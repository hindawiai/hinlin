<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * BIOS run समय पूर्णांकerface routines.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 2007-2017 Silicon Graphics, Inc. All rights reserved.
 * Copyright (c) Russ Anderson <rja@sgi.com>
 */

#समावेश <linux/efi.h>
#समावेश <linux/export.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/efi.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/pgभाग.स>
#समावेश <यंत्र/uv/मूलप्रण.स>
#समावेश <यंत्र/uv/uv_hub.h>

अचिन्हित दीर्घ uv_systab_phys __ro_after_init = EFI_INVALID_TABLE_ADDR;

काष्ठा uv_systab *uv_systab;

अटल s64 __uv_bios_call(क्रमागत uv_bios_cmd which, u64 a1, u64 a2, u64 a3,
			u64 a4, u64 a5)
अणु
	काष्ठा uv_systab *tab = uv_systab;
	s64 ret;

	अगर (!tab || !tab->function)
		/*
		 * BIOS करोes not support UV systab
		 */
		वापस BIOS_STATUS_UNIMPLEMENTED;

	ret = efi_call_virt_poपूर्णांकer(tab, function, (u64)which, a1, a2, a3, a4, a5);

	वापस ret;
पूर्ण

अटल s64 uv_bios_call(क्रमागत uv_bios_cmd which, u64 a1, u64 a2, u64 a3, u64 a4,
		u64 a5)
अणु
	s64 ret;

	अगर (करोwn_पूर्णांकerruptible(&__efi_uv_runसमय_lock))
		वापस BIOS_STATUS_ABORT;

	ret = __uv_bios_call(which, a1, a2, a3, a4, a5);
	up(&__efi_uv_runसमय_lock);

	वापस ret;
पूर्ण

अटल s64 uv_bios_call_irqsave(क्रमागत uv_bios_cmd which, u64 a1, u64 a2, u64 a3,
		u64 a4, u64 a5)
अणु
	अचिन्हित दीर्घ bios_flags;
	s64 ret;

	अगर (करोwn_पूर्णांकerruptible(&__efi_uv_runसमय_lock))
		वापस BIOS_STATUS_ABORT;

	local_irq_save(bios_flags);
	ret = __uv_bios_call(which, a1, a2, a3, a4, a5);
	local_irq_restore(bios_flags);

	up(&__efi_uv_runसमय_lock);

	वापस ret;
पूर्ण

दीर्घ sn_partition_id;
EXPORT_SYMBOL_GPL(sn_partition_id);
दीर्घ sn_coherency_id;
EXPORT_SYMBOL_GPL(sn_coherency_id);
दीर्घ sn_region_size;
EXPORT_SYMBOL_GPL(sn_region_size);
दीर्घ प्रणाली_serial_number;
पूर्णांक uv_type;

s64 uv_bios_get_sn_info(पूर्णांक fc, पूर्णांक *uvtype, दीर्घ *partid, दीर्घ *coher,
		दीर्घ *region, दीर्घ *ssn)
अणु
	s64 ret;
	u64 v0, v1;
	जोड़ partition_info_u part;

	ret = uv_bios_call_irqsave(UV_BIOS_GET_SN_INFO, fc,
				(u64)(&v0), (u64)(&v1), 0, 0);
	अगर (ret != BIOS_STATUS_SUCCESS)
		वापस ret;

	part.val = v0;
	अगर (uvtype)
		*uvtype = part.hub_version;
	अगर (partid)
		*partid = part.partition_id;
	अगर (coher)
		*coher = part.coherence_id;
	अगर (region)
		*region = part.region_size;
	अगर (ssn)
		*ssn = v1;
	वापस ret;
पूर्ण

पूर्णांक
uv_bios_mq_watchlist_alloc(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक mq_size,
			   अचिन्हित दीर्घ *पूर्णांकr_mmr_offset)
अणु
	u64 watchlist;
	s64 ret;

	/*
	 * bios वापसs watchlist number or negative error number.
	 */
	ret = (पूर्णांक)uv_bios_call_irqsave(UV_BIOS_WATCHLIST_ALLOC, addr,
			mq_size, (u64)पूर्णांकr_mmr_offset,
			(u64)&watchlist, 0);
	अगर (ret < BIOS_STATUS_SUCCESS)
		वापस ret;

	वापस watchlist;
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_mq_watchlist_alloc);

पूर्णांक
uv_bios_mq_watchlist_मुक्त(पूर्णांक blade, पूर्णांक watchlist_num)
अणु
	वापस (पूर्णांक)uv_bios_call_irqsave(UV_BIOS_WATCHLIST_FREE,
				blade, watchlist_num, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_mq_watchlist_मुक्त);

s64
uv_bios_change_memprotect(u64 paddr, u64 len, क्रमागत uv_memprotect perms)
अणु
	वापस uv_bios_call_irqsave(UV_BIOS_MEMPROTECT, paddr, len,
					perms, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_change_memprotect);

s64
uv_bios_reserved_page_pa(u64 buf, u64 *cookie, u64 *addr, u64 *len)
अणु
	वापस uv_bios_call_irqsave(UV_BIOS_GET_PARTITION_ADDR, (u64)cookie,
				    (u64)addr, buf, (u64)len, 0);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_reserved_page_pa);

