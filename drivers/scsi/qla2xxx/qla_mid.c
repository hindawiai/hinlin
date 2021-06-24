<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_gbl.h"
#समावेश "qla_target.h"

#समावेश <linux/moduleparam.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsicam.h>
#समावेश <linux/delay.h>

व्योम
qla2x00_vp_stop_समयr(scsi_qla_host_t *vha)
अणु
	अगर (vha->vp_idx && vha->समयr_active) अणु
		del_समयr_sync(&vha->समयr);
		vha->समयr_active = 0;
	पूर्ण
पूर्ण

अटल uपूर्णांक32_t
qla24xx_allocate_vp_id(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t vp_id;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;

	/* Find an empty slot and assign an vp_id */
	mutex_lock(&ha->vport_lock);
	vp_id = find_first_zero_bit(ha->vp_idx_map, ha->max_npiv_vports + 1);
	अगर (vp_id > ha->max_npiv_vports) अणु
		ql_dbg(ql_dbg_vport, vha, 0xa000,
		    "vp_id %d is bigger than max-supported %d.\n",
		    vp_id, ha->max_npiv_vports);
		mutex_unlock(&ha->vport_lock);
		वापस vp_id;
	पूर्ण

	set_bit(vp_id, ha->vp_idx_map);
	ha->num_vhosts++;
	vha->vp_idx = vp_id;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_add_tail(&vha->list, &ha->vp_list);
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	qlt_update_vp_map(vha, SET_VP_IDX);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	mutex_unlock(&ha->vport_lock);
	वापस vp_id;
पूर्ण

व्योम
qla24xx_deallocate_vp_id(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t vp_id;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags = 0;
	u8 i;

	mutex_lock(&ha->vport_lock);
	/*
	 * Wait क्रम all pending activities to finish beक्रमe removing vport from
	 * the list.
	 * Lock needs to be held क्रम safe removal from the list (it
	 * ensures no active vp_list traversal जबतक the vport is हटाओd
	 * from the queue)
	 */
	क्रम (i = 0; i < 10; i++) अणु
		अगर (रुको_event_समयout(vha->vref_रुकोq,
		    !atomic_पढ़ो(&vha->vref_count), HZ) > 0)
			अवरोध;
	पूर्ण

	spin_lock_irqsave(&ha->vport_slock, flags);
	अगर (atomic_पढ़ो(&vha->vref_count)) अणु
		ql_dbg(ql_dbg_vport, vha, 0xfffa,
		    "vha->vref_count=%u timeout\n", vha->vref_count.counter);
		vha->vref_count = (atomic_t)ATOMIC_INIT(0);
	पूर्ण
	list_del(&vha->list);
	qlt_update_vp_map(vha, RESET_VP_IDX);
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	vp_id = vha->vp_idx;
	ha->num_vhosts--;
	clear_bit(vp_id, ha->vp_idx_map);

	mutex_unlock(&ha->vport_lock);
पूर्ण

अटल scsi_qla_host_t *
qla24xx_find_vhost_by_name(काष्ठा qla_hw_data *ha, uपूर्णांक8_t *port_name)
अणु
	scsi_qla_host_t *vha;
	काष्ठा scsi_qla_host *tvha;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->vport_slock, flags);
	/* Locate matching device in database. */
	list_क्रम_each_entry_safe(vha, tvha, &ha->vp_list, list) अणु
		अगर (!स_भेद(port_name, vha->port_name, WWN_SIZE)) अणु
			spin_unlock_irqrestore(&ha->vport_slock, flags);
			वापस vha;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);
	वापस शून्य;
पूर्ण

/*
 * qla2x00_mark_vp_devices_dead
 *	Updates fcport state when device goes offline.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	fcport = port काष्ठाure poपूर्णांकer.
 *
 * Return:
 *	None.
 *
 * Context:
 */
अटल व्योम
qla2x00_mark_vp_devices_dead(scsi_qla_host_t *vha)
अणु
	/*
	 * !!! NOTE !!!
	 * This function, अगर called in contexts other than vp create, disable
	 * or delete, please make sure this is synchronized with the
	 * delete thपढ़ो.
	 */
	fc_port_t *fcport;

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		ql_dbg(ql_dbg_vport, vha, 0xa001,
		    "Marking port dead, loop_id=0x%04x : %x.\n",
		    fcport->loop_id, fcport->vha->vp_idx);

		qla2x00_mark_device_lost(vha, fcport, 0);
		qla2x00_set_fcport_state(fcport, FCS_UNCONFIGURED);
	पूर्ण
पूर्ण

