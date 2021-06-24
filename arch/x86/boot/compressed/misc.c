<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * misc.c
 *
 * This is a collection of several routines used to extract the kernel
 * which includes KASLR relocation, decompression, ELF parsing, and
 * relocation processing. Additionally included are the screen and serial
 * output functions and related debugging support functions.
 *
 * दो_स्मृति by Hannu Savolainen 1993 and Matthias Urlichs 1994
 * माला_दो by Nick Holloway 1993, better माला_दो by Martin Mares 1995
 * High loaded stuff by Hans Lermen & Werner Almesberger, Feb. 1996
 */

#समावेश "misc.h"
#समावेश "error.h"
#समावेश "pgtable.h"
#समावेश "../string.h"
#समावेश "../voffset.h"
#समावेश <यंत्र/bootparam_utils.h>

/*
 * WARNING!!
 * This code is compiled with -fPIC and it is relocated dynamically at
 * run समय, but no relocation processing is perक्रमmed. This means that
 * it is not safe to place poपूर्णांकers in अटल काष्ठाures.
 */

/* Macros used by the included decompressor code below. */
#घोषणा STATIC		अटल

/*
 * Provide definitions of memzero and स_हटाओ as some of the decompressors will
 * try to define their own functions अगर these are not defined as macros.
 */
#घोषणा memzero(s, n)	स_रखो((s), 0, (n))
#घोषणा स_हटाओ		स_हटाओ

/* Functions used by the included decompressor code below. */
व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n);

/*
 * This is set up by the setup-routine at boot-समय
 */
काष्ठा boot_params *boot_params;

memptr मुक्त_mem_ptr;
memptr मुक्त_mem_end_ptr;

अटल अक्षर *vidmem;
अटल पूर्णांक vidport;
अटल पूर्णांक lines, cols;

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

#अगर_घोषित CONFIG_KERNEL_LZ4
#समावेश "../../../../lib/decompress_unlz4.c"
#पूर्ण_अगर

#अगर_घोषित CONFIG_KERNEL_ZSTD
#समावेश "../../../../lib/decompress_unzstd.c"
#पूर्ण_अगर
/*
 * NOTE: When adding a new decompressor, please update the analysis in
 * ../header.S.
 */

अटल व्योम scroll(व्योम)
अणु
	पूर्णांक i;

	स_हटाओ(vidmem, vidmem + cols * 2, (lines - 1) * cols * 2);
	क्रम (i = (lines - 1) * cols * 2; i < lines * cols * 2; i += 2)
		vidmem[i] = ' ';
पूर्ण

#घोषणा XMTRDY          0x20

#घोषणा TXR             0       /*  Transmit रेजिस्टर (WRITE) */
#घोषणा LSR             5       /*  Line Status               */
अटल व्योम serial_अक्षर_दो(पूर्णांक ch)
अणु
	अचिन्हित समयout = 0xffff;

	जबतक ((inb(early_serial_base + LSR) & XMTRDY) == 0 && --समयout)
		cpu_relax();

	outb(ch, early_serial_base + TXR);
पूर्ण

व्योम __माला_दोtr(स्थिर अक्षर *s)
अणु
	पूर्णांक x, y, pos;
	अक्षर c;

	अगर (early_serial_base) अणु
		स्थिर अक्षर *str = s;
		जबतक (*str) अणु
			अगर (*str == '\n')
				serial_अक्षर_दो('\r');
			serial_अक्षर_दो(*str++);
		पूर्ण
	पूर्ण

	अगर (lines == 0 || cols == 0)
		वापस;

	x = boot_params->screen_info.orig_x;
	y = boot_params->screen_info.orig_y;

	जबतक ((c = *s++) != '\0') अणु
		अगर (c == '\n') अणु
			x = 0;
			अगर (++y >= lines) अणु
				scroll();
				y--;
			पूर्ण
		पूर्ण अन्यथा अणु
			vidmem[(x + cols * y) * 2] = c;
			अगर (++x >= cols) अणु
				x = 0;
				अगर (++y >= lines) अणु
					scroll();
					y--;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	boot_params->screen_info.orig_x = x;
	boot_params->screen_info.orig_y = y;

	pos = (x + cols * y) * 2;	/* Update cursor position */
	outb(14, vidport);
	outb(0xff & (pos >> 9), vidport+1);
	outb(15, vidport);
	outb(0xff & (pos >> 1), vidport+1);
