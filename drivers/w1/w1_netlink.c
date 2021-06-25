<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2003 Evgeniy Polyakov <zbr@ioremap.net>
 */

#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netlink.h>
#समावेश <linux/connector.h>

#समावेश "w1_internal.h"
#समावेश "w1_netlink.h"

#अगर defined(CONFIG_W1_CON) && (defined(CONFIG_CONNECTOR) || (defined(CONFIG_CONNECTOR_MODULE) && defined(CONFIG_W1_MODULE)))

/* Bundle together everything required to process a request in one memory
 * allocation.
 */
काष्ठा w1_cb_block अणु
	atomic_t refcnt;
	u32 portid; /* Sending process port ID */
	/* maximum value क्रम first_cn->len */
	u16 maxlen;
	/* poपूर्णांकers to building up the reply message */
	काष्ठा cn_msg *first_cn; /* fixed once the काष्ठाure is populated */
	काष्ठा cn_msg *cn; /* advances as cn_msg is appeneded */
	काष्ठा w1_netlink_msg *msg; /* advances as w1_netlink_msg is appened */
	काष्ठा w1_netlink_cmd *cmd; /* advances as cmds are appened */
	काष्ठा w1_netlink_msg *cur_msg; /* currently message being processed */
	/* copy of the original request follows */
	काष्ठा cn_msg request_cn;
	/* followed by variable length:
	 * cn_msg, data (w1_netlink_msg and w1_netlink_cmd)
	 * one or more काष्ठा w1_cb_node
	 * reply first_cn, data (w1_netlink_msg and w1_netlink_cmd)
	 */
पूर्ण;
काष्ठा w1_cb_node अणु
	काष्ठा w1_async_cmd async;
	/* poपूर्णांकers within w1_cb_block and cn data */
	काष्ठा w1_cb_block *block;
	काष्ठा w1_netlink_msg *msg;
	काष्ठा w1_slave *sl;
	काष्ठा w1_master *dev;
पूर्ण;

/**
 * w1_reply_len() - calculate current reply length, compare to maxlen
 * @block: block to calculate
 *
 * Calculates the current message length including possible multiple
 * cn_msg and data, excludes the first माप(काष्ठा cn_msg).  Direclty
 * compariable to maxlen and usable to send the message.
 */
अटल u16 w1_reply_len(काष्ठा w1_cb_block *block)
अणु
	अगर (!block->cn)
		वापस 0;
	वापस (u8 *)block->cn - (u8 *)block->first_cn + block->cn->len;
पूर्ण

अटल व्योम w1_unref_block(काष्ठा w1_cb_block *block)
अणु
	अगर (atomic_sub_वापस(1, &block->refcnt) == 0) अणु
		u16 len = w1_reply_len(block);
		अगर (len) अणु
			cn_netlink_send_mult(block->first_cn, len,
				block->portid, 0, GFP_KERNEL);
		पूर्ण
		kमुक्त(block);
	पूर्ण
पूर्ण

/**
 * w1_reply_make_space() - send message अगर needed to make space
 * @block: block to make space on
 * @space: how many bytes requested
 *
 * Verअगरy there is enough room left क्रम the caller to add "space" bytes to the
 * message, अगर there isn't send the message and reset.
 */
अटल व्योम w1_reply_make_space(काष्ठा w1_cb_block *block, u16 space)
अणु
	u16 len = w1_reply_len(block);
	अगर (len + space >= block->maxlen) अणु
		cn_netlink_send_mult(block->first_cn, len, block->portid, 0, GFP_KERNEL);
		block->first_cn->len = 0;
		block->cn = शून्य;
		block->msg = शून्य;
		block->cmd = शून्य;
	पूर्ण
पूर्ण

/* Early send when replies aren't bundled. */
अटल व्योम w1_netlink_check_send(काष्ठा w1_cb_block *block)
अणु
	अगर (!(block->request_cn.flags & W1_CN_BUNDLE) && block->cn)
		w1_reply_make_space(block, block->maxlen);
पूर्ण

