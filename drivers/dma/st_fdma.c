<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * DMA driver क्रम STMicroelectronics STi FDMA controller
 *
 * Copyright (C) 2014 STMicroelectronics
 *
 * Author: Luकरोvic Barre <Luकरोvic.barre@st.com>
 *	   Peter Grअगरfin <peter.grअगरfin@linaro.org>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_dma.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/slab.h>

#समावेश "st_fdma.h"

अटल अंतरभूत काष्ठा st_fdma_chan *to_st_fdma_chan(काष्ठा dma_chan *c)
अणु
	वापस container_of(c, काष्ठा st_fdma_chan, vchan.chan);
पूर्ण

अटल काष्ठा st_fdma_desc *to_st_fdma_desc(काष्ठा virt_dma_desc *vd)
अणु
	वापस container_of(vd, काष्ठा st_fdma_desc, vdesc);
पूर्ण

अटल पूर्णांक st_fdma_dreq_get(काष्ठा st_fdma_chan *fchan)
अणु
	काष्ठा st_fdma_dev *fdev = fchan->fdev;
	u32 req_line_cfg = fchan->cfg.req_line;
	u32 dreq_line;
	पूर्णांक try = 0;

	/*
	 * dreq_mask is shared क्रम n channels of fdma, so all accesses must be
	 * atomic. अगर the dreq_mask is changed between ffz and set_bit,
	 * we retry
	 */
	करो अणु
		अगर (fdev->dreq_mask == ~0L) अणु
			dev_err(fdev->dev, "No req lines available\n");
			वापस -EINVAL;
		पूर्ण

		अगर (try || req_line_cfg >= ST_FDMA_NR_DREQS) अणु
			dev_err(fdev->dev, "Invalid or used req line\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अणु
			dreq_line = req_line_cfg;
		पूर्ण

		try++;
	पूर्ण जबतक (test_and_set_bit(dreq_line, &fdev->dreq_mask));

	dev_dbg(fdev->dev, "get dreq_line:%d mask:%#lx\n",
		dreq_line, fdev->dreq_mask);

	वापस dreq_line;
पूर्ण

अटल व्योम st_fdma_dreq_put(काष्ठा st_fdma_chan *fchan)
अणु
	काष्ठा st_fdma_dev *fdev = fchan->fdev;

	dev_dbg(fdev->dev, "put dreq_line:%#x\n", fchan->dreq_line);
	clear_bit(fchan->dreq_line, &fdev->dreq_mask);
पूर्ण

अटल व्योम st_fdma_xfer_desc(काष्ठा st_fdma_chan *fchan)
अणु
	काष्ठा virt_dma_desc *vdesc;
	अचिन्हित दीर्घ nbytes, ch_cmd, cmd;

	vdesc = vchan_next_desc(&fchan->vchan);
	अगर (!vdesc)
		वापस;

	fchan->fdesc = to_st_fdma_desc(vdesc);
	nbytes = fchan->fdesc->node[0].desc->nbytes;
	cmd = FDMA_CMD_START(fchan->vchan.chan.chan_id);
	ch_cmd = fchan->fdesc->node[0].pdesc | FDMA_CH_CMD_STA_START;

	/* start the channel क्रम the descriptor */
	fnode_ग_लिखो(fchan, nbytes, FDMA_CNTN_OFST);
	fchan_ग_लिखो(fchan, ch_cmd, FDMA_CH_CMD_OFST);
	ग_लिखोl(cmd,
		fchan->fdev->slim_rproc->peri + FDMA_CMD_SET_OFST);

	dev_dbg(fchan->fdev->dev, "start chan:%d\n", fchan->vchan.chan.chan_id);
पूर्ण

अटल व्योम st_fdma_ch_sta_update(काष्ठा st_fdma_chan *fchan,
				  अचिन्हित दीर्घ पूर्णांक_sta)
अणु
	अचिन्हित दीर्घ ch_sta, ch_err;
	पूर्णांक ch_id = fchan->vchan.chan.chan_id;
	काष्ठा st_fdma_dev *fdev = fchan->fdev;

	ch_sta = fchan_पढ़ो(fchan, FDMA_CH_CMD_OFST);
	ch_err = ch_sta & FDMA_CH_CMD_ERR_MASK;
	ch_sta &= FDMA_CH_CMD_STA_MASK;

	अगर (पूर्णांक_sta & FDMA_INT_STA_ERR) अणु
		dev_warn(fdev->dev, "chan:%d, error:%ld\n", ch_id, ch_err);
		fchan->status = DMA_ERROR;
		वापस;
	पूर्ण

	चयन (ch_sta) अणु
	हाल FDMA_CH_CMD_STA_PAUSED:
		fchan->status = DMA_PAUSED;
		अवरोध;

	हाल FDMA_CH_CMD_STA_RUNNING:
		fchan->status = DMA_IN_PROGRESS;
		अवरोध;
	पूर्ण
पूर्ण

अटल irqवापस_t st_fdma_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा st_fdma_dev *fdev = dev_id;
	irqवापस_t ret = IRQ_NONE;
	काष्ठा st_fdma_chan *fchan = &fdev->chans[0];
	अचिन्हित दीर्घ पूर्णांक_sta, clr;

	पूर्णांक_sta = fdma_पढ़ो(fdev, FDMA_INT_STA_OFST);
	clr = पूर्णांक_sta;

	क्रम (; पूर्णांक_sta != 0 ; पूर्णांक_sta >>= 2, fchan++) अणु
		अगर (!(पूर्णांक_sta & (FDMA_INT_STA_CH | FDMA_INT_STA_ERR)))
			जारी;

		spin_lock(&fchan->vchan.lock);
		st_fdma_ch_sta_update(fchan, पूर्णांक_sta);

		अगर (fchan->fdesc) अणु
			अगर (!fchan->fdesc->iscyclic) अणु
				list_del(&fchan->fdesc->vdesc.node);
				vchan_cookie_complete(&fchan->fdesc->vdesc);
				fchan->fdesc = शून्य;
				fchan->status = DMA_COMPLETE;
			पूर्ण अन्यथा अणु
				vchan_cyclic_callback(&fchan->fdesc->vdesc);
			पूर्ण

			/* Start the next descriptor (अगर available) */
			अगर (!fchan->fdesc)
				st_fdma_xfer_desc(fchan);
		पूर्ण

		spin_unlock(&fchan->vchan.lock);
		ret = IRQ_HANDLED;
	पूर्ण

	fdma_ग_लिखो(fdev, clr, FDMA_INT_CLR_OFST);

	वापस ret;
पूर्ण

अटल काष्ठा dma_chan *st_fdma_of_xlate(काष्ठा of_phandle_args *dma_spec,
					 काष्ठा of_dma *ofdma)
अणु
	काष्ठा st_fdma_dev *fdev = ofdma->of_dma_data;
	काष्ठा dma_chan *chan;
	काष्ठा st_fdma_chan *fchan;
	पूर्णांक ret;

	अगर (dma_spec->args_count < 1)
		वापस ERR_PTR(-EINVAL);

	अगर (fdev->dma_device.dev->of_node != dma_spec->np)
		वापस ERR_PTR(-EINVAL);

	ret = rproc_boot(fdev->slim_rproc->rproc);
	अगर (ret == -ENOENT)
		वापस ERR_PTR(-EPROBE_DEFER);
	अन्यथा अगर (ret)
		वापस ERR_PTR(ret);

	chan = dma_get_any_slave_channel(&fdev->dma_device);
	अगर (!chan)
		जाओ err_chan;

	fchan = to_st_fdma_chan(chan);

	fchan->cfg.of_node = dma_spec->np;
	fchan->cfg.req_line = dma_spec->args[0];
	fchan->cfg.req_ctrl = 0;
	fchan->cfg.type = ST_FDMA_TYPE_FREE_RUN;

	अगर (dma_spec->args_count > 1)
		fchan->cfg.req_ctrl = dma_spec->args[1]
			& FDMA_REQ_CTRL_CFG_MASK;

	अगर (dma_spec->args_count > 2)
		fchan->cfg.type = dma_spec->args[2];

	अगर (fchan->cfg.type == ST_FDMA_TYPE_FREE_RUN) अणु
		fchan->dreq_line = 0;
	पूर्ण अन्यथा अणु
		fchan->dreq_line = st_fdma_dreq_get(fchan);
		अगर (IS_ERR_VALUE(fchan->dreq_line)) अणु
			chan = ERR_PTR(fchan->dreq_line);
			जाओ err_chan;
		पूर्ण
	पूर्ण

	dev_dbg(fdev->dev, "xlate req_line:%d type:%d req_ctrl:%#lx\n",
		fchan->cfg.req_line, fchan->cfg.type, fchan->cfg.req_ctrl);

	वापस chan;

err_chan:
	rproc_shutकरोwn(fdev->slim_rproc->rproc);
	वापस chan;

पूर्ण

अटल व्योम st_fdma_मुक्त_desc(काष्ठा virt_dma_desc *vdesc)
अणु
	काष्ठा st_fdma_desc *fdesc;
	पूर्णांक i;

	fdesc = to_st_fdma_desc(vdesc);
	क्रम (i = 0; i < fdesc->n_nodes; i++)
		dma_pool_मुक्त(fdesc->fchan->node_pool, fdesc->node[i].desc,
			      fdesc->node[i].pdesc);
	kमुक्त(fdesc);
पूर्ण

अटल काष्ठा st_fdma_desc *st_fdma_alloc_desc(काष्ठा st_fdma_chan *fchan,
					       पूर्णांक sg_len)
अणु
	काष्ठा st_fdma_desc *fdesc;
	पूर्णांक i;

	fdesc = kzalloc(काष्ठा_size(fdesc, node, sg_len), GFP_NOWAIT);
	अगर (!fdesc)
		वापस शून्य;

	fdesc->fchan = fchan;
	fdesc->n_nodes = sg_len;
	क्रम (i = 0; i < sg_len; i++) अणु
		fdesc->node[i].desc = dma_pool_alloc(fchan->node_pool,
				GFP_NOWAIT, &fdesc->node[i].pdesc);
		अगर (!fdesc->node[i].desc)
			जाओ err;
	पूर्ण
	वापस fdesc;

err:
	जबतक (--i >= 0)
		dma_pool_मुक्त(fchan->node_pool, fdesc->node[i].desc,
			      fdesc->node[i].pdesc);
	kमुक्त(fdesc);
	वापस शून्य;
पूर्ण

अटल पूर्णांक st_fdma_alloc_chan_res(काष्ठा dma_chan *chan)
अणु
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);

	/* Create the dma pool क्रम descriptor allocation */
	fchan->node_pool = dma_pool_create(dev_name(&chan->dev->device),
					    fchan->fdev->dev,
					    माप(काष्ठा st_fdma_hw_node),
					    __alignof__(काष्ठा st_fdma_hw_node),
					    0);

	अगर (!fchan->node_pool) अणु
		dev_err(fchan->fdev->dev, "unable to allocate desc pool\n");
		वापस -ENOMEM;
	पूर्ण

	dev_dbg(fchan->fdev->dev, "alloc ch_id:%d type:%d\n",
		fchan->vchan.chan.chan_id, fchan->cfg.type);

	वापस 0;
