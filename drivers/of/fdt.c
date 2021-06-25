<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Functions क्रम working with the Flattened Device Tree data क्रमmat
 *
 * Copyright 2009 Benjamin Herrenschmidt, IBM Corp
 * benh@kernel.crashing.org
 */

#घोषणा pr_fmt(fmt)	"OF: fdt: " fmt

#समावेश <linux/crc32.h>
#समावेश <linux/kernel.h>
#समावेश <linux/initrd.h>
#समावेश <linux/memblock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/sizes.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/libfdt.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/अक्रमom.h>

#समावेश <यंत्र/setup.h>  /* क्रम COMMAND_LINE_SIZE */
#समावेश <यंत्र/page.h>

#समावेश "of_private.h"

/*
 * of_fdt_limit_memory - limit the number of regions in the /memory node
 * @limit: maximum entries
 *
 * Adjust the flattened device tree to have at most 'limit' number of
 * memory entries in the /memory node. This function may be called
 * any समय after initial_boot_param is set.
 */
व्योम __init of_fdt_limit_memory(पूर्णांक limit)
अणु
	पूर्णांक memory;
	पूर्णांक len;
	स्थिर व्योम *val;
	पूर्णांक nr_address_cells = OF_ROOT_NODE_ADDR_CELLS_DEFAULT;
	पूर्णांक nr_size_cells = OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
	स्थिर __be32 *addr_prop;
	स्थिर __be32 *size_prop;
	पूर्णांक root_offset;
	पूर्णांक cell_size;

	root_offset = fdt_path_offset(initial_boot_params, "/");
	अगर (root_offset < 0)
		वापस;

	addr_prop = fdt_getprop(initial_boot_params, root_offset,
				"#address-cells", शून्य);
	अगर (addr_prop)
		nr_address_cells = fdt32_to_cpu(*addr_prop);

	size_prop = fdt_getprop(initial_boot_params, root_offset,
				"#size-cells", शून्य);
	अगर (size_prop)
		nr_size_cells = fdt32_to_cpu(*size_prop);

	cell_size = माप(uपूर्णांक32_t)*(nr_address_cells + nr_size_cells);

	memory = fdt_path_offset(initial_boot_params, "/memory");
	अगर (memory > 0) अणु
		val = fdt_getprop(initial_boot_params, memory, "reg", &len);
		अगर (len > limit*cell_size) अणु
			len = limit*cell_size;
			pr_debug("Limiting number of entries to %d\n", limit);
			fdt_setprop(initial_boot_params, memory, "reg", val,
					len);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool of_fdt_device_is_available(स्थिर व्योम *blob, अचिन्हित दीर्घ node)
अणु
	स्थिर अक्षर *status = fdt_getprop(blob, node, "status", शून्य);

	अगर (!status)
		वापस true;

	अगर (!म_भेद(status, "ok") || !म_भेद(status, "okay"))
		वापस true;

	वापस false;
पूर्ण

अटल व्योम *unflatten_dt_alloc(व्योम **mem, अचिन्हित दीर्घ size,
				       अचिन्हित दीर्घ align)
अणु
	व्योम *res;

	*mem = PTR_ALIGN(*mem, align);
	res = *mem;
	*mem += size;

	वापस res;
पूर्ण

अटल व्योम populate_properties(स्थिर व्योम *blob,
				पूर्णांक offset,
				व्योम **mem,
				काष्ठा device_node *np,
				स्थिर अक्षर *nodename,
				bool dryrun)
अणु
	काष्ठा property *pp, **pprev = शून्य;
	पूर्णांक cur;
	bool has_name = false;

	pprev = &np->properties;
	क्रम (cur = fdt_first_property_offset(blob, offset);
	     cur >= 0;
	     cur = fdt_next_property_offset(blob, cur)) अणु
		स्थिर __be32 *val;
		स्थिर अक्षर *pname;
		u32 sz;

		val = fdt_getprop_by_offset(blob, cur, &pname, &sz);
		अगर (!val) अणु
			pr_warn("Cannot locate property at 0x%x\n", cur);
			जारी;
		पूर्ण

		अगर (!pname) अणु
			pr_warn("Cannot find property name at 0x%x\n", cur);
			जारी;
		पूर्ण

		अगर (!म_भेद(pname, "name"))
			has_name = true;

		pp = unflatten_dt_alloc(mem, माप(काष्ठा property),
					__alignof__(काष्ठा property));
		अगर (dryrun)
			जारी;

		/* We accept flattened tree phandles either in
		 * ePAPR-style "phandle" properties, or the
		 * legacy "linux,phandle" properties.  If both
		 * appear and have dअगरferent values, things
		 * will get weird. Don't करो that.
		 */
		अगर (!म_भेद(pname, "phandle") ||
		    !म_भेद(pname, "linux,phandle")) अणु
			अगर (!np->phandle)
				np->phandle = be32_to_cpup(val);
		पूर्ण

		/* And we process the "ibm,phandle" property
		 * used in pSeries dynamic device tree
		 * stuff
		 */
		अगर (!म_भेद(pname, "ibm,phandle"))
			np->phandle = be32_to_cpup(val);

		pp->name   = (अक्षर *)pname;
		pp->length = sz;
		pp->value  = (__be32 *)val;
		*pprev     = pp;
		pprev      = &pp->next;
	पूर्ण

	/* With version 0x10 we may not have the name property,
	 * recreate it here from the unit name अगर असलent
	 */
	अगर (!has_name) अणु
		स्थिर अक्षर *p = nodename, *ps = p, *pa = शून्य;
		पूर्णांक len;

		जबतक (*p) अणु
			अगर ((*p) == '@')
				pa = p;
			अन्यथा अगर ((*p) == '/')
				ps = p + 1;
			p++;
		पूर्ण

		अगर (pa < ps)
			pa = p;
		len = (pa - ps) + 1;
		pp = unflatten_dt_alloc(mem, माप(काष्ठा property) + len,
					__alignof__(काष्ठा property));
		अगर (!dryrun) अणु
			pp->name   = "name";
			pp->length = len;
			pp->value  = pp + 1;
			*pprev     = pp;
			pprev      = &pp->next;
			स_नकल(pp->value, ps, len - 1);
			((अक्षर *)pp->value)[len - 1] = 0;
			pr_debug("fixed up name for %s -> %s\n",
				 nodename, (अक्षर *)pp->value);
		पूर्ण
	पूर्ण

	अगर (!dryrun)
		*pprev = शून्य;
