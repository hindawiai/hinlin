<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HP Quicksilver AGP GART routines
 *
 * Copyright (c) 2006, Kyle McMartin <kyle@parisc-linux.org>
 *
 * Based on drivers/अक्षर/agpgart/hp-agp.c which is
 * (c) Copyright 2002, 2003 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/klist.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/parisc-device.h>
#समावेश <यंत्र/ropes.h>

#समावेश "agp.h"

#घोषणा DRVNAME	"quicksilver"
#घोषणा DRVPFX	DRVNAME ": "

#घोषणा AGP8X_MODE_BIT		3
#घोषणा AGP8X_MODE		(1 << AGP8X_MODE_BIT)

अटल अचिन्हित दीर्घ
parisc_agp_mask_memory(काष्ठा agp_bridge_data *bridge, dma_addr_t addr,
		       पूर्णांक type);

अटल काष्ठा _parisc_agp_info अणु
	व्योम __iomem *ioc_regs;
	व्योम __iomem *lba_regs;

	पूर्णांक lba_cap_offset;

	u64 *gatt;
	u64 gatt_entries;

	u64 gart_base;
	u64 gart_size;

	पूर्णांक io_page_size;
	पूर्णांक io_pages_per_kpage;
पूर्ण parisc_agp_info;

अटल काष्ठा gatt_mask parisc_agp_masks[] =
अणु
        अणु
		.mask = SBA_Pसूची_VALID_BIT,
		.type = 0
	पूर्ण
पूर्ण;

अटल काष्ठा aper_size_info_fixed parisc_agp_sizes[] =
अणु
        अणु0, 0, 0पूर्ण,              /* filled in by parisc_agp_fetch_size() */
पूर्ण;

अटल पूर्णांक
parisc_agp_fetch_size(व्योम)
अणु
	पूर्णांक size;

	size = parisc_agp_info.gart_size / MB(1);
	parisc_agp_sizes[0].size = size;
	agp_bridge->current_size = (व्योम *) &parisc_agp_sizes[0];

	वापस size;
पूर्ण

अटल पूर्णांक
parisc_agp_configure(व्योम)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;

	agp_bridge->gart_bus_addr = info->gart_base;
	agp_bridge->capndx = info->lba_cap_offset;
	agp_bridge->mode = पढ़ोl(info->lba_regs+info->lba_cap_offset+PCI_AGP_STATUS);

	वापस 0;
पूर्ण

अटल व्योम
parisc_agp_tlbflush(काष्ठा agp_memory *mem)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;

	ग_लिखोq(info->gart_base | ilog2(info->gart_size), info->ioc_regs+IOC_PCOM);
	पढ़ोq(info->ioc_regs+IOC_PCOM);	/* flush */
पूर्ण

अटल पूर्णांक
parisc_agp_create_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
	पूर्णांक i;

	क्रम (i = 0; i < info->gatt_entries; i++) अणु
		info->gatt[i] = (अचिन्हित दीर्घ)agp_bridge->scratch_page;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
parisc_agp_मुक्त_gatt_table(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;

	info->gatt[0] = SBA_AGPGART_COOKIE;

	वापस 0;
पूर्ण

अटल पूर्णांक
parisc_agp_insert_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
	पूर्णांक i, k;
	off_t j, io_pg_start;
	पूर्णांक io_pg_count;

	अगर (type != mem->type ||
		agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type)) अणु
		वापस -EINVAL;
	पूर्ण

	io_pg_start = info->io_pages_per_kpage * pg_start;
	io_pg_count = info->io_pages_per_kpage * mem->page_count;
	अगर ((io_pg_start + io_pg_count) > info->gatt_entries) अणु
		वापस -EINVAL;
	पूर्ण

	j = io_pg_start;
	जबतक (j < (io_pg_start + io_pg_count)) अणु
		अगर (info->gatt[j])
			वापस -EBUSY;
		j++;
	पूर्ण

	अगर (!mem->is_flushed) अणु
		global_cache_flush();
		mem->is_flushed = true;
	पूर्ण

	क्रम (i = 0, j = io_pg_start; i < mem->page_count; i++) अणु
		अचिन्हित दीर्घ paddr;

		paddr = page_to_phys(mem->pages[i]);
		क्रम (k = 0;
		     k < info->io_pages_per_kpage;
		     k++, j++, paddr += info->io_page_size) अणु
			info->gatt[j] =
				parisc_agp_mask_memory(agp_bridge,
					paddr, type);
		पूर्ण
	पूर्ण

	agp_bridge->driver->tlb_flush(mem);

	वापस 0;
