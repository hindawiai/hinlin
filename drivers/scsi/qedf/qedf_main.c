<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/device.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/crc32.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/phylink.h>
#समावेश <scsi/libfc.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/fc_frame.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/cpu.h>
#समावेश "qedf.h"
#समावेश "qedf_dbg.h"
#समावेश <uapi/linux/pci_regs.h>

स्थिर काष्ठा qed_fcoe_ops *qed_ops;

अटल पूर्णांक qedf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id);
अटल व्योम qedf_हटाओ(काष्ठा pci_dev *pdev);
अटल व्योम qedf_shutकरोwn(काष्ठा pci_dev *pdev);
अटल व्योम qedf_schedule_recovery_handler(व्योम *dev);
अटल व्योम qedf_recovery_handler(काष्ठा work_काष्ठा *work);

/*
 * Driver module parameters.
 */
अटल अचिन्हित पूर्णांक qedf_dev_loss_पंचांगo = 60;
module_param_named(dev_loss_पंचांगo, qedf_dev_loss_पंचांगo, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev_loss_पंचांगo,  " dev_loss_tmo setting for attached "
	"remote ports (default 60)");

uपूर्णांक qedf_debug = QEDF_LOG_INFO;
module_param_named(debug, qedf_debug, uपूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(debug, " Debug mask. Pass '1' to enable default debugging"
	" mask");

अटल uपूर्णांक qedf_fipvlan_retries = 60;
module_param_named(fipvlan_retries, qedf_fipvlan_retries, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(fipvlan_retries, " Number of FIP VLAN requests to attempt "
	"before giving up (default 60)");

अटल uपूर्णांक qedf_fallback_vlan = QEDF_FALLBACK_VLAN;
module_param_named(fallback_vlan, qedf_fallback_vlan, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(fallback_vlan, " VLAN ID to try if fip vlan request fails "
	"(default 1002).");

अटल पूर्णांक qedf_शेष_prio = -1;
module_param_named(शेष_prio, qedf_शेष_prio, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(शेष_prio, " Override 802.1q priority for FIP and FCoE"
	" traffic (value between 0 and 7, default 3).");

uपूर्णांक qedf_dump_frames;
module_param_named(dump_frames, qedf_dump_frames, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dump_frames, " Print the skb data of FIP and FCoE frames "
	"(default off)");

अटल uपूर्णांक qedf_queue_depth;
module_param_named(queue_depth, qedf_queue_depth, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(queue_depth, " Sets the queue depth for all LUNs discovered "
	"by the qedf driver. Default is 0 (use OS default).");

uपूर्णांक qedf_io_tracing;
module_param_named(io_tracing, qedf_io_tracing, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(io_tracing, " Enable logging of SCSI requests/completions "
	"into trace buffer. (default off).");

अटल uपूर्णांक qedf_max_lun = MAX_FIBRE_LUNS;
module_param_named(max_lun, qedf_max_lun, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(max_lun, " Sets the maximum luns per target that the driver "
	"supports. (default 0xffffffff)");

uपूर्णांक qedf_link_करोwn_पंचांगo;
module_param_named(link_करोwn_पंचांगo, qedf_link_करोwn_पंचांगo, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(link_करोwn_पंचांगo, " Delays informing the fcoe transport that the "
	"link is down by N seconds.");

bool qedf_retry_delay;
module_param_named(retry_delay, qedf_retry_delay, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(retry_delay, " Enable/disable handling of FCP_RSP IU retry "
	"delay handling (default off).");

अटल bool qedf_dcbx_no_रुको;
module_param_named(dcbx_no_रुको, qedf_dcbx_no_रुको, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dcbx_no_रुको, " Do not wait for DCBX convergence to start "
	"sending FIP VLAN requests on link up (Default: off).");

अटल uपूर्णांक qedf_dp_module;
module_param_named(dp_module, qedf_dp_module, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dp_module, " bit flags control for verbose printk passed "
	"qed module during probe.");

अटल uपूर्णांक qedf_dp_level = QED_LEVEL_NOTICE;
module_param_named(dp_level, qedf_dp_level, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dp_level, " printk verbosity control passed to qed module  "
	"during probe (0-3: 0 more verbose).");

अटल bool qedf_enable_recovery = true;
module_param_named(enable_recovery, qedf_enable_recovery,
		bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(enable_recovery, "Enable/disable recovery on driver/firmware "
		"interface level errors 0 = Disabled, 1 = Enabled (Default: 1).");

काष्ठा workqueue_काष्ठा *qedf_io_wq;

अटल काष्ठा fcoe_percpu_s qedf_global;
अटल DEFINE_SPINLOCK(qedf_global_lock);

अटल काष्ठा kmem_cache *qedf_io_work_cache;

व्योम qedf_set_vlan_id(काष्ठा qedf_ctx *qedf, पूर्णांक vlan_id)
अणु
	पूर्णांक vlan_id_पंचांगp = 0;

	vlan_id_पंचांगp = vlan_id  | (qedf->prio << VLAN_PRIO_SHIFT);
	qedf->vlan_id = vlan_id_पंचांगp;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "Setting vlan_id=0x%04x prio=%d.\n",
		  vlan_id_पंचांगp, qedf->prio);
पूर्ण

/* Returns true अगर we have a valid vlan, false otherwise */
अटल bool qedf_initiate_fipvlan_req(काष्ठा qedf_ctx *qedf)
अणु

	जबतक (qedf->fipvlan_retries--) अणु
		/* This is to catch अगर link goes करोwn during fipvlan retries */
		अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_DOWN) अणु
			QEDF_ERR(&qedf->dbg_ctx, "Link not up.\n");
			वापस false;
		पूर्ण

		अगर (test_bit(QEDF_UNLOADING, &qedf->flags)) अणु
			QEDF_ERR(&qedf->dbg_ctx, "Driver unloading.\n");
			वापस false;
		पूर्ण

		अगर (qedf->vlan_id > 0) अणु
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
				  "vlan = 0x%x already set, calling ctlr_link_up.\n",
				  qedf->vlan_id);
			अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_UP)
				fcoe_ctlr_link_up(&qedf->ctlr);
			वापस true;
		पूर्ण

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			   "Retry %d.\n", qedf->fipvlan_retries);
		init_completion(&qedf->fipvlan_compl);
		qedf_fcoe_send_vlan_req(qedf);
		रुको_क्रम_completion_समयout(&qedf->fipvlan_compl, 1 * HZ);
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम qedf_handle_link_update(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_ctx *qedf =
	    container_of(work, काष्ठा qedf_ctx, link_update.work);
	पूर्णांक rc;

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC, "Entered. link_state=%d.\n",
		  atomic_पढ़ो(&qedf->link_state));

	अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_UP) अणु
		rc = qedf_initiate_fipvlan_req(qedf);
		अगर (rc)
			वापस;

		अगर (atomic_पढ़ो(&qedf->link_state) != QEDF_LINK_UP) अणु
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
				  "Link is down, resetting vlan_id.\n");
			qedf->vlan_id = 0;
			वापस;
		पूर्ण

		/*
		 * If we get here then we never received a repsonse to our
		 * fip vlan request so set the vlan_id to the शेष and
		 * tell FCoE that the link is up
		 */
		QEDF_WARN(&(qedf->dbg_ctx), "Did not receive FIP VLAN "
			   "response, falling back to default VLAN %d.\n",
			   qedf_fallback_vlan);
		qedf_set_vlan_id(qedf, qedf_fallback_vlan);

		/*
		 * Zero out data_src_addr so we'll update it with the new
		 * lport port_id
		 */
		eth_zero_addr(qedf->data_src_addr);
		fcoe_ctlr_link_up(&qedf->ctlr);
	पूर्ण अन्यथा अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_DOWN) अणु
		/*
		 * If we hit here and link_करोwn_पंचांगo_valid is still 1 it means
		 * that link_करोwn_पंचांगo समयd out so set it to 0 to make sure any
		 * other पढ़ोers have accurate state.
		 */
		atomic_set(&qedf->link_करोwn_पंचांगo_valid, 0);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		    "Calling fcoe_ctlr_link_down().\n");
		fcoe_ctlr_link_करोwn(&qedf->ctlr);
		अगर (qedf_रुको_क्रम_upload(qedf) == false)
			QEDF_ERR(&qedf->dbg_ctx,
				 "Could not upload all sessions.\n");
		/* Reset the number of FIP VLAN retries */
		qedf->fipvlan_retries = qedf_fipvlan_retries;
	पूर्ण
पूर्ण

#घोषणा	QEDF_FCOE_MAC_METHOD_GRANGED_MAC		1
#घोषणा QEDF_FCOE_MAC_METHOD_FCF_MAP			2
#घोषणा QEDF_FCOE_MAC_METHOD_FCOE_SET_MAC		3
अटल व्योम qedf_set_data_src_addr(काष्ठा qedf_ctx *qedf, काष्ठा fc_frame *fp)
अणु
	u8 *granted_mac;
	काष्ठा fc_frame_header *fh = fc_frame_header_get(fp);
	u8 fc_map[3];
	पूर्णांक method = 0;

	/* Get granted MAC address from FIP FLOGI payload */
	granted_mac = fr_cb(fp)->granted_mac;

	/*
	 * We set the source MAC क्रम FCoE traffic based on the Granted MAC
	 * address from the चयन.
	 *
	 * If granted_mac is non-zero, we used that.
	 * If the granted_mac is zeroed out, created the FCoE MAC based on
	 * the sel_fcf->fc_map and the d_id fo the FLOGI frame.
	 * If sel_fcf->fc_map is 0 then we use the शेष FCF-MAC plus the
	 * d_id of the FLOGI frame.
	 */
	अगर (!is_zero_ether_addr(granted_mac)) अणु
		ether_addr_copy(qedf->data_src_addr, granted_mac);
		method = QEDF_FCOE_MAC_METHOD_GRANGED_MAC;
	पूर्ण अन्यथा अगर (qedf->ctlr.sel_fcf->fc_map != 0) अणु
		hton24(fc_map, qedf->ctlr.sel_fcf->fc_map);
		qedf->data_src_addr[0] = fc_map[0];
		qedf->data_src_addr[1] = fc_map[1];
		qedf->data_src_addr[2] = fc_map[2];
		qedf->data_src_addr[3] = fh->fh_d_id[0];
		qedf->data_src_addr[4] = fh->fh_d_id[1];
		qedf->data_src_addr[5] = fh->fh_d_id[2];
		method = QEDF_FCOE_MAC_METHOD_FCF_MAP;
	पूर्ण अन्यथा अणु
		fc_fcoe_set_mac(qedf->data_src_addr, fh->fh_d_id);
		method = QEDF_FCOE_MAC_METHOD_FCOE_SET_MAC;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
	    "QEDF data_src_mac=%pM method=%d.\n", qedf->data_src_addr, method);
पूर्ण

अटल व्योम qedf_flogi_resp(काष्ठा fc_seq *seq, काष्ठा fc_frame *fp,
	व्योम *arg)
अणु
	काष्ठा fc_exch *exch = fc_seq_exch(seq);
	काष्ठा fc_lport *lport = exch->lp;
	काष्ठा qedf_ctx *qedf = lport_priv(lport);

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL.\n");
		वापस;
	पूर्ण

	/*
	 * If ERR_PTR is set then करोn't try to stat anything as it will cause
	 * a crash when we access fp.
	 */
	अगर (IS_ERR(fp)) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
		    "fp has IS_ERR() set.\n");
		जाओ skip_stat;
	पूर्ण

	/* Log stats क्रम FLOGI reject */
	अगर (fc_frame_payload_op(fp) == ELS_LS_RJT)
		qedf->flogi_failed++;
	अन्यथा अगर (fc_frame_payload_op(fp) == ELS_LS_ACC) अणु
		/* Set the source MAC we will use क्रम FCoE traffic */
		qedf_set_data_src_addr(qedf, fp);
		qedf->flogi_pending = 0;
	पूर्ण

	/* Complete flogi_compl so we can proceed to sending ADISCs */
	complete(&qedf->flogi_compl);

skip_stat:
	/* Report response to libfc */
	fc_lport_flogi_resp(seq, fp, lport);
पूर्ण

अटल काष्ठा fc_seq *qedf_elsct_send(काष्ठा fc_lport *lport, u32 did,
	काष्ठा fc_frame *fp, अचिन्हित पूर्णांक op,
	व्योम (*resp)(काष्ठा fc_seq *,
	काष्ठा fc_frame *,
	व्योम *),
	व्योम *arg, u32 समयout)
अणु
	काष्ठा qedf_ctx *qedf = lport_priv(lport);

	/*
	 * Intercept FLOGI क्रम statistic purposes. Note we use the resp
	 * callback to tell अगर this is really a flogi.
	 */
	अगर (resp == fc_lport_flogi_resp) अणु
		qedf->flogi_cnt++;
		अगर (qedf->flogi_pending >= QEDF_FLOGI_RETRY_CNT) अणु
			schedule_delayed_work(&qedf->stag_work, 2);
			वापस शून्य;
		पूर्ण
		qedf->flogi_pending++;
		वापस fc_elsct_send(lport, did, fp, op, qedf_flogi_resp,
		    arg, समयout);
	पूर्ण

	वापस fc_elsct_send(lport, did, fp, op, resp, arg, समयout);
पूर्ण

पूर्णांक qedf_send_flogi(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा fc_frame *fp;

	lport = qedf->lport;

	अगर (!lport->tt.elsct_send) अणु
		QEDF_ERR(&qedf->dbg_ctx, "tt.elsct_send not set.\n");
		वापस -EINVAL;
	पूर्ण

	fp = fc_frame_alloc(lport, माप(काष्ठा fc_els_flogi));
	अगर (!fp) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "fc_frame_alloc failed.\n");
		वापस -ENOMEM;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_ELS,
	    "Sending FLOGI to reestablish session with switch.\n");
	lport->tt.elsct_send(lport, FC_FID_FLOGI, fp,
	    ELS_FLOGI, qedf_flogi_resp, lport, lport->r_a_tov);

	init_completion(&qedf->flogi_compl);

	वापस 0;
पूर्ण

/*
 * This function is called अगर link_करोwn_पंचांगo is in use.  If we get a link up and
 * link_करोwn_पंचांगo has not expired then use just FLOGI/ADISC to recover our
 * sessions with tarमाला_लो.  Otherwise, just call fcoe_ctlr_link_up().
 */
अटल व्योम qedf_link_recovery(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_ctx *qedf =
	    container_of(work, काष्ठा qedf_ctx, link_recovery.work);
	काष्ठा fc_lport *lport = qedf->lport;
	काष्ठा fc_rport_priv *rdata;
	bool rc;
	पूर्णांक retries = 30;
	पूर्णांक rval, i;
	काष्ठा list_head rdata_login_list;

	INIT_LIST_HEAD(&rdata_login_list);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
	    "Link down tmo did not expire.\n");

	/*
	 * Essentially reset the fcoe_ctlr here without affecting the state
	 * of the libfc काष्ठाs.
	 */
	qedf->ctlr.state = FIP_ST_LINK_WAIT;
	fcoe_ctlr_link_करोwn(&qedf->ctlr);

	/*
	 * Bring the link up beक्रमe we send the fipvlan request so libfcoe
	 * can select a new fcf in parallel
	 */
	fcoe_ctlr_link_up(&qedf->ctlr);

	/* Since the link when करोwn and up to verअगरy which vlan we're on */
	qedf->fipvlan_retries = qedf_fipvlan_retries;
	rc = qedf_initiate_fipvlan_req(qedf);
	/* If getting the VLAN fails, set the VLAN to the fallback one */
	अगर (!rc)
		qedf_set_vlan_id(qedf, qedf_fallback_vlan);

	/*
	 * We need to रुको क्रम an FCF to be selected due to the
	 * fcoe_ctlr_link_up other the FLOGI will be rejected.
	 */
	जबतक (retries > 0) अणु
		अगर (qedf->ctlr.sel_fcf) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "FCF reselected, proceeding with FLOGI.\n");
			अवरोध;
		पूर्ण
		msleep(500);
		retries--;
	पूर्ण

	अगर (retries < 1) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Exhausted retries waiting for "
		    "FCF selection.\n");
		वापस;
	पूर्ण

	rval = qedf_send_flogi(qedf);
	अगर (rval)
		वापस;

	/* Wait क्रम FLOGI completion beक्रमe proceeding with sending ADISCs */
	i = रुको_क्रम_completion_समयout(&qedf->flogi_compl,
	    qedf->lport->r_a_tov);
	अगर (i == 0) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "FLOGI timed out.\n");
		वापस;
	पूर्ण

	/*
	 * Call lport->tt.rport_login which will cause libfc to send an
	 * ADISC since the rport is in state पढ़ोy.
	 */
	mutex_lock(&lport->disc.disc_mutex);
	list_क्रम_each_entry_rcu(rdata, &lport->disc.rports, peers) अणु
		अगर (kref_get_unless_zero(&rdata->kref)) अणु
			fc_rport_login(rdata);
			kref_put(&rdata->kref, fc_rport_destroy);
		पूर्ण
	पूर्ण
	mutex_unlock(&lport->disc.disc_mutex);
पूर्ण

अटल व्योम qedf_update_link_speed(काष्ठा qedf_ctx *qedf,
	काष्ठा qed_link_output *link)
अणु
	__ETHTOOL_DECLARE_LINK_MODE_MASK(sup_caps);
	काष्ठा fc_lport *lport = qedf->lport;

	lport->link_speed = FC_PORTSPEED_UNKNOWN;
	lport->link_supported_speeds = FC_PORTSPEED_UNKNOWN;

	/* Set fc_host link speed */
	चयन (link->speed) अणु
	हाल 10000:
		lport->link_speed = FC_PORTSPEED_10GBIT;
		अवरोध;
	हाल 25000:
		lport->link_speed = FC_PORTSPEED_25GBIT;
		अवरोध;
	हाल 40000:
		lport->link_speed = FC_PORTSPEED_40GBIT;
		अवरोध;
	हाल 50000:
		lport->link_speed = FC_PORTSPEED_50GBIT;
		अवरोध;
	हाल 100000:
		lport->link_speed = FC_PORTSPEED_100GBIT;
		अवरोध;
	हाल 20000:
		lport->link_speed = FC_PORTSPEED_20GBIT;
		अवरोध;
	शेष:
		lport->link_speed = FC_PORTSPEED_UNKNOWN;
		अवरोध;
	पूर्ण

	/*
	 * Set supported link speed by querying the supported
	 * capabilities of the link.
	 */

	phylink_zero(sup_caps);
	phylink_set(sup_caps, 10000baseT_Full);
	phylink_set(sup_caps, 10000baseKX4_Full);
	phylink_set(sup_caps, 10000baseR_FEC);
	phylink_set(sup_caps, 10000baseCR_Full);
	phylink_set(sup_caps, 10000baseSR_Full);
	phylink_set(sup_caps, 10000baseLR_Full);
	phylink_set(sup_caps, 10000baseLRM_Full);
	phylink_set(sup_caps, 10000baseKR_Full);

	अगर (linkmode_पूर्णांकersects(link->supported_caps, sup_caps))
		lport->link_supported_speeds |= FC_PORTSPEED_10GBIT;

	phylink_zero(sup_caps);
	phylink_set(sup_caps, 25000baseKR_Full);
	phylink_set(sup_caps, 25000baseCR_Full);
	phylink_set(sup_caps, 25000baseSR_Full);

	अगर (linkmode_पूर्णांकersects(link->supported_caps, sup_caps))
		lport->link_supported_speeds |= FC_PORTSPEED_25GBIT;

	phylink_zero(sup_caps);
	phylink_set(sup_caps, 40000baseLR4_Full);
	phylink_set(sup_caps, 40000baseKR4_Full);
	phylink_set(sup_caps, 40000baseCR4_Full);
	phylink_set(sup_caps, 40000baseSR4_Full);

	अगर (linkmode_पूर्णांकersects(link->supported_caps, sup_caps))
		lport->link_supported_speeds |= FC_PORTSPEED_40GBIT;

	phylink_zero(sup_caps);
	phylink_set(sup_caps, 50000baseKR2_Full);
	phylink_set(sup_caps, 50000baseCR2_Full);
	phylink_set(sup_caps, 50000baseSR2_Full);

	अगर (linkmode_पूर्णांकersects(link->supported_caps, sup_caps))
		lport->link_supported_speeds |= FC_PORTSPEED_50GBIT;

	phylink_zero(sup_caps);
	phylink_set(sup_caps, 100000baseKR4_Full);
	phylink_set(sup_caps, 100000baseSR4_Full);
	phylink_set(sup_caps, 100000baseCR4_Full);
	phylink_set(sup_caps, 100000baseLR4_ER4_Full);

	अगर (linkmode_पूर्णांकersects(link->supported_caps, sup_caps))
		lport->link_supported_speeds |= FC_PORTSPEED_100GBIT;

	phylink_zero(sup_caps);
	phylink_set(sup_caps, 20000baseKR2_Full);

	अगर (linkmode_पूर्णांकersects(link->supported_caps, sup_caps))
		lport->link_supported_speeds |= FC_PORTSPEED_20GBIT;

	अगर (lport->host && lport->host->shost_data)
		fc_host_supported_speeds(lport->host) =
			lport->link_supported_speeds;
