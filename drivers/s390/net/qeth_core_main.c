<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    Copyright IBM Corp. 2007, 2009
 *    Author(s): Utz Bacher <utz.bacher@de.ibm.com>,
 *		 Frank Pavlic <fpavlic@de.ibm.com>,
 *		 Thomas Spatzier <tspat@de.ibm.com>,
 *		 Frank Blaschka <frank.blaschka@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "qeth"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/compat.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/log2.h>
#समावेश <linux/पन.स>
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/mii.h>
#समावेश <linux/mm.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netdev_features.h>
#समावेश <linux/rcutree.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <net/iucv/af_iucv.h>
#समावेश <net/dsfield.h>
#समावेश <net/sock.h>

#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/sysinfo.h>
#समावेश <यंत्र/diag.h>
#समावेश <यंत्र/cपन.स>
#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/cpcmd.h>

#समावेश "qeth_core.h"

काष्ठा qeth_dbf_info qeth_dbf[QETH_DBF_INFOS] = अणु
	/* define dbf - Name, Pages, Areas, Maxlen, Level, View, Handle */
	/*                   N  P  A    M  L  V                      H  */
	[QETH_DBF_SETUP] = अणु"qeth_setup",
				8, 1,   8, 5, &debug_hex_ascii_view, शून्यपूर्ण,
	[QETH_DBF_MSG]	 = अणु"qeth_msg", 8, 1, 11 * माप(दीर्घ), 3,
			    &debug_प्र_लिखो_view, शून्यपूर्ण,
	[QETH_DBF_CTRL]  = अणु"qeth_control",
		8, 1, QETH_DBF_CTRL_LEN, 5, &debug_hex_ascii_view, शून्यपूर्ण,
पूर्ण;
EXPORT_SYMBOL_GPL(qeth_dbf);

काष्ठा kmem_cache *qeth_core_header_cache;
EXPORT_SYMBOL_GPL(qeth_core_header_cache);
अटल काष्ठा kmem_cache *qeth_qdio_outbuf_cache;

अटल काष्ठा device *qeth_core_root_dev;
अटल काष्ठा dentry *qeth_debugfs_root;
अटल काष्ठा lock_class_key qdio_out_skb_queue_key;

अटल व्योम qeth_issue_next_पढ़ो_cb(काष्ठा qeth_card *card,
				    काष्ठा qeth_cmd_buffer *iob,
				    अचिन्हित पूर्णांक data_length);
अटल पूर्णांक qeth_qdio_establish(काष्ठा qeth_card *);
अटल व्योम qeth_मुक्त_qdio_queues(काष्ठा qeth_card *card);
अटल व्योम qeth_notअगरy_skbs(काष्ठा qeth_qdio_out_q *queue,
		काष्ठा qeth_qdio_out_buffer *buf,
		क्रमागत iucv_tx_notअगरy notअगरication);

अटल व्योम qeth_बंद_dev_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_card *card;

	card = container_of(work, काष्ठा qeth_card, बंद_dev_work);
	QETH_CARD_TEXT(card, 2, "cldevhdl");
	ccwgroup_set_offline(card->gdev);
पूर्ण

अटल स्थिर अक्षर *qeth_get_cardname(काष्ठा qeth_card *card)
अणु
	अगर (IS_VM_NIC(card)) अणु
		चयन (card->info.type) अणु
		हाल QETH_CARD_TYPE_OSD:
			वापस " Virtual NIC QDIO";
		हाल QETH_CARD_TYPE_IQD:
			वापस " Virtual NIC Hiper";
		हाल QETH_CARD_TYPE_OSM:
			वापस " Virtual NIC QDIO - OSM";
		हाल QETH_CARD_TYPE_OSX:
			वापस " Virtual NIC QDIO - OSX";
		शेष:
			वापस " unknown";
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (card->info.type) अणु
		हाल QETH_CARD_TYPE_OSD:
			वापस " OSD Express";
		हाल QETH_CARD_TYPE_IQD:
			वापस " HiperSockets";
		हाल QETH_CARD_TYPE_OSN:
			वापस " OSN QDIO";
		हाल QETH_CARD_TYPE_OSM:
			वापस " OSM QDIO";
		हाल QETH_CARD_TYPE_OSX:
			वापस " OSX QDIO";
		शेष:
			वापस " unknown";
		पूर्ण
	पूर्ण
	वापस " n/a";
पूर्ण

/* max length to be वापसed: 14 */
स्थिर अक्षर *qeth_get_cardname_लघु(काष्ठा qeth_card *card)
अणु
	अगर (IS_VM_NIC(card)) अणु
		चयन (card->info.type) अणु
		हाल QETH_CARD_TYPE_OSD:
			वापस "Virt.NIC QDIO";
		हाल QETH_CARD_TYPE_IQD:
			वापस "Virt.NIC Hiper";
		हाल QETH_CARD_TYPE_OSM:
			वापस "Virt.NIC OSM";
		हाल QETH_CARD_TYPE_OSX:
			वापस "Virt.NIC OSX";
		शेष:
			वापस "unknown";
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (card->info.type) अणु
		हाल QETH_CARD_TYPE_OSD:
			चयन (card->info.link_type) अणु
			हाल QETH_LINK_TYPE_FAST_ETH:
				वापस "OSD_100";
			हाल QETH_LINK_TYPE_HSTR:
				वापस "HSTR";
			हाल QETH_LINK_TYPE_GBIT_ETH:
				वापस "OSD_1000";
			हाल QETH_LINK_TYPE_10GBIT_ETH:
				वापस "OSD_10GIG";
			हाल QETH_LINK_TYPE_25GBIT_ETH:
				वापस "OSD_25GIG";
			हाल QETH_LINK_TYPE_LANE_ETH100:
				वापस "OSD_FE_LANE";
			हाल QETH_LINK_TYPE_LANE_TR:
				वापस "OSD_TR_LANE";
			हाल QETH_LINK_TYPE_LANE_ETH1000:
				वापस "OSD_GbE_LANE";
			हाल QETH_LINK_TYPE_LANE:
				वापस "OSD_ATM_LANE";
			शेष:
				वापस "OSD_Express";
			पूर्ण
		हाल QETH_CARD_TYPE_IQD:
			वापस "HiperSockets";
		हाल QETH_CARD_TYPE_OSN:
			वापस "OSN";
		हाल QETH_CARD_TYPE_OSM:
			वापस "OSM_1000";
		हाल QETH_CARD_TYPE_OSX:
			वापस "OSX_10GIG";
		शेष:
			वापस "unknown";
		पूर्ण
	पूर्ण
	वापस "n/a";
पूर्ण

व्योम qeth_set_allowed_thपढ़ोs(काष्ठा qeth_card *card, अचिन्हित दीर्घ thपढ़ोs,
			 पूर्णांक clear_start_mask)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	card->thपढ़ो_allowed_mask = thपढ़ोs;
	अगर (clear_start_mask)
		card->thपढ़ो_start_mask &= thपढ़ोs;
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);
	wake_up(&card->रुको_q);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_set_allowed_thपढ़ोs);

पूर्णांक qeth_thपढ़ोs_running(काष्ठा qeth_card *card, अचिन्हित दीर्घ thपढ़ोs)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	rc = (card->thपढ़ो_running_mask & thपढ़ोs);
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_thपढ़ोs_running);

अटल व्योम qeth_clear_working_pool_list(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_buffer_pool_entry *pool_entry, *पंचांगp;
	काष्ठा qeth_qdio_q *queue = card->qdio.in_q;
	अचिन्हित पूर्णांक i;

	QETH_CARD_TEXT(card, 5, "clwrklst");
	list_क्रम_each_entry_safe(pool_entry, पंचांगp,
				 &card->qdio.in_buf_pool.entry_list, list)
		list_del(&pool_entry->list);

	क्रम (i = 0; i < ARRAY_SIZE(queue->bufs); i++)
		queue->bufs[i].pool_entry = शून्य;
पूर्ण

अटल व्योम qeth_मुक्त_pool_entry(काष्ठा qeth_buffer_pool_entry *entry)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(entry->elements); i++) अणु
		अगर (entry->elements[i])
			__मुक्त_page(entry->elements[i]);
	पूर्ण

	kमुक्त(entry);
पूर्ण

अटल व्योम qeth_मुक्त_buffer_pool(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_buffer_pool_entry *entry, *पंचांगp;

	list_क्रम_each_entry_safe(entry, पंचांगp, &card->qdio.init_pool.entry_list,
				 init_list) अणु
		list_del(&entry->init_list);
		qeth_मुक्त_pool_entry(entry);
	पूर्ण
पूर्ण

अटल काष्ठा qeth_buffer_pool_entry *qeth_alloc_pool_entry(अचिन्हित पूर्णांक pages)
अणु
	काष्ठा qeth_buffer_pool_entry *entry;
	अचिन्हित पूर्णांक i;

	entry = kzalloc(माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस शून्य;

	क्रम (i = 0; i < pages; i++) अणु
		entry->elements[i] = __dev_alloc_page(GFP_KERNEL);

		अगर (!entry->elements[i]) अणु
			qeth_मुक्त_pool_entry(entry);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस entry;
पूर्ण

अटल पूर्णांक qeth_alloc_buffer_pool(काष्ठा qeth_card *card)
अणु
	अचिन्हित पूर्णांक buf_elements = QETH_MAX_BUFFER_ELEMENTS(card);
	अचिन्हित पूर्णांक i;

	QETH_CARD_TEXT(card, 5, "alocpool");
	क्रम (i = 0; i < card->qdio.init_pool.buf_count; ++i) अणु
		काष्ठा qeth_buffer_pool_entry *entry;

		entry = qeth_alloc_pool_entry(buf_elements);
		अगर (!entry) अणु
			qeth_मुक्त_buffer_pool(card);
			वापस -ENOMEM;
		पूर्ण

		list_add(&entry->init_list, &card->qdio.init_pool.entry_list);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qeth_resize_buffer_pool(काष्ठा qeth_card *card, अचिन्हित पूर्णांक count)
अणु
	अचिन्हित पूर्णांक buf_elements = QETH_MAX_BUFFER_ELEMENTS(card);
	काष्ठा qeth_qdio_buffer_pool *pool = &card->qdio.init_pool;
	काष्ठा qeth_buffer_pool_entry *entry, *पंचांगp;
	पूर्णांक delta = count - pool->buf_count;
	LIST_HEAD(entries);

	QETH_CARD_TEXT(card, 2, "realcbp");

	/* Defer until queue is allocated: */
	अगर (!card->qdio.in_q)
		जाओ out;

	/* Remove entries from the pool: */
	जबतक (delta < 0) अणु
		entry = list_first_entry(&pool->entry_list,
					 काष्ठा qeth_buffer_pool_entry,
					 init_list);
		list_del(&entry->init_list);
		qeth_मुक्त_pool_entry(entry);

		delta++;
	पूर्ण

	/* Allocate additional entries: */
	जबतक (delta > 0) अणु
		entry = qeth_alloc_pool_entry(buf_elements);
		अगर (!entry) अणु
			list_क्रम_each_entry_safe(entry, पंचांगp, &entries,
						 init_list) अणु
				list_del(&entry->init_list);
				qeth_मुक्त_pool_entry(entry);
			पूर्ण

			वापस -ENOMEM;
		पूर्ण

		list_add(&entry->init_list, &entries);

		delta--;
	पूर्ण

	list_splice(&entries, &pool->entry_list);

out:
	card->qdio.in_buf_pool.buf_count = count;
	pool->buf_count = count;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_resize_buffer_pool);

अटल व्योम qeth_मुक्त_qdio_queue(काष्ठा qeth_qdio_q *q)
अणु
	अगर (!q)
		वापस;

	qdio_मुक्त_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
	kमुक्त(q);
पूर्ण

अटल काष्ठा qeth_qdio_q *qeth_alloc_qdio_queue(व्योम)
अणु
	काष्ठा qeth_qdio_q *q = kzalloc(माप(*q), GFP_KERNEL);
	पूर्णांक i;

	अगर (!q)
		वापस शून्य;

	अगर (qdio_alloc_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q)) अणु
		kमुक्त(q);
		वापस शून्य;
	पूर्ण

	क्रम (i = 0; i < QDIO_MAX_BUFFERS_PER_Q; ++i)
		q->bufs[i].buffer = q->qdio_bufs[i];

	QETH_DBF_HEX(SETUP, 2, &q, माप(व्योम *));
	वापस q;
पूर्ण

अटल पूर्णांक qeth_cq_init(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	अगर (card->options.cq == QETH_CQ_ENABLED) अणु
		QETH_CARD_TEXT(card, 2, "cqinit");
		qdio_reset_buffers(card->qdio.c_q->qdio_bufs,
				   QDIO_MAX_BUFFERS_PER_Q);
		card->qdio.c_q->next_buf_to_init = 127;
		rc = करो_QDIO(CARD_DDEV(card), QDIO_FLAG_SYNC_INPUT,
			     card->qdio.no_in_queues - 1, 0, 127, शून्य);
		अगर (rc) अणु
			QETH_CARD_TEXT_(card, 2, "1err%d", rc);
			जाओ out;
		पूर्ण
	पूर्ण
	rc = 0;
out:
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_alloc_cq(काष्ठा qeth_card *card)
अणु
	अगर (card->options.cq == QETH_CQ_ENABLED) अणु
		QETH_CARD_TEXT(card, 2, "cqon");
		card->qdio.c_q = qeth_alloc_qdio_queue();
		अगर (!card->qdio.c_q) अणु
			dev_err(&card->gdev->dev, "Failed to create completion queue\n");
			वापस -ENOMEM;
		पूर्ण

		card->qdio.no_in_queues = 2;
	पूर्ण अन्यथा अणु
		QETH_CARD_TEXT(card, 2, "nocq");
		card->qdio.c_q = शून्य;
		card->qdio.no_in_queues = 1;
	पूर्ण
	QETH_CARD_TEXT_(card, 2, "iqc%d", card->qdio.no_in_queues);
	वापस 0;
पूर्ण

अटल व्योम qeth_मुक्त_cq(काष्ठा qeth_card *card)
अणु
	अगर (card->qdio.c_q) अणु
		--card->qdio.no_in_queues;
		qeth_मुक्त_qdio_queue(card->qdio.c_q);
		card->qdio.c_q = शून्य;
	पूर्ण
पूर्ण

अटल क्रमागत iucv_tx_notअगरy qeth_compute_cq_notअगरication(पूर्णांक sbalf15,
							पूर्णांक delayed)
अणु
	क्रमागत iucv_tx_notअगरy n;

	चयन (sbalf15) अणु
	हाल 0:
		n = delayed ? TX_NOTIFY_DELAYED_OK : TX_NOTIFY_OK;
		अवरोध;
	हाल 4:
	हाल 16:
	हाल 17:
	हाल 18:
		n = delayed ? TX_NOTIFY_DELAYED_UNREACHABLE :
			TX_NOTIFY_UNREACHABLE;
		अवरोध;
	शेष:
		n = delayed ? TX_NOTIFY_DELAYED_GENERALERROR :
			TX_NOTIFY_GENERALERROR;
		अवरोध;
	पूर्ण

	वापस n;
पूर्ण

अटल व्योम qeth_qdio_handle_aob(काष्ठा qeth_card *card,
				 अचिन्हित दीर्घ phys_aob_addr)
अणु
	क्रमागत qeth_qdio_out_buffer_state new_state = QETH_QDIO_BUF_QAOB_OK;
	काष्ठा qaob *aob;
	काष्ठा qeth_qdio_out_buffer *buffer;
	क्रमागत iucv_tx_notअगरy notअगरication;
	काष्ठा qeth_qdio_out_q *queue;
	अचिन्हित पूर्णांक i;

	aob = (काष्ठा qaob *) phys_to_virt(phys_aob_addr);
	QETH_CARD_TEXT(card, 5, "haob");
	QETH_CARD_TEXT_(card, 5, "%lx", phys_aob_addr);
	buffer = (काष्ठा qeth_qdio_out_buffer *) aob->user1;
	QETH_CARD_TEXT_(card, 5, "%lx", aob->user1);

	अगर (aob->aorc) अणु
		QETH_CARD_TEXT_(card, 2, "aorc%02X", aob->aorc);
		new_state = QETH_QDIO_BUF_QAOB_ERROR;
	पूर्ण

	चयन (atomic_xchg(&buffer->state, new_state)) अणु
	हाल QETH_QDIO_BUF_PRIMED:
		/* Faster than TX completion code, let it handle the async
		 * completion क्रम us. It will also recycle the QAOB.
		 */
		अवरोध;
	हाल QETH_QDIO_BUF_PENDING:
		/* TX completion code is active and will handle the async
		 * completion क्रम us. It will also recycle the QAOB.
		 */
		अवरोध;
	हाल QETH_QDIO_BUF_NEED_QAOB:
		/* TX completion code is alपढ़ोy finished. */
		notअगरication = qeth_compute_cq_notअगरication(aob->aorc, 1);
		qeth_notअगरy_skbs(buffer->q, buffer, notअगरication);

		/* Free dangling allocations. The attached skbs are handled by
		 * qeth_tx_complete_pending_bufs(), and so is the QAOB.
		 */
		क्रम (i = 0;
		     i < aob->sb_count && i < QETH_MAX_BUFFER_ELEMENTS(card);
		     i++) अणु
			व्योम *data = phys_to_virt(aob->sba[i]);

			अगर (data && buffer->is_header[i])
				kmem_cache_मुक्त(qeth_core_header_cache, data);
			buffer->is_header[i] = 0;
		पूर्ण

		queue = buffer->q;
		atomic_set(&buffer->state, QETH_QDIO_BUF_EMPTY);
		napi_schedule(&queue->napi);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल व्योम qeth_setup_ccw(काष्ठा ccw1 *ccw, u8 cmd_code, u8 flags, u32 len,
			   व्योम *data)
अणु
	ccw->cmd_code = cmd_code;
	ccw->flags = flags | CCW_FLAG_SLI;
	ccw->count = len;
	ccw->cda = (__u32) __pa(data);
पूर्ण

अटल पूर्णांक __qeth_issue_next_पढ़ो(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob = card->पढ़ो_cmd;
	काष्ठा qeth_channel *channel = iob->channel;
	काष्ठा ccw1 *ccw = __ccw_from_cmd(iob);
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 5, "issnxrd");
	अगर (channel->state != CH_STATE_UP)
		वापस -EIO;

	स_रखो(iob->data, 0, iob->length);
	qeth_setup_ccw(ccw, CCW_CMD_READ, 0, iob->length, iob->data);
	iob->callback = qeth_issue_next_पढ़ो_cb;
	/* keep the cmd alive after completion: */
	qeth_get_cmd(iob);

	QETH_CARD_TEXT(card, 6, "noirqpnd");
	rc = ccw_device_start(channel->ccwdev, ccw, (addr_t) iob, 0, 0);
	अगर (!rc) अणु
		channel->active_cmd = iob;
	पूर्ण अन्यथा अणु
		QETH_DBF_MESSAGE(2, "error %i on device %x when starting next read ccw!\n",
				 rc, CARD_DEVID(card));
		qeth_unlock_channel(card, channel);
		qeth_put_cmd(iob);
		card->पढ़ो_or_ग_लिखो_problem = 1;
		qeth_schedule_recovery(card);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_issue_next_पढ़ो(काष्ठा qeth_card *card)
अणु
	पूर्णांक ret;

	spin_lock_irq(get_ccwdev_lock(CARD_RDEV(card)));
	ret = __qeth_issue_next_पढ़ो(card);
	spin_unlock_irq(get_ccwdev_lock(CARD_RDEV(card)));

	वापस ret;
पूर्ण

अटल व्योम qeth_enqueue_cmd(काष्ठा qeth_card *card,
			     काष्ठा qeth_cmd_buffer *iob)
अणु
	spin_lock_irq(&card->lock);
	list_add_tail(&iob->list_entry, &card->cmd_रुकोer_list);
	spin_unlock_irq(&card->lock);
पूर्ण

अटल व्योम qeth_dequeue_cmd(काष्ठा qeth_card *card,
			     काष्ठा qeth_cmd_buffer *iob)
अणु
	spin_lock_irq(&card->lock);
	list_del(&iob->list_entry);
	spin_unlock_irq(&card->lock);
पूर्ण

व्योम qeth_notअगरy_cmd(काष्ठा qeth_cmd_buffer *iob, पूर्णांक reason)
अणु
	iob->rc = reason;
	complete(&iob->करोne);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_notअगरy_cmd);

अटल व्योम qeth_flush_local_addrs4(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_local_addr *addr;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&card->local_addrs4_lock);
	hash_क्रम_each_safe(card->local_addrs4, i, पंचांगp, addr, hnode) अणु
		hash_del_rcu(&addr->hnode);
		kमुक्त_rcu(addr, rcu);
	पूर्ण
	spin_unlock_irq(&card->local_addrs4_lock);
पूर्ण

