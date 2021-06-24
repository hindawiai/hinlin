<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/opal.h>

#समावेश "pci.h"

/* क्रम pci_dev_is_added() */
#समावेश "../../../../drivers/pci/pci.h"

/*
 * The majority of the complनिकासy in supporting SR-IOV on PowerNV comes from
 * the need to put the MMIO space क्रम each VF पूर्णांकo a separate PE. Internally
 * the PHB maps MMIO addresses to a specअगरic PE using the "Memory BAR Table".
 * The MBT historically only applied to the 64bit MMIO winकरोw of the PHB
 * so it's common to see it referred to as the "M64BT".
 *
 * An MBT entry stores the mapped range as an <base>,<mask> pair. This क्रमces
 * the address range that we want to map to be घातer-of-two sized and aligned.
 * For conventional PCI devices this isn't really an issue since PCI device BARs
 * have the same requirement.
 *
 * For a SR-IOV BAR things are a little more awkward since size and alignment
 * are not coupled. The alignment is set based on the the per-VF BAR size, but
 * the total BAR area is: number-of-vfs * per-vf-size. The number of VFs
 * isn't necessarily a घातer of two, so neither is the total size. To fix that
 * we need to finesse (पढ़ो: hack) the Linux BAR allocator so that it will
 * allocate the SR-IOV BARs in a way that lets us map them using the MBT.
 *
 * The changes to size and alignment that we need to करो depend on the "mode"
 * of MBT entry that we use. We only support SR-IOV on PHB3 (IODA2) and above,
 * so as a baseline we can assume that we have the following BAR modes
 * available:
 *
 *   NB: $PE_COUNT is the number of PEs that the PHB supports.
 *
 * a) A segmented BAR that splits the mapped range पूर्णांकo $PE_COUNT equally sized
 *    segments. The n'th segment is mapped to the n'th PE.
 * b) An un-segmented BAR that maps the whole address range to a specअगरic PE.
 *
 *
 * We prefer to use mode a) since it only requires one MBT entry per SR-IOV BAR
 * For comparison b) requires one entry per-VF per-BAR, or:
 * (num-vfs * num-sriov-bars) in total. To use a) we need the size of each segment
 * to equal the size of the per-VF BAR area. So:
 *
 *	new_size = per-vf-size * number-of-PEs
 *
 * The alignment क्रम the SR-IOV BAR also needs to be changed from per-vf-size
 * to "new_size", calculated above. Implementing this is a convoluted process
 * which requires several hooks in the PCI core:
 *
 * 1. In pcibios_add_device() we call pnv_pci_ioda_fixup_iov().
 *
 *    At this poपूर्णांक the device has been probed and the device's BARs are sized,
 *    but no resource allocations have been करोne. The SR-IOV BARs are sized
 *    based on the maximum number of VFs supported by the device and we need
 *    to increase that to new_size.
 *
 * 2. Later, when Linux actually assigns resources it tries to make the resource
 *    allocations क्रम each PCI bus as compact as possible. As a part of that it
 *    sorts the BARs on a bus by their required alignment, which is calculated
 *    using pci_resource_alignment().
 *
 *    For IOV resources this goes:
 *    pci_resource_alignment()
 *        pci_sriov_resource_alignment()
 *            pcibios_sriov_resource_alignment()
 *                pnv_pci_iov_resource_alignment()
 *
 *    Our hook overrides the शेष alignment, equal to the per-vf-size, with
 *    new_size computed above.
 *
 * 3. When userspace enables VFs क्रम a device:
 *
 *    sriov_enable()
 *       pcibios_sriov_enable()
 *           pnv_pcibios_sriov_enable()
 *
 *    This is where we actually allocate PE numbers क्रम each VF and setup the
 *    MBT mapping क्रम each SR-IOV BAR. In steps 1) and 2) we setup an "arena"
 *    where each MBT segment is equal in size to the VF BAR so we can shअगरt
 *    around the actual SR-IOV BAR location within this arena. We need this
 *    ability because the PE space is shared by all devices on the same PHB.
 *    When using mode a) described above segment 0 in maps to PE#0 which might
 *    be alपढ़ोy being used by another device on the PHB.
 *
 *    As a result we need allocate a contigious range of PE numbers, then shअगरt
 *    the address programmed पूर्णांकo the SR-IOV BAR of the PF so that the address
 *    of VF0 matches up with the segment corresponding to the first allocated
 *    PE number. This is handled in pnv_pci_vf_resource_shअगरt().
 *
 *    Once all that is करोne we वापस to the PCI core which then enables VFs,
 *    scans them and creates pci_devs क्रम each. The init process क्रम a VF is
 *    largely the same as a normal device, but the VF is inserted पूर्णांकo the IODA
 *    PE that we allocated क्रम it rather than the PE associated with the bus.
 *
 * 4. When userspace disables VFs we unwind the above in
 *    pnv_pcibios_sriov_disable(). Fortunately this is relatively simple since
 *    we करोn't need to validate anything, just tear करोwn the mappings and
 *    move SR-IOV resource back to its "proper" location.
 *
 * That's how mode a) works. In theory mode b) (single PE mapping) is less work
 * since we can map each inभागidual VF with a separate BAR. However, there's a
 * few limitations:
 *
 * 1) For IODA2 mode b) has a minimum alignment requirement of 32MB. This makes
 *    it only usable क्रम devices with very large per-VF BARs. Such devices are
 *    similar to Big Foot. They definitely exist, but I've never seen one.
 *
 * 2) The number of MBT entries that we have is limited. PHB3 and PHB4 only
 *    16 total and some are needed क्रम. Most SR-IOV capable network cards can support
 *    more than 16 VFs on each port.
 *
 * We use b) when using a) would use more than 1/4 of the entire 64 bit MMIO
 * winकरोw of the PHB.
 *
 *
 *
 * PHB4 (IODA3) added a few new features that would be useful क्रम SR-IOV. It
 * allowed the MBT to map 32bit MMIO space in addition to 64bit which allows
 * us to support SR-IOV BARs in the 32bit MMIO winकरोw. This is useful since
 * the Linux BAR allocation will place any BAR marked as non-prefetchable पूर्णांकo
 * the non-prefetchable bridge winकरोw, which is 32bit only. It also added two
 * new modes:
 *
 * c) A segmented BAR similar to a), but each segment can be inभागidually
 *    mapped to any PE. This is matches how the 32bit MMIO winकरोw worked on
 *    IODA1&2.
 *
 * d) A segmented BAR with 8, 64, or 128 segments. This works similarly to a),
 *    but with fewer segments and configurable base PE.
 *
 *    i.e. The n'th segment maps to the (n + base)'th PE.
 *
 *    The base PE is also required to be a multiple of the winकरोw size.
 *
 * Unक्रमtunately, the OPAL API करोesn't currently (as of skiboot v6.6) allow us
 * to exploit any of the IODA3 features.
 */

