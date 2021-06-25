<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <fcntl.h>
#समावेश <मानकपन.स>
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <पूर्णांकtypes.h>

#समावेश "dso.h"
#समावेश "map.h"
#समावेश "maps.h"
#समावेश "symbol.h"
#समावेश "symsrc.h"
#समावेश "demangle-ocaml.h"
#समावेश "demangle-java.h"
#समावेश "demangle-rust.h"
#समावेश "machine.h"
#समावेश "vdso.h"
#समावेश "debug.h"
#समावेश "util/copyfile.h"
#समावेश <linux/प्रकार.स>
#समावेश <linux/kernel.h>
#समावेश <linux/zभाग.स>
#समावेश <symbol/kallsyms.h>
#समावेश <पूर्णांकernal/lib.h>

#अगर_अघोषित EM_AARCH64
#घोषणा EM_AARCH64	183  /* ARM 64 bit */
#पूर्ण_अगर

#अगर_अघोषित ELF32_ST_VISIBILITY
#घोषणा ELF32_ST_VISIBILITY(o)	((o) & 0x03)
#पूर्ण_अगर

/* For ELF64 the definitions are the same.  */
#अगर_अघोषित ELF64_ST_VISIBILITY
#घोषणा ELF64_ST_VISIBILITY(o)	ELF32_ST_VISIBILITY (o)
#पूर्ण_अगर

/* How to extract inक्रमmation held in the st_other field.  */
#अगर_अघोषित GELF_ST_VISIBILITY
#घोषणा GELF_ST_VISIBILITY(val)	ELF64_ST_VISIBILITY (val)
#पूर्ण_अगर

प्रकार Elf64_Nhdr GElf_Nhdr;

#अगर_अघोषित DMGL_PARAMS
#घोषणा DMGL_NO_OPTS     0              /* For पढ़ोability... */
#घोषणा DMGL_PARAMS      (1 << 0)       /* Include function args */
#घोषणा DMGL_ANSI        (1 << 1)       /* Include स्थिर, अस्थिर, etc */
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBBFD_SUPPORT
#घोषणा PACKAGE 'perf'
#समावेश <bfd.h>
#अन्यथा
#अगर_घोषित HAVE_CPLUS_DEMANGLE_SUPPORT
बाह्य अक्षर *cplus_demangle(स्थिर अक्षर *, पूर्णांक);

अटल अंतरभूत अक्षर *bfd_demangle(व्योम __maybe_unused *v, स्थिर अक्षर *c, पूर्णांक i)
अणु
	वापस cplus_demangle(c, i);
पूर्ण
#अन्यथा
#अगर_घोषित NO_DEMANGLE
अटल अंतरभूत अक्षर *bfd_demangle(व्योम __maybe_unused *v,
				 स्थिर अक्षर __maybe_unused *c,
				 पूर्णांक __maybe_unused i)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_अघोषित HAVE_ELF_GETPHDRNUM_SUPPORT
अटल पूर्णांक elf_getphdrnum(Elf *elf, माप_प्रकार *dst)
अणु
	GElf_Ehdr gehdr;
	GElf_Ehdr *ehdr;

	ehdr = gelf_getehdr(elf, &gehdr);
	अगर (!ehdr)
		वापस -1;

	*dst = ehdr->e_phnum;

	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित HAVE_ELF_GETSHDRSTRNDX_SUPPORT
अटल पूर्णांक elf_माला_लोhdrstrndx(Elf *elf __maybe_unused, माप_प्रकार *dst __maybe_unused)
अणु
	pr_err("%s: update your libelf to > 0.140, this one lacks elf_getshdrstrndx().\n", __func__);
	वापस -1;
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित NT_GNU_BUILD_ID
#घोषणा NT_GNU_BUILD_ID 3
#पूर्ण_अगर

/**
 * elf_symtab__क्रम_each_symbol - iterate thru all the symbols
 *
 * @syms: काष्ठा elf_symtab instance to iterate
 * @idx: uपूर्णांक32_t idx
 * @sym: GElf_Sym iterator
 */
#घोषणा elf_symtab__क्रम_each_symbol(syms, nr_syms, idx, sym) \
	क्रम (idx = 0, gelf_माला_लोym(syms, idx, &sym);\
	     idx < nr_syms; \
	     idx++, gelf_माला_लोym(syms, idx, &sym))

अटल अंतरभूत uपूर्णांक8_t elf_sym__type(स्थिर GElf_Sym *sym)
अणु
	वापस GELF_ST_TYPE(sym->st_info);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t elf_sym__visibility(स्थिर GElf_Sym *sym)
अणु
	वापस GELF_ST_VISIBILITY(sym->st_other);
पूर्ण

#अगर_अघोषित STT_GNU_IFUNC
#घोषणा STT_GNU_IFUNC 10
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक elf_sym__is_function(स्थिर GElf_Sym *sym)
अणु
	वापस (elf_sym__type(sym) == STT_FUNC ||
		elf_sym__type(sym) == STT_GNU_IFUNC) &&
	       sym->st_name != 0 &&
	       sym->st_shndx != SHN_UNDEF;
पूर्ण

अटल अंतरभूत bool elf_sym__is_object(स्थिर GElf_Sym *sym)
अणु
	वापस elf_sym__type(sym) == STT_OBJECT &&
		sym->st_name != 0 &&
		sym->st_shndx != SHN_UNDEF;
पूर्ण

अटल अंतरभूत पूर्णांक elf_sym__is_label(स्थिर GElf_Sym *sym)
अणु
	वापस elf_sym__type(sym) == STT_NOTYPE &&
		sym->st_name != 0 &&
		sym->st_shndx != SHN_UNDEF &&
		sym->st_shndx != SHN_ABS &&
		elf_sym__visibility(sym) != STV_HIDDEN &&
		elf_sym__visibility(sym) != STV_INTERNAL;
पूर्ण

अटल bool elf_sym__filter(GElf_Sym *sym)
अणु
	वापस elf_sym__is_function(sym) || elf_sym__is_object(sym);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *elf_sym__name(स्थिर GElf_Sym *sym,
					स्थिर Elf_Data *symstrs)
अणु
	वापस symstrs->d_buf + sym->st_name;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *elf_sec__name(स्थिर GElf_Shdr *shdr,
					स्थिर Elf_Data *secstrs)
अणु
	वापस secstrs->d_buf + shdr->sh_name;
पूर्ण

अटल अंतरभूत पूर्णांक elf_sec__is_text(स्थिर GElf_Shdr *shdr,
					स्थिर Elf_Data *secstrs)
अणु
	वापस म_माला(elf_sec__name(shdr, secstrs), "text") != शून्य;
पूर्ण

अटल अंतरभूत bool elf_sec__is_data(स्थिर GElf_Shdr *shdr,
				    स्थिर Elf_Data *secstrs)
अणु
	वापस म_माला(elf_sec__name(shdr, secstrs), "data") != शून्य;
पूर्ण

अटल bool elf_sec__filter(GElf_Shdr *shdr, Elf_Data *secstrs)
अणु
	वापस elf_sec__is_text(shdr, secstrs) || 
	       elf_sec__is_data(shdr, secstrs);
पूर्ण

अटल माप_प्रकार elf_addr_to_index(Elf *elf, GElf_Addr addr)
अणु
	Elf_Scn *sec = शून्य;
	GElf_Shdr shdr;
	माप_प्रकार cnt = 1;

	जबतक ((sec = elf_nextscn(elf, sec)) != शून्य) अणु
		gelf_माला_लोhdr(sec, &shdr);

		अगर ((addr >= shdr.sh_addr) &&
		    (addr < (shdr.sh_addr + shdr.sh_size)))
			वापस cnt;

		++cnt;
	पूर्ण

	वापस -1;
पूर्ण

Elf_Scn *elf_section_by_name(Elf *elf, GElf_Ehdr *ep,
			     GElf_Shdr *shp, स्थिर अक्षर *name, माप_प्रकार *idx)
अणु
	Elf_Scn *sec = शून्य;
	माप_प्रकार cnt = 1;

	/* Elf is corrupted/truncated, aव्योम calling elf_strptr. */
	अगर (!elf_rawdata(elf_माला_लोcn(elf, ep->e_shstrndx), शून्य))
		वापस शून्य;

	जबतक ((sec = elf_nextscn(elf, sec)) != शून्य) अणु
		अक्षर *str;

		gelf_माला_लोhdr(sec, shp);
		str = elf_strptr(elf, ep->e_shstrndx, shp->sh_name);
		अगर (str && !म_भेद(name, str)) अणु
			अगर (idx)
				*idx = cnt;
			वापस sec;
		पूर्ण
		++cnt;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool want_demangle(bool is_kernel_sym)
अणु
	वापस is_kernel_sym ? symbol_conf.demangle_kernel : symbol_conf.demangle;
पूर्ण

अटल अक्षर *demangle_sym(काष्ठा dso *dso, पूर्णांक kmodule, स्थिर अक्षर *elf_name)
अणु
	पूर्णांक demangle_flags = verbose > 0 ? (DMGL_PARAMS | DMGL_ANSI) : DMGL_NO_OPTS;
	अक्षर *demangled = शून्य;

	/*
	 * We need to figure out अगर the object was created from C++ sources
	 * DWARF DW_compile_unit has this, but we करोn't always have access
	 * to it...
	 */
	अगर (!want_demangle(dso->kernel || kmodule))
	    वापस demangled;

	demangled = bfd_demangle(शून्य, elf_name, demangle_flags);
	अगर (demangled == शून्य) अणु
		demangled = ocaml_demangle_sym(elf_name);
		अगर (demangled == शून्य) अणु
			demangled = java_demangle_sym(elf_name, JAVA_DEMANGLE_NORET);
		पूर्ण
	पूर्ण
	अन्यथा अगर (rust_is_mangled(demangled))
		/*
		    * Input to Rust demangling is the BFD-demangled
		    * name which it Rust-demangles in place.
		    */
		rust_demangle_sym(demangled);

	वापस demangled;
पूर्ण

#घोषणा elf_section__क्रम_each_rel(reldata, pos, pos_mem, idx, nr_entries) \
	क्रम (idx = 0, pos = gelf_getrel(reldata, 0, &pos_mem); \
	     idx < nr_entries; \
	     ++idx, pos = gelf_getrel(reldata, idx, &pos_mem))

#घोषणा elf_section__क्रम_each_rela(reldata, pos, pos_mem, idx, nr_entries) \
	क्रम (idx = 0, pos = gelf_getrela(reldata, 0, &pos_mem); \
	     idx < nr_entries; \
	     ++idx, pos = gelf_getrela(reldata, idx, &pos_mem))

