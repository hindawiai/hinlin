<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2011-2014, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DMA_H_
#घोषणा _DMA_H_

#समावेश <linux/dmaengine.h>

/* maximum data transfer block size between BAM and CE */
#घोषणा QCE_BAM_BURST_SIZE		64

#घोषणा QCE_AUTHIV_REGS_CNT		16
#घोषणा QCE_AUTH_BYTECOUNT_REGS_CNT	4
#घोषणा QCE_CNTRIV_REGS_CNT		4

काष्ठा qce_result_dump अणु
	u32 auth_iv[QCE_AUTHIV_REGS_CNT];
	u32 auth_byte_count[QCE_AUTH_BYTECOUNT_REGS_CNT];
	u32 encr_cntr_iv[QCE_CNTRIV_REGS_CNT];
	u32 status;
	u32 status2;
पूर्ण;

#घोषणा QCE_IGNORE_BUF_SZ	(2 * QCE_BAM_BURST_SIZE)
#घोषणा QCE_RESULT_BUF_SZ	\
		ALIGN(माप(काष्ठा qce_result_dump), QCE_BAM_BURST_SIZE)

काष्ठा qce_dma_data अणु
	काष्ठा dma_chan *txchan;
	काष्ठा dma_chan *rxchan;
	काष्ठा qce_result_dump *result_buf;
	व्योम *ignore_buf;
पूर्ण;

पूर्णांक qce_dma_request(काष्ठा device *dev, काष्ठा qce_dma_data *dma);
व्योम qce_dma_release(काष्ठा qce_dma_data *dma);
पूर्णांक qce_dma_prep_sgs(काष्ठा qce_dma_data *dma, काष्ठा scatterlist *sg_in,
		     पूर्णांक in_ents, काष्ठा scatterlist *sg_out, पूर्णांक out_ents,
		     dma_async_tx_callback cb, व्योम *cb_param);
व्योम qce_dma_issue_pending(काष्ठा qce_dma_data *dma);
पूर्णांक qce_dma_terminate_all(काष्ठा qce_dma_data *dma);
काष्ठा scatterlist *
qce_sgtable_add(काष्ठा sg_table *sgt, काष्ठा scatterlist *sg_add,
		अचिन्हित पूर्णांक max_len);

#पूर्ण_अगर /* _DMA_H_ */
