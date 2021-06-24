<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2015 Mentor Graphics Corporation.
 *
 * vdsomunge - Host program which produces a shared object
 * architecturally specअगरied to be usable by both soft- and hard-भग्न
 * programs.
 *
 * The Procedure Call Standard क्रम the ARM Architecture (ARM IHI
 * 0042E) says:
 *
 *	6.4.1 VFP and Base Standard Compatibility
 *
 *	Code compiled क्रम the VFP calling standard is compatible with
 *	the base standard (and vice-versa) अगर no भग्नing-poपूर्णांक or
 *	containerized vector arguments or results are used.
 *
 * And ELF क्रम the ARM Architecture (ARM IHI 0044E) (Table 4-2) says:
 *
 *	If both EF_ARM_ABI_FLOAT_XXXX bits are clear, conक्रमmance to the
 *	base procedure-call standard is implied.
 *
 * The VDSO is built with -msoft-भग्न, as with the rest of the ARM
 * kernel, and uses no भग्नing poपूर्णांक arguments or results.  The build
 * process will produce a shared object that may or may not have the
 * EF_ARM_ABI_FLOAT_SOFT flag set (it seems to depend on the binutils
 * version; binutils starting with 2.24 appears to set it).  The
 * EF_ARM_ABI_FLOAT_HARD flag should definitely not be set, and this
 * program will error out अगर it is.
 *
 * If the soft-भग्न flag is set, this program clears it.  That's all
 * it करोes.
 */

#समावेश <elf.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <मानकतर्क.स>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/types.h>
#समावेश <unistd.h>

#घोषणा swab16(x) \
	((((x) & 0x00ff) << 8) | \
	 (((x) & 0xff00) >> 8))

#घोषणा swab32(x) \
	((((x) & 0x000000ff) << 24) | \
	 (((x) & 0x0000ff00) <<  8) | \
	 (((x) & 0x00ff0000) >>  8) | \
	 (((x) & 0xff000000) >> 24))

#अगर __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#घोषणा HOST_ORDER ELFDATA2LSB
#या_अगर __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#घोषणा HOST_ORDER ELFDATA2MSB
#पूर्ण_अगर

/* Some of the ELF स्थिरants we'd like to use were added to <elf.h>
 * relatively recently.
 */
#अगर_अघोषित EF_ARM_EABI_VER5
#घोषणा EF_ARM_EABI_VER5 0x05000000
#पूर्ण_अगर

#अगर_अघोषित EF_ARM_ABI_FLOAT_SOFT
#घोषणा EF_ARM_ABI_FLOAT_SOFT 0x200
#पूर्ण_अगर

#अगर_अघोषित EF_ARM_ABI_FLOAT_HARD
#घोषणा EF_ARM_ABI_FLOAT_HARD 0x400
#पूर्ण_अगर

अटल पूर्णांक failed;
अटल स्थिर अक्षर *argv0;
अटल स्थिर अक्षर *outfile;

अटल व्योम fail(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	failed = 1;
	ख_लिखो(मानक_त्रुटि, "%s: ", argv0);
	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	बहु_पूर्ण(ap);
	निकास(निकास_त्रुटि);
पूर्ण

अटल व्योम cleanup(व्योम)
अणु
	अगर (failed && outfile != शून्य)
		unlink(outfile);
पूर्ण

अटल Elf32_Word पढ़ो_elf_word(Elf32_Word word, bool swap)
अणु
	वापस swap ? swab32(word) : word;
पूर्ण

अटल Elf32_Half पढ़ो_elf_half(Elf32_Half half, bool swap)
अणु
	वापस swap ? swab16(half) : half;
पूर्ण

अटल व्योम ग_लिखो_elf_word(Elf32_Word val, Elf32_Word *dst, bool swap)
अणु
	*dst = swap ? swab32(val) : val;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	स्थिर Elf32_Ehdr *inhdr;
	bool clear_soft_भग्न;
	स्थिर अक्षर *infile;
	Elf32_Word e_flags;
	स्थिर व्योम *inbuf;
	काष्ठा stat stat;
	व्योम *outbuf;
	bool swap;
	पूर्णांक outfd;
	पूर्णांक infd;

	निकास_पर(cleanup);
	argv0 = argv[0];

	अगर (argc != 3)
		fail("Usage: %s [infile] [outfile]\n", argv[0]);

	infile = argv[1];
	outfile = argv[2];

	infd = खोलो(infile, O_RDONLY);
	अगर (infd < 0)
		fail("Cannot open %s: %s\n", infile, म_त्रुटि(त्रुटि_सं));

	अगर (ख_स्थिति(infd, &stat) != 0)
		fail("Failed stat for %s: %s\n", infile, म_त्रुटि(त्रुटि_सं));

	inbuf = mmap(शून्य, stat.st_size, PROT_READ, MAP_PRIVATE, infd, 0);
	अगर (inbuf == MAP_FAILED)
		fail("Failed to map %s: %s\n", infile, म_त्रुटि(त्रुटि_सं));

	बंद(infd);

	inhdr = inbuf;

	अगर (स_भेद(&inhdr->e_ident, ELFMAG, SELFMAG) != 0)
		fail("Not an ELF file\n");

	अगर (inhdr->e_ident[EI_CLASS] != ELFCLASS32)
		fail("Unsupported ELF class\n");

	swap = inhdr->e_ident[EI_DATA] != HOST_ORDER;

	अगर (पढ़ो_elf_half(inhdr->e_type, swap) != ET_DYN)
		fail("Not a shared object\n");

	अगर (पढ़ो_elf_half(inhdr->e_machine, swap) != EM_ARM)
		fail("Unsupported architecture %#x\n", inhdr->e_machine);

	e_flags = पढ़ो_elf_word(inhdr->e_flags, swap);

	अगर (EF_ARM_EABI_VERSION(e_flags) != EF_ARM_EABI_VER5) अणु
		fail("Unsupported EABI version %#x\n",
		     EF_ARM_EABI_VERSION(e_flags));
	पूर्ण

	अगर (e_flags & EF_ARM_ABI_FLOAT_HARD)
		fail("Unexpected hard-float flag set in e_flags\n");

	clear_soft_भग्न = !!(e_flags & EF_ARM_ABI_FLOAT_SOFT);

	outfd = खोलो(outfile, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	अगर (outfd < 0)
		fail("Cannot open %s: %s\n", outfile, म_त्रुटि(त्रुटि_सं));

	अगर (ftruncate(outfd, stat.st_size) != 0)
		fail("Cannot truncate %s: %s\n", outfile, म_त्रुटि(त्रुटि_सं));

	outbuf = mmap(शून्य, stat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,
		      outfd, 0);
	अगर (outbuf == MAP_FAILED)
		fail("Failed to map %s: %s\n", outfile, म_त्रुटि(त्रुटि_सं));

	बंद(outfd);

	स_नकल(outbuf, inbuf, stat.st_size);

	अगर (clear_soft_भग्न) अणु
		Elf32_Ehdr *outhdr;

		outhdr = outbuf;
		e_flags &= ~EF_ARM_ABI_FLOAT_SOFT;
		ग_लिखो_elf_word(e_flags, &outhdr->e_flags, swap);
	पूर्ण

	अगर (msync(outbuf, stat.st_size, MS_SYNC) != 0)
		fail("Failed to sync %s: %s\n", outfile, म_त्रुटि(त्रुटि_सं));

	वापस निकास_सफल;
पूर्ण
