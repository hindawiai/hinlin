<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 *  IB infraकाष्ठाure:
 *  Establish SMC-R as an Infiniband Client to be notअगरied about added and
 *  हटाओd IB devices of type RDMA.
 *  Determine device and port अक्षरacteristics क्रम these IB devices.
 *
 *  Copyright IBM Corp. 2016
 *
 *  Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#समावेश <linux/अक्रमom.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/रुको.h>
#समावेश <linux/mutex.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_cache.h>

#समावेश "smc_pnet.h"
#समावेश "smc_ib.h"
#समावेश "smc_core.h"
#समावेश "smc_wr.h"
#समावेश "smc.h"
#समावेश "smc_netlink.h"

#घोषणा SMC_MAX_CQE 32766	/* max. # of completion queue elements */

#घोषणा SMC_QP_MIN_RNR_TIMER		5
#घोषणा SMC_QP_TIMEOUT			15 /* 4096 * 2 ** समयout usec */
#घोषणा SMC_QP_RETRY_CNT			7 /* 7: infinite */
#घोषणा SMC_QP_RNR_RETRY			7 /* 7: infinite */

काष्ठा smc_ib_devices smc_ib_devices = अणु	/* smc-रेजिस्टरed ib devices */
	.mutex = __MUTEX_INITIALIZER(smc_ib_devices.mutex),
	.list = LIST_HEAD_INIT(smc_ib_devices.list),
पूर्ण;

u8 local_प्रणालीid[SMC_SYSTEMID_LEN];		/* unique प्रणाली identअगरier */

