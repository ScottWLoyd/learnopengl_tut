
static const char* read_entire_file(const char* file, bool binary)
{
	if (!file)
	{
		return NULL;
	}

	const char* mode = binary ? "rb" : "r";
	FILE* f = fopen(file, mode);
	if (!f)
	{
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	long len = ftell(f);
	rewind(f);

	char* buf = (char*)malloc(len);
	size_t bytes_read = fread(buf, 1, len, f);
	fclose(f);
	buf[bytes_read] = 0;
	return (const char*)buf;
}