/**
 * w1_netlink_setup_msg() - prepare to ग_लिखो block->msg
 * @block: block to operate on
 * @ack: determines अगर cn can be reused
 *
 * block->cn will be setup with the correct ack, advancing अगर needed
 * block->cn->len करोes not include space क्रम block->msg
 * block->msg advances but reमुख्यs uninitialized
 */
अटल व्योम w1_netlink_setup_msg(काष्ठा w1_cb_block *block, u32 ack)
अणु
	अगर (block->cn && block->cn->ack == ack) अणु
		block->msg = (काष्ठा w1_netlink_msg *)(block->cn->data + block->cn->len);
	पूर्ण अन्यथा अणु
		/* advance or set to data */
		अगर (block->cn)
			block->cn = (काष्ठा cn_msg *)(block->cn->data +
				block->cn->len);
		अन्यथा
			block->cn = block->first_cn;

		स_नकल(block->cn, &block->request_cn, माप(*block->cn));
		block->cn->len = 0;
		block->cn->ack = ack;
		block->msg = (काष्ठा w1_netlink_msg *)block->cn->data;
	पूर्ण
पूर्ण

/* Append cmd to msg, include cmd->data as well.  This is because
 * any following data goes with the command and in the हाल of a पढ़ो is
 * the results.
 */
अटल व्योम w1_netlink_queue_cmd(काष्ठा w1_cb_block *block,
	काष्ठा w1_netlink_cmd *cmd)
अणु
	u32 space;
	w1_reply_make_space(block, माप(काष्ठा cn_msg) +
		माप(काष्ठा w1_netlink_msg) + माप(*cmd) + cmd->len);

	/* There's a status message sent after each command, so no poपूर्णांक
	 * in trying to bundle this cmd after an existing one, because
	 * there won't be one.  Allocate and copy over a new cn_msg.
	 */
	w1_netlink_setup_msg(block, block->request_cn.seq + 1);
	स_नकल(block->msg, block->cur_msg, माप(*block->msg));
	block->cn->len += माप(*block->msg);
	block->msg->len = 0;
	block->cmd = (काष्ठा w1_netlink_cmd *)(block->msg->data);

	space = माप(*cmd) + cmd->len;
	अगर (block->cmd != cmd)
		स_नकल(block->cmd, cmd, space);
	block->cn->len += space;
	block->msg->len += space;
पूर्ण

/* Append req_msg and req_cmd, no other commands and no data from req_cmd are
 * copied.
 */
अटल व्योम w1_netlink_queue_status(काष्ठा w1_cb_block *block,
	काष्ठा w1_netlink_msg *req_msg, काष्ठा w1_netlink_cmd *req_cmd,
	पूर्णांक error)
अणु
	u16 space = माप(काष्ठा cn_msg) + माप(*req_msg) + माप(*req_cmd);
	w1_reply_make_space(block, space);
	w1_netlink_setup_msg(block, block->request_cn.ack);

	स_नकल(block->msg, req_msg, माप(*req_msg));
	block->cn->len += माप(*req_msg);
	block->msg->len = 0;
	block->msg->status = (u8)-error;
	अगर (req_cmd) अणु
		काष्ठा w1_netlink_cmd *cmd = (काष्ठा w1_netlink_cmd *)block->msg->data;
		स_नकल(cmd, req_cmd, माप(*cmd));
		block->cn->len += माप(*cmd);
		block->msg->len += माप(*cmd);
		cmd->len = 0;
	पूर्ण
	w1_netlink_check_send(block);
पूर्ण

/**
 * w1_netlink_send_error() - sends the error message now
 * @cn: original cn_msg
 * @msg: original w1_netlink_msg
 * @portid: where to send it
 * @error: error status
 *
 * Use when a block isn't available to queue the message to and cn, msg
 * might not be contiguous.
 */
अटल व्योम w1_netlink_send_error(काष्ठा cn_msg *cn, काष्ठा w1_netlink_msg *msg,
	पूर्णांक portid, पूर्णांक error)
