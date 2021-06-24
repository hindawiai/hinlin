<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <byteswap.h>
#समावेश <elf.h>
#समावेश <endian.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

#अगर_घोषित be32toh
/* If libc provides leअणु16,32,64पूर्णtoh() then we'll use them */
#या_अगर BYTE_ORDER == LITTLE_ENDIAN
# define le16toh(x)	(x)
# define le32toh(x)	(x)
# define le64toh(x)	(x)
#या_अगर BYTE_ORDER == BIG_ENDIAN
# define le16toh(x)	bswap_16(x)
# define le32toh(x)	bswap_32(x)
# define le64toh(x)	bswap_64(x)
#पूर्ण_अगर

/* MIPS opcodes, in bits 31:26 of an inकाष्ठाion */
#घोषणा OP_SPECIAL	0x00
#घोषणा OP_REGIMM	0x01
#घोषणा OP_BEQ		0x04
#घोषणा OP_BNE		0x05
#घोषणा OP_BLEZ		0x06
#घोषणा OP_BGTZ		0x07
#घोषणा OP_BEQL		0x14
#घोषणा OP_BNEL		0x15
#घोषणा OP_BLEZL	0x16
#घोषणा OP_BGTZL	0x17
#घोषणा OP_LL		0x30
#घोषणा OP_LLD		0x34
#घोषणा OP_SC		0x38
#घोषणा OP_SCD		0x3c

/* Bits 20:16 of OP_REGIMM inकाष्ठाions */
#घोषणा REGIMM_BLTZ	0x00
#घोषणा REGIMM_BGEZ	0x01
#घोषणा REGIMM_BLTZL	0x02
#घोषणा REGIMM_BGEZL	0x03
#घोषणा REGIMM_BLTZAL	0x10
#घोषणा REGIMM_BGEZAL	0x11
#घोषणा REGIMM_BLTZALL	0x12
#घोषणा REGIMM_BGEZALL	0x13

/* Bits 5:0 of OP_SPECIAL inकाष्ठाions */
#घोषणा SPECIAL_SYNC	0x0f

अटल व्योम usage(खाता *f)
अणु
	ख_लिखो(f, "Usage: loongson3-llsc-check /path/to/vmlinux\n");
पूर्ण

अटल पूर्णांक se16(uपूर्णांक16_t x)
अणु
	वापस (पूर्णांक16_t)x;
पूर्ण

अटल bool is_ll(uपूर्णांक32_t insn)
अणु
	चयन (insn >> 26) अणु
	हाल OP_LL:
	हाल OP_LLD:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_sc(uपूर्णांक32_t insn)
अणु
	चयन (insn >> 26) अणु
	हाल OP_SC:
	हाल OP_SCD:
		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_sync(uपूर्णांक32_t insn)
अणु
	/* Bits 31:11 should all be zeroes */
	अगर (insn >> 11)
		वापस false;

	/* Bits 5:0 specअगरy the SYNC special encoding */
	अगर ((insn & 0x3f) != SPECIAL_SYNC)
		वापस false;

	वापस true;
पूर्ण

अटल bool is_branch(uपूर्णांक32_t insn, पूर्णांक *off)
अणु
	चयन (insn >> 26) अणु
	हाल OP_BEQ:
	हाल OP_BEQL:
	हाल OP_BNE:
	हाल OP_BNEL:
	हाल OP_BGTZ:
	हाल OP_BGTZL:
	हाल OP_BLEZ:
	हाल OP_BLEZL:
		*off = se16(insn) + 1;
		वापस true;

	हाल OP_REGIMM:
		चयन ((insn >> 16) & 0x1f) अणु
		हाल REGIMM_BGEZ:
		हाल REGIMM_BGEZL:
		हाल REGIMM_BGEZAL:
		हाल REGIMM_BGEZALL:
		हाल REGIMM_BLTZ:
		हाल REGIMM_BLTZL:
		हाल REGIMM_BLTZAL:
		हाल REGIMM_BLTZALL:
			*off = se16(insn) + 1;
			वापस true;

		शेष:
			वापस false;
		पूर्ण

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक check_ll(uपूर्णांक64_t pc, uपूर्णांक32_t *code, माप_प्रकार sz)
अणु
	sमाप_प्रकार i, max, sc_pos;
	पूर्णांक off;

	/*
	 * Every LL must be preceded by a sync inकाष्ठाion in order to ensure
	 * that inकाष्ठाion reordering करोesn't allow a prior memory access to
	 * execute after the LL & cause erroneous results.
	 */
	अगर (!is_sync(le32toh(code[-1]))) अणु
		ख_लिखो(मानक_त्रुटि, "%" PRIx64 ": LL not preceded by sync\n", pc);
		वापस -EINVAL;
	पूर्ण

	/* Find the matching SC inकाष्ठाion */
	max = sz / 4;
	क्रम (sc_pos = 0; sc_pos < max; sc_pos++) अणु
		अगर (is_sc(le32toh(code[sc_pos])))
			अवरोध;
	पूर्ण
	अगर (sc_pos >= max) अणु
		ख_लिखो(मानक_त्रुटि, "%" PRIx64 ": LL has no matching SC\n", pc);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Check branches within the LL/SC loop target sync inकाष्ठाions,
	 * ensuring that speculative execution can't generate memory accesses
	 * due to inकाष्ठाions outside of the loop.
	 */
	क्रम (i = 0; i < sc_pos; i++) अणु
		अगर (!is_branch(le32toh(code[i]), &off))
			जारी;

		/*
		 * If the branch target is within the LL/SC loop then we करोn't
		 * need to worry about it.
		 */
		अगर ((off >= -i) && (off <= sc_pos))
			जारी;

		/* If the branch tarमाला_लो a sync inकाष्ठाion we're all good... */
		अगर (is_sync(le32toh(code[i + off])))
			जारी;

		/* ...but अगर not, we have a problem */
		ख_लिखो(मानक_त्रुटि, "%" PRIx64 ": Branch target not a sync\n",
			pc + (i * 4));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_code(uपूर्णांक64_t pc, uपूर्णांक32_t *code, माप_प्रकार sz)
