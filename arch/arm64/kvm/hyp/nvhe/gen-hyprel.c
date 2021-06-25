<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 - Google LLC
 * Author: David Brazdil <dbrazdil@google.com>
 *
 * Generates relocation inक्रमmation used by the kernel to convert
 * असलolute addresses in hyp data from kernel VAs to hyp VAs.
 *
 * This is necessary because hyp code is linked पूर्णांकo the same binary
 * as the kernel but executes under dअगरferent memory mappings.
 * If the compiler used असलolute addressing, those addresses need to
 * be converted beक्रमe they are used by hyp code.
 *
 * The input of this program is the relocatable ELF object containing
 * all hyp code/data, not yet linked पूर्णांकo vmlinux. Hyp section names
 * should have been prefixed with `.hyp` at this poपूर्णांक.
 *
 * The output (prपूर्णांकed to मानक_निकास) is an assembly file containing
 * an array of 32-bit पूर्णांकegers and अटल relocations that inकाष्ठा
 * the linker of `vmlinux` to populate the array entries with offsets
 * to positions in the kernel binary containing VAs used by hyp code.
 *
 * Note that dynamic relocations could be used क्रम the same purpose.
 * However, those are only generated अगर CONFIG_RELOCATABLE=y.
 */

#समावेश <elf.h>
#समावेश <endian.h>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <sys/mman.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <unistd.h>

#समावेश <generated/स्वतःconf.h>

#घोषणा HYP_SECTION_PREFIX		".hyp"
#घोषणा HYP_RELOC_SECTION		".hyp.reloc"
#घोषणा HYP_SECTION_SYMBOL_PREFIX	"__hyp_section_"

/*
 * AArch64 relocation type स्थिरants.
 * Included in हाल these are not defined in the host toolchain.
 */
#अगर_अघोषित R_AARCH64_ABS64
#घोषणा R_AARCH64_ABS64			257
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_PREL64
#घोषणा R_AARCH64_PREL64		260
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_PREL32
#घोषणा R_AARCH64_PREL32		261
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_PREL16
#घोषणा R_AARCH64_PREL16		262
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_PLT32
#घोषणा R_AARCH64_PLT32			314
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_LD_PREL_LO19
#घोषणा R_AARCH64_LD_PREL_LO19		273
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_ADR_PREL_LO21
#घोषणा R_AARCH64_ADR_PREL_LO21		274
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_ADR_PREL_PG_HI21
#घोषणा R_AARCH64_ADR_PREL_PG_HI21	275
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_ADR_PREL_PG_HI21_NC
#घोषणा R_AARCH64_ADR_PREL_PG_HI21_NC	276
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_ADD_ABS_LO12_NC
#घोषणा R_AARCH64_ADD_ABS_LO12_NC	277
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_LDST8_ABS_LO12_NC
#घोषणा R_AARCH64_LDST8_ABS_LO12_NC	278
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_TSTBR14
#घोषणा R_AARCH64_TSTBR14		279
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_CONDBR19
#घोषणा R_AARCH64_CONDBR19		280
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_JUMP26
#घोषणा R_AARCH64_JUMP26		282
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_CALL26
#घोषणा R_AARCH64_CALL26		283
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_LDST16_ABS_LO12_NC
#घोषणा R_AARCH64_LDST16_ABS_LO12_NC	284
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_LDST32_ABS_LO12_NC
#घोषणा R_AARCH64_LDST32_ABS_LO12_NC	285
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_LDST64_ABS_LO12_NC
#घोषणा R_AARCH64_LDST64_ABS_LO12_NC	286
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G0
#घोषणा R_AARCH64_MOVW_PREL_G0		287
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G0_NC
#घोषणा R_AARCH64_MOVW_PREL_G0_NC	288
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G1
#घोषणा R_AARCH64_MOVW_PREL_G1		289
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G1_NC
#घोषणा R_AARCH64_MOVW_PREL_G1_NC	290
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G2
#घोषणा R_AARCH64_MOVW_PREL_G2		291
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G2_NC
#घोषणा R_AARCH64_MOVW_PREL_G2_NC	292
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_MOVW_PREL_G3
#घोषणा R_AARCH64_MOVW_PREL_G3		293
#पूर्ण_अगर
#अगर_अघोषित R_AARCH64_LDST128_ABS_LO12_NC
#घोषणा R_AARCH64_LDST128_ABS_LO12_NC	299
#पूर्ण_अगर

/* Global state of the processed ELF. */
अटल काष्ठा अणु
	स्थिर अक्षर	*path;
	अक्षर		*begin;
	माप_प्रकार		size;
	Elf64_Ehdr	*ehdr;
	Elf64_Shdr	*sh_table;
	स्थिर अक्षर	*sh_string;
