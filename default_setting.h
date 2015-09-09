#ifndef DEFAULT_SETTING
#define DEFAULT_SETTING

// Path
const QString DEFAULT_FOLDER_PATH("/Users/blue/");
const QString APP_FOLDER_PATH("/Users/blue/QtWorkspace/firstQt/");
const QString PREFERENCES_FILE_PATH("/Users/blue/QtWorkspace/firstQt/Output/my_preferences.txt");

// Icon suffix
const QString OPEN_FOLDER_ICON_SUFFIX("icons/open_folder.png");
const QString SETTING_ICON_SUFFIX("icons/setting.png");
const QString XRAY_WINDOW_ICON_SUFFIX("icons/xray_icon.png");
const QString IMAGE_WINDOW_ICON_SUFFIX("icons/image_icon.png");
const QString FAQ_ICON_SUFFIX("icons/faq_icon.png");
// const QString LOCK_ICON_SUFFIX("icons/lock.png");
// const QString UNLOCK_ICON_SUFFIX("icons/unlock.png");

// Action tip text
const QString OPEN_FOLDER_TIP_TEXT("Open Folder");
const QString SETTING_TIP_TEXT("Setting");
const QString XRAY_WINDOW_TIP_TEXT("X-ray window");
const QString IMAGE_WINDOW_TIP_TEXT("Image window");
const QString FAQ_TIP_TEXT("FAQ");


// Image scale and format
const qreal FIT_IMAGE_SIZE_RATIO = 0.98;
const QStringList READABLE_IMAGE_LIST = QStringList() << "*.jpg" << "*.bmp" << "*.png" << "*.gif";

// Window title
const QString MAIN_WINDOW_TITLE("Case Viewer");
const QString XRAY_WINDOW_TITLE("X-ray Photo");
const QString IMAGE_WINDOW_TITLE("Original Photo");
const QString SETTING_DIALOG_TITLE("Setting");
const QString MESSAGE_DIALOG_TITLE("Message!");
const QString FAQ_WINDOW_TITLE("FAQ");
const QString HYPHEN(" - ");

// TreeView
const int MAX_TREEVIEW_WIDTH = 300;

// Image
const int MIN_SCALE_RATIO = 1;
const int MAX_SCALE_RATIO = 300;
const int SLIDER_SINGLE_STEP = 10;

// Icon size
// const QSize DEFAULT_ICON_SIZE(30, 30);

// ==================
// String
// ==================
const QString FIT_WINDOW_TEXT("Fit window size (space)");

// X-ray TreeView
const QString XRAY_TO_XRAY_PATH("x-ray/");

// Image TreeView
const QString PHOTO_TO_PHOTO_PATH("照片/");


// Note
const QString NOTE_FILE_SUFFIX_NAME("_note.txt");
const QString NOTE_HINT("How about taking some note");



#endif // DEFAULT_SETTING