अटल व्योम qeth_flush_local_addrs6(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_local_addr *addr;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक i;

	spin_lock_irq(&card->local_addrs6_lock);
	hash_क्रम_each_safe(card->local_addrs6, i, पंचांगp, addr, hnode) अणु
		hash_del_rcu(&addr->hnode);
		kमुक्त_rcu(addr, rcu);
	पूर्ण
	spin_unlock_irq(&card->local_addrs6_lock);
पूर्ण

अटल व्योम qeth_flush_local_addrs(काष्ठा qeth_card *card)
अणु
	qeth_flush_local_addrs4(card);
	qeth_flush_local_addrs6(card);
पूर्ण

अटल व्योम qeth_add_local_addrs4(काष्ठा qeth_card *card,
				  काष्ठा qeth_ipacmd_local_addrs4 *cmd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (cmd->addr_length !=
	    माप_field(काष्ठा qeth_ipacmd_local_addr4, addr)) अणु
		dev_err_ratelimited(&card->gdev->dev,
				    "Dropped IPv4 ADD LOCAL ADDR event with bad length %u\n",
				    cmd->addr_length);
		वापस;
	पूर्ण

	spin_lock(&card->local_addrs4_lock);
	क्रम (i = 0; i < cmd->count; i++) अणु
		अचिन्हित पूर्णांक key = ipv4_addr_hash(cmd->addrs[i].addr);
		काष्ठा qeth_local_addr *addr;
		bool duplicate = false;

		hash_क्रम_each_possible(card->local_addrs4, addr, hnode, key) अणु
			अगर (addr->addr.s6_addr32[3] == cmd->addrs[i].addr) अणु
				duplicate = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (duplicate)
			जारी;

		addr = kदो_स्मृति(माप(*addr), GFP_ATOMIC);
		अगर (!addr) अणु
			dev_err(&card->gdev->dev,
				"Failed to allocate local addr object. Traffic to %pI4 might suffer.\n",
				&cmd->addrs[i].addr);
			जारी;
		पूर्ण

		ipv6_addr_set(&addr->addr, 0, 0, 0, cmd->addrs[i].addr);
		hash_add_rcu(card->local_addrs4, &addr->hnode, key);
	पूर्ण
	spin_unlock(&card->local_addrs4_lock);
पूर्ण

अटल व्योम qeth_add_local_addrs6(काष्ठा qeth_card *card,
				  काष्ठा qeth_ipacmd_local_addrs6 *cmd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (cmd->addr_length !=
	    माप_field(काष्ठा qeth_ipacmd_local_addr6, addr)) अणु
		dev_err_ratelimited(&card->gdev->dev,
				    "Dropped IPv6 ADD LOCAL ADDR event with bad length %u\n",
				    cmd->addr_length);
		वापस;
	पूर्ण

	spin_lock(&card->local_addrs6_lock);
	क्रम (i = 0; i < cmd->count; i++) अणु
		u32 key = ipv6_addr_hash(&cmd->addrs[i].addr);
		काष्ठा qeth_local_addr *addr;
		bool duplicate = false;

		hash_क्रम_each_possible(card->local_addrs6, addr, hnode, key) अणु
			अगर (ipv6_addr_equal(&addr->addr, &cmd->addrs[i].addr)) अणु
				duplicate = true;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (duplicate)
			जारी;

		addr = kदो_स्मृति(माप(*addr), GFP_ATOMIC);
		अगर (!addr) अणु
			dev_err(&card->gdev->dev,
				"Failed to allocate local addr object. Traffic to %pI6c might suffer.\n",
				&cmd->addrs[i].addr);
			जारी;
		पूर्ण

		addr->addr = cmd->addrs[i].addr;
		hash_add_rcu(card->local_addrs6, &addr->hnode, key);
	पूर्ण
	spin_unlock(&card->local_addrs6_lock);
पूर्ण

अटल व्योम qeth_del_local_addrs4(काष्ठा qeth_card *card,
				  काष्ठा qeth_ipacmd_local_addrs4 *cmd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (cmd->addr_length !=
	    माप_field(काष्ठा qeth_ipacmd_local_addr4, addr)) अणु
		dev_err_ratelimited(&card->gdev->dev,
				    "Dropped IPv4 DEL LOCAL ADDR event with bad length %u\n",
				    cmd->addr_length);
		वापस;
	पूर्ण

	spin_lock(&card->local_addrs4_lock);
	क्रम (i = 0; i < cmd->count; i++) अणु
		काष्ठा qeth_ipacmd_local_addr4 *addr = &cmd->addrs[i];
		अचिन्हित पूर्णांक key = ipv4_addr_hash(addr->addr);
		काष्ठा qeth_local_addr *पंचांगp;

		hash_क्रम_each_possible(card->local_addrs4, पंचांगp, hnode, key) अणु
			अगर (पंचांगp->addr.s6_addr32[3] == addr->addr) अणु
				hash_del_rcu(&पंचांगp->hnode);
				kमुक्त_rcu(पंचांगp, rcu);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&card->local_addrs4_lock);
पूर्ण

अटल व्योम qeth_del_local_addrs6(काष्ठा qeth_card *card,
				  काष्ठा qeth_ipacmd_local_addrs6 *cmd)
अणु
	अचिन्हित पूर्णांक i;

	अगर (cmd->addr_length !=
	    माप_field(काष्ठा qeth_ipacmd_local_addr6, addr)) अणु
		dev_err_ratelimited(&card->gdev->dev,
				    "Dropped IPv6 DEL LOCAL ADDR event with bad length %u\n",
				    cmd->addr_length);
		वापस;
	पूर्ण

	spin_lock(&card->local_addrs6_lock);
	क्रम (i = 0; i < cmd->count; i++) अणु
		काष्ठा qeth_ipacmd_local_addr6 *addr = &cmd->addrs[i];
		u32 key = ipv6_addr_hash(&addr->addr);
		काष्ठा qeth_local_addr *पंचांगp;

		hash_क्रम_each_possible(card->local_addrs6, पंचांगp, hnode, key) अणु
			अगर (ipv6_addr_equal(&पंचांगp->addr, &addr->addr)) अणु
				hash_del_rcu(&पंचांगp->hnode);
				kमुक्त_rcu(पंचांगp, rcu);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock(&card->local_addrs6_lock);
पूर्ण

अटल bool qeth_next_hop_is_local_v4(काष्ठा qeth_card *card,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा qeth_local_addr *पंचांगp;
	bool is_local = false;
	अचिन्हित पूर्णांक key;
	__be32 next_hop;

	अगर (hash_empty(card->local_addrs4))
		वापस false;

	rcu_पढ़ो_lock();
	next_hop = qeth_next_hop_v4_rcu(skb,
					qeth_dst_check_rcu(skb, htons(ETH_P_IP)));
	key = ipv4_addr_hash(next_hop);

	hash_क्रम_each_possible_rcu(card->local_addrs4, पंचांगp, hnode, key) अणु
		अगर (पंचांगp->addr.s6_addr32[3] == next_hop) अणु
			is_local = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस is_local;
पूर्ण

अटल bool qeth_next_hop_is_local_v6(काष्ठा qeth_card *card,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा qeth_local_addr *पंचांगp;
	काष्ठा in6_addr *next_hop;
	bool is_local = false;
	u32 key;

	अगर (hash_empty(card->local_addrs6))
		वापस false;

	rcu_पढ़ो_lock();
	next_hop = qeth_next_hop_v6_rcu(skb,
					qeth_dst_check_rcu(skb, htons(ETH_P_IPV6)));
	key = ipv6_addr_hash(next_hop);

	hash_क्रम_each_possible_rcu(card->local_addrs6, पंचांगp, hnode, key) अणु
		अगर (ipv6_addr_equal(&पंचांगp->addr, next_hop)) अणु
			is_local = true;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस is_local;
पूर्ण

अटल पूर्णांक qeth_debugfs_local_addr_show(काष्ठा seq_file *m, व्योम *v)
अणु
	काष्ठा qeth_card *card = m->निजी;
	काष्ठा qeth_local_addr *पंचांगp;
	अचिन्हित पूर्णांक i;

	rcu_पढ़ो_lock();
	hash_क्रम_each_rcu(card->local_addrs4, i, पंचांगp, hnode)
		seq_म_लिखो(m, "%pI4\n", &पंचांगp->addr.s6_addr32[3]);
	hash_क्रम_each_rcu(card->local_addrs6, i, पंचांगp, hnode)
		seq_म_लिखो(m, "%pI6c\n", &पंचांगp->addr);
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(qeth_debugfs_local_addr);

अटल व्योम qeth_issue_ipa_msg(काष्ठा qeth_ipa_cmd *cmd, पूर्णांक rc,
		काष्ठा qeth_card *card)
अणु
	स्थिर अक्षर *ipa_name;
	पूर्णांक com = cmd->hdr.command;

	ipa_name = qeth_get_ipa_cmd_name(com);

	अगर (rc)
		QETH_DBF_MESSAGE(2, "IPA: %s(%#x) for device %x returned %#x \"%s\"\n",
				 ipa_name, com, CARD_DEVID(card), rc,
				 qeth_get_ipa_msg(rc));
	अन्यथा
		QETH_DBF_MESSAGE(5, "IPA: %s(%#x) for device %x succeeded\n",
				 ipa_name, com, CARD_DEVID(card));
पूर्ण

अटल काष्ठा qeth_ipa_cmd *qeth_check_ipa_data(काष्ठा qeth_card *card,
						काष्ठा qeth_ipa_cmd *cmd)
अणु
	QETH_CARD_TEXT(card, 5, "chkipad");

	अगर (IS_IPA_REPLY(cmd)) अणु
		अगर (cmd->hdr.command != IPA_CMD_SETCCID &&
		    cmd->hdr.command != IPA_CMD_DELCCID &&
		    cmd->hdr.command != IPA_CMD_MODCCID &&
		    cmd->hdr.command != IPA_CMD_SET_DIAG_ASS)
			qeth_issue_ipa_msg(cmd, cmd->hdr.वापस_code, card);
		वापस cmd;
	पूर्ण

	/* handle unsolicited event: */
	चयन (cmd->hdr.command) अणु
	हाल IPA_CMD_STOPLAN:
		अगर (cmd->hdr.वापस_code == IPA_RC_VEPA_TO_VEB_TRANSITION) अणु
			dev_err(&card->gdev->dev,
				"Interface %s is down because the adjacent port is no longer in reflective relay mode\n",
				netdev_name(card->dev));
			schedule_work(&card->बंद_dev_work);
		पूर्ण अन्यथा अणु
			dev_warn(&card->gdev->dev,
				 "The link for interface %s on CHPID 0x%X failed\n",
				 netdev_name(card->dev), card->info.chpid);
			qeth_issue_ipa_msg(cmd, cmd->hdr.वापस_code, card);
			netअगर_carrier_off(card->dev);
		पूर्ण
		वापस शून्य;
	हाल IPA_CMD_STARTLAN:
		dev_info(&card->gdev->dev,
			 "The link for %s on CHPID 0x%X has been restored\n",
			 netdev_name(card->dev), card->info.chpid);
		अगर (card->info.hwtrap)
			card->info.hwtrap = 2;
		qeth_schedule_recovery(card);
		वापस शून्य;
	हाल IPA_CMD_SETBRIDGEPORT_IQD:
	हाल IPA_CMD_SETBRIDGEPORT_OSA:
	हाल IPA_CMD_ADDRESS_CHANGE_NOTIF:
		अगर (card->discipline->control_event_handler(card, cmd))
			वापस cmd;
		वापस शून्य;
	हाल IPA_CMD_MODCCID:
		वापस cmd;
	हाल IPA_CMD_REGISTER_LOCAL_ADDR:
		अगर (cmd->hdr.prot_version == QETH_PROT_IPV4)
			qeth_add_local_addrs4(card, &cmd->data.local_addrs4);
		अन्यथा अगर (cmd->hdr.prot_version == QETH_PROT_IPV6)
			qeth_add_local_addrs6(card, &cmd->data.local_addrs6);

		QETH_CARD_TEXT(card, 3, "irla");
		वापस शून्य;
	हाल IPA_CMD_UNREGISTER_LOCAL_ADDR:
		अगर (cmd->hdr.prot_version == QETH_PROT_IPV4)
			qeth_del_local_addrs4(card, &cmd->data.local_addrs4);
		अन्यथा अगर (cmd->hdr.prot_version == QETH_PROT_IPV6)
			qeth_del_local_addrs6(card, &cmd->data.local_addrs6);

		QETH_CARD_TEXT(card, 3, "urla");
		वापस शून्य;
	शेष:
		QETH_DBF_MESSAGE(2, "Received data is IPA but not a reply!\n");
		वापस cmd;
	पूर्ण
पूर्ण

अटल व्योम qeth_clear_ipacmd_list(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	अचिन्हित दीर्घ flags;

	QETH_CARD_TEXT(card, 4, "clipalst");

	spin_lock_irqsave(&card->lock, flags);
	list_क्रम_each_entry(iob, &card->cmd_रुकोer_list, list_entry)
		qeth_notअगरy_cmd(iob, -ECANCELED);
	spin_unlock_irqrestore(&card->lock, flags);
पूर्ण

अटल पूर्णांक qeth_check_idx_response(काष्ठा qeth_card *card,
	अचिन्हित अक्षर *buffer)
अणु
	QETH_DBF_HEX(CTRL, 2, buffer, QETH_DBF_CTRL_LEN);
	अगर ((buffer[2] & QETH_IDX_TERMINATE_MASK) == QETH_IDX_TERMINATE) अणु
		QETH_DBF_MESSAGE(2, "received an IDX TERMINATE with cause code %#04x\n",
				 buffer[4]);
		QETH_CARD_TEXT(card, 2, "ckidxres");
		QETH_CARD_TEXT(card, 2, " idxterm");
		QETH_CARD_TEXT_(card, 2, "rc%x", buffer[4]);
		अगर (buffer[4] == QETH_IDX_TERM_BAD_TRANSPORT ||
		    buffer[4] == QETH_IDX_TERM_BAD_TRANSPORT_VM) अणु
			dev_err(&card->gdev->dev,
				"The device does not support the configured transport mode\n");
			वापस -EPROTONOSUPPORT;
		पूर्ण
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

व्योम qeth_put_cmd(काष्ठा qeth_cmd_buffer *iob)
अणु
	अगर (refcount_dec_and_test(&iob->ref_count)) अणु
		kमुक्त(iob->data);
		kमुक्त(iob);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(qeth_put_cmd);

अटल व्योम qeth_release_buffer_cb(काष्ठा qeth_card *card,
				   काष्ठा qeth_cmd_buffer *iob,
				   अचिन्हित पूर्णांक data_length)
अणु
	qeth_put_cmd(iob);
पूर्ण

अटल व्योम qeth_cancel_cmd(काष्ठा qeth_cmd_buffer *iob, पूर्णांक rc)
अणु
	qeth_notअगरy_cmd(iob, rc);
	qeth_put_cmd(iob);
पूर्ण

काष्ठा qeth_cmd_buffer *qeth_alloc_cmd(काष्ठा qeth_channel *channel,
				       अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक ccws,
				       दीर्घ समयout)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	अगर (length > QETH_बफ_मानE)
		वापस शून्य;

	iob = kzalloc(माप(*iob), GFP_KERNEL);
	अगर (!iob)
		वापस शून्य;

	iob->data = kzalloc(ALIGN(length, 8) + ccws * माप(काष्ठा ccw1),
			    GFP_KERNEL | GFP_DMA);
	अगर (!iob->data) अणु
		kमुक्त(iob);
		वापस शून्य;
	पूर्ण

	init_completion(&iob->करोne);
	spin_lock_init(&iob->lock);
	refcount_set(&iob->ref_count, 1);
	iob->channel = channel;
	iob->समयout = समयout;
	iob->length = length;
	वापस iob;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_alloc_cmd);

अटल व्योम qeth_issue_next_पढ़ो_cb(काष्ठा qeth_card *card,
				    काष्ठा qeth_cmd_buffer *iob,
				    अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_cmd_buffer *request = शून्य;
	काष्ठा qeth_ipa_cmd *cmd = शून्य;
	काष्ठा qeth_reply *reply = शून्य;
	काष्ठा qeth_cmd_buffer *पंचांगp;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 4, "sndctlcb");
	rc = qeth_check_idx_response(card, iob->data);
	चयन (rc) अणु
	हाल 0:
		अवरोध;
	हाल -EIO:
		qeth_schedule_recovery(card);
		fallthrough;
	शेष:
		qeth_clear_ipacmd_list(card);
		जाओ err_idx;
	पूर्ण

	cmd = __ipa_reply(iob);
	अगर (cmd) अणु
		cmd = qeth_check_ipa_data(card, cmd);
		अगर (!cmd)
			जाओ out;
		अगर (IS_OSN(card) && card->osn_info.assist_cb &&
		    cmd->hdr.command != IPA_CMD_STARTLAN) अणु
			card->osn_info.assist_cb(card->dev, cmd);
			जाओ out;
		पूर्ण
	पूर्ण

	/* match against pending cmd requests */
	spin_lock_irqsave(&card->lock, flags);
	list_क्रम_each_entry(पंचांगp, &card->cmd_रुकोer_list, list_entry) अणु
		अगर (पंचांगp->match && पंचांगp->match(पंचांगp, iob)) अणु
			request = पंचांगp;
			/* take the object outside the lock */
			qeth_get_cmd(request);
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&card->lock, flags);

	अगर (!request)
		जाओ out;

	reply = &request->reply;
	अगर (!reply->callback) अणु
		rc = 0;
		जाओ no_callback;
	पूर्ण

	spin_lock_irqsave(&request->lock, flags);
	अगर (request->rc)
		/* Bail out when the requestor has alपढ़ोy left: */
		rc = request->rc;
	अन्यथा
		rc = reply->callback(card, reply, cmd ? (अचिन्हित दीर्घ)cmd :
							(अचिन्हित दीर्घ)iob);
	spin_unlock_irqrestore(&request->lock, flags);

no_callback:
	अगर (rc <= 0)
		qeth_notअगरy_cmd(request, rc);
	qeth_put_cmd(request);
out:
	स_नकल(&card->seqno.pdu_hdr_ack,
		QETH_PDU_HEADER_SEQ_NO(iob->data),
		QETH_SEQ_NO_LENGTH);
	__qeth_issue_next_पढ़ो(card);
err_idx:
	qeth_put_cmd(iob);
पूर्ण

अटल पूर्णांक qeth_set_thपढ़ो_start_bit(काष्ठा qeth_card *card,
		अचिन्हित दीर्घ thपढ़ो)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	अगर (!(card->thपढ़ो_allowed_mask & thपढ़ो))
		rc = -EPERM;
	अन्यथा अगर (card->thपढ़ो_start_mask & thपढ़ो)
		rc = -EBUSY;
	अन्यथा
		card->thपढ़ो_start_mask |= thपढ़ो;
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);

	वापस rc;
पूर्ण

अटल व्योम qeth_clear_thपढ़ो_start_bit(काष्ठा qeth_card *card,
					अचिन्हित दीर्घ thपढ़ो)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	card->thपढ़ो_start_mask &= ~thपढ़ो;
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);
	wake_up(&card->रुको_q);
पूर्ण

अटल व्योम qeth_clear_thपढ़ो_running_bit(काष्ठा qeth_card *card,
					  अचिन्हित दीर्घ thपढ़ो)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	card->thपढ़ो_running_mask &= ~thपढ़ो;
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);
	wake_up_all(&card->रुको_q);
पूर्ण

अटल पूर्णांक __qeth_करो_run_thपढ़ो(काष्ठा qeth_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	अगर (card->thपढ़ो_start_mask & thपढ़ो) अणु
		अगर ((card->thपढ़ो_allowed_mask & thपढ़ो) &&
		    !(card->thपढ़ो_running_mask & thपढ़ो)) अणु
			rc = 1;
			card->thपढ़ो_start_mask &= ~thपढ़ो;
			card->thपढ़ो_running_mask |= thपढ़ो;
		पूर्ण अन्यथा
			rc = -EPERM;
	पूर्ण
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_करो_run_thपढ़ो(काष्ठा qeth_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
	पूर्णांक rc = 0;

	रुको_event(card->रुको_q,
		   (rc = __qeth_करो_run_thपढ़ो(card, thपढ़ो)) >= 0);
	वापस rc;
पूर्ण

पूर्णांक qeth_schedule_recovery(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "startrec");

	rc = qeth_set_thपढ़ो_start_bit(card, QETH_RECOVER_THREAD);
	अगर (!rc)
		schedule_work(&card->kernel_thपढ़ो_starter);

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_get_problem(काष्ठा qeth_card *card, काष्ठा ccw_device *cdev,
			    काष्ठा irb *irb)
अणु
	पूर्णांक dstat, cstat;
	अक्षर *sense;

	sense = (अक्षर *) irb->ecw;
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	अगर (cstat & (SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK |
		     SCHN_STAT_CHN_DATA_CHK | SCHN_STAT_CHAIN_CHECK |
		     SCHN_STAT_PROT_CHECK | SCHN_STAT_PROG_CHECK)) अणु
		QETH_CARD_TEXT(card, 2, "CGENCHK");
		dev_warn(&cdev->dev, "The qeth device driver "
			"failed to recover an error on the device\n");
		QETH_DBF_MESSAGE(2, "check on channel %x with dstat=%#x, cstat=%#x\n",
				 CCW_DEVID(cdev), dstat, cstat);
		prपूर्णांक_hex_dump(KERN_WARNING, "qeth: irb ", DUMP_PREFIX_OFFSET,
				16, 1, irb, 64, 1);
		वापस -EIO;
	पूर्ण

	अगर (dstat & DEV_STAT_UNIT_CHECK) अणु
		अगर (sense[SENSE_RESETTING_EVENT_BYTE] &
		    SENSE_RESETTING_EVENT_FLAG) अणु
			QETH_CARD_TEXT(card, 2, "REVIND");
			वापस -EIO;
		पूर्ण
		अगर (sense[SENSE_COMMAND_REJECT_BYTE] &
		    SENSE_COMMAND_REJECT_FLAG) अणु
			QETH_CARD_TEXT(card, 2, "CMDREJi");
			वापस -EIO;
		पूर्ण
		अगर ((sense[2] == 0xaf) && (sense[3] == 0xfe)) अणु
			QETH_CARD_TEXT(card, 2, "AFFE");
			वापस -EIO;
		पूर्ण
		अगर ((!sense[0]) && (!sense[1]) && (!sense[2]) && (!sense[3])) अणु
			QETH_CARD_TEXT(card, 2, "ZEROSEN");
			वापस 0;
		पूर्ण
		QETH_CARD_TEXT(card, 2, "DGENCHK");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_check_irb_error(काष्ठा qeth_card *card, काष्ठा ccw_device *cdev,
				काष्ठा irb *irb)
अणु
	अगर (!IS_ERR(irb))
		वापस 0;

	चयन (PTR_ERR(irb)) अणु
	हाल -EIO:
		QETH_DBF_MESSAGE(2, "i/o-error on channel %x\n",
				 CCW_DEVID(cdev));
		QETH_CARD_TEXT(card, 2, "ckirberr");
		QETH_CARD_TEXT_(card, 2, "  rc%d", -EIO);
		वापस -EIO;
	हाल -ETIMEDOUT:
		dev_warn(&cdev->dev, "A hardware operation timed out"
			" on the device\n");
		QETH_CARD_TEXT(card, 2, "ckirberr");
		QETH_CARD_TEXT_(card, 2, "  rc%d", -ETIMEDOUT);
		वापस -ETIMEDOUT;
	शेष:
		QETH_DBF_MESSAGE(2, "unknown error %ld on channel %x\n",
				 PTR_ERR(irb), CCW_DEVID(cdev));
		QETH_CARD_TEXT(card, 2, "ckirberr");
		QETH_CARD_TEXT(card, 2, "  rc???");
		वापस PTR_ERR(irb);
	पूर्ण
पूर्ण

अटल व्योम qeth_irq(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm,
		काष्ठा irb *irb)
अणु
	पूर्णांक rc;
	पूर्णांक cstat, dstat;
	काष्ठा qeth_cmd_buffer *iob = शून्य;
	काष्ठा ccwgroup_device *gdev;
	काष्ठा qeth_channel *channel;
	काष्ठा qeth_card *card;

	/* जबतक we hold the ccwdev lock, this stays valid: */
	gdev = dev_get_drvdata(&cdev->dev);
	card = dev_get_drvdata(&gdev->dev);

	QETH_CARD_TEXT(card, 5, "irq");

	अगर (card->पढ़ो.ccwdev == cdev) अणु
		channel = &card->पढ़ो;
		QETH_CARD_TEXT(card, 5, "read");
	पूर्ण अन्यथा अगर (card->ग_लिखो.ccwdev == cdev) अणु
		channel = &card->ग_लिखो;
		QETH_CARD_TEXT(card, 5, "write");
	पूर्ण अन्यथा अणु
		channel = &card->data;
		QETH_CARD_TEXT(card, 5, "data");
	पूर्ण

	अगर (पूर्णांकparm == 0) अणु
		QETH_CARD_TEXT(card, 5, "irqunsol");
	पूर्ण अन्यथा अगर ((addr_t)पूर्णांकparm != (addr_t)channel->active_cmd) अणु
		QETH_CARD_TEXT(card, 5, "irqunexp");

		dev_err(&cdev->dev,
			"Received IRQ with intparm %lx, expected %px\n",
			पूर्णांकparm, channel->active_cmd);
		अगर (channel->active_cmd)
			qeth_cancel_cmd(channel->active_cmd, -EIO);
	पूर्ण अन्यथा अणु
		iob = (काष्ठा qeth_cmd_buffer *) (addr_t)पूर्णांकparm;
	पूर्ण

	channel->active_cmd = शून्य;
	qeth_unlock_channel(card, channel);

	rc = qeth_check_irb_error(card, cdev, irb);
	अगर (rc) अणु
		/* IO was terminated, मुक्त its resources. */
		अगर (iob)
			qeth_cancel_cmd(iob, rc);
		वापस;
	पूर्ण

	अगर (irb->scsw.cmd.fctl & SCSW_FCTL_CLEAR_FUNC) अणु
		channel->state = CH_STATE_STOPPED;
		wake_up(&card->रुको_q);
	पूर्ण

	अगर (irb->scsw.cmd.fctl & SCSW_FCTL_HALT_FUNC) अणु
		channel->state = CH_STATE_HALTED;
		wake_up(&card->रुको_q);
	पूर्ण

	अगर (iob && (irb->scsw.cmd.fctl & (SCSW_FCTL_CLEAR_FUNC |
					  SCSW_FCTL_HALT_FUNC))) अणु
		qeth_cancel_cmd(iob, -ECANCELED);
		iob = शून्य;
	पूर्ण

	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	अगर ((dstat & DEV_STAT_UNIT_EXCEP) ||
	    (dstat & DEV_STAT_UNIT_CHECK) ||
	    (cstat)) अणु
		अगर (irb->esw.esw0.erw.cons) अणु
			dev_warn(&channel->ccwdev->dev,
				"The qeth device driver failed to recover "
				"an error on the device\n");
			QETH_DBF_MESSAGE(2, "sense data available on channel %x: cstat %#X dstat %#X\n",
					 CCW_DEVID(channel->ccwdev), cstat,
					 dstat);
			prपूर्णांक_hex_dump(KERN_WARNING, "qeth: irb ",
				DUMP_PREFIX_OFFSET, 16, 1, irb, 32, 1);
			prपूर्णांक_hex_dump(KERN_WARNING, "qeth: sense data ",
				DUMP_PREFIX_OFFSET, 16, 1, irb->ecw, 32, 1);
		पूर्ण

		rc = qeth_get_problem(card, cdev, irb);
		अगर (rc) अणु
			card->पढ़ो_or_ग_लिखो_problem = 1;
			अगर (iob)
				qeth_cancel_cmd(iob, rc);
			qeth_clear_ipacmd_list(card);
			qeth_schedule_recovery(card);
			वापस;
		पूर्ण
	पूर्ण

	अगर (iob) अणु
		/* sanity check: */
		अगर (irb->scsw.cmd.count > iob->length) अणु
			qeth_cancel_cmd(iob, -EIO);
			वापस;
		पूर्ण
		अगर (iob->callback)
			iob->callback(card, iob,
				      iob->length - irb->scsw.cmd.count);
	पूर्ण
पूर्ण

अटल व्योम qeth_notअगरy_skbs(काष्ठा qeth_qdio_out_q *q,
		काष्ठा qeth_qdio_out_buffer *buf,
		क्रमागत iucv_tx_notअगरy notअगरication)
अणु
	काष्ठा sk_buff *skb;

	skb_queue_walk(&buf->skb_list, skb) अणु
		काष्ठा sock *sk = skb->sk;

		QETH_CARD_TEXT_(q->card, 5, "skbn%d", notअगरication);
		QETH_CARD_TEXT_(q->card, 5, "%lx", (दीर्घ) skb);
		अगर (sk && sk->sk_family == PF_IUCV)
			iucv_sk(sk)->sk_txnotअगरy(sk, notअगरication);
	पूर्ण
पूर्ण

अटल व्योम qeth_tx_complete_buf(काष्ठा qeth_qdio_out_buffer *buf, bool error,
				 पूर्णांक budget)
अणु
	काष्ठा qeth_qdio_out_q *queue = buf->q;
	काष्ठा sk_buff *skb;

	/* Empty buffer? */
	अगर (buf->next_element_to_fill == 0)
		वापस;

	QETH_TXQ_STAT_INC(queue, bufs);
	QETH_TXQ_STAT_ADD(queue, buf_elements, buf->next_element_to_fill);
	अगर (error) अणु
		QETH_TXQ_STAT_ADD(queue, tx_errors, buf->frames);
	पूर्ण अन्यथा अणु
		QETH_TXQ_STAT_ADD(queue, tx_packets, buf->frames);
		QETH_TXQ_STAT_ADD(queue, tx_bytes, buf->bytes);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&buf->skb_list)) != शून्य) अणु
		अचिन्हित पूर्णांक bytes = qdisc_pkt_len(skb);
		bool is_tso = skb_is_gso(skb);
		अचिन्हित पूर्णांक packets;

		packets = is_tso ? skb_shinfo(skb)->gso_segs : 1;
		अगर (!error) अणु
			अगर (skb->ip_summed == CHECKSUM_PARTIAL)
				QETH_TXQ_STAT_ADD(queue, skbs_csum, packets);
			अगर (skb_is_nonlinear(skb))
				QETH_TXQ_STAT_INC(queue, skbs_sg);
			अगर (is_tso) अणु
				QETH_TXQ_STAT_INC(queue, skbs_tso);
				QETH_TXQ_STAT_ADD(queue, tso_bytes, bytes);
			पूर्ण
		पूर्ण

		napi_consume_skb(skb, budget);
	पूर्ण
पूर्ण

अटल व्योम qeth_clear_output_buffer(काष्ठा qeth_qdio_out_q *queue,
				     काष्ठा qeth_qdio_out_buffer *buf,
				     bool error, पूर्णांक budget)
अणु
	पूर्णांक i;

	/* is PCI flag set on buffer? */
	अगर (buf->buffer->element[0].sflags & SBAL_SFLAGS0_PCI_REQ)
		atomic_dec(&queue->set_pci_flags_count);

	qeth_tx_complete_buf(buf, error, budget);

	क्रम (i = 0; i < queue->max_elements; ++i) अणु
		व्योम *data = phys_to_virt(buf->buffer->element[i].addr);

		अगर (data && buf->is_header[i])
			kmem_cache_मुक्त(qeth_core_header_cache, data);
		buf->is_header[i] = 0;
	पूर्ण

	qeth_scrub_qdio_buffer(buf->buffer, queue->max_elements);
	buf->next_element_to_fill = 0;
	buf->frames = 0;
	buf->bytes = 0;
	atomic_set(&buf->state, QETH_QDIO_BUF_EMPTY);
पूर्ण

अटल व्योम qeth_मुक्त_out_buf(काष्ठा qeth_qdio_out_buffer *buf)
अणु
	अगर (buf->aob)
		qdio_release_aob(buf->aob);
	kmem_cache_मुक्त(qeth_qdio_outbuf_cache, buf);
पूर्ण

अटल व्योम qeth_tx_complete_pending_bufs(काष्ठा qeth_card *card,
					  काष्ठा qeth_qdio_out_q *queue,
					  bool drain, पूर्णांक budget)
अणु
	काष्ठा qeth_qdio_out_buffer *buf, *पंचांगp;

	list_क्रम_each_entry_safe(buf, पंचांगp, &queue->pending_bufs, list_entry) अणु
		अगर (drain || atomic_पढ़ो(&buf->state) == QETH_QDIO_BUF_EMPTY) अणु
			QETH_CARD_TEXT(card, 5, "fp");
			QETH_CARD_TEXT_(card, 5, "%lx", (दीर्घ) buf);

			अगर (drain)
				qeth_notअगरy_skbs(queue, buf,
						 TX_NOTIFY_GENERALERROR);
			qeth_tx_complete_buf(buf, drain, budget);

			list_del(&buf->list_entry);
			qeth_मुक्त_out_buf(buf);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qeth_drain_output_queue(काष्ठा qeth_qdio_out_q *q, bool मुक्त)
अणु
	पूर्णांक j;

	qeth_tx_complete_pending_bufs(q->card, q, true, 0);

	क्रम (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; ++j) अणु
		अगर (!q->bufs[j])
			जारी;

		qeth_clear_output_buffer(q, q->bufs[j], true, 0);
		अगर (मुक्त) अणु
			qeth_मुक्त_out_buf(q->bufs[j]);
			q->bufs[j] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qeth_drain_output_queues(काष्ठा qeth_card *card)
अणु
	पूर्णांक i;

	QETH_CARD_TEXT(card, 2, "clearqdbf");
	/* clear outbound buffers to मुक्त skbs */
	क्रम (i = 0; i < card->qdio.no_out_queues; ++i) अणु
		अगर (card->qdio.out_qs[i])
			qeth_drain_output_queue(card->qdio.out_qs[i], false);
	पूर्ण
पूर्ण

अटल व्योम qeth_osa_set_output_queues(काष्ठा qeth_card *card, bool single)
अणु
	अचिन्हित पूर्णांक max = single ? 1 : card->dev->num_tx_queues;

	अगर (card->qdio.no_out_queues == max)
		वापस;

	अगर (atomic_पढ़ो(&card->qdio.state) != QETH_QDIO_UNINITIALIZED)
		qeth_मुक्त_qdio_queues(card);

	अगर (max == 1 && card->qdio.करो_prio_queueing != QETH_PRIOQ_DEFAULT)
		dev_info(&card->gdev->dev, "Priority Queueing not supported\n");

	card->qdio.no_out_queues = max;
पूर्ण

अटल पूर्णांक qeth_update_from_chp_desc(काष्ठा qeth_card *card)
अणु
	काष्ठा ccw_device *ccwdev;
	काष्ठा channel_path_desc_fmt0 *chp_dsc;

	QETH_CARD_TEXT(card, 2, "chp_desc");

	ccwdev = card->data.ccwdev;
	chp_dsc = ccw_device_get_chp_desc(ccwdev, 0);
	अगर (!chp_dsc)
		वापस -ENOMEM;

	card->info.func_level = 0x4100 + chp_dsc->desc;

	अगर (IS_OSD(card) || IS_OSX(card))
		/* CHPP field bit 6 == 1 -> single queue */
		qeth_osa_set_output_queues(card, chp_dsc->chpp & 0x02);

	kमुक्त(chp_dsc);
	QETH_CARD_TEXT_(card, 2, "nr:%x", card->qdio.no_out_queues);
	QETH_CARD_TEXT_(card, 2, "lvl:%02x", card->info.func_level);
	वापस 0;
पूर्ण

अटल व्योम qeth_init_qdio_info(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 4, "intqdinf");
	atomic_set(&card->qdio.state, QETH_QDIO_UNINITIALIZED);
	card->qdio.करो_prio_queueing = QETH_PRIOQ_DEFAULT;
	card->qdio.शेष_out_queue = QETH_DEFAULT_QUEUE;

	/* inbound */
	card->qdio.no_in_queues = 1;
	card->qdio.in_buf_size = QETH_IN_BUF_SIZE_DEFAULT;
	अगर (IS_IQD(card))
		card->qdio.init_pool.buf_count = QETH_IN_BUF_COUNT_HSDEFAULT;
	अन्यथा
		card->qdio.init_pool.buf_count = QETH_IN_BUF_COUNT_DEFAULT;
	card->qdio.in_buf_pool.buf_count = card->qdio.init_pool.buf_count;
	INIT_LIST_HEAD(&card->qdio.in_buf_pool.entry_list);
	INIT_LIST_HEAD(&card->qdio.init_pool.entry_list);
पूर्ण

अटल व्योम qeth_set_initial_options(काष्ठा qeth_card *card)
अणु
	card->options.route4.type = NO_ROUTER;
	card->options.route6.type = NO_ROUTER;
	card->options.isolation = ISOLATION_MODE_NONE;
	card->options.cq = QETH_CQ_DISABLED;
	card->options.layer = QETH_DISCIPLINE_UNDETERMINED;
पूर्ण

अटल पूर्णांक qeth_करो_start_thपढ़ो(काष्ठा qeth_card *card, अचिन्हित दीर्घ thपढ़ो)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	spin_lock_irqsave(&card->thपढ़ो_mask_lock, flags);
	QETH_CARD_TEXT_(card, 4, "  %02x%02x%02x",
			(u8) card->thपढ़ो_start_mask,
			(u8) card->thपढ़ो_allowed_mask,
			(u8) card->thपढ़ो_running_mask);
	rc = (card->thपढ़ो_start_mask & thपढ़ो);
	spin_unlock_irqrestore(&card->thपढ़ो_mask_lock, flags);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_करो_reset(व्योम *data);
अटल व्योम qeth_start_kernel_thपढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा task_काष्ठा *ts;
	काष्ठा qeth_card *card = container_of(work, काष्ठा qeth_card,
					kernel_thपढ़ो_starter);
	QETH_CARD_TEXT(card, 2, "strthrd");

	अगर (card->पढ़ो.state != CH_STATE_UP &&
	    card->ग_लिखो.state != CH_STATE_UP)
		वापस;
	अगर (qeth_करो_start_thपढ़ो(card, QETH_RECOVER_THREAD)) अणु
		ts = kthपढ़ो_run(qeth_करो_reset, card, "qeth_recover");
		अगर (IS_ERR(ts)) अणु
			qeth_clear_thपढ़ो_start_bit(card, QETH_RECOVER_THREAD);
			qeth_clear_thपढ़ो_running_bit(card,
				QETH_RECOVER_THREAD);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qeth_buffer_reclaim_work(काष्ठा work_काष्ठा *);
अटल व्योम qeth_setup_card(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 2, "setupcrd");

	card->info.type = CARD_RDEV(card)->id.driver_info;
	card->state = CARD_STATE_DOWN;
	spin_lock_init(&card->lock);
	spin_lock_init(&card->thपढ़ो_mask_lock);
	mutex_init(&card->conf_mutex);
	mutex_init(&card->discipline_mutex);
	INIT_WORK(&card->kernel_thपढ़ो_starter, qeth_start_kernel_thपढ़ो);
	INIT_LIST_HEAD(&card->cmd_रुकोer_list);
	init_रुकोqueue_head(&card->रुको_q);
	qeth_set_initial_options(card);
	/* IP address takeover */
	INIT_LIST_HEAD(&card->ipato.entries);
	qeth_init_qdio_info(card);
	INIT_DELAYED_WORK(&card->buffer_reclaim_work, qeth_buffer_reclaim_work);
	INIT_WORK(&card->बंद_dev_work, qeth_बंद_dev_handler);
	hash_init(card->rx_mode_addrs);
	hash_init(card->local_addrs4);
	hash_init(card->local_addrs6);
	spin_lock_init(&card->local_addrs4_lock);
	spin_lock_init(&card->local_addrs6_lock);
पूर्ण

अटल व्योम qeth_core_sl_prपूर्णांक(काष्ठा seq_file *m, काष्ठा service_level *slr)
अणु
	काष्ठा qeth_card *card = container_of(slr, काष्ठा qeth_card,
					qeth_service_level);
	अगर (card->info.mcl_level[0])
		seq_म_लिखो(m, "qeth: %s firmware level %s\n",
			CARD_BUS_ID(card), card->info.mcl_level);
पूर्ण

अटल काष्ठा qeth_card *qeth_alloc_card(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card;

	QETH_DBF_TEXT(SETUP, 2, "alloccrd");
	card = kzalloc(माप(*card), GFP_KERNEL);
	अगर (!card)
		जाओ out;
	QETH_DBF_HEX(SETUP, 2, &card, माप(व्योम *));

	card->gdev = gdev;
	dev_set_drvdata(&gdev->dev, card);
	CARD_RDEV(card) = gdev->cdev[0];
	CARD_WDEV(card) = gdev->cdev[1];
	CARD_DDEV(card) = gdev->cdev[2];

	card->event_wq = alloc_ordered_workqueue("%s_event", 0,
						 dev_name(&gdev->dev));
	अगर (!card->event_wq)
		जाओ out_wq;

	card->पढ़ो_cmd = qeth_alloc_cmd(&card->पढ़ो, QETH_बफ_मानE, 1, 0);
	अगर (!card->पढ़ो_cmd)
		जाओ out_पढ़ो_cmd;

	card->debugfs = debugfs_create_dir(dev_name(&gdev->dev),
					   qeth_debugfs_root);
	debugfs_create_file("local_addrs", 0400, card->debugfs, card,
			    &qeth_debugfs_local_addr_fops);

	card->qeth_service_level.seq_prपूर्णांक = qeth_core_sl_prपूर्णांक;
	रेजिस्टर_service_level(&card->qeth_service_level);
	वापस card;

out_पढ़ो_cmd:
	destroy_workqueue(card->event_wq);
out_wq:
	dev_set_drvdata(&gdev->dev, शून्य);
	kमुक्त(card);
out:
	वापस शून्य;
पूर्ण

अटल पूर्णांक qeth_clear_channel(काष्ठा qeth_card *card,
			      काष्ठा qeth_channel *channel)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "clearch");
	spin_lock_irq(get_ccwdev_lock(channel->ccwdev));
	rc = ccw_device_clear(channel->ccwdev, (addr_t)channel->active_cmd);
	spin_unlock_irq(get_ccwdev_lock(channel->ccwdev));

	अगर (rc)
		वापस rc;
	rc = रुको_event_पूर्णांकerruptible_समयout(card->रुको_q,
			channel->state == CH_STATE_STOPPED, QETH_TIMEOUT);
	अगर (rc == -ERESTARTSYS)
		वापस rc;
	अगर (channel->state != CH_STATE_STOPPED)
		वापस -ETIME;
	channel->state = CH_STATE_DOWN;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_halt_channel(काष्ठा qeth_card *card,
			     काष्ठा qeth_channel *channel)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 3, "haltch");
	spin_lock_irq(get_ccwdev_lock(channel->ccwdev));
	rc = ccw_device_halt(channel->ccwdev, (addr_t)channel->active_cmd);
	spin_unlock_irq(get_ccwdev_lock(channel->ccwdev));

	अगर (rc)
		वापस rc;
	rc = रुको_event_पूर्णांकerruptible_समयout(card->रुको_q,
			channel->state == CH_STATE_HALTED, QETH_TIMEOUT);
	अगर (rc == -ERESTARTSYS)
		वापस rc;
	अगर (channel->state != CH_STATE_HALTED)
		वापस -ETIME;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_stop_channel(काष्ठा qeth_channel *channel)
अणु
	काष्ठा ccw_device *cdev = channel->ccwdev;
	पूर्णांक rc;

	rc = ccw_device_set_offline(cdev);

	spin_lock_irq(get_ccwdev_lock(cdev));
	अगर (channel->active_cmd) अणु
		dev_err(&cdev->dev, "Stopped channel while cmd %px was still active\n",
			channel->active_cmd);
		channel->active_cmd = शून्य;
	पूर्ण
	cdev->handler = शून्य;
	spin_unlock_irq(get_ccwdev_lock(cdev));

	वापस rc;
पूर्ण

अटल पूर्णांक qeth_start_channel(काष्ठा qeth_channel *channel)
अणु
	काष्ठा ccw_device *cdev = channel->ccwdev;
	पूर्णांक rc;

	channel->state = CH_STATE_DOWN;
	atomic_set(&channel->irq_pending, 0);

	spin_lock_irq(get_ccwdev_lock(cdev));
	cdev->handler = qeth_irq;
	spin_unlock_irq(get_ccwdev_lock(cdev));

	rc = ccw_device_set_online(cdev);
	अगर (rc)
		जाओ err;

	वापस 0;

err:
	spin_lock_irq(get_ccwdev_lock(cdev));
	cdev->handler = शून्य;
	spin_unlock_irq(get_ccwdev_lock(cdev));
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_halt_channels(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc1 = 0, rc2 = 0, rc3 = 0;

	QETH_CARD_TEXT(card, 3, "haltchs");
	rc1 = qeth_halt_channel(card, &card->पढ़ो);
	rc2 = qeth_halt_channel(card, &card->ग_लिखो);
	rc3 = qeth_halt_channel(card, &card->data);
	अगर (rc1)
		वापस rc1;
	अगर (rc2)
		वापस rc2;
	वापस rc3;
पूर्ण

अटल पूर्णांक qeth_clear_channels(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc1 = 0, rc2 = 0, rc3 = 0;

	QETH_CARD_TEXT(card, 3, "clearchs");
	rc1 = qeth_clear_channel(card, &card->पढ़ो);
	rc2 = qeth_clear_channel(card, &card->ग_लिखो);
	rc3 = qeth_clear_channel(card, &card->data);
	अगर (rc1)
		वापस rc1;
	अगर (rc2)
		वापस rc2;
	वापस rc3;
पूर्ण

अटल पूर्णांक qeth_clear_halt_card(काष्ठा qeth_card *card, पूर्णांक halt)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 3, "clhacrd");

	अगर (halt)
		rc = qeth_halt_channels(card);
	अगर (rc)
		वापस rc;
	वापस qeth_clear_channels(card);
पूर्ण

अटल पूर्णांक qeth_qdio_clear_card(काष्ठा qeth_card *card, पूर्णांक use_halt)
अणु
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 3, "qdioclr");
	चयन (atomic_cmpxchg(&card->qdio.state, QETH_QDIO_ESTABLISHED,
		QETH_QDIO_CLEANING)) अणु
	हाल QETH_QDIO_ESTABLISHED:
		अगर (IS_IQD(card))
			rc = qdio_shutकरोwn(CARD_DDEV(card),
				QDIO_FLAG_CLEANUP_USING_HALT);
		अन्यथा
			rc = qdio_shutकरोwn(CARD_DDEV(card),
				QDIO_FLAG_CLEANUP_USING_CLEAR);
		अगर (rc)
			QETH_CARD_TEXT_(card, 3, "1err%d", rc);
		atomic_set(&card->qdio.state, QETH_QDIO_ALLOCATED);
		अवरोध;
	हाल QETH_QDIO_CLEANING:
		वापस rc;
	शेष:
		अवरोध;
	पूर्ण
	rc = qeth_clear_halt_card(card, use_halt);
	अगर (rc)
		QETH_CARD_TEXT_(card, 3, "2err%d", rc);
	वापस rc;
पूर्ण

अटल क्रमागत qeth_discipline_id qeth_vm_detect_layer(काष्ठा qeth_card *card)
अणु
	क्रमागत qeth_discipline_id disc = QETH_DISCIPLINE_UNDETERMINED;
	काष्ठा diag26c_vnic_resp *response = शून्य;
	काष्ठा diag26c_vnic_req *request = शून्य;
	काष्ठा ccw_dev_id id;
	अक्षर userid[80];
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "vmlayer");

	cpcmd("QUERY USERID", userid, माप(userid), &rc);
	अगर (rc)
		जाओ out;

	request = kzalloc(माप(*request), GFP_KERNEL | GFP_DMA);
	response = kzalloc(माप(*response), GFP_KERNEL | GFP_DMA);
	अगर (!request || !response) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	ccw_device_get_id(CARD_RDEV(card), &id);
	request->resp_buf_len = माप(*response);
	request->resp_version = DIAG26C_VERSION6_VM65918;
	request->req_क्रमmat = DIAG26C_VNIC_INFO;
	ASCEBC(userid, 8);
	स_नकल(&request->sys_name, userid, 8);
	request->devno = id.devno;

	QETH_DBF_HEX(CTRL, 2, request, माप(*request));
	rc = diag26c(request, response, DIAG26C_PORT_VNIC);
	QETH_DBF_HEX(CTRL, 2, request, माप(*request));
	अगर (rc)
		जाओ out;
	QETH_DBF_HEX(CTRL, 2, response, माप(*response));

	अगर (request->resp_buf_len < माप(*response) ||
	    response->version != request->resp_version) अणु
		rc = -EIO;
		जाओ out;
	पूर्ण

	अगर (response->protocol == VNIC_INFO_PROT_L2)
		disc = QETH_DISCIPLINE_LAYER2;
	अन्यथा अगर (response->protocol == VNIC_INFO_PROT_L3)
		disc = QETH_DISCIPLINE_LAYER3;

