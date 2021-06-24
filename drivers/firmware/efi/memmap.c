<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Common EFI memory map functions.
 */

#घोषणा pr_fmt(fmt) "efi: " fmt

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/efi.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/early_ioremap.h>
#समावेश <linux/memblock.h>
#समावेश <linux/slab.h>

अटल phys_addr_t __init __efi_memmap_alloc_early(अचिन्हित दीर्घ size)
अणु
	वापस memblock_phys_alloc(size, SMP_CACHE_BYTES);
पूर्ण

अटल phys_addr_t __init __efi_memmap_alloc_late(अचिन्हित दीर्घ size)
अणु
	अचिन्हित पूर्णांक order = get_order(size);
	काष्ठा page *p = alloc_pages(GFP_KERNEL, order);

	अगर (!p)
		वापस 0;

	वापस PFN_PHYS(page_to_pfn(p));
पूर्ण

व्योम __init __efi_memmap_मुक्त(u64 phys, अचिन्हित दीर्घ size, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & EFI_MEMMAP_MEMBLOCK) अणु
		अगर (slab_is_available())
			memblock_मुक्त_late(phys, size);
		अन्यथा
			memblock_मुक्त(phys, size);
	पूर्ण अन्यथा अगर (flags & EFI_MEMMAP_SLAB) अणु
		काष्ठा page *p = pfn_to_page(PHYS_PFN(phys));
		अचिन्हित पूर्णांक order = get_order(size);

		मुक्त_pages((अचिन्हित दीर्घ) page_address(p), order);
	पूर्ण
पूर्ण

अटल व्योम __init efi_memmap_मुक्त(व्योम)
अणु
	__efi_memmap_मुक्त(efi.memmap.phys_map,
			efi.memmap.desc_size * efi.memmap.nr_map,
			efi.memmap.flags);
पूर्ण

/**
 * efi_memmap_alloc - Allocate memory क्रम the EFI memory map
 * @num_entries: Number of entries in the allocated map.
 * @data: efi memmap installation parameters
 *
 * Depending on whether mm_init() has alपढ़ोy been invoked or not,
 * either memblock or "normal" page allocation is used.
 *
 * Returns the physical address of the allocated memory map on
 * success, zero on failure.
 */
पूर्णांक __init efi_memmap_alloc(अचिन्हित पूर्णांक num_entries,
		काष्ठा efi_memory_map_data *data)
अणु
	/* Expect allocation parameters are zero initialized */
	WARN_ON(data->phys_map || data->size);

	data->size = num_entries * efi.memmap.desc_size;
	data->desc_version = efi.memmap.desc_version;
	data->desc_size = efi.memmap.desc_size;
	data->flags &= ~(EFI_MEMMAP_SLAB | EFI_MEMMAP_MEMBLOCK);
	data->flags |= efi.memmap.flags & EFI_MEMMAP_LATE;

	अगर (slab_is_available()) अणु
		data->flags |= EFI_MEMMAP_SLAB;
		data->phys_map = __efi_memmap_alloc_late(data->size);
	पूर्ण अन्यथा अणु
		data->flags |= EFI_MEMMAP_MEMBLOCK;
		data->phys_map = __efi_memmap_alloc_early(data->size);
	पूर्ण

	अगर (!data->phys_map)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

/**
 * __efi_memmap_init - Common code क्रम mapping the EFI memory map
 * @data: EFI memory map data
 *
 * This function takes care of figuring out which function to use to
 * map the EFI memory map in efi.memmap based on how far पूर्णांकo the boot
 * we are.
 *
 * During bootup EFI_MEMMAP_LATE in data->flags should be clear since we
 * only have access to the early_memremap*() functions as the vदो_स्मृति
 * space isn't setup.  Once the kernel is fully booted we can fallback
 * to the more robust memremap*() API.
 *
 * Returns zero on success, a negative error code on failure.
 */
अटल पूर्णांक __init __efi_memmap_init(काष्ठा efi_memory_map_data *data)
अणु
	काष्ठा efi_memory_map map;
	phys_addr_t phys_map;

	अगर (efi_enabled(EFI_PARAVIRT))
		वापस 0;

	phys_map = data->phys_map;

	अगर (data->flags & EFI_MEMMAP_LATE)
		map.map = memremap(phys_map, data->size, MEMREMAP_WB);
	अन्यथा
		map.map = early_memremap(phys_map, data->size);

	अगर (!map.map) अणु
		pr_err("Could not map the memory map!\n");
		वापस -ENOMEM;
	पूर्ण

	/* NOP अगर data->flags & (EFI_MEMMAP_MEMBLOCK | EFI_MEMMAP_SLAB) == 0 */
	efi_memmap_मुक्त();

	map.phys_map = data->phys_map;
	map.nr_map = data->size / data->desc_size;
	map.map_end = map.map + data->size;

	map.desc_version = data->desc_version;
	map.desc_size = data->desc_size;
	map.flags = data->flags;

	set_bit(EFI_MEMMAP, &efi.flags);

	efi.memmap = map;

	वापस 0;