पूर्ण

अटल व्योम qedf_bw_update(व्योम *dev)
अणु
	काष्ठा qedf_ctx *qedf = (काष्ठा qedf_ctx *)dev;
	काष्ठा qed_link_output link;

	/* Get the latest status of the link */
	qed_ops->common->get_link(qedf->cdev, &link);

	अगर (test_bit(QEDF_UNLOADING, &qedf->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Ignore link update, driver getting unload.\n");
		वापस;
	पूर्ण

	अगर (link.link_up) अणु
		अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_UP)
			qedf_update_link_speed(qedf, &link);
		अन्यथा
			QEDF_ERR(&qedf->dbg_ctx,
				 "Ignore bw update, link is down.\n");

	पूर्ण अन्यथा अणु
		QEDF_ERR(&qedf->dbg_ctx, "link_up is not set.\n");
	पूर्ण
पूर्ण

अटल व्योम qedf_link_update(व्योम *dev, काष्ठा qed_link_output *link)
अणु
	काष्ठा qedf_ctx *qedf = (काष्ठा qedf_ctx *)dev;

	/*
	 * Prevent race where we're removing the module and we get link update
	 * क्रम qed.
	 */
	अगर (test_bit(QEDF_UNLOADING, &qedf->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Ignore link update, driver getting unload.\n");
		वापस;
	पूर्ण

	अगर (link->link_up) अणु
		अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_UP) अणु
			QEDF_INFO((&qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Ignoring link up event as link is already up.\n");
			वापस;
		पूर्ण
		QEDF_ERR(&(qedf->dbg_ctx), "LINK UP (%d GB/s).\n",
		    link->speed / 1000);

		/* Cancel any pending link करोwn work */
		cancel_delayed_work(&qedf->link_update);

		atomic_set(&qedf->link_state, QEDF_LINK_UP);
		qedf_update_link_speed(qedf, link);

		अगर (atomic_पढ़ो(&qedf->dcbx) == QEDF_DCBX_DONE ||
		    qedf_dcbx_no_रुको) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			     "DCBx done.\n");
			अगर (atomic_पढ़ो(&qedf->link_करोwn_पंचांगo_valid) > 0)
				queue_delayed_work(qedf->link_update_wq,
				    &qedf->link_recovery, 0);
			अन्यथा
				queue_delayed_work(qedf->link_update_wq,
				    &qedf->link_update, 0);
			atomic_set(&qedf->link_करोwn_पंचांगo_valid, 0);
		पूर्ण

	पूर्ण अन्यथा अणु
		QEDF_ERR(&(qedf->dbg_ctx), "LINK DOWN.\n");

		atomic_set(&qedf->link_state, QEDF_LINK_DOWN);
		atomic_set(&qedf->dcbx, QEDF_DCBX_PENDING);
		/*
		 * Flag that we're रुकोing क्रम the link to come back up beक्रमe
		 * inक्रमming the fcoe layer of the event.
		 */
		अगर (qedf_link_करोwn_पंचांगo > 0) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Starting link down tmo.\n");
			atomic_set(&qedf->link_करोwn_पंचांगo_valid, 1);
		पूर्ण
		qedf->vlan_id = 0;
		qedf_update_link_speed(qedf, link);
		queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
		    qedf_link_करोwn_पंचांगo * HZ);
	पूर्ण
पूर्ण


अटल व्योम qedf_dcbx_handler(व्योम *dev, काष्ठा qed_dcbx_get *get, u32 mib_type)
अणु
	काष्ठा qedf_ctx *qedf = (काष्ठा qedf_ctx *)dev;
	u8 पंचांगp_prio;

	QEDF_ERR(&(qedf->dbg_ctx), "DCBx event valid=%d enabled=%d fcoe "
	    "prio=%d.\n", get->operational.valid, get->operational.enabled,
	    get->operational.app_prio.fcoe);

	अगर (get->operational.enabled && get->operational.valid) अणु
		/* If DCBX was alपढ़ोy negotiated on link up then just निकास */
		अगर (atomic_पढ़ो(&qedf->dcbx) == QEDF_DCBX_DONE) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "DCBX already set on link up.\n");
			वापस;
		पूर्ण

		atomic_set(&qedf->dcbx, QEDF_DCBX_DONE);

		/*
		 * Set the 8021q priority in the following manner:
		 *
		 * 1. If a modparam is set use that
		 * 2. If the value is not between 0..7 use the शेष
		 * 3. Use the priority we get from the DCBX app tag
		 */
		पंचांगp_prio = get->operational.app_prio.fcoe;
		अगर (qedf_शेष_prio > -1)
			qedf->prio = qedf_शेष_prio;
		अन्यथा अगर (पंचांगp_prio > 7) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "FIP/FCoE prio %d out of range, setting to %d.\n",
			    पंचांगp_prio, QEDF_DEFAULT_PRIO);
			qedf->prio = QEDF_DEFAULT_PRIO;
		पूर्ण अन्यथा
			qedf->prio = पंचांगp_prio;

		अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_UP &&
		    !qedf_dcbx_no_रुको) अणु
			अगर (atomic_पढ़ो(&qedf->link_करोwn_पंचांगo_valid) > 0)
				queue_delayed_work(qedf->link_update_wq,
				    &qedf->link_recovery, 0);
			अन्यथा
				queue_delayed_work(qedf->link_update_wq,
				    &qedf->link_update, 0);
			atomic_set(&qedf->link_करोwn_पंचांगo_valid, 0);
		पूर्ण
	पूर्ण

पूर्ण

अटल u32 qedf_get_login_failures(व्योम *cookie)
अणु
	काष्ठा qedf_ctx *qedf;

	qedf = (काष्ठा qedf_ctx *)cookie;
	वापस qedf->flogi_failed;
पूर्ण

अटल काष्ठा qed_fcoe_cb_ops qedf_cb_ops = अणु
	अणु
		.link_update = qedf_link_update,
		.bw_update = qedf_bw_update,
		.schedule_recovery_handler = qedf_schedule_recovery_handler,
		.dcbx_aen = qedf_dcbx_handler,
		.get_generic_tlv_data = qedf_get_generic_tlv_data,
		.get_protocol_tlv_data = qedf_get_protocol_tlv_data,
		.schedule_hw_err_handler = qedf_schedule_hw_err_handler,
	पूर्ण
पूर्ण;

/*
 * Various transport ढाँचाs.
 */

अटल काष्ठा scsi_transport_ढाँचा *qedf_fc_transport_ढाँचा;
अटल काष्ठा scsi_transport_ढाँचा *qedf_fc_vport_transport_ढाँचा;

/*
 * SCSI EH handlers
 */
अटल पूर्णांक qedf_eh_पात(काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_rport *rport = starget_to_rport(scsi_target(sc_cmd->device));
	काष्ठा fc_lport *lport;
	काष्ठा qedf_ctx *qedf;
	काष्ठा qedf_ioreq *io_req;
	काष्ठा fc_rport_libfc_priv *rp = rport->dd_data;
	काष्ठा fc_rport_priv *rdata;
	काष्ठा qedf_rport *fcport = शून्य;
	पूर्णांक rc = FAILED;
	पूर्णांक रुको_count = 100;
	पूर्णांक refcount = 0;
	पूर्णांक rval;
	पूर्णांक got_ref = 0;

	lport = shost_priv(sc_cmd->device->host);
	qedf = (काष्ठा qedf_ctx *)lport_priv(lport);

	/* rport and tgt are allocated together, so tgt should be non-शून्य */
	fcport = (काष्ठा qedf_rport *)&rp[1];
	rdata = fcport->rdata;
	अगर (!rdata || !kref_get_unless_zero(&rdata->kref)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "stale rport, sc_cmd=%p\n", sc_cmd);
		rc = SUCCESS;
		जाओ out;
	पूर्ण


	io_req = (काष्ठा qedf_ioreq *)sc_cmd->SCp.ptr;
	अगर (!io_req) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "sc_cmd not queued with lld, sc_cmd=%p op=0x%02x, port_id=%06x\n",
			 sc_cmd, sc_cmd->cmnd[0],
			 rdata->ids.port_id);
		rc = SUCCESS;
		जाओ drop_rdata_kref;
	पूर्ण

	rval = kref_get_unless_zero(&io_req->refcount);	/* ID: 005 */
	अगर (rval)
		got_ref = 1;

	/* If we got a valid io_req, confirm it beदीर्घs to this sc_cmd. */
	अगर (!rval || io_req->sc_cmd != sc_cmd) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Freed/Incorrect io_req, io_req->sc_cmd=%p, sc_cmd=%p, port_id=%06x, bailing out.\n",
			 io_req->sc_cmd, sc_cmd, rdata->ids.port_id);

		जाओ drop_rdata_kref;
	पूर्ण

	अगर (fc_remote_port_chkपढ़ोy(rport)) अणु
		refcount = kref_पढ़ो(&io_req->refcount);
		QEDF_ERR(&qedf->dbg_ctx,
			 "rport not ready, io_req=%p, xid=0x%x sc_cmd=%p op=0x%02x, refcount=%d, port_id=%06x\n",
			 io_req, io_req->xid, sc_cmd, sc_cmd->cmnd[0],
			 refcount, rdata->ids.port_id);

		जाओ drop_rdata_kref;
	पूर्ण

	rc = fc_block_scsi_eh(sc_cmd);
	अगर (rc)
		जाओ drop_rdata_kref;

	अगर (test_bit(QEDF_RPORT_UPLOADING_CONNECTION, &fcport->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Connection uploading, xid=0x%x., port_id=%06x\n",
			 io_req->xid, rdata->ids.port_id);
		जबतक (io_req->sc_cmd && (रुको_count != 0)) अणु
			msleep(100);
			रुको_count--;
		पूर्ण
		अगर (रुको_count) अणु
			QEDF_ERR(&qedf->dbg_ctx, "ABTS succeeded\n");
			rc = SUCCESS;
		पूर्ण अन्यथा अणु
			QEDF_ERR(&qedf->dbg_ctx, "ABTS failed\n");
			rc = FAILED;
		पूर्ण
		जाओ drop_rdata_kref;
	पूर्ण

	अगर (lport->state != LPORT_ST_READY || !(lport->link_up)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "link not ready.\n");
		जाओ drop_rdata_kref;
	पूर्ण

	QEDF_ERR(&qedf->dbg_ctx,
		 "Aborting io_req=%p sc_cmd=%p xid=0x%x fp_idx=%d, port_id=%06x.\n",
		 io_req, sc_cmd, io_req->xid, io_req->fp_idx,
		 rdata->ids.port_id);

	अगर (qedf->stop_io_on_error) अणु
		qedf_stop_all_io(qedf);
		rc = SUCCESS;
		जाओ drop_rdata_kref;
	पूर्ण

	init_completion(&io_req->abts_करोne);
	rval = qedf_initiate_abts(io_req, true);
	अगर (rval) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to queue ABTS.\n");
		/*
		 * If we fail to queue the ABTS then वापस this command to
		 * the SCSI layer as it will own and मुक्त the xid
		 */
		rc = SUCCESS;
		qedf_scsi_करोne(qedf, io_req, DID_ERROR);
		जाओ drop_rdata_kref;
	पूर्ण

	रुको_क्रम_completion(&io_req->abts_करोne);

	अगर (io_req->event == QEDF_IOREQ_EV_ABORT_SUCCESS ||
	    io_req->event == QEDF_IOREQ_EV_ABORT_FAILED ||
	    io_req->event == QEDF_IOREQ_EV_CLEANUP_SUCCESS) अणु
		/*
		 * If we get a reponse to the पात this is success from
		 * the perspective that all references to the command have
		 * been हटाओd from the driver and firmware
		 */
		rc = SUCCESS;
	पूर्ण अन्यथा अणु
		/* If the पात and cleanup failed then वापस a failure */
		rc = FAILED;
	पूर्ण

	अगर (rc == SUCCESS)
		QEDF_ERR(&(qedf->dbg_ctx), "ABTS succeeded, xid=0x%x.\n",
			  io_req->xid);
	अन्यथा
		QEDF_ERR(&(qedf->dbg_ctx), "ABTS failed, xid=0x%x.\n",
			  io_req->xid);

drop_rdata_kref:
	kref_put(&rdata->kref, fc_rport_destroy);
out:
	अगर (got_ref)
		kref_put(&io_req->refcount, qedf_release_cmd);
	वापस rc;
पूर्ण

अटल पूर्णांक qedf_eh_target_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	QEDF_ERR(शून्य, "%d:0:%d:%lld: TARGET RESET Issued...",
		 sc_cmd->device->host->host_no, sc_cmd->device->id,
		 sc_cmd->device->lun);
	वापस qedf_initiate_पंचांगf(sc_cmd, FCP_TMF_TGT_RESET);
पूर्ण

अटल पूर्णांक qedf_eh_device_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	QEDF_ERR(शून्य, "%d:0:%d:%lld: LUN RESET Issued... ",
		 sc_cmd->device->host->host_no, sc_cmd->device->id,
		 sc_cmd->device->lun);
	वापस qedf_initiate_पंचांगf(sc_cmd, FCP_TMF_LUN_RESET);
पूर्ण

bool qedf_रुको_क्रम_upload(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा qedf_rport *fcport = शून्य;
	पूर्णांक रुको_cnt = 120;

	जबतक (रुको_cnt--) अणु
		अगर (atomic_पढ़ो(&qedf->num_offloads))
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
				  "Waiting for all uploads to complete num_offloads = 0x%x.\n",
				  atomic_पढ़ो(&qedf->num_offloads));
		अन्यथा
			वापस true;
		msleep(500);
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(fcport, &qedf->fcports, peers) अणु
		अगर (fcport && test_bit(QEDF_RPORT_SESSION_READY,
				       &fcport->flags)) अणु
			अगर (fcport->rdata)
				QEDF_ERR(&qedf->dbg_ctx,
					 "Waiting for fcport %p portid=%06x.\n",
					 fcport, fcport->rdata->ids.port_id);
			पूर्ण अन्यथा अणु
				QEDF_ERR(&qedf->dbg_ctx,
					 "Waiting for fcport %p.\n", fcport);
			पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस false;

पूर्ण

/* Perक्रमms soft reset of qedf_ctx by simulating a link करोwn/up */
व्योम qedf_ctx_soft_reset(काष्ठा fc_lport *lport)
अणु
	काष्ठा qedf_ctx *qedf;
	काष्ठा qed_link_output अगर_link;

	अगर (lport->vport) अणु
		QEDF_ERR(शून्य, "Cannot issue host reset on NPIV port.\n");
		वापस;
	पूर्ण

	qedf = lport_priv(lport);

	qedf->flogi_pending = 0;
	/* For host reset, essentially करो a soft link up/करोwn */
	atomic_set(&qedf->link_state, QEDF_LINK_DOWN);
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "Queuing link down work.\n");
	queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
	    0);

	अगर (qedf_रुको_क्रम_upload(qedf) == false) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Could not upload all sessions.\n");
		WARN_ON(atomic_पढ़ो(&qedf->num_offloads));
	पूर्ण

	/* Beक्रमe setting link up query physical link state */
	qed_ops->common->get_link(qedf->cdev, &अगर_link);
	/* Bail अगर the physical link is not up */
	अगर (!अगर_link.link_up) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
			  "Physical link is not up.\n");
		वापस;
	पूर्ण
	/* Flush and रुको to make sure link करोwn is processed */
	flush_delayed_work(&qedf->link_update);
	msleep(500);

	atomic_set(&qedf->link_state, QEDF_LINK_UP);
	qedf->vlan_id  = 0;
	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "Queue link up work.\n");
	queue_delayed_work(qedf->link_update_wq, &qedf->link_update,
	    0);
पूर्ण

/* Reset the host by gracefully logging out and then logging back in */
अटल पूर्णांक qedf_eh_host_reset(काष्ठा scsi_cmnd *sc_cmd)
अणु
	काष्ठा fc_lport *lport;
	काष्ठा qedf_ctx *qedf;

	lport = shost_priv(sc_cmd->device->host);
	qedf = lport_priv(lport);

	अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_DOWN ||
	    test_bit(QEDF_UNLOADING, &qedf->flags))
		वापस FAILED;

	QEDF_ERR(&(qedf->dbg_ctx), "HOST RESET Issued...");

	qedf_ctx_soft_reset(lport);

	वापस SUCCESS;
पूर्ण

अटल पूर्णांक qedf_slave_configure(काष्ठा scsi_device *sdev)
अणु
	अगर (qedf_queue_depth) अणु
		scsi_change_queue_depth(sdev, qedf_queue_depth);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा qedf_host_ढाँचा = अणु
	.module 	= THIS_MODULE,
	.name 		= QEDF_MODULE_NAME,
	.this_id 	= -1,
	.cmd_per_lun	= 32,
	.max_sectors 	= 0xffff,
	.queuecommand 	= qedf_queuecommand,
	.shost_attrs	= qedf_host_attrs,
	.eh_पात_handler	= qedf_eh_पात,
	.eh_device_reset_handler = qedf_eh_device_reset, /* lun reset */
	.eh_target_reset_handler = qedf_eh_target_reset, /* target reset */
	.eh_host_reset_handler  = qedf_eh_host_reset,
	.slave_configure	= qedf_slave_configure,
	.dma_boundary = QED_HW_DMA_BOUNDARY,
	.sg_tablesize = QEDF_MAX_BDS_PER_CMD,
	.can_queue = FCOE_PARAMS_NUM_TASKS,
	.change_queue_depth = scsi_change_queue_depth,
पूर्ण;

अटल पूर्णांक qedf_get_paged_crc_eof(काष्ठा sk_buff *skb, पूर्णांक tlen)
अणु
	पूर्णांक rc;

	spin_lock(&qedf_global_lock);
	rc = fcoe_get_paged_crc_eof(skb, tlen, &qedf_global);
	spin_unlock(&qedf_global_lock);

	वापस rc;
पूर्ण

