<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/h8300/boot/compressed/misc.c
 *
 * This is a collection of several routines from gzip-1.0.3
 * adapted क्रम Linux.
 *
 * दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 *
 * Adapted क्रम h8300 by Yoshinori Sato 2006
 */

#समावेश <linux/uaccess.h>

/*
 * gzip declarations
 */

#घोषणा OF(args)  args
#घोषणा STATIC अटल

#अघोषित स_रखो
#अघोषित स_नकल
#घोषणा memzero(s, n)     स_रखो((s), (0), (n))

बाह्य पूर्णांक _end;
अटल अचिन्हित दीर्घ मुक्त_mem_ptr;
अटल अचिन्हित दीर्घ मुक्त_mem_end_ptr;

बाह्य अक्षर input_data[];
बाह्य पूर्णांक input_len;
बाह्य अक्षर output[];

#घोषणा HEAP_SIZE             0x10000

#अगर_घोषित CONFIG_KERNEL_GZIP
#समावेश "../../../../lib/decompress_inflate.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZO
#समावेश "../../../../lib/decompress_unlzo.c"
#पूर्ण_अगर

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *ss = (अक्षर *)s;

	क्रम (i = 0; i < n; i++)
		ss[i] = c;
	वापस s;
पूर्ण

व्योम *स_नकल(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *d = (अक्षर *)dest, *s = (अक्षर *)src;

	क्रम (i = 0; i < n; i++)
		d[i] = s[i];
	वापस dest;
पूर्ण

अटल व्योम error(अक्षर *x)
अणु
	जबतक (1)
		;	/* Halt */
पूर्ण

व्योम decompress_kernel(व्योम)
अणु
	मुक्त_mem_ptr = (अचिन्हित दीर्घ)&_end;
	मुक्त_mem_end_ptr = मुक्त_mem_ptr + HEAP_SIZE;

	__decompress(input_data, input_len, शून्य, शून्य, output, 0, शून्य, error);
पूर्ण
