<शैली गुरु>
/*
 * Copyright 2008 Cisco Systems, Inc.  All rights reserved.
 * Copyright 2007 Nuova Systems, Inc.  All rights reserved.
 *
 * This program is मुक्त software; you may redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
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
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/workqueue.h>
#समावेश <scsi/fc/fc_fip.h>
#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <scsi/fc_frame.h>
#समावेश <scsi/libfc.h>
#समावेश "fnic_io.h"
#समावेश "fnic.h"
#समावेश "fnic_fip.h"
#समावेश "cq_enet_desc.h"
#समावेश "cq_exch_desc.h"

अटल u8 fcoe_all_fcfs[ETH_ALEN] = FIP_ALL_FCF_MACS;
काष्ठा workqueue_काष्ठा *fnic_fip_queue;
काष्ठा workqueue_काष्ठा *fnic_event_queue;

अटल व्योम fnic_set_eth_mode(काष्ठा fnic *);
अटल व्योम fnic_fcoe_send_vlan_req(काष्ठा fnic *fnic);
अटल व्योम fnic_fcoe_start_fcf_disc(काष्ठा fnic *fnic);
अटल व्योम fnic_fcoe_process_vlan_resp(काष्ठा fnic *fnic, काष्ठा sk_buff *);
अटल पूर्णांक fnic_fcoe_vlan_check(काष्ठा fnic *fnic, u16 flag);
अटल पूर्णांक fnic_fcoe_handle_fip_frame(काष्ठा fnic *fnic, काष्ठा sk_buff *skb);

व्योम fnic_handle_link(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fnic *fnic = container_of(work, काष्ठा fnic, link_work);
	अचिन्हित दीर्घ flags;
	पूर्णांक old_link_status;
	u32 old_link_करोwn_cnt;
	u64 old_port_speed, new_port_speed;

	spin_lock_irqsave(&fnic->fnic_lock, flags);

	fnic->link_events = 1;      /* less work to just set everyसमय*/

	अगर (fnic->stop_rx_link_events) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस;
	पूर्ण

	old_link_करोwn_cnt = fnic->link_करोwn_cnt;
	old_link_status = fnic->link_status;
	old_port_speed = atomic64_पढ़ो(
			&fnic->fnic_stats.misc_stats.current_port_speed);

	fnic->link_status = vnic_dev_link_status(fnic->vdev);
	fnic->link_करोwn_cnt = vnic_dev_link_करोwn_cnt(fnic->vdev);

	new_port_speed = vnic_dev_port_speed(fnic->vdev);
	atomic64_set(&fnic->fnic_stats.misc_stats.current_port_speed,
			new_port_speed);
	अगर (old_port_speed != new_port_speed)
		FNIC_MAIN_DBG(KERN_INFO, fnic->lport->host,
				"Current vnic speed set to :  %llu\n",
				new_port_speed);

	चयन (vnic_dev_port_speed(fnic->vdev)) अणु
	हाल DCEM_PORTSPEED_10G:
		fc_host_speed(fnic->lport->host)   = FC_PORTSPEED_10GBIT;
		fnic->lport->link_supported_speeds = FC_PORTSPEED_10GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_20G:
		fc_host_speed(fnic->lport->host)   = FC_PORTSPEED_20GBIT;
		fnic->lport->link_supported_speeds = FC_PORTSPEED_20GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_25G:
		fc_host_speed(fnic->lport->host)   = FC_PORTSPEED_25GBIT;
		fnic->lport->link_supported_speeds = FC_PORTSPEED_25GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_40G:
	हाल DCEM_PORTSPEED_4x10G:
		fc_host_speed(fnic->lport->host)   = FC_PORTSPEED_40GBIT;
		fnic->lport->link_supported_speeds = FC_PORTSPEED_40GBIT;
		अवरोध;
	हाल DCEM_PORTSPEED_100G:
		fc_host_speed(fnic->lport->host)   = FC_PORTSPEED_100GBIT;
		fnic->lport->link_supported_speeds = FC_PORTSPEED_100GBIT;
		अवरोध;
	शेष:
		fc_host_speed(fnic->lport->host)   = FC_PORTSPEED_UNKNOWN;
		fnic->lport->link_supported_speeds = FC_PORTSPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	अगर (old_link_status == fnic->link_status) अणु
		अगर (!fnic->link_status) अणु
			/* DOWN -> DOWN */
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			fnic_fc_trace_set_data(fnic->lport->host->host_no,
				FNIC_FC_LE, "Link Status: DOWN->DOWN",
				म_माप("Link Status: DOWN->DOWN"));
		पूर्ण अन्यथा अणु
			अगर (old_link_करोwn_cnt != fnic->link_करोwn_cnt) अणु
				/* UP -> DOWN -> UP */
				fnic->lport->host_stats.link_failure_count++;
				spin_unlock_irqrestore(&fnic->fnic_lock, flags);
				fnic_fc_trace_set_data(
					fnic->lport->host->host_no,
					FNIC_FC_LE,
					"Link Status:UP_DOWN_UP",
					म_माप("Link_Status:UP_DOWN_UP")
					);
				FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
					     "link down\n");
				fcoe_ctlr_link_करोwn(&fnic->ctlr);
				अगर (fnic->config.flags & VFCF_FIP_CAPABLE) अणु
					/* start FCoE VLAN discovery */
					fnic_fc_trace_set_data(
						fnic->lport->host->host_no,
						FNIC_FC_LE,
						"Link Status: UP_DOWN_UP_VLAN",
						म_माप(
						"Link Status: UP_DOWN_UP_VLAN")
						);
					fnic_fcoe_send_vlan_req(fnic);
					वापस;
				पूर्ण
				FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
					     "link up\n");
				fcoe_ctlr_link_up(&fnic->ctlr);
			पूर्ण अन्यथा अणु
				/* UP -> UP */
				spin_unlock_irqrestore(&fnic->fnic_lock, flags);
				fnic_fc_trace_set_data(
					fnic->lport->host->host_no, FNIC_FC_LE,
					"Link Status: UP_UP",
					म_माप("Link Status: UP_UP"));
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (fnic->link_status) अणु
		/* DOWN -> UP */
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		अगर (fnic->config.flags & VFCF_FIP_CAPABLE) अणु
			/* start FCoE VLAN discovery */
				fnic_fc_trace_set_data(
				fnic->lport->host->host_no,
				FNIC_FC_LE, "Link Status: DOWN_UP_VLAN",
				म_माप("Link Status: DOWN_UP_VLAN"));
			fnic_fcoe_send_vlan_req(fnic);
			वापस;
		पूर्ण
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host, "link up\n");
		fnic_fc_trace_set_data(fnic->lport->host->host_no, FNIC_FC_LE,
			"Link Status: DOWN_UP", म_माप("Link Status: DOWN_UP"));
		fcoe_ctlr_link_up(&fnic->ctlr);
	पूर्ण अन्यथा अणु
		/* UP -> DOWN */
		fnic->lport->host_stats.link_failure_count++;
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host, "link down\n");
		fnic_fc_trace_set_data(
			fnic->lport->host->host_no, FNIC_FC_LE,
			"Link Status: UP_DOWN",
			म_माप("Link Status: UP_DOWN"));
		अगर (fnic->config.flags & VFCF_FIP_CAPABLE) अणु
			FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
				"deleting fip-timer during link-down\n");
			del_समयr_sync(&fnic->fip_समयr);
		पूर्ण
		fcoe_ctlr_link_करोwn(&fnic->ctlr);
	पूर्ण

