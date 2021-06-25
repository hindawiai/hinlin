<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Keem Bay OCS AES Crypto Driver.
 *
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/dma-mapping.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/swab.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/त्रुटिसं.स>

#समावेश <crypto/aes.h>
#समावेश <crypto/gcm.h>

#समावेश "ocs-aes.h"

#घोषणा AES_COMMAND_OFFSET			0x0000
#घोषणा AES_KEY_0_OFFSET			0x0004
#घोषणा AES_KEY_1_OFFSET			0x0008
#घोषणा AES_KEY_2_OFFSET			0x000C
#घोषणा AES_KEY_3_OFFSET			0x0010
#घोषणा AES_KEY_4_OFFSET			0x0014
#घोषणा AES_KEY_5_OFFSET			0x0018
#घोषणा AES_KEY_6_OFFSET			0x001C
#घोषणा AES_KEY_7_OFFSET			0x0020
#घोषणा AES_IV_0_OFFSET				0x0024
#घोषणा AES_IV_1_OFFSET				0x0028
#घोषणा AES_IV_2_OFFSET				0x002C
#घोषणा AES_IV_3_OFFSET				0x0030
#घोषणा AES_ACTIVE_OFFSET			0x0034
#घोषणा AES_STATUS_OFFSET			0x0038
#घोषणा AES_KEY_SIZE_OFFSET			0x0044
#घोषणा AES_IER_OFFSET				0x0048
#घोषणा AES_ISR_OFFSET				0x005C
#घोषणा AES_MULTIPURPOSE1_0_OFFSET		0x0200
#घोषणा AES_MULTIPURPOSE1_1_OFFSET		0x0204
#घोषणा AES_MULTIPURPOSE1_2_OFFSET		0x0208
#घोषणा AES_MULTIPURPOSE1_3_OFFSET		0x020C
#घोषणा AES_MULTIPURPOSE2_0_OFFSET		0x0220
#घोषणा AES_MULTIPURPOSE2_1_OFFSET		0x0224
#घोषणा AES_MULTIPURPOSE2_2_OFFSET		0x0228
#घोषणा AES_MULTIPURPOSE2_3_OFFSET		0x022C
#घोषणा AES_BYTE_ORDER_CFG_OFFSET		0x02C0
#घोषणा AES_TLEN_OFFSET				0x0300
#घोषणा AES_T_MAC_0_OFFSET			0x0304
#घोषणा AES_T_MAC_1_OFFSET			0x0308
#घोषणा AES_T_MAC_2_OFFSET			0x030C
#घोषणा AES_T_MAC_3_OFFSET			0x0310
#घोषणा AES_PLEN_OFFSET				0x0314
#घोषणा AES_A_DMA_SRC_ADDR_OFFSET		0x0400
#घोषणा AES_A_DMA_DST_ADDR_OFFSET		0x0404
#घोषणा AES_A_DMA_SRC_SIZE_OFFSET		0x0408
#घोषणा AES_A_DMA_DST_SIZE_OFFSET		0x040C
#घोषणा AES_A_DMA_DMA_MODE_OFFSET		0x0410
#घोषणा AES_A_DMA_NEXT_SRC_DESCR_OFFSET		0x0418
#घोषणा AES_A_DMA_NEXT_DST_DESCR_OFFSET		0x041C
#घोषणा AES_A_DMA_WHILE_ACTIVE_MODE_OFFSET	0x0420
#घोषणा AES_A_DMA_LOG_OFFSET			0x0424
#घोषणा AES_A_DMA_STATUS_OFFSET			0x0428
#घोषणा AES_A_DMA_PERF_CNTR_OFFSET		0x042C
#घोषणा AES_A_DMA_MSI_ISR_OFFSET		0x0480
#घोषणा AES_A_DMA_MSI_IER_OFFSET		0x0484
#घोषणा AES_A_DMA_MSI_MASK_OFFSET		0x0488
#घोषणा AES_A_DMA_INBUFFER_WRITE_FIFO_OFFSET	0x0600
#घोषणा AES_A_DMA_OUTBUFFER_READ_FIFO_OFFSET	0x0700

/*
 * AES_A_DMA_DMA_MODE रेजिस्टर.
 * Default: 0x00000000.
 * bit[31]	ACTIVE
 *		This bit activates the DMA. When the DMA finishes, it resets
 *		this bit to zero.
 * bit[30:26]	Unused by this driver.
 * bit[25]	SRC_LINK_LIST_EN
 *		Source link list enable bit. When the linked list is terminated
 *		this bit is reset by the DMA.
 * bit[24]	DST_LINK_LIST_EN
 *		Destination link list enable bit. When the linked list is
 *		terminated this bit is reset by the DMA.
 * bit[23:0]	Unused by this driver.
 */
#घोषणा AES_A_DMA_DMA_MODE_ACTIVE		BIT(31)
#घोषणा AES_A_DMA_DMA_MODE_SRC_LINK_LIST_EN	BIT(25)
#घोषणा AES_A_DMA_DMA_MODE_DST_LINK_LIST_EN	BIT(24)

/*
 * AES_ACTIVE रेजिस्टर
 * शेष 0x00000000
 * bit[31:10]	Reserved
 * bit[9]	LAST_ADATA
 * bit[8]	LAST_GCX
 * bit[7:2]	Reserved
 * bit[1]	TERMINATION
 * bit[0]	TRIGGER
 */
#घोषणा AES_ACTIVE_LAST_ADATA			BIT(9)
#घोषणा AES_ACTIVE_LAST_CCM_GCM			BIT(8)
#घोषणा AES_ACTIVE_TERMINATION			BIT(1)
#घोषणा AES_ACTIVE_TRIGGER			BIT(0)

#घोषणा AES_DISABLE_INT				0x00000000
#घोषणा AES_DMA_CPD_ERR_INT			BIT(8)
#घोषणा AES_DMA_OUTBUF_RD_ERR_INT		BIT(7)
#घोषणा AES_DMA_OUTBUF_WR_ERR_INT		BIT(6)
#घोषणा AES_DMA_INBUF_RD_ERR_INT		BIT(5)
#घोषणा AES_DMA_INBUF_WR_ERR_INT		BIT(4)
#घोषणा AES_DMA_BAD_COMP_INT			BIT(3)
#घोषणा AES_DMA_SAI_INT				BIT(2)
#घोषणा AES_DMA_SRC_DONE_INT			BIT(0)
#घोषणा AES_COMPLETE_INT			BIT(1)

#घोषणा AES_DMA_MSI_MASK_CLEAR			BIT(0)

#घोषणा AES_128_BIT_KEY				0x00000000
#घोषणा AES_256_BIT_KEY				BIT(0)

#घोषणा AES_DEACTIVATE_PERF_CNTR		0x00000000
#घोषणा AES_ACTIVATE_PERF_CNTR			BIT(0)

#घोषणा AES_MAX_TAG_SIZE_U32			4

#घोषणा OCS_LL_DMA_FLAG_TERMINATE		BIT(31)

/*
 * There is an inconsistency in the करोcumentation. This is करोcumented as a
 * 11-bit value, but it is actually 10-bits.
 */
#घोषणा AES_DMA_STATUS_INPUT_BUFFER_OCCUPANCY_MASK	0x3FF

/*
 * During CCM decrypt, the OCS block needs to finish processing the ciphertext
 * beक्रमe the tag is written. For 128-bit mode this required delay is 28 OCS
 * घड़ी cycles. For 256-bit mode it is 36 OCS घड़ी cycles.
 */
#घोषणा CCM_DECRYPT_DELAY_TAG_CLK_COUNT		36UL

/*
 * During CCM decrypt there must be a delay of at least 42 OCS घड़ी cycles
 * between setting the TRIGGER bit in AES_ACTIVE and setting the LAST_CCM_GCM
 * bit in the same रेजिस्टर (as stated in the OCS databook)
 */
#घोषणा CCM_DECRYPT_DELAY_LAST_GCX_CLK_COUNT	42UL

/* See RFC3610 section 2.2 */
#घोषणा L_PRIME_MIN (1)
#घोषणा L_PRIME_MAX (7)
/*
 * CCM IV क्रमmat from RFC 3610 section 2.3
 *
 *   Octet Number   Contents
 *   ------------   ---------
 *   0              Flags
 *   1 ... 15-L     Nonce N
 *   16-L ... 15    Counter i
 *
 * Flags = L' = L - 1
 */
