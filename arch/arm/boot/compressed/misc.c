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
 */

अचिन्हित पूर्णांक __machine_arch_type;

#समावेश <linux/compiler.h>	/* क्रम अंतरभूत */
#समावेश <linux/types.h>
#समावेश <linux/linkage.h>
#समावेश "misc.h"

अटल व्योम माला_दोtr(स्थिर अक्षर *ptr);

#समावेश CONFIG_UNCOMPRESS_INCLUDE

#अगर_घोषित CONFIG_DEBUG_ICEDCC

#अगर defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K) || defined(CONFIG_CPU_V7)

अटल व्योम icedcc_अ_दो(पूर्णांक ch)
अणु
	पूर्णांक status, i = 0x4000000;

	करो अणु
		अगर (--i < 0)
			वापस;

		यंत्र अस्थिर ("mrc p14, 0, %0, c0, c1, 0" : "=r" (status));
	पूर्ण जबतक (status & (1 << 29));

	यंत्र("mcr p14, 0, %0, c0, c5, 0" : : "r" (ch));
पूर्ण


#या_अगर defined(CONFIG_CPU_XSCALE)

अटल व्योम icedcc_अ_दो(पूर्णांक ch)
अणु
	पूर्णांक status, i = 0x4000000;

	करो अणु
		अगर (--i < 0)
			वापस;

		यंत्र अस्थिर ("mrc p14, 0, %0, c14, c0, 0" : "=r" (status));
	पूर्ण जबतक (status & (1 << 28));

	यंत्र("mcr p14, 0, %0, c8, c0, 0" : : "r" (ch));
पूर्ण

#अन्यथा

अटल व्योम icedcc_अ_दो(पूर्णांक ch)
अणु
	पूर्णांक status, i = 0x4000000;

	करो अणु
		अगर (--i < 0)
			वापस;

		यंत्र अस्थिर ("mrc p14, 0, %0, c0, c0, 0" : "=r" (status));
	पूर्ण जबतक (status & 2);

	यंत्र("mcr p14, 0, %0, c1, c0, 0" : : "r" (ch));
पूर्ण

#पूर्ण_अगर

#घोषणा अ_दो(ch)	icedcc_अ_दो(ch)
#पूर्ण_अगर

अटल व्योम माला_दोtr(स्थिर अक्षर *ptr)
अणु
	अक्षर c;

	जबतक ((c = *ptr++) != '\0') अणु
		अगर (c == '\n')
			अ_दो('\r');
		अ_दो(c);
	पूर्ण

	flush();
पूर्ण

/*
 * gzip declarations
 */
बाह्य अक्षर input_data[];
बाह्य अक्षर input_data_end[];

अचिन्हित अक्षर *output_data;

अचिन्हित दीर्घ मुक्त_mem_ptr;
अचिन्हित दीर्घ मुक्त_mem_end_ptr;

#अगर_अघोषित arch_error
#घोषणा arch_error(x)
#पूर्ण_अगर

व्योम error(अक्षर *x)
अणु
	arch_error(x);

	माला_दोtr("\n\n");
	माला_दोtr(x);
	माला_दोtr("\n\n -- System halted");

	जबतक(1);	/* Halt */
पूर्ण

यंत्रlinkage व्योम __भाग0(व्योम)
अणु
	error("Attempting division by 0!");
पूर्ण

स्थिर अचिन्हित दीर्घ __stack_chk_guard = 0x000a0dff;

व्योम __stack_chk_fail(व्योम)
अणु
	error("stack-protector: Kernel stack is corrupted\n");
पूर्ण

बाह्य पूर्णांक करो_decompress(u8 *input, पूर्णांक len, u8 *output, व्योम (*error)(अक्षर *x));


व्योम
decompress_kernel(अचिन्हित दीर्घ output_start, अचिन्हित दीर्घ मुक्त_mem_ptr_p,
		अचिन्हित दीर्घ मुक्त_mem_ptr_end_p,
		पूर्णांक arch_id)
अणु
	पूर्णांक ret;

	output_data		= (अचिन्हित अक्षर *)output_start;
	मुक्त_mem_ptr		= मुक्त_mem_ptr_p;
	मुक्त_mem_end_ptr	= मुक्त_mem_ptr_end_p;
	__machine_arch_type	= arch_id;

	arch_decomp_setup();

	माला_दोtr("Uncompressing Linux...");
	ret = करो_decompress(input_data, input_data_end - input_data,
			    output_data, error);
	अगर (ret)
		error("decompressor returned an error");
	अन्यथा
		माला_दोtr(" done, booting the kernel.\n");
पूर्ण

व्योम क्रमtअगरy_panic(स्थिर अक्षर *name)
अणु
	error("detected buffer overflow");
पूर्ण