पूर्ण

अटल पूर्णांक populate_node(स्थिर व्योम *blob,
			  पूर्णांक offset,
			  व्योम **mem,
			  काष्ठा device_node *dad,
			  काष्ठा device_node **pnp,
			  bool dryrun)
अणु
	काष्ठा device_node *np;
	स्थिर अक्षर *pathp;
	पूर्णांक len;

	pathp = fdt_get_name(blob, offset, &len);
	अगर (!pathp) अणु
		*pnp = शून्य;
		वापस len;
	पूर्ण

	len++;

	np = unflatten_dt_alloc(mem, माप(काष्ठा device_node) + len,
				__alignof__(काष्ठा device_node));
	अगर (!dryrun) अणु
		अक्षर *fn;
		of_node_init(np);
		np->full_name = fn = ((अक्षर *)np) + माप(*np);

		स_नकल(fn, pathp, len);

		अगर (dad != शून्य) अणु
			np->parent = dad;
			np->sibling = dad->child;
			dad->child = np;
		पूर्ण
	पूर्ण

	populate_properties(blob, offset, mem, np, pathp, dryrun);
	अगर (!dryrun) अणु
		np->name = of_get_property(np, "name", शून्य);
		अगर (!np->name)
			np->name = "<NULL>";
	पूर्ण

	*pnp = np;
	वापस true;
पूर्ण

अटल व्योम reverse_nodes(काष्ठा device_node *parent)
अणु
	काष्ठा device_node *child, *next;

	/* In-depth first */
	child = parent->child;
	जबतक (child) अणु
		reverse_nodes(child);

		child = child->sibling;
	पूर्ण

	/* Reverse the nodes in the child list */
	child = parent->child;
	parent->child = शून्य;
	जबतक (child) अणु
		next = child->sibling;

		child->sibling = parent->child;
		parent->child = child;
		child = next;
	पूर्ण
पूर्ण

/**
 * unflatten_dt_nodes - Alloc and populate a device_node from the flat tree
 * @blob: The parent device tree blob
 * @mem: Memory chunk to use क्रम allocating device nodes and properties
 * @dad: Parent काष्ठा device_node
 * @nodepp: The device_node tree created by the call
 *
 * Return: The size of unflattened device tree or error code
 */
अटल पूर्णांक unflatten_dt_nodes(स्थिर व्योम *blob,
			      व्योम *mem,
			      काष्ठा device_node *dad,
			      काष्ठा device_node **nodepp)
अणु
	काष्ठा device_node *root;
	पूर्णांक offset = 0, depth = 0, initial_depth = 0;
#घोषणा FDT_MAX_DEPTH	64
	काष्ठा device_node *nps[FDT_MAX_DEPTH];
	व्योम *base = mem;
	bool dryrun = !base;
	पूर्णांक ret;

	अगर (nodepp)
		*nodepp = शून्य;

	/*
	 * We're unflattening device sub-tree अगर @dad is valid. There are
	 * possibly multiple nodes in the first level of depth. We need
	 * set @depth to 1 to make fdt_next_node() happy as it bails
	 * immediately when negative @depth is found. Otherwise, the device
	 * nodes except the first one won't be unflattened successfully.
	 */
	अगर (dad)
		depth = initial_depth = 1;

	root = dad;
	nps[depth] = dad;

	क्रम (offset = 0;
	     offset >= 0 && depth >= initial_depth;
	     offset = fdt_next_node(blob, offset, &depth)) अणु
		अगर (WARN_ON_ONCE(depth >= FDT_MAX_DEPTH))
			जारी;

		अगर (!IS_ENABLED(CONFIG_OF_KOBJ) &&
		    !of_fdt_device_is_available(blob, offset))
			जारी;

		ret = populate_node(blob, offset, &mem, nps[depth],
				   &nps[depth+1], dryrun);
		अगर (ret < 0)
			वापस ret;

		अगर (!dryrun && nodepp && !*nodepp)
			*nodepp = nps[depth+1];
		अगर (!dryrun && !root)
			root = nps[depth+1];
	पूर्ण

	अगर (offset < 0 && offset != -FDT_ERR_NOTFOUND) अणु
		pr_err("Error %d processing FDT\n", offset);
		वापस -EINVAL;
	पूर्ण

	/*
	 * Reverse the child list. Some drivers assumes node order matches .dts
	 * node order
	 */
	अगर (!dryrun)
		reverse_nodes(root);

	वापस mem - base;
पूर्ण

/**
 * __unflatten_device_tree - create tree of device_nodes from flat blob
 * @blob: The blob to expand
 * @dad: Parent device node
 * @mynodes: The device_node tree created by the call
 * @dt_alloc: An allocator that provides a भव address to memory
 * क्रम the resulting tree
 * @detached: अगर true set OF_DETACHED on @mynodes
 *
 * unflattens a device-tree, creating the tree of काष्ठा device_node. It also
 * fills the "name" and "type" poपूर्णांकers of the nodes so the normal device-tree
 * walking functions can be used.
 *
 * Return: शून्य on failure or the memory chunk containing the unflattened
 * device tree on success.
 */
