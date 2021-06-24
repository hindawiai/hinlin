<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * VIA AGPGART routines.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश "agp.h"

अटल स्थिर काष्ठा pci_device_id agp_via_pci_table[];

#घोषणा VIA_GARTCTRL	0x80
#घोषणा VIA_APSIZE	0x84
#घोषणा VIA_ATTBASE	0x88

#घोषणा VIA_AGP3_GARTCTRL	0x90
#घोषणा VIA_AGP3_APSIZE		0x94
#घोषणा VIA_AGP3_ATTBASE	0x98
#घोषणा VIA_AGPSEL		0xfd

अटल पूर्णांक via_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u8 temp;
	काष्ठा aper_size_info_8 *values;

	values = A_SIZE_8(agp_bridge->driver->aperture_sizes);
	pci_पढ़ो_config_byte(agp_bridge->dev, VIA_APSIZE, &temp);
	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp == values[i].size_value) अणु
			agp_bridge->previous_size =
			    agp_bridge->current_size = (व्योम *) (values + i);
			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण
	prपूर्णांकk(KERN_ERR PFX "Unknown aperture size from AGP bridge (0x%x)\n", temp);
	वापस 0;
पूर्ण


अटल पूर्णांक via_configure(व्योम)
अणु
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);
	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, VIA_APSIZE,
			      current_size->size_value);
	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* GART control रेजिस्टर */
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_GARTCTRL, 0x0000000f);

	/* attbase - aperture GATT base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_ATTBASE,
			    (agp_bridge->gatt_bus_addr & 0xfffff000) | 3);
	वापस 0;
पूर्ण


अटल व्योम via_cleanup(व्योम)
अणु
	काष्ठा aper_size_info_8 *previous_size;

	previous_size = A_SIZE_8(agp_bridge->previous_size);
	pci_ग_लिखो_config_byte(agp_bridge->dev, VIA_APSIZE,
			      previous_size->size_value);
	/* Do not disable by writing 0 to VIA_ATTBASE, it screws things up
	 * during reinitialization.
	 */
पूर्ण


अटल व्योम via_tlbflush(काष्ठा agp_memory *mem)
अणु
	u32 temp;

	pci_पढ़ो_config_dword(agp_bridge->dev, VIA_GARTCTRL, &temp);
	temp |= (1<<7);
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_GARTCTRL, temp);
	temp &= ~(1<<7);
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_GARTCTRL, temp);
पूर्ण


अटल स्थिर काष्ठा aper_size_info_8 via_generic_sizes[9] =
अणु
	अणु256, 65536, 6, 0पूर्ण,
	अणु128, 32768, 5, 128पूर्ण,
	अणु64, 16384, 4, 192पूर्ण,
	अणु32, 8192, 3, 224पूर्ण,
	अणु16, 4096, 2, 240पूर्ण,
	अणु8, 2048, 1, 248पूर्ण,
	अणु4, 1024, 0, 252पूर्ण,
	अणु2, 512, 0, 254पूर्ण,
	अणु1, 256, 0, 255पूर्ण
पूर्ण;


अटल पूर्णांक via_fetch_size_agp3(व्योम)
अणु
	पूर्णांक i;
	u16 temp;
	काष्ठा aper_size_info_16 *values;

	values = A_SIZE_16(agp_bridge->driver->aperture_sizes);
	pci_पढ़ो_config_word(agp_bridge->dev, VIA_AGP3_APSIZE, &temp);
	temp &= 0xfff;

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


अटल पूर्णांक via_configure_agp3(व्योम)
अणु
	u32 temp;
	काष्ठा aper_size_info_16 *current_size;

	current_size = A_SIZE_16(agp_bridge->current_size);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture GATT base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_AGP3_ATTBASE,
		agp_bridge->gatt_bus_addr & 0xfffff000);

	/* 1. Enable GTLB in RX90<7>, all AGP aperture access needs to fetch
	 *    translation table first.
	 * 2. Enable AGP aperture in RX91<0>. This bit controls the enabling of the
	 *    graphics AGP aperture क्रम the AGP3.0 port.
	 */
	pci_पढ़ो_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, temp | (3<<7));
	वापस 0;
