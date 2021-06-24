<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Alex Smith <alex.smith@imgtec.com>
 */

अटल अंतरभूत bool FUNC(patch_vdso)(स्थिर अक्षर *path, व्योम *vdso)
अणु
	स्थिर ELF(Ehdr) *ehdr = vdso;
	व्योम *shdrs;
	ELF(Shdr) *shdr;
	अक्षर *shstrtab, *name;
	uपूर्णांक16_t sh_count, sh_entsize, i;

	shdrs = vdso + FUNC(swap_uपूर्णांक)(ehdr->e_shoff);
	sh_count = swap_uपूर्णांक16(ehdr->e_shnum);
	sh_entsize = swap_uपूर्णांक16(ehdr->e_shentsize);

	shdr = shdrs + (sh_entsize * swap_uपूर्णांक16(ehdr->e_shstrndx));
	shstrtab = vdso + FUNC(swap_uपूर्णांक)(shdr->sh_offset);

	क्रम (i = 0; i < sh_count; i++) अणु
		shdr = shdrs + (i * sh_entsize);
		name = shstrtab + swap_uपूर्णांक32(shdr->sh_name);

		/*
		 * Ensure there are no relocation sections - ld.so करोes not
		 * relocate the VDSO so अगर there are relocations things will
		 * अवरोध.
		 */
		चयन (swap_uपूर्णांक32(shdr->sh_type)) अणु
		हाल SHT_REL:
		हाल SHT_RELA:
			ख_लिखो(मानक_त्रुटि,
				"%s: '%s' contains relocation sections\n",
				program_name, path);
			वापस false;
		पूर्ण

		/* Check क्रम existing sections. */
		अगर (म_भेद(name, ".MIPS.abiflags") == 0) अणु
			ख_लिखो(मानक_त्रुटि,
				"%s: '%s' already contains a '.MIPS.abiflags' section\n",
				program_name, path);
			वापस false;
		पूर्ण

		अगर (म_भेद(name, ".mips_abiflags") == 0) अणु
			म_नकल(name, ".MIPS.abiflags");
			shdr->sh_type = swap_uपूर्णांक32(SHT_MIPS_ABIFLAGS);
			shdr->sh_entsize = shdr->sh_size;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत bool FUNC(get_symbols)(स्थिर अक्षर *path, व्योम *vdso)
अणु
	स्थिर ELF(Ehdr) *ehdr = vdso;
	व्योम *shdrs, *symtab;
	ELF(Shdr) *shdr;
	स्थिर ELF(Sym) *sym;
	अक्षर *strtab, *name;
	uपूर्णांक16_t sh_count, sh_entsize, st_count, st_entsize, i, j;
	uपूर्णांक64_t offset;
	uपूर्णांक32_t flags;

	shdrs = vdso + FUNC(swap_uपूर्णांक)(ehdr->e_shoff);
	sh_count = swap_uपूर्णांक16(ehdr->e_shnum);
	sh_entsize = swap_uपूर्णांक16(ehdr->e_shentsize);

	क्रम (i = 0; i < sh_count; i++) अणु
		shdr = shdrs + (i * sh_entsize);

		अगर (swap_uपूर्णांक32(shdr->sh_type) == SHT_SYMTAB)
			अवरोध;
	पूर्ण

	अगर (i == sh_count) अणु
		ख_लिखो(मानक_त्रुटि, "%s: '%s' has no symbol table\n", program_name,
			path);
		वापस false;
	पूर्ण

	/* Get flags */
	flags = swap_uपूर्णांक32(ehdr->e_flags);
	अगर (elf_class == ELFCLASS64)
		elf_abi = ABI_N64;
	अन्यथा अगर (flags & EF_MIPS_ABI2)
		elf_abi = ABI_N32;
	अन्यथा
		elf_abi = ABI_O32;

	/* Get symbol table. */
	symtab = vdso + FUNC(swap_uपूर्णांक)(shdr->sh_offset);
	st_entsize = FUNC(swap_uपूर्णांक)(shdr->sh_entsize);
	st_count = FUNC(swap_uपूर्णांक)(shdr->sh_size) / st_entsize;

	/* Get string table. */
	shdr = shdrs + (swap_uपूर्णांक32(shdr->sh_link) * sh_entsize);
	strtab = vdso + FUNC(swap_uपूर्णांक)(shdr->sh_offset);

	/* Write offsets क्रम symbols needed by the kernel. */
	क्रम (i = 0; vdso_symbols[i].name; i++) अणु
		अगर (!(vdso_symbols[i].abis & elf_abi))
			जारी;

		क्रम (j = 0; j < st_count; j++) अणु
			sym = symtab + (j * st_entsize);
			name = strtab + swap_uपूर्णांक32(sym->st_name);

			अगर (!म_भेद(name, vdso_symbols[i].name)) अणु
				offset = FUNC(swap_uपूर्णांक)(sym->st_value);

				ख_लिखो(out_file,
					"\t.%s = 0x%" PRIx64 ",\n",
					vdso_symbols[i].offset_name, offset);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (j == st_count) अणु
			ख_लिखो(मानक_त्रुटि,
				"%s: '%s' is missing required symbol '%s'\n",
				program_name, path, vdso_symbols[i].name);
			वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण
