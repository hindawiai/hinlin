<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * misc.c
 * 
 * This is a collection of several routines from gzip-1.0.3 
 * adapted क्रम Linux.
 *
 * दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 *
 * Modअगरied क्रम ARM Linux by Russell King
 *
 * Nicolas Pitre <nico@visuaide.com>  1999/04/14 :
 *  For this code to run directly from Flash, all स्थिरant variables must
 *  be marked with 'const' and all other variables initialized at run-समय 
 *  only.  This way all non स्थिरant variables will end up in the bss segment,
 *  which should poपूर्णांक to addresses in RAM and cleared to 0 on start.
 *  This allows क्रम a much quicker boot समय.
 *
 * Modअगरied क्रम Alpha, from the ARM version, by Jay Estabrook 2003.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>

#समावेश <linux/uaccess.h>

#घोषणा memzero(s,n)	स_रखो ((s),0,(n))
#घोषणा माला_दो		srm_prपूर्णांकk
बाह्य दीर्घ srm_prपूर्णांकk(स्थिर अक्षर *, ...)
     __attribute__ ((क्रमmat (म_लिखो, 1, 2)));

/*
 * gzip delarations
 */
#घोषणा OF(args)  args
#घोषणा STATIC अटल

प्रकार अचिन्हित अक्षर  uch;
प्रकार अचिन्हित लघु ush;
प्रकार अचिन्हित दीर्घ  ulg;

#घोषणा WSIZE 0x8000		/* Winकरोw size must be at least 32k, */
				/* and a घातer of two */

अटल uch *inbuf;		/* input buffer */
अटल uch *winकरोw;		/* Sliding winकरोw buffer */

अटल अचिन्हित insize;		/* valid bytes in inbuf */
अटल अचिन्हित inptr;		/* index of next byte to be processed in inbuf */
अटल अचिन्हित outcnt;		/* bytes in output buffer */

/* gzip flag byte */
#घोषणा ASCII_FLAG   0x01 /* bit 0 set: file probably ascii text */
#घोषणा CONTINUATION 0x02 /* bit 1 set: continuation of multi-part gzip file */
#घोषणा EXTRA_FIELD  0x04 /* bit 2 set: extra field present */
#घोषणा ORIG_NAME    0x08 /* bit 3 set: original file name present */
#घोषणा COMMENT      0x10 /* bit 4 set: file comment present */
#घोषणा ENCRYPTED    0x20 /* bit 5 set: file is encrypted */
#घोषणा RESERVED     0xC0 /* bit 6,7:   reserved */

#घोषणा get_byte()  (inptr < insize ? inbuf[inptr++] : fill_inbuf())

/* Diagnostic functions */
#अगर_घोषित DEBUG
#  define Assert(cond,msg) अणुअगर(!(cond)) error(msg);पूर्ण
#  define Trace(x) ख_लिखो x
#  define Tracev(x) अणुअगर (verbose) ख_लिखो x ;पूर्ण
#  define Tracevv(x) अणुअगर (verbose>1) ख_लिखो x ;पूर्ण
#  define Tracec(c,x) अणुअगर (verbose && (c)) ख_लिखो x ;पूर्ण
#  define Tracecv(c,x) अणुअगर (verbose>1 && (c)) ख_लिखो x ;पूर्ण
#अन्यथा
#  define Assert(cond,msg)
#  define Trace(x)
#  define Tracev(x)
#  define Tracevv(x)
#  define Tracec(c,x)
#  define Tracecv(c,x)
#पूर्ण_अगर

अटल पूर्णांक  fill_inbuf(व्योम);
अटल व्योम flush_winकरोw(व्योम);
अटल व्योम error(अक्षर *m);

अटल अक्षर *input_data;
अटल पूर्णांक  input_data_size;

अटल uch *output_data;
अटल ulg output_ptr;
अटल ulg bytes_out;

अटल व्योम error(अक्षर *m);
अटल व्योम gzip_mark(व्योम **);
अटल व्योम gzip_release(व्योम **);

बाह्य पूर्णांक end;
अटल ulg मुक्त_mem_ptr;
अटल ulg मुक्त_mem_end_ptr;

#घोषणा HEAP_SIZE 0x3000

#समावेश "../../../lib/inflate.c"

/* ===========================================================================
 * Fill the input buffer. This is called only when the buffer is empty
 * and at least one byte is really needed.
 */
पूर्णांक fill_inbuf(व्योम)
अणु
	अगर (insize != 0)
		error("ran out of input data");

	inbuf = input_data;
	insize = input_data_size;

	inptr = 1;
	वापस inbuf[0];
पूर्ण

/* ===========================================================================
 * Write the output winकरोw winकरोw[0..outcnt-1] and update crc and bytes_out.
 * (Used क्रम the decompressed data only.)
 */
व्योम flush_winकरोw(व्योम)
अणु
	ulg c = crc;
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
/*	माला_दो("."); */
पूर्ण

अटल व्योम error(अक्षर *x)
अणु
	माला_दो("\n\n");
	माला_दो(x);
	माला_दो("\n\n -- System halted");

	जबतक(1);	/* Halt */
पूर्ण

अचिन्हित पूर्णांक
decompress_kernel(व्योम *output_start,
		  व्योम *input_start,
		  माप_प्रकार ksize,
		  माप_प्रकार kzsize)
अणु
	output_data		= (uch *)output_start;
	input_data		= (uch *)input_start;
	input_data_size		= kzsize; /* use compressed size */

	/* FIXME FIXME FIXME */
	मुक्त_mem_ptr		= (ulg)output_start + ksize;
	मुक्त_mem_end_ptr	= (ulg)output_start + ksize + 0x200000;
	/* FIXME FIXME FIXME */

	/* put in temp area to reduce initial footprपूर्णांक */
	winकरोw = दो_स्मृति(WSIZE);

	makecrc();
/*	माला_दो("Uncompressing Linux..."); */
	gunzip();
/*	माला_दो(" done, booting the kernel.\n"); */
	वापस output_ptr;
पूर्ण
