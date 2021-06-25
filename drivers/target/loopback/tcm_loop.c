<शैली गुरु>
/*******************************************************************************
 *
 * This file contains the Linux/SCSI LLD भव SCSI initiator driver
 * क्रम emulated SAS initiator ports
 *
 * तऊ Copyright 2011-2013 Datera, Inc.
 *
 * Licensed to the Linux Foundation under the General Public License (GPL) version 2.
 *
 * Author: Nicholas A. Bellinger <nab@risingtideप्रणालीs.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 ****************************************************************************/

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <linux/configfs.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_cmnd.h>

#समावेश <target/target_core_base.h>
#समावेश <target/target_core_fabric.h>

#समावेश "tcm_loop.h"

#घोषणा to_tcm_loop_hba(hba)	container_of(hba, काष्ठा tcm_loop_hba, dev)

अटल काष्ठा kmem_cache *tcm_loop_cmd_cache;

अटल पूर्णांक tcm_loop_hba_no_cnt;

अटल पूर्णांक tcm_loop_queue_status(काष्ठा se_cmd *se_cmd);

अटल अचिन्हित पूर्णांक tcm_loop_nr_hw_queues = 1;
module_param_named(nr_hw_queues, tcm_loop_nr_hw_queues, uपूर्णांक, 0644);

अटल अचिन्हित पूर्णांक tcm_loop_can_queue = 1024;
module_param_named(can_queue, tcm_loop_can_queue, uपूर्णांक, 0644);

अटल अचिन्हित पूर्णांक tcm_loop_cmd_per_lun = 1024;
module_param_named(cmd_per_lun, tcm_loop_cmd_per_lun, uपूर्णांक, 0644);

/*
 * Called from काष्ठा target_core_fabric_ops->check_stop_मुक्त()
 */
अटल पूर्णांक tcm_loop_check_stop_मुक्त(काष्ठा se_cmd *se_cmd)
अणु
	वापस transport_generic_मुक्त_cmd(se_cmd, 0);
पूर्ण

अटल व्योम tcm_loop_release_cmd(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा tcm_loop_cmd *tl_cmd = container_of(se_cmd,
				काष्ठा tcm_loop_cmd, tl_se_cmd);
	काष्ठा scsi_cmnd *sc = tl_cmd->sc;

	अगर (se_cmd->se_cmd_flags & SCF_SCSI_TMR_CDB)
		kmem_cache_मुक्त(tcm_loop_cmd_cache, tl_cmd);
	अन्यथा
		sc->scsi_करोne(sc);
पूर्ण

अटल पूर्णांक tcm_loop_show_info(काष्ठा seq_file *m, काष्ठा Scsi_Host *host)
अणु
	seq_माला_दो(m, "tcm_loop_proc_info()\n");
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_driver_probe(काष्ठा device *);
अटल पूर्णांक tcm_loop_driver_हटाओ(काष्ठा device *);

अटल पूर्णांक pseuकरो_lld_bus_match(काष्ठा device *dev,
				काष्ठा device_driver *dev_driver)
अणु
	वापस 1;
पूर्ण

अटल काष्ठा bus_type tcm_loop_lld_bus = अणु
	.name			= "tcm_loop_bus",
	.match			= pseuकरो_lld_bus_match,
	.probe			= tcm_loop_driver_probe,
	.हटाओ			= tcm_loop_driver_हटाओ,
पूर्ण;

अटल काष्ठा device_driver tcm_loop_driverfs = अणु
	.name			= "tcm_loop",
	.bus			= &tcm_loop_lld_bus,
पूर्ण;
/*
 * Used with root_device_रेजिस्टर() in tcm_loop_alloc_core_bus() below
 */
अटल काष्ठा device *tcm_loop_primary;

अटल व्योम tcm_loop_target_queue_cmd(काष्ठा tcm_loop_cmd *tl_cmd)
अणु
	काष्ठा se_cmd *se_cmd = &tl_cmd->tl_se_cmd;
	काष्ठा scsi_cmnd *sc = tl_cmd->sc;
	काष्ठा tcm_loop_nexus *tl_nexus;
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा tcm_loop_tpg *tl_tpg;
	काष्ठा scatterlist *sgl_bidi = शून्य;
	u32 sgl_bidi_count = 0, transfer_length;

	tl_hba = *(काष्ठा tcm_loop_hba **)shost_priv(sc->device->host);
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];

	/*
	 * Ensure that this tl_tpg reference from the incoming sc->device->id
	 * has alपढ़ोy been configured via tcm_loop_make_naa_tpg().
	 */
	अगर (!tl_tpg->tl_hba) अणु
		set_host_byte(sc, DID_NO_CONNECT);
		जाओ out_करोne;
	पूर्ण
	अगर (tl_tpg->tl_transport_status == TCM_TRANSPORT_OFFLINE) अणु
		set_host_byte(sc, DID_TRANSPORT_DISRUPTED);
		जाओ out_करोne;
	पूर्ण
	tl_nexus = tl_tpg->tl_nexus;
	अगर (!tl_nexus) अणु
		scmd_prपूर्णांकk(KERN_ERR, sc,
			    "TCM_Loop I_T Nexus does not exist\n");
		set_host_byte(sc, DID_ERROR);
		जाओ out_करोne;
	पूर्ण

	transfer_length = scsi_transfer_length(sc);
	अगर (!scsi_prot_sg_count(sc) &&
	    scsi_get_prot_op(sc) != SCSI_PROT_NORMAL) अणु
		se_cmd->prot_pto = true;
		/*
		 * loopback transport करोesn't support
		 * WRITE_GENERATE, READ_STRIP protection
		 * inक्रमmation operations, go ahead unरक्षित.
		 */
		transfer_length = scsi_bufflen(sc);
	पूर्ण

	se_cmd->tag = tl_cmd->sc_cmd_tag;
	target_init_cmd(se_cmd, tl_nexus->se_sess, &tl_cmd->tl_sense_buf[0],
			tl_cmd->sc->device->lun, transfer_length,
			TCM_SIMPLE_TAG, sc->sc_data_direction, 0);

	अगर (target_submit_prep(se_cmd, sc->cmnd, scsi_sglist(sc),
			       scsi_sg_count(sc), sgl_bidi, sgl_bidi_count,
			       scsi_prot_sglist(sc), scsi_prot_sg_count(sc),
			       GFP_ATOMIC))
		वापस;

	target_queue_submission(se_cmd);
	वापस;

