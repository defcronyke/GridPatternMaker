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
 * Frontend.hpp
 *
 * Created on: Feb 27, 2014
 *     Author: Jeremy Carter
 *      Email: Jeremy [at] JeremyCarter [dot] ca
 */

// This is the SDL portion of the frontend.

#ifndef __DEFCRONYKE__FRONTEND_HPP__INCLUDED__
#define __DEFCRONYKE__FRONTEND_HPP__INCLUDED__

#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <string>
#include "Grid.hpp"

namespace jc_gridpatternmaker
{

static const std::string version_str = "v1.0.0";

static const std::string license_shorttext =
	"GridPatternMaker " + version_str + " | Make a coloured grid pattern.\n"
	"Copyright (C) 2014 Jeremy Carter (Jeremy@JeremyCarter.ca)\n\n"
	"This program is free software: you can redistribute it and/or modify it\n"
	"under the terms of the GNU General Public License as published by the\n"
	"Free Software Foundation, either version 3 of the License, or (at your\n"
	"option) any later version.\n\n"
	"This program is distributed in the hope that it will be useful, but\n"
	"WITHOUT ANY WARRANTY; without even the implied warranty of\n"
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU \n"
	"General Public License for more details.\n\n"
	"You should have received a copy of the GNU General Public License along\n"
	"with this program. If not, see <http://www.gnu.org/licenses/>.\n";
static const std::string license_gui_shorttext =
	"GridPatternMaker " + version_str + " | Make a coloured grid pattern.\n"
	"Copyright (C) 2014 Jeremy Carter (Jeremy@JeremyCarter.ca)\n\n"
	"This program is free software: you can redistribute it and/or modify "
	"it under the terms of the GNU General Public License as published by "
	"the Free Software Foundation, either version 3 of the License, or "
	"(at your option) any later version.\n\n"
	"This program is distributed in the hope that it will be useful, "
	"but WITHOUT ANY WARRANTY; without even the implied warranty of "
	"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the "
	"GNU General Public License for more details.\n\n"
	"You should have received a copy of the GNU General Public License "
	"along with this program.  If not, see\n"
	"<http://www.gnu.org/licenses/>.\n";

class Frontend
{
public:
	Frontend(Grid& grid);
	virtual ~Frontend();

	virtual void operator()();
	virtual void display();
	virtual unsigned long long handle_events(int& selected_colour);
	virtual void resize(unsigned int w, unsigned h);
	virtual bool load_file(const std::string& file, Grid& grid);
	virtual std::string grid_str();

	Grid& grid;
	unsigned int w, h;
	SDL_Window* sdl_window;
	SDL_Renderer* sdl_renderer;
	SDL_Surface* sdl_bg_surface;
	SDL_Texture* sdl_bg_texture;
	SDL_Surface* sdl_sq1_surface;
	SDL_Texture* sdl_sq1_texture;
	SDL_Surface* sdl_sq2_surface;
	SDL_Texture* sdl_sq2_texture;
	SDL_Surface* sdl_sq3_surface;
	SDL_Texture* sdl_sq3_texture;
	SDL_Surface* sdl_sq4_surface;
	SDL_Texture* sdl_sq4_texture;
	SDL_Surface* sdl_sq5_surface;
	SDL_Texture* sdl_sq5_texture;
	SDL_Surface* sdl_sq6_surface;
	SDL_Texture* sdl_sq6_texture;
	SDL_Surface* sdl_hln_surface;
	SDL_Texture* sdl_hln_texture;
	SDL_Surface* sdl_vln_surface;
	SDL_Texture* sdl_vln_texture;
	SDL_Event sdl_event;
	bool mouse_down;
	std::string file;
};

}
#endif
