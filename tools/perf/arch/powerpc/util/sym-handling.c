<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2015 Naveen N. Rao, IBM Corporation
 */

#समावेश "dso.h"
#समावेश "symbol.h"
#समावेश "map.h"
#समावेश "probe-event.h"
#समावेश "probe-file.h"

पूर्णांक arch__choose_best_symbol(काष्ठा symbol *syma,
			     काष्ठा symbol *symb __maybe_unused)
अणु
	अक्षर *sym = syma->name;

#अगर !defined(_CALL_ELF) || _CALL_ELF != 2
	/* Skip over any initial करोt */
	अगर (*sym == '.')
		sym++;
#पूर्ण_अगर

	/* Aव्योम "SyS" kernel syscall aliases */
	अगर (म_माप(sym) >= 3 && !म_भेदन(sym, "SyS", 3))
		वापस SYMBOL_B;
	अगर (म_माप(sym) >= 10 && !म_भेदन(sym, "compat_SyS", 10))
		वापस SYMBOL_B;

	वापस SYMBOL_A;
पूर्ण

#अगर !defined(_CALL_ELF) || _CALL_ELF != 2
/* Allow matching against करोt variants */
पूर्णांक arch__compare_symbol_names(स्थिर अक्षर *namea, स्थिर अक्षर *nameb)
अणु
	/* Skip over initial करोt */
	अगर (*namea == '.')
		namea++;
	अगर (*nameb == '.')
		nameb++;

	वापस म_भेद(namea, nameb);
पूर्ण

पूर्णांक arch__compare_symbol_names_n(स्थिर अक्षर *namea, स्थिर अक्षर *nameb,
				 अचिन्हित पूर्णांक n)
अणु
	/* Skip over initial करोt */
	अगर (*namea == '.')
		namea++;
	अगर (*nameb == '.')
		nameb++;

	वापस म_भेदन(namea, nameb, n);
पूर्ण

स्थिर अक्षर *arch__normalize_symbol_name(स्थिर अक्षर *name)
अणु
	/* Skip over initial करोt */
	अगर (name && *name == '.')
		name++;
	वापस name;
पूर्ण
#पूर्ण_अगर

#अगर defined(_CALL_ELF) && _CALL_ELF == 2

#अगर_घोषित HAVE_LIBELF_SUPPORT
व्योम arch__sym_update(काष्ठा symbol *s, GElf_Sym *sym)
अणु
	s->arch_sym = sym->st_other;
पूर्ण
#पूर्ण_अगर

#घोषणा PPC64LE_LEP_OFFSET	8

व्योम arch__fix_tev_from_maps(काष्ठा perf_probe_event *pev,
			     काष्ठा probe_trace_event *tev, काष्ठा map *map,
			     काष्ठा symbol *sym)
अणु
	पूर्णांक lep_offset;

	/*
	 * When probing at a function entry poपूर्णांक, we normally always want the
	 * LEP since that catches calls to the function through both the GEP and
	 * the LEP. Hence, we would like to probe at an offset of 8 bytes अगर
	 * the user only specअगरied the function entry.
	 *
	 * However, अगर the user specअगरies an offset, we fall back to using the
	 * GEP since all userspace applications (objdump/पढ़ोelf) show function
	 * disassembly with offsets from the GEP.
	 */
	अगर (pev->poपूर्णांक.offset || !map || !sym)
		वापस;

	/* For kretprobes, add an offset only अगर the kernel supports it */
	अगर (!pev->uprobes && pev->poपूर्णांक.retprobe) अणु
#अगर_घोषित HAVE_LIBELF_SUPPORT
		अगर (!kretprobe_offset_is_supported())
#पूर्ण_अगर
			वापस;
	पूर्ण

	lep_offset = PPC64_LOCAL_ENTRY_OFFSET(sym->arch_sym);

	अगर (map->dso->symtab_type == DSO_BINARY_TYPE__KALLSYMS)
		tev->poपूर्णांक.offset += PPC64LE_LEP_OFFSET;
	अन्यथा अगर (lep_offset) अणु
		अगर (pev->uprobes)
			tev->poपूर्णांक.address += lep_offset;
		अन्यथा
			tev->poपूर्णांक.offset += lep_offset;
	पूर्ण
पूर्ण

#अगर_घोषित HAVE_LIBELF_SUPPORT
व्योम arch__post_process_probe_trace_events(काष्ठा perf_probe_event *pev,
					   पूर्णांक ntevs)
अणु
	काष्ठा probe_trace_event *tev;
	काष्ठा map *map;
	काष्ठा symbol *sym = शून्य;
	काष्ठा rb_node *पंचांगp;
	पूर्णांक i = 0;

	map = get_target_map(pev->target, pev->nsi, pev->uprobes);
	अगर (!map || map__load(map) < 0)
		वापस;

	क्रम (i = 0; i < ntevs; i++) अणु
		tev = &pev->tevs[i];
		map__क्रम_each_symbol(map, sym, पंचांगp) अणु
			अगर (map->unmap_ip(map, sym->start) == tev->poपूर्णांक.address) अणु
				arch__fix_tev_from_maps(pev, tev, map, sym);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर /* HAVE_LIBELF_SUPPORT */

#पूर्ण_अगर