व्योम *__unflatten_device_tree(स्थिर व्योम *blob,
			      काष्ठा device_node *dad,
			      काष्ठा device_node **mynodes,
			      व्योम *(*dt_alloc)(u64 size, u64 align),
			      bool detached)
अणु
	पूर्णांक size;
	व्योम *mem;
	पूर्णांक ret;

	अगर (mynodes)
		*mynodes = शून्य;

	pr_debug(" -> unflatten_device_tree()\n");

	अगर (!blob) अणु
		pr_debug("No device tree pointer\n");
		वापस शून्य;
	पूर्ण

	pr_debug("Unflattening device tree:\n");
	pr_debug("magic: %08x\n", fdt_magic(blob));
	pr_debug("size: %08x\n", fdt_totalsize(blob));
	pr_debug("version: %08x\n", fdt_version(blob));

	अगर (fdt_check_header(blob)) अणु
		pr_err("Invalid device tree blob header\n");
		वापस शून्य;
	पूर्ण

	/* First pass, scan क्रम size */
	size = unflatten_dt_nodes(blob, शून्य, dad, शून्य);
	अगर (size <= 0)
		वापस शून्य;

	size = ALIGN(size, 4);
	pr_debug("  size is %d, allocating...\n", size);

	/* Allocate memory क्रम the expanded device tree */
	mem = dt_alloc(size + 4, __alignof__(काष्ठा device_node));
	अगर (!mem)
		वापस शून्य;

	स_रखो(mem, 0, size);

	*(__be32 *)(mem + size) = cpu_to_be32(0xdeadbeef);

	pr_debug("  unflattening %p...\n", mem);

	/* Second pass, करो actual unflattening */
	ret = unflatten_dt_nodes(blob, mem, dad, mynodes);

	अगर (be32_to_cpup(mem + size) != 0xdeadbeef)
		pr_warn("End of tree marker overwritten: %08x\n",
			be32_to_cpup(mem + size));

	अगर (ret <= 0)
		वापस शून्य;

	अगर (detached && mynodes && *mynodes) अणु
		of_node_set_flag(*mynodes, OF_DETACHED);
		pr_debug("unflattened tree is detached\n");
	पूर्ण

	pr_debug(" <- unflatten_device_tree()\n");
	वापस mem;
पूर्ण

अटल व्योम *kernel_tree_alloc(u64 size, u64 align)
अणु
	वापस kzalloc(size, GFP_KERNEL);
पूर्ण

अटल DEFINE_MUTEX(of_fdt_unflatten_mutex);

/**
 * of_fdt_unflatten_tree - create tree of device_nodes from flat blob
 * @blob: Flat device tree blob
 * @dad: Parent device node
 * @mynodes: The device tree created by the call
 *
 * unflattens the device-tree passed by the firmware, creating the
 * tree of काष्ठा device_node. It also fills the "name" and "type"
 * poपूर्णांकers of the nodes so the normal device-tree walking functions
 * can be used.
 *
 * Return: शून्य on failure or the memory chunk containing the unflattened
 * device tree on success.
 */
व्योम *of_fdt_unflatten_tree(स्थिर अचिन्हित दीर्घ *blob,
			    काष्ठा device_node *dad,
			    काष्ठा device_node **mynodes)
अणु
	व्योम *mem;

	mutex_lock(&of_fdt_unflatten_mutex);
	mem = __unflatten_device_tree(blob, dad, mynodes, &kernel_tree_alloc,
				      true);
	mutex_unlock(&of_fdt_unflatten_mutex);

	वापस mem;
पूर्ण
EXPORT_SYMBOL_GPL(of_fdt_unflatten_tree);

/* Everything below here references initial_boot_params directly. */
पूर्णांक __initdata dt_root_addr_cells;
पूर्णांक __initdata dt_root_size_cells;

व्योम *initial_boot_params __ro_after_init;

#अगर_घोषित CONFIG_OF_EARLY_FLATTREE

अटल u32 of_fdt_crc32;

/*
 * __reserved_mem_reserve_reg() - reserve all memory described in 'reg' property
 */
अटल पूर्णांक __init __reserved_mem_reserve_reg(अचिन्हित दीर्घ node,
					     स्थिर अक्षर *uname)
अणु
	पूर्णांक t_len = (dt_root_addr_cells + dt_root_size_cells) * माप(__be32);
	phys_addr_t base, size;
	पूर्णांक len;
	स्थिर __be32 *prop;
	पूर्णांक first = 1;
	bool nomap;

	prop = of_get_flat_dt_prop(node, "reg", &len);
	अगर (!prop)
		वापस -ENOENT;

	अगर (len && len % t_len != 0) अणु
		pr_err("Reserved memory: invalid reg property in '%s', skipping node.\n",
		       uname);
		वापस -EINVAL;
	पूर्ण

	nomap = of_get_flat_dt_prop(node, "no-map", शून्य) != शून्य;

	जबतक (len >= t_len) अणु
		base = dt_mem_next_cell(dt_root_addr_cells, &prop);
		size = dt_mem_next_cell(dt_root_size_cells, &prop);

		अगर (size &&
		    early_init_dt_reserve_memory_arch(base, size, nomap) == 0)
			pr_debug("Reserved memory: reserved region for node '%s': base %pa, size %ld MiB\n",
				uname, &base, (अचिन्हित दीर्घ)size / SZ_1M);
		अन्यथा
			pr_info("Reserved memory: failed to reserve memory for node '%s': base %pa, size %ld MiB\n",
				uname, &base, (अचिन्हित दीर्घ)size / SZ_1M);

		len -= t_len;
		अगर (first) अणु
			fdt_reserved_mem_save_node(node, uname, base, size);
			first = 0;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * __reserved_mem_check_root() - check अगर #size-cells, #address-cells provided
 * in /reserved-memory matches the values supported by the current implementation,
 * also check अगर ranges property has been provided
 */
