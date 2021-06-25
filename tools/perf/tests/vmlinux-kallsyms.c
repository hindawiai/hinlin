<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/compiler.h>
#समावेश <linux/rbtree.h>
#समावेश <पूर्णांकtypes.h>
#समावेश <माला.स>
#समावेश <मानककोष.स>
#समावेश "dso.h"
#समावेश "map.h"
#समावेश "symbol.h"
#समावेश <पूर्णांकernal/lib.h> // page_size
#समावेश "tests.h"
#समावेश "debug.h"
#समावेश "machine.h"

#घोषणा UM(x) kallsyms_map->unmap_ip(kallsyms_map, (x))

पूर्णांक test__vmlinux_matches_kallsyms(काष्ठा test *test __maybe_unused, पूर्णांक subtest __maybe_unused)
अणु
	पूर्णांक err = -1;
	काष्ठा rb_node *nd;
	काष्ठा symbol *sym;
	काष्ठा map *kallsyms_map, *vmlinux_map, *map;
	काष्ठा machine kallsyms, vmlinux;
	काष्ठा maps *maps = machine__kernel_maps(&vmlinux);
	u64 mem_start, mem_end;
	bool header_prपूर्णांकed;

	/*
	 * Step 1:
	 *
	 * Init the machines that will hold kernel, modules obtained from
	 * both vmlinux + .ko files and from /proc/kallsyms split by modules.
	 */
	machine__init(&kallsyms, "", HOST_KERNEL_ID);
	machine__init(&vmlinux, "", HOST_KERNEL_ID);

	/*
	 * Step 2:
	 *
	 * Create the kernel maps क्रम kallsyms and the DSO where we will then
	 * load /proc/kallsyms. Also create the modules maps from /proc/modules
	 * and find the .ko files that match them in /lib/modules/`uname -r`/.
	 */
	अगर (machine__create_kernel_maps(&kallsyms) < 0) अणु
		pr_debug("machine__create_kernel_maps ");
		जाओ out;
	पूर्ण

	/*
	 * Step 3:
	 *
	 * Load and split /proc/kallsyms पूर्णांकo multiple maps, one per module.
	 * Do not use kcore, as this test was deचिन्हित beक्रमe kcore support
	 * and has parts that only make sense अगर using the non-kcore code.
	 * XXX: extend it to stress the kcorre code as well, hपूर्णांक: the list
	 * of modules extracted from /proc/kcore, in its current क्रमm, can't
	 * be compacted against the list of modules found in the "vmlinux"
	 * code and with the one got from /proc/modules from the "kallsyms" code.
	 */
	अगर (machine__load_kallsyms(&kallsyms, "/proc/kallsyms") <= 0) अणु
		pr_debug("dso__load_kallsyms ");
		जाओ out;
	पूर्ण

	/*
	 * Step 4:
	 *
	 * kallsyms will be पूर्णांकernally on demand sorted by name so that we can
	 * find the reference relocation * symbol, i.e. the symbol we will use
	 * to see अगर the running kernel was relocated by checking अगर it has the
	 * same value in the vmlinux file we load.
	 */
	kallsyms_map = machine__kernel_map(&kallsyms);

	/*
	 * Step 5:
	 *
	 * Now repeat step 2, this समय क्रम the vmlinux file we'll स्वतः-locate.
	 */
	अगर (machine__create_kernel_maps(&vmlinux) < 0) अणु
		pr_debug("machine__create_kernel_maps ");
		जाओ out;
	पूर्ण

	vmlinux_map = machine__kernel_map(&vmlinux);

	/*
	 * Step 6:
	 *
	 * Locate a vmlinux file in the vmlinux path that has a buildid that
	 * matches the one of the running kernel.
	 *
	 * While करोing that look अगर we find the ref reloc symbol, अगर we find it
	 * we'll have its ref_reloc_symbol.unrelocated_addr and then
	 * maps__reloc_vmlinux will notice and set proper ->[un]map_ip routines
	 * to fixup the symbols.
	 */
	अगर (machine__load_vmlinux_path(&vmlinux) <= 0) अणु
		pr_debug("Couldn't find a vmlinux that matches the kernel running on this machine, skipping test\n");
		err = TEST_SKIP;
		जाओ out;
	पूर्ण

	err = 0;
	/*
	 * Step 7:
	 *
	 * Now look at the symbols in the vmlinux DSO and check अगर we find all of them
	 * in the kallsyms dso. For the ones that are in both, check its names and
	 * end addresses too.
	 */
	map__क्रम_each_symbol(vmlinux_map, sym, nd) अणु
		काष्ठा symbol *pair, *first_pair;

		sym  = rb_entry(nd, काष्ठा symbol, rb_node);

		अगर (sym->start == sym->end)
			जारी;

		mem_start = vmlinux_map->unmap_ip(vmlinux_map, sym->start);
		mem_end = vmlinux_map->unmap_ip(vmlinux_map, sym->end);

		first_pair = machine__find_kernel_symbol(&kallsyms, mem_start, शून्य);
		pair = first_pair;

		अगर (pair && UM(pair->start) == mem_start) अणु