अणु
	काष्ठा अणु
		काष्ठा cn_msg cn;
		काष्ठा w1_netlink_msg msg;
	पूर्ण packet;
	स_नकल(&packet.cn, cn, माप(packet.cn));
	स_नकल(&packet.msg, msg, माप(packet.msg));
	packet.cn.len = माप(packet.msg);
	packet.msg.len = 0;
	packet.msg.status = (u8)-error;
	cn_netlink_send(&packet.cn, portid, 0, GFP_KERNEL);
पूर्ण

/**
 * w1_netlink_send() - sends w1 netlink notअगरications
 * @dev: w1_master the even is associated with or क्रम
 * @msg: w1_netlink_msg message to be sent
 *
 * This are notअगरications generated from the kernel.
 */
व्योम w1_netlink_send(काष्ठा w1_master *dev, काष्ठा w1_netlink_msg *msg)
अणु
	काष्ठा अणु
		काष्ठा cn_msg cn;
		काष्ठा w1_netlink_msg msg;
	पूर्ण packet;
	स_रखो(&packet, 0, माप(packet));

	packet.cn.id.idx = CN_W1_IDX;
	packet.cn.id.val = CN_W1_VAL;

	packet.cn.seq = dev->seq++;
	packet.cn.len = माप(*msg);

	स_नकल(&packet.msg, msg, माप(*msg));
	packet.msg.len = 0;

	cn_netlink_send(&packet.cn, 0, 0, GFP_KERNEL);
पूर्ण

अटल व्योम w1_send_slave(काष्ठा w1_master *dev, u64 rn)
अणु
	काष्ठा w1_cb_block *block = dev->priv;
	काष्ठा w1_netlink_cmd *cache_cmd = block->cmd;
	u64 *data;

	w1_reply_make_space(block, माप(*data));

	/* Add cmd back अगर the packet was sent */
	अगर (!block->cmd) अणु
		cache_cmd->len = 0;
		w1_netlink_queue_cmd(block, cache_cmd);
	पूर्ण

	data = (u64 *)(block->cmd->data + block->cmd->len);

	*data = rn;
	block->cn->len += माप(*data);
	block->msg->len += माप(*data);
	block->cmd->len += माप(*data);
पूर्ण

अटल व्योम w1_found_send_slave(काष्ठा w1_master *dev, u64 rn)
अणु
	/* update kernel slave list */
	w1_slave_found(dev, rn);

	w1_send_slave(dev, rn);
पूर्ण

/* Get the current slave list, or search (with or without alarm) */
अटल पूर्णांक w1_get_slaves(काष्ठा w1_master *dev, काष्ठा w1_netlink_cmd *req_cmd)
अणु
	काष्ठा w1_slave *sl;

	req_cmd->len = 0;
	w1_netlink_queue_cmd(dev->priv, req_cmd);

	अगर (req_cmd->cmd == W1_CMD_LIST_SLAVES) अणु
		u64 rn;
		mutex_lock(&dev->list_mutex);
		list_क्रम_each_entry(sl, &dev->slist, w1_slave_entry) अणु
			स_नकल(&rn, &sl->reg_num, माप(rn));
			w1_send_slave(dev, rn);
		पूर्ण
		mutex_unlock(&dev->list_mutex);
	पूर्ण अन्यथा अणु
		w1_search_process_cb(dev, req_cmd->cmd == W1_CMD_ALARM_SEARCH ?
			W1_ALARM_SEARCH : W1_SEARCH, w1_found_send_slave);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक w1_process_command_io(काष्ठा w1_master *dev,
	काष्ठा w1_netlink_cmd *cmd)
अणु
	पूर्णांक err = 0;

	चयन (cmd->cmd) अणु
	हाल W1_CMD_TOUCH:
		w1_touch_block(dev, cmd->data, cmd->len);
		w1_netlink_queue_cmd(dev->priv, cmd);
		अवरोध;
	हाल W1_CMD_READ:
		w1_पढ़ो_block(dev, cmd->data, cmd->len);
		w1_netlink_queue_cmd(dev->priv, cmd);
		अवरोध;
	हाल W1_CMD_WRITE:
		w1_ग_लिखो_block(dev, cmd->data, cmd->len);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक w1_process_command_addहटाओ(काष्ठा w1_master *dev,
	काष्ठा w1_netlink_cmd *cmd)
