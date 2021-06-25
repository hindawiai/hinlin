<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Admin Function driver
 *
 * Copyright (C) 2018 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>

#समावेश "rvu.h"
#समावेश "cgx.h"
#समावेश "lmac_common.h"
#समावेश "rvu_reg.h"
#समावेश "rvu_trace.h"

काष्ठा cgx_evq_entry अणु
	काष्ठा list_head evq_node;
	काष्ठा cgx_link_event link_event;
पूर्ण;

#घोषणा M(_name, _id, _fn_name, _req_type, _rsp_type)			\
अटल काष्ठा _req_type __maybe_unused					\
*otx2_mbox_alloc_msg_ ## _fn_name(काष्ठा rvu *rvu, पूर्णांक devid)		\
अणु									\
	काष्ठा _req_type *req;						\
									\
	req = (काष्ठा _req_type *)otx2_mbox_alloc_msg_rsp(		\
		&rvu->afpf_wq_info.mbox_up, devid, माप(काष्ठा _req_type), \
		माप(काष्ठा _rsp_type));				\
	अगर (!req)							\
		वापस शून्य;						\
	req->hdr.sig = OTX2_MBOX_REQ_SIG;				\
	req->hdr.id = _id;						\
	trace_otx2_msg_alloc(rvu->pdev, _id, माप(*req));		\
	वापस req;							\
पूर्ण

MBOX_UP_CGX_MESSAGES
#अघोषित M

bool is_mac_feature_supported(काष्ठा rvu *rvu, पूर्णांक pf, पूर्णांक feature)
अणु
	u8 cgx_id, lmac_id;
	व्योम *cgxd;

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस 0;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	cgxd = rvu_cgx_pdata(cgx_id, rvu);

	वापस  (cgx_features_get(cgxd) & feature);
पूर्ण

/* Returns biपंचांगap of mapped PFs */
अटल u16 cgxlmac_to_pfmap(काष्ठा rvu *rvu, u8 cgx_id, u8 lmac_id)
अणु
	वापस rvu->cgxlmac2pf_map[CGX_OFFSET(cgx_id) + lmac_id];
पूर्ण

अटल पूर्णांक cgxlmac_to_pf(काष्ठा rvu *rvu, पूर्णांक cgx_id, पूर्णांक lmac_id)
अणु
	अचिन्हित दीर्घ pfmap;

	pfmap = cgxlmac_to_pfmap(rvu, cgx_id, lmac_id);

	/* Assumes only one pf mapped to a cgx lmac port */
	अगर (!pfmap)
		वापस -ENODEV;
	अन्यथा
		वापस find_first_bit(&pfmap, 16);
पूर्ण

अटल u8 cgxlmac_id_to_bmap(u8 cgx_id, u8 lmac_id)
अणु
	वापस ((cgx_id & 0xF) << 4) | (lmac_id & 0xF);
पूर्ण

व्योम *rvu_cgx_pdata(u8 cgx_id, काष्ठा rvu *rvu)
अणु
	अगर (cgx_id >= rvu->cgx_cnt_max)
		वापस शून्य;

	वापस rvu->cgx_idmap[cgx_id];
पूर्ण

/* Return first enabled CGX instance अगर none are enabled then वापस शून्य */
व्योम *rvu_first_cgx_pdata(काष्ठा rvu *rvu)
अणु
	पूर्णांक first_enabled_cgx = 0;
	व्योम *cgxd = शून्य;

	क्रम (; first_enabled_cgx < rvu->cgx_cnt_max; first_enabled_cgx++) अणु
		cgxd = rvu_cgx_pdata(first_enabled_cgx, rvu);
		अगर (cgxd)
			अवरोध;
	पूर्ण

	वापस cgxd;
पूर्ण

/* Based on P2X connectivity find mapped NIX block क्रम a PF */
अटल व्योम rvu_map_cgx_nix_block(काष्ठा rvu *rvu, पूर्णांक pf,
				  पूर्णांक cgx_id, पूर्णांक lmac_id)
अणु
	काष्ठा rvu_pfvf *pfvf = &rvu->pf[pf];
	u8 p2x;

	p2x = cgx_lmac_get_p2x(cgx_id, lmac_id);
	/* Firmware sets P2X_SELECT as either NIX0 or NIX1 */
	pfvf->nix_blkaddr = BLKADDR_NIX0;
	अगर (p2x == CMR_P2X_SEL_NIX1)
		pfvf->nix_blkaddr = BLKADDR_NIX1;
