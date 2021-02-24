#pragma once
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif


class Window : public wxFrame, public wxThreadHelper
{
	public:
		Window();
		~Window();
		
	public:
		void OnTimer(wxTimerEvent &);
		void OnBrowse(wxCommandEvent &);
		void OnMake(wxCommandEvent &);
		void OnMerge(wxCommandEvent &);
		void OnExit(wxCommandEvent &);
		void OnKeyDown(wxKeyEvent &);
		
		// Thread
		void OnThreadUpdate(wxThreadEvent &);
		void OnClose(wxCloseEvent &);
		
	protected:
		virtual wxThread::ExitCode Entry();
		
		// the output data of the Entry() routine:
		char m_data[1024];
		wxCriticalSection m_dataCS; // protects field above
		
		wxDECLARE_EVENT_TABLE();
		
	private:
		wxMenuBar
		*menubar;
		
		wxStaticText
		*text;
		
		wxButton
		*browse_button,
		*make_button,
		*merge_button;
		
		wxListBox
		*listbox;
		
		wxTimer
		*timer;
};