out:
	kमुक्त(response);
	kमुक्त(request);
	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "err%x", rc);
	वापस disc;
पूर्ण

/* Determine whether the device requires a specअगरic layer discipline */
अटल क्रमागत qeth_discipline_id qeth_enक्रमce_discipline(काष्ठा qeth_card *card)
अणु
	क्रमागत qeth_discipline_id disc = QETH_DISCIPLINE_UNDETERMINED;

	अगर (IS_OSM(card) || IS_OSN(card))
		disc = QETH_DISCIPLINE_LAYER2;
	अन्यथा अगर (IS_VM_NIC(card))
		disc = IS_IQD(card) ? QETH_DISCIPLINE_LAYER3 :
				      qeth_vm_detect_layer(card);

	चयन (disc) अणु
	हाल QETH_DISCIPLINE_LAYER2:
		QETH_CARD_TEXT(card, 3, "force l2");
		अवरोध;
	हाल QETH_DISCIPLINE_LAYER3:
		QETH_CARD_TEXT(card, 3, "force l3");
		अवरोध;
	शेष:
		QETH_CARD_TEXT(card, 3, "force no");
	पूर्ण

	वापस disc;
पूर्ण

अटल व्योम qeth_set_blkt_शेषs(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 2, "cfgblkt");

	अगर (card->info.use_v1_blkt) अणु
		card->info.blkt.समय_प्रकारotal = 0;
		card->info.blkt.पूर्णांकer_packet = 0;
		card->info.blkt.पूर्णांकer_packet_jumbo = 0;
	पूर्ण अन्यथा अणु
		card->info.blkt.समय_प्रकारotal = 250;
		card->info.blkt.पूर्णांकer_packet = 5;
		card->info.blkt.पूर्णांकer_packet_jumbo = 15;
	पूर्ण
पूर्ण

अटल व्योम qeth_idx_init(काष्ठा qeth_card *card)
अणु
	स_रखो(&card->seqno, 0, माप(card->seqno));

	card->token.issuer_rm_w = 0x00010103UL;
	card->token.cm_filter_w = 0x00010108UL;
	card->token.cm_connection_w = 0x0001010aUL;
	card->token.ulp_filter_w = 0x0001010bUL;
	card->token.ulp_connection_w = 0x0001010dUL;

	चयन (card->info.type) अणु
	हाल QETH_CARD_TYPE_IQD:
		card->info.func_level =	QETH_IDX_FUNC_LEVEL_IQD;
		अवरोध;
	हाल QETH_CARD_TYPE_OSD:
	हाल QETH_CARD_TYPE_OSN:
		card->info.func_level = QETH_IDX_FUNC_LEVEL_OSD;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qeth_idx_finalize_cmd(काष्ठा qeth_card *card,
				  काष्ठा qeth_cmd_buffer *iob)
अणु
	स_नकल(QETH_TRANSPORT_HEADER_SEQ_NO(iob->data), &card->seqno.trans_hdr,
	       QETH_SEQ_NO_LENGTH);
	अगर (iob->channel == &card->ग_लिखो)
		card->seqno.trans_hdr++;
पूर्ण

अटल पूर्णांक qeth_peer_func_level(पूर्णांक level)
अणु
	अगर ((level & 0xff) == 8)
		वापस (level & 0xff) + 0x400;
	अगर (((level >> 8) & 3) == 1)
		वापस (level & 0xff) + 0x200;
	वापस level;
पूर्ण

अटल व्योम qeth_mpc_finalize_cmd(काष्ठा qeth_card *card,
				  काष्ठा qeth_cmd_buffer *iob)
अणु
	qeth_idx_finalize_cmd(card, iob);

	स_नकल(QETH_PDU_HEADER_SEQ_NO(iob->data),
	       &card->seqno.pdu_hdr, QETH_SEQ_NO_LENGTH);
	card->seqno.pdu_hdr++;
	स_नकल(QETH_PDU_HEADER_ACK_SEQ_NO(iob->data),
	       &card->seqno.pdu_hdr_ack, QETH_SEQ_NO_LENGTH);

	iob->callback = qeth_release_buffer_cb;
पूर्ण

अटल bool qeth_mpc_match_reply(काष्ठा qeth_cmd_buffer *iob,
				 काष्ठा qeth_cmd_buffer *reply)
अणु
	/* MPC cmds are issued strictly in sequence. */
	वापस !IS_IPA(reply->data);
पूर्ण

अटल काष्ठा qeth_cmd_buffer *qeth_mpc_alloc_cmd(काष्ठा qeth_card *card,
						  स्थिर व्योम *data,
						  अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	iob = qeth_alloc_cmd(&card->ग_लिखो, data_length, 1, QETH_TIMEOUT);
	अगर (!iob)
		वापस शून्य;

	स_नकल(iob->data, data, data_length);
	qeth_setup_ccw(__ccw_from_cmd(iob), CCW_CMD_WRITE, 0, data_length,
		       iob->data);
	iob->finalize = qeth_mpc_finalize_cmd;
	iob->match = qeth_mpc_match_reply;
	वापस iob;
पूर्ण

/**
 * qeth_send_control_data() -	send control command to the card
 * @card:			qeth_card काष्ठाure poपूर्णांकer
 * @iob:			qeth_cmd_buffer poपूर्णांकer
 * @reply_cb:			callback function poपूर्णांकer
 * @cb_card:			poपूर्णांकer to the qeth_card काष्ठाure
 * @cb_reply:			poपूर्णांकer to the qeth_reply काष्ठाure
 * @cb_cmd:			poपूर्णांकer to the original iob क्रम non-IPA
 *				commands, or to the qeth_ipa_cmd काष्ठाure
 *				क्रम the IPA commands.
 * @reply_param:		निजी poपूर्णांकer passed to the callback
 *
 * Callback function माला_लो called one or more बार, with cb_cmd
 * poपूर्णांकing to the response वापसed by the hardware. Callback
 * function must वापस
 *   > 0 अगर more reply blocks are expected,
 *     0 अगर the last or only reply block is received, and
 *   < 0 on error.
 * Callback function can get the value of the reply_param poपूर्णांकer from the
 * field 'param' of the काष्ठाure qeth_reply.
 */

अटल पूर्णांक qeth_send_control_data(काष्ठा qeth_card *card,
				  काष्ठा qeth_cmd_buffer *iob,
				  पूर्णांक (*reply_cb)(काष्ठा qeth_card *cb_card,
						  काष्ठा qeth_reply *cb_reply,
						  अचिन्हित दीर्घ cb_cmd),
				  व्योम *reply_param)
अणु
	काष्ठा qeth_channel *channel = iob->channel;
	काष्ठा qeth_reply *reply = &iob->reply;
	दीर्घ समयout = iob->समयout;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "sendctl");

	reply->callback = reply_cb;
	reply->param = reply_param;

	समयout = रुको_event_पूर्णांकerruptible_समयout(card->रुको_q,
						   qeth_trylock_channel(channel),
						   समयout);
	अगर (समयout <= 0) अणु
		qeth_put_cmd(iob);
		वापस (समयout == -ERESTARTSYS) ? -EINTR : -ETIME;
	पूर्ण

	अगर (iob->finalize)
		iob->finalize(card, iob);
	QETH_DBF_HEX(CTRL, 2, iob->data, min(iob->length, QETH_DBF_CTRL_LEN));

	qeth_enqueue_cmd(card, iob);

	/* This pairs with iob->callback, and keeps the iob alive after IO: */
	qeth_get_cmd(iob);

	QETH_CARD_TEXT(card, 6, "noirqpnd");
	spin_lock_irq(get_ccwdev_lock(channel->ccwdev));
	rc = ccw_device_start_समयout(channel->ccwdev, __ccw_from_cmd(iob),
				      (addr_t) iob, 0, 0, समयout);
	अगर (!rc)
		channel->active_cmd = iob;
	spin_unlock_irq(get_ccwdev_lock(channel->ccwdev));
	अगर (rc) अणु
		QETH_DBF_MESSAGE(2, "qeth_send_control_data on device %x: ccw_device_start rc = %i\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, " err%d", rc);
		qeth_dequeue_cmd(card, iob);
		qeth_put_cmd(iob);
		qeth_unlock_channel(card, channel);
		जाओ out;
	पूर्ण

	समयout = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&iob->करोne,
							    समयout);
	अगर (समयout <= 0)
		rc = (समयout == -ERESTARTSYS) ? -EINTR : -ETIME;

	qeth_dequeue_cmd(card, iob);

	अगर (reply_cb) अणु
		/* Wait until the callback क्रम a late reply has completed: */
		spin_lock_irq(&iob->lock);
		अगर (rc)
			/* Zap any callback that's still pending: */
			iob->rc = rc;
		spin_unlock_irq(&iob->lock);
	पूर्ण

	अगर (!rc)
		rc = iob->rc;

out:
	qeth_put_cmd(iob);
	वापस rc;
पूर्ण

काष्ठा qeth_node_desc अणु
	काष्ठा node_descriptor nd1;
	काष्ठा node_descriptor nd2;
	काष्ठा node_descriptor nd3;
पूर्ण;

