<शैली गुरु>
/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

/*
 * This file is included up to twice from vdso2c.c.  It generates code क्रम
 * 32-bit and 64-bit vDSOs.  We will eventually need both क्रम 64-bit builds,
 * since 32-bit vDSOs will then be built क्रम 32-bit userspace.
 */

अटल व्योम BITSFUNC(go)(व्योम *raw_addr, माप_प्रकार raw_len,
			 व्योम *stripped_addr, माप_प्रकार stripped_len,
			 खाता *outfile, स्थिर अक्षर *name)
अणु
	पूर्णांक found_load = 0;
	अचिन्हित दीर्घ load_size = -1;  /* Work around bogus warning */
	अचिन्हित दीर्घ mapping_size;
	पूर्णांक i;
	अचिन्हित दीर्घ j;
	ELF(Shdr) *symtab_hdr = शून्य, *strtab_hdr;
	ELF(Ehdr) *hdr = (ELF(Ehdr) *)raw_addr;
	ELF(Dyn) *dyn = 0, *dyn_end = 0;
	INT_BITS syms[NSYMS] = अणुपूर्ण;

	ELF(Phdr) *pt = (ELF(Phdr) *)(raw_addr + GET_BE(&hdr->e_phoff));

	/* Walk the segment table. */
	क्रम (i = 0; i < GET_BE(&hdr->e_phnum); i++) अणु
		अगर (GET_BE(&pt[i].p_type) == PT_LOAD) अणु
			अगर (found_load)
				fail("multiple PT_LOAD segs\n");

			अगर (GET_BE(&pt[i].p_offset) != 0 ||
			    GET_BE(&pt[i].p_vaddr) != 0)
				fail("PT_LOAD in wrong place\n");

			अगर (GET_BE(&pt[i].p_memsz) != GET_BE(&pt[i].p_filesz))
				fail("cannot handle memsz != filesz\n");

			load_size = GET_BE(&pt[i].p_memsz);
			found_load = 1;
		पूर्ण अन्यथा अगर (GET_BE(&pt[i].p_type) == PT_DYNAMIC) अणु
			dyn = raw_addr + GET_BE(&pt[i].p_offset);
			dyn_end = raw_addr + GET_BE(&pt[i].p_offset) +
				GET_BE(&pt[i].p_memsz);
		पूर्ण
	पूर्ण
	अगर (!found_load)
		fail("no PT_LOAD seg\n");

	अगर (stripped_len < load_size)
		fail("stripped input is too short\n");

	/* Walk the dynamic table */
	क्रम (i = 0; dyn + i < dyn_end &&
		     GET_BE(&dyn[i].d_tag) != DT_शून्य; i++) अणु
		typeof(dyn[i].d_tag) tag = GET_BE(&dyn[i].d_tag);
		typeof(dyn[i].d_un.d_val) val = GET_BE(&dyn[i].d_un.d_val);

		अगर ((tag == DT_RELSZ || tag == DT_RELASZ) && (val != 0))
			fail("vdso image contains dynamic relocations\n");
	पूर्ण

	/* Walk the section table */
	क्रम (i = 0; i < GET_BE(&hdr->e_shnum); i++) अणु
		ELF(Shdr) *sh = raw_addr + GET_BE(&hdr->e_shoff) +
			GET_BE(&hdr->e_shentsize) * i;
		अगर (GET_BE(&sh->sh_type) == SHT_SYMTAB)
			symtab_hdr = sh;
	पूर्ण

	अगर (!symtab_hdr)
		fail("no symbol table\n");

	strtab_hdr = raw_addr + GET_BE(&hdr->e_shoff) +
		GET_BE(&hdr->e_shentsize) * GET_BE(&symtab_hdr->sh_link);

	/* Walk the symbol table */
	क्रम (i = 0;
	     i < GET_BE(&symtab_hdr->sh_size) / GET_BE(&symtab_hdr->sh_entsize);
	     i++) अणु
		पूर्णांक k;

		ELF(Sym) *sym = raw_addr + GET_BE(&symtab_hdr->sh_offset) +
			GET_BE(&symtab_hdr->sh_entsize) * i;
		स्थिर अक्षर *name = raw_addr + GET_BE(&strtab_hdr->sh_offset) +
			GET_BE(&sym->st_name);

		क्रम (k = 0; k < NSYMS; k++) अणु
			अगर (!म_भेद(name, required_syms[k].name)) अणु
				अगर (syms[k]) अणु
					fail("duplicate symbol %s\n",
					     required_syms[k].name);
				पूर्ण

				/*
				 * Careful: we use negative addresses, but
				 * st_value is अचिन्हित, so we rely
				 * on syms[k] being a चिन्हित type of the
				 * correct width.
				 */
				syms[k] = GET_BE(&sym->st_value);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Validate mapping addresses. */
	अगर (syms[sym_vvar_start] % 8192)
		fail("vvar_begin must be a multiple of 8192\n");

	अगर (!name) अणु
		ख_डालो(stripped_addr, stripped_len, 1, outfile);
		वापस;
	पूर्ण

	mapping_size = (stripped_len + 8191) / 8192 * 8192;

	ख_लिखो(outfile, "/* AUTOMATICALLY GENERATED -- DO NOT EDIT */\n\n");
	ख_लिखो(outfile, "#include <linux/cache.h>\n");
	ख_लिखो(outfile, "#include <asm/vdso.h>\n");
	ख_लिखो(outfile, "\n");
	ख_लिखो(outfile,
		"static unsigned char raw_data[%lu] __ro_after_init __aligned(8192)= {",
		mapping_size);
	क्रम (j = 0; j < stripped_len; j++) अणु
		अगर (j % 10 == 0)
			ख_लिखो(outfile, "\n\t");
		ख_लिखो(outfile, "0x%02X, ",
			(पूर्णांक)((अचिन्हित अक्षर *)stripped_addr)[j]);
	पूर्ण
	ख_लिखो(outfile, "\n};\n\n");

	ख_लिखो(outfile, "const struct vdso_image %s_builtin = {\n", name);
	ख_लिखो(outfile, "\t.data = raw_data,\n");
	ख_लिखो(outfile, "\t.size = %lu,\n", mapping_size);
	क्रम (i = 0; i < NSYMS; i++) अणु
		अगर (required_syms[i].export && syms[i])
			ख_लिखो(outfile, "\t.sym_%s = %" PRIi64 ",\n",
				required_syms[i].name, (पूर्णांक64_t)syms[i]);
	पूर्ण
	ख_लिखो(outfile, "};\n");
पूर्ण
