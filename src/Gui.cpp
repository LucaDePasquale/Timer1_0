//
// Created by depa on 19.11.25.
//

#include "Gui.h"
#include <sstream>
#include <iomanip>

GUI::GUI(std::shared_ptr<Timer> t)
    : timer(t)
{
    frame = new wxFrame(nullptr, wxID_ANY, "Timer GUI", wxDefaultPosition, wxSize(450,300));
    panel = new wxPanel(frame);

    // LIST
    wxArrayString hoursList;
    wxArrayString minutesList;
    wxArrayString secondsList;

    for (int i = 0; i < 60; i++) {
        wxString val = wxString::Format("%02d", i);
        if (i < 24) hoursList.Add(val);
        minutesList.Add(val);
        secondsList.Add(val);
    }

    hoursChoice = new wxChoice(panel, ID_CH_HOURS, wxPoint(50,30), wxSize(60,25), hoursList);
    minutesChoice = new wxChoice(panel, ID_CH_MINUTES, wxPoint(120,30), wxSize(60,25), minutesList);
    secondsChoice = new wxChoice(panel, ID_CH_SECONDS, wxPoint(190,30), wxSize(60,25), secondsList);

    hoursChoice->SetSelection(0);
    minutesChoice->SetSelection(0);
    secondsChoice->SetSelection(0);


    // LABEL TIMER

    timerLabel = new wxStaticText(panel, wxID_ANY, "00:00:00", wxPoint(160,90), wxSize(120,30));
    timerLabel->SetFont(wxFont(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    // LABEL DATE
    dateLabel = new wxStaticText(panel, wxID_ANY,dateTime.updateCurrent(),wxPoint(20, 10), wxSize(250, 30));

    dateLabel->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD));


    // STATUS LABEL

    statusLabel = new wxStaticText(panel, wxID_ANY, "PAUSED", wxPoint(170,130), wxSize(120,30));


    // BOTTONS

    startPauseBtn = new wxButton(panel, ID_BTN_START, "Start", wxPoint(50,180));
    restartBtn    = new wxButton(panel, ID_BTN_RESTART, "Restart", wxPoint(150,180));
    applyBtn      = new wxButton(panel, ID_BTN_APPLY, "Apply", wxPoint(270,30));
    formatBtn = new wxButton(panel, ID_BTN_FORMAT, "Format", wxPoint(50, 200));
    frame->Bind(wxEVT_BUTTON, &GUI::OnFormatChange, this, ID_BTN_FORMAT);


    // TIMER GUI

    guiTimer = new wxTimer(frame, ID_GUI_TIMER);

    // BIND EVENT
    frame->Bind(wxEVT_BUTTON, &GUI::OnStartPause, this, ID_BTN_START);
    frame->Bind(wxEVT_BUTTON, &GUI::OnRestart, this, ID_BTN_RESTART);
    frame->Bind(wxEVT_BUTTON, &GUI::OnApply, this, ID_BTN_APPLY);
    frame->Bind(wxEVT_TIMER,  &GUI::OnGuiTick, this, ID_GUI_TIMER);

    guiTimer->Start(100);

    attach();
}

GUI::~GUI() {
    detach();
}

void GUI::Show() {
    frame->Show(true);
}

// OBSERVER
void GUI::attach() {
    timer->subscribe(this);
}
void GUI::detach() {
    timer->unsubscribe(this);
}

void GUI::update() {
    int sec = timer->getRemainingTime();

    timerLabel->SetLabel(formatTime(sec));

    if (sec == 0) {
        statusLabel->SetLabel("TIMER UP!");
        startPauseBtn->SetLabel("Start");
    }
    else if (timer->isRunning()) {
        statusLabel->SetLabel("RUNNING");
        startPauseBtn->SetLabel("Pause");
    }
    else {
        statusLabel->SetLabel("PAUSED");
        startPauseBtn->SetLabel("Start");
    }
}


// EVENT


void GUI::OnGuiTick(wxTimerEvent&) {
    dateLabel->SetLabel(dateTime.updateCurrent());
    timer->getTick();
}

void GUI::OnStartPause(wxCommandEvent&) {
    if (timer->isRunning()) {
        timer->stopTimer();
        startPauseBtn->SetLabel("Start");
    }
    else {
        timer->resumeTimer();
        startPauseBtn->SetLabel("Pause");
    }
}

void GUI::OnRestart(wxCommandEvent&) {
    try {
        timer->restartTimer();
    } catch (...) {
        statusLabel->SetLabel("Can't restart while running");
    }
}

void GUI::OnApply(wxCommandEvent&) {

    int h = hoursChoice->GetSelection();
    int m = minutesChoice->GetSelection();
    int s = secondsChoice->GetSelection();

    int total = h * 3600 + m * 60 + s;

    timer->setDuration(total);

    timerLabel->SetLabel(formatTime(total));
    statusLabel->SetLabel("PAUSED");
}


// FORMAT TIME


std::string GUI::formatTime(int seconds) {
    std::ostringstream oss;
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;

    oss << std::setw(2) << std::setfill('0') << h << ":"
        << std::setw(2) << std::setfill('0') << m << ":"
        << std::setw(2) << std::setfill('0') << s;

    return oss.str();
}
void GUI::OnFormatChange(wxCommandEvent&)
{
    dateTime.setViewmode();
    dateLabel->SetLabel(dateTime.updateCurrent());
}