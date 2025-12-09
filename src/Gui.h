//
// Created by depa on 19.11.25.
//

#ifndef GUI_H
#define GUI_H



#include <wx/wx.h>
#include <wx/timer.h>
#include <wx/spinctrl.h>
#include <memory>
#include "Timer.h"
#include "Observer.h"
#include "Datetime.h"

class GUI : public Observer {
public:
    GUI(std::shared_ptr<Timer> t);
    ~GUI() override;

    void Show();

    // Observer methods
    void update() override;
    void attach() override;
    void detach() override;

    void OnGuiTick(wxTimerEvent& event);
    void OnStartPause(wxCommandEvent& event);
    void OnRestart(wxCommandEvent& event);
    void OnApply(wxCommandEvent& event);
    void OnFormatChange(wxCommandEvent& event);

    std::string formatTime(int seconds);

    enum {
        ID_GUI_TIMER = 1001,
        ID_BTN_START,
        ID_BTN_RESTART,
        ID_CH_HOURS,
        ID_CH_MINUTES,
        ID_CH_SECONDS,
        ID_BTN_APPLY,
        ID_BTN_FORMAT,
    };



private:
    std::shared_ptr<Timer> timer;

    wxFrame* frame;
    wxPanel* panel;
    wxStaticText* timerLabel;
    wxStaticText* statusLabel;
    wxTimer* guiTimer;
    wxButton* startPauseBtn;
    wxButton* restartBtn;
    wxButton* plusBtn;
    wxButton* minusBtn;
    wxSpinCtrl* spinHours;
    wxSpinCtrl* spinMinutes;
    wxSpinCtrl* spinSeconds;


    wxChoice* hoursChoice;
    wxChoice* minutesChoice;
    wxChoice* secondsChoice;
    wxButton* applyBtn;

    DateTime dateTime;
    wxStaticText* dateLabel;
    wxButton* formatBtn;



    


};



#endif //GUI_H


