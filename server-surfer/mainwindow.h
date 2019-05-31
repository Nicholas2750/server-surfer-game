#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>
#include <QMessageBox>
#include "./server-surfer-backend/src/server_surfer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT



public:
    // Constructor called by main.cpp to start the game.
    explicit MainWindow(QWidget *parent = nullptr);


// slots that gets activated whenever a user interacts with the GUI
// as noted by their different naming convention than normal methods.
private slots:
    void on_start_button_clicked();
    void on_open_in_browser_button_clicked();
    void on_next_server_button_clicked();
    void on_stop_button_clicked();
    void on_retry_button_clicked();
    void on_scan_port_button_clicked();
    void on_find_subdomain_button_clicked();
    void on_find_subdirectory_button_clicked();


// Normal methods that implements the logic of the GUI.
private:
    // Implements the switching between screens.
    void ShowStartScreenInterface(bool);
    void ShowGameScreenInterface(bool);
    void ShowEndScreenInterface(bool);

    // Updates the state of the game.
    void UpdateState();
    void UpdateNextServerList();
    void EndOngoingGame(QString);

    // Displays the result of scanning a server.
    void DisplayScanResult(string);


    // Private variables that are used throughout the cycle of the game.
    Ui::MainWindow *ui;
    Game server_surfer;
    bool can_choose_server;


    // Constants that are used in the game.
    const QString INVALID_URL_TITLE = "Invalid URL";
    const QString INVALID_URL_MESSAGE = "The URL you have entered is not valid";
    const QString SCAN_TITLE = "Scan Result";
    const QString START_SERVER_INFO_HEADER = "You started from :\n";
    const QString CURRENT_SERVER_INFO_HEADER = "You are currently at :\n";
    const QString MOVES_TAKEN_INFO_HEADER = "Moves Taken: ";
    const QString OUT_OF_MOVE_MESSAGE = "You have ran out of moves";
    const QString DEAD_END_MESSAGE = "You have ended up in an invalid server / server with no links";
    const string END_MESSAGE = "\n\nGame Over\nScore: ";

    const QString MESSAGE_BOX_STYLESHEET = "QLabel{min-width: 750px;}";

    const int MAX_MOVES_ALLOWED = 10;
    const int MAX_NEXT_SERVER_OPTION_ALLOWED = 10;
};

#endif // MAINWINDOW_H