पूर्ण

/**
 * efi_memmap_init_early - Map the EFI memory map data काष्ठाure
 * @data: EFI memory map data
 *
 * Use early_memremap() to map the passed in EFI memory map and assign
 * it to efi.memmap.
 */
पूर्णांक __init efi_memmap_init_early(काष्ठा efi_memory_map_data *data)
अणु
	/* Cannot go backwards */
	WARN_ON(efi.memmap.flags & EFI_MEMMAP_LATE);

	data->flags = 0;
	वापस __efi_memmap_init(data);
पूर्ण

व्योम __init efi_memmap_unmap(व्योम)
अणु
	अगर (!efi_enabled(EFI_MEMMAP))
		वापस;

	अगर (!(efi.memmap.flags & EFI_MEMMAP_LATE)) अणु
		अचिन्हित दीर्घ size;

		size = efi.memmap.desc_size * efi.memmap.nr_map;
		early_memunmap(efi.memmap.map, size);
	पूर्ण अन्यथा अणु
		memunmap(efi.memmap.map);
	पूर्ण

	efi.memmap.map = शून्य;
	clear_bit(EFI_MEMMAP, &efi.flags);
पूर्ण

/**
 * efi_memmap_init_late - Map efi.memmap with memremap()
 * @phys_addr: Physical address of the new EFI memory map
 * @size: Size in bytes of the new EFI memory map
 *
 * Setup a mapping of the EFI memory map using ioremap_cache(). This
 * function should only be called once the vदो_स्मृति space has been
 * setup and is thereक्रमe not suitable क्रम calling during early EFI
 * initialise, e.g. in efi_init(). Additionally, it expects
 * efi_memmap_init_early() to have alपढ़ोy been called.
 *
 * The reason there are two EFI memmap initialisation
 * (efi_memmap_init_early() and this late version) is because the
 * early EFI memmap should be explicitly unmapped once EFI
 * initialisation is complete as the fixmap space used to map the EFI
 * memmap (via early_memremap()) is a scarce resource.
 *
 * This late mapping is पूर्णांकended to persist क्रम the duration of
 * runसमय so that things like efi_mem_desc_lookup() and
 * efi_mem_attributes() always work.
 *
 * Returns zero on success, a negative error code on failure.
 */
पूर्णांक __init efi_memmap_init_late(phys_addr_t addr, अचिन्हित दीर्घ size)
अणु
	काष्ठा efi_memory_map_data data = अणु
		.phys_map = addr,
		.size = size,
		.flags = EFI_MEMMAP_LATE,
	पूर्ण;

	/* Did we क्रमget to unmap the early EFI memmap? */
	WARN_ON(efi.memmap.map);

	/* Were we alपढ़ोy called? */
	WARN_ON(efi.memmap.flags & EFI_MEMMAP_LATE);

	/*
	 * It makes no sense to allow callers to रेजिस्टर dअगरferent
	 * values क्रम the following fields. Copy them out of the
	 * existing early EFI memmap.
	 */
	data.desc_version = efi.memmap.desc_version;
	data.desc_size = efi.memmap.desc_size;

	वापस __efi_memmap_init(&data);
पूर्ण

/**
 * efi_memmap_install - Install a new EFI memory map in efi.memmap
 * @ctx: map allocation parameters (address, size, flags)
 *
 * Unlike efi_memmap_init_*(), this function करोes not allow the caller
 * to चयन from early to late mappings. It simply uses the existing
 * mapping function and installs the new memmap.
 *
 * Returns zero on success, a negative error code on failure.
 */
पूर्णांक __init efi_memmap_install(काष्ठा efi_memory_map_data *data)
अणु
	efi_memmap_unmap();

	वापस __efi_memmap_init(data);
पूर्ण

/**
 * efi_memmap_split_count - Count number of additional EFI memmap entries
 * @md: EFI memory descriptor to split
 * @range: Address range (start, end) to split around
 *
 * Returns the number of additional EFI memmap entries required to
 * accomodate @range.
 */
