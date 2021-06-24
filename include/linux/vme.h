<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VME_H_
#घोषणा _VME_H_

/* Resource Type */
क्रमागत vme_resource_type अणु
	VME_MASTER,
	VME_SLAVE,
	VME_DMA,
	VME_LM
पूर्ण;

/* VME Address Spaces */
#घोषणा VME_A16		0x1
#घोषणा VME_A24		0x2
#घोषणा	VME_A32		0x4
#घोषणा VME_A64		0x8
#घोषणा VME_CRCSR	0x10
#घोषणा VME_USER1	0x20
#घोषणा VME_USER2	0x40
#घोषणा VME_USER3	0x80
#घोषणा VME_USER4	0x100

#घोषणा VME_A16_MAX	0x10000ULL
#घोषणा VME_A24_MAX	0x1000000ULL
#घोषणा VME_A32_MAX	0x100000000ULL
#घोषणा VME_A64_MAX	0x10000000000000000ULL
#घोषणा VME_CRCSR_MAX	0x1000000ULL


/* VME Cycle Types */
#घोषणा VME_SCT		0x1
#घोषणा VME_BLT		0x2
#घोषणा VME_MBLT	0x4
#घोषणा VME_2eVME	0x8
#घोषणा VME_2eSST	0x10
#घोषणा VME_2eSSTB	0x20

#घोषणा VME_2eSST160	0x100
#घोषणा VME_2eSST267	0x200
#घोषणा VME_2eSST320	0x400

#घोषणा	VME_SUPER	0x1000
#घोषणा	VME_USER	0x2000
#घोषणा	VME_PROG	0x4000
#घोषणा	VME_DATA	0x8000

/* VME Data Widths */
#घोषणा VME_D8		0x1
#घोषणा VME_D16		0x2
#घोषणा VME_D32		0x4
#घोषणा VME_D64		0x8

/* Arbitration Scheduling Modes */
#घोषणा VME_R_ROBIN_MODE	0x1
#घोषणा VME_PRIORITY_MODE	0x2

#घोषणा VME_DMA_PATTERN			(1<<0)
#घोषणा VME_DMA_PCI			(1<<1)
#घोषणा VME_DMA_VME			(1<<2)

#घोषणा VME_DMA_PATTERN_BYTE		(1<<0)
#घोषणा VME_DMA_PATTERN_WORD		(1<<1)
#घोषणा VME_DMA_PATTERN_INCREMENT	(1<<2)

#घोषणा VME_DMA_VME_TO_MEM		(1<<0)
#घोषणा VME_DMA_MEM_TO_VME		(1<<1)
#घोषणा VME_DMA_VME_TO_VME		(1<<2)
#घोषणा VME_DMA_MEM_TO_MEM		(1<<3)
#घोषणा VME_DMA_PATTERN_TO_VME		(1<<4)
#घोषणा VME_DMA_PATTERN_TO_MEM		(1<<5)

काष्ठा vme_dma_attr अणु
	u32 type;
	व्योम *निजी;
पूर्ण;

काष्ठा vme_resource अणु
	क्रमागत vme_resource_type type;
	काष्ठा list_head *entry;
पूर्ण;

बाह्य काष्ठा bus_type vme_bus_type;

/* Number of VME पूर्णांकerrupt vectors */
#घोषणा VME_NUM_STATUSID	256

/* VME_MAX_BRIDGES comes from the type of vme_bus_numbers */
#घोषणा VME_MAX_BRIDGES		(माप(अचिन्हित पूर्णांक)*8)
#घोषणा VME_MAX_SLOTS		32

#घोषणा VME_SLOT_CURRENT	-1
#घोषणा VME_SLOT_ALL		-2

/**
 * काष्ठा vme_dev - Structure representing a VME device
 * @num: The device number
 * @bridge: Poपूर्णांकer to the bridge device this device is on
 * @dev: Internal device काष्ठाure
 * @drv_list: List of devices (per driver)
 * @bridge_list: List of devices (per bridge)
 */
काष्ठा vme_dev अणु
	पूर्णांक num;
	काष्ठा vme_bridge *bridge;
	काष्ठा device dev;
	काष्ठा list_head drv_list;
	काष्ठा list_head bridge_list;
पूर्ण;

/**
 * काष्ठा vme_driver - Structure representing a VME driver
 * @name: Driver name, should be unique among VME drivers and usually the same
 *        as the module name.
 * @match: Callback used to determine whether probe should be run.
 * @probe: Callback क्रम device binding, called when new device is detected.
 * @हटाओ: Callback, called on device removal.
 * @driver: Underlying generic device driver काष्ठाure.
 * @devices: List of VME devices (काष्ठा vme_dev) associated with this driver.
 */
काष्ठा vme_driver अणु
	स्थिर अक्षर *name;
	पूर्णांक (*match)(काष्ठा vme_dev *);
	पूर्णांक (*probe)(काष्ठा vme_dev *);
	व्योम (*हटाओ)(काष्ठा vme_dev *);
	काष्ठा device_driver driver;
	काष्ठा list_head devices;
पूर्ण;

