<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2012-2019 ARM Limited (or its affiliates). */

#समावेश "cc_driver.h"
#समावेश "cc_sram_mgr.h"

/**
 * cc_sram_mgr_init() - Initializes SRAM pool.
 *      The pool starts right at the beginning of SRAM.
 *      Returns zero क्रम success, negative value otherwise.
 *
 * @drvdata: Associated device driver context
 *
 * Return:
 * 0 क्रम success, negative error code क्रम failure.
 */
पूर्णांक cc_sram_mgr_init(काष्ठा cc_drvdata *drvdata)
अणु
	u32 start = 0;
	काष्ठा device *dev = drvdata_to_dev(drvdata);

	अगर (drvdata->hw_rev < CC_HW_REV_712) अणु
		/* Pool starts after ROM bytes */
		start = cc_ioपढ़ो(drvdata, CC_REG(HOST_SEP_SRAM_THRESHOLD));
		अगर ((start & 0x3) != 0) अणु
			dev_err(dev, "Invalid SRAM offset 0x%x\n", start);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	drvdata->sram_मुक्त_offset = start;
	वापस 0;
पूर्ण

/**
 * cc_sram_alloc() - Allocate buffer from SRAM pool.
 *
 * @drvdata: Associated device driver context
 * @size: The requested numer of bytes to allocate
 *
 * Return:
 * Address offset in SRAM or शून्य_SRAM_ADDR क्रम failure.
 */
u32 cc_sram_alloc(काष्ठा cc_drvdata *drvdata, u32 size)
अणु
	काष्ठा device *dev = drvdata_to_dev(drvdata);
	u32 p;

	अगर ((size & 0x3)) अणु
		dev_err(dev, "Requested buffer size (%u) is not multiple of 4",
			size);
		वापस शून्य_SRAM_ADDR;
	पूर्ण
	अगर (size > (CC_CC_SRAM_SIZE - drvdata->sram_मुक्त_offset)) अणु
		dev_err(dev, "Not enough space to allocate %u B (at offset %u)\n",
			size, drvdata->sram_मुक्त_offset);
		वापस शून्य_SRAM_ADDR;
	पूर्ण

	p = drvdata->sram_मुक्त_offset;
	drvdata->sram_मुक्त_offset += size;
	dev_dbg(dev, "Allocated %u B @ %u\n", size, p);
	वापस p;
पूर्ण

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
		      काष्ठा cc_hw_desc *seq, अचिन्हित पूर्णांक *seq_len)
अणु
	u32 i;
	अचिन्हित पूर्णांक idx = *seq_len;

	क्रम (i = 0; i < nelement; i++, idx++) अणु
		hw_desc_init(&seq[idx]);
		set_din_स्थिर(&seq[idx], src[i], माप(u32));
		set_करोut_sram(&seq[idx], dst + (i * माप(u32)), माप(u32));
		set_flow_mode(&seq[idx], BYPASS);
	पूर्ण

	*seq_len = idx;
पूर्ण
