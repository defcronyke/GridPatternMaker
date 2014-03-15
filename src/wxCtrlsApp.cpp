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
 * wxCtrlsApp.cpp
 *
 * Created on: Mar 2, 2014
 *     Author: Jeremy Carter
 *      Email: Jeremy [at] JeremyCarter [dot] ca
 */
#include "wxCtrlsApp.hpp"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/wfstream.h>

#include <iostream>
#include <SDL.h>
#include "Grid.hpp"

wxCtrlsFrame::wxCtrlsFrame(const wxString& title, const wxPoint& pos, wxSize& size,
	Frontend& frontend)
 : frontend(frontend), selected_colour(1), menu_file(0), menu_help(0), menu_bar(0), toolbar(0),
   wxFrame(0, wxID_ANY, title, pos, size)
{
	menu_file = new wxMenu;
	menu_file->Append(wxID_EXIT);

	menu_help = new wxMenu;
	menu_help->Append(wxID_ABOUT);

	menu_bar = new wxMenuBar;
	menu_bar->Append(menu_file, "&File");
	menu_bar->Append(menu_help, "&Help");

	SetMenuBar(menu_bar);

	wxImage::AddHandler(new wxPNGHandler);
	wxBitmap save_as(wxT("res/sa.png"), wxBITMAP_TYPE_PNG);
	wxBitmap load(wxT("res/load.png"), wxBITMAP_TYPE_PNG);
	wxBitmap clear(wxT("res/cl.png"), wxBITMAP_TYPE_PNG);
	wxBitmap add_row(wxT("res/addr.png"), wxBITMAP_TYPE_PNG);
	wxBitmap rem_row(wxT("res/remr.png"), wxBITMAP_TYPE_PNG);
	wxBitmap add_col(wxT("res/addc.png"), wxBITMAP_TYPE_PNG);
	wxBitmap rem_col(wxT("res/remc.png"), wxBITMAP_TYPE_PNG);
	wxBitmap colour1(wxT("res/colour1.png"), wxBITMAP_TYPE_PNG);
	wxBitmap colour2(wxT("res/colour2.png"), wxBITMAP_TYPE_PNG);
	wxBitmap colour3(wxT("res/colour3.png"), wxBITMAP_TYPE_PNG);
	wxBitmap colour4(wxT("res/colour4.png"), wxBITMAP_TYPE_PNG);
	wxBitmap colour5(wxT("res/colour5.png"), wxBITMAP_TYPE_PNG);
	wxBitmap colour6(wxT("res/colour6.png"), wxBITMAP_TYPE_PNG);

	toolbar = CreateToolBar();
	toolbar->AddTool(ID_SaveAs, wxT("Save As..."), save_as);
	toolbar->AddTool(ID_Load, wxT("Load File..."), load);
	toolbar->AddTool(ID_Clear, wxT("Clear Grid..."), clear);
	toolbar->AddTool(ID_AddRow, wxT("Add Row"), add_row);
	toolbar->AddTool(ID_RemRow, wxT("Remove Row"), rem_row);
	toolbar->AddTool(ID_AddCol, wxT("Add Column"), add_col);
	toolbar->AddTool(ID_RemCol, wxT("Remove Column"), rem_col);
	toolbar->AddTool(ID_Colour1, wxT("Colour1"), colour1);
	toolbar->AddTool(ID_Colour2, wxT("Colour2"), colour2);
	toolbar->AddTool(ID_Colour3, wxT("Colour3"), colour3);
	toolbar->AddTool(ID_Colour4, wxT("Colour4"), colour4);
	toolbar->AddTool(ID_Colour5, wxT("Colour5"), colour5);
	toolbar->AddTool(ID_Colour6, wxT("Colour6"), colour6);
	toolbar->Realize();

	Connect(ID_SaveAs, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::SaveAs));
	Connect(ID_Load, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Load));
	Connect(ID_Clear, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Clear));
	Connect(ID_AddRow, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::AddRow));
	Connect(ID_RemRow, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::RemRow));
	Connect(ID_AddCol, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::AddCol));
	Connect(ID_RemCol, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::RemCol));
	Connect(ID_Colour1, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour1));
	Connect(ID_Colour2, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour2));
	Connect(ID_Colour3, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour3));
	Connect(ID_Colour4, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour4));
	Connect(ID_Colour5, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour5));
	Connect(ID_Colour6, wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour6));

	CreateStatusBar();
	SetStatusText("Copyright 2014 Jeremy Carter (Jeremy@JeremyCarter.ca)");
}

