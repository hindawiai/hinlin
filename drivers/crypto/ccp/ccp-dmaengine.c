<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMD Cryptographic Coprocessor (CCP) driver
 *
 * Copyright (C) 2016,2019 Advanced Micro Devices, Inc.
 *
 * Author: Gary R Hook <gary.hook@amd.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/ccp.h>

#समावेश "ccp-dev.h"
#समावेश "../../dma/dmaengine.h"

#घोषणा CCP_DMA_WIDTH(_mask)		\
(अणु					\
	u64 mask = _mask + 1;		\
	(mask == 0) ? 64 : fls64(mask);	\
पूर्ण)

/* The CCP as a DMA provider can be configured क्रम खुला or निजी
 * channels. Default is specअगरied in the vdata क्रम the device (PCI ID).
 * This module parameter will override क्रम all channels on all devices:
 *   dma_chan_attr = 0x2 to क्रमce all channels खुला
 *                 = 0x1 to क्रमce all channels निजी
 *                 = 0x0 to defer to the vdata setting
 *                 = any other value: warning, revert to 0x0
 */
अटल अचिन्हित पूर्णांक dma_chan_attr = CCP_DMA_DFLT;
module_param(dma_chan_attr, uपूर्णांक, 0444);
MODULE_PARM_DESC(dma_chan_attr, "Set DMA channel visibility: 0 (default) = device defaults, 1 = make private, 2 = make public");

अटल अचिन्हित पूर्णांक dmaengine = 1;
module_param(dmaengine, uपूर्णांक, 0444);
MODULE_PARM_DESC(dmaengine, "Register services with the DMA subsystem (any non-zero value, default: 1)");

अटल अचिन्हित पूर्णांक ccp_get_dma_chan_attr(काष्ठा ccp_device *ccp)
अणु
	चयन (dma_chan_attr) अणु
	हाल CCP_DMA_DFLT:
		वापस ccp->vdata->dma_chan_attr;

	हाल CCP_DMA_PRIV:
		वापस DMA_PRIVATE;

	हाल CCP_DMA_PUB:
		वापस 0;

	शेष:
		dev_info_once(ccp->dev, "Invalid value for dma_chan_attr: %d\n",
			      dma_chan_attr);
		वापस ccp->vdata->dma_chan_attr;
	पूर्ण
पूर्ण

अटल व्योम ccp_मुक्त_cmd_resources(काष्ठा ccp_device *ccp,
				   काष्ठा list_head *list)
अणु
	काष्ठा ccp_dma_cmd *cmd, *cपंचांगp;

	list_क्रम_each_entry_safe(cmd, cपंचांगp, list, entry) अणु
		list_del(&cmd->entry);
		kmem_cache_मुक्त(ccp->dma_cmd_cache, cmd);
	पूर्ण
पूर्ण

अटल व्योम ccp_मुक्त_desc_resources(काष्ठा ccp_device *ccp,
				    काष्ठा list_head *list)
अणु
	काष्ठा ccp_dma_desc *desc, *dपंचांगp;

	list_क्रम_each_entry_safe(desc, dपंचांगp, list, entry) अणु
		ccp_मुक्त_cmd_resources(ccp, &desc->active);
		ccp_मुक्त_cmd_resources(ccp, &desc->pending);

		list_del(&desc->entry);
		kmem_cache_मुक्त(ccp->dma_desc_cache, desc);
	पूर्ण
पूर्ण

अटल व्योम ccp_मुक्त_chan_resources(काष्ठा dma_chan *dma_chan)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	अचिन्हित दीर्घ flags;

	dev_dbg(chan->ccp->dev, "%s - chan=%p\n", __func__, chan);

	spin_lock_irqsave(&chan->lock, flags);

	ccp_मुक्त_desc_resources(chan->ccp, &chan->complete);
	ccp_मुक्त_desc_resources(chan->ccp, &chan->active);
	ccp_मुक्त_desc_resources(chan->ccp, &chan->pending);
	ccp_मुक्त_desc_resources(chan->ccp, &chan->created);

	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