अटल व्योम qeth_पढ़ो_conf_data_cb(काष्ठा qeth_card *card,
				   काष्ठा qeth_cmd_buffer *iob,
				   अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_node_desc *nd = (काष्ठा qeth_node_desc *) iob->data;
	पूर्णांक rc = 0;
	u8 *tag;

	QETH_CARD_TEXT(card, 2, "cfgunit");

	अगर (data_length < माप(*nd)) अणु
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	card->info.is_vm_nic = nd->nd1.plant[0] == _ascebc['V'] &&
			       nd->nd1.plant[1] == _ascebc['M'];
	tag = (u8 *)&nd->nd1.tag;
	card->info.chpid = tag[0];
	card->info.unit_addr2 = tag[1];

	tag = (u8 *)&nd->nd2.tag;
	card->info.cula = tag[1];

	card->info.use_v1_blkt = nd->nd3.model[0] == 0xF0 &&
				 nd->nd3.model[1] == 0xF0 &&
				 nd->nd3.model[2] >= 0xF1 &&
				 nd->nd3.model[2] <= 0xF4;

out:
	qeth_notअगरy_cmd(iob, rc);
	qeth_put_cmd(iob);
पूर्ण

अटल पूर्णांक qeth_पढ़ो_conf_data(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_channel *channel = &card->data;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा ciw *ciw;

	/* scan क्रम RCD command in extended SenseID data */
	ciw = ccw_device_get_ciw(channel->ccwdev, CIW_TYPE_RCD);
	अगर (!ciw || ciw->cmd == 0)
		वापस -EOPNOTSUPP;
	अगर (ciw->count < माप(काष्ठा qeth_node_desc))
		वापस -EINVAL;

	iob = qeth_alloc_cmd(channel, ciw->count, 1, QETH_RCD_TIMEOUT);
	अगर (!iob)
		वापस -ENOMEM;

	iob->callback = qeth_पढ़ो_conf_data_cb;
	qeth_setup_ccw(__ccw_from_cmd(iob), ciw->cmd, 0, iob->length,
		       iob->data);

	वापस qeth_send_control_data(card, iob, शून्य, शून्य);
पूर्ण

अटल पूर्णांक qeth_idx_check_activate_response(काष्ठा qeth_card *card,
					    काष्ठा qeth_channel *channel,
					    काष्ठा qeth_cmd_buffer *iob)
अणु
	पूर्णांक rc;

	rc = qeth_check_idx_response(card, iob->data);
	अगर (rc)
		वापस rc;

	अगर (QETH_IS_IDX_ACT_POS_REPLY(iob->data))
		वापस 0;

	/* negative reply: */
	QETH_CARD_TEXT_(card, 2, "idxneg%c",
			QETH_IDX_ACT_CAUSE_CODE(iob->data));

	चयन (QETH_IDX_ACT_CAUSE_CODE(iob->data)) अणु
	हाल QETH_IDX_ACT_ERR_EXCL:
		dev_err(&channel->ccwdev->dev,
			"The adapter is used exclusively by another host\n");
		वापस -EBUSY;
	हाल QETH_IDX_ACT_ERR_AUTH:
	हाल QETH_IDX_ACT_ERR_AUTH_USER:
		dev_err(&channel->ccwdev->dev,
			"Setting the device online failed because of insufficient authorization\n");
		वापस -EPERM;
	शेष:
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channel %x: negative reply\n",
				 CCW_DEVID(channel->ccwdev));
		वापस -EIO;
	पूर्ण
पूर्ण

अटल व्योम qeth_idx_activate_पढ़ो_channel_cb(काष्ठा qeth_card *card,
					      काष्ठा qeth_cmd_buffer *iob,
					      अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_channel *channel = iob->channel;
	u16 peer_level;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "idxrdcb");

	rc = qeth_idx_check_activate_response(card, channel, iob);
	अगर (rc)
		जाओ out;

	स_नकल(&peer_level, QETH_IDX_ACT_FUNC_LEVEL(iob->data), 2);
	अगर (peer_level != qeth_peer_func_level(card->info.func_level)) अणु
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channel %x: function level mismatch (sent: %#x, received: %#x)\n",
				 CCW_DEVID(channel->ccwdev),
				 card->info.func_level, peer_level);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(&card->token.issuer_rm_r,
	       QETH_IDX_ACT_ISSUER_RM_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	स_नकल(&card->info.mcl_level[0],
	       QETH_IDX_REPLY_LEVEL(iob->data), QETH_MCL_LENGTH);

out:
	qeth_notअगरy_cmd(iob, rc);
	qeth_put_cmd(iob);
पूर्ण

अटल व्योम qeth_idx_activate_ग_लिखो_channel_cb(काष्ठा qeth_card *card,
					       काष्ठा qeth_cmd_buffer *iob,
					       अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_channel *channel = iob->channel;
	u16 peer_level;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "idxwrcb");

	rc = qeth_idx_check_activate_response(card, channel, iob);
	अगर (rc)
		जाओ out;

	स_नकल(&peer_level, QETH_IDX_ACT_FUNC_LEVEL(iob->data), 2);
	अगर ((peer_level & ~0x0100) !=
	    qeth_peer_func_level(card->info.func_level)) अणु
		QETH_DBF_MESSAGE(2, "IDX_ACTIVATE on channel %x: function level mismatch (sent: %#x, received: %#x)\n",
				 CCW_DEVID(channel->ccwdev),
				 card->info.func_level, peer_level);
		rc = -EINVAL;
	पूर्ण

out:
	qeth_notअगरy_cmd(iob, rc);
	qeth_put_cmd(iob);
पूर्ण

अटल व्योम qeth_idx_setup_activate_cmd(काष्ठा qeth_card *card,
					काष्ठा qeth_cmd_buffer *iob)
अणु
	u16 addr = (card->info.cula << 8) + card->info.unit_addr2;
	u8 port = ((u8)card->dev->dev_port) | 0x80;
	काष्ठा ccw1 *ccw = __ccw_from_cmd(iob);

	qeth_setup_ccw(&ccw[0], CCW_CMD_WRITE, CCW_FLAG_CC, IDX_ACTIVATE_SIZE,
		       iob->data);
	qeth_setup_ccw(&ccw[1], CCW_CMD_READ, 0, iob->length, iob->data);
	iob->finalize = qeth_idx_finalize_cmd;

	port |= QETH_IDX_ACT_INVAL_FRAME;
	स_नकल(QETH_IDX_ACT_PNO(iob->data), &port, 1);
	स_नकल(QETH_IDX_ACT_ISSUER_RM_TOKEN(iob->data),
	       &card->token.issuer_rm_w, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_IDX_ACT_FUNC_LEVEL(iob->data),
	       &card->info.func_level, 2);
	स_नकल(QETH_IDX_ACT_QDIO_DEV_CUA(iob->data), &card->info.ddev_devno, 2);
	स_नकल(QETH_IDX_ACT_QDIO_DEV_REALADDR(iob->data), &addr, 2);
पूर्ण

अटल पूर्णांक qeth_idx_activate_पढ़ो_channel(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_channel *channel = &card->पढ़ो;
	काष्ठा qeth_cmd_buffer *iob;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "idxread");

	iob = qeth_alloc_cmd(channel, QETH_बफ_मानE, 2, QETH_TIMEOUT);
	अगर (!iob)
		वापस -ENOMEM;

	स_नकल(iob->data, IDX_ACTIVATE_READ, IDX_ACTIVATE_SIZE);
	qeth_idx_setup_activate_cmd(card, iob);
	iob->callback = qeth_idx_activate_पढ़ो_channel_cb;

	rc = qeth_send_control_data(card, iob, शून्य, शून्य);
	अगर (rc)
		वापस rc;

	channel->state = CH_STATE_UP;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_idx_activate_ग_लिखो_channel(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_channel *channel = &card->ग_लिखो;
	काष्ठा qeth_cmd_buffer *iob;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "idxwrite");

	iob = qeth_alloc_cmd(channel, QETH_बफ_मानE, 2, QETH_TIMEOUT);
	अगर (!iob)
		वापस -ENOMEM;

	स_नकल(iob->data, IDX_ACTIVATE_WRITE, IDX_ACTIVATE_SIZE);
	qeth_idx_setup_activate_cmd(card, iob);
	iob->callback = qeth_idx_activate_ग_लिखो_channel_cb;

	rc = qeth_send_control_data(card, iob, शून्य, शून्य);
	अगर (rc)
		वापस rc;

	channel->state = CH_STATE_UP;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_cm_enable_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
		अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "cmenblcb");

	iob = (काष्ठा qeth_cmd_buffer *) data;
	स_नकल(&card->token.cm_filter_r,
	       QETH_CM_ENABLE_RESP_FILTER_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_cm_enable(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "cmenable");

	iob = qeth_mpc_alloc_cmd(card, CM_ENABLE, CM_ENABLE_SIZE);
	अगर (!iob)
		वापस -ENOMEM;

	स_नकल(QETH_CM_ENABLE_ISSUER_RM_TOKEN(iob->data),
	       &card->token.issuer_rm_r, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_CM_ENABLE_FILTER_TOKEN(iob->data),
	       &card->token.cm_filter_w, QETH_MPC_TOKEN_LENGTH);

	वापस qeth_send_control_data(card, iob, qeth_cm_enable_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_cm_setup_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
		अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "cmsetpcb");

	iob = (काष्ठा qeth_cmd_buffer *) data;
	स_नकल(&card->token.cm_connection_r,
	       QETH_CM_SETUP_RESP_DEST_ADDR(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_cm_setup(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "cmsetup");

	iob = qeth_mpc_alloc_cmd(card, CM_SETUP, CM_SETUP_SIZE);
	अगर (!iob)
		वापस -ENOMEM;

	स_नकल(QETH_CM_SETUP_DEST_ADDR(iob->data),
	       &card->token.issuer_rm_r, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_CM_SETUP_CONNECTION_TOKEN(iob->data),
	       &card->token.cm_connection_w, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_CM_SETUP_FILTER_TOKEN(iob->data),
	       &card->token.cm_filter_r, QETH_MPC_TOKEN_LENGTH);
	वापस qeth_send_control_data(card, iob, qeth_cm_setup_cb, शून्य);
पूर्ण

अटल bool qeth_is_supported_link_type(काष्ठा qeth_card *card, u8 link_type)
अणु
	अगर (link_type == QETH_LINK_TYPE_LANE_TR ||
	    link_type == QETH_LINK_TYPE_HSTR) अणु
		dev_err(&card->gdev->dev, "Unsupported Token Ring device\n");
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक qeth_update_max_mtu(काष्ठा qeth_card *card, अचिन्हित पूर्णांक max_mtu)
अणु
	काष्ठा net_device *dev = card->dev;
	अचिन्हित पूर्णांक new_mtu;

	अगर (!max_mtu) अणु
		/* IQD needs accurate max MTU to set up its RX buffers: */
		अगर (IS_IQD(card))
			वापस -EINVAL;
		/* tolerate quirky HW: */
		max_mtu = ETH_MAX_MTU;
	पूर्ण

	rtnl_lock();
	अगर (IS_IQD(card)) अणु
		/* move any device with शेष MTU to new max MTU: */
		new_mtu = (dev->mtu == dev->max_mtu) ? max_mtu : dev->mtu;

		/* adjust RX buffer size to new max MTU: */
		card->qdio.in_buf_size = max_mtu + 2 * PAGE_SIZE;
		अगर (dev->max_mtu && dev->max_mtu != max_mtu)
			qeth_मुक्त_qdio_queues(card);
	पूर्ण अन्यथा अणु
		अगर (dev->mtu)
			new_mtu = dev->mtu;
		/* शेष MTUs क्रम first setup: */
		अन्यथा अगर (IS_LAYER2(card))
			new_mtu = ETH_DATA_LEN;
		अन्यथा
			new_mtu = ETH_DATA_LEN - 8; /* allow क्रम LLC + SNAP */
	पूर्ण

	dev->max_mtu = max_mtu;
	dev->mtu = min(new_mtu, max_mtu);
	rtnl_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_get_mtu_outof_framesize(पूर्णांक framesize)
अणु
	चयन (framesize) अणु
	हाल 0x4000:
		वापस 8192;
	हाल 0x6000:
		वापस 16384;
	हाल 0xa000:
		वापस 32768;
	हाल 0xffff:
		वापस 57344;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_ulp_enable_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
		अचिन्हित दीर्घ data)
अणु
	__u16 mtu, framesize;
	__u16 len;
	काष्ठा qeth_cmd_buffer *iob;
	u8 link_type = 0;

	QETH_CARD_TEXT(card, 2, "ulpenacb");

	iob = (काष्ठा qeth_cmd_buffer *) data;
	स_नकल(&card->token.ulp_filter_r,
	       QETH_ULP_ENABLE_RESP_FILTER_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	अगर (IS_IQD(card)) अणु
		स_नकल(&framesize, QETH_ULP_ENABLE_RESP_MAX_MTU(iob->data), 2);
		mtu = qeth_get_mtu_outof_framesize(framesize);
	पूर्ण अन्यथा अणु
		mtu = *(__u16 *)QETH_ULP_ENABLE_RESP_MAX_MTU(iob->data);
	पूर्ण
	*(u16 *)reply->param = mtu;

	स_नकल(&len, QETH_ULP_ENABLE_RESP_DIFINFO_LEN(iob->data), 2);
	अगर (len >= QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE) अणु
		स_नकल(&link_type,
		       QETH_ULP_ENABLE_RESP_LINK_TYPE(iob->data), 1);
		अगर (!qeth_is_supported_link_type(card, link_type))
			वापस -EPROTONOSUPPORT;
	पूर्ण

	card->info.link_type = link_type;
	QETH_CARD_TEXT_(card, 2, "link%d", card->info.link_type);
	वापस 0;
पूर्ण

अटल u8 qeth_mpc_select_prot_type(काष्ठा qeth_card *card)
अणु
	अगर (IS_OSN(card))
		वापस QETH_PROT_OSN2;
	वापस IS_LAYER2(card) ? QETH_PROT_LAYER2 : QETH_PROT_TCPIP;
पूर्ण

अटल पूर्णांक qeth_ulp_enable(काष्ठा qeth_card *card)
अणु
	u8 prot_type = qeth_mpc_select_prot_type(card);
	काष्ठा qeth_cmd_buffer *iob;
	u16 max_mtu;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "ulpenabl");

	iob = qeth_mpc_alloc_cmd(card, ULP_ENABLE, ULP_ENABLE_SIZE);
	अगर (!iob)
		वापस -ENOMEM;

	*(QETH_ULP_ENABLE_LINKNUM(iob->data)) = (u8) card->dev->dev_port;
	स_नकल(QETH_ULP_ENABLE_PROT_TYPE(iob->data), &prot_type, 1);
	स_नकल(QETH_ULP_ENABLE_DEST_ADDR(iob->data),
	       &card->token.cm_connection_r, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_ULP_ENABLE_FILTER_TOKEN(iob->data),
	       &card->token.ulp_filter_w, QETH_MPC_TOKEN_LENGTH);
	rc = qeth_send_control_data(card, iob, qeth_ulp_enable_cb, &max_mtu);
	अगर (rc)
		वापस rc;
	वापस qeth_update_max_mtu(card, max_mtu);
पूर्ण

अटल पूर्णांक qeth_ulp_setup_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
		अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "ulpstpcb");

	iob = (काष्ठा qeth_cmd_buffer *) data;
	स_नकल(&card->token.ulp_connection_r,
	       QETH_ULP_SETUP_RESP_CONNECTION_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	अगर (!म_भेदन("00S", QETH_ULP_SETUP_RESP_CONNECTION_TOKEN(iob->data),
		     3)) अणु
		QETH_CARD_TEXT(card, 2, "olmlimit");
		dev_err(&card->gdev->dev, "A connection could not be "
			"established because of an OLM limit\n");
		वापस -EMLINK;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_ulp_setup(काष्ठा qeth_card *card)
अणु
	__u16 temp;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "ulpsetup");

	iob = qeth_mpc_alloc_cmd(card, ULP_SETUP, ULP_SETUP_SIZE);
	अगर (!iob)
		वापस -ENOMEM;

	स_नकल(QETH_ULP_SETUP_DEST_ADDR(iob->data),
	       &card->token.cm_connection_r, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_ULP_SETUP_CONNECTION_TOKEN(iob->data),
	       &card->token.ulp_connection_w, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_ULP_SETUP_FILTER_TOKEN(iob->data),
	       &card->token.ulp_filter_r, QETH_MPC_TOKEN_LENGTH);

	स_नकल(QETH_ULP_SETUP_CUA(iob->data), &card->info.ddev_devno, 2);
	temp = (card->info.cula << 8) + card->info.unit_addr2;
	स_नकल(QETH_ULP_SETUP_REAL_DEVADDR(iob->data), &temp, 2);
	वापस qeth_send_control_data(card, iob, qeth_ulp_setup_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_alloc_out_buf(काष्ठा qeth_qdio_out_q *q, अचिन्हित पूर्णांक bidx,
			      gfp_t gfp)
अणु
	काष्ठा qeth_qdio_out_buffer *newbuf;

	newbuf = kmem_cache_zalloc(qeth_qdio_outbuf_cache, gfp);
	अगर (!newbuf)
		वापस -ENOMEM;

	newbuf->buffer = q->qdio_bufs[bidx];
	skb_queue_head_init(&newbuf->skb_list);
	lockdep_set_class(&newbuf->skb_list.lock, &qdio_out_skb_queue_key);
	newbuf->q = q;
	atomic_set(&newbuf->state, QETH_QDIO_BUF_EMPTY);
	q->bufs[bidx] = newbuf;
	वापस 0;
पूर्ण

अटल व्योम qeth_मुक्त_output_queue(काष्ठा qeth_qdio_out_q *q)
अणु
	अगर (!q)
		वापस;

	qeth_drain_output_queue(q, true);
	qdio_मुक्त_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
	kमुक्त(q);
पूर्ण

अटल काष्ठा qeth_qdio_out_q *qeth_alloc_output_queue(व्योम)
अणु
	काष्ठा qeth_qdio_out_q *q = kzalloc(माप(*q), GFP_KERNEL);
	अचिन्हित पूर्णांक i;

	अगर (!q)
		वापस शून्य;

	अगर (qdio_alloc_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q))
		जाओ err_qdio_bufs;

	क्रम (i = 0; i < QDIO_MAX_BUFFERS_PER_Q; i++) अणु
		अगर (qeth_alloc_out_buf(q, i, GFP_KERNEL))
			जाओ err_out_bufs;
	पूर्ण

	वापस q;

err_out_bufs:
	जबतक (i > 0)
		qeth_मुक्त_out_buf(q->bufs[--i]);
	qdio_मुक्त_buffers(q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
err_qdio_bufs:
	kमुक्त(q);
	वापस शून्य;
पूर्ण

अटल व्योम qeth_tx_completion_समयr(काष्ठा समयr_list *समयr)
अणु
	काष्ठा qeth_qdio_out_q *queue = from_समयr(queue, समयr, समयr);

	napi_schedule(&queue->napi);
	QETH_TXQ_STAT_INC(queue, completion_समयr);
पूर्ण

अटल पूर्णांक qeth_alloc_qdio_queues(काष्ठा qeth_card *card)
अणु
	अचिन्हित पूर्णांक i;

	QETH_CARD_TEXT(card, 2, "allcqdbf");

	अगर (atomic_cmpxchg(&card->qdio.state, QETH_QDIO_UNINITIALIZED,
		QETH_QDIO_ALLOCATED) != QETH_QDIO_UNINITIALIZED)
		वापस 0;

	QETH_CARD_TEXT(card, 2, "inq");
	card->qdio.in_q = qeth_alloc_qdio_queue();
	अगर (!card->qdio.in_q)
		जाओ out_nomem;

	/* inbound buffer pool */
	अगर (qeth_alloc_buffer_pool(card))
		जाओ out_मुक्तinq;

	/* outbound */
	क्रम (i = 0; i < card->qdio.no_out_queues; ++i) अणु
		काष्ठा qeth_qdio_out_q *queue;

		queue = qeth_alloc_output_queue();
		अगर (!queue)
			जाओ out_मुक्तoutq;
		QETH_CARD_TEXT_(card, 2, "outq %i", i);
		QETH_CARD_HEX(card, 2, &queue, माप(व्योम *));
		card->qdio.out_qs[i] = queue;
		queue->card = card;
		queue->queue_no = i;
		INIT_LIST_HEAD(&queue->pending_bufs);
		spin_lock_init(&queue->lock);
		समयr_setup(&queue->समयr, qeth_tx_completion_समयr, 0);
		queue->coalesce_usecs = QETH_TX_COALESCE_USECS;
		queue->max_coalesced_frames = QETH_TX_MAX_COALESCED_FRAMES;
		queue->priority = QETH_QIB_PQUE_PRIO_DEFAULT;
	पूर्ण

	/* completion */
	अगर (qeth_alloc_cq(card))
		जाओ out_मुक्तoutq;

	वापस 0;

out_मुक्तoutq:
	जबतक (i > 0) अणु
		qeth_मुक्त_output_queue(card->qdio.out_qs[--i]);
		card->qdio.out_qs[i] = शून्य;
	पूर्ण
	qeth_मुक्त_buffer_pool(card);
out_मुक्तinq:
	qeth_मुक्त_qdio_queue(card->qdio.in_q);
	card->qdio.in_q = शून्य;
out_nomem:
	atomic_set(&card->qdio.state, QETH_QDIO_UNINITIALIZED);
	वापस -ENOMEM;
पूर्ण

अटल व्योम qeth_मुक्त_qdio_queues(काष्ठा qeth_card *card)
अणु
	पूर्णांक i, j;

	अगर (atomic_xchg(&card->qdio.state, QETH_QDIO_UNINITIALIZED) ==
		QETH_QDIO_UNINITIALIZED)
		वापस;

	qeth_मुक्त_cq(card);
	क्रम (j = 0; j < QDIO_MAX_BUFFERS_PER_Q; ++j) अणु
		अगर (card->qdio.in_q->bufs[j].rx_skb)
			dev_kमुक्त_skb_any(card->qdio.in_q->bufs[j].rx_skb);
	पूर्ण
	qeth_मुक्त_qdio_queue(card->qdio.in_q);
	card->qdio.in_q = शून्य;
	/* inbound buffer pool */
	qeth_मुक्त_buffer_pool(card);
	/* मुक्त outbound qdio_qs */
	क्रम (i = 0; i < card->qdio.no_out_queues; i++) अणु
		qeth_मुक्त_output_queue(card->qdio.out_qs[i]);
		card->qdio.out_qs[i] = शून्य;
	पूर्ण
पूर्ण

अटल व्योम qeth_fill_qib_parms(काष्ठा qeth_card *card,
				काष्ठा qeth_qib_parms *parms)
अणु
	काष्ठा qeth_qdio_out_q *queue;
	अचिन्हित पूर्णांक i;

	parms->pcit_magic[0] = 'P';
	parms->pcit_magic[1] = 'C';
	parms->pcit_magic[2] = 'I';
	parms->pcit_magic[3] = 'T';
	ASCEBC(parms->pcit_magic, माप(parms->pcit_magic));
	parms->pcit_a = QETH_PCI_THRESHOLD_A(card);
	parms->pcit_b = QETH_PCI_THRESHOLD_B(card);
	parms->pcit_c = QETH_PCI_TIMER_VALUE(card);

	parms->blkt_magic[0] = 'B';
	parms->blkt_magic[1] = 'L';
	parms->blkt_magic[2] = 'K';
	parms->blkt_magic[3] = 'T';
	ASCEBC(parms->blkt_magic, माप(parms->blkt_magic));
	parms->blkt_total = card->info.blkt.समय_प्रकारotal;
	parms->blkt_पूर्णांकer_packet = card->info.blkt.पूर्णांकer_packet;
	parms->blkt_पूर्णांकer_packet_jumbo = card->info.blkt.पूर्णांकer_packet_jumbo;

	/* Prio-queueing implicitly uses the शेष priorities: */
	अगर (qeth_uses_tx_prio_queueing(card) || card->qdio.no_out_queues == 1)
		वापस;

	parms->pque_magic[0] = 'P';
	parms->pque_magic[1] = 'Q';
	parms->pque_magic[2] = 'U';
	parms->pque_magic[3] = 'E';
	ASCEBC(parms->pque_magic, माप(parms->pque_magic));
	parms->pque_order = QETH_QIB_PQUE_ORDER_RR;
	parms->pque_units = QETH_QIB_PQUE_UNITS_SBAL;

	qeth_क्रम_each_output_queue(card, queue, i)
		parms->pque_priority[i] = queue->priority;
पूर्ण

अटल पूर्णांक qeth_qdio_activate(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 3, "qdioact");
	वापस qdio_activate(CARD_DDEV(card));
पूर्ण

अटल पूर्णांक qeth_dm_act(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "dmact");

	iob = qeth_mpc_alloc_cmd(card, DM_ACT, DM_ACT_SIZE);
	अगर (!iob)
		वापस -ENOMEM;

	स_नकल(QETH_DM_ACT_DEST_ADDR(iob->data),
	       &card->token.cm_connection_r, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_DM_ACT_CONNECTION_TOKEN(iob->data),
	       &card->token.ulp_connection_r, QETH_MPC_TOKEN_LENGTH);
	वापस qeth_send_control_data(card, iob, शून्य, शून्य);
पूर्ण

अटल पूर्णांक qeth_mpc_initialize(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "mpcinit");

	rc = qeth_issue_next_पढ़ो(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_cm_enable(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "2err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_cm_setup(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "3err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_ulp_enable(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "4err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_ulp_setup(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "5err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_alloc_qdio_queues(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "5err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_qdio_establish(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "6err%d", rc);
		qeth_मुक्त_qdio_queues(card);
		वापस rc;
	पूर्ण
	rc = qeth_qdio_activate(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "7err%d", rc);
		वापस rc;
	पूर्ण
	rc = qeth_dm_act(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "8err%d", rc);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qeth_prपूर्णांक_status_message(काष्ठा qeth_card *card)
अणु
	चयन (card->info.type) अणु
	हाल QETH_CARD_TYPE_OSD:
	हाल QETH_CARD_TYPE_OSM:
	हाल QETH_CARD_TYPE_OSX:
		/* VM will use a non-zero first अक्षरacter
		 * to indicate a HiperSockets like reporting
		 * of the level OSA sets the first अक्षरacter to zero
		 * */
		अगर (!card->info.mcl_level[0]) अणु
			प्र_लिखो(card->info.mcl_level, "%02x%02x",
				card->info.mcl_level[2],
				card->info.mcl_level[3]);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल QETH_CARD_TYPE_IQD:
		अगर (IS_VM_NIC(card) || (card->info.mcl_level[0] & 0x80)) अणु
			card->info.mcl_level[0] = (अक्षर) _ebcasc[(__u8)
				card->info.mcl_level[0]];
			card->info.mcl_level[1] = (अक्षर) _ebcasc[(__u8)
				card->info.mcl_level[1]];
			card->info.mcl_level[2] = (अक्षर) _ebcasc[(__u8)
				card->info.mcl_level[2]];
			card->info.mcl_level[3] = (अक्षर) _ebcasc[(__u8)
				card->info.mcl_level[3]];
			card->info.mcl_level[QETH_MCL_LENGTH] = 0;
		पूर्ण
		अवरोध;
	शेष:
		स_रखो(&card->info.mcl_level[0], 0, QETH_MCL_LENGTH + 1);
	पूर्ण
	dev_info(&card->gdev->dev,
		 "Device is a%s card%s%s%s\nwith link type %s.\n",
		 qeth_get_cardname(card),
		 (card->info.mcl_level[0]) ? " (level: " : "",
		 (card->info.mcl_level[0]) ? card->info.mcl_level : "",
		 (card->info.mcl_level[0]) ? ")" : "",
		 qeth_get_cardname_लघु(card));
पूर्ण

अटल व्योम qeth_initialize_working_pool_list(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_buffer_pool_entry *entry;

	QETH_CARD_TEXT(card, 5, "inwrklst");

	list_क्रम_each_entry(entry,
			    &card->qdio.init_pool.entry_list, init_list) अणु
		qeth_put_buffer_pool_entry(card, entry);
	पूर्ण
पूर्ण

अटल काष्ठा qeth_buffer_pool_entry *qeth_find_मुक्त_buffer_pool_entry(
					काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_buffer_pool_entry *entry;
	पूर्णांक i, मुक्त;

	अगर (list_empty(&card->qdio.in_buf_pool.entry_list))
		वापस शून्य;

	list_क्रम_each_entry(entry, &card->qdio.in_buf_pool.entry_list, list) अणु
		मुक्त = 1;
		क्रम (i = 0; i < QETH_MAX_BUFFER_ELEMENTS(card); ++i) अणु
			अगर (page_count(entry->elements[i]) > 1) अणु
				मुक्त = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (मुक्त) अणु
			list_del_init(&entry->list);
			वापस entry;
		पूर्ण
	पूर्ण

	/* no मुक्त buffer in pool so take first one and swap pages */
	entry = list_first_entry(&card->qdio.in_buf_pool.entry_list,
				 काष्ठा qeth_buffer_pool_entry, list);
	क्रम (i = 0; i < QETH_MAX_BUFFER_ELEMENTS(card); ++i) अणु
		अगर (page_count(entry->elements[i]) > 1) अणु
			काष्ठा page *page = dev_alloc_page();

			अगर (!page)
				वापस शून्य;

			__मुक्त_page(entry->elements[i]);
			entry->elements[i] = page;
			QETH_CARD_STAT_INC(card, rx_sg_alloc_page);
		पूर्ण
	पूर्ण
	list_del_init(&entry->list);
	वापस entry;
पूर्ण

अटल पूर्णांक qeth_init_input_buffer(काष्ठा qeth_card *card,
		काष्ठा qeth_qdio_buffer *buf)
अणु
	काष्ठा qeth_buffer_pool_entry *pool_entry = buf->pool_entry;
	पूर्णांक i;

	अगर ((card->options.cq == QETH_CQ_ENABLED) && (!buf->rx_skb)) अणु
		buf->rx_skb = netdev_alloc_skb(card->dev,
					       ETH_HLEN +
					       माप(काष्ठा ipv6hdr));
		अगर (!buf->rx_skb)
			वापस -ENOMEM;
	पूर्ण

	अगर (!pool_entry) अणु
		pool_entry = qeth_find_मुक्त_buffer_pool_entry(card);
		अगर (!pool_entry)
			वापस -ENOBUFS;

		buf->pool_entry = pool_entry;
	पूर्ण

	/*
	 * since the buffer is accessed only from the input_tasklet
	 * there shouldn't be a need to synchronize; also, since we use
	 * the QETH_IN_BUF_REQUEUE_THRESHOLD we should never run  out off
	 * buffers
	 */
	क्रम (i = 0; i < QETH_MAX_BUFFER_ELEMENTS(card); ++i) अणु
		buf->buffer->element[i].length = PAGE_SIZE;
		buf->buffer->element[i].addr =
			page_to_phys(pool_entry->elements[i]);
		अगर (i == QETH_MAX_BUFFER_ELEMENTS(card) - 1)
			buf->buffer->element[i].eflags = SBAL_EFLAGS_LAST_ENTRY;
		अन्यथा
			buf->buffer->element[i].eflags = 0;
		buf->buffer->element[i].sflags = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक qeth_tx_select_bulk_max(काष्ठा qeth_card *card,
					    काष्ठा qeth_qdio_out_q *queue)
अणु
	अगर (!IS_IQD(card) ||
	    qeth_iqd_is_mcast_queue(card, queue) ||
	    card->options.cq == QETH_CQ_ENABLED ||
	    qdio_get_ssqd_desc(CARD_DDEV(card), &card->ssqd))
		वापस 1;

	वापस card->ssqd.mmwc ? card->ssqd.mmwc : 1;
पूर्ण

अटल पूर्णांक qeth_init_qdio_queues(काष्ठा qeth_card *card)
अणु
	अचिन्हित पूर्णांक rx_bufs = card->qdio.in_buf_pool.buf_count;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "initqdqs");

	/* inbound queue */
	qdio_reset_buffers(card->qdio.in_q->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
	स_रखो(&card->rx, 0, माप(काष्ठा qeth_rx));

	qeth_initialize_working_pool_list(card);
	/*give only as many buffers to hardware as we have buffer pool entries*/
	क्रम (i = 0; i < rx_bufs; i++) अणु
		rc = qeth_init_input_buffer(card, &card->qdio.in_q->bufs[i]);
		अगर (rc)
			वापस rc;
	पूर्ण

	card->qdio.in_q->next_buf_to_init = QDIO_BUFNR(rx_bufs);
	rc = करो_QDIO(CARD_DDEV(card), QDIO_FLAG_SYNC_INPUT, 0, 0, rx_bufs,
		     शून्य);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
		वापस rc;
	पूर्ण

	/* completion */
	rc = qeth_cq_init(card);
	अगर (rc) अणु
		वापस rc;
	पूर्ण

	/* outbound queue */
	क्रम (i = 0; i < card->qdio.no_out_queues; ++i) अणु
		काष्ठा qeth_qdio_out_q *queue = card->qdio.out_qs[i];

		qdio_reset_buffers(queue->qdio_bufs, QDIO_MAX_BUFFERS_PER_Q);
		queue->max_elements = QETH_MAX_BUFFER_ELEMENTS(card);
		queue->next_buf_to_fill = 0;
		queue->करो_pack = 0;
		queue->prev_hdr = शून्य;
		queue->coalesced_frames = 0;
		queue->bulk_start = 0;
		queue->bulk_count = 0;
		queue->bulk_max = qeth_tx_select_bulk_max(card, queue);
		atomic_set(&queue->used_buffers, 0);
		atomic_set(&queue->set_pci_flags_count, 0);
		netdev_tx_reset_queue(netdev_get_tx_queue(card->dev, i));
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qeth_ipa_finalize_cmd(काष्ठा qeth_card *card,
				  काष्ठा qeth_cmd_buffer *iob)
अणु
	qeth_mpc_finalize_cmd(card, iob);

	/* override with IPA-specअगरic values: */
	__ipa_cmd(iob)->hdr.seqno = card->seqno.ipa++;
पूर्ण

व्योम qeth_prepare_ipa_cmd(काष्ठा qeth_card *card, काष्ठा qeth_cmd_buffer *iob,
			  u16 cmd_length,
			  bool (*match)(काष्ठा qeth_cmd_buffer *iob,
					काष्ठा qeth_cmd_buffer *reply))
अणु
	u8 prot_type = qeth_mpc_select_prot_type(card);
	u16 total_length = iob->length;

	qeth_setup_ccw(__ccw_from_cmd(iob), CCW_CMD_WRITE, 0, total_length,
		       iob->data);
	iob->finalize = qeth_ipa_finalize_cmd;
	iob->match = match;

	स_नकल(iob->data, IPA_PDU_HEADER, IPA_PDU_HEADER_SIZE);
	स_नकल(QETH_IPA_PDU_LEN_TOTAL(iob->data), &total_length, 2);
	स_नकल(QETH_IPA_CMD_PROT_TYPE(iob->data), &prot_type, 1);
	स_नकल(QETH_IPA_PDU_LEN_PDU1(iob->data), &cmd_length, 2);
	स_नकल(QETH_IPA_PDU_LEN_PDU2(iob->data), &cmd_length, 2);
	स_नकल(QETH_IPA_CMD_DEST_ADDR(iob->data),
	       &card->token.ulp_connection_r, QETH_MPC_TOKEN_LENGTH);
	स_नकल(QETH_IPA_PDU_LEN_PDU3(iob->data), &cmd_length, 2);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_prepare_ipa_cmd);

अटल bool qeth_ipa_match_reply(काष्ठा qeth_cmd_buffer *iob,
				 काष्ठा qeth_cmd_buffer *reply)
अणु
	काष्ठा qeth_ipa_cmd *ipa_reply = __ipa_reply(reply);

	वापस ipa_reply && (__ipa_cmd(iob)->hdr.seqno == ipa_reply->hdr.seqno);
पूर्ण

काष्ठा qeth_cmd_buffer *qeth_ipa_alloc_cmd(काष्ठा qeth_card *card,
					   क्रमागत qeth_ipa_cmds cmd_code,
					   क्रमागत qeth_prot_versions prot,
					   अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipacmd_hdr *hdr;

	data_length += दुरत्व(काष्ठा qeth_ipa_cmd, data);
	iob = qeth_alloc_cmd(&card->ग_लिखो, IPA_PDU_HEADER_SIZE + data_length, 1,
			     QETH_IPA_TIMEOUT);
	अगर (!iob)
		वापस शून्य;

	qeth_prepare_ipa_cmd(card, iob, data_length, qeth_ipa_match_reply);

	hdr = &__ipa_cmd(iob)->hdr;
	hdr->command = cmd_code;
	hdr->initiator = IPA_CMD_INITIATOR_HOST;
	/* hdr->seqno is set by qeth_send_control_data() */
	hdr->adapter_type = QETH_LINK_TYPE_FAST_ETH;
	hdr->rel_adapter_no = (u8) card->dev->dev_port;
	hdr->prim_version_no = IS_LAYER2(card) ? 2 : 1;
	hdr->param_count = 1;
	hdr->prot_version = prot;
	वापस iob;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_ipa_alloc_cmd);

अटल पूर्णांक qeth_send_ipa_cmd_cb(काष्ठा qeth_card *card,
				काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	वापस (cmd->hdr.वापस_code) ? -EIO : 0;
पूर्ण

/**
 * qeth_send_ipa_cmd() - send an IPA command
 *
 * See qeth_send_control_data() क्रम explanation of the arguments.
 */

पूर्णांक qeth_send_ipa_cmd(काष्ठा qeth_card *card, काष्ठा qeth_cmd_buffer *iob,
		पूर्णांक (*reply_cb)(काष्ठा qeth_card *, काष्ठा qeth_reply*,
			अचिन्हित दीर्घ),
		व्योम *reply_param)
अणु
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 4, "sendipa");

	अगर (card->पढ़ो_or_ग_लिखो_problem) अणु
		qeth_put_cmd(iob);
		वापस -EIO;
	पूर्ण

	अगर (reply_cb == शून्य)
		reply_cb = qeth_send_ipa_cmd_cb;
	rc = qeth_send_control_data(card, iob, reply_cb, reply_param);
	अगर (rc == -ETIME) अणु
		qeth_clear_ipacmd_list(card);
		qeth_schedule_recovery(card);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_send_ipa_cmd);

अटल पूर्णांक qeth_send_startlan_cb(काष्ठा qeth_card *card,
				 काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	अगर (cmd->hdr.वापस_code == IPA_RC_LAN_OFFLINE)
		वापस -ENETDOWN;

	वापस (cmd->hdr.वापस_code) ? -EIO : 0;
पूर्ण

अटल पूर्णांक qeth_send_startlan(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "strtlan");

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_STARTLAN, QETH_PROT_NONE, 0);
	अगर (!iob)
		वापस -ENOMEM;
	वापस qeth_send_ipa_cmd(card, iob, qeth_send_startlan_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_setadpparms_inspect_rc(काष्ठा qeth_ipa_cmd *cmd)
अणु
	अगर (!cmd->hdr.वापस_code)
		cmd->hdr.वापस_code =
			cmd->data.setadapterparms.hdr.वापस_code;
	वापस cmd->hdr.वापस_code;
पूर्ण

अटल पूर्णांक qeth_query_setadapterparms_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_query_cmds_supp *query_cmd;

	QETH_CARD_TEXT(card, 3, "quyadpcb");
	अगर (qeth_setadpparms_inspect_rc(cmd))
		वापस -EIO;

	query_cmd = &cmd->data.setadapterparms.data.query_cmds_supp;
	अगर (query_cmd->lan_type & 0x7f) अणु
		अगर (!qeth_is_supported_link_type(card, query_cmd->lan_type))
			वापस -EPROTONOSUPPORT;

		card->info.link_type = query_cmd->lan_type;
		QETH_CARD_TEXT_(card, 2, "lnk %d", card->info.link_type);
	पूर्ण

	card->options.adp.supported = query_cmd->supported_cmds;
	वापस 0;
पूर्ण

अटल काष्ठा qeth_cmd_buffer *qeth_get_adapter_cmd(काष्ठा qeth_card *card,
						    क्रमागत qeth_ipa_setadp_cmd adp_cmd,
						    अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_ipacmd_setadpparms_hdr *hdr;
	काष्ठा qeth_cmd_buffer *iob;

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_SETADAPTERPARMS, QETH_PROT_IPV4,
				 data_length +
				 दुरत्व(काष्ठा qeth_ipacmd_setadpparms,
					  data));
	अगर (!iob)
		वापस शून्य;

	hdr = &__ipa_cmd(iob)->data.setadapterparms.hdr;
	hdr->cmdlength = माप(*hdr) + data_length;
	hdr->command_code = adp_cmd;
	hdr->used_total = 1;
	hdr->seq_no = 1;
	वापस iob;
पूर्ण

अटल पूर्णांक qeth_query_setadapterparms(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 3, "queryadp");
	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_COMMANDS_SUPPORTED,
				   SETADP_DATA_SIZखातापूर्ण(query_cmds_supp));
	अगर (!iob)
		वापस -ENOMEM;
	rc = qeth_send_ipa_cmd(card, iob, qeth_query_setadapterparms_cb, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_query_ipassists_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 2, "qipasscb");

	cmd = (काष्ठा qeth_ipa_cmd *) data;

	चयन (cmd->hdr.वापस_code) अणु
	हाल IPA_RC_SUCCESS:
		अवरोध;
	हाल IPA_RC_NOTSUPP:
	हाल IPA_RC_L2_UNSUPPORTED_CMD:
		QETH_CARD_TEXT(card, 2, "ipaunsup");
		card->options.ipa4.supported |= IPA_SETADAPTERPARMS;
		card->options.ipa6.supported |= IPA_SETADAPTERPARMS;
		वापस -EOPNOTSUPP;
	शेष:
		QETH_DBF_MESSAGE(1, "IPA_CMD_QIPASSIST on device %x: Unhandled rc=%#x\n",
				 CARD_DEVID(card), cmd->hdr.वापस_code);
		वापस -EIO;
	पूर्ण

	अगर (cmd->hdr.prot_version == QETH_PROT_IPV4)
		card->options.ipa4 = cmd->hdr.assists;
	अन्यथा अगर (cmd->hdr.prot_version == QETH_PROT_IPV6)
		card->options.ipa6 = cmd->hdr.assists;
	अन्यथा
		QETH_DBF_MESSAGE(1, "IPA_CMD_QIPASSIST on device %x: Flawed LIC detected\n",
				 CARD_DEVID(card));
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_query_ipassists(काष्ठा qeth_card *card,
				क्रमागत qeth_prot_versions prot)
अणु
	पूर्णांक rc;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT_(card, 2, "qipassi%i", prot);
	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_QIPASSIST, prot, 0);
	अगर (!iob)
		वापस -ENOMEM;
	rc = qeth_send_ipa_cmd(card, iob, qeth_query_ipassists_cb, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_query_चयन_attributes_cb(काष्ठा qeth_card *card,
				काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_query_चयन_attributes *attrs;
	काष्ठा qeth_चयन_info *sw_info;

	QETH_CARD_TEXT(card, 2, "qswiatcb");
	अगर (qeth_setadpparms_inspect_rc(cmd))
		वापस -EIO;

	sw_info = (काष्ठा qeth_चयन_info *)reply->param;
	attrs = &cmd->data.setadapterparms.data.query_चयन_attributes;
	sw_info->capabilities = attrs->capabilities;
	sw_info->settings = attrs->settings;
	QETH_CARD_TEXT_(card, 2, "%04x%04x", sw_info->capabilities,
			sw_info->settings);
	वापस 0;
पूर्ण

पूर्णांक qeth_query_चयन_attributes(काष्ठा qeth_card *card,
				 काष्ठा qeth_चयन_info *sw_info)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "qswiattr");
	अगर (!qeth_adp_supported(card, IPA_SETADP_QUERY_SWITCH_ATTRIBUTES))
		वापस -EOPNOTSUPP;
	अगर (!netअगर_carrier_ok(card->dev))
		वापस -ENOMEDIUM;
	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_SWITCH_ATTRIBUTES, 0);
	अगर (!iob)
		वापस -ENOMEM;
	वापस qeth_send_ipa_cmd(card, iob,
				qeth_query_चयन_attributes_cb, sw_info);
पूर्ण

काष्ठा qeth_cmd_buffer *qeth_get_diag_cmd(काष्ठा qeth_card *card,
					  क्रमागत qeth_diags_cmds sub_cmd,
					  अचिन्हित पूर्णांक data_length)
अणु
	काष्ठा qeth_ipacmd_diagass *cmd;
	काष्ठा qeth_cmd_buffer *iob;

	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_SET_DIAG_ASS, QETH_PROT_NONE,
				 DIAG_HDR_LEN + data_length);
	अगर (!iob)
		वापस शून्य;

	cmd = &__ipa_cmd(iob)->data.diagass;
	cmd->subcmd_len = DIAG_SUB_HDR_LEN + data_length;
	cmd->subcmd = sub_cmd;
	वापस iob;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_get_diag_cmd);

अटल पूर्णांक qeth_query_setdiagass_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	u16 rc = cmd->hdr.वापस_code;

	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "diagq:%x", rc);
		वापस -EIO;
	पूर्ण

	card->info.diagass_support = cmd->data.diagass.ext;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_query_setdiagass(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "qdiagass");
	iob = qeth_get_diag_cmd(card, QETH_DIAGS_CMD_QUERY, 0);
	अगर (!iob)
		वापस -ENOMEM;
	वापस qeth_send_ipa_cmd(card, iob, qeth_query_setdiagass_cb, शून्य);
पूर्ण

अटल व्योम qeth_get_trap_id(काष्ठा qeth_card *card, काष्ठा qeth_trap_id *tid)
अणु
	अचिन्हित दीर्घ info = get_zeroed_page(GFP_KERNEL);
	काष्ठा sysinfo_2_2_2 *info222 = (काष्ठा sysinfo_2_2_2 *)info;
	काष्ठा sysinfo_3_2_2 *info322 = (काष्ठा sysinfo_3_2_2 *)info;
	काष्ठा ccw_dev_id ccwid;
	पूर्णांक level;

	tid->chpid = card->info.chpid;
	ccw_device_get_id(CARD_RDEV(card), &ccwid);
	tid->ssid = ccwid.ssid;
	tid->devno = ccwid.devno;
	अगर (!info)
		वापस;
	level = stsi(शून्य, 0, 0, 0);
	अगर ((level >= 2) && (stsi(info222, 2, 2, 2) == 0))
		tid->lparnr = info222->lpar_number;
	अगर ((level >= 3) && (stsi(info322, 3, 2, 2) == 0)) अणु
		EBCASC(info322->vm[0].name, माप(info322->vm[0].name));
		स_नकल(tid->vmname, info322->vm[0].name, माप(tid->vmname));
	पूर्ण
	मुक्त_page(info);
पूर्ण

अटल पूर्णांक qeth_hw_trap_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	u16 rc = cmd->hdr.वापस_code;

	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "trapc:%x", rc);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक qeth_hw_trap(काष्ठा qeth_card *card, क्रमागत qeth_diags_trap_action action)
अणु
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 2, "diagtrap");
	iob = qeth_get_diag_cmd(card, QETH_DIAGS_CMD_TRAP, 64);
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.diagass.type = 1;
	cmd->data.diagass.action = action;
	चयन (action) अणु
	हाल QETH_DIAGS_TRAP_ARM:
		cmd->data.diagass.options = 0x0003;
		cmd->data.diagass.ext = 0x00010000 +
			माप(काष्ठा qeth_trap_id);
		qeth_get_trap_id(card,
			(काष्ठा qeth_trap_id *)cmd->data.diagass.cdata);
		अवरोध;
	हाल QETH_DIAGS_TRAP_DISARM:
		cmd->data.diagass.options = 0x0001;
		अवरोध;
	हाल QETH_DIAGS_TRAP_CAPTURE:
		अवरोध;
	पूर्ण
	वापस qeth_send_ipa_cmd(card, iob, qeth_hw_trap_cb, शून्य);
पूर्ण

अटल पूर्णांक qeth_check_qdio_errors(काष्ठा qeth_card *card,
				  काष्ठा qdio_buffer *buf,
				  अचिन्हित पूर्णांक qdio_error,
				  स्थिर अक्षर *dbftext)
अणु
	अगर (qdio_error) अणु
		QETH_CARD_TEXT(card, 2, dbftext);
		QETH_CARD_TEXT_(card, 2, " F15=%02X",
			       buf->element[15].sflags);
		QETH_CARD_TEXT_(card, 2, " F14=%02X",
			       buf->element[14].sflags);
		QETH_CARD_TEXT_(card, 2, " qerr=%X", qdio_error);
		अगर ((buf->element[15].sflags) == 0x12) अणु
			QETH_CARD_STAT_INC(card, rx_fअगरo_errors);
			वापस 0;
		पूर्ण अन्यथा
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक qeth_rx_refill_queue(काष्ठा qeth_card *card,
					 अचिन्हित पूर्णांक count)
अणु
	काष्ठा qeth_qdio_q *queue = card->qdio.in_q;
	काष्ठा list_head *lh;
	पूर्णांक i;
	पूर्णांक rc;
	पूर्णांक newcount = 0;

	/* only requeue at a certain threshold to aव्योम SIGAs */
	अगर (count >= QETH_IN_BUF_REQUEUE_THRESHOLD(card)) अणु
		क्रम (i = queue->next_buf_to_init;
		     i < queue->next_buf_to_init + count; ++i) अणु
			अगर (qeth_init_input_buffer(card,
				&queue->bufs[QDIO_BUFNR(i)])) अणु
				अवरोध;
			पूर्ण अन्यथा अणु
				newcount++;
			पूर्ण
		पूर्ण

		अगर (newcount < count) अणु
			/* we are in memory लघुage so we चयन back to
			   traditional skb allocation and drop packages */
			atomic_set(&card->क्रमce_alloc_skb, 3);
			count = newcount;
		पूर्ण अन्यथा अणु
			atomic_add_unless(&card->क्रमce_alloc_skb, -1, 0);
		पूर्ण

		अगर (!count) अणु
			i = 0;
			list_क्रम_each(lh, &card->qdio.in_buf_pool.entry_list)
				i++;
			अगर (i == card->qdio.in_buf_pool.buf_count) अणु
				QETH_CARD_TEXT(card, 2, "qsarbw");
				schedule_delayed_work(
					&card->buffer_reclaim_work,
					QETH_RECLAIM_WORK_TIME);
			पूर्ण
			वापस 0;
		पूर्ण

		rc = करो_QDIO(CARD_DDEV(card), QDIO_FLAG_SYNC_INPUT, 0,
			     queue->next_buf_to_init, count, शून्य);
		अगर (rc) अणु
			QETH_CARD_TEXT(card, 2, "qinberr");
		पूर्ण
		queue->next_buf_to_init = QDIO_BUFNR(queue->next_buf_to_init +
						     count);
		वापस count;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qeth_buffer_reclaim_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qeth_card *card = container_of(to_delayed_work(work),
					      काष्ठा qeth_card,
					      buffer_reclaim_work);

	local_bh_disable();
	napi_schedule(&card->napi);
	/* kick-start the NAPI softirq: */
	local_bh_enable();
पूर्ण

अटल व्योम qeth_handle_send_error(काष्ठा qeth_card *card,
		काष्ठा qeth_qdio_out_buffer *buffer, अचिन्हित पूर्णांक qdio_err)
अणु
	पूर्णांक sbalf15 = buffer->buffer->element[15].sflags;

	QETH_CARD_TEXT(card, 6, "hdsnderr");
	qeth_check_qdio_errors(card, buffer->buffer, qdio_err, "qouterr");

	अगर (!qdio_err)
		वापस;

	अगर ((sbalf15 >= 15) && (sbalf15 <= 31))
		वापस;

	QETH_CARD_TEXT(card, 1, "lnkfail");
	QETH_CARD_TEXT_(card, 1, "%04x %02x",
		       (u16)qdio_err, (u8)sbalf15);
पूर्ण

/**
 * qeth_prep_flush_pack_buffer - Prepares flushing of a packing buffer.
 * @queue: queue to check क्रम packing buffer
 *
 * Returns number of buffers that were prepared क्रम flush.
 */
अटल पूर्णांक qeth_prep_flush_pack_buffer(काष्ठा qeth_qdio_out_q *queue)
अणु
	काष्ठा qeth_qdio_out_buffer *buffer;

	buffer = queue->bufs[queue->next_buf_to_fill];
	अगर ((atomic_पढ़ो(&buffer->state) == QETH_QDIO_BUF_EMPTY) &&
	    (buffer->next_element_to_fill > 0)) अणु
		/* it's a packing buffer */
		atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
		queue->next_buf_to_fill =
			QDIO_BUFNR(queue->next_buf_to_fill + 1);
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Switched to packing state अगर the number of used buffers on a queue
 * reaches a certain limit.
 */
अटल व्योम qeth_चयन_to_packing_अगर_needed(काष्ठा qeth_qdio_out_q *queue)
अणु
	अगर (!queue->करो_pack) अणु
		अगर (atomic_पढ़ो(&queue->used_buffers)
		    >= QETH_HIGH_WATERMARK_PACK)अणु
			/* चयन non-PACKING -> PACKING */
			QETH_CARD_TEXT(queue->card, 6, "np->pack");
			QETH_TXQ_STAT_INC(queue, packing_mode_चयन);
			queue->करो_pack = 1;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Switches from packing to non-packing mode. If there is a packing
 * buffer on the queue this buffer will be prepared to be flushed.
 * In that हाल 1 is वापसed to inक्रमm the caller. If no buffer
 * has to be flushed, zero is वापसed.
 */
अटल पूर्णांक qeth_चयन_to_nonpacking_अगर_needed(काष्ठा qeth_qdio_out_q *queue)
अणु
	अगर (queue->करो_pack) अणु
		अगर (atomic_पढ़ो(&queue->used_buffers)
		    <= QETH_LOW_WATERMARK_PACK) अणु
			/* चयन PACKING -> non-PACKING */
			QETH_CARD_TEXT(queue->card, 6, "pack->np");
			QETH_TXQ_STAT_INC(queue, packing_mode_चयन);
			queue->करो_pack = 0;
			वापस qeth_prep_flush_pack_buffer(queue);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम qeth_flush_buffers(काष्ठा qeth_qdio_out_q *queue, पूर्णांक index,
			       पूर्णांक count)
अणु
	काष्ठा qeth_qdio_out_buffer *buf = queue->bufs[index];
	अचिन्हित पूर्णांक qdio_flags = QDIO_FLAG_SYNC_OUTPUT;
	काष्ठा qeth_card *card = queue->card;
	काष्ठा qaob *aob = शून्य;
	पूर्णांक rc;
	पूर्णांक i;

	क्रम (i = index; i < index + count; ++i) अणु
		अचिन्हित पूर्णांक bidx = QDIO_BUFNR(i);
		काष्ठा sk_buff *skb;

		buf = queue->bufs[bidx];
		buf->buffer->element[buf->next_element_to_fill - 1].eflags |=
				SBAL_EFLAGS_LAST_ENTRY;
		queue->coalesced_frames += buf->frames;

		अगर (IS_IQD(card)) अणु
			skb_queue_walk(&buf->skb_list, skb)
				skb_tx_बारtamp(skb);
		पूर्ण
	पूर्ण

	अगर (IS_IQD(card)) अणु
		अगर (card->options.cq == QETH_CQ_ENABLED &&
		    !qeth_iqd_is_mcast_queue(card, queue) &&
		    count == 1) अणु
			अगर (!buf->aob)
				buf->aob = qdio_allocate_aob();
			अगर (buf->aob) अणु
				aob = buf->aob;
				aob->user1 = (u64) buf;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!queue->करो_pack) अणु
			अगर ((atomic_पढ़ो(&queue->used_buffers) >=
				(QETH_HIGH_WATERMARK_PACK -
				 QETH_WATERMARK_PACK_FUZZ)) &&
			    !atomic_पढ़ो(&queue->set_pci_flags_count)) अणु
				/* it's likely that we'll go to packing
				 * mode soon */
				atomic_inc(&queue->set_pci_flags_count);
				buf->buffer->element[0].sflags |= SBAL_SFLAGS0_PCI_REQ;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!atomic_पढ़ो(&queue->set_pci_flags_count)) अणु
				/*
				 * there's no outstanding PCI any more, so we
				 * have to request a PCI to be sure the the PCI
				 * will wake at some समय in the future then we
				 * can flush packed buffers that might still be
				 * hanging around, which can happen अगर no
				 * further send was requested by the stack
				 */
				atomic_inc(&queue->set_pci_flags_count);
				buf->buffer->element[0].sflags |= SBAL_SFLAGS0_PCI_REQ;
			पूर्ण
		पूर्ण

		अगर (atomic_पढ़ो(&queue->set_pci_flags_count))
			qdio_flags |= QDIO_FLAG_PCI_OUT;
	पूर्ण

	QETH_TXQ_STAT_INC(queue, करोorbell);
	rc = करो_QDIO(CARD_DDEV(card), qdio_flags, queue->queue_no, index, count,
		     aob);

	चयन (rc) अणु
	हाल 0:
	हाल -ENOBUFS:
		/* ignore temporary SIGA errors without busy condition */

		/* Fake the TX completion पूर्णांकerrupt: */
		अगर (IS_IQD(card)) अणु
			अचिन्हित पूर्णांक frames = READ_ONCE(queue->max_coalesced_frames);
			अचिन्हित पूर्णांक usecs = READ_ONCE(queue->coalesce_usecs);

			अगर (frames && queue->coalesced_frames >= frames) अणु
				napi_schedule(&queue->napi);
				queue->coalesced_frames = 0;
				QETH_TXQ_STAT_INC(queue, coal_frames);
			पूर्ण अन्यथा अगर (usecs) अणु
				qeth_tx_arm_समयr(queue, usecs);
			पूर्ण
		पूर्ण

		अवरोध;
	शेष:
		QETH_CARD_TEXT(queue->card, 2, "flushbuf");
		QETH_CARD_TEXT_(queue->card, 2, " q%d", queue->queue_no);
		QETH_CARD_TEXT_(queue->card, 2, " idx%d", index);
		QETH_CARD_TEXT_(queue->card, 2, " c%d", count);
		QETH_CARD_TEXT_(queue->card, 2, " err%d", rc);

		/* this must not happen under normal circumstances. अगर it
		 * happens something is really wrong -> recover */
		qeth_schedule_recovery(queue->card);
	पूर्ण
पूर्ण

अटल व्योम qeth_flush_queue(काष्ठा qeth_qdio_out_q *queue)
अणु
	qeth_flush_buffers(queue, queue->bulk_start, queue->bulk_count);

	queue->bulk_start = QDIO_BUFNR(queue->bulk_start + queue->bulk_count);
	queue->prev_hdr = शून्य;
	queue->bulk_count = 0;
पूर्ण

अटल व्योम qeth_check_outbound_queue(काष्ठा qeth_qdio_out_q *queue)
अणु
	/*
	 * check अगर weed have to चयन to non-packing mode or अगर
	 * we have to get a pci flag out on the queue
	 */
	अगर ((atomic_पढ़ो(&queue->used_buffers) <= QETH_LOW_WATERMARK_PACK) ||
	    !atomic_पढ़ो(&queue->set_pci_flags_count)) अणु
		अचिन्हित पूर्णांक index, flush_cnt;
		bool q_was_packing;

		spin_lock(&queue->lock);

		index = queue->next_buf_to_fill;
		q_was_packing = queue->करो_pack;

		flush_cnt = qeth_चयन_to_nonpacking_अगर_needed(queue);
		अगर (!flush_cnt && !atomic_पढ़ो(&queue->set_pci_flags_count))
			flush_cnt = qeth_prep_flush_pack_buffer(queue);

		अगर (flush_cnt) अणु
			qeth_flush_buffers(queue, index, flush_cnt);
			अगर (q_was_packing)
				QETH_TXQ_STAT_ADD(queue, bufs_pack, flush_cnt);
		पूर्ण

		spin_unlock(&queue->lock);
	पूर्ण
पूर्ण

अटल व्योम qeth_qdio_poll(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ card_ptr)
अणु
	काष्ठा qeth_card *card = (काष्ठा qeth_card *)card_ptr;

	napi_schedule_irqoff(&card->napi);
पूर्ण

पूर्णांक qeth_configure_cq(काष्ठा qeth_card *card, क्रमागत qeth_cq cq)
अणु
	पूर्णांक rc;

	अगर (card->options.cq ==  QETH_CQ_NOTAVAILABLE) अणु
		rc = -1;
		जाओ out;
	पूर्ण अन्यथा अणु
		अगर (card->options.cq == cq) अणु
			rc = 0;
			जाओ out;
		पूर्ण

		qeth_मुक्त_qdio_queues(card);
		card->options.cq = cq;
		rc = 0;
	पूर्ण
out:
	वापस rc;