अटल पूर्णांक smc_ib_modअगरy_qp_init(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_qp_attr qp_attr;

	स_रखो(&qp_attr, 0, माप(qp_attr));
	qp_attr.qp_state = IB_QPS_INIT;
	qp_attr.pkey_index = 0;
	qp_attr.port_num = lnk->ibport;
	qp_attr.qp_access_flags = IB_ACCESS_LOCAL_WRITE
				| IB_ACCESS_REMOTE_WRITE;
	वापस ib_modअगरy_qp(lnk->roce_qp, &qp_attr,
			    IB_QP_STATE | IB_QP_PKEY_INDEX |
			    IB_QP_ACCESS_FLAGS | IB_QP_PORT);
पूर्ण

अटल पूर्णांक smc_ib_modअगरy_qp_rtr(काष्ठा smc_link *lnk)
अणु
	क्रमागत ib_qp_attr_mask qp_attr_mask =
		IB_QP_STATE | IB_QP_AV | IB_QP_PATH_MTU | IB_QP_DEST_QPN |
		IB_QP_RQ_PSN | IB_QP_MAX_DEST_RD_ATOMIC | IB_QP_MIN_RNR_TIMER;
	काष्ठा ib_qp_attr qp_attr;

	स_रखो(&qp_attr, 0, माप(qp_attr));
	qp_attr.qp_state = IB_QPS_RTR;
	qp_attr.path_mtu = min(lnk->path_mtu, lnk->peer_mtu);
	qp_attr.ah_attr.type = RDMA_AH_ATTR_TYPE_ROCE;
	rdma_ah_set_port_num(&qp_attr.ah_attr, lnk->ibport);
	rdma_ah_set_grh(&qp_attr.ah_attr, शून्य, 0, lnk->sgid_index, 1, 0);
	rdma_ah_set_dgid_raw(&qp_attr.ah_attr, lnk->peer_gid);
	स_नकल(&qp_attr.ah_attr.roce.dmac, lnk->peer_mac,
	       माप(lnk->peer_mac));
	qp_attr.dest_qp_num = lnk->peer_qpn;
	qp_attr.rq_psn = lnk->peer_psn; /* starting receive packet seq # */
	qp_attr.max_dest_rd_atomic = 1; /* max # of resources क्रम incoming
					 * requests
					 */
	qp_attr.min_rnr_समयr = SMC_QP_MIN_RNR_TIMER;

	वापस ib_modअगरy_qp(lnk->roce_qp, &qp_attr, qp_attr_mask);
पूर्ण

पूर्णांक smc_ib_modअगरy_qp_rts(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_qp_attr qp_attr;

	स_रखो(&qp_attr, 0, माप(qp_attr));
	qp_attr.qp_state = IB_QPS_RTS;
	qp_attr.समयout = SMC_QP_TIMEOUT;	/* local ack समयout */
	qp_attr.retry_cnt = SMC_QP_RETRY_CNT;	/* retry count */
	qp_attr.rnr_retry = SMC_QP_RNR_RETRY;	/* RNR retries, 7=infinite */
	qp_attr.sq_psn = lnk->psn_initial;	/* starting send packet seq # */
	qp_attr.max_rd_atomic = 1;	/* # of outstanding RDMA पढ़ोs and
					 * atomic ops allowed
					 */
	वापस ib_modअगरy_qp(lnk->roce_qp, &qp_attr,
			    IB_QP_STATE | IB_QP_TIMEOUT | IB_QP_RETRY_CNT |
			    IB_QP_SQ_PSN | IB_QP_RNR_RETRY |
			    IB_QP_MAX_QP_RD_ATOMIC);
पूर्ण

पूर्णांक smc_ib_modअगरy_qp_reset(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_qp_attr qp_attr;

	स_रखो(&qp_attr, 0, माप(qp_attr));
	qp_attr.qp_state = IB_QPS_RESET;
	वापस ib_modअगरy_qp(lnk->roce_qp, &qp_attr, IB_QP_STATE);
पूर्ण

पूर्णांक smc_ib_पढ़ोy_link(काष्ठा smc_link *lnk)
अणु
	काष्ठा smc_link_group *lgr = smc_get_lgr(lnk);
	पूर्णांक rc = 0;

	rc = smc_ib_modअगरy_qp_init(lnk);
	अगर (rc)
		जाओ out;

	rc = smc_ib_modअगरy_qp_rtr(lnk);
	अगर (rc)
		जाओ out;
	smc_wr_remember_qp_attr(lnk);
	rc = ib_req_notअगरy_cq(lnk->smcibdev->roce_cq_recv,
			      IB_CQ_SOLICITED_MASK);
	अगर (rc)
		जाओ out;
	rc = smc_wr_rx_post_init(lnk);
	अगर (rc)
		जाओ out;
	smc_wr_remember_qp_attr(lnk);

	अगर (lgr->role == SMC_SERV) अणु
		rc = smc_ib_modअगरy_qp_rts(lnk);
		अगर (rc)
			जाओ out;
		smc_wr_remember_qp_attr(lnk);
	पूर्ण
out:
	वापस rc;
पूर्ण

अटल पूर्णांक smc_ib_fill_mac(काष्ठा smc_ib_device *smcibdev, u8 ibport)
अणु
	स्थिर काष्ठा ib_gid_attr *attr;
	पूर्णांक rc;

	attr = rdma_get_gid_attr(smcibdev->ibdev, ibport, 0);
	अगर (IS_ERR(attr))
		वापस -ENODEV;

	rc = rdma_पढ़ो_gid_l2_fields(attr, शून्य, smcibdev->mac[ibport - 1]);
	rdma_put_gid_attr(attr);
	वापस rc;
पूर्ण

/* Create an identअगरier unique क्रम this instance of SMC-R.
 * The MAC-address of the first active रेजिस्टरed IB device
 * plus a अक्रमom 2-byte number is used to create this identअगरier.
 * This name is delivered to the peer during connection initialization.
 */
अटल अंतरभूत व्योम smc_ib_define_local_प्रणालीid(काष्ठा smc_ib_device *smcibdev,
						u8 ibport)
अणु
	स_नकल(&local_प्रणालीid[2], &smcibdev->mac[ibport - 1],
	       माप(smcibdev->mac[ibport - 1]));
पूर्ण

bool smc_ib_is_valid_local_प्रणालीid(व्योम)
अणु
	वापस !is_zero_ether_addr(&local_प्रणालीid[2]);
पूर्ण

अटल व्योम smc_ib_init_local_प्रणालीid(व्योम)
अणु
	get_अक्रमom_bytes(&local_प्रणालीid[0], 2);
पूर्ण

bool smc_ib_port_active(काष्ठा smc_ib_device *smcibdev, u8 ibport)
अणु
	वापस smcibdev->pattr[ibport - 1].state == IB_PORT_ACTIVE;
पूर्ण

/* determine the gid क्रम an ib-device port and vlan id */
पूर्णांक smc_ib_determine_gid(काष्ठा smc_ib_device *smcibdev, u8 ibport,
			 अचिन्हित लघु vlan_id, u8 gid[], u8 *sgid_index)
अणु
	स्थिर काष्ठा ib_gid_attr *attr;
	स्थिर काष्ठा net_device *ndev;
	पूर्णांक i;

	क्रम (i = 0; i < smcibdev->pattr[ibport - 1].gid_tbl_len; i++) अणु
		attr = rdma_get_gid_attr(smcibdev->ibdev, ibport, i);
		अगर (IS_ERR(attr))
			जारी;

		rcu_पढ़ो_lock();
		ndev = rdma_पढ़ो_gid_attr_ndev_rcu(attr);
		अगर (!IS_ERR(ndev) &&
		    ((!vlan_id && !is_vlan_dev(ndev)) ||
		     (vlan_id && is_vlan_dev(ndev) &&
		      vlan_dev_vlan_id(ndev) == vlan_id)) &&
		    attr->gid_type == IB_GID_TYPE_ROCE) अणु
			rcu_पढ़ो_unlock();
			अगर (gid)
				स_नकल(gid, &attr->gid, SMC_GID_SIZE);
			अगर (sgid_index)
				*sgid_index = attr->index;
			rdma_put_gid_attr(attr);
			वापस 0;
		पूर्ण
		rcu_पढ़ो_unlock();
		rdma_put_gid_attr(attr);
	पूर्ण
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक smc_ib_remember_port_attr(काष्ठा smc_ib_device *smcibdev, u8 ibport)
अणु
	पूर्णांक rc;

	स_रखो(&smcibdev->pattr[ibport - 1], 0,
	       माप(smcibdev->pattr[ibport - 1]));
	rc = ib_query_port(smcibdev->ibdev, ibport,
			   &smcibdev->pattr[ibport - 1]);
	अगर (rc)
		जाओ out;
	/* the SMC protocol requires specअगरication of the RoCE MAC address */
	rc = smc_ib_fill_mac(smcibdev, ibport);
	अगर (rc)
		जाओ out;
	अगर (!smc_ib_is_valid_local_प्रणालीid() &&
	    smc_ib_port_active(smcibdev, ibport))
		/* create unique प्रणाली identअगरier */
		smc_ib_define_local_प्रणालीid(smcibdev, ibport);
out:
	वापस rc;
पूर्ण

/* process context wrapper क्रम might_sleep smc_ib_remember_port_attr */
अटल व्योम smc_ib_port_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा smc_ib_device *smcibdev = container_of(
		work, काष्ठा smc_ib_device, port_event_work);
	u8 port_idx;

	क्रम_each_set_bit(port_idx, &smcibdev->port_event_mask, SMC_MAX_PORTS) अणु
		smc_ib_remember_port_attr(smcibdev, port_idx + 1);
		clear_bit(port_idx, &smcibdev->port_event_mask);
		अगर (!smc_ib_port_active(smcibdev, port_idx + 1)) अणु
			set_bit(port_idx, smcibdev->ports_going_away);
			smcr_port_err(smcibdev, port_idx + 1);
		पूर्ण अन्यथा अणु
			clear_bit(port_idx, smcibdev->ports_going_away);
			smcr_port_add(smcibdev, port_idx + 1);
		पूर्ण
	पूर्ण
पूर्ण

/* can be called in IRQ context */
अटल व्योम smc_ib_global_event_handler(काष्ठा ib_event_handler *handler,
					काष्ठा ib_event *ibevent)
अणु
	काष्ठा smc_ib_device *smcibdev;
	bool schedule = false;
	u8 port_idx;

	smcibdev = container_of(handler, काष्ठा smc_ib_device, event_handler);

	चयन (ibevent->event) अणु
	हाल IB_EVENT_DEVICE_FATAL:
		/* terminate all ports on device */
		क्रम (port_idx = 0; port_idx < SMC_MAX_PORTS; port_idx++) अणु
			set_bit(port_idx, &smcibdev->port_event_mask);
			अगर (!test_and_set_bit(port_idx,
					      smcibdev->ports_going_away))
				schedule = true;
		पूर्ण
		अगर (schedule)
			schedule_work(&smcibdev->port_event_work);
		अवरोध;
	हाल IB_EVENT_PORT_ACTIVE:
		port_idx = ibevent->element.port_num - 1;
		अगर (port_idx >= SMC_MAX_PORTS)
			अवरोध;
		set_bit(port_idx, &smcibdev->port_event_mask);
		अगर (test_and_clear_bit(port_idx, smcibdev->ports_going_away))
			schedule_work(&smcibdev->port_event_work);
		अवरोध;
	हाल IB_EVENT_PORT_ERR:
		port_idx = ibevent->element.port_num - 1;
		अगर (port_idx >= SMC_MAX_PORTS)
			अवरोध;
		set_bit(port_idx, &smcibdev->port_event_mask);
		अगर (!test_and_set_bit(port_idx, smcibdev->ports_going_away))
			schedule_work(&smcibdev->port_event_work);
		अवरोध;
	हाल IB_EVENT_GID_CHANGE:
		port_idx = ibevent->element.port_num - 1;
		अगर (port_idx >= SMC_MAX_PORTS)
			अवरोध;
		set_bit(port_idx, &smcibdev->port_event_mask);
		schedule_work(&smcibdev->port_event_work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम smc_ib_dealloc_protection_करोमुख्य(काष्ठा smc_link *lnk)
अणु
	अगर (lnk->roce_pd)
		ib_dealloc_pd(lnk->roce_pd);
	lnk->roce_pd = शून्य;
पूर्ण

पूर्णांक smc_ib_create_protection_करोमुख्य(काष्ठा smc_link *lnk)
अणु
	पूर्णांक rc;

	lnk->roce_pd = ib_alloc_pd(lnk->smcibdev->ibdev, 0);
	rc = PTR_ERR_OR_ZERO(lnk->roce_pd);
	अगर (IS_ERR(lnk->roce_pd))
		lnk->roce_pd = शून्य;
	वापस rc;
पूर्ण

अटल bool smcr_diag_is_dev_critical(काष्ठा smc_lgr_list *smc_lgr,
				      काष्ठा smc_ib_device *smcibdev)
अणु
	काष्ठा smc_link_group *lgr;
	bool rc = false;
	पूर्णांक i;

	spin_lock_bh(&smc_lgr->lock);
	list_क्रम_each_entry(lgr, &smc_lgr->list, list) अणु
		अगर (lgr->is_smcd)
			जारी;
		क्रम (i = 0; i < SMC_LINKS_PER_LGR_MAX; i++) अणु
			अगर (lgr->lnk[i].state == SMC_LNK_UNUSED ||
			    lgr->lnk[i].smcibdev != smcibdev)
				जारी;
			अगर (lgr->type == SMC_LGR_SINGLE ||
			    lgr->type == SMC_LGR_ASYMMETRIC_LOCAL) अणु
				rc = true;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण
out:
	spin_unlock_bh(&smc_lgr->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक smc_nl_handle_dev_port(काष्ठा sk_buff *skb,
				  काष्ठा ib_device *ibdev,
				  काष्ठा smc_ib_device *smcibdev,
				  पूर्णांक port)
अणु
	अक्षर smc_pnet[SMC_MAX_PNETID_LEN + 1];
	काष्ठा nlattr *port_attrs;
	अचिन्हित अक्षर port_state;
	पूर्णांक lnk_count = 0;

	port_attrs = nla_nest_start(skb, SMC_NLA_DEV_PORT + port);
	अगर (!port_attrs)
		जाओ errout;

	अगर (nla_put_u8(skb, SMC_NLA_DEV_PORT_PNET_USR,
		       smcibdev->pnetid_by_user[port]))
		जाओ errattr;
	स_नकल(smc_pnet, &smcibdev->pnetid[port], SMC_MAX_PNETID_LEN);
	smc_pnet[SMC_MAX_PNETID_LEN] = 0;
	अगर (nla_put_string(skb, SMC_NLA_DEV_PORT_PNETID, smc_pnet))
		जाओ errattr;
	अगर (nla_put_u32(skb, SMC_NLA_DEV_PORT_NETDEV,
			smcibdev->ndev_अगरidx[port]))
		जाओ errattr;
	अगर (nla_put_u8(skb, SMC_NLA_DEV_PORT_VALID, 1))
		जाओ errattr;
	port_state = smc_ib_port_active(smcibdev, port + 1);
	अगर (nla_put_u8(skb, SMC_NLA_DEV_PORT_STATE, port_state))
		जाओ errattr;
	lnk_count = atomic_पढ़ो(&smcibdev->lnk_cnt_by_port[port]);
	अगर (nla_put_u32(skb, SMC_NLA_DEV_PORT_LNK_CNT, lnk_count))
		जाओ errattr;
	nla_nest_end(skb, port_attrs);
	वापस 0;
errattr:
	nla_nest_cancel(skb, port_attrs);
errout:
	वापस -EMSGSIZE;
पूर्ण

अटल bool smc_nl_handle_pci_values(स्थिर काष्ठा smc_pci_dev *smc_pci_dev,
				     काष्ठा sk_buff *skb)
अणु
	अगर (nla_put_u32(skb, SMC_NLA_DEV_PCI_FID, smc_pci_dev->pci_fid))
		वापस false;
	अगर (nla_put_u16(skb, SMC_NLA_DEV_PCI_CHID, smc_pci_dev->pci_pchid))
		वापस false;
	अगर (nla_put_u16(skb, SMC_NLA_DEV_PCI_VENDOR, smc_pci_dev->pci_venकरोr))
		वापस false;
	अगर (nla_put_u16(skb, SMC_NLA_DEV_PCI_DEVICE, smc_pci_dev->pci_device))
		वापस false;
	अगर (nla_put_string(skb, SMC_NLA_DEV_PCI_ID, smc_pci_dev->pci_id))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक smc_nl_handle_smcr_dev(काष्ठा smc_ib_device *smcibdev,
				  काष्ठा sk_buff *skb,
				  काष्ठा netlink_callback *cb)
अणु
	अक्षर smc_ibname[IB_DEVICE_NAME_MAX];
	काष्ठा smc_pci_dev smc_pci_dev;
	काष्ठा pci_dev *pci_dev;
	अचिन्हित अक्षर is_crit;
	काष्ठा nlattr *attrs;
	व्योम *nlh;
	पूर्णांक i;

	nlh = genlmsg_put(skb, NETLINK_CB(cb->skb).portid, cb->nlh->nlmsg_seq,
			  &smc_gen_nl_family, NLM_F_MULTI,
			  SMC_NETLINK_GET_DEV_SMCR);
	अगर (!nlh)
		जाओ errmsg;
	attrs = nla_nest_start(skb, SMC_GEN_DEV_SMCR);
	अगर (!attrs)
		जाओ errout;
	is_crit = smcr_diag_is_dev_critical(&smc_lgr_list, smcibdev);
	अगर (nla_put_u8(skb, SMC_NLA_DEV_IS_CRIT, is_crit))
		जाओ errattr;
	अगर (smcibdev->ibdev->dev.parent) अणु
		स_रखो(&smc_pci_dev, 0, माप(smc_pci_dev));
		pci_dev = to_pci_dev(smcibdev->ibdev->dev.parent);
		smc_set_pci_values(pci_dev, &smc_pci_dev);
		अगर (!smc_nl_handle_pci_values(&smc_pci_dev, skb))
			जाओ errattr;
	पूर्ण
	snम_लिखो(smc_ibname, माप(smc_ibname), "%s", smcibdev->ibdev->name);
	अगर (nla_put_string(skb, SMC_NLA_DEV_IB_NAME, smc_ibname))
		जाओ errattr;
	क्रम (i = 1; i <= SMC_MAX_PORTS; i++) अणु
		अगर (!rdma_is_port_valid(smcibdev->ibdev, i))
			जारी;
		अगर (smc_nl_handle_dev_port(skb, smcibdev->ibdev,
					   smcibdev, i - 1))
			जाओ errattr;
	पूर्ण

	nla_nest_end(skb, attrs);
	genlmsg_end(skb, nlh);
	वापस 0;

errattr:
	nla_nest_cancel(skb, attrs);
errout:
	genlmsg_cancel(skb, nlh);
errmsg:
	वापस -EMSGSIZE;
पूर्ण

अटल व्योम smc_nl_prep_smcr_dev(काष्ठा smc_ib_devices *dev_list,
				 काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा smc_nl_dmp_ctx *cb_ctx = smc_nl_dmp_ctx(cb);
	काष्ठा smc_ib_device *smcibdev;
	पूर्णांक snum = cb_ctx->pos[0];
	पूर्णांक num = 0;

	mutex_lock(&dev_list->mutex);
	list_क्रम_each_entry(smcibdev, &dev_list->list, list) अणु
		अगर (num < snum)
			जाओ next;
		अगर (smc_nl_handle_smcr_dev(smcibdev, skb, cb))
			जाओ errout;
next:
		num++;
	पूर्ण
errout:
	mutex_unlock(&dev_list->mutex);
	cb_ctx->pos[0] = num;
पूर्ण

पूर्णांक smcr_nl_get_device(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	smc_nl_prep_smcr_dev(&smc_ib_devices, skb, cb);
	वापस skb->len;
पूर्ण

अटल व्योम smc_ib_qp_event_handler(काष्ठा ib_event *ibevent, व्योम *priv)
अणु
	काष्ठा smc_link *lnk = (काष्ठा smc_link *)priv;
	काष्ठा smc_ib_device *smcibdev = lnk->smcibdev;
	u8 port_idx;

	चयन (ibevent->event) अणु
	हाल IB_EVENT_QP_FATAL:
	हाल IB_EVENT_QP_ACCESS_ERR:
		port_idx = ibevent->element.qp->port - 1;
		अगर (port_idx >= SMC_MAX_PORTS)
			अवरोध;
		set_bit(port_idx, &smcibdev->port_event_mask);
		अगर (!test_and_set_bit(port_idx, smcibdev->ports_going_away))
			schedule_work(&smcibdev->port_event_work);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम smc_ib_destroy_queue_pair(काष्ठा smc_link *lnk)
अणु
	अगर (lnk->roce_qp)
		ib_destroy_qp(lnk->roce_qp);
	lnk->roce_qp = शून्य;
पूर्ण

/* create a queue pair within the protection करोमुख्य क्रम a link */
पूर्णांक smc_ib_create_queue_pair(काष्ठा smc_link *lnk)
अणु
	काष्ठा ib_qp_init_attr qp_attr = अणु
		.event_handler = smc_ib_qp_event_handler,
		.qp_context = lnk,
		.send_cq = lnk->smcibdev->roce_cq_send,
		.recv_cq = lnk->smcibdev->roce_cq_recv,
		.srq = शून्य,
		.cap = अणु
				/* include unsolicited rdma_ग_लिखोs as well,
				 * there are max. 2 RDMA_WRITE per 1 WR_SEND
				 */
			.max_send_wr = SMC_WR_BUF_CNT * 3,
			.max_recv_wr = SMC_WR_BUF_CNT * 3,
			.max_send_sge = SMC_IB_MAX_SEND_SGE,
			.max_recv_sge = 1,
		पूर्ण,
		.sq_sig_type = IB_SIGNAL_REQ_WR,
		.qp_type = IB_QPT_RC,
	पूर्ण;
	पूर्णांक rc;

	lnk->roce_qp = ib_create_qp(lnk->roce_pd, &qp_attr);
	rc = PTR_ERR_OR_ZERO(lnk->roce_qp);
	अगर (IS_ERR(lnk->roce_qp))
		lnk->roce_qp = शून्य;
	अन्यथा
		smc_wr_remember_qp_attr(lnk);
	वापस rc;
पूर्ण

व्योम smc_ib_put_memory_region(काष्ठा ib_mr *mr)
अणु
	ib_dereg_mr(mr);
पूर्ण

अटल पूर्णांक smc_ib_map_mr_sg(काष्ठा smc_buf_desc *buf_slot, u8 link_idx)
अणु
	अचिन्हित पूर्णांक offset = 0;
	पूर्णांक sg_num;

	/* map the largest prefix of a dma mapped SG list */
	sg_num = ib_map_mr_sg(buf_slot->mr_rx[link_idx],
			      buf_slot->sgt[link_idx].sgl,
			      buf_slot->sgt[link_idx].orig_nents,
			      &offset, PAGE_SIZE);

	वापस sg_num;
पूर्ण

/* Allocate a memory region and map the dma mapped SG list of buf_slot */
पूर्णांक smc_ib_get_memory_region(काष्ठा ib_pd *pd, पूर्णांक access_flags,
			     काष्ठा smc_buf_desc *buf_slot, u8 link_idx)
अणु
	अगर (buf_slot->mr_rx[link_idx])
		वापस 0; /* alपढ़ोy करोne */

	buf_slot->mr_rx[link_idx] =
		ib_alloc_mr(pd, IB_MR_TYPE_MEM_REG, 1 << buf_slot->order);
	अगर (IS_ERR(buf_slot->mr_rx[link_idx])) अणु
		पूर्णांक rc;

		rc = PTR_ERR(buf_slot->mr_rx[link_idx]);
		buf_slot->mr_rx[link_idx] = शून्य;
		वापस rc;
	पूर्ण

	अगर (smc_ib_map_mr_sg(buf_slot, link_idx) != 1)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* synchronize buffer usage क्रम cpu access */
व्योम smc_ib_sync_sg_क्रम_cpu(काष्ठा smc_link *lnk,
			    काष्ठा smc_buf_desc *buf_slot,
			    क्रमागत dma_data_direction data_direction)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	/* क्रम now there is just one DMA address */
	क्रम_each_sg(buf_slot->sgt[lnk->link_idx].sgl, sg,
		    buf_slot->sgt[lnk->link_idx].nents, i) अणु
		अगर (!sg_dma_len(sg))
			अवरोध;
		ib_dma_sync_single_क्रम_cpu(lnk->smcibdev->ibdev,
					   sg_dma_address(sg),
					   sg_dma_len(sg),
					   data_direction);
	पूर्ण
पूर्ण

/* synchronize buffer usage क्रम device access */
व्योम smc_ib_sync_sg_क्रम_device(काष्ठा smc_link *lnk,
			       काष्ठा smc_buf_desc *buf_slot,
			       क्रमागत dma_data_direction data_direction)
अणु
	काष्ठा scatterlist *sg;
	अचिन्हित पूर्णांक i;

	/* क्रम now there is just one DMA address */
	क्रम_each_sg(buf_slot->sgt[lnk->link_idx].sgl, sg,
		    buf_slot->sgt[lnk->link_idx].nents, i) अणु
		अगर (!sg_dma_len(sg))
			अवरोध;
		ib_dma_sync_single_क्रम_device(lnk->smcibdev->ibdev,
					      sg_dma_address(sg),
					      sg_dma_len(sg),
					      data_direction);
	पूर्ण
पूर्ण

/* Map a new TX or RX buffer SG-table to DMA */
पूर्णांक smc_ib_buf_map_sg(काष्ठा smc_link *lnk,
		      काष्ठा smc_buf_desc *buf_slot,
		      क्रमागत dma_data_direction data_direction)
अणु
	पूर्णांक mapped_nents;

	mapped_nents = ib_dma_map_sg(lnk->smcibdev->ibdev,
				     buf_slot->sgt[lnk->link_idx].sgl,
				     buf_slot->sgt[lnk->link_idx].orig_nents,
				     data_direction);
	अगर (!mapped_nents)
		वापस -ENOMEM;

	वापस mapped_nents;
पूर्ण

व्योम smc_ib_buf_unmap_sg(काष्ठा smc_link *lnk,
			 काष्ठा smc_buf_desc *buf_slot,
			 क्रमागत dma_data_direction data_direction)
अणु
	अगर (!buf_slot->sgt[lnk->link_idx].sgl->dma_address)
		वापस; /* alपढ़ोy unmapped */

	ib_dma_unmap_sg(lnk->smcibdev->ibdev,
			buf_slot->sgt[lnk->link_idx].sgl,
			buf_slot->sgt[lnk->link_idx].orig_nents,
			data_direction);
	buf_slot->sgt[lnk->link_idx].sgl->dma_address = 0;
पूर्ण

दीर्घ smc_ib_setup_per_ibdev(काष्ठा smc_ib_device *smcibdev)
अणु
	काष्ठा ib_cq_init_attr cqattr =	अणु
		.cqe = SMC_MAX_CQE, .comp_vector = 0 पूर्ण;
	पूर्णांक cqe_size_order, smc_order;
	दीर्घ rc;

	mutex_lock(&smcibdev->mutex);
	rc = 0;
	अगर (smcibdev->initialized)
		जाओ out;
	/* the calculated number of cq entries fits to mlx5 cq allocation */
	cqe_size_order = cache_line_size() == 128 ? 7 : 6;
	smc_order = MAX_ORDER - cqe_size_order - 1;
	अगर (SMC_MAX_CQE + 2 > (0x00000001 << smc_order) * PAGE_SIZE)
		cqattr.cqe = (0x00000001 << smc_order) * PAGE_SIZE - 2;
	smcibdev->roce_cq_send = ib_create_cq(smcibdev->ibdev,
					      smc_wr_tx_cq_handler, शून्य,
					      smcibdev, &cqattr);
	rc = PTR_ERR_OR_ZERO(smcibdev->roce_cq_send);
	अगर (IS_ERR(smcibdev->roce_cq_send)) अणु
		smcibdev->roce_cq_send = शून्य;
		जाओ out;
	पूर्ण
	smcibdev->roce_cq_recv = ib_create_cq(smcibdev->ibdev,
					      smc_wr_rx_cq_handler, शून्य,
					      smcibdev, &cqattr);
	rc = PTR_ERR_OR_ZERO(smcibdev->roce_cq_recv);
	अगर (IS_ERR(smcibdev->roce_cq_recv)) अणु
		smcibdev->roce_cq_recv = शून्य;
		जाओ err;
	पूर्ण
	smc_wr_add_dev(smcibdev);
	smcibdev->initialized = 1;
	जाओ out;

err:
	ib_destroy_cq(smcibdev->roce_cq_send);
out:
	mutex_unlock(&smcibdev->mutex);
	वापस rc;
पूर्ण

अटल व्योम smc_ib_cleanup_per_ibdev(काष्ठा smc_ib_device *smcibdev)
अणु
	mutex_lock(&smcibdev->mutex);
	अगर (!smcibdev->initialized)
		जाओ out;
	smcibdev->initialized = 0;
	ib_destroy_cq(smcibdev->roce_cq_recv);
	ib_destroy_cq(smcibdev->roce_cq_send);
	smc_wr_हटाओ_dev(smcibdev);
out:
	mutex_unlock(&smcibdev->mutex);
पूर्ण

अटल काष्ठा ib_client smc_ib_client;

अटल व्योम smc_copy_netdev_अगरindex(काष्ठा smc_ib_device *smcibdev, पूर्णांक port)
अणु
	काष्ठा ib_device *ibdev = smcibdev->ibdev;
	काष्ठा net_device *ndev;

	अगर (!ibdev->ops.get_netdev)
		वापस;
	ndev = ibdev->ops.get_netdev(ibdev, port + 1);
	अगर (ndev) अणु
		smcibdev->ndev_अगरidx[port] = ndev->अगरindex;
		dev_put(ndev);
	पूर्ण
पूर्ण

व्योम smc_ib_ndev_change(काष्ठा net_device *ndev, अचिन्हित दीर्घ event)
अणु
	काष्ठा smc_ib_device *smcibdev;
	काष्ठा ib_device *libdev;
	काष्ठा net_device *lndev;
	u8 port_cnt;
	पूर्णांक i;

	mutex_lock(&smc_ib_devices.mutex);
	list_क्रम_each_entry(smcibdev, &smc_ib_devices.list, list) अणु
		port_cnt = smcibdev->ibdev->phys_port_cnt;
		क्रम (i = 0; i < min_t(माप_प्रकार, port_cnt, SMC_MAX_PORTS); i++) अणु
			libdev = smcibdev->ibdev;
			अगर (!libdev->ops.get_netdev)
				जारी;
			lndev = libdev->ops.get_netdev(libdev, i + 1);
			अगर (lndev)
				dev_put(lndev);
			अगर (lndev != ndev)
				जारी;
			अगर (event == NETDEV_REGISTER)
				smcibdev->ndev_अगरidx[i] = ndev->अगरindex;
			अगर (event == NETDEV_UNREGISTER)
				smcibdev->ndev_अगरidx[i] = 0;
		पूर्ण
	पूर्ण
	mutex_unlock(&smc_ib_devices.mutex);
पूर्ण

/* callback function क्रम ib_रेजिस्टर_client() */
अटल पूर्णांक smc_ib_add_dev(काष्ठा ib_device *ibdev)
अणु
	काष्ठा smc_ib_device *smcibdev;
	u8 port_cnt;
	पूर्णांक i;

	अगर (ibdev->node_type != RDMA_NODE_IB_CA)
		वापस -EOPNOTSUPP;

	smcibdev = kzalloc(माप(*smcibdev), GFP_KERNEL);
	अगर (!smcibdev)
		वापस -ENOMEM;

	smcibdev->ibdev = ibdev;
	INIT_WORK(&smcibdev->port_event_work, smc_ib_port_event_work);
	atomic_set(&smcibdev->lnk_cnt, 0);
	init_रुकोqueue_head(&smcibdev->lnks_deleted);
	mutex_init(&smcibdev->mutex);
	mutex_lock(&smc_ib_devices.mutex);
	list_add_tail(&smcibdev->list, &smc_ib_devices.list);
	mutex_unlock(&smc_ib_devices.mutex);
	ib_set_client_data(ibdev, &smc_ib_client, smcibdev);
	INIT_IB_EVENT_HANDLER(&smcibdev->event_handler, smcibdev->ibdev,
			      smc_ib_global_event_handler);
	ib_रेजिस्टर_event_handler(&smcibdev->event_handler);

	/* trigger पढ़ोing of the port attributes */
	port_cnt = smcibdev->ibdev->phys_port_cnt;
	pr_warn_ratelimited("smc: adding ib device %s with port count %d\n",
			    smcibdev->ibdev->name, port_cnt);
	क्रम (i = 0;
	     i < min_t(माप_प्रकार, port_cnt, SMC_MAX_PORTS);
	     i++) अणु
		set_bit(i, &smcibdev->port_event_mask);
		/* determine pnetids of the port */
		अगर (smc_pnetid_by_dev_port(ibdev->dev.parent, i,
					   smcibdev->pnetid[i]))
			smc_pnetid_by_table_ib(smcibdev, i + 1);
		smc_copy_netdev_अगरindex(smcibdev, i);
		pr_warn_ratelimited("smc:    ib device %s port %d has pnetid "
				    "%.16s%s\n",
				    smcibdev->ibdev->name, i + 1,
				    smcibdev->pnetid[i],
				    smcibdev->pnetid_by_user[i] ?
				     " (user defined)" :
				     "");
	पूर्ण
	schedule_work(&smcibdev->port_event_work);
	वापस 0;
पूर्ण

/* callback function क्रम ib_unरेजिस्टर_client() */
अटल व्योम smc_ib_हटाओ_dev(काष्ठा ib_device *ibdev, व्योम *client_data)
अणु
	काष्ठा smc_ib_device *smcibdev = client_data;

	mutex_lock(&smc_ib_devices.mutex);
	list_del_init(&smcibdev->list); /* हटाओ from smc_ib_devices */
	mutex_unlock(&smc_ib_devices.mutex);
	pr_warn_ratelimited("smc: removing ib device %s\n",
			    smcibdev->ibdev->name);
	smc_smcr_terminate_all(smcibdev);
	smc_ib_cleanup_per_ibdev(smcibdev);
	ib_unरेजिस्टर_event_handler(&smcibdev->event_handler);
	cancel_work_sync(&smcibdev->port_event_work);
	kमुक्त(smcibdev);
पूर्ण

अटल काष्ठा ib_client smc_ib_client = अणु
	.name	= "smc_ib",
	.add	= smc_ib_add_dev,
	.हटाओ = smc_ib_हटाओ_dev,
पूर्ण;

पूर्णांक __init smc_ib_रेजिस्टर_client(व्योम)
अणु
	smc_ib_init_local_प्रणालीid();
	वापस ib_रेजिस्टर_client(&smc_ib_client);
पूर्ण

व्योम smc_ib_unरेजिस्टर_client(व्योम)
अणु
	ib_unरेजिस्टर_client(&smc_ib_client);
पूर्ण
