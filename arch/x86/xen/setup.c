<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Machine specअगरic setup क्रम xen
 *
 * Jeremy Fitzhardinge <jeremy@xensource.com>, XenSource Inc, 2007
 */

#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/pm.h>
#समावेश <linux/memblock.h>
#समावेश <linux/cpuidle.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/memory_hotplug.h>

#समावेश <यंत्र/elf.h>
#समावेश <यंत्र/vdso.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/acpi.h>
#समावेश <यंत्र/numa.h>
#समावेश <यंत्र/idtentry.h>
#समावेश <यंत्र/xen/hypervisor.h>
#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/पूर्णांकerface/callback.h>
#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/पूर्णांकerface/physdev.h>
#समावेश <xen/features.h>
#समावेश <xen/hvc-console.h>
#समावेश "xen-ops.h"
#समावेश "mmu.h"

#घोषणा GB(x) ((uपूर्णांक64_t)(x) * 1024 * 1024 * 1024)

/* Amount of extra memory space we add to the e820 ranges */
काष्ठा xen_memory_region xen_extra_mem[XEN_EXTRA_MEM_MAX_REGIONS] __initdata;

/* Number of pages released from the initial allocation. */
अचिन्हित दीर्घ xen_released_pages;

/* E820 map used during setting up memory. */
अटल काष्ठा e820_table xen_e820_table __initdata;

/*
 * Buffer used to remap identity mapped pages. We only need the भव space.
 * The physical page behind this address is remapped as needed to dअगरferent
 * buffer pages.
 */
#घोषणा REMAP_SIZE	(P2M_PER_PAGE - 3)
अटल काष्ठा अणु
	अचिन्हित दीर्घ	next_area_mfn;
	अचिन्हित दीर्घ	target_pfn;
	अचिन्हित दीर्घ	size;
	अचिन्हित दीर्घ	mfns[REMAP_SIZE];
पूर्ण xen_remap_buf __initdata __aligned(PAGE_SIZE);
अटल अचिन्हित दीर्घ xen_remap_mfn __initdata = INVALID_P2M_ENTRY;

/*
 * The maximum amount of extra memory compared to the base size.  The
 * मुख्य scaling factor is the size of काष्ठा page.  At extreme ratios
 * of base:extra, all the base memory can be filled with page
 * काष्ठाures क्रम the extra memory, leaving no space क्रम anything
 * अन्यथा.
 *
 * 10x seems like a reasonable balance between scaling flexibility and
 * leaving a practically usable प्रणाली.
 */
#घोषणा EXTRA_MEM_RATIO		(10)

अटल bool xen_512gb_limit __initdata = IS_ENABLED(CONFIG_XEN_512GB);

अटल व्योम __init xen_parse_512gb(व्योम)
अणु
	bool val = false;
	अक्षर *arg;

	arg = म_माला(xen_start_info->cmd_line, "xen_512gb_limit");
	अगर (!arg)
		वापस;

	arg = म_माला(xen_start_info->cmd_line, "xen_512gb_limit=");
	अगर (!arg)
		val = true;
	अन्यथा अगर (strtobool(arg + म_माप("xen_512gb_limit="), &val))
		वापस;

	xen_512gb_limit = val;
पूर्ण

अटल व्योम __init xen_add_extra_mem(अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ n_pfns)
अणु
	पूर्णांक i;

	/*
	 * No need to check क्रम zero size, should happen rarely and will only
	 * ग_लिखो a new entry regarded to be unused due to zero size.
	 */
	क्रम (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++) अणु
		/* Add new region. */
		अगर (xen_extra_mem[i].n_pfns == 0) अणु
			xen_extra_mem[i].start_pfn = start_pfn;
			xen_extra_mem[i].n_pfns = n_pfns;
			अवरोध;
		पूर्ण
		/* Append to existing region. */
		अगर (xen_extra_mem[i].start_pfn + xen_extra_mem[i].n_pfns ==
		    start_pfn) अणु
			xen_extra_mem[i].n_pfns += n_pfns;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i == XEN_EXTRA_MEM_MAX_REGIONS)
		prपूर्णांकk(KERN_WARNING "Warning: not enough extra memory regions\n");

	memblock_reserve(PFN_PHYS(start_pfn), PFN_PHYS(n_pfns));
पूर्ण