/*
 * We need to check अगर we have a .dynsym, so that we can handle the
 * .plt, synthesizing its symbols, that aren't on the symtअसल (be it
 * .dynsym or .symtab).
 * And always look at the original dso, not at debuginfo packages, that
 * have the PLT data stripped out (shdr_rel_plt.sh_type == SHT_NOBITS).
 */
पूर्णांक dso__synthesize_plt_symbols(काष्ठा dso *dso, काष्ठा symsrc *ss)
अणु
	uपूर्णांक32_t nr_rel_entries, idx;
	GElf_Sym sym;
	u64 plt_offset, plt_header_size, plt_entry_size;
	GElf_Shdr shdr_plt;
	काष्ठा symbol *f;
	GElf_Shdr shdr_rel_plt, shdr_dynsym;
	Elf_Data *reldata, *syms, *symstrs;
	Elf_Scn *scn_plt_rel, *scn_symstrs, *scn_dynsym;
	माप_प्रकार dynsym_idx;
	GElf_Ehdr ehdr;
	अक्षर sympltname[1024];
	Elf *elf;
	पूर्णांक nr = 0, symidx, err = 0;

	अगर (!ss->dynsym)
		वापस 0;

	elf = ss->elf;
	ehdr = ss->ehdr;

	scn_dynsym = ss->dynsym;
	shdr_dynsym = ss->dynshdr;
	dynsym_idx = ss->dynsym_idx;

	अगर (scn_dynsym == शून्य)
		जाओ out_elf_end;

	scn_plt_rel = elf_section_by_name(elf, &ehdr, &shdr_rel_plt,
					  ".rela.plt", शून्य);
	अगर (scn_plt_rel == शून्य) अणु
		scn_plt_rel = elf_section_by_name(elf, &ehdr, &shdr_rel_plt,
						  ".rel.plt", शून्य);
		अगर (scn_plt_rel == शून्य)
			जाओ out_elf_end;
	पूर्ण

	err = -1;

	अगर (shdr_rel_plt.sh_link != dynsym_idx)
		जाओ out_elf_end;

	अगर (elf_section_by_name(elf, &ehdr, &shdr_plt, ".plt", शून्य) == शून्य)
		जाओ out_elf_end;

	/*
	 * Fetch the relocation section to find the idxes to the GOT
	 * and the symbols in the .dynsym they refer to.
	 */
	reldata = elf_getdata(scn_plt_rel, शून्य);
	अगर (reldata == शून्य)
		जाओ out_elf_end;

	syms = elf_getdata(scn_dynsym, शून्य);
	अगर (syms == शून्य)
		जाओ out_elf_end;

	scn_symstrs = elf_माला_लोcn(elf, shdr_dynsym.sh_link);
	अगर (scn_symstrs == शून्य)
		जाओ out_elf_end;

	symstrs = elf_getdata(scn_symstrs, शून्य);
	अगर (symstrs == शून्य)
		जाओ out_elf_end;

	अगर (symstrs->d_size == 0)
		जाओ out_elf_end;

	nr_rel_entries = shdr_rel_plt.sh_size / shdr_rel_plt.sh_entsize;
	plt_offset = shdr_plt.sh_offset;
	चयन (ehdr.e_machine) अणु
		हाल EM_ARM:
			plt_header_size = 20;
			plt_entry_size = 12;
			अवरोध;

		हाल EM_AARCH64:
			plt_header_size = 32;
			plt_entry_size = 16;
			अवरोध;

		हाल EM_SPARC:
			plt_header_size = 48;
			plt_entry_size = 12;
			अवरोध;

		हाल EM_SPARCV9:
			plt_header_size = 128;
			plt_entry_size = 32;
			अवरोध;

		शेष: /* FIXME: s390/alpha/mips/parisc/poperpc/sh/xtensa need to be checked */
			plt_header_size = shdr_plt.sh_entsize;
			plt_entry_size = shdr_plt.sh_entsize;
			अवरोध;
	पूर्ण
	plt_offset += plt_header_size;

	अगर (shdr_rel_plt.sh_type == SHT_RELA) अणु
		GElf_Rela pos_mem, *pos;

		elf_section__क्रम_each_rela(reldata, pos, pos_mem, idx,
					   nr_rel_entries) अणु
			स्थिर अक्षर *elf_name = शून्य;
			अक्षर *demangled = शून्य;
			symidx = GELF_R_SYM(pos->r_info);
			gelf_माला_लोym(syms, symidx, &sym);

			elf_name = elf_sym__name(&sym, symstrs);
			demangled = demangle_sym(dso, 0, elf_name);
			अगर (demangled != शून्य)
				elf_name = demangled;
			snम_लिखो(sympltname, माप(sympltname),
				 "%s@plt", elf_name);
			मुक्त(demangled);

			f = symbol__new(plt_offset, plt_entry_size,
					STB_GLOBAL, STT_FUNC, sympltname);
			अगर (!f)
				जाओ out_elf_end;

			plt_offset += plt_entry_size;
			symbols__insert(&dso->symbols, f);
			++nr;
		पूर्ण
	पूर्ण अन्यथा अगर (shdr_rel_plt.sh_type == SHT_REL) अणु
		GElf_Rel pos_mem, *pos;
		elf_section__क्रम_each_rel(reldata, pos, pos_mem, idx,
					  nr_rel_entries) अणु
			स्थिर अक्षर *elf_name = शून्य;
			अक्षर *demangled = शून्य;
			symidx = GELF_R_SYM(pos->r_info);
			gelf_माला_लोym(syms, symidx, &sym);

			elf_name = elf_sym__name(&sym, symstrs);
			demangled = demangle_sym(dso, 0, elf_name);
			अगर (demangled != शून्य)
				elf_name = demangled;
			snम_लिखो(sympltname, माप(sympltname),
				 "%s@plt", elf_name);
			मुक्त(demangled);

			f = symbol__new(plt_offset, plt_entry_size,
					STB_GLOBAL, STT_FUNC, sympltname);
			अगर (!f)
				जाओ out_elf_end;

			plt_offset += plt_entry_size;
			symbols__insert(&dso->symbols, f);
			++nr;
		पूर्ण
	पूर्ण

	err = 0;
out_elf_end:
	अगर (err == 0)
		वापस nr;
	pr_debug("%s: problems reading %s PLT info.\n",
		 __func__, dso->दीर्घ_name);
	वापस 0;
पूर्ण

अक्षर *dso__demangle_sym(काष्ठा dso *dso, पूर्णांक kmodule, स्थिर अक्षर *elf_name)
अणु
	वापस demangle_sym(dso, kmodule, elf_name);
पूर्ण

/*
 * Align offset to 4 bytes as needed क्रम note name and descriptor data.
 */
#घोषणा NOTE_ALIGN(n) (((n) + 3) & -4U)

अटल पूर्णांक elf_पढ़ो_build_id(Elf *elf, व्योम *bf, माप_प्रकार size)
अणु
	पूर्णांक err = -1;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	Elf_Data *data;
	Elf_Scn *sec;
	Elf_Kind ek;
	व्योम *ptr;

	अगर (size < BUILD_ID_SIZE)
		जाओ out;

	ek = elf_kind(elf);
	अगर (ek != ELF_K_ELF)
		जाओ out;

	अगर (gelf_getehdr(elf, &ehdr) == शून्य) अणु
		pr_err("%s: cannot get elf header.\n", __func__);
		जाओ out;
	पूर्ण

	/*
	 * Check following sections क्रम notes:
	 *   '.note.gnu.build-id'
	 *   '.notes'
	 *   '.note' (VDSO specअगरic)
	 */
	करो अणु
		sec = elf_section_by_name(elf, &ehdr, &shdr,
					  ".note.gnu.build-id", शून्य);
		अगर (sec)
			अवरोध;

		sec = elf_section_by_name(elf, &ehdr, &shdr,
					  ".notes", शून्य);
		अगर (sec)
			अवरोध;

		sec = elf_section_by_name(elf, &ehdr, &shdr,
					  ".note", शून्य);
		अगर (sec)
			अवरोध;

		वापस err;

	पूर्ण जबतक (0);

	data = elf_getdata(sec, शून्य);
	अगर (data == शून्य)
		जाओ out;

	ptr = data->d_buf;
	जबतक (ptr < (data->d_buf + data->d_size)) अणु
		GElf_Nhdr *nhdr = ptr;
		माप_प्रकार namesz = NOTE_ALIGN(nhdr->n_namesz),
		       descsz = NOTE_ALIGN(nhdr->n_descsz);
		स्थिर अक्षर *name;

		ptr += माप(*nhdr);
		name = ptr;
		ptr += namesz;
		अगर (nhdr->n_type == NT_GNU_BUILD_ID &&
		    nhdr->n_namesz == माप("GNU")) अणु
			अगर (स_भेद(name, "GNU", माप("GNU")) == 0) अणु
				माप_प्रकार sz = min(size, descsz);
				स_नकल(bf, ptr, sz);
				स_रखो(bf + sz, 0, size - sz);
				err = descsz;
				अवरोध;
			पूर्ण
		पूर्ण
		ptr += descsz;
	पूर्ण

out:
	वापस err;
पूर्ण

#अगर_घोषित HAVE_LIBBFD_BUILDID_SUPPORT

अटल पूर्णांक पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid)
अणु
	माप_प्रकार size = माप(bid->data);
	पूर्णांक err = -1;
	bfd *abfd;

	abfd = bfd_खोलोr(filename, शून्य);
	अगर (!abfd)
		वापस -1;

	अगर (!bfd_check_क्रमmat(abfd, bfd_object)) अणु
		pr_debug2("%s: cannot read %s bfd file.\n", __func__, filename);
		जाओ out_बंद;
	पूर्ण

	अगर (!abfd->build_id || abfd->build_id->size > size)
		जाओ out_बंद;

	स_नकल(bid->data, abfd->build_id->data, abfd->build_id->size);
	स_रखो(bid->data + abfd->build_id->size, 0, size - abfd->build_id->size);
	err = bid->size = abfd->build_id->size;

out_बंद:
	bfd_बंद(abfd);
	वापस err;
पूर्ण

#अन्यथा // HAVE_LIBBFD_BUILDID_SUPPORT

अटल पूर्णांक पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid)
अणु
	माप_प्रकार size = माप(bid->data);
	पूर्णांक fd, err = -1;
	Elf *elf;

	अगर (size < BUILD_ID_SIZE)
		जाओ out;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0)
		जाओ out;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य) अणु
		pr_debug2("%s: cannot read %s ELF file.\n", __func__, filename);
		जाओ out_बंद;
	पूर्ण

	err = elf_पढ़ो_build_id(elf, bid->data, size);
	अगर (err > 0)
		bid->size = err;

	elf_end(elf);
out_बंद:
	बंद(fd);
