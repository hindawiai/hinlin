<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "unwind.h"
#समावेश "dso.h"
#समावेश "map.h"
#समावेश "thread.h"
#समावेश "session.h"
#समावेश "debug.h"
#समावेश "env.h"
#समावेश "callchain.h"

काष्ठा unwind_libunwind_ops __weak *local_unwind_libunwind_ops;
काष्ठा unwind_libunwind_ops __weak *x86_32_unwind_libunwind_ops;
काष्ठा unwind_libunwind_ops __weak *arm64_unwind_libunwind_ops;

अटल व्योम unwind__रेजिस्टर_ops(काष्ठा maps *maps, काष्ठा unwind_libunwind_ops *ops)
अणु
	maps->unwind_libunwind_ops = ops;
पूर्ण

पूर्णांक unwind__prepare_access(काष्ठा maps *maps, काष्ठा map *map, bool *initialized)
अणु
	स्थिर अक्षर *arch;
	क्रमागत dso_type dso_type;
	काष्ठा unwind_libunwind_ops *ops = local_unwind_libunwind_ops;
	पूर्णांक err;

	अगर (!dwarf_callchain_users)
		वापस 0;

	अगर (maps->addr_space) अणु
		pr_debug("unwind: thread map already set, dso=%s\n",
			 map->dso->name);
		अगर (initialized)
			*initialized = true;
		वापस 0;
	पूर्ण

	/* env->arch is शून्य क्रम live-mode (i.e. perf top) */
	अगर (!maps->machine->env || !maps->machine->env->arch)
		जाओ out_रेजिस्टर;

	dso_type = dso__type(map->dso, maps->machine);
	अगर (dso_type == DSO__TYPE_UNKNOWN)
		वापस 0;

	arch = perf_env__arch(maps->machine->env);

	अगर (!म_भेद(arch, "x86")) अणु
		अगर (dso_type != DSO__TYPE_64BIT)
			ops = x86_32_unwind_libunwind_ops;
	पूर्ण अन्यथा अगर (!म_भेद(arch, "arm64") || !म_भेद(arch, "arm")) अणु
		अगर (dso_type == DSO__TYPE_64BIT)
			ops = arm64_unwind_libunwind_ops;
	पूर्ण

	अगर (!ops) अणु
		pr_err("unwind: target platform=%s is not supported\n", arch);
		वापस 0;
	पूर्ण
out_रेजिस्टर:
	unwind__रेजिस्टर_ops(maps, ops);

	err = maps->unwind_libunwind_ops->prepare_access(maps);
	अगर (initialized)
		*initialized = err ? false : true;
	वापस err;
पूर्ण

व्योम unwind__flush_access(काष्ठा maps *maps)
अणु
	अगर (maps->unwind_libunwind_ops)
		maps->unwind_libunwind_ops->flush_access(maps);
पूर्ण

व्योम unwind__finish_access(काष्ठा maps *maps)
अणु
	अगर (maps->unwind_libunwind_ops)
		maps->unwind_libunwind_ops->finish_access(maps);
पूर्ण

पूर्णांक unwind__get_entries(unwind_entry_cb_t cb, व्योम *arg,
			 काष्ठा thपढ़ो *thपढ़ो,
			 काष्ठा perf_sample *data, पूर्णांक max_stack)
अणु
	अगर (thपढ़ो->maps->unwind_libunwind_ops)
		वापस thपढ़ो->maps->unwind_libunwind_ops->get_entries(cb, arg, thपढ़ो, data, max_stack);
	वापस 0;
पूर्ण