अटल व्योम __init xen_del_extra_mem(अचिन्हित दीर्घ start_pfn,
				     अचिन्हित दीर्घ n_pfns)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ start_r, size_r;

	क्रम (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++) अणु
		start_r = xen_extra_mem[i].start_pfn;
		size_r = xen_extra_mem[i].n_pfns;

		/* Start of region. */
		अगर (start_r == start_pfn) अणु
			BUG_ON(n_pfns > size_r);
			xen_extra_mem[i].start_pfn += n_pfns;
			xen_extra_mem[i].n_pfns -= n_pfns;
			अवरोध;
		पूर्ण
		/* End of region. */
		अगर (start_r + size_r == start_pfn + n_pfns) अणु
			BUG_ON(n_pfns > size_r);
			xen_extra_mem[i].n_pfns -= n_pfns;
			अवरोध;
		पूर्ण
		/* Mid of region. */
		अगर (start_pfn > start_r && start_pfn < start_r + size_r) अणु
			BUG_ON(start_pfn + n_pfns > start_r + size_r);
			xen_extra_mem[i].n_pfns = start_pfn - start_r;
			/* Calling memblock_reserve() again is okay. */
			xen_add_extra_mem(start_pfn + n_pfns, start_r + size_r -
					  (start_pfn + n_pfns));
			अवरोध;
		पूर्ण
	पूर्ण
	memblock_मुक्त(PFN_PHYS(start_pfn), PFN_PHYS(n_pfns));
पूर्ण

/*
 * Called during boot beक्रमe the p2m list can take entries beyond the
 * hypervisor supplied p2m list. Entries in extra mem are to be regarded as
 * invalid.
 */
अचिन्हित दीर्घ __ref xen_chk_extra_mem(अचिन्हित दीर्घ pfn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++) अणु
		अगर (pfn >= xen_extra_mem[i].start_pfn &&
		    pfn < xen_extra_mem[i].start_pfn + xen_extra_mem[i].n_pfns)
			वापस INVALID_P2M_ENTRY;
	पूर्ण

	वापस IDENTITY_FRAME(pfn);
पूर्ण

/*
 * Mark all pfns of extra mem as invalid in p2m list.
 */
व्योम __init xen_inv_extra_mem(व्योम)
अणु
	अचिन्हित दीर्घ pfn, pfn_s, pfn_e;
	पूर्णांक i;

	क्रम (i = 0; i < XEN_EXTRA_MEM_MAX_REGIONS; i++) अणु
		अगर (!xen_extra_mem[i].n_pfns)
			जारी;
		pfn_s = xen_extra_mem[i].start_pfn;
		pfn_e = pfn_s + xen_extra_mem[i].n_pfns;
		क्रम (pfn = pfn_s; pfn < pfn_e; pfn++)
			set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
	पूर्ण
पूर्ण

/*
 * Finds the next RAM pfn available in the E820 map after min_pfn.
 * This function updates min_pfn with the pfn found and वापसs
 * the size of that range or zero अगर not found.
 */
अटल अचिन्हित दीर्घ __init xen_find_pfn_range(अचिन्हित दीर्घ *min_pfn)
अणु
	स्थिर काष्ठा e820_entry *entry = xen_e820_table.entries;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ करोne = 0;

	क्रम (i = 0; i < xen_e820_table.nr_entries; i++, entry++) अणु
		अचिन्हित दीर्घ s_pfn;
		अचिन्हित दीर्घ e_pfn;

		अगर (entry->type != E820_TYPE_RAM)
			जारी;

		e_pfn = PFN_DOWN(entry->addr + entry->size);

		/* We only care about E820 after this */
		अगर (e_pfn <= *min_pfn)
			जारी;

		s_pfn = PFN_UP(entry->addr);

		/* If min_pfn falls within the E820 entry, we want to start
		 * at the min_pfn PFN.
		 */
		अगर (s_pfn <= *min_pfn) अणु
			करोne = e_pfn - *min_pfn;
		पूर्ण अन्यथा अणु
			करोne = e_pfn - s_pfn;
			*min_pfn = s_pfn;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस करोne;
पूर्ण

अटल पूर्णांक __init xen_मुक्त_mfn(अचिन्हित दीर्घ mfn)
अणु
	काष्ठा xen_memory_reservation reservation = अणु
		.address_bits = 0,
		.extent_order = 0,
		.करोmid        = DOMID_SELF
	पूर्ण;

	set_xen_guest_handle(reservation.extent_start, &mfn);
	reservation.nr_extents = 1;

	वापस HYPERVISOR_memory_op(XENMEM_decrease_reservation, &reservation);
पूर्ण

/*
 * This releases a chunk of memory and then करोes the identity map. It's used
 * as a fallback अगर the remapping fails.
 */
अटल व्योम __init xen_set_identity_and_release_chunk(अचिन्हित दीर्घ start_pfn,
			अचिन्हित दीर्घ end_pfn, अचिन्हित दीर्घ nr_pages)
