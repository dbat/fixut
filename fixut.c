#include <conio.h>
#include <tchar.h>
#include "windows.h"
#include <stdio.h>
#include <time.h>

int showhelp(_TCHAR* arg)
{
	_TCHAR *p, *s = arg;

	p = _tcschr(s, '\\');
	while(p) {
		s = ++p;
		p = _tcschr(p, '\\');
	}

	printf(" \n");
	printf(" Version: 0.0.1\n");
	printf(" Created: 2003.03.19\n");
	printf(" Revised: 2007.11.03\n\n");
	printf(" Compiled with Borland's BCC version 5.5.1 (Freeware)\n\n");
	printf(" SYNOPSYS:\n");
	printf(" \tFix broken torrent's downloaded files.\n\n");
	printf(" USAGE:\n");
	printf(" \t%s [ filename ] ...\n\n", s);
	printf(" ARGUMENTS:\n");
	printf(" \tfilename: one or more files to be fixed\n");
	printf(" \t- must be a real filename, not a wildcard\n");
	printf(" \t- must have had the corresponding *.!ut file\n");
	printf(" \t  after processing, the *.!ut files can be safely discarded\n\n", s);
	printf(" Press any key to continue..\n"); getch();
	return 1;

}

int showerr(const _TCHAR* msg)
{
	_TCHAR * lem;
	int err = GetLastError();

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lem, 0, NULL);

	//printf("ERROR: %s.\nLast error code:%d\n%s", msg, err, lem);
	printf("ERROR[%d]: %s.\n", err, msg); // no need to show last error string
	if (err != 183 && err != 0) printf("%s\n", lem);
	LocalFree(lem);
	return 0;
}

#define strcpy _tcscpy
#define strcat _tcscat

#define POWERSHIFT 24
const unsigned long BLOCK = 1 << POWERSHIFT;

int _tmain(int c, _TCHAR* args[])
{
	int i, k, len, changed;
	DWORD got;
	HANDLE source, target;
	LARGE_INTEGER qsize;
	__int64 sourcesize, targetsize;
	_TCHAR srcfile[1256];

	unsigned char ca, cb;
	unsigned char *bufs, *buft;
	DWORD gots, gott;

	const _TCHAR slut[] = ".!ut\0";

	//printf("ccount: %d\n", c);
	if (c < 2) return showhelp(args[0]);
 	//if ((c < 3) && (args[1][0] == '/')) return showhelp(args[0]);

	bufs = malloc(BLOCK); if (!bufs) return showerr("Not enough memory");
	buft = malloc(BLOCK); if (!buft) return showerr("Not enough memory");
	printf("Buffer size: %dMB\n", BLOCK>>20);

	for (i = 1; i < c; i++) {
		printf("File \"%s\" ", args[i]);
		target = CreateFile(args[i], GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (target == INVALID_HANDLE_VALUE) {
			showerr("Failed opening target file");
			continue;
		}

		//len = strlen(args[i]);

		strcpy(srcfile, args[i]);
		strcat(srcfile, slut);

		source = CreateFile(srcfile, GENERIC_READ,
			FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (source == INVALID_HANDLE_VALUE) {
			CloseHandle(target); // previously opened
			showerr("Failed reading !ut file");
			continue;
		}

		GetFileSizeEx(source, &qsize); sourcesize = qsize.QuadPart;
		GetFileSizeEx(target, &qsize); targetsize = qsize.QuadPart;

		//printf("File size: %I64d\n", sourcesize);
		if ((targetsize < 1) || (targetsize != sourcesize)) {
			showerr("File size is different");
			CloseHandle(target);
			CloseHandle(source);
			continue;
		}

		//printf("File size: %I64d\n", sourcesize);
		SetFilePointer(target, 0, NULL, 0);
		SetFilePointer(source, 0, NULL, 0);
		while (sourcesize > 0) {
			sourcesize -= BLOCK;

			ReadFile(target, buft, BLOCK, &got, NULL);
			ReadFile(source, bufs, BLOCK, &got, NULL);

			changed = 0;
			for (k = 0; (DWORD)k < got; k++) {
				if ((buft[k] == 0) && (bufs[k] > 0)) {
					buft[k] = bufs[k];
					changed = 1;
				}
			}

			if (changed) {
				SetFilePointer(target, -(int)got, NULL, 1);
				WriteFile(target, buft, got, &got, NULL);
			}
        }
		CloseHandle(target);
		CloseHandle(source);
		printf("- done\n");
	}
	free(bufs);
	free(buft);
	return 0;
}