अटल व्योम ccp_cleanup_desc_resources(काष्ठा ccp_device *ccp,
				       काष्ठा list_head *list)
अणु
	काष्ठा ccp_dma_desc *desc, *dपंचांगp;

	list_क्रम_each_entry_safe_reverse(desc, dपंचांगp, list, entry) अणु
		अगर (!async_tx_test_ack(&desc->tx_desc))
			जारी;

		dev_dbg(ccp->dev, "%s - desc=%p\n", __func__, desc);

		ccp_मुक्त_cmd_resources(ccp, &desc->active);
		ccp_मुक्त_cmd_resources(ccp, &desc->pending);

		list_del(&desc->entry);
		kmem_cache_मुक्त(ccp->dma_desc_cache, desc);
	पूर्ण
पूर्ण

अटल व्योम ccp_करो_cleanup(अचिन्हित दीर्घ data)
अणु
	काष्ठा ccp_dma_chan *chan = (काष्ठा ccp_dma_chan *)data;
	अचिन्हित दीर्घ flags;

	dev_dbg(chan->ccp->dev, "%s - chan=%s\n", __func__,
		dma_chan_name(&chan->dma_chan));

	spin_lock_irqsave(&chan->lock, flags);

	ccp_cleanup_desc_resources(chan->ccp, &chan->complete);

	spin_unlock_irqrestore(&chan->lock, flags);
पूर्ण

अटल पूर्णांक ccp_issue_next_cmd(काष्ठा ccp_dma_desc *desc)
अणु
	काष्ठा ccp_dma_cmd *cmd;
	पूर्णांक ret;

	cmd = list_first_entry(&desc->pending, काष्ठा ccp_dma_cmd, entry);
	list_move(&cmd->entry, &desc->active);

	dev_dbg(desc->ccp->dev, "%s - tx %d, cmd=%p\n", __func__,
		desc->tx_desc.cookie, cmd);

	ret = ccp_enqueue_cmd(&cmd->ccp_cmd);
	अगर (!ret || (ret == -EINPROGRESS) || (ret == -EBUSY))
		वापस 0;

	dev_dbg(desc->ccp->dev, "%s - error: ret=%d, tx %d, cmd=%p\n", __func__,
		ret, desc->tx_desc.cookie, cmd);

	वापस ret;
पूर्ण

अटल व्योम ccp_मुक्त_active_cmd(काष्ठा ccp_dma_desc *desc)
अणु
	काष्ठा ccp_dma_cmd *cmd;

	cmd = list_first_entry_or_null(&desc->active, काष्ठा ccp_dma_cmd,
				       entry);
	अगर (!cmd)
		वापस;

	dev_dbg(desc->ccp->dev, "%s - freeing tx %d cmd=%p\n",
		__func__, desc->tx_desc.cookie, cmd);

	list_del(&cmd->entry);
	kmem_cache_मुक्त(desc->ccp->dma_cmd_cache, cmd);
पूर्ण

अटल काष्ठा ccp_dma_desc *__ccp_next_dma_desc(काष्ठा ccp_dma_chan *chan,
						काष्ठा ccp_dma_desc *desc)
अणु
	/* Move current DMA descriptor to the complete list */
	अगर (desc)
		list_move(&desc->entry, &chan->complete);

	/* Get the next DMA descriptor on the active list */
	desc = list_first_entry_or_null(&chan->active, काष्ठा ccp_dma_desc,
					entry);

	वापस desc;
पूर्ण

अटल काष्ठा ccp_dma_desc *ccp_handle_active_desc(काष्ठा ccp_dma_chan *chan,
						   काष्ठा ccp_dma_desc *desc)