अणु
	अचिन्हित दीर्घ pfn, end;
	पूर्णांक ret;

	WARN_ON(start_pfn > end_pfn);

	/* Release pages first. */
	end = min(end_pfn, nr_pages);
	क्रम (pfn = start_pfn; pfn < end; pfn++) अणु
		अचिन्हित दीर्घ mfn = pfn_to_mfn(pfn);

		/* Make sure pfn exists to start with */
		अगर (mfn == INVALID_P2M_ENTRY || mfn_to_pfn(mfn) != pfn)
			जारी;

		ret = xen_मुक्त_mfn(mfn);
		WARN(ret != 1, "Failed to release pfn %lx err=%d\n", pfn, ret);

		अगर (ret == 1) अणु
			xen_released_pages++;
			अगर (!__set_phys_to_machine(pfn, INVALID_P2M_ENTRY))
				अवरोध;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण

	set_phys_range_identity(start_pfn, end_pfn);
पूर्ण

/*
 * Helper function to update the p2m and m2p tables and kernel mapping.
 */
अटल व्योम __init xen_update_mem_tables(अचिन्हित दीर्घ pfn, अचिन्हित दीर्घ mfn)
अणु
	काष्ठा mmu_update update = अणु
		.ptr = ((uपूर्णांक64_t)mfn << PAGE_SHIFT) | MMU_MACHPHYS_UPDATE,
		.val = pfn
	पूर्ण;

	/* Update p2m */
	अगर (!set_phys_to_machine(pfn, mfn)) अणु
		WARN(1, "Failed to set p2m mapping for pfn=%ld mfn=%ld\n",
		     pfn, mfn);
		BUG();
	पूर्ण

	/* Update m2p */
	अगर (HYPERVISOR_mmu_update(&update, 1, शून्य, DOMID_SELF) < 0) अणु
		WARN(1, "Failed to set m2p mapping for mfn=%ld pfn=%ld\n",
		     mfn, pfn);
		BUG();
	पूर्ण

	/* Update kernel mapping, but not क्रम highmem. */
	अगर (pfn >= PFN_UP(__pa(high_memory - 1)))
		वापस;

	अगर (HYPERVISOR_update_va_mapping((अचिन्हित दीर्घ)__va(pfn << PAGE_SHIFT),
					 mfn_pte(mfn, PAGE_KERNEL), 0)) अणु
		WARN(1, "Failed to update kernel mapping for mfn=%ld pfn=%ld\n",
		      mfn, pfn);
		BUG();
	पूर्ण
पूर्ण

/*
 * This function updates the p2m and m2p tables with an identity map from
 * start_pfn to start_pfn+size and prepares remapping the underlying RAM of the
 * original allocation at remap_pfn. The inक्रमmation needed क्रम remapping is
 * saved in the memory itself to aव्योम the need क्रम allocating buffers. The
 * complete remap inक्रमmation is contained in a list of MFNs each containing
 * up to REMAP_SIZE MFNs and the start target PFN क्रम करोing the remap.
 * This enables us to preserve the original mfn sequence जबतक करोing the
 * remapping at a समय when the memory management is capable of allocating
 * भव and physical memory in arbitrary amounts, see 'xen_remap_memory' and
 * its callers.
 */
अटल व्योम __init xen_करो_set_identity_and_remap_chunk(
        अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ size, अचिन्हित दीर्घ remap_pfn)
अणु
	अचिन्हित दीर्घ buf = (अचिन्हित दीर्घ)&xen_remap_buf;
	अचिन्हित दीर्घ mfn_save, mfn;
	अचिन्हित दीर्घ ident_pfn_iter, remap_pfn_iter;
	अचिन्हित दीर्घ ident_end_pfn = start_pfn + size;
	अचिन्हित दीर्घ left = size;
	अचिन्हित पूर्णांक i, chunk;

	WARN_ON(size == 0);

	mfn_save = virt_to_mfn(buf);

	क्रम (ident_pfn_iter = start_pfn, remap_pfn_iter = remap_pfn;
	     ident_pfn_iter < ident_end_pfn;
	     ident_pfn_iter += REMAP_SIZE, remap_pfn_iter += REMAP_SIZE) अणु
		chunk = (left < REMAP_SIZE) ? left : REMAP_SIZE;

		/* Map first pfn to xen_remap_buf */
		mfn = pfn_to_mfn(ident_pfn_iter);
		set_pte_mfn(buf, mfn, PAGE_KERNEL);

		/* Save mapping inक्रमmation in page */
		xen_remap_buf.next_area_mfn = xen_remap_mfn;
		xen_remap_buf.target_pfn = remap_pfn_iter;
		xen_remap_buf.size = chunk;
		क्रम (i = 0; i < chunk; i++)
			xen_remap_buf.mfns[i] = pfn_to_mfn(ident_pfn_iter + i);

		/* Put remap buf पूर्णांकo list. */
		xen_remap_mfn = mfn;

		/* Set identity map */
		set_phys_range_identity(ident_pfn_iter, ident_pfn_iter + chunk);

		left -= chunk;
	पूर्ण

	/* Restore old xen_remap_buf mapping */
	set_pte_mfn(buf, mfn_save, PAGE_KERNEL);
पूर्ण

