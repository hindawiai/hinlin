<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)
/*
 * BPF अटल linker
 *
 * Copyright (c) 2021 Facebook
 */
#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <त्रुटिसं.स>
#समावेश <linux/err.h>
#समावेश <linux/btf.h>
#समावेश <elf.h>
#समावेश <libelf.h>
#समावेश <gelf.h>
#समावेश <fcntl.h>
#समावेश "libbpf.h"
#समावेश "btf.h"
#समावेश "libbpf_internal.h"
#समावेश "strset.h"

#घोषणा BTF_EXTERN_SEC ".extern"

काष्ठा src_sec अणु
	स्थिर अक्षर *sec_name;
	/* positional (not necessarily ELF) index in an array of sections */
	पूर्णांक id;
	/* positional (not necessarily ELF) index of a matching section in a final object file */
	पूर्णांक dst_id;
	/* section data offset in a matching output section */
	पूर्णांक dst_off;
	/* whether section is omitted from the final ELF file */
	bool skipped;
	/* whether section is an ephemeral section, not mapped to an ELF section */
	bool ephemeral;

	/* ELF info */
	माप_प्रकार sec_idx;
	Elf_Scn *scn;
	Elf64_Shdr *shdr;
	Elf_Data *data;

	/* corresponding BTF DATASEC type ID */
	पूर्णांक sec_type_id;
पूर्ण;

काष्ठा src_obj अणु
	स्थिर अक्षर *filename;
	पूर्णांक fd;
	Elf *elf;
	/* Section header strings section index */
	माप_प्रकार shstrs_sec_idx;
	/* SYMTAB section index */
	माप_प्रकार symtab_sec_idx;

	काष्ठा btf *btf;
	काष्ठा btf_ext *btf_ext;

	/* List of sections (including ephemeral). Slot zero is unused. */
	काष्ठा src_sec *secs;
	पूर्णांक sec_cnt;

	/* mapping of symbol indices from src to dst ELF */
	पूर्णांक *sym_map;
	/* mapping from the src BTF type IDs to dst ones */
	पूर्णांक *btf_type_map;
पूर्ण;

/* single .BTF.ext data section */
काष्ठा btf_ext_sec_data अणु
	माप_प्रकार rec_cnt;
	__u32 rec_sz;
	व्योम *recs;
पूर्ण;

काष्ठा glob_sym अणु
	/* ELF symbol index */
	पूर्णांक sym_idx;
	/* associated section id क्रम .ksyms, .kconfig, etc, but not .बाह्य */
	पूर्णांक sec_id;
	/* बाह्य name offset in STRTAB */
	पूर्णांक name_off;
	/* optional associated BTF type ID */
	पूर्णांक btf_id;
	/* BTF type ID to which VAR/FUNC type is poपूर्णांकing to; used क्रम
	 * rewriting types when बाह्य VAR/FUNC is resolved to a concrete
	 * definition
	 */
	पूर्णांक underlying_btf_id;
	/* sec_var index in the corresponding dst_sec, अगर exists */
	पूर्णांक var_idx;

	/* बाह्य or resolved/global symbol */
	bool is_बाह्य;
	/* weak or strong symbol, never goes back from strong to weak */
	bool is_weak;
पूर्ण;

काष्ठा dst_sec अणु
	अक्षर *sec_name;
	/* positional (not necessarily ELF) index in an array of sections */
	पूर्णांक id;

	bool ephemeral;

	/* ELF info */
	माप_प्रकार sec_idx;
	Elf_Scn *scn;
	Elf64_Shdr *shdr;
	Elf_Data *data;

	/* final output section size */
	पूर्णांक sec_sz;
	/* final output contents of the section */
	व्योम *raw_data;

	/* corresponding STT_SECTION symbol index in SYMTAB */
	पूर्णांक sec_sym_idx;

	/* section's DATASEC variable info, emitted on BTF finalization */
	bool has_btf;
	पूर्णांक sec_var_cnt;
	काष्ठा btf_var_secinfo *sec_vars;

	/* section's .BTF.ext data */
	काष्ठा btf_ext_sec_data func_info;
	काष्ठा btf_ext_sec_data line_info;
	काष्ठा btf_ext_sec_data core_relo_info;
पूर्ण;

काष्ठा bpf_linker अणु
	अक्षर *filename;
	पूर्णांक fd;
	Elf *elf;
	Elf64_Ehdr *elf_hdr;

	/* Output sections metadata */
	काष्ठा dst_sec *secs;
	पूर्णांक sec_cnt;

	काष्ठा strset *strtab_strs; /* STRTAB unique strings */
	माप_प्रकार strtab_sec_idx; /* STRTAB section index */
	माप_प्रकार symtab_sec_idx; /* SYMTAB section index */

	काष्ठा btf *btf;
	काष्ठा btf_ext *btf_ext;

	/* global (including बाह्य) ELF symbols */
	पूर्णांक glob_sym_cnt;
	काष्ठा glob_sym *glob_syms;
पूर्ण;