पूर्ण

अटल पूर्णांक rvu_map_cgx_lmac_pf(काष्ठा rvu *rvu)
अणु
	काष्ठा npc_pkind *pkind = &rvu->hw->pkind;
	पूर्णांक cgx_cnt_max = rvu->cgx_cnt_max;
	पूर्णांक pf = PF_CGXMAP_BASE;
	अचिन्हित दीर्घ lmac_bmap;
	पूर्णांक size, मुक्त_pkind;
	पूर्णांक cgx, lmac, iter;

	अगर (!cgx_cnt_max)
		वापस 0;

	अगर (cgx_cnt_max > 0xF || MAX_LMAC_PER_CGX > 0xF)
		वापस -EINVAL;

	/* Alloc map table
	 * An additional entry is required since PF id starts from 1 and
	 * hence entry at offset 0 is invalid.
	 */
	size = (cgx_cnt_max * MAX_LMAC_PER_CGX + 1) * माप(u8);
	rvu->pf2cgxlmac_map = devm_kदो_स्मृति(rvu->dev, size, GFP_KERNEL);
	अगर (!rvu->pf2cgxlmac_map)
		वापस -ENOMEM;

	/* Initialize all entries with an invalid cgx and lmac id */
	स_रखो(rvu->pf2cgxlmac_map, 0xFF, size);

	/* Reverse map table */
	rvu->cgxlmac2pf_map = devm_kzalloc(rvu->dev,
				  cgx_cnt_max * MAX_LMAC_PER_CGX * माप(u16),
				  GFP_KERNEL);
	अगर (!rvu->cgxlmac2pf_map)
		वापस -ENOMEM;

	rvu->cgx_mapped_pfs = 0;
	क्रम (cgx = 0; cgx < cgx_cnt_max; cgx++) अणु
		अगर (!rvu_cgx_pdata(cgx, rvu))
			जारी;
		lmac_bmap = cgx_get_lmac_bmap(rvu_cgx_pdata(cgx, rvu));
		क्रम_each_set_bit(iter, &lmac_bmap, MAX_LMAC_PER_CGX) अणु
			lmac = cgx_get_lmacid(rvu_cgx_pdata(cgx, rvu),
					      iter);
			rvu->pf2cgxlmac_map[pf] = cgxlmac_id_to_bmap(cgx, lmac);
			rvu->cgxlmac2pf_map[CGX_OFFSET(cgx) + lmac] = 1 << pf;
			मुक्त_pkind = rvu_alloc_rsrc(&pkind->rsrc);
			pkind->pfchan_map[मुक्त_pkind] = ((pf) & 0x3F) << 16;
			rvu_map_cgx_nix_block(rvu, pf, cgx, lmac);
			rvu->cgx_mapped_pfs++;
			pf++;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rvu_cgx_send_link_info(पूर्णांक cgx_id, पूर्णांक lmac_id, काष्ठा rvu *rvu)
अणु
	काष्ठा cgx_evq_entry *qentry;
	अचिन्हित दीर्घ flags;
	पूर्णांक err;

	qentry = kदो_स्मृति(माप(*qentry), GFP_KERNEL);
	अगर (!qentry)
		वापस -ENOMEM;

	/* Lock the event queue beक्रमe we पढ़ो the local link status */
	spin_lock_irqsave(&rvu->cgx_evq_lock, flags);
	err = cgx_get_link_info(rvu_cgx_pdata(cgx_id, rvu), lmac_id,
				&qentry->link_event.link_uinfo);
	qentry->link_event.cgx_id = cgx_id;
	qentry->link_event.lmac_id = lmac_id;
	अगर (err) अणु
		kमुक्त(qentry);
		जाओ skip_add;
	पूर्ण
	list_add_tail(&qentry->evq_node, &rvu->cgx_evq_head);
skip_add:
	spin_unlock_irqrestore(&rvu->cgx_evq_lock, flags);

	/* start worker to process the events */
	queue_work(rvu->cgx_evh_wq, &rvu->cgx_evh_work);

	वापस 0;
पूर्ण

