/* Ⓒ Copyright 2014 Jeremy Carter
 *
 * This file is part of GridPatternMaker.
 *
 * GridPatternMaker is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3, as published 
 * by the Free Software Foundation.
 *
 * GridPatternMaker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GridPatternMaker. If not, see <http://www.gnu.org/licenses/gpl-3.0.txt>.
 *
 * wxCtrlsApp.hpp
 *
 * Created on: Mar 2, 2014
 *     Author: Jeremy Carter
 *      Email: Jeremy [at] JeremyCarter [dot] ca
 */

// This is the WxWidgets portion of the frontend. It also defines main() and runs the whole show.

#ifndef __DEFCRONYKE__WXCTRLSAPP_HPP__INCLUDED__
#define __DEFCRONYKE__WXCTRLSAPP_HPP__INCLUDED__

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>
#include "Frontend.hpp"
#include "Grid.hpp"

using namespace jc_gridpatternmaker;

class wxCtrlsFrame : public wxFrame
{
public:
	wxCtrlsFrame(const wxString& title, const wxPoint& pos, wxSize& size,
		Frontend& frontend);
	virtual ~wxCtrlsFrame();

	int selected_colour;

private:
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void SaveAs(wxCommandEvent& event);
	void Load(wxCommandEvent& event);
	void Clear(wxCommandEvent& event);
	void AddRow(wxCommandEvent& event);
	void RemRow(wxCommandEvent& event);
	void AddCol(wxCommandEvent& event);
	void RemCol(wxCommandEvent& event);
	void Colour1(wxCommandEvent& event);
	void Colour2(wxCommandEvent& event);
	void Colour3(wxCommandEvent& event);
	void Colour4(wxCommandEvent& event);
	void Colour5(wxCommandEvent& event);
	void Colour6(wxCommandEvent& event);

	Frontend& frontend;
	wxMenu* menu_file;
	wxMenu* menu_help;
	wxMenuBar* menu_bar;
	wxToolBar* toolbar;

	wxDECLARE_EVENT_TABLE();
};

class wxCtrlsApp : public wxApp
{
	Grid grid;
	Frontend frontend;

public:
	wxCtrlsApp();
	virtual ~wxCtrlsApp();
	virtual bool OnInit();
	void OnIdle(wxIdleEvent& event);

	bool rendering, handling_events, first_run;
	wxCtrlsFrame* frame;
};

enum
{
	ID_Idle = 1,
	ID_SaveAs,
	ID_Load,
	ID_Clear,
	ID_AddRow,
	ID_RemRow,
	ID_AddCol,
	ID_RemCol,
	ID_Colour1,
	ID_Colour2,
	ID_Colour3,
	ID_Colour4,
	ID_Colour5,
	ID_Colour6,
};

wxBEGIN_EVENT_TABLE(wxCtrlsFrame, wxFrame)
	EVT_MENU(wxID_EXIT, wxCtrlsFrame::OnExit)
	EVT_MENU(wxID_ABOUT, wxCtrlsFrame::OnAbout)
	EVT_MENU(ID_SaveAs, wxCtrlsFrame::SaveAs)
	EVT_MENU(ID_Load, wxCtrlsFrame::Load)
	EVT_MENU(ID_Clear, wxCtrlsFrame::Clear)
	EVT_MENU(ID_AddRow, wxCtrlsFrame::AddRow)
	EVT_MENU(ID_RemRow, wxCtrlsFrame::RemRow)
	EVT_MENU(ID_AddCol, wxCtrlsFrame::AddCol)
	EVT_MENU(ID_RemCol, wxCtrlsFrame::RemCol)
	EVT_MENU(ID_Colour1, wxCtrlsFrame::Colour1)
	EVT_MENU(ID_Colour2, wxCtrlsFrame::Colour2)
	EVT_MENU(ID_Colour3, wxCtrlsFrame::Colour3)
	EVT_MENU(ID_Colour4, wxCtrlsFrame::Colour4)
	EVT_MENU(ID_Colour5, wxCtrlsFrame::Colour5)
	EVT_MENU(ID_Colour6, wxCtrlsFrame::Colour6)

wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(wxCtrlsApp);

#endif
