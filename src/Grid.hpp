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
 * Grid.hpp
 *
 * Created on: Feb 27, 2014
 *     Author: Jeremy Carter
 *      Email: Jeremy [at] JeremyCarter [dot] ca
 */

#ifndef __DEFCRONYKE__GRID_HPP__INCLUDED__
#define __DEFCRONYKE__GRID_HPP__INCLUDED__

#include <utility>
#include <vector>

namespace jc_gridpatternmaker
{

class Colour
{
public:
	Colour(float r = 1.f, float g = 1.f, float b = 1.f, float a = 1.f)
	 : r(r), g(g), b(b), a(a), colour_num(1){}
	~Colour(){}
	float r, g, b, a; // Unused
	unsigned int colour_num;
};

class Square
{
public:
	Square(float x = 0, float y = 0, float w = 20.f, float h = 20.f, Colour c = Colour(), bool visible = false)
	 : x(x), y(y), w(w), h(h), c(c), visible(visible){}
	~Square(){}

	float x, y, w, h;
	Colour c;
	bool visible;
};

typedef std::vector<std::vector<Square> > GridDataArray;

class Grid
{
public:
	Grid(unsigned int rows = 10, unsigned int cols = 10)
 	 : outer_padding(10.f), inner_padding(1.f), rows(rows), cols(cols)
	{
		operator()();
	}

	virtual ~Grid(){}

	virtual void operator()()
	{
		float sq_xpos = outer_padding;
		float sq_ypos = outer_padding;

		for (unsigned int row = 0; row < rows; ++row)
		{
			std::vector<Square> row_data;
			for (unsigned int col = 0; col < cols; ++col)
			{
				row_data.push_back(Square(sq_xpos, sq_ypos));
				sq_xpos += row_data.at(0).w;
			}
			squares.push_back(row_data);
			sq_xpos = outer_padding;
			sq_ypos += squares.at(0).at(0).h;
		}
	}

	virtual void resize_rows(unsigned int new_rowsize)
	{
		for (auto& row : squares)
		{
			if (new_rowsize > row.size())
			{
				unsigned int num_new_cols = new_rowsize - row.size();

				float sq_xpos = row.at(row.size()-1).x + row.at(row.size()-1).w;
				float sq_ypos = row.at(row.size()-1).y;

				for (unsigned int new_col_num = 0; new_col_num < num_new_cols; ++new_col_num)
				{
					row.push_back(Square(sq_xpos, sq_ypos));
					sq_xpos += row.at(0).w;
				}
			}
			else if (new_rowsize < row.size())
			{
				row.resize(new_rowsize);
			}
		}
		cols = new_rowsize;
	}

	virtual void resize_cols(unsigned int new_colsize)
	{
		unsigned int num_new_rows = new_colsize - squares.size();

		if (new_colsize > squares.size())
		{
			float sq_xpos = squares.at(squares.size()-1).at(0).x;
			float sq_ypos = squares.at(squares.size()-1).at(0).y + squares.at(squares.size()-1).at(0).h;

			for (unsigned int new_row_num = 0; new_row_num < num_new_rows; ++new_row_num)
			{
				std::vector<Square> row_data;
				for (unsigned int col_num = 0; col_num < squares.at(0).size(); ++col_num)
				{
					row_data.push_back(Square(sq_xpos, sq_ypos));
					sq_xpos += squares.at(0).at(0).w;
				}
				squares.push_back(row_data);
				sq_xpos = squares.at(0).at(0).x;
				sq_ypos += squares.at(squares.size()-1).at(0).h;
			}
		}
		else if (new_colsize < squares.size())
		{
			squares.resize(new_colsize);
		}
		rows = new_colsize;
	}

	float outer_padding;
	float inner_padding;

	GridDataArray squares;
	unsigned int rows, cols;
};

}
#endif
