<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2018 MediaTek Inc.

#समावेश <linux/completion.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/module.h>
#समावेश <linux/mailbox_controller.h>
#समावेश <linux/soc/mediatek/mtk-cmdq.h>

#घोषणा CMDQ_WRITE_ENABLE_MASK	BIT(0)
#घोषणा CMDQ_POLL_ENABLE_MASK	BIT(0)
#घोषणा CMDQ_EOC_IRQ_EN		BIT(0)
#घोषणा CMDQ_REG_TYPE		1
#घोषणा CMDQ_JUMP_RELATIVE	1

काष्ठा cmdq_inकाष्ठाion अणु
	जोड़ अणु
		u32 value;
		u32 mask;
		काष्ठा अणु
			u16 arg_c;
			u16 src_reg;
		पूर्ण;
	पूर्ण;
	जोड़ अणु
		u16 offset;
		u16 event;
		u16 reg_dst;
	पूर्ण;
	जोड़ अणु
		u8 subsys;
		काष्ठा अणु
			u8 sop:5;
			u8 arg_c_t:1;
			u8 src_t:1;
			u8 dst_t:1;
		पूर्ण;
	पूर्ण;
	u8 op;
पूर्ण;

पूर्णांक cmdq_dev_get_client_reg(काष्ठा device *dev,
			    काष्ठा cmdq_client_reg *client_reg, पूर्णांक idx)
अणु
	काष्ठा of_phandle_args spec;
	पूर्णांक err;

	अगर (!client_reg)
		वापस -ENOENT;

	err = of_parse_phandle_with_fixed_args(dev->of_node,
					       "mediatek,gce-client-reg",
					       3, idx, &spec);
	अगर (err < 0) अणु
		dev_err(dev,
			"error %d can't parse gce-client-reg property (%d)",
			err, idx);

		वापस err;
	पूर्ण

	client_reg->subsys = (u8)spec.args[0];
	client_reg->offset = (u16)spec.args[1];
	client_reg->size = (u16)spec.args[2];
	of_node_put(spec.np);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cmdq_dev_get_client_reg);

काष्ठा cmdq_client *cmdq_mbox_create(काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा cmdq_client *client;

	client = kzalloc(माप(*client), GFP_KERNEL);
	अगर (!client)
		वापस (काष्ठा cmdq_client *)-ENOMEM;

	client->client.dev = dev;
	client->client.tx_block = false;
	client->client.knows_txकरोne = true;
	client->chan = mbox_request_channel(&client->client, index);

	अगर (IS_ERR(client->chan)) अणु
		दीर्घ err;

		dev_err(dev, "failed to request channel\n");
		err = PTR_ERR(client->chan);
		kमुक्त(client);

		वापस ERR_PTR(err);
	पूर्ण

	वापस client;
पूर्ण
EXPORT_SYMBOL(cmdq_mbox_create);

व्योम cmdq_mbox_destroy(काष्ठा cmdq_client *client)
अणु
	mbox_मुक्त_channel(client->chan);
	kमुक्त(client);
पूर्ण
EXPORT_SYMBOL(cmdq_mbox_destroy);

काष्ठा cmdq_pkt *cmdq_pkt_create(काष्ठा cmdq_client *client, माप_प्रकार size)
अणु
	काष्ठा cmdq_pkt *pkt;
	काष्ठा device *dev;
	dma_addr_t dma_addr;

	pkt = kzalloc(माप(*pkt), GFP_KERNEL);
	अगर (!pkt)
		वापस ERR_PTR(-ENOMEM);
	pkt->va_base = kzalloc(size, GFP_KERNEL);
	अगर (!pkt->va_base) अणु
		kमुक्त(pkt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	pkt->buf_size = size;
	pkt->cl = (व्योम *)client;

	dev = client->chan->mbox->dev;
	dma_addr = dma_map_single(dev, pkt->va_base, pkt->buf_size,
				  DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		dev_err(dev, "dma map failed, size=%u\n", (u32)(u64)size);
		kमुक्त(pkt->va_base);
		kमुक्त(pkt);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	pkt->pa_base = dma_addr;

	वापस pkt;
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_create);

व्योम cmdq_pkt_destroy(काष्ठा cmdq_pkt *pkt)
अणु
	काष्ठा cmdq_client *client = (काष्ठा cmdq_client *)pkt->cl;

	dma_unmap_single(client->chan->mbox->dev, pkt->pa_base, pkt->buf_size,
			 DMA_TO_DEVICE);
	kमुक्त(pkt->va_base);
	kमुक्त(pkt);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_destroy);

अटल पूर्णांक cmdq_pkt_append_command(काष्ठा cmdq_pkt *pkt,
				   काष्ठा cmdq_inकाष्ठाion inst)
अणु
	काष्ठा cmdq_inकाष्ठाion *cmd_ptr;

	अगर (unlikely(pkt->cmd_buf_size + CMDQ_INST_SIZE > pkt->buf_size)) अणु
		/*
		 * In the हाल of allocated buffer size (pkt->buf_size) is used
		 * up, the real required size (pkt->cmdq_buf_size) is still
		 * increased, so that the user knows how much memory should be
		 * ultimately allocated after appending all commands and
		 * flushing the command packet. Thereक्रम, the user can call
		 * cmdq_pkt_create() again with the real required buffer size.
		 */
		pkt->cmd_buf_size += CMDQ_INST_SIZE;
		WARN_ONCE(1, "%s: buffer size %u is too small !\n",
			__func__, (u32)pkt->buf_size);
		वापस -ENOMEM;
	पूर्ण

	cmd_ptr = pkt->va_base + pkt->cmd_buf_size;
	*cmd_ptr = inst;
	pkt->cmd_buf_size += CMDQ_INST_SIZE;

	वापस 0;
पूर्ण

पूर्णांक cmdq_pkt_ग_लिखो(काष्ठा cmdq_pkt *pkt, u8 subsys, u16 offset, u32 value)
अणु
	काष्ठा cmdq_inकाष्ठाion inst;

	inst.op = CMDQ_CODE_WRITE;
	inst.value = value;
	inst.offset = offset;
	inst.subsys = subsys;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_ग_लिखो);

