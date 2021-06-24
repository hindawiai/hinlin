<शैली गुरु>
/*
 * ALi AGPGART routines.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <यंत्र/page.h>		/* PAGE_SIZE */
#समावेश "agp.h"

#घोषणा ALI_AGPCTRL	0xb8
#घोषणा ALI_ATTBASE	0xbc
#घोषणा ALI_TLBCTRL	0xc0
#घोषणा ALI_TAGCTRL	0xc4
#घोषणा ALI_CACHE_FLUSH_CTRL	0xD0
#घोषणा ALI_CACHE_FLUSH_ADDR_MASK	0xFFFFF000
#घोषणा ALI_CACHE_FLUSH_EN	0x100

अटल पूर्णांक ali_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u32 temp;
	काष्ठा aper_size_info_32 *values;

	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_ATTBASE, &temp);
	temp &= ~(0xfffffff0);
	values = A_SIZE_32(agp_bridge->driver->aperture_sizes);

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp == values[i].size_value) अणु
			agp_bridge->previous_size =
			    agp_bridge->current_size = (व्योम *) (values + i);
			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ali_tlbflush(काष्ठा agp_memory *mem)
अणु
	u32 temp;

	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
	temp &= 0xfffffff0;
	temp |= (1<<0 | 1<<1);
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_TAGCTRL, temp);
पूर्ण

अटल व्योम ali_cleanup(व्योम)
अणु
	काष्ठा aper_size_info_32 *previous_size;
	u32 temp;

	previous_size = A_SIZE_32(agp_bridge->previous_size);

	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
// clear tag
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_TAGCTRL,
			((temp & 0xffffff00) | 0x00000001|0x00000002));

	pci_पढ़ो_config_dword(agp_bridge->dev,  ALI_ATTBASE, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_ATTBASE,
			((temp & 0x00000ff0) | previous_size->size_value));
पूर्ण

अटल पूर्णांक ali_configure(व्योम)
अणु
	u32 temp;
	काष्ठा aper_size_info_32 *current_size;

	current_size = A_SIZE_32(agp_bridge->current_size);

	/* aperture size and gatt addr */
	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_ATTBASE, &temp);
	temp = (((temp & 0x00000ff0) | (agp_bridge->gatt_bus_addr & 0xfffff000))
			| (current_size->size_value & 0xf));
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_ATTBASE, temp);

	/* tlb control */
	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_TLBCTRL, ((temp & 0xffffff00) | 0x00000010));

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

#अगर 0
	अगर (agp_bridge->type == ALI_M1541) अणु
		u32 nlvm_addr = 0;

		चयन (current_size->size_value) अणु
			हाल 0:  अवरोध;
			हाल 1:  nlvm_addr = 0x100000;अवरोध;
			हाल 2:  nlvm_addr = 0x200000;अवरोध;
			हाल 3:  nlvm_addr = 0x400000;अवरोध;
			हाल 4:  nlvm_addr = 0x800000;अवरोध;
			हाल 6:  nlvm_addr = 0x1000000;अवरोध;
			हाल 7:  nlvm_addr = 0x2000000;अवरोध;
			हाल 8:  nlvm_addr = 0x4000000;अवरोध;
			हाल 9:  nlvm_addr = 0x8000000;अवरोध;
			हाल 10: nlvm_addr = 0x10000000;अवरोध;
			शेष: अवरोध;
		पूर्ण
		nlvm_addr--;
		nlvm_addr&=0xfff00000;

		nlvm_addr+= agp_bridge->gart_bus_addr;
		nlvm_addr|=(agp_bridge->gart_bus_addr>>12);
		dev_info(&agp_bridge->dev->dev, "nlvm top &base = %8x\n",
			 nlvm_addr);
	पूर्ण
#पूर्ण_अगर

	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
	temp &= 0xffffff7f;		//enable TLB
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_TLBCTRL, temp);

	वापस 0;
पूर्ण


अटल व्योम m1541_cache_flush(व्योम)
अणु
	पूर्णांक i, page_count;
	u32 temp;

	global_cache_flush();

	page_count = 1 << A_SIZE_32(agp_bridge->current_size)->page_order;
	क्रम (i = 0; i < PAGE_SIZE * page_count; i += PAGE_SIZE) अणु
		pci_पढ़ो_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL,
				&temp);
		pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL,
				(((temp & ALI_CACHE_FLUSH_ADDR_MASK) |
				  (agp_bridge->gatt_bus_addr + i)) |
				 ALI_CACHE_FLUSH_EN));
	पूर्ण
पूर्ण

अटल काष्ठा page *m1541_alloc_page(काष्ठा agp_bridge_data *bridge)
अणु
	काष्ठा page *page = agp_generic_alloc_page(agp_bridge);
	u32 temp;

	अगर (!page)
		वापस शून्य;

	pci_पढ़ो_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL,
			(((temp & ALI_CACHE_FLUSH_ADDR_MASK) |
			  page_to_phys(page)) | ALI_CACHE_FLUSH_EN ));
	वापस page;
पूर्ण

अटल व्योम ali_destroy_page(काष्ठा page *page, पूर्णांक flags)
अणु
	अगर (page) अणु
		अगर (flags & AGP_PAGE_DESTROY_UNMAP) अणु
			global_cache_flush();	/* is this really needed?  --hch */
			agp_generic_destroy_page(page, flags);
		पूर्ण अन्यथा
			agp_generic_destroy_page(page, flags);
	पूर्ण