out:
	वापस err;
पूर्ण

#पूर्ण_अगर // HAVE_LIBBFD_BUILDID_SUPPORT

पूर्णांक filename__पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid)
अणु
	काष्ठा kmod_path m = अणु .name = शून्य, पूर्ण;
	अक्षर path[PATH_MAX];
	पूर्णांक err;

	अगर (!filename)
		वापस -EFAULT;

	err = kmod_path__parse(&m, filename);
	अगर (err)
		वापस -1;

	अगर (m.comp) अणु
		पूर्णांक error = 0, fd;

		fd = filename__decompress(filename, path, माप(path), m.comp, &error);
		अगर (fd < 0) अणु
			pr_debug("Failed to decompress (error %d) %s\n",
				 error, filename);
			वापस -1;
		पूर्ण
		बंद(fd);
		filename = path;
	पूर्ण

	err = पढ़ो_build_id(filename, bid);

	अगर (m.comp)
		unlink(filename);
	वापस err;
पूर्ण

पूर्णांक sysfs__पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid)
अणु
	माप_प्रकार size = माप(bid->data);
	पूर्णांक fd, err = -1;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0)
		जाओ out;

	जबतक (1) अणु
		अक्षर bf[बफ_मान];
		GElf_Nhdr nhdr;
		माप_प्रकार namesz, descsz;

		अगर (पढ़ो(fd, &nhdr, माप(nhdr)) != माप(nhdr))
			अवरोध;

		namesz = NOTE_ALIGN(nhdr.n_namesz);
		descsz = NOTE_ALIGN(nhdr.n_descsz);
		अगर (nhdr.n_type == NT_GNU_BUILD_ID &&
		    nhdr.n_namesz == माप("GNU")) अणु
			अगर (पढ़ो(fd, bf, namesz) != (sमाप_प्रकार)namesz)
				अवरोध;
			अगर (स_भेद(bf, "GNU", माप("GNU")) == 0) अणु
				माप_प्रकार sz = min(descsz, size);
				अगर (पढ़ो(fd, bid->data, sz) == (sमाप_प्रकार)sz) अणु
					स_रखो(bid->data + sz, 0, size - sz);
					bid->size = sz;
					err = 0;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (पढ़ो(fd, bf, descsz) != (sमाप_प्रकार)descsz)
				अवरोध;
		पूर्ण अन्यथा अणु
			पूर्णांक n = namesz + descsz;

			अगर (n > (पूर्णांक)माप(bf)) अणु
				n = माप(bf);
				pr_debug("%s: truncating reading of build id in sysfs file %s: n_namesz=%u, n_descsz=%u.\n",
					 __func__, filename, nhdr.n_namesz, nhdr.n_descsz);
			पूर्ण
			अगर (पढ़ो(fd, bf, n) != n)
				अवरोध;
		पूर्ण
	पूर्ण
	बंद(fd);
out:
	वापस err;
पूर्ण

#अगर_घोषित HAVE_LIBBFD_SUPPORT

पूर्णांक filename__पढ़ो_debuglink(स्थिर अक्षर *filename, अक्षर *debuglink,
			     माप_प्रकार size)
अणु
	पूर्णांक err = -1;
	asection *section;
	bfd *abfd;

	abfd = bfd_खोलोr(filename, शून्य);
	अगर (!abfd)
		वापस -1;

	अगर (!bfd_check_क्रमmat(abfd, bfd_object)) अणु
		pr_debug2("%s: cannot read %s bfd file.\n", __func__, filename);
		जाओ out_बंद;
	पूर्ण

	section = bfd_get_section_by_name(abfd, ".gnu_debuglink");
	अगर (!section)
		जाओ out_बंद;

	अगर (section->size > size)
		जाओ out_बंद;

	अगर (!bfd_get_section_contents(abfd, section, debuglink, 0,
				      section->size))
		जाओ out_बंद;

	err = 0;

out_बंद:
	bfd_बंद(abfd);
	वापस err;
पूर्ण

#अन्यथा

पूर्णांक filename__पढ़ो_debuglink(स्थिर अक्षर *filename, अक्षर *debuglink,
			     माप_प्रकार size)
अणु
	पूर्णांक fd, err = -1;
	Elf *elf;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	Elf_Data *data;
	Elf_Scn *sec;
	Elf_Kind ek;

	fd = खोलो(filename, O_RDONLY);
	अगर (fd < 0)
		जाओ out;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य) अणु
		pr_debug2("%s: cannot read %s ELF file.\n", __func__, filename);
		जाओ out_बंद;
	पूर्ण

	ek = elf_kind(elf);
	अगर (ek != ELF_K_ELF)
		जाओ out_elf_end;

	अगर (gelf_getehdr(elf, &ehdr) == शून्य) अणु
		pr_err("%s: cannot get elf header.\n", __func__);
		जाओ out_elf_end;
	पूर्ण

	sec = elf_section_by_name(elf, &ehdr, &shdr,
				  ".gnu_debuglink", शून्य);
	अगर (sec == शून्य)
		जाओ out_elf_end;

	data = elf_getdata(sec, शून्य);
	अगर (data == शून्य)
		जाओ out_elf_end;

	/* the start of this section is a zero-terminated string */
	म_नकलन(debuglink, data->d_buf, size);

	err = 0;

out_elf_end:
	elf_end(elf);
out_बंद:
	बंद(fd);
out:
	वापस err;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक dso__swap_init(काष्ठा dso *dso, अचिन्हित अक्षर eidata)
अणु
	अटल अचिन्हित पूर्णांक स्थिर endian = 1;

	dso->needs_swap = DSO_SWAP__NO;

	चयन (eidata) अणु
	हाल ELFDATA2LSB:
		/* We are big endian, DSO is little endian. */
		अगर (*(अचिन्हित अक्षर स्थिर *)&endian != 1)
			dso->needs_swap = DSO_SWAP__YES;
		अवरोध;

	हाल ELFDATA2MSB:
		/* We are little endian, DSO is big endian. */
		अगर (*(अचिन्हित अक्षर स्थिर *)&endian != 0)
			dso->needs_swap = DSO_SWAP__YES;
		अवरोध;

	शेष:
		pr_err("unrecognized DSO data encoding %d\n", eidata);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

bool symsrc__possibly_runसमय(काष्ठा symsrc *ss)
अणु
	वापस ss->dynsym || ss->opdsec;
पूर्ण

bool symsrc__has_symtab(काष्ठा symsrc *ss)
अणु
	वापस ss->symtab != शून्य;
पूर्ण

व्योम symsrc__destroy(काष्ठा symsrc *ss)
अणु
	zमुक्त(&ss->name);
	elf_end(ss->elf);
	बंद(ss->fd);
पूर्ण

bool elf__needs_adjust_symbols(GElf_Ehdr ehdr)
अणु
	/*
	 * Usually vmlinux is an ELF file with type ET_EXEC क्रम most
	 * architectures; except Arm64 kernel is linked with option
	 * '-share', so need to check type ET_DYN.
	 */
	वापस ehdr.e_type == ET_EXEC || ehdr.e_type == ET_REL ||
	       ehdr.e_type == ET_DYN;
पूर्ण

पूर्णांक symsrc__init(काष्ठा symsrc *ss, काष्ठा dso *dso, स्थिर अक्षर *name,
		 क्रमागत dso_binary_type type)
अणु
	GElf_Ehdr ehdr;
	Elf *elf;
	पूर्णांक fd;

	अगर (dso__needs_decompress(dso)) अणु
		fd = dso__decompress_kmodule_fd(dso, name);
		अगर (fd < 0)
			वापस -1;

		type = dso->symtab_type;
	पूर्ण अन्यथा अणु
		fd = खोलो(name, O_RDONLY);
		अगर (fd < 0) अणु
			dso->load_त्रुटि_सं = त्रुटि_सं;
			वापस -1;
		पूर्ण
	पूर्ण

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य) अणु
		pr_debug("%s: cannot read %s ELF file.\n", __func__, name);
		dso->load_त्रुटि_सं = DSO_LOAD_ERRNO__INVALID_ELF;
		जाओ out_बंद;
	पूर्ण

	अगर (gelf_getehdr(elf, &ehdr) == शून्य) अणु
		dso->load_त्रुटि_सं = DSO_LOAD_ERRNO__INVALID_ELF;
		pr_debug("%s: cannot get elf header.\n", __func__);
		जाओ out_elf_end;
	पूर्ण

	अगर (dso__swap_init(dso, ehdr.e_ident[EI_DATA])) अणु
		dso->load_त्रुटि_सं = DSO_LOAD_ERRNO__INTERNAL_ERROR;
		जाओ out_elf_end;
	पूर्ण

	/* Always reject images with a mismatched build-id: */
	अगर (dso->has_build_id && !symbol_conf.ignore_vmlinux_buildid) अणु
		u8 build_id[BUILD_ID_SIZE];
		काष्ठा build_id bid;
		पूर्णांक size;

		size = elf_पढ़ो_build_id(elf, build_id, BUILD_ID_SIZE);
		अगर (size <= 0) अणु
			dso->load_त्रुटि_सं = DSO_LOAD_ERRNO__CANNOT_READ_BUILDID;
			जाओ out_elf_end;
		पूर्ण

		build_id__init(&bid, build_id, size);
		अगर (!dso__build_id_equal(dso, &bid)) अणु
			pr_debug("%s: build id mismatch for %s.\n", __func__, name);
			dso->load_त्रुटि_सं = DSO_LOAD_ERRNO__MISMATCHING_BUILDID;
			जाओ out_elf_end;
		पूर्ण
	पूर्ण

	ss->is_64_bit = (gelf_अ_लोlass(elf) == ELFCLASS64);

	ss->symtab = elf_section_by_name(elf, &ehdr, &ss->symshdr, ".symtab",
			शून्य);
	अगर (ss->symshdr.sh_type != SHT_SYMTAB)
		ss->symtab = शून्य;

	ss->dynsym_idx = 0;
	ss->dynsym = elf_section_by_name(elf, &ehdr, &ss->dynshdr, ".dynsym",
			&ss->dynsym_idx);
	अगर (ss->dynshdr.sh_type != SHT_DYNSYM)
		ss->dynsym = शून्य;

	ss->opdidx = 0;
	ss->opdsec = elf_section_by_name(elf, &ehdr, &ss->opdshdr, ".opd",
			&ss->opdidx);
	अगर (ss->opdshdr.sh_type != SHT_PROGBITS)
		ss->opdsec = शून्य;

	अगर (dso->kernel == DSO_SPACE__USER)
		ss->adjust_symbols = true;
	अन्यथा
		ss->adjust_symbols = elf__needs_adjust_symbols(ehdr);

	ss->name   = strdup(name);
	अगर (!ss->name) अणु
		dso->load_त्रुटि_सं = त्रुटि_सं;
		जाओ out_elf_end;
	पूर्ण

	ss->elf    = elf;
	ss->fd     = fd;
	ss->ehdr   = ehdr;
	ss->type   = type;

	वापस 0;