पूर्ण

व्योम __puthex(अचिन्हित दीर्घ value)
अणु
	अक्षर alpha[2] = "0";
	पूर्णांक bits;

	क्रम (bits = माप(value) * 8 - 4; bits >= 0; bits -= 4) अणु
		अचिन्हित दीर्घ digit = (value >> bits) & 0xf;

		अगर (digit < 0xA)
			alpha[0] = '0' + digit;
		अन्यथा
			alpha[0] = 'a' + (digit - 0xA);

		__माला_दोtr(alpha);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86_NEED_RELOCS
अटल व्योम handle_relocations(व्योम *output, अचिन्हित दीर्घ output_len,
			       अचिन्हित दीर्घ virt_addr)
अणु
	पूर्णांक *reloc;
	अचिन्हित दीर्घ delta, map, ptr;
	अचिन्हित दीर्घ min_addr = (अचिन्हित दीर्घ)output;
	अचिन्हित दीर्घ max_addr = min_addr + (VO___bss_start - VO__text);

	/*
	 * Calculate the delta between where vmlinux was linked to load
	 * and where it was actually loaded.
	 */
	delta = min_addr - LOAD_PHYSICAL_ADDR;

	/*
	 * The kernel contains a table of relocation addresses. Those
	 * addresses have the final load address of the kernel in भव
	 * memory. We are currently working in the self map. So we need to
	 * create an adjusपंचांगent क्रम kernel memory addresses to the self map.
	 * This will involve subtracting out the base address of the kernel.
	 */
	map = delta - __START_KERNEL_map;

	/*
	 * 32-bit always perक्रमms relocations. 64-bit relocations are only
	 * needed अगर KASLR has chosen a dअगरferent starting address offset
	 * from __START_KERNEL_map.
	 */
	अगर (IS_ENABLED(CONFIG_X86_64))
		delta = virt_addr - LOAD_PHYSICAL_ADDR;

	अगर (!delta) अणु
		debug_माला_दोtr("No relocation needed... ");
		वापस;
	पूर्ण
	debug_माला_दोtr("Performing relocations... ");

	/*
	 * Process relocations: 32 bit relocations first then 64 bit after.
	 * Three sets of binary relocations are added to the end of the kernel
	 * beक्रमe compression. Each relocation table entry is the kernel
	 * address of the location which needs to be updated stored as a
	 * 32-bit value which is sign extended to 64 bits.
	 *
	 * Format is:
	 *
	 * kernel bits...
	 * 0 - zero terminator क्रम 64 bit relocations
	 * 64 bit relocation repeated
	 * 0 - zero terminator क्रम inverse 32 bit relocations
	 * 32 bit inverse relocation repeated
	 * 0 - zero terminator क्रम 32 bit relocations
	 * 32 bit relocation repeated
	 *
	 * So we work backwards from the end of the decompressed image.
	 */
	क्रम (reloc = output + output_len - माप(*reloc); *reloc; reloc--) अणु
		दीर्घ extended = *reloc;
		extended += map;

		ptr = (अचिन्हित दीर्घ)extended;
		अगर (ptr < min_addr || ptr > max_addr)
			error("32-bit relocation outside of kernel!\n");

		*(uपूर्णांक32_t *)ptr += delta;
	पूर्ण
#अगर_घोषित CONFIG_X86_64
	जबतक (*--reloc) अणु
		दीर्घ extended = *reloc;
		extended += map;

		ptr = (अचिन्हित दीर्घ)extended;
		अगर (ptr < min_addr || ptr > max_addr)
			error("inverse 32-bit relocation outside of kernel!\n");

		*(पूर्णांक32_t *)ptr -= delta;
	पूर्ण
	क्रम (reloc--; *reloc; reloc--) अणु
		दीर्घ extended = *reloc;
		extended += map;

		ptr = (अचिन्हित दीर्घ)extended;
		अगर (ptr < min_addr || ptr > max_addr)
			error("64-bit relocation outside of kernel!\n");

		*(uपूर्णांक64_t *)ptr += delta;
	पूर्ण
