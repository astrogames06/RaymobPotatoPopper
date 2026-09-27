:: Builds the App
call gradlew.bat assembleDebug

:: Installs the App
adb install -r app\build\outputs\apk\debug\app-debug.apk

:: Force-stop the old process
adb shell am force-stop com.raylib.raymob
adb shell am kill com.raylib.raymob

:: Delays the App opening to prevent glitches
timeout /t 1 >nul

:: Opens the App
adb shell am start -S -n "com.raylib.raymob/.NativeLoader"