पूर्ण

/*
 * This function passes incoming fabric frames to libFC
 */
व्योम fnic_handle_frame(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fnic *fnic = container_of(work, काष्ठा fnic, frame_work);
	काष्ठा fc_lport *lp = fnic->lport;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	काष्ठा fc_frame *fp;

	जबतक ((skb = skb_dequeue(&fnic->frame_queue))) अणु

		spin_lock_irqsave(&fnic->fnic_lock, flags);
		अगर (fnic->stop_rx_link_events) अणु
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
		fp = (काष्ठा fc_frame *)skb;

		/*
		 * If we're in a transitional state, just re-queue and वापस.
		 * The queue will be serviced when we get to a stable state.
		 */
		अगर (fnic->state != FNIC_IN_FC_MODE &&
		    fnic->state != FNIC_IN_ETH_MODE) अणु
			skb_queue_head(&fnic->frame_queue, skb);
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);

		fc_exch_recv(lp, fp);
	पूर्ण
पूर्ण

व्योम fnic_fcoe_evlist_मुक्त(काष्ठा fnic *fnic)
अणु
	काष्ठा fnic_event *fevt = शून्य;
	काष्ठा fnic_event *next = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (list_empty(&fnic->evlist)) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(fevt, next, &fnic->evlist, list) अणु
		list_del(&fevt->list);
		kमुक्त(fevt);
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);
पूर्ण

व्योम fnic_handle_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fnic *fnic = container_of(work, काष्ठा fnic, event_work);
	काष्ठा fnic_event *fevt = शून्य;
	काष्ठा fnic_event *next = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (list_empty(&fnic->evlist)) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(fevt, next, &fnic->evlist, list) अणु
		अगर (fnic->stop_rx_link_events) अणु
			list_del(&fevt->list);
			kमुक्त(fevt);
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			वापस;
		पूर्ण
		/*
		 * If we're in a transitional state, just re-queue and वापस.
		 * The queue will be serviced when we get to a stable state.
		 */
		अगर (fnic->state != FNIC_IN_FC_MODE &&
		    fnic->state != FNIC_IN_ETH_MODE) अणु
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			वापस;
		पूर्ण

		list_del(&fevt->list);
		चयन (fevt->event) अणु
		हाल FNIC_EVT_START_VLAN_DISC:
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			fnic_fcoe_send_vlan_req(fnic);
			spin_lock_irqsave(&fnic->fnic_lock, flags);
			अवरोध;
		हाल FNIC_EVT_START_FCF_DISC:
			FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
				  "Start FCF Discovery\n");
			fnic_fcoe_start_fcf_disc(fnic);
			अवरोध;
		शेष:
			FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
				  "Unknown event 0x%x\n", fevt->event);
			अवरोध;
		पूर्ण
		kमुक्त(fevt);
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);
पूर्ण

/**
 * is_fnic_fip_flogi_reject() - Check अगर the Received FIP FLOGI frame is rejected
 * @fip: The FCoE controller that received the frame
 * @skb: The received FIP frame
 *
 * Returns non-zero अगर the frame is rejected with unsupported cmd with
 * insufficient resource els explanation.
 */
अटल अंतरभूत पूर्णांक is_fnic_fip_flogi_reject(काष्ठा fcoe_ctlr *fip,
					 काष्ठा sk_buff *skb)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fip_header *fiph;
	काष्ठा fc_frame_header *fh = शून्य;
	काष्ठा fip_desc *desc;
	काष्ठा fip_encaps *els;
	u16 op;
	u8 els_op;
	u8 sub;

	माप_प्रकार rlen;
	माप_प्रकार dlen = 0;

	अगर (skb_linearize(skb))
		वापस 0;

	अगर (skb->len < माप(*fiph))
		वापस 0;

	fiph = (काष्ठा fip_header *)skb->data;
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	अगर (op != FIP_OP_LS)
		वापस 0;

	अगर (sub != FIP_SC_REP)
		वापस 0;

	rlen = ntohs(fiph->fip_dl_len) * 4;
	अगर (rlen + माप(*fiph) > skb->len)
		वापस 0;

	desc = (काष्ठा fip_desc *)(fiph + 1);
	dlen = desc->fip_dlen * FIP_BPW;

	अगर (desc->fip_dtype == FIP_DT_FLOGI) अणु

		अगर (dlen < माप(*els) + माप(*fh) + 1)
			वापस 0;

		els = (काष्ठा fip_encaps *)desc;
		fh = (काष्ठा fc_frame_header *)(els + 1);

		अगर (!fh)
			वापस 0;

		/*
		 * ELS command code, reason and explanation should be = Reject,
		 * unsupported command and insufficient resource
		 */
		els_op = *(u8 *)(fh + 1);
		अगर (els_op == ELS_LS_RJT) अणु
			shost_prपूर्णांकk(KERN_INFO, lport->host,
				  "Flogi Request Rejected by Switch\n");
			वापस 1;
		पूर्ण
		shost_prपूर्णांकk(KERN_INFO, lport->host,
				"Flogi Request Accepted by Switch\n");
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम fnic_fcoe_send_vlan_req(काष्ठा fnic *fnic)
अणु
	काष्ठा fcoe_ctlr *fip = &fnic->ctlr;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	काष्ठा sk_buff *skb;
	अक्षर *eth_fr;
	काष्ठा fip_vlan *vlan;
	u64 vlan_tov;

	fnic_fcoe_reset_vlans(fnic);
	fnic->set_vlan(fnic, 0);

	अगर (prपूर्णांकk_ratelimit())
		FNIC_FCS_DBG(KERN_INFO, fnic->lport->host,
			  "Sending VLAN request...\n");

	skb = dev_alloc_skb(माप(काष्ठा fip_vlan));
	अगर (!skb)
		वापस;

	eth_fr = (अक्षर *)skb->data;
	vlan = (काष्ठा fip_vlan *)eth_fr;

	स_रखो(vlan, 0, माप(*vlan));
	स_नकल(vlan->eth.h_source, fip->ctl_src_addr, ETH_ALEN);
	स_नकल(vlan->eth.h_dest, fcoe_all_fcfs, ETH_ALEN);
	vlan->eth.h_proto = htons(ETH_P_FIP);

	vlan->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	vlan->fip.fip_op = htons(FIP_OP_VLAN);
	vlan->fip.fip_subcode = FIP_SC_VL_REQ;
	vlan->fip.fip_dl_len = htons(माप(vlan->desc) / FIP_BPW);

	vlan->desc.mac.fd_desc.fip_dtype = FIP_DT_MAC;
	vlan->desc.mac.fd_desc.fip_dlen = माप(vlan->desc.mac) / FIP_BPW;
	स_नकल(&vlan->desc.mac.fd_mac, fip->ctl_src_addr, ETH_ALEN);

	vlan->desc.wwnn.fd_desc.fip_dtype = FIP_DT_NAME;
	vlan->desc.wwnn.fd_desc.fip_dlen = माप(vlan->desc.wwnn) / FIP_BPW;
	put_unaligned_be64(fip->lp->wwnn, &vlan->desc.wwnn.fd_wwn);
	atomic64_inc(&fnic_stats->vlan_stats.vlan_disc_reqs);

	skb_put(skb, माप(*vlan));
	skb->protocol = htons(ETH_P_FIP);
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	fip->send(fip, skb);

	/* set a समयr so that we can retry अगर there no response */
	vlan_tov = jअगरfies + msecs_to_jअगरfies(FCOE_CTLR_FIPVLAN_TOV);
	mod_समयr(&fnic->fip_समयr, round_jअगरfies(vlan_tov));
