<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "symbol.h"
#समावेश <निश्चित.स>
#समावेश <त्रुटिसं.स>
#समावेश <पूर्णांकtypes.h>
#समावेश <सीमा.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <uapi/linux/mman.h> /* To get things like MAP_HUGETLB even on older libc headers */
#समावेश "dso.h"
#समावेश "map.h"
#समावेश "map_symbol.h"
#समावेश "thread.h"
#समावेश "vdso.h"
#समावेश "build-id.h"
#समावेश "debug.h"
#समावेश "machine.h"
#समावेश <linux/माला.स>
#समावेश <linux/zभाग.स>
#समावेश "srcline.h"
#समावेश "namespaces.h"
#समावेश "unwind.h"
#समावेश "srccode.h"
#समावेश "ui/ui.h"

अटल व्योम __maps__insert(काष्ठा maps *maps, काष्ठा map *map);

अटल अंतरभूत पूर्णांक is_android_lib(स्थिर अक्षर *filename)
अणु
	वापस strstarts(filename, "/data/app-lib/") ||
	       strstarts(filename, "/system/lib/");
पूर्ण

अटल अंतरभूत bool replace_android_lib(स्थिर अक्षर *filename, अक्षर *newfilename)
अणु
	स्थिर अक्षर *libname;
	अक्षर *app_abi;
	माप_प्रकार app_abi_length, new_length;
	माप_प्रकार lib_length = 0;

	libname  = म_खोजप(filename, '/');
	अगर (libname)
		lib_length = म_माप(libname);

	app_abi = दो_पर्या("APP_ABI");
	अगर (!app_abi)
		वापस false;

	app_abi_length = म_माप(app_abi);

	अगर (strstarts(filename, "/data/app-lib/")) अणु
		अक्षर *apk_path;

		अगर (!app_abi_length)
			वापस false;

		new_length = 7 + app_abi_length + lib_length;

		apk_path = दो_पर्या("APK_PATH");
		अगर (apk_path) अणु
			new_length += म_माप(apk_path) + 1;
			अगर (new_length > PATH_MAX)
				वापस false;
			snम_लिखो(newfilename, new_length,
				 "%s/libs/%s/%s", apk_path, app_abi, libname);
		पूर्ण अन्यथा अणु
			अगर (new_length > PATH_MAX)
				वापस false;
			snम_लिखो(newfilename, new_length,
				 "libs/%s/%s", app_abi, libname);
		पूर्ण
		वापस true;
	पूर्ण

	अगर (strstarts(filename, "/system/lib/")) अणु
		अक्षर *ndk, *app;
		स्थिर अक्षर *arch;
		पूर्णांक ndk_length, app_length;

		ndk = दो_पर्या("NDK_ROOT");
		app = दो_पर्या("APP_PLATFORM");

		अगर (!(ndk && app))
			वापस false;

		ndk_length = म_माप(ndk);
		app_length = म_माप(app);

		अगर (!(ndk_length && app_length && app_abi_length))
			वापस false;

		arch = !म_भेदन(app_abi, "arm", 3) ? "arm" :
		       !म_भेदन(app_abi, "mips", 4) ? "mips" :
		       !म_भेदन(app_abi, "x86", 3) ? "x86" : शून्य;

		अगर (!arch)
			वापस false;

		new_length = 27 + ndk_length +
			     app_length + lib_length
			   + म_माप(arch);

		अगर (new_length > PATH_MAX)
			वापस false;
		snम_लिखो(newfilename, new_length,
			"%.*s/platforms/%.*s/arch-%s/usr/lib/%s",
			ndk_length, ndk, app_length, app, arch, libname);

		वापस true;
	पूर्ण
	वापस false;
पूर्ण

व्योम map__init(काष्ठा map *map, u64 start, u64 end, u64 pgoff, काष्ठा dso *dso)
अणु
	map->start    = start;
	map->end      = end;
	map->pgoff    = pgoff;
	map->reloc    = 0;
	map->dso      = dso__get(dso);
	map->map_ip   = map__map_ip;
	map->unmap_ip = map__unmap_ip;
	RB_CLEAR_NODE(&map->rb_node);
	map->erange_warned = false;
	refcount_set(&map->refcnt, 1);
