<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * TCE helpers क्रम IODA PCI/PCIe on PowerNV platक्रमms
 *
 * Copyright 2018 IBM Corp.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/iommu.h>

#समावेश <यंत्र/iommu.h>
#समावेश <यंत्र/tce.h>
#समावेश "pci.h"

अचिन्हित दीर्घ pnv_ioda_parse_tce_sizes(काष्ठा pnv_phb *phb)
अणु
	काष्ठा pci_controller *hose = phb->hose;
	काष्ठा device_node *dn = hose->dn;
	अचिन्हित दीर्घ mask = 0;
	पूर्णांक i, rc, count;
	u32 val;

	count = of_property_count_u32_elems(dn, "ibm,supported-tce-sizes");
	अगर (count <= 0) अणु
		mask = SZ_4K | SZ_64K;
		/* Add 16M क्रम POWER8 by शेष */
		अगर (cpu_has_feature(CPU_FTR_ARCH_207S) &&
				!cpu_has_feature(CPU_FTR_ARCH_300))
			mask |= SZ_16M | SZ_256M;
		वापस mask;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		rc = of_property_पढ़ो_u32_index(dn, "ibm,supported-tce-sizes",
						i, &val);
		अगर (rc == 0)
			mask |= 1ULL << val;
	पूर्ण

	वापस mask;
पूर्ण

व्योम pnv_pci_setup_iommu_table(काष्ठा iommu_table *tbl,
		व्योम *tce_mem, u64 tce_size,
		u64 dma_offset, अचिन्हित पूर्णांक page_shअगरt)
अणु
	tbl->it_blocksize = 16;
	tbl->it_base = (अचिन्हित दीर्घ)tce_mem;
	tbl->it_page_shअगरt = page_shअगरt;
	tbl->it_offset = dma_offset >> tbl->it_page_shअगरt;
	tbl->it_index = 0;
	tbl->it_size = tce_size >> 3;
	tbl->it_busno = 0;
	tbl->it_type = TCE_PCI;
पूर्ण

अटल __be64 *pnv_alloc_tce_level(पूर्णांक nid, अचिन्हित पूर्णांक shअगरt)
अणु
	काष्ठा page *tce_mem = शून्य;
	__be64 *addr;

	tce_mem = alloc_pages_node(nid, GFP_ATOMIC | __GFP_NOWARN,
			shअगरt - PAGE_SHIFT);
	अगर (!tce_mem) अणु
		pr_err("Failed to allocate a TCE memory, level shift=%d\n",
				shअगरt);
		वापस शून्य;
	पूर्ण
	addr = page_address(tce_mem);
	स_रखो(addr, 0, 1UL << shअगरt);

	वापस addr;
पूर्ण

अटल व्योम pnv_pci_ioda2_table_करो_मुक्त_pages(__be64 *addr,
		अचिन्हित दीर्घ size, अचिन्हित पूर्णांक levels);

अटल __be64 *pnv_tce(काष्ठा iommu_table *tbl, bool user, दीर्घ idx, bool alloc)
अणु
	__be64 *पंचांगp = user ? tbl->it_userspace : (__be64 *) tbl->it_base;
	पूर्णांक  level = tbl->it_indirect_levels;
	स्थिर दीर्घ shअगरt = ilog2(tbl->it_level_size);
	अचिन्हित दीर्घ mask = (tbl->it_level_size - 1) << (level * shअगरt);

	जबतक (level) अणु
		पूर्णांक n = (idx & mask) >> (level * shअगरt);
		अचिन्हित दीर्घ oldtce, tce = be64_to_cpu(READ_ONCE(पंचांगp[n]));

		अगर (!tce) अणु
			__be64 *पंचांगp2;

			अगर (!alloc)
				वापस शून्य;

			पंचांगp2 = pnv_alloc_tce_level(tbl->it_nid,
					ilog2(tbl->it_level_size) + 3);
			अगर (!पंचांगp2)
				वापस शून्य;

			tce = __pa(पंचांगp2) | TCE_PCI_READ | TCE_PCI_WRITE;
			oldtce = be64_to_cpu(cmpxchg(&पंचांगp[n], 0,
					cpu_to_be64(tce)));
			अगर (oldtce) अणु
				pnv_pci_ioda2_table_करो_मुक्त_pages(पंचांगp2,
					ilog2(tbl->it_level_size) + 3, 1);
				tce = oldtce;
			पूर्ण
		पूर्ण

		पंचांगp = __va(tce & ~(TCE_PCI_READ | TCE_PCI_WRITE));
		idx &= ~mask;
		mask >>= shअगरt;
		--level;
	पूर्ण

	वापस पंचांगp + idx;