#घोषणा pr_warn_elf(fmt, ...)									\
	libbpf_prपूर्णांक(LIBBPF_WARN, "libbpf: " fmt ": %s\n", ##__VA_ARGS__, elf_errmsg(-1))

अटल पूर्णांक init_output_elf(काष्ठा bpf_linker *linker, स्थिर अक्षर *file);

अटल पूर्णांक linker_load_obj_file(काष्ठा bpf_linker *linker, स्थिर अक्षर *filename, काष्ठा src_obj *obj);
अटल पूर्णांक linker_sanity_check_elf(काष्ठा src_obj *obj);
अटल पूर्णांक linker_sanity_check_elf_symtab(काष्ठा src_obj *obj, काष्ठा src_sec *sec);
अटल पूर्णांक linker_sanity_check_elf_relos(काष्ठा src_obj *obj, काष्ठा src_sec *sec);
अटल पूर्णांक linker_sanity_check_btf(काष्ठा src_obj *obj);
अटल पूर्णांक linker_sanity_check_btf_ext(काष्ठा src_obj *obj);
अटल पूर्णांक linker_fixup_btf(काष्ठा src_obj *obj);
अटल पूर्णांक linker_append_sec_data(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj);
अटल पूर्णांक linker_append_elf_syms(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj);
अटल पूर्णांक linker_append_elf_sym(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj,
				 Elf64_Sym *sym, स्थिर अक्षर *sym_name, पूर्णांक src_sym_idx);
अटल पूर्णांक linker_append_elf_relos(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj);
अटल पूर्णांक linker_append_btf(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj);
अटल पूर्णांक linker_append_btf_ext(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj);

अटल पूर्णांक finalize_btf(काष्ठा bpf_linker *linker);
अटल पूर्णांक finalize_btf_ext(काष्ठा bpf_linker *linker);

व्योम bpf_linker__मुक्त(काष्ठा bpf_linker *linker)
अणु
	पूर्णांक i;

	अगर (!linker)
		वापस;

	मुक्त(linker->filename);

	अगर (linker->elf)
		elf_end(linker->elf);

	अगर (linker->fd >= 0)
		बंद(linker->fd);

	strset__मुक्त(linker->strtab_strs);

	btf__मुक्त(linker->btf);
	btf_ext__मुक्त(linker->btf_ext);

	क्रम (i = 1; i < linker->sec_cnt; i++) अणु
		काष्ठा dst_sec *sec = &linker->secs[i];

		मुक्त(sec->sec_name);
		मुक्त(sec->raw_data);
		मुक्त(sec->sec_vars);

		मुक्त(sec->func_info.recs);
		मुक्त(sec->line_info.recs);
		मुक्त(sec->core_relo_info.recs);
	पूर्ण
	मुक्त(linker->secs);

	मुक्त(linker);
पूर्ण

काष्ठा bpf_linker *bpf_linker__new(स्थिर अक्षर *filename, काष्ठा bpf_linker_opts *opts)
अणु
	काष्ठा bpf_linker *linker;
	पूर्णांक err;

	अगर (!OPTS_VALID(opts, bpf_linker_opts))
		वापस शून्य;

	अगर (elf_version(EV_CURRENT) == EV_NONE) अणु
		pr_warn_elf("libelf initialization failed");
		वापस शून्य;
	पूर्ण

	linker = सुस्मृति(1, माप(*linker));
	अगर (!linker)
		वापस शून्य;

	linker->fd = -1;

	err = init_output_elf(linker, filename);
	अगर (err)
		जाओ err_out;

	वापस linker;

err_out:
	bpf_linker__मुक्त(linker);
	वापस शून्य;
पूर्ण

अटल काष्ठा dst_sec *add_dst_sec(काष्ठा bpf_linker *linker, स्थिर अक्षर *sec_name)
अणु
	काष्ठा dst_sec *secs = linker->secs, *sec;
	माप_प्रकार new_cnt = linker->sec_cnt ? linker->sec_cnt + 1 : 2;

	secs = libbpf_पुनः_स्मृतिarray(secs, new_cnt, माप(*secs));
	अगर (!secs)
		वापस शून्य;

	/* zero out newly allocated memory */
	स_रखो(secs + linker->sec_cnt, 0, (new_cnt - linker->sec_cnt) * माप(*secs));

	linker->secs = secs;
	linker->sec_cnt = new_cnt;

	sec = &linker->secs[new_cnt - 1];
	sec->id = new_cnt - 1;
	sec->sec_name = strdup(sec_name);
	अगर (!sec->sec_name)
		वापस शून्य;

	वापस sec;
पूर्ण

अटल Elf64_Sym *add_new_sym(काष्ठा bpf_linker *linker, माप_प्रकार *sym_idx)
अणु
	काष्ठा dst_sec *symtab = &linker->secs[linker->symtab_sec_idx];
	Elf64_Sym *syms, *sym;
	माप_प्रकार sym_cnt = symtab->sec_sz / माप(*sym);

	syms = libbpf_पुनः_स्मृतिarray(symtab->raw_data, sym_cnt + 1, माप(*sym));
	अगर (!syms)
		वापस शून्य;

	sym = &syms[sym_cnt];
	स_रखो(sym, 0, माप(*sym));

	symtab->raw_data = syms;
	symtab->sec_sz += माप(*sym);
	symtab->shdr->sh_size += माप(*sym);
	symtab->data->d_size += माप(*sym);

	अगर (sym_idx)
		*sym_idx = sym_cnt;

	वापस sym;
पूर्ण

अटल पूर्णांक init_output_elf(काष्ठा bpf_linker *linker, स्थिर अक्षर *file)
अणु
	पूर्णांक err, str_off;
	Elf64_Sym *init_sym;
	काष्ठा dst_sec *sec;

	linker->filename = strdup(file);
	अगर (!linker->filename)
		वापस -ENOMEM;

	linker->fd = खोलो(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	अगर (linker->fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to create '%s': %d\n", file, err);
		वापस err;
	पूर्ण

	linker->elf = elf_begin(linker->fd, ELF_C_WRITE, शून्य);
	अगर (!linker->elf) अणु
		pr_warn_elf("failed to create ELF object");
		वापस -EINVAL;
	पूर्ण

	/* ELF header */
	linker->elf_hdr = elf64_newehdr(linker->elf);
	अगर (!linker->elf_hdr) अणु
		pr_warn_elf("failed to create ELF header");
		वापस -EINVAL;
	पूर्ण

	linker->elf_hdr->e_machine = EM_BPF;
	linker->elf_hdr->e_type = ET_REL;
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	linker->elf_hdr->e_ident[EI_DATA] = ELFDATA2LSB;
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
	linker->elf_hdr->e_ident[EI_DATA] = ELFDATA2MSB;
#अन्यथा
#त्रुटि "Unknown __BYTE_ORDER"
#पूर्ण_अगर

	/* STRTAB */
	/* initialize strset with an empty string to conक्रमm to ELF */
	linker->strtab_strs = strset__new(पूर्णांक_उच्च, "", माप(""));
	अगर (libbpf_get_error(linker->strtab_strs))
		वापस libbpf_get_error(linker->strtab_strs);

	sec = add_dst_sec(linker, ".strtab");
	अगर (!sec)
		वापस -ENOMEM;

	sec->scn = elf_newscn(linker->elf);
	अगर (!sec->scn) अणु
		pr_warn_elf("failed to create STRTAB section");
		वापस -EINVAL;
	पूर्ण

	sec->shdr = elf64_माला_लोhdr(sec->scn);
	अगर (!sec->shdr)
		वापस -EINVAL;

	sec->data = elf_newdata(sec->scn);
	अगर (!sec->data) अणु
		pr_warn_elf("failed to create STRTAB data");
		वापस -EINVAL;
	पूर्ण

	str_off = strset__add_str(linker->strtab_strs, sec->sec_name);
	अगर (str_off < 0)
		वापस str_off;

	sec->sec_idx = elf_ndxscn(sec->scn);
	linker->elf_hdr->e_shstrndx = sec->sec_idx;
	linker->strtab_sec_idx = sec->sec_idx;

	sec->shdr->sh_name = str_off;
	sec->shdr->sh_type = SHT_STRTAB;
	sec->shdr->sh_flags = SHF_STRINGS;
	sec->shdr->sh_offset = 0;
	sec->shdr->sh_link = 0;
	sec->shdr->sh_info = 0;
	sec->shdr->sh_addralign = 1;
	sec->shdr->sh_size = sec->sec_sz = 0;
	sec->shdr->sh_entsize = 0;

	/* SYMTAB */
	sec = add_dst_sec(linker, ".symtab");
	अगर (!sec)
		वापस -ENOMEM;

	sec->scn = elf_newscn(linker->elf);
	अगर (!sec->scn) अणु
		pr_warn_elf("failed to create SYMTAB section");
		वापस -EINVAL;
	पूर्ण

	sec->shdr = elf64_माला_लोhdr(sec->scn);
	अगर (!sec->shdr)
		वापस -EINVAL;

	sec->data = elf_newdata(sec->scn);
	अगर (!sec->data) अणु
		pr_warn_elf("failed to create SYMTAB data");
		वापस -EINVAL;
	पूर्ण

	str_off = strset__add_str(linker->strtab_strs, sec->sec_name);
	अगर (str_off < 0)
		वापस str_off;

	sec->sec_idx = elf_ndxscn(sec->scn);
	linker->symtab_sec_idx = sec->sec_idx;

	sec->shdr->sh_name = str_off;
	sec->shdr->sh_type = SHT_SYMTAB;
	sec->shdr->sh_flags = 0;
	sec->shdr->sh_offset = 0;
	sec->shdr->sh_link = linker->strtab_sec_idx;
	/* sh_info should be one greater than the index of the last local
	 * symbol (i.e., binding is STB_LOCAL). But why and who cares?
	 */
	sec->shdr->sh_info = 0;
	sec->shdr->sh_addralign = 8;
	sec->shdr->sh_entsize = माप(Elf64_Sym);

	/* .BTF */
	linker->btf = btf__new_empty();
	err = libbpf_get_error(linker->btf);
	अगर (err)
		वापस err;

	/* add the special all-zero symbol */
	init_sym = add_new_sym(linker, शून्य);
	अगर (!init_sym)
		वापस -EINVAL;

	init_sym->st_name = 0;
	init_sym->st_info = 0;
	init_sym->st_other = 0;
	init_sym->st_shndx = SHN_UNDEF;
	init_sym->st_value = 0;
	init_sym->st_size = 0;

	वापस 0;
पूर्ण

पूर्णांक bpf_linker__add_file(काष्ठा bpf_linker *linker, स्थिर अक्षर *filename)
अणु
	काष्ठा src_obj obj = अणुपूर्ण;
	पूर्णांक err = 0;

	अगर (!linker->elf)
		वापस -EINVAL;

	err = err ?: linker_load_obj_file(linker, filename, &obj);
	err = err ?: linker_append_sec_data(linker, &obj);
	err = err ?: linker_append_elf_syms(linker, &obj);
	err = err ?: linker_append_elf_relos(linker, &obj);
	err = err ?: linker_append_btf(linker, &obj);
	err = err ?: linker_append_btf_ext(linker, &obj);

	/* मुक्त up src_obj resources */
	मुक्त(obj.btf_type_map);
	btf__मुक्त(obj.btf);
	btf_ext__मुक्त(obj.btf_ext);
	मुक्त(obj.secs);
	मुक्त(obj.sym_map);
	अगर (obj.elf)
		elf_end(obj.elf);
	अगर (obj.fd >= 0)
		बंद(obj.fd);

	वापस err;
पूर्ण

अटल bool is_dwarf_sec_name(स्थिर अक्षर *name)
अणु
	/* approximation, but the actual list is too दीर्घ */
	वापस म_भेदन(name, ".debug_", माप(".debug_") - 1) == 0;
पूर्ण

अटल bool is_ignored_sec(काष्ठा src_sec *sec)
अणु
	Elf64_Shdr *shdr = sec->shdr;
	स्थिर अक्षर *name = sec->sec_name;

	/* no special handling of .strtab */
	अगर (shdr->sh_type == SHT_STRTAB)
		वापस true;

	/* ignore .llvm_addrsig section as well */
	अगर (shdr->sh_type == SHT_LLVM_ADDRSIG)
		वापस true;

	/* no subprograms will lead to an empty .text section, ignore it */
	अगर (shdr->sh_type == SHT_PROGBITS && shdr->sh_size == 0 &&
	    म_भेद(sec->sec_name, ".text") == 0)
		वापस true;

	/* DWARF sections */
	अगर (is_dwarf_sec_name(sec->sec_name))
		वापस true;

	अगर (म_भेदन(name, ".rel", माप(".rel") - 1) == 0) अणु
		name += माप(".rel") - 1;
		/* DWARF section relocations */
		अगर (is_dwarf_sec_name(name))
			वापस true;

		/* .BTF and .BTF.ext करोn't need relocations */
		अगर (म_भेद(name, BTF_ELF_SEC) == 0 ||
		    म_भेद(name, BTF_EXT_ELF_SEC) == 0)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल काष्ठा src_sec *add_src_sec(काष्ठा src_obj *obj, स्थिर अक्षर *sec_name)
अणु
	काष्ठा src_sec *secs = obj->secs, *sec;
	माप_प्रकार new_cnt = obj->sec_cnt ? obj->sec_cnt + 1 : 2;

	secs = libbpf_पुनः_स्मृतिarray(secs, new_cnt, माप(*secs));
	अगर (!secs)
		वापस शून्य;

	/* zero out newly allocated memory */
	स_रखो(secs + obj->sec_cnt, 0, (new_cnt - obj->sec_cnt) * माप(*secs));

	obj->secs = secs;
	obj->sec_cnt = new_cnt;

	sec = &obj->secs[new_cnt - 1];
	sec->id = new_cnt - 1;
	sec->sec_name = sec_name;

	वापस sec;
पूर्ण

अटल पूर्णांक linker_load_obj_file(काष्ठा bpf_linker *linker, स्थिर अक्षर *filename, काष्ठा src_obj *obj)
अणु
#अगर __BYTE_ORDER == __LITTLE_ENDIAN
	स्थिर पूर्णांक host_endianness = ELFDATA2LSB;
#या_अगर __BYTE_ORDER == __BIG_ENDIAN
	स्थिर पूर्णांक host_endianness = ELFDATA2MSB;
#अन्यथा
#त्रुटि "Unknown __BYTE_ORDER"
#पूर्ण_अगर
	पूर्णांक err = 0;
	Elf_Scn *scn;
	Elf_Data *data;
	Elf64_Ehdr *ehdr;
	Elf64_Shdr *shdr;
	काष्ठा src_sec *sec;

	pr_debug("linker: adding object file '%s'...\n", filename);

	obj->filename = filename;

	obj->fd = खोलो(filename, O_RDONLY);
	अगर (obj->fd < 0) अणु
		err = -त्रुटि_सं;
		pr_warn("failed to open file '%s': %d\n", filename, err);
		वापस err;
	पूर्ण
	obj->elf = elf_begin(obj->fd, ELF_C_READ_MMAP, शून्य);
	अगर (!obj->elf) अणु
		err = -त्रुटि_सं;
		pr_warn_elf("failed to parse ELF file '%s'", filename);
		वापस err;
	पूर्ण

	/* Sanity check ELF file high-level properties */
	ehdr = elf64_getehdr(obj->elf);
	अगर (!ehdr) अणु
		err = -त्रुटि_सं;
		pr_warn_elf("failed to get ELF header for %s", filename);
		वापस err;
	पूर्ण
	अगर (ehdr->e_ident[EI_DATA] != host_endianness) अणु
		err = -EOPNOTSUPP;
		pr_warn_elf("unsupported byte order of ELF file %s", filename);
		वापस err;
	पूर्ण
	अगर (ehdr->e_type != ET_REL
	    || ehdr->e_machine != EM_BPF
	    || ehdr->e_ident[EI_CLASS] != ELFCLASS64) अणु
		err = -EOPNOTSUPP;
		pr_warn_elf("unsupported kind of ELF file %s", filename);
		वापस err;
	पूर्ण

	अगर (elf_माला_लोhdrstrndx(obj->elf, &obj->shstrs_sec_idx)) अणु
		err = -त्रुटि_सं;
		pr_warn_elf("failed to get SHSTRTAB section index for %s", filename);
		वापस err;
	पूर्ण

	scn = शून्य;
	जबतक ((scn = elf_nextscn(obj->elf, scn)) != शून्य) अणु
		माप_प्रकार sec_idx = elf_ndxscn(scn);
		स्थिर अक्षर *sec_name;

		shdr = elf64_माला_लोhdr(scn);
		अगर (!shdr) अणु
			err = -त्रुटि_सं;
			pr_warn_elf("failed to get section #%zu header for %s",
				    sec_idx, filename);
			वापस err;
		पूर्ण

		sec_name = elf_strptr(obj->elf, obj->shstrs_sec_idx, shdr->sh_name);
		अगर (!sec_name) अणु
			err = -त्रुटि_सं;
			pr_warn_elf("failed to get section #%zu name for %s",
				    sec_idx, filename);
			वापस err;
		पूर्ण

		data = elf_getdata(scn, 0);
		अगर (!data) अणु
			err = -त्रुटि_सं;
			pr_warn_elf("failed to get section #%zu (%s) data from %s",
				    sec_idx, sec_name, filename);
			वापस err;
		पूर्ण

		sec = add_src_sec(obj, sec_name);
		अगर (!sec)
			वापस -ENOMEM;

		sec->scn = scn;
		sec->shdr = shdr;
		sec->data = data;
		sec->sec_idx = elf_ndxscn(scn);

		अगर (is_ignored_sec(sec)) अणु
			sec->skipped = true;
			जारी;
		पूर्ण

		चयन (shdr->sh_type) अणु
		हाल SHT_SYMTAB:
			अगर (obj->symtab_sec_idx) अणु
				err = -EOPNOTSUPP;
				pr_warn("multiple SYMTAB sections found, not supported\n");
				वापस err;
			पूर्ण
			obj->symtab_sec_idx = sec_idx;
			अवरोध;
		हाल SHT_STRTAB:
			/* we'll स्थिरruct our own string table */
			अवरोध;
		हाल SHT_PROGBITS:
			अगर (म_भेद(sec_name, BTF_ELF_SEC) == 0) अणु
				obj->btf = btf__new(data->d_buf, shdr->sh_size);
				err = libbpf_get_error(obj->btf);
				अगर (err) अणु
					pr_warn("failed to parse .BTF from %s: %d\n", filename, err);
					वापस err;
				पूर्ण
				sec->skipped = true;
				जारी;
			पूर्ण
			अगर (म_भेद(sec_name, BTF_EXT_ELF_SEC) == 0) अणु
				obj->btf_ext = btf_ext__new(data->d_buf, shdr->sh_size);
				err = libbpf_get_error(obj->btf_ext);
				अगर (err) अणु
					pr_warn("failed to parse .BTF.ext from '%s': %d\n", filename, err);
					वापस err;
				पूर्ण
				sec->skipped = true;
				जारी;
			पूर्ण

			/* data & code */
			अवरोध;
		हाल SHT_NOBITS:
			/* BSS */
			अवरोध;
		हाल SHT_REL:
			/* relocations */
			अवरोध;
		शेष:
			pr_warn("unrecognized section #%zu (%s) in %s\n",
				sec_idx, sec_name, filename);
			err = -EINVAL;
			वापस err;
		पूर्ण
	पूर्ण

	err = err ?: linker_sanity_check_elf(obj);
	err = err ?: linker_sanity_check_btf(obj);
	err = err ?: linker_sanity_check_btf_ext(obj);
	err = err ?: linker_fixup_btf(obj);

	वापस err;
पूर्ण

अटल bool is_घात_of_2(माप_प्रकार x)
अणु
	वापस x && (x & (x - 1)) == 0;
पूर्ण

अटल पूर्णांक linker_sanity_check_elf(काष्ठा src_obj *obj)
अणु
	काष्ठा src_sec *sec;
	पूर्णांक i, err;

	अगर (!obj->symtab_sec_idx) अणु
		pr_warn("ELF is missing SYMTAB section in %s\n", obj->filename);
		वापस -EINVAL;
	पूर्ण
	अगर (!obj->shstrs_sec_idx) अणु
		pr_warn("ELF is missing section headers STRTAB section in %s\n", obj->filename);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 1; i < obj->sec_cnt; i++) अणु
		sec = &obj->secs[i];

		अगर (sec->sec_name[0] == '\0') अणु
			pr_warn("ELF section #%zu has empty name in %s\n", sec->sec_idx, obj->filename);
			वापस -EINVAL;
		पूर्ण

		अगर (sec->shdr->sh_addralign && !is_घात_of_2(sec->shdr->sh_addralign))
			वापस -EINVAL;
		अगर (sec->shdr->sh_addralign != sec->data->d_align)
			वापस -EINVAL;

		अगर (sec->shdr->sh_size != sec->data->d_size)
			वापस -EINVAL;

		चयन (sec->shdr->sh_type) अणु
		हाल SHT_SYMTAB:
			err = linker_sanity_check_elf_symtab(obj, sec);
			अगर (err)
				वापस err;
			अवरोध;
		हाल SHT_STRTAB:
			अवरोध;
		हाल SHT_PROGBITS:
			अगर (sec->shdr->sh_flags & SHF_EXECINSTR) अणु
				अगर (sec->shdr->sh_size % माप(काष्ठा bpf_insn) != 0)
					वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल SHT_NOBITS:
			अवरोध;
		हाल SHT_REL:
			err = linker_sanity_check_elf_relos(obj, sec);
			अगर (err)
				वापस err;
			अवरोध;
		हाल SHT_LLVM_ADDRSIG:
			अवरोध;
		शेष:
			pr_warn("ELF section #%zu (%s) has unrecognized type %zu in %s\n",
				sec->sec_idx, sec->sec_name, (माप_प्रकार)sec->shdr->sh_type, obj->filename);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक linker_sanity_check_elf_symtab(काष्ठा src_obj *obj, काष्ठा src_sec *sec)
अणु
	काष्ठा src_sec *link_sec;
	Elf64_Sym *sym;
	पूर्णांक i, n;

	अगर (sec->shdr->sh_entsize != माप(Elf64_Sym))
		वापस -EINVAL;
	अगर (sec->shdr->sh_size % sec->shdr->sh_entsize != 0)
		वापस -EINVAL;

	अगर (!sec->shdr->sh_link || sec->shdr->sh_link >= obj->sec_cnt) अणु
		pr_warn("ELF SYMTAB section #%zu points to missing STRTAB section #%zu in %s\n",
			sec->sec_idx, (माप_प्रकार)sec->shdr->sh_link, obj->filename);
		वापस -EINVAL;
	पूर्ण
	link_sec = &obj->secs[sec->shdr->sh_link];
	अगर (link_sec->shdr->sh_type != SHT_STRTAB) अणु
		pr_warn("ELF SYMTAB section #%zu points to invalid STRTAB section #%zu in %s\n",
			sec->sec_idx, (माप_प्रकार)sec->shdr->sh_link, obj->filename);
		वापस -EINVAL;
	पूर्ण

	n = sec->shdr->sh_size / sec->shdr->sh_entsize;
	sym = sec->data->d_buf;
	क्रम (i = 0; i < n; i++, sym++) अणु
		पूर्णांक sym_type = ELF64_ST_TYPE(sym->st_info);
		पूर्णांक sym_bind = ELF64_ST_BIND(sym->st_info);
		पूर्णांक sym_vis = ELF64_ST_VISIBILITY(sym->st_other);

		अगर (i == 0) अणु
			अगर (sym->st_name != 0 || sym->st_info != 0
			    || sym->st_other != 0 || sym->st_shndx != 0
			    || sym->st_value != 0 || sym->st_size != 0) अणु
				pr_warn("ELF sym #0 is invalid in %s\n", obj->filename);
				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण
		अगर (sym_bind != STB_LOCAL && sym_bind != STB_GLOBAL && sym_bind != STB_WEAK) अणु
			pr_warn("ELF sym #%d in section #%zu has unsupported symbol binding %d\n",
				i, sec->sec_idx, sym_bind);
			वापस -EINVAL;
		पूर्ण
		अगर (sym_vis != STV_DEFAULT && sym_vis != STV_HIDDEN) अणु
			pr_warn("ELF sym #%d in section #%zu has unsupported symbol visibility %d\n",
				i, sec->sec_idx, sym_vis);
			वापस -EINVAL;
		पूर्ण
		अगर (sym->st_shndx == 0) अणु
			अगर (sym_type != STT_NOTYPE || sym_bind == STB_LOCAL
			    || sym->st_value != 0 || sym->st_size != 0) अणु
				pr_warn("ELF sym #%d is invalid extern symbol in %s\n",
					i, obj->filename);

				वापस -EINVAL;
			पूर्ण
			जारी;
		पूर्ण
		अगर (sym->st_shndx < SHN_LORESERVE && sym->st_shndx >= obj->sec_cnt) अणु
			pr_warn("ELF sym #%d in section #%zu points to missing section #%zu in %s\n",
				i, sec->sec_idx, (माप_प्रकार)sym->st_shndx, obj->filename);
			वापस -EINVAL;
		पूर्ण
		अगर (sym_type == STT_SECTION) अणु
			अगर (sym->st_value != 0)
				वापस -EINVAL;
			जारी;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक linker_sanity_check_elf_relos(काष्ठा src_obj *obj, काष्ठा src_sec *sec)
अणु
	काष्ठा src_sec *link_sec, *sym_sec;
	Elf64_Rel *relo;
	पूर्णांक i, n;

	अगर (sec->shdr->sh_entsize != माप(Elf64_Rel))
		वापस -EINVAL;
	अगर (sec->shdr->sh_size % sec->shdr->sh_entsize != 0)
		वापस -EINVAL;

	/* SHT_REL's sh_link should poपूर्णांक to SYMTAB */
	अगर (sec->shdr->sh_link != obj->symtab_sec_idx) अणु
		pr_warn("ELF relo section #%zu points to invalid SYMTAB section #%zu in %s\n",
			sec->sec_idx, (माप_प्रकार)sec->shdr->sh_link, obj->filename);
		वापस -EINVAL;
	पूर्ण

	/* SHT_REL's sh_info poपूर्णांकs to relocated section */
	अगर (!sec->shdr->sh_info || sec->shdr->sh_info >= obj->sec_cnt) अणु
		pr_warn("ELF relo section #%zu points to missing section #%zu in %s\n",
			sec->sec_idx, (माप_प्रकार)sec->shdr->sh_info, obj->filename);
		वापस -EINVAL;
	पूर्ण
	link_sec = &obj->secs[sec->shdr->sh_info];

	/* .rel<secname> -> <secname> pattern is followed */
	अगर (म_भेदन(sec->sec_name, ".rel", माप(".rel") - 1) != 0
	    || म_भेद(sec->sec_name + माप(".rel") - 1, link_sec->sec_name) != 0) अणु
		pr_warn("ELF relo section #%zu name has invalid name in %s\n",
			sec->sec_idx, obj->filename);
		वापस -EINVAL;
	पूर्ण

	/* करोn't further validate relocations क्रम ignored sections */
	अगर (link_sec->skipped)
		वापस 0;

	/* relocatable section is data or inकाष्ठाions */
	अगर (link_sec->shdr->sh_type != SHT_PROGBITS && link_sec->shdr->sh_type != SHT_NOBITS) अणु
		pr_warn("ELF relo section #%zu points to invalid section #%zu in %s\n",
			sec->sec_idx, (माप_प्रकार)sec->shdr->sh_info, obj->filename);
		वापस -EINVAL;
	पूर्ण

	/* check sanity of each relocation */
	n = sec->shdr->sh_size / sec->shdr->sh_entsize;
	relo = sec->data->d_buf;
	sym_sec = &obj->secs[obj->symtab_sec_idx];
	क्रम (i = 0; i < n; i++, relo++) अणु
		माप_प्रकार sym_idx = ELF64_R_SYM(relo->r_info);
		माप_प्रकार sym_type = ELF64_R_TYPE(relo->r_info);

		अगर (sym_type != R_BPF_64_64 && sym_type != R_BPF_64_32) अणु
			pr_warn("ELF relo #%d in section #%zu has unexpected type %zu in %s\n",
				i, sec->sec_idx, sym_type, obj->filename);
			वापस -EINVAL;
		पूर्ण

		अगर (!sym_idx || sym_idx * माप(Elf64_Sym) >= sym_sec->shdr->sh_size) अणु
			pr_warn("ELF relo #%d in section #%zu points to invalid symbol #%zu in %s\n",
				i, sec->sec_idx, sym_idx, obj->filename);
			वापस -EINVAL;
		पूर्ण

		अगर (link_sec->shdr->sh_flags & SHF_EXECINSTR) अणु
			अगर (relo->r_offset % माप(काष्ठा bpf_insn) != 0) अणु
				pr_warn("ELF relo #%d in section #%zu points to missing symbol #%zu in %s\n",
					i, sec->sec_idx, sym_idx, obj->filename);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_btf_type_id(__u32 *type_id, व्योम *ctx)
अणु
	काष्ठा btf *btf = ctx;

	अगर (*type_id > btf__get_nr_types(btf))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक check_btf_str_off(__u32 *str_off, व्योम *ctx)
अणु
	काष्ठा btf *btf = ctx;
	स्थिर अक्षर *s;

	s = btf__str_by_offset(btf, *str_off);

	अगर (!s)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक linker_sanity_check_btf(काष्ठा src_obj *obj)
अणु
	काष्ठा btf_type *t;
	पूर्णांक i, n, err = 0;

	अगर (!obj->btf)
		वापस 0;

	n = btf__get_nr_types(obj->btf);
	क्रम (i = 1; i <= n; i++) अणु
		t = btf_type_by_id(obj->btf, i);

		err = err ?: btf_type_visit_type_ids(t, check_btf_type_id, obj->btf);
		err = err ?: btf_type_visit_str_offs(t, check_btf_str_off, obj->btf);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक linker_sanity_check_btf_ext(काष्ठा src_obj *obj)
अणु
	पूर्णांक err = 0;

	अगर (!obj->btf_ext)
		वापस 0;

	/* can't use .BTF.ext without .BTF */
	अगर (!obj->btf)
		वापस -EINVAL;

	err = err ?: btf_ext_visit_type_ids(obj->btf_ext, check_btf_type_id, obj->btf);
	err = err ?: btf_ext_visit_str_offs(obj->btf_ext, check_btf_str_off, obj->btf);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक init_sec(काष्ठा bpf_linker *linker, काष्ठा dst_sec *dst_sec, काष्ठा src_sec *src_sec)
अणु
	Elf_Scn *scn;
	Elf_Data *data;
	Elf64_Shdr *shdr;
	पूर्णांक name_off;

	dst_sec->sec_sz = 0;
	dst_sec->sec_idx = 0;
	dst_sec->ephemeral = src_sec->ephemeral;

	/* ephemeral sections are just thin section shells lacking most parts */
	अगर (src_sec->ephemeral)
		वापस 0;

	scn = elf_newscn(linker->elf);
	अगर (!scn)
		वापस -ENOMEM;
	data = elf_newdata(scn);
	अगर (!data)
		वापस -ENOMEM;
	shdr = elf64_माला_लोhdr(scn);
	अगर (!shdr)
		वापस -ENOMEM;

	dst_sec->scn = scn;
	dst_sec->shdr = shdr;
	dst_sec->data = data;
	dst_sec->sec_idx = elf_ndxscn(scn);

	name_off = strset__add_str(linker->strtab_strs, src_sec->sec_name);
	अगर (name_off < 0)
		वापस name_off;

	shdr->sh_name = name_off;
	shdr->sh_type = src_sec->shdr->sh_type;
	shdr->sh_flags = src_sec->shdr->sh_flags;
	shdr->sh_size = 0;
	/* sh_link and sh_info have dअगरferent meaning क्रम dअगरferent types of
	 * sections, so we leave it up to the caller code to fill them in, अगर
	 * necessary
	 */
	shdr->sh_link = 0;
	shdr->sh_info = 0;
	shdr->sh_addralign = src_sec->shdr->sh_addralign;
	shdr->sh_entsize = src_sec->shdr->sh_entsize;

	data->d_type = src_sec->data->d_type;
	data->d_size = 0;
	data->d_buf = शून्य;
	data->d_align = src_sec->data->d_align;
	data->d_off = 0;

	वापस 0;
पूर्ण

अटल काष्ठा dst_sec *find_dst_sec_by_name(काष्ठा bpf_linker *linker, स्थिर अक्षर *sec_name)
अणु
	काष्ठा dst_sec *sec;
	पूर्णांक i;

	क्रम (i = 1; i < linker->sec_cnt; i++) अणु
		sec = &linker->secs[i];

		अगर (म_भेद(sec->sec_name, sec_name) == 0)
			वापस sec;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool secs_match(काष्ठा dst_sec *dst, काष्ठा src_sec *src)
अणु
	अगर (dst->ephemeral || src->ephemeral)
		वापस true;

	अगर (dst->shdr->sh_type != src->shdr->sh_type) अणु
		pr_warn("sec %s types mismatch\n", dst->sec_name);
		वापस false;
	पूर्ण
	अगर (dst->shdr->sh_flags != src->shdr->sh_flags) अणु
		pr_warn("sec %s flags mismatch\n", dst->sec_name);
		वापस false;
	पूर्ण
	अगर (dst->shdr->sh_entsize != src->shdr->sh_entsize) अणु
		pr_warn("sec %s entsize mismatch\n", dst->sec_name);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool sec_content_is_same(काष्ठा dst_sec *dst_sec, काष्ठा src_sec *src_sec)
अणु
	अगर (dst_sec->sec_sz != src_sec->shdr->sh_size)
		वापस false;
	अगर (स_भेद(dst_sec->raw_data, src_sec->data->d_buf, dst_sec->sec_sz) != 0)
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक extend_sec(काष्ठा bpf_linker *linker, काष्ठा dst_sec *dst, काष्ठा src_sec *src)
अणु
	व्योम *पंचांगp;
	माप_प्रकार dst_align, src_align;
	माप_प्रकार dst_align_sz, dst_final_sz;
	पूर्णांक err;

	/* Ephemeral source section करोesn't contribute anything to ELF
	 * section data.
	 */
	अगर (src->ephemeral)
		वापस 0;

	/* Some sections (like .maps) can contain both बाह्यs (and thus be
	 * ephemeral) and non-बाह्यs (map definitions). So it's possible that
	 * it has to be "upgraded" from ephemeral to non-ephemeral when the
	 * first non-ephemeral entity appears. In such हाल, we add ELF
	 * section, data, etc.
	 */
	अगर (dst->ephemeral) अणु
		err = init_sec(linker, dst, src);
		अगर (err)
			वापस err;
	पूर्ण

	dst_align = dst->shdr->sh_addralign;
	src_align = src->shdr->sh_addralign;
	अगर (dst_align == 0)
		dst_align = 1;
	अगर (dst_align < src_align)
		dst_align = src_align;

	dst_align_sz = (dst->sec_sz + dst_align - 1) / dst_align * dst_align;

	/* no need to re-align final size */
	dst_final_sz = dst_align_sz + src->shdr->sh_size;

	अगर (src->shdr->sh_type != SHT_NOBITS) अणु
		पंचांगp = पुनः_स्मृति(dst->raw_data, dst_final_sz);
		अगर (!पंचांगp)
			वापस -ENOMEM;
		dst->raw_data = पंचांगp;

		/* pad dst section, अगर it's alignment क्रमced size increase */
		स_रखो(dst->raw_data + dst->sec_sz, 0, dst_align_sz - dst->sec_sz);
		/* now copy src data at a properly aligned offset */
		स_नकल(dst->raw_data + dst_align_sz, src->data->d_buf, src->shdr->sh_size);
	पूर्ण

	dst->sec_sz = dst_final_sz;
	dst->shdr->sh_size = dst_final_sz;
	dst->data->d_size = dst_final_sz;

	dst->shdr->sh_addralign = dst_align;
	dst->data->d_align = dst_align;

	src->dst_off = dst_align_sz;

	वापस 0;
पूर्ण

अटल bool is_data_sec(काष्ठा src_sec *sec)
अणु
	अगर (!sec || sec->skipped)
		वापस false;
	/* ephemeral sections are data sections, e.g., .kconfig, .ksyms */
	अगर (sec->ephemeral)
		वापस true;
	वापस sec->shdr->sh_type == SHT_PROGBITS || sec->shdr->sh_type == SHT_NOBITS;
पूर्ण

अटल bool is_relo_sec(काष्ठा src_sec *sec)
अणु
	अगर (!sec || sec->skipped || sec->ephemeral)
		वापस false;
	वापस sec->shdr->sh_type == SHT_REL;
पूर्ण

अटल पूर्णांक linker_append_sec_data(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj)
अणु
	पूर्णांक i, err;

	क्रम (i = 1; i < obj->sec_cnt; i++) अणु
		काष्ठा src_sec *src_sec;
		काष्ठा dst_sec *dst_sec;

		src_sec = &obj->secs[i];
		अगर (!is_data_sec(src_sec))
			जारी;

		dst_sec = find_dst_sec_by_name(linker, src_sec->sec_name);
		अगर (!dst_sec) अणु
			dst_sec = add_dst_sec(linker, src_sec->sec_name);
			अगर (!dst_sec)
				वापस -ENOMEM;
			err = init_sec(linker, dst_sec, src_sec);
			अगर (err) अणु
				pr_warn("failed to init section '%s'\n", src_sec->sec_name);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!secs_match(dst_sec, src_sec)) अणु
				pr_warn("ELF sections %s are incompatible\n", src_sec->sec_name);
				वापस -1;
			पूर्ण

			/* "license" and "version" sections are deduped */
			अगर (म_भेद(src_sec->sec_name, "license") == 0
			    || म_भेद(src_sec->sec_name, "version") == 0) अणु
				अगर (!sec_content_is_same(dst_sec, src_sec)) अणु
					pr_warn("non-identical contents of section '%s' are not supported\n", src_sec->sec_name);
					वापस -EINVAL;
				पूर्ण
				src_sec->skipped = true;
				src_sec->dst_id = dst_sec->id;
				जारी;
			पूर्ण
		पूर्ण

		/* record mapped section index */
		src_sec->dst_id = dst_sec->id;

		err = extend_sec(linker, dst_sec, src_sec);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक linker_append_elf_syms(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj)
अणु
	काष्ठा src_sec *symtab = &obj->secs[obj->symtab_sec_idx];
	Elf64_Sym *sym = symtab->data->d_buf;
	पूर्णांक i, n = symtab->shdr->sh_size / symtab->shdr->sh_entsize, err;
	पूर्णांक str_sec_idx = symtab->shdr->sh_link;
	स्थिर अक्षर *sym_name;

	obj->sym_map = सुस्मृति(n + 1, माप(*obj->sym_map));
	अगर (!obj->sym_map)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++, sym++) अणु
		/* We alपढ़ोy validated all-zero symbol #0 and we alपढ़ोy
		 * appended it preventively to the final SYMTAB, so skip it.
		 */
		अगर (i == 0)
			जारी;

		sym_name = elf_strptr(obj->elf, str_sec_idx, sym->st_name);
		अगर (!sym_name) अणु
			pr_warn("can't fetch symbol name for symbol #%d in '%s'\n", i, obj->filename);
			वापस -EINVAL;
		पूर्ण

		err = linker_append_elf_sym(linker, obj, sym, sym_name, i);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल Elf64_Sym *get_sym_by_idx(काष्ठा bpf_linker *linker, माप_प्रकार sym_idx)
