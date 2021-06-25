<शैली गुरु>
/*
 * Definitions and wrapper functions क्रम kernel decompressor
 *
 *   (C) 2017 Helge Deller <deller@gmx.de>
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/elf.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/page.h>
#समावेश "sizes.h"

/*
 * gzip declarations
 */
#घोषणा STATIC अटल

#अघोषित स_हटाओ
#घोषणा स_हटाओ स_हटाओ
#घोषणा memzero(s, n) स_रखो((s), 0, (n))

#घोषणा दो_स्मृति	दो_स्मृति_gzip
#घोषणा मुक्त	मुक्त_gzip

/* Symbols defined by linker scripts */
बाह्य अक्षर input_data[];
बाह्य पूर्णांक input_len;
/* output_len is inserted by the linker possibly at an unaligned address */
बाह्य __le32 output_len __aligned(1);
बाह्य अक्षर _text, _end;
बाह्य अक्षर _bss, _ebss;
बाह्य अक्षर _startcode_end;
बाह्य व्योम startup_जारी(व्योम *entry, अचिन्हित दीर्घ cmdline,
	अचिन्हित दीर्घ rd_start, अचिन्हित दीर्घ rd_end) __noवापस;

व्योम error(अक्षर *m) __noवापस;

अटल अचिन्हित दीर्घ मुक्त_mem_ptr;
अटल अचिन्हित दीर्घ मुक्त_mem_end_ptr;

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

व्योम *स_हटाओ(व्योम *dest, स्थिर व्योम *src, माप_प्रकार n)
अणु
	स्थिर अक्षर *s = src;
	अक्षर *d = dest;

	अगर (d <= s) अणु
		जबतक (n--)
			*d++ = *s++;
	पूर्ण अन्यथा अणु
		d += n;
		s += n;
		जबतक (n--)
			*--d = *--s;
	पूर्ण
	वापस dest;
पूर्ण

व्योम *स_रखो(व्योम *s, पूर्णांक c, माप_प्रकार count)
अणु
	अक्षर *xs = (अक्षर *)s;

	जबतक (count--)
		*xs++ = c;
	वापस s;
पूर्ण

व्योम *स_नकल(व्योम *d, स्थिर व्योम *s, माप_प्रकार len)
अणु
	अक्षर *dest = (अक्षर *)d;
	स्थिर अक्षर *source = (स्थिर अक्षर *)s;

	जबतक (len--)
		*dest++ = *source++;
	वापस d;
पूर्ण