पूर्णांक
qla24xx_disable_vp(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = QLA_SUCCESS;
	fc_port_t *fcport;

	अगर (vha->hw->flags.fw_started)
		ret = qla24xx_control_vp(vha, VCE_COMMAND_DISABLE_VPS_LOGO_ALL);

	atomic_set(&vha->loop_state, LOOP_DOWN);
	atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list)
		fcport->logout_on_delete = 0;

	qla2x00_mark_all_devices_lost(vha);

	/* Remove port id from vp target map */
	spin_lock_irqsave(&vha->hw->hardware_lock, flags);
	qlt_update_vp_map(vha, RESET_AL_PA);
	spin_unlock_irqrestore(&vha->hw->hardware_lock, flags);

	qla2x00_mark_vp_devices_dead(vha);
	atomic_set(&vha->vp_state, VP_FAILED);
	vha->flags.management_server_logged_in = 0;
	अगर (ret == QLA_SUCCESS) अणु
		fc_vport_set_state(vha->fc_vport, FC_VPORT_DISABLED);
	पूर्ण अन्यथा अणु
		fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक
qla24xx_enable_vp(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret;
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	/* Check अगर physical ha port is Up */
	अगर (atomic_पढ़ो(&base_vha->loop_state) == LOOP_DOWN  ||
		atomic_पढ़ो(&base_vha->loop_state) == LOOP_DEAD ||
		!(ha->current_topology & ISP_CFG_F)) अणु
		vha->vp_err_state =  VP_ERR_PORTDWN;
		fc_vport_set_state(vha->fc_vport, FC_VPORT_LINKDOWN);
		ql_dbg(ql_dbg_taskm, vha, 0x800b,
		    "%s skip enable. loop_state %x topo %x\n",
		    __func__, base_vha->loop_state.counter,
		    ha->current_topology);

		जाओ enable_failed;
	पूर्ण

	/* Initialize the new vport unless it is a persistent port */
	mutex_lock(&ha->vport_lock);
	ret = qla24xx_modअगरy_vp_config(vha);
	mutex_unlock(&ha->vport_lock);

	अगर (ret != QLA_SUCCESS) अणु
		fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		जाओ enable_failed;
	पूर्ण

	ql_dbg(ql_dbg_taskm, vha, 0x801a,
	    "Virtual port with id: %d - Enabled.\n", vha->vp_idx);
	वापस 0;

enable_failed:
	ql_dbg(ql_dbg_taskm, vha, 0x801b,
	    "Virtual port with id: %d - Disabled.\n", vha->vp_idx);
	वापस 1;
पूर्ण

अटल व्योम
qla24xx_configure_vp(scsi_qla_host_t *vha)
अणु
	काष्ठा fc_vport *fc_vport;
	पूर्णांक ret;

	fc_vport = vha->fc_vport;

	ql_dbg(ql_dbg_vport, vha, 0xa002,
	    "%s: change request #3.\n", __func__);
	ret = qla2x00_send_change_request(vha, 0x3, vha->vp_idx);
	अगर (ret != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_vport, vha, 0xa003, "Failed to enable "
		    "receiving of RSCN requests: 0x%x.\n", ret);
		वापस;
	पूर्ण अन्यथा अणु
		/* Corresponds to SCR enabled */
		clear_bit(VP_SCR_NEEDED, &vha->vp_flags);
	पूर्ण

	vha->flags.online = 1;
	अगर (qla24xx_configure_vhba(vha))
		वापस;

	atomic_set(&vha->vp_state, VP_ACTIVE);
	fc_vport_set_state(fc_vport, FC_VPORT_ACTIVE);
पूर्ण

व्योम
qla2x00_alert_all_vps(काष्ठा rsp_que *rsp, uपूर्णांक16_t *mb)
अणु
	scsi_qla_host_t *vha;
	काष्ठा qla_hw_data *ha = rsp->hw;
	पूर्णांक i = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vha, &ha->vp_list, list) अणु
		अगर (vha->vp_idx) अणु
			अगर (test_bit(VPORT_DELETE, &vha->dpc_flags))
				जारी;

			atomic_inc(&vha->vref_count);
			spin_unlock_irqrestore(&ha->vport_slock, flags);

			चयन (mb[0]) अणु
			हाल MBA_LIP_OCCURRED:
			हाल MBA_LOOP_UP:
			हाल MBA_LOOP_DOWN:
			हाल MBA_LIP_RESET:
			हाल MBA_POINT_TO_POINT:
			हाल MBA_CHG_IN_CONNECTION:
				ql_dbg(ql_dbg_async, vha, 0x5024,
				    "Async_event for VP[%d], mb=0x%x vha=%p.\n",
				    i, *mb, vha);
				qla2x00_async_event(vha, rsp, mb);
				अवरोध;
			हाल MBA_PORT_UPDATE:
			हाल MBA_RSCN_UPDATE:
				अगर ((mb[3] & 0xff) == vha->vp_idx) अणु
					ql_dbg(ql_dbg_async, vha, 0x5024,
					    "Async_event for VP[%d], mb=0x%x vha=%p\n",
					    i, *mb, vha);
					qla2x00_async_event(vha, rsp, mb);
				पूर्ण
				अवरोध;
			पूर्ण

			spin_lock_irqsave(&ha->vport_slock, flags);
			atomic_dec(&vha->vref_count);
			wake_up(&vha->vref_रुकोq);
		पूर्ण
		i++;
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);
पूर्ण