पूर्ण elf;

#अगर defined(CONFIG_CPU_LITTLE_ENDIAN)

#घोषणा elf16toh(x)	le16toh(x)
#घोषणा elf32toh(x)	le32toh(x)
#घोषणा elf64toh(x)	le64toh(x)

#घोषणा ELFENDIAN	ELFDATA2LSB

#या_अगर defined(CONFIG_CPU_BIG_ENDIAN)

#घोषणा elf16toh(x)	be16toh(x)
#घोषणा elf32toh(x)	be32toh(x)
#घोषणा elf64toh(x)	be64toh(x)

#घोषणा ELFENDIAN	ELFDATA2MSB

#अन्यथा

#त्रुटि PDP-endian sadly unsupported...

#पूर्ण_अगर

#घोषणा fatal_error(fmt, ...)						\
	(अणु								\
		ख_लिखो(मानक_त्रुटि, "error: %s: " fmt "\n",			\
			elf.path, ## __VA_ARGS__);			\
		निकास(निकास_त्रुटि);					\
		__builtin_unreachable();				\
	पूर्ण)

#घोषणा fatal_लिखो_त्रुटि(msg)						\
	(अणु								\
		ख_लिखो(मानक_त्रुटि, "error: %s: " msg ": %s\n",		\
			elf.path, म_त्रुटि(त्रुटि_सं));			\
		निकास(निकास_त्रुटि);					\
		__builtin_unreachable();				\
	पूर्ण)

#घोषणा निश्चित_op(lhs, rhs, fmt, op)					\
	(अणु								\
		typeof(lhs) _lhs = (lhs);				\
		typeof(rhs) _rhs = (rhs);				\
									\
		अगर (!(_lhs op _rhs)) अणु					\
			fatal_error("assertion " #lhs " " #op " " #rhs	\
				" failed (lhs=" fmt ", rhs=" fmt	\
				", line=%d)", _lhs, _rhs, __LINE__);	\
		पूर्ण							\
	पूर्ण)

#घोषणा निश्चित_eq(lhs, rhs, fmt)	निश्चित_op(lhs, rhs, fmt, ==)
#घोषणा निश्चित_ne(lhs, rhs, fmt)	निश्चित_op(lhs, rhs, fmt, !=)
#घोषणा निश्चित_lt(lhs, rhs, fmt)	निश्चित_op(lhs, rhs, fmt, <)
#घोषणा निश्चित_ge(lhs, rhs, fmt)	निश्चित_op(lhs, rhs, fmt, >=)

/*
 * Return a poपूर्णांकer of a given type at a given offset from
 * the beginning of the ELF file.
 */
#घोषणा elf_ptr(type, off) ((type *)(elf.begin + (off)))

/* Iterate over all sections in the ELF. */
#घोषणा क्रम_each_section(var) \
	क्रम (var = elf.sh_table; var < elf.sh_table + elf16toh(elf.ehdr->e_shnum); ++var)

/* Iterate over all Elf64_Rela relocations in a given section. */
#घोषणा क्रम_each_rela(shdr, var)					\
	क्रम (var = elf_ptr(Elf64_Rela, elf64toh(shdr->sh_offset));	\
	     var < elf_ptr(Elf64_Rela, elf64toh(shdr->sh_offset) + elf64toh(shdr->sh_size)); var++)

/* True अगर a string starts with a given prefix. */
अटल अंतरभूत bool starts_with(स्थिर अक्षर *str, स्थिर अक्षर *prefix)
अणु
	वापस स_भेद(str, prefix, म_माप(prefix)) == 0;
पूर्ण

/* Returns a string containing the name of a given section. */
अटल अंतरभूत स्थिर अक्षर *section_name(Elf64_Shdr *shdr)
अणु
	वापस elf.sh_string + elf32toh(shdr->sh_name);
पूर्ण

/* Returns a poपूर्णांकer to the first byte of section data. */
अटल अंतरभूत स्थिर अक्षर *section_begin(Elf64_Shdr *shdr)
अणु
	वापस elf_ptr(अक्षर, elf64toh(shdr->sh_offset));
पूर्ण

/* Find a section by its offset from the beginning of the file. */
अटल अंतरभूत Elf64_Shdr *section_by_off(Elf64_Off off)
अणु
	निश्चित_ne(off, 0UL, "%lu");
	वापस elf_ptr(Elf64_Shdr, off);
पूर्ण

/* Find a section by its index. */
अटल अंतरभूत Elf64_Shdr *section_by_idx(uपूर्णांक16_t idx)
अणु
	निश्चित_ne(idx, SHN_UNDEF, "%u");
	वापस &elf.sh_table[idx];
पूर्ण

/*
 * Memory-map the given ELF file, perक्रमm sanity checks, and
 * populate global state.
 */
अटल व्योम init_elf(स्थिर अक्षर *path)
अणु
	पूर्णांक fd, ret;
	काष्ठा stat stat;

	/* Store path in the global काष्ठा क्रम error prपूर्णांकing. */
	elf.path = path;

	/* Open the ELF file. */
	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0)
		fatal_लिखो_त्रुटि("Could not open ELF file");

	/* Get status of ELF file to obtain its size. */
	ret = ख_स्थिति(fd, &stat);
	अगर (ret < 0) अणु
		बंद(fd);
		fatal_लिखो_त्रुटि("Could not get status of ELF file");
	पूर्ण

	/* mmap() the entire ELF file पढ़ो-only at an arbitrary address. */
	elf.begin = mmap(0, stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	अगर (elf.begin == MAP_FAILED) अणु
		बंद(fd);
		fatal_लिखो_त्रुटि("Could not mmap ELF file");
	पूर्ण

	/* mmap() was successful, बंद the FD. */
	बंद(fd);

	/* Get poपूर्णांकer to the ELF header. */
	निश्चित_ge(stat.st_size, माप(*elf.ehdr), "%lu");
	elf.ehdr = elf_ptr(Elf64_Ehdr, 0);

	/* Check the ELF magic. */
	निश्चित_eq(elf.ehdr->e_ident[EI_MAG0], ELFMAG0, "0x%x");
	निश्चित_eq(elf.ehdr->e_ident[EI_MAG1], ELFMAG1, "0x%x");
	निश्चित_eq(elf.ehdr->e_ident[EI_MAG2], ELFMAG2, "0x%x");
	निश्चित_eq(elf.ehdr->e_ident[EI_MAG3], ELFMAG3, "0x%x");

	/* Sanity check that this is an ELF64 relocatable object क्रम AArch64. */
	निश्चित_eq(elf.ehdr->e_ident[EI_CLASS], ELFCLASS64, "%u");
	निश्चित_eq(elf.ehdr->e_ident[EI_DATA], ELFENDIAN, "%u");
	निश्चित_eq(elf16toh(elf.ehdr->e_type), ET_REL, "%u");
	निश्चित_eq(elf16toh(elf.ehdr->e_machine), EM_AARCH64, "%u");

	/* Populate fields of the global काष्ठा. */
	elf.sh_table = section_by_off(elf64toh(elf.ehdr->e_shoff));
	elf.sh_string = section_begin(section_by_idx(elf16toh(elf.ehdr->e_shstrndx)));
पूर्ण

/* Prपूर्णांक the prologue of the output ASM file. */
अटल व्योम emit_prologue(व्योम)
अणु
	म_लिखो(".data\n"
	       ".pushsection " HYP_RELOC_SECTION ", \"a\"\n");
पूर्ण

/* Prपूर्णांक ASM statements needed as a prologue to a processed hyp section. */
अटल व्योम emit_section_prologue(स्थिर अक्षर *sh_orig_name)
अणु
	/* Declare the hyp section symbol. */
	म_लिखो(".global %s%s\n", HYP_SECTION_SYMBOL_PREFIX, sh_orig_name);
पूर्ण

/*
 * Prपूर्णांक ASM statements to create a hyp relocation entry क्रम a given
 * R_AARCH64_ABS64 relocation.
 *
 * The linker of vmlinux will populate the position given by `rela` with
 * an असलolute 64-bit kernel VA. If the kernel is relocatable, it will
 * also generate a dynamic relocation entry so that the kernel can shअगरt
 * the address at runसमय क्रम KASLR.
 *
 * Emit a 32-bit offset from the current address to the position given
 * by `rela`. This way the kernel can iterate over all kernel VAs used
 * by hyp at runसमय and convert them to hyp VAs. However, that offset
 * will not be known until linking of `vmlinux`, so emit a PREL32
 * relocation referencing a symbol that the hyp linker script put at
 * the beginning of the relocated section + the offset from `rela`.
 */
अटल व्योम emit_rela_असल64(Elf64_Rela *rela, स्थिर अक्षर *sh_orig_name)
अणु
	/* Offset of this reloc from the beginning of HYP_RELOC_SECTION. */
	अटल माप_प्रकार reloc_offset;

	/* Create storage क्रम the 32-bit offset. */
	म_लिखो(".word 0\n");

	/*
	 * Create a PREL32 relocation which inकाष्ठाs the linker of `vmlinux`
	 * to insert offset to position <base> + <offset>, where <base> is
	 * a symbol at the beginning of the relocated section, and <offset>
	 * is `rela->r_offset`.
	 */
	म_लिखो(".reloc %lu, R_AARCH64_PREL32, %s%s + 0x%lx\n",
	       reloc_offset, HYP_SECTION_SYMBOL_PREFIX, sh_orig_name,
	       elf64toh(rela->r_offset));

	reloc_offset += 4;
पूर्ण

/* Prपूर्णांक the epilogue of the output ASM file. */
अटल व्योम emit_epilogue(व्योम)
अणु
	म_लिखो(".popsection\n");
पूर्ण

/*
 * Iterate over all RELA relocations in a given section and emit
 * hyp relocation data क्रम all असलolute addresses in hyp code/data.
 *
 * Static relocations that generate PC-relative-addressing are ignored.
 * Failure is reported क्रम unexpected relocation types.
 */
अटल व्योम emit_rela_section(Elf64_Shdr *sh_rela)
अणु
	Elf64_Shdr *sh_orig = &elf.sh_table[elf32toh(sh_rela->sh_info)];
	स्थिर अक्षर *sh_orig_name = section_name(sh_orig);
	Elf64_Rela *rela;

	/* Skip all non-hyp sections. */
	अगर (!starts_with(sh_orig_name, HYP_SECTION_PREFIX))
		वापस;

	emit_section_prologue(sh_orig_name);

	क्रम_each_rela(sh_rela, rela) अणु
		uपूर्णांक32_t type = (uपूर्णांक32_t)elf64toh(rela->r_info);

		/* Check that rela poपूर्णांकs inside the relocated section. */
		निश्चित_lt(elf64toh(rela->r_offset), elf64toh(sh_orig->sh_size), "0x%lx");

		चयन (type) अणु
		/*
		 * Data relocations to generate असलolute addressing.
		 * Emit a hyp relocation.
		 */
		हाल R_AARCH64_ABS64:
			emit_rela_असल64(rela, sh_orig_name);
			अवरोध;
		/* Allow position-relative data relocations. */
		हाल R_AARCH64_PREL64:
		हाल R_AARCH64_PREL32:
		हाल R_AARCH64_PREL16:
		हाल R_AARCH64_PLT32:
			अवरोध;
		/* Allow relocations to generate PC-relative addressing. */
		हाल R_AARCH64_LD_PREL_LO19:
		हाल R_AARCH64_ADR_PREL_LO21:
		हाल R_AARCH64_ADR_PREL_PG_HI21:
		हाल R_AARCH64_ADR_PREL_PG_HI21_NC:
		हाल R_AARCH64_ADD_ABS_LO12_NC:
		हाल R_AARCH64_LDST8_ABS_LO12_NC:
		हाल R_AARCH64_LDST16_ABS_LO12_NC:
		हाल R_AARCH64_LDST32_ABS_LO12_NC:
		हाल R_AARCH64_LDST64_ABS_LO12_NC:
		हाल R_AARCH64_LDST128_ABS_LO12_NC:
			अवरोध;
		/* Allow relative relocations क्रम control-flow inकाष्ठाions. */
		हाल R_AARCH64_TSTBR14:
		हाल R_AARCH64_CONDBR19:
		हाल R_AARCH64_JUMP26:
		हाल R_AARCH64_CALL26:
			अवरोध;
		/* Allow group relocations to create PC-relative offset अंतरभूत. */
		हाल R_AARCH64_MOVW_PREL_G0:
		हाल R_AARCH64_MOVW_PREL_G0_NC:
		हाल R_AARCH64_MOVW_PREL_G1:
		हाल R_AARCH64_MOVW_PREL_G1_NC:
		हाल R_AARCH64_MOVW_PREL_G2:
		हाल R_AARCH64_MOVW_PREL_G2_NC:
		हाल R_AARCH64_MOVW_PREL_G3:
			अवरोध;
		शेष:
			fatal_error("Unexpected RELA type %u", type);
		पूर्ण
	पूर्ण
पूर्ण

/* Iterate over all sections and emit hyp relocation data क्रम RELA sections. */
अटल व्योम emit_all_relocs(व्योम)
अणु
	Elf64_Shdr *shdr;

	क्रम_each_section(shdr) अणु
		चयन (elf32toh(shdr->sh_type)) अणु
		हाल SHT_REL:
			fatal_error("Unexpected SHT_REL section \"%s\"",
				section_name(shdr));
		हाल SHT_RELA:
			emit_rela_section(shdr);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, स्थिर अक्षर **argv)
अणु
	अगर (argc != 2) अणु
		ख_लिखो(मानक_त्रुटि, "Usage: %s <elf_input>\n", argv[0]);
		वापस निकास_त्रुटि;
	पूर्ण

	init_elf(argv[1]);

	emit_prologue();
	emit_all_relocs();
	emit_epilogue();

	वापस निकास_सफल;
पूर्ण