पूर्ण

अटल व्योम fnic_fcoe_process_vlan_resp(काष्ठा fnic *fnic, काष्ठा sk_buff *skb)
अणु
	काष्ठा fcoe_ctlr *fip = &fnic->ctlr;
	काष्ठा fip_header *fiph;
	काष्ठा fip_desc *desc;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	u16 vid;
	माप_प्रकार rlen;
	माप_प्रकार dlen;
	काष्ठा fcoe_vlan *vlan;
	u64 sol_समय;
	अचिन्हित दीर्घ flags;

	FNIC_FCS_DBG(KERN_INFO, fnic->lport->host,
		  "Received VLAN response...\n");

	fiph = (काष्ठा fip_header *) skb->data;

	FNIC_FCS_DBG(KERN_INFO, fnic->lport->host,
		  "Received VLAN response... OP 0x%x SUB_OP 0x%x\n",
		  ntohs(fiph->fip_op), fiph->fip_subcode);

	rlen = ntohs(fiph->fip_dl_len) * 4;
	fnic_fcoe_reset_vlans(fnic);
	spin_lock_irqsave(&fnic->vlans_lock, flags);
	desc = (काष्ठा fip_desc *)(fiph + 1);
	जबतक (rlen > 0) अणु
		dlen = desc->fip_dlen * FIP_BPW;
		चयन (desc->fip_dtype) अणु
		हाल FIP_DT_VLAN:
			vid = ntohs(((काष्ठा fip_vlan_desc *)desc)->fd_vlan);
			shost_prपूर्णांकk(KERN_INFO, fnic->lport->host,
				  "process_vlan_resp: FIP VLAN %d\n", vid);
			vlan = kzalloc(माप(*vlan), GFP_ATOMIC);
			अगर (!vlan) अणु
				/* retry from समयr */
				spin_unlock_irqrestore(&fnic->vlans_lock,
							flags);
				जाओ out;
			पूर्ण
			vlan->vid = vid & 0x0fff;
			vlan->state = FIP_VLAN_AVAIL;
			list_add_tail(&vlan->list, &fnic->vlans);
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण

	/* any VLAN descriptors present ? */
	अगर (list_empty(&fnic->vlans)) अणु
		/* retry from समयr */
		atomic64_inc(&fnic_stats->vlan_stats.resp_withno_vlanID);
		FNIC_FCS_DBG(KERN_INFO, fnic->lport->host,
			  "No VLAN descriptors in FIP VLAN response\n");
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		जाओ out;
	पूर्ण

	vlan = list_first_entry(&fnic->vlans, काष्ठा fcoe_vlan, list);
	fnic->set_vlan(fnic, vlan->vid);
	vlan->state = FIP_VLAN_SENT; /* sent now */
	vlan->sol_count++;
	spin_unlock_irqrestore(&fnic->vlans_lock, flags);

	/* start the solicitation */
	fcoe_ctlr_link_up(fip);

	sol_समय = jअगरfies + msecs_to_jअगरfies(FCOE_CTLR_START_DELAY);
	mod_समयr(&fnic->fip_समयr, round_jअगरfies(sol_समय));
out:
	वापस;
पूर्ण

अटल व्योम fnic_fcoe_start_fcf_disc(काष्ठा fnic *fnic)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_vlan *vlan;
	u64 sol_समय;

	spin_lock_irqsave(&fnic->vlans_lock, flags);
	vlan = list_first_entry(&fnic->vlans, काष्ठा fcoe_vlan, list);
	fnic->set_vlan(fnic, vlan->vid);
	vlan->state = FIP_VLAN_SENT; /* sent now */
	vlan->sol_count = 1;
	spin_unlock_irqrestore(&fnic->vlans_lock, flags);

	/* start the solicitation */
	fcoe_ctlr_link_up(&fnic->ctlr);

	sol_समय = jअगरfies + msecs_to_jअगरfies(FCOE_CTLR_START_DELAY);
	mod_समयr(&fnic->fip_समयr, round_jअगरfies(sol_समय));
पूर्ण

अटल पूर्णांक fnic_fcoe_vlan_check(काष्ठा fnic *fnic, u16 flag)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_vlan *fvlan;

	spin_lock_irqsave(&fnic->vlans_lock, flags);
	अगर (list_empty(&fnic->vlans)) अणु
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		वापस -EINVAL;
	पूर्ण

	fvlan = list_first_entry(&fnic->vlans, काष्ठा fcoe_vlan, list);
	अगर (fvlan->state == FIP_VLAN_USED) अणु
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		वापस 0;
	पूर्ण

	अगर (fvlan->state == FIP_VLAN_SENT) अणु
		fvlan->state = FIP_VLAN_USED;
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&fnic->vlans_lock, flags);
	वापस -EINVAL;
पूर्ण

अटल व्योम fnic_event_enq(काष्ठा fnic *fnic, क्रमागत fnic_evt ev)
अणु
	काष्ठा fnic_event *fevt;
	अचिन्हित दीर्घ flags;

	fevt = kदो_स्मृति(माप(*fevt), GFP_ATOMIC);
	अगर (!fevt)
		वापस;

	fevt->fnic = fnic;
	fevt->event = ev;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	list_add_tail(&fevt->list, &fnic->evlist);
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	schedule_work(&fnic->event_work);
पूर्ण

