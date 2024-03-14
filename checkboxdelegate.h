#include <QItemDelegate>
#include <QPainter>

class CheckboxDelegate : public QItemDelegate
{
public:
    CheckboxDelegate(QObject* parent = nullptr) : QItemDelegate(parent) {}

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const override
    {
        bool isCheckable = index.flags() & Qt::ItemIsUserCheckable;
        bool isEnabled = index.flags() & Qt::ItemIsEnabled;

        if (isCheckable) {
            bool checked = index.data(Qt::CheckStateRole).toBool();

            QString imagePath = (isEnabled) ? (checked ? ":/new/prefix1/QSS_IMG/checked.png" : ":/new/prefix1/QSS_IMG/unchecked1.png") :
                                            (checked ? ":/new/prefix1/QSS_IMG/1.png" : ":/new/prefix1/QSS_IMG/0.png");

            QPixmap pixmap(imagePath);
            painter->drawPixmap(option.rect, pixmap);
        } else {
            QItemDelegate::paint(painter, option, index);
        }
    }
};
