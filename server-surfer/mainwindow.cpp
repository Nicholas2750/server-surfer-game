#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server-surfer-backend/src/server_surfer.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    server_surfer = Game();

    can_choose_server = false;

    ShowGameScreenInterface(false);
    ShowEndScreenInterface(false);
}


void MainWindow::ShowStartScreenInterface(bool visibility) {
    ui->info_box->setVisible(visibility);
    ui->url_textbox->setVisible(visibility);
    ui->start_button->setVisible(visibility);
}


void MainWindow::ShowGameScreenInterface(bool visibility) {
    ui->current_server->setVisible(visibility);
    ui->start_server->setVisible(visibility);

    ui->status_box->setVisible(visibility);

    ui->next_server_list->setVisible(visibility);
    ui->next_server_button->setVisible(visibility);
    ui->stop_button->setVisible(visibility);

    ui->open_in_browser_button->setVisible(visibility);
    ui->scan_port_button->setVisible(visibility);
    ui->find_subdomain_button->setVisible(visibility);
    ui->find_subdirectory_button->setVisible(visibility);
}


void MainWindow::ShowEndScreenInterface(bool visibility) {
    ui->status_box->setVisible(visibility);
    ui->retry_button->setVisible(visibility);
}


void MainWindow::EndOngoingGame(QString why_game_ended) {
    can_choose_server = false;

    string end_message = END_MESSAGE + std::to_string(server_surfer.CalculateScore());
    ui->status_box->setText(why_game_ended + QString::fromStdString(end_message));

    ShowGameScreenInterface(false);
    ShowEndScreenInterface(true);
}


void MainWindow::UpdateNextServerList() {
    ui->next_server_list->clear();

    for (int i = 0; i < server_surfer.GetLinks().size(); i++) {

        if (i >= MAX_NEXT_SERVER_OPTION_ALLOWED) {
            break;
        }

        QString link = QString::fromStdString(server_surfer.GetLinks()[i]);
        ui->next_server_list->addItem(link);
    }
}


void MainWindow::UpdateState() {
    // Gets all needed data.
    QString start_server_info = QString::fromStdString(server_surfer.GetStartServerInfo());
    QString current_server_info = QString::fromStdString(server_surfer.GetCurrentServerInfo());
    int moves_taken = server_surfer.GetMovesTaken();
    int number_of_links_extracted = server_surfer.GetLinks().size();

    // Updates the information displayed to player.
    ui->start_server->setText(START_SERVER_INFO_HEADER + start_server_info);
    ui->current_server->setText(CURRENT_SERVER_INFO_HEADER + current_server_info);
    ui->status_box->setText(MOVES_TAKEN_INFO_HEADER + QString::number(moves_taken));
    UpdateNextServerList();

    can_choose_server = true;

    // Checks if the game should end.
    if (moves_taken >= MAX_MOVES_ALLOWED) {
        EndOngoingGame(OUT_OF_MOVE_MESSAGE);
    }

    if (number_of_links_extracted == 0) {
        EndOngoingGame(DEAD_END_MESSAGE);
    }
}


void MainWindow::DisplayScanResult(string scan_result) {
    QString scan_result_to_display = QString::fromStdString(scan_result);

    QMessageBox message_box;
    message_box.setWindowTitle(SCAN_TITLE);
    message_box.setText(scan_result_to_display);
    message_box.setStyleSheet(MESSAGE_BOX_STYLESHEET);

    message_box.exec();
}


// Note that the different naming convention of the methods writte below this comment indicates
// that they are slots that gets activated when user interacts with the GUI element such as buttons.


void MainWindow::on_open_in_browser_button_clicked() {
    QString current_url = QString::fromStdString(server_surfer.GetCurrentServerURL());

    QDesktopServices::openUrl(current_url);
}


void MainWindow::on_next_server_button_clicked() {
    string selected_server = ui->next_server_list->currentText().toStdString();

    if (can_choose_server) {
        can_choose_server = false;

        server_surfer.MakeMove(selected_server);

        UpdateState();
    }
}


void MainWindow::on_start_button_clicked() {
    string url = ui->url_textbox->text().toStdString();

    if (!server_surfer.IsValidURL(url)) {
        QMessageBox message_box;
        message_box.critical(0, INVALID_URL_TITLE, INVALID_URL_MESSAGE);
        return;
    }

    ShowStartScreenInterface(false);
    ShowGameScreenInterface(true);

    server_surfer.MakeMove(url);

    UpdateState();
}


void MainWindow::on_stop_button_clicked() {
    EndOngoingGame("");
}


void MainWindow::on_retry_button_clicked() {
    server_surfer = Game();

    can_choose_server = false;

    ShowStartScreenInterface(true);
    ShowGameScreenInterface(false);
    ShowEndScreenInterface(false);
}


void MainWindow::on_scan_port_button_clicked() {
    string port_scan_result = server_surfer.ScanCurrentServerPort();
    DisplayScanResult(port_scan_result);
}


void MainWindow::on_find_subdomain_button_clicked() {
    string subdomain_scan_result = server_surfer.ScanCurrentServerSubdomain();
    DisplayScanResult(subdomain_scan_result);
}


void MainWindow::on_find_subdirectory_button_clicked() {
    string subdirectory_scan_result = server_surfer.ScanCurrentServerSubdirectory();
    DisplayScanResult(subdirectory_scan_result);
}
