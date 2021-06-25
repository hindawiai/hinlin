<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_gbl.h"

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "qla_devtbl.h"

#अगर_घोषित CONFIG_SPARC
#समावेश <यंत्र/prom.h>
#पूर्ण_अगर

#समावेश "qla_target.h"

/*
*  QLogic ISP2x00 Hardware Support Function Prototypes.
*/
अटल पूर्णांक qla2x00_isp_firmware(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_setup_chip(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_fw_पढ़ोy(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_configure_hba(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_configure_loop(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_configure_local_loop(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_configure_fabric(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_find_all_fabric_devs(scsi_qla_host_t *);
अटल पूर्णांक qla2x00_restart_isp(scsi_qla_host_t *);

अटल काष्ठा qla_chip_state_84xx *qla84xx_get_chip(काष्ठा scsi_qla_host *);
अटल पूर्णांक qla84xx_init_chip(scsi_qla_host_t *);
अटल पूर्णांक qla25xx_init_queues(काष्ठा qla_hw_data *);
अटल पूर्णांक qla24xx_post_prli_work(काष्ठा scsi_qla_host*, fc_port_t *);
अटल व्योम qla24xx_handle_gpdb_event(scsi_qla_host_t *vha,
				      काष्ठा event_arg *ea);
अटल व्योम qla24xx_handle_prli_करोne_event(काष्ठा scsi_qla_host *,
    काष्ठा event_arg *);
अटल व्योम __qla24xx_handle_gpdb_event(scsi_qla_host_t *, काष्ठा event_arg *);

/* SRB Extensions ---------------------------------------------------------- */

व्योम
qla2x00_sp_समयout(काष्ठा समयr_list *t)
अणु
	srb_t *sp = from_समयr(sp, t, u.iocb_cmd.समयr);
	काष्ठा srb_iocb *iocb;

	WARN_ON(irqs_disabled());
	iocb = &sp->u.iocb_cmd;
	iocb->समयout(sp);
पूर्ण

व्योम qla2x00_sp_मुक्त(srb_t *sp)
अणु
	काष्ठा srb_iocb *iocb = &sp->u.iocb_cmd;

	del_समयr(&iocb->समयr);
	qla2x00_rel_sp(sp);
पूर्ण

व्योम qla2xxx_rel_करोne_warning(srb_t *sp, पूर्णांक res)
अणु
	WARN_ONCE(1, "Calling done() of an already freed srb %p object\n", sp);
पूर्ण

व्योम qla2xxx_rel_मुक्त_warning(srb_t *sp)
अणु
	WARN_ONCE(1, "Calling free() of an already freed srb %p object\n", sp);
पूर्ण

/* Asynchronous Login/Logout Routines -------------------------------------- */

अचिन्हित दीर्घ
qla2x00_get_async_समयout(काष्ठा scsi_qla_host *vha)
अणु
	अचिन्हित दीर्घ पंचांगo;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Firmware should use चयन negotiated r_a_tov क्रम समयout. */
	पंचांगo = ha->r_a_tov / 10 * 2;
	अगर (IS_QLAFX00(ha)) अणु
		पंचांगo = FX00_DEF_RATOV * 2;
	पूर्ण अन्यथा अगर (!IS_FWI2_CAPABLE(ha)) अणु
		/*
		 * Except क्रम earlier ISPs where the समयout is seeded from the
		 * initialization control block.
		 */
		पंचांगo = ha->login_समयout;
	पूर्ण
	वापस पंचांगo;
पूर्ण

अटल व्योम qla24xx_पात_iocb_समयout(व्योम *data)
अणु
	srb_t *sp = data;
	काष्ठा srb_iocb *abt = &sp->u.iocb_cmd;
	काष्ठा qla_qpair *qpair = sp->qpair;
	u32 handle;
	अचिन्हित दीर्घ flags;

	अगर (sp->cmd_sp)
		ql_dbg(ql_dbg_async, sp->vha, 0x507c,
		    "Abort timeout - cmd hdl=%x, cmd type=%x hdl=%x, type=%x\n",
		    sp->cmd_sp->handle, sp->cmd_sp->type,
		    sp->handle, sp->type);
	अन्यथा
		ql_dbg(ql_dbg_async, sp->vha, 0x507c,
		    "Abort timeout 2 - hdl=%x, type=%x\n",
		    sp->handle, sp->type);

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	क्रम (handle = 1; handle < qpair->req->num_outstanding_cmds; handle++) अणु
		अगर (sp->cmd_sp && (qpair->req->outstanding_cmds[handle] ==
		    sp->cmd_sp))
			qpair->req->outstanding_cmds[handle] = शून्य;

		/* removing the पात */
		अगर (qpair->req->outstanding_cmds[handle] == sp) अणु
			qpair->req->outstanding_cmds[handle] = शून्य;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	अगर (sp->cmd_sp)
		sp->cmd_sp->करोne(sp->cmd_sp, QLA_OS_TIMER_EXPIRED);

	abt->u.abt.comp_status = cpu_to_le16(CS_TIMEOUT);
	sp->करोne(sp, QLA_OS_TIMER_EXPIRED);
पूर्ण

अटल व्योम qla24xx_पात_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा srb_iocb *abt = &sp->u.iocb_cmd;
	srb_t *orig_sp = sp->cmd_sp;

	अगर (orig_sp)
		qla_रुको_nvme_release_cmd_kref(orig_sp);

	del_समयr(&sp->u.iocb_cmd.समयr);
	अगर (sp->flags & SRB_WAKEUP_ON_COMP)
		complete(&abt->u.abt.comp);
	अन्यथा
		sp->मुक्त(sp);
पूर्ण

पूर्णांक qla24xx_async_पात_cmd(srb_t *cmd_sp, bool रुको)
अणु
	scsi_qla_host_t *vha = cmd_sp->vha;
	काष्ठा srb_iocb *abt_iocb;
	srb_t *sp;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	sp = qla2xxx_get_qpair_sp(cmd_sp->vha, cmd_sp->qpair, cmd_sp->fcport,
				  GFP_ATOMIC);
	अगर (!sp)
		वापस rval;

	abt_iocb = &sp->u.iocb_cmd;
	sp->type = SRB_ABT_CMD;
	sp->name = "abort";
	sp->qpair = cmd_sp->qpair;
	sp->cmd_sp = cmd_sp;
	अगर (रुको)
		sp->flags = SRB_WAKEUP_ON_COMP;

	abt_iocb->समयout = qla24xx_पात_iocb_समयout;
	init_completion(&abt_iocb->u.abt.comp);
	/* FW can send 2 x ABTS's समयout/20s */
	qla2x00_init_समयr(sp, 42);

	abt_iocb->u.abt.cmd_hndl = cmd_sp->handle;
	abt_iocb->u.abt.req_que_no = cpu_to_le16(cmd_sp->qpair->req->id);

	sp->करोne = qla24xx_पात_sp_करोne;

	ql_dbg(ql_dbg_async, vha, 0x507c,
	       "Abort command issued - hdl=%x, type=%x\n", cmd_sp->handle,
	       cmd_sp->type);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		sp->मुक्त(sp);
		वापस rval;
	पूर्ण

	अगर (रुको) अणु
		रुको_क्रम_completion(&abt_iocb->u.abt.comp);
		rval = abt_iocb->u.abt.comp_status == CS_COMPLETE ?
			QLA_SUCCESS : QLA_FUNCTION_FAILED;
		sp->मुक्त(sp);
	पूर्ण

	वापस rval;
पूर्ण

व्योम
qla2x00_async_iocb_समयout(व्योम *data)
अणु
	srb_t *sp = data;
	fc_port_t *fcport = sp->fcport;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	पूर्णांक rc, h;
	अचिन्हित दीर्घ flags;

	अगर (fcport) अणु
		ql_dbg(ql_dbg_disc, fcport->vha, 0x2071,
		    "Async-%s timeout - hdl=%x portid=%06x %8phC.\n",
		    sp->name, sp->handle, fcport->d_id.b24, fcport->port_name);

		fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	पूर्ण अन्यथा अणु
		pr_info("Async-%s timeout - hdl=%x.\n",
		    sp->name, sp->handle);
	पूर्ण

	चयन (sp->type) अणु
	हाल SRB_LOGIN_CMD:
		rc = qla24xx_async_पात_cmd(sp, false);
		अगर (rc) अणु
			/* Retry as needed. */
			lio->u.logio.data[0] = MBS_COMMAND_ERROR;
			lio->u.logio.data[1] =
				lio->u.logio.flags & SRB_LOGIN_RETRIED ?
				QLA_LOGIO_LOGIN_RETRIED : 0;
			spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
			क्रम (h = 1; h < sp->qpair->req->num_outstanding_cmds;
			    h++) अणु
				अगर (sp->qpair->req->outstanding_cmds[h] ==
				    sp) अणु
					sp->qpair->req->outstanding_cmds[h] =
					    शून्य;
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
			sp->करोne(sp, QLA_FUNCTION_TIMEOUT);
		पूर्ण
		अवरोध;
	हाल SRB_LOGOUT_CMD:
	हाल SRB_CT_PTHRU_CMD:
	हाल SRB_MB_IOCB:
	हाल SRB_NACK_PLOGI:
	हाल SRB_NACK_PRLI:
	हाल SRB_NACK_LOGO:
	हाल SRB_CTRL_VP:
	शेष:
		rc = qla24xx_async_पात_cmd(sp, false);
		अगर (rc) अणु
			spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
			क्रम (h = 1; h < sp->qpair->req->num_outstanding_cmds;
			    h++) अणु
				अगर (sp->qpair->req->outstanding_cmds[h] ==
				    sp) अणु
					sp->qpair->req->outstanding_cmds[h] =
					    शून्य;
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
			sp->करोne(sp, QLA_FUNCTION_TIMEOUT);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम qla2x00_async_login_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	काष्ठा event_arg ea;

	ql_dbg(ql_dbg_disc, vha, 0x20dd,
	    "%s %8phC res %d \n", __func__, sp->fcport->port_name, res);

	sp->fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

	अगर (!test_bit(UNLOADING, &vha->dpc_flags)) अणु
		स_रखो(&ea, 0, माप(ea));
		ea.fcport = sp->fcport;
		ea.data[0] = lio->u.logio.data[0];
		ea.data[1] = lio->u.logio.data[1];
		ea.iop[0] = lio->u.logio.iop[0];
		ea.iop[1] = lio->u.logio.iop[1];
		ea.sp = sp;
		qla24xx_handle_plogi_करोne_event(vha, &ea);
	पूर्ण

	sp->मुक्त(sp);
पूर्ण

अटल अंतरभूत bool
fcport_is_smaller(fc_port_t *fcport)
अणु
	अगर (wwn_to_u64(fcport->port_name) <
	    wwn_to_u64(fcport->vha->port_name))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत bool
fcport_is_bigger(fc_port_t *fcport)
अणु
	वापस !fcport_is_smaller(fcport);
पूर्ण

पूर्णांक
qla2x00_async_login(काष्ठा scsi_qla_host *vha, fc_port_t *fcport,
    uपूर्णांक16_t *data)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT) ||
	    fcport->loop_id == FC_NO_LOOP_ID) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "%s: %8phC - not sending command.\n",
		    __func__, fcport->port_name);
		वापस rval;
	पूर्ण

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_PEND);
	fcport->flags |= FCF_ASYNC_SENT;
	fcport->logout_completed = 0;

	sp->type = SRB_LOGIN_CMD;
	sp->name = "login";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	lio = &sp->u.iocb_cmd;
	lio->समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->करोne = qla2x00_async_login_sp_करोne;
	अगर (N2N_TOPO(fcport->vha->hw) && fcport_is_bigger(fcport))
		lio->u.logio.flags |= SRB_LOGIN_PRLI_ONLY;
	अन्यथा
		lio->u.logio.flags |= SRB_LOGIN_COND_PLOGI;

	अगर (NVME_TARGET(vha->hw, fcport))
		lio->u.logio.flags |= SRB_LOGIN_SKIP_PRLI;

	ql_log(ql_log_warn, vha, 0x2072,
	       "Async-login - %8phC hdl=%x, loopid=%x portid=%02x%02x%02x retries=%d.\n",
	       fcport->port_name, sp->handle, fcport->loop_id,
	       fcport->d_id.b.करोमुख्य, fcport->d_id.b.area, fcport->d_id.b.al_pa,
	       fcport->login_retry);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		fcport->flags |= FCF_LOGIN_NEEDED;
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
करोne:
	fcport->flags &= ~FCF_ASYNC_ACTIVE;
	वापस rval;
पूर्ण

अटल व्योम qla2x00_async_logout_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	sp->fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	sp->fcport->login_gen++;
	qlt_logo_completion_handler(sp->fcport, res);
	sp->मुक्त(sp);
पूर्ण

पूर्णांक
qla2x00_async_logout(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	fcport->flags |= FCF_ASYNC_SENT;
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_LOGOUT_CMD;
	sp->name = "logout";

	lio = &sp->u.iocb_cmd;
	lio->समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->करोne = qla2x00_async_logout_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x2070,
	    "Async-logout - hdl=%x loop-id=%x portid=%02x%02x%02x %8phC.\n",
	    sp->handle, fcport->loop_id, fcport->d_id.b.करोमुख्य,
		fcport->d_id.b.area, fcport->d_id.b.al_pa,
		fcport->port_name);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;
	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	वापस rval;
पूर्ण

व्योम
qla2x00_async_prlo_करोne(काष्ठा scsi_qla_host *vha, fc_port_t *fcport,
    uपूर्णांक16_t *data)
अणु
	fcport->flags &= ~FCF_ASYNC_ACTIVE;
	/* Don't re-login in target mode */
	अगर (!fcport->tgt_session)
		qla2x00_mark_device_lost(vha, fcport, 1);
	qlt_logo_completion_handler(fcport, data[0]);
पूर्ण

अटल व्योम qla2x00_async_prlo_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	काष्ठा scsi_qla_host *vha = sp->vha;

	sp->fcport->flags &= ~FCF_ASYNC_ACTIVE;
	अगर (!test_bit(UNLOADING, &vha->dpc_flags))
		qla2x00_post_async_prlo_करोne_work(sp->fcport->vha, sp->fcport,
		    lio->u.logio.data);
	sp->मुक्त(sp);
पूर्ण

पूर्णांक
qla2x00_async_prlo(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	पूर्णांक rval;

	rval = QLA_FUNCTION_FAILED;
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_PRLO_CMD;
	sp->name = "prlo";

	lio = &sp->u.iocb_cmd;
	lio->समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->करोne = qla2x00_async_prlo_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x2070,
	    "Async-prlo - hdl=%x loop-id=%x portid=%02x%02x%02x.\n",
	    sp->handle, fcport->loop_id, fcport->d_id.b.करोमुख्य,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	fcport->flags &= ~FCF_ASYNC_ACTIVE;
	वापस rval;
पूर्ण

अटल
व्योम qla24xx_handle_adisc_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	काष्ठा fc_port *fcport = ea->fcport;

	ql_dbg(ql_dbg_disc, vha, 0x20d2,
	    "%s %8phC DS %d LS %d rc %d login %d|%d rscn %d|%d lid %d\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, ea->rc, fcport->login_gen, ea->sp->gen2,
	    fcport->rscn_gen, ea->sp->gen1, fcport->loop_id);

	WARN_ONCE(!qla2xxx_is_valid_mbs(ea->data[0]), "mbs: %#x\n",
		  ea->data[0]);

	अगर (ea->data[0] != MBS_COMMAND_COMPLETE) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2066,
		    "%s %8phC: adisc fail: post delete\n",
		    __func__, ea->fcport->port_name);
		/* deleted = 0 & logout_on_delete = क्रमce fw cleanup */
		fcport->deleted = 0;
		fcport->logout_on_delete = 1;
		qlt_schedule_sess_क्रम_deletion(ea->fcport);
		वापस;
	पूर्ण

	अगर (ea->fcport->disc_state == DSC_DELETE_PEND)
		वापस;

	अगर (ea->sp->gen2 != ea->fcport->login_gen) अणु
		/* target side must have changed it. */
		ql_dbg(ql_dbg_disc, vha, 0x20d3,
		    "%s %8phC generation changed\n",
		    __func__, ea->fcport->port_name);
		वापस;
	पूर्ण अन्यथा अगर (ea->sp->gen1 != ea->fcport->rscn_gen) अणु
		qla_rscn_replay(fcport);
		qlt_schedule_sess_क्रम_deletion(fcport);
		वापस;
	पूर्ण

	__qla24xx_handle_gpdb_event(vha, ea);
पूर्ण

अटल पूर्णांक qla_post_els_plogi_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_ELS_PLOGI);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	fcport->flags |= FCF_ASYNC_ACTIVE;
	qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_PEND);
	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल व्योम qla2x00_async_adisc_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा event_arg ea;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;

	ql_dbg(ql_dbg_disc, vha, 0x2066,
	    "Async done-%s res %x %8phC\n",
	    sp->name, res, sp->fcport->port_name);

	sp->fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

	स_रखो(&ea, 0, माप(ea));
	ea.rc = res;
	ea.data[0] = lio->u.logio.data[0];
	ea.data[1] = lio->u.logio.data[1];
	ea.iop[0] = lio->u.logio.iop[0];
	ea.iop[1] = lio->u.logio.iop[1];
	ea.fcport = sp->fcport;
	ea.sp = sp;

	qla24xx_handle_adisc_event(vha, &ea);

	sp->मुक्त(sp);
पूर्ण

पूर्णांक
qla2x00_async_adisc(काष्ठा scsi_qla_host *vha, fc_port_t *fcport,
    uपूर्णांक16_t *data)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		वापस rval;

	fcport->flags |= FCF_ASYNC_SENT;
	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_ADISC_CMD;
	sp->name = "adisc";

	lio = &sp->u.iocb_cmd;
	lio->समयout = qla2x00_async_iocb_समयout;
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->करोne = qla2x00_async_adisc_sp_करोne;
	अगर (data[1] & QLA_LOGIO_LOGIN_RETRIED)
		lio->u.logio.flags |= SRB_LOGIN_RETRIED;

	ql_dbg(ql_dbg_disc, vha, 0x206f,
	    "Async-adisc - hdl=%x loopid=%x portid=%06x %8phC.\n",
	    sp->handle, fcport->loop_id, fcport->d_id.b24, fcport->port_name);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
	qla2x00_post_async_adisc_work(vha, fcport, data);
	वापस rval;
पूर्ण

अटल bool qla2x00_is_reserved_id(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_FWI2_CAPABLE(ha))
		वापस loop_id > NPH_LAST_HANDLE;

	वापस (loop_id > ha->max_loop_id && loop_id < SNS_FIRST_LOOP_ID) ||
		loop_id == MANAGEMENT_SERVER || loop_id == BROADCAST;
पूर्ण

/**
 * qla2x00_find_new_loop_id - scan through our port list and find a new usable loop ID
 * @vha: adapter state poपूर्णांकer.
 * @dev: port काष्ठाure poपूर्णांकer.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
अटल पूर्णांक qla2x00_find_new_loop_id(scsi_qla_host_t *vha, fc_port_t *dev)
अणु
	पूर्णांक	rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags = 0;

	rval = QLA_SUCCESS;

	spin_lock_irqsave(&ha->vport_slock, flags);

	dev->loop_id = find_first_zero_bit(ha->loop_id_map, LOOPID_MAP_SIZE);
	अगर (dev->loop_id >= LOOPID_MAP_SIZE ||
	    qla2x00_is_reserved_id(vha, dev->loop_id)) अणु
		dev->loop_id = FC_NO_LOOP_ID;
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		set_bit(dev->loop_id, ha->loop_id_map);
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	अगर (rval == QLA_SUCCESS)
		ql_dbg(ql_dbg_disc, dev->vha, 0x2086,
		       "Assigning new loopid=%x, portid=%x.\n",
		       dev->loop_id, dev->d_id.b24);
	अन्यथा
		ql_log(ql_log_warn, dev->vha, 0x2087,
		       "No loop_id's available, portid=%x.\n",
		       dev->d_id.b24);

	वापस rval;
पूर्ण

व्योम qla2x00_clear_loop_id(fc_port_t *fcport)
अणु
	काष्ठा qla_hw_data *ha = fcport->vha->hw;

	अगर (fcport->loop_id == FC_NO_LOOP_ID ||
	    qla2x00_is_reserved_id(fcport->vha, fcport->loop_id))
		वापस;

	clear_bit(fcport->loop_id, ha->loop_id_map);
	fcport->loop_id = FC_NO_LOOP_ID;
पूर्ण

अटल व्योम qla24xx_handle_gnl_करोne_event(scsi_qla_host_t *vha,
	काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport, *conflict_fcport;
	काष्ठा get_name_list_extended *e;
	u16 i, n, found = 0, loop_id;
	port_id_t id;
	u64 wwn;
	u16 data[2];
	u8 current_login_state, nvme_cls;

	fcport = ea->fcport;
	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "%s %8phC DS %d LS rc %d %d login %d|%d rscn %d|%d lid %d\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, ea->rc,
	    fcport->login_gen, fcport->last_login_gen,
	    fcport->rscn_gen, fcport->last_rscn_gen, vha->loop_id);

	अगर (fcport->disc_state == DSC_DELETE_PEND)
		वापस;

	अगर (ea->rc) अणु /* rval */
		अगर (fcport->login_retry == 0) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20de,
			    "GNL failed Port login retry %8phN, retry cnt=%d.\n",
			    fcport->port_name, fcport->login_retry);
		पूर्ण
		वापस;
	पूर्ण

	अगर (fcport->last_rscn_gen != fcport->rscn_gen) अणु
		qla_rscn_replay(fcport);
		qlt_schedule_sess_क्रम_deletion(fcport);
		वापस;
	पूर्ण अन्यथा अगर (fcport->last_login_gen != fcport->login_gen) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20e0,
		    "%s %8phC login gen changed\n",
		    __func__, fcport->port_name);
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण

	n = ea->data[0] / माप(काष्ठा get_name_list_extended);

	ql_dbg(ql_dbg_disc, vha, 0x20e1,
	    "%s %d %8phC n %d %02x%02x%02x lid %d \n",
	    __func__, __LINE__, fcport->port_name, n,
	    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
	    fcport->d_id.b.al_pa, fcport->loop_id);

	क्रम (i = 0; i < n; i++) अणु
		e = &vha->gnl.l[i];
		wwn = wwn_to_u64(e->port_name);
		id.b.करोमुख्य = e->port_id[2];
		id.b.area = e->port_id[1];
		id.b.al_pa = e->port_id[0];
		id.b.rsvd_1 = 0;

		अगर (स_भेद((u8 *)&wwn, fcport->port_name, WWN_SIZE))
			जारी;

		अगर (IS_SW_RESV_ADDR(id))
			जारी;

		found = 1;

		loop_id = le16_to_cpu(e->nport_handle);
		loop_id = (loop_id & 0x7fff);
		nvme_cls = e->current_login_state >> 4;
		current_login_state = e->current_login_state & 0xf;

		अगर (PRLI_PHASE(nvme_cls)) अणु
			current_login_state = nvme_cls;
			fcport->fc4_type &= ~FS_FC4TYPE_FCP;
			fcport->fc4_type |= FS_FC4TYPE_NVME;
		पूर्ण अन्यथा अगर (PRLI_PHASE(current_login_state)) अणु
			fcport->fc4_type |= FS_FC4TYPE_FCP;
			fcport->fc4_type &= ~FS_FC4TYPE_NVME;
		पूर्ण

		ql_dbg(ql_dbg_disc, vha, 0x20e2,
		    "%s found %8phC CLS [%x|%x] fc4_type %d ID[%06x|%06x] lid[%d|%d]\n",
		    __func__, fcport->port_name,
		    e->current_login_state, fcport->fw_login_state,
		    fcport->fc4_type, id.b24, fcport->d_id.b24,
		    loop_id, fcport->loop_id);

		चयन (fcport->disc_state) अणु
		हाल DSC_DELETE_PEND:
		हाल DSC_DELETED:
			अवरोध;
		शेष:
			अगर ((id.b24 != fcport->d_id.b24 &&
			    fcport->d_id.b24 &&
			    fcport->loop_id != FC_NO_LOOP_ID) ||
			    (fcport->loop_id != FC_NO_LOOP_ID &&
				fcport->loop_id != loop_id)) अणु
				ql_dbg(ql_dbg_disc, vha, 0x20e3,
				    "%s %d %8phC post del sess\n",
				    __func__, __LINE__, fcport->port_name);
				अगर (fcport->n2n_flag)
					fcport->d_id.b24 = 0;
				qlt_schedule_sess_क्रम_deletion(fcport);
				वापस;
			पूर्ण
			अवरोध;
		पूर्ण

		fcport->loop_id = loop_id;
		अगर (fcport->n2n_flag)
			fcport->d_id.b24 = id.b24;

		wwn = wwn_to_u64(fcport->port_name);
		qlt_find_sess_invalidate_other(vha, wwn,
			id, loop_id, &conflict_fcport);

		अगर (conflict_fcport) अणु
			/*
			 * Another share fcport share the same loop_id &
			 * nport id. Conflict fcport needs to finish
			 * cleanup beक्रमe this fcport can proceed to login.
			 */
			conflict_fcport->conflict = fcport;
			fcport->login_छोड़ो = 1;
		पूर्ण

		चयन (vha->hw->current_topology) अणु
		शेष:
			चयन (current_login_state) अणु
			हाल DSC_LS_PRLI_COMP:
				ql_dbg(ql_dbg_disc + ql_dbg_verbose,
				    vha, 0x20e4, "%s %d %8phC post gpdb\n",
				    __func__, __LINE__, fcport->port_name);

				अगर ((e->prli_svc_param_word_3[0] & BIT_4) == 0)
					fcport->port_type = FCT_INITIATOR;
				अन्यथा
					fcport->port_type = FCT_TARGET;
				data[0] = data[1] = 0;
				qla2x00_post_async_adisc_work(vha, fcport,
				    data);
				अवरोध;
			हाल DSC_LS_PORT_UNAVAIL:
			शेष:
				अगर (fcport->loop_id == FC_NO_LOOP_ID) अणु
					qla2x00_find_new_loop_id(vha, fcport);
					fcport->fw_login_state =
					    DSC_LS_PORT_UNAVAIL;
				पूर्ण
				ql_dbg(ql_dbg_disc, vha, 0x20e5,
				    "%s %d %8phC\n", __func__, __LINE__,
				    fcport->port_name);
				qla24xx_fcport_handle_login(vha, fcport);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल ISP_CFG_N:
			fcport->fw_login_state = current_login_state;
			fcport->d_id = id;
			चयन (current_login_state) अणु
			हाल DSC_LS_PRLI_PEND:
				/*
				 * In the middle of PRLI. Let it finish.
				 * Allow relogin code to recheck state again
				 * with GNL. Push disc_state back to DELETED
				 * so GNL can go out again
				 */
				qla2x00_set_fcport_disc_state(fcport,
				    DSC_DELETED);
				अवरोध;
			हाल DSC_LS_PRLI_COMP:
				अगर ((e->prli_svc_param_word_3[0] & BIT_4) == 0)
					fcport->port_type = FCT_INITIATOR;
				अन्यथा
					fcport->port_type = FCT_TARGET;

				data[0] = data[1] = 0;
				qla2x00_post_async_adisc_work(vha, fcport,
				    data);
				अवरोध;
			हाल DSC_LS_PLOGI_COMP:
				अगर (fcport_is_bigger(fcport)) अणु
					/* local adapter is smaller */
					अगर (fcport->loop_id != FC_NO_LOOP_ID)
						qla2x00_clear_loop_id(fcport);

					fcport->loop_id = loop_id;
					qla24xx_fcport_handle_login(vha,
					    fcport);
					अवरोध;
				पूर्ण
				fallthrough;
			शेष:
				अगर (fcport_is_smaller(fcport)) अणु
					/* local adapter is bigger */
					अगर (fcport->loop_id != FC_NO_LOOP_ID)
						qla2x00_clear_loop_id(fcport);

					fcport->loop_id = loop_id;
					qla24xx_fcport_handle_login(vha,
					    fcport);
				पूर्ण
				अवरोध;
			पूर्ण
			अवरोध;
		पूर्ण /* चयन (ha->current_topology) */
	पूर्ण

	अगर (!found) अणु
		चयन (vha->hw->current_topology) अणु
		हाल ISP_CFG_F:
		हाल ISP_CFG_FL:
			क्रम (i = 0; i < n; i++) अणु
				e = &vha->gnl.l[i];
				id.b.करोमुख्य = e->port_id[0];
				id.b.area = e->port_id[1];
				id.b.al_pa = e->port_id[2];
				id.b.rsvd_1 = 0;
				loop_id = le16_to_cpu(e->nport_handle);

				अगर (fcport->d_id.b24 == id.b24) अणु
					conflict_fcport =
					    qla2x00_find_fcport_by_wwpn(vha,
						e->port_name, 0);
					अगर (conflict_fcport) अणु
						ql_dbg(ql_dbg_disc + ql_dbg_verbose,
						    vha, 0x20e5,
						    "%s %d %8phC post del sess\n",
						    __func__, __LINE__,
						    conflict_fcport->port_name);
						qlt_schedule_sess_क्रम_deletion
							(conflict_fcport);
					पूर्ण
				पूर्ण
				/*
				 * FW alपढ़ोy picked this loop id क्रम
				 * another fcport
				 */
				अगर (fcport->loop_id == loop_id)
					fcport->loop_id = FC_NO_LOOP_ID;
			पूर्ण
			qla24xx_fcport_handle_login(vha, fcport);
			अवरोध;
		हाल ISP_CFG_N:
			qla2x00_set_fcport_disc_state(fcport, DSC_DELETED);
			अगर (समय_after_eq(jअगरfies, fcport->dm_login_expire)) अणु
				अगर (fcport->n2n_link_reset_cnt < 2) अणु
					fcport->n2n_link_reset_cnt++;
					/*
					 * remote port is not sending PLOGI.
					 * Reset link to kick start his state
					 * machine
					 */
					set_bit(N2N_LINK_RESET,
					    &vha->dpc_flags);
				पूर्ण अन्यथा अणु
					अगर (fcport->n2n_chip_reset < 1) अणु
						ql_log(ql_log_info, vha, 0x705d,
						    "Chip reset to bring laser down");
						set_bit(ISP_ABORT_NEEDED,
						    &vha->dpc_flags);
						fcport->n2n_chip_reset++;
					पूर्ण अन्यथा अणु
						ql_log(ql_log_info, vha, 0x705d,
						    "Remote port %8ph is not coming back\n",
						    fcport->port_name);
						fcport->scan_state = 0;
					पूर्ण
				पूर्ण
				qla2xxx_wake_dpc(vha);
			पूर्ण अन्यथा अणु
				/*
				 * report port suppose to करो PLOGI. Give him
				 * more समय. FW will catch it.
				 */
				set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण /* gnl_event */

अटल व्योम qla24xx_async_gnl_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	अचिन्हित दीर्घ flags;
	काष्ठा fc_port *fcport = शून्य, *tf;
	u16 i, n = 0, loop_id;
	काष्ठा event_arg ea;
	काष्ठा get_name_list_extended *e;
	u64 wwn;
	काष्ठा list_head h;
	bool found = false;

	ql_dbg(ql_dbg_disc, vha, 0x20e7,
	    "Async done-%s res %x mb[1]=%x mb[2]=%x \n",
	    sp->name, res, sp->u.iocb_cmd.u.mbx.in_mb[1],
	    sp->u.iocb_cmd.u.mbx.in_mb[2]);

	अगर (res == QLA_FUNCTION_TIMEOUT)
		वापस;

	sp->fcport->flags &= ~(FCF_ASYNC_SENT|FCF_ASYNC_ACTIVE);
	स_रखो(&ea, 0, माप(ea));
	ea.sp = sp;
	ea.rc = res;

	अगर (sp->u.iocb_cmd.u.mbx.in_mb[1] >=
	    माप(काष्ठा get_name_list_extended)) अणु
		n = sp->u.iocb_cmd.u.mbx.in_mb[1] /
		    माप(काष्ठा get_name_list_extended);
		ea.data[0] = sp->u.iocb_cmd.u.mbx.in_mb[1]; /* amnt xfered */
	पूर्ण

	क्रम (i = 0; i < n; i++) अणु
		e = &vha->gnl.l[i];
		loop_id = le16_to_cpu(e->nport_handle);
		/* mask out reserve bit */
		loop_id = (loop_id & 0x7fff);
		set_bit(loop_id, vha->hw->loop_id_map);
		wwn = wwn_to_u64(e->port_name);

		ql_dbg(ql_dbg_disc, vha, 0x20e8,
		    "%s %8phC %02x:%02x:%02x CLS %x/%x lid %x \n",
		    __func__, &wwn, e->port_id[2], e->port_id[1],
		    e->port_id[0], e->current_login_state, e->last_login_state,
		    (loop_id & 0x7fff));
	पूर्ण

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);

	INIT_LIST_HEAD(&h);
	fcport = tf = शून्य;
	अगर (!list_empty(&vha->gnl.fcports))
		list_splice_init(&vha->gnl.fcports, &h);
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	list_क्रम_each_entry_safe(fcport, tf, &h, gnl_entry) अणु
		list_del_init(&fcport->gnl_entry);
		spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
		fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		ea.fcport = fcport;

		qla24xx_handle_gnl_करोne_event(vha, &ea);
	पूर्ण

	/* create new fcport अगर fw has knowledge of new sessions */
	क्रम (i = 0; i < n; i++) अणु
		port_id_t id;
		u64 wwnn;

		e = &vha->gnl.l[i];
		wwn = wwn_to_u64(e->port_name);

		found = false;
		list_क्रम_each_entry_safe(fcport, tf, &vha->vp_fcports, list) अणु
			अगर (!स_भेद((u8 *)&wwn, fcport->port_name,
			    WWN_SIZE)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण

		id.b.करोमुख्य = e->port_id[2];
		id.b.area = e->port_id[1];
		id.b.al_pa = e->port_id[0];
		id.b.rsvd_1 = 0;

		अगर (!found && wwn && !IS_SW_RESV_ADDR(id)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2065,
			    "%s %d %8phC %06x post new sess\n",
			    __func__, __LINE__, (u8 *)&wwn, id.b24);
			wwnn = wwn_to_u64(e->node_name);
			qla24xx_post_newsess_work(vha, &id, (u8 *)&wwn,
			    (u8 *)&wwnn, शून्य, 0);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	vha->gnl.sent = 0;
	अगर (!list_empty(&vha->gnl.fcports)) अणु
		/* retrigger gnl */
		list_क्रम_each_entry_safe(fcport, tf, &vha->gnl.fcports,
		    gnl_entry) अणु
			list_del_init(&fcport->gnl_entry);
			fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);
			अगर (qla24xx_post_gnl_work(vha, fcport) == QLA_SUCCESS)
				अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	sp->मुक्त(sp);
पूर्ण

पूर्णांक qla24xx_async_gnl(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *mbx;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	अचिन्हित दीर्घ flags;
	u16 *mb;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT))
		वापस rval;

	ql_dbg(ql_dbg_disc, vha, 0x20d9,
	    "Async-gnlist WWPN %8phC \n", fcport->port_name);

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	fcport->flags |= FCF_ASYNC_SENT;
	qla2x00_set_fcport_disc_state(fcport, DSC_GNL);
	fcport->last_rscn_gen = fcport->rscn_gen;
	fcport->last_login_gen = fcport->login_gen;

	list_add_tail(&fcport->gnl_entry, &vha->gnl.fcports);
	अगर (vha->gnl.sent) अणु
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		वापस QLA_SUCCESS;
	पूर्ण
	vha->gnl.sent = 1;
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_MB_IOCB;
	sp->name = "gnlist";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	mbx = &sp->u.iocb_cmd;
	mbx->समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha)+2);

	mb = sp->u.iocb_cmd.u.mbx.out_mb;
	mb[0] = MBC_PORT_NODE_NAME_LIST;
	mb[1] = BIT_2 | BIT_3;
	mb[2] = MSW(vha->gnl.ldma);
	mb[3] = LSW(vha->gnl.ldma);
	mb[6] = MSW(MSD(vha->gnl.ldma));
	mb[7] = LSW(MSD(vha->gnl.ldma));
	mb[8] = vha->gnl.size;
	mb[9] = vha->vp_idx;

	sp->करोne = qla24xx_async_gnl_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x20da,
	    "Async-%s - OUT WWPN %8phC hndl %x\n",
	    sp->name, fcport->port_name, sp->handle);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	fcport->flags &= ~(FCF_ASYNC_ACTIVE | FCF_ASYNC_SENT);
	वापस rval;
पूर्ण

पूर्णांक qla24xx_post_gnl_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_GNL);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	fcport->flags |= FCF_ASYNC_ACTIVE;
	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल व्योम qla24xx_async_gpdb_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	fc_port_t *fcport = sp->fcport;
	u16 *mb = sp->u.iocb_cmd.u.mbx.in_mb;
	काष्ठा event_arg ea;

	ql_dbg(ql_dbg_disc, vha, 0x20db,
	    "Async done-%s res %x, WWPN %8phC mb[1]=%x mb[2]=%x \n",
	    sp->name, res, fcport->port_name, mb[1], mb[2]);

	fcport->flags &= ~(FCF_ASYNC_SENT | FCF_ASYNC_ACTIVE);

	अगर (res == QLA_FUNCTION_TIMEOUT)
		जाओ करोne;

	स_रखो(&ea, 0, माप(ea));
	ea.fcport = fcport;
	ea.sp = sp;

	qla24xx_handle_gpdb_event(vha, &ea);

करोne:
	dma_pool_मुक्त(ha->s_dma_pool, sp->u.iocb_cmd.u.mbx.in,
		sp->u.iocb_cmd.u.mbx.in_dma);

	sp->मुक्त(sp);
पूर्ण

अटल पूर्णांक qla24xx_post_prli_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;

	अगर (vha->host->active_mode == MODE_TARGET)
		वापस QLA_FUNCTION_FAILED;

	e = qla2x00_alloc_work(vha, QLA_EVT_PRLI);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;

	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल व्योम qla2x00_async_prli_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;
	काष्ठा event_arg ea;

	ql_dbg(ql_dbg_disc, vha, 0x2129,
	    "%s %8phC res %d \n", __func__,
	    sp->fcport->port_name, res);

	sp->fcport->flags &= ~FCF_ASYNC_SENT;

	अगर (!test_bit(UNLOADING, &vha->dpc_flags)) अणु
		स_रखो(&ea, 0, माप(ea));
		ea.fcport = sp->fcport;
		ea.data[0] = lio->u.logio.data[0];
		ea.data[1] = lio->u.logio.data[1];
		ea.iop[0] = lio->u.logio.iop[0];
		ea.iop[1] = lio->u.logio.iop[1];
		ea.sp = sp;

		qla24xx_handle_prli_करोne_event(vha, &ea);
	पूर्ण

	sp->मुक्त(sp);
पूर्ण

पूर्णांक
qla24xx_async_prli(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (!vha->flags.online) अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff, "%s %d %8phC exit\n",
		    __func__, __LINE__, fcport->port_name);
		वापस rval;
	पूर्ण

	अगर ((fcport->fw_login_state == DSC_LS_PLOGI_PEND ||
	    fcport->fw_login_state == DSC_LS_PRLI_PEND) &&
	    qla_dual_mode_enabled(vha)) अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff, "%s %d %8phC exit\n",
		    __func__, __LINE__, fcport->port_name);
		वापस rval;
	पूर्ण

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		वापस rval;

	fcport->flags |= FCF_ASYNC_SENT;
	fcport->logout_completed = 0;

	sp->type = SRB_PRLI_CMD;
	sp->name = "prli";

	lio = &sp->u.iocb_cmd;
	lio->समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	sp->करोne = qla2x00_async_prli_sp_करोne;
	lio->u.logio.flags = 0;

	अगर (NVME_TARGET(vha->hw, fcport))
		lio->u.logio.flags |= SRB_LOGIN_NVME_PRLI;

	ql_dbg(ql_dbg_disc, vha, 0x211b,
	    "Async-prli - %8phC hdl=%x, loopid=%x portid=%06x retries=%d fc4type %x priority %x %s.\n",
	    fcport->port_name, sp->handle, fcport->loop_id, fcport->d_id.b24,
	    fcport->login_retry, fcport->fc4_type, vha->hw->fc4_type_priority,
	    NVME_TARGET(vha->hw, fcport) ? "nvme" : "fcp");

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		fcport->flags |= FCF_LOGIN_NEEDED;
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
	वापस rval;
पूर्ण

पूर्णांक qla24xx_post_gpdb_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport, u8 opt)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_GPDB);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	e->u.fcport.opt = opt;
	fcport->flags |= FCF_ASYNC_ACTIVE;
	वापस qla2x00_post_work(vha, e);
पूर्ण

पूर्णांक qla24xx_async_gpdb(काष्ठा scsi_qla_host *vha, fc_port_t *fcport, u8 opt)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *mbx;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	u16 *mb;
	dma_addr_t pd_dma;
	काष्ठा port_database_24xx *pd;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!vha->flags.online || (fcport->flags & FCF_ASYNC_SENT) ||
	    fcport->loop_id == FC_NO_LOOP_ID) अणु
		ql_log(ql_log_warn, vha, 0xffff,
		    "%s: %8phC - not sending command.\n",
		    __func__, fcport->port_name);
		वापस rval;
	पूर्ण

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	qla2x00_set_fcport_disc_state(fcport, DSC_GPDB);

	fcport->flags |= FCF_ASYNC_SENT;
	sp->type = SRB_MB_IOCB;
	sp->name = "gpdb";
	sp->gen1 = fcport->rscn_gen;
	sp->gen2 = fcport->login_gen;

	mbx = &sp->u.iocb_cmd;
	mbx->समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	pd = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &pd_dma);
	अगर (pd == शून्य) अणु
		ql_log(ql_log_warn, vha, 0xd043,
		    "Failed to allocate port database structure.\n");
		जाओ करोne_मुक्त_sp;
	पूर्ण

	mb = sp->u.iocb_cmd.u.mbx.out_mb;
	mb[0] = MBC_GET_PORT_DATABASE;
	mb[1] = fcport->loop_id;
	mb[2] = MSW(pd_dma);
	mb[3] = LSW(pd_dma);
	mb[6] = MSW(MSD(pd_dma));
	mb[7] = LSW(MSD(pd_dma));
	mb[9] = vha->vp_idx;
	mb[10] = opt;

	mbx->u.mbx.in = pd;
	mbx->u.mbx.in_dma = pd_dma;

	sp->करोne = qla24xx_async_gpdb_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x20dc,
	    "Async-%s %8phC hndl %x opt %x\n",
	    sp->name, fcport->port_name, sp->handle, opt);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;
	वापस rval;

करोne_मुक्त_sp:
	अगर (pd)
		dma_pool_मुक्त(ha->s_dma_pool, pd, pd_dma);

	sp->मुक्त(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
करोne:
	fcport->flags &= ~FCF_ASYNC_ACTIVE;
	qla24xx_post_gpdb_work(vha, fcport, opt);
	वापस rval;
पूर्ण

अटल
व्योम __qla24xx_handle_gpdb_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	ea->fcport->login_gen++;
	ea->fcport->deleted = 0;
	ea->fcport->logout_on_delete = 1;

	अगर (!ea->fcport->login_succ && !IS_SW_RESV_ADDR(ea->fcport->d_id)) अणु
		vha->fcport_count++;
		ea->fcport->login_succ = 1;

		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		qla24xx_sched_upd_fcport(ea->fcport);
		spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	पूर्ण अन्यथा अगर (ea->fcport->login_succ) अणु
		/*
		 * We have an existing session. A late RSCN delivery
		 * must have triggered the session to be re-validate.
		 * Session is still valid.
		 */
		ql_dbg(ql_dbg_disc, vha, 0x20d6,
		    "%s %d %8phC session revalidate success\n",
		    __func__, __LINE__, ea->fcport->port_name);
		qla2x00_set_fcport_disc_state(ea->fcport, DSC_LOGIN_COMPLETE);
	पूर्ण
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
पूर्ण

अटल
व्योम qla24xx_handle_gpdb_event(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport = ea->fcport;
	काष्ठा port_database_24xx *pd;
	काष्ठा srb *sp = ea->sp;
	uपूर्णांक8_t	ls;

	pd = (काष्ठा port_database_24xx *)sp->u.iocb_cmd.u.mbx.in;

	fcport->flags &= ~FCF_ASYNC_SENT;

	ql_dbg(ql_dbg_disc, vha, 0x20d2,
	    "%s %8phC DS %d LS %d fc4_type %x rc %d\n", __func__,
	    fcport->port_name, fcport->disc_state, pd->current_login_state,
	    fcport->fc4_type, ea->rc);

	अगर (fcport->disc_state == DSC_DELETE_PEND)
		वापस;

	अगर (NVME_TARGET(vha->hw, fcport))
		ls = pd->current_login_state >> 4;
	अन्यथा
		ls = pd->current_login_state & 0xf;

	अगर (ea->sp->gen2 != fcport->login_gen) अणु
		/* target side must have changed it. */

		ql_dbg(ql_dbg_disc, vha, 0x20d3,
		    "%s %8phC generation changed\n",
		    __func__, fcport->port_name);
		वापस;
	पूर्ण अन्यथा अगर (ea->sp->gen1 != fcport->rscn_gen) अणु
		qla_rscn_replay(fcport);
		qlt_schedule_sess_क्रम_deletion(fcport);
		वापस;
	पूर्ण

	चयन (ls) अणु
	हाल PDS_PRLI_COMPLETE:
		__qla24xx_parse_gpdb(vha, fcport, pd);
		अवरोध;
	हाल PDS_PLOGI_PENDING:
	हाल PDS_PLOGI_COMPLETE:
	हाल PDS_PRLI_PENDING:
	हाल PDS_PRLI2_PENDING:
		/* Set discovery state back to GNL to Relogin attempt */
		अगर (qla_dual_mode_enabled(vha) ||
		    qla_ini_mode_enabled(vha)) अणु
			qla2x00_set_fcport_disc_state(fcport, DSC_GNL);
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		पूर्ण
		वापस;
	हाल PDS_LOGO_PENDING:
	हाल PDS_PORT_UNAVAILABLE:
	शेष:
		ql_dbg(ql_dbg_disc, vha, 0x20d5, "%s %d %8phC post del sess\n",
		    __func__, __LINE__, fcport->port_name);
		qlt_schedule_sess_क्रम_deletion(fcport);
		वापस;
	पूर्ण
	__qla24xx_handle_gpdb_event(vha, ea);
पूर्ण /* gpdb event */

अटल व्योम qla_chk_n2n_b4_login(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	u8 login = 0;
	पूर्णांक rc;

	अगर (qla_tgt_mode_enabled(vha))
		वापस;

	अगर (qla_dual_mode_enabled(vha)) अणु
		अगर (N2N_TOPO(vha->hw)) अणु
			u64 mywwn, wwn;

			mywwn = wwn_to_u64(vha->port_name);
			wwn = wwn_to_u64(fcport->port_name);
			अगर (mywwn > wwn)
				login = 1;
			अन्यथा अगर ((fcport->fw_login_state == DSC_LS_PLOGI_COMP)
			    && समय_after_eq(jअगरfies,
				    fcport->plogi_nack_करोne_deadline))
				login = 1;
		पूर्ण अन्यथा अणु
			login = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* initiator mode */
		login = 1;
	पूर्ण

	अगर (login && fcport->login_retry) अणु
		fcport->login_retry--;
		अगर (fcport->loop_id == FC_NO_LOOP_ID) अणु
			fcport->fw_login_state = DSC_LS_PORT_UNAVAIL;
			rc = qla2x00_find_new_loop_id(vha, fcport);
			अगर (rc) अणु
				ql_dbg(ql_dbg_disc, vha, 0x20e6,
				    "%s %d %8phC post del sess - out of loopid\n",
				    __func__, __LINE__, fcport->port_name);
				fcport->scan_state = 0;
				qlt_schedule_sess_क्रम_deletion(fcport);
				वापस;
			पूर्ण
		पूर्ण
		ql_dbg(ql_dbg_disc, vha, 0x20bf,
		    "%s %d %8phC post login\n",
		    __func__, __LINE__, fcport->port_name);
		qla2x00_post_async_login_work(vha, fcport, शून्य);
	पूर्ण
पूर्ण

पूर्णांक qla24xx_fcport_handle_login(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	u16 data[2];
	u64 wwn;
	u16 sec;

	ql_dbg(ql_dbg_disc, vha, 0x20d8,
	    "%s %8phC DS %d LS %d P %d fl %x confl %p rscn %d|%d login %d lid %d scan %d\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, fcport->login_छोड़ो, fcport->flags,
	    fcport->conflict, fcport->last_rscn_gen, fcport->rscn_gen,
	    fcport->login_gen, fcport->loop_id, fcport->scan_state);

	अगर (fcport->scan_state != QLA_FCPORT_FOUND)
		वापस 0;

	अगर ((fcport->loop_id != FC_NO_LOOP_ID) &&
	    qla_dual_mode_enabled(vha) &&
	    ((fcport->fw_login_state == DSC_LS_PLOGI_PEND) ||
	     (fcport->fw_login_state == DSC_LS_PRLI_PEND)))
		वापस 0;

	अगर (fcport->fw_login_state == DSC_LS_PLOGI_COMP &&
	    !N2N_TOPO(vha->hw)) अणु
		अगर (समय_beक्रमe_eq(jअगरfies, fcport->plogi_nack_करोne_deadline)) अणु
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
			वापस 0;
		पूर्ण
	पूर्ण

	/* Target won't initiate port login अगर fabric is present */
	अगर (vha->host->active_mode == MODE_TARGET && !N2N_TOPO(vha->hw))
		वापस 0;

	अगर (fcport->flags & FCF_ASYNC_SENT) अणु
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		वापस 0;
	पूर्ण

	चयन (fcport->disc_state) अणु
	हाल DSC_DELETED:
		wwn = wwn_to_u64(fcport->node_name);
		चयन (vha->hw->current_topology) अणु
		हाल ISP_CFG_N:
			अगर (fcport_is_smaller(fcport)) अणु
				/* this adapter is bigger */
				अगर (fcport->login_retry) अणु
					अगर (fcport->loop_id == FC_NO_LOOP_ID) अणु
						qla2x00_find_new_loop_id(vha,
						    fcport);
						fcport->fw_login_state =
						    DSC_LS_PORT_UNAVAIL;
					पूर्ण
					fcport->login_retry--;
					qla_post_els_plogi_work(vha, fcport);
				पूर्ण अन्यथा अणु
					ql_log(ql_log_info, vha, 0x705d,
					    "Unable to reach remote port %8phC",
					    fcport->port_name);
				पूर्ण
			पूर्ण अन्यथा अणु
				qla24xx_post_gnl_work(vha, fcport);
			पूर्ण
			अवरोध;
		शेष:
			अगर (wwn == 0)    अणु
				ql_dbg(ql_dbg_disc, vha, 0xffff,
				    "%s %d %8phC post GNNID\n",
				    __func__, __LINE__, fcport->port_name);
				qla24xx_post_gnnid_work(vha, fcport);
			पूर्ण अन्यथा अगर (fcport->loop_id == FC_NO_LOOP_ID) अणु
				ql_dbg(ql_dbg_disc, vha, 0x20bd,
				    "%s %d %8phC post gnl\n",
				    __func__, __LINE__, fcport->port_name);
				qla24xx_post_gnl_work(vha, fcport);
			पूर्ण अन्यथा अणु
				qla_chk_n2n_b4_login(vha, fcport);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	हाल DSC_GNL:
		चयन (vha->hw->current_topology) अणु
		हाल ISP_CFG_N:
			अगर ((fcport->current_login_state & 0xf) == 0x6) अणु
				ql_dbg(ql_dbg_disc, vha, 0x2118,
				    "%s %d %8phC post GPDB work\n",
				    __func__, __LINE__, fcport->port_name);
				fcport->chip_reset =
					vha->hw->base_qpair->chip_reset;
				qla24xx_post_gpdb_work(vha, fcport, 0);
			पूर्ण  अन्यथा अणु
				ql_dbg(ql_dbg_disc, vha, 0x2118,
				    "%s %d %8phC post %s PRLI\n",
				    __func__, __LINE__, fcport->port_name,
				    NVME_TARGET(vha->hw, fcport) ? "NVME" :
				    "FC");
				qla24xx_post_prli_work(vha, fcport);
			पूर्ण
			अवरोध;
		शेष:
			अगर (fcport->login_छोड़ो) अणु
				ql_dbg(ql_dbg_disc, vha, 0x20d8,
				    "%s %d %8phC exit\n",
				    __func__, __LINE__,
				    fcport->port_name);
				fcport->last_rscn_gen = fcport->rscn_gen;
				fcport->last_login_gen = fcport->login_gen;
				set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
				अवरोध;
			पूर्ण
			qla_chk_n2n_b4_login(vha, fcport);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल DSC_LOGIN_FAILED:
		अगर (N2N_TOPO(vha->hw))
			qla_chk_n2n_b4_login(vha, fcport);
		अन्यथा
			qlt_schedule_sess_क्रम_deletion(fcport);
		अवरोध;

	हाल DSC_LOGIN_COMPLETE:
		/* recheck login state */
		data[0] = data[1] = 0;
		qla2x00_post_async_adisc_work(vha, fcport, data);
		अवरोध;

	हाल DSC_LOGIN_PEND:
		अगर (fcport->fw_login_state == DSC_LS_PLOGI_COMP)
			qla24xx_post_prli_work(vha, fcport);
		अवरोध;

	हाल DSC_UPD_FCPORT:
		sec =  jअगरfies_to_msecs(jअगरfies -
		    fcport->jअगरfies_at_registration)/1000;
		अगर (fcport->sec_since_registration < sec && sec &&
		    !(sec % 60)) अणु
			fcport->sec_since_registration = sec;
			ql_dbg(ql_dbg_disc, fcport->vha, 0xffff,
			    "%s %8phC - Slow Rport registration(%d Sec)\n",
			    __func__, fcport->port_name, sec);
		पूर्ण

		अगर (fcport->next_disc_state != DSC_DELETE_PEND)
			fcport->next_disc_state = DSC_ADISC;
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qla24xx_post_newsess_work(काष्ठा scsi_qla_host *vha, port_id_t *id,
    u8 *port_name, u8 *node_name, व्योम *pla, u8 fc4_type)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_NEW_SESS);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.new_sess.id = *id;
	e->u.new_sess.pla = pla;
	e->u.new_sess.fc4_type = fc4_type;
	स_नकल(e->u.new_sess.port_name, port_name, WWN_SIZE);
	अगर (node_name)
		स_नकल(e->u.new_sess.node_name, node_name, WWN_SIZE);

	वापस qla2x00_post_work(vha, e);
पूर्ण

व्योम qla2x00_handle_rscn(scsi_qla_host_t *vha, काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport;
	अचिन्हित दीर्घ flags;

	fcport = qla2x00_find_fcport_by_nportid(vha, &ea->id, 1);
	अगर (fcport) अणु
		fcport->scan_needed = 1;
		fcport->rscn_gen++;
	पूर्ण

	spin_lock_irqsave(&vha->work_lock, flags);
	अगर (vha->scan.scan_flags == 0) अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff, "%s: schedule\n", __func__);
		vha->scan.scan_flags |= SF_QUEUED;
		schedule_delayed_work(&vha->scan.scan_work, 5);
	पूर्ण
	spin_unlock_irqrestore(&vha->work_lock, flags);
पूर्ण

व्योम qla24xx_handle_relogin_event(scsi_qla_host_t *vha,
	काष्ठा event_arg *ea)
अणु
	fc_port_t *fcport = ea->fcport;

	अगर (test_bit(UNLOADING, &vha->dpc_flags))
		वापस;

	ql_dbg(ql_dbg_disc, vha, 0x2102,
	    "%s %8phC DS %d LS %d P %d del %d cnfl %p rscn %d|%d login %d|%d fl %x\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, fcport->login_छोड़ो,
	    fcport->deleted, fcport->conflict,
	    fcport->last_rscn_gen, fcport->rscn_gen,
	    fcport->last_login_gen, fcport->login_gen,
	    fcport->flags);

	अगर (fcport->last_rscn_gen != fcport->rscn_gen) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20e9, "%s %d %8phC post gnl\n",
		    __func__, __LINE__, fcport->port_name);
		qla24xx_post_gnl_work(vha, fcport);
		वापस;
	पूर्ण

	qla24xx_fcport_handle_login(vha, fcport);
पूर्ण

व्योम qla_handle_els_plogi_करोne(scsi_qla_host_t *vha,
				      काष्ठा event_arg *ea)
अणु
	/* क्रम pure Target Mode, PRLI will not be initiated */
	अगर (vha->host->active_mode == MODE_TARGET)
		वापस;

	ql_dbg(ql_dbg_disc, vha, 0x2118,
	    "%s %d %8phC post PRLI\n",
	    __func__, __LINE__, ea->fcport->port_name);
	qla24xx_post_prli_work(vha, ea->fcport);
पूर्ण

/*
 * RSCN(s) came in क्रम this fcport, but the RSCN(s) was not able
 * to be consumed by the fcport
 */
व्योम qla_rscn_replay(fc_port_t *fcport)
अणु
	काष्ठा event_arg ea;

	चयन (fcport->disc_state) अणु
	हाल DSC_DELETE_PEND:
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	अगर (fcport->scan_needed) अणु
		स_रखो(&ea, 0, माप(ea));
		ea.id = fcport->d_id;
		ea.id.b.rsvd_1 = RSCN_PORT_ADDR;
		qla2x00_handle_rscn(fcport->vha, &ea);
	पूर्ण
पूर्ण

अटल व्योम
qla2x00_पंचांगf_iocb_समयout(व्योम *data)
अणु
	srb_t *sp = data;
	काष्ठा srb_iocb *पंचांगf = &sp->u.iocb_cmd;
	पूर्णांक rc, h;
	अचिन्हित दीर्घ flags;

	rc = qla24xx_async_पात_cmd(sp, false);
	अगर (rc) अणु
		spin_lock_irqsave(sp->qpair->qp_lock_ptr, flags);
		क्रम (h = 1; h < sp->qpair->req->num_outstanding_cmds; h++) अणु
			अगर (sp->qpair->req->outstanding_cmds[h] == sp) अणु
				sp->qpair->req->outstanding_cmds[h] = शून्य;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(sp->qpair->qp_lock_ptr, flags);
		पंचांगf->u.पंचांगf.comp_status = cpu_to_le16(CS_TIMEOUT);
		पंचांगf->u.पंचांगf.data = QLA_FUNCTION_FAILED;
		complete(&पंचांगf->u.पंचांगf.comp);
	पूर्ण
पूर्ण

अटल व्योम qla2x00_पंचांगf_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा srb_iocb *पंचांगf = &sp->u.iocb_cmd;

	complete(&पंचांगf->u.पंचांगf.comp);
पूर्ण

पूर्णांक
qla2x00_async_पंचांग_cmd(fc_port_t *fcport, uपूर्णांक32_t flags, uपूर्णांक32_t lun,
	uपूर्णांक32_t tag)
अणु
	काष्ठा scsi_qla_host *vha = fcport->vha;
	काष्ठा srb_iocb *पंचांग_iocb;
	srb_t *sp;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	पंचांग_iocb = &sp->u.iocb_cmd;
	sp->type = SRB_TM_CMD;
	sp->name = "tmf";

	पंचांग_iocb->समयout = qla2x00_पंचांगf_iocb_समयout;
	init_completion(&पंचांग_iocb->u.पंचांगf.comp);
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha));

	पंचांग_iocb->u.पंचांगf.flags = flags;
	पंचांग_iocb->u.पंचांगf.lun = lun;
	पंचांग_iocb->u.पंचांगf.data = tag;
	sp->करोne = qla2x00_पंचांगf_sp_करोne;

	ql_dbg(ql_dbg_taskm, vha, 0x802f,
	    "Async-tmf hdl=%x loop-id=%x portid=%02x%02x%02x.\n",
	    sp->handle, fcport->loop_id, fcport->d_id.b.करोमुख्य,
	    fcport->d_id.b.area, fcport->d_id.b.al_pa);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;
	रुको_क्रम_completion(&पंचांग_iocb->u.पंचांगf.comp);

	rval = पंचांग_iocb->u.पंचांगf.data;

	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x8030,
		    "TM IOCB failed (%x).\n", rval);
	पूर्ण

	अगर (!test_bit(UNLOADING, &vha->dpc_flags) && !IS_QLAFX00(vha->hw)) अणु
		flags = पंचांग_iocb->u.पंचांगf.flags;
		lun = (uपूर्णांक16_t)पंचांग_iocb->u.पंचांगf.lun;

		/* Issue Marker IOCB */
		qla2x00_marker(vha, vha->hw->base_qpair,
		    fcport->loop_id, lun,
		    flags == TCF_LUN_RESET ? MK_SYNC_ID_LUN : MK_SYNC_ID);
	पूर्ण

करोne_मुक्त_sp:
	sp->मुक्त(sp);
	fcport->flags &= ~FCF_ASYNC_SENT;
करोne:
	वापस rval;
पूर्ण

पूर्णांक
qla24xx_async_पात_command(srb_t *sp)
अणु
	अचिन्हित दीर्घ   flags = 0;

	uपूर्णांक32_t	handle;
	fc_port_t	*fcport = sp->fcport;
	काष्ठा qla_qpair *qpair = sp->qpair;
	काष्ठा scsi_qla_host *vha = fcport->vha;
	काष्ठा req_que *req = qpair->req;

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	क्रम (handle = 1; handle < req->num_outstanding_cmds; handle++) अणु
		अगर (req->outstanding_cmds[handle] == sp)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	अगर (handle == req->num_outstanding_cmds) अणु
		/* Command not found. */
		वापस QLA_FUNCTION_FAILED;
	पूर्ण
	अगर (sp->type == SRB_FXIOCB_DCMD)
		वापस qlafx00_fx_disc(vha, &vha->hw->mr.fcport,
		    FXDISC_ABORT_IOCTL);

	वापस qla24xx_async_पात_cmd(sp, true);
पूर्ण

अटल व्योम
qla24xx_handle_prli_करोne_event(काष्ठा scsi_qla_host *vha, काष्ठा event_arg *ea)
अणु
	WARN_ONCE(!qla2xxx_is_valid_mbs(ea->data[0]), "mbs: %#x\n",
		  ea->data[0]);

	चयन (ea->data[0]) अणु
	हाल MBS_COMMAND_COMPLETE:
		ql_dbg(ql_dbg_disc, vha, 0x2118,
		    "%s %d %8phC post gpdb\n",
		    __func__, __LINE__, ea->fcport->port_name);

		ea->fcport->chip_reset = vha->hw->base_qpair->chip_reset;
		ea->fcport->logout_on_delete = 1;
		ea->fcport->nvme_prli_service_param = ea->iop[0];
		अगर (ea->iop[0] & NVME_PRLI_SP_FIRST_BURST)
			ea->fcport->nvme_first_burst_size =
			    (ea->iop[1] & 0xffff) * 512;
		अन्यथा
			ea->fcport->nvme_first_burst_size = 0;
		qla24xx_post_gpdb_work(vha, ea->fcport, 0);
		अवरोध;
	शेष:
		अगर ((ea->iop[0] == LSC_SCODE_ELS_REJECT) &&
		    (ea->iop[1] == 0x50000)) अणु   /* reson 5=busy expl:0x0 */
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
			ea->fcport->fw_login_state = DSC_LS_PLOGI_COMP;
			अवरोध;
		पूर्ण

		ql_dbg(ql_dbg_disc, vha, 0x2118,
		       "%s %d %8phC priority %s, fc4type %x\n",
		       __func__, __LINE__, ea->fcport->port_name,
		       vha->hw->fc4_type_priority == FC4_PRIORITY_FCP ?
		       "FCP" : "NVMe", ea->fcport->fc4_type);

		अगर (N2N_TOPO(vha->hw)) अणु
			अगर (vha->hw->fc4_type_priority == FC4_PRIORITY_NVME) अणु
				ea->fcport->fc4_type &= ~FS_FC4TYPE_NVME;
				ea->fcport->fc4_type |= FS_FC4TYPE_FCP;
			पूर्ण अन्यथा अणु
				ea->fcport->fc4_type &= ~FS_FC4TYPE_FCP;
				ea->fcport->fc4_type |= FS_FC4TYPE_NVME;
			पूर्ण

			अगर (ea->fcport->n2n_link_reset_cnt < 3) अणु
				ea->fcport->n2n_link_reset_cnt++;
				vha->relogin_jअगर = jअगरfies + 2 * HZ;
				/*
				 * PRLI failed. Reset link to kick start
				 * state machine
				 */
				set_bit(N2N_LINK_RESET, &vha->dpc_flags);
			पूर्ण अन्यथा अणु
				ql_log(ql_log_warn, vha, 0x2119,
				       "%s %d %8phC Unable to reconnect\n",
				       __func__, __LINE__,
				       ea->fcport->port_name);
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 * चयन connect. login failed. Take connection करोwn
			 * and allow relogin to retrigger
			 */
			अगर (NVME_FCP_TARGET(ea->fcport)) अणु
				ql_dbg(ql_dbg_disc, vha, 0x2118,
				       "%s %d %8phC post %s prli\n",
				       __func__, __LINE__,
				       ea->fcport->port_name,
				       (ea->fcport->fc4_type & FS_FC4TYPE_NVME)
				       ? "NVMe" : "FCP");
				अगर (vha->hw->fc4_type_priority == FC4_PRIORITY_NVME)
					ea->fcport->fc4_type &= ~FS_FC4TYPE_NVME;
				अन्यथा
					ea->fcport->fc4_type &= ~FS_FC4TYPE_FCP;
			पूर्ण

			ea->fcport->flags &= ~FCF_ASYNC_SENT;
			ea->fcport->keep_nport_handle = 0;
			ea->fcport->logout_on_delete = 1;
			qlt_schedule_sess_क्रम_deletion(ea->fcport);
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

व्योम
qla24xx_handle_plogi_करोne_event(काष्ठा scsi_qla_host *vha, काष्ठा event_arg *ea)
अणु
	port_id_t cid;	/* conflict Nport id */
	u16 lid;
	काष्ठा fc_port *conflict_fcport;
	अचिन्हित दीर्घ flags;
	काष्ठा fc_port *fcport = ea->fcport;

	ql_dbg(ql_dbg_disc, vha, 0xffff,
	    "%s %8phC DS %d LS %d rc %d login %d|%d rscn %d|%d data %x|%x iop %x|%x\n",
	    __func__, fcport->port_name, fcport->disc_state,
	    fcport->fw_login_state, ea->rc, ea->sp->gen2, fcport->login_gen,
	    ea->sp->gen1, fcport->rscn_gen,
	    ea->data[0], ea->data[1], ea->iop[0], ea->iop[1]);

	अगर ((fcport->fw_login_state == DSC_LS_PLOGI_PEND) ||
	    (fcport->fw_login_state == DSC_LS_PRLI_PEND)) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20ea,
		    "%s %d %8phC Remote is trying to login\n",
		    __func__, __LINE__, fcport->port_name);
		वापस;
	पूर्ण

	अगर ((fcport->disc_state == DSC_DELETE_PEND) ||
	    (fcport->disc_state == DSC_DELETED)) अणु
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण

	अगर (ea->sp->gen2 != fcport->login_gen) अणु
		/* target side must have changed it. */
		ql_dbg(ql_dbg_disc, vha, 0x20d3,
		    "%s %8phC generation changed\n",
		    __func__, fcport->port_name);
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण अन्यथा अगर (ea->sp->gen1 != fcport->rscn_gen) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20d3,
		    "%s %8phC RSCN generation changed\n",
		    __func__, fcport->port_name);
		qla_rscn_replay(fcport);
		qlt_schedule_sess_क्रम_deletion(fcport);
		वापस;
	पूर्ण

	WARN_ONCE(!qla2xxx_is_valid_mbs(ea->data[0]), "mbs: %#x\n",
		  ea->data[0]);

	चयन (ea->data[0]) अणु
	हाल MBS_COMMAND_COMPLETE:
		/*
		 * Driver must validate login state - If PRLI not complete,
		 * क्रमce a relogin attempt via implicit LOGO, PLOGI, and PRLI
		 * requests.
		 */
		अगर (NVME_TARGET(vha->hw, ea->fcport)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2117,
				"%s %d %8phC post prli\n",
				__func__, __LINE__, ea->fcport->port_name);
			qla24xx_post_prli_work(vha, ea->fcport);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_disc, vha, 0x20ea,
			    "%s %d %8phC LoopID 0x%x in use with %06x. post gpdb\n",
			    __func__, __LINE__, ea->fcport->port_name,
			    ea->fcport->loop_id, ea->fcport->d_id.b24);

			set_bit(ea->fcport->loop_id, vha->hw->loop_id_map);
			spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
			ea->fcport->chip_reset = vha->hw->base_qpair->chip_reset;
			ea->fcport->logout_on_delete = 1;
			ea->fcport->send_els_logo = 0;
			ea->fcport->fw_login_state = DSC_LS_PRLI_COMP;
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

			qla24xx_post_gpdb_work(vha, ea->fcport, 0);
		पूर्ण
		अवरोध;
	हाल MBS_COMMAND_ERROR:
		ql_dbg(ql_dbg_disc, vha, 0x20eb, "%s %d %8phC cmd error %x\n",
		    __func__, __LINE__, ea->fcport->port_name, ea->data[1]);

		ea->fcport->flags &= ~FCF_ASYNC_SENT;
		qla2x00_set_fcport_disc_state(ea->fcport, DSC_LOGIN_FAILED);
		अगर (ea->data[1] & QLA_LOGIO_LOGIN_RETRIED)
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
		अन्यथा
			qla2x00_mark_device_lost(vha, ea->fcport, 1);
		अवरोध;
	हाल MBS_LOOP_ID_USED:
		/* data[1] = IO PARAM 1 = nport ID  */
		cid.b.करोमुख्य = (ea->iop[1] >> 16) & 0xff;
		cid.b.area   = (ea->iop[1] >>  8) & 0xff;
		cid.b.al_pa  = ea->iop[1] & 0xff;
		cid.b.rsvd_1 = 0;

		ql_dbg(ql_dbg_disc, vha, 0x20ec,
		    "%s %d %8phC lid %#x in use with pid %06x post gnl\n",
		    __func__, __LINE__, ea->fcport->port_name,
		    ea->fcport->loop_id, cid.b24);

		set_bit(ea->fcport->loop_id, vha->hw->loop_id_map);
		ea->fcport->loop_id = FC_NO_LOOP_ID;
		qla24xx_post_gnl_work(vha, ea->fcport);
		अवरोध;
	हाल MBS_PORT_ID_USED:
		lid = ea->iop[1] & 0xffff;
		qlt_find_sess_invalidate_other(vha,
		    wwn_to_u64(ea->fcport->port_name),
		    ea->fcport->d_id, lid, &conflict_fcport);

		अगर (conflict_fcport) अणु
			/*
			 * Another fcport share the same loop_id/nport id.
			 * Conflict fcport needs to finish cleanup beक्रमe this
			 * fcport can proceed to login.
			 */
			conflict_fcport->conflict = ea->fcport;
			ea->fcport->login_छोड़ो = 1;

			ql_dbg(ql_dbg_disc, vha, 0x20ed,
			    "%s %d %8phC NPortId %06x inuse with loopid 0x%x. post gidpn\n",
			    __func__, __LINE__, ea->fcport->port_name,
			    ea->fcport->d_id.b24, lid);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_disc, vha, 0x20ed,
			    "%s %d %8phC NPortId %06x inuse with loopid 0x%x. sched delete\n",
			    __func__, __LINE__, ea->fcport->port_name,
			    ea->fcport->d_id.b24, lid);

			qla2x00_clear_loop_id(ea->fcport);
			set_bit(lid, vha->hw->loop_id_map);
			ea->fcport->loop_id = lid;
			ea->fcport->keep_nport_handle = 0;
			ea->fcport->logout_on_delete = 1;
			qlt_schedule_sess_क्रम_deletion(ea->fcport);
		पूर्ण
		अवरोध;
	पूर्ण
	वापस;
पूर्ण

/****************************************************************************/
/*                QLogic ISP2x00 Hardware Support Functions.                */
/****************************************************************************/

अटल पूर्णांक
qla83xx_nic_core_fw_load(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t idc_major_ver, idc_minor_ver;
	uपूर्णांक16_t config[4];

	qla83xx_idc_lock(vha, 0);

	/* SV: TODO: Assign initialization समयout from
	 * flash-info / other param
	 */
	ha->fcoe_dev_init_समयout = QLA83XX_IDC_INITIALIZATION_TIMEOUT;
	ha->fcoe_reset_समयout = QLA83XX_IDC_RESET_ACK_TIMEOUT;

	/* Set our fcoe function presence */
	अगर (__qla83xx_set_drv_presence(vha) != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb077,
		    "Error while setting DRV-Presence.\n");
		rval = QLA_FUNCTION_FAILED;
		जाओ निकास;
	पूर्ण

	/* Decide the reset ownership */
	qla83xx_reset_ownership(vha);

	/*
	 * On first protocol driver load:
	 * Init-Owner: Set IDC-Major-Version and Clear IDC-Lock-Recovery
	 * रेजिस्टर.
	 * Others: Check compatibility with current IDC Major version.
	 */
	qla83xx_rd_reg(vha, QLA83XX_IDC_MAJOR_VERSION, &idc_major_ver);
	अगर (ha->flags.nic_core_reset_owner) अणु
		/* Set IDC Major version */
		idc_major_ver = QLA83XX_SUPP_IDC_MAJOR_VERSION;
		qla83xx_wr_reg(vha, QLA83XX_IDC_MAJOR_VERSION, idc_major_ver);

		/* Clearing IDC-Lock-Recovery रेजिस्टर */
		qla83xx_wr_reg(vha, QLA83XX_IDC_LOCK_RECOVERY, 0);
	पूर्ण अन्यथा अगर (idc_major_ver != QLA83XX_SUPP_IDC_MAJOR_VERSION) अणु
		/*
		 * Clear further IDC participation अगर we are not compatible with
		 * the current IDC Major Version.
		 */
		ql_log(ql_log_warn, vha, 0xb07d,
		    "Failing load, idc_major_ver=%d, expected_major_ver=%d.\n",
		    idc_major_ver, QLA83XX_SUPP_IDC_MAJOR_VERSION);
		__qla83xx_clear_drv_presence(vha);
		rval = QLA_FUNCTION_FAILED;
		जाओ निकास;
	पूर्ण
	/* Each function sets its supported Minor version. */
	qla83xx_rd_reg(vha, QLA83XX_IDC_MINOR_VERSION, &idc_minor_ver);
	idc_minor_ver |= (QLA83XX_SUPP_IDC_MINOR_VERSION << (ha->portnum * 2));
	qla83xx_wr_reg(vha, QLA83XX_IDC_MINOR_VERSION, idc_minor_ver);

	अगर (ha->flags.nic_core_reset_owner) अणु
		स_रखो(config, 0, माप(config));
		अगर (!qla81xx_get_port_config(vha, config))
			qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE,
			    QLA8XXX_DEV_READY);
	पूर्ण

	rval = qla83xx_idc_state_handler(vha);

निकास:
	qla83xx_idc_unlock(vha, 0);

	वापस rval;
पूर्ण

/*
* qla2x00_initialize_adapter
*      Initialize board.
*
* Input:
*      ha = adapter block poपूर्णांकer.
*
* Returns:
*      0 = success
*/
पूर्णांक
qla2x00_initialize_adapter(scsi_qla_host_t *vha)
अणु
	पूर्णांक	rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	स_रखो(&vha->qla_stats, 0, माप(vha->qla_stats));
	स_रखो(&vha->fc_host_stat, 0, माप(vha->fc_host_stat));

	/* Clear adapter flags. */
	vha->flags.online = 0;
	ha->flags.chip_reset_करोne = 0;
	vha->flags.reset_active = 0;
	ha->flags.pci_channel_io_perm_failure = 0;
	ha->flags.eeh_busy = 0;
	vha->qla_stats.jअगरfies_at_last_reset = get_jअगरfies_64();
	atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
	atomic_set(&vha->loop_state, LOOP_DOWN);
	vha->device_flags = DFLG_NO_CABLE;
	vha->dpc_flags = 0;
	vha->flags.management_server_logged_in = 0;
	vha->marker_needed = 0;
	ha->isp_पात_cnt = 0;
	ha->beacon_blink_led = 0;

	set_bit(0, ha->req_qid_map);
	set_bit(0, ha->rsp_qid_map);

	ql_dbg(ql_dbg_init, vha, 0x0040,
	    "Configuring PCI space...\n");
	rval = ha->isp_ops->pci_config(vha);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0044,
		    "Unable to configure PCI space.\n");
		वापस (rval);
	पूर्ण

	ha->isp_ops->reset_chip(vha);

	/* Check क्रम secure flash support */
	अगर (IS_QLA28XX(ha)) अणु
		अगर (rd_reg_word(&reg->mailbox12) & BIT_0)
			ha->flags.secure_adapter = 1;
		ql_log(ql_log_info, vha, 0xffff, "Secure Adapter: %s\n",
		    (ha->flags.secure_adapter) ? "Yes" : "No");
	पूर्ण


	rval = qla2xxx_get_flash_info(vha);
	अगर (rval) अणु
		ql_log(ql_log_fatal, vha, 0x004f,
		    "Unable to validate FLASH data.\n");
		वापस rval;
	पूर्ण

	अगर (IS_QLA8044(ha)) अणु
		qla8044_पढ़ो_reset_ढाँचा(vha);

		/* NOTE: If ql2xकरोntresethba==1, set IDC_CTRL DONTRESET_BIT0.
		 * If DONRESET_BIT0 is set, drivers should not set dev_state
		 * to NEED_RESET. But अगर NEED_RESET is set, drivers should
		 * should honor the reset. */
		अगर (ql2xकरोntresethba == 1)
			qla8044_set_idc_करोntreset(vha);
	पूर्ण

	ha->isp_ops->get_flash_version(vha, req->ring);
	ql_dbg(ql_dbg_init, vha, 0x0061,
	    "Configure NVRAM parameters...\n");

	/* Let priority शेष to FCP, can be overridden by nvram_config */
	ha->fc4_type_priority = FC4_PRIORITY_FCP;

	ha->isp_ops->nvram_config(vha);

	अगर (ha->fc4_type_priority != FC4_PRIORITY_FCP &&
	    ha->fc4_type_priority != FC4_PRIORITY_NVME)
		ha->fc4_type_priority = FC4_PRIORITY_FCP;

	ql_log(ql_log_info, vha, 0xffff, "FC4 priority set to %s\n",
	       ha->fc4_type_priority == FC4_PRIORITY_FCP ? "FCP" : "NVMe");

	अगर (ha->flags.disable_serdes) अणु
		/* Mask HBA via NVRAM settings? */
		ql_log(ql_log_info, vha, 0x0077,
		    "Masking HBA WWPN %8phN (via NVRAM).\n", vha->port_name);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x0078,
	    "Verifying loaded RISC code...\n");

	/* If smartsan enabled then require fdmi and rdp enabled */
	अगर (ql2xsmartsan) अणु
		ql2xfdmienable = 1;
		ql2xrdpenable = 1;
	पूर्ण

	अगर (qla2x00_isp_firmware(vha) != QLA_SUCCESS) अणु
		rval = ha->isp_ops->chip_diag(vha);
		अगर (rval)
			वापस (rval);
		rval = qla2x00_setup_chip(vha);
		अगर (rval)
			वापस (rval);
	पूर्ण

	अगर (IS_QLA84XX(ha)) अणु
		ha->cs84xx = qla84xx_get_chip(vha);
		अगर (!ha->cs84xx) अणु
			ql_log(ql_log_warn, vha, 0x00d0,
			    "Unable to configure ISP84XX.\n");
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	अगर (qla_ini_mode_enabled(vha) || qla_dual_mode_enabled(vha))
		rval = qla2x00_init_rings(vha);

	/* No poपूर्णांक in continuing अगर firmware initialization failed. */
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	ha->flags.chip_reset_करोne = 1;

	अगर (rval == QLA_SUCCESS && IS_QLA84XX(ha)) अणु
		/* Issue verअगरy 84xx FW IOCB to complete 84xx initialization */
		rval = qla84xx_init_chip(vha);
		अगर (rval != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x00d4,
			    "Unable to initialize ISP84XX.\n");
			qla84xx_put_chip(vha);
		पूर्ण
	पूर्ण

	/* Load the NIC Core f/w अगर we are the first protocol driver. */
	अगर (IS_QLA8031(ha)) अणु
		rval = qla83xx_nic_core_fw_load(vha);
		अगर (rval)
			ql_log(ql_log_warn, vha, 0x0124,
			    "Error in initializing NIC Core f/w.\n");
	पूर्ण

	अगर (IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha))
		qla24xx_पढ़ो_fcp_prio_cfg(vha);

	अगर (IS_P3P_TYPE(ha))
		qla82xx_set_driver_version(vha, QLA2XXX_VERSION);
	अन्यथा
		qla25xx_set_driver_version(vha, QLA2XXX_VERSION);

	वापस (rval);
पूर्ण

/**
 * qla2100_pci_config() - Setup ISP21xx PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2100_pci_config(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t w;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	pci_set_master(ha->pdev);
	pci_try_set_mwi(ha->pdev);

	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= (PCI_COMMAND_PARITY | PCI_COMMAND_SERR);
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, w);

	pci_disable_rom(ha->pdev);

	/* Get PCI bus inक्रमmation. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->pci_attr = rd_reg_word(&reg->ctrl_status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla2300_pci_config() - Setup ISP23xx PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2300_pci_config(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t	w;
	अचिन्हित दीर्घ   flags = 0;
	uपूर्णांक32_t	cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	pci_set_master(ha->pdev);
	pci_try_set_mwi(ha->pdev);

	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= (PCI_COMMAND_PARITY | PCI_COMMAND_SERR);

	अगर (IS_QLA2322(ha) || IS_QLA6322(ha))
		w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, w);

	/*
	 * If this is a 2300 card and not 2312, reset the
	 * COMMAND_INVALIDATE due to a bug in the 2300. Unक्रमtunately,
	 * the 2310 also reports itself as a 2300 so we need to get the
	 * fb revision level -- a 6 indicates it really is a 2300 and
	 * not a 2310.
	 */
	अगर (IS_QLA2300(ha)) अणु
		spin_lock_irqsave(&ha->hardware_lock, flags);

		/* Pause RISC. */
		wrt_reg_word(&reg->hccr, HCCR_PAUSE_RISC);
		क्रम (cnt = 0; cnt < 30000; cnt++) अणु
			अगर ((rd_reg_word(&reg->hccr) & HCCR_RISC_PAUSE) != 0)
				अवरोध;

			udelay(10);
		पूर्ण

		/* Select FPM रेजिस्टरs. */
		wrt_reg_word(&reg->ctrl_status, 0x20);
		rd_reg_word(&reg->ctrl_status);

		/* Get the fb rev level */
		ha->fb_rev = RD_FB_CMD_REG(ha, reg);

		अगर (ha->fb_rev == FPM_2300)
			pci_clear_mwi(ha->pdev);

		/* Deselect FPM रेजिस्टरs. */
		wrt_reg_word(&reg->ctrl_status, 0x0);
		rd_reg_word(&reg->ctrl_status);

		/* Release RISC module. */
		wrt_reg_word(&reg->hccr, HCCR_RELEASE_RISC);
		क्रम (cnt = 0; cnt < 30000; cnt++) अणु
			अगर ((rd_reg_word(&reg->hccr) & HCCR_RISC_PAUSE) == 0)
				अवरोध;

			udelay(10);
		पूर्ण

		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण

	pci_ग_लिखो_config_byte(ha->pdev, PCI_LATENCY_TIMER, 0x80);

	pci_disable_rom(ha->pdev);

	/* Get PCI bus inक्रमmation. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->pci_attr = rd_reg_word(&reg->ctrl_status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla24xx_pci_config() - Setup ISP24xx PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla24xx_pci_config(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t w;
	अचिन्हित दीर्घ flags = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	pci_set_master(ha->pdev);
	pci_try_set_mwi(ha->pdev);

	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= (PCI_COMMAND_PARITY | PCI_COMMAND_SERR);
	w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, w);

	pci_ग_लिखो_config_byte(ha->pdev, PCI_LATENCY_TIMER, 0x80);

	/* PCI-X -- adjust Maximum Memory Read Byte Count (2048). */
	अगर (pci_find_capability(ha->pdev, PCI_CAP_ID_PCIX))
		pcix_set_mmrbc(ha->pdev, 2048);

	/* PCIe -- adjust Maximum Read Request Size (2048). */
	अगर (pci_is_pcie(ha->pdev))
		pcie_set_पढ़ोrq(ha->pdev, 4096);

	pci_disable_rom(ha->pdev);

	ha->chip_revision = ha->pdev->revision;

	/* Get PCI bus inक्रमmation. */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->pci_attr = rd_reg_dword(&reg->ctrl_status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla25xx_pci_config() - Setup ISP25xx PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla25xx_pci_config(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t w;
	काष्ठा qla_hw_data *ha = vha->hw;

	pci_set_master(ha->pdev);
	pci_try_set_mwi(ha->pdev);

	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &w);
	w |= (PCI_COMMAND_PARITY | PCI_COMMAND_SERR);
	w &= ~PCI_COMMAND_INTX_DISABLE;
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, w);

	/* PCIe -- adjust Maximum Read Request Size (2048). */
	अगर (pci_is_pcie(ha->pdev))
		pcie_set_पढ़ोrq(ha->pdev, 4096);

	pci_disable_rom(ha->pdev);

	ha->chip_revision = ha->pdev->revision;

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla2x00_isp_firmware() - Choose firmware image.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_isp_firmware(scsi_qla_host_t *vha)
अणु
	पूर्णांक  rval;
	uपूर्णांक16_t loop_id, topo, sw_cap;
	uपूर्णांक8_t करोमुख्य, area, al_pa;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Assume loading risc code */
	rval = QLA_FUNCTION_FAILED;

	अगर (ha->flags.disable_risc_code_load) अणु
		ql_log(ql_log_info, vha, 0x0079, "RISC CODE NOT loaded.\n");

		/* Verअगरy checksum of loaded RISC code. */
		rval = qla2x00_verअगरy_checksum(vha, ha->fw_srisc_address);
		अगर (rval == QLA_SUCCESS) अणु
			/* And, verअगरy we are not in ROM code. */
			rval = qla2x00_get_adapter_id(vha, &loop_id, &al_pa,
			    &area, &करोमुख्य, &topo, &sw_cap);
		पूर्ण
	पूर्ण

	अगर (rval)
		ql_dbg(ql_dbg_init, vha, 0x007a,
		    "**** Load RISC code ****.\n");

	वापस (rval);
पूर्ण

/**
 * qla2x00_reset_chip() - Reset ISP chip.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_reset_chip(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ   flags = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	uपूर्णांक32_t	cnt;
	uपूर्णांक16_t	cmd;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस rval;

	ha->isp_ops->disable_पूर्णांकrs(ha);

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Turn off master enable */
	cmd = 0;
	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &cmd);
	cmd &= ~PCI_COMMAND_MASTER;
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, cmd);

	अगर (!IS_QLA2100(ha)) अणु
		/* Pause RISC. */
		wrt_reg_word(&reg->hccr, HCCR_PAUSE_RISC);
		अगर (IS_QLA2200(ha) || IS_QLA2300(ha)) अणु
			क्रम (cnt = 0; cnt < 30000; cnt++) अणु
				अगर ((rd_reg_word(&reg->hccr) &
				    HCCR_RISC_PAUSE) != 0)
					अवरोध;
				udelay(100);
			पूर्ण
		पूर्ण अन्यथा अणु
			rd_reg_word(&reg->hccr);	/* PCI Posting. */
			udelay(10);
		पूर्ण

		/* Select FPM रेजिस्टरs. */
		wrt_reg_word(&reg->ctrl_status, 0x20);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */

		/* FPM Soft Reset. */
		wrt_reg_word(&reg->fpm_diag_config, 0x100);
		rd_reg_word(&reg->fpm_diag_config);	/* PCI Posting. */

		/* Toggle Fpm Reset. */
		अगर (!IS_QLA2200(ha)) अणु
			wrt_reg_word(&reg->fpm_diag_config, 0x0);
			rd_reg_word(&reg->fpm_diag_config); /* PCI Posting. */
		पूर्ण

		/* Select frame buffer रेजिस्टरs. */
		wrt_reg_word(&reg->ctrl_status, 0x10);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */

		/* Reset frame buffer FIFOs. */
		अगर (IS_QLA2200(ha)) अणु
			WRT_FB_CMD_REG(ha, reg, 0xa000);
			RD_FB_CMD_REG(ha, reg);		/* PCI Posting. */
		पूर्ण अन्यथा अणु
			WRT_FB_CMD_REG(ha, reg, 0x00fc);

			/* Read back fb_cmd until zero or 3 seconds max */
			क्रम (cnt = 0; cnt < 3000; cnt++) अणु
				अगर ((RD_FB_CMD_REG(ha, reg) & 0xff) == 0)
					अवरोध;
				udelay(100);
			पूर्ण
		पूर्ण

		/* Select RISC module रेजिस्टरs. */
		wrt_reg_word(&reg->ctrl_status, 0);
		rd_reg_word(&reg->ctrl_status);		/* PCI Posting. */

		/* Reset RISC processor. */
		wrt_reg_word(&reg->hccr, HCCR_RESET_RISC);
		rd_reg_word(&reg->hccr);		/* PCI Posting. */

		/* Release RISC processor. */
		wrt_reg_word(&reg->hccr, HCCR_RELEASE_RISC);
		rd_reg_word(&reg->hccr);		/* PCI Posting. */
	पूर्ण

	wrt_reg_word(&reg->hccr, HCCR_CLR_RISC_INT);
	wrt_reg_word(&reg->hccr, HCCR_CLR_HOST_INT);

	/* Reset ISP chip. */
	wrt_reg_word(&reg->ctrl_status, CSR_ISP_SOFT_RESET);

	/* Wait क्रम RISC to recover from reset. */
	अगर (IS_QLA2100(ha) || IS_QLA2200(ha) || IS_QLA2300(ha)) अणु
		/*
		 * It is necessary to क्रम a delay here since the card करोesn't
		 * respond to PCI पढ़ोs during a reset. On some architectures
		 * this will result in an MCA.
		 */
		udelay(20);
		क्रम (cnt = 30000; cnt; cnt--) अणु
			अगर ((rd_reg_word(&reg->ctrl_status) &
			    CSR_ISP_SOFT_RESET) == 0)
				अवरोध;
			udelay(100);
		पूर्ण
	पूर्ण अन्यथा
		udelay(10);

	/* Reset RISC processor. */
	wrt_reg_word(&reg->hccr, HCCR_RESET_RISC);

	wrt_reg_word(&reg->semaphore, 0);

	/* Release RISC processor. */
	wrt_reg_word(&reg->hccr, HCCR_RELEASE_RISC);
	rd_reg_word(&reg->hccr);			/* PCI Posting. */

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha) || IS_QLA2300(ha)) अणु
		क्रम (cnt = 0; cnt < 30000; cnt++) अणु
			अगर (RD_MAILBOX_REG(ha, reg, 0) != MBS_BUSY)
				अवरोध;

			udelay(100);
		पूर्ण
	पूर्ण अन्यथा
		udelay(100);

	/* Turn on master enable */
	cmd |= PCI_COMMAND_MASTER;
	pci_ग_लिखो_config_word(ha->pdev, PCI_COMMAND, cmd);

	/* Disable RISC छोड़ो on FPM parity error. */
	अगर (!IS_QLA2100(ha)) अणु
		wrt_reg_word(&reg->hccr, HCCR_DISABLE_PARITY_PAUSE);
		rd_reg_word(&reg->hccr);		/* PCI Posting. */
	पूर्ण

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla81xx_reset_mpi() - Reset's MPI FW via Write MPI Register MBC.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla81xx_reset_mpi(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t mb[4] = अणु0x1010, 0, 1, 0पूर्ण;

	अगर (!IS_QLA81XX(vha->hw))
		वापस QLA_SUCCESS;

	वापस qla81xx_ग_लिखो_mpi_रेजिस्टर(vha, mb);
पूर्ण

अटल पूर्णांक
qla_chk_risc_recovery(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	__le16 __iomem *mbptr = &reg->mailbox0;
	पूर्णांक i;
	u16 mb[32];
	पूर्णांक rc = QLA_SUCCESS;

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस rc;

	/* this check is only valid after RISC reset */
	mb[0] = rd_reg_word(mbptr);
	mbptr++;
	अगर (mb[0] == 0xf) अणु
		rc = QLA_FUNCTION_FAILED;

		क्रम (i = 1; i < 32; i++) अणु
			mb[i] = rd_reg_word(mbptr);
			mbptr++;
		पूर्ण

		ql_log(ql_log_warn, vha, 0x1015,
		       "RISC reset failed. mb[0-7] %04xh %04xh %04xh %04xh %04xh %04xh %04xh %04xh\n",
		       mb[0], mb[1], mb[2], mb[3], mb[4], mb[5], mb[6], mb[7]);
		ql_log(ql_log_warn, vha, 0x1015,
		       "RISC reset failed. mb[8-15] %04xh %04xh %04xh %04xh %04xh %04xh %04xh %04xh\n",
		       mb[8], mb[9], mb[10], mb[11], mb[12], mb[13], mb[14],
		       mb[15]);
		ql_log(ql_log_warn, vha, 0x1015,
		       "RISC reset failed. mb[16-23] %04xh %04xh %04xh %04xh %04xh %04xh %04xh %04xh\n",
		       mb[16], mb[17], mb[18], mb[19], mb[20], mb[21], mb[22],
		       mb[23]);
		ql_log(ql_log_warn, vha, 0x1015,
		       "RISC reset failed. mb[24-31] %04xh %04xh %04xh %04xh %04xh %04xh %04xh %04xh\n",
		       mb[24], mb[25], mb[26], mb[27], mb[28], mb[29], mb[30],
		       mb[31]);
	पूर्ण
	वापस rc;
पूर्ण

/**
 * qla24xx_reset_risc() - Perक्रमm full reset of ISP24xx RISC.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
अटल अंतरभूत पूर्णांक
qla24xx_reset_risc(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	uपूर्णांक32_t cnt;
	uपूर्णांक16_t wd;
	अटल पूर्णांक abts_cnt; /* ISP पात retry counts */
	पूर्णांक rval = QLA_SUCCESS;
	पूर्णांक prपूर्णांक = 1;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Reset RISC. */
	wrt_reg_dword(&reg->ctrl_status, CSRX_DMA_SHUTDOWN|MWB_4096_BYTES);
	क्रम (cnt = 0; cnt < 30000; cnt++) अणु
		अगर ((rd_reg_dword(&reg->ctrl_status) & CSRX_DMA_ACTIVE) == 0)
			अवरोध;

		udelay(10);
	पूर्ण

	अगर (!(rd_reg_dword(&reg->ctrl_status) & CSRX_DMA_ACTIVE))
		set_bit(DMA_SHUTDOWN_CMPL, &ha->fw_dump_cap_flags);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x017e,
	    "HCCR: 0x%x, Control Status %x, DMA active status:0x%x\n",
	    rd_reg_dword(&reg->hccr),
	    rd_reg_dword(&reg->ctrl_status),
	    (rd_reg_dword(&reg->ctrl_status) & CSRX_DMA_ACTIVE));

	wrt_reg_dword(&reg->ctrl_status,
	    CSRX_ISP_SOFT_RESET|CSRX_DMA_SHUTDOWN|MWB_4096_BYTES);
	pci_पढ़ो_config_word(ha->pdev, PCI_COMMAND, &wd);

	udelay(100);

	/* Wait क्रम firmware to complete NVRAM accesses. */
	rd_reg_word(&reg->mailbox0);
	क्रम (cnt = 10000; rd_reg_word(&reg->mailbox0) != 0 &&
	    rval == QLA_SUCCESS; cnt--) अणु
		barrier();
		अगर (cnt)
			udelay(5);
		अन्यथा
			rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण

	अगर (rval == QLA_SUCCESS)
		set_bit(ISP_MBX_RDY, &ha->fw_dump_cap_flags);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x017f,
	    "HCCR: 0x%x, MailBox0 Status 0x%x\n",
	    rd_reg_dword(&reg->hccr),
	    rd_reg_word(&reg->mailbox0));

	/* Wait क्रम soft-reset to complete. */
	rd_reg_dword(&reg->ctrl_status);
	क्रम (cnt = 0; cnt < 60; cnt++) अणु
		barrier();
		अगर ((rd_reg_dword(&reg->ctrl_status) &
		    CSRX_ISP_SOFT_RESET) == 0)
			अवरोध;

		udelay(5);
	पूर्ण
	अगर (!(rd_reg_dword(&reg->ctrl_status) & CSRX_ISP_SOFT_RESET))
		set_bit(ISP_SOFT_RESET_CMPL, &ha->fw_dump_cap_flags);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x015d,
	    "HCCR: 0x%x, Soft Reset status: 0x%x\n",
	    rd_reg_dword(&reg->hccr),
	    rd_reg_dword(&reg->ctrl_status));

	/* If required, करो an MPI FW reset now */
	अगर (test_and_clear_bit(MPI_RESET_NEEDED, &vha->dpc_flags)) अणु
		अगर (qla81xx_reset_mpi(vha) != QLA_SUCCESS) अणु
			अगर (++abts_cnt < 5) अणु
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				set_bit(MPI_RESET_NEEDED, &vha->dpc_flags);
			पूर्ण अन्यथा अणु
				/*
				 * We exhausted the ISP पात retries. We have to
				 * set the board offline.
				 */
				abts_cnt = 0;
				vha->flags.online = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	wrt_reg_dword(&reg->hccr, HCCRX_SET_RISC_RESET);
	rd_reg_dword(&reg->hccr);

	wrt_reg_dword(&reg->hccr, HCCRX_REL_RISC_PAUSE);
	rd_reg_dword(&reg->hccr);

	wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_RESET);
	mdelay(10);
	rd_reg_dword(&reg->hccr);

	wd = rd_reg_word(&reg->mailbox0);
	क्रम (cnt = 300; wd != 0 && rval == QLA_SUCCESS; cnt--) अणु
		barrier();
		अगर (cnt) अणु
			mdelay(1);
			अगर (prपूर्णांक && qla_chk_risc_recovery(vha))
				prपूर्णांक = 0;

			wd = rd_reg_word(&reg->mailbox0);
		पूर्ण अन्यथा अणु
			rval = QLA_FUNCTION_TIMEOUT;

			ql_log(ql_log_warn, vha, 0x015e,
			       "RISC reset timeout\n");
		पूर्ण
	पूर्ण

	अगर (rval == QLA_SUCCESS)
		set_bit(RISC_RDY_AFT_RESET, &ha->fw_dump_cap_flags);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x015e,
	    "Host Risc 0x%x, mailbox0 0x%x\n",
	    rd_reg_dword(&reg->hccr),
	     rd_reg_word(&reg->mailbox0));

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x015f,
	    "Driver in %s mode\n",
	    IS_NOPOLLING_TYPE(ha) ? "Interrupt" : "Polling");

	अगर (IS_NOPOLLING_TYPE(ha))
		ha->isp_ops->enable_पूर्णांकrs(ha);

	वापस rval;
पूर्ण

अटल व्योम
qla25xx_पढ़ो_risc_sema_reg(scsi_qla_host_t *vha, uपूर्णांक32_t *data)
अणु
	काष्ठा device_reg_24xx __iomem *reg = &vha->hw->iobase->isp24;

	wrt_reg_dword(&reg->iobase_addr, RISC_REGISTER_BASE_OFFSET);
	*data = rd_reg_dword(&reg->iobase_winकरोw + RISC_REGISTER_WINDOW_OFFSET);
पूर्ण

अटल व्योम
qla25xx_ग_लिखो_risc_sema_reg(scsi_qla_host_t *vha, uपूर्णांक32_t data)
अणु
	काष्ठा device_reg_24xx __iomem *reg = &vha->hw->iobase->isp24;

	wrt_reg_dword(&reg->iobase_addr, RISC_REGISTER_BASE_OFFSET);
	wrt_reg_dword(&reg->iobase_winकरोw + RISC_REGISTER_WINDOW_OFFSET, data);
पूर्ण

अटल व्योम
qla25xx_manipulate_risc_semaphore(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t wd32 = 0;
	uपूर्णांक delta_msec = 100;
	uपूर्णांक elapsed_msec = 0;
	uपूर्णांक समयout_msec;
	uदीर्घ n;

	अगर (vha->hw->pdev->subप्रणाली_device != 0x0175 &&
	    vha->hw->pdev->subप्रणाली_device != 0x0240)
		वापस;

	wrt_reg_dword(&vha->hw->iobase->isp24.hccr, HCCRX_SET_RISC_PAUSE);
	udelay(100);

attempt:
	समयout_msec = TIMEOUT_SEMAPHORE;
	n = समयout_msec / delta_msec;
	जबतक (n--) अणु
		qla25xx_ग_लिखो_risc_sema_reg(vha, RISC_SEMAPHORE_SET);
		qla25xx_पढ़ो_risc_sema_reg(vha, &wd32);
		अगर (wd32 & RISC_SEMAPHORE)
			अवरोध;
		msleep(delta_msec);
		elapsed_msec += delta_msec;
		अगर (elapsed_msec > TIMEOUT_TOTAL_ELAPSED)
			जाओ क्रमce;
	पूर्ण

	अगर (!(wd32 & RISC_SEMAPHORE))
		जाओ क्रमce;

	अगर (!(wd32 & RISC_SEMAPHORE_FORCE))
		जाओ acquired;

	qla25xx_ग_लिखो_risc_sema_reg(vha, RISC_SEMAPHORE_CLR);
	समयout_msec = TIMEOUT_SEMAPHORE_FORCE;
	n = समयout_msec / delta_msec;
	जबतक (n--) अणु
		qla25xx_पढ़ो_risc_sema_reg(vha, &wd32);
		अगर (!(wd32 & RISC_SEMAPHORE_FORCE))
			अवरोध;
		msleep(delta_msec);
		elapsed_msec += delta_msec;
		अगर (elapsed_msec > TIMEOUT_TOTAL_ELAPSED)
			जाओ क्रमce;
	पूर्ण

	अगर (wd32 & RISC_SEMAPHORE_FORCE)
		qla25xx_ग_लिखो_risc_sema_reg(vha, RISC_SEMAPHORE_FORCE_CLR);

	जाओ attempt;

क्रमce:
	qla25xx_ग_लिखो_risc_sema_reg(vha, RISC_SEMAPHORE_FORCE_SET);

acquired:
	वापस;
पूर्ण

/**
 * qla24xx_reset_chip() - Reset ISP24xx chip.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla24xx_reset_chip(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (pci_channel_offline(ha->pdev) &&
	    ha->flags.pci_channel_io_perm_failure) अणु
		वापस rval;
	पूर्ण

	ha->isp_ops->disable_पूर्णांकrs(ha);

	qla25xx_manipulate_risc_semaphore(vha);

	/* Perक्रमm RISC reset. */
	rval = qla24xx_reset_risc(vha);

	वापस rval;
पूर्ण

/**
 * qla2x00_chip_diag() - Test chip क्रम proper operation.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_chip_diag(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	अचिन्हित दीर्घ	flags = 0;
	uपूर्णांक16_t	data;
	uपूर्णांक32_t	cnt;
	uपूर्णांक16_t	mb[5];
	काष्ठा req_que *req = ha->req_q_map[0];

	/* Assume a failed state */
	rval = QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_init, vha, 0x007b, "Testing device at %p.\n",
	       &reg->flash_address);

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Reset ISP chip. */
	wrt_reg_word(&reg->ctrl_status, CSR_ISP_SOFT_RESET);

	/*
	 * We need to have a delay here since the card will not respond जबतक
	 * in reset causing an MCA on some architectures.
	 */
	udelay(20);
	data = qla2x00_debounce_रेजिस्टर(&reg->ctrl_status);
	क्रम (cnt = 6000000 ; cnt && (data & CSR_ISP_SOFT_RESET); cnt--) अणु
		udelay(5);
		data = rd_reg_word(&reg->ctrl_status);
		barrier();
	पूर्ण

	अगर (!cnt)
		जाओ chip_diag_failed;

	ql_dbg(ql_dbg_init, vha, 0x007c,
	    "Reset register cleared by chip reset.\n");

	/* Reset RISC processor. */
	wrt_reg_word(&reg->hccr, HCCR_RESET_RISC);
	wrt_reg_word(&reg->hccr, HCCR_RELEASE_RISC);

	/* Workaround क्रम QLA2312 PCI parity error */
	अगर (IS_QLA2100(ha) || IS_QLA2200(ha) || IS_QLA2300(ha)) अणु
		data = qla2x00_debounce_रेजिस्टर(MAILBOX_REG(ha, reg, 0));
		क्रम (cnt = 6000000; cnt && (data == MBS_BUSY); cnt--) अणु
			udelay(5);
			data = RD_MAILBOX_REG(ha, reg, 0);
			barrier();
		पूर्ण
	पूर्ण अन्यथा
		udelay(10);

	अगर (!cnt)
		जाओ chip_diag_failed;

	/* Check product ID of chip */
	ql_dbg(ql_dbg_init, vha, 0x007d, "Checking product ID of chip.\n");

	mb[1] = RD_MAILBOX_REG(ha, reg, 1);
	mb[2] = RD_MAILBOX_REG(ha, reg, 2);
	mb[3] = RD_MAILBOX_REG(ha, reg, 3);
	mb[4] = qla2x00_debounce_रेजिस्टर(MAILBOX_REG(ha, reg, 4));
	अगर (mb[1] != PROD_ID_1 || (mb[2] != PROD_ID_2 && mb[2] != PROD_ID_2a) ||
	    mb[3] != PROD_ID_3) अणु
		ql_log(ql_log_warn, vha, 0x0062,
		    "Wrong product ID = 0x%x,0x%x,0x%x.\n",
		    mb[1], mb[2], mb[3]);

		जाओ chip_diag_failed;
	पूर्ण
	ha->product_id[0] = mb[1];
	ha->product_id[1] = mb[2];
	ha->product_id[2] = mb[3];
	ha->product_id[3] = mb[4];

	/* Adjust fw RISC transfer size */
	अगर (req->length > 1024)
		ha->fw_transfer_size = REQUEST_ENTRY_SIZE * 1024;
	अन्यथा
		ha->fw_transfer_size = REQUEST_ENTRY_SIZE *
		    req->length;

	अगर (IS_QLA2200(ha) &&
	    RD_MAILBOX_REG(ha, reg, 7) == QLA2200A_RISC_ROM_VER) अणु
		/* Limit firmware transfer size with a 2200A */
		ql_dbg(ql_dbg_init, vha, 0x007e, "Found QLA2200A Chip.\n");

		ha->device_type |= DT_ISP2200A;
		ha->fw_transfer_size = 128;
	पूर्ण

	/* Wrap Incoming Mailboxes Test. */
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	ql_dbg(ql_dbg_init, vha, 0x007f, "Checking mailboxes.\n");
	rval = qla2x00_mbx_reg_test(vha);
	अगर (rval)
		ql_log(ql_log_warn, vha, 0x0080,
		    "Failed mailbox send register test.\n");
	अन्यथा
		/* Flag a successful rval */
		rval = QLA_SUCCESS;
	spin_lock_irqsave(&ha->hardware_lock, flags);

chip_diag_failed:
	अगर (rval)
		ql_log(ql_log_info, vha, 0x0081,
		    "Chip diagnostics **** FAILED ****.\n");

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस (rval);
पूर्ण

/**
 * qla24xx_chip_diag() - Test ISP24xx क्रम proper operation.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qla24xx_chip_diag(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];

	अगर (IS_P3P_TYPE(ha))
		वापस QLA_SUCCESS;

	ha->fw_transfer_size = REQUEST_ENTRY_SIZE * req->length;

	rval = qla2x00_mbx_reg_test(vha);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0082,
		    "Failed mailbox send register test.\n");
	पूर्ण अन्यथा अणु
		/* Flag a successful rval */
		rval = QLA_SUCCESS;
	पूर्ण

	वापस rval;
पूर्ण

अटल व्योम
qla2x00_init_fce_trace(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	dma_addr_t tc_dma;
	व्योम *tc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस;

	अगर (!IS_QLA25XX(ha) && !IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस;

	अगर (ha->fce) अणु
		ql_dbg(ql_dbg_init, vha, 0x00bd,
		       "%s: FCE Mem is already allocated.\n",
		       __func__);
		वापस;
	पूर्ण

	/* Allocate memory क्रम Fibre Channel Event Buffer. */
	tc = dma_alloc_coherent(&ha->pdev->dev, FCE_SIZE, &tc_dma,
				GFP_KERNEL);
	अगर (!tc) अणु
		ql_log(ql_log_warn, vha, 0x00be,
		       "Unable to allocate (%d KB) for FCE.\n",
		       FCE_SIZE / 1024);
		वापस;
	पूर्ण

	rval = qla2x00_enable_fce_trace(vha, tc_dma, FCE_NUM_BUFFERS,
					ha->fce_mb, &ha->fce_bufs);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x00bf,
		       "Unable to initialize FCE (%d).\n", rval);
		dma_मुक्त_coherent(&ha->pdev->dev, FCE_SIZE, tc, tc_dma);
		वापस;
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x00c0,
	       "Allocated (%d KB) for FCE...\n", FCE_SIZE / 1024);

	ha->flags.fce_enabled = 1;
	ha->fce_dma = tc_dma;
	ha->fce = tc;
पूर्ण

अटल व्योम
qla2x00_init_eft_trace(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	dma_addr_t tc_dma;
	व्योम *tc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस;

	अगर (ha->eft) अणु
		ql_dbg(ql_dbg_init, vha, 0x00bd,
		    "%s: EFT Mem is already allocated.\n",
		    __func__);
		वापस;
	पूर्ण

	/* Allocate memory क्रम Extended Trace Buffer. */
	tc = dma_alloc_coherent(&ha->pdev->dev, EFT_SIZE, &tc_dma,
				GFP_KERNEL);
	अगर (!tc) अणु
		ql_log(ql_log_warn, vha, 0x00c1,
		       "Unable to allocate (%d KB) for EFT.\n",
		       EFT_SIZE / 1024);
		वापस;
	पूर्ण

	rval = qla2x00_enable_eft_trace(vha, tc_dma, EFT_NUM_BUFFERS);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x00c2,
		       "Unable to initialize EFT (%d).\n", rval);
		dma_मुक्त_coherent(&ha->pdev->dev, EFT_SIZE, tc, tc_dma);
		वापस;
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x00c3,
	       "Allocated (%d KB) EFT ...\n", EFT_SIZE / 1024);

	ha->eft_dma = tc_dma;
	ha->eft = tc;
पूर्ण

अटल व्योम
qla2x00_alloc_offload_mem(scsi_qla_host_t *vha)
अणु
	qla2x00_init_fce_trace(vha);
	qla2x00_init_eft_trace(vha);
पूर्ण

व्योम
qla2x00_alloc_fw_dump(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t dump_size, fixed_size, mem_size, req_q_size, rsp_q_size,
	    eft_size, fce_size, mq_size;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];
	काष्ठा qla2xxx_fw_dump *fw_dump;

	dump_size = fixed_size = mem_size = eft_size = fce_size = mq_size = 0;
	req_q_size = rsp_q_size = 0;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha)) अणु
		fixed_size = माप(काष्ठा qla2100_fw_dump);
	पूर्ण अन्यथा अगर (IS_QLA23XX(ha)) अणु
		fixed_size = दुरत्व(काष्ठा qla2300_fw_dump, data_ram);
		mem_size = (ha->fw_memory_size - 0x11000 + 1) *
		    माप(uपूर्णांक16_t);
	पूर्ण अन्यथा अगर (IS_FWI2_CAPABLE(ha)) अणु
		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
			fixed_size = दुरत्व(काष्ठा qla83xx_fw_dump, ext_mem);
		अन्यथा अगर (IS_QLA81XX(ha))
			fixed_size = दुरत्व(काष्ठा qla81xx_fw_dump, ext_mem);
		अन्यथा अगर (IS_QLA25XX(ha))
			fixed_size = दुरत्व(काष्ठा qla25xx_fw_dump, ext_mem);
		अन्यथा
			fixed_size = दुरत्व(काष्ठा qla24xx_fw_dump, ext_mem);

		mem_size = (ha->fw_memory_size - 0x100000 + 1) *
		    माप(uपूर्णांक32_t);
		अगर (ha->mqenable) अणु
			अगर (!IS_QLA83XX(ha) && !IS_QLA27XX(ha) &&
			    !IS_QLA28XX(ha))
				mq_size = माप(काष्ठा qla2xxx_mq_chain);
			/*
			 * Allocate maximum buffer size क्रम all queues - Q0.
			 * Resizing must be करोne at end-of-dump processing.
			 */
			mq_size += (ha->max_req_queues - 1) *
			    (req->length * माप(request_t));
			mq_size += (ha->max_rsp_queues - 1) *
			    (rsp->length * माप(response_t));
		पूर्ण
		अगर (ha->tgt.atio_ring)
			mq_size += ha->tgt.atio_q_length * माप(request_t);

		qla2x00_init_fce_trace(vha);
		अगर (ha->fce)
			fce_size = माप(काष्ठा qla2xxx_fce_chain) + FCE_SIZE;
		qla2x00_init_eft_trace(vha);
		अगर (ha->eft)
			eft_size = EFT_SIZE;
	पूर्ण

	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		काष्ठा fwdt *fwdt = ha->fwdt;
		uपूर्णांक j;

		क्रम (j = 0; j < 2; j++, fwdt++) अणु
			अगर (!fwdt->ढाँचा) अणु
				ql_dbg(ql_dbg_init, vha, 0x00ba,
				    "-> fwdt%u no template\n", j);
				जारी;
			पूर्ण
			ql_dbg(ql_dbg_init, vha, 0x00fa,
			    "-> fwdt%u calculating fwdump size...\n", j);
			fwdt->dump_size = qla27xx_fwdt_calculate_dump_size(
			    vha, fwdt->ढाँचा);
			ql_dbg(ql_dbg_init, vha, 0x00fa,
			    "-> fwdt%u calculated fwdump size = %#lx bytes\n",
			    j, fwdt->dump_size);
			dump_size += fwdt->dump_size;
		पूर्ण
		/* Add space क्रम spare MPI fw dump. */
		dump_size += ha->fwdt[1].dump_size;
	पूर्ण अन्यथा अणु
		req_q_size = req->length * माप(request_t);
		rsp_q_size = rsp->length * माप(response_t);
		dump_size = दुरत्व(काष्ठा qla2xxx_fw_dump, isp);
		dump_size += fixed_size + mem_size + req_q_size + rsp_q_size
			+ eft_size;
		ha->chain_offset = dump_size;
		dump_size += mq_size + fce_size;
		अगर (ha->exchoffld_buf)
			dump_size += माप(काष्ठा qla2xxx_offld_chain) +
				ha->exchoffld_size;
		अगर (ha->exlogin_buf)
			dump_size += माप(काष्ठा qla2xxx_offld_chain) +
				ha->exlogin_size;
	पूर्ण

	अगर (!ha->fw_dump_len || dump_size > ha->fw_dump_alloc_len) अणु

		ql_dbg(ql_dbg_init, vha, 0x00c5,
		    "%s dump_size %d fw_dump_len %d fw_dump_alloc_len %d\n",
		    __func__, dump_size, ha->fw_dump_len,
		    ha->fw_dump_alloc_len);

		fw_dump = vदो_स्मृति(dump_size);
		अगर (!fw_dump) अणु
			ql_log(ql_log_warn, vha, 0x00c4,
			    "Unable to allocate (%d KB) for firmware dump.\n",
			    dump_size / 1024);
		पूर्ण अन्यथा अणु
			mutex_lock(&ha->optrom_mutex);
			अगर (ha->fw_dumped) अणु
				स_नकल(fw_dump, ha->fw_dump, ha->fw_dump_len);
				vमुक्त(ha->fw_dump);
				ha->fw_dump = fw_dump;
				ha->fw_dump_alloc_len =  dump_size;
				ql_dbg(ql_dbg_init, vha, 0x00c5,
				    "Re-Allocated (%d KB) and save firmware dump.\n",
				    dump_size / 1024);
			पूर्ण अन्यथा अणु
				vमुक्त(ha->fw_dump);
				ha->fw_dump = fw_dump;

				ha->fw_dump_len = ha->fw_dump_alloc_len =
				    dump_size;
				ql_dbg(ql_dbg_init, vha, 0x00c5,
				    "Allocated (%d KB) for firmware dump.\n",
				    dump_size / 1024);

				अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
					ha->mpi_fw_dump = (अक्षर *)fw_dump +
						ha->fwdt[1].dump_size;
					mutex_unlock(&ha->optrom_mutex);
					वापस;
				पूर्ण

				ha->fw_dump->signature[0] = 'Q';
				ha->fw_dump->signature[1] = 'L';
				ha->fw_dump->signature[2] = 'G';
				ha->fw_dump->signature[3] = 'C';
				ha->fw_dump->version = htonl(1);

				ha->fw_dump->fixed_size = htonl(fixed_size);
				ha->fw_dump->mem_size = htonl(mem_size);
				ha->fw_dump->req_q_size = htonl(req_q_size);
				ha->fw_dump->rsp_q_size = htonl(rsp_q_size);

				ha->fw_dump->eft_size = htonl(eft_size);
				ha->fw_dump->eft_addr_l =
				    htonl(LSD(ha->eft_dma));
				ha->fw_dump->eft_addr_h =
				    htonl(MSD(ha->eft_dma));

				ha->fw_dump->header_size =
					htonl(दुरत्व
					    (काष्ठा qla2xxx_fw_dump, isp));
			पूर्ण
			mutex_unlock(&ha->optrom_mutex);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
qla81xx_mpi_sync(scsi_qla_host_t *vha)
अणु
#घोषणा MPS_MASK	0xe0
	पूर्णांक rval;
	uपूर्णांक16_t dc;
	uपूर्णांक32_t dw;

	अगर (!IS_QLA81XX(vha->hw))
		वापस QLA_SUCCESS;

	rval = qla2x00_ग_लिखो_ram_word(vha, 0x7c00, 1);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x0105,
		    "Unable to acquire semaphore.\n");
		जाओ करोne;
	पूर्ण

	pci_पढ़ो_config_word(vha->hw->pdev, 0x54, &dc);
	rval = qla2x00_पढ़ो_ram_word(vha, 0x7a15, &dw);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x0067, "Unable to read sync.\n");
		जाओ करोne_release;
	पूर्ण

	dc &= MPS_MASK;
	अगर (dc == (dw & MPS_MASK))
		जाओ करोne_release;

	dw &= ~MPS_MASK;
	dw |= dc;
	rval = qla2x00_ग_लिखो_ram_word(vha, 0x7a15, dw);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x0114, "Unable to gain sync.\n");
	पूर्ण

करोne_release:
	rval = qla2x00_ग_लिखो_ram_word(vha, 0x7c00, 0);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x006d,
		    "Unable to release semaphore.\n");
	पूर्ण

करोne:
	वापस rval;
पूर्ण

पूर्णांक
qla2x00_alloc_outstanding_cmds(काष्ठा qla_hw_data *ha, काष्ठा req_que *req)
अणु
	/* Don't try to पुनः_स्मृतिate the array */
	अगर (req->outstanding_cmds)
		वापस QLA_SUCCESS;

	अगर (!IS_FWI2_CAPABLE(ha))
		req->num_outstanding_cmds = DEFAULT_OUTSTANDING_COMMANDS;
	अन्यथा अणु
		अगर (ha->cur_fw_xcb_count <= ha->cur_fw_iocb_count)
			req->num_outstanding_cmds = ha->cur_fw_xcb_count;
		अन्यथा
			req->num_outstanding_cmds = ha->cur_fw_iocb_count;
	पूर्ण

	req->outstanding_cmds = kसुस्मृति(req->num_outstanding_cmds,
					माप(srb_t *),
					GFP_KERNEL);

	अगर (!req->outstanding_cmds) अणु
		/*
		 * Try to allocate a minimal size just so we can get through
		 * initialization.
		 */
		req->num_outstanding_cmds = MIN_OUTSTANDING_COMMANDS;
		req->outstanding_cmds = kसुस्मृति(req->num_outstanding_cmds,
						माप(srb_t *),
						GFP_KERNEL);

		अगर (!req->outstanding_cmds) अणु
			ql_log(ql_log_fatal, शून्य, 0x0126,
			    "Failed to allocate memory for "
			    "outstanding_cmds for req_que %p.\n", req);
			req->num_outstanding_cmds = 0;
			वापस QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

#घोषणा PRINT_FIELD(_field, _flag, _str) अणु		\
	अगर (a0->_field & _flag) अणु\
		अगर (p) अणु\
			म_जोड़ो(ptr, "|");\
			ptr++;\
			leftover--;\
		पूर्ण \
		len = snम_लिखो(ptr, leftover, "%s", _str);	\
		p = 1;\
		leftover -= len;\
		ptr += len; \
	पूर्ण \
पूर्ण

अटल व्योम qla2xxx_prपूर्णांक_sfp_info(काष्ठा scsi_qla_host *vha)
अणु
#घोषणा STR_LEN 64
	काष्ठा sff_8247_a0 *a0 = (काष्ठा sff_8247_a0 *)vha->hw->sfp_data;
	u8 str[STR_LEN], *ptr, p;
	पूर्णांक leftover, len;

	स_रखो(str, 0, STR_LEN);
	snम_लिखो(str, SFF_VEN_NAME_LEN+1, a0->venकरोr_name);
	ql_dbg(ql_dbg_init, vha, 0x015a,
	    "SFP MFG Name: %s\n", str);

	स_रखो(str, 0, STR_LEN);
	snम_लिखो(str, SFF_PART_NAME_LEN+1, a0->venकरोr_pn);
	ql_dbg(ql_dbg_init, vha, 0x015c,
	    "SFP Part Name: %s\n", str);

	/* media */
	स_रखो(str, 0, STR_LEN);
	ptr = str;
	leftover = STR_LEN;
	p = len = 0;
	PRINT_FIELD(fc_med_cc9, FC_MED_TW, "Twin AX");
	PRINT_FIELD(fc_med_cc9, FC_MED_TP, "Twisted Pair");
	PRINT_FIELD(fc_med_cc9, FC_MED_MI, "Min Coax");
	PRINT_FIELD(fc_med_cc9, FC_MED_TV, "Video Coax");
	PRINT_FIELD(fc_med_cc9, FC_MED_M6, "MultiMode 62.5um");
	PRINT_FIELD(fc_med_cc9, FC_MED_M5, "MultiMode 50um");
	PRINT_FIELD(fc_med_cc9, FC_MED_SM, "SingleMode");
	ql_dbg(ql_dbg_init, vha, 0x0160,
	    "SFP Media: %s\n", str);

	/* link length */
	स_रखो(str, 0, STR_LEN);
	ptr = str;
	leftover = STR_LEN;
	p = len = 0;
	PRINT_FIELD(fc_ll_cc7, FC_LL_VL, "Very Long");
	PRINT_FIELD(fc_ll_cc7, FC_LL_S, "Short");
	PRINT_FIELD(fc_ll_cc7, FC_LL_I, "Intermediate");
	PRINT_FIELD(fc_ll_cc7, FC_LL_L, "Long");
	PRINT_FIELD(fc_ll_cc7, FC_LL_M, "Medium");
	ql_dbg(ql_dbg_init, vha, 0x0196,
	    "SFP Link Length: %s\n", str);

	स_रखो(str, 0, STR_LEN);
	ptr = str;
	leftover = STR_LEN;
	p = len = 0;
	PRINT_FIELD(fc_ll_cc7, FC_LL_SA, "Short Wave (SA)");
	PRINT_FIELD(fc_ll_cc7, FC_LL_LC, "Long Wave(LC)");
	PRINT_FIELD(fc_tec_cc8, FC_TEC_SN, "Short Wave (SN)");
	PRINT_FIELD(fc_tec_cc8, FC_TEC_SL, "Short Wave (SL)");
	PRINT_FIELD(fc_tec_cc8, FC_TEC_LL, "Long Wave (LL)");
	ql_dbg(ql_dbg_init, vha, 0x016e,
	    "SFP FC Link Tech: %s\n", str);

	अगर (a0->length_km)
		ql_dbg(ql_dbg_init, vha, 0x016f,
		    "SFP Distant: %d km\n", a0->length_km);
	अगर (a0->length_100m)
		ql_dbg(ql_dbg_init, vha, 0x0170,
		    "SFP Distant: %d m\n", a0->length_100m*100);
	अगर (a0->length_50um_10m)
		ql_dbg(ql_dbg_init, vha, 0x0189,
		    "SFP Distant (WL=50um): %d m\n", a0->length_50um_10m * 10);
	अगर (a0->length_62um_10m)
		ql_dbg(ql_dbg_init, vha, 0x018a,
		  "SFP Distant (WL=62.5um): %d m\n", a0->length_62um_10m * 10);
	अगर (a0->length_om4_10m)
		ql_dbg(ql_dbg_init, vha, 0x0194,
		    "SFP Distant (OM4): %d m\n", a0->length_om4_10m * 10);
	अगर (a0->length_om3_10m)
		ql_dbg(ql_dbg_init, vha, 0x0195,
		    "SFP Distant (OM3): %d m\n", a0->length_om3_10m * 10);
पूर्ण


/**
 * qla24xx_detect_sfp()
 *
 * @vha: adapter state poपूर्णांकer.
 *
 * @वापस
 *	0 -- Configure firmware to use लघु-range settings -- normal
 *	     buffer-to-buffer credits.
 *
 *	1 -- Configure firmware to use दीर्घ-range settings -- extra
 *	     buffer-to-buffer credits should be allocated with
 *	     ha->lr_distance containing distance settings from NVRAM or SFP
 *	     (अगर supported).
 */
पूर्णांक
qla24xx_detect_sfp(scsi_qla_host_t *vha)
अणु
	पूर्णांक rc, used_nvram;
	काष्ठा sff_8247_a0 *a;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा nvram_81xx *nv = ha->nvram;
#घोषणा LR_DISTANCE_UNKNOWN	2
	अटल स्थिर अक्षर * स्थिर types[] = अणु "Short", "Long" पूर्ण;
	अटल स्थिर अक्षर * स्थिर lengths[] = अणु "(10km)", "(5km)", "" पूर्ण;
	u8 ll = 0;

	/* Seed with NVRAM settings. */
	used_nvram = 0;
	ha->flags.lr_detected = 0;
	अगर (IS_BPM_RANGE_CAPABLE(ha) &&
	    (nv->enhanced_features & NEF_LR_DIST_ENABLE)) अणु
		used_nvram = 1;
		ha->flags.lr_detected = 1;
		ha->lr_distance =
		    (nv->enhanced_features >> LR_DIST_NV_POS)
		     & LR_DIST_NV_MASK;
	पूर्ण

	अगर (!IS_BPM_ENABLED(vha))
		जाओ out;
	/* Determine SR/LR capabilities of SFP/Transceiver. */
	rc = qla2x00_पढ़ो_sfp_dev(vha, शून्य, 0);
	अगर (rc)
		जाओ out;

	used_nvram = 0;
	a = (काष्ठा sff_8247_a0 *)vha->hw->sfp_data;
	qla2xxx_prपूर्णांक_sfp_info(vha);

	ha->flags.lr_detected = 0;
	ll = a->fc_ll_cc7;
	अगर (ll & FC_LL_VL || ll & FC_LL_L) अणु
		/* Long range, track length. */
		ha->flags.lr_detected = 1;

		अगर (a->length_km > 5 || a->length_100m > 50)
			ha->lr_distance = LR_DISTANCE_10K;
		अन्यथा
			ha->lr_distance = LR_DISTANCE_5K;
	पूर्ण

out:
	ql_dbg(ql_dbg_async, vha, 0x507b,
	    "SFP detect: %s-Range SFP %s (nvr=%x ll=%x lr=%x lrd=%x).\n",
	    types[ha->flags.lr_detected],
	    ha->flags.lr_detected ? lengths[ha->lr_distance] :
	       lengths[LR_DISTANCE_UNKNOWN],
	    used_nvram, ll, ha->flags.lr_detected, ha->lr_distance);
	वापस ha->flags.lr_detected;
पूर्ण

व्योम qla_init_iocb_limit(scsi_qla_host_t *vha)
अणु
	u16 i, num_qps;
	u32 limit;
	काष्ठा qla_hw_data *ha = vha->hw;

	num_qps = ha->num_qpairs + 1;
	limit = (ha->orig_fw_iocb_count * QLA_IOCB_PCT_LIMIT) / 100;

	ha->base_qpair->fwres.iocbs_total = ha->orig_fw_iocb_count;
	ha->base_qpair->fwres.iocbs_limit = limit;
	ha->base_qpair->fwres.iocbs_qp_limit = limit / num_qps;
	ha->base_qpair->fwres.iocbs_used = 0;
	क्रम (i = 0; i < ha->max_qpairs; i++) अणु
		अगर (ha->queue_pair_map[i])  अणु
			ha->queue_pair_map[i]->fwres.iocbs_total =
				ha->orig_fw_iocb_count;
			ha->queue_pair_map[i]->fwres.iocbs_limit = limit;
			ha->queue_pair_map[i]->fwres.iocbs_qp_limit =
				limit / num_qps;
			ha->queue_pair_map[i]->fwres.iocbs_used = 0;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * qla2x00_setup_chip() - Load and start RISC firmware.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_setup_chip(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t srisc_address = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	अचिन्हित दीर्घ flags;
	uपूर्णांक16_t fw_major_version;
	पूर्णांक करोne_once = 0;

	अगर (IS_P3P_TYPE(ha)) अणु
		rval = ha->isp_ops->load_risc(vha, &srisc_address);
		अगर (rval == QLA_SUCCESS) अणु
			qla2x00_stop_firmware(vha);
			जाओ enable_82xx_npiv;
		पूर्ण अन्यथा
			जाओ failed;
	पूर्ण

	अगर (!IS_FWI2_CAPABLE(ha) && !IS_QLA2100(ha) && !IS_QLA2200(ha)) अणु
		/* Disable SRAM, Inकाष्ठाion RAM and GP RAM parity.  */
		spin_lock_irqsave(&ha->hardware_lock, flags);
		wrt_reg_word(&reg->hccr, (HCCR_ENABLE_PARITY + 0x0));
		rd_reg_word(&reg->hccr);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण

	qla81xx_mpi_sync(vha);

execute_fw_with_lr:
	/* Load firmware sequences */
	rval = ha->isp_ops->load_risc(vha, &srisc_address);
	अगर (rval == QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_init, vha, 0x00c9,
		    "Verifying Checksum of loaded RISC code.\n");

		rval = qla2x00_verअगरy_checksum(vha, srisc_address);
		अगर (rval == QLA_SUCCESS) अणु
			/* Start firmware execution. */
			ql_dbg(ql_dbg_init, vha, 0x00ca,
			    "Starting firmware.\n");

			अगर (ql2xexlogins)
				ha->flags.exlogins_enabled = 1;

			अगर (qla_is_exch_offld_enabled(vha))
				ha->flags.exchoffld_enabled = 1;

			rval = qla2x00_execute_fw(vha, srisc_address);
			/* Retrieve firmware inक्रमmation. */
			अगर (rval == QLA_SUCCESS) अणु
				/* Enable BPM support? */
				अगर (!करोne_once++ && qla24xx_detect_sfp(vha)) अणु
					ql_dbg(ql_dbg_init, vha, 0x00ca,
					    "Re-starting firmware -- BPM.\n");
					/* Best-efक्रमt - re-init. */
					ha->isp_ops->reset_chip(vha);
					ha->isp_ops->chip_diag(vha);
					जाओ execute_fw_with_lr;
				पूर्ण

				अगर (IS_ZIO_THRESHOLD_CAPABLE(ha))
					qla27xx_set_zio_threshold(vha,
					    ha->last_zio_threshold);

				rval = qla2x00_set_exlogins_buffer(vha);
				अगर (rval != QLA_SUCCESS)
					जाओ failed;

				rval = qla2x00_set_exchoffld_buffer(vha);
				अगर (rval != QLA_SUCCESS)
					जाओ failed;

enable_82xx_npiv:
				fw_major_version = ha->fw_major_version;
				अगर (IS_P3P_TYPE(ha))
					qla82xx_check_md_needed(vha);
				अन्यथा
					rval = qla2x00_get_fw_version(vha);
				अगर (rval != QLA_SUCCESS)
					जाओ failed;
				ha->flags.npiv_supported = 0;
				अगर (IS_QLA2XXX_MIDTYPE(ha) &&
					 (ha->fw_attributes & BIT_2)) अणु
					ha->flags.npiv_supported = 1;
					अगर ((!ha->max_npiv_vports) ||
					    ((ha->max_npiv_vports + 1) %
					    MIN_MULTI_ID_FABRIC))
						ha->max_npiv_vports =
						    MIN_MULTI_ID_FABRIC - 1;
				पूर्ण
				qla2x00_get_resource_cnts(vha);
				qla_init_iocb_limit(vha);

				/*
				 * Allocate the array of outstanding commands
				 * now that we know the firmware resources.
				 */
				rval = qla2x00_alloc_outstanding_cmds(ha,
				    vha->req);
				अगर (rval != QLA_SUCCESS)
					जाओ failed;

				अगर (!fw_major_version && !(IS_P3P_TYPE(ha)))
					qla2x00_alloc_offload_mem(vha);

				अगर (ql2xallocfwdump && !(IS_P3P_TYPE(ha)))
					qla2x00_alloc_fw_dump(vha);

			पूर्ण अन्यथा अणु
				जाओ failed;
			पूर्ण
		पूर्ण अन्यथा अणु
			ql_log(ql_log_fatal, vha, 0x00cd,
			    "ISP Firmware failed checksum.\n");
			जाओ failed;
		पूर्ण

		/* Enable PUREX PASSTHRU */
		अगर (ql2xrdpenable || ha->flags.scm_supported_f)
			qla25xx_set_els_cmds_supported(vha);
	पूर्ण अन्यथा
		जाओ failed;

	अगर (!IS_FWI2_CAPABLE(ha) && !IS_QLA2100(ha) && !IS_QLA2200(ha)) अणु
		/* Enable proper parity. */
		spin_lock_irqsave(&ha->hardware_lock, flags);
		अगर (IS_QLA2300(ha))
			/* SRAM parity */
			wrt_reg_word(&reg->hccr, HCCR_ENABLE_PARITY + 0x1);
		अन्यथा
			/* SRAM, Inकाष्ठाion RAM and GP RAM parity */
			wrt_reg_word(&reg->hccr, HCCR_ENABLE_PARITY + 0x7);
		rd_reg_word(&reg->hccr);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	पूर्ण

	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
		ha->flags.fac_supported = 1;
	अन्यथा अगर (rval == QLA_SUCCESS && IS_FAC_REQUIRED(ha)) अणु
		uपूर्णांक32_t size;

		rval = qla81xx_fac_get_sector_size(vha, &size);
		अगर (rval == QLA_SUCCESS) अणु
			ha->flags.fac_supported = 1;
			ha->fdt_block_size = size << 2;
		पूर्ण अन्यथा अणु
			ql_log(ql_log_warn, vha, 0x00ce,
			    "Unsupported FAC firmware (%d.%02d.%02d).\n",
			    ha->fw_major_version, ha->fw_minor_version,
			    ha->fw_subminor_version);

			अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
			    IS_QLA28XX(ha)) अणु
				ha->flags.fac_supported = 0;
				rval = QLA_SUCCESS;
			पूर्ण
		पूर्ण
	पूर्ण
failed:
	अगर (rval) अणु
		ql_log(ql_log_fatal, vha, 0x00cf,
		    "Setup chip ****FAILED****.\n");
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_init_response_q_entries() - Initializes response queue entries.
 * @rsp: response queue
 *
 * Beginning of request ring has initialization control block alपढ़ोy built
 * by nvram config routine.
 *
 * Returns 0 on success.
 */
व्योम
qla2x00_init_response_q_entries(काष्ठा rsp_que *rsp)
अणु
	uपूर्णांक16_t cnt;
	response_t *pkt;

	rsp->ring_ptr = rsp->ring;
	rsp->ring_index    = 0;
	rsp->status_srb = शून्य;
	pkt = rsp->ring_ptr;
	क्रम (cnt = 0; cnt < rsp->length; cnt++) अणु
		pkt->signature = RESPONSE_PROCESSED;
		pkt++;
	पूर्ण
पूर्ण

/**
 * qla2x00_update_fw_options() - Read and process firmware options.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
व्योम
qla2x00_update_fw_options(scsi_qla_host_t *vha)
अणु
	uपूर्णांक16_t swing, emphasis, tx_sens, rx_sens;
	काष्ठा qla_hw_data *ha = vha->hw;

	स_रखो(ha->fw_options, 0, माप(ha->fw_options));
	qla2x00_get_fw_options(vha, ha->fw_options);

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस;

	/* Serial Link options. */
	ql_dbg(ql_dbg_init + ql_dbg_buffer, vha, 0x0115,
	    "Serial link options.\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0109,
	    ha->fw_seriallink_options, माप(ha->fw_seriallink_options));

	ha->fw_options[1] &= ~FO1_SET_EMPHASIS_SWING;
	अगर (ha->fw_seriallink_options[3] & BIT_2) अणु
		ha->fw_options[1] |= FO1_SET_EMPHASIS_SWING;

		/*  1G settings */
		swing = ha->fw_seriallink_options[2] & (BIT_2 | BIT_1 | BIT_0);
		emphasis = (ha->fw_seriallink_options[2] &
		    (BIT_4 | BIT_3)) >> 3;
		tx_sens = ha->fw_seriallink_options[0] &
		    (BIT_3 | BIT_2 | BIT_1 | BIT_0);
		rx_sens = (ha->fw_seriallink_options[0] &
		    (BIT_7 | BIT_6 | BIT_5 | BIT_4)) >> 4;
		ha->fw_options[10] = (emphasis << 14) | (swing << 8);
		अगर (IS_QLA2300(ha) || IS_QLA2312(ha) || IS_QLA6312(ha)) अणु
			अगर (rx_sens == 0x0)
				rx_sens = 0x3;
			ha->fw_options[10] |= (tx_sens << 4) | rx_sens;
		पूर्ण अन्यथा अगर (IS_QLA2322(ha) || IS_QLA6322(ha))
			ha->fw_options[10] |= BIT_5 |
			    ((rx_sens & (BIT_1 | BIT_0)) << 2) |
			    (tx_sens & (BIT_1 | BIT_0));

		/*  2G settings */
		swing = (ha->fw_seriallink_options[2] &
		    (BIT_7 | BIT_6 | BIT_5)) >> 5;
		emphasis = ha->fw_seriallink_options[3] & (BIT_1 | BIT_0);
		tx_sens = ha->fw_seriallink_options[1] &
		    (BIT_3 | BIT_2 | BIT_1 | BIT_0);
		rx_sens = (ha->fw_seriallink_options[1] &
		    (BIT_7 | BIT_6 | BIT_5 | BIT_4)) >> 4;
		ha->fw_options[11] = (emphasis << 14) | (swing << 8);
		अगर (IS_QLA2300(ha) || IS_QLA2312(ha) || IS_QLA6312(ha)) अणु
			अगर (rx_sens == 0x0)
				rx_sens = 0x3;
			ha->fw_options[11] |= (tx_sens << 4) | rx_sens;
		पूर्ण अन्यथा अगर (IS_QLA2322(ha) || IS_QLA6322(ha))
			ha->fw_options[11] |= BIT_5 |
			    ((rx_sens & (BIT_1 | BIT_0)) << 2) |
			    (tx_sens & (BIT_1 | BIT_0));
	पूर्ण

	/* FCP2 options. */
	/*  Return command IOCBs without रुकोing क्रम an ABTS to complete. */
	ha->fw_options[3] |= BIT_13;

	/* LED scheme. */
	अगर (ha->flags.enable_led_scheme)
		ha->fw_options[2] |= BIT_12;

	/* Detect ISP6312. */
	अगर (IS_QLA6312(ha))
		ha->fw_options[2] |= BIT_13;

	/* Set Retry FLOGI in हाल of P2P connection */
	अगर (ha->operating_mode == P2P) अणु
		ha->fw_options[2] |= BIT_3;
		ql_dbg(ql_dbg_disc, vha, 0x2100,
		    "(%s): Setting FLOGI retry BIT in fw_options[2]: 0x%x\n",
			__func__, ha->fw_options[2]);
	पूर्ण

	/* Update firmware options. */
	qla2x00_set_fw_options(vha, ha->fw_options);
पूर्ण

व्योम
qla24xx_update_fw_options(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_P3P_TYPE(ha))
		वापस;

	/*  Hold status IOCBs until ABTS response received. */
	अगर (ql2xfwholdabts)
		ha->fw_options[3] |= BIT_12;

	/* Set Retry FLOGI in हाल of P2P connection */
	अगर (ha->operating_mode == P2P) अणु
		ha->fw_options[2] |= BIT_3;
		ql_dbg(ql_dbg_disc, vha, 0x2101,
		    "(%s): Setting FLOGI retry BIT in fw_options[2]: 0x%x\n",
			__func__, ha->fw_options[2]);
	पूर्ण

	/* Move PUREX, ABTS RX & RIDA to ATIOQ */
	अगर (ql2xmvasynctoatio &&
	    (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))) अणु
		अगर (qla_tgt_mode_enabled(vha) ||
		    qla_dual_mode_enabled(vha))
			ha->fw_options[2] |= BIT_11;
		अन्यथा
			ha->fw_options[2] &= ~BIT_11;
	पूर्ण

	अगर (IS_QLA25XX(ha) || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		/*
		 * Tell FW to track each exchange to prevent
		 * driver from using stale exchange.
		 */
		अगर (qla_tgt_mode_enabled(vha) ||
		    qla_dual_mode_enabled(vha))
			ha->fw_options[2] |= BIT_4;
		अन्यथा
			ha->fw_options[2] &= ~BIT_4;

		/* Reserve 1/2 of emergency exchanges क्रम ELS.*/
		अगर (qla2xuseresexchक्रमels)
			ha->fw_options[2] |= BIT_8;
		अन्यथा
			ha->fw_options[2] &= ~BIT_8;
	पूर्ण

	अगर (ql2xrdpenable || ha->flags.scm_supported_f)
		ha->fw_options[1] |= ADD_FO1_ENABLE_PUREX_IOCB;

	/* Enable Async 8130/8131 events -- transceiver insertion/removal */
	अगर (IS_BPM_RANGE_CAPABLE(ha))
		ha->fw_options[3] |= BIT_10;

	ql_dbg(ql_dbg_init, vha, 0x00e8,
	    "%s, add FW options 1-3 = 0x%04x 0x%04x 0x%04x mode %x\n",
	    __func__, ha->fw_options[1], ha->fw_options[2],
	    ha->fw_options[3], vha->host->active_mode);

	अगर (ha->fw_options[1] || ha->fw_options[2] || ha->fw_options[3])
		qla2x00_set_fw_options(vha, ha->fw_options);

	/* Update Serial Link options. */
	अगर ((le16_to_cpu(ha->fw_seriallink_options24[0]) & BIT_0) == 0)
		वापस;

	rval = qla2x00_set_serdes_params(vha,
	    le16_to_cpu(ha->fw_seriallink_options24[1]),
	    le16_to_cpu(ha->fw_seriallink_options24[2]),
	    le16_to_cpu(ha->fw_seriallink_options24[3]));
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x0104,
		    "Unable to update Serial Link options (%x).\n", rval);
	पूर्ण
पूर्ण

व्योम
qla2x00_config_rings(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];

	/* Setup ring parameters in initialization control block. */
	ha->init_cb->request_q_outpoपूर्णांकer = cpu_to_le16(0);
	ha->init_cb->response_q_inpoपूर्णांकer = cpu_to_le16(0);
	ha->init_cb->request_q_length = cpu_to_le16(req->length);
	ha->init_cb->response_q_length = cpu_to_le16(rsp->length);
	put_unaligned_le64(req->dma, &ha->init_cb->request_q_address);
	put_unaligned_le64(rsp->dma, &ha->init_cb->response_q_address);

	wrt_reg_word(ISP_REQ_Q_IN(ha, reg), 0);
	wrt_reg_word(ISP_REQ_Q_OUT(ha, reg), 0);
	wrt_reg_word(ISP_RSP_Q_IN(ha, reg), 0);
	wrt_reg_word(ISP_RSP_Q_OUT(ha, reg), 0);
	rd_reg_word(ISP_RSP_Q_OUT(ha, reg));		/* PCI Posting. */
पूर्ण

व्योम
qla24xx_config_rings(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	device_reg_t *reg = ISP_QUE_REG(ha, 0);
	काष्ठा device_reg_2xxx __iomem *ioreg = &ha->iobase->isp;
	काष्ठा qla_msix_entry *msix;
	काष्ठा init_cb_24xx *icb;
	uपूर्णांक16_t rid = 0;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];

	/* Setup ring parameters in initialization control block. */
	icb = (काष्ठा init_cb_24xx *)ha->init_cb;
	icb->request_q_outpoपूर्णांकer = cpu_to_le16(0);
	icb->response_q_inpoपूर्णांकer = cpu_to_le16(0);
	icb->request_q_length = cpu_to_le16(req->length);
	icb->response_q_length = cpu_to_le16(rsp->length);
	put_unaligned_le64(req->dma, &icb->request_q_address);
	put_unaligned_le64(rsp->dma, &icb->response_q_address);

	/* Setup ATIO queue dma poपूर्णांकers क्रम target mode */
	icb->atio_q_inpoपूर्णांकer = cpu_to_le16(0);
	icb->atio_q_length = cpu_to_le16(ha->tgt.atio_q_length);
	put_unaligned_le64(ha->tgt.atio_dma, &icb->atio_q_address);

	अगर (IS_SHADOW_REG_CAPABLE(ha))
		icb->firmware_options_2 |= cpu_to_le32(BIT_30|BIT_29);

	अगर (ha->mqenable || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		icb->qos = cpu_to_le16(QLA_DEFAULT_QUE_QOS);
		icb->rid = cpu_to_le16(rid);
		अगर (ha->flags.msix_enabled) अणु
			msix = &ha->msix_entries[1];
			ql_dbg(ql_dbg_init, vha, 0x0019,
			    "Registering vector 0x%x for base que.\n",
			    msix->entry);
			icb->msix = cpu_to_le16(msix->entry);
		पूर्ण
		/* Use alternate PCI bus number */
		अगर (MSB(rid))
			icb->firmware_options_2 |= cpu_to_le32(BIT_19);
		/* Use alternate PCI devfn */
		अगर (LSB(rid))
			icb->firmware_options_2 |= cpu_to_le32(BIT_18);

		/* Use Disable MSIX Handshake mode क्रम capable adapters */
		अगर ((ha->fw_attributes & BIT_6) && (IS_MSIX_NACK_CAPABLE(ha)) &&
		    (ha->flags.msix_enabled)) अणु
			icb->firmware_options_2 &= cpu_to_le32(~BIT_22);
			ha->flags.disable_msix_handshake = 1;
			ql_dbg(ql_dbg_init, vha, 0x00fe,
			    "MSIX Handshake Disable Mode turned on.\n");
		पूर्ण अन्यथा अणु
			icb->firmware_options_2 |= cpu_to_le32(BIT_22);
		पूर्ण
		icb->firmware_options_2 |= cpu_to_le32(BIT_23);

		wrt_reg_dword(&reg->isp25mq.req_q_in, 0);
		wrt_reg_dword(&reg->isp25mq.req_q_out, 0);
		wrt_reg_dword(&reg->isp25mq.rsp_q_in, 0);
		wrt_reg_dword(&reg->isp25mq.rsp_q_out, 0);
	पूर्ण अन्यथा अणु
		wrt_reg_dword(&reg->isp24.req_q_in, 0);
		wrt_reg_dword(&reg->isp24.req_q_out, 0);
		wrt_reg_dword(&reg->isp24.rsp_q_in, 0);
		wrt_reg_dword(&reg->isp24.rsp_q_out, 0);
	पूर्ण

	qlt_24xx_config_rings(vha);

	/* If the user has configured the speed, set it here */
	अगर (ha->set_data_rate) अणु
		ql_dbg(ql_dbg_init, vha, 0x00fd,
		    "Speed set by user : %s Gbps \n",
		    qla2x00_get_link_speed_str(ha, ha->set_data_rate));
		icb->firmware_options_3 = cpu_to_le32(ha->set_data_rate << 13);
	पूर्ण

	/* PCI posting */
	rd_reg_word(&ioreg->hccr);
पूर्ण

/**
 * qla2x00_init_rings() - Initializes firmware.
 * @vha: HA context
 *
 * Beginning of request ring has initialization control block alपढ़ोy built
 * by nvram config routine.
 *
 * Returns 0 on success.
 */
पूर्णांक
qla2x00_init_rings(scsi_qla_host_t *vha)
अणु
	पूर्णांक	rval;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक cnt, que;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;
	काष्ठा rsp_que *rsp;
	काष्ठा mid_init_cb_24xx *mid_init_cb =
	    (काष्ठा mid_init_cb_24xx *) ha->init_cb;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Clear outstanding commands array. */
	क्रम (que = 0; que < ha->max_req_queues; que++) अणु
		req = ha->req_q_map[que];
		अगर (!req || !test_bit(que, ha->req_qid_map))
			जारी;
		req->out_ptr = (uपूर्णांक16_t *)(req->ring + req->length);
		*req->out_ptr = 0;
		क्रम (cnt = 1; cnt < req->num_outstanding_cmds; cnt++)
			req->outstanding_cmds[cnt] = शून्य;

		req->current_outstanding_cmd = 1;

		/* Initialize firmware. */
		req->ring_ptr  = req->ring;
		req->ring_index    = 0;
		req->cnt      = req->length;
	पूर्ण

	क्रम (que = 0; que < ha->max_rsp_queues; que++) अणु
		rsp = ha->rsp_q_map[que];
		अगर (!rsp || !test_bit(que, ha->rsp_qid_map))
			जारी;
		rsp->in_ptr = (uपूर्णांक16_t *)(rsp->ring + rsp->length);
		*rsp->in_ptr = 0;
		/* Initialize response queue entries */
		अगर (IS_QLAFX00(ha))
			qlafx00_init_response_q_entries(rsp);
		अन्यथा
			qla2x00_init_response_q_entries(rsp);
	पूर्ण

	ha->tgt.atio_ring_ptr = ha->tgt.atio_ring;
	ha->tgt.atio_ring_index = 0;
	/* Initialize ATIO queue entries */
	qlt_init_atio_q_entries(vha);

	ha->isp_ops->config_rings(vha);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	ql_dbg(ql_dbg_init, vha, 0x00d1, "Issue init firmware.\n");

	अगर (IS_QLAFX00(ha)) अणु
		rval = qlafx00_init_firmware(vha, ha->init_cb_size);
		जाओ next_check;
	पूर्ण

	/* Update any ISP specअगरic firmware options beक्रमe initialization. */
	ha->isp_ops->update_fw_options(vha);

	अगर (ha->flags.npiv_supported) अणु
		अगर (ha->operating_mode == LOOP && !IS_CNA_CAPABLE(ha))
			ha->max_npiv_vports = MIN_MULTI_ID_FABRIC - 1;
		mid_init_cb->count = cpu_to_le16(ha->max_npiv_vports);
	पूर्ण

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		mid_init_cb->options = cpu_to_le16(BIT_1);
		mid_init_cb->init_cb.execution_throttle =
		    cpu_to_le16(ha->cur_fw_xcb_count);
		ha->flags.dport_enabled =
			(le32_to_cpu(mid_init_cb->init_cb.firmware_options_1) &
			 BIT_7) != 0;
		ql_dbg(ql_dbg_init, vha, 0x0191, "DPORT Support: %s.\n",
		    (ha->flags.dport_enabled) ? "enabled" : "disabled");
		/* FA-WWPN Status */
		ha->flags.fawwpn_enabled =
			(le32_to_cpu(mid_init_cb->init_cb.firmware_options_1) &
			 BIT_6) != 0;
		ql_dbg(ql_dbg_init, vha, 0x00bc, "FA-WWPN Support: %s.\n",
		    (ha->flags.fawwpn_enabled) ? "enabled" : "disabled");
	पूर्ण

	rval = qla2x00_init_firmware(vha, ha->init_cb_size);
next_check:
	अगर (rval) अणु
		ql_log(ql_log_fatal, vha, 0x00d2,
		    "Init Firmware **** FAILED ****.\n");
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_init, vha, 0x00d3,
		    "Init Firmware -- success.\n");
		QLA_FW_STARTED(ha);
		vha->u_ql2xexchoffld = vha->u_ql2xiniexchg = 0;
	पूर्ण

	वापस (rval);
पूर्ण

/**
 * qla2x00_fw_पढ़ोy() - Waits क्रम firmware पढ़ोy.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
अटल पूर्णांक
qla2x00_fw_पढ़ोy(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	अचिन्हित दीर्घ	wसमय, mसमय, cs84xx_समय;
	uपूर्णांक16_t	min_रुको;	/* Minimum रुको समय अगर loop is करोwn */
	uपूर्णांक16_t	रुको_समय;	/* Wait समय अगर loop is coming पढ़ोy */
	uपूर्णांक16_t	state[6];
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (IS_QLAFX00(vha->hw))
		वापस qlafx00_fw_पढ़ोy(vha);

	rval = QLA_SUCCESS;

	/* Time to रुको क्रम loop करोwn */
	अगर (IS_P3P_TYPE(ha))
		min_रुको = 30;
	अन्यथा
		min_रुको = 20;

	/*
	 * Firmware should take at most one RATOV to login, plus 5 seconds क्रम
	 * our own processing.
	 */
	अगर ((रुको_समय = (ha->retry_count*ha->login_समयout) + 5) < min_रुको) अणु
		रुको_समय = min_रुको;
	पूर्ण

	/* Min रुको समय अगर loop करोwn */
	mसमय = jअगरfies + (min_रुको * HZ);

	/* रुको समय beक्रमe firmware पढ़ोy */
	wसमय = jअगरfies + (रुको_समय * HZ);

	/* Wait क्रम ISP to finish LIP */
	अगर (!vha->flags.init_करोne)
		ql_log(ql_log_info, vha, 0x801e,
		    "Waiting for LIP to complete.\n");

	करो अणु
		स_रखो(state, -1, माप(state));
		rval = qla2x00_get_firmware_state(vha, state);
		अगर (rval == QLA_SUCCESS) अणु
			अगर (state[0] < FSTATE_LOSS_OF_SYNC) अणु
				vha->device_flags &= ~DFLG_NO_CABLE;
			पूर्ण
			अगर (IS_QLA84XX(ha) && state[0] != FSTATE_READY) अणु
				ql_dbg(ql_dbg_taskm, vha, 0x801f,
				    "fw_state=%x 84xx=%x.\n", state[0],
				    state[2]);
				अगर ((state[2] & FSTATE_LOGGED_IN) &&
				     (state[2] & FSTATE_WAITING_FOR_VERIFY)) अणु
					ql_dbg(ql_dbg_taskm, vha, 0x8028,
					    "Sending verify iocb.\n");

					cs84xx_समय = jअगरfies;
					rval = qla84xx_init_chip(vha);
					अगर (rval != QLA_SUCCESS) अणु
						ql_log(ql_log_warn,
						    vha, 0x8007,
						    "Init chip failed.\n");
						अवरोध;
					पूर्ण

					/* Add समय taken to initialize. */
					cs84xx_समय = jअगरfies - cs84xx_समय;
					wसमय += cs84xx_समय;
					mसमय += cs84xx_समय;
					ql_dbg(ql_dbg_taskm, vha, 0x8008,
					    "Increasing wait time by %ld. "
					    "New time %ld.\n", cs84xx_समय,
					    wसमय);
				पूर्ण
			पूर्ण अन्यथा अगर (state[0] == FSTATE_READY) अणु
				ql_dbg(ql_dbg_taskm, vha, 0x8037,
				    "F/W Ready - OK.\n");

				qla2x00_get_retry_cnt(vha, &ha->retry_count,
				    &ha->login_समयout, &ha->r_a_tov);

				rval = QLA_SUCCESS;
				अवरोध;
			पूर्ण

			rval = QLA_FUNCTION_FAILED;

			अगर (atomic_पढ़ो(&vha->loop_करोwn_समयr) &&
			    state[0] != FSTATE_READY) अणु
				/* Loop करोwn. Timeout on min_रुको क्रम states
				 * other than Wait क्रम Login.
				 */
				अगर (समय_after_eq(jअगरfies, mसमय)) अणु
					ql_log(ql_log_info, vha, 0x8038,
					    "Cable is unplugged...\n");

					vha->device_flags |= DFLG_NO_CABLE;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Mailbox cmd failed. Timeout on min_रुको. */
			अगर (समय_after_eq(jअगरfies, mसमय) ||
				ha->flags.isp82xx_fw_hung)
				अवरोध;
		पूर्ण

		अगर (समय_after_eq(jअगरfies, wसमय))
			अवरोध;

		/* Delay क्रम a जबतक */
		msleep(500);
	पूर्ण जबतक (1);

	ql_dbg(ql_dbg_taskm, vha, 0x803a,
	    "fw_state=%x (%x, %x, %x, %x %x) curr time=%lx.\n", state[0],
	    state[1], state[2], state[3], state[4], state[5], jअगरfies);

	अगर (rval && !(vha->device_flags & DFLG_NO_CABLE)) अणु
		ql_log(ql_log_warn, vha, 0x803b,
		    "Firmware ready **** FAILED ****.\n");
	पूर्ण

	वापस (rval);
पूर्ण

/*
*  qla2x00_configure_hba
*      Setup adapter context.
*
* Input:
*      ha = adapter state poपूर्णांकer.
*
* Returns:
*      0 = success
*
* Context:
*      Kernel context.
*/
अटल पूर्णांक
qla2x00_configure_hba(scsi_qla_host_t *vha)
अणु
	पूर्णांक       rval;
	uपूर्णांक16_t      loop_id;
	uपूर्णांक16_t      topo;
	uपूर्णांक16_t      sw_cap;
	uपूर्णांक8_t       al_pa;
	uपूर्णांक8_t       area;
	uपूर्णांक8_t       करोमुख्य;
	अक्षर		connect_type[22];
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	port_id_t id;
	अचिन्हित दीर्घ flags;

	/* Get host addresses. */
	rval = qla2x00_get_adapter_id(vha,
	    &loop_id, &al_pa, &area, &करोमुख्य, &topo, &sw_cap);
	अगर (rval != QLA_SUCCESS) अणु
		अगर (LOOP_TRANSITION(vha) || atomic_पढ़ो(&ha->loop_करोwn_समयr) ||
		    IS_CNA_CAPABLE(ha) ||
		    (rval == QLA_COMMAND_ERROR && loop_id == 0x7)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2008,
			    "Loop is in a transition state.\n");
		पूर्ण अन्यथा अणु
			ql_log(ql_log_warn, vha, 0x2009,
			    "Unable to get host loop ID.\n");
			अगर (IS_FWI2_CAPABLE(ha) && (vha == base_vha) &&
			    (rval == QLA_COMMAND_ERROR && loop_id == 0x1b)) अणु
				ql_log(ql_log_warn, vha, 0x1151,
				    "Doing link init.\n");
				अगर (qla24xx_link_initialize(vha) == QLA_SUCCESS)
					वापस rval;
			पूर्ण
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		पूर्ण
		वापस (rval);
	पूर्ण

	अगर (topo == 4) अणु
		ql_log(ql_log_info, vha, 0x200a,
		    "Cannot get topology - retrying.\n");
		वापस (QLA_FUNCTION_FAILED);
	पूर्ण

	vha->loop_id = loop_id;

	/* initialize */
	ha->min_बाह्यal_loopid = SNS_FIRST_LOOP_ID;
	ha->operating_mode = LOOP;
	ha->चयन_cap = 0;

	चयन (topo) अणु
	हाल 0:
		ql_dbg(ql_dbg_disc, vha, 0x200b, "HBA in NL topology.\n");
		ha->current_topology = ISP_CFG_NL;
		म_नकल(connect_type, "(Loop)");
		अवरोध;

	हाल 1:
		ql_dbg(ql_dbg_disc, vha, 0x200c, "HBA in FL topology.\n");
		ha->चयन_cap = sw_cap;
		ha->current_topology = ISP_CFG_FL;
		म_नकल(connect_type, "(FL_Port)");
		अवरोध;

	हाल 2:
		ql_dbg(ql_dbg_disc, vha, 0x200d, "HBA in N P2P topology.\n");
		ha->operating_mode = P2P;
		ha->current_topology = ISP_CFG_N;
		म_नकल(connect_type, "(N_Port-to-N_Port)");
		अवरोध;

	हाल 3:
		ql_dbg(ql_dbg_disc, vha, 0x200e, "HBA in F P2P topology.\n");
		ha->चयन_cap = sw_cap;
		ha->operating_mode = P2P;
		ha->current_topology = ISP_CFG_F;
		म_नकल(connect_type, "(F_Port)");
		अवरोध;

	शेष:
		ql_dbg(ql_dbg_disc, vha, 0x200f,
		    "HBA in unknown topology %x, using NL.\n", topo);
		ha->current_topology = ISP_CFG_NL;
		म_नकल(connect_type, "(Loop)");
		अवरोध;
	पूर्ण

	/* Save Host port and loop ID. */
	/* byte order - Big Endian */
	id.b.करोमुख्य = करोमुख्य;
	id.b.area = area;
	id.b.al_pa = al_pa;
	id.b.rsvd_1 = 0;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	अगर (!(topo == 2 && ha->flags.n2n_bigger))
		qlt_update_host_map(vha, id);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (!vha->flags.init_करोne)
		ql_log(ql_log_info, vha, 0x2010,
		    "Topology - %s, Host Loop address 0x%x.\n",
		    connect_type, vha->loop_id);

	वापस(rval);
पूर्ण

अंतरभूत व्योम
qla2x00_set_model_info(scsi_qla_host_t *vha, uपूर्णांक8_t *model, माप_प्रकार len,
		       स्थिर अक्षर *def)
अणु
	अक्षर *st, *en;
	uपूर्णांक16_t index;
	uपूर्णांक64_t zero[2] = अणु 0 पूर्ण;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक use_tbl = !IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha) &&
	    !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha);

	अगर (len > माप(zero))
		len = माप(zero);
	अगर (स_भेद(model, &zero, len) != 0) अणु
		स_नकल(ha->model_number, model, len);
		st = en = ha->model_number;
		en += len - 1;
		जबतक (en > st) अणु
			अगर (*en != 0x20 && *en != 0x00)
				अवरोध;
			*en-- = '\0';
		पूर्ण

		index = (ha->pdev->subप्रणाली_device & 0xff);
		अगर (use_tbl &&
		    ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_QLOGIC &&
		    index < QLA_MODEL_NAMES)
			strlcpy(ha->model_desc,
			    qla2x00_model_name[index * 2 + 1],
			    माप(ha->model_desc));
	पूर्ण अन्यथा अणु
		index = (ha->pdev->subप्रणाली_device & 0xff);
		अगर (use_tbl &&
		    ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_QLOGIC &&
		    index < QLA_MODEL_NAMES) अणु
			strlcpy(ha->model_number,
				qla2x00_model_name[index * 2],
				माप(ha->model_number));
			strlcpy(ha->model_desc,
			    qla2x00_model_name[index * 2 + 1],
			    माप(ha->model_desc));
		पूर्ण अन्यथा अणु
			strlcpy(ha->model_number, def,
				माप(ha->model_number));
		पूर्ण
	पूर्ण
	अगर (IS_FWI2_CAPABLE(ha))
		qla2xxx_get_vpd_field(vha, "\x82", ha->model_desc,
		    माप(ha->model_desc));
पूर्ण

/* On sparc प्रणालीs, obtain port and node WWN from firmware
 * properties.
 */
अटल व्योम qla2xxx_nvram_wwn_from_ofw(scsi_qla_host_t *vha, nvram_t *nv)
अणु
#अगर_घोषित CONFIG_SPARC
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा pci_dev *pdev = ha->pdev;
	काष्ठा device_node *dp = pci_device_to_OF_node(pdev);
	स्थिर u8 *val;
	पूर्णांक len;

	val = of_get_property(dp, "port-wwn", &len);
	अगर (val && len >= WWN_SIZE)
		स_नकल(nv->port_name, val, WWN_SIZE);

	val = of_get_property(dp, "node-wwn", &len);
	अगर (val && len >= WWN_SIZE)
		स_नकल(nv->node_name, val, WWN_SIZE);
#पूर्ण_अगर
पूर्ण

/*
* NVRAM configuration क्रम ISP 2xxx
*
* Input:
*      ha                = adapter block poपूर्णांकer.
*
* Output:
*      initialization control block in response_ring
*      host adapters parameters in host adapter block
*
* Returns:
*      0 = success.
*/
पूर्णांक
qla2x00_nvram_config(scsi_qla_host_t *vha)
अणु
	पूर्णांक             rval;
	uपूर्णांक8_t         chksum = 0;
	uपूर्णांक16_t        cnt;
	uपूर्णांक8_t         *dptr1, *dptr2;
	काष्ठा qla_hw_data *ha = vha->hw;
	init_cb_t       *icb = ha->init_cb;
	nvram_t         *nv = ha->nvram;
	uपूर्णांक8_t         *ptr = ha->nvram;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	rval = QLA_SUCCESS;

	/* Determine NVRAM starting address. */
	ha->nvram_size = माप(*nv);
	ha->nvram_base = 0;
	अगर (!IS_QLA2100(ha) && !IS_QLA2200(ha) && !IS_QLA2300(ha))
		अगर ((rd_reg_word(&reg->ctrl_status) >> 14) == 1)
			ha->nvram_base = 0x80;

	/* Get NVRAM data and calculate checksum. */
	ha->isp_ops->पढ़ो_nvram(vha, ptr, ha->nvram_base, ha->nvram_size);
	क्रम (cnt = 0, chksum = 0; cnt < ha->nvram_size; cnt++)
		chksum += *ptr++;

	ql_dbg(ql_dbg_init + ql_dbg_buffer, vha, 0x010f,
	    "Contents of NVRAM.\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0110,
	    nv, ha->nvram_size);

	/* Bad NVRAM data, set शेषs parameters. */
	अगर (chksum || स_भेद("ISP ", nv->id, माप(nv->id)) ||
	    nv->nvram_version < 1) अणु
		/* Reset NVRAM data. */
		ql_log(ql_log_warn, vha, 0x0064,
		    "Inconsistent NVRAM detected: checksum=%#x id=%.4s version=%#x.\n",
		    chksum, nv->id, nv->nvram_version);
		ql_log(ql_log_warn, vha, 0x0065,
		    "Falling back to "
		    "functioning (yet invalid -- WWPN) defaults.\n");

		/*
		 * Set शेष initialization control block.
		 */
		स_रखो(nv, 0, ha->nvram_size);
		nv->parameter_block_version = ICB_VERSION;

		अगर (IS_QLA23XX(ha)) अणु
			nv->firmware_options[0] = BIT_2 | BIT_1;
			nv->firmware_options[1] = BIT_7 | BIT_5;
			nv->add_firmware_options[0] = BIT_5;
			nv->add_firmware_options[1] = BIT_5 | BIT_4;
			nv->frame_payload_size = cpu_to_le16(2048);
			nv->special_options[1] = BIT_7;
		पूर्ण अन्यथा अगर (IS_QLA2200(ha)) अणु
			nv->firmware_options[0] = BIT_2 | BIT_1;
			nv->firmware_options[1] = BIT_7 | BIT_5;
			nv->add_firmware_options[0] = BIT_5;
			nv->add_firmware_options[1] = BIT_5 | BIT_4;
			nv->frame_payload_size = cpu_to_le16(1024);
		पूर्ण अन्यथा अगर (IS_QLA2100(ha)) अणु
			nv->firmware_options[0] = BIT_3 | BIT_1;
			nv->firmware_options[1] = BIT_5;
			nv->frame_payload_size = cpu_to_le16(1024);
		पूर्ण

		nv->max_iocb_allocation = cpu_to_le16(256);
		nv->execution_throttle = cpu_to_le16(16);
		nv->retry_count = 8;
		nv->retry_delay = 1;

		nv->port_name[0] = 33;
		nv->port_name[3] = 224;
		nv->port_name[4] = 139;

		qla2xxx_nvram_wwn_from_ofw(vha, nv);

		nv->login_समयout = 4;

		/*
		 * Set शेष host adapter parameters
		 */
		nv->host_p[1] = BIT_2;
		nv->reset_delay = 5;
		nv->port_करोwn_retry_count = 8;
		nv->max_luns_per_target = cpu_to_le16(8);
		nv->link_करोwn_समयout = 60;

		rval = 1;
	पूर्ण

	/* Reset Initialization control block */
	स_रखो(icb, 0, ha->init_cb_size);

	/*
	 * Setup driver NVRAM options.
	 */
	nv->firmware_options[0] |= (BIT_6 | BIT_1);
	nv->firmware_options[0] &= ~(BIT_5 | BIT_4);
	nv->firmware_options[1] |= (BIT_5 | BIT_0);
	nv->firmware_options[1] &= ~BIT_4;

	अगर (IS_QLA23XX(ha)) अणु
		nv->firmware_options[0] |= BIT_2;
		nv->firmware_options[0] &= ~BIT_3;
		nv->special_options[0] &= ~BIT_6;
		nv->add_firmware_options[1] |= BIT_5 | BIT_4;

		अगर (IS_QLA2300(ha)) अणु
			अगर (ha->fb_rev == FPM_2310) अणु
				म_नकल(ha->model_number, "QLA2310");
			पूर्ण अन्यथा अणु
				म_नकल(ha->model_number, "QLA2300");
			पूर्ण
		पूर्ण अन्यथा अणु
			qla2x00_set_model_info(vha, nv->model_number,
			    माप(nv->model_number), "QLA23xx");
		पूर्ण
	पूर्ण अन्यथा अगर (IS_QLA2200(ha)) अणु
		nv->firmware_options[0] |= BIT_2;
		/*
		 * 'Point-to-point preferred, else loop' is not a safe
		 * connection mode setting.
		 */
		अगर ((nv->add_firmware_options[0] & (BIT_6 | BIT_5 | BIT_4)) ==
		    (BIT_5 | BIT_4)) अणु
			/* Force 'loop preferred, else point-to-point'. */
			nv->add_firmware_options[0] &= ~(BIT_6 | BIT_5 | BIT_4);
			nv->add_firmware_options[0] |= BIT_5;
		पूर्ण
		म_नकल(ha->model_number, "QLA22xx");
	पूर्ण अन्यथा /*अगर (IS_QLA2100(ha))*/ अणु
		म_नकल(ha->model_number, "QLA2100");
	पूर्ण

	/*
	 * Copy over NVRAM RISC parameter block to initialization control block.
	 */
	dptr1 = (uपूर्णांक8_t *)icb;
	dptr2 = (uपूर्णांक8_t *)&nv->parameter_block_version;
	cnt = (uपूर्णांक8_t *)&icb->request_q_outpoपूर्णांकer - (uपूर्णांक8_t *)&icb->version;
	जबतक (cnt--)
		*dptr1++ = *dptr2++;

	/* Copy 2nd half. */
	dptr1 = (uपूर्णांक8_t *)icb->add_firmware_options;
	cnt = (uपूर्णांक8_t *)icb->reserved_3 - (uपूर्णांक8_t *)icb->add_firmware_options;
	जबतक (cnt--)
		*dptr1++ = *dptr2++;
	ha->frame_payload_size = le16_to_cpu(icb->frame_payload_size);
	/* Use alternate WWN? */
	अगर (nv->host_p[1] & BIT_7) अणु
		स_नकल(icb->node_name, nv->alternate_node_name, WWN_SIZE);
		स_नकल(icb->port_name, nv->alternate_port_name, WWN_SIZE);
	पूर्ण

	/* Prepare nodename */
	अगर ((icb->firmware_options[1] & BIT_6) == 0) अणु
		/*
		 * Firmware will apply the following mask अगर the nodename was
		 * not provided.
		 */
		स_नकल(icb->node_name, icb->port_name, WWN_SIZE);
		icb->node_name[0] &= 0xF0;
	पूर्ण

	/*
	 * Set host adapter parameters.
	 */

	/*
	 * BIT_7 in the host-parameters section allows क्रम modअगरication to
	 * पूर्णांकernal driver logging.
	 */
	अगर (nv->host_p[0] & BIT_7)
		ql2xextended_error_logging = QL_DBG_DEFAULT1_MASK;
	ha->flags.disable_risc_code_load = ((nv->host_p[0] & BIT_4) ? 1 : 0);
	/* Always load RISC code on non ISP2[12]00 chips. */
	अगर (!IS_QLA2100(ha) && !IS_QLA2200(ha))
		ha->flags.disable_risc_code_load = 0;
	ha->flags.enable_lip_reset = ((nv->host_p[1] & BIT_1) ? 1 : 0);
	ha->flags.enable_lip_full_login = ((nv->host_p[1] & BIT_2) ? 1 : 0);
	ha->flags.enable_target_reset = ((nv->host_p[1] & BIT_3) ? 1 : 0);
	ha->flags.enable_led_scheme = (nv->special_options[1] & BIT_4) ? 1 : 0;
	ha->flags.disable_serdes = 0;

	ha->operating_mode =
	    (icb->add_firmware_options[0] & (BIT_6 | BIT_5 | BIT_4)) >> 4;

	स_नकल(ha->fw_seriallink_options, nv->seriallink_options,
	    माप(ha->fw_seriallink_options));

	/* save HBA serial number */
	ha->serial0 = icb->port_name[5];
	ha->serial1 = icb->port_name[6];
	ha->serial2 = icb->port_name[7];
	स_नकल(vha->node_name, icb->node_name, WWN_SIZE);
	स_नकल(vha->port_name, icb->port_name, WWN_SIZE);

	icb->execution_throttle = cpu_to_le16(0xFFFF);

	ha->retry_count = nv->retry_count;

	/* Set minimum login_समयout to 4 seconds. */
	अगर (nv->login_समयout != ql2xlogपूर्णांकimeout)
		nv->login_समयout = ql2xlogपूर्णांकimeout;
	अगर (nv->login_समयout < 4)
		nv->login_समयout = 4;
	ha->login_समयout = nv->login_समयout;

	/* Set minimum RATOV to 100 tenths of a second. */
	ha->r_a_tov = 100;

	ha->loop_reset_delay = nv->reset_delay;

	/* Link Down Timeout = 0:
	 *
	 * 	When Port Down समयr expires we will start वापसing
	 *	I/O's to OS with "DID_NO_CONNECT".
	 *
	 * Link Down Timeout != 0:
	 *
	 *	 The driver रुकोs क्रम the link to come up after link करोwn
	 *	 beक्रमe वापसing I/Os to OS with "DID_NO_CONNECT".
	 */
	अगर (nv->link_करोwn_समयout == 0) अणु
		ha->loop_करोwn_पात_समय =
		    (LOOP_DOWN_TIME - LOOP_DOWN_TIMEOUT);
	पूर्ण अन्यथा अणु
		ha->link_करोwn_समयout =	 nv->link_करोwn_समयout;
		ha->loop_करोwn_पात_समय =
		    (LOOP_DOWN_TIME - ha->link_करोwn_समयout);
	पूर्ण

	/*
	 * Need enough समय to try and get the port back.
	 */
	ha->port_करोwn_retry_count = nv->port_करोwn_retry_count;
	अगर (qlport_करोwn_retry)
		ha->port_करोwn_retry_count = qlport_करोwn_retry;
	/* Set login_retry_count */
	ha->login_retry_count  = nv->retry_count;
	अगर (ha->port_करोwn_retry_count == nv->port_करोwn_retry_count &&
	    ha->port_करोwn_retry_count > 3)
		ha->login_retry_count = ha->port_करोwn_retry_count;
	अन्यथा अगर (ha->port_करोwn_retry_count > (पूर्णांक)ha->login_retry_count)
		ha->login_retry_count = ha->port_करोwn_retry_count;
	अगर (ql2xloginretrycount)
		ha->login_retry_count = ql2xloginretrycount;

	icb->lun_enables = cpu_to_le16(0);
	icb->command_resource_count = 0;
	icb->immediate_notअगरy_resource_count = 0;
	icb->समयout = cpu_to_le16(0);

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha)) अणु
		/* Enable RIO */
		icb->firmware_options[0] &= ~BIT_3;
		icb->add_firmware_options[0] &=
		    ~(BIT_3 | BIT_2 | BIT_1 | BIT_0);
		icb->add_firmware_options[0] |= BIT_2;
		icb->response_accumulation_समयr = 3;
		icb->पूर्णांकerrupt_delay_समयr = 5;

		vha->flags.process_response_queue = 1;
	पूर्ण अन्यथा अणु
		/* Enable ZIO. */
		अगर (!vha->flags.init_करोne) अणु
			ha->zio_mode = icb->add_firmware_options[0] &
			    (BIT_3 | BIT_2 | BIT_1 | BIT_0);
			ha->zio_समयr = icb->पूर्णांकerrupt_delay_समयr ?
			    icb->पूर्णांकerrupt_delay_समयr : 2;
		पूर्ण
		icb->add_firmware_options[0] &=
		    ~(BIT_3 | BIT_2 | BIT_1 | BIT_0);
		vha->flags.process_response_queue = 0;
		अगर (ha->zio_mode != QLA_ZIO_DISABLED) अणु
			ha->zio_mode = QLA_ZIO_MODE_6;

			ql_log(ql_log_info, vha, 0x0068,
			    "ZIO mode %d enabled; timer delay (%d us).\n",
			    ha->zio_mode, ha->zio_समयr * 100);

			icb->add_firmware_options[0] |= (uपूर्णांक8_t)ha->zio_mode;
			icb->पूर्णांकerrupt_delay_समयr = (uपूर्णांक8_t)ha->zio_समयr;
			vha->flags.process_response_queue = 1;
		पूर्ण
	पूर्ण

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0069,
		    "NVRAM configuration failed.\n");
	पूर्ण
	वापस (rval);
पूर्ण

अटल व्योम
qla2x00_rport_del(व्योम *data)
अणु
	fc_port_t *fcport = data;
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(fcport->vha->host->host_lock, flags);
	rport = fcport->drport ? fcport->drport : fcport->rport;
	fcport->drport = शून्य;
	spin_unlock_irqrestore(fcport->vha->host->host_lock, flags);
	अगर (rport) अणु
		ql_dbg(ql_dbg_disc, fcport->vha, 0x210b,
		    "%s %8phN. rport %p roles %x\n",
		    __func__, fcport->port_name, rport,
		    rport->roles);

		fc_remote_port_delete(rport);
	पूर्ण
पूर्ण

व्योम qla2x00_set_fcport_state(fc_port_t *fcport, पूर्णांक state)
अणु
	पूर्णांक old_state;

	old_state = atomic_पढ़ो(&fcport->state);
	atomic_set(&fcport->state, state);

	/* Don't prपूर्णांक state transitions during initial allocation of fcport */
	अगर (old_state && old_state != state) अणु
		ql_dbg(ql_dbg_disc, fcport->vha, 0x207d,
		       "FCPort %8phC state transitioned from %s to %s - portid=%02x%02x%02x.\n",
		       fcport->port_name, port_state_str[old_state],
		       port_state_str[state], fcport->d_id.b.करोमुख्य,
		       fcport->d_id.b.area, fcport->d_id.b.al_pa);
	पूर्ण
पूर्ण

/**
 * qla2x00_alloc_fcport() - Allocate a generic fcport.
 * @vha: HA context
 * @flags: allocation flags
 *
 * Returns a poपूर्णांकer to the allocated fcport, or शून्य, अगर none available.
 */
fc_port_t *
qla2x00_alloc_fcport(scsi_qla_host_t *vha, gfp_t flags)
अणु
	fc_port_t *fcport;

	fcport = kzalloc(माप(fc_port_t), flags);
	अगर (!fcport)
		वापस शून्य;

	fcport->ct_desc.ct_sns = dma_alloc_coherent(&vha->hw->pdev->dev,
		माप(काष्ठा ct_sns_pkt), &fcport->ct_desc.ct_sns_dma,
		flags);
	अगर (!fcport->ct_desc.ct_sns) अणु
		ql_log(ql_log_warn, vha, 0xd049,
		    "Failed to allocate ct_sns request.\n");
		kमुक्त(fcport);
		वापस शून्य;
	पूर्ण

	/* Setup fcport ढाँचा काष्ठाure. */
	fcport->vha = vha;
	fcport->port_type = FCT_UNKNOWN;
	fcport->loop_id = FC_NO_LOOP_ID;
	qla2x00_set_fcport_state(fcport, FCS_UNCONFIGURED);
	fcport->supported_classes = FC_COS_UNSPECIFIED;
	fcport->fp_speed = PORT_SPEED_UNKNOWN;

	fcport->disc_state = DSC_DELETED;
	fcport->fw_login_state = DSC_LS_PORT_UNAVAIL;
	fcport->deleted = QLA_SESS_DELETED;
	fcport->login_retry = vha->hw->login_retry_count;
	fcport->chip_reset = vha->hw->base_qpair->chip_reset;
	fcport->logout_on_delete = 1;
	fcport->tgt_link_करोwn_समय = QLA2XX_MAX_LINK_DOWN_TIME;
	fcport->tgt_लघु_link_करोwn_cnt = 0;
	fcport->dev_loss_पंचांगo = 0;

	अगर (!fcport->ct_desc.ct_sns) अणु
		ql_log(ql_log_warn, vha, 0xd049,
		    "Failed to allocate ct_sns request.\n");
		kमुक्त(fcport);
		वापस शून्य;
	पूर्ण

	INIT_WORK(&fcport->del_work, qla24xx_delete_sess_fn);
	INIT_WORK(&fcport->मुक्त_work, qlt_मुक्त_session_करोne);
	INIT_WORK(&fcport->reg_work, qla_रेजिस्टर_fcport_fn);
	INIT_LIST_HEAD(&fcport->gnl_entry);
	INIT_LIST_HEAD(&fcport->list);

	INIT_LIST_HEAD(&fcport->sess_cmd_list);
	spin_lock_init(&fcport->sess_cmd_lock);

	वापस fcport;
पूर्ण

व्योम
qla2x00_मुक्त_fcport(fc_port_t *fcport)
अणु
	अगर (fcport->ct_desc.ct_sns) अणु
		dma_मुक्त_coherent(&fcport->vha->hw->pdev->dev,
			माप(काष्ठा ct_sns_pkt), fcport->ct_desc.ct_sns,
			fcport->ct_desc.ct_sns_dma);

		fcport->ct_desc.ct_sns = शून्य;
	पूर्ण
	list_del(&fcport->list);
	qla2x00_clear_loop_id(fcport);
	kमुक्त(fcport);
पूर्ण

अटल व्योम qla_get_login_ढाँचा(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;
	u32 *bp, sz;
	__be32 *q;

	स_रखो(ha->init_cb, 0, ha->init_cb_size);
	sz = min_t(पूर्णांक, माप(काष्ठा fc_els_flogi), ha->init_cb_size);
	rval = qla24xx_get_port_login_templ(vha, ha->init_cb_dma,
					    ha->init_cb, sz);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_init, vha, 0x00d1,
		       "PLOGI ELS param read fail.\n");
		वापस;
	पूर्ण
	q = (__be32 *)&ha->plogi_els_payld.fl_csp;

	bp = (uपूर्णांक32_t *)ha->init_cb;
	cpu_to_be32_array(q, bp, sz / 4);
	ha->flags.plogi_ढाँचा_valid = 1;
पूर्ण

/*
 * qla2x00_configure_loop
 *      Updates Fibre Channel Device Database with what is actually on loop.
 *
 * Input:
 *      ha                = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success.
 *      1 = error.
 *      2 = database was full and device was not configured.
 */
अटल पूर्णांक
qla2x00_configure_loop(scsi_qla_host_t *vha)
अणु
	पूर्णांक  rval;
	अचिन्हित दीर्घ flags, save_flags;
	काष्ठा qla_hw_data *ha = vha->hw;

	rval = QLA_SUCCESS;

	/* Get Initiator ID */
	अगर (test_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags)) अणु
		rval = qla2x00_configure_hba(vha);
		अगर (rval != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2013,
			    "Unable to configure HBA.\n");
			वापस (rval);
		पूर्ण
	पूर्ण

	save_flags = flags = vha->dpc_flags;
	ql_dbg(ql_dbg_disc, vha, 0x2014,
	    "Configure loop -- dpc flags = 0x%lx.\n", flags);

	/*
	 * If we have both an RSCN and PORT UPDATE pending then handle them
	 * both at the same समय.
	 */
	clear_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
	clear_bit(RSCN_UPDATE, &vha->dpc_flags);

	qla2x00_get_data_rate(vha);
	qla_get_login_ढाँचा(vha);

	/* Determine what we need to करो */
	अगर ((ha->current_topology == ISP_CFG_FL ||
	    ha->current_topology == ISP_CFG_F) &&
	    (test_bit(LOCAL_LOOP_UPDATE, &flags))) अणु

		set_bit(RSCN_UPDATE, &flags);
		clear_bit(LOCAL_LOOP_UPDATE, &flags);

	पूर्ण अन्यथा अगर (ha->current_topology == ISP_CFG_NL ||
		   ha->current_topology == ISP_CFG_N) अणु
		clear_bit(RSCN_UPDATE, &flags);
		set_bit(LOCAL_LOOP_UPDATE, &flags);
	पूर्ण अन्यथा अगर (!vha->flags.online ||
	    (test_bit(ABORT_ISP_ACTIVE, &flags))) अणु
		set_bit(RSCN_UPDATE, &flags);
		set_bit(LOCAL_LOOP_UPDATE, &flags);
	पूर्ण

	अगर (test_bit(LOCAL_LOOP_UPDATE, &flags)) अणु
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2015,
			    "Loop resync needed, failing.\n");
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा
			rval = qla2x00_configure_local_loop(vha);
	पूर्ण

	अगर (rval == QLA_SUCCESS && test_bit(RSCN_UPDATE, &flags)) अणु
		अगर (LOOP_TRANSITION(vha)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2099,
			    "Needs RSCN update and loop transition.\n");
			rval = QLA_FUNCTION_FAILED;
		पूर्ण
		अन्यथा
			rval = qla2x00_configure_fabric(vha);
	पूर्ण

	अगर (rval == QLA_SUCCESS) अणु
		अगर (atomic_पढ़ो(&vha->loop_करोwn_समयr) ||
		    test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags)) अणु
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			atomic_set(&vha->loop_state, LOOP_READY);
			ql_dbg(ql_dbg_disc, vha, 0x2069,
			    "LOOP READY.\n");
			ha->flags.fw_init_करोne = 1;

			/*
			 * Process any ATIO queue entries that came in
			 * जबतक we weren't online.
			 */
			अगर (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) अणु
				spin_lock_irqsave(&ha->tgt.atio_lock, flags);
				qlt_24xx_process_atio_queue(vha, 0);
				spin_unlock_irqrestore(&ha->tgt.atio_lock,
				    flags);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (rval) अणु
		ql_dbg(ql_dbg_disc, vha, 0x206a,
		    "%s *** FAILED ***.\n", __func__);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x206b,
		    "%s: exiting normally.\n", __func__);
	पूर्ण

	/* Restore state अगर a resync event occurred during processing */
	अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags)) अणु
		अगर (test_bit(LOCAL_LOOP_UPDATE, &save_flags))
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		अगर (test_bit(RSCN_UPDATE, &save_flags)) अणु
			set_bit(RSCN_UPDATE, &vha->dpc_flags);
		पूर्ण
	पूर्ण

	वापस (rval);
पूर्ण

अटल पूर्णांक qla2x00_configure_n2n_loop(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags;
	fc_port_t *fcport;

	अगर (test_and_clear_bit(N2N_LOGIN_NEEDED, &vha->dpc_flags))
		set_bit(RELOGIN_NEEDED, &vha->dpc_flags);

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->n2n_flag) अणु
			qla24xx_fcport_handle_login(vha, fcport);
			वापस QLA_SUCCESS;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&vha->work_lock, flags);
	vha->scan.scan_retry++;
	spin_unlock_irqrestore(&vha->work_lock, flags);

	अगर (vha->scan.scan_retry < MAX_SCAN_RETRIES) अणु
		set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
	पूर्ण
	वापस QLA_FUNCTION_FAILED;
पूर्ण

/*
 * qla2x00_configure_local_loop
 *	Updates Fibre Channel Device Database with local loop devices.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *	0 = success.
 */
अटल पूर्णांक
qla2x00_configure_local_loop(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval, rval2;
	पूर्णांक		found_devs;
	पूर्णांक		found;
	fc_port_t	*fcport, *new_fcport;
	uपूर्णांक16_t	index;
	uपूर्णांक16_t	entries;
	काष्ठा gid_list_info *gid;
	uपूर्णांक16_t	loop_id;
	uपूर्णांक8_t		करोमुख्य, area, al_pa;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;

	/* Inititae N2N login. */
	अगर (N2N_TOPO(ha))
		वापस qla2x00_configure_n2n_loop(vha);

	found_devs = 0;
	new_fcport = शून्य;
	entries = MAX_FIBRE_DEVICES_LOOP;

	/* Get list of logged in devices. */
	स_रखो(ha->gid_list, 0, qla2x00_gid_list_size(ha));
	rval = qla2x00_get_id_list(vha, ha->gid_list, ha->gid_list_dma,
	    &entries);
	अगर (rval != QLA_SUCCESS)
		जाओ err;

	ql_dbg(ql_dbg_disc, vha, 0x2011,
	    "Entries in ID list (%d).\n", entries);
	ql_dump_buffer(ql_dbg_disc + ql_dbg_buffer, vha, 0x2075,
	    ha->gid_list, entries * माप(*ha->gid_list));

	अगर (entries == 0) अणु
		spin_lock_irqsave(&vha->work_lock, flags);
		vha->scan.scan_retry++;
		spin_unlock_irqrestore(&vha->work_lock, flags);

		अगर (vha->scan.scan_retry < MAX_SCAN_RETRIES) अणु
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		पूर्ण
	पूर्ण अन्यथा अणु
		vha->scan.scan_retry = 0;
	पूर्ण

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		fcport->scan_state = QLA_FCPORT_SCAN;
	पूर्ण

	/* Allocate temporary fcport क्रम any new fcports discovered. */
	new_fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (new_fcport == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x2012,
		    "Memory allocation failed for fcport.\n");
		rval = QLA_MEMORY_ALLOC_FAILED;
		जाओ err;
	पूर्ण
	new_fcport->flags &= ~FCF_FABRIC_DEVICE;

	/* Add devices to port list. */
	gid = ha->gid_list;
	क्रम (index = 0; index < entries; index++) अणु
		करोमुख्य = gid->करोमुख्य;
		area = gid->area;
		al_pa = gid->al_pa;
		अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
			loop_id = gid->loop_id_2100;
		अन्यथा
			loop_id = le16_to_cpu(gid->loop_id);
		gid = (व्योम *)gid + ha->gid_list_info_size;

		/* Bypass reserved करोमुख्य fields. */
		अगर ((करोमुख्य & 0xf0) == 0xf0)
			जारी;

		/* Bypass अगर not same करोमुख्य and area of adapter. */
		अगर (area && करोमुख्य && ((area != vha->d_id.b.area) ||
		    (करोमुख्य != vha->d_id.b.करोमुख्य)) &&
		    (ha->current_topology == ISP_CFG_NL))
			जारी;


		/* Bypass invalid local loop ID. */
		अगर (loop_id > LAST_LOCAL_LOOP_ID)
			जारी;

		स_रखो(new_fcport->port_name, 0, WWN_SIZE);

		/* Fill in member data. */
		new_fcport->d_id.b.करोमुख्य = करोमुख्य;
		new_fcport->d_id.b.area = area;
		new_fcport->d_id.b.al_pa = al_pa;
		new_fcport->loop_id = loop_id;
		new_fcport->scan_state = QLA_FCPORT_FOUND;

		rval2 = qla2x00_get_port_database(vha, new_fcport, 0);
		अगर (rval2 != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2097,
			    "Failed to retrieve fcport information "
			    "-- get_port_database=%x, loop_id=0x%04x.\n",
			    rval2, new_fcport->loop_id);
			/* Skip retry अगर N2N */
			अगर (ha->current_topology != ISP_CFG_N) अणु
				ql_dbg(ql_dbg_disc, vha, 0x2105,
				    "Scheduling resync.\n");
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				जारी;
			पूर्ण
		पूर्ण

		spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
		/* Check क्रम matching device in port list. */
		found = 0;
		fcport = शून्य;
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (स_भेद(new_fcport->port_name, fcport->port_name,
			    WWN_SIZE))
				जारी;

			fcport->flags &= ~FCF_FABRIC_DEVICE;
			fcport->loop_id = new_fcport->loop_id;
			fcport->port_type = new_fcport->port_type;
			fcport->d_id.b24 = new_fcport->d_id.b24;
			स_नकल(fcport->node_name, new_fcport->node_name,
			    WWN_SIZE);
			fcport->scan_state = QLA_FCPORT_FOUND;
			found++;
			अवरोध;
		पूर्ण

		अगर (!found) अणु
			/* New device, add to fcports list. */
			list_add_tail(&new_fcport->list, &vha->vp_fcports);

			/* Allocate a new replacement fcport. */
			fcport = new_fcport;

			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

			new_fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);

			अगर (new_fcport == शून्य) अणु
				ql_log(ql_log_warn, vha, 0xd031,
				    "Failed to allocate memory for fcport.\n");
				rval = QLA_MEMORY_ALLOC_FAILED;
				जाओ err;
			पूर्ण
			spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
			new_fcport->flags &= ~FCF_FABRIC_DEVICE;
		पूर्ण

		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

		/* Base iIDMA settings on HBA port speed. */
		fcport->fp_speed = ha->link_data_rate;

		found_devs++;
	पूर्ण

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
			अवरोध;

		अगर (fcport->scan_state == QLA_FCPORT_SCAN) अणु
			अगर ((qla_dual_mode_enabled(vha) ||
			    qla_ini_mode_enabled(vha)) &&
			    atomic_पढ़ो(&fcport->state) == FCS_ONLINE) अणु
				qla2x00_mark_device_lost(vha, fcport,
					ql2xplogiअसलentdevice);
				अगर (fcport->loop_id != FC_NO_LOOP_ID &&
				    (fcport->flags & FCF_FCP2_DEVICE) == 0 &&
				    fcport->port_type != FCT_INITIATOR &&
				    fcport->port_type != FCT_BROADCAST) अणु
					ql_dbg(ql_dbg_disc, vha, 0x20f0,
					    "%s %d %8phC post del sess\n",
					    __func__, __LINE__,
					    fcport->port_name);

					qlt_schedule_sess_क्रम_deletion(fcport);
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (fcport->scan_state == QLA_FCPORT_FOUND)
			qla24xx_fcport_handle_login(vha, fcport);
	पूर्ण

	qla2x00_मुक्त_fcport(new_fcport);

	वापस rval;

err:
	ql_dbg(ql_dbg_disc, vha, 0x2098,
	       "Configure local loop error exit: rval=%x.\n", rval);
	वापस rval;
पूर्ण

अटल व्योम
qla2x00_iidma_fcport(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक rval;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_IIDMA_CAPABLE(ha))
		वापस;

	अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE)
		वापस;

	अगर (fcport->fp_speed == PORT_SPEED_UNKNOWN ||
	    fcport->fp_speed > ha->link_data_rate ||
	    !ha->flags.gpsc_supported)
		वापस;

	rval = qla2x00_set_idma_speed(vha, fcport->loop_id, fcport->fp_speed,
	    mb);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2004,
		    "Unable to adjust iIDMA %8phN -- %04x %x %04x %04x.\n",
		    fcport->port_name, rval, fcport->fp_speed, mb[0], mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x2005,
		    "iIDMA adjusted to %s GB/s (%X) on %8phN.\n",
		    qla2x00_get_link_speed_str(ha, fcport->fp_speed),
		    fcport->fp_speed, fcport->port_name);
	पूर्ण
पूर्ण

व्योम qla_करो_iidma_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	qla2x00_iidma_fcport(vha, fcport);
	qla24xx_update_fcport_fcp_prio(vha, fcport);
पूर्ण

पूर्णांक qla_post_iidma_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_IIDMA);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.fcport.fcport = fcport;
	वापस qla2x00_post_work(vha, e);
पूर्ण

/* qla2x00_reg_remote_port is reserved क्रम Initiator Mode only.*/
अटल व्योम
qla2x00_reg_remote_port(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	काष्ठा fc_rport_identअगरiers rport_ids;
	काष्ठा fc_rport *rport;
	अचिन्हित दीर्घ flags;

	अगर (atomic_पढ़ो(&fcport->state) == FCS_ONLINE)
		वापस;

	rport_ids.node_name = wwn_to_u64(fcport->node_name);
	rport_ids.port_name = wwn_to_u64(fcport->port_name);
	rport_ids.port_id = fcport->d_id.b.करोमुख्य << 16 |
	    fcport->d_id.b.area << 8 | fcport->d_id.b.al_pa;
	rport_ids.roles = FC_RPORT_ROLE_UNKNOWN;
	fcport->rport = rport = fc_remote_port_add(vha->host, 0, &rport_ids);
	अगर (!rport) अणु
		ql_log(ql_log_warn, vha, 0x2006,
		    "Unable to allocate fc remote port.\n");
		वापस;
	पूर्ण

	spin_lock_irqsave(fcport->vha->host->host_lock, flags);
	*((fc_port_t **)rport->dd_data) = fcport;
	spin_unlock_irqrestore(fcport->vha->host->host_lock, flags);
	fcport->dev_loss_पंचांगo = rport->dev_loss_पंचांगo;

	rport->supported_classes = fcport->supported_classes;

	rport_ids.roles = FC_PORT_ROLE_UNKNOWN;
	अगर (fcport->port_type == FCT_INITIATOR)
		rport_ids.roles |= FC_PORT_ROLE_FCP_INITIATOR;
	अगर (fcport->port_type == FCT_TARGET)
		rport_ids.roles |= FC_PORT_ROLE_FCP_TARGET;
	अगर (fcport->port_type & FCT_NVME_INITIATOR)
		rport_ids.roles |= FC_PORT_ROLE_NVME_INITIATOR;
	अगर (fcport->port_type & FCT_NVME_TARGET)
		rport_ids.roles |= FC_PORT_ROLE_NVME_TARGET;
	अगर (fcport->port_type & FCT_NVME_DISCOVERY)
		rport_ids.roles |= FC_PORT_ROLE_NVME_DISCOVERY;

	fc_remote_port_rolechg(rport, rport_ids.roles);

	ql_dbg(ql_dbg_disc, vha, 0x20ee,
	    "%s: %8phN. rport %ld:0:%d (%p) is %s mode\n",
	    __func__, fcport->port_name, vha->host_no,
	    rport->scsi_target_id, rport,
	    (fcport->port_type == FCT_TARGET) ? "tgt" :
	    ((fcport->port_type & FCT_NVME) ? "nvme" : "ini"));
पूर्ण

/*
 * qla2x00_update_fcport
 *	Updates device on list.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	fcport = port काष्ठाure poपूर्णांकer.
 *
 * Return:
 *	0  - Success
 *  BIT_0 - error
 *
 * Context:
 *	Kernel context.
 */
व्योम
qla2x00_update_fcport(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	अगर (IS_SW_RESV_ADDR(fcport->d_id))
		वापस;

	ql_dbg(ql_dbg_disc, vha, 0x20ef, "%s %8phC\n",
	    __func__, fcport->port_name);

	qla2x00_set_fcport_disc_state(fcport, DSC_UPD_FCPORT);
	fcport->login_retry = vha->hw->login_retry_count;
	fcport->flags &= ~(FCF_LOGIN_NEEDED | FCF_ASYNC_SENT);
	fcport->deleted = 0;
	अगर (vha->hw->current_topology == ISP_CFG_NL)
		fcport->logout_on_delete = 0;
	अन्यथा
		fcport->logout_on_delete = 1;
	fcport->n2n_chip_reset = fcport->n2n_link_reset_cnt = 0;

	अगर (fcport->tgt_link_करोwn_समय < fcport->dev_loss_पंचांगo) अणु
		fcport->tgt_लघु_link_करोwn_cnt++;
		fcport->tgt_link_करोwn_समय = QLA2XX_MAX_LINK_DOWN_TIME;
	पूर्ण

	चयन (vha->hw->current_topology) अणु
	हाल ISP_CFG_N:
	हाल ISP_CFG_NL:
		fcport->keep_nport_handle = 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	qla2x00_iidma_fcport(vha, fcport);

	qla2x00_dfs_create_rport(vha, fcport);

	अगर (NVME_TARGET(vha->hw, fcport)) अणु
		qla_nvme_रेजिस्टर_remote(vha, fcport);
		qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_COMPLETE);
		qla2x00_set_fcport_state(fcport, FCS_ONLINE);
		वापस;
	पूर्ण

	qla24xx_update_fcport_fcp_prio(vha, fcport);

	चयन (vha->host->active_mode) अणु
	हाल MODE_INITIATOR:
		qla2x00_reg_remote_port(vha, fcport);
		अवरोध;
	हाल MODE_TARGET:
		अगर (!vha->vha_tgt.qla_tgt->tgt_stop &&
			!vha->vha_tgt.qla_tgt->tgt_stopped)
			qlt_fc_port_added(vha, fcport);
		अवरोध;
	हाल MODE_DUAL:
		qla2x00_reg_remote_port(vha, fcport);
		अगर (!vha->vha_tgt.qla_tgt->tgt_stop &&
			!vha->vha_tgt.qla_tgt->tgt_stopped)
			qlt_fc_port_added(vha, fcport);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	qla2x00_set_fcport_state(fcport, FCS_ONLINE);

	अगर (IS_IIDMA_CAPABLE(vha->hw) && vha->hw->flags.gpsc_supported) अणु
		अगर (fcport->id_changed) अणु
			fcport->id_changed = 0;
			ql_dbg(ql_dbg_disc, vha, 0x20d7,
			    "%s %d %8phC post gfpnid fcp_cnt %d\n",
			    __func__, __LINE__, fcport->port_name,
			    vha->fcport_count);
			qla24xx_post_gfpnid_work(vha, fcport);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_disc, vha, 0x20d7,
			    "%s %d %8phC post gpsc fcp_cnt %d\n",
			    __func__, __LINE__, fcport->port_name,
			    vha->fcport_count);
			qla24xx_post_gpsc_work(vha, fcport);
		पूर्ण
	पूर्ण

	qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_COMPLETE);
पूर्ण

व्योम qla_रेजिस्टर_fcport_fn(काष्ठा work_काष्ठा *work)
अणु
	fc_port_t *fcport = container_of(work, काष्ठा fc_port, reg_work);
	u32 rscn_gen = fcport->rscn_gen;
	u16 data[2];

	अगर (IS_SW_RESV_ADDR(fcport->d_id))
		वापस;

	qla2x00_update_fcport(fcport->vha, fcport);

	अगर (rscn_gen != fcport->rscn_gen) अणु
		/* RSCN(s) came in जबतक registration */
		चयन (fcport->next_disc_state) अणु
		हाल DSC_DELETE_PEND:
			qlt_schedule_sess_क्रम_deletion(fcport);
			अवरोध;
		हाल DSC_ADISC:
			data[0] = data[1] = 0;
			qla2x00_post_async_adisc_work(fcport->vha, fcport,
			    data);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * qla2x00_configure_fabric
 *      Setup SNS devices with loop ID's.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success.
 *      BIT_0 = error
 */
अटल पूर्णांक
qla2x00_configure_fabric(scsi_qla_host_t *vha)
अणु
	पूर्णांक	rval;
	fc_port_t	*fcport;
	uपूर्णांक16_t	mb[MAILBOX_REGISTER_COUNT];
	uपूर्णांक16_t	loop_id;
	LIST_HEAD(new_fcports);
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक		discovery_gen;

	/* If FL port exists, then SNS is present */
	अगर (IS_FWI2_CAPABLE(ha))
		loop_id = NPH_F_PORT;
	अन्यथा
		loop_id = SNS_FL_PORT;
	rval = qla2x00_get_port_name(vha, loop_id, vha->fabric_node_name, 1);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_disc, vha, 0x20a0,
		    "MBX_GET_PORT_NAME failed, No FL Port.\n");

		vha->device_flags &= ~SWITCH_FOUND;
		वापस (QLA_SUCCESS);
	पूर्ण
	vha->device_flags |= SWITCH_FOUND;

	rval = qla2x00_get_port_name(vha, loop_id, vha->fabric_port_name, 0);
	अगर (rval != QLA_SUCCESS)
		ql_dbg(ql_dbg_disc, vha, 0x20ff,
		    "Failed to get Fabric Port Name\n");

	अगर (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha)) अणु
		rval = qla2x00_send_change_request(vha, 0x3, 0);
		अगर (rval != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0x121,
			    "Failed to enable receiving of RSCN requests: 0x%x.\n",
			    rval);
	पूर्ण

	करो अणु
		qla2x00_mgmt_svr_login(vha);

		/* Ensure we are logged पूर्णांकo the SNS. */
		loop_id = NPH_SNS_LID(ha);
		rval = ha->isp_ops->fabric_login(vha, loop_id, 0xff, 0xff,
		    0xfc, mb, BIT_1|BIT_0);
		अगर (rval != QLA_SUCCESS || mb[0] != MBS_COMMAND_COMPLETE) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20a1,
			    "Failed SNS login: loop_id=%x mb[0]=%x mb[1]=%x mb[2]=%x mb[6]=%x mb[7]=%x (%x).\n",
			    loop_id, mb[0], mb[1], mb[2], mb[6], mb[7], rval);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			वापस rval;
		पूर्ण

		/* FDMI support. */
		अगर (ql2xfdmienable &&
		    test_and_clear_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags))
			qla2x00_fdmi_रेजिस्टर(vha);

		अगर (test_and_clear_bit(REGISTER_FC4_NEEDED, &vha->dpc_flags)) अणु
			अगर (qla2x00_rft_id(vha)) अणु
				/* EMPTY */
				ql_dbg(ql_dbg_disc, vha, 0x20a2,
				    "Register FC-4 TYPE failed.\n");
				अगर (test_bit(LOOP_RESYNC_NEEDED,
				    &vha->dpc_flags))
					अवरोध;
			पूर्ण
			अगर (qla2x00_rff_id(vha, FC4_TYPE_FCP_SCSI)) अणु
				/* EMPTY */
				ql_dbg(ql_dbg_disc, vha, 0x209a,
				    "Register FC-4 Features failed.\n");
				अगर (test_bit(LOOP_RESYNC_NEEDED,
				    &vha->dpc_flags))
					अवरोध;
			पूर्ण
			अगर (vha->flags.nvme_enabled) अणु
				अगर (qla2x00_rff_id(vha, FC_TYPE_NVME)) अणु
					ql_dbg(ql_dbg_disc, vha, 0x2049,
					    "Register NVME FC Type Features failed.\n");
				पूर्ण
			पूर्ण
			अगर (qla2x00_rnn_id(vha)) अणु
				/* EMPTY */
				ql_dbg(ql_dbg_disc, vha, 0x2104,
				    "Register Node Name failed.\n");
				अगर (test_bit(LOOP_RESYNC_NEEDED,
				    &vha->dpc_flags))
					अवरोध;
			पूर्ण अन्यथा अगर (qla2x00_rsnn_nn(vha)) अणु
				/* EMPTY */
				ql_dbg(ql_dbg_disc, vha, 0x209b,
				    "Register Symbolic Node Name failed.\n");
				अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
					अवरोध;
			पूर्ण
		पूर्ण


		/* Mark the समय right beक्रमe querying FW क्रम connected ports.
		 * This process is दीर्घ, asynchronous and by the समय it's करोne,
		 * collected inक्रमmation might not be accurate anymore. E.g.
		 * disconnected port might have re-connected and a bअक्रम new
		 * session has been created. In this हाल session's generation
		 * will be newer than discovery_gen. */
		qlt_करो_generation_tick(vha, &discovery_gen);

		अगर (USE_ASYNC_SCAN(ha)) अणु
			rval = qla24xx_async_gpnft(vha, FC4_TYPE_FCP_SCSI,
			    शून्य);
			अगर (rval)
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		पूर्ण अन्यथा  अणु
			list_क्रम_each_entry(fcport, &vha->vp_fcports, list)
				fcport->scan_state = QLA_FCPORT_SCAN;

			rval = qla2x00_find_all_fabric_devs(vha);
		पूर्ण
		अगर (rval != QLA_SUCCESS)
			अवरोध;
	पूर्ण जबतक (0);

	अगर (!vha->nvme_local_port && vha->flags.nvme_enabled)
		qla_nvme_रेजिस्टर_hba(vha);

	अगर (rval)
		ql_dbg(ql_dbg_disc, vha, 0x2068,
		    "Configure fabric error exit rval=%d.\n", rval);

	वापस (rval);
पूर्ण

/*
 * qla2x00_find_all_fabric_devs
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	dev = database device entry poपूर्णांकer.
 *
 * Returns:
 *	0 = success.
 *
 * Context:
 *	Kernel context.
 */
अटल पूर्णांक
qla2x00_find_all_fabric_devs(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	uपूर्णांक16_t	loop_id;
	fc_port_t	*fcport, *new_fcport;
	पूर्णांक		found;

	sw_info_t	*swl;
	पूर्णांक		swl_idx;
	पूर्णांक		first_dev, last_dev;
	port_id_t	wrap = अणुपूर्ण, nxt_d_id;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	अचिन्हित दीर्घ flags;

	rval = QLA_SUCCESS;

	/* Try GID_PT to get device list, अन्यथा GAN. */
	अगर (!ha->swl)
		ha->swl = kसुस्मृति(ha->max_fibre_devices, माप(sw_info_t),
		    GFP_KERNEL);
	swl = ha->swl;
	अगर (!swl) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_disc, vha, 0x209c,
		    "GID_PT allocations failed, fallback on GA_NXT.\n");
	पूर्ण अन्यथा अणु
		स_रखो(swl, 0, ha->max_fibre_devices * माप(sw_info_t));
		अगर (qla2x00_gid_pt(vha, swl) != QLA_SUCCESS) अणु
			swl = शून्य;
			अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
				वापस rval;
		पूर्ण अन्यथा अगर (qla2x00_gpn_id(vha, swl) != QLA_SUCCESS) अणु
			swl = शून्य;
			अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
				वापस rval;
		पूर्ण अन्यथा अगर (qla2x00_gnn_id(vha, swl) != QLA_SUCCESS) अणु
			swl = शून्य;
			अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
				वापस rval;
		पूर्ण अन्यथा अगर (qla2x00_gfpn_id(vha, swl) != QLA_SUCCESS) अणु
			swl = शून्य;
			अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
				वापस rval;
		पूर्ण

		/* If other queries succeeded probe क्रम FC-4 type */
		अगर (swl) अणु
			qla2x00_gff_id(vha, swl);
			अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
				वापस rval;
		पूर्ण
	पूर्ण
	swl_idx = 0;

	/* Allocate temporary fcport क्रम any new fcports discovered. */
	new_fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (new_fcport == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x209d,
		    "Failed to allocate memory for fcport.\n");
		वापस (QLA_MEMORY_ALLOC_FAILED);
	पूर्ण
	new_fcport->flags |= (FCF_FABRIC_DEVICE | FCF_LOGIN_NEEDED);
	/* Set start port ID scan at adapter ID. */
	first_dev = 1;
	last_dev = 0;

	/* Starting मुक्त loop ID. */
	loop_id = ha->min_बाह्यal_loopid;
	क्रम (; loop_id <= ha->max_loop_id; loop_id++) अणु
		अगर (qla2x00_is_reserved_id(vha, loop_id))
			जारी;

		अगर (ha->current_topology == ISP_CFG_FL &&
		    (atomic_पढ़ो(&vha->loop_करोwn_समयr) ||
		     LOOP_TRANSITION(vha))) अणु
			atomic_set(&vha->loop_करोwn_समयr, 0);
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
			अवरोध;
		पूर्ण

		अगर (swl != शून्य) अणु
			अगर (last_dev) अणु
				wrap.b24 = new_fcport->d_id.b24;
			पूर्ण अन्यथा अणु
				new_fcport->d_id.b24 = swl[swl_idx].d_id.b24;
				स_नकल(new_fcport->node_name,
				    swl[swl_idx].node_name, WWN_SIZE);
				स_नकल(new_fcport->port_name,
				    swl[swl_idx].port_name, WWN_SIZE);
				स_नकल(new_fcport->fabric_port_name,
				    swl[swl_idx].fabric_port_name, WWN_SIZE);
				new_fcport->fp_speed = swl[swl_idx].fp_speed;
				new_fcport->fc4_type = swl[swl_idx].fc4_type;

				new_fcport->nvme_flag = 0;
				अगर (vha->flags.nvme_enabled &&
				    swl[swl_idx].fc4_type & FS_FC4TYPE_NVME) अणु
					ql_log(ql_log_info, vha, 0x2131,
					    "FOUND: NVME port %8phC as FC Type 28h\n",
					    new_fcport->port_name);
				पूर्ण

				अगर (swl[swl_idx].d_id.b.rsvd_1 != 0) अणु
					last_dev = 1;
				पूर्ण
				swl_idx++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Send GA_NXT to the चयन */
			rval = qla2x00_ga_nxt(vha, new_fcport);
			अगर (rval != QLA_SUCCESS) अणु
				ql_log(ql_log_warn, vha, 0x209e,
				    "SNS scan failed -- assuming "
				    "zero-entry result.\n");
				rval = QLA_SUCCESS;
				अवरोध;
			पूर्ण
		पूर्ण

		/* If wrap on चयन device list, निकास. */
		अगर (first_dev) अणु
			wrap.b24 = new_fcport->d_id.b24;
			first_dev = 0;
		पूर्ण अन्यथा अगर (new_fcport->d_id.b24 == wrap.b24) अणु
			ql_dbg(ql_dbg_disc, vha, 0x209f,
			    "Device wrap (%02x%02x%02x).\n",
			    new_fcport->d_id.b.करोमुख्य,
			    new_fcport->d_id.b.area,
			    new_fcport->d_id.b.al_pa);
			अवरोध;
		पूर्ण

		/* Bypass अगर same physical adapter. */
		अगर (new_fcport->d_id.b24 == base_vha->d_id.b24)
			जारी;

		/* Bypass भव ports of the same host. */
		अगर (qla2x00_is_a_vp_did(vha, new_fcport->d_id.b24))
			जारी;

		/* Bypass अगर same करोमुख्य and area of adapter. */
		अगर (((new_fcport->d_id.b24 & 0xffff00) ==
		    (vha->d_id.b24 & 0xffff00)) && ha->current_topology ==
			ISP_CFG_FL)
			    जारी;

		/* Bypass reserved करोमुख्य fields. */
		अगर ((new_fcport->d_id.b.करोमुख्य & 0xf0) == 0xf0)
			जारी;

		/* Bypass ports whose FCP-4 type is not FCP_SCSI */
		अगर (ql2xgffidenable &&
		    (!(new_fcport->fc4_type & FS_FC4TYPE_FCP) &&
		    new_fcport->fc4_type != 0))
			जारी;

		spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);

		/* Locate matching device in database. */
		found = 0;
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (स_भेद(new_fcport->port_name, fcport->port_name,
			    WWN_SIZE))
				जारी;

			fcport->scan_state = QLA_FCPORT_FOUND;

			found++;

			/* Update port state. */
			स_नकल(fcport->fabric_port_name,
			    new_fcport->fabric_port_name, WWN_SIZE);
			fcport->fp_speed = new_fcport->fp_speed;

			/*
			 * If address the same and state FCS_ONLINE
			 * (or in target mode), nothing changed.
			 */
			अगर (fcport->d_id.b24 == new_fcport->d_id.b24 &&
			    (atomic_पढ़ो(&fcport->state) == FCS_ONLINE ||
			     (vha->host->active_mode == MODE_TARGET))) अणु
				अवरोध;
			पूर्ण

			अगर (fcport->login_retry == 0)
				fcport->login_retry =
					vha->hw->login_retry_count;
			/*
			 * If device was not a fabric device beक्रमe.
			 */
			अगर ((fcport->flags & FCF_FABRIC_DEVICE) == 0) अणु
				fcport->d_id.b24 = new_fcport->d_id.b24;
				qla2x00_clear_loop_id(fcport);
				fcport->flags |= (FCF_FABRIC_DEVICE |
				    FCF_LOGIN_NEEDED);
				अवरोध;
			पूर्ण

			/*
			 * Port ID changed or device was marked to be updated;
			 * Log it out अगर still logged in and mark it क्रम
			 * relogin later.
			 */
			अगर (qla_tgt_mode_enabled(base_vha)) अणु
				ql_dbg(ql_dbg_tgt_mgt, vha, 0xf080,
					 "port changed FC ID, %8phC"
					 " old %x:%x:%x (loop_id 0x%04x)-> new %x:%x:%x\n",
					 fcport->port_name,
					 fcport->d_id.b.करोमुख्य,
					 fcport->d_id.b.area,
					 fcport->d_id.b.al_pa,
					 fcport->loop_id,
					 new_fcport->d_id.b.करोमुख्य,
					 new_fcport->d_id.b.area,
					 new_fcport->d_id.b.al_pa);
				fcport->d_id.b24 = new_fcport->d_id.b24;
				अवरोध;
			पूर्ण

			fcport->d_id.b24 = new_fcport->d_id.b24;
			fcport->flags |= FCF_LOGIN_NEEDED;
			अवरोध;
		पूर्ण

		अगर (found && NVME_TARGET(vha->hw, fcport)) अणु
			अगर (fcport->disc_state == DSC_DELETE_PEND) अणु
				qla2x00_set_fcport_disc_state(fcport, DSC_GNL);
				vha->fcport_count--;
				fcport->login_succ = 0;
			पूर्ण
		पूर्ण

		अगर (found) अणु
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
			जारी;
		पूर्ण
		/* If device was not in our fcports list, then add it. */
		new_fcport->scan_state = QLA_FCPORT_FOUND;
		list_add_tail(&new_fcport->list, &vha->vp_fcports);

		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);


		/* Allocate a new replacement fcport. */
		nxt_d_id.b24 = new_fcport->d_id.b24;
		new_fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
		अगर (new_fcport == शून्य) अणु
			ql_log(ql_log_warn, vha, 0xd032,
			    "Memory allocation failed for fcport.\n");
			वापस (QLA_MEMORY_ALLOC_FAILED);
		पूर्ण
		new_fcport->flags |= (FCF_FABRIC_DEVICE | FCF_LOGIN_NEEDED);
		new_fcport->d_id.b24 = nxt_d_id.b24;
	पूर्ण

	qla2x00_मुक्त_fcport(new_fcport);

	/*
	 * Logout all previous fabric dev marked lost, except FCP2 devices.
	 */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
			अवरोध;

		अगर ((fcport->flags & FCF_FABRIC_DEVICE) == 0)
			जारी;

		अगर (fcport->scan_state == QLA_FCPORT_SCAN) अणु
			अगर ((qla_dual_mode_enabled(vha) ||
			    qla_ini_mode_enabled(vha)) &&
			    atomic_पढ़ो(&fcport->state) == FCS_ONLINE) अणु
				qla2x00_mark_device_lost(vha, fcport,
					ql2xplogiअसलentdevice);
				अगर (fcport->loop_id != FC_NO_LOOP_ID &&
				    (fcport->flags & FCF_FCP2_DEVICE) == 0 &&
				    fcport->port_type != FCT_INITIATOR &&
				    fcport->port_type != FCT_BROADCAST) अणु
					ql_dbg(ql_dbg_disc, vha, 0x20f0,
					    "%s %d %8phC post del sess\n",
					    __func__, __LINE__,
					    fcport->port_name);
					qlt_schedule_sess_क्रम_deletion(fcport);
					जारी;
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (fcport->scan_state == QLA_FCPORT_FOUND &&
		    (fcport->flags & FCF_LOGIN_NEEDED) != 0)
			qla24xx_fcport_handle_login(vha, fcport);
	पूर्ण
	वापस (rval);
पूर्ण

/* FW करोes not set aside Loop id क्रम MGMT Server/FFFFFAh */
पूर्णांक
qla2x00_reserve_mgmt_server_loop_id(scsi_qla_host_t *vha)
अणु
	पूर्णांक loop_id = FC_NO_LOOP_ID;
	पूर्णांक lid = NPH_MGMT_SERVER - vha->vp_idx;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->vp_idx == 0) अणु
		set_bit(NPH_MGMT_SERVER, ha->loop_id_map);
		वापस NPH_MGMT_SERVER;
	पूर्ण

	/* pick id from high and work करोwn to low */
	spin_lock_irqsave(&ha->vport_slock, flags);
	क्रम (; lid > 0; lid--) अणु
		अगर (!test_bit(lid, vha->hw->loop_id_map)) अणु
			set_bit(lid, vha->hw->loop_id_map);
			loop_id = lid;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	वापस loop_id;
पूर्ण

/*
 * qla2x00_fabric_login
 *	Issue fabric login command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	device = poपूर्णांकer to FC device type काष्ठाure.
 *
 * Returns:
 *      0 - Login successfully
 *      1 - Login failed
 *      2 - Initiator device
 *      3 - Fatal error
 */
पूर्णांक
qla2x00_fabric_login(scsi_qla_host_t *vha, fc_port_t *fcport,
    uपूर्णांक16_t *next_loopid)
अणु
	पूर्णांक	rval;
	पूर्णांक	retry;
	uपूर्णांक16_t पंचांगp_loopid;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	काष्ठा qla_hw_data *ha = vha->hw;

	retry = 0;
	पंचांगp_loopid = 0;

	क्रम (;;) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2000,
		    "Trying Fabric Login w/loop id 0x%04x for port "
		    "%02x%02x%02x.\n",
		    fcport->loop_id, fcport->d_id.b.करोमुख्य,
		    fcport->d_id.b.area, fcport->d_id.b.al_pa);

		/* Login fcport on चयन. */
		rval = ha->isp_ops->fabric_login(vha, fcport->loop_id,
		    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa, mb, BIT_0);
		अगर (rval != QLA_SUCCESS) अणु
			वापस rval;
		पूर्ण
		अगर (mb[0] == MBS_PORT_ID_USED) अणु
			/*
			 * Device has another loop ID.  The firmware team
			 * recommends the driver perक्रमm an implicit login with
			 * the specअगरied ID again. The ID we just used is save
			 * here so we वापस with an ID that can be tried by
			 * the next login.
			 */
			retry++;
			पंचांगp_loopid = fcport->loop_id;
			fcport->loop_id = mb[1];

			ql_dbg(ql_dbg_disc, vha, 0x2001,
			    "Fabric Login: port in use - next loop "
			    "id=0x%04x, port id= %02x%02x%02x.\n",
			    fcport->loop_id, fcport->d_id.b.करोमुख्य,
			    fcport->d_id.b.area, fcport->d_id.b.al_pa);

		पूर्ण अन्यथा अगर (mb[0] == MBS_COMMAND_COMPLETE) अणु
			/*
			 * Login succeeded.
			 */
			अगर (retry) अणु
				/* A retry occurred beक्रमe. */
				*next_loopid = पंचांगp_loopid;
			पूर्ण अन्यथा अणु
				/*
				 * No retry occurred beक्रमe. Just increment the
				 * ID value क्रम next login.
				 */
				*next_loopid = (fcport->loop_id + 1);
			पूर्ण

			अगर (mb[1] & BIT_0) अणु
				fcport->port_type = FCT_INITIATOR;
			पूर्ण अन्यथा अणु
				fcport->port_type = FCT_TARGET;
				अगर (mb[1] & BIT_1) अणु
					fcport->flags |= FCF_FCP2_DEVICE;
				पूर्ण
			पूर्ण

			अगर (mb[10] & BIT_0)
				fcport->supported_classes |= FC_COS_CLASS2;
			अगर (mb[10] & BIT_1)
				fcport->supported_classes |= FC_COS_CLASS3;

			अगर (IS_FWI2_CAPABLE(ha)) अणु
				अगर (mb[10] & BIT_7)
					fcport->flags |=
					    FCF_CONF_COMP_SUPPORTED;
			पूर्ण

			rval = QLA_SUCCESS;
			अवरोध;
		पूर्ण अन्यथा अगर (mb[0] == MBS_LOOP_ID_USED) अणु
			/*
			 * Loop ID alपढ़ोy used, try next loop ID.
			 */
			fcport->loop_id++;
			rval = qla2x00_find_new_loop_id(vha, fcport);
			अगर (rval != QLA_SUCCESS) अणु
				/* Ran out of loop IDs to use */
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (mb[0] == MBS_COMMAND_ERROR) अणु
			/*
			 * Firmware possibly समयd out during login. If NO
			 * retries are left to करो then the device is declared
			 * dead.
			 */
			*next_loopid = fcport->loop_id;
			ha->isp_ops->fabric_logout(vha, fcport->loop_id,
			    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
			    fcport->d_id.b.al_pa);
			qla2x00_mark_device_lost(vha, fcport, 1);

			rval = 1;
			अवरोध;
		पूर्ण अन्यथा अणु
			/*
			 * unrecoverable / not handled error
			 */
			ql_dbg(ql_dbg_disc, vha, 0x2002,
			    "Failed=%x port_id=%02x%02x%02x loop_id=%x "
			    "jiffies=%lx.\n", mb[0], fcport->d_id.b.करोमुख्य,
			    fcport->d_id.b.area, fcport->d_id.b.al_pa,
			    fcport->loop_id, jअगरfies);

			*next_loopid = fcport->loop_id;
			ha->isp_ops->fabric_logout(vha, fcport->loop_id,
			    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
			    fcport->d_id.b.al_pa);
			qla2x00_clear_loop_id(fcport);
			fcport->login_retry = 0;

			rval = 3;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस (rval);
पूर्ण

/*
 * qla2x00_local_device_login
 *	Issue local device login command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	loop_id = loop id of device to login to.
 *
 * Returns (Where's the #घोषणा!!!!):
 *      0 - Login successfully
 *      1 - Login failed
 *      3 - Fatal error
 */
पूर्णांक
qla2x00_local_device_login(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक		rval;
	uपूर्णांक16_t	mb[MAILBOX_REGISTER_COUNT];

	स_रखो(mb, 0, माप(mb));
	rval = qla2x00_login_local_device(vha, fcport, mb, BIT_0);
	अगर (rval == QLA_SUCCESS) अणु
		/* Interrogate mailbox रेजिस्टरs क्रम any errors */
		अगर (mb[0] == MBS_COMMAND_ERROR)
			rval = 1;
		अन्यथा अगर (mb[0] == MBS_COMMAND_PARAMETER_ERROR)
			/* device not in PCB table */
			rval = 3;
	पूर्ण

	वापस (rval);
पूर्ण

/*
 *  qla2x00_loop_resync
 *      Resync with fibre channel devices.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
पूर्णांक
qla2x00_loop_resync(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक32_t रुको_समय;

	clear_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
	अगर (vha->flags.online) अणु
		अगर (!(rval = qla2x00_fw_पढ़ोy(vha))) अणु
			/* Wait at most MAX_TARGET RSCNs क्रम a stable link. */
			रुको_समय = 256;
			करो अणु
				अगर (!IS_QLAFX00(vha->hw)) अणु
					/*
					 * Issue a marker after FW becomes
					 * पढ़ोy.
					 */
					qla2x00_marker(vha, vha->hw->base_qpair,
					    0, 0, MK_SYNC_ALL);
					vha->marker_needed = 0;
				पूर्ण

				/* Remap devices on Loop. */
				clear_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);

				अगर (IS_QLAFX00(vha->hw))
					qlafx00_configure_devices(vha);
				अन्यथा
					qla2x00_configure_loop(vha);

				रुको_समय--;
			पूर्ण जबतक (!atomic_पढ़ो(&vha->loop_करोwn_समयr) &&
				!(test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags))
				&& रुको_समय && (test_bit(LOOP_RESYNC_NEEDED,
				&vha->dpc_flags)));
		पूर्ण
	पूर्ण

	अगर (test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags))
		वापस (QLA_FUNCTION_FAILED);

	अगर (rval)
		ql_dbg(ql_dbg_disc, vha, 0x206c,
		    "%s *** FAILED ***.\n", __func__);

	वापस (rval);
पूर्ण

/*
* qla2x00_perक्रमm_loop_resync
* Description: This function will set the appropriate flags and call
*              qla2x00_loop_resync. If successful loop will be resynced
* Arguments : scsi_qla_host_t poपूर्णांकer
* returm    : Success or Failure
*/

पूर्णांक qla2x00_perक्रमm_loop_resync(scsi_qla_host_t *ha)
अणु
	पूर्णांक32_t rval = 0;

	अगर (!test_and_set_bit(LOOP_RESYNC_ACTIVE, &ha->dpc_flags)) अणु
		/*Configure the flags so that resync happens properly*/
		atomic_set(&ha->loop_करोwn_समयr, 0);
		अगर (!(ha->device_flags & DFLG_NO_CABLE)) अणु
			atomic_set(&ha->loop_state, LOOP_UP);
			set_bit(LOCAL_LOOP_UPDATE, &ha->dpc_flags);
			set_bit(REGISTER_FC4_NEEDED, &ha->dpc_flags);
			set_bit(LOOP_RESYNC_NEEDED, &ha->dpc_flags);

			rval = qla2x00_loop_resync(ha);
		पूर्ण अन्यथा
			atomic_set(&ha->loop_state, LOOP_DEAD);

		clear_bit(LOOP_RESYNC_ACTIVE, &ha->dpc_flags);
	पूर्ण

	वापस rval;
पूर्ण

व्योम
qla2x00_update_fcports(scsi_qla_host_t *base_vha)
अणु
	fc_port_t *fcport;
	काष्ठा scsi_qla_host *vha;
	काष्ठा qla_hw_data *ha = base_vha->hw;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ha->vport_slock, flags);
	/* Go with deferred removal of rport references. */
	list_क्रम_each_entry(vha, &base_vha->hw->vp_list, list) अणु
		atomic_inc(&vha->vref_count);
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (fcport->drport &&
			    atomic_पढ़ो(&fcport->state) != FCS_UNCONFIGURED) अणु
				spin_unlock_irqrestore(&ha->vport_slock, flags);
				qla2x00_rport_del(fcport);

				spin_lock_irqsave(&ha->vport_slock, flags);
			पूर्ण
		पूर्ण
		atomic_dec(&vha->vref_count);
		wake_up(&vha->vref_रुकोq);
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);
पूर्ण

/* Assumes idc_lock always held on entry */
व्योम
qla83xx_reset_ownership(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t drv_presence, drv_presence_mask;
	uपूर्णांक32_t dev_part_info1, dev_part_info2, class_type;
	uपूर्णांक32_t class_type_mask = 0x3;
	uपूर्णांक16_t fcoe_other_function = 0xffff, i;

	अगर (IS_QLA8044(ha)) अणु
		drv_presence = qla8044_rd_direct(vha,
		    QLA8044_CRB_DRV_ACTIVE_INDEX);
		dev_part_info1 = qla8044_rd_direct(vha,
		    QLA8044_CRB_DEV_PART_INFO_INDEX);
		dev_part_info2 = qla8044_rd_direct(vha,
		    QLA8044_CRB_DEV_PART_INFO2);
	पूर्ण अन्यथा अणु
		qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
		qla83xx_rd_reg(vha, QLA83XX_DEV_PARTINFO1, &dev_part_info1);
		qla83xx_rd_reg(vha, QLA83XX_DEV_PARTINFO2, &dev_part_info2);
	पूर्ण
	क्रम (i = 0; i < 8; i++) अणु
		class_type = ((dev_part_info1 >> (i * 4)) & class_type_mask);
		अगर ((class_type == QLA83XX_CLASS_TYPE_FCOE) &&
		    (i != ha->portnum)) अणु
			fcoe_other_function = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (fcoe_other_function == 0xffff) अणु
		क्रम (i = 0; i < 8; i++) अणु
			class_type = ((dev_part_info2 >> (i * 4)) &
			    class_type_mask);
			अगर ((class_type == QLA83XX_CLASS_TYPE_FCOE) &&
			    ((i + 8) != ha->portnum)) अणु
				fcoe_other_function = i + 8;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	/*
	 * Prepare drv-presence mask based on fcoe functions present.
	 * However consider only valid physical fcoe function numbers (0-15).
	 */
	drv_presence_mask = ~((1 << (ha->portnum)) |
			((fcoe_other_function == 0xffff) ?
			 0 : (1 << (fcoe_other_function))));

	/* We are the reset owner अगरf:
	 *    - No other protocol drivers present.
	 *    - This is the lowest among fcoe functions. */
	अगर (!(drv_presence & drv_presence_mask) &&
			(ha->portnum < fcoe_other_function)) अणु
		ql_dbg(ql_dbg_p3p, vha, 0xb07f,
		    "This host is Reset owner.\n");
		ha->flags.nic_core_reset_owner = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक
__qla83xx_set_drv_ack(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t drv_ack;

	rval = qla83xx_rd_reg(vha, QLA83XX_IDC_DRIVER_ACK, &drv_ack);
	अगर (rval == QLA_SUCCESS) अणु
		drv_ack |= (1 << ha->portnum);
		rval = qla83xx_wr_reg(vha, QLA83XX_IDC_DRIVER_ACK, drv_ack);
	पूर्ण

	वापस rval;
पूर्ण

अटल पूर्णांक
__qla83xx_clear_drv_ack(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t drv_ack;

	rval = qla83xx_rd_reg(vha, QLA83XX_IDC_DRIVER_ACK, &drv_ack);
	अगर (rval == QLA_SUCCESS) अणु
		drv_ack &= ~(1 << ha->portnum);
		rval = qla83xx_wr_reg(vha, QLA83XX_IDC_DRIVER_ACK, drv_ack);
	पूर्ण

	वापस rval;
पूर्ण

अटल स्थिर अक्षर *
qla83xx_dev_state_to_string(uपूर्णांक32_t dev_state)
अणु
	चयन (dev_state) अणु
	हाल QLA8XXX_DEV_COLD:
		वापस "COLD/RE-INIT";
	हाल QLA8XXX_DEV_INITIALIZING:
		वापस "INITIALIZING";
	हाल QLA8XXX_DEV_READY:
		वापस "READY";
	हाल QLA8XXX_DEV_NEED_RESET:
		वापस "NEED RESET";
	हाल QLA8XXX_DEV_NEED_QUIESCENT:
		वापस "NEED QUIESCENT";
	हाल QLA8XXX_DEV_FAILED:
		वापस "FAILED";
	हाल QLA8XXX_DEV_QUIESCENT:
		वापस "QUIESCENT";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

/* Assumes idc-lock always held on entry */
व्योम
qla83xx_idc_audit(scsi_qla_host_t *vha, पूर्णांक audit_type)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t idc_audit_reg = 0, duration_secs = 0;

	चयन (audit_type) अणु
	हाल IDC_AUDIT_TIMESTAMP:
		ha->idc_audit_ts = (jअगरfies_to_msecs(jअगरfies) / 1000);
		idc_audit_reg = (ha->portnum) |
		    (IDC_AUDIT_TIMESTAMP << 7) | (ha->idc_audit_ts << 8);
		qla83xx_wr_reg(vha, QLA83XX_IDC_AUDIT, idc_audit_reg);
		अवरोध;

	हाल IDC_AUDIT_COMPLETION:
		duration_secs = ((jअगरfies_to_msecs(jअगरfies) -
		    jअगरfies_to_msecs(ha->idc_audit_ts)) / 1000);
		idc_audit_reg = (ha->portnum) |
		    (IDC_AUDIT_COMPLETION << 7) | (duration_secs << 8);
		qla83xx_wr_reg(vha, QLA83XX_IDC_AUDIT, idc_audit_reg);
		अवरोध;

	शेष:
		ql_log(ql_log_warn, vha, 0xb078,
		    "Invalid audit type specified.\n");
		अवरोध;
	पूर्ण
पूर्ण

/* Assumes idc_lock always held on entry */
अटल पूर्णांक
qla83xx_initiating_reset(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t  idc_control, dev_state;

	__qla83xx_get_idc_control(vha, &idc_control);
	अगर ((idc_control & QLA83XX_IDC_RESET_DISABLED)) अणु
		ql_log(ql_log_info, vha, 0xb080,
		    "NIC Core reset has been disabled. idc-control=0x%x\n",
		    idc_control);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	/* Set NEED-RESET अगरf in READY state and we are the reset-owner */
	qla83xx_rd_reg(vha, QLA83XX_IDC_DEV_STATE, &dev_state);
	अगर (ha->flags.nic_core_reset_owner && dev_state == QLA8XXX_DEV_READY) अणु
		qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE,
		    QLA8XXX_DEV_NEED_RESET);
		ql_log(ql_log_info, vha, 0xb056, "HW State: NEED RESET.\n");
		qla83xx_idc_audit(vha, IDC_AUDIT_TIMESTAMP);
	पूर्ण अन्यथा अणु
		स्थिर अक्षर *state = qla83xx_dev_state_to_string(dev_state);

		ql_log(ql_log_info, vha, 0xb057, "HW State: %s.\n", state);

		/* SV: XXX: Is समयout required here? */
		/* Wait क्रम IDC state change READY -> NEED_RESET */
		जबतक (dev_state == QLA8XXX_DEV_READY) अणु
			qla83xx_idc_unlock(vha, 0);
			msleep(200);
			qla83xx_idc_lock(vha, 0);
			qla83xx_rd_reg(vha, QLA83XX_IDC_DEV_STATE, &dev_state);
		पूर्ण
	पूर्ण

	/* Send IDC ack by writing to drv-ack रेजिस्टर */
	__qla83xx_set_drv_ack(vha);

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
__qla83xx_set_idc_control(scsi_qla_host_t *vha, uपूर्णांक32_t idc_control)
अणु
	वापस qla83xx_wr_reg(vha, QLA83XX_IDC_CONTROL, idc_control);
पूर्ण

पूर्णांक
__qla83xx_get_idc_control(scsi_qla_host_t *vha, uपूर्णांक32_t *idc_control)
अणु
	वापस qla83xx_rd_reg(vha, QLA83XX_IDC_CONTROL, idc_control);
पूर्ण

अटल पूर्णांक
qla83xx_check_driver_presence(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t drv_presence = 0;
	काष्ठा qla_hw_data *ha = vha->hw;

	qla83xx_rd_reg(vha, QLA83XX_IDC_DRV_PRESENCE, &drv_presence);
	अगर (drv_presence & (1 << ha->portnum))
		वापस QLA_SUCCESS;
	अन्यथा
		वापस QLA_TEST_FAILED;
पूर्ण

पूर्णांक
qla83xx_nic_core_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_p3p, vha, 0xb058,
	    "Entered  %s().\n", __func__);

	अगर (vha->device_flags & DFLG_DEV_FAILED) अणु
		ql_log(ql_log_warn, vha, 0xb059,
		    "Device in unrecoverable FAILED state.\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	qla83xx_idc_lock(vha, 0);

	अगर (qla83xx_check_driver_presence(vha) != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0xb05a,
		    "Function=0x%x has been removed from IDC participation.\n",
		    ha->portnum);
		rval = QLA_FUNCTION_FAILED;
		जाओ निकास;
	पूर्ण

	qla83xx_reset_ownership(vha);

	rval = qla83xx_initiating_reset(vha);

	/*
	 * Perक्रमm reset अगर we are the reset-owner,
	 * अन्यथा रुको till IDC state changes to READY/FAILED.
	 */
	अगर (rval == QLA_SUCCESS) अणु
		rval = qla83xx_idc_state_handler(vha);

		अगर (rval == QLA_SUCCESS)
			ha->flags.nic_core_hung = 0;
		__qla83xx_clear_drv_ack(vha);
	पूर्ण

निकास:
	qla83xx_idc_unlock(vha, 0);

	ql_dbg(ql_dbg_p3p, vha, 0xb05b, "Exiting %s.\n", __func__);

	वापस rval;
पूर्ण

पूर्णांक
qla2xxx_mctp_dump(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (!IS_MCTP_CAPABLE(ha)) अणु
		/* This message can be हटाओd from the final version */
		ql_log(ql_log_info, vha, 0x506d,
		    "This board is not MCTP capable\n");
		वापस rval;
	पूर्ण

	अगर (!ha->mctp_dump) अणु
		ha->mctp_dump = dma_alloc_coherent(&ha->pdev->dev,
		    MCTP_DUMP_SIZE, &ha->mctp_dump_dma, GFP_KERNEL);

		अगर (!ha->mctp_dump) अणु
			ql_log(ql_log_warn, vha, 0x506e,
			    "Failed to allocate memory for mctp dump\n");
			वापस rval;
		पूर्ण
	पूर्ण

#घोषणा MCTP_DUMP_STR_ADDR	0x00000000
	rval = qla2x00_dump_mctp_data(vha, ha->mctp_dump_dma,
	    MCTP_DUMP_STR_ADDR, MCTP_DUMP_SIZE/4);
	अगर (rval != QLA_SUCCESS) अणु
		ql_log(ql_log_warn, vha, 0x506f,
		    "Failed to capture mctp dump\n");
	पूर्ण अन्यथा अणु
		ql_log(ql_log_info, vha, 0x5070,
		    "Mctp dump capture for host (%ld/%p).\n",
		    vha->host_no, ha->mctp_dump);
		ha->mctp_dumped = 1;
	पूर्ण

	अगर (!ha->flags.nic_core_reset_hdlr_active && !ha->portnum) अणु
		ha->flags.nic_core_reset_hdlr_active = 1;
		rval = qla83xx_restart_nic_firmware(vha);
		अगर (rval)
			/* NIC Core reset failed. */
			ql_log(ql_log_warn, vha, 0x5071,
			    "Failed to restart nic firmware\n");
		अन्यथा
			ql_dbg(ql_dbg_p3p, vha, 0xb084,
			    "Restarted NIC firmware successfully.\n");
		ha->flags.nic_core_reset_hdlr_active = 0;
	पूर्ण

	वापस rval;

पूर्ण

/*
* qla2x00_quiesce_io
* Description: This function will block the new I/Os
*              Its not पातing any I/Os as context
*              is not destroyed during quiescence
* Arguments: scsi_qla_host_t
* वापस   : व्योम
*/
व्योम
qla2x00_quiesce_io(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *vp;

	ql_dbg(ql_dbg_dpc, vha, 0x401d,
	    "Quiescing I/O - ha=%p.\n", ha);

	atomic_set(&ha->loop_करोwn_समयr, LOOP_DOWN_TIME);
	अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
		atomic_set(&vha->loop_state, LOOP_DOWN);
		qla2x00_mark_all_devices_lost(vha);
		list_क्रम_each_entry(vp, &ha->vp_list, list)
			qla2x00_mark_all_devices_lost(vp);
	पूर्ण अन्यथा अणु
		अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr))
			atomic_set(&vha->loop_करोwn_समयr,
					LOOP_DOWN_TIME);
	पूर्ण
	/* Wait क्रम pending cmds to complete */
	WARN_ON_ONCE(qla2x00_eh_रुको_क्रम_pending_commands(vha, 0, 0, WAIT_HOST)
		     != QLA_SUCCESS);
पूर्ण

व्योम
qla2x00_पात_isp_cleanup(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *vp;
	अचिन्हित दीर्घ flags;
	fc_port_t *fcport;
	u16 i;

	/* For ISP82XX, driver रुकोs क्रम completion of the commands.
	 * online flag should be set.
	 */
	अगर (!(IS_P3P_TYPE(ha)))
		vha->flags.online = 0;
	ha->flags.chip_reset_करोne = 0;
	clear_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	vha->qla_stats.total_isp_पातs++;

	ql_log(ql_log_info, vha, 0x00af,
	    "Performing ISP error recovery - ha=%p.\n", ha);

	ha->flags.purge_mbox = 1;
	/* For ISP82XX, reset_chip is just disabling पूर्णांकerrupts.
	 * Driver रुकोs क्रम the completion of the commands.
	 * the पूर्णांकerrupts need to be enabled.
	 */
	अगर (!(IS_P3P_TYPE(ha)))
		ha->isp_ops->reset_chip(vha);

	ha->link_data_rate = PORT_SPEED_UNKNOWN;
	SAVE_TOPO(ha);
	ha->flags.rida_fmt2 = 0;
	ha->flags.n2n_ae = 0;
	ha->flags.lip_ae = 0;
	ha->current_topology = 0;
	QLA_FW_STOPPED(ha);
	ha->flags.fw_init_करोne = 0;
	ha->chip_reset++;
	ha->base_qpair->chip_reset = ha->chip_reset;
	क्रम (i = 0; i < ha->max_qpairs; i++) अणु
		अगर (ha->queue_pair_map[i])
			ha->queue_pair_map[i]->chip_reset =
				ha->base_qpair->chip_reset;
	पूर्ण

	/* purge MBox commands */
	अगर (atomic_पढ़ो(&ha->num_pend_mbx_stage3)) अणु
		clear_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags);
		complete(&ha->mbx_पूर्णांकr_comp);
	पूर्ण

	i = 0;
	जबतक (atomic_पढ़ो(&ha->num_pend_mbx_stage3) ||
	    atomic_पढ़ो(&ha->num_pend_mbx_stage2) ||
	    atomic_पढ़ो(&ha->num_pend_mbx_stage1)) अणु
		msleep(20);
		i++;
		अगर (i > 50)
			अवरोध;
	पूर्ण
	ha->flags.purge_mbox = 0;

	atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
	अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
		atomic_set(&vha->loop_state, LOOP_DOWN);
		qla2x00_mark_all_devices_lost(vha);

		spin_lock_irqsave(&ha->vport_slock, flags);
		list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
			atomic_inc(&vp->vref_count);
			spin_unlock_irqrestore(&ha->vport_slock, flags);

			qla2x00_mark_all_devices_lost(vp);

			spin_lock_irqsave(&ha->vport_slock, flags);
			atomic_dec(&vp->vref_count);
		पूर्ण
		spin_unlock_irqrestore(&ha->vport_slock, flags);
	पूर्ण अन्यथा अणु
		अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr))
			atomic_set(&vha->loop_करोwn_समयr,
			    LOOP_DOWN_TIME);
	पूर्ण

	/* Clear all async request states across all VPs. */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		fcport->flags &= ~(FCF_LOGIN_NEEDED | FCF_ASYNC_SENT);
		fcport->scan_state = 0;
	पूर्ण
	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
		atomic_inc(&vp->vref_count);
		spin_unlock_irqrestore(&ha->vport_slock, flags);

		list_क्रम_each_entry(fcport, &vp->vp_fcports, list)
			fcport->flags &= ~(FCF_LOGIN_NEEDED | FCF_ASYNC_SENT);

		spin_lock_irqsave(&ha->vport_slock, flags);
		atomic_dec(&vp->vref_count);
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	/* Make sure क्रम ISP 82XX IO DMA is complete */
	अगर (IS_P3P_TYPE(ha)) अणु
		qla82xx_chip_reset_cleanup(vha);
		ql_log(ql_log_info, vha, 0x00b4,
		       "Done chip reset cleanup.\n");

		/* Done रुकोing क्रम pending commands. Reset online flag */
		vha->flags.online = 0;
	पूर्ण

	/* Requeue all commands in outstanding command list. */
	qla2x00_पात_all_cmds(vha, DID_RESET << 16);
	/* memory barrier */
	wmb();
पूर्ण

/*
*  qla2x00_पात_isp
*      Resets ISP and पातs all outstanding commands.
*
* Input:
*      ha           = adapter block poपूर्णांकer.
*
* Returns:
*      0 = success
*/
पूर्णांक
qla2x00_पात_isp(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	uपूर्णांक8_t        status = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *vp;
	काष्ठा req_que *req = ha->req_q_map[0];
	अचिन्हित दीर्घ flags;

	अगर (vha->flags.online) अणु
		qla2x00_पात_isp_cleanup(vha);

		अगर (vha->hw->flags.port_isolated)
			वापस status;

		अगर (qla2x00_isp_reg_stat(ha)) अणु
			ql_log(ql_log_info, vha, 0x803f,
			       "ISP Abort - ISP reg disconnect, exiting.\n");
			वापस status;
		पूर्ण

		अगर (test_and_clear_bit(ISP_ABORT_TO_ROM, &vha->dpc_flags)) अणु
			ha->flags.chip_reset_करोne = 1;
			vha->flags.online = 1;
			status = 0;
			clear_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
			वापस status;
		पूर्ण

		अगर (IS_QLA8031(ha)) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb05c,
			    "Clearing fcoe driver presence.\n");
			अगर (qla83xx_clear_drv_presence(vha) != QLA_SUCCESS)
				ql_dbg(ql_dbg_p3p, vha, 0xb073,
				    "Error while clearing DRV-Presence.\n");
		पूर्ण

		अगर (unlikely(pci_channel_offline(ha->pdev) &&
		    ha->flags.pci_channel_io_perm_failure)) अणु
			clear_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
			status = 0;
			वापस status;
		पूर्ण

		चयन (vha->qlini_mode) अणु
		हाल QLA2XXX_INI_MODE_DISABLED:
			अगर (!qla_tgt_mode_enabled(vha))
				वापस 0;
			अवरोध;
		हाल QLA2XXX_INI_MODE_DUAL:
			अगर (!qla_dual_mode_enabled(vha))
				वापस 0;
			अवरोध;
		हाल QLA2XXX_INI_MODE_ENABLED:
		शेष:
			अवरोध;
		पूर्ण

		ha->isp_ops->get_flash_version(vha, req->ring);

		अगर (qla2x00_isp_reg_stat(ha)) अणु
			ql_log(ql_log_info, vha, 0x803f,
			       "ISP Abort - ISP reg disconnect pre nvram config, exiting.\n");
			वापस status;
		पूर्ण
		ha->isp_ops->nvram_config(vha);

		अगर (qla2x00_isp_reg_stat(ha)) अणु
			ql_log(ql_log_info, vha, 0x803f,
			       "ISP Abort - ISP reg disconnect post nvmram config, exiting.\n");
			वापस status;
		पूर्ण
		अगर (!qla2x00_restart_isp(vha)) अणु
			clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);

			अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr)) अणु
				/*
				 * Issue marker command only when we are going
				 * to start the I/O .
				 */
				vha->marker_needed = 1;
			पूर्ण

			vha->flags.online = 1;

			ha->isp_ops->enable_पूर्णांकrs(ha);

			ha->isp_पात_cnt = 0;
			clear_bit(ISP_ABORT_RETRY, &vha->dpc_flags);

			अगर (IS_QLA81XX(ha) || IS_QLA8031(ha))
				qla2x00_get_fw_version(vha);
			अगर (ha->fce) अणु
				ha->flags.fce_enabled = 1;
				स_रखो(ha->fce, 0,
				    fce_calc_size(ha->fce_bufs));
				rval = qla2x00_enable_fce_trace(vha,
				    ha->fce_dma, ha->fce_bufs, ha->fce_mb,
				    &ha->fce_bufs);
				अगर (rval) अणु
					ql_log(ql_log_warn, vha, 0x8033,
					    "Unable to reinitialize FCE "
					    "(%d).\n", rval);
					ha->flags.fce_enabled = 0;
				पूर्ण
			पूर्ण

			अगर (ha->eft) अणु
				स_रखो(ha->eft, 0, EFT_SIZE);
				rval = qla2x00_enable_eft_trace(vha,
				    ha->eft_dma, EFT_NUM_BUFFERS);
				अगर (rval) अणु
					ql_log(ql_log_warn, vha, 0x8034,
					    "Unable to reinitialize EFT "
					    "(%d).\n", rval);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु	/* failed the ISP पात */
			vha->flags.online = 1;
			अगर (test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु
				अगर (ha->isp_पात_cnt == 0) अणु
					ql_log(ql_log_fatal, vha, 0x8035,
					    "ISP error recover failed - "
					    "board disabled.\n");
					/*
					 * The next call disables the board
					 * completely.
					 */
					qla2x00_पात_isp_cleanup(vha);
					vha->flags.online = 0;
					clear_bit(ISP_ABORT_RETRY,
					    &vha->dpc_flags);
					status = 0;
				पूर्ण अन्यथा अणु /* schedule another ISP पात */
					ha->isp_पात_cnt--;
					ql_dbg(ql_dbg_taskm, vha, 0x8020,
					    "ISP abort - retry remaining %d.\n",
					    ha->isp_पात_cnt);
					status = 1;
				पूर्ण
			पूर्ण अन्यथा अणु
				ha->isp_पात_cnt = MAX_RETRIES_OF_ISP_ABORT;
				ql_dbg(ql_dbg_taskm, vha, 0x8021,
				    "ISP error recovery - retrying (%d) "
				    "more times.\n", ha->isp_पात_cnt);
				set_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
				status = 1;
			पूर्ण
		पूर्ण

	पूर्ण

	अगर (vha->hw->flags.port_isolated) अणु
		qla2x00_पात_isp_cleanup(vha);
		वापस status;
	पूर्ण

	अगर (!status) अणु
		ql_dbg(ql_dbg_taskm, vha, 0x8022, "%s succeeded.\n", __func__);
		qla2x00_configure_hba(vha);
		spin_lock_irqsave(&ha->vport_slock, flags);
		list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
			अगर (vp->vp_idx) अणु
				atomic_inc(&vp->vref_count);
				spin_unlock_irqrestore(&ha->vport_slock, flags);

				qla2x00_vp_पात_isp(vp);

				spin_lock_irqsave(&ha->vport_slock, flags);
				atomic_dec(&vp->vref_count);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&ha->vport_slock, flags);

		अगर (IS_QLA8031(ha)) अणु
			ql_dbg(ql_dbg_p3p, vha, 0xb05d,
			    "Setting back fcoe driver presence.\n");
			अगर (qla83xx_set_drv_presence(vha) != QLA_SUCCESS)
				ql_dbg(ql_dbg_p3p, vha, 0xb074,
				    "Error while setting DRV-Presence.\n");
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_log(ql_log_warn, vha, 0x8023, "%s **** FAILED ****.\n",
		       __func__);
	पूर्ण

	वापस(status);
पूर्ण

/*
*  qla2x00_restart_isp
*      restarts the ISP after a reset
*
* Input:
*      ha = adapter block poपूर्णांकer.
*
* Returns:
*      0 = success
*/
अटल पूर्णांक
qla2x00_restart_isp(scsi_qla_host_t *vha)
अणु
	पूर्णांक status;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* If firmware needs to be loaded */
	अगर (qla2x00_isp_firmware(vha)) अणु
		vha->flags.online = 0;
		status = ha->isp_ops->chip_diag(vha);
		अगर (status)
			वापस status;
		status = qla2x00_setup_chip(vha);
		अगर (status)
			वापस status;
	पूर्ण

	status = qla2x00_init_rings(vha);
	अगर (status)
		वापस status;

	clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);
	ha->flags.chip_reset_करोne = 1;

	/* Initialize the queues in use */
	qla25xx_init_queues(ha);

	status = qla2x00_fw_पढ़ोy(vha);
	अगर (status) अणु
		/* अगर no cable then assume it's good */
		वापस vha->device_flags & DFLG_NO_CABLE ? 0 : status;
	पूर्ण

	/* Issue a marker after FW becomes पढ़ोy. */
	qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL);
	set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
qla25xx_init_queues(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा rsp_que *rsp = शून्य;
	काष्ठा req_que *req = शून्य;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);
	पूर्णांक ret = -1;
	पूर्णांक i;

	क्रम (i = 1; i < ha->max_rsp_queues; i++) अणु
		rsp = ha->rsp_q_map[i];
		अगर (rsp && test_bit(i, ha->rsp_qid_map)) अणु
			rsp->options &= ~BIT_0;
			ret = qla25xx_init_rsp_que(base_vha, rsp);
			अगर (ret != QLA_SUCCESS)
				ql_dbg(ql_dbg_init, base_vha, 0x00ff,
				    "%s Rsp que: %d init failed.\n",
				    __func__, rsp->id);
			अन्यथा
				ql_dbg(ql_dbg_init, base_vha, 0x0100,
				    "%s Rsp que: %d inited.\n",
				    __func__, rsp->id);
		पूर्ण
	पूर्ण
	क्रम (i = 1; i < ha->max_req_queues; i++) अणु
		req = ha->req_q_map[i];
		अगर (req && test_bit(i, ha->req_qid_map)) अणु
			/* Clear outstanding commands array. */
			req->options &= ~BIT_0;
			ret = qla25xx_init_req_que(base_vha, req);
			अगर (ret != QLA_SUCCESS)
				ql_dbg(ql_dbg_init, base_vha, 0x0101,
				    "%s Req que: %d init failed.\n",
				    __func__, req->id);
			अन्यथा
				ql_dbg(ql_dbg_init, base_vha, 0x0102,
				    "%s Req que: %d inited.\n",
				    __func__, req->id);
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
* qla2x00_reset_adapter
*      Reset adapter.
*
* Input:
*      ha = adapter block poपूर्णांकer.
*/
पूर्णांक
qla2x00_reset_adapter(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	vha->flags.online = 0;
	ha->isp_ops->disable_पूर्णांकrs(ha);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	wrt_reg_word(&reg->hccr, HCCR_RESET_RISC);
	rd_reg_word(&reg->hccr);			/* PCI Posting. */
	wrt_reg_word(&reg->hccr, HCCR_RELEASE_RISC);
	rd_reg_word(&reg->hccr);			/* PCI Posting. */
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla24xx_reset_adapter(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	अगर (IS_P3P_TYPE(ha))
		वापस QLA_SUCCESS;

	vha->flags.online = 0;
	ha->isp_ops->disable_पूर्णांकrs(ha);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	wrt_reg_dword(&reg->hccr, HCCRX_SET_RISC_RESET);
	rd_reg_dword(&reg->hccr);
	wrt_reg_dword(&reg->hccr, HCCRX_REL_RISC_PAUSE);
	rd_reg_dword(&reg->hccr);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (IS_NOPOLLING_TYPE(ha))
		ha->isp_ops->enable_पूर्णांकrs(ha);

	वापस QLA_SUCCESS;
पूर्ण

/* On sparc प्रणालीs, obtain port and node WWN from firmware
 * properties.
 */
अटल व्योम qla24xx_nvram_wwn_from_ofw(scsi_qla_host_t *vha,
	काष्ठा nvram_24xx *nv)
अणु
#अगर_घोषित CONFIG_SPARC
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा pci_dev *pdev = ha->pdev;
	काष्ठा device_node *dp = pci_device_to_OF_node(pdev);
	स्थिर u8 *val;
	पूर्णांक len;

	val = of_get_property(dp, "port-wwn", &len);
	अगर (val && len >= WWN_SIZE)
		स_नकल(nv->port_name, val, WWN_SIZE);

	val = of_get_property(dp, "node-wwn", &len);
	अगर (val && len >= WWN_SIZE)
		स_नकल(nv->node_name, val, WWN_SIZE);
#पूर्ण_अगर
पूर्ण

पूर्णांक
qla24xx_nvram_config(scsi_qla_host_t *vha)
अणु
	पूर्णांक   rval;
	काष्ठा init_cb_24xx *icb;
	काष्ठा nvram_24xx *nv;
	__le32 *dptr;
	uपूर्णांक8_t  *dptr1, *dptr2;
	uपूर्णांक32_t chksum;
	uपूर्णांक16_t cnt;
	काष्ठा qla_hw_data *ha = vha->hw;

	rval = QLA_SUCCESS;
	icb = (काष्ठा init_cb_24xx *)ha->init_cb;
	nv = ha->nvram;

	/* Determine NVRAM starting address. */
	अगर (ha->port_no == 0) अणु
		ha->nvram_base = FA_NVRAM_FUNC0_ADDR;
		ha->vpd_base = FA_NVRAM_VPD0_ADDR;
	पूर्ण अन्यथा अणु
		ha->nvram_base = FA_NVRAM_FUNC1_ADDR;
		ha->vpd_base = FA_NVRAM_VPD1_ADDR;
	पूर्ण

	ha->nvram_size = माप(*nv);
	ha->vpd_size = FA_NVRAM_VPD_SIZE;

	/* Get VPD data पूर्णांकo cache */
	ha->vpd = ha->nvram + VPD_OFFSET;
	ha->isp_ops->पढ़ो_nvram(vha, ha->vpd,
	    ha->nvram_base - FA_NVRAM_FUNC0_ADDR, FA_NVRAM_VPD_SIZE * 4);

	/* Get NVRAM data पूर्णांकo cache and calculate checksum. */
	dptr = (__क्रमce __le32 *)nv;
	ha->isp_ops->पढ़ो_nvram(vha, dptr, ha->nvram_base, ha->nvram_size);
	क्रम (cnt = 0, chksum = 0; cnt < ha->nvram_size >> 2; cnt++, dptr++)
		chksum += le32_to_cpu(*dptr);

	ql_dbg(ql_dbg_init + ql_dbg_buffer, vha, 0x006a,
	    "Contents of NVRAM\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x010d,
	    nv, ha->nvram_size);

	/* Bad NVRAM data, set शेषs parameters. */
	अगर (chksum || स_भेद("ISP ", nv->id, माप(nv->id)) ||
	    le16_to_cpu(nv->nvram_version) < ICB_VERSION) अणु
		/* Reset NVRAM data. */
		ql_log(ql_log_warn, vha, 0x006b,
		    "Inconsistent NVRAM checksum=%#x id=%.4s version=%#x.\n",
		    chksum, nv->id, nv->nvram_version);
		ql_dump_buffer(ql_dbg_init, vha, 0x006b, nv, माप(*nv));
		ql_log(ql_log_warn, vha, 0x006c,
		    "Falling back to functioning (yet invalid -- WWPN) "
		    "defaults.\n");

		/*
		 * Set शेष initialization control block.
		 */
		स_रखो(nv, 0, ha->nvram_size);
		nv->nvram_version = cpu_to_le16(ICB_VERSION);
		nv->version = cpu_to_le16(ICB_VERSION);
		nv->frame_payload_size = cpu_to_le16(2048);
		nv->execution_throttle = cpu_to_le16(0xFFFF);
		nv->exchange_count = cpu_to_le16(0);
		nv->hard_address = cpu_to_le16(124);
		nv->port_name[0] = 0x21;
		nv->port_name[1] = 0x00 + ha->port_no + 1;
		nv->port_name[2] = 0x00;
		nv->port_name[3] = 0xe0;
		nv->port_name[4] = 0x8b;
		nv->port_name[5] = 0x1c;
		nv->port_name[6] = 0x55;
		nv->port_name[7] = 0x86;
		nv->node_name[0] = 0x20;
		nv->node_name[1] = 0x00;
		nv->node_name[2] = 0x00;
		nv->node_name[3] = 0xe0;
		nv->node_name[4] = 0x8b;
		nv->node_name[5] = 0x1c;
		nv->node_name[6] = 0x55;
		nv->node_name[7] = 0x86;
		qla24xx_nvram_wwn_from_ofw(vha, nv);
		nv->login_retry_count = cpu_to_le16(8);
		nv->पूर्णांकerrupt_delay_समयr = cpu_to_le16(0);
		nv->login_समयout = cpu_to_le16(0);
		nv->firmware_options_1 =
		    cpu_to_le32(BIT_14|BIT_13|BIT_2|BIT_1);
		nv->firmware_options_2 = cpu_to_le32(2 << 4);
		nv->firmware_options_2 |= cpu_to_le32(BIT_12);
		nv->firmware_options_3 = cpu_to_le32(2 << 13);
		nv->host_p = cpu_to_le32(BIT_11|BIT_10);
		nv->efi_parameters = cpu_to_le32(0);
		nv->reset_delay = 5;
		nv->max_luns_per_target = cpu_to_le16(128);
		nv->port_करोwn_retry_count = cpu_to_le16(30);
		nv->link_करोwn_समयout = cpu_to_le16(30);

		rval = 1;
	पूर्ण

	अगर (qla_tgt_mode_enabled(vha)) अणु
		/* Don't enable full login after initial LIP */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_13);
		/* Don't enable LIP full login क्रम initiator */
		nv->host_p &= cpu_to_le32(~BIT_10);
	पूर्ण

	qlt_24xx_config_nvram_stage1(vha, nv);

	/* Reset Initialization control block */
	स_रखो(icb, 0, ha->init_cb_size);

	/* Copy 1st segment. */
	dptr1 = (uपूर्णांक8_t *)icb;
	dptr2 = (uपूर्णांक8_t *)&nv->version;
	cnt = (uपूर्णांक8_t *)&icb->response_q_inpoपूर्णांकer - (uपूर्णांक8_t *)&icb->version;
	जबतक (cnt--)
		*dptr1++ = *dptr2++;

	icb->login_retry_count = nv->login_retry_count;
	icb->link_करोwn_on_nos = nv->link_करोwn_on_nos;

	/* Copy 2nd segment. */
	dptr1 = (uपूर्णांक8_t *)&icb->पूर्णांकerrupt_delay_समयr;
	dptr2 = (uपूर्णांक8_t *)&nv->पूर्णांकerrupt_delay_समयr;
	cnt = (uपूर्णांक8_t *)&icb->reserved_3 -
	    (uपूर्णांक8_t *)&icb->पूर्णांकerrupt_delay_समयr;
	जबतक (cnt--)
		*dptr1++ = *dptr2++;
	ha->frame_payload_size = le16_to_cpu(icb->frame_payload_size);
	/*
	 * Setup driver NVRAM options.
	 */
	qla2x00_set_model_info(vha, nv->model_name, माप(nv->model_name),
	    "QLA2462");

	qlt_24xx_config_nvram_stage2(vha, icb);

	अगर (nv->host_p & cpu_to_le32(BIT_15)) अणु
		/* Use alternate WWN? */
		स_नकल(icb->node_name, nv->alternate_node_name, WWN_SIZE);
		स_नकल(icb->port_name, nv->alternate_port_name, WWN_SIZE);
	पूर्ण

	/* Prepare nodename */
	अगर ((icb->firmware_options_1 & cpu_to_le32(BIT_14)) == 0) अणु
		/*
		 * Firmware will apply the following mask अगर the nodename was
		 * not provided.
		 */
		स_नकल(icb->node_name, icb->port_name, WWN_SIZE);
		icb->node_name[0] &= 0xF0;
	पूर्ण

	/* Set host adapter parameters. */
	ha->flags.disable_risc_code_load = 0;
	ha->flags.enable_lip_reset = 0;
	ha->flags.enable_lip_full_login =
	    le32_to_cpu(nv->host_p) & BIT_10 ? 1 : 0;
	ha->flags.enable_target_reset =
	    le32_to_cpu(nv->host_p) & BIT_11 ? 1 : 0;
	ha->flags.enable_led_scheme = 0;
	ha->flags.disable_serdes = le32_to_cpu(nv->host_p) & BIT_5 ? 1 : 0;

	ha->operating_mode = (le32_to_cpu(icb->firmware_options_2) &
	    (BIT_6 | BIT_5 | BIT_4)) >> 4;

	स_नकल(ha->fw_seriallink_options24, nv->seriallink_options,
	    माप(ha->fw_seriallink_options24));

	/* save HBA serial number */
	ha->serial0 = icb->port_name[5];
	ha->serial1 = icb->port_name[6];
	ha->serial2 = icb->port_name[7];
	स_नकल(vha->node_name, icb->node_name, WWN_SIZE);
	स_नकल(vha->port_name, icb->port_name, WWN_SIZE);

	icb->execution_throttle = cpu_to_le16(0xFFFF);

	ha->retry_count = le16_to_cpu(nv->login_retry_count);

	/* Set minimum login_समयout to 4 seconds. */
	अगर (le16_to_cpu(nv->login_समयout) < ql2xlogपूर्णांकimeout)
		nv->login_समयout = cpu_to_le16(ql2xlogपूर्णांकimeout);
	अगर (le16_to_cpu(nv->login_समयout) < 4)
		nv->login_समयout = cpu_to_le16(4);
	ha->login_समयout = le16_to_cpu(nv->login_समयout);

	/* Set minimum RATOV to 100 tenths of a second. */
	ha->r_a_tov = 100;

	ha->loop_reset_delay = nv->reset_delay;

	/* Link Down Timeout = 0:
	 *
	 * 	When Port Down समयr expires we will start वापसing
	 *	I/O's to OS with "DID_NO_CONNECT".
	 *
	 * Link Down Timeout != 0:
	 *
	 *	 The driver रुकोs क्रम the link to come up after link करोwn
	 *	 beक्रमe वापसing I/Os to OS with "DID_NO_CONNECT".
	 */
	अगर (le16_to_cpu(nv->link_करोwn_समयout) == 0) अणु
		ha->loop_करोwn_पात_समय =
		    (LOOP_DOWN_TIME - LOOP_DOWN_TIMEOUT);
	पूर्ण अन्यथा अणु
		ha->link_करोwn_समयout =	le16_to_cpu(nv->link_करोwn_समयout);
		ha->loop_करोwn_पात_समय =
		    (LOOP_DOWN_TIME - ha->link_करोwn_समयout);
	पूर्ण

	/* Need enough समय to try and get the port back. */
	ha->port_करोwn_retry_count = le16_to_cpu(nv->port_करोwn_retry_count);
	अगर (qlport_करोwn_retry)
		ha->port_करोwn_retry_count = qlport_करोwn_retry;

	/* Set login_retry_count */
	ha->login_retry_count  = le16_to_cpu(nv->login_retry_count);
	अगर (ha->port_करोwn_retry_count ==
	    le16_to_cpu(nv->port_करोwn_retry_count) &&
	    ha->port_करोwn_retry_count > 3)
		ha->login_retry_count = ha->port_करोwn_retry_count;
	अन्यथा अगर (ha->port_करोwn_retry_count > (पूर्णांक)ha->login_retry_count)
		ha->login_retry_count = ha->port_करोwn_retry_count;
	अगर (ql2xloginretrycount)
		ha->login_retry_count = ql2xloginretrycount;

	/* N2N: driver will initiate Login instead of FW */
	icb->firmware_options_3 |= cpu_to_le32(BIT_8);

	/* Enable ZIO. */
	अगर (!vha->flags.init_करोne) अणु
		ha->zio_mode = le32_to_cpu(icb->firmware_options_2) &
		    (BIT_3 | BIT_2 | BIT_1 | BIT_0);
		ha->zio_समयr = le16_to_cpu(icb->पूर्णांकerrupt_delay_समयr) ?
		    le16_to_cpu(icb->पूर्णांकerrupt_delay_समयr) : 2;
	पूर्ण
	icb->firmware_options_2 &= cpu_to_le32(
	    ~(BIT_3 | BIT_2 | BIT_1 | BIT_0));
	अगर (ha->zio_mode != QLA_ZIO_DISABLED) अणु
		ha->zio_mode = QLA_ZIO_MODE_6;

		ql_log(ql_log_info, vha, 0x006f,
		    "ZIO mode %d enabled; timer delay (%d us).\n",
		    ha->zio_mode, ha->zio_समयr * 100);

		icb->firmware_options_2 |= cpu_to_le32(
		    (uपूर्णांक32_t)ha->zio_mode);
		icb->पूर्णांकerrupt_delay_समयr = cpu_to_le16(ha->zio_समयr);
	पूर्ण

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0070,
		    "NVRAM configuration failed.\n");
	पूर्ण
	वापस (rval);
पूर्ण

अटल व्योम
qla27xx_prपूर्णांक_image(काष्ठा scsi_qla_host *vha, अक्षर *name,
    काष्ठा qla27xx_image_status *image_status)
अणु
	ql_dbg(ql_dbg_init, vha, 0x018b,
	    "%s %s: mask=%#02x gen=%#04x ver=%u.%u map=%#01x sum=%#08x sig=%#08x\n",
	    name, "status",
	    image_status->image_status_mask,
	    le16_to_cpu(image_status->generation),
	    image_status->ver_major,
	    image_status->ver_minor,
	    image_status->biपंचांगap,
	    le32_to_cpu(image_status->checksum),
	    le32_to_cpu(image_status->signature));
पूर्ण

अटल bool
qla28xx_check_aux_image_status_signature(
    काष्ठा qla27xx_image_status *image_status)
अणु
	uदीर्घ signature = le32_to_cpu(image_status->signature);

	वापस signature != QLA28XX_AUX_IMG_STATUS_SIGN;
पूर्ण

अटल bool
qla27xx_check_image_status_signature(काष्ठा qla27xx_image_status *image_status)
अणु
	uदीर्घ signature = le32_to_cpu(image_status->signature);

	वापस
	    signature != QLA27XX_IMG_STATUS_SIGN &&
	    signature != QLA28XX_IMG_STATUS_SIGN;
पूर्ण

अटल uदीर्घ
qla27xx_image_status_checksum(काष्ठा qla27xx_image_status *image_status)
अणु
	__le32 *p = (__क्रमce __le32 *)image_status;
	uपूर्णांक n = माप(*image_status) / माप(*p);
	uपूर्णांक32_t sum = 0;

	क्रम ( ; n--; p++)
		sum += le32_to_cpup(p);

	वापस sum;
पूर्ण

अटल अंतरभूत uपूर्णांक
qla28xx_component_biपंचांगask(काष्ठा qla27xx_image_status *aux, uपूर्णांक biपंचांगask)
अणु
	वापस aux->biपंचांगap & biपंचांगask ?
	    QLA27XX_SECONDARY_IMAGE : QLA27XX_PRIMARY_IMAGE;
पूर्ण

अटल व्योम
qla28xx_component_status(
    काष्ठा active_regions *active_regions, काष्ठा qla27xx_image_status *aux)
अणु
	active_regions->aux.board_config =
	    qla28xx_component_biपंचांगask(aux, QLA28XX_AUX_IMG_BOARD_CONFIG);

	active_regions->aux.vpd_nvram =
	    qla28xx_component_biपंचांगask(aux, QLA28XX_AUX_IMG_VPD_NVRAM);

	active_regions->aux.npiv_config_0_1 =
	    qla28xx_component_biपंचांगask(aux, QLA28XX_AUX_IMG_NPIV_CONFIG_0_1);

	active_regions->aux.npiv_config_2_3 =
	    qla28xx_component_biपंचांगask(aux, QLA28XX_AUX_IMG_NPIV_CONFIG_2_3);
पूर्ण

अटल पूर्णांक
qla27xx_compare_image_generation(
    काष्ठा qla27xx_image_status *pri_image_status,
    काष्ठा qla27xx_image_status *sec_image_status)
अणु
	/* calculate generation delta as uपूर्णांक16 (this accounts क्रम wrap) */
	पूर्णांक16_t delta =
	    le16_to_cpu(pri_image_status->generation) -
	    le16_to_cpu(sec_image_status->generation);

	ql_dbg(ql_dbg_init, शून्य, 0x0180, "generation delta = %d\n", delta);

	वापस delta;
पूर्ण

व्योम
qla28xx_get_aux_images(
	काष्ठा scsi_qla_host *vha, काष्ठा active_regions *active_regions)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla27xx_image_status pri_aux_image_status, sec_aux_image_status;
	bool valid_pri_image = false, valid_sec_image = false;
	bool active_pri_image = false, active_sec_image = false;

	अगर (!ha->flt_region_aux_img_status_pri) अणु
		ql_dbg(ql_dbg_init, vha, 0x018a, "Primary aux image not addressed\n");
		जाओ check_sec_image;
	पूर्ण

	qla24xx_पढ़ो_flash_data(vha, (uपूर्णांक32_t *)&pri_aux_image_status,
	    ha->flt_region_aux_img_status_pri,
	    माप(pri_aux_image_status) >> 2);
	qla27xx_prपूर्णांक_image(vha, "Primary aux image", &pri_aux_image_status);

	अगर (qla28xx_check_aux_image_status_signature(&pri_aux_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018b,
		    "Primary aux image signature (%#x) not valid\n",
		    le32_to_cpu(pri_aux_image_status.signature));
		जाओ check_sec_image;
	पूर्ण

	अगर (qla27xx_image_status_checksum(&pri_aux_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018c,
		    "Primary aux image checksum failed\n");
		जाओ check_sec_image;
	पूर्ण

	valid_pri_image = true;

	अगर (pri_aux_image_status.image_status_mask & 1) अणु
		ql_dbg(ql_dbg_init, vha, 0x018d,
		    "Primary aux image is active\n");
		active_pri_image = true;
	पूर्ण

check_sec_image:
	अगर (!ha->flt_region_aux_img_status_sec) अणु
		ql_dbg(ql_dbg_init, vha, 0x018a,
		    "Secondary aux image not addressed\n");
		जाओ check_valid_image;
	पूर्ण

	qla24xx_पढ़ो_flash_data(vha, (uपूर्णांक32_t *)&sec_aux_image_status,
	    ha->flt_region_aux_img_status_sec,
	    माप(sec_aux_image_status) >> 2);
	qla27xx_prपूर्णांक_image(vha, "Secondary aux image", &sec_aux_image_status);

	अगर (qla28xx_check_aux_image_status_signature(&sec_aux_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018b,
		    "Secondary aux image signature (%#x) not valid\n",
		    le32_to_cpu(sec_aux_image_status.signature));
		जाओ check_valid_image;
	पूर्ण

	अगर (qla27xx_image_status_checksum(&sec_aux_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018c,
		    "Secondary aux image checksum failed\n");
		जाओ check_valid_image;
	पूर्ण

	valid_sec_image = true;

	अगर (sec_aux_image_status.image_status_mask & 1) अणु
		ql_dbg(ql_dbg_init, vha, 0x018d,
		    "Secondary aux image is active\n");
		active_sec_image = true;
	पूर्ण

check_valid_image:
	अगर (valid_pri_image && active_pri_image &&
	    valid_sec_image && active_sec_image) अणु
		अगर (qla27xx_compare_image_generation(&pri_aux_image_status,
		    &sec_aux_image_status) >= 0) अणु
			qla28xx_component_status(active_regions,
			    &pri_aux_image_status);
		पूर्ण अन्यथा अणु
			qla28xx_component_status(active_regions,
			    &sec_aux_image_status);
		पूर्ण
	पूर्ण अन्यथा अगर (valid_pri_image && active_pri_image) अणु
		qla28xx_component_status(active_regions, &pri_aux_image_status);
	पूर्ण अन्यथा अगर (valid_sec_image && active_sec_image) अणु
		qla28xx_component_status(active_regions, &sec_aux_image_status);
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x018f,
	    "aux images active: BCFG=%u VPD/NVR=%u NPIV0/1=%u NPIV2/3=%u\n",
	    active_regions->aux.board_config,
	    active_regions->aux.vpd_nvram,
	    active_regions->aux.npiv_config_0_1,
	    active_regions->aux.npiv_config_2_3);
पूर्ण

व्योम
qla27xx_get_active_image(काष्ठा scsi_qla_host *vha,
    काष्ठा active_regions *active_regions)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla27xx_image_status pri_image_status, sec_image_status;
	bool valid_pri_image = false, valid_sec_image = false;
	bool active_pri_image = false, active_sec_image = false;

	अगर (!ha->flt_region_img_status_pri) अणु
		ql_dbg(ql_dbg_init, vha, 0x018a, "Primary image not addressed\n");
		जाओ check_sec_image;
	पूर्ण

	अगर (qla24xx_पढ़ो_flash_data(vha, (uपूर्णांक32_t *)&pri_image_status,
	    ha->flt_region_img_status_pri, माप(pri_image_status) >> 2) !=
	    QLA_SUCCESS) अणु
		WARN_ON_ONCE(true);
		जाओ check_sec_image;
	पूर्ण
	qla27xx_prपूर्णांक_image(vha, "Primary image", &pri_image_status);

	अगर (qla27xx_check_image_status_signature(&pri_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018b,
		    "Primary image signature (%#x) not valid\n",
		    le32_to_cpu(pri_image_status.signature));
		जाओ check_sec_image;
	पूर्ण

	अगर (qla27xx_image_status_checksum(&pri_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018c,
		    "Primary image checksum failed\n");
		जाओ check_sec_image;
	पूर्ण

	valid_pri_image = true;

	अगर (pri_image_status.image_status_mask & 1) अणु
		ql_dbg(ql_dbg_init, vha, 0x018d,
		    "Primary image is active\n");
		active_pri_image = true;
	पूर्ण

check_sec_image:
	अगर (!ha->flt_region_img_status_sec) अणु
		ql_dbg(ql_dbg_init, vha, 0x018a, "Secondary image not addressed\n");
		जाओ check_valid_image;
	पूर्ण

	qla24xx_पढ़ो_flash_data(vha, (uपूर्णांक32_t *)(&sec_image_status),
	    ha->flt_region_img_status_sec, माप(sec_image_status) >> 2);
	qla27xx_prपूर्णांक_image(vha, "Secondary image", &sec_image_status);

	अगर (qla27xx_check_image_status_signature(&sec_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018b,
		    "Secondary image signature (%#x) not valid\n",
		    le32_to_cpu(sec_image_status.signature));
		जाओ check_valid_image;
	पूर्ण

	अगर (qla27xx_image_status_checksum(&sec_image_status)) अणु
		ql_dbg(ql_dbg_init, vha, 0x018c,
		    "Secondary image checksum failed\n");
		जाओ check_valid_image;
	पूर्ण

	valid_sec_image = true;

	अगर (sec_image_status.image_status_mask & 1) अणु
		ql_dbg(ql_dbg_init, vha, 0x018d,
		    "Secondary image is active\n");
		active_sec_image = true;
	पूर्ण

check_valid_image:
	अगर (valid_pri_image && active_pri_image)
		active_regions->global = QLA27XX_PRIMARY_IMAGE;

	अगर (valid_sec_image && active_sec_image) अणु
		अगर (!active_regions->global ||
		    qla27xx_compare_image_generation(
			&pri_image_status, &sec_image_status) < 0) अणु
			active_regions->global = QLA27XX_SECONDARY_IMAGE;
		पूर्ण
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x018f, "active image %s (%u)\n",
	    active_regions->global == QLA27XX_DEFAULT_IMAGE ?
		"default (boot/fw)" :
	    active_regions->global == QLA27XX_PRIMARY_IMAGE ?
		"primary" :
	    active_regions->global == QLA27XX_SECONDARY_IMAGE ?
		"secondary" : "invalid",
	    active_regions->global);
पूर्ण

bool qla24xx_risc_firmware_invalid(uपूर्णांक32_t *dword)
अणु
	वापस
	    !(dword[4] | dword[5] | dword[6] | dword[7]) ||
	    !(~dword[4] | ~dword[5] | ~dword[6] | ~dword[7]);
पूर्ण

अटल पूर्णांक
qla24xx_load_risc_flash(scsi_qla_host_t *vha, uपूर्णांक32_t *srisc_addr,
    uपूर्णांक32_t faddr)
अणु
	पूर्णांक rval;
	uपूर्णांक ढाँचाs, segments, fragment;
	uदीर्घ i;
	uपूर्णांक j;
	uदीर्घ dlen;
	uपूर्णांक32_t *dcode;
	uपूर्णांक32_t risc_addr, risc_size, risc_attr = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा fwdt *fwdt = ha->fwdt;

	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "FW: Loading firmware from flash (%x).\n", faddr);

	dcode = (uपूर्णांक32_t *)req->ring;
	qla24xx_पढ़ो_flash_data(vha, dcode, faddr, 8);
	अगर (qla24xx_risc_firmware_invalid(dcode)) अणु
		ql_log(ql_log_fatal, vha, 0x008c,
		    "Unable to verify the integrity of flash firmware "
		    "image.\n");
		ql_log(ql_log_fatal, vha, 0x008d,
		    "Firmware data: %08x %08x %08x %08x.\n",
		    dcode[0], dcode[1], dcode[2], dcode[3]);

		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	dcode = (uपूर्णांक32_t *)req->ring;
	*srisc_addr = 0;
	segments = FA_RISC_CODE_SEGMENTS;
	क्रम (j = 0; j < segments; j++) अणु
		ql_dbg(ql_dbg_init, vha, 0x008d,
		    "-> Loading segment %u...\n", j);
		qla24xx_पढ़ो_flash_data(vha, dcode, faddr, 10);
		risc_addr = be32_to_cpu((__क्रमce __be32)dcode[2]);
		risc_size = be32_to_cpu((__क्रमce __be32)dcode[3]);
		अगर (!*srisc_addr) अणु
			*srisc_addr = risc_addr;
			risc_attr = be32_to_cpu((__क्रमce __be32)dcode[9]);
		पूर्ण

		dlen = ha->fw_transfer_size >> 2;
		क्रम (fragment = 0; risc_size; fragment++) अणु
			अगर (dlen > risc_size)
				dlen = risc_size;

			ql_dbg(ql_dbg_init, vha, 0x008e,
			    "-> Loading fragment %u: %#x <- %#x (%#lx dwords)...\n",
			    fragment, risc_addr, faddr, dlen);
			qla24xx_पढ़ो_flash_data(vha, dcode, faddr, dlen);
			क्रम (i = 0; i < dlen; i++)
				dcode[i] = swab32(dcode[i]);

			rval = qla2x00_load_ram(vha, req->dma, risc_addr, dlen);
			अगर (rval) अणु
				ql_log(ql_log_fatal, vha, 0x008f,
				    "-> Failed load firmware fragment %u.\n",
				    fragment);
				वापस QLA_FUNCTION_FAILED;
			पूर्ण

			faddr += dlen;
			risc_addr += dlen;
			risc_size -= dlen;
		पूर्ण
	पूर्ण

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_SUCCESS;

	ढाँचाs = (risc_attr & BIT_9) ? 2 : 1;
	ql_dbg(ql_dbg_init, vha, 0x0160, "-> templates = %u\n", ढाँचाs);
	क्रम (j = 0; j < ढाँचाs; j++, fwdt++) अणु
		vमुक्त(fwdt->ढाँचा);
		fwdt->ढाँचा = शून्य;
		fwdt->length = 0;

		dcode = (uपूर्णांक32_t *)req->ring;
		qla24xx_पढ़ो_flash_data(vha, dcode, faddr, 7);
		risc_size = be32_to_cpu((__क्रमce __be32)dcode[2]);
		ql_dbg(ql_dbg_init, vha, 0x0161,
		    "-> fwdt%u template array at %#x (%#x dwords)\n",
		    j, faddr, risc_size);
		अगर (!risc_size || !~risc_size) अणु
			ql_dbg(ql_dbg_init, vha, 0x0162,
			    "-> fwdt%u failed to read array\n", j);
			जाओ failed;
		पूर्ण

		/* skip header and ignore checksum */
		faddr += 7;
		risc_size -= 8;

		ql_dbg(ql_dbg_init, vha, 0x0163,
		    "-> fwdt%u template allocate template %#x words...\n",
		    j, risc_size);
		fwdt->ढाँचा = vदो_स्मृति(risc_size * माप(*dcode));
		अगर (!fwdt->ढाँचा) अणु
			ql_log(ql_log_warn, vha, 0x0164,
			    "-> fwdt%u failed allocate template.\n", j);
			जाओ failed;
		पूर्ण

		dcode = fwdt->ढाँचा;
		qla24xx_पढ़ो_flash_data(vha, dcode, faddr, risc_size);

		अगर (!qla27xx_fwdt_ढाँचा_valid(dcode)) अणु
			ql_log(ql_log_warn, vha, 0x0165,
			    "-> fwdt%u failed template validate\n", j);
			जाओ failed;
		पूर्ण

		dlen = qla27xx_fwdt_ढाँचा_size(dcode);
		ql_dbg(ql_dbg_init, vha, 0x0166,
		    "-> fwdt%u template size %#lx bytes (%#lx words)\n",
		    j, dlen, dlen / माप(*dcode));
		अगर (dlen > risc_size * माप(*dcode)) अणु
			ql_log(ql_log_warn, vha, 0x0167,
			    "-> fwdt%u template exceeds array (%-lu bytes)\n",
			    j, dlen - risc_size * माप(*dcode));
			जाओ failed;
		पूर्ण

		fwdt->length = dlen;
		ql_dbg(ql_dbg_init, vha, 0x0168,
		    "-> fwdt%u loaded template ok\n", j);

		faddr += risc_size + 1;
	पूर्ण

	वापस QLA_SUCCESS;

failed:
	vमुक्त(fwdt->ढाँचा);
	fwdt->ढाँचा = शून्य;
	fwdt->length = 0;

	वापस QLA_SUCCESS;
पूर्ण

#घोषणा QLA_FW_URL "http://ldriver.qlogic.com/firmware/"

पूर्णांक
qla2x00_load_risc(scsi_qla_host_t *vha, uपूर्णांक32_t *srisc_addr)
अणु
	पूर्णांक	rval;
	पूर्णांक	i, fragment;
	uपूर्णांक16_t *wcode;
	__be16	 *fwcode;
	uपूर्णांक32_t risc_addr, risc_size, fwclen, wlen, *seg;
	काष्ठा fw_blob *blob;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];

	/* Load firmware blob. */
	blob = qla2x00_request_firmware(vha);
	अगर (!blob) अणु
		ql_log(ql_log_info, vha, 0x0083,
		    "Firmware image unavailable.\n");
		ql_log(ql_log_info, vha, 0x0084,
		    "Firmware images can be retrieved from: "QLA_FW_URL ".\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	rval = QLA_SUCCESS;

	wcode = (uपूर्णांक16_t *)req->ring;
	*srisc_addr = 0;
	fwcode = (__क्रमce __be16 *)blob->fw->data;
	fwclen = 0;

	/* Validate firmware image by checking version. */
	अगर (blob->fw->size < 8 * माप(uपूर्णांक16_t)) अणु
		ql_log(ql_log_fatal, vha, 0x0085,
		    "Unable to verify integrity of firmware image (%zd).\n",
		    blob->fw->size);
		जाओ fail_fw_पूर्णांकegrity;
	पूर्ण
	क्रम (i = 0; i < 4; i++)
		wcode[i] = be16_to_cpu(fwcode[i + 4]);
	अगर ((wcode[0] == 0xffff && wcode[1] == 0xffff && wcode[2] == 0xffff &&
	    wcode[3] == 0xffff) || (wcode[0] == 0 && wcode[1] == 0 &&
		wcode[2] == 0 && wcode[3] == 0)) अणु
		ql_log(ql_log_fatal, vha, 0x0086,
		    "Unable to verify integrity of firmware image.\n");
		ql_log(ql_log_fatal, vha, 0x0087,
		    "Firmware data: %04x %04x %04x %04x.\n",
		    wcode[0], wcode[1], wcode[2], wcode[3]);
		जाओ fail_fw_पूर्णांकegrity;
	पूर्ण

	seg = blob->segs;
	जबतक (*seg && rval == QLA_SUCCESS) अणु
		risc_addr = *seg;
		*srisc_addr = *srisc_addr == 0 ? *seg : *srisc_addr;
		risc_size = be16_to_cpu(fwcode[3]);

		/* Validate firmware image size. */
		fwclen += risc_size * माप(uपूर्णांक16_t);
		अगर (blob->fw->size < fwclen) अणु
			ql_log(ql_log_fatal, vha, 0x0088,
			    "Unable to verify integrity of firmware image "
			    "(%zd).\n", blob->fw->size);
			जाओ fail_fw_पूर्णांकegrity;
		पूर्ण

		fragment = 0;
		जबतक (risc_size > 0 && rval == QLA_SUCCESS) अणु
			wlen = (uपूर्णांक16_t)(ha->fw_transfer_size >> 1);
			अगर (wlen > risc_size)
				wlen = risc_size;
			ql_dbg(ql_dbg_init, vha, 0x0089,
			    "Loading risc segment@ risc addr %x number of "
			    "words 0x%x.\n", risc_addr, wlen);

			क्रम (i = 0; i < wlen; i++)
				wcode[i] = swab16((__क्रमce u32)fwcode[i]);

			rval = qla2x00_load_ram(vha, req->dma, risc_addr,
			    wlen);
			अगर (rval) अणु
				ql_log(ql_log_fatal, vha, 0x008a,
				    "Failed to load segment %d of firmware.\n",
				    fragment);
				अवरोध;
			पूर्ण

			fwcode += wlen;
			risc_addr += wlen;
			risc_size -= wlen;
			fragment++;
		पूर्ण

		/* Next segment. */
		seg++;
	पूर्ण
	वापस rval;

fail_fw_पूर्णांकegrity:
	वापस QLA_FUNCTION_FAILED;
पूर्ण

अटल पूर्णांक
qla24xx_load_risc_blob(scsi_qla_host_t *vha, uपूर्णांक32_t *srisc_addr)
अणु
	पूर्णांक	rval;
	uपूर्णांक ढाँचाs, segments, fragment;
	uपूर्णांक32_t *dcode;
	uदीर्घ dlen;
	uपूर्णांक32_t risc_addr, risc_size, risc_attr = 0;
	uदीर्घ i;
	uपूर्णांक j;
	काष्ठा fw_blob *blob;
	__be32 *fwcode;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा fwdt *fwdt = ha->fwdt;

	ql_dbg(ql_dbg_init, vha, 0x0090,
	    "-> FW: Loading via request-firmware.\n");

	blob = qla2x00_request_firmware(vha);
	अगर (!blob) अणु
		ql_log(ql_log_warn, vha, 0x0092,
		    "-> Firmware file not found.\n");

		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	fwcode = (__क्रमce __be32 *)blob->fw->data;
	dcode = (__क्रमce uपूर्णांक32_t *)fwcode;
	अगर (qla24xx_risc_firmware_invalid(dcode)) अणु
		ql_log(ql_log_fatal, vha, 0x0093,
		    "Unable to verify integrity of firmware image (%zd).\n",
		    blob->fw->size);
		ql_log(ql_log_fatal, vha, 0x0095,
		    "Firmware data: %08x %08x %08x %08x.\n",
		    dcode[0], dcode[1], dcode[2], dcode[3]);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	dcode = (uपूर्णांक32_t *)req->ring;
	*srisc_addr = 0;
	segments = FA_RISC_CODE_SEGMENTS;
	क्रम (j = 0; j < segments; j++) अणु
		ql_dbg(ql_dbg_init, vha, 0x0096,
		    "-> Loading segment %u...\n", j);
		risc_addr = be32_to_cpu(fwcode[2]);
		risc_size = be32_to_cpu(fwcode[3]);

		अगर (!*srisc_addr) अणु
			*srisc_addr = risc_addr;
			risc_attr = be32_to_cpu(fwcode[9]);
		पूर्ण

		dlen = ha->fw_transfer_size >> 2;
		क्रम (fragment = 0; risc_size; fragment++) अणु
			अगर (dlen > risc_size)
				dlen = risc_size;

			ql_dbg(ql_dbg_init, vha, 0x0097,
			    "-> Loading fragment %u: %#x <- %#x (%#lx words)...\n",
			    fragment, risc_addr,
			    (uपूर्णांक32_t)(fwcode - (typeof(fwcode))blob->fw->data),
			    dlen);

			क्रम (i = 0; i < dlen; i++)
				dcode[i] = swab32((__क्रमce u32)fwcode[i]);

			rval = qla2x00_load_ram(vha, req->dma, risc_addr, dlen);
			अगर (rval) अणु
				ql_log(ql_log_fatal, vha, 0x0098,
				    "-> Failed load firmware fragment %u.\n",
				    fragment);
				वापस QLA_FUNCTION_FAILED;
			पूर्ण

			fwcode += dlen;
			risc_addr += dlen;
			risc_size -= dlen;
		पूर्ण
	पूर्ण

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_SUCCESS;

	ढाँचाs = (risc_attr & BIT_9) ? 2 : 1;
	ql_dbg(ql_dbg_init, vha, 0x0170, "-> templates = %u\n", ढाँचाs);
	क्रम (j = 0; j < ढाँचाs; j++, fwdt++) अणु
		vमुक्त(fwdt->ढाँचा);
		fwdt->ढाँचा = शून्य;
		fwdt->length = 0;

		risc_size = be32_to_cpu(fwcode[2]);
		ql_dbg(ql_dbg_init, vha, 0x0171,
		    "-> fwdt%u template array at %#x (%#x dwords)\n",
		    j, (uपूर्णांक32_t)((व्योम *)fwcode - (व्योम *)blob->fw->data),
		    risc_size);
		अगर (!risc_size || !~risc_size) अणु
			ql_dbg(ql_dbg_init, vha, 0x0172,
			    "-> fwdt%u failed to read array\n", j);
			जाओ failed;
		पूर्ण

		/* skip header and ignore checksum */
		fwcode += 7;
		risc_size -= 8;

		ql_dbg(ql_dbg_init, vha, 0x0173,
		    "-> fwdt%u template allocate template %#x words...\n",
		    j, risc_size);
		fwdt->ढाँचा = vदो_स्मृति(risc_size * माप(*dcode));
		अगर (!fwdt->ढाँचा) अणु
			ql_log(ql_log_warn, vha, 0x0174,
			    "-> fwdt%u failed allocate template.\n", j);
			जाओ failed;
		पूर्ण

		dcode = fwdt->ढाँचा;
		क्रम (i = 0; i < risc_size; i++)
			dcode[i] = (__क्रमce u32)fwcode[i];

		अगर (!qla27xx_fwdt_ढाँचा_valid(dcode)) अणु
			ql_log(ql_log_warn, vha, 0x0175,
			    "-> fwdt%u failed template validate\n", j);
			जाओ failed;
		पूर्ण

		dlen = qla27xx_fwdt_ढाँचा_size(dcode);
		ql_dbg(ql_dbg_init, vha, 0x0176,
		    "-> fwdt%u template size %#lx bytes (%#lx words)\n",
		    j, dlen, dlen / माप(*dcode));
		अगर (dlen > risc_size * माप(*dcode)) अणु
			ql_log(ql_log_warn, vha, 0x0177,
			    "-> fwdt%u template exceeds array (%-lu bytes)\n",
			    j, dlen - risc_size * माप(*dcode));
			जाओ failed;
		पूर्ण

		fwdt->length = dlen;
		ql_dbg(ql_dbg_init, vha, 0x0178,
		    "-> fwdt%u loaded template ok\n", j);

		fwcode += risc_size + 1;
	पूर्ण

	वापस QLA_SUCCESS;

failed:
	vमुक्त(fwdt->ढाँचा);
	fwdt->ढाँचा = शून्य;
	fwdt->length = 0;

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qla24xx_load_risc(scsi_qla_host_t *vha, uपूर्णांक32_t *srisc_addr)
अणु
	पूर्णांक rval;

	अगर (ql2xfwloadbin == 1)
		वापस qla81xx_load_risc(vha, srisc_addr);

	/*
	 * FW Load priority:
	 * 1) Firmware via request-firmware पूर्णांकerface (.bin file).
	 * 2) Firmware residing in flash.
	 */
	rval = qla24xx_load_risc_blob(vha, srisc_addr);
	अगर (rval == QLA_SUCCESS)
		वापस rval;

	वापस qla24xx_load_risc_flash(vha, srisc_addr,
	    vha->hw->flt_region_fw);
पूर्ण

पूर्णांक
qla81xx_load_risc(scsi_qla_host_t *vha, uपूर्णांक32_t *srisc_addr)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा active_regions active_regions = अणु पूर्ण;

	अगर (ql2xfwloadbin == 2)
		जाओ try_blob_fw;

	/* FW Load priority:
	 * 1) Firmware residing in flash.
	 * 2) Firmware via request-firmware पूर्णांकerface (.bin file).
	 * 3) Golden-Firmware residing in flash -- (limited operation).
	 */

	अगर (!IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		जाओ try_primary_fw;

	qla27xx_get_active_image(vha, &active_regions);

	अगर (active_regions.global != QLA27XX_SECONDARY_IMAGE)
		जाओ try_primary_fw;

	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "Loading secondary firmware image.\n");
	rval = qla24xx_load_risc_flash(vha, srisc_addr, ha->flt_region_fw_sec);
	अगर (!rval)
		वापस rval;

try_primary_fw:
	ql_dbg(ql_dbg_init, vha, 0x008b,
	    "Loading primary firmware image.\n");
	rval = qla24xx_load_risc_flash(vha, srisc_addr, ha->flt_region_fw);
	अगर (!rval)
		वापस rval;

try_blob_fw:
	rval = qla24xx_load_risc_blob(vha, srisc_addr);
	अगर (!rval || !ha->flt_region_gold_fw)
		वापस rval;

	ql_log(ql_log_info, vha, 0x0099,
	    "Attempting to fallback to golden firmware.\n");
	rval = qla24xx_load_risc_flash(vha, srisc_addr, ha->flt_region_gold_fw);
	अगर (rval)
		वापस rval;

	ql_log(ql_log_info, vha, 0x009a, "Need firmware flash update.\n");
	ha->flags.running_gold_fw = 1;
	वापस rval;
पूर्ण

व्योम
qla2x00_try_to_stop_firmware(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret, retries;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (ha->flags.pci_channel_io_perm_failure)
		वापस;
	अगर (!IS_FWI2_CAPABLE(ha))
		वापस;
	अगर (!ha->fw_major_version)
		वापस;
	अगर (!ha->flags.fw_started)
		वापस;

	ret = qla2x00_stop_firmware(vha);
	क्रम (retries = 5; ret != QLA_SUCCESS && ret != QLA_FUNCTION_TIMEOUT &&
	    ret != QLA_INVALID_COMMAND && retries ; retries--) अणु
		ha->isp_ops->reset_chip(vha);
		अगर (ha->isp_ops->chip_diag(vha) != QLA_SUCCESS)
			जारी;
		अगर (qla2x00_setup_chip(vha) != QLA_SUCCESS)
			जारी;
		ql_log(ql_log_info, vha, 0x8015,
		    "Attempting retry of stop-firmware command.\n");
		ret = qla2x00_stop_firmware(vha);
	पूर्ण

	QLA_FW_STOPPED(ha);
	ha->flags.fw_init_करोne = 0;
पूर्ण

पूर्णांक
qla24xx_configure_vhba(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	पूर्णांक rval2;
	uपूर्णांक16_t mb[MAILBOX_REGISTER_COUNT];
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	अगर (!vha->vp_idx)
		वापस -EINVAL;

	rval = qla2x00_fw_पढ़ोy(base_vha);

	अगर (rval == QLA_SUCCESS) अणु
		clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);
		qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL);
	पूर्ण

	vha->flags.management_server_logged_in = 0;

	/* Login to SNS first */
	rval2 = ha->isp_ops->fabric_login(vha, NPH_SNS, 0xff, 0xff, 0xfc, mb,
	    BIT_1);
	अगर (rval2 != QLA_SUCCESS || mb[0] != MBS_COMMAND_COMPLETE) अणु
		अगर (rval2 == QLA_MEMORY_ALLOC_FAILED)
			ql_dbg(ql_dbg_init, vha, 0x0120,
			    "Failed SNS login: loop_id=%x, rval2=%d\n",
			    NPH_SNS, rval2);
		अन्यथा
			ql_dbg(ql_dbg_init, vha, 0x0103,
			    "Failed SNS login: loop_id=%x mb[0]=%x mb[1]=%x "
			    "mb[2]=%x mb[6]=%x mb[7]=%x.\n",
			    NPH_SNS, mb[0], mb[1], mb[2], mb[6], mb[7]);
		वापस (QLA_FUNCTION_FAILED);
	पूर्ण

	atomic_set(&vha->loop_करोwn_समयr, 0);
	atomic_set(&vha->loop_state, LOOP_UP);
	set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
	set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
	rval = qla2x00_loop_resync(base_vha);

	वापस rval;
पूर्ण

/* 84XX Support **************************************************************/

अटल LIST_HEAD(qla_cs84xx_list);
अटल DEFINE_MUTEX(qla_cs84xx_mutex);

अटल काष्ठा qla_chip_state_84xx *
qla84xx_get_chip(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_chip_state_84xx *cs84xx;
	काष्ठा qla_hw_data *ha = vha->hw;

	mutex_lock(&qla_cs84xx_mutex);

	/* Find any shared 84xx chip. */
	list_क्रम_each_entry(cs84xx, &qla_cs84xx_list, list) अणु
		अगर (cs84xx->bus == ha->pdev->bus) अणु
			kref_get(&cs84xx->kref);
			जाओ करोne;
		पूर्ण
	पूर्ण

	cs84xx = kzalloc(माप(*cs84xx), GFP_KERNEL);
	अगर (!cs84xx)
		जाओ करोne;

	kref_init(&cs84xx->kref);
	spin_lock_init(&cs84xx->access_lock);
	mutex_init(&cs84xx->fw_update_mutex);
	cs84xx->bus = ha->pdev->bus;

	list_add_tail(&cs84xx->list, &qla_cs84xx_list);
करोne:
	mutex_unlock(&qla_cs84xx_mutex);
	वापस cs84xx;
पूर्ण

अटल व्योम
__qla84xx_chip_release(काष्ठा kref *kref)
अणु
	काष्ठा qla_chip_state_84xx *cs84xx =
	    container_of(kref, काष्ठा qla_chip_state_84xx, kref);

	mutex_lock(&qla_cs84xx_mutex);
	list_del(&cs84xx->list);
	mutex_unlock(&qla_cs84xx_mutex);
	kमुक्त(cs84xx);
पूर्ण

व्योम
qla84xx_put_chip(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (ha->cs84xx)
		kref_put(&ha->cs84xx->kref, __qla84xx_chip_release);
पूर्ण

अटल पूर्णांक
qla84xx_init_chip(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	uपूर्णांक16_t status[2];
	काष्ठा qla_hw_data *ha = vha->hw;

	mutex_lock(&ha->cs84xx->fw_update_mutex);

	rval = qla84xx_verअगरy_chip(vha, status);

	mutex_unlock(&ha->cs84xx->fw_update_mutex);

	वापस rval != QLA_SUCCESS || status[0] ? QLA_FUNCTION_FAILED :
	    QLA_SUCCESS;
पूर्ण

/* 81XX Support **************************************************************/

पूर्णांक
qla81xx_nvram_config(scsi_qla_host_t *vha)
अणु
	पूर्णांक   rval;
	काष्ठा init_cb_81xx *icb;
	काष्ठा nvram_81xx *nv;
	__le32 *dptr;
	uपूर्णांक8_t  *dptr1, *dptr2;
	uपूर्णांक32_t chksum;
	uपूर्णांक16_t cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t faddr;
	काष्ठा active_regions active_regions = अणु पूर्ण;

	rval = QLA_SUCCESS;
	icb = (काष्ठा init_cb_81xx *)ha->init_cb;
	nv = ha->nvram;

	/* Determine NVRAM starting address. */
	ha->nvram_size = माप(*nv);
	ha->vpd_size = FA_NVRAM_VPD_SIZE;
	अगर (IS_P3P_TYPE(ha) || IS_QLA8031(ha))
		ha->vpd_size = FA_VPD_SIZE_82XX;

	अगर (IS_QLA28XX(ha) || IS_QLA27XX(ha))
		qla28xx_get_aux_images(vha, &active_regions);

	/* Get VPD data पूर्णांकo cache */
	ha->vpd = ha->nvram + VPD_OFFSET;

	faddr = ha->flt_region_vpd;
	अगर (IS_QLA28XX(ha)) अणु
		अगर (active_regions.aux.vpd_nvram == QLA27XX_SECONDARY_IMAGE)
			faddr = ha->flt_region_vpd_sec;
		ql_dbg(ql_dbg_init, vha, 0x0110,
		    "Loading %s nvram image.\n",
		    active_regions.aux.vpd_nvram == QLA27XX_PRIMARY_IMAGE ?
		    "primary" : "secondary");
	पूर्ण
	ha->isp_ops->पढ़ो_optrom(vha, ha->vpd, faddr << 2, ha->vpd_size);

	/* Get NVRAM data पूर्णांकo cache and calculate checksum. */
	faddr = ha->flt_region_nvram;
	अगर (IS_QLA28XX(ha)) अणु
		अगर (active_regions.aux.vpd_nvram == QLA27XX_SECONDARY_IMAGE)
			faddr = ha->flt_region_nvram_sec;
	पूर्ण
	ql_dbg(ql_dbg_init, vha, 0x0110,
	    "Loading %s nvram image.\n",
	    active_regions.aux.vpd_nvram == QLA27XX_PRIMARY_IMAGE ?
	    "primary" : "secondary");
	ha->isp_ops->पढ़ो_optrom(vha, ha->nvram, faddr << 2, ha->nvram_size);

	dptr = (__क्रमce __le32 *)nv;
	क्रम (cnt = 0, chksum = 0; cnt < ha->nvram_size >> 2; cnt++, dptr++)
		chksum += le32_to_cpu(*dptr);

	ql_dbg(ql_dbg_init + ql_dbg_buffer, vha, 0x0111,
	    "Contents of NVRAM:\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0112,
	    nv, ha->nvram_size);

	/* Bad NVRAM data, set शेषs parameters. */
	अगर (chksum || स_भेद("ISP ", nv->id, माप(nv->id)) ||
	    le16_to_cpu(nv->nvram_version) < ICB_VERSION) अणु
		/* Reset NVRAM data. */
		ql_log(ql_log_info, vha, 0x0073,
		    "Inconsistent NVRAM checksum=%#x id=%.4s version=%#x.\n",
		    chksum, nv->id, le16_to_cpu(nv->nvram_version));
		ql_dump_buffer(ql_dbg_init, vha, 0x0073, nv, माप(*nv));
		ql_log(ql_log_info, vha, 0x0074,
		    "Falling back to functioning (yet invalid -- WWPN) "
		    "defaults.\n");

		/*
		 * Set शेष initialization control block.
		 */
		स_रखो(nv, 0, ha->nvram_size);
		nv->nvram_version = cpu_to_le16(ICB_VERSION);
		nv->version = cpu_to_le16(ICB_VERSION);
		nv->frame_payload_size = cpu_to_le16(2048);
		nv->execution_throttle = cpu_to_le16(0xFFFF);
		nv->exchange_count = cpu_to_le16(0);
		nv->port_name[0] = 0x21;
		nv->port_name[1] = 0x00 + ha->port_no + 1;
		nv->port_name[2] = 0x00;
		nv->port_name[3] = 0xe0;
		nv->port_name[4] = 0x8b;
		nv->port_name[5] = 0x1c;
		nv->port_name[6] = 0x55;
		nv->port_name[7] = 0x86;
		nv->node_name[0] = 0x20;
		nv->node_name[1] = 0x00;
		nv->node_name[2] = 0x00;
		nv->node_name[3] = 0xe0;
		nv->node_name[4] = 0x8b;
		nv->node_name[5] = 0x1c;
		nv->node_name[6] = 0x55;
		nv->node_name[7] = 0x86;
		nv->login_retry_count = cpu_to_le16(8);
		nv->पूर्णांकerrupt_delay_समयr = cpu_to_le16(0);
		nv->login_समयout = cpu_to_le16(0);
		nv->firmware_options_1 =
		    cpu_to_le32(BIT_14|BIT_13|BIT_2|BIT_1);
		nv->firmware_options_2 = cpu_to_le32(2 << 4);
		nv->firmware_options_2 |= cpu_to_le32(BIT_12);
		nv->firmware_options_3 = cpu_to_le32(2 << 13);
		nv->host_p = cpu_to_le32(BIT_11|BIT_10);
		nv->efi_parameters = cpu_to_le32(0);
		nv->reset_delay = 5;
		nv->max_luns_per_target = cpu_to_le16(128);
		nv->port_करोwn_retry_count = cpu_to_le16(30);
		nv->link_करोwn_समयout = cpu_to_le16(180);
		nv->enode_mac[0] = 0x00;
		nv->enode_mac[1] = 0xC0;
		nv->enode_mac[2] = 0xDD;
		nv->enode_mac[3] = 0x04;
		nv->enode_mac[4] = 0x05;
		nv->enode_mac[5] = 0x06 + ha->port_no + 1;

		rval = 1;
	पूर्ण

	अगर (IS_T10_PI_CAPABLE(ha))
		nv->frame_payload_size &= cpu_to_le16(~7);

	qlt_81xx_config_nvram_stage1(vha, nv);

	/* Reset Initialization control block */
	स_रखो(icb, 0, ha->init_cb_size);

	/* Copy 1st segment. */
	dptr1 = (uपूर्णांक8_t *)icb;
	dptr2 = (uपूर्णांक8_t *)&nv->version;
	cnt = (uपूर्णांक8_t *)&icb->response_q_inpoपूर्णांकer - (uपूर्णांक8_t *)&icb->version;
	जबतक (cnt--)
		*dptr1++ = *dptr2++;

	icb->login_retry_count = nv->login_retry_count;

	/* Copy 2nd segment. */
	dptr1 = (uपूर्णांक8_t *)&icb->पूर्णांकerrupt_delay_समयr;
	dptr2 = (uपूर्णांक8_t *)&nv->पूर्णांकerrupt_delay_समयr;
	cnt = (uपूर्णांक8_t *)&icb->reserved_5 -
	    (uपूर्णांक8_t *)&icb->पूर्णांकerrupt_delay_समयr;
	जबतक (cnt--)
		*dptr1++ = *dptr2++;

	स_नकल(icb->enode_mac, nv->enode_mac, माप(icb->enode_mac));
	/* Some boards (with valid NVRAMs) still have शून्य enode_mac!! */
	अगर (!स_भेद(icb->enode_mac, "\0\0\0\0\0\0", माप(icb->enode_mac))) अणु
		icb->enode_mac[0] = 0x00;
		icb->enode_mac[1] = 0xC0;
		icb->enode_mac[2] = 0xDD;
		icb->enode_mac[3] = 0x04;
		icb->enode_mac[4] = 0x05;
		icb->enode_mac[5] = 0x06 + ha->port_no + 1;
	पूर्ण

	/* Use extended-initialization control block. */
	स_नकल(ha->ex_init_cb, &nv->ex_version, माप(*ha->ex_init_cb));
	ha->frame_payload_size = le16_to_cpu(icb->frame_payload_size);
	/*
	 * Setup driver NVRAM options.
	 */
	qla2x00_set_model_info(vha, nv->model_name, माप(nv->model_name),
	    "QLE8XXX");

	qlt_81xx_config_nvram_stage2(vha, icb);

	/* Use alternate WWN? */
	अगर (nv->host_p & cpu_to_le32(BIT_15)) अणु
		स_नकल(icb->node_name, nv->alternate_node_name, WWN_SIZE);
		स_नकल(icb->port_name, nv->alternate_port_name, WWN_SIZE);
	पूर्ण

	/* Prepare nodename */
	अगर ((icb->firmware_options_1 & cpu_to_le32(BIT_14)) == 0) अणु
		/*
		 * Firmware will apply the following mask अगर the nodename was
		 * not provided.
		 */
		स_नकल(icb->node_name, icb->port_name, WWN_SIZE);
		icb->node_name[0] &= 0xF0;
	पूर्ण

	अगर (IS_QLA28XX(ha) || IS_QLA27XX(ha)) अणु
		अगर ((nv->enhanced_features & BIT_7) == 0)
			ha->flags.scm_supported_a = 1;
	पूर्ण

	/* Set host adapter parameters. */
	ha->flags.disable_risc_code_load = 0;
	ha->flags.enable_lip_reset = 0;
	ha->flags.enable_lip_full_login =
	    le32_to_cpu(nv->host_p) & BIT_10 ? 1 : 0;
	ha->flags.enable_target_reset =
	    le32_to_cpu(nv->host_p) & BIT_11 ? 1 : 0;
	ha->flags.enable_led_scheme = 0;
	ha->flags.disable_serdes = le32_to_cpu(nv->host_p) & BIT_5 ? 1 : 0;

	ha->operating_mode = (le32_to_cpu(icb->firmware_options_2) &
	    (BIT_6 | BIT_5 | BIT_4)) >> 4;

	/* save HBA serial number */
	ha->serial0 = icb->port_name[5];
	ha->serial1 = icb->port_name[6];
	ha->serial2 = icb->port_name[7];
	स_नकल(vha->node_name, icb->node_name, WWN_SIZE);
	स_नकल(vha->port_name, icb->port_name, WWN_SIZE);

	icb->execution_throttle = cpu_to_le16(0xFFFF);

	ha->retry_count = le16_to_cpu(nv->login_retry_count);

	/* Set minimum login_समयout to 4 seconds. */
	अगर (le16_to_cpu(nv->login_समयout) < ql2xlogपूर्णांकimeout)
		nv->login_समयout = cpu_to_le16(ql2xlogपूर्णांकimeout);
	अगर (le16_to_cpu(nv->login_समयout) < 4)
		nv->login_समयout = cpu_to_le16(4);
	ha->login_समयout = le16_to_cpu(nv->login_समयout);

	/* Set minimum RATOV to 100 tenths of a second. */
	ha->r_a_tov = 100;

	ha->loop_reset_delay = nv->reset_delay;

	/* Link Down Timeout = 0:
	 *
	 *	When Port Down समयr expires we will start वापसing
	 *	I/O's to OS with "DID_NO_CONNECT".
	 *
	 * Link Down Timeout != 0:
	 *
	 *	 The driver रुकोs क्रम the link to come up after link करोwn
	 *	 beक्रमe वापसing I/Os to OS with "DID_NO_CONNECT".
	 */
	अगर (le16_to_cpu(nv->link_करोwn_समयout) == 0) अणु
		ha->loop_करोwn_पात_समय =
		    (LOOP_DOWN_TIME - LOOP_DOWN_TIMEOUT);
	पूर्ण अन्यथा अणु
		ha->link_करोwn_समयout =	le16_to_cpu(nv->link_करोwn_समयout);
		ha->loop_करोwn_पात_समय =
		    (LOOP_DOWN_TIME - ha->link_करोwn_समयout);
	पूर्ण

	/* Need enough समय to try and get the port back. */
	ha->port_करोwn_retry_count = le16_to_cpu(nv->port_करोwn_retry_count);
	अगर (qlport_करोwn_retry)
		ha->port_करोwn_retry_count = qlport_करोwn_retry;

	/* Set login_retry_count */
	ha->login_retry_count  = le16_to_cpu(nv->login_retry_count);
	अगर (ha->port_करोwn_retry_count ==
	    le16_to_cpu(nv->port_करोwn_retry_count) &&
	    ha->port_करोwn_retry_count > 3)
		ha->login_retry_count = ha->port_करोwn_retry_count;
	अन्यथा अगर (ha->port_करोwn_retry_count > (पूर्णांक)ha->login_retry_count)
		ha->login_retry_count = ha->port_करोwn_retry_count;
	अगर (ql2xloginretrycount)
		ha->login_retry_count = ql2xloginretrycount;

	/* अगर not running MSI-X we need handshaking on पूर्णांकerrupts */
	अगर (!vha->hw->flags.msix_enabled &&
	    (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)))
		icb->firmware_options_2 |= cpu_to_le32(BIT_22);

	/* Enable ZIO. */
	अगर (!vha->flags.init_करोne) अणु
		ha->zio_mode = le32_to_cpu(icb->firmware_options_2) &
		    (BIT_3 | BIT_2 | BIT_1 | BIT_0);
		ha->zio_समयr = le16_to_cpu(icb->पूर्णांकerrupt_delay_समयr) ?
		    le16_to_cpu(icb->पूर्णांकerrupt_delay_समयr) : 2;
	पूर्ण
	icb->firmware_options_2 &= cpu_to_le32(
	    ~(BIT_3 | BIT_2 | BIT_1 | BIT_0));
	vha->flags.process_response_queue = 0;
	अगर (ha->zio_mode != QLA_ZIO_DISABLED) अणु
		ha->zio_mode = QLA_ZIO_MODE_6;

		ql_log(ql_log_info, vha, 0x0075,
		    "ZIO mode %d enabled; timer delay (%d us).\n",
		    ha->zio_mode,
		    ha->zio_समयr * 100);

		icb->firmware_options_2 |= cpu_to_le32(
		    (uपूर्णांक32_t)ha->zio_mode);
		icb->पूर्णांकerrupt_delay_समयr = cpu_to_le16(ha->zio_समयr);
		vha->flags.process_response_queue = 1;
	पूर्ण

	 /* enable RIDA Format2 */
	icb->firmware_options_3 |= cpu_to_le32(BIT_0);

	/* N2N: driver will initiate Login instead of FW */
	icb->firmware_options_3 |= cpu_to_le32(BIT_8);

	/* Determine NVMe/FCP priority क्रम target ports */
	ha->fc4_type_priority = qla2xxx_get_fc4_priority(vha);

	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0076,
		    "NVRAM configuration failed.\n");
	पूर्ण
	वापस (rval);
पूर्ण

पूर्णांक
qla82xx_restart_isp(scsi_qla_host_t *vha)
अणु
	पूर्णांक status, rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *vp;
	अचिन्हित दीर्घ flags;

	status = qla2x00_init_rings(vha);
	अगर (!status) अणु
		clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);
		ha->flags.chip_reset_करोne = 1;

		status = qla2x00_fw_पढ़ोy(vha);
		अगर (!status) अणु
			/* Issue a marker after FW becomes पढ़ोy. */
			qla2x00_marker(vha, ha->base_qpair, 0, 0, MK_SYNC_ALL);
			vha->flags.online = 1;
			set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		पूर्ण

		/* अगर no cable then assume it's good */
		अगर ((vha->device_flags & DFLG_NO_CABLE))
			status = 0;
	पूर्ण

	अगर (!status) अणु
		clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);

		अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr)) अणु
			/*
			 * Issue marker command only when we are going
			 * to start the I/O .
			 */
			vha->marker_needed = 1;
		पूर्ण

		ha->isp_ops->enable_पूर्णांकrs(ha);

		ha->isp_पात_cnt = 0;
		clear_bit(ISP_ABORT_RETRY, &vha->dpc_flags);

		/* Update the firmware version */
		status = qla82xx_check_md_needed(vha);

		अगर (ha->fce) अणु
			ha->flags.fce_enabled = 1;
			स_रखो(ha->fce, 0,
			    fce_calc_size(ha->fce_bufs));
			rval = qla2x00_enable_fce_trace(vha,
			    ha->fce_dma, ha->fce_bufs, ha->fce_mb,
			    &ha->fce_bufs);
			अगर (rval) अणु
				ql_log(ql_log_warn, vha, 0x8001,
				    "Unable to reinitialize FCE (%d).\n",
				    rval);
				ha->flags.fce_enabled = 0;
			पूर्ण
		पूर्ण

		अगर (ha->eft) अणु
			स_रखो(ha->eft, 0, EFT_SIZE);
			rval = qla2x00_enable_eft_trace(vha,
			    ha->eft_dma, EFT_NUM_BUFFERS);
			अगर (rval) अणु
				ql_log(ql_log_warn, vha, 0x8010,
				    "Unable to reinitialize EFT (%d).\n",
				    rval);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!status) अणु
		ql_dbg(ql_dbg_taskm, vha, 0x8011,
		    "qla82xx_restart_isp succeeded.\n");

		spin_lock_irqsave(&ha->vport_slock, flags);
		list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
			अगर (vp->vp_idx) अणु
				atomic_inc(&vp->vref_count);
				spin_unlock_irqrestore(&ha->vport_slock, flags);

				qla2x00_vp_पात_isp(vp);

				spin_lock_irqsave(&ha->vport_slock, flags);
				atomic_dec(&vp->vref_count);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&ha->vport_slock, flags);

	पूर्ण अन्यथा अणु
		ql_log(ql_log_warn, vha, 0x8016,
		    "qla82xx_restart_isp **** FAILED ****.\n");
	पूर्ण

	वापस status;
पूर्ण

/*
 * qla24xx_get_fcp_prio
 *	Gets the fcp cmd priority value क्रम the logged in port.
 *	Looks क्रम a match of the port descriptors within
 *	each of the fcp prio config entries. If a match is found,
 *	the tag (priority) value is वापसed.
 *
 * Input:
 *	vha = scsi host काष्ठाure poपूर्णांकer.
 *	fcport = port काष्ठाure poपूर्णांकer.
 *
 * Return:
 *	non-zero (अगर found)
 *	-1 (अगर not found)
 *
 * Context:
 * 	Kernel context
 */
अटल पूर्णांक
qla24xx_get_fcp_prio(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक i, entries;
	uपूर्णांक8_t pid_match, wwn_match;
	पूर्णांक priority;
	uपूर्णांक32_t pid1, pid2;
	uपूर्णांक64_t wwn1, wwn2;
	काष्ठा qla_fcp_prio_entry *pri_entry;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->fcp_prio_cfg || !ha->flags.fcp_prio_enabled)
		वापस -1;

	priority = -1;
	entries = ha->fcp_prio_cfg->num_entries;
	pri_entry = &ha->fcp_prio_cfg->entry[0];

	क्रम (i = 0; i < entries; i++) अणु
		pid_match = wwn_match = 0;

		अगर (!(pri_entry->flags & FCP_PRIO_ENTRY_VALID)) अणु
			pri_entry++;
			जारी;
		पूर्ण

		/* check source pid क्रम a match */
		अगर (pri_entry->flags & FCP_PRIO_ENTRY_SPID_VALID) अणु
			pid1 = pri_entry->src_pid & INVALID_PORT_ID;
			pid2 = vha->d_id.b24 & INVALID_PORT_ID;
			अगर (pid1 == INVALID_PORT_ID)
				pid_match++;
			अन्यथा अगर (pid1 == pid2)
				pid_match++;
		पूर्ण

		/* check destination pid क्रम a match */
		अगर (pri_entry->flags & FCP_PRIO_ENTRY_DPID_VALID) अणु
			pid1 = pri_entry->dst_pid & INVALID_PORT_ID;
			pid2 = fcport->d_id.b24 & INVALID_PORT_ID;
			अगर (pid1 == INVALID_PORT_ID)
				pid_match++;
			अन्यथा अगर (pid1 == pid2)
				pid_match++;
		पूर्ण

		/* check source WWN क्रम a match */
		अगर (pri_entry->flags & FCP_PRIO_ENTRY_SWWN_VALID) अणु
			wwn1 = wwn_to_u64(vha->port_name);
			wwn2 = wwn_to_u64(pri_entry->src_wwpn);
			अगर (wwn2 == (uपूर्णांक64_t)-1)
				wwn_match++;
			अन्यथा अगर (wwn1 == wwn2)
				wwn_match++;
		पूर्ण

		/* check destination WWN क्रम a match */
		अगर (pri_entry->flags & FCP_PRIO_ENTRY_DWWN_VALID) अणु
			wwn1 = wwn_to_u64(fcport->port_name);
			wwn2 = wwn_to_u64(pri_entry->dst_wwpn);
			अगर (wwn2 == (uपूर्णांक64_t)-1)
				wwn_match++;
			अन्यथा अगर (wwn1 == wwn2)
				wwn_match++;
		पूर्ण

		अगर (pid_match == 2 || wwn_match == 2) अणु
			/* Found a matching entry */
			अगर (pri_entry->flags & FCP_PRIO_ENTRY_TAG_VALID)
				priority = pri_entry->tag;
			अवरोध;
		पूर्ण

		pri_entry++;
	पूर्ण

	वापस priority;
पूर्ण

/*
 * qla24xx_update_fcport_fcp_prio
 *	Activates fcp priority क्रम the logged in fc port
 *
 * Input:
 *	vha = scsi host काष्ठाure poपूर्णांकer.
 *	fcp = port काष्ठाure poपूर्णांकer.
 *
 * Return:
 *	QLA_SUCCESS or QLA_FUNCTION_FAILED
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla24xx_update_fcport_fcp_prio(scsi_qla_host_t *vha, fc_port_t *fcport)
अणु
	पूर्णांक ret;
	पूर्णांक priority;
	uपूर्णांक16_t mb[5];

	अगर (fcport->port_type != FCT_TARGET ||
	    fcport->loop_id == FC_NO_LOOP_ID)
		वापस QLA_FUNCTION_FAILED;

	priority = qla24xx_get_fcp_prio(vha, fcport);
	अगर (priority < 0)
		वापस QLA_FUNCTION_FAILED;

	अगर (IS_P3P_TYPE(vha->hw)) अणु
		fcport->fcp_prio = priority & 0xf;
		वापस QLA_SUCCESS;
	पूर्ण

	ret = qla24xx_set_fcp_prio(vha, fcport->loop_id, priority, mb);
	अगर (ret == QLA_SUCCESS) अणु
		अगर (fcport->fcp_prio != priority)
			ql_dbg(ql_dbg_user, vha, 0x709e,
			    "Updated FCP_CMND priority - value=%d loop_id=%d "
			    "port_id=%02x%02x%02x.\n", priority,
			    fcport->loop_id, fcport->d_id.b.करोमुख्य,
			    fcport->d_id.b.area, fcport->d_id.b.al_pa);
		fcport->fcp_prio = priority & 0xf;
	पूर्ण अन्यथा
		ql_dbg(ql_dbg_user, vha, 0x704f,
		    "Unable to update FCP_CMND priority - ret=0x%x for "
		    "loop_id=%d port_id=%02x%02x%02x.\n", ret, fcport->loop_id,
		    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa);
	वापस  ret;
पूर्ण

/*
 * qla24xx_update_all_fcp_prio
 *	Activates fcp priority क्रम all the logged in ports
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *
 * Return:
 *	QLA_SUCCESS or QLA_FUNCTION_FAILED
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla24xx_update_all_fcp_prio(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret;
	fc_port_t *fcport;

	ret = QLA_FUNCTION_FAILED;
	/* We need to set priority क्रम all logged in ports */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list)
		ret = qla24xx_update_fcport_fcp_prio(vha, fcport);

	वापस ret;
पूर्ण

काष्ठा qla_qpair *qla2xxx_create_qpair(काष्ठा scsi_qla_host *vha, पूर्णांक qos,
	पूर्णांक vp_idx, bool startqp)
अणु
	पूर्णांक rsp_id = 0;
	पूर्णांक  req_id = 0;
	पूर्णांक i;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t qpair_id = 0;
	काष्ठा qla_qpair *qpair = शून्य;
	काष्ठा qla_msix_entry *msix;

	अगर (!(ha->fw_attributes & BIT_6) || !ha->flags.msix_enabled) अणु
		ql_log(ql_log_warn, vha, 0x00181,
		    "FW/Driver is not multi-queue capable.\n");
		वापस शून्य;
	पूर्ण

	अगर (ql2xmqsupport || ql2xnvmeenable) अणु
		qpair = kzalloc(माप(काष्ठा qla_qpair), GFP_KERNEL);
		अगर (qpair == शून्य) अणु
			ql_log(ql_log_warn, vha, 0x0182,
			    "Failed to allocate memory for queue pair.\n");
			वापस शून्य;
		पूर्ण

		qpair->hw = vha->hw;
		qpair->vha = vha;
		qpair->qp_lock_ptr = &qpair->qp_lock;
		spin_lock_init(&qpair->qp_lock);
		qpair->use_shaकरोw_reg = IS_SHADOW_REG_CAPABLE(ha) ? 1 : 0;

		/* Assign available que pair id */
		mutex_lock(&ha->mq_lock);
		qpair_id = find_first_zero_bit(ha->qpair_qid_map, ha->max_qpairs);
		अगर (ha->num_qpairs >= ha->max_qpairs) अणु
			mutex_unlock(&ha->mq_lock);
			ql_log(ql_log_warn, vha, 0x0183,
			    "No resources to create additional q pair.\n");
			जाओ fail_qid_map;
		पूर्ण
		ha->num_qpairs++;
		set_bit(qpair_id, ha->qpair_qid_map);
		ha->queue_pair_map[qpair_id] = qpair;
		qpair->id = qpair_id;
		qpair->vp_idx = vp_idx;
		qpair->fw_started = ha->flags.fw_started;
		INIT_LIST_HEAD(&qpair->hपूर्णांकs_list);
		qpair->chip_reset = ha->base_qpair->chip_reset;
		qpair->enable_class_2 = ha->base_qpair->enable_class_2;
		qpair->enable_explicit_conf =
		    ha->base_qpair->enable_explicit_conf;

		क्रम (i = 0; i < ha->msix_count; i++) अणु
			msix = &ha->msix_entries[i];
			अगर (msix->in_use)
				जारी;
			qpair->msix = msix;
			ql_dbg(ql_dbg_multiq, vha, 0xc00f,
			    "Vector %x selected for qpair\n", msix->vector);
			अवरोध;
		पूर्ण
		अगर (!qpair->msix) अणु
			ql_log(ql_log_warn, vha, 0x0184,
			    "Out of MSI-X vectors!.\n");
			जाओ fail_msix;
		पूर्ण

		qpair->msix->in_use = 1;
		list_add_tail(&qpair->qp_list_elem, &vha->qp_list);
		qpair->pdev = ha->pdev;
		अगर (IS_QLA27XX(ha) || IS_QLA83XX(ha) || IS_QLA28XX(ha))
			qpair->reqq_start_iocbs = qla_83xx_start_iocbs;

		mutex_unlock(&ha->mq_lock);

		/* Create response queue first */
		rsp_id = qla25xx_create_rsp_que(ha, 0, 0, 0, qpair, startqp);
		अगर (!rsp_id) अणु
			ql_log(ql_log_warn, vha, 0x0185,
			    "Failed to create response queue.\n");
			जाओ fail_rsp;
		पूर्ण

		qpair->rsp = ha->rsp_q_map[rsp_id];

		/* Create request queue */
		req_id = qla25xx_create_req_que(ha, 0, vp_idx, 0, rsp_id, qos,
		    startqp);
		अगर (!req_id) अणु
			ql_log(ql_log_warn, vha, 0x0186,
			    "Failed to create request queue.\n");
			जाओ fail_req;
		पूर्ण

		qpair->req = ha->req_q_map[req_id];
		qpair->rsp->req = qpair->req;
		qpair->rsp->qpair = qpair;
		/* init qpair to this cpu. Will adjust at run समय. */
		qla_cpu_update(qpair, smp_processor_id());

		अगर (IS_T10_PI_CAPABLE(ha) && ql2xenabledअगर) अणु
			अगर (ha->fw_attributes & BIT_4)
				qpair->dअगरdix_supported = 1;
		पूर्ण

		qpair->srb_mempool = mempool_create_slab_pool(SRB_MIN_REQ, srb_cachep);
		अगर (!qpair->srb_mempool) अणु
			ql_log(ql_log_warn, vha, 0xd036,
			    "Failed to create srb mempool for qpair %d\n",
			    qpair->id);
			जाओ fail_mempool;
		पूर्ण

		/* Mark as online */
		qpair->online = 1;

		अगर (!vha->flags.qpairs_available)
			vha->flags.qpairs_available = 1;

		ql_dbg(ql_dbg_multiq, vha, 0xc00d,
		    "Request/Response queue pair created, id %d\n",
		    qpair->id);
		ql_dbg(ql_dbg_init, vha, 0x0187,
		    "Request/Response queue pair created, id %d\n",
		    qpair->id);
	पूर्ण
	वापस qpair;

fail_mempool:
fail_req:
	qla25xx_delete_rsp_que(vha, qpair->rsp);
fail_rsp:
	mutex_lock(&ha->mq_lock);
	qpair->msix->in_use = 0;
	list_del(&qpair->qp_list_elem);
	अगर (list_empty(&vha->qp_list))
		vha->flags.qpairs_available = 0;
fail_msix:
	ha->queue_pair_map[qpair_id] = शून्य;
	clear_bit(qpair_id, ha->qpair_qid_map);
	ha->num_qpairs--;
	mutex_unlock(&ha->mq_lock);
fail_qid_map:
	kमुक्त(qpair);
	वापस शून्य;
पूर्ण

पूर्णांक qla2xxx_delete_qpair(काष्ठा scsi_qla_host *vha, काष्ठा qla_qpair *qpair)
अणु
	पूर्णांक ret = QLA_FUNCTION_FAILED;
	काष्ठा qla_hw_data *ha = qpair->hw;

	qpair->delete_in_progress = 1;

	ret = qla25xx_delete_req_que(vha, qpair->req);
	अगर (ret != QLA_SUCCESS)
		जाओ fail;

	ret = qla25xx_delete_rsp_que(vha, qpair->rsp);
	अगर (ret != QLA_SUCCESS)
		जाओ fail;

	mutex_lock(&ha->mq_lock);
	ha->queue_pair_map[qpair->id] = शून्य;
	clear_bit(qpair->id, ha->qpair_qid_map);
	ha->num_qpairs--;
	list_del(&qpair->qp_list_elem);
	अगर (list_empty(&vha->qp_list)) अणु
		vha->flags.qpairs_available = 0;
		vha->flags.qpairs_req_created = 0;
		vha->flags.qpairs_rsp_created = 0;
	पूर्ण
	mempool_destroy(qpair->srb_mempool);
	kमुक्त(qpair);
	mutex_unlock(&ha->mq_lock);

	वापस QLA_SUCCESS;
fail:
	वापस ret;
पूर्ण

uपूर्णांक64_t
qla2x00_count_set_bits(uपूर्णांक32_t num)
अणु
	/* Brian Kernighan's Algorithm */
	u64 count = 0;

	जबतक (num) अणु
		num &= (num - 1);
		count++;
	पूर्ण
	वापस count;
पूर्ण

uपूर्णांक64_t
qla2x00_get_num_tgts(scsi_qla_host_t *vha)
अणु
	fc_port_t *f, *tf;
	u64 count = 0;

	f = शून्य;
	tf = शून्य;

	list_क्रम_each_entry_safe(f, tf, &vha->vp_fcports, list) अणु
		अगर (f->port_type != FCT_TARGET)
			जारी;
		count++;
	पूर्ण
	वापस count;
पूर्ण

पूर्णांक qla2xxx_reset_stats(काष्ठा Scsi_Host *host, u32 flags)
अणु
	scsi_qla_host_t *vha = shost_priv(host);
	fc_port_t *fcport = शून्य;
	अचिन्हित दीर्घ पूर्णांक_flags;

	अगर (flags & QLA2XX_HW_ERROR)
		vha->hw_err_cnt = 0;
	अगर (flags & QLA2XX_SHT_LNK_DWN)
		vha->लघु_link_करोwn_cnt = 0;
	अगर (flags & QLA2XX_INT_ERR)
		vha->पूर्णांकerface_err_cnt = 0;
	अगर (flags & QLA2XX_CMD_TIMEOUT)
		vha->cmd_समयout_cnt = 0;
	अगर (flags & QLA2XX_RESET_CMD_ERR)
		vha->reset_cmd_err_cnt = 0;
	अगर (flags & QLA2XX_TGT_SHT_LNK_DOWN) अणु
		spin_lock_irqsave(&vha->hw->tgt.sess_lock, पूर्णांक_flags);
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			fcport->tgt_लघु_link_करोwn_cnt = 0;
			fcport->tgt_link_करोwn_समय = QLA2XX_MAX_LINK_DOWN_TIME;
		पूर्ण
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, पूर्णांक_flags);
	पूर्ण
	vha->link_करोwn_समय = QLA2XX_MAX_LINK_DOWN_TIME;
	वापस 0;
पूर्ण

पूर्णांक qla2xxx_start_stats(काष्ठा Scsi_Host *host, u32 flags)
अणु
	वापस qla2xxx_reset_stats(host, flags);
पूर्ण

पूर्णांक qla2xxx_stop_stats(काष्ठा Scsi_Host *host, u32 flags)
अणु
	वापस qla2xxx_reset_stats(host, flags);
पूर्ण

पूर्णांक qla2xxx_get_ini_stats(काष्ठा Scsi_Host *host, u32 flags,
			  व्योम *data, u64 size)
अणु
	scsi_qla_host_t *vha = shost_priv(host);
	काष्ठा ql_vnd_host_stats_resp *resp = (काष्ठा ql_vnd_host_stats_resp *)data;
	काष्ठा ql_vnd_stats *rsp_data = &resp->stats;
	u64 ini_entry_count = 0;
	u64 i = 0;
	u64 entry_count = 0;
	u64 num_tgt = 0;
	u32 पंचांगp_stat_type = 0;
	fc_port_t *fcport = शून्य;
	अचिन्हित दीर्घ पूर्णांक_flags;

	/* Copy stat type to work on it */
	पंचांगp_stat_type = flags;

	अगर (पंचांगp_stat_type & BIT_17) अणु
		num_tgt = qla2x00_get_num_tgts(vha);
		/* unset BIT_17 */
		पंचांगp_stat_type &= ~(1 << 17);
	पूर्ण
	ini_entry_count = qla2x00_count_set_bits(पंचांगp_stat_type);

	entry_count = ini_entry_count + num_tgt;

	rsp_data->entry_count = entry_count;

	i = 0;
	अगर (flags & QLA2XX_HW_ERROR) अणु
		rsp_data->entry[i].stat_type = QLA2XX_HW_ERROR;
		rsp_data->entry[i].tgt_num = 0x0;
		rsp_data->entry[i].cnt = vha->hw_err_cnt;
		i++;
	पूर्ण

	अगर (flags & QLA2XX_SHT_LNK_DWN) अणु
		rsp_data->entry[i].stat_type = QLA2XX_SHT_LNK_DWN;
		rsp_data->entry[i].tgt_num = 0x0;
		rsp_data->entry[i].cnt = vha->लघु_link_करोwn_cnt;
		i++;
	पूर्ण

	अगर (flags & QLA2XX_INT_ERR) अणु
		rsp_data->entry[i].stat_type = QLA2XX_INT_ERR;
		rsp_data->entry[i].tgt_num = 0x0;
		rsp_data->entry[i].cnt = vha->पूर्णांकerface_err_cnt;
		i++;
	पूर्ण

	अगर (flags & QLA2XX_CMD_TIMEOUT) अणु
		rsp_data->entry[i].stat_type = QLA2XX_CMD_TIMEOUT;
		rsp_data->entry[i].tgt_num = 0x0;
		rsp_data->entry[i].cnt = vha->cmd_समयout_cnt;
		i++;
	पूर्ण

	अगर (flags & QLA2XX_RESET_CMD_ERR) अणु
		rsp_data->entry[i].stat_type = QLA2XX_RESET_CMD_ERR;
		rsp_data->entry[i].tgt_num = 0x0;
		rsp_data->entry[i].cnt = vha->reset_cmd_err_cnt;
		i++;
	पूर्ण

	/* i will जारी from previous loop, as target
	 * entries are after initiator
	 */
	अगर (flags & QLA2XX_TGT_SHT_LNK_DOWN) अणु
		spin_lock_irqsave(&vha->hw->tgt.sess_lock, पूर्णांक_flags);
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (fcport->port_type != FCT_TARGET)
				जारी;
			अगर (!fcport->rport)
				जारी;
			rsp_data->entry[i].stat_type = QLA2XX_TGT_SHT_LNK_DOWN;
			rsp_data->entry[i].tgt_num = fcport->rport->number;
			rsp_data->entry[i].cnt = fcport->tgt_लघु_link_करोwn_cnt;
			i++;
		पूर्ण
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, पूर्णांक_flags);
	पूर्ण
	resp->status = EXT_STATUS_OK;

	वापस 0;
पूर्ण

पूर्णांक qla2xxx_get_tgt_stats(काष्ठा Scsi_Host *host, u32 flags,
			  काष्ठा fc_rport *rport, व्योम *data, u64 size)
अणु
	काष्ठा ql_vnd_tgt_stats_resp *tgt_data = data;
	fc_port_t *fcport = *(fc_port_t **)rport->dd_data;

	tgt_data->status = 0;
	tgt_data->stats.entry_count = 1;
	tgt_data->stats.entry[0].stat_type = flags;
	tgt_data->stats.entry[0].tgt_num = rport->number;
	tgt_data->stats.entry[0].cnt = fcport->tgt_लघु_link_करोwn_cnt;

	वापस 0;
पूर्ण

पूर्णांक qla2xxx_disable_port(काष्ठा Scsi_Host *host)
अणु
	scsi_qla_host_t *vha = shost_priv(host);

	vha->hw->flags.port_isolated = 1;

	अगर (qla2x00_chip_is_करोwn(vha))
		वापस 0;

	अगर (vha->flags.online) अणु
		qla2x00_पात_isp_cleanup(vha);
		qla2x00_रुको_क्रम_sess_deletion(vha);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक qla2xxx_enable_port(काष्ठा Scsi_Host *host)
अणु
	scsi_qla_host_t *vha = shost_priv(host);

	vha->hw->flags.port_isolated = 0;
	/* Set the flag to 1, so that isp_पात can proceed */
	vha->flags.online = 1;
	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);

	वापस 0;
पूर्ण