#घोषणा L_PRIME_IDX		0
#घोषणा COUNTER_START(lprime)	(16 - ((lprime) + 1))
#घोषणा COUNTER_LEN(lprime)	((lprime) + 1)

क्रमागत aes_counter_mode अणु
	AES_CTR_M_NO_INC = 0,
	AES_CTR_M_32_INC = 1,
	AES_CTR_M_64_INC = 2,
	AES_CTR_M_128_INC = 3,
पूर्ण;

/**
 * काष्ठा ocs_dma_linked_list - OCS DMA linked list entry.
 * @src_addr:   Source address of the data.
 * @src_len:    Length of data to be fetched.
 * @next:	Next dma_list to fetch.
 * @ll_flags:   Flags (Freeze @ terminate) क्रम the DMA engine.
 */
काष्ठा ocs_dma_linked_list अणु
	u32 src_addr;
	u32 src_len;
	u32 next;
	u32 ll_flags;
पूर्ण __packed;

/*
 * Set endianness of inमाला_दो and outमाला_दो
 * AES_BYTE_ORDER_CFG
 * शेष 0x00000000
 * bit [10] - KEY_HI_LO_SWAP
 * bit [9] - KEY_HI_SWAP_DWORDS_IN_OCTWORD
 * bit [8] - KEY_HI_SWAP_BYTES_IN_DWORD
 * bit [7] - KEY_LO_SWAP_DWORDS_IN_OCTWORD
 * bit [6] - KEY_LO_SWAP_BYTES_IN_DWORD
 * bit [5] - IV_SWAP_DWORDS_IN_OCTWORD
 * bit [4] - IV_SWAP_BYTES_IN_DWORD
 * bit [3] - DOUT_SWAP_DWORDS_IN_OCTWORD
 * bit [2] - DOUT_SWAP_BYTES_IN_DWORD
 * bit [1] - DOUT_SWAP_DWORDS_IN_OCTWORD
 * bit [0] - DOUT_SWAP_BYTES_IN_DWORD
 */
