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

अटल Elf_Ehdr		ehdr;
अटल अचिन्हित दीर्घ	shnum;
अटल अचिन्हित पूर्णांक	shstrndx;

काष्ठा relocs अणु
	uपूर्णांक32_t	*offset;
	अचिन्हित दीर्घ	count;
	अचिन्हित दीर्घ	size;
पूर्ण;

अटल काष्ठा relocs relocs16;
अटल काष्ठा relocs relocs32;
#अगर ELF_BITS == 64
अटल काष्ठा relocs relocs32neg;
अटल काष्ठा relocs relocs64;
#पूर्ण_अगर

काष्ठा section अणु
	Elf_Shdr       shdr;
	काष्ठा section *link;
	Elf_Sym        *symtab;
	Elf_Rel        *reltab;
	अक्षर           *strtab;
पूर्ण;
अटल काष्ठा section *secs;

अटल स्थिर अक्षर * स्थिर sym_regex_kernel[S_NSYMTYPES] = अणु
/*
 * Following symbols have been audited. There values are स्थिरant and करो
 * not change अगर bzImage is loaded at a dअगरferent physical address than
 * the address क्रम which it has been compiled. Don't warn user about
 * असलolute relocations present w.r.t these symbols.
 */
	[S_ABS] =
	"^(xen_irq_disable_direct_reloc$|"
	"xen_save_fl_direct_reloc$|"
	"VDSO|"
	"__crc_)",

/*
 * These symbols are known to be relative, even अगर the linker marks them
 * as असलolute (typically defined outside any section in the linker script.)
 */
	[S_REL] =
	"^(__init_(begin|end)|"
	"__x86_cpu_dev_(start|end)|"
	"(__parainstructions|__alt_instructions)(|_end)|"
	"(__iommu_table|__apicdrivers|__smp_locks)(|_end)|"
	"__(start|end)_pci_.*|"
	"__(start|end)_builtin_fw|"
	"__(start|stop)___ksymtab(|_gpl)|"
	"__(start|stop)___kcrctab(|_gpl)|"
	"__(start|stop)___param|"
	"__(start|stop)___modver|"
	"__(start|stop)___bug_table|"
	"__tracedata_(start|end)|"
	"__(start|stop)_notes|"
	"__end_rodata|"
	"__end_rodata_aligned|"
	"__initramfs_start|"
	"(jiffies|jiffies_64)|"
#अगर ELF_BITS == 64
	"__per_cpu_load|"
	"init_per_cpu__.*|"
	"__end_rodata_hpage_align|"
#पूर्ण_अगर
	"__vvar_page|"
	"_end)$"
पूर्ण;


अटल स्थिर अक्षर * स्थिर sym_regex_realmode[S_NSYMTYPES] = अणु
/*
 * These symbols are known to be relative, even अगर the linker marks them
 * as असलolute (typically defined outside any section in the linker script.)
 */
	[S_REL] =
	"^pa_",

/*
 * These are 16-bit segment symbols when compiling 16-bit code.
 */
	[S_SEG] =
	"^real_mode_seg$",

/*
 * These are offsets beदीर्घing to segments, as opposed to linear addresses,
 * when compiling 16-bit code.
 */
	[S_LIN] =
	"^pa_",
पूर्ण;

अटल स्थिर अक्षर * स्थिर *sym_regex;

अटल regex_t sym_regex_c[S_NSYMTYPES];
अटल पूर्णांक is_reloc(क्रमागत symtype type, स्थिर अक्षर *sym_name)
अणु
	वापस sym_regex[type] &&
		!regexec(&sym_regex_c[type], sym_name, 0, शून्य, 0);
पूर्ण

अटल व्योम regex_init(पूर्णांक use_real_mode)
अणु
        अक्षर errbuf[128];
        पूर्णांक err;
	पूर्णांक i;

	अगर (use_real_mode)
		sym_regex = sym_regex_realmode;
	अन्यथा
		sym_regex = sym_regex_kernel;

	क्रम (i = 0; i < S_NSYMTYPES; i++) अणु
		अगर (!sym_regex[i])
			जारी;

		err = regcomp(&sym_regex_c[i], sym_regex[i],
			      REG_EXTENDED|REG_NOSUB);

		अगर (err) अणु
			regerror(err, &sym_regex_c[i], errbuf, माप(errbuf));
			die("%s", errbuf);
		पूर्ण
        पूर्ण
पूर्ण

अटल स्थिर अक्षर *sym_type(अचिन्हित type)
अणु
	अटल स्थिर अक्षर *type_name[] = अणु