अटल पूर्णांक __init __reserved_mem_check_root(अचिन्हित दीर्घ node)
अणु
	स्थिर __be32 *prop;

	prop = of_get_flat_dt_prop(node, "#size-cells", शून्य);
	अगर (!prop || be32_to_cpup(prop) != dt_root_size_cells)
		वापस -EINVAL;

	prop = of_get_flat_dt_prop(node, "#address-cells", शून्य);
	अगर (!prop || be32_to_cpup(prop) != dt_root_addr_cells)
		वापस -EINVAL;

	prop = of_get_flat_dt_prop(node, "ranges", शून्य);
	अगर (!prop)
		वापस -EINVAL;
	वापस 0;
पूर्ण

/*
 * __fdt_scan_reserved_mem() - scan a single FDT node क्रम reserved memory
 */
अटल पूर्णांक __init __fdt_scan_reserved_mem(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
					  पूर्णांक depth, व्योम *data)
अणु
	अटल पूर्णांक found;
	पूर्णांक err;

	अगर (!found && depth == 1 && म_भेद(uname, "reserved-memory") == 0) अणु
		अगर (__reserved_mem_check_root(node) != 0) अणु
			pr_err("Reserved memory: unsupported node format, ignoring\n");
			/* अवरोध scan */
			वापस 1;
		पूर्ण
		found = 1;
		/* scan next node */
		वापस 0;
	पूर्ण अन्यथा अगर (!found) अणु
		/* scan next node */
		वापस 0;
	पूर्ण अन्यथा अगर (found && depth < 2) अणु
		/* scanning of /reserved-memory has been finished */
		वापस 1;
	पूर्ण

	अगर (!of_fdt_device_is_available(initial_boot_params, node))
		वापस 0;

	err = __reserved_mem_reserve_reg(node, uname);
	अगर (err == -ENOENT && of_get_flat_dt_prop(node, "size", शून्य))
		fdt_reserved_mem_save_node(node, uname, 0, 0);

	/* scan next node */
	वापस 0;
पूर्ण

/**
 * early_init_fdt_scan_reserved_mem() - create reserved memory regions
 *
 * This function grअसल memory from early allocator क्रम device exclusive use
 * defined in device tree काष्ठाures. It should be called by arch specअगरic code
 * once the early allocator (i.e. memblock) has been fully activated.
 */
व्योम __init early_init_fdt_scan_reserved_mem(व्योम)
अणु
	पूर्णांक n;
	u64 base, size;

	अगर (!initial_boot_params)
		वापस;

	/* Process header /memreserve/ fields */
	क्रम (n = 0; ; n++) अणु
		fdt_get_mem_rsv(initial_boot_params, n, &base, &size);
		अगर (!size)
			अवरोध;
		early_init_dt_reserve_memory_arch(base, size, false);
	पूर्ण

	of_scan_flat_dt(__fdt_scan_reserved_mem, शून्य);
	fdt_init_reserved_mem();
पूर्ण

/**
 * early_init_fdt_reserve_self() - reserve the memory used by the FDT blob
 */
व्योम __init early_init_fdt_reserve_self(व्योम)
अणु
	अगर (!initial_boot_params)
		वापस;

	/* Reserve the dtb region */
	early_init_dt_reserve_memory_arch(__pa(initial_boot_params),
					  fdt_totalsize(initial_boot_params),
					  false);
पूर्ण

/**
 * of_scan_flat_dt - scan flattened tree blob and call callback on each.
 * @it: callback function
 * @data: context data poपूर्णांकer
 *
 * This function is used to scan the flattened device-tree, it is
 * used to extract the memory inक्रमmation at boot beक्रमe we can
 * unflatten the tree
 */
पूर्णांक __init of_scan_flat_dt(पूर्णांक (*it)(अचिन्हित दीर्घ node,
				     स्थिर अक्षर *uname, पूर्णांक depth,
				     व्योम *data),
			   व्योम *data)
अणु
	स्थिर व्योम *blob = initial_boot_params;
	स्थिर अक्षर *pathp;
	पूर्णांक offset, rc = 0, depth = -1;

	अगर (!blob)
		वापस 0;

	क्रम (offset = fdt_next_node(blob, -1, &depth);
	     offset >= 0 && depth >= 0 && !rc;
	     offset = fdt_next_node(blob, offset, &depth)) अणु

		pathp = fdt_get_name(blob, offset, शून्य);
		rc = it(offset, pathp, depth, data);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * of_scan_flat_dt_subnodes - scan sub-nodes of a node call callback on each.
 * @parent: parent node
 * @it: callback function
 * @data: context data poपूर्णांकer
 *
 * This function is used to scan sub-nodes of a node.
 */
पूर्णांक __init of_scan_flat_dt_subnodes(अचिन्हित दीर्घ parent,
				    पूर्णांक (*it)(अचिन्हित दीर्घ node,
					      स्थिर अक्षर *uname,
					      व्योम *data),
				    व्योम *data)