व्योम *vme_alloc_consistent(काष्ठा vme_resource *, माप_प्रकार, dma_addr_t *);
व्योम vme_मुक्त_consistent(काष्ठा vme_resource *, माप_प्रकार,  व्योम *,
	dma_addr_t);

माप_प्रकार vme_get_size(काष्ठा vme_resource *);
पूर्णांक vme_check_winकरोw(u32 aspace, अचिन्हित दीर्घ दीर्घ vme_base,
		     अचिन्हित दीर्घ दीर्घ size);

काष्ठा vme_resource *vme_slave_request(काष्ठा vme_dev *, u32, u32);
पूर्णांक vme_slave_set(काष्ठा vme_resource *, पूर्णांक, अचिन्हित दीर्घ दीर्घ,
	अचिन्हित दीर्घ दीर्घ, dma_addr_t, u32, u32);
पूर्णांक vme_slave_get(काष्ठा vme_resource *, पूर्णांक *, अचिन्हित दीर्घ दीर्घ *,
	अचिन्हित दीर्घ दीर्घ *, dma_addr_t *, u32 *, u32 *);
व्योम vme_slave_मुक्त(काष्ठा vme_resource *);

काष्ठा vme_resource *vme_master_request(काष्ठा vme_dev *, u32, u32, u32);
पूर्णांक vme_master_set(काष्ठा vme_resource *, पूर्णांक, अचिन्हित दीर्घ दीर्घ,
	अचिन्हित दीर्घ दीर्घ, u32, u32, u32);
पूर्णांक vme_master_get(काष्ठा vme_resource *, पूर्णांक *, अचिन्हित दीर्घ दीर्घ *,
	अचिन्हित दीर्घ दीर्घ *, u32 *, u32 *, u32 *);
sमाप_प्रकार vme_master_पढ़ो(काष्ठा vme_resource *, व्योम *, माप_प्रकार, loff_t);
sमाप_प्रकार vme_master_ग_लिखो(काष्ठा vme_resource *, व्योम *, माप_प्रकार, loff_t);
अचिन्हित पूर्णांक vme_master_rmw(काष्ठा vme_resource *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक,
	अचिन्हित पूर्णांक, loff_t);
पूर्णांक vme_master_mmap(काष्ठा vme_resource *resource, काष्ठा vm_area_काष्ठा *vma);
व्योम vme_master_मुक्त(काष्ठा vme_resource *);

काष्ठा vme_resource *vme_dma_request(काष्ठा vme_dev *, u32);
काष्ठा vme_dma_list *vme_new_dma_list(काष्ठा vme_resource *);
काष्ठा vme_dma_attr *vme_dma_pattern_attribute(u32, u32);
काष्ठा vme_dma_attr *vme_dma_pci_attribute(dma_addr_t);
काष्ठा vme_dma_attr *vme_dma_vme_attribute(अचिन्हित दीर्घ दीर्घ, u32, u32, u32);
व्योम vme_dma_मुक्त_attribute(काष्ठा vme_dma_attr *);
पूर्णांक vme_dma_list_add(काष्ठा vme_dma_list *, काष्ठा vme_dma_attr *,
	काष्ठा vme_dma_attr *, माप_प्रकार);
पूर्णांक vme_dma_list_exec(काष्ठा vme_dma_list *);
पूर्णांक vme_dma_list_मुक्त(काष्ठा vme_dma_list *);
पूर्णांक vme_dma_मुक्त(काष्ठा vme_resource *);

पूर्णांक vme_irq_request(काष्ठा vme_dev *, पूर्णांक, पूर्णांक,
	व्योम (*callback)(पूर्णांक, पूर्णांक, व्योम *), व्योम *);
व्योम vme_irq_मुक्त(काष्ठा vme_dev *, पूर्णांक, पूर्णांक);
पूर्णांक vme_irq_generate(काष्ठा vme_dev *, पूर्णांक, पूर्णांक);

काष्ठा vme_resource *vme_lm_request(काष्ठा vme_dev *);
पूर्णांक vme_lm_count(काष्ठा vme_resource *);
पूर्णांक vme_lm_set(काष्ठा vme_resource *, अचिन्हित दीर्घ दीर्घ, u32, u32);
पूर्णांक vme_lm_get(काष्ठा vme_resource *, अचिन्हित दीर्घ दीर्घ *, u32 *, u32 *);
पूर्णांक vme_lm_attach(काष्ठा vme_resource *, पूर्णांक, व्योम (*callback)(व्योम *), व्योम *);
पूर्णांक vme_lm_detach(काष्ठा vme_resource *, पूर्णांक);
व्योम vme_lm_मुक्त(काष्ठा vme_resource *);

पूर्णांक vme_slot_num(काष्ठा vme_dev *);
पूर्णांक vme_bus_num(काष्ठा vme_dev *);

पूर्णांक vme_रेजिस्टर_driver(काष्ठा vme_driver *, अचिन्हित पूर्णांक);
व्योम vme_unरेजिस्टर_driver(काष्ठा vme_driver *);


#पूर्ण_अगर /* _VME_H_ */