#पूर्ण_अगर
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम handle_relocations(व्योम *output, अचिन्हित दीर्घ output_len,
				      अचिन्हित दीर्घ virt_addr)
अणु पूर्ण
#पूर्ण_अगर

अटल व्योम parse_elf(व्योम *output)
अणु
#अगर_घोषित CONFIG_X86_64
	Elf64_Ehdr ehdr;
	Elf64_Phdr *phdrs, *phdr;
#अन्यथा
	Elf32_Ehdr ehdr;
	Elf32_Phdr *phdrs, *phdr;
#पूर्ण_अगर
	व्योम *dest;
	पूर्णांक i;

	स_नकल(&ehdr, output, माप(ehdr));
	अगर (ehdr.e_ident[EI_MAG0] != ELFMAG0 ||
	   ehdr.e_ident[EI_MAG1] != ELFMAG1 ||
	   ehdr.e_ident[EI_MAG2] != ELFMAG2 ||
	   ehdr.e_ident[EI_MAG3] != ELFMAG3) अणु
		error("Kernel is not a valid ELF file");
		वापस;
	पूर्ण

	debug_माला_दोtr("Parsing ELF... ");

	phdrs = दो_स्मृति(माप(*phdrs) * ehdr.e_phnum);
	अगर (!phdrs)
		error("Failed to allocate space for phdrs");

	स_नकल(phdrs, output + ehdr.e_phoff, माप(*phdrs) * ehdr.e_phnum);

	क्रम (i = 0; i < ehdr.e_phnum; i++) अणु
		phdr = &phdrs[i];

		चयन (phdr->p_type) अणु
		हाल PT_LOAD:
#अगर_घोषित CONFIG_X86_64
			अगर ((phdr->p_align % 0x200000) != 0)
				error("Alignment of LOAD segment isn't multiple of 2MB");
#पूर्ण_अगर
#अगर_घोषित CONFIG_RELOCATABLE
			dest = output;
			dest += (phdr->p_paddr - LOAD_PHYSICAL_ADDR);
#अन्यथा
			dest = (व्योम *)(phdr->p_paddr);
#पूर्ण_अगर
			स_हटाओ(dest, output + phdr->p_offset, phdr->p_filesz);
			अवरोध;
		शेष: /* Ignore other PT_* */ अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(phdrs);
पूर्ण

/*
 * The compressed kernel image (ZO), has been moved so that its position
 * is against the end of the buffer used to hold the uncompressed kernel
 * image (VO) and the execution environment (.bss, .brk), which makes sure
 * there is room to करो the in-place decompression. (See header.S क्रम the
 * calculations.)
 *
 *                             |-----compressed kernel image------|
 *                             V                                  V
 * 0                       extract_offset                      +INIT_SIZE
 * |-----------|---------------|-------------------------|--------|
 *             |               |                         |        |
 *           VO__text      startup_32 of ZO          VO__end    ZO__end
 *             ^                                         ^
 *             |-------uncompressed kernel image---------|
 *
 */
यंत्रlinkage __visible व्योम *extract_kernel(व्योम *rmode, memptr heap,
				  अचिन्हित अक्षर *input_data,
				  अचिन्हित दीर्घ input_len,
				  अचिन्हित अक्षर *output,
				  अचिन्हित दीर्घ output_len)