पूर्णांक
qla2x00_vp_पात_isp(scsi_qla_host_t *vha)
अणु
	fc_port_t *fcport;

	/*
	 * To exclusively reset vport, we need to log it out first.
	 * Note: This control_vp can fail अगर ISP reset is alपढ़ोy
	 * issued, this is expected, as the vp would be alपढ़ोy
	 * logged out due to ISP reset.
	 */
	अगर (!test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) अणु
		qla24xx_control_vp(vha, VCE_COMMAND_DISABLE_VPS_LOGO_ALL);
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list)
			fcport->logout_on_delete = 0;
	पूर्ण

	/*
	 * Physical port will करो most of the पात and recovery work. We can
	 * just treat it as a loop करोwn
	 */
	अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
		atomic_set(&vha->loop_state, LOOP_DOWN);
		qla2x00_mark_all_devices_lost(vha);
	पूर्ण अन्यथा अणु
		अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr))
			atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
	पूर्ण

	ql_dbg(ql_dbg_taskm, vha, 0x801d,
	    "Scheduling enable of Vport %d.\n", vha->vp_idx);

	वापस qla24xx_enable_vp(vha);
पूर्ण

अटल पूर्णांक
qla2x00_करो_dpc_vp(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	ql_dbg(ql_dbg_dpc + ql_dbg_verbose, vha, 0x4012,
	    "Entering %s vp_flags: 0x%lx.\n", __func__, vha->vp_flags);

	/* Check अगर Fw is पढ़ोy to configure VP first */
	अगर (test_bit(VP_CONFIG_OK, &base_vha->vp_flags)) अणु
		अगर (test_and_clear_bit(VP_IDX_ACQUIRED, &vha->vp_flags)) अणु
			/* VP acquired. complete port configuration */
			ql_dbg(ql_dbg_dpc, vha, 0x4014,
			    "Configure VP scheduled.\n");
			qla24xx_configure_vp(vha);
			ql_dbg(ql_dbg_dpc, vha, 0x4015,
			    "Configure VP end.\n");
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (test_bit(PROCESS_PUREX_IOCB, &vha->dpc_flags)) अणु
		अगर (atomic_पढ़ो(&vha->loop_state) == LOOP_READY) अणु
			qla24xx_process_purex_list(&vha->purex_list);
			clear_bit(PROCESS_PUREX_IOCB, &vha->dpc_flags);
		पूर्ण
	पूर्ण

	अगर (test_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags)) अणु
		ql_dbg(ql_dbg_dpc, vha, 0x4016,
		    "FCPort update scheduled.\n");
		qla2x00_update_fcports(vha);
		clear_bit(FCPORT_UPDATE_NEEDED, &vha->dpc_flags);
		ql_dbg(ql_dbg_dpc, vha, 0x4017,
		    "FCPort update end.\n");
	पूर्ण

	अगर (test_bit(RELOGIN_NEEDED, &vha->dpc_flags) &&
	    !test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags) &&
	    atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु

		अगर (!vha->relogin_jअगर ||
		    समय_after_eq(jअगरfies, vha->relogin_jअगर)) अणु
			vha->relogin_jअगर = jअगरfies + HZ;
			clear_bit(RELOGIN_NEEDED, &vha->dpc_flags);

			ql_dbg(ql_dbg_dpc, vha, 0x4018,
			    "Relogin needed scheduled.\n");
			qla24xx_post_relogin_work(vha);
		पूर्ण
	पूर्ण

	अगर (test_and_clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags) &&
	    (!(test_and_set_bit(RESET_ACTIVE, &vha->dpc_flags)))) अणु
		clear_bit(RESET_ACTIVE, &vha->dpc_flags);
	पूर्ण

	अगर (test_and_clear_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags)) अणु
		अगर (!(test_and_set_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags))) अणु
			ql_dbg(ql_dbg_dpc, vha, 0x401a,
			    "Loop resync scheduled.\n");
			qla2x00_loop_resync(vha);
			clear_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags);
			ql_dbg(ql_dbg_dpc, vha, 0x401b,
			    "Loop resync end.\n");
		पूर्ण
	पूर्ण

	ql_dbg(ql_dbg_dpc + ql_dbg_verbose, vha, 0x401c,
	    "Exiting %s.\n", __func__);
	वापस 0;
