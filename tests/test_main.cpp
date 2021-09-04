#include <QCoreApplication>
#include <QtTest>

#include "xlsxdocument.h"

class TestQXlsxIssue152 : public QObject {
    Q_OBJECT

public:
    TestQXlsxIssue152() = default;
    ~TestQXlsxIssue152() = default;

private slots:
    void
    testAutosizeColumnWidth();

    void
    testColumnWidth();

    void
    testColumnWidthAcrossManyColumns();

private:
    void
    saveDocument(QXlsx::Document &document, const QString &filePath);
};

void
TestQXlsxIssue152::
testAutosizeColumnWidth() {
    const int testCellIndex = 1;
    QVariant cellData =
            "Some large test string "
            "that doesn't fit in a regular column";

    QXlsx::Document document;
    document.write(
                testCellIndex,
                testCellIndex,
                cellData);

    document.autosizeColumnWidth(testCellIndex, testCellIndex);
    saveDocument(document, "autosize-column-width.xlsx");

    double columnWidth = document.columnWidth(testCellIndex);

    // The column width shouldn't be zero
    // because the data of the cell is some large string
    // that doesn't fit in 0 width
    QVERIFY(columnWidth > 0.0);
}

void
TestQXlsxIssue152::
testColumnWidth() {
    const double expectedColumnWidth = 32.0;
    const int testCellIndex = 1;
    QVariant cellData = 1337;

    QXlsx::Document document;
    document.write(
                testCellIndex,
                testCellIndex,
                cellData);

    document.setColumnWidth(testCellIndex, expectedColumnWidth);
    saveDocument(document, "column-width.xlsx");

    double columnWidth = document.columnWidth(testCellIndex);
    QVERIFY(columnWidth > 0.0);
    QVERIFY(qFuzzyCompare(columnWidth, expectedColumnWidth));
}

void
TestQXlsxIssue152::
testColumnWidthAcrossManyColumns() {
    const int columnCount = 255;
    const int initialWidth = 1;
    const int increaseWidthStep = 1;
    const int testRowIndex = 1;

    QXlsx::Document document;
    double expectedColumnWidth = initialWidth;
    for (int i = 1; i <= columnCount; ++i) {
        document.write(testRowIndex, i, i);
        document.setColumnWidth(i, expectedColumnWidth);

        expectedColumnWidth += increaseWidthStep;
    }
    saveDocument(document, "column-width-across-many-columns.xlsx");

    expectedColumnWidth = initialWidth;
    for (int i = 1; i <= columnCount; ++i) {
        double columnWidth = document.columnWidth(i);
        QVERIFY(columnWidth > 0.0);
        QVERIFY(qFuzzyCompare(columnWidth, expectedColumnWidth));

        expectedColumnWidth += increaseWidthStep;
    }
}

void
TestQXlsxIssue152::
saveDocument(QXlsx::Document &document, const QString &filePath) {
#ifdef SAVE_TEST_DOCUMENTS
    document.saveAs(filePath);
#else
    Q_UNUSED(document)
    Q_UNUSED(filePath)
#endif // SAVE_TEST_DOCUMENTS
}

QTEST_MAIN(TestQXlsxIssue152)

#include "test_main.moc"