out_करोne:
	sc->scsi_करोne(sc);
पूर्ण

/*
 * ->queuecommand can be and usually is called from पूर्णांकerrupt context, so
 * defer the actual submission to a workqueue.
 */
अटल पूर्णांक tcm_loop_queuecommand(काष्ठा Scsi_Host *sh, काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा tcm_loop_cmd *tl_cmd = scsi_cmd_priv(sc);

	pr_debug("%s() %d:%d:%d:%llu got CDB: 0x%02x scsi_buf_len: %u\n",
		 __func__, sc->device->host->host_no, sc->device->id,
		 sc->device->channel, sc->device->lun, sc->cmnd[0],
		 scsi_bufflen(sc));

	स_रखो(tl_cmd, 0, माप(*tl_cmd));
	tl_cmd->sc = sc;
	tl_cmd->sc_cmd_tag = sc->request->tag;

	tcm_loop_target_queue_cmd(tl_cmd);
	वापस 0;
पूर्ण

/*
 * Called from SCSI EH process context to issue a LUN_RESET TMR
 * to काष्ठा scsi_device
 */
अटल पूर्णांक tcm_loop_issue_पंचांगr(काष्ठा tcm_loop_tpg *tl_tpg,
			      u64 lun, पूर्णांक task, क्रमागत tcm_पंचांगreq_table पंचांगr)
अणु
	काष्ठा se_cmd *se_cmd;
	काष्ठा se_session *se_sess;
	काष्ठा tcm_loop_nexus *tl_nexus;
	काष्ठा tcm_loop_cmd *tl_cmd;
	पूर्णांक ret = TMR_FUNCTION_FAILED, rc;

	/*
	 * Locate the tl_nexus and se_sess poपूर्णांकers
	 */
	tl_nexus = tl_tpg->tl_nexus;
	अगर (!tl_nexus) अणु
		pr_err("Unable to perform device reset without active I_T Nexus\n");
		वापस ret;
	पूर्ण

	tl_cmd = kmem_cache_zalloc(tcm_loop_cmd_cache, GFP_KERNEL);
	अगर (!tl_cmd)
		वापस ret;

	init_completion(&tl_cmd->पंचांगr_करोne);

	se_cmd = &tl_cmd->tl_se_cmd;
	se_sess = tl_tpg->tl_nexus->se_sess;

	rc = target_submit_पंचांगr(se_cmd, se_sess, tl_cmd->tl_sense_buf, lun,
			       शून्य, पंचांगr, GFP_KERNEL, task,
			       TARGET_SCF_ACK_KREF);
	अगर (rc < 0)
		जाओ release;
	रुको_क्रम_completion(&tl_cmd->पंचांगr_करोne);
	ret = se_cmd->se_पंचांगr_req->response;
	target_put_sess_cmd(se_cmd);

out:
	वापस ret;

release:
	kmem_cache_मुक्त(tcm_loop_cmd_cache, tl_cmd);
	जाओ out;
पूर्ण

अटल पूर्णांक tcm_loop_पात_task(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा tcm_loop_tpg *tl_tpg;
	पूर्णांक ret = FAILED;

	/*
	 * Locate the tcm_loop_hba_t poपूर्णांकer
	 */
	tl_hba = *(काष्ठा tcm_loop_hba **)shost_priv(sc->device->host);
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];
	ret = tcm_loop_issue_पंचांगr(tl_tpg, sc->device->lun,
				 sc->request->tag, TMR_ABORT_TASK);
	वापस (ret == TMR_FUNCTION_COMPLETE) ? SUCCESS : FAILED;
पूर्ण

/*
 * Called from SCSI EH process context to issue a LUN_RESET TMR
 * to काष्ठा scsi_device
 */
अटल पूर्णांक tcm_loop_device_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा tcm_loop_tpg *tl_tpg;
	पूर्णांक ret = FAILED;

	/*
	 * Locate the tcm_loop_hba_t poपूर्णांकer
	 */
	tl_hba = *(काष्ठा tcm_loop_hba **)shost_priv(sc->device->host);
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];

	ret = tcm_loop_issue_पंचांगr(tl_tpg, sc->device->lun,
				 0, TMR_LUN_RESET);
	वापस (ret == TMR_FUNCTION_COMPLETE) ? SUCCESS : FAILED;
पूर्ण

अटल पूर्णांक tcm_loop_target_reset(काष्ठा scsi_cmnd *sc)
अणु
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा tcm_loop_tpg *tl_tpg;

	/*
	 * Locate the tcm_loop_hba_t poपूर्णांकer
	 */
	tl_hba = *(काष्ठा tcm_loop_hba **)shost_priv(sc->device->host);
	अगर (!tl_hba) अणु
		pr_err("Unable to perform device reset without active I_T Nexus\n");
		वापस FAILED;
	पूर्ण
	/*
	 * Locate the tl_tpg poपूर्णांकer from TargetID in sc->device->id
	 */
	tl_tpg = &tl_hba->tl_hba_tpgs[sc->device->id];
	अगर (tl_tpg) अणु
		tl_tpg->tl_transport_status = TCM_TRANSPORT_ONLINE;
		वापस SUCCESS;
	पूर्ण
	वापस FAILED;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा tcm_loop_driver_ढाँचा = अणु
	.show_info		= tcm_loop_show_info,
	.proc_name		= "tcm_loopback",
	.name			= "TCM_Loopback",
	.queuecommand		= tcm_loop_queuecommand,
	.change_queue_depth	= scsi_change_queue_depth,
	.eh_पात_handler = tcm_loop_पात_task,
	.eh_device_reset_handler = tcm_loop_device_reset,
	.eh_target_reset_handler = tcm_loop_target_reset,
	.this_id		= -1,
	.sg_tablesize		= 256,
	.max_sectors		= 0xFFFF,
	.dma_boundary		= PAGE_SIZE - 1,
	.module			= THIS_MODULE,
	.track_queue_depth	= 1,
	.cmd_size		= माप(काष्ठा tcm_loop_cmd),