/* This is called from पूर्णांकerrupt context and is expected to be atomic */
अटल पूर्णांक cgx_lmac_postevent(काष्ठा cgx_link_event *event, व्योम *data)
अणु
	काष्ठा cgx_evq_entry *qentry;
	काष्ठा rvu *rvu = data;

	/* post event to the event queue */
	qentry = kदो_स्मृति(माप(*qentry), GFP_ATOMIC);
	अगर (!qentry)
		वापस -ENOMEM;
	qentry->link_event = *event;
	spin_lock(&rvu->cgx_evq_lock);
	list_add_tail(&qentry->evq_node, &rvu->cgx_evq_head);
	spin_unlock(&rvu->cgx_evq_lock);

	/* start worker to process the events */
	queue_work(rvu->cgx_evh_wq, &rvu->cgx_evh_work);

	वापस 0;
पूर्ण

अटल व्योम cgx_notअगरy_pfs(काष्ठा cgx_link_event *event, काष्ठा rvu *rvu)
अणु
	काष्ठा cgx_link_user_info *linfo;
	काष्ठा cgx_link_info_msg *msg;
	अचिन्हित दीर्घ pfmap;
	पूर्णांक err, pfid;

	linfo = &event->link_uinfo;
	pfmap = cgxlmac_to_pfmap(rvu, event->cgx_id, event->lmac_id);

	करो अणु
		pfid = find_first_bit(&pfmap, 16);
		clear_bit(pfid, &pfmap);

		/* check अगर notअगरication is enabled */
		अगर (!test_bit(pfid, &rvu->pf_notअगरy_bmap)) अणु
			dev_info(rvu->dev, "cgx %d: lmac %d Link status %s\n",
				 event->cgx_id, event->lmac_id,
				 linfo->link_up ? "UP" : "DOWN");
			जारी;
		पूर्ण

		/* Send mbox message to PF */
		msg = otx2_mbox_alloc_msg_cgx_link_event(rvu, pfid);
		अगर (!msg)
			जारी;
		msg->link_info = *linfo;
		otx2_mbox_msg_send(&rvu->afpf_wq_info.mbox_up, pfid);
		err = otx2_mbox_रुको_क्रम_rsp(&rvu->afpf_wq_info.mbox_up, pfid);
		अगर (err)
			dev_warn(rvu->dev, "notification to pf %d failed\n",
				 pfid);
	पूर्ण जबतक (pfmap);
पूर्ण

अटल व्योम cgx_evhandler_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rvu *rvu = container_of(work, काष्ठा rvu, cgx_evh_work);
	काष्ठा cgx_evq_entry *qentry;
	काष्ठा cgx_link_event *event;
	अचिन्हित दीर्घ flags;

	करो अणु
		/* Dequeue an event */
		spin_lock_irqsave(&rvu->cgx_evq_lock, flags);
		qentry = list_first_entry_or_null(&rvu->cgx_evq_head,
						  काष्ठा cgx_evq_entry,
						  evq_node);
		अगर (qentry)
			list_del(&qentry->evq_node);
		spin_unlock_irqrestore(&rvu->cgx_evq_lock, flags);
		अगर (!qentry)
			अवरोध; /* nothing more to process */

		event = &qentry->link_event;

		/* process event */
		cgx_notअगरy_pfs(event, rvu);
		kमुक्त(qentry);
	पूर्ण जबतक (1);
पूर्ण

अटल पूर्णांक cgx_lmac_event_handler_init(काष्ठा rvu *rvu)
अणु
	अचिन्हित दीर्घ lmac_bmap;
	काष्ठा cgx_event_cb cb;
	पूर्णांक cgx, lmac, err;
	व्योम *cgxd;

	spin_lock_init(&rvu->cgx_evq_lock);
	INIT_LIST_HEAD(&rvu->cgx_evq_head);
	INIT_WORK(&rvu->cgx_evh_work, cgx_evhandler_task);
	rvu->cgx_evh_wq = alloc_workqueue("rvu_evh_wq", 0, 0);
	अगर (!rvu->cgx_evh_wq) अणु
		dev_err(rvu->dev, "alloc workqueue failed");
		वापस -ENOMEM;
	पूर्ण

	cb.notअगरy_link_chg = cgx_lmac_postevent; /* link change call back */
	cb.data = rvu;

	क्रम (cgx = 0; cgx <= rvu->cgx_cnt_max; cgx++) अणु
		cgxd = rvu_cgx_pdata(cgx, rvu);
		अगर (!cgxd)
			जारी;
		lmac_bmap = cgx_get_lmac_bmap(cgxd);
		क्रम_each_set_bit(lmac, &lmac_bmap, MAX_LMAC_PER_CGX) अणु
			err = cgx_lmac_evh_रेजिस्टर(&cb, cgxd, lmac);
			अगर (err)
				dev_err(rvu->dev,
					"%d:%d handler register failed\n",
					cgx, lmac);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम rvu_cgx_wq_destroy(काष्ठा rvu *rvu)
