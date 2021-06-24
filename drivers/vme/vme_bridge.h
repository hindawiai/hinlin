<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _VME_BRIDGE_H_
#घोषणा _VME_BRIDGE_H_

#समावेश <linux/vme.h>

#घोषणा VME_CRCSR_BUF_SIZE (508*1024)
/*
 * Resource काष्ठाures
 */
काष्ठा vme_master_resource अणु
	काष्ठा list_head list;
	काष्ठा vme_bridge *parent;
	/*
	 * We are likely to need to access the VME bus in पूर्णांकerrupt context, so
	 * protect master routines with a spinlock rather than a mutex.
	 */
	spinlock_t lock;
	पूर्णांक locked;
	पूर्णांक number;
	u32 address_attr;
	u32 cycle_attr;
	u32 width_attr;
	काष्ठा resource bus_resource;
	व्योम __iomem *kern_base;
पूर्ण;

काष्ठा vme_slave_resource अणु
	काष्ठा list_head list;
	काष्ठा vme_bridge *parent;
	काष्ठा mutex mtx;
	पूर्णांक locked;
	पूर्णांक number;
	u32 address_attr;
	u32 cycle_attr;
पूर्ण;

काष्ठा vme_dma_pattern अणु
	u32 pattern;
	u32 type;
पूर्ण;

काष्ठा vme_dma_pci अणु
	dma_addr_t address;
पूर्ण;

काष्ठा vme_dma_vme अणु
	अचिन्हित दीर्घ दीर्घ address;
	u32 aspace;
	u32 cycle;
	u32 dwidth;
पूर्ण;

काष्ठा vme_dma_list अणु
	काष्ठा list_head list;
	काष्ठा vme_dma_resource *parent;
	काष्ठा list_head entries;
	काष्ठा mutex mtx;
पूर्ण;

काष्ठा vme_dma_resource अणु
	काष्ठा list_head list;
	काष्ठा vme_bridge *parent;
	काष्ठा mutex mtx;
	पूर्णांक locked;
	पूर्णांक number;
	काष्ठा list_head pending;
	काष्ठा list_head running;
	u32 route_attr;
पूर्ण;

काष्ठा vme_lm_resource अणु
	काष्ठा list_head list;
	काष्ठा vme_bridge *parent;
	काष्ठा mutex mtx;
	पूर्णांक locked;
	पूर्णांक number;
	पूर्णांक monitors;
पूर्ण;

काष्ठा vme_error_handler अणु
	काष्ठा list_head list;
	अचिन्हित दीर्घ दीर्घ start;	/* Beginning of error winकरोw */
	अचिन्हित दीर्घ दीर्घ end;		/* End of error winकरोw */
	अचिन्हित दीर्घ दीर्घ first_error;	/* Address of the first error */
	u32 aspace;			/* Address space of error winकरोw*/
	अचिन्हित num_errors;		/* Number of errors */
पूर्ण;

काष्ठा vme_callback अणु
	व्योम (*func)(पूर्णांक, पूर्णांक, व्योम*);
	व्योम *priv_data;
पूर्ण;

काष्ठा vme_irq अणु
	पूर्णांक count;
	काष्ठा vme_callback callback[VME_NUM_STATUSID];
पूर्ण;

/* Allow 16 अक्षरacters क्रम name (including null अक्षरacter) */
#घोषणा VMENAMSIZ 16

/* This काष्ठाure stores all the inक्रमmation about one bridge
 * The काष्ठाure should be dynamically allocated by the driver and one instance
 * of the काष्ठाure should be present क्रम each VME chip present in the प्रणाली.
 */
