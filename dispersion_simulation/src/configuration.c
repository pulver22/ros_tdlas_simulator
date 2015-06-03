#include "configuration.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void configuration_init() {
	configuration.log_usage = 0;
}

void configuration_parse_commandline(int argc, char **argv) {
	int i;
	for (i = 0; i < argc; i++) {
		if (strstr(argv[i], "=")) {
			putenv(argv[i]);
		}
	}

	configuration.log_usage = configuration_get_bool("INFOTAXIS_CONFIGURATION_LOG_USAGE", configuration.log_usage);
}

const char *configuration_get_string(const char *name, const char *default_value) {
	if (configuration.log_usage) {
		printf("$CONFIGURATION_USAGE,string,%s,%s\n", name, default_value);
	}

	const char *value = getenv(name);
	return (value ? value : default_value);
}

int configuration_get_int(const char *name, int default_value) {
	if (configuration.log_usage) {
		printf("$CONFIGURATION_USAGE,int,%s,%d\n", name, default_value);
	}

	const char *str = getenv(name);
	if (! str) {
		return default_value;
	}
	return strtol(str, 0, 0);
}

int configuration_get_bool(const char *name, int default_value) {
	if (configuration.log_usage) {
		printf("$CONFIGURATION_USAGE,bool,%s,%d\n", name, default_value);
	}

	const char *str = getenv(name);
	if (! str) {
		return default_value;
	}
	if (strcmp(str, "true") == 0) {
		return 1;
	}
	if (strcmp(str, "on") == 0) {
		return 1;
	}
	if (strcmp(str, "yes") == 0) {
		return 1;
	}
	return (strtol(str, 0, 0) != 0 ? 1 : 0);
}

double configuration_get_double(const char *name, double default_value) {
	if (configuration.log_usage) {
		printf("$CONFIGURATION_USAGE,double,%s,%f\n", name, default_value);
	}

	const char *str = getenv(name);
	if (! str) {
		return default_value;
	}
	return strtod(str, 0);
}

extern char **environ;