अणु
	काष्ठा dst_sec *symtab = &linker->secs[linker->symtab_sec_idx];
	Elf64_Sym *syms = symtab->raw_data;

	वापस &syms[sym_idx];
पूर्ण

अटल काष्ठा glob_sym *find_glob_sym(काष्ठा bpf_linker *linker, स्थिर अक्षर *sym_name)
अणु
	काष्ठा glob_sym *glob_sym;
	स्थिर अक्षर *name;
	पूर्णांक i;

	क्रम (i = 0; i < linker->glob_sym_cnt; i++) अणु
		glob_sym = &linker->glob_syms[i];
		name = strset__data(linker->strtab_strs) + glob_sym->name_off;

		अगर (म_भेद(name, sym_name) == 0)
			वापस glob_sym;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा glob_sym *add_glob_sym(काष्ठा bpf_linker *linker)
अणु
	काष्ठा glob_sym *syms, *sym;

	syms = libbpf_पुनः_स्मृतिarray(linker->glob_syms, linker->glob_sym_cnt + 1,
				   माप(*linker->glob_syms));
	अगर (!syms)
		वापस शून्य;

	sym = &syms[linker->glob_sym_cnt];
	स_रखो(sym, 0, माप(*sym));
	sym->var_idx = -1;

	linker->glob_syms = syms;
	linker->glob_sym_cnt++;

	वापस sym;
