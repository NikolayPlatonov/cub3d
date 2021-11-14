#import <AppKit/NSScreen.h>

void	mlx_get_screen_size(int *width, int *height)
{
	NSRect display = [[NSScreen mainScreen] frame];
	*height = (int)display.size.height;
	*width = (int)display.size.width;
}