अणु
	स्थिर व्योम *blob = initial_boot_params;
	पूर्णांक node;

	fdt_क्रम_each_subnode(node, blob, parent) अणु
		स्थिर अक्षर *pathp;
		पूर्णांक rc;

		pathp = fdt_get_name(blob, node, शून्य);
		rc = it(node, pathp, data);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * of_get_flat_dt_subnode_by_name - get the subnode by given name
 *
 * @node: the parent node
 * @uname: the name of subnode
 * @वापस offset of the subnode, or -FDT_ERR_NOTFOUND अगर there is none
 */

पूर्णांक __init of_get_flat_dt_subnode_by_name(अचिन्हित दीर्घ node, स्थिर अक्षर *uname)
अणु
	वापस fdt_subnode_offset(initial_boot_params, node, uname);
पूर्ण

/*
 * of_get_flat_dt_root - find the root node in the flat blob
 */
अचिन्हित दीर्घ __init of_get_flat_dt_root(व्योम)
अणु
	वापस 0;
पूर्ण

/*
 * of_get_flat_dt_prop - Given a node in the flat blob, वापस the property ptr
 *
 * This function can be used within scan_flattened_dt callback to get
 * access to properties
 */
स्थिर व्योम *__init of_get_flat_dt_prop(अचिन्हित दीर्घ node, स्थिर अक्षर *name,
				       पूर्णांक *size)
अणु
	वापस fdt_getprop(initial_boot_params, node, name, size);
पूर्ण

/**
 * of_fdt_is_compatible - Return true अगर given node from the given blob has
 * compat in its compatible list
 * @blob: A device tree blob
 * @node: node to test
 * @compat: compatible string to compare with compatible list.
 *
 * Return: a non-zero value on match with smaller values वापसed क्रम more
 * specअगरic compatible values.
 */
अटल पूर्णांक of_fdt_is_compatible(स्थिर व्योम *blob,
		      अचिन्हित दीर्घ node, स्थिर अक्षर *compat)
अणु
	स्थिर अक्षर *cp;
	पूर्णांक cplen;
	अचिन्हित दीर्घ l, score = 0;

	cp = fdt_getprop(blob, node, "compatible", &cplen);
	अगर (cp == शून्य)
		वापस 0;
	जबतक (cplen > 0) अणु
		score++;
		अगर (of_compat_cmp(cp, compat, म_माप(compat)) == 0)
			वापस score;
		l = म_माप(cp) + 1;
		cp += l;
		cplen -= l;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * of_flat_dt_is_compatible - Return true अगर given node has compat in compatible list
 * @node: node to test
 * @compat: compatible string to compare with compatible list.
 */
पूर्णांक __init of_flat_dt_is_compatible(अचिन्हित दीर्घ node, स्थिर अक्षर *compat)
अणु
	वापस of_fdt_is_compatible(initial_boot_params, node, compat);
पूर्ण

/*
 * of_flat_dt_match - Return true अगर node matches a list of compatible values
 */
अटल पूर्णांक __init of_flat_dt_match(अचिन्हित दीर्घ node, स्थिर अक्षर *स्थिर *compat)
अणु
	अचिन्हित पूर्णांक पंचांगp, score = 0;

	अगर (!compat)
		वापस 0;

	जबतक (*compat) अणु
		पंचांगp = of_fdt_is_compatible(initial_boot_params, node, *compat);
		अगर (पंचांगp && (score == 0 || (पंचांगp < score)))
			score = पंचांगp;
		compat++;
	पूर्ण

	वापस score;
पूर्ण

/*
 * of_get_flat_dt_phandle - Given a node in the flat blob, वापस the phandle
 */
uपूर्णांक32_t __init of_get_flat_dt_phandle(अचिन्हित दीर्घ node)
अणु
	वापस fdt_get_phandle(initial_boot_params, node);
पूर्ण

काष्ठा fdt_scan_status अणु
	स्थिर अक्षर *name;
	पूर्णांक namelen;
	पूर्णांक depth;
	पूर्णांक found;
	पूर्णांक (*iterator)(अचिन्हित दीर्घ node, स्थिर अक्षर *uname, पूर्णांक depth, व्योम *data);
	व्योम *data;
पूर्ण;

स्थिर अक्षर * __init of_flat_dt_get_machine_name(व्योम)
अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ dt_root = of_get_flat_dt_root();

	name = of_get_flat_dt_prop(dt_root, "model", शून्य);
	अगर (!name)
		name = of_get_flat_dt_prop(dt_root, "compatible", शून्य);
	वापस name;
पूर्ण

/**
 * of_flat_dt_match_machine - Iterate match tables to find matching machine.
 *
 * @शेष_match: A machine specअगरic ptr to वापस in हाल of no match.
 * @get_next_compat: callback function to वापस next compatible match table.
 *
 * Iterate through machine match tables to find the best match क्रम the machine
 * compatible string in the FDT.
 */
स्थिर व्योम * __init of_flat_dt_match_machine(स्थिर व्योम *शेष_match,
		स्थिर व्योम * (*get_next_compat)(स्थिर अक्षर * स्थिर**))
अणु
	स्थिर व्योम *data = शून्य;
	स्थिर व्योम *best_data = शेष_match;
	स्थिर अक्षर *स्थिर *compat;
	अचिन्हित दीर्घ dt_root;
	अचिन्हित पूर्णांक best_score = ~1, score = 0;

	dt_root = of_get_flat_dt_root();
	जबतक ((data = get_next_compat(&compat))) अणु
		score = of_flat_dt_match(dt_root, compat);
		अगर (score > 0 && score < best_score) अणु
			best_data = data;
			best_score = score;
		पूर्ण
	पूर्ण
	अगर (!best_data) अणु
		स्थिर अक्षर *prop;
		पूर्णांक size;

		pr_err("\n unrecognized device tree list:\n[ ");

		prop = of_get_flat_dt_prop(dt_root, "compatible", &size);
		अगर (prop) अणु
			जबतक (size > 0) अणु
				prपूर्णांकk("'%s' ", prop);
				size -= म_माप(prop) + 1;
				prop += म_माप(prop) + 1;
			पूर्ण
		पूर्ण
		prपूर्णांकk("]\n\n");
		वापस शून्य;
	पूर्ण

	pr_info("Machine model: %s\n", of_flat_dt_get_machine_name());

	वापस best_data;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INITRD