पूर्ण

व्योम
qla2x00_करो_dpc_all_vps(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *vp;
	अचिन्हित दीर्घ flags = 0;

	अगर (vha->vp_idx)
		वापस;
	अगर (list_empty(&ha->vp_list))
		वापस;

	clear_bit(VP_DPC_NEEDED, &vha->dpc_flags);

	अगर (!(ha->current_topology & ISP_CFG_F))
		वापस;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
		अगर (vp->vp_idx) अणु
			atomic_inc(&vp->vref_count);
			spin_unlock_irqrestore(&ha->vport_slock, flags);

			qla2x00_करो_dpc_vp(vp);

			spin_lock_irqsave(&ha->vport_slock, flags);
			atomic_dec(&vp->vref_count);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);
पूर्ण

पूर्णांक
qla24xx_vport_create_req_sanity_check(काष्ठा fc_vport *fc_vport)
अणु
	scsi_qla_host_t *base_vha = shost_priv(fc_vport->shost);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	scsi_qla_host_t *vha;
	uपूर्णांक8_t port_name[WWN_SIZE];

	अगर (fc_vport->roles != FC_PORT_ROLE_FCP_INITIATOR)
		वापस VPCERR_UNSUPPORTED;

	/* Check up the F/W and H/W support NPIV */
	अगर (!ha->flags.npiv_supported)
		वापस VPCERR_UNSUPPORTED;

	/* Check up whether npiv supported चयन presented */
	अगर (!(ha->चयन_cap & FLOGI_MID_SUPPORT))
		वापस VPCERR_NO_FABRIC_SUPP;

	/* Check up unique WWPN */
	u64_to_wwn(fc_vport->port_name, port_name);
	अगर (!स_भेद(port_name, base_vha->port_name, WWN_SIZE))
		वापस VPCERR_BAD_WWN;
	vha = qla24xx_find_vhost_by_name(ha, port_name);
	अगर (vha)
		वापस VPCERR_BAD_WWN;

	/* Check up max-npiv-supports */
	अगर (ha->num_vhosts > ha->max_npiv_vports) अणु
		ql_dbg(ql_dbg_vport, vha, 0xa004,
		    "num_vhosts %ud is bigger "
		    "than max_npiv_vports %ud.\n",
		    ha->num_vhosts, ha->max_npiv_vports);
		वापस VPCERR_UNSUPPORTED;
	पूर्ण
	वापस 0;
पूर्ण

scsi_qla_host_t *
qla24xx_create_vhost(काष्ठा fc_vport *fc_vport)
अणु
	scsi_qla_host_t *base_vha = shost_priv(fc_vport->shost);
	काष्ठा qla_hw_data *ha = base_vha->hw;
	scsi_qla_host_t *vha;
	काष्ठा scsi_host_ढाँचा *sht = &qla2xxx_driver_ढाँचा;
	काष्ठा Scsi_Host *host;

	vha = qla2x00_create_host(sht, ha);
	अगर (!vha) अणु
		ql_log(ql_log_warn, vha, 0xa005,
		    "scsi_host_alloc() failed for vport.\n");
		वापस(शून्य);
	पूर्ण

	host = vha->host;
	fc_vport->dd_data = vha;
	/* New host info */
	u64_to_wwn(fc_vport->node_name, vha->node_name);
	u64_to_wwn(fc_vport->port_name, vha->port_name);

	vha->fc_vport = fc_vport;
	vha->device_flags = 0;
	vha->vp_idx = qla24xx_allocate_vp_id(vha);
	अगर (vha->vp_idx > ha->max_npiv_vports) अणु
		ql_dbg(ql_dbg_vport, vha, 0xa006,
		    "Couldn't allocate vp_id.\n");
		जाओ create_vhost_failed;
	पूर्ण
	vha->mgmt_svr_loop_id = qla2x00_reserve_mgmt_server_loop_id(vha);

	vha->dpc_flags = 0L;
	ha->dpc_active = 0;
	set_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags);
	set_bit(REGISTER_FC4_NEEDED, &vha->dpc_flags);

	/*
	 * To fix the issue of processing a parent's RSCN क्रम the vport beक्रमe
	 * its SCR is complete.
	 */
	set_bit(VP_SCR_NEEDED, &vha->vp_flags);
	atomic_set(&vha->loop_state, LOOP_DOWN);
	atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);

	qla2x00_start_समयr(vha, WATCH_INTERVAL);

	vha->req = base_vha->req;
	vha->flags.nvme_enabled = base_vha->flags.nvme_enabled;
	host->can_queue = base_vha->req->length + 128;
	host->cmd_per_lun = 3;
	अगर (IS_T10_PI_CAPABLE(ha) && ql2xenabledअगर)
		host->max_cmd_len = 32;
	अन्यथा
		host->max_cmd_len = MAX_CMDSZ;
	host->max_channel = MAX_BUSES - 1;
	host->max_lun = ql2xmaxlun;
	host->unique_id = host->host_no;
	host->max_id = ha->max_fibre_devices;
	host->transportt = qla2xxx_transport_vport_ढाँचा;

	ql_dbg(ql_dbg_vport, vha, 0xa007,
	    "Detect vport hba %ld at address = %p.\n",
	    vha->host_no, vha);

	vha->flags.init_करोne = 1;

	mutex_lock(&ha->vport_lock);
	set_bit(vha->vp_idx, ha->vp_idx_map);
	ha->cur_vport_count++;
	mutex_unlock(&ha->vport_lock);

	वापस vha;

