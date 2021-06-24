<शैली गुरु>
/* bnx2fc_fcoe.c: QLogic Linux FCoE offload driver.
 * This file contains the code that पूर्णांकeracts with libfc, libfcoe,
 * cnic modules to create FCoE instances, send/receive non-offloaded
 * FIP/FCoE packets, listen to link events etc.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Bhanu Prakash Gollapudi (bprakash@broadcom.com)
 */

#समावेश "bnx2fc.h"

#समावेश <linux/ethtool.h>

अटल काष्ठा list_head adapter_list;
अटल काष्ठा list_head अगर_list;
अटल u32 adapter_count;
अटल DEFINE_MUTEX(bnx2fc_dev_lock);
DEFINE_PER_CPU(काष्ठा bnx2fc_percpu_s, bnx2fc_percpu);

#घोषणा DRV_MODULE_NAME		"bnx2fc"
#घोषणा DRV_MODULE_VERSION	BNX2FC_VERSION
#घोषणा DRV_MODULE_RELDATE	"October 15, 2015"


अटल अक्षर version[] =
		"QLogic FCoE Driver " DRV_MODULE_NAME \
		" v" DRV_MODULE_VERSION " (" DRV_MODULE_RELDATE ")\n";


MODULE_AUTHOR("Bhanu Prakash Gollapudi <bprakash@broadcom.com>");
MODULE_DESCRIPTION("QLogic FCoE Driver");
MODULE_LICENSE("GPL");
MODULE_VERSION(DRV_MODULE_VERSION);

#घोषणा BNX2FC_MAX_QUEUE_DEPTH	256
#घोषणा BNX2FC_MIN_QUEUE_DEPTH	32
#घोषणा FCOE_WORD_TO_BYTE  4

अटल काष्ठा scsi_transport_ढाँचा	*bnx2fc_transport_ढाँचा;
अटल काष्ठा scsi_transport_ढाँचा	*bnx2fc_vport_xport_ढाँचा;

काष्ठा workqueue_काष्ठा *bnx2fc_wq;

/* bnx2fc काष्ठाure needs only one instance of the fcoe_percpu_s काष्ठाure.
 * Here the io thपढ़ोs are per cpu but the l2 thपढ़ो is just one
 */
काष्ठा fcoe_percpu_s bnx2fc_global;
अटल DEFINE_SPINLOCK(bnx2fc_global_lock);