पूर्णांक cmdq_pkt_ग_लिखो_mask(काष्ठा cmdq_pkt *pkt, u8 subsys,
			u16 offset, u32 value, u32 mask)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणु अणु0पूर्ण पूर्ण;
	u16 offset_mask = offset;
	पूर्णांक err;

	अगर (mask != 0xffffffff) अणु
		inst.op = CMDQ_CODE_MASK;
		inst.mask = ~mask;
		err = cmdq_pkt_append_command(pkt, inst);
		अगर (err < 0)
			वापस err;

		offset_mask |= CMDQ_WRITE_ENABLE_MASK;
	पूर्ण
	err = cmdq_pkt_ग_लिखो(pkt, subsys, offset_mask, value);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_ग_लिखो_mask);

पूर्णांक cmdq_pkt_पढ़ो_s(काष्ठा cmdq_pkt *pkt, u16 high_addr_reg_idx, u16 addr_low,
		    u16 reg_idx)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;

	inst.op = CMDQ_CODE_READ_S;
	inst.dst_t = CMDQ_REG_TYPE;
	inst.sop = high_addr_reg_idx;
	inst.reg_dst = reg_idx;
	inst.src_reg = addr_low;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_पढ़ो_s);

पूर्णांक cmdq_pkt_ग_लिखो_s(काष्ठा cmdq_pkt *pkt, u16 high_addr_reg_idx,
		     u16 addr_low, u16 src_reg_idx)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;

	inst.op = CMDQ_CODE_WRITE_S;
	inst.src_t = CMDQ_REG_TYPE;
	inst.sop = high_addr_reg_idx;
	inst.offset = addr_low;
	inst.src_reg = src_reg_idx;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_ग_लिखो_s);

पूर्णांक cmdq_pkt_ग_लिखो_s_mask(काष्ठा cmdq_pkt *pkt, u16 high_addr_reg_idx,
			  u16 addr_low, u16 src_reg_idx, u32 mask)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;
	पूर्णांक err;

	inst.op = CMDQ_CODE_MASK;
	inst.mask = ~mask;
	err = cmdq_pkt_append_command(pkt, inst);
	अगर (err < 0)
		वापस err;

	inst.mask = 0;
	inst.op = CMDQ_CODE_WRITE_S_MASK;
	inst.src_t = CMDQ_REG_TYPE;
	inst.sop = high_addr_reg_idx;
	inst.offset = addr_low;
	inst.src_reg = src_reg_idx;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_ग_लिखो_s_mask);

पूर्णांक cmdq_pkt_ग_लिखो_s_value(काष्ठा cmdq_pkt *pkt, u8 high_addr_reg_idx,
			   u16 addr_low, u32 value)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;

	inst.op = CMDQ_CODE_WRITE_S;
	inst.sop = high_addr_reg_idx;
	inst.offset = addr_low;
	inst.value = value;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_ग_लिखो_s_value);

पूर्णांक cmdq_pkt_ग_लिखो_s_mask_value(काष्ठा cmdq_pkt *pkt, u8 high_addr_reg_idx,
				u16 addr_low, u32 value, u32 mask)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;
	पूर्णांक err;

	inst.op = CMDQ_CODE_MASK;
	inst.mask = ~mask;
	err = cmdq_pkt_append_command(pkt, inst);
	अगर (err < 0)
		वापस err;

	inst.op = CMDQ_CODE_WRITE_S_MASK;
	inst.sop = high_addr_reg_idx;
	inst.offset = addr_low;
	inst.value = value;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_ग_लिखो_s_mask_value);

पूर्णांक cmdq_pkt_wfe(काष्ठा cmdq_pkt *pkt, u16 event, bool clear)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणु अणु0पूर्ण पूर्ण;
	u32 clear_option = clear ? CMDQ_WFE_UPDATE : 0;

	अगर (event >= CMDQ_MAX_EVENT)
		वापस -EINVAL;

	inst.op = CMDQ_CODE_WFE;
	inst.value = CMDQ_WFE_OPTION | clear_option;
	inst.event = event;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_wfe);

