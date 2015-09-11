#ifndef DEFAULT_SETTING
#define DEFAULT_SETTING

#include <Qt>

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
// const QString BOLD_BUTTON_ICON_SUFFIX("icons/bold_button_icon.png");
// const QString UNDERLINE_BUTTON_ICON_SUFFIX("icons/underline_button_icon.png");


// Action tip text
const QString OPEN_FOLDER_TIP_TEXT("開啟病人資料夾");
const QString SETTING_TIP_TEXT("設定");
const QString XRAY_WINDOW_TIP_TEXT("X光照片");
const QString IMAGE_WINDOW_TIP_TEXT("一般照片");
const QString SWITCH_TOOLBAR_VISIBLE_TIP_TEXT("顯示工具列");
const QString FAQ_TIP_TEXT("FAQ / 關於");


// Note
const QStringList TEXT_SIZE_QSTRING_LIST = QStringList()
	<< "12" << "14" << "16" << "18" << "20" << "22" << "24";
const QList<int> TEXT_SIZE_LIST = QList<int>()
	<< 12 << 14 << 16 << 18 << 20 << 22 << 24;

const QSize COLOR_BLOCK_ICON_SIZE(12, 12);

const QStringList TEXT_COLOR_QSTRING_LIST = QStringList()
	<< "黑色" << "白色" << "紅色" << "桃紅" << "黃色" << "綠色" << "青色" << "藍色" << "靛色";
const QList<QColor> TEXT_COLOR_LIST = QList<QColor>()
	<< QColor(Qt::black) << QColor(Qt::white) << QColor(Qt::red)
	<< QColor(Qt::magenta) << QColor(Qt::yellow)
	<< QColor(Qt::green) << QColor(Qt::cyan) << QColor(Qt::blue)
	<< QColor(Qt::darkBlue);

const QStringList TEXT_BACKGROUND_QSTRING_LIST = QStringList()
	<< "黑色" << "白色" << "紅色" << "桃紅" << "黃色" << "綠色" << "青色" << "藍色" << "靛色";
const QList<QColor> TEXT_BACKGROUND_LIST = QList<QColor>()
	<< QColor(Qt::black) << QColor(Qt::white) << QColor(Qt::red)
	<< QColor(Qt::magenta) << QColor(Qt::yellow)
	<< QColor(Qt::green) << QColor(Qt::cyan) << QColor(Qt::blue)
	<< QColor(Qt::darkBlue);


// Image scale and format
const qreal FIT_IMAGE_SIZE_RATIO = 0.98;
const QStringList READABLE_IMAGE_LIST = QStringList() << "*.jpg" << "*.bmp" << "*.png" << "*.gif";

// Window title
const QString MAIN_WINDOW_TITLE("Case Viewer");
const QString XRAY_WINDOW_TITLE("X光照片");
const QString IMAGE_WINDOW_TITLE("一般照片");
const QString SETTING_DIALOG_TITLE("設定");
const QString MESSAGE_DIALOG_TITLE("訊息");
const QString FAQ_WINDOW_TITLE("FAQ / 關於");
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
const QString FIT_WINDOW_TEXT("填滿(space)");


// Note
const QString NOTE_FILE_SUFFIX_NAME("_note.txt");
const QString NOTE_HINT("病人紀錄...");


// FAQ/About window
const QString FAQ_TAB_TITLE("FAQ");
const QString ABOUT_TAB_TITLE("關於");
const QString OK_TEXT("確定");


// Message window
const QString WRONG_XRAY_FOLDER_MESSAGE_1("在「");
const QString WRONG_XRAY_FOLDER_MESSAGE_2("」資料夾底下找不到「");
const QString WRONG_XRAY_FOLDER_MESSAGE_3("」資料夾！\n請確定有「");
const QString WRONG_XRAY_FOLDER_MESSAGE_4("」資料夾或是修改「設定」中的X光資料夾名稱使它和病人資料夾裡的名稱一致");

const QString WRONG_IMAGE_FOLDER_MESSAGE_1("在「");
const QString WRONG_IMAGE_FOLDER_MESSAGE_2("」資料夾底下找不到「");
const QString WRONG_IMAGE_FOLDER_MESSAGE_3("」資料夾！\n請確定有「");
const QString WRONG_IMAGE_FOLDER_MESSAGE_4("」資料夾或是修改「設定」中的一般照片資料夾名稱使它和病人資料夾裡的名稱一致");

const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE_1("在「");
const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE_2("」資料夾底下找不到「");
const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE_3("」資料夾和「");
const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE_4("」資料夾！\n請確定有「");
const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE_5("」資料夾和「");
const QString WRONG_XRAY_IMAGE_FOLDER_MESSAGE_6("」資料夾或是修改「設定」中的資料夾名稱使它們和病人資料夾裡的名稱一致");

// Preference constant
const QString PREFERENCE_FILE_AUTO_OPEN_TEXT("auto open windows");
const QString PREFERENCE_FILE_NOT_AUTO_OPEN_TEXT("not auto open windows");

// Preference file
const QStringList PREFERENCE_FILE_WARNING_LINES = QStringList()
	<< "=====================================\n"
	<< "Case Viewer ver.1.0\n"
	<< "Warning!! Don't modify this file!\n"
	<< "=====================================\n";


#endif // DEFAULT_SETTING