अटल काष्ठा cnic_ulp_ops bnx2fc_cnic_cb;
अटल काष्ठा libfc_function_ढाँचा bnx2fc_libfc_fcn_templ;
अटल काष्ठा scsi_host_ढाँचा bnx2fc_shost_ढाँचा;
अटल काष्ठा fc_function_ढाँचा bnx2fc_transport_function;
अटल काष्ठा fcoe_sysfs_function_ढाँचा bnx2fc_fcoe_sysfs_templ;
अटल काष्ठा fc_function_ढाँचा bnx2fc_vport_xport_function;
अटल पूर्णांक bnx2fc_create(काष्ठा net_device *netdev, क्रमागत fip_mode fip_mode);
अटल व्योम __bnx2fc_destroy(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक bnx2fc_destroy(काष्ठा net_device *net_device);
अटल पूर्णांक bnx2fc_enable(काष्ठा net_device *netdev);
अटल पूर्णांक bnx2fc_disable(काष्ठा net_device *netdev);

/* fcoe_syfs control पूर्णांकerface handlers */
अटल पूर्णांक bnx2fc_ctlr_alloc(काष्ठा net_device *netdev);
अटल पूर्णांक bnx2fc_ctlr_enabled(काष्ठा fcoe_ctlr_device *cdev);

अटल व्योम bnx2fc_recv_frame(काष्ठा sk_buff *skb);

अटल व्योम bnx2fc_start_disc(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक bnx2fc_shost_config(काष्ठा fc_lport *lport, काष्ठा device *dev);
अटल पूर्णांक bnx2fc_lport_config(काष्ठा fc_lport *lport);
अटल पूर्णांक bnx2fc_em_config(काष्ठा fc_lport *lport, काष्ठा bnx2fc_hba *hba);
अटल पूर्णांक bnx2fc_bind_adapter_devices(काष्ठा bnx2fc_hba *hba);
अटल व्योम bnx2fc_unbind_adapter_devices(काष्ठा bnx2fc_hba *hba);
अटल पूर्णांक bnx2fc_bind_pcidev(काष्ठा bnx2fc_hba *hba);
अटल व्योम bnx2fc_unbind_pcidev(काष्ठा bnx2fc_hba *hba);
अटल काष्ठा fc_lport *bnx2fc_अगर_create(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface,
				  काष्ठा device *parent, पूर्णांक npiv);
अटल व्योम bnx2fc_destroy_work(काष्ठा work_काष्ठा *work);

अटल काष्ठा bnx2fc_hba *bnx2fc_hba_lookup(काष्ठा net_device *phys_dev);
अटल काष्ठा bnx2fc_पूर्णांकerface *bnx2fc_पूर्णांकerface_lookup(काष्ठा net_device
							*phys_dev);
अटल अंतरभूत व्योम bnx2fc_पूर्णांकerface_put(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface);
अटल काष्ठा bnx2fc_hba *bnx2fc_find_hba_क्रम_cnic(काष्ठा cnic_dev *cnic);

अटल पूर्णांक bnx2fc_fw_init(काष्ठा bnx2fc_hba *hba);
अटल व्योम bnx2fc_fw_destroy(काष्ठा bnx2fc_hba *hba);

अटल व्योम bnx2fc_port_shutकरोwn(काष्ठा fc_lport *lport);
अटल व्योम bnx2fc_stop(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface);
अटल पूर्णांक __init bnx2fc_mod_init(व्योम);
अटल व्योम __निकास bnx2fc_mod_निकास(व्योम);

अचिन्हित पूर्णांक bnx2fc_debug_level;
module_param_named(debug_logging, bnx2fc_debug_level, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug_logging,
		"Option to enable extended logging,\n"
		"\t\tDefault is 0 - no logging.\n"
		"\t\t0x01 - SCSI cmd error, cleanup.\n"
		"\t\t0x02 - Session setup, cleanup, etc.\n"
		"\t\t0x04 - lport events, link, mtu, etc.\n"
		"\t\t0x08 - ELS logs.\n"
		"\t\t0x10 - fcoe L2 fame related logs.\n"
		"\t\t0xff - LOG all messages.");

अटल uपूर्णांक bnx2fc_devloss_पंचांगo;
module_param_named(devloss_पंचांगo, bnx2fc_devloss_पंचांगo, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(devloss_पंचांगo, " Change devloss_tmo for the remote ports "
	"attached via bnx2fc.");

अटल uपूर्णांक bnx2fc_max_luns = BNX2FC_MAX_LUN;
module_param_named(max_luns, bnx2fc_max_luns, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_luns, " Change the default max_lun per SCSI host. Default "
	"0xffff.");

अटल uपूर्णांक bnx2fc_queue_depth;
module_param_named(queue_depth, bnx2fc_queue_depth, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(queue_depth, " Change the default queue depth of SCSI devices "
	"attached via bnx2fc.");

अटल uपूर्णांक bnx2fc_log_fka;
module_param_named(log_fka, bnx2fc_log_fka, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(log_fka, " Print message to kernel log when fcoe is "
	"initiating a FIP keep alive when debug logging is enabled.");

अटल अंतरभूत काष्ठा net_device *bnx2fc_netdev(स्थिर काष्ठा fc_lport *lport)
अणु
	वापस ((काष्ठा bnx2fc_पूर्णांकerface *)
		((काष्ठा fcoe_port *)lport_priv(lport))->priv)->netdev;
पूर्ण

अटल व्योम bnx2fc_fcf_get_vlan_id(काष्ठा fcoe_fcf_device *fcf_dev)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev =
		fcoe_fcf_dev_to_ctlr_dev(fcf_dev);
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	काष्ठा bnx2fc_पूर्णांकerface *fcoe = fcoe_ctlr_priv(ctlr);

	fcf_dev->vlan_id = fcoe->vlan_id;
पूर्ण

अटल व्योम bnx2fc_clean_rx_queue(काष्ठा fc_lport *lp)
अणु
	काष्ठा fcoe_percpu_s *bg;
	काष्ठा fcoe_rcv_info *fr;
	काष्ठा sk_buff_head *list;
	काष्ठा sk_buff *skb, *next;

	bg = &bnx2fc_global;
	spin_lock_bh(&bg->fcoe_rx_list.lock);
	list = &bg->fcoe_rx_list;
	skb_queue_walk_safe(list, skb, next) अणु
		fr = fcoe_dev_from_skb(skb);
		अगर (fr->fr_dev == lp) अणु
			__skb_unlink(skb, list);
			kमुक्त_skb(skb);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&bg->fcoe_rx_list.lock);
पूर्ण

पूर्णांक bnx2fc_get_paged_crc_eof(काष्ठा sk_buff *skb, पूर्णांक tlen)
अणु
	पूर्णांक rc;
	spin_lock(&bnx2fc_global_lock);
	rc = fcoe_get_paged_crc_eof(skb, tlen, &bnx2fc_global);
	spin_unlock(&bnx2fc_global_lock);

	वापस rc;
पूर्ण

अटल व्योम bnx2fc_पात_io(काष्ठा fc_lport *lport)
अणु
	/*
	 * This function is no-op क्रम bnx2fc, but we करो
	 * not want to leave it as शून्य either, as libfc
	 * can call the शेष function which is
	 * fc_fcp_पात_io.
	 */
पूर्ण

अटल व्योम bnx2fc_cleanup(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा bnx2fc_rport *tgt;
	पूर्णांक i;

	BNX2FC_MISC_DBG("Entered %s\n", __func__);
	mutex_lock(&hba->hba_mutex);
	spin_lock_bh(&hba->hba_lock);
	क्रम (i = 0; i < BNX2FC_NUM_MAX_SESS; i++) अणु
		tgt = hba->tgt_ofld_list[i];
		अगर (tgt) अणु
			/* Cleanup IOs beदीर्घing to requested vport */
			अगर (tgt->port == port) अणु
				spin_unlock_bh(&hba->hba_lock);
				BNX2FC_TGT_DBG(tgt, "flush/cleanup\n");
				bnx2fc_flush_active_ios(tgt);
				spin_lock_bh(&hba->hba_lock);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hba->hba_lock);
	mutex_unlock(&hba->hba_mutex);
पूर्ण

अटल पूर्णांक bnx2fc_xmit_l2_frame(काष्ठा bnx2fc_rport *tgt,
			     काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_rport_priv *rdata = tgt->rdata;
	काष्ठा fc_frame_header *fh;
	पूर्णांक rc = 0;

	fh = fc_frame_header_get(fp);
	BNX2FC_TGT_DBG(tgt, "Xmit L2 frame rport = 0x%x, oxid = 0x%x, "
			"r_ctl = 0x%x\n", rdata->ids.port_id,
			ntohs(fh->fh_ox_id), fh->fh_r_ctl);
	अगर ((fh->fh_type == FC_TYPE_ELS) &&
	    (fh->fh_r_ctl == FC_RCTL_ELS_REQ)) अणु

		चयन (fc_frame_payload_op(fp)) अणु
		हाल ELS_ADISC:
			rc = bnx2fc_send_adisc(tgt, fp);
			अवरोध;
		हाल ELS_LOGO:
			rc = bnx2fc_send_logo(tgt, fp);
			अवरोध;
		हाल ELS_RLS:
			rc = bnx2fc_send_rls(tgt, fp);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर ((fh->fh_type ==  FC_TYPE_BLS) &&
	    (fh->fh_r_ctl == FC_RCTL_BA_ABTS))
		BNX2FC_TGT_DBG(tgt, "ABTS frame\n");
	अन्यथा अणु
		BNX2FC_TGT_DBG(tgt, "Send L2 frame type 0x%x "
				"rctl 0x%x thru non-offload path\n",
				fh->fh_type, fh->fh_r_ctl);
		वापस -ENODEV;
	पूर्ण
	अगर (rc)
		वापस -ENOMEM;
	अन्यथा
		वापस 0;
पूर्ण

/**
 * bnx2fc_xmit - bnx2fc's FCoE frame transmit function
 *
 * @lport:	the associated local port
 * @fp:	the fc_frame to be transmitted
 */
अटल पूर्णांक bnx2fc_xmit(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा ethhdr		*eh;
	काष्ठा fcoe_crc_eof	*cp;
	काष्ठा sk_buff		*skb;
	काष्ठा fc_frame_header	*fh;
	काष्ठा bnx2fc_पूर्णांकerface	*पूर्णांकerface;
	काष्ठा fcoe_ctlr        *ctlr;
	काष्ठा bnx2fc_hba *hba;
	काष्ठा fcoe_port	*port;
	काष्ठा fcoe_hdr		*hp;
	काष्ठा bnx2fc_rport	*tgt;
	काष्ठा fc_stats		*stats;
	u8			sof, eof;
	u32			crc;
	अचिन्हित पूर्णांक		hlen, tlen, elen;
	पूर्णांक			wlen, rc = 0;

	port = (काष्ठा fcoe_port *)lport_priv(lport);
	पूर्णांकerface = port->priv;
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	hba = पूर्णांकerface->hba;

	fh = fc_frame_header_get(fp);

	skb = fp_skb(fp);
	अगर (!lport->link_up) अणु
		BNX2FC_HBA_DBG(lport, "bnx2fc_xmit link down\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (unlikely(fh->fh_r_ctl == FC_RCTL_ELS_REQ)) अणु
		अगर (!ctlr->sel_fcf) अणु
			BNX2FC_HBA_DBG(lport, "FCF not selected yet!\n");
			kमुक्त_skb(skb);
			वापस -EINVAL;
		पूर्ण
		अगर (fcoe_ctlr_els_send(ctlr, lport, skb))
			वापस 0;
	पूर्ण

	sof = fr_sof(fp);
	eof = fr_eof(fp);

	/*
	 * Snoop the frame header to check अगर the frame is क्रम
	 * an offloaded session
	 */
	/*
	 * tgt_ofld_list access is synchronized using
	 * both hba mutex and hba lock. Atleast hba mutex or
	 * hba lock needs to be held क्रम पढ़ो access.
	 */

	spin_lock_bh(&hba->hba_lock);
	tgt = bnx2fc_tgt_lookup(port, ntoh24(fh->fh_d_id));
	अगर (tgt && (test_bit(BNX2FC_FLAG_SESSION_READY, &tgt->flags))) अणु
		/* This frame is क्रम offloaded session */
		BNX2FC_HBA_DBG(lport, "xmit: Frame is for offloaded session "
				"port_id = 0x%x\n", ntoh24(fh->fh_d_id));
		spin_unlock_bh(&hba->hba_lock);
		rc = bnx2fc_xmit_l2_frame(tgt, fp);
		अगर (rc != -ENODEV) अणु
			kमुक्त_skb(skb);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock_bh(&hba->hba_lock);
	पूर्ण

	elen = माप(काष्ठा ethhdr);
	hlen = माप(काष्ठा fcoe_hdr);
	tlen = माप(काष्ठा fcoe_crc_eof);
	wlen = (skb->len - tlen + माप(crc)) / FCOE_WORD_TO_BYTE;

	skb->ip_summed = CHECKSUM_NONE;
	crc = fcoe_fc_crc(fp);

	/* copy port crc and eof to the skb buff */
	अगर (skb_is_nonlinear(skb)) अणु
		skb_frag_t *frag;
		अगर (bnx2fc_get_paged_crc_eof(skb, tlen)) अणु
			kमुक्त_skb(skb);
			वापस -ENOMEM;
		पूर्ण
		frag = &skb_shinfo(skb)->frags[skb_shinfo(skb)->nr_frags - 1];
		cp = kmap_atomic(skb_frag_page(frag)) + skb_frag_off(frag);
	पूर्ण अन्यथा अणु
		cp = skb_put(skb, tlen);
	पूर्ण

	स_रखो(cp, 0, माप(*cp));
	cp->fcoe_eof = eof;
	cp->fcoe_crc32 = cpu_to_le32(~crc);
	अगर (skb_is_nonlinear(skb)) अणु
		kunmap_atomic(cp);
		cp = शून्य;
	पूर्ण

	/* adjust skb network/transport offsets to match mac/fcoe/port */
	skb_push(skb, elen + hlen);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	skb->mac_len = elen;
	skb->protocol = htons(ETH_P_FCOE);
	skb->dev = पूर्णांकerface->netdev;

	/* fill up mac and fcoe headers */
	eh = eth_hdr(skb);
	eh->h_proto = htons(ETH_P_FCOE);
	अगर (ctlr->map_dest)
		fc_fcoe_set_mac(eh->h_dest, fh->fh_d_id);
	अन्यथा
		/* insert GW address */
		स_नकल(eh->h_dest, ctlr->dest_addr, ETH_ALEN);

	अगर (unlikely(ctlr->flogi_oxid != FC_XID_UNKNOWN))
		स_नकल(eh->h_source, ctlr->ctl_src_addr, ETH_ALEN);
	अन्यथा
		स_नकल(eh->h_source, port->data_src_addr, ETH_ALEN);

	hp = (काष्ठा fcoe_hdr *)(eh + 1);
	स_रखो(hp, 0, माप(*hp));
	अगर (FC_FCOE_VER)
		FC_FCOE_ENCAPS_VER(hp, FC_FCOE_VER);
	hp->fcoe_sof = sof;

	/* fcoe lso, mss is in max_payload which is non-zero क्रम FCP data */
	अगर (lport->seq_offload && fr_max_payload(fp)) अणु
		skb_shinfo(skb)->gso_type = SKB_GSO_FCOE;
		skb_shinfo(skb)->gso_size = fr_max_payload(fp);
	पूर्ण अन्यथा अणु
		skb_shinfo(skb)->gso_type = 0;
		skb_shinfo(skb)->gso_size = 0;
	पूर्ण

	/*update tx stats */
	stats = per_cpu_ptr(lport->stats, get_cpu());
	stats->TxFrames++;
	stats->TxWords += wlen;
	put_cpu();

	/* send करोwn to lld */
	fr_dev(fp) = lport;
	अगर (port->fcoe_pending_queue.qlen)
		fcoe_check_रुको_queue(lport, skb);
	अन्यथा अगर (fcoe_start_io(skb))
		fcoe_check_रुको_queue(lport, skb);

	वापस 0;
पूर्ण

/**
 * bnx2fc_rcv - This is bnx2fc's receive function called by NET_RX_SOFTIRQ
 *
 * @skb:	the receive socket buffer
 * @dev:	associated net device
 * @ptype:	context
 * @olddev:	last device
 *
 * This function receives the packet and builds FC frame and passes it up
 */
अटल पूर्णांक bnx2fc_rcv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		काष्ठा packet_type *ptype, काष्ठा net_device *olddev)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_rcv_info *fr;
	काष्ठा fcoe_percpu_s *bg;
	काष्ठा sk_buff *पंचांगp_skb;

	पूर्णांकerface = container_of(ptype, काष्ठा bnx2fc_पूर्णांकerface,
				 fcoe_packet_type);
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	lport = ctlr->lp;

	अगर (unlikely(lport == शून्य)) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_rcv: lport is NULL\n");
		जाओ err;
	पूर्ण

	पंचांगp_skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!पंचांगp_skb)
		जाओ err;

	skb = पंचांगp_skb;

	अगर (unlikely(eth_hdr(skb)->h_proto != htons(ETH_P_FCOE))) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_rcv: Wrong FC type frame\n");
		जाओ err;
	पूर्ण

	/*
	 * Check क्रम minimum frame length, and make sure required FCoE
	 * and FC headers are pulled पूर्णांकo the linear data area.
	 */
	अगर (unlikely((skb->len < FCOE_MIN_FRAME) ||
	    !pskb_may_pull(skb, FCOE_HEADER_LEN)))
		जाओ err;

	skb_set_transport_header(skb, माप(काष्ठा fcoe_hdr));

	fr = fcoe_dev_from_skb(skb);
	fr->fr_dev = lport;

	bg = &bnx2fc_global;
	spin_lock(&bg->fcoe_rx_list.lock);

	__skb_queue_tail(&bg->fcoe_rx_list, skb);
	अगर (bg->fcoe_rx_list.qlen == 1)
		wake_up_process(bg->kthपढ़ो);

	spin_unlock(&bg->fcoe_rx_list.lock);

	वापस 0;
err:
	kमुक्त_skb(skb);
	वापस -1;
पूर्ण

अटल पूर्णांक bnx2fc_l2_rcv_thपढ़ो(व्योम *arg)
अणु
	काष्ठा fcoe_percpu_s *bg = arg;
	काष्ठा sk_buff *skb;

	set_user_nice(current, MIN_NICE);
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();
		spin_lock_bh(&bg->fcoe_rx_list.lock);
		जबतक ((skb = __skb_dequeue(&bg->fcoe_rx_list)) != शून्य) अणु
			spin_unlock_bh(&bg->fcoe_rx_list.lock);
			bnx2fc_recv_frame(skb);
			spin_lock_bh(&bg->fcoe_rx_list.lock);
		पूर्ण
		__set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_bh(&bg->fcoe_rx_list.lock);
	पूर्ण
	__set_current_state(TASK_RUNNING);
	वापस 0;
पूर्ण


अटल व्योम bnx2fc_recv_frame(काष्ठा sk_buff *skb)
अणु
	u32 fr_len;
	काष्ठा fc_lport *lport;
	काष्ठा fcoe_rcv_info *fr;
	काष्ठा fc_stats *stats;
	काष्ठा fc_frame_header *fh;
	काष्ठा fcoe_crc_eof crc_eof;
	काष्ठा fc_frame *fp;
	काष्ठा fc_lport *vn_port;
	काष्ठा fcoe_port *port, *phys_port;
	u8 *mac = शून्य;
	u8 *dest_mac = शून्य;
	काष्ठा fcoe_hdr *hp;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;

	fr = fcoe_dev_from_skb(skb);
	lport = fr->fr_dev;
	अगर (unlikely(lport == शून्य)) अणु
		prपूर्णांकk(KERN_ERR PFX "Invalid lport struct\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (skb_is_nonlinear(skb))
		skb_linearize(skb);
	mac = eth_hdr(skb)->h_source;
	dest_mac = eth_hdr(skb)->h_dest;

	/* Pull the header */
	hp = (काष्ठा fcoe_hdr *) skb_network_header(skb);
	fh = (काष्ठा fc_frame_header *) skb_transport_header(skb);
	skb_pull(skb, माप(काष्ठा fcoe_hdr));
	fr_len = skb->len - माप(काष्ठा fcoe_crc_eof);

	fp = (काष्ठा fc_frame *)skb;
	fc_frame_init(fp);
	fr_dev(fp) = lport;
	fr_sof(fp) = hp->fcoe_sof;
	अगर (skb_copy_bits(skb, fr_len, &crc_eof, माप(crc_eof))) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	fr_eof(fp) = crc_eof.fcoe_eof;
	fr_crc(fp) = crc_eof.fcoe_crc32;
	अगर (pskb_trim(skb, fr_len)) अणु
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	phys_port = lport_priv(lport);
	पूर्णांकerface = phys_port->priv;
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);

	fh = fc_frame_header_get(fp);

	अगर (ntoh24(&dest_mac[3]) != ntoh24(fh->fh_d_id)) अणु
		BNX2FC_HBA_DBG(lport, "FC frame d_id mismatch with MAC %pM.\n",
		    dest_mac);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	vn_port = fc_vport_id_lookup(lport, ntoh24(fh->fh_d_id));
	अगर (vn_port) अणु
		port = lport_priv(vn_port);
		अगर (!ether_addr_equal(port->data_src_addr, dest_mac)) अणु
			BNX2FC_HBA_DBG(lport, "fpma mismatch\n");
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण
	अगर (ctlr->state) अणु
		अगर (!ether_addr_equal(mac, ctlr->dest_addr)) अणु
			BNX2FC_HBA_DBG(lport, "Wrong source address: mac:%pM dest_addr:%pM.\n",
			    mac, ctlr->dest_addr);
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण
	अगर (fh->fh_r_ctl == FC_RCTL_DD_SOL_DATA &&
	    fh->fh_type == FC_TYPE_FCP) अणु
		/* Drop FCP data. We करोnt this in L2 path */
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	अगर (fh->fh_r_ctl == FC_RCTL_ELS_REQ &&
	    fh->fh_type == FC_TYPE_ELS) अणु
		चयन (fc_frame_payload_op(fp)) अणु
		हाल ELS_LOGO:
			अगर (ntoh24(fh->fh_s_id) == FC_FID_FLOGI) अणु
				/* drop non-FIP LOGO */
				kमुक्त_skb(skb);
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (fh->fh_r_ctl == FC_RCTL_BA_ABTS) अणु
		/* Drop incoming ABTS */
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/*
	 * If the destination ID from the frame header करोes not match what we
	 * have on record क्रम lport and the search क्रम a NPIV port came up
	 * empty then this is not addressed to our port so simply drop it.
	 */
	अगर (lport->port_id != ntoh24(fh->fh_d_id) && !vn_port) अणु
		BNX2FC_HBA_DBG(lport, "Dropping frame due to destination mismatch: lport->port_id=%x fh->d_id=%x.\n",
		    lport->port_id, ntoh24(fh->fh_d_id));
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	stats = per_cpu_ptr(lport->stats, smp_processor_id());
	stats->RxFrames++;
	stats->RxWords += fr_len / FCOE_WORD_TO_BYTE;

	अगर (le32_to_cpu(fr_crc(fp)) !=
			~crc32(~0, skb->data, fr_len)) अणु
		अगर (stats->InvalidCRCCount < 5)
			prपूर्णांकk(KERN_WARNING PFX "dropping frame with "
			       "CRC error\n");
		stats->InvalidCRCCount++;
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	fc_exch_recv(lport, fp);
पूर्ण

/**
 * bnx2fc_percpu_io_thपढ़ो - thपढ़ो per cpu क्रम ios
 *
 * @arg:	ptr to bnx2fc_percpu_info काष्ठाure
 */
अटल पूर्णांक bnx2fc_percpu_io_thपढ़ो(व्योम *arg)
अणु
	काष्ठा bnx2fc_percpu_s *p = arg;
	काष्ठा bnx2fc_work *work, *पंचांगp;
	LIST_HEAD(work_list);

	set_user_nice(current, MIN_NICE);
	set_current_state(TASK_INTERRUPTIBLE);
	जबतक (!kthपढ़ो_should_stop()) अणु
		schedule();
		spin_lock_bh(&p->fp_work_lock);
		जबतक (!list_empty(&p->work_list)) अणु
			list_splice_init(&p->work_list, &work_list);
			spin_unlock_bh(&p->fp_work_lock);

			list_क्रम_each_entry_safe(work, पंचांगp, &work_list, list) अणु
				list_del_init(&work->list);
				bnx2fc_process_cq_compl(work->tgt, work->wqe,
							work->rq_data,
							work->num_rq,
							work->task);
				kमुक्त(work);
			पूर्ण

			spin_lock_bh(&p->fp_work_lock);
		पूर्ण
		__set_current_state(TASK_INTERRUPTIBLE);
		spin_unlock_bh(&p->fp_work_lock);
	पूर्ण
	__set_current_state(TASK_RUNNING);

	वापस 0;
पूर्ण

अटल काष्ठा fc_host_statistics *bnx2fc_get_host_stats(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_host_statistics *bnx2fc_stats;
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा fcoe_statistics_params *fw_stats;
	पूर्णांक rc = 0;

	fw_stats = (काष्ठा fcoe_statistics_params *)hba->stats_buffer;
	अगर (!fw_stats)
		वापस शून्य;

	mutex_lock(&hba->hba_stats_mutex);

	bnx2fc_stats = fc_get_host_stats(shost);

	init_completion(&hba->stat_req_करोne);
	अगर (bnx2fc_send_stat_req(hba))
		जाओ unlock_stats_mutex;
	rc = रुको_क्रम_completion_समयout(&hba->stat_req_करोne, (2 * HZ));
	अगर (!rc) अणु
		BNX2FC_HBA_DBG(lport, "FW stat req timed out\n");
		जाओ unlock_stats_mutex;
	पूर्ण
	BNX2FC_STATS(hba, rx_stat2, fc_crc_cnt);
	bnx2fc_stats->invalid_crc_count += hba->bfw_stats.fc_crc_cnt;
	BNX2FC_STATS(hba, tx_stat, fcoe_tx_pkt_cnt);
	bnx2fc_stats->tx_frames += hba->bfw_stats.fcoe_tx_pkt_cnt;
	BNX2FC_STATS(hba, tx_stat, fcoe_tx_byte_cnt);
	bnx2fc_stats->tx_words += ((hba->bfw_stats.fcoe_tx_byte_cnt) / 4);
	BNX2FC_STATS(hba, rx_stat0, fcoe_rx_pkt_cnt);
	bnx2fc_stats->rx_frames += hba->bfw_stats.fcoe_rx_pkt_cnt;
	BNX2FC_STATS(hba, rx_stat0, fcoe_rx_byte_cnt);
	bnx2fc_stats->rx_words += ((hba->bfw_stats.fcoe_rx_byte_cnt) / 4);

	bnx2fc_stats->dumped_frames = 0;
	bnx2fc_stats->lip_count = 0;
	bnx2fc_stats->nos_count = 0;
	bnx2fc_stats->loss_of_sync_count = 0;
	bnx2fc_stats->loss_of_संकेत_count = 0;
	bnx2fc_stats->prim_seq_protocol_err_count = 0;

	स_नकल(&hba->prev_stats, hba->stats_buffer,
	       माप(काष्ठा fcoe_statistics_params));

unlock_stats_mutex:
	mutex_unlock(&hba->hba_stats_mutex);
	वापस bnx2fc_stats;
पूर्ण

अटल पूर्णांक bnx2fc_shost_config(काष्ठा fc_lport *lport, काष्ठा device *dev)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा Scsi_Host *shost = lport->host;
	पूर्णांक rc = 0;

	shost->max_cmd_len = BNX2FC_MAX_CMD_LEN;
	shost->max_lun = bnx2fc_max_luns;
	shost->max_id = BNX2FC_MAX_FCP_TGT;
	shost->max_channel = 0;
	अगर (lport->vport)
		shost->transportt = bnx2fc_vport_xport_ढाँचा;
	अन्यथा
		shost->transportt = bnx2fc_transport_ढाँचा;

	/* Add the new host to SCSI-ml */
	rc = scsi_add_host(lport->host, dev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "Error on scsi_add_host\n");
		वापस rc;
	पूर्ण
	अगर (!lport->vport)
		fc_host_max_npiv_vports(lport->host) = अच_लघु_उच्च;
	snम_लिखो(fc_host_symbolic_name(lport->host), 256,
		 "%s (QLogic %s) v%s over %s",
		BNX2FC_NAME, hba->chip_num, BNX2FC_VERSION,
		पूर्णांकerface->netdev->name);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_link_ok(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;
	काष्ठा net_device *dev = hba->phys_dev;
	पूर्णांक rc = 0;

	अगर ((dev->flags & IFF_UP) && netअगर_carrier_ok(dev))
		clear_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
	अन्यथा अणु
		set_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
		rc = -1;
	पूर्ण
	वापस rc;
पूर्ण

/**
 * bnx2fc_get_link_state - get network link state
 *
 * @hba:	adapter instance poपूर्णांकer
 *
 * updates adapter काष्ठाure flag based on netdev state
 */
व्योम bnx2fc_get_link_state(काष्ठा bnx2fc_hba *hba)
अणु
	अगर (test_bit(__LINK_STATE_NOCARRIER, &hba->phys_dev->state))
		set_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
	अन्यथा
		clear_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state);
पूर्ण

अटल पूर्णांक bnx2fc_net_config(काष्ठा fc_lport *lport, काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2fc_hba *hba;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fcoe_port *port;
	u64 wwnn, wwpn;

	port = lport_priv(lport);
	पूर्णांकerface = port->priv;
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	hba = पूर्णांकerface->hba;

	/* require support क्रम get_छोड़ोparam ethtool op. */
	अगर (!hba->phys_dev->ethtool_ops ||
	    !hba->phys_dev->ethtool_ops->get_छोड़ोparam)
		वापस -EOPNOTSUPP;

	अगर (fc_set_mfs(lport, BNX2FC_MFS))
		वापस -EINVAL;

	skb_queue_head_init(&port->fcoe_pending_queue);
	port->fcoe_pending_queue_active = 0;
	समयr_setup(&port->समयr, fcoe_queue_समयr, 0);

	fcoe_link_speed_update(lport);

	अगर (!lport->vport) अणु
		अगर (fcoe_get_wwn(netdev, &wwnn, NETDEV_FCOE_WWNN))
			wwnn = fcoe_wwn_from_mac(ctlr->ctl_src_addr,
						 1, 0);
		BNX2FC_HBA_DBG(lport, "WWNN = 0x%llx\n", wwnn);
		fc_set_wwnn(lport, wwnn);

		अगर (fcoe_get_wwn(netdev, &wwpn, NETDEV_FCOE_WWPN))
			wwpn = fcoe_wwn_from_mac(ctlr->ctl_src_addr,
						 2, 0);

		BNX2FC_HBA_DBG(lport, "WWPN = 0x%llx\n", wwpn);
		fc_set_wwpn(lport, wwpn);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम bnx2fc_destroy_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा bnx2fc_hba *hba = from_समयr(hba, t, destroy_समयr);

	prपूर्णांकk(KERN_ERR PFX "ERROR:bnx2fc_destroy_timer - "
	       "Destroy compl not received!!\n");
	set_bit(BNX2FC_FLAG_DESTROY_CMPL, &hba->flags);
	wake_up_पूर्णांकerruptible(&hba->destroy_रुको);
पूर्ण

/**
 * bnx2fc_indicate_netevent - Generic netdev event handler
 *
 * @context:	adapter काष्ठाure poपूर्णांकer
 * @event:	event type
 * @vlan_id:	vlan id - associated vlan id with this event
 *
 * Handles NETDEV_UP, NETDEV_DOWN, NETDEV_GOING_DOWN,NETDEV_CHANGE and
 * NETDEV_CHANGE_MTU events. Handle NETDEV_UNREGISTER only क्रम vlans.
 */
अटल व्योम bnx2fc_indicate_netevent(व्योम *context, अचिन्हित दीर्घ event,
				     u16 vlan_id)
अणु
	काष्ठा bnx2fc_hba *hba = (काष्ठा bnx2fc_hba *)context;
	काष्ठा fcoe_ctlr_device *cdev;
	काष्ठा fc_lport *lport;
	काष्ठा fc_lport *vport;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface, *पंचांगp;
	काष्ठा fcoe_ctlr *ctlr;
	पूर्णांक रुको_क्रम_upload = 0;
	u32 link_possible = 1;

	अगर (vlan_id != 0 && event != NETDEV_UNREGISTER)
		वापस;

	चयन (event) अणु
	हाल NETDEV_UP:
		अगर (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state))
			prपूर्णांकk(KERN_ERR "indicate_netevent: "\
					"hba is not UP!!\n");
		अवरोध;

	हाल NETDEV_DOWN:
		clear_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
		clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
		link_possible = 0;
		अवरोध;

	हाल NETDEV_GOING_DOWN:
		set_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state);
		link_possible = 0;
		अवरोध;

	हाल NETDEV_CHANGE:
		अवरोध;

	हाल NETDEV_UNREGISTER:
		अगर (!vlan_id)
			वापस;
		mutex_lock(&bnx2fc_dev_lock);
		list_क्रम_each_entry_safe(पूर्णांकerface, पंचांगp, &अगर_list, list) अणु
			अगर (पूर्णांकerface->hba == hba &&
			    पूर्णांकerface->vlan_id == (vlan_id & VLAN_VID_MASK))
				__bnx2fc_destroy(पूर्णांकerface);
		पूर्ण
		mutex_unlock(&bnx2fc_dev_lock);

		/* Ensure ALL destroy work has been completed beक्रमe वापस */
		flush_workqueue(bnx2fc_wq);
		वापस;

	शेष:
		वापस;
	पूर्ण

	mutex_lock(&bnx2fc_dev_lock);
	list_क्रम_each_entry(पूर्णांकerface, &अगर_list, list) अणु

		अगर (पूर्णांकerface->hba != hba)
			जारी;

		ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
		lport = ctlr->lp;
		BNX2FC_HBA_DBG(lport, "netevent handler - event=%s %ld\n",
				पूर्णांकerface->netdev->name, event);

		fcoe_link_speed_update(lport);

		cdev = fcoe_ctlr_to_ctlr_dev(ctlr);

		अगर (link_possible && !bnx2fc_link_ok(lport)) अणु
			चयन (cdev->enabled) अणु
			हाल FCOE_CTLR_DISABLED:
				pr_info("Link up while interface is disabled.\n");
				अवरोध;
			हाल FCOE_CTLR_ENABLED:
			हाल FCOE_CTLR_UNUSED:
				/* Reset max recv frame size to शेष */
				fc_set_mfs(lport, BNX2FC_MFS);
				/*
				 * ctlr link up will only be handled during
				 * enable to aव्योम sending discovery
				 * solicitation on a stale vlan
				 */
				अगर (पूर्णांकerface->enabled)
					fcoe_ctlr_link_up(ctlr);
			पूर्ण
		पूर्ण अन्यथा अगर (fcoe_ctlr_link_करोwn(ctlr)) अणु
			चयन (cdev->enabled) अणु
			हाल FCOE_CTLR_DISABLED:
				pr_info("Link down while interface is disabled.\n");
				अवरोध;
			हाल FCOE_CTLR_ENABLED:
			हाल FCOE_CTLR_UNUSED:
				mutex_lock(&lport->lp_mutex);
				list_क्रम_each_entry(vport, &lport->vports, list)
					fc_host_port_type(vport->host) =
					FC_PORTTYPE_UNKNOWN;
				mutex_unlock(&lport->lp_mutex);
				fc_host_port_type(lport->host) =
					FC_PORTTYPE_UNKNOWN;
				per_cpu_ptr(lport->stats,
					    get_cpu())->LinkFailureCount++;
				put_cpu();
				fcoe_clean_pending_queue(lport);
				रुको_क्रम_upload = 1;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&bnx2fc_dev_lock);

	अगर (रुको_क्रम_upload) अणु
		clear_bit(ADAPTER_STATE_READY, &hba->adapter_state);
		init_रुकोqueue_head(&hba->shutकरोwn_रुको);
		BNX2FC_MISC_DBG("indicate_netevent "
				"num_ofld_sess = %d\n",
				hba->num_ofld_sess);
		hba->रुको_क्रम_link_करोwn = 1;
		रुको_event_पूर्णांकerruptible(hba->shutकरोwn_रुको,
					 (hba->num_ofld_sess == 0));
		BNX2FC_MISC_DBG("wakeup - num_ofld_sess = %d\n",
				hba->num_ofld_sess);
		hba->रुको_क्रम_link_करोwn = 0;

		अगर (संकेत_pending(current))
			flush_संकेतs(current);
	पूर्ण
पूर्ण

अटल पूर्णांक bnx2fc_libfc_config(काष्ठा fc_lport *lport)
अणु

	/* Set the function poपूर्णांकers set by bnx2fc driver */
	स_नकल(&lport->tt, &bnx2fc_libfc_fcn_templ,
		माप(काष्ठा libfc_function_ढाँचा));
	fc_elsct_init(lport);
	fc_exch_init(lport);
	fc_disc_init(lport);
	fc_disc_config(lport, lport);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_em_config(काष्ठा fc_lport *lport, काष्ठा bnx2fc_hba *hba)
अणु
	पूर्णांक fcoe_min_xid, fcoe_max_xid;

	fcoe_min_xid = hba->max_xid + 1;
	अगर (nr_cpu_ids <= 2)
		fcoe_max_xid = hba->max_xid + FCOE_XIDS_PER_CPU_OFFSET;
	अन्यथा
		fcoe_max_xid = hba->max_xid + FCOE_MAX_XID_OFFSET;
	अगर (!fc_exch_mgr_alloc(lport, FC_CLASS_3, fcoe_min_xid,
			       fcoe_max_xid, शून्य)) अणु
		prपूर्णांकk(KERN_ERR PFX "em_config:fc_exch_mgr_alloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_lport_config(काष्ठा fc_lport *lport)
अणु
	lport->link_up = 0;
	lport->qfull = 0;
	lport->max_retry_count = BNX2FC_MAX_RETRY_CNT;
	lport->max_rport_retry_count = BNX2FC_MAX_RPORT_RETRY_CNT;
	lport->e_d_tov = 2 * 1000;
	lport->r_a_tov = 10 * 1000;

	lport->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
				FCP_SPPF_RETRY | FCP_SPPF_CONF_COMPL);
	lport->करोes_npiv = 1;

	स_रखो(&lport->rnid_gen, 0, माप(काष्ठा fc_els_rnid_gen));
	lport->rnid_gen.rnid_atype = BNX2FC_RNID_HBA;

	/* alloc stats काष्ठाure */
	अगर (fc_lport_init_stats(lport))
		वापस -ENOMEM;

	/* Finish fc_lport configuration */
	fc_lport_config(lport);

	वापस 0;
पूर्ण

/**
 * bnx2fc_fip_recv - handle a received FIP frame.
 *
 * @skb: the received skb
 * @dev: associated &net_device
 * @ptype: the &packet_type काष्ठाure which was used to रेजिस्टर this handler.
 * @orig_dev: original receive &net_device, in हाल @ dev is a bond.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक bnx2fc_fip_recv(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
			   काष्ठा packet_type *ptype,
			   काष्ठा net_device *orig_dev)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	पूर्णांकerface = container_of(ptype, काष्ठा bnx2fc_पूर्णांकerface,
				 fip_packet_type);
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	fcoe_ctlr_recv(ctlr, skb);
	वापस 0;
पूर्ण

/**
 * bnx2fc_update_src_mac - Update Ethernet MAC filters.
 *
 * @lport: The local port
 * @addr: Location of data to copy
 *
 * Remove any previously-set unicast MAC filter.
 * Add secondary FCoE MAC address filter क्रम our OUI.
 */
अटल व्योम bnx2fc_update_src_mac(काष्ठा fc_lport *lport, u8 *addr)
अणु
	काष्ठा fcoe_port *port = lport_priv(lport);

	स_नकल(port->data_src_addr, addr, ETH_ALEN);
पूर्ण

/**
 * bnx2fc_get_src_mac - वापस the ethernet source address क्रम an lport
 *
 * @lport: libfc port
 */
अटल u8 *bnx2fc_get_src_mac(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_port *port;

	port = (काष्ठा fcoe_port *)lport_priv(lport);
	वापस port->data_src_addr;
पूर्ण

/**
 * bnx2fc_fip_send - send an Ethernet-encapsulated FIP frame.
 *
 * @fip: FCoE controller.
 * @skb: FIP Packet.
 */
अटल व्योम bnx2fc_fip_send(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_header *fiph;
	काष्ठा ethhdr *eth_hdr;
	u16 op;
	u8 sub;

	fiph = (काष्ठा fip_header *) ((व्योम *)skb->data + 2 * ETH_ALEN + 2);
	eth_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	अगर (op == FIP_OP_CTRL && sub == FIP_SC_SOL && bnx2fc_log_fka)
		BNX2FC_MISC_DBG("Sending FKA from %pM to %pM.\n",
		    eth_hdr->h_source, eth_hdr->h_dest);

	skb->dev = bnx2fc_from_ctlr(fip)->netdev;
	dev_queue_xmit(skb);
पूर्ण

अटल पूर्णांक bnx2fc_vport_create(काष्ठा fc_vport *vport, bool disabled)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fcoe_port *port = lport_priv(n_port);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा fc_lport *vn_port;
	पूर्णांक rc;
	अक्षर buf[32];

	rc = fcoe_validate_vport_create(vport);
	अगर (rc) अणु
		fcoe_wwn_to_str(vport->port_name, buf, माप(buf));
		prपूर्णांकk(KERN_ERR PFX "Failed to create vport, "
		       "WWPN (0x%s) already exists\n",
		       buf);
		वापस rc;
	पूर्ण

	अगर (!test_bit(BNX2FC_FLAG_FW_INIT_DONE, &पूर्णांकerface->hba->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "vn ports cannot be created on"
			"this interface\n");
		वापस -EIO;
	पूर्ण
	rtnl_lock();
	mutex_lock(&bnx2fc_dev_lock);
	vn_port = bnx2fc_अगर_create(पूर्णांकerface, &vport->dev, 1);
	mutex_unlock(&bnx2fc_dev_lock);
	rtnl_unlock();

	अगर (!vn_port) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_vport_create (%s) failed\n",
			netdev->name);
		वापस -EIO;
	पूर्ण

	अगर (bnx2fc_devloss_पंचांगo)
		fc_host_dev_loss_पंचांगo(vn_port->host) = bnx2fc_devloss_पंचांगo;

	अगर (disabled) अणु
		fc_vport_set_state(vport, FC_VPORT_DISABLED);
	पूर्ण अन्यथा अणु
		vn_port->boot_समय = jअगरfies;
		fc_lport_init(vn_port);
		fc_fabric_login(vn_port);
		fc_vport_setlink(vn_port);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम bnx2fc_मुक्त_vport(काष्ठा bnx2fc_hba *hba, काष्ठा fc_lport *lport)
अणु
	काष्ठा bnx2fc_lport *blport, *पंचांगp;

	spin_lock_bh(&hba->hba_lock);
	list_क्रम_each_entry_safe(blport, पंचांगp, &hba->vports, list) अणु
		अगर (blport->lport == lport) अणु
			list_del(&blport->list);
			kमुक्त(blport);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&hba->hba_lock);
पूर्ण

अटल पूर्णांक bnx2fc_vport_destroy(काष्ठा fc_vport *vport)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fc_lport *vn_port = vport->dd_data;
	काष्ठा fcoe_port *port = lport_priv(vn_port);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	काष्ठा fc_lport *v_port;
	bool found = false;

	mutex_lock(&n_port->lp_mutex);
	list_क्रम_each_entry(v_port, &n_port->vports, list)
		अगर (v_port->vport == vport) अणु
			found = true;
			अवरोध;
		पूर्ण

	अगर (!found) अणु
		mutex_unlock(&n_port->lp_mutex);
		वापस -ENOENT;
	पूर्ण
	list_del(&vn_port->list);
	mutex_unlock(&n_port->lp_mutex);
	bnx2fc_मुक्त_vport(पूर्णांकerface->hba, port->lport);
	bnx2fc_port_shutकरोwn(port->lport);
	bnx2fc_पूर्णांकerface_put(पूर्णांकerface);
	queue_work(bnx2fc_wq, &port->destroy_work);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_vport_disable(काष्ठा fc_vport *vport, bool disable)
अणु
	काष्ठा fc_lport *lport = vport->dd_data;

	अगर (disable) अणु
		fc_vport_set_state(vport, FC_VPORT_DISABLED);
		fc_fabric_logoff(lport);
	पूर्ण अन्यथा अणु
		lport->boot_समय = jअगरfies;
		fc_fabric_login(lport);
		fc_vport_setlink(lport);
	पूर्ण
	वापस 0;
पूर्ण


अटल पूर्णांक bnx2fc_पूर्णांकerface_setup(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा net_device *netdev = पूर्णांकerface->netdev;
	काष्ठा net_device *physdev = पूर्णांकerface->hba->phys_dev;
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक sel_san_mac = 0;

	/* setup Source MAC Address */
	rcu_पढ़ो_lock();
	क्रम_each_dev_addr(physdev, ha) अणु
		BNX2FC_MISC_DBG("net_config: ha->type = %d, fip_mac = ",
				ha->type);
		prपूर्णांकk(KERN_INFO "%2x:%2x:%2x:%2x:%2x:%2x\n", ha->addr[0],
				ha->addr[1], ha->addr[2], ha->addr[3],
				ha->addr[4], ha->addr[5]);

		अगर ((ha->type == NETDEV_HW_ADDR_T_SAN) &&
		    (is_valid_ether_addr(ha->addr))) अणु
			स_नकल(ctlr->ctl_src_addr, ha->addr,
			       ETH_ALEN);
			sel_san_mac = 1;
			BNX2FC_MISC_DBG("Found SAN MAC\n");
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (!sel_san_mac)
		वापस -ENODEV;

	पूर्णांकerface->fip_packet_type.func = bnx2fc_fip_recv;
	पूर्णांकerface->fip_packet_type.type = htons(ETH_P_FIP);
	पूर्णांकerface->fip_packet_type.dev = netdev;
	dev_add_pack(&पूर्णांकerface->fip_packet_type);

	पूर्णांकerface->fcoe_packet_type.func = bnx2fc_rcv;
	पूर्णांकerface->fcoe_packet_type.type = __स्थिरant_htons(ETH_P_FCOE);
	पूर्णांकerface->fcoe_packet_type.dev = netdev;
	dev_add_pack(&पूर्णांकerface->fcoe_packet_type);

	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_attach_transport(व्योम)
अणु
	bnx2fc_transport_ढाँचा =
		fc_attach_transport(&bnx2fc_transport_function);

	अगर (bnx2fc_transport_ढाँचा == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to attach FC transport\n");
		वापस -ENODEV;
	पूर्ण

	bnx2fc_vport_xport_ढाँचा =
		fc_attach_transport(&bnx2fc_vport_xport_function);
	अगर (bnx2fc_vport_xport_ढाँचा == शून्य) अणु
		prपूर्णांकk(KERN_ERR PFX
		       "Failed to attach FC transport for vport\n");
		fc_release_transport(bnx2fc_transport_ढाँचा);
		bnx2fc_transport_ढाँचा = शून्य;
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण
अटल व्योम bnx2fc_release_transport(व्योम)
अणु
	fc_release_transport(bnx2fc_transport_ढाँचा);
	fc_release_transport(bnx2fc_vport_xport_ढाँचा);
	bnx2fc_transport_ढाँचा = शून्य;
	bnx2fc_vport_xport_ढाँचा = शून्य;
पूर्ण

अटल व्योम bnx2fc_पूर्णांकerface_release(काष्ठा kref *kref)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा net_device *netdev;

	पूर्णांकerface = container_of(kref, काष्ठा bnx2fc_पूर्णांकerface, kref);
	BNX2FC_MISC_DBG("Interface is being released\n");

	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	ctlr_dev = fcoe_ctlr_to_ctlr_dev(ctlr);
	netdev = पूर्णांकerface->netdev;

	/* tear-करोwn FIP controller */
	अगर (test_and_clear_bit(BNX2FC_CTLR_INIT_DONE, &पूर्णांकerface->अगर_flags))
		fcoe_ctlr_destroy(ctlr);

	fcoe_ctlr_device_delete(ctlr_dev);

	dev_put(netdev);
	module_put(THIS_MODULE);
पूर्ण

अटल अंतरभूत व्योम bnx2fc_पूर्णांकerface_get(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	kref_get(&पूर्णांकerface->kref);
पूर्ण

अटल अंतरभूत व्योम bnx2fc_पूर्णांकerface_put(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	kref_put(&पूर्णांकerface->kref, bnx2fc_पूर्णांकerface_release);
पूर्ण
अटल व्योम bnx2fc_hba_destroy(काष्ठा bnx2fc_hba *hba)
अणु
	/* Free the command manager */
	अगर (hba->cmd_mgr) अणु
		bnx2fc_cmd_mgr_मुक्त(hba->cmd_mgr);
		hba->cmd_mgr = शून्य;
	पूर्ण
	kमुक्त(hba->tgt_ofld_list);
	bnx2fc_unbind_pcidev(hba);
	kमुक्त(hba);
पूर्ण

/**
 * bnx2fc_hba_create - create a new bnx2fc hba
 *
 * @cnic:	poपूर्णांकer to cnic device
 *
 * Creates a new FCoE hba on the given device.
 *
 */
अटल काष्ठा bnx2fc_hba *bnx2fc_hba_create(काष्ठा cnic_dev *cnic)
अणु
	काष्ठा bnx2fc_hba *hba;
	काष्ठा fcoe_capabilities *fcoe_cap;
	पूर्णांक rc;

	hba = kzalloc(माप(*hba), GFP_KERNEL);
	अगर (!hba) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate hba structure\n");
		वापस शून्य;
	पूर्ण
	spin_lock_init(&hba->hba_lock);
	mutex_init(&hba->hba_mutex);
	mutex_init(&hba->hba_stats_mutex);

	hba->cnic = cnic;

	hba->max_tasks = cnic->max_fcoe_exchanges;
	hba->elsपंचांग_xids = (hba->max_tasks / 2);
	hba->max_outstanding_cmds = hba->elsपंचांग_xids;
	hba->max_xid = (hba->max_tasks - 1);

	rc = bnx2fc_bind_pcidev(hba);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "create_adapter:  bind error\n");
		जाओ bind_err;
	पूर्ण
	hba->phys_dev = cnic->netdev;
	hba->next_conn_id = 0;

	hba->tgt_ofld_list =
		kसुस्मृति(BNX2FC_NUM_MAX_SESS, माप(काष्ठा bnx2fc_rport *),
			GFP_KERNEL);
	अगर (!hba->tgt_ofld_list) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate tgt offload list\n");
		जाओ tgtofld_err;
	पूर्ण

	hba->num_ofld_sess = 0;

	hba->cmd_mgr = bnx2fc_cmd_mgr_alloc(hba);
	अगर (!hba->cmd_mgr) अणु
		prपूर्णांकk(KERN_ERR PFX "em_config:bnx2fc_cmd_mgr_alloc failed\n");
		जाओ cmgr_err;
	पूर्ण
	fcoe_cap = &hba->fcoe_cap;

	fcoe_cap->capability1 = BNX2FC_TM_MAX_SQES <<
					FCOE_IOS_PER_CONNECTION_SHIFT;
	fcoe_cap->capability1 |= BNX2FC_NUM_MAX_SESS <<
					FCOE_LOGINS_PER_PORT_SHIFT;
	fcoe_cap->capability2 = hba->max_outstanding_cmds <<
					FCOE_NUMBER_OF_EXCHANGES_SHIFT;
	fcoe_cap->capability2 |= BNX2FC_MAX_NPIV <<
					FCOE_NPIV_WWN_PER_PORT_SHIFT;
	fcoe_cap->capability3 = BNX2FC_NUM_MAX_SESS <<
					FCOE_TARGETS_SUPPORTED_SHIFT;
	fcoe_cap->capability3 |= hba->max_outstanding_cmds <<
					FCOE_OUTSTANDING_COMMANDS_SHIFT;
	fcoe_cap->capability4 = FCOE_CAPABILITY4_STATEFUL;

	init_रुकोqueue_head(&hba->shutकरोwn_रुको);
	init_रुकोqueue_head(&hba->destroy_रुको);
	INIT_LIST_HEAD(&hba->vports);

	वापस hba;

cmgr_err:
	kमुक्त(hba->tgt_ofld_list);
tgtofld_err:
	bnx2fc_unbind_pcidev(hba);
bind_err:
	kमुक्त(hba);
	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2fc_पूर्णांकerface *
bnx2fc_पूर्णांकerface_create(काष्ठा bnx2fc_hba *hba,
			काष्ठा net_device *netdev,
			क्रमागत fip_mode fip_mode)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	पूर्णांक size;
	पूर्णांक rc = 0;

	size = (माप(*पूर्णांकerface) + माप(काष्ठा fcoe_ctlr));
	ctlr_dev = fcoe_ctlr_device_add(&netdev->dev, &bnx2fc_fcoe_sysfs_templ,
					 size);
	अगर (!ctlr_dev) अणु
		prपूर्णांकk(KERN_ERR PFX "Unable to allocate interface structure\n");
		वापस शून्य;
	पूर्ण
	ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	ctlr->cdev = ctlr_dev;
	पूर्णांकerface = fcoe_ctlr_priv(ctlr);
	dev_hold(netdev);
	kref_init(&पूर्णांकerface->kref);
	पूर्णांकerface->hba = hba;
	पूर्णांकerface->netdev = netdev;

	/* Initialize FIP */
	fcoe_ctlr_init(ctlr, fip_mode);
	ctlr->send = bnx2fc_fip_send;
	ctlr->update_mac = bnx2fc_update_src_mac;
	ctlr->get_src_addr = bnx2fc_get_src_mac;
	set_bit(BNX2FC_CTLR_INIT_DONE, &पूर्णांकerface->अगर_flags);

	rc = bnx2fc_पूर्णांकerface_setup(पूर्णांकerface);
	अगर (!rc)
		वापस पूर्णांकerface;

	fcoe_ctlr_destroy(ctlr);
	dev_put(netdev);
	fcoe_ctlr_device_delete(ctlr_dev);
	वापस शून्य;
पूर्ण

/**
 * bnx2fc_अगर_create - Create FCoE instance on a given पूर्णांकerface
 *
 * @पूर्णांकerface:	FCoE पूर्णांकerface to create a local port on
 * @parent:	Device poपूर्णांकer to be the parent in sysfs क्रम the SCSI host
 * @npiv:	Indicates अगर the port is vport or not
 *
 * Creates a fc_lport instance and a Scsi_Host instance and configure them.
 *
 * Returns:	Allocated fc_lport or an error poपूर्णांकer
 */
अटल काष्ठा fc_lport *bnx2fc_अगर_create(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface,
				  काष्ठा device *parent, पूर्णांक npiv)
अणु
	काष्ठा fcoe_ctlr        *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा fc_lport		*lport, *n_port;
	काष्ठा fcoe_port	*port;
	काष्ठा Scsi_Host	*shost;
	काष्ठा fc_vport		*vport = dev_to_vport(parent);
	काष्ठा bnx2fc_lport	*blport;
	काष्ठा bnx2fc_hba	*hba = पूर्णांकerface->hba;
	पूर्णांक			rc = 0;

	blport = kzalloc(माप(काष्ठा bnx2fc_lport), GFP_KERNEL);
	अगर (!blport) अणु
		BNX2FC_HBA_DBG(ctlr->lp, "Unable to alloc blport\n");
		वापस शून्य;
	पूर्ण

	/* Allocate Scsi_Host काष्ठाure */
	bnx2fc_shost_ढाँचा.can_queue = hba->max_outstanding_cmds;
	अगर (!npiv)
		lport = libfc_host_alloc(&bnx2fc_shost_ढाँचा, माप(*port));
	अन्यथा
		lport = libfc_vport_create(vport, माप(*port));

	अगर (!lport) अणु
		prपूर्णांकk(KERN_ERR PFX "could not allocate scsi host structure\n");
		जाओ मुक्त_blport;
	पूर्ण
	shost = lport->host;
	port = lport_priv(lport);
	port->lport = lport;
	port->priv = पूर्णांकerface;
	port->get_netdev = bnx2fc_netdev;
	INIT_WORK(&port->destroy_work, bnx2fc_destroy_work);

	/* Configure fcoe_port */
	rc = bnx2fc_lport_config(lport);
	अगर (rc)
		जाओ lp_config_err;

	अगर (npiv) अणु
		prपूर्णांकk(KERN_ERR PFX "Setting vport names, 0x%llX 0x%llX\n",
			vport->node_name, vport->port_name);
		fc_set_wwnn(lport, vport->node_name);
		fc_set_wwpn(lport, vport->port_name);
	पूर्ण
	/* Configure netdev and networking properties of the lport */
	rc = bnx2fc_net_config(lport, पूर्णांकerface->netdev);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "Error on bnx2fc_net_config\n");
		जाओ lp_config_err;
	पूर्ण

	rc = bnx2fc_shost_config(lport, parent);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "Couldn't configure shost for %s\n",
			पूर्णांकerface->netdev->name);
		जाओ lp_config_err;
	पूर्ण

	/* Initialize the libfc library */
	rc = bnx2fc_libfc_config(lport);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "Couldn't configure libfc\n");
		जाओ shost_err;
	पूर्ण
	fc_host_port_type(lport->host) = FC_PORTTYPE_UNKNOWN;

	अगर (bnx2fc_devloss_पंचांगo)
		fc_host_dev_loss_पंचांगo(shost) = bnx2fc_devloss_पंचांगo;

	/* Allocate exchange manager */
	अगर (!npiv)
		rc = bnx2fc_em_config(lport, hba);
	अन्यथा अणु
		shost = vport_to_shost(vport);
		n_port = shost_priv(shost);
		rc = fc_exch_mgr_list_clone(n_port, lport);
	पूर्ण

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PFX "Error on bnx2fc_em_config\n");
		जाओ shost_err;
	पूर्ण

	bnx2fc_पूर्णांकerface_get(पूर्णांकerface);

	spin_lock_bh(&hba->hba_lock);
	blport->lport = lport;
	list_add_tail(&blport->list, &hba->vports);
	spin_unlock_bh(&hba->hba_lock);

	वापस lport;

shost_err:
	scsi_हटाओ_host(shost);
lp_config_err:
	scsi_host_put(lport->host);
मुक्त_blport:
	kमुक्त(blport);
	वापस शून्य;
पूर्ण

अटल व्योम bnx2fc_net_cleanup(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	/* Dont listen क्रम Ethernet packets anymore */
	__dev_हटाओ_pack(&पूर्णांकerface->fcoe_packet_type);
	__dev_हटाओ_pack(&पूर्णांकerface->fip_packet_type);
	synchronize_net();
पूर्ण

अटल व्योम bnx2fc_पूर्णांकerface_cleanup(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा fc_lport *lport = ctlr->lp;
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_hba *hba = पूर्णांकerface->hba;

	/* Stop the transmit retry समयr */
	del_समयr_sync(&port->समयr);

	/* Free existing transmit skbs */
	fcoe_clean_pending_queue(lport);

	bnx2fc_net_cleanup(पूर्णांकerface);

	bnx2fc_मुक्त_vport(hba, lport);
पूर्ण

अटल व्योम bnx2fc_अगर_destroy(काष्ठा fc_lport *lport)
अणु

	/* Free queued packets क्रम the receive thपढ़ो */
	bnx2fc_clean_rx_queue(lport);

	/* Detach from scsi-ml */
	fc_हटाओ_host(lport->host);
	scsi_हटाओ_host(lport->host);

	/*
	 * Note that only the physical lport will have the exchange manager.
	 * क्रम vports, this function is NOP
	 */
	fc_exch_mgr_मुक्त(lport);

	/* Free memory used by statistical counters */
	fc_lport_मुक्त_stats(lport);

	/* Release Scsi_Host */
	scsi_host_put(lport->host);
पूर्ण

अटल व्योम __bnx2fc_destroy(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा fc_lport *lport = ctlr->lp;
	काष्ठा fcoe_port *port = lport_priv(lport);

	bnx2fc_पूर्णांकerface_cleanup(पूर्णांकerface);
	bnx2fc_stop(पूर्णांकerface);
	list_del(&पूर्णांकerface->list);
	bnx2fc_पूर्णांकerface_put(पूर्णांकerface);
	queue_work(bnx2fc_wq, &port->destroy_work);
पूर्ण

/**
 * bnx2fc_destroy - Destroy a bnx2fc FCoE पूर्णांकerface
 *
 * @netdev: The net device that the FCoE पूर्णांकerface is on
 *
 * Called from sysfs.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक bnx2fc_destroy(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = शून्य;
	काष्ठा workqueue_काष्ठा *समयr_work_queue;
	काष्ठा fcoe_ctlr *ctlr;
	पूर्णांक rc = 0;

	rtnl_lock();
	mutex_lock(&bnx2fc_dev_lock);

	पूर्णांकerface = bnx2fc_पूर्णांकerface_lookup(netdev);
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	अगर (!पूर्णांकerface || !ctlr->lp) अणु
		rc = -ENODEV;
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_destroy: interface or lport not found\n");
		जाओ netdev_err;
	पूर्ण

	समयr_work_queue = पूर्णांकerface->समयr_work_queue;
	__bnx2fc_destroy(पूर्णांकerface);
	destroy_workqueue(समयr_work_queue);

netdev_err:
	mutex_unlock(&bnx2fc_dev_lock);
	rtnl_unlock();
	वापस rc;
पूर्ण

अटल व्योम bnx2fc_destroy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcoe_port *port;
	काष्ठा fc_lport *lport;

	port = container_of(work, काष्ठा fcoe_port, destroy_work);
	lport = port->lport;

	BNX2FC_HBA_DBG(lport, "Entered bnx2fc_destroy_work\n");

	bnx2fc_अगर_destroy(lport);
पूर्ण

अटल व्योम bnx2fc_unbind_adapter_devices(काष्ठा bnx2fc_hba *hba)
अणु
	bnx2fc_मुक्त_fw_resc(hba);
	bnx2fc_मुक्त_task_ctx(hba);
पूर्ण

/**
 * bnx2fc_bind_adapter_devices - binds bnx2fc adapter with the associated
 *			pci काष्ठाure
 *
 * @hba:		Adapter instance
 */
अटल पूर्णांक bnx2fc_bind_adapter_devices(काष्ठा bnx2fc_hba *hba)
अणु
	अगर (bnx2fc_setup_task_ctx(hba))
		जाओ mem_err;

	अगर (bnx2fc_setup_fw_resc(hba))
		जाओ mem_err;

	वापस 0;
mem_err:
	bnx2fc_unbind_adapter_devices(hba);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक bnx2fc_bind_pcidev(काष्ठा bnx2fc_hba *hba)
अणु
	काष्ठा cnic_dev *cnic;
	काष्ठा pci_dev *pdev;

	अगर (!hba->cnic) अणु
		prपूर्णांकk(KERN_ERR PFX "cnic is NULL\n");
		वापस -ENODEV;
	पूर्ण
	cnic = hba->cnic;
	pdev = hba->pcidev = cnic->pcidev;
	अगर (!hba->pcidev)
		वापस -ENODEV;

	चयन (pdev->device) अणु
	हाल PCI_DEVICE_ID_NX2_57710:
		म_नकलन(hba->chip_num, "BCM57710", BCM_CHIP_LEN);
		अवरोध;
	हाल PCI_DEVICE_ID_NX2_57711:
		म_नकलन(hba->chip_num, "BCM57711", BCM_CHIP_LEN);
		अवरोध;
	हाल PCI_DEVICE_ID_NX2_57712:
	हाल PCI_DEVICE_ID_NX2_57712_MF:
	हाल PCI_DEVICE_ID_NX2_57712_VF:
		म_नकलन(hba->chip_num, "BCM57712", BCM_CHIP_LEN);
		अवरोध;
	हाल PCI_DEVICE_ID_NX2_57800:
	हाल PCI_DEVICE_ID_NX2_57800_MF:
	हाल PCI_DEVICE_ID_NX2_57800_VF:
		म_नकलन(hba->chip_num, "BCM57800", BCM_CHIP_LEN);
		अवरोध;
	हाल PCI_DEVICE_ID_NX2_57810:
	हाल PCI_DEVICE_ID_NX2_57810_MF:
	हाल PCI_DEVICE_ID_NX2_57810_VF:
		म_नकलन(hba->chip_num, "BCM57810", BCM_CHIP_LEN);
		अवरोध;
	हाल PCI_DEVICE_ID_NX2_57840:
	हाल PCI_DEVICE_ID_NX2_57840_MF:
	हाल PCI_DEVICE_ID_NX2_57840_VF:
	हाल PCI_DEVICE_ID_NX2_57840_2_20:
	हाल PCI_DEVICE_ID_NX2_57840_4_10:
		म_नकलन(hba->chip_num, "BCM57840", BCM_CHIP_LEN);
		अवरोध;
	शेष:
		pr_err(PFX "Unknown device id 0x%x\n", pdev->device);
		अवरोध;
	पूर्ण
	pci_dev_get(hba->pcidev);
	वापस 0;
पूर्ण

अटल व्योम bnx2fc_unbind_pcidev(काष्ठा bnx2fc_hba *hba)
अणु
	अगर (hba->pcidev) अणु
		hba->chip_num[0] = '\0';
		pci_dev_put(hba->pcidev);
	पूर्ण
	hba->pcidev = शून्य;
पूर्ण

/**
 * bnx2fc_ulp_get_stats - cnic callback to populate FCoE stats
 *
 * @handle:    transport handle poपूर्णांकing to adapter काष्ठाure
 */
अटल पूर्णांक bnx2fc_ulp_get_stats(व्योम *handle)
अणु
	काष्ठा bnx2fc_hba *hba = handle;
	काष्ठा cnic_dev *cnic;
	काष्ठा fcoe_stats_info *stats_addr;

	अगर (!hba)
		वापस -EINVAL;

	cnic = hba->cnic;
	stats_addr = &cnic->stats_addr->fcoe_stat;
	अगर (!stats_addr)
		वापस -EINVAL;

	म_नकलन(stats_addr->version, BNX2FC_VERSION,
		माप(stats_addr->version));
	stats_addr->txq_size = BNX2FC_SQ_WQES_MAX;
	stats_addr->rxq_size = BNX2FC_CQ_WQES_MAX;

	वापस 0;
पूर्ण


/**
 * bnx2fc_ulp_start - cnic callback to initialize & start adapter instance
 *
 * @handle:	transport handle poपूर्णांकing to adapter काष्ठाure
 *
 * This function maps adapter काष्ठाure to pcidev काष्ठाure and initiates
 *	firmware handshake to enable/initialize on-chip FCoE components.
 *	This bnx2fc - cnic पूर्णांकerface api callback is used after following
 *	conditions are met -
 *	a) underlying network पूर्णांकerface is up (marked by event NETDEV_UP
 *		from netdev
 *	b) bnx2fc adatper काष्ठाure is रेजिस्टरed.
 */
अटल व्योम bnx2fc_ulp_start(व्योम *handle)
अणु
	काष्ठा bnx2fc_hba *hba = handle;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा fc_lport *lport;

	mutex_lock(&bnx2fc_dev_lock);

	अगर (!test_bit(BNX2FC_FLAG_FW_INIT_DONE, &hba->flags))
		bnx2fc_fw_init(hba);

	BNX2FC_MISC_DBG("bnx2fc started.\n");

	list_क्रम_each_entry(पूर्णांकerface, &अगर_list, list) अणु
		अगर (पूर्णांकerface->hba == hba) अणु
			ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
			lport = ctlr->lp;
			/* Kick off Fabric discovery*/
			prपूर्णांकk(KERN_ERR PFX "ulp_init: start discovery\n");
			lport->tt.frame_send = bnx2fc_xmit;
			bnx2fc_start_disc(पूर्णांकerface);
		पूर्ण
	पूर्ण

	mutex_unlock(&bnx2fc_dev_lock);
पूर्ण

अटल व्योम bnx2fc_port_shutकरोwn(काष्ठा fc_lport *lport)
अणु
	BNX2FC_MISC_DBG("Entered %s\n", __func__);
	fc_fabric_logoff(lport);
	fc_lport_destroy(lport);
पूर्ण

अटल व्योम bnx2fc_stop(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा fc_lport *lport;
	काष्ठा fc_lport *vport;

	अगर (!test_bit(BNX2FC_FLAG_FW_INIT_DONE, &पूर्णांकerface->hba->flags))
		वापस;

	lport = ctlr->lp;
	bnx2fc_port_shutकरोwn(lport);

	mutex_lock(&lport->lp_mutex);
	list_क्रम_each_entry(vport, &lport->vports, list)
		fc_host_port_type(vport->host) =
					FC_PORTTYPE_UNKNOWN;
	mutex_unlock(&lport->lp_mutex);
	fc_host_port_type(lport->host) = FC_PORTTYPE_UNKNOWN;
	fcoe_ctlr_link_करोwn(ctlr);
	fcoe_clean_pending_queue(lport);
पूर्ण

अटल पूर्णांक bnx2fc_fw_init(काष्ठा bnx2fc_hba *hba)
अणु
#घोषणा BNX2FC_INIT_POLL_TIME		(1000 / HZ)
	पूर्णांक rc = -1;
	पूर्णांक i = HZ;

	rc = bnx2fc_bind_adapter_devices(hba);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ALERT PFX
			"bnx2fc_bind_adapter_devices failed - rc = %d\n", rc);
		जाओ err_out;
	पूर्ण

	rc = bnx2fc_send_fw_fcoe_init_msg(hba);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ALERT PFX
			"bnx2fc_send_fw_fcoe_init_msg failed - rc = %d\n", rc);
		जाओ err_unbind;
	पूर्ण

	/*
	 * Wait until the adapter init message is complete, and adapter
	 * state is UP.
	 */
	जबतक (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state) && i--)
		msleep(BNX2FC_INIT_POLL_TIME);

	अगर (!test_bit(ADAPTER_STATE_UP, &hba->adapter_state)) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_start: %s failed to initialize.  "
				"Ignoring...\n",
				hba->cnic->netdev->name);
		rc = -1;
		जाओ err_unbind;
	पूर्ण


	set_bit(BNX2FC_FLAG_FW_INIT_DONE, &hba->flags);
	वापस 0;

err_unbind:
	bnx2fc_unbind_adapter_devices(hba);
err_out:
	वापस rc;
पूर्ण

अटल व्योम bnx2fc_fw_destroy(काष्ठा bnx2fc_hba *hba)
अणु
	अगर (test_and_clear_bit(BNX2FC_FLAG_FW_INIT_DONE, &hba->flags)) अणु
		अगर (bnx2fc_send_fw_fcoe_destroy_msg(hba) == 0) अणु
			समयr_setup(&hba->destroy_समयr, bnx2fc_destroy_समयr,
				    0);
			hba->destroy_समयr.expires = BNX2FC_FW_TIMEOUT +
								jअगरfies;
			add_समयr(&hba->destroy_समयr);
			रुको_event_पूर्णांकerruptible(hba->destroy_रुको,
					test_bit(BNX2FC_FLAG_DESTROY_CMPL,
						 &hba->flags));
			clear_bit(BNX2FC_FLAG_DESTROY_CMPL, &hba->flags);
			/* This should never happen */
			अगर (संकेत_pending(current))
				flush_संकेतs(current);

			del_समयr_sync(&hba->destroy_समयr);
		पूर्ण
		bnx2fc_unbind_adapter_devices(hba);
	पूर्ण
पूर्ण

/**
 * bnx2fc_ulp_stop - cnic callback to shutकरोwn adapter instance
 *
 * @handle:	transport handle poपूर्णांकing to adapter काष्ठाure
 *
 * Driver checks अगर adapter is alपढ़ोy in shutकरोwn mode, अगर not start
 *	the shutकरोwn process.
 */
अटल व्योम bnx2fc_ulp_stop(व्योम *handle)
अणु
	काष्ठा bnx2fc_hba *hba = handle;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;

	prपूर्णांकk(KERN_ERR "ULP_STOP\n");

	mutex_lock(&bnx2fc_dev_lock);
	अगर (!test_bit(BNX2FC_FLAG_FW_INIT_DONE, &hba->flags))
		जाओ निकास;
	list_क्रम_each_entry(पूर्णांकerface, &अगर_list, list) अणु
		अगर (पूर्णांकerface->hba == hba)
			bnx2fc_stop(पूर्णांकerface);
	पूर्ण
	BUG_ON(hba->num_ofld_sess != 0);

	mutex_lock(&hba->hba_mutex);
	clear_bit(ADAPTER_STATE_UP, &hba->adapter_state);
	clear_bit(ADAPTER_STATE_GOING_DOWN,
		  &hba->adapter_state);

	clear_bit(ADAPTER_STATE_READY, &hba->adapter_state);
	mutex_unlock(&hba->hba_mutex);

	bnx2fc_fw_destroy(hba);
निकास:
	mutex_unlock(&bnx2fc_dev_lock);
पूर्ण

अटल व्योम bnx2fc_start_disc(काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface)
अणु
	काष्ठा fcoe_ctlr *ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	काष्ठा fc_lport *lport;
	पूर्णांक रुको_cnt = 0;

	BNX2FC_MISC_DBG("Entered %s\n", __func__);
	/* Kick off FIP/FLOGI */
	अगर (!test_bit(BNX2FC_FLAG_FW_INIT_DONE, &पूर्णांकerface->hba->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "Init not done yet\n");
		वापस;
	पूर्ण

	lport = ctlr->lp;
	BNX2FC_HBA_DBG(lport, "calling fc_fabric_login\n");

	अगर (!bnx2fc_link_ok(lport) && पूर्णांकerface->enabled) अणु
		BNX2FC_HBA_DBG(lport, "ctlr_link_up\n");
		fcoe_ctlr_link_up(ctlr);
		fc_host_port_type(lport->host) = FC_PORTTYPE_NPORT;
		set_bit(ADAPTER_STATE_READY, &पूर्णांकerface->hba->adapter_state);
	पूर्ण

	/* रुको क्रम the FCF to be selected beक्रमe issuing FLOGI */
	जबतक (!ctlr->sel_fcf) अणु
		msleep(250);
		/* give up after 3 secs */
		अगर (++रुको_cnt > 12)
			अवरोध;
	पूर्ण

	/* Reset max receive frame size to शेष */
	अगर (fc_set_mfs(lport, BNX2FC_MFS))
		वापस;

	fc_lport_init(lport);
	fc_fabric_login(lport);
पूर्ण


/**
 * bnx2fc_ulp_init - Initialize an adapter instance
 *
 * @dev :	cnic device handle
 * Called from cnic_रेजिस्टर_driver() context to initialize all
 *	क्रमागतerated cnic devices. This routine allocates adapter काष्ठाure
 *	and other device specअगरic resources.
 */
अटल व्योम bnx2fc_ulp_init(काष्ठा cnic_dev *dev)
अणु
	काष्ठा bnx2fc_hba *hba;
	पूर्णांक rc = 0;

	BNX2FC_MISC_DBG("Entered %s\n", __func__);
	/* bnx2fc works only when bnx2x is loaded */
	अगर (!test_bit(CNIC_F_BNX2X_CLASS, &dev->flags) ||
	    (dev->max_fcoe_conn == 0)) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc FCoE not supported on %s,"
				    " flags: %lx fcoe_conn: %d\n",
			dev->netdev->name, dev->flags, dev->max_fcoe_conn);
		वापस;
	पूर्ण

	hba = bnx2fc_hba_create(dev);
	अगर (!hba) अणु
		prपूर्णांकk(KERN_ERR PFX "hba initialization failed\n");
		वापस;
	पूर्ण

	pr_info(PFX "FCoE initialized for %s.\n", dev->netdev->name);

	/* Add HBA to the adapter list */
	mutex_lock(&bnx2fc_dev_lock);
	list_add_tail(&hba->list, &adapter_list);
	adapter_count++;
	mutex_unlock(&bnx2fc_dev_lock);

	dev->fcoe_cap = &hba->fcoe_cap;
	clear_bit(BNX2FC_CNIC_REGISTERED, &hba->reg_with_cnic);
	rc = dev->रेजिस्टर_device(dev, CNIC_ULP_FCOE,
						(व्योम *) hba);
	अगर (rc)
		prपूर्णांकk(KERN_ERR PFX "register_device failed, rc = %d\n", rc);
	अन्यथा
		set_bit(BNX2FC_CNIC_REGISTERED, &hba->reg_with_cnic);
पूर्ण

/* Assumes rtnl_lock and the bnx2fc_dev_lock are alपढ़ोy taken */
अटल पूर्णांक __bnx2fc_disable(काष्ठा fcoe_ctlr *ctlr)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = fcoe_ctlr_priv(ctlr);

	अगर (पूर्णांकerface->enabled) अणु
		अगर (!ctlr->lp) अणु
			pr_err(PFX "__bnx2fc_disable: lport not found\n");
			वापस -ENODEV;
		पूर्ण अन्यथा अणु
			पूर्णांकerface->enabled = false;
			fcoe_ctlr_link_करोwn(ctlr);
			fcoe_clean_pending_queue(ctlr->lp);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Deperecated: Use bnx2fc_enabled()
 */
अटल पूर्णांक bnx2fc_disable(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	पूर्णांक rc = 0;

	rtnl_lock();
	mutex_lock(&bnx2fc_dev_lock);

	पूर्णांकerface = bnx2fc_पूर्णांकerface_lookup(netdev);
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);

	अगर (!पूर्णांकerface) अणु
		rc = -ENODEV;
		pr_err(PFX "bnx2fc_disable: interface not found\n");
	पूर्ण अन्यथा अणु
		rc = __bnx2fc_disable(ctlr);
	पूर्ण
	mutex_unlock(&bnx2fc_dev_lock);
	rtnl_unlock();
	वापस rc;
पूर्ण

अटल uपूर्णांक bnx2fc_npiv_create_vports(काष्ठा fc_lport *lport,
				      काष्ठा cnic_fc_npiv_tbl *npiv_tbl)
अणु
	काष्ठा fc_vport_identअगरiers vpid;
	uपूर्णांक i, created = 0;
	u64 wwnn = 0;
	अक्षर wwpn_str[32];
	अक्षर wwnn_str[32];

	अगर (npiv_tbl->count > MAX_NPIV_ENTRIES) अणु
		BNX2FC_HBA_DBG(lport, "Exceeded count max of npiv table\n");
		जाओ करोne;
	पूर्ण

	/* Sanity check the first entry to make sure it's not 0 */
	अगर (wwn_to_u64(npiv_tbl->wwnn[0]) == 0 &&
	    wwn_to_u64(npiv_tbl->wwpn[0]) == 0) अणु
		BNX2FC_HBA_DBG(lport, "First NPIV table entries invalid.\n");
		जाओ करोne;
	पूर्ण

	vpid.roles = FC_PORT_ROLE_FCP_INITIATOR;
	vpid.vport_type = FC_PORTTYPE_NPIV;
	vpid.disable = false;

	क्रम (i = 0; i < npiv_tbl->count; i++) अणु
		wwnn = wwn_to_u64(npiv_tbl->wwnn[i]);
		अगर (wwnn == 0) अणु
			/*
			 * If we get a 0 element from क्रम the WWNN then assume
			 * the WWNN should be the same as the physical port.
			 */
			wwnn = lport->wwnn;
		पूर्ण
		vpid.node_name = wwnn;
		vpid.port_name = wwn_to_u64(npiv_tbl->wwpn[i]);
		scnम_लिखो(vpid.symbolic_name, माप(vpid.symbolic_name),
		    "NPIV[%u]:%016llx-%016llx",
		    created, vpid.port_name, vpid.node_name);
		fcoe_wwn_to_str(vpid.node_name, wwnn_str, माप(wwnn_str));
		fcoe_wwn_to_str(vpid.port_name, wwpn_str, माप(wwpn_str));
		BNX2FC_HBA_DBG(lport, "Creating vport %s:%s.\n", wwnn_str,
		    wwpn_str);
		अगर (fc_vport_create(lport->host, 0, &vpid))
			created++;
		अन्यथा
			BNX2FC_HBA_DBG(lport, "Failed to create vport\n");
	पूर्ण
करोne:
	वापस created;
पूर्ण

अटल पूर्णांक __bnx2fc_enable(काष्ठा fcoe_ctlr *ctlr)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = fcoe_ctlr_priv(ctlr);
	काष्ठा bnx2fc_hba *hba;
	काष्ठा cnic_fc_npiv_tbl *npiv_tbl;
	काष्ठा fc_lport *lport;

	अगर (!पूर्णांकerface->enabled) अणु
		अगर (!ctlr->lp) अणु
			pr_err(PFX "__bnx2fc_enable: lport not found\n");
			वापस -ENODEV;
		पूर्ण अन्यथा अगर (!bnx2fc_link_ok(ctlr->lp)) अणु
			fcoe_ctlr_link_up(ctlr);
			पूर्णांकerface->enabled = true;
		पूर्ण
	पूर्ण

	/* Create अटल NPIV ports अगर any are contained in NVRAM */
	hba = पूर्णांकerface->hba;
	lport = ctlr->lp;

	अगर (!hba)
		जाओ करोne;

	अगर (!hba->cnic)
		जाओ करोne;

	अगर (!lport)
		जाओ करोne;

	अगर (!lport->host)
		जाओ करोne;

	अगर (!hba->cnic->get_fc_npiv_tbl)
		जाओ करोne;

	npiv_tbl = kzalloc(माप(काष्ठा cnic_fc_npiv_tbl), GFP_KERNEL);
	अगर (!npiv_tbl)
		जाओ करोne;

	अगर (hba->cnic->get_fc_npiv_tbl(hba->cnic, npiv_tbl))
		जाओ करोne_मुक्त;

	bnx2fc_npiv_create_vports(lport, npiv_tbl);
करोne_मुक्त:
	kमुक्त(npiv_tbl);
करोne:
	वापस 0;
पूर्ण

/*
 * Deprecated: Use bnx2fc_enabled()
 */
अटल पूर्णांक bnx2fc_enable(काष्ठा net_device *netdev)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा fcoe_ctlr *ctlr;
	पूर्णांक rc = 0;

	rtnl_lock();
	mutex_lock(&bnx2fc_dev_lock);

	पूर्णांकerface = bnx2fc_पूर्णांकerface_lookup(netdev);
	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	अगर (!पूर्णांकerface) अणु
		rc = -ENODEV;
		pr_err(PFX "bnx2fc_enable: interface not found\n");
	पूर्ण अन्यथा अणु
		rc = __bnx2fc_enable(ctlr);
	पूर्ण

	mutex_unlock(&bnx2fc_dev_lock);
	rtnl_unlock();
	वापस rc;
पूर्ण

/**
 * bnx2fc_ctlr_enabled() - Enable or disable an FCoE Controller
 * @cdev: The FCoE Controller that is being enabled or disabled
 *
 * fcoe_sysfs will ensure that the state of 'enabled' has
 * changed, so no checking is necessary here. This routine simply
 * calls fcoe_enable or fcoe_disable, both of which are deprecated.
 * When those routines are हटाओd the functionality can be merged
 * here.
 */
अटल पूर्णांक bnx2fc_ctlr_enabled(काष्ठा fcoe_ctlr_device *cdev)
अणु
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(cdev);

	चयन (cdev->enabled) अणु
	हाल FCOE_CTLR_ENABLED:
		वापस __bnx2fc_enable(ctlr);
	हाल FCOE_CTLR_DISABLED:
		वापस __bnx2fc_disable(ctlr);
	हाल FCOE_CTLR_UNUSED:
	शेष:
		वापस -ENOTSUPP;
	पूर्ण
पूर्ण

क्रमागत bnx2fc_create_link_state अणु
	BNX2FC_CREATE_LINK_DOWN,
	BNX2FC_CREATE_LINK_UP,
पूर्ण;

/**
 * _bnx2fc_create() - Create bnx2fc FCoE पूर्णांकerface
 * @netdev  :   The net_device object the Ethernet पूर्णांकerface to create on
 * @fip_mode:   The FIP mode क्रम this creation
 * @link_state: The ctlr link state on creation
 *
 * Called from either the libfcoe 'create' module parameter
 * via fcoe_create or from fcoe_syfs's ctlr_create file.
 *
 * libfcoe's 'create' module parameter is deprecated so some
 * consolidation of code can be करोne when that पूर्णांकerface is
 * हटाओd.
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक _bnx2fc_create(काष्ठा net_device *netdev,
			  क्रमागत fip_mode fip_mode,
			  क्रमागत bnx2fc_create_link_state link_state)
अणु
	काष्ठा fcoe_ctlr_device *cdev;
	काष्ठा fcoe_ctlr *ctlr;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;
	काष्ठा bnx2fc_hba *hba;
	काष्ठा net_device *phys_dev = netdev;
	काष्ठा fc_lport *lport;
	काष्ठा ethtool_drvinfo drvinfo;
	पूर्णांक rc = 0;
	पूर्णांक vlan_id = 0;

	BNX2FC_MISC_DBG("Entered bnx2fc_create\n");
	अगर (fip_mode != FIP_MODE_FABRIC) अणु
		prपूर्णांकk(KERN_ERR "fip mode not FABRIC\n");
		वापस -EIO;
	पूर्ण

	rtnl_lock();

	mutex_lock(&bnx2fc_dev_lock);

	अगर (!try_module_get(THIS_MODULE)) अणु
		rc = -EINVAL;
		जाओ mod_err;
	पूर्ण

	/* obtain physical netdev */
	अगर (is_vlan_dev(netdev))
		phys_dev = vlan_dev_real_dev(netdev);

	/* verअगरy अगर the physical device is a netxtreme2 device */
	अगर (phys_dev->ethtool_ops && phys_dev->ethtool_ops->get_drvinfo) अणु
		स_रखो(&drvinfo, 0, माप(drvinfo));
		phys_dev->ethtool_ops->get_drvinfo(phys_dev, &drvinfo);
		अगर (म_भेदन(drvinfo.driver, "bnx2x", म_माप("bnx2x"))) अणु
			prपूर्णांकk(KERN_ERR PFX "Not a netxtreme2 device\n");
			rc = -EINVAL;
			जाओ netdev_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR PFX "unable to obtain drv_info\n");
		rc = -EINVAL;
		जाओ netdev_err;
	पूर्ण

	/* obtain पूर्णांकerface and initialize rest of the काष्ठाure */
	hba = bnx2fc_hba_lookup(phys_dev);
	अगर (!hba) अणु
		rc = -ENODEV;
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_create: hba not found\n");
		जाओ netdev_err;
	पूर्ण

	अगर (bnx2fc_पूर्णांकerface_lookup(netdev)) अणु
		rc = -EEXIST;
		जाओ netdev_err;
	पूर्ण

	पूर्णांकerface = bnx2fc_पूर्णांकerface_create(hba, netdev, fip_mode);
	अगर (!पूर्णांकerface) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_interface_create failed\n");
		rc = -ENOMEM;
		जाओ netdev_err;
	पूर्ण

	अगर (is_vlan_dev(netdev)) अणु
		vlan_id = vlan_dev_vlan_id(netdev);
		पूर्णांकerface->vlan_enabled = 1;
	पूर्ण

	ctlr = bnx2fc_to_ctlr(पूर्णांकerface);
	cdev = fcoe_ctlr_to_ctlr_dev(ctlr);
	पूर्णांकerface->vlan_id = vlan_id;
	पूर्णांकerface->पंचांग_समयout = BNX2FC_TM_TIMEOUT;

	पूर्णांकerface->समयr_work_queue =
			create_singlethपढ़ो_workqueue("bnx2fc_timer_wq");
	अगर (!पूर्णांकerface->समयr_work_queue) अणु
		prपूर्णांकk(KERN_ERR PFX "ulp_init could not create timer_wq\n");
		rc = -EINVAL;
		जाओ अगरput_err;
	पूर्ण

	lport = bnx2fc_अगर_create(पूर्णांकerface, &cdev->dev, 0);
	अगर (!lport) अणु
		prपूर्णांकk(KERN_ERR PFX "Failed to create interface (%s)\n",
			netdev->name);
		rc = -EINVAL;
		जाओ अगर_create_err;
	पूर्ण

	/* Add पूर्णांकerface to अगर_list */
	list_add_tail(&पूर्णांकerface->list, &अगर_list);

	lport->boot_समय = jअगरfies;

	/* Make this master N_port */
	ctlr->lp = lport;

	अगर (link_state == BNX2FC_CREATE_LINK_UP)
		cdev->enabled = FCOE_CTLR_ENABLED;
	अन्यथा
		cdev->enabled = FCOE_CTLR_DISABLED;

	अगर (link_state == BNX2FC_CREATE_LINK_UP &&
	    !bnx2fc_link_ok(lport)) अणु
		fcoe_ctlr_link_up(ctlr);
		fc_host_port_type(lport->host) = FC_PORTTYPE_NPORT;
		set_bit(ADAPTER_STATE_READY, &पूर्णांकerface->hba->adapter_state);
	पूर्ण

	BNX2FC_HBA_DBG(lport, "create: START DISC\n");
	bnx2fc_start_disc(पूर्णांकerface);

	अगर (link_state == BNX2FC_CREATE_LINK_UP)
		पूर्णांकerface->enabled = true;

	/*
	 * Release from kref_init in bnx2fc_पूर्णांकerface_setup, on success
	 * lport should be holding a reference taken in bnx2fc_अगर_create
	 */
	bnx2fc_पूर्णांकerface_put(पूर्णांकerface);
	/* put netdev that was held जबतक calling dev_get_by_name */
	mutex_unlock(&bnx2fc_dev_lock);
	rtnl_unlock();
	वापस 0;

अगर_create_err:
	destroy_workqueue(पूर्णांकerface->समयr_work_queue);
अगरput_err:
	bnx2fc_net_cleanup(पूर्णांकerface);
	bnx2fc_पूर्णांकerface_put(पूर्णांकerface);
	जाओ mod_err;
netdev_err:
	module_put(THIS_MODULE);
mod_err:
	mutex_unlock(&bnx2fc_dev_lock);
	rtnl_unlock();
	वापस rc;
पूर्ण

/**
 * bnx2fc_create() - Create a bnx2fc पूर्णांकerface
 * @netdev  : The net_device object the Ethernet पूर्णांकerface to create on
 * @fip_mode: The FIP mode क्रम this creation
 *
 * Called from fcoe transport
 *
 * Returns: 0 क्रम success
 */
अटल पूर्णांक bnx2fc_create(काष्ठा net_device *netdev, क्रमागत fip_mode fip_mode)
अणु
	वापस _bnx2fc_create(netdev, fip_mode, BNX2FC_CREATE_LINK_UP);
पूर्ण

/**
 * bnx2fc_ctlr_alloc() - Allocate a bnx2fc पूर्णांकerface from fcoe_sysfs
 * @netdev: The net_device to be used by the allocated FCoE Controller
 *
 * This routine is called from fcoe_sysfs. It will start the fcoe_ctlr
 * in a link_करोwn state. The allows the user an opportunity to configure
 * the FCoE Controller from sysfs beक्रमe enabling the FCoE Controller.
 *
 * Creating in with this routine starts the FCoE Controller in Fabric
 * mode. The user can change to VN2VN or another mode beक्रमe enabling.
 */
अटल पूर्णांक bnx2fc_ctlr_alloc(काष्ठा net_device *netdev)
अणु
	वापस _bnx2fc_create(netdev, FIP_MODE_FABRIC,
			      BNX2FC_CREATE_LINK_DOWN);
पूर्ण

/**
 * bnx2fc_find_hba_क्रम_cnic - maps cnic instance to bnx2fc hba instance
 *
 * @cnic:	Poपूर्णांकer to cnic device instance
 *
 **/
अटल काष्ठा bnx2fc_hba *bnx2fc_find_hba_क्रम_cnic(काष्ठा cnic_dev *cnic)
अणु
	काष्ठा bnx2fc_hba *hba;

	/* Called with bnx2fc_dev_lock held */
	list_क्रम_each_entry(hba, &adapter_list, list) अणु
		अगर (hba->cnic == cnic)
			वापस hba;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2fc_पूर्णांकerface *bnx2fc_पूर्णांकerface_lookup(काष्ठा net_device
							*netdev)
अणु
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface;

	/* Called with bnx2fc_dev_lock held */
	list_क्रम_each_entry(पूर्णांकerface, &अगर_list, list) अणु
		अगर (पूर्णांकerface->netdev == netdev)
			वापस पूर्णांकerface;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा bnx2fc_hba *bnx2fc_hba_lookup(काष्ठा net_device
						      *phys_dev)
अणु
	काष्ठा bnx2fc_hba *hba;

	/* Called with bnx2fc_dev_lock held */
	list_क्रम_each_entry(hba, &adapter_list, list) अणु
		अगर (hba->phys_dev == phys_dev)
			वापस hba;
	पूर्ण
	prपूर्णांकk(KERN_ERR PFX "adapter_lookup: hba NULL\n");
	वापस शून्य;
पूर्ण

/**
 * bnx2fc_ulp_निकास - shuts करोwn adapter instance and मुक्तs all resources
 *
 * @dev:	cnic device handle
 */
अटल व्योम bnx2fc_ulp_निकास(काष्ठा cnic_dev *dev)
अणु
	काष्ठा bnx2fc_hba *hba;
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface, *पंचांगp;

	BNX2FC_MISC_DBG("Entered bnx2fc_ulp_exit\n");

	अगर (!test_bit(CNIC_F_BNX2X_CLASS, &dev->flags)) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc port check: %s, flags: %lx\n",
			dev->netdev->name, dev->flags);
		वापस;
	पूर्ण

	mutex_lock(&bnx2fc_dev_lock);
	hba = bnx2fc_find_hba_क्रम_cnic(dev);
	अगर (!hba) अणु
		prपूर्णांकk(KERN_ERR PFX "bnx2fc_ulp_exit: hba not found, dev 0%p\n",
		       dev);
		mutex_unlock(&bnx2fc_dev_lock);
		वापस;
	पूर्ण

	list_del_init(&hba->list);
	adapter_count--;

	list_क्रम_each_entry_safe(पूर्णांकerface, पंचांगp, &अगर_list, list)
		/* destroy not called yet, move to quiesced list */
		अगर (पूर्णांकerface->hba == hba)
			__bnx2fc_destroy(पूर्णांकerface);
	mutex_unlock(&bnx2fc_dev_lock);

	/* Ensure ALL destroy work has been completed beक्रमe वापस */
	flush_workqueue(bnx2fc_wq);

	bnx2fc_ulp_stop(hba);
	/* unरेजिस्टर cnic device */
	अगर (test_and_clear_bit(BNX2FC_CNIC_REGISTERED, &hba->reg_with_cnic))
		hba->cnic->unरेजिस्टर_device(hba->cnic, CNIC_ULP_FCOE);
	bnx2fc_hba_destroy(hba);
पूर्ण

अटल व्योम bnx2fc_rport_terminate_io(काष्ठा fc_rport *rport)
अणु
	/* This is a no-op */
पूर्ण

/**
 * bnx2fc_fcoe_reset - Resets the fcoe
 *
 * @shost: shost the reset is from
 *
 * Returns: always 0
 */
अटल पूर्णांक bnx2fc_fcoe_reset(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);
	fc_lport_reset(lport);
	वापस 0;
पूर्ण


अटल bool bnx2fc_match(काष्ठा net_device *netdev)
अणु
	काष्ठा net_device *phys_dev = netdev;

	mutex_lock(&bnx2fc_dev_lock);
	अगर (is_vlan_dev(netdev))
		phys_dev = vlan_dev_real_dev(netdev);

	अगर (bnx2fc_hba_lookup(phys_dev)) अणु
		mutex_unlock(&bnx2fc_dev_lock);
		वापस true;
	पूर्ण

	mutex_unlock(&bnx2fc_dev_lock);
	वापस false;
पूर्ण


अटल काष्ठा fcoe_transport bnx2fc_transport = अणु
	.name = अणु"bnx2fc"पूर्ण,
	.attached = false,
	.list = LIST_HEAD_INIT(bnx2fc_transport.list),
	.alloc = bnx2fc_ctlr_alloc,
	.match = bnx2fc_match,
	.create = bnx2fc_create,
	.destroy = bnx2fc_destroy,
	.enable = bnx2fc_enable,
	.disable = bnx2fc_disable,
पूर्ण;

/**
 * bnx2fc_cpu_online - Create a receive thपढ़ो क्रम an  online CPU
 *
 * @cpu: cpu index क्रम the online cpu
 */
अटल पूर्णांक bnx2fc_cpu_online(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा bnx2fc_percpu_s *p;
	काष्ठा task_काष्ठा *thपढ़ो;

	p = &per_cpu(bnx2fc_percpu, cpu);

	thपढ़ो = kthपढ़ो_create_on_node(bnx2fc_percpu_io_thपढ़ो,
					(व्योम *)p, cpu_to_node(cpu),
					"bnx2fc_thread/%d", cpu);
	अगर (IS_ERR(thपढ़ो))
		वापस PTR_ERR(thपढ़ो);

	/* bind thपढ़ो to the cpu */
	kthपढ़ो_bind(thपढ़ो, cpu);
	p->iothपढ़ो = thपढ़ो;
	wake_up_process(thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_cpu_offline(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा bnx2fc_percpu_s *p;
	काष्ठा task_काष्ठा *thपढ़ो;
	काष्ठा bnx2fc_work *work, *पंचांगp;

	BNX2FC_MISC_DBG("destroying io thread for CPU %d\n", cpu);

	/* Prevent any new work from being queued क्रम this CPU */
	p = &per_cpu(bnx2fc_percpu, cpu);
	spin_lock_bh(&p->fp_work_lock);
	thपढ़ो = p->iothपढ़ो;
	p->iothपढ़ो = शून्य;

	/* Free all work in the list */
	list_क्रम_each_entry_safe(work, पंचांगp, &p->work_list, list) अणु
		list_del_init(&work->list);
		bnx2fc_process_cq_compl(work->tgt, work->wqe, work->rq_data,
					work->num_rq, work->task);
		kमुक्त(work);
	पूर्ण

	spin_unlock_bh(&p->fp_work_lock);

	अगर (thपढ़ो)
		kthपढ़ो_stop(thपढ़ो);
	वापस 0;
पूर्ण

अटल पूर्णांक bnx2fc_slave_configure(काष्ठा scsi_device *sdev)
अणु
	अगर (!bnx2fc_queue_depth)
		वापस 0;

	scsi_change_queue_depth(sdev, bnx2fc_queue_depth);
	वापस 0;
पूर्ण

अटल क्रमागत cpuhp_state bnx2fc_online_state;

/**
 * bnx2fc_mod_init - module init entry poपूर्णांक
 *
 * Initialize driver wide global data काष्ठाures, and रेजिस्टर
 * with cnic module
 **/
अटल पूर्णांक __init bnx2fc_mod_init(व्योम)
अणु
	काष्ठा fcoe_percpu_s *bg;
	काष्ठा task_काष्ठा *l2_thपढ़ो;
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक cpu = 0;
	काष्ठा bnx2fc_percpu_s *p;

	prपूर्णांकk(KERN_INFO PFX "%s", version);

	/* रेजिस्टर as a fcoe transport */
	rc = fcoe_transport_attach(&bnx2fc_transport);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR "failed to register an fcoe transport, check "
			"if libfcoe is loaded\n");
		जाओ out;
	पूर्ण

	INIT_LIST_HEAD(&adapter_list);
	INIT_LIST_HEAD(&अगर_list);
	mutex_init(&bnx2fc_dev_lock);
	adapter_count = 0;

	/* Attach FC transport ढाँचा */
	rc = bnx2fc_attach_transport();
	अगर (rc)
		जाओ detach_ft;

	bnx2fc_wq = alloc_workqueue("bnx2fc", 0, 0);
	अगर (!bnx2fc_wq) अणु
		rc = -ENOMEM;
		जाओ release_bt;
	पूर्ण

	bg = &bnx2fc_global;
	skb_queue_head_init(&bg->fcoe_rx_list);
	l2_thपढ़ो = kthपढ़ो_create(bnx2fc_l2_rcv_thपढ़ो,
				   (व्योम *)bg,
				   "bnx2fc_l2_thread");
	अगर (IS_ERR(l2_thपढ़ो)) अणु
		rc = PTR_ERR(l2_thपढ़ो);
		जाओ मुक्त_wq;
	पूर्ण
	wake_up_process(l2_thपढ़ो);
	spin_lock_bh(&bg->fcoe_rx_list.lock);
	bg->kthपढ़ो = l2_thपढ़ो;
	spin_unlock_bh(&bg->fcoe_rx_list.lock);

	क्रम_each_possible_cpu(cpu) अणु
		p = &per_cpu(bnx2fc_percpu, cpu);
		INIT_LIST_HEAD(&p->work_list);
		spin_lock_init(&p->fp_work_lock);
	पूर्ण

	rc = cpuhp_setup_state(CPUHP_AP_ONLINE_DYN, "scsi/bnx2fc:online",
			       bnx2fc_cpu_online, bnx2fc_cpu_offline);
	अगर (rc < 0)
		जाओ stop_thपढ़ो;
	bnx2fc_online_state = rc;

	cnic_रेजिस्टर_driver(CNIC_ULP_FCOE, &bnx2fc_cnic_cb);
	वापस 0;

stop_thपढ़ो:
	kthपढ़ो_stop(l2_thपढ़ो);
मुक्त_wq:
	destroy_workqueue(bnx2fc_wq);
release_bt:
	bnx2fc_release_transport();
detach_ft:
	fcoe_transport_detach(&bnx2fc_transport);
out:
	वापस rc;
पूर्ण

अटल व्योम __निकास bnx2fc_mod_निकास(व्योम)
अणु
	LIST_HEAD(to_be_deleted);
	काष्ठा bnx2fc_hba *hba, *next;
	काष्ठा fcoe_percpu_s *bg;
	काष्ठा task_काष्ठा *l2_thपढ़ो;
	काष्ठा sk_buff *skb;

	/*
	 * NOTE: Since cnic calls रेजिस्टर_driver routine rtnl_lock,
	 * it will have higher precedence than bnx2fc_dev_lock.
	 * unरेजिस्टर_device() cannot be called with bnx2fc_dev_lock
	 * held.
	 */
	mutex_lock(&bnx2fc_dev_lock);
	list_splice_init(&adapter_list, &to_be_deleted);
	adapter_count = 0;
	mutex_unlock(&bnx2fc_dev_lock);

	/* Unरेजिस्टर with cnic */
	list_क्रम_each_entry_safe(hba, next, &to_be_deleted, list) अणु
		list_del_init(&hba->list);
		prपूर्णांकk(KERN_ERR PFX "MOD_EXIT:destroy hba = 0x%p\n",
		       hba);
		bnx2fc_ulp_stop(hba);
		/* unरेजिस्टर cnic device */
		अगर (test_and_clear_bit(BNX2FC_CNIC_REGISTERED,
				       &hba->reg_with_cnic))
			hba->cnic->unरेजिस्टर_device(hba->cnic,
							 CNIC_ULP_FCOE);
		bnx2fc_hba_destroy(hba);
	पूर्ण
	cnic_unरेजिस्टर_driver(CNIC_ULP_FCOE);

	/* Destroy global thपढ़ो */
	bg = &bnx2fc_global;
	spin_lock_bh(&bg->fcoe_rx_list.lock);
	l2_thपढ़ो = bg->kthपढ़ो;
	bg->kthपढ़ो = शून्य;
	जबतक ((skb = __skb_dequeue(&bg->fcoe_rx_list)) != शून्य)
		kमुक्त_skb(skb);

	spin_unlock_bh(&bg->fcoe_rx_list.lock);

	अगर (l2_thपढ़ो)
		kthपढ़ो_stop(l2_thपढ़ो);

	cpuhp_हटाओ_state(bnx2fc_online_state);

	destroy_workqueue(bnx2fc_wq);
	/*
	 * detach from scsi transport
	 * must happen after all destroys are करोne
	 */
	bnx2fc_release_transport();

	/* detach from fcoe transport */
	fcoe_transport_detach(&bnx2fc_transport);
पूर्ण

module_init(bnx2fc_mod_init);
module_निकास(bnx2fc_mod_निकास);

अटल काष्ठा fcoe_sysfs_function_ढाँचा bnx2fc_fcoe_sysfs_templ = अणु
	.set_fcoe_ctlr_enabled = bnx2fc_ctlr_enabled,
	.get_fcoe_ctlr_link_fail = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_vlink_fail = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_miss_fka = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_symb_err = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_err_block = fcoe_ctlr_get_lesb,
	.get_fcoe_ctlr_fcs_error = fcoe_ctlr_get_lesb,

	.get_fcoe_fcf_selected = fcoe_fcf_get_selected,
	.get_fcoe_fcf_vlan_id = bnx2fc_fcf_get_vlan_id,
पूर्ण;

अटल काष्ठा fc_function_ढाँचा bnx2fc_transport_function = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_active_fc4s = 1,
	.show_host_maxframe_size = 1,

	.show_host_port_id = 1,
	.show_host_supported_speeds = 1,
	.get_host_speed = fc_get_host_speed,
	.show_host_speed = 1,
	.show_host_port_type = 1,
	.get_host_port_state = fc_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,

	.dd_fcrport_size = (माप(काष्ठा fc_rport_libfc_priv) +
				माप(काष्ठा bnx2fc_rport)),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = fc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.get_fc_host_stats = bnx2fc_get_host_stats,

	.issue_fc_host_lip = bnx2fc_fcoe_reset,

	.terminate_rport_io = bnx2fc_rport_terminate_io,

	.vport_create = bnx2fc_vport_create,
	.vport_delete = bnx2fc_vport_destroy,
	.vport_disable = bnx2fc_vport_disable,
	.bsg_request = fc_lport_bsg_request,
पूर्ण;

अटल काष्ठा fc_function_ढाँचा bnx2fc_vport_xport_function = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_active_fc4s = 1,
	.show_host_maxframe_size = 1,

	.show_host_port_id = 1,
	.show_host_supported_speeds = 1,
	.get_host_speed = fc_get_host_speed,
	.show_host_speed = 1,
	.show_host_port_type = 1,
	.get_host_port_state = fc_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,

	.dd_fcrport_size = (माप(काष्ठा fc_rport_libfc_priv) +
				माप(काष्ठा bnx2fc_rport)),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,

	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = fc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.get_fc_host_stats = fc_get_host_stats,
	.issue_fc_host_lip = bnx2fc_fcoe_reset,
	.terminate_rport_io = fc_rport_terminate_io,
	.bsg_request = fc_lport_bsg_request,
पूर्ण;

/*
 * Additional scsi_host attributes.
 */
अटल sमाप_प्रकार
bnx2fc_पंचांग_समयout_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
	अक्षर *buf)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;

	प्र_लिखो(buf, "%u\n", पूर्णांकerface->पंचांग_समयout);
	वापस म_माप(buf);
पूर्ण

अटल sमाप_प्रकार
bnx2fc_पंचांग_समयout_store(काष्ठा device *dev,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा Scsi_Host *shost = class_to_shost(dev);
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा fcoe_port *port = lport_priv(lport);
	काष्ठा bnx2fc_पूर्णांकerface *पूर्णांकerface = port->priv;
	पूर्णांक rval, val;

	rval = kstrtouपूर्णांक(buf, 10, &val);
	अगर (rval)
		वापस rval;
	अगर (val > 255)
		वापस -दुस्फल;

	पूर्णांकerface->पंचांग_समयout = (u8)val;
	वापस म_माप(buf);
पूर्ण

अटल DEVICE_ATTR(पंचांग_समयout, S_IRUGO|S_IWUSR, bnx2fc_पंचांग_समयout_show,
	bnx2fc_पंचांग_समयout_store);

अटल काष्ठा device_attribute *bnx2fc_host_attrs[] = अणु
	&dev_attr_पंचांग_समयout,
	शून्य,
पूर्ण;

/*
 * scsi_host_ढाँचा काष्ठाure used जबतक रेजिस्टरing with SCSI-ml
 */
अटल काष्ठा scsi_host_ढाँचा bnx2fc_shost_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "QLogic Offload FCoE Initiator",
	.queuecommand		= bnx2fc_queuecommand,
	.eh_समयd_out		= fc_eh_समयd_out,
	.eh_पात_handler	= bnx2fc_eh_पात,	  /* abts */
	.eh_device_reset_handler = bnx2fc_eh_device_reset, /* lun reset */
	.eh_target_reset_handler = bnx2fc_eh_target_reset, /* tgt reset */
	.eh_host_reset_handler	= fc_eh_host_reset,
	.slave_alloc		= fc_slave_alloc,
	.change_queue_depth	= scsi_change_queue_depth,
	.this_id		= -1,
	.cmd_per_lun		= 3,
	.sg_tablesize		= BNX2FC_MAX_BDS_PER_CMD,
	.dma_boundary           = 0x7fff,
	.max_sectors		= 0x3fbf,
	.track_queue_depth	= 1,
	.slave_configure	= bnx2fc_slave_configure,
	.shost_attrs		= bnx2fc_host_attrs,
पूर्ण;

अटल काष्ठा libfc_function_ढाँचा bnx2fc_libfc_fcn_templ = अणु
	.frame_send		= bnx2fc_xmit,
	.elsct_send		= bnx2fc_elsct_send,
	.fcp_पात_io		= bnx2fc_पात_io,
	.fcp_cleanup		= bnx2fc_cleanup,
	.get_lesb		= fcoe_get_lesb,
	.rport_event_callback	= bnx2fc_rport_event_handler,
पूर्ण;

/*
 * bnx2fc_cnic_cb - global ढाँचा of bnx2fc - cnic driver पूर्णांकerface
 *			काष्ठाure carrying callback function poपूर्णांकers
 */
अटल काष्ठा cnic_ulp_ops bnx2fc_cnic_cb = अणु
	.owner			= THIS_MODULE,
	.cnic_init		= bnx2fc_ulp_init,
	.cnic_निकास		= bnx2fc_ulp_निकास,
	.cnic_start		= bnx2fc_ulp_start,
	.cnic_stop		= bnx2fc_ulp_stop,
	.indicate_kcqes		= bnx2fc_indicate_kcqe,
	.indicate_netevent	= bnx2fc_indicate_netevent,
	.cnic_get_stats		= bnx2fc_ulp_get_stats,
पूर्ण;
