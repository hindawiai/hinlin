<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश "qedf.h"

बाह्य स्थिर काष्ठा qed_fcoe_ops *qed_ops;
/*
 * FIP VLAN functions that will eventually move to libfcoe.
 */

व्योम qedf_fcoe_send_vlan_req(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा sk_buff *skb;
	अक्षर *eth_fr;
	काष्ठा fip_vlan *vlan;
#घोषणा MY_FIP_ALL_FCF_MACS        ((__u8[6]) अणु 1, 0x10, 0x18, 1, 0, 2 पूर्ण)
	अटल u8 my_fcoe_all_fcfs[ETH_ALEN] = MY_FIP_ALL_FCF_MACS;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rc;

	skb = dev_alloc_skb(माप(काष्ठा fip_vlan));
	अगर (!skb) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Failed to allocate skb.\n");
		वापस;
	पूर्ण

	eth_fr = (अक्षर *)skb->data;
	vlan = (काष्ठा fip_vlan *)eth_fr;

	स_रखो(vlan, 0, माप(*vlan));
	ether_addr_copy(vlan->eth.h_source, qedf->mac);
	ether_addr_copy(vlan->eth.h_dest, my_fcoe_all_fcfs);
	vlan->eth.h_proto = htons(ETH_P_FIP);

	vlan->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	vlan->fip.fip_op = htons(FIP_OP_VLAN);
	vlan->fip.fip_subcode = FIP_SC_VL_REQ;
	vlan->fip.fip_dl_len = htons(माप(vlan->desc) / FIP_BPW);

	vlan->desc.mac.fd_desc.fip_dtype = FIP_DT_MAC;
	vlan->desc.mac.fd_desc.fip_dlen = माप(vlan->desc.mac) / FIP_BPW;
	ether_addr_copy(vlan->desc.mac.fd_mac, qedf->mac);

	vlan->desc.wwnn.fd_desc.fip_dtype = FIP_DT_NAME;
	vlan->desc.wwnn.fd_desc.fip_dlen = माप(vlan->desc.wwnn) / FIP_BPW;
	put_unaligned_be64(qedf->lport->wwnn, &vlan->desc.wwnn.fd_wwn);

	skb_put(skb, माप(*vlan));
	skb->protocol = htons(ETH_P_FIP);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Sending FIP VLAN "
		   "request.");

	अगर (atomic_पढ़ो(&qedf->link_state) != QEDF_LINK_UP) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Cannot send vlan request "
		    "because link is not up.\n");

		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	set_bit(QED_LL2_XMIT_FLAGS_FIP_DISCOVERY, &flags);
	rc = qed_ops->ll2->start_xmit(qedf->cdev, skb, flags);
	अगर (rc) अणु
		QEDF_ERR(&qedf->dbg_ctx, "start_xmit failed rc = %d.\n", rc);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

पूर्ण

अटल व्योम qedf_fcoe_process_vlan_resp(काष्ठा qedf_ctx *qedf,
	काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_header *fiph;
	काष्ठा fip_desc *desc;
	u16 vid = 0;
	sमाप_प्रकार rlen;
	माप_प्रकार dlen;

	fiph = (काष्ठा fip_header *)(((व्योम *)skb->data) + 2 * ETH_ALEN + 2);

	rlen = ntohs(fiph->fip_dl_len) * 4;
	desc = (काष्ठा fip_desc *)(fiph + 1);
	जबतक (rlen > 0) अणु
		dlen = desc->fip_dlen * FIP_BPW;
		चयन (desc->fip_dtype) अणु
		हाल FIP_DT_VLAN:
			vid = ntohs(((काष्ठा fip_vlan_desc *)desc)->fd_vlan);
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण

	अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_DOWN) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
			  "Dropping VLAN response as link is down.\n");
		वापस;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "VLAN response, "
		   "vid=0x%x.\n", vid);

	अगर (vid > 0 && qedf->vlan_id != vid) अणु
		qedf_set_vlan_id(qedf, vid);

		/* Inक्रमm रुकोer that it's ok to call fcoe_ctlr_link up() */
		अगर (!completion_करोne(&qedf->fipvlan_compl))
			complete(&qedf->fipvlan_compl);
	पूर्ण