out_elf_end:
	elf_end(elf);
out_बंद:
	बंद(fd);
	वापस -1;
पूर्ण

/**
 * ref_reloc_sym_not_found - has kernel relocation symbol been found.
 * @kmap: kernel maps and relocation reference symbol
 *
 * This function वापसs %true अगर we are dealing with the kernel maps and the
 * relocation reference symbol has not yet been found.  Otherwise %false is
 * वापसed.
 */
अटल bool ref_reloc_sym_not_found(काष्ठा kmap *kmap)
अणु
	वापस kmap && kmap->ref_reloc_sym && kmap->ref_reloc_sym->name &&
	       !kmap->ref_reloc_sym->unrelocated_addr;
पूर्ण

/**
 * ref_reloc - kernel relocation offset.
 * @kmap: kernel maps and relocation reference symbol
 *
 * This function वापसs the offset of kernel addresses as determined by using
 * the relocation reference symbol i.e. अगर the kernel has not been relocated
 * then the वापस value is zero.
 */
अटल u64 ref_reloc(काष्ठा kmap *kmap)
अणु
	अगर (kmap && kmap->ref_reloc_sym &&
	    kmap->ref_reloc_sym->unrelocated_addr)
		वापस kmap->ref_reloc_sym->addr -
		       kmap->ref_reloc_sym->unrelocated_addr;
	वापस 0;
पूर्ण

व्योम __weak arch__sym_update(काष्ठा symbol *s __maybe_unused,
		GElf_Sym *sym __maybe_unused) अणु पूर्ण

अटल पूर्णांक dso__process_kernel_symbol(काष्ठा dso *dso, काष्ठा map *map,
				      GElf_Sym *sym, GElf_Shdr *shdr,
				      काष्ठा maps *kmaps, काष्ठा kmap *kmap,
				      काष्ठा dso **curr_dsop, काष्ठा map **curr_mapp,
				      स्थिर अक्षर *section_name,
				      bool adjust_kernel_syms, bool kmodule, bool *remap_kernel)
अणु
	काष्ठा dso *curr_dso = *curr_dsop;
	काष्ठा map *curr_map;
	अक्षर dso_name[PATH_MAX];

	/* Adjust symbol to map to file offset */
	अगर (adjust_kernel_syms)
		sym->st_value -= shdr->sh_addr - shdr->sh_offset;

	अगर (म_भेद(section_name, (curr_dso->लघु_name + dso->लघु_name_len)) == 0)
		वापस 0;

	अगर (म_भेद(section_name, ".text") == 0) अणु
		/*
		 * The initial kernel mapping is based on
		 * kallsyms and identity maps.  Overग_लिखो it to
		 * map to the kernel dso.
		 */
		अगर (*remap_kernel && dso->kernel && !kmodule) अणु
			*remap_kernel = false;
			map->start = shdr->sh_addr + ref_reloc(kmap);
			map->end = map->start + shdr->sh_size;
			map->pgoff = shdr->sh_offset;
			map->map_ip = map__map_ip;
			map->unmap_ip = map__unmap_ip;
			/* Ensure maps are correctly ordered */
			अगर (kmaps) अणु
				map__get(map);
				maps__हटाओ(kmaps, map);
				maps__insert(kmaps, map);
				map__put(map);
			पूर्ण
		पूर्ण

		/*
		 * The initial module mapping is based on
		 * /proc/modules mapped to offset zero.
		 * Overग_लिखो it to map to the module dso.
		 */
		अगर (*remap_kernel && kmodule) अणु
			*remap_kernel = false;
			map->pgoff = shdr->sh_offset;
		पूर्ण

		*curr_mapp = map;
		*curr_dsop = dso;
		वापस 0;
	पूर्ण

	अगर (!kmap)
		वापस 0;

	snम_लिखो(dso_name, माप(dso_name), "%s%s", dso->लघु_name, section_name);

	curr_map = maps__find_by_name(kmaps, dso_name);
	अगर (curr_map == शून्य) अणु
		u64 start = sym->st_value;

		अगर (kmodule)
			start += map->start + shdr->sh_offset;

		curr_dso = dso__new(dso_name);
		अगर (curr_dso == शून्य)
			वापस -1;
		curr_dso->kernel = dso->kernel;
		curr_dso->दीर्घ_name = dso->दीर्घ_name;
		curr_dso->दीर्घ_name_len = dso->दीर्घ_name_len;
		curr_map = map__new2(start, curr_dso);
		dso__put(curr_dso);
		अगर (curr_map == शून्य)
			वापस -1;

		अगर (curr_dso->kernel)
			map__kmap(curr_map)->kmaps = kmaps;

		अगर (adjust_kernel_syms) अणु
			curr_map->start  = shdr->sh_addr + ref_reloc(kmap);
			curr_map->end	 = curr_map->start + shdr->sh_size;
			curr_map->pgoff	 = shdr->sh_offset;
		पूर्ण अन्यथा अणु
			curr_map->map_ip = curr_map->unmap_ip = identity__map_ip;
		पूर्ण
		curr_dso->symtab_type = dso->symtab_type;
		maps__insert(kmaps, curr_map);
		/*
		 * Add it beक्रमe we drop the reference to curr_map, i.e. जबतक
		 * we still are sure to have a reference to this DSO via
		 * *curr_map->dso.
		 */
		dsos__add(&kmaps->machine->dsos, curr_dso);
		/* kmaps alपढ़ोy got it */
		map__put(curr_map);
		dso__set_loaded(curr_dso);
		*curr_mapp = curr_map;
		*curr_dsop = curr_dso;
	पूर्ण अन्यथा
		*curr_dsop = curr_map->dso;

	वापस 0;
पूर्ण

पूर्णांक dso__load_sym(काष्ठा dso *dso, काष्ठा map *map, काष्ठा symsrc *syms_ss,
		  काष्ठा symsrc *runसमय_ss, पूर्णांक kmodule)
