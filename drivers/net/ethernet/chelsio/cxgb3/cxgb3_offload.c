<शैली गुरु>
/*
 * Copyright (c) 2006-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <net/neighbour.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/atomic.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/netevent.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>

#समावेश "common.h"
#समावेश "regs.h"
#समावेश "cxgb3_ioctl.h"
#समावेश "cxgb3_ctl_defs.h"
#समावेश "cxgb3_defs.h"
#समावेश "l2t.h"
#समावेश "firmware_exports.h"
#समावेश "cxgb3_offload.h"

अटल LIST_HEAD(client_list);
अटल LIST_HEAD(ofld_dev_list);
अटल DEFINE_MUTEX(cxgb3_db_lock);

अटल DEFINE_RWLOCK(adapter_list_lock);
अटल LIST_HEAD(adapter_list);

अटल स्थिर अचिन्हित पूर्णांक MAX_ATIDS = 64 * 1024;
अटल स्थिर अचिन्हित पूर्णांक ATID_BASE = 0x10000;

अटल व्योम cxgb_neigh_update(काष्ठा neighbour *neigh);
अटल व्योम cxgb_redirect(काष्ठा dst_entry *old, काष्ठा dst_entry *new,
			  काष्ठा neighbour *neigh, स्थिर व्योम *daddr);

अटल अंतरभूत पूर्णांक offload_activated(काष्ठा t3cdev *tdev)
अणु
	स्थिर काष्ठा adapter *adapter = tdev2adap(tdev);

	वापस test_bit(OFFLOAD_DEVMAP_BIT, &adapter->खोलो_device_map);
पूर्ण

/**
 *	cxgb3_रेजिस्टर_client - रेजिस्टर an offload client
 *	@client: the client
 *
 *	Add the client to the client list,
 *	and call backs the client क्रम each activated offload device
 */
व्योम cxgb3_रेजिस्टर_client(काष्ठा cxgb3_client *client)
अणु
	काष्ठा t3cdev *tdev;

	mutex_lock(&cxgb3_db_lock);
	list_add_tail(&client->client_list, &client_list);

	अगर (client->add) अणु
		list_क्रम_each_entry(tdev, &ofld_dev_list, ofld_dev_list) अणु
			अगर (offload_activated(tdev))
				client->add(tdev);
		पूर्ण
	पूर्ण
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

EXPORT_SYMBOL(cxgb3_रेजिस्टर_client);

/**
 *	cxgb3_unरेजिस्टर_client - unरेजिस्टर an offload client
 *	@client: the client
 *
 *	Remove the client to the client list,
 *	and call backs the client क्रम each activated offload device.
 */
व्योम cxgb3_unरेजिस्टर_client(काष्ठा cxgb3_client *client)
अणु
	काष्ठा t3cdev *tdev;

	mutex_lock(&cxgb3_db_lock);
	list_del(&client->client_list);

	अगर (client->हटाओ) अणु
		list_क्रम_each_entry(tdev, &ofld_dev_list, ofld_dev_list) अणु
			अगर (offload_activated(tdev))
				client->हटाओ(tdev);
		पूर्ण
	पूर्ण
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

EXPORT_SYMBOL(cxgb3_unरेजिस्टर_client);

/**
 *	cxgb3_add_clients - activate रेजिस्टरed clients क्रम an offload device
 *	@tdev: the offload device
 *
 *	Call backs all रेजिस्टरed clients once a offload device is activated
 */
व्योम cxgb3_add_clients(काष्ठा t3cdev *tdev)
अणु
	काष्ठा cxgb3_client *client;

	mutex_lock(&cxgb3_db_lock);
	list_क्रम_each_entry(client, &client_list, client_list) अणु
		अगर (client->add)
			client->add(tdev);
	पूर्ण
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

/**
 *	cxgb3_हटाओ_clients - deactivates रेजिस्टरed clients
 *			       क्रम an offload device
 *	@tdev: the offload device
 *
 *	Call backs all रेजिस्टरed clients once a offload device is deactivated
 */
व्योम cxgb3_हटाओ_clients(काष्ठा t3cdev *tdev)
अणु
	काष्ठा cxgb3_client *client;

	mutex_lock(&cxgb3_db_lock);
	list_क्रम_each_entry(client, &client_list, client_list) अणु
		अगर (client->हटाओ)
			client->हटाओ(tdev);
	पूर्ण
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

व्योम cxgb3_event_notअगरy(काष्ठा t3cdev *tdev, u32 event, u32 port)
अणु
	काष्ठा cxgb3_client *client;

	mutex_lock(&cxgb3_db_lock);
	list_क्रम_each_entry(client, &client_list, client_list) अणु
		अगर (client->event_handler)
			client->event_handler(tdev, event, port);
	पूर्ण
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

अटल काष्ठा net_device *get_अगरf_from_mac(काष्ठा adapter *adapter,
					   स्थिर अचिन्हित अक्षर *mac,
					   अचिन्हित पूर्णांक vlan)
अणु
	पूर्णांक i;

	क्रम_each_port(adapter, i) अणु
		काष्ठा net_device *dev = adapter->port[i];

		अगर (ether_addr_equal(dev->dev_addr, mac)) अणु
			rcu_पढ़ो_lock();
			अगर (vlan && vlan != VLAN_VID_MASK) अणु
				dev = __vlan_find_dev_deep_rcu(dev, htons(ETH_P_8021Q), vlan);
			पूर्ण अन्यथा अगर (netअगर_is_bond_slave(dev)) अणु
				काष्ठा net_device *upper_dev;

				जबतक ((upper_dev =
					netdev_master_upper_dev_get_rcu(dev)))
					dev = upper_dev;
			पूर्ण
			rcu_पढ़ो_unlock();
			वापस dev;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक cxgb_ulp_iscsi_ctl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक req,
			      व्योम *data)