पूर्ण

अटल व्योम st_fdma_मुक्त_chan_res(काष्ठा dma_chan *chan)
अणु
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);
	काष्ठा rproc *rproc = fchan->fdev->slim_rproc->rproc;
	अचिन्हित दीर्घ flags;

	dev_dbg(fchan->fdev->dev, "%s: freeing chan:%d\n",
		__func__, fchan->vchan.chan.chan_id);

	अगर (fchan->cfg.type != ST_FDMA_TYPE_FREE_RUN)
		st_fdma_dreq_put(fchan);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	fchan->fdesc = शून्य;
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	dma_pool_destroy(fchan->node_pool);
	fchan->node_pool = शून्य;
	स_रखो(&fchan->cfg, 0, माप(काष्ठा st_fdma_cfg));

	rproc_shutकरोwn(rproc);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *st_fdma_prep_dma_स_नकल(
	काष्ठा dma_chan *chan,	dma_addr_t dst, dma_addr_t src,
	माप_प्रकार len, अचिन्हित दीर्घ flags)
अणु
	काष्ठा st_fdma_chan *fchan;
	काष्ठा st_fdma_desc *fdesc;
	काष्ठा st_fdma_hw_node *hw_node;

	अगर (!len)
		वापस शून्य;

	fchan = to_st_fdma_chan(chan);

	/* We only require a single descriptor */
	fdesc = st_fdma_alloc_desc(fchan, 1);
	अगर (!fdesc) अणु
		dev_err(fchan->fdev->dev, "no memory for desc\n");
		वापस शून्य;
	पूर्ण

	hw_node = fdesc->node[0].desc;
	hw_node->next = 0;
	hw_node->control = FDMA_NODE_CTRL_REQ_MAP_FREE_RUN;
	hw_node->control |= FDMA_NODE_CTRL_SRC_INCR;
	hw_node->control |= FDMA_NODE_CTRL_DST_INCR;
	hw_node->control |= FDMA_NODE_CTRL_INT_EON;
	hw_node->nbytes = len;
	hw_node->saddr = src;
	hw_node->daddr = dst;
	hw_node->generic.length = len;
	hw_node->generic.sstride = 0;
	hw_node->generic.dstride = 0;

	वापस vchan_tx_prep(&fchan->vchan, &fdesc->vdesc, flags);