अणु
	काष्ठा w1_slave *sl;
	पूर्णांक err = 0;
	काष्ठा w1_reg_num *id;

	अगर (cmd->len != माप(*id))
		वापस -EINVAL;

	id = (काष्ठा w1_reg_num *)cmd->data;

	sl = w1_slave_search_device(dev, id);
	चयन (cmd->cmd) अणु
	हाल W1_CMD_SLAVE_ADD:
		अगर (sl)
			err = -EINVAL;
		अन्यथा
			err = w1_attach_slave_device(dev, id);
		अवरोध;
	हाल W1_CMD_SLAVE_REMOVE:
		अगर (sl)
			w1_slave_detach(sl);
		अन्यथा
			err = -EINVAL;
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक w1_process_command_master(काष्ठा w1_master *dev,
	काष्ठा w1_netlink_cmd *req_cmd)
अणु
	पूर्णांक err = -EINVAL;

	/* drop bus_mutex क्रम search (करोes it's own locking), and add/हटाओ
	 * which करोesn't use the bus
	 */
	चयन (req_cmd->cmd) अणु
	हाल W1_CMD_SEARCH:
	हाल W1_CMD_ALARM_SEARCH:
	हाल W1_CMD_LIST_SLAVES:
		mutex_unlock(&dev->bus_mutex);
		err = w1_get_slaves(dev, req_cmd);
		mutex_lock(&dev->bus_mutex);
		अवरोध;
	हाल W1_CMD_READ:
	हाल W1_CMD_WRITE:
	हाल W1_CMD_TOUCH:
		err = w1_process_command_io(dev, req_cmd);
		अवरोध;
	हाल W1_CMD_RESET:
		err = w1_reset_bus(dev);
		अवरोध;
	हाल W1_CMD_SLAVE_ADD:
	हाल W1_CMD_SLAVE_REMOVE:
		mutex_unlock(&dev->bus_mutex);
		mutex_lock(&dev->mutex);
		err = w1_process_command_addहटाओ(dev, req_cmd);
		mutex_unlock(&dev->mutex);
		mutex_lock(&dev->bus_mutex);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक w1_process_command_slave(काष्ठा w1_slave *sl,
		काष्ठा w1_netlink_cmd *cmd)
अणु
	dev_dbg(&sl->master->dev, "%s: %02x.%012llx.%02x: cmd=%02x, len=%u.\n",
		__func__, sl->reg_num.family, (अचिन्हित दीर्घ दीर्घ)sl->reg_num.id,
		sl->reg_num.crc, cmd->cmd, cmd->len);

	वापस w1_process_command_io(sl->master, cmd);
पूर्ण

अटल पूर्णांक w1_process_command_root(काष्ठा cn_msg *req_cn, u32 portid)
अणु
	काष्ठा w1_master *dev;
	काष्ठा cn_msg *cn;
	काष्ठा w1_netlink_msg *msg;
	u32 *id;

	cn = kदो_स्मृति(PAGE_SIZE, GFP_KERNEL);
	अगर (!cn)
		वापस -ENOMEM;

	cn->id.idx = CN_W1_IDX;
	cn->id.val = CN_W1_VAL;

	cn->seq = req_cn->seq;
	cn->ack = req_cn->seq + 1;
	cn->len = माप(काष्ठा w1_netlink_msg);
	msg = (काष्ठा w1_netlink_msg *)cn->data;

	msg->type = W1_LIST_MASTERS;
	msg->status = 0;
	msg->len = 0;
	id = (u32 *)msg->data;

	mutex_lock(&w1_mlock);
	list_क्रम_each_entry(dev, &w1_masters, w1_master_entry) अणु
		अगर (cn->len + माप(*id) > PAGE_SIZE - माप(काष्ठा cn_msg)) अणु
			cn_netlink_send(cn, portid, 0, GFP_KERNEL);
			cn->len = माप(काष्ठा w1_netlink_msg);
			msg->len = 0;
			id = (u32 *)msg->data;
		पूर्ण

		*id = dev->id;
		msg->len += माप(*id);
		cn->len += माप(*id);
		id++;
	पूर्ण
	cn_netlink_send(cn, portid, 0, GFP_KERNEL);
	mutex_unlock(&w1_mlock);

	kमुक्त(cn);
	वापस 0;
