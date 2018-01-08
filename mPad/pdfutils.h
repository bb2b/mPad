#ifndef PDFUTILS_H
#define PDFUTILS_H
#include <QObject>
#include <QImage>
#include <QSize>
#include "poppler-qt5.h"

class PdfUtils
{
public:
    explicit PdfUtils(QString filePath);
    ~PdfUtils();
    //��ȡָ��ҳpdfͼ��(ҳ���0��ʼ)
    QImage getPdfImage(int pageNumber, int width, int height);
    //��ȡpdf��ҳ��
    int getNumPages();
    //��ȡpdfҳ���С
    QSize getPageSize();
private:
    QString filePath;
    int numPages;
    QSize pageSize;
    void getPdfInfo();
};

#endif // PDFUTILS_H