पूर्ण

काष्ठा map *map__new(काष्ठा machine *machine, u64 start, u64 len,
		     u64 pgoff, काष्ठा dso_id *id,
		     u32 prot, u32 flags, काष्ठा build_id *bid,
		     अक्षर *filename, काष्ठा thपढ़ो *thपढ़ो)
अणु
	काष्ठा map *map = दो_स्मृति(माप(*map));
	काष्ठा nsinfo *nsi = शून्य;
	काष्ठा nsinfo *nnsi;

	अगर (map != शून्य) अणु
		अक्षर newfilename[PATH_MAX];
		काष्ठा dso *dso;
		पूर्णांक anon, no_dso, vdso, android;

		android = is_android_lib(filename);
		anon = is_anon_memory(filename) || flags & MAP_HUGETLB;
		vdso = is_vdso_map(filename);
		no_dso = is_no_dso_memory(filename);
		map->prot = prot;
		map->flags = flags;
		nsi = nsinfo__get(thपढ़ो->nsinfo);

		अगर ((anon || no_dso) && nsi && (prot & PROT_EXEC)) अणु
			snम_लिखो(newfilename, माप(newfilename),
				 "/tmp/perf-%d.map", nsi->pid);
			filename = newfilename;
		पूर्ण

		अगर (android) अणु
			अगर (replace_android_lib(filename, newfilename))
				filename = newfilename;
		पूर्ण

		अगर (vdso) अणु
			/* The vdso maps are always on the host and not the
			 * container.  Ensure that we करोn't use setns to look
			 * them up.
			 */
			nnsi = nsinfo__copy(nsi);
			अगर (nnsi) अणु
				nsinfo__put(nsi);
				nnsi->need_setns = false;
				nsi = nnsi;
			पूर्ण
			pgoff = 0;
			dso = machine__findnew_vdso(machine, thपढ़ो);
		पूर्ण अन्यथा
			dso = machine__findnew_dso_id(machine, filename, id);

		अगर (dso == शून्य)
			जाओ out_delete;

		map__init(map, start, start + len, pgoff, dso);

		अगर (anon || no_dso) अणु
			map->map_ip = map->unmap_ip = identity__map_ip;

			/*
			 * Set memory without DSO as loaded. All map__find_*
			 * functions still वापस शून्य, and we aव्योम the
			 * unnecessary map__load warning.
			 */
			अगर (!(prot & PROT_EXEC))
				dso__set_loaded(dso);
		पूर्ण
		dso->nsinfo = nsi;

		अगर (build_id__is_defined(bid))
			dso__set_build_id(dso, bid);

		dso__put(dso);
	पूर्ण
	वापस map;
out_delete:
	nsinfo__put(nsi);
	मुक्त(map);
	वापस शून्य;
पूर्ण

/*
 * Conकाष्ठाor variant क्रम modules (where we know from /proc/modules where
 * they are loaded) and क्रम vmlinux, where only after we load all the
 * symbols we'll know where it starts and ends.
 */
काष्ठा map *map__new2(u64 start, काष्ठा dso *dso)
अणु
	काष्ठा map *map = सुस्मृति(1, (माप(*map) +
				     (dso->kernel ? माप(काष्ठा kmap) : 0)));
	अगर (map != शून्य) अणु
		/*
		 * ->end will be filled after we load all the symbols
		 */
		map__init(map, start, 0, 0, dso);
	पूर्ण

	वापस map;
पूर्ण

bool __map__is_kernel(स्थिर काष्ठा map *map)
अणु
	अगर (!map->dso->kernel)
		वापस false;
	वापस machine__kernel_map(map__kmaps((काष्ठा map *)map)->machine) == map;
पूर्ण

bool __map__is_extra_kernel_map(स्थिर काष्ठा map *map)
अणु
	काष्ठा kmap *kmap = __map__kmap((काष्ठा map *)map);

	वापस kmap && kmap->name[0];
पूर्ण

