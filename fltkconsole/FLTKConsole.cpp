/**	@file
        @brief	implementation of FLTK console GUI

        @date
        2009-2011

        @author
        Ryan Pavlik
        <rpavlik@iastate.edu> and <abiryan@ryand.net>
        http://academic.cleardefinition.com/
        Iowa State University Virtual Reality Applications Center
        Human-Computer Interaction Graduate Program
*/

//          Copyright Iowa State University 2009-2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

// Internal Includes
#include "FLTKConsole.h"
#include "../VRJLuaOutput.h"

// FLTK-generated source
#include <vrjlua-fltk-console.h>

// Library/third-party includes
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Native_File_Chooser.H>

#include <boost/make_shared.hpp>

#include <vrj/Kernel/Kernel.h>

// Standard includes
#ifdef VERBOSE
#include <iostream>
#endif
#include <stdexcept>

namespace vrjLua {

    class FLTKConsoleView : public FLTKConsoleUI {
      public:
        FLTKConsoleView(FLTKConsole *console)
            : _console(console)
            , FLTKConsoleUI(700, 590, "VRJLua Console") {
            _input->buffer(new Fl_Text_Buffer());
            _existingCode->buffer(new Fl_Text_Buffer());
            show();
        }

        virtual void runInput() {
            std::string input;
            {
                char *input_chars = _input->buffer()->text();
                input = std::string(input_chars);
                free(input_chars);
            }

            bool ret = _console->addString(input);
            if (ret) {
                _input->buffer()->text("");
            }
        }

        virtual void chooseAndRunFile() {
            boost::shared_ptr<Fl_Native_File_Chooser> fc =
                boost::make_shared<Fl_Native_File_Chooser>(
                    Fl_Native_File_Chooser::BROWSE_FILE);
            fc->title("Open VRJLua File...");
            fc->filter("VRJLua files\t*.{vrjlua,lua}");

            int ret = fc->show();
            if (ret != 0) {
                // No file picked, for one reason or another.
                return;
            }

            appendToDisplay("\n-- Run file chosen in GUI");
            _console->addFile(fc->filename());
        }

        virtual void saveFile() {
            Fl_Native_File_Chooser fc(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
            fc.title("Save VRJLua File...");
            fc.filter("VRJLua files\t*.{vrjlua,lua}");

            int ret = fc.show();
            if (ret != 0) {
                // No file picked, for one reason or another.
                return;
            }

            int saveret = _existingCode->buffer()->savefile(fc.filename());
            if (saveret == 0) {
                // Successful - append to the text display
                std::string code("-- code up to here saved to file '");
                code += fc.filename();
                code += "'\n";
                appendToDisplay(code.c_str());
            } else {
                appendToDisplay("\n-- Saving to chosen file failed");
            }
        }

        virtual void appendToDisplay(std::string const &message) {
            _existingCode->buffer()->append(message.c_str());
            _existingCode->buffer()->append("\n");
            // Scroll to bottom
            _existingCode->scroll(_existingCode->count_lines(
                                      0, _existingCode->buffer()->length(), 1),
                                  0);
        }

      protected:
        FLTKConsole *_console;
    };

    void FLTKConsole::setup(int &argc, char *argv[]) {
        Fl::args(argc, argv);
        Fl::get_system_colors();
    }

    FLTKConsole::FLTKConsole() : LuaConsole() {
        _view = boost::make_shared<FLTKConsoleView>(this);
    }

    FLTKConsole::FLTKConsole(LuaScript const &script) : LuaConsole(script) {
        _view = boost::make_shared<FLTKConsoleView>(this);
    }

    FLTKConsole::~FLTKConsole() {}

    namespace {
        void reportRunning(void *data) {
            RunLoopManager &run_ = *static_cast<RunLoopManager *>(data);
            run_.reportRunning();
        }
    }

    bool FLTKConsole::threadLoop() {
        {
            LoopGuard guard(run_, LoopGuard::DELAY_REPORTING_START);
            Fl::add_timeout(0, &reportRunning, static_cast<void *>(&run_));
            while (run_.shouldContinue() &&
                   vrj::Kernel::instance()->isRunning()) {
                // Do the FLTK loop
                bool ret = _doThreadWork();
                if (!ret) {
                    // Exit originating from FLTK
                    break;
                }
            }
        }
        vrj::Kernel::instance()->stop();
        vrj::Kernel::instance()->waitForKernelStop();
        return true;
    }

    void FLTKConsole::stopThread() { run_.signalAndWaitForShutdown(); }

    void FLTKConsole::appendToDisplay(std::string const &message) {
        _view->appendToDisplay(message);
    }

    void FLTKConsole::setTitle(std::string const &title) {
        _view->copy_label(title.c_str());
    }

    void FLTKConsole::disableAction() {
        VRJLUA_MSG_START(dbgVRJLUA_CONSOLE, MSG_STATUS)
            << "FLTKConsole::disableAction called but not implemented!!!"
            << VRJLUA_MSG_END(dbgVRJLUA_CONSOLE, MSG_STATUS);
    }

    bool FLTKConsole::_doThreadWork() {
        return ((Fl::wait(1.0 / 60.0) >= 0) && (Fl::first_window() != NULL));
    }

} // end of vrjLua namespace
