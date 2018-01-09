#include "pdfutils.h"

PdfUtils::PdfUtils(QString filePath)
{
    this->filePath = filePath;
    getPdfInfo();
}

PdfUtils::~PdfUtils()
{
}

QImage PdfUtils::getPdfImage(int pageNumber, int width, int height)
{
    QImage image;
    Poppler::Document* document = Poppler::Document::load(filePath);
    document->setRenderHint(Poppler::Document::TextAntialiasing);
    if (!document || document->isLocked())
    {
        // ... error message ....
        delete document;
        return image;
    }
    // Document starts at page 0
    Poppler::Page* pdfPage = document->page(pageNumber);
    if (pdfPage == 0)
    {
        // ... error message ...
        return image;
    }
    // Generate a QImage of the rendered page
    image = pdfPage->renderToImage(width*72/pdfPage->pageSize().width(),height*72/pdfPage->pageSize().height());
    if (image.isNull())
    {
        // ... error message ...
        return image;
    }
    // after the usage, the page must be deleted
    delete pdfPage;
    delete document;
    return image;
}

int PdfUtils::getNumPages()
{
    return numPages;
}

// first page size
QSize PdfUtils::getPageSize()
{
    return pageSize;
}

void PdfUtils::getPdfInfo()
{
    numPages = 0;
    Poppler::Document* document = Poppler::Document::load(filePath);
    if (!document || document->isLocked())
    {
        // ... error message ....
        delete document;
        return;
    }
    numPages = document->numPages();
    Poppler::Page* pdfPage = document->page(0);
    pageSize = pdfPage->pageSize();
    delete pdfPage;
    delete document;
}