bool __map__is_bpf_prog(स्थिर काष्ठा map *map)
अणु
	स्थिर अक्षर *name;

	अगर (map->dso->binary_type == DSO_BINARY_TYPE__BPF_PROG_INFO)
		वापस true;

	/*
	 * If PERF_RECORD_BPF_EVENT is not included, the dso will not have
	 * type of DSO_BINARY_TYPE__BPF_PROG_INFO. In such हालs, we can
	 * guess the type based on name.
	 */
	name = map->dso->लघु_name;
	वापस name && (म_माला(name, "bpf_prog_") == name);
पूर्ण

bool __map__is_bpf_image(स्थिर काष्ठा map *map)
अणु
	स्थिर अक्षर *name;

	अगर (map->dso->binary_type == DSO_BINARY_TYPE__BPF_IMAGE)
		वापस true;

	/*
	 * If PERF_RECORD_KSYMBOL is not included, the dso will not have
	 * type of DSO_BINARY_TYPE__BPF_IMAGE. In such हालs, we can
	 * guess the type based on name.
	 */
	name = map->dso->लघु_name;
	वापस name && is_bpf_image(name);
पूर्ण

bool __map__is_ool(स्थिर काष्ठा map *map)
अणु
	वापस map->dso && map->dso->binary_type == DSO_BINARY_TYPE__OOL;
पूर्ण

bool map__has_symbols(स्थिर काष्ठा map *map)
अणु
	वापस dso__has_symbols(map->dso);
पूर्ण

अटल व्योम map__निकास(काष्ठा map *map)
अणु
	BUG_ON(refcount_पढ़ो(&map->refcnt) != 0);
	dso__zput(map->dso);
पूर्ण

व्योम map__delete(काष्ठा map *map)
अणु
	map__निकास(map);
	मुक्त(map);
पूर्ण

व्योम map__put(काष्ठा map *map)
अणु
	अगर (map && refcount_dec_and_test(&map->refcnt))
		map__delete(map);
पूर्ण

व्योम map__fixup_start(काष्ठा map *map)
अणु
	काष्ठा rb_root_cached *symbols = &map->dso->symbols;
	काष्ठा rb_node *nd = rb_first_cached(symbols);
	अगर (nd != शून्य) अणु
		काष्ठा symbol *sym = rb_entry(nd, काष्ठा symbol, rb_node);
		map->start = sym->start;
	पूर्ण
पूर्ण

व्योम map__fixup_end(काष्ठा map *map)
अणु
	काष्ठा rb_root_cached *symbols = &map->dso->symbols;
	काष्ठा rb_node *nd = rb_last(&symbols->rb_root);
	अगर (nd != शून्य) अणु
		काष्ठा symbol *sym = rb_entry(nd, काष्ठा symbol, rb_node);
		map->end = sym->end;
	पूर्ण
पूर्ण

#घोषणा DSO__DELETED "(deleted)"

पूर्णांक map__load(काष्ठा map *map)
अणु
	स्थिर अक्षर *name = map->dso->दीर्घ_name;
	पूर्णांक nr;

	अगर (dso__loaded(map->dso))
		वापस 0;

	nr = dso__load(map->dso, map);
	अगर (nr < 0) अणु
		अगर (map->dso->has_build_id) अणु
			अक्षर sbuild_id[SBUILD_ID_SIZE];

			build_id__प्र_लिखो(&map->dso->bid, sbuild_id);
			pr_debug("%s with build id %s not found", name, sbuild_id);
		पूर्ण अन्यथा
			pr_debug("Failed to open %s", name);

		pr_debug(", continuing without symbols\n");
		वापस -1;
	पूर्ण अन्यथा अगर (nr == 0) अणु
#अगर_घोषित HAVE_LIBELF_SUPPORT
		स्थिर माप_प्रकार len = म_माप(name);
		स्थिर माप_प्रकार real_len = len - माप(DSO__DELETED);

		अगर (len > माप(DSO__DELETED) &&
		    म_भेद(name + real_len + 1, DSO__DELETED) == 0) अणु
			pr_debug("%.*s was updated (is prelink enabled?). "
				"Restart the long running apps that use it!\n",
				   (पूर्णांक)real_len, name);
		पूर्ण अन्यथा अणु
			pr_debug("no symbols found in %s, maybe install a debug package?\n", name);
		पूर्ण