अणु
	पूर्णांक err = 0;

	अगर (sz % 4) अणु
		ख_लिखो(मानक_त्रुटि, "%" PRIx64 ": Section size not a multiple of 4\n",
			pc);
		err = -EINVAL;
		sz -= (sz % 4);
	पूर्ण

	अगर (is_ll(le32toh(code[0]))) अणु
		ख_लिखो(मानक_त्रुटि, "%" PRIx64 ": First instruction in section is an LL\n",
			pc);
		err = -EINVAL;
	पूर्ण

#घोषणा advance() (	\
	code++,		\
	pc += 4,	\
	sz -= 4		\
)

	/*
	 * Skip the first inकाष्ठाionm allowing check_ll to look backwards
	 * unconditionally.
	 */
	advance();

	/* Now scan through the code looking क्रम LL inकाष्ठाions */
	क्रम (; sz; advance()) अणु
		अगर (is_ll(le32toh(code[0])))
			err |= check_ll(pc, code, sz);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक vmlinux_fd, status, err, i;
	स्थिर अक्षर *vmlinux_path;
	काष्ठा stat st;
	Elf64_Ehdr *eh;
	Elf64_Shdr *sh;
	व्योम *vmlinux;

	status = निकास_त्रुटि;

	अगर (argc < 2) अणु
		usage(मानक_त्रुटि);
		जाओ out_ret;
	पूर्ण

	vmlinux_path = argv[1];
	vmlinux_fd = खोलो(vmlinux_path, O_RDONLY);
	अगर (vmlinux_fd == -1) अणु
		लिखो_त्रुटि("Unable to open vmlinux");
		जाओ out_ret;
	पूर्ण

	err = ख_स्थिति(vmlinux_fd, &st);
	अगर (err) अणु
		लिखो_त्रुटि("Unable to stat vmlinux");
		जाओ out_बंद;
	पूर्ण

	vmlinux = mmap(शून्य, st.st_size, PROT_READ, MAP_PRIVATE, vmlinux_fd, 0);
	अगर (vmlinux == MAP_FAILED) अणु
		लिखो_त्रुटि("Unable to mmap vmlinux");
		जाओ out_बंद;
	पूर्ण

	eh = vmlinux;
	अगर (स_भेद(eh->e_ident, ELFMAG, SELFMAG)) अणु
		ख_लिखो(मानक_त्रुटि, "vmlinux is not an ELF?\n");
		जाओ out_munmap;
	पूर्ण

	अगर (eh->e_ident[EI_CLASS] != ELFCLASS64) अणु
		ख_लिखो(मानक_त्रुटि, "vmlinux is not 64b?\n");
		जाओ out_munmap;
	पूर्ण

	अगर (eh->e_ident[EI_DATA] != ELFDATA2LSB) अणु
		ख_लिखो(मानक_त्रुटि, "vmlinux is not little endian?\n");
		जाओ out_munmap;
	पूर्ण

	क्रम (i = 0; i < le16toh(eh->e_shnum); i++) अणु
		sh = vmlinux + le64toh(eh->e_shoff) + (i * le16toh(eh->e_shentsize));

		अगर (sh->sh_type != SHT_PROGBITS)
			जारी;
		अगर (!(sh->sh_flags & SHF_EXECINSTR))
			जारी;

		err = check_code(le64toh(sh->sh_addr),
				 vmlinux + le64toh(sh->sh_offset),
				 le64toh(sh->sh_size));
		अगर (err)
			जाओ out_munmap;
	पूर्ण

	status = निकास_सफल;
out_munmap:
	munmap(vmlinux, st.st_size);
out_बंद:
	बंद(vmlinux_fd);
out_ret:
	ख_लिखो(मानक_निकास, "loongson3-llsc-check returns %s\n",
		status ? "failure" : "success");
	वापस status;
पूर्ण
