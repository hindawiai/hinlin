<शैली गुरु>
/* Broadcom NetXtreme-C/E network driver.
 *
 * Copyright (c) 2016-2018 Broadcom Limited
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 */

#समावेश <linux/module.h>

#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/biपंचांगap.h>

#समावेश "bnxt_hsi.h"
#समावेश "bnxt.h"
#समावेश "bnxt_ulp.h"

अटल पूर्णांक bnxt_रेजिस्टर_dev(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id,
			     काष्ठा bnxt_ulp_ops *ulp_ops, व्योम *handle)
अणु
	काष्ठा net_device *dev = edev->net;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_ulp *ulp;

	ASSERT_RTNL();
	अगर (ulp_id >= BNXT_MAX_ULP)
		वापस -EINVAL;

	ulp = &edev->ulp_tbl[ulp_id];
	अगर (rcu_access_poपूर्णांकer(ulp->ulp_ops)) अणु
		netdev_err(bp->dev, "ulp id %d already registered\n", ulp_id);
		वापस -EBUSY;
	पूर्ण
	अगर (ulp_id == BNXT_ROCE_ULP) अणु
		अचिन्हित पूर्णांक max_stat_ctxs;

		max_stat_ctxs = bnxt_get_max_func_stat_ctxs(bp);
		अगर (max_stat_ctxs <= BNXT_MIN_ROCE_STAT_CTXS ||
		    bp->cp_nr_rings == max_stat_ctxs)
			वापस -ENOMEM;
	पूर्ण

	atomic_set(&ulp->ref_count, 0);
	ulp->handle = handle;
	rcu_assign_poपूर्णांकer(ulp->ulp_ops, ulp_ops);

	अगर (ulp_id == BNXT_ROCE_ULP) अणु
		अगर (test_bit(BNXT_STATE_OPEN, &bp->state))
			bnxt_hwrm_vnic_cfg(bp, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_unरेजिस्टर_dev(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id)
अणु
	काष्ठा net_device *dev = edev->net;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_ulp *ulp;
	पूर्णांक i = 0;

	ASSERT_RTNL();
	अगर (ulp_id >= BNXT_MAX_ULP)
		वापस -EINVAL;

	ulp = &edev->ulp_tbl[ulp_id];
	अगर (!rcu_access_poपूर्णांकer(ulp->ulp_ops)) अणु
		netdev_err(bp->dev, "ulp id %d not registered\n", ulp_id);
		वापस -EINVAL;
	पूर्ण
	अगर (ulp_id == BNXT_ROCE_ULP && ulp->msix_requested)
		edev->en_ops->bnxt_मुक्त_msix(edev, ulp_id);

	अगर (ulp->max_async_event_id)
		bnxt_hwrm_func_drv_rgtr(bp, शून्य, 0, true);

	RCU_INIT_POINTER(ulp->ulp_ops, शून्य);
	synchronize_rcu();
	ulp->max_async_event_id = 0;
	ulp->async_events_bmap = शून्य;
	जबतक (atomic_पढ़ो(&ulp->ref_count) != 0 && i < 10) अणु
		msleep(100);
		i++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnxt_fill_msix_vecs(काष्ठा bnxt *bp, काष्ठा bnxt_msix_entry *ent)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	पूर्णांक num_msix, idx, i;

	num_msix = edev->ulp_tbl[BNXT_ROCE_ULP].msix_requested;
	idx = edev->ulp_tbl[BNXT_ROCE_ULP].msix_base;
	क्रम (i = 0; i < num_msix; i++) अणु
		ent[i].vector = bp->irq_tbl[idx + i].vector;
		ent[i].ring_idx = idx + i;
		अगर (bp->flags & BNXT_FLAG_CHIP_P5) अणु
			ent[i].db_offset = DB_PF_OFFSET_P5;
			अगर (BNXT_VF(bp))
				ent[i].db_offset = DB_VF_OFFSET_P5;
		पूर्ण अन्यथा अणु
			ent[i].db_offset = (idx + i) * 0x80;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक bnxt_req_msix_vecs(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id,
			      काष्ठा bnxt_msix_entry *ent, पूर्णांक num_msix)
अणु
	काष्ठा net_device *dev = edev->net;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_hw_resc *hw_resc;
	पूर्णांक max_idx, max_cp_rings;
	पूर्णांक avail_msix, idx;
	पूर्णांक total_vecs;
	पूर्णांक rc = 0;

	ASSERT_RTNL();
	अगर (ulp_id != BNXT_ROCE_ULP)
		वापस -EINVAL;

	अगर (!(bp->flags & BNXT_FLAG_USING_MSIX))
		वापस -ENODEV;

	अगर (edev->ulp_tbl[ulp_id].msix_requested)
		वापस -EAGAIN;

	max_cp_rings = bnxt_get_max_func_cp_rings(bp);
	avail_msix = bnxt_get_avail_msix(bp, num_msix);
	अगर (!avail_msix)
		वापस -ENOMEM;
	अगर (avail_msix > num_msix)
		avail_msix = num_msix;

	अगर (BNXT_NEW_RM(bp)) अणु
		idx = bp->cp_nr_rings;
	पूर्ण अन्यथा अणु
		max_idx = min_t(पूर्णांक, bp->total_irqs, max_cp_rings);
		idx = max_idx - avail_msix;
	पूर्ण
	edev->ulp_tbl[ulp_id].msix_base = idx;
	edev->ulp_tbl[ulp_id].msix_requested = avail_msix;
	hw_resc = &bp->hw_resc;
	total_vecs = idx + avail_msix;
	अगर (bp->total_irqs < total_vecs ||
	    (BNXT_NEW_RM(bp) && hw_resc->resv_irqs < total_vecs)) अणु
		अगर (netअगर_running(dev)) अणु
			bnxt_बंद_nic(bp, true, false);
			rc = bnxt_खोलो_nic(bp, true, false);
		पूर्ण अन्यथा अणु
			rc = bnxt_reserve_rings(bp, true);
		पूर्ण
	पूर्ण
	अगर (rc) अणु
		edev->ulp_tbl[ulp_id].msix_requested = 0;
		वापस -EAGAIN;
	पूर्ण

	अगर (BNXT_NEW_RM(bp)) अणु
		पूर्णांक resv_msix;

		resv_msix = hw_resc->resv_irqs - bp->cp_nr_rings;
		avail_msix = min_t(पूर्णांक, resv_msix, avail_msix);
		edev->ulp_tbl[ulp_id].msix_requested = avail_msix;
	पूर्ण
	bnxt_fill_msix_vecs(bp, ent);
	edev->flags |= BNXT_EN_FLAG_MSIX_REQUESTED;
	वापस avail_msix;
पूर्ण

अटल पूर्णांक bnxt_मुक्त_msix_vecs(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id)
अणु
	काष्ठा net_device *dev = edev->net;
	काष्ठा bnxt *bp = netdev_priv(dev);

	ASSERT_RTNL();
	अगर (ulp_id != BNXT_ROCE_ULP)
		वापस -EINVAL;

	अगर (!(edev->flags & BNXT_EN_FLAG_MSIX_REQUESTED))
		वापस 0;

	edev->ulp_tbl[ulp_id].msix_requested = 0;
	edev->flags &= ~BNXT_EN_FLAG_MSIX_REQUESTED;
	अगर (netअगर_running(dev) && !(edev->flags & BNXT_EN_FLAG_ULP_STOPPED)) अणु
		bnxt_बंद_nic(bp, true, false);
		bnxt_खोलो_nic(bp, true, false);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bnxt_get_ulp_msix_num(काष्ठा bnxt *bp)
अणु
	अगर (bnxt_ulp_रेजिस्टरed(bp->edev, BNXT_ROCE_ULP)) अणु
		काष्ठा bnxt_en_dev *edev = bp->edev;

		वापस edev->ulp_tbl[BNXT_ROCE_ULP].msix_requested;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bnxt_get_ulp_msix_base(काष्ठा bnxt *bp)
अणु
	अगर (bnxt_ulp_रेजिस्टरed(bp->edev, BNXT_ROCE_ULP)) अणु
		काष्ठा bnxt_en_dev *edev = bp->edev;

		अगर (edev->ulp_tbl[BNXT_ROCE_ULP].msix_requested)
			वापस edev->ulp_tbl[BNXT_ROCE_ULP].msix_base;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bnxt_get_ulp_stat_ctxs(काष्ठा bnxt *bp)
अणु
	अगर (bnxt_ulp_रेजिस्टरed(bp->edev, BNXT_ROCE_ULP)) अणु
		काष्ठा bnxt_en_dev *edev = bp->edev;

		अगर (edev->ulp_tbl[BNXT_ROCE_ULP].msix_requested)
			वापस BNXT_MIN_ROCE_STAT_CTXS;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnxt_send_msg(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id,
			 काष्ठा bnxt_fw_msg *fw_msg)
अणु
	काष्ठा net_device *dev = edev->net;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा input *req;
	पूर्णांक rc;

	अगर (ulp_id != BNXT_ROCE_ULP && bp->fw_reset_state)
		वापस -EBUSY;

	mutex_lock(&bp->hwrm_cmd_lock);
	req = fw_msg->msg;
	req->resp_addr = cpu_to_le64(bp->hwrm_cmd_resp_dma_addr);
	rc = _hwrm_send_message(bp, fw_msg->msg, fw_msg->msg_len,
				fw_msg->समयout);
	अगर (!rc) अणु
		काष्ठा output *resp = bp->hwrm_cmd_resp_addr;
		u32 len = le16_to_cpu(resp->resp_len);

		अगर (fw_msg->resp_max_len < len)
			len = fw_msg->resp_max_len;

		स_नकल(fw_msg->resp, resp, len);
	पूर्ण
	mutex_unlock(&bp->hwrm_cmd_lock);
	वापस rc;
पूर्ण

अटल व्योम bnxt_ulp_get(काष्ठा bnxt_ulp *ulp)
अणु
	atomic_inc(&ulp->ref_count);
पूर्ण

अटल व्योम bnxt_ulp_put(काष्ठा bnxt_ulp *ulp)
अणु
	atomic_dec(&ulp->ref_count);
पूर्ण

व्योम bnxt_ulp_stop(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;
	पूर्णांक i;

	अगर (!edev)
		वापस;

	edev->flags |= BNXT_EN_FLAG_ULP_STOPPED;
	क्रम (i = 0; i < BNXT_MAX_ULP; i++) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[i];

		ops = rtnl_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_stop)
			जारी;
		ops->ulp_stop(ulp->handle);
	पूर्ण
पूर्ण

व्योम bnxt_ulp_start(काष्ठा bnxt *bp, पूर्णांक err)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;
	पूर्णांक i;

	अगर (!edev)
		वापस;

	edev->flags &= ~BNXT_EN_FLAG_ULP_STOPPED;

	अगर (err)
		वापस;

	क्रम (i = 0; i < BNXT_MAX_ULP; i++) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[i];

		ops = rtnl_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_start)
			जारी;
		ops->ulp_start(ulp->handle);
	पूर्ण