पूर्ण

पूर्णांक pnv_tce_build(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages,
		अचिन्हित दीर्घ uaddr, क्रमागत dma_data_direction direction,
		अचिन्हित दीर्घ attrs)
अणु
	u64 proto_tce = iommu_direction_to_tce_perm(direction);
	u64 rpn = __pa(uaddr) >> tbl->it_page_shअगरt;
	दीर्घ i;

	अगर (proto_tce & TCE_PCI_WRITE)
		proto_tce |= TCE_PCI_READ;

	क्रम (i = 0; i < npages; i++) अणु
		अचिन्हित दीर्घ newtce = proto_tce |
			((rpn + i) << tbl->it_page_shअगरt);
		अचिन्हित दीर्घ idx = index - tbl->it_offset + i;

		*(pnv_tce(tbl, false, idx, true)) = cpu_to_be64(newtce);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_IOMMU_API
पूर्णांक pnv_tce_xchg(काष्ठा iommu_table *tbl, दीर्घ index,
		अचिन्हित दीर्घ *hpa, क्रमागत dma_data_direction *direction,
		bool alloc)
अणु
	u64 proto_tce = iommu_direction_to_tce_perm(*direction);
	अचिन्हित दीर्घ newtce = *hpa | proto_tce, oldtce;
	अचिन्हित दीर्घ idx = index - tbl->it_offset;
	__be64 *ptce = शून्य;

	BUG_ON(*hpa & ~IOMMU_PAGE_MASK(tbl));

	अगर (*direction == DMA_NONE) अणु
		ptce = pnv_tce(tbl, false, idx, false);
		अगर (!ptce) अणु
			*hpa = 0;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!ptce) अणु
		ptce = pnv_tce(tbl, false, idx, alloc);
		अगर (!ptce)
			वापस -ENOMEM;
	पूर्ण

	अगर (newtce & TCE_PCI_WRITE)
		newtce |= TCE_PCI_READ;

	oldtce = be64_to_cpu(xchg(ptce, cpu_to_be64(newtce)));
	*hpa = oldtce & ~(TCE_PCI_READ | TCE_PCI_WRITE);
	*direction = iommu_tce_direction(oldtce);

	वापस 0;
पूर्ण

__be64 *pnv_tce_useraddrptr(काष्ठा iommu_table *tbl, दीर्घ index, bool alloc)
अणु
	अगर (WARN_ON_ONCE(!tbl->it_userspace))
		वापस शून्य;

	वापस pnv_tce(tbl, true, index - tbl->it_offset, alloc);
पूर्ण
#पूर्ण_अगर

व्योम pnv_tce_मुक्त(काष्ठा iommu_table *tbl, दीर्घ index, दीर्घ npages)
अणु
	दीर्घ i;

	क्रम (i = 0; i < npages; i++) अणु
		अचिन्हित दीर्घ idx = index - tbl->it_offset + i;
		__be64 *ptce = pnv_tce(tbl, false, idx,	false);

		अगर (ptce)
			*ptce = cpu_to_be64(0);
		अन्यथा
			/* Skip the rest of the level */
			i |= tbl->it_level_size - 1;
	पूर्ण
पूर्ण

अचिन्हित दीर्घ pnv_tce_get(काष्ठा iommu_table *tbl, दीर्घ index)
अणु
	__be64 *ptce = pnv_tce(tbl, false, index - tbl->it_offset, false);

	अगर (!ptce)
		वापस 0;

	वापस be64_to_cpu(*ptce);
पूर्ण

अटल व्योम pnv_pci_ioda2_table_करो_मुक्त_pages(__be64 *addr,
		अचिन्हित दीर्घ size, अचिन्हित पूर्णांक levels)
