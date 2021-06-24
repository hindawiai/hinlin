<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2008-2009 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2009 Intel Corporation.  All rights reserved.
 *
 * Maपूर्णांकained at www.Open-FCoE.org
 */

#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/समयr.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <net/rtnetlink.h>

#समावेश <scsi/fc/fc_els.h>
#समावेश <scsi/fc/fc_fs.h>
#समावेश <scsi/fc/fc_fip.h>
#समावेश <scsi/fc/fc_encaps.h>
#समावेश <scsi/fc/fc_fcoe.h>
#समावेश <scsi/fc/fc_fcp.h>

#समावेश <scsi/libfc.h>
#समावेश <scsi/libfcoe.h>

#समावेश "libfcoe.h"

#घोषणा	FCOE_CTLR_MIN_FKA	500		/* min keep alive (mS) */
#घोषणा	FCOE_CTLR_DEF_FKA	FIP_DEF_FKA	/* शेष keep alive (mS) */

अटल व्योम fcoe_ctlr_समयout(काष्ठा समयr_list *);
अटल व्योम fcoe_ctlr_समयr_work(काष्ठा work_काष्ठा *);
अटल व्योम fcoe_ctlr_recv_work(काष्ठा work_काष्ठा *);
अटल पूर्णांक fcoe_ctlr_flogi_retry(काष्ठा fcoe_ctlr *);

अटल व्योम fcoe_ctlr_vn_start(काष्ठा fcoe_ctlr *);
अटल पूर्णांक fcoe_ctlr_vn_recv(काष्ठा fcoe_ctlr *, काष्ठा sk_buff *);
अटल व्योम fcoe_ctlr_vn_समयout(काष्ठा fcoe_ctlr *);
अटल पूर्णांक fcoe_ctlr_vn_lookup(काष्ठा fcoe_ctlr *, u32, u8 *);

अटल पूर्णांक fcoe_ctlr_vlan_recv(काष्ठा fcoe_ctlr *, काष्ठा sk_buff *);

अटल u8 fcoe_all_fcfs[ETH_ALEN] = FIP_ALL_FCF_MACS;
अटल u8 fcoe_all_enode[ETH_ALEN] = FIP_ALL_ENODE_MACS;
अटल u8 fcoe_all_vn2vn[ETH_ALEN] = FIP_ALL_VN2VN_MACS;
अटल u8 fcoe_all_p2p[ETH_ALEN] = FIP_ALL_P2P_MACS;

अटल स्थिर अक्षर * स्थिर fcoe_ctlr_states[] = अणु
	[FIP_ST_DISABLED] =	"DISABLED",
	[FIP_ST_LINK_WAIT] =	"LINK_WAIT",
	[FIP_ST_AUTO] =		"AUTO",
	[FIP_ST_NON_FIP] =	"NON_FIP",
	[FIP_ST_ENABLED] =	"ENABLED",
	[FIP_ST_VNMP_START] =	"VNMP_START",
	[FIP_ST_VNMP_PROBE1] =	"VNMP_PROBE1",
	[FIP_ST_VNMP_PROBE2] =	"VNMP_PROBE2",
	[FIP_ST_VNMP_CLAIM] =	"VNMP_CLAIM",
	[FIP_ST_VNMP_UP] =	"VNMP_UP",
पूर्ण;

अटल स्थिर अक्षर *fcoe_ctlr_state(क्रमागत fip_state state)
अणु
	स्थिर अक्षर *cp = "unknown";

	अगर (state < ARRAY_SIZE(fcoe_ctlr_states))
		cp = fcoe_ctlr_states[state];
	अगर (!cp)
		cp = "unknown";
	वापस cp;
पूर्ण

/**
 * fcoe_ctlr_set_state() - Set and करो debug prपूर्णांकing क्रम the new FIP state.
 * @fip: The FCoE controller
 * @state: The new state
 */
अटल व्योम fcoe_ctlr_set_state(काष्ठा fcoe_ctlr *fip, क्रमागत fip_state state)
अणु
	अगर (state == fip->state)
		वापस;
	अगर (fip->lp)
		LIBFCOE_FIP_DBG(fip, "state %s -> %s\n",
			fcoe_ctlr_state(fip->state), fcoe_ctlr_state(state));
	fip->state = state;
पूर्ण

/**
 * fcoe_ctlr_mtu_valid() - Check अगर a FCF's MTU is valid
 * @fcf: The FCF to check
 *
 * Return non-zero अगर FCF fcoe_size has been validated.
 */
अटल अंतरभूत पूर्णांक fcoe_ctlr_mtu_valid(स्थिर काष्ठा fcoe_fcf *fcf)
अणु
	वापस (fcf->flags & FIP_FL_SOL) != 0;
पूर्ण

/**
 * fcoe_ctlr_fcf_usable() - Check अगर a FCF is usable
 * @fcf: The FCF to check
 *
 * Return non-zero अगर the FCF is usable.
 */
अटल अंतरभूत पूर्णांक fcoe_ctlr_fcf_usable(काष्ठा fcoe_fcf *fcf)
अणु
	u16 flags = FIP_FL_SOL | FIP_FL_AVAIL;

	वापस (fcf->flags & flags) == flags;
पूर्ण

/**
 * fcoe_ctlr_map_dest() - Set flag and OUI क्रम mapping destination addresses
 * @fip: The FCoE controller
 */
अटल व्योम fcoe_ctlr_map_dest(काष्ठा fcoe_ctlr *fip)
अणु
	अगर (fip->mode == FIP_MODE_VN2VN)
		hton24(fip->dest_addr, FIP_VN_FC_MAP);
	अन्यथा
		hton24(fip->dest_addr, FIP_DEF_FC_MAP);
	hton24(fip->dest_addr + 3, 0);
	fip->map_dest = 1;
पूर्ण

/**
 * fcoe_ctlr_init() - Initialize the FCoE Controller instance
 * @fip: The FCoE controller to initialize
 * @mode: FIP mode to set
 */
व्योम fcoe_ctlr_init(काष्ठा fcoe_ctlr *fip, क्रमागत fip_mode mode)
अणु
	fcoe_ctlr_set_state(fip, FIP_ST_LINK_WAIT);
	fip->mode = mode;
	fip->fip_resp = false;
	INIT_LIST_HEAD(&fip->fcfs);
	mutex_init(&fip->ctlr_mutex);
	spin_lock_init(&fip->ctlr_lock);
	fip->flogi_oxid = FC_XID_UNKNOWN;
	समयr_setup(&fip->समयr, fcoe_ctlr_समयout, 0);
	INIT_WORK(&fip->समयr_work, fcoe_ctlr_समयr_work);
	INIT_WORK(&fip->recv_work, fcoe_ctlr_recv_work);
	skb_queue_head_init(&fip->fip_recv_list);
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_init);

/**
 * fcoe_sysfs_fcf_add() - Add a fcoe_fcfअणु,_deviceपूर्ण to a fcoe_ctlrअणु,_deviceपूर्ण
 * @new: The newly discovered FCF
 *
 * Called with fip->ctlr_mutex held
 */
अटल पूर्णांक fcoe_sysfs_fcf_add(काष्ठा fcoe_fcf *new)
अणु
	काष्ठा fcoe_ctlr *fip = new->fip;
	काष्ठा fcoe_ctlr_device *ctlr_dev;
	काष्ठा fcoe_fcf_device *temp, *fcf_dev;
	पूर्णांक rc = -ENOMEM;

	LIBFCOE_FIP_DBG(fip, "New FCF fab %16.16llx mac %pM\n",
			new->fabric_name, new->fcf_mac);

	temp = kzalloc(माप(*temp), GFP_KERNEL);
	अगर (!temp)
		जाओ out;

	temp->fabric_name = new->fabric_name;
	temp->चयन_name = new->चयन_name;
	temp->fc_map = new->fc_map;
	temp->vfid = new->vfid;
	स_नकल(temp->mac, new->fcf_mac, ETH_ALEN);
	temp->priority = new->pri;
	temp->fka_period = new->fka_period;
	temp->selected = 0; /* शेष to unselected */

	/*
	 * If ctlr_dev करोesn't exist then it means we're a libfcoe user
	 * who करोesn't use fcoe_syfs and didn't allocate a fcoe_ctlr_device.
	 * fnic would be an example of a driver with this behavior. In this
	 * हाल we want to add the fcoe_fcf to the fcoe_ctlr list, but we
	 * करोn't want to make sysfs changes.
	 */

	ctlr_dev = fcoe_ctlr_to_ctlr_dev(fip);
	अगर (ctlr_dev) अणु
		mutex_lock(&ctlr_dev->lock);
		fcf_dev = fcoe_fcf_device_add(ctlr_dev, temp);
		अगर (unlikely(!fcf_dev)) अणु
			rc = -ENOMEM;
			mutex_unlock(&ctlr_dev->lock);
			जाओ out;
		पूर्ण

		/*
		 * The fcoe_sysfs layer can वापस a CONNECTED fcf that
		 * has a priv (fcf was never deleted) or a CONNECTED fcf
		 * that करोesn't have a priv (fcf was deleted). However,
		 * libfcoe will always delete FCFs beक्रमe trying to add
		 * them. This is ensured because both recv_adv and
		 * age_fcfs are रक्षित by the the fcoe_ctlr's mutex.
		 * This means that we should never get a FCF with a
		 * non-शून्य priv poपूर्णांकer.
		 */
		BUG_ON(fcf_dev->priv);

		fcf_dev->priv = new;
		new->fcf_dev = fcf_dev;
		mutex_unlock(&ctlr_dev->lock);
	पूर्ण

	list_add(&new->list, &fip->fcfs);
	fip->fcf_count++;
	rc = 0;

out:
	kमुक्त(temp);
	वापस rc;
पूर्ण

/**
 * fcoe_sysfs_fcf_del() - Remove a fcoe_fcfअणु,_deviceपूर्ण to a fcoe_ctlrअणु,_deviceपूर्ण
 * @new: The FCF to be हटाओd
 *
 * Called with fip->ctlr_mutex held
 */
अटल व्योम fcoe_sysfs_fcf_del(काष्ठा fcoe_fcf *new)
अणु
	काष्ठा fcoe_ctlr *fip = new->fip;
	काष्ठा fcoe_ctlr_device *cdev;
	काष्ठा fcoe_fcf_device *fcf_dev;

	list_del(&new->list);
	fip->fcf_count--;

	/*
	 * If ctlr_dev करोesn't exist then it means we're a libfcoe user
	 * who करोesn't use fcoe_syfs and didn't allocate a fcoe_ctlr_device
	 * or a fcoe_fcf_device.
	 *
	 * fnic would be an example of a driver with this behavior. In this
	 * हाल we want to हटाओ the fcoe_fcf from the fcoe_ctlr list (above),
	 * but we करोn't want to make sysfs changes.
	 */
	cdev = fcoe_ctlr_to_ctlr_dev(fip);
	अगर (cdev) अणु
		mutex_lock(&cdev->lock);
		fcf_dev = fcoe_fcf_to_fcf_dev(new);
		WARN_ON(!fcf_dev);
		new->fcf_dev = शून्य;
		fcoe_fcf_device_delete(fcf_dev);
		mutex_unlock(&cdev->lock);
	पूर्ण
	kमुक्त(new);
पूर्ण

/**
 * fcoe_ctlr_reset_fcfs() - Reset and मुक्त all FCFs क्रम a controller
 * @fip: The FCoE controller whose FCFs are to be reset
 *
 * Called with &fcoe_ctlr lock held.
 */
अटल व्योम fcoe_ctlr_reset_fcfs(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fcoe_fcf *fcf;
	काष्ठा fcoe_fcf *next;

	fip->sel_fcf = शून्य;
	list_क्रम_each_entry_safe(fcf, next, &fip->fcfs, list) अणु
		fcoe_sysfs_fcf_del(fcf);
	पूर्ण
	WARN_ON(fip->fcf_count);

	fip->sel_समय = 0;
पूर्ण

/**
 * fcoe_ctlr_destroy() - Disable and tear करोwn a FCoE controller
 * @fip: The FCoE controller to tear करोwn
 *
 * This is called by FCoE drivers beक्रमe मुक्तing the &fcoe_ctlr.
 *
 * The receive handler will have been deleted beक्रमe this to guarantee
 * that no more recv_work will be scheduled.
 *
 * The समयr routine will simply वापस once we set FIP_ST_DISABLED.
 * This guarantees that no further समयouts or work will be scheduled.
 */
व्योम fcoe_ctlr_destroy(काष्ठा fcoe_ctlr *fip)
अणु
	cancel_work_sync(&fip->recv_work);
	skb_queue_purge(&fip->fip_recv_list);

	mutex_lock(&fip->ctlr_mutex);
	fcoe_ctlr_set_state(fip, FIP_ST_DISABLED);
	fcoe_ctlr_reset_fcfs(fip);
	mutex_unlock(&fip->ctlr_mutex);
	del_समयr_sync(&fip->समयr);
	cancel_work_sync(&fip->समयr_work);
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_destroy);

/**
 * fcoe_ctlr_announce() - announce new FCF selection
 * @fip: The FCoE controller
 *
 * Also sets the destination MAC क्रम FCoE and control packets
 *
 * Called with neither ctlr_mutex nor ctlr_lock held.
 */
अटल व्योम fcoe_ctlr_announce(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fcoe_fcf *sel;
	काष्ठा fcoe_fcf *fcf;

	mutex_lock(&fip->ctlr_mutex);
	spin_lock_bh(&fip->ctlr_lock);

	kमुक्त_skb(fip->flogi_req);
	fip->flogi_req = शून्य;
	list_क्रम_each_entry(fcf, &fip->fcfs, list)
		fcf->flogi_sent = 0;

	spin_unlock_bh(&fip->ctlr_lock);
	sel = fip->sel_fcf;

	अगर (sel && ether_addr_equal(sel->fcf_mac, fip->dest_addr))
		जाओ unlock;
	अगर (!is_zero_ether_addr(fip->dest_addr)) अणु
		prपूर्णांकk(KERN_NOTICE "libfcoe: host%d: "
		       "FIP Fibre-Channel Forwarder MAC %pM deselected\n",
		       fip->lp->host->host_no, fip->dest_addr);
		eth_zero_addr(fip->dest_addr);
	पूर्ण
	अगर (sel) अणु
		prपूर्णांकk(KERN_INFO "libfcoe: host%d: FIP selected "
		       "Fibre-Channel Forwarder MAC %pM\n",
		       fip->lp->host->host_no, sel->fcf_mac);
		स_नकल(fip->dest_addr, sel->fcoe_mac, ETH_ALEN);
		fip->map_dest = 0;
	पूर्ण
unlock:
	mutex_unlock(&fip->ctlr_mutex);
पूर्ण

/**
 * fcoe_ctlr_fcoe_size() - Return the maximum FCoE size required क्रम VN_Port
 * @fip: The FCoE controller to get the maximum FCoE size from
 *
 * Returns the maximum packet size including the FCoE header and trailer,
 * but not including any Ethernet or VLAN headers.
 */
अटल अंतरभूत u32 fcoe_ctlr_fcoe_size(काष्ठा fcoe_ctlr *fip)
अणु
	/*
	 * Determine the max FCoE frame size allowed, including
	 * FCoE header and trailer.
	 * Note:  lp->mfs is currently the payload size, not the frame size.
	 */
	वापस fip->lp->mfs + माप(काष्ठा fc_frame_header) +
		माप(काष्ठा fcoe_hdr) + माप(काष्ठा fcoe_crc_eof);
पूर्ण

/**
 * fcoe_ctlr_solicit() - Send a FIP solicitation
 * @fip: The FCoE controller to send the solicitation on
 * @fcf: The destination FCF (अगर शून्य, a multicast solicitation is sent)
 */
अटल व्योम fcoe_ctlr_solicit(काष्ठा fcoe_ctlr *fip, काष्ठा fcoe_fcf *fcf)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fip_sol अणु
		काष्ठा ethhdr eth;
		काष्ठा fip_header fip;
		काष्ठा अणु
			काष्ठा fip_mac_desc mac;
			काष्ठा fip_wwn_desc wwnn;
			काष्ठा fip_size_desc size;
		पूर्ण __packed desc;
	पूर्ण  __packed * sol;
	u32 fcoe_size;

	skb = dev_alloc_skb(माप(*sol));
	अगर (!skb)
		वापस;

	sol = (काष्ठा fip_sol *)skb->data;

	स_रखो(sol, 0, माप(*sol));
	स_नकल(sol->eth.h_dest, fcf ? fcf->fcf_mac : fcoe_all_fcfs, ETH_ALEN);
	स_नकल(sol->eth.h_source, fip->ctl_src_addr, ETH_ALEN);
	sol->eth.h_proto = htons(ETH_P_FIP);

	sol->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	sol->fip.fip_op = htons(FIP_OP_DISC);
	sol->fip.fip_subcode = FIP_SC_SOL;
	sol->fip.fip_dl_len = htons(माप(sol->desc) / FIP_BPW);
	sol->fip.fip_flags = htons(FIP_FL_FPMA);
	अगर (fip->spma)
		sol->fip.fip_flags |= htons(FIP_FL_SPMA);

	sol->desc.mac.fd_desc.fip_dtype = FIP_DT_MAC;
	sol->desc.mac.fd_desc.fip_dlen = माप(sol->desc.mac) / FIP_BPW;
	स_नकल(sol->desc.mac.fd_mac, fip->ctl_src_addr, ETH_ALEN);

	sol->desc.wwnn.fd_desc.fip_dtype = FIP_DT_NAME;
	sol->desc.wwnn.fd_desc.fip_dlen = माप(sol->desc.wwnn) / FIP_BPW;
	put_unaligned_be64(fip->lp->wwnn, &sol->desc.wwnn.fd_wwn);

	fcoe_size = fcoe_ctlr_fcoe_size(fip);
	sol->desc.size.fd_desc.fip_dtype = FIP_DT_FCOE_SIZE;
	sol->desc.size.fd_desc.fip_dlen = माप(sol->desc.size) / FIP_BPW;
	sol->desc.size.fd_size = htons(fcoe_size);

	skb_put(skb, माप(*sol));
	skb->protocol = htons(ETH_P_FIP);
	skb->priority = fip->priority;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	fip->send(fip, skb);

	अगर (!fcf)
		fip->sol_समय = jअगरfies;
पूर्ण

/**
 * fcoe_ctlr_link_up() - Start FCoE controller
 * @fip: The FCoE controller to start
 *
 * Called from the LLD when the network link is पढ़ोy.
 */
व्योम fcoe_ctlr_link_up(काष्ठा fcoe_ctlr *fip)
अणु
	mutex_lock(&fip->ctlr_mutex);
	अगर (fip->state == FIP_ST_NON_FIP || fip->state == FIP_ST_AUTO) अणु
		mutex_unlock(&fip->ctlr_mutex);
		fc_linkup(fip->lp);
	पूर्ण अन्यथा अगर (fip->state == FIP_ST_LINK_WAIT) अणु
		अगर (fip->mode == FIP_MODE_NON_FIP)
			fcoe_ctlr_set_state(fip, FIP_ST_NON_FIP);
		अन्यथा
			fcoe_ctlr_set_state(fip, FIP_ST_AUTO);
		चयन (fip->mode) अणु
		शेष:
			LIBFCOE_FIP_DBG(fip, "invalid mode %d\n", fip->mode);
			fallthrough;
		हाल FIP_MODE_AUTO:
			LIBFCOE_FIP_DBG(fip, "%s", "setting AUTO mode.\n");
			fallthrough;
		हाल FIP_MODE_FABRIC:
		हाल FIP_MODE_NON_FIP:
			mutex_unlock(&fip->ctlr_mutex);
			fc_linkup(fip->lp);
			fcoe_ctlr_solicit(fip, शून्य);
			अवरोध;
		हाल FIP_MODE_VN2VN:
			fcoe_ctlr_vn_start(fip);
			mutex_unlock(&fip->ctlr_mutex);
			fc_linkup(fip->lp);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		mutex_unlock(&fip->ctlr_mutex);
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_link_up);