पूर्ण

व्योम bnxt_ulp_sriov_cfg(काष्ठा bnxt *bp, पूर्णांक num_vfs)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;
	पूर्णांक i;

	अगर (!edev)
		वापस;

	क्रम (i = 0; i < BNXT_MAX_ULP; i++) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[i];

		rcu_पढ़ो_lock();
		ops = rcu_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_sriov_config) अणु
			rcu_पढ़ो_unlock();
			जारी;
		पूर्ण
		bnxt_ulp_get(ulp);
		rcu_पढ़ो_unlock();
		ops->ulp_sriov_config(ulp->handle, num_vfs);
		bnxt_ulp_put(ulp);
	पूर्ण
पूर्ण

व्योम bnxt_ulp_shutकरोwn(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;
	पूर्णांक i;

	अगर (!edev)
		वापस;

	क्रम (i = 0; i < BNXT_MAX_ULP; i++) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[i];

		ops = rtnl_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_shutकरोwn)
			जारी;
		ops->ulp_shutकरोwn(ulp->handle);
	पूर्ण
पूर्ण

व्योम bnxt_ulp_irq_stop(काष्ठा bnxt *bp)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;

	अगर (!edev || !(edev->flags & BNXT_EN_FLAG_MSIX_REQUESTED))
		वापस;

	अगर (bnxt_ulp_रेजिस्टरed(bp->edev, BNXT_ROCE_ULP)) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[BNXT_ROCE_ULP];

		अगर (!ulp->msix_requested)
			वापस;

		ops = rtnl_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_irq_stop)
			वापस;
		ops->ulp_irq_stop(ulp->handle);
	पूर्ण
