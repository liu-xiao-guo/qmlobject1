#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlProperty>
#include <QScreen>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QRect geometry = QGuiApplication::primaryScreen()->availableGeometry();
    qDebug() << "Size width: " << geometry.width() << " height: " << geometry.height();

    QQuickView view;
    view.setSource(QUrl(QStringLiteral("qrc:///Main.qml")));
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    QQuickItem* root = view.rootObject();
    QObject *object = root->findChild<QObject*>("label");

    if (object) {
        object->setProperty("color", "red");
    }

    qDebug() << "Text Property value:" << QQmlProperty::read(object, "text").toString();
    QQmlProperty::write(object, "text", "Good morning");

    qDebug() << "Property value:" << object->property("fontSize").toString();
    object->setProperty("fontSize", "large");

    QList<QObject *> list = root->findChildren<QObject*>("label");
    qDebug() << "count: " << list.count();

    QObject *o;
    int index = 0;
    foreach (o, list) {
        qDebug() << "Text in label " << index << " is: " << o->property("text").toString();
        index++;
    }

    view.show();
    return app.exec();
}