/**
 * fcoe_ctlr_reset() - Reset a FCoE controller
 * @fip:       The FCoE controller to reset
 */
अटल व्योम fcoe_ctlr_reset(काष्ठा fcoe_ctlr *fip)
अणु
	fcoe_ctlr_reset_fcfs(fip);
	del_समयr(&fip->समयr);
	fip->ctlr_ka_समय = 0;
	fip->port_ka_समय = 0;
	fip->sol_समय = 0;
	fip->flogi_oxid = FC_XID_UNKNOWN;
	fcoe_ctlr_map_dest(fip);
पूर्ण

/**
 * fcoe_ctlr_link_करोwn() - Stop a FCoE controller
 * @fip: The FCoE controller to be stopped
 *
 * Returns non-zero अगर the link was up and now isn't.
 *
 * Called from the LLD when the network link is not पढ़ोy.
 * There may be multiple calls जबतक the link is करोwn.
 */
पूर्णांक fcoe_ctlr_link_करोwn(काष्ठा fcoe_ctlr *fip)
अणु
	पूर्णांक link_dropped;

	LIBFCOE_FIP_DBG(fip, "link down.\n");
	mutex_lock(&fip->ctlr_mutex);
	fcoe_ctlr_reset(fip);
	link_dropped = fip->state != FIP_ST_LINK_WAIT;
	fcoe_ctlr_set_state(fip, FIP_ST_LINK_WAIT);
	mutex_unlock(&fip->ctlr_mutex);

	अगर (link_dropped)
		fc_linkकरोwn(fip->lp);
	वापस link_dropped;
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_link_करोwn);

/**
 * fcoe_ctlr_send_keep_alive() - Send a keep-alive to the selected FCF
 * @fip:   The FCoE controller to send the FKA on
 * @lport: libfc fc_lport to send from
 * @ports: 0 क्रम controller keep-alive, 1 क्रम port keep-alive
 * @sa:	   The source MAC address
 *
 * A controller keep-alive is sent every fka_period (typically 8 seconds).
 * The source MAC is the native MAC address.
 *
 * A port keep-alive is sent every 90 seconds जबतक logged in.
 * The source MAC is the asचिन्हित mapped source address.
 * The destination is the FCF's F-port.
 */
अटल व्योम fcoe_ctlr_send_keep_alive(काष्ठा fcoe_ctlr *fip,
				      काष्ठा fc_lport *lport,
				      पूर्णांक ports, u8 *sa)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fip_kal अणु
		काष्ठा ethhdr eth;
		काष्ठा fip_header fip;
		काष्ठा fip_mac_desc mac;
	पूर्ण __packed * kal;
	काष्ठा fip_vn_desc *vn;
	u32 len;
	काष्ठा fc_lport *lp;
	काष्ठा fcoe_fcf *fcf;

	fcf = fip->sel_fcf;
	lp = fip->lp;
	अगर (!fcf || (ports && !lp->port_id))
		वापस;

	len = माप(*kal) + ports * माप(*vn);
	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस;

	kal = (काष्ठा fip_kal *)skb->data;
	स_रखो(kal, 0, len);
	स_नकल(kal->eth.h_dest, fcf->fcf_mac, ETH_ALEN);
	स_नकल(kal->eth.h_source, sa, ETH_ALEN);
	kal->eth.h_proto = htons(ETH_P_FIP);

	kal->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	kal->fip.fip_op = htons(FIP_OP_CTRL);
	kal->fip.fip_subcode = FIP_SC_KEEP_ALIVE;
	kal->fip.fip_dl_len = htons((माप(kal->mac) +
				     ports * माप(*vn)) / FIP_BPW);
	kal->fip.fip_flags = htons(FIP_FL_FPMA);
	अगर (fip->spma)
		kal->fip.fip_flags |= htons(FIP_FL_SPMA);

	kal->mac.fd_desc.fip_dtype = FIP_DT_MAC;
	kal->mac.fd_desc.fip_dlen = माप(kal->mac) / FIP_BPW;
	स_नकल(kal->mac.fd_mac, fip->ctl_src_addr, ETH_ALEN);
	अगर (ports) अणु
		vn = (काष्ठा fip_vn_desc *)(kal + 1);
		vn->fd_desc.fip_dtype = FIP_DT_VN_ID;
		vn->fd_desc.fip_dlen = माप(*vn) / FIP_BPW;
		स_नकल(vn->fd_mac, fip->get_src_addr(lport), ETH_ALEN);
		hton24(vn->fd_fc_id, lport->port_id);
		put_unaligned_be64(lport->wwpn, &vn->fd_wwpn);
	पूर्ण
	skb_put(skb, len);
	skb->protocol = htons(ETH_P_FIP);
	skb->priority = fip->priority;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	fip->send(fip, skb);
पूर्ण

/**
 * fcoe_ctlr_encaps() - Encapsulate an ELS frame क्रम FIP, without sending it
 * @fip:   The FCoE controller क्रम the ELS frame
 * @lport: The local port
 * @dtype: The FIP descriptor type क्रम the frame
 * @skb:   The FCoE ELS frame including FC header but no FCoE headers
 * @d_id:  The destination port ID.
 *
 * Returns non-zero error code on failure.
 *
 * The caller must check that the length is a multiple of 4.
 *
 * The @skb must have enough headroom (28 bytes) and tailroom (8 bytes).
 * Headroom includes the FIP encapsulation description, FIP header, and
 * Ethernet header.  The tailroom is क्रम the FIP MAC descriptor.
 */
अटल पूर्णांक fcoe_ctlr_encaps(काष्ठा fcoe_ctlr *fip, काष्ठा fc_lport *lport,
			    u8 dtype, काष्ठा sk_buff *skb, u32 d_id)
अणु
	काष्ठा fip_encaps_head अणु
		काष्ठा ethhdr eth;
		काष्ठा fip_header fip;
		काष्ठा fip_encaps encaps;
	पूर्ण __packed * cap;
	काष्ठा fc_frame_header *fh;
	काष्ठा fip_mac_desc *mac;
	काष्ठा fcoe_fcf *fcf;
	माप_प्रकार dlen;
	u16 fip_flags;
	u8 op;

	fh = (काष्ठा fc_frame_header *)skb->data;
	op = *(u8 *)(fh + 1);
	dlen = माप(काष्ठा fip_encaps) + skb->len;	/* len beक्रमe push */
	cap = skb_push(skb, माप(*cap));
	स_रखो(cap, 0, माप(*cap));

	अगर (lport->poपूर्णांक_to_multipoपूर्णांक) अणु
		अगर (fcoe_ctlr_vn_lookup(fip, d_id, cap->eth.h_dest))
			वापस -ENODEV;
		fip_flags = 0;
	पूर्ण अन्यथा अणु
		fcf = fip->sel_fcf;
		अगर (!fcf)
			वापस -ENODEV;
		fip_flags = fcf->flags;
		fip_flags &= fip->spma ? FIP_FL_SPMA | FIP_FL_FPMA :
					 FIP_FL_FPMA;
		अगर (!fip_flags)
			वापस -ENODEV;
		स_नकल(cap->eth.h_dest, fcf->fcf_mac, ETH_ALEN);
	पूर्ण
	स_नकल(cap->eth.h_source, fip->ctl_src_addr, ETH_ALEN);
	cap->eth.h_proto = htons(ETH_P_FIP);

	cap->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	cap->fip.fip_op = htons(FIP_OP_LS);
	अगर (op == ELS_LS_ACC || op == ELS_LS_RJT)
		cap->fip.fip_subcode = FIP_SC_REP;
	अन्यथा
		cap->fip.fip_subcode = FIP_SC_REQ;
	cap->fip.fip_flags = htons(fip_flags);

	cap->encaps.fd_desc.fip_dtype = dtype;
	cap->encaps.fd_desc.fip_dlen = dlen / FIP_BPW;

	अगर (op != ELS_LS_RJT) अणु
		dlen += माप(*mac);
		mac = skb_put_zero(skb, माप(*mac));
		mac->fd_desc.fip_dtype = FIP_DT_MAC;
		mac->fd_desc.fip_dlen = माप(*mac) / FIP_BPW;
		अगर (dtype != FIP_DT_FLOGI && dtype != FIP_DT_FDISC) अणु
			स_नकल(mac->fd_mac, fip->get_src_addr(lport), ETH_ALEN);
		पूर्ण अन्यथा अगर (fip->mode == FIP_MODE_VN2VN) अणु
			hton24(mac->fd_mac, FIP_VN_FC_MAP);
			hton24(mac->fd_mac + 3, fip->port_id);
		पूर्ण अन्यथा अगर (fip_flags & FIP_FL_SPMA) अणु
			LIBFCOE_FIP_DBG(fip, "FLOGI/FDISC sent with SPMA\n");
			स_नकल(mac->fd_mac, fip->ctl_src_addr, ETH_ALEN);
		पूर्ण अन्यथा अणु
			LIBFCOE_FIP_DBG(fip, "FLOGI/FDISC sent with FPMA\n");
			/* FPMA only FLOGI.  Must leave the MAC desc zeroed. */
		पूर्ण
	पूर्ण
	cap->fip.fip_dl_len = htons(dlen / FIP_BPW);

	skb->protocol = htons(ETH_P_FIP);
	skb->priority = fip->priority;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);
	वापस 0;
पूर्ण

/**
 * fcoe_ctlr_els_send() - Send an ELS frame encapsulated by FIP अगर appropriate.
 * @fip:	FCoE controller.
 * @lport:	libfc fc_lport to send from
 * @skb:	FCoE ELS frame including FC header but no FCoE headers.
 *
 * Returns a non-zero error code अगर the frame should not be sent.
 * Returns zero अगर the caller should send the frame with FCoE encapsulation.
 *
 * The caller must check that the length is a multiple of 4.
 * The SKB must have enough headroom (28 bytes) and tailroom (8 bytes).
 * The the skb must also be an fc_frame.
 *
 * This is called from the lower-level driver with spinlocks held,
 * so we must not take a mutex here.
 */
पूर्णांक fcoe_ctlr_els_send(काष्ठा fcoe_ctlr *fip, काष्ठा fc_lport *lport,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा fc_frame *fp;
	काष्ठा fc_frame_header *fh;
	u16 old_xid;
	u8 op;
	u8 mac[ETH_ALEN];

	fp = container_of(skb, काष्ठा fc_frame, skb);
	fh = (काष्ठा fc_frame_header *)skb->data;
	op = *(u8 *)(fh + 1);

	अगर (op == ELS_FLOGI && fip->mode != FIP_MODE_VN2VN) अणु
		old_xid = fip->flogi_oxid;
		fip->flogi_oxid = ntohs(fh->fh_ox_id);
		अगर (fip->state == FIP_ST_AUTO) अणु
			अगर (old_xid == FC_XID_UNKNOWN)
				fip->flogi_count = 0;
			fip->flogi_count++;
			अगर (fip->flogi_count < 3)
				जाओ drop;
			fcoe_ctlr_map_dest(fip);
			वापस 0;
		पूर्ण
		अगर (fip->state == FIP_ST_NON_FIP)
			fcoe_ctlr_map_dest(fip);
	पूर्ण

	अगर (fip->state == FIP_ST_NON_FIP)
		वापस 0;
	अगर (!fip->sel_fcf && fip->mode != FIP_MODE_VN2VN)
		जाओ drop;
	चयन (op) अणु
	हाल ELS_FLOGI:
		op = FIP_DT_FLOGI;
		अगर (fip->mode == FIP_MODE_VN2VN)
			अवरोध;
		spin_lock_bh(&fip->ctlr_lock);
		kमुक्त_skb(fip->flogi_req);
		fip->flogi_req = skb;
		fip->flogi_req_send = 1;
		spin_unlock_bh(&fip->ctlr_lock);
		schedule_work(&fip->समयr_work);
		वापस -EINPROGRESS;
	हाल ELS_FDISC:
		अगर (ntoh24(fh->fh_s_id))
			वापस 0;
		op = FIP_DT_FDISC;
		अवरोध;
	हाल ELS_LOGO:
		अगर (fip->mode == FIP_MODE_VN2VN) अणु
			अगर (fip->state != FIP_ST_VNMP_UP)
				जाओ drop;
			अगर (ntoh24(fh->fh_d_id) == FC_FID_FLOGI)
				जाओ drop;
		पूर्ण अन्यथा अणु
			अगर (fip->state != FIP_ST_ENABLED)
				वापस 0;
			अगर (ntoh24(fh->fh_d_id) != FC_FID_FLOGI)
				वापस 0;
		पूर्ण
		op = FIP_DT_LOGO;
		अवरोध;
	हाल ELS_LS_ACC:
		/*
		 * If non-FIP, we may have gotten an SID by accepting an FLOGI
		 * from a poपूर्णांक-to-poपूर्णांक connection.  Switch to using
		 * the source mac based on the SID.  The destination
		 * MAC in this हाल would have been set by receiving the
		 * FLOGI.
		 */
		अगर (fip->state == FIP_ST_NON_FIP) अणु
			अगर (fip->flogi_oxid == FC_XID_UNKNOWN)
				वापस 0;
			fip->flogi_oxid = FC_XID_UNKNOWN;
			fc_fcoe_set_mac(mac, fh->fh_d_id);
			fip->update_mac(lport, mac);
		पूर्ण
		fallthrough;
	हाल ELS_LS_RJT:
		op = fr_encaps(fp);
		अगर (op)
			अवरोध;
		वापस 0;
	शेष:
		अगर (fip->state != FIP_ST_ENABLED &&
		    fip->state != FIP_ST_VNMP_UP)
			जाओ drop;
		वापस 0;
	पूर्ण
	LIBFCOE_FIP_DBG(fip, "els_send op %u d_id %x\n",
			op, ntoh24(fh->fh_d_id));
	अगर (fcoe_ctlr_encaps(fip, lport, op, skb, ntoh24(fh->fh_d_id)))
		जाओ drop;
	fip->send(fip, skb);
	वापस -EINPROGRESS;
drop:
	LIBFCOE_FIP_DBG(fip, "drop els_send op %u d_id %x\n",
			op, ntoh24(fh->fh_d_id));
	kमुक्त_skb(skb);
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_els_send);

