<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_SYMBOL
#घोषणा __PERF_SYMBOL 1

#समावेश <linux/types.h>
#समावेश <linux/refcount.h>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <मानकपन.स>
#समावेश "path.h"
#समावेश "symbol_conf.h"
#समावेश "spark.h"

#अगर_घोषित HAVE_LIBELF_SUPPORT
#समावेश <libelf.h>
#समावेश <gelf.h>
#पूर्ण_अगर
#समावेश <elf.h>

काष्ठा dso;
काष्ठा map;
काष्ठा maps;
काष्ठा option;
काष्ठा build_id;

/*
 * libelf 0.8.x and earlier करो not support ELF_C_READ_MMAP;
 * क्रम newer versions we can use mmap to reduce memory usage:
 */
#अगर_घोषित ELF_C_READ_MMAP
# define PERF_ELF_C_READ_MMAP ELF_C_READ_MMAP
#अन्यथा
# define PERF_ELF_C_READ_MMAP ELF_C_READ
#पूर्ण_अगर

#अगर_घोषित HAVE_LIBELF_SUPPORT
Elf_Scn *elf_section_by_name(Elf *elf, GElf_Ehdr *ep,
			     GElf_Shdr *shp, स्थिर अक्षर *name, माप_प्रकार *idx);
#पूर्ण_अगर

/** काष्ठा symbol - symtab entry
 *
 * @ignore - resolvable but tools ignore it (e.g. idle routines)
 */
काष्ठा symbol अणु
	काष्ठा rb_node	rb_node;
	u64		start;
	u64		end;
	u16		namelen;
	u8		type:4;
	u8		binding:4;
	u8		idle:1;
	u8		ignore:1;
	u8		अंतरभूतd:1;
	u8		arch_sym;
	bool		annotate2;
	अक्षर		name[];
पूर्ण;

व्योम symbol__delete(काष्ठा symbol *sym);
व्योम symbols__delete(काष्ठा rb_root_cached *symbols);

/* symbols__क्रम_each_entry - iterate over symbols (rb_root)
 *
 * @symbols: the rb_root of symbols
 * @pos: the 'struct symbol *' to use as a loop cursor
 * @nd: the 'struct rb_node *' to use as a temporary storage
 */
#घोषणा symbols__क्रम_each_entry(symbols, pos, nd)			\
	क्रम (nd = rb_first_cached(symbols);					\
	     nd && (pos = rb_entry(nd, काष्ठा symbol, rb_node));	\
	     nd = rb_next(nd))

अटल अंतरभूत माप_प्रकार symbol__size(स्थिर काष्ठा symbol *sym)
अणु
	वापस sym->end - sym->start;
पूर्ण

काष्ठा strlist;
काष्ठा पूर्णांकlist;

काष्ठा symbol_name_rb_node अणु
	काष्ठा rb_node	rb_node;
	काष्ठा symbol	sym;
पूर्ण;

अटल अंतरभूत पूर्णांक __symbol__join_symfs(अक्षर *bf, माप_प्रकार size, स्थिर अक्षर *path)
अणु
	वापस path__join(bf, size, symbol_conf.symfs, path);
पूर्ण

#घोषणा symbol__join_symfs(bf, path) __symbol__join_symfs(bf, माप(bf), path)

बाह्य पूर्णांक vmlinux_path__nr_entries;
बाह्य अक्षर **vmlinux_path;

अटल अंतरभूत व्योम *symbol__priv(काष्ठा symbol *sym)
अणु
	वापस ((व्योम *)sym) - symbol_conf.priv_size;
पूर्ण

काष्ठा ref_reloc_sym अणु
	स्थिर अक्षर	*name;
	u64		addr;
	u64		unrelocated_addr;
पूर्ण;

काष्ठा addr_location अणु
	काष्ठा thपढ़ो *thपढ़ो;
	काष्ठा maps   *maps;
	काष्ठा map    *map;
	काष्ठा symbol *sym;
	स्थिर अक्षर    *srcline;
	u64	      addr;
	अक्षर	      level;
	u8	      filtered;
	u8	      cpumode;
	s32	      cpu;
	s32	      socket;
पूर्ण;

पूर्णांक dso__load(काष्ठा dso *dso, काष्ठा map *map);
पूर्णांक dso__load_vmlinux(काष्ठा dso *dso, काष्ठा map *map,
		      स्थिर अक्षर *vmlinux, bool vmlinux_allocated);