#पूर्ण_अगर
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

काष्ठा symbol *map__find_symbol(काष्ठा map *map, u64 addr)
अणु
	अगर (map__load(map) < 0)
		वापस शून्य;

	वापस dso__find_symbol(map->dso, addr);
पूर्ण

काष्ठा symbol *map__find_symbol_by_name(काष्ठा map *map, स्थिर अक्षर *name)
अणु
	अगर (map__load(map) < 0)
		वापस शून्य;

	अगर (!dso__sorted_by_name(map->dso))
		dso__sort_by_name(map->dso);

	वापस dso__find_symbol_by_name(map->dso, name);
पूर्ण

काष्ठा map *map__clone(काष्ठा map *from)
अणु
	माप_प्रकार size = माप(काष्ठा map);
	काष्ठा map *map;

	अगर (from->dso && from->dso->kernel)
		size += माप(काष्ठा kmap);

	map = memdup(from, size);
	अगर (map != शून्य) अणु
		refcount_set(&map->refcnt, 1);
		RB_CLEAR_NODE(&map->rb_node);
		dso__get(map->dso);
	पूर्ण

	वापस map;
पूर्ण

माप_प्रकार map__ख_लिखो(काष्ठा map *map, खाता *fp)
अणु
	वापस ख_लिखो(fp, " %" PRIx64 "-%" PRIx64 " %" PRIx64 " %s\n",
		       map->start, map->end, map->pgoff, map->dso->name);
पूर्ण

माप_प्रकार map__ख_लिखो_dsoname(काष्ठा map *map, खाता *fp)
अणु
	अक्षर buf[symbol_conf.pad_output_len_dso + 1];
	स्थिर अक्षर *dsoname = "[unknown]";

	अगर (map && map->dso) अणु
		अगर (symbol_conf.show_kernel_path && map->dso->दीर्घ_name)
			dsoname = map->dso->दीर्घ_name;
		अन्यथा
			dsoname = map->dso->name;
	पूर्ण

	अगर (symbol_conf.pad_output_len_dso) अणु
		scnम_लिखो_pad(buf, symbol_conf.pad_output_len_dso, "%s", dsoname);
		dsoname = buf;
	पूर्ण

	वापस ख_लिखो(fp, "%s", dsoname);
पूर्ण

अक्षर *map__srcline(काष्ठा map *map, u64 addr, काष्ठा symbol *sym)
अणु
	अगर (map == शून्य)
		वापस SRCLINE_UNKNOWN;
	वापस get_srcline(map->dso, map__rip_2objdump(map, addr), sym, true, true, addr);
पूर्ण

पूर्णांक map__ख_लिखो_srcline(काष्ठा map *map, u64 addr, स्थिर अक्षर *prefix,
			 खाता *fp)
अणु
	पूर्णांक ret = 0;

	अगर (map && map->dso) अणु
		अक्षर *srcline = map__srcline(map, addr, शून्य);
		अगर (म_भेदन(srcline, SRCLINE_UNKNOWN, म_माप(SRCLINE_UNKNOWN)) != 0)
			ret = ख_लिखो(fp, "%s%s", prefix, srcline);
		मुक्त_srcline(srcline);
	पूर्ण
	वापस ret;
पूर्ण

व्योम srccode_state_मुक्त(काष्ठा srccode_state *state)
अणु
	zमुक्त(&state->srcfile);
	state->line = 0;
पूर्ण

/**
 * map__rip_2objdump - convert symbol start address to objdump address.
 * @map: memory map
 * @rip: symbol start address
 *
 * objdump wants/reports असलolute IPs क्रम ET_EXEC, and RIPs क्रम ET_DYN.
 * map->dso->adjust_symbols==1 क्रम ET_EXEC-like हालs except ET_REL which is
 * relative to section start.
 *
 * Return: Address suitable क्रम passing to "objdump --start-address="
 */