अणु
	पूर्णांक i;
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक val = 0;
	काष्ठा ulp_iscsi_info *uiip = data;

	चयन (req) अणु
	हाल ULP_ISCSI_GET_PARAMS:
		uiip->pdev = adapter->pdev;
		uiip->llimit = t3_पढ़ो_reg(adapter, A_ULPRX_ISCSI_LLIMIT);
		uiip->ulimit = t3_पढ़ो_reg(adapter, A_ULPRX_ISCSI_ULIMIT);
		uiip->tagmask = t3_पढ़ो_reg(adapter, A_ULPRX_ISCSI_TAGMASK);

		val = t3_पढ़ो_reg(adapter, A_ULPRX_ISCSI_PSZ);
		क्रम (i = 0; i < 4; i++, val >>= 8)
			uiip->pgsz_factor[i] = val & 0xFF;

		val = t3_पढ़ो_reg(adapter, A_TP_PARA_REG7);
		uiip->max_txsz =
		uiip->max_rxsz = min((val >> S_PMMAXXFERLEN0)&M_PMMAXXFERLEN0,
				     (val >> S_PMMAXXFERLEN1)&M_PMMAXXFERLEN1);
		/*
		 * On tx, the iscsi pdu has to be <= tx page size and has to
		 * fit पूर्णांकo the Tx PM FIFO.
		 */
		val = min(adapter->params.tp.tx_pg_size,
			  t3_पढ़ो_reg(adapter, A_PM1_TX_CFG) >> 17);
		uiip->max_txsz = min(val, uiip->max_txsz);

		/* set MaxRxData to 16224 */
		val = t3_पढ़ो_reg(adapter, A_TP_PARA_REG2);
		अगर ((val >> S_MAXRXDATA) != 0x3f60) अणु
			val &= (M_RXCOALESCESIZE << S_RXCOALESCESIZE);
			val |= V_MAXRXDATA(0x3f60);
			pr_info("%s, iscsi set MaxRxData to 16224 (0x%x)\n",
				adapter->name, val);
			t3_ग_लिखो_reg(adapter, A_TP_PARA_REG2, val);
		पूर्ण

		/*
		 * on rx, the iscsi pdu has to be < rx page size and the
		 * the max rx data length programmed in TP
		 */
		val = min(adapter->params.tp.rx_pg_size,
			  ((t3_पढ़ो_reg(adapter, A_TP_PARA_REG2)) >>
				S_MAXRXDATA) & M_MAXRXDATA);
		uiip->max_rxsz = min(val, uiip->max_rxsz);
		अवरोध;
	हाल ULP_ISCSI_SET_PARAMS:
		t3_ग_लिखो_reg(adapter, A_ULPRX_ISCSI_TAGMASK, uiip->tagmask);
		/* program the ddp page sizes */
		क्रम (i = 0; i < 4; i++)
			val |= (uiip->pgsz_factor[i] & 0xF) << (8 * i);
		अगर (val && (val != t3_पढ़ो_reg(adapter, A_ULPRX_ISCSI_PSZ))) अणु
			pr_info("%s, setting iscsi pgsz 0x%x, %u,%u,%u,%u\n",
				adapter->name, val, uiip->pgsz_factor[0],
				uiip->pgsz_factor[1], uiip->pgsz_factor[2],
				uiip->pgsz_factor[3]);
			t3_ग_लिखो_reg(adapter, A_ULPRX_ISCSI_PSZ, val);
		पूर्ण
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

/* Response queue used क्रम RDMA events. */
#घोषणा ASYNC_NOTIF_RSPQ 0

अटल पूर्णांक cxgb_rdma_ctl(काष्ठा adapter *adapter, अचिन्हित पूर्णांक req, व्योम *data)
अणु
	पूर्णांक ret = 0;

	चयन (req) अणु
	हाल RDMA_GET_PARAMS: अणु
		काष्ठा rdma_info *rdma = data;
		काष्ठा pci_dev *pdev = adapter->pdev;

		rdma->udbell_physbase = pci_resource_start(pdev, 2);
		rdma->udbell_len = pci_resource_len(pdev, 2);
		rdma->tpt_base =
			t3_पढ़ो_reg(adapter, A_ULPTX_TPT_LLIMIT);
		rdma->tpt_top = t3_पढ़ो_reg(adapter, A_ULPTX_TPT_ULIMIT);
		rdma->pbl_base =
			t3_पढ़ो_reg(adapter, A_ULPTX_PBL_LLIMIT);
		rdma->pbl_top = t3_पढ़ो_reg(adapter, A_ULPTX_PBL_ULIMIT);
		rdma->rqt_base = t3_पढ़ो_reg(adapter, A_ULPRX_RQ_LLIMIT);
		rdma->rqt_top = t3_पढ़ो_reg(adapter, A_ULPRX_RQ_ULIMIT);
		rdma->kdb_addr = adapter->regs + A_SG_KDOORBELL;
		rdma->pdev = pdev;
		अवरोध;
	पूर्ण
	हाल RDMA_CQ_OP:अणु
		अचिन्हित दीर्घ flags;
		काष्ठा rdma_cq_op *rdma = data;

		/* may be called in any context */
		spin_lock_irqsave(&adapter->sge.reg_lock, flags);
		ret = t3_sge_cqcntxt_op(adapter, rdma->id, rdma->op,
					rdma->credits);
		spin_unlock_irqrestore(&adapter->sge.reg_lock, flags);
		अवरोध;
	पूर्ण
	हाल RDMA_GET_MEM:अणु
		काष्ठा ch_mem_range *t = data;
		काष्ठा mc7 *mem;

		अगर ((t->addr & 7) || (t->len & 7))
			वापस -EINVAL;
		अगर (t->mem_id == MEM_CM)
			mem = &adapter->cm;
		अन्यथा अगर (t->mem_id == MEM_PMRX)
			mem = &adapter->pmrx;
		अन्यथा अगर (t->mem_id == MEM_PMTX)
			mem = &adapter->pmtx;
		अन्यथा
			वापस -EINVAL;

		ret =
			t3_mc7_bd_पढ़ो(mem, t->addr / 8, t->len / 8,
					(u64 *) t->buf);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण
	हाल RDMA_CQ_SETUP:अणु
		काष्ठा rdma_cq_setup *rdma = data;

		spin_lock_irq(&adapter->sge.reg_lock);
		ret =
			t3_sge_init_cqcntxt(adapter, rdma->id,
					rdma->base_addr, rdma->size,
					ASYNC_NOTIF_RSPQ,
					rdma->ovfl_mode, rdma->credits,
					rdma->credit_thres);
		spin_unlock_irq(&adapter->sge.reg_lock);
		अवरोध;
	पूर्ण
	हाल RDMA_CQ_DISABLE:
		spin_lock_irq(&adapter->sge.reg_lock);
		ret = t3_sge_disable_cqcntxt(adapter, *(अचिन्हित पूर्णांक *)data);
		spin_unlock_irq(&adapter->sge.reg_lock);
		अवरोध;
	हाल RDMA_CTRL_QP_SETUP:अणु
		काष्ठा rdma_ctrlqp_setup *rdma = data;

		spin_lock_irq(&adapter->sge.reg_lock);
		ret = t3_sge_init_ecntxt(adapter, FW_RI_SGEEC_START, 0,
						SGE_CNTXT_RDMA,
						ASYNC_NOTIF_RSPQ,
						rdma->base_addr, rdma->size,
						FW_RI_TID_START, 1, 0);
		spin_unlock_irq(&adapter->sge.reg_lock);
		अवरोध;
	पूर्ण
	हाल RDMA_GET_MIB: अणु
		spin_lock(&adapter->stats_lock);
		t3_tp_get_mib_stats(adapter, (काष्ठा tp_mib_stats *)data);
		spin_unlock(&adapter->stats_lock);
		अवरोध;
	पूर्ण
	शेष:
		ret = -EOPNOTSUPP;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक cxgb_offload_ctl(काष्ठा t3cdev *tdev, अचिन्हित पूर्णांक req, व्योम *data)
