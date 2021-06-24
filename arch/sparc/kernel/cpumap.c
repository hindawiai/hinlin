<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* cpumap.c: used क्रम optimizing CPU assignment
 *
 * Copyright (C) 2009 Hong H. Pham <hong.pham@windriver.com>
 */

#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/cpudata.h>
#समावेश "cpumap.h"


क्रमागत अणु
	CPUINFO_LVL_ROOT = 0,
	CPUINFO_LVL_NODE,
	CPUINFO_LVL_CORE,
	CPUINFO_LVL_PROC,
	CPUINFO_LVL_MAX,
पूर्ण;

क्रमागत अणु
	ROVER_NO_OP              = 0,
	/* Increment rover every समय level is visited */
	ROVER_INC_ON_VISIT       = 1 << 0,
	/* Increment parent's rover every समय rover wraps around */
	ROVER_INC_PARENT_ON_LOOP = 1 << 1,
पूर्ण;

काष्ठा cpuinfo_node अणु
	पूर्णांक id;
	पूर्णांक level;
	पूर्णांक num_cpus;    /* Number of CPUs in this hierarchy */
	पूर्णांक parent_index;
	पूर्णांक child_start; /* Array index of the first child node */
	पूर्णांक child_end;   /* Array index of the last child node */
	पूर्णांक rover;       /* Child node iterator */
पूर्ण;

काष्ठा cpuinfo_level अणु
	पूर्णांक start_index; /* Index of first node of a level in a cpuinfo tree */
	पूर्णांक end_index;   /* Index of last node of a level in a cpuinfo tree */
	पूर्णांक num_nodes;   /* Number of nodes in a level in a cpuinfo tree */
पूर्ण;

काष्ठा cpuinfo_tree अणु
	पूर्णांक total_nodes;

	/* Offsets पूर्णांकo nodes[] क्रम each level of the tree */
	काष्ठा cpuinfo_level level[CPUINFO_LVL_MAX];
	काष्ठा cpuinfo_node  nodes[];
पूर्ण;


अटल काष्ठा cpuinfo_tree *cpuinfo_tree;

अटल u16 cpu_distribution_map[NR_CPUS];
अटल DEFINE_SPINLOCK(cpu_map_lock);


/* Niagara optimized cpuinfo tree traversal. */
अटल स्थिर पूर्णांक niagara_iterate_method[] = अणु
	[CPUINFO_LVL_ROOT] = ROVER_NO_OP,

	/* Stअक्रमs (or भव CPUs) within a core may not run concurrently
	 * on the Niagara, as inकाष्ठाion pipeline(s) are shared.  Distribute
	 * work to stअक्रमs in dअगरferent cores first क्रम better concurrency.
	 * Go to next NUMA node when all cores are used.
	 */
	[CPUINFO_LVL_NODE] = ROVER_INC_ON_VISIT|ROVER_INC_PARENT_ON_LOOP,

	/* Stअक्रमs are grouped together by proc_id in cpuinfo_sparc, i.e.
	 * a proc_id represents an inकाष्ठाion pipeline.  Distribute work to
	 * stअक्रमs in dअगरferent proc_id groups अगर the core has multiple
	 * inकाष्ठाion pipelines (e.g. the Niagara 2/2+ has two).
	 */
	[CPUINFO_LVL_CORE] = ROVER_INC_ON_VISIT,

	/* Pick the next stअक्रम in the proc_id group. */
	[CPUINFO_LVL_PROC] = ROVER_INC_ON_VISIT,
पूर्ण;

/* Generic cpuinfo tree traversal.  Distribute work round robin across NUMA
 * nodes.
 */
अटल स्थिर पूर्णांक generic_iterate_method[] = अणु
	[CPUINFO_LVL_ROOT] = ROVER_INC_ON_VISIT,
	[CPUINFO_LVL_NODE] = ROVER_NO_OP,
	[CPUINFO_LVL_CORE] = ROVER_INC_PARENT_ON_LOOP,
	[CPUINFO_LVL_PROC] = ROVER_INC_ON_VISIT|ROVER_INC_PARENT_ON_LOOP,
पूर्ण;


