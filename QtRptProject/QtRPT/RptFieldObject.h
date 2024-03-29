/*
Name: QtRpt
Version: 2.0.2
Web-site: http://www.qtrpt.tk
Programmer: Aleksey Osipov
E-mail: aliks-os@ukr.net
Web-site: http://www.aliks-os.tk

Copyright 2012-2018 Aleksey Osipov

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#pragma once

#include "qtrpt.h"
#include "RptCrossTabObject.h"
#include "RptBandObject.h"
#include <qtrptnamespace.h>
#include <QDomElement>

#if QT_VERSION >= 0x050800
    #include <QtCharts>
#endif

using namespace QtRptName;

class QtRPT;
class RptBandObject;
class RptCrossTabObject;



class RptFieldObject
{
    friend class QtRPT;
    friend class RptBandObject;

public:
    RptFieldObject();
    ~RptFieldObject();
    QString name;
    QString value;
    QRect rect;
    QColor borderTop;
    QColor borderBottom;
    QColor borderLeft;
    QColor borderRight;
    QColor borderColor;
    QColor fontColor;
    QColor backgroundColor;

    void setDefaultFontColor(QColor value);
    void setDefaultBackgroundColor(QColor value);

    int borderWidth;
    bool autoHeight;
    bool textWrap;
    int rotate;

    Qt::Alignment aligment;
    QString borderStyle;
    QFont font;
    FieldType fieldType;
    QString formatString;
    QString highlighting;
    QString imgFormat;
    QString printing;
    int barcodeType;
    int barcodeFrameType;
    int barcodeHeight;
    int ignoreAspectRatio;
    QByteArray picture;
    RptBandObject *parentBand;
    RptCrossTabObject *parentCrossTab;

    #if QT_VERSION >= 0x50800
        QChart *chart;
    #endif

    void setChartData(GraphDataList dataList);
    GraphDataList getChartData();

    int lineStartX;
    int lineEndX;
    int lineStartY;
    int lineEndY;
    bool arrowStart;
    bool arrowEnd;

    int recNo() {return m_recNo;}
    int reportPage() {return m_reportPage;}
    void setTop(int top);

    QString getHTMLStyle();
    RptCrossTabObject *crossTab;
    bool isCrossTabChild();
    RptFieldObject *clone();

private:
    QColor m_fontColor;
    QColor m_backgroundColor;
    int m_recNo;
    int m_reportPage;
    int m_top;
    QtRPT *m_qtrpt;
    void setProperty(QtRPT *qtrpt, QDomElement e);
    void updateHighlightingParam();

};

Q_DECLARE_METATYPE(RptFieldObject)
Q_DECLARE_METATYPE(GraphDataList)

QDebug operator<<(QDebug dbg, const RptFieldObject &obj);
QDebug operator<<(QDebug dbg, const RptFieldObject *obj);