अणु
	काष्ठा adapter *adapter = tdev2adap(tdev);
	काष्ठा tid_range *tid;
	काष्ठा mtutab *mtup;
	काष्ठा अगरf_mac *अगरfmacp;
	काष्ठा ddp_params *ddpp;
	काष्ठा adap_ports *ports;
	काष्ठा ofld_page_info *rx_page_info;
	काष्ठा tp_params *tp = &adapter->params.tp;
	पूर्णांक i;

	चयन (req) अणु
	हाल GET_MAX_OUTSTANDING_WR:
		*(अचिन्हित पूर्णांक *)data = FW_WR_NUM;
		अवरोध;
	हाल GET_WR_LEN:
		*(अचिन्हित पूर्णांक *)data = WR_FLITS;
		अवरोध;
	हाल GET_TX_MAX_CHUNK:
		*(अचिन्हित पूर्णांक *)data = 1 << 20;	/* 1MB */
		अवरोध;
	हाल GET_TID_RANGE:
		tid = data;
		tid->num = t3_mc5_size(&adapter->mc5) -
		    adapter->params.mc5.nroutes -
		    adapter->params.mc5.nfilters - adapter->params.mc5.nservers;
		tid->base = 0;
		अवरोध;
	हाल GET_STID_RANGE:
		tid = data;
		tid->num = adapter->params.mc5.nservers;
		tid->base = t3_mc5_size(&adapter->mc5) - tid->num -
		    adapter->params.mc5.nfilters - adapter->params.mc5.nroutes;
		अवरोध;
	हाल GET_L2T_CAPACITY:
		*(अचिन्हित पूर्णांक *)data = 2048;
		अवरोध;
	हाल GET_MTUS:
		mtup = data;
		mtup->size = NMTUS;
		mtup->mtus = adapter->params.mtus;
		अवरोध;
	हाल GET_IFF_FROM_MAC:
		अगरfmacp = data;
		अगरfmacp->dev = get_अगरf_from_mac(adapter, अगरfmacp->mac_addr,
						अगरfmacp->vlan_tag &
						VLAN_VID_MASK);
		अवरोध;
	हाल GET_DDP_PARAMS:
		ddpp = data;
		ddpp->llimit = t3_पढ़ो_reg(adapter, A_ULPRX_TDDP_LLIMIT);
		ddpp->ulimit = t3_पढ़ो_reg(adapter, A_ULPRX_TDDP_ULIMIT);
		ddpp->tag_mask = t3_पढ़ो_reg(adapter, A_ULPRX_TDDP_TAGMASK);
		अवरोध;
	हाल GET_PORTS:
		ports = data;
		ports->nports = adapter->params.nports;
		क्रम_each_port(adapter, i)
			ports->lldevs[i] = adapter->port[i];
		अवरोध;
	हाल ULP_ISCSI_GET_PARAMS:
	हाल ULP_ISCSI_SET_PARAMS:
		अगर (!offload_running(adapter))
			वापस -EAGAIN;
		वापस cxgb_ulp_iscsi_ctl(adapter, req, data);
	हाल RDMA_GET_PARAMS:
	हाल RDMA_CQ_OP:
	हाल RDMA_CQ_SETUP:
	हाल RDMA_CQ_DISABLE:
	हाल RDMA_CTRL_QP_SETUP:
	हाल RDMA_GET_MEM:
	हाल RDMA_GET_MIB:
		अगर (!offload_running(adapter))
			वापस -EAGAIN;
		वापस cxgb_rdma_ctl(adapter, req, data);
	हाल GET_RX_PAGE_INFO:
		rx_page_info = data;
		rx_page_info->page_size = tp->rx_pg_size;
		rx_page_info->num = tp->rx_num_pgs;
		अवरोध;
	हाल GET_ISCSI_IPV4ADDR: अणु
		काष्ठा iscsi_ipv4addr *p = data;
		काष्ठा port_info *pi = netdev_priv(p->dev);
		p->ipv4addr = pi->iscsi_ipv4addr;
		अवरोध;
	पूर्ण
	हाल GET_EMBEDDED_INFO: अणु
		काष्ठा ch_embedded_info *e = data;

		spin_lock(&adapter->stats_lock);
		t3_get_fw_version(adapter, &e->fw_vers);
		t3_get_tp_version(adapter, &e->tp_vers);
		spin_unlock(&adapter->stats_lock);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Dummy handler क्रम Rx offload packets in हाल we get an offload packet beक्रमe
 * proper processing is setup.  This complains and drops the packet as it isn't
 * normal to get offload packets at this stage.
 */
अटल पूर्णांक rx_offload_blackhole(काष्ठा t3cdev *dev, काष्ठा sk_buff **skbs,
				पूर्णांक n)
अणु
	जबतक (n--)
		dev_kमुक्त_skb_any(skbs[n]);
	वापस 0;
पूर्ण

अटल व्योम dummy_neigh_update(काष्ठा t3cdev *dev, काष्ठा neighbour *neigh)
अणु
पूर्ण

व्योम cxgb3_set_dummy_ops(काष्ठा t3cdev *dev)
अणु
	dev->recv = rx_offload_blackhole;
	dev->neigh_update = dummy_neigh_update;
पूर्ण

/*
 * Free an active-खोलो TID.
 */
व्योम *cxgb3_मुक्त_atid(काष्ठा t3cdev *tdev, पूर्णांक atid)
अणु
	काष्ठा tid_info *t = &(T3C_DATA(tdev))->tid_maps;
	जोड़ active_खोलो_entry *p = atid2entry(t, atid);
	व्योम *ctx = p->t3c_tid.ctx;

	spin_lock_bh(&t->atid_lock);
	p->next = t->aमुक्त;
	t->aमुक्त = p;
	t->atids_in_use--;
	spin_unlock_bh(&t->atid_lock);

	वापस ctx;
पूर्ण

EXPORT_SYMBOL(cxgb3_मुक्त_atid);

/*
 * Free a server TID and वापस it to the मुक्त pool.
 */