अटल पूर्णांक cpuinfo_id(पूर्णांक cpu, पूर्णांक level)
अणु
	पूर्णांक id;

	चयन (level) अणु
	हाल CPUINFO_LVL_ROOT:
		id = 0;
		अवरोध;
	हाल CPUINFO_LVL_NODE:
		id = cpu_to_node(cpu);
		अवरोध;
	हाल CPUINFO_LVL_CORE:
		id = cpu_data(cpu).core_id;
		अवरोध;
	हाल CPUINFO_LVL_PROC:
		id = cpu_data(cpu).proc_id;
		अवरोध;
	शेष:
		id = -EINVAL;
	पूर्ण
	वापस id;
पूर्ण

/*
 * Enumerate the CPU inक्रमmation in __cpu_data to determine the start index,
 * end index, and number of nodes क्रम each level in the cpuinfo tree.  The
 * total number of cpuinfo nodes required to build the tree is वापसed.
 */
अटल पूर्णांक क्रमागतerate_cpuinfo_nodes(काष्ठा cpuinfo_level *tree_level)
अणु
	पूर्णांक prev_id[CPUINFO_LVL_MAX];
	पूर्णांक i, n, num_nodes;

	क्रम (i = CPUINFO_LVL_ROOT; i < CPUINFO_LVL_MAX; i++) अणु
		काष्ठा cpuinfo_level *lv = &tree_level[i];

		prev_id[i] = -1;
		lv->start_index = lv->end_index = lv->num_nodes = 0;
	पूर्ण

	num_nodes = 1; /* Include the root node */

	क्रम (i = 0; i < num_possible_cpus(); i++) अणु
		अगर (!cpu_online(i))
			जारी;

		n = cpuinfo_id(i, CPUINFO_LVL_NODE);
		अगर (n > prev_id[CPUINFO_LVL_NODE]) अणु
			tree_level[CPUINFO_LVL_NODE].num_nodes++;
			prev_id[CPUINFO_LVL_NODE] = n;
			num_nodes++;
		पूर्ण
		n = cpuinfo_id(i, CPUINFO_LVL_CORE);
		अगर (n > prev_id[CPUINFO_LVL_CORE]) अणु
			tree_level[CPUINFO_LVL_CORE].num_nodes++;
			prev_id[CPUINFO_LVL_CORE] = n;
			num_nodes++;
		पूर्ण
		n = cpuinfo_id(i, CPUINFO_LVL_PROC);
		अगर (n > prev_id[CPUINFO_LVL_PROC]) अणु
			tree_level[CPUINFO_LVL_PROC].num_nodes++;
			prev_id[CPUINFO_LVL_PROC] = n;
			num_nodes++;
		पूर्ण
	पूर्ण

	tree_level[CPUINFO_LVL_ROOT].num_nodes = 1;

	n = tree_level[CPUINFO_LVL_NODE].num_nodes;
	tree_level[CPUINFO_LVL_NODE].start_index = 1;
	tree_level[CPUINFO_LVL_NODE].end_index   = n;

	n++;
	tree_level[CPUINFO_LVL_CORE].start_index = n;
	n += tree_level[CPUINFO_LVL_CORE].num_nodes;
	tree_level[CPUINFO_LVL_CORE].end_index   = n - 1;

	tree_level[CPUINFO_LVL_PROC].start_index = n;
	n += tree_level[CPUINFO_LVL_PROC].num_nodes;
	tree_level[CPUINFO_LVL_PROC].end_index   = n - 1;

	वापस num_nodes;
पूर्ण

/* Build a tree representation of the CPU hierarchy using the per CPU
 * inक्रमmation in __cpu_data.  Entries in __cpu_data[0..NR_CPUS] are
 * assumed to be sorted in ascending order based on node, core_id, and
 * proc_id (in order of signअगरicance).
 */
