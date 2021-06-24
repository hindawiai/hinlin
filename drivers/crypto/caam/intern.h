<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * CAAM/SEC 4.x driver backend
 * Private/पूर्णांकernal definitions between modules
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 * Copyright 2019 NXP
 */

#अगर_अघोषित INTERN_H
#घोषणा INTERN_H

#समावेश "ctrl.h"
#समावेश <crypto/engine.h>

/* Currently comes from Kconfig param as a ^2 (driver-required) */
#घोषणा JOBR_DEPTH (1 << CONFIG_CRYPTO_DEV_FSL_CAAM_RINGSIZE)

/*
 * Maximum size क्रम crypto-engine software queue based on Job Ring
 * size (JOBR_DEPTH) and a THRESHOLD (reserved क्रम the non-crypto-API
 * requests that are not passed through crypto-engine)
 */
#घोषणा THRESHOLD 15
#घोषणा CRYPTO_ENGINE_MAX_QLEN (JOBR_DEPTH - THRESHOLD)

/* Kconfig params क्रम पूर्णांकerrupt coalescing अगर selected (अन्यथा zero) */
#अगर_घोषित CONFIG_CRYPTO_DEV_FSL_CAAM_INTC
#घोषणा JOBR_INTC JRCFG_ICEN
#घोषणा JOBR_INTC_TIME_THLD CONFIG_CRYPTO_DEV_FSL_CAAM_INTC_TIME_THLD
#घोषणा JOBR_INTC_COUNT_THLD CONFIG_CRYPTO_DEV_FSL_CAAM_INTC_COUNT_THLD
#अन्यथा
#घोषणा JOBR_INTC 0
#घोषणा JOBR_INTC_TIME_THLD 0
#घोषणा JOBR_INTC_COUNT_THLD 0
#पूर्ण_अगर

/*
 * Storage क्रम tracking each in-process entry moving across a ring
 * Each entry on an output ring needs one of these
 */
काष्ठा caam_jrentry_info अणु
	व्योम (*callbk)(काष्ठा device *dev, u32 *desc, u32 status, व्योम *arg);
	व्योम *cbkarg;	/* Argument per ring entry */
	u32 *desc_addr_virt;	/* Stored virt addr क्रम postprocessing */
	dma_addr_t desc_addr_dma;	/* Stored bus addr क्रम करोne matching */
	u32 desc_size;	/* Stored size क्रम postprocessing, header derived */
पूर्ण;

/* Private sub-storage क्रम a single JobR */
काष्ठा caam_drv_निजी_jr अणु
	काष्ठा list_head	list_node;	/* Job Ring device list */
	काष्ठा device		*dev;
	पूर्णांक ridx;
	काष्ठा caam_job_ring __iomem *rregs;	/* JobR's रेजिस्टर space */
	काष्ठा tasklet_काष्ठा irqtask;
	पूर्णांक irq;			/* One per queue */
	bool hwrng;

	/* Number of scatterlist crypt transक्रमms active on the JobR */
	atomic_t tfm_count ____cacheline_aligned;

	/* Job ring info */
	काष्ठा caam_jrentry_info *entinfo;	/* Alloc'ed 1 per ring entry */
	spinlock_t inplock ____cacheline_aligned; /* Input ring index lock */
	u32 inpring_avail;	/* Number of मुक्त entries in input ring */
	पूर्णांक head;			/* entinfo (s/w ring) head index */
	व्योम *inpring;			/* Base of input ring, alloc
					 * DMA-safe */
	पूर्णांक out_ring_पढ़ो_index;	/* Output index "tail" */
	पूर्णांक tail;			/* entinfo (s/w ring) tail index */
	व्योम *outring;			/* Base of output ring, DMA-safe */
	काष्ठा crypto_engine *engine;
पूर्ण;

/*
 * Driver-निजी storage क्रम a single CAAM block instance
 */