पूर्ण


अटल व्योम via_cleanup_agp3(व्योम)
अणु
	काष्ठा aper_size_info_16 *previous_size;

	previous_size = A_SIZE_16(agp_bridge->previous_size);
	pci_ग_लिखो_config_byte(agp_bridge->dev, VIA_APSIZE, previous_size->size_value);
पूर्ण


अटल व्योम via_tlbflush_agp3(काष्ठा agp_memory *mem)
अणु
	u32 temp;

	pci_पढ़ो_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, temp & ~(1<<7));
	pci_ग_लिखो_config_dword(agp_bridge->dev, VIA_AGP3_GARTCTRL, temp);
पूर्ण


अटल स्थिर काष्ठा agp_bridge_driver via_agp3_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= agp3_generic_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 10,
	.needs_scratch_page	= true,
	.configure		= via_configure_agp3,
	.fetch_size		= via_fetch_size_agp3,
	.cleanup		= via_cleanup_agp3,
	.tlb_flush		= via_tlbflush_agp3,
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
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver via_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= via_generic_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 9,
	.needs_scratch_page	= true,
	.configure		= via_configure,
	.fetch_size		= via_fetch_size,
	.cleanup		= via_cleanup,
	.tlb_flush		= via_tlbflush,
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
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल काष्ठा agp_device_ids via_agp_device_ids[] =
अणु
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_82C597_0,
		.chipset_name	= "Apollo VP3",
	पूर्ण,

	अणु
		.device_id	= PCI_DEVICE_ID_VIA_82C598_0,
		.chipset_name	= "Apollo MVP3",
	पूर्ण,

	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8501_0,
		.chipset_name	= "Apollo MVP4",
	पूर्ण,

	/* VT8601 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8601_0,
		.chipset_name	= "Apollo ProMedia/PLE133Ta",
	पूर्ण,

	/* VT82C693A / VT28C694T */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_82C691_0,
		.chipset_name	= "Apollo Pro 133",
	पूर्ण,

	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8371_0,
		.chipset_name	= "KX133",
	पूर्ण,

	/* VT8633 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8633_0,
		.chipset_name	= "Pro 266",
	पूर्ण,

	अणु
		.device_id	= PCI_DEVICE_ID_VIA_XN266,
		.chipset_name	= "Apollo Pro266",
	पूर्ण,

	/* VT8361 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8361,
		.chipset_name	= "KLE133",
	पूर्ण,

	/* VT8365 / VT8362 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8363_0,
		.chipset_name	= "Twister-K/KT133x/KM133",
	पूर्ण,

	/* VT8753A */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8753_0,
		.chipset_name	= "P4X266",
	पूर्ण,

	/* VT8366 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8367_0,
		.chipset_name	= "KT266/KY266x/KT333",
	पूर्ण,

	/* VT8633 (क्रम CuMine/ Celeron) */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8653_0,
		.chipset_name	= "Pro266T",
	पूर्ण,

	/* KM266 / PM266 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_XM266,
		.chipset_name	= "PM266/KM266",
	पूर्ण,

	/* CLE266 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_862X_0,
		.chipset_name	= "CLE266",
	पूर्ण,

	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8377_0,
		.chipset_name	= "KT400/KT400A/KT600",
	पूर्ण,

	/* VT8604 / VT8605 / VT8603
	 * (Apollo Pro133A chipset with S3 Savage4) */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8605_0,
		.chipset_name	= "ProSavage PM133/PL133/PN133"
	पूर्ण,

	/* P4M266x/P4N266 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8703_51_0,
		.chipset_name	= "P4M266x/P4N266",
	पूर्ण,

	/* VT8754 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8754C_0,
		.chipset_name	= "PT800",
	पूर्ण,

	/* P4X600 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8763_0,
		.chipset_name	= "P4X600"
	पूर्ण,

	/* KM400 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8378_0,
		.chipset_name	= "KM400/KM400A",
	पूर्ण,

	/* PT880 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_PT880,
		.chipset_name	= "PT880",
	पूर्ण,

	/* PT880 Ultra */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_PT880ULTRA,
		.chipset_name	= "PT880 Ultra",
	पूर्ण,

	/* PT890 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_8783_0,
		.chipset_name	= "PT890",
	पूर्ण,

	/* PM800/PN800/PM880/PN880 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_PX8X0_0,
		.chipset_name	= "PM800/PN800/PM880/PN880",
	पूर्ण,
	/* KT880 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_3269_0,
		.chipset_name	= "KT880",
	पूर्ण,
	/* KTxxx/Px8xx */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_83_87XX_1,
		.chipset_name	= "VT83xx/VT87xx/KTxxx/Px8xx",
	पूर्ण,
	/* P4M800 */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_3296_0,
		.chipset_name	= "P4M800",
	पूर्ण,
	/* P4M800CE */
	अणु
		.device_id	= PCI_DEVICE_ID_VIA_P4M800CE,
		.chipset_name	= "VT3314",
	पूर्ण,
	/* VT3324 / CX700 */
	अणु
		.device_id  = PCI_DEVICE_ID_VIA_VT3324,
		.chipset_name   = "CX700",
	पूर्ण,
	/* VT3336 - this is a chipset क्रम AMD Athlon/K8 CPU. Due to K8's unique
	 * architecture, the AGP resource and behavior are dअगरferent from
	 * the traditional AGP which resides only in chipset. AGP is used
	 * by 3D driver which wasn't available क्रम the VT3336 and VT3364
	 * generation until now.  Unक्रमtunately, by testing, VT3364 works
	 * but VT3336 करोesn't. - explanation from via, just leave this as
	 * as a placeholder to aव्योम future patches adding it back in.
	 */
