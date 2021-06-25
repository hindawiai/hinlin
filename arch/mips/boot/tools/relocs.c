<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* This is included from relocs_32/64.c */

#घोषणा ElfW(type)		_ElfW(ELF_BITS, type)
#घोषणा _ElfW(bits, type)	__ElfW(bits, type)
#घोषणा __ElfW(bits, type)	Elf##bits##_##type

#घोषणा Elf_Addr		ElfW(Addr)
#घोषणा Elf_Ehdr		ElfW(Ehdr)
#घोषणा Elf_Phdr		ElfW(Phdr)
#घोषणा Elf_Shdr		ElfW(Shdr)
#घोषणा Elf_Sym			ElfW(Sym)

अटल Elf_Ehdr ehdr;

काष्ठा relocs अणु
	uपूर्णांक32_t	*offset;
	अचिन्हित दीर्घ	count;
	अचिन्हित दीर्घ	size;
पूर्ण;

अटल काष्ठा relocs relocs;

काष्ठा section अणु
	Elf_Shdr       shdr;
	काष्ठा section *link;
	Elf_Sym        *symtab;
	Elf_Rel        *reltab;
	अक्षर           *strtab;
	दीर्घ           shdr_offset;
पूर्ण;
अटल काष्ठा section *secs;

अटल स्थिर अक्षर * स्थिर regex_sym_kernel = अणु
/* Symbols matching these regex's should never be relocated */
	"^(__crc_)",
पूर्ण;

अटल regex_t sym_regex_c;

अटल पूर्णांक regex_skip_reloc(स्थिर अक्षर *sym_name)
अणु
	वापस !regexec(&sym_regex_c, sym_name, 0, शून्य, 0);
पूर्ण

अटल व्योम regex_init(व्योम)
अणु
	अक्षर errbuf[128];
	पूर्णांक err;

	err = regcomp(&sym_regex_c, regex_sym_kernel,
			REG_EXTENDED|REG_NOSUB);

	अगर (err) अणु
		regerror(err, &sym_regex_c, errbuf, माप(errbuf));
		die("%s", errbuf);
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *rel_type(अचिन्हित type)
अणु
	अटल स्थिर अक्षर * स्थिर type_name[] = अणु
#घोषणा REL_TYPE(X)[X] = #X
		REL_TYPE(R_MIPS_NONE),
		REL_TYPE(R_MIPS_16),
		REL_TYPE(R_MIPS_32),
		REL_TYPE(R_MIPS_REL32),
		REL_TYPE(R_MIPS_26),
		REL_TYPE(R_MIPS_HI16),
		REL_TYPE(R_MIPS_LO16),
		REL_TYPE(R_MIPS_GPREL16),
		REL_TYPE(R_MIPS_LITERAL),
		REL_TYPE(R_MIPS_GOT16),
		REL_TYPE(R_MIPS_PC16),
		REL_TYPE(R_MIPS_CALL16),
		REL_TYPE(R_MIPS_GPREL32),
		REL_TYPE(R_MIPS_64),
		REL_TYPE(R_MIPS_HIGHER),
		REL_TYPE(R_MIPS_HIGHEST),
		REL_TYPE(R_MIPS_PC21_S2),
		REL_TYPE(R_MIPS_PC26_S2),
#अघोषित REL_TYPE
	पूर्ण;
	स्थिर अक्षर *name = "unknown type rel type name";

	अगर (type < ARRAY_SIZE(type_name) && type_name[type])
		name = type_name[type];
	वापस name;
पूर्ण

अटल स्थिर अक्षर *sec_name(अचिन्हित shndx)
अणु
	स्थिर अक्षर *sec_strtab;
	स्थिर अक्षर *name;

	sec_strtab = secs[ehdr.e_shstrndx].strtab;
	अगर (shndx < ehdr.e_shnum)
		name = sec_strtab + secs[shndx].shdr.sh_name;
	अन्यथा अगर (shndx == SHN_ABS)
		name = "ABSOLUTE";
	अन्यथा अगर (shndx == SHN_COMMON)
		name = "COMMON";
	अन्यथा
		name = "<noname>";
	वापस name;