/*
 * This function takes a contiguous pfn range that needs to be identity mapped
 * and:
 *
 *  1) Finds a new range of pfns to use to remap based on E820 and remap_pfn.
 *  2) Calls the करो_ function to actually करो the mapping/remapping work.
 *
 * The goal is to not allocate additional memory but to remap the existing
 * pages. In the हाल of an error the underlying memory is simply released back
 * to Xen and not remapped.
 */
अटल अचिन्हित दीर्घ __init xen_set_identity_and_remap_chunk(
	अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn, अचिन्हित दीर्घ nr_pages,
	अचिन्हित दीर्घ remap_pfn)
अणु
	अचिन्हित दीर्घ pfn;
	अचिन्हित दीर्घ i = 0;
	अचिन्हित दीर्घ n = end_pfn - start_pfn;

	अगर (remap_pfn == 0)
		remap_pfn = nr_pages;

	जबतक (i < n) अणु
		अचिन्हित दीर्घ cur_pfn = start_pfn + i;
		अचिन्हित दीर्घ left = n - i;
		अचिन्हित दीर्घ size = left;
		अचिन्हित दीर्घ remap_range_size;

		/* Do not remap pages beyond the current allocation */
		अगर (cur_pfn >= nr_pages) अणु
			/* Identity map reमुख्यing pages */
			set_phys_range_identity(cur_pfn, cur_pfn + size);
			अवरोध;
		पूर्ण
		अगर (cur_pfn + size > nr_pages)
			size = nr_pages - cur_pfn;

		remap_range_size = xen_find_pfn_range(&remap_pfn);
		अगर (!remap_range_size) अणु
			pr_warn("Unable to find available pfn range, not remapping identity pages\n");
			xen_set_identity_and_release_chunk(cur_pfn,
						cur_pfn + left, nr_pages);
			अवरोध;
		पूर्ण
		/* Adjust size to fit in current e820 RAM region */
		अगर (size > remap_range_size)
			size = remap_range_size;

		xen_करो_set_identity_and_remap_chunk(cur_pfn, size, remap_pfn);

		/* Update variables to reflect new mappings. */
		i += size;
		remap_pfn += size;
	पूर्ण

	/*
	 * If the PFNs are currently mapped, the VA mapping also needs
	 * to be updated to be 1:1.
	 */
	क्रम (pfn = start_pfn; pfn <= max_pfn_mapped && pfn < end_pfn; pfn++)
		(व्योम)HYPERVISOR_update_va_mapping(
			(अचिन्हित दीर्घ)__va(pfn << PAGE_SHIFT),
			mfn_pte(pfn, PAGE_KERNEL_IO), 0);

	वापस remap_pfn;
पूर्ण

अटल अचिन्हित दीर्घ __init xen_count_remap_pages(
	अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn, अचिन्हित दीर्घ nr_pages,
	अचिन्हित दीर्घ remap_pages)
अणु
	अगर (start_pfn >= nr_pages)
		वापस remap_pages;

	वापस remap_pages + min(end_pfn, nr_pages) - start_pfn;
पूर्ण

अटल अचिन्हित दीर्घ __init xen_क्रमeach_remap_area(अचिन्हित दीर्घ nr_pages,
	अचिन्हित दीर्घ (*func)(अचिन्हित दीर्घ start_pfn, अचिन्हित दीर्घ end_pfn,
			      अचिन्हित दीर्घ nr_pages, अचिन्हित दीर्घ last_val))
अणु
	phys_addr_t start = 0;
	अचिन्हित दीर्घ ret_val = 0;
	स्थिर काष्ठा e820_entry *entry = xen_e820_table.entries;
	पूर्णांक i;

	/*
	 * Combine non-RAM regions and gaps until a RAM region (or the
	 * end of the map) is reached, then call the provided function
	 * to perक्रमm its duty on the non-RAM region.
	 *
	 * The combined non-RAM regions are rounded to a whole number
	 * of pages so any partial pages are accessible via the 1:1
	 * mapping.  This is needed क्रम some BIOSes that put (क्रम
	 * example) the DMI tables in a reserved region that begins on
	 * a non-page boundary.
	 */
	क्रम (i = 0; i < xen_e820_table.nr_entries; i++, entry++) अणु
		phys_addr_t end = entry->addr + entry->size;
		अगर (entry->type == E820_TYPE_RAM || i == xen_e820_table.nr_entries - 1) अणु
			अचिन्हित दीर्घ start_pfn = PFN_DOWN(start);
			अचिन्हित दीर्घ end_pfn = PFN_UP(end);

			अगर (entry->type == E820_TYPE_RAM)
				end_pfn = PFN_UP(entry->addr);

			अगर (start_pfn < end_pfn)
				ret_val = func(start_pfn, end_pfn, nr_pages,
					       ret_val);
			start = end;
		पूर्ण
	पूर्ण

	वापस ret_val;