#अगर 0
	अणु
		.device_id  = PCI_DEVICE_ID_VIA_VT3336,
		.chipset_name   = "VT3336",
	पूर्ण,
#पूर्ण_अगर
	/* P4M890 */
	अणु
		.device_id  = PCI_DEVICE_ID_VIA_P4M890,
		.chipset_name   = "P4M890",
	पूर्ण,
	/* P4M900 */
	अणु
		.device_id  = PCI_DEVICE_ID_VIA_VT3364,
		.chipset_name   = "P4M900",
	पूर्ण,
	अणु पूर्ण, /* dummy final entry, always present */
पूर्ण;


/*
 * VIA's AGP3 chipsets करो magick to put the AGP bridge compliant
 * with the same standards version as the graphics card.
 */
अटल व्योम check_via_agp3 (काष्ठा agp_bridge_data *bridge)
अणु
	u8 reg;

	pci_पढ़ो_config_byte(bridge->dev, VIA_AGPSEL, &reg);
	/* Check AGP 2.0 compatibility mode. */
	अगर ((reg & (1<<1))==0)
		bridge->driver = &via_agp3_driver;
पूर्ण


अटल पूर्णांक agp_via_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_device_ids *devs = via_agp_device_ids;
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक j = 0;
	u8 cap_ptr;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	j = ent - agp_via_pci_table;
	prपूर्णांकk (KERN_INFO PFX "Detected VIA %s chipset\n", devs[j].chipset_name);

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->dev = pdev;
	bridge->capndx = cap_ptr;
	bridge->driver = &via_driver;

	/*
	 * Garg, there are KT400s with KT266 IDs.
	 */
	अगर (pdev->device == PCI_DEVICE_ID_VIA_8367_0) अणु
		/* Is there a KT400 subप्रणाली ? */
		अगर (pdev->subप्रणाली_device == PCI_DEVICE_ID_VIA_8377_0) अणु
			prपूर्णांकk(KERN_INFO PFX "Found KT400 in disguise as a KT266.\n");
			check_via_agp3(bridge);
		पूर्ण
	पूर्ण

	/* If this is an AGP3 bridge, check which mode its in and adjust. */
	get_agp_version(bridge);
	अगर (bridge->major_version >= 3)
		check_via_agp3(bridge);

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev,
			bridge->capndx+PCI_AGP_STATUS, &bridge->mode);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_via_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक agp_via_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	pci_save_state (pdev);
	pci_set_घातer_state (pdev, PCI_D3hot);

	वापस 0;