#घोषणा SYM_TYPE(X) [X] = #X
		SYM_TYPE(STT_NOTYPE),
		SYM_TYPE(STT_OBJECT),
		SYM_TYPE(STT_FUNC),
		SYM_TYPE(STT_SECTION),
		SYM_TYPE(STT_खाता),
		SYM_TYPE(STT_COMMON),
		SYM_TYPE(STT_TLS),
#अघोषित SYM_TYPE
	पूर्ण;
	स्थिर अक्षर *name = "unknown sym type name";
	अगर (type < ARRAY_SIZE(type_name)) अणु
		name = type_name[type];
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर अक्षर *sym_bind(अचिन्हित bind)
अणु
	अटल स्थिर अक्षर *bind_name[] = अणु
#घोषणा SYM_BIND(X) [X] = #X
		SYM_BIND(STB_LOCAL),
		SYM_BIND(STB_GLOBAL),
		SYM_BIND(STB_WEAK),
#अघोषित SYM_BIND
	पूर्ण;
	स्थिर अक्षर *name = "unknown sym bind name";
	अगर (bind < ARRAY_SIZE(bind_name)) अणु
		name = bind_name[bind];
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर अक्षर *sym_visibility(अचिन्हित visibility)
अणु
	अटल स्थिर अक्षर *visibility_name[] = अणु
#घोषणा SYM_VISIBILITY(X) [X] = #X
		SYM_VISIBILITY(STV_DEFAULT),
		SYM_VISIBILITY(STV_INTERNAL),
		SYM_VISIBILITY(STV_HIDDEN),
		SYM_VISIBILITY(STV_PROTECTED),
#अघोषित SYM_VISIBILITY
	पूर्ण;
	स्थिर अक्षर *name = "unknown sym visibility name";
	अगर (visibility < ARRAY_SIZE(visibility_name)) अणु
		name = visibility_name[visibility];
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर अक्षर *rel_type(अचिन्हित type)
अणु
	अटल स्थिर अक्षर *type_name[] = अणु
#घोषणा REL_TYPE(X) [X] = #X
#अगर ELF_BITS == 64
		REL_TYPE(R_X86_64_NONE),
		REL_TYPE(R_X86_64_64),
		REL_TYPE(R_X86_64_PC64),
		REL_TYPE(R_X86_64_PC32),
		REL_TYPE(R_X86_64_GOT32),
		REL_TYPE(R_X86_64_PLT32),
		REL_TYPE(R_X86_64_COPY),
		REL_TYPE(R_X86_64_GLOB_DAT),
		REL_TYPE(R_X86_64_JUMP_SLOT),
		REL_TYPE(R_X86_64_RELATIVE),
		REL_TYPE(R_X86_64_GOTPCREL),
		REL_TYPE(R_X86_64_32),
		REL_TYPE(R_X86_64_32S),
		REL_TYPE(R_X86_64_16),
		REL_TYPE(R_X86_64_PC16),
		REL_TYPE(R_X86_64_8),
		REL_TYPE(R_X86_64_PC8),
#अन्यथा
		REL_TYPE(R_386_NONE),
		REL_TYPE(R_386_32),
		REL_TYPE(R_386_PC32),
		REL_TYPE(R_386_GOT32),
		REL_TYPE(R_386_PLT32),
		REL_TYPE(R_386_COPY),
		REL_TYPE(R_386_GLOB_DAT),
		REL_TYPE(R_386_JMP_SLOT),
		REL_TYPE(R_386_RELATIVE),
		REL_TYPE(R_386_GOTOFF),
		REL_TYPE(R_386_GOTPC),
		REL_TYPE(R_386_8),
		REL_TYPE(R_386_PC8),
		REL_TYPE(R_386_16),
		REL_TYPE(R_386_PC16),
#पूर्ण_अगर
#अघोषित REL_TYPE
	पूर्ण;
	स्थिर अक्षर *name = "unknown type rel type name";
	अगर (type < ARRAY_SIZE(type_name) && type_name[type]) अणु
		name = type_name[type];
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर अक्षर *sec_name(अचिन्हित shndx)
अणु
	स्थिर अक्षर *sec_strtab;
	स्थिर अक्षर *name;
	sec_strtab = secs[shstrndx].strtab;
	name = "<noname>";
	अगर (shndx < shnum) अणु
		name = sec_strtab + secs[shndx].shdr.sh_name;
	पूर्ण
	अन्यथा अगर (shndx == SHN_ABS) अणु
		name = "ABSOLUTE";
	पूर्ण
	अन्यथा अगर (shndx == SHN_COMMON) अणु
		name = "COMMON";
	पूर्ण
	वापस name;
पूर्ण

अटल स्थिर अक्षर *sym_name(स्थिर अक्षर *sym_strtab, Elf_Sym *sym)
अणु
	स्थिर अक्षर *name;
	name = "<noname>";
	अगर (sym->st_name) अणु
		name = sym_strtab + sym->st_name;
	पूर्ण
	अन्यथा अणु
		name = sec_name(sym->st_shndx);
	पूर्ण
	वापस name;