पूर्ण

अटल पूर्णांक config_reqctrl(काष्ठा st_fdma_chan *fchan,
			  क्रमागत dma_transfer_direction direction)
अणु
	u32 maxburst = 0, addr = 0;
	क्रमागत dma_slave_buswidth width;
	पूर्णांक ch_id = fchan->vchan.chan.chan_id;
	काष्ठा st_fdma_dev *fdev = fchan->fdev;

	चयन (direction) अणु

	हाल DMA_DEV_TO_MEM:
		fchan->cfg.req_ctrl &= ~FDMA_REQ_CTRL_WNR;
		maxburst = fchan->scfg.src_maxburst;
		width = fchan->scfg.src_addr_width;
		addr = fchan->scfg.src_addr;
		अवरोध;

	हाल DMA_MEM_TO_DEV:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_WNR;
		maxburst = fchan->scfg.dst_maxburst;
		width = fchan->scfg.dst_addr_width;
		addr = fchan->scfg.dst_addr;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	fchan->cfg.req_ctrl &= ~FDMA_REQ_CTRL_OPCODE_MASK;

	चयन (width) अणु

	हाल DMA_SLAVE_BUSWIDTH_1_BYTE:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST1;
		अवरोध;

	हाल DMA_SLAVE_BUSWIDTH_2_BYTES:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST2;
		अवरोध;

	हाल DMA_SLAVE_BUSWIDTH_4_BYTES:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST4;
		अवरोध;

	हाल DMA_SLAVE_BUSWIDTH_8_BYTES:
		fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_OPCODE_LD_ST8;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	fchan->cfg.req_ctrl &= ~FDMA_REQ_CTRL_NUM_OPS_MASK;
	fchan->cfg.req_ctrl |= FDMA_REQ_CTRL_NUM_OPS(maxburst-1);
	dreq_ग_लिखो(fchan, fchan->cfg.req_ctrl, FDMA_REQ_CTRL_OFST);

	fchan->cfg.dev_addr = addr;
	fchan->cfg.dir = direction;

	dev_dbg(fdev->dev, "chan:%d config_reqctrl:%#x req_ctrl:%#lx\n",
		ch_id, addr, fchan->cfg.req_ctrl);

	वापस 0;