पूर्ण

अटल पूर्णांक agp_via_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	pci_set_घातer_state (pdev, PCI_D0);
	pci_restore_state(pdev);

	अगर (bridge->driver == &via_agp3_driver)
		वापस via_configure_agp3();
	अन्यथा अगर (bridge->driver == &via_driver)
		वापस via_configure();

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

/* must be the same order as name table above */
अटल स्थिर काष्ठा pci_device_id agp_via_pci_table[] = अणु
#घोषणा ID(x) \
	अणु						\
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),	\
	.class_mask	= ~0,				\
	.venकरोr		= PCI_VENDOR_ID_VIA,		\
	.device		= x,				\
	.subvenकरोr	= PCI_ANY_ID,			\
	.subdevice	= PCI_ANY_ID,			\
	पूर्ण
	ID(PCI_DEVICE_ID_VIA_82C597_0),
	ID(PCI_DEVICE_ID_VIA_82C598_0),
	ID(PCI_DEVICE_ID_VIA_8501_0),
	ID(PCI_DEVICE_ID_VIA_8601_0),
	ID(PCI_DEVICE_ID_VIA_82C691_0),
	ID(PCI_DEVICE_ID_VIA_8371_0),
	ID(PCI_DEVICE_ID_VIA_8633_0),
	ID(PCI_DEVICE_ID_VIA_XN266),
	ID(PCI_DEVICE_ID_VIA_8361),
	ID(PCI_DEVICE_ID_VIA_8363_0),
	ID(PCI_DEVICE_ID_VIA_8753_0),
	ID(PCI_DEVICE_ID_VIA_8367_0),
	ID(PCI_DEVICE_ID_VIA_8653_0),
	ID(PCI_DEVICE_ID_VIA_XM266),
	ID(PCI_DEVICE_ID_VIA_862X_0),
	ID(PCI_DEVICE_ID_VIA_8377_0),
	ID(PCI_DEVICE_ID_VIA_8605_0),
	ID(PCI_DEVICE_ID_VIA_8703_51_0),
	ID(PCI_DEVICE_ID_VIA_8754C_0),
	ID(PCI_DEVICE_ID_VIA_8763_0),
	ID(PCI_DEVICE_ID_VIA_8378_0),
	ID(PCI_DEVICE_ID_VIA_PT880),
	ID(PCI_DEVICE_ID_VIA_PT880ULTRA),
	ID(PCI_DEVICE_ID_VIA_8783_0),
	ID(PCI_DEVICE_ID_VIA_PX8X0_0),
	ID(PCI_DEVICE_ID_VIA_3269_0),
	ID(PCI_DEVICE_ID_VIA_83_87XX_1),
	ID(PCI_DEVICE_ID_VIA_3296_0),
	ID(PCI_DEVICE_ID_VIA_P4M800CE),
	ID(PCI_DEVICE_ID_VIA_VT3324),
	ID(PCI_DEVICE_ID_VIA_P4M890),
	ID(PCI_DEVICE_ID_VIA_VT3364),
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_via_pci_table);


अटल काष्ठा pci_driver agp_via_pci_driver = अणु
	.name		= "agpgart-via",
	.id_table	= agp_via_pci_table,
	.probe		= agp_via_probe,
	.हटाओ		= agp_via_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_via_suspend,
	.resume		= agp_via_resume,
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक __init agp_via_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_via_pci_driver);
पूर्ण

अटल व्योम __निकास agp_via_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_via_pci_driver);
पूर्ण

module_init(agp_via_init);
module_निकास(agp_via_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dave Jones");
