<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Procedures क्रम creating, accessing and पूर्णांकerpreting the device tree.
 *
 * Paul Mackerras	August 1996.
 * Copyright (C) 1996-2005 Paul Mackerras.
 *
 *  Adapted क्रम 64bit PowerPC by Dave Engebretsen and Peter Bergner.
 *    अणुengebret|bergnerपूर्ण@us.ibm.com
 *
 *  Adapted क्रम sparc and sparc64 by David S. Miller davem@davemloft.net
 *
 *  Reconsolidated from arch/x/kernel/prom.c by Stephen Rothwell and
 *  Grant Likely.
 */

#घोषणा pr_fmt(fmt)	"OF: " fmt

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/console.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/cpu.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/proc_fs.h>

#समावेश "of_private.h"

LIST_HEAD(aliases_lookup);

काष्ठा device_node *of_root;
EXPORT_SYMBOL(of_root);
काष्ठा device_node *of_chosen;
काष्ठा device_node *of_aliases;
काष्ठा device_node *of_मानक_निकास;
अटल स्थिर अक्षर *of_मानक_निकास_options;

काष्ठा kset *of_kset;

/*
 * Used to protect the of_aliases, to hold off addition of nodes to sysfs.
 * This mutex must be held whenever modअगरications are being made to the
 * device tree. The of_अणुattach,detachपूर्ण_node() and
 * of_अणुadd,हटाओ,updateपूर्ण_property() helpers make sure this happens.
 */
DEFINE_MUTEX(of_mutex);

/* use when traversing tree through the child, sibling,
 * or parent members of काष्ठा device_node.
 */
DEFINE_RAW_SPINLOCK(devtree_lock);

