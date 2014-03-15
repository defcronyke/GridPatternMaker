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
 * Frontend.cpp
 *
 * Created on: Feb 27, 2014
 *     Author: Jeremy Carter
 *      Email: Jeremy [at] JeremyCarter [dot] ca
 */
#include "Frontend.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <SDL_image.h>
#include "Grid.hpp"

namespace jc_gridpatternmaker
{

Frontend::Frontend(Grid& grid)
 : grid(grid),
   w(grid.squares.at(0).size() * (grid.squares.at(0).at(0).w) + grid.outer_padding * 2 + grid.inner_padding),
   h(grid.squares.size() * (grid.squares.at(0).at(0).h) + grid.outer_padding * 2 + grid.inner_padding),
   sdl_window(0), sdl_renderer(0), sdl_bg_surface(0), sdl_bg_texture(0),
   sdl_sq1_surface(0), sdl_sq1_texture(0), sdl_sq2_surface(0), sdl_sq2_texture(0),
   sdl_sq3_surface(0), sdl_sq3_texture(0), sdl_sq4_surface(0), sdl_sq4_texture(0),
   sdl_sq5_surface(0), sdl_sq5_texture(0), sdl_sq6_surface(0), sdl_sq6_texture(0),
   sdl_hln_surface(0), sdl_hln_texture(0),
   sdl_vln_surface(0), sdl_vln_texture(0),
   mouse_down(false)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}
}