create_vhost_failed:
	वापस शून्य;
पूर्ण

अटल व्योम
qla25xx_मुक्त_req_que(काष्ठा scsi_qla_host *vha, काष्ठा req_que *req)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t que_id = req->id;

	dma_मुक्त_coherent(&ha->pdev->dev, (req->length + 1) *
		माप(request_t), req->ring, req->dma);
	req->ring = शून्य;
	req->dma = 0;
	अगर (que_id) अणु
		ha->req_q_map[que_id] = शून्य;
		mutex_lock(&ha->vport_lock);
		clear_bit(que_id, ha->req_qid_map);
		mutex_unlock(&ha->vport_lock);
	पूर्ण
	kमुक्त(req->outstanding_cmds);
	kमुक्त(req);
	req = शून्य;
पूर्ण

अटल व्योम
qla25xx_मुक्त_rsp_que(काष्ठा scsi_qla_host *vha, काष्ठा rsp_que *rsp)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t que_id = rsp->id;

	अगर (rsp->msix && rsp->msix->have_irq) अणु
		मुक्त_irq(rsp->msix->vector, rsp->msix->handle);
		rsp->msix->have_irq = 0;
		rsp->msix->in_use = 0;
		rsp->msix->handle = शून्य;
	पूर्ण
	dma_मुक्त_coherent(&ha->pdev->dev, (rsp->length + 1) *
		माप(response_t), rsp->ring, rsp->dma);
	rsp->ring = शून्य;
	rsp->dma = 0;
	अगर (que_id) अणु
		ha->rsp_q_map[que_id] = शून्य;
		mutex_lock(&ha->vport_lock);
		clear_bit(que_id, ha->rsp_qid_map);
		mutex_unlock(&ha->vport_lock);
	पूर्ण
	kमुक्त(rsp);
	rsp = शून्य;
पूर्ण