पूर्ण

अटल पूर्णांक
parisc_agp_हटाओ_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
	पूर्णांक i, io_pg_start, io_pg_count;

	अगर (type != mem->type ||
		agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type)) अणु
		वापस -EINVAL;
	पूर्ण

	io_pg_start = info->io_pages_per_kpage * pg_start;
	io_pg_count = info->io_pages_per_kpage * mem->page_count;
	क्रम (i = io_pg_start; i < io_pg_count + io_pg_start; i++) अणु
		info->gatt[i] = agp_bridge->scratch_page;
	पूर्ण

	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
parisc_agp_mask_memory(काष्ठा agp_bridge_data *bridge, dma_addr_t addr,
		       पूर्णांक type)
अणु
	वापस SBA_Pसूची_VALID_BIT | addr;
पूर्ण

अटल व्योम
parisc_agp_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
	u32 command;

	command = पढ़ोl(info->lba_regs + info->lba_cap_offset + PCI_AGP_STATUS);

	command = agp_collect_device_status(bridge, mode, command);
	command |= 0x00000100;

	ग_लिखोl(command, info->lba_regs + info->lba_cap_offset + PCI_AGP_COMMAND);

	agp_device_command(command, (mode & AGP8X_MODE) != 0);
पूर्ण

अटल स्थिर काष्ठा agp_bridge_driver parisc_agp_driver = अणु
	.owner			= THIS_MODULE,
	.माप_प्रकारype		= FIXED_APER_SIZE,
	.configure		= parisc_agp_configure,
	.fetch_size		= parisc_agp_fetch_size,
	.tlb_flush		= parisc_agp_tlbflush,
	.mask_memory		= parisc_agp_mask_memory,
	.masks			= parisc_agp_masks,
	.agp_enable		= parisc_agp_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= parisc_agp_create_gatt_table,
	.मुक्त_gatt_table	= parisc_agp_मुक्त_gatt_table,
	.insert_memory		= parisc_agp_insert_memory,
	.हटाओ_memory		= parisc_agp_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
	.cant_use_aperture	= true,
पूर्ण;

अटल पूर्णांक __init
agp_ioc_init(व्योम __iomem *ioc_regs)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
        u64 iova_base, *io_pdir, io_tlb_ps;
        पूर्णांक io_tlb_shअगरt;

        prपूर्णांकk(KERN_INFO DRVPFX "IO PDIR shared with sba_iommu\n");

        info->ioc_regs = ioc_regs;

        io_tlb_ps = पढ़ोq(info->ioc_regs+IOC_TCNFG);
        चयन (io_tlb_ps) अणु
        हाल 0: io_tlb_shअगरt = 12; अवरोध;
        हाल 1: io_tlb_shअगरt = 13; अवरोध;
        हाल 2: io_tlb_shअगरt = 14; अवरोध;
        हाल 3: io_tlb_shअगरt = 16; अवरोध;
        शेष:
                prपूर्णांकk(KERN_ERR DRVPFX "Invalid IOTLB page size "
                       "configuration 0x%llx\n", io_tlb_ps);
                info->gatt = शून्य;
                info->gatt_entries = 0;
                वापस -ENODEV;
        पूर्ण
        info->io_page_size = 1 << io_tlb_shअगरt;
        info->io_pages_per_kpage = PAGE_SIZE / info->io_page_size;

        iova_base = पढ़ोq(info->ioc_regs+IOC_IBASE) & ~0x1;
        info->gart_base = iova_base + PLUTO_IOVA_SIZE - PLUTO_GART_SIZE;

        info->gart_size = PLUTO_GART_SIZE;
        info->gatt_entries = info->gart_size / info->io_page_size;

        io_pdir = phys_to_virt(पढ़ोq(info->ioc_regs+IOC_Pसूची_BASE));
        info->gatt = &io_pdir[(PLUTO_IOVA_SIZE/2) >> PAGE_SHIFT];

        अगर (info->gatt[0] != SBA_AGPGART_COOKIE) अणु
                info->gatt = शून्य;
                info->gatt_entries = 0;
                prपूर्णांकk(KERN_ERR DRVPFX "No reserved IO PDIR entry found; "
                       "GART disabled\n");
                वापस -ENODEV;
        पूर्ण

        वापस 0;
पूर्ण