अणु
	काष्ठा kmap *kmap = dso->kernel ? map__kmap(map) : शून्य;
	काष्ठा maps *kmaps = kmap ? map__kmaps(map) : शून्य;
	काष्ठा map *curr_map = map;
	काष्ठा dso *curr_dso = dso;
	Elf_Data *symstrs, *secstrs;
	uपूर्णांक32_t nr_syms;
	पूर्णांक err = -1;
	uपूर्णांक32_t idx;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	GElf_Shdr tshdr;
	Elf_Data *syms, *opddata = शून्य;
	GElf_Sym sym;
	Elf_Scn *sec, *sec_strndx;
	Elf *elf;
	पूर्णांक nr = 0;
	bool remap_kernel = false, adjust_kernel_syms = false;

	अगर (kmap && !kmaps)
		वापस -1;

	dso->symtab_type = syms_ss->type;
	dso->is_64_bit = syms_ss->is_64_bit;
	dso->rel = syms_ss->ehdr.e_type == ET_REL;

	/*
	 * Modules may alपढ़ोy have symbols from kallsyms, but those symbols
	 * have the wrong values क्रम the dso maps, so हटाओ them.
	 */
	अगर (kmodule && syms_ss->symtab)
		symbols__delete(&dso->symbols);

	अगर (!syms_ss->symtab) अणु
		/*
		 * If the vmlinux is stripped, fail so we will fall back
		 * to using kallsyms. The vmlinux runसमय symbols aren't
		 * of much use.
		 */
		अगर (dso->kernel)
			जाओ out_elf_end;

		syms_ss->symtab  = syms_ss->dynsym;
		syms_ss->symshdr = syms_ss->dynshdr;
	पूर्ण

	elf = syms_ss->elf;
	ehdr = syms_ss->ehdr;
	sec = syms_ss->symtab;
	shdr = syms_ss->symshdr;

	अगर (elf_section_by_name(runसमय_ss->elf, &runसमय_ss->ehdr, &tshdr,
				".text", शून्य))
		dso->text_offset = tshdr.sh_addr - tshdr.sh_offset;

	अगर (runसमय_ss->opdsec)
		opddata = elf_rawdata(runसमय_ss->opdsec, शून्य);

	syms = elf_getdata(sec, शून्य);
	अगर (syms == शून्य)
		जाओ out_elf_end;

	sec = elf_माला_लोcn(elf, shdr.sh_link);
	अगर (sec == शून्य)
		जाओ out_elf_end;

	symstrs = elf_getdata(sec, शून्य);
	अगर (symstrs == शून्य)
		जाओ out_elf_end;

	sec_strndx = elf_माला_लोcn(runसमय_ss->elf, runसमय_ss->ehdr.e_shstrndx);
	अगर (sec_strndx == शून्य)
		जाओ out_elf_end;

	secstrs = elf_getdata(sec_strndx, शून्य);
	अगर (secstrs == शून्य)
		जाओ out_elf_end;

	nr_syms = shdr.sh_size / shdr.sh_entsize;

	स_रखो(&sym, 0, माप(sym));

	/*
	 * The kernel relocation symbol is needed in advance in order to adjust
	 * kernel maps correctly.
	 */
	अगर (ref_reloc_sym_not_found(kmap)) अणु
		elf_symtab__क्रम_each_symbol(syms, nr_syms, idx, sym) अणु
			स्थिर अक्षर *elf_name = elf_sym__name(&sym, symstrs);

			अगर (म_भेद(elf_name, kmap->ref_reloc_sym->name))
				जारी;
			kmap->ref_reloc_sym->unrelocated_addr = sym.st_value;
			map->reloc = kmap->ref_reloc_sym->addr -
				     kmap->ref_reloc_sym->unrelocated_addr;
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Handle any relocation of vdso necessary because older kernels
	 * attempted to prelink vdso to its भव address.
	 */
	अगर (dso__is_vdso(dso))
		map->reloc = map->start - dso->text_offset;

	dso->adjust_symbols = runसमय_ss->adjust_symbols || ref_reloc(kmap);
	/*
	 * Initial kernel and module mappings करो not map to the dso.
	 * Flag the fixups.
	 */
	अगर (dso->kernel) अणु
		remap_kernel = true;
		adjust_kernel_syms = dso->adjust_symbols;
	पूर्ण
	elf_symtab__क्रम_each_symbol(syms, nr_syms, idx, sym) अणु
		काष्ठा symbol *f;
		स्थिर अक्षर *elf_name = elf_sym__name(&sym, symstrs);
		अक्षर *demangled = शून्य;
		पूर्णांक is_label = elf_sym__is_label(&sym);
		स्थिर अक्षर *section_name;
		bool used_opd = false;

		अगर (!is_label && !elf_sym__filter(&sym))
			जारी;

		/* Reject ARM ELF "mapping symbols": these aren't unique and
		 * करोn't identअगरy functions, so will confuse the profile
		 * output: */
		अगर (ehdr.e_machine == EM_ARM || ehdr.e_machine == EM_AARCH64) अणु
			अगर (elf_name[0] == '$' && म_अक्षर("adtx", elf_name[1])
			    && (elf_name[2] == '\0' || elf_name[2] == '.'))
				जारी;
		पूर्ण

		अगर (runसमय_ss->opdsec && sym.st_shndx == runसमय_ss->opdidx) अणु
			u32 offset = sym.st_value - syms_ss->opdshdr.sh_addr;
			u64 *opd = opddata->d_buf + offset;
			sym.st_value = DSO__SWAP(dso, u64, *opd);
			sym.st_shndx = elf_addr_to_index(runसमय_ss->elf,
					sym.st_value);
			used_opd = true;
		पूर्ण
		/*
		 * When loading symbols in a data mapping, ABS symbols (which
		 * has a value of SHN_ABS in its st_shndx) failed at
		 * elf_माला_लोcn().  And it marks the loading as a failure so
		 * alपढ़ोy loaded symbols cannot be fixed up.
		 *
		 * I'm not sure what should be करोne. Just ignore them क्रम now.
		 * - Namhyung Kim
		 */
		अगर (sym.st_shndx == SHN_ABS)
			जारी;

		sec = elf_माला_लोcn(syms_ss->elf, sym.st_shndx);
		अगर (!sec)
			जाओ out_elf_end;

		gelf_माला_लोhdr(sec, &shdr);

		/*
		 * We have to fallback to runसमय when syms' section header has
		 * NOBITS set. NOBITS results in file offset (sh_offset) not
		 * being incremented. So sh_offset used below has dअगरferent
		 * values क्रम syms (invalid) and runसमय (valid).
		 */
		अगर (shdr.sh_type == SHT_NOBITS) अणु
			sec = elf_माला_लोcn(runसमय_ss->elf, sym.st_shndx);
			अगर (!sec)
				जाओ out_elf_end;

			gelf_माला_लोhdr(sec, &shdr);
		पूर्ण

		अगर (is_label && !elf_sec__filter(&shdr, secstrs))
			जारी;

		section_name = elf_sec__name(&shdr, secstrs);

		/* On ARM, symbols क्रम thumb functions have 1 added to
		 * the symbol address as a flag - हटाओ it */
		अगर ((ehdr.e_machine == EM_ARM) &&
		    (GELF_ST_TYPE(sym.st_info) == STT_FUNC) &&
		    (sym.st_value & 1))
			--sym.st_value;

		अगर (dso->kernel) अणु
			अगर (dso__process_kernel_symbol(dso, map, &sym, &shdr, kmaps, kmap, &curr_dso, &curr_map,
						       section_name, adjust_kernel_syms, kmodule, &remap_kernel))
				जाओ out_elf_end;
		पूर्ण अन्यथा अगर ((used_opd && runसमय_ss->adjust_symbols) ||
			   (!used_opd && syms_ss->adjust_symbols)) अणु
			pr_debug4("%s: adjusting symbol: st_value: %#" PRIx64 " "
				  "sh_addr: %#" PRIx64 " sh_offset: %#" PRIx64 "\n", __func__,
				  (u64)sym.st_value, (u64)shdr.sh_addr,
				  (u64)shdr.sh_offset);
			sym.st_value -= shdr.sh_addr - shdr.sh_offset;
		पूर्ण

		demangled = demangle_sym(dso, kmodule, elf_name);
		अगर (demangled != शून्य)
			elf_name = demangled;

		f = symbol__new(sym.st_value, sym.st_size,
				GELF_ST_BIND(sym.st_info),
				GELF_ST_TYPE(sym.st_info), elf_name);
		मुक्त(demangled);
		अगर (!f)
			जाओ out_elf_end;

		arch__sym_update(f, &sym);

		__symbols__insert(&curr_dso->symbols, f, dso->kernel);
		nr++;
	पूर्ण

	/*
	 * For misannotated, zeroed, ASM function sizes.
	 */
	अगर (nr > 0) अणु
		symbols__fixup_end(&dso->symbols);
		symbols__fixup_duplicate(&dso->symbols);
		अगर (kmap) अणु
			/*
			 * We need to fixup this here too because we create new
			 * maps here, क्रम things like vsyscall sections.
			 */
			maps__fixup_end(kmaps);
		पूर्ण
	पूर्ण
	err = nr;
out_elf_end:
	वापस err;
पूर्ण

अटल पूर्णांक elf_पढ़ो_maps(Elf *elf, bool exe, mapfn_t mapfn, व्योम *data)
अणु
	GElf_Phdr phdr;
	माप_प्रकार i, phdrnum;
	पूर्णांक err;
	u64 sz;

	अगर (elf_getphdrnum(elf, &phdrnum))
		वापस -1;

	क्रम (i = 0; i < phdrnum; i++) अणु
		अगर (gelf_getphdr(elf, i, &phdr) == शून्य)
			वापस -1;
		अगर (phdr.p_type != PT_LOAD)
			जारी;
		अगर (exe) अणु
			अगर (!(phdr.p_flags & PF_X))
				जारी;
		पूर्ण अन्यथा अणु
			अगर (!(phdr.p_flags & PF_R))
				जारी;
		पूर्ण
		sz = min(phdr.p_memsz, phdr.p_filesz);
		अगर (!sz)
			जारी;
		err = mapfn(phdr.p_vaddr, sz, phdr.p_offset, data);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक file__पढ़ो_maps(पूर्णांक fd, bool exe, mapfn_t mapfn, व्योम *data,
		    bool *is_64_bit)
अणु
	पूर्णांक err;
	Elf *elf;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य)
		वापस -1;

	अगर (is_64_bit)
		*is_64_bit = (gelf_अ_लोlass(elf) == ELFCLASS64);

	err = elf_पढ़ो_maps(elf, exe, mapfn, data);

	elf_end(elf);
	वापस err;
पूर्ण

क्रमागत dso_type dso__type_fd(पूर्णांक fd)
अणु
	क्रमागत dso_type dso_type = DSO__TYPE_UNKNOWN;
	GElf_Ehdr ehdr;
	Elf_Kind ek;
	Elf *elf;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य)
		जाओ out;

	ek = elf_kind(elf);
	अगर (ek != ELF_K_ELF)
		जाओ out_end;

	अगर (gelf_अ_लोlass(elf) == ELFCLASS64) अणु
		dso_type = DSO__TYPE_64BIT;
		जाओ out_end;
	पूर्ण

	अगर (gelf_getehdr(elf, &ehdr) == शून्य)
		जाओ out_end;

	अगर (ehdr.e_machine == EM_X86_64)
		dso_type = DSO__TYPE_X32BIT;
	अन्यथा
		dso_type = DSO__TYPE_32BIT;
out_end:
	elf_end(elf);
out:
	वापस dso_type;
पूर्ण

अटल पूर्णांक copy_bytes(पूर्णांक from, off_t from_offs, पूर्णांक to, off_t to_offs, u64 len)
अणु
	sमाप_प्रकार r;
	माप_प्रकार n;
	पूर्णांक err = -1;
	अक्षर *buf = दो_स्मृति(page_size);

	अगर (buf == शून्य)
		वापस -1;

	अगर (lseek(to, to_offs, शुरू_से) != to_offs)
		जाओ out;

	अगर (lseek(from, from_offs, शुरू_से) != from_offs)
		जाओ out;

	जबतक (len) अणु
		n = page_size;
		अगर (len < n)
			n = len;
		/* Use पढ़ो because mmap won't work on proc files */
		r = पढ़ो(from, buf, n);
		अगर (r < 0)
			जाओ out;
		अगर (!r)
			अवरोध;
		n = r;
		r = ग_लिखो(to, buf, n);
		अगर (r < 0)
			जाओ out;
		अगर ((माप_प्रकार)r != n)
			जाओ out;
		len -= n;
	पूर्ण

	err = 0;
out:
	मुक्त(buf);
	वापस err;
पूर्ण

काष्ठा kcore अणु
	पूर्णांक fd;
	पूर्णांक elfclass;
	Elf *elf;
	GElf_Ehdr ehdr;
पूर्ण;

अटल पूर्णांक kcore__खोलो(काष्ठा kcore *kcore, स्थिर अक्षर *filename)
अणु
	GElf_Ehdr *ehdr;

	kcore->fd = खोलो(filename, O_RDONLY);
	अगर (kcore->fd == -1)
		वापस -1;

	kcore->elf = elf_begin(kcore->fd, ELF_C_READ, शून्य);
	अगर (!kcore->elf)
		जाओ out_बंद;

	kcore->elfclass = gelf_अ_लोlass(kcore->elf);
	अगर (kcore->elfclass == ELFCLASSNONE)
		जाओ out_end;

	ehdr = gelf_getehdr(kcore->elf, &kcore->ehdr);
	अगर (!ehdr)
		जाओ out_end;

	वापस 0;

out_end:
	elf_end(kcore->elf);
out_बंद:
	बंद(kcore->fd);
	वापस -1;
पूर्ण

अटल पूर्णांक kcore__init(काष्ठा kcore *kcore, अक्षर *filename, पूर्णांक elfclass,
		       bool temp)
अणु
	kcore->elfclass = elfclass;

	अगर (temp)
		kcore->fd = mkstemp(filename);
	अन्यथा
		kcore->fd = खोलो(filename, O_WRONLY | O_CREAT | O_EXCL, 0400);
	अगर (kcore->fd == -1)
		वापस -1;

	kcore->elf = elf_begin(kcore->fd, ELF_C_WRITE, शून्य);
	अगर (!kcore->elf)
		जाओ out_बंद;

	अगर (!gelf_newehdr(kcore->elf, elfclass))
		जाओ out_end;

	स_रखो(&kcore->ehdr, 0, माप(GElf_Ehdr));

	वापस 0;

out_end:
	elf_end(kcore->elf);
out_बंद:
	बंद(kcore->fd);
	unlink(filename);
	वापस -1;
पूर्ण

अटल व्योम kcore__बंद(काष्ठा kcore *kcore)
अणु
	elf_end(kcore->elf);
	बंद(kcore->fd);
पूर्ण