पूर्ण

/*
 * Remap the memory prepared in xen_करो_set_identity_and_remap_chunk().
 * The remap inक्रमmation (which mfn remap to which pfn) is contained in the
 * to be remapped memory itself in a linked list anchored at xen_remap_mfn.
 * This scheme allows to remap the dअगरferent chunks in arbitrary order जबतक
 * the resulting mapping will be independent from the order.
 */
व्योम __init xen_remap_memory(व्योम)
अणु
	अचिन्हित दीर्घ buf = (अचिन्हित दीर्घ)&xen_remap_buf;
	अचिन्हित दीर्घ mfn_save, pfn;
	अचिन्हित दीर्घ remapped = 0;
	अचिन्हित पूर्णांक i;
	अचिन्हित दीर्घ pfn_s = ~0UL;
	अचिन्हित दीर्घ len = 0;

	mfn_save = virt_to_mfn(buf);

	जबतक (xen_remap_mfn != INVALID_P2M_ENTRY) अणु
		/* Map the remap inक्रमmation */
		set_pte_mfn(buf, xen_remap_mfn, PAGE_KERNEL);

		BUG_ON(xen_remap_mfn != xen_remap_buf.mfns[0]);

		pfn = xen_remap_buf.target_pfn;
		क्रम (i = 0; i < xen_remap_buf.size; i++) अणु
			xen_update_mem_tables(pfn, xen_remap_buf.mfns[i]);
			remapped++;
			pfn++;
		पूर्ण
		अगर (pfn_s == ~0UL || pfn == pfn_s) अणु
			pfn_s = xen_remap_buf.target_pfn;
			len += xen_remap_buf.size;
		पूर्ण अन्यथा अगर (pfn_s + len == xen_remap_buf.target_pfn) अणु
			len += xen_remap_buf.size;
		पूर्ण अन्यथा अणु
			xen_del_extra_mem(pfn_s, len);
			pfn_s = xen_remap_buf.target_pfn;
			len = xen_remap_buf.size;
		पूर्ण
		xen_remap_mfn = xen_remap_buf.next_area_mfn;
	पूर्ण

	अगर (pfn_s != ~0UL && len)
		xen_del_extra_mem(pfn_s, len);

	set_pte_mfn(buf, mfn_save, PAGE_KERNEL);

	pr_info("Remapped %ld page(s)\n", remapped);
पूर्ण

अटल अचिन्हित दीर्घ __init xen_get_pages_limit(व्योम)
अणु
	अचिन्हित दीर्घ limit;

	limit = MAXMEM / PAGE_SIZE;
	अगर (!xen_initial_करोमुख्य() && xen_512gb_limit)
		limit = GB(512) / PAGE_SIZE;

	वापस limit;
पूर्ण

अटल अचिन्हित दीर्घ __init xen_get_max_pages(व्योम)
अणु
	अचिन्हित दीर्घ max_pages, limit;
	करोmid_t करोmid = DOMID_SELF;
	दीर्घ ret;

	limit = xen_get_pages_limit();
	max_pages = limit;

	/*
	 * For the initial करोमुख्य we use the maximum reservation as
	 * the maximum page.
	 *
	 * For guest करोमुख्यs the current maximum reservation reflects
	 * the current maximum rather than the अटल maximum. In this
	 * हाल the e820 map provided to us will cover the अटल
	 * maximum region.
	 */
	अगर (xen_initial_करोमुख्य()) अणु
		ret = HYPERVISOR_memory_op(XENMEM_maximum_reservation, &करोmid);
		अगर (ret > 0)
			max_pages = ret;
	पूर्ण

	वापस min(max_pages, limit);
पूर्ण

अटल व्योम __init xen_align_and_add_e820_region(phys_addr_t start,
						 phys_addr_t size, पूर्णांक type)
अणु
	phys_addr_t end = start + size;

	/* Align RAM regions to page boundaries. */
	अगर (type == E820_TYPE_RAM) अणु
		start = PAGE_ALIGN(start);
		end &= ~((phys_addr_t)PAGE_SIZE - 1);
#अगर_घोषित CONFIG_MEMORY_HOTPLUG
		/*
		 * Don't allow adding memory not in E820 map जबतक booting the
		 * प्रणाली. Once the balloon driver is up it will हटाओ that
		 * restriction again.
		 */
		max_mem_size = end;
#पूर्ण_अगर
	पूर्ण

	e820__range_add(start, end - start, type);
पूर्ण

अटल व्योम __init xen_ignore_unusable(व्योम)
अणु
	काष्ठा e820_entry *entry = xen_e820_table.entries;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < xen_e820_table.nr_entries; i++, entry++) अणु
		अगर (entry->type == E820_TYPE_UNUSABLE)
			entry->type = E820_TYPE_RAM;
	पूर्ण
पूर्ण