पूर्ण;

अटल पूर्णांक tcm_loop_driver_probe(काष्ठा device *dev)
अणु
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा Scsi_Host *sh;
	पूर्णांक error, host_prot;

	tl_hba = to_tcm_loop_hba(dev);

	sh = scsi_host_alloc(&tcm_loop_driver_ढाँचा,
			माप(काष्ठा tcm_loop_hba));
	अगर (!sh) अणु
		pr_err("Unable to allocate struct scsi_host\n");
		वापस -ENODEV;
	पूर्ण
	tl_hba->sh = sh;

	/*
	 * Assign the काष्ठा tcm_loop_hba poपूर्णांकer to काष्ठा Scsi_Host->hostdata
	 */
	*((काष्ठा tcm_loop_hba **)sh->hostdata) = tl_hba;
	/*
	 * Setup single ID, Channel and LUN क्रम now..
	 */
	sh->max_id = 2;
	sh->max_lun = 0;
	sh->max_channel = 0;
	sh->max_cmd_len = SCSI_MAX_VARLEN_CDB_SIZE;
	sh->nr_hw_queues = tcm_loop_nr_hw_queues;
	sh->can_queue = tcm_loop_can_queue;
	sh->cmd_per_lun = tcm_loop_cmd_per_lun;

	host_prot = SHOST_DIF_TYPE1_PROTECTION | SHOST_DIF_TYPE2_PROTECTION |
		    SHOST_DIF_TYPE3_PROTECTION | SHOST_DIX_TYPE1_PROTECTION |
		    SHOST_DIX_TYPE2_PROTECTION | SHOST_DIX_TYPE3_PROTECTION;

	scsi_host_set_prot(sh, host_prot);
	scsi_host_set_guard(sh, SHOST_DIX_GUARD_CRC);

	error = scsi_add_host(sh, &tl_hba->dev);
	अगर (error) अणु
		pr_err("%s: scsi_add_host failed\n", __func__);
		scsi_host_put(sh);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_driver_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा Scsi_Host *sh;

	tl_hba = to_tcm_loop_hba(dev);
	sh = tl_hba->sh;

	scsi_हटाओ_host(sh);
	scsi_host_put(sh);
	वापस 0;
पूर्ण

अटल व्योम tcm_loop_release_adapter(काष्ठा device *dev)
अणु
	काष्ठा tcm_loop_hba *tl_hba = to_tcm_loop_hba(dev);

	kमुक्त(tl_hba);
पूर्ण

/*
 * Called from tcm_loop_make_scsi_hba() in tcm_loop_configfs.c
 */
अटल पूर्णांक tcm_loop_setup_hba_bus(काष्ठा tcm_loop_hba *tl_hba, पूर्णांक tcm_loop_host_id)
अणु
	पूर्णांक ret;

	tl_hba->dev.bus = &tcm_loop_lld_bus;
	tl_hba->dev.parent = tcm_loop_primary;
	tl_hba->dev.release = &tcm_loop_release_adapter;
	dev_set_name(&tl_hba->dev, "tcm_loop_adapter_%d", tcm_loop_host_id);

	ret = device_रेजिस्टर(&tl_hba->dev);
	अगर (ret) अणु
		pr_err("device_register() failed for tl_hba->dev: %d\n", ret);
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Called from tcm_loop_fabric_init() in tcl_loop_fabric.c to load the emulated
 * tcm_loop SCSI bus.
 */
अटल पूर्णांक tcm_loop_alloc_core_bus(व्योम)
अणु
	पूर्णांक ret;

	tcm_loop_primary = root_device_रेजिस्टर("tcm_loop_0");
	अगर (IS_ERR(tcm_loop_primary)) अणु
		pr_err("Unable to allocate tcm_loop_primary\n");
		वापस PTR_ERR(tcm_loop_primary);
	पूर्ण

	ret = bus_रेजिस्टर(&tcm_loop_lld_bus);
	अगर (ret) अणु
		pr_err("bus_register() failed for tcm_loop_lld_bus\n");
		जाओ dev_unreg;
	पूर्ण

	ret = driver_रेजिस्टर(&tcm_loop_driverfs);
	अगर (ret) अणु
		pr_err("driver_register() failed for tcm_loop_driverfs\n");
		जाओ bus_unreg;
	पूर्ण

	pr_debug("Initialized TCM Loop Core Bus\n");
	वापस ret;

bus_unreg:
	bus_unरेजिस्टर(&tcm_loop_lld_bus);
dev_unreg:
	root_device_unरेजिस्टर(tcm_loop_primary);
	वापस ret;
पूर्ण

अटल व्योम tcm_loop_release_core_bus(व्योम)
अणु
	driver_unरेजिस्टर(&tcm_loop_driverfs);
	bus_unरेजिस्टर(&tcm_loop_lld_bus);
	root_device_unरेजिस्टर(tcm_loop_primary);

	pr_debug("Releasing TCM Loop Core BUS\n");
पूर्ण

अटल अंतरभूत काष्ठा tcm_loop_tpg *tl_tpg(काष्ठा se_portal_group *se_tpg)
अणु
	वापस container_of(se_tpg, काष्ठा tcm_loop_tpg, tl_se_tpg);
पूर्ण

अटल अक्षर *tcm_loop_get_endpoपूर्णांक_wwn(काष्ठा se_portal_group *se_tpg)
अणु
	/*
	 * Return the passed NAA identअगरier क्रम the Target Port
	 */
	वापस &tl_tpg(se_tpg)->tl_hba->tl_wwn_address[0];