पूर्ण

अटल व्योम fill_hw_node(काष्ठा st_fdma_hw_node *hw_node,
			काष्ठा st_fdma_chan *fchan,
			क्रमागत dma_transfer_direction direction)
अणु
	अगर (direction == DMA_MEM_TO_DEV) अणु
		hw_node->control |= FDMA_NODE_CTRL_SRC_INCR;
		hw_node->control |= FDMA_NODE_CTRL_DST_STATIC;
		hw_node->daddr = fchan->cfg.dev_addr;
	पूर्ण अन्यथा अणु
		hw_node->control |= FDMA_NODE_CTRL_SRC_STATIC;
		hw_node->control |= FDMA_NODE_CTRL_DST_INCR;
		hw_node->saddr = fchan->cfg.dev_addr;
	पूर्ण

	hw_node->generic.sstride = 0;
	hw_node->generic.dstride = 0;
पूर्ण

अटल अंतरभूत काष्ठा st_fdma_chan *st_fdma_prep_common(काष्ठा dma_chan *chan,
		माप_प्रकार len, क्रमागत dma_transfer_direction direction)
अणु
	काष्ठा st_fdma_chan *fchan;

	अगर (!chan || !len)
		वापस शून्य;

	fchan = to_st_fdma_chan(chan);

	अगर (!is_slave_direction(direction)) अणु
		dev_err(fchan->fdev->dev, "bad direction?\n");
		वापस शून्य;
	पूर्ण

	वापस fchan;
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *st_fdma_prep_dma_cyclic(
		काष्ठा dma_chan *chan, dma_addr_t buf_addr, माप_प्रकार len,
		माप_प्रकार period_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags)