अटल व्योम __early_init_dt_declare_initrd(अचिन्हित दीर्घ start,
					   अचिन्हित दीर्घ end)
अणु
	/* ARM64 would cause a BUG to occur here when CONFIG_DEBUG_VM is
	 * enabled since __va() is called too early. ARM64 करोes make use
	 * of phys_initrd_start/phys_initrd_size so we can skip this
	 * conversion.
	 */
	अगर (!IS_ENABLED(CONFIG_ARM64)) अणु
		initrd_start = (अचिन्हित दीर्घ)__va(start);
		initrd_end = (अचिन्हित दीर्घ)__va(end);
		initrd_below_start_ok = 1;
	पूर्ण
पूर्ण

/**
 * early_init_dt_check_क्रम_initrd - Decode initrd location from flat tree
 * @node: reference to node containing initrd location ('chosen')
 */
अटल व्योम __init early_init_dt_check_क्रम_initrd(अचिन्हित दीर्घ node)
अणु
	u64 start, end;
	पूर्णांक len;
	स्थिर __be32 *prop;

	pr_debug("Looking for initrd properties... ");

	prop = of_get_flat_dt_prop(node, "linux,initrd-start", &len);
	अगर (!prop)
		वापस;
	start = of_पढ़ो_number(prop, len/4);

	prop = of_get_flat_dt_prop(node, "linux,initrd-end", &len);
	अगर (!prop)
		वापस;
	end = of_पढ़ो_number(prop, len/4);

	__early_init_dt_declare_initrd(start, end);
	phys_initrd_start = start;
	phys_initrd_size = end - start;

	pr_debug("initrd_start=0x%llx  initrd_end=0x%llx\n",
		 (अचिन्हित दीर्घ दीर्घ)start, (अचिन्हित दीर्घ दीर्घ)end);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम early_init_dt_check_क्रम_initrd(अचिन्हित दीर्घ node)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_INITRD */

#अगर_घोषित CONFIG_SERIAL_EARLYCON

पूर्णांक __init early_init_dt_scan_chosen_मानक_निकास(व्योम)
अणु
	पूर्णांक offset;
	स्थिर अक्षर *p, *q, *options = शून्य;
	पूर्णांक l;
	स्थिर काष्ठा earlycon_id *match;
	स्थिर व्योम *fdt = initial_boot_params;

	offset = fdt_path_offset(fdt, "/chosen");
	अगर (offset < 0)
		offset = fdt_path_offset(fdt, "/chosen@0");
	अगर (offset < 0)
		वापस -ENOENT;

	p = fdt_getprop(fdt, offset, "stdout-path", &l);
	अगर (!p)
		p = fdt_getprop(fdt, offset, "linux,stdout-path", &l);
	अगर (!p || !l)
		वापस -ENOENT;

	q = म_अक्षरnul(p, ':');
	अगर (*q != '\0')
		options = q + 1;
	l = q - p;

	/* Get the node specअगरied by मानक_निकास-path */
	offset = fdt_path_offset_namelen(fdt, p, l);
	अगर (offset < 0) अणु
		pr_warn("earlycon: stdout-path %.*s not found\n", l, p);
		वापस 0;
	पूर्ण

	क्रम (match = __earlycon_table; match < __earlycon_table_end; match++) अणु
		अगर (!match->compatible[0])
			जारी;

		अगर (fdt_node_check_compatible(fdt, offset, match->compatible))
			जारी;

		अगर (of_setup_earlycon(match, offset, options) == 0)
			वापस 0;
	पूर्ण
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

/*
 * early_init_dt_scan_root - fetch the top level address and size cells
 */
पूर्णांक __init early_init_dt_scan_root(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				   पूर्णांक depth, व्योम *data)
अणु
	स्थिर __be32 *prop;

	अगर (depth != 0)
		वापस 0;

	dt_root_size_cells = OF_ROOT_NODE_SIZE_CELLS_DEFAULT;
	dt_root_addr_cells = OF_ROOT_NODE_ADDR_CELLS_DEFAULT;

	prop = of_get_flat_dt_prop(node, "#size-cells", शून्य);
	अगर (prop)
		dt_root_size_cells = be32_to_cpup(prop);
	pr_debug("dt_root_size_cells = %x\n", dt_root_size_cells);

	prop = of_get_flat_dt_prop(node, "#address-cells", शून्य);
	अगर (prop)
		dt_root_addr_cells = be32_to_cpup(prop);
	pr_debug("dt_root_addr_cells = %x\n", dt_root_addr_cells);

	/* अवरोध now */
	वापस 1;
पूर्ण

u64 __init dt_mem_next_cell(पूर्णांक s, स्थिर __be32 **cellp)
अणु
	स्थिर __be32 *p = *cellp;

	*cellp = p + s;
	वापस of_पढ़ो_number(p, s);
पूर्ण

/*
 * early_init_dt_scan_memory - Look क्रम and parse memory nodes
 */
