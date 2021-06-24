<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Definitions and wrapper functions क्रम kernel decompressor
 *
 * Copyright IBM Corp. 2010
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <यंत्र/page.h>
#समावेश "decompressor.h"

/*
 * gzip declarations
 */
#घोषणा STATIC अटल

#अघोषित स_रखो
#अघोषित स_नकल
#अघोषित स_हटाओ
#घोषणा स_हटाओ स_हटाओ
#घोषणा memzero(s, n) स_रखो((s), 0, (n))

/* Symbols defined by linker scripts */
बाह्य अक्षर _end[];
बाह्य अचिन्हित अक्षर _compressed_start[];
बाह्य अचिन्हित अक्षर _compressed_end[];

#अगर_घोषित CONFIG_HAVE_KERNEL_BZIP2
#घोषणा BOOT_HEAP_SIZE	0x400000
#अन्यथा
#घोषणा BOOT_HEAP_SIZE	0x10000
#पूर्ण_अगर

अटल अचिन्हित दीर्घ मुक्त_mem_ptr = (अचिन्हित दीर्घ) _end;
अटल अचिन्हित दीर्घ मुक्त_mem_end_ptr = (अचिन्हित दीर्घ) _end + BOOT_HEAP_SIZE;

#अगर_घोषित CONFIG_KERNEL_GZIP
#समावेश "../../../../lib/decompress_inflate.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_BZIP2
#समावेश "../../../../lib/decompress_bunzip2.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZ4
#समावेश "../../../../lib/decompress_unlz4.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZMA
#समावेश "../../../../lib/decompress_unlzma.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_LZO
#समावेश "../../../../lib/decompress_unlzo.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_XZ
#समावेश "../../../../lib/decompress_unxz.c"
#पूर्ण_अगर

#घोषणा decompress_offset ALIGN((अचिन्हित दीर्घ)_end + BOOT_HEAP_SIZE, PAGE_SIZE)

अचिन्हित दीर्घ mem_safe_offset(व्योम)
अणु
	/*
	 * due to 4MB HEAD_SIZE क्रम bzip2
	 * 'decompress_offset + vmlinux.image_size' could be larger than
	 * kernel at final position + its .bss, so take the larger of two
	 */
	वापस max(decompress_offset + vmlinux.image_size,
		   vmlinux.शेष_lma + vmlinux.image_size + vmlinux.bss_size);
पूर्ण

व्योम *decompress_kernel(व्योम)
अणु
	व्योम *output = (व्योम *)decompress_offset;

	__decompress(_compressed_start, _compressed_end - _compressed_start,
		     शून्य, शून्य, output, 0, शून्य, error);
	वापस output;
पूर्ण