पूर्ण

अटल व्योम w1_process_cb(काष्ठा w1_master *dev, काष्ठा w1_async_cmd *async_cmd)
अणु
	काष्ठा w1_cb_node *node = container_of(async_cmd, काष्ठा w1_cb_node,
		async);
	u16 mlen = node->msg->len;
	u16 len;
	पूर्णांक err = 0;
	काष्ठा w1_slave *sl = node->sl;
	काष्ठा w1_netlink_cmd *cmd = (काष्ठा w1_netlink_cmd *)node->msg->data;

	mutex_lock(&dev->bus_mutex);
	dev->priv = node->block;
	अगर (sl && w1_reset_select_slave(sl))
		err = -ENODEV;
	node->block->cur_msg = node->msg;

	जबतक (mlen && !err) अणु
		अगर (cmd->len + माप(काष्ठा w1_netlink_cmd) > mlen) अणु
			err = -E2BIG;
			अवरोध;
		पूर्ण

		अगर (sl)
			err = w1_process_command_slave(sl, cmd);
		अन्यथा
			err = w1_process_command_master(dev, cmd);
		w1_netlink_check_send(node->block);

		w1_netlink_queue_status(node->block, node->msg, cmd, err);
		err = 0;

		len = माप(*cmd) + cmd->len;
		cmd = (काष्ठा w1_netlink_cmd *)((u8 *)cmd + len);
		mlen -= len;
	पूर्ण

	अगर (!cmd || err)
		w1_netlink_queue_status(node->block, node->msg, cmd, err);

	/* ref taken in w1_search_slave or w1_search_master_id when building
	 * the block
	 */
	अगर (sl)
		w1_unref_slave(sl);
	अन्यथा
		atomic_dec(&dev->refcnt);
	dev->priv = शून्य;
	mutex_unlock(&dev->bus_mutex);

	mutex_lock(&dev->list_mutex);
	list_del(&async_cmd->async_entry);
	mutex_unlock(&dev->list_mutex);

	w1_unref_block(node->block);
पूर्ण

अटल व्योम w1_list_count_cmds(काष्ठा w1_netlink_msg *msg, पूर्णांक *cmd_count,
	u16 *slave_len)
अणु
	काष्ठा w1_netlink_cmd *cmd = (काष्ठा w1_netlink_cmd *)msg->data;
	u16 mlen = msg->len;
	u16 len;
	पूर्णांक slave_list = 0;
	जबतक (mlen) अणु
		अगर (cmd->len + माप(काष्ठा w1_netlink_cmd) > mlen)
			अवरोध;

		चयन (cmd->cmd) अणु
		हाल W1_CMD_SEARCH:
		हाल W1_CMD_ALARM_SEARCH:
		हाल W1_CMD_LIST_SLAVES:
			++slave_list;
		पूर्ण
		++*cmd_count;
		len = माप(*cmd) + cmd->len;
		cmd = (काष्ठा w1_netlink_cmd *)((u8 *)cmd + len);
		mlen -= len;
	पूर्ण

	अगर (slave_list) अणु
		काष्ठा w1_master *dev = w1_search_master_id(msg->id.mst.id);
		अगर (dev) अणु
			/* Bytes, and likely an overstimate, and अगर it isn't
			 * the results can still be split between packets.
			 */
			*slave_len += माप(काष्ठा w1_reg_num) * slave_list *
				(dev->slave_count + dev->max_slave_count);
			/* search incremented it */
			atomic_dec(&dev->refcnt);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम w1_cn_callback(काष्ठा cn_msg *cn, काष्ठा netlink_skb_parms *nsp)
