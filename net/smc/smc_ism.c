<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Shared Memory Communications Direct over ISM devices (SMC-D)
 *
 * Functions क्रम ISM device.
 *
 * Copyright IBM Corp. 2018
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/page.h>

#समावेश "smc.h"
#समावेश "smc_core.h"
#समावेश "smc_ism.h"
#समावेश "smc_pnet.h"
#समावेश "smc_netlink.h"

काष्ठा smcd_dev_list smcd_dev_list = अणु
	.list = LIST_HEAD_INIT(smcd_dev_list.list),
	.mutex = __MUTEX_INITIALIZER(smcd_dev_list.mutex)
पूर्ण;

अटल bool smc_ism_v2_capable;

/* Test अगर an ISM communication is possible - same CPC */
पूर्णांक smc_ism_cantalk(u64 peer_gid, अचिन्हित लघु vlan_id, काष्ठा smcd_dev *smcd)
अणु
	वापस smcd->ops->query_remote_gid(smcd, peer_gid, vlan_id ? 1 : 0,
					   vlan_id);
पूर्ण

पूर्णांक smc_ism_ग_लिखो(काष्ठा smcd_dev *smcd, स्थिर काष्ठा smc_ism_position *pos,
		  व्योम *data, माप_प्रकार len)
अणु
	पूर्णांक rc;

	rc = smcd->ops->move_data(smcd, pos->token, pos->index, pos->संकेत,
				  pos->offset, data, len);

	वापस rc < 0 ? rc : 0;
पूर्ण

व्योम smc_ism_get_प्रणाली_eid(काष्ठा smcd_dev *smcd, u8 **eid)
अणु
	smcd->ops->get_प्रणाली_eid(smcd, eid);
पूर्ण

u16 smc_ism_get_chid(काष्ठा smcd_dev *smcd)
अणु
	वापस smcd->ops->get_chid(smcd);
पूर्ण

/* HW supports ISM V2 and thus System EID is defined */
bool smc_ism_is_v2_capable(व्योम)
अणु
	वापस smc_ism_v2_capable;
पूर्ण

/* Set a connection using this DMBE. */
व्योम smc_ism_set_conn(काष्ठा smc_connection *conn)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&conn->lgr->smcd->lock, flags);
	conn->lgr->smcd->conn[conn->rmb_desc->sba_idx] = conn;
	spin_unlock_irqrestore(&conn->lgr->smcd->lock, flags);
पूर्ण

/* Unset a connection using this DMBE. */
व्योम smc_ism_unset_conn(काष्ठा smc_connection *conn)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!conn->rmb_desc)
		वापस;

	spin_lock_irqsave(&conn->lgr->smcd->lock, flags);
	conn->lgr->smcd->conn[conn->rmb_desc->sba_idx] = शून्य;
	spin_unlock_irqrestore(&conn->lgr->smcd->lock, flags);
पूर्ण

/* Register a VLAN identअगरier with the ISM device. Use a reference count
 * and add a VLAN identअगरier only when the first DMB using this VLAN is
 * रेजिस्टरed.
 */
पूर्णांक smc_ism_get_vlan(काष्ठा smcd_dev *smcd, अचिन्हित लघु vlanid)
अणु
	काष्ठा smc_ism_vlanid *new_vlan, *vlan;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc = 0;

	अगर (!vlanid)			/* No valid vlan id */
		वापस -EINVAL;

	/* create new vlan entry, in हाल we need it */
	new_vlan = kzalloc(माप(*new_vlan), GFP_KERNEL);
	अगर (!new_vlan)
		वापस -ENOMEM;
	new_vlan->vlanid = vlanid;
	refcount_set(&new_vlan->refcnt, 1);

	/* अगर there is an existing entry, increase count and वापस */
	spin_lock_irqsave(&smcd->lock, flags);
	list_क्रम_each_entry(vlan, &smcd->vlan, list) अणु
		अगर (vlan->vlanid == vlanid) अणु
			refcount_inc(&vlan->refcnt);
			kमुक्त(new_vlan);
			जाओ out;
		पूर्ण
	पूर्ण

	/* no existing entry found.
	 * add new entry to device; might fail, e.g., अगर HW limit reached
	 */
	अगर (smcd->ops->add_vlan_id(smcd, vlanid)) अणु
		kमुक्त(new_vlan);
		rc = -EIO;
		जाओ out;
	पूर्ण
	list_add_tail(&new_vlan->list, &smcd->vlan);
