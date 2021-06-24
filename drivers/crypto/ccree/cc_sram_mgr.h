<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#अगर_अघोषित __CC_SRAM_MGR_H__
#घोषणा __CC_SRAM_MGR_H__

#अगर_अघोषित CC_CC_SRAM_SIZE
#घोषणा CC_CC_SRAM_SIZE 4096
#पूर्ण_अगर

काष्ठा cc_drvdata;

#घोषणा शून्य_SRAM_ADDR ((u32)-1)

/**
 * cc_sram_mgr_init() - Initializes SRAM pool.
 * The first X bytes of SRAM are reserved क्रम ROM usage, hence, pool
 * starts right after X bytes.
 *
 * @drvdata: Associated device driver context
 *
 * Return:
 * Zero क्रम success, negative value otherwise.
 */
पूर्णांक cc_sram_mgr_init(काष्ठा cc_drvdata *drvdata);

/**
 * cc_sram_alloc() - Allocate buffer from SRAM pool.
 *
 * @drvdata: Associated device driver context
 * @size: The requested bytes to allocate
 *
 * Return:
 * Address offset in SRAM or शून्य_SRAM_ADDR क्रम failure.
 */
u32 cc_sram_alloc(काष्ठा cc_drvdata *drvdata, u32 size);

/**
 * cc_set_sram_desc() - Create स्थिर descriptors sequence to
 *	set values in given array पूर्णांकo SRAM.
 * Note: each स्थिर value can't exceed word size.
 *
 * @src:	  A poपूर्णांकer to array of words to set as स्थिरs.
 * @dst:	  The target SRAM buffer to set पूर्णांकo
 * @nelement:	  The number of words in "src" array
 * @seq:	  A poपूर्णांकer to the given IN/OUT descriptor sequence
 * @seq_len:	  A poपूर्णांकer to the given IN/OUT sequence length
 */
व्योम cc_set_sram_desc(स्थिर u32 *src, u32 dst, अचिन्हित पूर्णांक nelement,
		      काष्ठा cc_hw_desc *seq, अचिन्हित पूर्णांक *seq_len);

#पूर्ण_अगर /*__CC_SRAM_MGR_H__*/