पूर्णांक __init efi_memmap_split_count(efi_memory_desc_t *md, काष्ठा range *range)
अणु
	u64 m_start, m_end;
	u64 start, end;
	पूर्णांक count = 0;

	start = md->phys_addr;
	end = start + (md->num_pages << EFI_PAGE_SHIFT) - 1;

	/* modअगरying range */
	m_start = range->start;
	m_end = range->end;

	अगर (m_start <= start) अणु
		/* split पूर्णांकo 2 parts */
		अगर (start < m_end && m_end < end)
			count++;
	पूर्ण

	अगर (start < m_start && m_start < end) अणु
		/* split पूर्णांकo 3 parts */
		अगर (m_end < end)
			count += 2;
		/* split पूर्णांकo 2 parts */
		अगर (end <= m_end)
			count++;
	पूर्ण

	वापस count;
पूर्ण

/**
 * efi_memmap_insert - Insert a memory region in an EFI memmap
 * @old_memmap: The existing EFI memory map काष्ठाure
 * @buf: Address of buffer to store new map
 * @mem: Memory map entry to insert
 *
 * It is suggested that you call efi_memmap_split_count() first
 * to see how large @buf needs to be.
 */
व्योम __init efi_memmap_insert(काष्ठा efi_memory_map *old_memmap, व्योम *buf,
			      काष्ठा efi_mem_range *mem)
अणु
	u64 m_start, m_end, m_attr;
	efi_memory_desc_t *md;
	u64 start, end;
	व्योम *old, *new;

	/* modअगरying range */
	m_start = mem->range.start;
	m_end = mem->range.end;
	m_attr = mem->attribute;

	/*
	 * The EFI memory map deals with regions in EFI_PAGE_SIZE
	 * units. Ensure that the region described by 'mem' is aligned
	 * correctly.
	 */
	अगर (!IS_ALIGNED(m_start, EFI_PAGE_SIZE) ||
	    !IS_ALIGNED(m_end + 1, EFI_PAGE_SIZE)) अणु
		WARN_ON(1);
		वापस;
	पूर्ण

	क्रम (old = old_memmap->map, new = buf;
	     old < old_memmap->map_end;
	     old += old_memmap->desc_size, new += old_memmap->desc_size) अणु

		/* copy original EFI memory descriptor */
		स_नकल(new, old, old_memmap->desc_size);
		md = new;
		start = md->phys_addr;
		end = md->phys_addr + (md->num_pages << EFI_PAGE_SHIFT) - 1;

		अगर (m_start <= start && end <= m_end)
			md->attribute |= m_attr;

		अगर (m_start <= start &&
		    (start < m_end && m_end < end)) अणु
			/* first part */
			md->attribute |= m_attr;
			md->num_pages = (m_end - md->phys_addr + 1) >>
				EFI_PAGE_SHIFT;
			/* latter part */
			new += old_memmap->desc_size;
			स_नकल(new, old, old_memmap->desc_size);
			md = new;
			md->phys_addr = m_end + 1;
			md->num_pages = (end - md->phys_addr + 1) >>
				EFI_PAGE_SHIFT;
		पूर्ण

		अगर ((start < m_start && m_start < end) && m_end < end) अणु
			/* first part */
			md->num_pages = (m_start - md->phys_addr) >>
				EFI_PAGE_SHIFT;
			/* middle part */
			new += old_memmap->desc_size;
			स_नकल(new, old, old_memmap->desc_size);
			md = new;
			md->attribute |= m_attr;
			md->phys_addr = m_start;
			md->num_pages = (m_end - m_start + 1) >>
				EFI_PAGE_SHIFT;
			/* last part */
			new += old_memmap->desc_size;
			स_नकल(new, old, old_memmap->desc_size);
			md = new;
			md->phys_addr = m_end + 1;
			md->num_pages = (end - m_end) >>
				EFI_PAGE_SHIFT;
		पूर्ण

		अगर ((start < m_start && m_start < end) &&
		    (end <= m_end)) अणु
			/* first part */
			md->num_pages = (m_start - md->phys_addr) >>
				EFI_PAGE_SHIFT;
			/* latter part */
			new += old_memmap->desc_size;
			स_नकल(new, old, old_memmap->desc_size);
			md = new;
			md->phys_addr = m_start;
			md->num_pages = (end - md->phys_addr + 1) >>
				EFI_PAGE_SHIFT;
			md->attribute |= m_attr;
		पूर्ण
	पूर्ण
पूर्ण