u64 map__rip_2objdump(काष्ठा map *map, u64 rip)
अणु
	काष्ठा kmap *kmap = __map__kmap(map);

	/*
	 * vmlinux करोes not have program headers क्रम PTI entry trampolines and
	 * kcore may not either. However the trampoline object code is on the
	 * मुख्य kernel map, so just use that instead.
	 */
	अगर (kmap && is_entry_trampoline(kmap->name) && kmap->kmaps && kmap->kmaps->machine) अणु
		काष्ठा map *kernel_map = machine__kernel_map(kmap->kmaps->machine);

		अगर (kernel_map)
			map = kernel_map;
	पूर्ण

	अगर (!map->dso->adjust_symbols)
		वापस rip;

	अगर (map->dso->rel)
		वापस rip - map->pgoff;

	/*
	 * kernel modules also have DSO_TYPE_USER in dso->kernel,
	 * but all kernel modules are ET_REL, so won't get here.
	 */
	अगर (map->dso->kernel == DSO_SPACE__USER)
		वापस rip + map->dso->text_offset;

	वापस map->unmap_ip(map, rip) - map->reloc;
पूर्ण

/**
 * map__objdump_2mem - convert objdump address to a memory address.
 * @map: memory map
 * @ip: objdump address
 *
 * Closely related to map__rip_2objdump(), this function takes an address from
 * objdump and converts it to a memory address.  Note this assumes that @map
 * contains the address.  To be sure the result is valid, check it क्रमwards
 * e.g. map__rip_2objdump(map->map_ip(map, map__objdump_2mem(map, ip))) == ip
 *
 * Return: Memory address.
 */
u64 map__objdump_2mem(काष्ठा map *map, u64 ip)
अणु
	अगर (!map->dso->adjust_symbols)
		वापस map->unmap_ip(map, ip);

	अगर (map->dso->rel)
		वापस map->unmap_ip(map, ip + map->pgoff);

	/*
	 * kernel modules also have DSO_TYPE_USER in dso->kernel,
	 * but all kernel modules are ET_REL, so won't get here.
	 */
	अगर (map->dso->kernel == DSO_SPACE__USER)
		वापस map->unmap_ip(map, ip - map->dso->text_offset);

	वापस ip + map->reloc;
पूर्ण

व्योम maps__init(काष्ठा maps *maps, काष्ठा machine *machine)
अणु
	maps->entries = RB_ROOT;
	init_rwsem(&maps->lock);
	maps->machine = machine;
	maps->last_search_by_name = शून्य;
	maps->nr_maps = 0;
	maps->maps_by_name = शून्य;
	refcount_set(&maps->refcnt, 1);
पूर्ण

अटल व्योम __maps__मुक्त_maps_by_name(काष्ठा maps *maps)
अणु
	/*
	 * Free everything to try to करो it from the rbtree in the next search
	 */
	zमुक्त(&maps->maps_by_name);
	maps->nr_maps_allocated = 0;
पूर्ण

व्योम maps__insert(काष्ठा maps *maps, काष्ठा map *map)
अणु
	करोwn_ग_लिखो(&maps->lock);
	__maps__insert(maps, map);
	++maps->nr_maps;

	अगर (map->dso && map->dso->kernel) अणु
		काष्ठा kmap *kmap = map__kmap(map);

		अगर (kmap)
			kmap->kmaps = maps;
		अन्यथा
			pr_err("Internal error: kernel dso with non kernel map\n");
	पूर्ण


	/*
	 * If we alपढ़ोy perक्रमmed some search by name, then we need to add the just
	 * inserted map and resort.
	 */
	अगर (maps->maps_by_name) अणु
		अगर (maps->nr_maps > maps->nr_maps_allocated) अणु
			पूर्णांक nr_allocate = maps->nr_maps * 2;
			काष्ठा map **maps_by_name = पुनः_स्मृति(maps->maps_by_name, nr_allocate * माप(map));

			अगर (maps_by_name == शून्य) अणु
				__maps__मुक्त_maps_by_name(maps);
				up_ग_लिखो(&maps->lock);
				वापस;
			पूर्ण

			maps->maps_by_name = maps_by_name;
			maps->nr_maps_allocated = nr_allocate;
		पूर्ण
		maps->maps_by_name[maps->nr_maps - 1] = map;
		__maps__sort_by_name(maps);
	पूर्ण
	up_ग_लिखो(&maps->lock);
