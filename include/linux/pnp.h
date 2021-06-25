<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Linux Plug and Play Support
 * Copyright by Adam Belay <ambx1@neo.rr.com>
 * Copyright (C) 2008 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 */

#अगर_अघोषित _LINUX_PNP_H
#घोषणा _LINUX_PNP_H

#समावेश <linux/device.h>
#समावेश <linux/list.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/console.h>

#घोषणा PNP_NAME_LEN		50

काष्ठा pnp_protocol;
काष्ठा pnp_dev;

/*
 * Resource Management
 */
#अगर_घोषित CONFIG_PNP
काष्ठा resource *pnp_get_resource(काष्ठा pnp_dev *dev, अचिन्हित दीर्घ type,
				अचिन्हित पूर्णांक num);
#अन्यथा
अटल अंतरभूत काष्ठा resource *pnp_get_resource(काष्ठा pnp_dev *dev,
			अचिन्हित दीर्घ type, अचिन्हित पूर्णांक num)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक pnp_resource_valid(काष्ठा resource *res)
अणु
	अगर (res)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक pnp_resource_enabled(काष्ठा resource *res)
अणु
	अगर (res && !(res->flags & IORESOURCE_DISABLED))
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत resource_माप_प्रकार pnp_resource_len(काष्ठा resource *res)
अणु
	अगर (res->start == 0 && res->end == 0)
		वापस 0;
	वापस resource_size(res);
पूर्ण


अटल अंतरभूत resource_माप_प्रकार pnp_port_start(काष्ठा pnp_dev *dev,
					     अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_IO, bar);

	अगर (pnp_resource_valid(res))
		वापस res->start;
	वापस 0;
पूर्ण