अटल व्योम pnv_pci_ioda_fixup_iov_resources(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा resource *res;
	पूर्णांक i;
	resource_माप_प्रकार vf_bar_sz;
	काष्ठा pnv_iov_data *iov;
	पूर्णांक mul;

	iov = kzalloc(माप(*iov), GFP_KERNEL);
	अगर (!iov)
		जाओ disable_iov;
	pdev->dev.archdata.iov_data = iov;
	mul = phb->ioda.total_pe_num;

	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &pdev->resource[i + PCI_IOV_RESOURCES];
		अगर (!res->flags || res->parent)
			जारी;
		अगर (!pnv_pci_is_m64_flags(res->flags)) अणु
			dev_warn(&pdev->dev, "Don't support SR-IOV with non M64 VF BAR%d: %pR. \n",
				 i, res);
			जाओ disable_iov;
		पूर्ण

		vf_bar_sz = pci_iov_resource_size(pdev, i + PCI_IOV_RESOURCES);

		/*
		 * Generally, one segmented M64 BAR maps one IOV BAR. However,
		 * अगर a VF BAR is too large we end up wasting a lot of space.
		 * If each VF needs more than 1/4 of the शेष m64 segment
		 * then each VF BAR should be mapped in single-PE mode to reduce
		 * the amount of space required. This करोes however limit the
		 * number of VFs we can support.
		 *
		 * The 1/4 limit is arbitrary and can be tweaked.
		 */
		अगर (vf_bar_sz > (phb->ioda.m64_segsize >> 2)) अणु
			/*
			 * On PHB3, the minimum size alignment of M64 BAR in
			 * single mode is 32MB. If this VF BAR is smaller than
			 * 32MB, but still too large क्रम a segmented winकरोw
			 * then we can't map it and need to disable SR-IOV क्रम
			 * this device.
			 */
			अगर (vf_bar_sz < SZ_32M) अणु
				pci_err(pdev, "VF BAR%d: %pR can't be mapped in single PE mode\n",
					i, res);
				जाओ disable_iov;
			पूर्ण

			iov->m64_single_mode[i] = true;
			जारी;
		पूर्ण

		/*
		 * This BAR can be mapped with one segmented winकरोw, so adjust
		 * te resource size to accommodate.
		 */
		pci_dbg(pdev, " Fixing VF BAR%d: %pR to\n", i, res);
		res->end = res->start + vf_bar_sz * mul - 1;
		pci_dbg(pdev, "                       %pR\n", res);

		pci_info(pdev, "VF BAR%d: %pR (expanded to %d VFs for PE alignment)",
			 i, res, mul);

		iov->need_shअगरt = true;
	पूर्ण

	वापस;

disable_iov:
	/* Save ourselves some MMIO space by disabling the unusable BARs */
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &pdev->resource[i + PCI_IOV_RESOURCES];
		res->flags = 0;
		res->end = res->start - 1;
	पूर्ण

	pdev->dev.archdata.iov_data = शून्य;
	kमुक्त(iov);
पूर्ण

व्योम pnv_pci_ioda_fixup_iov(काष्ठा pci_dev *pdev)
अणु
	अगर (WARN_ON(pci_dev_is_added(pdev)))
		वापस;

	अगर (pdev->is_virtfn) अणु
		काष्ठा pnv_ioda_pe *pe = pnv_ioda_get_pe(pdev);

		/*
		 * VF PEs are single-device PEs so their pdev poपूर्णांकer needs to
		 * be set. The pdev करोesn't exist when the PE is allocated (in
		 * (pcibios_sriov_enable()) so we fix it up here.
		 */
		pe->pdev = pdev;
		WARN_ON(!(pe->flags & PNV_IODA_PE_VF));
	पूर्ण अन्यथा अगर (pdev->is_physfn) अणु
		/*
		 * For PFs adjust their allocated IOV resources to match what
		 * the PHB can support using it's M64 BAR table.
		 */
		pnv_pci_ioda_fixup_iov_resources(pdev);
	पूर्ण
पूर्ण

resource_माप_प्रकार pnv_pci_iov_resource_alignment(काष्ठा pci_dev *pdev,
						      पूर्णांक resno)
अणु
	resource_माप_प्रकार align = pci_iov_resource_size(pdev, resno);
	काष्ठा pnv_phb *phb = pci_bus_to_pnvhb(pdev->bus);
	काष्ठा pnv_iov_data *iov = pnv_iov_get(pdev);

	/*
	 * iov can be null अगर we have an SR-IOV device with IOV BAR that can't
	 * be placed in the m64 space (i.e. The BAR is 32bit or non-prefetch).
	 * In that हाल we करोn't allow VFs to be enabled since one of their
	 * BARs would not be placed in the correct PE.
	 */
	अगर (!iov)
		वापस align;

	/*
	 * If we're using single mode then we can just use the native VF BAR
	 * alignment. We validated that it's possible to use a single PE
	 * winकरोw above when we did the fixup.
	 */
	अगर (iov->m64_single_mode[resno - PCI_IOV_RESOURCES])
		वापस align;

	/*
	 * On PowerNV platक्रमm, IOV BAR is mapped by M64 BAR to enable the
	 * SR-IOV. While from hardware perspective, the range mapped by M64
	 * BAR should be size aligned.
	 *
	 * This function वापसs the total IOV BAR size अगर M64 BAR is in
	 * Shared PE mode or just VF BAR size अगर not.
	 * If the M64 BAR is in Single PE mode, वापस the VF BAR size or
	 * M64 segment size अगर IOV BAR size is less.
	 */
	वापस phb->ioda.total_pe_num * align;
पूर्ण

अटल पूर्णांक pnv_pci_vf_release_m64(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	काष्ठा pnv_iov_data   *iov;
	काष्ठा pnv_phb        *phb;
	पूर्णांक winकरोw_id;

	phb = pci_bus_to_pnvhb(pdev->bus);
	iov = pnv_iov_get(pdev);

	क्रम_each_set_bit(winकरोw_id, iov->used_m64_bar_mask, MAX_M64_BARS) अणु
		opal_pci_phb_mmio_enable(phb->opal_id,
					 OPAL_M64_WINDOW_TYPE,
					 winकरोw_id,
					 0);

		clear_bit(winकरोw_id, &phb->ioda.m64_bar_alloc);
	पूर्ण

	वापस 0;
पूर्ण


/*
 * PHB3 and beyond support segmented winकरोws. The winकरोw's address range
 * is subभागided पूर्णांकo phb->ioda.total_pe_num segments and there's a 1-1
 * mapping between PEs and segments.
 */
अटल पूर्णांक64_t pnv_ioda_map_m64_segmented(काष्ठा pnv_phb *phb,
					  पूर्णांक winकरोw_id,
					  resource_माप_प्रकार start,
					  resource_माप_प्रकार size)
अणु
	पूर्णांक64_t rc;

	rc = opal_pci_set_phb_mem_winकरोw(phb->opal_id,
					 OPAL_M64_WINDOW_TYPE,
					 winकरोw_id,
					 start,
					 0, /* unused */
					 size);
	अगर (rc)
		जाओ out;

	rc = opal_pci_phb_mmio_enable(phb->opal_id,
				      OPAL_M64_WINDOW_TYPE,
				      winकरोw_id,
				      OPAL_ENABLE_M64_SPLIT);
out:
	अगर (rc)
		pr_err("Failed to map M64 window #%d: %lld\n", winकरोw_id, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक64_t pnv_ioda_map_m64_single(काष्ठा pnv_phb *phb,
				       पूर्णांक pe_num,
				       पूर्णांक winकरोw_id,
				       resource_माप_प्रकार start,
				       resource_माप_प्रकार size)
अणु
	पूर्णांक64_t rc;

	/*
	 * The API क्रम setting up m64 mmio winकरोws seems to have been deचिन्हित
	 * with P7-IOC in mind. For that chip each M64 BAR (winकरोw) had a fixed
	 * split of 8 equally sized segments each of which could inभागidually
	 * asचिन्हित to a PE.
	 *
	 * The problem with this is that the API करोesn't have any way to
	 * communicate the number of segments we want on a BAR. This wasn't
	 * a problem क्रम p7-ioc since you didn't have a choice, but the
	 * single PE winकरोws added in PHB3 करोn't map cleanly to this API.
	 *
	 * As a result we've got this slightly awkward process where we
	 * call opal_pci_map_pe_mmio_winकरोw() to put the single in single
	 * PE mode, and set the PE क्रम the winकरोw beक्रमe setting the address
	 * bounds. We need to करो it this way because the single PE winकरोws
	 * क्रम PHB3 have dअगरferent alignment requirements on PHB3.
	 */
	rc = opal_pci_map_pe_mmio_winकरोw(phb->opal_id,
					 pe_num,
					 OPAL_M64_WINDOW_TYPE,
					 winकरोw_id,
					 0);
	अगर (rc)
		जाओ out;

	/*
	 * NB: In single PE mode the winकरोw needs to be aligned to 32MB
	 */
	rc = opal_pci_set_phb_mem_winकरोw(phb->opal_id,
					 OPAL_M64_WINDOW_TYPE,
					 winकरोw_id,
					 start,
					 0, /* ignored by FW, m64 is 1-1 */
					 size);
	अगर (rc)
		जाओ out;

	/*
	 * Now actually enable it. We specअगरied the BAR should be in "non-split"
	 * mode so FW will validate that the BAR is in single PE mode.
	 */
	rc = opal_pci_phb_mmio_enable(phb->opal_id,
				      OPAL_M64_WINDOW_TYPE,
				      winकरोw_id,
				      OPAL_ENABLE_M64_NON_SPLIT);
out:
	अगर (rc)
		pr_err("Error mapping single PE BAR\n");

	वापस rc;
पूर्ण

अटल पूर्णांक pnv_pci_alloc_m64_bar(काष्ठा pnv_phb *phb, काष्ठा pnv_iov_data *iov)
अणु
	पूर्णांक win;

	करो अणु
		win = find_next_zero_bit(&phb->ioda.m64_bar_alloc,
				phb->ioda.m64_bar_idx + 1, 0);

		अगर (win >= phb->ioda.m64_bar_idx + 1)
			वापस -1;
	पूर्ण जबतक (test_and_set_bit(win, &phb->ioda.m64_bar_alloc));

	set_bit(win, iov->used_m64_bar_mask);

	वापस win;
पूर्ण

अटल पूर्णांक pnv_pci_vf_assign_m64(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	काष्ठा pnv_iov_data   *iov;
	काष्ठा pnv_phb        *phb;
	पूर्णांक                    win;
	काष्ठा resource       *res;
	पूर्णांक                    i, j;
	पूर्णांक64_t                rc;
	resource_माप_प्रकार        size, start;
	पूर्णांक                    base_pe_num;

	phb = pci_bus_to_pnvhb(pdev->bus);
	iov = pnv_iov_get(pdev);

	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &pdev->resource[i + PCI_IOV_RESOURCES];
		अगर (!res->flags || !res->parent)
			जारी;

		/* करोn't need single mode? map everything in one go! */
		अगर (!iov->m64_single_mode[i]) अणु
			win = pnv_pci_alloc_m64_bar(phb, iov);
			अगर (win < 0)
				जाओ m64_failed;

			size = resource_size(res);
			start = res->start;

			rc = pnv_ioda_map_m64_segmented(phb, win, start, size);
			अगर (rc)
				जाओ m64_failed;

			जारी;
		पूर्ण

		/* otherwise map each VF with single PE BARs */
		size = pci_iov_resource_size(pdev, PCI_IOV_RESOURCES + i);
		base_pe_num = iov->vf_pe_arr[0].pe_number;

		क्रम (j = 0; j < num_vfs; j++) अणु
			win = pnv_pci_alloc_m64_bar(phb, iov);
			अगर (win < 0)
				जाओ m64_failed;

			start = res->start + size * j;
			rc = pnv_ioda_map_m64_single(phb, win,
						     base_pe_num + j,
						     start,
						     size);
			अगर (rc)
				जाओ m64_failed;
		पूर्ण
	पूर्ण
	वापस 0;

m64_failed:
	pnv_pci_vf_release_m64(pdev, num_vfs);
	वापस -EBUSY;
पूर्ण

अटल व्योम pnv_ioda_release_vf_PE(काष्ठा pci_dev *pdev)
अणु
	काष्ठा pnv_phb        *phb;
	काष्ठा pnv_ioda_pe    *pe, *pe_n;

	phb = pci_bus_to_pnvhb(pdev->bus);

	अगर (!pdev->is_physfn)
		वापस;

	/* FIXME: Use pnv_ioda_release_pe()? */
	list_क्रम_each_entry_safe(pe, pe_n, &phb->ioda.pe_list, list) अणु
		अगर (pe->parent_dev != pdev)
			जारी;

		pnv_pci_ioda2_release_pe_dma(pe);

		/* Remove from list */
		mutex_lock(&phb->ioda.pe_list_mutex);
		list_del(&pe->list);
		mutex_unlock(&phb->ioda.pe_list_mutex);

		pnv_ioda_deconfigure_pe(phb, pe);

		pnv_ioda_मुक्त_pe(pe);
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_pci_vf_resource_shअगरt(काष्ठा pci_dev *dev, पूर्णांक offset)
अणु
	काष्ठा resource *res, res2;
	काष्ठा pnv_iov_data *iov;
	resource_माप_प्रकार size;
	u16 num_vfs;
	पूर्णांक i;

	अगर (!dev->is_physfn)
		वापस -EINVAL;
	iov = pnv_iov_get(dev);

	/*
	 * "offset" is in VFs.  The M64 winकरोws are sized so that when they
	 * are segmented, each segment is the same size as the IOV BAR.
	 * Each segment is in a separate PE, and the high order bits of the
	 * address are the PE number.  Thereक्रमe, each VF's BAR is in a
	 * separate PE, and changing the IOV BAR start address changes the
	 * range of PEs the VFs are in.
	 */
	num_vfs = iov->num_vfs;
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &dev->resource[i + PCI_IOV_RESOURCES];
		अगर (!res->flags || !res->parent)
			जारी;
		अगर (iov->m64_single_mode[i])
			जारी;

		/*
		 * The actual IOV BAR range is determined by the start address
		 * and the actual size क्रम num_vfs VFs BAR.  This check is to
		 * make sure that after shअगरting, the range will not overlap
		 * with another device.
		 */
		size = pci_iov_resource_size(dev, i + PCI_IOV_RESOURCES);
		res2.flags = res->flags;
		res2.start = res->start + (size * offset);
		res2.end = res2.start + (size * num_vfs) - 1;

		अगर (res2.end > res->end) अणु
			dev_err(&dev->dev, "VF BAR%d: %pR would extend past %pR (trying to enable %d VFs shifted by %d)\n",
				i, &res2, res, num_vfs, offset);
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	/*
	 * Since M64 BAR shares segments among all possible 256 PEs,
	 * we have to shअगरt the beginning of PF IOV BAR to make it start from
	 * the segment which beदीर्घs to the PE number asचिन्हित to the first VF.
	 * This creates a "hole" in the /proc/iomem which could be used क्रम
	 * allocating other resources so we reserve this area below and
	 * release when IOV is released.
	 */
	क्रम (i = 0; i < PCI_SRIOV_NUM_BARS; i++) अणु
		res = &dev->resource[i + PCI_IOV_RESOURCES];
		अगर (!res->flags || !res->parent)
			जारी;
		अगर (iov->m64_single_mode[i])
			जारी;

		size = pci_iov_resource_size(dev, i + PCI_IOV_RESOURCES);
		res2 = *res;
		res->start += size * offset;

		dev_info(&dev->dev, "VF BAR%d: %pR shifted to %pR (%sabling %d VFs shifted by %d)\n",
			 i, &res2, res, (offset > 0) ? "En" : "Dis",
			 num_vfs, offset);

		अगर (offset < 0) अणु
			devm_release_resource(&dev->dev, &iov->holes[i]);
			स_रखो(&iov->holes[i], 0, माप(iov->holes[i]));
		पूर्ण

		pci_update_resource(dev, i + PCI_IOV_RESOURCES);

		अगर (offset > 0) अणु
			iov->holes[i].start = res2.start;
			iov->holes[i].end = res2.start + size * offset - 1;
			iov->holes[i].flags = IORESOURCE_BUS;
			iov->holes[i].name = "pnv_iov_reserved";
			devm_request_resource(&dev->dev, res->parent,
					&iov->holes[i]);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम pnv_pci_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	u16                    num_vfs, base_pe;
	काष्ठा pnv_iov_data   *iov;

	iov = pnv_iov_get(pdev);
	num_vfs = iov->num_vfs;
	base_pe = iov->vf_pe_arr[0].pe_number;

	अगर (WARN_ON(!iov))
		वापस;

	/* Release VF PEs */
	pnv_ioda_release_vf_PE(pdev);

	/* Un-shअगरt the IOV BARs अगर we need to */
	अगर (iov->need_shअगरt)
		pnv_pci_vf_resource_shअगरt(pdev, -base_pe);

	/* Release M64 winकरोws */
	pnv_pci_vf_release_m64(pdev, num_vfs);
पूर्ण

अटल व्योम pnv_ioda_setup_vf_PE(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	काष्ठा pnv_phb        *phb;
	काष्ठा pnv_ioda_pe    *pe;
	पूर्णांक                    pe_num;
	u16                    vf_index;
	काष्ठा pnv_iov_data   *iov;
	काष्ठा pci_dn         *pdn;

	अगर (!pdev->is_physfn)
		वापस;

	phb = pci_bus_to_pnvhb(pdev->bus);
	pdn = pci_get_pdn(pdev);
	iov = pnv_iov_get(pdev);

	/* Reserve PE क्रम each VF */
	क्रम (vf_index = 0; vf_index < num_vfs; vf_index++) अणु
		पूर्णांक vf_devfn = pci_iov_virtfn_devfn(pdev, vf_index);
		पूर्णांक vf_bus = pci_iov_virtfn_bus(pdev, vf_index);
		काष्ठा pci_dn *vf_pdn;

		pe = &iov->vf_pe_arr[vf_index];
		pe->phb = phb;
		pe->flags = PNV_IODA_PE_VF;
		pe->pbus = शून्य;
		pe->parent_dev = pdev;
		pe->mve_number = -1;
		pe->rid = (vf_bus << 8) | vf_devfn;

		pe_num = pe->pe_number;
		pe_info(pe, "VF %04d:%02d:%02d.%d associated with PE#%x\n",
			pci_करोमुख्य_nr(pdev->bus), pdev->bus->number,
			PCI_SLOT(vf_devfn), PCI_FUNC(vf_devfn), pe_num);

		अगर (pnv_ioda_configure_pe(phb, pe)) अणु
			/* XXX What करो we करो here ? */
			pnv_ioda_मुक्त_pe(pe);
			pe->pdev = शून्य;
			जारी;
		पूर्ण

		/* Put PE to the list */
		mutex_lock(&phb->ioda.pe_list_mutex);
		list_add_tail(&pe->list, &phb->ioda.pe_list);
		mutex_unlock(&phb->ioda.pe_list_mutex);

		/* associate this pe to it's pdn */
		list_क्रम_each_entry(vf_pdn, &pdn->parent->child_list, list) अणु
			अगर (vf_pdn->busno == vf_bus &&
			    vf_pdn->devfn == vf_devfn) अणु
				vf_pdn->pe_number = pe_num;
				अवरोध;
			पूर्ण
		पूर्ण

		pnv_pci_ioda2_setup_dma_pe(phb, pe);
	पूर्ण
पूर्ण

अटल पूर्णांक pnv_pci_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	काष्ठा pnv_ioda_pe    *base_pe;
	काष्ठा pnv_iov_data   *iov;
	काष्ठा pnv_phb        *phb;
	पूर्णांक                    ret;
	u16                    i;

	phb = pci_bus_to_pnvhb(pdev->bus);
	iov = pnv_iov_get(pdev);

	/*
	 * There's a calls to IODA2 PE setup code littered throughout. We could
	 * probably fix that, but we'd still have problems due to the
	 * restriction inherent on IODA1 PHBs.
	 *
	 * NB: We class IODA3 as IODA2 since they're very similar.
	 */
	अगर (phb->type != PNV_PHB_IODA2) अणु
		pci_err(pdev, "SR-IOV is not supported on this PHB\n");
		वापस -ENXIO;
	पूर्ण

	अगर (!iov) अणु
		dev_info(&pdev->dev, "don't support this SRIOV device with non 64bit-prefetchable IOV BAR\n");
		वापस -ENOSPC;
	पूर्ण

	/* allocate a contigious block of PEs क्रम our VFs */
	base_pe = pnv_ioda_alloc_pe(phb, num_vfs);
	अगर (!base_pe) अणु
		pci_err(pdev, "Unable to allocate PEs for %d VFs\n", num_vfs);
		वापस -EBUSY;
	पूर्ण

	iov->vf_pe_arr = base_pe;
	iov->num_vfs = num_vfs;

	/* Assign M64 winकरोw accordingly */
	ret = pnv_pci_vf_assign_m64(pdev, num_vfs);
	अगर (ret) अणु
		dev_info(&pdev->dev, "Not enough M64 window resources\n");
		जाओ m64_failed;
	पूर्ण

	/*
	 * When using one M64 BAR to map one IOV BAR, we need to shअगरt
	 * the IOV BAR according to the PE# allocated to the VFs.
	 * Otherwise, the PE# क्रम the VF will conflict with others.
	 */
	अगर (iov->need_shअगरt) अणु
		ret = pnv_pci_vf_resource_shअगरt(pdev, base_pe->pe_number);
		अगर (ret)
			जाओ shअगरt_failed;
	पूर्ण

	/* Setup VF PEs */
	pnv_ioda_setup_vf_PE(pdev, num_vfs);

	वापस 0;

shअगरt_failed:
	pnv_pci_vf_release_m64(pdev, num_vfs);

m64_failed:
	क्रम (i = 0; i < num_vfs; i++)
		pnv_ioda_मुक्त_pe(&iov->vf_pe_arr[i]);

	वापस ret;
पूर्ण

पूर्णांक pnv_pcibios_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	pnv_pci_sriov_disable(pdev);

	/* Release PCI data */
	हटाओ_sriov_vf_pdns(pdev);
	वापस 0;
पूर्ण

पूर्णांक pnv_pcibios_sriov_enable(काष्ठा pci_dev *pdev, u16 num_vfs)
अणु
	/* Allocate PCI data */
	add_sriov_vf_pdns(pdev);

	वापस pnv_pci_sriov_enable(pdev, num_vfs);
पूर्ण