अटल काष्ठा qedf_rport *qedf_fcport_lookup(काष्ठा qedf_ctx *qedf, u32 port_id)
अणु
	काष्ठा qedf_rport *fcport;
	काष्ठा fc_rport_priv *rdata;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(fcport, &qedf->fcports, peers) अणु
		rdata = fcport->rdata;
		अगर (rdata == शून्य)
			जारी;
		अगर (rdata->ids.port_id == port_id) अणु
			rcu_पढ़ो_unlock();
			वापस fcport;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	/* Return शून्य to caller to let them know fcport was not found */
	वापस शून्य;
पूर्ण

/* Transmits an ELS frame over an offloaded session */
अटल पूर्णांक qedf_xmit_l2_frame(काष्ठा qedf_rport *fcport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_frame_header *fh;
	पूर्णांक rc = 0;

	fh = fc_frame_header_get(fp);
	अगर ((fh->fh_type == FC_TYPE_ELS) &&
	    (fh->fh_r_ctl == FC_RCTL_ELS_REQ)) अणु
		चयन (fc_frame_payload_op(fp)) अणु
		हाल ELS_ADISC:
			qedf_send_adisc(fcport, fp);
			rc = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

/*
 * qedf_xmit - qedf FCoE frame transmit function
 */
अटल पूर्णांक qedf_xmit(काष्ठा fc_lport *lport, काष्ठा fc_frame *fp)
अणु
	काष्ठा fc_lport		*base_lport;
	काष्ठा qedf_ctx		*qedf;
	काष्ठा ethhdr		*eh;
	काष्ठा fcoe_crc_eof	*cp;
	काष्ठा sk_buff		*skb;
	काष्ठा fc_frame_header	*fh;
	काष्ठा fcoe_hdr		*hp;
	u8			sof, eof;
	u32			crc;
	अचिन्हित पूर्णांक		hlen, tlen, elen;
	पूर्णांक			wlen;
	काष्ठा fc_stats		*stats;
	काष्ठा fc_lport *पंचांगp_lport;
	काष्ठा fc_lport *vn_port = शून्य;
	काष्ठा qedf_rport *fcport;
	पूर्णांक rc;
	u16 vlan_tci = 0;

	qedf = (काष्ठा qedf_ctx *)lport_priv(lport);

	fh = fc_frame_header_get(fp);
	skb = fp_skb(fp);

	/* Filter out traffic to other NPIV ports on the same host */
	अगर (lport->vport)
		base_lport = shost_priv(vport_to_shost(lport->vport));
	अन्यथा
		base_lport = lport;

	/* Flag अगर the destination is the base port */
	अगर (base_lport->port_id == ntoh24(fh->fh_d_id)) अणु
		vn_port = base_lport;
	पूर्ण अन्यथा अणु
		/* Got through the list of vports attached to the base_lport
		 * and see अगर we have a match with the destination address.
		 */
		list_क्रम_each_entry(पंचांगp_lport, &base_lport->vports, list) अणु
			अगर (पंचांगp_lport->port_id == ntoh24(fh->fh_d_id)) अणु
				vn_port = पंचांगp_lport;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (vn_port && ntoh24(fh->fh_d_id) != FC_FID_FLOGI) अणु
		काष्ठा fc_rport_priv *rdata = शून्य;

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2,
		    "Dropping FCoE frame to %06x.\n", ntoh24(fh->fh_d_id));
		kमुक्त_skb(skb);
		rdata = fc_rport_lookup(lport, ntoh24(fh->fh_d_id));
		अगर (rdata) अणु
			rdata->retries = lport->max_rport_retry_count;
			kref_put(&rdata->kref, fc_rport_destroy);
		पूर्ण
		वापस -EINVAL;
	पूर्ण
	/* End NPIV filtering */

	अगर (!qedf->ctlr.sel_fcf) अणु
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (!test_bit(QEDF_LL2_STARTED, &qedf->flags)) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "LL2 not started\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (atomic_पढ़ो(&qedf->link_state) != QEDF_LINK_UP) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "qedf link down\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	अगर (unlikely(fh->fh_r_ctl == FC_RCTL_ELS_REQ)) अणु
		अगर (fcoe_ctlr_els_send(&qedf->ctlr, lport, skb))
			वापस 0;
	पूर्ण

	/* Check to see अगर this needs to be sent on an offloaded session */
	fcport = qedf_fcport_lookup(qedf, ntoh24(fh->fh_d_id));

	अगर (fcport && test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		rc = qedf_xmit_l2_frame(fcport, fp);
		/*
		 * If the frame was successfully sent over the middle path
		 * then करो not try to also send it over the LL2 path
		 */
		अगर (rc)
			वापस 0;
	पूर्ण

	sof = fr_sof(fp);
	eof = fr_eof(fp);

	elen = माप(काष्ठा ethhdr);
	hlen = माप(काष्ठा fcoe_hdr);
	tlen = माप(काष्ठा fcoe_crc_eof);
	wlen = (skb->len - tlen + माप(crc)) / FCOE_WORD_TO_BYTE;

	skb->ip_summed = CHECKSUM_NONE;
	crc = fcoe_fc_crc(fp);

	/* copy port crc and eof to the skb buff */
	अगर (skb_is_nonlinear(skb)) अणु
		skb_frag_t *frag;

		अगर (qedf_get_paged_crc_eof(skb, tlen)) अणु
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

	/*
	 * Add VLAN tag to non-offload FCoE frame based on current stored VLAN
	 * क्रम FIP/FCoE traffic.
	 */
	__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), qedf->vlan_id);

	/* fill up mac and fcoe headers */
	eh = eth_hdr(skb);
	eh->h_proto = htons(ETH_P_FCOE);
	अगर (qedf->ctlr.map_dest)
		fc_fcoe_set_mac(eh->h_dest, fh->fh_d_id);
	अन्यथा
		/* insert GW address */
		ether_addr_copy(eh->h_dest, qedf->ctlr.dest_addr);

	/* Set the source MAC address */
	ether_addr_copy(eh->h_source, qedf->data_src_addr);

	hp = (काष्ठा fcoe_hdr *)(eh + 1);
	स_रखो(hp, 0, माप(*hp));
	अगर (FC_FCOE_VER)
		FC_FCOE_ENCAPS_VER(hp, FC_FCOE_VER);
	hp->fcoe_sof = sof;

	/*update tx stats */
	stats = per_cpu_ptr(lport->stats, get_cpu());
	stats->TxFrames++;
	stats->TxWords += wlen;
	put_cpu();

	/* Get VLAN ID from skb क्रम prपूर्णांकing purposes */
	__vlan_hwaccel_get_tag(skb, &vlan_tci);

	/* send करोwn to lld */
	fr_dev(fp) = lport;
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2, "FCoE frame send: "
	    "src=%06x dest=%06x r_ctl=%x type=%x vlan=%04x.\n",
	    ntoh24(fh->fh_s_id), ntoh24(fh->fh_d_id), fh->fh_r_ctl, fh->fh_type,
	    vlan_tci);
	अगर (qedf_dump_frames)
		prपूर्णांक_hex_dump(KERN_WARNING, "fcoe: ", DUMP_PREFIX_OFFSET, 16,
		    1, skb->data, skb->len, false);
	rc = qed_ops->ll2->start_xmit(qedf->cdev, skb, 0);
	अगर (rc) अणु
		QEDF_ERR(&qedf->dbg_ctx, "start_xmit failed rc = %d.\n", rc);
		kमुक्त_skb(skb);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedf_alloc_sq(काष्ठा qedf_ctx *qedf, काष्ठा qedf_rport *fcport)
अणु
	पूर्णांक rval = 0;
	u32 *pbl;
	dma_addr_t page;
	पूर्णांक num_pages;

	/* Calculate appropriate queue and PBL sizes */
	fcport->sq_mem_size = SQ_NUM_ENTRIES * माप(काष्ठा fcoe_wqe);
	fcport->sq_mem_size = ALIGN(fcport->sq_mem_size, QEDF_PAGE_SIZE);
	fcport->sq_pbl_size = (fcport->sq_mem_size / QEDF_PAGE_SIZE) *
	    माप(व्योम *);
	fcport->sq_pbl_size = fcport->sq_pbl_size + QEDF_PAGE_SIZE;

	fcport->sq = dma_alloc_coherent(&qedf->pdev->dev, fcport->sq_mem_size,
					&fcport->sq_dma, GFP_KERNEL);
	अगर (!fcport->sq) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate send queue.\n");
		rval = 1;
		जाओ out;
	पूर्ण

	fcport->sq_pbl = dma_alloc_coherent(&qedf->pdev->dev,
					    fcport->sq_pbl_size,
					    &fcport->sq_pbl_dma, GFP_KERNEL);
	अगर (!fcport->sq_pbl) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate send queue PBL.\n");
		rval = 1;
		जाओ out_मुक्त_sq;
	पूर्ण

	/* Create PBL */
	num_pages = fcport->sq_mem_size / QEDF_PAGE_SIZE;
	page = fcport->sq_dma;
	pbl = (u32 *)fcport->sq_pbl;

	जबतक (num_pages--) अणु
		*pbl = U64_LO(page);
		pbl++;
		*pbl = U64_HI(page);
		pbl++;
		page += QEDF_PAGE_SIZE;
	पूर्ण

	वापस rval;

out_मुक्त_sq:
	dma_मुक्त_coherent(&qedf->pdev->dev, fcport->sq_mem_size, fcport->sq,
	    fcport->sq_dma);
out:
	वापस rval;
पूर्ण

अटल व्योम qedf_मुक्त_sq(काष्ठा qedf_ctx *qedf, काष्ठा qedf_rport *fcport)
अणु
	अगर (fcport->sq_pbl)
		dma_मुक्त_coherent(&qedf->pdev->dev, fcport->sq_pbl_size,
		    fcport->sq_pbl, fcport->sq_pbl_dma);
	अगर (fcport->sq)
		dma_मुक्त_coherent(&qedf->pdev->dev, fcport->sq_mem_size,
		    fcport->sq, fcport->sq_dma);
पूर्ण

अटल पूर्णांक qedf_offload_connection(काष्ठा qedf_ctx *qedf,
	काष्ठा qedf_rport *fcport)
अणु
	काष्ठा qed_fcoe_params_offload conn_info;
	u32 port_id;
	पूर्णांक rval;
	uपूर्णांक16_t total_sqe = (fcport->sq_mem_size / माप(काष्ठा fcoe_wqe));

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_CONN, "Offloading connection "
		   "portid=%06x.\n", fcport->rdata->ids.port_id);
	rval = qed_ops->acquire_conn(qedf->cdev, &fcport->handle,
	    &fcport->fw_cid, &fcport->p_करोorbell);
	अगर (rval) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Could not acquire connection "
			   "for portid=%06x.\n", fcport->rdata->ids.port_id);
		rval = 1; /* For some reason qed वापसs 0 on failure here */
		जाओ out;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_CONN, "portid=%06x "
		   "fw_cid=%08x handle=%d.\n", fcport->rdata->ids.port_id,
		   fcport->fw_cid, fcport->handle);

	स_रखो(&conn_info, 0, माप(काष्ठा qed_fcoe_params_offload));

	/* Fill in the offload connection info */
	conn_info.sq_pbl_addr = fcport->sq_pbl_dma;

	conn_info.sq_curr_page_addr = (dma_addr_t)(*(u64 *)fcport->sq_pbl);
	conn_info.sq_next_page_addr =
	    (dma_addr_t)(*(u64 *)(fcport->sq_pbl + 8));

	/* Need to use our FCoE MAC क्रम the offload session */
	ether_addr_copy(conn_info.src_mac, qedf->data_src_addr);

	ether_addr_copy(conn_info.dst_mac, qedf->ctlr.dest_addr);

	conn_info.tx_max_fc_pay_len = fcport->rdata->maxframe_size;
	conn_info.e_d_tov_समयr_val = qedf->lport->e_d_tov;
	conn_info.rec_tov_समयr_val = 3; /* I think this is what E3 was */
	conn_info.rx_max_fc_pay_len = fcport->rdata->maxframe_size;

	/* Set VLAN data */
	conn_info.vlan_tag = qedf->vlan_id <<
	    FCOE_CONN_OFFLOAD_RAMROD_DATA_VLAN_ID_SHIFT;
	conn_info.vlan_tag |=
	    qedf->prio << FCOE_CONN_OFFLOAD_RAMROD_DATA_PRIORITY_SHIFT;
	conn_info.flags |= (FCOE_CONN_OFFLOAD_RAMROD_DATA_B_VLAN_FLAG_MASK <<
	    FCOE_CONN_OFFLOAD_RAMROD_DATA_B_VLAN_FLAG_SHIFT);

	/* Set host port source id */
	port_id = fc_host_port_id(qedf->lport->host);
	fcport->sid = port_id;
	conn_info.s_id.addr_hi = (port_id & 0x000000FF);
	conn_info.s_id.addr_mid = (port_id & 0x0000FF00) >> 8;
	conn_info.s_id.addr_lo = (port_id & 0x00FF0000) >> 16;

	conn_info.max_conc_seqs_c3 = fcport->rdata->max_seq;

	/* Set remote port destination id */
	port_id = fcport->rdata->rport->port_id;
	conn_info.d_id.addr_hi = (port_id & 0x000000FF);
	conn_info.d_id.addr_mid = (port_id & 0x0000FF00) >> 8;
	conn_info.d_id.addr_lo = (port_id & 0x00FF0000) >> 16;

	conn_info.def_q_idx = 0; /* Default index क्रम send queue? */

	/* Set FC-TAPE specअगरic flags अगर needed */
	अगर (fcport->dev_type == QEDF_RPORT_TYPE_TAPE) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_CONN,
		    "Enable CONF, REC for portid=%06x.\n",
		    fcport->rdata->ids.port_id);
		conn_info.flags |= 1 <<
		    FCOE_CONN_OFFLOAD_RAMROD_DATA_B_CONF_REQ_SHIFT;
		conn_info.flags |=
		    ((fcport->rdata->sp_features & FC_SP_FT_SEQC) ? 1 : 0) <<
		    FCOE_CONN_OFFLOAD_RAMROD_DATA_B_REC_VALID_SHIFT;
	पूर्ण

	rval = qed_ops->offload_conn(qedf->cdev, fcport->handle, &conn_info);
	अगर (rval) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Could not offload connection "
			   "for portid=%06x.\n", fcport->rdata->ids.port_id);
		जाओ out_मुक्त_conn;
	पूर्ण अन्यथा
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_CONN, "Offload "
			   "succeeded portid=%06x total_sqe=%d.\n",
			   fcport->rdata->ids.port_id, total_sqe);

	spin_lock_init(&fcport->rport_lock);
	atomic_set(&fcport->मुक्त_sqes, total_sqe);
	वापस 0;
out_मुक्त_conn:
	qed_ops->release_conn(qedf->cdev, fcport->handle);
out:
	वापस rval;
पूर्ण

#घोषणा QEDF_TERM_BUFF_SIZE		10
अटल व्योम qedf_upload_connection(काष्ठा qedf_ctx *qedf,
	काष्ठा qedf_rport *fcport)
अणु
	व्योम *term_params;
	dma_addr_t term_params_dma;

	/* Term params needs to be a DMA coherent buffer as qed shared the
	 * physical DMA address with the firmware. The buffer may be used in
	 * the receive path so we may eventually have to move this.
	 */
	term_params = dma_alloc_coherent(&qedf->pdev->dev, QEDF_TERM_BUFF_SIZE,
		&term_params_dma, GFP_KERNEL);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_CONN, "Uploading connection "
		   "port_id=%06x.\n", fcport->rdata->ids.port_id);

	qed_ops->destroy_conn(qedf->cdev, fcport->handle, term_params_dma);
	qed_ops->release_conn(qedf->cdev, fcport->handle);

	dma_मुक्त_coherent(&qedf->pdev->dev, QEDF_TERM_BUFF_SIZE, term_params,
	    term_params_dma);
पूर्ण

अटल व्योम qedf_cleanup_fcport(काष्ठा qedf_ctx *qedf,
	काष्ठा qedf_rport *fcport)
अणु
	काष्ठा fc_rport_priv *rdata = fcport->rdata;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_CONN, "Cleaning up portid=%06x.\n",
	    fcport->rdata->ids.port_id);

	/* Flush any reमुख्यing i/o's beक्रमe we upload the connection */
	qedf_flush_active_ios(fcport, -1);

	अगर (test_and_clear_bit(QEDF_RPORT_SESSION_READY, &fcport->flags))
		qedf_upload_connection(qedf, fcport);
	qedf_मुक्त_sq(qedf, fcport);
	fcport->rdata = शून्य;
	fcport->qedf = शून्य;
	kref_put(&rdata->kref, fc_rport_destroy);
पूर्ण

/*
 * This event_callback is called after successful completion of libfc
 * initiated target login. qedf can proceed with initiating the session
 * establishment.
 */
अटल व्योम qedf_rport_event_handler(काष्ठा fc_lport *lport,
				काष्ठा fc_rport_priv *rdata,
				क्रमागत fc_rport_event event)
