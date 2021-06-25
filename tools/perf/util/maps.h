<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PERF_MAPS_H
#घोषणा __PERF_MAPS_H

#समावेश <linux/refcount.h>
#समावेश <linux/rbtree.h>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <linux/types.h>
#समावेश "rwsem.h"

काष्ठा ref_reloc_sym;
काष्ठा machine;
काष्ठा map;
काष्ठा maps;
काष्ठा thपढ़ो;

काष्ठा map *maps__find(काष्ठा maps *maps, u64 addr);
काष्ठा map *maps__first(काष्ठा maps *maps);
काष्ठा map *map__next(काष्ठा map *map);

#घोषणा maps__क्रम_each_entry(maps, map) \
	क्रम (map = maps__first(maps); map; map = map__next(map))

#घोषणा maps__क्रम_each_entry_safe(maps, map, next) \
	क्रम (map = maps__first(maps), next = map__next(map); map; map = next, next = map__next(map))

काष्ठा maps अणु
	काष्ठा rb_root      entries;
	काष्ठा rw_semaphore lock;
	काष्ठा machine	 *machine;
	काष्ठा map	 *last_search_by_name;
	काष्ठा map	 **maps_by_name;
	refcount_t	 refcnt;
	अचिन्हित पूर्णांक	 nr_maps;
	अचिन्हित पूर्णांक	 nr_maps_allocated;
#अगर_घोषित HAVE_LIBUNWIND_SUPPORT
	व्योम				*addr_space;
	काष्ठा unwind_libunwind_ops	*unwind_libunwind_ops;
#पूर्ण_अगर
पूर्ण;

#घोषणा KMAP_NAME_LEN 256

काष्ठा kmap अणु
	काष्ठा ref_reloc_sym *ref_reloc_sym;
	काष्ठा maps	     *kmaps;
	अक्षर		     name[KMAP_NAME_LEN];
पूर्ण;

काष्ठा maps *maps__new(काष्ठा machine *machine);
व्योम maps__delete(काष्ठा maps *maps);
bool maps__empty(काष्ठा maps *maps);

अटल अंतरभूत काष्ठा maps *maps__get(काष्ठा maps *maps)
अणु
	अगर (maps)
		refcount_inc(&maps->refcnt);
	वापस maps;
पूर्ण

व्योम maps__put(काष्ठा maps *maps);
व्योम maps__init(काष्ठा maps *maps, काष्ठा machine *machine);
व्योम maps__निकास(काष्ठा maps *maps);
पूर्णांक maps__clone(काष्ठा thपढ़ो *thपढ़ो, काष्ठा maps *parent);
माप_प्रकार maps__ख_लिखो(काष्ठा maps *maps, खाता *fp);

व्योम maps__insert(काष्ठा maps *maps, काष्ठा map *map);

व्योम maps__हटाओ(काष्ठा maps *maps, काष्ठा map *map);

काष्ठा symbol *maps__find_symbol(काष्ठा maps *maps, u64 addr, काष्ठा map **mapp);
काष्ठा symbol *maps__find_symbol_by_name(काष्ठा maps *maps, स्थिर अक्षर *name, काष्ठा map **mapp);

काष्ठा addr_map_symbol;

पूर्णांक maps__find_ams(काष्ठा maps *maps, काष्ठा addr_map_symbol *ams);

पूर्णांक maps__fixup_overlappings(काष्ठा maps *maps, काष्ठा map *map, खाता *fp);

काष्ठा map *maps__find_by_name(काष्ठा maps *maps, स्थिर अक्षर *name);

पूर्णांक maps__merge_in(काष्ठा maps *kmaps, काष्ठा map *new_map);

व्योम __maps__sort_by_name(काष्ठा maps *maps);

#पूर्ण_अगर // __PERF_MAPS_H