अणु
	काष्ठा st_fdma_chan *fchan;
	काष्ठा st_fdma_desc *fdesc;
	पूर्णांक sg_len, i;

	fchan = st_fdma_prep_common(chan, len, direction);
	अगर (!fchan)
		वापस शून्य;

	अगर (!period_len)
		वापस शून्य;

	अगर (config_reqctrl(fchan, direction)) अणु
		dev_err(fchan->fdev->dev, "bad width or direction\n");
		वापस शून्य;
	पूर्ण

	/* the buffer length must be a multiple of period_len */
	अगर (len % period_len != 0) अणु
		dev_err(fchan->fdev->dev, "len is not multiple of period\n");
		वापस शून्य;
	पूर्ण

	sg_len = len / period_len;
	fdesc = st_fdma_alloc_desc(fchan, sg_len);
	अगर (!fdesc) अणु
		dev_err(fchan->fdev->dev, "no memory for desc\n");
		वापस शून्य;
	पूर्ण

	fdesc->iscyclic = true;

	क्रम (i = 0; i < sg_len; i++) अणु
		काष्ठा st_fdma_hw_node *hw_node = fdesc->node[i].desc;

		hw_node->next = fdesc->node[(i + 1) % sg_len].pdesc;

		hw_node->control =
			FDMA_NODE_CTRL_REQ_MAP_DREQ(fchan->dreq_line);
		hw_node->control |= FDMA_NODE_CTRL_INT_EON;

		fill_hw_node(hw_node, fchan, direction);

		अगर (direction == DMA_MEM_TO_DEV)
			hw_node->saddr = buf_addr + (i * period_len);
		अन्यथा
			hw_node->daddr = buf_addr + (i * period_len);

		hw_node->nbytes = period_len;
		hw_node->generic.length = period_len;
	पूर्ण

	वापस vchan_tx_prep(&fchan->vchan, &fdesc->vdesc, flags);
पूर्ण

अटल काष्ठा dma_async_tx_descriptor *st_fdma_prep_slave_sg(
		काष्ठा dma_chan *chan, काष्ठा scatterlist *sgl,
		अचिन्हित पूर्णांक sg_len, क्रमागत dma_transfer_direction direction,
		अचिन्हित दीर्घ flags, व्योम *context)
अणु
	काष्ठा st_fdma_chan *fchan;
	काष्ठा st_fdma_desc *fdesc;
	काष्ठा st_fdma_hw_node *hw_node;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	fchan = st_fdma_prep_common(chan, sg_len, direction);
	अगर (!fchan)
		वापस शून्य;

	अगर (!sgl)
		वापस शून्य;

	fdesc = st_fdma_alloc_desc(fchan, sg_len);
	अगर (!fdesc) अणु
		dev_err(fchan->fdev->dev, "no memory for desc\n");
		वापस शून्य;
	पूर्ण

	fdesc->iscyclic = false;

	क्रम_each_sg(sgl, sg, sg_len, i) अणु
		hw_node = fdesc->node[i].desc;

		hw_node->next = fdesc->node[(i + 1) % sg_len].pdesc;
		hw_node->control = FDMA_NODE_CTRL_REQ_MAP_DREQ(fchan->dreq_line);

		fill_hw_node(hw_node, fchan, direction);

		अगर (direction == DMA_MEM_TO_DEV)
			hw_node->saddr = sg_dma_address(sg);
		अन्यथा
			hw_node->daddr = sg_dma_address(sg);

		hw_node->nbytes = sg_dma_len(sg);
		hw_node->generic.length = sg_dma_len(sg);
	पूर्ण

	/* पूर्णांकerrupt at end of last node */
	hw_node->control |= FDMA_NODE_CTRL_INT_EON;

	वापस vchan_tx_prep(&fchan->vchan, &fdesc->vdesc, flags);