पूर्ण

अटल Elf_Sym *sym_lookup(स्थिर अक्षर *symname)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		दीर्घ nsyms;
		अक्षर *strtab;
		Elf_Sym *symtab;
		Elf_Sym *sym;

		अगर (sec->shdr.sh_type != SHT_SYMTAB)
			जारी;

		nsyms = sec->shdr.sh_size/माप(Elf_Sym);
		symtab = sec->symtab;
		strtab = sec->link->strtab;

		क्रम (sym = symtab; --nsyms >= 0; sym++) अणु
			अगर (!sym->st_name)
				जारी;
			अगर (म_भेद(symname, strtab + sym->st_name) == 0)
				वापस sym;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर BYTE_ORDER == LITTLE_ENDIAN
#घोषणा le16_to_cpu(val) (val)
#घोषणा le32_to_cpu(val) (val)
#घोषणा le64_to_cpu(val) (val)
#पूर्ण_अगर
#अगर BYTE_ORDER == BIG_ENDIAN
#घोषणा le16_to_cpu(val) bswap_16(val)
#घोषणा le32_to_cpu(val) bswap_32(val)
#घोषणा le64_to_cpu(val) bswap_64(val)
#पूर्ण_अगर

अटल uपूर्णांक16_t elf16_to_cpu(uपूर्णांक16_t val)
अणु
	वापस le16_to_cpu(val);
पूर्ण

अटल uपूर्णांक32_t elf32_to_cpu(uपूर्णांक32_t val)
अणु
	वापस le32_to_cpu(val);
पूर्ण

#घोषणा elf_half_to_cpu(x)	elf16_to_cpu(x)
#घोषणा elf_word_to_cpu(x)	elf32_to_cpu(x)

#अगर ELF_BITS == 64
अटल uपूर्णांक64_t elf64_to_cpu(uपूर्णांक64_t val)
अणु
        वापस le64_to_cpu(val);
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
	अगर (ख_पढ़ो(&ehdr, माप(ehdr), 1, fp) != 1) अणु
		die("Cannot read ELF header: %s\n",
			म_त्रुटि(त्रुटि_सं));
	पूर्ण
	अगर (स_भेद(ehdr.e_ident, ELFMAG, SELFMAG) != 0) अणु
		die("No ELF magic\n");
	पूर्ण
	अगर (ehdr.e_ident[EI_CLASS] != ELF_CLASS) अणु
		die("Not a %d bit executable\n", ELF_BITS);
	पूर्ण
	अगर (ehdr.e_ident[EI_DATA] != ELFDATA2LSB) अणु
		die("Not a LSB ELF executable\n");
	पूर्ण
	अगर (ehdr.e_ident[EI_VERSION] != EV_CURRENT) अणु
		die("Unknown ELF version\n");
	पूर्ण
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

	shnum = ehdr.e_shnum;
	shstrndx = ehdr.e_shstrndx;

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


	अगर (shnum == SHN_UNDEF || shstrndx == SHN_XINDEX) अणु
		Elf_Shdr shdr;

		अगर (ख_जाओ(fp, ehdr.e_shoff, शुरू_से) < 0)
			die("Seek to %d failed: %s\n", ehdr.e_shoff, म_त्रुटि(त्रुटि_सं));

		अगर (ख_पढ़ो(&shdr, माप(shdr), 1, fp) != 1)
			die("Cannot read initial ELF section header: %s\n", म_त्रुटि(त्रुटि_सं));

		अगर (shnum == SHN_UNDEF)
			shnum = elf_xword_to_cpu(shdr.sh_size);

		अगर (shstrndx == SHN_XINDEX)
			shstrndx = elf_word_to_cpu(shdr.sh_link);
	पूर्ण

	अगर (shstrndx >= shnum)
		die("String table index out of bounds\n");
पूर्ण

अटल व्योम पढ़ो_shdrs(खाता *fp)
अणु
	पूर्णांक i;
	Elf_Shdr shdr;

	secs = सुस्मृति(shnum, माप(काष्ठा section));
	अगर (!secs) अणु
		die("Unable to allocate %d section headers\n",
		    shnum);
	पूर्ण
	अगर (ख_जाओ(fp, ehdr.e_shoff, शुरू_से) < 0) अणु
		die("Seek to %d failed: %s\n",
			ehdr.e_shoff, म_त्रुटि(त्रुटि_सं));
	पूर्ण
	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		अगर (ख_पढ़ो(&shdr, माप(shdr), 1, fp) != 1)
			die("Cannot read ELF section headers %d/%d: %s\n",
			    i, shnum, म_त्रुटि(त्रुटि_सं));
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
		अगर (sec->shdr.sh_link < shnum)
			sec->link = &secs[sec->shdr.sh_link];
	पूर्ण

