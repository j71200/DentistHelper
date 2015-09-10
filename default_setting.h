#ifndef DEFAULT_SETTING
#define DEFAULT_SETTING

// Path
const QString DEFAULT_FOLDER_PATH("/Users/blue/");
const QString APP_FOLDER_PATH("/Users/blue/QtWorkspace/firstQt/");
const QString PREFERENCES_FILE_PATH("/Users/blue/QtWorkspace/firstQt/Output/my_preferences.txt");

// Folder
const QString DEFAULT_XRAY_FOLDER_NAME("x-rays");
const QString DEFAULT_IMAGE_FOLDER_NAME("照片");

// Icon suffix
const QString OPEN_FOLDER_ICON_SUFFIX("icons/open_folder.png");
const QString SETTING_ICON_SUFFIX("icons/setting.png");
const QString XRAY_WINDOW_ICON_SUFFIX("icons/xray_icon.png");
const QString IMAGE_WINDOW_ICON_SUFFIX("icons/image_icon.png");
const QString FAQ_ICON_SUFFIX("icons/faq_icon.png");
const QString CHECK_ICON_SUFFIX("icons/check_icon.png");
const QString CROSS_ICON_SUFFIX("icons/cross_icon.png");

// Action tip text
const QString OPEN_FOLDER_TIP_TEXT("Open Folder");
const QString SETTING_TIP_TEXT("Setting");
const QString XRAY_WINDOW_TIP_TEXT("X-ray window");
const QString IMAGE_WINDOW_TIP_TEXT("Image window");
const QString FAQ_TIP_TEXT("FAQ / About");


// Image scale and format
const qreal FIT_IMAGE_SIZE_RATIO = 0.98;
const QStringList READABLE_IMAGE_LIST = QStringList() << "*.jpg" << "*.bmp" << "*.png" << "*.gif";

// Window title
const QString MAIN_WINDOW_TITLE("Case Viewer");
const QString XRAY_WINDOW_TITLE("X-ray Photo");
const QString IMAGE_WINDOW_TITLE("Original Photo");
const QString SETTING_DIALOG_TITLE("Setting");
const QString MESSAGE_DIALOG_TITLE("Message!");
const QString FAQ_WINDOW_TITLE("FAQ / About");
const QString HYPHEN(" - ");

// TreeView
const int MAX_TREEVIEW_WIDTH = 300;

// Image
const int MIN_SCALE_RATIO = 1;
const int MAX_SCALE_RATIO = 300;
const int SLIDER_SINGLE_STEP = 10;

// Icon size
const QSize DEFAULT_ICON_SIZE(20, 20);

// ==================
// String
// ==================
const QString FIT_WINDOW_TEXT("Fit window size (space)");


// Note
const QString NOTE_FILE_SUFFIX_NAME("_note.txt");
const QString NOTE_HINT("How about taking some note");


// FAQ/About window
const QString FAQ_TAB_TITLE("FAQ");
const QString ABOUT_TAB_TITLE("About");
const QString OK_TEXT("OK");


// Message window
const QString WRONG_XRAY_FOLDER_MESSAGE("Wrong x-ray folder path!\nPlease check your x-ray folder name\nor correct the X-RAY FOLDER NAME in setting.");
const QString WRONG_IMAGE_FOLDER_MESSAGE("Wrong image folder path!\nPlease check your image folder name\nor correct the IMAGE FOLDER NAME in setting.");
const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE("Wrong x-ray and image folder path!\nPlease check your x-ray and image folder name\nor correct both the X-RAY FOLDER NAME\nand IMAGE FOLDER NAME in setting.");


// Preference file
const QStringList PREFERENCE_FILE_WARNING_LINES = QStringList()
	<< "=====================================\n"
	<< "Warning!!\n"
	<< "=====================================\n";


#endif // DEFAULT_SETTING