अणु
	काष्ठा w1_netlink_msg *msg = (काष्ठा w1_netlink_msg *)(cn + 1);
	काष्ठा w1_slave *sl;
	काष्ठा w1_master *dev;
	u16 msg_len;
	u16 slave_len = 0;
	पूर्णांक err = 0;
	काष्ठा w1_cb_block *block = शून्य;
	काष्ठा w1_cb_node *node = शून्य;
	पूर्णांक node_count = 0;
	पूर्णांक cmd_count = 0;

	/* If any unknown flag is set let the application know, that way
	 * applications can detect the असलence of features in kernels that
	 * करोn't know about them.  http://lwn.net/Articles/587527/
	 */
	अगर (cn->flags & ~(W1_CN_BUNDLE)) अणु
		w1_netlink_send_error(cn, msg, nsp->portid, -EINVAL);
		वापस;
	पूर्ण

	/* Count the number of master or slave commands there are to allocate
	 * space क्रम one cb_node each.
	 */
	msg_len = cn->len;
	जबतक (msg_len && !err) अणु
		अगर (msg->len + माप(काष्ठा w1_netlink_msg) > msg_len) अणु
			err = -E2BIG;
			अवरोध;
		पूर्ण

		/* count messages क्रम nodes and allocate any additional space
		 * required क्रम slave lists
		 */
		अगर (msg->type == W1_MASTER_CMD || msg->type == W1_SLAVE_CMD) अणु
			++node_count;
			w1_list_count_cmds(msg, &cmd_count, &slave_len);
		पूर्ण

		msg_len -= माप(काष्ठा w1_netlink_msg) + msg->len;
		msg = (काष्ठा w1_netlink_msg *)(((u8 *)msg) +
			माप(काष्ठा w1_netlink_msg) + msg->len);
	पूर्ण
	msg = (काष्ठा w1_netlink_msg *)(cn + 1);
	अगर (node_count) अणु
		पूर्णांक size;
		पूर्णांक reply_size = माप(*cn) + cn->len + slave_len;
		अगर (cn->flags & W1_CN_BUNDLE) अणु
			/* bundling duplicats some of the messages */
			reply_size += 2 * cmd_count * (माप(काष्ठा cn_msg) +
				माप(काष्ठा w1_netlink_msg) +
				माप(काष्ठा w1_netlink_cmd));
		पूर्ण
		reply_size = min(CONNECTOR_MAX_MSG_SIZE, reply_size);

		/* allocate space क्रम the block, a copy of the original message,
		 * one node per cmd to poपूर्णांक पूर्णांकo the original message,
		 * space क्रम replies which is the original message size plus
		 * space क्रम any list slave data and status messages
		 * cn->len करोesn't include itself which is part of the block
		 * */
		size =  /* block + original message */
			माप(काष्ठा w1_cb_block) + माप(*cn) + cn->len +
			/* space क्रम nodes */
			node_count * माप(काष्ठा w1_cb_node) +
			/* replies */
			माप(काष्ठा cn_msg) + reply_size;
		block = kzalloc(size, GFP_KERNEL);
		अगर (!block) अणु
			/* अगर the प्रणाली is alपढ़ोy out of memory,
			 * (A) will this work, and (B) would it be better
			 * to not try?
			 */
			w1_netlink_send_error(cn, msg, nsp->portid, -ENOMEM);
			वापस;
		पूर्ण
		atomic_set(&block->refcnt, 1);
		block->portid = nsp->portid;
		स_नकल(&block->request_cn, cn, माप(*cn) + cn->len);
		node = (काष्ठा w1_cb_node *)(block->request_cn.data + cn->len);

		/* Sneeky, when not bundling, reply_size is the allocated space
		 * required क्रम the reply, cn_msg isn't part of maxlen so
		 * it should be reply_size - माप(काष्ठा cn_msg), however
		 * when checking अगर there is enough space, w1_reply_make_space
		 * is called with the full message size including cn_msg,
		 * because it isn't known at that समय अगर an additional cn_msg
		 * will need to be allocated.  So an extra cn_msg is added
		 * above in "size".
		 */
		block->maxlen = reply_size;
		block->first_cn = (काष्ठा cn_msg *)(node + node_count);
		स_रखो(block->first_cn, 0, माप(*block->first_cn));
	पूर्ण

	msg_len = cn->len;
	जबतक (msg_len && !err) अणु

		dev = शून्य;
		sl = शून्य;

		अगर (msg->len + माप(काष्ठा w1_netlink_msg) > msg_len) अणु
			err = -E2BIG;
			अवरोध;
		पूर्ण

		/* execute on this thपढ़ो, no need to process later */
		अगर (msg->type == W1_LIST_MASTERS) अणु
			err = w1_process_command_root(cn, nsp->portid);
			जाओ out_cont;
		पूर्ण

		/* All following message types require additional data,
		 * check here beक्रमe references are taken.
		 */
		अगर (!msg->len) अणु
			err = -EPROTO;
			जाओ out_cont;
		पूर्ण

		/* both search calls take references */
		अगर (msg->type == W1_MASTER_CMD) अणु
			dev = w1_search_master_id(msg->id.mst.id);
		पूर्ण अन्यथा अगर (msg->type == W1_SLAVE_CMD) अणु
			sl = w1_search_slave((काष्ठा w1_reg_num *)msg->id.id);
			अगर (sl)
				dev = sl->master;
		पूर्ण अन्यथा अणु
			pr_notice("%s: cn: %x.%x, wrong type: %u, len: %u.\n",
				__func__, cn->id.idx, cn->id.val,
				msg->type, msg->len);
			err = -EPROTO;
			जाओ out_cont;
		पूर्ण

		अगर (!dev) अणु
			err = -ENODEV;
			जाओ out_cont;
		पूर्ण

		err = 0;

		atomic_inc(&block->refcnt);
		node->async.cb = w1_process_cb;
		node->block = block;
		node->msg = (काष्ठा w1_netlink_msg *)((u8 *)&block->request_cn +
			(माप_प्रकार)((u8 *)msg - (u8 *)cn));
		node->sl = sl;
		node->dev = dev;

		mutex_lock(&dev->list_mutex);
		list_add_tail(&node->async.async_entry, &dev->async_list);
		wake_up_process(dev->thपढ़ो);
		mutex_unlock(&dev->list_mutex);
		++node;

