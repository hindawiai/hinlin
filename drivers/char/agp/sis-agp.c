<शैली गुरु>
/*
 * SiS AGPGART routines.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/delay.h>
#समावेश "agp.h"

#घोषणा SIS_ATTBASE	0x90
#घोषणा SIS_APSIZE	0x94
#घोषणा SIS_TLBCNTRL	0x97
#घोषणा SIS_TLBFLUSH	0x98

#घोषणा PCI_DEVICE_ID_SI_662	0x0662
#घोषणा PCI_DEVICE_ID_SI_671	0x0671

अटल bool agp_sis_क्रमce_delay = 0;
अटल पूर्णांक agp_sis_agp_spec = -1;

अटल पूर्णांक sis_fetch_size(व्योम)
अणु
	u8 temp_size;
	पूर्णांक i;
	काष्ठा aper_size_info_8 *values;

	pci_पढ़ो_config_byte(agp_bridge->dev, SIS_APSIZE, &temp_size);
	values = A_SIZE_8(agp_bridge->driver->aperture_sizes);
	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर ((temp_size == values[i].size_value) ||
		    ((temp_size & ~(0x07)) ==
		     (values[i].size_value & ~(0x07)))) अणु
			agp_bridge->previous_size =
			    agp_bridge->current_size = (व्योम *) (values + i);

			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sis_tlbflush(काष्ठा agp_memory *mem)
अणु
	pci_ग_लिखो_config_byte(agp_bridge->dev, SIS_TLBFLUSH, 0x02);
पूर्ण

अटल पूर्णांक sis_configure(व्योम)
अणु
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);
	pci_ग_लिखो_config_byte(agp_bridge->dev, SIS_TLBCNTRL, 0x05);
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);
	pci_ग_लिखो_config_dword(agp_bridge->dev, SIS_ATTBASE,
			       agp_bridge->gatt_bus_addr);
	pci_ग_लिखो_config_byte(agp_bridge->dev, SIS_APSIZE,
			      current_size->size_value);
	वापस 0;
पूर्ण

अटल व्योम sis_cleanup(व्योम)
अणु
	काष्ठा aper_size_info_8 *previous_size;

	previous_size = A_SIZE_8(agp_bridge->previous_size);
	pci_ग_लिखो_config_byte(agp_bridge->dev, SIS_APSIZE,
			      (previous_size->size_value & ~(0x03)));
पूर्ण

अटल व्योम sis_delayed_enable(काष्ठा agp_bridge_data *bridge, u32 mode)
अणु
	काष्ठा pci_dev *device = शून्य;
	u32 command;
	पूर्णांक rate;

	dev_info(&agp_bridge->dev->dev, "AGP %d.%d bridge\n",
		 agp_bridge->major_version, agp_bridge->minor_version);

	pci_पढ़ो_config_dword(agp_bridge->dev, agp_bridge->capndx + PCI_AGP_STATUS, &command);
	command = agp_collect_device_status(bridge, mode, command);
	command |= AGPSTAT_AGP_ENABLE;
	rate = (command & 0x7) << 2;

	क्रम_each_pci_dev(device) अणु
		u8 agp = pci_find_capability(device, PCI_CAP_ID_AGP);
		अगर (!agp)
			जारी;

		dev_info(&agp_bridge->dev->dev, "putting AGP V3 device at %s into %dx mode\n",
			 pci_name(device), rate);

		pci_ग_लिखो_config_dword(device, agp + PCI_AGP_COMMAND, command);

		/*
		 * Weird: on some sis chipsets any rate change in the target
		 * command रेजिस्टर triggers a 5ms screwup during which the master
		 * cannot be configured
		 */
		अगर (device->device == bridge->dev->device) अणु
			dev_info(&agp_bridge->dev->dev, "SiS delay workaround: giving bridge time to recover\n");
			msleep(10);
		पूर्ण
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा aper_size_info_8 sis_generic_sizes[7] =
अणु
	अणु256, 65536, 6, 99पूर्ण,
	अणु128, 32768, 5, 83पूर्ण,
	अणु64, 16384, 4, 67पूर्ण,
	अणु32, 8192, 3, 51पूर्ण,
	अणु16, 4096, 2, 35पूर्ण,
	अणु8, 2048, 1, 19पूर्ण,
	अणु4, 1024, 0, 3पूर्ण