bool of_node_name_eq(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *node_name;
	माप_प्रकार len;

	अगर (!np)
		वापस false;

	node_name = kbasename(np->full_name);
	len = म_अक्षरnul(node_name, '@') - node_name;

	वापस (म_माप(name) == len) && (म_भेदन(node_name, name, len) == 0);
पूर्ण
EXPORT_SYMBOL(of_node_name_eq);

bool of_node_name_prefix(स्थिर काष्ठा device_node *np, स्थिर अक्षर *prefix)
अणु
	अगर (!np)
		वापस false;

	वापस म_भेदन(kbasename(np->full_name), prefix, म_माप(prefix)) == 0;
पूर्ण
EXPORT_SYMBOL(of_node_name_prefix);

अटल bool __of_node_is_type(स्थिर काष्ठा device_node *np, स्थिर अक्षर *type)
अणु
	स्थिर अक्षर *match = __of_get_property(np, "device_type", शून्य);

	वापस np && match && type && !म_भेद(match, type);
पूर्ण

पूर्णांक of_bus_n_addr_cells(काष्ठा device_node *np)
अणु
	u32 cells;

	क्रम (; np; np = np->parent)
		अगर (!of_property_पढ़ो_u32(np, "#address-cells", &cells))
			वापस cells;

	/* No #address-cells property क्रम the root node */
	वापस OF_ROOT_NODE_ADDR_CELLS_DEFAULT;
पूर्ण

पूर्णांक of_n_addr_cells(काष्ठा device_node *np)
अणु
	अगर (np->parent)
		np = np->parent;

	वापस of_bus_n_addr_cells(np);
पूर्ण
EXPORT_SYMBOL(of_n_addr_cells);

पूर्णांक of_bus_n_size_cells(काष्ठा device_node *np)
अणु
	u32 cells;

	क्रम (; np; np = np->parent)
		अगर (!of_property_पढ़ो_u32(np, "#size-cells", &cells))
			वापस cells;

	/* No #size-cells property क्रम the root node */
	वापस OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
पूर्ण

पूर्णांक of_n_size_cells(काष्ठा device_node *np)
अणु
	अगर (np->parent)
		np = np->parent;

	वापस of_bus_n_size_cells(np);
पूर्ण
EXPORT_SYMBOL(of_n_size_cells);

#अगर_घोषित CONFIG_NUMA
पूर्णांक __weak of_node_to_nid(काष्ठा device_node *np)
अणु
	वापस NUMA_NO_NODE;
पूर्ण
#पूर्ण_अगर

#घोषणा OF_PHANDLE_CACHE_BITS	7
#घोषणा OF_PHANDLE_CACHE_SZ	BIT(OF_PHANDLE_CACHE_BITS)

अटल काष्ठा device_node *phandle_cache[OF_PHANDLE_CACHE_SZ];

अटल u32 of_phandle_cache_hash(phandle handle)
अणु
	वापस hash_32(handle, OF_PHANDLE_CACHE_BITS);
पूर्ण

/*
 * Caller must hold devtree_lock.
 */
व्योम __of_phandle_cache_inv_entry(phandle handle)
अणु
	u32 handle_hash;
	काष्ठा device_node *np;

	अगर (!handle)
		वापस;

	handle_hash = of_phandle_cache_hash(handle);

	np = phandle_cache[handle_hash];
	अगर (np && handle == np->phandle)
		phandle_cache[handle_hash] = शून्य;
पूर्ण

व्योम __init of_core_init(व्योम)
अणु
	काष्ठा device_node *np;


	/* Create the kset, and रेजिस्टर existing nodes */
	mutex_lock(&of_mutex);
	of_kset = kset_create_and_add("devicetree", शून्य, firmware_kobj);
	अगर (!of_kset) अणु
		mutex_unlock(&of_mutex);
		pr_err("failed to register existing nodes\n");
		वापस;
	पूर्ण
	क्रम_each_of_allnodes(np) अणु
		__of_attach_node_sysfs(np);
		अगर (np->phandle && !phandle_cache[of_phandle_cache_hash(np->phandle)])
			phandle_cache[of_phandle_cache_hash(np->phandle)] = np;
	पूर्ण
	mutex_unlock(&of_mutex);

	/* Symlink in /proc as required by userspace ABI */
	अगर (of_root)
		proc_symlink("device-tree", शून्य, "/sys/firmware/devicetree/base");
पूर्ण

अटल काष्ठा property *__of_find_property(स्थिर काष्ठा device_node *np,
					   स्थिर अक्षर *name, पूर्णांक *lenp)
अणु
	काष्ठा property *pp;

	अगर (!np)
		वापस शून्य;

	क्रम (pp = np->properties; pp; pp = pp->next) अणु
		अगर (of_prop_cmp(pp->name, name) == 0) अणु
			अगर (lenp)
				*lenp = pp->length;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस pp;
पूर्ण

काष्ठा property *of_find_property(स्थिर काष्ठा device_node *np,
				  स्थिर अक्षर *name,
				  पूर्णांक *lenp)
अणु
	काष्ठा property *pp;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	pp = __of_find_property(np, name, lenp);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	वापस pp;
पूर्ण
EXPORT_SYMBOL(of_find_property);

काष्ठा device_node *__of_find_all_nodes(काष्ठा device_node *prev)
अणु
	काष्ठा device_node *np;
	अगर (!prev) अणु
		np = of_root;
	पूर्ण अन्यथा अगर (prev->child) अणु
		np = prev->child;
	पूर्ण अन्यथा अणु
		/* Walk back up looking क्रम a sibling, or the end of the काष्ठाure */
		np = prev;
		जबतक (np->parent && !np->sibling)
			np = np->parent;
		np = np->sibling; /* Might be null at the end of the tree */
	पूर्ण
	वापस np;
पूर्ण

/**
 * of_find_all_nodes - Get next node in global list
 * @prev:	Previous node or शून्य to start iteration
 *		of_node_put() will be called on it
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_all_nodes(काष्ठा device_node *prev)
अणु
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	np = __of_find_all_nodes(prev);
	of_node_get(np);
	of_node_put(prev);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_all_nodes);

/*
 * Find a property with a given name क्रम a given node
 * and वापस the value.
 */
स्थिर व्योम *__of_get_property(स्थिर काष्ठा device_node *np,
			      स्थिर अक्षर *name, पूर्णांक *lenp)
अणु
	काष्ठा property *pp = __of_find_property(np, name, lenp);

	वापस pp ? pp->value : शून्य;
पूर्ण

/*
 * Find a property with a given name क्रम a given node
 * and वापस the value.
 */
स्थिर व्योम *of_get_property(स्थिर काष्ठा device_node *np, स्थिर अक्षर *name,
			    पूर्णांक *lenp)
अणु
	काष्ठा property *pp = of_find_property(np, name, lenp);

	वापस pp ? pp->value : शून्य;
पूर्ण
EXPORT_SYMBOL(of_get_property);

/*
 * arch_match_cpu_phys_id - Match the given logical CPU and physical id
 *
 * @cpu: logical cpu index of a core/thपढ़ो
 * @phys_id: physical identअगरier of a core/thपढ़ो
 *
 * CPU logical to physical index mapping is architecture specअगरic.
 * However this __weak function provides a शेष match of physical
 * id to logical cpu index. phys_id provided here is usually values पढ़ो
 * from the device tree which must match the hardware पूर्णांकernal रेजिस्टरs.
 *
 * Returns true अगर the physical identअगरier and the logical cpu index
 * correspond to the same core/thपढ़ो, false otherwise.
 */
bool __weak arch_match_cpu_phys_id(पूर्णांक cpu, u64 phys_id)
अणु
	वापस (u32)phys_id == cpu;
पूर्ण

/*
 * Checks अगर the given "prop_name" property holds the physical id of the
 * core/thपढ़ो corresponding to the logical cpu 'cpu'. If 'thread' is not
 * शून्य, local thपढ़ो number within the core is वापसed in it.
 */
अटल bool __of_find_n_match_cpu_property(काष्ठा device_node *cpun,
			स्थिर अक्षर *prop_name, पूर्णांक cpu, अचिन्हित पूर्णांक *thपढ़ो)
अणु
	स्थिर __be32 *cell;
	पूर्णांक ac, prop_len, tid;
	u64 hwid;

	ac = of_n_addr_cells(cpun);
	cell = of_get_property(cpun, prop_name, &prop_len);
	अगर (!cell && !ac && arch_match_cpu_phys_id(cpu, 0))
		वापस true;
	अगर (!cell || !ac)
		वापस false;
	prop_len /= माप(*cell) * ac;
	क्रम (tid = 0; tid < prop_len; tid++) अणु
		hwid = of_पढ़ो_number(cell, ac);
		अगर (arch_match_cpu_phys_id(cpu, hwid)) अणु
			अगर (thपढ़ो)
				*thपढ़ो = tid;
			वापस true;
		पूर्ण
		cell += ac;
	पूर्ण
	वापस false;
पूर्ण

/*
 * arch_find_n_match_cpu_physical_id - See अगर the given device node is
 * क्रम the cpu corresponding to logical cpu 'cpu'.  Return true अगर so,
 * अन्यथा false.  If 'thread' is non-शून्य, the local thपढ़ो number within the
 * core is वापसed in it.
 */
bool __weak arch_find_n_match_cpu_physical_id(काष्ठा device_node *cpun,
					      पूर्णांक cpu, अचिन्हित पूर्णांक *thपढ़ो)
अणु
	/* Check क्रम non-standard "ibm,ppc-interrupt-server#s" property
	 * क्रम thपढ़ो ids on PowerPC. If it करोesn't exist fallback to
	 * standard "reg" property.
	 */
	अगर (IS_ENABLED(CONFIG_PPC) &&
	    __of_find_n_match_cpu_property(cpun,
					   "ibm,ppc-interrupt-server#s",
					   cpu, thपढ़ो))
		वापस true;

	वापस __of_find_n_match_cpu_property(cpun, "reg", cpu, thपढ़ो);
पूर्ण

/**
 * of_get_cpu_node - Get device node associated with the given logical CPU
 *
 * @cpu: CPU number(logical index) क्रम which device node is required
 * @thपढ़ो: अगर not शून्य, local thपढ़ो number within the physical core is
 *          वापसed
 *
 * The मुख्य purpose of this function is to retrieve the device node क्रम the
 * given logical CPU index. It should be used to initialize the of_node in
 * cpu device. Once of_node in cpu device is populated, all the further
 * references can use that instead.
 *
 * CPU logical to physical index mapping is architecture specअगरic and is built
 * beक्रमe booting secondary cores. This function uses arch_match_cpu_phys_id
 * which can be overridden by architecture specअगरic implementation.
 *
 * Return: A node poपूर्णांकer क्रम the logical cpu with refcount incremented, use
 * of_node_put() on it when करोne. Returns शून्य अगर not found.
 */
काष्ठा device_node *of_get_cpu_node(पूर्णांक cpu, अचिन्हित पूर्णांक *thपढ़ो)
अणु
	काष्ठा device_node *cpun;

	क्रम_each_of_cpu_node(cpun) अणु
		अगर (arch_find_n_match_cpu_physical_id(cpun, cpu, thपढ़ो))
			वापस cpun;
	पूर्ण
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(of_get_cpu_node);

/**
 * of_cpu_node_to_id: Get the logical CPU number क्रम a given device_node
 *
 * @cpu_node: Poपूर्णांकer to the device_node क्रम CPU.
 *
 * Return: The logical CPU number of the given CPU device_node or -ENODEV अगर the
 * CPU is not found.
 */
पूर्णांक of_cpu_node_to_id(काष्ठा device_node *cpu_node)
अणु
	पूर्णांक cpu;
	bool found = false;
	काष्ठा device_node *np;

	क्रम_each_possible_cpu(cpu) अणु
		np = of_cpu_device_node_get(cpu);
		found = (cpu_node == np);
		of_node_put(np);
		अगर (found)
			वापस cpu;
	पूर्ण

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(of_cpu_node_to_id);

/**
 * of_get_cpu_state_node - Get CPU's idle state node at the given index
 *
 * @cpu_node: The device node क्रम the CPU
 * @index: The index in the list of the idle states
 *
 * Two generic methods can be used to describe a CPU's idle states, either via
 * a flattened description through the "cpu-idle-states" binding or via the
 * hierarchical layout, using the "power-domains" and the "domain-idle-states"
 * bindings. This function check क्रम both and वापसs the idle state node क्रम
 * the requested index.
 *
 * Return: An idle state node अगर found at @index. The refcount is incremented
 * क्रम it, so call of_node_put() on it when करोne. Returns शून्य अगर not found.
 */
काष्ठा device_node *of_get_cpu_state_node(काष्ठा device_node *cpu_node,
					  पूर्णांक index)
अणु
	काष्ठा of_phandle_args args;
	पूर्णांक err;

	err = of_parse_phandle_with_args(cpu_node, "power-domains",
					"#power-domain-cells", 0, &args);
	अगर (!err) अणु
		काष्ठा device_node *state_node =
			of_parse_phandle(args.np, "domain-idle-states", index);

		of_node_put(args.np);
		अगर (state_node)
			वापस state_node;
	पूर्ण

	वापस of_parse_phandle(cpu_node, "cpu-idle-states", index);
पूर्ण
EXPORT_SYMBOL(of_get_cpu_state_node);

/**
 * __of_device_is_compatible() - Check अगर the node matches given स्थिरraपूर्णांकs
 * @device: poपूर्णांकer to node
 * @compat: required compatible string, शून्य or "" क्रम any match
 * @type: required device_type value, शून्य or "" क्रम any match
 * @name: required node name, शून्य or "" क्रम any match
 *
 * Checks अगर the given @compat, @type and @name strings match the
 * properties of the given @device. A स्थिरraपूर्णांकs can be skipped by
 * passing शून्य or an empty string as the स्थिरraपूर्णांक.
 *
 * Returns 0 क्रम no match, and a positive पूर्णांकeger on match. The वापस
 * value is a relative score with larger values indicating better
 * matches. The score is weighted क्रम the most specअगरic compatible value
 * to get the highest score. Matching type is next, followed by matching
 * name. Practically speaking, this results in the following priority
 * order क्रम matches:
 *
 * 1. specअगरic compatible && type && name
 * 2. specअगरic compatible && type
 * 3. specअगरic compatible && name
 * 4. specअगरic compatible
 * 5. general compatible && type && name
 * 6. general compatible && type
 * 7. general compatible && name
 * 8. general compatible
 * 9. type && name
 * 10. type
 * 11. name
 */
अटल पूर्णांक __of_device_is_compatible(स्थिर काष्ठा device_node *device,
				     स्थिर अक्षर *compat, स्थिर अक्षर *type, स्थिर अक्षर *name)
अणु
	काष्ठा property *prop;
	स्थिर अक्षर *cp;
	पूर्णांक index = 0, score = 0;

	/* Compatible match has highest priority */
	अगर (compat && compat[0]) अणु
		prop = __of_find_property(device, "compatible", शून्य);
		क्रम (cp = of_prop_next_string(prop, शून्य); cp;
		     cp = of_prop_next_string(prop, cp), index++) अणु
			अगर (of_compat_cmp(cp, compat, म_माप(compat)) == 0) अणु
				score = पूर्णांक_उच्च/2 - (index << 2);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!score)
			वापस 0;
	पूर्ण

	/* Matching type is better than matching name */
	अगर (type && type[0]) अणु
		अगर (!__of_node_is_type(device, type))
			वापस 0;
		score += 2;
	पूर्ण

	/* Matching name is a bit better than not */
	अगर (name && name[0]) अणु
		अगर (!of_node_name_eq(device, name))
			वापस 0;
		score++;
	पूर्ण

	वापस score;
पूर्ण

/** Checks अगर the given "compat" string matches one of the strings in
 * the device's "compatible" property
 */
पूर्णांक of_device_is_compatible(स्थिर काष्ठा device_node *device,
		स्थिर अक्षर *compat)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक res;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	res = __of_device_is_compatible(device, compat, शून्य, शून्य);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस res;
पूर्ण
EXPORT_SYMBOL(of_device_is_compatible);

/** Checks अगर the device is compatible with any of the entries in
 *  a शून्य terminated array of strings. Returns the best match
 *  score or 0.
 */
पूर्णांक of_device_compatible_match(काष्ठा device_node *device,
			       स्थिर अक्षर *स्थिर *compat)
अणु
	अचिन्हित पूर्णांक पंचांगp, score = 0;

	अगर (!compat)
		वापस 0;

	जबतक (*compat) अणु
		पंचांगp = of_device_is_compatible(device, *compat);
		अगर (पंचांगp > score)
			score = पंचांगp;
		compat++;
	पूर्ण

	वापस score;