अटल अंतरभूत resource_माप_प्रकार pnp_port_end(काष्ठा pnp_dev *dev,
					   अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_IO, bar);

	अगर (pnp_resource_valid(res))
		वापस res->end;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pnp_port_flags(काष्ठा pnp_dev *dev,
					   अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_IO, bar);

	अगर (pnp_resource_valid(res))
		वापस res->flags;
	वापस IORESOURCE_IO | IORESOURCE_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक pnp_port_valid(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	वापस pnp_resource_valid(pnp_get_resource(dev, IORESOURCE_IO, bar));
पूर्ण

अटल अंतरभूत resource_माप_प्रकार pnp_port_len(काष्ठा pnp_dev *dev,
					   अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_IO, bar);

	अगर (pnp_resource_valid(res))
		वापस pnp_resource_len(res);
	वापस 0;
पूर्ण


अटल अंतरभूत resource_माप_प्रकार pnp_mem_start(काष्ठा pnp_dev *dev,
					    अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_MEM, bar);

	अगर (pnp_resource_valid(res))
		वापस res->start;
	वापस 0;
पूर्ण

अटल अंतरभूत resource_माप_प्रकार pnp_mem_end(काष्ठा pnp_dev *dev,
					  अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_MEM, bar);

	अगर (pnp_resource_valid(res))
		वापस res->end;
	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pnp_mem_flags(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_MEM, bar);

	अगर (pnp_resource_valid(res))
		वापस res->flags;
	वापस IORESOURCE_MEM | IORESOURCE_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक pnp_mem_valid(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	वापस pnp_resource_valid(pnp_get_resource(dev, IORESOURCE_MEM, bar));
पूर्ण

अटल अंतरभूत resource_माप_प्रकार pnp_mem_len(काष्ठा pnp_dev *dev,
					  अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_MEM, bar);

	अगर (pnp_resource_valid(res))
		वापस pnp_resource_len(res);
	वापस 0;
पूर्ण


अटल अंतरभूत resource_माप_प्रकार pnp_irq(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_IRQ, bar);

	अगर (pnp_resource_valid(res))
		वापस res->start;
	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pnp_irq_flags(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_IRQ, bar);

	अगर (pnp_resource_valid(res))
		वापस res->flags;
	वापस IORESOURCE_IRQ | IORESOURCE_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक pnp_irq_valid(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	वापस pnp_resource_valid(pnp_get_resource(dev, IORESOURCE_IRQ, bar));
पूर्ण


अटल अंतरभूत resource_माप_प्रकार pnp_dma(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_DMA, bar);

	अगर (pnp_resource_valid(res))
		वापस res->start;
	वापस -1;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ pnp_dma_flags(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	काष्ठा resource *res = pnp_get_resource(dev, IORESOURCE_DMA, bar);

	अगर (pnp_resource_valid(res))
		वापस res->flags;
	वापस IORESOURCE_DMA | IORESOURCE_AUTO;
पूर्ण

अटल अंतरभूत पूर्णांक pnp_dma_valid(काष्ठा pnp_dev *dev, अचिन्हित पूर्णांक bar)
अणु
	वापस pnp_resource_valid(pnp_get_resource(dev, IORESOURCE_DMA, bar));
पूर्ण


/*
 * Device Management
 */

काष्ठा pnp_card अणु
	काष्ठा device dev;		/* Driver Model device पूर्णांकerface */
	अचिन्हित अक्षर number;		/* used as an index, must be unique */
	काष्ठा list_head global_list;	/* node in global list of cards */
	काष्ठा list_head protocol_list;	/* node in protocol's list of cards */
	काष्ठा list_head devices;	/* devices attached to the card */

	काष्ठा pnp_protocol *protocol;
	काष्ठा pnp_id *id;		/* contains supported EISA IDs */

	अक्षर name[PNP_NAME_LEN];	/* contains a human-पढ़ोable name */
	अचिन्हित अक्षर pnpver;		/* Plug & Play version */
	अचिन्हित अक्षर productver;	/* product version */
	अचिन्हित पूर्णांक serial;		/* serial number */
	अचिन्हित अक्षर checksum;		/* अगर zero - checksum passed */
	काष्ठा proc_dir_entry *procdir;	/* directory entry in /proc/bus/isapnp */
पूर्ण;

#घोषणा global_to_pnp_card(n) list_entry(n, काष्ठा pnp_card, global_list)
#घोषणा protocol_to_pnp_card(n) list_entry(n, काष्ठा pnp_card, protocol_list)
#घोषणा to_pnp_card(n) container_of(n, काष्ठा pnp_card, dev)
#घोषणा pnp_क्रम_each_card(card)	\
	list_क्रम_each_entry(card, &pnp_cards, global_list)

काष्ठा pnp_card_link अणु
	काष्ठा pnp_card *card;
	काष्ठा pnp_card_driver *driver;
	व्योम *driver_data;
	pm_message_t pm_state;
पूर्ण;

अटल अंतरभूत व्योम *pnp_get_card_drvdata(काष्ठा pnp_card_link *pcard)
अणु
	वापस pcard->driver_data;
पूर्ण

अटल अंतरभूत व्योम pnp_set_card_drvdata(काष्ठा pnp_card_link *pcard, व्योम *data)
अणु
	pcard->driver_data = data;
पूर्ण

काष्ठा pnp_dev अणु
	काष्ठा device dev;		/* Driver Model device पूर्णांकerface */
	u64 dma_mask;
	अचिन्हित पूर्णांक number;		/* used as an index, must be unique */
	पूर्णांक status;

	काष्ठा list_head global_list;	/* node in global list of devices */
	काष्ठा list_head protocol_list;	/* node in list of device's protocol */
	काष्ठा list_head card_list;	/* node in card's list of devices */
	काष्ठा list_head rdev_list;	/* node in cards list of requested devices */

	काष्ठा pnp_protocol *protocol;
	काष्ठा pnp_card *card;	/* card the device is attached to, none अगर शून्य */
	काष्ठा pnp_driver *driver;
	काष्ठा pnp_card_link *card_link;

	काष्ठा pnp_id *id;		/* supported EISA IDs */

	पूर्णांक active;
	पूर्णांक capabilities;
	अचिन्हित पूर्णांक num_dependent_sets;
	काष्ठा list_head resources;
	काष्ठा list_head options;

	अक्षर name[PNP_NAME_LEN];	/* contains a human-पढ़ोable name */
	पूर्णांक flags;			/* used by protocols */
	काष्ठा proc_dir_entry *procent;	/* device entry in /proc/bus/isapnp */
	व्योम *data;
पूर्ण;

#घोषणा global_to_pnp_dev(n) list_entry(n, काष्ठा pnp_dev, global_list)
#घोषणा card_to_pnp_dev(n) list_entry(n, काष्ठा pnp_dev, card_list)
#घोषणा protocol_to_pnp_dev(n) list_entry(n, काष्ठा pnp_dev, protocol_list)
#घोषणा	to_pnp_dev(n) container_of(n, काष्ठा pnp_dev, dev)
#घोषणा pnp_क्रम_each_dev(dev) list_क्रम_each_entry(dev, &pnp_global, global_list)
#घोषणा card_क्रम_each_dev(card, dev)	\
	list_क्रम_each_entry(dev, &(card)->devices, card_list)
#घोषणा pnp_dev_name(dev) (dev)->name

अटल अंतरभूत व्योम *pnp_get_drvdata(काष्ठा pnp_dev *pdev)
अणु
	वापस dev_get_drvdata(&pdev->dev);
पूर्ण

अटल अंतरभूत व्योम pnp_set_drvdata(काष्ठा pnp_dev *pdev, व्योम *data)
अणु
	dev_set_drvdata(&pdev->dev, data);
पूर्ण

काष्ठा pnp_fixup अणु
	अक्षर id[7];
	व्योम (*quirk_function) (काष्ठा pnp_dev * dev);	/* fixup function */
पूर्ण;

/* config parameters */
#घोषणा PNP_CONFIG_NORMAL	0x0001
#घोषणा PNP_CONFIG_FORCE	0x0002	/* disables validity checking */

/* capabilities */
#घोषणा PNP_READ		0x0001
#घोषणा PNP_WRITE		0x0002
#घोषणा PNP_DISABLE		0x0004
#घोषणा PNP_CONFIGURABLE	0x0008
#घोषणा PNP_REMOVABLE		0x0010
#घोषणा PNP_CONSOLE		0x0020

#घोषणा pnp_can_पढ़ो(dev)	(((dev)->protocol->get) && \
				 ((dev)->capabilities & PNP_READ))
#घोषणा pnp_can_ग_लिखो(dev)	(((dev)->protocol->set) && \
				 ((dev)->capabilities & PNP_WRITE))
#घोषणा pnp_can_disable(dev)	(((dev)->protocol->disable) &&		  \
				 ((dev)->capabilities & PNP_DISABLE) &&	  \
				 (!((dev)->capabilities & PNP_CONSOLE) || \
				  console_suspend_enabled))
#घोषणा pnp_can_configure(dev)	((!(dev)->active) && \
				 ((dev)->capabilities & PNP_CONFIGURABLE))
