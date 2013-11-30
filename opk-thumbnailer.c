#include <string.h>
#include <stdio.h>
#include <opk.h>

int main (int argc, char **argv)
{
	struct OPK *opk;
	const char *metadata;
	void *data;
	size_t data_len;
	char icon[100];
	FILE *f;

	if (argc < 3) {
		printf("Usage: opk-thumbnailer input.opk output.png\n");
		return 1;
	}

	opk = opk_open(argv[1]);
	if (!opk) {
		fprintf(stderr, "Not an OPK file or file corrupted\n");
		return 1;
	}

	if (opk_open_metadata(opk, &metadata) < 1) {
		opk_close(opk);
		fprintf(stderr, "No valid metadata in OPK file\n");
		return 1;
	}

	for (;;) {
		const char *key, *val;
		size_t lkey, lval;

		if (opk_read_pair(opk, &key, &lkey, &val, &lval) < 1) {
			opk_close(opk);
			fprintf(stderr, "Icon path not found in metadata\n");
			return 1;
		}

		if (!strncmp(key, "Icon", lkey)) {
			sprintf(icon, "%.*s", (int) lval, val);
			strcat(icon, ".png");
			break;
		}
	}

	if (opk_extract_file(opk, icon, &data, &data_len)) {
		opk_close(opk);
		fprintf(stderr, "Unable to extract icon file\n");
		return 1;
	}

	opk_close(opk);

	f = fopen(argv[2], "w");
	fwrite(data, data_len, 1, f);
	fclose(f);
	free(data);
	return 0;
}