अटल पूर्णांक fnic_fcoe_handle_fip_frame(काष्ठा fnic *fnic, काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_header *fiph;
	पूर्णांक ret = 1;
	u16 op;
	u8 sub;

	अगर (!skb || !(skb->data))
		वापस -1;

	अगर (skb_linearize(skb))
		जाओ drop;

	fiph = (काष्ठा fip_header *)skb->data;
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	अगर (FIP_VER_DECAPS(fiph->fip_ver) != FIP_VER)
		जाओ drop;

	अगर (ntohs(fiph->fip_dl_len) * FIP_BPW + माप(*fiph) > skb->len)
		जाओ drop;

	अगर (op == FIP_OP_DISC && sub == FIP_SC_ADV) अणु
		अगर (fnic_fcoe_vlan_check(fnic, ntohs(fiph->fip_flags)))
			जाओ drop;
		/* pass it on to fcoe */
		ret = 1;
	पूर्ण अन्यथा अगर (op == FIP_OP_VLAN && sub == FIP_SC_VL_NOTE) अणु
		/* set the vlan as used */
		fnic_fcoe_process_vlan_resp(fnic, skb);
		ret = 0;
	पूर्ण अन्यथा अगर (op == FIP_OP_CTRL && sub == FIP_SC_CLR_VLINK) अणु
		/* received CVL request, restart vlan disc */
		fnic_event_enq(fnic, FNIC_EVT_START_VLAN_DISC);
		/* pass it on to fcoe */
		ret = 1;
	पूर्ण
drop:
	वापस ret;
पूर्ण

व्योम fnic_handle_fip_frame(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fnic *fnic = container_of(work, काष्ठा fnic, fip_frame_work);
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;
	काष्ठा ethhdr *eh;

	जबतक ((skb = skb_dequeue(&fnic->fip_frame_queue))) अणु
		spin_lock_irqsave(&fnic->fnic_lock, flags);
		अगर (fnic->stop_rx_link_events) अणु
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			dev_kमुक्त_skb(skb);
			वापस;
		पूर्ण
		/*
		 * If we're in a transitional state, just re-queue and वापस.
		 * The queue will be serviced when we get to a stable state.
		 */
		अगर (fnic->state != FNIC_IN_FC_MODE &&
		    fnic->state != FNIC_IN_ETH_MODE) अणु
			skb_queue_head(&fnic->fip_frame_queue, skb);
			spin_unlock_irqrestore(&fnic->fnic_lock, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		eh = (काष्ठा ethhdr *)skb->data;
		अगर (eh->h_proto == htons(ETH_P_FIP)) अणु
			skb_pull(skb, माप(*eh));
			अगर (fnic_fcoe_handle_fip_frame(fnic, skb) <= 0) अणु
				dev_kमुक्त_skb(skb);
				जारी;
			पूर्ण
			/*
			 * If there's FLOGI rejects - clear all
			 * fcf's & restart from scratch
			 */
			अगर (is_fnic_fip_flogi_reject(&fnic->ctlr, skb)) अणु
				atomic64_inc(
					&fnic_stats->vlan_stats.flogi_rejects);
				shost_prपूर्णांकk(KERN_INFO, fnic->lport->host,
					  "Trigger a Link down - VLAN Disc\n");
				fcoe_ctlr_link_करोwn(&fnic->ctlr);
				/* start FCoE VLAN discovery */
				fnic_fcoe_send_vlan_req(fnic);
				dev_kमुक्त_skb(skb);
				जारी;
			पूर्ण
			fcoe_ctlr_recv(&fnic->ctlr, skb);
			जारी;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * fnic_import_rq_eth_pkt() - handle received FCoE or FIP frame.
 * @fnic:	fnic instance.
 * @skb:	Ethernet Frame.
 */
अटल अंतरभूत पूर्णांक fnic_import_rq_eth_pkt(काष्ठा fnic *fnic, काष्ठा sk_buff *skb)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा ethhdr *eh;
	काष्ठा fcoe_hdr *fcoe_hdr;
	काष्ठा fcoe_crc_eof *ft;

	/*
	 * Unकरो VLAN encapsulation अगर present.
	 */
	eh = (काष्ठा ethhdr *)skb->data;
	अगर (eh->h_proto == htons(ETH_P_8021Q)) अणु
		स_हटाओ((u8 *)eh + VLAN_HLEN, eh, ETH_ALEN * 2);
		eh = skb_pull(skb, VLAN_HLEN);
		skb_reset_mac_header(skb);
	पूर्ण
	अगर (eh->h_proto == htons(ETH_P_FIP)) अणु
		अगर (!(fnic->config.flags & VFCF_FIP_CAPABLE)) अणु
			prपूर्णांकk(KERN_ERR "Dropped FIP frame, as firmware "
					"uses non-FIP mode, Enable FIP "
					"using UCSM\n");
			जाओ drop;
		पूर्ण
		अगर ((fnic_fc_trace_set_data(fnic->lport->host->host_no,
			FNIC_FC_RECV|0x80, (अक्षर *)skb->data, skb->len)) != 0) अणु
			prपूर्णांकk(KERN_ERR "fnic ctlr frame trace error!!!");
		पूर्ण
		skb_queue_tail(&fnic->fip_frame_queue, skb);
		queue_work(fnic_fip_queue, &fnic->fip_frame_work);
		वापस 1;		/* let caller know packet was used */
	पूर्ण
	अगर (eh->h_proto != htons(ETH_P_FCOE))
		जाओ drop;
	skb_set_network_header(skb, माप(*eh));
	skb_pull(skb, माप(*eh));

	fcoe_hdr = (काष्ठा fcoe_hdr *)skb->data;
	अगर (FC_FCOE_DECAPS_VER(fcoe_hdr) != FC_FCOE_VER)
		जाओ drop;

	fp = (काष्ठा fc_frame *)skb;
	fc_frame_init(fp);
	fr_sof(fp) = fcoe_hdr->fcoe_sof;
	skb_pull(skb, माप(काष्ठा fcoe_hdr));
	skb_reset_transport_header(skb);

	ft = (काष्ठा fcoe_crc_eof *)(skb->data + skb->len - माप(*ft));
	fr_eof(fp) = ft->fcoe_eof;
	skb_trim(skb, skb->len - माप(*ft));
	वापस 0;
drop:
	dev_kमुक्त_skb_irq(skb);
	वापस -1;
पूर्ण

/**
 * fnic_update_mac_locked() - set data MAC address and filters.
 * @fnic:	fnic instance.
 * @new:	newly-asचिन्हित FCoE MAC address.
 *
 * Called with the fnic lock held.
 */
व्योम fnic_update_mac_locked(काष्ठा fnic *fnic, u8 *new)
अणु
	u8 *ctl = fnic->ctlr.ctl_src_addr;
	u8 *data = fnic->data_src_addr;

	अगर (is_zero_ether_addr(new))
		new = ctl;
	अगर (ether_addr_equal(data, new))
		वापस;
	FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host, "update_mac %pM\n", new);
	अगर (!is_zero_ether_addr(data) && !ether_addr_equal(data, ctl))
		vnic_dev_del_addr(fnic->vdev, data);
	स_नकल(data, new, ETH_ALEN);
	अगर (!ether_addr_equal(new, ctl))
		vnic_dev_add_addr(fnic->vdev, new);
पूर्ण

/**
 * fnic_update_mac() - set data MAC address and filters.
 * @lport:	local port.
 * @new:	newly-asचिन्हित FCoE MAC address.
 */
व्योम fnic_update_mac(काष्ठा fc_lport *lport, u8 *new)
अणु
	काष्ठा fnic *fnic = lport_priv(lport);

	spin_lock_irq(&fnic->fnic_lock);
	fnic_update_mac_locked(fnic, new);
	spin_unlock_irq(&fnic->fnic_lock);
पूर्ण

/**
 * fnic_set_port_id() - set the port_ID after successful FLOGI.
 * @lport:	local port.
 * @port_id:	asचिन्हित FC_ID.
 * @fp:		received frame containing the FLOGI accept or शून्य.
 *
 * This is called from libfc when a new FC_ID has been asचिन्हित.
 * This causes us to reset the firmware to FC_MODE and setup the new MAC
 * address and FC_ID.
 *
 * It is also called with FC_ID 0 when we're logged off.
 *
 * If the FC_ID is due to poपूर्णांक-to-poपूर्णांक, fp may be शून्य.
 */
व्योम fnic_set_port_id(काष्ठा fc_lport *lport, u32 port_id, काष्ठा fc_frame *fp)
अणु
	काष्ठा fnic *fnic = lport_priv(lport);
	u8 *mac;
	पूर्णांक ret;

	FNIC_FCS_DBG(KERN_DEBUG, lport->host, "set port_id %x fp %p\n",
		     port_id, fp);

	/*
	 * If we're clearing the FC_ID, change to use the ctl_src_addr.
	 * Set ethernet mode to send FLOGI.
	 */
	अगर (!port_id) अणु
		fnic_update_mac(lport, fnic->ctlr.ctl_src_addr);
		fnic_set_eth_mode(fnic);
		वापस;
	पूर्ण

	अगर (fp) अणु
		mac = fr_cb(fp)->granted_mac;
		अगर (is_zero_ether_addr(mac)) अणु
			/* non-FIP - FLOGI alपढ़ोy accepted - ignore वापस */
			fcoe_ctlr_recv_flogi(&fnic->ctlr, lport, fp);
		पूर्ण
		fnic_update_mac(lport, mac);
	पूर्ण

	/* Change state to reflect transition to FC mode */
	spin_lock_irq(&fnic->fnic_lock);
	अगर (fnic->state == FNIC_IN_ETH_MODE || fnic->state == FNIC_IN_FC_MODE)
		fnic->state = FNIC_IN_ETH_TRANS_FC_MODE;
	अन्यथा अणु
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
			     "Unexpected fnic state %s while"
			     " processing flogi resp\n",
			     fnic_state_to_str(fnic->state));
		spin_unlock_irq(&fnic->fnic_lock);
		वापस;
	पूर्ण
	spin_unlock_irq(&fnic->fnic_lock);

	/*
	 * Send FLOGI registration to firmware to set up FC mode.
	 * The new address will be set up when registration completes.
	 */
	ret = fnic_flogi_reg_handler(fnic, port_id);

	अगर (ret < 0) अणु
		spin_lock_irq(&fnic->fnic_lock);
		अगर (fnic->state == FNIC_IN_ETH_TRANS_FC_MODE)
			fnic->state = FNIC_IN_ETH_MODE;
		spin_unlock_irq(&fnic->fnic_lock);
	पूर्ण
पूर्ण

अटल व्योम fnic_rq_cmpl_frame_recv(काष्ठा vnic_rq *rq, काष्ठा cq_desc
				    *cq_desc, काष्ठा vnic_rq_buf *buf,
				    पूर्णांक skipped __attribute__((unused)),
				    व्योम *opaque)
अणु
	काष्ठा fnic *fnic = vnic_dev_priv(rq->vdev);
	काष्ठा sk_buff *skb;
	काष्ठा fc_frame *fp;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	u8 type, color, eop, sop, ingress_port, vlan_stripped;
	u8 fcoe = 0, fcoe_sof, fcoe_eof;
	u8 fcoe_fc_crc_ok = 1, fcoe_enc_error = 0;
	u8 tcp_udp_csum_ok, udp, tcp, ipv4_csum_ok;
	u8 ipv6, ipv4, ipv4_fragment, rss_type, csum_not_calc;
	u8 fcs_ok = 1, packet_error = 0;
	u16 q_number, completed_index, bytes_written = 0, vlan, checksum;
	u32 rss_hash;
	u16 exchange_id, पंचांगpl;
	u8 sof = 0;
	u8 eof = 0;
	u32 fcp_bytes_written = 0;
	अचिन्हित दीर्घ flags;

	dma_unmap_single(&fnic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_FROM_DEVICE);
	skb = buf->os_buf;
	fp = (काष्ठा fc_frame *)skb;
	buf->os_buf = शून्य;

	cq_desc_dec(cq_desc, &type, &color, &q_number, &completed_index);
	अगर (type == CQ_DESC_TYPE_RQ_FCP) अणु
		cq_fcp_rq_desc_dec((काष्ठा cq_fcp_rq_desc *)cq_desc,
				   &type, &color, &q_number, &completed_index,
				   &eop, &sop, &fcoe_fc_crc_ok, &exchange_id,
				   &पंचांगpl, &fcp_bytes_written, &sof, &eof,
				   &ingress_port, &packet_error,
				   &fcoe_enc_error, &fcs_ok, &vlan_stripped,
				   &vlan);
		skb_trim(skb, fcp_bytes_written);
		fr_sof(fp) = sof;
		fr_eof(fp) = eof;

	पूर्ण अन्यथा अगर (type == CQ_DESC_TYPE_RQ_ENET) अणु
		cq_enet_rq_desc_dec((काष्ठा cq_enet_rq_desc *)cq_desc,
				    &type, &color, &q_number, &completed_index,
				    &ingress_port, &fcoe, &eop, &sop,
				    &rss_type, &csum_not_calc, &rss_hash,
				    &bytes_written, &packet_error,
				    &vlan_stripped, &vlan, &checksum,
				    &fcoe_sof, &fcoe_fc_crc_ok,
				    &fcoe_enc_error, &fcoe_eof,
				    &tcp_udp_csum_ok, &udp, &tcp,
				    &ipv4_csum_ok, &ipv6, &ipv4,
				    &ipv4_fragment, &fcs_ok);
		skb_trim(skb, bytes_written);
		अगर (!fcs_ok) अणु
			atomic64_inc(&fnic_stats->misc_stats.frame_errors);
			FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
				     "fcs error.  dropping packet.\n");
			जाओ drop;
		पूर्ण
		अगर (fnic_import_rq_eth_pkt(fnic, skb))
			वापस;

	पूर्ण अन्यथा अणु
		/* wrong CQ type*/
		shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
			     "fnic rq_cmpl wrong cq type x%x\n", type);
		जाओ drop;
	पूर्ण

	अगर (!fcs_ok || packet_error || !fcoe_fc_crc_ok || fcoe_enc_error) अणु
		atomic64_inc(&fnic_stats->misc_stats.frame_errors);
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
			     "fnic rq_cmpl fcoe x%x fcsok x%x"
			     " pkterr x%x fcoe_fc_crc_ok x%x, fcoe_enc_err"
			     " x%x\n",
			     fcoe, fcs_ok, packet_error,
			     fcoe_fc_crc_ok, fcoe_enc_error);
		जाओ drop;
	पूर्ण

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (fnic->stop_rx_link_events) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		जाओ drop;
	पूर्ण
	fr_dev(fp) = fnic->lport;
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);
	अगर ((fnic_fc_trace_set_data(fnic->lport->host->host_no, FNIC_FC_RECV,
					(अक्षर *)skb->data, skb->len)) != 0) अणु
		prपूर्णांकk(KERN_ERR "fnic ctlr frame trace error!!!");
	पूर्ण

	skb_queue_tail(&fnic->frame_queue, skb);
	queue_work(fnic_event_queue, &fnic->frame_work);

	वापस;