पूर्णांक
qla25xx_delete_req_que(काष्ठा scsi_qla_host *vha, काष्ठा req_que *req)
अणु
	पूर्णांक ret = QLA_SUCCESS;

	अगर (req && vha->flags.qpairs_req_created) अणु
		req->options |= BIT_0;
		ret = qla25xx_init_req_que(vha, req);
		अगर (ret != QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;

		qla25xx_मुक्त_req_que(vha, req);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
qla25xx_delete_rsp_que(काष्ठा scsi_qla_host *vha, काष्ठा rsp_que *rsp)
अणु
	पूर्णांक ret = QLA_SUCCESS;

	अगर (rsp && vha->flags.qpairs_rsp_created) अणु
		rsp->options |= BIT_0;
		ret = qla25xx_init_rsp_que(vha, rsp);
		अगर (ret != QLA_SUCCESS)
			वापस QLA_FUNCTION_FAILED;

		qla25xx_मुक्त_rsp_que(vha, rsp);
	पूर्ण

	वापस ret;
पूर्ण

/* Delete all queues क्रम a given vhost */
पूर्णांक
qla25xx_delete_queues(काष्ठा scsi_qla_host *vha)
अणु
	पूर्णांक cnt, ret = 0;
	काष्ठा req_que *req = शून्य;
	काष्ठा rsp_que *rsp = शून्य;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_qpair *qpair, *tqpair;

	अगर (ql2xmqsupport || ql2xnvmeenable) अणु
		list_क्रम_each_entry_safe(qpair, tqpair, &vha->qp_list,
		    qp_list_elem)
			qla2xxx_delete_qpair(vha, qpair);
	पूर्ण अन्यथा अणु
		/* Delete request queues */
		क्रम (cnt = 1; cnt < ha->max_req_queues; cnt++) अणु
			req = ha->req_q_map[cnt];
			अगर (req && test_bit(cnt, ha->req_qid_map)) अणु
				ret = qla25xx_delete_req_que(vha, req);
				अगर (ret != QLA_SUCCESS) अणु
					ql_log(ql_log_warn, vha, 0x00ea,
					    "Couldn't delete req que %d.\n",
					    req->id);
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण

		/* Delete response queues */
		क्रम (cnt = 1; cnt < ha->max_rsp_queues; cnt++) अणु
			rsp = ha->rsp_q_map[cnt];
			अगर (rsp && test_bit(cnt, ha->rsp_qid_map)) अणु
				ret = qla25xx_delete_rsp_que(vha, rsp);
				अगर (ret != QLA_SUCCESS) अणु
					ql_log(ql_log_warn, vha, 0x00eb,
					    "Couldn't delete rsp que %d.\n",
					    rsp->id);
					वापस ret;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक
qla25xx_create_req_que(काष्ठा qla_hw_data *ha, uपूर्णांक16_t options,
    uपूर्णांक8_t vp_idx, uपूर्णांक16_t rid, पूर्णांक rsp_que, uपूर्णांक8_t qos, bool startqp)
अणु
	पूर्णांक ret = 0;
	काष्ठा req_que *req = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	काष्ठा scsi_qla_host *vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक16_t que_id = 0;
	device_reg_t *reg;
	uपूर्णांक32_t cnt;

	req = kzalloc(माप(काष्ठा req_que), GFP_KERNEL);
	अगर (req == शून्य) अणु
		ql_log(ql_log_fatal, base_vha, 0x00d9,
		    "Failed to allocate memory for request queue.\n");
		जाओ failed;
	पूर्ण

	req->length = REQUEST_ENTRY_CNT_24XX;
	req->ring = dma_alloc_coherent(&ha->pdev->dev,
			(req->length + 1) * माप(request_t),
			&req->dma, GFP_KERNEL);
	अगर (req->ring == शून्य) अणु
		ql_log(ql_log_fatal, base_vha, 0x00da,
		    "Failed to allocate memory for request_ring.\n");
		जाओ que_failed;
	पूर्ण

	ret = qla2x00_alloc_outstanding_cmds(ha, req);
	अगर (ret != QLA_SUCCESS)
		जाओ que_failed;

	mutex_lock(&ha->mq_lock);
	que_id = find_first_zero_bit(ha->req_qid_map, ha->max_req_queues);
	अगर (que_id >= ha->max_req_queues) अणु
		mutex_unlock(&ha->mq_lock);
		ql_log(ql_log_warn, base_vha, 0x00db,
		    "No resources to create additional request queue.\n");
		जाओ que_failed;
	पूर्ण
	set_bit(que_id, ha->req_qid_map);
	ha->req_q_map[que_id] = req;
	req->rid = rid;
	req->vp_idx = vp_idx;
	req->qos = qos;

	ql_dbg(ql_dbg_multiq, base_vha, 0xc002,
	    "queue_id=%d rid=%d vp_idx=%d qos=%d.\n",
	    que_id, req->rid, req->vp_idx, req->qos);
	ql_dbg(ql_dbg_init, base_vha, 0x00dc,
	    "queue_id=%d rid=%d vp_idx=%d qos=%d.\n",
	    que_id, req->rid, req->vp_idx, req->qos);
	अगर (rsp_que < 0)
		req->rsp = शून्य;
	अन्यथा
		req->rsp = ha->rsp_q_map[rsp_que];
	/* Use alternate PCI bus number */
	अगर (MSB(req->rid))
		options |= BIT_4;
	/* Use alternate PCI devfn */
	अगर (LSB(req->rid))
		options |= BIT_5;
	req->options = options;

	ql_dbg(ql_dbg_multiq, base_vha, 0xc003,
	    "options=0x%x.\n", req->options);
	ql_dbg(ql_dbg_init, base_vha, 0x00dd,
	    "options=0x%x.\n", req->options);
	क्रम (cnt = 1; cnt < req->num_outstanding_cmds; cnt++)
		req->outstanding_cmds[cnt] = शून्य;
	req->current_outstanding_cmd = 1;

	req->ring_ptr = req->ring;
	req->ring_index = 0;
	req->cnt = req->length;
	req->id = que_id;
	reg = ISP_QUE_REG(ha, que_id);
	req->req_q_in = &reg->isp25mq.req_q_in;
	req->req_q_out = &reg->isp25mq.req_q_out;
	req->max_q_depth = ha->req_q_map[0]->max_q_depth;
	req->out_ptr = (uपूर्णांक16_t *)(req->ring + req->length);
	mutex_unlock(&ha->mq_lock);
	ql_dbg(ql_dbg_multiq, base_vha, 0xc004,
	    "ring_ptr=%p ring_index=%d, "
	    "cnt=%d id=%d max_q_depth=%d.\n",
	    req->ring_ptr, req->ring_index,
	    req->cnt, req->id, req->max_q_depth);
	ql_dbg(ql_dbg_init, base_vha, 0x00de,
	    "ring_ptr=%p ring_index=%d, "
	    "cnt=%d id=%d max_q_depth=%d.\n",
	    req->ring_ptr, req->ring_index, req->cnt,
	    req->id, req->max_q_depth);

	अगर (startqp) अणु
		ret = qla25xx_init_req_que(base_vha, req);
		अगर (ret != QLA_SUCCESS) अणु
			ql_log(ql_log_fatal, base_vha, 0x00df,
			    "%s failed.\n", __func__);
			mutex_lock(&ha->mq_lock);
			clear_bit(que_id, ha->req_qid_map);
			mutex_unlock(&ha->mq_lock);
			जाओ que_failed;
		पूर्ण
		vha->flags.qpairs_req_created = 1;
	पूर्ण

	वापस req->id;

que_failed:
	qla25xx_मुक्त_req_que(base_vha, req);
failed:
	वापस 0;
पूर्ण

अटल व्योम qla_करो_work(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qla_qpair *qpair = container_of(work, काष्ठा qla_qpair, q_work);
	काष्ठा scsi_qla_host *vha = qpair->vha;

	spin_lock_irqsave(&qpair->qp_lock, flags);
	qla24xx_process_response_queue(vha, qpair->rsp);
	spin_unlock_irqrestore(&qpair->qp_lock, flags);

पूर्ण

/* create response queue */
पूर्णांक
qla25xx_create_rsp_que(काष्ठा qla_hw_data *ha, uपूर्णांक16_t options,
    uपूर्णांक8_t vp_idx, uपूर्णांक16_t rid, काष्ठा qla_qpair *qpair, bool startqp)
अणु
	पूर्णांक ret = 0;
	काष्ठा rsp_que *rsp = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	काष्ठा scsi_qla_host *vha = pci_get_drvdata(ha->pdev);
	uपूर्णांक16_t que_id = 0;
	device_reg_t *reg;

	rsp = kzalloc(माप(काष्ठा rsp_que), GFP_KERNEL);
	अगर (rsp == शून्य) अणु
		ql_log(ql_log_warn, base_vha, 0x0066,
		    "Failed to allocate memory for response queue.\n");
		जाओ failed;
	पूर्ण

	rsp->length = RESPONSE_ENTRY_CNT_MQ;
	rsp->ring = dma_alloc_coherent(&ha->pdev->dev,
			(rsp->length + 1) * माप(response_t),
			&rsp->dma, GFP_KERNEL);
	अगर (rsp->ring == शून्य) अणु
		ql_log(ql_log_warn, base_vha, 0x00e1,
		    "Failed to allocate memory for response ring.\n");
		जाओ que_failed;
	पूर्ण

	mutex_lock(&ha->mq_lock);
	que_id = find_first_zero_bit(ha->rsp_qid_map, ha->max_rsp_queues);
	अगर (que_id >= ha->max_rsp_queues) अणु
		mutex_unlock(&ha->mq_lock);
		ql_log(ql_log_warn, base_vha, 0x00e2,
		    "No resources to create additional request queue.\n");
		जाओ que_failed;
	पूर्ण
	set_bit(que_id, ha->rsp_qid_map);

	rsp->msix = qpair->msix;

	ha->rsp_q_map[que_id] = rsp;
	rsp->rid = rid;
	rsp->vp_idx = vp_idx;
	rsp->hw = ha;
	ql_dbg(ql_dbg_init, base_vha, 0x00e4,
	    "rsp queue_id=%d rid=%d vp_idx=%d hw=%p.\n",
	    que_id, rsp->rid, rsp->vp_idx, rsp->hw);
	/* Use alternate PCI bus number */
	अगर (MSB(rsp->rid))
		options |= BIT_4;
	/* Use alternate PCI devfn */
	अगर (LSB(rsp->rid))
		options |= BIT_5;
	/* Enable MSIX handshake mode on क्रम uncapable adapters */
	अगर (!IS_MSIX_NACK_CAPABLE(ha))
		options |= BIT_6;

	/* Set option to indicate response queue creation */
	options |= BIT_1;

	rsp->options = options;
	rsp->id = que_id;
	reg = ISP_QUE_REG(ha, que_id);
	rsp->rsp_q_in = &reg->isp25mq.rsp_q_in;
	rsp->rsp_q_out = &reg->isp25mq.rsp_q_out;
	rsp->in_ptr = (uपूर्णांक16_t *)(rsp->ring + rsp->length);
	mutex_unlock(&ha->mq_lock);
	ql_dbg(ql_dbg_multiq, base_vha, 0xc00b,
	    "options=%x id=%d rsp_q_in=%p rsp_q_out=%p\n",
	    rsp->options, rsp->id, rsp->rsp_q_in,
	    rsp->rsp_q_out);
	ql_dbg(ql_dbg_init, base_vha, 0x00e5,
	    "options=%x id=%d rsp_q_in=%p rsp_q_out=%p\n",
	    rsp->options, rsp->id, rsp->rsp_q_in,
	    rsp->rsp_q_out);

	ret = qla25xx_request_irq(ha, qpair, qpair->msix,
		ha->flags.disable_msix_handshake ?
		QLA_MSIX_QPAIR_MULTIQ_RSP_Q : QLA_MSIX_QPAIR_MULTIQ_RSP_Q_HS);
	अगर (ret)
		जाओ que_failed;

	अगर (startqp) अणु
		ret = qla25xx_init_rsp_que(base_vha, rsp);
		अगर (ret != QLA_SUCCESS) अणु
			ql_log(ql_log_fatal, base_vha, 0x00e7,
			    "%s failed.\n", __func__);
			mutex_lock(&ha->mq_lock);
			clear_bit(que_id, ha->rsp_qid_map);
			mutex_unlock(&ha->mq_lock);
			जाओ que_failed;
		पूर्ण
		vha->flags.qpairs_rsp_created = 1;
	पूर्ण
	rsp->req = शून्य;

	qla2x00_init_response_q_entries(rsp);
	अगर (qpair->hw->wq)
		INIT_WORK(&qpair->q_work, qla_करो_work);
	वापस rsp->id;

que_failed:
	qla25xx_मुक्त_rsp_que(base_vha, rsp);
failed:
	वापस 0;
पूर्ण

अटल व्योम qla_ctrlvp_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	अगर (sp->comp)
		complete(sp->comp);
	/* करोn't मुक्त sp here. Let the caller करो the मुक्त */
पूर्ण

/**
 * qla24xx_control_vp() - Enable a भव port क्रम given host
 * @vha:	adapter block poपूर्णांकer
 * @cmd:	command type to be sent क्रम enable भव port
 *
 * Return:	qla2xxx local function वापस status code.
 */
पूर्णांक qla24xx_control_vp(scsi_qla_host_t *vha, पूर्णांक cmd)
अणु
	पूर्णांक rval = QLA_MEMORY_ALLOC_FAILED;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक	vp_index = vha->vp_idx;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	DECLARE_COMPLETION_ONSTACK(comp);
	srb_t *sp;

	ql_dbg(ql_dbg_vport, vha, 0x10c1,
	    "Entered %s cmd %x index %d.\n", __func__, cmd, vp_index);

	अगर (vp_index == 0 || vp_index >= ha->max_npiv_vports)
		वापस QLA_PARAMETER_ERROR;

	sp = qla2x00_get_sp(base_vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		वापस rval;

	sp->type = SRB_CTRL_VP;
	sp->name = "ctrl_vp";
	sp->comp = &comp;
	sp->करोne = qla_ctrlvp_sp_करोne;
	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);
	sp->u.iocb_cmd.u.ctrlvp.cmd = cmd;
	sp->u.iocb_cmd.u.ctrlvp.vp_index = vp_index;

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_async, vha, 0xffff,
		    "%s: %s Failed submission. %x.\n",
		    __func__, sp->name, rval);
		जाओ करोne;
	पूर्ण

	ql_dbg(ql_dbg_vport, vha, 0x113f, "%s hndl %x submitted\n",
	    sp->name, sp->handle);

	रुको_क्रम_completion(&comp);
	sp->comp = शून्य;

	rval = sp->rc;
	चयन (rval) अणु
	हाल QLA_FUNCTION_TIMEOUT:
		ql_dbg(ql_dbg_vport, vha, 0xffff, "%s: %s Timeout. %x.\n",
		    __func__, sp->name, rval);
		अवरोध;
	हाल QLA_SUCCESS:
		ql_dbg(ql_dbg_vport, vha, 0xffff, "%s: %s done.\n",
		    __func__, sp->name);
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_vport, vha, 0xffff, "%s: %s Failed. %x.\n",
		    __func__, sp->name, rval);
		अवरोध;
	पूर्ण
करोne:
	sp->मुक्त(sp);
	वापस rval;
पूर्ण
