<शैली गुरु>
/*
 * vdso2c - A vdso image preparation tool
 * Copyright (c) 2014 Andy Lutomirski and others
 * Licensed under the GPL v2
 *
 * vdso2c requires stripped and unstripped input.  It would be trivial
 * to fully strip the input in here, but, क्रम reasons described below,
 * we need to ग_लिखो a section table.  Doing this is more or less
 * equivalent to dropping all non-allocatable sections, but it's
 * easier to let objcopy handle that instead of करोing it ourselves.
 * If we ever need to करो something fancier than what objcopy provides,
 * it would be straightक्रमward to add here.
 *
 * We keep a section table क्रम a few reasons:
 *
 * Binutils has issues debugging the vDSO: it पढ़ोs the section table to
 * find SHT_NOTE; it won't look at PT_NOTE क्रम the in-memory vDSO, which
 * would अवरोध build-id अगर we हटाओd the section table.  Binutils
 * also requires that shstrndx != 0.  See:
 * https://sourceware.org/bugzilla/show_bug.cgi?id=17064
 *
 * elfutils might not look क्रम PT_NOTE अगर there is a section table at
 * all.  I करोn't know whether this matters क्रम any practical purpose.
 *
 * For simplicity, rather than hacking up a partial section table, we
 * just ग_लिखो a mostly complete one.  We omit non-dynamic symbols,
 * though, since they're rather large.
 *
 * Once binutils माला_लो fixed, we might be able to drop this क्रम all but
 * the 64-bit vdso, since build-id only works in kernel RPMs, and
 * प्रणालीs that update to new enough kernel RPMs will likely update
 * binutils in sync.  build-id has never worked क्रम home-built kernel
 * RPMs without manual symlinking, and I suspect that no one ever करोes
 * that.
 */

/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <मानक_निवेशt.h>
#समावेश <unistd.h>
#समावेश <मानकतर्क.स>
#समावेश <मानककोष.स>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <fcntl.h>
#समावेश <err.h>

#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <tools/be_byteshअगरt.h>

#समावेश <linux/elf.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

स्थिर अक्षर *outfilename;

/* Symbols that we need in vdso2c. */
क्रमागत अणु
	sym_vvar_start,
	sym_VDSO_FAKE_SECTION_TABLE_START,
	sym_VDSO_FAKE_SECTION_TABLE_END,
पूर्ण;

काष्ठा vdso_sym अणु
	स्थिर अक्षर *name;
	पूर्णांक export;
पूर्ण;

काष्ठा vdso_sym required_syms[] = अणु
	[sym_vvar_start] = अणु"vvar_start", 1पूर्ण,
	[sym_VDSO_FAKE_SECTION_TABLE_START] = अणु
		"VDSO_FAKE_SECTION_TABLE_START", 0
	पूर्ण,
	[sym_VDSO_FAKE_SECTION_TABLE_END] = अणु
		"VDSO_FAKE_SECTION_TABLE_END", 0
	पूर्ण,
पूर्ण;

__attribute__((क्रमmat(म_लिखो, 1, 2))) __attribute__((noवापस))
अटल व्योम fail(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, क्रमmat);
	ख_लिखो(मानक_त्रुटि, "Error: ");
	भख_लिखो(मानक_त्रुटि, क्रमmat, ap);
	अगर (outfilename)
		unlink(outfilename);
	निकास(1);
	बहु_पूर्ण(ap);
पूर्ण

/*
 * Evil macros क्रम big-endian पढ़ोs and ग_लिखोs
 */
