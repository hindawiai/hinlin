<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <linux/mm.h>

#अगर_अघोषित ioremap_cache
/* temporary जबतक we convert existing ioremap_cache users to memremap */
__weak व्योम __iomem *ioremap_cache(resource_माप_प्रकार offset, अचिन्हित दीर्घ size)
अणु
	वापस ioremap(offset, size);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_memremap_wb
अटल व्योम *arch_memremap_wb(resource_माप_प्रकार offset, अचिन्हित दीर्घ size)
अणु
	वापस (__क्रमce व्योम *)ioremap_cache(offset, size);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित arch_memremap_can_ram_remap
अटल bool arch_memremap_can_ram_remap(resource_माप_प्रकार offset, माप_प्रकार size,
					अचिन्हित दीर्घ flags)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल व्योम *try_ram_remap(resource_माप_प्रकार offset, माप_प्रकार size,
			   अचिन्हित दीर्घ flags)
अणु
	अचिन्हित दीर्घ pfn = PHYS_PFN(offset);

	/* In the simple हाल just वापस the existing linear address */
	अगर (pfn_valid(pfn) && !PageHighMem(pfn_to_page(pfn)) &&
	    arch_memremap_can_ram_remap(offset, size, flags))
		वापस __va(offset);

	वापस शून्य; /* fallback to arch_memremap_wb */
पूर्ण

/**
 * memremap() - remap an iomem_resource as cacheable memory
 * @offset: iomem resource start address
 * @size: size of remap
 * @flags: any of MEMREMAP_WB, MEMREMAP_WT, MEMREMAP_WC,
 *		  MEMREMAP_ENC, MEMREMAP_DEC
 *
 * memremap() is "ioremap" क्रम हालs where it is known that the resource
 * being mapped करोes not have i/o side effects and the __iomem
 * annotation is not applicable. In the हाल of multiple flags, the dअगरferent
 * mapping types will be attempted in the order listed below until one of
 * them succeeds.
 *
 * MEMREMAP_WB - matches the शेष mapping क्रम System RAM on
 * the architecture.  This is usually a पढ़ो-allocate ग_लिखो-back cache.
 * Moreover, अगर MEMREMAP_WB is specअगरied and the requested remap region is RAM
 * memremap() will bypass establishing a new mapping and instead वापस
 * a poपूर्णांकer पूर्णांकo the direct map.
 *
 * MEMREMAP_WT - establish a mapping whereby ग_लिखोs either bypass the
 * cache or are written through to memory and never exist in a
 * cache-dirty state with respect to program visibility.  Attempts to
 * map System RAM with this mapping type will fail.
 *
 * MEMREMAP_WC - establish a ग_लिखोcombine mapping, whereby ग_लिखोs may
 * be coalesced together (e.g. in the CPU's ग_लिखो buffers), but is otherwise
 * uncached. Attempts to map System RAM with this mapping type will fail.
 */
व्योम *memremap(resource_माप_प्रकार offset, माप_प्रकार size, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक is_ram = region_पूर्णांकersects(offset, size,
				       IORESOURCE_SYSTEM_RAM, IORES_DESC_NONE);
	व्योम *addr = शून्य;

	अगर (!flags)
		वापस शून्य;

	अगर (is_ram == REGION_MIXED) अणु
		WARN_ONCE(1, "memremap attempted on mixed range %pa size: %#lx\n",
				&offset, (अचिन्हित दीर्घ) size);
		वापस शून्य;
	पूर्ण

	/* Try all mapping types requested until one वापसs non-शून्य */
	अगर (flags & MEMREMAP_WB) अणु
		/*
		 * MEMREMAP_WB is special in that it can be satisfied
		 * from the direct map.  Some archs depend on the
		 * capability of memremap() to स्वतःdetect हालs where
		 * the requested range is potentially in System RAM.
		 */
		अगर (is_ram == REGION_INTERSECTS)
			addr = try_ram_remap(offset, size, flags);
		अगर (!addr)
			addr = arch_memremap_wb(offset, size);
	पूर्ण

	/*
	 * If we करोn't have a mapping yet and other request flags are
	 * present then we will be attempting to establish a new भव
	 * address mapping.  Enक्रमce that this mapping is not aliasing
	 * System RAM.
	 */
	अगर (!addr && is_ram == REGION_INTERSECTS && flags != MEMREMAP_WB) अणु
		WARN_ONCE(1, "memremap attempted on ram %pa size: %#lx\n",
				&offset, (अचिन्हित दीर्घ) size);
		वापस शून्य;
	पूर्ण

	अगर (!addr && (flags & MEMREMAP_WT))
		addr = ioremap_wt(offset, size);

	अगर (!addr && (flags & MEMREMAP_WC))
		addr = ioremap_wc(offset, size);

	वापस addr;
पूर्ण
EXPORT_SYMBOL(memremap);

व्योम memunmap(व्योम *addr)
अणु
	अगर (is_ioremap_addr(addr))
		iounmap((व्योम __iomem *) addr);
पूर्ण
EXPORT_SYMBOL(memunmap);

अटल व्योम devm_memremap_release(काष्ठा device *dev, व्योम *res)
अणु
	memunmap(*(व्योम **)res);
पूर्ण

अटल पूर्णांक devm_memremap_match(काष्ठा device *dev, व्योम *res, व्योम *match_data)
अणु
	वापस *(व्योम **)res == match_data;
पूर्ण

व्योम *devm_memremap(काष्ठा device *dev, resource_माप_प्रकार offset,
		माप_प्रकार size, अचिन्हित दीर्घ flags)
अणु
	व्योम **ptr, *addr;

	ptr = devres_alloc_node(devm_memremap_release, माप(*ptr), GFP_KERNEL,
			dev_to_node(dev));
	अगर (!ptr)
		वापस ERR_PTR(-ENOMEM);

	addr = memremap(offset, size, flags);
	अगर (addr) अणु
		*ptr = addr;
		devres_add(dev, ptr);
	पूर्ण अन्यथा अणु
		devres_मुक्त(ptr);
		वापस ERR_PTR(-ENXIO);
	पूर्ण

	वापस addr;
पूर्ण
EXPORT_SYMBOL(devm_memremap);

व्योम devm_memunmap(काष्ठा device *dev, व्योम *addr)
अणु
	WARN_ON(devres_release(dev, devm_memremap_release,
				devm_memremap_match, addr));
पूर्ण
EXPORT_SYMBOL(devm_memunmap);