पूर्ण

/**
 * of_machine_is_compatible - Test root of device tree क्रम a given compatible value
 * @compat: compatible string to look क्रम in root node's compatible property.
 *
 * Return: A positive पूर्णांकeger अगर the root node has the given value in its
 * compatible property.
 */
पूर्णांक of_machine_is_compatible(स्थिर अक्षर *compat)
अणु
	काष्ठा device_node *root;
	पूर्णांक rc = 0;

	root = of_find_node_by_path("/");
	अगर (root) अणु
		rc = of_device_is_compatible(root, compat);
		of_node_put(root);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(of_machine_is_compatible);

/**
 *  __of_device_is_available - check अगर a device is available क्रम use
 *
 *  @device: Node to check क्रम availability, with locks alपढ़ोy held
 *
 *  Return: True अगर the status property is असलent or set to "okay" or "ok",
 *  false otherwise
 */
अटल bool __of_device_is_available(स्थिर काष्ठा device_node *device)
अणु
	स्थिर अक्षर *status;
	पूर्णांक statlen;

	अगर (!device)
		वापस false;

	status = __of_get_property(device, "status", &statlen);
	अगर (status == शून्य)
		वापस true;

	अगर (statlen > 0) अणु
		अगर (!म_भेद(status, "okay") || !म_भेद(status, "ok"))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 *  of_device_is_available - check अगर a device is available क्रम use
 *
 *  @device: Node to check क्रम availability
 *
 *  Return: True अगर the status property is असलent or set to "okay" or "ok",
 *  false otherwise
 */
bool of_device_is_available(स्थिर काष्ठा device_node *device)
अणु
	अचिन्हित दीर्घ flags;
	bool res;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	res = __of_device_is_available(device);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस res;

पूर्ण
EXPORT_SYMBOL(of_device_is_available);

/**
 *  of_device_is_big_endian - check अगर a device has BE रेजिस्टरs
 *
 *  @device: Node to check क्रम endianness
 *
 *  Return: True अगर the device has a "big-endian" property, or अगर the kernel
 *  was compiled क्रम BE *and* the device has a "native-endian" property.
 *  Returns false otherwise.
 *
 *  Callers would nominally use ioपढ़ो32be/ioग_लिखो32be अगर
 *  of_device_is_big_endian() == true, or पढ़ोl/ग_लिखोl otherwise.
 */
bool of_device_is_big_endian(स्थिर काष्ठा device_node *device)
अणु
	अगर (of_property_पढ़ो_bool(device, "big-endian"))
		वापस true;
	अगर (IS_ENABLED(CONFIG_CPU_BIG_ENDIAN) &&
	    of_property_पढ़ो_bool(device, "native-endian"))
		वापस true;
	वापस false;
पूर्ण
EXPORT_SYMBOL(of_device_is_big_endian);

/**
 * of_get_parent - Get a node's parent अगर any
 * @node:	Node to get parent
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_get_parent(स्थिर काष्ठा device_node *node)
अणु
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;

	अगर (!node)
		वापस शून्य;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	np = of_node_get(node->parent);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_get_parent);

/**
 * of_get_next_parent - Iterate to a node's parent
 * @node:	Node to get parent of
 *
 * This is like of_get_parent() except that it drops the
 * refcount on the passed node, making it suitable क्रम iterating
 * through a node's parents.
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_get_next_parent(काष्ठा device_node *node)
अणु
	काष्ठा device_node *parent;
	अचिन्हित दीर्घ flags;

	अगर (!node)
		वापस शून्य;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	parent = of_node_get(node->parent);
	of_node_put(node);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस parent;
पूर्ण
EXPORT_SYMBOL(of_get_next_parent);

अटल काष्ठा device_node *__of_get_next_child(स्थिर काष्ठा device_node *node,
						काष्ठा device_node *prev)
अणु
	काष्ठा device_node *next;

	अगर (!node)
		वापस शून्य;

	next = prev ? prev->sibling : node->child;
	क्रम (; next; next = next->sibling)
		अगर (of_node_get(next))
			अवरोध;
	of_node_put(prev);
	वापस next;
पूर्ण
#घोषणा __क्रम_each_child_of_node(parent, child) \
	क्रम (child = __of_get_next_child(parent, शून्य); child != शून्य; \
	     child = __of_get_next_child(parent, child))

/**
 * of_get_next_child - Iterate a node childs
 * @node:	parent node
 * @prev:	previous child of the parent node, or शून्य to get first
 *
 * Return: A node poपूर्णांकer with refcount incremented, use of_node_put() on
 * it when करोne. Returns शून्य when prev is the last child. Decrements the
 * refcount of prev.
 */
काष्ठा device_node *of_get_next_child(स्थिर काष्ठा device_node *node,
	काष्ठा device_node *prev)
अणु
	काष्ठा device_node *next;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	next = __of_get_next_child(node, prev);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस next;
पूर्ण
EXPORT_SYMBOL(of_get_next_child);

/**
 * of_get_next_available_child - Find the next available child node
 * @node:	parent node
 * @prev:	previous child of the parent node, or शून्य to get first
 *
 * This function is like of_get_next_child(), except that it
 * स्वतःmatically skips any disabled nodes (i.e. status = "disabled").
 */
काष्ठा device_node *of_get_next_available_child(स्थिर काष्ठा device_node *node,
	काष्ठा device_node *prev)
अणु
	काष्ठा device_node *next;
	अचिन्हित दीर्घ flags;

	अगर (!node)
		वापस शून्य;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	next = prev ? prev->sibling : node->child;
	क्रम (; next; next = next->sibling) अणु
		अगर (!__of_device_is_available(next))
			जारी;
		अगर (of_node_get(next))
			अवरोध;
	पूर्ण
	of_node_put(prev);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस next;
पूर्ण
EXPORT_SYMBOL(of_get_next_available_child);

/**
 * of_get_next_cpu_node - Iterate on cpu nodes
 * @prev:	previous child of the /cpus node, or शून्य to get first
 *
 * Return: A cpu node poपूर्णांकer with refcount incremented, use of_node_put()
 * on it when करोne. Returns शून्य when prev is the last child. Decrements
 * the refcount of prev.
 */
काष्ठा device_node *of_get_next_cpu_node(काष्ठा device_node *prev)
अणु
	काष्ठा device_node *next = शून्य;
	अचिन्हित दीर्घ flags;
	काष्ठा device_node *node;

	अगर (!prev)
		node = of_find_node_by_path("/cpus");

	raw_spin_lock_irqsave(&devtree_lock, flags);
	अगर (prev)
		next = prev->sibling;
	अन्यथा अगर (node) अणु
		next = node->child;
		of_node_put(node);
	पूर्ण
	क्रम (; next; next = next->sibling) अणु
		अगर (!(of_node_name_eq(next, "cpu") ||
		      __of_node_is_type(next, "cpu")))
			जारी;
		अगर (of_node_get(next))
			अवरोध;
	पूर्ण
	of_node_put(prev);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस next;
पूर्ण
EXPORT_SYMBOL(of_get_next_cpu_node);

/**
 * of_get_compatible_child - Find compatible child node
 * @parent:	parent node
 * @compatible:	compatible string
 *
 * Lookup child node whose compatible property contains the given compatible
 * string.
 *
 * Return: a node poपूर्णांकer with refcount incremented, use of_node_put() on it
 * when करोne; or शून्य अगर not found.
 */
काष्ठा device_node *of_get_compatible_child(स्थिर काष्ठा device_node *parent,
				स्थिर अक्षर *compatible)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(parent, child) अणु
		अगर (of_device_is_compatible(child, compatible))
			अवरोध;
	पूर्ण

	वापस child;
पूर्ण
EXPORT_SYMBOL(of_get_compatible_child);

/**
 * of_get_child_by_name - Find the child node by name क्रम a given parent
 * @node:	parent node
 * @name:	child name to look क्रम.
 *
 * This function looks क्रम child node क्रम given matching name
 *
 * Return: A node poपूर्णांकer अगर found, with refcount incremented, use
 * of_node_put() on it when करोne.
 * Returns शून्य अगर node is not found.
 */
काष्ठा device_node *of_get_child_by_name(स्थिर काष्ठा device_node *node,
				स्थिर अक्षर *name)
अणु
	काष्ठा device_node *child;

	क्रम_each_child_of_node(node, child)
		अगर (of_node_name_eq(child, name))
			अवरोध;
	वापस child;
पूर्ण
EXPORT_SYMBOL(of_get_child_by_name);

काष्ठा device_node *__of_find_node_by_path(काष्ठा device_node *parent,
						स्थिर अक्षर *path)
अणु
	काष्ठा device_node *child;
	पूर्णांक len;

	len = म_खोज(path, "/:");
	अगर (!len)
		वापस शून्य;

	__क्रम_each_child_of_node(parent, child) अणु
		स्थिर अक्षर *name = kbasename(child->full_name);
		अगर (म_भेदन(path, name, len) == 0 && (म_माप(name) == len))
			वापस child;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा device_node *__of_find_node_by_full_path(काष्ठा device_node *node,
						स्थिर अक्षर *path)
