<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ssi_protocol.c
 *
 * Implementation of the SSI McSAAB improved protocol.
 *
 * Copyright (C) 2010 Nokia Corporation. All rights reserved.
 * Copyright (C) 2013 Sebastian Reichel <sre@kernel.org>
 *
 * Contact: Carlos Chinea <carlos.chinea@nokia.com>
 */

#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/अगर_phonet.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/hsi/hsi.h>
#समावेश <linux/hsi/ssi_protocol.h>

व्योम ssi_waketest(काष्ठा hsi_client *cl, अचिन्हित पूर्णांक enable);

#घोषणा SSIP_TXQUEUE_LEN	100
#घोषणा SSIP_MAX_MTU		65535
#घोषणा SSIP_DEFAULT_MTU	4000
#घोषणा PN_MEDIA_SOS		21
#घोषणा SSIP_MIN_PN_HDR		6	/* FIXME: Revisit */
#घोषणा SSIP_WDTOUT		2000	/* FIXME: has to be 500 msecs */
#घोषणा SSIP_KATOUT		15	/* 15 msecs */
#घोषणा SSIP_MAX_CMDS		5 /* Number of pre-allocated commands buffers */
#घोषणा SSIP_BYTES_TO_FRAMES(x) ((((x) - 1) >> 2) + 1)
#घोषणा SSIP_CMT_LOADER_SYNC	0x11223344
/*
 * SSI protocol command definitions
 */
#घोषणा SSIP_COMMAND(data)	((data) >> 28)
#घोषणा SSIP_PAYLOAD(data)	((data) & 0xfffffff)
/* Commands */
#घोषणा SSIP_SW_BREAK		0
#घोषणा SSIP_BOOTINFO_REQ	1
#घोषणा SSIP_BOOTINFO_RESP	2
#घोषणा SSIP_WAKETEST_RESULT	3
#घोषणा SSIP_START_TRANS	4
#घोषणा SSIP_READY		5
/* Payloads */
#घोषणा SSIP_DATA_VERSION(data)	((data) & 0xff)
#घोषणा SSIP_LOCAL_VERID	1
#घोषणा SSIP_WAKETEST_OK	0
#घोषणा SSIP_WAKETEST_FAILED	1
#घोषणा SSIP_PDU_LENGTH(data)	(((data) >> 8) & 0xffff)
#घोषणा SSIP_MSG_ID(data)	((data) & 0xff)
/* Generic Command */
#घोषणा SSIP_CMD(cmd, payload)	(((cmd) << 28) | ((payload) & 0xfffffff))
/* Commands क्रम the control channel */
#घोषणा SSIP_BOOTINFO_REQ_CMD(ver) \
		SSIP_CMD(SSIP_BOOTINFO_REQ, SSIP_DATA_VERSION(ver))
#घोषणा SSIP_BOOTINFO_RESP_CMD(ver) \
		SSIP_CMD(SSIP_BOOTINFO_RESP, SSIP_DATA_VERSION(ver))
#घोषणा SSIP_START_TRANS_CMD(pdulen, id) \
		SSIP_CMD(SSIP_START_TRANS, (((pdulen) << 8) | SSIP_MSG_ID(id)))
#घोषणा SSIP_READY_CMD		SSIP_CMD(SSIP_READY, 0)
#घोषणा SSIP_SWBREAK_CMD	SSIP_CMD(SSIP_SW_BREAK, 0)

#घोषणा SSIP_WAKETEST_FLAG 0

/* Main state machine states */
क्रमागत अणु
	INIT,
	HANDSHAKE,
	ACTIVE,
पूर्ण;

/* Send state machine states */
क्रमागत अणु
	SEND_IDLE,
	WAIT4READY,
	SEND_READY,
	SENDING,
	SENDING_SWBREAK,
पूर्ण;

/* Receive state machine states */
क्रमागत अणु
	RECV_IDLE,
	RECV_READY,
	RECEIVING,
पूर्ण;

/**
 * काष्ठा ssi_protocol - SSI protocol (McSAAB) data
 * @मुख्य_state: Main state machine
 * @send_state: TX state machine
 * @recv_state: RX state machine
 * @flags: Flags, currently only used to follow wake line test
 * @rxid: RX data id
 * @txid: TX data id
 * @txqueue_len: TX queue length
 * @tx_wd: TX watchकरोg
 * @rx_wd: RX watchकरोg
 * @keep_alive: Workaround क्रम SSI HW bug
 * @lock: To serialize access to this काष्ठा
 * @netdev: Phonet network device
 * @txqueue: TX data queue
 * @cmdqueue: Queue of मुक्त commands
 * @cl: HSI client own reference
 * @link: Link क्रम ssip_list
 * @tx_usecount: Refcount to keep track the slaves that use the wake line
 * @channel_id_cmd: HSI channel id क्रम command stream
 * @channel_id_data: HSI channel id क्रम data stream
 */
काष्ठा ssi_protocol अणु
	अचिन्हित पूर्णांक		मुख्य_state;
	अचिन्हित पूर्णांक		send_state;
	अचिन्हित पूर्णांक		recv_state;
	अचिन्हित दीर्घ		flags;
	u8			rxid;
	u8			txid;
	अचिन्हित पूर्णांक		txqueue_len;
	काष्ठा समयr_list	tx_wd;
	काष्ठा समयr_list	rx_wd;
	काष्ठा समयr_list	keep_alive; /* wake-up workaround */
	spinlock_t		lock;
	काष्ठा net_device	*netdev;
	काष्ठा list_head	txqueue;
	काष्ठा list_head	cmdqueue;
	काष्ठा work_काष्ठा	work;
	काष्ठा hsi_client	*cl;
	काष्ठा list_head	link;
	atomic_t		tx_usecnt;
	पूर्णांक			channel_id_cmd;
	पूर्णांक			channel_id_data;