out:
	spin_unlock_irqrestore(&smcd->lock, flags);
	वापस rc;
पूर्ण

/* Unरेजिस्टर a VLAN identअगरier with the ISM device. Use a reference count
 * and हटाओ a VLAN identअगरier only when the last DMB using this VLAN is
 * unरेजिस्टरed.
 */
पूर्णांक smc_ism_put_vlan(काष्ठा smcd_dev *smcd, अचिन्हित लघु vlanid)
अणु
	काष्ठा smc_ism_vlanid *vlan;
	अचिन्हित दीर्घ flags;
	bool found = false;
	पूर्णांक rc = 0;

	अगर (!vlanid)			/* No valid vlan id */
		वापस -EINVAL;

	spin_lock_irqsave(&smcd->lock, flags);
	list_क्रम_each_entry(vlan, &smcd->vlan, list) अणु
		अगर (vlan->vlanid == vlanid) अणु
			अगर (!refcount_dec_and_test(&vlan->refcnt))
				जाओ out;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		rc = -ENOENT;
		जाओ out;		/* VLAN id not in table */
	पूर्ण

	/* Found and the last reference just gone */
	अगर (smcd->ops->del_vlan_id(smcd, vlanid))
		rc = -EIO;
	list_del(&vlan->list);
	kमुक्त(vlan);
out:
	spin_unlock_irqrestore(&smcd->lock, flags);
	वापस rc;
पूर्ण

पूर्णांक smc_ism_unरेजिस्टर_dmb(काष्ठा smcd_dev *smcd, काष्ठा smc_buf_desc *dmb_desc)
अणु
	काष्ठा smcd_dmb dmb;
	पूर्णांक rc = 0;

	अगर (!dmb_desc->dma_addr)
		वापस rc;

	स_रखो(&dmb, 0, माप(dmb));
	dmb.dmb_tok = dmb_desc->token;
	dmb.sba_idx = dmb_desc->sba_idx;
	dmb.cpu_addr = dmb_desc->cpu_addr;
	dmb.dma_addr = dmb_desc->dma_addr;
	dmb.dmb_len = dmb_desc->len;
	rc = smcd->ops->unरेजिस्टर_dmb(smcd, &dmb);
	अगर (!rc || rc == ISM_ERROR) अणु
		dmb_desc->cpu_addr = शून्य;
		dmb_desc->dma_addr = 0;
	पूर्ण

	वापस rc;
पूर्ण

पूर्णांक smc_ism_रेजिस्टर_dmb(काष्ठा smc_link_group *lgr, पूर्णांक dmb_len,
			 काष्ठा smc_buf_desc *dmb_desc)
