<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * probe-event.c : perf-probe definition to probe_events क्रमmat converter
 *
 * Written by Masami Hiramatsu <mhiramat@redhat.com>
 */

#समावेश <पूर्णांकtypes.h>
#समावेश <sys/utsname.h>
#समावेश <sys/types.h>
#समावेश <sys/स्थिति.स>
#समावेश <fcntl.h>
#समावेश <त्रुटिसं.स>
#समावेश <मानकपन.स>
#समावेश <unistd.h>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <मानकतर्क.स>
#समावेश <सीमा.स>
#समावेश <elf.h>

#समावेश "build-id.h"
#समावेश "event.h"
#समावेश "namespaces.h"
#समावेश "strlist.h"
#समावेश "strfilter.h"
#समावेश "debug.h"
#समावेश "dso.h"
#समावेश "color.h"
#समावेश "map.h"
#समावेश "maps.h"
#समावेश "symbol.h"
#समावेश <api/fs/fs.h>
#समावेश "trace-event.h"	/* For __maybe_unused */
#समावेश "probe-event.h"
#समावेश "probe-finder.h"
#समावेश "probe-file.h"
#समावेश "session.h"
#समावेश "string2.h"
#समावेश "strbuf.h"

#समावेश <subcmd/pager.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/zभाग.स>

#अगर_घोषित HAVE_DEBUGINFOD_SUPPORT
#समावेश <elfutils/debuginfod.h>
#पूर्ण_अगर

#घोषणा PERFPROBE_GROUP "probe"

bool probe_event_dry_run;	/* Dry run flag */
काष्ठा probe_conf probe_conf = अणु .magic_num = DEFAULT_PROBE_MAGIC_NUM पूर्ण;

#घोषणा semantic_error(msg ...) pr_err("Semantic error :" msg)

पूर्णांक e_snम_लिखो(अक्षर *str, माप_प्रकार size, स्थिर अक्षर *क्रमmat, ...)
अणु
	पूर्णांक ret;
	बहु_सूची ap;
	बहु_शुरू(ap, क्रमmat);
	ret = vsnम_लिखो(str, size, क्रमmat, ap);
	बहु_पूर्ण(ap);
	अगर (ret >= (पूर्णांक)size)
		ret = -E2BIG;
	वापस ret;
पूर्ण

अटल काष्ठा machine *host_machine;

/* Initialize symbol maps and path of vmlinux/modules */
पूर्णांक init_probe_symbol_maps(bool user_only)
अणु
	पूर्णांक ret;

	symbol_conf.sort_by_name = true;
	symbol_conf.allow_aliases = true;
	ret = symbol__init(शून्य);
	अगर (ret < 0) अणु
		pr_debug("Failed to init symbol map.\n");
		जाओ out;
	पूर्ण

	अगर (host_machine || user_only)	/* alपढ़ोy initialized */
		वापस 0;

	अगर (symbol_conf.vmlinux_name)
		pr_debug("Use vmlinux: %s\n", symbol_conf.vmlinux_name);

	host_machine = machine__new_host();
	अगर (!host_machine) अणु
		pr_debug("machine__new_host() failed.\n");
		symbol__निकास();
		ret = -1;
	पूर्ण
out:
	अगर (ret < 0)
		pr_warning("Failed to init vmlinux path.\n");
	वापस ret;
पूर्ण

व्योम निकास_probe_symbol_maps(व्योम)
अणु
	machine__delete(host_machine);
	host_machine = शून्य;
	symbol__निकास();
पूर्ण

अटल काष्ठा ref_reloc_sym *kernel_get_ref_reloc_sym(काष्ठा map **pmap)
अणु
	/* kmap->ref_reloc_sym should be set अगर host_machine is initialized */
	काष्ठा kmap *kmap;
	काष्ठा map *map = machine__kernel_map(host_machine);

	अगर (map__load(map) < 0)
		वापस शून्य;

	kmap = map__kmap(map);
	अगर (!kmap)
		वापस शून्य;

	अगर (pmap)
		*pmap = map;

	वापस kmap->ref_reloc_sym;
पूर्ण

अटल पूर्णांक kernel_get_symbol_address_by_name(स्थिर अक्षर *name, u64 *addr,
					     bool reloc, bool reladdr)
अणु
	काष्ठा ref_reloc_sym *reloc_sym;
	काष्ठा symbol *sym;
	काष्ठा map *map;

	/* ref_reloc_sym is just a label. Need a special fix*/
	reloc_sym = kernel_get_ref_reloc_sym(&map);
	अगर (reloc_sym && म_भेद(name, reloc_sym->name) == 0)
		*addr = (!map->reloc || reloc) ? reloc_sym->addr :
			reloc_sym->unrelocated_addr;
	अन्यथा अणु
		sym = machine__find_kernel_symbol_by_name(host_machine, name, &map);
		अगर (!sym)
			वापस -ENOENT;
		*addr = map->unmap_ip(map, sym->start) -
			((reloc) ? 0 : map->reloc) -
			((reladdr) ? map->start : 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा map *kernel_get_module_map(स्थिर अक्षर *module)
अणु
	काष्ठा maps *maps = machine__kernel_maps(host_machine);
	काष्ठा map *pos;

	/* A file path -- this is an offline module */
	अगर (module && म_अक्षर(module, '/'))
		वापस dso__new_map(module);

	अगर (!module) अणु
		pos = machine__kernel_map(host_machine);
		वापस map__get(pos);
	पूर्ण

	maps__क्रम_each_entry(maps, pos) अणु
		/* लघु_name is "[module]" */
		अगर (म_भेदन(pos->dso->लघु_name + 1, module,
			    pos->dso->लघु_name_len - 2) == 0 &&
		    module[pos->dso->लघु_name_len - 2] == '\0') अणु
			वापस map__get(pos);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा map *get_target_map(स्थिर अक्षर *target, काष्ठा nsinfo *nsi, bool user)
अणु
	/* Init maps of given executable or kernel */
	अगर (user) अणु
		काष्ठा map *map;

		map = dso__new_map(target);
		अगर (map && map->dso)
			map->dso->nsinfo = nsinfo__get(nsi);
		वापस map;
	पूर्ण अन्यथा अणु
		वापस kernel_get_module_map(target);
	पूर्ण
पूर्ण

अटल पूर्णांक convert_exec_to_group(स्थिर अक्षर *exec, अक्षर **result)
अणु
	अक्षर *ptr1, *ptr2, *exec_copy;
	अक्षर buf[64];
	पूर्णांक ret;

	exec_copy = strdup(exec);
	अगर (!exec_copy)
		वापस -ENOMEM;

	ptr1 = basename(exec_copy);
	अगर (!ptr1) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (ptr2 = ptr1; *ptr2 != '\0'; ptr2++) अणु
		अगर (!है_अक्षर_अंक(*ptr2) && *ptr2 != '_') अणु
			*ptr2 = '\0';
			अवरोध;
		पूर्ण
	पूर्ण

	ret = e_snम_लिखो(buf, 64, "%s_%s", PERFPROBE_GROUP, ptr1);
	अगर (ret < 0)
		जाओ out;

	*result = strdup(buf);
	ret = *result ? 0 : -ENOMEM;

out:
	मुक्त(exec_copy);
	वापस ret;
पूर्ण

अटल व्योम clear_perf_probe_poपूर्णांक(काष्ठा perf_probe_poपूर्णांक *pp)
अणु
	zमुक्त(&pp->file);
	zमुक्त(&pp->function);
	zमुक्त(&pp->lazy_line);
पूर्ण

अटल व्योम clear_probe_trace_events(काष्ठा probe_trace_event *tevs, पूर्णांक ntevs)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ntevs; i++)
		clear_probe_trace_event(tevs + i);
पूर्ण

अटल bool kprobe_blacklist__listed(अचिन्हित दीर्घ address);
अटल bool kprobe_warn_out_range(स्थिर अक्षर *symbol, अचिन्हित दीर्घ address)
अणु
	काष्ठा map *map;
	bool ret = false;

	map = kernel_get_module_map(शून्य);
	अगर (map) अणु
		ret = address <= map->start || map->end < address;
		अगर (ret)
			pr_warning("%s is out of .text, skip it.\n", symbol);
		map__put(map);
	पूर्ण
	अगर (!ret && kprobe_blacklist__listed(address)) अणु
		pr_warning("%s is blacklisted function, skip it.\n", symbol);
		ret = true;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * @module can be module name of module file path. In हाल of path,
 * inspect elf and find out what is actual module name.
 * Caller has to मुक्त mod_name after using it.
 */
अटल अक्षर *find_module_name(स्थिर अक्षर *module)
अणु
	पूर्णांक fd;
	Elf *elf;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	Elf_Data *data;
	Elf_Scn *sec;
	अक्षर *mod_name = शून्य;
	पूर्णांक name_offset;

	fd = खोलो(module, O_RDONLY);
	अगर (fd < 0)
		वापस शून्य;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य)
		जाओ elf_err;

	अगर (gelf_getehdr(elf, &ehdr) == शून्य)
		जाओ ret_err;

	sec = elf_section_by_name(elf, &ehdr, &shdr,
			".gnu.linkonce.this_module", शून्य);
	अगर (!sec)
		जाओ ret_err;

	data = elf_getdata(sec, शून्य);
	अगर (!data || !data->d_buf)
		जाओ ret_err;

	/*
	 * NOTE:
	 * '.gnu.linkonce.this_module' section of kernel module elf directly
	 * maps to 'struct module' from linux/module.h. This section contains
	 * actual module name which will be used by kernel after loading it.
	 * But, we cannot use 'struct module' here since linux/module.h is not
	 * exposed to user-space. Offset of 'name' has reमुख्यed same from दीर्घ
	 * समय, so hardcoding it here.
	 */
	अगर (ehdr.e_ident[EI_CLASS] == ELFCLASS32)
		name_offset = 12;
	अन्यथा	/* expect ELFCLASS64 by शेष */
		name_offset = 24;

	mod_name = strdup((अक्षर *)data->d_buf + name_offset);

ret_err:
	elf_end(elf);
elf_err:
	बंद(fd);
	वापस mod_name;
पूर्ण

#अगर_घोषित HAVE_DWARF_SUPPORT

अटल पूर्णांक kernel_get_module_dso(स्थिर अक्षर *module, काष्ठा dso **pdso)
अणु
	काष्ठा dso *dso;
	काष्ठा map *map;
	स्थिर अक्षर *vmlinux_name;
	पूर्णांक ret = 0;

	अगर (module) अणु
		अक्षर module_name[128];

		snम_लिखो(module_name, माप(module_name), "[%s]", module);
		map = maps__find_by_name(&host_machine->kmaps, module_name);
		अगर (map) अणु
			dso = map->dso;
			जाओ found;
		पूर्ण
		pr_debug("Failed to find module %s.\n", module);
		वापस -ENOENT;
	पूर्ण

	map = machine__kernel_map(host_machine);
	dso = map->dso;
	अगर (!dso->has_build_id)
		dso__पढ़ो_running_kernel_build_id(dso, host_machine);

	vmlinux_name = symbol_conf.vmlinux_name;
	dso->load_त्रुटि_सं = 0;
	अगर (vmlinux_name)
		ret = dso__load_vmlinux(dso, map, vmlinux_name, false);
	अन्यथा
		ret = dso__load_vmlinux_path(dso, map);
found:
	*pdso = dso;
	वापस ret;
पूर्ण

/*
 * Some binaries like glibc have special symbols which are on the symbol
 * table, but not in the debuginfo. If we can find the address of the
 * symbol from map, we can translate the address back to the probe poपूर्णांक.
 */
अटल पूर्णांक find_alternative_probe_poपूर्णांक(काष्ठा debuginfo *dinfo,
					काष्ठा perf_probe_poपूर्णांक *pp,
					काष्ठा perf_probe_poपूर्णांक *result,
					स्थिर अक्षर *target, काष्ठा nsinfo *nsi,
					bool uprobes)
अणु
	काष्ठा map *map = शून्य;
	काष्ठा symbol *sym;
	u64 address = 0;
	पूर्णांक ret = -ENOENT;

	/* This can work only क्रम function-name based one */
	अगर (!pp->function || pp->file)
		वापस -ENOTSUP;

	map = get_target_map(target, nsi, uprobes);
	अगर (!map)
		वापस -EINVAL;

	/* Find the address of given function */
	map__क्रम_each_symbol_by_name(map, pp->function, sym) अणु
		अगर (uprobes) अणु
			address = sym->start;
			अगर (sym->type == STT_GNU_IFUNC)
				pr_warning("Warning: The probe function (%s) is a GNU indirect function.\n"
					   "Consider identifying the final function used at run time and set the probe directly on that.\n",
					   pp->function);
		पूर्ण अन्यथा
			address = map->unmap_ip(map, sym->start) - map->reloc;
		अवरोध;
	पूर्ण
	अगर (!address) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	pr_debug("Symbol %s address found : %" PRIx64 "\n",
			pp->function, address);

	ret = debuginfo__find_probe_poपूर्णांक(dinfo, (अचिन्हित दीर्घ)address,
					  result);
	अगर (ret <= 0)
		ret = (!ret) ? -ENOENT : ret;
	अन्यथा अणु
		result->offset += pp->offset;
		result->line += pp->line;
		result->retprobe = pp->retprobe;
		ret = 0;
	पूर्ण

out:
	map__put(map);
	वापस ret;

पूर्ण

अटल पूर्णांक get_alternative_probe_event(काष्ठा debuginfo *dinfo,
				       काष्ठा perf_probe_event *pev,
				       काष्ठा perf_probe_poपूर्णांक *पंचांगp)
अणु
	पूर्णांक ret;

	स_नकल(पंचांगp, &pev->poपूर्णांक, माप(*पंचांगp));
	स_रखो(&pev->poपूर्णांक, 0, माप(pev->poपूर्णांक));
	ret = find_alternative_probe_poपूर्णांक(dinfo, पंचांगp, &pev->poपूर्णांक, pev->target,
					   pev->nsi, pev->uprobes);
	अगर (ret < 0)
		स_नकल(&pev->poपूर्णांक, पंचांगp, माप(*पंचांगp));

	वापस ret;
पूर्ण

अटल पूर्णांक get_alternative_line_range(काष्ठा debuginfo *dinfo,
				      काष्ठा line_range *lr,
				      स्थिर अक्षर *target, bool user)
अणु
	काष्ठा perf_probe_poपूर्णांक pp = अणु .function = lr->function,
				       .file = lr->file,
				       .line = lr->start पूर्ण;
	काष्ठा perf_probe_poपूर्णांक result;
	पूर्णांक ret, len = 0;

	स_रखो(&result, 0, माप(result));

	अगर (lr->end != पूर्णांक_उच्च)
		len = lr->end - lr->start;
	ret = find_alternative_probe_poपूर्णांक(dinfo, &pp, &result,
					   target, शून्य, user);
	अगर (!ret) अणु
		lr->function = result.function;
		lr->file = result.file;
		lr->start = result.line;
		अगर (lr->end != पूर्णांक_उच्च)
			lr->end = lr->start + len;
		clear_perf_probe_poपूर्णांक(&pp);
	पूर्ण
	वापस ret;
पूर्ण

#अगर_घोषित HAVE_DEBUGINFOD_SUPPORT
अटल काष्ठा debuginfo *खोलो_from_debuginfod(काष्ठा dso *dso, काष्ठा nsinfo *nsi,
					      bool silent)