पूर्ण

अटल bool glob_sym_btf_matches(स्थिर अक्षर *sym_name, bool exact,
				 स्थिर काष्ठा btf *btf1, __u32 id1,
				 स्थिर काष्ठा btf *btf2, __u32 id2)
अणु
	स्थिर काष्ठा btf_type *t1, *t2;
	bool is_अटल1, is_अटल2;
	स्थिर अक्षर *n1, *n2;
	पूर्णांक i, n;

recur:
	n1 = n2 = शून्य;
	t1 = skip_mods_and_प्रकारs(btf1, id1, &id1);
	t2 = skip_mods_and_प्रकारs(btf2, id2, &id2);

	/* check अगर only one side is FWD, otherwise handle with common logic */
	अगर (!exact && btf_is_fwd(t1) != btf_is_fwd(t2)) अणु
		n1 = btf__str_by_offset(btf1, t1->name_off);
		n2 = btf__str_by_offset(btf2, t2->name_off);
		अगर (म_भेद(n1, n2) != 0) अणु
			pr_warn("global '%s': incompatible forward declaration names '%s' and '%s'\n",
				sym_name, n1, n2);
			वापस false;
		पूर्ण
		/* validate अगर FWD kind matches concrete kind */
		अगर (btf_is_fwd(t1)) अणु
			अगर (btf_kflag(t1) && btf_is_जोड़(t2))
				वापस true;
			अगर (!btf_kflag(t1) && btf_is_काष्ठा(t2))
				वापस true;
			pr_warn("global '%s': incompatible %s forward declaration and concrete kind %s\n",
				sym_name, btf_kflag(t1) ? "union" : "struct", btf_kind_str(t2));
		पूर्ण अन्यथा अणु
			अगर (btf_kflag(t2) && btf_is_जोड़(t1))
				वापस true;
			अगर (!btf_kflag(t2) && btf_is_काष्ठा(t1))
				वापस true;
			pr_warn("global '%s': incompatible %s forward declaration and concrete kind %s\n",
				sym_name, btf_kflag(t2) ? "union" : "struct", btf_kind_str(t1));
		पूर्ण
		वापस false;
	पूर्ण

	अगर (btf_kind(t1) != btf_kind(t2)) अणु
		pr_warn("global '%s': incompatible BTF kinds %s and %s\n",
			sym_name, btf_kind_str(t1), btf_kind_str(t2));
		वापस false;
	पूर्ण

	चयन (btf_kind(t1)) अणु
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION:
	हाल BTF_KIND_ENUM:
	हाल BTF_KIND_FWD:
	हाल BTF_KIND_FUNC:
	हाल BTF_KIND_VAR:
		n1 = btf__str_by_offset(btf1, t1->name_off);
		n2 = btf__str_by_offset(btf2, t2->name_off);
		अगर (म_भेद(n1, n2) != 0) अणु
			pr_warn("global '%s': incompatible %s names '%s' and '%s'\n",
				sym_name, btf_kind_str(t1), n1, n2);
			वापस false;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (btf_kind(t1)) अणु
	हाल BTF_KIND_UNKN: /* व्योम */
	हाल BTF_KIND_FWD:
		वापस true;
	हाल BTF_KIND_INT:
	हाल BTF_KIND_FLOAT:
	हाल BTF_KIND_ENUM:
		/* ignore encoding क्रम पूर्णांक and क्रमागत values क्रम क्रमागत */
		अगर (t1->size != t2->size) अणु
			pr_warn("global '%s': incompatible %s '%s' size %u and %u\n",
				sym_name, btf_kind_str(t1), n1, t1->size, t2->size);
			वापस false;
		पूर्ण
		वापस true;
	हाल BTF_KIND_PTR:
		/* just validate overall shape of the referenced type, so no
		 * contents comparison क्रम काष्ठा/जोड़, and allowd fwd vs
		 * काष्ठा/जोड़
		 */
		exact = false;
		id1 = t1->type;
		id2 = t2->type;
		जाओ recur;
	हाल BTF_KIND_ARRAY:
		/* ignore index type and array size */
		id1 = btf_array(t1)->type;
		id2 = btf_array(t2)->type;
		जाओ recur;
	हाल BTF_KIND_FUNC:
		/* बाह्य and global linkages are compatible */
		is_अटल1 = btf_func_linkage(t1) == BTF_FUNC_STATIC;
		is_अटल2 = btf_func_linkage(t2) == BTF_FUNC_STATIC;
		अगर (is_अटल1 != is_अटल2) अणु
			pr_warn("global '%s': incompatible func '%s' linkage\n", sym_name, n1);
			वापस false;
		पूर्ण

		id1 = t1->type;
		id2 = t2->type;
		जाओ recur;
	हाल BTF_KIND_VAR:
		/* बाह्य and global linkages are compatible */
		is_अटल1 = btf_var(t1)->linkage == BTF_VAR_STATIC;
		is_अटल2 = btf_var(t2)->linkage == BTF_VAR_STATIC;
		अगर (is_अटल1 != is_अटल2) अणु
			pr_warn("global '%s': incompatible var '%s' linkage\n", sym_name, n1);
			वापस false;
		पूर्ण

		id1 = t1->type;
		id2 = t2->type;
		जाओ recur;
	हाल BTF_KIND_STRUCT:
	हाल BTF_KIND_UNION: अणु
		स्थिर काष्ठा btf_member *m1, *m2;

		अगर (!exact)
			वापस true;

		अगर (btf_vlen(t1) != btf_vlen(t2)) अणु
			pr_warn("global '%s': incompatible number of %s fields %u and %u\n",
				sym_name, btf_kind_str(t1), btf_vlen(t1), btf_vlen(t2));
			वापस false;
		पूर्ण

		n = btf_vlen(t1);
		m1 = btf_members(t1);
		m2 = btf_members(t2);
		क्रम (i = 0; i < n; i++, m1++, m2++) अणु
			n1 = btf__str_by_offset(btf1, m1->name_off);
			n2 = btf__str_by_offset(btf2, m2->name_off);
			अगर (म_भेद(n1, n2) != 0) अणु
				pr_warn("global '%s': incompatible field #%d names '%s' and '%s'\n",
					sym_name, i, n1, n2);
				वापस false;
			पूर्ण
			अगर (m1->offset != m2->offset) अणु
				pr_warn("global '%s': incompatible field #%d ('%s') offsets\n",
					sym_name, i, n1);
				वापस false;
			पूर्ण
			अगर (!glob_sym_btf_matches(sym_name, exact, btf1, m1->type, btf2, m2->type))
				वापस false;
		पूर्ण

		वापस true;
	पूर्ण
	हाल BTF_KIND_FUNC_PROTO: अणु
		स्थिर काष्ठा btf_param *m1, *m2;

		अगर (btf_vlen(t1) != btf_vlen(t2)) अणु
			pr_warn("global '%s': incompatible number of %s params %u and %u\n",
				sym_name, btf_kind_str(t1), btf_vlen(t1), btf_vlen(t2));
			वापस false;
		पूर्ण

		n = btf_vlen(t1);
		m1 = btf_params(t1);
		m2 = btf_params(t2);
		क्रम (i = 0; i < n; i++, m1++, m2++) अणु
			/* ignore func arg names */
			अगर (!glob_sym_btf_matches(sym_name, exact, btf1, m1->type, btf2, m2->type))
				वापस false;
		पूर्ण

		/* now check वापस type as well */
		id1 = t1->type;
		id2 = t2->type;
		जाओ recur;
	पूर्ण

	/* skip_mods_and_प्रकारs() make this impossible */
	हाल BTF_KIND_TYPEDEF:
	हाल BTF_KIND_VOLATILE:
	हाल BTF_KIND_CONST:
	हाल BTF_KIND_RESTRICT:
	/* DATASECs are never compared with each other */
	हाल BTF_KIND_DATASEC:
	शेष:
		pr_warn("global '%s': unsupported BTF kind %s\n",
			sym_name, btf_kind_str(t1));
		वापस false;
	पूर्ण
पूर्ण

अटल bool map_defs_match(स्थिर अक्षर *sym_name,
			   स्थिर काष्ठा btf *मुख्य_btf,
			   स्थिर काष्ठा btf_map_def *मुख्य_def,
			   स्थिर काष्ठा btf_map_def *मुख्य_inner_def,
			   स्थिर काष्ठा btf *extra_btf,
			   स्थिर काष्ठा btf_map_def *extra_def,
			   स्थिर काष्ठा btf_map_def *extra_inner_def)
