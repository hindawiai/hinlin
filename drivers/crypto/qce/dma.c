<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2014, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/dmaengine.h>
#समावेश <crypto/scatterwalk.h>

#समावेश "dma.h"

पूर्णांक qce_dma_request(काष्ठा device *dev, काष्ठा qce_dma_data *dma)
अणु
	पूर्णांक ret;

	dma->txchan = dma_request_chan(dev, "tx");
	अगर (IS_ERR(dma->txchan))
		वापस PTR_ERR(dma->txchan);

	dma->rxchan = dma_request_chan(dev, "rx");
	अगर (IS_ERR(dma->rxchan)) अणु
		ret = PTR_ERR(dma->rxchan);
		जाओ error_rx;
	पूर्ण

	dma->result_buf = kदो_स्मृति(QCE_RESULT_BUF_SZ + QCE_IGNORE_BUF_SZ,
				  GFP_KERNEL);
	अगर (!dma->result_buf) अणु
		ret = -ENOMEM;
		जाओ error_nomem;
	पूर्ण

	dma->ignore_buf = dma->result_buf + QCE_RESULT_BUF_SZ;

	वापस 0;
error_nomem:
	dma_release_channel(dma->rxchan);
error_rx:
	dma_release_channel(dma->txchan);
	वापस ret;
पूर्ण

व्योम qce_dma_release(काष्ठा qce_dma_data *dma)
अणु
	dma_release_channel(dma->txchan);
	dma_release_channel(dma->rxchan);
	kमुक्त(dma->result_buf);
पूर्ण

काष्ठा scatterlist *
qce_sgtable_add(काष्ठा sg_table *sgt, काष्ठा scatterlist *new_sgl,
		अचिन्हित पूर्णांक max_len)
अणु
	काष्ठा scatterlist *sg = sgt->sgl, *sg_last = शून्य;
	अचिन्हित पूर्णांक new_len;

	जबतक (sg) अणु
		अगर (!sg_page(sg))
			अवरोध;
		sg = sg_next(sg);
	पूर्ण

	अगर (!sg)
		वापस ERR_PTR(-EINVAL);

	जबतक (new_sgl && sg && max_len) अणु
		new_len = new_sgl->length > max_len ? max_len : new_sgl->length;
		sg_set_page(sg, sg_page(new_sgl), new_len, new_sgl->offset);
		sg_last = sg;
		sg = sg_next(sg);
		new_sgl = sg_next(new_sgl);
		max_len -= new_len;
	पूर्ण

	वापस sg_last;
पूर्ण

अटल पूर्णांक qce_dma_prep_sg(काष्ठा dma_chan *chan, काष्ठा scatterlist *sg,
			   पूर्णांक nents, अचिन्हित दीर्घ flags,
			   क्रमागत dma_transfer_direction dir,
			   dma_async_tx_callback cb, व्योम *cb_param)
अणु
	काष्ठा dma_async_tx_descriptor *desc;
	dma_cookie_t cookie;

	अगर (!sg || !nents)
		वापस -EINVAL;

	desc = dmaengine_prep_slave_sg(chan, sg, nents, dir, flags);
	अगर (!desc)
		वापस -EINVAL;

	desc->callback = cb;
	desc->callback_param = cb_param;
	cookie = dmaengine_submit(desc);

	वापस dma_submit_error(cookie);
पूर्ण

पूर्णांक qce_dma_prep_sgs(काष्ठा qce_dma_data *dma, काष्ठा scatterlist *rx_sg,
		     पूर्णांक rx_nents, काष्ठा scatterlist *tx_sg, पूर्णांक tx_nents,
		     dma_async_tx_callback cb, व्योम *cb_param)
अणु
	काष्ठा dma_chan *rxchan = dma->rxchan;
	काष्ठा dma_chan *txchan = dma->txchan;
	अचिन्हित दीर्घ flags = DMA_PREP_INTERRUPT | DMA_CTRL_ACK;
	पूर्णांक ret;

	ret = qce_dma_prep_sg(rxchan, rx_sg, rx_nents, flags, DMA_MEM_TO_DEV,
			     शून्य, शून्य);
	अगर (ret)
		वापस ret;

	वापस qce_dma_prep_sg(txchan, tx_sg, tx_nents, flags, DMA_DEV_TO_MEM,
			       cb, cb_param);
पूर्ण

व्योम qce_dma_issue_pending(काष्ठा qce_dma_data *dma)
अणु
	dma_async_issue_pending(dma->rxchan);
	dma_async_issue_pending(dma->txchan);
पूर्ण

पूर्णांक qce_dma_terminate_all(काष्ठा qce_dma_data *dma)
अणु
	पूर्णांक ret;

	ret = dmaengine_terminate_all(dma->rxchan);
	वापस ret ?: dmaengine_terminate_all(dma->txchan);
पूर्ण