अणु
	स्थिर अक्षर *separator = म_अक्षर(path, ':');

	जबतक (node && *path == '/') अणु
		काष्ठा device_node *पंचांगp = node;

		path++; /* Increment past '/' delimiter */
		node = __of_find_node_by_path(node, path);
		of_node_put(पंचांगp);
		path = म_अक्षरnul(path, '/');
		अगर (separator && separator < path)
			अवरोध;
	पूर्ण
	वापस node;
पूर्ण

/**
 * of_find_node_opts_by_path - Find a node matching a full OF path
 * @path: Either the full path to match, or अगर the path करोes not
 *       start with '/', the name of a property of the /aliases
 *       node (an alias).  In the हाल of an alias, the node
 *       matching the alias' value will be वापसed.
 * @opts: Address of a poपूर्णांकer पूर्णांकo which to store the start of
 *       an options string appended to the end of the path with
 *       a ':' separator.
 *
 * Valid paths:
 *  * /foo/bar	Full path
 *  * foo	Valid alias
 *  * foo/bar	Valid alias + relative path
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_node_opts_by_path(स्थिर अक्षर *path, स्थिर अक्षर **opts)
अणु
	काष्ठा device_node *np = शून्य;
	काष्ठा property *pp;
	अचिन्हित दीर्घ flags;
	स्थिर अक्षर *separator = म_अक्षर(path, ':');

	अगर (opts)
		*opts = separator ? separator + 1 : शून्य;

	अगर (म_भेद(path, "/") == 0)
		वापस of_node_get(of_root);

	/* The path could begin with an alias */
	अगर (*path != '/') अणु
		पूर्णांक len;
		स्थिर अक्षर *p = separator;

		अगर (!p)
			p = म_अक्षरnul(path, '/');
		len = p - path;

		/* of_aliases must not be शून्य */
		अगर (!of_aliases)
			वापस शून्य;

		क्रम_each_property_of_node(of_aliases, pp) अणु
			अगर (म_माप(pp->name) == len && !म_भेदन(pp->name, path, len)) अणु
				np = of_find_node_by_path(pp->value);
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!np)
			वापस शून्य;
		path = p;
	पूर्ण

	/* Step करोwn the tree matching path components */
	raw_spin_lock_irqsave(&devtree_lock, flags);
	अगर (!np)
		np = of_node_get(of_root);
	np = __of_find_node_by_full_path(np, path);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_node_opts_by_path);

/**
 * of_find_node_by_name - Find a node by its "name" property
 * @from:	The node to start searching from or शून्य; the node
 *		you pass will not be searched, only the next one
 *		will. Typically, you pass what the previous call
 *		वापसed. of_node_put() will be called on @from.
 * @name:	The name string to match against
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_node_by_name(काष्ठा device_node *from,
	स्थिर अक्षर *name)
अणु
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	क्रम_each_of_allnodes_from(from, np)
		अगर (of_node_name_eq(np, name) && of_node_get(np))
			अवरोध;
	of_node_put(from);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_node_by_name);

/**
 * of_find_node_by_type - Find a node by its "device_type" property
 * @from:	The node to start searching from, or शून्य to start searching
 *		the entire device tree. The node you pass will not be
 *		searched, only the next one will; typically, you pass
 *		what the previous call वापसed. of_node_put() will be
 *		called on from क्रम you.
 * @type:	The type string to match against
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_node_by_type(काष्ठा device_node *from,
	स्थिर अक्षर *type)
अणु
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	क्रम_each_of_allnodes_from(from, np)
		अगर (__of_node_is_type(np, type) && of_node_get(np))
			अवरोध;
	of_node_put(from);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_node_by_type);

/**
 * of_find_compatible_node - Find a node based on type and one of the
 *                                tokens in its "compatible" property
 * @from:	The node to start searching from or शून्य, the node
 *		you pass will not be searched, only the next one
 *		will; typically, you pass what the previous call
 *		वापसed. of_node_put() will be called on it
 * @type:	The type string to match "device_type" or शून्य to ignore
 * @compatible:	The string to match to one of the tokens in the device
 *		"compatible" list.
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_compatible_node(काष्ठा device_node *from,
	स्थिर अक्षर *type, स्थिर अक्षर *compatible)
अणु
	काष्ठा device_node *np;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	क्रम_each_of_allnodes_from(from, np)
		अगर (__of_device_is_compatible(np, compatible, type, शून्य) &&
		    of_node_get(np))
			अवरोध;
	of_node_put(from);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_compatible_node);

/**
 * of_find_node_with_property - Find a node which has a property with
 *                              the given name.
 * @from:	The node to start searching from or शून्य, the node
 *		you pass will not be searched, only the next one
 *		will; typically, you pass what the previous call
 *		वापसed. of_node_put() will be called on it
 * @prop_name:	The name of the property to look क्रम.
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_node_with_property(काष्ठा device_node *from,
	स्थिर अक्षर *prop_name)
अणु
	काष्ठा device_node *np;
	काष्ठा property *pp;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	क्रम_each_of_allnodes_from(from, np) अणु
		क्रम (pp = np->properties; pp; pp = pp->next) अणु
			अगर (of_prop_cmp(pp->name, prop_name) == 0) अणु
				of_node_get(np);
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	of_node_put(from);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_node_with_property);

अटल
स्थिर काष्ठा of_device_id *__of_match_node(स्थिर काष्ठा of_device_id *matches,
					   स्थिर काष्ठा device_node *node)
अणु
	स्थिर काष्ठा of_device_id *best_match = शून्य;
	पूर्णांक score, best_score = 0;

	अगर (!matches)
		वापस शून्य;

	क्रम (; matches->name[0] || matches->type[0] || matches->compatible[0]; matches++) अणु
		score = __of_device_is_compatible(node, matches->compatible,
						  matches->type, matches->name);
		अगर (score > best_score) अणु
			best_match = matches;
			best_score = score;
		पूर्ण
	पूर्ण

	वापस best_match;
पूर्ण

/**
 * of_match_node - Tell अगर a device_node has a matching of_match काष्ठाure
 * @matches:	array of of device match काष्ठाures to search in
 * @node:	the of device काष्ठाure to match against
 *
 * Low level utility function used by device matching.
 */
स्थिर काष्ठा of_device_id *of_match_node(स्थिर काष्ठा of_device_id *matches,
					 स्थिर काष्ठा device_node *node)
अणु
	स्थिर काष्ठा of_device_id *match;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	match = __of_match_node(matches, node);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस match;
पूर्ण
EXPORT_SYMBOL(of_match_node);

/**
 * of_find_matching_node_and_match - Find a node based on an of_device_id
 *				     match table.
 * @from:	The node to start searching from or शून्य, the node
 *		you pass will not be searched, only the next one
 *		will; typically, you pass what the previous call
 *		वापसed. of_node_put() will be called on it
 * @matches:	array of of device match काष्ठाures to search in
 * @match:	Updated to poपूर्णांक at the matches entry which matched
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_matching_node_and_match(काष्ठा device_node *from,
					स्थिर काष्ठा of_device_id *matches,
					स्थिर काष्ठा of_device_id **match)
अणु
	काष्ठा device_node *np;
	स्थिर काष्ठा of_device_id *m;
	अचिन्हित दीर्घ flags;

	अगर (match)
		*match = शून्य;

	raw_spin_lock_irqsave(&devtree_lock, flags);
	क्रम_each_of_allnodes_from(from, np) अणु
		m = __of_match_node(matches, np);
		अगर (m && of_node_get(np)) अणु
			अगर (match)
				*match = m;
			अवरोध;
		पूर्ण
	पूर्ण
	of_node_put(from);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_matching_node_and_match);

/**
 * of_modalias_node - Lookup appropriate modalias क्रम a device node
 * @node:	poपूर्णांकer to a device tree node
 * @modalias:	Poपूर्णांकer to buffer that modalias value will be copied पूर्णांकo
 * @len:	Length of modalias value
 *
 * Based on the value of the compatible property, this routine will attempt
 * to choose an appropriate modalias value क्रम a particular device tree node.
 * It करोes this by stripping the manufacturer prefix (as delimited by a ',')
 * from the first entry in the compatible list property.
 *
 * Return: This routine वापसs 0 on success, <0 on failure.
 */
पूर्णांक of_modalias_node(काष्ठा device_node *node, अक्षर *modalias, पूर्णांक len)
अणु
	स्थिर अक्षर *compatible, *p;
	पूर्णांक cplen;

	compatible = of_get_property(node, "compatible", &cplen);
	अगर (!compatible || म_माप(compatible) > cplen)
		वापस -ENODEV;
	p = म_अक्षर(compatible, ',');
	strlcpy(modalias, p ? p + 1 : compatible, len);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_modalias_node);