पूर्ण

अटल व्योम पढ़ो_strtअसल(खाता *fp)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		अगर (sec->shdr.sh_type != SHT_STRTAB) अणु
			जारी;
		पूर्ण
		sec->strtab = दो_स्मृति(sec->shdr.sh_size);
		अगर (!sec->strtab) अणु
			die("malloc of %d bytes for strtab failed\n",
				sec->shdr.sh_size);
		पूर्ण
		अगर (ख_जाओ(fp, sec->shdr.sh_offset, शुरू_से) < 0) अणु
			die("Seek to %d failed: %s\n",
				sec->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));
		पूर्ण
		अगर (ख_पढ़ो(sec->strtab, 1, sec->shdr.sh_size, fp)
		    != sec->shdr.sh_size) अणु
			die("Cannot read symbol table: %s\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम पढ़ो_symtअसल(खाता *fp)
अणु
	पूर्णांक i,j;
	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		अगर (sec->shdr.sh_type != SHT_SYMTAB) अणु
			जारी;
		पूर्ण
		sec->symtab = दो_स्मृति(sec->shdr.sh_size);
		अगर (!sec->symtab) अणु
			die("malloc of %d bytes for symtab failed\n",
				sec->shdr.sh_size);
		पूर्ण
		अगर (ख_जाओ(fp, sec->shdr.sh_offset, शुरू_से) < 0) अणु
			die("Seek to %d failed: %s\n",
				sec->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));
		पूर्ण
		अगर (ख_पढ़ो(sec->symtab, 1, sec->shdr.sh_size, fp)
		    != sec->shdr.sh_size) अणु
			die("Cannot read symbol table: %s\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण
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
	पूर्णांक i,j;
	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		अगर (sec->shdr.sh_type != SHT_REL_TYPE) अणु
			जारी;
		पूर्ण
		sec->reltab = दो_स्मृति(sec->shdr.sh_size);
		अगर (!sec->reltab) अणु
			die("malloc of %d bytes for relocs failed\n",
				sec->shdr.sh_size);
		पूर्ण
		अगर (ख_जाओ(fp, sec->shdr.sh_offset, शुरू_से) < 0) अणु
			die("Seek to %d failed: %s\n",
				sec->shdr.sh_offset, म_त्रुटि(त्रुटि_सं));
		पूर्ण
		अगर (ख_पढ़ो(sec->reltab, 1, sec->shdr.sh_size, fp)
		    != sec->shdr.sh_size) अणु
			die("Cannot read symbol table: %s\n",
				म_त्रुटि(त्रुटि_सं));
		पूर्ण
		क्रम (j = 0; j < sec->shdr.sh_size/माप(Elf_Rel); j++) अणु
			Elf_Rel *rel = &sec->reltab[j];
			rel->r_offset = elf_addr_to_cpu(rel->r_offset);
			rel->r_info   = elf_xword_to_cpu(rel->r_info);
#अगर (SHT_REL_TYPE == SHT_RELA)
			rel->r_addend = elf_xword_to_cpu(rel->r_addend);
#पूर्ण_अगर
		पूर्ण
	पूर्ण
पूर्ण


अटल व्योम prपूर्णांक_असलolute_symbols(व्योम)
अणु
	पूर्णांक i;
	स्थिर अक्षर *क्रमmat;

	अगर (ELF_BITS == 64)
		क्रमmat = "%5d %016"PRIx64" %5"PRId64" %10s %10s %12s %s\n";
	अन्यथा
		क्रमmat = "%5d %08"PRIx32"  %5"PRId32" %10s %10s %12s %s\n";

	म_लिखो("Absolute symbols\n");
	म_लिखो(" Num:    Value Size  Type       Bind        Visibility  Name\n");
	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		अक्षर *sym_strtab;
		पूर्णांक j;

		अगर (sec->shdr.sh_type != SHT_SYMTAB) अणु
			जारी;
		पूर्ण
		sym_strtab = sec->link->strtab;
		क्रम (j = 0; j < sec->shdr.sh_size/माप(Elf_Sym); j++) अणु
			Elf_Sym *sym;
			स्थिर अक्षर *name;
			sym = &sec->symtab[j];
			name = sym_name(sym_strtab, sym);
			अगर (sym->st_shndx != SHN_ABS) अणु
				जारी;
			पूर्ण
			म_लिखो(क्रमmat,
				j, sym->st_value, sym->st_size,
				sym_type(ELF_ST_TYPE(sym->st_info)),
				sym_bind(ELF_ST_BIND(sym->st_info)),
				sym_visibility(ELF_ST_VISIBILITY(sym->st_other)),
				name);
		पूर्ण
	पूर्ण
	म_लिखो("\n");
पूर्ण

अटल व्योम prपूर्णांक_असलolute_relocs(व्योम)
अणु
	पूर्णांक i, prपूर्णांकed = 0;
	स्थिर अक्षर *क्रमmat;

	अगर (ELF_BITS == 64)
		क्रमmat = "%016"PRIx64" %016"PRIx64" %10s %016"PRIx64"  %s\n";
	अन्यथा
		क्रमmat = "%08"PRIx32" %08"PRIx32" %10s %08"PRIx32"  %s\n";

	क्रम (i = 0; i < shnum; i++) अणु
		काष्ठा section *sec = &secs[i];
		काष्ठा section *sec_applies, *sec_symtab;
		अक्षर *sym_strtab;
		Elf_Sym *sh_symtab;
		पूर्णांक j;
		अगर (sec->shdr.sh_type != SHT_REL_TYPE) अणु
			जारी;
		पूर्ण
		sec_symtab  = sec->link;
		sec_applies = &secs[sec->shdr.sh_info];
		अगर (!(sec_applies->shdr.sh_flags & SHF_ALLOC)) अणु
			जारी;
		पूर्ण
		sh_symtab  = sec_symtab->symtab;
		sym_strtab = sec_symtab->link->strtab;
		क्रम (j = 0; j < sec->shdr.sh_size/माप(Elf_Rel); j++) अणु
			Elf_Rel *rel;
			Elf_Sym *sym;
			स्थिर अक्षर *name;
			rel = &sec->reltab[j];
			sym = &sh_symtab[ELF_R_SYM(rel->r_info)];
			name = sym_name(sym_strtab, sym);
			अगर (sym->st_shndx != SHN_ABS) अणु
				जारी;
			पूर्ण

			/* Absolute symbols are not relocated अगर bzImage is
			 * loaded at a non-compiled address. Display a warning
			 * to user at compile समय about the असलolute
			 * relocations present.
			 *
			 * User need to audit the code to make sure
			 * some symbols which should have been section
			 * relative have not become असलolute because of some
			 * linker optimization or wrong programming usage.
			 *
			 * Beक्रमe warning check अगर this असलolute symbol
			 * relocation is harmless.
			 */
			अगर (is_reloc(S_ABS, name) || is_reloc(S_REL, name))
				जारी;

			अगर (!prपूर्णांकed) अणु
				म_लिखो("WARNING: Absolute relocations"
					" present\n");
				म_लिखो("Offset     Info     Type     Sym.Value "
					"Sym.Name\n");
				prपूर्णांकed = 1;
			पूर्ण

			म_लिखो(क्रमmat,
				rel->r_offset,
				rel->r_info,
				rel_type(ELF_R_TYPE(rel->r_info)),
				sym->st_value,
				name);
		पूर्ण
	पूर्ण

	अगर (prपूर्णांकed)
		म_लिखो("\n");
पूर्ण

अटल व्योम add_reloc(काष्ठा relocs *r, uपूर्णांक32_t offset)
अणु
	अगर (r->count == r->size) अणु
		अचिन्हित दीर्घ newsize = r->size + 50000;
		व्योम *mem = पुनः_स्मृति(r->offset, newsize * माप(r->offset[0]));

		अगर (!mem)
			die("realloc of %ld entries for relocs failed\n",
                                newsize);
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
	क्रम (i = 0; i < shnum; i++) अणु
		अक्षर *sym_strtab;
		Elf_Sym *sh_symtab;
		काष्ठा section *sec_applies, *sec_symtab;
		पूर्णांक j;
		काष्ठा section *sec = &secs[i];

		अगर (sec->shdr.sh_type != SHT_REL_TYPE) अणु
			जारी;
		पूर्ण
		sec_symtab  = sec->link;
		sec_applies = &secs[sec->shdr.sh_info];
		अगर (!(sec_applies->shdr.sh_flags & SHF_ALLOC)) अणु
			जारी;
		पूर्ण
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

/*
 * The .data..percpu section is a special हाल क्रम x86_64 SMP kernels.
 * It is used to initialize the actual per_cpu areas and to provide
 * definitions क्रम the per_cpu variables that correspond to their offsets
 * within the percpu area. Since the values of all of the symbols need
 * to be offsets from the start of the per_cpu area the भव address
 * (sh_addr) of .data..percpu is 0 in SMP kernels.
 *
 * This means that:
 *
 *	Relocations that reference symbols in the per_cpu area करो not
 *	need further relocation (since the value is an offset relative
 *	to the start of the per_cpu area that करोes not change).
 *
 *	Relocations that apply to the per_cpu area need to have their
 *	offset adjusted by by the value of __per_cpu_load to make them
 *	poपूर्णांक to the correct place in the loaded image (because the
 *	भव address of .data..percpu is 0).
 *
 * For non SMP kernels .data..percpu is linked as part of the normal
 * kernel data and करोes not require special treaपंचांगent.
 *
 */
अटल पूर्णांक per_cpu_shndx	= -1;
अटल Elf_Addr per_cpu_load_addr;

अटल व्योम percpu_init(व्योम)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < shnum; i++) अणु
		ElfW(Sym) *sym;
		अगर (म_भेद(sec_name(i), ".data..percpu"))
			जारी;

		अगर (secs[i].shdr.sh_addr != 0)	/* non SMP kernel */
			वापस;

		sym = sym_lookup("__per_cpu_load");
		अगर (!sym)
			die("can't find __per_cpu_load\n");

		per_cpu_shndx = i;
		per_cpu_load_addr = sym->st_value;
		वापस;
	पूर्ण
