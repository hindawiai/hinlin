<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_EISA_H
#घोषणा _LINUX_EISA_H

#समावेश <linux/ioport.h>
#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

#घोषणा EISA_MAX_SLOTS 8

#घोषणा EISA_MAX_RESOURCES 4

/* A few EISA स्थिरants/offsets... */

#घोषणा EISA_DMA1_STATUS            8
#घोषणा EISA_INT1_CTRL           0x20
#घोषणा EISA_INT1_MASK           0x21
#घोषणा EISA_INT2_CTRL           0xA0
#घोषणा EISA_INT2_MASK           0xA1
#घोषणा EISA_DMA2_STATUS         0xD0
#घोषणा EISA_DMA2_WRITE_SINGLE   0xD4
#घोषणा EISA_EXT_NMI_RESET_CTRL 0x461
#घोषणा EISA_INT1_EDGE_LEVEL    0x4D0
#घोषणा EISA_INT2_EDGE_LEVEL    0x4D1
#घोषणा EISA_VENDOR_ID_OFFSET   0xC80
#घोषणा EISA_CONFIG_OFFSET      0xC84

#घोषणा EISA_CONFIG_ENABLED         1
#घोषणा EISA_CONFIG_FORCED          2

/* There is not much we can say about an EISA device, apart from
 * signature, slot number, and base address. dma_mask is set by
 * शेष to parent device mask..*/

काष्ठा eisa_device अणु
	काष्ठा eisa_device_id id;
	पूर्णांक                   slot;
	पूर्णांक                   state;
	अचिन्हित दीर्घ         base_addr;
	काष्ठा resource       res[EISA_MAX_RESOURCES];
	u64                   dma_mask;
	काष्ठा device         dev; /* generic device */
#अगर_घोषित CONFIG_EISA_NAMES
	अक्षर		      pretty_name[50];
#पूर्ण_अगर
पूर्ण;

#घोषणा to_eisa_device(n) container_of(n, काष्ठा eisa_device, dev)

अटल अंतरभूत पूर्णांक eisa_get_region_index (व्योम *addr)
अणु
	अचिन्हित दीर्घ x = (अचिन्हित दीर्घ) addr;

	x &= 0xc00;
	वापस (x >> 12);
पूर्ण

काष्ठा eisa_driver अणु
	स्थिर काष्ठा eisa_device_id *id_table;
	काष्ठा device_driver         driver;
पूर्ण;

#घोषणा to_eisa_driver(drv) container_of(drv,काष्ठा eisa_driver, driver)

/* These बाह्यal functions are only available when EISA support is enabled. */
#अगर_घोषित CONFIG_EISA

बाह्य काष्ठा bus_type eisa_bus_type;
पूर्णांक eisa_driver_रेजिस्टर (काष्ठा eisa_driver *edrv);
व्योम eisa_driver_unरेजिस्टर (काष्ठा eisa_driver *edrv);

#अन्यथा /* !CONFIG_EISA */

अटल अंतरभूत पूर्णांक eisa_driver_रेजिस्टर (काष्ठा eisa_driver *edrv) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम eisa_driver_unरेजिस्टर (काष्ठा eisa_driver *edrv) अणु पूर्ण

#पूर्ण_अगर /* !CONFIG_EISA */

/* Mimics pci.h... */
अटल अंतरभूत व्योम *eisa_get_drvdata (काष्ठा eisa_device *edev)
अणु
        वापस dev_get_drvdata(&edev->dev);
पूर्ण

अटल अंतरभूत व्योम eisa_set_drvdata (काष्ठा eisa_device *edev, व्योम *data)
अणु
        dev_set_drvdata(&edev->dev, data);
पूर्ण

/* The EISA root device. There's rumours about machines with multiple
 * busses (PA-RISC ?), so we try to handle that. */

काष्ठा eisa_root_device अणु
	काष्ठा device   *dev;	 /* Poपूर्णांकer to bridge device */
	काष्ठा resource *res;
	अचिन्हित दीर्घ    bus_base_addr;
	पूर्णांक		 slots;  /* Max slot number */
	पूर्णांक		 क्रमce_probe; /* Probe even when no slot 0 */
	u64		 dma_mask; /* from bridge device */
	पूर्णांक              bus_nr; /* Set by eisa_root_रेजिस्टर */
	काष्ठा resource  eisa_root_res;	/* ditto */
पूर्ण;

पूर्णांक eisa_root_रेजिस्टर (काष्ठा eisa_root_device *root);

#अगर_घोषित CONFIG_EISA
बाह्य पूर्णांक EISA_bus;
#अन्यथा
# define EISA_bus 0
#पूर्ण_अगर

#पूर्ण_अगर