s64 uv_bios_freq_base(u64 घड़ी_प्रकारype, u64 *ticks_per_second)
अणु
	वापस uv_bios_call(UV_BIOS_FREQ_BASE, घड़ी_प्रकारype,
			   (u64)ticks_per_second, 0, 0, 0);
पूर्ण

/*
 * uv_bios_set_legacy_vga_target - Set Legacy VGA I/O Target
 * @decode: true to enable target, false to disable target
 * @करोमुख्य: PCI करोमुख्य number
 * @bus: PCI bus number
 *
 * Returns:
 *    0: Success
 *    -EINVAL: Invalid करोमुख्य or bus number
 *    -ENOSYS: Capability not available
 *    -EBUSY: Legacy VGA I/O cannot be retargeted at this समय
 */
पूर्णांक uv_bios_set_legacy_vga_target(bool decode, पूर्णांक करोमुख्य, पूर्णांक bus)
अणु
	वापस uv_bios_call(UV_BIOS_SET_LEGACY_VGA_TARGET,
				(u64)decode, (u64)करोमुख्य, (u64)bus, 0, 0);
पूर्ण

बाह्य s64 uv_bios_get_master_nasid(u64 size, u64 *master_nasid)
अणु
	वापस uv_bios_call(UV_BIOS_EXTRA, 0, UV_BIOS_EXTRA_MASTER_NASID, 0,
				size, (u64)master_nasid);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_get_master_nasid);

बाह्य s64 uv_bios_get_heapsize(u64 nasid, u64 size, u64 *heap_size)
अणु
	वापस uv_bios_call(UV_BIOS_EXTRA, nasid, UV_BIOS_EXTRA_GET_HEAPSIZE,
				0, size, (u64)heap_size);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_get_heapsize);

बाह्य s64 uv_bios_install_heap(u64 nasid, u64 heap_size, u64 *bios_heap)
अणु
	वापस uv_bios_call(UV_BIOS_EXTRA, nasid, UV_BIOS_EXTRA_INSTALL_HEAP,
				0, heap_size, (u64)bios_heap);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_install_heap);

बाह्य s64 uv_bios_obj_count(u64 nasid, u64 size, u64 *objcnt)
अणु
	वापस uv_bios_call(UV_BIOS_EXTRA, nasid, UV_BIOS_EXTRA_OBJECT_COUNT,
				0, size, (u64)objcnt);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_obj_count);

बाह्य s64 uv_bios_क्रमागत_objs(u64 nasid, u64 size, u64 *objbuf)
अणु
	वापस uv_bios_call(UV_BIOS_EXTRA, nasid, UV_BIOS_EXTRA_ENUM_OBJECTS,
				0, size, (u64)objbuf);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_क्रमागत_objs);

बाह्य s64 uv_bios_क्रमागत_ports(u64 nasid, u64 obj_id, u64 size, u64 *portbuf)
अणु
	वापस uv_bios_call(UV_BIOS_EXTRA, nasid, UV_BIOS_EXTRA_ENUM_PORTS,
				obj_id, size, (u64)portbuf);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_क्रमागत_ports);

बाह्य s64 uv_bios_get_geoinfo(u64 nasid, u64 size, u64 *buf)
अणु
	वापस uv_bios_call(UV_BIOS_GET_GEOINFO, nasid, (u64)buf, size, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_get_geoinfo);

बाह्य s64 uv_bios_get_pci_topology(u64 size, u64 *buf)
अणु
	वापस uv_bios_call(UV_BIOS_GET_PCI_TOPOLOGY, (u64)buf, size, 0, 0, 0);
पूर्ण
EXPORT_SYMBOL_GPL(uv_bios_get_pci_topology);

अचिन्हित दीर्घ get_uv_systab_phys(bool msg)
अणु
	अगर ((uv_systab_phys == EFI_INVALID_TABLE_ADDR) ||
	    !uv_systab_phys || efi_runसमय_disabled()) अणु
		अगर (msg)
			pr_crit("UV: UVsystab: missing\n");
		वापस 0;
	पूर्ण
	वापस uv_systab_phys;
पूर्ण

पूर्णांक uv_bios_init(व्योम)
अणु
	अचिन्हित दीर्घ uv_systab_phys_addr;

	uv_systab = शून्य;
	uv_systab_phys_addr = get_uv_systab_phys(1);
	अगर (!uv_systab_phys_addr)
		वापस -EEXIST;

	uv_systab = ioremap(uv_systab_phys_addr, माप(काष्ठा uv_systab));
	अगर (!uv_systab || म_भेदन(uv_systab->signature, UV_SYSTAB_SIG, 4)) अणु
		pr_err("UV: UVsystab: bad signature!\n");
		iounmap(uv_systab);
		वापस -EINVAL;
	पूर्ण

	/* Starting with UV4 the UV systab size is variable */
	अगर (uv_systab->revision >= UV_SYSTAB_VERSION_UV4) अणु
		पूर्णांक size = uv_systab->size;

		iounmap(uv_systab);
		uv_systab = ioremap(uv_systab_phys_addr, size);
		अगर (!uv_systab) अणु
			pr_err("UV: UVsystab: ioremap(%d) failed!\n", size);
			वापस -EFAULT;
		पूर्ण
	पूर्ण
	pr_info("UV: UVsystab: Revision:%x\n", uv_systab->revision);
	वापस 0;
पूर्ण