bool __init xen_is_e820_reserved(phys_addr_t start, phys_addr_t size)
अणु
	काष्ठा e820_entry *entry;
	अचिन्हित mapcnt;
	phys_addr_t end;

	अगर (!size)
		वापस false;

	end = start + size;
	entry = xen_e820_table.entries;

	क्रम (mapcnt = 0; mapcnt < xen_e820_table.nr_entries; mapcnt++) अणु
		अगर (entry->type == E820_TYPE_RAM && entry->addr <= start &&
		    (entry->addr + entry->size) >= end)
			वापस false;

		entry++;
	पूर्ण

	वापस true;
पूर्ण

/*
 * Find a मुक्त area in physical memory not yet reserved and compliant with
 * E820 map.
 * Used to relocate pre-allocated areas like initrd or p2m list which are in
 * conflict with the to be used E820 map.
 * In हाल no area is found, वापस 0. Otherwise वापस the physical address
 * of the area which is alपढ़ोy reserved क्रम convenience.
 */
phys_addr_t __init xen_find_मुक्त_area(phys_addr_t size)
अणु
	अचिन्हित mapcnt;
	phys_addr_t addr, start;
	काष्ठा e820_entry *entry = xen_e820_table.entries;

	क्रम (mapcnt = 0; mapcnt < xen_e820_table.nr_entries; mapcnt++, entry++) अणु
		अगर (entry->type != E820_TYPE_RAM || entry->size < size)
			जारी;
		start = entry->addr;
		क्रम (addr = start; addr < start + size; addr += PAGE_SIZE) अणु
			अगर (!memblock_is_reserved(addr))
				जारी;
			start = addr + PAGE_SIZE;
			अगर (start + size > entry->addr + entry->size)
				अवरोध;
		पूर्ण
		अगर (addr >= start + size) अणु
			memblock_reserve(start, size);
			वापस start;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Like स_नकल, but with physical addresses क्रम dest and src.
 */
अटल व्योम __init xen_phys_स_नकल(phys_addr_t dest, phys_addr_t src,
				   phys_addr_t n)
अणु
	phys_addr_t dest_off, src_off, dest_len, src_len, len;
	व्योम *from, *to;

	जबतक (n) अणु
		dest_off = dest & ~PAGE_MASK;
		src_off = src & ~PAGE_MASK;
		dest_len = n;
		अगर (dest_len > (NR_FIX_BTMAPS << PAGE_SHIFT) - dest_off)
			dest_len = (NR_FIX_BTMAPS << PAGE_SHIFT) - dest_off;
		src_len = n;
		अगर (src_len > (NR_FIX_BTMAPS << PAGE_SHIFT) - src_off)
			src_len = (NR_FIX_BTMAPS << PAGE_SHIFT) - src_off;
		len = min(dest_len, src_len);
		to = early_memremap(dest - dest_off, dest_len + dest_off);
		from = early_memremap(src - src_off, src_len + src_off);
		स_नकल(to, from, len);
		early_memunmap(to, dest_len + dest_off);
		early_memunmap(from, src_len + src_off);
		n -= len;
		dest += len;
		src += len;
	पूर्ण
पूर्ण

/*
 * Reserve Xen mfn_list.
 */
अटल व्योम __init xen_reserve_xen_mfnlist(व्योम)
अणु
	phys_addr_t start, size;

	अगर (xen_start_info->mfn_list >= __START_KERNEL_map) अणु
		start = __pa(xen_start_info->mfn_list);
		size = PFN_ALIGN(xen_start_info->nr_pages *
				 माप(अचिन्हित दीर्घ));
	पूर्ण अन्यथा अणु
		start = PFN_PHYS(xen_start_info->first_p2m_pfn);
		size = PFN_PHYS(xen_start_info->nr_p2m_frames);
	पूर्ण

	memblock_reserve(start, size);
	अगर (!xen_is_e820_reserved(start, size))
		वापस;

	xen_relocate_p2m();
	memblock_मुक्त(start, size);
पूर्ण

/**
 * machine_specअगरic_memory_setup - Hook क्रम machine specअगरic memory setup.
 **/
अक्षर * __init xen_memory_setup(व्योम)
अणु
	अचिन्हित दीर्घ max_pfn, pfn_s, n_pfns;
	phys_addr_t mem_end, addr, size, chunk_size;
	u32 type;
	पूर्णांक rc;
	काष्ठा xen_memory_map memmap;
	अचिन्हित दीर्घ max_pages;
	अचिन्हित दीर्घ extra_pages = 0;
	पूर्णांक i;
	पूर्णांक op;

	xen_parse_512gb();
	max_pfn = xen_get_pages_limit();
	max_pfn = min(max_pfn, xen_start_info->nr_pages);
	mem_end = PFN_PHYS(max_pfn);

	memmap.nr_entries = ARRAY_SIZE(xen_e820_table.entries);
	set_xen_guest_handle(memmap.buffer, xen_e820_table.entries);