अणु
	स्थिर अक्षर *reason;

	अगर (मुख्य_def->map_type != extra_def->map_type) अणु
		reason = "type";
		जाओ mismatch;
	पूर्ण

	/* check key type/size match */
	अगर (मुख्य_def->key_size != extra_def->key_size) अणु
		reason = "key_size";
		जाओ mismatch;
	पूर्ण
	अगर (!!मुख्य_def->key_type_id != !!extra_def->key_type_id) अणु
		reason = "key type";
		जाओ mismatch;
	पूर्ण
	अगर ((मुख्य_def->parts & MAP_DEF_KEY_TYPE)
	     && !glob_sym_btf_matches(sym_name, true /*exact*/,
				      मुख्य_btf, मुख्य_def->key_type_id,
				      extra_btf, extra_def->key_type_id)) अणु
		reason = "key type";
		जाओ mismatch;
	पूर्ण

	/* validate value type/size match */
	अगर (मुख्य_def->value_size != extra_def->value_size) अणु
		reason = "value_size";
		जाओ mismatch;
	पूर्ण
	अगर (!!मुख्य_def->value_type_id != !!extra_def->value_type_id) अणु
		reason = "value type";
		जाओ mismatch;
	पूर्ण
	अगर ((मुख्य_def->parts & MAP_DEF_VALUE_TYPE)
	     && !glob_sym_btf_matches(sym_name, true /*exact*/,
				      मुख्य_btf, मुख्य_def->value_type_id,
				      extra_btf, extra_def->value_type_id)) अणु
		reason = "key type";
		जाओ mismatch;
	पूर्ण

	अगर (मुख्य_def->max_entries != extra_def->max_entries) अणु
		reason = "max_entries";
		जाओ mismatch;
	पूर्ण
	अगर (मुख्य_def->map_flags != extra_def->map_flags) अणु
		reason = "map_flags";
		जाओ mismatch;
	पूर्ण
	अगर (मुख्य_def->numa_node != extra_def->numa_node) अणु
		reason = "numa_node";
		जाओ mismatch;
	पूर्ण
	अगर (मुख्य_def->pinning != extra_def->pinning) अणु
		reason = "pinning";
		जाओ mismatch;
	पूर्ण

	अगर ((मुख्य_def->parts & MAP_DEF_INNER_MAP) != (extra_def->parts & MAP_DEF_INNER_MAP)) अणु
		reason = "inner map";
		जाओ mismatch;
	पूर्ण

	अगर (मुख्य_def->parts & MAP_DEF_INNER_MAP) अणु
		अक्षर inner_map_name[128];

		snम_लिखो(inner_map_name, माप(inner_map_name), "%s.inner", sym_name);

		वापस map_defs_match(inner_map_name,
				      मुख्य_btf, मुख्य_inner_def, शून्य,
				      extra_btf, extra_inner_def, शून्य);
	पूर्ण

	वापस true;

mismatch:
	pr_warn("global '%s': map %s mismatch\n", sym_name, reason);
	वापस false;
पूर्ण

अटल bool glob_map_defs_match(स्थिर अक्षर *sym_name,
				काष्ठा bpf_linker *linker, काष्ठा glob_sym *glob_sym,
				काष्ठा src_obj *obj, Elf64_Sym *sym, पूर्णांक btf_id)
अणु
	काष्ठा btf_map_def dst_def = अणुपूर्ण, dst_inner_def = अणुपूर्ण;
	काष्ठा btf_map_def src_def = अणुपूर्ण, src_inner_def = अणुपूर्ण;
	स्थिर काष्ठा btf_type *t;
	पूर्णांक err;

	t = btf__type_by_id(obj->btf, btf_id);
	अगर (!btf_is_var(t)) अणु
		pr_warn("global '%s': invalid map definition type [%d]\n", sym_name, btf_id);
		वापस false;
	पूर्ण
	t = skip_mods_and_प्रकारs(obj->btf, t->type, शून्य);

	err = parse_btf_map_def(sym_name, obj->btf, t, true /*strict*/, &src_def, &src_inner_def);
	अगर (err) अणु
		pr_warn("global '%s': invalid map definition\n", sym_name);
		वापस false;
	पूर्ण

	/* re-parse existing map definition */
	t = btf__type_by_id(linker->btf, glob_sym->btf_id);
	t = skip_mods_and_प्रकारs(linker->btf, t->type, शून्य);
	err = parse_btf_map_def(sym_name, linker->btf, t, true /*strict*/, &dst_def, &dst_inner_def);
	अगर (err) अणु
		/* this should not happen, because we alपढ़ोy validated it */
		pr_warn("global '%s': invalid dst map definition\n", sym_name);
		वापस false;
	पूर्ण

	/* Currently बाह्य map definition has to be complete and match
	 * concrete map definition exactly. This restriction might be lअगरted
	 * in the future.
	 */
	वापस map_defs_match(sym_name, linker->btf, &dst_def, &dst_inner_def,
			      obj->btf, &src_def, &src_inner_def);
पूर्ण

अटल bool glob_syms_match(स्थिर अक्षर *sym_name,
			    काष्ठा bpf_linker *linker, काष्ठा glob_sym *glob_sym,
			    काष्ठा src_obj *obj, Elf64_Sym *sym, माप_प्रकार sym_idx, पूर्णांक btf_id)
अणु
	स्थिर काष्ठा btf_type *src_t;

	/* अगर we are dealing with बाह्यs, BTF types describing both global
	 * and बाह्य VARs/FUNCs should be completely present in all files
	 */
	अगर (!glob_sym->btf_id || !btf_id) अणु
		pr_warn("BTF info is missing for global symbol '%s'\n", sym_name);
		वापस false;
	पूर्ण

	src_t = btf__type_by_id(obj->btf, btf_id);
	अगर (!btf_is_var(src_t) && !btf_is_func(src_t)) अणु
		pr_warn("only extern variables and functions are supported, but got '%s' for '%s'\n",
			btf_kind_str(src_t), sym_name);
		वापस false;
	पूर्ण

	/* deal with .maps definitions specially */
	अगर (glob_sym->sec_id && म_भेद(linker->secs[glob_sym->sec_id].sec_name, MAPS_ELF_SEC) == 0)
		वापस glob_map_defs_match(sym_name, linker, glob_sym, obj, sym, btf_id);

	अगर (!glob_sym_btf_matches(sym_name, true /*exact*/,
				  linker->btf, glob_sym->btf_id, obj->btf, btf_id))
		वापस false;

	वापस true;
पूर्ण

अटल bool btf_is_non_अटल(स्थिर काष्ठा btf_type *t)
अणु
	वापस (btf_is_var(t) && btf_var(t)->linkage != BTF_VAR_STATIC)
	       || (btf_is_func(t) && btf_func_linkage(t) != BTF_FUNC_STATIC);
पूर्ण

अटल पूर्णांक find_glob_sym_btf(काष्ठा src_obj *obj, Elf64_Sym *sym, स्थिर अक्षर *sym_name,
			     पूर्णांक *out_btf_sec_id, पूर्णांक *out_btf_id)
अणु
	पूर्णांक i, j, n = btf__get_nr_types(obj->btf), m, btf_id = 0;
	स्थिर काष्ठा btf_type *t;
	स्थिर काष्ठा btf_var_secinfo *vi;
	स्थिर अक्षर *name;

	क्रम (i = 1; i <= n; i++) अणु
		t = btf__type_by_id(obj->btf, i);

		/* some global and बाह्य FUNCs and VARs might not be associated with any
		 * DATASEC, so try to detect them in the same pass
		 */
		अगर (btf_is_non_अटल(t)) अणु
			name = btf__str_by_offset(obj->btf, t->name_off);
			अगर (म_भेद(name, sym_name) != 0)
				जारी;

			/* remember and still try to find DATASEC */
			btf_id = i;
			जारी;
		पूर्ण

		अगर (!btf_is_datasec(t))
			जारी;

		vi = btf_var_secinfos(t);
		क्रम (j = 0, m = btf_vlen(t); j < m; j++, vi++) अणु
			t = btf__type_by_id(obj->btf, vi->type);
			name = btf__str_by_offset(obj->btf, t->name_off);

			अगर (म_भेद(name, sym_name) != 0)
				जारी;
			अगर (btf_is_var(t) && btf_var(t)->linkage == BTF_VAR_STATIC)
				जारी;
			अगर (btf_is_func(t) && btf_func_linkage(t) == BTF_FUNC_STATIC)
				जारी;

			अगर (btf_id && btf_id != vi->type) अणु
				pr_warn("global/extern '%s' BTF is ambiguous: both types #%d and #%u match\n",
					sym_name, btf_id, vi->type);
				वापस -EINVAL;
			पूर्ण

			*out_btf_sec_id = i;
			*out_btf_id = vi->type;

			वापस 0;
		पूर्ण
	पूर्ण

	/* मुक्त-भग्नing बाह्य or global FUNC */
	अगर (btf_id) अणु
		*out_btf_sec_id = 0;
		*out_btf_id = btf_id;
		वापस 0;
	पूर्ण

	pr_warn("failed to find BTF info for global/extern symbol '%s'\n", sym_name);
	वापस -ENOENT;
पूर्ण

अटल काष्ठा src_sec *find_src_sec_by_name(काष्ठा src_obj *obj, स्थिर अक्षर *sec_name)
अणु
	काष्ठा src_sec *sec;
	पूर्णांक i;

	क्रम (i = 1; i < obj->sec_cnt; i++) अणु
		sec = &obj->secs[i];

		अगर (म_भेद(sec->sec_name, sec_name) == 0)
			वापस sec;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक complete_बाह्य_btf_info(काष्ठा btf *dst_btf, पूर्णांक dst_id,
				    काष्ठा btf *src_btf, पूर्णांक src_id)
अणु
	काष्ठा btf_type *dst_t = btf_type_by_id(dst_btf, dst_id);
	काष्ठा btf_type *src_t = btf_type_by_id(src_btf, src_id);
	काष्ठा btf_param *src_p, *dst_p;
	स्थिर अक्षर *s;
	पूर्णांक i, n, off;

	/* We alपढ़ोy made sure that source and destination types (FUNC or
	 * VAR) match in terms of types and argument names.
	 */
	अगर (btf_is_var(dst_t)) अणु
		btf_var(dst_t)->linkage = BTF_VAR_GLOBAL_ALLOCATED;
		वापस 0;
	पूर्ण

	dst_t->info = btf_type_info(BTF_KIND_FUNC, BTF_FUNC_GLOBAL, 0);

	/* now onto FUNC_PROTO types */
	src_t = btf_type_by_id(src_btf, src_t->type);
	dst_t = btf_type_by_id(dst_btf, dst_t->type);

	/* Fill in all the argument names, which क्रम बाह्य FUNCs are missing.
	 * We'll end up with two copies of FUNCs/VARs क्रम बाह्यs, but that
	 * will be taken care of by BTF dedup at the very end.
	 * It might be that BTF types क्रम बाह्य in one file has less/more BTF
	 * inक्रमmation (e.g., FWD instead of full STRUCT/UNION inक्रमmation),
	 * but that should be (in most हालs, subject to BTF dedup rules)
	 * handled and resolved by BTF dedup algorithm as well, so we won't
	 * worry about it. Our only job is to make sure that argument names
	 * are populated on both sides, otherwise BTF dedup will pedantically
	 * consider them dअगरferent.
	 */
	src_p = btf_params(src_t);
	dst_p = btf_params(dst_t);
	क्रम (i = 0, n = btf_vlen(dst_t); i < n; i++, src_p++, dst_p++) अणु
		अगर (!src_p->name_off)
			जारी;

		/* src_btf has more complete info, so add name to dst_btf */
		s = btf__str_by_offset(src_btf, src_p->name_off);
		off = btf__add_str(dst_btf, s);
		अगर (off < 0)
			वापस off;
		dst_p->name_off = off;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम sym_update_bind(Elf64_Sym *sym, पूर्णांक sym_bind)
अणु
	sym->st_info = ELF64_ST_INFO(sym_bind, ELF64_ST_TYPE(sym->st_info));
पूर्ण

अटल व्योम sym_update_type(Elf64_Sym *sym, पूर्णांक sym_type)
अणु
	sym->st_info = ELF64_ST_INFO(ELF64_ST_BIND(sym->st_info), sym_type);
पूर्ण

अटल व्योम sym_update_visibility(Elf64_Sym *sym, पूर्णांक sym_vis)
अणु
	/* libelf करोesn't provide setters क्रम ST_VISIBILITY,
	 * but it is stored in the lower 2 bits of st_other
	 */
	sym->st_other &= 0x03;
	sym->st_other |= sym_vis;
पूर्ण

अटल पूर्णांक linker_append_elf_sym(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj,
				 Elf64_Sym *sym, स्थिर अक्षर *sym_name, पूर्णांक src_sym_idx)