अणु
	स्थिर अचिन्हित दीर्घ addr_ul = (अचिन्हित दीर्घ) addr &
			~(TCE_PCI_READ | TCE_PCI_WRITE);

	अगर (levels) अणु
		दीर्घ i;
		u64 *पंचांगp = (u64 *) addr_ul;

		क्रम (i = 0; i < size; ++i) अणु
			अचिन्हित दीर्घ hpa = be64_to_cpu(पंचांगp[i]);

			अगर (!(hpa & (TCE_PCI_READ | TCE_PCI_WRITE)))
				जारी;

			pnv_pci_ioda2_table_करो_मुक्त_pages(__va(hpa), size,
					levels - 1);
		पूर्ण
	पूर्ण

	मुक्त_pages(addr_ul, get_order(size << 3));
पूर्ण

व्योम pnv_pci_ioda2_table_मुक्त_pages(काष्ठा iommu_table *tbl)
अणु
	स्थिर अचिन्हित दीर्घ size = tbl->it_indirect_levels ?
			tbl->it_level_size : tbl->it_size;

	अगर (!tbl->it_size)
		वापस;

	pnv_pci_ioda2_table_करो_मुक्त_pages((__be64 *)tbl->it_base, size,
			tbl->it_indirect_levels);
	अगर (tbl->it_userspace) अणु
		pnv_pci_ioda2_table_करो_मुक्त_pages(tbl->it_userspace, size,
				tbl->it_indirect_levels);
	पूर्ण
पूर्ण

अटल __be64 *pnv_pci_ioda2_table_करो_alloc_pages(पूर्णांक nid, अचिन्हित पूर्णांक shअगरt,
		अचिन्हित पूर्णांक levels, अचिन्हित दीर्घ limit,
		अचिन्हित दीर्घ *current_offset, अचिन्हित दीर्घ *total_allocated)
अणु
	__be64 *addr, *पंचांगp;
	अचिन्हित दीर्घ allocated = 1UL << shअगरt;
	अचिन्हित पूर्णांक entries = 1UL << (shअगरt - 3);
	दीर्घ i;

	addr = pnv_alloc_tce_level(nid, shअगरt);
	*total_allocated += allocated;

	--levels;
	अगर (!levels) अणु
		*current_offset += allocated;
		वापस addr;
	पूर्ण

	क्रम (i = 0; i < entries; ++i) अणु
		पंचांगp = pnv_pci_ioda2_table_करो_alloc_pages(nid, shअगरt,
				levels, limit, current_offset, total_allocated);
		अगर (!पंचांगp)
			अवरोध;

		addr[i] = cpu_to_be64(__pa(पंचांगp) |
				TCE_PCI_READ | TCE_PCI_WRITE);

		अगर (*current_offset >= limit)
			अवरोध;
	पूर्ण

	वापस addr;
पूर्ण

दीर्घ pnv_pci_ioda2_table_alloc_pages(पूर्णांक nid, __u64 bus_offset,
		__u32 page_shअगरt, __u64 winकरोw_size, __u32 levels,
		bool alloc_userspace_copy, काष्ठा iommu_table *tbl)