अणु
	काष्ठा dma_async_tx_descriptor *tx_desc;
	अचिन्हित दीर्घ flags;

	/* Loop over descriptors until one is found with commands */
	करो अणु
		अगर (desc) अणु
			/* Remove the DMA command from the list and मुक्त it */
			ccp_मुक्त_active_cmd(desc);

			अगर (!list_empty(&desc->pending)) अणु
				/* No errors, keep going */
				अगर (desc->status != DMA_ERROR)
					वापस desc;

				/* Error, मुक्त reमुख्यing commands and move on */
				ccp_मुक्त_cmd_resources(desc->ccp,
						       &desc->pending);
			पूर्ण

			tx_desc = &desc->tx_desc;
		पूर्ण अन्यथा अणु
			tx_desc = शून्य;
		पूर्ण

		spin_lock_irqsave(&chan->lock, flags);

		अगर (desc) अणु
			अगर (desc->status != DMA_ERROR)
				desc->status = DMA_COMPLETE;

			dev_dbg(desc->ccp->dev,
				"%s - tx %d complete, status=%u\n", __func__,
				desc->tx_desc.cookie, desc->status);

			dma_cookie_complete(tx_desc);
			dma_descriptor_unmap(tx_desc);
		पूर्ण

		desc = __ccp_next_dma_desc(chan, desc);

		spin_unlock_irqrestore(&chan->lock, flags);

		अगर (tx_desc) अणु
			dmaengine_desc_get_callback_invoke(tx_desc, शून्य);

			dma_run_dependencies(tx_desc);
		पूर्ण
	पूर्ण जबतक (desc);

	वापस शून्य;
पूर्ण

अटल काष्ठा ccp_dma_desc *__ccp_pending_to_active(काष्ठा ccp_dma_chan *chan)
अणु
	काष्ठा ccp_dma_desc *desc;

	अगर (list_empty(&chan->pending))
		वापस शून्य;

	desc = list_empty(&chan->active)
		? list_first_entry(&chan->pending, काष्ठा ccp_dma_desc, entry)
		: शून्य;

	list_splice_tail_init(&chan->pending, &chan->active);

	वापस desc;
पूर्ण

अटल व्योम ccp_cmd_callback(व्योम *data, पूर्णांक err)
अणु
	काष्ठा ccp_dma_desc *desc = data;
	काष्ठा ccp_dma_chan *chan;
	पूर्णांक ret;

	अगर (err == -EINPROGRESS)
		वापस;

	chan = container_of(desc->tx_desc.chan, काष्ठा ccp_dma_chan,
			    dma_chan);

	dev_dbg(chan->ccp->dev, "%s - tx %d callback, err=%d\n",
		__func__, desc->tx_desc.cookie, err);

	अगर (err)
		desc->status = DMA_ERROR;

	जबतक (true) अणु
		/* Check क्रम DMA descriptor completion */
		desc = ccp_handle_active_desc(chan, desc);

		/* Don't submit cmd अगर no descriptor or DMA is छोड़ोd */
		अगर (!desc || (chan->status == DMA_PAUSED))
			अवरोध;

		ret = ccp_issue_next_cmd(desc);
		अगर (!ret)
			अवरोध;

		desc->status = DMA_ERROR;
	पूर्ण

	tasklet_schedule(&chan->cleanup_tasklet);
पूर्ण

अटल dma_cookie_t ccp_tx_submit(काष्ठा dma_async_tx_descriptor *tx_desc)
अणु
	काष्ठा ccp_dma_desc *desc = container_of(tx_desc, काष्ठा ccp_dma_desc,
						 tx_desc);
	काष्ठा ccp_dma_chan *chan;
	dma_cookie_t cookie;
	अचिन्हित दीर्घ flags;

	chan = container_of(tx_desc->chan, काष्ठा ccp_dma_chan, dma_chan);

	spin_lock_irqsave(&chan->lock, flags);

	cookie = dma_cookie_assign(tx_desc);
	list_del(&desc->entry);
	list_add_tail(&desc->entry, &chan->pending);

	spin_unlock_irqrestore(&chan->lock, flags);

	dev_dbg(chan->ccp->dev, "%s - added tx descriptor %d to pending list\n",
		__func__, cookie);

	वापस cookie;