अणु
	काष्ठा src_sec *src_sec = शून्य;
	काष्ठा dst_sec *dst_sec = शून्य;
	काष्ठा glob_sym *glob_sym = शून्य;
	पूर्णांक name_off, sym_type, sym_bind, sym_vis, err;
	पूर्णांक btf_sec_id = 0, btf_id = 0;
	माप_प्रकार dst_sym_idx;
	Elf64_Sym *dst_sym;
	bool sym_is_बाह्य;

	sym_type = ELF64_ST_TYPE(sym->st_info);
	sym_bind = ELF64_ST_BIND(sym->st_info);
	sym_vis = ELF64_ST_VISIBILITY(sym->st_other);
	sym_is_बाह्य = sym->st_shndx == SHN_UNDEF;

	अगर (sym_is_बाह्य) अणु
		अगर (!obj->btf) अणु
			pr_warn("externs without BTF info are not supported\n");
			वापस -ENOTSUP;
		पूर्ण
	पूर्ण अन्यथा अगर (sym->st_shndx < SHN_LORESERVE) अणु
		src_sec = &obj->secs[sym->st_shndx];
		अगर (src_sec->skipped)
			वापस 0;
		dst_sec = &linker->secs[src_sec->dst_id];

		/* allow only one STT_SECTION symbol per section */
		अगर (sym_type == STT_SECTION && dst_sec->sec_sym_idx) अणु
			obj->sym_map[src_sym_idx] = dst_sec->sec_sym_idx;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (sym_bind == STB_LOCAL)
		जाओ add_sym;

	/* find matching BTF info */
	err = find_glob_sym_btf(obj, sym, sym_name, &btf_sec_id, &btf_id);
	अगर (err)
		वापस err;

	अगर (sym_is_बाह्य && btf_sec_id) अणु
		स्थिर अक्षर *sec_name = शून्य;
		स्थिर काष्ठा btf_type *t;

		t = btf__type_by_id(obj->btf, btf_sec_id);
		sec_name = btf__str_by_offset(obj->btf, t->name_off);

		/* Clang माला_दो unannotated बाह्य vars पूर्णांकo
		 * '.extern' BTF DATASEC. Treat them the same
		 * as unannotated बाह्य funcs (which are
		 * currently not put पूर्णांकo any DATASECs).
		 * Those करोn't have associated src_sec/dst_sec.
		 */
		अगर (म_भेद(sec_name, BTF_EXTERN_SEC) != 0) अणु
			src_sec = find_src_sec_by_name(obj, sec_name);
			अगर (!src_sec) अणु
				pr_warn("failed to find matching ELF sec '%s'\n", sec_name);
				वापस -ENOENT;
			पूर्ण
			dst_sec = &linker->secs[src_sec->dst_id];
		पूर्ण
	पूर्ण

	glob_sym = find_glob_sym(linker, sym_name);
	अगर (glob_sym) अणु
		/* Preventively resolve to existing symbol. This is
		 * needed क्रम further relocation symbol remapping in
		 * the next step of linking.
		 */
		obj->sym_map[src_sym_idx] = glob_sym->sym_idx;

		/* If both symbols are non-बाह्यs, at least one of
		 * them has to be STB_WEAK, otherwise they are in
		 * a conflict with each other.
		 */
		अगर (!sym_is_बाह्य && !glob_sym->is_बाह्य
		    && !glob_sym->is_weak && sym_bind != STB_WEAK) अणु
			pr_warn("conflicting non-weak symbol #%d (%s) definition in '%s'\n",
				src_sym_idx, sym_name, obj->filename);
			वापस -EINVAL;
		पूर्ण

		अगर (!glob_syms_match(sym_name, linker, glob_sym, obj, sym, src_sym_idx, btf_id))
			वापस -EINVAL;

		dst_sym = get_sym_by_idx(linker, glob_sym->sym_idx);

		/* If new symbol is strong, then क्रमce dst_sym to be strong as
		 * well; this way a mix of weak and non-weak बाह्य
		 * definitions will end up being strong.
		 */
		अगर (sym_bind == STB_GLOBAL) अणु
			/* We still need to preserve type (NOTYPE or
			 * OBJECT/FUNC, depending on whether the symbol is
			 * बाह्य or not)
			 */
			sym_update_bind(dst_sym, STB_GLOBAL);
			glob_sym->is_weak = false;
		पूर्ण

		/* Non-शेष visibility is "contaminating", with stricter
		 * visibility overwriting more permissive ones, even अगर more
		 * permissive visibility comes from just an बाह्य definition.
		 * Currently only STV_DEFAULT and STV_HIDDEN are allowed and
		 * ensured by ELF symbol sanity checks above.
		 */
		अगर (sym_vis > ELF64_ST_VISIBILITY(dst_sym->st_other))
			sym_update_visibility(dst_sym, sym_vis);

		/* If the new symbol is बाह्य, then regardless अगर
		 * existing symbol is बाह्य or resolved global, just
		 * keep the existing one untouched.
		 */
		अगर (sym_is_बाह्य)
			वापस 0;

		/* If existing symbol is a strong resolved symbol, bail out,
		 * because we lost resolution battle have nothing to
		 * contribute. We alपढ़ोy checked abover that there is no
		 * strong-strong conflict. We also alपढ़ोy tightened binding
		 * and visibility, so nothing अन्यथा to contribute at that poपूर्णांक.
		 */
		अगर (!glob_sym->is_बाह्य && sym_bind == STB_WEAK)
			वापस 0;

		/* At this poपूर्णांक, new symbol is strong non-बाह्य,
		 * so overग_लिखो glob_sym with new symbol inक्रमmation.
		 * Preserve binding and visibility.
		 */
		sym_update_type(dst_sym, sym_type);
		dst_sym->st_shndx = dst_sec->sec_idx;
		dst_sym->st_value = src_sec->dst_off + sym->st_value;
		dst_sym->st_size = sym->st_size;

		/* see comment below about dst_sec->id vs dst_sec->sec_idx */
		glob_sym->sec_id = dst_sec->id;
		glob_sym->is_बाह्य = false;

		अगर (complete_बाह्य_btf_info(linker->btf, glob_sym->btf_id,
					     obj->btf, btf_id))
			वापस -EINVAL;

		/* request updating VAR's/FUNC's underlying BTF type when appending BTF type */
		glob_sym->underlying_btf_id = 0;

		obj->sym_map[src_sym_idx] = glob_sym->sym_idx;
		वापस 0;
	पूर्ण

add_sym:
	name_off = strset__add_str(linker->strtab_strs, sym_name);
	अगर (name_off < 0)
		वापस name_off;

	dst_sym = add_new_sym(linker, &dst_sym_idx);
	अगर (!dst_sym)
		वापस -ENOMEM;

	dst_sym->st_name = name_off;
	dst_sym->st_info = sym->st_info;
	dst_sym->st_other = sym->st_other;
	dst_sym->st_shndx = dst_sec ? dst_sec->sec_idx : sym->st_shndx;
	dst_sym->st_value = (src_sec ? src_sec->dst_off : 0) + sym->st_value;
	dst_sym->st_size = sym->st_size;

	obj->sym_map[src_sym_idx] = dst_sym_idx;

	अगर (sym_type == STT_SECTION && dst_sym) अणु
		dst_sec->sec_sym_idx = dst_sym_idx;
		dst_sym->st_value = 0;
	पूर्ण

	अगर (sym_bind != STB_LOCAL) अणु
		glob_sym = add_glob_sym(linker);
		अगर (!glob_sym)
			वापस -ENOMEM;

		glob_sym->sym_idx = dst_sym_idx;
		/* we use dst_sec->id (and not dst_sec->sec_idx), because
		 * ephemeral sections (.kconfig, .ksyms, etc) करोn't have
		 * sec_idx (as they करोn't have corresponding ELF section), but
		 * still have id. .बाह्य करोesn't have even ephemeral section
		 * associated with it, so dst_sec->id == dst_sec->sec_idx == 0.
		 */
		glob_sym->sec_id = dst_sec ? dst_sec->id : 0;
		glob_sym->name_off = name_off;
		/* we will fill btf_id in during BTF merging step */
		glob_sym->btf_id = 0;
		glob_sym->is_बाह्य = sym_is_बाह्य;
		glob_sym->is_weak = sym_bind == STB_WEAK;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक linker_append_elf_relos(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj)
अणु
	काष्ठा src_sec *src_symtab = &obj->secs[obj->symtab_sec_idx];
	काष्ठा dst_sec *dst_symtab = &linker->secs[linker->symtab_sec_idx];
	पूर्णांक i, err;

	क्रम (i = 1; i < obj->sec_cnt; i++) अणु
		काष्ठा src_sec *src_sec, *src_linked_sec;
		काष्ठा dst_sec *dst_sec, *dst_linked_sec;
		Elf64_Rel *src_rel, *dst_rel;
		पूर्णांक j, n;

		src_sec = &obj->secs[i];
		अगर (!is_relo_sec(src_sec))
			जारी;

		/* shdr->sh_info poपूर्णांकs to relocatable section */
		src_linked_sec = &obj->secs[src_sec->shdr->sh_info];
		अगर (src_linked_sec->skipped)
			जारी;

		dst_sec = find_dst_sec_by_name(linker, src_sec->sec_name);
		अगर (!dst_sec) अणु
			dst_sec = add_dst_sec(linker, src_sec->sec_name);
			अगर (!dst_sec)
				वापस -ENOMEM;
			err = init_sec(linker, dst_sec, src_sec);
			अगर (err) अणु
				pr_warn("failed to init section '%s'\n", src_sec->sec_name);
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अगर (!secs_match(dst_sec, src_sec)) अणु
			pr_warn("sections %s are not compatible\n", src_sec->sec_name);
			वापस -1;
		पूर्ण

		/* shdr->sh_link poपूर्णांकs to SYMTAB */
		dst_sec->shdr->sh_link = linker->symtab_sec_idx;

		/* shdr->sh_info poपूर्णांकs to relocated section */
		dst_linked_sec = &linker->secs[src_linked_sec->dst_id];
		dst_sec->shdr->sh_info = dst_linked_sec->sec_idx;

		src_sec->dst_id = dst_sec->id;
		err = extend_sec(linker, dst_sec, src_sec);
		अगर (err)
			वापस err;

		src_rel = src_sec->data->d_buf;
		dst_rel = dst_sec->raw_data + src_sec->dst_off;
		n = src_sec->shdr->sh_size / src_sec->shdr->sh_entsize;
		क्रम (j = 0; j < n; j++, src_rel++, dst_rel++) अणु
			माप_प्रकार src_sym_idx = ELF64_R_SYM(src_rel->r_info);
			माप_प्रकार sym_type = ELF64_R_TYPE(src_rel->r_info);
			Elf64_Sym *src_sym, *dst_sym;
			माप_प्रकार dst_sym_idx;

			src_sym_idx = ELF64_R_SYM(src_rel->r_info);
			src_sym = src_symtab->data->d_buf + माप(*src_sym) * src_sym_idx;

			dst_sym_idx = obj->sym_map[src_sym_idx];
			dst_sym = dst_symtab->raw_data + माप(*dst_sym) * dst_sym_idx;
			dst_rel->r_offset += src_linked_sec->dst_off;
			sym_type = ELF64_R_TYPE(src_rel->r_info);
			dst_rel->r_info = ELF64_R_INFO(dst_sym_idx, sym_type);

			अगर (ELF64_ST_TYPE(src_sym->st_info) == STT_SECTION) अणु
				काष्ठा src_sec *sec = &obj->secs[src_sym->st_shndx];
				काष्ठा bpf_insn *insn;

				अगर (src_linked_sec->shdr->sh_flags & SHF_EXECINSTR) अणु
					/* calls to the very first अटल function inside
					 * .text section at offset 0 will
					 * reference section symbol, not the
					 * function symbol. Fix that up,
					 * otherwise it won't be possible to
					 * relocate calls to two dअगरferent
					 * अटल functions with the same name
					 * (rom two dअगरferent object files)
					 */
					insn = dst_linked_sec->raw_data + dst_rel->r_offset;
					अगर (insn->code == (BPF_JMP | BPF_CALL))
						insn->imm += sec->dst_off / माप(काष्ठा bpf_insn);
					अन्यथा
						insn->imm += sec->dst_off;
				पूर्ण अन्यथा अणु
					pr_warn("relocation against STT_SECTION in non-exec section is not supported!\n");
					वापस -EINVAL;
				पूर्ण
			पूर्ण

		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल Elf64_Sym *find_sym_by_name(काष्ठा src_obj *obj, माप_प्रकार sec_idx,
				   पूर्णांक sym_type, स्थिर अक्षर *sym_name)
अणु
	काष्ठा src_sec *symtab = &obj->secs[obj->symtab_sec_idx];
	Elf64_Sym *sym = symtab->data->d_buf;
	पूर्णांक i, n = symtab->shdr->sh_size / symtab->shdr->sh_entsize;
	पूर्णांक str_sec_idx = symtab->shdr->sh_link;
	स्थिर अक्षर *name;

	क्रम (i = 0; i < n; i++, sym++) अणु
		अगर (sym->st_shndx != sec_idx)
			जारी;
		अगर (ELF64_ST_TYPE(sym->st_info) != sym_type)
			जारी;

		name = elf_strptr(obj->elf, str_sec_idx, sym->st_name);
		अगर (!name)
			वापस शून्य;

		अगर (म_भेद(sym_name, name) != 0)
			जारी;

		वापस sym;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक linker_fixup_btf(काष्ठा src_obj *obj)