अटल काष्ठा cpuinfo_tree *build_cpuinfo_tree(व्योम)
अणु
	काष्ठा cpuinfo_tree *new_tree;
	काष्ठा cpuinfo_node *node;
	काष्ठा cpuinfo_level पंचांगp_level[CPUINFO_LVL_MAX];
	पूर्णांक num_cpus[CPUINFO_LVL_MAX];
	पूर्णांक level_rover[CPUINFO_LVL_MAX];
	पूर्णांक prev_id[CPUINFO_LVL_MAX];
	पूर्णांक n, id, cpu, prev_cpu, last_cpu, level;

	n = क्रमागतerate_cpuinfo_nodes(पंचांगp_level);

	new_tree = kzalloc(काष्ठा_size(new_tree, nodes, n), GFP_ATOMIC);
	अगर (!new_tree)
		वापस शून्य;

	new_tree->total_nodes = n;
	स_नकल(&new_tree->level, पंचांगp_level, माप(पंचांगp_level));

	prev_cpu = cpu = cpumask_first(cpu_online_mask);

	/* Initialize all levels in the tree with the first CPU */
	क्रम (level = CPUINFO_LVL_PROC; level >= CPUINFO_LVL_ROOT; level--) अणु
		n = new_tree->level[level].start_index;

		level_rover[level] = n;
		node = &new_tree->nodes[n];

		id = cpuinfo_id(cpu, level);
		अगर (unlikely(id < 0)) अणु
			kमुक्त(new_tree);
			वापस शून्य;
		पूर्ण
		node->id = id;
		node->level = level;
		node->num_cpus = 1;

		node->parent_index = (level > CPUINFO_LVL_ROOT)
		    ? new_tree->level[level - 1].start_index : -1;

		node->child_start = node->child_end = node->rover =
		    (level == CPUINFO_LVL_PROC)
		    ? cpu : new_tree->level[level + 1].start_index;

		prev_id[level] = node->id;
		num_cpus[level] = 1;
	पूर्ण

	क्रम (last_cpu = (num_possible_cpus() - 1); last_cpu >= 0; last_cpu--) अणु
		अगर (cpu_online(last_cpu))
			अवरोध;
	पूर्ण

	जबतक (++cpu <= last_cpu) अणु
		अगर (!cpu_online(cpu))
			जारी;

		क्रम (level = CPUINFO_LVL_PROC; level >= CPUINFO_LVL_ROOT;
		     level--) अणु
			id = cpuinfo_id(cpu, level);
			अगर (unlikely(id < 0)) अणु
				kमुक्त(new_tree);
				वापस शून्य;
			पूर्ण

			अगर ((id != prev_id[level]) || (cpu == last_cpu)) अणु
				prev_id[level] = id;
				node = &new_tree->nodes[level_rover[level]];
				node->num_cpus = num_cpus[level];
				num_cpus[level] = 1;

				अगर (cpu == last_cpu)
					node->num_cpus++;

				/* Connect tree node to parent */
				अगर (level == CPUINFO_LVL_ROOT)
					node->parent_index = -1;
				अन्यथा
					node->parent_index =
					    level_rover[level - 1];

				अगर (level == CPUINFO_LVL_PROC) अणु
					node->child_end =
					    (cpu == last_cpu) ? cpu : prev_cpu;
				पूर्ण अन्यथा अणु
					node->child_end =
					    level_rover[level + 1] - 1;
				पूर्ण

				/* Initialize the next node in the same level */
				n = ++level_rover[level];
				अगर (n <= new_tree->level[level].end_index) अणु
					node = &new_tree->nodes[n];
					node->id = id;
					node->level = level;

					/* Connect node to child */
					node->child_start = node->child_end =
					node->rover =
					    (level == CPUINFO_LVL_PROC)
					    ? cpu : level_rover[level + 1];
				पूर्ण
			पूर्ण अन्यथा
				num_cpus[level]++;
		पूर्ण
		prev_cpu = cpu;
	पूर्ण

	वापस new_tree;
पूर्ण

अटल व्योम increment_rover(काष्ठा cpuinfo_tree *t, पूर्णांक node_index,
                            पूर्णांक root_index, स्थिर पूर्णांक *rover_inc_table)
अणु
	काष्ठा cpuinfo_node *node = &t->nodes[node_index];
	पूर्णांक top_level, level;

	top_level = t->nodes[root_index].level;
	क्रम (level = node->level; level >= top_level; level--) अणु
		node->rover++;
		अगर (node->rover <= node->child_end)
			वापस;

		node->rover = node->child_start;
		/* If parent's rover करोes not need to be adjusted, stop here. */
		अगर ((level == top_level) ||
		    !(rover_inc_table[level] & ROVER_INC_PARENT_ON_LOOP))
			वापस;

		node = &t->nodes[node->parent_index];
	पूर्ण
पूर्ण