पूर्ण

व्योम qedf_fip_send(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा qedf_ctx *qedf = container_of(fip, काष्ठा qedf_ctx, ctlr);
	काष्ठा ethhdr *eth_hdr;
	काष्ठा fip_header *fiph;
	u16 op, vlan_tci = 0;
	u8 sub;
	पूर्णांक rc = -1;

	अगर (!test_bit(QEDF_LL2_STARTED, &qedf->flags)) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "LL2 not started\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	fiph = (काष्ठा fip_header *) ((व्योम *)skb->data + 2 * ETH_ALEN + 2);
	eth_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	/*
	 * Add VLAN tag to non-offload FIP frame based on current stored VLAN
	 * क्रम FIP/FCoE traffic.
	 */
	__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), qedf->vlan_id);

	/* Get VLAN ID from skb क्रम prपूर्णांकing purposes */
	__vlan_hwaccel_get_tag(skb, &vlan_tci);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2, "FIP frame send: "
	    "dest=%pM op=%x sub=%x vlan=%04x.", eth_hdr->h_dest, op, sub,
	    vlan_tci);
	अगर (qedf_dump_frames)
		prपूर्णांक_hex_dump(KERN_WARNING, "fip ", DUMP_PREFIX_OFFSET, 16, 1,
		    skb->data, skb->len, false);

	rc = qed_ops->ll2->start_xmit(qedf->cdev, skb, 0);
	अगर (rc) अणु
		QEDF_ERR(&qedf->dbg_ctx, "start_xmit failed rc = %d.\n", rc);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
पूर्ण

अटल u8 fcoe_all_enode[ETH_ALEN] = FIP_ALL_ENODE_MACS;