पूर्णांक dso__load_vmlinux_path(काष्ठा dso *dso, काष्ठा map *map);
पूर्णांक __dso__load_kallsyms(काष्ठा dso *dso, स्थिर अक्षर *filename, काष्ठा map *map,
			 bool no_kcore);
पूर्णांक dso__load_kallsyms(काष्ठा dso *dso, स्थिर अक्षर *filename, काष्ठा map *map);

व्योम dso__insert_symbol(काष्ठा dso *dso,
			काष्ठा symbol *sym);
व्योम dso__delete_symbol(काष्ठा dso *dso,
			काष्ठा symbol *sym);

काष्ठा symbol *dso__find_symbol(काष्ठा dso *dso, u64 addr);
काष्ठा symbol *dso__find_symbol_by_name(काष्ठा dso *dso, स्थिर अक्षर *name);

काष्ठा symbol *symbol__next_by_name(काष्ठा symbol *sym);

काष्ठा symbol *dso__first_symbol(काष्ठा dso *dso);
काष्ठा symbol *dso__last_symbol(काष्ठा dso *dso);
काष्ठा symbol *dso__next_symbol(काष्ठा symbol *sym);

क्रमागत dso_type dso__type_fd(पूर्णांक fd);

पूर्णांक filename__पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *id);
पूर्णांक sysfs__पढ़ो_build_id(स्थिर अक्षर *filename, काष्ठा build_id *bid);
पूर्णांक modules__parse(स्थिर अक्षर *filename, व्योम *arg,
		   पूर्णांक (*process_module)(व्योम *arg, स्थिर अक्षर *name,
					 u64 start, u64 size));
पूर्णांक filename__पढ़ो_debuglink(स्थिर अक्षर *filename, अक्षर *debuglink,
			     माप_प्रकार size);

काष्ठा perf_env;
पूर्णांक symbol__init(काष्ठा perf_env *env);
व्योम symbol__निकास(व्योम);
व्योम symbol__elf_init(व्योम);
पूर्णांक symbol__annotation_init(व्योम);

काष्ठा symbol *symbol__new(u64 start, u64 len, u8 binding, u8 type, स्थिर अक्षर *name);
माप_प्रकार __symbol__ख_लिखो_symname_offs(स्थिर काष्ठा symbol *sym,
				      स्थिर काष्ठा addr_location *al,
				      bool unknown_as_addr,
				      bool prपूर्णांक_offsets, खाता *fp);
माप_प्रकार symbol__ख_लिखो_symname_offs(स्थिर काष्ठा symbol *sym,
				    स्थिर काष्ठा addr_location *al, खाता *fp);
माप_प्रकार __symbol__ख_लिखो_symname(स्थिर काष्ठा symbol *sym,
				 स्थिर काष्ठा addr_location *al,
				 bool unknown_as_addr, खाता *fp);
माप_प्रकार symbol__ख_लिखो_symname(स्थिर काष्ठा symbol *sym, खाता *fp);
माप_प्रकार symbol__ख_लिखो(काष्ठा symbol *sym, खाता *fp);
bool symbol__restricted_filename(स्थिर अक्षर *filename,
				 स्थिर अक्षर *restricted_filename);
पूर्णांक symbol__config_symfs(स्थिर काष्ठा option *opt __maybe_unused,
			 स्थिर अक्षर *dir, पूर्णांक unset __maybe_unused);

काष्ठा symsrc;

#अगर_घोषित HAVE_LIBBFD_SUPPORT
पूर्णांक dso__load_bfd_symbols(काष्ठा dso *dso, स्थिर अक्षर *debugfile);
#पूर्ण_अगर

पूर्णांक dso__load_sym(काष्ठा dso *dso, काष्ठा map *map, काष्ठा symsrc *syms_ss,
		  काष्ठा symsrc *runसमय_ss, पूर्णांक kmodule);
पूर्णांक dso__synthesize_plt_symbols(काष्ठा dso *dso, काष्ठा symsrc *ss);

अक्षर *dso__demangle_sym(काष्ठा dso *dso, पूर्णांक kmodule, स्थिर अक्षर *elf_name);

व्योम __symbols__insert(काष्ठा rb_root_cached *symbols, काष्ठा symbol *sym,
		       bool kernel);
व्योम symbols__insert(काष्ठा rb_root_cached *symbols, काष्ठा symbol *sym);
व्योम symbols__fixup_duplicate(काष्ठा rb_root_cached *symbols);
व्योम symbols__fixup_end(काष्ठा rb_root_cached *symbols);
व्योम maps__fixup_end(काष्ठा maps *maps);