अटल पूर्णांक kcore__copy_hdr(काष्ठा kcore *from, काष्ठा kcore *to, माप_प्रकार count)
अणु
	GElf_Ehdr *ehdr = &to->ehdr;
	GElf_Ehdr *kehdr = &from->ehdr;

	स_नकल(ehdr->e_ident, kehdr->e_ident, EI_NIDENT);
	ehdr->e_type      = kehdr->e_type;
	ehdr->e_machine   = kehdr->e_machine;
	ehdr->e_version   = kehdr->e_version;
	ehdr->e_entry     = 0;
	ehdr->e_shoff     = 0;
	ehdr->e_flags     = kehdr->e_flags;
	ehdr->e_phnum     = count;
	ehdr->e_shentsize = 0;
	ehdr->e_shnum     = 0;
	ehdr->e_shstrndx  = 0;

	अगर (from->elfclass == ELFCLASS32) अणु
		ehdr->e_phoff     = माप(Elf32_Ehdr);
		ehdr->e_ehsize    = माप(Elf32_Ehdr);
		ehdr->e_phentsize = माप(Elf32_Phdr);
	पूर्ण अन्यथा अणु
		ehdr->e_phoff     = माप(Elf64_Ehdr);
		ehdr->e_ehsize    = माप(Elf64_Ehdr);
		ehdr->e_phentsize = माप(Elf64_Phdr);
	पूर्ण

	अगर (!gelf_update_ehdr(to->elf, ehdr))
		वापस -1;

	अगर (!gelf_newphdr(to->elf, count))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक kcore__add_phdr(काष्ठा kcore *kcore, पूर्णांक idx, off_t offset,
			   u64 addr, u64 len)
अणु
	GElf_Phdr phdr = अणु
		.p_type		= PT_LOAD,
		.p_flags	= PF_R | PF_W | PF_X,
		.p_offset	= offset,
		.p_vaddr	= addr,
		.p_paddr	= 0,
		.p_filesz	= len,
		.p_memsz	= len,
		.p_align	= page_size,
	पूर्ण;

	अगर (!gelf_update_phdr(kcore->elf, idx, &phdr))
		वापस -1;

	वापस 0;
पूर्ण

अटल off_t kcore__ग_लिखो(काष्ठा kcore *kcore)
अणु
	वापस elf_update(kcore->elf, ELF_C_WRITE);
पूर्ण

काष्ठा phdr_data अणु
	off_t offset;
	off_t rel;
	u64 addr;
	u64 len;
	काष्ठा list_head node;
	काष्ठा phdr_data *remaps;
पूर्ण;

काष्ठा sym_data अणु
	u64 addr;
	काष्ठा list_head node;
पूर्ण;

काष्ठा kcore_copy_info अणु
	u64 stext;
	u64 etext;
	u64 first_symbol;
	u64 last_symbol;
	u64 first_module;
	u64 first_module_symbol;
	u64 last_module_symbol;
	माप_प्रकार phnum;
	काष्ठा list_head phdrs;
	काष्ठा list_head syms;
पूर्ण;

#घोषणा kcore_copy__क्रम_each_phdr(k, p) \
	list_क्रम_each_entry((p), &(k)->phdrs, node)

अटल काष्ठा phdr_data *phdr_data__new(u64 addr, u64 len, off_t offset)
अणु
	काष्ठा phdr_data *p = zalloc(माप(*p));

	अगर (p) अणु
		p->addr   = addr;
		p->len    = len;
		p->offset = offset;
	पूर्ण

	वापस p;
पूर्ण

अटल काष्ठा phdr_data *kcore_copy_info__addnew(काष्ठा kcore_copy_info *kci,
						 u64 addr, u64 len,
						 off_t offset)
अणु
	काष्ठा phdr_data *p = phdr_data__new(addr, len, offset);

	अगर (p)
		list_add_tail(&p->node, &kci->phdrs);

	वापस p;
पूर्ण

अटल व्योम kcore_copy__मुक्त_phdrs(काष्ठा kcore_copy_info *kci)
अणु
	काष्ठा phdr_data *p, *पंचांगp;

	list_क्रम_each_entry_safe(p, पंचांगp, &kci->phdrs, node) अणु
		list_del_init(&p->node);
		मुक्त(p);
	पूर्ण
पूर्ण

अटल काष्ठा sym_data *kcore_copy__new_sym(काष्ठा kcore_copy_info *kci,
					    u64 addr)
अणु
	काष्ठा sym_data *s = zalloc(माप(*s));

	अगर (s) अणु
		s->addr = addr;
		list_add_tail(&s->node, &kci->syms);
	पूर्ण

	वापस s;
पूर्ण

अटल व्योम kcore_copy__मुक्त_syms(काष्ठा kcore_copy_info *kci)
अणु
	काष्ठा sym_data *s, *पंचांगp;

	list_क्रम_each_entry_safe(s, पंचांगp, &kci->syms, node) अणु
		list_del_init(&s->node);
		मुक्त(s);
	पूर्ण
पूर्ण

अटल पूर्णांक kcore_copy__process_kallsyms(व्योम *arg, स्थिर अक्षर *name, अक्षर type,
					u64 start)
अणु
	काष्ठा kcore_copy_info *kci = arg;

	अगर (!kallsyms__is_function(type))
		वापस 0;

	अगर (म_अक्षर(name, '[')) अणु
		अगर (!kci->first_module_symbol || start < kci->first_module_symbol)
			kci->first_module_symbol = start;
		अगर (start > kci->last_module_symbol)
			kci->last_module_symbol = start;
		वापस 0;
	पूर्ण

	अगर (!kci->first_symbol || start < kci->first_symbol)
		kci->first_symbol = start;

	अगर (!kci->last_symbol || start > kci->last_symbol)
		kci->last_symbol = start;

	अगर (!म_भेद(name, "_stext")) अणु
		kci->stext = start;
		वापस 0;
	पूर्ण

	अगर (!म_भेद(name, "_etext")) अणु
		kci->etext = start;
		वापस 0;
	पूर्ण

	अगर (is_entry_trampoline(name) && !kcore_copy__new_sym(kci, start))
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक kcore_copy__parse_kallsyms(काष्ठा kcore_copy_info *kci,
				      स्थिर अक्षर *dir)
