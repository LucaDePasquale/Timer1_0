#include <iostream>


#include "Gui.h"
#include "Timer.h"
#include "Datetime.h"
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    bool OnInit() override {
        auto timer = std::make_shared<Timer>();
        GUI* gui = new GUI(timer);
        gui->Show();
        return true;
    }
};
wxIMPLEMENT_APP(MyApp);

// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.