पूर्ण
EXPORT_SYMBOL_GPL(qeth_configure_cq);

अटल व्योम qeth_qdio_cq_handler(काष्ठा qeth_card *card, अचिन्हित पूर्णांक qdio_err,
				 अचिन्हित पूर्णांक queue, पूर्णांक first_element,
				 पूर्णांक count)
अणु
	काष्ठा qeth_qdio_q *cq = card->qdio.c_q;
	पूर्णांक i;
	पूर्णांक rc;

	QETH_CARD_TEXT_(card, 5, "qcqhe%d", first_element);
	QETH_CARD_TEXT_(card, 5, "qcqhc%d", count);
	QETH_CARD_TEXT_(card, 5, "qcqherr%d", qdio_err);

	अगर (qdio_err) अणु
		netअगर_tx_stop_all_queues(card->dev);
		qeth_schedule_recovery(card);
		वापस;
	पूर्ण

	क्रम (i = first_element; i < first_element + count; ++i) अणु
		काष्ठा qdio_buffer *buffer = cq->qdio_bufs[QDIO_BUFNR(i)];
		पूर्णांक e = 0;

		जबतक ((e < QDIO_MAX_ELEMENTS_PER_BUFFER) &&
		       buffer->element[e].addr) अणु
			अचिन्हित दीर्घ phys_aob_addr = buffer->element[e].addr;

			qeth_qdio_handle_aob(card, phys_aob_addr);
			++e;
		पूर्ण
		qeth_scrub_qdio_buffer(buffer, QDIO_MAX_ELEMENTS_PER_BUFFER);
	पूर्ण
	rc = करो_QDIO(CARD_DDEV(card), QDIO_FLAG_SYNC_INPUT, queue,
		     cq->next_buf_to_init, count, शून्य);
	अगर (rc) अणु
		dev_warn(&card->gdev->dev,
			"QDIO reported an error, rc=%i\n", rc);
		QETH_CARD_TEXT(card, 2, "qcqherr");
	पूर्ण

	cq->next_buf_to_init = QDIO_BUFNR(cq->next_buf_to_init + count);
पूर्ण

अटल व्योम qeth_qdio_input_handler(काष्ठा ccw_device *ccwdev,
				    अचिन्हित पूर्णांक qdio_err, पूर्णांक queue,
				    पूर्णांक first_elem, पूर्णांक count,
				    अचिन्हित दीर्घ card_ptr)
अणु
	काष्ठा qeth_card *card = (काष्ठा qeth_card *)card_ptr;

	QETH_CARD_TEXT_(card, 2, "qihq%d", queue);
	QETH_CARD_TEXT_(card, 2, "qiec%d", qdio_err);

	अगर (qdio_err)
		qeth_schedule_recovery(card);
पूर्ण

अटल व्योम qeth_qdio_output_handler(काष्ठा ccw_device *ccwdev,
				     अचिन्हित पूर्णांक qdio_error, पूर्णांक __queue,
				     पूर्णांक first_element, पूर्णांक count,
				     अचिन्हित दीर्घ card_ptr)
अणु
	काष्ठा qeth_card *card        = (काष्ठा qeth_card *) card_ptr;
	काष्ठा qeth_qdio_out_q *queue = card->qdio.out_qs[__queue];
	काष्ठा net_device *dev = card->dev;
	काष्ठा netdev_queue *txq;
	पूर्णांक i;

	QETH_CARD_TEXT(card, 6, "qdouhdl");
	अगर (qdio_error & QDIO_ERROR_FATAL) अणु
		QETH_CARD_TEXT(card, 2, "achkcond");
		netअगर_tx_stop_all_queues(dev);
		qeth_schedule_recovery(card);
		वापस;
	पूर्ण

	क्रम (i = first_element; i < (first_element + count); ++i) अणु
		काष्ठा qeth_qdio_out_buffer *buf = queue->bufs[QDIO_BUFNR(i)];

		qeth_handle_send_error(card, buf, qdio_error);
		qeth_clear_output_buffer(queue, buf, qdio_error, 0);
	पूर्ण

	atomic_sub(count, &queue->used_buffers);
	qeth_check_outbound_queue(queue);

	txq = netdev_get_tx_queue(dev, __queue);
	/* xmit may have observed the full-condition, but not yet stopped the
	 * txq. In which हाल the code below won't trigger. So beक्रमe वापसing,
	 * xmit will re-check the txq's fill level and wake it up अगर needed.
	 */
	अगर (netअगर_tx_queue_stopped(txq) && !qeth_out_queue_is_full(queue))
		netअगर_tx_wake_queue(txq);
पूर्ण

/**
 * Note: Function assumes that we have 4 outbound queues.
 */
पूर्णांक qeth_get_priority_queue(काष्ठा qeth_card *card, काष्ठा sk_buff *skb)
अणु
	काष्ठा vlan_ethhdr *veth = vlan_eth_hdr(skb);
	u8 tos;

	चयन (card->qdio.करो_prio_queueing) अणु
	हाल QETH_PRIO_Q_ING_TOS:
	हाल QETH_PRIO_Q_ING_PREC:
		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			tos = ipv4_get_dsfield(ip_hdr(skb));
			अवरोध;
		हाल htons(ETH_P_IPV6):
			tos = ipv6_get_dsfield(ipv6_hdr(skb));
			अवरोध;
		शेष:
			वापस card->qdio.शेष_out_queue;
		पूर्ण
		अगर (card->qdio.करो_prio_queueing == QETH_PRIO_Q_ING_PREC)
			वापस ~tos >> 6 & 3;
		अगर (tos & IPTOS_MINCOST)
			वापस 3;
		अगर (tos & IPTOS_RELIABILITY)
			वापस 2;
		अगर (tos & IPTOS_THROUGHPUT)
			वापस 1;
		अगर (tos & IPTOS_LOWDELAY)
			वापस 0;
		अवरोध;
	हाल QETH_PRIO_Q_ING_SKB:
		अगर (skb->priority > 5)
			वापस 0;
		वापस ~skb->priority >> 1 & 3;
	हाल QETH_PRIO_Q_ING_VLAN:
		अगर (veth->h_vlan_proto == htons(ETH_P_8021Q))
			वापस ~ntohs(veth->h_vlan_TCI) >>
			       (VLAN_PRIO_SHIFT + 1) & 3;
		अवरोध;
	हाल QETH_PRIO_Q_ING_FIXED:
		वापस card->qdio.शेष_out_queue;
	शेष:
		अवरोध;
	पूर्ण
	वापस card->qdio.शेष_out_queue;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_get_priority_queue);

/**
 * qeth_get_elements_क्रम_frags() -	find number of SBALEs क्रम skb frags.
 * @skb:				SKB address
 *
 * Returns the number of pages, and thus QDIO buffer elements, needed to cover
 * fragmented part of the SKB. Returns zero क्रम linear SKB.
 */
अटल पूर्णांक qeth_get_elements_क्रम_frags(काष्ठा sk_buff *skb)
अणु
	पूर्णांक cnt, elements = 0;

	क्रम (cnt = 0; cnt < skb_shinfo(skb)->nr_frags; cnt++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[cnt];

		elements += qeth_get_elements_क्रम_range(
			(addr_t)skb_frag_address(frag),
			(addr_t)skb_frag_address(frag) + skb_frag_size(frag));
	पूर्ण
	वापस elements;
पूर्ण

/**
 * qeth_count_elements() -	Counts the number of QDIO buffer elements needed
 *				to transmit an skb.
 * @skb:			the skb to operate on.
 * @data_offset:		skip this part of the skb's linear data
 *
 * Returns the number of pages, and thus QDIO buffer elements, needed to map the
 * skb's data (both its linear part and paged fragments).
 */
अचिन्हित पूर्णांक qeth_count_elements(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक data_offset)
अणु
	अचिन्हित पूर्णांक elements = qeth_get_elements_क्रम_frags(skb);
	addr_t end = (addr_t)skb->data + skb_headlen(skb);
	addr_t start = (addr_t)skb->data + data_offset;

	अगर (start != end)
		elements += qeth_get_elements_क्रम_range(start, end);
	वापस elements;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_count_elements);

#घोषणा QETH_HDR_CACHE_OBJ_SIZE		(माप(काष्ठा qeth_hdr_tso) + \
					 MAX_TCP_HEADER)

/**
 * qeth_add_hw_header() - add a HW header to an skb.
 * @skb: skb that the HW header should be added to.
 * @hdr: द्विगुन poपूर्णांकer to a qeth_hdr. When वापसing with >= 0,
 *	 it contains a valid poपूर्णांकer to a qeth_hdr.
 * @hdr_len: length of the HW header.
 * @proto_len: length of protocol headers that need to be in same page as the
 *	       HW header.
 *
 * Returns the pushed length. If the header can't be pushed on
 * (eg. because it would cross a page boundary), it is allocated from
 * the cache instead and 0 is वापसed.
 * The number of needed buffer elements is वापसed in @elements.
 * Error to create the hdr is indicated by वापसing with < 0.
 */
अटल पूर्णांक qeth_add_hw_header(काष्ठा qeth_qdio_out_q *queue,
			      काष्ठा sk_buff *skb, काष्ठा qeth_hdr **hdr,
			      अचिन्हित पूर्णांक hdr_len, अचिन्हित पूर्णांक proto_len,
			      अचिन्हित पूर्णांक *elements)
अणु
	gfp_t gfp = GFP_ATOMIC | (skb_pfmeदो_स्मृति(skb) ? __GFP_MEMALLOC : 0);
	स्थिर अचिन्हित पूर्णांक contiguous = proto_len ? proto_len : 1;
	स्थिर अचिन्हित पूर्णांक max_elements = queue->max_elements;
	अचिन्हित पूर्णांक __elements;
	addr_t start, end;
	bool push_ok;
	पूर्णांक rc;

check_layout:
	start = (addr_t)skb->data - hdr_len;
	end = (addr_t)skb->data;

	अगर (qeth_get_elements_क्रम_range(start, end + contiguous) == 1) अणु
		/* Push HW header पूर्णांकo same page as first protocol header. */
		push_ok = true;
		/* ... but TSO always needs a separate element क्रम headers: */
		अगर (skb_is_gso(skb))
			__elements = 1 + qeth_count_elements(skb, proto_len);
		अन्यथा
			__elements = qeth_count_elements(skb, 0);
	पूर्ण अन्यथा अगर (!proto_len && PAGE_ALIGNED(skb->data)) अणु
		/* Push HW header पूर्णांकo preceding page, flush with skb->data. */
		push_ok = true;
		__elements = 1 + qeth_count_elements(skb, 0);
	पूर्ण अन्यथा अणु
		/* Use header cache, copy protocol headers up. */
		push_ok = false;
		__elements = 1 + qeth_count_elements(skb, proto_len);
	पूर्ण

	/* Compress skb to fit पूर्णांकo one IO buffer: */
	अगर (__elements > max_elements) अणु
		अगर (!skb_is_nonlinear(skb)) अणु
			/* Drop it, no easy way of shrinking it further. */
			QETH_DBF_MESSAGE(2, "Dropped an oversized skb (Max Elements=%u / Actual=%u / Length=%u).\n",
					 max_elements, __elements, skb->len);
			वापस -E2BIG;
		पूर्ण

		rc = skb_linearize(skb);
		अगर (rc) अणु
			QETH_TXQ_STAT_INC(queue, skbs_linearized_fail);
			वापस rc;
		पूर्ण

		QETH_TXQ_STAT_INC(queue, skbs_linearized);
		/* Linearization changed the layout, re-evaluate: */
		जाओ check_layout;
	पूर्ण

	*elements = __elements;
	/* Add the header: */
	अगर (push_ok) अणु
		*hdr = skb_push(skb, hdr_len);
		वापस hdr_len;
	पूर्ण

	/* Fall back to cache element with known-good alignment: */
	अगर (hdr_len + proto_len > QETH_HDR_CACHE_OBJ_SIZE)
		वापस -E2BIG;
	*hdr = kmem_cache_alloc(qeth_core_header_cache, gfp);
	अगर (!*hdr)
		वापस -ENOMEM;
	/* Copy protocol headers behind HW header: */
	skb_copy_from_linear_data(skb, ((अक्षर *)*hdr) + hdr_len, proto_len);
	वापस 0;
पूर्ण

अटल bool qeth_iqd_may_bulk(काष्ठा qeth_qdio_out_q *queue,
			      काष्ठा sk_buff *curr_skb,
			      काष्ठा qeth_hdr *curr_hdr)
अणु
	काष्ठा qeth_qdio_out_buffer *buffer = queue->bufs[queue->bulk_start];
	काष्ठा qeth_hdr *prev_hdr = queue->prev_hdr;

	अगर (!prev_hdr)
		वापस true;

	/* All packets must have the same target: */
	अगर (curr_hdr->hdr.l2.id == QETH_HEADER_TYPE_LAYER2) अणु
		काष्ठा sk_buff *prev_skb = skb_peek(&buffer->skb_list);

		वापस ether_addr_equal(eth_hdr(prev_skb)->h_dest,
					eth_hdr(curr_skb)->h_dest) &&
		       qeth_l2_same_vlan(&prev_hdr->hdr.l2, &curr_hdr->hdr.l2);
	पूर्ण

	वापस qeth_l3_same_next_hop(&prev_hdr->hdr.l3, &curr_hdr->hdr.l3) &&
	       qeth_l3_iqd_same_vlan(&prev_hdr->hdr.l3, &curr_hdr->hdr.l3);
पूर्ण

/**
 * qeth_fill_buffer() - map skb पूर्णांकo an output buffer
 * @buf:	buffer to transport the skb
 * @skb:	skb to map पूर्णांकo the buffer
 * @hdr:	qeth_hdr क्रम this skb. Either at skb->data, or allocated
 *		from qeth_core_header_cache.
 * @offset:	when mapping the skb, start at skb->data + offset
 * @hd_len:	अगर > 0, build a dedicated header element of this size
 */
अटल अचिन्हित पूर्णांक qeth_fill_buffer(काष्ठा qeth_qdio_out_buffer *buf,
				     काष्ठा sk_buff *skb, काष्ठा qeth_hdr *hdr,
				     अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक hd_len)
अणु
	काष्ठा qdio_buffer *buffer = buf->buffer;
	पूर्णांक element = buf->next_element_to_fill;
	पूर्णांक length = skb_headlen(skb) - offset;
	अक्षर *data = skb->data + offset;
	अचिन्हित पूर्णांक elem_length, cnt;
	bool is_first_elem = true;

	__skb_queue_tail(&buf->skb_list, skb);

	/* build dedicated element क्रम HW Header */
	अगर (hd_len) अणु
		is_first_elem = false;

		buffer->element[element].addr = virt_to_phys(hdr);
		buffer->element[element].length = hd_len;
		buffer->element[element].eflags = SBAL_EFLAGS_FIRST_FRAG;

		/* HW header is allocated from cache: */
		अगर ((व्योम *)hdr != skb->data)
			buf->is_header[element] = 1;
		/* HW header was pushed and is contiguous with linear part: */
		अन्यथा अगर (length > 0 && !PAGE_ALIGNED(data) &&
			 (data == (अक्षर *)hdr + hd_len))
			buffer->element[element].eflags |=
				SBAL_EFLAGS_CONTIGUOUS;

		element++;
	पूर्ण

	/* map linear part पूर्णांकo buffer element(s) */
	जबतक (length > 0) अणु
		elem_length = min_t(अचिन्हित पूर्णांक, length,
				    PAGE_SIZE - offset_in_page(data));

		buffer->element[element].addr = virt_to_phys(data);
		buffer->element[element].length = elem_length;
		length -= elem_length;
		अगर (is_first_elem) अणु
			is_first_elem = false;
			अगर (length || skb_is_nonlinear(skb))
				/* skb needs additional elements */
				buffer->element[element].eflags =
					SBAL_EFLAGS_FIRST_FRAG;
			अन्यथा
				buffer->element[element].eflags = 0;
		पूर्ण अन्यथा अणु
			buffer->element[element].eflags =
				SBAL_EFLAGS_MIDDLE_FRAG;
		पूर्ण

		data += elem_length;
		element++;
	पूर्ण

	/* map page frags पूर्णांकo buffer element(s) */
	क्रम (cnt = 0; cnt < skb_shinfo(skb)->nr_frags; cnt++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[cnt];

		data = skb_frag_address(frag);
		length = skb_frag_size(frag);
		जबतक (length > 0) अणु
			elem_length = min_t(अचिन्हित पूर्णांक, length,
					    PAGE_SIZE - offset_in_page(data));

			buffer->element[element].addr = virt_to_phys(data);
			buffer->element[element].length = elem_length;
			buffer->element[element].eflags =
				SBAL_EFLAGS_MIDDLE_FRAG;

			length -= elem_length;
			data += elem_length;
			element++;
		पूर्ण
	पूर्ण

	अगर (buffer->element[element - 1].eflags)
		buffer->element[element - 1].eflags = SBAL_EFLAGS_LAST_FRAG;
	buf->next_element_to_fill = element;
	वापस element;
पूर्ण

अटल पूर्णांक __qeth_xmit(काष्ठा qeth_card *card, काष्ठा qeth_qdio_out_q *queue,
		       काष्ठा sk_buff *skb, अचिन्हित पूर्णांक elements,
		       काष्ठा qeth_hdr *hdr, अचिन्हित पूर्णांक offset,
		       अचिन्हित पूर्णांक hd_len)
अणु
	अचिन्हित पूर्णांक bytes = qdisc_pkt_len(skb);
	काष्ठा qeth_qdio_out_buffer *buffer;
	अचिन्हित पूर्णांक next_element;
	काष्ठा netdev_queue *txq;
	bool stopped = false;
	bool flush;

	buffer = queue->bufs[QDIO_BUFNR(queue->bulk_start + queue->bulk_count)];
	txq = netdev_get_tx_queue(card->dev, skb_get_queue_mapping(skb));

	/* Just a sanity check, the wake/stop logic should ensure that we always
	 * get a मुक्त buffer.
	 */
	अगर (atomic_पढ़ो(&buffer->state) != QETH_QDIO_BUF_EMPTY)
		वापस -EBUSY;

	flush = !qeth_iqd_may_bulk(queue, skb, hdr);

	अगर (flush ||
	    (buffer->next_element_to_fill + elements > queue->max_elements)) अणु
		अगर (buffer->next_element_to_fill > 0) अणु
			atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
			queue->bulk_count++;
		पूर्ण

		अगर (queue->bulk_count >= queue->bulk_max)
			flush = true;

		अगर (flush)
			qeth_flush_queue(queue);

		buffer = queue->bufs[QDIO_BUFNR(queue->bulk_start +
						queue->bulk_count)];

		/* Sanity-check again: */
		अगर (atomic_पढ़ो(&buffer->state) != QETH_QDIO_BUF_EMPTY)
			वापस -EBUSY;
	पूर्ण

	अगर (buffer->next_element_to_fill == 0 &&
	    atomic_inc_वापस(&queue->used_buffers) >= QDIO_MAX_BUFFERS_PER_Q) अणु
		/* If a TX completion happens right _here_ and misses to wake
		 * the txq, then our re-check below will catch the race.
		 */
		QETH_TXQ_STAT_INC(queue, stopped);
		netअगर_tx_stop_queue(txq);
		stopped = true;
	पूर्ण

	next_element = qeth_fill_buffer(buffer, skb, hdr, offset, hd_len);
	buffer->bytes += bytes;
	buffer->frames += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;
	queue->prev_hdr = hdr;

	flush = __netdev_tx_sent_queue(txq, bytes,
				       !stopped && netdev_xmit_more());

	अगर (flush || next_element >= queue->max_elements) अणु
		atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
		queue->bulk_count++;

		अगर (queue->bulk_count >= queue->bulk_max)
			flush = true;

		अगर (flush)
			qeth_flush_queue(queue);
	पूर्ण

	अगर (stopped && !qeth_out_queue_is_full(queue))
		netअगर_tx_start_queue(txq);
	वापस 0;
पूर्ण

पूर्णांक qeth_करो_send_packet(काष्ठा qeth_card *card, काष्ठा qeth_qdio_out_q *queue,
			काष्ठा sk_buff *skb, काष्ठा qeth_hdr *hdr,
			अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक hd_len,
			पूर्णांक elements_needed)
अणु
	अचिन्हित पूर्णांक start_index = queue->next_buf_to_fill;
	काष्ठा qeth_qdio_out_buffer *buffer;
	अचिन्हित पूर्णांक next_element;
	काष्ठा netdev_queue *txq;
	bool stopped = false;
	पूर्णांक flush_count = 0;
	पूर्णांक करो_pack = 0;
	पूर्णांक rc = 0;

	buffer = queue->bufs[queue->next_buf_to_fill];

	/* Just a sanity check, the wake/stop logic should ensure that we always
	 * get a मुक्त buffer.
	 */
	अगर (atomic_पढ़ो(&buffer->state) != QETH_QDIO_BUF_EMPTY)
		वापस -EBUSY;

	txq = netdev_get_tx_queue(card->dev, skb_get_queue_mapping(skb));

	/* check अगर we need to चयन packing state of this queue */
	qeth_चयन_to_packing_अगर_needed(queue);
	अगर (queue->करो_pack) अणु
		करो_pack = 1;
		/* करोes packet fit in current buffer? */
		अगर (buffer->next_element_to_fill + elements_needed >
		    queue->max_elements) अणु
			/* ... no -> set state PRIMED */
			atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
			flush_count++;
			queue->next_buf_to_fill =
				QDIO_BUFNR(queue->next_buf_to_fill + 1);
			buffer = queue->bufs[queue->next_buf_to_fill];

			/* We stepped क्रमward, so sanity-check again: */
			अगर (atomic_पढ़ो(&buffer->state) !=
			    QETH_QDIO_BUF_EMPTY) अणु
				qeth_flush_buffers(queue, start_index,
							   flush_count);
				rc = -EBUSY;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (buffer->next_element_to_fill == 0 &&
	    atomic_inc_वापस(&queue->used_buffers) >= QDIO_MAX_BUFFERS_PER_Q) अणु
		/* If a TX completion happens right _here_ and misses to wake
		 * the txq, then our re-check below will catch the race.
		 */
		QETH_TXQ_STAT_INC(queue, stopped);
		netअगर_tx_stop_queue(txq);
		stopped = true;
	पूर्ण

	next_element = qeth_fill_buffer(buffer, skb, hdr, offset, hd_len);
	buffer->bytes += qdisc_pkt_len(skb);
	buffer->frames += skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 1;

	अगर (queue->करो_pack)
		QETH_TXQ_STAT_INC(queue, skbs_pack);
	अगर (!queue->करो_pack || stopped || next_element >= queue->max_elements) अणु
		flush_count++;
		atomic_set(&buffer->state, QETH_QDIO_BUF_PRIMED);
		queue->next_buf_to_fill =
				QDIO_BUFNR(queue->next_buf_to_fill + 1);
	पूर्ण

	अगर (flush_count)
		qeth_flush_buffers(queue, start_index, flush_count);

out:
	अगर (करो_pack)
		QETH_TXQ_STAT_ADD(queue, bufs_pack, flush_count);

	अगर (stopped && !qeth_out_queue_is_full(queue))
		netअगर_tx_start_queue(txq);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_करो_send_packet);

अटल व्योम qeth_fill_tso_ext(काष्ठा qeth_hdr_tso *hdr,
			      अचिन्हित पूर्णांक payload_len, काष्ठा sk_buff *skb,
			      अचिन्हित पूर्णांक proto_len)
अणु
	काष्ठा qeth_hdr_ext_tso *ext = &hdr->ext;

	ext->hdr_tot_len = माप(*ext);
	ext->imb_hdr_no = 1;
	ext->hdr_type = 1;
	ext->hdr_version = 1;
	ext->hdr_len = 28;
	ext->payload_len = payload_len;
	ext->mss = skb_shinfo(skb)->gso_size;
	ext->dg_hdr_len = proto_len;
पूर्ण

पूर्णांक qeth_xmit(काष्ठा qeth_card *card, काष्ठा sk_buff *skb,
	      काष्ठा qeth_qdio_out_q *queue, __be16 proto,
	      व्योम (*fill_header)(काष्ठा qeth_qdio_out_q *queue,
				  काष्ठा qeth_hdr *hdr, काष्ठा sk_buff *skb,
				  __be16 proto, अचिन्हित पूर्णांक data_len))
अणु
	अचिन्हित पूर्णांक proto_len, hw_hdr_len;
	अचिन्हित पूर्णांक frame_len = skb->len;
	bool is_tso = skb_is_gso(skb);
	अचिन्हित पूर्णांक data_offset = 0;
	काष्ठा qeth_hdr *hdr = शून्य;
	अचिन्हित पूर्णांक hd_len = 0;
	अचिन्हित पूर्णांक elements;
	पूर्णांक push_len, rc;

	अगर (is_tso) अणु
		hw_hdr_len = माप(काष्ठा qeth_hdr_tso);
		proto_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	पूर्ण अन्यथा अणु
		hw_hdr_len = माप(काष्ठा qeth_hdr);
		proto_len = (IS_IQD(card) && IS_LAYER2(card)) ? ETH_HLEN : 0;
	पूर्ण

	rc = skb_cow_head(skb, hw_hdr_len);
	अगर (rc)
		वापस rc;

	push_len = qeth_add_hw_header(queue, skb, &hdr, hw_hdr_len, proto_len,
				      &elements);
	अगर (push_len < 0)
		वापस push_len;
	अगर (is_tso || !push_len) अणु
		/* HW header needs its own buffer element. */
		hd_len = hw_hdr_len + proto_len;
		data_offset = push_len + proto_len;
	पूर्ण
	स_रखो(hdr, 0, hw_hdr_len);
	fill_header(queue, hdr, skb, proto, frame_len);
	अगर (is_tso)
		qeth_fill_tso_ext((काष्ठा qeth_hdr_tso *) hdr,
				  frame_len - proto_len, skb, proto_len);

	अगर (IS_IQD(card)) अणु
		rc = __qeth_xmit(card, queue, skb, elements, hdr, data_offset,
				 hd_len);
	पूर्ण अन्यथा अणु
		/* TODO: drop skb_orphan() once TX completion is fast enough */
		skb_orphan(skb);
		spin_lock(&queue->lock);
		rc = qeth_करो_send_packet(card, queue, skb, hdr, data_offset,
					 hd_len, elements);
		spin_unlock(&queue->lock);
	पूर्ण

	अगर (rc && !push_len)
		kmem_cache_मुक्त(qeth_core_header_cache, hdr);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_xmit);

अटल पूर्णांक qeth_setadp_promisc_mode_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_ipacmd_setadpparms *setparms;

	QETH_CARD_TEXT(card, 4, "prmadpcb");

	setparms = &(cmd->data.setadapterparms);
	अगर (qeth_setadpparms_inspect_rc(cmd)) अणु
		QETH_CARD_TEXT_(card, 4, "prmrc%x", cmd->hdr.वापस_code);
		setparms->data.mode = SET_PROMISC_MODE_OFF;
	पूर्ण
	card->info.promisc_mode = setparms->data.mode;
	वापस (cmd->hdr.वापस_code) ? -EIO : 0;
पूर्ण

व्योम qeth_setadp_promisc_mode(काष्ठा qeth_card *card, bool enable)
अणु
	क्रमागत qeth_ipa_promisc_modes mode = enable ? SET_PROMISC_MODE_ON :
						    SET_PROMISC_MODE_OFF;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 4, "setprom");
	QETH_CARD_TEXT_(card, 4, "mode:%x", mode);

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_SET_PROMISC_MODE,
				   SETADP_DATA_SIZखातापूर्ण(mode));
	अगर (!iob)
		वापस;
	cmd = __ipa_cmd(iob);
	cmd->data.setadapterparms.data.mode = mode;
	qeth_send_ipa_cmd(card, iob, qeth_setadp_promisc_mode_cb, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_setadp_promisc_mode);

अटल पूर्णांक qeth_setadpparms_change_macaddr_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_ipacmd_setadpparms *adp_cmd;

	QETH_CARD_TEXT(card, 4, "chgmaccb");
	अगर (qeth_setadpparms_inspect_rc(cmd))
		वापस -EIO;

	adp_cmd = &cmd->data.setadapterparms;
	अगर (!is_valid_ether_addr(adp_cmd->data.change_addr.addr))
		वापस -EADDRNOTAVAIL;

	अगर (IS_LAYER2(card) && IS_OSD(card) && !IS_VM_NIC(card) &&
	    !(adp_cmd->hdr.flags & QETH_SETADP_FLAGS_VIRTUAL_MAC))
		वापस -EADDRNOTAVAIL;

	ether_addr_copy(card->dev->dev_addr, adp_cmd->data.change_addr.addr);
	वापस 0;
पूर्ण

पूर्णांक qeth_setadpparms_change_macaddr(काष्ठा qeth_card *card)
अणु
	पूर्णांक rc;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;

	QETH_CARD_TEXT(card, 4, "chgmac");

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_ALTER_MAC_ADDRESS,
				   SETADP_DATA_SIZखातापूर्ण(change_addr));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	cmd->data.setadapterparms.data.change_addr.cmd = CHANGE_ADDR_READ_MAC;
	cmd->data.setadapterparms.data.change_addr.addr_size = ETH_ALEN;
	ether_addr_copy(cmd->data.setadapterparms.data.change_addr.addr,
			card->dev->dev_addr);
	rc = qeth_send_ipa_cmd(card, iob, qeth_setadpparms_change_macaddr_cb,
			       शून्य);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_setadpparms_change_macaddr);

अटल पूर्णांक qeth_setadpparms_set_access_ctrl_cb(काष्ठा qeth_card *card,
		काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_set_access_ctrl *access_ctrl_req;

	QETH_CARD_TEXT(card, 4, "setaccb");

	access_ctrl_req = &cmd->data.setadapterparms.data.set_access_ctrl;
	QETH_CARD_TEXT_(card, 2, "rc=%d",
			cmd->data.setadapterparms.hdr.वापस_code);
	अगर (cmd->data.setadapterparms.hdr.वापस_code !=
						SET_ACCESS_CTRL_RC_SUCCESS)
		QETH_DBF_MESSAGE(3, "ERR:SET_ACCESS_CTRL(%#x) on device %x: %#x\n",
				 access_ctrl_req->subcmd_code, CARD_DEVID(card),
				 cmd->data.setadapterparms.hdr.वापस_code);
	चयन (qeth_setadpparms_inspect_rc(cmd)) अणु
	हाल SET_ACCESS_CTRL_RC_SUCCESS:
		अगर (access_ctrl_req->subcmd_code == ISOLATION_MODE_NONE)
			dev_info(&card->gdev->dev,
			    "QDIO data connection isolation is deactivated\n");
		अन्यथा
			dev_info(&card->gdev->dev,
			    "QDIO data connection isolation is activated\n");
		वापस 0;
	हाल SET_ACCESS_CTRL_RC_ALREADY_NOT_ISOLATED:
		QETH_DBF_MESSAGE(2, "QDIO data connection isolation on device %x already deactivated\n",
				 CARD_DEVID(card));
		वापस 0;
	हाल SET_ACCESS_CTRL_RC_ALREADY_ISOLATED:
		QETH_DBF_MESSAGE(2, "QDIO data connection isolation on device %x already activated\n",
				 CARD_DEVID(card));
		वापस 0;
	हाल SET_ACCESS_CTRL_RC_NOT_SUPPORTED:
		dev_err(&card->gdev->dev, "Adapter does not "
			"support QDIO data connection isolation\n");
		वापस -EOPNOTSUPP;
	हाल SET_ACCESS_CTRL_RC_NONE_SHARED_ADAPTER:
		dev_err(&card->gdev->dev,
			"Adapter is dedicated. "
			"QDIO data connection isolation not supported\n");
		वापस -EOPNOTSUPP;
	हाल SET_ACCESS_CTRL_RC_ACTIVE_CHECKSUM_OFF:
		dev_err(&card->gdev->dev,
			"TSO does not permit QDIO data connection isolation\n");
		वापस -EPERM;
	हाल SET_ACCESS_CTRL_RC_REFLREL_UNSUPPORTED:
		dev_err(&card->gdev->dev, "The adjacent switch port does not "
			"support reflective relay mode\n");
		वापस -EOPNOTSUPP;
	हाल SET_ACCESS_CTRL_RC_REFLREL_FAILED:
		dev_err(&card->gdev->dev, "The reflective relay mode cannot be "
					"enabled at the adjacent switch port");
		वापस -EREMOTEIO;
	हाल SET_ACCESS_CTRL_RC_REFLREL_DEACT_FAILED:
		dev_warn(&card->gdev->dev, "Turning off reflective relay mode "
					"at the adjacent switch failed\n");
		/* benign error जबतक disabling ISOLATION_MODE_FWD */
		वापस 0;
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

पूर्णांक qeth_setadpparms_set_access_ctrl(काष्ठा qeth_card *card,
				     क्रमागत qeth_ipa_isolation_modes mode)
अणु
	पूर्णांक rc;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;
	काष्ठा qeth_set_access_ctrl *access_ctrl_req;

	QETH_CARD_TEXT(card, 4, "setacctl");

	अगर (!qeth_adp_supported(card, IPA_SETADP_SET_ACCESS_CONTROL)) अणु
		dev_err(&card->gdev->dev,
			"Adapter does not support QDIO data connection isolation\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_SET_ACCESS_CONTROL,
				   SETADP_DATA_SIZखातापूर्ण(set_access_ctrl));
	अगर (!iob)
		वापस -ENOMEM;
	cmd = __ipa_cmd(iob);
	access_ctrl_req = &cmd->data.setadapterparms.data.set_access_ctrl;
	access_ctrl_req->subcmd_code = mode;

	rc = qeth_send_ipa_cmd(card, iob, qeth_setadpparms_set_access_ctrl_cb,
			       शून्य);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "rc=%d", rc);
		QETH_DBF_MESSAGE(3, "IPA(SET_ACCESS_CTRL(%d) on device %x: sent failed\n",
				 rc, CARD_DEVID(card));
	पूर्ण

	वापस rc;
पूर्ण

व्योम qeth_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा qeth_card *card;

	card = dev->ml_priv;
	QETH_CARD_TEXT(card, 4, "txtimeo");
	qeth_schedule_recovery(card);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_tx_समयout);