drop:
	dev_kमुक्त_skb_irq(skb);
पूर्ण

अटल पूर्णांक fnic_rq_cmpl_handler_cont(काष्ठा vnic_dev *vdev,
				     काष्ठा cq_desc *cq_desc, u8 type,
				     u16 q_number, u16 completed_index,
				     व्योम *opaque)
अणु
	काष्ठा fnic *fnic = vnic_dev_priv(vdev);

	vnic_rq_service(&fnic->rq[q_number], cq_desc, completed_index,
			VNIC_RQ_RETURN_DESC, fnic_rq_cmpl_frame_recv,
			शून्य);
	वापस 0;
पूर्ण

पूर्णांक fnic_rq_cmpl_handler(काष्ठा fnic *fnic, पूर्णांक rq_work_to_करो)
अणु
	अचिन्हित पूर्णांक tot_rq_work_करोne = 0, cur_work_करोne;
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	क्रम (i = 0; i < fnic->rq_count; i++) अणु
		cur_work_करोne = vnic_cq_service(&fnic->cq[i], rq_work_to_करो,
						fnic_rq_cmpl_handler_cont,
						शून्य);
		अगर (cur_work_करोne) अणु
			err = vnic_rq_fill(&fnic->rq[i], fnic_alloc_rq_frame);
			अगर (err)
				shost_prपूर्णांकk(KERN_ERR, fnic->lport->host,
					     "fnic_alloc_rq_frame can't alloc"
					     " frame\n");
		पूर्ण
		tot_rq_work_करोne += cur_work_करोne;
	पूर्ण

	वापस tot_rq_work_करोne;