पूर्ण

अटल काष्ठा ccp_dma_cmd *ccp_alloc_dma_cmd(काष्ठा ccp_dma_chan *chan)
अणु
	काष्ठा ccp_dma_cmd *cmd;

	cmd = kmem_cache_alloc(chan->ccp->dma_cmd_cache, GFP_NOWAIT);
	अगर (cmd)
		स_रखो(cmd, 0, माप(*cmd));

	वापस cmd;
पूर्ण

अटल काष्ठा ccp_dma_desc *ccp_alloc_dma_desc(काष्ठा ccp_dma_chan *chan,
					       अचिन्हित दीर्घ flags)
अणु
	काष्ठा ccp_dma_desc *desc;

	desc = kmem_cache_zalloc(chan->ccp->dma_desc_cache, GFP_NOWAIT);
	अगर (!desc)
		वापस शून्य;

	dma_async_tx_descriptor_init(&desc->tx_desc, &chan->dma_chan);
	desc->tx_desc.flags = flags;
	desc->tx_desc.tx_submit = ccp_tx_submit;
	desc->ccp = chan->ccp;
	INIT_LIST_HEAD(&desc->entry);
	INIT_LIST_HEAD(&desc->pending);
	INIT_LIST_HEAD(&desc->active);
	desc->status = DMA_IN_PROGRESS;

	वापस desc;
पूर्ण

अटल काष्ठा ccp_dma_desc *ccp_create_desc(काष्ठा dma_chan *dma_chan,
					    काष्ठा scatterlist *dst_sg,
					    अचिन्हित पूर्णांक dst_nents,
					    काष्ठा scatterlist *src_sg,
					    अचिन्हित पूर्णांक src_nents,
					    अचिन्हित दीर्घ flags)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	काष्ठा ccp_device *ccp = chan->ccp;
	काष्ठा ccp_dma_desc *desc;
	काष्ठा ccp_dma_cmd *cmd;
	काष्ठा ccp_cmd *ccp_cmd;
	काष्ठा ccp_passthru_nomap_engine *ccp_pt;
	अचिन्हित पूर्णांक src_offset, src_len;
	अचिन्हित पूर्णांक dst_offset, dst_len;
	अचिन्हित पूर्णांक len;
	अचिन्हित दीर्घ sflags;
	माप_प्रकार total_len;

	अगर (!dst_sg || !src_sg)
		वापस शून्य;

	अगर (!dst_nents || !src_nents)
		वापस शून्य;

	desc = ccp_alloc_dma_desc(chan, flags);
	अगर (!desc)
		वापस शून्य;

	total_len = 0;

	src_len = sg_dma_len(src_sg);
	src_offset = 0;

	dst_len = sg_dma_len(dst_sg);
	dst_offset = 0;

	जबतक (true) अणु
		अगर (!src_len) अणु
			src_nents--;
			अगर (!src_nents)
				अवरोध;

			src_sg = sg_next(src_sg);
			अगर (!src_sg)
				अवरोध;

			src_len = sg_dma_len(src_sg);
			src_offset = 0;
			जारी;
		पूर्ण

		अगर (!dst_len) अणु
			dst_nents--;
			अगर (!dst_nents)
				अवरोध;

			dst_sg = sg_next(dst_sg);
			अगर (!dst_sg)
				अवरोध;

			dst_len = sg_dma_len(dst_sg);
			dst_offset = 0;
			जारी;
		पूर्ण

		len = min(dst_len, src_len);

		cmd = ccp_alloc_dma_cmd(chan);
		अगर (!cmd)
			जाओ err;

		ccp_cmd = &cmd->ccp_cmd;
		ccp_cmd->ccp = chan->ccp;
		ccp_pt = &ccp_cmd->u.passthru_nomap;
		ccp_cmd->flags = CCP_CMD_MAY_BACKLOG;
		ccp_cmd->flags |= CCP_CMD_PASSTHRU_NO_DMA_MAP;
		ccp_cmd->engine = CCP_ENGINE_PASSTHRU;
		ccp_pt->bit_mod = CCP_PASSTHRU_BITWISE_NOOP;
		ccp_pt->byte_swap = CCP_PASSTHRU_BYTESWAP_NOOP;
		ccp_pt->src_dma = sg_dma_address(src_sg) + src_offset;
		ccp_pt->dst_dma = sg_dma_address(dst_sg) + dst_offset;
		ccp_pt->src_len = len;
		ccp_pt->final = 1;
		ccp_cmd->callback = ccp_cmd_callback;
		ccp_cmd->data = desc;

		list_add_tail(&cmd->entry, &desc->pending);

		dev_dbg(ccp->dev,
			"%s - cmd=%p, src=%pad, dst=%pad, len=%llu\n", __func__,
			cmd, &ccp_pt->src_dma,
			&ccp_pt->dst_dma, ccp_pt->src_len);

		total_len += len;

		src_len -= len;
		src_offset += len;

		dst_len -= len;
		dst_offset += len;
	पूर्ण

	desc->len = total_len;

	अगर (list_empty(&desc->pending))
		जाओ err;

	dev_dbg(ccp->dev, "%s - desc=%p\n", __func__, desc);

	spin_lock_irqsave(&chan->lock, sflags);

	list_add_tail(&desc->entry, &chan->created);

	spin_unlock_irqrestore(&chan->lock, sflags);

	वापस desc;