अटल पूर्णांक qeth_mdio_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	पूर्णांक rc = 0;

	चयन (regnum) अणु
	हाल MII_BMCR: /* Basic mode control रेजिस्टर */
		rc = BMCR_FULLDPLX;
		अगर ((card->info.link_type != QETH_LINK_TYPE_GBIT_ETH) &&
		    (card->info.link_type != QETH_LINK_TYPE_OSN) &&
		    (card->info.link_type != QETH_LINK_TYPE_10GBIT_ETH) &&
		    (card->info.link_type != QETH_LINK_TYPE_25GBIT_ETH))
			rc |= BMCR_SPEED100;
		अवरोध;
	हाल MII_BMSR: /* Basic mode status रेजिस्टर */
		rc = BMSR_ERCAP | BMSR_ANEGCOMPLETE | BMSR_LSTATUS |
		     BMSR_10HALF | BMSR_10FULL | BMSR_100HALF | BMSR_100FULL |
		     BMSR_100BASE4;
		अवरोध;
	हाल MII_PHYSID1: /* PHYS ID 1 */
		rc = (dev->dev_addr[0] << 16) | (dev->dev_addr[1] << 8) |
		     dev->dev_addr[2];
		rc = (rc >> 5) & 0xFFFF;
		अवरोध;
	हाल MII_PHYSID2: /* PHYS ID 2 */
		rc = (dev->dev_addr[2] << 10) & 0xFFFF;
		अवरोध;
	हाल MII_ADVERTISE: /* Advertisement control reg */
		rc = ADVERTISE_ALL;
		अवरोध;
	हाल MII_LPA: /* Link partner ability reg */
		rc = LPA_10HALF | LPA_10FULL | LPA_100HALF | LPA_100FULL |
		     LPA_100BASE4 | LPA_LPACK;
		अवरोध;
	हाल MII_EXPANSION: /* Expansion रेजिस्टर */
		अवरोध;
	हाल MII_DCOUNTER: /* disconnect counter */
		अवरोध;
	हाल MII_FCSCOUNTER: /* false carrier counter */
		अवरोध;
	हाल MII_NWAYTEST: /* N-way स्वतः-neg test रेजिस्टर */
		अवरोध;
	हाल MII_RERRCOUNTER: /* rx error counter */
		rc = card->stats.rx_length_errors +
		     card->stats.rx_frame_errors +
		     card->stats.rx_fअगरo_errors;
		अवरोध;
	हाल MII_SREVISION: /* silicon revision */
		अवरोध;
	हाल MII_RESV1: /* reserved 1 */
		अवरोध;
	हाल MII_LBRERROR: /* loopback, rx, bypass error */
		अवरोध;
	हाल MII_PHYADDR: /* physical address */
		अवरोध;
	हाल MII_RESV2: /* reserved 2 */
		अवरोध;
	हाल MII_TPISTATUS: /* TPI status क्रम 10mbps */
		अवरोध;
	हाल MII_NCONFIG: /* network पूर्णांकerface config */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_snmp_command_cb(काष्ठा qeth_card *card,
				काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_arp_query_info *qinfo = reply->param;
	काष्ठा qeth_ipacmd_setadpparms *adp_cmd;
	अचिन्हित पूर्णांक data_len;
	व्योम *snmp_data;

	QETH_CARD_TEXT(card, 3, "snpcmdcb");

	अगर (cmd->hdr.वापस_code) अणु
		QETH_CARD_TEXT_(card, 4, "scer1%x", cmd->hdr.वापस_code);
		वापस -EIO;
	पूर्ण
	अगर (cmd->data.setadapterparms.hdr.वापस_code) अणु
		cmd->hdr.वापस_code =
			cmd->data.setadapterparms.hdr.वापस_code;
		QETH_CARD_TEXT_(card, 4, "scer2%x", cmd->hdr.वापस_code);
		वापस -EIO;
	पूर्ण

	adp_cmd = &cmd->data.setadapterparms;
	data_len = adp_cmd->hdr.cmdlength - माप(adp_cmd->hdr);
	अगर (adp_cmd->hdr.seq_no == 1) अणु
		snmp_data = &adp_cmd->data.snmp;
	पूर्ण अन्यथा अणु
		snmp_data = &adp_cmd->data.snmp.request;
		data_len -= दुरत्व(काष्ठा qeth_snmp_cmd, request);
	पूर्ण

	/* check अगर there is enough room in userspace */
	अगर ((qinfo->udata_len - qinfo->udata_offset) < data_len) अणु
		QETH_CARD_TEXT_(card, 4, "scer3%i", -ENOSPC);
		वापस -ENOSPC;
	पूर्ण
	QETH_CARD_TEXT_(card, 4, "snore%i",
			cmd->data.setadapterparms.hdr.used_total);
	QETH_CARD_TEXT_(card, 4, "sseqn%i",
			cmd->data.setadapterparms.hdr.seq_no);
	/*copy entries to user buffer*/
	स_नकल(qinfo->udata + qinfo->udata_offset, snmp_data, data_len);
	qinfo->udata_offset += data_len;

	अगर (cmd->data.setadapterparms.hdr.seq_no <
	    cmd->data.setadapterparms.hdr.used_total)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_snmp_command(काष्ठा qeth_card *card, अक्षर __user *udata)
अणु
	काष्ठा qeth_snmp_ureq __user *ureq;
	काष्ठा qeth_cmd_buffer *iob;
	अचिन्हित पूर्णांक req_len;
	काष्ठा qeth_arp_query_info qinfo = अणु0, पूर्ण;
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 3, "snmpcmd");

	अगर (IS_VM_NIC(card))
		वापस -EOPNOTSUPP;

	अगर ((!qeth_adp_supported(card, IPA_SETADP_SET_SNMP_CONTROL)) &&
	    IS_LAYER3(card))
		वापस -EOPNOTSUPP;

	ureq = (काष्ठा qeth_snmp_ureq __user *) udata;
	अगर (get_user(qinfo.udata_len, &ureq->hdr.data_len) ||
	    get_user(req_len, &ureq->hdr.req_len))
		वापस -EFAULT;

	/* Sanitize user input, to aव्योम overflows in iob size calculation: */
	अगर (req_len > QETH_बफ_मानE)
		वापस -EINVAL;

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_SET_SNMP_CONTROL, req_len);
	अगर (!iob)
		वापस -ENOMEM;

	अगर (copy_from_user(&__ipa_cmd(iob)->data.setadapterparms.data.snmp,
			   &ureq->cmd, req_len)) अणु
		qeth_put_cmd(iob);
		वापस -EFAULT;
	पूर्ण

	qinfo.udata = kzalloc(qinfo.udata_len, GFP_KERNEL);
	अगर (!qinfo.udata) अणु
		qeth_put_cmd(iob);
		वापस -ENOMEM;
	पूर्ण
	qinfo.udata_offset = माप(काष्ठा qeth_snmp_ureq_hdr);

	rc = qeth_send_ipa_cmd(card, iob, qeth_snmp_command_cb, &qinfo);
	अगर (rc)
		QETH_DBF_MESSAGE(2, "SNMP command failed on device %x: (%#x)\n",
				 CARD_DEVID(card), rc);
	अन्यथा अणु
		अगर (copy_to_user(udata, qinfo.udata, qinfo.udata_len))
			rc = -EFAULT;
	पूर्ण

	kमुक्त(qinfo.udata);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_setadpparms_query_oat_cb(काष्ठा qeth_card *card,
					 काष्ठा qeth_reply *reply,
					 अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *)data;
	काष्ठा qeth_qoat_priv *priv = reply->param;
	पूर्णांक resdatalen;

	QETH_CARD_TEXT(card, 3, "qoatcb");
	अगर (qeth_setadpparms_inspect_rc(cmd))
		वापस -EIO;

	resdatalen = cmd->data.setadapterparms.hdr.cmdlength;

	अगर (resdatalen > (priv->buffer_len - priv->response_len))
		वापस -ENOSPC;

	स_नकल(priv->buffer + priv->response_len,
	       &cmd->data.setadapterparms.hdr, resdatalen);
	priv->response_len += resdatalen;

	अगर (cmd->data.setadapterparms.hdr.seq_no <
	    cmd->data.setadapterparms.hdr.used_total)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_query_oat_command(काष्ठा qeth_card *card, अक्षर __user *udata)
अणु
	पूर्णांक rc = 0;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_cmd *cmd;
	काष्ठा qeth_query_oat *oat_req;
	काष्ठा qeth_query_oat_data oat_data;
	काष्ठा qeth_qoat_priv priv;
	व्योम __user *पंचांगp;

	QETH_CARD_TEXT(card, 3, "qoatcmd");

	अगर (!qeth_adp_supported(card, IPA_SETADP_QUERY_OAT))
		वापस -EOPNOTSUPP;

	अगर (copy_from_user(&oat_data, udata, माप(oat_data)))
		वापस -EFAULT;

	priv.buffer_len = oat_data.buffer_len;
	priv.response_len = 0;
	priv.buffer = vzalloc(oat_data.buffer_len);
	अगर (!priv.buffer)
		वापस -ENOMEM;

	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_OAT,
				   SETADP_DATA_SIZखातापूर्ण(query_oat));
	अगर (!iob) अणु
		rc = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण
	cmd = __ipa_cmd(iob);
	oat_req = &cmd->data.setadapterparms.data.query_oat;
	oat_req->subcmd_code = oat_data.command;

	rc = qeth_send_ipa_cmd(card, iob, qeth_setadpparms_query_oat_cb, &priv);
	अगर (!rc) अणु
		पंचांगp = is_compat_task() ? compat_ptr(oat_data.ptr) :
					 u64_to_user_ptr(oat_data.ptr);
		oat_data.response_len = priv.response_len;

		अगर (copy_to_user(पंचांगp, priv.buffer, priv.response_len) ||
		    copy_to_user(udata, &oat_data, माप(oat_data)))
			rc = -EFAULT;
	पूर्ण

out_मुक्त:
	vमुक्त(priv.buffer);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_query_card_info_cb(काष्ठा qeth_card *card,
				   काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *)data;
	काष्ठा qeth_link_info *link_info = reply->param;
	काष्ठा qeth_query_card_info *card_info;

	QETH_CARD_TEXT(card, 2, "qcrdincb");
	अगर (qeth_setadpparms_inspect_rc(cmd))
		वापस -EIO;

	card_info = &cmd->data.setadapterparms.data.card_info;
	netdev_dbg(card->dev,
		   "card info: card_type=0x%02x, port_mode=0x%04x, port_speed=0x%08x\n",
		   card_info->card_type, card_info->port_mode,
		   card_info->port_speed);

	चयन (card_info->port_mode) अणु
	हाल CARD_INFO_PORTM_FULLDUPLEX:
		link_info->duplex = DUPLEX_FULL;
		अवरोध;
	हाल CARD_INFO_PORTM_HALFDUPLEX:
		link_info->duplex = DUPLEX_HALF;
		अवरोध;
	शेष:
		link_info->duplex = DUPLEX_UNKNOWN;
	पूर्ण

	चयन (card_info->card_type) अणु
	हाल CARD_INFO_TYPE_1G_COPPER_A:
	हाल CARD_INFO_TYPE_1G_COPPER_B:
		link_info->speed = SPEED_1000;
		link_info->port = PORT_TP;
		अवरोध;
	हाल CARD_INFO_TYPE_1G_FIBRE_A:
	हाल CARD_INFO_TYPE_1G_FIBRE_B:
		link_info->speed = SPEED_1000;
		link_info->port = PORT_FIBRE;
		अवरोध;
	हाल CARD_INFO_TYPE_10G_FIBRE_A:
	हाल CARD_INFO_TYPE_10G_FIBRE_B:
		link_info->speed = SPEED_10000;
		link_info->port = PORT_FIBRE;
		अवरोध;
	शेष:
		चयन (card_info->port_speed) अणु
		हाल CARD_INFO_PORTS_10M:
			link_info->speed = SPEED_10;
			अवरोध;
		हाल CARD_INFO_PORTS_100M:
			link_info->speed = SPEED_100;
			अवरोध;
		हाल CARD_INFO_PORTS_1G:
			link_info->speed = SPEED_1000;
			अवरोध;
		हाल CARD_INFO_PORTS_10G:
			link_info->speed = SPEED_10000;
			अवरोध;
		हाल CARD_INFO_PORTS_25G:
			link_info->speed = SPEED_25000;
			अवरोध;
		शेष:
			link_info->speed = SPEED_UNKNOWN;
		पूर्ण

		link_info->port = PORT_OTHER;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qeth_query_card_info(काष्ठा qeth_card *card,
			 काष्ठा qeth_link_info *link_info)
अणु
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 2, "qcrdinfo");
	अगर (!qeth_adp_supported(card, IPA_SETADP_QUERY_CARD_INFO))
		वापस -EOPNOTSUPP;
	iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_CARD_INFO, 0);
	अगर (!iob)
		वापस -ENOMEM;

	वापस qeth_send_ipa_cmd(card, iob, qeth_query_card_info_cb, link_info);
पूर्ण

अटल पूर्णांक qeth_init_link_info_oat_cb(काष्ठा qeth_card *card,
				      काष्ठा qeth_reply *reply_priv,
				      अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *)data;
	काष्ठा qeth_link_info *link_info = reply_priv->param;
	काष्ठा qeth_query_oat_physical_अगर *phys_अगर;
	काष्ठा qeth_query_oat_reply *reply;

	अगर (qeth_setadpparms_inspect_rc(cmd))
		वापस -EIO;

	/* Multi-part reply is unexpected, करोn't bother: */
	अगर (cmd->data.setadapterparms.hdr.used_total > 1)
		वापस -EINVAL;

	/* Expect the reply to start with phys_अगर data: */
	reply = &cmd->data.setadapterparms.data.query_oat.reply[0];
	अगर (reply->type != QETH_QOAT_REPLY_TYPE_PHYS_IF ||
	    reply->length < माप(*reply))
		वापस -EINVAL;

	phys_अगर = &reply->phys_अगर;

	चयन (phys_अगर->speed_duplex) अणु
	हाल QETH_QOAT_PHYS_SPEED_10M_HALF:
		link_info->speed = SPEED_10;
		link_info->duplex = DUPLEX_HALF;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_10M_FULL:
		link_info->speed = SPEED_10;
		link_info->duplex = DUPLEX_FULL;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_100M_HALF:
		link_info->speed = SPEED_100;
		link_info->duplex = DUPLEX_HALF;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_100M_FULL:
		link_info->speed = SPEED_100;
		link_info->duplex = DUPLEX_FULL;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_1000M_HALF:
		link_info->speed = SPEED_1000;
		link_info->duplex = DUPLEX_HALF;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_1000M_FULL:
		link_info->speed = SPEED_1000;
		link_info->duplex = DUPLEX_FULL;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_10G_FULL:
		link_info->speed = SPEED_10000;
		link_info->duplex = DUPLEX_FULL;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_25G_FULL:
		link_info->speed = SPEED_25000;
		link_info->duplex = DUPLEX_FULL;
		अवरोध;
	हाल QETH_QOAT_PHYS_SPEED_UNKNOWN:
	शेष:
		link_info->speed = SPEED_UNKNOWN;
		link_info->duplex = DUPLEX_UNKNOWN;
		अवरोध;
	पूर्ण

	चयन (phys_अगर->media_type) अणु
	हाल QETH_QOAT_PHYS_MEDIA_COPPER:
		link_info->port = PORT_TP;
		link_info->link_mode = QETH_LINK_MODE_UNKNOWN;
		अवरोध;
	हाल QETH_QOAT_PHYS_MEDIA_FIBRE_SHORT:
		link_info->port = PORT_FIBRE;
		link_info->link_mode = QETH_LINK_MODE_FIBRE_SHORT;
		अवरोध;
	हाल QETH_QOAT_PHYS_MEDIA_FIBRE_LONG:
		link_info->port = PORT_FIBRE;
		link_info->link_mode = QETH_LINK_MODE_FIBRE_LONG;
		अवरोध;
	शेष:
		link_info->port = PORT_OTHER;
		link_info->link_mode = QETH_LINK_MODE_UNKNOWN;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qeth_init_link_info(काष्ठा qeth_card *card)
अणु
	card->info.link_info.duplex = DUPLEX_FULL;

	अगर (IS_IQD(card) || IS_VM_NIC(card)) अणु
		card->info.link_info.speed = SPEED_10000;
		card->info.link_info.port = PORT_FIBRE;
		card->info.link_info.link_mode = QETH_LINK_MODE_FIBRE_SHORT;
	पूर्ण अन्यथा अणु
		चयन (card->info.link_type) अणु
		हाल QETH_LINK_TYPE_FAST_ETH:
		हाल QETH_LINK_TYPE_LANE_ETH100:
			card->info.link_info.speed = SPEED_100;
			card->info.link_info.port = PORT_TP;
			अवरोध;
		हाल QETH_LINK_TYPE_GBIT_ETH:
		हाल QETH_LINK_TYPE_LANE_ETH1000:
			card->info.link_info.speed = SPEED_1000;
			card->info.link_info.port = PORT_FIBRE;
			अवरोध;
		हाल QETH_LINK_TYPE_10GBIT_ETH:
			card->info.link_info.speed = SPEED_10000;
			card->info.link_info.port = PORT_FIBRE;
			अवरोध;
		हाल QETH_LINK_TYPE_25GBIT_ETH:
			card->info.link_info.speed = SPEED_25000;
			card->info.link_info.port = PORT_FIBRE;
			अवरोध;
		शेष:
			dev_info(&card->gdev->dev, "Unknown link type %x\n",
				 card->info.link_type);
			card->info.link_info.speed = SPEED_UNKNOWN;
			card->info.link_info.port = PORT_OTHER;
		पूर्ण

		card->info.link_info.link_mode = QETH_LINK_MODE_UNKNOWN;
	पूर्ण

	/* Get more accurate data via QUERY OAT: */
	अगर (qeth_adp_supported(card, IPA_SETADP_QUERY_OAT)) अणु
		काष्ठा qeth_link_info link_info;
		काष्ठा qeth_cmd_buffer *iob;

		iob = qeth_get_adapter_cmd(card, IPA_SETADP_QUERY_OAT,
					   SETADP_DATA_SIZखातापूर्ण(query_oat));
		अगर (iob) अणु
			काष्ठा qeth_ipa_cmd *cmd = __ipa_cmd(iob);
			काष्ठा qeth_query_oat *oat_req;

			oat_req = &cmd->data.setadapterparms.data.query_oat;
			oat_req->subcmd_code = QETH_QOAT_SCOPE_INTERFACE;

			अगर (!qeth_send_ipa_cmd(card, iob,
					       qeth_init_link_info_oat_cb,
					       &link_info)) अणु
				अगर (link_info.speed != SPEED_UNKNOWN)
					card->info.link_info.speed = link_info.speed;
				अगर (link_info.duplex != DUPLEX_UNKNOWN)
					card->info.link_info.duplex = link_info.duplex;
				अगर (link_info.port != PORT_OTHER)
					card->info.link_info.port = link_info.port;
				अगर (link_info.link_mode != QETH_LINK_MODE_UNKNOWN)
					card->info.link_info.link_mode = link_info.link_mode;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * qeth_vm_request_mac() - Request a hypervisor-managed MAC address
 * @card: poपूर्णांकer to a qeth_card
 *
 * Returns
 *	0, अगर a MAC address has been set क्रम the card's netdevice
 *	a वापस code, क्रम various error conditions
 */
पूर्णांक qeth_vm_request_mac(काष्ठा qeth_card *card)
अणु
	काष्ठा diag26c_mac_resp *response;
	काष्ठा diag26c_mac_req *request;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "vmreqmac");

	request = kzalloc(माप(*request), GFP_KERNEL | GFP_DMA);
	response = kzalloc(माप(*response), GFP_KERNEL | GFP_DMA);
	अगर (!request || !response) अणु
		rc = -ENOMEM;
		जाओ out;
	पूर्ण

	request->resp_buf_len = माप(*response);
	request->resp_version = DIAG26C_VERSION2;
	request->op_code = DIAG26C_GET_MAC;
	request->devno = card->info.ddev_devno;

	QETH_DBF_HEX(CTRL, 2, request, माप(*request));
	rc = diag26c(request, response, DIAG26C_MAC_SERVICES);
	QETH_DBF_HEX(CTRL, 2, request, माप(*request));
	अगर (rc)
		जाओ out;
	QETH_DBF_HEX(CTRL, 2, response, माप(*response));

	अगर (request->resp_buf_len < माप(*response) ||
	    response->version != request->resp_version) अणु
		rc = -EIO;
		QETH_CARD_TEXT(card, 2, "badresp");
		QETH_CARD_HEX(card, 2, &request->resp_buf_len,
			      माप(request->resp_buf_len));
	पूर्ण अन्यथा अगर (!is_valid_ether_addr(response->mac)) अणु
		rc = -EINVAL;
		QETH_CARD_TEXT(card, 2, "badmac");
		QETH_CARD_HEX(card, 2, response->mac, ETH_ALEN);
	पूर्ण अन्यथा अणु
		ether_addr_copy(card->dev->dev_addr, response->mac);
	पूर्ण

out:
	kमुक्त(response);
	kमुक्त(request);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_vm_request_mac);

अटल व्योम qeth_determine_capabilities(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_channel *channel = &card->data;
	काष्ठा ccw_device *ddev = channel->ccwdev;
	पूर्णांक rc;
	पूर्णांक ddev_offline = 0;

	QETH_CARD_TEXT(card, 2, "detcapab");
	अगर (!ddev->online) अणु
		ddev_offline = 1;
		rc = qeth_start_channel(channel);
		अगर (rc) अणु
			QETH_CARD_TEXT_(card, 2, "3err%d", rc);
			जाओ out;
		पूर्ण
	पूर्ण

	rc = qeth_पढ़ो_conf_data(card);
	अगर (rc) अणु
		QETH_DBF_MESSAGE(2, "qeth_read_conf_data on device %x returned %i\n",
				 CARD_DEVID(card), rc);
		QETH_CARD_TEXT_(card, 2, "5err%d", rc);
		जाओ out_offline;
	पूर्ण

	rc = qdio_get_ssqd_desc(ddev, &card->ssqd);
	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "6err%d", rc);

	QETH_CARD_TEXT_(card, 2, "qfmt%d", card->ssqd.qfmt);
	QETH_CARD_TEXT_(card, 2, "ac1:%02x", card->ssqd.qdioac1);
	QETH_CARD_TEXT_(card, 2, "ac2:%04x", card->ssqd.qdioac2);
	QETH_CARD_TEXT_(card, 2, "ac3:%04x", card->ssqd.qdioac3);
	QETH_CARD_TEXT_(card, 2, "icnt%d", card->ssqd.icnt);
	अगर (!((card->ssqd.qfmt != QDIO_IQDIO_QFMT) ||
	    ((card->ssqd.qdioac1 & CHSC_AC1_INITIATE_INPUTQ) == 0) ||
	    ((card->ssqd.qdioac3 & CHSC_AC3_FORMAT2_CQ_AVAILABLE) == 0))) अणु
		dev_info(&card->gdev->dev,
			"Completion Queueing supported\n");
	पूर्ण अन्यथा अणु
		card->options.cq = QETH_CQ_NOTAVAILABLE;
	पूर्ण

out_offline:
	अगर (ddev_offline == 1)
		qeth_stop_channel(channel);
out:
	वापस;
पूर्ण

अटल व्योम qeth_पढ़ो_ccw_conf_data(काष्ठा qeth_card *card)
अणु
	काष्ठा qeth_card_info *info = &card->info;
	काष्ठा ccw_device *cdev = CARD_DDEV(card);
	काष्ठा ccw_dev_id dev_id;

	QETH_CARD_TEXT(card, 2, "ccwconfd");
	ccw_device_get_id(cdev, &dev_id);

	info->ddev_devno = dev_id.devno;
	info->ids_valid = !ccw_device_get_cssid(cdev, &info->cssid) &&
			  !ccw_device_get_iid(cdev, &info->iid) &&
			  !ccw_device_get_chid(cdev, 0, &info->chid);
	info->ssid = dev_id.ssid;

	dev_info(&card->gdev->dev, "CHID: %x CHPID: %x\n",
		 info->chid, info->chpid);

	QETH_CARD_TEXT_(card, 3, "devn%x", info->ddev_devno);
	QETH_CARD_TEXT_(card, 3, "cssid:%x", info->cssid);
	QETH_CARD_TEXT_(card, 3, "iid:%x", info->iid);
	QETH_CARD_TEXT_(card, 3, "ssid:%x", info->ssid);
	QETH_CARD_TEXT_(card, 3, "chpid:%x", info->chpid);
	QETH_CARD_TEXT_(card, 3, "chid:%x", info->chid);
	QETH_CARD_TEXT_(card, 3, "idval%x", info->ids_valid);
पूर्ण

अटल पूर्णांक qeth_qdio_establish(काष्ठा qeth_card *card)
अणु
	काष्ठा qdio_buffer **out_sbal_ptrs[QETH_MAX_OUT_QUEUES];
	काष्ठा qdio_buffer **in_sbal_ptrs[QETH_MAX_IN_QUEUES];
	काष्ठा qeth_qib_parms *qib_parms = शून्य;
	काष्ठा qdio_initialize init_data;
	अचिन्हित पूर्णांक i;
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "qdioest");

	अगर (!IS_IQD(card) && !IS_VM_NIC(card)) अणु
		qib_parms = kzalloc(माप_field(काष्ठा qib, parm), GFP_KERNEL);
		अगर (!qib_parms)
			वापस -ENOMEM;

		qeth_fill_qib_parms(card, qib_parms);
	पूर्ण

	in_sbal_ptrs[0] = card->qdio.in_q->qdio_bufs;
	अगर (card->options.cq == QETH_CQ_ENABLED)
		in_sbal_ptrs[1] = card->qdio.c_q->qdio_bufs;

	क्रम (i = 0; i < card->qdio.no_out_queues; i++)
		out_sbal_ptrs[i] = card->qdio.out_qs[i]->qdio_bufs;

	स_रखो(&init_data, 0, माप(काष्ठा qdio_initialize));
	init_data.q_क्रमmat		 = IS_IQD(card) ? QDIO_IQDIO_QFMT :
							  QDIO_QETH_QFMT;
	init_data.qib_param_field_क्रमmat = 0;
	init_data.qib_param_field	 = (व्योम *)qib_parms;
	init_data.no_input_qs            = card->qdio.no_in_queues;
	init_data.no_output_qs           = card->qdio.no_out_queues;
	init_data.input_handler		 = qeth_qdio_input_handler;
	init_data.output_handler	 = qeth_qdio_output_handler;
	init_data.irq_poll		 = qeth_qdio_poll;
	init_data.पूर्णांक_parm               = (अचिन्हित दीर्घ) card;
	init_data.input_sbal_addr_array  = in_sbal_ptrs;
	init_data.output_sbal_addr_array = out_sbal_ptrs;
	init_data.scan_threshold	 = IS_IQD(card) ? 0 : 32;

	अगर (atomic_cmpxchg(&card->qdio.state, QETH_QDIO_ALLOCATED,
		QETH_QDIO_ESTABLISHED) == QETH_QDIO_ALLOCATED) अणु
		rc = qdio_allocate(CARD_DDEV(card), init_data.no_input_qs,
				   init_data.no_output_qs);
		अगर (rc) अणु
			atomic_set(&card->qdio.state, QETH_QDIO_ALLOCATED);
			जाओ out;
		पूर्ण
		rc = qdio_establish(CARD_DDEV(card), &init_data);
		अगर (rc) अणु
			atomic_set(&card->qdio.state, QETH_QDIO_ALLOCATED);
			qdio_मुक्त(CARD_DDEV(card));
		पूर्ण
	पूर्ण

	चयन (card->options.cq) अणु
	हाल QETH_CQ_ENABLED:
		dev_info(&card->gdev->dev, "Completion Queue support enabled");
		अवरोध;
	हाल QETH_CQ_DISABLED:
		dev_info(&card->gdev->dev, "Completion Queue support disabled");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

out:
	kमुक्त(qib_parms);
	वापस rc;
पूर्ण

अटल व्योम qeth_core_मुक्त_card(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 2, "freecrd");

	unरेजिस्टर_service_level(&card->qeth_service_level);
	debugfs_हटाओ_recursive(card->debugfs);
	qeth_put_cmd(card->पढ़ो_cmd);
	destroy_workqueue(card->event_wq);
	dev_set_drvdata(&card->gdev->dev, शून्य);
	kमुक्त(card);
पूर्ण

अटल व्योम qeth_trace_features(काष्ठा qeth_card *card)
अणु
	QETH_CARD_TEXT(card, 2, "features");
	QETH_CARD_HEX(card, 2, &card->options.ipa4, माप(card->options.ipa4));
	QETH_CARD_HEX(card, 2, &card->options.ipa6, माप(card->options.ipa6));
	QETH_CARD_HEX(card, 2, &card->options.adp, माप(card->options.adp));
	QETH_CARD_HEX(card, 2, &card->info.diagass_support,
		      माप(card->info.diagass_support));
पूर्ण

अटल काष्ठा ccw_device_id qeth_ids[] = अणु
	अणुCCW_DEVICE_DEVTYPE(0x1731, 0x01, 0x1732, 0x01),
					.driver_info = QETH_CARD_TYPE_OSDपूर्ण,
	अणुCCW_DEVICE_DEVTYPE(0x1731, 0x05, 0x1732, 0x05),
					.driver_info = QETH_CARD_TYPE_IQDपूर्ण,
#अगर_घोषित CONFIG_QETH_OSN
	अणुCCW_DEVICE_DEVTYPE(0x1731, 0x06, 0x1732, 0x06),
					.driver_info = QETH_CARD_TYPE_OSNपूर्ण,
#पूर्ण_अगर
	अणुCCW_DEVICE_DEVTYPE(0x1731, 0x02, 0x1732, 0x03),
					.driver_info = QETH_CARD_TYPE_OSMपूर्ण,
#अगर_घोषित CONFIG_QETH_OSX
	अणुCCW_DEVICE_DEVTYPE(0x1731, 0x02, 0x1732, 0x02),
					.driver_info = QETH_CARD_TYPE_OSXपूर्ण,
#पूर्ण_अगर
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(ccw, qeth_ids);

अटल काष्ठा ccw_driver qeth_ccw_driver = अणु
	.driver = अणु
		.owner = THIS_MODULE,
		.name = "qeth",
	पूर्ण,
	.ids = qeth_ids,
	.probe = ccwgroup_probe_ccwdev,
	.हटाओ = ccwgroup_हटाओ_ccwdev,
पूर्ण;

अटल पूर्णांक qeth_hardsetup_card(काष्ठा qeth_card *card, bool *carrier_ok)
अणु
	पूर्णांक retries = 3;
	पूर्णांक rc;

	QETH_CARD_TEXT(card, 2, "hrdsetup");
	atomic_set(&card->क्रमce_alloc_skb, 0);
	rc = qeth_update_from_chp_desc(card);
	अगर (rc)
		वापस rc;
retry:
	अगर (retries < 3)
		QETH_DBF_MESSAGE(2, "Retrying to do IDX activates on device %x.\n",
				 CARD_DEVID(card));
	rc = qeth_qdio_clear_card(card, !IS_IQD(card));
	qeth_stop_channel(&card->data);
	qeth_stop_channel(&card->ग_लिखो);
	qeth_stop_channel(&card->पढ़ो);
	qdio_मुक्त(CARD_DDEV(card));

	rc = qeth_start_channel(&card->पढ़ो);
	अगर (rc)
		जाओ retriable;
	rc = qeth_start_channel(&card->ग_लिखो);
	अगर (rc)
		जाओ retriable;
	rc = qeth_start_channel(&card->data);
	अगर (rc)
		जाओ retriable;
retriable:
	अगर (rc == -ERESTARTSYS) अणु
		QETH_CARD_TEXT(card, 2, "break1");
		वापस rc;
	पूर्ण अन्यथा अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
		अगर (--retries < 0)
			जाओ out;
		अन्यथा
			जाओ retry;
	पूर्ण

	qeth_determine_capabilities(card);
	qeth_पढ़ो_ccw_conf_data(card);
	qeth_idx_init(card);

	rc = qeth_idx_activate_पढ़ो_channel(card);
	अगर (rc == -EINTR) अणु
		QETH_CARD_TEXT(card, 2, "break2");
		वापस rc;
	पूर्ण अन्यथा अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "3err%d", rc);
		अगर (--retries < 0)
			जाओ out;
		अन्यथा
			जाओ retry;
	पूर्ण

	rc = qeth_idx_activate_ग_लिखो_channel(card);
	अगर (rc == -EINTR) अणु
		QETH_CARD_TEXT(card, 2, "break3");
		वापस rc;
	पूर्ण अन्यथा अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "4err%d", rc);
		अगर (--retries < 0)
			जाओ out;
		अन्यथा
			जाओ retry;
	पूर्ण
	card->पढ़ो_or_ग_लिखो_problem = 0;
	rc = qeth_mpc_initialize(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "5err%d", rc);
		जाओ out;
	पूर्ण

	rc = qeth_send_startlan(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "6err%d", rc);
		अगर (rc == -ENETDOWN) अणु
			dev_warn(&card->gdev->dev, "The LAN is offline\n");
			*carrier_ok = false;
		पूर्ण अन्यथा अणु
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		*carrier_ok = true;
	पूर्ण

	card->options.ipa4.supported = 0;
	card->options.ipa6.supported = 0;
	card->options.adp.supported = 0;
	card->options.sbp.supported_funcs = 0;
	card->info.diagass_support = 0;
	rc = qeth_query_ipassists(card, QETH_PROT_IPV4);
	अगर (rc == -ENOMEM)
		जाओ out;
	अगर (qeth_is_supported(card, IPA_IPV6)) अणु
		rc = qeth_query_ipassists(card, QETH_PROT_IPV6);
		अगर (rc == -ENOMEM)
			जाओ out;
	पूर्ण
	अगर (qeth_is_supported(card, IPA_SETADAPTERPARMS)) अणु
		rc = qeth_query_setadapterparms(card);
		अगर (rc < 0) अणु
			QETH_CARD_TEXT_(card, 2, "7err%d", rc);
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (qeth_adp_supported(card, IPA_SETADP_SET_DIAG_ASSIST)) अणु
		rc = qeth_query_setdiagass(card);
		अगर (rc)
			QETH_CARD_TEXT_(card, 2, "8err%d", rc);
	पूर्ण

	qeth_trace_features(card);

	अगर (!qeth_is_diagass_supported(card, QETH_DIAGS_CMD_TRAP) ||
	    (card->info.hwtrap && qeth_hw_trap(card, QETH_DIAGS_TRAP_ARM)))
		card->info.hwtrap = 0;

	अगर (card->options.isolation != ISOLATION_MODE_NONE) अणु
		rc = qeth_setadpparms_set_access_ctrl(card,
						      card->options.isolation);
		अगर (rc)
			जाओ out;
	पूर्ण

	qeth_init_link_info(card);

	rc = qeth_init_qdio_queues(card);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "9err%d", rc);
		जाओ out;
	पूर्ण

	वापस 0;
out:
	dev_warn(&card->gdev->dev, "The qeth device driver failed to recover "
		"an error on the device\n");
	QETH_DBF_MESSAGE(2, "Initialization for device %x failed in hardsetup! rc=%d\n",
			 CARD_DEVID(card), rc);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_set_online(काष्ठा qeth_card *card,
			   स्थिर काष्ठा qeth_discipline *disc)
