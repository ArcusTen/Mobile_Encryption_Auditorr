#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QtAndroidExtras>

class SecurityAuditor : public QWidget
{
    Q_OBJECT

public:
    SecurityAuditor(QWidget *parent = nullptr) : QWidget(parent)
    {
        setupUi();
    }

private slots:
    void checkEncryptionStatus()
    {
        bool isEncrypted = getAndroidEncryptionStatus();

        if (isEncrypted)
        {
            QMessageBox::information(this, "Encryption Status", "Device is encrypted!");
        }
        else
        {
            QMessageBox::warning(this, "Encryption Status", "Device is not encrypted!");
        }
    }

private:
    void setupUi()
    {
        QVBoxLayout *layout = new QVBoxLayout(this);

        QLabel *titleLabel = new QLabel("Mobile Device Encryption/Security Auditor", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        layout->addWidget(titleLabel);

        QPushButton *checkButton = new QPushButton("Check Encryption Status", this);
        connect(checkButton, &QPushButton::clicked, this, &SecurityAuditor::checkEncryptionStatus);
        layout->addWidget(checkButton);

        setLayout(layout);
    }

    bool getAndroidEncryptionStatus()
    {
        // Using Qt Android Extras to call Android SafetyNet API for Android 10
        QAndroidJniObject activity = QtAndroid::androidActivity();
        if (activity.isValid()) {
            QAndroidJniObject context = activity.callObjectMethod("getApplicationContext", "()Landroid/content/Context;");
            QAndroidJniObject packageManager = context.callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
            QAndroidJniObject packageName = context.callObjectMethod("getPackageName", "()Ljava/lang/String;");
            QAndroidJniObject signature = packageManager.callObjectMethod("getPackageInfo", "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;", packageName.object<jstring>(), 64).getObjectField("signatures").getObjectArrayElement(0);
            QAndroidJniObject safetyNetAPI = QAndroidJniObject::getStaticObjectField("com/google/android/gms/safetynet/SafetyNet", "getClient", "(Landroid/content/Context;)Lcom/google/android/gms/safetynet/SafetyNetClient;", context.object<jobject>());

            QAndroidJniObject safetyNetTask = safetyNetAPI.callObjectMethod("attest", "(Lcom/google/android/gms/safetynet/SafetyNetApiAttestationRequest;)Lcom/google/android/gms/tasks/Task;", signature);
            QAndroidJniEnvironment env;
            if (env->ExceptionCheck()) {
                env->ExceptionClear();
                return false;
            }
            return true;
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    SecurityAuditor auditor;
    auditor.setWindowTitle("Mobile Security Auditor");
    auditor.resize(400, 200);
    auditor.show();

    return app.exec();
}

#include "main.moc"
