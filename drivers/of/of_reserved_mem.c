<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Device tree based initialization code क्रम reserved memory.
 *
 * Copyright (c) 2013, 2015 The Linux Foundation. All Rights Reserved.
 * Copyright (c) 2013,2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 * Author: Marek Szyprowski <m.szyprowski@samsung.com>
 * Author: Josh Cartwright <joshc@codeaurora.org>
 */

#घोषणा pr_fmt(fmt)	"OF: reserved mem: " fmt

#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/mm.h>
#समावेश <linux/sizes.h>
#समावेश <linux/of_reserved_स्मृति.स>
#समावेश <linux/sort.h>
#समावेश <linux/slab.h>
#समावेश <linux/memblock.h>

#घोषणा MAX_RESERVED_REGIONS	64
अटल काष्ठा reserved_mem reserved_mem[MAX_RESERVED_REGIONS];
अटल पूर्णांक reserved_mem_count;

अटल पूर्णांक __init early_init_dt_alloc_reserved_memory_arch(phys_addr_t size,
	phys_addr_t align, phys_addr_t start, phys_addr_t end, bool nomap,
	phys_addr_t *res_base)
अणु
	phys_addr_t base;

	end = !end ? MEMBLOCK_ALLOC_ANYWHERE : end;
	align = !align ? SMP_CACHE_BYTES : align;
	base = memblock_find_in_range(start, end, size, align);
	अगर (!base)
		वापस -ENOMEM;

	*res_base = base;
	अगर (nomap)
		वापस memblock_हटाओ(base, size);

	वापस memblock_reserve(base, size);
पूर्ण

/*
 * fdt_reserved_mem_save_node() - save fdt node क्रम second pass initialization
 */
व्योम __init fdt_reserved_mem_save_node(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				      phys_addr_t base, phys_addr_t size)
अणु
	काष्ठा reserved_mem *rmem = &reserved_mem[reserved_mem_count];

	अगर (reserved_mem_count == ARRAY_SIZE(reserved_mem)) अणु
		pr_err("not enough space for all defined regions.\n");
		वापस;
	पूर्ण

	rmem->fdt_node = node;
	rmem->name = uname;
	rmem->base = base;
	rmem->size = size;

	reserved_mem_count++;
	वापस;
पूर्ण

/*
 * __reserved_mem_alloc_size() - allocate reserved memory described by
 *	'size', 'alignment'  and 'alloc-ranges' properties.
 */
अटल पूर्णांक __init __reserved_mem_alloc_size(अचिन्हित दीर्घ node,
	स्थिर अक्षर *uname, phys_addr_t *res_base, phys_addr_t *res_size)
अणु
	पूर्णांक t_len = (dt_root_addr_cells + dt_root_size_cells) * माप(__be32);
	phys_addr_t start = 0, end = 0;
	phys_addr_t base = 0, align = 0, size;
	पूर्णांक len;
	स्थिर __be32 *prop;
	bool nomap;
	पूर्णांक ret;

	prop = of_get_flat_dt_prop(node, "size", &len);
	अगर (!prop)
		वापस -EINVAL;

	अगर (len != dt_root_size_cells * माप(__be32)) अणु
		pr_err("invalid size property in '%s' node.\n", uname);
		वापस -EINVAL;
	पूर्ण
	size = dt_mem_next_cell(dt_root_size_cells, &prop);

	prop = of_get_flat_dt_prop(node, "alignment", &len);
	अगर (prop) अणु
		अगर (len != dt_root_addr_cells * माप(__be32)) अणु
			pr_err("invalid alignment property in '%s' node.\n",
				uname);
			वापस -EINVAL;
		पूर्ण
		align = dt_mem_next_cell(dt_root_addr_cells, &prop);
	पूर्ण

	nomap = of_get_flat_dt_prop(node, "no-map", शून्य) != शून्य;

	/* Need adjust the alignment to satisfy the CMA requirement */
	अगर (IS_ENABLED(CONFIG_CMA)
	    && of_flat_dt_is_compatible(node, "shared-dma-pool")
	    && of_get_flat_dt_prop(node, "reusable", शून्य)
	    && !nomap) अणु
		अचिन्हित दीर्घ order =
			max_t(अचिन्हित दीर्घ, MAX_ORDER - 1, pageblock_order);

		align = max(align, (phys_addr_t)PAGE_SIZE << order);
	पूर्ण

	prop = of_get_flat_dt_prop(node, "alloc-ranges", &len);
	अगर (prop) अणु

		अगर (len % t_len != 0) अणु
			pr_err("invalid alloc-ranges property in '%s', skipping node.\n",
			       uname);
			वापस -EINVAL;
		पूर्ण

		base = 0;

		जबतक (len > 0) अणु
			start = dt_mem_next_cell(dt_root_addr_cells, &prop);
			end = start + dt_mem_next_cell(dt_root_size_cells,
						       &prop);

			ret = early_init_dt_alloc_reserved_memory_arch(size,
					align, start, end, nomap, &base);
			अगर (ret == 0) अणु
				pr_debug("allocated memory for '%s' node: base %pa, size %ld MiB\n",
					uname, &base,
					(अचिन्हित दीर्घ)size / SZ_1M);
				अवरोध;
			पूर्ण
			len -= t_len;
		पूर्ण

	पूर्ण अन्यथा अणु
		ret = early_init_dt_alloc_reserved_memory_arch(size, align,
							0, 0, nomap, &base);
		अगर (ret == 0)
			pr_debug("allocated memory for '%s' node: base %pa, size %ld MiB\n",
				uname, &base, (अचिन्हित दीर्घ)size / SZ_1M);
	पूर्ण

	अगर (base == 0) अणु
		pr_info("failed to allocate memory for node '%s'\n", uname);
		वापस -ENOMEM;
	पूर्ण

	*res_base = base;
	*res_size = size;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id __rmem_of_table_sentinel
	__used __section("__reservedmem_of_table_end");