out_cont:
		/* Can't queue because that modअगरies block and another
		 * thपढ़ो could be processing the messages by now and
		 * there isn't a lock, send directly.
		 */
		अगर (err)
			w1_netlink_send_error(cn, msg, nsp->portid, err);
		msg_len -= माप(काष्ठा w1_netlink_msg) + msg->len;
		msg = (काष्ठा w1_netlink_msg *)(((u8 *)msg) +
			माप(काष्ठा w1_netlink_msg) + msg->len);

		/*
		 * Let's allow requests क्रम nonexisting devices.
		 */
		अगर (err == -ENODEV)
			err = 0;
	पूर्ण
	अगर (block)
		w1_unref_block(block);
पूर्ण

पूर्णांक w1_init_netlink(व्योम)
अणु
	काष्ठा cb_id w1_id = अणु.idx = CN_W1_IDX, .val = CN_W1_VALपूर्ण;

	वापस cn_add_callback(&w1_id, "w1", &w1_cn_callback);
पूर्ण

व्योम w1_fini_netlink(व्योम)
अणु
	काष्ठा cb_id w1_id = अणु.idx = CN_W1_IDX, .val = CN_W1_VALपूर्ण;

	cn_del_callback(&w1_id);
पूर्ण
#अन्यथा
व्योम w1_netlink_send(काष्ठा w1_master *dev, काष्ठा w1_netlink_msg *cn)
अणु
पूर्ण

पूर्णांक w1_init_netlink(व्योम)
अणु
	वापस 0;
पूर्ण

व्योम w1_fini_netlink(व्योम)
अणु
पूर्ण
#पूर्ण_अगर
