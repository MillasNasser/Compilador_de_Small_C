#ifndef __IO_H
#define __IO_H
	#include "HeaderPadrao.h"
	typedef struct s_IO{
		FILE *sourceCode;
		void (*openFile)(struct s_IO *self, string path);
		bool (*closeFile)(struct s_IO *self);
		char (*getNextChar)(struct s_IO *self);
		bool (*rewind)(struct s_IO *self);
	} IO;

	IO* new_IO();
	
	void del_IO(IO*);
#endif //__IO_H