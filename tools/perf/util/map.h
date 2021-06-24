<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_MAP_H
#घोषणा __PERF_MAP_H

#समावेश <linux/refcount.h>
#समावेश <linux/compiler.h>
#समावेश <linux/list.h>
#समावेश <linux/rbtree.h>
#समावेश <मानकपन.स>
#समावेश <माला.स>
#समावेश <stdbool.h>
#समावेश <linux/types.h>

काष्ठा dso;
काष्ठा maps;
काष्ठा machine;

काष्ठा map अणु
	जोड़ अणु
		काष्ठा rb_node	rb_node;
		काष्ठा list_head node;
	पूर्ण;
	u64			start;
	u64			end;
	bool			erange_warned:1;
	bool			priv:1;
	u32			prot;
	u64			pgoff;
	u64			reloc;

	/* ip -> dso rip */
	u64			(*map_ip)(काष्ठा map *, u64);
	/* dso rip -> ip */
	u64			(*unmap_ip)(काष्ठा map *, u64);

	काष्ठा dso		*dso;
	refcount_t		refcnt;
	u32			flags;
पूर्ण;

काष्ठा kmap;

काष्ठा kmap *__map__kmap(काष्ठा map *map);
काष्ठा kmap *map__kmap(काष्ठा map *map);
काष्ठा maps *map__kmaps(काष्ठा map *map);

अटल अंतरभूत u64 map__map_ip(काष्ठा map *map, u64 ip)
अणु
	वापस ip - map->start + map->pgoff;
पूर्ण

अटल अंतरभूत u64 map__unmap_ip(काष्ठा map *map, u64 ip)
अणु
	वापस ip + map->start - map->pgoff;
पूर्ण

अटल अंतरभूत u64 identity__map_ip(काष्ठा map *map __maybe_unused, u64 ip)
अणु
	वापस ip;
पूर्ण

अटल अंतरभूत माप_प्रकार map__size(स्थिर काष्ठा map *map)
अणु
	वापस map->end - map->start;
पूर्ण

/* rip/ip <-> addr suitable क्रम passing to `objdump --start-address=` */
u64 map__rip_2objdump(काष्ठा map *map, u64 rip);

/* objdump address -> memory address */
u64 map__objdump_2mem(काष्ठा map *map, u64 ip);

काष्ठा symbol;
काष्ठा thपढ़ो;

/* map__क्रम_each_symbol - iterate over the symbols in the given map
 *
 * @map: the 'struct map *' in which symbols are iterated
 * @pos: the 'struct symbol *' to use as a loop cursor
 * @n: the 'struct rb_node *' to use as a temporary storage
 * Note: caller must ensure map->dso is not शून्य (map is loaded).
 */
#घोषणा map__क्रम_each_symbol(map, pos, n)	\
	dso__क्रम_each_symbol(map->dso, pos, n)

/* map__क्रम_each_symbol_with_name - iterate over the symbols in the given map
 *                                  that have the given name
 *
 * @map: the 'struct map *' in which symbols are iterated
 * @sym_name: the symbol name
 * @pos: the 'struct symbol *' to use as a loop cursor
 */
#घोषणा __map__क्रम_each_symbol_by_name(map, sym_name, pos)	\
	क्रम (pos = map__find_symbol_by_name(map, sym_name);	\
	     pos &&						\
	     !symbol__match_symbol_name(pos->name, sym_name,	\
					SYMBOL_TAG_INCLUDE__DEFAULT_ONLY); \
	     pos = symbol__next_by_name(pos))

#घोषणा map__क्रम_each_symbol_by_name(map, sym_name, pos)		\
	__map__क्रम_each_symbol_by_name(map, sym_name, (pos))

व्योम map__init(काष्ठा map *map,
	       u64 start, u64 end, u64 pgoff, काष्ठा dso *dso);

काष्ठा dso_id;
काष्ठा build_id;