पूर्ण

अटल काष्ठा section *sec_lookup(स्थिर अक्षर *secname)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ehdr.e_shnum; i++)
		अगर (म_भेद(secname, sec_name(i)) == 0)
			वापस &secs[i];

	वापस शून्य;
पूर्ण

अटल स्थिर अक्षर *sym_name(स्थिर अक्षर *sym_strtab, Elf_Sym *sym)
अणु
	स्थिर अक्षर *name;

	अगर (sym->st_name)
		name = sym_strtab + sym->st_name;
	अन्यथा
		name = sec_name(sym->st_shndx);
	वापस name;
पूर्ण

#अगर BYTE_ORDER == LITTLE_ENDIAN
#घोषणा le16_to_cpu(val) (val)
#घोषणा le32_to_cpu(val) (val)
#घोषणा le64_to_cpu(val) (val)
#घोषणा be16_to_cpu(val) bswap_16(val)
#घोषणा be32_to_cpu(val) bswap_32(val)
#घोषणा be64_to_cpu(val) bswap_64(val)

#घोषणा cpu_to_le16(val) (val)
#घोषणा cpu_to_le32(val) (val)
#घोषणा cpu_to_le64(val) (val)
#घोषणा cpu_to_be16(val) bswap_16(val)
#घोषणा cpu_to_be32(val) bswap_32(val)
#घोषणा cpu_to_be64(val) bswap_64(val)
#पूर्ण_अगर
#अगर BYTE_ORDER == BIG_ENDIAN
#घोषणा le16_to_cpu(val) bswap_16(val)
#घोषणा le32_to_cpu(val) bswap_32(val)
#घोषणा le64_to_cpu(val) bswap_64(val)
#घोषणा be16_to_cpu(val) (val)
#घोषणा be32_to_cpu(val) (val)
#घोषणा be64_to_cpu(val) (val)

#घोषणा cpu_to_le16(val) bswap_16(val)
#घोषणा cpu_to_le32(val) bswap_32(val)
#घोषणा cpu_to_le64(val) bswap_64(val)
#घोषणा cpu_to_be16(val) (val)
#घोषणा cpu_to_be32(val) (val)
#घोषणा cpu_to_be64(val) (val)
#पूर्ण_अगर