अणु
	स्थिर अचिन्हित दीर्घ kernel_total_size = VO__end - VO__text;
	अचिन्हित दीर्घ virt_addr = LOAD_PHYSICAL_ADDR;
	अचिन्हित दीर्घ needed_size;

	/* Retain x86 boot parameters poपूर्णांकer passed from startup_32/64. */
	boot_params = rmode;

	/* Clear flags पूर्णांकended क्रम solely in-kernel use. */
	boot_params->hdr.loadflags &= ~KASLR_FLAG;

	sanitize_boot_params(boot_params);

	अगर (boot_params->screen_info.orig_video_mode == 7) अणु
		vidmem = (अक्षर *) 0xb0000;
		vidport = 0x3b4;
	पूर्ण अन्यथा अणु
		vidmem = (अक्षर *) 0xb8000;
		vidport = 0x3d4;
	पूर्ण

	lines = boot_params->screen_info.orig_video_lines;
	cols = boot_params->screen_info.orig_video_cols;

	console_init();

	/*
	 * Save RSDP address क्रम later use. Have this after console_init()
	 * so that early debugging output from the RSDP parsing code can be
	 * collected.
	 */
	boot_params->acpi_rsdp_addr = get_rsdp_addr();

	debug_माला_दोtr("early console in extract_kernel\n");

	मुक्त_mem_ptr     = heap;	/* Heap */
	मुक्त_mem_end_ptr = heap + BOOT_HEAP_SIZE;

	/*
	 * The memory hole needed क्रम the kernel is the larger of either
	 * the entire decompressed kernel plus relocation table, or the
	 * entire decompressed kernel plus .bss and .brk sections.
	 *
	 * On X86_64, the memory is mapped with PMD pages. Round the
	 * size up so that the full extent of PMD pages mapped is
	 * included in the check against the valid memory table
	 * entries. This ensures the full mapped area is usable RAM
	 * and करोesn't include any reserved areas.
	 */
	needed_size = max(output_len, kernel_total_size);
#अगर_घोषित CONFIG_X86_64
	needed_size = ALIGN(needed_size, MIN_KERNEL_ALIGN);
#पूर्ण_अगर

	/* Report initial kernel position details. */
	debug_putaddr(input_data);
	debug_putaddr(input_len);
	debug_putaddr(output);
	debug_putaddr(output_len);
	debug_putaddr(kernel_total_size);
	debug_putaddr(needed_size);

#अगर_घोषित CONFIG_X86_64
	/* Report address of 32-bit trampoline */
	debug_putaddr(trampoline_32bit);
#पूर्ण_अगर

	choose_अक्रमom_location((अचिन्हित दीर्घ)input_data, input_len,
				(अचिन्हित दीर्घ *)&output,
				needed_size,
				&virt_addr);

	/* Validate memory location choices. */
	अगर ((अचिन्हित दीर्घ)output & (MIN_KERNEL_ALIGN - 1))
		error("Destination physical address inappropriately aligned");
	अगर (virt_addr & (MIN_KERNEL_ALIGN - 1))
		error("Destination virtual address inappropriately aligned");
#अगर_घोषित CONFIG_X86_64
	अगर (heap > 0x3fffffffffffUL)
		error("Destination address too large");
	अगर (virt_addr + max(output_len, kernel_total_size) > KERNEL_IMAGE_SIZE)
		error("Destination virtual address is beyond the kernel mapping area");
#अन्यथा
	अगर (heap > ((-__PAGE_OFFSET-(128<<20)-1) & 0x7fffffff))
		error("Destination address too large");
#पूर्ण_अगर
#अगर_अघोषित CONFIG_RELOCATABLE
	अगर (virt_addr != LOAD_PHYSICAL_ADDR)
		error("Destination virtual address changed when not relocatable");
#पूर्ण_अगर

	debug_माला_दोtr("\nDecompressing Linux... ");
	__decompress(input_data, input_len, शून्य, शून्य, output, output_len,
			शून्य, error);
	parse_elf(output);
	handle_relocations(output, output_len, virt_addr);
	debug_माला_दोtr("done.\nBooting the kernel.\n");

	/* Disable exception handling beक्रमe booting the kernel */
	cleanup_exception_handling();

	वापस output;
पूर्ण

व्योम क्रमtअगरy_panic(स्थिर अक्षर *name)
अणु
	error("detected buffer overflow");
पूर्ण