/**
 * of_find_node_by_phandle - Find a node given a phandle
 * @handle:	phandle of the node to find
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_find_node_by_phandle(phandle handle)
अणु
	काष्ठा device_node *np = शून्य;
	अचिन्हित दीर्घ flags;
	u32 handle_hash;

	अगर (!handle)
		वापस शून्य;

	handle_hash = of_phandle_cache_hash(handle);

	raw_spin_lock_irqsave(&devtree_lock, flags);

	अगर (phandle_cache[handle_hash] &&
	    handle == phandle_cache[handle_hash]->phandle)
		np = phandle_cache[handle_hash];

	अगर (!np) अणु
		क्रम_each_of_allnodes(np)
			अगर (np->phandle == handle &&
			    !of_node_check_flag(np, OF_DETACHED)) अणु
				phandle_cache[handle_hash] = np;
				अवरोध;
			पूर्ण
	पूर्ण

	of_node_get(np);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	वापस np;
पूर्ण
EXPORT_SYMBOL(of_find_node_by_phandle);

व्योम of_prपूर्णांक_phandle_args(स्थिर अक्षर *msg, स्थिर काष्ठा of_phandle_args *args)
अणु
	पूर्णांक i;
	prपूर्णांकk("%s %pOF", msg, args->np);
	क्रम (i = 0; i < args->args_count; i++) अणु
		स्थिर अक्षर delim = i ? ',' : ':';

		pr_cont("%c%08x", delim, args->args[i]);
	पूर्ण
	pr_cont("\n");
पूर्ण

पूर्णांक of_phandle_iterator_init(काष्ठा of_phandle_iterator *it,
		स्थिर काष्ठा device_node *np,
		स्थिर अक्षर *list_name,
		स्थिर अक्षर *cells_name,
		पूर्णांक cell_count)
अणु
	स्थिर __be32 *list;
	पूर्णांक size;

	स_रखो(it, 0, माप(*it));

	/*
	 * one of cell_count or cells_name must be provided to determine the
	 * argument length.
	 */
	अगर (cell_count < 0 && !cells_name)
		वापस -EINVAL;

	list = of_get_property(np, list_name, &size);
	अगर (!list)
		वापस -ENOENT;

	it->cells_name = cells_name;
	it->cell_count = cell_count;
	it->parent = np;
	it->list_end = list + size / माप(*list);
	it->phandle_end = list;
	it->cur = list;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_phandle_iterator_init);

पूर्णांक of_phandle_iterator_next(काष्ठा of_phandle_iterator *it)
अणु
	uपूर्णांक32_t count = 0;

	अगर (it->node) अणु
		of_node_put(it->node);
		it->node = शून्य;
	पूर्ण

	अगर (!it->cur || it->phandle_end >= it->list_end)
		वापस -ENOENT;

	it->cur = it->phandle_end;

	/* If phandle is 0, then it is an empty entry with no arguments. */
	it->phandle = be32_to_cpup(it->cur++);

	अगर (it->phandle) अणु

		/*
		 * Find the provider node and parse the #*-cells property to
		 * determine the argument length.
		 */
		it->node = of_find_node_by_phandle(it->phandle);

		अगर (it->cells_name) अणु
			अगर (!it->node) अणु
				pr_err("%pOF: could not find phandle %d\n",
				       it->parent, it->phandle);
				जाओ err;
			पूर्ण

			अगर (of_property_पढ़ो_u32(it->node, it->cells_name,
						 &count)) अणु
				/*
				 * If both cell_count and cells_name is given,
				 * fall back to cell_count in असलence
				 * of the cells_name property
				 */
				अगर (it->cell_count >= 0) अणु
					count = it->cell_count;
				पूर्ण अन्यथा अणु
					pr_err("%pOF: could not get %s for %pOF\n",
					       it->parent,
					       it->cells_name,
					       it->node);
					जाओ err;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			count = it->cell_count;
		पूर्ण

		/*
		 * Make sure that the arguments actually fit in the reमुख्यing
		 * property data length
		 */
		अगर (it->cur + count > it->list_end) अणु
			pr_err("%pOF: %s = %d found %d\n",
			       it->parent, it->cells_name,
			       count, it->cell_count);
			जाओ err;
		पूर्ण
	पूर्ण

	it->phandle_end = it->cur + count;
	it->cur_count = count;

	वापस 0;

err:
	अगर (it->node) अणु
		of_node_put(it->node);
		it->node = शून्य;
	पूर्ण

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(of_phandle_iterator_next);

पूर्णांक of_phandle_iterator_args(काष्ठा of_phandle_iterator *it,
			     uपूर्णांक32_t *args,
			     पूर्णांक size)
अणु
	पूर्णांक i, count;

	count = it->cur_count;

	अगर (WARN_ON(size < count))
		count = size;

	क्रम (i = 0; i < count; i++)
		args[i] = be32_to_cpup(it->cur++);

	वापस count;
पूर्ण

अटल पूर्णांक __of_parse_phandle_with_args(स्थिर काष्ठा device_node *np,
					स्थिर अक्षर *list_name,
					स्थिर अक्षर *cells_name,
					पूर्णांक cell_count, पूर्णांक index,
					काष्ठा of_phandle_args *out_args)
अणु
	काष्ठा of_phandle_iterator it;
	पूर्णांक rc, cur_index = 0;

	/* Loop over the phandles until all the requested entry is found */
	of_क्रम_each_phandle(&it, rc, np, list_name, cells_name, cell_count) अणु
		/*
		 * All of the error हालs bail out of the loop, so at
		 * this poपूर्णांक, the parsing is successful. If the requested
		 * index matches, then fill the out_args काष्ठाure and वापस,
		 * or वापस -ENOENT क्रम an empty entry.
		 */
		rc = -ENOENT;
		अगर (cur_index == index) अणु
			अगर (!it.phandle)
				जाओ err;

			अगर (out_args) अणु
				पूर्णांक c;

				c = of_phandle_iterator_args(&it,
							     out_args->args,
							     MAX_PHANDLE_ARGS);
				out_args->np = it.node;
				out_args->args_count = c;
			पूर्ण अन्यथा अणु
				of_node_put(it.node);
			पूर्ण

			/* Found it! वापस success */
			वापस 0;
		पूर्ण

		cur_index++;
	पूर्ण

	/*
	 * Unlock node beक्रमe वापसing result; will be one of:
	 * -ENOENT : index is क्रम empty phandle
	 * -EINVAL : parsing error on data
	 */

 err:
	of_node_put(it.node);
	वापस rc;
पूर्ण

/**
 * of_parse_phandle - Resolve a phandle property to a device_node poपूर्णांकer
 * @np: Poपूर्णांकer to device node holding phandle property
 * @phandle_name: Name of property holding a phandle value
 * @index: For properties holding a table of phandles, this is the index पूर्णांकo
 *         the table
 *
 * Return: The device_node poपूर्णांकer with refcount incremented.  Use
 * of_node_put() on it when करोne.
 */
काष्ठा device_node *of_parse_phandle(स्थिर काष्ठा device_node *np,
				     स्थिर अक्षर *phandle_name, पूर्णांक index)
अणु
	काष्ठा of_phandle_args args;

	अगर (index < 0)
		वापस शून्य;

	अगर (__of_parse_phandle_with_args(np, phandle_name, शून्य, 0,
					 index, &args))
		वापस शून्य;

	वापस args.np;
पूर्ण
EXPORT_SYMBOL(of_parse_phandle);

/**
 * of_parse_phandle_with_args() - Find a node poपूर्णांकed by phandle in a list
 * @np:		poपूर्णांकer to a device tree node containing a list
 * @list_name:	property name that contains a list
 * @cells_name:	property name that specअगरies phandles' arguments count
 * @index:	index of a phandle to parse out
 * @out_args:	optional poपूर्णांकer to output arguments काष्ठाure (will be filled)
 *
 * This function is useful to parse lists of phandles and their arguments.
 * Returns 0 on success and fills out_args, on error वापसs appropriate
 * त्रुटि_सं value.
 *
 * Caller is responsible to call of_node_put() on the वापसed out_args->np
 * poपूर्णांकer.
 *
 * Example::
 *
 *  phandle1: node1 अणु
 *	#list-cells = <2>;
 *  पूर्ण;
 *
 *  phandle2: node2 अणु
 *	#list-cells = <1>;
 *  पूर्ण;
 *
 *  node3 अणु
 *	list = <&phandle1 1 2 &phandle2 3>;
 *  पूर्ण;
 *
 * To get a device_node of the ``node2`` node you may call this:
 * of_parse_phandle_with_args(node3, "list", "#list-cells", 1, &args);
 */
पूर्णांक of_parse_phandle_with_args(स्थिर काष्ठा device_node *np, स्थिर अक्षर *list_name,
				स्थिर अक्षर *cells_name, पूर्णांक index,
				काष्ठा of_phandle_args *out_args)
अणु
	पूर्णांक cell_count = -1;

	अगर (index < 0)
		वापस -EINVAL;

	/* If cells_name is शून्य we assume a cell count of 0 */
	अगर (!cells_name)
		cell_count = 0;

	वापस __of_parse_phandle_with_args(np, list_name, cells_name,
					    cell_count, index, out_args);
पूर्ण
EXPORT_SYMBOL(of_parse_phandle_with_args);