पूर्ण;

अटल काष्ठा agp_bridge_driver sis_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= sis_generic_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= sis_configure,
	.fetch_size		= sis_fetch_size,
	.cleanup		= sis_cleanup,
	.tlb_flush		= sis_tlbflush,
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

// chipsets that require the 'delay hack'
अटल पूर्णांक sis_broken_chipsets[] = अणु
	PCI_DEVICE_ID_SI_648,
	PCI_DEVICE_ID_SI_746,
	0 // terminator
पूर्ण;

अटल व्योम sis_get_driver(काष्ठा agp_bridge_data *bridge)
अणु
	पूर्णांक i;

	क्रम (i=0; sis_broken_chipsets[i]!=0; ++i)
		अगर (bridge->dev->device==sis_broken_chipsets[i])
			अवरोध;

	अगर (sis_broken_chipsets[i] || agp_sis_क्रमce_delay)
		sis_driver.agp_enable=sis_delayed_enable;

	// sis chipsets that indicate less than agp3.5
	// are not actually fully agp3 compliant
	अगर ((agp_bridge->major_version == 3 && agp_bridge->minor_version >= 5
	     && agp_sis_agp_spec!=0) || agp_sis_agp_spec==1) अणु
		sis_driver.aperture_sizes = agp3_generic_sizes;
		sis_driver.माप_प्रकारype = U16_APER_SIZE;
		sis_driver.num_aperture_sizes = AGP_GENERIC_SIZES_ENTRIES;
		sis_driver.configure = agp3_generic_configure;
		sis_driver.fetch_size = agp3_generic_fetch_size;
		sis_driver.cleanup = agp3_generic_cleanup;
		sis_driver.tlb_flush = agp3_generic_tlbflush;
	पूर्ण
पूर्ण


अटल पूर्णांक agp_sis_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;


	dev_info(&pdev->dev, "SiS chipset [%04x/%04x]\n",
		 pdev->venकरोr, pdev->device);
	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->driver = &sis_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	get_agp_version(bridge);

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev, bridge->capndx+PCI_AGP_STATUS, &bridge->mode);
	sis_get_driver(bridge);

	pci_set_drvdata(pdev, bridge);
	वापस agp_add_bridge(bridge);
पूर्ण

अटल व्योम agp_sis_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक agp_sis_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	pci_save_state(pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

अटल पूर्णांक agp_sis_resume(काष्ठा pci_dev *pdev)
अणु
	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	वापस sis_driver.configure();
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id agp_sis_pci_table[] = अणु
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_5591,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_530,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_540,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_550,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_620,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_630,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_635,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_645,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_646,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_648,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_650,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_651,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_655,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_661,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_662,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_671,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_730,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_735,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_740,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_741,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_745,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
		.class		= (PCI_CLASS_BRIDGE_HOST << 8),
		.class_mask	= ~0,
		.venकरोr		= PCI_VENDOR_ID_SI,
		.device		= PCI_DEVICE_ID_SI_746,
		.subvenकरोr	= PCI_ANY_ID,
		.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_sis_pci_table);

अटल काष्ठा pci_driver agp_sis_pci_driver = अणु
	.name		= "agpgart-sis",
	.id_table	= agp_sis_pci_table,
	.probe		= agp_sis_probe,
	.हटाओ		= agp_sis_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_sis_suspend,
	.resume		= agp_sis_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init agp_sis_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_sis_pci_driver);
पूर्ण

अटल व्योम __निकास agp_sis_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_sis_pci_driver);
पूर्ण

module_init(agp_sis_init);
module_निकास(agp_sis_cleanup);

module_param(agp_sis_क्रमce_delay, bool, 0);
MODULE_PARM_DESC(agp_sis_क्रमce_delay,"forces sis delay hack");
module_param(agp_sis_agp_spec, पूर्णांक, 0);
MODULE_PARM_DESC(agp_sis_agp_spec,"0=force sis init, 1=force generic agp3 init, default: autodetect");
MODULE_LICENSE("GPL and additional rights");