अणु
	bool carrier_ok;
	पूर्णांक rc;

	mutex_lock(&card->conf_mutex);
	QETH_CARD_TEXT(card, 2, "setonlin");

	rc = qeth_hardsetup_card(card, &carrier_ok);
	अगर (rc) अणु
		QETH_CARD_TEXT_(card, 2, "2err%04x", rc);
		rc = -ENODEV;
		जाओ err_hardsetup;
	पूर्ण

	qeth_prपूर्णांक_status_message(card);

	अगर (card->dev->reg_state != NETREG_REGISTERED)
		/* no need क्रम locking / error handling at this early stage: */
		qeth_set_real_num_tx_queues(card, qeth_tx_actual_queues(card));

	rc = disc->set_online(card, carrier_ok);
	अगर (rc)
		जाओ err_online;

	/* let user_space know that device is online */
	kobject_uevent(&card->gdev->dev.kobj, KOBJ_CHANGE);

	mutex_unlock(&card->conf_mutex);
	वापस 0;

err_online:
err_hardsetup:
	qeth_qdio_clear_card(card, 0);
	qeth_clear_working_pool_list(card);
	qeth_flush_local_addrs(card);

	qeth_stop_channel(&card->data);
	qeth_stop_channel(&card->ग_लिखो);
	qeth_stop_channel(&card->पढ़ो);
	qdio_मुक्त(CARD_DDEV(card));

	mutex_unlock(&card->conf_mutex);
	वापस rc;
पूर्ण

पूर्णांक qeth_set_offline(काष्ठा qeth_card *card, स्थिर काष्ठा qeth_discipline *disc,
		     bool resetting)
अणु
	पूर्णांक rc, rc2, rc3;

	mutex_lock(&card->conf_mutex);
	QETH_CARD_TEXT(card, 3, "setoffl");

	अगर ((!resetting && card->info.hwtrap) || card->info.hwtrap == 2) अणु
		qeth_hw_trap(card, QETH_DIAGS_TRAP_DISARM);
		card->info.hwtrap = 1;
	पूर्ण

	/* cancel any stalled cmd that might block the rtnl: */
	qeth_clear_ipacmd_list(card);

	rtnl_lock();
	card->info.खोलो_when_online = card->dev->flags & IFF_UP;
	dev_बंद(card->dev);
	netअगर_device_detach(card->dev);
	netअगर_carrier_off(card->dev);
	rtnl_unlock();

	cancel_work_sync(&card->rx_mode_work);

	disc->set_offline(card);

	qeth_qdio_clear_card(card, 0);
	qeth_drain_output_queues(card);
	qeth_clear_working_pool_list(card);
	qeth_flush_local_addrs(card);
	card->info.promisc_mode = 0;

	rc  = qeth_stop_channel(&card->data);
	rc2 = qeth_stop_channel(&card->ग_लिखो);
	rc3 = qeth_stop_channel(&card->पढ़ो);
	अगर (!rc)
		rc = (rc2) ? rc2 : rc3;
	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "1err%d", rc);
	qdio_मुक्त(CARD_DDEV(card));

	/* let user_space know that device is offline */
	kobject_uevent(&card->gdev->dev.kobj, KOBJ_CHANGE);

	mutex_unlock(&card->conf_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_set_offline);

अटल पूर्णांक qeth_करो_reset(व्योम *data)
अणु
	स्थिर काष्ठा qeth_discipline *disc;
	काष्ठा qeth_card *card = data;
	पूर्णांक rc;

	/* Lock-मुक्त, other users will block until we are करोne. */
	disc = card->discipline;

	QETH_CARD_TEXT(card, 2, "recover1");
	अगर (!qeth_करो_run_thपढ़ो(card, QETH_RECOVER_THREAD))
		वापस 0;
	QETH_CARD_TEXT(card, 2, "recover2");
	dev_warn(&card->gdev->dev,
		 "A recovery process has been started for the device\n");

	qeth_set_offline(card, disc, true);
	rc = qeth_set_online(card, disc);
	अगर (!rc) अणु
		dev_info(&card->gdev->dev,
			 "Device successfully recovered!\n");
	पूर्ण अन्यथा अणु
		ccwgroup_set_offline(card->gdev);
		dev_warn(&card->gdev->dev,
			 "The qeth device driver failed to recover an error on the device\n");
	पूर्ण
	qeth_clear_thपढ़ो_start_bit(card, QETH_RECOVER_THREAD);
	qeth_clear_thपढ़ो_running_bit(card, QETH_RECOVER_THREAD);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_QETH_L3)
अटल व्योम qeth_l3_rebuild_skb(काष्ठा qeth_card *card, काष्ठा sk_buff *skb,
				काष्ठा qeth_hdr *hdr)
अणु
	काष्ठा af_iucv_trans_hdr *iucv = (काष्ठा af_iucv_trans_hdr *) skb->data;
	काष्ठा qeth_hdr_layer3 *l3_hdr = &hdr->hdr.l3;
	काष्ठा net_device *dev = skb->dev;

	अगर (IS_IQD(card) && iucv->magic == ETH_P_AF_IUCV) अणु
		dev_hard_header(skb, dev, ETH_P_AF_IUCV, dev->dev_addr,
				"FAKELL", skb->len);
		वापस;
	पूर्ण

	अगर (!(l3_hdr->flags & QETH_HDR_PASSTHRU)) अणु
		u16 prot = (l3_hdr->flags & QETH_HDR_IPV6) ? ETH_P_IPV6 :
							     ETH_P_IP;
		अचिन्हित अक्षर tg_addr[ETH_ALEN];

		skb_reset_network_header(skb);
		चयन (l3_hdr->flags & QETH_HDR_CAST_MASK) अणु
		हाल QETH_CAST_MULTICAST:
			अगर (prot == ETH_P_IP)
				ip_eth_mc_map(ip_hdr(skb)->daddr, tg_addr);
			अन्यथा
				ipv6_eth_mc_map(&ipv6_hdr(skb)->daddr, tg_addr);
			QETH_CARD_STAT_INC(card, rx_multicast);
			अवरोध;
		हाल QETH_CAST_BROADCAST:
			ether_addr_copy(tg_addr, dev->broadcast);
			QETH_CARD_STAT_INC(card, rx_multicast);
			अवरोध;
		शेष:
			अगर (card->options.snअगरfer)
				skb->pkt_type = PACKET_OTHERHOST;
			ether_addr_copy(tg_addr, dev->dev_addr);
		पूर्ण

		अगर (l3_hdr->ext_flags & QETH_HDR_EXT_SRC_MAC_ADDR)
			dev_hard_header(skb, dev, prot, tg_addr,
					&l3_hdr->next_hop.rx.src_mac, skb->len);
		अन्यथा
			dev_hard_header(skb, dev, prot, tg_addr, "FAKELL",
					skb->len);
	पूर्ण

	/* copy VLAN tag from hdr पूर्णांकo skb */
	अगर (!card->options.snअगरfer &&
	    (l3_hdr->ext_flags & (QETH_HDR_EXT_VLAN_FRAME |
				  QETH_HDR_EXT_INCLUDE_VLAN_TAG))) अणु
		u16 tag = (l3_hdr->ext_flags & QETH_HDR_EXT_VLAN_FRAME) ?
				l3_hdr->vlan_id :
				l3_hdr->next_hop.rx.vlan_id;

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tag);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल व्योम qeth_receive_skb(काष्ठा qeth_card *card, काष्ठा sk_buff *skb,
			     काष्ठा qeth_hdr *hdr, bool uses_frags)
अणु
	काष्ठा napi_काष्ठा *napi = &card->napi;
	bool is_cso;

	चयन (hdr->hdr.l2.id) अणु
	हाल QETH_HEADER_TYPE_OSN:
		skb_push(skb, माप(*hdr));
		skb_copy_to_linear_data(skb, hdr, माप(*hdr));
		QETH_CARD_STAT_ADD(card, rx_bytes, skb->len);
		QETH_CARD_STAT_INC(card, rx_packets);

		card->osn_info.data_cb(skb);
		वापस;
#अगर IS_ENABLED(CONFIG_QETH_L3)
	हाल QETH_HEADER_TYPE_LAYER3:
		qeth_l3_rebuild_skb(card, skb, hdr);
		is_cso = hdr->hdr.l3.ext_flags & QETH_HDR_EXT_CSUM_TRANSP_REQ;
		अवरोध;
#पूर्ण_अगर
	हाल QETH_HEADER_TYPE_LAYER2:
		is_cso = hdr->hdr.l2.flags[1] & QETH_HDR_EXT_CSUM_TRANSP_REQ;
		अवरोध;
	शेष:
		/* never happens */
		अगर (uses_frags)
			napi_मुक्त_frags(napi);
		अन्यथा
			dev_kमुक्त_skb_any(skb);
		वापस;
	पूर्ण

	अगर (is_cso && (card->dev->features & NETIF_F_RXCSUM)) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		QETH_CARD_STAT_INC(card, rx_skb_csum);
	पूर्ण अन्यथा अणु
		skb->ip_summed = CHECKSUM_NONE;
	पूर्ण

	QETH_CARD_STAT_ADD(card, rx_bytes, skb->len);
	QETH_CARD_STAT_INC(card, rx_packets);
	अगर (skb_is_nonlinear(skb)) अणु
		QETH_CARD_STAT_INC(card, rx_sg_skbs);
		QETH_CARD_STAT_ADD(card, rx_sg_frags,
				   skb_shinfo(skb)->nr_frags);
	पूर्ण

	अगर (uses_frags) अणु
		napi_gro_frags(napi);
	पूर्ण अन्यथा अणु
		skb->protocol = eth_type_trans(skb, skb->dev);
		napi_gro_receive(napi, skb);
	पूर्ण
पूर्ण

अटल व्योम qeth_create_skb_frag(काष्ठा sk_buff *skb, अक्षर *data, पूर्णांक data_len)
अणु
	काष्ठा page *page = virt_to_page(data);
	अचिन्हित पूर्णांक next_frag;

	next_frag = skb_shinfo(skb)->nr_frags;
	get_page(page);
	skb_add_rx_frag(skb, next_frag, page, offset_in_page(data), data_len,
			data_len);
पूर्ण

अटल अंतरभूत पूर्णांक qeth_is_last_sbale(काष्ठा qdio_buffer_element *sbale)
अणु
	वापस (sbale->eflags & SBAL_EFLAGS_LAST_ENTRY);
पूर्ण

अटल पूर्णांक qeth_extract_skb(काष्ठा qeth_card *card,
			    काष्ठा qeth_qdio_buffer *qethbuffer, u8 *element_no,
			    पूर्णांक *__offset)
अणु
	काष्ठा qeth_priv *priv = netdev_priv(card->dev);
	काष्ठा qdio_buffer *buffer = qethbuffer->buffer;
	काष्ठा napi_काष्ठा *napi = &card->napi;
	काष्ठा qdio_buffer_element *element;
	अचिन्हित पूर्णांक linear_len = 0;
	bool uses_frags = false;
	पूर्णांक offset = *__offset;
	bool use_rx_sg = false;
	अचिन्हित पूर्णांक headroom;
	काष्ठा qeth_hdr *hdr;
	काष्ठा sk_buff *skb;
	पूर्णांक skb_len = 0;

	element = &buffer->element[*element_no];

next_packet:
	/* qeth_hdr must not cross element boundaries */
	जबतक (element->length < offset + माप(काष्ठा qeth_hdr)) अणु
		अगर (qeth_is_last_sbale(element))
			वापस -ENODATA;
		element++;
		offset = 0;
	पूर्ण

	hdr = phys_to_virt(element->addr) + offset;
	offset += माप(*hdr);
	skb = शून्य;

	चयन (hdr->hdr.l2.id) अणु
	हाल QETH_HEADER_TYPE_LAYER2:
		skb_len = hdr->hdr.l2.pkt_length;
		linear_len = ETH_HLEN;
		headroom = 0;
		अवरोध;
	हाल QETH_HEADER_TYPE_LAYER3:
		skb_len = hdr->hdr.l3.length;
		अगर (!IS_LAYER3(card)) अणु
			QETH_CARD_STAT_INC(card, rx_dropped_notsupp);
			जाओ walk_packet;
		पूर्ण

		अगर (hdr->hdr.l3.flags & QETH_HDR_PASSTHRU) अणु
			linear_len = ETH_HLEN;
			headroom = 0;
			अवरोध;
		पूर्ण

		अगर (hdr->hdr.l3.flags & QETH_HDR_IPV6)
			linear_len = माप(काष्ठा ipv6hdr);
		अन्यथा
			linear_len = माप(काष्ठा iphdr);
		headroom = ETH_HLEN;
		अवरोध;
	हाल QETH_HEADER_TYPE_OSN:
		skb_len = hdr->hdr.osn.pdu_length;
		अगर (!IS_OSN(card)) अणु
			QETH_CARD_STAT_INC(card, rx_dropped_notsupp);
			जाओ walk_packet;
		पूर्ण

		linear_len = skb_len;
		headroom = माप(काष्ठा qeth_hdr);
		अवरोध;
	शेष:
		अगर (hdr->hdr.l2.id & QETH_HEADER_MASK_INVAL)
			QETH_CARD_STAT_INC(card, rx_frame_errors);
		अन्यथा
			QETH_CARD_STAT_INC(card, rx_dropped_notsupp);

		/* Can't determine packet length, drop the whole buffer. */
		वापस -EPROTONOSUPPORT;
	पूर्ण

	अगर (skb_len < linear_len) अणु
		QETH_CARD_STAT_INC(card, rx_dropped_runt);
		जाओ walk_packet;
	पूर्ण

	use_rx_sg = (card->options.cq == QETH_CQ_ENABLED) ||
		    (skb_len > READ_ONCE(priv->rx_copyअवरोध) &&
		     !atomic_पढ़ो(&card->क्रमce_alloc_skb) &&
		     !IS_OSN(card));

	अगर (use_rx_sg) अणु
		/* QETH_CQ_ENABLED only: */
		अगर (qethbuffer->rx_skb &&
		    skb_tailroom(qethbuffer->rx_skb) >= linear_len + headroom) अणु
			skb = qethbuffer->rx_skb;
			qethbuffer->rx_skb = शून्य;
			जाओ use_skb;
		पूर्ण

		skb = napi_get_frags(napi);
		अगर (!skb) अणु
			/* -ENOMEM, no poपूर्णांक in falling back further. */
			QETH_CARD_STAT_INC(card, rx_dropped_nomem);
			जाओ walk_packet;
		पूर्ण

		अगर (skb_tailroom(skb) >= linear_len + headroom) अणु
			uses_frags = true;
			जाओ use_skb;
		पूर्ण

		netdev_info_once(card->dev,
				 "Insufficient linear space in NAPI frags skb, need %u but have %u\n",
				 linear_len + headroom, skb_tailroom(skb));
		/* Shouldn't happen. Don't optimize, fall back to linear skb. */
	पूर्ण

	linear_len = skb_len;
	skb = napi_alloc_skb(napi, linear_len + headroom);
	अगर (!skb) अणु
		QETH_CARD_STAT_INC(card, rx_dropped_nomem);
		जाओ walk_packet;
	पूर्ण

use_skb:
	अगर (headroom)
		skb_reserve(skb, headroom);
walk_packet:
	जबतक (skb_len) अणु
		पूर्णांक data_len = min(skb_len, (पूर्णांक)(element->length - offset));
		अक्षर *data = phys_to_virt(element->addr) + offset;

		skb_len -= data_len;
		offset += data_len;

		/* Extract data from current element: */
		अगर (skb && data_len) अणु
			अगर (linear_len) अणु
				अचिन्हित पूर्णांक copy_len;

				copy_len = min_t(अचिन्हित पूर्णांक, linear_len,
						 data_len);

				skb_put_data(skb, data, copy_len);
				linear_len -= copy_len;
				data_len -= copy_len;
				data += copy_len;
			पूर्ण

			अगर (data_len)
				qeth_create_skb_frag(skb, data, data_len);
		पूर्ण

		/* Step क्रमward to next element: */
		अगर (skb_len) अणु
			अगर (qeth_is_last_sbale(element)) अणु
				QETH_CARD_TEXT(card, 4, "unexeob");
				QETH_CARD_HEX(card, 2, buffer, माप(व्योम *));
				अगर (skb) अणु
					अगर (uses_frags)
						napi_मुक्त_frags(napi);
					अन्यथा
						dev_kमुक्त_skb_any(skb);
					QETH_CARD_STAT_INC(card,
							   rx_length_errors);
				पूर्ण
				वापस -EMSGSIZE;
			पूर्ण
			element++;
			offset = 0;
		पूर्ण
	पूर्ण

	/* This packet was skipped, go get another one: */
	अगर (!skb)
		जाओ next_packet;

	*element_no = element - &buffer->element[0];
	*__offset = offset;

	qeth_receive_skb(card, skb, hdr, uses_frags);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक qeth_extract_skbs(काष्ठा qeth_card *card, पूर्णांक budget,
				      काष्ठा qeth_qdio_buffer *buf, bool *करोne)
अणु
	अचिन्हित पूर्णांक work_करोne = 0;

	जबतक (budget) अणु
		अगर (qeth_extract_skb(card, buf, &card->rx.buf_element,
				     &card->rx.e_offset)) अणु
			*करोne = true;
			अवरोध;
		पूर्ण

		work_करोne++;
		budget--;
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल अचिन्हित पूर्णांक qeth_rx_poll(काष्ठा qeth_card *card, पूर्णांक budget)
अणु
	काष्ठा qeth_rx *ctx = &card->rx;
	अचिन्हित पूर्णांक work_करोne = 0;

	जबतक (budget > 0) अणु
		काष्ठा qeth_qdio_buffer *buffer;
		अचिन्हित पूर्णांक skbs_करोne = 0;
		bool करोne = false;

		/* Fetch completed RX buffers: */
		अगर (!card->rx.b_count) अणु
			card->rx.qdio_err = 0;
			card->rx.b_count = qdio_get_next_buffers(
				card->data.ccwdev, 0, &card->rx.b_index,
				&card->rx.qdio_err);
			अगर (card->rx.b_count <= 0) अणु
				card->rx.b_count = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Process one completed RX buffer: */
		buffer = &card->qdio.in_q->bufs[card->rx.b_index];
		अगर (!(card->rx.qdio_err &&
		      qeth_check_qdio_errors(card, buffer->buffer,
					     card->rx.qdio_err, "qinerr")))
			skbs_करोne = qeth_extract_skbs(card, budget, buffer,
						      &करोne);
		अन्यथा
			करोne = true;

		work_करोne += skbs_करोne;
		budget -= skbs_करोne;

		अगर (करोne) अणु
			QETH_CARD_STAT_INC(card, rx_bufs);
			qeth_put_buffer_pool_entry(card, buffer->pool_entry);
			buffer->pool_entry = शून्य;
			card->rx.b_count--;
			ctx->bufs_refill++;
			ctx->bufs_refill -= qeth_rx_refill_queue(card,
								 ctx->bufs_refill);

			/* Step क्रमward to next buffer: */
			card->rx.b_index = QDIO_BUFNR(card->rx.b_index + 1);
			card->rx.buf_element = 0;
			card->rx.e_offset = 0;
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल व्योम qeth_cq_poll(काष्ठा qeth_card *card)
अणु
	अचिन्हित पूर्णांक work_करोne = 0;

	जबतक (work_करोne < QDIO_MAX_BUFFERS_PER_Q) अणु
		अचिन्हित पूर्णांक start, error;
		पूर्णांक completed;

		completed = qdio_inspect_queue(CARD_DDEV(card), 1, true, &start,
					       &error);
		अगर (completed <= 0)
			वापस;

		qeth_qdio_cq_handler(card, error, 1, start, completed);
		work_करोne += completed;
	पूर्ण
पूर्ण

पूर्णांक qeth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qeth_card *card = container_of(napi, काष्ठा qeth_card, napi);
	अचिन्हित पूर्णांक work_करोne;

	work_करोne = qeth_rx_poll(card, budget);

	अगर (card->options.cq == QETH_CQ_ENABLED)
		qeth_cq_poll(card);

	अगर (budget) अणु
		काष्ठा qeth_rx *ctx = &card->rx;

		/* Process any substantial refill backlog: */
		ctx->bufs_refill -= qeth_rx_refill_queue(card, ctx->bufs_refill);

		/* Exhausted the RX budget. Keep IRQ disabled, we get called again. */
		अगर (work_करोne >= budget)
			वापस work_करोne;
	पूर्ण

	अगर (napi_complete_करोne(napi, work_करोne) &&
	    qdio_start_irq(CARD_DDEV(card)))
		napi_schedule(napi);

	वापस work_करोne;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_poll);

अटल व्योम qeth_iqd_tx_complete(काष्ठा qeth_qdio_out_q *queue,
				 अचिन्हित पूर्णांक bidx, अचिन्हित पूर्णांक qdio_error,
				 पूर्णांक budget)
अणु
	काष्ठा qeth_qdio_out_buffer *buffer = queue->bufs[bidx];
	u8 sflags = buffer->buffer->element[15].sflags;
	काष्ठा qeth_card *card = queue->card;
	bool error = !!qdio_error;

	अगर (qdio_error == QDIO_ERROR_SLSB_PENDING) अणु
		काष्ठा qaob *aob = buffer->aob;

		अगर (!aob) अणु
			netdev_WARN_ONCE(card->dev,
					 "Pending TX buffer %#x without QAOB on TX queue %u\n",
					 bidx, queue->queue_no);
			qeth_schedule_recovery(card);
			वापस;
		पूर्ण

		QETH_CARD_TEXT_(card, 5, "pel%u", bidx);

		चयन (atomic_cmpxchg(&buffer->state,
				       QETH_QDIO_BUF_PRIMED,
				       QETH_QDIO_BUF_PENDING)) अणु
		हाल QETH_QDIO_BUF_PRIMED:
			/* We have initial ownership, no QAOB (yet): */
			qeth_notअगरy_skbs(queue, buffer, TX_NOTIFY_PENDING);

			/* Handle race with qeth_qdio_handle_aob(): */
			चयन (atomic_xchg(&buffer->state,
					    QETH_QDIO_BUF_NEED_QAOB)) अणु
			हाल QETH_QDIO_BUF_PENDING:
				/* No concurrent QAOB notअगरication. */

				/* Prepare the queue slot क्रम immediate re-use: */
				qeth_scrub_qdio_buffer(buffer->buffer, queue->max_elements);
				अगर (qeth_alloc_out_buf(queue, bidx,
						       GFP_ATOMIC)) अणु
					QETH_CARD_TEXT(card, 2, "outofbuf");
					qeth_schedule_recovery(card);
				पूर्ण

				list_add(&buffer->list_entry,
					 &queue->pending_bufs);
				/* Skip clearing the buffer: */
				वापस;
			हाल QETH_QDIO_BUF_QAOB_OK:
				qeth_notअगरy_skbs(queue, buffer,
						 TX_NOTIFY_DELAYED_OK);
				error = false;
				अवरोध;
			हाल QETH_QDIO_BUF_QAOB_ERROR:
				qeth_notअगरy_skbs(queue, buffer,
						 TX_NOTIFY_DELAYED_GENERALERROR);
				error = true;
				अवरोध;
			शेष:
				WARN_ON_ONCE(1);
			पूर्ण

			अवरोध;
		हाल QETH_QDIO_BUF_QAOB_OK:
			/* qeth_qdio_handle_aob() alपढ़ोy received a QAOB: */
			qeth_notअगरy_skbs(queue, buffer, TX_NOTIFY_OK);
			error = false;
			अवरोध;
		हाल QETH_QDIO_BUF_QAOB_ERROR:
			/* qeth_qdio_handle_aob() alपढ़ोy received a QAOB: */
			qeth_notअगरy_skbs(queue, buffer, TX_NOTIFY_GENERALERROR);
			error = true;
			अवरोध;
		शेष:
			WARN_ON_ONCE(1);
		पूर्ण

		स_रखो(aob, 0, माप(*aob));
	पूर्ण अन्यथा अगर (card->options.cq == QETH_CQ_ENABLED) अणु
		qeth_notअगरy_skbs(queue, buffer,
				 qeth_compute_cq_notअगरication(sflags, 0));
	पूर्ण

	qeth_clear_output_buffer(queue, buffer, error, budget);
पूर्ण

अटल पूर्णांक qeth_tx_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qeth_qdio_out_q *queue = qeth_napi_to_out_queue(napi);
	अचिन्हित पूर्णांक queue_no = queue->queue_no;
	काष्ठा qeth_card *card = queue->card;
	काष्ठा net_device *dev = card->dev;
	अचिन्हित पूर्णांक work_करोne = 0;
	काष्ठा netdev_queue *txq;

	txq = netdev_get_tx_queue(dev, qeth_iqd_translate_txq(dev, queue_no));

	जबतक (1) अणु
		अचिन्हित पूर्णांक start, error, i;
		अचिन्हित पूर्णांक packets = 0;
		अचिन्हित पूर्णांक bytes = 0;
		पूर्णांक completed;

		qeth_tx_complete_pending_bufs(card, queue, false, budget);

		अगर (qeth_out_queue_is_empty(queue)) अणु
			napi_complete(napi);
			वापस 0;
		पूर्ण

		/* Give the CPU a breather: */
		अगर (work_करोne >= QDIO_MAX_BUFFERS_PER_Q) अणु
			QETH_TXQ_STAT_INC(queue, completion_yield);
			अगर (napi_complete_करोne(napi, 0))
				napi_schedule(napi);
			वापस 0;
		पूर्ण

		completed = qdio_inspect_queue(CARD_DDEV(card), queue_no, false,
					       &start, &error);
		अगर (completed <= 0) अणु
			/* Ensure we see TX completion क्रम pending work: */
			अगर (napi_complete_करोne(napi, 0))
				qeth_tx_arm_समयr(queue, QETH_TX_TIMER_USECS);
			वापस 0;
		पूर्ण

		क्रम (i = start; i < start + completed; i++) अणु
			काष्ठा qeth_qdio_out_buffer *buffer;
			अचिन्हित पूर्णांक bidx = QDIO_BUFNR(i);

			buffer = queue->bufs[bidx];
			packets += buffer->frames;
			bytes += buffer->bytes;

			qeth_handle_send_error(card, buffer, error);
			qeth_iqd_tx_complete(queue, bidx, error, budget);
		पूर्ण

		netdev_tx_completed_queue(txq, packets, bytes);
		atomic_sub(completed, &queue->used_buffers);
		work_करोne += completed;

		/* xmit may have observed the full-condition, but not yet
		 * stopped the txq. In which हाल the code below won't trigger.
		 * So beक्रमe वापसing, xmit will re-check the txq's fill level
		 * and wake it up अगर needed.
		 */
		अगर (netअगर_tx_queue_stopped(txq) &&
		    !qeth_out_queue_is_full(queue))
			netअगर_tx_wake_queue(txq);
	पूर्ण
पूर्ण

अटल पूर्णांक qeth_setassparms_inspect_rc(काष्ठा qeth_ipa_cmd *cmd)
अणु
	अगर (!cmd->hdr.वापस_code)
		cmd->hdr.वापस_code = cmd->data.setassparms.hdr.वापस_code;
	वापस cmd->hdr.वापस_code;
पूर्ण

अटल पूर्णांक qeth_setassparms_get_caps_cb(काष्ठा qeth_card *card,
					काष्ठा qeth_reply *reply,
					अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_ipa_caps *caps = reply->param;

	अगर (qeth_setassparms_inspect_rc(cmd))
		वापस -EIO;

	caps->supported = cmd->data.setassparms.data.caps.supported;
	caps->enabled = cmd->data.setassparms.data.caps.enabled;
	वापस 0;
पूर्ण

पूर्णांक qeth_setassparms_cb(काष्ठा qeth_card *card,
			काष्ठा qeth_reply *reply, अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;

	QETH_CARD_TEXT(card, 4, "defadpcb");

	अगर (cmd->hdr.वापस_code)
		वापस -EIO;

	cmd->hdr.वापस_code = cmd->data.setassparms.hdr.वापस_code;
	अगर (cmd->hdr.prot_version == QETH_PROT_IPV4)
		card->options.ipa4.enabled = cmd->hdr.assists.enabled;
	अगर (cmd->hdr.prot_version == QETH_PROT_IPV6)
		card->options.ipa6.enabled = cmd->hdr.assists.enabled;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_setassparms_cb);

काष्ठा qeth_cmd_buffer *qeth_get_setassparms_cmd(काष्ठा qeth_card *card,
						 क्रमागत qeth_ipa_funcs ipa_func,
						 u16 cmd_code,
						 अचिन्हित पूर्णांक data_length,
						 क्रमागत qeth_prot_versions prot)
अणु
	काष्ठा qeth_ipacmd_setassparms *setassparms;
	काष्ठा qeth_ipacmd_setassparms_hdr *hdr;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT(card, 4, "getasscm");
	iob = qeth_ipa_alloc_cmd(card, IPA_CMD_SETASSPARMS, prot,
				 data_length +
				 दुरत्व(काष्ठा qeth_ipacmd_setassparms,
					  data));
	अगर (!iob)
		वापस शून्य;

	setassparms = &__ipa_cmd(iob)->data.setassparms;
	setassparms->assist_no = ipa_func;

	hdr = &setassparms->hdr;
	hdr->length = माप(*hdr) + data_length;
	hdr->command_code = cmd_code;
	वापस iob;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_get_setassparms_cmd);

पूर्णांक qeth_send_simple_setassparms_prot(काष्ठा qeth_card *card,
				      क्रमागत qeth_ipa_funcs ipa_func,
				      u16 cmd_code, u32 *data,
				      क्रमागत qeth_prot_versions prot)
अणु
	अचिन्हित पूर्णांक length = data ? SETASS_DATA_SIZखातापूर्ण(flags_32bit) : 0;
	काष्ठा qeth_cmd_buffer *iob;

	QETH_CARD_TEXT_(card, 4, "simassp%i", prot);
	iob = qeth_get_setassparms_cmd(card, ipa_func, cmd_code, length, prot);
	अगर (!iob)
		वापस -ENOMEM;

	अगर (data)
		__ipa_cmd(iob)->data.setassparms.data.flags_32bit = *data;
	वापस qeth_send_ipa_cmd(card, iob, qeth_setassparms_cb, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_send_simple_setassparms_prot);

अटल व्योम qeth_unरेजिस्टर_dbf_views(व्योम)
अणु
	पूर्णांक x;

	क्रम (x = 0; x < QETH_DBF_INFOS; x++) अणु
		debug_unरेजिस्टर(qeth_dbf[x].id);
		qeth_dbf[x].id = शून्य;
	पूर्ण
पूर्ण

व्योम qeth_dbf_दीर्घtext(debug_info_t *id, पूर्णांक level, अक्षर *fmt, ...)
अणु
	अक्षर dbf_txt_buf[32];
	बहु_सूची args;

	अगर (!debug_level_enabled(id, level))
		वापस;
	बहु_शुरू(args, fmt);
	vsnम_लिखो(dbf_txt_buf, माप(dbf_txt_buf), fmt, args);
	बहु_पूर्ण(args);
	debug_text_event(id, level, dbf_txt_buf);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_dbf_दीर्घtext);

अटल पूर्णांक qeth_रेजिस्टर_dbf_views(व्योम)
अणु
	पूर्णांक ret;
	पूर्णांक x;

	क्रम (x = 0; x < QETH_DBF_INFOS; x++) अणु
		/* रेजिस्टर the areas */
		qeth_dbf[x].id = debug_रेजिस्टर(qeth_dbf[x].name,
						qeth_dbf[x].pages,
						qeth_dbf[x].areas,
						qeth_dbf[x].len);
		अगर (qeth_dbf[x].id == शून्य) अणु
			qeth_unरेजिस्टर_dbf_views();
			वापस -ENOMEM;
		पूर्ण

		/* रेजिस्टर a view */
		ret = debug_रेजिस्टर_view(qeth_dbf[x].id, qeth_dbf[x].view);
		अगर (ret) अणु
			qeth_unरेजिस्टर_dbf_views();
			वापस ret;
		पूर्ण

		/* set a passing level */
		debug_set_level(qeth_dbf[x].id, qeth_dbf[x].level);
	पूर्ण

	वापस 0;
पूर्ण

अटल DEFINE_MUTEX(qeth_mod_mutex);	/* क्रम synchronized module loading */

पूर्णांक qeth_setup_discipline(काष्ठा qeth_card *card,
			  क्रमागत qeth_discipline_id discipline)
अणु
	पूर्णांक rc;

	mutex_lock(&qeth_mod_mutex);
	चयन (discipline) अणु
	हाल QETH_DISCIPLINE_LAYER3:
		card->discipline = try_then_request_module(
			symbol_get(qeth_l3_discipline), "qeth_l3");
		अवरोध;
	हाल QETH_DISCIPLINE_LAYER2:
		card->discipline = try_then_request_module(
			symbol_get(qeth_l2_discipline), "qeth_l2");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&qeth_mod_mutex);

	अगर (!card->discipline) अणु
		dev_err(&card->gdev->dev, "There is no kernel module to "
			"support discipline %d\n", discipline);
		वापस -EINVAL;
	पूर्ण

	rc = card->discipline->setup(card->gdev);
	अगर (rc) अणु
		अगर (discipline == QETH_DISCIPLINE_LAYER2)
			symbol_put(qeth_l2_discipline);
		अन्यथा
			symbol_put(qeth_l3_discipline);
		card->discipline = शून्य;

		वापस rc;
	पूर्ण

	card->options.layer = discipline;
	वापस 0;
पूर्ण

व्योम qeth_हटाओ_discipline(काष्ठा qeth_card *card)
अणु
	card->discipline->हटाओ(card->gdev);

	अगर (IS_LAYER2(card))
		symbol_put(qeth_l2_discipline);
	अन्यथा
		symbol_put(qeth_l3_discipline);
	card->options.layer = QETH_DISCIPLINE_UNDETERMINED;
	card->discipline = शून्य;
पूर्ण

स्थिर काष्ठा device_type qeth_generic_devtype = अणु
	.name = "qeth_generic",
पूर्ण;
EXPORT_SYMBOL_GPL(qeth_generic_devtype);

अटल स्थिर काष्ठा device_type qeth_osn_devtype = अणु
	.name = "qeth_osn",
पूर्ण;

#घोषणा DBF_NAME_LEN	20

काष्ठा qeth_dbf_entry अणु
	अक्षर dbf_name[DBF_NAME_LEN];
	debug_info_t *dbf_info;
	काष्ठा list_head dbf_list;
पूर्ण;

अटल LIST_HEAD(qeth_dbf_list);
अटल DEFINE_MUTEX(qeth_dbf_list_mutex);

अटल debug_info_t *qeth_get_dbf_entry(अक्षर *name)
अणु
	काष्ठा qeth_dbf_entry *entry;
	debug_info_t *rc = शून्य;

	mutex_lock(&qeth_dbf_list_mutex);
	list_क्रम_each_entry(entry, &qeth_dbf_list, dbf_list) अणु
		अगर (म_भेद(entry->dbf_name, name) == 0) अणु
			rc = entry->dbf_info;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&qeth_dbf_list_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_add_dbf_entry(काष्ठा qeth_card *card, अक्षर *name)
