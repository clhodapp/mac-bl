
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const static int num_settings = 8;

static FILE * fopen_or_fail(const char * path, const char * mode) {
	FILE * ret = fopen(path, mode);
	if (ret == NULL) {
		perror(path);
		exit(1);
	}
	return ret;
}

int main(int argc, char** argv) {

	char actual_str[25];
	char max_str[25];

	FILE* max_file = fopen_or_fail("/sys/class/backlight/gmux_backlight/max_brightness", "r");
	fgets(max_str, sizeof(max_str), max_file);
	fclose(max_file);

	long int max = atol(max_str);

	FILE* current_file = fopen_or_fail("/sys/class/backlight/gmux_backlight/brightness", "r");
	fgets(actual_str, sizeof(actual_str), current_file);
	fclose(current_file);

	long int actual = atol(actual_str);

	long long int * settings = malloc(num_settings * sizeof(long long int));

	for (int i = 0; i < num_settings; i++)
		settings[i] = i * max / (num_settings - 1);
	
	if (!strcmp(argv[0], "bl")) {
		printf("current brightness is %li\n", actual);
	} else {
		long long new_brightness;
		if (!strcmp(argv[0], "bm")) {
			int idx = 7;
			while (settings[idx] >= actual && idx > 0) idx--;
			new_brightness = settings[idx];
		} else {
			int idx = 0;
			while (settings[idx] <= actual && idx < 7) idx++;
			new_brightness = settings[idx];
		}

		printf("changing %li to %lli\n", actual, new_brightness);

		FILE * update_file = fopen_or_fail("/sys/class/backlight/gmux_backlight/brightness", "w");
		fprintf(update_file, "%lli\n", new_brightness);

		fclose(update_file);
	}

	return 0;

}