पूर्ण

व्योम bnxt_ulp_irq_restart(काष्ठा bnxt *bp, पूर्णांक err)
अणु
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;

	अगर (!edev || !(edev->flags & BNXT_EN_FLAG_MSIX_REQUESTED))
		वापस;

	अगर (bnxt_ulp_रेजिस्टरed(bp->edev, BNXT_ROCE_ULP)) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[BNXT_ROCE_ULP];
		काष्ठा bnxt_msix_entry *ent = शून्य;

		अगर (!ulp->msix_requested)
			वापस;

		ops = rtnl_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_irq_restart)
			वापस;

		अगर (!err) अणु
			ent = kसुस्मृति(ulp->msix_requested, माप(*ent),
				      GFP_KERNEL);
			अगर (!ent)
				वापस;
			bnxt_fill_msix_vecs(bp, ent);
		पूर्ण
		ops->ulp_irq_restart(ulp->handle, ent);
		kमुक्त(ent);
	पूर्ण
पूर्ण

व्योम bnxt_ulp_async_events(काष्ठा bnxt *bp, काष्ठा hwrm_async_event_cmpl *cmpl)
अणु
	u16 event_id = le16_to_cpu(cmpl->event_id);
	काष्ठा bnxt_en_dev *edev = bp->edev;
	काष्ठा bnxt_ulp_ops *ops;
	पूर्णांक i;

	अगर (!edev)
		वापस;

	rcu_पढ़ो_lock();
	क्रम (i = 0; i < BNXT_MAX_ULP; i++) अणु
		काष्ठा bnxt_ulp *ulp = &edev->ulp_tbl[i];

		ops = rcu_dereference(ulp->ulp_ops);
		अगर (!ops || !ops->ulp_async_notअगरier)
			जारी;
		अगर (!ulp->async_events_bmap ||
		    event_id > ulp->max_async_event_id)
			जारी;

		/* Read max_async_event_id first beक्रमe testing the biपंचांगap. */
		smp_rmb();
		अगर (test_bit(event_id, ulp->async_events_bmap))
			ops->ulp_async_notअगरier(ulp->handle, cmpl);
	पूर्ण
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक bnxt_रेजिस्टर_async_events(काष्ठा bnxt_en_dev *edev, पूर्णांक ulp_id,
				      अचिन्हित दीर्घ *events_bmap, u16 max_id)