अणु
	काष्ठा qeth_dbf_entry *new_entry;

	card->debug = debug_रेजिस्टर(name, 2, 1, 8);
	अगर (!card->debug) अणु
		QETH_DBF_TEXT_(SETUP, 2, "%s", "qcdbf");
		जाओ err;
	पूर्ण
	अगर (debug_रेजिस्टर_view(card->debug, &debug_hex_ascii_view))
		जाओ err_dbg;
	new_entry = kzalloc(माप(काष्ठा qeth_dbf_entry), GFP_KERNEL);
	अगर (!new_entry)
		जाओ err_dbg;
	म_नकलन(new_entry->dbf_name, name, DBF_NAME_LEN);
	new_entry->dbf_info = card->debug;
	mutex_lock(&qeth_dbf_list_mutex);
	list_add(&new_entry->dbf_list, &qeth_dbf_list);
	mutex_unlock(&qeth_dbf_list_mutex);

	वापस 0;

err_dbg:
	debug_unरेजिस्टर(card->debug);
err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम qeth_clear_dbf_list(व्योम)
अणु
	काष्ठा qeth_dbf_entry *entry, *पंचांगp;

	mutex_lock(&qeth_dbf_list_mutex);
	list_क्रम_each_entry_safe(entry, पंचांगp, &qeth_dbf_list, dbf_list) अणु
		list_del(&entry->dbf_list);
		debug_unरेजिस्टर(entry->dbf_info);
		kमुक्त(entry);
	पूर्ण
	mutex_unlock(&qeth_dbf_list_mutex);
पूर्ण

अटल काष्ठा net_device *qeth_alloc_netdev(काष्ठा qeth_card *card)
अणु
	काष्ठा net_device *dev;
	काष्ठा qeth_priv *priv;

	चयन (card->info.type) अणु
	हाल QETH_CARD_TYPE_IQD:
		dev = alloc_netdev_mqs(माप(*priv), "hsi%d", NET_NAME_UNKNOWN,
				       ether_setup, QETH_MAX_OUT_QUEUES, 1);
		अवरोध;
	हाल QETH_CARD_TYPE_OSM:
		dev = alloc_etherdev(माप(*priv));
		अवरोध;
	हाल QETH_CARD_TYPE_OSN:
		dev = alloc_netdev(माप(*priv), "osn%d", NET_NAME_UNKNOWN,
				   ether_setup);
		अवरोध;
	शेष:
		dev = alloc_etherdev_mqs(माप(*priv), QETH_MAX_OUT_QUEUES, 1);
	पूर्ण

	अगर (!dev)
		वापस शून्य;

	priv = netdev_priv(dev);
	priv->rx_copyअवरोध = QETH_RX_COPYBREAK;
	priv->tx_wanted_queues = IS_IQD(card) ? QETH_IQD_MIN_TXQ : 1;

	dev->ml_priv = card;
	dev->watchकरोg_समयo = QETH_TX_TIMEOUT;
	dev->min_mtu = IS_OSN(card) ? 64 : 576;
	 /* initialized when device first goes online: */
	dev->max_mtu = 0;
	dev->mtu = 0;
	SET_NETDEV_DEV(dev, &card->gdev->dev);
	netअगर_carrier_off(dev);

	अगर (IS_OSN(card)) अणु
		dev->ethtool_ops = &qeth_osn_ethtool_ops;
	पूर्ण अन्यथा अणु
		dev->ethtool_ops = &qeth_ethtool_ops;
		dev->priv_flags &= ~IFF_TX_SKB_SHARING;
		dev->hw_features |= NETIF_F_SG;
		dev->vlan_features |= NETIF_F_SG;
		अगर (IS_IQD(card))
			dev->features |= NETIF_F_SG;
	पूर्ण

	वापस dev;
पूर्ण

काष्ठा net_device *qeth_clone_netdev(काष्ठा net_device *orig)
अणु
	काष्ठा net_device *clone = qeth_alloc_netdev(orig->ml_priv);

	अगर (!clone)
		वापस शून्य;

	clone->dev_port = orig->dev_port;
	वापस clone;
पूर्ण

अटल पूर्णांक qeth_core_probe_device(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card;
	काष्ठा device *dev;
	पूर्णांक rc;
	क्रमागत qeth_discipline_id enक्रमced_disc;
	अक्षर dbf_name[DBF_NAME_LEN];

	QETH_DBF_TEXT(SETUP, 2, "probedev");

	dev = &gdev->dev;
	अगर (!get_device(dev))
		वापस -ENODEV;

	QETH_DBF_TEXT_(SETUP, 2, "%s", dev_name(&gdev->dev));

	card = qeth_alloc_card(gdev);
	अगर (!card) अणु
		QETH_DBF_TEXT_(SETUP, 2, "1err%d", -ENOMEM);
		rc = -ENOMEM;
		जाओ err_dev;
	पूर्ण

	snम_लिखो(dbf_name, माप(dbf_name), "qeth_card_%s",
		dev_name(&gdev->dev));
	card->debug = qeth_get_dbf_entry(dbf_name);
	अगर (!card->debug) अणु
		rc = qeth_add_dbf_entry(card, dbf_name);
		अगर (rc)
			जाओ err_card;
	पूर्ण

	qeth_setup_card(card);
	card->dev = qeth_alloc_netdev(card);
	अगर (!card->dev) अणु
		rc = -ENOMEM;
		जाओ err_card;
	पूर्ण

	qeth_determine_capabilities(card);
	qeth_set_blkt_शेषs(card);

	card->qdio.no_out_queues = card->dev->num_tx_queues;
	rc = qeth_update_from_chp_desc(card);
	अगर (rc)
		जाओ err_chp_desc;

	अगर (IS_OSN(card))
		gdev->dev.groups = qeth_osn_dev_groups;
	अन्यथा
		gdev->dev.groups = qeth_dev_groups;

	enक्रमced_disc = qeth_enक्रमce_discipline(card);
	चयन (enक्रमced_disc) अणु
	हाल QETH_DISCIPLINE_UNDETERMINED:
		gdev->dev.type = &qeth_generic_devtype;
		अवरोध;
	शेष:
		card->info.layer_enक्रमced = true;
		/* It's so early that we don't need the discipline_mutex yet. */
		rc = qeth_setup_discipline(card, enक्रमced_disc);
		अगर (rc)
			जाओ err_setup_disc;

		gdev->dev.type = IS_OSN(card) ? &qeth_osn_devtype :
						card->discipline->devtype;
		अवरोध;
	पूर्ण

	वापस 0;

err_setup_disc:
err_chp_desc:
	मुक्त_netdev(card->dev);
err_card:
	qeth_core_मुक्त_card(card);
err_dev:
	put_device(dev);
	वापस rc;
पूर्ण

अटल व्योम qeth_core_हटाओ_device(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);

	QETH_CARD_TEXT(card, 2, "removedv");

	mutex_lock(&card->discipline_mutex);
	अगर (card->discipline)
		qeth_हटाओ_discipline(card);
	mutex_unlock(&card->discipline_mutex);

	qeth_मुक्त_qdio_queues(card);

	मुक्त_netdev(card->dev);
	qeth_core_मुक्त_card(card);
	put_device(&gdev->dev);
पूर्ण

अटल पूर्णांक qeth_core_set_online(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);
	पूर्णांक rc = 0;
	क्रमागत qeth_discipline_id def_discipline;

	mutex_lock(&card->discipline_mutex);
	अगर (!card->discipline) अणु
		def_discipline = IS_IQD(card) ? QETH_DISCIPLINE_LAYER3 :
						QETH_DISCIPLINE_LAYER2;
		rc = qeth_setup_discipline(card, def_discipline);
		अगर (rc)
			जाओ err;
	पूर्ण

	rc = qeth_set_online(card, card->discipline);

err:
	mutex_unlock(&card->discipline_mutex);
	वापस rc;
पूर्ण

अटल पूर्णांक qeth_core_set_offline(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);
	पूर्णांक rc;

	mutex_lock(&card->discipline_mutex);
	rc = qeth_set_offline(card, card->discipline, false);
	mutex_unlock(&card->discipline_mutex);

	वापस rc;
पूर्ण

अटल व्योम qeth_core_shutकरोwn(काष्ठा ccwgroup_device *gdev)
अणु
	काष्ठा qeth_card *card = dev_get_drvdata(&gdev->dev);

	qeth_set_allowed_thपढ़ोs(card, 0, 1);
	अगर ((gdev->state == CCWGROUP_ONLINE) && card->info.hwtrap)
		qeth_hw_trap(card, QETH_DIAGS_TRAP_DISARM);
	qeth_qdio_clear_card(card, 0);
	qeth_drain_output_queues(card);
	qdio_मुक्त(CARD_DDEV(card));
पूर्ण

अटल sमाप_प्रकार group_store(काष्ठा device_driver *ddrv, स्थिर अक्षर *buf,
			   माप_प्रकार count)
अणु
	पूर्णांक err;

	err = ccwgroup_create_dev(qeth_core_root_dev, to_ccwgroupdrv(ddrv), 3,
				  buf);

	वापस err ? err : count;
पूर्ण
अटल DRIVER_ATTR_WO(group);

अटल काष्ठा attribute *qeth_drv_attrs[] = अणु
	&driver_attr_group.attr,
	शून्य,
पूर्ण;
अटल काष्ठा attribute_group qeth_drv_attr_group = अणु
	.attrs = qeth_drv_attrs,
पूर्ण;
अटल स्थिर काष्ठा attribute_group *qeth_drv_attr_groups[] = अणु
	&qeth_drv_attr_group,
	शून्य,
पूर्ण;

अटल काष्ठा ccwgroup_driver qeth_core_ccwgroup_driver = अणु
	.driver = अणु
		.groups = qeth_drv_attr_groups,
		.owner = THIS_MODULE,
		.name = "qeth",
	पूर्ण,
	.ccw_driver = &qeth_ccw_driver,
	.setup = qeth_core_probe_device,
	.हटाओ = qeth_core_हटाओ_device,
	.set_online = qeth_core_set_online,
	.set_offline = qeth_core_set_offline,
	.shutकरोwn = qeth_core_shutकरोwn,
पूर्ण;

काष्ठा qeth_card *qeth_get_card_by_busid(अक्षर *bus_id)
अणु
	काष्ठा ccwgroup_device *gdev;
	काष्ठा qeth_card *card;

	gdev = get_ccwgroupdev_by_busid(&qeth_core_ccwgroup_driver, bus_id);
	अगर (!gdev)
		वापस शून्य;

	card = dev_get_drvdata(&gdev->dev);
	put_device(&gdev->dev);
	वापस card;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_get_card_by_busid);

पूर्णांक qeth_करो_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	काष्ठा mii_ioctl_data *mii_data;
	पूर्णांक rc = 0;

	चयन (cmd) अणु
	हाल SIOC_QETH_ADP_SET_SNMP_CONTROL:
		rc = qeth_snmp_command(card, rq->अगरr_अगरru.अगरru_data);
		अवरोध;
	हाल SIOC_QETH_GET_CARD_TYPE:
		अगर ((IS_OSD(card) || IS_OSM(card) || IS_OSX(card)) &&
		    !IS_VM_NIC(card))
			वापस 1;
		वापस 0;
	हाल SIOCGMIIPHY:
		mii_data = अगर_mii(rq);
		mii_data->phy_id = 0;
		अवरोध;
	हाल SIOCGMIIREG:
		mii_data = अगर_mii(rq);
		अगर (mii_data->phy_id != 0)
			rc = -EINVAL;
		अन्यथा
			mii_data->val_out = qeth_mdio_पढ़ो(dev,
				mii_data->phy_id, mii_data->reg_num);
		अवरोध;
	हाल SIOC_QETH_QUERY_OAT:
		rc = qeth_query_oat_command(card, rq->अगरr_अगरru.अगरru_data);
		अवरोध;
	शेष:
		अगर (card->discipline->करो_ioctl)
			rc = card->discipline->करो_ioctl(dev, rq, cmd);
		अन्यथा
			rc = -EOPNOTSUPP;
	पूर्ण
	अगर (rc)
		QETH_CARD_TEXT_(card, 2, "ioce%x", rc);
	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_करो_ioctl);

अटल पूर्णांक qeth_start_csum_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
			      अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	u32 *features = reply->param;

	अगर (qeth_setassparms_inspect_rc(cmd))
		वापस -EIO;

	*features = cmd->data.setassparms.data.flags_32bit;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_set_csum_off(काष्ठा qeth_card *card, क्रमागत qeth_ipa_funcs cstype,
			     क्रमागत qeth_prot_versions prot)
अणु
	वापस qeth_send_simple_setassparms_prot(card, cstype, IPA_CMD_ASS_STOP,
						 शून्य, prot);
पूर्ण

अटल पूर्णांक qeth_set_csum_on(काष्ठा qeth_card *card, क्रमागत qeth_ipa_funcs cstype,
			    क्रमागत qeth_prot_versions prot, u8 *lp2lp)
अणु
	u32 required_features = QETH_IPA_CHECKSUM_UDP | QETH_IPA_CHECKSUM_TCP;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_caps caps;
	u32 features;
	पूर्णांक rc;

	/* some L3 HW requires combined L3+L4 csum offload: */
	अगर (IS_LAYER3(card) && prot == QETH_PROT_IPV4 &&
	    cstype == IPA_OUTBOUND_CHECKSUM)
		required_features |= QETH_IPA_CHECKSUM_IP_HDR;

	iob = qeth_get_setassparms_cmd(card, cstype, IPA_CMD_ASS_START, 0,
				       prot);
	अगर (!iob)
		वापस -ENOMEM;

	rc = qeth_send_ipa_cmd(card, iob, qeth_start_csum_cb, &features);
	अगर (rc)
		वापस rc;

	अगर ((required_features & features) != required_features) अणु
		qeth_set_csum_off(card, cstype, prot);
		वापस -EOPNOTSUPP;
	पूर्ण

	iob = qeth_get_setassparms_cmd(card, cstype, IPA_CMD_ASS_ENABLE,
				       SETASS_DATA_SIZखातापूर्ण(flags_32bit),
				       prot);
	अगर (!iob) अणु
		qeth_set_csum_off(card, cstype, prot);
		वापस -ENOMEM;
	पूर्ण

	अगर (features & QETH_IPA_CHECKSUM_LP2LP)
		required_features |= QETH_IPA_CHECKSUM_LP2LP;
	__ipa_cmd(iob)->data.setassparms.data.flags_32bit = required_features;
	rc = qeth_send_ipa_cmd(card, iob, qeth_setassparms_get_caps_cb, &caps);
	अगर (rc) अणु
		qeth_set_csum_off(card, cstype, prot);
		वापस rc;
	पूर्ण

	अगर (!qeth_ipa_caps_supported(&caps, required_features) ||
	    !qeth_ipa_caps_enabled(&caps, required_features)) अणु
		qeth_set_csum_off(card, cstype, prot);
		वापस -EOPNOTSUPP;
	पूर्ण

	dev_info(&card->gdev->dev, "HW Checksumming (%sbound IPv%d) enabled\n",
		 cstype == IPA_INBOUND_CHECKSUM ? "in" : "out", prot);

	अगर (lp2lp)
		*lp2lp = qeth_ipa_caps_enabled(&caps, QETH_IPA_CHECKSUM_LP2LP);

	वापस 0;
पूर्ण

अटल पूर्णांक qeth_set_ipa_csum(काष्ठा qeth_card *card, bool on, पूर्णांक cstype,
			     क्रमागत qeth_prot_versions prot, u8 *lp2lp)
अणु
	वापस on ? qeth_set_csum_on(card, cstype, prot, lp2lp) :
		    qeth_set_csum_off(card, cstype, prot);
पूर्ण

अटल पूर्णांक qeth_start_tso_cb(काष्ठा qeth_card *card, काष्ठा qeth_reply *reply,
			     अचिन्हित दीर्घ data)
अणु
	काष्ठा qeth_ipa_cmd *cmd = (काष्ठा qeth_ipa_cmd *) data;
	काष्ठा qeth_tso_start_data *tso_data = reply->param;

	अगर (qeth_setassparms_inspect_rc(cmd))
		वापस -EIO;

	tso_data->mss = cmd->data.setassparms.data.tso.mss;
	tso_data->supported = cmd->data.setassparms.data.tso.supported;
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_set_tso_off(काष्ठा qeth_card *card,
			    क्रमागत qeth_prot_versions prot)
अणु
	वापस qeth_send_simple_setassparms_prot(card, IPA_OUTBOUND_TSO,
						 IPA_CMD_ASS_STOP, शून्य, prot);
पूर्ण

अटल पूर्णांक qeth_set_tso_on(काष्ठा qeth_card *card,
			   क्रमागत qeth_prot_versions prot)
अणु
	काष्ठा qeth_tso_start_data tso_data;
	काष्ठा qeth_cmd_buffer *iob;
	काष्ठा qeth_ipa_caps caps;
	पूर्णांक rc;

	iob = qeth_get_setassparms_cmd(card, IPA_OUTBOUND_TSO,
				       IPA_CMD_ASS_START, 0, prot);
	अगर (!iob)
		वापस -ENOMEM;

	rc = qeth_send_ipa_cmd(card, iob, qeth_start_tso_cb, &tso_data);
	अगर (rc)
		वापस rc;

	अगर (!tso_data.mss || !(tso_data.supported & QETH_IPA_LARGE_SEND_TCP)) अणु
		qeth_set_tso_off(card, prot);
		वापस -EOPNOTSUPP;
	पूर्ण

	iob = qeth_get_setassparms_cmd(card, IPA_OUTBOUND_TSO,
				       IPA_CMD_ASS_ENABLE,
				       SETASS_DATA_SIZखातापूर्ण(caps), prot);
	अगर (!iob) अणु
		qeth_set_tso_off(card, prot);
		वापस -ENOMEM;
	पूर्ण

	/* enable TSO capability */
	__ipa_cmd(iob)->data.setassparms.data.caps.enabled =
		QETH_IPA_LARGE_SEND_TCP;
	rc = qeth_send_ipa_cmd(card, iob, qeth_setassparms_get_caps_cb, &caps);
	अगर (rc) अणु
		qeth_set_tso_off(card, prot);
		वापस rc;
	पूर्ण

	अगर (!qeth_ipa_caps_supported(&caps, QETH_IPA_LARGE_SEND_TCP) ||
	    !qeth_ipa_caps_enabled(&caps, QETH_IPA_LARGE_SEND_TCP)) अणु
		qeth_set_tso_off(card, prot);
		वापस -EOPNOTSUPP;
	पूर्ण

	dev_info(&card->gdev->dev, "TSOv%u enabled (MSS: %u)\n", prot,
		 tso_data.mss);
	वापस 0;
पूर्ण

अटल पूर्णांक qeth_set_ipa_tso(काष्ठा qeth_card *card, bool on,
			    क्रमागत qeth_prot_versions prot)
अणु
	वापस on ? qeth_set_tso_on(card, prot) : qeth_set_tso_off(card, prot);
पूर्ण

अटल पूर्णांक qeth_set_ipa_rx_csum(काष्ठा qeth_card *card, bool on)
अणु
	पूर्णांक rc_ipv4 = (on) ? -EOPNOTSUPP : 0;
	पूर्णांक rc_ipv6;

	अगर (qeth_is_supported(card, IPA_INBOUND_CHECKSUM))
		rc_ipv4 = qeth_set_ipa_csum(card, on, IPA_INBOUND_CHECKSUM,
					    QETH_PROT_IPV4, शून्य);
	अगर (!qeth_is_supported6(card, IPA_INBOUND_CHECKSUM_V6))
		/* no/one Offload Assist available, so the rc is trivial */
		वापस rc_ipv4;

	rc_ipv6 = qeth_set_ipa_csum(card, on, IPA_INBOUND_CHECKSUM,
				    QETH_PROT_IPV6, शून्य);

	अगर (on)
		/* enable: success अगर any Assist is active */
		वापस (rc_ipv6) ? rc_ipv4 : 0;

	/* disable: failure अगर any Assist is still active */
	वापस (rc_ipv6) ? rc_ipv6 : rc_ipv4;
पूर्ण

/**
 * qeth_enable_hw_features() - (Re-)Enable HW functions क्रम device features
 * @dev:	a net_device
 */
व्योम qeth_enable_hw_features(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	netdev_features_t features;

	features = dev->features;
	/* क्रमce-off any feature that might need an IPA sequence.
	 * netdev_update_features() will restart them.
	 */
	dev->features &= ~dev->hw_features;
	/* toggle VLAN filter, so that VIDs are re-programmed: */
	अगर (IS_LAYER2(card) && IS_VM_NIC(card)) अणु
		dev->features &= ~NETIF_F_HW_VLAN_CTAG_FILTER;
		dev->wanted_features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	पूर्ण
	netdev_update_features(dev);
	अगर (features != dev->features)
		dev_warn(&card->gdev->dev,
			 "Device recovery failed to restore all offload features\n");
पूर्ण
EXPORT_SYMBOL_GPL(qeth_enable_hw_features);

अटल व्योम qeth_check_restricted_features(काष्ठा qeth_card *card,
					   netdev_features_t changed,
					   netdev_features_t actual)
अणु
	netdev_features_t ipv6_features = NETIF_F_TSO6;
	netdev_features_t ipv4_features = NETIF_F_TSO;

	अगर (!card->info.has_lp2lp_cso_v6)
		ipv6_features |= NETIF_F_IPV6_CSUM;
	अगर (!card->info.has_lp2lp_cso_v4)
		ipv4_features |= NETIF_F_IP_CSUM;

	अगर ((changed & ipv6_features) && !(actual & ipv6_features))
		qeth_flush_local_addrs6(card);
	अगर ((changed & ipv4_features) && !(actual & ipv4_features))
		qeth_flush_local_addrs4(card);
पूर्ण

पूर्णांक qeth_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	netdev_features_t changed = dev->features ^ features;
	पूर्णांक rc = 0;

	QETH_CARD_TEXT(card, 2, "setfeat");
	QETH_CARD_HEX(card, 2, &features, माप(features));

	अगर ((changed & NETIF_F_IP_CSUM)) अणु
		rc = qeth_set_ipa_csum(card, features & NETIF_F_IP_CSUM,
				       IPA_OUTBOUND_CHECKSUM, QETH_PROT_IPV4,
				       &card->info.has_lp2lp_cso_v4);
		अगर (rc)
			changed ^= NETIF_F_IP_CSUM;
	पूर्ण
	अगर (changed & NETIF_F_IPV6_CSUM) अणु
		rc = qeth_set_ipa_csum(card, features & NETIF_F_IPV6_CSUM,
				       IPA_OUTBOUND_CHECKSUM, QETH_PROT_IPV6,
				       &card->info.has_lp2lp_cso_v6);
		अगर (rc)
			changed ^= NETIF_F_IPV6_CSUM;
	पूर्ण
	अगर (changed & NETIF_F_RXCSUM) अणु
		rc = qeth_set_ipa_rx_csum(card, features & NETIF_F_RXCSUM);
		अगर (rc)
			changed ^= NETIF_F_RXCSUM;
	पूर्ण
	अगर (changed & NETIF_F_TSO) अणु
		rc = qeth_set_ipa_tso(card, features & NETIF_F_TSO,
				      QETH_PROT_IPV4);
		अगर (rc)
			changed ^= NETIF_F_TSO;
	पूर्ण
	अगर (changed & NETIF_F_TSO6) अणु
		rc = qeth_set_ipa_tso(card, features & NETIF_F_TSO6,
				      QETH_PROT_IPV6);
		अगर (rc)
			changed ^= NETIF_F_TSO6;
	पूर्ण

	qeth_check_restricted_features(card, dev->features ^ features,
				       dev->features ^ changed);

	/* everything changed successfully? */
	अगर ((dev->features ^ features) == changed)
		वापस 0;
	/* something went wrong. save changed features and वापस error */
	dev->features ^= changed;
	वापस -EIO;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_set_features);

netdev_features_t qeth_fix_features(काष्ठा net_device *dev,
				    netdev_features_t features)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	QETH_CARD_TEXT(card, 2, "fixfeat");
	अगर (!qeth_is_supported(card, IPA_OUTBOUND_CHECKSUM))
		features &= ~NETIF_F_IP_CSUM;
	अगर (!qeth_is_supported6(card, IPA_OUTBOUND_CHECKSUM_V6))
		features &= ~NETIF_F_IPV6_CSUM;
	अगर (!qeth_is_supported(card, IPA_INBOUND_CHECKSUM) &&
	    !qeth_is_supported6(card, IPA_INBOUND_CHECKSUM_V6))
		features &= ~NETIF_F_RXCSUM;
	अगर (!qeth_is_supported(card, IPA_OUTBOUND_TSO))
		features &= ~NETIF_F_TSO;
	अगर (!qeth_is_supported6(card, IPA_OUTBOUND_TSO))
		features &= ~NETIF_F_TSO6;

	QETH_CARD_HEX(card, 2, &features, माप(features));
	वापस features;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_fix_features);

netdev_features_t qeth_features_check(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      netdev_features_t features)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	/* Traffic with local next-hop is not eligible क्रम some offloads: */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL &&
	    READ_ONCE(card->options.isolation) != ISOLATION_MODE_FWD) अणु
		netdev_features_t restricted = 0;

		अगर (skb_is_gso(skb) && !netअगर_needs_gso(skb, features))
			restricted |= NETIF_F_ALL_TSO;

		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			अगर (!card->info.has_lp2lp_cso_v4)
				restricted |= NETIF_F_IP_CSUM;

			अगर (restricted && qeth_next_hop_is_local_v4(card, skb))
				features &= ~restricted;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			अगर (!card->info.has_lp2lp_cso_v6)
				restricted |= NETIF_F_IPV6_CSUM;

			अगर (restricted && qeth_next_hop_is_local_v6(card, skb))
				features &= ~restricted;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/* GSO segmentation builds skbs with
	 *	a (small) linear part क्रम the headers, and
	 *	page frags क्रम the data.
	 * Compared to a linear skb, the header-only part consumes an
	 * additional buffer element. This reduces buffer utilization, and
	 * hurts throughput. So compress small segments पूर्णांकo one element.
	 */
	अगर (netअगर_needs_gso(skb, features)) अणु
		/* match skb_segment(): */
		अचिन्हित पूर्णांक करोffset = skb->data - skb_mac_header(skb);
		अचिन्हित पूर्णांक hsize = skb_shinfo(skb)->gso_size;
		अचिन्हित पूर्णांक hroom = skb_headroom(skb);

		/* linearize only अगर resulting skb allocations are order-0: */
		अगर (SKB_DATA_ALIGN(hroom + करोffset + hsize) <= SKB_MAX_HEAD(0))
			features &= ~NETIF_F_SG;
	पूर्ण

	वापस vlan_features_check(skb, features);
पूर्ण
EXPORT_SYMBOL_GPL(qeth_features_check);

व्योम qeth_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;
	काष्ठा qeth_qdio_out_q *queue;
	अचिन्हित पूर्णांक i;

	QETH_CARD_TEXT(card, 5, "getstat");

	stats->rx_packets = card->stats.rx_packets;
	stats->rx_bytes = card->stats.rx_bytes;
	stats->rx_errors = card->stats.rx_length_errors +
			   card->stats.rx_frame_errors +
			   card->stats.rx_fअगरo_errors;
	stats->rx_dropped = card->stats.rx_dropped_nomem +
			    card->stats.rx_dropped_notsupp +
			    card->stats.rx_dropped_runt;
	stats->multicast = card->stats.rx_multicast;
	stats->rx_length_errors = card->stats.rx_length_errors;
	stats->rx_frame_errors = card->stats.rx_frame_errors;
	stats->rx_fअगरo_errors = card->stats.rx_fअगरo_errors;

	क्रम (i = 0; i < card->qdio.no_out_queues; i++) अणु
		queue = card->qdio.out_qs[i];

		stats->tx_packets += queue->stats.tx_packets;
		stats->tx_bytes += queue->stats.tx_bytes;
		stats->tx_errors += queue->stats.tx_errors;
		stats->tx_dropped += queue->stats.tx_dropped;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(qeth_get_stats64);

#घोषणा TC_IQD_UCAST   0
अटल व्योम qeth_iqd_set_prio_tc_map(काष्ठा net_device *dev,
				     अचिन्हित पूर्णांक ucast_txqs)
अणु
	अचिन्हित पूर्णांक prio;

	/* IQD requires mcast traffic to be placed on a dedicated queue, and
	 * qeth_iqd_select_queue() deals with this.
	 * For unicast traffic, we defer the queue selection to the stack.
	 * By installing a trivial prio map that spans over only the unicast
	 * queues, we can encourage the stack to spपढ़ो the ucast traffic evenly
	 * without selecting the mcast queue.
	 */

	/* One traffic class, spanning over all active ucast queues: */
	netdev_set_num_tc(dev, 1);
	netdev_set_tc_queue(dev, TC_IQD_UCAST, ucast_txqs,
			    QETH_IQD_MIN_UCAST_TXQ);

	/* Map all priorities to this traffic class: */
	क्रम (prio = 0; prio <= TC_BITMASK; prio++)
		netdev_set_prio_tc_map(dev, prio, TC_IQD_UCAST);
पूर्ण

पूर्णांक qeth_set_real_num_tx_queues(काष्ठा qeth_card *card, अचिन्हित पूर्णांक count)
अणु
	काष्ठा net_device *dev = card->dev;
	पूर्णांक rc;

	/* Per netअगर_setup_tc(), adjust the mapping first: */
	अगर (IS_IQD(card))
		qeth_iqd_set_prio_tc_map(dev, count - 1);

	rc = netअगर_set_real_num_tx_queues(dev, count);

	अगर (rc && IS_IQD(card))
		qeth_iqd_set_prio_tc_map(dev, dev->real_num_tx_queues - 1);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_set_real_num_tx_queues);

u16 qeth_iqd_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			  u8 cast_type, काष्ठा net_device *sb_dev)
अणु
	u16 txq;

	अगर (cast_type != RTN_UNICAST)
		वापस QETH_IQD_MCAST_TXQ;
	अगर (dev->real_num_tx_queues == QETH_IQD_MIN_TXQ)
		वापस QETH_IQD_MIN_UCAST_TXQ;

	txq = netdev_pick_tx(dev, skb, sb_dev);
	वापस (txq == QETH_IQD_MCAST_TXQ) ? QETH_IQD_MIN_UCAST_TXQ : txq;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_iqd_select_queue);

पूर्णांक qeth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	QETH_CARD_TEXT(card, 4, "qethopen");

	card->data.state = CH_STATE_UP;
	netअगर_tx_start_all_queues(dev);

	local_bh_disable();
	अगर (IS_IQD(card)) अणु
		काष्ठा qeth_qdio_out_q *queue;
		अचिन्हित पूर्णांक i;

		qeth_क्रम_each_output_queue(card, queue, i) अणु
			netअगर_tx_napi_add(dev, &queue->napi, qeth_tx_poll,
					  QETH_NAPI_WEIGHT);
			napi_enable(&queue->napi);
			napi_schedule(&queue->napi);
		पूर्ण
	पूर्ण

	napi_enable(&card->napi);
	napi_schedule(&card->napi);
	/* kick-start the NAPI softirq: */
	local_bh_enable();

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_खोलो);

पूर्णांक qeth_stop(काष्ठा net_device *dev)
अणु
	काष्ठा qeth_card *card = dev->ml_priv;

	QETH_CARD_TEXT(card, 4, "qethstop");

	napi_disable(&card->napi);
	cancel_delayed_work_sync(&card->buffer_reclaim_work);
	qdio_stop_irq(CARD_DDEV(card));

	अगर (IS_IQD(card)) अणु
		काष्ठा qeth_qdio_out_q *queue;
		अचिन्हित पूर्णांक i;

		/* Quiesce the NAPI instances: */
		qeth_क्रम_each_output_queue(card, queue, i)
			napi_disable(&queue->napi);

		/* Stop .nकरो_start_xmit, might still access queue->napi. */
		netअगर_tx_disable(dev);

		qeth_क्रम_each_output_queue(card, queue, i) अणु
			del_समयr_sync(&queue->समयr);
			/* Queues may get re-allocated, so हटाओ the NAPIs. */
			netअगर_napi_del(&queue->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_tx_disable(dev);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qeth_stop);

अटल पूर्णांक __init qeth_core_init(व्योम)
अणु
	पूर्णांक rc;

	pr_info("loading core functions\n");

	qeth_debugfs_root = debugfs_create_dir("qeth", शून्य);

	rc = qeth_रेजिस्टर_dbf_views();
	अगर (rc)
		जाओ dbf_err;
	qeth_core_root_dev = root_device_रेजिस्टर("qeth");
	rc = PTR_ERR_OR_ZERO(qeth_core_root_dev);
	अगर (rc)
		जाओ रेजिस्टर_err;
	qeth_core_header_cache =
		kmem_cache_create("qeth_hdr", QETH_HDR_CACHE_OBJ_SIZE,
				  roundup_घात_of_two(QETH_HDR_CACHE_OBJ_SIZE),
				  0, शून्य);
	अगर (!qeth_core_header_cache) अणु
		rc = -ENOMEM;
		जाओ slab_err;
	पूर्ण
	qeth_qdio_outbuf_cache = kmem_cache_create("qeth_buf",
			माप(काष्ठा qeth_qdio_out_buffer), 0, 0, शून्य);
	अगर (!qeth_qdio_outbuf_cache) अणु
		rc = -ENOMEM;
		जाओ cqslab_err;
	पूर्ण
	rc = ccw_driver_रेजिस्टर(&qeth_ccw_driver);
	अगर (rc)
		जाओ ccw_err;
	rc = ccwgroup_driver_रेजिस्टर(&qeth_core_ccwgroup_driver);
	अगर (rc)
		जाओ ccwgroup_err;

	वापस 0;

ccwgroup_err:
	ccw_driver_unरेजिस्टर(&qeth_ccw_driver);
ccw_err:
	kmem_cache_destroy(qeth_qdio_outbuf_cache);
cqslab_err:
	kmem_cache_destroy(qeth_core_header_cache);
slab_err:
	root_device_unरेजिस्टर(qeth_core_root_dev);
रेजिस्टर_err:
	qeth_unरेजिस्टर_dbf_views();
dbf_err:
	debugfs_हटाओ_recursive(qeth_debugfs_root);
	pr_err("Initializing the qeth device driver failed\n");
	वापस rc;
पूर्ण

अटल व्योम __निकास qeth_core_निकास(व्योम)
अणु
	qeth_clear_dbf_list();
	ccwgroup_driver_unरेजिस्टर(&qeth_core_ccwgroup_driver);
	ccw_driver_unरेजिस्टर(&qeth_ccw_driver);
	kmem_cache_destroy(qeth_qdio_outbuf_cache);
	kmem_cache_destroy(qeth_core_header_cache);
	root_device_unरेजिस्टर(qeth_core_root_dev);
	qeth_unरेजिस्टर_dbf_views();
	debugfs_हटाओ_recursive(qeth_debugfs_root);
	pr_info("core functions removed\n");
पूर्ण

module_init(qeth_core_init);
module_निकास(qeth_core_निकास);
MODULE_AUTHOR("Frank Blaschka <frank.blaschka@de.ibm.com>");
MODULE_DESCRIPTION("qeth core functions");
MODULE_LICENSE("GPL");
