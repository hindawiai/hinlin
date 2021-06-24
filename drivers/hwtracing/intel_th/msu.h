<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Intel(R) Trace Hub Memory Storage Unit (MSU) data काष्ठाures
 *
 * Copyright (C) 2014-2015 Intel Corporation.
 */

#अगर_अघोषित __INTEL_TH_MSU_H__
#घोषणा __INTEL_TH_MSU_H__

क्रमागत अणु
	REG_MSU_MSUPARAMS	= 0x0000,
	REG_MSU_MSUSTS		= 0x0008,
	REG_MSU_MINTCTL		= 0x0004, /* MSU-global पूर्णांकerrupt control */
	REG_MSU_MSC0CTL		= 0x0100, /* MSC0 control */
	REG_MSU_MSC0STS		= 0x0104, /* MSC0 status */
	REG_MSU_MSC0BAR		= 0x0108, /* MSC0 output base address */
	REG_MSU_MSC0SIZE	= 0x010c, /* MSC0 output size */
	REG_MSU_MSC0MWP		= 0x0110, /* MSC0 ग_लिखो poपूर्णांकer */
	REG_MSU_MSC0NWSA	= 0x011c, /* MSC0 next winकरोw start address */

	REG_MSU_MSC1CTL		= 0x0200, /* MSC1 control */
	REG_MSU_MSC1STS		= 0x0204, /* MSC1 status */
	REG_MSU_MSC1BAR		= 0x0208, /* MSC1 output base address */
	REG_MSU_MSC1SIZE	= 0x020c, /* MSC1 output size */
	REG_MSU_MSC1MWP		= 0x0210, /* MSC1 ग_लिखो poपूर्णांकer */
	REG_MSU_MSC1NWSA	= 0x021c, /* MSC1 next winकरोw start address */
पूर्ण;

/* MSUSTS bits */
#घोषणा MSUSTS_MSU_INT	BIT(0)
#घोषणा MSUSTS_MSC0BLAST	BIT(16)
#घोषणा MSUSTS_MSC1BLAST	BIT(24)

/* MSCnCTL bits */
#घोषणा MSC_EN		BIT(0)
#घोषणा MSC_WRAPEN	BIT(1)
#घोषणा MSC_RD_HDR_OVRD	BIT(2)
#घोषणा MSC_MODE	(BIT(4) | BIT(5))
#घोषणा MSC_LEN		(BIT(8) | BIT(9) | BIT(10))

/* MINTCTL bits */
#घोषणा MICDE		BIT(0)
#घोषणा M0BLIE		BIT(16)
#घोषणा M1BLIE		BIT(24)

/* MSCnSTS bits */
#घोषणा MSCSTS_WRAPSTAT	BIT(1)	/* Wrap occurred */
#घोषणा MSCSTS_PLE	BIT(2)	/* Pipeline Empty */

/*
 * Multiblock/multiwinकरोw block descriptor
 */
काष्ठा msc_block_desc अणु
	u32	sw_tag;
	u32	block_sz;
	u32	next_blk;
	u32	next_win;
	u32	res0[4];
	u32	hw_tag;
	u32	valid_dw;
	u32	ts_low;
	u32	ts_high;
	u32	res1[4];
पूर्ण __packed;

#घोषणा MSC_BDESC	माप(काष्ठा msc_block_desc)
#घोषणा DATA_IN_PAGE	(PAGE_SIZE - MSC_BDESC)

/* MSC multiblock sw tag bits */
#घोषणा MSC_SW_TAG_LASTBLK	BIT(0)
#घोषणा MSC_SW_TAG_LASTWIN	BIT(1)

/* MSC multiblock hw tag bits */
#घोषणा MSC_HW_TAG_TRIGGER	BIT(0)
#घोषणा MSC_HW_TAG_BLOCKWRAP	BIT(1)
#घोषणा MSC_HW_TAG_WINWRAP	BIT(2)
#घोषणा MSC_HW_TAG_ENDBIT	BIT(3)

अटल अंतरभूत अचिन्हित दीर्घ msc_data_sz(काष्ठा msc_block_desc *bdesc)
अणु
	अगर (!bdesc->valid_dw)
		वापस 0;

	वापस bdesc->valid_dw * 4 - MSC_BDESC;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ msc_total_sz(काष्ठा msc_block_desc *bdesc)
अणु
	वापस bdesc->valid_dw * 4;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ msc_block_sz(काष्ठा msc_block_desc *bdesc)
अणु
	वापस bdesc->block_sz * 64 - MSC_BDESC;
पूर्ण

अटल अंतरभूत bool msc_block_wrapped(काष्ठा msc_block_desc *bdesc)
अणु
	अगर (bdesc->hw_tag & (MSC_HW_TAG_BLOCKWRAP | MSC_HW_TAG_WINWRAP))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool msc_block_last_written(काष्ठा msc_block_desc *bdesc)
अणु
	अगर ((bdesc->hw_tag & MSC_HW_TAG_ENDBIT) ||
	    (msc_data_sz(bdesc) != msc_block_sz(bdesc)))
		वापस true;

	वापस false;
पूर्ण

/* रुकोing क्रम Pipeline Empty bit(s) to निश्चित क्रम MSC */
#घोषणा MSC_PLE_WAITLOOP_DEPTH	10000

#पूर्ण_अगर /* __INTEL_TH_MSU_H__ */