#घोषणा pnp_can_suspend(dev)	(((dev)->protocol->suspend) &&		  \
				 (!((dev)->capabilities & PNP_CONSOLE) || \
				  console_suspend_enabled))


#अगर_घोषित CONFIG_ISAPNP
बाह्य काष्ठा pnp_protocol isapnp_protocol;
#घोषणा pnp_device_is_isapnp(dev) ((dev)->protocol == (&isapnp_protocol))
#अन्यथा
#घोषणा pnp_device_is_isapnp(dev) 0
#पूर्ण_अगर
बाह्य काष्ठा mutex pnp_res_mutex;

#अगर_घोषित CONFIG_PNPBIOS
बाह्य काष्ठा pnp_protocol pnpbios_protocol;
बाह्य bool arch_pnpbios_disabled(व्योम);
#घोषणा pnp_device_is_pnpbios(dev) ((dev)->protocol == (&pnpbios_protocol))
#अन्यथा
#घोषणा pnp_device_is_pnpbios(dev) 0
#घोषणा arch_pnpbios_disabled()	false
#पूर्ण_अगर

#अगर_घोषित CONFIG_PNPACPI
बाह्य काष्ठा pnp_protocol pnpacpi_protocol;

अटल अंतरभूत काष्ठा acpi_device *pnp_acpi_device(काष्ठा pnp_dev *dev)
अणु
	अगर (dev->protocol == &pnpacpi_protocol)
		वापस dev->data;
	वापस शून्य;
पूर्ण
#अन्यथा
#घोषणा pnp_acpi_device(dev) 0
#पूर्ण_अगर

