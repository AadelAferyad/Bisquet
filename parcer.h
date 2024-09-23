#ifndef FT_PARCER
#define FT_PARCER
#include "bsq.h"


void	fill_map_fs_line(char *buffer, mp *map);
int	validate_map_fs_line(char *buffer, mp *map);
mp	*read_map_fs_line(int fd);
int	is_valid(mp *map, char *buffer, int *height, int rbytes);
int	validate_map(int fd, mp *map);

char	*allocate_map_in_buffer(int fd, int size, int start);
int	allocate_row(int fd, mp *map);
int	allocate_map(int fd, mp *map);
#endif
