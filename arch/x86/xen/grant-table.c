<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/******************************************************************************
 * grant_table.c
 * x86 specअगरic part
 *
 * Granting क्रमeign access to our memory reservation.
 *
 * Copyright (c) 2005-2006, Christopher Clark
 * Copyright (c) 2004-2005, K A Fraser
 * Copyright (c) 2008 Isaku Yamahata <yamahata at valinux co jp>
 *                    VA Linux Systems Japan. Split out x86 specअगरic part.
 */

#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <xen/पूर्णांकerface/xen.h>
#समावेश <xen/page.h>
#समावेश <xen/grant_table.h>
#समावेश <xen/xen.h>


अटल काष्ठा gnttab_vm_area अणु
	काष्ठा vm_काष्ठा *area;
	pte_t **ptes;
	पूर्णांक idx;
पूर्ण gnttab_shared_vm_area, gnttab_status_vm_area;

पूर्णांक arch_gnttab_map_shared(अचिन्हित दीर्घ *frames, अचिन्हित दीर्घ nr_gframes,
			   अचिन्हित दीर्घ max_nr_gframes,
			   व्योम **__shared)
अणु
	व्योम *shared = *__shared;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ i;

	अगर (shared == शून्य)
		*__shared = shared = gnttab_shared_vm_area.area->addr;

	addr = (अचिन्हित दीर्घ)shared;

	क्रम (i = 0; i < nr_gframes; i++) अणु
		set_pte_at(&init_mm, addr, gnttab_shared_vm_area.ptes[i],
			   mfn_pte(frames[i], PAGE_KERNEL));
		addr += PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक arch_gnttab_map_status(uपूर्णांक64_t *frames, अचिन्हित दीर्घ nr_gframes,
			   अचिन्हित दीर्घ max_nr_gframes,
			   grant_status_t **__shared)
अणु
	grant_status_t *shared = *__shared;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ i;

	अगर (shared == शून्य)
		*__shared = shared = gnttab_status_vm_area.area->addr;

	addr = (अचिन्हित दीर्घ)shared;

	क्रम (i = 0; i < nr_gframes; i++) अणु
		set_pte_at(&init_mm, addr, gnttab_status_vm_area.ptes[i],
			   mfn_pte(frames[i], PAGE_KERNEL));
		addr += PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

व्योम arch_gnttab_unmap(व्योम *shared, अचिन्हित दीर्घ nr_gframes)
अणु
	pte_t **ptes;
	अचिन्हित दीर्घ addr;
	अचिन्हित दीर्घ i;

	अगर (shared == gnttab_status_vm_area.area->addr)
		ptes = gnttab_status_vm_area.ptes;
	अन्यथा
		ptes = gnttab_shared_vm_area.ptes;

	addr = (अचिन्हित दीर्घ)shared;

	क्रम (i = 0; i < nr_gframes; i++) अणु
		set_pte_at(&init_mm, addr, ptes[i], __pte(0));
		addr += PAGE_SIZE;
	पूर्ण
पूर्ण

अटल पूर्णांक gnttab_apply(pte_t *pte, अचिन्हित दीर्घ addr, व्योम *data)
अणु
	काष्ठा gnttab_vm_area *area = data;

	area->ptes[area->idx++] = pte;
	वापस 0;
पूर्ण

अटल पूर्णांक arch_gnttab_valloc(काष्ठा gnttab_vm_area *area, अचिन्हित nr_frames)
अणु
	area->ptes = kदो_स्मृति_array(nr_frames, माप(*area->ptes), GFP_KERNEL);
	अगर (area->ptes == शून्य)
		वापस -ENOMEM;
	area->area = get_vm_area(PAGE_SIZE * nr_frames, VM_IOREMAP);
	अगर (!area->area)
		जाओ out_मुक्त_ptes;
	अगर (apply_to_page_range(&init_mm, (अचिन्हित दीर्घ)area->area->addr,
			PAGE_SIZE * nr_frames, gnttab_apply, area))
		जाओ out_मुक्त_vm_area;
	वापस 0;
out_मुक्त_vm_area:
	मुक्त_vm_area(area->area);
out_मुक्त_ptes:
	kमुक्त(area->ptes);
	वापस -ENOMEM;
पूर्ण

अटल व्योम arch_gnttab_vमुक्त(काष्ठा gnttab_vm_area *area)
अणु
	मुक्त_vm_area(area->area);
	kमुक्त(area->ptes);
पूर्ण

पूर्णांक arch_gnttab_init(अचिन्हित दीर्घ nr_shared, अचिन्हित दीर्घ nr_status)
अणु
	पूर्णांक ret;

	अगर (!xen_pv_करोमुख्य())
		वापस 0;

	ret = arch_gnttab_valloc(&gnttab_shared_vm_area, nr_shared);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Always allocate the space क्रम the status frames in हाल
	 * we're migrated to a host with V2 support.
	 */
	ret = arch_gnttab_valloc(&gnttab_status_vm_area, nr_status);
	अगर (ret < 0)
		जाओ err;

	वापस 0;
err:
	arch_gnttab_vमुक्त(&gnttab_shared_vm_area);
	वापस -ENOMEM;
पूर्ण

#अगर_घोषित CONFIG_XEN_PVH
#समावेश <xen/events.h>
#समावेश <xen/xen-ops.h>
अटल पूर्णांक __init xen_pvh_gnttab_setup(व्योम)
अणु
	अगर (!xen_pvh_करोमुख्य())
		वापस -ENODEV;

	xen_स्वतः_xlat_grant_frames.count = gnttab_max_grant_frames();

	वापस xen_xlate_map_ballooned_pages(&xen_स्वतः_xlat_grant_frames.pfn,
					     &xen_स्वतः_xlat_grant_frames.vaddr,
					     xen_स्वतः_xlat_grant_frames.count);
पूर्ण
/* Call it _beक्रमe_ __gnttab_init as we need to initialize the
 * xen_स्वतः_xlat_grant_frames first. */
core_initcall(xen_pvh_gnttab_setup);
#पूर्ण_अगर