अणु
	काष्ठा qedf_ctx *qedf = lport_priv(lport);
	काष्ठा fc_rport *rport = rdata->rport;
	काष्ठा fc_rport_libfc_priv *rp;
	काष्ठा qedf_rport *fcport;
	u32 port_id;
	पूर्णांक rval;
	अचिन्हित दीर्घ flags;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "event = %d, "
		   "port_id = 0x%x\n", event, rdata->ids.port_id);

	चयन (event) अणु
	हाल RPORT_EV_READY:
		अगर (!rport) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "rport is NULL.\n");
			अवरोध;
		पूर्ण

		rp = rport->dd_data;
		fcport = (काष्ठा qedf_rport *)&rp[1];
		fcport->qedf = qedf;

		अगर (atomic_पढ़ो(&qedf->num_offloads) >= QEDF_MAX_SESSIONS) अणु
			QEDF_ERR(&(qedf->dbg_ctx), "Not offloading "
			    "portid=0x%x as max number of offloaded sessions "
			    "reached.\n", rdata->ids.port_id);
			वापस;
		पूर्ण

		/*
		 * Don't try to offload the session again. Can happen when we
		 * get an ADISC
		 */
		अगर (test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "Session already "
				   "offloaded, portid=0x%x.\n",
				   rdata->ids.port_id);
			वापस;
		पूर्ण

		अगर (rport->port_id == FC_FID_सूची_SERV) अणु
			/*
			 * qedf_rport काष्ठाure करोesn't exist क्रम
			 * directory server.
			 * We should not come here, as lport will
			 * take care of fabric login
			 */
			QEDF_WARN(&(qedf->dbg_ctx), "rport struct does not "
			    "exist for dir server port_id=%x\n",
			    rdata->ids.port_id);
			अवरोध;
		पूर्ण

		अगर (rdata->spp_type != FC_TYPE_FCP) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Not offloading since spp type isn't FCP\n");
			अवरोध;
		पूर्ण
		अगर (!(rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET)) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Not FCP target so not offloading\n");
			अवरोध;
		पूर्ण

		/* Initial reference held on entry, so this can't fail */
		kref_get(&rdata->kref);
		fcport->rdata = rdata;
		fcport->rport = rport;

		rval = qedf_alloc_sq(qedf, fcport);
		अगर (rval) अणु
			qedf_cleanup_fcport(qedf, fcport);
			अवरोध;
		पूर्ण

		/* Set device type */
		अगर (rdata->flags & FC_RP_FLAGS_RETRY &&
		    rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET &&
		    !(rdata->ids.roles & FC_RPORT_ROLE_FCP_INITIATOR)) अणु
			fcport->dev_type = QEDF_RPORT_TYPE_TAPE;
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "portid=%06x is a TAPE device.\n",
			    rdata->ids.port_id);
		पूर्ण अन्यथा अणु
			fcport->dev_type = QEDF_RPORT_TYPE_DISK;
		पूर्ण

		rval = qedf_offload_connection(qedf, fcport);
		अगर (rval) अणु
			qedf_cleanup_fcport(qedf, fcport);
			अवरोध;
		पूर्ण

		/* Add fcport to list of qedf_ctx list of offloaded ports */
		spin_lock_irqsave(&qedf->hba_lock, flags);
		list_add_rcu(&fcport->peers, &qedf->fcports);
		spin_unlock_irqrestore(&qedf->hba_lock, flags);

		/*
		 * Set the session पढ़ोy bit to let everyone know that this
		 * connection is पढ़ोy क्रम I/O
		 */
		set_bit(QEDF_RPORT_SESSION_READY, &fcport->flags);
		atomic_inc(&qedf->num_offloads);

		अवरोध;
	हाल RPORT_EV_LOGO:
	हाल RPORT_EV_FAILED:
	हाल RPORT_EV_STOP:
		port_id = rdata->ids.port_id;
		अगर (port_id == FC_FID_सूची_SERV)
			अवरोध;

		अगर (rdata->spp_type != FC_TYPE_FCP) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "No action since spp type isn't FCP\n");
			अवरोध;
		पूर्ण
		अगर (!(rdata->ids.roles & FC_RPORT_ROLE_FCP_TARGET)) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "Not FCP target so no action\n");
			अवरोध;
		पूर्ण

		अगर (!rport) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "port_id=%x - rport notcreated Yet!!\n", port_id);
			अवरोध;
		पूर्ण
		rp = rport->dd_data;
		/*
		 * Perक्रमm session upload. Note that rdata->peers is alपढ़ोy
		 * हटाओd from disc->rports list beक्रमe we get this event.
		 */
		fcport = (काष्ठा qedf_rport *)&rp[1];

		spin_lock_irqsave(&fcport->rport_lock, flags);
		/* Only मुक्त this fcport अगर it is offloaded alपढ़ोy */
		अगर (test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags) &&
		    !test_bit(QEDF_RPORT_UPLOADING_CONNECTION,
		    &fcport->flags)) अणु
			set_bit(QEDF_RPORT_UPLOADING_CONNECTION,
				&fcport->flags);
			spin_unlock_irqrestore(&fcport->rport_lock, flags);
			qedf_cleanup_fcport(qedf, fcport);
			/*
			 * Remove fcport to list of qedf_ctx list of offloaded
			 * ports
			 */
			spin_lock_irqsave(&qedf->hba_lock, flags);
			list_del_rcu(&fcport->peers);
			spin_unlock_irqrestore(&qedf->hba_lock, flags);

			clear_bit(QEDF_RPORT_UPLOADING_CONNECTION,
			    &fcport->flags);
			atomic_dec(&qedf->num_offloads);
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore(&fcport->rport_lock, flags);
		पूर्ण
		अवरोध;

	हाल RPORT_EV_NONE:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qedf_पात_io(काष्ठा fc_lport *lport)
अणु
	/* NO-OP but need to fill in the ढाँचा */
पूर्ण

अटल व्योम qedf_fcp_cleanup(काष्ठा fc_lport *lport)
अणु
	/*
	 * NO-OP but need to fill in ढाँचा to prevent a शून्य
	 * function poपूर्णांकer dereference during link करोwn. I/Os
	 * will be flushed when port is uploaded.
	 */
पूर्ण

अटल काष्ठा libfc_function_ढाँचा qedf_lport_ढाँचा = अणु
	.frame_send		= qedf_xmit,
	.fcp_पात_io		= qedf_पात_io,
	.fcp_cleanup		= qedf_fcp_cleanup,
	.rport_event_callback	= qedf_rport_event_handler,
	.elsct_send		= qedf_elsct_send,
पूर्ण;

अटल व्योम qedf_fcoe_ctlr_setup(काष्ठा qedf_ctx *qedf)
अणु
	fcoe_ctlr_init(&qedf->ctlr, FIP_MODE_AUTO);

	qedf->ctlr.send = qedf_fip_send;
	qedf->ctlr.get_src_addr = qedf_get_src_mac;
	ether_addr_copy(qedf->ctlr.ctl_src_addr, qedf->mac);
पूर्ण

अटल व्योम qedf_setup_fdmi(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा fc_lport *lport = qedf->lport;
	u8 buf[8];
	पूर्णांक pos;
	uपूर्णांक32_t i;

	/*
	 * fdmi_enabled needs to be set क्रम libfc
	 * to execute FDMI registration
	 */
	lport->fdmi_enabled = 1;

	/*
	 * Setup the necessary fc_host attributes to that will be used to fill
	 * in the FDMI inक्रमmation.
	 */

	/* Get the PCI-e Device Serial Number Capability */
	pos = pci_find_ext_capability(qedf->pdev, PCI_EXT_CAP_ID_DSN);
	अगर (pos) अणु
		pos += 4;
		क्रम (i = 0; i < 8; i++)
			pci_पढ़ो_config_byte(qedf->pdev, pos + i, &buf[i]);

		snम_लिखो(fc_host_serial_number(lport->host),
		    FC_SERIAL_NUMBER_SIZE,
		    "%02X%02X%02X%02X%02X%02X%02X%02X",
		    buf[7], buf[6], buf[5], buf[4],
		    buf[3], buf[2], buf[1], buf[0]);
	पूर्ण अन्यथा
		snम_लिखो(fc_host_serial_number(lport->host),
		    FC_SERIAL_NUMBER_SIZE, "Unknown");

	snम_लिखो(fc_host_manufacturer(lport->host),
	    FC_SERIAL_NUMBER_SIZE, "%s", "Marvell Semiconductor Inc.");

	अगर (qedf->pdev->device == QL45xxx) अणु
		snम_लिखो(fc_host_model(lport->host),
			FC_SYMBOLIC_NAME_SIZE, "%s", "QL45xxx");

		snम_लिखो(fc_host_model_description(lport->host),
			FC_SYMBOLIC_NAME_SIZE, "%s",
			"Marvell FastLinQ QL45xxx FCoE Adapter");
	पूर्ण

	अगर (qedf->pdev->device == QL41xxx) अणु
		snम_लिखो(fc_host_model(lport->host),
			FC_SYMBOLIC_NAME_SIZE, "%s", "QL41xxx");

		snम_लिखो(fc_host_model_description(lport->host),
			FC_SYMBOLIC_NAME_SIZE, "%s",
			"Marvell FastLinQ QL41xxx FCoE Adapter");
	पूर्ण

	snम_लिखो(fc_host_hardware_version(lport->host),
	    FC_VERSION_STRING_SIZE, "Rev %d", qedf->pdev->revision);

	snम_लिखो(fc_host_driver_version(lport->host),
	    FC_VERSION_STRING_SIZE, "%s", QEDF_VERSION);

	snम_लिखो(fc_host_firmware_version(lport->host),
	    FC_VERSION_STRING_SIZE, "%d.%d.%d.%d",
	    FW_MAJOR_VERSION, FW_MINOR_VERSION, FW_REVISION_VERSION,
	    FW_ENGINEERING_VERSION);

पूर्ण

अटल पूर्णांक qedf_lport_setup(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा fc_lport *lport = qedf->lport;

	lport->link_up = 0;
	lport->max_retry_count = QEDF_FLOGI_RETRY_CNT;
	lport->max_rport_retry_count = QEDF_RPORT_RETRY_CNT;
	lport->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
	    FCP_SPPF_RETRY | FCP_SPPF_CONF_COMPL);
	lport->boot_समय = jअगरfies;
	lport->e_d_tov = 2 * 1000;
	lport->r_a_tov = 10 * 1000;

	/* Set NPIV support */
	lport->करोes_npiv = 1;
	fc_host_max_npiv_vports(lport->host) = QEDF_MAX_NPIV;

	fc_set_wwnn(lport, qedf->wwnn);
	fc_set_wwpn(lport, qedf->wwpn);

	अगर (fcoe_libfc_config(lport, &qedf->ctlr, &qedf_lport_ढाँचा, 0)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "fcoe_libfc_config failed.\n");
		वापस -ENOMEM;
	पूर्ण

	/* Allocate the exchange manager */
	fc_exch_mgr_alloc(lport, FC_CLASS_3, FCOE_PARAMS_NUM_TASKS,
			  0xfffe, शून्य);

	अगर (fc_lport_init_stats(lport))
		वापस -ENOMEM;

	/* Finish lport config */
	fc_lport_config(lport);

	/* Set max frame size */
	fc_set_mfs(lport, QEDF_MFS);
	fc_host_maxframe_size(lport->host) = lport->mfs;

	/* Set शेष dev_loss_पंचांगo based on module parameter */
	fc_host_dev_loss_पंचांगo(lport->host) = qedf_dev_loss_पंचांगo;

	/* Set symbolic node name */
	अगर (qedf->pdev->device == QL45xxx)
		snम_लिखो(fc_host_symbolic_name(lport->host), 256,
			"Marvell FastLinQ 45xxx FCoE v%s", QEDF_VERSION);

	अगर (qedf->pdev->device == QL41xxx)
		snम_लिखो(fc_host_symbolic_name(lport->host), 256,
			"Marvell FastLinQ 41xxx FCoE v%s", QEDF_VERSION);

	qedf_setup_fdmi(qedf);

	वापस 0;
पूर्ण

/*
 * NPIV functions
 */

अटल पूर्णांक qedf_vport_libfc_config(काष्ठा fc_vport *vport,
	काष्ठा fc_lport *lport)
अणु
	lport->link_up = 0;
	lport->qfull = 0;
	lport->max_retry_count = QEDF_FLOGI_RETRY_CNT;
	lport->max_rport_retry_count = QEDF_RPORT_RETRY_CNT;
	lport->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
	    FCP_SPPF_RETRY | FCP_SPPF_CONF_COMPL);
	lport->boot_समय = jअगरfies;
	lport->e_d_tov = 2 * 1000;
	lport->r_a_tov = 10 * 1000;
	lport->करोes_npiv = 1; /* Temporary until we add NPIV support */

	/* Allocate stats क्रम vport */
	अगर (fc_lport_init_stats(lport))
		वापस -ENOMEM;

	/* Finish lport config */
	fc_lport_config(lport);

	/* offload related configuration */
	lport->crc_offload = 0;
	lport->seq_offload = 0;
	lport->lro_enabled = 0;
	lport->lro_xid = 0;
	lport->lso_max = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक qedf_vport_create(काष्ठा fc_vport *vport, bool disabled)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fc_lport *vn_port;
	काष्ठा qedf_ctx *base_qedf = lport_priv(n_port);
	काष्ठा qedf_ctx *vport_qedf;

	अक्षर buf[32];
	पूर्णांक rc = 0;

	rc = fcoe_validate_vport_create(vport);
	अगर (rc) अणु
		fcoe_wwn_to_str(vport->port_name, buf, माप(buf));
		QEDF_WARN(&(base_qedf->dbg_ctx), "Failed to create vport, "
			   "WWPN (0x%s) already exists.\n", buf);
		वापस rc;
	पूर्ण

	अगर (atomic_पढ़ो(&base_qedf->link_state) != QEDF_LINK_UP) अणु
		QEDF_WARN(&(base_qedf->dbg_ctx), "Cannot create vport "
			   "because link is not up.\n");
		वापस -EIO;
	पूर्ण

	vn_port = libfc_vport_create(vport, माप(काष्ठा qedf_ctx));
	अगर (!vn_port) अणु
		QEDF_WARN(&(base_qedf->dbg_ctx), "Could not create lport "
			   "for vport.\n");
		वापस -ENOMEM;
	पूर्ण

	fcoe_wwn_to_str(vport->port_name, buf, माप(buf));
	QEDF_ERR(&(base_qedf->dbg_ctx), "Creating NPIV port, WWPN=%s.\n",
	    buf);

	/* Copy some fields from base_qedf */
	vport_qedf = lport_priv(vn_port);
	स_नकल(vport_qedf, base_qedf, माप(काष्ठा qedf_ctx));

	/* Set qedf data specअगरic to this vport */
	vport_qedf->lport = vn_port;
	/* Use same hba_lock as base_qedf */
	vport_qedf->hba_lock = base_qedf->hba_lock;
	vport_qedf->pdev = base_qedf->pdev;
	vport_qedf->cmd_mgr = base_qedf->cmd_mgr;
	init_completion(&vport_qedf->flogi_compl);
	INIT_LIST_HEAD(&vport_qedf->fcports);

	rc = qedf_vport_libfc_config(vport, vn_port);
	अगर (rc) अणु
		QEDF_ERR(&(base_qedf->dbg_ctx), "Could not allocate memory "
		    "for lport stats.\n");
		जाओ err;
	पूर्ण

	fc_set_wwnn(vn_port, vport->node_name);
	fc_set_wwpn(vn_port, vport->port_name);
	vport_qedf->wwnn = vn_port->wwnn;
	vport_qedf->wwpn = vn_port->wwpn;

	vn_port->host->transportt = qedf_fc_vport_transport_ढाँचा;
	vn_port->host->can_queue = FCOE_PARAMS_NUM_TASKS;
	vn_port->host->max_lun = qedf_max_lun;
	vn_port->host->sg_tablesize = QEDF_MAX_BDS_PER_CMD;
	vn_port->host->max_cmd_len = QEDF_MAX_CDB_LEN;

	rc = scsi_add_host(vn_port->host, &vport->dev);
	अगर (rc) अणु
		QEDF_WARN(&base_qedf->dbg_ctx,
			  "Error adding Scsi_Host rc=0x%x.\n", rc);
		जाओ err;
	पूर्ण

	/* Set शेष dev_loss_पंचांगo based on module parameter */
	fc_host_dev_loss_पंचांगo(vn_port->host) = qedf_dev_loss_पंचांगo;

	/* Init libfc stuffs */
	स_नकल(&vn_port->tt, &qedf_lport_ढाँचा,
		माप(qedf_lport_ढाँचा));
	fc_exch_init(vn_port);
	fc_elsct_init(vn_port);
	fc_lport_init(vn_port);
	fc_disc_init(vn_port);
	fc_disc_config(vn_port, vn_port);


	/* Allocate the exchange manager */
	shost = vport_to_shost(vport);
	n_port = shost_priv(shost);
	fc_exch_mgr_list_clone(n_port, vn_port);

	/* Set max frame size */
	fc_set_mfs(vn_port, QEDF_MFS);

	fc_host_port_type(vn_port->host) = FC_PORTTYPE_UNKNOWN;

	अगर (disabled) अणु
		fc_vport_set_state(vport, FC_VPORT_DISABLED);
	पूर्ण अन्यथा अणु
		vn_port->boot_समय = jअगरfies;
		fc_fabric_login(vn_port);
		fc_vport_setlink(vn_port);
	पूर्ण

	QEDF_INFO(&(base_qedf->dbg_ctx), QEDF_LOG_NPIV, "vn_port=%p.\n",
		   vn_port);

	/* Set up debug context क्रम vport */
	vport_qedf->dbg_ctx.host_no = vn_port->host->host_no;
	vport_qedf->dbg_ctx.pdev = base_qedf->pdev;

	वापस 0;

err:
	scsi_host_put(vn_port->host);
	वापस rc;
पूर्ण

अटल पूर्णांक qedf_vport_destroy(काष्ठा fc_vport *vport)
अणु
	काष्ठा Scsi_Host *shost = vport_to_shost(vport);
	काष्ठा fc_lport *n_port = shost_priv(shost);
	काष्ठा fc_lport *vn_port = vport->dd_data;
	काष्ठा qedf_ctx *qedf = lport_priv(vn_port);

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL.\n");
		जाओ out;
	पूर्ण

	/* Set unloading bit on vport qedf_ctx to prevent more I/O */
	set_bit(QEDF_UNLOADING, &qedf->flags);

	mutex_lock(&n_port->lp_mutex);
	list_del(&vn_port->list);
	mutex_unlock(&n_port->lp_mutex);

	fc_fabric_logoff(vn_port);
	fc_lport_destroy(vn_port);

	/* Detach from scsi-ml */
	fc_हटाओ_host(vn_port->host);
	scsi_हटाओ_host(vn_port->host);

	/*
	 * Only try to release the exchange manager अगर the vn_port
	 * configuration is complete.
	 */
	अगर (vn_port->state == LPORT_ST_READY)
		fc_exch_mgr_मुक्त(vn_port);

	/* Free memory used by statistical counters */
	fc_lport_मुक्त_stats(vn_port);

	/* Release Scsi_Host */
	scsi_host_put(vn_port->host);

out:
	वापस 0;
पूर्ण

अटल पूर्णांक qedf_vport_disable(काष्ठा fc_vport *vport, bool disable)
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

/*
 * During removal we need to रुको क्रम all the vports associated with a port
 * to be destroyed so we aव्योम a race condition where libfc is still trying
 * to reap vports जबतक the driver हटाओ function has alपढ़ोy reaped the
 * driver contexts associated with the physical port.
 */
अटल व्योम qedf_रुको_क्रम_vport_destroy(काष्ठा qedf_ctx *qedf)
अणु
	काष्ठा fc_host_attrs *fc_host = shost_to_fc_host(qedf->lport->host);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_NPIV,
	    "Entered.\n");
	जबतक (fc_host->npiv_vports_inuse > 0) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_NPIV,
		    "Waiting for all vports to be reaped.\n");
		msleep(1000);
	पूर्ण
पूर्ण

/**
 * qedf_fcoe_reset - Resets the fcoe
 *
 * @shost: shost the reset is from
 *
 * Returns: always 0
 */
अटल पूर्णांक qedf_fcoe_reset(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);

	qedf_ctx_soft_reset(lport);
	वापस 0;
पूर्ण

अटल व्योम qedf_get_host_port_id(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा fc_lport *lport = shost_priv(shost);

	fc_host_port_id(shost) = lport->port_id;
पूर्ण

अटल काष्ठा fc_host_statistics *qedf_fc_get_host_stats(काष्ठा Scsi_Host
	*shost)
अणु
	काष्ठा fc_host_statistics *qedf_stats;
	काष्ठा fc_lport *lport = shost_priv(shost);
	काष्ठा qedf_ctx *qedf = lport_priv(lport);
	काष्ठा qed_fcoe_stats *fw_fcoe_stats;

	qedf_stats = fc_get_host_stats(shost);

	/* We करोn't collect offload stats क्रम specअगरic NPIV ports */
	अगर (lport->vport)
		जाओ out;

	fw_fcoe_stats = kदो_स्मृति(माप(काष्ठा qed_fcoe_stats), GFP_KERNEL);
	अगर (!fw_fcoe_stats) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate memory for "
		    "fw_fcoe_stats.\n");
		जाओ out;
	पूर्ण

	mutex_lock(&qedf->stats_mutex);

	/* Query firmware क्रम offload stats */
	qed_ops->get_stats(qedf->cdev, fw_fcoe_stats);

	/*
	 * The expectation is that we add our offload stats to the stats
	 * being मुख्यtained by libfc each समय the fc_get_host_status callback
	 * is invoked. The additions are not carried over क्रम each call to
	 * the fc_get_host_stats callback.
	 */
	qedf_stats->tx_frames += fw_fcoe_stats->fcoe_tx_data_pkt_cnt +
	    fw_fcoe_stats->fcoe_tx_xfer_pkt_cnt +
	    fw_fcoe_stats->fcoe_tx_other_pkt_cnt;
	qedf_stats->rx_frames += fw_fcoe_stats->fcoe_rx_data_pkt_cnt +
	    fw_fcoe_stats->fcoe_rx_xfer_pkt_cnt +
	    fw_fcoe_stats->fcoe_rx_other_pkt_cnt;
	qedf_stats->fcp_input_megabytes +=
	    करो_भाग(fw_fcoe_stats->fcoe_rx_byte_cnt, 1000000);
	qedf_stats->fcp_output_megabytes +=
	    करो_भाग(fw_fcoe_stats->fcoe_tx_byte_cnt, 1000000);
	qedf_stats->rx_words += fw_fcoe_stats->fcoe_rx_byte_cnt / 4;
	qedf_stats->tx_words += fw_fcoe_stats->fcoe_tx_byte_cnt / 4;
	qedf_stats->invalid_crc_count +=
	    fw_fcoe_stats->fcoe_silent_drop_pkt_crc_error_cnt;
	qedf_stats->dumped_frames =
	    fw_fcoe_stats->fcoe_silent_drop_total_pkt_cnt;
	qedf_stats->error_frames +=
	    fw_fcoe_stats->fcoe_silent_drop_total_pkt_cnt;
	qedf_stats->fcp_input_requests += qedf->input_requests;
	qedf_stats->fcp_output_requests += qedf->output_requests;
	qedf_stats->fcp_control_requests += qedf->control_requests;
	qedf_stats->fcp_packet_पातs += qedf->packet_पातs;
	qedf_stats->fcp_frame_alloc_failures += qedf->alloc_failures;

	mutex_unlock(&qedf->stats_mutex);
	kमुक्त(fw_fcoe_stats);