अटल पूर्णांक iterate_cpu(काष्ठा cpuinfo_tree *t, अचिन्हित पूर्णांक root_index)
अणु
	स्थिर पूर्णांक *rover_inc_table;
	पूर्णांक level, new_index, index = root_index;

	चयन (sun4v_chip_type) अणु
	हाल SUN4V_CHIP_NIAGARA1:
	हाल SUN4V_CHIP_NIAGARA2:
	हाल SUN4V_CHIP_NIAGARA3:
	हाल SUN4V_CHIP_NIAGARA4:
	हाल SUN4V_CHIP_NIAGARA5:
	हाल SUN4V_CHIP_SPARC_M6:
	हाल SUN4V_CHIP_SPARC_M7:
	हाल SUN4V_CHIP_SPARC_M8:
	हाल SUN4V_CHIP_SPARC_SN:
	हाल SUN4V_CHIP_SPARC64X:
		rover_inc_table = niagara_iterate_method;
		अवरोध;
	शेष:
		rover_inc_table = generic_iterate_method;
	पूर्ण

	क्रम (level = t->nodes[root_index].level; level < CPUINFO_LVL_MAX;
	     level++) अणु
		new_index = t->nodes[index].rover;
		अगर (rover_inc_table[level] & ROVER_INC_ON_VISIT)
			increment_rover(t, index, root_index, rover_inc_table);

		index = new_index;
	पूर्ण
	वापस index;
पूर्ण

अटल व्योम _cpu_map_rebuild(व्योम)
अणु
	पूर्णांक i;

	अगर (cpuinfo_tree) अणु
		kमुक्त(cpuinfo_tree);
		cpuinfo_tree = शून्य;
	पूर्ण

	cpuinfo_tree = build_cpuinfo_tree();
	अगर (!cpuinfo_tree)
		वापस;

	/* Build CPU distribution map that spans all online CPUs.  No need
	 * to check अगर the CPU is online, as that is करोne when the cpuinfo
	 * tree is being built.
	 */
	क्रम (i = 0; i < cpuinfo_tree->nodes[0].num_cpus; i++)
		cpu_distribution_map[i] = iterate_cpu(cpuinfo_tree, 0);
पूर्ण

/* Fallback अगर the cpuinfo tree could not be built.  CPU mapping is linear
 * round robin.
 */
अटल पूर्णांक simple_map_to_cpu(अचिन्हित पूर्णांक index)
अणु
	पूर्णांक i, end, cpu_rover;

	cpu_rover = 0;
	end = index % num_online_cpus();
	क्रम (i = 0; i < num_possible_cpus(); i++) अणु
		अगर (cpu_online(cpu_rover)) अणु
			अगर (cpu_rover >= end)
				वापस cpu_rover;

			cpu_rover++;
		पूर्ण
	पूर्ण

	/* Impossible, since num_online_cpus() <= num_possible_cpus() */
	वापस cpumask_first(cpu_online_mask);
पूर्ण

अटल पूर्णांक _map_to_cpu(अचिन्हित पूर्णांक index)
अणु
	काष्ठा cpuinfo_node *root_node;

	अगर (unlikely(!cpuinfo_tree)) अणु
		_cpu_map_rebuild();
		अगर (!cpuinfo_tree)
			वापस simple_map_to_cpu(index);
	पूर्ण

	root_node = &cpuinfo_tree->nodes[0];
#अगर_घोषित CONFIG_HOTPLUG_CPU
	अगर (unlikely(root_node->num_cpus != num_online_cpus())) अणु
		_cpu_map_rebuild();
		अगर (!cpuinfo_tree)
			वापस simple_map_to_cpu(index);
	पूर्ण
#पूर्ण_अगर
	वापस cpu_distribution_map[index % root_node->num_cpus];
पूर्ण

पूर्णांक map_to_cpu(अचिन्हित पूर्णांक index)
अणु
	पूर्णांक mapped_cpu;
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&cpu_map_lock, flag);
	mapped_cpu = _map_to_cpu(index);

#अगर_घोषित CONFIG_HOTPLUG_CPU
	जबतक (unlikely(!cpu_online(mapped_cpu)))
		mapped_cpu = _map_to_cpu(index);
#पूर्ण_अगर
	spin_unlock_irqrestore(&cpu_map_lock, flag);
	वापस mapped_cpu;
पूर्ण
EXPORT_SYMBOL(map_to_cpu);

व्योम cpu_map_rebuild(व्योम)
अणु
	अचिन्हित दीर्घ flag;

	spin_lock_irqsave(&cpu_map_lock, flag);
	_cpu_map_rebuild();
	spin_unlock_irqrestore(&cpu_map_lock, flag);
पूर्ण