अणु
	अगर (rvu->cgx_evh_wq) अणु
		flush_workqueue(rvu->cgx_evh_wq);
		destroy_workqueue(rvu->cgx_evh_wq);
		rvu->cgx_evh_wq = शून्य;
	पूर्ण
पूर्ण

पूर्णांक rvu_cgx_init(काष्ठा rvu *rvu)
अणु
	पूर्णांक cgx, err;
	व्योम *cgxd;

	/* CGX port id starts from 0 and are not necessarily contiguous
	 * Hence we allocate resources based on the maximum port id value.
	 */
	rvu->cgx_cnt_max = cgx_get_cgxcnt_max();
	अगर (!rvu->cgx_cnt_max) अणु
		dev_info(rvu->dev, "No CGX devices found!\n");
		वापस -ENODEV;
	पूर्ण

	rvu->cgx_idmap = devm_kzalloc(rvu->dev, rvu->cgx_cnt_max *
				      माप(व्योम *), GFP_KERNEL);
	अगर (!rvu->cgx_idmap)
		वापस -ENOMEM;

	/* Initialize the cgxdata table */
	क्रम (cgx = 0; cgx < rvu->cgx_cnt_max; cgx++)
		rvu->cgx_idmap[cgx] = cgx_get_pdata(cgx);

	/* Map CGX LMAC पूर्णांकerfaces to RVU PFs */
	err = rvu_map_cgx_lmac_pf(rvu);
	अगर (err)
		वापस err;

	/* Register क्रम CGX events */
	err = cgx_lmac_event_handler_init(rvu);
	अगर (err)
		वापस err;

	mutex_init(&rvu->cgx_cfg_lock);

	/* Ensure event handler registration is completed, beक्रमe
	 * we turn on the links
	 */
	mb();

	/* Do link up क्रम all CGX ports */
	क्रम (cgx = 0; cgx <= rvu->cgx_cnt_max; cgx++) अणु
		cgxd = rvu_cgx_pdata(cgx, rvu);
		अगर (!cgxd)
			जारी;
		err = cgx_lmac_linkup_start(cgxd);
		अगर (err)
			dev_err(rvu->dev,
				"Link up process failed to start on cgx %d\n",
				cgx);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rvu_cgx_निकास(काष्ठा rvu *rvu)
अणु
	अचिन्हित दीर्घ lmac_bmap;
	पूर्णांक cgx, lmac;
	व्योम *cgxd;

	क्रम (cgx = 0; cgx <= rvu->cgx_cnt_max; cgx++) अणु
		cgxd = rvu_cgx_pdata(cgx, rvu);
		अगर (!cgxd)
			जारी;
		lmac_bmap = cgx_get_lmac_bmap(cgxd);
		क्रम_each_set_bit(lmac, &lmac_bmap, MAX_LMAC_PER_CGX)
			cgx_lmac_evh_unरेजिस्टर(cgxd, lmac);
	पूर्ण

	/* Ensure event handler unरेजिस्टर is completed */
	mb();

	rvu_cgx_wq_destroy(rvu);
	वापस 0;
पूर्ण

/* Most of the CGX configuration is restricted to the mapped PF only,
 * VF's of mapped PF and other PFs are not allowed. This fn() checks
 * whether a PFFUNC is permitted to करो the config or not.
 */
अटल bool is_cgx_config_permitted(काष्ठा rvu *rvu, u16 pcअगरunc)
अणु
	अगर ((pcअगरunc & RVU_PFVF_FUNC_MASK) ||
	    !is_pf_cgxmapped(rvu, rvu_get_pf(pcअगरunc)))
		वापस false;
	वापस true;
पूर्ण