पूर्ण

/*
 * This function is called once at init समय to allocate and fill RQ
 * buffers. Subsequently, it is called in the पूर्णांकerrupt context after RQ
 * buffer processing to replenish the buffers in the RQ
 */
पूर्णांक fnic_alloc_rq_frame(काष्ठा vnic_rq *rq)
अणु
	काष्ठा fnic *fnic = vnic_dev_priv(rq->vdev);
	काष्ठा sk_buff *skb;
	u16 len;
	dma_addr_t pa;
	पूर्णांक r;

	len = FC_FRAME_HEADROOM + FC_MAX_FRAME + FC_FRAME_TAILROOM;
	skb = dev_alloc_skb(len);
	अगर (!skb) अणु
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
			     "Unable to allocate RQ sk_buff\n");
		वापस -ENOMEM;
	पूर्ण
	skb_reset_mac_header(skb);
	skb_reset_transport_header(skb);
	skb_reset_network_header(skb);
	skb_put(skb, len);
	pa = dma_map_single(&fnic->pdev->dev, skb->data, len, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&fnic->pdev->dev, pa)) अणु
		r = -ENOMEM;
		prपूर्णांकk(KERN_ERR "PCI mapping failed with error %d\n", r);
		जाओ मुक्त_skb;
	पूर्ण

	fnic_queue_rq_desc(rq, skb, pa, len);
	वापस 0;

मुक्त_skb:
	kमुक्त_skb(skb);
	वापस r;
पूर्ण

व्योम fnic_मुक्त_rq_buf(काष्ठा vnic_rq *rq, काष्ठा vnic_rq_buf *buf)
अणु
	काष्ठा fc_frame *fp = buf->os_buf;
	काष्ठा fnic *fnic = vnic_dev_priv(rq->vdev);

	dma_unmap_single(&fnic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_FROM_DEVICE);

	dev_kमुक्त_skb(fp_skb(fp));
	buf->os_buf = शून्य;
पूर्ण

/**
 * fnic_eth_send() - Send Ethernet frame.
 * @fip:	fcoe_ctlr instance.
 * @skb:	Ethernet Frame, FIP, without VLAN encapsulation.
 */