पूर्णांक cmdq_pkt_clear_event(काष्ठा cmdq_pkt *pkt, u16 event)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणु अणु0पूर्ण पूर्ण;

	अगर (event >= CMDQ_MAX_EVENT)
		वापस -EINVAL;

	inst.op = CMDQ_CODE_WFE;
	inst.value = CMDQ_WFE_UPDATE;
	inst.event = event;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_clear_event);

पूर्णांक cmdq_pkt_set_event(काष्ठा cmdq_pkt *pkt, u16 event)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;

	अगर (event >= CMDQ_MAX_EVENT)
		वापस -EINVAL;

	inst.op = CMDQ_CODE_WFE;
	inst.value = CMDQ_WFE_UPDATE | CMDQ_WFE_UPDATE_VALUE;
	inst.event = event;

	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_set_event);

पूर्णांक cmdq_pkt_poll(काष्ठा cmdq_pkt *pkt, u8 subsys,
		  u16 offset, u32 value)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक err;

	inst.op = CMDQ_CODE_POLL;
	inst.value = value;
	inst.offset = offset;
	inst.subsys = subsys;
	err = cmdq_pkt_append_command(pkt, inst);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_poll);

पूर्णांक cmdq_pkt_poll_mask(काष्ठा cmdq_pkt *pkt, u8 subsys,
		       u16 offset, u32 value, u32 mask)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक err;

	inst.op = CMDQ_CODE_MASK;
	inst.mask = ~mask;
	err = cmdq_pkt_append_command(pkt, inst);
	अगर (err < 0)
		वापस err;

	offset = offset | CMDQ_POLL_ENABLE_MASK;
	err = cmdq_pkt_poll(pkt, subsys, offset, value);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_poll_mask);

पूर्णांक cmdq_pkt_assign(काष्ठा cmdq_pkt *pkt, u16 reg_idx, u32 value)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;

	inst.op = CMDQ_CODE_LOGIC;
	inst.dst_t = CMDQ_REG_TYPE;
	inst.reg_dst = reg_idx;
	inst.value = value;
	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_assign);

पूर्णांक cmdq_pkt_jump(काष्ठा cmdq_pkt *pkt, dma_addr_t addr)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणुपूर्ण;

	inst.op = CMDQ_CODE_JUMP;
	inst.offset = CMDQ_JUMP_RELATIVE;
	inst.value = addr >>
		cmdq_get_shअगरt_pa(((काष्ठा cmdq_client *)pkt->cl)->chan);
	वापस cmdq_pkt_append_command(pkt, inst);
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_jump);

पूर्णांक cmdq_pkt_finalize(काष्ठा cmdq_pkt *pkt)
अणु
	काष्ठा cmdq_inकाष्ठाion inst = अणु अणु0पूर्ण पूर्ण;
	पूर्णांक err;

	/* insert EOC and generate IRQ क्रम each command iteration */
	inst.op = CMDQ_CODE_EOC;
	inst.value = CMDQ_EOC_IRQ_EN;
	err = cmdq_pkt_append_command(pkt, inst);
	अगर (err < 0)
		वापस err;

	/* JUMP to end */
	inst.op = CMDQ_CODE_JUMP;
	inst.value = CMDQ_JUMP_PASS >>
		cmdq_get_shअगरt_pa(((काष्ठा cmdq_client *)pkt->cl)->chan);
	err = cmdq_pkt_append_command(pkt, inst);

	वापस err;
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_finalize);

अटल व्योम cmdq_pkt_flush_async_cb(काष्ठा cmdq_cb_data data)
अणु
	काष्ठा cmdq_pkt *pkt = (काष्ठा cmdq_pkt *)data.data;
	काष्ठा cmdq_task_cb *cb = &pkt->cb;
	काष्ठा cmdq_client *client = (काष्ठा cmdq_client *)pkt->cl;

	dma_sync_single_क्रम_cpu(client->chan->mbox->dev, pkt->pa_base,
				pkt->cmd_buf_size, DMA_TO_DEVICE);
	अगर (cb->cb) अणु
		data.data = cb->data;
		cb->cb(data);
	पूर्ण
पूर्ण

पूर्णांक cmdq_pkt_flush_async(काष्ठा cmdq_pkt *pkt, cmdq_async_flush_cb cb,
			 व्योम *data)
अणु
	पूर्णांक err;
	काष्ठा cmdq_client *client = (काष्ठा cmdq_client *)pkt->cl;

	pkt->cb.cb = cb;
	pkt->cb.data = data;
	pkt->async_cb.cb = cmdq_pkt_flush_async_cb;
	pkt->async_cb.data = pkt;

	dma_sync_single_क्रम_device(client->chan->mbox->dev, pkt->pa_base,
				   pkt->cmd_buf_size, DMA_TO_DEVICE);

	err = mbox_send_message(client->chan, pkt);
	अगर (err < 0)
		वापस err;
	/* We can send next packet immediately, so just call txकरोne. */
	mbox_client_txकरोne(client->chan, 0);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cmdq_pkt_flush_async);

MODULE_LICENSE("GPL v2");