/*
 * __reserved_mem_init_node() - call region specअगरic reserved memory init code
 */
अटल पूर्णांक __init __reserved_mem_init_node(काष्ठा reserved_mem *rmem)
अणु
	बाह्य स्थिर काष्ठा of_device_id __reservedmem_of_table[];
	स्थिर काष्ठा of_device_id *i;
	पूर्णांक ret = -ENOENT;

	क्रम (i = __reservedmem_of_table; i < &__rmem_of_table_sentinel; i++) अणु
		reservedmem_of_init_fn initfn = i->data;
		स्थिर अक्षर *compat = i->compatible;

		अगर (!of_flat_dt_is_compatible(rmem->fdt_node, compat))
			जारी;

		ret = initfn(rmem);
		अगर (ret == 0) अणु
			pr_info("initialized node %s, compatible id %s\n",
				rmem->name, compat);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __init __rmem_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा reserved_mem *ra = a, *rb = b;

	अगर (ra->base < rb->base)
		वापस -1;

	अगर (ra->base > rb->base)
		वापस 1;

	/*
	 * Put the dynamic allocations (address == 0, size == 0) beक्रमe अटल
	 * allocations at address 0x0 so that overlap detection works
	 * correctly.
	 */
	अगर (ra->size < rb->size)
		वापस -1;
	अगर (ra->size > rb->size)
		वापस 1;

	वापस 0;
पूर्ण

अटल व्योम __init __rmem_check_क्रम_overlap(व्योम)
अणु
	पूर्णांक i;

	अगर (reserved_mem_count < 2)
		वापस;

	sort(reserved_mem, reserved_mem_count, माप(reserved_mem[0]),
	     __rmem_cmp, शून्य);
	क्रम (i = 0; i < reserved_mem_count - 1; i++) अणु
		काष्ठा reserved_mem *this, *next;

		this = &reserved_mem[i];
		next = &reserved_mem[i + 1];

		अगर (this->base + this->size > next->base) अणु
			phys_addr_t this_end, next_end;

			this_end = this->base + this->size;
			next_end = next->base + next->size;
			pr_err("OVERLAP DETECTED!\n%s (%pa--%pa) overlaps with %s (%pa--%pa)\n",
			       this->name, &this->base, &this_end,
			       next->name, &next->base, &next_end);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * fdt_init_reserved_mem() - allocate and init all saved reserved memory regions
 */
व्योम __init fdt_init_reserved_mem(व्योम)
अणु
	पूर्णांक i;

	/* check क्रम overlapping reserved regions */
	__rmem_check_क्रम_overlap();

	क्रम (i = 0; i < reserved_mem_count; i++) अणु
		काष्ठा reserved_mem *rmem = &reserved_mem[i];
		अचिन्हित दीर्घ node = rmem->fdt_node;
		पूर्णांक len;
		स्थिर __be32 *prop;
		पूर्णांक err = 0;
		bool nomap;

		nomap = of_get_flat_dt_prop(node, "no-map", शून्य) != शून्य;
		prop = of_get_flat_dt_prop(node, "phandle", &len);
		अगर (!prop)
			prop = of_get_flat_dt_prop(node, "linux,phandle", &len);
		अगर (prop)
			rmem->phandle = of_पढ़ो_number(prop, len/4);

		अगर (rmem->size == 0)
			err = __reserved_mem_alloc_size(node, rmem->name,
						 &rmem->base, &rmem->size);
		अगर (err == 0) अणु
			err = __reserved_mem_init_node(rmem);
			अगर (err != 0 && err != -ENOENT) अणु
				pr_info("node %s compatible matching fail\n",
					rmem->name);
				memblock_मुक्त(rmem->base, rmem->size);
				अगर (nomap)
					memblock_add(rmem->base, rmem->size);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा reserved_mem *__find_rmem(काष्ठा device_node *node)
अणु
	अचिन्हित पूर्णांक i;

	अगर (!node->phandle)
		वापस शून्य;

	क्रम (i = 0; i < reserved_mem_count; i++)
		अगर (reserved_mem[i].phandle == node->phandle)
			वापस &reserved_mem[i];
	वापस शून्य;
पूर्ण

काष्ठा rmem_asचिन्हित_device अणु
	काष्ठा device *dev;
	काष्ठा reserved_mem *rmem;
	काष्ठा list_head list;