wxCtrlsFrame::~wxCtrlsFrame()
{
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::SaveAs));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Load));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Clear));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::AddRow));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::RemRow));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::AddCol));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::RemCol));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour1));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour2));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour3));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour4));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour5));
	Disconnect(wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(wxCtrlsFrame::Colour6));

	toolbar->Close();
	menu_bar->Close();
	this->Close();
}

void wxCtrlsFrame::OnExit(wxCommandEvent& event)
{
	wxCtrlsFrame::Close(true);
}

void wxCtrlsFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a maker for grid patterns. It may be useful for knitting designs or other.\n\n" + license_gui_shorttext,
		"About GridPatternMaker", wxOK | wxICON_INFORMATION);
}

void wxCtrlsFrame::SaveAs(wxCommandEvent& event)
{
	wxFileDialog save_file_dialog(this, _("Save GPM file"), "", "",
		"GPM files (*.gpm)|*.gpm", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);

	if (save_file_dialog.ShowModal() == wxID_CANCEL)
		return;

	wxFileOutputStream output_stream(save_file_dialog.GetPath());
	if (!output_stream.IsOk())
	{
		wxLogError("Cannot save file '%s'.", save_file_dialog.GetPath());
		return;
	}

	std::string text = frontend.grid_str();
	output_stream.WriteAll(text.c_str(), text.size());
}

void wxCtrlsFrame::Load(wxCommandEvent& event)
{
	wxFileDialog load_file_dialog(this, _("Load GPM file"), "", "",
			"GPM files (*.gpm)|*.gpm", 0);

	if (load_file_dialog.ShowModal() == wxID_CANCEL)
		return;

	std::string filename = load_file_dialog.GetPath().ToStdString();

	frontend.load_file(filename, frontend.grid);
	frontend();

	int x, y;
	SDL_GetWindowPosition(frontend.sdl_window, &x, &y);
	wxPoint point(x, frontend.h + 140);
	Move(point);
}

void wxCtrlsFrame::Clear(wxCommandEvent& event)
{
	wxMessageDialog are_you_sure(this, _("Are you sure you'd like to clear the grid?"), _("Are you sure?"), wxCENTRE | wxYES_NO);
	int response = are_you_sure.ShowModal();

	if (response == wxID_YES)
	{
		for (auto& row : frontend.grid.squares)
		{
			for (auto& square : row)
			{
				square.visible = false;
				square.c.colour_num = 1;
			}
		}
		std::cout << "Grid cleared." << std::endl;
	}
}

void wxCtrlsFrame::AddRow(wxCommandEvent& event)
{
	frontend.grid.resize_cols(frontend.grid.rows+1);
	frontend.resize(frontend.w, frontend.h + frontend.grid.squares.at(0).at(0).h);

	int x, y;
	SDL_GetWindowPosition(frontend.sdl_window, &x, &y);
	wxPoint point(x, y + frontend.h + frontend.grid.squares.at(0).at(0).h + (frontend.grid.outer_padding*2));
	Move(point);
	std::cout << "Added a row (" << frontend.grid.cols << "x" << frontend.grid.rows << ")" << std::endl;
}

void wxCtrlsFrame::RemRow(wxCommandEvent& event)
{
	if (frontend.grid.rows > 1)
	{
		frontend.grid.resize_cols(frontend.grid.rows-1);
		frontend.resize(frontend.w, frontend.h - frontend.grid.squares.at(0).at(0).h);
		int x, y;
		SDL_GetWindowPosition(frontend.sdl_window, &x, &y);
		wxPoint point(x, (y + frontend.h + (frontend.grid.outer_padding*6)) - frontend.grid.squares.at(0).at(0).h);
		Move(point);
		std::cout << "Removed a row (" << frontend.grid.cols << "x" << frontend.grid.rows << ")" << std::endl;
	}
	else
	{
		std::cout << "You can't remove any more rows." << std::endl;
	}
}