अणु
	debuginfod_client *c = debuginfod_begin();
	अक्षर sbuild_id[SBUILD_ID_SIZE + 1];
	काष्ठा debuginfo *ret = शून्य;
	काष्ठा nscookie nsc;
	अक्षर *path;
	पूर्णांक fd;

	अगर (!c)
		वापस शून्य;

	build_id__प्र_लिखो(&dso->bid, sbuild_id);
	fd = debuginfod_find_debuginfo(c, (स्थिर अचिन्हित अक्षर *)sbuild_id,
					0, &path);
	अगर (fd >= 0)
		बंद(fd);
	debuginfod_end(c);
	अगर (fd < 0) अणु
		अगर (!silent)
			pr_debug("Failed to find debuginfo in debuginfod.\n");
		वापस शून्य;
	पूर्ण
	अगर (!silent)
		pr_debug("Load debuginfo from debuginfod (%s)\n", path);

	nsinfo__mountns_enter(nsi, &nsc);
	ret = debuginfo__new((स्थिर अक्षर *)path);
	nsinfo__mountns_निकास(&nsc);
	वापस ret;
पूर्ण
#अन्यथा
अटल अंतरभूत
काष्ठा debuginfo *खोलो_from_debuginfod(काष्ठा dso *dso __maybe_unused,
				       काष्ठा nsinfo *nsi __maybe_unused,
				       bool silent __maybe_unused)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

/* Open new debuginfo of given module */
अटल काष्ठा debuginfo *खोलो_debuginfo(स्थिर अक्षर *module, काष्ठा nsinfo *nsi,
					bool silent)
अणु
	स्थिर अक्षर *path = module;
	अक्षर reason[STRERR_बफ_मानE];
	काष्ठा debuginfo *ret = शून्य;
	काष्ठा dso *dso = शून्य;
	काष्ठा nscookie nsc;
	पूर्णांक err;

	अगर (!module || !म_अक्षर(module, '/')) अणु
		err = kernel_get_module_dso(module, &dso);
		अगर (err < 0) अणु
			अगर (!dso || dso->load_त्रुटि_सं == 0) अणु
				अगर (!str_error_r(-err, reason, STRERR_बफ_मानE))
					म_नकल(reason, "(unknown)");
			पूर्ण अन्यथा
				dso__म_त्रुटि_load(dso, reason, STRERR_बफ_मानE);
			अगर (dso)
				ret = खोलो_from_debuginfod(dso, nsi, silent);
			अगर (ret)
				वापस ret;
			अगर (!silent) अणु
				अगर (module)
					pr_err("Module %s is not loaded, please specify its full path name.\n", module);
				अन्यथा
					pr_err("Failed to find the path for the kernel: %s\n", reason);
			पूर्ण
			वापस शून्य;
		पूर्ण
		path = dso->दीर्घ_name;
	पूर्ण
	nsinfo__mountns_enter(nsi, &nsc);
	ret = debuginfo__new(path);
	अगर (!ret && !silent) अणु
		pr_warning("The %s file has no debug information.\n", path);
		अगर (!module || !strtailcmp(path, ".ko"))
			pr_warning("Rebuild with CONFIG_DEBUG_INFO=y, ");
		अन्यथा
			pr_warning("Rebuild with -g, ");
		pr_warning("or install an appropriate debuginfo package.\n");
	पूर्ण
	nsinfo__mountns_निकास(&nsc);
	वापस ret;
पूर्ण

/* For caching the last debuginfo */
अटल काष्ठा debuginfo *debuginfo_cache;
अटल अक्षर *debuginfo_cache_path;

अटल काष्ठा debuginfo *debuginfo_cache__खोलो(स्थिर अक्षर *module, bool silent)
अणु
	स्थिर अक्षर *path = module;

	/* If the module is शून्य, it should be the kernel. */
	अगर (!module)
		path = "kernel";

	अगर (debuginfo_cache_path && !म_भेद(debuginfo_cache_path, path))
		जाओ out;

	/* Copy module path */
	मुक्त(debuginfo_cache_path);
	debuginfo_cache_path = strdup(path);
	अगर (!debuginfo_cache_path) अणु
		debuginfo__delete(debuginfo_cache);
		debuginfo_cache = शून्य;
		जाओ out;
	पूर्ण

	debuginfo_cache = खोलो_debuginfo(module, शून्य, silent);
	अगर (!debuginfo_cache)
		zमुक्त(&debuginfo_cache_path);
out:
	वापस debuginfo_cache;
पूर्ण

अटल व्योम debuginfo_cache__निकास(व्योम)
अणु
	debuginfo__delete(debuginfo_cache);
	debuginfo_cache = शून्य;
	zमुक्त(&debuginfo_cache_path);
पूर्ण


अटल पूर्णांक get_text_start_address(स्थिर अक्षर *exec, अचिन्हित दीर्घ *address,
				  काष्ठा nsinfo *nsi)
अणु
	Elf *elf;
	GElf_Ehdr ehdr;
	GElf_Shdr shdr;
	पूर्णांक fd, ret = -ENOENT;
	काष्ठा nscookie nsc;

	nsinfo__mountns_enter(nsi, &nsc);
	fd = खोलो(exec, O_RDONLY);
	nsinfo__mountns_निकास(&nsc);
	अगर (fd < 0)
		वापस -त्रुटि_सं;

	elf = elf_begin(fd, PERF_ELF_C_READ_MMAP, शून्य);
	अगर (elf == शून्य) अणु
		ret = -EINVAL;
		जाओ out_बंद;
	पूर्ण

	अगर (gelf_getehdr(elf, &ehdr) == शून्य)
		जाओ out;

	अगर (!elf_section_by_name(elf, &ehdr, &shdr, ".text", शून्य))
		जाओ out;

	*address = shdr.sh_addr - shdr.sh_offset;
	ret = 0;
out:
	elf_end(elf);
out_बंद:
	बंद(fd);

	वापस ret;
पूर्ण

/*
 * Convert trace poपूर्णांक to probe poपूर्णांक with debuginfo
 */
अटल पूर्णांक find_perf_probe_poपूर्णांक_from_dwarf(काष्ठा probe_trace_poपूर्णांक *tp,
					    काष्ठा perf_probe_poपूर्णांक *pp,
					    bool is_kprobe)
अणु
	काष्ठा debuginfo *dinfo = शून्य;
	अचिन्हित दीर्घ stext = 0;
	u64 addr = tp->address;
	पूर्णांक ret = -ENOENT;

	/* convert the address to dwarf address */
	अगर (!is_kprobe) अणु
		अगर (!addr) अणु
			ret = -EINVAL;
			जाओ error;
		पूर्ण
		ret = get_text_start_address(tp->module, &stext, शून्य);
		अगर (ret < 0)
			जाओ error;
		addr += stext;
	पूर्ण अन्यथा अगर (tp->symbol) अणु
		/* If the module is given, this वापसs relative address */
		ret = kernel_get_symbol_address_by_name(tp->symbol, &addr,
							false, !!tp->module);
		अगर (ret != 0)
			जाओ error;
		addr += tp->offset;
	पूर्ण

	pr_debug("try to find information at %" PRIx64 " in %s\n", addr,
		 tp->module ? : "kernel");

	dinfo = debuginfo_cache__खोलो(tp->module, verbose <= 0);
	अगर (dinfo)
		ret = debuginfo__find_probe_poपूर्णांक(dinfo,
						 (अचिन्हित दीर्घ)addr, pp);
	अन्यथा
		ret = -ENOENT;

	अगर (ret > 0) अणु
		pp->retprobe = tp->retprobe;
		वापस 0;
	पूर्ण
error:
	pr_debug("Failed to find corresponding probes from debuginfo.\n");
	वापस ret ? : -ENOENT;
पूर्ण

/* Adjust symbol name and address */
अटल पूर्णांक post_process_probe_trace_poपूर्णांक(काष्ठा probe_trace_poपूर्णांक *tp,
					   काष्ठा map *map, अचिन्हित दीर्घ offs)
अणु
	काष्ठा symbol *sym;
	u64 addr = tp->address - offs;

	sym = map__find_symbol(map, addr);
	अगर (!sym)
		वापस -ENOENT;

	अगर (म_भेद(sym->name, tp->symbol)) अणु
		/* If we have no realname, use symbol क्रम it */
		अगर (!tp->realname)
			tp->realname = tp->symbol;
		अन्यथा
			मुक्त(tp->symbol);
		tp->symbol = strdup(sym->name);
		अगर (!tp->symbol)
			वापस -ENOMEM;
	पूर्ण
	tp->offset = addr - sym->start;
	tp->address -= offs;

	वापस 0;
पूर्ण

/*
 * Rename DWARF symbols to ELF symbols -- gcc someबार optimizes functions
 * and generate new symbols with suffixes such as .स्थिरprop.N or .isra.N
 * etc. Since those symbols are not recorded in DWARF, we have to find
 * correct generated symbols from offline ELF binary.
 * For online kernel or uprobes we करोn't need this because those are
 * rebased on _text, or alपढ़ोy a section relative address.
 */
अटल पूर्णांक
post_process_offline_probe_trace_events(काष्ठा probe_trace_event *tevs,
					पूर्णांक ntevs, स्थिर अक्षर *pathname)
अणु
	काष्ठा map *map;
	अचिन्हित दीर्घ stext = 0;
	पूर्णांक i, ret = 0;

	/* Prepare a map क्रम offline binary */
	map = dso__new_map(pathname);
	अगर (!map || get_text_start_address(pathname, &stext, शून्य) < 0) अणु
		pr_warning("Failed to get ELF symbols for %s\n", pathname);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ntevs; i++) अणु
		ret = post_process_probe_trace_poपूर्णांक(&tevs[i].poपूर्णांक,
						     map, stext);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	map__put(map);

	वापस ret;
पूर्ण

अटल पूर्णांक add_exec_to_probe_trace_events(काष्ठा probe_trace_event *tevs,
					  पूर्णांक ntevs, स्थिर अक्षर *exec,
					  काष्ठा nsinfo *nsi)
अणु
	पूर्णांक i, ret = 0;
	अचिन्हित दीर्घ stext = 0;

	अगर (!exec)
		वापस 0;

	ret = get_text_start_address(exec, &stext, nsi);
	अगर (ret < 0)
		वापस ret;

	क्रम (i = 0; i < ntevs && ret >= 0; i++) अणु
		/* poपूर्णांक.address is the address of poपूर्णांक.symbol + poपूर्णांक.offset */
		tevs[i].poपूर्णांक.address -= stext;
		tevs[i].poपूर्णांक.module = strdup(exec);
		अगर (!tevs[i].poपूर्णांक.module) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		tevs[i].uprobes = true;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
post_process_module_probe_trace_events(काष्ठा probe_trace_event *tevs,
				       पूर्णांक ntevs, स्थिर अक्षर *module,
				       काष्ठा debuginfo *dinfo)
अणु
	Dwarf_Addr text_offs = 0;
	पूर्णांक i, ret = 0;
	अक्षर *mod_name = शून्य;
	काष्ठा map *map;

	अगर (!module)
		वापस 0;

	map = get_target_map(module, शून्य, false);
	अगर (!map || debuginfo__get_text_offset(dinfo, &text_offs, true) < 0) अणु
		pr_warning("Failed to get ELF symbols for %s\n", module);
		वापस -EINVAL;
	पूर्ण

	mod_name = find_module_name(module);
	क्रम (i = 0; i < ntevs; i++) अणु
		ret = post_process_probe_trace_poपूर्णांक(&tevs[i].poपूर्णांक,
						map, (अचिन्हित दीर्घ)text_offs);
		अगर (ret < 0)
			अवरोध;
		tevs[i].poपूर्णांक.module =
			strdup(mod_name ? mod_name : module);
		अगर (!tevs[i].poपूर्णांक.module) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
	पूर्ण

	मुक्त(mod_name);
	map__put(map);

	वापस ret;
पूर्ण

अटल पूर्णांक
post_process_kernel_probe_trace_events(काष्ठा probe_trace_event *tevs,
				       पूर्णांक ntevs)