पूर्ण;

अटल LIST_HEAD(of_rmem_asचिन्हित_device_list);
अटल DEFINE_MUTEX(of_rmem_asचिन्हित_device_mutex);

/**
 * of_reserved_mem_device_init_by_idx() - assign reserved memory region to
 *					  given device
 * @dev:	Poपूर्णांकer to the device to configure
 * @np:		Poपूर्णांकer to the device_node with 'reserved-memory' property
 * @idx:	Index of selected region
 *
 * This function assigns respective DMA-mapping operations based on reserved
 * memory region specअगरied by 'memory-region' property in @np node to the @dev
 * device. When driver needs to use more than one reserved memory region, it
 * should allocate child devices and initialize regions by name क्रम each of
 * child device.
 *
 * Returns error code or zero on success.
 */
पूर्णांक of_reserved_mem_device_init_by_idx(काष्ठा device *dev,
				       काष्ठा device_node *np, पूर्णांक idx)
अणु
	काष्ठा rmem_asचिन्हित_device *rd;
	काष्ठा device_node *target;
	काष्ठा reserved_mem *rmem;
	पूर्णांक ret;

	अगर (!np || !dev)
		वापस -EINVAL;

	target = of_parse_phandle(np, "memory-region", idx);
	अगर (!target)
		वापस -ENODEV;

	अगर (!of_device_is_available(target)) अणु
		of_node_put(target);
		वापस 0;
	पूर्ण

	rmem = __find_rmem(target);
	of_node_put(target);

	अगर (!rmem || !rmem->ops || !rmem->ops->device_init)
		वापस -EINVAL;

	rd = kदो_स्मृति(माप(काष्ठा rmem_asचिन्हित_device), GFP_KERNEL);
	अगर (!rd)
		वापस -ENOMEM;

	ret = rmem->ops->device_init(rmem, dev);
	अगर (ret == 0) अणु
		rd->dev = dev;
		rd->rmem = rmem;

		mutex_lock(&of_rmem_asचिन्हित_device_mutex);
		list_add(&rd->list, &of_rmem_asचिन्हित_device_list);
		mutex_unlock(&of_rmem_asचिन्हित_device_mutex);

		dev_info(dev, "assigned reserved memory node %s\n", rmem->name);
	पूर्ण अन्यथा अणु
		kमुक्त(rd);
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(of_reserved_mem_device_init_by_idx);

/**
 * of_reserved_mem_device_init_by_name() - assign named reserved memory region
 *					   to given device
 * @dev: poपूर्णांकer to the device to configure
 * @np: poपूर्णांकer to the device node with 'memory-region' property
 * @name: name of the selected memory region
 *
 * Returns: 0 on success or a negative error-code on failure.
 */
पूर्णांक of_reserved_mem_device_init_by_name(काष्ठा device *dev,
					काष्ठा device_node *np,
					स्थिर अक्षर *name)
अणु
	पूर्णांक idx = of_property_match_string(np, "memory-region-names", name);

	वापस of_reserved_mem_device_init_by_idx(dev, np, idx);
पूर्ण
EXPORT_SYMBOL_GPL(of_reserved_mem_device_init_by_name);

/**
 * of_reserved_mem_device_release() - release reserved memory device काष्ठाures
 * @dev:	Poपूर्णांकer to the device to deconfigure
 *
 * This function releases काष्ठाures allocated क्रम memory region handling क्रम
 * the given device.
 */
व्योम of_reserved_mem_device_release(काष्ठा device *dev)
अणु
	काष्ठा rmem_asचिन्हित_device *rd, *पंचांगp;
	LIST_HEAD(release_list);

	mutex_lock(&of_rmem_asचिन्हित_device_mutex);
	list_क्रम_each_entry_safe(rd, पंचांगp, &of_rmem_asचिन्हित_device_list, list) अणु
		अगर (rd->dev == dev)
			list_move_tail(&rd->list, &release_list);
	पूर्ण
	mutex_unlock(&of_rmem_asचिन्हित_device_mutex);

	list_क्रम_each_entry_safe(rd, पंचांगp, &release_list, list) अणु
		अगर (rd->rmem && rd->rmem->ops && rd->rmem->ops->device_release)
			rd->rmem->ops->device_release(rd->rmem, dev);

		kमुक्त(rd);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(of_reserved_mem_device_release);

/**
 * of_reserved_mem_lookup() - acquire reserved_mem from a device node
 * @np:		node poपूर्णांकer of the desired reserved-memory region
 *
 * This function allows drivers to acquire a reference to the reserved_mem
 * काष्ठा based on a device node handle.
 *
 * Returns a reserved_mem reference, or शून्य on error.
 */
काष्ठा reserved_mem *of_reserved_mem_lookup(काष्ठा device_node *np)
अणु
	स्थिर अक्षर *name;
	पूर्णांक i;

	अगर (!np->full_name)
		वापस शून्य;

	name = kbasename(np->full_name);
	क्रम (i = 0; i < reserved_mem_count; i++)
		अगर (!म_भेद(reserved_mem[i].name, name))
			वापस &reserved_mem[i];

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(of_reserved_mem_lookup);
