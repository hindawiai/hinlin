<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is included twice from vdso2c.c.  It generates code क्रम 32-bit
 * and 64-bit vDSOs.  We need both क्रम 64-bit builds, since 32-bit vDSOs
 * are built क्रम 32-bit userspace.
 */

अटल व्योम BITSFUNC(copy)(खाता *outfile, स्थिर अचिन्हित अक्षर *data, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (i % 10 == 0)
			ख_लिखो(outfile, "\n\t");
		ख_लिखो(outfile, "0x%02X, ", (पूर्णांक)(data)[i]);
	पूर्ण
पूर्ण


/*
 * Extract a section from the input data पूर्णांकo a standalone blob.  Used to
 * capture kernel-only data that needs to persist indefinitely, e.g. the
 * exception fixup tables, but only in the kernel, i.e. the section can
 * be stripped from the final vDSO image.
 */
अटल व्योम BITSFUNC(extract)(स्थिर अचिन्हित अक्षर *data, माप_प्रकार data_len,
			      खाता *outfile, ELF(Shdr) *sec, स्थिर अक्षर *name)
अणु
	अचिन्हित दीर्घ offset;
	माप_प्रकार len;

	offset = (अचिन्हित दीर्घ)GET_LE(&sec->sh_offset);
	len = (माप_प्रकार)GET_LE(&sec->sh_size);

	अगर (offset + len > data_len)
		fail("section to extract overruns input data");

	ख_लिखो(outfile, "static const unsigned char %s[%zu] = {", name, len);
	BITSFUNC(copy)(outfile, data + offset, len);
	ख_लिखो(outfile, "\n};\n\n");
पूर्ण

अटल व्योम BITSFUNC(go)(व्योम *raw_addr, माप_प्रकार raw_len,
			 व्योम *stripped_addr, माप_प्रकार stripped_len,
			 खाता *outfile, स्थिर अक्षर *image_name)
अणु
	पूर्णांक found_load = 0;
	अचिन्हित दीर्घ load_size = -1;  /* Work around bogus warning */
	अचिन्हित दीर्घ mapping_size;
	ELF(Ehdr) *hdr = (ELF(Ehdr) *)raw_addr;
	अचिन्हित दीर्घ i, syms_nr;
	ELF(Shdr) *symtab_hdr = शून्य, *strtab_hdr, *secstrings_hdr,
		*alt_sec = शून्य, *extable_sec = शून्य;
	ELF(Dyn) *dyn = 0, *dyn_end = 0;
	स्थिर अक्षर *secstrings;
	INT_BITS syms[NSYMS] = अणुपूर्ण;

	ELF(Phdr) *pt = (ELF(Phdr) *)(raw_addr + GET_LE(&hdr->e_phoff));

	अगर (GET_LE(&hdr->e_type) != ET_DYN)
		fail("input is not a shared object\n");

	/* Walk the segment table. */
	क्रम (i = 0; i < GET_LE(&hdr->e_phnum); i++) अणु
		अगर (GET_LE(&pt[i].p_type) == PT_LOAD) अणु
			अगर (found_load)
				fail("multiple PT_LOAD segs\n");

			अगर (GET_LE(&pt[i].p_offset) != 0 ||
			    GET_LE(&pt[i].p_vaddr) != 0)
				fail("PT_LOAD in wrong place\n");

			अगर (GET_LE(&pt[i].p_memsz) != GET_LE(&pt[i].p_filesz))
				fail("cannot handle memsz != filesz\n");

			load_size = GET_LE(&pt[i].p_memsz);
			found_load = 1;
		पूर्ण अन्यथा अगर (GET_LE(&pt[i].p_type) == PT_DYNAMIC) अणु
			dyn = raw_addr + GET_LE(&pt[i].p_offset);
			dyn_end = raw_addr + GET_LE(&pt[i].p_offset) +
				GET_LE(&pt[i].p_memsz);
		पूर्ण
	पूर्ण
	अगर (!found_load)
		fail("no PT_LOAD seg\n");

	अगर (stripped_len < load_size)
		fail("stripped input is too short\n");

	अगर (!dyn)
		fail("input has no PT_DYNAMIC section -- your toolchain is buggy\n");

	/* Walk the dynamic table */
	क्रम (i = 0; dyn + i < dyn_end &&
		     GET_LE(&dyn[i].d_tag) != DT_शून्य; i++) अणु
		typeof(dyn[i].d_tag) tag = GET_LE(&dyn[i].d_tag);
		अगर (tag == DT_REL || tag == DT_RELSZ || tag == DT_RELA ||
		    tag == DT_RELENT || tag == DT_TEXTREL)
			fail("vdso image contains dynamic relocations\n");
	पूर्ण

	/* Walk the section table */
	secstrings_hdr = raw_addr + GET_LE(&hdr->e_shoff) +
		GET_LE(&hdr->e_shentsize)*GET_LE(&hdr->e_shstrndx);
	secstrings = raw_addr + GET_LE(&secstrings_hdr->sh_offset);
	क्रम (i = 0; i < GET_LE(&hdr->e_shnum); i++) अणु
		ELF(Shdr) *sh = raw_addr + GET_LE(&hdr->e_shoff) +
			GET_LE(&hdr->e_shentsize) * i;
		अगर (GET_LE(&sh->sh_type) == SHT_SYMTAB)
			symtab_hdr = sh;

		अगर (!म_भेद(secstrings + GET_LE(&sh->sh_name),
			    ".altinstructions"))
			alt_sec = sh;
		अगर (!म_भेद(secstrings + GET_LE(&sh->sh_name), "__ex_table"))
			extable_sec = sh;
	पूर्ण

	अगर (!symtab_hdr)
		fail("no symbol table\n");

	strtab_hdr = raw_addr + GET_LE(&hdr->e_shoff) +
		GET_LE(&hdr->e_shentsize) * GET_LE(&symtab_hdr->sh_link);

	syms_nr = GET_LE(&symtab_hdr->sh_size) / GET_LE(&symtab_hdr->sh_entsize);
	/* Walk the symbol table */
	क्रम (i = 0; i < syms_nr; i++) अणु
		अचिन्हित पूर्णांक k;
		ELF(Sym) *sym = raw_addr + GET_LE(&symtab_hdr->sh_offset) +
			GET_LE(&symtab_hdr->sh_entsize) * i;
		स्थिर अक्षर *sym_name = raw_addr +
				       GET_LE(&strtab_hdr->sh_offset) +
				       GET_LE(&sym->st_name);

		क्रम (k = 0; k < NSYMS; k++) अणु
			अगर (!म_भेद(sym_name, required_syms[k].name)) अणु
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
				syms[k] = GET_LE(&sym->st_value);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Validate mapping addresses. */
	क्रम (i = 0; i < माप(special_pages) / माप(special_pages[0]); i++) अणु
		INT_BITS symval = syms[special_pages[i]];

		अगर (!symval)
			जारी;  /* The mapping isn't used; ignore it. */

		अगर (symval % 4096)
			fail("%s must be a multiple of 4096\n",
			     required_syms[i].name);
		अगर (symval + 4096 < syms[sym_vvar_start])
			fail("%s underruns vvar_start\n",
			     required_syms[i].name);
		अगर (symval + 4096 > 0)
			fail("%s is on the wrong side of the vdso text\n",
			     required_syms[i].name);
	पूर्ण
	अगर (syms[sym_vvar_start] % 4096)
		fail("vvar_begin must be a multiple of 4096\n");

	अगर (!image_name) अणु
		ख_डालो(stripped_addr, stripped_len, 1, outfile);
		वापस;
	पूर्ण

	mapping_size = (stripped_len + 4095) / 4096 * 4096;

	ख_लिखो(outfile, "/* AUTOMATICALLY GENERATED -- DO NOT EDIT */\n\n");
	ख_लिखो(outfile, "#include <linux/linkage.h>\n");
	ख_लिखो(outfile, "#include <asm/page_types.h>\n");
	ख_लिखो(outfile, "#include <asm/vdso.h>\n");
	ख_लिखो(outfile, "\n");
	ख_लिखो(outfile,
		"static unsigned char raw_data[%lu] __ro_after_init __aligned(PAGE_SIZE) = {",
		mapping_size);
	क्रम (i = 0; i < stripped_len; i++) अणु
		अगर (i % 10 == 0)
			ख_लिखो(outfile, "\n\t");
		ख_लिखो(outfile, "0x%02X, ",
			(पूर्णांक)((अचिन्हित अक्षर *)stripped_addr)[i]);
	पूर्ण
	ख_लिखो(outfile, "\n};\n\n");
	अगर (extable_sec)
		BITSFUNC(extract)(raw_addr, raw_len, outfile,
				  extable_sec, "extable");

	ख_लिखो(outfile, "const struct vdso_image %s = {\n", image_name);
	ख_लिखो(outfile, "\t.data = raw_data,\n");
	ख_लिखो(outfile, "\t.size = %lu,\n", mapping_size);
	अगर (alt_sec) अणु
		ख_लिखो(outfile, "\t.alt = %lu,\n",
			(अचिन्हित दीर्घ)GET_LE(&alt_sec->sh_offset));
		ख_लिखो(outfile, "\t.alt_len = %lu,\n",
			(अचिन्हित दीर्घ)GET_LE(&alt_sec->sh_size));
	पूर्ण
	अगर (extable_sec) अणु
		ख_लिखो(outfile, "\t.extable_base = %lu,\n",
			(अचिन्हित दीर्घ)GET_LE(&extable_sec->sh_offset));
		ख_लिखो(outfile, "\t.extable_len = %lu,\n",
			(अचिन्हित दीर्घ)GET_LE(&extable_sec->sh_size));
		ख_लिखो(outfile, "\t.extable = extable,\n");
	पूर्ण

	क्रम (i = 0; i < NSYMS; i++) अणु
		अगर (required_syms[i].export && syms[i])
			ख_लिखो(outfile, "\t.sym_%s = %" PRIi64 ",\n",
				required_syms[i].name, (पूर्णांक64_t)syms[i]);
	पूर्ण
	ख_लिखो(outfile, "};\n");
पूर्ण