अणु
	स्थिर अक्षर *sec_name;
	काष्ठा src_sec *sec;
	पूर्णांक i, j, n, m;

	अगर (!obj->btf)
		वापस 0;

	n = btf__get_nr_types(obj->btf);
	क्रम (i = 1; i <= n; i++) अणु
		काष्ठा btf_var_secinfo *vi;
		काष्ठा btf_type *t;

		t = btf_type_by_id(obj->btf, i);
		अगर (btf_kind(t) != BTF_KIND_DATASEC)
			जारी;

		sec_name = btf__str_by_offset(obj->btf, t->name_off);
		sec = find_src_sec_by_name(obj, sec_name);
		अगर (sec) अणु
			/* record actual section size, unless ephemeral */
			अगर (sec->shdr)
				t->size = sec->shdr->sh_size;
		पूर्ण अन्यथा अणु
			/* BTF can have some sections that are not represented
			 * in ELF, e.g., .kconfig, .ksyms, .बाह्य, which are used
			 * क्रम special बाह्य variables.
			 *
			 * For all but one such special (ephemeral)
			 * sections, we pre-create "section shells" to be able
			 * to keep track of extra per-section metadata later
			 * (e.g., those BTF बाह्य variables).
			 *
			 * .बाह्य is even more special, though, because it
			 * contains बाह्य variables that need to be resolved
			 * by अटल linker, not libbpf and kernel. When such
			 * बाह्यs are resolved, we are going to हटाओ them
			 * from .बाह्य BTF section and might end up not
			 * needing it at all. Each resolved बाह्य should have
			 * matching non-बाह्य VAR/FUNC in other sections.
			 *
			 * We करो support leaving some of the बाह्यs
			 * unresolved, though, to support हालs of building
			 * libraries, which will later be linked against final
			 * BPF applications. So अगर at finalization we still
			 * see unresolved बाह्यs, we'll create .बाह्य
			 * section on our own.
			 */
			अगर (म_भेद(sec_name, BTF_EXTERN_SEC) == 0)
				जारी;

			sec = add_src_sec(obj, sec_name);
			अगर (!sec)
				वापस -ENOMEM;

			sec->ephemeral = true;
			sec->sec_idx = 0; /* will match UNDEF shndx in ELF */
		पूर्ण

		/* remember ELF section and its BTF type ID match */
		sec->sec_type_id = i;

		/* fix up variable offsets */
		vi = btf_var_secinfos(t);
		क्रम (j = 0, m = btf_vlen(t); j < m; j++, vi++) अणु
			स्थिर काष्ठा btf_type *vt = btf__type_by_id(obj->btf, vi->type);
			स्थिर अक्षर *var_name = btf__str_by_offset(obj->btf, vt->name_off);
			पूर्णांक var_linkage = btf_var(vt)->linkage;
			Elf64_Sym *sym;

			/* no need to patch up अटल or बाह्य vars */
			अगर (var_linkage != BTF_VAR_GLOBAL_ALLOCATED)
				जारी;

			sym = find_sym_by_name(obj, sec->sec_idx, STT_OBJECT, var_name);
			अगर (!sym) अणु
				pr_warn("failed to find symbol for variable '%s' in section '%s'\n", var_name, sec_name);
				वापस -ENOENT;
			पूर्ण

			vi->offset = sym->st_value;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक remap_type_id(__u32 *type_id, व्योम *ctx)
अणु
	पूर्णांक *id_map = ctx;
	पूर्णांक new_id = id_map[*type_id];

	/* Error out अगर the type wasn't remapped. Ignore VOID which stays VOID. */
	अगर (new_id == 0 && *type_id != 0) अणु
		pr_warn("failed to find new ID mapping for original BTF type ID %u\n", *type_id);
		वापस -EINVAL;
	पूर्ण

	*type_id = id_map[*type_id];

	वापस 0;
पूर्ण

अटल पूर्णांक linker_append_btf(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj)
अणु
	स्थिर काष्ठा btf_type *t;
	पूर्णांक i, j, n, start_id, id;
	स्थिर अक्षर *name;

	अगर (!obj->btf)
		वापस 0;

	start_id = btf__get_nr_types(linker->btf) + 1;
	n = btf__get_nr_types(obj->btf);

	obj->btf_type_map = सुस्मृति(n + 1, माप(पूर्णांक));
	अगर (!obj->btf_type_map)
		वापस -ENOMEM;

	क्रम (i = 1; i <= n; i++) अणु
		काष्ठा glob_sym *glob_sym = शून्य;

		t = btf__type_by_id(obj->btf, i);

		/* DATASECs are handled specially below */
		अगर (btf_kind(t) == BTF_KIND_DATASEC)
			जारी;

		अगर (btf_is_non_अटल(t)) अणु
			/* there should be glob_sym alपढ़ोy */
			name = btf__str_by_offset(obj->btf, t->name_off);
			glob_sym = find_glob_sym(linker, name);

			/* VARs without corresponding glob_sym are those that
			 * beदीर्घ to skipped/deduplicated sections (i.e.,
			 * license and version), so just skip them
			 */
			अगर (!glob_sym)
				जारी;

			/* linker_append_elf_sym() might have requested
			 * updating underlying type ID, अगर बाह्य was resolved
			 * to strong symbol or weak got upgraded to non-weak
			 */
			अगर (glob_sym->underlying_btf_id == 0)
				glob_sym->underlying_btf_id = -t->type;

			/* globals from previous object files that match our
			 * VAR/FUNC alपढ़ोy have a corresponding associated
			 * BTF type, so just make sure to use it
			 */
			अगर (glob_sym->btf_id) अणु
				/* reuse existing BTF type क्रम global var/func */
				obj->btf_type_map[i] = glob_sym->btf_id;
				जारी;
			पूर्ण
		पूर्ण

		id = btf__add_type(linker->btf, obj->btf, t);
		अगर (id < 0) अणु
			pr_warn("failed to append BTF type #%d from file '%s'\n", i, obj->filename);
			वापस id;
		पूर्ण

		obj->btf_type_map[i] = id;

		/* record just appended BTF type क्रम var/func */
		अगर (glob_sym) अणु
			glob_sym->btf_id = id;
			glob_sym->underlying_btf_id = -t->type;
		पूर्ण
	पूर्ण

	/* remap all the types except DATASECs */
	n = btf__get_nr_types(linker->btf);
	क्रम (i = start_id; i <= n; i++) अणु
		काष्ठा btf_type *dst_t = btf_type_by_id(linker->btf, i);

		अगर (btf_type_visit_type_ids(dst_t, remap_type_id, obj->btf_type_map))
			वापस -EINVAL;
	पूर्ण

	/* Reग_लिखो VAR/FUNC underlying types (i.e., FUNC's FUNC_PROTO and VAR's
	 * actual type), अगर necessary
	 */
	क्रम (i = 0; i < linker->glob_sym_cnt; i++) अणु
		काष्ठा glob_sym *glob_sym = &linker->glob_syms[i];
		काष्ठा btf_type *glob_t;

		अगर (glob_sym->underlying_btf_id >= 0)
			जारी;

		glob_sym->underlying_btf_id = obj->btf_type_map[-glob_sym->underlying_btf_id];

		glob_t = btf_type_by_id(linker->btf, glob_sym->btf_id);
		glob_t->type = glob_sym->underlying_btf_id;
	पूर्ण

	/* append DATASEC info */
	क्रम (i = 1; i < obj->sec_cnt; i++) अणु
		काष्ठा src_sec *src_sec;
		काष्ठा dst_sec *dst_sec;
		स्थिर काष्ठा btf_var_secinfo *src_var;
		काष्ठा btf_var_secinfo *dst_var;

		src_sec = &obj->secs[i];
		अगर (!src_sec->sec_type_id || src_sec->skipped)
			जारी;
		dst_sec = &linker->secs[src_sec->dst_id];

		/* Mark section as having BTF regardless of the presence of
		 * variables. In some हालs compiler might generate empty BTF
		 * with no variables inक्रमmation. E.g., when promoting local
		 * array/काष्ठाure variable initial values and BPF object
		 * file otherwise has no पढ़ो-only अटल variables in
		 * .rodata. We need to preserve such empty BTF and just set
		 * correct section size.
		 */
		dst_sec->has_btf = true;

		t = btf__type_by_id(obj->btf, src_sec->sec_type_id);
		src_var = btf_var_secinfos(t);
		n = btf_vlen(t);
		क्रम (j = 0; j < n; j++, src_var++) अणु
			व्योम *sec_vars = dst_sec->sec_vars;
			पूर्णांक new_id = obj->btf_type_map[src_var->type];
			काष्ठा glob_sym *glob_sym = शून्य;

			t = btf_type_by_id(linker->btf, new_id);
			अगर (btf_is_non_अटल(t)) अणु
				name = btf__str_by_offset(linker->btf, t->name_off);
				glob_sym = find_glob_sym(linker, name);
				अगर (glob_sym->sec_id != dst_sec->id) अणु
					pr_warn("global '%s': section mismatch %d vs %d\n",
						name, glob_sym->sec_id, dst_sec->id);
					वापस -EINVAL;
				पूर्ण
			पूर्ण

			/* If there is alपढ़ोy a member (VAR or FUNC) mapped
			 * to the same type, करोn't add a duplicate entry.
			 * This will happen when multiple object files define
			 * the same बाह्य VARs/FUNCs.
			 */
			अगर (glob_sym && glob_sym->var_idx >= 0) अणु
				__s64 sz;

				dst_var = &dst_sec->sec_vars[glob_sym->var_idx];
				/* Because underlying BTF type might have
				 * changed, so might its size have changed, so
				 * re-calculate and update it in sec_var.
				 */
				sz = btf__resolve_size(linker->btf, glob_sym->underlying_btf_id);
				अगर (sz < 0) अणु
					pr_warn("global '%s': failed to resolve size of underlying type: %d\n",
						name, (पूर्णांक)sz);
					वापस -EINVAL;
				पूर्ण
				dst_var->size = sz;
				जारी;
			पूर्ण

			sec_vars = libbpf_पुनः_स्मृतिarray(sec_vars,
						       dst_sec->sec_var_cnt + 1,
						       माप(*dst_sec->sec_vars));
			अगर (!sec_vars)
				वापस -ENOMEM;

			dst_sec->sec_vars = sec_vars;
			dst_sec->sec_var_cnt++;

			dst_var = &dst_sec->sec_vars[dst_sec->sec_var_cnt - 1];
			dst_var->type = obj->btf_type_map[src_var->type];
			dst_var->size = src_var->size;
			dst_var->offset = src_sec->dst_off + src_var->offset;

			अगर (glob_sym)
				glob_sym->var_idx = dst_sec->sec_var_cnt - 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम *add_btf_ext_rec(काष्ठा btf_ext_sec_data *ext_data, स्थिर व्योम *src_rec)
अणु
	व्योम *पंचांगp;

	पंचांगp = libbpf_पुनः_स्मृतिarray(ext_data->recs, ext_data->rec_cnt + 1, ext_data->rec_sz);
	अगर (!पंचांगp)
		वापस शून्य;
	ext_data->recs = पंचांगp;

	पंचांगp += ext_data->rec_cnt * ext_data->rec_sz;
	स_नकल(पंचांगp, src_rec, ext_data->rec_sz);

	ext_data->rec_cnt++;

	वापस पंचांगp;
पूर्ण

अटल पूर्णांक linker_append_btf_ext(काष्ठा bpf_linker *linker, काष्ठा src_obj *obj)
अणु
	स्थिर काष्ठा btf_ext_info_sec *ext_sec;
	स्थिर अक्षर *sec_name, *s;
	काष्ठा src_sec *src_sec;
	काष्ठा dst_sec *dst_sec;
	पूर्णांक rec_sz, str_off, i;

	अगर (!obj->btf_ext)
		वापस 0;

	rec_sz = obj->btf_ext->func_info.rec_size;
	क्रम_each_btf_ext_sec(&obj->btf_ext->func_info, ext_sec) अणु
		काष्ठा bpf_func_info_min *src_rec, *dst_rec;

		sec_name = btf__name_by_offset(obj->btf, ext_sec->sec_name_off);
		src_sec = find_src_sec_by_name(obj, sec_name);
		अगर (!src_sec) अणु
			pr_warn("can't find section '%s' referenced from .BTF.ext\n", sec_name);
			वापस -EINVAL;
		पूर्ण
		dst_sec = &linker->secs[src_sec->dst_id];

		अगर (dst_sec->func_info.rec_sz == 0)
			dst_sec->func_info.rec_sz = rec_sz;
		अगर (dst_sec->func_info.rec_sz != rec_sz) अणु
			pr_warn("incompatible .BTF.ext record sizes for section '%s'\n", sec_name);
			वापस -EINVAL;
		पूर्ण

		क्रम_each_btf_ext_rec(&obj->btf_ext->func_info, ext_sec, i, src_rec) अणु
			dst_rec = add_btf_ext_rec(&dst_sec->func_info, src_rec);
			अगर (!dst_rec)
				वापस -ENOMEM;

			dst_rec->insn_off += src_sec->dst_off;
			dst_rec->type_id = obj->btf_type_map[dst_rec->type_id];
		पूर्ण
	पूर्ण

	rec_sz = obj->btf_ext->line_info.rec_size;
	क्रम_each_btf_ext_sec(&obj->btf_ext->line_info, ext_sec) अणु
		काष्ठा bpf_line_info_min *src_rec, *dst_rec;

		sec_name = btf__name_by_offset(obj->btf, ext_sec->sec_name_off);
		src_sec = find_src_sec_by_name(obj, sec_name);
		अगर (!src_sec) अणु
			pr_warn("can't find section '%s' referenced from .BTF.ext\n", sec_name);
			वापस -EINVAL;
		पूर्ण
		dst_sec = &linker->secs[src_sec->dst_id];

		अगर (dst_sec->line_info.rec_sz == 0)
			dst_sec->line_info.rec_sz = rec_sz;
		अगर (dst_sec->line_info.rec_sz != rec_sz) अणु
			pr_warn("incompatible .BTF.ext record sizes for section '%s'\n", sec_name);
			वापस -EINVAL;
		पूर्ण

		क्रम_each_btf_ext_rec(&obj->btf_ext->line_info, ext_sec, i, src_rec) अणु
			dst_rec = add_btf_ext_rec(&dst_sec->line_info, src_rec);
			अगर (!dst_rec)
				वापस -ENOMEM;

			dst_rec->insn_off += src_sec->dst_off;

			s = btf__str_by_offset(obj->btf, src_rec->file_name_off);
			str_off = btf__add_str(linker->btf, s);
			अगर (str_off < 0)
				वापस -ENOMEM;
			dst_rec->file_name_off = str_off;

			s = btf__str_by_offset(obj->btf, src_rec->line_off);
			str_off = btf__add_str(linker->btf, s);
			अगर (str_off < 0)
				वापस -ENOMEM;
			dst_rec->line_off = str_off;

			/* dst_rec->line_col is fine */
		पूर्ण
	पूर्ण

	rec_sz = obj->btf_ext->core_relo_info.rec_size;
	क्रम_each_btf_ext_sec(&obj->btf_ext->core_relo_info, ext_sec) अणु
		काष्ठा bpf_core_relo *src_rec, *dst_rec;

		sec_name = btf__name_by_offset(obj->btf, ext_sec->sec_name_off);
		src_sec = find_src_sec_by_name(obj, sec_name);
		अगर (!src_sec) अणु
			pr_warn("can't find section '%s' referenced from .BTF.ext\n", sec_name);
			वापस -EINVAL;
		पूर्ण
		dst_sec = &linker->secs[src_sec->dst_id];

		अगर (dst_sec->core_relo_info.rec_sz == 0)
			dst_sec->core_relo_info.rec_sz = rec_sz;
		अगर (dst_sec->core_relo_info.rec_sz != rec_sz) अणु
			pr_warn("incompatible .BTF.ext record sizes for section '%s'\n", sec_name);
			वापस -EINVAL;
		पूर्ण

		क्रम_each_btf_ext_rec(&obj->btf_ext->core_relo_info, ext_sec, i, src_rec) अणु
			dst_rec = add_btf_ext_rec(&dst_sec->core_relo_info, src_rec);
			अगर (!dst_rec)
				वापस -ENOMEM;

			dst_rec->insn_off += src_sec->dst_off;
			dst_rec->type_id = obj->btf_type_map[dst_rec->type_id];

			s = btf__str_by_offset(obj->btf, src_rec->access_str_off);
			str_off = btf__add_str(linker->btf, s);
			अगर (str_off < 0)
				वापस -ENOMEM;
			dst_rec->access_str_off = str_off;

			/* dst_rec->kind is fine */
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक bpf_linker__finalize(काष्ठा bpf_linker *linker)
अणु
	काष्ठा dst_sec *sec;
	माप_प्रकार strs_sz;
	स्थिर व्योम *strs;
	पूर्णांक err, i;

	अगर (!linker->elf)
		वापस -EINVAL;

	err = finalize_btf(linker);
	अगर (err)
		वापस err;

	/* Finalize strings */
	strs_sz = strset__data_size(linker->strtab_strs);
	strs = strset__data(linker->strtab_strs);

	sec = &linker->secs[linker->strtab_sec_idx];
	sec->data->d_align = 1;
	sec->data->d_off = 0LL;
	sec->data->d_buf = (व्योम *)strs;
	sec->data->d_type = ELF_T_BYTE;
	sec->data->d_size = strs_sz;
	sec->shdr->sh_size = strs_sz;

	क्रम (i = 1; i < linker->sec_cnt; i++) अणु
		sec = &linker->secs[i];

		/* STRTAB is handled specially above */
		अगर (sec->sec_idx == linker->strtab_sec_idx)
			जारी;

		/* special ephemeral sections (.ksyms, .kconfig, etc) */
		अगर (!sec->scn)
			जारी;

		sec->data->d_buf = sec->raw_data;
	पूर्ण

	/* Finalize ELF layout */
	अगर (elf_update(linker->elf, ELF_C_शून्य) < 0) अणु
		err = -त्रुटि_सं;
		pr_warn_elf("failed to finalize ELF layout");
		वापस err;
	पूर्ण

	/* Write out final ELF contents */
	अगर (elf_update(linker->elf, ELF_C_WRITE) < 0) अणु
		err = -त्रुटि_सं;
		pr_warn_elf("failed to write ELF contents");
		वापस err;
	पूर्ण

	elf_end(linker->elf);
	बंद(linker->fd);

	linker->elf = शून्य;
	linker->fd = -1;

	वापस 0;