अणु
	व्योम *addr, *uas = शून्य;
	अचिन्हित दीर्घ offset = 0, level_shअगरt, total_allocated = 0;
	अचिन्हित दीर्घ total_allocated_uas = 0;
	स्थिर अचिन्हित पूर्णांक winकरोw_shअगरt = ilog2(winकरोw_size);
	अचिन्हित पूर्णांक entries_shअगरt = winकरोw_shअगरt - page_shअगरt;
	अचिन्हित पूर्णांक table_shअगरt = max_t(अचिन्हित पूर्णांक, entries_shअगरt + 3,
			PAGE_SHIFT);
	स्थिर अचिन्हित दीर्घ tce_table_size = 1UL << table_shअगरt;

	अगर (!levels || (levels > POWERNV_IOMMU_MAX_LEVELS))
		वापस -EINVAL;

	अगर (!is_घातer_of_2(winकरोw_size))
		वापस -EINVAL;

	/* Adjust direct table size from winकरोw_size and levels */
	entries_shअगरt = (entries_shअगरt + levels - 1) / levels;
	level_shअगरt = entries_shअगरt + 3;
	level_shअगरt = max_t(अचिन्हित पूर्णांक, level_shअगरt, PAGE_SHIFT);

	अगर ((level_shअगरt - 3) * levels + page_shअगरt >= 55)
		वापस -EINVAL;

	/* Allocate TCE table */
	addr = pnv_pci_ioda2_table_करो_alloc_pages(nid, level_shअगरt,
			1, tce_table_size, &offset, &total_allocated);

	/* addr==शून्य means that the first level allocation failed */
	अगर (!addr)
		वापस -ENOMEM;

	/*
	 * First level was allocated but some lower level failed as
	 * we did not allocate as much as we wanted,
	 * release partially allocated table.
	 */
	अगर (levels == 1 && offset < tce_table_size)
		जाओ मुक्त_tces_निकास;

	/* Allocate userspace view of the TCE table */
	अगर (alloc_userspace_copy) अणु
		offset = 0;
		uas = pnv_pci_ioda2_table_करो_alloc_pages(nid, level_shअगरt,
				1, tce_table_size, &offset,
				&total_allocated_uas);
		अगर (!uas)
			जाओ मुक्त_tces_निकास;
		अगर (levels == 1 && (offset < tce_table_size ||
				total_allocated_uas != total_allocated))
			जाओ मुक्त_uas_निकास;
	पूर्ण

	/* Setup linux iommu table */
	pnv_pci_setup_iommu_table(tbl, addr, tce_table_size, bus_offset,
			page_shअगरt);
	tbl->it_level_size = 1ULL << (level_shअगरt - 3);
	tbl->it_indirect_levels = levels - 1;
	tbl->it_userspace = uas;
	tbl->it_nid = nid;

	pr_debug("Created TCE table: ws=%08llx ts=%lx @%08llx base=%lx uas=%p levels=%d/%d\n",
			winकरोw_size, tce_table_size, bus_offset, tbl->it_base,
			tbl->it_userspace, 1, levels);

	वापस 0;

मुक्त_uas_निकास:
	pnv_pci_ioda2_table_करो_मुक्त_pages(uas,
			1ULL << (level_shअगरt - 3), levels - 1);
मुक्त_tces_निकास:
	pnv_pci_ioda2_table_करो_मुक्त_pages(addr,
			1ULL << (level_shअगरt - 3), levels - 1);

	वापस -ENOMEM;
पूर्ण

व्योम pnv_pci_unlink_table_and_group(काष्ठा iommu_table *tbl,
		काष्ठा iommu_table_group *table_group)
अणु
	दीर्घ i;
	bool found;
	काष्ठा iommu_table_group_link *tgl;

	अगर (!tbl || !table_group)
		वापस;

	/* Remove link to a group from table's list of attached groups */
	found = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(tgl, &tbl->it_group_list, next) अणु
		अगर (tgl->table_group == table_group) अणु
			list_del_rcu(&tgl->next);
			kमुक्त_rcu(tgl, rcu);
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (WARN_ON(!found))
		वापस;

	/* Clean a poपूर्णांकer to iommu_table in iommu_table_group::tables[] */
	found = false;
	क्रम (i = 0; i < IOMMU_TABLE_GROUP_MAX_TABLES; ++i) अणु
		अगर (table_group->tables[i] == tbl) अणु
			iommu_tce_table_put(tbl);
			table_group->tables[i] = शून्य;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	WARN_ON(!found);
पूर्ण

दीर्घ pnv_pci_link_table_and_group(पूर्णांक node, पूर्णांक num,
		काष्ठा iommu_table *tbl,
		काष्ठा iommu_table_group *table_group)
अणु
	काष्ठा iommu_table_group_link *tgl = शून्य;

	अगर (WARN_ON(!tbl || !table_group))
		वापस -EINVAL;

	tgl = kzalloc_node(माप(काष्ठा iommu_table_group_link), GFP_KERNEL,
			node);
	अगर (!tgl)
		वापस -ENOMEM;

	tgl->table_group = table_group;
	list_add_rcu(&tgl->next, &tbl->it_group_list);

	table_group->tables[num] = iommu_tce_table_get(tbl);

	वापस 0;
पूर्ण