next_pair:
			अगर (arch__compare_symbol_names(sym->name, pair->name) == 0) अणु
				/*
				 * kallsyms करोn't have the symbol end, so we
				 * set that by using the next symbol start - 1,
				 * in some हालs we get this up to a page
				 * wrong, trace_kदो_स्मृति when I was developing
				 * this code was one such example, 2106 bytes
				 * off the real size. More than that and we
				 * _really_ have a problem.
				 */
				s64 skew = mem_end - UM(pair->end);
				अगर (lद_असल(skew) >= page_size)
					pr_debug("WARN: %#" PRIx64 ": diff end addr for %s v: %#" PRIx64 " k: %#" PRIx64 "\n",
						 mem_start, sym->name, mem_end,
						 UM(pair->end));

				/*
				 * Do not count this as a failure, because we
				 * could really find a हाल where it's not
				 * possible to get proper function end from
				 * kallsyms.
				 */
				जारी;
			पूर्ण अन्यथा अणु
				pair = machine__find_kernel_symbol_by_name(&kallsyms, sym->name, शून्य);
				अगर (pair) अणु
					अगर (UM(pair->start) == mem_start)
						जाओ next_pair;

					pr_debug("WARN: %#" PRIx64 ": diff name v: %s k: %s\n",
						 mem_start, sym->name, pair->name);
				पूर्ण अन्यथा अणु
					pr_debug("WARN: %#" PRIx64 ": diff name v: %s k: %s\n",
						 mem_start, sym->name, first_pair->name);
				पूर्ण

				जारी;
			पूर्ण
		पूर्ण अन्यथा अगर (mem_start == kallsyms.vmlinux_map->end) अणु
			/*
			 * Ignore aliases to _etext, i.e. to the end of the kernel text area,
			 * such as __indirect_thunk_end.
			 */
			जारी;
		पूर्ण अन्यथा अणु
			pr_debug("ERR : %#" PRIx64 ": %s not on kallsyms\n",
				 mem_start, sym->name);
		पूर्ण

		err = -1;
	पूर्ण

	अगर (verbose <= 0)
		जाओ out;

	header_prपूर्णांकed = false;

	maps__क्रम_each_entry(maps, map) अणु
		काष्ठा map *
		/*
		 * If it is the kernel, kallsyms is always "[kernel.kallsyms]", जबतक
		 * the kernel will have the path क्रम the vmlinux file being used,
		 * so use the लघु name, less descriptive but the same ("[kernel]" in
		 * both हालs.
		 */
		pair = maps__find_by_name(&kallsyms.kmaps, (map->dso->kernel ?
								map->dso->लघु_name :
								map->dso->name));
		अगर (pair) अणु
			pair->priv = 1;
		पूर्ण अन्यथा अणु
			अगर (!header_prपूर्णांकed) अणु
				pr_info("WARN: Maps only in vmlinux:\n");
				header_prपूर्णांकed = true;
			पूर्ण
			map__ख_लिखो(map, मानक_त्रुटि);
		पूर्ण
	पूर्ण

	header_prपूर्णांकed = false;

	maps__क्रम_each_entry(maps, map) अणु
		काष्ठा map *pair;

		mem_start = vmlinux_map->unmap_ip(vmlinux_map, map->start);
		mem_end = vmlinux_map->unmap_ip(vmlinux_map, map->end);

		pair = maps__find(&kallsyms.kmaps, mem_start);
		अगर (pair == शून्य || pair->priv)
			जारी;

		अगर (pair->start == mem_start) अणु
			अगर (!header_prपूर्णांकed) अणु
				pr_info("WARN: Maps in vmlinux with a different name in kallsyms:\n");
				header_prपूर्णांकed = true;
			पूर्ण

			pr_info("WARN: %" PRIx64 "-%" PRIx64 " %" PRIx64 " %s in kallsyms as",
				map->start, map->end, map->pgoff, map->dso->name);
			अगर (mem_end != pair->end)
				pr_info(":\nWARN: *%" PRIx64 "-%" PRIx64 " %" PRIx64,
					pair->start, pair->end, pair->pgoff);
			pr_info(" %s\n", pair->dso->name);
			pair->priv = 1;
		पूर्ण
	पूर्ण

	header_prपूर्णांकed = false;

	maps = machine__kernel_maps(&kallsyms);

	maps__क्रम_each_entry(maps, map) अणु
		अगर (!map->priv) अणु
			अगर (!header_prपूर्णांकed) अणु
				pr_info("WARN: Maps only in kallsyms:\n");
				header_prपूर्णांकed = true;
			पूर्ण
			map__ख_लिखो(map, मानक_त्रुटि);
		पूर्ण
	पूर्ण
out:
	machine__निकास(&kallsyms);
	machine__निकास(&vmlinux);
	वापस err;
पूर्ण