/* status */
#घोषणा PNP_READY		0x0000
#घोषणा PNP_ATTACHED		0x0001
#घोषणा PNP_BUSY		0x0002
#घोषणा PNP_FAULTY		0x0004

/* isapnp specअगरic macros */

#घोषणा isapnp_card_number(dev)	((dev)->card ? (dev)->card->number : -1)
#घोषणा isapnp_csn_number(dev)  ((dev)->number)

/*
 * Driver Management
 */

काष्ठा pnp_id अणु
	अक्षर id[PNP_ID_LEN];
	काष्ठा pnp_id *next;
पूर्ण;

काष्ठा pnp_driver अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा pnp_device_id *id_table;
	अचिन्हित पूर्णांक flags;
	पूर्णांक (*probe) (काष्ठा pnp_dev *dev, स्थिर काष्ठा pnp_device_id *dev_id);
	व्योम (*हटाओ) (काष्ठा pnp_dev *dev);
	व्योम (*shutकरोwn) (काष्ठा pnp_dev *dev);
	पूर्णांक (*suspend) (काष्ठा pnp_dev *dev, pm_message_t state);
	पूर्णांक (*resume) (काष्ठा pnp_dev *dev);
	काष्ठा device_driver driver;
पूर्ण;

#घोषणा	to_pnp_driver(drv) container_of(drv, काष्ठा pnp_driver, driver)

काष्ठा pnp_card_driver अणु
	काष्ठा list_head global_list;
	अक्षर *name;
	स्थिर काष्ठा pnp_card_device_id *id_table;
	अचिन्हित पूर्णांक flags;
	पूर्णांक (*probe) (काष्ठा pnp_card_link *card,
		      स्थिर काष्ठा pnp_card_device_id *card_id);
	व्योम (*हटाओ) (काष्ठा pnp_card_link *card);
	पूर्णांक (*suspend) (काष्ठा pnp_card_link *card, pm_message_t state);
	पूर्णांक (*resume) (काष्ठा pnp_card_link *card);
	काष्ठा pnp_driver link;
पूर्ण;

#घोषणा	to_pnp_card_driver(drv) container_of(drv, काष्ठा pnp_card_driver, link)

/* pnp driver flags */
#घोषणा PNP_DRIVER_RES_DO_NOT_CHANGE	0x0001	/* करो not change the state of the device */
#घोषणा PNP_DRIVER_RES_DISABLE		0x0003	/* ensure the device is disabled */

/*
 * Protocol Management
 */

काष्ठा pnp_protocol अणु
	काष्ठा list_head protocol_list;
	अक्षर *name;

	/* resource control functions */
	पूर्णांक (*get) (काष्ठा pnp_dev *dev);
	पूर्णांक (*set) (काष्ठा pnp_dev *dev);
	पूर्णांक (*disable) (काष्ठा pnp_dev *dev);

	/* protocol specअगरic suspend/resume */
	bool (*can_wakeup) (काष्ठा pnp_dev *dev);
	पूर्णांक (*suspend) (काष्ठा pnp_dev * dev, pm_message_t state);
	पूर्णांक (*resume) (काष्ठा pnp_dev * dev);

	/* used by pnp layer only (look but करोn't touch) */
	अचिन्हित अक्षर number;	/* protocol number */
	काष्ठा device dev;	/* link to driver model */
	काष्ठा list_head cards;
	काष्ठा list_head devices;
पूर्ण;

#घोषणा to_pnp_protocol(n) list_entry(n, काष्ठा pnp_protocol, protocol_list)
#घोषणा protocol_क्रम_each_card(protocol, card)	\
	list_क्रम_each_entry(card, &(protocol)->cards, protocol_list)
#घोषणा protocol_क्रम_each_dev(protocol, dev)	\
	list_क्रम_each_entry(dev, &(protocol)->devices, protocol_list)

बाह्य काष्ठा bus_type pnp_bus_type;

#अगर defined(CONFIG_PNP)

/* device management */
पूर्णांक pnp_device_attach(काष्ठा pnp_dev *pnp_dev);
व्योम pnp_device_detach(काष्ठा pnp_dev *pnp_dev);
बाह्य काष्ठा list_head pnp_global;
बाह्य पूर्णांक pnp_platक्रमm_devices;