out:
	वापस qedf_stats;
पूर्ण

अटल काष्ठा fc_function_ढाँचा qedf_fc_transport_fn = अणु
	.show_host_node_name = 1,
	.show_host_port_name = 1,
	.show_host_supported_classes = 1,
	.show_host_supported_fc4s = 1,
	.show_host_active_fc4s = 1,
	.show_host_maxframe_size = 1,

	.get_host_port_id = qedf_get_host_port_id,
	.show_host_port_id = 1,
	.show_host_supported_speeds = 1,
	.get_host_speed = fc_get_host_speed,
	.show_host_speed = 1,
	.show_host_port_type = 1,
	.get_host_port_state = fc_get_host_port_state,
	.show_host_port_state = 1,
	.show_host_symbolic_name = 1,

	/*
	 * Tell FC transport to allocate enough space to store the backpoपूर्णांकer
	 * क्रम the associate qedf_rport काष्ठा.
	 */
	.dd_fcrport_size = (माप(काष्ठा fc_rport_libfc_priv) +
				माप(काष्ठा qedf_rport)),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,
	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = fc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.get_fc_host_stats = qedf_fc_get_host_stats,
	.issue_fc_host_lip = qedf_fcoe_reset,
	.vport_create = qedf_vport_create,
	.vport_delete = qedf_vport_destroy,
	.vport_disable = qedf_vport_disable,
	.bsg_request = fc_lport_bsg_request,
पूर्ण;

अटल काष्ठा fc_function_ढाँचा qedf_fc_vport_transport_fn = अणु
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
				माप(काष्ठा qedf_rport)),
	.show_rport_maxframe_size = 1,
	.show_rport_supported_classes = 1,
	.show_host_fabric_name = 1,
	.show_starget_node_name = 1,
	.show_starget_port_name = 1,
	.show_starget_port_id = 1,
	.set_rport_dev_loss_पंचांगo = fc_set_rport_loss_पंचांगo,
	.show_rport_dev_loss_पंचांगo = 1,
	.get_fc_host_stats = fc_get_host_stats,
	.issue_fc_host_lip = qedf_fcoe_reset,
	.bsg_request = fc_lport_bsg_request,
पूर्ण;

अटल bool qedf_fp_has_work(काष्ठा qedf_fastpath *fp)
अणु
	काष्ठा qedf_ctx *qedf = fp->qedf;
	काष्ठा global_queue *que;
	काष्ठा qed_sb_info *sb_info = fp->sb_info;
	काष्ठा status_block_e4 *sb = sb_info->sb_virt;
	u16 prod_idx;

	/* Get the poपूर्णांकer to the global CQ this completion is on */
	que = qedf->global_queues[fp->sb_id];

	/* Be sure all responses have been written to PI */
	rmb();

	/* Get the current firmware producer index */
	prod_idx = sb->pi_array[QEDF_FCOE_PARAMS_GL_RQ_PI];

	वापस (que->cq_prod_idx != prod_idx);
पूर्ण

/*
 * Interrupt handler code.
 */

/* Process completion queue and copy CQE contents क्रम deferred processesing
 *
 * Return true अगर we should wake the I/O thपढ़ो, false अगर not.
 */
अटल bool qedf_process_completions(काष्ठा qedf_fastpath *fp)
अणु
	काष्ठा qedf_ctx *qedf = fp->qedf;
	काष्ठा qed_sb_info *sb_info = fp->sb_info;
	काष्ठा status_block_e4 *sb = sb_info->sb_virt;
	काष्ठा global_queue *que;
	u16 prod_idx;
	काष्ठा fcoe_cqe *cqe;
	काष्ठा qedf_io_work *io_work;
	पूर्णांक num_handled = 0;
	अचिन्हित पूर्णांक cpu;
	काष्ठा qedf_ioreq *io_req = शून्य;
	u16 xid;
	u16 new_cqes;
	u32 comp_type;

	/* Get the current firmware producer index */
	prod_idx = sb->pi_array[QEDF_FCOE_PARAMS_GL_RQ_PI];

	/* Get the poपूर्णांकer to the global CQ this completion is on */
	que = qedf->global_queues[fp->sb_id];

	/* Calculate the amount of new elements since last processing */
	new_cqes = (prod_idx >= que->cq_prod_idx) ?
	    (prod_idx - que->cq_prod_idx) :
	    0x10000 - que->cq_prod_idx + prod_idx;

	/* Save producer index */
	que->cq_prod_idx = prod_idx;

	जबतक (new_cqes) अणु
		fp->completions++;
		num_handled++;
		cqe = &que->cq[que->cq_cons_idx];

		comp_type = (cqe->cqe_data >> FCOE_CQE_CQE_TYPE_SHIFT) &
		    FCOE_CQE_CQE_TYPE_MASK;

		/*
		 * Process unsolicited CQEs directly in the पूर्णांकerrupt handler
		 * sine we need the fastpath ID
		 */
		अगर (comp_type == FCOE_UNSOLIC_CQE_TYPE) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_UNSOL,
			   "Unsolicated CQE.\n");
			qedf_process_unsol_compl(qedf, fp->sb_id, cqe);
			/*
			 * Don't add a work list item.  Increment consumer
			 * consumer index and move on.
			 */
			जाओ inc_idx;
		पूर्ण

		xid = cqe->cqe_data & FCOE_CQE_TASK_ID_MASK;
		io_req = &qedf->cmd_mgr->cmds[xid];

		/*
		 * Figure out which percpu thपढ़ो we should queue this I/O
		 * on.
		 */
		अगर (!io_req)
			/* If there is not io_req assocated with this CQE
			 * just queue it on CPU 0
			 */
			cpu = 0;
		अन्यथा अणु
			cpu = io_req->cpu;
			io_req->पूर्णांक_cpu = smp_processor_id();
		पूर्ण

		io_work = mempool_alloc(qedf->io_mempool, GFP_ATOMIC);
		अगर (!io_work) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate "
				   "work for I/O completion.\n");
			जारी;
		पूर्ण
		स_रखो(io_work, 0, माप(काष्ठा qedf_io_work));

		INIT_WORK(&io_work->work, qedf_fp_io_handler);

		/* Copy contents of CQE क्रम deferred processing */
		स_नकल(&io_work->cqe, cqe, माप(काष्ठा fcoe_cqe));

		io_work->qedf = fp->qedf;
		io_work->fp = शून्य; /* Only used क्रम unsolicited frames */

		queue_work_on(cpu, qedf_io_wq, &io_work->work);

inc_idx:
		que->cq_cons_idx++;
		अगर (que->cq_cons_idx == fp->cq_num_entries)
			que->cq_cons_idx = 0;
		new_cqes--;
	पूर्ण

	वापस true;
पूर्ण


/* MSI-X fastpath handler code */
अटल irqवापस_t qedf_msix_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qedf_fastpath *fp = dev_id;

	अगर (!fp) अणु
		QEDF_ERR(शून्य, "fp is null.\n");
		वापस IRQ_HANDLED;
	पूर्ण
	अगर (!fp->sb_info) अणु
		QEDF_ERR(शून्य, "fp->sb_info in null.");
		वापस IRQ_HANDLED;
	पूर्ण

	/*
	 * Disable पूर्णांकerrupts क्रम this status block जबतक we process new
	 * completions
	 */
	qed_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0 /*करो not update*/);

	जबतक (1) अणु
		qedf_process_completions(fp);

		अगर (qedf_fp_has_work(fp) == 0) अणु
			/* Update the sb inक्रमmation */
			qed_sb_update_sb_idx(fp->sb_info);

			/* Check क्रम more work */
			rmb();

			अगर (qedf_fp_has_work(fp) == 0) अणु
				/* Re-enable पूर्णांकerrupts */
				qed_sb_ack(fp->sb_info, IGU_INT_ENABLE, 1);
				वापस IRQ_HANDLED;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Do we ever want to अवरोध out of above loop? */
	वापस IRQ_HANDLED;
पूर्ण

/* simd handler क्रम MSI/INTa */
अटल व्योम qedf_simd_पूर्णांक_handler(व्योम *cookie)
अणु
	/* Cookie is qedf_ctx काष्ठा */
	काष्ठा qedf_ctx *qedf = (काष्ठा qedf_ctx *)cookie;

	QEDF_WARN(&(qedf->dbg_ctx), "qedf=%p.\n", qedf);
पूर्ण

#घोषणा QEDF_SIMD_HANDLER_NUM		0
अटल व्योम qedf_sync_मुक्त_irqs(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक i;
	u16 vector_idx = 0;
	u32 vector;

	अगर (qedf->पूर्णांक_info.msix_cnt) अणु
		क्रम (i = 0; i < qedf->पूर्णांक_info.used_cnt; i++) अणु
			vector_idx = i * qedf->dev_info.common.num_hwfns +
				qed_ops->common->get_affin_hwfn_idx(qedf->cdev);
			QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
				  "Freeing IRQ #%d vector_idx=%d.\n",
				  i, vector_idx);
			vector = qedf->पूर्णांक_info.msix[vector_idx].vector;
			synchronize_irq(vector);
			irq_set_affinity_hपूर्णांक(vector, शून्य);
			irq_set_affinity_notअगरier(vector, शून्य);
			मुक्त_irq(vector, &qedf->fp_array[i]);
		पूर्ण
	पूर्ण अन्यथा
		qed_ops->common->simd_handler_clean(qedf->cdev,
		    QEDF_SIMD_HANDLER_NUM);

	qedf->पूर्णांक_info.used_cnt = 0;
	qed_ops->common->set_fp_पूर्णांक(qedf->cdev, 0);
पूर्ण

अटल पूर्णांक qedf_request_msix_irq(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक i, rc, cpu;
	u16 vector_idx = 0;
	u32 vector;

	cpu = cpumask_first(cpu_online_mask);
	क्रम (i = 0; i < qedf->num_queues; i++) अणु
		vector_idx = i * qedf->dev_info.common.num_hwfns +
			qed_ops->common->get_affin_hwfn_idx(qedf->cdev);
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
			  "Requesting IRQ #%d vector_idx=%d.\n",
			  i, vector_idx);
		vector = qedf->पूर्णांक_info.msix[vector_idx].vector;
		rc = request_irq(vector, qedf_msix_handler, 0, "qedf",
				 &qedf->fp_array[i]);

		अगर (rc) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "request_irq failed.\n");
			qedf_sync_मुक्त_irqs(qedf);
			वापस rc;
		पूर्ण

		qedf->पूर्णांक_info.used_cnt++;
		rc = irq_set_affinity_hपूर्णांक(vector, get_cpu_mask(cpu));
		cpu = cpumask_next(cpu, cpu_online_mask);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedf_setup_पूर्णांक(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक rc = 0;

	/*
	 * Learn पूर्णांकerrupt configuration
	 */
	rc = qed_ops->common->set_fp_पूर्णांक(qedf->cdev, num_online_cpus());
	अगर (rc <= 0)
		वापस 0;

	rc  = qed_ops->common->get_fp_पूर्णांक(qedf->cdev, &qedf->पूर्णांक_info);
	अगर (rc)
		वापस 0;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Number of msix_cnt = "
		   "0x%x num of cpus = 0x%x\n", qedf->पूर्णांक_info.msix_cnt,
		   num_online_cpus());

	अगर (qedf->पूर्णांक_info.msix_cnt)
		वापस qedf_request_msix_irq(qedf);

	qed_ops->common->simd_handler_config(qedf->cdev, &qedf,
	    QEDF_SIMD_HANDLER_NUM, qedf_simd_पूर्णांक_handler);
	qedf->पूर्णांक_info.used_cnt = 1;

	QEDF_ERR(&qedf->dbg_ctx,
		 "Cannot load driver due to a lack of MSI-X vectors.\n");
	वापस -EINVAL;
पूर्ण

/* Main function क्रम libfc frame reception */
अटल व्योम qedf_recv_frame(काष्ठा qedf_ctx *qedf,
	काष्ठा sk_buff *skb)
अणु
	u32 fr_len;
	काष्ठा fc_lport *lport;
	काष्ठा fc_frame_header *fh;
	काष्ठा fcoe_crc_eof crc_eof;
	काष्ठा fc_frame *fp;
	u8 *mac = शून्य;
	u8 *dest_mac = शून्य;
	काष्ठा fcoe_hdr *hp;
	काष्ठा qedf_rport *fcport;
	काष्ठा fc_lport *vn_port;
	u32 f_ctl;

	lport = qedf->lport;
	अगर (lport == शून्य || lport->state == LPORT_ST_DISABLED) अणु
		QEDF_WARN(शून्य, "Invalid lport struct or lport disabled.\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (skb_is_nonlinear(skb))
		skb_linearize(skb);
	mac = eth_hdr(skb)->h_source;
	dest_mac = eth_hdr(skb)->h_dest;

	/* Pull the header */
	hp = (काष्ठा fcoe_hdr *)skb->data;
	fh = (काष्ठा fc_frame_header *) skb_transport_header(skb);
	skb_pull(skb, माप(काष्ठा fcoe_hdr));
	fr_len = skb->len - माप(काष्ठा fcoe_crc_eof);

	fp = (काष्ठा fc_frame *)skb;
	fc_frame_init(fp);
	fr_dev(fp) = lport;
	fr_sof(fp) = hp->fcoe_sof;
	अगर (skb_copy_bits(skb, fr_len, &crc_eof, माप(crc_eof))) अणु
		QEDF_INFO(शून्य, QEDF_LOG_LL2, "skb_copy_bits failed.\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण
	fr_eof(fp) = crc_eof.fcoe_eof;
	fr_crc(fp) = crc_eof.fcoe_crc32;
	अगर (pskb_trim(skb, fr_len)) अणु
		QEDF_INFO(शून्य, QEDF_LOG_LL2, "pskb_trim failed.\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	fh = fc_frame_header_get(fp);

	/*
	 * Invalid frame filters.
	 */

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

	अगर (ntoh24(&dest_mac[3]) != ntoh24(fh->fh_d_id)) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2,
		    "FC frame d_id mismatch with MAC %pM.\n", dest_mac);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	अगर (qedf->ctlr.state) अणु
		अगर (!ether_addr_equal(mac, qedf->ctlr.dest_addr)) अणु
			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2,
			    "Wrong source address: mac:%pM dest_addr:%pM.\n",
			    mac, qedf->ctlr.dest_addr);
			kमुक्त_skb(skb);
			वापस;
		पूर्ण
	पूर्ण

	vn_port = fc_vport_id_lookup(lport, ntoh24(fh->fh_d_id));

	/*
	 * If the destination ID from the frame header करोes not match what we
	 * have on record क्रम lport and the search क्रम a NPIV port came up
	 * empty then this is not addressed to our port so simply drop it.
	 */
	अगर (lport->port_id != ntoh24(fh->fh_d_id) && !vn_port) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_LL2,
			  "Dropping frame due to destination mismatch: lport->port_id=0x%x fh->d_id=0x%x.\n",
			  lport->port_id, ntoh24(fh->fh_d_id));
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	f_ctl = ntoh24(fh->fh_f_ctl);
	अगर ((fh->fh_type == FC_TYPE_BLS) && (f_ctl & FC_FC_SEQ_CTX) &&
	    (f_ctl & FC_FC_EX_CTX)) अणु
		/* Drop incoming ABTS response that has both SEQ/EX CTX set */
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_LL2,
			  "Dropping ABTS response as both SEQ/EX CTX set.\n");
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/*
	 * If a connection is uploading, drop incoming FCoE frames as there
	 * is a small winकरोw where we could try to वापस a frame जबतक libfc
	 * is trying to clean things up.
	 */

	/* Get fcport associated with d_id अगर it exists */
	fcport = qedf_fcport_lookup(qedf, ntoh24(fh->fh_d_id));

	अगर (fcport && test_bit(QEDF_RPORT_UPLOADING_CONNECTION,
	    &fcport->flags)) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2,
		    "Connection uploading, dropping fp=%p.\n", fp);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_LL2, "FCoE frame receive: "
	    "skb=%p fp=%p src=%06x dest=%06x r_ctl=%x fh_type=%x.\n", skb, fp,
	    ntoh24(fh->fh_s_id), ntoh24(fh->fh_d_id), fh->fh_r_ctl,
	    fh->fh_type);
	अगर (qedf_dump_frames)
		prपूर्णांक_hex_dump(KERN_WARNING, "fcoe: ", DUMP_PREFIX_OFFSET, 16,
		    1, skb->data, skb->len, false);
	fc_exch_recv(lport, fp);
पूर्ण

अटल व्योम qedf_ll2_process_skb(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_skb_work *skb_work =
	    container_of(work, काष्ठा qedf_skb_work, work);
	काष्ठा qedf_ctx *qedf = skb_work->qedf;
	काष्ठा sk_buff *skb = skb_work->skb;
	काष्ठा ethhdr *eh;

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL\n");
		जाओ err_out;
	पूर्ण

	eh = (काष्ठा ethhdr *)skb->data;

	/* Unकरो VLAN encapsulation */
	अगर (eh->h_proto == htons(ETH_P_8021Q)) अणु
		स_हटाओ((u8 *)eh + VLAN_HLEN, eh, ETH_ALEN * 2);
		eh = skb_pull(skb, VLAN_HLEN);
		skb_reset_mac_header(skb);
	पूर्ण

	/*
	 * Process either a FIP frame or FCoE frame based on the
	 * protocol value.  If it's not either just drop the
	 * frame.
	 */
	अगर (eh->h_proto == htons(ETH_P_FIP)) अणु
		qedf_fip_recv(qedf, skb);
		जाओ out;
	पूर्ण अन्यथा अगर (eh->h_proto == htons(ETH_P_FCOE)) अणु
		__skb_pull(skb, ETH_HLEN);
		qedf_recv_frame(qedf, skb);
		जाओ out;
	पूर्ण अन्यथा
		जाओ err_out;

err_out:
	kमुक्त_skb(skb);
out:
	kमुक्त(skb_work);
	वापस;
पूर्ण

अटल पूर्णांक qedf_ll2_rx(व्योम *cookie, काष्ठा sk_buff *skb,
	u32 arg1, u32 arg2)
अणु
	काष्ठा qedf_ctx *qedf = (काष्ठा qedf_ctx *)cookie;
	काष्ठा qedf_skb_work *skb_work;

	अगर (atomic_पढ़ो(&qedf->link_state) == QEDF_LINK_DOWN) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_LL2,
			  "Dropping frame as link state is down.\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	skb_work = kzalloc(माप(काष्ठा qedf_skb_work), GFP_ATOMIC);
	अगर (!skb_work) अणु
		QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate skb_work so "
			   "dropping frame.\n");
		kमुक्त_skb(skb);
		वापस 0;
	पूर्ण

	INIT_WORK(&skb_work->work, qedf_ll2_process_skb);
	skb_work->skb = skb;
	skb_work->qedf = qedf;
	queue_work(qedf->ll2_recv_wq, &skb_work->work);

	वापस 0;
