<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HP zx1 AGPGART routines.
 *
 * (c) Copyright 2002, 2003 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/log2.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/acpi-ext.h>

#समावेश "agp.h"

#घोषणा HP_ZX1_IOC_OFFSET	0x1000  /* ACPI reports SBA, we want IOC */

/* HP ZX1 IOC रेजिस्टरs */
#घोषणा HP_ZX1_IBASE		0x300
#घोषणा HP_ZX1_IMASK		0x308
#घोषणा HP_ZX1_PCOM		0x310
#घोषणा HP_ZX1_TCNFG		0x318
#घोषणा HP_ZX1_Pसूची_BASE	0x320

#घोषणा HP_ZX1_IOVA_BASE	GB(1UL)
#घोषणा HP_ZX1_IOVA_SIZE	GB(1UL)
#घोषणा HP_ZX1_GART_SIZE	(HP_ZX1_IOVA_SIZE / 2)
#घोषणा HP_ZX1_SBA_IOMMU_COOKIE	0x0000badbadc0ffeeUL

#घोषणा HP_ZX1_Pसूची_VALID_BIT	0x8000000000000000UL
#घोषणा HP_ZX1_IOVA_TO_Pसूची(va)	((va - hp_निजी.iova_base) >> hp_निजी.io_tlb_shअगरt)

#घोषणा AGP8X_MODE_BIT		3
#घोषणा AGP8X_MODE		(1 << AGP8X_MODE_BIT)

/* AGP bridge need not be PCI device, but DRM thinks it is. */
अटल काष्ठा pci_dev fake_bridge_dev;

अटल पूर्णांक hp_zx1_gart_found;

अटल काष्ठा aper_size_info_fixed hp_zx1_sizes[] =
अणु
	अणु0, 0, 0पूर्ण,		/* filled in by hp_zx1_fetch_size() */
पूर्ण;

अटल काष्ठा gatt_mask hp_zx1_masks[] =
अणु
	अणु.mask = HP_ZX1_Pसूची_VALID_BIT, .type = 0पूर्ण
पूर्ण;

अटल काष्ठा _hp_निजी अणु
	अस्थिर u8 __iomem *ioc_regs;
	अस्थिर u8 __iomem *lba_regs;
	पूर्णांक lba_cap_offset;
	u64 *io_pdir;		// Pसूची क्रम entire IOVA
	u64 *gatt;		// Pसूची just क्रम GART (subset of above)
	u64 gatt_entries;
	u64 iova_base;
	u64 gart_base;
	u64 gart_size;
	u64 io_pdir_size;
	पूर्णांक io_pdir_owner;	// करो we own it, or share it with sba_iommu?
	पूर्णांक io_page_size;
	पूर्णांक io_tlb_shअगरt;
	पूर्णांक io_tlb_ps;		// IOC ps config
	पूर्णांक io_pages_per_kpage;
पूर्ण hp_निजी;

