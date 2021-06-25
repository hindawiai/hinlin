<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __FSL_PAMU_DOMAIN_H
#घोषणा __FSL_PAMU_DOMAIN_H

#समावेश "fsl_pamu.h"

काष्ठा fsl_dma_करोमुख्य अणु
	/* list of devices associated with the करोमुख्य */
	काष्ठा list_head		devices;
	u32				stash_id;
	काष्ठा iommu_करोमुख्य		iommu_करोमुख्य;
	spinlock_t			करोमुख्य_lock;
पूर्ण;

/* करोमुख्य-device relationship */
काष्ठा device_करोमुख्य_info अणु
	काष्ठा list_head link;	/* link to करोमुख्य siblings */
	काष्ठा device *dev;
	u32 liodn;
	काष्ठा fsl_dma_करोमुख्य *करोमुख्य; /* poपूर्णांकer to करोमुख्य */
पूर्ण;
#पूर्ण_अगर  /* __FSL_PAMU_DOMAIN_H */
