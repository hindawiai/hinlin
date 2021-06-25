<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *
 * Copyright (C) 2013 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित __FSL_PAMU_STASH_H
#घोषणा __FSL_PAMU_STASH_H

काष्ठा iommu_करोमुख्य;

/* cache stash tarमाला_लो */
क्रमागत pamu_stash_target अणु
	PAMU_ATTR_CACHE_L1 = 1,
	PAMU_ATTR_CACHE_L2,
	PAMU_ATTR_CACHE_L3,
पूर्ण;

पूर्णांक fsl_pamu_configure_l1_stash(काष्ठा iommu_करोमुख्य *करोमुख्य, u32 cpu);

#पूर्ण_अगर  /* __FSL_PAMU_STASH_H */