#घोषणा GBE(x, bits, अगरnot)						\
	__builtin_choose_expr(						\
		(माप(*(x)) == bits/8),				\
		(__typeof__(*(x)))get_unaligned_be##bits(x), अगरnot)

#घोषणा LAST_GBE(x)							\
	__builtin_choose_expr(माप(*(x)) == 1, *(x), (व्योम)(0))

#घोषणा GET_BE(x)							\
	GBE(x, 64, GBE(x, 32, GBE(x, 16, LAST_GBE(x))))

#घोषणा PBE(x, val, bits, अगरnot)					\
	__builtin_choose_expr(						\
		(माप(*(x)) == bits/8),				\
		put_unaligned_be##bits((val), (x)), अगरnot)

#घोषणा LAST_PBE(x, val)						\
	__builtin_choose_expr(माप(*(x)) == 1, *(x) = (val), (व्योम)(0))

#घोषणा PUT_BE(x, val)					\
	PBE(x, val, 64, PBE(x, val, 32, PBE(x, val, 16, LAST_PBE(x, val))))

#घोषणा NSYMS ARRAY_SIZE(required_syms)

#घोषणा BITSFUNC3(name, bits, suffix) name##bits##suffix
#घोषणा BITSFUNC2(name, bits, suffix) BITSFUNC3(name, bits, suffix)
#घोषणा BITSFUNC(name) BITSFUNC2(name, ELF_BITS, )

#घोषणा INT_BITS BITSFUNC2(पूर्णांक, ELF_BITS, _t)

#घोषणा ELF_BITS_XFORM2(bits, x) Elf##bits##_##x
#घोषणा ELF_BITS_XFORM(bits, x) ELF_BITS_XFORM2(bits, x)
#घोषणा ELF(x) ELF_BITS_XFORM(ELF_BITS, x)

#घोषणा ELF_BITS 64
#समावेश "vdso2c.h"
#अघोषित ELF_BITS

#घोषणा ELF_BITS 32
#समावेश "vdso2c.h"
#अघोषित ELF_BITS

अटल व्योम go(व्योम *raw_addr, माप_प्रकार raw_len,
	       व्योम *stripped_addr, माप_प्रकार stripped_len,
	       खाता *outfile, स्थिर अक्षर *name)
अणु
	Elf64_Ehdr *hdr = (Elf64_Ehdr *)raw_addr;

	अगर (hdr->e_ident[EI_CLASS] == ELFCLASS64) अणु
		go64(raw_addr, raw_len, stripped_addr, stripped_len,
		     outfile, name);
	पूर्ण अन्यथा अगर (hdr->e_ident[EI_CLASS] == ELFCLASS32) अणु
		go32(raw_addr, raw_len, stripped_addr, stripped_len,
		     outfile, name);
	पूर्ण अन्यथा अणु
		fail("unknown ELF class\n");
	पूर्ण
पूर्ण

अटल व्योम map_input(स्थिर अक्षर *name, व्योम **addr, माप_प्रकार *len, पूर्णांक prot)
अणु
	off_t पंचांगp_len;

	पूर्णांक fd = खोलो(name, O_RDONLY);

	अगर (fd == -1)
		err(1, "%s", name);

	पंचांगp_len = lseek(fd, 0, अंत_से);
	अगर (पंचांगp_len == (off_t)-1)
		err(1, "lseek");
	*len = (माप_प्रकार)पंचांगp_len;

	*addr = mmap(शून्य, पंचांगp_len, prot, MAP_PRIVATE, fd, 0);
	अगर (*addr == MAP_FAILED)
		err(1, "mmap");

	बंद(fd);
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	माप_प्रकार raw_len, stripped_len;
	व्योम *raw_addr, *stripped_addr;
	खाता *outfile;
	अक्षर *name, *पंचांगp;
	पूर्णांक namelen;

	अगर (argc != 4) अणु
		म_लिखो("Usage: vdso2c RAW_INPUT STRIPPED_INPUT OUTPUT\n");
		वापस 1;
	पूर्ण

	/*
	 * Figure out the काष्ठा name.  If we're writing to a .so file,
	 * generate raw output insted.
	 */
	name = strdup(argv[3]);
	namelen = म_माप(name);
	अगर (namelen >= 3 && !म_भेद(name + namelen - 3, ".so")) अणु
		name = शून्य;
	पूर्ण अन्यथा अणु
		पंचांगp = म_खोजप(name, '/');
		अगर (पंचांगp)
			name = पंचांगp + 1;
		पंचांगp = म_अक्षर(name, '.');
		अगर (पंचांगp)
			*पंचांगp = '\0';
		क्रम (पंचांगp = name; *पंचांगp; पंचांगp++)
			अगर (*पंचांगp == '-')
				*पंचांगp = '_';
	पूर्ण

	map_input(argv[1], &raw_addr, &raw_len, PROT_READ);
	map_input(argv[2], &stripped_addr, &stripped_len, PROT_READ);

	outfilename = argv[3];
	outfile = ख_खोलो(outfilename, "w");
	अगर (!outfile)
		err(1, "%s", argv[2]);

	go(raw_addr, raw_len, stripped_addr, stripped_len, outfile, name);

	munmap(raw_addr, raw_len);
	munmap(stripped_addr, stripped_len);
	ख_बंद(outfile);

	वापस 0;
पूर्ण