व्योम fnic_eth_send(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fnic *fnic = fnic_from_ctlr(fip);
	काष्ठा vnic_wq *wq = &fnic->wq[0];
	dma_addr_t pa;
	काष्ठा ethhdr *eth_hdr;
	काष्ठा vlan_ethhdr *vlan_hdr;
	अचिन्हित दीर्घ flags;

	अगर (!fnic->vlan_hw_insert) अणु
		eth_hdr = (काष्ठा ethhdr *)skb_mac_header(skb);
		vlan_hdr = skb_push(skb, माप(*vlan_hdr) - माप(*eth_hdr));
		स_नकल(vlan_hdr, eth_hdr, 2 * ETH_ALEN);
		vlan_hdr->h_vlan_proto = htons(ETH_P_8021Q);
		vlan_hdr->h_vlan_encapsulated_proto = eth_hdr->h_proto;
		vlan_hdr->h_vlan_TCI = htons(fnic->vlan_id);
		अगर ((fnic_fc_trace_set_data(fnic->lport->host->host_no,
			FNIC_FC_SEND|0x80, (अक्षर *)eth_hdr, skb->len)) != 0) अणु
			prपूर्णांकk(KERN_ERR "fnic ctlr frame trace error!!!");
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((fnic_fc_trace_set_data(fnic->lport->host->host_no,
			FNIC_FC_SEND|0x80, (अक्षर *)skb->data, skb->len)) != 0) अणु
			prपूर्णांकk(KERN_ERR "fnic ctlr frame trace error!!!");
		पूर्ण
	पूर्ण

	pa = dma_map_single(&fnic->pdev->dev, skb->data, skb->len,
			DMA_TO_DEVICE);
	अगर (dma_mapping_error(&fnic->pdev->dev, pa)) अणु
		prपूर्णांकk(KERN_ERR "DMA mapping failed\n");
		जाओ मुक्त_skb;
	पूर्ण

	spin_lock_irqsave(&fnic->wq_lock[0], flags);
	अगर (!vnic_wq_desc_avail(wq))
		जाओ irq_restore;

	fnic_queue_wq_eth_desc(wq, skb, pa, skb->len,
			       0 /* hw inserts cos value */,
			       fnic->vlan_id, 1);
	spin_unlock_irqrestore(&fnic->wq_lock[0], flags);
	वापस;

irq_restore:
	spin_unlock_irqrestore(&fnic->wq_lock[0], flags);
	dma_unmap_single(&fnic->pdev->dev, pa, skb->len, DMA_TO_DEVICE);
मुक्त_skb:
	kमुक्त_skb(skb);
पूर्ण

/*
 * Send FC frame.
 */
अटल पूर्णांक fnic_send_frame(काष्ठा fnic *fnic, काष्ठा fc_frame *fp)
अणु
	काष्ठा vnic_wq *wq = &fnic->wq[0];
	काष्ठा sk_buff *skb;
	dma_addr_t pa;
	काष्ठा ethhdr *eth_hdr;
	काष्ठा vlan_ethhdr *vlan_hdr;
	काष्ठा fcoe_hdr *fcoe_hdr;
	काष्ठा fc_frame_header *fh;
	u32 tot_len, eth_hdr_len;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	fh = fc_frame_header_get(fp);
	skb = fp_skb(fp);

	अगर (unlikely(fh->fh_r_ctl == FC_RCTL_ELS_REQ) &&
	    fcoe_ctlr_els_send(&fnic->ctlr, fnic->lport, skb))
		वापस 0;

	अगर (!fnic->vlan_hw_insert) अणु
		eth_hdr_len = माप(*vlan_hdr) + माप(*fcoe_hdr);
		vlan_hdr = skb_push(skb, eth_hdr_len);
		eth_hdr = (काष्ठा ethhdr *)vlan_hdr;
		vlan_hdr->h_vlan_proto = htons(ETH_P_8021Q);
		vlan_hdr->h_vlan_encapsulated_proto = htons(ETH_P_FCOE);
		vlan_hdr->h_vlan_TCI = htons(fnic->vlan_id);
		fcoe_hdr = (काष्ठा fcoe_hdr *)(vlan_hdr + 1);
	पूर्ण अन्यथा अणु
		eth_hdr_len = माप(*eth_hdr) + माप(*fcoe_hdr);
		eth_hdr = skb_push(skb, eth_hdr_len);
		eth_hdr->h_proto = htons(ETH_P_FCOE);
		fcoe_hdr = (काष्ठा fcoe_hdr *)(eth_hdr + 1);
	पूर्ण

	अगर (fnic->ctlr.map_dest)
		fc_fcoe_set_mac(eth_hdr->h_dest, fh->fh_d_id);
	अन्यथा
		स_नकल(eth_hdr->h_dest, fnic->ctlr.dest_addr, ETH_ALEN);
	स_नकल(eth_hdr->h_source, fnic->data_src_addr, ETH_ALEN);

	tot_len = skb->len;
	BUG_ON(tot_len % 4);

	स_रखो(fcoe_hdr, 0, माप(*fcoe_hdr));
	fcoe_hdr->fcoe_sof = fr_sof(fp);
	अगर (FC_FCOE_VER)
		FC_FCOE_ENCAPS_VER(fcoe_hdr, FC_FCOE_VER);

	pa = dma_map_single(&fnic->pdev->dev, eth_hdr, tot_len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&fnic->pdev->dev, pa)) अणु
		ret = -ENOMEM;
		prपूर्णांकk(KERN_ERR "DMA map failed with error %d\n", ret);
		जाओ मुक्त_skb_on_err;
	पूर्ण

	अगर ((fnic_fc_trace_set_data(fnic->lport->host->host_no, FNIC_FC_SEND,
				(अक्षर *)eth_hdr, tot_len)) != 0) अणु
		prपूर्णांकk(KERN_ERR "fnic ctlr frame trace error!!!");
	पूर्ण

	spin_lock_irqsave(&fnic->wq_lock[0], flags);

	अगर (!vnic_wq_desc_avail(wq)) अणु
		dma_unmap_single(&fnic->pdev->dev, pa, tot_len, DMA_TO_DEVICE);
		ret = -1;
		जाओ irq_restore;
	पूर्ण

	fnic_queue_wq_desc(wq, skb, pa, tot_len, fr_eof(fp),
			   0 /* hw inserts cos value */,
			   fnic->vlan_id, 1, 1, 1);

irq_restore:
	spin_unlock_irqrestore(&fnic->wq_lock[0], flags);

मुक्त_skb_on_err:
	अगर (ret)
		dev_kमुक्त_skb_any(fp_skb(fp));

	वापस ret;
पूर्ण

/*
 * fnic_send
 * Routine to send a raw frame
 */
पूर्णांक fnic_send(काष्ठा fc_lport *lp, काष्ठा fc_frame *fp)
अणु
	काष्ठा fnic *fnic = lport_priv(lp);
	अचिन्हित दीर्घ flags;

	अगर (fnic->in_हटाओ) अणु
		dev_kमुक्त_skb(fp_skb(fp));
		वापस -1;
	पूर्ण

	/*
	 * Queue frame अगर in a transitional state.
	 * This occurs जबतक रेजिस्टरing the Port_ID / MAC address after FLOGI.
	 */
	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (fnic->state != FNIC_IN_FC_MODE && fnic->state != FNIC_IN_ETH_MODE) अणु
		skb_queue_tail(&fnic->tx_queue, fp_skb(fp));
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	वापस fnic_send_frame(fnic, fp);
पूर्ण

/**
 * fnic_flush_tx() - send queued frames.
 * @fnic: fnic device
 *
 * Send frames that were रुकोing to go out in FC or Ethernet mode.
 * Whenever changing modes we purge queued frames, so these frames should
 * be queued क्रम the stable mode that we're in, either FC or Ethernet.
 *
 * Called without fnic_lock held.
 */
व्योम fnic_flush_tx(काष्ठा fnic *fnic)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fc_frame *fp;

	जबतक ((skb = skb_dequeue(&fnic->tx_queue))) अणु
		fp = (काष्ठा fc_frame *)skb;
		fnic_send_frame(fnic, fp);
	पूर्ण
पूर्ण

/**
 * fnic_set_eth_mode() - put fnic पूर्णांकo ethernet mode.
 * @fnic: fnic device
 *
 * Called without fnic lock held.
 */
अटल व्योम fnic_set_eth_mode(काष्ठा fnic *fnic)
अणु
	अचिन्हित दीर्घ flags;
	क्रमागत fnic_state old_state;
	पूर्णांक ret;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
again:
	old_state = fnic->state;
	चयन (old_state) अणु
	हाल FNIC_IN_FC_MODE:
	हाल FNIC_IN_ETH_TRANS_FC_MODE:
	शेष:
		fnic->state = FNIC_IN_FC_TRANS_ETH_MODE;
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);

		ret = fnic_fw_reset_handler(fnic);

		spin_lock_irqsave(&fnic->fnic_lock, flags);
		अगर (fnic->state != FNIC_IN_FC_TRANS_ETH_MODE)
			जाओ again;
		अगर (ret)
			fnic->state = old_state;
		अवरोध;

	हाल FNIC_IN_FC_TRANS_ETH_MODE:
	हाल FNIC_IN_ETH_MODE:
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);
पूर्ण