पूर्ण

#अगर ELF_BITS == 64

/*
 * Check to see अगर a symbol lies in the .data..percpu section.
 *
 * The linker incorrectly associates some symbols with the
 * .data..percpu section so we also need to check the symbol
 * name to make sure that we classअगरy the symbol correctly.
 *
 * The GNU linker incorrectly associates:
 *	__init_begin
 *	__per_cpu_load
 *
 * The "gold" linker incorrectly associates:
 *	init_per_cpu__fixed_percpu_data
 *	init_per_cpu__gdt_page
 */
अटल पूर्णांक is_percpu_sym(ElfW(Sym) *sym, स्थिर अक्षर *symname)
अणु
	वापस (sym->st_shndx == per_cpu_shndx) &&
		म_भेद(symname, "__init_begin") &&
		म_भेद(symname, "__per_cpu_load") &&
		म_भेदन(symname, "init_per_cpu_", 13);
पूर्ण


अटल पूर्णांक करो_reloc64(काष्ठा section *sec, Elf_Rel *rel, ElfW(Sym) *sym,
		      स्थिर अक्षर *symname)
अणु
	अचिन्हित r_type = ELF64_R_TYPE(rel->r_info);
	ElfW(Addr) offset = rel->r_offset;
	पूर्णांक shn_असल = (sym->st_shndx == SHN_ABS) && !is_reloc(S_REL, symname);

	अगर (sym->st_shndx == SHN_UNDEF)
		वापस 0;

	/*
	 * Adjust the offset अगर this reloc applies to the percpu section.
	 */
	अगर (sec->shdr.sh_info == per_cpu_shndx)
		offset += per_cpu_load_addr;

	चयन (r_type) अणु
	हाल R_X86_64_NONE:
		/* NONE can be ignored. */
		अवरोध;

	हाल R_X86_64_PC32:
	हाल R_X86_64_PLT32:
		/*
		 * PC relative relocations करोn't need to be adjusted unless
		 * referencing a percpu symbol.
		 *
		 * NB: R_X86_64_PLT32 can be treated as R_X86_64_PC32.
		 */
		अगर (is_percpu_sym(sym, symname))
			add_reloc(&relocs32neg, offset);
		अवरोध;

	हाल R_X86_64_PC64:
		/*
		 * Only used by jump labels
		 */
		अगर (is_percpu_sym(sym, symname))
			die("Invalid R_X86_64_PC64 relocation against per-CPU symbol %s\n",
			    symname);
		अवरोध;

	हाल R_X86_64_32:
	हाल R_X86_64_32S:
	हाल R_X86_64_64:
		/*
		 * References to the percpu area करोn't need to be adjusted.
		 */
		अगर (is_percpu_sym(sym, symname))
			अवरोध;

		अगर (shn_असल) अणु
			/*
			 * Whitelisted असलolute symbols करो not require
			 * relocation.
			 */
			अगर (is_reloc(S_ABS, symname))
				अवरोध;

			die("Invalid absolute %s relocation: %s\n",
			    rel_type(r_type), symname);
			अवरोध;
		पूर्ण

		/*
		 * Relocation offsets क्रम 64 bit kernels are output
		 * as 32 bits and sign extended back to 64 bits when
		 * the relocations are processed.
		 * Make sure that the offset will fit.
		 */
		अगर ((पूर्णांक32_t)offset != (पूर्णांक64_t)offset)
			die("Relocation offset doesn't fit in 32 bits\n");

		अगर (r_type == R_X86_64_64)
			add_reloc(&relocs64, offset);
		अन्यथा
			add_reloc(&relocs32, offset);
		अवरोध;

	शेष:
		die("Unsupported relocation type: %s (%d)\n",
		    rel_type(r_type), r_type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा

अटल पूर्णांक करो_reloc32(काष्ठा section *sec, Elf_Rel *rel, Elf_Sym *sym,
		      स्थिर अक्षर *symname)
अणु
	अचिन्हित r_type = ELF32_R_TYPE(rel->r_info);
	पूर्णांक shn_असल = (sym->st_shndx == SHN_ABS) && !is_reloc(S_REL, symname);

	चयन (r_type) अणु
	हाल R_386_NONE:
	हाल R_386_PC32:
	हाल R_386_PC16:
	हाल R_386_PC8:
	हाल R_386_PLT32:
		/*
		 * NONE can be ignored and PC relative relocations करोn't need
		 * to be adjusted. Because sym must be defined, R_386_PLT32 can
		 * be treated the same way as R_386_PC32.
		 */
		अवरोध;

	हाल R_386_32:
		अगर (shn_असल) अणु
			/*
			 * Whitelisted असलolute symbols करो not require
			 * relocation.
			 */
			अगर (is_reloc(S_ABS, symname))
				अवरोध;

			die("Invalid absolute %s relocation: %s\n",
			    rel_type(r_type), symname);
			अवरोध;
		पूर्ण

		add_reloc(&relocs32, rel->r_offset);
		अवरोध;

	शेष:
		die("Unsupported relocation type: %s (%d)\n",
		    rel_type(r_type), r_type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक करो_reloc_real(काष्ठा section *sec, Elf_Rel *rel, Elf_Sym *sym,
			 स्थिर अक्षर *symname)
अणु
	अचिन्हित r_type = ELF32_R_TYPE(rel->r_info);
	पूर्णांक shn_असल = (sym->st_shndx == SHN_ABS) && !is_reloc(S_REL, symname);

	चयन (r_type) अणु
	हाल R_386_NONE:
	हाल R_386_PC32:
	हाल R_386_PC16:
	हाल R_386_PC8:
	हाल R_386_PLT32:
		/*
		 * NONE can be ignored and PC relative relocations करोn't need
		 * to be adjusted. Because sym must be defined, R_386_PLT32 can
		 * be treated the same way as R_386_PC32.
		 */
		अवरोध;

	हाल R_386_16:
		अगर (shn_असल) अणु
			/*
			 * Whitelisted असलolute symbols करो not require
			 * relocation.
			 */
			अगर (is_reloc(S_ABS, symname))
				अवरोध;

			अगर (is_reloc(S_SEG, symname)) अणु
				add_reloc(&relocs16, rel->r_offset);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!is_reloc(S_LIN, symname))
				अवरोध;
		पूर्ण
		die("Invalid %s %s relocation: %s\n",
		    shn_असल ? "absolute" : "relative",
		    rel_type(r_type), symname);
		अवरोध;

	हाल R_386_32:
		अगर (shn_असल) अणु
			/*
			 * Whitelisted असलolute symbols करो not require
			 * relocation.
			 */
			अगर (is_reloc(S_ABS, symname))
				अवरोध;

			अगर (is_reloc(S_REL, symname)) अणु
				add_reloc(&relocs32, rel->r_offset);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (is_reloc(S_LIN, symname))
				add_reloc(&relocs32, rel->r_offset);
			अवरोध;
		पूर्ण
		die("Invalid %s %s relocation: %s\n",
		    shn_असल ? "absolute" : "relative",
		    rel_type(r_type), symname);
		अवरोध;

	शेष:
		die("Unsupported relocation type: %s (%d)\n",
		    rel_type(r_type), r_type);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक cmp_relocs(स्थिर व्योम *va, स्थिर व्योम *vb)
अणु
	स्थिर uपूर्णांक32_t *a, *b;
	a = va; b = vb;
	वापस (*a == *b)? 0 : (*a > *b)? 1 : -1;
पूर्ण

अटल व्योम sort_relocs(काष्ठा relocs *r)
अणु
	क्विक(r->offset, r->count, माप(r->offset[0]), cmp_relocs);
पूर्ण

अटल पूर्णांक ग_लिखो32(uपूर्णांक32_t v, खाता *f)
अणु
	अचिन्हित अक्षर buf[4];

	put_unaligned_le32(v, buf);
	वापस ख_डालो(buf, 1, 4, f) == 4 ? 0 : -1;
पूर्ण

अटल पूर्णांक ग_लिखो32_as_text(uपूर्णांक32_t v, खाता *f)
अणु
	वापस ख_लिखो(f, "\t.long 0x%08"PRIx32"\n", v) > 0 ? 0 : -1;
पूर्ण

अटल व्योम emit_relocs(पूर्णांक as_text, पूर्णांक use_real_mode)
अणु
	पूर्णांक i;
	पूर्णांक (*ग_लिखो_reloc)(uपूर्णांक32_t, खाता *) = ग_लिखो32;
	पूर्णांक (*करो_reloc)(काष्ठा section *sec, Elf_Rel *rel, Elf_Sym *sym,
			स्थिर अक्षर *symname);

#अगर ELF_BITS == 64
	अगर (!use_real_mode)
		करो_reloc = करो_reloc64;
	अन्यथा
		die("--realmode not valid for a 64-bit ELF file");
#अन्यथा
	अगर (!use_real_mode)
		करो_reloc = करो_reloc32;
	अन्यथा
		करो_reloc = करो_reloc_real;
#पूर्ण_अगर

	/* Collect up the relocations */
	walk_relocs(करो_reloc);

	अगर (relocs16.count && !use_real_mode)
		die("Segment relocations found but --realmode not specified\n");

	/* Order the relocations क्रम more efficient processing */
	sort_relocs(&relocs32);
#अगर ELF_BITS == 64
	sort_relocs(&relocs32neg);
	sort_relocs(&relocs64);
#अन्यथा
	sort_relocs(&relocs16);
#पूर्ण_अगर

	/* Prपूर्णांक the relocations */
	अगर (as_text) अणु
		/* Prपूर्णांक the relocations in a क्रमm suitable that
		 * gas will like.
		 */
		म_लिखो(".section \".data.reloc\",\"a\"\n");
		म_लिखो(".balign 4\n");
		ग_लिखो_reloc = ग_लिखो32_as_text;
	पूर्ण

	अगर (use_real_mode) अणु
		ग_लिखो_reloc(relocs16.count, मानक_निकास);
		क्रम (i = 0; i < relocs16.count; i++)
			ग_लिखो_reloc(relocs16.offset[i], मानक_निकास);

		ग_लिखो_reloc(relocs32.count, मानक_निकास);
		क्रम (i = 0; i < relocs32.count; i++)
			ग_लिखो_reloc(relocs32.offset[i], मानक_निकास);
	पूर्ण अन्यथा अणु
#अगर ELF_BITS == 64
		/* Prपूर्णांक a stop */
		ग_लिखो_reloc(0, मानक_निकास);

		/* Now prपूर्णांक each relocation */
		क्रम (i = 0; i < relocs64.count; i++)
			ग_लिखो_reloc(relocs64.offset[i], मानक_निकास);

		/* Prपूर्णांक a stop */
		ग_लिखो_reloc(0, मानक_निकास);

		/* Now prपूर्णांक each inverse 32-bit relocation */
		क्रम (i = 0; i < relocs32neg.count; i++)
			ग_लिखो_reloc(relocs32neg.offset[i], मानक_निकास);
#पूर्ण_अगर

		/* Prपूर्णांक a stop */
		ग_लिखो_reloc(0, मानक_निकास);

		/* Now prपूर्णांक each relocation */
		क्रम (i = 0; i < relocs32.count; i++)
			ग_लिखो_reloc(relocs32.offset[i], मानक_निकास);
	पूर्ण
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
	म_लिखो("%s\t%s\t%s\t%s\n",
		sec_name(sec->shdr.sh_info),
		rel_type(ELF_R_TYPE(rel->r_info)),
		symname,
		sec_name(sym->st_shndx));
	वापस 0;
पूर्ण

अटल व्योम prपूर्णांक_reloc_info(व्योम)
अणु
	म_लिखो("reloc section\treloc type\tsymbol\tsymbol section\n");
	walk_relocs(करो_reloc_info);
पूर्ण

#अगर ELF_BITS == 64
# define process process_64
#अन्यथा
# define process process_32
#पूर्ण_अगर

व्योम process(खाता *fp, पूर्णांक use_real_mode, पूर्णांक as_text,
	     पूर्णांक show_असलolute_syms, पूर्णांक show_असलolute_relocs,
	     पूर्णांक show_reloc_info)
अणु
	regex_init(use_real_mode);
	पढ़ो_ehdr(fp);
	पढ़ो_shdrs(fp);
	पढ़ो_strtअसल(fp);
	पढ़ो_symtअसल(fp);
	पढ़ो_relocs(fp);
	अगर (ELF_BITS == 64)
		percpu_init();
	अगर (show_असलolute_syms) अणु
		prपूर्णांक_असलolute_symbols();
		वापस;
	पूर्ण
	अगर (show_असलolute_relocs) अणु
		prपूर्णांक_असलolute_relocs();
		वापस;
	पूर्ण
	अगर (show_reloc_info) अणु
		prपूर्णांक_reloc_info();
		वापस;
	पूर्ण
	emit_relocs(as_text, use_real_mode);
पूर्ण