पूर्ण

अटल माप_प्रकार st_fdma_desc_residue(काष्ठा st_fdma_chan *fchan,
				   काष्ठा virt_dma_desc *vdesc,
				   bool in_progress)
अणु
	काष्ठा st_fdma_desc *fdesc = fchan->fdesc;
	माप_प्रकार residue = 0;
	dma_addr_t cur_addr = 0;
	पूर्णांक i;

	अगर (in_progress) अणु
		cur_addr = fchan_पढ़ो(fchan, FDMA_CH_CMD_OFST);
		cur_addr &= FDMA_CH_CMD_DATA_MASK;
	पूर्ण

	क्रम (i = fchan->fdesc->n_nodes - 1 ; i >= 0; i--) अणु
		अगर (cur_addr == fdesc->node[i].pdesc) अणु
			residue += fnode_पढ़ो(fchan, FDMA_CNTN_OFST);
			अवरोध;
		पूर्ण
		residue += fdesc->node[i].desc->nbytes;
	पूर्ण

	वापस residue;
पूर्ण

अटल क्रमागत dma_status st_fdma_tx_status(काष्ठा dma_chan *chan,
					 dma_cookie_t cookie,
					 काष्ठा dma_tx_state *txstate)
अणु
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);
	काष्ठा virt_dma_desc *vd;
	क्रमागत dma_status ret;
	अचिन्हित दीर्घ flags;

	ret = dma_cookie_status(chan, cookie, txstate);
	अगर (ret == DMA_COMPLETE || !txstate)
		वापस ret;

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	vd = vchan_find_desc(&fchan->vchan, cookie);
	अगर (fchan->fdesc && cookie == fchan->fdesc->vdesc.tx.cookie)
		txstate->residue = st_fdma_desc_residue(fchan, vd, true);
	अन्यथा अगर (vd)
		txstate->residue = st_fdma_desc_residue(fchan, vd, false);
	अन्यथा
		txstate->residue = 0;

	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	वापस ret;
पूर्ण

अटल व्योम st_fdma_issue_pending(काष्ठा dma_chan *chan)
अणु
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fchan->vchan.lock, flags);

	अगर (vchan_issue_pending(&fchan->vchan) && !fchan->fdesc)
		st_fdma_xfer_desc(fchan);

	spin_unlock_irqrestore(&fchan->vchan.lock, flags);
पूर्ण

अटल पूर्णांक st_fdma_छोड़ो(काष्ठा dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);
	पूर्णांक ch_id = fchan->vchan.chan.chan_id;
	अचिन्हित दीर्घ cmd = FDMA_CMD_PAUSE(ch_id);

	dev_dbg(fchan->fdev->dev, "pause chan:%d\n", ch_id);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	अगर (fchan->fdesc)
		fdma_ग_लिखो(fchan->fdev, cmd, FDMA_CMD_SET_OFST);
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक st_fdma_resume(काष्ठा dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ val;
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);
	पूर्णांक ch_id = fchan->vchan.chan.chan_id;

	dev_dbg(fchan->fdev->dev, "resume chan:%d\n", ch_id);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	अगर (fchan->fdesc) अणु
		val = fchan_पढ़ो(fchan, FDMA_CH_CMD_OFST);
		val &= FDMA_CH_CMD_DATA_MASK;
		fchan_ग_लिखो(fchan, val, FDMA_CH_CMD_OFST);
	पूर्ण
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक st_fdma_terminate_all(काष्ठा dma_chan *chan)
अणु
	अचिन्हित दीर्घ flags;
	LIST_HEAD(head);
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);
	पूर्णांक ch_id = fchan->vchan.chan.chan_id;
	अचिन्हित दीर्घ cmd = FDMA_CMD_PAUSE(ch_id);

	dev_dbg(fchan->fdev->dev, "terminate chan:%d\n", ch_id);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	fdma_ग_लिखो(fchan->fdev, cmd, FDMA_CMD_SET_OFST);
	fchan->fdesc = शून्य;
	vchan_get_all_descriptors(&fchan->vchan, &head);
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);
	vchan_dma_desc_मुक्त_list(&fchan->vchan, &head);

	वापस 0;
