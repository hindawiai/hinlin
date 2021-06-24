<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>

#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "../../../util/machine.h"
#समावेश "../../../util/map.h"
#समावेश "../../../util/symbol.h"
#समावेश <linux/प्रकार.स>

#समावेश <symbol/kallsyms.h>

#अगर defined(__x86_64__)

काष्ठा extra_kernel_map_info अणु
	पूर्णांक cnt;
	पूर्णांक max_cnt;
	काष्ठा extra_kernel_map *maps;
	bool get_entry_trampolines;
	u64 entry_trampoline;
पूर्ण;

अटल पूर्णांक add_extra_kernel_map(काष्ठा extra_kernel_map_info *mi, u64 start,
				u64 end, u64 pgoff, स्थिर अक्षर *name)
अणु
	अगर (mi->cnt >= mi->max_cnt) अणु
		व्योम *buf;
		माप_प्रकार sz;

		mi->max_cnt = mi->max_cnt ? mi->max_cnt * 2 : 32;
		sz = माप(काष्ठा extra_kernel_map) * mi->max_cnt;
		buf = पुनः_स्मृति(mi->maps, sz);
		अगर (!buf)
			वापस -1;
		mi->maps = buf;
	पूर्ण

	mi->maps[mi->cnt].start = start;
	mi->maps[mi->cnt].end   = end;
	mi->maps[mi->cnt].pgoff = pgoff;
	strlcpy(mi->maps[mi->cnt].name, name, KMAP_NAME_LEN);

	mi->cnt += 1;

	वापस 0;
पूर्ण

अटल पूर्णांक find_extra_kernel_maps(व्योम *arg, स्थिर अक्षर *name, अक्षर type,
				  u64 start)
अणु
	काष्ठा extra_kernel_map_info *mi = arg;

	अगर (!mi->entry_trampoline && kallsyms2elf_binding(type) == STB_GLOBAL &&
	    !म_भेद(name, "_entry_trampoline")) अणु
		mi->entry_trampoline = start;
		वापस 0;
	पूर्ण

	अगर (is_entry_trampoline(name)) अणु
		u64 end = start + page_size;

		वापस add_extra_kernel_map(mi, start, end, 0, name);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक machine__create_extra_kernel_maps(काष्ठा machine *machine,
				      काष्ठा dso *kernel)
अणु
	काष्ठा extra_kernel_map_info mi = अणु .cnt = 0, पूर्ण;
	अक्षर filename[PATH_MAX];
	पूर्णांक ret;
	पूर्णांक i;

	machine__get_kallsyms_filename(machine, filename, PATH_MAX);

	अगर (symbol__restricted_filename(filename, "/proc/kallsyms"))
		वापस 0;

	ret = kallsyms__parse(filename, &mi, find_extra_kernel_maps);
	अगर (ret)
		जाओ out_मुक्त;

	अगर (!mi.entry_trampoline)
		जाओ out_मुक्त;

	क्रम (i = 0; i < mi.cnt; i++) अणु
		काष्ठा extra_kernel_map *xm = &mi.maps[i];

		xm->pgoff = mi.entry_trampoline;
		ret = machine__create_extra_kernel_map(machine, kernel, xm);
		अगर (ret)
			जाओ out_मुक्त;
	पूर्ण

	machine->trampolines_mapped = mi.cnt;
out_मुक्त:
	मुक्त(mi.maps);
	वापस ret;
पूर्ण

#पूर्ण_अगर