#अगर defined(CONFIG_MEMORY_HOTPLUG) && defined(CONFIG_XEN_BALLOON)
	xen_saved_max_mem_size = max_mem_size;
#पूर्ण_अगर

	op = xen_initial_करोमुख्य() ?
		XENMEM_machine_memory_map :
		XENMEM_memory_map;
	rc = HYPERVISOR_memory_op(op, &memmap);
	अगर (rc == -ENOSYS) अणु
		BUG_ON(xen_initial_करोमुख्य());
		memmap.nr_entries = 1;
		xen_e820_table.entries[0].addr = 0ULL;
		xen_e820_table.entries[0].size = mem_end;
		/* 8MB slack (to balance backend allocations). */
		xen_e820_table.entries[0].size += 8ULL << 20;
		xen_e820_table.entries[0].type = E820_TYPE_RAM;
		rc = 0;
	पूर्ण
	BUG_ON(rc);
	BUG_ON(memmap.nr_entries == 0);
	xen_e820_table.nr_entries = memmap.nr_entries;

	/*
	 * Xen won't allow a 1:1 mapping to be created to UNUSABLE
	 * regions, so अगर we're using the machine memory map leave the
	 * region as RAM as it is in the pseuकरो-physical map.
	 *
	 * UNUSABLE regions in करोmUs are not handled and will need
	 * a patch in the future.
	 */
	अगर (xen_initial_करोमुख्य())
		xen_ignore_unusable();

	/* Make sure the Xen-supplied memory map is well-ordered. */
	e820__update_table(&xen_e820_table);

	max_pages = xen_get_max_pages();

	/* How many extra pages करो we need due to remapping? */
	max_pages += xen_क्रमeach_remap_area(max_pfn, xen_count_remap_pages);

	अगर (max_pages > max_pfn)
		extra_pages += max_pages - max_pfn;

	/*
	 * Clamp the amount of extra memory to a EXTRA_MEM_RATIO
	 * factor the base size.
	 *
	 * Make sure we have no memory above max_pages, as this area
	 * isn't handled by the p2m management.
	 */
	extra_pages = min3(EXTRA_MEM_RATIO * min(max_pfn, PFN_DOWN(MAXMEM)),
			   extra_pages, max_pages - max_pfn);
	i = 0;
	addr = xen_e820_table.entries[0].addr;
	size = xen_e820_table.entries[0].size;
	जबतक (i < xen_e820_table.nr_entries) अणु
		bool discard = false;

		chunk_size = size;
		type = xen_e820_table.entries[i].type;

		अगर (type == E820_TYPE_RAM) अणु
			अगर (addr < mem_end) अणु
				chunk_size = min(size, mem_end - addr);
			पूर्ण अन्यथा अगर (extra_pages) अणु
				chunk_size = min(size, PFN_PHYS(extra_pages));
				pfn_s = PFN_UP(addr);
				n_pfns = PFN_DOWN(addr + chunk_size) - pfn_s;
				extra_pages -= n_pfns;
				xen_add_extra_mem(pfn_s, n_pfns);
				xen_max_p2m_pfn = pfn_s + n_pfns;
			पूर्ण अन्यथा
				discard = true;
		पूर्ण

		अगर (!discard)
			xen_align_and_add_e820_region(addr, chunk_size, type);

		addr += chunk_size;
		size -= chunk_size;
		अगर (size == 0) अणु
			i++;
			अगर (i < xen_e820_table.nr_entries) अणु
				addr = xen_e820_table.entries[i].addr;
				size = xen_e820_table.entries[i].size;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Set the rest as identity mapped, in हाल PCI BARs are
	 * located here.
	 */
	set_phys_range_identity(addr / PAGE_SIZE, ~0ul);

	/*
	 * In करोmU, the ISA region is normal, usable memory, but we
	 * reserve ISA memory anyway because too many things poke
	 * about in there.
	 */
	e820__range_add(ISA_START_ADDRESS, ISA_END_ADDRESS - ISA_START_ADDRESS, E820_TYPE_RESERVED);

	e820__update_table(e820_table);

	/*
	 * Check whether the kernel itself conflicts with the target E820 map.
	 * Failing now is better than running पूर्णांकo weird problems later due
	 * to relocating (and even reusing) pages with kernel text or data.
	 */
	अगर (xen_is_e820_reserved(__pa_symbol(_text),
			__pa_symbol(__bss_stop) - __pa_symbol(_text))) अणु
		xen_raw_console_ग_लिखो("Xen hypervisor allocated kernel memory conflicts with E820 map\n");
		BUG();
	पूर्ण

	/*
	 * Check क्रम a conflict of the hypervisor supplied page tables with
	 * the target E820 map.
	 */
	xen_pt_check_e820();

	xen_reserve_xen_mfnlist();

	/* Check क्रम a conflict of the initrd with the target E820 map. */
	अगर (xen_is_e820_reserved(boot_params.hdr.ramdisk_image,
				 boot_params.hdr.ramdisk_size)) अणु
		phys_addr_t new_area, start, size;

		new_area = xen_find_मुक्त_area(boot_params.hdr.ramdisk_size);
		अगर (!new_area) अणु
			xen_raw_console_ग_लिखो("Can't find new memory area for initrd needed due to E820 map conflict\n");
			BUG();
		पूर्ण

		start = boot_params.hdr.ramdisk_image;
		size = boot_params.hdr.ramdisk_size;
		xen_phys_स_नकल(new_area, start, size);
		pr_info("initrd moved from [mem %#010llx-%#010llx] to [mem %#010llx-%#010llx]\n",
			start, start + size, new_area, new_area + size);
		memblock_मुक्त(start, size);
		boot_params.hdr.ramdisk_image = new_area;
		boot_params.ext_ramdisk_image = new_area >> 32;
	पूर्ण

	/*
	 * Set identity map on non-RAM pages and prepare remapping the
	 * underlying RAM.
	 */
	xen_क्रमeach_remap_area(max_pfn, xen_set_identity_and_remap_chunk);

	pr_info("Released %ld page(s)\n", xen_released_pages);

	वापस "Xen";
