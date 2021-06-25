<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2020 Oracle Corporation
 *
 * Module Author: Mike Christie
 */
#समावेश "dm-path-selector.h"

#समावेश <linux/device-mapper.h>
#समावेश <linux/module.h>

#घोषणा DM_MSG_PREFIX "multipath io-affinity"

काष्ठा path_info अणु
	काष्ठा dm_path *path;
	cpumask_var_t cpumask;
	refcount_t refcount;
	bool failed;
पूर्ण;

काष्ठा selector अणु
	काष्ठा path_info **path_map;
	cpumask_var_t path_mask;
	atomic_t map_misses;
पूर्ण;

अटल व्योम ioa_मुक्त_path(काष्ठा selector *s, अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा path_info *pi = s->path_map[cpu];

	अगर (!pi)
		वापस;

	अगर (refcount_dec_and_test(&pi->refcount)) अणु
		cpumask_clear_cpu(cpu, s->path_mask);
		मुक्त_cpumask_var(pi->cpumask);
		kमुक्त(pi);

		s->path_map[cpu] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक ioa_add_path(काष्ठा path_selector *ps, काष्ठा dm_path *path,
			पूर्णांक argc, अक्षर **argv, अक्षर **error)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi = शून्य;
	अचिन्हित पूर्णांक cpu;
	पूर्णांक ret;

	अगर (argc != 1) अणु
		*error = "io-affinity ps: invalid number of arguments";
		वापस -EINVAL;
	पूर्ण

	pi = kzalloc(माप(*pi), GFP_KERNEL);
	अगर (!pi) अणु
		*error = "io-affinity ps: Error allocating path context";
		वापस -ENOMEM;
	पूर्ण

	pi->path = path;
	path->pscontext = pi;
	refcount_set(&pi->refcount, 1);

	अगर (!zalloc_cpumask_var(&pi->cpumask, GFP_KERNEL)) अणु
		*error = "io-affinity ps: Error allocating cpumask context";
		ret = -ENOMEM;
		जाओ मुक्त_pi;
	पूर्ण

	ret = cpumask_parse(argv[0], pi->cpumask);
	अगर (ret) अणु
		*error = "io-affinity ps: invalid cpumask";
		ret = -EINVAL;
		जाओ मुक्त_mask;
	पूर्ण

	क्रम_each_cpu(cpu, pi->cpumask) अणु
		अगर (cpu >= nr_cpu_ids) अणु
			DMWARN_LIMIT("Ignoring mapping for CPU %u. Max CPU is %u",
				     cpu, nr_cpu_ids);
			अवरोध;
		पूर्ण

		अगर (s->path_map[cpu]) अणु
			DMWARN("CPU mapping for %u exists. Ignoring.", cpu);
			जारी;
		पूर्ण

		cpumask_set_cpu(cpu, s->path_mask);
		s->path_map[cpu] = pi;
		refcount_inc(&pi->refcount);
		जारी;
	पूर्ण

	अगर (refcount_dec_and_test(&pi->refcount)) अणु
		*error = "io-affinity ps: No new/valid CPU mapping found";
		ret = -EINVAL;
		जाओ मुक्त_mask;
	पूर्ण

	वापस 0;

मुक्त_mask:
	मुक्त_cpumask_var(pi->cpumask);
मुक्त_pi:
	kमुक्त(pi);
	वापस ret;
पूर्ण

अटल पूर्णांक ioa_create(काष्ठा path_selector *ps, अचिन्हित argc, अक्षर **argv)
अणु
	काष्ठा selector *s;

	s = kदो_स्मृति(माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;

	s->path_map = kzalloc(nr_cpu_ids * माप(काष्ठा path_info *),
			      GFP_KERNEL);
	अगर (!s->path_map)
		जाओ मुक्त_selector;

	अगर (!zalloc_cpumask_var(&s->path_mask, GFP_KERNEL))
		जाओ मुक्त_map;

	atomic_set(&s->map_misses, 0);
	ps->context = s;
	वापस 0;

मुक्त_map:
	kमुक्त(s->path_map);
मुक्त_selector:
	kमुक्त(s);
	वापस -ENOMEM;
पूर्ण

अटल व्योम ioa_destroy(काष्ठा path_selector *ps)
अणु
	काष्ठा selector *s = ps->context;
	अचिन्हित cpu;

	क्रम_each_cpu(cpu, s->path_mask)
		ioa_मुक्त_path(s, cpu);

	मुक्त_cpumask_var(s->path_mask);
	kमुक्त(s->path_map);
	kमुक्त(s);

	ps->context = शून्य;
पूर्ण

अटल पूर्णांक ioa_status(काष्ठा path_selector *ps, काष्ठा dm_path *path,
		      status_type_t type, अक्षर *result, अचिन्हित पूर्णांक maxlen)
अणु
	काष्ठा selector *s = ps->context;
	काष्ठा path_info *pi;
	पूर्णांक sz = 0;

	अगर (!path) अणु
		DMEMIT("0 ");
		वापस sz;
	पूर्ण

	चयन(type) अणु
	हाल STATUSTYPE_INFO:
		DMEMIT("%d ", atomic_पढ़ो(&s->map_misses));
		अवरोध;
	हाल STATUSTYPE_TABLE:
		pi = path->pscontext;
		DMEMIT("%*pb ", cpumask_pr_args(pi->cpumask));
		अवरोध;
	पूर्ण

	वापस sz;
पूर्ण

अटल व्योम ioa_fail_path(काष्ठा path_selector *ps, काष्ठा dm_path *p)
अणु
	काष्ठा path_info *pi = p->pscontext;

	pi->failed = true;
पूर्ण

अटल पूर्णांक ioa_reinstate_path(काष्ठा path_selector *ps, काष्ठा dm_path *p)
अणु
	काष्ठा path_info *pi = p->pscontext;

	pi->failed = false;
	वापस 0;
पूर्ण

अटल काष्ठा dm_path *ioa_select_path(काष्ठा path_selector *ps,
				       माप_प्रकार nr_bytes)
अणु
	अचिन्हित पूर्णांक cpu, node;
	काष्ठा selector *s = ps->context;
	स्थिर काष्ठा cpumask *cpumask;
	काष्ठा path_info *pi;
	पूर्णांक i;

	cpu = get_cpu();

	pi = s->path_map[cpu];
	अगर (pi && !pi->failed)
		जाओ करोne;

	/*
	 * Perf is not optimal, but we at least try the local node then just
	 * try not to fail.
	 */
	अगर (!pi)
		atomic_inc(&s->map_misses);

	node = cpu_to_node(cpu);
	cpumask = cpumask_of_node(node);
	क्रम_each_cpu(i, cpumask) अणु
		pi = s->path_map[i];
		अगर (pi && !pi->failed)
			जाओ करोne;
	पूर्ण

	क्रम_each_cpu(i, s->path_mask) अणु
		pi = s->path_map[i];
		अगर (pi && !pi->failed)
			जाओ करोne;
	पूर्ण
	pi = शून्य;

करोne:
	put_cpu();
	वापस pi ? pi->path : शून्य;
पूर्ण

अटल काष्ठा path_selector_type ioa_ps = अणु
	.name		= "io-affinity",
	.module		= THIS_MODULE,
	.table_args	= 1,
	.info_args	= 1,
	.create		= ioa_create,
	.destroy	= ioa_destroy,
	.status		= ioa_status,
	.add_path	= ioa_add_path,
	.fail_path	= ioa_fail_path,
	.reinstate_path	= ioa_reinstate_path,
	.select_path	= ioa_select_path,
पूर्ण;

अटल पूर्णांक __init dm_ioa_init(व्योम)
अणु
	पूर्णांक ret = dm_रेजिस्टर_path_selector(&ioa_ps);

	अगर (ret < 0)
		DMERR("register failed %d", ret);
	वापस ret;
पूर्ण

अटल व्योम __निकास dm_ioa_निकास(व्योम)
अणु
	पूर्णांक ret = dm_unरेजिस्टर_path_selector(&ioa_ps);

	अगर (ret < 0)
		DMERR("unregister failed %d", ret);
पूर्ण

module_init(dm_ioa_init);
module_निकास(dm_ioa_निकास);

MODULE_DESCRIPTION(DM_NAME " multipath path selector that selects paths based on the CPU IO is being executed on");
MODULE_AUTHOR("Mike Christie <michael.christie@oracle.com>");
MODULE_LICENSE("GPL");