Frontend::~Frontend()
{
	if (sdl_vln_texture != nullptr) SDL_DestroyTexture(sdl_vln_texture);
	if (sdl_hln_texture != nullptr) SDL_DestroyTexture(sdl_hln_texture);
	if (sdl_sq1_texture != nullptr) SDL_DestroyTexture(sdl_sq1_texture);
	if (sdl_sq2_texture != nullptr) SDL_DestroyTexture(sdl_sq2_texture);
	if (sdl_sq3_texture != nullptr) SDL_DestroyTexture(sdl_sq3_texture);
	if (sdl_sq4_texture != nullptr) SDL_DestroyTexture(sdl_sq4_texture);
	if (sdl_sq5_texture != nullptr) SDL_DestroyTexture(sdl_sq5_texture);
	if (sdl_sq6_texture != nullptr) SDL_DestroyTexture(sdl_sq6_texture);
	if (sdl_bg_texture != nullptr) SDL_DestroyTexture(sdl_bg_texture);
	if (sdl_renderer != nullptr) SDL_DestroyRenderer(sdl_renderer);
	if (sdl_window != nullptr) SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Frontend::operator()()
{
	if (sdl_vln_texture != nullptr) SDL_DestroyTexture(sdl_vln_texture);
	if (sdl_hln_texture != nullptr) SDL_DestroyTexture(sdl_hln_texture);
	if (sdl_sq1_texture != nullptr) SDL_DestroyTexture(sdl_sq1_texture);
	if (sdl_sq2_texture != nullptr) SDL_DestroyTexture(sdl_sq2_texture);
	if (sdl_sq3_texture != nullptr) SDL_DestroyTexture(sdl_sq3_texture);
	if (sdl_sq4_texture != nullptr) SDL_DestroyTexture(sdl_sq4_texture);
	if (sdl_sq5_texture != nullptr) SDL_DestroyTexture(sdl_sq5_texture);
	if (sdl_sq6_texture != nullptr) SDL_DestroyTexture(sdl_sq6_texture);
	if (sdl_bg_texture != nullptr) SDL_DestroyTexture(sdl_bg_texture);
	if (sdl_renderer != nullptr) SDL_DestroyRenderer(sdl_renderer);
	if (sdl_window != nullptr) SDL_DestroyWindow(sdl_window);

	w = grid.squares.at(0).size() * (grid.squares.at(0).at(0).w) + grid.outer_padding * 2 + grid.inner_padding;
    h = grid.squares.size() * (grid.squares.at(0).at(0).h) + grid.outer_padding * 2 + grid.inner_padding;

	sdl_window = SDL_CreateWindow(("GridPatternMaker " + version_str).c_str(), 100, 100, w, h, SDL_WINDOW_SHOWN);
	if (sdl_window == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (sdl_renderer == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_bg_surface = IMG_Load("res/bg.png");
	if (sdl_bg_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_bg_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_bg_surface);
	SDL_FreeSurface(sdl_bg_surface);
	if (sdl_bg_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq1_surface = IMG_Load("res/sq1.png");
	if (sdl_sq1_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq1_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_sq1_surface);
	SDL_FreeSurface(sdl_sq1_surface);
	if (sdl_sq1_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq2_surface = IMG_Load("res/sq2.png");
	if (sdl_sq2_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq2_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_sq2_surface);
	SDL_FreeSurface(sdl_sq2_surface);
	if (sdl_sq2_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq3_surface = IMG_Load("res/sq3.png");
	if (sdl_sq3_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq3_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_sq3_surface);
	SDL_FreeSurface(sdl_sq3_surface);
	if (sdl_sq3_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq4_surface = IMG_Load("res/sq4.png");
	if (sdl_sq4_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq4_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_sq4_surface);
	SDL_FreeSurface(sdl_sq4_surface);
	if (sdl_sq4_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq5_surface = IMG_Load("res/sq5.png");
	if (sdl_sq5_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq5_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_sq5_surface);
	SDL_FreeSurface(sdl_sq5_surface);
	if (sdl_sq5_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq6_surface = IMG_Load("res/sq6.png");
	if (sdl_sq6_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_sq6_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_sq6_surface);
	SDL_FreeSurface(sdl_sq6_surface);
	if (sdl_sq6_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_hln_surface = IMG_Load("res/ln1.png");
	if (sdl_hln_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_hln_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_hln_surface);
	SDL_FreeSurface(sdl_hln_surface);
	if (sdl_hln_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_vln_surface = IMG_Load("res/ln1.png");
	if (sdl_vln_surface == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}

	sdl_vln_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_vln_surface);
	SDL_FreeSurface(sdl_vln_surface);
	if (sdl_vln_texture == nullptr)
	{
		std::cerr << "SDL Error: " << SDL_GetError() << "\n";
		return;
	}
}

void Frontend::display()
{
	SDL_RenderClear(sdl_renderer);

	SDL_Rect background_rect;
	background_rect.x = background_rect.y = 0;
	background_rect.w = w;
	background_rect.h = h;
	SDL_RenderCopy(sdl_renderer, sdl_bg_texture, 0, &background_rect);

	for (auto& row : grid.squares)
	{
		for (auto& column : row)
		{
			if (column.visible)
			{
				SDL_Rect sq_rect;
				sq_rect.x = column.x;
				sq_rect.y = column.y;
				sq_rect.w = column.w;
				sq_rect.h = column.h;
				SDL_Texture* square_tex = 0;

				if (column.c.colour_num == 1)
					square_tex = sdl_sq1_texture;
				else if (column.c.colour_num == 2)
					square_tex = sdl_sq2_texture;
				else if (column.c.colour_num == 3)
					square_tex = sdl_sq3_texture;
				else if (column.c.colour_num == 4)
					square_tex = sdl_sq4_texture;
				else if (column.c.colour_num == 5)
					square_tex = sdl_sq5_texture;
				else if (column.c.colour_num == 6)
					square_tex = sdl_sq6_texture;


				SDL_RenderCopy(sdl_renderer, square_tex, 0, &sq_rect);
			}
		}
	}

	SDL_Rect hln_rect;
	hln_rect.x = grid.outer_padding;
	hln_rect.y = grid.outer_padding;
	hln_rect.w = (grid.squares.at(0).at(0).w) * grid.squares.at(0).size() + grid.inner_padding;
	hln_rect.h = grid.inner_padding;
	SDL_RenderCopy(sdl_renderer, sdl_hln_texture, 0, &hln_rect);
	for (auto& row : grid.squares)
	{
		hln_rect.y += row.at(0).h;
		SDL_RenderCopy(sdl_renderer, sdl_hln_texture, 0, &hln_rect);
	}

	SDL_Rect vln_rect;
	vln_rect.x = grid.outer_padding;
	vln_rect.y = grid.outer_padding;
	vln_rect.w = grid.inner_padding;
	vln_rect.h = (grid.squares.at(0).at(0).h) * grid.squares.size();
	SDL_RenderCopy(sdl_renderer, sdl_vln_texture, 0, &vln_rect);
	for (auto& col : grid.squares.at(0))
	{
		vln_rect.x += col.w;
		SDL_RenderCopy(sdl_renderer, sdl_vln_texture, 0, &vln_rect);
	}

	SDL_RenderPresent(sdl_renderer);
}

unsigned long long Frontend::handle_events(int& selected_colour)
{
	unsigned long long event_out = 0;

	while (SDL_PollEvent(&sdl_event))
	{
		switch(sdl_event.type)
		{
		case SDL_QUIT:
			event_out = 1;

			break;

		case SDL_KEYDOWN:

			break;

		case SDL_KEYUP:

			if (sdl_event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				event_out = 1;

			break;

		default:
			break;
		}

		int x = 0;
		int y = 0;
		if ((!mouse_down) && (SDL_GetMouseState(&x, &y) & SDL_BUTTON(1))) // If left mouse button pressed, toggle square visibility.
		{
			mouse_down = true;

			unsigned int row_num = 0;
			for (auto& row : grid.squares)
			{
				unsigned int col_num = 0;
				for (auto& col : row)
				{
					if ((x >= col.x) && (x <= col.x + col.w) && (y >= col.y) && (y <= col.y + col.h))
					{
						if (col.c.colour_num == selected_colour || !col.visible)
							col.visible = !col.visible;

						col.c.colour_num = selected_colour;

						std::cout << "Toggled visibility: (" << col_num+1 << "," << row_num+1 << ")" << std::endl;
					}
					col_num++;
				}
				row_num++;
			}
		}
		else if ((!mouse_down) && (SDL_GetMouseState(&x, &y) & SDL_BUTTON(3))) // If right mouse butten pressed, cycle through colours.
		{
			mouse_down = true;
			unsigned int row_num = 0;
			for (auto& row : grid.squares)
			{
				unsigned int col_num = 0;
				for (auto& col : row)
				{
					if ((x >= col.x) && (x <= col.x + col.w) && (y >= col.y) && (y <= col.y + col.h))
					{
						col.c.colour_num = selected_colour % 6 + 1;

						if (!col.visible)
							col.visible = true;

						selected_colour = col.c.colour_num;

						std::cout << "Changed square to colour " << col.c.colour_num << ": (" << col_num+1 << "," << row_num+1 << ")" << std::endl;
					}
					col_num++;
				}
				row_num++;
			}
		}
		else if (!(SDL_GetMouseState(&x, &y) & SDL_BUTTON(1)) && !(SDL_GetMouseState(&x, &y) & SDL_BUTTON(3)))
		{
			mouse_down = false;
		}

		return event_out;
	}

	return event_out;
}

void Frontend::resize(unsigned int w, unsigned h)
{
	this->w = w;
	this->h = h;
	SDL_SetWindowSize(sdl_window, w, h);
}

bool Frontend::load_file(const std::string& file, Grid& grid)
{
	std::string line;
	std::ifstream filestream(file.c_str());
	bool first_line = true;
	unsigned int num_rows = 0;
	unsigned int num_cols = 0;

	if (filestream.is_open())
	{
		bool first_line = true;
		while (getline(filestream, line))
		{
			if (first_line)
			{
				first_line = false;
				num_cols = line.length();
			}
			else
			{
				if (line.length() != num_cols)
				{
					std::cerr << "File Error: " << file << " wrong number of columns on line: " << num_rows+1 << "\n";
					return false;
				}
			}
			num_rows++;
		}
		filestream.close();
	}

	grid.resize_rows(num_cols);
	grid.resize_cols(num_rows);

	unsigned int w_pix = grid.squares.at(0).size() * (grid.squares.at(0).at(0).w) + grid.outer_padding * 2 + grid.inner_padding;
	unsigned int h_pix = grid.squares.size() * (grid.squares.at(0).at(0).h) + grid.outer_padding * 2 + grid.inner_padding;

	resize(w_pix, h_pix);

	filestream.open(file.c_str());
	if (filestream.is_open())
	{
		unsigned int row = 0;
		while (getline(filestream, line))
		{
			unsigned int col = 0;
			for (auto& ch : line)
			{
				unsigned int num = line.at(col) - '0';

				if (num > 0)
				{
					grid.squares.at(row).at(col).visible = true;
					grid.squares.at(row).at(col).c.colour_num = num;
				}
				else if (num == 0)
				{
					grid.squares.at(row).at(col).visible = false;
				}
				col++;
			}
			row++;
		}
		filestream.close();
	}
	this->file = file;

	return true;
}

std::string Frontend::grid_str()
{
	std::string grid_string;

	unsigned int row_num = 0;
	for (auto& row : grid.squares)
	{
		unsigned int col_num = 0;
		for (auto& col : row)
		{
			if (!col.visible)
				grid_string += "0";
			else
			{
				std::stringstream to_string;
				to_string << col.c.colour_num;
				grid_string += to_string.str();
			}

			col_num++;
		}
		grid_string += "\n";
		row_num++;
	}

	return grid_string;
}

}