/**
 * of_parse_phandle_with_args_map() - Find a node poपूर्णांकed by phandle in a list and remap it
 * @np:		poपूर्णांकer to a device tree node containing a list
 * @list_name:	property name that contains a list
 * @stem_name:	stem of property names that specअगरy phandles' arguments count
 * @index:	index of a phandle to parse out
 * @out_args:	optional poपूर्णांकer to output arguments काष्ठाure (will be filled)
 *
 * This function is useful to parse lists of phandles and their arguments.
 * Returns 0 on success and fills out_args, on error वापसs appropriate त्रुटि_सं
 * value. The dअगरference between this function and of_parse_phandle_with_args()
 * is that this API remaps a phandle अगर the node the phandle poपूर्णांकs to has
 * a <@stem_name>-map property.
 *
 * Caller is responsible to call of_node_put() on the वापसed out_args->np
 * poपूर्णांकer.
 *
 * Example::
 *
 *  phandle1: node1 अणु
 *  	#list-cells = <2>;
 *  पूर्ण;
 *
 *  phandle2: node2 अणु
 *  	#list-cells = <1>;
 *  पूर्ण;
 *
 *  phandle3: node3 अणु
 *  	#list-cells = <1>;
 *  	list-map = <0 &phandle2 3>,
 *  		   <1 &phandle2 2>,
 *  		   <2 &phandle1 5 1>;
 *  	list-map-mask = <0x3>;
 *  पूर्ण;
 *
 *  node4 अणु
 *  	list = <&phandle1 1 2 &phandle3 0>;
 *  पूर्ण;
 *
 * To get a device_node of the ``node2`` node you may call this:
 * of_parse_phandle_with_args(node4, "list", "list", 1, &args);
 */
पूर्णांक of_parse_phandle_with_args_map(स्थिर काष्ठा device_node *np,
				   स्थिर अक्षर *list_name,
				   स्थिर अक्षर *stem_name,
				   पूर्णांक index, काष्ठा of_phandle_args *out_args)
अणु
	अक्षर *cells_name, *map_name = शून्य, *mask_name = शून्य;
	अक्षर *pass_name = शून्य;
	काष्ठा device_node *cur, *new = शून्य;
	स्थिर __be32 *map, *mask, *pass;
	अटल स्थिर __be32 dummy_mask[] = अणु [0 ... MAX_PHANDLE_ARGS] = ~0 पूर्ण;
	अटल स्थिर __be32 dummy_pass[] = अणु [0 ... MAX_PHANDLE_ARGS] = 0 पूर्ण;
	__be32 initial_match_array[MAX_PHANDLE_ARGS];
	स्थिर __be32 *match_array = initial_match_array;
	पूर्णांक i, ret, map_len, match;
	u32 list_size, new_size;

	अगर (index < 0)
		वापस -EINVAL;

	cells_name = kaप्र_लिखो(GFP_KERNEL, "#%s-cells", stem_name);
	अगर (!cells_name)
		वापस -ENOMEM;

	ret = -ENOMEM;
	map_name = kaप्र_लिखो(GFP_KERNEL, "%s-map", stem_name);
	अगर (!map_name)
		जाओ मुक्त;

	mask_name = kaप्र_लिखो(GFP_KERNEL, "%s-map-mask", stem_name);
	अगर (!mask_name)
		जाओ मुक्त;

	pass_name = kaप्र_लिखो(GFP_KERNEL, "%s-map-pass-thru", stem_name);
	अगर (!pass_name)
		जाओ मुक्त;

	ret = __of_parse_phandle_with_args(np, list_name, cells_name, -1, index,
					   out_args);
	अगर (ret)
		जाओ मुक्त;

	/* Get the #<list>-cells property */
	cur = out_args->np;
	ret = of_property_पढ़ो_u32(cur, cells_name, &list_size);
	अगर (ret < 0)
		जाओ put;

	/* Precalculate the match array - this simplअगरies match loop */
	क्रम (i = 0; i < list_size; i++)
		initial_match_array[i] = cpu_to_be32(out_args->args[i]);

	ret = -EINVAL;
	जबतक (cur) अणु
		/* Get the <list>-map property */
		map = of_get_property(cur, map_name, &map_len);
		अगर (!map) अणु
			ret = 0;
			जाओ मुक्त;
		पूर्ण
		map_len /= माप(u32);

		/* Get the <list>-map-mask property (optional) */
		mask = of_get_property(cur, mask_name, शून्य);
		अगर (!mask)
			mask = dummy_mask;
		/* Iterate through <list>-map property */
		match = 0;
		जबतक (map_len > (list_size + 1) && !match) अणु
			/* Compare specअगरiers */
			match = 1;
			क्रम (i = 0; i < list_size; i++, map_len--)
				match &= !((match_array[i] ^ *map++) & mask[i]);

			of_node_put(new);
			new = of_find_node_by_phandle(be32_to_cpup(map));
			map++;
			map_len--;

			/* Check अगर not found */
			अगर (!new)
				जाओ put;

			अगर (!of_device_is_available(new))
				match = 0;

			ret = of_property_पढ़ो_u32(new, cells_name, &new_size);
			अगर (ret)
				जाओ put;

			/* Check क्रम malक्रमmed properties */
			अगर (WARN_ON(new_size > MAX_PHANDLE_ARGS))
				जाओ put;
			अगर (map_len < new_size)
				जाओ put;

			/* Move क्रमward by new node's #<list>-cells amount */
			map += new_size;
			map_len -= new_size;
		पूर्ण
		अगर (!match)
			जाओ put;

		/* Get the <list>-map-pass-thru property (optional) */
		pass = of_get_property(cur, pass_name, शून्य);
		अगर (!pass)
			pass = dummy_pass;

		/*
		 * Successfully parsed a <list>-map translation; copy new
		 * specअगरier पूर्णांकo the out_args काष्ठाure, keeping the
		 * bits specअगरied in <list>-map-pass-thru.
		 */
		match_array = map - new_size;
		क्रम (i = 0; i < new_size; i++) अणु
			__be32 val = *(map - new_size + i);

			अगर (i < list_size) अणु
				val &= ~pass[i];
				val |= cpu_to_be32(out_args->args[i]) & pass[i];
			पूर्ण

			out_args->args[i] = be32_to_cpu(val);
		पूर्ण
		out_args->args_count = list_size = new_size;
		/* Iterate again with new provider */
		out_args->np = new;
		of_node_put(cur);
		cur = new;
	पूर्ण
put:
	of_node_put(cur);
	of_node_put(new);
मुक्त:
	kमुक्त(mask_name);
	kमुक्त(map_name);
	kमुक्त(cells_name);
	kमुक्त(pass_name);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(of_parse_phandle_with_args_map);

/**
 * of_parse_phandle_with_fixed_args() - Find a node poपूर्णांकed by phandle in a list
 * @np:		poपूर्णांकer to a device tree node containing a list
 * @list_name:	property name that contains a list
 * @cell_count: number of argument cells following the phandle
 * @index:	index of a phandle to parse out
 * @out_args:	optional poपूर्णांकer to output arguments काष्ठाure (will be filled)
 *
 * This function is useful to parse lists of phandles and their arguments.
 * Returns 0 on success and fills out_args, on error वापसs appropriate
 * त्रुटि_सं value.
 *
 * Caller is responsible to call of_node_put() on the वापसed out_args->np
 * poपूर्णांकer.
 *
 * Example::
 *
 *  phandle1: node1 अणु
 *  पूर्ण;
 *
 *  phandle2: node2 अणु
 *  पूर्ण;
 *
 *  node3 अणु
 *  	list = <&phandle1 0 2 &phandle2 2 3>;
 *  पूर्ण;
 *
 * To get a device_node of the ``node2`` node you may call this:
 * of_parse_phandle_with_fixed_args(node3, "list", 2, 1, &args);
 */
पूर्णांक of_parse_phandle_with_fixed_args(स्थिर काष्ठा device_node *np,
				स्थिर अक्षर *list_name, पूर्णांक cell_count,
				पूर्णांक index, काष्ठा of_phandle_args *out_args)
अणु
	अगर (index < 0)
		वापस -EINVAL;
	वापस __of_parse_phandle_with_args(np, list_name, शून्य, cell_count,
					   index, out_args);
पूर्ण
EXPORT_SYMBOL(of_parse_phandle_with_fixed_args);

/**
 * of_count_phandle_with_args() - Find the number of phandles references in a property
 * @np:		poपूर्णांकer to a device tree node containing a list
 * @list_name:	property name that contains a list
 * @cells_name:	property name that specअगरies phandles' arguments count
 *
 * Return: The number of phandle + argument tuples within a property. It
 * is a typical pattern to encode a list of phandle and variable
 * arguments पूर्णांकo a single property. The number of arguments is encoded
 * by a property in the phandle-target node. For example, a gpios
 * property would contain a list of GPIO specअगरies consisting of a
 * phandle and 1 or more arguments. The number of arguments are
 * determined by the #gpio-cells property in the node poपूर्णांकed to by the
 * phandle.
 */
पूर्णांक of_count_phandle_with_args(स्थिर काष्ठा device_node *np, स्थिर अक्षर *list_name,
				स्थिर अक्षर *cells_name)