पूर्ण

अटल व्योम __maps__हटाओ(काष्ठा maps *maps, काष्ठा map *map)
अणु
	rb_erase_init(&map->rb_node, &maps->entries);
	map__put(map);
पूर्ण

व्योम maps__हटाओ(काष्ठा maps *maps, काष्ठा map *map)
अणु
	करोwn_ग_लिखो(&maps->lock);
	अगर (maps->last_search_by_name == map)
		maps->last_search_by_name = शून्य;

	__maps__हटाओ(maps, map);
	--maps->nr_maps;
	अगर (maps->maps_by_name)
		__maps__मुक्त_maps_by_name(maps);
	up_ग_लिखो(&maps->lock);
पूर्ण

अटल व्योम __maps__purge(काष्ठा maps *maps)
अणु
	काष्ठा map *pos, *next;

	maps__क्रम_each_entry_safe(maps, pos, next) अणु
		rb_erase_init(&pos->rb_node,  &maps->entries);
		map__put(pos);
	पूर्ण
पूर्ण

व्योम maps__निकास(काष्ठा maps *maps)
अणु
	करोwn_ग_लिखो(&maps->lock);
	__maps__purge(maps);
	up_ग_लिखो(&maps->lock);
पूर्ण

bool maps__empty(काष्ठा maps *maps)
अणु
	वापस !maps__first(maps);
पूर्ण

काष्ठा maps *maps__new(काष्ठा machine *machine)
अणु
	काष्ठा maps *maps = zalloc(माप(*maps));

	अगर (maps != शून्य)
		maps__init(maps, machine);

	वापस maps;
पूर्ण

व्योम maps__delete(काष्ठा maps *maps)
अणु
	maps__निकास(maps);
	unwind__finish_access(maps);
	मुक्त(maps);
पूर्ण

व्योम maps__put(काष्ठा maps *maps)
अणु
	अगर (maps && refcount_dec_and_test(&maps->refcnt))
		maps__delete(maps);
पूर्ण

काष्ठा symbol *maps__find_symbol(काष्ठा maps *maps, u64 addr, काष्ठा map **mapp)
अणु
	काष्ठा map *map = maps__find(maps, addr);

	/* Ensure map is loaded beक्रमe using map->map_ip */
	अगर (map != शून्य && map__load(map) >= 0) अणु
		अगर (mapp != शून्य)
			*mapp = map;
		वापस map__find_symbol(map, map->map_ip(map, addr));
	पूर्ण

	वापस शून्य;
पूर्ण

अटल bool map__contains_symbol(काष्ठा map *map, काष्ठा symbol *sym)
अणु
	u64 ip = map->unmap_ip(map, sym->start);

	वापस ip >= map->start && ip < map->end;
पूर्ण

काष्ठा symbol *maps__find_symbol_by_name(काष्ठा maps *maps, स्थिर अक्षर *name, काष्ठा map **mapp)
अणु
	काष्ठा symbol *sym;
	काष्ठा map *pos;

	करोwn_पढ़ो(&maps->lock);

	maps__क्रम_each_entry(maps, pos) अणु
		sym = map__find_symbol_by_name(pos, name);

		अगर (sym == शून्य)
			जारी;
		अगर (!map__contains_symbol(pos, sym)) अणु
			sym = शून्य;
			जारी;
		पूर्ण
		अगर (mapp != शून्य)
			*mapp = pos;
		जाओ out;
	पूर्ण

	sym = शून्य;
out:
	up_पढ़ो(&maps->lock);
	वापस sym;
पूर्ण