पूर्ण

अटल काष्ठा qed_ll2_cb_ops qedf_ll2_cb_ops = अणु
	.rx_cb = qedf_ll2_rx,
	.tx_cb = शून्य,
पूर्ण;

/* Main thपढ़ो to process I/O completions */
व्योम qedf_fp_io_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_io_work *io_work =
	    container_of(work, काष्ठा qedf_io_work, work);
	u32 comp_type;

	/*
	 * Deferred part of unsolicited CQE sends
	 * frame to libfc.
	 */
	comp_type = (io_work->cqe.cqe_data >>
	    FCOE_CQE_CQE_TYPE_SHIFT) &
	    FCOE_CQE_CQE_TYPE_MASK;
	अगर (comp_type == FCOE_UNSOLIC_CQE_TYPE &&
	    io_work->fp)
		fc_exch_recv(io_work->qedf->lport, io_work->fp);
	अन्यथा
		qedf_process_cqe(io_work->qedf, &io_work->cqe);

	kमुक्त(io_work);
पूर्ण

अटल पूर्णांक qedf_alloc_and_init_sb(काष्ठा qedf_ctx *qedf,
	काष्ठा qed_sb_info *sb_info, u16 sb_id)
अणु
	काष्ठा status_block_e4 *sb_virt;
	dma_addr_t sb_phys;
	पूर्णांक ret;

	sb_virt = dma_alloc_coherent(&qedf->pdev->dev,
	    माप(काष्ठा status_block_e4), &sb_phys, GFP_KERNEL);

	अगर (!sb_virt) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Status block allocation failed for id = %d.\n",
			 sb_id);
		वापस -ENOMEM;
	पूर्ण

	ret = qed_ops->common->sb_init(qedf->cdev, sb_info, sb_virt, sb_phys,
	    sb_id, QED_SB_TYPE_STORAGE);

	अगर (ret) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Status block initialization failed (0x%x) for id = %d.\n",
			 ret, sb_id);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम qedf_मुक्त_sb(काष्ठा qedf_ctx *qedf, काष्ठा qed_sb_info *sb_info)
अणु
	अगर (sb_info->sb_virt)
		dma_मुक्त_coherent(&qedf->pdev->dev, माप(*sb_info->sb_virt),
		    (व्योम *)sb_info->sb_virt, sb_info->sb_phys);
पूर्ण

अटल व्योम qedf_destroy_sb(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक id;
	काष्ठा qedf_fastpath *fp = शून्य;

	क्रम (id = 0; id < qedf->num_queues; id++) अणु
		fp = &(qedf->fp_array[id]);
		अगर (fp->sb_id == QEDF_SB_ID_शून्य)
			अवरोध;
		qedf_मुक्त_sb(qedf, fp->sb_info);
		kमुक्त(fp->sb_info);
	पूर्ण
	kमुक्त(qedf->fp_array);
पूर्ण

अटल पूर्णांक qedf_prepare_sb(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक id;
	काष्ठा qedf_fastpath *fp;
	पूर्णांक ret;

	qedf->fp_array =
	    kसुस्मृति(qedf->num_queues, माप(काष्ठा qedf_fastpath),
		GFP_KERNEL);

	अगर (!qedf->fp_array) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "fastpath array allocation "
			  "failed.\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (id = 0; id < qedf->num_queues; id++) अणु
		fp = &(qedf->fp_array[id]);
		fp->sb_id = QEDF_SB_ID_शून्य;
		fp->sb_info = kसुस्मृति(1, माप(*fp->sb_info), GFP_KERNEL);
		अगर (!fp->sb_info) अणु
			QEDF_ERR(&(qedf->dbg_ctx), "SB info struct "
				  "allocation failed.\n");
			जाओ err;
		पूर्ण
		ret = qedf_alloc_and_init_sb(qedf, fp->sb_info, id);
		अगर (ret) अणु
			QEDF_ERR(&(qedf->dbg_ctx), "SB allocation and "
				  "initialization failed.\n");
			जाओ err;
		पूर्ण
		fp->sb_id = id;
		fp->qedf = qedf;
		fp->cq_num_entries =
		    qedf->global_queues[id]->cq_mem_size /
		    माप(काष्ठा fcoe_cqe);
	पूर्ण
err:
	वापस 0;
पूर्ण

व्योम qedf_process_cqe(काष्ठा qedf_ctx *qedf, काष्ठा fcoe_cqe *cqe)
अणु
	u16 xid;
	काष्ठा qedf_ioreq *io_req;
	काष्ठा qedf_rport *fcport;
	u32 comp_type;

	comp_type = (cqe->cqe_data >> FCOE_CQE_CQE_TYPE_SHIFT) &
	    FCOE_CQE_CQE_TYPE_MASK;

	xid = cqe->cqe_data & FCOE_CQE_TASK_ID_MASK;
	io_req = &qedf->cmd_mgr->cmds[xid];

	/* Completion not क्रम a valid I/O anymore so just वापस */
	अगर (!io_req) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "io_req is NULL for xid=0x%x.\n", xid);
		वापस;
	पूर्ण

	fcport = io_req->fcport;

	अगर (fcport == शून्य) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "fcport is NULL for xid=0x%x io_req=%p.\n",
			 xid, io_req);
		वापस;
	पूर्ण

	/*
	 * Check that fcport is offloaded.  If it isn't then the spinlock
	 * isn't valid and shouldn't be taken. We should just वापस.
	 */
	अगर (!test_bit(QEDF_RPORT_SESSION_READY, &fcport->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx,
			 "Session not offloaded yet, fcport = %p.\n", fcport);
		वापस;
	पूर्ण


	चयन (comp_type) अणु
	हाल FCOE_GOOD_COMPLETION_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		चयन (io_req->cmd_type) अणु
		हाल QEDF_SCSI_CMD:
			qedf_scsi_completion(qedf, cqe, io_req);
			अवरोध;
		हाल QEDF_ELS:
			qedf_process_els_compl(qedf, cqe, io_req);
			अवरोध;
		हाल QEDF_TASK_MGMT_CMD:
			qedf_process_पंचांगf_compl(qedf, cqe, io_req);
			अवरोध;
		हाल QEDF_SEQ_CLEANUP:
			qedf_process_seq_cleanup_compl(qedf, cqe, io_req);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल FCOE_ERROR_DETECTION_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Error detect CQE.\n");
		qedf_process_error_detect(qedf, cqe, io_req);
		अवरोध;
	हाल FCOE_EXCH_CLEANUP_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Cleanup CQE.\n");
		qedf_process_cleanup_compl(qedf, cqe, io_req);
		अवरोध;
	हाल FCOE_ABTS_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Abort CQE.\n");
		qedf_process_abts_compl(qedf, cqe, io_req);
		अवरोध;
	हाल FCOE_DUMMY_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Dummy CQE.\n");
		अवरोध;
	हाल FCOE_LOCAL_COMP_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Local completion CQE.\n");
		अवरोध;
	हाल FCOE_WARNING_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Warning CQE.\n");
		qedf_process_warning_compl(qedf, cqe, io_req);
		अवरोध;
	हाल MAX_FCOE_CQE_TYPE:
		atomic_inc(&fcport->मुक्त_sqes);
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Max FCoE CQE.\n");
		अवरोध;
	शेष:
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_IO,
		    "Default CQE.\n");
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qedf_मुक्त_bdq(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक i;

	अगर (qedf->bdq_pbl_list)
		dma_मुक्त_coherent(&qedf->pdev->dev, QEDF_PAGE_SIZE,
		    qedf->bdq_pbl_list, qedf->bdq_pbl_list_dma);

	अगर (qedf->bdq_pbl)
		dma_मुक्त_coherent(&qedf->pdev->dev, qedf->bdq_pbl_mem_size,
		    qedf->bdq_pbl, qedf->bdq_pbl_dma);

	क्रम (i = 0; i < QEDF_BDQ_SIZE; i++) अणु
		अगर (qedf->bdq[i].buf_addr) अणु
			dma_मुक्त_coherent(&qedf->pdev->dev, QEDF_BDQ_BUF_SIZE,
			    qedf->bdq[i].buf_addr, qedf->bdq[i].buf_dma);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम qedf_मुक्त_global_queues(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक i;
	काष्ठा global_queue **gl = qedf->global_queues;

	क्रम (i = 0; i < qedf->num_queues; i++) अणु
		अगर (!gl[i])
			जारी;

		अगर (gl[i]->cq)
			dma_मुक्त_coherent(&qedf->pdev->dev,
			    gl[i]->cq_mem_size, gl[i]->cq, gl[i]->cq_dma);
		अगर (gl[i]->cq_pbl)
			dma_मुक्त_coherent(&qedf->pdev->dev, gl[i]->cq_pbl_size,
			    gl[i]->cq_pbl, gl[i]->cq_pbl_dma);

		kमुक्त(gl[i]);
	पूर्ण

	qedf_मुक्त_bdq(qedf);
पूर्ण

अटल पूर्णांक qedf_alloc_bdq(काष्ठा qedf_ctx *qedf)
अणु
	पूर्णांक i;
	काष्ठा scsi_bd *pbl;
	u64 *list;
	dma_addr_t page;

	/* Alloc dma memory क्रम BDQ buffers */
	क्रम (i = 0; i < QEDF_BDQ_SIZE; i++) अणु
		qedf->bdq[i].buf_addr = dma_alloc_coherent(&qedf->pdev->dev,
		    QEDF_BDQ_BUF_SIZE, &qedf->bdq[i].buf_dma, GFP_KERNEL);
		अगर (!qedf->bdq[i].buf_addr) अणु
			QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate BDQ "
			    "buffer %d.\n", i);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Alloc dma memory क्रम BDQ page buffer list */
	qedf->bdq_pbl_mem_size =
	    QEDF_BDQ_SIZE * माप(काष्ठा scsi_bd);
	qedf->bdq_pbl_mem_size =
	    ALIGN(qedf->bdq_pbl_mem_size, QEDF_PAGE_SIZE);

	qedf->bdq_pbl = dma_alloc_coherent(&qedf->pdev->dev,
	    qedf->bdq_pbl_mem_size, &qedf->bdq_pbl_dma, GFP_KERNEL);
	अगर (!qedf->bdq_pbl) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate BDQ PBL.\n");
		वापस -ENOMEM;
	पूर्ण

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		  "BDQ PBL addr=0x%p dma=%pad\n",
		  qedf->bdq_pbl, &qedf->bdq_pbl_dma);

	/*
	 * Populate BDQ PBL with physical and भव address of inभागidual
	 * BDQ buffers
	 */
	pbl = (काष्ठा scsi_bd *)qedf->bdq_pbl;
	क्रम (i = 0; i < QEDF_BDQ_SIZE; i++) अणु
		pbl->address.hi = cpu_to_le32(U64_HI(qedf->bdq[i].buf_dma));
		pbl->address.lo = cpu_to_le32(U64_LO(qedf->bdq[i].buf_dma));
		pbl->opaque.fcoe_opaque.hi = 0;
		/* Opaque lo data is an index पूर्णांकo the BDQ array */
		pbl->opaque.fcoe_opaque.lo = cpu_to_le32(i);
		pbl++;
	पूर्ण

	/* Allocate list of PBL pages */
	qedf->bdq_pbl_list = dma_alloc_coherent(&qedf->pdev->dev,
						QEDF_PAGE_SIZE,
						&qedf->bdq_pbl_list_dma,
						GFP_KERNEL);
	अगर (!qedf->bdq_pbl_list) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Could not allocate list of PBL pages.\n");
		वापस -ENOMEM;
	पूर्ण

	/*
	 * Now populate PBL list with pages that contain poपूर्णांकers to the
	 * inभागidual buffers.
	 */
	qedf->bdq_pbl_list_num_entries = qedf->bdq_pbl_mem_size /
	    QEDF_PAGE_SIZE;
	list = (u64 *)qedf->bdq_pbl_list;
	page = qedf->bdq_pbl_list_dma;
	क्रम (i = 0; i < qedf->bdq_pbl_list_num_entries; i++) अणु
		*list = qedf->bdq_pbl_dma;
		list++;
		page += QEDF_PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qedf_alloc_global_queues(काष्ठा qedf_ctx *qedf)
अणु
	u32 *list;
	पूर्णांक i;
	पूर्णांक status = 0, rc;
	u32 *pbl;
	dma_addr_t page;
	पूर्णांक num_pages;

	/* Allocate and map CQs, RQs */
	/*
	 * Number of global queues (CQ / RQ). This should
	 * be <= number of available MSIX vectors क्रम the PF
	 */
	अगर (!qedf->num_queues) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "No MSI-X vectors available!\n");
		वापस 1;
	पूर्ण

	/*
	 * Make sure we allocated the PBL that will contain the physical
	 * addresses of our queues
	 */
	अगर (!qedf->p_cpuq) अणु
		status = 1;
		QEDF_ERR(&qedf->dbg_ctx, "p_cpuq is NULL.\n");
		जाओ mem_alloc_failure;
	पूर्ण

	qedf->global_queues = kzalloc((माप(काष्ठा global_queue *)
	    * qedf->num_queues), GFP_KERNEL);
	अगर (!qedf->global_queues) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Unable to allocate global "
			  "queues array ptr memory\n");
		वापस -ENOMEM;
	पूर्ण
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		   "qedf->global_queues=%p.\n", qedf->global_queues);

	/* Allocate DMA coherent buffers क्रम BDQ */
	rc = qedf_alloc_bdq(qedf);
	अगर (rc) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Unable to allocate bdq.\n");
		जाओ mem_alloc_failure;
	पूर्ण

	/* Allocate a CQ and an associated PBL क्रम each MSI-X vector */
	क्रम (i = 0; i < qedf->num_queues; i++) अणु
		qedf->global_queues[i] = kzalloc(माप(काष्ठा global_queue),
		    GFP_KERNEL);
		अगर (!qedf->global_queues[i]) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "Unable to allocate "
				   "global queue %d.\n", i);
			status = -ENOMEM;
			जाओ mem_alloc_failure;
		पूर्ण

		qedf->global_queues[i]->cq_mem_size =
		    FCOE_PARAMS_CQ_NUM_ENTRIES * माप(काष्ठा fcoe_cqe);
		qedf->global_queues[i]->cq_mem_size =
		    ALIGN(qedf->global_queues[i]->cq_mem_size, QEDF_PAGE_SIZE);

		qedf->global_queues[i]->cq_pbl_size =
		    (qedf->global_queues[i]->cq_mem_size /
		    PAGE_SIZE) * माप(व्योम *);
		qedf->global_queues[i]->cq_pbl_size =
		    ALIGN(qedf->global_queues[i]->cq_pbl_size, QEDF_PAGE_SIZE);

		qedf->global_queues[i]->cq =
		    dma_alloc_coherent(&qedf->pdev->dev,
				       qedf->global_queues[i]->cq_mem_size,
				       &qedf->global_queues[i]->cq_dma,
				       GFP_KERNEL);

		अगर (!qedf->global_queues[i]->cq) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate cq.\n");
			status = -ENOMEM;
			जाओ mem_alloc_failure;
		पूर्ण

		qedf->global_queues[i]->cq_pbl =
		    dma_alloc_coherent(&qedf->pdev->dev,
				       qedf->global_queues[i]->cq_pbl_size,
				       &qedf->global_queues[i]->cq_pbl_dma,
				       GFP_KERNEL);

		अगर (!qedf->global_queues[i]->cq_pbl) अणु
			QEDF_WARN(&(qedf->dbg_ctx), "Could not allocate cq PBL.\n");
			status = -ENOMEM;
			जाओ mem_alloc_failure;
		पूर्ण

		/* Create PBL */
		num_pages = qedf->global_queues[i]->cq_mem_size /
		    QEDF_PAGE_SIZE;
		page = qedf->global_queues[i]->cq_dma;
		pbl = (u32 *)qedf->global_queues[i]->cq_pbl;

		जबतक (num_pages--) अणु
			*pbl = U64_LO(page);
			pbl++;
			*pbl = U64_HI(page);
			pbl++;
			page += QEDF_PAGE_SIZE;
		पूर्ण
		/* Set the initial consumer index क्रम cq */
		qedf->global_queues[i]->cq_cons_idx = 0;
	पूर्ण

	list = (u32 *)qedf->p_cpuq;

	/*
	 * The list is built as follows: CQ#0 PBL poपूर्णांकer, RQ#0 PBL poपूर्णांकer,
	 * CQ#1 PBL poपूर्णांकer, RQ#1 PBL poपूर्णांकer, etc.  Each PBL poपूर्णांकer poपूर्णांकs
	 * to the physical address which contains an array of poपूर्णांकers to
	 * the physical addresses of the specअगरic queue pages.
	 */
	क्रम (i = 0; i < qedf->num_queues; i++) अणु
		*list = U64_LO(qedf->global_queues[i]->cq_pbl_dma);
		list++;
		*list = U64_HI(qedf->global_queues[i]->cq_pbl_dma);
		list++;
		*list = U64_LO(0);
		list++;
		*list = U64_HI(0);
		list++;
	पूर्ण

	वापस 0;

mem_alloc_failure:
	qedf_मुक्त_global_queues(qedf);
	वापस status;
पूर्ण