व्योम rvu_cgx_enadis_rx_bp(काष्ठा rvu *rvu, पूर्णांक pf, bool enable)
अणु
	काष्ठा mac_ops *mac_ops;
	u8 cgx_id, lmac_id;
	व्योम *cgxd;

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	cgxd = rvu_cgx_pdata(cgx_id, rvu);

	mac_ops = get_mac_ops(cgxd);
	/* Set / clear CTL_BCK to control छोड़ो frame क्रमwarding to NIX */
	अगर (enable)
		mac_ops->mac_enadis_rx_छोड़ो_fwding(cgxd, lmac_id, true);
	अन्यथा
		mac_ops->mac_enadis_rx_छोड़ो_fwding(cgxd, lmac_id, false);
पूर्ण

पूर्णांक rvu_cgx_config_rxtx(काष्ठा rvu *rvu, u16 pcअगरunc, bool start)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_cgx_config_permitted(rvu, pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	cgx_lmac_rx_tx_enable(rvu_cgx_pdata(cgx_id, rvu), lmac_id, start);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_start_rxtx(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				    काष्ठा msg_rsp *rsp)
अणु
	rvu_cgx_config_rxtx(rvu, req->hdr.pcअगरunc, true);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_stop_rxtx(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				   काष्ठा msg_rsp *rsp)
अणु
	rvu_cgx_config_rxtx(rvu, req->hdr.pcअगरunc, false);
	वापस 0;
पूर्ण

अटल पूर्णांक rvu_lmac_get_stats(काष्ठा rvu *rvu, काष्ठा msg_req *req,
			      व्योम *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	काष्ठा mac_ops *mac_ops;
	पूर्णांक stat = 0, err = 0;
	u64 tx_stat, rx_stat;
	u8 cgx_idx, lmac;
	व्योम *cgxd;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -ENODEV;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_idx, &lmac);
	cgxd = rvu_cgx_pdata(cgx_idx, rvu);
	mac_ops = get_mac_ops(cgxd);

	/* Rx stats */
	जबतक (stat < mac_ops->rx_stats_cnt) अणु
		err = mac_ops->mac_get_rx_stats(cgxd, lmac, stat, &rx_stat);
		अगर (err)
			वापस err;
		अगर (mac_ops->rx_stats_cnt == RPM_RX_STATS_COUNT)
			((काष्ठा rpm_stats_rsp *)rsp)->rx_stats[stat] = rx_stat;
		अन्यथा
			((काष्ठा cgx_stats_rsp *)rsp)->rx_stats[stat] = rx_stat;
		stat++;
	पूर्ण

	/* Tx stats */
	stat = 0;
	जबतक (stat < mac_ops->tx_stats_cnt) अणु
		err = mac_ops->mac_get_tx_stats(cgxd, lmac, stat, &tx_stat);
		अगर (err)
			वापस err;
		अगर (mac_ops->tx_stats_cnt == RPM_TX_STATS_COUNT)
			((काष्ठा rpm_stats_rsp *)rsp)->tx_stats[stat] = tx_stat;
		अन्यथा
			((काष्ठा cgx_stats_rsp *)rsp)->tx_stats[stat] = tx_stat;
		stat++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_stats(काष्ठा rvu *rvu, काष्ठा msg_req *req,
			       काष्ठा cgx_stats_rsp *rsp)
अणु
	वापस rvu_lmac_get_stats(rvu, req, (व्योम *)rsp);
पूर्ण

पूर्णांक rvu_mbox_handler_rpm_stats(काष्ठा rvu *rvu, काष्ठा msg_req *req,
			       काष्ठा rpm_stats_rsp *rsp)
अणु
	वापस rvu_lmac_get_stats(rvu, req, (व्योम *)rsp);
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_fec_stats(काष्ठा rvu *rvu,
				   काष्ठा msg_req *req,
				   काष्ठा cgx_fec_stats_rsp *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_idx, lmac;
	व्योम *cgxd;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -EPERM;
	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_idx, &lmac);

	cgxd = rvu_cgx_pdata(cgx_idx, rvu);
	वापस cgx_get_fec_stats(cgxd, lmac, rsp);
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_mac_addr_set(काष्ठा rvu *rvu,
				      काष्ठा cgx_mac_addr_set_or_get *req,
				      काष्ठा cgx_mac_addr_set_or_get *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	cgx_lmac_addr_set(cgx_id, lmac_id, req->mac_addr);

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_mac_addr_get(काष्ठा rvu *rvu,
				      काष्ठा cgx_mac_addr_set_or_get *req,
				      काष्ठा cgx_mac_addr_set_or_get *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_id, lmac_id;
	पूर्णांक rc = 0, i;
	u64 cfg;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	rsp->hdr.rc = rc;
	cfg = cgx_lmac_addr_get(cgx_id, lmac_id);
	/* copy 48 bit mac address to req->mac_addr */
	क्रम (i = 0; i < ETH_ALEN; i++)
		rsp->mac_addr[i] = cfg >> (ETH_ALEN - 1 - i) * 8;
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_promisc_enable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					काष्ठा msg_rsp *rsp)
अणु
	u16 pcअगरunc = req->hdr.pcअगरunc;
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	cgx_lmac_promisc_config(cgx_id, lmac_id, true);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_promisc_disable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					 काष्ठा msg_rsp *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	cgx_lmac_promisc_config(cgx_id, lmac_id, false);
	वापस 0;
पूर्ण

अटल पूर्णांक rvu_cgx_ptp_rx_cfg(काष्ठा rvu *rvu, u16 pcअगरunc, bool enable)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id, lmac_id;
	व्योम *cgxd;

	अगर (!is_mac_feature_supported(rvu, pf, RVU_LMAC_FEAT_PTP))
		वापस 0;

	/* This msg is expected only from PFs that are mapped to CGX LMACs,
	 * अगर received from other PF/VF simply ACK, nothing to करो.
	 */
	अगर ((pcअगरunc & RVU_PFVF_FUNC_MASK) ||
	    !is_pf_cgxmapped(rvu, pf))
		वापस -ENODEV;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	cgxd = rvu_cgx_pdata(cgx_id, rvu);

	cgx_lmac_ptp_config(cgxd, lmac_id, enable);
	/* If PTP is enabled then inक्रमm NPC that packets to be
	 * parsed by this PF will have their data shअगरted by 8 bytes
	 * and अगर PTP is disabled then no shअगरt is required
	 */
	अगर (npc_config_ts_kpuaction(rvu, pf, pcअगरunc, enable))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_ptp_rx_enable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				       काष्ठा msg_rsp *rsp)
अणु
	वापस rvu_cgx_ptp_rx_cfg(rvu, req->hdr.pcअगरunc, true);
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_ptp_rx_disable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					काष्ठा msg_rsp *rsp)
अणु
	वापस rvu_cgx_ptp_rx_cfg(rvu, req->hdr.pcअगरunc, false);