अटल पूर्णांक __init hp_zx1_ioc_shared(व्योम)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	prपूर्णांकk(KERN_INFO PFX "HP ZX1 IOC: IOPDIR shared with sba_iommu\n");

	/*
	 * IOC alपढ़ोy configured by sba_iommu module; just use
	 * its setup.  We assume:
	 *	- IOVA space is 1Gb in size
	 *	- first 512Mb is IOMMU, second 512Mb is GART
	 */
	hp->io_tlb_ps = पढ़ोq(hp->ioc_regs+HP_ZX1_TCNFG);
	चयन (hp->io_tlb_ps) अणु
		हाल 0: hp->io_tlb_shअगरt = 12; अवरोध;
		हाल 1: hp->io_tlb_shअगरt = 13; अवरोध;
		हाल 2: hp->io_tlb_shअगरt = 14; अवरोध;
		हाल 3: hp->io_tlb_shअगरt = 16; अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR PFX "Invalid IOTLB page size "
			       "configuration 0x%x\n", hp->io_tlb_ps);
			hp->gatt = शून्य;
			hp->gatt_entries = 0;
			वापस -ENODEV;
	पूर्ण
	hp->io_page_size = 1 << hp->io_tlb_shअगरt;
	hp->io_pages_per_kpage = PAGE_SIZE / hp->io_page_size;

	hp->iova_base = पढ़ोq(hp->ioc_regs+HP_ZX1_IBASE) & ~0x1;
	hp->gart_base = hp->iova_base + HP_ZX1_IOVA_SIZE - HP_ZX1_GART_SIZE;

	hp->gart_size = HP_ZX1_GART_SIZE;
	hp->gatt_entries = hp->gart_size / hp->io_page_size;

	hp->io_pdir = phys_to_virt(पढ़ोq(hp->ioc_regs+HP_ZX1_Pसूची_BASE));
	hp->gatt = &hp->io_pdir[HP_ZX1_IOVA_TO_Pसूची(hp->gart_base)];

	अगर (hp->gatt[0] != HP_ZX1_SBA_IOMMU_COOKIE) अणु
		/* Normal हाल when no AGP device in प्रणाली */
		hp->gatt = शून्य;
		hp->gatt_entries = 0;
		prपूर्णांकk(KERN_ERR PFX "No reserved IO PDIR entry found; "
		       "GART disabled\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init
hp_zx1_ioc_owner (व्योम)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	prपूर्णांकk(KERN_INFO PFX "HP ZX1 IOC: IOPDIR dedicated to GART\n");

	/*
	 * Select an IOV page size no larger than प्रणाली page size.
	 */
	अगर (PAGE_SIZE >= KB(64)) अणु
		hp->io_tlb_shअगरt = 16;
		hp->io_tlb_ps = 3;
	पूर्ण अन्यथा अगर (PAGE_SIZE >= KB(16)) अणु
		hp->io_tlb_shअगरt = 14;
		hp->io_tlb_ps = 2;
	पूर्ण अन्यथा अगर (PAGE_SIZE >= KB(8)) अणु
		hp->io_tlb_shअगरt = 13;
		hp->io_tlb_ps = 1;
	पूर्ण अन्यथा अणु
		hp->io_tlb_shअगरt = 12;
		hp->io_tlb_ps = 0;
	पूर्ण
	hp->io_page_size = 1 << hp->io_tlb_shअगरt;
	hp->io_pages_per_kpage = PAGE_SIZE / hp->io_page_size;

	hp->iova_base = HP_ZX1_IOVA_BASE;
	hp->gart_size = HP_ZX1_GART_SIZE;
	hp->gart_base = hp->iova_base + HP_ZX1_IOVA_SIZE - hp->gart_size;

	hp->gatt_entries = hp->gart_size / hp->io_page_size;
	hp->io_pdir_size = (HP_ZX1_IOVA_SIZE / hp->io_page_size) * माप(u64);

	वापस 0;
पूर्ण

अटल पूर्णांक __init
hp_zx1_ioc_init (u64 hpa)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	hp->ioc_regs = ioremap(hpa, 1024);
	अगर (!hp->ioc_regs)
		वापस -ENOMEM;

	/*
	 * If the IOTLB is currently disabled, we can take it over.
	 * Otherwise, we have to share with sba_iommu.
	 */
	hp->io_pdir_owner = (पढ़ोq(hp->ioc_regs+HP_ZX1_IBASE) & 0x1) == 0;

	अगर (hp->io_pdir_owner)
		वापस hp_zx1_ioc_owner();

	वापस hp_zx1_ioc_shared();
पूर्ण

अटल पूर्णांक
hp_zx1_lba_find_capability (अस्थिर u8 __iomem *hpa, पूर्णांक cap)
अणु
	u16 status;
	u8 pos, id;
	पूर्णांक ttl = 48;

	status = पढ़ोw(hpa+PCI_STATUS);
	अगर (!(status & PCI_STATUS_CAP_LIST))
		वापस 0;
	pos = पढ़ोb(hpa+PCI_CAPABILITY_LIST);
	जबतक (ttl-- && pos >= 0x40) अणु
		pos &= ~3;
		id = पढ़ोb(hpa+pos+PCI_CAP_LIST_ID);
		अगर (id == 0xff)
			अवरोध;
		अगर (id == cap)
			वापस pos;
		pos = पढ़ोb(hpa+pos+PCI_CAP_LIST_NEXT);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init
hp_zx1_lba_init (u64 hpa)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;
	पूर्णांक cap;

	hp->lba_regs = ioremap(hpa, 256);
	अगर (!hp->lba_regs)
		वापस -ENOMEM;

	hp->lba_cap_offset = hp_zx1_lba_find_capability(hp->lba_regs, PCI_CAP_ID_AGP);

	cap = पढ़ोl(hp->lba_regs+hp->lba_cap_offset) & 0xff;
	अगर (cap != PCI_CAP_ID_AGP) अणु
		prपूर्णांकk(KERN_ERR PFX "Invalid capability ID 0x%02x at 0x%x\n",
		       cap, hp->lba_cap_offset);
		iounmap(hp->lba_regs);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
hp_zx1_fetch_size(व्योम)
अणु
	पूर्णांक size;

	size = hp_निजी.gart_size / MB(1);
	hp_zx1_sizes[0].size = size;
	agp_bridge->current_size = (व्योम *) &hp_zx1_sizes[0];
	वापस size;
पूर्ण

अटल पूर्णांक
hp_zx1_configure (व्योम)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	agp_bridge->gart_bus_addr = hp->gart_base;
	agp_bridge->capndx = hp->lba_cap_offset;
	agp_bridge->mode = पढ़ोl(hp->lba_regs+hp->lba_cap_offset+PCI_AGP_STATUS);

	अगर (hp->io_pdir_owner) अणु
		ग_लिखोl(virt_to_phys(hp->io_pdir), hp->ioc_regs+HP_ZX1_Pसूची_BASE);
		पढ़ोl(hp->ioc_regs+HP_ZX1_Pसूची_BASE);
		ग_लिखोl(hp->io_tlb_ps, hp->ioc_regs+HP_ZX1_TCNFG);
		पढ़ोl(hp->ioc_regs+HP_ZX1_TCNFG);
		ग_लिखोl((अचिन्हित पूर्णांक)(~(HP_ZX1_IOVA_SIZE-1)), hp->ioc_regs+HP_ZX1_IMASK);
		पढ़ोl(hp->ioc_regs+HP_ZX1_IMASK);
		ग_लिखोl(hp->iova_base|1, hp->ioc_regs+HP_ZX1_IBASE);
		पढ़ोl(hp->ioc_regs+HP_ZX1_IBASE);
		ग_लिखोl(hp->iova_base|ilog2(HP_ZX1_IOVA_SIZE), hp->ioc_regs+HP_ZX1_PCOM);
		पढ़ोl(hp->ioc_regs+HP_ZX1_PCOM);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
hp_zx1_cleanup (व्योम)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	अगर (hp->ioc_regs) अणु
		अगर (hp->io_pdir_owner) अणु
			ग_लिखोq(0, hp->ioc_regs+HP_ZX1_IBASE);
			पढ़ोq(hp->ioc_regs+HP_ZX1_IBASE);
		पूर्ण
		iounmap(hp->ioc_regs);
	पूर्ण
	अगर (hp->lba_regs)
		iounmap(hp->lba_regs);
पूर्ण

अटल व्योम
hp_zx1_tlbflush (काष्ठा agp_memory *mem)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	ग_लिखोq(hp->gart_base | ilog2(hp->gart_size), hp->ioc_regs+HP_ZX1_PCOM);
	पढ़ोq(hp->ioc_regs+HP_ZX1_PCOM);
पूर्ण

अटल पूर्णांक
hp_zx1_create_gatt_table (काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;
	पूर्णांक i;

	अगर (hp->io_pdir_owner) अणु
		hp->io_pdir = (u64 *) __get_मुक्त_pages(GFP_KERNEL,
						get_order(hp->io_pdir_size));
		अगर (!hp->io_pdir) अणु
			prपूर्णांकk(KERN_ERR PFX "Couldn't allocate contiguous "
				"memory for I/O PDIR\n");
			hp->gatt = शून्य;
			hp->gatt_entries = 0;
			वापस -ENOMEM;
		पूर्ण
		स_रखो(hp->io_pdir, 0, hp->io_pdir_size);

		hp->gatt = &hp->io_pdir[HP_ZX1_IOVA_TO_Pसूची(hp->gart_base)];
	पूर्ण

	क्रम (i = 0; i < hp->gatt_entries; i++) अणु
		hp->gatt[i] = (अचिन्हित दीर्घ) agp_bridge->scratch_page;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
hp_zx1_मुक्त_gatt_table (काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;

	अगर (hp->io_pdir_owner)
		मुक्त_pages((अचिन्हित दीर्घ) hp->io_pdir,
			    get_order(hp->io_pdir_size));
	अन्यथा
		hp->gatt[0] = HP_ZX1_SBA_IOMMU_COOKIE;
	वापस 0;
पूर्ण

अटल पूर्णांक
hp_zx1_insert_memory (काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;
	पूर्णांक i, k;
	off_t j, io_pg_start;
	पूर्णांक io_pg_count;

	अगर (type != mem->type ||
		agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type)) अणु
		वापस -EINVAL;
	पूर्ण

	io_pg_start = hp->io_pages_per_kpage * pg_start;
	io_pg_count = hp->io_pages_per_kpage * mem->page_count;
	अगर ((io_pg_start + io_pg_count) > hp->gatt_entries) अणु
		वापस -EINVAL;
	पूर्ण

	j = io_pg_start;
	जबतक (j < (io_pg_start + io_pg_count)) अणु
		अगर (hp->gatt[j]) अणु
			वापस -EBUSY;
		पूर्ण
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
		     k < hp->io_pages_per_kpage;
		     k++, j++, paddr += hp->io_page_size) अणु
			hp->gatt[j] = HP_ZX1_Pसूची_VALID_BIT | paddr;
		पूर्ण
	पूर्ण

	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण

अटल पूर्णांक
hp_zx1_हटाओ_memory (काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;
	पूर्णांक i, io_pg_start, io_pg_count;

	अगर (type != mem->type ||
		agp_bridge->driver->agp_type_to_mask_type(agp_bridge, type)) अणु
		वापस -EINVAL;
	पूर्ण

	io_pg_start = hp->io_pages_per_kpage * pg_start;
	io_pg_count = hp->io_pages_per_kpage * mem->page_count;
	क्रम (i = io_pg_start; i < io_pg_count + io_pg_start; i++) अणु
		hp->gatt[i] = agp_bridge->scratch_page;
	पूर्ण

	agp_bridge->driver->tlb_flush(mem);
	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ
hp_zx1_mask_memory (काष्ठा agp_bridge_data *bridge, dma_addr_t addr, पूर्णांक type)
अणु
	वापस HP_ZX1_Pसूची_VALID_BIT | addr;
पूर्ण

अटल व्योम
hp_zx1_enable (काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	काष्ठा _hp_निजी *hp = &hp_निजी;
	u32 command;

	command = पढ़ोl(hp->lba_regs+hp->lba_cap_offset+PCI_AGP_STATUS);
	command = agp_collect_device_status(bridge, mode, command);
	command |= 0x00000100;

	ग_लिखोl(command, hp->lba_regs+hp->lba_cap_offset+PCI_AGP_COMMAND);

	agp_device_command(command, (mode & AGP8X_MODE) != 0);
पूर्ण

स्थिर काष्ठा agp_bridge_driver hp_zx1_driver = अणु
	.owner			= THIS_MODULE,
	.माप_प्रकारype		= FIXED_APER_SIZE,
	.configure		= hp_zx1_configure,
	.fetch_size		= hp_zx1_fetch_size,
	.cleanup		= hp_zx1_cleanup,
	.tlb_flush		= hp_zx1_tlbflush,
	.mask_memory		= hp_zx1_mask_memory,
	.masks			= hp_zx1_masks,
	.agp_enable		= hp_zx1_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= hp_zx1_create_gatt_table,
	.मुक्त_gatt_table	= hp_zx1_मुक्त_gatt_table,
	.insert_memory		= hp_zx1_insert_memory,
	.हटाओ_memory		= hp_zx1_हटाओ_memory,
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
hp_zx1_setup (u64 ioc_hpa, u64 lba_hpa)
अणु
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक error = 0;

	error = hp_zx1_ioc_init(ioc_hpa);
	अगर (error)
		जाओ fail;

	error = hp_zx1_lba_init(lba_hpa);
	अगर (error)
		जाओ fail;

	bridge = agp_alloc_bridge();
	अगर (!bridge) अणु
		error = -ENOMEM;
		जाओ fail;
	पूर्ण
	bridge->driver = &hp_zx1_driver;

	fake_bridge_dev.venकरोr = PCI_VENDOR_ID_HP;
	fake_bridge_dev.device = PCI_DEVICE_ID_HP_PCIX_LBA;
	bridge->dev = &fake_bridge_dev;

	error = agp_add_bridge(bridge);
  fail:
	अगर (error)
		hp_zx1_cleanup();
	वापस error;
पूर्ण

अटल acpi_status __init
zx1_gart_probe (acpi_handle obj, u32 depth, व्योम *context, व्योम **ret)
अणु
	acpi_handle handle, parent;
	acpi_status status;
	काष्ठा acpi_device_info *info;
	u64 lba_hpa, sba_hpa, length;
	पूर्णांक match;

	status = hp_acpi_csr_space(obj, &lba_hpa, &length);
	अगर (ACPI_FAILURE(status))
		वापस AE_OK; /* keep looking क्रम another bridge */

	/* Look क्रम an enclosing IOC scope and find its CSR space */
	handle = obj;
	करो अणु
		status = acpi_get_object_info(handle, &info);
		अगर (ACPI_SUCCESS(status) && (info->valid & ACPI_VALID_HID)) अणु
			/* TBD check _CID also */
			match = (म_भेद(info->hardware_id.string, "HWP0001") == 0);
			kमुक्त(info);
			अगर (match) अणु
				status = hp_acpi_csr_space(handle, &sba_hpa, &length);
				अगर (ACPI_SUCCESS(status))
					अवरोध;
				अन्यथा अणु
					prपूर्णांकk(KERN_ERR PFX "Detected HP ZX1 "
					       "AGP LBA but no IOC.\n");
					वापस AE_OK;
				पूर्ण
			पूर्ण
		पूर्ण

		status = acpi_get_parent(handle, &parent);
		handle = parent;
	पूर्ण जबतक (ACPI_SUCCESS(status));

	अगर (ACPI_FAILURE(status))
		वापस AE_OK;	/* found no enclosing IOC */

	अगर (hp_zx1_setup(sba_hpa + HP_ZX1_IOC_OFFSET, lba_hpa))
		वापस AE_OK;

	prपूर्णांकk(KERN_INFO PFX "Detected HP ZX1 %s AGP chipset "
		"(ioc=%llx, lba=%llx)\n", (अक्षर *)context,
		sba_hpa + HP_ZX1_IOC_OFFSET, lba_hpa);

	hp_zx1_gart_found = 1;
	वापस AE_CTRL_TERMINATE; /* we only support one bridge; quit looking */
पूर्ण

अटल पूर्णांक __init
agp_hp_init (व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;

	acpi_get_devices("HWP0003", zx1_gart_probe, "HWP0003", शून्य);
	अगर (hp_zx1_gart_found)
		वापस 0;

	acpi_get_devices("HWP0007", zx1_gart_probe, "HWP0007", शून्य);
	अगर (hp_zx1_gart_found)
		वापस 0;

	वापस -ENODEV;
पूर्ण

अटल व्योम __निकास
agp_hp_cleanup (व्योम)
अणु
पूर्ण

module_init(agp_hp_init);
module_निकास(agp_hp_cleanup);

MODULE_LICENSE("GPL and additional rights");