अटल व्योम fnic_wq_complete_frame_send(काष्ठा vnic_wq *wq,
					काष्ठा cq_desc *cq_desc,
					काष्ठा vnic_wq_buf *buf, व्योम *opaque)
अणु
	काष्ठा sk_buff *skb = buf->os_buf;
	काष्ठा fc_frame *fp = (काष्ठा fc_frame *)skb;
	काष्ठा fnic *fnic = vnic_dev_priv(wq->vdev);

	dma_unmap_single(&fnic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_TO_DEVICE);
	dev_kमुक्त_skb_irq(fp_skb(fp));
	buf->os_buf = शून्य;
पूर्ण

अटल पूर्णांक fnic_wq_cmpl_handler_cont(काष्ठा vnic_dev *vdev,
				     काष्ठा cq_desc *cq_desc, u8 type,
				     u16 q_number, u16 completed_index,
				     व्योम *opaque)
अणु
	काष्ठा fnic *fnic = vnic_dev_priv(vdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&fnic->wq_lock[q_number], flags);
	vnic_wq_service(&fnic->wq[q_number], cq_desc, completed_index,
			fnic_wq_complete_frame_send, शून्य);
	spin_unlock_irqrestore(&fnic->wq_lock[q_number], flags);

	वापस 0;
पूर्ण

पूर्णांक fnic_wq_cmpl_handler(काष्ठा fnic *fnic, पूर्णांक work_to_करो)
अणु
	अचिन्हित पूर्णांक wq_work_करोne = 0;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < fnic->raw_wq_count; i++) अणु
		wq_work_करोne  += vnic_cq_service(&fnic->cq[fnic->rq_count+i],
						 work_to_करो,
						 fnic_wq_cmpl_handler_cont,
						 शून्य);
	पूर्ण

	वापस wq_work_करोne;
पूर्ण


व्योम fnic_मुक्त_wq_buf(काष्ठा vnic_wq *wq, काष्ठा vnic_wq_buf *buf)
अणु
	काष्ठा fc_frame *fp = buf->os_buf;
	काष्ठा fnic *fnic = vnic_dev_priv(wq->vdev);

	dma_unmap_single(&fnic->pdev->dev, buf->dma_addr, buf->len,
			 DMA_TO_DEVICE);

	dev_kमुक्त_skb(fp_skb(fp));
	buf->os_buf = शून्य;
पूर्ण

व्योम fnic_fcoe_reset_vlans(काष्ठा fnic *fnic)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_vlan *vlan;
	काष्ठा fcoe_vlan *next;

	/*
	 * indicate a link करोwn to fcoe so that all fcf's are free'd
	 * might not be required since we did this beक्रमe sending vlan
	 * discovery request
	 */
	spin_lock_irqsave(&fnic->vlans_lock, flags);
	अगर (!list_empty(&fnic->vlans)) अणु
		list_क्रम_each_entry_safe(vlan, next, &fnic->vlans, list) अणु
			list_del(&vlan->list);
			kमुक्त(vlan);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&fnic->vlans_lock, flags);
पूर्ण

व्योम fnic_handle_fip_समयr(काष्ठा fnic *fnic)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा fcoe_vlan *vlan;
	काष्ठा fnic_stats *fnic_stats = &fnic->fnic_stats;
	u64 sol_समय;

	spin_lock_irqsave(&fnic->fnic_lock, flags);
	अगर (fnic->stop_rx_link_events) अणु
		spin_unlock_irqrestore(&fnic->fnic_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&fnic->fnic_lock, flags);

	अगर (fnic->ctlr.mode == FIP_MODE_NON_FIP)
		वापस;

	spin_lock_irqsave(&fnic->vlans_lock, flags);
	अगर (list_empty(&fnic->vlans)) अणु
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		/* no vlans available, try again */
		अगर (unlikely(fnic_log_level & FNIC_FCS_LOGGING))
			अगर (prपूर्णांकk_ratelimit())
				shost_prपूर्णांकk(KERN_DEBUG, fnic->lport->host,
						"Start VLAN Discovery\n");
		fnic_event_enq(fnic, FNIC_EVT_START_VLAN_DISC);
		वापस;
	पूर्ण

	vlan = list_first_entry(&fnic->vlans, काष्ठा fcoe_vlan, list);
	FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
		  "fip_timer: vlan %d state %d sol_count %d\n",
		  vlan->vid, vlan->state, vlan->sol_count);
	चयन (vlan->state) अणु
	हाल FIP_VLAN_USED:
		FNIC_FCS_DBG(KERN_DEBUG, fnic->lport->host,
			  "FIP VLAN is selected for FC transaction\n");
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		अवरोध;
	हाल FIP_VLAN_FAILED:
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		/* अगर all vlans are in failed state, restart vlan disc */
		अगर (unlikely(fnic_log_level & FNIC_FCS_LOGGING))
			अगर (prपूर्णांकk_ratelimit())
				shost_prपूर्णांकk(KERN_DEBUG, fnic->lport->host,
					  "Start VLAN Discovery\n");
		fnic_event_enq(fnic, FNIC_EVT_START_VLAN_DISC);
		अवरोध;
	हाल FIP_VLAN_SENT:
		अगर (vlan->sol_count >= FCOE_CTLR_MAX_SOL) अणु
			/*
			 * no response on this vlan, हटाओ  from the list.
			 * Try the next vlan
			 */
			FNIC_FCS_DBG(KERN_INFO, fnic->lport->host,
				  "Dequeue this VLAN ID %d from list\n",
				  vlan->vid);
			list_del(&vlan->list);
			kमुक्त(vlan);
			vlan = शून्य;
			अगर (list_empty(&fnic->vlans)) अणु
				/* we exhausted all vlans, restart vlan disc */
				spin_unlock_irqrestore(&fnic->vlans_lock,
							flags);
				FNIC_FCS_DBG(KERN_INFO, fnic->lport->host,
					  "fip_timer: vlan list empty, "
					  "trigger vlan disc\n");
				fnic_event_enq(fnic, FNIC_EVT_START_VLAN_DISC);
				वापस;
			पूर्ण
			/* check the next vlan */
			vlan = list_first_entry(&fnic->vlans, काष्ठा fcoe_vlan,
							list);
			fnic->set_vlan(fnic, vlan->vid);
			vlan->state = FIP_VLAN_SENT; /* sent now */
		पूर्ण
		spin_unlock_irqrestore(&fnic->vlans_lock, flags);
		atomic64_inc(&fnic_stats->vlan_stats.sol_expiry_count);
		vlan->sol_count++;
		sol_समय = jअगरfies + msecs_to_jअगरfies
					(FCOE_CTLR_START_DELAY);
		mod_समयr(&fnic->fip_समयr, round_jअगरfies(sol_समय));
		अवरोध;
	पूर्ण
पूर्ण