/**
 * fcoe_ctlr_age_fcfs() - Reset and मुक्त all old FCFs क्रम a controller
 * @fip: The FCoE controller to मुक्त FCFs on
 *
 * Called with lock held and preemption disabled.
 *
 * An FCF is considered old अगर we have missed two advertisements.
 * That is, there have been no valid advertisement from it क्रम 2.5
 * बार its keep-alive period.
 *
 * In addition, determine the समय when an FCF selection can occur.
 *
 * Also, increment the MissDiscAdvCount when no advertisement is received
 * क्रम the corresponding FCF क्रम 1.5 * FKA_ADV_PERIOD (FC-BB-5 LESB).
 *
 * Returns the समय in jअगरfies क्रम the next call.
 */
अटल अचिन्हित दीर्घ fcoe_ctlr_age_fcfs(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fcoe_fcf *fcf;
	काष्ठा fcoe_fcf *next;
	अचिन्हित दीर्घ next_समयr = jअगरfies + msecs_to_jअगरfies(FIP_VN_KA_PERIOD);
	अचिन्हित दीर्घ deadline;
	अचिन्हित दीर्घ sel_समय = 0;
	काष्ठा list_head del_list;
	काष्ठा fc_stats *stats;

	INIT_LIST_HEAD(&del_list);

	stats = per_cpu_ptr(fip->lp->stats, get_cpu());

	list_क्रम_each_entry_safe(fcf, next, &fip->fcfs, list) अणु
		deadline = fcf->समय + fcf->fka_period + fcf->fka_period / 2;
		अगर (fip->sel_fcf == fcf) अणु
			अगर (समय_after(jअगरfies, deadline)) अणु
				stats->MissDiscAdvCount++;
				prपूर्णांकk(KERN_INFO "libfcoe: host%d: "
				       "Missing Discovery Advertisement "
				       "for fab %16.16llx count %lld\n",
				       fip->lp->host->host_no, fcf->fabric_name,
				       stats->MissDiscAdvCount);
			पूर्ण अन्यथा अगर (समय_after(next_समयr, deadline))
				next_समयr = deadline;
		पूर्ण

		deadline += fcf->fka_period;
		अगर (समय_after_eq(jअगरfies, deadline)) अणु
			अगर (fip->sel_fcf == fcf)
				fip->sel_fcf = शून्य;
			/*
			 * Move to delete list so we can call
			 * fcoe_sysfs_fcf_del (which can sleep)
			 * after the put_cpu().
			 */
			list_del(&fcf->list);
			list_add(&fcf->list, &del_list);
			stats->VLinkFailureCount++;
		पूर्ण अन्यथा अणु
			अगर (समय_after(next_समयr, deadline))
				next_समयr = deadline;
			अगर (fcoe_ctlr_mtu_valid(fcf) &&
			    (!sel_समय || समय_beक्रमe(sel_समय, fcf->समय)))
				sel_समय = fcf->समय;
		पूर्ण
	पूर्ण
	put_cpu();

	list_क्रम_each_entry_safe(fcf, next, &del_list, list) अणु
		/* Removes fcf from current list */
		fcoe_sysfs_fcf_del(fcf);
	पूर्ण

	अगर (sel_समय && !fip->sel_fcf && !fip->sel_समय) अणु
		sel_समय += msecs_to_jअगरfies(FCOE_CTLR_START_DELAY);
		fip->sel_समय = sel_समय;
	पूर्ण

	वापस next_समयr;
पूर्ण

/**
 * fcoe_ctlr_parse_adv() - Decode a FIP advertisement पूर्णांकo a new FCF entry
 * @fip: The FCoE controller receiving the advertisement
 * @skb: The received FIP advertisement frame
 * @fcf: The resulting FCF entry
 *
 * Returns zero on a valid parsed advertisement,
 * otherwise वापसs non zero value.
 */
अटल पूर्णांक fcoe_ctlr_parse_adv(काष्ठा fcoe_ctlr *fip,
			       काष्ठा sk_buff *skb, काष्ठा fcoe_fcf *fcf)
अणु
	काष्ठा fip_header *fiph;
	काष्ठा fip_desc *desc = शून्य;
	काष्ठा fip_wwn_desc *wwn;
	काष्ठा fip_fab_desc *fab;
	काष्ठा fip_fka_desc *fka;
	अचिन्हित दीर्घ t;
	माप_प्रकार rlen;
	माप_प्रकार dlen;
	u32 desc_mask;

	स_रखो(fcf, 0, माप(*fcf));
	fcf->fka_period = msecs_to_jअगरfies(FCOE_CTLR_DEF_FKA);

	fiph = (काष्ठा fip_header *)skb->data;
	fcf->flags = ntohs(fiph->fip_flags);

	/*
	 * mask of required descriptors. validating each one clears its bit.
	 */
	desc_mask = BIT(FIP_DT_PRI) | BIT(FIP_DT_MAC) | BIT(FIP_DT_NAME) |
			BIT(FIP_DT_FAB) | BIT(FIP_DT_FKA);

	rlen = ntohs(fiph->fip_dl_len) * 4;
	अगर (rlen + माप(*fiph) > skb->len)
		वापस -EINVAL;

	desc = (काष्ठा fip_desc *)(fiph + 1);
	जबतक (rlen > 0) अणु
		dlen = desc->fip_dlen * FIP_BPW;
		अगर (dlen < माप(*desc) || dlen > rlen)
			वापस -EINVAL;
		/* Drop Adv अगर there are duplicate critical descriptors */
		अगर ((desc->fip_dtype < 32) &&
		    !(desc_mask & 1U << desc->fip_dtype)) अणु
			LIBFCOE_FIP_DBG(fip, "Duplicate Critical "
					"Descriptors in FIP adv\n");
			वापस -EINVAL;
		पूर्ण
		चयन (desc->fip_dtype) अणु
		हाल FIP_DT_PRI:
			अगर (dlen != माप(काष्ठा fip_pri_desc))
				जाओ len_err;
			fcf->pri = ((काष्ठा fip_pri_desc *)desc)->fd_pri;
			desc_mask &= ~BIT(FIP_DT_PRI);
			अवरोध;
		हाल FIP_DT_MAC:
			अगर (dlen != माप(काष्ठा fip_mac_desc))
				जाओ len_err;
			स_नकल(fcf->fcf_mac,
			       ((काष्ठा fip_mac_desc *)desc)->fd_mac,
			       ETH_ALEN);
			स_नकल(fcf->fcoe_mac, fcf->fcf_mac, ETH_ALEN);
			अगर (!is_valid_ether_addr(fcf->fcf_mac)) अणु
				LIBFCOE_FIP_DBG(fip,
					"Invalid MAC addr %pM in FIP adv\n",
					fcf->fcf_mac);
				वापस -EINVAL;
			पूर्ण
			desc_mask &= ~BIT(FIP_DT_MAC);
			अवरोध;
		हाल FIP_DT_NAME:
			अगर (dlen != माप(काष्ठा fip_wwn_desc))
				जाओ len_err;
			wwn = (काष्ठा fip_wwn_desc *)desc;
			fcf->चयन_name = get_unaligned_be64(&wwn->fd_wwn);
			desc_mask &= ~BIT(FIP_DT_NAME);
			अवरोध;
		हाल FIP_DT_FAB:
			अगर (dlen != माप(काष्ठा fip_fab_desc))
				जाओ len_err;
			fab = (काष्ठा fip_fab_desc *)desc;
			fcf->fabric_name = get_unaligned_be64(&fab->fd_wwn);
			fcf->vfid = ntohs(fab->fd_vfid);
			fcf->fc_map = ntoh24(fab->fd_map);
			desc_mask &= ~BIT(FIP_DT_FAB);
			अवरोध;
		हाल FIP_DT_FKA:
			अगर (dlen != माप(काष्ठा fip_fka_desc))
				जाओ len_err;
			fka = (काष्ठा fip_fka_desc *)desc;
			अगर (fka->fd_flags & FIP_FKA_ADV_D)
				fcf->fd_flags = 1;
			t = ntohl(fka->fd_fka_period);
			अगर (t >= FCOE_CTLR_MIN_FKA)
				fcf->fka_period = msecs_to_jअगरfies(t);
			desc_mask &= ~BIT(FIP_DT_FKA);
			अवरोध;
		हाल FIP_DT_MAP_OUI:
		हाल FIP_DT_FCOE_SIZE:
		हाल FIP_DT_FLOGI:
		हाल FIP_DT_FDISC:
		हाल FIP_DT_LOGO:
		हाल FIP_DT_ELP:
		शेष:
			LIBFCOE_FIP_DBG(fip, "unexpected descriptor type %x "
					"in FIP adv\n", desc->fip_dtype);
			/* standard says ignore unknown descriptors >= 128 */
			अगर (desc->fip_dtype < FIP_DT_NON_CRITICAL)
				वापस -EINVAL;
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण
	अगर (!fcf->fc_map || (fcf->fc_map & 0x10000))
		वापस -EINVAL;
	अगर (!fcf->चयन_name)
		वापस -EINVAL;
	अगर (desc_mask) अणु
		LIBFCOE_FIP_DBG(fip, "adv missing descriptors mask %x\n",
				desc_mask);
		वापस -EINVAL;
	पूर्ण
	वापस 0;

len_err:
	LIBFCOE_FIP_DBG(fip, "FIP length error in descriptor type %x len %zu\n",
			desc->fip_dtype, dlen);
	वापस -EINVAL;
पूर्ण

/**
 * fcoe_ctlr_recv_adv() - Handle an incoming advertisement
 * @fip: The FCoE controller receiving the advertisement
 * @skb: The received FIP packet
 */
अटल व्योम fcoe_ctlr_recv_adv(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fcoe_fcf *fcf;
	काष्ठा fcoe_fcf new;
	अचिन्हित दीर्घ sol_tov = msecs_to_jअगरfies(FCOE_CTLR_SOL_TOV);
	पूर्णांक first = 0;
	पूर्णांक mtu_valid;
	पूर्णांक found = 0;
	पूर्णांक rc = 0;

	अगर (fcoe_ctlr_parse_adv(fip, skb, &new))
		वापस;

	mutex_lock(&fip->ctlr_mutex);
	first = list_empty(&fip->fcfs);
	list_क्रम_each_entry(fcf, &fip->fcfs, list) अणु
		अगर (fcf->चयन_name == new.चयन_name &&
		    fcf->fabric_name == new.fabric_name &&
		    fcf->fc_map == new.fc_map &&
		    ether_addr_equal(fcf->fcf_mac, new.fcf_mac)) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		अगर (fip->fcf_count >= FCOE_CTLR_FCF_LIMIT)
			जाओ out;

		fcf = kदो_स्मृति(माप(*fcf), GFP_ATOMIC);
		अगर (!fcf)
			जाओ out;

		स_नकल(fcf, &new, माप(new));
		fcf->fip = fip;
		rc = fcoe_sysfs_fcf_add(fcf);
		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR "Failed to allocate sysfs instance "
			       "for FCF, fab %16.16llx mac %pM\n",
			       new.fabric_name, new.fcf_mac);
			kमुक्त(fcf);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Update the FCF's keep-alive descriptor flags.
		 * Other flag changes from new advertisements are
		 * ignored after a solicited advertisement is
		 * received and the FCF is selectable (usable).
		 */
		fcf->fd_flags = new.fd_flags;
		अगर (!fcoe_ctlr_fcf_usable(fcf))
			fcf->flags = new.flags;

		अगर (fcf == fip->sel_fcf && !fcf->fd_flags) अणु
			fip->ctlr_ka_समय -= fcf->fka_period;
			fip->ctlr_ka_समय += new.fka_period;
			अगर (समय_beक्रमe(fip->ctlr_ka_समय, fip->समयr.expires))
				mod_समयr(&fip->समयr, fip->ctlr_ka_समय);
		पूर्ण
		fcf->fka_period = new.fka_period;
		स_नकल(fcf->fcf_mac, new.fcf_mac, ETH_ALEN);
	पूर्ण

	mtu_valid = fcoe_ctlr_mtu_valid(fcf);
	fcf->समय = jअगरfies;
	अगर (!found)
		LIBFCOE_FIP_DBG(fip, "New FCF fab %16.16llx mac %pM\n",
				fcf->fabric_name, fcf->fcf_mac);

	/*
	 * If this advertisement is not solicited and our max receive size
	 * hasn't been verअगरied, send a solicited advertisement.
	 */
	अगर (!mtu_valid)
		fcoe_ctlr_solicit(fip, fcf);

	/*
	 * If its been a जबतक since we did a solicit, and this is
	 * the first advertisement we've received, करो a multicast
	 * solicitation to gather as many advertisements as we can
	 * beक्रमe selection occurs.
	 */
	अगर (first && समय_after(jअगरfies, fip->sol_समय + sol_tov))
		fcoe_ctlr_solicit(fip, शून्य);

	/*
	 * Put this FCF at the head of the list क्रम priority among equals.
	 * This helps in the हाल of an NPV चयन which insists we use
	 * the FCF that answers multicast solicitations, not the others that
	 * are sending periodic multicast advertisements.
	 */
	अगर (mtu_valid)
		list_move(&fcf->list, &fip->fcfs);

	/*
	 * If this is the first validated FCF, note the समय and
	 * set a समयr to trigger selection.
	 */
	अगर (mtu_valid && !fip->sel_fcf && !fip->sel_समय &&
	    fcoe_ctlr_fcf_usable(fcf)) अणु
		fip->sel_समय = jअगरfies +
			msecs_to_jअगरfies(FCOE_CTLR_START_DELAY);
		अगर (!समयr_pending(&fip->समयr) ||
		    समय_beक्रमe(fip->sel_समय, fip->समयr.expires))
			mod_समयr(&fip->समयr, fip->sel_समय);
	पूर्ण

out:
	mutex_unlock(&fip->ctlr_mutex);
पूर्ण

/**
 * fcoe_ctlr_recv_els() - Handle an incoming FIP encapsulated ELS frame
 * @fip: The FCoE controller which received the packet
 * @skb: The received FIP packet
 */
अटल व्योम fcoe_ctlr_recv_els(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fip_header *fiph;
	काष्ठा fc_frame *fp = (काष्ठा fc_frame *)skb;
	काष्ठा fc_frame_header *fh = शून्य;
	काष्ठा fip_desc *desc;
	काष्ठा fip_encaps *els;
	काष्ठा fcoe_fcf *sel;
	काष्ठा fc_stats *stats;
	क्रमागत fip_desc_type els_dtype = 0;
	u8 els_op;
	u8 sub;
	u8 granted_mac[ETH_ALEN] = अणु 0 पूर्ण;
	माप_प्रकार els_len = 0;
	माप_प्रकार rlen;
	माप_प्रकार dlen;
	u32 desc_mask = 0;
	u32 desc_cnt = 0;

	fiph = (काष्ठा fip_header *)skb->data;
	sub = fiph->fip_subcode;
	अगर (sub != FIP_SC_REQ && sub != FIP_SC_REP)
		जाओ drop;

	rlen = ntohs(fiph->fip_dl_len) * 4;
	अगर (rlen + माप(*fiph) > skb->len)
		जाओ drop;

	desc = (काष्ठा fip_desc *)(fiph + 1);
	जबतक (rlen > 0) अणु
		desc_cnt++;
		dlen = desc->fip_dlen * FIP_BPW;
		अगर (dlen < माप(*desc) || dlen > rlen)
			जाओ drop;
		/* Drop ELS अगर there are duplicate critical descriptors */
		अगर (desc->fip_dtype < 32) अणु
			अगर ((desc->fip_dtype != FIP_DT_MAC) &&
			    (desc_mask & 1U << desc->fip_dtype)) अणु
				LIBFCOE_FIP_DBG(fip, "Duplicate Critical "
						"Descriptors in FIP ELS\n");
				जाओ drop;
			पूर्ण
			desc_mask |= (1 << desc->fip_dtype);
		पूर्ण
		चयन (desc->fip_dtype) अणु
		हाल FIP_DT_MAC:
			sel = fip->sel_fcf;
			अगर (desc_cnt == 1) अणु
				LIBFCOE_FIP_DBG(fip, "FIP descriptors "
						"received out of order\n");
				जाओ drop;
			पूर्ण
			/*
			 * Some चयन implementations send two MAC descriptors,
			 * with first MAC(granted_mac) being the FPMA, and the
			 * second one(fcoe_mac) is used as destination address
			 * क्रम sending/receiving FCoE packets. FIP traffic is
			 * sent using fip_mac. For regular चयनes, both
			 * fip_mac and fcoe_mac would be the same.
			 */
			अगर (desc_cnt == 2)
				स_नकल(granted_mac,
				       ((काष्ठा fip_mac_desc *)desc)->fd_mac,
				       ETH_ALEN);

			अगर (dlen != माप(काष्ठा fip_mac_desc))
				जाओ len_err;

			अगर ((desc_cnt == 3) && (sel))
				स_नकल(sel->fcoe_mac,
				       ((काष्ठा fip_mac_desc *)desc)->fd_mac,
				       ETH_ALEN);
			अवरोध;
		हाल FIP_DT_FLOGI:
		हाल FIP_DT_FDISC:
		हाल FIP_DT_LOGO:
		हाल FIP_DT_ELP:
			अगर (desc_cnt != 1) अणु
				LIBFCOE_FIP_DBG(fip, "FIP descriptors "
						"received out of order\n");
				जाओ drop;
			पूर्ण
			अगर (fh)
				जाओ drop;
			अगर (dlen < माप(*els) + माप(*fh) + 1)
				जाओ len_err;
			els_len = dlen - माप(*els);
			els = (काष्ठा fip_encaps *)desc;
			fh = (काष्ठा fc_frame_header *)(els + 1);
			els_dtype = desc->fip_dtype;
			अवरोध;
		शेष:
			LIBFCOE_FIP_DBG(fip, "unexpected descriptor type %x "
					"in FIP adv\n", desc->fip_dtype);
			/* standard says ignore unknown descriptors >= 128 */
			अगर (desc->fip_dtype < FIP_DT_NON_CRITICAL)
				जाओ drop;
			अगर (desc_cnt <= 2) अणु
				LIBFCOE_FIP_DBG(fip, "FIP descriptors "
						"received out of order\n");
				जाओ drop;
			पूर्ण
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण

	अगर (!fh)
		जाओ drop;
	els_op = *(u8 *)(fh + 1);

	अगर ((els_dtype == FIP_DT_FLOGI || els_dtype == FIP_DT_FDISC) &&
	    sub == FIP_SC_REP && fip->mode != FIP_MODE_VN2VN) अणु
		अगर (els_op == ELS_LS_ACC) अणु
			अगर (!is_valid_ether_addr(granted_mac)) अणु
				LIBFCOE_FIP_DBG(fip,
					"Invalid MAC address %pM in FIP ELS\n",
					granted_mac);
				जाओ drop;
			पूर्ण
			स_नकल(fr_cb(fp)->granted_mac, granted_mac, ETH_ALEN);

			अगर (fip->flogi_oxid == ntohs(fh->fh_ox_id)) अणु
				fip->flogi_oxid = FC_XID_UNKNOWN;
				अगर (els_dtype == FIP_DT_FLOGI)
					fcoe_ctlr_announce(fip);
			पूर्ण
		पूर्ण अन्यथा अगर (els_dtype == FIP_DT_FLOGI &&
			   !fcoe_ctlr_flogi_retry(fip))
			जाओ drop;	/* retrying FLOGI so drop reject */
	पूर्ण

	अगर ((desc_cnt == 0) || ((els_op != ELS_LS_RJT) &&
	    (!(1U << FIP_DT_MAC & desc_mask)))) अणु
		LIBFCOE_FIP_DBG(fip, "Missing critical descriptors "
				"in FIP ELS\n");
		जाओ drop;
	पूर्ण

	/*
	 * Convert skb पूर्णांकo an fc_frame containing only the ELS.
	 */
	skb_pull(skb, (u8 *)fh - skb->data);
	skb_trim(skb, els_len);
	fp = (काष्ठा fc_frame *)skb;
	fc_frame_init(fp);
	fr_sof(fp) = FC_SOF_I3;
	fr_eof(fp) = FC_खातापूर्ण_T;
	fr_dev(fp) = lport;
	fr_encaps(fp) = els_dtype;

	stats = per_cpu_ptr(lport->stats, get_cpu());
	stats->RxFrames++;
	stats->RxWords += skb->len / FIP_BPW;
	put_cpu();

	fc_exch_recv(lport, fp);
	वापस;

len_err:
	LIBFCOE_FIP_DBG(fip, "FIP length error in descriptor type %x len %zu\n",
			desc->fip_dtype, dlen);
drop:
	kमुक्त_skb(skb);
पूर्ण

/**
 * fcoe_ctlr_recv_clr_vlink() - Handle an incoming link reset frame
 * @fip: The FCoE controller that received the frame
 * @skb: The received FIP packet
 *
 * There may be multiple VN_Port descriptors.
 * The overall length has alपढ़ोy been checked.
 */
अटल व्योम fcoe_ctlr_recv_clr_vlink(काष्ठा fcoe_ctlr *fip,
				     काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_desc *desc;
	काष्ठा fip_mac_desc *mp;
	काष्ठा fip_wwn_desc *wp;
	काष्ठा fip_vn_desc *vp;
	माप_प्रकार rlen;
	माप_प्रकार dlen;
	काष्ठा fcoe_fcf *fcf = fip->sel_fcf;
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fc_lport *vn_port = शून्य;
	u32 desc_mask;
	पूर्णांक num_vlink_desc;
	पूर्णांक reset_phys_port = 0;
	काष्ठा fip_vn_desc **vlink_desc_arr = शून्य;
	काष्ठा fip_header *fh = (काष्ठा fip_header *)skb->data;
	काष्ठा ethhdr *eh = eth_hdr(skb);

	LIBFCOE_FIP_DBG(fip, "Clear Virtual Link received\n");

	अगर (!fcf) अणु
		/*
		 * We are yet to select best FCF, but we got CVL in the
		 * meanसमय. reset the ctlr and let it rediscover the FCF
		 */
		LIBFCOE_FIP_DBG(fip, "Resetting fcoe_ctlr as FCF has not been "
		    "selected yet\n");
		mutex_lock(&fip->ctlr_mutex);
		fcoe_ctlr_reset(fip);
		mutex_unlock(&fip->ctlr_mutex);
		वापस;
	पूर्ण

	/*
	 * If we've selected an FCF check that the CVL is from there to aव्योम
	 * processing CVLs from an unexpected source.  If it is from an
	 * unexpected source drop it on the न्यूनमान.
	 */
	अगर (!ether_addr_equal(eh->h_source, fcf->fcf_mac)) अणु
		LIBFCOE_FIP_DBG(fip, "Dropping CVL due to source address "
		    "mismatch with FCF src=%pM\n", eh->h_source);
		वापस;
	पूर्ण

	/*
	 * If we haven't logged पूर्णांकo the fabric but receive a CVL we should
	 * reset everything and go back to solicitation.
	 */
	अगर (!lport->port_id) अणु
		LIBFCOE_FIP_DBG(fip, "lport not logged in, resoliciting\n");
		mutex_lock(&fip->ctlr_mutex);
		fcoe_ctlr_reset(fip);
		mutex_unlock(&fip->ctlr_mutex);
		fc_lport_reset(fip->lp);
		fcoe_ctlr_solicit(fip, शून्य);
		वापस;
	पूर्ण

	/*
	 * mask of required descriptors.  Validating each one clears its bit.
	 */
	desc_mask = BIT(FIP_DT_MAC) | BIT(FIP_DT_NAME);

	rlen = ntohs(fh->fip_dl_len) * FIP_BPW;
	desc = (काष्ठा fip_desc *)(fh + 1);

	/*
	 * Actually need to subtract 'sizeof(*mp) - sizeof(*wp)' from 'rlen'
	 * beक्रमe determining max Vx_Port descriptor but a buggy FCF could have
	 * omitted either or both MAC Address and Name Identअगरier descriptors
	 */
	num_vlink_desc = rlen / माप(*vp);
	अगर (num_vlink_desc)
		vlink_desc_arr = kदो_स्मृति_array(num_vlink_desc, माप(vp),
					       GFP_ATOMIC);
	अगर (!vlink_desc_arr)
		वापस;
	num_vlink_desc = 0;

	जबतक (rlen >= माप(*desc)) अणु
		dlen = desc->fip_dlen * FIP_BPW;
		अगर (dlen > rlen)
			जाओ err;
		/* Drop CVL अगर there are duplicate critical descriptors */
		अगर ((desc->fip_dtype < 32) &&
		    (desc->fip_dtype != FIP_DT_VN_ID) &&
		    !(desc_mask & 1U << desc->fip_dtype)) अणु
			LIBFCOE_FIP_DBG(fip, "Duplicate Critical "
					"Descriptors in FIP CVL\n");
			जाओ err;
		पूर्ण
		चयन (desc->fip_dtype) अणु
		हाल FIP_DT_MAC:
			mp = (काष्ठा fip_mac_desc *)desc;
			अगर (dlen < माप(*mp))
				जाओ err;
			अगर (!ether_addr_equal(mp->fd_mac, fcf->fcf_mac))
				जाओ err;
			desc_mask &= ~BIT(FIP_DT_MAC);
			अवरोध;
		हाल FIP_DT_NAME:
			wp = (काष्ठा fip_wwn_desc *)desc;
			अगर (dlen < माप(*wp))
				जाओ err;
			अगर (get_unaligned_be64(&wp->fd_wwn) != fcf->चयन_name)
				जाओ err;
			desc_mask &= ~BIT(FIP_DT_NAME);
			अवरोध;
		हाल FIP_DT_VN_ID:
			vp = (काष्ठा fip_vn_desc *)desc;
			अगर (dlen < माप(*vp))
				जाओ err;
			vlink_desc_arr[num_vlink_desc++] = vp;
			vn_port = fc_vport_id_lookup(lport,
						      ntoh24(vp->fd_fc_id));
			अगर (vn_port && (vn_port == lport)) अणु
				mutex_lock(&fip->ctlr_mutex);
				per_cpu_ptr(lport->stats,
					    get_cpu())->VLinkFailureCount++;
				put_cpu();
				fcoe_ctlr_reset(fip);
				mutex_unlock(&fip->ctlr_mutex);
			पूर्ण
			अवरोध;
		शेष:
			/* standard says ignore unknown descriptors >= 128 */
			अगर (desc->fip_dtype < FIP_DT_NON_CRITICAL)
				जाओ err;
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण

	/*
	 * reset only अगर all required descriptors were present and valid.
	 */
	अगर (desc_mask)
		LIBFCOE_FIP_DBG(fip, "missing descriptors mask %x\n",
				desc_mask);
	अन्यथा अगर (!num_vlink_desc) अणु
		LIBFCOE_FIP_DBG(fip, "CVL: no Vx_Port descriptor found\n");
		/*
		 * No Vx_Port description. Clear all NPIV ports,
		 * followed by physical port
		 */
		mutex_lock(&fip->ctlr_mutex);
		per_cpu_ptr(lport->stats, get_cpu())->VLinkFailureCount++;
		put_cpu();
		fcoe_ctlr_reset(fip);
		mutex_unlock(&fip->ctlr_mutex);

		mutex_lock(&lport->lp_mutex);
		list_क्रम_each_entry(vn_port, &lport->vports, list)
			fc_lport_reset(vn_port);
		mutex_unlock(&lport->lp_mutex);

		fc_lport_reset(fip->lp);
		fcoe_ctlr_solicit(fip, शून्य);
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		LIBFCOE_FIP_DBG(fip, "performing Clear Virtual Link\n");
		क्रम (i = 0; i < num_vlink_desc; i++) अणु
			vp = vlink_desc_arr[i];
			vn_port = fc_vport_id_lookup(lport,
						     ntoh24(vp->fd_fc_id));
			अगर (!vn_port)
				जारी;

			/*
			 * 'port_id' is alपढ़ोy validated, check MAC address and
			 * wwpn
			 */
			अगर (!ether_addr_equal(fip->get_src_addr(vn_port),
					      vp->fd_mac) ||
				get_unaligned_be64(&vp->fd_wwpn) !=
							vn_port->wwpn)
				जारी;

			अगर (vn_port == lport)
				/*
				 * Physical port, defer processing till all
				 * listed NPIV ports are cleared
				 */
				reset_phys_port = 1;
			अन्यथा    /* NPIV port */
				fc_lport_reset(vn_port);
		पूर्ण

		अगर (reset_phys_port) अणु
			fc_lport_reset(fip->lp);
			fcoe_ctlr_solicit(fip, शून्य);
		पूर्ण
	पूर्ण

err:
	kमुक्त(vlink_desc_arr);
पूर्ण

/**
 * fcoe_ctlr_recv() - Receive a FIP packet
 * @fip: The FCoE controller that received the packet
 * @skb: The received FIP packet
 *
 * This may be called from either NET_RX_SOFTIRQ or IRQ.
 */
व्योम fcoe_ctlr_recv(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस;
	skb_queue_tail(&fip->fip_recv_list, skb);
	schedule_work(&fip->recv_work);
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_recv);

/**
 * fcoe_ctlr_recv_handler() - Receive a FIP frame
 * @fip: The FCoE controller that received the frame
 * @skb: The received FIP frame
 *
 * Returns non-zero अगर the frame is dropped.
 */
अटल पूर्णांक fcoe_ctlr_recv_handler(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_header *fiph;
	काष्ठा ethhdr *eh;
	क्रमागत fip_state state;
	bool fip_vlan_resp = false;
	u16 op;
	u8 sub;

	अगर (skb_linearize(skb))
		जाओ drop;
	अगर (skb->len < माप(*fiph))
		जाओ drop;
	eh = eth_hdr(skb);
	अगर (fip->mode == FIP_MODE_VN2VN) अणु
		अगर (!ether_addr_equal(eh->h_dest, fip->ctl_src_addr) &&
		    !ether_addr_equal(eh->h_dest, fcoe_all_vn2vn) &&
		    !ether_addr_equal(eh->h_dest, fcoe_all_p2p))
			जाओ drop;
	पूर्ण अन्यथा अगर (!ether_addr_equal(eh->h_dest, fip->ctl_src_addr) &&
		   !ether_addr_equal(eh->h_dest, fcoe_all_enode))
		जाओ drop;
	fiph = (काष्ठा fip_header *)skb->data;
	op = ntohs(fiph->fip_op);
	sub = fiph->fip_subcode;

	अगर (FIP_VER_DECAPS(fiph->fip_ver) != FIP_VER)
		जाओ drop;
	अगर (ntohs(fiph->fip_dl_len) * FIP_BPW + माप(*fiph) > skb->len)
		जाओ drop;

	mutex_lock(&fip->ctlr_mutex);
	state = fip->state;
	अगर (state == FIP_ST_AUTO) अणु
		fip->map_dest = 0;
		fcoe_ctlr_set_state(fip, FIP_ST_ENABLED);
		state = FIP_ST_ENABLED;
		LIBFCOE_FIP_DBG(fip, "Using FIP mode\n");
	पूर्ण
	fip_vlan_resp = fip->fip_resp;
	mutex_unlock(&fip->ctlr_mutex);

	अगर (fip->mode == FIP_MODE_VN2VN && op == FIP_OP_VN2VN)
		वापस fcoe_ctlr_vn_recv(fip, skb);

	अगर (fip_vlan_resp && op == FIP_OP_VLAN) अणु
		LIBFCOE_FIP_DBG(fip, "fip vlan discovery\n");
		वापस fcoe_ctlr_vlan_recv(fip, skb);
	पूर्ण

	अगर (state != FIP_ST_ENABLED && state != FIP_ST_VNMP_UP &&
	    state != FIP_ST_VNMP_CLAIM)
		जाओ drop;

	अगर (op == FIP_OP_LS) अणु
		fcoe_ctlr_recv_els(fip, skb);	/* consumes skb */
		वापस 0;
	पूर्ण

	अगर (state != FIP_ST_ENABLED)
		जाओ drop;

	अगर (op == FIP_OP_DISC && sub == FIP_SC_ADV)
		fcoe_ctlr_recv_adv(fip, skb);
	अन्यथा अगर (op == FIP_OP_CTRL && sub == FIP_SC_CLR_VLINK)
		fcoe_ctlr_recv_clr_vlink(fip, skb);
	kमुक्त_skb(skb);
	वापस 0;
drop:
	kमुक्त_skb(skb);
	वापस -1;
पूर्ण

/**
 * fcoe_ctlr_select() - Select the best FCF (अगर possible)
 * @fip: The FCoE controller
 *
 * Returns the selected FCF, or शून्य अगर none are usable.
 *
 * If there are conflicting advertisements, no FCF can be chosen.
 *
 * If there is alपढ़ोy a selected FCF, this will choose a better one or
 * an equivalent one that hasn't alपढ़ोy been sent a FLOGI.
 *
 * Called with lock held.
 */
अटल काष्ठा fcoe_fcf *fcoe_ctlr_select(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fcoe_fcf *fcf;
	काष्ठा fcoe_fcf *best = fip->sel_fcf;

	list_क्रम_each_entry(fcf, &fip->fcfs, list) अणु
		LIBFCOE_FIP_DBG(fip, "consider FCF fab %16.16llx "
				"VFID %d mac %pM map %x val %d "
				"sent %u pri %u\n",
				fcf->fabric_name, fcf->vfid, fcf->fcf_mac,
				fcf->fc_map, fcoe_ctlr_mtu_valid(fcf),
				fcf->flogi_sent, fcf->pri);
		अगर (!fcoe_ctlr_fcf_usable(fcf)) अणु
			LIBFCOE_FIP_DBG(fip, "FCF for fab %16.16llx "
					"map %x %svalid %savailable\n",
					fcf->fabric_name, fcf->fc_map,
					(fcf->flags & FIP_FL_SOL) ? "" : "in",
					(fcf->flags & FIP_FL_AVAIL) ?
					"" : "un");
			जारी;
		पूर्ण
		अगर (!best || fcf->pri < best->pri || best->flogi_sent)
			best = fcf;
		अगर (fcf->fabric_name != best->fabric_name ||
		    fcf->vfid != best->vfid ||
		    fcf->fc_map != best->fc_map) अणु
			LIBFCOE_FIP_DBG(fip, "Conflicting fabric, VFID, "
					"or FC-MAP\n");
			वापस शून्य;
		पूर्ण
	पूर्ण
	fip->sel_fcf = best;
	अगर (best) अणु
		LIBFCOE_FIP_DBG(fip, "using FCF mac %pM\n", best->fcf_mac);
		fip->port_ka_समय = jअगरfies +
			msecs_to_jअगरfies(FIP_VN_KA_PERIOD);
		fip->ctlr_ka_समय = jअगरfies + best->fka_period;
		अगर (समय_beक्रमe(fip->ctlr_ka_समय, fip->समयr.expires))
			mod_समयr(&fip->समयr, fip->ctlr_ka_समय);
	पूर्ण
	वापस best;
पूर्ण

/**
 * fcoe_ctlr_flogi_send_locked() - send FIP-encapsulated FLOGI to current FCF
 * @fip: The FCoE controller
 *
 * Returns non-zero error अगर it could not be sent.
 *
 * Called with ctlr_mutex and ctlr_lock held.
 * Caller must verअगरy that fip->sel_fcf is not शून्य.
 */
अटल पूर्णांक fcoe_ctlr_flogi_send_locked(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा sk_buff *skb_orig;
	काष्ठा fc_frame_header *fh;
	पूर्णांक error;

	skb_orig = fip->flogi_req;
	अगर (!skb_orig)
		वापस -EINVAL;

	/*
	 * Clone and send the FLOGI request.  If clone fails, use original.
	 */
	skb = skb_clone(skb_orig, GFP_ATOMIC);
	अगर (!skb) अणु
		skb = skb_orig;
		fip->flogi_req = शून्य;
	पूर्ण
	fh = (काष्ठा fc_frame_header *)skb->data;
	error = fcoe_ctlr_encaps(fip, fip->lp, FIP_DT_FLOGI, skb,
				 ntoh24(fh->fh_d_id));
	अगर (error) अणु
		kमुक्त_skb(skb);
		वापस error;
	पूर्ण
	fip->send(fip, skb);
	fip->sel_fcf->flogi_sent = 1;
	वापस 0;
पूर्ण

/**
 * fcoe_ctlr_flogi_retry() - resend FLOGI request to a new FCF अगर possible
 * @fip: The FCoE controller
 *
 * Returns non-zero error code अगर there's no FLOGI request to retry or
 * no alternate FCF available.
 */
अटल पूर्णांक fcoe_ctlr_flogi_retry(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fcoe_fcf *fcf;
	पूर्णांक error;

	mutex_lock(&fip->ctlr_mutex);
	spin_lock_bh(&fip->ctlr_lock);
	LIBFCOE_FIP_DBG(fip, "re-sending FLOGI - reselect\n");
	fcf = fcoe_ctlr_select(fip);
	अगर (!fcf || fcf->flogi_sent) अणु
		kमुक्त_skb(fip->flogi_req);
		fip->flogi_req = शून्य;
		error = -ENOENT;
	पूर्ण अन्यथा अणु
		fcoe_ctlr_solicit(fip, शून्य);
		error = fcoe_ctlr_flogi_send_locked(fip);
	पूर्ण
	spin_unlock_bh(&fip->ctlr_lock);
	mutex_unlock(&fip->ctlr_mutex);
	वापस error;
पूर्ण


/**
 * fcoe_ctlr_flogi_send() - Handle sending of FIP FLOGI.
 * @fip: The FCoE controller that समयd out
 *
 * Done here because fcoe_ctlr_els_send() can't get mutex.
 *
 * Called with ctlr_mutex held.  The caller must not hold ctlr_lock.
 */
अटल व्योम fcoe_ctlr_flogi_send(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fcoe_fcf *fcf;

	spin_lock_bh(&fip->ctlr_lock);
	fcf = fip->sel_fcf;
	अगर (!fcf || !fip->flogi_req_send)
		जाओ unlock;

	LIBFCOE_FIP_DBG(fip, "sending FLOGI\n");

	/*
	 * If this FLOGI is being sent due to a समयout retry
	 * to the same FCF as beक्रमe, select a dअगरferent FCF अगर possible.
	 */
	अगर (fcf->flogi_sent) अणु
		LIBFCOE_FIP_DBG(fip, "sending FLOGI - reselect\n");
		fcf = fcoe_ctlr_select(fip);
		अगर (!fcf || fcf->flogi_sent) अणु
			LIBFCOE_FIP_DBG(fip, "sending FLOGI - clearing\n");
			list_क्रम_each_entry(fcf, &fip->fcfs, list)
				fcf->flogi_sent = 0;
			fcf = fcoe_ctlr_select(fip);
		पूर्ण
	पूर्ण
	अगर (fcf) अणु
		fcoe_ctlr_flogi_send_locked(fip);
		fip->flogi_req_send = 0;
	पूर्ण अन्यथा /* XXX */
		LIBFCOE_FIP_DBG(fip, "No FCF selected - defer send\n");
unlock:
	spin_unlock_bh(&fip->ctlr_lock);
पूर्ण

/**
 * fcoe_ctlr_समयout() - FIP समयout handler
 * @t: Timer context use to obtain the controller reference
 */
अटल व्योम fcoe_ctlr_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा fcoe_ctlr *fip = from_समयr(fip, t, समयr);

	schedule_work(&fip->समयr_work);
पूर्ण

/**
 * fcoe_ctlr_समयr_work() - Worker thपढ़ो function क्रम समयr work
 * @work: Handle to a FCoE controller
 *
 * Ages FCFs.  Triggers FCF selection अगर possible.
 * Sends keep-alives and resets.
 */
अटल व्योम fcoe_ctlr_समयr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fcoe_ctlr *fip;
	काष्ठा fc_lport *vport;
	u8 *mac;
	u8 reset = 0;
	u8 send_ctlr_ka = 0;
	u8 send_port_ka = 0;
	काष्ठा fcoe_fcf *sel;
	काष्ठा fcoe_fcf *fcf;
	अचिन्हित दीर्घ next_समयr;

	fip = container_of(work, काष्ठा fcoe_ctlr, समयr_work);
	अगर (fip->mode == FIP_MODE_VN2VN)
		वापस fcoe_ctlr_vn_समयout(fip);
	mutex_lock(&fip->ctlr_mutex);
	अगर (fip->state == FIP_ST_DISABLED) अणु
		mutex_unlock(&fip->ctlr_mutex);
		वापस;
	पूर्ण

	fcf = fip->sel_fcf;
	next_समयr = fcoe_ctlr_age_fcfs(fip);

	sel = fip->sel_fcf;
	अगर (!sel && fip->sel_समय) अणु
		अगर (समय_after_eq(jअगरfies, fip->sel_समय)) अणु
			sel = fcoe_ctlr_select(fip);
			fip->sel_समय = 0;
		पूर्ण अन्यथा अगर (समय_after(next_समयr, fip->sel_समय))
			next_समयr = fip->sel_समय;
	पूर्ण

	अगर (sel && fip->flogi_req_send)
		fcoe_ctlr_flogi_send(fip);
	अन्यथा अगर (!sel && fcf)
		reset = 1;

	अगर (sel && !sel->fd_flags) अणु
		अगर (समय_after_eq(jअगरfies, fip->ctlr_ka_समय)) अणु
			fip->ctlr_ka_समय = jअगरfies + sel->fka_period;
			send_ctlr_ka = 1;
		पूर्ण
		अगर (समय_after(next_समयr, fip->ctlr_ka_समय))
			next_समयr = fip->ctlr_ka_समय;

		अगर (समय_after_eq(jअगरfies, fip->port_ka_समय)) अणु
			fip->port_ka_समय = jअगरfies +
				msecs_to_jअगरfies(FIP_VN_KA_PERIOD);
			send_port_ka = 1;
		पूर्ण
		अगर (समय_after(next_समयr, fip->port_ka_समय))
			next_समयr = fip->port_ka_समय;
	पूर्ण
	अगर (!list_empty(&fip->fcfs))
		mod_समयr(&fip->समयr, next_समयr);
	mutex_unlock(&fip->ctlr_mutex);

	अगर (reset) अणु
		fc_lport_reset(fip->lp);
		/* restart things with a solicitation */
		fcoe_ctlr_solicit(fip, शून्य);
	पूर्ण

	अगर (send_ctlr_ka)
		fcoe_ctlr_send_keep_alive(fip, शून्य, 0, fip->ctl_src_addr);

	अगर (send_port_ka) अणु
		mutex_lock(&fip->lp->lp_mutex);
		mac = fip->get_src_addr(fip->lp);
		fcoe_ctlr_send_keep_alive(fip, fip->lp, 1, mac);
		list_क्रम_each_entry(vport, &fip->lp->vports, list) अणु
			mac = fip->get_src_addr(vport);
			fcoe_ctlr_send_keep_alive(fip, vport, 1, mac);
		पूर्ण
		mutex_unlock(&fip->lp->lp_mutex);
	पूर्ण
पूर्ण

/**
 * fcoe_ctlr_recv_work() - Worker thपढ़ो function क्रम receiving FIP frames
 * @recv_work: Handle to a FCoE controller
 */
अटल व्योम fcoe_ctlr_recv_work(काष्ठा work_काष्ठा *recv_work)
अणु
	काष्ठा fcoe_ctlr *fip;
	काष्ठा sk_buff *skb;

	fip = container_of(recv_work, काष्ठा fcoe_ctlr, recv_work);
	जबतक ((skb = skb_dequeue(&fip->fip_recv_list)))
		fcoe_ctlr_recv_handler(fip, skb);
पूर्ण

/**
 * fcoe_ctlr_recv_flogi() - Snoop pre-FIP receipt of FLOGI response
 * @fip: The FCoE controller
 * @lport: The local port
 * @fp:	 The FC frame to snoop
 *
 * Snoop potential response to FLOGI or even incoming FLOGI.
 *
 * The caller has checked that we are रुकोing क्रम login as indicated
 * by fip->flogi_oxid != FC_XID_UNKNOWN.
 *
 * The caller is responsible क्रम मुक्तing the frame.
 * Fill in the granted_mac address.
 *
 * Return non-zero अगर the frame should not be delivered to libfc.
 */
पूर्णांक fcoe_ctlr_recv_flogi(काष्ठा fcoe_ctlr *fip, काष्ठा fc_lport *lport,
			 काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh;
	u8 op;
	u8 *sa;

	sa = eth_hdr(&fp->skb)->h_source;
	fh = fc_frame_header_get(fp);
	अगर (fh->fh_type != FC_TYPE_ELS)
		वापस 0;

	op = fc_frame_payload_op(fp);
	अगर (op == ELS_LS_ACC && fh->fh_r_ctl == FC_RCTL_ELS_REP &&
	    fip->flogi_oxid == ntohs(fh->fh_ox_id)) अणु

		mutex_lock(&fip->ctlr_mutex);
		अगर (fip->state != FIP_ST_AUTO && fip->state != FIP_ST_NON_FIP) अणु
			mutex_unlock(&fip->ctlr_mutex);
			वापस -EINVAL;
		पूर्ण
		fcoe_ctlr_set_state(fip, FIP_ST_NON_FIP);
		LIBFCOE_FIP_DBG(fip,
				"received FLOGI LS_ACC using non-FIP mode\n");

		/*
		 * FLOGI accepted.
		 * If the src mac addr is FC_OUI-based, then we mark the
		 * address_mode flag to use FC_OUI-based Ethernet DA.
		 * Otherwise we use the FCoE gateway addr
		 */
		अगर (ether_addr_equal(sa, (u8[6])FC_FCOE_FLOGI_MAC)) अणु
			fcoe_ctlr_map_dest(fip);
		पूर्ण अन्यथा अणु
			स_नकल(fip->dest_addr, sa, ETH_ALEN);
			fip->map_dest = 0;
		पूर्ण
		fip->flogi_oxid = FC_XID_UNKNOWN;
		mutex_unlock(&fip->ctlr_mutex);
		fc_fcoe_set_mac(fr_cb(fp)->granted_mac, fh->fh_d_id);
	पूर्ण अन्यथा अगर (op == ELS_FLOGI && fh->fh_r_ctl == FC_RCTL_ELS_REQ && sa) अणु
		/*
		 * Save source MAC क्रम poपूर्णांक-to-poपूर्णांक responses.
		 */
		mutex_lock(&fip->ctlr_mutex);
		अगर (fip->state == FIP_ST_AUTO || fip->state == FIP_ST_NON_FIP) अणु
			स_नकल(fip->dest_addr, sa, ETH_ALEN);
			fip->map_dest = 0;
			अगर (fip->state == FIP_ST_AUTO)
				LIBFCOE_FIP_DBG(fip, "received non-FIP FLOGI. "
						"Setting non-FIP mode\n");
			fcoe_ctlr_set_state(fip, FIP_ST_NON_FIP);
		पूर्ण
		mutex_unlock(&fip->ctlr_mutex);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_recv_flogi);

/**
 * fcoe_wwn_from_mac() - Converts a 48-bit IEEE MAC address to a 64-bit FC WWN
 * @mac:    The MAC address to convert
 * @scheme: The scheme to use when converting
 * @port:   The port indicator क्रम converting
 *
 * Returns: u64 fc world wide name
 */
u64 fcoe_wwn_from_mac(अचिन्हित अक्षर mac[MAX_ADDR_LEN],
		      अचिन्हित पूर्णांक scheme, अचिन्हित पूर्णांक port)
अणु
	u64 wwn;
	u64 host_mac;

	/* The MAC is in NO, so flip only the low 48 bits */
	host_mac = ((u64) mac[0] << 40) |
		((u64) mac[1] << 32) |
		((u64) mac[2] << 24) |
		((u64) mac[3] << 16) |
		((u64) mac[4] << 8) |
		(u64) mac[5];

	WARN_ON(host_mac >= (1ULL << 48));
	wwn = host_mac | ((u64) scheme << 60);
	चयन (scheme) अणु
	हाल 1:
		WARN_ON(port != 0);
		अवरोध;
	हाल 2:
		WARN_ON(port >= 0xfff);
		wwn |= (u64) port << 48;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	वापस wwn;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_wwn_from_mac);

/**
 * fcoe_ctlr_rport() - वापस the fcoe_rport क्रम a given fc_rport_priv
 * @rdata: libfc remote port
 */
अटल अंतरभूत काष्ठा fcoe_rport *fcoe_ctlr_rport(काष्ठा fc_rport_priv *rdata)
अणु
	वापस container_of(rdata, काष्ठा fcoe_rport, rdata);
पूर्ण

/**
 * fcoe_ctlr_vn_send() - Send a FIP VN2VN Probe Request or Reply.
 * @fip: The FCoE controller
 * @sub: sub-opcode क्रम probe request, reply, or advertisement.
 * @dest: The destination Ethernet MAC address
 * @min_len: minimum size of the Ethernet payload to be sent
 */
अटल व्योम fcoe_ctlr_vn_send(काष्ठा fcoe_ctlr *fip,
			      क्रमागत fip_vn2vn_subcode sub,
			      स्थिर u8 *dest, माप_प्रकार min_len)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fip_vn2vn_probe_frame अणु
		काष्ठा ethhdr eth;
		काष्ठा fip_header fip;
		काष्ठा fip_mac_desc mac;
		काष्ठा fip_wwn_desc wwnn;
		काष्ठा fip_vn_desc vn;
	पूर्ण __packed * frame;
	काष्ठा fip_fc4_feat *ff;
	काष्ठा fip_size_desc *size;
	u32 fcp_feat;
	माप_प्रकार len;
	माप_प्रकार dlen;

	len = माप(*frame);
	dlen = 0;
	अगर (sub == FIP_SC_VN_CLAIM_NOTIFY || sub == FIP_SC_VN_CLAIM_REP) अणु
		dlen = माप(काष्ठा fip_fc4_feat) +
		       माप(काष्ठा fip_size_desc);
		len += dlen;
	पूर्ण
	dlen += माप(frame->mac) + माप(frame->wwnn) + माप(frame->vn);
	len = max(len, min_len + माप(काष्ठा ethhdr));

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस;

	frame = (काष्ठा fip_vn2vn_probe_frame *)skb->data;
	स_रखो(frame, 0, len);
	स_नकल(frame->eth.h_dest, dest, ETH_ALEN);

	अगर (sub == FIP_SC_VN_BEACON) अणु
		hton24(frame->eth.h_source, FIP_VN_FC_MAP);
		hton24(frame->eth.h_source + 3, fip->port_id);
	पूर्ण अन्यथा अणु
		स_नकल(frame->eth.h_source, fip->ctl_src_addr, ETH_ALEN);
	पूर्ण
	frame->eth.h_proto = htons(ETH_P_FIP);

	frame->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	frame->fip.fip_op = htons(FIP_OP_VN2VN);
	frame->fip.fip_subcode = sub;
	frame->fip.fip_dl_len = htons(dlen / FIP_BPW);

	frame->mac.fd_desc.fip_dtype = FIP_DT_MAC;
	frame->mac.fd_desc.fip_dlen = माप(frame->mac) / FIP_BPW;
	स_नकल(frame->mac.fd_mac, fip->ctl_src_addr, ETH_ALEN);

	frame->wwnn.fd_desc.fip_dtype = FIP_DT_NAME;
	frame->wwnn.fd_desc.fip_dlen = माप(frame->wwnn) / FIP_BPW;
	put_unaligned_be64(fip->lp->wwnn, &frame->wwnn.fd_wwn);

	frame->vn.fd_desc.fip_dtype = FIP_DT_VN_ID;
	frame->vn.fd_desc.fip_dlen = माप(frame->vn) / FIP_BPW;
	hton24(frame->vn.fd_mac, FIP_VN_FC_MAP);
	hton24(frame->vn.fd_mac + 3, fip->port_id);
	hton24(frame->vn.fd_fc_id, fip->port_id);
	put_unaligned_be64(fip->lp->wwpn, &frame->vn.fd_wwpn);

	/*
	 * For claims, add FC-4 features.
	 * TBD: Add पूर्णांकerface to get fc-4 types and features from libfc.
	 */
	अगर (sub == FIP_SC_VN_CLAIM_NOTIFY || sub == FIP_SC_VN_CLAIM_REP) अणु
		ff = (काष्ठा fip_fc4_feat *)(frame + 1);
		ff->fd_desc.fip_dtype = FIP_DT_FC4F;
		ff->fd_desc.fip_dlen = माप(*ff) / FIP_BPW;
		ff->fd_fts = fip->lp->fcts;

		fcp_feat = 0;
		अगर (fip->lp->service_params & FCP_SPPF_INIT_FCN)
			fcp_feat |= FCP_FEAT_INIT;
		अगर (fip->lp->service_params & FCP_SPPF_TARG_FCN)
			fcp_feat |= FCP_FEAT_TARG;
		fcp_feat <<= (FC_TYPE_FCP * 4) % 32;
		ff->fd_ff.fd_feat[FC_TYPE_FCP * 4 / 32] = htonl(fcp_feat);

		size = (काष्ठा fip_size_desc *)(ff + 1);
		size->fd_desc.fip_dtype = FIP_DT_FCOE_SIZE;
		size->fd_desc.fip_dlen = माप(*size) / FIP_BPW;
		size->fd_size = htons(fcoe_ctlr_fcoe_size(fip));
	पूर्ण

	skb_put(skb, len);
	skb->protocol = htons(ETH_P_FIP);
	skb->priority = fip->priority;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);

	fip->send(fip, skb);
पूर्ण

/**
 * fcoe_ctlr_vn_rport_callback - Event handler क्रम rport events.
 * @lport: The lport which is receiving the event
 * @rdata: remote port निजी data
 * @event: The event that occurred
 *
 * Locking Note:  The rport lock must not be held when calling this function.
 */
अटल व्योम fcoe_ctlr_vn_rport_callback(काष्ठा fc_lport *lport,
					काष्ठा fc_rport_priv *rdata,
					क्रमागत fc_rport_event event)
अणु
	काष्ठा fcoe_ctlr *fip = lport->disc.priv;
	काष्ठा fcoe_rport *frport = fcoe_ctlr_rport(rdata);

	LIBFCOE_FIP_DBG(fip, "vn_rport_callback %x event %d\n",
			rdata->ids.port_id, event);

	mutex_lock(&fip->ctlr_mutex);
	चयन (event) अणु
	हाल RPORT_EV_READY:
		frport->login_count = 0;
		अवरोध;
	हाल RPORT_EV_LOGO:
	हाल RPORT_EV_FAILED:
	हाल RPORT_EV_STOP:
		frport->login_count++;
		अगर (frport->login_count > FCOE_CTLR_VN2VN_LOGIN_LIMIT) अणु
			LIBFCOE_FIP_DBG(fip,
					"rport FLOGI limited port_id %6.6x\n",
					rdata->ids.port_id);
			fc_rport_logoff(rdata);
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	mutex_unlock(&fip->ctlr_mutex);
पूर्ण

अटल काष्ठा fc_rport_operations fcoe_ctlr_vn_rport_ops = अणु
	.event_callback = fcoe_ctlr_vn_rport_callback,
पूर्ण;

/**
 * fcoe_ctlr_disc_stop_locked() - stop discovery in VN2VN mode
 * @lport: The local port
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_disc_stop_locked(काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_rport_priv *rdata;

	mutex_lock(&lport->disc.disc_mutex);
	list_क्रम_each_entry_rcu(rdata, &lport->disc.rports, peers) अणु
		अगर (kref_get_unless_zero(&rdata->kref)) अणु
			fc_rport_logoff(rdata);
			kref_put(&rdata->kref, fc_rport_destroy);
		पूर्ण
	पूर्ण
	lport->disc.disc_callback = शून्य;
	mutex_unlock(&lport->disc.disc_mutex);
पूर्ण

/**
 * fcoe_ctlr_disc_stop() - stop discovery in VN2VN mode
 * @lport: The local port
 *
 * Called through the local port ढाँचा क्रम discovery.
 * Called without the ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_disc_stop(काष्ठा fc_lport *lport)
अणु
	काष्ठा fcoe_ctlr *fip = lport->disc.priv;

	mutex_lock(&fip->ctlr_mutex);
	fcoe_ctlr_disc_stop_locked(lport);
	mutex_unlock(&fip->ctlr_mutex);
पूर्ण

/**
 * fcoe_ctlr_disc_stop_final() - stop discovery क्रम shutकरोwn in VN2VN mode
 * @lport: The local port
 *
 * Called through the local port ढाँचा क्रम discovery.
 * Called without the ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_disc_stop_final(काष्ठा fc_lport *lport)
अणु
	fcoe_ctlr_disc_stop(lport);
	fc_rport_flush_queue();
	synchronize_rcu();
पूर्ण

/**
 * fcoe_ctlr_vn_restart() - VN2VN probe restart with new port_id
 * @fip: The FCoE controller
 *
 * Called with fcoe_ctlr lock held.
 */
अटल व्योम fcoe_ctlr_vn_restart(काष्ठा fcoe_ctlr *fip)
अणु
	अचिन्हित दीर्घ रुको;
	u32 port_id;

	fcoe_ctlr_disc_stop_locked(fip->lp);

	/*
	 * Get proposed port ID.
	 * If this is the first try after link up, use any previous port_id.
	 * If there was none, use the low bits of the port_name.
	 * On subsequent tries, get the next अक्रमom one.
	 * Don't use reserved IDs, use another non-zero value, just as अक्रमom.
	 */
	port_id = fip->port_id;
	अगर (fip->probe_tries)
		port_id = pअक्रमom_u32_state(&fip->rnd_state) & 0xffff;
	अन्यथा अगर (!port_id)
		port_id = fip->lp->wwpn & 0xffff;
	अगर (!port_id || port_id == 0xffff)
		port_id = 1;
	fip->port_id = port_id;

	अगर (fip->probe_tries < FIP_VN_RLIM_COUNT) अणु
		fip->probe_tries++;
		रुको = pअक्रमom_u32() % FIP_VN_PROBE_WAIT;
	पूर्ण अन्यथा
		रुको = FIP_VN_RLIM_INT;
	mod_समयr(&fip->समयr, jअगरfies + msecs_to_jअगरfies(रुको));
	fcoe_ctlr_set_state(fip, FIP_ST_VNMP_START);
पूर्ण

/**
 * fcoe_ctlr_vn_start() - Start in VN2VN mode
 * @fip: The FCoE controller
 *
 * Called with fcoe_ctlr lock held.
 */
अटल व्योम fcoe_ctlr_vn_start(काष्ठा fcoe_ctlr *fip)
अणु
	fip->probe_tries = 0;
	pअक्रमom_seed_state(&fip->rnd_state, fip->lp->wwpn);
	fcoe_ctlr_vn_restart(fip);
पूर्ण

/**
 * fcoe_ctlr_vn_parse - parse probe request or response
 * @fip: The FCoE controller
 * @skb: incoming packet
 * @frport: parsed FCoE rport from the probe request
 *
 * Returns non-zero error number on error.
 * Does not consume the packet.
 */
अटल पूर्णांक fcoe_ctlr_vn_parse(काष्ठा fcoe_ctlr *fip,
			      काष्ठा sk_buff *skb,
			      काष्ठा fcoe_rport *frport)
अणु
	काष्ठा fip_header *fiph;
	काष्ठा fip_desc *desc = शून्य;
	काष्ठा fip_mac_desc *macd = शून्य;
	काष्ठा fip_wwn_desc *wwn = शून्य;
	काष्ठा fip_vn_desc *vn = शून्य;
	काष्ठा fip_size_desc *size = शून्य;
	माप_प्रकार rlen;
	माप_प्रकार dlen;
	u32 desc_mask = 0;
	u32 dtype;
	u8 sub;

	fiph = (काष्ठा fip_header *)skb->data;
	frport->flags = ntohs(fiph->fip_flags);

	sub = fiph->fip_subcode;
	चयन (sub) अणु
	हाल FIP_SC_VN_PROBE_REQ:
	हाल FIP_SC_VN_PROBE_REP:
	हाल FIP_SC_VN_BEACON:
		desc_mask = BIT(FIP_DT_MAC) | BIT(FIP_DT_NAME) |
			    BIT(FIP_DT_VN_ID);
		अवरोध;
	हाल FIP_SC_VN_CLAIM_NOTIFY:
	हाल FIP_SC_VN_CLAIM_REP:
		desc_mask = BIT(FIP_DT_MAC) | BIT(FIP_DT_NAME) |
			    BIT(FIP_DT_VN_ID) | BIT(FIP_DT_FC4F) |
			    BIT(FIP_DT_FCOE_SIZE);
		अवरोध;
	शेष:
		LIBFCOE_FIP_DBG(fip, "vn_parse unknown subcode %u\n", sub);
		वापस -EINVAL;
	पूर्ण

	rlen = ntohs(fiph->fip_dl_len) * 4;
	अगर (rlen + माप(*fiph) > skb->len)
		वापस -EINVAL;

	desc = (काष्ठा fip_desc *)(fiph + 1);
	जबतक (rlen > 0) अणु
		dlen = desc->fip_dlen * FIP_BPW;
		अगर (dlen < माप(*desc) || dlen > rlen)
			वापस -EINVAL;

		dtype = desc->fip_dtype;
		अगर (dtype < 32) अणु
			अगर (!(desc_mask & BIT(dtype))) अणु
				LIBFCOE_FIP_DBG(fip,
						"unexpected or duplicated desc "
						"desc type %u in "
						"FIP VN2VN subtype %u\n",
						dtype, sub);
				वापस -EINVAL;
			पूर्ण
			desc_mask &= ~BIT(dtype);
		पूर्ण

		चयन (dtype) अणु
		हाल FIP_DT_MAC:
			अगर (dlen != माप(काष्ठा fip_mac_desc))
				जाओ len_err;
			macd = (काष्ठा fip_mac_desc *)desc;
			अगर (!is_valid_ether_addr(macd->fd_mac)) अणु
				LIBFCOE_FIP_DBG(fip,
					"Invalid MAC addr %pM in FIP VN2VN\n",
					 macd->fd_mac);
				वापस -EINVAL;
			पूर्ण
			स_नकल(frport->enode_mac, macd->fd_mac, ETH_ALEN);
			अवरोध;
		हाल FIP_DT_NAME:
			अगर (dlen != माप(काष्ठा fip_wwn_desc))
				जाओ len_err;
			wwn = (काष्ठा fip_wwn_desc *)desc;
			frport->rdata.ids.node_name =
				get_unaligned_be64(&wwn->fd_wwn);
			अवरोध;
		हाल FIP_DT_VN_ID:
			अगर (dlen != माप(काष्ठा fip_vn_desc))
				जाओ len_err;
			vn = (काष्ठा fip_vn_desc *)desc;
			स_नकल(frport->vn_mac, vn->fd_mac, ETH_ALEN);
			frport->rdata.ids.port_id = ntoh24(vn->fd_fc_id);
			frport->rdata.ids.port_name =
				get_unaligned_be64(&vn->fd_wwpn);
			अवरोध;
		हाल FIP_DT_FC4F:
			अगर (dlen != माप(काष्ठा fip_fc4_feat))
				जाओ len_err;
			अवरोध;
		हाल FIP_DT_FCOE_SIZE:
			अगर (dlen != माप(काष्ठा fip_size_desc))
				जाओ len_err;
			size = (काष्ठा fip_size_desc *)desc;
			frport->fcoe_len = ntohs(size->fd_size);
			अवरोध;
		शेष:
			LIBFCOE_FIP_DBG(fip, "unexpected descriptor type %x "
					"in FIP probe\n", dtype);
			/* standard says ignore unknown descriptors >= 128 */
			अगर (dtype < FIP_DT_NON_CRITICAL)
				वापस -EINVAL;
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण
	वापस 0;

len_err:
	LIBFCOE_FIP_DBG(fip, "FIP length error in descriptor type %x len %zu\n",
			dtype, dlen);
	वापस -EINVAL;
पूर्ण

/**
 * fcoe_ctlr_vn_send_claim() - send multicast FIP VN2VN Claim Notअगरication.
 * @fip: The FCoE controller
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_send_claim(काष्ठा fcoe_ctlr *fip)
अणु
	fcoe_ctlr_vn_send(fip, FIP_SC_VN_CLAIM_NOTIFY, fcoe_all_vn2vn, 0);
	fip->sol_समय = jअगरfies;
पूर्ण

/**
 * fcoe_ctlr_vn_probe_req() - handle incoming VN2VN probe request.
 * @fip: The FCoE controller
 * @frport: parsed FCoE rport from the probe request
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_probe_req(काष्ठा fcoe_ctlr *fip,
				   काष्ठा fcoe_rport *frport)
अणु
	अगर (frport->rdata.ids.port_id != fip->port_id)
		वापस;

	चयन (fip->state) अणु
	हाल FIP_ST_VNMP_CLAIM:
	हाल FIP_ST_VNMP_UP:
		LIBFCOE_FIP_DBG(fip, "vn_probe_req: send reply, state %x\n",
				fip->state);
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REP,
				  frport->enode_mac, 0);
		अवरोध;
	हाल FIP_ST_VNMP_PROBE1:
	हाल FIP_ST_VNMP_PROBE2:
		/*
		 * Decide whether to reply to the Probe.
		 * Our selected address is never a "recorded" one, so
		 * only reply अगर our WWPN is greater and the
		 * Probe's REC bit is not set.
		 * If we करोn't reply, we will change our address.
		 */
		अगर (fip->lp->wwpn > frport->rdata.ids.port_name &&
		    !(frport->flags & FIP_FL_REC_OR_P2P)) अणु
			LIBFCOE_FIP_DBG(fip, "vn_probe_req: "
					"port_id collision\n");
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REP,
					  frport->enode_mac, 0);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल FIP_ST_VNMP_START:
		LIBFCOE_FIP_DBG(fip, "vn_probe_req: "
				"restart VN2VN negotiation\n");
		fcoe_ctlr_vn_restart(fip);
		अवरोध;
	शेष:
		LIBFCOE_FIP_DBG(fip, "vn_probe_req: ignore state %x\n",
				fip->state);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fcoe_ctlr_vn_probe_reply() - handle incoming VN2VN probe reply.
 * @fip: The FCoE controller
 * @frport: parsed FCoE rport from the probe request
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_probe_reply(काष्ठा fcoe_ctlr *fip,
				     काष्ठा fcoe_rport *frport)
अणु
	अगर (frport->rdata.ids.port_id != fip->port_id)
		वापस;
	चयन (fip->state) अणु
	हाल FIP_ST_VNMP_START:
	हाल FIP_ST_VNMP_PROBE1:
	हाल FIP_ST_VNMP_PROBE2:
	हाल FIP_ST_VNMP_CLAIM:
		LIBFCOE_FIP_DBG(fip, "vn_probe_reply: restart state %x\n",
				fip->state);
		fcoe_ctlr_vn_restart(fip);
		अवरोध;
	हाल FIP_ST_VNMP_UP:
		LIBFCOE_FIP_DBG(fip, "vn_probe_reply: send claim notify\n");
		fcoe_ctlr_vn_send_claim(fip);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fcoe_ctlr_vn_add() - Add a VN2VN entry to the list, based on a claim reply.
 * @fip: The FCoE controller
 * @new: newly-parsed FCoE rport as a ढाँचा क्रम new rdata
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_add(काष्ठा fcoe_ctlr *fip, काष्ठा fcoe_rport *new)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fc_rport_identअगरiers *ids;
	काष्ठा fcoe_rport *frport;
	u32 port_id;

	port_id = new->rdata.ids.port_id;
	अगर (port_id == fip->port_id)
		वापस;

	mutex_lock(&lport->disc.disc_mutex);
	rdata = fc_rport_create(lport, port_id);
	अगर (!rdata) अणु
		mutex_unlock(&lport->disc.disc_mutex);
		वापस;
	पूर्ण
	mutex_lock(&rdata->rp_mutex);
	mutex_unlock(&lport->disc.disc_mutex);

	rdata->ops = &fcoe_ctlr_vn_rport_ops;
	rdata->disc_id = lport->disc.disc_id;

	ids = &rdata->ids;
	अगर ((ids->port_name != -1 &&
	     ids->port_name != new->rdata.ids.port_name) ||
	    (ids->node_name != -1 &&
	     ids->node_name != new->rdata.ids.node_name)) अणु
		mutex_unlock(&rdata->rp_mutex);
		LIBFCOE_FIP_DBG(fip, "vn_add rport logoff %6.6x\n", port_id);
		fc_rport_logoff(rdata);
		mutex_lock(&rdata->rp_mutex);
	पूर्ण
	ids->port_name = new->rdata.ids.port_name;
	ids->node_name = new->rdata.ids.node_name;
	mutex_unlock(&rdata->rp_mutex);

	frport = fcoe_ctlr_rport(rdata);
	LIBFCOE_FIP_DBG(fip, "vn_add rport %6.6x %s state %d\n",
			port_id, frport->fcoe_len ? "old" : "new",
			rdata->rp_state);
	frport->fcoe_len = new->fcoe_len;
	frport->flags = new->flags;
	frport->login_count = new->login_count;
	स_नकल(frport->enode_mac, new->enode_mac, ETH_ALEN);
	स_नकल(frport->vn_mac, new->vn_mac, ETH_ALEN);
	frport->समय = 0;
पूर्ण

/**
 * fcoe_ctlr_vn_lookup() - Find VN remote port's MAC address
 * @fip: The FCoE controller
 * @port_id:  The port_id of the remote VN_node
 * @mac: buffer which will hold the VN_NODE destination MAC address, अगर found.
 *
 * Returns non-zero error अगर no remote port found.
 */
अटल पूर्णांक fcoe_ctlr_vn_lookup(काष्ठा fcoe_ctlr *fip, u32 port_id, u8 *mac)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fcoe_rport *frport;
	पूर्णांक ret = -1;

	rdata = fc_rport_lookup(lport, port_id);
	अगर (rdata) अणु
		frport = fcoe_ctlr_rport(rdata);
		स_नकल(mac, frport->enode_mac, ETH_ALEN);
		ret = 0;
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * fcoe_ctlr_vn_claim_notअगरy() - handle received FIP VN2VN Claim Notअगरication
 * @fip: The FCoE controller
 * @new: newly-parsed FCoE rport as a ढाँचा क्रम new rdata
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_claim_notअगरy(काष्ठा fcoe_ctlr *fip,
				      काष्ठा fcoe_rport *new)
अणु
	अगर (new->flags & FIP_FL_REC_OR_P2P) अणु
		LIBFCOE_FIP_DBG(fip, "send probe req for P2P/REC\n");
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		वापस;
	पूर्ण
	चयन (fip->state) अणु
	हाल FIP_ST_VNMP_START:
	हाल FIP_ST_VNMP_PROBE1:
	हाल FIP_ST_VNMP_PROBE2:
		अगर (new->rdata.ids.port_id == fip->port_id) अणु
			LIBFCOE_FIP_DBG(fip, "vn_claim_notify: "
					"restart, state %d\n",
					fip->state);
			fcoe_ctlr_vn_restart(fip);
		पूर्ण
		अवरोध;
	हाल FIP_ST_VNMP_CLAIM:
	हाल FIP_ST_VNMP_UP:
		अगर (new->rdata.ids.port_id == fip->port_id) अणु
			अगर (new->rdata.ids.port_name > fip->lp->wwpn) अणु
				LIBFCOE_FIP_DBG(fip, "vn_claim_notify: "
						"restart, port_id collision\n");
				fcoe_ctlr_vn_restart(fip);
				अवरोध;
			पूर्ण
			LIBFCOE_FIP_DBG(fip, "vn_claim_notify: "
					"send claim notify\n");
			fcoe_ctlr_vn_send_claim(fip);
			अवरोध;
		पूर्ण
		LIBFCOE_FIP_DBG(fip, "vn_claim_notify: send reply to %x\n",
				new->rdata.ids.port_id);
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_CLAIM_REP, new->enode_mac,
				  min((u32)new->fcoe_len,
				      fcoe_ctlr_fcoe_size(fip)));
		fcoe_ctlr_vn_add(fip, new);
		अवरोध;
	शेष:
		LIBFCOE_FIP_DBG(fip, "vn_claim_notify: "
				"ignoring claim from %x\n",
				new->rdata.ids.port_id);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * fcoe_ctlr_vn_claim_resp() - handle received Claim Response
 * @fip: The FCoE controller that received the frame
 * @new: newly-parsed FCoE rport from the Claim Response
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_claim_resp(काष्ठा fcoe_ctlr *fip,
				    काष्ठा fcoe_rport *new)
अणु
	LIBFCOE_FIP_DBG(fip, "claim resp from from rport %x - state %s\n",
			new->rdata.ids.port_id, fcoe_ctlr_state(fip->state));
	अगर (fip->state == FIP_ST_VNMP_UP || fip->state == FIP_ST_VNMP_CLAIM)
		fcoe_ctlr_vn_add(fip, new);
पूर्ण

/**
 * fcoe_ctlr_vn_beacon() - handle received beacon.
 * @fip: The FCoE controller that received the frame
 * @new: newly-parsed FCoE rport from the Beacon
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vn_beacon(काष्ठा fcoe_ctlr *fip,
				काष्ठा fcoe_rport *new)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fcoe_rport *frport;

	अगर (new->flags & FIP_FL_REC_OR_P2P) अणु
		LIBFCOE_FIP_DBG(fip, "p2p beacon while in vn2vn mode\n");
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		वापस;
	पूर्ण
	rdata = fc_rport_lookup(lport, new->rdata.ids.port_id);
	अगर (rdata) अणु
		अगर (rdata->ids.node_name == new->rdata.ids.node_name &&
		    rdata->ids.port_name == new->rdata.ids.port_name) अणु
			frport = fcoe_ctlr_rport(rdata);

			LIBFCOE_FIP_DBG(fip, "beacon from rport %x\n",
					rdata->ids.port_id);
			अगर (!frport->समय && fip->state == FIP_ST_VNMP_UP) अणु
				LIBFCOE_FIP_DBG(fip, "beacon expired "
						"for rport %x\n",
						rdata->ids.port_id);
				fc_rport_login(rdata);
			पूर्ण
			frport->समय = jअगरfies;
		पूर्ण
		kref_put(&rdata->kref, fc_rport_destroy);
		वापस;
	पूर्ण
	अगर (fip->state != FIP_ST_VNMP_UP)
		वापस;

	/*
	 * Beacon from a new neighbor.
	 * Send a claim notअगरy अगर one hasn't been sent recently.
	 * Don't add the neighbor yet.
	 */
	LIBFCOE_FIP_DBG(fip, "beacon from new rport %x. sending claim notify\n",
			new->rdata.ids.port_id);
	अगर (समय_after(jअगरfies,
		       fip->sol_समय + msecs_to_jअगरfies(FIP_VN_ANN_WAIT)))
		fcoe_ctlr_vn_send_claim(fip);
पूर्ण

/**
 * fcoe_ctlr_vn_age() - Check क्रम VN_ports without recent beacons
 * @fip: The FCoE controller
 *
 * Called with ctlr_mutex held.
 * Called only in state FIP_ST_VNMP_UP.
 * Returns the soonest समय क्रम next age-out or a समय far in the future.
 */
अटल अचिन्हित दीर्घ fcoe_ctlr_vn_age(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fcoe_rport *frport;
	अचिन्हित दीर्घ next_समय;
	अचिन्हित दीर्घ deadline;

	next_समय = jअगरfies + msecs_to_jअगरfies(FIP_VN_BEACON_INT * 10);
	mutex_lock(&lport->disc.disc_mutex);
	list_क्रम_each_entry_rcu(rdata, &lport->disc.rports, peers) अणु
		अगर (!kref_get_unless_zero(&rdata->kref))
			जारी;
		frport = fcoe_ctlr_rport(rdata);
		अगर (!frport->समय) अणु
			kref_put(&rdata->kref, fc_rport_destroy);
			जारी;
		पूर्ण
		deadline = frport->समय +
			   msecs_to_jअगरfies(FIP_VN_BEACON_INT * 25 / 10);
		अगर (समय_after_eq(jअगरfies, deadline)) अणु
			frport->समय = 0;
			LIBFCOE_FIP_DBG(fip,
				"port %16.16llx fc_id %6.6x beacon expired\n",
				rdata->ids.port_name, rdata->ids.port_id);
			fc_rport_logoff(rdata);
		पूर्ण अन्यथा अगर (समय_beक्रमe(deadline, next_समय))
			next_समय = deadline;
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
	mutex_unlock(&lport->disc.disc_mutex);
	वापस next_समय;
पूर्ण

/**
 * fcoe_ctlr_vn_recv() - Receive a FIP frame
 * @fip: The FCoE controller that received the frame
 * @skb: The received FIP frame
 *
 * Returns non-zero अगर the frame is dropped.
 * Always consumes the frame.
 */
अटल पूर्णांक fcoe_ctlr_vn_recv(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_header *fiph;
	क्रमागत fip_vn2vn_subcode sub;
	काष्ठा fcoe_rport frport = अणु पूर्ण;
	पूर्णांक rc, vlan_id = 0;

	fiph = (काष्ठा fip_header *)skb->data;
	sub = fiph->fip_subcode;

	अगर (fip->lp->vlan)
		vlan_id = skb_vlan_tag_get_id(skb);

	अगर (vlan_id && vlan_id != fip->lp->vlan) अणु
		LIBFCOE_FIP_DBG(fip, "vn_recv drop frame sub %x vlan %d\n",
				sub, vlan_id);
		rc = -EAGAIN;
		जाओ drop;
	पूर्ण

	rc = fcoe_ctlr_vn_parse(fip, skb, &frport);
	अगर (rc) अणु
		LIBFCOE_FIP_DBG(fip, "vn_recv vn_parse error %d\n", rc);
		जाओ drop;
	पूर्ण

	mutex_lock(&fip->ctlr_mutex);
	चयन (sub) अणु
	हाल FIP_SC_VN_PROBE_REQ:
		fcoe_ctlr_vn_probe_req(fip, &frport);
		अवरोध;
	हाल FIP_SC_VN_PROBE_REP:
		fcoe_ctlr_vn_probe_reply(fip, &frport);
		अवरोध;
	हाल FIP_SC_VN_CLAIM_NOTIFY:
		fcoe_ctlr_vn_claim_notअगरy(fip, &frport);
		अवरोध;
	हाल FIP_SC_VN_CLAIM_REP:
		fcoe_ctlr_vn_claim_resp(fip, &frport);
		अवरोध;
	हाल FIP_SC_VN_BEACON:
		fcoe_ctlr_vn_beacon(fip, &frport);
		अवरोध;
	शेष:
		LIBFCOE_FIP_DBG(fip, "vn_recv unknown subcode %d\n", sub);
		rc = -1;
		अवरोध;
	पूर्ण
	mutex_unlock(&fip->ctlr_mutex);
drop:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

/**
 * fcoe_ctlr_vlan_parse - parse vlan discovery request or response
 * @fip: The FCoE controller
 * @skb: incoming packet
 * @frport: parsed FCoE rport from the probe request
 *
 * Returns non-zero error number on error.
 * Does not consume the packet.
 */
अटल पूर्णांक fcoe_ctlr_vlan_parse(काष्ठा fcoe_ctlr *fip,
			      काष्ठा sk_buff *skb,
			      काष्ठा fcoe_rport *frport)
अणु
	काष्ठा fip_header *fiph;
	काष्ठा fip_desc *desc = शून्य;
	काष्ठा fip_mac_desc *macd = शून्य;
	काष्ठा fip_wwn_desc *wwn = शून्य;
	माप_प्रकार rlen;
	माप_प्रकार dlen;
	u32 desc_mask = 0;
	u32 dtype;
	u8 sub;

	fiph = (काष्ठा fip_header *)skb->data;
	frport->flags = ntohs(fiph->fip_flags);

	sub = fiph->fip_subcode;
	चयन (sub) अणु
	हाल FIP_SC_VL_REQ:
		desc_mask = BIT(FIP_DT_MAC) | BIT(FIP_DT_NAME);
		अवरोध;
	शेष:
		LIBFCOE_FIP_DBG(fip, "vn_parse unknown subcode %u\n", sub);
		वापस -EINVAL;
	पूर्ण

	rlen = ntohs(fiph->fip_dl_len) * 4;
	अगर (rlen + माप(*fiph) > skb->len)
		वापस -EINVAL;

	desc = (काष्ठा fip_desc *)(fiph + 1);
	जबतक (rlen > 0) अणु
		dlen = desc->fip_dlen * FIP_BPW;
		अगर (dlen < माप(*desc) || dlen > rlen)
			वापस -EINVAL;

		dtype = desc->fip_dtype;
		अगर (dtype < 32) अणु
			अगर (!(desc_mask & BIT(dtype))) अणु
				LIBFCOE_FIP_DBG(fip,
						"unexpected or duplicated desc "
						"desc type %u in "
						"FIP VN2VN subtype %u\n",
						dtype, sub);
				वापस -EINVAL;
			पूर्ण
			desc_mask &= ~BIT(dtype);
		पूर्ण

		चयन (dtype) अणु
		हाल FIP_DT_MAC:
			अगर (dlen != माप(काष्ठा fip_mac_desc))
				जाओ len_err;
			macd = (काष्ठा fip_mac_desc *)desc;
			अगर (!is_valid_ether_addr(macd->fd_mac)) अणु
				LIBFCOE_FIP_DBG(fip,
					"Invalid MAC addr %pM in FIP VN2VN\n",
					 macd->fd_mac);
				वापस -EINVAL;
			पूर्ण
			स_नकल(frport->enode_mac, macd->fd_mac, ETH_ALEN);
			अवरोध;
		हाल FIP_DT_NAME:
			अगर (dlen != माप(काष्ठा fip_wwn_desc))
				जाओ len_err;
			wwn = (काष्ठा fip_wwn_desc *)desc;
			frport->rdata.ids.node_name =
				get_unaligned_be64(&wwn->fd_wwn);
			अवरोध;
		शेष:
			LIBFCOE_FIP_DBG(fip, "unexpected descriptor type %x "
					"in FIP probe\n", dtype);
			/* standard says ignore unknown descriptors >= 128 */
			अगर (dtype < FIP_DT_NON_CRITICAL)
				वापस -EINVAL;
			अवरोध;
		पूर्ण
		desc = (काष्ठा fip_desc *)((अक्षर *)desc + dlen);
		rlen -= dlen;
	पूर्ण
	वापस 0;

len_err:
	LIBFCOE_FIP_DBG(fip, "FIP length error in descriptor type %x len %zu\n",
			dtype, dlen);
	वापस -EINVAL;
पूर्ण

/**
 * fcoe_ctlr_vlan_send() - Send a FIP VLAN Notअगरication
 * @fip: The FCoE controller
 * @sub: sub-opcode क्रम vlan notअगरication or vn2vn vlan notअगरication
 * @dest: The destination Ethernet MAC address
 */
अटल व्योम fcoe_ctlr_vlan_send(काष्ठा fcoe_ctlr *fip,
			      क्रमागत fip_vlan_subcode sub,
			      स्थिर u8 *dest)
अणु
	काष्ठा sk_buff *skb;
	काष्ठा fip_vlan_notअगरy_frame अणु
		काष्ठा ethhdr eth;
		काष्ठा fip_header fip;
		काष्ठा fip_mac_desc mac;
		काष्ठा fip_vlan_desc vlan;
	पूर्ण __packed * frame;
	माप_प्रकार len;
	माप_प्रकार dlen;

	len = माप(*frame);
	dlen = माप(frame->mac) + माप(frame->vlan);
	len = max(len, माप(काष्ठा ethhdr));

	skb = dev_alloc_skb(len);
	अगर (!skb)
		वापस;

	LIBFCOE_FIP_DBG(fip, "fip %s vlan notification, vlan %d\n",
			fip->mode == FIP_MODE_VN2VN ? "vn2vn" : "fcf",
			fip->lp->vlan);

	frame = (काष्ठा fip_vlan_notअगरy_frame *)skb->data;
	स_रखो(frame, 0, len);
	स_नकल(frame->eth.h_dest, dest, ETH_ALEN);

	स_नकल(frame->eth.h_source, fip->ctl_src_addr, ETH_ALEN);
	frame->eth.h_proto = htons(ETH_P_FIP);

	frame->fip.fip_ver = FIP_VER_ENCAPS(FIP_VER);
	frame->fip.fip_op = htons(FIP_OP_VLAN);
	frame->fip.fip_subcode = sub;
	frame->fip.fip_dl_len = htons(dlen / FIP_BPW);

	frame->mac.fd_desc.fip_dtype = FIP_DT_MAC;
	frame->mac.fd_desc.fip_dlen = माप(frame->mac) / FIP_BPW;
	स_नकल(frame->mac.fd_mac, fip->ctl_src_addr, ETH_ALEN);

	frame->vlan.fd_desc.fip_dtype = FIP_DT_VLAN;
	frame->vlan.fd_desc.fip_dlen = माप(frame->vlan) / FIP_BPW;
	put_unaligned_be16(fip->lp->vlan, &frame->vlan.fd_vlan);

	skb_put(skb, len);
	skb->protocol = htons(ETH_P_FIP);
	skb->priority = fip->priority;
	skb_reset_mac_header(skb);
	skb_reset_network_header(skb);

	fip->send(fip, skb);
पूर्ण

/**
 * fcoe_ctlr_vlan_disc_reply() - send FIP VLAN Discovery Notअगरication.
 * @fip: The FCoE controller
 * @frport: The newly-parsed FCoE rport from the Discovery Request
 *
 * Called with ctlr_mutex held.
 */
अटल व्योम fcoe_ctlr_vlan_disc_reply(काष्ठा fcoe_ctlr *fip,
				      काष्ठा fcoe_rport *frport)
अणु
	क्रमागत fip_vlan_subcode sub = FIP_SC_VL_NOTE;

	अगर (fip->mode == FIP_MODE_VN2VN)
		sub = FIP_SC_VL_VN2VN_NOTE;

	fcoe_ctlr_vlan_send(fip, sub, frport->enode_mac);
पूर्ण

/**
 * fcoe_ctlr_vlan_recv - vlan request receive handler क्रम VN2VN mode.
 * @fip: The FCoE controller
 * @skb: The received FIP packet
 */
अटल पूर्णांक fcoe_ctlr_vlan_recv(काष्ठा fcoe_ctlr *fip, काष्ठा sk_buff *skb)
अणु
	काष्ठा fip_header *fiph;
	क्रमागत fip_vlan_subcode sub;
	काष्ठा fcoe_rport frport = अणु पूर्ण;
	पूर्णांक rc;

	fiph = (काष्ठा fip_header *)skb->data;
	sub = fiph->fip_subcode;
	rc = fcoe_ctlr_vlan_parse(fip, skb, &frport);
	अगर (rc) अणु
		LIBFCOE_FIP_DBG(fip, "vlan_recv vlan_parse error %d\n", rc);
		जाओ drop;
	पूर्ण
	mutex_lock(&fip->ctlr_mutex);
	अगर (sub == FIP_SC_VL_REQ)
		fcoe_ctlr_vlan_disc_reply(fip, &frport);
	mutex_unlock(&fip->ctlr_mutex);

drop:
	kमुक्त_skb(skb);
	वापस rc;
पूर्ण

/**
 * fcoe_ctlr_disc_recv - discovery receive handler क्रम VN2VN mode.
 * @lport: The local port
 * @fp: The received frame
 *
 * This should never be called since we करोn't see RSCNs or other
 * fabric-generated ELSes.
 */
अटल व्योम fcoe_ctlr_disc_recv(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_seq_els_data rjt_data;

	rjt_data.reason = ELS_RJT_UNSUP;
	rjt_data.explan = ELS_EXPL_NONE;
	fc_seq_els_rsp_send(fp, ELS_LS_RJT, &rjt_data);
	fc_frame_मुक्त(fp);
पूर्ण

/*
 * fcoe_ctlr_disc_start - start discovery क्रम VN2VN mode.
 *
 * This sets a flag indicating that remote ports should be created
 * and started क्रम the peers we discover.  We use the disc_callback
 * poपूर्णांकer as that flag.  Peers alपढ़ोy discovered are created here.
 *
 * The lport lock is held during this call. The callback must be करोne
 * later, without holding either the lport or discovery locks.
 * The fcoe_ctlr lock may also be held during this call.
 */
अटल व्योम fcoe_ctlr_disc_start(व्योम (*callback)(काष्ठा fc_lport *,
						  क्रमागत fc_disc_event),
				 काष्ठा fc_lport *lport)
अणु
	काष्ठा fc_disc *disc = &lport->disc;
	काष्ठा fcoe_ctlr *fip = disc->priv;

	mutex_lock(&disc->disc_mutex);
	disc->disc_callback = callback;
	disc->disc_id = (disc->disc_id + 2) | 1;
	disc->pending = 1;
	schedule_work(&fip->समयr_work);
	mutex_unlock(&disc->disc_mutex);
पूर्ण

/**
 * fcoe_ctlr_vn_disc() - report FIP VN_port discovery results after claim state.
 * @fip: The FCoE controller
 *
 * Starts the FLOGI and PLOGI login process to each discovered rport क्रम which
 * we've received at least one beacon.
 * Perक्रमms the discovery complete callback.
 */
अटल व्योम fcoe_ctlr_vn_disc(काष्ठा fcoe_ctlr *fip)
अणु
	काष्ठा fc_lport *lport = fip->lp;
	काष्ठा fc_disc *disc = &lport->disc;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा fcoe_rport *frport;
	व्योम (*callback)(काष्ठा fc_lport *, क्रमागत fc_disc_event);

	mutex_lock(&disc->disc_mutex);
	callback = disc->pending ? disc->disc_callback : शून्य;
	disc->pending = 0;
	list_क्रम_each_entry_rcu(rdata, &disc->rports, peers) अणु
		अगर (!kref_get_unless_zero(&rdata->kref))
			जारी;
		frport = fcoe_ctlr_rport(rdata);
		अगर (frport->समय)
			fc_rport_login(rdata);
		kref_put(&rdata->kref, fc_rport_destroy);
	पूर्ण
	mutex_unlock(&disc->disc_mutex);
	अगर (callback)
		callback(lport, DISC_EV_SUCCESS);
पूर्ण

/**
 * fcoe_ctlr_vn_समयout - समयr work function क्रम VN2VN mode.
 * @fip: The FCoE controller
 */
अटल व्योम fcoe_ctlr_vn_समयout(काष्ठा fcoe_ctlr *fip)
अणु
	अचिन्हित दीर्घ next_समय;
	u8 mac[ETH_ALEN];
	u32 new_port_id = 0;

	mutex_lock(&fip->ctlr_mutex);
	चयन (fip->state) अणु
	हाल FIP_ST_VNMP_START:
		fcoe_ctlr_set_state(fip, FIP_ST_VNMP_PROBE1);
		LIBFCOE_FIP_DBG(fip, "vn_timeout: send 1st probe request\n");
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		next_समय = jअगरfies + msecs_to_jअगरfies(FIP_VN_PROBE_WAIT);
		अवरोध;
	हाल FIP_ST_VNMP_PROBE1:
		fcoe_ctlr_set_state(fip, FIP_ST_VNMP_PROBE2);
		LIBFCOE_FIP_DBG(fip, "vn_timeout: send 2nd probe request\n");
		fcoe_ctlr_vn_send(fip, FIP_SC_VN_PROBE_REQ, fcoe_all_vn2vn, 0);
		next_समय = jअगरfies + msecs_to_jअगरfies(FIP_VN_ANN_WAIT);
		अवरोध;
	हाल FIP_ST_VNMP_PROBE2:
		fcoe_ctlr_set_state(fip, FIP_ST_VNMP_CLAIM);
		new_port_id = fip->port_id;
		hton24(mac, FIP_VN_FC_MAP);
		hton24(mac + 3, new_port_id);
		fcoe_ctlr_map_dest(fip);
		fip->update_mac(fip->lp, mac);
		LIBFCOE_FIP_DBG(fip, "vn_timeout: send claim notify\n");
		fcoe_ctlr_vn_send_claim(fip);
		next_समय = jअगरfies + msecs_to_jअगरfies(FIP_VN_ANN_WAIT);
		अवरोध;
	हाल FIP_ST_VNMP_CLAIM:
		/*
		 * This may be invoked either by starting discovery so करोn't
		 * go to the next state unless it's been दीर्घ enough.
		 */
		next_समय = fip->sol_समय + msecs_to_jअगरfies(FIP_VN_ANN_WAIT);
		अगर (समय_after_eq(jअगरfies, next_समय)) अणु
			fcoe_ctlr_set_state(fip, FIP_ST_VNMP_UP);
			LIBFCOE_FIP_DBG(fip, "vn_timeout: send vn2vn beacon\n");
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_BEACON,
					  fcoe_all_vn2vn, 0);
			next_समय = jअगरfies + msecs_to_jअगरfies(FIP_VN_ANN_WAIT);
			fip->port_ka_समय = next_समय;
		पूर्ण
		fcoe_ctlr_vn_disc(fip);
		अवरोध;
	हाल FIP_ST_VNMP_UP:
		next_समय = fcoe_ctlr_vn_age(fip);
		अगर (समय_after_eq(jअगरfies, fip->port_ka_समय)) अणु
			LIBFCOE_FIP_DBG(fip, "vn_timeout: send vn2vn beacon\n");
			fcoe_ctlr_vn_send(fip, FIP_SC_VN_BEACON,
					  fcoe_all_vn2vn, 0);
			fip->port_ka_समय = jअगरfies +
				 msecs_to_jअगरfies(FIP_VN_BEACON_INT +
					(pअक्रमom_u32() % FIP_VN_BEACON_FUZZ));
		पूर्ण
		अगर (समय_beक्रमe(fip->port_ka_समय, next_समय))
			next_समय = fip->port_ka_समय;
		अवरोध;
	हाल FIP_ST_LINK_WAIT:
		जाओ unlock;
	शेष:
		WARN(1, "unexpected state %d\n", fip->state);
		जाओ unlock;
	पूर्ण
	mod_समयr(&fip->समयr, next_समय);
unlock:
	mutex_unlock(&fip->ctlr_mutex);

	/* If port ID is new, notअगरy local port after dropping ctlr_mutex */
	अगर (new_port_id)
		fc_lport_set_local_id(fip->lp, new_port_id);
पूर्ण

/**
 * fcoe_ctlr_mode_set() - Set or reset the ctlr's mode
 * @lport: The local port to be (re)configured
 * @fip:   The FCoE controller whose mode is changing
 * @fip_mode: The new fip mode
 *
 * Note that the we shouldn't be changing the libfc discovery settings
 * (fc_disc_config) जबतक an lport is going through the libfc state
 * machine. The mode can only be changed when a fcoe_ctlr device is
 * disabled, so that should ensure that this routine is only called
 * when nothing is happening.
 */
अटल व्योम fcoe_ctlr_mode_set(काष्ठा fc_lport *lport, काष्ठा fcoe_ctlr *fip,
			       क्रमागत fip_mode fip_mode)
अणु
	व्योम *priv;

	WARN_ON(lport->state != LPORT_ST_RESET &&
		lport->state != LPORT_ST_DISABLED);

	अगर (fip_mode == FIP_MODE_VN2VN) अणु
		lport->rport_priv_size = माप(काष्ठा fcoe_rport);
		lport->poपूर्णांक_to_multipoपूर्णांक = 1;
		lport->tt.disc_recv_req = fcoe_ctlr_disc_recv;
		lport->tt.disc_start = fcoe_ctlr_disc_start;
		lport->tt.disc_stop = fcoe_ctlr_disc_stop;
		lport->tt.disc_stop_final = fcoe_ctlr_disc_stop_final;
		priv = fip;
	पूर्ण अन्यथा अणु
		lport->rport_priv_size = 0;
		lport->poपूर्णांक_to_multipoपूर्णांक = 0;
		lport->tt.disc_recv_req = शून्य;
		lport->tt.disc_start = शून्य;
		lport->tt.disc_stop = शून्य;
		lport->tt.disc_stop_final = शून्य;
		priv = lport;
	पूर्ण

	fc_disc_config(lport, priv);
पूर्ण

/**
 * fcoe_libfc_config() - Sets up libfc related properties क्रम local port
 * @lport:    The local port to configure libfc क्रम
 * @fip:      The FCoE controller in use by the local port
 * @tt:       The libfc function ढाँचा
 * @init_fcp: If non-zero, the FCP portion of libfc should be initialized
 *
 * Returns : 0 क्रम success
 */
पूर्णांक fcoe_libfc_config(काष्ठा fc_lport *lport, काष्ठा fcoe_ctlr *fip,
		      स्थिर काष्ठा libfc_function_ढाँचा *tt, पूर्णांक init_fcp)
अणु
	/* Set the function poपूर्णांकers set by the LLDD */
	स_नकल(&lport->tt, tt, माप(*tt));
	अगर (init_fcp && fc_fcp_init(lport))
		वापस -ENOMEM;
	fc_exch_init(lport);
	fc_elsct_init(lport);
	fc_lport_init(lport);
	fc_disc_init(lport);
	fcoe_ctlr_mode_set(lport, fip, fip->mode);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fcoe_libfc_config);

व्योम fcoe_fcf_get_selected(काष्ठा fcoe_fcf_device *fcf_dev)
अणु
	काष्ठा fcoe_ctlr_device *ctlr_dev = fcoe_fcf_dev_to_ctlr_dev(fcf_dev);
	काष्ठा fcoe_ctlr *fip = fcoe_ctlr_device_priv(ctlr_dev);
	काष्ठा fcoe_fcf *fcf;

	mutex_lock(&fip->ctlr_mutex);
	mutex_lock(&ctlr_dev->lock);

	fcf = fcoe_fcf_device_priv(fcf_dev);
	अगर (fcf)
		fcf_dev->selected = (fcf == fip->sel_fcf) ? 1 : 0;
	अन्यथा
		fcf_dev->selected = 0;

	mutex_unlock(&ctlr_dev->lock);
	mutex_unlock(&fip->ctlr_mutex);
पूर्ण
EXPORT_SYMBOL(fcoe_fcf_get_selected);

व्योम fcoe_ctlr_set_fip_mode(काष्ठा fcoe_ctlr_device *ctlr_dev)
अणु
	काष्ठा fcoe_ctlr *ctlr = fcoe_ctlr_device_priv(ctlr_dev);
	काष्ठा fc_lport *lport = ctlr->lp;

	mutex_lock(&ctlr->ctlr_mutex);
	चयन (ctlr_dev->mode) अणु
	हाल FIP_CONN_TYPE_VN2VN:
		ctlr->mode = FIP_MODE_VN2VN;
		अवरोध;
	हाल FIP_CONN_TYPE_FABRIC:
	शेष:
		ctlr->mode = FIP_MODE_FABRIC;
		अवरोध;
	पूर्ण

	mutex_unlock(&ctlr->ctlr_mutex);

	fcoe_ctlr_mode_set(lport, ctlr, ctlr->mode);
पूर्ण
EXPORT_SYMBOL(fcoe_ctlr_set_fip_mode);
