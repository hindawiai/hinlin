<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/boot/compressed/misc.c
 *
 * This is a collection of several routines from gzip-1.0.3
 * adapted क्रम Linux.
 *
 * दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 *
 * Adapted क्रम SH by Stuart Menefy, Aug 1999
 *
 * Modअगरied to use standard LinuxSH BIOS by Greg Banks 7Jul2000
 */

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/page.h>

/*
 * gzip declarations
 */

#घोषणा STATIC अटल

#अघोषित स_रखो
#अघोषित स_नकल
#घोषणा memzero(s, n)     स_रखो ((s), 0, (n))

/* cache.c */
#घोषणा CACHE_ENABLE      0
#घोषणा CACHE_DISABLE     1
पूर्णांक cache_control(अचिन्हित पूर्णांक command);

बाह्य अक्षर input_data[];
बाह्य पूर्णांक input_len;
अटल अचिन्हित अक्षर *output;

अटल व्योम error(अक्षर *m);

पूर्णांक माला_दो(स्थिर अक्षर *);

बाह्य पूर्णांक _text;		/* Defined in vmlinux.lds.S */
बाह्य पूर्णांक _end;
अटल अचिन्हित दीर्घ मुक्त_mem_ptr;
अटल अचिन्हित दीर्घ मुक्त_mem_end_ptr;

#अगर_घोषित CONFIG_HAVE_KERNEL_BZIP2
#घोषणा HEAP_SIZE	0x400000
#अन्यथा
#घोषणा HEAP_SIZE	0x10000
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_GZIP
#समावेश "../../../../lib/decompress_inflate.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_BZIP2
#समावेश "../../../../lib/decompress_bunzip2.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZMA
#समावेश "../../../../lib/decompress_unlzma.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_XZ
#समावेश "../../../../lib/decompress_unxz.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZO
#समावेश "../../../../lib/decompress_unlzo.c"
#पूर्ण_अगर

पूर्णांक माला_दो(स्थिर अक्षर *s)
अणु
	/* This should be updated to use the sh-sci routines */
	वापस 0;
पूर्ण

व्योम* स_रखो(व्योम* s, पूर्णांक c, माप_प्रकार n)
अणु
	पूर्णांक i;
	अक्षर *ss = (अक्षर*)s;

	क्रम (i=0;i<n;i++) ss[i] = c;
	वापस s;
पूर्ण

व्योम* स_नकल(व्योम* __dest, __स्थिर व्योम* __src,
			    माप_प्रकार __n)
अणु
	पूर्णांक i;
	अक्षर *d = (अक्षर *)__dest, *s = (अक्षर *)__src;

	क्रम (i=0;i<__n;i++) d[i] = s[i];
	वापस __dest;
पूर्ण

अटल व्योम error(अक्षर *x)
अणु
	माला_दो("\n\n");
	माला_दो(x);
	माला_दो("\n\n -- System halted");

	जबतक(1);	/* Halt */
पूर्ण

स्थिर अचिन्हित दीर्घ __stack_chk_guard = 0x000a0dff;

व्योम __stack_chk_fail(व्योम)
अणु
	error("stack-protector: Kernel stack is corrupted\n");
पूर्ण

/* Needed because vmlinux.lds.h references this */
व्योम ftrace_stub(व्योम)
अणु
पूर्ण

#घोषणा stackalign	4

#घोषणा STACK_SIZE (4096)
दीर्घ __attribute__ ((aligned(stackalign))) user_stack[STACK_SIZE];
दीर्घ *stack_start = &user_stack[STACK_SIZE];

व्योम decompress_kernel(व्योम)
अणु
	अचिन्हित दीर्घ output_addr;

	output_addr = __pa((अचिन्हित दीर्घ)&_text+PAGE_SIZE);
#अगर defined(CONFIG_29BIT)
	output_addr |= P2SEG;
#पूर्ण_अगर

	output = (अचिन्हित अक्षर *)output_addr;
	मुक्त_mem_ptr = (अचिन्हित दीर्घ)&_end;
	मुक्त_mem_end_ptr = मुक्त_mem_ptr + HEAP_SIZE;

	माला_दो("Uncompressing Linux... ");
	cache_control(CACHE_ENABLE);
	__decompress(input_data, input_len, शून्य, शून्य, output, 0, शून्य, error);
	cache_control(CACHE_DISABLE);
	माला_दो("Ok, booting the kernel.\n");
पूर्ण