पूर्ण

अटल पूर्णांक emit_elf_data_sec(काष्ठा bpf_linker *linker, स्थिर अक्षर *sec_name,
			     माप_प्रकार align, स्थिर व्योम *raw_data, माप_प्रकार raw_sz)
अणु
	Elf_Scn *scn;
	Elf_Data *data;
	Elf64_Shdr *shdr;
	पूर्णांक name_off;

	name_off = strset__add_str(linker->strtab_strs, sec_name);
	अगर (name_off < 0)
		वापस name_off;

	scn = elf_newscn(linker->elf);
	अगर (!scn)
		वापस -ENOMEM;
	data = elf_newdata(scn);
	अगर (!data)
		वापस -ENOMEM;
	shdr = elf64_माला_लोhdr(scn);
	अगर (!shdr)
		वापस -EINVAL;

	shdr->sh_name = name_off;
	shdr->sh_type = SHT_PROGBITS;
	shdr->sh_flags = 0;
	shdr->sh_size = raw_sz;
	shdr->sh_link = 0;
	shdr->sh_info = 0;
	shdr->sh_addralign = align;
	shdr->sh_entsize = 0;

	data->d_type = ELF_T_BYTE;
	data->d_size = raw_sz;
	data->d_buf = (व्योम *)raw_data;
	data->d_align = align;
	data->d_off = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक finalize_btf(काष्ठा bpf_linker *linker)
अणु
	काष्ठा btf *btf = linker->btf;
	स्थिर व्योम *raw_data;
	पूर्णांक i, j, id, err;
	__u32 raw_sz;

	/* bail out अगर no BTF data was produced */
	अगर (btf__get_nr_types(linker->btf) == 0)
		वापस 0;

	क्रम (i = 1; i < linker->sec_cnt; i++) अणु
		काष्ठा dst_sec *sec = &linker->secs[i];

		अगर (!sec->has_btf)
			जारी;

		id = btf__add_datasec(btf, sec->sec_name, sec->sec_sz);
		अगर (id < 0) अणु
			pr_warn("failed to add consolidated BTF type for datasec '%s': %d\n",
				sec->sec_name, id);
			वापस id;
		पूर्ण

		क्रम (j = 0; j < sec->sec_var_cnt; j++) अणु
			काष्ठा btf_var_secinfo *vi = &sec->sec_vars[j];

			अगर (btf__add_datasec_var_info(btf, vi->type, vi->offset, vi->size))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	err = finalize_btf_ext(linker);
	अगर (err) अणु
		pr_warn(".BTF.ext generation failed: %d\n", err);
		वापस err;
	पूर्ण

	err = btf__dedup(linker->btf, linker->btf_ext, शून्य);
	अगर (err) अणु
		pr_warn("BTF dedup failed: %d\n", err);
		वापस err;
	पूर्ण

	/* Emit .BTF section */
	raw_data = btf__get_raw_data(linker->btf, &raw_sz);
	अगर (!raw_data)
		वापस -ENOMEM;

	err = emit_elf_data_sec(linker, BTF_ELF_SEC, 8, raw_data, raw_sz);
	अगर (err) अणु
		pr_warn("failed to write out .BTF ELF section: %d\n", err);
		वापस err;
	पूर्ण

	/* Emit .BTF.ext section */
	अगर (linker->btf_ext) अणु
		raw_data = btf_ext__get_raw_data(linker->btf_ext, &raw_sz);
		अगर (!raw_data)
			वापस -ENOMEM;

		err = emit_elf_data_sec(linker, BTF_EXT_ELF_SEC, 8, raw_data, raw_sz);
		अगर (err) अणु
			pr_warn("failed to write out .BTF.ext ELF section: %d\n", err);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emit_btf_ext_data(काष्ठा bpf_linker *linker, व्योम *output,
			     स्थिर अक्षर *sec_name, काष्ठा btf_ext_sec_data *sec_data)
अणु
	काष्ठा btf_ext_info_sec *sec_info;
	व्योम *cur = output;
	पूर्णांक str_off;
	माप_प्रकार sz;

	अगर (!sec_data->rec_cnt)
		वापस 0;

	str_off = btf__add_str(linker->btf, sec_name);
	अगर (str_off < 0)
		वापस -ENOMEM;

	sec_info = cur;
	sec_info->sec_name_off = str_off;
	sec_info->num_info = sec_data->rec_cnt;
	cur += माप(काष्ठा btf_ext_info_sec);

	sz = sec_data->rec_cnt * sec_data->rec_sz;
	स_नकल(cur, sec_data->recs, sz);
	cur += sz;

	वापस cur - output;
पूर्ण

अटल पूर्णांक finalize_btf_ext(काष्ठा bpf_linker *linker)
अणु
	माप_प्रकार funcs_sz = 0, lines_sz = 0, core_relos_sz = 0, total_sz = 0;
	माप_प्रकार func_rec_sz = 0, line_rec_sz = 0, core_relo_rec_sz = 0;
	काष्ठा btf_ext_header *hdr;
	व्योम *data, *cur;
	पूर्णांक i, err, sz;

	/* validate that all sections have the same .BTF.ext record sizes
	 * and calculate total data size क्रम each type of data (func info,
	 * line info, core relos)
	 */
	क्रम (i = 1; i < linker->sec_cnt; i++) अणु
		काष्ठा dst_sec *sec = &linker->secs[i];

		अगर (sec->func_info.rec_cnt) अणु
			अगर (func_rec_sz == 0)
				func_rec_sz = sec->func_info.rec_sz;
			अगर (func_rec_sz != sec->func_info.rec_sz) अणु
				pr_warn("mismatch in func_info record size %zu != %u\n",
					func_rec_sz, sec->func_info.rec_sz);
				वापस -EINVAL;
			पूर्ण

			funcs_sz += माप(काष्ठा btf_ext_info_sec) + func_rec_sz * sec->func_info.rec_cnt;
		पूर्ण
		अगर (sec->line_info.rec_cnt) अणु
			अगर (line_rec_sz == 0)
				line_rec_sz = sec->line_info.rec_sz;
			अगर (line_rec_sz != sec->line_info.rec_sz) अणु
				pr_warn("mismatch in line_info record size %zu != %u\n",
					line_rec_sz, sec->line_info.rec_sz);
				वापस -EINVAL;
			पूर्ण

			lines_sz += माप(काष्ठा btf_ext_info_sec) + line_rec_sz * sec->line_info.rec_cnt;
		पूर्ण
		अगर (sec->core_relo_info.rec_cnt) अणु
			अगर (core_relo_rec_sz == 0)
				core_relo_rec_sz = sec->core_relo_info.rec_sz;
			अगर (core_relo_rec_sz != sec->core_relo_info.rec_sz) अणु
				pr_warn("mismatch in core_relo_info record size %zu != %u\n",
					core_relo_rec_sz, sec->core_relo_info.rec_sz);
				वापस -EINVAL;
			पूर्ण

			core_relos_sz += माप(काष्ठा btf_ext_info_sec) + core_relo_rec_sz * sec->core_relo_info.rec_cnt;
		पूर्ण
	पूर्ण

	अगर (!funcs_sz && !lines_sz && !core_relos_sz)
		वापस 0;

	total_sz += माप(काष्ठा btf_ext_header);
	अगर (funcs_sz) अणु
		funcs_sz += माप(__u32); /* record size prefix */
		total_sz += funcs_sz;
	पूर्ण
	अगर (lines_sz) अणु
		lines_sz += माप(__u32); /* record size prefix */
		total_sz += lines_sz;
	पूर्ण
	अगर (core_relos_sz) अणु
		core_relos_sz += माप(__u32); /* record size prefix */
		total_sz += core_relos_sz;
	पूर्ण

	cur = data = सुस्मृति(1, total_sz);
	अगर (!data)
		वापस -ENOMEM;

	hdr = cur;
	hdr->magic = BTF_MAGIC;
	hdr->version = BTF_VERSION;
	hdr->flags = 0;
	hdr->hdr_len = माप(काष्ठा btf_ext_header);
	cur += माप(काष्ठा btf_ext_header);

	/* All offsets are in bytes relative to the end of this header */
	hdr->func_info_off = 0;
	hdr->func_info_len = funcs_sz;
	hdr->line_info_off = funcs_sz;
	hdr->line_info_len = lines_sz;
	hdr->core_relo_off = funcs_sz + lines_sz;
	hdr->core_relo_len = core_relos_sz;

	अगर (funcs_sz) अणु
		*(__u32 *)cur = func_rec_sz;
		cur += माप(__u32);

		क्रम (i = 1; i < linker->sec_cnt; i++) अणु
			काष्ठा dst_sec *sec = &linker->secs[i];

			sz = emit_btf_ext_data(linker, cur, sec->sec_name, &sec->func_info);
			अगर (sz < 0) अणु
				err = sz;
				जाओ out;
			पूर्ण

			cur += sz;
		पूर्ण
	पूर्ण

	अगर (lines_sz) अणु
		*(__u32 *)cur = line_rec_sz;
		cur += माप(__u32);

		क्रम (i = 1; i < linker->sec_cnt; i++) अणु
			काष्ठा dst_sec *sec = &linker->secs[i];

			sz = emit_btf_ext_data(linker, cur, sec->sec_name, &sec->line_info);
			अगर (sz < 0) अणु
				err = sz;
				जाओ out;
			पूर्ण

			cur += sz;
		पूर्ण
	पूर्ण

	अगर (core_relos_sz) अणु
		*(__u32 *)cur = core_relo_rec_sz;
		cur += माप(__u32);

		क्रम (i = 1; i < linker->sec_cnt; i++) अणु
			काष्ठा dst_sec *sec = &linker->secs[i];

			sz = emit_btf_ext_data(linker, cur, sec->sec_name, &sec->core_relo_info);
			अगर (sz < 0) अणु
				err = sz;
				जाओ out;
			पूर्ण

			cur += sz;
		पूर्ण
	पूर्ण

	linker->btf_ext = btf_ext__new(data, total_sz);
	err = libbpf_get_error(linker->btf_ext);
	अगर (err) अणु
		linker->btf_ext = शून्य;
		pr_warn("failed to parse final .BTF.ext data: %d\n", err);
		जाओ out;
	पूर्ण

out:
	मुक्त(data);
	वापस err;
पूर्ण
