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
 * We're keep a section table क्रम a few reasons:
 *
 * The Go runसमय had a couple of bugs: it would पढ़ो the section
 * table to try to figure out how many dynamic symbols there were (it
 * shouldn't have looked at the section table at all) and, अगर there
 * were no SHT_SYNDYM section table entry, it would use an
 * uninitialized value क्रम the number of symbols.  An empty DYNSYM
 * table would work, but I see no reason not to ग_लिखो a valid one (and
 * keep full perक्रमmance क्रम old Go programs).  This hack is only
 * needed on x86_64.
 *
 * The bug was पूर्णांकroduced on 2012-08-31 by:
 * https://code.google.com/p/go/source/detail?r=56ea40aac72b
 * and was fixed on 2014-06-13 by:
 * https://code.google.com/p/go/source/detail?r=fc1cd5e12595
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

#समावेश <tools/le_byteshअगरt.h>

#समावेश <linux/elf.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

स्थिर अक्षर *outfilename;

/* Symbols that we need in vdso2c. */
क्रमागत अणु
	sym_vvar_start,
	sym_vvar_page,
	sym_pvघड़ी_page,
	sym_hvघड़ी_page,
	sym_समयns_page,
पूर्ण;

स्थिर पूर्णांक special_pages[] = अणु
	sym_vvar_page,
	sym_pvघड़ी_page,
	sym_hvघड़ी_page,
	sym_समयns_page,
पूर्ण;

काष्ठा vdso_sym अणु
	स्थिर अक्षर *name;
	bool export;
पूर्ण;

काष्ठा vdso_sym required_syms[] = अणु
	[sym_vvar_start] = अणु"vvar_start", trueपूर्ण,
	[sym_vvar_page] = अणु"vvar_page", trueपूर्ण,
	[sym_pvघड़ी_page] = अणु"pvclock_page", trueपूर्ण,
	[sym_hvघड़ी_page] = अणु"hvclock_page", trueपूर्ण,
	[sym_समयns_page] = अणु"timens_page", trueपूर्ण,
	अणु"VDSO32_NOTE_MASK", trueपूर्ण,
	अणु"__kernel_vsyscall", trueपूर्ण,
	अणु"__kernel_sigreturn", trueपूर्ण,
	अणु"__kernel_rt_sigreturn", trueपूर्ण,
	अणु"int80_landing_pad", trueपूर्ण,
	अणु"vdso32_rt_sigreturn_landing_pad", trueपूर्ण,
	अणु"vdso32_sigreturn_landing_pad", trueपूर्ण,
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
 * Evil macros क्रम little-endian पढ़ोs and ग_लिखोs
 */
#घोषणा GLE(x, bits, अगरnot)						\
	__builtin_choose_expr(						\
		(माप(*(x)) == bits/8),				\
		(__typeof__(*(x)))get_unaligned_le##bits(x), अगरnot)

बाह्य व्योम bad_get_le(व्योम);
#घोषणा LAST_GLE(x)							\
	__builtin_choose_expr(माप(*(x)) == 1, *(x), bad_get_le())

#घोषणा GET_LE(x)							\
	GLE(x, 64, GLE(x, 32, GLE(x, 16, LAST_GLE(x))))

#घोषणा PLE(x, val, bits, अगरnot)					\
	__builtin_choose_expr(						\
		(माप(*(x)) == bits/8),				\
		put_unaligned_le##bits((val), (x)), अगरnot)

बाह्य व्योम bad_put_le(व्योम);
#घोषणा LAST_PLE(x, val)						\
	__builtin_choose_expr(माप(*(x)) == 1, *(x) = (val), bad_put_le())

#घोषणा PUT_LE(x, val)					\
	PLE(x, val, 64, PLE(x, val, 32, PLE(x, val, 16, LAST_PLE(x, val))))


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
		err(1, "open(%s)", name);

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
	 * generate raw output instead.
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
		err(1, "fopen(%s)", outfilename);

	go(raw_addr, raw_len, stripped_addr, stripped_len, outfile, name);

	munmap(raw_addr, raw_len);
	munmap(stripped_addr, stripped_len);
	ख_बंद(outfile);

	वापस 0;
पूर्ण