/* Process incoming FIP frames. */
व्योम qedf_fip_recv(काष्ठा qedf_ctx *qedf, काष्ठा sk_buff *skb)
अणु
	काष्ठा ethhdr *eth_hdr;
	काष्ठा fip_header *fiph;
	काष्ठा fip_desc *desc;
	काष्ठा fip_mac_desc *mp;
	काष्ठा fip_wwn_desc *wp;
	काष्ठा fip_vn_desc *vp;
	माप_प्रकार rlen, dlen;
	u16 op;
	u8 sub;
	bool fcf_valid = false;
	/* Default is to handle CVL regardless of fabric id descriptor */
	bool fabric_id_valid = true;
	bool fc_wwpn_valid = false;
	u64 चयन_name;
	u16 vlan = 0;

	eth_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
	fiph = (काष्ठा fip_header *) ((व्योम *)skb->data + 2 * ETH_ALEN + 2);
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_LL2,
		  "FIP frame received: skb=%p fiph=%p source=%pM destn=%pM op=%x sub=%x vlan=%04x",
		  skb, fiph, eth_hdr->h_source, eth_hdr->h_dest, op,
		  sub, vlan);
	अगर (qedf_dump_frames)
		prपूर्णांक_hex_dump(KERN_WARNING, "fip ", DUMP_PREFIX_OFFSET, 16, 1,
		    skb->data, skb->len, false);

	अगर (!ether_addr_equal(eth_hdr->h_dest, qedf->mac) &&
	    !ether_addr_equal(eth_hdr->h_dest, fcoe_all_enode) &&
		!ether_addr_equal(eth_hdr->h_dest, qedf->data_src_addr)) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_LL2,
			  "Dropping FIP type 0x%x pkt due to destination MAC mismatch dest_mac=%pM ctlr.dest_addr=%pM data_src_addr=%pM.\n",
			  op, eth_hdr->h_dest, qedf->mac,
			  qedf->data_src_addr);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* Handle FIP VLAN resp in the driver */
	अगर (op == FIP_OP_VLAN && sub == FIP_SC_VL_NOTE) अणु
		qedf_fcoe_process_vlan_resp(qedf, skb);
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अगर (op == FIP_OP_CTRL && sub == FIP_SC_CLR_VLINK) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Clear virtual "
			   "link received.\n");

		/* Check that an FCF has been selected by fcoe */
		अगर (qedf->ctlr.sel_fcf == शून्य) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Dropping CVL since FCF has not been selected "
			    "yet.");
			kमुक्त_skb(skb);
			वापस;
		पूर्ण

		/*
		 * We need to loop through the CVL descriptors to determine
		 * अगर we want to reset the fcoe link
		 */
		rlen = ntohs(fiph->fip_dl_len) * FIP_BPW;
		desc = (काष्ठा fip_desc *)(fiph + 1);
		जबतक (rlen >= माप(*desc)) अणु
			dlen = desc->fip_dlen * FIP_BPW;
			चयन (desc->fip_dtype) अणु
			हाल FIP_DT_MAC:
				mp = (काष्ठा fip_mac_desc *)desc;
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
					  "Switch fd_mac=%pM.\n", mp->fd_mac);
				अगर (ether_addr_equal(mp->fd_mac,
				    qedf->ctlr.sel_fcf->fcf_mac))
					fcf_valid = true;
				अवरोध;
			हाल FIP_DT_NAME:
				wp = (काष्ठा fip_wwn_desc *)desc;
				चयन_name = get_unaligned_be64(&wp->fd_wwn);
				QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
					  "Switch fd_wwn=%016llx fcf_switch_name=%016llx.\n",
					  चयन_name,
					  qedf->ctlr.sel_fcf->चयन_name);
				अगर (चयन_name ==
				    qedf->ctlr.sel_fcf->चयन_name)
					fc_wwpn_valid = true;
				अवरोध;
			हाल FIP_DT_VN_ID:
				fabric_id_valid = false;
				vp = (काष्ठा fip_vn_desc *)desc;

				QEDF_ERR(&qedf->dbg_ctx,
					 "CVL vx_port fd_fc_id=0x%x fd_mac=%pM fd_wwpn=%016llx.\n",
					 ntoh24(vp->fd_fc_id), vp->fd_mac,
					 get_unaligned_be64(&vp->fd_wwpn));
				/* Check क्रम vx_port wwpn OR Check vx_port
				 * fabric ID OR Check vx_port MAC
				 */
				अगर ((get_unaligned_be64(&vp->fd_wwpn) ==
					qedf->wwpn) ||
				   (ntoh24(vp->fd_fc_id) ==
					qedf->lport->port_id) ||
				   (ether_addr_equal(vp->fd_mac,
					qedf->data_src_addr))) अणु
					fabric_id_valid = true;
				पूर्ण
				अवरोध;
			शेष:
				/* Ignore anything अन्यथा */
				अवरोध;
			पूर्ण
			desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
			rlen -= dlen;
		पूर्ण

		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
			  "fcf_valid=%d fabric_id_valid=%d fc_wwpn_valid=%d.\n",
			  fcf_valid, fabric_id_valid, fc_wwpn_valid);
		अगर (fcf_valid && fabric_id_valid && fc_wwpn_valid)
			qedf_ctx_soft_reset(qedf->lport);
		kमुक्त_skb(skb);
	पूर्ण अन्यथा अणु
		/* Everything अन्यथा is handled by libfcoe */
		__skb_pull(skb, ETH_HLEN);
		fcoe_ctlr_recv(&qedf->ctlr, skb);
	पूर्ण
पूर्ण

u8 *qedf_get_src_mac(काष्ठा fc_lport *lport)
अणु
	काष्ठा qedf_ctx *qedf = lport_priv(lport);

	वापस qedf->data_src_addr;
पूर्ण