अणु
	काष्ठा of_phandle_iterator it;
	पूर्णांक rc, cur_index = 0;

	/*
	 * If cells_name is शून्य we assume a cell count of 0. This makes
	 * counting the phandles trivial as each 32bit word in the list is a
	 * phandle and no arguments are to consider. So we करोn't iterate through
	 * the list but just use the length to determine the phandle count.
	 */
	अगर (!cells_name) अणु
		स्थिर __be32 *list;
		पूर्णांक size;

		list = of_get_property(np, list_name, &size);
		अगर (!list)
			वापस -ENOENT;

		वापस size / माप(*list);
	पूर्ण

	rc = of_phandle_iterator_init(&it, np, list_name, cells_name, -1);
	अगर (rc)
		वापस rc;

	जबतक ((rc = of_phandle_iterator_next(&it)) == 0)
		cur_index += 1;

	अगर (rc != -ENOENT)
		वापस rc;

	वापस cur_index;
पूर्ण
EXPORT_SYMBOL(of_count_phandle_with_args);

/**
 * __of_add_property - Add a property to a node without lock operations
 * @np:		Caller's Device Node
 * @prop:	Property to add
 */
पूर्णांक __of_add_property(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	काष्ठा property **next;

	prop->next = शून्य;
	next = &np->properties;
	जबतक (*next) अणु
		अगर (म_भेद(prop->name, (*next)->name) == 0)
			/* duplicate ! करोn't insert it */
			वापस -EEXIST;

		next = &(*next)->next;
	पूर्ण
	*next = prop;

	वापस 0;
पूर्ण

/**
 * of_add_property - Add a property to a node
 * @np:		Caller's Device Node
 * @prop:	Property to add
 */
पूर्णांक of_add_property(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	mutex_lock(&of_mutex);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	rc = __of_add_property(np, prop);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	अगर (!rc)
		__of_add_property_sysfs(np, prop);

	mutex_unlock(&of_mutex);

	अगर (!rc)
		of_property_notअगरy(OF_RECONFIG_ADD_PROPERTY, np, prop, शून्य);

	वापस rc;
पूर्ण

पूर्णांक __of_हटाओ_property(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	काष्ठा property **next;

	क्रम (next = &np->properties; *next; next = &(*next)->next) अणु
		अगर (*next == prop)
			अवरोध;
	पूर्ण
	अगर (*next == शून्य)
		वापस -ENODEV;

	/* found the node */
	*next = prop->next;
	prop->next = np->deadprops;
	np->deadprops = prop;

	वापस 0;
पूर्ण

/**
 * of_हटाओ_property - Remove a property from a node.
 * @np:		Caller's Device Node
 * @prop:	Property to हटाओ
 *
 * Note that we करोn't actually हटाओ it, since we have given out
 * who-knows-how-many poपूर्णांकers to the data using get-property.
 * Instead we just move the property to the "dead properties"
 * list, so it won't be found any more.
 */
पूर्णांक of_हटाओ_property(काष्ठा device_node *np, काष्ठा property *prop)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (!prop)
		वापस -ENODEV;

	mutex_lock(&of_mutex);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	rc = __of_हटाओ_property(np, prop);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	अगर (!rc)
		__of_हटाओ_property_sysfs(np, prop);

	mutex_unlock(&of_mutex);

	अगर (!rc)
		of_property_notअगरy(OF_RECONFIG_REMOVE_PROPERTY, np, prop, शून्य);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(of_हटाओ_property);

पूर्णांक __of_update_property(काष्ठा device_node *np, काष्ठा property *newprop,
		काष्ठा property **oldpropp)
अणु
	काष्ठा property **next, *oldprop;

	क्रम (next = &np->properties; *next; next = &(*next)->next) अणु
		अगर (of_prop_cmp((*next)->name, newprop->name) == 0)
			अवरोध;
	पूर्ण
	*oldpropp = oldprop = *next;

	अगर (oldprop) अणु
		/* replace the node */
		newprop->next = oldprop->next;
		*next = newprop;
		oldprop->next = np->deadprops;
		np->deadprops = oldprop;
	पूर्ण अन्यथा अणु
		/* new node */
		newprop->next = शून्य;
		*next = newprop;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * of_update_property - Update a property in a node, अगर the property करोes
 * not exist, add it.
 *
 * Note that we करोn't actually हटाओ it, since we have given out
 * who-knows-how-many poपूर्णांकers to the data using get-property.
 * Instead we just move the property to the "dead properties" list,
 * and add the new property to the property list
 */
पूर्णांक of_update_property(काष्ठा device_node *np, काष्ठा property *newprop)
अणु
	काष्ठा property *oldprop;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (!newprop->name)
		वापस -EINVAL;

	mutex_lock(&of_mutex);

	raw_spin_lock_irqsave(&devtree_lock, flags);
	rc = __of_update_property(np, newprop, &oldprop);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);

	अगर (!rc)
		__of_update_property_sysfs(np, newprop, oldprop);

	mutex_unlock(&of_mutex);

	अगर (!rc)
		of_property_notअगरy(OF_RECONFIG_UPDATE_PROPERTY, np, newprop, oldprop);

	वापस rc;
पूर्ण

अटल व्योम of_alias_add(काष्ठा alias_prop *ap, काष्ठा device_node *np,
			 पूर्णांक id, स्थिर अक्षर *stem, पूर्णांक stem_len)
अणु
	ap->np = np;
	ap->id = id;
	म_नकलन(ap->stem, stem, stem_len);
	ap->stem[stem_len] = 0;
	list_add_tail(&ap->link, &aliases_lookup);
	pr_debug("adding DT alias:%s: stem=%s id=%i node=%pOF\n",
		 ap->alias, ap->stem, ap->id, np);
पूर्ण

/**
 * of_alias_scan - Scan all properties of the 'aliases' node
 * @dt_alloc:	An allocator that provides a भव address to memory
 *		क्रम storing the resulting tree
 *
 * The function scans all the properties of the 'aliases' node and populates
 * the global lookup table with the properties.  It वापसs the
 * number of alias properties found, or an error code in हाल of failure.
 */
व्योम of_alias_scan(व्योम * (*dt_alloc)(u64 size, u64 align))
अणु
	काष्ठा property *pp;

	of_aliases = of_find_node_by_path("/aliases");
	of_chosen = of_find_node_by_path("/chosen");
	अगर (of_chosen == शून्य)
		of_chosen = of_find_node_by_path("/chosen@0");

	अगर (of_chosen) अणु
		/* linux,मानक_निकास-path and /aliases/मानक_निकास are क्रम legacy compatibility */
		स्थिर अक्षर *name = शून्य;

		अगर (of_property_पढ़ो_string(of_chosen, "stdout-path", &name))
			of_property_पढ़ो_string(of_chosen, "linux,stdout-path",
						&name);
		अगर (IS_ENABLED(CONFIG_PPC) && !name)
			of_property_पढ़ो_string(of_aliases, "stdout", &name);
		अगर (name)
			of_मानक_निकास = of_find_node_opts_by_path(name, &of_मानक_निकास_options);
	पूर्ण

	अगर (!of_aliases)
		वापस;

	क्रम_each_property_of_node(of_aliases, pp) अणु
		स्थिर अक्षर *start = pp->name;
		स्थिर अक्षर *end = start + म_माप(start);
		काष्ठा device_node *np;
		काष्ठा alias_prop *ap;
		पूर्णांक id, len;

		/* Skip those we करो not want to proceed */
		अगर (!म_भेद(pp->name, "name") ||
		    !म_भेद(pp->name, "phandle") ||
		    !म_भेद(pp->name, "linux,phandle"))
			जारी;

		np = of_find_node_by_path(pp->value);
		अगर (!np)
			जारी;

		/* walk the alias backwards to extract the id and work out
		 * the 'stem' string */
		जबतक (है_अंक(*(end-1)) && end > start)
			end--;
		len = end - start;

		अगर (kstrtoपूर्णांक(end, 10, &id) < 0)
			जारी;

		/* Allocate an alias_prop with enough space क्रम the stem */
		ap = dt_alloc(माप(*ap) + len + 1, __alignof__(*ap));
		अगर (!ap)
			जारी;
		स_रखो(ap, 0, माप(*ap) + len + 1);
		ap->alias = start;
		of_alias_add(ap, np, id, start, len);
	पूर्ण
पूर्ण

/**
 * of_alias_get_id - Get alias id क्रम the given device_node
 * @np:		Poपूर्णांकer to the given device_node
 * @stem:	Alias stem of the given device_node
 *
 * The function travels the lookup table to get the alias id क्रम the given
 * device_node and alias stem.
 *
 * Return: The alias id अगर found.
 */
पूर्णांक of_alias_get_id(काष्ठा device_node *np, स्थिर अक्षर *stem)
अणु
	काष्ठा alias_prop *app;
	पूर्णांक id = -ENODEV;

	mutex_lock(&of_mutex);
	list_क्रम_each_entry(app, &aliases_lookup, link) अणु
		अगर (म_भेद(app->stem, stem) != 0)
			जारी;

		अगर (np == app->np) अणु
			id = app->id;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&of_mutex);

	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(of_alias_get_id);

/**
 * of_alias_get_alias_list - Get alias list क्रम the given device driver
 * @matches:	Array of OF device match काष्ठाures to search in
 * @stem:	Alias stem of the given device_node
 * @biपंचांगap:	Biपंचांगap field poपूर्णांकer
 * @nbits:	Maximum number of alias IDs which can be recorded in biपंचांगap
 *
 * The function travels the lookup table to record alias ids क्रम the given
 * device match काष्ठाures and alias stem.
 *
 * Return:	0 or -ENOSYS when !CONFIG_OF or
 *		-EOVERFLOW अगर alias ID is greater then allocated nbits
 */
पूर्णांक of_alias_get_alias_list(स्थिर काष्ठा of_device_id *matches,
			     स्थिर अक्षर *stem, अचिन्हित दीर्घ *biपंचांगap,
			     अचिन्हित पूर्णांक nbits)
अणु
	काष्ठा alias_prop *app;
	पूर्णांक ret = 0;

	/* Zero biपंचांगap field to make sure that all the समय it is clean */
	biपंचांगap_zero(biपंचांगap, nbits);

	mutex_lock(&of_mutex);
	pr_debug("%s: Looking for stem: %s\n", __func__, stem);
	list_क्रम_each_entry(app, &aliases_lookup, link) अणु
		pr_debug("%s: stem: %s, id: %d\n",
			 __func__, app->stem, app->id);

		अगर (म_भेद(app->stem, stem) != 0) अणु
			pr_debug("%s: stem comparison didn't pass %s\n",
				 __func__, app->stem);
			जारी;
		पूर्ण

		अगर (of_match_node(matches, app->np)) अणु
			pr_debug("%s: Allocated ID %d\n", __func__, app->id);

			अगर (app->id >= nbits) अणु
				pr_warn("%s: ID %d >= than bitmap field %d\n",
					__func__, app->id, nbits);
				ret = -EOVERFLOW;
			पूर्ण अन्यथा अणु
				set_bit(app->id, biपंचांगap);
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&of_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_alias_get_alias_list);