अणु
	काष्ठा smcd_dmb dmb;
	पूर्णांक rc;

	स_रखो(&dmb, 0, माप(dmb));
	dmb.dmb_len = dmb_len;
	dmb.sba_idx = dmb_desc->sba_idx;
	dmb.vlan_id = lgr->vlan_id;
	dmb.rgid = lgr->peer_gid;
	rc = lgr->smcd->ops->रेजिस्टर_dmb(lgr->smcd, &dmb);
	अगर (!rc) अणु
		dmb_desc->sba_idx = dmb.sba_idx;
		dmb_desc->token = dmb.dmb_tok;
		dmb_desc->cpu_addr = dmb.cpu_addr;
		dmb_desc->dma_addr = dmb.dma_addr;
		dmb_desc->len = dmb.dmb_len;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक smc_nl_handle_smcd_dev(काष्ठा smcd_dev *smcd,
				  काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	अक्षर smc_pnet[SMC_MAX_PNETID_LEN + 1];
	काष्ठा smc_pci_dev smc_pci_dev;
	काष्ठा nlattr *port_attrs;
	काष्ठा nlattr *attrs;
	पूर्णांक use_cnt = 0;
	व्योम *nlh;

	nlh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &smc_gen_nl_family, NLM_F_MULTI,
			  SMC_NETLINK_GET_DEV_SMCD);
	अगर (!nlh)
		जाओ errmsg;
	attrs = nla_nest_start(skb, SMC_GEN_DEV_SMCD);
	अगर (!attrs)
		जाओ errout;
	use_cnt = atomic_पढ़ो(&smcd->lgr_cnt);
	अगर (nla_put_u32(skb, SMC_NLA_DEV_USE_CNT, use_cnt))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_DEV_IS_CRIT, use_cnt > 0))
		जाओ errattr;
	स_रखो(&smc_pci_dev, 0, माप(smc_pci_dev));
	smc_set_pci_values(to_pci_dev(smcd->dev.parent), &smc_pci_dev);
	अगर (nla_put_u32(skb, SMC_NLA_DEV_PCI_FID, smc_pci_dev.pci_fid))
		जाओ errattr;
	अगर (nla_put_u16(skb, SMC_NLA_DEV_PCI_CHID, smc_pci_dev.pci_pchid))
		जाओ errattr;
	अगर (nla_put_u16(skb, SMC_NLA_DEV_PCI_VENDOR, smc_pci_dev.pci_venकरोr))
		जाओ errattr;
	अगर (nla_put_u16(skb, SMC_NLA_DEV_PCI_DEVICE, smc_pci_dev.pci_device))
		जाओ errattr;
	अगर (nla_put_string(skb, SMC_NLA_DEV_PCI_ID, smc_pci_dev.pci_id))
		जाओ errattr;

	port_attrs = nla_nest_start(skb, SMC_NLA_DEV_PORT);
	अगर (!port_attrs)
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_DEV_PORT_PNET_USR, smcd->pnetid_by_user))
		जाओ errportattr;
	स_नकल(smc_pnet, smcd->pnetid, SMC_MAX_PNETID_LEN);
	smc_pnet[SMC_MAX_PNETID_LEN] = 0;
	अगर (nla_put_string(skb, SMC_NLA_DEV_PORT_PNETID, smc_pnet))
		जाओ errportattr;

	nla_nest_end(skb, port_attrs);
	nla_nest_end(skb, attrs);
	genlmsg_end(skb, nlh);
	वापस 0;

errportattr:
	nla_nest_cancel(skb, port_attrs);
errattr:
	nla_nest_cancel(skb, attrs);
errout:
	nlmsg_cancel(skb, nlh);