पूर्ण

अटल पूर्णांक रेजिस्टर_callback(अचिन्हित type, स्थिर व्योम *func)
अणु
	काष्ठा callback_रेजिस्टर callback = अणु
		.type = type,
		.address = XEN_CALLBACK(__KERNEL_CS, func),
		.flags = CALLBACKF_mask_events,
	पूर्ण;

	वापस HYPERVISOR_callback_op(CALLBACKOP_रेजिस्टर, &callback);
पूर्ण

व्योम xen_enable_sysenter(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित sysenter_feature;

	sysenter_feature = X86_FEATURE_SYSENTER32;

	अगर (!boot_cpu_has(sysenter_feature))
		वापस;

	ret = रेजिस्टर_callback(CALLBACKTYPE_sysenter, xen_sysenter_target);
	अगर(ret != 0)
		setup_clear_cpu_cap(sysenter_feature);
पूर्ण

व्योम xen_enable_syscall(व्योम)
अणु
	पूर्णांक ret;

	ret = रेजिस्टर_callback(CALLBACKTYPE_syscall, xen_syscall_target);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to set syscall callback: %d\n", ret);
		/* Pretty fatal; 64-bit userspace has no other
		   mechanism क्रम syscalls. */
	पूर्ण

	अगर (boot_cpu_has(X86_FEATURE_SYSCALL32)) अणु
		ret = रेजिस्टर_callback(CALLBACKTYPE_syscall32,
					xen_syscall32_target);
		अगर (ret != 0)
			setup_clear_cpu_cap(X86_FEATURE_SYSCALL32);
	पूर्ण
पूर्ण

अटल व्योम __init xen_pvmmu_arch_setup(व्योम)
अणु
	HYPERVISOR_vm_assist(VMASST_CMD_enable, VMASST_TYPE_4gb_segments);
	HYPERVISOR_vm_assist(VMASST_CMD_enable, VMASST_TYPE_writable_pagetables);

	HYPERVISOR_vm_assist(VMASST_CMD_enable,
			     VMASST_TYPE_pae_extended_cr3);

	अगर (रेजिस्टर_callback(CALLBACKTYPE_event,
			      xen_यंत्र_exc_xen_hypervisor_callback) ||
	    रेजिस्टर_callback(CALLBACKTYPE_failsafe, xen_failsafe_callback))
		BUG();

	xen_enable_sysenter();
	xen_enable_syscall();
पूर्ण

/* This function is not called क्रम HVM करोमुख्यs */
व्योम __init xen_arch_setup(व्योम)
अणु
	xen_panic_handler_init();
	xen_pvmmu_arch_setup();

#अगर_घोषित CONFIG_ACPI
	अगर (!(xen_start_info->flags & SIF_INITDOMAIN)) अणु
		prपूर्णांकk(KERN_INFO "ACPI in unprivileged domain disabled\n");
		disable_acpi();
	पूर्ण
#पूर्ण_अगर

	स_नकल(boot_command_line, xen_start_info->cmd_line,
	       MAX_GUEST_CMDLINE > COMMAND_LINE_SIZE ?
	       COMMAND_LINE_SIZE : MAX_GUEST_CMDLINE);

	/* Set up idle, making sure it calls safe_halt() pvop */
	disable_cpuidle();
	disable_cpufreq();
	WARN_ON(xen_set_शेष_idle());
#अगर_घोषित CONFIG_NUMA
	numa_off = 1;
#पूर्ण_अगर
पूर्ण
