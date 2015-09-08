#ifndef DEFAULT_SETTING
#define DEFAULT_SETTING

// Path
const QString DEFAULT_FOLDER_PATH("/Users/blue/");
const QString APP_FOLDER_PATH("/Users/blue/QtWorkspace/firstQt/");
const QString PREFERENCES_FILE_PATH("/Users/blue/QtWorkspace/firstQt/Output/my_preferences.txt");

// Icon suffix
const QString LOCK_ICON_SUFFIX("icons/lock.png");
const QString UNLOCK_ICON_SUFFIX("icons/unlock.png");

// Image scale and format
const qreal FIT_IMAGE_SIZE_RATIO = 0.98;
const QStringList READABLE_IMAGE_LIST = QStringList() << "*.jpg" << "*.bmp" << "*.png" << "*.gif";

// Window title
const QString MAIN_WINDOW_TITLE("Case Viewer");
const QString XRAY_WINDOW_TITLE("X-ray Photo");
const QString IMAGE_WINDOW_TITLE("Original Photo");
const QString SETTING_DIALOG_TITLE("Setting");
const QString MESSAGE_DIALOG_TITLE("Message!");

// TreeView
const int MAX_TREEVIEW_WIDTH = 300;

// Image
const int MIN_SCALE_RATIO = 1;
const int MAX_SCALE_RATIO = 300;
const int SLIDER_SINGLE_STEP = 10;

// Icon size
const QSize DEFAULT_ICON_SIZE(30, 30);

// ==================
// String
// ==================
const QString FIT_WINDOW_TEXT("Fit window size");

// X-ray TreeView
const QString XRAY_TO_XRAY_PATH("x-ray/");

// Image TreeView
const QString PHOTO_TO_PHOTO_PATH("照片/");


// Note
const QString NOTE_FILE_SUFFIX_NAME("_note.txt");
const QString NOTE_HINT("How about taking some note");



#endif // DEFAULT_SETTING

