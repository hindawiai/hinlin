<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CXL Flash Device Driver
 *
 * Written by: Matthew R. Ochs <mrochs@linux.vnet.ibm.com>, IBM Corporation
 *	       Uma Krishnan <ukrishn@linux.vnet.ibm.com>, IBM Corporation
 *
 * Copyright (C) 2018 IBM Corporation
 */

#घोषणा OCXL_MAX_IRQS	4	/* Max पूर्णांकerrupts per process */

काष्ठा ocxlflash_irqs अणु
	पूर्णांक hwirq;
	u32 virq;
	व्योम __iomem *vtrig;
पूर्ण;

/* OCXL hardware AFU associated with the host */
काष्ठा ocxl_hw_afu अणु
	काष्ठा ocxlflash_context *ocxl_ctx; /* Host context */
	काष्ठा pci_dev *pdev;		/* PCI device */
	काष्ठा device *dev;		/* Generic device */
	bool perst_same_image;		/* Same image loaded on perst */

	काष्ठा ocxl_fn_config fcfg;	/* DVSEC config of the function */
	काष्ठा ocxl_afu_config acfg;	/* AFU configuration data */

	पूर्णांक fn_actag_base;		/* Function acTag base */
	पूर्णांक fn_actag_enabled;		/* Function acTag number enabled */
	पूर्णांक afu_actag_base;		/* AFU acTag base */
	पूर्णांक afu_actag_enabled;		/* AFU acTag number enabled */

	phys_addr_t ppmmio_phys;	/* Per process MMIO space */
	phys_addr_t gmmio_phys;		/* Global AFU MMIO space */
	व्योम __iomem *gmmio_virt;	/* Global MMIO map */

	व्योम *link_token;		/* Link token क्रम the SPA */
	काष्ठा idr idr;			/* IDR to manage contexts */
	पूर्णांक max_pasid;			/* Maximum number of contexts */
	bool is_present;		/* Function has AFUs defined */
पूर्ण;

क्रमागत ocxlflash_ctx_state अणु
	CLOSED,
	OPENED,
	STARTED
पूर्ण;

काष्ठा ocxlflash_context अणु
	काष्ठा ocxl_hw_afu *hw_afu;	/* HW AFU back poपूर्णांकer */
	काष्ठा address_space *mapping;	/* Mapping क्रम pseuकरो fileप्रणाली */
	bool master;			/* Whether this is a master context */
	पूर्णांक pe;				/* Process element */

	phys_addr_t psn_phys;		/* Process mapping */
	u64 psn_size;			/* Process mapping size */

	spinlock_t slock;		/* Protects irq/fault/event updates */
	रुको_queue_head_t wq;		/* Wait queue क्रम poll and पूर्णांकerrupts */
	काष्ठा mutex state_mutex;	/* Mutex to update context state */
	क्रमागत ocxlflash_ctx_state state;	/* Context state */

	काष्ठा ocxlflash_irqs *irqs;	/* Poपूर्णांकer to array of काष्ठाures */
	पूर्णांक num_irqs;			/* Number of पूर्णांकerrupts */
	bool pending_irq;		/* Pending पूर्णांकerrupt on the context */
	uदीर्घ irq_biपंचांगap;		/* Bits indicating pending irq num */

	u64 fault_addr;			/* Address that triggered the fault */
	u64 fault_dsisr;		/* Value of dsisr रेजिस्टर at fault */
	bool pending_fault;		/* Pending translation fault */
पूर्ण;