पूर्ण

अटल पूर्णांक st_fdma_slave_config(काष्ठा dma_chan *chan,
				काष्ठा dma_slave_config *slave_cfg)
अणु
	काष्ठा st_fdma_chan *fchan = to_st_fdma_chan(chan);

	स_नकल(&fchan->scfg, slave_cfg, माप(fchan->scfg));
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा st_fdma_driverdata fdma_mpe31_stih407_11 = अणु
	.name = "STiH407",
	.id = 0,
पूर्ण;

अटल स्थिर काष्ठा st_fdma_driverdata fdma_mpe31_stih407_12 = अणु
	.name = "STiH407",
	.id = 1,
पूर्ण;

अटल स्थिर काष्ठा st_fdma_driverdata fdma_mpe31_stih407_13 = अणु
	.name = "STiH407",
	.id = 2,
पूर्ण;

अटल स्थिर काष्ठा of_device_id st_fdma_match[] = अणु
	अणु .compatible = "st,stih407-fdma-mpe31-11"
	  , .data = &fdma_mpe31_stih407_11 पूर्ण,
	अणु .compatible = "st,stih407-fdma-mpe31-12"
	  , .data = &fdma_mpe31_stih407_12 पूर्ण,
	अणु .compatible = "st,stih407-fdma-mpe31-13"
	  , .data = &fdma_mpe31_stih407_13 पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_fdma_match);

अटल पूर्णांक st_fdma_parse_dt(काष्ठा platक्रमm_device *pdev,
			स्थिर काष्ठा st_fdma_driverdata *drvdata,
			काष्ठा st_fdma_dev *fdev)
अणु
	snम_लिखो(fdev->fw_name, FW_NAME_SIZE, "fdma_%s_%d.elf",
		drvdata->name, drvdata->id);

	वापस of_property_पढ़ो_u32(pdev->dev.of_node, "dma-channels",
				    &fdev->nr_channels);
पूर्ण
#घोषणा FDMA_DMA_BUSWIDTHS	(BIT(DMA_SLAVE_BUSWIDTH_1_BYTE) | \
				 BIT(DMA_SLAVE_BUSWIDTH_2_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_3_BYTES) | \
				 BIT(DMA_SLAVE_BUSWIDTH_4_BYTES))

अटल व्योम st_fdma_मुक्त(काष्ठा st_fdma_dev *fdev)
अणु
	काष्ठा st_fdma_chan *fchan;
	पूर्णांक i;

	क्रम (i = 0; i < fdev->nr_channels; i++) अणु
		fchan = &fdev->chans[i];
		list_del(&fchan->vchan.chan.device_node);
		tasklet_समाप्त(&fchan->vchan.task);
	पूर्ण
पूर्ण