काष्ठा map *map__new(काष्ठा machine *machine, u64 start, u64 len,
		     u64 pgoff, काष्ठा dso_id *id, u32 prot, u32 flags,
		     काष्ठा build_id *bid, अक्षर *filename, काष्ठा thपढ़ो *thपढ़ो);
काष्ठा map *map__new2(u64 start, काष्ठा dso *dso);
व्योम map__delete(काष्ठा map *map);
काष्ठा map *map__clone(काष्ठा map *map);

अटल अंतरभूत काष्ठा map *map__get(काष्ठा map *map)
अणु
	अगर (map)
		refcount_inc(&map->refcnt);
	वापस map;
पूर्ण

व्योम map__put(काष्ठा map *map);

अटल अंतरभूत व्योम __map__zput(काष्ठा map **map)
अणु
	map__put(*map);
	*map = शून्य;
पूर्ण

#घोषणा map__zput(map) __map__zput(&map)

माप_प्रकार map__ख_लिखो(काष्ठा map *map, खाता *fp);
माप_प्रकार map__ख_लिखो_dsoname(काष्ठा map *map, खाता *fp);
अक्षर *map__srcline(काष्ठा map *map, u64 addr, काष्ठा symbol *sym);
पूर्णांक map__ख_लिखो_srcline(काष्ठा map *map, u64 addr, स्थिर अक्षर *prefix,
			 खाता *fp);

पूर्णांक map__load(काष्ठा map *map);
काष्ठा symbol *map__find_symbol(काष्ठा map *map, u64 addr);
काष्ठा symbol *map__find_symbol_by_name(काष्ठा map *map, स्थिर अक्षर *name);
व्योम map__fixup_start(काष्ठा map *map);
व्योम map__fixup_end(काष्ठा map *map);

पूर्णांक map__set_kallsyms_ref_reloc_sym(काष्ठा map *map, स्थिर अक्षर *symbol_name,
				    u64 addr);

bool __map__is_kernel(स्थिर काष्ठा map *map);
bool __map__is_extra_kernel_map(स्थिर काष्ठा map *map);
bool __map__is_bpf_prog(स्थिर काष्ठा map *map);
bool __map__is_bpf_image(स्थिर काष्ठा map *map);
bool __map__is_ool(स्थिर काष्ठा map *map);

अटल अंतरभूत bool __map__is_kmodule(स्थिर काष्ठा map *map)
अणु
	वापस !__map__is_kernel(map) && !__map__is_extra_kernel_map(map) &&
	       !__map__is_bpf_prog(map) && !__map__is_ool(map) &&
	       !__map__is_bpf_image(map);
पूर्ण

bool map__has_symbols(स्थिर काष्ठा map *map);

#घोषणा ENTRY_TRAMPOLINE_NAME "__entry_SYSCALL_64_trampoline"

अटल अंतरभूत bool is_entry_trampoline(स्थिर अक्षर *name)
अणु
	वापस !म_भेद(name, ENTRY_TRAMPOLINE_NAME);
पूर्ण

अटल अंतरभूत bool is_bpf_image(स्थिर अक्षर *name)
अणु
	वापस म_भेदन(name, "bpf_trampoline_", माप("bpf_trampoline_") - 1) == 0 ||
	       म_भेदन(name, "bpf_dispatcher_", माप("bpf_dispatcher_") - 1) == 0;
पूर्ण

अटल अंतरभूत पूर्णांक is_anon_memory(स्थिर अक्षर *filename)
अणु
	वापस !म_भेद(filename, "//anon") ||
	       !म_भेदन(filename, "/dev/zero", माप("/dev/zero") - 1) ||
	       !म_भेदन(filename, "/anon_hugepage", माप("/anon_hugepage") - 1);
पूर्ण

अटल अंतरभूत पूर्णांक is_no_dso_memory(स्थिर अक्षर *filename)
अणु
	वापस !म_भेदन(filename, "[stack", 6) ||
	       !म_भेदन(filename, "/SYSV", 5)  ||
	       !म_भेद(filename, "[heap]");
पूर्ण
#पूर्ण_अगर /* __PERF_MAP_H */