अटल पूर्णांक qedf_set_fcoe_pf_param(काष्ठा qedf_ctx *qedf)
अणु
	u8 sq_num_pbl_pages;
	u32 sq_mem_size;
	u32 cq_mem_size;
	u32 cq_num_entries;
	पूर्णांक rval;

	/*
	 * The number of completion queues/fastpath पूर्णांकerrupts/status blocks
	 * we allocation is the minimum off:
	 *
	 * Number of CPUs
	 * Number allocated by qed क्रम our PCI function
	 */
	qedf->num_queues = MIN_NUM_CPUS_MSIX(qedf);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Number of CQs is %d.\n",
		   qedf->num_queues);

	qedf->p_cpuq = dma_alloc_coherent(&qedf->pdev->dev,
	    qedf->num_queues * माप(काष्ठा qedf_glbl_q_params),
	    &qedf->hw_p_cpuq, GFP_KERNEL);

	अगर (!qedf->p_cpuq) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "dma_alloc_coherent failed.\n");
		वापस 1;
	पूर्ण

	rval = qedf_alloc_global_queues(qedf);
	अगर (rval) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Global queue allocation "
			  "failed.\n");
		वापस 1;
	पूर्ण

	/* Calculate SQ PBL size in the same manner as in qedf_sq_alloc() */
	sq_mem_size = SQ_NUM_ENTRIES * माप(काष्ठा fcoe_wqe);
	sq_mem_size = ALIGN(sq_mem_size, QEDF_PAGE_SIZE);
	sq_num_pbl_pages = (sq_mem_size / QEDF_PAGE_SIZE);

	/* Calculate CQ num entries */
	cq_mem_size = FCOE_PARAMS_CQ_NUM_ENTRIES * माप(काष्ठा fcoe_cqe);
	cq_mem_size = ALIGN(cq_mem_size, QEDF_PAGE_SIZE);
	cq_num_entries = cq_mem_size / माप(काष्ठा fcoe_cqe);

	स_रखो(&(qedf->pf_params), 0, माप(qedf->pf_params));

	/* Setup the value क्रम fcoe PF */
	qedf->pf_params.fcoe_pf_params.num_cons = QEDF_MAX_SESSIONS;
	qedf->pf_params.fcoe_pf_params.num_tasks = FCOE_PARAMS_NUM_TASKS;
	qedf->pf_params.fcoe_pf_params.glbl_q_params_addr =
	    (u64)qedf->hw_p_cpuq;
	qedf->pf_params.fcoe_pf_params.sq_num_pbl_pages = sq_num_pbl_pages;

	qedf->pf_params.fcoe_pf_params.rq_buffer_log_size = 0;

	qedf->pf_params.fcoe_pf_params.cq_num_entries = cq_num_entries;
	qedf->pf_params.fcoe_pf_params.num_cqs = qedf->num_queues;

	/* log_page_size: 12 क्रम 4KB pages */
	qedf->pf_params.fcoe_pf_params.log_page_size = ilog2(QEDF_PAGE_SIZE);

	qedf->pf_params.fcoe_pf_params.mtu = 9000;
	qedf->pf_params.fcoe_pf_params.gl_rq_pi = QEDF_FCOE_PARAMS_GL_RQ_PI;
	qedf->pf_params.fcoe_pf_params.gl_cmd_pi = QEDF_FCOE_PARAMS_GL_CMD_PI;

	/* BDQ address and size */
	qedf->pf_params.fcoe_pf_params.bdq_pbl_base_addr[0] =
	    qedf->bdq_pbl_list_dma;
	qedf->pf_params.fcoe_pf_params.bdq_pbl_num_entries[0] =
	    qedf->bdq_pbl_list_num_entries;
	qedf->pf_params.fcoe_pf_params.rq_buffer_size = QEDF_BDQ_BUF_SIZE;

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
	    "bdq_list=%p bdq_pbl_list_dma=%llx bdq_pbl_list_entries=%d.\n",
	    qedf->bdq_pbl_list,
	    qedf->pf_params.fcoe_pf_params.bdq_pbl_base_addr[0],
	    qedf->pf_params.fcoe_pf_params.bdq_pbl_num_entries[0]);

	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
	    "cq_num_entries=%d.\n",
	    qedf->pf_params.fcoe_pf_params.cq_num_entries);

	वापस 0;
पूर्ण

/* Free DMA coherent memory क्रम array of queue poपूर्णांकers we pass to qed */
अटल व्योम qedf_मुक्त_fcoe_pf_param(काष्ठा qedf_ctx *qedf)
अणु
	माप_प्रकार size = 0;

	अगर (qedf->p_cpuq) अणु
		size = qedf->num_queues * माप(काष्ठा qedf_glbl_q_params);
		dma_मुक्त_coherent(&qedf->pdev->dev, size, qedf->p_cpuq,
		    qedf->hw_p_cpuq);
	पूर्ण

	qedf_मुक्त_global_queues(qedf);

	kमुक्त(qedf->global_queues);
पूर्ण

/*
 * PCI driver functions
 */

अटल स्थिर काष्ठा pci_device_id qedf_pci_tbl[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, 0x165c) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_QLOGIC, 0x8080) पूर्ण,
	अणु0पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, qedf_pci_tbl);

अटल काष्ठा pci_driver qedf_pci_driver = अणु
	.name = QEDF_MODULE_NAME,
	.id_table = qedf_pci_tbl,
	.probe = qedf_probe,
	.हटाओ = qedf_हटाओ,
	.shutकरोwn = qedf_shutकरोwn,
पूर्ण;

अटल पूर्णांक __qedf_probe(काष्ठा pci_dev *pdev, पूर्णांक mode)
अणु
	पूर्णांक rc = -EINVAL;
	काष्ठा fc_lport *lport;
	काष्ठा qedf_ctx *qedf = शून्य;
	काष्ठा Scsi_Host *host;
	bool is_vf = false;
	काष्ठा qed_ll2_params params;
	अक्षर host_buf[20];
	काष्ठा qed_link_params link_params;
	पूर्णांक status;
	व्योम *task_start, *task_end;
	काष्ठा qed_slowpath_params slowpath_params;
	काष्ठा qed_probe_params qed_params;
	u16 retry_cnt = 10;

	/*
	 * When करोing error recovery we didn't reap the lport so don't try
	 * to पुनः_स्मृतिate it.
	 */
retry_probe:
	अगर (mode == QEDF_MODE_RECOVERY)
		msleep(2000);

	अगर (mode != QEDF_MODE_RECOVERY) अणु
		lport = libfc_host_alloc(&qedf_host_ढाँचा,
		    माप(काष्ठा qedf_ctx));

		अगर (!lport) अणु
			QEDF_ERR(शून्य, "Could not allocate lport.\n");
			rc = -ENOMEM;
			जाओ err0;
		पूर्ण

		fc_disc_init(lport);

		/* Initialize qedf_ctx */
		qedf = lport_priv(lport);
		set_bit(QEDF_PROBING, &qedf->flags);
		qedf->lport = lport;
		qedf->ctlr.lp = lport;
		qedf->pdev = pdev;
		qedf->dbg_ctx.pdev = pdev;
		qedf->dbg_ctx.host_no = lport->host->host_no;
		spin_lock_init(&qedf->hba_lock);
		INIT_LIST_HEAD(&qedf->fcports);
		qedf->curr_conn_id = QEDF_MAX_SESSIONS - 1;
		atomic_set(&qedf->num_offloads, 0);
		qedf->stop_io_on_error = false;
		pci_set_drvdata(pdev, qedf);
		init_completion(&qedf->fipvlan_compl);
		mutex_init(&qedf->stats_mutex);
		mutex_init(&qedf->flush_mutex);
		qedf->flogi_pending = 0;

		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_INFO,
		   "QLogic FastLinQ FCoE Module qedf %s, "
		   "FW %d.%d.%d.%d\n", QEDF_VERSION,
		   FW_MAJOR_VERSION, FW_MINOR_VERSION, FW_REVISION_VERSION,
		   FW_ENGINEERING_VERSION);
	पूर्ण अन्यथा अणु
		/* Init poपूर्णांकers during recovery */
		qedf = pci_get_drvdata(pdev);
		set_bit(QEDF_PROBING, &qedf->flags);
		lport = qedf->lport;
	पूर्ण

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC, "Probe started.\n");

	host = lport->host;

	/* Allocate mempool क्रम qedf_io_work काष्ठाs */
	qedf->io_mempool = mempool_create_slab_pool(QEDF_IO_WORK_MIN,
	    qedf_io_work_cache);
	अगर (qedf->io_mempool == शून्य) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "qedf->io_mempool is NULL.\n");
		जाओ err1;
	पूर्ण
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_INFO, "qedf->io_mempool=%p.\n",
	    qedf->io_mempool);

	प्र_लिखो(host_buf, "qedf_%u_link",
	    qedf->lport->host->host_no);
	qedf->link_update_wq = create_workqueue(host_buf);
	INIT_DELAYED_WORK(&qedf->link_update, qedf_handle_link_update);
	INIT_DELAYED_WORK(&qedf->link_recovery, qedf_link_recovery);
	INIT_DELAYED_WORK(&qedf->grcdump_work, qedf_wq_grcdump);
	INIT_DELAYED_WORK(&qedf->stag_work, qedf_stag_change_work);
	qedf->fipvlan_retries = qedf_fipvlan_retries;
	/* Set a शेष prio in हाल DCBX करोesn't converge */
	अगर (qedf_शेष_prio > -1) अणु
		/*
		 * This is the हाल where we pass a modparam in so we want to
		 * honor it even अगर dcbx करोesn't converge.
		 */
		qedf->prio = qedf_शेष_prio;
	पूर्ण अन्यथा
		qedf->prio = QEDF_DEFAULT_PRIO;

	/*
	 * Common probe. Takes care of basic hardware init and pci_*
	 * functions.
	 */
	स_रखो(&qed_params, 0, माप(qed_params));
	qed_params.protocol = QED_PROTOCOL_FCOE;
	qed_params.dp_module = qedf_dp_module;
	qed_params.dp_level = qedf_dp_level;
	qed_params.is_vf = is_vf;
	qedf->cdev = qed_ops->common->probe(pdev, &qed_params);
	अगर (!qedf->cdev) अणु
		अगर ((mode == QEDF_MODE_RECOVERY) && retry_cnt) अणु
			QEDF_ERR(&qedf->dbg_ctx,
				"Retry %d initialize hardware\n", retry_cnt);
			retry_cnt--;
			जाओ retry_probe;
		पूर्ण
		QEDF_ERR(&qedf->dbg_ctx, "common probe failed.\n");
		rc = -ENODEV;
		जाओ err1;
	पूर्ण

	/* Learn inक्रमmation crucial क्रम qedf to progress */
	rc = qed_ops->fill_dev_info(qedf->cdev, &qedf->dev_info);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to dev info.\n");
		जाओ err1;
	पूर्ण

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC,
		  "dev_info: num_hwfns=%d affin_hwfn_idx=%d.\n",
		  qedf->dev_info.common.num_hwfns,
		  qed_ops->common->get_affin_hwfn_idx(qedf->cdev));

	/* queue allocation code should come here
	 * order should be
	 * 	slowpath_start
	 * 	status block allocation
	 *	पूर्णांकerrupt registration (to get min number of queues)
	 *	set_fcoe_pf_param
	 *	qed_sp_fcoe_func_start
	 */
	rc = qedf_set_fcoe_pf_param(qedf);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Cannot set fcoe pf param.\n");
		जाओ err2;
	पूर्ण
	qed_ops->common->update_pf_params(qedf->cdev, &qedf->pf_params);

	/* Learn inक्रमmation crucial क्रम qedf to progress */
	rc = qed_ops->fill_dev_info(qedf->cdev, &qedf->dev_info);
	अगर (rc) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Failed to fill dev info.\n");
		जाओ err2;
	पूर्ण

	अगर (mode != QEDF_MODE_RECOVERY) अणु
		qedf->devlink = qed_ops->common->devlink_रेजिस्टर(qedf->cdev);
		अगर (IS_ERR(qedf->devlink)) अणु
			QEDF_ERR(&qedf->dbg_ctx, "Cannot register devlink\n");
			qedf->devlink = शून्य;
		पूर्ण
	पूर्ण

	/* Record BDQ producer करोorbell addresses */
	qedf->bdq_primary_prod = qedf->dev_info.primary_dbq_rq_addr;
	qedf->bdq_secondary_prod = qedf->dev_info.secondary_bdq_rq_addr;
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
	    "BDQ primary_prod=%p secondary_prod=%p.\n", qedf->bdq_primary_prod,
	    qedf->bdq_secondary_prod);

	qed_ops->रेजिस्टर_ops(qedf->cdev, &qedf_cb_ops, qedf);

	rc = qedf_prepare_sb(qedf);
	अगर (rc) अणु

		QEDF_ERR(&(qedf->dbg_ctx), "Cannot start slowpath.\n");
		जाओ err2;
	पूर्ण

	/* Start the Slowpath-process */
	slowpath_params.पूर्णांक_mode = QED_INT_MODE_MSIX;
	slowpath_params.drv_major = QEDF_DRIVER_MAJOR_VER;
	slowpath_params.drv_minor = QEDF_DRIVER_MINOR_VER;
	slowpath_params.drv_rev = QEDF_DRIVER_REV_VER;
	slowpath_params.drv_eng = QEDF_DRIVER_ENG_VER;
	म_नकलन(slowpath_params.name, "qedf", QED_DRV_VER_STR_SIZE);
	rc = qed_ops->common->slowpath_start(qedf->cdev, &slowpath_params);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Cannot start slowpath.\n");
		जाओ err2;
	पूर्ण

	/*
	 * update_pf_params needs to be called beक्रमe and after slowpath
	 * start
	 */
	qed_ops->common->update_pf_params(qedf->cdev, &qedf->pf_params);

	/* Setup पूर्णांकerrupts */
	rc = qedf_setup_पूर्णांक(qedf);
	अगर (rc) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Setup interrupts failed.\n");
		जाओ err3;
	पूर्ण

	rc = qed_ops->start(qedf->cdev, &qedf->tasks);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Cannot start FCoE function.\n");
		जाओ err4;
	पूर्ण
	task_start = qedf_get_task_mem(&qedf->tasks, 0);
	task_end = qedf_get_task_mem(&qedf->tasks, MAX_TID_BLOCKS_FCOE - 1);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "Task context start=%p, "
		   "end=%p block_size=%u.\n", task_start, task_end,
		   qedf->tasks.size);

	/*
	 * We need to ग_लिखो the number of BDs in the BDQ we've pपुनः_स्मृतिated so
	 * the f/w will करो a prefetch and we'll get an unsolicited CQE when a
	 * packet arrives.
	 */
	qedf->bdq_prod_idx = QEDF_BDQ_SIZE;
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
	    "Writing %d to primary and secondary BDQ doorbell registers.\n",
	    qedf->bdq_prod_idx);
	ग_लिखोw(qedf->bdq_prod_idx, qedf->bdq_primary_prod);
	पढ़ोw(qedf->bdq_primary_prod);
	ग_लिखोw(qedf->bdq_prod_idx, qedf->bdq_secondary_prod);
	पढ़ोw(qedf->bdq_secondary_prod);

	qed_ops->common->set_घातer_state(qedf->cdev, PCI_D0);

	/* Now that the dev_info काष्ठा has been filled in set the MAC
	 * address
	 */
	ether_addr_copy(qedf->mac, qedf->dev_info.common.hw_mac);
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC, "MAC address is %pM.\n",
		   qedf->mac);

	/*
	 * Set the WWNN and WWPN in the following way:
	 *
	 * If the info we get from qed is non-zero then use that to set the
	 * WWPN and WWNN. Otherwise fall back to use fcoe_wwn_from_mac() based
	 * on the MAC address.
	 */
	अगर (qedf->dev_info.wwnn != 0 && qedf->dev_info.wwpn != 0) अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		    "Setting WWPN and WWNN from qed dev_info.\n");
		qedf->wwnn = qedf->dev_info.wwnn;
		qedf->wwpn = qedf->dev_info.wwpn;
	पूर्ण अन्यथा अणु
		QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
		    "Setting WWPN and WWNN using fcoe_wwn_from_mac().\n");
		qedf->wwnn = fcoe_wwn_from_mac(qedf->mac, 1, 0);
		qedf->wwpn = fcoe_wwn_from_mac(qedf->mac, 2, 0);
	पूर्ण
	QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,  "WWNN=%016llx "
		   "WWPN=%016llx.\n", qedf->wwnn, qedf->wwpn);

	प्र_लिखो(host_buf, "host_%d", host->host_no);
	qed_ops->common->set_name(qedf->cdev, host_buf);

	/* Allocate cmd mgr */
	qedf->cmd_mgr = qedf_cmd_mgr_alloc(qedf);
	अगर (!qedf->cmd_mgr) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to allocate cmd mgr.\n");
		rc = -ENOMEM;
		जाओ err5;
	पूर्ण

	अगर (mode != QEDF_MODE_RECOVERY) अणु
		host->transportt = qedf_fc_transport_ढाँचा;
		host->max_lun = qedf_max_lun;
		host->max_cmd_len = QEDF_MAX_CDB_LEN;
		host->can_queue = FCOE_PARAMS_NUM_TASKS;
		rc = scsi_add_host(host, &pdev->dev);
		अगर (rc) अणु
			QEDF_WARN(&qedf->dbg_ctx,
				  "Error adding Scsi_Host rc=0x%x.\n", rc);
			जाओ err6;
		पूर्ण
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.mtu = QEDF_LL2_BUF_SIZE;
	ether_addr_copy(params.ll2_mac_address, qedf->mac);

	/* Start LL2 processing thपढ़ो */
	snम_लिखो(host_buf, 20, "qedf_%d_ll2", host->host_no);
	qedf->ll2_recv_wq =
		create_workqueue(host_buf);
	अगर (!qedf->ll2_recv_wq) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to LL2 workqueue.\n");
		rc = -ENOMEM;
		जाओ err7;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	qedf_dbg_host_init(&(qedf->dbg_ctx), qedf_debugfs_ops,
			    qedf_dbg_fops);
#पूर्ण_अगर

	/* Start LL2 */
	qed_ops->ll2->रेजिस्टर_cb_ops(qedf->cdev, &qedf_ll2_cb_ops, qedf);
	rc = qed_ops->ll2->start(qedf->cdev, &params);
	अगर (rc) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Could not start Light L2.\n");
		जाओ err7;
	पूर्ण
	set_bit(QEDF_LL2_STARTED, &qedf->flags);

	/* Set initial FIP/FCoE VLAN to शून्य */
	qedf->vlan_id = 0;

	/*
	 * No need to setup fcoe_ctlr or fc_lport objects during recovery since
	 * they were not reaped during the unload process.
	 */
	अगर (mode != QEDF_MODE_RECOVERY) अणु
		/* Setup imbedded fcoe controller */
		qedf_fcoe_ctlr_setup(qedf);

		/* Setup lport */
		rc = qedf_lport_setup(qedf);
		अगर (rc) अणु
			QEDF_ERR(&(qedf->dbg_ctx),
			    "qedf_lport_setup failed.\n");
			जाओ err7;
		पूर्ण
	पूर्ण

	प्र_लिखो(host_buf, "qedf_%u_timer", qedf->lport->host->host_no);
	qedf->समयr_work_queue =
		create_workqueue(host_buf);
	अगर (!qedf->समयr_work_queue) अणु
		QEDF_ERR(&(qedf->dbg_ctx), "Failed to start timer "
			  "workqueue.\n");
		rc = -ENOMEM;
		जाओ err7;
	पूर्ण

	/* DPC workqueue is not reaped during recovery unload */
	अगर (mode != QEDF_MODE_RECOVERY) अणु
		प्र_लिखो(host_buf, "qedf_%u_dpc",
		    qedf->lport->host->host_no);
		qedf->dpc_wq = create_workqueue(host_buf);
	पूर्ण
	INIT_DELAYED_WORK(&qedf->recovery_work, qedf_recovery_handler);

	/*
	 * GRC dump and sysfs parameters are not reaped during the recovery
	 * unload process.
	 */
	अगर (mode != QEDF_MODE_RECOVERY) अणु
		qedf->grcdump_size =
		    qed_ops->common->dbg_all_data_size(qedf->cdev);
		अगर (qedf->grcdump_size) अणु
			rc = qedf_alloc_grc_dump_buf(&qedf->grcdump,
			    qedf->grcdump_size);
			अगर (rc) अणु
				QEDF_ERR(&(qedf->dbg_ctx),
				    "GRC Dump buffer alloc failed.\n");
				qedf->grcdump = शून्य;
			पूर्ण

			QEDF_INFO(&(qedf->dbg_ctx), QEDF_LOG_DISC,
			    "grcdump: addr=%p, size=%u.\n",
			    qedf->grcdump, qedf->grcdump_size);
		पूर्ण
		qedf_create_sysfs_ctx_attr(qedf);

		/* Initialize I/O tracing क्रम this adapter */
		spin_lock_init(&qedf->io_trace_lock);
		qedf->io_trace_idx = 0;
	पूर्ण

	init_completion(&qedf->flogi_compl);

	status = qed_ops->common->update_drv_state(qedf->cdev, true);
	अगर (status)
		QEDF_ERR(&(qedf->dbg_ctx),
			"Failed to send drv state to MFW.\n");

	स_रखो(&link_params, 0, माप(काष्ठा qed_link_params));
	link_params.link_up = true;
	status = qed_ops->common->set_link(qedf->cdev, &link_params);
	अगर (status)
		QEDF_WARN(&(qedf->dbg_ctx), "set_link failed.\n");

	/* Start/restart discovery */
	अगर (mode == QEDF_MODE_RECOVERY)
		fcoe_ctlr_link_up(&qedf->ctlr);
	अन्यथा
		fc_fabric_login(lport);

	QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC, "Probe done.\n");

	clear_bit(QEDF_PROBING, &qedf->flags);

	/* All good */
	वापस 0;