पूर्ण

अटल पूर्णांक rvu_cgx_config_linkevents(काष्ठा rvu *rvu, u16 pcअगरunc, bool en)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_cgx_config_permitted(rvu, pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	अगर (en) अणु
		set_bit(pf, &rvu->pf_notअगरy_bmap);
		/* Send the current link status to PF */
		rvu_cgx_send_link_info(cgx_id, lmac_id, rvu);
	पूर्ण अन्यथा अणु
		clear_bit(pf, &rvu->pf_notअगरy_bmap);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_start_linkevents(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					  काष्ठा msg_rsp *rsp)
अणु
	rvu_cgx_config_linkevents(rvu, req->hdr.pcअगरunc, true);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_stop_linkevents(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					 काष्ठा msg_rsp *rsp)
अणु
	rvu_cgx_config_linkevents(rvu, req->hdr.pcअगरunc, false);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_get_linkinfo(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				      काष्ठा cgx_link_info_msg *rsp)
अणु
	u8 cgx_id, lmac_id;
	पूर्णांक pf, err;

	pf = rvu_get_pf(req->hdr.pcअगरunc);

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस -ENODEV;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	err = cgx_get_link_info(rvu_cgx_pdata(cgx_id, rvu), lmac_id,
				&rsp->link_info);
	वापस err;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_features_get(काष्ठा rvu *rvu,
				      काष्ठा msg_req *req,
				      काष्ठा cgx_features_info_msg *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_idx, lmac;
	व्योम *cgxd;

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस 0;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_idx, &lmac);
	cgxd = rvu_cgx_pdata(cgx_idx, rvu);
	rsp->lmac_features = cgx_features_get(cgxd);

	वापस 0;
पूर्ण

u32 rvu_cgx_get_fअगरolen(काष्ठा rvu *rvu)
अणु
	काष्ठा mac_ops *mac_ops;
	u32 fअगरo_len;

	mac_ops = get_mac_ops(rvu_first_cgx_pdata(rvu));
	fअगरo_len = mac_ops ? mac_ops->fअगरo_len : 0;

	वापस fअगरo_len;
पूर्ण

अटल पूर्णांक rvu_cgx_config_पूर्णांकlbk(काष्ठा rvu *rvu, u16 pcअगरunc, bool en)
अणु
	पूर्णांक pf = rvu_get_pf(pcअगरunc);
	काष्ठा mac_ops *mac_ops;
	u8 cgx_id, lmac_id;

	अगर (!is_cgx_config_permitted(rvu, pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	mac_ops = get_mac_ops(rvu_cgx_pdata(cgx_id, rvu));

	वापस mac_ops->mac_lmac_पूर्णांकl_lbk(rvu_cgx_pdata(cgx_id, rvu),
					  lmac_id, en);
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_पूर्णांकlbk_enable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
				       काष्ठा msg_rsp *rsp)
अणु
	rvu_cgx_config_पूर्णांकlbk(rvu, req->hdr.pcअगरunc, true);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_पूर्णांकlbk_disable(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					काष्ठा msg_rsp *rsp)
अणु
	rvu_cgx_config_पूर्णांकlbk(rvu, req->hdr.pcअगरunc, false);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_cfg_छोड़ो_frm(काष्ठा rvu *rvu,
				       काष्ठा cgx_छोड़ो_frm_cfg *req,
				       काष्ठा cgx_छोड़ो_frm_cfg *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	काष्ठा mac_ops *mac_ops;
	u8 cgx_id, lmac_id;
	व्योम *cgxd;

	अगर (!is_mac_feature_supported(rvu, pf, RVU_LMAC_FEAT_FC))
		वापस 0;

	/* This msg is expected only from PF/VFs that are mapped to CGX LMACs,
	 * अगर received from other PF/VF simply ACK, nothing to करो.
	 */
	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस -ENODEV;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	cgxd = rvu_cgx_pdata(cgx_id, rvu);
	mac_ops = get_mac_ops(cgxd);

	अगर (req->set)
		mac_ops->mac_enadis_छोड़ो_frm(cgxd, lmac_id,
					      req->tx_छोड़ो, req->rx_छोड़ो);
	अन्यथा
		mac_ops->mac_get_छोड़ो_frm_status(cgxd, lmac_id,
						  &rsp->tx_छोड़ो,
						  &rsp->rx_छोड़ो);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_get_phy_fec_stats(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					   काष्ठा msg_rsp *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	वापस cgx_get_phy_fec_stats(rvu_cgx_pdata(cgx_id, rvu), lmac_id);
पूर्ण

/* Finds cumulative status of NIX rx/tx counters from LF of a PF and those
 * from its VFs as well. ie. NIX rx/tx counters at the CGX port level
 */
पूर्णांक rvu_cgx_nix_cuml_stats(काष्ठा rvu *rvu, व्योम *cgxd, पूर्णांक lmac_id,
			   पूर्णांक index, पूर्णांक rxtxflag, u64 *stat)
अणु
	काष्ठा rvu_block *block;
	पूर्णांक blkaddr;
	u16 pcअगरunc;
	पूर्णांक pf, lf;

	*stat = 0;

	अगर (!cgxd || !rvu)
		वापस -EINVAL;

	pf = cgxlmac_to_pf(rvu, cgx_get_cgxid(cgxd), lmac_id);
	अगर (pf < 0)
		वापस pf;

	/* Assumes LF of a PF and all of its VF beदीर्घs to the same
	 * NIX block
	 */
	pcअगरunc = pf << RVU_PFVF_PF_SHIFT;
	blkaddr = rvu_get_blkaddr(rvu, BLKTYPE_NIX, pcअगरunc);
	अगर (blkaddr < 0)
		वापस 0;
	block = &rvu->hw->block[blkaddr];

	क्रम (lf = 0; lf < block->lf.max; lf++) अणु
		/* Check अगर a lf is attached to this PF or one of its VFs */
		अगर (!((block->fn_map[lf] & ~RVU_PFVF_FUNC_MASK) == (pcअगरunc &
			 ~RVU_PFVF_FUNC_MASK)))
			जारी;
		अगर (rxtxflag == NIX_STATS_RX)
			*stat += rvu_पढ़ो64(rvu, blkaddr,
					    NIX_AF_LFX_RX_STATX(lf, index));
		अन्यथा
			*stat += rvu_पढ़ो64(rvu, blkaddr,
					    NIX_AF_LFX_TX_STATX(lf, index));
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक rvu_cgx_start_stop_io(काष्ठा rvu *rvu, u16 pcअगरunc, bool start)
अणु
	काष्ठा rvu_pfvf *parent_pf, *pfvf;
	पूर्णांक cgx_users, err = 0;

	अगर (!is_pf_cgxmapped(rvu, rvu_get_pf(pcअगरunc)))
		वापस 0;

	parent_pf = &rvu->pf[rvu_get_pf(pcअगरunc)];
	pfvf = rvu_get_pfvf(rvu, pcअगरunc);

	mutex_lock(&rvu->cgx_cfg_lock);

	अगर (start && pfvf->cgx_in_use)
		जाओ निकास;  /* CGX is alपढ़ोy started hence nothing to करो */
	अगर (!start && !pfvf->cgx_in_use)
		जाओ निकास; /* CGX is alपढ़ोy stopped hence nothing to करो */

	अगर (start) अणु
		cgx_users = parent_pf->cgx_users;
		parent_pf->cgx_users++;
	पूर्ण अन्यथा अणु
		parent_pf->cgx_users--;
		cgx_users = parent_pf->cgx_users;
	पूर्ण

	/* Start CGX when first of all NIXLFs is started.
	 * Stop CGX when last of all NIXLFs is stopped.
	 */
	अगर (!cgx_users) अणु
		err = rvu_cgx_config_rxtx(rvu, pcअगरunc & ~RVU_PFVF_FUNC_MASK,
					  start);
		अगर (err) अणु
			dev_err(rvu->dev, "Unable to %s CGX\n",
				start ? "start" : "stop");
			/* Revert the usage count in हाल of error */
			parent_pf->cgx_users = start ? parent_pf->cgx_users  - 1
					       : parent_pf->cgx_users  + 1;
			जाओ निकास;
		पूर्ण
	पूर्ण
	pfvf->cgx_in_use = start;
निकास:
	mutex_unlock(&rvu->cgx_cfg_lock);
	वापस err;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_set_fec_param(काष्ठा rvu *rvu,
				       काष्ठा fec_mode *req,
				       काष्ठा fec_mode *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस -EPERM;

	अगर (req->fec == OTX2_FEC_OFF)
		req->fec = OTX2_FEC_NONE;
	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);
	rsp->fec = cgx_set_fec(req->fec, cgx_id, lmac_id);
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_get_aux_link_info(काष्ठा rvu *rvu, काष्ठा msg_req *req,
					   काष्ठा cgx_fw_data *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_id, lmac_id;

	अगर (!rvu->fwdata)
		वापस -ENXIO;

	अगर (!is_pf_cgxmapped(rvu, pf))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_id, &lmac_id);

	स_नकल(&rsp->fwdata, &rvu->fwdata->cgx_fw_data[cgx_id][lmac_id],
	       माप(काष्ठा cgx_lmac_fwdata_s));
	वापस 0;
पूर्ण

पूर्णांक rvu_mbox_handler_cgx_set_link_mode(काष्ठा rvu *rvu,
				       काष्ठा cgx_set_link_mode_req *req,
				       काष्ठा cgx_set_link_mode_rsp *rsp)
अणु
	पूर्णांक pf = rvu_get_pf(req->hdr.pcअगरunc);
	u8 cgx_idx, lmac;
	व्योम *cgxd;

	अगर (!is_cgx_config_permitted(rvu, req->hdr.pcअगरunc))
		वापस -EPERM;

	rvu_get_cgx_lmac_id(rvu->pf2cgxlmac_map[pf], &cgx_idx, &lmac);
	cgxd = rvu_cgx_pdata(cgx_idx, rvu);
	rsp->status = cgx_set_link_mode(cgxd, req->args, cgx_idx, lmac);
	वापस 0;
पूर्ण