पूर्णांक __init early_init_dt_scan_memory(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				     पूर्णांक depth, व्योम *data)
अणु
	स्थिर अक्षर *type = of_get_flat_dt_prop(node, "device_type", शून्य);
	स्थिर __be32 *reg, *endp;
	पूर्णांक l;
	bool hotpluggable;

	/* We are scanning "memory" nodes only */
	अगर (type == शून्य || म_भेद(type, "memory") != 0)
		वापस 0;

	reg = of_get_flat_dt_prop(node, "linux,usable-memory", &l);
	अगर (reg == शून्य)
		reg = of_get_flat_dt_prop(node, "reg", &l);
	अगर (reg == शून्य)
		वापस 0;

	endp = reg + (l / माप(__be32));
	hotpluggable = of_get_flat_dt_prop(node, "hotpluggable", शून्य);

	pr_debug("memory scan node %s, reg size %d,\n", uname, l);

	जबतक ((endp - reg) >= (dt_root_addr_cells + dt_root_size_cells)) अणु
		u64 base, size;

		base = dt_mem_next_cell(dt_root_addr_cells, &reg);
		size = dt_mem_next_cell(dt_root_size_cells, &reg);

		अगर (size == 0)
			जारी;
		pr_debug(" - %llx ,  %llx\n", (अचिन्हित दीर्घ दीर्घ)base,
		    (अचिन्हित दीर्घ दीर्घ)size);

		early_init_dt_add_memory_arch(base, size);

		अगर (!hotpluggable)
			जारी;

		अगर (early_init_dt_mark_hotplug_memory_arch(base, size))
			pr_warn("failed to mark hotplug range 0x%llx - 0x%llx\n",
				base, base + size);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक __init early_init_dt_scan_chosen(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				     पूर्णांक depth, व्योम *data)
अणु
	पूर्णांक l;
	स्थिर अक्षर *p;
	स्थिर व्योम *rng_seed;

	pr_debug("search \"chosen\", depth: %d, uname: %s\n", depth, uname);

	अगर (depth != 1 || !data ||
	    (म_भेद(uname, "chosen") != 0 && म_भेद(uname, "chosen@0") != 0))
		वापस 0;

	early_init_dt_check_क्रम_initrd(node);

	/* Retrieve command line */
	p = of_get_flat_dt_prop(node, "bootargs", &l);
	अगर (p != शून्य && l > 0)
		strlcpy(data, p, min(l, COMMAND_LINE_SIZE));

	/*
	 * CONFIG_CMDLINE is meant to be a शेष in हाल nothing अन्यथा
	 * managed to set the command line, unless CONFIG_CMDLINE_FORCE
	 * is set in which हाल we override whatever was found earlier.
	 */