errmsg:
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम smc_nl_prep_smcd_dev(काष्ठा smcd_dev_list *dev_list,
				 काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा smc_nl_dmp_ctx *cb_ctx = smc_nl_dmp_ctx(cb);
	पूर्णांक snum = cb_ctx->pos[0];
	काष्ठा smcd_dev *smcd;
	पूर्णांक num = 0;

	mutex_lock(&dev_list->mutex);
	list_क्रम_each_entry(smcd, &dev_list->list, list) अणु
		अगर (num < snum)
			जाओ next;
		अगर (smc_nl_handle_smcd_dev(smcd, skb, cb))
			जाओ errout;
next:
		num++;
	पूर्ण
errout:
	mutex_unlock(&dev_list->mutex);
	cb_ctx->pos[0] = num;
पूर्ण

पूर्णांक smcd_nl_get_device(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	smc_nl_prep_smcd_dev(&smcd_dev_list, skb, cb);
	वापस skb->len;
पूर्ण

काष्ठा smc_ism_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा smcd_dev *smcd;
	काष्ठा smcd_event event;
पूर्ण;

#घोषणा ISM_EVENT_REQUEST		0x0001
#घोषणा ISM_EVENT_RESPONSE		0x0002
#घोषणा ISM_EVENT_REQUEST_IR		0x00000001
#घोषणा ISM_EVENT_CODE_SHUTDOWN		0x80
#घोषणा ISM_EVENT_CODE_TESTLINK		0x83

जोड़ smcd_sw_event_info अणु
	u64	info;
	काष्ठा अणु
		u8		uid[SMC_LGR_ID_SIZE];
		अचिन्हित लघु	vlan_id;
		u16		code;
	पूर्ण;
पूर्ण;

अटल व्योम smcd_handle_sw_event(काष्ठा smc_ism_event_work *wrk)
अणु
	जोड़ smcd_sw_event_info ev_info;

	ev_info.info = wrk->event.info;
	चयन (wrk->event.code) अणु
	हाल ISM_EVENT_CODE_SHUTDOWN:	/* Peer shut करोwn DMBs */
		smc_smcd_terminate(wrk->smcd, wrk->event.tok, ev_info.vlan_id);
		अवरोध;
	हाल ISM_EVENT_CODE_TESTLINK:	/* Activity समयr */
		अगर (ev_info.code == ISM_EVENT_REQUEST) अणु
			ev_info.code = ISM_EVENT_RESPONSE;
			wrk->smcd->ops->संकेत_event(wrk->smcd,
						     wrk->event.tok,
						     ISM_EVENT_REQUEST_IR,
						     ISM_EVENT_CODE_TESTLINK,
						     ev_info.info);
			पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक smc_ism_संकेत_shutकरोwn(काष्ठा smc_link_group *lgr)
अणु
	पूर्णांक rc;
	जोड़ smcd_sw_event_info ev_info;

	अगर (lgr->peer_shutकरोwn)
		वापस 0;

	स_नकल(ev_info.uid, lgr->id, SMC_LGR_ID_SIZE);
	ev_info.vlan_id = lgr->vlan_id;
	ev_info.code = ISM_EVENT_REQUEST;
	rc = lgr->smcd->ops->संकेत_event(lgr->smcd, lgr->peer_gid,
					  ISM_EVENT_REQUEST_IR,
					  ISM_EVENT_CODE_SHUTDOWN,
					  ev_info.info);
	वापस rc;
पूर्ण

/* worker क्रम SMC-D events */
अटल व्योम smc_ism_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_ism_event_work *wrk =
		container_of(work, काष्ठा smc_ism_event_work, work);

	चयन (wrk->event.type) अणु
	हाल ISM_EVENT_GID:	/* GID event, token is peer GID */
		smc_smcd_terminate(wrk->smcd, wrk->event.tok, VLAN_VID_MASK);
		अवरोध;
	हाल ISM_EVENT_DMB:
		अवरोध;
	हाल ISM_EVENT_SWR:	/* Software defined event */
		smcd_handle_sw_event(wrk);
		अवरोध;
	पूर्ण
	kमुक्त(wrk);
पूर्ण

अटल व्योम smcd_release(काष्ठा device *dev)
अणु
	काष्ठा smcd_dev *smcd = container_of(dev, काष्ठा smcd_dev, dev);

	kमुक्त(smcd->conn);
	kमुक्त(smcd);
पूर्ण

काष्ठा smcd_dev *smcd_alloc_dev(काष्ठा device *parent, स्थिर अक्षर *name,
				स्थिर काष्ठा smcd_ops *ops, पूर्णांक max_dmbs)
अणु
	काष्ठा smcd_dev *smcd;

	smcd = kzalloc(माप(*smcd), GFP_KERNEL);
	अगर (!smcd)
		वापस शून्य;
	smcd->conn = kसुस्मृति(max_dmbs, माप(काष्ठा smc_connection *),
			     GFP_KERNEL);
	अगर (!smcd->conn) अणु
		kमुक्त(smcd);
		वापस शून्य;
	पूर्ण

	smcd->event_wq = alloc_ordered_workqueue("ism_evt_wq-%s)",
						 WQ_MEM_RECLAIM, name);
	अगर (!smcd->event_wq) अणु
		kमुक्त(smcd->conn);
		kमुक्त(smcd);
		वापस शून्य;
	पूर्ण

	smcd->dev.parent = parent;
	smcd->dev.release = smcd_release;
	device_initialize(&smcd->dev);
	dev_set_name(&smcd->dev, name);
	smcd->ops = ops;
	अगर (smc_pnetid_by_dev_port(parent, 0, smcd->pnetid))
		smc_pnetid_by_table_smcd(smcd);

	spin_lock_init(&smcd->lock);
	spin_lock_init(&smcd->lgr_lock);
	INIT_LIST_HEAD(&smcd->vlan);
	INIT_LIST_HEAD(&smcd->lgr_list);
	init_रुकोqueue_head(&smcd->lgrs_deleted);
	वापस smcd;
पूर्ण
EXPORT_SYMBOL_GPL(smcd_alloc_dev);

पूर्णांक smcd_रेजिस्टर_dev(काष्ठा smcd_dev *smcd)
अणु
	पूर्णांक rc;

	mutex_lock(&smcd_dev_list.mutex);
	अगर (list_empty(&smcd_dev_list.list)) अणु
		u8 *प्रणाली_eid = शून्य;

		smc_ism_get_प्रणाली_eid(smcd, &प्रणाली_eid);
		अगर (प्रणाली_eid[24] != '0' || system_eid[28] != '0')
			smc_ism_v2_capable = true;
	पूर्ण
	/* sort list: devices without pnetid beक्रमe devices with pnetid */
	अगर (smcd->pnetid[0])
		list_add_tail(&smcd->list, &smcd_dev_list.list);
	अन्यथा
		list_add(&smcd->list, &smcd_dev_list.list);
	mutex_unlock(&smcd_dev_list.mutex);

	pr_warn_ratelimited("smc: adding smcd device %s with pnetid %.16s%s\n",
			    dev_name(&smcd->dev), smcd->pnetid,
			    smcd->pnetid_by_user ? " (user defined)" : "");

	rc = device_add(&smcd->dev);
	अगर (rc) अणु
		mutex_lock(&smcd_dev_list.mutex);
		list_del(&smcd->list);
		mutex_unlock(&smcd_dev_list.mutex);
	पूर्ण

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(smcd_रेजिस्टर_dev);

व्योम smcd_unरेजिस्टर_dev(काष्ठा smcd_dev *smcd)
अणु
	pr_warn_ratelimited("smc: removing smcd device %s\n",
			    dev_name(&smcd->dev));
	mutex_lock(&smcd_dev_list.mutex);
	list_del_init(&smcd->list);
	mutex_unlock(&smcd_dev_list.mutex);
	smcd->going_away = 1;
	smc_smcd_terminate_all(smcd);
	flush_workqueue(smcd->event_wq);
	destroy_workqueue(smcd->event_wq);

	device_del(&smcd->dev);
पूर्ण
EXPORT_SYMBOL_GPL(smcd_unरेजिस्टर_dev);

व्योम smcd_मुक्त_dev(काष्ठा smcd_dev *smcd)
अणु
	put_device(&smcd->dev);
पूर्ण
EXPORT_SYMBOL_GPL(smcd_मुक्त_dev);

/* SMCD Device event handler. Called from ISM device पूर्णांकerrupt handler.
 * Parameters are smcd device poपूर्णांकer,
 * - event->type (0 --> DMB, 1 --> GID),
 * - event->code (event code),
 * - event->tok (either DMB token when event type 0, or GID when event type 1)
 * - event->समय (समय of day)
 * - event->info (debug info).
 *
 * Context:
 * - Function called in IRQ context from ISM device driver event handler.
 */
व्योम smcd_handle_event(काष्ठा smcd_dev *smcd, काष्ठा smcd_event *event)
अणु
	काष्ठा smc_ism_event_work *wrk;

	अगर (smcd->going_away)
		वापस;
	/* copy event to event work queue, and let it be handled there */
	wrk = kदो_स्मृति(माप(*wrk), GFP_ATOMIC);
	अगर (!wrk)
		वापस;
	INIT_WORK(&wrk->work, smc_ism_event_work);
	wrk->smcd = smcd;
	wrk->event = *event;
	queue_work(smcd->event_wq, &wrk->work);
पूर्ण
EXPORT_SYMBOL_GPL(smcd_handle_event);

/* SMCD Device पूर्णांकerrupt handler. Called from ISM device पूर्णांकerrupt handler.
 * Parameters are smcd device poपूर्णांकer and DMB number. Find the connection and
 * schedule the tasklet क्रम this connection.
 *
 * Context:
 * - Function called in IRQ context from ISM device driver IRQ handler.
 */
व्योम smcd_handle_irq(काष्ठा smcd_dev *smcd, अचिन्हित पूर्णांक dmbno)
अणु
	काष्ठा smc_connection *conn = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&smcd->lock, flags);
	conn = smcd->conn[dmbno];
	अगर (conn && !conn->समाप्तed)
		tasklet_schedule(&conn->rx_tsklet);
	spin_unlock_irqrestore(&smcd->lock, flags);
पूर्ण
EXPORT_SYMBOL_GPL(smcd_handle_irq);

व्योम __init smc_ism_init(व्योम)
अणु
	smc_ism_v2_capable = false;
पूर्ण