पूर्णांक maps__find_ams(काष्ठा maps *maps, काष्ठा addr_map_symbol *ams)
अणु
	अगर (ams->addr < ams->ms.map->start || ams->addr >= ams->ms.map->end) अणु
		अगर (maps == शून्य)
			वापस -1;
		ams->ms.map = maps__find(maps, ams->addr);
		अगर (ams->ms.map == शून्य)
			वापस -1;
	पूर्ण

	ams->al_addr = ams->ms.map->map_ip(ams->ms.map, ams->addr);
	ams->ms.sym = map__find_symbol(ams->ms.map, ams->al_addr);

	वापस ams->ms.sym ? 0 : -1;
पूर्ण

माप_प्रकार maps__ख_लिखो(काष्ठा maps *maps, खाता *fp)
अणु
	माप_प्रकार prपूर्णांकed = 0;
	काष्ठा map *pos;

	करोwn_पढ़ो(&maps->lock);

	maps__क्रम_each_entry(maps, pos) अणु
		prपूर्णांकed += ख_लिखो(fp, "Map:");
		prपूर्णांकed += map__ख_लिखो(pos, fp);
		अगर (verbose > 2) अणु
			prपूर्णांकed += dso__ख_लिखो(pos->dso, fp);
			prपूर्णांकed += ख_लिखो(fp, "--\n");
		पूर्ण
	पूर्ण

	up_पढ़ो(&maps->lock);

	वापस prपूर्णांकed;
पूर्ण

पूर्णांक maps__fixup_overlappings(काष्ठा maps *maps, काष्ठा map *map, खाता *fp)
अणु
	काष्ठा rb_root *root;
	काष्ठा rb_node *next, *first;
	पूर्णांक err = 0;

	करोwn_ग_लिखो(&maps->lock);

	root = &maps->entries;

	/*
	 * Find first map where end > map->start.
	 * Same as find_vma() in kernel.
	 */
	next = root->rb_node;
	first = शून्य;
	जबतक (next) अणु
		काष्ठा map *pos = rb_entry(next, काष्ठा map, rb_node);

		अगर (pos->end > map->start) अणु
			first = next;
			अगर (pos->start <= map->start)
				अवरोध;
			next = next->rb_left;
		पूर्ण अन्यथा
			next = next->rb_right;
	पूर्ण

	next = first;
	जबतक (next) अणु
		काष्ठा map *pos = rb_entry(next, काष्ठा map, rb_node);
		next = rb_next(&pos->rb_node);

		/*
		 * Stop अगर current map starts after map->end.
		 * Maps are ordered by start: next will not overlap क्रम sure.
		 */
		अगर (pos->start >= map->end)
			अवरोध;

		अगर (verbose >= 2) अणु

			अगर (use_browser) अणु
				pr_debug("overlapping maps in %s (disable tui for more info)\n",
					   map->dso->name);
			पूर्ण अन्यथा अणु
				ख_माला_दो("overlapping maps:\n", fp);
				map__ख_लिखो(map, fp);
				map__ख_लिखो(pos, fp);
			पूर्ण
		पूर्ण

		rb_erase_init(&pos->rb_node, root);
		/*
		 * Now check अगर we need to create new maps क्रम areas not
		 * overlapped by the new map:
		 */
		अगर (map->start > pos->start) अणु
			काष्ठा map *beक्रमe = map__clone(pos);

			अगर (beक्रमe == शून्य) अणु
				err = -ENOMEM;
				जाओ put_map;
			पूर्ण

			beक्रमe->end = map->start;
			__maps__insert(maps, beक्रमe);
			अगर (verbose >= 2 && !use_browser)
				map__ख_लिखो(beक्रमe, fp);
			map__put(beक्रमe);
		पूर्ण

		अगर (map->end < pos->end) अणु
			काष्ठा map *after = map__clone(pos);

			अगर (after == शून्य) अणु
				err = -ENOMEM;
				जाओ put_map;
			पूर्ण

			after->start = map->end;
			after->pgoff += map->end - pos->start;
			निश्चित(pos->map_ip(pos, map->end) == after->map_ip(after, map->end));
			__maps__insert(maps, after);
			अगर (verbose >= 2 && !use_browser)
				map__ख_लिखो(after, fp);
			map__put(after);
		पूर्ण