अटल अंतरभूत व्योम aes_a_set_endianness(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(0x7FF, aes_dev->base_reg + AES_BYTE_ORDER_CFG_OFFSET);
पूर्ण

/* Trigger AES process start. */
अटल अंतरभूत व्योम aes_a_op_trigger(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_ACTIVE_TRIGGER, aes_dev->base_reg + AES_ACTIVE_OFFSET);
पूर्ण

/* Indicate last bulk of data. */
अटल अंतरभूत व्योम aes_a_op_termination(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_ACTIVE_TERMINATION,
		  aes_dev->base_reg + AES_ACTIVE_OFFSET);
पूर्ण

/*
 * Set LAST_CCM_GCM in AES_ACTIVE रेजिस्टर and clear all other bits.
 *
 * Called when DMA is programmed to fetch the last batch of data.
 * - For AES-CCM it is called क्रम the last batch of Payload data and Ciphertext
 *   data.
 * - For AES-GCM, it is called क्रम the last batch of Plaपूर्णांकext data and
 *   Ciphertext data.
 */
अटल अंतरभूत व्योम aes_a_set_last_gcx(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_ACTIVE_LAST_CCM_GCM,
		  aes_dev->base_reg + AES_ACTIVE_OFFSET);
पूर्ण

/* Wait क्रम LAST_CCM_GCM bit to be unset. */
अटल अंतरभूत व्योम aes_a_रुको_last_gcx(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	u32 aes_active_reg;

	करो अणु
		aes_active_reg = ioपढ़ो32(aes_dev->base_reg +
					  AES_ACTIVE_OFFSET);
	पूर्ण जबतक (aes_active_reg & AES_ACTIVE_LAST_CCM_GCM);
पूर्ण

/* Wait क्रम 10 bits of input occupancy. */
अटल व्योम aes_a_dma_रुको_input_buffer_occupancy(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	u32 reg;

	करो अणु
		reg = ioपढ़ो32(aes_dev->base_reg + AES_A_DMA_STATUS_OFFSET);
	पूर्ण जबतक (reg & AES_DMA_STATUS_INPUT_BUFFER_OCCUPANCY_MASK);
पूर्ण

 /*
  * Set LAST_CCM_GCM and LAST_ADATA bits in AES_ACTIVE रेजिस्टर (and clear all
  * other bits).
  *
  * Called when DMA is programmed to fetch the last batch of Associated Data
  * (CCM हाल) or Additional Authenticated Data (GCM हाल).
  */
अटल अंतरभूत व्योम aes_a_set_last_gcx_and_adata(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_ACTIVE_LAST_ADATA | AES_ACTIVE_LAST_CCM_GCM,
		  aes_dev->base_reg + AES_ACTIVE_OFFSET);
पूर्ण

/* Set DMA src and dst transfer size to 0 */
अटल अंतरभूत व्योम aes_a_dma_set_xfer_size_zero(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(0, aes_dev->base_reg + AES_A_DMA_SRC_SIZE_OFFSET);
	ioग_लिखो32(0, aes_dev->base_reg + AES_A_DMA_DST_SIZE_OFFSET);
पूर्ण

/* Activate DMA क्रम zero-byte transfer हाल. */
अटल अंतरभूत व्योम aes_a_dma_active(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_A_DMA_DMA_MODE_ACTIVE,
		  aes_dev->base_reg + AES_A_DMA_DMA_MODE_OFFSET);
पूर्ण

/* Activate DMA and enable src linked list */
अटल अंतरभूत व्योम aes_a_dma_active_src_ll_en(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_A_DMA_DMA_MODE_ACTIVE |
		  AES_A_DMA_DMA_MODE_SRC_LINK_LIST_EN,
		  aes_dev->base_reg + AES_A_DMA_DMA_MODE_OFFSET);
पूर्ण

/* Activate DMA and enable dst linked list */
अटल अंतरभूत व्योम aes_a_dma_active_dst_ll_en(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_A_DMA_DMA_MODE_ACTIVE |
		  AES_A_DMA_DMA_MODE_DST_LINK_LIST_EN,
		  aes_dev->base_reg + AES_A_DMA_DMA_MODE_OFFSET);
पूर्ण

/* Activate DMA and enable src and dst linked lists */
अटल अंतरभूत व्योम aes_a_dma_active_src_dst_ll_en(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(AES_A_DMA_DMA_MODE_ACTIVE |
		  AES_A_DMA_DMA_MODE_SRC_LINK_LIST_EN |
		  AES_A_DMA_DMA_MODE_DST_LINK_LIST_EN,
		  aes_dev->base_reg + AES_A_DMA_DMA_MODE_OFFSET);
पूर्ण

/* Reset PERF_CNTR to 0 and activate it */
अटल अंतरभूत व्योम aes_a_dma_reset_and_activate_perf_cntr(स्थिर काष्ठा ocs_aes_dev *aes_dev)
अणु
	ioग_लिखो32(0x00000000, aes_dev->base_reg + AES_A_DMA_PERF_CNTR_OFFSET);
	ioग_लिखो32(AES_ACTIVATE_PERF_CNTR,
		  aes_dev->base_reg + AES_A_DMA_WHILE_ACTIVE_MODE_OFFSET);
पूर्ण

/* Wait until PERF_CNTR is > delay, then deactivate it */
अटल अंतरभूत व्योम aes_a_dma_रुको_and_deactivate_perf_cntr(स्थिर काष्ठा ocs_aes_dev *aes_dev,
							   पूर्णांक delay)
अणु
	जबतक (ioपढ़ो32(aes_dev->base_reg + AES_A_DMA_PERF_CNTR_OFFSET) < delay)
		;
	ioग_लिखो32(AES_DEACTIVATE_PERF_CNTR,
		  aes_dev->base_reg + AES_A_DMA_WHILE_ACTIVE_MODE_OFFSET);
पूर्ण

/* Disable AES and DMA IRQ. */
अटल व्योम aes_irq_disable(काष्ठा ocs_aes_dev *aes_dev)
अणु
	u32 isr_val = 0;

	/* Disable पूर्णांकerrupts */
	ioग_लिखो32(AES_DISABLE_INT,
		  aes_dev->base_reg + AES_A_DMA_MSI_IER_OFFSET);
	ioग_लिखो32(AES_DISABLE_INT, aes_dev->base_reg + AES_IER_OFFSET);

	/* Clear any pending पूर्णांकerrupt */
	isr_val = ioपढ़ो32(aes_dev->base_reg + AES_A_DMA_MSI_ISR_OFFSET);
	अगर (isr_val)
		ioग_लिखो32(isr_val,
			  aes_dev->base_reg + AES_A_DMA_MSI_ISR_OFFSET);

	isr_val = ioपढ़ो32(aes_dev->base_reg + AES_A_DMA_MSI_MASK_OFFSET);
	अगर (isr_val)
		ioग_लिखो32(isr_val,
			  aes_dev->base_reg + AES_A_DMA_MSI_MASK_OFFSET);

	isr_val = ioपढ़ो32(aes_dev->base_reg + AES_ISR_OFFSET);
	अगर (isr_val)
		ioग_लिखो32(isr_val, aes_dev->base_reg + AES_ISR_OFFSET);
पूर्ण

/* Enable AES or DMA IRQ.  IRQ is disabled once fired. */
अटल व्योम aes_irq_enable(काष्ठा ocs_aes_dev *aes_dev, u8 irq)
अणु
	अगर (irq == AES_COMPLETE_INT) अणु
		/* Ensure DMA error पूर्णांकerrupts are enabled */
		ioग_लिखो32(AES_DMA_CPD_ERR_INT |
			  AES_DMA_OUTBUF_RD_ERR_INT |
			  AES_DMA_OUTBUF_WR_ERR_INT |
			  AES_DMA_INBUF_RD_ERR_INT |
			  AES_DMA_INBUF_WR_ERR_INT |
			  AES_DMA_BAD_COMP_INT |
			  AES_DMA_SAI_INT,
			  aes_dev->base_reg + AES_A_DMA_MSI_IER_OFFSET);
		/*
		 * AES_IER
		 * शेष 0x00000000
		 * bits [31:3] - reserved
		 * bit [2] - EN_SKS_ERR
		 * bit [1] - EN_AES_COMPLETE
		 * bit [0] - reserved
		 */
		ioग_लिखो32(AES_COMPLETE_INT, aes_dev->base_reg + AES_IER_OFFSET);
		वापस;
	पूर्ण
	अगर (irq == AES_DMA_SRC_DONE_INT) अणु
		/* Ensure AES पूर्णांकerrupts are disabled */
		ioग_लिखो32(AES_DISABLE_INT, aes_dev->base_reg + AES_IER_OFFSET);
		/*
		 * DMA_MSI_IER
		 * शेष 0x00000000
		 * bits [31:9] - reserved
		 * bit [8] - CPD_ERR_INT_EN
		 * bit [7] - OUTBUF_RD_ERR_INT_EN
		 * bit [6] - OUTBUF_WR_ERR_INT_EN
		 * bit [5] - INBUF_RD_ERR_INT_EN
		 * bit [4] - INBUF_WR_ERR_INT_EN
		 * bit [3] - BAD_COMP_INT_EN
		 * bit [2] - SAI_INT_EN
		 * bit [1] - DST_DONE_INT_EN
		 * bit [0] - SRC_DONE_INT_EN
		 */
		ioग_लिखो32(AES_DMA_CPD_ERR_INT |
			  AES_DMA_OUTBUF_RD_ERR_INT |
			  AES_DMA_OUTBUF_WR_ERR_INT |
			  AES_DMA_INBUF_RD_ERR_INT |
			  AES_DMA_INBUF_WR_ERR_INT |
			  AES_DMA_BAD_COMP_INT |
			  AES_DMA_SAI_INT |
			  AES_DMA_SRC_DONE_INT,
			  aes_dev->base_reg + AES_A_DMA_MSI_IER_OFFSET);
	पूर्ण
पूर्ण

/* Enable and रुको क्रम IRQ (either from OCS AES engine or DMA) */
अटल पूर्णांक ocs_aes_irq_enable_and_रुको(काष्ठा ocs_aes_dev *aes_dev, u8 irq)
अणु
	पूर्णांक rc;

	reinit_completion(&aes_dev->irq_completion);
	aes_irq_enable(aes_dev, irq);
	rc = रुको_क्रम_completion_पूर्णांकerruptible(&aes_dev->irq_completion);
	अगर (rc)
		वापस rc;

	वापस aes_dev->dma_err_mask ? -EIO : 0;
पूर्ण

/* Configure DMA to OCS, linked list mode */
अटल अंतरभूत व्योम dma_to_ocs_aes_ll(काष्ठा ocs_aes_dev *aes_dev,
				     dma_addr_t dma_list)
अणु
	ioग_लिखो32(0, aes_dev->base_reg + AES_A_DMA_SRC_SIZE_OFFSET);
	ioग_लिखो32(dma_list,
		  aes_dev->base_reg + AES_A_DMA_NEXT_SRC_DESCR_OFFSET);
पूर्ण

/* Configure DMA from OCS, linked list mode */
अटल अंतरभूत व्योम dma_from_ocs_aes_ll(काष्ठा ocs_aes_dev *aes_dev,
				       dma_addr_t dma_list)
अणु
	ioग_लिखो32(0, aes_dev->base_reg + AES_A_DMA_DST_SIZE_OFFSET);
	ioग_लिखो32(dma_list,
		  aes_dev->base_reg + AES_A_DMA_NEXT_DST_DESCR_OFFSET);
पूर्ण

irqवापस_t ocs_aes_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ocs_aes_dev *aes_dev = dev_id;
	u32 aes_dma_isr;

	/* Read DMA ISR status. */
	aes_dma_isr = ioपढ़ो32(aes_dev->base_reg + AES_A_DMA_MSI_ISR_OFFSET);

	/* Disable and clear पूर्णांकerrupts. */
	aes_irq_disable(aes_dev);

	/* Save DMA error status. */
	aes_dev->dma_err_mask = aes_dma_isr &
				(AES_DMA_CPD_ERR_INT |
				 AES_DMA_OUTBUF_RD_ERR_INT |
				 AES_DMA_OUTBUF_WR_ERR_INT |
				 AES_DMA_INBUF_RD_ERR_INT |
				 AES_DMA_INBUF_WR_ERR_INT |
				 AES_DMA_BAD_COMP_INT |
				 AES_DMA_SAI_INT);

	/* Signal IRQ completion. */
	complete(&aes_dev->irq_completion);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * ocs_aes_set_key() - Write key पूर्णांकo OCS AES hardware.
 * @aes_dev:	The OCS AES device to ग_लिखो the key to.
 * @key_size:	The size of the key (in bytes).
 * @key:	The key to ग_लिखो.
 * @cipher:	The cipher the key is क्रम.
 *
 * For AES @key_size must be either 16 or 32. For SM4 @key_size must be 16.
 *
 * Return:	0 on success, negative error code otherwise.
 */
पूर्णांक ocs_aes_set_key(काष्ठा ocs_aes_dev *aes_dev, u32 key_size, स्थिर u8 *key,
		    क्रमागत ocs_cipher cipher)
अणु
	स्थिर u32 *key_u32;
	u32 val;
	पूर्णांक i;

	/* OCS AES supports 128-bit and 256-bit keys only. */
	अगर (cipher == OCS_AES && !(key_size == 32 || key_size == 16)) अणु
		dev_err(aes_dev->dev,
			"%d-bit keys not supported by AES cipher\n",
			key_size * 8);
		वापस -EINVAL;
	पूर्ण
	/* OCS SM4 supports 128-bit keys only. */
	अगर (cipher == OCS_SM4 && key_size != 16) अणु
		dev_err(aes_dev->dev,
			"%d-bit keys not supported for SM4 cipher\n",
			key_size * 8);
		वापस -EINVAL;
	पूर्ण

	अगर (!key)
		वापस -EINVAL;

	key_u32 = (स्थिर u32 *)key;

	/* Write key to AES_KEY[0-7] रेजिस्टरs */
	क्रम (i = 0; i < (key_size / माप(u32)); i++) अणु
		ioग_लिखो32(key_u32[i],
			  aes_dev->base_reg + AES_KEY_0_OFFSET +
			  (i * माप(u32)));
	पूर्ण
	/*
	 * Write key size
	 * bits [31:1] - reserved
	 * bit [0] - AES_KEY_SIZE
	 *           0 - 128 bit key
	 *           1 - 256 bit key
	 */
	val = (key_size == 16) ? AES_128_BIT_KEY : AES_256_BIT_KEY;
	ioग_लिखो32(val, aes_dev->base_reg + AES_KEY_SIZE_OFFSET);

	वापस 0;
पूर्ण

/* Write AES_COMMAND */
अटल अंतरभूत व्योम set_ocs_aes_command(काष्ठा ocs_aes_dev *aes_dev,
				       क्रमागत ocs_cipher cipher,
				       क्रमागत ocs_mode mode,
				       क्रमागत ocs_inकाष्ठाion inकाष्ठाion)
अणु
	u32 val;

	/* AES_COMMAND
	 * शेष 0x000000CC
	 * bit [14] - CIPHER_SELECT
	 *            0 - AES
	 *            1 - SM4
	 * bits [11:8] - OCS_AES_MODE
	 *               0000 - ECB
	 *               0001 - CBC
	 *               0010 - CTR
	 *               0110 - CCM
	 *               0111 - GCM
	 *               1001 - CTS
	 * bits [7:6] - AES_INSTRUCTION
	 *              00 - ENCRYPT
	 *              01 - DECRYPT
	 *              10 - EXPAND
	 *              11 - BYPASS
	 * bits [3:2] - CTR_M_BITS
	 *              00 - No increment
	 *              01 - Least signअगरicant 32 bits are incremented
	 *              10 - Least signअगरicant 64 bits are incremented
	 *              11 - Full 128 bits are incremented
	 */
	val = (cipher << 14) | (mode << 8) | (inकाष्ठाion << 6) |
	      (AES_CTR_M_128_INC << 2);
	ioग_लिखो32(val, aes_dev->base_reg + AES_COMMAND_OFFSET);
पूर्ण

अटल व्योम ocs_aes_init(काष्ठा ocs_aes_dev *aes_dev,
			 क्रमागत ocs_mode mode,
			 क्रमागत ocs_cipher cipher,
			 क्रमागत ocs_inकाष्ठाion inकाष्ठाion)
अणु
	/* Ensure पूर्णांकerrupts are disabled and pending पूर्णांकerrupts cleared. */
	aes_irq_disable(aes_dev);

	/* Set endianness recommended by data-sheet. */
	aes_a_set_endianness(aes_dev);

	/* Set AES_COMMAND रेजिस्टर. */
	set_ocs_aes_command(aes_dev, cipher, mode, inकाष्ठाion);
पूर्ण

/*
 * Write the byte length of the last AES/SM4 block of Payload data (without
 * zero padding and without the length of the MAC) in रेजिस्टर AES_PLEN.
 */
अटल अंतरभूत व्योम ocs_aes_ग_लिखो_last_data_blk_len(काष्ठा ocs_aes_dev *aes_dev,
						   u32 size)
अणु
	u32 val;

	अगर (size == 0) अणु
		val = 0;
		जाओ निकास;
	पूर्ण

	val = size % AES_BLOCK_SIZE;
	अगर (val == 0)
		val = AES_BLOCK_SIZE;

निकास:
	ioग_लिखो32(val, aes_dev->base_reg + AES_PLEN_OFFSET);
पूर्ण

/*
 * Validate inमाला_दो according to mode.
 * If OK वापस 0; अन्यथा वापस -EINVAL.
 */
अटल पूर्णांक ocs_aes_validate_inमाला_दो(dma_addr_t src_dma_list, u32 src_size,
				   स्थिर u8 *iv, u32 iv_size,
				   dma_addr_t aad_dma_list, u32 aad_size,
				   स्थिर u8 *tag, u32 tag_size,
				   क्रमागत ocs_cipher cipher, क्रमागत ocs_mode mode,
				   क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
				   dma_addr_t dst_dma_list)
अणु
	/* Ensure cipher, mode and inकाष्ठाion are valid. */
	अगर (!(cipher == OCS_AES || cipher == OCS_SM4))
		वापस -EINVAL;

	अगर (mode != OCS_MODE_ECB && mode != OCS_MODE_CBC &&
	    mode != OCS_MODE_CTR && mode != OCS_MODE_CCM &&
	    mode != OCS_MODE_GCM && mode != OCS_MODE_CTS)
		वापस -EINVAL;

	अगर (inकाष्ठाion != OCS_ENCRYPT && inकाष्ठाion != OCS_DECRYPT &&
	    inकाष्ठाion != OCS_EXPAND  && inकाष्ठाion != OCS_BYPASS)
		वापस -EINVAL;

	/*
	 * When inकाष्ठाion is OCS_BYPASS, OCS simply copies data from source
	 * to destination using DMA.
	 *
	 * AES mode is irrelevant, but both source and destination DMA
	 * linked-list must be defined.
	 */
	अगर (inकाष्ठाion == OCS_BYPASS) अणु
		अगर (src_dma_list == DMA_MAPPING_ERROR ||
		    dst_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		वापस 0;
	पूर्ण

	/*
	 * For perक्रमmance reasons चयन based on mode to limit unnecessary
	 * conditionals क्रम each mode
	 */
	चयन (mode) अणु
	हाल OCS_MODE_ECB:
		/* Ensure input length is multiple of block size */
		अगर (src_size % AES_BLOCK_SIZE != 0)
			वापस -EINVAL;

		/* Ensure source and destination linked lists are created */
		अगर (src_dma_list == DMA_MAPPING_ERROR ||
		    dst_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_CBC:
		/* Ensure input length is multiple of block size */
		अगर (src_size % AES_BLOCK_SIZE != 0)
			वापस -EINVAL;

		/* Ensure source and destination linked lists are created */
		अगर (src_dma_list == DMA_MAPPING_ERROR ||
		    dst_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		/* Ensure IV is present and block size in length */
		अगर (!iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_CTR:
		/* Ensure input length of 1 byte or greater */
		अगर (src_size == 0)
			वापस -EINVAL;

		/* Ensure source and destination linked lists are created */
		अगर (src_dma_list == DMA_MAPPING_ERROR ||
		    dst_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		/* Ensure IV is present and block size in length */
		अगर (!iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_CTS:
		/* Ensure input length >= block size */
		अगर (src_size < AES_BLOCK_SIZE)
			वापस -EINVAL;

		/* Ensure source and destination linked lists are created */
		अगर (src_dma_list == DMA_MAPPING_ERROR ||
		    dst_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		/* Ensure IV is present and block size in length */
		अगर (!iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_GCM:
		/* Ensure IV is present and GCM_AES_IV_SIZE in length */
		अगर (!iv || iv_size != GCM_AES_IV_SIZE)
			वापस -EINVAL;

		/*
		 * If input data present ensure source and destination linked
		 * lists are created
		 */
		अगर (src_size && (src_dma_list == DMA_MAPPING_ERROR ||
				 dst_dma_list == DMA_MAPPING_ERROR))
			वापस -EINVAL;

		/* If aad present ensure aad linked list is created */
		अगर (aad_size && aad_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		/* Ensure tag destination is set */
		अगर (!tag)
			वापस -EINVAL;

		/* Just ensure that tag_size करोesn't cause overflows. */
		अगर (tag_size > (AES_MAX_TAG_SIZE_U32 * माप(u32)))
			वापस -EINVAL;

		वापस 0;

	हाल OCS_MODE_CCM:
		/* Ensure IV is present and block size in length */
		अगर (!iv || iv_size != AES_BLOCK_SIZE)
			वापस -EINVAL;

		/* 2 <= L <= 8, so 1 <= L' <= 7 */
		अगर (iv[L_PRIME_IDX] < L_PRIME_MIN ||
		    iv[L_PRIME_IDX] > L_PRIME_MAX)
			वापस -EINVAL;

		/* If aad present ensure aad linked list is created */
		अगर (aad_size && aad_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		/* Just ensure that tag_size करोesn't cause overflows. */
		अगर (tag_size > (AES_MAX_TAG_SIZE_U32 * माप(u32)))
			वापस -EINVAL;

		अगर (inकाष्ठाion == OCS_DECRYPT) अणु
			/*
			 * If input data present ensure source and destination
			 * linked lists are created
			 */
			अगर (src_size && (src_dma_list == DMA_MAPPING_ERROR ||
					 dst_dma_list == DMA_MAPPING_ERROR))
				वापस -EINVAL;

			/* Ensure input tag is present */
			अगर (!tag)
				वापस -EINVAL;

			वापस 0;
		पूर्ण

		/* Inकाष्ठाion == OCS_ENCRYPT */

		/*
		 * Destination linked list always required (क्रम tag even अगर no
		 * input data)
		 */
		अगर (dst_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		/* If input data present ensure src linked list is created */
		अगर (src_size && src_dma_list == DMA_MAPPING_ERROR)
			वापस -EINVAL;

		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

/**
 * ocs_aes_op() - Perक्रमm AES/SM4 operation.
 * @aes_dev:		The OCS AES device to use.
 * @mode:		The mode to use (ECB, CBC, CTR, or CTS).
 * @cipher:		The cipher to use (AES or SM4).
 * @inकाष्ठाion:	The inकाष्ठाion to perक्रमm (encrypt or decrypt).
 * @dst_dma_list:	The OCS DMA list mapping output memory.
 * @src_dma_list:	The OCS DMA list mapping input payload data.
 * @src_size:		The amount of data mapped by @src_dma_list.
 * @iv:			The IV vector.
 * @iv_size:		The size (in bytes) of @iv.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक ocs_aes_op(काष्ठा ocs_aes_dev *aes_dev,
	       क्रमागत ocs_mode mode,
	       क्रमागत ocs_cipher cipher,
	       क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
	       dma_addr_t dst_dma_list,
	       dma_addr_t src_dma_list,
	       u32 src_size,
	       u8 *iv,
	       u32 iv_size)
अणु
	u32 *iv32;
	पूर्णांक rc;

	rc = ocs_aes_validate_inमाला_दो(src_dma_list, src_size, iv, iv_size, 0, 0,
				     शून्य, 0, cipher, mode, inकाष्ठाion,
				     dst_dma_list);
	अगर (rc)
		वापस rc;
	/*
	 * ocs_aes_validate_inमाला_दो() is a generic check, now ensure mode is not
	 * GCM or CCM.
	 */
	अगर (mode == OCS_MODE_GCM || mode == OCS_MODE_CCM)
		वापस -EINVAL;

	/* Cast IV to u32 array. */
	iv32 = (u32 *)iv;

	ocs_aes_init(aes_dev, mode, cipher, inकाष्ठाion);

	अगर (mode == OCS_MODE_CTS) अणु
		/* Write the byte length of the last data block to engine. */
		ocs_aes_ग_लिखो_last_data_blk_len(aes_dev, src_size);
	पूर्ण

	/* ECB is the only mode that करोesn't use IV. */
	अगर (mode != OCS_MODE_ECB) अणु
		ioग_लिखो32(iv32[0], aes_dev->base_reg + AES_IV_0_OFFSET);
		ioग_लिखो32(iv32[1], aes_dev->base_reg + AES_IV_1_OFFSET);
		ioग_लिखो32(iv32[2], aes_dev->base_reg + AES_IV_2_OFFSET);
		ioग_लिखो32(iv32[3], aes_dev->base_reg + AES_IV_3_OFFSET);
	पूर्ण

	/* Set AES_ACTIVE.TRIGGER to start the operation. */
	aes_a_op_trigger(aes_dev);

	/* Configure and activate input / output DMA. */
	dma_to_ocs_aes_ll(aes_dev, src_dma_list);
	dma_from_ocs_aes_ll(aes_dev, dst_dma_list);
	aes_a_dma_active_src_dst_ll_en(aes_dev);

	अगर (mode == OCS_MODE_CTS) अणु
		/*
		 * For CTS mode, inकाष्ठा engine to activate ciphertext
		 * stealing अगर last block of data is incomplete.
		 */
		aes_a_set_last_gcx(aes_dev);
	पूर्ण अन्यथा अणु
		/* For all other modes, just ग_लिखो the 'termination' bit. */
		aes_a_op_termination(aes_dev);
	पूर्ण

	/* Wait क्रम engine to complete processing. */
	rc = ocs_aes_irq_enable_and_रुको(aes_dev, AES_COMPLETE_INT);
	अगर (rc)
		वापस rc;

	अगर (mode == OCS_MODE_CTR) अणु
		/* Read back IV क्रम streaming mode */
		iv32[0] = ioपढ़ो32(aes_dev->base_reg + AES_IV_0_OFFSET);
		iv32[1] = ioपढ़ो32(aes_dev->base_reg + AES_IV_1_OFFSET);
		iv32[2] = ioपढ़ो32(aes_dev->base_reg + AES_IV_2_OFFSET);
		iv32[3] = ioपढ़ो32(aes_dev->base_reg + AES_IV_3_OFFSET);
	पूर्ण

	वापस 0;
पूर्ण

/* Compute and ग_लिखो J0 to engine रेजिस्टरs. */
अटल व्योम ocs_aes_gcm_ग_लिखो_j0(स्थिर काष्ठा ocs_aes_dev *aes_dev,
				 स्थिर u8 *iv)
अणु
	स्थिर u32 *j0 = (u32 *)iv;

	/*
	 * IV must be 12 bytes; Other sizes not supported as Linux crypto API
	 * करोes only expects/allows 12 byte IV क्रम GCM
	 */
	ioग_लिखो32(0x00000001, aes_dev->base_reg + AES_IV_0_OFFSET);
	ioग_लिखो32(__swab32(j0[2]), aes_dev->base_reg + AES_IV_1_OFFSET);
	ioग_लिखो32(__swab32(j0[1]), aes_dev->base_reg + AES_IV_2_OFFSET);
	ioग_लिखो32(__swab32(j0[0]), aes_dev->base_reg + AES_IV_3_OFFSET);
पूर्ण

/* Read GCM tag from engine रेजिस्टरs. */
अटल अंतरभूत व्योम ocs_aes_gcm_पढ़ो_tag(काष्ठा ocs_aes_dev *aes_dev,
					u8 *tag, u32 tag_size)
अणु
	u32 tag_u32[AES_MAX_TAG_SIZE_U32];

	/*
	 * The Authentication Tag T is stored in Little Endian order in the
	 * रेजिस्टरs with the most signअगरicant bytes stored from AES_T_MAC[3]
	 * करोwnward.
	 */
	tag_u32[0] = __swab32(ioपढ़ो32(aes_dev->base_reg + AES_T_MAC_3_OFFSET));
	tag_u32[1] = __swab32(ioपढ़ो32(aes_dev->base_reg + AES_T_MAC_2_OFFSET));
	tag_u32[2] = __swab32(ioपढ़ो32(aes_dev->base_reg + AES_T_MAC_1_OFFSET));
	tag_u32[3] = __swab32(ioपढ़ो32(aes_dev->base_reg + AES_T_MAC_0_OFFSET));

	स_नकल(tag, tag_u32, tag_size);
पूर्ण

/**
 * ocs_aes_gcm_op() - Perक्रमm GCM operation.
 * @aes_dev:		The OCS AES device to use.
 * @cipher:		The Cipher to use (AES or SM4).
 * @inकाष्ठाion:	The inकाष्ठाion to perक्रमm (encrypt or decrypt).
 * @dst_dma_list:	The OCS DMA list mapping output memory.
 * @src_dma_list:	The OCS DMA list mapping input payload data.
 * @src_size:		The amount of data mapped by @src_dma_list.
 * @iv:			The input IV vector.
 * @aad_dma_list:	The OCS DMA list mapping input AAD data.
 * @aad_size:		The amount of data mapped by @aad_dma_list.
 * @out_tag:		Where to store computed tag.
 * @tag_size:		The size (in bytes) of @out_tag.
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक ocs_aes_gcm_op(काष्ठा ocs_aes_dev *aes_dev,
		   क्रमागत ocs_cipher cipher,
		   क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
		   dma_addr_t dst_dma_list,
		   dma_addr_t src_dma_list,
		   u32 src_size,
		   स्थिर u8 *iv,
		   dma_addr_t aad_dma_list,
		   u32 aad_size,
		   u8 *out_tag,
		   u32 tag_size)
अणु
	u64 bit_len;
	u32 val;
	पूर्णांक rc;

	rc = ocs_aes_validate_inमाला_दो(src_dma_list, src_size, iv,
				     GCM_AES_IV_SIZE, aad_dma_list,
				     aad_size, out_tag, tag_size, cipher,
				     OCS_MODE_GCM, inकाष्ठाion,
				     dst_dma_list);
	अगर (rc)
		वापस rc;

	ocs_aes_init(aes_dev, OCS_MODE_GCM, cipher, inकाष्ठाion);

	/* Compute and ग_लिखो J0 to OCS HW. */
	ocs_aes_gcm_ग_लिखो_j0(aes_dev, iv);

	/* Write out_tag byte length */
	ioग_लिखो32(tag_size, aes_dev->base_reg + AES_TLEN_OFFSET);

	/* Write the byte length of the last plaपूर्णांकext / ciphertext block. */
	ocs_aes_ग_लिखो_last_data_blk_len(aes_dev, src_size);

	/* Write ciphertext bit length */
	bit_len = (u64)src_size * 8;
	val = bit_len & 0xFFFFFFFF;
	ioग_लिखो32(val, aes_dev->base_reg + AES_MULTIPURPOSE2_0_OFFSET);
	val = bit_len >> 32;
	ioग_लिखो32(val, aes_dev->base_reg + AES_MULTIPURPOSE2_1_OFFSET);

	/* Write aad bit length */
	bit_len = (u64)aad_size * 8;
	val = bit_len & 0xFFFFFFFF;
	ioग_लिखो32(val, aes_dev->base_reg + AES_MULTIPURPOSE2_2_OFFSET);
	val = bit_len >> 32;
	ioग_लिखो32(val, aes_dev->base_reg + AES_MULTIPURPOSE2_3_OFFSET);

	/* Set AES_ACTIVE.TRIGGER to start the operation. */
	aes_a_op_trigger(aes_dev);

	/* Process AAD. */
	अगर (aad_size) अणु
		/* If aad present, configure DMA to feed it to the engine. */
		dma_to_ocs_aes_ll(aes_dev, aad_dma_list);
		aes_a_dma_active_src_ll_en(aes_dev);

		/* Inकाष्ठाs engine to pad last block of aad, अगर needed. */
		aes_a_set_last_gcx_and_adata(aes_dev);

		/* Wait क्रम DMA transfer to complete. */
		rc = ocs_aes_irq_enable_and_रुको(aes_dev, AES_DMA_SRC_DONE_INT);
		अगर (rc)
			वापस rc;
	पूर्ण अन्यथा अणु
		aes_a_set_last_gcx_and_adata(aes_dev);
	पूर्ण

	/* Wait until adata (अगर present) has been processed. */
	aes_a_रुको_last_gcx(aes_dev);
	aes_a_dma_रुको_input_buffer_occupancy(aes_dev);

	/* Now process payload. */
	अगर (src_size) अणु
		/* Configure and activate DMA क्रम both input and output data. */
		dma_to_ocs_aes_ll(aes_dev, src_dma_list);
		dma_from_ocs_aes_ll(aes_dev, dst_dma_list);
		aes_a_dma_active_src_dst_ll_en(aes_dev);
	पूर्ण अन्यथा अणु
		aes_a_dma_set_xfer_size_zero(aes_dev);
		aes_a_dma_active(aes_dev);
	पूर्ण

	/* Inकाष्ठा AES/SMA4 engine payload processing is over. */
	aes_a_set_last_gcx(aes_dev);

	/* Wait क्रम OCS AES engine to complete processing. */
	rc = ocs_aes_irq_enable_and_रुको(aes_dev, AES_COMPLETE_INT);
	अगर (rc)
		वापस rc;

	ocs_aes_gcm_पढ़ो_tag(aes_dev, out_tag, tag_size);

	वापस 0;
पूर्ण

/* Write encrypted tag to AES/SM4 engine. */
अटल व्योम ocs_aes_ccm_ग_लिखो_encrypted_tag(काष्ठा ocs_aes_dev *aes_dev,
					    स्थिर u8 *in_tag, u32 tag_size)
अणु
	पूर्णांक i;

	/* Ensure DMA input buffer is empty */
	aes_a_dma_रुको_input_buffer_occupancy(aes_dev);

	/*
	 * During CCM decrypt, the OCS block needs to finish processing the
	 * ciphertext beक्रमe the tag is written.  So delay needed after DMA has
	 * completed writing the ciphertext
	 */
	aes_a_dma_reset_and_activate_perf_cntr(aes_dev);
	aes_a_dma_रुको_and_deactivate_perf_cntr(aes_dev,
						CCM_DECRYPT_DELAY_TAG_CLK_COUNT);

	/* Write encrypted tag to AES/SM4 engine. */
	क्रम (i = 0; i < tag_size; i++) अणु
		ioग_लिखो8(in_tag[i], aes_dev->base_reg +
				    AES_A_DMA_INBUFFER_WRITE_FIFO_OFFSET);
	पूर्ण
पूर्ण

/*
 * Write B0 CCM block to OCS AES HW.
 *
 * Note: B0 क्रमmat is करोcumented in NIST Special Publication 800-38C
 * https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialखुलाation800-38c.pdf
 * (see Section A.2.1)
 */
अटल पूर्णांक ocs_aes_ccm_ग_लिखो_b0(स्थिर काष्ठा ocs_aes_dev *aes_dev,
				स्थिर u8 *iv, u32 adata_size, u32 tag_size,
				u32 cryptlen)
अणु
	u8 b0[16]; /* CCM B0 block is 16 bytes दीर्घ. */
	पूर्णांक i, q;

	/* Initialize B0 to 0. */
	स_रखो(b0, 0, माप(b0));

	/*
	 * B0[0] is the 'Flags Octet' and has the following काष्ठाure:
	 *   bit 7: Reserved
	 *   bit 6: Adata flag
	 *   bit 5-3: t value encoded as (t-2)/2
	 *   bit 2-0: q value encoded as q - 1
	 */
	/* If there is AAD data, set the Adata flag. */
	अगर (adata_size)
		b0[0] |= BIT(6);
	/*
	 * t denotes the octet length of T.
	 * t can only be an element of अणु 4, 6, 8, 10, 12, 14, 16पूर्ण and is
	 * encoded as (t - 2) / 2
	 */
	b0[0] |= (((tag_size - 2) / 2) & 0x7)  << 3;
	/*
	 * q is the octet length of Q.
	 * q can only be an element of अणु2, 3, 4, 5, 6, 7, 8पूर्ण and is encoded as
	 * q - 1 == iv[0] & 0x7;
	 */
	b0[0] |= iv[0] & 0x7;
	/*
	 * Copy the Nonce N from IV to B0; N is located in iv[1]..iv[15 - q]
	 * and must be copied to b0[1]..b0[15-q].
	 * q == (iv[0] & 0x7) + 1
	 */
	q = (iv[0] & 0x7) + 1;
	क्रम (i = 1; i <= 15 - q; i++)
		b0[i] = iv[i];
	/*
	 * The rest of B0 must contain Q, i.e., the message length.
	 * Q is encoded in q octets, in big-endian order, so to ग_लिखो it, we
	 * start from the end of B0 and we move backward.
	 */
	i = माप(b0) - 1;
	जबतक (q) अणु
		b0[i] = cryptlen & 0xff;
		cryptlen >>= 8;
		i--;
		q--;
	पूर्ण
	/*
	 * If cryptlen is not zero at this poपूर्णांक, it means that its original
	 * value was too big.
	 */
	अगर (cryptlen)
		वापस -EOVERFLOW;
	/* Now ग_लिखो B0 to OCS AES input buffer. */
	क्रम (i = 0; i < माप(b0); i++)
		ioग_लिखो8(b0[i], aes_dev->base_reg +
				AES_A_DMA_INBUFFER_WRITE_FIFO_OFFSET);
	वापस 0;
पूर्ण

/*
 * Write adata length to OCS AES HW.
 *
 * Note: adata len encoding is करोcumented in NIST Special Publication 800-38C
 * https://nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialखुलाation800-38c.pdf
 * (see Section A.2.2)
 */
अटल व्योम ocs_aes_ccm_ग_लिखो_adata_len(स्थिर काष्ठा ocs_aes_dev *aes_dev,
					u64 adata_len)
अणु
	u8 enc_a[10]; /* Maximum encoded size: 10 octets. */
	पूर्णांक i, len;

	/*
	 * adata_len ('a') is encoded as follows:
	 * If 0 < a < 2^16 - 2^8    ==> 'a' encoded as [a]16, i.e., two octets
	 *				(big endian).
	 * If 2^16 - 2^8 ै	अ a < 2^32 ==> 'a' encoded as 0xff || 0xfe || [a]32,
	 *				i.e., six octets (big endian).
	 * If 2^32 ै	अ a < 2^64       ==> 'a' encoded as 0xff || 0xff || [a]64,
	 *				i.e., ten octets (big endian).
	 */
	अगर (adata_len < 65280) अणु
		len = 2;
		*(__be16 *)enc_a = cpu_to_be16(adata_len);
	पूर्ण अन्यथा अगर (adata_len <= 0xFFFFFFFF) अणु
		len = 6;
		*(__be16 *)enc_a = cpu_to_be16(0xfffe);
		*(__be32 *)&enc_a[2] = cpu_to_be32(adata_len);
	पूर्ण अन्यथा अणु /* adata_len >= 2^32 */
		len = 10;
		*(__be16 *)enc_a = cpu_to_be16(0xffff);
		*(__be64 *)&enc_a[2] = cpu_to_be64(adata_len);
	पूर्ण
	क्रम (i = 0; i < len; i++)
		ioग_लिखो8(enc_a[i],
			 aes_dev->base_reg +
			 AES_A_DMA_INBUFFER_WRITE_FIFO_OFFSET);
पूर्ण

अटल पूर्णांक ocs_aes_ccm_करो_adata(काष्ठा ocs_aes_dev *aes_dev,
				dma_addr_t adata_dma_list, u32 adata_size)
अणु
	पूर्णांक rc;

	अगर (!adata_size) अणु
		/* Since no aad the LAST_GCX bit can be set now */
		aes_a_set_last_gcx_and_adata(aes_dev);
		जाओ निकास;
	पूर्ण

	/* Adata हाल. */

	/*
	 * Form the encoding of the Associated data length and ग_लिखो it
	 * to the AES/SM4 input buffer.
	 */
	ocs_aes_ccm_ग_लिखो_adata_len(aes_dev, adata_size);

	/* Configure the AES/SM4 DMA to fetch the Associated Data */
	dma_to_ocs_aes_ll(aes_dev, adata_dma_list);

	/* Activate DMA to fetch Associated data. */
	aes_a_dma_active_src_ll_en(aes_dev);

	/* Set LAST_GCX and LAST_ADATA in AES ACTIVE रेजिस्टर. */
	aes_a_set_last_gcx_and_adata(aes_dev);

	/* Wait क्रम DMA transfer to complete. */
	rc = ocs_aes_irq_enable_and_रुको(aes_dev, AES_DMA_SRC_DONE_INT);
	अगर (rc)
		वापस rc;

निकास:
	/* Wait until adata (अगर present) has been processed. */
	aes_a_रुको_last_gcx(aes_dev);
	aes_a_dma_रुको_input_buffer_occupancy(aes_dev);

	वापस 0;
पूर्ण

अटल पूर्णांक ocs_aes_ccm_encrypt_करो_payload(काष्ठा ocs_aes_dev *aes_dev,
					  dma_addr_t dst_dma_list,
					  dma_addr_t src_dma_list,
					  u32 src_size)
अणु
	अगर (src_size) अणु
		/*
		 * Configure and activate DMA क्रम both input and output
		 * data.
		 */
		dma_to_ocs_aes_ll(aes_dev, src_dma_list);
		dma_from_ocs_aes_ll(aes_dev, dst_dma_list);
		aes_a_dma_active_src_dst_ll_en(aes_dev);
	पूर्ण अन्यथा अणु
		/* Configure and activate DMA क्रम output data only. */
		dma_from_ocs_aes_ll(aes_dev, dst_dma_list);
		aes_a_dma_active_dst_ll_en(aes_dev);
	पूर्ण

	/*
	 * Set the LAST GCX bit in AES_ACTIVE Register to inकाष्ठा
	 * AES/SM4 engine to pad the last block of data.
	 */
	aes_a_set_last_gcx(aes_dev);

	/* We are करोne, रुको क्रम IRQ and वापस. */
	वापस ocs_aes_irq_enable_and_रुको(aes_dev, AES_COMPLETE_INT);
पूर्ण

अटल पूर्णांक ocs_aes_ccm_decrypt_करो_payload(काष्ठा ocs_aes_dev *aes_dev,
					  dma_addr_t dst_dma_list,
					  dma_addr_t src_dma_list,
					  u32 src_size)
अणु
	अगर (!src_size) अणु
		/* Let engine process 0-length input. */
		aes_a_dma_set_xfer_size_zero(aes_dev);
		aes_a_dma_active(aes_dev);
		aes_a_set_last_gcx(aes_dev);

		वापस 0;
	पूर्ण

	/*
	 * Configure and activate DMA क्रम both input and output
	 * data.
	 */
	dma_to_ocs_aes_ll(aes_dev, src_dma_list);
	dma_from_ocs_aes_ll(aes_dev, dst_dma_list);
	aes_a_dma_active_src_dst_ll_en(aes_dev);
	/*
	 * Set the LAST GCX bit in AES_ACTIVE Register; this allows the
	 * AES/SM4 engine to dअगरferentiate between encrypted data and
	 * encrypted MAC.
	 */
	aes_a_set_last_gcx(aes_dev);
	 /*
	  * Enable DMA DONE पूर्णांकerrupt; once DMA transfer is over,
	  * पूर्णांकerrupt handler will process the MAC/tag.
	  */
	वापस ocs_aes_irq_enable_and_रुको(aes_dev, AES_DMA_SRC_DONE_INT);
पूर्ण

/*
 * Compare Tag to Yr.
 *
 * Only used at the end of CCM decrypt. If tag == yr, message authentication
 * has succeeded.
 */
अटल अंतरभूत पूर्णांक ccm_compare_tag_to_yr(काष्ठा ocs_aes_dev *aes_dev,
					u8 tag_size_bytes)
अणु
	u32 tag[AES_MAX_TAG_SIZE_U32];
	u32 yr[AES_MAX_TAG_SIZE_U32];
	u8 i;

	/* Read Tag and Yr from AES रेजिस्टरs. */
	क्रम (i = 0; i < AES_MAX_TAG_SIZE_U32; i++) अणु
		tag[i] = ioपढ़ो32(aes_dev->base_reg +
				  AES_T_MAC_0_OFFSET + (i * माप(u32)));
		yr[i] = ioपढ़ो32(aes_dev->base_reg +
				 AES_MULTIPURPOSE2_0_OFFSET +
				 (i * माप(u32)));
	पूर्ण

	वापस स_भेद(tag, yr, tag_size_bytes) ? -EBADMSG : 0;
पूर्ण

/**
 * ocs_aes_ccm_op() - Perक्रमm CCM operation.
 * @aes_dev:		The OCS AES device to use.
 * @cipher:		The Cipher to use (AES or SM4).
 * @inकाष्ठाion:	The inकाष्ठाion to perक्रमm (encrypt or decrypt).
 * @dst_dma_list:	The OCS DMA list mapping output memory.
 * @src_dma_list:	The OCS DMA list mapping input payload data.
 * @src_size:		The amount of data mapped by @src_dma_list.
 * @iv:			The input IV vector.
 * @adata_dma_list:	The OCS DMA list mapping input A-data.
 * @adata_size:		The amount of data mapped by @adata_dma_list.
 * @in_tag:		Input tag.
 * @tag_size:		The size (in bytes) of @in_tag.
 *
 * Note: क्रम encrypt the tag is appended to the ciphertext (in the memory
 *	 mapped by @dst_dma_list).
 *
 * Return: 0 on success, negative error code otherwise.
 */
पूर्णांक ocs_aes_ccm_op(काष्ठा ocs_aes_dev *aes_dev,
		   क्रमागत ocs_cipher cipher,
		   क्रमागत ocs_inकाष्ठाion inकाष्ठाion,
		   dma_addr_t dst_dma_list,
		   dma_addr_t src_dma_list,
		   u32 src_size,
		   u8 *iv,
		   dma_addr_t adata_dma_list,
		   u32 adata_size,
		   u8 *in_tag,
		   u32 tag_size)
अणु
	u32 *iv_32;
	u8 lprime;
	पूर्णांक rc;

	rc = ocs_aes_validate_inमाला_दो(src_dma_list, src_size, iv,
				     AES_BLOCK_SIZE, adata_dma_list, adata_size,
				     in_tag, tag_size, cipher, OCS_MODE_CCM,
				     inकाष्ठाion, dst_dma_list);
	अगर (rc)
		वापस rc;

	ocs_aes_init(aes_dev, OCS_MODE_CCM, cipher, inकाष्ठाion);

	/*
	 * Note: rfc 3610 and NIST 800-38C require counter of zero to encrypt
	 * auth tag so ensure this is the हाल
	 */
	lprime = iv[L_PRIME_IDX];
	स_रखो(&iv[COUNTER_START(lprime)], 0, COUNTER_LEN(lprime));

	/*
	 * Nonce is alपढ़ोy converted to ctr0 beक्रमe being passed पूर्णांकo this
	 * function as iv.
	 */
	iv_32 = (u32 *)iv;
	ioग_लिखो32(__swab32(iv_32[0]),
		  aes_dev->base_reg + AES_MULTIPURPOSE1_3_OFFSET);
	ioग_लिखो32(__swab32(iv_32[1]),
		  aes_dev->base_reg + AES_MULTIPURPOSE1_2_OFFSET);
	ioग_लिखो32(__swab32(iv_32[2]),
		  aes_dev->base_reg + AES_MULTIPURPOSE1_1_OFFSET);
	ioग_लिखो32(__swab32(iv_32[3]),
		  aes_dev->base_reg + AES_MULTIPURPOSE1_0_OFFSET);

	/* Write MAC/tag length in रेजिस्टर AES_TLEN */
	ioग_लिखो32(tag_size, aes_dev->base_reg + AES_TLEN_OFFSET);
	/*
	 * Write the byte length of the last AES/SM4 block of Payload data
	 * (without zero padding and without the length of the MAC) in रेजिस्टर
	 * AES_PLEN.
	 */
	ocs_aes_ग_लिखो_last_data_blk_len(aes_dev, src_size);

	/* Set AES_ACTIVE.TRIGGER to start the operation. */
	aes_a_op_trigger(aes_dev);

	aes_a_dma_reset_and_activate_perf_cntr(aes_dev);

	/* Form block B0 and ग_लिखो it to the AES/SM4 input buffer. */
	rc = ocs_aes_ccm_ग_लिखो_b0(aes_dev, iv, adata_size, tag_size, src_size);
	अगर (rc)
		वापस rc;
	/*
	 * Ensure there has been at least CCM_DECRYPT_DELAY_LAST_GCX_CLK_COUNT
	 * घड़ी cycles since TRIGGER bit was set
	 */
	aes_a_dma_रुको_and_deactivate_perf_cntr(aes_dev,
						CCM_DECRYPT_DELAY_LAST_GCX_CLK_COUNT);

	/* Process Adata. */
	ocs_aes_ccm_करो_adata(aes_dev, adata_dma_list, adata_size);

	/* For Encrypt हाल we just process the payload and वापस. */
	अगर (inकाष्ठाion == OCS_ENCRYPT) अणु
		वापस ocs_aes_ccm_encrypt_करो_payload(aes_dev, dst_dma_list,
						      src_dma_list, src_size);
	पूर्ण
	/* For Decypt we need to process the payload and then the tag. */
	rc = ocs_aes_ccm_decrypt_करो_payload(aes_dev, dst_dma_list,
					    src_dma_list, src_size);
	अगर (rc)
		वापस rc;

	/* Process MAC/tag directly: feed tag to engine and रुको क्रम IRQ. */
	ocs_aes_ccm_ग_लिखो_encrypted_tag(aes_dev, in_tag, tag_size);
	rc = ocs_aes_irq_enable_and_रुको(aes_dev, AES_COMPLETE_INT);
	अगर (rc)
		वापस rc;

	वापस ccm_compare_tag_to_yr(aes_dev, tag_size);
पूर्ण

/**
 * ocs_create_linked_list_from_sg() - Create OCS DMA linked list from SG list.
 * @aes_dev:	  The OCS AES device the list will be created क्रम.
 * @sg:		  The SG list OCS DMA linked list will be created from. When
 *		  passed to this function, @sg must have been alपढ़ोy mapped
 *		  with dma_map_sg().
 * @sg_dma_count: The number of DMA-mapped entries in @sg. This must be the
 *		  value वापसed by dma_map_sg() when @sg was mapped.
 * @dll_desc:	  The OCS DMA dma_list to use to store inक्रमmation about the
 *		  created linked list.
 * @data_size:	  The size of the data (from the SG list) to be mapped पूर्णांकo the
 *		  OCS DMA linked list.
 * @data_offset:  The offset (within the SG list) of the data to be mapped.
 *
 * Return:	0 on success, negative error code otherwise.
 */
पूर्णांक ocs_create_linked_list_from_sg(स्थिर काष्ठा ocs_aes_dev *aes_dev,
				   काष्ठा scatterlist *sg,
				   पूर्णांक sg_dma_count,
				   काष्ठा ocs_dll_desc *dll_desc,
				   माप_प्रकार data_size, माप_प्रकार data_offset)
अणु
	काष्ठा ocs_dma_linked_list *ll = शून्य;
	काष्ठा scatterlist *sg_पंचांगp;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक dma_nents;
	पूर्णांक i;

	अगर (!dll_desc || !sg || !aes_dev)
		वापस -EINVAL;

	/* Default values क्रम when no ddl_desc is created. */
	dll_desc->vaddr = शून्य;
	dll_desc->dma_addr = DMA_MAPPING_ERROR;
	dll_desc->size = 0;

	अगर (data_size == 0)
		वापस 0;

	/* Loop over sg_list until we reach entry at specअगरied offset. */
	जबतक (data_offset >= sg_dma_len(sg)) अणु
		data_offset -= sg_dma_len(sg);
		sg_dma_count--;
		sg = sg_next(sg);
		/* If we reach the end of the list, offset was invalid. */
		अगर (!sg || sg_dma_count == 0)
			वापस -EINVAL;
	पूर्ण

	/* Compute number of DMA-mapped SG entries to add पूर्णांकo OCS DMA list. */
	dma_nents = 0;
	पंचांगp = 0;
	sg_पंचांगp = sg;
	जबतक (पंचांगp < data_offset + data_size) अणु
		/* If we reach the end of the list, data_size was invalid. */
		अगर (!sg_पंचांगp)
			वापस -EINVAL;
		पंचांगp += sg_dma_len(sg_पंचांगp);
		dma_nents++;
		sg_पंचांगp = sg_next(sg_पंचांगp);
	पूर्ण
	अगर (dma_nents > sg_dma_count)
		वापस -EINVAL;

	/* Allocate the DMA list, one entry क्रम each SG entry. */
	dll_desc->size = माप(काष्ठा ocs_dma_linked_list) * dma_nents;
	dll_desc->vaddr = dma_alloc_coherent(aes_dev->dev, dll_desc->size,
					     &dll_desc->dma_addr, GFP_KERNEL);
	अगर (!dll_desc->vaddr)
		वापस -ENOMEM;

	/* Populate DMA linked list entries. */
	ll = dll_desc->vaddr;
	क्रम (i = 0; i < dma_nents; i++, sg = sg_next(sg)) अणु
		ll[i].src_addr = sg_dma_address(sg) + data_offset;
		ll[i].src_len = (sg_dma_len(sg) - data_offset) < data_size ?
				(sg_dma_len(sg) - data_offset) : data_size;
		data_offset = 0;
		data_size -= ll[i].src_len;
		/* Current element poपूर्णांकs to the DMA address of the next one. */
		ll[i].next = dll_desc->dma_addr + (माप(*ll) * (i + 1));
		ll[i].ll_flags = 0;
	पूर्ण
	/* Terminate last element. */
	ll[i - 1].next = 0;
	ll[i - 1].ll_flags = OCS_LL_DMA_FLAG_TERMINATE;

	वापस 0;
पूर्ण