काष्ठा vme_bridge अणु
	अक्षर name[VMENAMSIZ];
	पूर्णांक num;
	काष्ठा list_head master_resources;
	काष्ठा list_head slave_resources;
	काष्ठा list_head dma_resources;
	काष्ठा list_head lm_resources;

	/* List क्रम रेजिस्टरed errors handlers */
	काष्ठा list_head vme_error_handlers;
	/* List of devices on this bridge */
	काष्ठा list_head devices;

	/* Bridge Info - XXX Move to निजी काष्ठाure? */
	काष्ठा device *parent;	/* Parent device (eg. pdev->dev क्रम PCI) */
	व्योम *driver_priv;	/* Private poपूर्णांकer क्रम the bridge driver */
	काष्ठा list_head bus_list; /* list of VME buses */

	/* Interrupt callbacks */
	काष्ठा vme_irq irq[7];
	/* Locking क्रम VME irq callback configuration */
	काष्ठा mutex irq_mtx;

	/* Slave Functions */
	पूर्णांक (*slave_get) (काष्ठा vme_slave_resource *, पूर्णांक *,
		अचिन्हित दीर्घ दीर्घ *, अचिन्हित दीर्घ दीर्घ *, dma_addr_t *,
		u32 *, u32 *);
	पूर्णांक (*slave_set) (काष्ठा vme_slave_resource *, पूर्णांक, अचिन्हित दीर्घ दीर्घ,
		अचिन्हित दीर्घ दीर्घ, dma_addr_t, u32, u32);

	/* Master Functions */
	पूर्णांक (*master_get) (काष्ठा vme_master_resource *, पूर्णांक *,
		अचिन्हित दीर्घ दीर्घ *, अचिन्हित दीर्घ दीर्घ *, u32 *, u32 *,
		u32 *);
	पूर्णांक (*master_set) (काष्ठा vme_master_resource *, पूर्णांक,
		अचिन्हित दीर्घ दीर्घ, अचिन्हित दीर्घ दीर्घ,  u32, u32, u32);
	sमाप_प्रकार (*master_पढ़ो) (काष्ठा vme_master_resource *, व्योम *, माप_प्रकार,
		loff_t);
	sमाप_प्रकार (*master_ग_लिखो) (काष्ठा vme_master_resource *, व्योम *, माप_प्रकार,
		loff_t);
	अचिन्हित पूर्णांक (*master_rmw) (काष्ठा vme_master_resource *, अचिन्हित पूर्णांक,
		अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, loff_t);

	/* DMA Functions */
	पूर्णांक (*dma_list_add) (काष्ठा vme_dma_list *, काष्ठा vme_dma_attr *,
		काष्ठा vme_dma_attr *, माप_प्रकार);
	पूर्णांक (*dma_list_exec) (काष्ठा vme_dma_list *);
	पूर्णांक (*dma_list_empty) (काष्ठा vme_dma_list *);

	/* Interrupt Functions */
	व्योम (*irq_set) (काष्ठा vme_bridge *, पूर्णांक, पूर्णांक, पूर्णांक);
	पूर्णांक (*irq_generate) (काष्ठा vme_bridge *, पूर्णांक, पूर्णांक);

	/* Location monitor functions */
	पूर्णांक (*lm_set) (काष्ठा vme_lm_resource *, अचिन्हित दीर्घ दीर्घ, u32, u32);
	पूर्णांक (*lm_get) (काष्ठा vme_lm_resource *, अचिन्हित दीर्घ दीर्घ *, u32 *,
		u32 *);
	पूर्णांक (*lm_attach)(काष्ठा vme_lm_resource *, पूर्णांक,
			 व्योम (*callback)(व्योम *), व्योम *);
	पूर्णांक (*lm_detach) (काष्ठा vme_lm_resource *, पूर्णांक);

	/* CR/CSR space functions */
	पूर्णांक (*slot_get) (काष्ठा vme_bridge *);

	/* Bridge parent पूर्णांकerface */
	व्योम *(*alloc_consistent)(काष्ठा device *dev, माप_प्रकार size,
		dma_addr_t *dma);
	व्योम (*मुक्त_consistent)(काष्ठा device *dev, माप_प्रकार size,
		व्योम *vaddr, dma_addr_t dma);
पूर्ण;

व्योम vme_bus_error_handler(काष्ठा vme_bridge *bridge,
			   अचिन्हित दीर्घ दीर्घ address, पूर्णांक am);
व्योम vme_irq_handler(काष्ठा vme_bridge *, पूर्णांक, पूर्णांक);

काष्ठा vme_bridge *vme_init_bridge(काष्ठा vme_bridge *);
पूर्णांक vme_रेजिस्टर_bridge(काष्ठा vme_bridge *);
व्योम vme_unरेजिस्टर_bridge(काष्ठा vme_bridge *);
काष्ठा vme_error_handler *vme_रेजिस्टर_error_handler(
	काष्ठा vme_bridge *bridge, u32 aspace,
	अचिन्हित दीर्घ दीर्घ address, माप_प्रकार len);
व्योम vme_unरेजिस्टर_error_handler(काष्ठा vme_error_handler *handler);

#पूर्ण_अगर /* _VME_BRIDGE_H_ */