/**
 * of_alias_get_highest_id - Get highest alias id क्रम the given stem
 * @stem:	Alias stem to be examined
 *
 * The function travels the lookup table to get the highest alias id क्रम the
 * given alias stem.  It वापसs the alias id अगर found.
 */
पूर्णांक of_alias_get_highest_id(स्थिर अक्षर *stem)
अणु
	काष्ठा alias_prop *app;
	पूर्णांक id = -ENODEV;

	mutex_lock(&of_mutex);
	list_क्रम_each_entry(app, &aliases_lookup, link) अणु
		अगर (म_भेद(app->stem, stem) != 0)
			जारी;

		अगर (app->id > id)
			id = app->id;
	पूर्ण
	mutex_unlock(&of_mutex);

	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(of_alias_get_highest_id);

/**
 * of_console_check() - Test and setup console क्रम DT setup
 * @dn: Poपूर्णांकer to device node
 * @name: Name to use क्रम preferred console without index. ex. "ttyS"
 * @index: Index to use क्रम preferred console.
 *
 * Check अगर the given device node matches the मानक_निकास-path property in the
 * /chosen node. If it करोes then रेजिस्टर it as the preferred console.
 *
 * Return: TRUE अगर console successfully setup. Otherwise वापस FALSE.
 */
bool of_console_check(काष्ठा device_node *dn, अक्षर *name, पूर्णांक index)
अणु
	अगर (!dn || dn != of_मानक_निकास || console_set_on_cmdline)
		वापस false;

	/*
	 * XXX: cast `options' to अक्षर poपूर्णांकer to suppress complication
	 * warnings: prपूर्णांकk, UART and console drivers expect अक्षर poपूर्णांकer.
	 */
	वापस !add_preferred_console(name, index, (अक्षर *)of_मानक_निकास_options);
पूर्ण
EXPORT_SYMBOL_GPL(of_console_check);

/**
 * of_find_next_cache_node - Find a node's subsidiary cache
 * @np:	node of type "cpu" or "cache"
 *
 * Return: A node poपूर्णांकer with refcount incremented, use
 * of_node_put() on it when करोne.  Caller should hold a reference
 * to np.
 */
काष्ठा device_node *of_find_next_cache_node(स्थिर काष्ठा device_node *np)
अणु
	काष्ठा device_node *child, *cache_node;

	cache_node = of_parse_phandle(np, "l2-cache", 0);
	अगर (!cache_node)
		cache_node = of_parse_phandle(np, "next-level-cache", 0);

	अगर (cache_node)
		वापस cache_node;

	/* OF on pmac has nodes instead of properties named "l2-cache"
	 * beneath CPU nodes.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_PMAC) && of_node_is_type(np, "cpu"))
		क्रम_each_child_of_node(np, child)
			अगर (of_node_is_type(child, "cache"))
				वापस child;

	वापस शून्य;
पूर्ण

/**
 * of_find_last_cache_level - Find the level at which the last cache is
 * 		present क्रम the given logical cpu
 *
 * @cpu: cpu number(logical index) क्रम which the last cache level is needed
 *
 * Return: The the level at which the last cache is present. It is exactly
 * same as  the total number of cache levels क्रम the given logical cpu.
 */
पूर्णांक of_find_last_cache_level(अचिन्हित पूर्णांक cpu)
अणु
	u32 cache_level = 0;
	काष्ठा device_node *prev = शून्य, *np = of_cpu_device_node_get(cpu);

	जबतक (np) अणु
		prev = np;
		of_node_put(np);
		np = of_find_next_cache_node(np);
	पूर्ण

	of_property_पढ़ो_u32(prev, "cache-level", &cache_level);

	वापस cache_level;
पूर्ण

/**
 * of_map_id - Translate an ID through a करोwnstream mapping.
 * @np: root complex device node.
 * @id: device ID to map.
 * @map_name: property name of the map to use.
 * @map_mask_name: optional property name of the mask to use.
 * @target: optional poपूर्णांकer to a target device node.
 * @id_out: optional poपूर्णांकer to receive the translated ID.
 *
 * Given a device ID, look up the appropriate implementation-defined
 * platक्रमm ID and/or the target device which receives transactions on that
 * ID, as per the "iommu-map" and "msi-map" bindings. Either of @target or
 * @id_out may be शून्य अगर only the other is required. If @target poपूर्णांकs to
 * a non-शून्य device node poपूर्णांकer, only entries targeting that node will be
 * matched; अगर it poपूर्णांकs to a शून्य value, it will receive the device node of
 * the first matching target phandle, with a reference held.
 *
 * Return: 0 on success or a standard error code on failure.
 */
पूर्णांक of_map_id(काष्ठा device_node *np, u32 id,
	       स्थिर अक्षर *map_name, स्थिर अक्षर *map_mask_name,
	       काष्ठा device_node **target, u32 *id_out)
अणु
	u32 map_mask, masked_id;
	पूर्णांक map_len;
	स्थिर __be32 *map = शून्य;

	अगर (!np || !map_name || (!target && !id_out))
		वापस -EINVAL;

	map = of_get_property(np, map_name, &map_len);
	अगर (!map) अणु
		अगर (target)
			वापस -ENODEV;
		/* Otherwise, no map implies no translation */
		*id_out = id;
		वापस 0;
	पूर्ण

	अगर (!map_len || map_len % (4 * माप(*map))) अणु
		pr_err("%pOF: Error: Bad %s length: %d\n", np,
			map_name, map_len);
		वापस -EINVAL;
	पूर्ण

	/* The शेष is to select all bits. */
	map_mask = 0xffffffff;

	/*
	 * Can be overridden by "{iommu,msi}-map-mask" property.
	 * If of_property_पढ़ो_u32() fails, the शेष is used.
	 */
	अगर (map_mask_name)
		of_property_पढ़ो_u32(np, map_mask_name, &map_mask);

	masked_id = map_mask & id;
	क्रम ( ; map_len > 0; map_len -= 4 * माप(*map), map += 4) अणु
		काष्ठा device_node *phandle_node;
		u32 id_base = be32_to_cpup(map + 0);
		u32 phandle = be32_to_cpup(map + 1);
		u32 out_base = be32_to_cpup(map + 2);
		u32 id_len = be32_to_cpup(map + 3);

		अगर (id_base & ~map_mask) अणु
			pr_err("%pOF: Invalid %s translation - %s-mask (0x%x) ignores id-base (0x%x)\n",
				np, map_name, map_name,
				map_mask, id_base);
			वापस -EFAULT;
		पूर्ण

		अगर (masked_id < id_base || masked_id >= id_base + id_len)
			जारी;

		phandle_node = of_find_node_by_phandle(phandle);
		अगर (!phandle_node)
			वापस -ENODEV;

		अगर (target) अणु
			अगर (*target)
				of_node_put(phandle_node);
			अन्यथा
				*target = phandle_node;

			अगर (*target != phandle_node)
				जारी;
		पूर्ण

		अगर (id_out)
			*id_out = masked_id - id_base + out_base;

		pr_debug("%pOF: %s, using mask %08x, id-base: %08x, out-base: %08x, length: %08x, id: %08x -> %08x\n",
			np, map_name, map_mask, id_base, out_base,
			id_len, id, masked_id - id_base + out_base);
		वापस 0;
	पूर्ण

	pr_info("%pOF: no %s translation for id 0x%x on %pOF\n", np, map_name,
		id, target && *target ? *target : शून्य);

	/* Bypasses translation */
	अगर (id_out)
		*id_out = id;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(of_map_id);