void wxCtrlsFrame::AddCol(wxCommandEvent& event)
{
	frontend.grid.resize_rows(frontend.grid.cols+1);
	frontend.resize(frontend.w + frontend.grid.squares.at(0).at(0).w, frontend.h);
	int x, y;
	SDL_GetWindowPosition(frontend.sdl_window, &x, &y);
	wxPoint point(x, y + frontend.h + frontend.grid.outer_padding * 4);
	Move(point);
	std::cout << "Added a column (" << frontend.grid.cols << "x" << frontend.grid.rows << ")" << std::endl;
}

void wxCtrlsFrame::RemCol(wxCommandEvent& event)
{
	if (frontend.grid.cols > 1)
	{
		frontend.grid.resize_rows(frontend.grid.cols-1);
		frontend.resize(frontend.w - frontend.grid.squares.at(0).at(0).w, frontend.h);
		int x, y;
		SDL_GetWindowPosition(frontend.sdl_window, &x, &y);
		wxPoint point(x, y + frontend.h + frontend.grid.outer_padding * 4);
		Move(point);
		std::cout << "Removed a column (" << frontend.grid.cols << "x" << frontend.grid.rows << ")" << std::endl;
	}
	else
	{
		std::cout << "You can't remove any more columns." << std::endl;
	}
}

void wxCtrlsFrame::Colour1(wxCommandEvent& event)
{
	selected_colour = 1;
}

void wxCtrlsFrame::Colour2(wxCommandEvent& event)
{
	selected_colour = 2;
}

void wxCtrlsFrame::Colour3(wxCommandEvent& event)
{
	selected_colour = 3;
}

void wxCtrlsFrame::Colour4(wxCommandEvent& event)
{
	selected_colour = 4;
}

void wxCtrlsFrame::Colour5(wxCommandEvent& event)
{
	selected_colour = 5;
}

void wxCtrlsFrame::Colour6(wxCommandEvent& event)
{
	selected_colour = 6;
}


wxCtrlsApp::wxCtrlsApp()
 : wxApp(), frontend(grid), rendering(false), handling_events(false), first_run(true), frame(0)
{
}

wxCtrlsApp::~wxCtrlsApp()
{
	Disconnect(wxEVT_IDLE, wxIdleEventHandler(wxCtrlsApp::OnIdle));
	std::cout << "\nGoodbye." << std::endl;
}

bool wxCtrlsApp::OnInit()
{
	if (argc == 3)
	{
		grid.resize_rows(std::atoi(argv[1].c_str()));
		grid.resize_cols(std::atoi(argv[2].c_str()));
	}
	else if (argc == 2)
	{
		bool success = frontend.load_file(std::string(argv[1].c_str()), grid);
		if (!success) return 1;
	}

	frontend();

	wxPoint point(100, frontend.h + 140);
	wxSize size(460,130);

	frame = new wxCtrlsFrame(_("GridPatternMaker " + version_str), point, size, frontend);

	std::cout << license_shorttext << std::endl;

	std::cout << "Dimensions: " << grid.cols << "x" << grid.rows << std::endl;

	frame->Show(true);

	rendering = true;
	handling_events = true;

	Connect(wxID_ANY, wxEVT_IDLE, wxIdleEventHandler(wxCtrlsApp::OnIdle));

	return true;
}

void wxCtrlsApp::OnIdle(wxIdleEvent& event)
{
	if (!rendering && !handling_events)
	{
		Disconnect(wxEVT_IDLE, wxIdleEventHandler(wxCtrlsApp::OnIdle));
	}
	else
	{
		frontend.display();

		unsigned long long sdl_event = frontend.handle_events(frame->selected_colour);

		if (sdl_event == 1)
		{
			rendering = handling_events = false;
			ExitMainLoop();
			return;
		}

		event.RequestMore();
	}
}
