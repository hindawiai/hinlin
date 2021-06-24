<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2001 MontaVista Software Inc.
 * Author: Matt Porter <mporter@mvista.com>
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/libfdt.h>

#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र-generic/vmlinux.lds.h>

/*
 * These two variables specअगरy the मुक्त mem region
 * that can be used क्रम temporary दो_स्मृति area
 */
अचिन्हित दीर्घ मुक्त_mem_ptr;
अचिन्हित दीर्घ मुक्त_mem_end_ptr;

/* The linker tells us where the image is. */
बाह्य अचिन्हित अक्षर __image_begin, __image_end;

/* debug पूर्णांकerfaces  */
#अगर_घोषित CONFIG_DEBUG_ZBOOT
बाह्य व्योम माला_दो(स्थिर अक्षर *s);
बाह्य व्योम puthex(अचिन्हित दीर्घ दीर्घ val);
#अन्यथा
#घोषणा माला_दो(s) करो अणुपूर्ण जबतक (0)
#घोषणा puthex(val) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

बाह्य अक्षर __appended_dtb[];

व्योम error(अक्षर *x)
अणु
	माला_दो("\n\n");
	माला_दो(x);
	माला_दो("\n\n -- System halted");

	जबतक (1)
		;	/* Halt */
पूर्ण

/* activate the code क्रम pre-boot environment */
#घोषणा STATIC अटल

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

#अगर_घोषित CONFIG_KERNEL_ZSTD
#समावेश "../../../../lib/decompress_unzstd.c"
#पूर्ण_अगर

स्थिर अचिन्हित दीर्घ __stack_chk_guard = 0x000a0dff;

व्योम __stack_chk_fail(व्योम)
अणु
	error("stack-protector: Kernel stack is corrupted\n");
पूर्ण

व्योम decompress_kernel(अचिन्हित दीर्घ boot_heap_start)
अणु
	अचिन्हित दीर्घ zimage_start, zimage_size;

	zimage_start = (अचिन्हित दीर्घ)(&__image_begin);
	zimage_size = (अचिन्हित दीर्घ)(&__image_end) -
	    (अचिन्हित दीर्घ)(&__image_begin);

	माला_दो("zimage at:     ");
	puthex(zimage_start);
	माला_दो(" ");
	puthex(zimage_size + zimage_start);
	माला_दो("\n");

	/* This area are prepared क्रम दो_स्मृतिing when decompressing */
	मुक्त_mem_ptr = boot_heap_start;
	मुक्त_mem_end_ptr = boot_heap_start + BOOT_HEAP_SIZE;

	/* Display standard Linux/MIPS boot prompt */
	माला_दो("Uncompressing Linux at load address ");
	puthex(VMLINUX_LOAD_ADDRESS_ULL);
	माला_दो("\n");

	/* Decompress the kernel with according algorithm */
	__decompress((अक्षर *)zimage_start, zimage_size, 0, 0,
		   (व्योम *)VMLINUX_LOAD_ADDRESS_ULL, 0, 0, error);

	अगर (IS_ENABLED(CONFIG_MIPS_RAW_APPENDED_DTB) &&
	    fdt_magic((व्योम *)&__appended_dtb) == FDT_MAGIC) अणु
		अचिन्हित पूर्णांक image_size, dtb_size;

		dtb_size = fdt_totalsize((व्योम *)&__appended_dtb);

		/* last four bytes is always image size in little endian */
		image_size = get_unaligned_le32((व्योम *)&__image_end - 4);

		/* The device tree's address must be properly aligned  */
		image_size = ALIGN(image_size, STRUCT_ALIGNMENT);

		माला_दो("Copy device tree to address  ");
		puthex(VMLINUX_LOAD_ADDRESS_ULL + image_size);
		माला_दो("\n");

		/* copy dtb to where the booted kernel will expect it */
		स_नकल((व्योम *)VMLINUX_LOAD_ADDRESS_ULL + image_size,
		       __appended_dtb, dtb_size);
	पूर्ण

	/* FIXME: should we flush cache here? */
	माला_दो("Now, booting the kernel...\n");
पूर्ण
