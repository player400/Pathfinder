#pragma once

#define TOWN_SYMBOL '*'
#define PATH_SYMBOL '#'
#define FIELD_SYMBOL '.'

class Input
{
private:
	char** map = nullptr;
	Coords map_size;

	static bool is_letter(char symbol)
	{
		if (symbol != TOWN_SYMBOL && symbol != PATH_SYMBOL && symbol != FIELD_SYMBOL)
		{
			return true;
		}
		return false;
	}

	bool is_first_letter(Coords position)
	{
		Coords left = position;
		left.width -= 1;
		if (is_letter(map[position.height][position.width]))
		{
			if (left.width >= 0 && is_letter(map[left.height][left.width]))
			{
				return false;
			}
			return true;
		}
		return false;
	}

	bool is_last_letter(Coords position)
	{
		Coords right = position;
		right.width += 1;
		if (is_letter(map[position.height][position.width]))
		{
			if (right.width < map_size.width && is_letter(map[right.height][right.width]))
			{
				return false;
			}
			return true;
		}
		return false;
	}

	bool is_first_or_last_letter(Coords position)
	{
		if (is_last_letter(position) || is_first_letter(position))
		{
			return true;
		}
		return false;
	}

public:
	Map* parse_map(TownGraph* graph, Map* parsed_map)
	{
		for (int i = 0; i < map_size.height; i++)
		{
			for (int j = 0; j < map_size.width; j++)
			{
				if (map[i][j] == FIELD_SYMBOL || is_letter(map[i][j]))
				{
					parsed_map->add_to_map(new Field({ i, j }));
				}
				else if (map[i][j] == PATH_SYMBOL)
				{
					parsed_map->add_to_map(new Path({ i, j }));
				}
				else
				{
					Town* new_town = new Town({ i, j });
					Coords position = { i - 1, j - 1 };
					Coords name_position;
					for (int a = 0; a < 3; a++)
					{
						for (int b = 0; b < 3; b++)
						{
							if (a == 1 && b == 1)
							{
								continue;
							}
							Coords neighbour = position;
							neighbour.height += a;
							neighbour.width += b;
							if ((neighbour.width >= 0 && neighbour.width < map_size.width) && (neighbour.height >= 0 && neighbour.height < map_size.height))
							{
								if (is_first_or_last_letter(neighbour))
								{
									name_position = neighbour;
									break;
								}
							}
						}
					}
					while (!(is_first_letter(name_position)))
					{
						name_position.width--;
					}
					while (true)
					{
						new_town->push_back_name(map[name_position.height][name_position.width]);
						if (is_last_letter(name_position))
						{
							break;
						}
						name_position.width++;
					}
					parsed_map->add_to_map(new_town);
					new_town->push_back_name('\0');
					graph->add_town(new_town);
					parsed_map->add_town(new_town);
				}
			}
		}
		return parsed_map;
	}

	void read_map()
	{
		for (int i = 0; i < map_size.height; i++)
		{
			for (int j = 0; j < map_size.width;)
			{
				char element = getchar();
				if (element != '\n')
				{
					map[i][j] = element;
					j++;
				}
			}
		}
	}

	Input(Coords size)
	{
		map_size = size;
		map = (char**)malloc(sizeof(char*) * size.height);
		for (int i = 0; i < size.height; i++)
		{
			map[i] = (char*)malloc(sizeof(char) * size.width);
		}
	}

	~Input()
	{
		for (int i = 0; i < map_size.height; i++)
		{
			free(map[i]);
		}
		free(map);
	}
};