/* multidevice card support */
काष्ठा pnp_dev *pnp_request_card_device(काष्ठा pnp_card_link *clink,
					स्थिर अक्षर *id, काष्ठा pnp_dev *from);
व्योम pnp_release_card_device(काष्ठा pnp_dev *dev);
पूर्णांक pnp_रेजिस्टर_card_driver(काष्ठा pnp_card_driver *drv);
व्योम pnp_unरेजिस्टर_card_driver(काष्ठा pnp_card_driver *drv);
बाह्य काष्ठा list_head pnp_cards;

/* resource management */
पूर्णांक pnp_possible_config(काष्ठा pnp_dev *dev, पूर्णांक type, resource_माप_प्रकार base,
			resource_माप_प्रकार size);
पूर्णांक pnp_स्वतः_config_dev(काष्ठा pnp_dev *dev);
पूर्णांक pnp_start_dev(काष्ठा pnp_dev *dev);
पूर्णांक pnp_stop_dev(काष्ठा pnp_dev *dev);
पूर्णांक pnp_activate_dev(काष्ठा pnp_dev *dev);
पूर्णांक pnp_disable_dev(काष्ठा pnp_dev *dev);
पूर्णांक pnp_range_reserved(resource_माप_प्रकार start, resource_माप_प्रकार end);

/* protocol helpers */
पूर्णांक pnp_is_active(काष्ठा pnp_dev *dev);
पूर्णांक compare_pnp_id(काष्ठा pnp_id *pos, स्थिर अक्षर *id);
पूर्णांक pnp_रेजिस्टर_driver(काष्ठा pnp_driver *drv);
व्योम pnp_unरेजिस्टर_driver(काष्ठा pnp_driver *drv);

#अन्यथा

/* device management */
अटल अंतरभूत पूर्णांक pnp_device_attach(काष्ठा pnp_dev *pnp_dev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम pnp_device_detach(काष्ठा pnp_dev *pnp_dev) अणु पूर्ण

#घोषणा pnp_platक्रमm_devices 0

/* multidevice card support */
अटल अंतरभूत काष्ठा pnp_dev *pnp_request_card_device(काष्ठा pnp_card_link *clink, स्थिर अक्षर *id, काष्ठा pnp_dev *from) अणु वापस शून्य; पूर्ण
अटल अंतरभूत व्योम pnp_release_card_device(काष्ठा pnp_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक pnp_रेजिस्टर_card_driver(काष्ठा pnp_card_driver *drv) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम pnp_unरेजिस्टर_card_driver(काष्ठा pnp_card_driver *drv) अणु पूर्ण

/* resource management */
अटल अंतरभूत पूर्णांक pnp_possible_config(काष्ठा pnp_dev *dev, पूर्णांक type,
				      resource_माप_प्रकार base,
				      resource_माप_प्रकार size) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक pnp_स्वतः_config_dev(काष्ठा pnp_dev *dev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pnp_start_dev(काष्ठा pnp_dev *dev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pnp_stop_dev(काष्ठा pnp_dev *dev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pnp_activate_dev(काष्ठा pnp_dev *dev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pnp_disable_dev(काष्ठा pnp_dev *dev) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pnp_range_reserved(resource_माप_प्रकार start, resource_माप_प्रकार end) अणु वापस 0;पूर्ण

/* protocol helpers */
अटल अंतरभूत पूर्णांक pnp_is_active(काष्ठा pnp_dev *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक compare_pnp_id(काष्ठा pnp_id *pos, स्थिर अक्षर *id) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत पूर्णांक pnp_रेजिस्टर_driver(काष्ठा pnp_driver *drv) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम pnp_unरेजिस्टर_driver(काष्ठा pnp_driver *drv) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_PNP */

/**
 * module_pnp_driver() - Helper macro क्रम रेजिस्टरing a PnP driver
 * @__pnp_driver: pnp_driver काष्ठा
 *
 * Helper macro क्रम PnP drivers which करो not करो anything special in module
 * init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_pnp_driver(__pnp_driver) \
	module_driver(__pnp_driver, pnp_रेजिस्टर_driver, \
				    pnp_unरेजिस्टर_driver)

#पूर्ण_अगर /* _LINUX_PNP_H */