काष्ठा caam_drv_निजी अणु
	/* Physical-presence section */
	काष्ठा caam_ctrl __iomem *ctrl; /* controller region */
	काष्ठा caam_deco __iomem *deco; /* DECO/CCB views */
	काष्ठा caam_assurance __iomem *assure;
	काष्ठा caam_queue_अगर __iomem *qi; /* QI control region */
	काष्ठा caam_job_ring __iomem *jr[4];	/* JobR's रेजिस्टर space */

	काष्ठा iommu_करोमुख्य *करोमुख्य;

	/*
	 * Detected geometry block. Filled in from device tree अगर घातerpc,
	 * or from रेजिस्टर-based version detection code
	 */
	u8 total_jobrs;		/* Total Job Rings in device */
	u8 qi_present;		/* Nonzero अगर QI present in device */
	u8 mc_en;		/* Nonzero अगर MC f/w is active */
	पूर्णांक secvio_irq;		/* Security violation पूर्णांकerrupt number */
	पूर्णांक virt_en;		/* Virtualization enabled in CAAM */
	पूर्णांक era;		/* CAAM Era (पूर्णांकernal HW revision) */

#घोषणा	RNG4_MAX_HANDLES 2
	/* RNG4 block */
	u32 rng4_sh_init;	/* This biपंचांगap shows which of the State
				   Handles of the RNG4 block are initialized
				   by this driver */

	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;
	/*
	 * debugfs entries क्रम developer view पूर्णांकo driver/device
	 * variables at runसमय.
	 */
#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *ctl; /* controller dir */
	काष्ठा debugfs_blob_wrapper ctl_kek_wrap, ctl_tkek_wrap, ctl_tdsk_wrap;
#पूर्ण_अगर
पूर्ण;

#अगर_घोषित CONFIG_CRYPTO_DEV_FSL_CAAM_CRYPTO_API

पूर्णांक caam_algapi_init(काष्ठा device *dev);
व्योम caam_algapi_निकास(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक caam_algapi_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम caam_algapi_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_FSL_CAAM_CRYPTO_API */

#अगर_घोषित CONFIG_CRYPTO_DEV_FSL_CAAM_AHASH_API

पूर्णांक caam_algapi_hash_init(काष्ठा device *dev);
व्योम caam_algapi_hash_निकास(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक caam_algapi_hash_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम caam_algapi_hash_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_FSL_CAAM_AHASH_API */

#अगर_घोषित CONFIG_CRYPTO_DEV_FSL_CAAM_PKC_API

पूर्णांक caam_pkc_init(काष्ठा device *dev);
व्योम caam_pkc_निकास(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक caam_pkc_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम caam_pkc_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_FSL_CAAM_PKC_API */

#अगर_घोषित CONFIG_CRYPTO_DEV_FSL_CAAM_RNG_API

पूर्णांक caam_rng_init(काष्ठा device *dev);
व्योम caam_rng_निकास(काष्ठा device *dev);

#अन्यथा

अटल अंतरभूत पूर्णांक caam_rng_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम caam_rng_निकास(काष्ठा device *dev) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_CRYPTO_DEV_FSL_CAAM_RNG_API */

#अगर_घोषित CONFIG_CAAM_QI

पूर्णांक caam_qi_algapi_init(काष्ठा device *dev);
व्योम caam_qi_algapi_निकास(व्योम);

#अन्यथा

अटल अंतरभूत पूर्णांक caam_qi_algapi_init(काष्ठा device *dev)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम caam_qi_algapi_निकास(व्योम)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_CAAM_QI */

अटल अंतरभूत u64 caam_get_dma_mask(काष्ठा device *dev)
अणु
	काष्ठा device_node *nprop = dev->of_node;

	अगर (caam_ptr_sz != माप(u64))
		वापस DMA_BIT_MASK(32);

	अगर (caam_dpaa2)
		वापस DMA_BIT_MASK(49);

	अगर (of_device_is_compatible(nprop, "fsl,sec-v5.0-job-ring") ||
	    of_device_is_compatible(nprop, "fsl,sec-v5.0"))
		वापस DMA_BIT_MASK(40);

	वापस DMA_BIT_MASK(36);
पूर्ण


#पूर्ण_अगर /* INTERN_H */