पूर्ण;

/* List of ssi protocol instances */
अटल LIST_HEAD(ssip_list);

अटल व्योम ssip_rxcmd_complete(काष्ठा hsi_msg *msg);

अटल अंतरभूत व्योम ssip_set_cmd(काष्ठा hsi_msg *msg, u32 cmd)
अणु
	u32 *data;

	data = sg_virt(msg->sgt.sgl);
	*data = cmd;
पूर्ण

अटल अंतरभूत u32 ssip_get_cmd(काष्ठा hsi_msg *msg)
अणु
	u32 *data;

	data = sg_virt(msg->sgt.sgl);

	वापस *data;
पूर्ण

अटल व्योम ssip_skb_to_msg(काष्ठा sk_buff *skb, काष्ठा hsi_msg *msg)
अणु
	skb_frag_t *frag;
	काष्ठा scatterlist *sg;
	पूर्णांक i;

	BUG_ON(msg->sgt.nents != (अचिन्हित पूर्णांक)(skb_shinfo(skb)->nr_frags + 1));

	sg = msg->sgt.sgl;
	sg_set_buf(sg, skb->data, skb_headlen(skb));
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		sg = sg_next(sg);
		BUG_ON(!sg);
		frag = &skb_shinfo(skb)->frags[i];
		sg_set_page(sg, skb_frag_page(frag), skb_frag_size(frag),
				skb_frag_off(frag));
	पूर्ण
पूर्ण

अटल व्योम ssip_मुक्त_data(काष्ठा hsi_msg *msg)
अणु
	काष्ठा sk_buff *skb;

	skb = msg->context;
	pr_debug("free data: msg %p context %p skb %p\n", msg, msg->context,
								skb);
	msg->deकाष्ठाor = शून्य;
	dev_kमुक्त_skb(skb);
	hsi_मुक्त_msg(msg);
पूर्ण

अटल काष्ठा hsi_msg *ssip_alloc_data(काष्ठा ssi_protocol *ssi,
					काष्ठा sk_buff *skb, gfp_t flags)
अणु
	काष्ठा hsi_msg *msg;

	msg = hsi_alloc_msg(skb_shinfo(skb)->nr_frags + 1, flags);
	अगर (!msg)
		वापस शून्य;
	ssip_skb_to_msg(skb, msg);
	msg->deकाष्ठाor = ssip_मुक्त_data;
	msg->channel = ssi->channel_id_data;
	msg->context = skb;

	वापस msg;
पूर्ण

अटल अंतरभूत व्योम ssip_release_cmd(काष्ठा hsi_msg *msg)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(msg->cl);

	dev_dbg(&msg->cl->device, "Release cmd 0x%08x\n", ssip_get_cmd(msg));
	spin_lock_bh(&ssi->lock);
	list_add_tail(&msg->link, &ssi->cmdqueue);
	spin_unlock_bh(&ssi->lock);
पूर्ण

अटल काष्ठा hsi_msg *ssip_claim_cmd(काष्ठा ssi_protocol *ssi)
अणु
	काष्ठा hsi_msg *msg;

	BUG_ON(list_empty(&ssi->cmdqueue));

	spin_lock_bh(&ssi->lock);
	msg = list_first_entry(&ssi->cmdqueue, काष्ठा hsi_msg, link);
	list_del(&msg->link);
	spin_unlock_bh(&ssi->lock);
	msg->deकाष्ठाor = ssip_release_cmd;

	वापस msg;
पूर्ण

अटल व्योम ssip_मुक्त_cmds(काष्ठा ssi_protocol *ssi)
अणु
	काष्ठा hsi_msg *msg, *पंचांगp;

	list_क्रम_each_entry_safe(msg, पंचांगp, &ssi->cmdqueue, link) अणु
		list_del(&msg->link);
		msg->deकाष्ठाor = शून्य;
		kमुक्त(sg_virt(msg->sgt.sgl));
		hsi_मुक्त_msg(msg);
	पूर्ण
पूर्ण

अटल पूर्णांक ssip_alloc_cmds(काष्ठा ssi_protocol *ssi)
अणु
	काष्ठा hsi_msg *msg;
	u32 *buf;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < SSIP_MAX_CMDS; i++) अणु
		msg = hsi_alloc_msg(1, GFP_KERNEL);
		अगर (!msg)
			जाओ out;
		buf = kदो_स्मृति(माप(*buf), GFP_KERNEL);
		अगर (!buf) अणु
			hsi_मुक्त_msg(msg);
			जाओ out;
		पूर्ण
		sg_init_one(msg->sgt.sgl, buf, माप(*buf));
		msg->channel = ssi->channel_id_cmd;
		list_add_tail(&msg->link, &ssi->cmdqueue);
	पूर्ण

	वापस 0;
out:
	ssip_मुक्त_cmds(ssi);

	वापस -ENOMEM;
पूर्ण

अटल व्योम ssip_set_rxstate(काष्ठा ssi_protocol *ssi, अचिन्हित पूर्णांक state)
अणु
	ssi->recv_state = state;
	चयन (state) अणु
	हाल RECV_IDLE:
		del_समयr(&ssi->rx_wd);
		अगर (ssi->send_state == SEND_IDLE)
			del_समयr(&ssi->keep_alive);
		अवरोध;
	हाल RECV_READY:
		/* CMT speech workaround */
		अगर (atomic_पढ़ो(&ssi->tx_usecnt))
			अवरोध;
		fallthrough;
	हाल RECEIVING:
		mod_समयr(&ssi->keep_alive, jअगरfies +
						msecs_to_jअगरfies(SSIP_KATOUT));
		mod_समयr(&ssi->rx_wd, jअगरfies + msecs_to_jअगरfies(SSIP_WDTOUT));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ssip_set_txstate(काष्ठा ssi_protocol *ssi, अचिन्हित पूर्णांक state)