err:
	ccp_मुक्त_cmd_resources(ccp, &desc->pending);
	kmem_cache_मुक्त(ccp->dma_desc_cache, desc);

	वापस शून्य;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *ccp_prep_dma_स_नकल(
	काष्ठा dma_chan *dma_chan, dma_addr_t dst, dma_addr_t src, माप_प्रकार len,
	अचिन्हित दीर्घ flags)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	काष्ठा ccp_dma_desc *desc;
	काष्ठा scatterlist dst_sg, src_sg;

	dev_dbg(chan->ccp->dev,
		"%s - src=%pad, dst=%pad, len=%zu, flags=%#lx\n",
		__func__, &src, &dst, len, flags);

	sg_init_table(&dst_sg, 1);
	sg_dma_address(&dst_sg) = dst;
	sg_dma_len(&dst_sg) = len;

	sg_init_table(&src_sg, 1);
	sg_dma_address(&src_sg) = src;
	sg_dma_len(&src_sg) = len;

	desc = ccp_create_desc(dma_chan, &dst_sg, 1, &src_sg, 1, flags);
	अगर (!desc)
		वापस शून्य;

	वापस &desc->tx_desc;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *ccp_prep_dma_पूर्णांकerrupt(
	काष्ठा dma_chan *dma_chan, अचिन्हित दीर्घ flags)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	काष्ठा ccp_dma_desc *desc;

	desc = ccp_alloc_dma_desc(chan, flags);
	अगर (!desc)
		वापस शून्य;

	वापस &desc->tx_desc;
पूर्ण

अटल व्योम ccp_issue_pending(काष्ठा dma_chan *dma_chan)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	काष्ठा ccp_dma_desc *desc;
	अचिन्हित दीर्घ flags;

	dev_dbg(chan->ccp->dev, "%s\n", __func__);

	spin_lock_irqsave(&chan->lock, flags);

	desc = __ccp_pending_to_active(chan);

	spin_unlock_irqrestore(&chan->lock, flags);

	/* If there was nothing active, start processing */
	अगर (desc)
		ccp_cmd_callback(desc, 0);