व्योम cxgb3_मुक्त_stid(काष्ठा t3cdev *tdev, पूर्णांक stid)
अणु
	काष्ठा tid_info *t = &(T3C_DATA(tdev))->tid_maps;
	जोड़ listen_entry *p = stid2entry(t, stid);

	spin_lock_bh(&t->stid_lock);
	p->next = t->sमुक्त;
	t->sमुक्त = p;
	t->stids_in_use--;
	spin_unlock_bh(&t->stid_lock);
पूर्ण

EXPORT_SYMBOL(cxgb3_मुक्त_stid);

व्योम cxgb3_insert_tid(काष्ठा t3cdev *tdev, काष्ठा cxgb3_client *client,
		      व्योम *ctx, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	t->tid_tab[tid].client = client;
	t->tid_tab[tid].ctx = ctx;
	atomic_inc(&t->tids_in_use);
पूर्ण

EXPORT_SYMBOL(cxgb3_insert_tid);

/*
 * Populate a TID_RELEASE WR.  The skb must be alपढ़ोy propely sized.
 */
अटल अंतरभूत व्योम mk_tid_release(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा cpl_tid_release *req;

	skb->priority = CPL_PRIORITY_SETUP;
	req = __skb_put(skb, माप(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_TID_RELEASE, tid));
पूर्ण

अटल व्योम t3_process_tid_release_list(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा t3c_data *td = container_of(work, काष्ठा t3c_data,
					   tid_release_task);
	काष्ठा sk_buff *skb;
	काष्ठा t3cdev *tdev = td->dev;


	spin_lock_bh(&td->tid_release_lock);
	जबतक (td->tid_release_list) अणु
		काष्ठा t3c_tid_entry *p = td->tid_release_list;

		td->tid_release_list = p->ctx;
		spin_unlock_bh(&td->tid_release_lock);

		skb = alloc_skb(माप(काष्ठा cpl_tid_release),
				GFP_KERNEL);
		अगर (!skb)
			skb = td->nofail_skb;
		अगर (!skb) अणु
			spin_lock_bh(&td->tid_release_lock);
			p->ctx = (व्योम *)td->tid_release_list;
			td->tid_release_list = p;
			अवरोध;
		पूर्ण
		mk_tid_release(skb, p - td->tid_maps.tid_tab);
		cxgb3_ofld_send(tdev, skb);
		p->ctx = शून्य;
		अगर (skb == td->nofail_skb)
			td->nofail_skb =
				alloc_skb(माप(काष्ठा cpl_tid_release),
					GFP_KERNEL);
		spin_lock_bh(&td->tid_release_lock);
	पूर्ण
	td->release_list_incomplete = (td->tid_release_list == शून्य) ? 0 : 1;
	spin_unlock_bh(&td->tid_release_lock);

	अगर (!td->nofail_skb)
		td->nofail_skb =
			alloc_skb(माप(काष्ठा cpl_tid_release),
				GFP_KERNEL);
पूर्ण

/* use ctx as a next poपूर्णांकer in the tid release list */
व्योम cxgb3_queue_tid_release(काष्ठा t3cdev *tdev, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा t3c_data *td = T3C_DATA(tdev);
	काष्ठा t3c_tid_entry *p = &td->tid_maps.tid_tab[tid];

	spin_lock_bh(&td->tid_release_lock);
	p->ctx = (व्योम *)td->tid_release_list;
	p->client = शून्य;
	td->tid_release_list = p;
	अगर (!p->ctx || td->release_list_incomplete)
		schedule_work(&td->tid_release_task);
	spin_unlock_bh(&td->tid_release_lock);
पूर्ण

EXPORT_SYMBOL(cxgb3_queue_tid_release);

/*
 * Remove a tid from the TID table.  A client may defer processing its last
 * CPL message अगर it is locked at the समय it arrives, and जबतक the message
 * sits in the client's backlog the TID may be reused क्रम another connection.
 * To handle this we atomically चयन the TID association अगर it still poपूर्णांकs
 * to the original client context.
 */
व्योम cxgb3_हटाओ_tid(काष्ठा t3cdev *tdev, व्योम *ctx, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	BUG_ON(tid >= t->ntids);
	अगर (tdev->type == T3A)
		(व्योम)cmpxchg(&t->tid_tab[tid].ctx, ctx, शून्य);
	अन्यथा अणु
		काष्ठा sk_buff *skb;

		skb = alloc_skb(माप(काष्ठा cpl_tid_release), GFP_ATOMIC);
		अगर (likely(skb)) अणु
			mk_tid_release(skb, tid);
			cxgb3_ofld_send(tdev, skb);
			t->tid_tab[tid].ctx = शून्य;
		पूर्ण अन्यथा
			cxgb3_queue_tid_release(tdev, tid);
	पूर्ण
	atomic_dec(&t->tids_in_use);
पूर्ण

EXPORT_SYMBOL(cxgb3_हटाओ_tid);

पूर्णांक cxgb3_alloc_atid(काष्ठा t3cdev *tdev, काष्ठा cxgb3_client *client,
		     व्योम *ctx)
अणु
	पूर्णांक atid = -1;
	काष्ठा tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	spin_lock_bh(&t->atid_lock);
	अगर (t->aमुक्त &&
	    t->atids_in_use + atomic_पढ़ो(&t->tids_in_use) + MC5_MIN_TIDS <=
	    t->ntids) अणु
		जोड़ active_खोलो_entry *p = t->aमुक्त;

		atid = (p - t->atid_tab) + t->atid_base;
		t->aमुक्त = p->next;
		p->t3c_tid.ctx = ctx;
		p->t3c_tid.client = client;
		t->atids_in_use++;
	पूर्ण
	spin_unlock_bh(&t->atid_lock);
	वापस atid;
पूर्ण

EXPORT_SYMBOL(cxgb3_alloc_atid);

पूर्णांक cxgb3_alloc_stid(काष्ठा t3cdev *tdev, काष्ठा cxgb3_client *client,
		     व्योम *ctx)
अणु
	पूर्णांक stid = -1;
	काष्ठा tid_info *t = &(T3C_DATA(tdev))->tid_maps;

	spin_lock_bh(&t->stid_lock);
	अगर (t->sमुक्त) अणु
		जोड़ listen_entry *p = t->sमुक्त;

		stid = (p - t->stid_tab) + t->stid_base;
		t->sमुक्त = p->next;
		p->t3c_tid.ctx = ctx;
		p->t3c_tid.client = client;
		t->stids_in_use++;
	पूर्ण
	spin_unlock_bh(&t->stid_lock);
	वापस stid;
पूर्ण

EXPORT_SYMBOL(cxgb3_alloc_stid);

/* Get the t3cdev associated with a net_device */
काष्ठा t3cdev *dev2t3cdev(काष्ठा net_device *dev)
अणु
	स्थिर काष्ठा port_info *pi = netdev_priv(dev);

	वापस (काष्ठा t3cdev *)pi->adapter;
पूर्ण

EXPORT_SYMBOL(dev2t3cdev);

अटल पूर्णांक करो_smt_ग_लिखो_rpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_smt_ग_लिखो_rpl *rpl = cplhdr(skb);

	अगर (rpl->status != CPL_ERR_NONE)
		pr_err("Unexpected SMT_WRITE_RPL status %u for entry %u\n",
		       rpl->status, GET_TID(rpl));

	वापस CPL_RET_BUF_DONE;
पूर्ण

अटल पूर्णांक करो_l2t_ग_लिखो_rpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_l2t_ग_लिखो_rpl *rpl = cplhdr(skb);

	अगर (rpl->status != CPL_ERR_NONE)
		pr_err("Unexpected L2T_WRITE_RPL status %u for entry %u\n",
		       rpl->status, GET_TID(rpl));

	वापस CPL_RET_BUF_DONE;
पूर्ण

अटल पूर्णांक करो_rte_ग_लिखो_rpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_rte_ग_लिखो_rpl *rpl = cplhdr(skb);

	अगर (rpl->status != CPL_ERR_NONE)
		pr_err("Unexpected RTE_WRITE_RPL status %u for entry %u\n",
		       rpl->status, GET_TID(rpl));

	वापस CPL_RET_BUF_DONE;
पूर्ण

अटल पूर्णांक करो_act_खोलो_rpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_act_खोलो_rpl *rpl = cplhdr(skb);
	अचिन्हित पूर्णांक atid = G_TID(ntohl(rpl->atid));
	काष्ठा t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_atid(&(T3C_DATA(dev))->tid_maps, atid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client &&
	    t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[CPL_ACT_OPEN_RPL]) अणु
		वापस t3c_tid->client->handlers[CPL_ACT_OPEN_RPL] (dev, skb,
								    t3c_tid->
								    ctx);
	पूर्ण अन्यथा अणु
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, CPL_ACT_OPEN_RPL);
		वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_stid_rpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	जोड़ opcode_tid *p = cplhdr(skb);
	अचिन्हित पूर्णांक stid = G_TID(ntohl(p->opcode_tid));
	काष्ठा t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_stid(&(T3C_DATA(dev))->tid_maps, stid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[p->opcode]) अणु
		वापस t3c_tid->client->handlers[p->opcode] (dev, skb,
							     t3c_tid->ctx);
	पूर्ण अन्यथा अणु
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, p->opcode);
		वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_hwtid_rpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	जोड़ opcode_tid *p = cplhdr(skb);
	अचिन्हित पूर्णांक hwtid = G_TID(ntohl(p->opcode_tid));
	काष्ठा t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[p->opcode]) अणु
		वापस t3c_tid->client->handlers[p->opcode]
		    (dev, skb, t3c_tid->ctx);
	पूर्ण अन्यथा अणु
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, p->opcode);
		वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_cr(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_pass_accept_req *req = cplhdr(skb);
	अचिन्हित पूर्णांक stid = G_PASS_OPEN_TID(ntohl(req->tos_tid));
	काष्ठा tid_info *t = &(T3C_DATA(dev))->tid_maps;
	काष्ठा t3c_tid_entry *t3c_tid;
	अचिन्हित पूर्णांक tid = GET_TID(req);

	अगर (unlikely(tid >= t->ntids)) अणु
		prपूर्णांकk("%s: passive open TID %u too large\n",
		       dev->name, tid);
		t3_fatal_err(tdev2adap(dev));
		वापस CPL_RET_BUF_DONE;
	पूर्ण

	t3c_tid = lookup_stid(t, stid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[CPL_PASS_ACCEPT_REQ]) अणु
		वापस t3c_tid->client->handlers[CPL_PASS_ACCEPT_REQ]
		    (dev, skb, t3c_tid->ctx);
	पूर्ण अन्यथा अणु
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, CPL_PASS_ACCEPT_REQ);
		वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	पूर्ण
पूर्ण

/*
 * Returns an sk_buff क्रम a reply CPL message of size len.  If the input
 * sk_buff has no other users it is trimmed and reused, otherwise a new buffer
 * is allocated.  The input skb must be of size at least len.  Note that this
 * operation करोes not destroy the original skb data even अगर it decides to reuse
 * the buffer.
 */
अटल काष्ठा sk_buff *cxgb3_get_cpl_reply_skb(काष्ठा sk_buff *skb, माप_प्रकार len,
					       gfp_t gfp)
अणु
	अगर (likely(!skb_cloned(skb))) अणु
		BUG_ON(skb->len < len);
		__skb_trim(skb, len);
		skb_get(skb);
	पूर्ण अन्यथा अणु
		skb = alloc_skb(len, gfp);
		अगर (skb)
			__skb_put(skb, len);
	पूर्ण
	वापस skb;
पूर्ण

अटल पूर्णांक करो_पात_req_rss(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	जोड़ opcode_tid *p = cplhdr(skb);
	अचिन्हित पूर्णांक hwtid = G_TID(ntohl(p->opcode_tid));
	काष्ठा t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[p->opcode]) अणु
		वापस t3c_tid->client->handlers[p->opcode]
		    (dev, skb, t3c_tid->ctx);
	पूर्ण अन्यथा अणु
		काष्ठा cpl_पात_req_rss *req = cplhdr(skb);
		काष्ठा cpl_पात_rpl *rpl;
		काष्ठा sk_buff *reply_skb;
		अचिन्हित पूर्णांक tid = GET_TID(req);
		u8 cmd = req->status;

		अगर (req->status == CPL_ERR_RTX_NEG_ADVICE ||
		    req->status == CPL_ERR_PERSIST_NEG_ADVICE)
			जाओ out;

		reply_skb = cxgb3_get_cpl_reply_skb(skb,
						    माप(काष्ठा
							   cpl_पात_rpl),
						    GFP_ATOMIC);

		अगर (!reply_skb) अणु
			prपूर्णांकk("do_abort_req_rss: couldn't get skb!\n");
			जाओ out;
		पूर्ण
		reply_skb->priority = CPL_PRIORITY_DATA;
		__skb_put(reply_skb, माप(काष्ठा cpl_पात_rpl));
		rpl = cplhdr(reply_skb);
		rpl->wr.wr_hi =
		    htonl(V_WR_OP(FW_WROPCODE_OFLD_HOST_ABORT_CON_RPL));
		rpl->wr.wr_lo = htonl(V_WR_TID(tid));
		OPCODE_TID(rpl) = htonl(MK_OPCODE_TID(CPL_ABORT_RPL, tid));
		rpl->cmd = cmd;
		cxgb3_ofld_send(dev, reply_skb);
out:
		वापस CPL_RET_BUF_DONE;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_act_establish(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_act_establish *req = cplhdr(skb);
	अचिन्हित पूर्णांक atid = G_PASS_OPEN_TID(ntohl(req->tos_tid));
	काष्ठा tid_info *t = &(T3C_DATA(dev))->tid_maps;
	काष्ठा t3c_tid_entry *t3c_tid;
	अचिन्हित पूर्णांक tid = GET_TID(req);

	अगर (unlikely(tid >= t->ntids)) अणु
		prपूर्णांकk("%s: active establish TID %u too large\n",
		       dev->name, tid);
		t3_fatal_err(tdev2adap(dev));
		वापस CPL_RET_BUF_DONE;
	पूर्ण

	t3c_tid = lookup_atid(t, atid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[CPL_ACT_ESTABLISH]) अणु
		वापस t3c_tid->client->handlers[CPL_ACT_ESTABLISH]
		    (dev, skb, t3c_tid->ctx);
	पूर्ण अन्यथा अणु
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, CPL_ACT_ESTABLISH);
		वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	पूर्ण
पूर्ण

अटल पूर्णांक करो_trace(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	काष्ठा cpl_trace_pkt *p = cplhdr(skb);

	skb->protocol = htons(0xffff);
	skb->dev = dev->lldev;
	skb_pull(skb, माप(*p));
	skb_reset_mac_header(skb);
	netअगर_receive_skb(skb);
	वापस 0;
पूर्ण

/*
 * That skb would better have come from process_responses() where we abuse
 * ->priority and ->csum to carry our data.  NB: अगर we get to per-arch
 * ->csum, the things might get really पूर्णांकeresting here.
 */

अटल अंतरभूत u32 get_hwtid(काष्ठा sk_buff *skb)
अणु
	वापस ntohl((__क्रमce __be32)skb->priority) >> 8 & 0xfffff;
पूर्ण

अटल अंतरभूत u32 get_opcode(काष्ठा sk_buff *skb)
अणु
	वापस G_OPCODE(ntohl((__क्रमce __be32)skb->csum));
पूर्ण

अटल पूर्णांक करो_term(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक hwtid = get_hwtid(skb);
	अचिन्हित पूर्णांक opcode = get_opcode(skb);
	काष्ठा t3c_tid_entry *t3c_tid;

	t3c_tid = lookup_tid(&(T3C_DATA(dev))->tid_maps, hwtid);
	अगर (t3c_tid && t3c_tid->ctx && t3c_tid->client->handlers &&
	    t3c_tid->client->handlers[opcode]) अणु
		वापस t3c_tid->client->handlers[opcode] (dev, skb,
							  t3c_tid->ctx);
	पूर्ण अन्यथा अणु
		pr_err("%s: received clientless CPL command 0x%x\n",
		       dev->name, opcode);
		वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
	पूर्ण
पूर्ण

अटल पूर्णांक nb_callback(काष्ठा notअगरier_block *self, अचिन्हित दीर्घ event,
		       व्योम *ctx)
अणु
	चयन (event) अणु
	हाल (NETEVENT_NEIGH_UPDATE):अणु
		cxgb_neigh_update((काष्ठा neighbour *)ctx);
		अवरोध;
	पूर्ण
	हाल (NETEVENT_REसूचीECT):अणु
		काष्ठा netevent_redirect *nr = ctx;
		cxgb_redirect(nr->old, nr->new, nr->neigh,
			      nr->daddr);
		cxgb_neigh_update(nr->neigh);
		अवरोध;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block nb = अणु
	.notअगरier_call = nb_callback
पूर्ण;

/*
 * Process a received packet with an unknown/unexpected CPL opcode.
 */
अटल पूर्णांक करो_bad_cpl(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	pr_err("%s: received bad CPL command 0x%x\n", dev->name, *skb->data);
	वापस CPL_RET_BUF_DONE | CPL_RET_BAD_MSG;
पूर्ण

/*
 * Handlers क्रम each CPL opcode
 */
अटल cpl_handler_func cpl_handlers[NUM_CPL_CMDS];

/*
 * Add a new handler to the CPL dispatch table.  A शून्य handler may be supplied
 * to unरेजिस्टर an existing handler.
 */
व्योम t3_रेजिस्टर_cpl_handler(अचिन्हित पूर्णांक opcode, cpl_handler_func h)
अणु
	अगर (opcode < NUM_CPL_CMDS)
		cpl_handlers[opcode] = h ? h : करो_bad_cpl;
	अन्यथा
		pr_err("T3C: handler registration for opcode %x failed\n",
		       opcode);
पूर्ण

EXPORT_SYMBOL(t3_रेजिस्टर_cpl_handler);

/*
 * T3CDEV's receive method.
 */
अटल पूर्णांक process_rx(काष्ठा t3cdev *dev, काष्ठा sk_buff **skbs, पूर्णांक n)
अणु
	जबतक (n--) अणु
		काष्ठा sk_buff *skb = *skbs++;
		अचिन्हित पूर्णांक opcode = get_opcode(skb);
		पूर्णांक ret = cpl_handlers[opcode] (dev, skb);

#अगर VALIDATE_TID
		अगर (ret & CPL_RET_UNKNOWN_TID) अणु
			जोड़ opcode_tid *p = cplhdr(skb);

			pr_err("%s: CPL message (opcode %u) had unknown TID %u\n",
			       dev->name, opcode, G_TID(ntohl(p->opcode_tid)));
		पूर्ण
#पूर्ण_अगर
		अगर (ret & CPL_RET_BUF_DONE)
			kमुक्त_skb(skb);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Sends an sk_buff to a T3C driver after dealing with any active network taps.
 */
पूर्णांक cxgb3_ofld_send(काष्ठा t3cdev *dev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक r;

	local_bh_disable();
	r = dev->send(dev, skb);
	local_bh_enable();
	वापस r;
पूर्ण

EXPORT_SYMBOL(cxgb3_ofld_send);

अटल पूर्णांक is_offloading(काष्ठा net_device *dev)
अणु
	काष्ठा adapter *adapter;
	पूर्णांक i;

	पढ़ो_lock_bh(&adapter_list_lock);
	list_क्रम_each_entry(adapter, &adapter_list, adapter_list) अणु
		क्रम_each_port(adapter, i) अणु
			अगर (dev == adapter->port[i]) अणु
				पढ़ो_unlock_bh(&adapter_list_lock);
				वापस 1;
			पूर्ण
		पूर्ण
	पूर्ण
	पढ़ो_unlock_bh(&adapter_list_lock);
	वापस 0;
पूर्ण

अटल व्योम cxgb_neigh_update(काष्ठा neighbour *neigh)
अणु
	काष्ठा net_device *dev;

	अगर (!neigh)
		वापस;
	dev = neigh->dev;
	अगर (dev && (is_offloading(dev))) अणु
		काष्ठा t3cdev *tdev = dev2t3cdev(dev);

		BUG_ON(!tdev);
		t3_l2t_update(tdev, neigh);
	पूर्ण
पूर्ण

अटल व्योम set_l2t_ix(काष्ठा t3cdev *tdev, u32 tid, काष्ठा l2t_entry *e)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा cpl_set_tcb_field *req;

	skb = alloc_skb(माप(*req), GFP_ATOMIC);
	अगर (!skb) अणु
		pr_err("%s: cannot allocate skb!\n", __func__);
		वापस;
	पूर्ण
	skb->priority = CPL_PRIORITY_CONTROL;
	req = skb_put(skb, माप(*req));
	req->wr.wr_hi = htonl(V_WR_OP(FW_WROPCODE_FORWARD));
	OPCODE_TID(req) = htonl(MK_OPCODE_TID(CPL_SET_TCB_FIELD, tid));
	req->reply = 0;
	req->cpu_idx = 0;
	req->word = htons(W_TCB_L2T_IX);
	req->mask = cpu_to_be64(V_TCB_L2T_IX(M_TCB_L2T_IX));
	req->val = cpu_to_be64(V_TCB_L2T_IX(e->idx));
	tdev->send(tdev, skb);
पूर्ण

अटल व्योम cxgb_redirect(काष्ठा dst_entry *old, काष्ठा dst_entry *new,
			  काष्ठा neighbour *neigh,
			  स्थिर व्योम *daddr)
अणु
	काष्ठा net_device *dev;
	काष्ठा tid_info *ti;
	काष्ठा t3cdev *tdev;
	u32 tid;
	पूर्णांक update_tcb;
	काष्ठा l2t_entry *e;
	काष्ठा t3c_tid_entry *te;

	dev = neigh->dev;

	अगर (!is_offloading(dev))
		वापस;
	tdev = dev2t3cdev(dev);
	BUG_ON(!tdev);

	/* Add new L2T entry */
	e = t3_l2t_get(tdev, new, dev, daddr);
	अगर (!e) अणु
		pr_err("%s: couldn't allocate new l2t entry!\n", __func__);
		वापस;
	पूर्ण

	/* Walk tid table and notअगरy clients of dst change. */
	ti = &(T3C_DATA(tdev))->tid_maps;
	क्रम (tid = 0; tid < ti->ntids; tid++) अणु
		te = lookup_tid(ti, tid);
		BUG_ON(!te);
		अगर (te && te->ctx && te->client && te->client->redirect) अणु
			update_tcb = te->client->redirect(te->ctx, old, new, e);
			अगर (update_tcb) अणु
				rcu_पढ़ो_lock();
				l2t_hold(L2DATA(tdev), e);
				rcu_पढ़ो_unlock();
				set_l2t_ix(tdev, tid, e);
			पूर्ण
		पूर्ण
	पूर्ण
	l2t_release(tdev, e);
पूर्ण

/*
 * Allocate and initialize the TID tables.  Returns 0 on success.
 */
अटल पूर्णांक init_tid_tअसल(काष्ठा tid_info *t, अचिन्हित पूर्णांक ntids,
			 अचिन्हित पूर्णांक natids, अचिन्हित पूर्णांक nstids,
			 अचिन्हित पूर्णांक atid_base, अचिन्हित पूर्णांक stid_base)
अणु
	अचिन्हित दीर्घ size = ntids * माप(*t->tid_tab) +
	    natids * माप(*t->atid_tab) + nstids * माप(*t->stid_tab);

	t->tid_tab = kvzalloc(size, GFP_KERNEL);
	अगर (!t->tid_tab)
		वापस -ENOMEM;

	t->stid_tab = (जोड़ listen_entry *)&t->tid_tab[ntids];
	t->atid_tab = (जोड़ active_खोलो_entry *)&t->stid_tab[nstids];
	t->ntids = ntids;
	t->nstids = nstids;
	t->stid_base = stid_base;
	t->sमुक्त = शून्य;
	t->natids = natids;
	t->atid_base = atid_base;
	t->aमुक्त = शून्य;
	t->stids_in_use = t->atids_in_use = 0;
	atomic_set(&t->tids_in_use, 0);
	spin_lock_init(&t->stid_lock);
	spin_lock_init(&t->atid_lock);

	/*
	 * Setup the मुक्त lists क्रम stid_tab and atid_tab.
	 */
	अगर (nstids) अणु
		जबतक (--nstids)
			t->stid_tab[nstids - 1].next = &t->stid_tab[nstids];
		t->sमुक्त = t->stid_tab;
	पूर्ण
	अगर (natids) अणु
		जबतक (--natids)
			t->atid_tab[natids - 1].next = &t->atid_tab[natids];
		t->aमुक्त = t->atid_tab;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम मुक्त_tid_maps(काष्ठा tid_info *t)
अणु
	kvमुक्त(t->tid_tab);
पूर्ण

अटल अंतरभूत व्योम add_adapter(काष्ठा adapter *adap)
अणु
	ग_लिखो_lock_bh(&adapter_list_lock);
	list_add_tail(&adap->adapter_list, &adapter_list);
	ग_लिखो_unlock_bh(&adapter_list_lock);
पूर्ण

अटल अंतरभूत व्योम हटाओ_adapter(काष्ठा adapter *adap)
अणु
	ग_लिखो_lock_bh(&adapter_list_lock);
	list_del(&adap->adapter_list);
	ग_लिखो_unlock_bh(&adapter_list_lock);
पूर्ण

पूर्णांक cxgb3_offload_activate(काष्ठा adapter *adapter)
अणु
	काष्ठा t3cdev *dev = &adapter->tdev;
	पूर्णांक natids, err;
	काष्ठा t3c_data *t;
	काष्ठा tid_range stid_range, tid_range;
	काष्ठा mtutab mtutab;
	अचिन्हित पूर्णांक l2t_capacity;
	काष्ठा l2t_data *l2td;

	t = kzalloc(माप(*t), GFP_KERNEL);
	अगर (!t)
		वापस -ENOMEM;

	err = -EOPNOTSUPP;
	अगर (dev->ctl(dev, GET_TX_MAX_CHUNK, &t->tx_max_chunk) < 0 ||
	    dev->ctl(dev, GET_MAX_OUTSTANDING_WR, &t->max_wrs) < 0 ||
	    dev->ctl(dev, GET_L2T_CAPACITY, &l2t_capacity) < 0 ||
	    dev->ctl(dev, GET_MTUS, &mtutab) < 0 ||
	    dev->ctl(dev, GET_TID_RANGE, &tid_range) < 0 ||
	    dev->ctl(dev, GET_STID_RANGE, &stid_range) < 0)
		जाओ out_मुक्त;

	err = -ENOMEM;
	l2td = t3_init_l2t(l2t_capacity);
	अगर (!l2td)
		जाओ out_मुक्त;

	natids = min(tid_range.num / 2, MAX_ATIDS);
	err = init_tid_tअसल(&t->tid_maps, tid_range.num, natids,
			    stid_range.num, ATID_BASE, stid_range.base);
	अगर (err)
		जाओ out_मुक्त_l2t;

	t->mtus = mtutab.mtus;
	t->nmtus = mtutab.size;

	INIT_WORK(&t->tid_release_task, t3_process_tid_release_list);
	spin_lock_init(&t->tid_release_lock);
	INIT_LIST_HEAD(&t->list_node);
	t->dev = dev;

	RCU_INIT_POINTER(dev->l2opt, l2td);
	T3C_DATA(dev) = t;
	dev->recv = process_rx;
	dev->neigh_update = t3_l2t_update;

	/* Register netevent handler once */
	अगर (list_empty(&adapter_list))
		रेजिस्टर_netevent_notअगरier(&nb);

	t->nofail_skb = alloc_skb(माप(काष्ठा cpl_tid_release), GFP_KERNEL);
	t->release_list_incomplete = 0;

	add_adapter(adapter);
	वापस 0;

out_मुक्त_l2t:
	kvमुक्त(l2td);
out_मुक्त:
	kमुक्त(t);
	वापस err;
पूर्ण

अटल व्योम clean_l2_data(काष्ठा rcu_head *head)
अणु
	काष्ठा l2t_data *d = container_of(head, काष्ठा l2t_data, rcu_head);
	kvमुक्त(d);
पूर्ण


व्योम cxgb3_offload_deactivate(काष्ठा adapter *adapter)
अणु
	काष्ठा t3cdev *tdev = &adapter->tdev;
	काष्ठा t3c_data *t = T3C_DATA(tdev);
	काष्ठा l2t_data *d;

	हटाओ_adapter(adapter);
	अगर (list_empty(&adapter_list))
		unरेजिस्टर_netevent_notअगरier(&nb);

	मुक्त_tid_maps(&t->tid_maps);
	T3C_DATA(tdev) = शून्य;
	rcu_पढ़ो_lock();
	d = L2DATA(tdev);
	rcu_पढ़ो_unlock();
	RCU_INIT_POINTER(tdev->l2opt, शून्य);
	call_rcu(&d->rcu_head, clean_l2_data);
	kमुक्त_skb(t->nofail_skb);
	kमुक्त(t);
पूर्ण

अटल अंतरभूत व्योम रेजिस्टर_tdev(काष्ठा t3cdev *tdev)
अणु
	अटल पूर्णांक unit;

	mutex_lock(&cxgb3_db_lock);
	snम_लिखो(tdev->name, माप(tdev->name), "ofld_dev%d", unit++);
	list_add_tail(&tdev->ofld_dev_list, &ofld_dev_list);
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_tdev(काष्ठा t3cdev *tdev)
अणु
	mutex_lock(&cxgb3_db_lock);
	list_del(&tdev->ofld_dev_list);
	mutex_unlock(&cxgb3_db_lock);
पूर्ण

अटल अंतरभूत पूर्णांक adap2type(काष्ठा adapter *adapter)
अणु
	पूर्णांक type = 0;

	चयन (adapter->params.rev) अणु
	हाल T3_REV_A:
		type = T3A;
		अवरोध;
	हाल T3_REV_B:
	हाल T3_REV_B2:
		type = T3B;
		अवरोध;
	हाल T3_REV_C:
		type = T3C;
		अवरोध;
	पूर्ण
	वापस type;
पूर्ण

व्योम cxgb3_adapter_ofld(काष्ठा adapter *adapter)
अणु
	काष्ठा t3cdev *tdev = &adapter->tdev;

	INIT_LIST_HEAD(&tdev->ofld_dev_list);

	cxgb3_set_dummy_ops(tdev);
	tdev->send = t3_offload_tx;
	tdev->ctl = cxgb_offload_ctl;
	tdev->type = adap2type(adapter);

	रेजिस्टर_tdev(tdev);
पूर्ण

व्योम cxgb3_adapter_unofld(काष्ठा adapter *adapter)
अणु
	काष्ठा t3cdev *tdev = &adapter->tdev;

	tdev->recv = शून्य;
	tdev->neigh_update = शून्य;

	unरेजिस्टर_tdev(tdev);
पूर्ण

व्योम __init cxgb3_offload_init(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NUM_CPL_CMDS; ++i)
		cpl_handlers[i] = करो_bad_cpl;

	t3_रेजिस्टर_cpl_handler(CPL_SMT_WRITE_RPL, करो_smt_ग_लिखो_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_L2T_WRITE_RPL, करो_l2t_ग_लिखो_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_RTE_WRITE_RPL, करो_rte_ग_लिखो_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_PASS_OPEN_RPL, करो_stid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_CLOSE_LISTSRV_RPL, करो_stid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_PASS_ACCEPT_REQ, करो_cr);
	t3_रेजिस्टर_cpl_handler(CPL_PASS_ESTABLISH, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_ABORT_RPL_RSS, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_ABORT_RPL, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_RX_URG_NOTIFY, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_RX_DATA, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_TX_DATA_ACK, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_TX_DMA_ACK, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_ACT_OPEN_RPL, करो_act_खोलो_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_PEER_CLOSE, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_CLOSE_CON_RPL, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_ABORT_REQ_RSS, करो_पात_req_rss);
	t3_रेजिस्टर_cpl_handler(CPL_ACT_ESTABLISH, करो_act_establish);
	t3_रेजिस्टर_cpl_handler(CPL_SET_TCB_RPL, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_GET_TCB_RPL, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_RDMA_TERMINATE, करो_term);
	t3_रेजिस्टर_cpl_handler(CPL_RDMA_EC_STATUS, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_TRACE_PKT, करो_trace);
	t3_रेजिस्टर_cpl_handler(CPL_RX_DATA_DDP, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_RX_DDP_COMPLETE, करो_hwtid_rpl);
	t3_रेजिस्टर_cpl_handler(CPL_ISCSI_HDR, करो_hwtid_rpl);
पूर्ण