प्रकार पूर्णांक (*mapfn_t)(u64 start, u64 len, u64 pgoff, व्योम *data);
पूर्णांक file__पढ़ो_maps(पूर्णांक fd, bool exe, mapfn_t mapfn, व्योम *data,
		    bool *is_64_bit);

#घोषणा PERF_KCORE_EXTRACT "/tmp/perf-kcore-XXXXXX"

काष्ठा kcore_extract अणु
	अक्षर *kcore_filename;
	u64 addr;
	u64 offs;
	u64 len;
	अक्षर extract_filename[माप(PERF_KCORE_EXTRACT)];
	पूर्णांक fd;
पूर्ण;

पूर्णांक kcore_extract__create(काष्ठा kcore_extract *kce);
व्योम kcore_extract__delete(काष्ठा kcore_extract *kce);

पूर्णांक kcore_copy(स्थिर अक्षर *from_dir, स्थिर अक्षर *to_dir);
पूर्णांक compare_proc_modules(स्थिर अक्षर *from, स्थिर अक्षर *to);

पूर्णांक setup_list(काष्ठा strlist **list, स्थिर अक्षर *list_str,
	       स्थिर अक्षर *list_name);
पूर्णांक setup_पूर्णांकlist(काष्ठा पूर्णांकlist **list, स्थिर अक्षर *list_str,
		  स्थिर अक्षर *list_name);

#अगर_घोषित HAVE_LIBELF_SUPPORT
bool elf__needs_adjust_symbols(GElf_Ehdr ehdr);
व्योम arch__sym_update(काष्ठा symbol *s, GElf_Sym *sym);
#पूर्ण_अगर

स्थिर अक्षर *arch__normalize_symbol_name(स्थिर अक्षर *name);
#घोषणा SYMBOL_A 0
#घोषणा SYMBOL_B 1

व्योम arch__symbols__fixup_end(काष्ठा symbol *p, काष्ठा symbol *c);
पूर्णांक arch__compare_symbol_names(स्थिर अक्षर *namea, स्थिर अक्षर *nameb);
पूर्णांक arch__compare_symbol_names_n(स्थिर अक्षर *namea, स्थिर अक्षर *nameb,
				 अचिन्हित पूर्णांक n);
पूर्णांक arch__choose_best_symbol(काष्ठा symbol *syma, काष्ठा symbol *symb);

क्रमागत symbol_tag_include अणु
	SYMBOL_TAG_INCLUDE__NONE = 0,
	SYMBOL_TAG_INCLUDE__DEFAULT_ONLY
पूर्ण;

पूर्णांक symbol__match_symbol_name(स्थिर अक्षर *namea, स्थिर अक्षर *nameb,
			      क्रमागत symbol_tag_include includes);

/* काष्ठाure containing an SDT note's info */
काष्ठा sdt_note अणु
	अक्षर *name;			/* name of the note*/
	अक्षर *provider;			/* provider name */
	अक्षर *args;
	bool bit32;			/* whether the location is 32 bits? */
	जोड़ अणु				/* location, base and semaphore addrs */
		Elf64_Addr a64[3];
		Elf32_Addr a32[3];
	पूर्ण addr;
	काष्ठा list_head note_list;	/* SDT notes' list */
पूर्ण;

पूर्णांक get_sdt_note_list(काष्ठा list_head *head, स्थिर अक्षर *target);
पूर्णांक cleanup_sdt_note_list(काष्ठा list_head *sdt_notes);
पूर्णांक sdt_notes__get_count(काष्ठा list_head *start);

#घोषणा SDT_PROBES_SCN ".probes"
#घोषणा SDT_BASE_SCN ".stapsdt.base"
#घोषणा SDT_NOTE_SCN  ".note.stapsdt"
#घोषणा SDT_NOTE_TYPE 3
#घोषणा SDT_NOTE_NAME "stapsdt"
#घोषणा NR_ADDR 3

क्रमागत अणु
	SDT_NOTE_IDX_LOC = 0,
	SDT_NOTE_IDX_BASE,
	SDT_NOTE_IDX_REFCTR,
पूर्ण;

काष्ठा mem_info *mem_info__new(व्योम);
काष्ठा mem_info *mem_info__get(काष्ठा mem_info *mi);
व्योम   mem_info__put(काष्ठा mem_info *mi);

अटल अंतरभूत व्योम __mem_info__zput(काष्ठा mem_info **mi)
अणु
	mem_info__put(*mi);
	*mi = शून्य;
पूर्ण

#घोषणा mem_info__zput(mi) __mem_info__zput(&mi)

#पूर्ण_अगर /* __PERF_SYMBOL */