err7:
	अगर (qedf->ll2_recv_wq)
		destroy_workqueue(qedf->ll2_recv_wq);
	fc_हटाओ_host(qedf->lport->host);
	scsi_हटाओ_host(qedf->lport->host);
#अगर_घोषित CONFIG_DEBUG_FS
	qedf_dbg_host_निकास(&(qedf->dbg_ctx));
#पूर्ण_अगर
err6:
	qedf_cmd_mgr_मुक्त(qedf->cmd_mgr);
err5:
	qed_ops->stop(qedf->cdev);
err4:
	qedf_मुक्त_fcoe_pf_param(qedf);
	qedf_sync_मुक्त_irqs(qedf);
err3:
	qed_ops->common->slowpath_stop(qedf->cdev);
err2:
	qed_ops->common->हटाओ(qedf->cdev);
err1:
	scsi_host_put(lport->host);
err0:
	अगर (qedf) अणु
		QEDF_INFO(&qedf->dbg_ctx, QEDF_LOG_DISC, "Probe done.\n");

		clear_bit(QEDF_PROBING, &qedf->flags);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक qedf_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	वापस __qedf_probe(pdev, QEDF_MODE_NORMAL);
पूर्ण

अटल व्योम __qedf_हटाओ(काष्ठा pci_dev *pdev, पूर्णांक mode)
अणु
	काष्ठा qedf_ctx *qedf;
	पूर्णांक rc;

	अगर (!pdev) अणु
		QEDF_ERR(शून्य, "pdev is NULL.\n");
		वापस;
	पूर्ण

	qedf = pci_get_drvdata(pdev);

	/*
	 * Prevent race where we're in board disable work and then try to
	 * rmmod the module.
	 */
	अगर (test_bit(QEDF_UNLOADING, &qedf->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Already removing PCI function.\n");
		वापस;
	पूर्ण

	अगर (mode != QEDF_MODE_RECOVERY)
		set_bit(QEDF_UNLOADING, &qedf->flags);

	/* Logoff the fabric to upload all connections */
	अगर (mode == QEDF_MODE_RECOVERY)
		fcoe_ctlr_link_करोwn(&qedf->ctlr);
	अन्यथा
		fc_fabric_logoff(qedf->lport);

	अगर (!qedf_रुको_क्रम_upload(qedf))
		QEDF_ERR(&qedf->dbg_ctx, "Could not upload all sessions.\n");

#अगर_घोषित CONFIG_DEBUG_FS
	qedf_dbg_host_निकास(&(qedf->dbg_ctx));
#पूर्ण_अगर

	/* Stop any link update handling */
	cancel_delayed_work_sync(&qedf->link_update);
	destroy_workqueue(qedf->link_update_wq);
	qedf->link_update_wq = शून्य;

	अगर (qedf->समयr_work_queue)
		destroy_workqueue(qedf->समयr_work_queue);

	/* Stop Light L2 */
	clear_bit(QEDF_LL2_STARTED, &qedf->flags);
	qed_ops->ll2->stop(qedf->cdev);
	अगर (qedf->ll2_recv_wq)
		destroy_workqueue(qedf->ll2_recv_wq);

	/* Stop fastpath */
	qedf_sync_मुक्त_irqs(qedf);
	qedf_destroy_sb(qedf);

	/*
	 * During recovery करोn't destroy OS स्थिरructs that represent the
	 * physical port.
	 */
	अगर (mode != QEDF_MODE_RECOVERY) अणु
		qedf_मुक्त_grc_dump_buf(&qedf->grcdump);
		qedf_हटाओ_sysfs_ctx_attr(qedf);

		/* Remove all SCSI/libfc/libfcoe काष्ठाures */
		fcoe_ctlr_destroy(&qedf->ctlr);
		fc_lport_destroy(qedf->lport);
		fc_हटाओ_host(qedf->lport->host);
		scsi_हटाओ_host(qedf->lport->host);
	पूर्ण

	qedf_cmd_mgr_मुक्त(qedf->cmd_mgr);

	अगर (mode != QEDF_MODE_RECOVERY) अणु
		fc_exch_mgr_मुक्त(qedf->lport);
		fc_lport_मुक्त_stats(qedf->lport);

		/* Wait क्रम all vports to be reaped */
		qedf_रुको_क्रम_vport_destroy(qedf);
	पूर्ण

	/*
	 * Now that all connections have been uploaded we can stop the
	 * rest of the qed operations
	 */
	qed_ops->stop(qedf->cdev);

	अगर (mode != QEDF_MODE_RECOVERY) अणु
		अगर (qedf->dpc_wq) अणु
			/* Stop general DPC handling */
			destroy_workqueue(qedf->dpc_wq);
			qedf->dpc_wq = शून्य;
		पूर्ण
	पूर्ण

	/* Final shutकरोwn क्रम the board */
	qedf_मुक्त_fcoe_pf_param(qedf);
	अगर (mode != QEDF_MODE_RECOVERY) अणु
		qed_ops->common->set_घातer_state(qedf->cdev, PCI_D0);
		pci_set_drvdata(pdev, शून्य);
	पूर्ण

	rc = qed_ops->common->update_drv_state(qedf->cdev, false);
	अगर (rc)
		QEDF_ERR(&(qedf->dbg_ctx),
			"Failed to send drv state to MFW.\n");

	अगर (mode != QEDF_MODE_RECOVERY && qedf->devlink) अणु
		qed_ops->common->devlink_unरेजिस्टर(qedf->devlink);
		qedf->devlink = शून्य;
	पूर्ण

	qed_ops->common->slowpath_stop(qedf->cdev);
	qed_ops->common->हटाओ(qedf->cdev);

	mempool_destroy(qedf->io_mempool);

	/* Only reap the Scsi_host on a real removal */
	अगर (mode != QEDF_MODE_RECOVERY)
		scsi_host_put(qedf->lport->host);
पूर्ण

अटल व्योम qedf_हटाओ(काष्ठा pci_dev *pdev)
अणु
	/* Check to make sure this function wasn't alपढ़ोy disabled */
	अगर (!atomic_पढ़ो(&pdev->enable_cnt))
		वापस;

	__qedf_हटाओ(pdev, QEDF_MODE_NORMAL);
पूर्ण

व्योम qedf_wq_grcdump(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_ctx *qedf =
	    container_of(work, काष्ठा qedf_ctx, grcdump_work.work);

	QEDF_ERR(&(qedf->dbg_ctx), "Collecting GRC dump.\n");
	qedf_capture_grc_dump(qedf);
पूर्ण

व्योम qedf_schedule_hw_err_handler(व्योम *dev, क्रमागत qed_hw_err_type err_type)
अणु
	काष्ठा qedf_ctx *qedf = dev;

	QEDF_ERR(&(qedf->dbg_ctx),
			"Hardware error handler scheduled, event=%d.\n",
			err_type);

	अगर (test_bit(QEDF_IN_RECOVERY, &qedf->flags)) अणु
		QEDF_ERR(&(qedf->dbg_ctx),
				"Already in recovery, not scheduling board disable work.\n");
		वापस;
	पूर्ण

	चयन (err_type) अणु
	हाल QED_HW_ERR_FAN_FAIL:
		schedule_delayed_work(&qedf->board_disable_work, 0);
		अवरोध;
	हाल QED_HW_ERR_MFW_RESP_FAIL:
	हाल QED_HW_ERR_HW_ATTN:
	हाल QED_HW_ERR_DMAE_FAIL:
	हाल QED_HW_ERR_FW_ASSERT:
		/* Prevent HW attentions from being reनिश्चितed */
		qed_ops->common->attn_clr_enable(qedf->cdev, true);
		अवरोध;
	हाल QED_HW_ERR_RAMROD_FAIL:
		/* Prevent HW attentions from being reनिश्चितed */
		qed_ops->common->attn_clr_enable(qedf->cdev, true);

		अगर (qedf_enable_recovery && qedf->devlink)
			qed_ops->common->report_fatal_error(qedf->devlink,
				err_type);

		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * Protocol TLV handler
 */
व्योम qedf_get_protocol_tlv_data(व्योम *dev, व्योम *data)
अणु
	काष्ठा qedf_ctx *qedf = dev;
	काष्ठा qed_mfw_tlv_fcoe *fcoe = data;
	काष्ठा fc_lport *lport;
	काष्ठा Scsi_Host *host;
	काष्ठा fc_host_attrs *fc_host;
	काष्ठा fc_host_statistics *hst;

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is null.\n");
		वापस;
	पूर्ण

	अगर (test_bit(QEDF_PROBING, &qedf->flags)) अणु
		QEDF_ERR(&qedf->dbg_ctx, "Function is still probing.\n");
		वापस;
	पूर्ण

	lport = qedf->lport;
	host = lport->host;
	fc_host = shost_to_fc_host(host);

	/* Force a refresh of the fc_host stats including offload stats */
	hst = qedf_fc_get_host_stats(host);

	fcoe->qos_pri_set = true;
	fcoe->qos_pri = 3; /* Hard coded to 3 in driver */

	fcoe->ra_tov_set = true;
	fcoe->ra_tov = lport->r_a_tov;

	fcoe->ed_tov_set = true;
	fcoe->ed_tov = lport->e_d_tov;

	fcoe->npiv_state_set = true;
	fcoe->npiv_state = 1; /* NPIV always enabled */

	fcoe->num_npiv_ids_set = true;
	fcoe->num_npiv_ids = fc_host->npiv_vports_inuse;

	/* Certain attributes we only want to set अगर we've selected an FCF */
	अगर (qedf->ctlr.sel_fcf) अणु
		fcoe->चयन_name_set = true;
		u64_to_wwn(qedf->ctlr.sel_fcf->चयन_name, fcoe->चयन_name);
	पूर्ण

	fcoe->port_state_set = true;
	/* For qedf we're either link करोwn or fabric attach */
	अगर (lport->link_up)
		fcoe->port_state = QED_MFW_TLV_PORT_STATE_FABRIC;
	अन्यथा
		fcoe->port_state = QED_MFW_TLV_PORT_STATE_OFFLINE;

	fcoe->link_failures_set = true;
	fcoe->link_failures = (u16)hst->link_failure_count;

	fcoe->fcoe_txq_depth_set = true;
	fcoe->fcoe_rxq_depth_set = true;
	fcoe->fcoe_rxq_depth = FCOE_PARAMS_NUM_TASKS;
	fcoe->fcoe_txq_depth = FCOE_PARAMS_NUM_TASKS;

	fcoe->fcoe_rx_frames_set = true;
	fcoe->fcoe_rx_frames = hst->rx_frames;

	fcoe->fcoe_tx_frames_set = true;
	fcoe->fcoe_tx_frames = hst->tx_frames;

	fcoe->fcoe_rx_bytes_set = true;
	fcoe->fcoe_rx_bytes = hst->fcp_input_megabytes * 1000000;

	fcoe->fcoe_tx_bytes_set = true;
	fcoe->fcoe_tx_bytes = hst->fcp_output_megabytes * 1000000;

	fcoe->crc_count_set = true;
	fcoe->crc_count = hst->invalid_crc_count;

	fcoe->tx_abts_set = true;
	fcoe->tx_abts = hst->fcp_packet_पातs;

	fcoe->tx_lun_rst_set = true;
	fcoe->tx_lun_rst = qedf->lun_resets;

	fcoe->पात_task_sets_set = true;
	fcoe->पात_task_sets = qedf->packet_पातs;

	fcoe->scsi_busy_set = true;
	fcoe->scsi_busy = qedf->busy;

	fcoe->scsi_tsk_full_set = true;
	fcoe->scsi_tsk_full = qedf->task_set_fulls;
पूर्ण

/* Deferred work function to perक्रमm soft context reset on STAG change */
व्योम qedf_stag_change_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_ctx *qedf =
	    container_of(work, काष्ठा qedf_ctx, stag_work.work);

	अगर (!qedf) अणु
		QEDF_ERR(शून्य, "qedf is NULL");
		वापस;
	पूर्ण
	QEDF_ERR(&qedf->dbg_ctx, "Performing software context reset.\n");
	qedf_ctx_soft_reset(qedf->lport);
पूर्ण

अटल व्योम qedf_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	__qedf_हटाओ(pdev, QEDF_MODE_NORMAL);
पूर्ण

/*
 * Recovery handler code
 */
अटल व्योम qedf_schedule_recovery_handler(व्योम *dev)
अणु
	काष्ठा qedf_ctx *qedf = dev;

	QEDF_ERR(&qedf->dbg_ctx, "Recovery handler scheduled.\n");
	schedule_delayed_work(&qedf->recovery_work, 0);
पूर्ण

अटल व्योम qedf_recovery_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qedf_ctx *qedf =
	    container_of(work, काष्ठा qedf_ctx, recovery_work.work);

	अगर (test_and_set_bit(QEDF_IN_RECOVERY, &qedf->flags))
		वापस;

	/*
	 * Call common_ops->recovery_prolog to allow the MFW to quiesce
	 * any PCI transactions.
	 */
	qed_ops->common->recovery_prolog(qedf->cdev);

	QEDF_ERR(&qedf->dbg_ctx, "Recovery work start.\n");
	__qedf_हटाओ(qedf->pdev, QEDF_MODE_RECOVERY);
	/*
	 * Reset link and dcbx to करोwn state since we will not get a link करोwn
	 * event from the MFW but calling __qedf_हटाओ will essentially be a
	 * link करोwn event.
	 */
	atomic_set(&qedf->link_state, QEDF_LINK_DOWN);
	atomic_set(&qedf->dcbx, QEDF_DCBX_PENDING);
	__qedf_probe(qedf->pdev, QEDF_MODE_RECOVERY);
	clear_bit(QEDF_IN_RECOVERY, &qedf->flags);
	QEDF_ERR(&qedf->dbg_ctx, "Recovery work complete.\n");
पूर्ण

/* Generic TLV data callback */
व्योम qedf_get_generic_tlv_data(व्योम *dev, काष्ठा qed_generic_tlvs *data)
अणु
	काष्ठा qedf_ctx *qedf;

	अगर (!dev) अणु
		QEDF_INFO(शून्य, QEDF_LOG_EVT,
			  "dev is NULL so ignoring get_generic_tlv_data request.\n");
		वापस;
	पूर्ण
	qedf = (काष्ठा qedf_ctx *)dev;

	स_रखो(data, 0, माप(काष्ठा qed_generic_tlvs));
	ether_addr_copy(data->mac[0], qedf->mac);
पूर्ण

/*
 * Module Init/Remove
 */

अटल पूर्णांक __init qedf_init(व्योम)
अणु
	पूर्णांक ret;

	/* If debug=1 passed, set the शेष log mask */
	अगर (qedf_debug == QEDF_LOG_DEFAULT)
		qedf_debug = QEDF_DEFAULT_LOG_MASK;

	/*
	 * Check that शेष prio क्रम FIP/FCoE traffic is between 0..7 अगर a
	 * value has been set
	 */
	अगर (qedf_शेष_prio > -1)
		अगर (qedf_शेष_prio > 7) अणु
			qedf_शेष_prio = QEDF_DEFAULT_PRIO;
			QEDF_ERR(शून्य, "FCoE/FIP priority out of range, resetting to %d.\n",
			    QEDF_DEFAULT_PRIO);
		पूर्ण

	/* Prपूर्णांक driver banner */
	QEDF_INFO(शून्य, QEDF_LOG_INFO, "%s v%s.\n", QEDF_DESCR,
		   QEDF_VERSION);

	/* Create kmem_cache क्रम qedf_io_work काष्ठाs */
	qedf_io_work_cache = kmem_cache_create("qedf_io_work_cache",
	    माप(काष्ठा qedf_io_work), 0, SLAB_HWCACHE_ALIGN, शून्य);
	अगर (qedf_io_work_cache == शून्य) अणु
		QEDF_ERR(शून्य, "qedf_io_work_cache is NULL.\n");
		जाओ err1;
	पूर्ण
	QEDF_INFO(शून्य, QEDF_LOG_DISC, "qedf_io_work_cache=%p.\n",
	    qedf_io_work_cache);

	qed_ops = qed_get_fcoe_ops();
	अगर (!qed_ops) अणु
		QEDF_ERR(शून्य, "Failed to get qed fcoe operations\n");
		जाओ err1;
	पूर्ण

#अगर_घोषित CONFIG_DEBUG_FS
	qedf_dbg_init("qedf");
#पूर्ण_अगर

	qedf_fc_transport_ढाँचा =
	    fc_attach_transport(&qedf_fc_transport_fn);
	अगर (!qedf_fc_transport_ढाँचा) अणु
		QEDF_ERR(शून्य, "Could not register with FC transport\n");
		जाओ err2;
	पूर्ण

	qedf_fc_vport_transport_ढाँचा =
		fc_attach_transport(&qedf_fc_vport_transport_fn);
	अगर (!qedf_fc_vport_transport_ढाँचा) अणु
		QEDF_ERR(शून्य, "Could not register vport template with FC "
			  "transport\n");
		जाओ err3;
	पूर्ण

	qedf_io_wq = create_workqueue("qedf_io_wq");
	अगर (!qedf_io_wq) अणु
		QEDF_ERR(शून्य, "Could not create qedf_io_wq.\n");
		जाओ err4;
	पूर्ण

	qedf_cb_ops.get_login_failures = qedf_get_login_failures;

	ret = pci_रेजिस्टर_driver(&qedf_pci_driver);
	अगर (ret) अणु
		QEDF_ERR(शून्य, "Failed to register driver\n");
		जाओ err5;
	पूर्ण

	वापस 0;

err5:
	destroy_workqueue(qedf_io_wq);
err4:
	fc_release_transport(qedf_fc_vport_transport_ढाँचा);
err3:
	fc_release_transport(qedf_fc_transport_ढाँचा);
err2:
#अगर_घोषित CONFIG_DEBUG_FS
	qedf_dbg_निकास();
#पूर्ण_अगर
	qed_put_fcoe_ops();
err1:
	वापस -EINVAL;
पूर्ण

अटल व्योम __निकास qedf_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&qedf_pci_driver);

	destroy_workqueue(qedf_io_wq);

	fc_release_transport(qedf_fc_vport_transport_ढाँचा);
	fc_release_transport(qedf_fc_transport_ढाँचा);
#अगर_घोषित CONFIG_DEBUG_FS
	qedf_dbg_निकास();
#पूर्ण_अगर
	qed_put_fcoe_ops();

	kmem_cache_destroy(qedf_io_work_cache);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("QLogic FastLinQ 4xxxx FCoE Module");
MODULE_AUTHOR("QLogic Corporation");
MODULE_VERSION(QEDF_VERSION);
module_init(qedf_init);
module_निकास(qedf_cleanup);