अटल uपूर्णांक16_t elf16_to_cpu(uपूर्णांक16_t val)
अणु
	अगर (ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		वापस le16_to_cpu(val);
	अन्यथा
		वापस be16_to_cpu(val);
पूर्ण

अटल uपूर्णांक32_t elf32_to_cpu(uपूर्णांक32_t val)
अणु
	अगर (ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		वापस le32_to_cpu(val);
	अन्यथा
		वापस be32_to_cpu(val);
पूर्ण

अटल uपूर्णांक32_t cpu_to_elf32(uपूर्णांक32_t val)
अणु
	अगर (ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		वापस cpu_to_le32(val);
	अन्यथा
		वापस cpu_to_be32(val);
पूर्ण

#घोषणा elf_half_to_cpu(x)	elf16_to_cpu(x)
#घोषणा elf_word_to_cpu(x)	elf32_to_cpu(x)

#अगर ELF_BITS == 64
अटल uपूर्णांक64_t elf64_to_cpu(uपूर्णांक64_t val)
अणु
	अगर (ehdr.e_ident[EI_DATA] == ELFDATA2LSB)
		वापस le64_to_cpu(val);
	अन्यथा
		वापस be64_to_cpu(val);
पूर्ण
#घोषणा elf_addr_to_cpu(x)	elf64_to_cpu(x)
#घोषणा elf_off_to_cpu(x)	elf64_to_cpu(x)
#घोषणा elf_xword_to_cpu(x)	elf64_to_cpu(x)
#अन्यथा
#घोषणा elf_addr_to_cpu(x)	elf32_to_cpu(x)
#घोषणा elf_off_to_cpu(x)	elf32_to_cpu(x)
#घोषणा elf_xword_to_cpu(x)	elf32_to_cpu(x)
#पूर्ण_अगर

अटल व्योम पढ़ो_ehdr(खाता *fp)
अणु
	अगर (ख_पढ़ो(&ehdr, माप(ehdr), 1, fp) != 1)
		die("Cannot read ELF header: %s\n", म_त्रुटि(त्रुटि_सं));

	अगर (स_भेद(ehdr.e_ident, ELFMAG, SELFMAG) != 0)
		die("No ELF magic\n");

	अगर (ehdr.e_ident[EI_CLASS] != ELF_CLASS)
		die("Not a %d bit executable\n", ELF_BITS);

	अगर ((ehdr.e_ident[EI_DATA] != ELFDATA2LSB) &&
	    (ehdr.e_ident[EI_DATA] != ELFDATA2MSB))
		die("Unknown ELF Endianness\n");

	अगर (ehdr.e_ident[EI_VERSION] != EV_CURRENT)
		die("Unknown ELF version\n");

	/* Convert the fields to native endian */
	ehdr.e_type      = elf_half_to_cpu(ehdr.e_type);
	ehdr.e_machine   = elf_half_to_cpu(ehdr.e_machine);
	ehdr.e_version   = elf_word_to_cpu(ehdr.e_version);
	ehdr.e_entry     = elf_addr_to_cpu(ehdr.e_entry);
	ehdr.e_phoff     = elf_off_to_cpu(ehdr.e_phoff);
	ehdr.e_shoff     = elf_off_to_cpu(ehdr.e_shoff);
	ehdr.e_flags     = elf_word_to_cpu(ehdr.e_flags);
	ehdr.e_ehsize    = elf_half_to_cpu(ehdr.e_ehsize);
	ehdr.e_phentsize = elf_half_to_cpu(ehdr.e_phentsize);
	ehdr.e_phnum     = elf_half_to_cpu(ehdr.e_phnum);
	ehdr.e_shentsize = elf_half_to_cpu(ehdr.e_shentsize);
	ehdr.e_shnum     = elf_half_to_cpu(ehdr.e_shnum);
	ehdr.e_shstrndx  = elf_half_to_cpu(ehdr.e_shstrndx);

	अगर ((ehdr.e_type != ET_EXEC) && (ehdr.e_type != ET_DYN))
		die("Unsupported ELF header type\n");

	अगर (ehdr.e_machine != ELF_MACHINE)
		die("Not for %s\n", ELF_MACHINE_NAME);

	अगर (ehdr.e_version != EV_CURRENT)
		die("Unknown ELF version\n");

	अगर (ehdr.e_ehsize != माप(Elf_Ehdr))
		die("Bad Elf header size\n");

	अगर (ehdr.e_phentsize != माप(Elf_Phdr))
		die("Bad program header entry\n");

	अगर (ehdr.e_shentsize != माप(Elf_Shdr))
		die("Bad section header entry\n");

	अगर (ehdr.e_shstrndx >= ehdr.e_shnum)
		die("String table index out of bounds\n");
पूर्ण

अटल व्योम पढ़ो_shdrs(खाता *fp)
अणु
	पूर्णांक i;
	Elf_Shdr shdr;

	secs = सुस्मृति(ehdr.e_shnum, माप(काष्ठा section));
	अगर (!secs)
		die("Unable to allocate %d section headers\n", ehdr.e_shnum);

	अगर (ख_जाओ(fp, ehdr.e_shoff, शुरू_से) < 0)
		die("Seek to %d failed: %s\n", ehdr.e_shoff, म_त्रुटि(त्रुटि_सं));

	क्रम (i = 0; i < ehdr.e_shnum; i++) अणु
		काष्ठा section *sec = &secs[i];

		sec->shdr_offset = ख_बताओ(fp);
		अगर (ख_पढ़ो(&shdr, माप(shdr), 1, fp) != 1)
			die("Cannot read ELF section headers %d/%d: %s\n",
			    i, ehdr.e_shnum, म_त्रुटि(त्रुटि_सं));
		sec->shdr.sh_name      = elf_word_to_cpu(shdr.sh_name);
		sec->shdr.sh_type      = elf_word_to_cpu(shdr.sh_type);
		sec->shdr.sh_flags     = elf_xword_to_cpu(shdr.sh_flags);
		sec->shdr.sh_addr      = elf_addr_to_cpu(shdr.sh_addr);
		sec->shdr.sh_offset    = elf_off_to_cpu(shdr.sh_offset);
		sec->shdr.sh_size      = elf_xword_to_cpu(shdr.sh_size);
		sec->shdr.sh_link      = elf_word_to_cpu(shdr.sh_link);
		sec->shdr.sh_info      = elf_word_to_cpu(shdr.sh_info);
		sec->shdr.sh_addralign = elf_xword_to_cpu(shdr.sh_addralign);
		sec->shdr.sh_entsize   = elf_xword_to_cpu(shdr.sh_entsize);
		अगर (sec->shdr.sh_link < ehdr.e_shnum)
			sec->link = &secs[sec->shdr.sh_link];
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_strtअसल(खाता *fp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ehdr.e_shnum; i++) अणु
		काष्ठा section *sec = &secs[i];

		अगर (sec->shdr.sh_type != SHT_STRTAB)
			जारी;

		sec->strtab = दो_स्मृति(sec->shdr.sh_size);
		अगर (!sec->strtab)
			die("malloc of %d bytes for strtab failed\n",
			    sec->shdr.sh_size);

		अगर (ख_जाओ(fp, sec->shdr.sh_offset, शुरू_से) < 0)
			die("Seek to %d failed: %s\n",
			    sec->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));

		अगर (ख_पढ़ो(sec->strtab, 1, sec->shdr.sh_size, fp) !=
		    sec->shdr.sh_size)
			die("Cannot read symbol table: %s\n", म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_symtअसल(खाता *fp)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < ehdr.e_shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		अगर (sec->shdr.sh_type != SHT_SYMTAB)
			जारी;

		sec->symtab = दो_स्मृति(sec->shdr.sh_size);
		अगर (!sec->symtab)
			die("malloc of %d bytes for symtab failed\n",
			    sec->shdr.sh_size);

		अगर (ख_जाओ(fp, sec->shdr.sh_offset, शुरू_से) < 0)
			die("Seek to %d failed: %s\n",
			    sec->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));

		अगर (ख_पढ़ो(sec->symtab, 1, sec->shdr.sh_size, fp) !=
		    sec->shdr.sh_size)
			die("Cannot read symbol table: %s\n", म_त्रुटि(त्रुटि_सं));

		क्रम (j = 0; j < sec->shdr.sh_size/माप(Elf_Sym); j++) अणु
			Elf_Sym *sym = &sec->symtab[j];

			sym->st_name  = elf_word_to_cpu(sym->st_name);
			sym->st_value = elf_addr_to_cpu(sym->st_value);
			sym->st_size  = elf_xword_to_cpu(sym->st_size);
			sym->st_shndx = elf_half_to_cpu(sym->st_shndx);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_relocs(खाता *fp)
अणु
	अटल अचिन्हित दीर्घ base = 0;
	पूर्णांक i, j;

	अगर (!base) अणु
		काष्ठा section *sec = sec_lookup(".text");

		अगर (!sec)
			die("Could not find .text section\n");

		base = sec->shdr.sh_addr;
	पूर्ण

	क्रम (i = 0; i < ehdr.e_shnum; i++) अणु
		काष्ठा section *sec = &secs[i];

		अगर (sec->shdr.sh_type != SHT_REL_TYPE)
			जारी;

		sec->reltab = दो_स्मृति(sec->shdr.sh_size);
		अगर (!sec->reltab)
			die("malloc of %d bytes for relocs failed\n",
			    sec->shdr.sh_size);

		अगर (ख_जाओ(fp, sec->shdr.sh_offset, शुरू_से) < 0)
			die("Seek to %d failed: %s\n",
			    sec->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));

		अगर (ख_पढ़ो(sec->reltab, 1, sec->shdr.sh_size, fp) !=
		    sec->shdr.sh_size)
			die("Cannot read symbol table: %s\n", म_त्रुटि(त्रुटि_सं));

		क्रम (j = 0; j < sec->shdr.sh_size/माप(Elf_Rel); j++) अणु
			Elf_Rel *rel = &sec->reltab[j];

			rel->r_offset = elf_addr_to_cpu(rel->r_offset);
			/* Set offset पूर्णांकo kernel image */
			rel->r_offset -= base;
#अगर (ELF_BITS == 32)
			rel->r_info   = elf_xword_to_cpu(rel->r_info);
#अन्यथा
			/* Convert MIPS64 RELA क्रमmat - only the symbol
			 * index needs converting to native endianness
			 */
			rel->r_info   = rel->r_info;
			ELF_R_SYM(rel->r_info) = elf32_to_cpu(ELF_R_SYM(rel->r_info));
#पूर्ण_अगर
#अगर (SHT_REL_TYPE == SHT_RELA)
			rel->r_addend = elf_xword_to_cpu(rel->r_addend);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम हटाओ_relocs(खाता *fp)
अणु
	पूर्णांक i;
	Elf_Shdr shdr;

	क्रम (i = 0; i < ehdr.e_shnum; i++) अणु
		काष्ठा section *sec = &secs[i];

		अगर (sec->shdr.sh_type != SHT_REL_TYPE)
			जारी;

		अगर (ख_जाओ(fp, sec->shdr_offset, शुरू_से) < 0)
			die("Seek to %d failed: %s\n",
			    sec->shdr_offset, म_त्रुटि(त्रुटि_सं));

		अगर (ख_पढ़ो(&shdr, माप(shdr), 1, fp) != 1)
			die("Cannot read ELF section headers %d/%d: %s\n",
			    i, ehdr.e_shnum, म_त्रुटि(त्रुटि_सं));

		/* Set relocation section size to 0, effectively removing it.
		 * This is necessary due to lack of support क्रम relocations
		 * in objcopy when creating 32bit elf from 64bit elf.
		 */
		shdr.sh_size = 0;

		अगर (ख_जाओ(fp, sec->shdr_offset, शुरू_से) < 0)
			die("Seek to %d failed: %s\n",
			    sec->shdr_offset, म_त्रुटि(त्रुटि_सं));

		अगर (ख_डालो(&shdr, माप(shdr), 1, fp) != 1)
			die("Cannot write ELF section headers %d/%d: %s\n",
			    i, ehdr.e_shnum, म_त्रुटि(त्रुटि_सं));
	पूर्ण
पूर्ण

अटल व्योम add_reloc(काष्ठा relocs *r, uपूर्णांक32_t offset, अचिन्हित type)
अणु
	/* Relocation representation in binary table:
	 * |76543210|76543210|76543210|76543210|
	 * |  Type  |  offset from _text >> 2  |
	 */
	offset >>= 2;
	अगर (offset > 0x00FFFFFF)
		die("Kernel image exceeds maximum size for relocation!\n");

	offset = (offset & 0x00FFFFFF) | ((type & 0xFF) << 24);

	अगर (r->count == r->size) अणु
		अचिन्हित दीर्घ newsize = r->size + 50000;
		व्योम *mem = पुनः_स्मृति(r->offset, newsize * माप(r->offset[0]));

		अगर (!mem)
			die("realloc failed\n");

		r->offset = mem;
		r->size = newsize;
	पूर्ण
	r->offset[r->count++] = offset;
पूर्ण

अटल व्योम walk_relocs(पूर्णांक (*process)(काष्ठा section *sec, Elf_Rel *rel,
			Elf_Sym *sym, स्थिर अक्षर *symname))
अणु
	पूर्णांक i;

	/* Walk through the relocations */
	क्रम (i = 0; i < ehdr.e_shnum; i++) अणु
		अक्षर *sym_strtab;
		Elf_Sym *sh_symtab;
		काष्ठा section *sec_applies, *sec_symtab;
		पूर्णांक j;
		काष्ठा section *sec = &secs[i];

		अगर (sec->shdr.sh_type != SHT_REL_TYPE)
			जारी;

		sec_symtab  = sec->link;
		sec_applies = &secs[sec->shdr.sh_info];
		अगर (!(sec_applies->shdr.sh_flags & SHF_ALLOC))
			जारी;

		sh_symtab = sec_symtab->symtab;
		sym_strtab = sec_symtab->link->strtab;
		क्रम (j = 0; j < sec->shdr.sh_size/माप(Elf_Rel); j++) अणु
			Elf_Rel *rel = &sec->reltab[j];
			Elf_Sym *sym = &sh_symtab[ELF_R_SYM(rel->r_info)];
			स्थिर अक्षर *symname = sym_name(sym_strtab, sym);

			process(sec, rel, sym, symname);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक करो_reloc(काष्ठा section *sec, Elf_Rel *rel, Elf_Sym *sym,
		      स्थिर अक्षर *symname)
अणु
	अचिन्हित r_type = ELF_R_TYPE(rel->r_info);
	अचिन्हित bind = ELF_ST_BIND(sym->st_info);

	अगर ((bind == STB_WEAK) && (sym->st_value == 0)) अणु
		/* Don't relocate weak symbols without a target */
		वापस 0;
	पूर्ण

	अगर (regex_skip_reloc(symname))
		वापस 0;

	चयन (r_type) अणु
	हाल R_MIPS_NONE:
	हाल R_MIPS_REL32:
	हाल R_MIPS_PC16:
	हाल R_MIPS_PC21_S2:
	हाल R_MIPS_PC26_S2:
		/*
		 * NONE can be ignored and PC relative relocations करोn't
		 * need to be adjusted.
		 */
	हाल R_MIPS_HIGHEST:
	हाल R_MIPS_HIGHER:
		/* We support relocating within the same 4Gb segment only,
		 * thus leaving the top 32bits unchanged
		 */
	हाल R_MIPS_LO16:
		/* We support relocating by 64k jumps only
		 * thus leaving the bottom 16bits unchanged
		 */
		अवरोध;

	हाल R_MIPS_64:
	हाल R_MIPS_32:
	हाल R_MIPS_26:
	हाल R_MIPS_HI16:
		add_reloc(&relocs, rel->r_offset, r_type);
		अवरोध;

	शेष:
		die("Unsupported relocation type: %s (%d)\n",
		    rel_type(r_type), r_type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_reloc_as_bin(uपूर्णांक32_t v, खाता *f)
अणु
	अचिन्हित अक्षर buf[4];

	v = cpu_to_elf32(v);

	स_नकल(buf, &v, माप(uपूर्णांक32_t));
	वापस ख_डालो(buf, 1, 4, f);
पूर्ण

अटल पूर्णांक ग_लिखो_reloc_as_text(uपूर्णांक32_t v, खाता *f)
अणु
	पूर्णांक res;

	res = ख_लिखो(f, "\t.long 0x%08"PRIx32"\n", v);
	अगर (res < 0)
		वापस res;
	अन्यथा
		वापस माप(uपूर्णांक32_t);
पूर्ण

अटल व्योम emit_relocs(पूर्णांक as_text, पूर्णांक as_bin, खाता *outf)
अणु
	पूर्णांक i;
	पूर्णांक (*ग_लिखो_reloc)(uपूर्णांक32_t, खाता *) = ग_लिखो_reloc_as_bin;
	पूर्णांक size = 0;
	पूर्णांक size_reserved;
	काष्ठा section *sec_reloc;

	sec_reloc = sec_lookup(".data.reloc");
	अगर (!sec_reloc)
		die("Could not find relocation section\n");

	size_reserved = sec_reloc->shdr.sh_size;

	/* Collect up the relocations */
	walk_relocs(करो_reloc);

	/* Prपूर्णांक the relocations */
	अगर (as_text) अणु
		/* Prपूर्णांक the relocations in a क्रमm suitable that
		 * gas will like.
		 */
		म_लिखो(".section \".data.reloc\",\"a\"\n");
		म_लिखो(".balign 4\n");
		/* Output text to मानक_निकास */
		ग_लिखो_reloc = ग_लिखो_reloc_as_text;
		outf = मानक_निकास;
	पूर्ण अन्यथा अगर (as_bin) अणु
		/* Output raw binary to मानक_निकास */
		outf = मानक_निकास;
	पूर्ण अन्यथा अणु
		/* Seek to offset of the relocation section.
		* Each relocation is then written पूर्णांकo the
		* vmlinux kernel image.
		*/
		अगर (ख_जाओ(outf, sec_reloc->shdr.sh_offset, शुरू_से) < 0) अणु
			die("Seek to %d failed: %s\n",
				sec_reloc->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < relocs.count; i++)
		size += ग_लिखो_reloc(relocs.offset[i], outf);

	/* Prपूर्णांक a stop, but only अगर we've actually written some relocs */
	अगर (size)
		size += ग_लिखो_reloc(0, outf);

	अगर (size > size_reserved)
		/* Die, but suggest a value क्रम CONFIG_RELOCATION_TABLE_SIZE
		 * which will fix this problem and allow a bit of headroom
		 * अगर more kernel features are enabled
		 */
		die("Relocations overflow available space!\n" \
		    "Please adjust CONFIG_RELOCATION_TABLE_SIZE " \
		    "to at least 0x%08x\n", (size + 0x1000) & ~0xFFF);
पूर्ण

/*
 * As an aid to debugging problems with dअगरferent linkers
 * prपूर्णांक summary inक्रमmation about the relocs.
 * Since dअगरferent linkers tend to emit the sections in
 * dअगरferent orders we use the section names in the output.
 */
अटल पूर्णांक करो_reloc_info(काष्ठा section *sec, Elf_Rel *rel, ElfW(Sym) *sym,
				स्थिर अक्षर *symname)
अणु
	म_लिखो("%16s  0x%08x  %16s  %40s  %16s\n",
		sec_name(sec->shdr.sh_info),
		(अचिन्हित पूर्णांक)rel->r_offset,
		rel_type(ELF_R_TYPE(rel->r_info)),
		symname,
		sec_name(sym->st_shndx));
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_reloc_info(व्योम)
अणु
	म_लिखो("%16s  %10s  %16s  %40s  %16s\n",
		"reloc section",
		"offset",
		"reloc type",
		"symbol",
		"symbol section");
	walk_relocs(करो_reloc_info);
पूर्ण

#अगर ELF_BITS == 64
# define process process_64
#अन्यथा
# define process process_32
#पूर्ण_अगर

व्योम process(खाता *fp, पूर्णांक as_text, पूर्णांक as_bin,
	     पूर्णांक show_reloc_info, पूर्णांक keep_relocs)
अणु
	regex_init();
	पढ़ो_ehdr(fp);
	पढ़ो_shdrs(fp);
	पढ़ो_strtअसल(fp);
	पढ़ो_symtअसल(fp);
	पढ़ो_relocs(fp);
	अगर (show_reloc_info) अणु
		prपूर्णांक_reloc_info();
		वापस;
	पूर्ण
	emit_relocs(as_text, as_bin, fp);
	अगर (!keep_relocs)
		हटाओ_relocs(fp);
पूर्ण