अटल पूर्णांक st_fdma_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_fdma_dev *fdev;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा device_node *np = pdev->dev.of_node;
	स्थिर काष्ठा st_fdma_driverdata *drvdata;
	पूर्णांक ret, i;

	match = of_match_device((st_fdma_match), &pdev->dev);
	अगर (!match || !match->data) अणु
		dev_err(&pdev->dev, "No device match found\n");
		वापस -ENODEV;
	पूर्ण

	drvdata = match->data;

	fdev = devm_kzalloc(&pdev->dev, माप(*fdev), GFP_KERNEL);
	अगर (!fdev)
		वापस -ENOMEM;

	ret = st_fdma_parse_dt(pdev, drvdata, fdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "unable to find platform data\n");
		जाओ err;
	पूर्ण

	fdev->chans = devm_kसुस्मृति(&pdev->dev, fdev->nr_channels,
				   माप(काष्ठा st_fdma_chan), GFP_KERNEL);
	अगर (!fdev->chans)
		वापस -ENOMEM;

	fdev->dev = &pdev->dev;
	fdev->drvdata = drvdata;
	platक्रमm_set_drvdata(pdev, fdev);

	fdev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (fdev->irq < 0)
		वापस -EINVAL;

	ret = devm_request_irq(&pdev->dev, fdev->irq, st_fdma_irq_handler, 0,
			       dev_name(&pdev->dev), fdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Failed to request irq (%d)\n", ret);
		जाओ err;
	पूर्ण

	fdev->slim_rproc = st_slim_rproc_alloc(pdev, fdev->fw_name);
	अगर (IS_ERR(fdev->slim_rproc)) अणु
		ret = PTR_ERR(fdev->slim_rproc);
		dev_err(&pdev->dev, "slim_rproc_alloc failed (%d)\n", ret);
		जाओ err;
	पूर्ण

	/* Initialise list of FDMA channels */
	INIT_LIST_HEAD(&fdev->dma_device.channels);
	क्रम (i = 0; i < fdev->nr_channels; i++) अणु
		काष्ठा st_fdma_chan *fchan = &fdev->chans[i];

		fchan->fdev = fdev;
		fchan->vchan.desc_मुक्त = st_fdma_मुक्त_desc;
		vchan_init(&fchan->vchan, &fdev->dma_device);
	पूर्ण

	/* Initialise the FDMA dreq (reserve 0 & 31 क्रम FDMA use) */
	fdev->dreq_mask = BIT(0) | BIT(31);

	dma_cap_set(DMA_SLAVE, fdev->dma_device.cap_mask);
	dma_cap_set(DMA_CYCLIC, fdev->dma_device.cap_mask);
	dma_cap_set(DMA_MEMCPY, fdev->dma_device.cap_mask);

	fdev->dma_device.dev = &pdev->dev;
	fdev->dma_device.device_alloc_chan_resources = st_fdma_alloc_chan_res;
	fdev->dma_device.device_मुक्त_chan_resources = st_fdma_मुक्त_chan_res;
	fdev->dma_device.device_prep_dma_cyclic	= st_fdma_prep_dma_cyclic;
	fdev->dma_device.device_prep_slave_sg = st_fdma_prep_slave_sg;
	fdev->dma_device.device_prep_dma_स_नकल = st_fdma_prep_dma_स_नकल;
	fdev->dma_device.device_tx_status = st_fdma_tx_status;
	fdev->dma_device.device_issue_pending = st_fdma_issue_pending;
	fdev->dma_device.device_terminate_all = st_fdma_terminate_all;
	fdev->dma_device.device_config = st_fdma_slave_config;
	fdev->dma_device.device_छोड़ो = st_fdma_छोड़ो;
	fdev->dma_device.device_resume = st_fdma_resume;

	fdev->dma_device.src_addr_widths = FDMA_DMA_BUSWIDTHS;
	fdev->dma_device.dst_addr_widths = FDMA_DMA_BUSWIDTHS;
	fdev->dma_device.directions = BIT(DMA_DEV_TO_MEM) | BIT(DMA_MEM_TO_DEV);
	fdev->dma_device.residue_granularity = DMA_RESIDUE_GRANULARITY_BURST;

	ret = dmaenginem_async_device_रेजिस्टर(&fdev->dma_device);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to register DMA device (%d)\n", ret);
		जाओ err_rproc;
	पूर्ण

	ret = of_dma_controller_रेजिस्टर(np, st_fdma_of_xlate, fdev);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Failed to register controller (%d)\n", ret);
		जाओ err_rproc;
	पूर्ण

	dev_info(&pdev->dev, "ST FDMA engine driver, irq:%d\n", fdev->irq);

	वापस 0;

err_rproc:
	st_fdma_मुक्त(fdev);
	st_slim_rproc_put(fdev->slim_rproc);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक st_fdma_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा st_fdma_dev *fdev = platक्रमm_get_drvdata(pdev);

	devm_मुक्त_irq(&pdev->dev, fdev->irq, fdev);
	st_slim_rproc_put(fdev->slim_rproc);
	of_dma_controller_मुक्त(pdev->dev.of_node);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver st_fdma_platक्रमm_driver = अणु
	.driver = अणु
		.name = DRIVER_NAME,
		.of_match_table = st_fdma_match,
	पूर्ण,
	.probe = st_fdma_probe,
	.हटाओ = st_fdma_हटाओ,
पूर्ण;
module_platक्रमm_driver(st_fdma_platक्रमm_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("STMicroelectronics FDMA engine driver");
MODULE_AUTHOR("Ludovic.barre <Ludovic.barre@st.com>");
MODULE_AUTHOR("Peter Griffin <peter.griffin@linaro.org>");
MODULE_ALIAS("platform: " DRIVER_NAME);