#अगर_घोषित CONFIG_CMDLINE
#अगर defined(CONFIG_CMDLINE_EXTEND)
	strlcat(data, " ", COMMAND_LINE_SIZE);
	strlcat(data, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
#या_अगर defined(CONFIG_CMDLINE_FORCE)
	strlcpy(data, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
#अन्यथा
	/* No arguments from boot loader, use kernel's  cmdl*/
	अगर (!((अक्षर *)data)[0])
		strlcpy(data, CONFIG_CMDLINE, COMMAND_LINE_SIZE);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_CMDLINE */

	pr_debug("Command line is: %s\n", (अक्षर *)data);

	rng_seed = of_get_flat_dt_prop(node, "rng-seed", &l);
	अगर (rng_seed && l > 0) अणु
		add_bootloader_अक्रमomness(rng_seed, l);

		/* try to clear seed so it won't be found. */
		fdt_nop_property(initial_boot_params, node, "rng-seed");

		/* update CRC check value */
		of_fdt_crc32 = crc32_be(~0, initial_boot_params,
				fdt_totalsize(initial_boot_params));
	पूर्ण

	/* अवरोध now */
	वापस 1;
पूर्ण

#अगर_अघोषित MIN_MEMBLOCK_ADDR
#घोषणा MIN_MEMBLOCK_ADDR	__pa(PAGE_OFFSET)
#पूर्ण_अगर
#अगर_अघोषित MAX_MEMBLOCK_ADDR
#घोषणा MAX_MEMBLOCK_ADDR	((phys_addr_t)~0)
#पूर्ण_अगर

व्योम __init __weak early_init_dt_add_memory_arch(u64 base, u64 size)
अणु
	स्थिर u64 phys_offset = MIN_MEMBLOCK_ADDR;

	अगर (size < PAGE_SIZE - (base & ~PAGE_MASK)) अणु
		pr_warn("Ignoring memory block 0x%llx - 0x%llx\n",
			base, base + size);
		वापस;
	पूर्ण

	अगर (!PAGE_ALIGNED(base)) अणु
		size -= PAGE_SIZE - (base & ~PAGE_MASK);
		base = PAGE_ALIGN(base);
	पूर्ण
	size &= PAGE_MASK;

	अगर (base > MAX_MEMBLOCK_ADDR) अणु
		pr_warn("Ignoring memory block 0x%llx - 0x%llx\n",
			base, base + size);
		वापस;
	पूर्ण

	अगर (base + size - 1 > MAX_MEMBLOCK_ADDR) अणु
		pr_warn("Ignoring memory range 0x%llx - 0x%llx\n",
			((u64)MAX_MEMBLOCK_ADDR) + 1, base + size);
		size = MAX_MEMBLOCK_ADDR - base + 1;
	पूर्ण

	अगर (base + size < phys_offset) अणु
		pr_warn("Ignoring memory block 0x%llx - 0x%llx\n",
			base, base + size);
		वापस;
	पूर्ण
	अगर (base < phys_offset) अणु
		pr_warn("Ignoring memory range 0x%llx - 0x%llx\n",
			base, phys_offset);
		size -= phys_offset - base;
		base = phys_offset;
	पूर्ण
	memblock_add(base, size);
पूर्ण

पूर्णांक __init __weak early_init_dt_mark_hotplug_memory_arch(u64 base, u64 size)
अणु
	वापस memblock_mark_hotplug(base, size);
पूर्ण

पूर्णांक __init __weak early_init_dt_reserve_memory_arch(phys_addr_t base,
					phys_addr_t size, bool nomap)
अणु
	अगर (nomap) अणु
		/*
		 * If the memory is alपढ़ोy reserved (by another region), we
		 * should not allow it to be marked nomap.
		 */
		अगर (memblock_is_region_reserved(base, size))
			वापस -EBUSY;

		वापस memblock_mark_nomap(base, size);
	पूर्ण
	वापस memblock_reserve(base, size);
पूर्ण

अटल व्योम * __init early_init_dt_alloc_memory_arch(u64 size, u64 align)
अणु
	व्योम *ptr = memblock_alloc(size, align);

	अगर (!ptr)
		panic("%s: Failed to allocate %llu bytes align=0x%llx\n",
		      __func__, size, align);

	वापस ptr;
पूर्ण

bool __init early_init_dt_verअगरy(व्योम *params)
अणु
	अगर (!params)
		वापस false;

	/* check device tree validity */
	अगर (fdt_check_header(params))
		वापस false;

	/* Setup flat device-tree poपूर्णांकer */
	initial_boot_params = params;
	of_fdt_crc32 = crc32_be(~0, initial_boot_params,
				fdt_totalsize(initial_boot_params));
	वापस true;
पूर्ण


व्योम __init early_init_dt_scan_nodes(व्योम)
अणु
	पूर्णांक rc = 0;

	/* Retrieve various inक्रमmation from the /chosen node */
	rc = of_scan_flat_dt(early_init_dt_scan_chosen, boot_command_line);
	अगर (!rc)
		pr_warn("No chosen node found, continuing without\n");

	/* Initialize अणुsize,addressपूर्ण-cells info */
	of_scan_flat_dt(early_init_dt_scan_root, शून्य);

	/* Setup memory, calling early_init_dt_add_memory_arch */
	of_scan_flat_dt(early_init_dt_scan_memory, शून्य);
पूर्ण

bool __init early_init_dt_scan(व्योम *params)
अणु
	bool status;

	status = early_init_dt_verअगरy(params);
	अगर (!status)
		वापस false;

	early_init_dt_scan_nodes();
	वापस true;
पूर्ण

/**
 * unflatten_device_tree - create tree of device_nodes from flat blob
 *
 * unflattens the device-tree passed by the firmware, creating the
 * tree of काष्ठा device_node. It also fills the "name" and "type"
 * poपूर्णांकers of the nodes so the normal device-tree walking functions
 * can be used.
 */
व्योम __init unflatten_device_tree(व्योम)
अणु
	__unflatten_device_tree(initial_boot_params, शून्य, &of_root,
				early_init_dt_alloc_memory_arch, false);

	/* Get poपूर्णांकer to "/chosen" and "/aliases" nodes क्रम use everywhere */
	of_alias_scan(early_init_dt_alloc_memory_arch);

	unittest_unflatten_overlay_base();
पूर्ण

/**
 * unflatten_and_copy_device_tree - copy and create tree of device_nodes from flat blob
 *
 * Copies and unflattens the device-tree passed by the firmware, creating the
 * tree of काष्ठा device_node. It also fills the "name" and "type"
 * poपूर्णांकers of the nodes so the normal device-tree walking functions
 * can be used. This should only be used when the FDT memory has not been
 * reserved such is the हाल when the FDT is built-in to the kernel init
 * section. If the FDT memory is reserved alपढ़ोy then unflatten_device_tree
 * should be used instead.
 */
व्योम __init unflatten_and_copy_device_tree(व्योम)
अणु
	पूर्णांक size;
	व्योम *dt;

	अगर (!initial_boot_params) अणु
		pr_warn("No valid device tree found, continuing without\n");
		वापस;
	पूर्ण

	size = fdt_totalsize(initial_boot_params);
	dt = early_init_dt_alloc_memory_arch(size,
					     roundup_घात_of_two(FDT_V17_SIZE));

	अगर (dt) अणु
		स_नकल(dt, initial_boot_params, size);
		initial_boot_params = dt;
	पूर्ण
	unflatten_device_tree();
पूर्ण

#अगर_घोषित CONFIG_SYSFS
अटल sमाप_प्रकार of_fdt_raw_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj,
			       काष्ठा bin_attribute *bin_attr,
			       अक्षर *buf, loff_t off, माप_प्रकार count)
अणु
	स_नकल(buf, initial_boot_params + off, count);
	वापस count;
पूर्ण

अटल पूर्णांक __init of_fdt_raw_init(व्योम)
अणु
	अटल काष्ठा bin_attribute of_fdt_raw_attr =
		__BIN_ATTR(fdt, S_IRUSR, of_fdt_raw_पढ़ो, शून्य, 0);

	अगर (!initial_boot_params)
		वापस 0;

	अगर (of_fdt_crc32 != crc32_be(~0, initial_boot_params,
				     fdt_totalsize(initial_boot_params))) अणु
		pr_warn("not creating '/sys/firmware/fdt': CRC check failed\n");
		वापस 0;
	पूर्ण
	of_fdt_raw_attr.size = fdt_totalsize(initial_boot_params);
	वापस sysfs_create_bin_file(firmware_kobj, &of_fdt_raw_attr);
पूर्ण
late_initcall(of_fdt_raw_init);
#पूर्ण_अगर

#पूर्ण_अगर /* CONFIG_OF_EARLY_FLATTREE */
