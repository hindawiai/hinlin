<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/******************************************************************************
 * Xen memory reservation utilities.
 *
 * Copyright (c) 2003, B Dragovic
 * Copyright (c) 2003-2004, M Williamson, K Fraser
 * Copyright (c) 2005 Dan M. Smith, IBM Corporation
 * Copyright (c) 2010 Daniel Kiper
 * Copyright (c) 2018 Oleksandr Andrushchenko, EPAM Systems Inc.
 */

#समावेश <यंत्र/xen/hypercall.h>

#समावेश <xen/पूर्णांकerface/memory.h>
#समावेश <xen/mem-reservation.h>
#समावेश <linux/moduleparam.h>

bool __पढ़ो_mostly xen_scrub_pages = IS_ENABLED(CONFIG_XEN_SCRUB_PAGES_DEFAULT);
core_param(xen_scrub_pages, xen_scrub_pages, bool, 0);

/*
 * Use one extent per PAGE_SIZE to aव्योम to अवरोध करोwn the page पूर्णांकo
 * multiple frame.
 */
#घोषणा EXTENT_ORDER (fls(XEN_PFN_PER_PAGE) - 1)

#अगर_घोषित CONFIG_XEN_HAVE_PVMMU
व्योम __xenmem_reservation_va_mapping_update(अचिन्हित दीर्घ count,
					    काष्ठा page **pages,
					    xen_pfn_t *frames)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा page *page = pages[i];
		अचिन्हित दीर्घ pfn = page_to_pfn(page);

		BUG_ON(!page);

		/*
		 * We करोn't support PV MMU when Linux and Xen is using
		 * dअगरferent page granularity.
		 */
		BUILD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

		set_phys_to_machine(pfn, frames[i]);

		/* Link back पूर्णांकo the page tables अगर not highmem. */
		अगर (!PageHighMem(page)) अणु
			पूर्णांक ret;

			ret = HYPERVISOR_update_va_mapping(
					(अचिन्हित दीर्घ)__va(pfn << PAGE_SHIFT),
					mfn_pte(frames[i], PAGE_KERNEL),
					0);
			BUG_ON(ret);
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__xenmem_reservation_va_mapping_update);

व्योम __xenmem_reservation_va_mapping_reset(अचिन्हित दीर्घ count,
					   काष्ठा page **pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++) अणु
		काष्ठा page *page = pages[i];
		अचिन्हित दीर्घ pfn = page_to_pfn(page);

		/*
		 * We करोn't support PV MMU when Linux and Xen are using
		 * dअगरferent page granularity.
		 */
		BUILD_BUG_ON(XEN_PAGE_SIZE != PAGE_SIZE);

		अगर (!PageHighMem(page)) अणु
			पूर्णांक ret;

			ret = HYPERVISOR_update_va_mapping(
					(अचिन्हित दीर्घ)__va(pfn << PAGE_SHIFT),
					__pte_ma(0), 0);
			BUG_ON(ret);
		पूर्ण
		__set_phys_to_machine(pfn, INVALID_P2M_ENTRY);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(__xenmem_reservation_va_mapping_reset);
#पूर्ण_अगर /* CONFIG_XEN_HAVE_PVMMU */

/* @frames is an array of PFNs */
पूर्णांक xenmem_reservation_increase(पूर्णांक count, xen_pfn_t *frames)
अणु
	काष्ठा xen_memory_reservation reservation = अणु
		.address_bits = 0,
		.extent_order = EXTENT_ORDER,
		.करोmid        = DOMID_SELF
	पूर्ण;

	/* XENMEM_populate_physmap requires a PFN based on Xen granularity. */
	set_xen_guest_handle(reservation.extent_start, frames);
	reservation.nr_extents = count;
	वापस HYPERVISOR_memory_op(XENMEM_populate_physmap, &reservation);
पूर्ण
EXPORT_SYMBOL_GPL(xenmem_reservation_increase);

/* @frames is an array of GFNs */
पूर्णांक xenmem_reservation_decrease(पूर्णांक count, xen_pfn_t *frames)
अणु
	काष्ठा xen_memory_reservation reservation = अणु
		.address_bits = 0,
		.extent_order = EXTENT_ORDER,
		.करोmid        = DOMID_SELF
	पूर्ण;

	/* XENMEM_decrease_reservation requires a GFN */
	set_xen_guest_handle(reservation.extent_start, frames);
	reservation.nr_extents = count;
	वापस HYPERVISOR_memory_op(XENMEM_decrease_reservation, &reservation);
पूर्ण
EXPORT_SYMBOL_GPL(xenmem_reservation_decrease);
