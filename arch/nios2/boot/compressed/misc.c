<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2009 Thomas Chou <thomas@wytron.com.tw>
 *
 * This is a collection of several routines from gzip-1.0.3
 * adapted क्रम Linux.
 *
 * दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 *
 * Adapted क्रम SH by Stuart Menefy, Aug 1999
 *
 * Modअगरied to use standard LinuxSH BIOS by Greg Banks 7Jul2000
 *
 * Based on arch/sh/boot/compressed/misc.c
 */

#समावेश <linux/माला.स>

/*
 * gzip declarations
 */
#घोषणा OF(args)  args
#घोषणा STATIC अटल

#अघोषित स_रखो
#अघोषित स_नकल
#घोषणा memzero(s, n)		स_रखो((s), 0, (n))

प्रकार अचिन्हित अक्षर  uch;
प्रकार अचिन्हित लघु ush;
प्रकार अचिन्हित दीर्घ  ulg;
#घोषणा WSIZE 0x8000		/* Winकरोw size must be at least 32k, */
				/* and a घातer of two */

अटल uch *inbuf;		/* input buffer */
अटल uch winकरोw[WSIZE];	/* Sliding winकरोw buffer */

अटल अचिन्हित insize;	/* valid bytes in inbuf */
अटल अचिन्हित inptr;	/* index of next byte to be processed in inbuf */
अटल अचिन्हित outcnt;	/* bytes in output buffer */

/* gzip flag byte */
#घोषणा ASCII_FLAG	0x01 /* bit 0 set: file probably ASCII text */
#घोषणा CONTINUATION	0x02 /* bit 1 set: continuation of multi-part gzip
				file */
#घोषणा EXTRA_FIELD	0x04 /* bit 2 set: extra field present */
#घोषणा ORIG_NAME	0x08 /* bit 3 set: original file name present */
#घोषणा COMMENT		0x10 /* bit 4 set: file comment present */
#घोषणा ENCRYPTED	0x20 /* bit 5 set: file is encrypted */
#घोषणा RESERVED	0xC0 /* bit 6,7:   reserved */

#घोषणा get_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf())

#अगर_घोषित DEBUG
#  define Assert(cond, msg) अणुअगर (!(cond)) error(msg); पूर्ण
#  define Trace(x) ख_लिखो x
#  define Tracev(x) अणुअगर (verbose) ख_लिखो x ; पूर्ण
#  define Tracevv(x) अणुअगर (verbose > 1) ख_लिखो x ; पूर्ण
#  define Tracec(c, x) अणुअगर (verbose && (c)) ख_लिखो x ; पूर्ण
#  define Tracecv(c, x) अणुअगर (verbose > 1 && (c)) ख_लिखो x ; पूर्ण
#अन्यथा
#  define Assert(cond, msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c, x)
#  define Tracecv(c, x)
#पूर्ण_अगर
अटल पूर्णांक  fill_inbuf(व्योम);
अटल व्योम flush_winकरोw(व्योम);
अटल व्योम error(अक्षर *m);

बाह्य अक्षर input_data[];
बाह्य पूर्णांक input_len;

अटल दीर्घ bytes_out;
अटल uch *output_data;
अटल अचिन्हित दीर्घ output_ptr;

#समावेश "console.c"

अटल व्योम error(अक्षर *m);

पूर्णांक माला_दो(स्थिर अक्षर *);

बाह्य पूर्णांक _end;
अटल अचिन्हित दीर्घ मुक्त_mem_ptr;
अटल अचिन्हित दीर्घ मुक्त_mem_end_ptr;

#घोषणा HEAP_SIZE			0x10000

#समावेश "../../../../lib/inflate.c"

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *ss = (अक्षर *)s;

	क्रम (i = 0; i < n; i++)
		ss[i] = c;
	वापस s;
पूर्ण

व्योम *स_नकल(व्योम *__dest, __स्थिर व्योम *__src, माप_प्रकार __n)
अणु
	पूर्णांक i;
	अक्षर *d = (अक्षर *)__dest, *s = (अक्षर *)__src;

	क्रम (i = 0; i < __n; i++)
		d[i] = s[i];
	वापस __dest;
पूर्ण

/*
 * Fill the input buffer. This is called only when the buffer is empty
 * and at least one byte is really needed.
 */
अटल पूर्णांक fill_inbuf(व्योम)
अणु
	अगर (insize != 0)
		error("ran out of input data");

	inbuf = input_data;
	insize = input_len;
	inptr = 1;
	वापस inbuf[0];
पूर्ण

/*
 * Write the output winकरोw winकरोw[0..outcnt-1] and update crc and bytes_out.
 * (Used क्रम the decompressed data only.)
 */
अटल व्योम flush_winकरोw(व्योम)
अणु
	ulg c = crc;	/* temporary variable */
	अचिन्हित n;
	uch *in, *out, ch;

	in = winकरोw;
	out = &output_data[output_ptr];
	क्रम (n = 0; n < outcnt; n++) अणु
		ch = *out++ = *in++;
		c = crc_32_tab[((पूर्णांक)c ^ ch) & 0xff] ^ (c >> 8);
	पूर्ण
	crc = c;
	bytes_out += (ulg)outcnt;
	output_ptr += (ulg)outcnt;
	outcnt = 0;
पूर्ण

अटल व्योम error(अक्षर *x)
अणु
	माला_दो("\nERROR\n");
	माला_दो(x);
	माला_दो("\n\n -- System halted");

	जबतक (1)	/* Halt */
		;
पूर्ण

व्योम decompress_kernel(व्योम)
अणु
	output_data = (व्योम *) (CONFIG_NIOS2_MEM_BASE |
				CONFIG_NIOS2_KERNEL_REGION_BASE);
	output_ptr = 0;
	मुक्त_mem_ptr = (अचिन्हित दीर्घ)&_end;
	मुक्त_mem_end_ptr = मुक्त_mem_ptr + HEAP_SIZE;

	console_init();
	makecrc();
	माला_दो("Uncompressing Linux... ");
	gunzip();
	माला_दो("Ok, booting the kernel.\n");
पूर्ण