अणु
	ssi->send_state = state;
	चयन (state) अणु
	हाल SEND_IDLE:
	हाल SEND_READY:
		del_समयr(&ssi->tx_wd);
		अगर (ssi->recv_state == RECV_IDLE)
			del_समयr(&ssi->keep_alive);
		अवरोध;
	हाल WAIT4READY:
	हाल SENDING:
	हाल SENDING_SWBREAK:
		mod_समयr(&ssi->keep_alive,
				jअगरfies + msecs_to_jअगरfies(SSIP_KATOUT));
		mod_समयr(&ssi->tx_wd, jअगरfies + msecs_to_jअगरfies(SSIP_WDTOUT));
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

काष्ठा hsi_client *ssip_slave_get_master(काष्ठा hsi_client *slave)
अणु
	काष्ठा hsi_client *master = ERR_PTR(-ENODEV);
	काष्ठा ssi_protocol *ssi;

	list_क्रम_each_entry(ssi, &ssip_list, link)
		अगर (slave->device.parent == ssi->cl->device.parent) अणु
			master = ssi->cl;
			अवरोध;
		पूर्ण

	वापस master;
पूर्ण
EXPORT_SYMBOL_GPL(ssip_slave_get_master);

पूर्णांक ssip_slave_start_tx(काष्ठा hsi_client *master)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(master);

	dev_dbg(&master->device, "start TX %d\n", atomic_पढ़ो(&ssi->tx_usecnt));
	spin_lock_bh(&ssi->lock);
	अगर (ssi->send_state == SEND_IDLE) अणु
		ssip_set_txstate(ssi, WAIT4READY);
		hsi_start_tx(master);
	पूर्ण
	spin_unlock_bh(&ssi->lock);
	atomic_inc(&ssi->tx_usecnt);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ssip_slave_start_tx);

पूर्णांक ssip_slave_stop_tx(काष्ठा hsi_client *master)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(master);

	WARN_ON_ONCE(atomic_पढ़ो(&ssi->tx_usecnt) == 0);

	अगर (atomic_dec_and_test(&ssi->tx_usecnt)) अणु
		spin_lock_bh(&ssi->lock);
		अगर ((ssi->send_state == SEND_READY) ||
			(ssi->send_state == WAIT4READY)) अणु
			ssip_set_txstate(ssi, SEND_IDLE);
			hsi_stop_tx(master);
		पूर्ण
		spin_unlock_bh(&ssi->lock);
	पूर्ण
	dev_dbg(&master->device, "stop TX %d\n", atomic_पढ़ो(&ssi->tx_usecnt));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ssip_slave_stop_tx);

पूर्णांक ssip_slave_running(काष्ठा hsi_client *master)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(master);
	वापस netअगर_running(ssi->netdev);
पूर्ण
EXPORT_SYMBOL_GPL(ssip_slave_running);