put_map:
		map__put(pos);

		अगर (err)
			जाओ out;
	पूर्ण

	err = 0;
out:
	up_ग_लिखो(&maps->lock);
	वापस err;
पूर्ण

/*
 * XXX This should not really _copy_ te maps, but refcount them.
 */
पूर्णांक maps__clone(काष्ठा thपढ़ो *thपढ़ो, काष्ठा maps *parent)
अणु
	काष्ठा maps *maps = thपढ़ो->maps;
	पूर्णांक err;
	काष्ठा map *map;

	करोwn_पढ़ो(&parent->lock);

	maps__क्रम_each_entry(parent, map) अणु
		काष्ठा map *new = map__clone(map);

		अगर (new == शून्य) अणु
			err = -ENOMEM;
			जाओ out_unlock;
		पूर्ण

		err = unwind__prepare_access(maps, new, शून्य);
		अगर (err)
			जाओ out_unlock;

		maps__insert(maps, new);
		map__put(new);
	पूर्ण

	err = 0;
out_unlock:
	up_पढ़ो(&parent->lock);
	वापस err;
पूर्ण

अटल व्योम __maps__insert(काष्ठा maps *maps, काष्ठा map *map)
अणु
	काष्ठा rb_node **p = &maps->entries.rb_node;
	काष्ठा rb_node *parent = शून्य;
	स्थिर u64 ip = map->start;
	काष्ठा map *m;

	जबतक (*p != शून्य) अणु
		parent = *p;
		m = rb_entry(parent, काष्ठा map, rb_node);
		अगर (ip < m->start)
			p = &(*p)->rb_left;
		अन्यथा
			p = &(*p)->rb_right;
	पूर्ण

	rb_link_node(&map->rb_node, parent, p);
	rb_insert_color(&map->rb_node, &maps->entries);
	map__get(map);
पूर्ण

काष्ठा map *maps__find(काष्ठा maps *maps, u64 ip)
अणु
	काष्ठा rb_node *p;
	काष्ठा map *m;

	करोwn_पढ़ो(&maps->lock);

	p = maps->entries.rb_node;
	जबतक (p != शून्य) अणु
		m = rb_entry(p, काष्ठा map, rb_node);
		अगर (ip < m->start)
			p = p->rb_left;
		अन्यथा अगर (ip >= m->end)
			p = p->rb_right;
		अन्यथा
			जाओ out;
	पूर्ण

	m = शून्य;
out:
	up_पढ़ो(&maps->lock);
	वापस m;
पूर्ण

काष्ठा map *maps__first(काष्ठा maps *maps)
अणु
	काष्ठा rb_node *first = rb_first(&maps->entries);

	अगर (first)
		वापस rb_entry(first, काष्ठा map, rb_node);
	वापस शून्य;
पूर्ण

अटल काष्ठा map *__map__next(काष्ठा map *map)
अणु
	काष्ठा rb_node *next = rb_next(&map->rb_node);

	अगर (next)
		वापस rb_entry(next, काष्ठा map, rb_node);
	वापस शून्य;
पूर्ण

काष्ठा map *map__next(काष्ठा map *map)
अणु
	वापस map ? __map__next(map) : शून्य;
पूर्ण

काष्ठा kmap *__map__kmap(काष्ठा map *map)
अणु
	अगर (!map->dso || !map->dso->kernel)
		वापस शून्य;
	वापस (काष्ठा kmap *)(map + 1);
पूर्ण

काष्ठा kmap *map__kmap(काष्ठा map *map)
अणु
	काष्ठा kmap *kmap = __map__kmap(map);

	अगर (!kmap)
		pr_err("Internal error: map__kmap with a non-kernel map\n");
	वापस kmap;
पूर्ण

काष्ठा maps *map__kmaps(काष्ठा map *map)
अणु
	काष्ठा kmap *kmap = map__kmap(map);

	अगर (!kmap || !kmap->kmaps) अणु
		pr_err("Internal error: map__kmaps with a non-kernel map\n");
		वापस शून्य;
	पूर्ण
	वापस kmap->kmaps;
पूर्ण
