# _**Mobile Device Encryption/Security Auditor**_

## _**Overview**_

This app checks the encryption status of an Android device using the Android SafetyNet API. It displays a message indicating whether the device is encrypted or not.

## _**Requirements**_

- Qt 5.0 or higher
- Android SDK (for building and deploying on Android devices)

## _**Usage**_

1. Build and run the application on an Android device or emulator.
2. Click the "Check Encryption Status" button.
3. The application will display a message box indicating whether the device is encrypted or not.

## _**Implementation Details**_

The application is implemented in C++ using the Qt framework. The main components include:

- `SecurityAuditor` class: Inherits from `QWidget` and provides the main functionality of the application. It includes a method (`checkEncryptionStatus`) that queries the Android SafetyNet API to determine the encryption status.

- `getAndroidEncryptionStatus` method: Uses Qt Android Extras to call the Android SafetyNet API for Android 10. It retrieves the package signature and performs an attestation request to determine the encryption status.

## _**Building and Running**_

1. Ensure you have Qt installed on your development machine.
2. Open the project in Qt Creator or use the command line to build the application.
3. Deploy the application to an Android device or emulator.

```bash
# Example command for building and deploying
qmake
make
make install
```

## _**Contributions**_

Contributions are welcome! If you find any issues or have suggestions for improvements, feel free to open an issue or submit a pull request.
