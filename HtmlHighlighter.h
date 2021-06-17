#ifndef HTMLHIGHLIGHTER_H
#define HTMLHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegExp>

class HtmlHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    HtmlHighlighter(QTextDocument *parent = 0);

protected:
    void highlightBlock(const QString &text) override;

private:
    enum States {
        None,
        Tag,
        Comment,
        Quote
    };

    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QVector<HighlightingRule> startTagRules;
    QVector<HighlightingRule> endTagRules;

    QRegExp openTag;
    QRegExp closeTag;
    QTextCharFormat edgeTagFormat;
    QTextCharFormat insideTagFormat;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;
    QTextCharFormat multiLineCommentFormat;

    QRegExp quotes;
    QTextCharFormat quotationFormat;
    QTextCharFormat tagsFormat;
};

#endif // HTMLHIGHLIGHTER_H
