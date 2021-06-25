<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * OF NUMA Parsing support.
 *
 * Copyright (C) 2015 - 2016 Cavium Inc.
 */

#घोषणा pr_fmt(fmt) "OF: NUMA: " fmt

#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/nodemask.h>

#समावेश <यंत्र/numa.h>

/* define शेष numa node to 0 */
#घोषणा DEFAULT_NODE 0

/*
 * Even though we connect cpus to numa करोमुख्यs later in SMP
 * init, we need to know the node ids now क्रम all cpus.
*/
अटल व्योम __init of_numa_parse_cpu_nodes(व्योम)
अणु
	u32 nid;
	पूर्णांक r;
	काष्ठा device_node *np;

	क्रम_each_of_cpu_node(np) अणु
		r = of_property_पढ़ो_u32(np, "numa-node-id", &nid);
		अगर (r)
			जारी;

		pr_debug("CPU on %u\n", nid);
		अगर (nid >= MAX_NUMNODES)
			pr_warn("Node id %u exceeds maximum value\n", nid);
		अन्यथा
			node_set(nid, numa_nodes_parsed);
	पूर्ण
पूर्ण

अटल पूर्णांक __init of_numa_parse_memory_nodes(व्योम)
अणु
	काष्ठा device_node *np = शून्य;
	काष्ठा resource rsrc;
	u32 nid;
	पूर्णांक i, r;

	क्रम_each_node_by_type(np, "memory") अणु
		r = of_property_पढ़ो_u32(np, "numa-node-id", &nid);
		अगर (r == -EINVAL)
			/*
			 * property करोesn't exist अगर -EINVAL, जारी
			 * looking क्रम more memory nodes with
			 * "numa-node-id" property
			 */
			जारी;

		अगर (nid >= MAX_NUMNODES) अणु
			pr_warn("Node id %u exceeds maximum value\n", nid);
			r = -EINVAL;
		पूर्ण

		क्रम (i = 0; !r && !of_address_to_resource(np, i, &rsrc); i++)
			r = numa_add_memblk(nid, rsrc.start, rsrc.end + 1);

		अगर (!i || r) अणु
			of_node_put(np);
			pr_err("bad property in memory node\n");
			वापस r ? : -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init of_numa_parse_distance_map_v1(काष्ठा device_node *map)
अणु
	स्थिर __be32 *matrix;
	पूर्णांक entry_count;
	पूर्णांक i;

	pr_info("parsing numa-distance-map-v1\n");

	matrix = of_get_property(map, "distance-matrix", शून्य);
	अगर (!matrix) अणु
		pr_err("No distance-matrix property in distance-map\n");
		वापस -EINVAL;
	पूर्ण

	entry_count = of_property_count_u32_elems(map, "distance-matrix");
	अगर (entry_count <= 0) अणु
		pr_err("Invalid distance-matrix\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i + 2 < entry_count; i += 3) अणु
		u32 nodea, nodeb, distance;

		nodea = of_पढ़ो_number(matrix, 1);
		matrix++;
		nodeb = of_पढ़ो_number(matrix, 1);
		matrix++;
		distance = of_पढ़ो_number(matrix, 1);
		matrix++;

		अगर ((nodea == nodeb && distance != LOCAL_DISTANCE) ||
		    (nodea != nodeb && distance <= LOCAL_DISTANCE)) अणु
			pr_err("Invalid distance[node%d -> node%d] = %d\n",
			       nodea, nodeb, distance);
			वापस -EINVAL;
		पूर्ण

		numa_set_distance(nodea, nodeb, distance);

		/* Set शेष distance of node B->A same as A->B */
		अगर (nodeb > nodea)
			numa_set_distance(nodeb, nodea, distance);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init of_numa_parse_distance_map(व्योम)
अणु
	पूर्णांक ret = 0;
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य,
				     "numa-distance-map-v1");
	अगर (np)
		ret = of_numa_parse_distance_map_v1(np);

	of_node_put(np);
	वापस ret;
पूर्ण

पूर्णांक of_node_to_nid(काष्ठा device_node *device)
अणु
	काष्ठा device_node *np;
	u32 nid;
	पूर्णांक r = -ENODATA;

	np = of_node_get(device);

	जबतक (np) अणु
		r = of_property_पढ़ो_u32(np, "numa-node-id", &nid);
		/*
		 * -EINVAL indicates the property was not found, and
		 *  we walk up the tree trying to find a parent with a
		 *  "numa-node-id".  Any other type of error indicates
		 *  a bad device tree and we give up.
		 */
		अगर (r != -EINVAL)
			अवरोध;

		np = of_get_next_parent(np);
	पूर्ण
	अगर (np && r)
		pr_warn("Invalid \"numa-node-id\" property in node %pOFn\n",
			np);
	of_node_put(np);

	/*
	 * If numa=off passed on command line, or with a defective
	 * device tree, the nid may not be in the set of possible
	 * nodes.  Check क्रम this हाल and वापस NUMA_NO_NODE.
	 */
	अगर (!r && nid < MAX_NUMNODES && node_possible(nid))
		वापस nid;

	वापस NUMA_NO_NODE;
पूर्ण

पूर्णांक __init of_numa_init(व्योम)
अणु
	पूर्णांक r;

	of_numa_parse_cpu_nodes();
	r = of_numa_parse_memory_nodes();
	अगर (r)
		वापस r;
	वापस of_numa_parse_distance_map();
पूर्ण
