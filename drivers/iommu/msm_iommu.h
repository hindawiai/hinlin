<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 */

#अगर_अघोषित MSM_IOMMU_H
#घोषणा MSM_IOMMU_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iommu.h>
#समावेश <linux/clk.h>

/* Sharability attributes of MSM IOMMU mappings */
#घोषणा MSM_IOMMU_ATTR_NON_SH		0x0
#घोषणा MSM_IOMMU_ATTR_SH		0x4

/* Cacheability attributes of MSM IOMMU mappings */
#घोषणा MSM_IOMMU_ATTR_NONCACHED	0x0
#घोषणा MSM_IOMMU_ATTR_CACHED_WB_WA	0x1
#घोषणा MSM_IOMMU_ATTR_CACHED_WB_NWA	0x2
#घोषणा MSM_IOMMU_ATTR_CACHED_WT	0x3

/* Mask क्रम the cache policy attribute */
#घोषणा MSM_IOMMU_CP_MASK		0x03

/* Maximum number of Machine IDs that we are allowing to be mapped to the same
 * context bank. The number of MIDs mapped to the same CB करोes not affect
 * perक्रमmance, but there is a practical limit on how many distinct MIDs may
 * be present. These mappings are typically determined at design समय and are
 * not expected to change at run समय.
 */
#घोषणा MAX_NUM_MIDS	32

/* Maximum number of context banks that can be present in IOMMU */
#घोषणा IOMMU_MAX_CBS	128

/**
 * काष्ठा msm_iommu_dev - a single IOMMU hardware instance
 * ncb		Number of context banks present on this IOMMU HW instance
 * dev:		IOMMU device
 * irq:		Interrupt number
 * clk:		The bus घड़ी क्रम this IOMMU hardware instance
 * pclk:	The घड़ी क्रम the IOMMU bus पूर्णांकerconnect
 * dev_node:	list head in qcom_iommu_device_list
 * करोm_node:	list head क्रम करोमुख्य
 * ctx_list:	list of 'struct msm_iommu_ctx_dev'
 * context_map: Biपंचांगap to track allocated context banks
 */
काष्ठा msm_iommu_dev अणु
	व्योम __iomem *base;
	पूर्णांक ncb;
	काष्ठा device *dev;
	पूर्णांक irq;
	काष्ठा clk *clk;
	काष्ठा clk *pclk;
	काष्ठा list_head dev_node;
	काष्ठा list_head करोm_node;
	काष्ठा list_head ctx_list;
	DECLARE_BITMAP(context_map, IOMMU_MAX_CBS);

	काष्ठा iommu_device iommu;
पूर्ण;

/**
 * काष्ठा msm_iommu_ctx_dev - an IOMMU context bank instance
 * of_node	node ptr of client device
 * num		Index of this context bank within the hardware
 * mids		List of Machine IDs that are to be mapped पूर्णांकo this context
 *		bank, terminated by -1. The MID is a set of संकेतs on the
 *		AXI bus that identअगरies the function associated with a specअगरic
 *		memory request. (See ARM spec).
 * num_mids	Total number of mids
 * node		list head in ctx_list
 */
काष्ठा msm_iommu_ctx_dev अणु
	काष्ठा device_node *of_node;
	पूर्णांक num;
	पूर्णांक mids[MAX_NUM_MIDS];
	पूर्णांक num_mids;
	काष्ठा list_head list;
पूर्ण;

/*
 * Interrupt handler क्रम the IOMMU context fault पूर्णांकerrupt. Hooking the
 * पूर्णांकerrupt is not supported in the API yet, but this will prपूर्णांक an error
 * message and dump useful IOMMU रेजिस्टरs.
 */
irqवापस_t msm_iommu_fault_handler(पूर्णांक irq, व्योम *dev_id);

#पूर्ण_अगर