पूर्ण

अटल क्रमागत dma_status ccp_tx_status(काष्ठा dma_chan *dma_chan,
				     dma_cookie_t cookie,
				     काष्ठा dma_tx_state *state)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	काष्ठा ccp_dma_desc *desc;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	अगर (chan->status == DMA_PAUSED) अणु
		ret = DMA_PAUSED;
		जाओ out;
	पूर्ण

	ret = dma_cookie_status(dma_chan, cookie, state);
	अगर (ret == DMA_COMPLETE) अणु
		spin_lock_irqsave(&chan->lock, flags);

		/* Get status from complete chain, अगर still there */
		list_क्रम_each_entry(desc, &chan->complete, entry) अणु
			अगर (desc->tx_desc.cookie != cookie)
				जारी;

			ret = desc->status;
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&chan->lock, flags);
	पूर्ण

out:
	dev_dbg(chan->ccp->dev, "%s - %u\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक ccp_छोड़ो(काष्ठा dma_chan *dma_chan)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);

	chan->status = DMA_PAUSED;

	/*TODO: Wait क्रम active DMA to complete beक्रमe वापसing? */

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_resume(काष्ठा dma_chan *dma_chan)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	काष्ठा ccp_dma_desc *desc;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&chan->lock, flags);

	desc = list_first_entry_or_null(&chan->active, काष्ठा ccp_dma_desc,
					entry);

	spin_unlock_irqrestore(&chan->lock, flags);

	/* Indicate the channel is running again */
	chan->status = DMA_IN_PROGRESS;

	/* If there was something active, re-start */
	अगर (desc)
		ccp_cmd_callback(desc, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक ccp_terminate_all(काष्ठा dma_chan *dma_chan)
अणु
	काष्ठा ccp_dma_chan *chan = container_of(dma_chan, काष्ठा ccp_dma_chan,
						 dma_chan);
	अचिन्हित दीर्घ flags;

	dev_dbg(chan->ccp->dev, "%s\n", __func__);

	/*TODO: Wait क्रम active DMA to complete beक्रमe continuing */

	spin_lock_irqsave(&chan->lock, flags);

	/*TODO: Purge the complete list? */
	ccp_मुक्त_desc_resources(chan->ccp, &chan->active);
	ccp_मुक्त_desc_resources(chan->ccp, &chan->pending);
	ccp_मुक्त_desc_resources(chan->ccp, &chan->created);

	spin_unlock_irqrestore(&chan->lock, flags);

	वापस 0;
पूर्ण

पूर्णांक ccp_dmaengine_रेजिस्टर(काष्ठा ccp_device *ccp)
अणु
	काष्ठा ccp_dma_chan *chan;
	काष्ठा dma_device *dma_dev = &ccp->dma_dev;
	काष्ठा dma_chan *dma_chan;
	अक्षर *dma_cmd_cache_name;
	अक्षर *dma_desc_cache_name;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!dmaengine)
		वापस 0;

	ccp->ccp_dma_chan = devm_kसुस्मृति(ccp->dev, ccp->cmd_q_count,
					 माप(*(ccp->ccp_dma_chan)),
					 GFP_KERNEL);
	अगर (!ccp->ccp_dma_chan)
		वापस -ENOMEM;

	dma_cmd_cache_name = devm_kaप्र_लिखो(ccp->dev, GFP_KERNEL,
					    "%s-dmaengine-cmd-cache",
					    ccp->name);
	अगर (!dma_cmd_cache_name)
		वापस -ENOMEM;

	ccp->dma_cmd_cache = kmem_cache_create(dma_cmd_cache_name,
					       माप(काष्ठा ccp_dma_cmd),
					       माप(व्योम *),
					       SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ccp->dma_cmd_cache)
		वापस -ENOMEM;

	dma_desc_cache_name = devm_kaप्र_लिखो(ccp->dev, GFP_KERNEL,
					     "%s-dmaengine-desc-cache",
					     ccp->name);
	अगर (!dma_desc_cache_name) अणु
		ret = -ENOMEM;
		जाओ err_cache;
	पूर्ण

	ccp->dma_desc_cache = kmem_cache_create(dma_desc_cache_name,
						माप(काष्ठा ccp_dma_desc),
						माप(व्योम *),
						SLAB_HWCACHE_ALIGN, शून्य);
	अगर (!ccp->dma_desc_cache) अणु
		ret = -ENOMEM;
		जाओ err_cache;
	पूर्ण

	dma_dev->dev = ccp->dev;
	dma_dev->src_addr_widths = CCP_DMA_WIDTH(dma_get_mask(ccp->dev));
	dma_dev->dst_addr_widths = CCP_DMA_WIDTH(dma_get_mask(ccp->dev));
	dma_dev->directions = DMA_MEM_TO_MEM;
	dma_dev->residue_granularity = DMA_RESIDUE_GRANULARITY_DESCRIPTOR;
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_INTERRUPT, dma_dev->cap_mask);

	/* The DMA channels क्रम this device can be set to खुला or निजी,
	 * and overridden by the module parameter dma_chan_attr.
	 * Default: according to the value in vdata (dma_chan_attr=0)
	 * dma_chan_attr=0x1: all channels निजी (override vdata)
	 * dma_chan_attr=0x2: all channels खुला (override vdata)
	 */
	अगर (ccp_get_dma_chan_attr(ccp) == DMA_PRIVATE)
		dma_cap_set(DMA_PRIVATE, dma_dev->cap_mask);

	INIT_LIST_HEAD(&dma_dev->channels);
	क्रम (i = 0; i < ccp->cmd_q_count; i++) अणु
		chan = ccp->ccp_dma_chan + i;
		dma_chan = &chan->dma_chan;

		chan->ccp = ccp;

		spin_lock_init(&chan->lock);
		INIT_LIST_HEAD(&chan->created);
		INIT_LIST_HEAD(&chan->pending);
		INIT_LIST_HEAD(&chan->active);
		INIT_LIST_HEAD(&chan->complete);

		tasklet_init(&chan->cleanup_tasklet, ccp_करो_cleanup,
			     (अचिन्हित दीर्घ)chan);

		dma_chan->device = dma_dev;
		dma_cookie_init(dma_chan);

		list_add_tail(&dma_chan->device_node, &dma_dev->channels);
	पूर्ण

	dma_dev->device_मुक्त_chan_resources = ccp_मुक्त_chan_resources;
	dma_dev->device_prep_dma_स_नकल = ccp_prep_dma_स_नकल;
	dma_dev->device_prep_dma_पूर्णांकerrupt = ccp_prep_dma_पूर्णांकerrupt;
	dma_dev->device_issue_pending = ccp_issue_pending;
	dma_dev->device_tx_status = ccp_tx_status;
	dma_dev->device_छोड़ो = ccp_छोड़ो;
	dma_dev->device_resume = ccp_resume;
	dma_dev->device_terminate_all = ccp_terminate_all;

	ret = dma_async_device_रेजिस्टर(dma_dev);
	अगर (ret)
		जाओ err_reg;

	वापस 0;

err_reg:
	kmem_cache_destroy(ccp->dma_desc_cache);

err_cache:
	kmem_cache_destroy(ccp->dma_cmd_cache);

	वापस ret;
पूर्ण

व्योम ccp_dmaengine_unरेजिस्टर(काष्ठा ccp_device *ccp)
अणु
	काष्ठा dma_device *dma_dev = &ccp->dma_dev;

	अगर (!dmaengine)
		वापस;

	dma_async_device_unरेजिस्टर(dma_dev);

	kmem_cache_destroy(ccp->dma_desc_cache);
	kmem_cache_destroy(ccp->dma_cmd_cache);
पूर्ण