अटल व्योम ssip_reset(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा list_head *head, *पंचांगp;
	काष्ठा hsi_msg *msg;

	अगर (netअगर_running(ssi->netdev))
		netअगर_carrier_off(ssi->netdev);
	hsi_flush(cl);
	spin_lock_bh(&ssi->lock);
	अगर (ssi->send_state != SEND_IDLE)
		hsi_stop_tx(cl);
	spin_unlock_bh(&ssi->lock);
	अगर (test_and_clear_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
		ssi_waketest(cl, 0); /* FIXME: To be हटाओd */
	spin_lock_bh(&ssi->lock);
	del_समयr(&ssi->rx_wd);
	del_समयr(&ssi->tx_wd);
	del_समयr(&ssi->keep_alive);
	ssi->मुख्य_state = 0;
	ssi->send_state = 0;
	ssi->recv_state = 0;
	ssi->flags = 0;
	ssi->rxid = 0;
	ssi->txid = 0;
	list_क्रम_each_safe(head, पंचांगp, &ssi->txqueue) अणु
		msg = list_entry(head, काष्ठा hsi_msg, link);
		dev_dbg(&cl->device, "Pending TX data\n");
		list_del(head);
		ssip_मुक्त_data(msg);
	पूर्ण
	ssi->txqueue_len = 0;
	spin_unlock_bh(&ssi->lock);
पूर्ण

अटल व्योम ssip_dump_state(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;

	spin_lock_bh(&ssi->lock);
	dev_err(&cl->device, "Main state: %d\n", ssi->मुख्य_state);
	dev_err(&cl->device, "Recv state: %d\n", ssi->recv_state);
	dev_err(&cl->device, "Send state: %d\n", ssi->send_state);
	dev_err(&cl->device, "CMT %s\n", (ssi->मुख्य_state == ACTIVE) ?
							"Online" : "Offline");
	dev_err(&cl->device, "Wake test %d\n",
				test_bit(SSIP_WAKETEST_FLAG, &ssi->flags));
	dev_err(&cl->device, "Data RX id: %d\n", ssi->rxid);
	dev_err(&cl->device, "Data TX id: %d\n", ssi->txid);

	list_क्रम_each_entry(msg, &ssi->txqueue, link)
		dev_err(&cl->device, "pending TX data (%p)\n", msg);
	spin_unlock_bh(&ssi->lock);
पूर्ण

अटल व्योम ssip_error(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;

	ssip_dump_state(cl);
	ssip_reset(cl);
	msg = ssip_claim_cmd(ssi);
	msg->complete = ssip_rxcmd_complete;
	hsi_async_पढ़ो(cl, msg);
पूर्ण

अटल व्योम ssip_keep_alive(काष्ठा समयr_list *t)
अणु
	काष्ठा ssi_protocol *ssi = from_समयr(ssi, t, keep_alive);
	काष्ठा hsi_client *cl = ssi->cl;

	dev_dbg(&cl->device, "Keep alive kick in: m(%d) r(%d) s(%d)\n",
		ssi->मुख्य_state, ssi->recv_state, ssi->send_state);

	spin_lock(&ssi->lock);
	अगर (ssi->recv_state == RECV_IDLE)
		चयन (ssi->send_state) अणु
		हाल SEND_READY:
			अगर (atomic_पढ़ो(&ssi->tx_usecnt) == 0)
				अवरोध;
			fallthrough;
			/*
			 * Workaround क्रम cmt-speech in that हाल
			 * we relay on audio समयrs.
			 */
		हाल SEND_IDLE:
			spin_unlock(&ssi->lock);
			वापस;
		पूर्ण
	mod_समयr(&ssi->keep_alive, jअगरfies + msecs_to_jअगरfies(SSIP_KATOUT));
	spin_unlock(&ssi->lock);
पूर्ण

अटल व्योम ssip_rx_wd(काष्ठा समयr_list *t)
अणु
	काष्ठा ssi_protocol *ssi = from_समयr(ssi, t, rx_wd);
	काष्ठा hsi_client *cl = ssi->cl;

	dev_err(&cl->device, "Watchdog triggered\n");
	ssip_error(cl);
पूर्ण

अटल व्योम ssip_tx_wd(काष्ठा समयr_list *t)
अणु
	काष्ठा ssi_protocol *ssi = from_समयr(ssi, t, tx_wd);
	काष्ठा hsi_client *cl = ssi->cl;

	dev_err(&cl->device, "Watchdog triggered\n");
	ssip_error(cl);
पूर्ण

अटल व्योम ssip_send_bootinfo_req_cmd(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;

	dev_dbg(&cl->device, "Issuing BOOT INFO REQ command\n");
	msg = ssip_claim_cmd(ssi);
	ssip_set_cmd(msg, SSIP_BOOTINFO_REQ_CMD(SSIP_LOCAL_VERID));
	msg->complete = ssip_release_cmd;
	hsi_async_ग_लिखो(cl, msg);
	dev_dbg(&cl->device, "Issuing RX command\n");
	msg = ssip_claim_cmd(ssi);
	msg->complete = ssip_rxcmd_complete;
	hsi_async_पढ़ो(cl, msg);
पूर्ण

अटल व्योम ssip_start_rx(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;

	dev_dbg(&cl->device, "RX start M(%d) R(%d)\n", ssi->मुख्य_state,
						ssi->recv_state);
	spin_lock_bh(&ssi->lock);
	/*
	 * We can have two UP events in a row due to a लघु low
	 * high transition. Thereक्रमe we need to ignore the sencond UP event.
	 */
	अगर ((ssi->मुख्य_state != ACTIVE) || (ssi->recv_state == RECV_READY)) अणु
		spin_unlock_bh(&ssi->lock);
		वापस;
	पूर्ण
	ssip_set_rxstate(ssi, RECV_READY);
	spin_unlock_bh(&ssi->lock);

	msg = ssip_claim_cmd(ssi);
	ssip_set_cmd(msg, SSIP_READY_CMD);
	msg->complete = ssip_release_cmd;
	dev_dbg(&cl->device, "Send READY\n");
	hsi_async_ग_लिखो(cl, msg);
पूर्ण

अटल व्योम ssip_stop_rx(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);

	dev_dbg(&cl->device, "RX stop M(%d)\n", ssi->मुख्य_state);
	spin_lock_bh(&ssi->lock);
	अगर (likely(ssi->मुख्य_state == ACTIVE))
		ssip_set_rxstate(ssi, RECV_IDLE);
	spin_unlock_bh(&ssi->lock);
पूर्ण

अटल व्योम ssip_मुक्त_strans(काष्ठा hsi_msg *msg)
अणु
	ssip_मुक्त_data(msg->context);
	ssip_release_cmd(msg);
पूर्ण

अटल व्योम ssip_strans_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_client *cl = msg->cl;
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *data;

	data = msg->context;
	ssip_release_cmd(msg);
	spin_lock_bh(&ssi->lock);
	ssip_set_txstate(ssi, SENDING);
	spin_unlock_bh(&ssi->lock);
	hsi_async_ग_लिखो(cl, data);
पूर्ण

अटल पूर्णांक ssip_xmit(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg, *dmsg;
	काष्ठा sk_buff *skb;

	spin_lock_bh(&ssi->lock);
	अगर (list_empty(&ssi->txqueue)) अणु
		spin_unlock_bh(&ssi->lock);
		वापस 0;
	पूर्ण
	dmsg = list_first_entry(&ssi->txqueue, काष्ठा hsi_msg, link);
	list_del(&dmsg->link);
	ssi->txqueue_len--;
	spin_unlock_bh(&ssi->lock);

	msg = ssip_claim_cmd(ssi);
	skb = dmsg->context;
	msg->context = dmsg;
	msg->complete = ssip_strans_complete;
	msg->deकाष्ठाor = ssip_मुक्त_strans;

	spin_lock_bh(&ssi->lock);
	ssip_set_cmd(msg, SSIP_START_TRANS_CMD(SSIP_BYTES_TO_FRAMES(skb->len),
								ssi->txid));
	ssi->txid++;
	ssip_set_txstate(ssi, SENDING);
	spin_unlock_bh(&ssi->lock);

	dev_dbg(&cl->device, "Send STRANS (%d frames)\n",
						SSIP_BYTES_TO_FRAMES(skb->len));

	वापस hsi_async_ग_लिखो(cl, msg);
पूर्ण

/* In soft IRQ context */
अटल व्योम ssip_pn_rx(काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device *dev = skb->dev;

	अगर (unlikely(!netअगर_running(dev))) अणु
		dev_dbg(&dev->dev, "Drop RX packet\n");
		dev->stats.rx_dropped++;
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण
	अगर (unlikely(!pskb_may_pull(skb, SSIP_MIN_PN_HDR))) अणु
		dev_dbg(&dev->dev, "Error drop RX packet\n");
		dev->stats.rx_errors++;
		dev->stats.rx_length_errors++;
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण
	dev->stats.rx_packets++;
	dev->stats.rx_bytes += skb->len;

	/* length field is exchanged in network byte order */
	((u16 *)skb->data)[2] = ntohs(((u16 *)skb->data)[2]);
	dev_dbg(&dev->dev, "RX length fixed (%04x -> %u)\n",
			((u16 *)skb->data)[2], ntohs(((u16 *)skb->data)[2]));

	skb->protocol = htons(ETH_P_PHONET);
	skb_reset_mac_header(skb);
	__skb_pull(skb, 1);
	netअगर_rx(skb);
पूर्ण

अटल व्योम ssip_rx_data_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_client *cl = msg->cl;
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा sk_buff *skb;

	अगर (msg->status == HSI_STATUS_ERROR) अणु
		dev_err(&cl->device, "RX data error\n");
		ssip_मुक्त_data(msg);
		ssip_error(cl);
		वापस;
	पूर्ण
	del_समयr(&ssi->rx_wd); /* FIXME: Revisit */
	skb = msg->context;
	ssip_pn_rx(skb);
	hsi_मुक्त_msg(msg);
पूर्ण

अटल व्योम ssip_rx_bootinक्रमeq(काष्ठा hsi_client *cl, u32 cmd)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;

	/* Workaroud: Ignore CMT Loader message leftover */
	अगर (cmd == SSIP_CMT_LOADER_SYNC)
		वापस;

	चयन (ssi->मुख्य_state) अणु
	हाल ACTIVE:
		dev_err(&cl->device, "Boot info req on active state\n");
		ssip_error(cl);
		fallthrough;
	हाल INIT:
	हाल HANDSHAKE:
		spin_lock_bh(&ssi->lock);
		ssi->मुख्य_state = HANDSHAKE;
		spin_unlock_bh(&ssi->lock);

		अगर (!test_and_set_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
			ssi_waketest(cl, 1); /* FIXME: To be हटाओd */

		spin_lock_bh(&ssi->lock);
		/* Start boot handshake watchकरोg */
		mod_समयr(&ssi->tx_wd, jअगरfies + msecs_to_jअगरfies(SSIP_WDTOUT));
		spin_unlock_bh(&ssi->lock);
		dev_dbg(&cl->device, "Send BOOTINFO_RESP\n");
		अगर (SSIP_DATA_VERSION(cmd) != SSIP_LOCAL_VERID)
			dev_warn(&cl->device, "boot info req verid mismatch\n");
		msg = ssip_claim_cmd(ssi);
		ssip_set_cmd(msg, SSIP_BOOTINFO_RESP_CMD(SSIP_LOCAL_VERID));
		msg->complete = ssip_release_cmd;
		hsi_async_ग_लिखो(cl, msg);
		अवरोध;
	शेष:
		dev_dbg(&cl->device, "Wrong state M(%d)\n", ssi->मुख्य_state);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ssip_rx_bootinक्रमesp(काष्ठा hsi_client *cl, u32 cmd)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);

	अगर (SSIP_DATA_VERSION(cmd) != SSIP_LOCAL_VERID)
		dev_warn(&cl->device, "boot info resp verid mismatch\n");

	spin_lock_bh(&ssi->lock);
	अगर (ssi->मुख्य_state != ACTIVE)
		/* Use tx_wd as a boot watchकरोg in non ACTIVE state */
		mod_समयr(&ssi->tx_wd, jअगरfies + msecs_to_jअगरfies(SSIP_WDTOUT));
	अन्यथा
		dev_dbg(&cl->device, "boot info resp ignored M(%d)\n",
							ssi->मुख्य_state);
	spin_unlock_bh(&ssi->lock);
पूर्ण

अटल व्योम ssip_rx_waketest(काष्ठा hsi_client *cl, u32 cmd)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	अचिन्हित पूर्णांक wkres = SSIP_PAYLOAD(cmd);

	spin_lock_bh(&ssi->lock);
	अगर (ssi->मुख्य_state != HANDSHAKE) अणु
		dev_dbg(&cl->device, "wake lines test ignored M(%d)\n",
							ssi->मुख्य_state);
		spin_unlock_bh(&ssi->lock);
		वापस;
	पूर्ण
	spin_unlock_bh(&ssi->lock);

	अगर (test_and_clear_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
		ssi_waketest(cl, 0); /* FIXME: To be हटाओd */

	spin_lock_bh(&ssi->lock);
	ssi->मुख्य_state = ACTIVE;
	del_समयr(&ssi->tx_wd); /* Stop boot handshake समयr */
	spin_unlock_bh(&ssi->lock);

	dev_notice(&cl->device, "WAKELINES TEST %s\n",
				wkres & SSIP_WAKETEST_FAILED ? "FAILED" : "OK");
	अगर (wkres & SSIP_WAKETEST_FAILED) अणु
		ssip_error(cl);
		वापस;
	पूर्ण
	dev_dbg(&cl->device, "CMT is ONLINE\n");
	netअगर_wake_queue(ssi->netdev);
	netअगर_carrier_on(ssi->netdev);
पूर्ण

अटल व्योम ssip_rx_पढ़ोy(काष्ठा hsi_client *cl)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);

	spin_lock_bh(&ssi->lock);
	अगर (unlikely(ssi->मुख्य_state != ACTIVE)) अणु
		dev_dbg(&cl->device, "READY on wrong state: S(%d) M(%d)\n",
					ssi->send_state, ssi->मुख्य_state);
		spin_unlock_bh(&ssi->lock);
		वापस;
	पूर्ण
	अगर (ssi->send_state != WAIT4READY) अणु
		dev_dbg(&cl->device, "Ignore spurious READY command\n");
		spin_unlock_bh(&ssi->lock);
		वापस;
	पूर्ण
	ssip_set_txstate(ssi, SEND_READY);
	spin_unlock_bh(&ssi->lock);
	ssip_xmit(cl);
पूर्ण

अटल व्योम ssip_rx_strans(काष्ठा hsi_client *cl, u32 cmd)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा sk_buff *skb;
	काष्ठा hsi_msg *msg;
	पूर्णांक len = SSIP_PDU_LENGTH(cmd);

	dev_dbg(&cl->device, "RX strans: %d frames\n", len);
	spin_lock_bh(&ssi->lock);
	अगर (unlikely(ssi->मुख्य_state != ACTIVE)) अणु
		dev_err(&cl->device, "START TRANS wrong state: S(%d) M(%d)\n",
					ssi->send_state, ssi->मुख्य_state);
		spin_unlock_bh(&ssi->lock);
		वापस;
	पूर्ण
	ssip_set_rxstate(ssi, RECEIVING);
	अगर (unlikely(SSIP_MSG_ID(cmd) != ssi->rxid)) अणु
		dev_err(&cl->device, "START TRANS id %d expected %d\n",
					SSIP_MSG_ID(cmd), ssi->rxid);
		spin_unlock_bh(&ssi->lock);
		जाओ out1;
	पूर्ण
	ssi->rxid++;
	spin_unlock_bh(&ssi->lock);
	skb = netdev_alloc_skb(ssi->netdev, len * 4);
	अगर (unlikely(!skb)) अणु
		dev_err(&cl->device, "No memory for rx skb\n");
		जाओ out1;
	पूर्ण
	skb->dev = ssi->netdev;
	skb_put(skb, len * 4);
	msg = ssip_alloc_data(ssi, skb, GFP_ATOMIC);
	अगर (unlikely(!msg)) अणु
		dev_err(&cl->device, "No memory for RX data msg\n");
		जाओ out2;
	पूर्ण
	msg->complete = ssip_rx_data_complete;
	hsi_async_पढ़ो(cl, msg);

	वापस;
out2:
	dev_kमुक्त_skb(skb);
out1:
	ssip_error(cl);
पूर्ण

अटल व्योम ssip_rxcmd_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_client *cl = msg->cl;
	u32 cmd = ssip_get_cmd(msg);
	अचिन्हित पूर्णांक cmdid = SSIP_COMMAND(cmd);

	अगर (msg->status == HSI_STATUS_ERROR) अणु
		dev_err(&cl->device, "RX error detected\n");
		ssip_release_cmd(msg);
		ssip_error(cl);
		वापस;
	पूर्ण
	hsi_async_पढ़ो(cl, msg);
	dev_dbg(&cl->device, "RX cmd: 0x%08x\n", cmd);
	चयन (cmdid) अणु
	हाल SSIP_SW_BREAK:
		/* Ignored */
		अवरोध;
	हाल SSIP_BOOTINFO_REQ:
		ssip_rx_bootinक्रमeq(cl, cmd);
		अवरोध;
	हाल SSIP_BOOTINFO_RESP:
		ssip_rx_bootinक्रमesp(cl, cmd);
		अवरोध;
	हाल SSIP_WAKETEST_RESULT:
		ssip_rx_waketest(cl, cmd);
		अवरोध;
	हाल SSIP_START_TRANS:
		ssip_rx_strans(cl, cmd);
		अवरोध;
	हाल SSIP_READY:
		ssip_rx_पढ़ोy(cl);
		अवरोध;
	शेष:
		dev_warn(&cl->device, "command 0x%08x not supported\n", cmd);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ssip_swअवरोध_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_client *cl = msg->cl;
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);

	ssip_release_cmd(msg);
	spin_lock_bh(&ssi->lock);
	अगर (list_empty(&ssi->txqueue)) अणु
		अगर (atomic_पढ़ो(&ssi->tx_usecnt)) अणु
			ssip_set_txstate(ssi, SEND_READY);
		पूर्ण अन्यथा अणु
			ssip_set_txstate(ssi, SEND_IDLE);
			hsi_stop_tx(cl);
		पूर्ण
		spin_unlock_bh(&ssi->lock);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&ssi->lock);
		ssip_xmit(cl);
	पूर्ण
	netअगर_wake_queue(ssi->netdev);
पूर्ण

अटल व्योम ssip_tx_data_complete(काष्ठा hsi_msg *msg)
अणु
	काष्ठा hsi_client *cl = msg->cl;
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *cmsg;

	अगर (msg->status == HSI_STATUS_ERROR) अणु
		dev_err(&cl->device, "TX data error\n");
		ssip_error(cl);
		जाओ out;
	पूर्ण
	spin_lock_bh(&ssi->lock);
	अगर (list_empty(&ssi->txqueue)) अणु
		ssip_set_txstate(ssi, SENDING_SWBREAK);
		spin_unlock_bh(&ssi->lock);
		cmsg = ssip_claim_cmd(ssi);
		ssip_set_cmd(cmsg, SSIP_SWBREAK_CMD);
		cmsg->complete = ssip_swअवरोध_complete;
		dev_dbg(&cl->device, "Send SWBREAK\n");
		hsi_async_ग_लिखो(cl, cmsg);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&ssi->lock);
		ssip_xmit(cl);
	पूर्ण
out:
	ssip_मुक्त_data(msg);
पूर्ण

अटल व्योम ssip_port_event(काष्ठा hsi_client *cl, अचिन्हित दीर्घ event)
अणु
	चयन (event) अणु
	हाल HSI_EVENT_START_RX:
		ssip_start_rx(cl);
		अवरोध;
	हाल HSI_EVENT_STOP_RX:
		ssip_stop_rx(cl);
		अवरोध;
	शेष:
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक ssip_pn_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा hsi_client *cl = to_hsi_client(dev->dev.parent);
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	पूर्णांक err;

	err = hsi_claim_port(cl, 1);
	अगर (err < 0) अणु
		dev_err(&cl->device, "SSI port already claimed\n");
		वापस err;
	पूर्ण
	err = hsi_रेजिस्टर_port_event(cl, ssip_port_event);
	अगर (err < 0) अणु
		dev_err(&cl->device, "Register HSI port event failed (%d)\n",
			err);
		वापस err;
	पूर्ण
	dev_dbg(&cl->device, "Configuring SSI port\n");
	hsi_setup(cl);

	अगर (!test_and_set_bit(SSIP_WAKETEST_FLAG, &ssi->flags))
		ssi_waketest(cl, 1); /* FIXME: To be हटाओd */

	spin_lock_bh(&ssi->lock);
	ssi->मुख्य_state = HANDSHAKE;
	spin_unlock_bh(&ssi->lock);

	ssip_send_bootinfo_req_cmd(cl);

	वापस 0;
पूर्ण

अटल पूर्णांक ssip_pn_stop(काष्ठा net_device *dev)
अणु
	काष्ठा hsi_client *cl = to_hsi_client(dev->dev.parent);

	ssip_reset(cl);
	hsi_unरेजिस्टर_port_event(cl);
	hsi_release_port(cl);

	वापस 0;
पूर्ण

अटल व्योम ssip_xmit_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ssi_protocol *ssi =
				container_of(work, काष्ठा ssi_protocol, work);
	काष्ठा hsi_client *cl = ssi->cl;

	ssip_xmit(cl);
पूर्ण

अटल पूर्णांक ssip_pn_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा hsi_client *cl = to_hsi_client(dev->dev.parent);
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);
	काष्ठा hsi_msg *msg;

	अगर ((skb->protocol != htons(ETH_P_PHONET)) ||
					(skb->len < SSIP_MIN_PN_HDR))
		जाओ drop;
	/* Pad to 32-bits - FIXME: Revisit*/
	अगर ((skb->len & 3) && skb_pad(skb, 4 - (skb->len & 3)))
		जाओ inc_dropped;

	/*
	 * Modem sends Phonet messages over SSI with its own endianness.
	 * Assume that modem has the same endianness as we करो.
	 */
	अगर (skb_cow_head(skb, 0))
		जाओ drop;

	/* length field is exchanged in network byte order */
	((u16 *)skb->data)[2] = htons(((u16 *)skb->data)[2]);

	msg = ssip_alloc_data(ssi, skb, GFP_ATOMIC);
	अगर (!msg) अणु
		dev_dbg(&cl->device, "Dropping tx data: No memory\n");
		जाओ drop;
	पूर्ण
	msg->complete = ssip_tx_data_complete;

	spin_lock_bh(&ssi->lock);
	अगर (unlikely(ssi->मुख्य_state != ACTIVE)) अणु
		spin_unlock_bh(&ssi->lock);
		dev_dbg(&cl->device, "Dropping tx data: CMT is OFFLINE\n");
		जाओ drop2;
	पूर्ण
	list_add_tail(&msg->link, &ssi->txqueue);
	ssi->txqueue_len++;
	अगर (dev->tx_queue_len < ssi->txqueue_len) अणु
		dev_info(&cl->device, "TX queue full %d\n", ssi->txqueue_len);
		netअगर_stop_queue(dev);
	पूर्ण
	अगर (ssi->send_state == SEND_IDLE) अणु
		ssip_set_txstate(ssi, WAIT4READY);
		spin_unlock_bh(&ssi->lock);
		dev_dbg(&cl->device, "Start TX qlen %d\n", ssi->txqueue_len);
		hsi_start_tx(cl);
	पूर्ण अन्यथा अगर (ssi->send_state == SEND_READY) अणु
		/* Needed क्रम cmt-speech workaround */
		dev_dbg(&cl->device, "Start TX on SEND READY qlen %d\n",
							ssi->txqueue_len);
		spin_unlock_bh(&ssi->lock);
		schedule_work(&ssi->work);
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&ssi->lock);
	पूर्ण
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += skb->len;

	वापस 0;
drop2:
	hsi_मुक्त_msg(msg);
drop:
	dev_kमुक्त_skb(skb);
inc_dropped:
	dev->stats.tx_dropped++;

	वापस 0;
पूर्ण

/* CMT reset event handler */
व्योम ssip_reset_event(काष्ठा hsi_client *master)
अणु
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(master);
	dev_err(&ssi->cl->device, "CMT reset detected!\n");
	ssip_error(ssi->cl);
पूर्ण
EXPORT_SYMBOL_GPL(ssip_reset_event);

अटल स्थिर काष्ठा net_device_ops ssip_pn_ops = अणु
	.nकरो_खोलो	= ssip_pn_खोलो,
	.nकरो_stop	= ssip_pn_stop,
	.nकरो_start_xmit	= ssip_pn_xmit,
पूर्ण;

अटल व्योम ssip_pn_setup(काष्ठा net_device *dev)
अणु
	dev->features		= 0;
	dev->netdev_ops		= &ssip_pn_ops;
	dev->type		= ARPHRD_PHONET;
	dev->flags		= IFF_POINTOPOINT | IFF_NOARP;
	dev->mtu		= SSIP_DEFAULT_MTU;
	dev->hard_header_len	= 1;
	dev->dev_addr[0]	= PN_MEDIA_SOS;
	dev->addr_len		= 1;
	dev->tx_queue_len	= SSIP_TXQUEUE_LEN;

	dev->needs_मुक्त_netdev	= true;
	dev->header_ops		= &phonet_header_ops;
पूर्ण

अटल पूर्णांक ssi_protocol_probe(काष्ठा device *dev)
अणु
	अटल स्थिर अक्षर अगरname[] = "phonet%d";
	काष्ठा hsi_client *cl = to_hsi_client(dev);
	काष्ठा ssi_protocol *ssi;
	पूर्णांक err;

	ssi = kzalloc(माप(*ssi), GFP_KERNEL);
	अगर (!ssi)
		वापस -ENOMEM;

	spin_lock_init(&ssi->lock);
	समयr_setup(&ssi->rx_wd, ssip_rx_wd, TIMER_DEFERRABLE);
	समयr_setup(&ssi->tx_wd, ssip_tx_wd, TIMER_DEFERRABLE);
	समयr_setup(&ssi->keep_alive, ssip_keep_alive, 0);
	INIT_LIST_HEAD(&ssi->txqueue);
	INIT_LIST_HEAD(&ssi->cmdqueue);
	atomic_set(&ssi->tx_usecnt, 0);
	hsi_client_set_drvdata(cl, ssi);
	ssi->cl = cl;
	INIT_WORK(&ssi->work, ssip_xmit_work);

	ssi->channel_id_cmd = hsi_get_channel_id_by_name(cl, "mcsaab-control");
	अगर (ssi->channel_id_cmd < 0) अणु
		err = ssi->channel_id_cmd;
		dev_err(dev, "Could not get cmd channel (%d)\n", err);
		जाओ out;
	पूर्ण

	ssi->channel_id_data = hsi_get_channel_id_by_name(cl, "mcsaab-data");
	अगर (ssi->channel_id_data < 0) अणु
		err = ssi->channel_id_data;
		dev_err(dev, "Could not get data channel (%d)\n", err);
		जाओ out;
	पूर्ण

	err = ssip_alloc_cmds(ssi);
	अगर (err < 0) अणु
		dev_err(dev, "No memory for commands\n");
		जाओ out;
	पूर्ण

	ssi->netdev = alloc_netdev(0, अगरname, NET_NAME_UNKNOWN, ssip_pn_setup);
	अगर (!ssi->netdev) अणु
		dev_err(dev, "No memory for netdev\n");
		err = -ENOMEM;
		जाओ out1;
	पूर्ण

	/* MTU range: 6 - 65535 */
	ssi->netdev->min_mtu = PHONET_MIN_MTU;
	ssi->netdev->max_mtu = SSIP_MAX_MTU;

	SET_NETDEV_DEV(ssi->netdev, dev);
	netअगर_carrier_off(ssi->netdev);
	err = रेजिस्टर_netdev(ssi->netdev);
	अगर (err < 0) अणु
		dev_err(dev, "Register netdev failed (%d)\n", err);
		जाओ out2;
	पूर्ण

	list_add(&ssi->link, &ssip_list);

	dev_dbg(dev, "channel configuration: cmd=%d, data=%d\n",
		ssi->channel_id_cmd, ssi->channel_id_data);

	वापस 0;
out2:
	मुक्त_netdev(ssi->netdev);
out1:
	ssip_मुक्त_cmds(ssi);
out:
	kमुक्त(ssi);

	वापस err;
पूर्ण

अटल पूर्णांक ssi_protocol_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा hsi_client *cl = to_hsi_client(dev);
	काष्ठा ssi_protocol *ssi = hsi_client_drvdata(cl);

	list_del(&ssi->link);
	unरेजिस्टर_netdev(ssi->netdev);
	ssip_मुक्त_cmds(ssi);
	hsi_client_set_drvdata(cl, शून्य);
	kमुक्त(ssi);

	वापस 0;
पूर्ण

अटल काष्ठा hsi_client_driver ssip_driver = अणु
	.driver = अणु
		.name	= "ssi-protocol",
		.owner	= THIS_MODULE,
		.probe	= ssi_protocol_probe,
		.हटाओ	= ssi_protocol_हटाओ,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init ssip_init(व्योम)
अणु
	pr_info("SSI protocol aka McSAAB added\n");

	वापस hsi_रेजिस्टर_client_driver(&ssip_driver);
पूर्ण
module_init(ssip_init);

अटल व्योम __निकास ssip_निकास(व्योम)
अणु
	hsi_unरेजिस्टर_client_driver(&ssip_driver);
	pr_info("SSI protocol driver removed\n");
पूर्ण
module_निकास(ssip_निकास);

MODULE_ALIAS("hsi:ssi-protocol");
MODULE_AUTHOR("Carlos Chinea <carlos.chinea@nokia.com>");
MODULE_AUTHOR("Remi Denis-Courmont <remi.denis-courmont@nokia.com>");
MODULE_DESCRIPTION("SSI protocol improved aka McSAAB");
MODULE_LICENSE("GPL");