अणु
	काष्ठा net_device *dev = edev->net;
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_ulp *ulp;

	अगर (ulp_id >= BNXT_MAX_ULP)
		वापस -EINVAL;

	ulp = &edev->ulp_tbl[ulp_id];
	ulp->async_events_bmap = events_bmap;
	/* Make sure bnxt_ulp_async_events() sees this order */
	smp_wmb();
	ulp->max_async_event_id = max_id;
	bnxt_hwrm_func_drv_rgtr(bp, events_bmap, max_id + 1, true);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा bnxt_en_ops bnxt_en_ops_tbl = अणु
	.bnxt_रेजिस्टर_device	= bnxt_रेजिस्टर_dev,
	.bnxt_unरेजिस्टर_device	= bnxt_unरेजिस्टर_dev,
	.bnxt_request_msix	= bnxt_req_msix_vecs,
	.bnxt_मुक्त_msix		= bnxt_मुक्त_msix_vecs,
	.bnxt_send_fw_msg	= bnxt_send_msg,
	.bnxt_रेजिस्टर_fw_async_events	= bnxt_रेजिस्टर_async_events,
पूर्ण;

काष्ठा bnxt_en_dev *bnxt_ulp_probe(काष्ठा net_device *dev)
अणु
	काष्ठा bnxt *bp = netdev_priv(dev);
	काष्ठा bnxt_en_dev *edev;

	edev = bp->edev;
	अगर (!edev) अणु
		edev = kzalloc(माप(*edev), GFP_KERNEL);
		अगर (!edev)
			वापस ERR_PTR(-ENOMEM);
		edev->en_ops = &bnxt_en_ops_tbl;
		अगर (bp->flags & BNXT_FLAG_ROCEV1_CAP)
			edev->flags |= BNXT_EN_FLAG_ROCEV1_CAP;
		अगर (bp->flags & BNXT_FLAG_ROCEV2_CAP)
			edev->flags |= BNXT_EN_FLAG_ROCEV2_CAP;
		edev->net = dev;
		edev->pdev = bp->pdev;
		edev->l2_db_size = bp->db_size;
		edev->l2_db_size_nc = bp->db_size;
		bp->edev = edev;
	पूर्ण
	वापस bp->edev;
पूर्ण
EXPORT_SYMBOL(bnxt_ulp_probe);