पूर्ण

अटल u16 tcm_loop_get_tag(काष्ठा se_portal_group *se_tpg)
अणु
	/*
	 * This Tag is used when क्रमming SCSI Name identअगरier in EVPD=1 0x83
	 * to represent the SCSI Target Port.
	 */
	वापस tl_tpg(se_tpg)->tl_tpgt;
पूर्ण

/*
 * Returning (1) here allows क्रम target_core_mod काष्ठा se_node_acl to be generated
 * based upon the incoming fabric dependent SCSI Initiator Port
 */
अटल पूर्णांक tcm_loop_check_demo_mode(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल पूर्णांक tcm_loop_check_demo_mode_cache(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

/*
 * Allow I_T Nexus full READ-WRITE access without explict Initiator Node ACLs क्रम
 * local भव Linux/SCSI LLD passthrough पूर्णांकo VM hypervisor guest
 */
अटल पूर्णांक tcm_loop_check_demo_mode_ग_लिखो_protect(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

/*
 * Because TCM_Loop करोes not use explict ACLs and MappedLUNs, this will
 * never be called क्रम TCM_Loop by target_core_fabric_configfs.c code.
 * It has been added here as a nop क्रम target_fabric_tf_ops_check()
 */
अटल पूर्णांक tcm_loop_check_prod_mode_ग_लिखो_protect(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_check_prot_fabric_only(काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg, काष्ठा tcm_loop_tpg,
						   tl_se_tpg);
	वापस tl_tpg->tl_fabric_prot_type;
पूर्ण

अटल u32 tcm_loop_get_inst_index(काष्ठा se_portal_group *se_tpg)
अणु
	वापस 1;
पूर्ण

अटल u32 tcm_loop_sess_get_index(काष्ठा se_session *se_sess)
अणु
	वापस 1;
पूर्ण

अटल व्योम tcm_loop_set_शेष_node_attributes(काष्ठा se_node_acl *se_acl)
अणु
	वापस;
पूर्ण

अटल पूर्णांक tcm_loop_get_cmd_state(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा tcm_loop_cmd *tl_cmd = container_of(se_cmd,
			काष्ठा tcm_loop_cmd, tl_se_cmd);

	वापस tl_cmd->sc_cmd_state;
पूर्ण

अटल पूर्णांक tcm_loop_ग_लिखो_pending(काष्ठा se_cmd *se_cmd)
अणु
	/*
	 * Since Linux/SCSI has alपढ़ोy sent करोwn a काष्ठा scsi_cmnd
	 * sc->sc_data_direction of DMA_TO_DEVICE with काष्ठा scatterlist array
	 * memory, and memory has alपढ़ोy been mapped to काष्ठा se_cmd->t_mem_list
	 * क्रमmat with transport_generic_map_mem_to_cmd().
	 *
	 * We now tell TCM to add this WRITE CDB directly पूर्णांकo the TCM storage
	 * object execution queue.
	 */
	target_execute_cmd(se_cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_queue_data_or_status(स्थिर अक्षर *func,
		काष्ठा se_cmd *se_cmd, u8 scsi_status)
अणु
	काष्ठा tcm_loop_cmd *tl_cmd = container_of(se_cmd,
				काष्ठा tcm_loop_cmd, tl_se_cmd);
	काष्ठा scsi_cmnd *sc = tl_cmd->sc;

	pr_debug("%s() called for scsi_cmnd: %p cdb: 0x%02x\n",
		 func, sc, sc->cmnd[0]);

	अगर (se_cmd->sense_buffer &&
	   ((se_cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE) ||
	    (se_cmd->se_cmd_flags & SCF_EMULATED_TASK_SENSE))) अणु

		स_नकल(sc->sense_buffer, se_cmd->sense_buffer,
				SCSI_SENSE_BUFFERSIZE);
		sc->result = SAM_STAT_CHECK_CONDITION;
		set_driver_byte(sc, DRIVER_SENSE);
	पूर्ण अन्यथा
		sc->result = scsi_status;

	set_host_byte(sc, DID_OK);
	अगर ((se_cmd->se_cmd_flags & SCF_OVERFLOW_BIT) ||
	    (se_cmd->se_cmd_flags & SCF_UNDERFLOW_BIT))
		scsi_set_resid(sc, se_cmd->residual_count);
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_queue_data_in(काष्ठा se_cmd *se_cmd)
अणु
	वापस tcm_loop_queue_data_or_status(__func__, se_cmd, SAM_STAT_GOOD);
पूर्ण

अटल पूर्णांक tcm_loop_queue_status(काष्ठा se_cmd *se_cmd)
अणु
	वापस tcm_loop_queue_data_or_status(__func__,
					     se_cmd, se_cmd->scsi_status);
पूर्ण

अटल व्योम tcm_loop_queue_पंचांग_rsp(काष्ठा se_cmd *se_cmd)
अणु
	काष्ठा tcm_loop_cmd *tl_cmd = container_of(se_cmd,
				काष्ठा tcm_loop_cmd, tl_se_cmd);

	/* Wake up tcm_loop_issue_पंचांगr(). */
	complete(&tl_cmd->पंचांगr_करोne);
पूर्ण

अटल व्योम tcm_loop_पातed_task(काष्ठा se_cmd *se_cmd)
अणु
	वापस;
पूर्ण

अटल अक्षर *tcm_loop_dump_proto_id(काष्ठा tcm_loop_hba *tl_hba)
अणु
	चयन (tl_hba->tl_proto_id) अणु
	हाल SCSI_PROTOCOL_SAS:
		वापस "SAS";
	हाल SCSI_PROTOCOL_FCP:
		वापस "FCP";
	हाल SCSI_PROTOCOL_ISCSI:
		वापस "iSCSI";
	शेष:
		अवरोध;
	पूर्ण

	वापस "Unknown";
पूर्ण

/* Start items क्रम tcm_loop_port_cit */

अटल पूर्णांक tcm_loop_port_link(
	काष्ठा se_portal_group *se_tpg,
	काष्ठा se_lun *lun)
अणु
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
				काष्ठा tcm_loop_tpg, tl_se_tpg);
	काष्ठा tcm_loop_hba *tl_hba = tl_tpg->tl_hba;

	atomic_inc_mb(&tl_tpg->tl_tpg_port_count);
	/*
	 * Add Linux/SCSI काष्ठा scsi_device by HCTL
	 */
	scsi_add_device(tl_hba->sh, 0, tl_tpg->tl_tpgt, lun->unpacked_lun);

	pr_debug("TCM_Loop_ConfigFS: Port Link Successful\n");
	वापस 0;
पूर्ण

अटल व्योम tcm_loop_port_unlink(
	काष्ठा se_portal_group *se_tpg,
	काष्ठा se_lun *se_lun)
अणु
	काष्ठा scsi_device *sd;
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा tcm_loop_tpg *tl_tpg;

	tl_tpg = container_of(se_tpg, काष्ठा tcm_loop_tpg, tl_se_tpg);
	tl_hba = tl_tpg->tl_hba;

	sd = scsi_device_lookup(tl_hba->sh, 0, tl_tpg->tl_tpgt,
				se_lun->unpacked_lun);
	अगर (!sd) अणु
		pr_err("Unable to locate struct scsi_device for %d:%d:%llu\n",
		       0, tl_tpg->tl_tpgt, se_lun->unpacked_lun);
		वापस;
	पूर्ण
	/*
	 * Remove Linux/SCSI काष्ठा scsi_device by HCTL
	 */
	scsi_हटाओ_device(sd);
	scsi_device_put(sd);

	atomic_dec_mb(&tl_tpg->tl_tpg_port_count);

	pr_debug("TCM_Loop_ConfigFS: Port Unlink Successful\n");
पूर्ण

/* End items क्रम tcm_loop_port_cit */

अटल sमाप_प्रकार tcm_loop_tpg_attrib_fabric_prot_type_show(
		काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg, काष्ठा tcm_loop_tpg,
						   tl_se_tpg);

	वापस प्र_लिखो(page, "%d\n", tl_tpg->tl_fabric_prot_type);
पूर्ण

अटल sमाप_प्रकार tcm_loop_tpg_attrib_fabric_prot_type_store(
		काष्ठा config_item *item, स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = attrib_to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg, काष्ठा tcm_loop_tpg,
						   tl_se_tpg);
	अचिन्हित दीर्घ val;
	पूर्णांक ret = kम_से_अदीर्घ(page, 0, &val);

	अगर (ret) अणु
		pr_err("kstrtoul() returned %d for fabric_prot_type\n", ret);
		वापस ret;
	पूर्ण
	अगर (val != 0 && val != 1 && val != 3) अणु
		pr_err("Invalid qla2xxx fabric_prot_type: %lu\n", val);
		वापस -EINVAL;
	पूर्ण
	tl_tpg->tl_fabric_prot_type = val;

	वापस count;
पूर्ण

CONFIGFS_ATTR(tcm_loop_tpg_attrib_, fabric_prot_type);

अटल काष्ठा configfs_attribute *tcm_loop_tpg_attrib_attrs[] = अणु
	&tcm_loop_tpg_attrib_attr_fabric_prot_type,
	शून्य,
पूर्ण;

/* Start items क्रम tcm_loop_nexus_cit */

अटल पूर्णांक tcm_loop_alloc_sess_cb(काष्ठा se_portal_group *se_tpg,
				  काष्ठा se_session *se_sess, व्योम *p)
अणु
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
					काष्ठा tcm_loop_tpg, tl_se_tpg);

	tl_tpg->tl_nexus = p;
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_make_nexus(
	काष्ठा tcm_loop_tpg *tl_tpg,
	स्थिर अक्षर *name)
अणु
	काष्ठा tcm_loop_hba *tl_hba = tl_tpg->tl_hba;
	काष्ठा tcm_loop_nexus *tl_nexus;
	पूर्णांक ret;

	अगर (tl_tpg->tl_nexus) अणु
		pr_debug("tl_tpg->tl_nexus already exists\n");
		वापस -EEXIST;
	पूर्ण

	tl_nexus = kzalloc(माप(*tl_nexus), GFP_KERNEL);
	अगर (!tl_nexus)
		वापस -ENOMEM;

	tl_nexus->se_sess = target_setup_session(&tl_tpg->tl_se_tpg, 0, 0,
					TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS,
					name, tl_nexus, tcm_loop_alloc_sess_cb);
	अगर (IS_ERR(tl_nexus->se_sess)) अणु
		ret = PTR_ERR(tl_nexus->se_sess);
		kमुक्त(tl_nexus);
		वापस ret;
	पूर्ण

	pr_debug("TCM_Loop_ConfigFS: Established I_T Nexus to emulated %s Initiator Port: %s\n",
		 tcm_loop_dump_proto_id(tl_hba), name);
	वापस 0;
पूर्ण

अटल पूर्णांक tcm_loop_drop_nexus(
	काष्ठा tcm_loop_tpg *tpg)
अणु
	काष्ठा se_session *se_sess;
	काष्ठा tcm_loop_nexus *tl_nexus;

	tl_nexus = tpg->tl_nexus;
	अगर (!tl_nexus)
		वापस -ENODEV;

	se_sess = tl_nexus->se_sess;
	अगर (!se_sess)
		वापस -ENODEV;

	अगर (atomic_पढ़ो(&tpg->tl_tpg_port_count)) अणु
		pr_err("Unable to remove TCM_Loop I_T Nexus with active TPG port count: %d\n",
		       atomic_पढ़ो(&tpg->tl_tpg_port_count));
		वापस -EPERM;
	पूर्ण

	pr_debug("TCM_Loop_ConfigFS: Removing I_T Nexus to emulated %s Initiator Port: %s\n",
		 tcm_loop_dump_proto_id(tpg->tl_hba),
		 tl_nexus->se_sess->se_node_acl->initiatorname);
	/*
	 * Release the SCSI I_T Nexus to the emulated Target Port
	 */
	target_हटाओ_session(se_sess);
	tpg->tl_nexus = शून्य;
	kमुक्त(tl_nexus);
	वापस 0;
पूर्ण

/* End items क्रम tcm_loop_nexus_cit */

अटल sमाप_प्रकार tcm_loop_tpg_nexus_show(काष्ठा config_item *item, अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			काष्ठा tcm_loop_tpg, tl_se_tpg);
	काष्ठा tcm_loop_nexus *tl_nexus;
	sमाप_प्रकार ret;

	tl_nexus = tl_tpg->tl_nexus;
	अगर (!tl_nexus)
		वापस -ENODEV;

	ret = snम_लिखो(page, PAGE_SIZE, "%s\n",
		tl_nexus->se_sess->se_node_acl->initiatorname);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार tcm_loop_tpg_nexus_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			काष्ठा tcm_loop_tpg, tl_se_tpg);
	काष्ठा tcm_loop_hba *tl_hba = tl_tpg->tl_hba;
	अचिन्हित अक्षर i_port[TL_WWN_ADDR_LEN], *ptr, *port_ptr;
	पूर्णांक ret;
	/*
	 * Shutकरोwn the active I_T nexus अगर 'NULL' is passed..
	 */
	अगर (!म_भेदन(page, "NULL", 4)) अणु
		ret = tcm_loop_drop_nexus(tl_tpg);
		वापस (!ret) ? count : ret;
	पूर्ण
	/*
	 * Otherwise make sure the passed भव Initiator port WWN matches
	 * the fabric protocol_id set in tcm_loop_make_scsi_hba(), and call
	 * tcm_loop_make_nexus()
	 */
	अगर (म_माप(page) >= TL_WWN_ADDR_LEN) अणु
		pr_err("Emulated NAA Sas Address: %s, exceeds max: %d\n",
		       page, TL_WWN_ADDR_LEN);
		वापस -EINVAL;
	पूर्ण
	snम_लिखो(&i_port[0], TL_WWN_ADDR_LEN, "%s", page);

	ptr = म_माला(i_port, "naa.");
	अगर (ptr) अणु
		अगर (tl_hba->tl_proto_id != SCSI_PROTOCOL_SAS) अणु
			pr_err("Passed SAS Initiator Port %s does not match target port protoid: %s\n",
			       i_port, tcm_loop_dump_proto_id(tl_hba));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[0];
		जाओ check_newline;
	पूर्ण
	ptr = म_माला(i_port, "fc.");
	अगर (ptr) अणु
		अगर (tl_hba->tl_proto_id != SCSI_PROTOCOL_FCP) अणु
			pr_err("Passed FCP Initiator Port %s does not match target port protoid: %s\n",
			       i_port, tcm_loop_dump_proto_id(tl_hba));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[3]; /* Skip over "fc." */
		जाओ check_newline;
	पूर्ण
	ptr = म_माला(i_port, "iqn.");
	अगर (ptr) अणु
		अगर (tl_hba->tl_proto_id != SCSI_PROTOCOL_ISCSI) अणु
			pr_err("Passed iSCSI Initiator Port %s does not match target port protoid: %s\n",
			       i_port, tcm_loop_dump_proto_id(tl_hba));
			वापस -EINVAL;
		पूर्ण
		port_ptr = &i_port[0];
		जाओ check_newline;
	पूर्ण
	pr_err("Unable to locate prefix for emulated Initiator Port: %s\n",
	       i_port);
	वापस -EINVAL;
	/*
	 * Clear any trailing newline क्रम the NAA WWN
	 */
check_newline:
	अगर (i_port[म_माप(i_port)-1] == '\n')
		i_port[म_माप(i_port)-1] = '\0';

	ret = tcm_loop_make_nexus(tl_tpg, port_ptr);
	अगर (ret < 0)
		वापस ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार tcm_loop_tpg_transport_status_show(काष्ठा config_item *item,
		अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			काष्ठा tcm_loop_tpg, tl_se_tpg);
	स्थिर अक्षर *status = शून्य;
	sमाप_प्रकार ret = -EINVAL;

	चयन (tl_tpg->tl_transport_status) अणु
	हाल TCM_TRANSPORT_ONLINE:
		status = "online";
		अवरोध;
	हाल TCM_TRANSPORT_OFFLINE:
		status = "offline";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (status)
		ret = snम_लिखो(page, PAGE_SIZE, "%s\n", status);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार tcm_loop_tpg_transport_status_store(काष्ठा config_item *item,
		स्थिर अक्षर *page, माप_प्रकार count)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			काष्ठा tcm_loop_tpg, tl_se_tpg);

	अगर (!म_भेदन(page, "online", 6)) अणु
		tl_tpg->tl_transport_status = TCM_TRANSPORT_ONLINE;
		वापस count;
	पूर्ण
	अगर (!म_भेदन(page, "offline", 7)) अणु
		tl_tpg->tl_transport_status = TCM_TRANSPORT_OFFLINE;
		अगर (tl_tpg->tl_nexus) अणु
			काष्ठा se_session *tl_sess = tl_tpg->tl_nexus->se_sess;

			core_allocate_nexus_loss_ua(tl_sess->se_node_acl);
		पूर्ण
		वापस count;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार tcm_loop_tpg_address_show(काष्ठा config_item *item,
					 अक्षर *page)
अणु
	काष्ठा se_portal_group *se_tpg = to_tpg(item);
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
			काष्ठा tcm_loop_tpg, tl_se_tpg);
	काष्ठा tcm_loop_hba *tl_hba = tl_tpg->tl_hba;

	वापस snम_लिखो(page, PAGE_SIZE, "%d:0:%d\n",
			tl_hba->sh->host_no, tl_tpg->tl_tpgt);
पूर्ण

CONFIGFS_ATTR(tcm_loop_tpg_, nexus);
CONFIGFS_ATTR(tcm_loop_tpg_, transport_status);
CONFIGFS_ATTR_RO(tcm_loop_tpg_, address);

अटल काष्ठा configfs_attribute *tcm_loop_tpg_attrs[] = अणु
	&tcm_loop_tpg_attr_nexus,
	&tcm_loop_tpg_attr_transport_status,
	&tcm_loop_tpg_attr_address,
	शून्य,
पूर्ण;

/* Start items क्रम tcm_loop_naa_cit */

अटल काष्ठा se_portal_group *tcm_loop_make_naa_tpg(काष्ठा se_wwn *wwn,
						     स्थिर अक्षर *name)
अणु
	काष्ठा tcm_loop_hba *tl_hba = container_of(wwn,
			काष्ठा tcm_loop_hba, tl_hba_wwn);
	काष्ठा tcm_loop_tpg *tl_tpg;
	पूर्णांक ret;
	अचिन्हित दीर्घ tpgt;

	अगर (म_माला(name, "tpgt_") != name) अणु
		pr_err("Unable to locate \"tpgt_#\" directory group\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	अगर (kम_से_अदीर्घ(name+5, 10, &tpgt))
		वापस ERR_PTR(-EINVAL);

	अगर (tpgt >= TL_TPGS_PER_HBA) अणु
		pr_err("Passed tpgt: %lu exceeds TL_TPGS_PER_HBA: %u\n",
		       tpgt, TL_TPGS_PER_HBA);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	tl_tpg = &tl_hba->tl_hba_tpgs[tpgt];
	tl_tpg->tl_hba = tl_hba;
	tl_tpg->tl_tpgt = tpgt;
	/*
	 * Register the tl_tpg as a emulated TCM Target Endpoपूर्णांक
	 */
	ret = core_tpg_रेजिस्टर(wwn, &tl_tpg->tl_se_tpg, tl_hba->tl_proto_id);
	अगर (ret < 0)
		वापस ERR_PTR(-ENOMEM);

	pr_debug("TCM_Loop_ConfigFS: Allocated Emulated %s Target Port %s,t,0x%04lx\n",
		 tcm_loop_dump_proto_id(tl_hba),
		 config_item_name(&wwn->wwn_group.cg_item), tpgt);
	वापस &tl_tpg->tl_se_tpg;
पूर्ण

अटल व्योम tcm_loop_drop_naa_tpg(
	काष्ठा se_portal_group *se_tpg)
अणु
	काष्ठा se_wwn *wwn = se_tpg->se_tpg_wwn;
	काष्ठा tcm_loop_tpg *tl_tpg = container_of(se_tpg,
				काष्ठा tcm_loop_tpg, tl_se_tpg);
	काष्ठा tcm_loop_hba *tl_hba;
	अचिन्हित लघु tpgt;

	tl_hba = tl_tpg->tl_hba;
	tpgt = tl_tpg->tl_tpgt;
	/*
	 * Release the I_T Nexus क्रम the Virtual target link अगर present
	 */
	tcm_loop_drop_nexus(tl_tpg);
	/*
	 * Deरेजिस्टर the tl_tpg as a emulated TCM Target Endpoपूर्णांक
	 */
	core_tpg_deरेजिस्टर(se_tpg);

	tl_tpg->tl_hba = शून्य;
	tl_tpg->tl_tpgt = 0;

	pr_debug("TCM_Loop_ConfigFS: Deallocated Emulated %s Target Port %s,t,0x%04x\n",
		 tcm_loop_dump_proto_id(tl_hba),
		 config_item_name(&wwn->wwn_group.cg_item), tpgt);
पूर्ण

/* End items क्रम tcm_loop_naa_cit */

/* Start items क्रम tcm_loop_cit */

अटल काष्ठा se_wwn *tcm_loop_make_scsi_hba(
	काष्ठा target_fabric_configfs *tf,
	काष्ठा config_group *group,
	स्थिर अक्षर *name)
अणु
	काष्ठा tcm_loop_hba *tl_hba;
	काष्ठा Scsi_Host *sh;
	अक्षर *ptr;
	पूर्णांक ret, off = 0;

	tl_hba = kzalloc(माप(*tl_hba), GFP_KERNEL);
	अगर (!tl_hba)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Determine the emulated Protocol Identअगरier and Target Port Name
	 * based on the incoming configfs directory name.
	 */
	ptr = म_माला(name, "naa.");
	अगर (ptr) अणु
		tl_hba->tl_proto_id = SCSI_PROTOCOL_SAS;
		जाओ check_len;
	पूर्ण
	ptr = म_माला(name, "fc.");
	अगर (ptr) अणु
		tl_hba->tl_proto_id = SCSI_PROTOCOL_FCP;
		off = 3; /* Skip over "fc." */
		जाओ check_len;
	पूर्ण
	ptr = म_माला(name, "iqn.");
	अगर (!ptr) अणु
		pr_err("Unable to locate prefix for emulated Target Port: %s\n",
		       name);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	tl_hba->tl_proto_id = SCSI_PROTOCOL_ISCSI;

check_len:
	अगर (म_माप(name) >= TL_WWN_ADDR_LEN) अणु
		pr_err("Emulated NAA %s Address: %s, exceeds max: %d\n",
		       name, tcm_loop_dump_proto_id(tl_hba), TL_WWN_ADDR_LEN);
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	snम_लिखो(&tl_hba->tl_wwn_address[0], TL_WWN_ADDR_LEN, "%s", &name[off]);

	/*
	 * Call device_रेजिस्टर(tl_hba->dev) to रेजिस्टर the emulated
	 * Linux/SCSI LLD of type काष्ठा Scsi_Host at tl_hba->sh after
	 * device_रेजिस्टर() callbacks in tcm_loop_driver_probe()
	 */
	ret = tcm_loop_setup_hba_bus(tl_hba, tcm_loop_hba_no_cnt);
	अगर (ret)
		जाओ out;

	sh = tl_hba->sh;
	tcm_loop_hba_no_cnt++;
	pr_debug("TCM_Loop_ConfigFS: Allocated emulated Target %s Address: %s at Linux/SCSI Host ID: %d\n",
		 tcm_loop_dump_proto_id(tl_hba), name, sh->host_no);
	वापस &tl_hba->tl_hba_wwn;
out:
	kमुक्त(tl_hba);
	वापस ERR_PTR(ret);
पूर्ण

अटल व्योम tcm_loop_drop_scsi_hba(
	काष्ठा se_wwn *wwn)
अणु
	काष्ठा tcm_loop_hba *tl_hba = container_of(wwn,
				काष्ठा tcm_loop_hba, tl_hba_wwn);

	pr_debug("TCM_Loop_ConfigFS: Deallocating emulated Target %s Address: %s at Linux/SCSI Host ID: %d\n",
		 tcm_loop_dump_proto_id(tl_hba), tl_hba->tl_wwn_address,
		 tl_hba->sh->host_no);
	/*
	 * Call device_unरेजिस्टर() on the original tl_hba->dev.
	 * tcm_loop_fabric_scsi.c:tcm_loop_release_adapter() will
	 * release *tl_hba;
	 */
	device_unरेजिस्टर(&tl_hba->dev);
पूर्ण

/* Start items क्रम tcm_loop_cit */
अटल sमाप_प्रकार tcm_loop_wwn_version_show(काष्ठा config_item *item, अक्षर *page)
अणु
	वापस प्र_लिखो(page, "TCM Loopback Fabric module %s\n", TCM_LOOP_VERSION);
पूर्ण

CONFIGFS_ATTR_RO(tcm_loop_wwn_, version);

अटल काष्ठा configfs_attribute *tcm_loop_wwn_attrs[] = अणु
	&tcm_loop_wwn_attr_version,
	शून्य,
पूर्ण;

/* End items क्रम tcm_loop_cit */

अटल स्थिर काष्ठा target_core_fabric_ops loop_ops = अणु
	.module				= THIS_MODULE,
	.fabric_name			= "loopback",
	.tpg_get_wwn			= tcm_loop_get_endpoपूर्णांक_wwn,
	.tpg_get_tag			= tcm_loop_get_tag,
	.tpg_check_demo_mode		= tcm_loop_check_demo_mode,
	.tpg_check_demo_mode_cache	= tcm_loop_check_demo_mode_cache,
	.tpg_check_demo_mode_ग_लिखो_protect =
				tcm_loop_check_demo_mode_ग_लिखो_protect,
	.tpg_check_prod_mode_ग_लिखो_protect =
				tcm_loop_check_prod_mode_ग_लिखो_protect,
	.tpg_check_prot_fabric_only	= tcm_loop_check_prot_fabric_only,
	.tpg_get_inst_index		= tcm_loop_get_inst_index,
	.check_stop_मुक्त		= tcm_loop_check_stop_मुक्त,
	.release_cmd			= tcm_loop_release_cmd,
	.sess_get_index			= tcm_loop_sess_get_index,
	.ग_लिखो_pending			= tcm_loop_ग_लिखो_pending,
	.set_शेष_node_attributes	= tcm_loop_set_शेष_node_attributes,
	.get_cmd_state			= tcm_loop_get_cmd_state,
	.queue_data_in			= tcm_loop_queue_data_in,
	.queue_status			= tcm_loop_queue_status,
	.queue_पंचांग_rsp			= tcm_loop_queue_पंचांग_rsp,
	.पातed_task			= tcm_loop_पातed_task,
	.fabric_make_wwn		= tcm_loop_make_scsi_hba,
	.fabric_drop_wwn		= tcm_loop_drop_scsi_hba,
	.fabric_make_tpg		= tcm_loop_make_naa_tpg,
	.fabric_drop_tpg		= tcm_loop_drop_naa_tpg,
	.fabric_post_link		= tcm_loop_port_link,
	.fabric_pre_unlink		= tcm_loop_port_unlink,
	.tfc_wwn_attrs			= tcm_loop_wwn_attrs,
	.tfc_tpg_base_attrs		= tcm_loop_tpg_attrs,
	.tfc_tpg_attrib_attrs		= tcm_loop_tpg_attrib_attrs,
पूर्ण;

अटल पूर्णांक __init tcm_loop_fabric_init(व्योम)
अणु
	पूर्णांक ret = -ENOMEM;

	tcm_loop_cmd_cache = kmem_cache_create("tcm_loop_cmd_cache",
				माप(काष्ठा tcm_loop_cmd),
				__alignof__(काष्ठा tcm_loop_cmd),
				0, शून्य);
	अगर (!tcm_loop_cmd_cache) अणु
		pr_debug("kmem_cache_create() for tcm_loop_cmd_cache failed\n");
		जाओ out;
	पूर्ण

	ret = tcm_loop_alloc_core_bus();
	अगर (ret)
		जाओ out_destroy_cache;

	ret = target_रेजिस्टर_ढाँचा(&loop_ops);
	अगर (ret)
		जाओ out_release_core_bus;

	वापस 0;

out_release_core_bus:
	tcm_loop_release_core_bus();
out_destroy_cache:
	kmem_cache_destroy(tcm_loop_cmd_cache);
out:
	वापस ret;
पूर्ण

अटल व्योम __निकास tcm_loop_fabric_निकास(व्योम)
अणु
	target_unरेजिस्टर_ढाँचा(&loop_ops);
	tcm_loop_release_core_bus();
	kmem_cache_destroy(tcm_loop_cmd_cache);
पूर्ण

MODULE_DESCRIPTION("TCM loopback virtual Linux/SCSI fabric module");
MODULE_AUTHOR("Nicholas A. Bellinger <nab@risingtidesystems.com>");
MODULE_LICENSE("GPL");
module_init(tcm_loop_fabric_init);
module_निकास(tcm_loop_fabric_निकास);