माप_प्रकार म_माप(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *sc;

	क्रम (sc = s; *sc != '\0'; ++sc)
		;
	वापस sc - s;
पूर्ण

अक्षर *म_अक्षर(स्थिर अक्षर *s, पूर्णांक c)
अणु
	जबतक (*s) अणु
		अगर (*s == (अक्षर)c)
			वापस (अक्षर *)s;
		++s;
	पूर्ण
	वापस शून्य;
पूर्ण

पूर्णांक माला_दो(स्थिर अक्षर *s)
अणु
	स्थिर अक्षर *nuline = s;

	जबतक ((nuline = म_अक्षर(s, '\n')) != शून्य) अणु
		अगर (nuline != s)
			pdc_iodc_prपूर्णांक(s, nuline - s);
		pdc_iodc_prपूर्णांक("\r\n", 2);
		s = nuline + 1;
	पूर्ण
	अगर (*s != '\0')
		pdc_iodc_prपूर्णांक(s, म_माप(s));

	वापस 0;
पूर्ण

अटल पूर्णांक अक्षर_दो(पूर्णांक c)
अणु
	अक्षर buf[2];

	buf[0] = c;
	buf[1] = '\0';
	माला_दो(buf);
	वापस c;
पूर्ण

व्योम __noवापस error(अक्षर *x)
अणु
	अगर (x) माला_दो(x);
	माला_दो("\n -- System halted\n");
	जबतक (1)	/* रुको क्रमever */
		;
पूर्ण

अटल पूर्णांक prपूर्णांक_num(अचिन्हित दीर्घ num, पूर्णांक base)
अणु
	स्थिर अक्षर hex[] = "0123456789abcdef";
	अक्षर str[40];
	पूर्णांक i = माप(str)-1;

	str[i--] = '\0';
	करो अणु
		str[i--] = hex[num % base];
		num = num / base;
	पूर्ण जबतक (num);

	अगर (base == 16) अणु
		str[i--] = 'x';
		str[i] = '0';
	पूर्ण अन्यथा i++;
	माला_दो(&str[i]);

	वापस 0;
पूर्ण

पूर्णांक म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	पूर्णांक i = 0;

	बहु_शुरू(args, fmt);

	जबतक (fmt[i]) अणु
		अगर (fmt[i] != '%') अणु
put:
			अक्षर_दो(fmt[i++]);
			जारी;
		पूर्ण

		अगर (fmt[++i] == '%')
			जाओ put;
		prपूर्णांक_num(बहु_तर्क(args, अचिन्हित दीर्घ),
			fmt[i] == 'x' ? 16:10);
		++i;
	पूर्ण

	बहु_पूर्ण(args);
	वापस 0;
पूर्ण

/* helper functions क्रम libgcc */
व्योम पात(व्योम)
अणु
	error("aborted.");
पूर्ण

#अघोषित दो_स्मृति
व्योम *दो_स्मृति(माप_प्रकार size)
अणु
	वापस दो_स्मृति_gzip(size);
पूर्ण

#अघोषित मुक्त
व्योम मुक्त(व्योम *ptr)
अणु
	वापस मुक्त_gzip(ptr);
पूर्ण


अटल व्योम flush_data_cache(अक्षर *start, अचिन्हित दीर्घ length)
अणु
	अक्षर *end = start + length;

	करो अणु
		यंत्र अस्थिर("fdc 0(%0)" : : "r" (start));
		यंत्र अस्थिर("fic 0(%%sr0,%0)" : : "r" (start));
		start += 16;
	पूर्ण जबतक (start < end);
	यंत्र अस्थिर("fdc 0(%0)" : : "r" (end));

	यंत्र ("sync");
पूर्ण

अटल व्योम parse_elf(व्योम *output)
अणु
#अगर_घोषित CONFIG_64BIT
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

#अगर_घोषित DEBUG
	म_लिखो("Parsing ELF... ");
#पूर्ण_अगर

	phdrs = दो_स्मृति(माप(*phdrs) * ehdr.e_phnum);
	अगर (!phdrs)
		error("Failed to allocate space for phdrs");

	स_नकल(phdrs, output + ehdr.e_phoff, माप(*phdrs) * ehdr.e_phnum);

	क्रम (i = 0; i < ehdr.e_phnum; i++) अणु
		phdr = &phdrs[i];

		चयन (phdr->p_type) अणु
		हाल PT_LOAD:
			dest = (व्योम *)((अचिन्हित दीर्घ) phdr->p_paddr &
					(__PAGE_OFFSET_DEFAULT-1));
			स_हटाओ(dest, output + phdr->p_offset, phdr->p_filesz);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(phdrs);
पूर्ण

अचिन्हित दीर्घ decompress_kernel(अचिन्हित पूर्णांक started_wide,
		अचिन्हित पूर्णांक command_line,
		स्थिर अचिन्हित पूर्णांक rd_start,
		स्थिर अचिन्हित पूर्णांक rd_end)
अणु
	अक्षर *output;
	अचिन्हित दीर्घ vmlinux_addr, vmlinux_len;
	अचिन्हित दीर्घ kernel_addr, kernel_len;

#अगर_घोषित CONFIG_64BIT
	parisc_narrow_firmware = 0;
#पूर्ण_अगर

	set_firmware_width_unlocked();

	अक्षर_दो('D');	/* अगर you get this D and no more, string storage */
			/* in $GLOBAL$ is wrong or %dp is wrong */
	माला_दो("ecompressing Linux... ");

	/* where the final bits are stored */
	kernel_addr = KERNEL_BINARY_TEXT_START;
	kernel_len = __pa(SZ_end) - __pa(SZparisc_kernel_start);
	अगर ((अचिन्हित दीर्घ) &_startcode_end > kernel_addr)
		error("Bootcode overlaps kernel code");

	/*
	 * Calculate addr to where the vmlinux ELF file shall be decompressed.
	 * Assembly code in head.S positioned the stack directly behind bss, so
	 * leave 2 MB क्रम the stack.
	 */
	vmlinux_addr = (अचिन्हित दीर्घ) &_ebss + 2*1024*1024;
	vmlinux_len = get_unaligned_le32(&output_len);
	output = (अक्षर *) vmlinux_addr;

	/*
	 * Initialize मुक्त_mem_ptr and मुक्त_mem_end_ptr.
	 */
	मुक्त_mem_ptr = vmlinux_addr + vmlinux_len;

	/* Limit memory क्रम bootoader to 1GB */
	#घोषणा ARTIFICIAL_LIMIT (1*1024*1024*1024)
	मुक्त_mem_end_ptr = PAGE0->imm_max_mem;
	अगर (मुक्त_mem_end_ptr > ARTIFICIAL_LIMIT)
		मुक्त_mem_end_ptr = ARTIFICIAL_LIMIT;

#अगर_घोषित CONFIG_BLK_DEV_INITRD
	/* अगर we have ramdisk this is at end of memory */
	अगर (rd_start && rd_start < मुक्त_mem_end_ptr)
		मुक्त_mem_end_ptr = rd_start;
#पूर्ण_अगर

	अगर (मुक्त_mem_ptr >= मुक्त_mem_end_ptr) अणु
		पूर्णांक मुक्त_ram;
		मुक्त_ram = (मुक्त_mem_ptr >> 20) + 1;
		अगर (मुक्त_ram < 32)
			मुक्त_ram = 32;
		म_लिखो("\nKernel requires at least %d MB RAM.\n",
			मुक्त_ram);
		error(शून्य);
	पूर्ण

#अगर_घोषित DEBUG
	म_लिखो("\n");
	म_लिखो("startcode_end = %x\n", &_startcode_end);
	म_लिखो("commandline   = %x\n", command_line);
	म_लिखो("rd_start      = %x\n", rd_start);
	म_लिखो("rd_end        = %x\n", rd_end);

	म_लिखो("free_ptr      = %x\n", मुक्त_mem_ptr);
	म_लिखो("free_ptr_end  = %x\n", मुक्त_mem_end_ptr);

	म_लिखो("input_data    = %x\n", input_data);
	म_लिखो("input_len     = %x\n", input_len);
	म_लिखो("output        = %x\n", output);
	म_लिखो("output_len    = %x\n", vmlinux_len);
	म_लिखो("kernel_addr   = %x\n", kernel_addr);
	म_लिखो("kernel_len    = %x\n", kernel_len);
#पूर्ण_अगर

	__decompress(input_data, input_len, शून्य, शून्य,
			output, 0, शून्य, error);
	parse_elf(output);

	output = (अक्षर *) kernel_addr;
	flush_data_cache(output, kernel_len);

	म_लिखो("done.\nBooting the kernel.\n");

	वापस (अचिन्हित दीर्घ) output;
पूर्ण