अणु
	अक्षर kallsyms_filename[PATH_MAX];

	scnम_लिखो(kallsyms_filename, PATH_MAX, "%s/kallsyms", dir);

	अगर (symbol__restricted_filename(kallsyms_filename, "/proc/kallsyms"))
		वापस -1;

	अगर (kallsyms__parse(kallsyms_filename, kci,
			    kcore_copy__process_kallsyms) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक kcore_copy__process_modules(व्योम *arg,
				       स्थिर अक्षर *name __maybe_unused,
				       u64 start, u64 size __maybe_unused)
अणु
	काष्ठा kcore_copy_info *kci = arg;

	अगर (!kci->first_module || start < kci->first_module)
		kci->first_module = start;

	वापस 0;
पूर्ण

अटल पूर्णांक kcore_copy__parse_modules(काष्ठा kcore_copy_info *kci,
				     स्थिर अक्षर *dir)
अणु
	अक्षर modules_filename[PATH_MAX];

	scnम_लिखो(modules_filename, PATH_MAX, "%s/modules", dir);

	अगर (symbol__restricted_filename(modules_filename, "/proc/modules"))
		वापस -1;

	अगर (modules__parse(modules_filename, kci,
			   kcore_copy__process_modules) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक kcore_copy__map(काष्ठा kcore_copy_info *kci, u64 start, u64 end,
			   u64 pgoff, u64 s, u64 e)
अणु
	u64 len, offset;

	अगर (s < start || s >= end)
		वापस 0;

	offset = (s - start) + pgoff;
	len = e < end ? e - s : end - s;

	वापस kcore_copy_info__addnew(kci, s, len, offset) ? 0 : -1;
पूर्ण

अटल पूर्णांक kcore_copy__पढ़ो_map(u64 start, u64 len, u64 pgoff, व्योम *data)
अणु
	काष्ठा kcore_copy_info *kci = data;
	u64 end = start + len;
	काष्ठा sym_data *sdat;

	अगर (kcore_copy__map(kci, start, end, pgoff, kci->stext, kci->etext))
		वापस -1;

	अगर (kcore_copy__map(kci, start, end, pgoff, kci->first_module,
			    kci->last_module_symbol))
		वापस -1;

	list_क्रम_each_entry(sdat, &kci->syms, node) अणु
		u64 s = round_करोwn(sdat->addr, page_size);

		अगर (kcore_copy__map(kci, start, end, pgoff, s, s + len))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kcore_copy__पढ़ो_maps(काष्ठा kcore_copy_info *kci, Elf *elf)
अणु
	अगर (elf_पढ़ो_maps(elf, true, kcore_copy__पढ़ो_map, kci) < 0)
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम kcore_copy__find_remaps(काष्ठा kcore_copy_info *kci)
अणु
	काष्ठा phdr_data *p, *k = शून्य;
	u64 kend;

	अगर (!kci->stext)
		वापस;

	/* Find phdr that corresponds to the kernel map (contains stext) */
	kcore_copy__क्रम_each_phdr(kci, p) अणु
		u64 pend = p->addr + p->len - 1;

		अगर (p->addr <= kci->stext && pend >= kci->stext) अणु
			k = p;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!k)
		वापस;

	kend = k->offset + k->len;

	/* Find phdrs that remap the kernel */
	kcore_copy__क्रम_each_phdr(kci, p) अणु
		u64 pend = p->offset + p->len;

		अगर (p == k)
			जारी;

		अगर (p->offset >= k->offset && pend <= kend)
			p->remaps = k;
	पूर्ण
पूर्ण

अटल व्योम kcore_copy__layout(काष्ठा kcore_copy_info *kci)
अणु
	काष्ठा phdr_data *p;
	off_t rel = 0;

	kcore_copy__find_remaps(kci);

	kcore_copy__क्रम_each_phdr(kci, p) अणु
		अगर (!p->remaps) अणु
			p->rel = rel;
			rel += p->len;
		पूर्ण
		kci->phnum += 1;
	पूर्ण

	kcore_copy__क्रम_each_phdr(kci, p) अणु
		काष्ठा phdr_data *k = p->remaps;

		अगर (k)
			p->rel = p->offset - k->offset + k->rel;
	पूर्ण
पूर्ण

अटल पूर्णांक kcore_copy__calc_maps(काष्ठा kcore_copy_info *kci, स्थिर अक्षर *dir,
				 Elf *elf)
अणु
	अगर (kcore_copy__parse_kallsyms(kci, dir))
		वापस -1;

	अगर (kcore_copy__parse_modules(kci, dir))
		वापस -1;

	अगर (kci->stext)
		kci->stext = round_करोwn(kci->stext, page_size);
	अन्यथा
		kci->stext = round_करोwn(kci->first_symbol, page_size);

	अगर (kci->etext) अणु
		kci->etext = round_up(kci->etext, page_size);
	पूर्ण अन्यथा अगर (kci->last_symbol) अणु
		kci->etext = round_up(kci->last_symbol, page_size);
		kci->etext += page_size;
	पूर्ण

	अगर (kci->first_module_symbol &&
	    (!kci->first_module || kci->first_module_symbol < kci->first_module))
		kci->first_module = kci->first_module_symbol;

	kci->first_module = round_करोwn(kci->first_module, page_size);

	अगर (kci->last_module_symbol) अणु
		kci->last_module_symbol = round_up(kci->last_module_symbol,
						   page_size);
		kci->last_module_symbol += page_size;
	पूर्ण

	अगर (!kci->stext || !kci->etext)
		वापस -1;

	अगर (kci->first_module && !kci->last_module_symbol)
		वापस -1;

	अगर (kcore_copy__पढ़ो_maps(kci, elf))
		वापस -1;

	kcore_copy__layout(kci);

	वापस 0;
पूर्ण

अटल पूर्णांक kcore_copy__copy_file(स्थिर अक्षर *from_dir, स्थिर अक्षर *to_dir,
				 स्थिर अक्षर *name)
अणु
	अक्षर from_filename[PATH_MAX];
	अक्षर to_filename[PATH_MAX];

	scnम_लिखो(from_filename, PATH_MAX, "%s/%s", from_dir, name);
	scnम_लिखो(to_filename, PATH_MAX, "%s/%s", to_dir, name);

	वापस copyfile_mode(from_filename, to_filename, 0400);
पूर्ण

अटल पूर्णांक kcore_copy__unlink(स्थिर अक्षर *dir, स्थिर अक्षर *name)
अणु
	अक्षर filename[PATH_MAX];

	scnम_लिखो(filename, PATH_MAX, "%s/%s", dir, name);

	वापस unlink(filename);
पूर्ण

अटल पूर्णांक kcore_copy__compare_fds(पूर्णांक from, पूर्णांक to)
अणु
	अक्षर *buf_from;
	अक्षर *buf_to;
	sमाप_प्रकार ret;
	माप_प्रकार len;
	पूर्णांक err = -1;

	buf_from = दो_स्मृति(page_size);
	buf_to = दो_स्मृति(page_size);
	अगर (!buf_from || !buf_to)
		जाओ out;

	जबतक (1) अणु
		/* Use पढ़ो because mmap won't work on proc files */
		ret = पढ़ो(from, buf_from, page_size);
		अगर (ret < 0)
			जाओ out;

		अगर (!ret)
			अवरोध;

		len = ret;

		अगर (पढ़ोn(to, buf_to, len) != (पूर्णांक)len)
			जाओ out;

		अगर (स_भेद(buf_from, buf_to, len))
			जाओ out;
	पूर्ण

	err = 0;
out:
	मुक्त(buf_to);
	मुक्त(buf_from);
	वापस err;
पूर्ण

अटल पूर्णांक kcore_copy__compare_files(स्थिर अक्षर *from_filename,
				     स्थिर अक्षर *to_filename)
अणु
	पूर्णांक from, to, err = -1;

	from = खोलो(from_filename, O_RDONLY);
	अगर (from < 0)
		वापस -1;

	to = खोलो(to_filename, O_RDONLY);
	अगर (to < 0)
		जाओ out_बंद_from;

	err = kcore_copy__compare_fds(from, to);

	बंद(to);
out_बंद_from:
	बंद(from);
	वापस err;
पूर्ण

अटल पूर्णांक kcore_copy__compare_file(स्थिर अक्षर *from_dir, स्थिर अक्षर *to_dir,
				    स्थिर अक्षर *name)
अणु
	अक्षर from_filename[PATH_MAX];
	अक्षर to_filename[PATH_MAX];

	scnम_लिखो(from_filename, PATH_MAX, "%s/%s", from_dir, name);
	scnम_लिखो(to_filename, PATH_MAX, "%s/%s", to_dir, name);

	वापस kcore_copy__compare_files(from_filename, to_filename);
पूर्ण

/**
 * kcore_copy - copy kallsyms, modules and kcore from one directory to another.
 * @from_dir: from directory
 * @to_dir: to directory
 *
 * This function copies kallsyms, modules and kcore files from one directory to
 * another.  kallsyms and modules are copied entirely.  Only code segments are
 * copied from kcore.  It is assumed that two segments suffice: one क्रम the
 * kernel proper and one क्रम all the modules.  The code segments are determined
 * from kallsyms and modules files.  The kernel map starts at _stext or the
 * lowest function symbol, and ends at _etext or the highest function symbol.
 * The module map starts at the lowest module address and ends at the highest
 * module symbol.  Start addresses are rounded करोwn to the nearest page.  End
 * addresses are rounded up to the nearest page.  An extra page is added to the
 * highest kernel symbol and highest module symbol to, hopefully, encompass that
 * symbol too.  Because it contains only code sections, the resulting kcore is
 * unusual.  One signअगरicant peculiarity is that the mapping (start -> pgoff)
 * is not the same क्रम the kernel map and the modules map.  That happens because
 * the data is copied adjacently whereas the original kcore has gaps.  Finally,
 * kallsyms and modules files are compared with their copies to check that
 * modules have not been loaded or unloaded जबतक the copies were taking place.
 *
 * Return: %0 on success, %-1 on failure.
 */
पूर्णांक kcore_copy(स्थिर अक्षर *from_dir, स्थिर अक्षर *to_dir)
अणु
	काष्ठा kcore kcore;
	काष्ठा kcore extract;
	पूर्णांक idx = 0, err = -1;
	off_t offset, sz;
	काष्ठा kcore_copy_info kci = अणु .stext = 0, पूर्ण;
	अक्षर kcore_filename[PATH_MAX];
	अक्षर extract_filename[PATH_MAX];
	काष्ठा phdr_data *p;

	INIT_LIST_HEAD(&kci.phdrs);
	INIT_LIST_HEAD(&kci.syms);

	अगर (kcore_copy__copy_file(from_dir, to_dir, "kallsyms"))
		वापस -1;

	अगर (kcore_copy__copy_file(from_dir, to_dir, "modules"))
		जाओ out_unlink_kallsyms;

	scnम_लिखो(kcore_filename, PATH_MAX, "%s/kcore", from_dir);
	scnम_लिखो(extract_filename, PATH_MAX, "%s/kcore", to_dir);

	अगर (kcore__खोलो(&kcore, kcore_filename))
		जाओ out_unlink_modules;

	अगर (kcore_copy__calc_maps(&kci, from_dir, kcore.elf))
		जाओ out_kcore_बंद;

	अगर (kcore__init(&extract, extract_filename, kcore.elfclass, false))
		जाओ out_kcore_बंद;

	अगर (kcore__copy_hdr(&kcore, &extract, kci.phnum))
		जाओ out_extract_बंद;

	offset = gelf_fsize(extract.elf, ELF_T_EHDR, 1, EV_CURRENT) +
		 gelf_fsize(extract.elf, ELF_T_PHDR, kci.phnum, EV_CURRENT);
	offset = round_up(offset, page_size);

	kcore_copy__क्रम_each_phdr(&kci, p) अणु
		off_t offs = p->rel + offset;

		अगर (kcore__add_phdr(&extract, idx++, offs, p->addr, p->len))
			जाओ out_extract_बंद;
	पूर्ण

	sz = kcore__ग_लिखो(&extract);
	अगर (sz < 0 || sz > offset)
		जाओ out_extract_बंद;

	kcore_copy__क्रम_each_phdr(&kci, p) अणु
		off_t offs = p->rel + offset;

		अगर (p->remaps)
			जारी;
		अगर (copy_bytes(kcore.fd, p->offset, extract.fd, offs, p->len))
			जाओ out_extract_बंद;
	पूर्ण

	अगर (kcore_copy__compare_file(from_dir, to_dir, "modules"))
		जाओ out_extract_बंद;

	अगर (kcore_copy__compare_file(from_dir, to_dir, "kallsyms"))
		जाओ out_extract_बंद;

	err = 0;

out_extract_बंद:
	kcore__बंद(&extract);
	अगर (err)
		unlink(extract_filename);
out_kcore_बंद:
	kcore__बंद(&kcore);
out_unlink_modules:
	अगर (err)
		kcore_copy__unlink(to_dir, "modules");
out_unlink_kallsyms:
	अगर (err)
		kcore_copy__unlink(to_dir, "kallsyms");

	kcore_copy__मुक्त_phdrs(&kci);
	kcore_copy__मुक्त_syms(&kci);

	वापस err;
पूर्ण

पूर्णांक kcore_extract__create(काष्ठा kcore_extract *kce)
अणु
	काष्ठा kcore kcore;
	काष्ठा kcore extract;
	माप_प्रकार count = 1;
	पूर्णांक idx = 0, err = -1;
	off_t offset = page_size, sz;

	अगर (kcore__खोलो(&kcore, kce->kcore_filename))
		वापस -1;

	म_नकल(kce->extract_filename, PERF_KCORE_EXTRACT);
	अगर (kcore__init(&extract, kce->extract_filename, kcore.elfclass, true))
		जाओ out_kcore_बंद;

	अगर (kcore__copy_hdr(&kcore, &extract, count))
		जाओ out_extract_बंद;

	अगर (kcore__add_phdr(&extract, idx, offset, kce->addr, kce->len))
		जाओ out_extract_बंद;

	sz = kcore__ग_लिखो(&extract);
	अगर (sz < 0 || sz > offset)
		जाओ out_extract_बंद;

	अगर (copy_bytes(kcore.fd, kce->offs, extract.fd, offset, kce->len))
		जाओ out_extract_बंद;

	err = 0;

out_extract_बंद:
	kcore__बंद(&extract);
	अगर (err)
		unlink(kce->extract_filename);
out_kcore_बंद:
	kcore__बंद(&kcore);

	वापस err;
पूर्ण

व्योम kcore_extract__delete(काष्ठा kcore_extract *kce)
अणु
	unlink(kce->extract_filename);
पूर्ण

#अगर_घोषित HAVE_GELF_GETNOTE_SUPPORT

अटल व्योम sdt_adjust_loc(काष्ठा sdt_note *पंचांगp, GElf_Addr base_off)
अणु
	अगर (!base_off)
		वापस;

	अगर (पंचांगp->bit32)
		पंचांगp->addr.a32[SDT_NOTE_IDX_LOC] =
			पंचांगp->addr.a32[SDT_NOTE_IDX_LOC] + base_off -
			पंचांगp->addr.a32[SDT_NOTE_IDX_BASE];
	अन्यथा
		पंचांगp->addr.a64[SDT_NOTE_IDX_LOC] =
			पंचांगp->addr.a64[SDT_NOTE_IDX_LOC] + base_off -
			पंचांगp->addr.a64[SDT_NOTE_IDX_BASE];
पूर्ण

अटल व्योम sdt_adjust_refctr(काष्ठा sdt_note *पंचांगp, GElf_Addr base_addr,
			      GElf_Addr base_off)
अणु
	अगर (!base_off)
		वापस;

	अगर (पंचांगp->bit32 && पंचांगp->addr.a32[SDT_NOTE_IDX_REFCTR])
		पंचांगp->addr.a32[SDT_NOTE_IDX_REFCTR] -= (base_addr - base_off);
	अन्यथा अगर (पंचांगp->addr.a64[SDT_NOTE_IDX_REFCTR])
		पंचांगp->addr.a64[SDT_NOTE_IDX_REFCTR] -= (base_addr - base_off);
पूर्ण

/**
 * populate_sdt_note : Parse raw data and identअगरy SDT note
 * @elf: elf of the खोलोed file
 * @data: raw data of a section with description offset applied
 * @len: note description size
 * @type: type of the note
 * @sdt_notes: List to add the SDT note
 *
 * Responsible क्रम parsing the @data in section .note.stapsdt in @elf and
 * अगर its an SDT note, it appends to @sdt_notes list.
 */
अटल पूर्णांक populate_sdt_note(Elf **elf, स्थिर अक्षर *data, माप_प्रकार len,
			     काष्ठा list_head *sdt_notes)
अणु
	स्थिर अक्षर *provider, *name, *args;
	काष्ठा sdt_note *पंचांगp = शून्य;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	पूर्णांक ret = -EINVAL;

	जोड़ अणु
		Elf64_Addr a64[NR_ADDR];
		Elf32_Addr a32[NR_ADDR];
	पूर्ण buf;

	Elf_Data dst = अणु
		.d_buf = &buf, .d_type = ELF_T_ADDR, .d_version = EV_CURRENT,
		.d_size = gelf_fsize((*elf), ELF_T_ADDR, NR_ADDR, EV_CURRENT),
		.d_off = 0, .d_align = 0
	पूर्ण;
	Elf_Data src = अणु
		.d_buf = (व्योम *) data, .d_type = ELF_T_ADDR,
		.d_version = EV_CURRENT, .d_size = dst.d_size, .d_off = 0,
		.d_align = 0
	पूर्ण;

	पंचांगp = (काष्ठा sdt_note *)सुस्मृति(1, माप(काष्ठा sdt_note));
	अगर (!पंचांगp) अणु
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण

	INIT_LIST_HEAD(&पंचांगp->note_list);

	अगर (len < dst.d_size + 3)
		जाओ out_मुक्त_note;

	/* Translation from file representation to memory representation */
	अगर (gelf_xlatetom(*elf, &dst, &src,
			  elf_getident(*elf, शून्य)[EI_DATA]) == शून्य) अणु
		pr_err("gelf_xlatetom : %s\n", elf_errmsg(-1));
		जाओ out_मुक्त_note;
	पूर्ण

	/* Populate the fields of sdt_note */
	provider = data + dst.d_size;

	name = (स्थिर अक्षर *)स_प्रथम(provider, '\0', data + len - provider);
	अगर (name++ == शून्य)
		जाओ out_मुक्त_note;

	पंचांगp->provider = strdup(provider);
	अगर (!पंचांगp->provider) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_note;
	पूर्ण
	पंचांगp->name = strdup(name);
	अगर (!पंचांगp->name) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_prov;
	पूर्ण

	args = स_प्रथम(name, '\0', data + len - name);

	/*
	 * There is no argument अगर:
	 * - We reached the end of the note;
	 * - There is not enough room to hold a potential string;
	 * - The argument string is empty or just contains ':'.
	 */
	अगर (args == शून्य || data + len - args < 2 ||
		args[1] == ':' || args[1] == '\0')
		पंचांगp->args = शून्य;
	अन्यथा अणु
		पंचांगp->args = strdup(++args);
		अगर (!पंचांगp->args) अणु
			ret = -ENOMEM;
			जाओ out_मुक्त_name;
		पूर्ण
	पूर्ण

	अगर (gelf_अ_लोlass(*elf) == ELFCLASS32) अणु
		स_नकल(&पंचांगp->addr, &buf, 3 * माप(Elf32_Addr));
		पंचांगp->bit32 = true;
	पूर्ण अन्यथा अणु
		स_नकल(&पंचांगp->addr, &buf, 3 * माप(Elf64_Addr));
		पंचांगp->bit32 = false;
	पूर्ण

	अगर (!gelf_getehdr(*elf, &ehdr)) अणु
		pr_debug("%s : cannot get elf header.\n", __func__);
		ret = -EBADF;
		जाओ out_मुक्त_args;
	पूर्ण

	/* Adjust the prelink effect :
	 * Find out the .stapsdt.base section.
	 * This scn will help us to handle prelinking (अगर present).
	 * Compare the retrieved file offset of the base section with the
	 * base address in the description of the SDT note. If its dअगरferent,
	 * then accordingly, adjust the note location.
	 */
	अगर (elf_section_by_name(*elf, &ehdr, &shdr, SDT_BASE_SCN, शून्य))
		sdt_adjust_loc(पंचांगp, shdr.sh_offset);

	/* Adjust reference counter offset */
	अगर (elf_section_by_name(*elf, &ehdr, &shdr, SDT_PROBES_SCN, शून्य))
		sdt_adjust_refctr(पंचांगp, shdr.sh_addr, shdr.sh_offset);

	list_add_tail(&पंचांगp->note_list, sdt_notes);
	वापस 0;

out_मुक्त_args:
	zमुक्त(&पंचांगp->args);
out_मुक्त_name:
	zमुक्त(&पंचांगp->name);
out_मुक्त_prov:
	zमुक्त(&पंचांगp->provider);
out_मुक्त_note:
	मुक्त(पंचांगp);
out_err:
	वापस ret;
पूर्ण

/**
 * स्थिरruct_sdt_notes_list : स्थिरructs a list of SDT notes
 * @elf : elf to look पूर्णांकo
 * @sdt_notes : empty list_head
 *
 * Scans the sections in 'elf' क्रम the section
 * .note.stapsdt. It, then calls populate_sdt_note to find
 * out the SDT events and populates the 'sdt_notes'.
 */
अटल पूर्णांक स्थिरruct_sdt_notes_list(Elf *elf, काष्ठा list_head *sdt_notes)
अणु
	GElf_Ehdr ehdr;
	Elf_Scn *scn = शून्य;
	Elf_Data *data;
	GElf_Shdr shdr;
	माप_प्रकार shstrndx, next;
	GElf_Nhdr nhdr;
	माप_प्रकार name_off, desc_off, offset;
	पूर्णांक ret = 0;

	अगर (gelf_getehdr(elf, &ehdr) == शून्य) अणु
		ret = -EBADF;
		जाओ out_ret;
	पूर्ण
	अगर (elf_माला_लोhdrstrndx(elf, &shstrndx) != 0) अणु
		ret = -EBADF;
		जाओ out_ret;
	पूर्ण

	/* Look क्रम the required section */
	scn = elf_section_by_name(elf, &ehdr, &shdr, SDT_NOTE_SCN, शून्य);
	अगर (!scn) अणु
		ret = -ENOENT;
		जाओ out_ret;
	पूर्ण

	अगर ((shdr.sh_type != SHT_NOTE) || (shdr.sh_flags & SHF_ALLOC)) अणु
		ret = -ENOENT;
		जाओ out_ret;
	पूर्ण

	data = elf_getdata(scn, शून्य);

	/* Get the SDT notes */
	क्रम (offset = 0; (next = gelf_getnote(data, offset, &nhdr, &name_off,
					      &desc_off)) > 0; offset = next) अणु
		अगर (nhdr.n_namesz == माप(SDT_NOTE_NAME) &&
		    !स_भेद(data->d_buf + name_off, SDT_NOTE_NAME,
			    माप(SDT_NOTE_NAME))) अणु
			/* Check the type of the note */
			अगर (nhdr.n_type != SDT_NOTE_TYPE)
				जाओ out_ret;

			ret = populate_sdt_note(&elf, ((data->d_buf) + desc_off),
						nhdr.n_descsz, sdt_notes);
			अगर (ret < 0)
				जाओ out_ret;
		पूर्ण
	पूर्ण
	अगर (list_empty(sdt_notes))
		ret = -ENOENT;

out_ret:
	वापस ret;
पूर्ण

/**
 * get_sdt_note_list : Wrapper to स्थिरruct a list of sdt notes
 * @head : empty list_head
 * @target : file to find SDT notes from
 *
 * This खोलोs the file, initializes
 * the ELF and then calls स्थिरruct_sdt_notes_list.
 */
पूर्णांक get_sdt_note_list(काष्ठा list_head *head, स्थिर अक्षर *target)
अणु
	Elf *elf;
	पूर्णांक fd, ret;

	fd = खोलो(target, O_RDONLY);
	अगर (fd < 0)
		वापस -EBADF;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (!elf) अणु
		ret = -EBADF;
		जाओ out_बंद;
	पूर्ण
	ret = स्थिरruct_sdt_notes_list(elf, head);
	elf_end(elf);
out_बंद:
	बंद(fd);
	वापस ret;
पूर्ण

/**
 * cleanup_sdt_note_list : मुक्त the sdt notes' list
 * @sdt_notes: sdt notes' list
 *
 * Free up the SDT notes in @sdt_notes.
 * Returns the number of SDT notes मुक्त'd.
 */
पूर्णांक cleanup_sdt_note_list(काष्ठा list_head *sdt_notes)
अणु
	काष्ठा sdt_note *पंचांगp, *pos;
	पूर्णांक nr_मुक्त = 0;

	list_क्रम_each_entry_safe(pos, पंचांगp, sdt_notes, note_list) अणु
		list_del_init(&pos->note_list);
		zमुक्त(&pos->args);
		zमुक्त(&pos->name);
		zमुक्त(&pos->provider);
		मुक्त(pos);
		nr_मुक्त++;
	पूर्ण
	वापस nr_मुक्त;
पूर्ण

/**
 * sdt_notes__get_count: Counts the number of sdt events
 * @start: list_head to sdt_notes list
 *
 * Returns the number of SDT notes in a list
 */
पूर्णांक sdt_notes__get_count(काष्ठा list_head *start)
अणु
	काष्ठा sdt_note *sdt_ptr;
	पूर्णांक count = 0;

	list_क्रम_each_entry(sdt_ptr, start, note_list)
		count++;
	वापस count;
पूर्ण
#पूर्ण_अगर

व्योम symbol__elf_init(व्योम)
अणु
	elf_version(EV_CURRENT);
पूर्ण