पूर्ण

अटल व्योम m1541_destroy_page(काष्ठा page *page, पूर्णांक flags)
अणु
	u32 temp;

	अगर (page == शून्य)
		वापस;

	अगर (flags & AGP_PAGE_DESTROY_UNMAP) अणु
		global_cache_flush();

		pci_पढ़ो_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL, &temp);
		pci_ग_लिखो_config_dword(agp_bridge->dev, ALI_CACHE_FLUSH_CTRL,
				       (((temp & ALI_CACHE_FLUSH_ADDR_MASK) |
					 page_to_phys(page)) | ALI_CACHE_FLUSH_EN));
	पूर्ण
	agp_generic_destroy_page(page, flags);
पूर्ण


/* Setup function */

अटल स्थिर काष्ठा aper_size_info_32 ali_generic_sizes[7] =
अणु
	अणु256, 65536, 6, 10पूर्ण,
	अणु128, 32768, 5, 9पूर्ण,
	अणु64, 16384, 4, 8पूर्ण,
	अणु32, 8192, 3, 7पूर्ण,
	अणु16, 4096, 2, 6पूर्ण,
	अणु8, 2048, 1, 4पूर्ण,
	अणु4, 1024, 0, 3पूर्ण
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver ali_generic_bridge = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= ali_generic_sizes,
	.माप_प्रकारype		= U32_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= ali_configure,
	.fetch_size		= ali_fetch_size,
	.cleanup		= ali_cleanup,
	.tlb_flush		= ali_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= शून्य,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_destroy_page	= ali_destroy_page,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver ali_m1541_bridge = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= ali_generic_sizes,
	.माप_प्रकारype		= U32_APER_SIZE,
	.num_aperture_sizes	= 7,
	.configure		= ali_configure,
	.fetch_size		= ali_fetch_size,
	.cleanup		= ali_cleanup,
	.tlb_flush		= ali_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= शून्य,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= m1541_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= m1541_alloc_page,
	.agp_destroy_page	= m1541_destroy_page,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;


अटल काष्ठा agp_device_ids ali_agp_device_ids[] =
अणु
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1541,
		.chipset_name	= "M1541",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1621,
		.chipset_name	= "M1621",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1631,
		.chipset_name	= "M1631",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1632,
		.chipset_name	= "M1632",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1641,
		.chipset_name	= "M1641",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1644,
		.chipset_name	= "M1644",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1647,
		.chipset_name	= "M1647",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1651,
		.chipset_name	= "M1651",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1671,
		.chipset_name	= "M1671",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1681,
		.chipset_name	= "M1681",
	पूर्ण,
	अणु
		.device_id	= PCI_DEVICE_ID_AL_M1683,
		.chipset_name	= "M1683",
	पूर्ण,

	अणु पूर्ण, /* dummy final entry, always present */
पूर्ण;

अटल पूर्णांक agp_ali_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_device_ids *devs = ali_agp_device_ids;
	काष्ठा agp_bridge_data *bridge;
	u8 hidden_1621_id, cap_ptr;
	पूर्णांक j;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	/* probe क्रम known chipsets */
	क्रम (j = 0; devs[j].chipset_name; j++) अणु
		अगर (pdev->device == devs[j].device_id)
			जाओ found;
	पूर्ण

	dev_err(&pdev->dev, "unsupported ALi chipset [%04x/%04x])\n",
		pdev->venकरोr, pdev->device);
	वापस -ENODEV;


found:
	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_AL_M1541:
		bridge->driver = &ali_m1541_bridge;
		अवरोध;
	हाल PCI_DEVICE_ID_AL_M1621:
		pci_पढ़ो_config_byte(pdev, 0xFB, &hidden_1621_id);
		चयन (hidden_1621_id) अणु
		हाल 0x31:
			devs[j].chipset_name = "M1631";
			अवरोध;
		हाल 0x32:
			devs[j].chipset_name = "M1632";
			अवरोध;
		हाल 0x41:
			devs[j].chipset_name = "M1641";
			अवरोध;
		हाल 0x43:
			devs[j].chipset_name = "M1621";
			अवरोध;
		हाल 0x47:
			devs[j].chipset_name = "M1647";
			अवरोध;
		हाल 0x51:
			devs[j].chipset_name = "M1651";
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		bridge->driver = &ali_generic_bridge;
	पूर्ण

	dev_info(&pdev->dev, "ALi %s chipset\n", devs[j].chipset_name);

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS,
			&bridge->mode);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_ali_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

अटल स्थिर काष्ठा pci_device_id agp_ali_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AL,
	.device		= PCI_ANY_ID,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_ali_pci_table);

अटल काष्ठा pci_driver agp_ali_pci_driver = अणु
	.name		= "agpgart-ali",
	.id_table	= agp_ali_pci_table,
	.probe		= agp_ali_probe,
	.हटाओ		= agp_ali_हटाओ,
पूर्ण;

अटल पूर्णांक __init agp_ali_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_ali_pci_driver);
पूर्ण

अटल व्योम __निकास agp_ali_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_ali_pci_driver);
पूर्ण

module_init(agp_ali_init);
module_निकास(agp_ali_cleanup);

MODULE_AUTHOR("Dave Jones");
MODULE_LICENSE("GPL and additional rights");