अणु
	काष्ठा ref_reloc_sym *reloc_sym;
	काष्ठा map *map;
	अक्षर *पंचांगp;
	पूर्णांक i, skipped = 0;

	/* Skip post process अगर the target is an offline kernel */
	अगर (symbol_conf.ignore_vmlinux_buildid)
		वापस post_process_offline_probe_trace_events(tevs, ntevs,
						symbol_conf.vmlinux_name);

	reloc_sym = kernel_get_ref_reloc_sym(&map);
	अगर (!reloc_sym) अणु
		pr_warning("Relocated base symbol is not found!\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < ntevs; i++) अणु
		अगर (!tevs[i].poपूर्णांक.address)
			जारी;
		अगर (tevs[i].poपूर्णांक.retprobe && !kretprobe_offset_is_supported())
			जारी;
		/*
		 * If we found a wrong one, mark it by शून्य symbol.
		 * Since addresses in debuginfo is same as objdump, we need
		 * to convert it to addresses on memory.
		 */
		अगर (kprobe_warn_out_range(tevs[i].poपूर्णांक.symbol,
			map__objdump_2mem(map, tevs[i].poपूर्णांक.address))) अणु
			पंचांगp = शून्य;
			skipped++;
		पूर्ण अन्यथा अणु
			पंचांगp = strdup(reloc_sym->name);
			अगर (!पंचांगp)
				वापस -ENOMEM;
		पूर्ण
		/* If we have no realname, use symbol क्रम it */
		अगर (!tevs[i].poपूर्णांक.realname)
			tevs[i].poपूर्णांक.realname = tevs[i].poपूर्णांक.symbol;
		अन्यथा
			मुक्त(tevs[i].poपूर्णांक.symbol);
		tevs[i].poपूर्णांक.symbol = पंचांगp;
		tevs[i].poपूर्णांक.offset = tevs[i].poपूर्णांक.address -
			(map->reloc ? reloc_sym->unrelocated_addr :
				      reloc_sym->addr);
	पूर्ण
	वापस skipped;
पूर्ण

व्योम __weak
arch__post_process_probe_trace_events(काष्ठा perf_probe_event *pev __maybe_unused,
				      पूर्णांक ntevs __maybe_unused)
अणु
पूर्ण

/* Post processing the probe events */
अटल पूर्णांक post_process_probe_trace_events(काष्ठा perf_probe_event *pev,
					   काष्ठा probe_trace_event *tevs,
					   पूर्णांक ntevs, स्थिर अक्षर *module,
					   bool uprobe, काष्ठा debuginfo *dinfo)
अणु
	पूर्णांक ret;

	अगर (uprobe)
		ret = add_exec_to_probe_trace_events(tevs, ntevs, module,
						     pev->nsi);
	अन्यथा अगर (module)
		/* Currently ref_reloc_sym based probe is not क्रम drivers */
		ret = post_process_module_probe_trace_events(tevs, ntevs,
							     module, dinfo);
	अन्यथा
		ret = post_process_kernel_probe_trace_events(tevs, ntevs);

	अगर (ret >= 0)
		arch__post_process_probe_trace_events(pev, ntevs);

	वापस ret;
पूर्ण

/* Try to find perf_probe_event with debuginfo */
अटल पूर्णांक try_to_find_probe_trace_events(काष्ठा perf_probe_event *pev,
					  काष्ठा probe_trace_event **tevs)
अणु
	bool need_dwarf = perf_probe_event_need_dwarf(pev);
	काष्ठा perf_probe_poपूर्णांक पंचांगp;
	काष्ठा debuginfo *dinfo;
	पूर्णांक ntevs, ret = 0;

	/* Workaround क्रम gcc #98776 issue.
	 * Perf failed to add kretprobe event with debuginfo of vmlinux which is
	 * compiled by gcc with -fpatchable-function-entry option enabled. The
	 * same issue with kernel module. The retprobe करोesn`t need debuginfo.
	 * This workaround solution use map to query the probe function address
	 * क्रम retprobe event.
	 */
	अगर (pev->poपूर्णांक.retprobe)
		वापस 0;

	dinfo = खोलो_debuginfo(pev->target, pev->nsi, !need_dwarf);
	अगर (!dinfo) अणु
		अगर (need_dwarf)
			वापस -ENOENT;
		pr_debug("Could not open debuginfo. Try to use symbols.\n");
		वापस 0;
	पूर्ण

	pr_debug("Try to find probe point from debuginfo.\n");
	/* Searching trace events corresponding to a probe event */
	ntevs = debuginfo__find_trace_events(dinfo, pev, tevs);

	अगर (ntevs == 0)	अणु  /* Not found, retry with an alternative */
		ret = get_alternative_probe_event(dinfo, pev, &पंचांगp);
		अगर (!ret) अणु
			ntevs = debuginfo__find_trace_events(dinfo, pev, tevs);
			/*
			 * Write back to the original probe_event क्रम
			 * setting appropriate (user given) event name
			 */
			clear_perf_probe_poपूर्णांक(&pev->poपूर्णांक);
			स_नकल(&pev->poपूर्णांक, &पंचांगp, माप(पंचांगp));
		पूर्ण
	पूर्ण

	अगर (ntevs > 0) अणु	/* Succeeded to find trace events */
		pr_debug("Found %d probe_trace_events.\n", ntevs);
		ret = post_process_probe_trace_events(pev, *tevs, ntevs,
					pev->target, pev->uprobes, dinfo);
		अगर (ret < 0 || ret == ntevs) अणु
			pr_debug("Post processing failed or all events are skipped. (%d)\n", ret);
			clear_probe_trace_events(*tevs, ntevs);
			zमुक्त(tevs);
			ntevs = 0;
		पूर्ण
	पूर्ण

	debuginfo__delete(dinfo);

	अगर (ntevs == 0)	अणु	/* No error but failed to find probe poपूर्णांक. */
		pr_warning("Probe point '%s' not found.\n",
			   synthesize_perf_probe_poपूर्णांक(&pev->poपूर्णांक));
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (ntevs < 0) अणु
		/* Error path : ntevs < 0 */
		pr_debug("An error occurred in debuginfo analysis (%d).\n", ntevs);
		अगर (ntevs == -EBADF)
			pr_warning("Warning: No dwarf info found in the vmlinux - "
				"please rebuild kernel with CONFIG_DEBUG_INFO=y.\n");
		अगर (!need_dwarf) अणु
			pr_debug("Trying to use symbols.\n");
			वापस 0;
		पूर्ण
	पूर्ण
	वापस ntevs;
पूर्ण

#घोषणा LINEBUF_SIZE 256
#घोषणा NR_ADDITIONAL_LINES 2

अटल पूर्णांक __show_one_line(खाता *fp, पूर्णांक l, bool skip, bool show_num)
अणु
	अक्षर buf[LINEBUF_SIZE], sbuf[STRERR_बफ_मानE];
	स्थिर अक्षर *color = show_num ? "" : PERF_COLOR_BLUE;
	स्थिर अक्षर *prefix = शून्य;

	करो अणु
		अगर (ख_माला_लो(buf, LINEBUF_SIZE, fp) == शून्य)
			जाओ error;
		अगर (skip)
			जारी;
		अगर (!prefix) अणु
			prefix = show_num ? "%7d  " : "         ";
			color_ख_लिखो(मानक_निकास, color, prefix, l);
		पूर्ण
		color_ख_लिखो(मानक_निकास, color, "%s", buf);

	पूर्ण जबतक (म_अक्षर(buf, '\n') == शून्य);

	वापस 1;
error:
	अगर (ख_त्रुटि(fp)) अणु
		pr_warning("File read error: %s\n",
			   str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक _show_one_line(खाता *fp, पूर्णांक l, bool skip, bool show_num)
अणु
	पूर्णांक rv = __show_one_line(fp, l, skip, show_num);
	अगर (rv == 0) अणु
		pr_warning("Source file is shorter than expected.\n");
		rv = -1;
	पूर्ण
	वापस rv;
पूर्ण

#घोषणा show_one_line_with_num(f,l)	_show_one_line(f,l,false,true)
#घोषणा show_one_line(f,l)		_show_one_line(f,l,false,false)
#घोषणा skip_one_line(f,l)		_show_one_line(f,l,true,false)
#घोषणा show_one_line_or_eof(f,l)	__show_one_line(f,l,false,false)

/*
 * Show line-range always requires debuginfo to find source file and
 * line number.
 */
अटल पूर्णांक __show_line_range(काष्ठा line_range *lr, स्थिर अक्षर *module,
			     bool user)
अणु
	काष्ठा build_id bid;
	पूर्णांक l = 1;
	काष्ठा पूर्णांक_node *ln;
	काष्ठा debuginfo *dinfo;
	खाता *fp;
	पूर्णांक ret;
	अक्षर *पंचांगp;
	अक्षर sbuf[STRERR_बफ_मानE];
	अक्षर sbuild_id[SBUILD_ID_SIZE] = "";

	/* Search a line range */
	dinfo = खोलो_debuginfo(module, शून्य, false);
	अगर (!dinfo)
		वापस -ENOENT;

	ret = debuginfo__find_line_range(dinfo, lr);
	अगर (!ret) अणु	/* Not found, retry with an alternative */
		ret = get_alternative_line_range(dinfo, lr, module, user);
		अगर (!ret)
			ret = debuginfo__find_line_range(dinfo, lr);
	पूर्ण
	अगर (dinfo->build_id) अणु
		build_id__init(&bid, dinfo->build_id, BUILD_ID_SIZE);
		build_id__प्र_लिखो(&bid, sbuild_id);
	पूर्ण
	debuginfo__delete(dinfo);
	अगर (ret == 0 || ret == -ENOENT) अणु
		pr_warning("Specified source line is not found.\n");
		वापस -ENOENT;
	पूर्ण अन्यथा अगर (ret < 0) अणु
		pr_warning("Debuginfo analysis failed.\n");
		वापस ret;
	पूर्ण

	/* Convert source file path */
	पंचांगp = lr->path;
	ret = find_source_path(पंचांगp, sbuild_id, lr->comp_dir, &lr->path);

	/* Free old path when new path is asचिन्हित */
	अगर (पंचांगp != lr->path)
		मुक्त(पंचांगp);

	अगर (ret < 0) अणु
		pr_warning("Failed to find source file path.\n");
		वापस ret;
	पूर्ण

	setup_pager();

	अगर (lr->function)
		ख_लिखो(मानक_निकास, "<%s@%s:%d>\n", lr->function, lr->path,
			lr->start - lr->offset);
	अन्यथा
		ख_लिखो(मानक_निकास, "<%s:%d>\n", lr->path, lr->start);

	fp = ख_खोलो(lr->path, "r");
	अगर (fp == शून्य) अणु
		pr_warning("Failed to open %s: %s\n", lr->path,
			   str_error_r(त्रुटि_सं, sbuf, माप(sbuf)));
		वापस -त्रुटि_सं;
	पूर्ण
	/* Skip to starting line number */
	जबतक (l < lr->start) अणु
		ret = skip_one_line(fp, l++);
		अगर (ret < 0)
			जाओ end;
	पूर्ण

	पूर्णांकlist__क्रम_each_entry(ln, lr->line_list) अणु
		क्रम (; ln->i > (अचिन्हित दीर्घ)l; l++) अणु
			ret = show_one_line(fp, l - lr->offset);
			अगर (ret < 0)
				जाओ end;
		पूर्ण
		ret = show_one_line_with_num(fp, l++ - lr->offset);
		अगर (ret < 0)
			जाओ end;
	पूर्ण

	अगर (lr->end == पूर्णांक_उच्च)
		lr->end = l + NR_ADDITIONAL_LINES;
	जबतक (l <= lr->end) अणु
		ret = show_one_line_or_eof(fp, l++ - lr->offset);
		अगर (ret <= 0)
			अवरोध;
	पूर्ण
end:
	ख_बंद(fp);
	वापस ret;
पूर्ण

पूर्णांक show_line_range(काष्ठा line_range *lr, स्थिर अक्षर *module,
		    काष्ठा nsinfo *nsi, bool user)
अणु
	पूर्णांक ret;
	काष्ठा nscookie nsc;

	ret = init_probe_symbol_maps(user);
	अगर (ret < 0)
		वापस ret;
	nsinfo__mountns_enter(nsi, &nsc);
	ret = __show_line_range(lr, module, user);
	nsinfo__mountns_निकास(&nsc);
	निकास_probe_symbol_maps();

	वापस ret;
पूर्ण

अटल पूर्णांक show_available_vars_at(काष्ठा debuginfo *dinfo,
				  काष्ठा perf_probe_event *pev,
				  काष्ठा strfilter *_filter)
अणु
	अक्षर *buf;
	पूर्णांक ret, i, nvars;
	काष्ठा str_node *node;
	काष्ठा variable_list *vls = शून्य, *vl;
	काष्ठा perf_probe_poपूर्णांक पंचांगp;
	स्थिर अक्षर *var;

	buf = synthesize_perf_probe_poपूर्णांक(&pev->poपूर्णांक);
	अगर (!buf)
		वापस -EINVAL;
	pr_debug("Searching variables at %s\n", buf);

	ret = debuginfo__find_available_vars_at(dinfo, pev, &vls);
	अगर (!ret) अणु  /* Not found, retry with an alternative */
		ret = get_alternative_probe_event(dinfo, pev, &पंचांगp);
		अगर (!ret) अणु
			ret = debuginfo__find_available_vars_at(dinfo, pev,
								&vls);
			/* Release the old probe_poपूर्णांक */
			clear_perf_probe_poपूर्णांक(&पंचांगp);
		पूर्ण
	पूर्ण
	अगर (ret <= 0) अणु
		अगर (ret == 0 || ret == -ENOENT) अणु
			pr_err("Failed to find the address of %s\n", buf);
			ret = -ENOENT;
		पूर्ण अन्यथा
			pr_warning("Debuginfo analysis failed.\n");
		जाओ end;
	पूर्ण

	/* Some variables are found */
	ख_लिखो(मानक_निकास, "Available variables at %s\n", buf);
	क्रम (i = 0; i < ret; i++) अणु
		vl = &vls[i];
		/*
		 * A probe poपूर्णांक might be converted to
		 * several trace poपूर्णांकs.
		 */
		ख_लिखो(मानक_निकास, "\t@<%s+%lu>\n", vl->poपूर्णांक.symbol,
			vl->poपूर्णांक.offset);
		zमुक्त(&vl->poपूर्णांक.symbol);
		nvars = 0;
		अगर (vl->vars) अणु
			strlist__क्रम_each_entry(node, vl->vars) अणु
				var = म_अक्षर(node->s, '\t') + 1;
				अगर (strfilter__compare(_filter, var)) अणु
					ख_लिखो(मानक_निकास, "\t\t%s\n", node->s);
					nvars++;
				पूर्ण
			पूर्ण
			strlist__delete(vl->vars);
		पूर्ण
		अगर (nvars == 0)
			ख_लिखो(मानक_निकास, "\t\t(No matched variables)\n");
	पूर्ण
	मुक्त(vls);
end:
	मुक्त(buf);
	वापस ret;
पूर्ण

/* Show available variables on given probe poपूर्णांक */
पूर्णांक show_available_vars(काष्ठा perf_probe_event *pevs, पूर्णांक npevs,
			काष्ठा strfilter *_filter)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा debuginfo *dinfo;

	ret = init_probe_symbol_maps(pevs->uprobes);
	अगर (ret < 0)
		वापस ret;

	dinfo = खोलो_debuginfo(pevs->target, pevs->nsi, false);
	अगर (!dinfo) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	setup_pager();

	क्रम (i = 0; i < npevs && ret >= 0; i++)
		ret = show_available_vars_at(dinfo, &pevs[i], _filter);

	debuginfo__delete(dinfo);
out:
	निकास_probe_symbol_maps();
	वापस ret;
पूर्ण

#अन्यथा	/* !HAVE_DWARF_SUPPORT */

अटल व्योम debuginfo_cache__निकास(व्योम)
अणु
पूर्ण

अटल पूर्णांक
find_perf_probe_poपूर्णांक_from_dwarf(काष्ठा probe_trace_poपूर्णांक *tp __maybe_unused,
				 काष्ठा perf_probe_poपूर्णांक *pp __maybe_unused,
				 bool is_kprobe __maybe_unused)
अणु
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक try_to_find_probe_trace_events(काष्ठा perf_probe_event *pev,
				काष्ठा probe_trace_event **tevs __maybe_unused)
अणु
	अगर (perf_probe_event_need_dwarf(pev)) अणु
		pr_warning("Debuginfo-analysis is not supported.\n");
		वापस -ENOSYS;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक show_line_range(काष्ठा line_range *lr __maybe_unused,
		    स्थिर अक्षर *module __maybe_unused,
		    काष्ठा nsinfo *nsi __maybe_unused,
		    bool user __maybe_unused)
अणु
	pr_warning("Debuginfo-analysis is not supported.\n");
	वापस -ENOSYS;
पूर्ण

पूर्णांक show_available_vars(काष्ठा perf_probe_event *pevs __maybe_unused,
			पूर्णांक npevs __maybe_unused,
			काष्ठा strfilter *filter __maybe_unused)
अणु
	pr_warning("Debuginfo-analysis is not supported.\n");
	वापस -ENOSYS;
पूर्ण
#पूर्ण_अगर

व्योम line_range__clear(काष्ठा line_range *lr)
अणु
	zमुक्त(&lr->function);
	zमुक्त(&lr->file);
	zमुक्त(&lr->path);
	zमुक्त(&lr->comp_dir);
	पूर्णांकlist__delete(lr->line_list);
पूर्ण

पूर्णांक line_range__init(काष्ठा line_range *lr)
अणु
	स_रखो(lr, 0, माप(*lr));
	lr->line_list = पूर्णांकlist__new(शून्य);
	अगर (!lr->line_list)
		वापस -ENOMEM;
	अन्यथा
		वापस 0;
पूर्ण

अटल पूर्णांक parse_line_num(अक्षर **ptr, पूर्णांक *val, स्थिर अक्षर *what)
अणु
	स्थिर अक्षर *start = *ptr;

	त्रुटि_सं = 0;
	*val = म_से_दीर्घ(*ptr, ptr, 0);
	अगर (त्रुटि_सं || *ptr == start) अणु
		semantic_error("'%s' is not a valid number.\n", what);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Check the name is good क्रम event, group or function */
अटल bool is_c_func_name(स्थिर अक्षर *name)
अणु
	अगर (!है_अक्षर(*name) && *name != '_')
		वापस false;
	जबतक (*++name != '\0') अणु
		अगर (!है_अक्षर(*name) && !है_अंक(*name) && *name != '_')
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/*
 * Stuff 'lr' according to the line range described by 'arg'.
 * The line range syntax is described by:
 *
 *         SRC[:SLN[+NUM|-ELN]]
 *         FNC[@SRC][:SLN[+NUM|-ELN]]
 */
पूर्णांक parse_line_range_desc(स्थिर अक्षर *arg, काष्ठा line_range *lr)
अणु
	अक्षर *range, *file, *name = strdup(arg);
	पूर्णांक err;

	अगर (!name)
		वापस -ENOMEM;

	lr->start = 0;
	lr->end = पूर्णांक_उच्च;

	range = म_अक्षर(name, ':');
	अगर (range) अणु
		*range++ = '\0';

		err = parse_line_num(&range, &lr->start, "start line");
		अगर (err)
			जाओ err;

		अगर (*range == '+' || *range == '-') अणु
			स्थिर अक्षर c = *range++;

			err = parse_line_num(&range, &lr->end, "end line");
			अगर (err)
				जाओ err;

			अगर (c == '+') अणु
				lr->end += lr->start;
				/*
				 * Adjust the number of lines here.
				 * If the number of lines == 1, the
				 * the end of line should be equal to
				 * the start of line.
				 */
				lr->end--;
			पूर्ण
		पूर्ण

		pr_debug("Line range is %d to %d\n", lr->start, lr->end);

		err = -EINVAL;
		अगर (lr->start > lr->end) अणु
			semantic_error("Start line must be smaller"
				       " than end line.\n");
			जाओ err;
		पूर्ण
		अगर (*range != '\0') अणु
			semantic_error("Tailing with invalid str '%s'.\n", range);
			जाओ err;
		पूर्ण
	पूर्ण

	file = म_अक्षर(name, '@');
	अगर (file) अणु
		*file = '\0';
		lr->file = strdup(++file);
		अगर (lr->file == शून्य) अणु
			err = -ENOMEM;
			जाओ err;
		पूर्ण
		lr->function = name;
	पूर्ण अन्यथा अगर (म_अक्षर(name, '/') || strchr(name, '.'))
		lr->file = name;
	अन्यथा अगर (is_c_func_name(name))/* We reuse it क्रम checking funcname */
		lr->function = name;
	अन्यथा अणु	/* Invalid name */
		semantic_error("'%s' is not a valid function name.\n", name);
		err = -EINVAL;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	मुक्त(name);
	वापस err;
पूर्ण

अटल पूर्णांक parse_perf_probe_event_name(अक्षर **arg, काष्ठा perf_probe_event *pev)
अणु
	अक्षर *ptr;

	ptr = strpbrk_esc(*arg, ":");
	अगर (ptr) अणु
		*ptr = '\0';
		अगर (!pev->sdt && !is_c_func_name(*arg))
			जाओ ng_name;
		pev->group = strdup_esc(*arg);
		अगर (!pev->group)
			वापस -ENOMEM;
		*arg = ptr + 1;
	पूर्ण अन्यथा
		pev->group = शून्य;

	pev->event = strdup_esc(*arg);
	अगर (pev->event == शून्य)
		वापस -ENOMEM;

	अगर (!pev->sdt && !is_c_func_name(pev->event)) अणु
		zमुक्त(&pev->event);
ng_name:
		zमुक्त(&pev->group);
		semantic_error("%s is bad for event name -it must "
			       "follow C symbol-naming rule.\n", *arg);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Parse probepoपूर्णांक definition. */
अटल पूर्णांक parse_perf_probe_poपूर्णांक(अक्षर *arg, काष्ठा perf_probe_event *pev)
अणु
	काष्ठा perf_probe_poपूर्णांक *pp = &pev->poपूर्णांक;
	अक्षर *ptr, *पंचांगp;
	अक्षर c, nc = 0;
	bool file_spec = false;
	पूर्णांक ret;

	/*
	 * <Syntax>
	 * perf probe [GRP:][EVENT=]SRC[:LN|;PTN]
	 * perf probe [GRP:][EVENT=]FUNC[@SRC][+OFFS|%वापस|:LN|;PAT]
	 * perf probe %[GRP:]SDT_EVENT
	 */
	अगर (!arg)
		वापस -EINVAL;

	अगर (is_sdt_event(arg)) अणु
		pev->sdt = true;
		अगर (arg[0] == '%')
			arg++;
	पूर्ण

	ptr = strpbrk_esc(arg, ";=@+%");
	अगर (pev->sdt) अणु
		अगर (ptr) अणु
			अगर (*ptr != '@') अणु
				semantic_error("%s must be an SDT name.\n",
					       arg);
				वापस -EINVAL;
			पूर्ण
			/* This must be a target file name or build id */
			पंचांगp = build_id_cache__complement(ptr + 1);
			अगर (पंचांगp) अणु
				pev->target = build_id_cache__origname(पंचांगp);
				मुक्त(पंचांगp);
			पूर्ण अन्यथा
				pev->target = strdup_esc(ptr + 1);
			अगर (!pev->target)
				वापस -ENOMEM;
			*ptr = '\0';
		पूर्ण
		ret = parse_perf_probe_event_name(&arg, pev);
		अगर (ret == 0) अणु
			अगर (aप्र_लिखो(&pev->poपूर्णांक.function, "%%%s", pev->event) < 0)
				ret = -त्रुटि_सं;
		पूर्ण
		वापस ret;
	पूर्ण

	अगर (ptr && *ptr == '=') अणु	/* Event name */
		*ptr = '\0';
		पंचांगp = ptr + 1;
		ret = parse_perf_probe_event_name(&arg, pev);
		अगर (ret < 0)
			वापस ret;

		arg = पंचांगp;
	पूर्ण

	/*
	 * Check arg is function or file name and copy it.
	 *
	 * We consider arg to be a file spec अगर and only अगर it satisfies
	 * all of the below criteria::
	 * - it करोes not include any of "+@%",
	 * - it includes one of ":;", and
	 * - it has a period '.' in the name.
	 *
	 * Otherwise, we consider arg to be a function specअगरication.
	 */
	अगर (!strpbrk_esc(arg, "+@%")) अणु
		ptr = strpbrk_esc(arg, ";:");
		/* This is a file spec अगर it includes a '.' beक्रमe ; or : */
		अगर (ptr && स_प्रथम(arg, '.', ptr - arg))
			file_spec = true;
	पूर्ण

	ptr = strpbrk_esc(arg, ";:+@%");
	अगर (ptr) अणु
		nc = *ptr;
		*ptr++ = '\0';
	पूर्ण

	अगर (arg[0] == '\0')
		पंचांगp = शून्य;
	अन्यथा अणु
		पंचांगp = strdup_esc(arg);
		अगर (पंचांगp == शून्य)
			वापस -ENOMEM;
	पूर्ण

	अगर (file_spec)
		pp->file = पंचांगp;
	अन्यथा अणु
		pp->function = पंचांगp;

		/*
		 * Keep pp->function even अगर this is असलolute address,
		 * so it can mark whether असल_address is valid.
		 * Which make 'perf probe lib.bin 0x0' possible.
		 *
		 * Note that checking length of पंचांगp is not needed
		 * because when we access पंचांगp[1] we know पंचांगp[0] is '0',
		 * so पंचांगp[1] should always valid (but could be '\0').
		 */
		अगर (पंचांगp && !म_भेदन(पंचांगp, "0x", 2)) अणु
			pp->असल_address = म_से_अदीर्घ(pp->function, &पंचांगp, 0);
			अगर (*पंचांगp != '\0') अणु
				semantic_error("Invalid absolute address.\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Parse other options */
	जबतक (ptr) अणु
		arg = ptr;
		c = nc;
		अगर (c == ';') अणु	/* Lazy pattern must be the last part */
			pp->lazy_line = strdup(arg); /* let leave escapes */
			अगर (pp->lazy_line == शून्य)
				वापस -ENOMEM;
			अवरोध;
		पूर्ण
		ptr = strpbrk_esc(arg, ";:+@%");
		अगर (ptr) अणु
			nc = *ptr;
			*ptr++ = '\0';
		पूर्ण
		चयन (c) अणु
		हाल ':':	/* Line number */
			pp->line = म_से_अदीर्घ(arg, &पंचांगp, 0);
			अगर (*पंचांगp != '\0') अणु
				semantic_error("There is non-digit char"
					       " in line number.\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल '+':	/* Byte offset from a symbol */
			pp->offset = म_से_अदीर्घ(arg, &पंचांगp, 0);
			अगर (*पंचांगp != '\0') अणु
				semantic_error("There is non-digit character"
						" in offset.\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल '@':	/* File name */
			अगर (pp->file) अणु
				semantic_error("SRC@SRC is not allowed.\n");
				वापस -EINVAL;
			पूर्ण
			pp->file = strdup_esc(arg);
			अगर (pp->file == शून्य)
				वापस -ENOMEM;
			अवरोध;
		हाल '%':	/* Probe places */
			अगर (म_भेद(arg, "return") == 0) अणु
				pp->retprobe = 1;
			पूर्ण अन्यथा अणु	/* Others not supported yet */
				semantic_error("%%%s is not supported.\n", arg);
				वापस -ENOTSUP;
			पूर्ण
			अवरोध;
		शेष:	/* Buggy हाल */
			pr_err("This program has a bug at %s:%d.\n",
				__खाता__, __LINE__);
			वापस -ENOTSUP;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Exclusion check */
	अगर (pp->lazy_line && pp->line) अणु
		semantic_error("Lazy pattern can't be used with"
			       " line number.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pp->lazy_line && pp->offset) अणु
		semantic_error("Lazy pattern can't be used with offset.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pp->line && pp->offset) अणु
		semantic_error("Offset can't be used with line number.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pp->line && !pp->lazy_line && pp->file && !pp->function) अणु
		semantic_error("File always requires line number or "
			       "lazy pattern.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pp->offset && !pp->function) अणु
		semantic_error("Offset requires an entry function.\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((pp->offset || pp->line || pp->lazy_line) && pp->retprobe) अणु
		semantic_error("Offset/Line/Lazy pattern can't be used with "
			       "return probe.\n");
		वापस -EINVAL;
	पूर्ण

	pr_debug("symbol:%s file:%s line:%d offset:%lu return:%d lazy:%s\n",
		 pp->function, pp->file, pp->line, pp->offset, pp->retprobe,
		 pp->lazy_line);
	वापस 0;
पूर्ण

/* Parse perf-probe event argument */
अटल पूर्णांक parse_perf_probe_arg(अक्षर *str, काष्ठा perf_probe_arg *arg)
अणु
	अक्षर *पंचांगp, *goodname;
	काष्ठा perf_probe_arg_field **fieldp;

	pr_debug("parsing arg: %s into ", str);

	पंचांगp = म_अक्षर(str, '=');
	अगर (पंचांगp) अणु
		arg->name = strndup(str, पंचांगp - str);
		अगर (arg->name == शून्य)
			वापस -ENOMEM;
		pr_debug("name:%s ", arg->name);
		str = पंचांगp + 1;
	पूर्ण

	पंचांगp = म_अक्षर(str, '@');
	अगर (पंचांगp && पंचांगp != str && !म_भेद(पंचांगp + 1, "user")) अणु /* user attr */
		अगर (!user_access_is_supported()) अणु
			semantic_error("ftrace does not support user access\n");
			वापस -EINVAL;
		पूर्ण
		*पंचांगp = '\0';
		arg->user_access = true;
		pr_debug("user_access ");
	पूर्ण

	पंचांगp = म_अक्षर(str, ':');
	अगर (पंचांगp) अणु	/* Type setting */
		*पंचांगp = '\0';
		arg->type = strdup(पंचांगp + 1);
		अगर (arg->type == शून्य)
			वापस -ENOMEM;
		pr_debug("type:%s ", arg->type);
	पूर्ण

	पंचांगp = strpbrk(str, "-.[");
	अगर (!is_c_varname(str) || !पंचांगp) अणु
		/* A variable, रेजिस्टर, symbol or special value */
		arg->var = strdup(str);
		अगर (arg->var == शून्य)
			वापस -ENOMEM;
		pr_debug("%s\n", arg->var);
		वापस 0;
	पूर्ण

	/* Structure fields or array element */
	arg->var = strndup(str, पंचांगp - str);
	अगर (arg->var == शून्य)
		वापस -ENOMEM;
	goodname = arg->var;
	pr_debug("%s, ", arg->var);
	fieldp = &arg->field;

	करो अणु
		*fieldp = zalloc(माप(काष्ठा perf_probe_arg_field));
		अगर (*fieldp == शून्य)
			वापस -ENOMEM;
		अगर (*पंचांगp == '[') अणु	/* Array */
			str = पंचांगp;
			(*fieldp)->index = म_से_दीर्घ(str + 1, &पंचांगp, 0);
			(*fieldp)->ref = true;
			अगर (*पंचांगp != ']' || पंचांगp == str + 1) अणु
				semantic_error("Array index must be a"
						" number.\n");
				वापस -EINVAL;
			पूर्ण
			पंचांगp++;
			अगर (*पंचांगp == '\0')
				पंचांगp = शून्य;
		पूर्ण अन्यथा अणु		/* Structure */
			अगर (*पंचांगp == '.') अणु
				str = पंचांगp + 1;
				(*fieldp)->ref = false;
			पूर्ण अन्यथा अगर (पंचांगp[1] == '>') अणु
				str = पंचांगp + 2;
				(*fieldp)->ref = true;
			पूर्ण अन्यथा अणु
				semantic_error("Argument parse error: %s\n",
					       str);
				वापस -EINVAL;
			पूर्ण
			पंचांगp = strpbrk(str, "-.[");
		पूर्ण
		अगर (पंचांगp) अणु
			(*fieldp)->name = strndup(str, पंचांगp - str);
			अगर ((*fieldp)->name == शून्य)
				वापस -ENOMEM;
			अगर (*str != '[')
				goodname = (*fieldp)->name;
			pr_debug("%s(%d), ", (*fieldp)->name, (*fieldp)->ref);
			fieldp = &(*fieldp)->next;
		पूर्ण
	पूर्ण जबतक (पंचांगp);
	(*fieldp)->name = strdup(str);
	अगर ((*fieldp)->name == शून्य)
		वापस -ENOMEM;
	अगर (*str != '[')
		goodname = (*fieldp)->name;
	pr_debug("%s(%d)\n", (*fieldp)->name, (*fieldp)->ref);

	/* If no name is specअगरied, set the last field name (not array index)*/
	अगर (!arg->name) अणु
		arg->name = strdup(goodname);
		अगर (arg->name == शून्य)
			वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

/* Parse perf-probe event command */
पूर्णांक parse_perf_probe_command(स्थिर अक्षर *cmd, काष्ठा perf_probe_event *pev)
अणु
	अक्षर **argv;
	पूर्णांक argc, i, ret = 0;

	argv = argv_split(cmd, &argc);
	अगर (!argv) अणु
		pr_debug("Failed to split arguments.\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (argc - 1 > MAX_PROBE_ARGS) अणु
		semantic_error("Too many probe arguments (%d).\n", argc - 1);
		ret = -दुस्फल;
		जाओ out;
	पूर्ण
	/* Parse probe poपूर्णांक */
	ret = parse_perf_probe_poपूर्णांक(argv[0], pev);
	अगर (ret < 0)
		जाओ out;

	/* Generate event name अगर needed */
	अगर (!pev->event && pev->poपूर्णांक.function && pev->poपूर्णांक.line
			&& !pev->poपूर्णांक.lazy_line && !pev->poपूर्णांक.offset) अणु
		अगर (aप्र_लिखो(&pev->event, "%s_L%d", pev->poपूर्णांक.function,
			pev->poपूर्णांक.line) < 0)
			वापस -ENOMEM;
	पूर्ण

	/* Copy arguments and ensure वापस probe has no C argument */
	pev->nargs = argc - 1;
	pev->args = zalloc(माप(काष्ठा perf_probe_arg) * pev->nargs);
	अगर (pev->args == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < pev->nargs && ret >= 0; i++) अणु
		ret = parse_perf_probe_arg(argv[i + 1], &pev->args[i]);
		अगर (ret >= 0 &&
		    is_c_varname(pev->args[i].var) && pev->poपूर्णांक.retprobe) अणु
			semantic_error("You can't specify local variable for"
				       " kretprobe.\n");
			ret = -EINVAL;
		पूर्ण
	पूर्ण
out:
	argv_मुक्त(argv);

	वापस ret;
पूर्ण

/* Returns true अगर *any* ARG is either C variable, $params or $vars. */
bool perf_probe_with_var(काष्ठा perf_probe_event *pev)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < pev->nargs; i++)
		अगर (is_c_varname(pev->args[i].var)              ||
		    !म_भेद(pev->args[i].var, PROBE_ARG_PARAMS) ||
		    !म_भेद(pev->args[i].var, PROBE_ARG_VARS))
			वापस true;
	वापस false;
पूर्ण

/* Return true अगर this perf_probe_event requires debuginfo */
bool perf_probe_event_need_dwarf(काष्ठा perf_probe_event *pev)
अणु
	अगर (pev->poपूर्णांक.file || pev->poपूर्णांक.line || pev->poपूर्णांक.lazy_line)
		वापस true;

	अगर (perf_probe_with_var(pev))
		वापस true;

	वापस false;
पूर्ण

/* Parse probe_events event पूर्णांकo काष्ठा probe_poपूर्णांक */
पूर्णांक parse_probe_trace_command(स्थिर अक्षर *cmd, काष्ठा probe_trace_event *tev)
अणु
	काष्ठा probe_trace_poपूर्णांक *tp = &tev->poपूर्णांक;
	अक्षर pr;
	अक्षर *p;
	अक्षर *argv0_str = शून्य, *fmt, *fmt1_str, *fmt2_str, *fmt3_str;
	पूर्णांक ret, i, argc;
	अक्षर **argv;

	pr_debug("Parsing probe_events: %s\n", cmd);
	argv = argv_split(cmd, &argc);
	अगर (!argv) अणु
		pr_debug("Failed to split arguments.\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (argc < 2) अणु
		semantic_error("Too few probe arguments.\n");
		ret = -दुस्फल;
		जाओ out;
	पूर्ण

	/* Scan event and group name. */
	argv0_str = strdup(argv[0]);
	अगर (argv0_str == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	fmt1_str = म_मोहर_r(argv0_str, ":", &fmt);
	fmt2_str = म_मोहर_r(शून्य, "/", &fmt);
	fmt3_str = म_मोहर_r(शून्य, " \t", &fmt);
	अगर (fmt1_str == शून्य || fmt2_str == शून्य || fmt3_str == शून्य) अणु
		semantic_error("Failed to parse event name: %s\n", argv[0]);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	pr = fmt1_str[0];
	tev->group = strdup(fmt2_str);
	tev->event = strdup(fmt3_str);
	अगर (tev->group == शून्य || tev->event == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	pr_debug("Group:%s Event:%s probe:%c\n", tev->group, tev->event, pr);

	tp->retprobe = (pr == 'r');

	/* Scan module name(अगर there), function name and offset */
	p = म_अक्षर(argv[1], ':');
	अगर (p) अणु
		tp->module = strndup(argv[1], p - argv[1]);
		अगर (!tp->module) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		tev->uprobes = (tp->module[0] == '/');
		p++;
	पूर्ण अन्यथा
		p = argv[1];
	fmt1_str = म_मोहर_r(p, "+", &fmt);
	/* only the address started with 0x */
	अगर (fmt1_str[0] == '0')	अणु
		/*
		 * Fix a special हाल:
		 * अगर address == 0, kernel reports something like:
		 * p:probe_libc/असल_0 /lib/libc-2.18.so:0x          (null) arg1=%ax
		 * Newer kernel may fix that, but we want to
		 * support old kernel also.
		 */
		अगर (म_भेद(fmt1_str, "0x") == 0) अणु
			अगर (!argv[2] || म_भेद(argv[2], "(null)")) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			tp->address = 0;

			मुक्त(argv[2]);
			क्रम (i = 2; argv[i + 1] != शून्य; i++)
				argv[i] = argv[i + 1];

			argv[i] = शून्य;
			argc -= 1;
		पूर्ण अन्यथा
			tp->address = म_से_अदीर्घ(fmt1_str, शून्य, 0);
	पूर्ण अन्यथा अणु
		/* Only the symbol-based probe has offset */
		tp->symbol = strdup(fmt1_str);
		अगर (tp->symbol == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		fmt2_str = म_मोहर_r(शून्य, "", &fmt);
		अगर (fmt2_str == शून्य)
			tp->offset = 0;
		अन्यथा
			tp->offset = म_से_अदीर्घ(fmt2_str, शून्य, 10);
	पूर्ण

	अगर (tev->uprobes) अणु
		fmt2_str = म_अक्षर(p, '(');
		अगर (fmt2_str)
			tp->ref_ctr_offset = म_से_अदीर्घ(fmt2_str + 1, शून्य, 0);
	पूर्ण

	tev->nargs = argc - 2;
	tev->args = zalloc(माप(काष्ठा probe_trace_arg) * tev->nargs);
	अगर (tev->args == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	क्रम (i = 0; i < tev->nargs; i++) अणु
		p = म_अक्षर(argv[i + 2], '=');
		अगर (p)	/* We करोn't need which रेजिस्टर is asचिन्हित. */
			*p++ = '\0';
		अन्यथा
			p = argv[i + 2];
		tev->args[i].name = strdup(argv[i + 2]);
		/* TODO: parse regs and offset */
		tev->args[i].value = strdup(p);
		अगर (tev->args[i].name == शून्य || tev->args[i].value == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण
	ret = 0;
out:
	मुक्त(argv0_str);
	argv_मुक्त(argv);
	वापस ret;
पूर्ण

/* Compose only probe arg */
अक्षर *synthesize_perf_probe_arg(काष्ठा perf_probe_arg *pa)
अणु
	काष्ठा perf_probe_arg_field *field = pa->field;
	काष्ठा strbuf buf;
	अक्षर *ret = शून्य;
	पूर्णांक err;

	अगर (strbuf_init(&buf, 64) < 0)
		वापस शून्य;

	अगर (pa->name && pa->var)
		err = strbuf_addf(&buf, "%s=%s", pa->name, pa->var);
	अन्यथा
		err = strbuf_addstr(&buf, pa->name ?: pa->var);
	अगर (err)
		जाओ out;

	जबतक (field) अणु
		अगर (field->name[0] == '[')
			err = strbuf_addstr(&buf, field->name);
		अन्यथा
			err = strbuf_addf(&buf, "%s%s", field->ref ? "->" : ".",
					  field->name);
		field = field->next;
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (pa->type)
		अगर (strbuf_addf(&buf, ":%s", pa->type) < 0)
			जाओ out;

	ret = strbuf_detach(&buf, शून्य);
out:
	strbuf_release(&buf);
	वापस ret;
पूर्ण

/* Compose only probe poपूर्णांक (not argument) */
अक्षर *synthesize_perf_probe_poपूर्णांक(काष्ठा perf_probe_poपूर्णांक *pp)
अणु
	काष्ठा strbuf buf;
	अक्षर *पंचांगp, *ret = शून्य;
	पूर्णांक len, err = 0;

	अगर (strbuf_init(&buf, 64) < 0)
		वापस शून्य;

	अगर (pp->function) अणु
		अगर (strbuf_addstr(&buf, pp->function) < 0)
			जाओ out;
		अगर (pp->offset)
			err = strbuf_addf(&buf, "+%lu", pp->offset);
		अन्यथा अगर (pp->line)
			err = strbuf_addf(&buf, ":%d", pp->line);
		अन्यथा अगर (pp->retprobe)
			err = strbuf_addstr(&buf, "%return");
		अगर (err)
			जाओ out;
	पूर्ण
	अगर (pp->file) अणु
		पंचांगp = pp->file;
		len = म_माप(पंचांगp);
		अगर (len > 30) अणु
			पंचांगp = म_अक्षर(pp->file + len - 30, '/');
			पंचांगp = पंचांगp ? पंचांगp + 1 : pp->file + len - 30;
		पूर्ण
		err = strbuf_addf(&buf, "@%s", पंचांगp);
		अगर (!err && !pp->function && pp->line)
			err = strbuf_addf(&buf, ":%d", pp->line);
	पूर्ण
	अगर (!err)
		ret = strbuf_detach(&buf, शून्य);
out:
	strbuf_release(&buf);
	वापस ret;
पूर्ण

अक्षर *synthesize_perf_probe_command(काष्ठा perf_probe_event *pev)
अणु
	काष्ठा strbuf buf;
	अक्षर *पंचांगp, *ret = शून्य;
	पूर्णांक i;

	अगर (strbuf_init(&buf, 64))
		वापस शून्य;
	अगर (pev->event)
		अगर (strbuf_addf(&buf, "%s:%s=", pev->group ?: PERFPROBE_GROUP,
				pev->event) < 0)
			जाओ out;

	पंचांगp = synthesize_perf_probe_poपूर्णांक(&pev->poपूर्णांक);
	अगर (!पंचांगp || strbuf_addstr(&buf, पंचांगp) < 0)
		जाओ out;
	मुक्त(पंचांगp);

	क्रम (i = 0; i < pev->nargs; i++) अणु
		पंचांगp = synthesize_perf_probe_arg(pev->args + i);
		अगर (!पंचांगp || strbuf_addf(&buf, " %s", पंचांगp) < 0)
			जाओ out;
		मुक्त(पंचांगp);
	पूर्ण

	ret = strbuf_detach(&buf, शून्य);
out:
	strbuf_release(&buf);
	वापस ret;
पूर्ण

अटल पूर्णांक __synthesize_probe_trace_arg_ref(काष्ठा probe_trace_arg_ref *ref,
					    काष्ठा strbuf *buf, पूर्णांक depth)
अणु
	पूर्णांक err;
	अगर (ref->next) अणु
		depth = __synthesize_probe_trace_arg_ref(ref->next, buf,
							 depth + 1);
		अगर (depth < 0)
			वापस depth;
	पूर्ण
	अगर (ref->user_access)
		err = strbuf_addf(buf, "%s%ld(", "+u", ref->offset);
	अन्यथा
		err = strbuf_addf(buf, "%+ld(", ref->offset);
	वापस (err < 0) ? err : depth;
पूर्ण

अटल पूर्णांक synthesize_probe_trace_arg(काष्ठा probe_trace_arg *arg,
				      काष्ठा strbuf *buf)
अणु
	काष्ठा probe_trace_arg_ref *ref = arg->ref;
	पूर्णांक depth = 0, err;

	/* Argument name or separator */
	अगर (arg->name)
		err = strbuf_addf(buf, " %s=", arg->name);
	अन्यथा
		err = strbuf_addch(buf, ' ');
	अगर (err)
		वापस err;

	/* Special हाल: @XXX */
	अगर (arg->value[0] == '@' && arg->ref)
			ref = ref->next;

	/* Dereferencing arguments */
	अगर (ref) अणु
		depth = __synthesize_probe_trace_arg_ref(ref, buf, 1);
		अगर (depth < 0)
			वापस depth;
	पूर्ण

	/* Prपूर्णांक argument value */
	अगर (arg->value[0] == '@' && arg->ref)
		err = strbuf_addf(buf, "%s%+ld", arg->value, arg->ref->offset);
	अन्यथा
		err = strbuf_addstr(buf, arg->value);

	/* Closing */
	जबतक (!err && depth--)
		err = strbuf_addch(buf, ')');

	/* Prपूर्णांक argument type */
	अगर (!err && arg->type)
		err = strbuf_addf(buf, ":%s", arg->type);

	वापस err;
पूर्ण

अटल पूर्णांक
synthesize_uprobe_trace_def(काष्ठा probe_trace_event *tev, काष्ठा strbuf *buf)
अणु
	काष्ठा probe_trace_poपूर्णांक *tp = &tev->poपूर्णांक;
	पूर्णांक err;

	err = strbuf_addf(buf, "%s:0x%lx", tp->module, tp->address);

	अगर (err >= 0 && tp->ref_ctr_offset) अणु
		अगर (!uprobe_ref_ctr_is_supported())
			वापस -1;
		err = strbuf_addf(buf, "(0x%lx)", tp->ref_ctr_offset);
	पूर्ण
	वापस err >= 0 ? 0 : -1;
पूर्ण

अक्षर *synthesize_probe_trace_command(काष्ठा probe_trace_event *tev)
अणु
	काष्ठा probe_trace_poपूर्णांक *tp = &tev->poपूर्णांक;
	काष्ठा strbuf buf;
	अक्षर *ret = शून्य;
	पूर्णांक i, err;

	/* Uprobes must have tp->module */
	अगर (tev->uprobes && !tp->module)
		वापस शून्य;

	अगर (strbuf_init(&buf, 32) < 0)
		वापस शून्य;

	अगर (strbuf_addf(&buf, "%c:%s/%s ", tp->retprobe ? 'r' : 'p',
			tev->group, tev->event) < 0)
		जाओ error;
	/*
	 * If tp->address == 0, then this poपूर्णांक must be a
	 * असलolute address uprobe.
	 * try_to_find_असलolute_address() should have made
	 * tp->symbol to "0x0".
	 */
	अगर (tev->uprobes && !tp->address) अणु
		अगर (!tp->symbol || म_भेद(tp->symbol, "0x0"))
			जाओ error;
	पूर्ण

	/* Use the tp->address क्रम uprobes */
	अगर (tev->uprobes) अणु
		err = synthesize_uprobe_trace_def(tev, &buf);
	पूर्ण अन्यथा अगर (!म_भेदन(tp->symbol, "0x", 2)) अणु
		/* Absolute address. See try_to_find_असलolute_address() */
		err = strbuf_addf(&buf, "%s%s0x%lx", tp->module ?: "",
				  tp->module ? ":" : "", tp->address);
	पूर्ण अन्यथा अणु
		err = strbuf_addf(&buf, "%s%s%s+%lu", tp->module ?: "",
				tp->module ? ":" : "", tp->symbol, tp->offset);
	पूर्ण

	अगर (err)
		जाओ error;

	क्रम (i = 0; i < tev->nargs; i++)
		अगर (synthesize_probe_trace_arg(&tev->args[i], &buf) < 0)
			जाओ error;

	ret = strbuf_detach(&buf, शून्य);
error:
	strbuf_release(&buf);
	वापस ret;
पूर्ण

अटल पूर्णांक find_perf_probe_poपूर्णांक_from_map(काष्ठा probe_trace_poपूर्णांक *tp,
					  काष्ठा perf_probe_poपूर्णांक *pp,
					  bool is_kprobe)
अणु
	काष्ठा symbol *sym = शून्य;
	काष्ठा map *map = शून्य;
	u64 addr = tp->address;
	पूर्णांक ret = -ENOENT;

	अगर (!is_kprobe) अणु
		map = dso__new_map(tp->module);
		अगर (!map)
			जाओ out;
		sym = map__find_symbol(map, addr);
	पूर्ण अन्यथा अणु
		अगर (tp->symbol && !addr) अणु
			अगर (kernel_get_symbol_address_by_name(tp->symbol,
						&addr, true, false) < 0)
				जाओ out;
		पूर्ण
		अगर (addr) अणु
			addr += tp->offset;
			sym = machine__find_kernel_symbol(host_machine, addr, &map);
		पूर्ण
	पूर्ण

	अगर (!sym)
		जाओ out;

	pp->retprobe = tp->retprobe;
	pp->offset = addr - map->unmap_ip(map, sym->start);
	pp->function = strdup(sym->name);
	ret = pp->function ? 0 : -ENOMEM;

out:
	अगर (map && !is_kprobe) अणु
		map__put(map);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक convert_to_perf_probe_poपूर्णांक(काष्ठा probe_trace_poपूर्णांक *tp,
				       काष्ठा perf_probe_poपूर्णांक *pp,
				       bool is_kprobe)
अणु
	अक्षर buf[128];
	पूर्णांक ret;

	ret = find_perf_probe_poपूर्णांक_from_dwarf(tp, pp, is_kprobe);
	अगर (!ret)
		वापस 0;
	ret = find_perf_probe_poपूर्णांक_from_map(tp, pp, is_kprobe);
	अगर (!ret)
		वापस 0;

	pr_debug("Failed to find probe point from both of dwarf and map.\n");

	अगर (tp->symbol) अणु
		pp->function = strdup(tp->symbol);
		pp->offset = tp->offset;
	पूर्ण अन्यथा अणु
		ret = e_snम_लिखो(buf, 128, "0x%" PRIx64, (u64)tp->address);
		अगर (ret < 0)
			वापस ret;
		pp->function = strdup(buf);
		pp->offset = 0;
	पूर्ण
	अगर (pp->function == शून्य)
		वापस -ENOMEM;

	pp->retprobe = tp->retprobe;

	वापस 0;
पूर्ण

अटल पूर्णांक convert_to_perf_probe_event(काष्ठा probe_trace_event *tev,
			       काष्ठा perf_probe_event *pev, bool is_kprobe)
अणु
	काष्ठा strbuf buf = STRBUF_INIT;
	पूर्णांक i, ret;

	/* Convert event/group name */
	pev->event = strdup(tev->event);
	pev->group = strdup(tev->group);
	अगर (pev->event == शून्य || pev->group == शून्य)
		वापस -ENOMEM;

	/* Convert trace_poपूर्णांक to probe_poपूर्णांक */
	ret = convert_to_perf_probe_poपूर्णांक(&tev->poपूर्णांक, &pev->poपूर्णांक, is_kprobe);
	अगर (ret < 0)
		वापस ret;

	/* Convert trace_arg to probe_arg */
	pev->nargs = tev->nargs;
	pev->args = zalloc(माप(काष्ठा perf_probe_arg) * pev->nargs);
	अगर (pev->args == शून्य)
		वापस -ENOMEM;
	क्रम (i = 0; i < tev->nargs && ret >= 0; i++) अणु
		अगर (tev->args[i].name)
			pev->args[i].name = strdup(tev->args[i].name);
		अन्यथा अणु
			अगर ((ret = strbuf_init(&buf, 32)) < 0)
				जाओ error;
			ret = synthesize_probe_trace_arg(&tev->args[i], &buf);
			pev->args[i].name = strbuf_detach(&buf, शून्य);
		पूर्ण
		अगर (pev->args[i].name == शून्य && ret >= 0)
			ret = -ENOMEM;
	पूर्ण
error:
	अगर (ret < 0)
		clear_perf_probe_event(pev);

	वापस ret;
पूर्ण

व्योम clear_perf_probe_event(काष्ठा perf_probe_event *pev)
अणु
	काष्ठा perf_probe_arg_field *field, *next;
	पूर्णांक i;

	zमुक्त(&pev->event);
	zमुक्त(&pev->group);
	zमुक्त(&pev->target);
	clear_perf_probe_poपूर्णांक(&pev->poपूर्णांक);

	क्रम (i = 0; i < pev->nargs; i++) अणु
		zमुक्त(&pev->args[i].name);
		zमुक्त(&pev->args[i].var);
		zमुक्त(&pev->args[i].type);
		field = pev->args[i].field;
		जबतक (field) अणु
			next = field->next;
			zमुक्त(&field->name);
			मुक्त(field);
			field = next;
		पूर्ण
	पूर्ण
	pev->nargs = 0;
	zमुक्त(&pev->args);
पूर्ण

#घोषणा strdup_or_जाओ(str, label)	\
(अणु अक्षर *__p = शून्य; अगर (str && !(__p = strdup(str))) जाओ label; __p; पूर्ण)

अटल पूर्णांक perf_probe_poपूर्णांक__copy(काष्ठा perf_probe_poपूर्णांक *dst,
				  काष्ठा perf_probe_poपूर्णांक *src)
अणु
	dst->file = strdup_or_जाओ(src->file, out_err);
	dst->function = strdup_or_जाओ(src->function, out_err);
	dst->lazy_line = strdup_or_जाओ(src->lazy_line, out_err);
	dst->line = src->line;
	dst->retprobe = src->retprobe;
	dst->offset = src->offset;
	वापस 0;

out_err:
	clear_perf_probe_poपूर्णांक(dst);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक perf_probe_arg__copy(काष्ठा perf_probe_arg *dst,
				काष्ठा perf_probe_arg *src)
अणु
	काष्ठा perf_probe_arg_field *field, **ppfield;

	dst->name = strdup_or_जाओ(src->name, out_err);
	dst->var = strdup_or_जाओ(src->var, out_err);
	dst->type = strdup_or_जाओ(src->type, out_err);

	field = src->field;
	ppfield = &(dst->field);
	जबतक (field) अणु
		*ppfield = zalloc(माप(*field));
		अगर (!*ppfield)
			जाओ out_err;
		(*ppfield)->name = strdup_or_जाओ(field->name, out_err);
		(*ppfield)->index = field->index;
		(*ppfield)->ref = field->ref;
		field = field->next;
		ppfield = &((*ppfield)->next);
	पूर्ण
	वापस 0;
out_err:
	वापस -ENOMEM;
पूर्ण

पूर्णांक perf_probe_event__copy(काष्ठा perf_probe_event *dst,
			   काष्ठा perf_probe_event *src)
अणु
	पूर्णांक i;

	dst->event = strdup_or_जाओ(src->event, out_err);
	dst->group = strdup_or_जाओ(src->group, out_err);
	dst->target = strdup_or_जाओ(src->target, out_err);
	dst->uprobes = src->uprobes;

	अगर (perf_probe_poपूर्णांक__copy(&dst->poपूर्णांक, &src->poपूर्णांक) < 0)
		जाओ out_err;

	dst->args = zalloc(माप(काष्ठा perf_probe_arg) * src->nargs);
	अगर (!dst->args)
		जाओ out_err;
	dst->nargs = src->nargs;

	क्रम (i = 0; i < src->nargs; i++)
		अगर (perf_probe_arg__copy(&dst->args[i], &src->args[i]) < 0)
			जाओ out_err;
	वापस 0;

out_err:
	clear_perf_probe_event(dst);
	वापस -ENOMEM;
पूर्ण

व्योम clear_probe_trace_event(काष्ठा probe_trace_event *tev)
अणु
	काष्ठा probe_trace_arg_ref *ref, *next;
	पूर्णांक i;

	zमुक्त(&tev->event);
	zमुक्त(&tev->group);
	zमुक्त(&tev->poपूर्णांक.symbol);
	zमुक्त(&tev->poपूर्णांक.realname);
	zमुक्त(&tev->poपूर्णांक.module);
	क्रम (i = 0; i < tev->nargs; i++) अणु
		zमुक्त(&tev->args[i].name);
		zमुक्त(&tev->args[i].value);
		zमुक्त(&tev->args[i].type);
		ref = tev->args[i].ref;
		जबतक (ref) अणु
			next = ref->next;
			मुक्त(ref);
			ref = next;
		पूर्ण
	पूर्ण
	zमुक्त(&tev->args);
	tev->nargs = 0;
पूर्ण

काष्ठा kprobe_blacklist_node अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ start;
	अचिन्हित दीर्घ end;
	अक्षर *symbol;
पूर्ण;

अटल व्योम kprobe_blacklist__delete(काष्ठा list_head *blacklist)
अणु
	काष्ठा kprobe_blacklist_node *node;

	जबतक (!list_empty(blacklist)) अणु
		node = list_first_entry(blacklist,
					काष्ठा kprobe_blacklist_node, list);
		list_del_init(&node->list);
		zमुक्त(&node->symbol);
		मुक्त(node);
	पूर्ण
पूर्ण

अटल पूर्णांक kprobe_blacklist__load(काष्ठा list_head *blacklist)
अणु
	काष्ठा kprobe_blacklist_node *node;
	स्थिर अक्षर *__debugfs = debugfs__mountpoपूर्णांक();
	अक्षर buf[PATH_MAX], *p;
	खाता *fp;
	पूर्णांक ret;

	अगर (__debugfs == शून्य)
		वापस -ENOTSUP;

	ret = e_snम_लिखो(buf, PATH_MAX, "%s/kprobes/blacklist", __debugfs);
	अगर (ret < 0)
		वापस ret;

	fp = ख_खोलो(buf, "r");
	अगर (!fp)
		वापस -त्रुटि_सं;

	ret = 0;
	जबतक (ख_माला_लो(buf, PATH_MAX, fp)) अणु
		node = zalloc(माप(*node));
		अगर (!node) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		INIT_LIST_HEAD(&node->list);
		list_add_tail(&node->list, blacklist);
		अगर (माला_पूछो(buf, "0x%lx-0x%lx", &node->start, &node->end) != 2) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		p = म_अक्षर(buf, '\t');
		अगर (p) अणु
			p++;
			अगर (p[म_माप(p) - 1] == '\n')
				p[म_माप(p) - 1] = '\0';
		पूर्ण अन्यथा
			p = (अक्षर *)"unknown";
		node->symbol = strdup(p);
		अगर (!node->symbol) अणु
			ret = -ENOMEM;
			अवरोध;
		पूर्ण
		pr_debug2("Blacklist: 0x%lx-0x%lx, %s\n",
			  node->start, node->end, node->symbol);
		ret++;
	पूर्ण
	अगर (ret < 0)
		kprobe_blacklist__delete(blacklist);
	ख_बंद(fp);

	वापस ret;
पूर्ण

अटल काष्ठा kprobe_blacklist_node *
kprobe_blacklist__find_by_address(काष्ठा list_head *blacklist,
				  अचिन्हित दीर्घ address)
अणु
	काष्ठा kprobe_blacklist_node *node;

	list_क्रम_each_entry(node, blacklist, list) अणु
		अगर (node->start <= address && address < node->end)
			वापस node;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल LIST_HEAD(kprobe_blacklist);

अटल व्योम kprobe_blacklist__init(व्योम)
अणु
	अगर (!list_empty(&kprobe_blacklist))
		वापस;

	अगर (kprobe_blacklist__load(&kprobe_blacklist) < 0)
		pr_debug("No kprobe blacklist support, ignored\n");
पूर्ण

अटल व्योम kprobe_blacklist__release(व्योम)
अणु
	kprobe_blacklist__delete(&kprobe_blacklist);
पूर्ण

अटल bool kprobe_blacklist__listed(अचिन्हित दीर्घ address)
अणु
	वापस !!kprobe_blacklist__find_by_address(&kprobe_blacklist, address);
पूर्ण

अटल पूर्णांक perf_probe_event__प्र_लिखो(स्थिर अक्षर *group, स्थिर अक्षर *event,
				     काष्ठा perf_probe_event *pev,
				     स्थिर अक्षर *module,
				     काष्ठा strbuf *result)
अणु
	पूर्णांक i, ret;
	अक्षर *buf;

	अगर (aप्र_लिखो(&buf, "%s:%s", group, event) < 0)
		वापस -त्रुटि_सं;
	ret = strbuf_addf(result, "  %-20s (on ", buf);
	मुक्त(buf);
	अगर (ret)
		वापस ret;

	/* Synthesize only event probe poपूर्णांक */
	buf = synthesize_perf_probe_poपूर्णांक(&pev->poपूर्णांक);
	अगर (!buf)
		वापस -ENOMEM;
	ret = strbuf_addstr(result, buf);
	मुक्त(buf);

	अगर (!ret && module)
		ret = strbuf_addf(result, " in %s", module);

	अगर (!ret && pev->nargs > 0) अणु
		ret = strbuf_add(result, " with", 5);
		क्रम (i = 0; !ret && i < pev->nargs; i++) अणु
			buf = synthesize_perf_probe_arg(&pev->args[i]);
			अगर (!buf)
				वापस -ENOMEM;
			ret = strbuf_addf(result, " %s", buf);
			मुक्त(buf);
		पूर्ण
	पूर्ण
	अगर (!ret)
		ret = strbuf_addch(result, ')');

	वापस ret;
पूर्ण

/* Show an event */
पूर्णांक show_perf_probe_event(स्थिर अक्षर *group, स्थिर अक्षर *event,
			  काष्ठा perf_probe_event *pev,
			  स्थिर अक्षर *module, bool use_मानक_निकास)
अणु
	काष्ठा strbuf buf = STRBUF_INIT;
	पूर्णांक ret;

	ret = perf_probe_event__प्र_लिखो(group, event, pev, module, &buf);
	अगर (ret >= 0) अणु
		अगर (use_मानक_निकास)
			म_लिखो("%s\n", buf.buf);
		अन्यथा
			pr_info("%s\n", buf.buf);
	पूर्ण
	strbuf_release(&buf);

	वापस ret;
पूर्ण

अटल bool filter_probe_trace_event(काष्ठा probe_trace_event *tev,
				     काष्ठा strfilter *filter)
अणु
	अक्षर पंचांगp[128];

	/* At first, check the event name itself */
	अगर (strfilter__compare(filter, tev->event))
		वापस true;

	/* Next, check the combination of name and group */
	अगर (e_snम_लिखो(पंचांगp, 128, "%s:%s", tev->group, tev->event) < 0)
		वापस false;
	वापस strfilter__compare(filter, पंचांगp);
पूर्ण

अटल पूर्णांक __show_perf_probe_events(पूर्णांक fd, bool is_kprobe,
				    काष्ठा strfilter *filter)
अणु
	पूर्णांक ret = 0;
	काष्ठा probe_trace_event tev;
	काष्ठा perf_probe_event pev;
	काष्ठा strlist *rawlist;
	काष्ठा str_node *ent;

	स_रखो(&tev, 0, माप(tev));
	स_रखो(&pev, 0, माप(pev));

	rawlist = probe_file__get_rawlist(fd);
	अगर (!rawlist)
		वापस -ENOMEM;

	strlist__क्रम_each_entry(ent, rawlist) अणु
		ret = parse_probe_trace_command(ent->s, &tev);
		अगर (ret >= 0) अणु
			अगर (!filter_probe_trace_event(&tev, filter))
				जाओ next;
			ret = convert_to_perf_probe_event(&tev, &pev,
								is_kprobe);
			अगर (ret < 0)
				जाओ next;
			ret = show_perf_probe_event(pev.group, pev.event,
						    &pev, tev.poपूर्णांक.module,
						    true);
		पूर्ण
next:
		clear_perf_probe_event(&pev);
		clear_probe_trace_event(&tev);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	strlist__delete(rawlist);
	/* Cleanup cached debuginfo अगर needed */
	debuginfo_cache__निकास();

	वापस ret;
पूर्ण

/* List up current perf-probe events */
पूर्णांक show_perf_probe_events(काष्ठा strfilter *filter)
अणु
	पूर्णांक kp_fd, up_fd, ret;

	setup_pager();

	अगर (probe_conf.cache)
		वापस probe_cache__show_all_caches(filter);

	ret = init_probe_symbol_maps(false);
	अगर (ret < 0)
		वापस ret;

	ret = probe_file__खोलो_both(&kp_fd, &up_fd, 0);
	अगर (ret < 0)
		वापस ret;

	अगर (kp_fd >= 0)
		ret = __show_perf_probe_events(kp_fd, true, filter);
	अगर (up_fd >= 0 && ret >= 0)
		ret = __show_perf_probe_events(up_fd, false, filter);
	अगर (kp_fd > 0)
		बंद(kp_fd);
	अगर (up_fd > 0)
		बंद(up_fd);
	निकास_probe_symbol_maps();

	वापस ret;
पूर्ण

अटल पूर्णांक get_new_event_name(अक्षर *buf, माप_प्रकार len, स्थिर अक्षर *base,
			      काष्ठा strlist *namelist, bool ret_event,
			      bool allow_suffix)
अणु
	पूर्णांक i, ret;
	अक्षर *p, *nbase;

	अगर (*base == '.')
		base++;
	nbase = strdup(base);
	अगर (!nbase)
		वापस -ENOMEM;

	/* Cut off the करोt suffixes (e.g. .स्थिर, .isra) and version suffixes */
	p = strpbrk(nbase, ".@");
	अगर (p && p != nbase)
		*p = '\0';

	/* Try no suffix number */
	ret = e_snम_लिखो(buf, len, "%s%s", nbase, ret_event ? "__return" : "");
	अगर (ret < 0) अणु
		pr_debug("snprintf() failed: %d\n", ret);
		जाओ out;
	पूर्ण
	अगर (!strlist__has_entry(namelist, buf))
		जाओ out;

	अगर (!allow_suffix) अणु
		pr_warning("Error: event \"%s\" already exists.\n"
			   " Hint: Remove existing event by 'perf probe -d'\n"
			   "       or force duplicates by 'perf probe -f'\n"
			   "       or set 'force=yes' in BPF source.\n",
			   buf);
		ret = -EEXIST;
		जाओ out;
	पूर्ण

	/* Try to add suffix */
	क्रम (i = 1; i < MAX_EVENT_INDEX; i++) अणु
		ret = e_snम_लिखो(buf, len, "%s_%d", nbase, i);
		अगर (ret < 0) अणु
			pr_debug("snprintf() failed: %d\n", ret);
			जाओ out;
		पूर्ण
		अगर (!strlist__has_entry(namelist, buf))
			अवरोध;
	पूर्ण
	अगर (i == MAX_EVENT_INDEX) अणु
		pr_warning("Too many events are on the same function.\n");
		ret = -दुस्फल;
	पूर्ण

out:
	मुक्त(nbase);

	/* Final validation */
	अगर (ret >= 0 && !is_c_func_name(buf)) अणु
		pr_warning("Internal error: \"%s\" is an invalid event name.\n",
			   buf);
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/* Warn अगर the current kernel's uprobe implementation is old */
अटल व्योम warn_uprobe_event_compat(काष्ठा probe_trace_event *tev)
अणु
	पूर्णांक i;
	अक्षर *buf = synthesize_probe_trace_command(tev);
	काष्ठा probe_trace_poपूर्णांक *tp = &tev->poपूर्णांक;

	अगर (tp->ref_ctr_offset && !uprobe_ref_ctr_is_supported()) अणु
		pr_warning("A semaphore is associated with %s:%s and "
			   "seems your kernel doesn't support it.\n",
			   tev->group, tev->event);
	पूर्ण

	/* Old uprobe event करोesn't support memory dereference */
	अगर (!tev->uprobes || tev->nargs == 0 || !buf)
		जाओ out;

	क्रम (i = 0; i < tev->nargs; i++)
		अगर (strglobmatch(tev->args[i].value, "[$@+-]*")) अणु
			pr_warning("Please upgrade your kernel to at least "
				   "3.14 to have access to feature %s\n",
				   tev->args[i].value);
			अवरोध;
		पूर्ण
out:
	मुक्त(buf);
पूर्ण

/* Set new name from original perf_probe_event and namelist */
अटल पूर्णांक probe_trace_event__set_name(काष्ठा probe_trace_event *tev,
				       काष्ठा perf_probe_event *pev,
				       काष्ठा strlist *namelist,
				       bool allow_suffix)
अणु
	स्थिर अक्षर *event, *group;
	अक्षर buf[64];
	पूर्णांक ret;

	/* If probe_event or trace_event alपढ़ोy have the name, reuse it */
	अगर (pev->event && !pev->sdt)
		event = pev->event;
	अन्यथा अगर (tev->event)
		event = tev->event;
	अन्यथा अणु
		/* Or generate new one from probe poपूर्णांक */
		अगर (pev->poपूर्णांक.function &&
			(म_भेदन(pev->poपूर्णांक.function, "0x", 2) != 0) &&
			!strisglob(pev->poपूर्णांक.function))
			event = pev->poपूर्णांक.function;
		अन्यथा
			event = tev->poपूर्णांक.realname;
	पूर्ण
	अगर (pev->group && !pev->sdt)
		group = pev->group;
	अन्यथा अगर (tev->group)
		group = tev->group;
	अन्यथा
		group = PERFPROBE_GROUP;

	/* Get an unused new event name */
	ret = get_new_event_name(buf, 64, event, namelist,
				 tev->poपूर्णांक.retprobe, allow_suffix);
	अगर (ret < 0)
		वापस ret;

	event = buf;

	tev->event = strdup(event);
	tev->group = strdup(group);
	अगर (tev->event == शून्य || tev->group == शून्य)
		वापस -ENOMEM;

	/*
	 * Add new event name to namelist अगर multiprobe event is NOT
	 * supported, since we have to use new event name क्रम following
	 * probes in that हाल.
	 */
	अगर (!multiprobe_event_is_supported())
		strlist__add(namelist, event);
	वापस 0;
पूर्ण

अटल पूर्णांक __खोलो_probe_file_and_namelist(bool uprobe,
					  काष्ठा strlist **namelist)
अणु
	पूर्णांक fd;

	fd = probe_file__खोलो(PF_FL_RW | (uprobe ? PF_FL_UPROBE : 0));
	अगर (fd < 0)
		वापस fd;

	/* Get current event names */
	*namelist = probe_file__get_namelist(fd);
	अगर (!(*namelist)) अणु
		pr_debug("Failed to get current event list.\n");
		बंद(fd);
		वापस -ENOMEM;
	पूर्ण
	वापस fd;
पूर्ण

अटल पूर्णांक __add_probe_trace_events(काष्ठा perf_probe_event *pev,
				     काष्ठा probe_trace_event *tevs,
				     पूर्णांक ntevs, bool allow_suffix)
अणु
	पूर्णांक i, fd[2] = अणु-1, -1पूर्ण, up, ret;
	काष्ठा probe_trace_event *tev = शून्य;
	काष्ठा probe_cache *cache = शून्य;
	काष्ठा strlist *namelist[2] = अणुशून्य, शून्यपूर्ण;
	काष्ठा nscookie nsc;

	up = pev->uprobes ? 1 : 0;
	fd[up] = __खोलो_probe_file_and_namelist(up, &namelist[up]);
	अगर (fd[up] < 0)
		वापस fd[up];

	ret = 0;
	क्रम (i = 0; i < ntevs; i++) अणु
		tev = &tevs[i];
		up = tev->uprobes ? 1 : 0;
		अगर (fd[up] == -1) अणु	/* Open the kprobe/uprobe_events */
			fd[up] = __खोलो_probe_file_and_namelist(up,
								&namelist[up]);
			अगर (fd[up] < 0)
				जाओ बंद_out;
		पूर्ण
		/* Skip अगर the symbol is out of .text or blacklisted */
		अगर (!tev->poपूर्णांक.symbol && !pev->uprobes)
			जारी;

		/* Set new name क्रम tev (and update namelist) */
		ret = probe_trace_event__set_name(tev, pev, namelist[up],
						  allow_suffix);
		अगर (ret < 0)
			अवरोध;

		nsinfo__mountns_enter(pev->nsi, &nsc);
		ret = probe_file__add_event(fd[up], tev);
		nsinfo__mountns_निकास(&nsc);
		अगर (ret < 0)
			अवरोध;

		/*
		 * Probes after the first probe which comes from same
		 * user input are always allowed to add suffix, because
		 * there might be several addresses corresponding to
		 * one code line.
		 */
		allow_suffix = true;
	पूर्ण
	अगर (ret == -EINVAL && pev->uprobes)
		warn_uprobe_event_compat(tev);
	अगर (ret == 0 && probe_conf.cache) अणु
		cache = probe_cache__new(pev->target, pev->nsi);
		अगर (!cache ||
		    probe_cache__add_entry(cache, pev, tevs, ntevs) < 0 ||
		    probe_cache__commit(cache) < 0)
			pr_warning("Failed to add event to probe cache\n");
		probe_cache__delete(cache);
	पूर्ण

बंद_out:
	क्रम (up = 0; up < 2; up++) अणु
		strlist__delete(namelist[up]);
		अगर (fd[up] >= 0)
			बंद(fd[up]);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक find_probe_functions(काष्ठा map *map, अक्षर *name,
				काष्ठा symbol **syms)
अणु
	पूर्णांक found = 0;
	काष्ठा symbol *sym;
	काष्ठा rb_node *पंचांगp;
	स्थिर अक्षर *norm, *ver;
	अक्षर *buf = शून्य;
	bool cut_version = true;

	अगर (map__load(map) < 0)
		वापस 0;

	/* If user gives a version, करोn't cut off the version from symbols */
	अगर (म_अक्षर(name, '@'))
		cut_version = false;

	map__क्रम_each_symbol(map, sym, पंचांगp) अणु
		norm = arch__normalize_symbol_name(sym->name);
		अगर (!norm)
			जारी;

		अगर (cut_version) अणु
			/* We करोn't care about शेष symbol or not */
			ver = म_अक्षर(norm, '@');
			अगर (ver) अणु
				buf = strndup(norm, ver - norm);
				अगर (!buf)
					वापस -ENOMEM;
				norm = buf;
			पूर्ण
		पूर्ण

		अगर (strglobmatch(norm, name)) अणु
			found++;
			अगर (syms && found < probe_conf.max_probes)
				syms[found - 1] = sym;
		पूर्ण
		अगर (buf)
			zमुक्त(&buf);
	पूर्ण

	वापस found;
पूर्ण

व्योम __weak arch__fix_tev_from_maps(काष्ठा perf_probe_event *pev __maybe_unused,
				काष्ठा probe_trace_event *tev __maybe_unused,
				काष्ठा map *map __maybe_unused,
				काष्ठा symbol *sym __maybe_unused) अणु पूर्ण

/*
 * Find probe function addresses from map.
 * Return an error or the number of found probe_trace_event
 */
अटल पूर्णांक find_probe_trace_events_from_map(काष्ठा perf_probe_event *pev,
					    काष्ठा probe_trace_event **tevs)
अणु
	काष्ठा map *map = शून्य;
	काष्ठा ref_reloc_sym *reloc_sym = शून्य;
	काष्ठा symbol *sym;
	काष्ठा symbol **syms = शून्य;
	काष्ठा probe_trace_event *tev;
	काष्ठा perf_probe_poपूर्णांक *pp = &pev->poपूर्णांक;
	काष्ठा probe_trace_poपूर्णांक *tp;
	पूर्णांक num_matched_functions;
	पूर्णांक ret, i, j, skipped = 0;
	अक्षर *mod_name;

	map = get_target_map(pev->target, pev->nsi, pev->uprobes);
	अगर (!map) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	syms = दो_स्मृति(माप(काष्ठा symbol *) * probe_conf.max_probes);
	अगर (!syms) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	/*
	 * Load matched symbols: Since the dअगरferent local symbols may have
	 * same name but dअगरferent addresses, this lists all the symbols.
	 */
	num_matched_functions = find_probe_functions(map, pp->function, syms);
	अगर (num_matched_functions <= 0) अणु
		pr_err("Failed to find symbol %s in %s\n", pp->function,
			pev->target ? : "kernel");
		ret = -ENOENT;
		जाओ out;
	पूर्ण अन्यथा अगर (num_matched_functions > probe_conf.max_probes) अणु
		pr_err("Too many functions matched in %s\n",
			pev->target ? : "kernel");
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	/* Note that the symbols in the kmodule are not relocated */
	अगर (!pev->uprobes && !pev->target &&
			(!pp->retprobe || kretprobe_offset_is_supported())) अणु
		reloc_sym = kernel_get_ref_reloc_sym(शून्य);
		अगर (!reloc_sym) अणु
			pr_warning("Relocated base symbol is not found!\n");
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Setup result trace-probe-events */
	*tevs = zalloc(माप(*tev) * num_matched_functions);
	अगर (!*tevs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = 0;

	क्रम (j = 0; j < num_matched_functions; j++) अणु
		sym = syms[j];

		/* There can be duplicated symbols in the map */
		क्रम (i = 0; i < j; i++)
			अगर (sym->start == syms[i]->start) अणु
				pr_debug("Found duplicated symbol %s @ %" PRIx64 "\n",
					 sym->name, sym->start);
				अवरोध;
			पूर्ण
		अगर (i != j)
			जारी;

		tev = (*tevs) + ret;
		tp = &tev->poपूर्णांक;
		अगर (ret == num_matched_functions) अणु
			pr_warning("Too many symbols are listed. Skip it.\n");
			अवरोध;
		पूर्ण
		ret++;

		अगर (pp->offset > sym->end - sym->start) अणु
			pr_warning("Offset %ld is bigger than the size of %s\n",
				   pp->offset, sym->name);
			ret = -ENOENT;
			जाओ err_out;
		पूर्ण
		/* Add one probe poपूर्णांक */
		tp->address = map->unmap_ip(map, sym->start) + pp->offset;

		/* Check the kprobe (not in module) is within .text  */
		अगर (!pev->uprobes && !pev->target &&
		    kprobe_warn_out_range(sym->name, tp->address)) अणु
			tp->symbol = शून्य;	/* Skip it */
			skipped++;
		पूर्ण अन्यथा अगर (reloc_sym) अणु
			tp->symbol = strdup_or_जाओ(reloc_sym->name, nomem_out);
			tp->offset = tp->address - reloc_sym->addr;
		पूर्ण अन्यथा अणु
			tp->symbol = strdup_or_जाओ(sym->name, nomem_out);
			tp->offset = pp->offset;
		पूर्ण
		tp->realname = strdup_or_जाओ(sym->name, nomem_out);

		tp->retprobe = pp->retprobe;
		अगर (pev->target) अणु
			अगर (pev->uprobes) अणु
				tev->poपूर्णांक.module = strdup_or_जाओ(pev->target,
								   nomem_out);
			पूर्ण अन्यथा अणु
				mod_name = find_module_name(pev->target);
				tev->poपूर्णांक.module =
					strdup(mod_name ? mod_name : pev->target);
				मुक्त(mod_name);
				अगर (!tev->poपूर्णांक.module)
					जाओ nomem_out;
			पूर्ण
		पूर्ण
		tev->uprobes = pev->uprobes;
		tev->nargs = pev->nargs;
		अगर (tev->nargs) अणु
			tev->args = zalloc(माप(काष्ठा probe_trace_arg) *
					   tev->nargs);
			अगर (tev->args == शून्य)
				जाओ nomem_out;
		पूर्ण
		क्रम (i = 0; i < tev->nargs; i++) अणु
			अगर (pev->args[i].name)
				tev->args[i].name =
					strdup_or_जाओ(pev->args[i].name,
							nomem_out);

			tev->args[i].value = strdup_or_जाओ(pev->args[i].var,
							    nomem_out);
			अगर (pev->args[i].type)
				tev->args[i].type =
					strdup_or_जाओ(pev->args[i].type,
							nomem_out);
		पूर्ण
		arch__fix_tev_from_maps(pev, tev, map, sym);
	पूर्ण
	अगर (ret == skipped) अणु
		ret = -ENOENT;
		जाओ err_out;
	पूर्ण

out:
	map__put(map);
	मुक्त(syms);
	वापस ret;

nomem_out:
	ret = -ENOMEM;
err_out:
	clear_probe_trace_events(*tevs, num_matched_functions);
	zमुक्त(tevs);
	जाओ out;
पूर्ण

अटल पूर्णांक try_to_find_असलolute_address(काष्ठा perf_probe_event *pev,
					काष्ठा probe_trace_event **tevs)
अणु
	काष्ठा perf_probe_poपूर्णांक *pp = &pev->poपूर्णांक;
	काष्ठा probe_trace_event *tev;
	काष्ठा probe_trace_poपूर्णांक *tp;
	पूर्णांक i, err;

	अगर (!(pev->poपूर्णांक.function && !म_भेदन(pev->poपूर्णांक.function, "0x", 2)))
		वापस -EINVAL;
	अगर (perf_probe_event_need_dwarf(pev))
		वापस -EINVAL;

	/*
	 * This is 'perf probe /lib/libc.so 0xabcd'. Try to probe at
	 * असलolute address.
	 *
	 * Only one tev can be generated by this.
	 */
	*tevs = zalloc(माप(*tev));
	अगर (!*tevs)
		वापस -ENOMEM;

	tev = *tevs;
	tp = &tev->poपूर्णांक;

	/*
	 * Don't use tp->offset, use address directly, because
	 * in synthesize_probe_trace_command() address cannot be
	 * zero.
	 */
	tp->address = pev->poपूर्णांक.असल_address;
	tp->retprobe = pp->retprobe;
	tev->uprobes = pev->uprobes;

	err = -ENOMEM;
	/*
	 * Give it a '0x' leading symbol name.
	 * In __add_probe_trace_events, a शून्य symbol is पूर्णांकerpreted as
	 * invalid.
	 */
	अगर (aप्र_लिखो(&tp->symbol, "0x%lx", tp->address) < 0)
		जाओ errout;

	/* For kprobe, check range */
	अगर ((!tev->uprobes) &&
	    (kprobe_warn_out_range(tev->poपूर्णांक.symbol,
				   tev->poपूर्णांक.address))) अणु
		err = -EACCES;
		जाओ errout;
	पूर्ण

	अगर (aप्र_लिखो(&tp->realname, "abs_%lx", tp->address) < 0)
		जाओ errout;

	अगर (pev->target) अणु
		tp->module = strdup(pev->target);
		अगर (!tp->module)
			जाओ errout;
	पूर्ण

	अगर (tev->group) अणु
		tev->group = strdup(pev->group);
		अगर (!tev->group)
			जाओ errout;
	पूर्ण

	अगर (pev->event) अणु
		tev->event = strdup(pev->event);
		अगर (!tev->event)
			जाओ errout;
	पूर्ण

	tev->nargs = pev->nargs;
	tev->args = zalloc(माप(काष्ठा probe_trace_arg) * tev->nargs);
	अगर (!tev->args)
		जाओ errout;

	क्रम (i = 0; i < tev->nargs; i++)
		copy_to_probe_trace_arg(&tev->args[i], &pev->args[i]);

	वापस 1;

errout:
	clear_probe_trace_events(*tevs, 1);
	*tevs = शून्य;
	वापस err;
पूर्ण

/* Concatenate two arrays */
अटल व्योम *memcat(व्योम *a, माप_प्रकार sz_a, व्योम *b, माप_प्रकार sz_b)
अणु
	व्योम *ret;

	ret = दो_स्मृति(sz_a + sz_b);
	अगर (ret) अणु
		स_नकल(ret, a, sz_a);
		स_नकल(ret + sz_a, b, sz_b);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक
concat_probe_trace_events(काष्ठा probe_trace_event **tevs, पूर्णांक *ntevs,
			  काष्ठा probe_trace_event **tevs2, पूर्णांक ntevs2)
अणु
	काष्ठा probe_trace_event *new_tevs;
	पूर्णांक ret = 0;

	अगर (*ntevs == 0) अणु
		*tevs = *tevs2;
		*ntevs = ntevs2;
		*tevs2 = शून्य;
		वापस 0;
	पूर्ण

	अगर (*ntevs + ntevs2 > probe_conf.max_probes)
		ret = -E2BIG;
	अन्यथा अणु
		/* Concatenate the array of probe_trace_event */
		new_tevs = memcat(*tevs, (*ntevs) * माप(**tevs),
				  *tevs2, ntevs2 * माप(**tevs2));
		अगर (!new_tevs)
			ret = -ENOMEM;
		अन्यथा अणु
			मुक्त(*tevs);
			*tevs = new_tevs;
			*ntevs += ntevs2;
		पूर्ण
	पूर्ण
	अगर (ret < 0)
		clear_probe_trace_events(*tevs2, ntevs2);
	zमुक्त(tevs2);

	वापस ret;
पूर्ण

/*
 * Try to find probe_trace_event from given probe caches. Return the number
 * of cached events found, अगर an error occurs वापस the error.
 */
अटल पूर्णांक find_cached_events(काष्ठा perf_probe_event *pev,
			      काष्ठा probe_trace_event **tevs,
			      स्थिर अक्षर *target)
अणु
	काष्ठा probe_cache *cache;
	काष्ठा probe_cache_entry *entry;
	काष्ठा probe_trace_event *पंचांगp_tevs = शून्य;
	पूर्णांक ntevs = 0;
	पूर्णांक ret = 0;

	cache = probe_cache__new(target, pev->nsi);
	/* Return 0 ("not found") अगर the target has no probe cache. */
	अगर (!cache)
		वापस 0;

	क्रम_each_probe_cache_entry(entry, cache) अणु
		/* Skip the cache entry which has no name */
		अगर (!entry->pev.event || !entry->pev.group)
			जारी;
		अगर ((!pev->group || strglobmatch(entry->pev.group, pev->group)) &&
		    strglobmatch(entry->pev.event, pev->event)) अणु
			ret = probe_cache_entry__get_event(entry, &पंचांगp_tevs);
			अगर (ret > 0)
				ret = concat_probe_trace_events(tevs, &ntevs,
								&पंचांगp_tevs, ret);
			अगर (ret < 0)
				अवरोध;
		पूर्ण
	पूर्ण
	probe_cache__delete(cache);
	अगर (ret < 0) अणु
		clear_probe_trace_events(*tevs, ntevs);
		zमुक्त(tevs);
	पूर्ण अन्यथा अणु
		ret = ntevs;
		अगर (ntevs > 0 && target && target[0] == '/')
			pev->uprobes = true;
	पूर्ण

	वापस ret;
पूर्ण

/* Try to find probe_trace_event from all probe caches */
अटल पूर्णांक find_cached_events_all(काष्ठा perf_probe_event *pev,
				   काष्ठा probe_trace_event **tevs)
अणु
	काष्ठा probe_trace_event *पंचांगp_tevs = शून्य;
	काष्ठा strlist *bidlist;
	काष्ठा str_node *nd;
	अक्षर *pathname;
	पूर्णांक ntevs = 0;
	पूर्णांक ret;

	/* Get the buildid list of all valid caches */
	bidlist = build_id_cache__list_all(true);
	अगर (!bidlist) अणु
		ret = -त्रुटि_सं;
		pr_debug("Failed to get buildids: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = 0;
	strlist__क्रम_each_entry(nd, bidlist) अणु
		pathname = build_id_cache__origname(nd->s);
		ret = find_cached_events(pev, &पंचांगp_tevs, pathname);
		/* In the हाल of cnt == 0, we just skip it */
		अगर (ret > 0)
			ret = concat_probe_trace_events(tevs, &ntevs,
							&पंचांगp_tevs, ret);
		मुक्त(pathname);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	strlist__delete(bidlist);

	अगर (ret < 0) अणु
		clear_probe_trace_events(*tevs, ntevs);
		zमुक्त(tevs);
	पूर्ण अन्यथा
		ret = ntevs;

	वापस ret;
पूर्ण

अटल पूर्णांक find_probe_trace_events_from_cache(काष्ठा perf_probe_event *pev,
					      काष्ठा probe_trace_event **tevs)
अणु
	काष्ठा probe_cache *cache;
	काष्ठा probe_cache_entry *entry;
	काष्ठा probe_trace_event *tev;
	काष्ठा str_node *node;
	पूर्णांक ret, i;

	अगर (pev->sdt) अणु
		/* For SDT/cached events, we use special search functions */
		अगर (!pev->target)
			वापस find_cached_events_all(pev, tevs);
		अन्यथा
			वापस find_cached_events(pev, tevs, pev->target);
	पूर्ण
	cache = probe_cache__new(pev->target, pev->nsi);
	अगर (!cache)
		वापस 0;

	entry = probe_cache__find(cache, pev);
	अगर (!entry) अणु
		/* SDT must be in the cache */
		ret = pev->sdt ? -ENOENT : 0;
		जाओ out;
	पूर्ण

	ret = strlist__nr_entries(entry->tevlist);
	अगर (ret > probe_conf.max_probes) अणु
		pr_debug("Too many entries matched in the cache of %s\n",
			 pev->target ? : "kernel");
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	*tevs = zalloc(ret * माप(*tev));
	अगर (!*tevs) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	i = 0;
	strlist__क्रम_each_entry(node, entry->tevlist) अणु
		tev = &(*tevs)[i++];
		ret = parse_probe_trace_command(node->s, tev);
		अगर (ret < 0)
			जाओ out;
		/* Set the uprobes attribute as same as original */
		tev->uprobes = pev->uprobes;
	पूर्ण
	ret = i;

out:
	probe_cache__delete(cache);
	वापस ret;
पूर्ण

अटल पूर्णांक convert_to_probe_trace_events(काष्ठा perf_probe_event *pev,
					 काष्ठा probe_trace_event **tevs)
अणु
	पूर्णांक ret;

	अगर (!pev->group && !pev->sdt) अणु
		/* Set group name अगर not given */
		अगर (!pev->uprobes) अणु
			pev->group = strdup(PERFPROBE_GROUP);
			ret = pev->group ? 0 : -ENOMEM;
		पूर्ण अन्यथा
			ret = convert_exec_to_group(pev->target, &pev->group);
		अगर (ret != 0) अणु
			pr_warning("Failed to make a group name.\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ret = try_to_find_असलolute_address(pev, tevs);
	अगर (ret > 0)
		वापस ret;

	/* At first, we need to lookup cache entry */
	ret = find_probe_trace_events_from_cache(pev, tevs);
	अगर (ret > 0 || pev->sdt)	/* SDT can be found only in the cache */
		वापस ret == 0 ? -ENOENT : ret; /* Found in probe cache */

	/* Convert perf_probe_event with debuginfo */
	ret = try_to_find_probe_trace_events(pev, tevs);
	अगर (ret != 0)
		वापस ret;	/* Found in debuginfo or got an error */

	वापस find_probe_trace_events_from_map(pev, tevs);
पूर्ण

पूर्णांक convert_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs)
अणु
	पूर्णांक i, ret;

	/* Loop 1: convert all events */
	क्रम (i = 0; i < npevs; i++) अणु
		/* Init kprobe blacklist अगर needed */
		अगर (!pevs[i].uprobes)
			kprobe_blacklist__init();
		/* Convert with or without debuginfo */
		ret  = convert_to_probe_trace_events(&pevs[i], &pevs[i].tevs);
		अगर (ret < 0)
			वापस ret;
		pevs[i].ntevs = ret;
	पूर्ण
	/* This just release blacklist only अगर allocated */
	kprobe_blacklist__release();

	वापस 0;
पूर्ण

अटल पूर्णांक show_probe_trace_event(काष्ठा probe_trace_event *tev)
अणु
	अक्षर *buf = synthesize_probe_trace_command(tev);

	अगर (!buf) अणु
		pr_debug("Failed to synthesize probe trace event.\n");
		वापस -EINVAL;
	पूर्ण

	/* Showing definition always go मानक_निकास */
	म_लिखो("%s\n", buf);
	मुक्त(buf);

	वापस 0;
पूर्ण

पूर्णांक show_probe_trace_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs)
अणु
	काष्ठा strlist *namelist = strlist__new(शून्य, शून्य);
	काष्ठा probe_trace_event *tev;
	काष्ठा perf_probe_event *pev;
	पूर्णांक i, j, ret = 0;

	अगर (!namelist)
		वापस -ENOMEM;

	क्रम (j = 0; j < npevs && !ret; j++) अणु
		pev = &pevs[j];
		क्रम (i = 0; i < pev->ntevs && !ret; i++) अणु
			tev = &pev->tevs[i];
			/* Skip अगर the symbol is out of .text or blacklisted */
			अगर (!tev->poपूर्णांक.symbol && !pev->uprobes)
				जारी;

			/* Set new name क्रम tev (and update namelist) */
			ret = probe_trace_event__set_name(tev, pev,
							  namelist, true);
			अगर (!ret)
				ret = show_probe_trace_event(tev);
		पूर्ण
	पूर्ण
	strlist__delete(namelist);

	वापस ret;
पूर्ण

पूर्णांक apply_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs)
अणु
	पूर्णांक i, ret = 0;

	/* Loop 2: add all events */
	क्रम (i = 0; i < npevs; i++) अणु
		ret = __add_probe_trace_events(&pevs[i], pevs[i].tevs,
					       pevs[i].ntevs,
					       probe_conf.क्रमce_add);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

व्योम cleanup_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs)
अणु
	पूर्णांक i, j;
	काष्ठा perf_probe_event *pev;

	/* Loop 3: cleanup and मुक्त trace events  */
	क्रम (i = 0; i < npevs; i++) अणु
		pev = &pevs[i];
		क्रम (j = 0; j < pevs[i].ntevs; j++)
			clear_probe_trace_event(&pevs[i].tevs[j]);
		zमुक्त(&pevs[i].tevs);
		pevs[i].ntevs = 0;
		nsinfo__zput(pev->nsi);
		clear_perf_probe_event(&pevs[i]);
	पूर्ण
पूर्ण

पूर्णांक add_perf_probe_events(काष्ठा perf_probe_event *pevs, पूर्णांक npevs)
अणु
	पूर्णांक ret;

	ret = init_probe_symbol_maps(pevs->uprobes);
	अगर (ret < 0)
		वापस ret;

	ret = convert_perf_probe_events(pevs, npevs);
	अगर (ret == 0)
		ret = apply_perf_probe_events(pevs, npevs);

	cleanup_perf_probe_events(pevs, npevs);

	निकास_probe_symbol_maps();
	वापस ret;
पूर्ण

पूर्णांक del_perf_probe_events(काष्ठा strfilter *filter)
अणु
	पूर्णांक ret, ret2, ufd = -1, kfd = -1;
	अक्षर *str = strfilter__string(filter);

	अगर (!str)
		वापस -EINVAL;

	/* Get current event names */
	ret = probe_file__खोलो_both(&kfd, &ufd, PF_FL_RW);
	अगर (ret < 0)
		जाओ out;

	ret = probe_file__del_events(kfd, filter);
	अगर (ret < 0 && ret != -ENOENT)
		जाओ error;

	ret2 = probe_file__del_events(ufd, filter);
	अगर (ret2 < 0 && ret2 != -ENOENT) अणु
		ret = ret2;
		जाओ error;
	पूर्ण
	ret = 0;

error:
	अगर (kfd >= 0)
		बंद(kfd);
	अगर (ufd >= 0)
		बंद(ufd);
out:
	मुक्त(str);

	वापस ret;
पूर्ण

पूर्णांक show_available_funcs(स्थिर अक्षर *target, काष्ठा nsinfo *nsi,
			 काष्ठा strfilter *_filter, bool user)
अणु
        काष्ठा rb_node *nd;
	काष्ठा map *map;
	पूर्णांक ret;

	ret = init_probe_symbol_maps(user);
	अगर (ret < 0)
		वापस ret;

	/* Get a symbol map */
	map = get_target_map(target, nsi, user);
	अगर (!map) अणु
		pr_err("Failed to get a map for %s\n", (target) ? : "kernel");
		वापस -EINVAL;
	पूर्ण

	ret = map__load(map);
	अगर (ret) अणु
		अगर (ret == -2) अणु
			अक्षर *str = strfilter__string(_filter);
			pr_err("Failed to find symbols matched to \"%s\"\n",
			       str);
			मुक्त(str);
		पूर्ण अन्यथा
			pr_err("Failed to load symbols in %s\n",
			       (target) ? : "kernel");
		जाओ end;
	पूर्ण
	अगर (!dso__sorted_by_name(map->dso))
		dso__sort_by_name(map->dso);

	/* Show all (filtered) symbols */
	setup_pager();

	क्रम (nd = rb_first_cached(&map->dso->symbol_names); nd;
	     nd = rb_next(nd)) अणु
		काष्ठा symbol_name_rb_node *pos = rb_entry(nd, काष्ठा symbol_name_rb_node, rb_node);

		अगर (strfilter__compare(_filter, pos->sym.name))
			म_लिखो("%s\n", pos->sym.name);
	पूर्ण
end:
	map__put(map);
	निकास_probe_symbol_maps();

	वापस ret;
पूर्ण

पूर्णांक copy_to_probe_trace_arg(काष्ठा probe_trace_arg *tvar,
			    काष्ठा perf_probe_arg *pvar)
अणु
	tvar->value = strdup(pvar->var);
	अगर (tvar->value == शून्य)
		वापस -ENOMEM;
	अगर (pvar->type) अणु
		tvar->type = strdup(pvar->type);
		अगर (tvar->type == शून्य)
			वापस -ENOMEM;
	पूर्ण
	अगर (pvar->name) अणु
		tvar->name = strdup(pvar->name);
		अगर (tvar->name == शून्य)
			वापस -ENOMEM;
	पूर्ण अन्यथा
		tvar->name = शून्य;
	वापस 0;
पूर्ण