अटल पूर्णांक
lba_find_capability(पूर्णांक cap)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
        u16 status;
        u8 pos, id;
        पूर्णांक ttl = 48;

        status = पढ़ोw(info->lba_regs + PCI_STATUS);
        अगर (!(status & PCI_STATUS_CAP_LIST))
                वापस 0;
        pos = पढ़ोb(info->lba_regs + PCI_CAPABILITY_LIST);
        जबतक (ttl-- && pos >= 0x40) अणु
                pos &= ~3;
                id = पढ़ोb(info->lba_regs + pos + PCI_CAP_LIST_ID);
                अगर (id == 0xff)
                        अवरोध;
                अगर (id == cap)
                        वापस pos;
                pos = पढ़ोb(info->lba_regs + pos + PCI_CAP_LIST_NEXT);
        पूर्ण
        वापस 0;
पूर्ण

अटल पूर्णांक __init
agp_lba_init(व्योम __iomem *lba_hpa)
अणु
	काष्ठा _parisc_agp_info *info = &parisc_agp_info;
        पूर्णांक cap;

	info->lba_regs = lba_hpa;
        info->lba_cap_offset = lba_find_capability(PCI_CAP_ID_AGP);

        cap = पढ़ोl(lba_hpa + info->lba_cap_offset) & 0xff;
        अगर (cap != PCI_CAP_ID_AGP) अणु
                prपूर्णांकk(KERN_ERR DRVPFX "Invalid capability ID 0x%02x at 0x%x\n",
                       cap, info->lba_cap_offset);
                वापस -ENODEV;
        पूर्ण

        वापस 0;
पूर्ण

अटल पूर्णांक __init
parisc_agp_setup(व्योम __iomem *ioc_hpa, व्योम __iomem *lba_hpa)
अणु
	काष्ठा pci_dev *fake_bridge_dev = शून्य;
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक error = 0;

	fake_bridge_dev = pci_alloc_dev(शून्य);
	अगर (!fake_bridge_dev) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण

	error = agp_ioc_init(ioc_hpa);
	अगर (error)
		जाओ fail;

	error = agp_lba_init(lba_hpa);
	अगर (error)
		जाओ fail;

	bridge = agp_alloc_bridge();
	अगर (!bridge) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण
	bridge->driver = &parisc_agp_driver;

	fake_bridge_dev->venकरोr = PCI_VENDOR_ID_HP;
	fake_bridge_dev->device = PCI_DEVICE_ID_HP_PCIX_LBA;
	bridge->dev = fake_bridge_dev;

	error = agp_add_bridge(bridge);
	अगर (error)
		जाओ fail;
	वापस 0;

fail:
	kमुक्त(fake_bridge_dev);
	वापस error;
पूर्ण

अटल पूर्णांक
find_quicksilver(काष्ठा device *dev, व्योम *data)
अणु
	काष्ठा parisc_device **lba = data;
	काष्ठा parisc_device *padev = to_parisc_device(dev);

	अगर (IS_QUICKSILVER(padev))
		*lba = padev;

	वापस 0;
पूर्ण

अटल पूर्णांक
parisc_agp_init(व्योम)
अणु
	बाह्य काष्ठा sba_device *sba_list;

	पूर्णांक err = -1;
	काष्ठा parisc_device *sba = शून्य, *lba = शून्य;
	काष्ठा lba_device *lbadev = शून्य;

	अगर (!sba_list)
		जाओ out;

	/* Find our parent Pluto */
	sba = sba_list->dev;
	अगर (!IS_PLUTO(sba)) अणु
		prपूर्णांकk(KERN_INFO DRVPFX "No Pluto found, so no AGPGART for you.\n");
		जाओ out;
	पूर्ण

	/* Now search our Pluto क्रम our precious AGP device... */
	device_क्रम_each_child(&sba->dev, &lba, find_quicksilver);

	अगर (!lba) अणु
		prपूर्णांकk(KERN_INFO DRVPFX "No AGP devices found.\n");
		जाओ out;
	पूर्ण

	lbadev = parisc_get_drvdata(lba);

	/* w00t, let's go find our cookies... */
	parisc_agp_setup(sba_list->ioc[0].ioc_hpa, lbadev->hba.base_addr);

	वापस 0;

out:
	वापस err;
पूर्ण

module_init(parisc_agp_init);

MODULE_AUTHOR("Kyle McMartin <kyle@parisc-linux.org>");
MODULE_LICENSE("GPL");
