<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  qla_target.c SCSI LLD infraकाष्ठाure क्रम QLogic 22xx/23xx/24xx/25xx
 *
 *  based on qla2x00t.c code:
 *
 *  Copyright (C) 2004 - 2010 Vladislav Bolkhovitin <vst@vlnb.net>
 *  Copyright (C) 2004 - 2005 Leonid Stoljar
 *  Copyright (C) 2006 Nathaniel Clark <nate@misrule.us>
 *  Copyright (C) 2006 - 2010 ID7 Ltd.
 *
 *  Forward port and refactoring to modern qla2xxx and target/configfs
 *
 *  Copyright (C) 2010-2013 Nicholas A. Bellinger <nab@kernel.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/types.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/list.h>
#समावेश <linux/workqueue.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_tcq.h>

#समावेश "qla_def.h"
#समावेश "qla_target.h"

अटल पूर्णांक ql2xtgt_tape_enable;
module_param(ql2xtgt_tape_enable, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql2xtgt_tape_enable,
		"Enables Sequence level error recovery (aka FC Tape). Default is 0 - no SLER. 1 - Enable SLER.");

अटल अक्षर *qlini_mode = QLA2XXX_INI_MODE_STR_ENABLED;
module_param(qlini_mode, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(qlini_mode,
	"Determines when initiator mode will be enabled. Possible values: "
	"\"exclusive\" - initiator mode will be enabled on load, "
	"disabled on enabling target mode and then on disabling target mode "
	"enabled back; "
	"\"disabled\" - initiator mode will never be enabled; "
	"\"dual\" - Initiator Modes will be enabled. Target Mode can be activated "
	"when ready "
	"\"enabled\" (default) - initiator mode will always stay enabled.");

अटल पूर्णांक ql_dm_tgt_ex_pct = 0;
module_param(ql_dm_tgt_ex_pct, पूर्णांक, S_IRUGO|S_IWUSR);
MODULE_PARM_DESC(ql_dm_tgt_ex_pct,
	"For Dual Mode (qlini_mode=dual), this parameter determines "
	"the percentage of exchanges/cmds FW will allocate resources "
	"for Target mode.");

पूर्णांक ql2xuctrlirq = 1;
module_param(ql2xuctrlirq, पूर्णांक, 0644);
MODULE_PARM_DESC(ql2xuctrlirq,
    "User to control IRQ placement via smp_affinity."
    "Valid with qlini_mode=disabled."
    "1(default): enable");

पूर्णांक ql2x_ini_mode = QLA2XXX_INI_MODE_EXCLUSIVE;

अटल पूर्णांक qla_sam_status = SAM_STAT_BUSY;
अटल पूर्णांक tc_sam_status = SAM_STAT_TASK_SET_FULL; /* target core */

/*
 * From scsi/fc/fc_fcp.h
 */
क्रमागत fcp_resp_rsp_codes अणु
	FCP_TMF_CMPL = 0,
	FCP_DATA_LEN_INVALID = 1,
	FCP_CMND_FIELDS_INVALID = 2,
	FCP_DATA_PARAM_MISMATCH = 3,
	FCP_TMF_REJECTED = 4,
	FCP_TMF_FAILED = 5,
	FCP_TMF_INVALID_LUN = 9,
पूर्ण;

/*
 * fc_pri_ta from scsi/fc/fc_fcp.h
 */
#घोषणा FCP_PTA_SIMPLE      0   /* simple task attribute */
#घोषणा FCP_PTA_HEADQ       1   /* head of queue task attribute */
#घोषणा FCP_PTA_ORDERED     2   /* ordered task attribute */
#घोषणा FCP_PTA_ACA         4   /* स्वतः. contingent allegiance */
#घोषणा FCP_PTA_MASK        7   /* mask क्रम task attribute field */
#घोषणा FCP_PRI_SHIFT       3   /* priority field starts in bit 3 */
#घोषणा FCP_PRI_RESVD_MASK  0x80        /* reserved bits in priority field */

/*
 * This driver calls qla2x00_alloc_iocbs() and qla2x00_issue_marker(), which
 * must be called under HW lock and could unlock/lock it inside.
 * It isn't an issue, since in the current implementation on the समय when
 * those functions are called:
 *
 *   - Either context is IRQ and only IRQ handler can modअगरy HW data,
 *     including rings related fields,
 *
 *   - Or access to target mode variables from काष्ठा qla_tgt करोesn't
 *     cross those functions boundaries, except tgt_stop, which
 *     additionally रक्षित by irq_cmd_count.
 */
/* Predefs क्रम callbacks handed to qla2xxx LLD */
अटल व्योम qlt_24xx_atio_pkt(काष्ठा scsi_qla_host *ha,
	काष्ठा atio_from_isp *pkt, uपूर्णांक8_t);
अटल व्योम qlt_response_pkt(काष्ठा scsi_qla_host *ha, काष्ठा rsp_que *rsp,
	response_t *pkt);
अटल पूर्णांक qlt_issue_task_mgmt(काष्ठा fc_port *sess, u64 lun,
	पूर्णांक fn, व्योम *iocb, पूर्णांक flags);
अटल व्योम qlt_send_term_exchange(काष्ठा qla_qpair *, काष्ठा qla_tgt_cmd
	*cmd, काष्ठा atio_from_isp *atio, पूर्णांक ha_locked, पूर्णांक ul_पात);
अटल व्योम qlt_alloc_qfull_cmd(काष्ठा scsi_qla_host *vha,
	काष्ठा atio_from_isp *atio, uपूर्णांक16_t status, पूर्णांक qfull);
अटल व्योम qlt_disable_vha(काष्ठा scsi_qla_host *vha);
अटल व्योम qlt_clear_tgt_db(काष्ठा qla_tgt *tgt);
अटल व्योम qlt_send_notअगरy_ack(काष्ठा qla_qpair *qpair,
	काष्ठा imm_ntfy_from_isp *ntfy,
	uपूर्णांक32_t add_flags, uपूर्णांक16_t resp_code, पूर्णांक resp_code_valid,
	uपूर्णांक16_t srr_flags, uपूर्णांक16_t srr_reject_code, uपूर्णांक8_t srr_explan);
अटल व्योम qlt_send_term_imm_notअगर(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *imm, पूर्णांक ha_locked);
अटल काष्ठा fc_port *qlt_create_sess(काष्ठा scsi_qla_host *vha,
	fc_port_t *fcport, bool local);
व्योम qlt_unreg_sess(काष्ठा fc_port *sess);
अटल व्योम qlt_24xx_handle_abts(काष्ठा scsi_qla_host *,
	काष्ठा abts_recv_from_24xx *);
अटल व्योम qlt_send_busy(काष्ठा qla_qpair *, काष्ठा atio_from_isp *,
    uपूर्णांक16_t);
अटल पूर्णांक qlt_check_reserve_मुक्त_req(काष्ठा qla_qpair *qpair, uपूर्णांक32_t);
अटल अंतरभूत uपूर्णांक32_t qlt_make_handle(काष्ठा qla_qpair *);

/*
 * Global Variables
 */
अटल काष्ठा kmem_cache *qla_tgt_mgmt_cmd_cachep;
काष्ठा kmem_cache *qla_tgt_plogi_cachep;
अटल mempool_t *qla_tgt_mgmt_cmd_mempool;
अटल काष्ठा workqueue_काष्ठा *qla_tgt_wq;
अटल DEFINE_MUTEX(qla_tgt_mutex);
अटल LIST_HEAD(qla_tgt_glist);

अटल स्थिर अक्षर *prot_op_str(u32 prot_op)
अणु
	चयन (prot_op) अणु
	हाल TARGET_PROT_NORMAL:	वापस "NORMAL";
	हाल TARGET_PROT_DIN_INSERT:	वापस "DIN_INSERT";
	हाल TARGET_PROT_DOUT_INSERT:	वापस "DOUT_INSERT";
	हाल TARGET_PROT_DIN_STRIP:	वापस "DIN_STRIP";
	हाल TARGET_PROT_DOUT_STRIP:	वापस "DOUT_STRIP";
	हाल TARGET_PROT_DIN_PASS:	वापस "DIN_PASS";
	हाल TARGET_PROT_DOUT_PASS:	वापस "DOUT_PASS";
	शेष:			वापस "UNKNOWN";
	पूर्ण
पूर्ण

/* This API पूर्णांकentionally takes dest as a parameter, rather than वापसing
 * पूर्णांक value to aव्योम caller क्रमgetting to issue wmb() after the store */
व्योम qlt_करो_generation_tick(काष्ठा scsi_qla_host *vha, पूर्णांक *dest)
अणु
	scsi_qla_host_t *base_vha = pci_get_drvdata(vha->hw->pdev);
	*dest = atomic_inc_वापस(&base_vha->generation_tick);
	/* memory barrier */
	wmb();
पूर्ण

/* Might release hw lock, then reaquire!! */
अटल अंतरभूत पूर्णांक qlt_issue_marker(काष्ठा scsi_qla_host *vha, पूर्णांक vha_locked)
अणु
	/* Send marker अगर required */
	अगर (unlikely(vha->marker_needed != 0)) अणु
		पूर्णांक rc = qla2x00_issue_marker(vha, vha_locked);

		अगर (rc != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe03d,
			    "qla_target(%d): issue_marker() failed\n",
			    vha->vp_idx);
		पूर्ण
		वापस rc;
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

अटल अंतरभूत
काष्ठा scsi_qla_host *qlt_find_host_by_d_id(काष्ठा scsi_qla_host *vha,
					    be_id_t d_id)
अणु
	काष्ठा scsi_qla_host *host;
	uपूर्णांक32_t key;

	अगर (vha->d_id.b.area == d_id.area &&
	    vha->d_id.b.करोमुख्य == d_id.करोमुख्य &&
	    vha->d_id.b.al_pa == d_id.al_pa)
		वापस vha;

	key = be_to_port_id(d_id).b24;

	host = btree_lookup32(&vha->hw->tgt.host_map, key);
	अगर (!host)
		ql_dbg(ql_dbg_tgt_mgt + ql_dbg_verbose, vha, 0xf005,
		    "Unable to find host %06x\n", key);

	वापस host;
पूर्ण

अटल अंतरभूत
काष्ठा scsi_qla_host *qlt_find_host_by_vp_idx(काष्ठा scsi_qla_host *vha,
	uपूर्णांक16_t vp_idx)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->vp_idx == vp_idx)
		वापस vha;

	BUG_ON(ha->tgt.tgt_vp_map == शून्य);
	अगर (likely(test_bit(vp_idx, ha->vp_idx_map)))
		वापस ha->tgt.tgt_vp_map[vp_idx].vha;

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम qlt_incr_num_pend_cmds(काष्ठा scsi_qla_host *vha)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vha->hw->tgt.q_full_lock, flags);

	vha->hw->tgt.num_pend_cmds++;
	अगर (vha->hw->tgt.num_pend_cmds > vha->qla_stats.stat_max_pend_cmds)
		vha->qla_stats.stat_max_pend_cmds =
			vha->hw->tgt.num_pend_cmds;
	spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);
पूर्ण
अटल अंतरभूत व्योम qlt_decr_num_pend_cmds(काष्ठा scsi_qla_host *vha)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vha->hw->tgt.q_full_lock, flags);
	vha->hw->tgt.num_pend_cmds--;
	spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);
पूर्ण


अटल व्योम qlt_queue_unknown_atio(scsi_qla_host_t *vha,
	काष्ठा atio_from_isp *atio, uपूर्णांक8_t ha_locked)
अणु
	काष्ठा qla_tgt_sess_op *u;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	अचिन्हित दीर्घ flags;

	अगर (tgt->tgt_stop) अणु
		ql_dbg(ql_dbg_async, vha, 0x502c,
		    "qla_target(%d): dropping unknown ATIO_TYPE7, because tgt is being stopped",
		    vha->vp_idx);
		जाओ out_term;
	पूर्ण

	u = kzalloc(माप(*u), GFP_ATOMIC);
	अगर (u == शून्य)
		जाओ out_term;

	u->vha = vha;
	स_नकल(&u->atio, atio, माप(*atio));
	INIT_LIST_HEAD(&u->cmd_list);

	spin_lock_irqsave(&vha->cmd_list_lock, flags);
	list_add_tail(&u->cmd_list, &vha->unknown_atio_list);
	spin_unlock_irqrestore(&vha->cmd_list_lock, flags);

	schedule_delayed_work(&vha->unknown_atio_work, 1);

out:
	वापस;

out_term:
	qlt_send_term_exchange(vha->hw->base_qpair, शून्य, atio, ha_locked, 0);
	जाओ out;
पूर्ण

अटल व्योम qlt_try_to_dequeue_unknown_atios(काष्ठा scsi_qla_host *vha,
	uपूर्णांक8_t ha_locked)
अणु
	काष्ठा qla_tgt_sess_op *u, *t;
	scsi_qla_host_t *host;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	अचिन्हित दीर्घ flags;
	uपूर्णांक8_t queued = 0;

	list_क्रम_each_entry_safe(u, t, &vha->unknown_atio_list, cmd_list) अणु
		अगर (u->पातed) अणु
			ql_dbg(ql_dbg_async, vha, 0x502e,
			    "Freeing unknown %s %p, because of Abort\n",
			    "ATIO_TYPE7", u);
			qlt_send_term_exchange(vha->hw->base_qpair, शून्य,
			    &u->atio, ha_locked, 0);
			जाओ पात;
		पूर्ण

		host = qlt_find_host_by_d_id(vha, u->atio.u.isp24.fcp_hdr.d_id);
		अगर (host != शून्य) अणु
			ql_dbg(ql_dbg_async + ql_dbg_verbose, vha, 0x502f,
			    "Requeuing unknown ATIO_TYPE7 %p\n", u);
			qlt_24xx_atio_pkt(host, &u->atio, ha_locked);
		पूर्ण अन्यथा अगर (tgt->tgt_stop) अणु
			ql_dbg(ql_dbg_async + ql_dbg_verbose, vha, 0x503a,
			    "Freeing unknown %s %p, because tgt is being stopped\n",
			    "ATIO_TYPE7", u);
			qlt_send_term_exchange(vha->hw->base_qpair, शून्य,
			    &u->atio, ha_locked, 0);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_async + ql_dbg_verbose, vha, 0x503d,
			    "Reschedule u %p, vha %p, host %p\n", u, vha, host);
			अगर (!queued) अणु
				queued = 1;
				schedule_delayed_work(&vha->unknown_atio_work,
				    1);
			पूर्ण
			जारी;
		पूर्ण

पात:
		spin_lock_irqsave(&vha->cmd_list_lock, flags);
		list_del(&u->cmd_list);
		spin_unlock_irqrestore(&vha->cmd_list_lock, flags);
		kमुक्त(u);
	पूर्ण
पूर्ण

व्योम qlt_unknown_atio_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा scsi_qla_host *vha = container_of(to_delayed_work(work),
	    काष्ठा scsi_qla_host, unknown_atio_work);

	qlt_try_to_dequeue_unknown_atios(vha, 0);
पूर्ण

अटल bool qlt_24xx_atio_pkt_all_vps(काष्ठा scsi_qla_host *vha,
	काष्ठा atio_from_isp *atio, uपूर्णांक8_t ha_locked)
अणु
	ql_dbg(ql_dbg_tgt, vha, 0xe072,
		"%s: qla_target(%d): type %x ox_id %04x\n",
		__func__, vha->vp_idx, atio->u.raw.entry_type,
		be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id));

	चयन (atio->u.raw.entry_type) अणु
	हाल ATIO_TYPE7:
	अणु
		काष्ठा scsi_qla_host *host = qlt_find_host_by_d_id(vha,
		    atio->u.isp24.fcp_hdr.d_id);
		अगर (unlikely(शून्य == host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe03e,
			    "qla_target(%d): Received ATIO_TYPE7 "
			    "with unknown d_id %x:%x:%x\n", vha->vp_idx,
			    atio->u.isp24.fcp_hdr.d_id.करोमुख्य,
			    atio->u.isp24.fcp_hdr.d_id.area,
			    atio->u.isp24.fcp_hdr.d_id.al_pa);


			qlt_queue_unknown_atio(vha, atio, ha_locked);
			अवरोध;
		पूर्ण
		अगर (unlikely(!list_empty(&vha->unknown_atio_list)))
			qlt_try_to_dequeue_unknown_atios(vha, ha_locked);

		qlt_24xx_atio_pkt(host, atio, ha_locked);
		अवरोध;
	पूर्ण

	हाल IMMED_NOTIFY_TYPE:
	अणु
		काष्ठा scsi_qla_host *host = vha;
		काष्ठा imm_ntfy_from_isp *entry =
		    (काष्ठा imm_ntfy_from_isp *)atio;

		qlt_issue_marker(vha, ha_locked);

		अगर ((entry->u.isp24.vp_index != 0xFF) &&
		    (entry->u.isp24.nport_handle != cpu_to_le16(0xFFFF))) अणु
			host = qlt_find_host_by_vp_idx(vha,
			    entry->u.isp24.vp_index);
			अगर (unlikely(!host)) अणु
				ql_dbg(ql_dbg_tgt, vha, 0xe03f,
				    "qla_target(%d): Received "
				    "ATIO (IMMED_NOTIFY_TYPE) "
				    "with unknown vp_index %d\n",
				    vha->vp_idx, entry->u.isp24.vp_index);
				अवरोध;
			पूर्ण
		पूर्ण
		qlt_24xx_atio_pkt(host, atio, ha_locked);
		अवरोध;
	पूर्ण

	हाल VP_RPT_ID_IOCB_TYPE:
		qla24xx_report_id_acquisition(vha,
			(काष्ठा vp_rpt_id_entry_24xx *)atio);
		अवरोध;

	हाल ABTS_RECV_24XX:
	अणु
		काष्ठा abts_recv_from_24xx *entry =
			(काष्ठा abts_recv_from_24xx *)atio;
		काष्ठा scsi_qla_host *host = qlt_find_host_by_vp_idx(vha,
			entry->vp_index);
		अचिन्हित दीर्घ flags;

		अगर (unlikely(!host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe00a,
			    "qla_target(%d): Response pkt (ABTS_RECV_24XX) "
			    "received, with unknown vp_index %d\n",
			    vha->vp_idx, entry->vp_index);
			अवरोध;
		पूर्ण
		अगर (!ha_locked)
			spin_lock_irqsave(&host->hw->hardware_lock, flags);
		qlt_24xx_handle_abts(host, (काष्ठा abts_recv_from_24xx *)atio);
		अगर (!ha_locked)
			spin_unlock_irqrestore(&host->hw->hardware_lock, flags);
		अवरोध;
	पूर्ण

	/* हाल PUREX_IOCB_TYPE: ql2xmvasynctoatio */

	शेष:
		ql_dbg(ql_dbg_tgt, vha, 0xe040,
		    "qla_target(%d): Received unknown ATIO atio "
		    "type %x\n", vha->vp_idx, atio->u.raw.entry_type);
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

व्योम qlt_response_pkt_all_vps(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp, response_t *pkt)
अणु
	चयन (pkt->entry_type) अणु
	हाल CTIO_CRC2:
		ql_dbg(ql_dbg_tgt, vha, 0xe073,
			"qla_target(%d):%s: CRC2 Response pkt\n",
			vha->vp_idx, __func__);
		fallthrough;
	हाल CTIO_TYPE7:
	अणु
		काष्ठा ctio7_from_24xx *entry = (काष्ठा ctio7_from_24xx *)pkt;
		काष्ठा scsi_qla_host *host = qlt_find_host_by_vp_idx(vha,
		    entry->vp_index);
		अगर (unlikely(!host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe041,
			    "qla_target(%d): Response pkt (CTIO_TYPE7) "
			    "received, with unknown vp_index %d\n",
			    vha->vp_idx, entry->vp_index);
			अवरोध;
		पूर्ण
		qlt_response_pkt(host, rsp, pkt);
		अवरोध;
	पूर्ण

	हाल IMMED_NOTIFY_TYPE:
	अणु
		काष्ठा scsi_qla_host *host;
		काष्ठा imm_ntfy_from_isp *entry =
		    (काष्ठा imm_ntfy_from_isp *)pkt;

		host = qlt_find_host_by_vp_idx(vha, entry->u.isp24.vp_index);
		अगर (unlikely(!host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe042,
			    "qla_target(%d): Response pkt (IMMED_NOTIFY_TYPE) "
			    "received, with unknown vp_index %d\n",
			    vha->vp_idx, entry->u.isp24.vp_index);
			अवरोध;
		पूर्ण
		qlt_response_pkt(host, rsp, pkt);
		अवरोध;
	पूर्ण

	हाल NOTIFY_ACK_TYPE:
	अणु
		काष्ठा scsi_qla_host *host = vha;
		काष्ठा nack_to_isp *entry = (काष्ठा nack_to_isp *)pkt;

		अगर (0xFF != entry->u.isp24.vp_index) अणु
			host = qlt_find_host_by_vp_idx(vha,
			    entry->u.isp24.vp_index);
			अगर (unlikely(!host)) अणु
				ql_dbg(ql_dbg_tgt, vha, 0xe043,
				    "qla_target(%d): Response "
				    "pkt (NOTIFY_ACK_TYPE) "
				    "received, with unknown "
				    "vp_index %d\n", vha->vp_idx,
				    entry->u.isp24.vp_index);
				अवरोध;
			पूर्ण
		पूर्ण
		qlt_response_pkt(host, rsp, pkt);
		अवरोध;
	पूर्ण

	हाल ABTS_RECV_24XX:
	अणु
		काष्ठा abts_recv_from_24xx *entry =
		    (काष्ठा abts_recv_from_24xx *)pkt;
		काष्ठा scsi_qla_host *host = qlt_find_host_by_vp_idx(vha,
		    entry->vp_index);
		अगर (unlikely(!host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe044,
			    "qla_target(%d): Response pkt "
			    "(ABTS_RECV_24XX) received, with unknown "
			    "vp_index %d\n", vha->vp_idx, entry->vp_index);
			अवरोध;
		पूर्ण
		qlt_response_pkt(host, rsp, pkt);
		अवरोध;
	पूर्ण

	हाल ABTS_RESP_24XX:
	अणु
		काष्ठा abts_resp_to_24xx *entry =
		    (काष्ठा abts_resp_to_24xx *)pkt;
		काष्ठा scsi_qla_host *host = qlt_find_host_by_vp_idx(vha,
		    entry->vp_index);
		अगर (unlikely(!host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe045,
			    "qla_target(%d): Response pkt "
			    "(ABTS_RECV_24XX) received, with unknown "
			    "vp_index %d\n", vha->vp_idx, entry->vp_index);
			अवरोध;
		पूर्ण
		qlt_response_pkt(host, rsp, pkt);
		अवरोध;
	पूर्ण
	शेष:
		qlt_response_pkt(vha, rsp, pkt);
		अवरोध;
	पूर्ण

पूर्ण

/*
 * All qlt_plogi_ack_t operations are रक्षित by hardware_lock
 */
अटल पूर्णांक qla24xx_post_nack_work(काष्ठा scsi_qla_host *vha, fc_port_t *fcport,
	काष्ठा imm_ntfy_from_isp *ntfy, पूर्णांक type)
अणु
	काष्ठा qla_work_evt *e;

	e = qla2x00_alloc_work(vha, QLA_EVT_NACK);
	अगर (!e)
		वापस QLA_FUNCTION_FAILED;

	e->u.nack.fcport = fcport;
	e->u.nack.type = type;
	स_नकल(e->u.nack.iocb, ntfy, माप(काष्ठा imm_ntfy_from_isp));
	वापस qla2x00_post_work(vha, e);
पूर्ण

अटल व्योम qla2x00_async_nack_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_disc, vha, 0x20f2,
	    "Async done-%s res %x %8phC  type %d\n",
	    sp->name, res, sp->fcport->port_name, sp->type);

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	sp->fcport->flags &= ~FCF_ASYNC_SENT;
	sp->fcport->chip_reset = vha->hw->base_qpair->chip_reset;

	चयन (sp->type) अणु
	हाल SRB_NACK_PLOGI:
		sp->fcport->login_gen++;
		sp->fcport->fw_login_state = DSC_LS_PLOGI_COMP;
		sp->fcport->logout_on_delete = 1;
		sp->fcport->plogi_nack_करोne_deadline = jअगरfies + HZ;
		sp->fcport->send_els_logo = 0;
		अवरोध;

	हाल SRB_NACK_PRLI:
		sp->fcport->fw_login_state = DSC_LS_PRLI_COMP;
		sp->fcport->deleted = 0;
		sp->fcport->send_els_logo = 0;

		अगर (!sp->fcport->login_succ &&
		    !IS_SW_RESV_ADDR(sp->fcport->d_id)) अणु
			sp->fcport->login_succ = 1;

			vha->fcport_count++;
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
			qla24xx_sched_upd_fcport(sp->fcport);
			spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
		पूर्ण अन्यथा अणु
			sp->fcport->login_retry = 0;
			qla2x00_set_fcport_disc_state(sp->fcport,
			    DSC_LOGIN_COMPLETE);
			sp->fcport->deleted = 0;
			sp->fcport->logout_on_delete = 1;
		पूर्ण
		अवरोध;

	हाल SRB_NACK_LOGO:
		sp->fcport->login_gen++;
		sp->fcport->fw_login_state = DSC_LS_PORT_UNAVAIL;
		qlt_logo_completion_handler(sp->fcport, MBS_COMMAND_COMPLETE);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	sp->मुक्त(sp);
पूर्ण

पूर्णांक qla24xx_async_notअगरy_ack(scsi_qla_host_t *vha, fc_port_t *fcport,
	काष्ठा imm_ntfy_from_isp *ntfy, पूर्णांक type)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	srb_t *sp;
	अक्षर *c = शून्य;

	fcport->flags |= FCF_ASYNC_SENT;
	चयन (type) अणु
	हाल SRB_NACK_PLOGI:
		fcport->fw_login_state = DSC_LS_PLOGI_PEND;
		c = "PLOGI";
		अवरोध;
	हाल SRB_NACK_PRLI:
		fcport->fw_login_state = DSC_LS_PRLI_PEND;
		fcport->deleted = 0;
		c = "PRLI";
		अवरोध;
	हाल SRB_NACK_LOGO:
		fcport->fw_login_state = DSC_LS_LOGO_PEND;
		c = "LOGO";
		अवरोध;
	पूर्ण

	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	अगर (!sp)
		जाओ करोne;

	sp->type = type;
	sp->name = "nack";

	sp->u.iocb_cmd.समयout = qla2x00_async_iocb_समयout;
	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha)+2);

	sp->u.iocb_cmd.u.nack.ntfy = ntfy;
	sp->करोne = qla2x00_async_nack_sp_करोne;

	ql_dbg(ql_dbg_disc, vha, 0x20f4,
	    "Async-%s %8phC hndl %x %s\n",
	    sp->name, fcport->port_name, sp->handle, c);

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_मुक्त_sp;

	वापस rval;

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	fcport->flags &= ~FCF_ASYNC_SENT;
	वापस rval;
पूर्ण

व्योम qla24xx_करो_nack_work(काष्ठा scsi_qla_host *vha, काष्ठा qla_work_evt *e)
अणु
	fc_port_t *t;

	चयन (e->u.nack.type) अणु
	हाल SRB_NACK_PRLI:
		t = e->u.nack.fcport;
		flush_work(&t->del_work);
		flush_work(&t->मुक्त_work);
		mutex_lock(&vha->vha_tgt.tgt_mutex);
		t = qlt_create_sess(vha, e->u.nack.fcport, 0);
		mutex_unlock(&vha->vha_tgt.tgt_mutex);
		अगर (t) अणु
			ql_log(ql_log_info, vha, 0xd034,
			    "%s create sess success %p", __func__, t);
			/* create sess has an extra kref */
			vha->hw->tgt.tgt_ops->put_sess(e->u.nack.fcport);
		पूर्ण
		अवरोध;
	पूर्ण
	qla24xx_async_notअगरy_ack(vha, e->u.nack.fcport,
	    (काष्ठा imm_ntfy_from_isp *)e->u.nack.iocb, e->u.nack.type);
पूर्ण

व्योम qla24xx_delete_sess_fn(काष्ठा work_काष्ठा *work)
अणु
	fc_port_t *fcport = container_of(work, काष्ठा fc_port, del_work);
	काष्ठा qla_hw_data *ha = fcport->vha->hw;

	अगर (fcport->se_sess) अणु
		ha->tgt.tgt_ops->shutकरोwn_sess(fcport);
		ha->tgt.tgt_ops->put_sess(fcport);
	पूर्ण अन्यथा अणु
		qlt_unreg_sess(fcport);
	पूर्ण
पूर्ण

/*
 * Called from qla2x00_reg_remote_port()
 */
व्योम qlt_fc_port_added(काष्ठा scsi_qla_host *vha, fc_port_t *fcport)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा fc_port *sess = fcport;
	अचिन्हित दीर्घ flags;

	अगर (!vha->hw->tgt.tgt_ops)
		वापस;

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	अगर (tgt->tgt_stop) अणु
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
		वापस;
	पूर्ण

	अगर (fcport->disc_state == DSC_DELETE_PEND) अणु
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
		वापस;
	पूर्ण

	अगर (!sess->se_sess) अणु
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

		mutex_lock(&vha->vha_tgt.tgt_mutex);
		sess = qlt_create_sess(vha, fcport, false);
		mutex_unlock(&vha->vha_tgt.tgt_mutex);

		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	पूर्ण अन्यथा अणु
		अगर (fcport->fw_login_state == DSC_LS_PRLI_COMP) अणु
			spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
			वापस;
		पूर्ण

		अगर (!kref_get_unless_zero(&sess->sess_kref)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x2107,
			    "%s: kref_get fail sess %8phC \n",
			    __func__, sess->port_name);
			spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
			वापस;
		पूर्ण

		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf04c,
		    "qla_target(%u): %ssession for port %8phC "
		    "(loop ID %d) reappeared\n", vha->vp_idx,
		    sess->local ? "local " : "", sess->port_name, sess->loop_id);

		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf007,
		    "Reappeared sess %p\n", sess);

		ha->tgt.tgt_ops->update_sess(sess, fcport->d_id,
		    fcport->loop_id,
		    (fcport->flags & FCF_CONF_COMP_SUPPORTED));
	पूर्ण

	अगर (sess && sess->local) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf04d,
		    "qla_target(%u): local session for "
		    "port %8phC (loop ID %d) became global\n", vha->vp_idx,
		    fcport->port_name, sess->loop_id);
		sess->local = 0;
	पूर्ण
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	ha->tgt.tgt_ops->put_sess(sess);
पूर्ण

/*
 * This is a zero-base ref-counting solution, since hardware_lock
 * guarantees that ref_count is not modअगरied concurrently.
 * Upon successful वापस content of iocb is undefined
 */
अटल काष्ठा qlt_plogi_ack_t *
qlt_plogi_ack_find_add(काष्ठा scsi_qla_host *vha, port_id_t *id,
		       काष्ठा imm_ntfy_from_isp *iocb)
अणु
	काष्ठा qlt_plogi_ack_t *pla;

	lockdep_निश्चित_held(&vha->hw->hardware_lock);

	list_क्रम_each_entry(pla, &vha->plogi_ack_list, list) अणु
		अगर (pla->id.b24 == id->b24) अणु
			ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0x210d,
			    "%s %d %8phC Term INOT due to new INOT",
			    __func__, __LINE__,
			    pla->iocb.u.isp24.port_name);
			qlt_send_term_imm_notअगर(vha, &pla->iocb, 1);
			स_नकल(&pla->iocb, iocb, माप(pla->iocb));
			वापस pla;
		पूर्ण
	पूर्ण

	pla = kmem_cache_zalloc(qla_tgt_plogi_cachep, GFP_ATOMIC);
	अगर (!pla) अणु
		ql_dbg(ql_dbg_async, vha, 0x5088,
		       "qla_target(%d): Allocation of plogi_ack failed\n",
		       vha->vp_idx);
		वापस शून्य;
	पूर्ण

	स_नकल(&pla->iocb, iocb, माप(pla->iocb));
	pla->id = *id;
	list_add_tail(&pla->list, &vha->plogi_ack_list);

	वापस pla;
पूर्ण

व्योम qlt_plogi_ack_unref(काष्ठा scsi_qla_host *vha,
    काष्ठा qlt_plogi_ack_t *pla)
अणु
	काष्ठा imm_ntfy_from_isp *iocb = &pla->iocb;
	port_id_t port_id;
	uपूर्णांक16_t loop_id;
	fc_port_t *fcport = pla->fcport;

	BUG_ON(!pla->ref_count);
	pla->ref_count--;

	अगर (pla->ref_count)
		वापस;

	ql_dbg(ql_dbg_disc, vha, 0x5089,
	    "Sending PLOGI ACK to wwn %8phC s_id %02x:%02x:%02x loop_id %#04x"
	    " exch %#x ox_id %#x\n", iocb->u.isp24.port_name,
	    iocb->u.isp24.port_id[2], iocb->u.isp24.port_id[1],
	    iocb->u.isp24.port_id[0],
	    le16_to_cpu(iocb->u.isp24.nport_handle),
	    iocb->u.isp24.exchange_address, iocb->ox_id);

	port_id.b.करोमुख्य = iocb->u.isp24.port_id[2];
	port_id.b.area   = iocb->u.isp24.port_id[1];
	port_id.b.al_pa  = iocb->u.isp24.port_id[0];
	port_id.b.rsvd_1 = 0;

	loop_id = le16_to_cpu(iocb->u.isp24.nport_handle);

	fcport->loop_id = loop_id;
	fcport->d_id = port_id;
	अगर (iocb->u.isp24.status_subcode == ELS_PLOGI)
		qla24xx_post_nack_work(vha, fcport, iocb, SRB_NACK_PLOGI);
	अन्यथा
		qla24xx_post_nack_work(vha, fcport, iocb, SRB_NACK_PRLI);

	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->plogi_link[QLT_PLOGI_LINK_SAME_WWN] == pla)
			fcport->plogi_link[QLT_PLOGI_LINK_SAME_WWN] = शून्य;
		अगर (fcport->plogi_link[QLT_PLOGI_LINK_CONFLICT] == pla)
			fcport->plogi_link[QLT_PLOGI_LINK_CONFLICT] = शून्य;
	पूर्ण

	list_del(&pla->list);
	kmem_cache_मुक्त(qla_tgt_plogi_cachep, pla);
पूर्ण

व्योम
qlt_plogi_ack_link(काष्ठा scsi_qla_host *vha, काष्ठा qlt_plogi_ack_t *pla,
    काष्ठा fc_port *sess, क्रमागत qlt_plogi_link_t link)
अणु
	काष्ठा imm_ntfy_from_isp *iocb = &pla->iocb;
	/* Inc ref_count first because link might alपढ़ोy be poपूर्णांकing at pla */
	pla->ref_count++;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf097,
		"Linking sess %p [%d] wwn %8phC with PLOGI ACK to wwn %8phC"
		" s_id %02x:%02x:%02x, ref=%d pla %p link %d\n",
		sess, link, sess->port_name,
		iocb->u.isp24.port_name, iocb->u.isp24.port_id[2],
		iocb->u.isp24.port_id[1], iocb->u.isp24.port_id[0],
		pla->ref_count, pla, link);

	अगर (link == QLT_PLOGI_LINK_CONFLICT) अणु
		चयन (sess->disc_state) अणु
		हाल DSC_DELETED:
		हाल DSC_DELETE_PEND:
			pla->ref_count--;
			वापस;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (sess->plogi_link[link])
		qlt_plogi_ack_unref(vha, sess->plogi_link[link]);

	अगर (link == QLT_PLOGI_LINK_SAME_WWN)
		pla->fcport = sess;

	sess->plogi_link[link] = pla;
पूर्ण

प्रकार काष्ठा अणु
	/* These fields must be initialized by the caller */
	port_id_t id;
	/*
	 * number of cmds dropped जबतक we were रुकोing क्रम
	 * initiator to ack LOGO initialize to 1 अगर LOGO is
	 * triggered by a command, otherwise, to 0
	 */
	पूर्णांक cmd_count;

	/* These fields are used by callee */
	काष्ठा list_head list;
पूर्ण qlt_port_logo_t;

अटल व्योम
qlt_send_first_logo(काष्ठा scsi_qla_host *vha, qlt_port_logo_t *logo)
अणु
	qlt_port_logo_t *पंचांगp;
	पूर्णांक res;

	mutex_lock(&vha->vha_tgt.tgt_mutex);

	list_क्रम_each_entry(पंचांगp, &vha->logo_list, list) अणु
		अगर (पंचांगp->id.b24 == logo->id.b24) अणु
			पंचांगp->cmd_count += logo->cmd_count;
			mutex_unlock(&vha->vha_tgt.tgt_mutex);
			वापस;
		पूर्ण
	पूर्ण

	list_add_tail(&logo->list, &vha->logo_list);

	mutex_unlock(&vha->vha_tgt.tgt_mutex);

	res = qla24xx_els_dcmd_iocb(vha, ELS_DCMD_LOGO, logo->id);

	mutex_lock(&vha->vha_tgt.tgt_mutex);
	list_del(&logo->list);
	mutex_unlock(&vha->vha_tgt.tgt_mutex);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf098,
	    "Finished LOGO to %02x:%02x:%02x, dropped %d cmds, res = %#x\n",
	    logo->id.b.करोमुख्य, logo->id.b.area, logo->id.b.al_pa,
	    logo->cmd_count, res);
पूर्ण

व्योम qlt_मुक्त_session_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा fc_port *sess = container_of(work, काष्ठा fc_port,
	    मुक्त_work);
	काष्ठा qla_tgt *tgt = sess->tgt;
	काष्ठा scsi_qla_host *vha = sess->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;
	bool logout_started = false;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	काष्ठा qlt_plogi_ack_t *own =
		sess->plogi_link[QLT_PLOGI_LINK_SAME_WWN];

	ql_dbg(ql_dbg_disc, vha, 0xf084,
		"%s: se_sess %p / sess %p from port %8phC loop_id %#04x"
		" s_id %02x:%02x:%02x logout %d keep %d els_logo %d\n",
		__func__, sess->se_sess, sess, sess->port_name, sess->loop_id,
		sess->d_id.b.करोमुख्य, sess->d_id.b.area, sess->d_id.b.al_pa,
		sess->logout_on_delete, sess->keep_nport_handle,
		sess->send_els_logo);

	अगर (!IS_SW_RESV_ADDR(sess->d_id)) अणु
		qla2x00_mark_device_lost(vha, sess, 0);

		अगर (sess->send_els_logo) अणु
			qlt_port_logo_t logo;

			logo.id = sess->d_id;
			logo.cmd_count = 0;
			अगर (!own)
				qlt_send_first_logo(vha, &logo);
			sess->send_els_logo = 0;
		पूर्ण

		अगर (sess->logout_on_delete && sess->loop_id != FC_NO_LOOP_ID) अणु
			पूर्णांक rc;

			अगर (!own ||
			     (own->iocb.u.isp24.status_subcode == ELS_PLOGI)) अणु
				rc = qla2x00_post_async_logout_work(vha, sess,
				    शून्य);
				अगर (rc != QLA_SUCCESS)
					ql_log(ql_log_warn, vha, 0xf085,
					    "Schedule logo failed sess %p rc %d\n",
					    sess, rc);
				अन्यथा
					logout_started = true;
			पूर्ण अन्यथा अगर (own && (own->iocb.u.isp24.status_subcode ==
				ELS_PRLI) && ha->flags.rida_fmt2) अणु
				rc = qla2x00_post_async_prlo_work(vha, sess,
				    शून्य);
				अगर (rc != QLA_SUCCESS)
					ql_log(ql_log_warn, vha, 0xf085,
					    "Schedule PRLO failed sess %p rc %d\n",
					    sess, rc);
				अन्यथा
					logout_started = true;
			पूर्ण
		पूर्ण /* अगर sess->logout_on_delete */

		अगर (sess->nvme_flag & NVME_FLAG_REGISTERED &&
		    !(sess->nvme_flag & NVME_FLAG_DELETING)) अणु
			sess->nvme_flag |= NVME_FLAG_DELETING;
			qla_nvme_unरेजिस्टर_remote_port(sess);
		पूर्ण
	पूर्ण

	/*
	 * Release the target session क्रम FC Nexus from fabric module code.
	 */
	अगर (sess->se_sess != शून्य)
		ha->tgt.tgt_ops->मुक्त_session(sess);

	अगर (logout_started) अणु
		bool traced = false;
		u16 cnt = 0;

		जबतक (!READ_ONCE(sess->logout_completed)) अणु
			अगर (!traced) अणु
				ql_dbg(ql_dbg_disc, vha, 0xf086,
					"%s: waiting for sess %p logout\n",
					__func__, sess);
				traced = true;
			पूर्ण
			msleep(100);
			cnt++;
			/*
			 * Driver समयout is set to 22 Sec, update count value to loop
			 * दीर्घ enough क्रम log-out to complete beक्रमe advancing. Otherwise,
			 * straddling logout can पूर्णांकerfere with re-login attempt.
			 */
			अगर (cnt > 230)
				अवरोध;
		पूर्ण

		ql_dbg(ql_dbg_disc, vha, 0xf087,
		    "%s: sess %p logout completed\n", __func__, sess);
	पूर्ण

	अगर (sess->logo_ack_needed) अणु
		sess->logo_ack_needed = 0;
		qla24xx_async_notअगरy_ack(vha, sess,
			(काष्ठा imm_ntfy_from_isp *)sess->iocb, SRB_NACK_LOGO);
	पूर्ण

	spin_lock_irqsave(&vha->work_lock, flags);
	sess->flags &= ~FCF_ASYNC_SENT;
	spin_unlock_irqrestore(&vha->work_lock, flags);

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	अगर (sess->se_sess) अणु
		sess->se_sess = शून्य;
		अगर (tgt && !IS_SW_RESV_ADDR(sess->d_id))
			tgt->sess_count--;
	पूर्ण

	qla2x00_set_fcport_disc_state(sess, DSC_DELETED);
	sess->fw_login_state = DSC_LS_PORT_UNAVAIL;
	sess->deleted = QLA_SESS_DELETED;

	अगर (sess->login_succ && !IS_SW_RESV_ADDR(sess->d_id)) अणु
		vha->fcport_count--;
		sess->login_succ = 0;
	पूर्ण

	qla2x00_clear_loop_id(sess);

	अगर (sess->conflict) अणु
		sess->conflict->login_छोड़ो = 0;
		sess->conflict = शून्य;
		अगर (!test_bit(UNLOADING, &vha->dpc_flags))
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
	पूर्ण

	अणु
		काष्ठा qlt_plogi_ack_t *con =
		    sess->plogi_link[QLT_PLOGI_LINK_CONFLICT];
		काष्ठा imm_ntfy_from_isp *iocb;

		own = sess->plogi_link[QLT_PLOGI_LINK_SAME_WWN];

		अगर (con) अणु
			iocb = &con->iocb;
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf099,
				 "se_sess %p / sess %p port %8phC is gone,"
				 " %s (ref=%d), releasing PLOGI for %8phC (ref=%d)\n",
				 sess->se_sess, sess, sess->port_name,
				 own ? "releasing own PLOGI" : "no own PLOGI pending",
				 own ? own->ref_count : -1,
				 iocb->u.isp24.port_name, con->ref_count);
			qlt_plogi_ack_unref(vha, con);
			sess->plogi_link[QLT_PLOGI_LINK_CONFLICT] = शून्य;
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf09a,
			    "se_sess %p / sess %p port %8phC is gone, %s (ref=%d)\n",
			    sess->se_sess, sess, sess->port_name,
			    own ? "releasing own PLOGI" :
			    "no own PLOGI pending",
			    own ? own->ref_count : -1);
		पूर्ण

		अगर (own) अणु
			sess->fw_login_state = DSC_LS_PLOGI_PEND;
			qlt_plogi_ack_unref(vha, own);
			sess->plogi_link[QLT_PLOGI_LINK_SAME_WWN] = शून्य;
		पूर्ण
	पूर्ण

	sess->explicit_logout = 0;
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
	sess->मुक्त_pending = 0;

	qla2x00_dfs_हटाओ_rport(vha, sess);

	ql_dbg(ql_dbg_disc, vha, 0xf001,
	    "Unregistration of sess %p %8phC finished fcp_cnt %d\n",
		sess, sess->port_name, vha->fcport_count);

	अगर (tgt && (tgt->sess_count == 0))
		wake_up_all(&tgt->रुकोQ);

	अगर (!test_bit(PFLG_DRIVER_REMOVING, &base_vha->pci_flags) &&
	    !(vha->vp_idx && test_bit(VPORT_DELETE, &vha->dpc_flags)) &&
	    (!tgt || !tgt->tgt_stop) && !LOOP_TRANSITION(vha)) अणु
		चयन (vha->host->active_mode) अणु
		हाल MODE_INITIATOR:
		हाल MODE_DUAL:
			set_bit(RELOGIN_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			अवरोध;
		हाल MODE_TARGET:
		शेष:
			/* no-op */
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (vha->fcport_count == 0)
		wake_up_all(&vha->fcport_रुकोQ);
पूर्ण

/* ha->tgt.sess_lock supposed to be held on entry */
व्योम qlt_unreg_sess(काष्ठा fc_port *sess)
अणु
	काष्ठा scsi_qla_host *vha = sess->vha;
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_disc, sess->vha, 0x210a,
	    "%s sess %p for deletion %8phC\n",
	    __func__, sess, sess->port_name);

	spin_lock_irqsave(&sess->vha->work_lock, flags);
	अगर (sess->मुक्त_pending) अणु
		spin_unlock_irqrestore(&sess->vha->work_lock, flags);
		वापस;
	पूर्ण
	sess->मुक्त_pending = 1;
	/*
	 * Use FCF_ASYNC_SENT flag to block other cmds used in sess
	 * management from being sent.
	 */
	sess->flags |= FCF_ASYNC_SENT;
	spin_unlock_irqrestore(&sess->vha->work_lock, flags);

	अगर (sess->se_sess)
		vha->hw->tgt.tgt_ops->clear_nacl_from_fcport_map(sess);

	sess->deleted = QLA_SESS_DELETION_IN_PROGRESS;
	qla2x00_set_fcport_disc_state(sess, DSC_DELETE_PEND);
	sess->last_rscn_gen = sess->rscn_gen;
	sess->last_login_gen = sess->login_gen;

	queue_work(sess->vha->hw->wq, &sess->मुक्त_work);
पूर्ण
EXPORT_SYMBOL(qlt_unreg_sess);

अटल पूर्णांक qlt_reset(काष्ठा scsi_qla_host *vha, व्योम *iocb, पूर्णांक mcmd)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess = शून्य;
	uपूर्णांक16_t loop_id;
	पूर्णांक res = 0;
	काष्ठा imm_ntfy_from_isp *n = (काष्ठा imm_ntfy_from_isp *)iocb;
	अचिन्हित दीर्घ flags;

	loop_id = le16_to_cpu(n->u.isp24.nport_handle);
	अगर (loop_id == 0xFFFF) अणु
		/* Global event */
		atomic_inc(&vha->vha_tgt.qla_tgt->tgt_global_resets_count);
		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
		qlt_clear_tgt_db(vha->vha_tgt.qla_tgt);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
	पूर्ण अन्यथा अणु
		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
		sess = ha->tgt.tgt_ops->find_sess_by_loop_id(vha, loop_id);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
	पूर्ण

	ql_dbg(ql_dbg_tgt, vha, 0xe000,
	    "Using sess for qla_tgt_reset: %p\n", sess);
	अगर (!sess) अणु
		res = -ESRCH;
		वापस res;
	पूर्ण

	ql_dbg(ql_dbg_tgt, vha, 0xe047,
	    "scsi(%ld): resetting (session %p from port %8phC mcmd %x, "
	    "loop_id %d)\n", vha->host_no, sess, sess->port_name,
	    mcmd, loop_id);

	वापस qlt_issue_task_mgmt(sess, 0, mcmd, iocb, QLA24XX_MGMT_SEND_NACK);
पूर्ण

अटल व्योम qla24xx_chk_fcp_state(काष्ठा fc_port *sess)
अणु
	अगर (sess->chip_reset != sess->vha->hw->base_qpair->chip_reset) अणु
		sess->logout_on_delete = 0;
		sess->logo_ack_needed = 0;
		sess->fw_login_state = DSC_LS_PORT_UNAVAIL;
	पूर्ण
पूर्ण

व्योम qlt_schedule_sess_क्रम_deletion(काष्ठा fc_port *sess)
अणु
	काष्ठा qla_tgt *tgt = sess->tgt;
	अचिन्हित दीर्घ flags;
	u16 sec;

	चयन (sess->disc_state) अणु
	हाल DSC_DELETE_PEND:
		वापस;
	हाल DSC_DELETED:
		अगर (!sess->plogi_link[QLT_PLOGI_LINK_SAME_WWN] &&
			!sess->plogi_link[QLT_PLOGI_LINK_CONFLICT]) अणु
			अगर (tgt && tgt->tgt_stop && tgt->sess_count == 0)
				wake_up_all(&tgt->रुकोQ);

			अगर (sess->vha->fcport_count == 0)
				wake_up_all(&sess->vha->fcport_रुकोQ);
			वापस;
		पूर्ण
		अवरोध;
	हाल DSC_UPD_FCPORT:
		/*
		 * This port is not करोne reporting to upper layer.
		 * let it finish
		 */
		sess->next_disc_state = DSC_DELETE_PEND;
		sec = jअगरfies_to_msecs(jअगरfies -
		    sess->jअगरfies_at_registration)/1000;
		अगर (sess->sec_since_registration < sec && sec && !(sec % 5)) अणु
			sess->sec_since_registration = sec;
			ql_dbg(ql_dbg_disc, sess->vha, 0xffff,
			    "%s %8phC : Slow Rport registration(%d Sec)\n",
			    __func__, sess->port_name, sec);
		पूर्ण
		वापस;
	शेष:
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&sess->vha->work_lock, flags);
	अगर (sess->deleted == QLA_SESS_DELETION_IN_PROGRESS) अणु
		spin_unlock_irqrestore(&sess->vha->work_lock, flags);
		वापस;
	पूर्ण
	sess->deleted = QLA_SESS_DELETION_IN_PROGRESS;
	spin_unlock_irqrestore(&sess->vha->work_lock, flags);

	sess->prli_pend_समयr = 0;
	qla2x00_set_fcport_disc_state(sess, DSC_DELETE_PEND);

	qla24xx_chk_fcp_state(sess);

	ql_dbg(ql_log_warn, sess->vha, 0xe001,
	    "Scheduling sess %p for deletion %8phC\n",
	    sess, sess->port_name);

	WARN_ON(!queue_work(sess->vha->hw->wq, &sess->del_work));
पूर्ण

अटल व्योम qlt_clear_tgt_db(काष्ठा qla_tgt *tgt)
अणु
	काष्ठा fc_port *sess;
	scsi_qla_host_t *vha = tgt->vha;

	list_क्रम_each_entry(sess, &vha->vp_fcports, list) अणु
		अगर (sess->se_sess)
			qlt_schedule_sess_क्रम_deletion(sess);
	पूर्ण

	/* At this poपूर्णांक tgt could be alपढ़ोy dead */
पूर्ण

अटल पूर्णांक qla24xx_get_loop_id(काष्ठा scsi_qla_host *vha, be_id_t s_id,
	uपूर्णांक16_t *loop_id)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	dma_addr_t gid_list_dma;
	काष्ठा gid_list_info *gid_list, *gid;
	पूर्णांक res, rc, i;
	uपूर्णांक16_t entries;

	gid_list = dma_alloc_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
	    &gid_list_dma, GFP_KERNEL);
	अगर (!gid_list) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf044,
		    "qla_target(%d): DMA Alloc failed of %u\n",
		    vha->vp_idx, qla2x00_gid_list_size(ha));
		वापस -ENOMEM;
	पूर्ण

	/* Get list of logged in devices */
	rc = qla24xx_gidlist_रुको(vha, gid_list, gid_list_dma, &entries);
	अगर (rc != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf045,
		    "qla_target(%d): get_id_list() failed: %x\n",
		    vha->vp_idx, rc);
		res = -EBUSY;
		जाओ out_मुक्त_id_list;
	पूर्ण

	gid = gid_list;
	res = -ENOENT;
	क्रम (i = 0; i < entries; i++) अणु
		अगर (gid->al_pa == s_id.al_pa &&
		    gid->area == s_id.area &&
		    gid->करोमुख्य == s_id.करोमुख्य) अणु
			*loop_id = le16_to_cpu(gid->loop_id);
			res = 0;
			अवरोध;
		पूर्ण
		gid = (व्योम *)gid + ha->gid_list_info_size;
	पूर्ण

out_मुक्त_id_list:
	dma_मुक्त_coherent(&ha->pdev->dev, qla2x00_gid_list_size(ha),
	    gid_list, gid_list_dma);
	वापस res;
पूर्ण

/*
 * Adds an extra ref to allow to drop hw lock after adding sess to the list.
 * Caller must put it.
 */
अटल काष्ठा fc_port *qlt_create_sess(
	काष्ठा scsi_qla_host *vha,
	fc_port_t *fcport,
	bool local)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess = fcport;
	अचिन्हित दीर्घ flags;

	अगर (vha->vha_tgt.qla_tgt->tgt_stop)
		वापस शून्य;

	अगर (fcport->se_sess) अणु
		अगर (!kref_get_unless_zero(&sess->sess_kref)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20f6,
			    "%s: kref_get_unless_zero failed for %8phC\n",
			    __func__, sess->port_name);
			वापस शून्य;
		पूर्ण
		वापस fcport;
	पूर्ण
	sess->tgt = vha->vha_tgt.qla_tgt;
	sess->local = local;

	/*
	 * Under normal circumstances we want to logout from firmware when
	 * session eventually ends and release corresponding nport handle.
	 * In the exception हालs (e.g. when new PLOGI is रुकोing) corresponding
	 * code will adjust these flags as necessary.
	 */
	sess->logout_on_delete = 1;
	sess->keep_nport_handle = 0;
	sess->logout_completed = 0;

	अगर (ha->tgt.tgt_ops->check_initiator_node_acl(vha,
	    &fcport->port_name[0], sess) < 0) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf015,
		    "(%d) %8phC check_initiator_node_acl failed\n",
		    vha->vp_idx, fcport->port_name);
		वापस शून्य;
	पूर्ण अन्यथा अणु
		kref_init(&fcport->sess_kref);
		/*
		 * Take an extra reference to ->sess_kref here to handle
		 * fc_port access across ->tgt.sess_lock reaquire.
		 */
		अगर (!kref_get_unless_zero(&sess->sess_kref)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20f7,
			    "%s: kref_get_unless_zero failed for %8phC\n",
			    __func__, sess->port_name);
			वापस शून्य;
		पूर्ण

		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
		अगर (!IS_SW_RESV_ADDR(sess->d_id))
			vha->vha_tgt.qla_tgt->sess_count++;

		qlt_करो_generation_tick(vha, &sess->generation);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
	पूर्ण

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf006,
	    "Adding sess %p se_sess %p  to tgt %p sess_count %d\n",
	    sess, sess->se_sess, vha->vha_tgt.qla_tgt,
	    vha->vha_tgt.qla_tgt->sess_count);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf04b,
	    "qla_target(%d): %ssession for wwn %8phC (loop_id %d, "
	    "s_id %x:%x:%x, confirmed completion %ssupported) added\n",
	    vha->vp_idx, local ?  "local " : "", fcport->port_name,
	    fcport->loop_id, sess->d_id.b.करोमुख्य, sess->d_id.b.area,
	    sess->d_id.b.al_pa, sess->conf_compl_supported ?  "" : "not ");

	वापस sess;
पूर्ण

/*
 * max_gen - specअगरies maximum session generation
 * at which this deletion requestion is still valid
 */
व्योम
qlt_fc_port_deleted(काष्ठा scsi_qla_host *vha, fc_port_t *fcport, पूर्णांक max_gen)
अणु
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा fc_port *sess = fcport;
	अचिन्हित दीर्घ flags;

	अगर (!vha->hw->tgt.tgt_ops)
		वापस;

	अगर (!tgt)
		वापस;

	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	अगर (tgt->tgt_stop) अणु
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		वापस;
	पूर्ण
	अगर (!sess->se_sess) अणु
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		वापस;
	पूर्ण

	अगर (max_gen - sess->generation < 0) अणु
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf092,
		    "Ignoring stale deletion request for se_sess %p / sess %p"
		    " for port %8phC, req_gen %d, sess_gen %d\n",
		    sess->se_sess, sess, sess->port_name, max_gen,
		    sess->generation);
		वापस;
	पूर्ण

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf008, "qla_tgt_fc_port_deleted %p", sess);

	sess->local = 1;
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
	qlt_schedule_sess_क्रम_deletion(sess);
पूर्ण

अटल अंतरभूत पूर्णांक test_tgt_sess_count(काष्ठा qla_tgt *tgt)
अणु
	काष्ठा qla_hw_data *ha = tgt->ha;
	अचिन्हित दीर्घ flags;
	पूर्णांक res;
	/*
	 * We need to protect against race, when tgt is मुक्तd beक्रमe or
	 * inside wake_up()
	 */
	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	ql_dbg(ql_dbg_tgt, tgt->vha, 0xe002,
	    "tgt %p, sess_count=%d\n",
	    tgt, tgt->sess_count);
	res = (tgt->sess_count == 0);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	वापस res;
पूर्ण

/* Called by tcm_qla2xxx configfs code */
पूर्णांक qlt_stop_phase1(काष्ठा qla_tgt *tgt)
अणु
	काष्ठा scsi_qla_host *vha = tgt->vha;
	काष्ठा qla_hw_data *ha = tgt->ha;
	अचिन्हित दीर्घ flags;

	mutex_lock(&ha->optrom_mutex);
	mutex_lock(&qla_tgt_mutex);

	अगर (tgt->tgt_stop || tgt->tgt_stopped) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf04e,
		    "Already in tgt->tgt_stop or tgt_stopped state\n");
		mutex_unlock(&qla_tgt_mutex);
		mutex_unlock(&ha->optrom_mutex);
		वापस -EPERM;
	पूर्ण

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xe003, "Stopping target for host %ld(%p)\n",
	    vha->host_no, vha);
	/*
	 * Mutex needed to sync with qla_tgt_fc_port_[added,deleted].
	 * Lock is needed, because we still can get an incoming packet.
	 */
	mutex_lock(&vha->vha_tgt.tgt_mutex);
	tgt->tgt_stop = 1;
	qlt_clear_tgt_db(tgt);
	mutex_unlock(&vha->vha_tgt.tgt_mutex);
	mutex_unlock(&qla_tgt_mutex);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf009,
	    "Waiting for sess works (tgt %p)", tgt);
	spin_lock_irqsave(&tgt->sess_work_lock, flags);
	जबतक (!list_empty(&tgt->sess_works_list)) अणु
		spin_unlock_irqrestore(&tgt->sess_work_lock, flags);
		flush_scheduled_work();
		spin_lock_irqsave(&tgt->sess_work_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&tgt->sess_work_lock, flags);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf00a,
	    "Waiting for tgt %p: sess_count=%d\n", tgt, tgt->sess_count);

	रुको_event_समयout(tgt->रुकोQ, test_tgt_sess_count(tgt), 10*HZ);

	/* Big hammer */
	अगर (!ha->flags.host_shutting_करोwn &&
	    (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha)))
		qlt_disable_vha(vha);

	/* Wait क्रम sessions to clear out (just in हाल) */
	रुको_event_समयout(tgt->रुकोQ, test_tgt_sess_count(tgt), 10*HZ);
	mutex_unlock(&ha->optrom_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(qlt_stop_phase1);

/* Called by tcm_qla2xxx configfs code */
व्योम qlt_stop_phase2(काष्ठा qla_tgt *tgt)
अणु
	scsi_qla_host_t *vha = tgt->vha;

	अगर (tgt->tgt_stopped) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf04f,
		    "Already in tgt->tgt_stopped state\n");
		dump_stack();
		वापस;
	पूर्ण
	अगर (!tgt->tgt_stop) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf00b,
		    "%s: phase1 stop is not completed\n", __func__);
		dump_stack();
		वापस;
	पूर्ण

	mutex_lock(&tgt->ha->optrom_mutex);
	mutex_lock(&vha->vha_tgt.tgt_mutex);
	tgt->tgt_stop = 0;
	tgt->tgt_stopped = 1;
	mutex_unlock(&vha->vha_tgt.tgt_mutex);
	mutex_unlock(&tgt->ha->optrom_mutex);

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf00c, "Stop of tgt %p finished\n",
	    tgt);

	चयन (vha->qlini_mode) अणु
	हाल QLA2XXX_INI_MODE_EXCLUSIVE:
		vha->flags.online = 1;
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(qlt_stop_phase2);

/* Called from qlt_हटाओ_target() -> qla2x00_हटाओ_one() */
अटल व्योम qlt_release(काष्ठा qla_tgt *tgt)
अणु
	scsi_qla_host_t *vha = tgt->vha;
	व्योम *node;
	u64 key = 0;
	u16 i;
	काष्ठा qla_qpair_hपूर्णांक *h;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!tgt->tgt_stop && !tgt->tgt_stopped)
		qlt_stop_phase1(tgt);

	अगर (!tgt->tgt_stopped)
		qlt_stop_phase2(tgt);

	क्रम (i = 0; i < vha->hw->max_qpairs + 1; i++) अणु
		अचिन्हित दीर्घ flags;

		h = &tgt->qphपूर्णांकs[i];
		अगर (h->qpair) अणु
			spin_lock_irqsave(h->qpair->qp_lock_ptr, flags);
			list_del(&h->hपूर्णांक_elem);
			spin_unlock_irqrestore(h->qpair->qp_lock_ptr, flags);
			h->qpair = शून्य;
		पूर्ण
	पूर्ण
	kमुक्त(tgt->qphपूर्णांकs);
	mutex_lock(&qla_tgt_mutex);
	list_del(&vha->vha_tgt.qla_tgt->tgt_list_entry);
	mutex_unlock(&qla_tgt_mutex);

	btree_क्रम_each_safe64(&tgt->lun_qpair_map, key, node)
		btree_हटाओ64(&tgt->lun_qpair_map, key);

	btree_destroy64(&tgt->lun_qpair_map);

	अगर (vha->vp_idx)
		अगर (ha->tgt.tgt_ops &&
		    ha->tgt.tgt_ops->हटाओ_target &&
		    vha->vha_tgt.target_lport_ptr)
			ha->tgt.tgt_ops->हटाओ_target(vha);

	vha->vha_tgt.qla_tgt = शून्य;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf00d,
	    "Release of tgt %p finished\n", tgt);

	kमुक्त(tgt);
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक qlt_sched_sess_work(काष्ठा qla_tgt *tgt, पूर्णांक type,
	स्थिर व्योम *param, अचिन्हित पूर्णांक param_size)
अणु
	काष्ठा qla_tgt_sess_work_param *prm;
	अचिन्हित दीर्घ flags;

	prm = kzalloc(माप(*prm), GFP_ATOMIC);
	अगर (!prm) अणु
		ql_dbg(ql_dbg_tgt_mgt, tgt->vha, 0xf050,
		    "qla_target(%d): Unable to create session "
		    "work, command will be refused", 0);
		वापस -ENOMEM;
	पूर्ण

	ql_dbg(ql_dbg_tgt_mgt, tgt->vha, 0xf00e,
	    "Scheduling work (type %d, prm %p)"
	    " to find session for param %p (size %d, tgt %p)\n",
	    type, prm, param, param_size, tgt);

	prm->type = type;
	स_नकल(&prm->पंचांग_iocb, param, param_size);

	spin_lock_irqsave(&tgt->sess_work_lock, flags);
	list_add_tail(&prm->sess_works_list_entry, &tgt->sess_works_list);
	spin_unlock_irqrestore(&tgt->sess_work_lock, flags);

	schedule_work(&tgt->sess_work);

	वापस 0;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_send_notअगरy_ack(काष्ठा qla_qpair *qpair,
	काष्ठा imm_ntfy_from_isp *ntfy,
	uपूर्णांक32_t add_flags, uपूर्णांक16_t resp_code, पूर्णांक resp_code_valid,
	uपूर्णांक16_t srr_flags, uपूर्णांक16_t srr_reject_code, uपूर्णांक8_t srr_explan)
अणु
	काष्ठा scsi_qla_host *vha = qpair->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	request_t *pkt;
	काष्ठा nack_to_isp *nack;

	अगर (!ha->flags.fw_started)
		वापस;

	ql_dbg(ql_dbg_tgt, vha, 0xe004, "Sending NOTIFY_ACK (ha=%p)\n", ha);

	pkt = (request_t *)__qla2x00_alloc_iocbs(qpair, शून्य);
	अगर (!pkt) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe049,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet\n", vha->vp_idx, __func__);
		वापस;
	पूर्ण

	अगर (vha->vha_tgt.qla_tgt != शून्य)
		vha->vha_tgt.qla_tgt->notअगरy_ack_expected++;

	pkt->entry_type = NOTIFY_ACK_TYPE;
	pkt->entry_count = 1;

	nack = (काष्ठा nack_to_isp *)pkt;
	nack->ox_id = ntfy->ox_id;

	nack->u.isp24.handle = QLA_TGT_SKIP_HANDLE;
	nack->u.isp24.nport_handle = ntfy->u.isp24.nport_handle;
	अगर (le16_to_cpu(ntfy->u.isp24.status) == IMM_NTFY_ELS) अणु
		nack->u.isp24.flags = ntfy->u.isp24.flags &
			cpu_to_le16(NOTIFY24XX_FLAGS_PUREX_IOCB);
	पूर्ण
	nack->u.isp24.srr_rx_id = ntfy->u.isp24.srr_rx_id;
	nack->u.isp24.status = ntfy->u.isp24.status;
	nack->u.isp24.status_subcode = ntfy->u.isp24.status_subcode;
	nack->u.isp24.fw_handle = ntfy->u.isp24.fw_handle;
	nack->u.isp24.exchange_address = ntfy->u.isp24.exchange_address;
	nack->u.isp24.srr_rel_offs = ntfy->u.isp24.srr_rel_offs;
	nack->u.isp24.srr_ui = ntfy->u.isp24.srr_ui;
	nack->u.isp24.srr_flags = cpu_to_le16(srr_flags);
	nack->u.isp24.srr_reject_code = srr_reject_code;
	nack->u.isp24.srr_reject_code_expl = srr_explan;
	nack->u.isp24.vp_index = ntfy->u.isp24.vp_index;

	ql_dbg(ql_dbg_tgt, vha, 0xe005,
	    "qla_target(%d): Sending 24xx Notify Ack %d\n",
	    vha->vp_idx, nack->u.isp24.status);

	/* Memory Barrier */
	wmb();
	qla2x00_start_iocbs(vha, qpair->req);
पूर्ण

अटल पूर्णांक qlt_build_abts_resp_iocb(काष्ठा qla_tgt_mgmt_cmd *mcmd)
अणु
	काष्ठा scsi_qla_host *vha = mcmd->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा abts_resp_to_24xx *resp;
	__le32 f_ctl;
	uपूर्णांक32_t h;
	uपूर्णांक8_t *p;
	पूर्णांक rc;
	काष्ठा abts_recv_from_24xx *abts = &mcmd->orig_iocb.abts;
	काष्ठा qla_qpair *qpair = mcmd->qpair;

	ql_dbg(ql_dbg_tgt, vha, 0xe006,
	    "Sending task mgmt ABTS response (ha=%p, status=%x)\n",
	    ha, mcmd->fc_पंचांग_rsp);

	rc = qlt_check_reserve_मुक्त_req(qpair, 1);
	अगर (rc) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe04a,
		    "qla_target(%d): %s failed: unable to allocate request packet\n",
		    vha->vp_idx, __func__);
		वापस -EAGAIN;
	पूर्ण

	resp = (काष्ठा abts_resp_to_24xx *)qpair->req->ring_ptr;
	स_रखो(resp, 0, माप(*resp));

	h = qlt_make_handle(qpair);
	अगर (unlikely(h == QLA_TGT_शून्य_HANDLE)) अणु
		/*
		 * CTIO type 7 from the firmware करोesn't provide a way to
		 * know the initiator's LOOP ID, hence we can't find
		 * the session and, so, the command.
		 */
		वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		qpair->req->outstanding_cmds[h] = (srb_t *)mcmd;
	पूर्ण

	resp->handle = make_handle(qpair->req->id, h);
	resp->entry_type = ABTS_RESP_24XX;
	resp->entry_count = 1;
	resp->nport_handle = abts->nport_handle;
	resp->vp_index = vha->vp_idx;
	resp->sof_type = abts->sof_type;
	resp->exchange_address = abts->exchange_address;
	resp->fcp_hdr_le = abts->fcp_hdr_le;
	f_ctl = cpu_to_le32(F_CTL_EXCH_CONTEXT_RESP |
	    F_CTL_LAST_SEQ | F_CTL_END_SEQ |
	    F_CTL_SEQ_INITIATIVE);
	p = (uपूर्णांक8_t *)&f_ctl;
	resp->fcp_hdr_le.f_ctl[0] = *p++;
	resp->fcp_hdr_le.f_ctl[1] = *p++;
	resp->fcp_hdr_le.f_ctl[2] = *p;

	resp->fcp_hdr_le.d_id = abts->fcp_hdr_le.s_id;
	resp->fcp_hdr_le.s_id = abts->fcp_hdr_le.d_id;

	resp->exchange_addr_to_पात = abts->exchange_addr_to_पात;
	अगर (mcmd->fc_पंचांग_rsp == FCP_TMF_CMPL) अणु
		resp->fcp_hdr_le.r_ctl = R_CTL_BASIC_LINK_SERV | R_CTL_B_ACC;
		resp->payload.ba_acct.seq_id_valid = SEQ_ID_INVALID;
		resp->payload.ba_acct.low_seq_cnt = 0x0000;
		resp->payload.ba_acct.high_seq_cnt = cpu_to_le16(0xFFFF);
		resp->payload.ba_acct.ox_id = abts->fcp_hdr_le.ox_id;
		resp->payload.ba_acct.rx_id = abts->fcp_hdr_le.rx_id;
	पूर्ण अन्यथा अणु
		resp->fcp_hdr_le.r_ctl = R_CTL_BASIC_LINK_SERV | R_CTL_B_RJT;
		resp->payload.ba_rjt.reason_code =
			BA_RJT_REASON_CODE_UNABLE_TO_PERFORM;
		/* Other bytes are zero */
	पूर्ण

	vha->vha_tgt.qla_tgt->abts_resp_expected++;

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);

	वापस rc;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_24xx_send_abts_resp(काष्ठा qla_qpair *qpair,
	काष्ठा abts_recv_from_24xx *abts, uपूर्णांक32_t status,
	bool ids_reversed)
अणु
	काष्ठा scsi_qla_host *vha = qpair->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा abts_resp_to_24xx *resp;
	__le32 f_ctl;
	uपूर्णांक8_t *p;

	ql_dbg(ql_dbg_tgt, vha, 0xe006,
	    "Sending task mgmt ABTS response (ha=%p, atio=%p, status=%x\n",
	    ha, abts, status);

	resp = (काष्ठा abts_resp_to_24xx *)qla2x00_alloc_iocbs_पढ़ोy(qpair,
	    शून्य);
	अगर (!resp) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe04a,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet", vha->vp_idx, __func__);
		वापस;
	पूर्ण

	resp->entry_type = ABTS_RESP_24XX;
	resp->handle = QLA_TGT_SKIP_HANDLE;
	resp->entry_count = 1;
	resp->nport_handle = abts->nport_handle;
	resp->vp_index = vha->vp_idx;
	resp->sof_type = abts->sof_type;
	resp->exchange_address = abts->exchange_address;
	resp->fcp_hdr_le = abts->fcp_hdr_le;
	f_ctl = cpu_to_le32(F_CTL_EXCH_CONTEXT_RESP |
	    F_CTL_LAST_SEQ | F_CTL_END_SEQ |
	    F_CTL_SEQ_INITIATIVE);
	p = (uपूर्णांक8_t *)&f_ctl;
	resp->fcp_hdr_le.f_ctl[0] = *p++;
	resp->fcp_hdr_le.f_ctl[1] = *p++;
	resp->fcp_hdr_le.f_ctl[2] = *p;
	अगर (ids_reversed) अणु
		resp->fcp_hdr_le.d_id = abts->fcp_hdr_le.d_id;
		resp->fcp_hdr_le.s_id = abts->fcp_hdr_le.s_id;
	पूर्ण अन्यथा अणु
		resp->fcp_hdr_le.d_id = abts->fcp_hdr_le.s_id;
		resp->fcp_hdr_le.s_id = abts->fcp_hdr_le.d_id;
	पूर्ण
	resp->exchange_addr_to_पात = abts->exchange_addr_to_पात;
	अगर (status == FCP_TMF_CMPL) अणु
		resp->fcp_hdr_le.r_ctl = R_CTL_BASIC_LINK_SERV | R_CTL_B_ACC;
		resp->payload.ba_acct.seq_id_valid = SEQ_ID_INVALID;
		resp->payload.ba_acct.low_seq_cnt = 0x0000;
		resp->payload.ba_acct.high_seq_cnt = cpu_to_le16(0xFFFF);
		resp->payload.ba_acct.ox_id = abts->fcp_hdr_le.ox_id;
		resp->payload.ba_acct.rx_id = abts->fcp_hdr_le.rx_id;
	पूर्ण अन्यथा अणु
		resp->fcp_hdr_le.r_ctl = R_CTL_BASIC_LINK_SERV | R_CTL_B_RJT;
		resp->payload.ba_rjt.reason_code =
			BA_RJT_REASON_CODE_UNABLE_TO_PERFORM;
		/* Other bytes are zero */
	पूर्ण

	vha->vha_tgt.qla_tgt->abts_resp_expected++;

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_24xx_retry_term_exchange(काष्ठा scsi_qla_host *vha,
    काष्ठा qla_qpair *qpair, response_t *pkt, काष्ठा qla_tgt_mgmt_cmd *mcmd)
अणु
	काष्ठा ctio7_to_24xx *ctio;
	u16 पंचांगp;
	काष्ठा abts_recv_from_24xx *entry;

	ctio = (काष्ठा ctio7_to_24xx *)qla2x00_alloc_iocbs_पढ़ोy(qpair, शून्य);
	अगर (ctio == शून्य) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe04b,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet\n", vha->vp_idx, __func__);
		वापस;
	पूर्ण

	अगर (mcmd)
		/* abts from remote port */
		entry = &mcmd->orig_iocb.abts;
	अन्यथा
		/* abts from this driver.  */
		entry = (काष्ठा abts_recv_from_24xx *)pkt;

	/*
	 * We've got on entrance firmware's response on by us generated
	 * ABTS response. So, in it ID fields are reversed.
	 */

	ctio->entry_type = CTIO_TYPE7;
	ctio->entry_count = 1;
	ctio->nport_handle = entry->nport_handle;
	ctio->handle = QLA_TGT_SKIP_HANDLE |	CTIO_COMPLETION_HANDLE_MARK;
	ctio->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	ctio->vp_index = vha->vp_idx;
	ctio->exchange_addr = entry->exchange_addr_to_पात;
	पंचांगp = (CTIO7_FLAGS_STATUS_MODE_1 | CTIO7_FLAGS_TERMINATE);

	अगर (mcmd) अणु
		ctio->initiator_id = entry->fcp_hdr_le.s_id;

		अगर (mcmd->flags & QLA24XX_MGMT_ABORT_IO_ATTR_VALID)
			पंचांगp |= (mcmd->पात_io_attr << 9);
		अन्यथा अगर (qpair->retry_term_cnt & 1)
			पंचांगp |= (0x4 << 9);
	पूर्ण अन्यथा अणु
		ctio->initiator_id = entry->fcp_hdr_le.d_id;

		अगर (qpair->retry_term_cnt & 1)
			पंचांगp |= (0x4 << 9);
	पूर्ण
	ctio->u.status1.flags = cpu_to_le16(पंचांगp);
	ctio->u.status1.ox_id = entry->fcp_hdr_le.ox_id;

	ql_dbg(ql_dbg_tgt, vha, 0xe007,
	    "Sending retry TERM EXCH CTIO7 flags %04xh oxid %04xh attr valid %x\n",
	    le16_to_cpu(ctio->u.status1.flags),
	    le16_to_cpu(ctio->u.status1.ox_id),
	    (mcmd && mcmd->flags & QLA24XX_MGMT_ABORT_IO_ATTR_VALID) ? 1 : 0);

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);

	अगर (mcmd)
		qlt_build_abts_resp_iocb(mcmd);
	अन्यथा
		qlt_24xx_send_abts_resp(qpair,
		    (काष्ठा abts_recv_from_24xx *)entry, FCP_TMF_CMPL, true);

पूर्ण

/* drop cmds क्रम the given lun
 * XXX only looks क्रम cmds on the port through which lun reset was recieved
 * XXX करोes not go through the list of other port (which may have cmds
 *     क्रम the same lun)
 */
अटल व्योम पात_cmds_क्रम_lun(काष्ठा scsi_qla_host *vha, u64 lun, be_id_t s_id)
अणु
	काष्ठा qla_tgt_sess_op *op;
	काष्ठा qla_tgt_cmd *cmd;
	uपूर्णांक32_t key;
	अचिन्हित दीर्घ flags;

	key = sid_to_key(s_id);
	spin_lock_irqsave(&vha->cmd_list_lock, flags);
	list_क्रम_each_entry(op, &vha->qla_sess_op_cmd_list, cmd_list) अणु
		uपूर्णांक32_t op_key;
		u64 op_lun;

		op_key = sid_to_key(op->atio.u.isp24.fcp_hdr.s_id);
		op_lun = scsilun_to_पूर्णांक(
			(काष्ठा scsi_lun *)&op->atio.u.isp24.fcp_cmnd.lun);
		अगर (op_key == key && op_lun == lun)
			op->पातed = true;
	पूर्ण

	list_क्रम_each_entry(op, &vha->unknown_atio_list, cmd_list) अणु
		uपूर्णांक32_t op_key;
		u64 op_lun;

		op_key = sid_to_key(op->atio.u.isp24.fcp_hdr.s_id);
		op_lun = scsilun_to_पूर्णांक(
			(काष्ठा scsi_lun *)&op->atio.u.isp24.fcp_cmnd.lun);
		अगर (op_key == key && op_lun == lun)
			op->पातed = true;
	पूर्ण

	list_क्रम_each_entry(cmd, &vha->qla_cmd_list, cmd_list) अणु
		uपूर्णांक32_t cmd_key;
		u64 cmd_lun;

		cmd_key = sid_to_key(cmd->atio.u.isp24.fcp_hdr.s_id);
		cmd_lun = scsilun_to_पूर्णांक(
			(काष्ठा scsi_lun *)&cmd->atio.u.isp24.fcp_cmnd.lun);
		अगर (cmd_key == key && cmd_lun == lun)
			cmd->पातed = 1;
	पूर्ण
	spin_unlock_irqrestore(&vha->cmd_list_lock, flags);
पूर्ण

अटल काष्ठा qla_qpair_hपूर्णांक *qlt_find_qphपूर्णांक(काष्ठा scsi_qla_host *vha,
    uपूर्णांक64_t unpacked_lun)
अणु
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा qla_qpair_hपूर्णांक *h = शून्य;

	अगर (vha->flags.qpairs_available) अणु
		h = btree_lookup64(&tgt->lun_qpair_map, unpacked_lun);
		अगर (!h)
			h = &tgt->qphपूर्णांकs[0];
	पूर्ण अन्यथा अणु
		h = &tgt->qphपूर्णांकs[0];
	पूर्ण

	वापस h;
पूर्ण

अटल व्योम qlt_करो_पंचांगr_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_tgt_mgmt_cmd *mcmd =
		container_of(work, काष्ठा qla_tgt_mgmt_cmd, work);
	काष्ठा qla_hw_data *ha = mcmd->vha->hw;
	पूर्णांक rc;
	uपूर्णांक32_t tag;
	अचिन्हित दीर्घ flags;

	चयन (mcmd->पंचांगr_func) अणु
	हाल QLA_TGT_ABTS:
		tag = le32_to_cpu(mcmd->orig_iocb.abts.exchange_addr_to_पात);
		अवरोध;
	शेष:
		tag = 0;
		अवरोध;
	पूर्ण

	rc = ha->tgt.tgt_ops->handle_पंचांगr(mcmd, mcmd->unpacked_lun,
	    mcmd->पंचांगr_func, tag);

	अगर (rc != 0) अणु
		spin_lock_irqsave(mcmd->qpair->qp_lock_ptr, flags);
		चयन (mcmd->पंचांगr_func) अणु
		हाल QLA_TGT_ABTS:
			mcmd->fc_पंचांग_rsp = FCP_TMF_REJECTED;
			qlt_build_abts_resp_iocb(mcmd);
			अवरोध;
		हाल QLA_TGT_LUN_RESET:
		हाल QLA_TGT_CLEAR_TS:
		हाल QLA_TGT_ABORT_TS:
		हाल QLA_TGT_CLEAR_ACA:
		हाल QLA_TGT_TARGET_RESET:
			qlt_send_busy(mcmd->qpair, &mcmd->orig_iocb.atio,
			    qla_sam_status);
			अवरोध;

		हाल QLA_TGT_ABORT_ALL:
		हाल QLA_TGT_NEXUS_LOSS_SESS:
		हाल QLA_TGT_NEXUS_LOSS:
			qlt_send_notअगरy_ack(mcmd->qpair,
			    &mcmd->orig_iocb.imm_ntfy, 0, 0, 0, 0, 0, 0);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(mcmd->qpair->qp_lock_ptr, flags);

		ql_dbg(ql_dbg_tgt_mgt, mcmd->vha, 0xf052,
		    "qla_target(%d):  tgt_ops->handle_tmr() failed: %d\n",
		    mcmd->vha->vp_idx, rc);
		mempool_मुक्त(mcmd, qla_tgt_mgmt_cmd_mempool);
	पूर्ण
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक __qlt_24xx_handle_abts(काष्ठा scsi_qla_host *vha,
	काष्ठा abts_recv_from_24xx *abts, काष्ठा fc_port *sess)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt_mgmt_cmd *mcmd;
	काष्ठा qla_qpair_hपूर्णांक *h = &vha->vha_tgt.qla_tgt->qphपूर्णांकs[0];
	काष्ठा qla_tgt_cmd *पात_cmd;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf00f,
	    "qla_target(%d): task abort (tag=%d)\n",
	    vha->vp_idx, abts->exchange_addr_to_पात);

	mcmd = mempool_alloc(qla_tgt_mgmt_cmd_mempool, GFP_ATOMIC);
	अगर (mcmd == शून्य) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf051,
		    "qla_target(%d): %s: Allocation of ABORT cmd failed",
		    vha->vp_idx, __func__);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(mcmd, 0, माप(*mcmd));
	mcmd->cmd_type = TYPE_TGT_TMCMD;
	mcmd->sess = sess;
	स_नकल(&mcmd->orig_iocb.abts, abts, माप(mcmd->orig_iocb.abts));
	mcmd->reset_count = ha->base_qpair->chip_reset;
	mcmd->पंचांगr_func = QLA_TGT_ABTS;
	mcmd->qpair = h->qpair;
	mcmd->vha = vha;

	/*
	 * LUN is looked up by target-core पूर्णांकernally based on the passed
	 * abts->exchange_addr_to_पात tag.
	 */
	mcmd->se_cmd.cpuid = h->cpuid;

	पात_cmd = ha->tgt.tgt_ops->find_cmd_by_tag(sess,
				le32_to_cpu(abts->exchange_addr_to_पात));
	अगर (!पात_cmd)
		वापस -EIO;
	mcmd->unpacked_lun = पात_cmd->se_cmd.orig_fe_lun;

	अगर (पात_cmd->qpair) अणु
		mcmd->qpair = पात_cmd->qpair;
		mcmd->se_cmd.cpuid = पात_cmd->se_cmd.cpuid;
		mcmd->पात_io_attr = पात_cmd->atio.u.isp24.attr;
		mcmd->flags = QLA24XX_MGMT_ABORT_IO_ATTR_VALID;
	पूर्ण

	INIT_WORK(&mcmd->work, qlt_करो_पंचांगr_work);
	queue_work_on(mcmd->se_cmd.cpuid, qla_tgt_wq, &mcmd->work);

	वापस 0;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_24xx_handle_abts(काष्ठा scsi_qla_host *vha,
	काष्ठा abts_recv_from_24xx *abts)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess;
	uपूर्णांक32_t tag = le32_to_cpu(abts->exchange_addr_to_पात);
	be_id_t s_id;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;

	अगर (le32_to_cpu(abts->fcp_hdr_le.parameter) & ABTS_PARAM_ABORT_SEQ) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf053,
		    "qla_target(%d): ABTS: Abort Sequence not "
		    "supported\n", vha->vp_idx);
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		वापस;
	पूर्ण

	अगर (tag == ATIO_EXCHANGE_ADDRESS_UNKNOWN) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf010,
		    "qla_target(%d): ABTS: Unknown Exchange "
		    "Address received\n", vha->vp_idx);
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		वापस;
	पूर्ण

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf011,
	    "qla_target(%d): task abort (s_id=%x:%x:%x, "
	    "tag=%d, param=%x)\n", vha->vp_idx, abts->fcp_hdr_le.s_id.करोमुख्य,
	    abts->fcp_hdr_le.s_id.area, abts->fcp_hdr_le.s_id.al_pa, tag,
	    le32_to_cpu(abts->fcp_hdr_le.parameter));

	s_id = le_id_to_be(abts->fcp_hdr_le.s_id);

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	sess = ha->tgt.tgt_ops->find_sess_by_s_id(vha, s_id);
	अगर (!sess) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf012,
		    "qla_target(%d): task abort for non-existent session\n",
		    vha->vp_idx);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
			    false);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);


	अगर (sess->deleted) अणु
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		वापस;
	पूर्ण

	rc = __qlt_24xx_handle_abts(vha, abts, sess);
	अगर (rc != 0) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf054,
		    "qla_target(%d): __qlt_24xx_handle_abts() failed: %d\n",
		    vha->vp_idx, rc);
		qlt_24xx_send_abts_resp(ha->base_qpair, abts, FCP_TMF_REJECTED,
		    false);
		वापस;
	पूर्ण
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_24xx_send_task_mgmt_ctio(काष्ठा qla_qpair *qpair,
	काष्ठा qla_tgt_mgmt_cmd *mcmd, uपूर्णांक32_t resp_code)
अणु
	काष्ठा scsi_qla_host *ha = mcmd->vha;
	काष्ठा atio_from_isp *atio = &mcmd->orig_iocb.atio;
	काष्ठा ctio7_to_24xx *ctio;
	uपूर्णांक16_t temp;

	ql_dbg(ql_dbg_tgt, ha, 0xe008,
	    "Sending task mgmt CTIO7 (ha=%p, atio=%p, resp_code=%x\n",
	    ha, atio, resp_code);


	ctio = (काष्ठा ctio7_to_24xx *)__qla2x00_alloc_iocbs(qpair, शून्य);
	अगर (ctio == शून्य) अणु
		ql_dbg(ql_dbg_tgt, ha, 0xe04c,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet\n", ha->vp_idx, __func__);
		वापस;
	पूर्ण

	ctio->entry_type = CTIO_TYPE7;
	ctio->entry_count = 1;
	ctio->handle = QLA_TGT_SKIP_HANDLE | CTIO_COMPLETION_HANDLE_MARK;
	ctio->nport_handle = cpu_to_le16(mcmd->sess->loop_id);
	ctio->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	ctio->vp_index = ha->vp_idx;
	ctio->initiator_id = be_id_to_le(atio->u.isp24.fcp_hdr.s_id);
	ctio->exchange_addr = atio->u.isp24.exchange_addr;
	temp = (atio->u.isp24.attr << 9)|
		CTIO7_FLAGS_STATUS_MODE_1 | CTIO7_FLAGS_SEND_STATUS;
	ctio->u.status1.flags = cpu_to_le16(temp);
	temp = be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id);
	ctio->u.status1.ox_id = cpu_to_le16(temp);
	ctio->u.status1.scsi_status =
	    cpu_to_le16(SS_RESPONSE_INFO_LEN_VALID);
	ctio->u.status1.response_len = cpu_to_le16(8);
	ctio->u.status1.sense_data[0] = resp_code;

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(ha, qpair->req);
पूर्ण

व्योम qlt_मुक्त_mcmd(काष्ठा qla_tgt_mgmt_cmd *mcmd)
अणु
	mempool_मुक्त(mcmd, qla_tgt_mgmt_cmd_mempool);
पूर्ण
EXPORT_SYMBOL(qlt_मुक्त_mcmd);

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then
 * reacquire
 */
व्योम qlt_send_resp_ctio(काष्ठा qla_qpair *qpair, काष्ठा qla_tgt_cmd *cmd,
    uपूर्णांक8_t scsi_status, uपूर्णांक8_t sense_key, uपूर्णांक8_t asc, uपूर्णांक8_t ascq)
अणु
	काष्ठा atio_from_isp *atio = &cmd->atio;
	काष्ठा ctio7_to_24xx *ctio;
	uपूर्णांक16_t temp;
	काष्ठा scsi_qla_host *vha = cmd->vha;

	ql_dbg(ql_dbg_tgt_dअगर, vha, 0x3066,
	    "Sending response CTIO7 (vha=%p, atio=%p, scsi_status=%02x, "
	    "sense_key=%02x, asc=%02x, ascq=%02x",
	    vha, atio, scsi_status, sense_key, asc, ascq);

	ctio = (काष्ठा ctio7_to_24xx *)qla2x00_alloc_iocbs(vha, शून्य);
	अगर (!ctio) अणु
		ql_dbg(ql_dbg_async, vha, 0x3067,
		    "qla2x00t(%ld): %s failed: unable to allocate request packet",
		    vha->host_no, __func__);
		जाओ out;
	पूर्ण

	ctio->entry_type = CTIO_TYPE7;
	ctio->entry_count = 1;
	ctio->handle = QLA_TGT_SKIP_HANDLE;
	ctio->nport_handle = cpu_to_le16(cmd->sess->loop_id);
	ctio->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	ctio->vp_index = vha->vp_idx;
	ctio->initiator_id = be_id_to_le(atio->u.isp24.fcp_hdr.s_id);
	ctio->exchange_addr = atio->u.isp24.exchange_addr;
	temp = (atio->u.isp24.attr << 9) |
	    CTIO7_FLAGS_STATUS_MODE_1 | CTIO7_FLAGS_SEND_STATUS;
	ctio->u.status1.flags = cpu_to_le16(temp);
	temp = be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id);
	ctio->u.status1.ox_id = cpu_to_le16(temp);
	ctio->u.status1.scsi_status =
	    cpu_to_le16(SS_RESPONSE_INFO_LEN_VALID | scsi_status);
	ctio->u.status1.response_len = cpu_to_le16(18);
	ctio->u.status1.residual = cpu_to_le32(get_datalen_क्रम_atio(atio));

	अगर (ctio->u.status1.residual != 0)
		ctio->u.status1.scsi_status |=
		    cpu_to_le16(SS_RESIDUAL_UNDER);

	/* Fixed क्रमmat sense data. */
	ctio->u.status1.sense_data[0] = 0x70;
	ctio->u.status1.sense_data[2] = sense_key;
	/* Additional sense length */
	ctio->u.status1.sense_data[7] = 0xa;
	/* ASC and ASCQ */
	ctio->u.status1.sense_data[12] = asc;
	ctio->u.status1.sense_data[13] = ascq;

	/* Memory Barrier */
	wmb();

	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);

out:
	वापस;
पूर्ण

/* callback from target fabric module code */
व्योम qlt_xmit_पंचांग_rsp(काष्ठा qla_tgt_mgmt_cmd *mcmd)
अणु
	काष्ठा scsi_qla_host *vha = mcmd->sess->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_qpair *qpair = mcmd->qpair;
	bool मुक्त_mcmd = true;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf013,
	    "TM response mcmd (%p) status %#x state %#x",
	    mcmd, mcmd->fc_पंचांग_rsp, mcmd->flags);

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);

	अगर (!vha->flags.online || mcmd->reset_count != qpair->chip_reset) अणु
		/*
		 * Either the port is not online or this request was from
		 * previous lअगरe, just पात the processing.
		 */
		ql_dbg(ql_dbg_async, vha, 0xe100,
			"RESET-TMR online/active/old-count/new-count = %d/%d/%d/%d.\n",
			vha->flags.online, qla2x00_reset_active(vha),
			mcmd->reset_count, qpair->chip_reset);
		ha->tgt.tgt_ops->मुक्त_mcmd(mcmd);
		spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);
		वापस;
	पूर्ण

	अगर (mcmd->flags == QLA24XX_MGMT_SEND_NACK) अणु
		चयन (mcmd->orig_iocb.imm_ntfy.u.isp24.status_subcode) अणु
		हाल ELS_LOGO:
		हाल ELS_PRLO:
		हाल ELS_TPRLO:
			ql_dbg(ql_dbg_disc, vha, 0x2106,
			    "TM response logo %8phC status %#x state %#x",
			    mcmd->sess->port_name, mcmd->fc_पंचांग_rsp,
			    mcmd->flags);
			qlt_schedule_sess_क्रम_deletion(mcmd->sess);
			अवरोध;
		शेष:
			qlt_send_notअगरy_ack(vha->hw->base_qpair,
			    &mcmd->orig_iocb.imm_ntfy, 0, 0, 0, 0, 0, 0);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (mcmd->orig_iocb.atio.u.raw.entry_type == ABTS_RECV_24XX) अणु
			qlt_build_abts_resp_iocb(mcmd);
			मुक्त_mcmd = false;
		पूर्ण अन्यथा
			qlt_24xx_send_task_mgmt_ctio(qpair, mcmd,
			    mcmd->fc_पंचांग_rsp);
	पूर्ण
	/*
	 * Make the callback क्रम ->मुक्त_mcmd() to queue_work() and invoke
	 * target_put_sess_cmd() to drop cmd_kref to 1.  The final
	 * target_put_sess_cmd() call will be made from TFO->check_stop_मुक्त()
	 * -> tcm_qla2xxx_check_stop_मुक्त() to release the TMR associated se_cmd
	 * descriptor after TFO->queue_पंचांग_rsp() -> tcm_qla2xxx_queue_पंचांग_rsp() ->
	 * qlt_xmit_पंचांग_rsp() वापसs here..
	 */
	अगर (मुक्त_mcmd)
		ha->tgt.tgt_ops->मुक्त_mcmd(mcmd);

	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);
पूर्ण
EXPORT_SYMBOL(qlt_xmit_पंचांग_rsp);

/* No locks */
अटल पूर्णांक qlt_pci_map_calc_cnt(काष्ठा qla_tgt_prm *prm)
अणु
	काष्ठा qla_tgt_cmd *cmd = prm->cmd;

	BUG_ON(cmd->sg_cnt == 0);

	prm->sg = (काष्ठा scatterlist *)cmd->sg;
	prm->seg_cnt = dma_map_sg(&cmd->qpair->pdev->dev, cmd->sg,
	    cmd->sg_cnt, cmd->dma_data_direction);
	अगर (unlikely(prm->seg_cnt == 0))
		जाओ out_err;

	prm->cmd->sg_mapped = 1;

	अगर (cmd->se_cmd.prot_op == TARGET_PROT_NORMAL) अणु
		/*
		 * If greater than four sg entries then we need to allocate
		 * the continuation entries
		 */
		अगर (prm->seg_cnt > QLA_TGT_DATASEGS_PER_CMD_24XX)
			prm->req_cnt += DIV_ROUND_UP(prm->seg_cnt -
			QLA_TGT_DATASEGS_PER_CMD_24XX,
			QLA_TGT_DATASEGS_PER_CONT_24XX);
	पूर्ण अन्यथा अणु
		/* DIF */
		अगर ((cmd->se_cmd.prot_op == TARGET_PROT_DIN_INSERT) ||
		    (cmd->se_cmd.prot_op == TARGET_PROT_DOUT_STRIP)) अणु
			prm->seg_cnt = DIV_ROUND_UP(cmd->bufflen, cmd->blk_sz);
			prm->tot_dsds = prm->seg_cnt;
		पूर्ण अन्यथा
			prm->tot_dsds = prm->seg_cnt;

		अगर (cmd->prot_sg_cnt) अणु
			prm->prot_sg      = cmd->prot_sg;
			prm->prot_seg_cnt = dma_map_sg(&cmd->qpair->pdev->dev,
				cmd->prot_sg, cmd->prot_sg_cnt,
				cmd->dma_data_direction);
			अगर (unlikely(prm->prot_seg_cnt == 0))
				जाओ out_err;

			अगर ((cmd->se_cmd.prot_op == TARGET_PROT_DIN_INSERT) ||
			    (cmd->se_cmd.prot_op == TARGET_PROT_DOUT_STRIP)) अणु
				/* Dअगर Bundling not support here */
				prm->prot_seg_cnt = DIV_ROUND_UP(cmd->bufflen,
								cmd->blk_sz);
				prm->tot_dsds += prm->prot_seg_cnt;
			पूर्ण अन्यथा
				prm->tot_dsds += prm->prot_seg_cnt;
		पूर्ण
	पूर्ण

	वापस 0;

out_err:
	ql_dbg_qp(ql_dbg_tgt, prm->cmd->qpair, 0xe04d,
	    "qla_target(%d): PCI mapping failed: sg_cnt=%d",
	    0, prm->cmd->sg_cnt);
	वापस -1;
पूर्ण

अटल व्योम qlt_unmap_sg(काष्ठा scsi_qla_host *vha, काष्ठा qla_tgt_cmd *cmd)
अणु
	काष्ठा qla_hw_data *ha;
	काष्ठा qla_qpair *qpair;

	अगर (!cmd->sg_mapped)
		वापस;

	qpair = cmd->qpair;

	dma_unmap_sg(&qpair->pdev->dev, cmd->sg, cmd->sg_cnt,
	    cmd->dma_data_direction);
	cmd->sg_mapped = 0;

	अगर (cmd->prot_sg_cnt)
		dma_unmap_sg(&qpair->pdev->dev, cmd->prot_sg, cmd->prot_sg_cnt,
			cmd->dma_data_direction);

	अगर (!cmd->ctx)
		वापस;
	ha = vha->hw;
	अगर (cmd->ctx_dsd_alloced)
		qla2x00_clean_dsd_pool(ha, cmd->ctx);

	dma_pool_मुक्त(ha->dl_dma_pool, cmd->ctx, cmd->ctx->crc_ctx_dma);
पूर्ण

अटल पूर्णांक qlt_check_reserve_मुक्त_req(काष्ठा qla_qpair *qpair,
	uपूर्णांक32_t req_cnt)
अणु
	uपूर्णांक32_t cnt;
	काष्ठा req_que *req = qpair->req;

	अगर (req->cnt < (req_cnt + 2)) अणु
		cnt = (uपूर्णांक16_t)(qpair->use_shaकरोw_reg ? *req->out_ptr :
		    rd_reg_dword_relaxed(req->req_q_out));

		अगर  (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length - (req->ring_index - cnt);

		अगर (unlikely(req->cnt < (req_cnt + 2)))
			वापस -EAGAIN;
	पूर्ण

	req->cnt -= req_cnt;

	वापस 0;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल अंतरभूत व्योम *qlt_get_req_pkt(काष्ठा req_que *req)
अणु
	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा अणु
		req->ring_ptr++;
	पूर्ण
	वापस (cont_entry_t *)req->ring_ptr;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल अंतरभूत uपूर्णांक32_t qlt_make_handle(काष्ठा qla_qpair *qpair)
अणु
	uपूर्णांक32_t h;
	पूर्णांक index;
	uपूर्णांक8_t found = 0;
	काष्ठा req_que *req = qpair->req;

	h = req->current_outstanding_cmd;

	क्रम (index = 1; index < req->num_outstanding_cmds; index++) अणु
		h++;
		अगर (h == req->num_outstanding_cmds)
			h = 1;

		अगर (h == QLA_TGT_SKIP_HANDLE)
			जारी;

		अगर (!req->outstanding_cmds[h]) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (found) अणु
		req->current_outstanding_cmd = h;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_io, qpair->vha, 0x305b,
		    "qla_target(%d): Ran out of empty cmd slots\n",
		    qpair->vha->vp_idx);
		h = QLA_TGT_शून्य_HANDLE;
	पूर्ण

	वापस h;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक qlt_24xx_build_ctio_pkt(काष्ठा qla_qpair *qpair,
	काष्ठा qla_tgt_prm *prm)
अणु
	uपूर्णांक32_t h;
	काष्ठा ctio7_to_24xx *pkt;
	काष्ठा atio_from_isp *atio = &prm->cmd->atio;
	uपूर्णांक16_t temp;

	pkt = (काष्ठा ctio7_to_24xx *)qpair->req->ring_ptr;
	prm->pkt = pkt;
	स_रखो(pkt, 0, माप(*pkt));

	pkt->entry_type = CTIO_TYPE7;
	pkt->entry_count = (uपूर्णांक8_t)prm->req_cnt;
	pkt->vp_index = prm->cmd->vp_idx;

	h = qlt_make_handle(qpair);
	अगर (unlikely(h == QLA_TGT_शून्य_HANDLE)) अणु
		/*
		 * CTIO type 7 from the firmware करोesn't provide a way to
		 * know the initiator's LOOP ID, hence we can't find
		 * the session and, so, the command.
		 */
		वापस -EAGAIN;
	पूर्ण अन्यथा
		qpair->req->outstanding_cmds[h] = (srb_t *)prm->cmd;

	pkt->handle = make_handle(qpair->req->id, h);
	pkt->handle |= CTIO_COMPLETION_HANDLE_MARK;
	pkt->nport_handle = cpu_to_le16(prm->cmd->loop_id);
	pkt->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	pkt->initiator_id = be_id_to_le(atio->u.isp24.fcp_hdr.s_id);
	pkt->exchange_addr = atio->u.isp24.exchange_addr;
	temp = atio->u.isp24.attr << 9;
	pkt->u.status0.flags |= cpu_to_le16(temp);
	temp = be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id);
	pkt->u.status0.ox_id = cpu_to_le16(temp);
	pkt->u.status0.relative_offset = cpu_to_le32(prm->cmd->offset);

	वापस 0;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. We have alपढ़ोy made sure
 * that there is sufficient amount of request entries to not drop it.
 */
अटल व्योम qlt_load_cont_data_segments(काष्ठा qla_tgt_prm *prm)
अणु
	पूर्णांक cnt;
	काष्ठा dsd64 *cur_dsd;

	/* Build continuation packets */
	जबतक (prm->seg_cnt > 0) अणु
		cont_a64_entry_t *cont_pkt64 =
			(cont_a64_entry_t *)qlt_get_req_pkt(
			   prm->cmd->qpair->req);

		/*
		 * Make sure that from cont_pkt64 none of
		 * 64-bit specअगरic fields used क्रम 32-bit
		 * addressing. Cast to (cont_entry_t *) क्रम
		 * that.
		 */

		स_रखो(cont_pkt64, 0, माप(*cont_pkt64));

		cont_pkt64->entry_count = 1;
		cont_pkt64->sys_define = 0;

		cont_pkt64->entry_type = CONTINUE_A64_TYPE;
		cur_dsd = cont_pkt64->dsd;

		/* Load continuation entry data segments */
		क्रम (cnt = 0;
		    cnt < QLA_TGT_DATASEGS_PER_CONT_24XX && prm->seg_cnt;
		    cnt++, prm->seg_cnt--) अणु
			append_dsd64(&cur_dsd, prm->sg);
			prm->sg = sg_next(prm->sg);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. We have alपढ़ोy made sure
 * that there is sufficient amount of request entries to not drop it.
 */
अटल व्योम qlt_load_data_segments(काष्ठा qla_tgt_prm *prm)
अणु
	पूर्णांक cnt;
	काष्ठा dsd64 *cur_dsd;
	काष्ठा ctio7_to_24xx *pkt24 = (काष्ठा ctio7_to_24xx *)prm->pkt;

	pkt24->u.status0.transfer_length = cpu_to_le32(prm->cmd->bufflen);

	/* Setup packet address segment poपूर्णांकer */
	cur_dsd = &pkt24->u.status0.dsd;

	/* Set total data segment count */
	अगर (prm->seg_cnt)
		pkt24->dseg_count = cpu_to_le16(prm->seg_cnt);

	अगर (prm->seg_cnt == 0) अणु
		/* No data transfer */
		cur_dsd->address = 0;
		cur_dsd->length = 0;
		वापस;
	पूर्ण

	/* If scatter gather */

	/* Load command entry data segments */
	क्रम (cnt = 0;
	    (cnt < QLA_TGT_DATASEGS_PER_CMD_24XX) && prm->seg_cnt;
	    cnt++, prm->seg_cnt--) अणु
		append_dsd64(&cur_dsd, prm->sg);
		prm->sg = sg_next(prm->sg);
	पूर्ण

	qlt_load_cont_data_segments(prm);
पूर्ण

अटल अंतरभूत पूर्णांक qlt_has_data(काष्ठा qla_tgt_cmd *cmd)
अणु
	वापस cmd->bufflen > 0;
पूर्ण

अटल व्योम qlt_prपूर्णांक_dअगर_err(काष्ठा qla_tgt_prm *prm)
अणु
	काष्ठा qla_tgt_cmd *cmd;
	काष्ठा scsi_qla_host *vha;

	/* asc 0x10=dअगर error */
	अगर (prm->sense_buffer && (prm->sense_buffer[12] == 0x10)) अणु
		cmd = prm->cmd;
		vha = cmd->vha;
		/* ASCQ */
		चयन (prm->sense_buffer[13]) अणु
		हाल 1:
			ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe00b,
			    "BE detected Guard TAG ERR: lba[0x%llx|%lld] len[0x%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			अवरोध;
		हाल 2:
			ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe00c,
			    "BE detected APP TAG ERR: lba[0x%llx|%lld] len[0x%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			अवरोध;
		हाल 3:
			ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe00f,
			    "BE detected REF TAG ERR: lba[0x%llx|%lld] len[0x%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			अवरोध;
		शेष:
			ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe010,
			    "BE detected Dif ERR: lba[%llx|%lld] len[%x] "
			    "se_cmd=%p tag[%x]",
			    cmd->lba, cmd->lba, cmd->num_blks, &cmd->se_cmd,
			    cmd->atio.u.isp24.exchange_addr);
			अवरोध;
		पूर्ण
		ql_dump_buffer(ql_dbg_tgt_dअगर, vha, 0xe011, cmd->cdb, 16);
	पूर्ण
पूर्ण

/*
 * Called without ha->hardware_lock held
 */
अटल पूर्णांक qlt_pre_xmit_response(काष्ठा qla_tgt_cmd *cmd,
	काष्ठा qla_tgt_prm *prm, पूर्णांक xmit_type, uपूर्णांक8_t scsi_status,
	uपूर्णांक32_t *full_req_cnt)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	काष्ठा qla_qpair *qpair = cmd->qpair;

	prm->cmd = cmd;
	prm->tgt = cmd->tgt;
	prm->pkt = शून्य;
	prm->rq_result = scsi_status;
	prm->sense_buffer = &cmd->sense_buffer[0];
	prm->sense_buffer_len = TRANSPORT_SENSE_BUFFER;
	prm->sg = शून्य;
	prm->seg_cnt = -1;
	prm->req_cnt = 1;
	prm->residual = 0;
	prm->add_status_pkt = 0;
	prm->prot_sg = शून्य;
	prm->prot_seg_cnt = 0;
	prm->tot_dsds = 0;

	अगर ((xmit_type & QLA_TGT_XMIT_DATA) && qlt_has_data(cmd)) अणु
		अगर  (qlt_pci_map_calc_cnt(prm) != 0)
			वापस -EAGAIN;
	पूर्ण

	*full_req_cnt = prm->req_cnt;

	अगर (se_cmd->se_cmd_flags & SCF_UNDERFLOW_BIT) अणु
		prm->residual = se_cmd->residual_count;
		ql_dbg_qp(ql_dbg_io + ql_dbg_verbose, qpair, 0x305c,
		    "Residual underflow: %d (tag %lld, op %x, bufflen %d, rq_result %x)\n",
		       prm->residual, se_cmd->tag,
		       se_cmd->t_task_cdb ? se_cmd->t_task_cdb[0] : 0,
		       cmd->bufflen, prm->rq_result);
		prm->rq_result |= SS_RESIDUAL_UNDER;
	पूर्ण अन्यथा अगर (se_cmd->se_cmd_flags & SCF_OVERFLOW_BIT) अणु
		prm->residual = se_cmd->residual_count;
		ql_dbg_qp(ql_dbg_io, qpair, 0x305d,
		    "Residual overflow: %d (tag %lld, op %x, bufflen %d, rq_result %x)\n",
		       prm->residual, se_cmd->tag, se_cmd->t_task_cdb ?
		       se_cmd->t_task_cdb[0] : 0, cmd->bufflen, prm->rq_result);
		prm->rq_result |= SS_RESIDUAL_OVER;
	पूर्ण

	अगर (xmit_type & QLA_TGT_XMIT_STATUS) अणु
		/*
		 * If QLA_TGT_XMIT_DATA is not set, add_status_pkt will be
		 * ignored in *xmit_response() below
		 */
		अगर (qlt_has_data(cmd)) अणु
			अगर (QLA_TGT_SENSE_VALID(prm->sense_buffer) ||
			    (IS_FWI2_CAPABLE(cmd->vha->hw) &&
			    (prm->rq_result != 0))) अणु
				prm->add_status_pkt = 1;
				(*full_req_cnt)++;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक qlt_need_explicit_conf(काष्ठा qla_tgt_cmd *cmd,
    पूर्णांक sending_sense)
अणु
	अगर (cmd->qpair->enable_class_2)
		वापस 0;

	अगर (sending_sense)
		वापस cmd->conf_compl_supported;
	अन्यथा
		वापस cmd->qpair->enable_explicit_conf &&
                    cmd->conf_compl_supported;
पूर्ण

अटल व्योम qlt_24xx_init_ctio_to_isp(काष्ठा ctio7_to_24xx *ctio,
	काष्ठा qla_tgt_prm *prm)
अणु
	prm->sense_buffer_len = min_t(uपूर्णांक32_t, prm->sense_buffer_len,
	    (uपूर्णांक32_t)माप(ctio->u.status1.sense_data));
	ctio->u.status0.flags |= cpu_to_le16(CTIO7_FLAGS_SEND_STATUS);
	अगर (qlt_need_explicit_conf(prm->cmd, 0)) अणु
		ctio->u.status0.flags |= cpu_to_le16(
		    CTIO7_FLAGS_EXPLICIT_CONFORM |
		    CTIO7_FLAGS_CONFORM_REQ);
	पूर्ण
	ctio->u.status0.residual = cpu_to_le32(prm->residual);
	ctio->u.status0.scsi_status = cpu_to_le16(prm->rq_result);
	अगर (QLA_TGT_SENSE_VALID(prm->sense_buffer)) अणु
		पूर्णांक i;

		अगर (qlt_need_explicit_conf(prm->cmd, 1)) अणु
			अगर ((prm->rq_result & SS_SCSI_STATUS_BYTE) != 0) अणु
				ql_dbg_qp(ql_dbg_tgt, prm->cmd->qpair, 0xe017,
				    "Skipping EXPLICIT_CONFORM and "
				    "CTIO7_FLAGS_CONFORM_REQ for FCP READ w/ "
				    "non GOOD status\n");
				जाओ skip_explict_conf;
			पूर्ण
			ctio->u.status1.flags |= cpu_to_le16(
			    CTIO7_FLAGS_EXPLICIT_CONFORM |
			    CTIO7_FLAGS_CONFORM_REQ);
		पूर्ण
skip_explict_conf:
		ctio->u.status1.flags &=
		    ~cpu_to_le16(CTIO7_FLAGS_STATUS_MODE_0);
		ctio->u.status1.flags |=
		    cpu_to_le16(CTIO7_FLAGS_STATUS_MODE_1);
		ctio->u.status1.scsi_status |=
		    cpu_to_le16(SS_SENSE_LEN_VALID);
		ctio->u.status1.sense_length =
		    cpu_to_le16(prm->sense_buffer_len);
		क्रम (i = 0; i < prm->sense_buffer_len/4; i++) अणु
			uपूर्णांक32_t v;

			v = get_unaligned_be32(
					&((uपूर्णांक32_t *)prm->sense_buffer)[i]);
			put_unaligned_le32(v,
				&((uपूर्णांक32_t *)ctio->u.status1.sense_data)[i]);
		पूर्ण
		qlt_prपूर्णांक_dअगर_err(prm);

	पूर्ण अन्यथा अणु
		ctio->u.status1.flags &=
		    ~cpu_to_le16(CTIO7_FLAGS_STATUS_MODE_0);
		ctio->u.status1.flags |=
		    cpu_to_le16(CTIO7_FLAGS_STATUS_MODE_1);
		ctio->u.status1.sense_length = 0;
		स_रखो(ctio->u.status1.sense_data, 0,
		    माप(ctio->u.status1.sense_data));
	पूर्ण

	/* Sense with len > 24, is it possible ??? */
पूर्ण

अटल अंतरभूत पूर्णांक
qlt_hba_err_chk_enabled(काष्ठा se_cmd *se_cmd)
अणु
	चयन (se_cmd->prot_op) अणु
	हाल TARGET_PROT_DOUT_INSERT:
	हाल TARGET_PROT_DIN_STRIP:
		अगर (ql2xenablehba_err_chk >= 1)
			वापस 1;
		अवरोध;
	हाल TARGET_PROT_DOUT_PASS:
	हाल TARGET_PROT_DIN_PASS:
		अगर (ql2xenablehba_err_chk >= 2)
			वापस 1;
		अवरोध;
	हाल TARGET_PROT_DIN_INSERT:
	हाल TARGET_PROT_DOUT_STRIP:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
qla_tgt_ref_mask_check(काष्ठा se_cmd *se_cmd)
अणु
	चयन (se_cmd->prot_op) अणु
	हाल TARGET_PROT_DIN_INSERT:
	हाल TARGET_PROT_DOUT_INSERT:
	हाल TARGET_PROT_DIN_STRIP:
	हाल TARGET_PROT_DOUT_STRIP:
	हाल TARGET_PROT_DIN_PASS:
	हाल TARGET_PROT_DOUT_PASS:
	    वापस 1;
	शेष:
	    वापस 0;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * qla_tgt_set_dअगर_tags - Extract Ref and App tags from SCSI command
 */
अटल व्योम
qla_tgt_set_dअगर_tags(काष्ठा qla_tgt_cmd *cmd, काष्ठा crc_context *ctx,
    uपूर्णांक16_t *pfw_prot_opts)
अणु
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	uपूर्णांक32_t lba = 0xffffffff & se_cmd->t_task_lba;
	scsi_qla_host_t *vha = cmd->tgt->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t t32 = 0;

	/*
	 * रुको till Mode Sense/Select cmd, modepage Ah, subpage 2
	 * have been immplemented by TCM, beक्रमe AppTag is avail.
	 * Look क्रम modesense_handlers[]
	 */
	ctx->app_tag = 0;
	ctx->app_tag_mask[0] = 0x0;
	ctx->app_tag_mask[1] = 0x0;

	अगर (IS_PI_UNINIT_CAPABLE(ha)) अणु
		अगर ((se_cmd->prot_type == TARGET_DIF_TYPE1_PROT) ||
		    (se_cmd->prot_type == TARGET_DIF_TYPE2_PROT))
			*pfw_prot_opts |= PO_DIS_VALD_APP_ESC;
		अन्यथा अगर (se_cmd->prot_type == TARGET_DIF_TYPE3_PROT)
			*pfw_prot_opts |= PO_DIS_VALD_APP_REF_ESC;
	पूर्ण

	t32 = ha->tgt.tgt_ops->get_dअगर_tags(cmd, pfw_prot_opts);

	चयन (se_cmd->prot_type) अणु
	हाल TARGET_DIF_TYPE0_PROT:
		/*
		 * No check क्रम ql2xenablehba_err_chk, as it
		 * would be an I/O error अगर hba tag generation
		 * is not करोne.
		 */
		ctx->ref_tag = cpu_to_le32(lba);
		/* enable ALL bytes of the ref tag */
		ctx->ref_tag_mask[0] = 0xff;
		ctx->ref_tag_mask[1] = 0xff;
		ctx->ref_tag_mask[2] = 0xff;
		ctx->ref_tag_mask[3] = 0xff;
		अवरोध;
	हाल TARGET_DIF_TYPE1_PROT:
	    /*
	     * For TYPE 1 protection: 16 bit GUARD tag, 32 bit
	     * REF tag, and 16 bit app tag.
	     */
	    ctx->ref_tag = cpu_to_le32(lba);
	    अगर (!qla_tgt_ref_mask_check(se_cmd) ||
		!(ha->tgt.tgt_ops->chk_dअगर_tags(t32))) अणु
		    *pfw_prot_opts |= PO_DIS_REF_TAG_VALD;
		    अवरोध;
	    पूर्ण
	    /* enable ALL bytes of the ref tag */
	    ctx->ref_tag_mask[0] = 0xff;
	    ctx->ref_tag_mask[1] = 0xff;
	    ctx->ref_tag_mask[2] = 0xff;
	    ctx->ref_tag_mask[3] = 0xff;
	    अवरोध;
	हाल TARGET_DIF_TYPE2_PROT:
	    /*
	     * For TYPE 2 protection: 16 bit GUARD + 32 bit REF
	     * tag has to match LBA in CDB + N
	     */
	    ctx->ref_tag = cpu_to_le32(lba);
	    अगर (!qla_tgt_ref_mask_check(se_cmd) ||
		!(ha->tgt.tgt_ops->chk_dअगर_tags(t32))) अणु
		    *pfw_prot_opts |= PO_DIS_REF_TAG_VALD;
		    अवरोध;
	    पूर्ण
	    /* enable ALL bytes of the ref tag */
	    ctx->ref_tag_mask[0] = 0xff;
	    ctx->ref_tag_mask[1] = 0xff;
	    ctx->ref_tag_mask[2] = 0xff;
	    ctx->ref_tag_mask[3] = 0xff;
	    अवरोध;
	हाल TARGET_DIF_TYPE3_PROT:
	    /* For TYPE 3 protection: 16 bit GUARD only */
	    *pfw_prot_opts |= PO_DIS_REF_TAG_VALD;
	    ctx->ref_tag_mask[0] = ctx->ref_tag_mask[1] =
		ctx->ref_tag_mask[2] = ctx->ref_tag_mask[3] = 0x00;
	    अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
qlt_build_ctio_crc2_pkt(काष्ठा qla_qpair *qpair, काष्ठा qla_tgt_prm *prm)
अणु
	काष्ठा dsd64		*cur_dsd;
	uपूर्णांक32_t		transfer_length = 0;
	uपूर्णांक32_t		data_bytes;
	uपूर्णांक32_t		dअगर_bytes;
	uपूर्णांक8_t			bundling = 1;
	काष्ठा crc_context	*crc_ctx_pkt = शून्य;
	काष्ठा qla_hw_data	*ha;
	काष्ठा ctio_crc2_to_fw	*pkt;
	dma_addr_t		crc_ctx_dma;
	uपूर्णांक16_t		fw_prot_opts = 0;
	काष्ठा qla_tgt_cmd	*cmd = prm->cmd;
	काष्ठा se_cmd		*se_cmd = &cmd->se_cmd;
	uपूर्णांक32_t h;
	काष्ठा atio_from_isp *atio = &prm->cmd->atio;
	काष्ठा qla_tc_param	tc;
	uपूर्णांक16_t t16;
	scsi_qla_host_t *vha = cmd->vha;

	ha = vha->hw;

	pkt = (काष्ठा ctio_crc2_to_fw *)qpair->req->ring_ptr;
	prm->pkt = pkt;
	स_रखो(pkt, 0, माप(*pkt));

	ql_dbg_qp(ql_dbg_tgt, cmd->qpair, 0xe071,
		"qla_target(%d):%s: se_cmd[%p] CRC2 prot_op[0x%x] cmd prot sg:cnt[%p:%x] lba[%llu]\n",
		cmd->vp_idx, __func__, se_cmd, se_cmd->prot_op,
		prm->prot_sg, prm->prot_seg_cnt, se_cmd->t_task_lba);

	अगर ((se_cmd->prot_op == TARGET_PROT_DIN_INSERT) ||
	    (se_cmd->prot_op == TARGET_PROT_DOUT_STRIP))
		bundling = 0;

	/* Compute dअगर len and adjust data len to incude protection */
	data_bytes = cmd->bufflen;
	dअगर_bytes  = (data_bytes / cmd->blk_sz) * 8;

	चयन (se_cmd->prot_op) अणु
	हाल TARGET_PROT_DIN_INSERT:
	हाल TARGET_PROT_DOUT_STRIP:
		transfer_length = data_bytes;
		अगर (cmd->prot_sg_cnt)
			data_bytes += dअगर_bytes;
		अवरोध;
	हाल TARGET_PROT_DIN_STRIP:
	हाल TARGET_PROT_DOUT_INSERT:
	हाल TARGET_PROT_DIN_PASS:
	हाल TARGET_PROT_DOUT_PASS:
		transfer_length = data_bytes + dअगर_bytes;
		अवरोध;
	शेष:
		BUG();
		अवरोध;
	पूर्ण

	अगर (!qlt_hba_err_chk_enabled(se_cmd))
		fw_prot_opts |= 0x10; /* Disable Guard tag checking */
	/* HBA error checking enabled */
	अन्यथा अगर (IS_PI_UNINIT_CAPABLE(ha)) अणु
		अगर ((se_cmd->prot_type == TARGET_DIF_TYPE1_PROT) ||
		    (se_cmd->prot_type == TARGET_DIF_TYPE2_PROT))
			fw_prot_opts |= PO_DIS_VALD_APP_ESC;
		अन्यथा अगर (se_cmd->prot_type == TARGET_DIF_TYPE3_PROT)
			fw_prot_opts |= PO_DIS_VALD_APP_REF_ESC;
	पूर्ण

	चयन (se_cmd->prot_op) अणु
	हाल TARGET_PROT_DIN_INSERT:
	हाल TARGET_PROT_DOUT_INSERT:
		fw_prot_opts |= PO_MODE_DIF_INSERT;
		अवरोध;
	हाल TARGET_PROT_DIN_STRIP:
	हाल TARGET_PROT_DOUT_STRIP:
		fw_prot_opts |= PO_MODE_DIF_REMOVE;
		अवरोध;
	हाल TARGET_PROT_DIN_PASS:
	हाल TARGET_PROT_DOUT_PASS:
		fw_prot_opts |= PO_MODE_DIF_PASS;
		/* FUTURE: करोes tcm require T10CRC<->IPCKSUM conversion? */
		अवरोध;
	शेष:/* Normal Request */
		fw_prot_opts |= PO_MODE_DIF_PASS;
		अवरोध;
	पूर्ण

	/* ---- PKT ---- */
	/* Update entry type to indicate Command Type CRC_2 IOCB */
	pkt->entry_type  = CTIO_CRC2;
	pkt->entry_count = 1;
	pkt->vp_index = cmd->vp_idx;

	h = qlt_make_handle(qpair);
	अगर (unlikely(h == QLA_TGT_शून्य_HANDLE)) अणु
		/*
		 * CTIO type 7 from the firmware करोesn't provide a way to
		 * know the initiator's LOOP ID, hence we can't find
		 * the session and, so, the command.
		 */
		वापस -EAGAIN;
	पूर्ण अन्यथा
		qpair->req->outstanding_cmds[h] = (srb_t *)prm->cmd;

	pkt->handle  = make_handle(qpair->req->id, h);
	pkt->handle |= CTIO_COMPLETION_HANDLE_MARK;
	pkt->nport_handle = cpu_to_le16(prm->cmd->loop_id);
	pkt->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	pkt->initiator_id = be_id_to_le(atio->u.isp24.fcp_hdr.s_id);
	pkt->exchange_addr   = atio->u.isp24.exchange_addr;

	/* silence compile warning */
	t16 = be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id);
	pkt->ox_id  = cpu_to_le16(t16);

	t16 = (atio->u.isp24.attr << 9);
	pkt->flags |= cpu_to_le16(t16);
	pkt->relative_offset = cpu_to_le32(prm->cmd->offset);

	/* Set transfer direction */
	अगर (cmd->dma_data_direction == DMA_TO_DEVICE)
		pkt->flags = cpu_to_le16(CTIO7_FLAGS_DATA_IN);
	अन्यथा अगर (cmd->dma_data_direction == DMA_FROM_DEVICE)
		pkt->flags = cpu_to_le16(CTIO7_FLAGS_DATA_OUT);

	pkt->dseg_count = cpu_to_le16(prm->tot_dsds);
	/* Fibre channel byte count */
	pkt->transfer_length = cpu_to_le32(transfer_length);

	/* ----- CRC context -------- */

	/* Allocate CRC context from global pool */
	crc_ctx_pkt = cmd->ctx =
	    dma_pool_zalloc(ha->dl_dma_pool, GFP_ATOMIC, &crc_ctx_dma);

	अगर (!crc_ctx_pkt)
		जाओ crc_queuing_error;

	crc_ctx_pkt->crc_ctx_dma = crc_ctx_dma;
	INIT_LIST_HEAD(&crc_ctx_pkt->dsd_list);

	/* Set handle */
	crc_ctx_pkt->handle = pkt->handle;

	qla_tgt_set_dअगर_tags(cmd, crc_ctx_pkt, &fw_prot_opts);

	put_unaligned_le64(crc_ctx_dma, &pkt->crc_context_address);
	pkt->crc_context_len = cpu_to_le16(CRC_CONTEXT_LEN_FW);

	अगर (!bundling) अणु
		cur_dsd = &crc_ctx_pkt->u.nobundling.data_dsd[0];
	पूर्ण अन्यथा अणु
		/*
		 * Configure Bundling अगर we need to fetch पूर्णांकerlaving
		 * protection PCI accesses
		 */
		fw_prot_opts |= PO_ENABLE_DIF_BUNDLING;
		crc_ctx_pkt->u.bundling.dअगर_byte_count = cpu_to_le32(dअगर_bytes);
		crc_ctx_pkt->u.bundling.dseg_count =
			cpu_to_le16(prm->tot_dsds - prm->prot_seg_cnt);
		cur_dsd = &crc_ctx_pkt->u.bundling.data_dsd[0];
	पूर्ण

	/* Finish the common fields of CRC pkt */
	crc_ctx_pkt->blk_size   = cpu_to_le16(cmd->blk_sz);
	crc_ctx_pkt->prot_opts  = cpu_to_le16(fw_prot_opts);
	crc_ctx_pkt->byte_count = cpu_to_le32(data_bytes);
	crc_ctx_pkt->guard_seed = cpu_to_le16(0);

	स_रखो((uपूर्णांक8_t *)&tc, 0 , माप(tc));
	tc.vha = vha;
	tc.blk_sz = cmd->blk_sz;
	tc.bufflen = cmd->bufflen;
	tc.sg = cmd->sg;
	tc.prot_sg = cmd->prot_sg;
	tc.ctx = crc_ctx_pkt;
	tc.ctx_dsd_alloced = &cmd->ctx_dsd_alloced;

	/* Walks data segments */
	pkt->flags |= cpu_to_le16(CTIO7_FLAGS_DSD_PTR);

	अगर (!bundling && prm->prot_seg_cnt) अणु
		अगर (qla24xx_walk_and_build_sglist_no_dअगरb(ha, शून्य, cur_dsd,
			prm->tot_dsds, &tc))
			जाओ crc_queuing_error;
	पूर्ण अन्यथा अगर (qla24xx_walk_and_build_sglist(ha, शून्य, cur_dsd,
		(prm->tot_dsds - prm->prot_seg_cnt), &tc))
		जाओ crc_queuing_error;

	अगर (bundling && prm->prot_seg_cnt) अणु
		/* Walks dअगर segments */
		pkt->add_flags |= CTIO_CRC2_AF_DIF_DSD_ENA;

		cur_dsd = &crc_ctx_pkt->u.bundling.dअगर_dsd;
		अगर (qla24xx_walk_and_build_prot_sglist(ha, शून्य, cur_dsd,
			prm->prot_seg_cnt, cmd))
			जाओ crc_queuing_error;
	पूर्ण
	वापस QLA_SUCCESS;

crc_queuing_error:
	/* Cleanup will be perक्रमmed by the caller */
	qpair->req->outstanding_cmds[h] = शून्य;

	वापस QLA_FUNCTION_FAILED;
पूर्ण

/*
 * Callback to setup response of xmit_type of QLA_TGT_XMIT_DATA and *
 * QLA_TGT_XMIT_STATUS क्रम >= 24xx silicon
 */
पूर्णांक qlt_xmit_response(काष्ठा qla_tgt_cmd *cmd, पूर्णांक xmit_type,
	uपूर्णांक8_t scsi_status)
अणु
	काष्ठा scsi_qla_host *vha = cmd->vha;
	काष्ठा qla_qpair *qpair = cmd->qpair;
	काष्ठा ctio7_to_24xx *pkt;
	काष्ठा qla_tgt_prm prm;
	uपूर्णांक32_t full_req_cnt = 0;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक res;

	अगर (!qpair->fw_started || (cmd->reset_count != qpair->chip_reset) ||
	    (cmd->sess && cmd->sess->deleted)) अणु
		cmd->state = QLA_TGT_STATE_PROCESSED;
		वापस 0;
	पूर्ण

	ql_dbg_qp(ql_dbg_tgt, qpair, 0xe018,
	    "is_send_status=%d, cmd->bufflen=%d, cmd->sg_cnt=%d, cmd->dma_data_direction=%d se_cmd[%p] qp %d\n",
	    (xmit_type & QLA_TGT_XMIT_STATUS) ?
	    1 : 0, cmd->bufflen, cmd->sg_cnt, cmd->dma_data_direction,
	    &cmd->se_cmd, qpair->id);

	res = qlt_pre_xmit_response(cmd, &prm, xmit_type, scsi_status,
	    &full_req_cnt);
	अगर (unlikely(res != 0)) अणु
		वापस res;
	पूर्ण

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);

	अगर (xmit_type == QLA_TGT_XMIT_STATUS)
		qpair->tgt_counters.core_qla_snd_status++;
	अन्यथा
		qpair->tgt_counters.core_qla_que_buf++;

	अगर (!qpair->fw_started || cmd->reset_count != qpair->chip_reset) अणु
		/*
		 * Either the port is not online or this request was from
		 * previous lअगरe, just पात the processing.
		 */
		cmd->state = QLA_TGT_STATE_PROCESSED;
		ql_dbg_qp(ql_dbg_async, qpair, 0xe101,
			"RESET-RSP online/active/old-count/new-count = %d/%d/%d/%d.\n",
			vha->flags.online, qla2x00_reset_active(vha),
			cmd->reset_count, qpair->chip_reset);
		spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);
		वापस 0;
	पूर्ण

	/* Does F/W have an IOCBs क्रम this request */
	res = qlt_check_reserve_मुक्त_req(qpair, full_req_cnt);
	अगर (unlikely(res))
		जाओ out_unmap_unlock;

	अगर (cmd->se_cmd.prot_op && (xmit_type & QLA_TGT_XMIT_DATA))
		res = qlt_build_ctio_crc2_pkt(qpair, &prm);
	अन्यथा
		res = qlt_24xx_build_ctio_pkt(qpair, &prm);
	अगर (unlikely(res != 0)) अणु
		qpair->req->cnt += full_req_cnt;
		जाओ out_unmap_unlock;
	पूर्ण

	pkt = (काष्ठा ctio7_to_24xx *)prm.pkt;

	अगर (qlt_has_data(cmd) && (xmit_type & QLA_TGT_XMIT_DATA)) अणु
		pkt->u.status0.flags |=
		    cpu_to_le16(CTIO7_FLAGS_DATA_IN |
			CTIO7_FLAGS_STATUS_MODE_0);

		अगर (cmd->se_cmd.prot_op == TARGET_PROT_NORMAL)
			qlt_load_data_segments(&prm);

		अगर (prm.add_status_pkt == 0) अणु
			अगर (xmit_type & QLA_TGT_XMIT_STATUS) अणु
				pkt->u.status0.scsi_status =
				    cpu_to_le16(prm.rq_result);
				pkt->u.status0.residual =
				    cpu_to_le32(prm.residual);
				pkt->u.status0.flags |= cpu_to_le16(
				    CTIO7_FLAGS_SEND_STATUS);
				अगर (qlt_need_explicit_conf(cmd, 0)) अणु
					pkt->u.status0.flags |=
					    cpu_to_le16(
						CTIO7_FLAGS_EXPLICIT_CONFORM |
						CTIO7_FLAGS_CONFORM_REQ);
				पूर्ण
			पूर्ण

		पूर्ण अन्यथा अणु
			/*
			 * We have alपढ़ोy made sure that there is sufficient
			 * amount of request entries to not drop HW lock in
			 * req_pkt().
			 */
			काष्ठा ctio7_to_24xx *ctio =
				(काष्ठा ctio7_to_24xx *)qlt_get_req_pkt(
				    qpair->req);

			ql_dbg_qp(ql_dbg_tgt, qpair, 0x305e,
			    "Building additional status packet 0x%p.\n",
			    ctio);

			/*
			 * T10Dअगर: ctio_crc2_to_fw overlay ontop of
			 * ctio7_to_24xx
			 */
			स_नकल(ctio, pkt, माप(*ctio));
			/* reset back to CTIO7 */
			ctio->entry_count = 1;
			ctio->entry_type = CTIO_TYPE7;
			ctio->dseg_count = 0;
			ctio->u.status1.flags &= ~cpu_to_le16(
			    CTIO7_FLAGS_DATA_IN);

			/* Real finish is ctio_m1's finish */
			pkt->handle |= CTIO_INTERMEDIATE_HANDLE_MARK;
			pkt->u.status0.flags |= cpu_to_le16(
			    CTIO7_FLAGS_DONT_RET_CTIO);

			/* qlt_24xx_init_ctio_to_isp will correct
			 * all neccessary fields that's part of CTIO7.
			 * There should be no residual of CTIO-CRC2 data.
			 */
			qlt_24xx_init_ctio_to_isp((काष्ठा ctio7_to_24xx *)ctio,
			    &prm);
		पूर्ण
	पूर्ण अन्यथा
		qlt_24xx_init_ctio_to_isp(pkt, &prm);


	cmd->state = QLA_TGT_STATE_PROCESSED; /* Mid-level is करोne processing */
	cmd->cmd_sent_to_fw = 1;
	cmd->ctio_flags = le16_to_cpu(pkt->u.status0.flags);

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	वापस 0;

out_unmap_unlock:
	qlt_unmap_sg(vha, cmd);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(qlt_xmit_response);

पूर्णांक qlt_rdy_to_xfer(काष्ठा qla_tgt_cmd *cmd)
अणु
	काष्ठा ctio7_to_24xx *pkt;
	काष्ठा scsi_qla_host *vha = cmd->vha;
	काष्ठा qla_tgt *tgt = cmd->tgt;
	काष्ठा qla_tgt_prm prm;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक res = 0;
	काष्ठा qla_qpair *qpair = cmd->qpair;

	स_रखो(&prm, 0, माप(prm));
	prm.cmd = cmd;
	prm.tgt = tgt;
	prm.sg = शून्य;
	prm.req_cnt = 1;

	/* Calculate number of entries and segments required */
	अगर (qlt_pci_map_calc_cnt(&prm) != 0)
		वापस -EAGAIN;

	अगर (!qpair->fw_started || (cmd->reset_count != qpair->chip_reset) ||
	    (cmd->sess && cmd->sess->deleted)) अणु
		/*
		 * Either the port is not online or this request was from
		 * previous lअगरe, just पात the processing.
		 */
		cmd->पातed = 1;
		cmd->ग_लिखो_data_transferred = 0;
		cmd->state = QLA_TGT_STATE_DATA_IN;
		vha->hw->tgt.tgt_ops->handle_data(cmd);
		ql_dbg_qp(ql_dbg_async, qpair, 0xe102,
			"RESET-XFR online/active/old-count/new-count = %d/%d/%d/%d.\n",
			vha->flags.online, qla2x00_reset_active(vha),
			cmd->reset_count, qpair->chip_reset);
		वापस 0;
	पूर्ण

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	/* Does F/W have an IOCBs क्रम this request */
	res = qlt_check_reserve_मुक्त_req(qpair, prm.req_cnt);
	अगर (res != 0)
		जाओ out_unlock_मुक्त_unmap;
	अगर (cmd->se_cmd.prot_op)
		res = qlt_build_ctio_crc2_pkt(qpair, &prm);
	अन्यथा
		res = qlt_24xx_build_ctio_pkt(qpair, &prm);

	अगर (unlikely(res != 0)) अणु
		qpair->req->cnt += prm.req_cnt;
		जाओ out_unlock_मुक्त_unmap;
	पूर्ण

	pkt = (काष्ठा ctio7_to_24xx *)prm.pkt;
	pkt->u.status0.flags |= cpu_to_le16(CTIO7_FLAGS_DATA_OUT |
	    CTIO7_FLAGS_STATUS_MODE_0);

	अगर (cmd->se_cmd.prot_op == TARGET_PROT_NORMAL)
		qlt_load_data_segments(&prm);

	cmd->state = QLA_TGT_STATE_NEED_DATA;
	cmd->cmd_sent_to_fw = 1;
	cmd->ctio_flags = le16_to_cpu(pkt->u.status0.flags);

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	वापस res;

out_unlock_मुक्त_unmap:
	qlt_unmap_sg(vha, cmd);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	वापस res;
पूर्ण
EXPORT_SYMBOL(qlt_rdy_to_xfer);


/*
 * it is assumed either hardware_lock or qpair lock is held.
 */
अटल व्योम
qlt_handle_dअगर_error(काष्ठा qla_qpair *qpair, काष्ठा qla_tgt_cmd *cmd,
	काष्ठा ctio_crc_from_fw *sts)
अणु
	uपूर्णांक8_t		*ap = &sts->actual_dअगर[0];
	uपूर्णांक8_t		*ep = &sts->expected_dअगर[0];
	uपूर्णांक64_t	lba = cmd->se_cmd.t_task_lba;
	uपूर्णांक8_t scsi_status, sense_key, asc, ascq;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_qla_host *vha = cmd->vha;

	cmd->trc_flags |= TRC_DIF_ERR;

	cmd->a_guard   = get_unaligned_be16(ap + 0);
	cmd->a_app_tag = get_unaligned_be16(ap + 2);
	cmd->a_ref_tag = get_unaligned_be32(ap + 4);

	cmd->e_guard   = get_unaligned_be16(ep + 0);
	cmd->e_app_tag = get_unaligned_be16(ep + 2);
	cmd->e_ref_tag = get_unaligned_be32(ep + 4);

	ql_dbg(ql_dbg_tgt_dअगर, vha, 0xf075,
	    "%s: aborted %d state %d\n", __func__, cmd->पातed, cmd->state);

	scsi_status = sense_key = asc = ascq = 0;

	/* check appl tag */
	अगर (cmd->e_app_tag != cmd->a_app_tag) अणु
		ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe00d,
		    "App Tag ERR: cdb[%x] lba[%llx %llx] blks[%x] [Actual|Expected] Ref[%x|%x], App[%x|%x], Guard [%x|%x] cmd=%p ox_id[%04x]",
		    cmd->cdb[0], lba, (lba+cmd->num_blks), cmd->num_blks,
		    cmd->a_ref_tag, cmd->e_ref_tag, cmd->a_app_tag,
		    cmd->e_app_tag, cmd->a_guard, cmd->e_guard, cmd,
		    cmd->atio.u.isp24.fcp_hdr.ox_id);

		cmd->dअगर_err_code = DIF_ERR_APP;
		scsi_status = SAM_STAT_CHECK_CONDITION;
		sense_key = ABORTED_COMMAND;
		asc = 0x10;
		ascq = 0x2;
	पूर्ण

	/* check ref tag */
	अगर (cmd->e_ref_tag != cmd->a_ref_tag) अणु
		ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe00e,
		    "Ref Tag ERR: cdb[%x] lba[%llx %llx] blks[%x] [Actual|Expected] Ref[%x|%x], App[%x|%x], Guard[%x|%x] cmd=%p ox_id[%04x] ",
		    cmd->cdb[0], lba, (lba+cmd->num_blks), cmd->num_blks,
		    cmd->a_ref_tag, cmd->e_ref_tag, cmd->a_app_tag,
		    cmd->e_app_tag, cmd->a_guard, cmd->e_guard, cmd,
		    cmd->atio.u.isp24.fcp_hdr.ox_id);

		cmd->dअगर_err_code = DIF_ERR_REF;
		scsi_status = SAM_STAT_CHECK_CONDITION;
		sense_key = ABORTED_COMMAND;
		asc = 0x10;
		ascq = 0x3;
		जाओ out;
	पूर्ण

	/* check guard */
	अगर (cmd->e_guard != cmd->a_guard) अणु
		ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe012,
		    "Guard ERR: cdb[%x] lba[%llx %llx] blks[%x] [Actual|Expected] Ref[%x|%x], App[%x|%x], Guard [%x|%x] cmd=%p ox_id[%04x]",
		    cmd->cdb[0], lba, (lba+cmd->num_blks), cmd->num_blks,
		    cmd->a_ref_tag, cmd->e_ref_tag, cmd->a_app_tag,
		    cmd->e_app_tag, cmd->a_guard, cmd->e_guard, cmd,
		    cmd->atio.u.isp24.fcp_hdr.ox_id);

		cmd->dअगर_err_code = DIF_ERR_GRD;
		scsi_status = SAM_STAT_CHECK_CONDITION;
		sense_key = ABORTED_COMMAND;
		asc = 0x10;
		ascq = 0x1;
	पूर्ण
out:
	चयन (cmd->state) अणु
	हाल QLA_TGT_STATE_NEED_DATA:
		/* handle_data will load DIF error code  */
		cmd->state = QLA_TGT_STATE_DATA_IN;
		vha->hw->tgt.tgt_ops->handle_data(cmd);
		अवरोध;
	शेष:
		spin_lock_irqsave(&cmd->cmd_lock, flags);
		अगर (cmd->पातed) अणु
			spin_unlock_irqrestore(&cmd->cmd_lock, flags);
			vha->hw->tgt.tgt_ops->मुक्त_cmd(cmd);
			अवरोध;
		पूर्ण
		spin_unlock_irqrestore(&cmd->cmd_lock, flags);

		qlt_send_resp_ctio(qpair, cmd, scsi_status, sense_key, asc,
		    ascq);
		/* assume scsi status माला_लो out on the wire.
		 * Will not रुको क्रम completion.
		 */
		vha->hw->tgt.tgt_ops->मुक्त_cmd(cmd);
		अवरोध;
	पूर्ण
पूर्ण

/* If hardware_lock held on entry, might drop it, then reaquire */
/* This function sends the appropriate CTIO to ISP 2xxx or 24xx */
अटल पूर्णांक __qlt_send_term_imm_notअगर(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *ntfy)
अणु
	काष्ठा nack_to_isp *nack;
	काष्ठा qla_hw_data *ha = vha->hw;
	request_t *pkt;
	पूर्णांक ret = 0;

	ql_dbg(ql_dbg_tgt_पंचांगr, vha, 0xe01c,
	    "Sending TERM ELS CTIO (ha=%p)\n", ha);

	pkt = (request_t *)qla2x00_alloc_iocbs(vha, शून्य);
	अगर (pkt == शून्य) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe080,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet\n", vha->vp_idx, __func__);
		वापस -ENOMEM;
	पूर्ण

	pkt->entry_type = NOTIFY_ACK_TYPE;
	pkt->entry_count = 1;
	pkt->handle = QLA_TGT_SKIP_HANDLE;

	nack = (काष्ठा nack_to_isp *)pkt;
	nack->ox_id = ntfy->ox_id;

	nack->u.isp24.nport_handle = ntfy->u.isp24.nport_handle;
	अगर (le16_to_cpu(ntfy->u.isp24.status) == IMM_NTFY_ELS) अणु
		nack->u.isp24.flags = ntfy->u.isp24.flags &
			cpu_to_le16(NOTIFY24XX_FLAGS_PUREX_IOCB);
	पूर्ण

	/* terminate */
	nack->u.isp24.flags |=
		__स्थिरant_cpu_to_le16(NOTIFY_ACK_FLAGS_TERMINATE);

	nack->u.isp24.srr_rx_id = ntfy->u.isp24.srr_rx_id;
	nack->u.isp24.status = ntfy->u.isp24.status;
	nack->u.isp24.status_subcode = ntfy->u.isp24.status_subcode;
	nack->u.isp24.fw_handle = ntfy->u.isp24.fw_handle;
	nack->u.isp24.exchange_address = ntfy->u.isp24.exchange_address;
	nack->u.isp24.srr_rel_offs = ntfy->u.isp24.srr_rel_offs;
	nack->u.isp24.srr_ui = ntfy->u.isp24.srr_ui;
	nack->u.isp24.vp_index = ntfy->u.isp24.vp_index;

	qla2x00_start_iocbs(vha, vha->req);
	वापस ret;
पूर्ण

अटल व्योम qlt_send_term_imm_notअगर(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *imm, पूर्णांक ha_locked)
अणु
	पूर्णांक rc;

	WARN_ON_ONCE(!ha_locked);
	rc = __qlt_send_term_imm_notअगर(vha, imm);
	pr_debug("rc = %d\n", rc);
पूर्ण

/*
 * If hardware_lock held on entry, might drop it, then reaquire
 * This function sends the appropriate CTIO to ISP 2xxx or 24xx
 */
अटल पूर्णांक __qlt_send_term_exchange(काष्ठा qla_qpair *qpair,
	काष्ठा qla_tgt_cmd *cmd,
	काष्ठा atio_from_isp *atio)
अणु
	काष्ठा scsi_qla_host *vha = qpair->vha;
	काष्ठा ctio7_to_24xx *ctio24;
	काष्ठा qla_hw_data *ha = vha->hw;
	request_t *pkt;
	पूर्णांक ret = 0;
	uपूर्णांक16_t temp;

	ql_dbg(ql_dbg_tgt, vha, 0xe009, "Sending TERM EXCH CTIO (ha=%p)\n", ha);

	अगर (cmd)
		vha = cmd->vha;

	pkt = (request_t *)qla2x00_alloc_iocbs_पढ़ोy(qpair, शून्य);
	अगर (pkt == शून्य) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe050,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet\n", vha->vp_idx, __func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (cmd != शून्य) अणु
		अगर (cmd->state < QLA_TGT_STATE_PROCESSED) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe051,
			    "qla_target(%d): Terminating cmd %p with "
			    "incorrect state %d\n", vha->vp_idx, cmd,
			    cmd->state);
		पूर्ण अन्यथा
			ret = 1;
	पूर्ण

	qpair->tgt_counters.num_term_xchg_sent++;
	pkt->entry_count = 1;
	pkt->handle = QLA_TGT_SKIP_HANDLE | CTIO_COMPLETION_HANDLE_MARK;

	ctio24 = (काष्ठा ctio7_to_24xx *)pkt;
	ctio24->entry_type = CTIO_TYPE7;
	ctio24->nport_handle = cpu_to_le16(CTIO7_NHANDLE_UNRECOGNIZED);
	ctio24->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	ctio24->vp_index = vha->vp_idx;
	ctio24->initiator_id = be_id_to_le(atio->u.isp24.fcp_hdr.s_id);
	ctio24->exchange_addr = atio->u.isp24.exchange_addr;
	temp = (atio->u.isp24.attr << 9) | CTIO7_FLAGS_STATUS_MODE_1 |
		CTIO7_FLAGS_TERMINATE;
	ctio24->u.status1.flags = cpu_to_le16(temp);
	temp = be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id);
	ctio24->u.status1.ox_id = cpu_to_le16(temp);

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);
	वापस ret;
पूर्ण

अटल व्योम qlt_send_term_exchange(काष्ठा qla_qpair *qpair,
	काष्ठा qla_tgt_cmd *cmd, काष्ठा atio_from_isp *atio, पूर्णांक ha_locked,
	पूर्णांक ul_पात)
अणु
	काष्ठा scsi_qla_host *vha;
	अचिन्हित दीर्घ flags = 0;
	पूर्णांक rc;

	/* why use dअगरferent vha? NPIV */
	अगर (cmd)
		vha = cmd->vha;
	अन्यथा
		vha = qpair->vha;

	अगर (ha_locked) अणु
		rc = __qlt_send_term_exchange(qpair, cmd, atio);
		अगर (rc == -ENOMEM)
			qlt_alloc_qfull_cmd(vha, atio, 0, 0);
		जाओ करोne;
	पूर्ण
	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	rc = __qlt_send_term_exchange(qpair, cmd, atio);
	अगर (rc == -ENOMEM)
		qlt_alloc_qfull_cmd(vha, atio, 0, 0);

करोne:
	अगर (cmd && !ul_पात && !cmd->पातed) अणु
		अगर (cmd->sg_mapped)
			qlt_unmap_sg(vha, cmd);
		vha->hw->tgt.tgt_ops->मुक्त_cmd(cmd);
	पूर्ण

	अगर (!ha_locked)
		spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	वापस;
पूर्ण

अटल व्योम qlt_init_term_exchange(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा list_head मुक्त_list;
	काष्ठा qla_tgt_cmd *cmd, *tcmd;

	vha->hw->tgt.leak_exchg_thresh_hold =
	    (vha->hw->cur_fw_xcb_count/100) * LEAK_EXCHG_THRESH_HOLD_PERCENT;

	cmd = tcmd = शून्य;
	अगर (!list_empty(&vha->hw->tgt.q_full_list)) अणु
		INIT_LIST_HEAD(&मुक्त_list);
		list_splice_init(&vha->hw->tgt.q_full_list, &मुक्त_list);

		list_क्रम_each_entry_safe(cmd, tcmd, &मुक्त_list, cmd_list) अणु
			list_del(&cmd->cmd_list);
			/* This cmd was never sent to TCM.  There is no need
			 * to schedule मुक्त or call मुक्त_cmd
			 */
			qlt_मुक्त_cmd(cmd);
			vha->hw->tgt.num_qfull_cmds_alloc--;
		पूर्ण
	पूर्ण
	vha->hw->tgt.num_qfull_cmds_dropped = 0;
पूर्ण

अटल व्योम qlt_chk_exch_leak_thresh_hold(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t total_leaked;

	total_leaked = vha->hw->tgt.num_qfull_cmds_dropped;

	अगर (vha->hw->tgt.leak_exchg_thresh_hold &&
	    (total_leaked > vha->hw->tgt.leak_exchg_thresh_hold)) अणु

		ql_dbg(ql_dbg_tgt, vha, 0xe079,
		    "Chip reset due to exchange starvation: %d/%d.\n",
		    total_leaked, vha->hw->cur_fw_xcb_count);

		अगर (IS_P3P_TYPE(vha->hw))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		अन्यथा
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
	पूर्ण

पूर्ण

पूर्णांक qlt_पात_cmd(काष्ठा qla_tgt_cmd *cmd)
अणु
	काष्ठा qla_tgt *tgt = cmd->tgt;
	काष्ठा scsi_qla_host *vha = tgt->vha;
	काष्ठा se_cmd *se_cmd = &cmd->se_cmd;
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf014,
	    "qla_target(%d): terminating exchange for aborted cmd=%p "
	    "(se_cmd=%p, tag=%llu)", vha->vp_idx, cmd, &cmd->se_cmd,
	    se_cmd->tag);

	spin_lock_irqsave(&cmd->cmd_lock, flags);
	अगर (cmd->पातed) अणु
		spin_unlock_irqrestore(&cmd->cmd_lock, flags);
		/*
		 * It's normal to see 2 calls in this path:
		 *  1) XFER Rdy completion + CMD_T_ABORT
		 *  2) TCM TMR - drain_state_list
		 */
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf016,
		    "multiple abort. %p transport_state %x, t_state %x, "
		    "se_cmd_flags %x\n", cmd, cmd->se_cmd.transport_state,
		    cmd->se_cmd.t_state, cmd->se_cmd.se_cmd_flags);
		वापस -EIO;
	पूर्ण
	cmd->पातed = 1;
	cmd->trc_flags |= TRC_ABORT;
	spin_unlock_irqrestore(&cmd->cmd_lock, flags);

	qlt_send_term_exchange(cmd->qpair, cmd, &cmd->atio, 0, 1);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(qlt_पात_cmd);

व्योम qlt_मुक्त_cmd(काष्ठा qla_tgt_cmd *cmd)
अणु
	काष्ठा fc_port *sess = cmd->sess;

	ql_dbg(ql_dbg_tgt, cmd->vha, 0xe074,
	    "%s: se_cmd[%p] ox_id %04x\n",
	    __func__, &cmd->se_cmd,
	    be16_to_cpu(cmd->atio.u.isp24.fcp_hdr.ox_id));

	BUG_ON(cmd->cmd_in_wq);

	अगर (cmd->sg_mapped)
		qlt_unmap_sg(cmd->vha, cmd);

	अगर (!cmd->q_full)
		qlt_decr_num_pend_cmds(cmd->vha);

	BUG_ON(cmd->sg_mapped);
	cmd->jअगरfies_at_मुक्त = get_jअगरfies_64();
	अगर (unlikely(cmd->मुक्त_sg))
		kमुक्त(cmd->sg);

	अगर (!sess || !sess->se_sess) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	cmd->jअगरfies_at_मुक्त = get_jअगरfies_64();
	cmd->vha->hw->tgt.tgt_ops->rel_cmd(cmd);
पूर्ण
EXPORT_SYMBOL(qlt_मुक्त_cmd);

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल पूर्णांक qlt_term_ctio_exchange(काष्ठा qla_qpair *qpair, व्योम *ctio,
	काष्ठा qla_tgt_cmd *cmd, uपूर्णांक32_t status)
अणु
	पूर्णांक term = 0;
	काष्ठा scsi_qla_host *vha = qpair->vha;

	अगर (cmd->se_cmd.prot_op)
		ql_dbg(ql_dbg_tgt_dअगर, vha, 0xe013,
		    "Term DIF cmd: lba[0x%llx|%lld] len[0x%x] "
		    "se_cmd=%p tag[%x] op %#x/%s",
		     cmd->lba, cmd->lba,
		     cmd->num_blks, &cmd->se_cmd,
		     cmd->atio.u.isp24.exchange_addr,
		     cmd->se_cmd.prot_op,
		     prot_op_str(cmd->se_cmd.prot_op));

	अगर (ctio != शून्य) अणु
		काष्ठा ctio7_from_24xx *c = (काष्ठा ctio7_from_24xx *)ctio;

		term = !(c->flags &
		    cpu_to_le16(OF_TERM_EXCH));
	पूर्ण अन्यथा
		term = 1;

	अगर (term)
		qlt_send_term_exchange(qpair, cmd, &cmd->atio, 1, 0);

	वापस term;
पूर्ण


/* ha->hardware_lock supposed to be held on entry */
अटल व्योम *qlt_ctio_to_cmd(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp, uपूर्णांक32_t handle, व्योम *ctio)
अणु
	व्योम *cmd = शून्य;
	काष्ठा req_que *req;
	पूर्णांक qid = GET_QID(handle);
	uपूर्णांक32_t h = handle & ~QLA_TGT_HANDLE_MASK;

	अगर (unlikely(h == QLA_TGT_SKIP_HANDLE))
		वापस शून्य;

	अगर (qid == rsp->req->id) अणु
		req = rsp->req;
	पूर्ण अन्यथा अगर (vha->hw->req_q_map[qid]) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0x1000a,
		    "qla_target(%d): CTIO completion with different QID %d handle %x\n",
		    vha->vp_idx, rsp->id, handle);
		req = vha->hw->req_q_map[qid];
	पूर्ण अन्यथा अणु
		वापस शून्य;
	पूर्ण

	h &= QLA_CMD_HANDLE_MASK;

	अगर (h != QLA_TGT_शून्य_HANDLE) अणु
		अगर (unlikely(h >= req->num_outstanding_cmds)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe052,
			    "qla_target(%d): Wrong handle %x received\n",
			    vha->vp_idx, handle);
			वापस शून्य;
		पूर्ण

		cmd = req->outstanding_cmds[h];
		अगर (unlikely(cmd == शून्य)) अणु
			ql_dbg(ql_dbg_async, vha, 0xe053,
			    "qla_target(%d): Suspicious: unable to find the command with handle %x req->id %d rsp->id %d\n",
				vha->vp_idx, handle, req->id, rsp->id);
			वापस शून्य;
		पूर्ण
		req->outstanding_cmds[h] = शून्य;
	पूर्ण अन्यथा अगर (ctio != शून्य) अणु
		/* We can't get loop ID from CTIO7 */
		ql_dbg(ql_dbg_tgt, vha, 0xe054,
		    "qla_target(%d): Wrong CTIO received: QLA24xx doesn't "
		    "support NULL handles\n", vha->vp_idx);
		वापस शून्य;
	पूर्ण

	वापस cmd;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_करो_ctio_completion(काष्ठा scsi_qla_host *vha,
    काष्ठा rsp_que *rsp, uपूर्णांक32_t handle, uपूर्णांक32_t status, व्योम *ctio)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा se_cmd *se_cmd;
	काष्ठा qla_tgt_cmd *cmd;
	काष्ठा qla_qpair *qpair = rsp->qpair;

	अगर (handle & CTIO_INTERMEDIATE_HANDLE_MARK) अणु
		/* That could happen only in हाल of an error/reset/पात */
		अगर (status != CTIO_SUCCESS) अणु
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf01d,
			    "Intermediate CTIO received"
			    " (status %x)\n", status);
		पूर्ण
		वापस;
	पूर्ण

	cmd = qlt_ctio_to_cmd(vha, rsp, handle, ctio);
	अगर (cmd == शून्य)
		वापस;

	se_cmd = &cmd->se_cmd;
	cmd->cmd_sent_to_fw = 0;

	qlt_unmap_sg(vha, cmd);

	अगर (unlikely(status != CTIO_SUCCESS)) अणु
		चयन (status & 0xFFFF) अणु
		हाल CTIO_INVALID_RX_ID:
			अगर (prपूर्णांकk_ratelimit())
				dev_info(&vha->hw->pdev->dev,
				    "qla_target(%d): CTIO with INVALID_RX_ID ATIO attr %x CTIO Flags %x|%x\n",
				    vha->vp_idx, cmd->atio.u.isp24.attr,
				    ((cmd->ctio_flags >> 9) & 0xf),
				    cmd->ctio_flags);

			अवरोध;
		हाल CTIO_LIP_RESET:
		हाल CTIO_TARGET_RESET:
		हाल CTIO_ABORTED:
			/* driver request पात via Terminate exchange */
		हाल CTIO_TIMEOUT:
			/* They are OK */
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf058,
			    "qla_target(%d): CTIO with "
			    "status %#x received, state %x, se_cmd %p, "
			    "(LIP_RESET=e, ABORTED=2, TARGET_RESET=17, "
			    "TIMEOUT=b, INVALID_RX_ID=8)\n", vha->vp_idx,
			    status, cmd->state, se_cmd);
			अवरोध;

		हाल CTIO_PORT_LOGGED_OUT:
		हाल CTIO_PORT_UNAVAILABLE:
		अणु
			पूर्णांक logged_out =
				(status & 0xFFFF) == CTIO_PORT_LOGGED_OUT;

			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf059,
			    "qla_target(%d): CTIO with %s status %x "
			    "received (state %x, se_cmd %p)\n", vha->vp_idx,
			    logged_out ? "PORT LOGGED OUT" : "PORT UNAVAILABLE",
			    status, cmd->state, se_cmd);

			अगर (logged_out && cmd->sess) अणु
				/*
				 * Session is alपढ़ोy logged out, but we need
				 * to notअगरy initiator, who's not aware of this
				 */
				cmd->sess->send_els_logo = 1;
				ql_dbg(ql_dbg_disc, vha, 0x20f8,
				    "%s %d %8phC post del sess\n",
				    __func__, __LINE__, cmd->sess->port_name);

				qlt_schedule_sess_क्रम_deletion(cmd->sess);
			पूर्ण
			अवरोध;
		पूर्ण
		हाल CTIO_DIF_ERROR: अणु
			काष्ठा ctio_crc_from_fw *crc =
				(काष्ठा ctio_crc_from_fw *)ctio;
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf073,
			    "qla_target(%d): CTIO with DIF_ERROR status %x "
			    "received (state %x, ulp_cmd %p) actual_dif[0x%llx] "
			    "expect_dif[0x%llx]\n",
			    vha->vp_idx, status, cmd->state, se_cmd,
			    *((u64 *)&crc->actual_dअगर[0]),
			    *((u64 *)&crc->expected_dअगर[0]));

			qlt_handle_dअगर_error(qpair, cmd, ctio);
			वापस;
		पूर्ण
		शेष:
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf05b,
			    "qla_target(%d): CTIO with error status 0x%x received (state %x, se_cmd %p\n",
			    vha->vp_idx, status, cmd->state, se_cmd);
			अवरोध;
		पूर्ण


		/* "cmd->aborted" means
		 * cmd is alपढ़ोy पातed/terminated, we करोn't
		 * need to terminate again.  The exchange is alपढ़ोy
		 * cleaned up/मुक्तd at FW level.  Just cleanup at driver
		 * level.
		 */
		अगर ((cmd->state != QLA_TGT_STATE_NEED_DATA) &&
		    (!cmd->पातed)) अणु
			cmd->trc_flags |= TRC_CTIO_ERR;
			अगर (qlt_term_ctio_exchange(qpair, ctio, cmd, status))
				वापस;
		पूर्ण
	पूर्ण

	अगर (cmd->state == QLA_TGT_STATE_PROCESSED) अणु
		cmd->trc_flags |= TRC_CTIO_DONE;
	पूर्ण अन्यथा अगर (cmd->state == QLA_TGT_STATE_NEED_DATA) अणु
		cmd->state = QLA_TGT_STATE_DATA_IN;

		अगर (status == CTIO_SUCCESS)
			cmd->ग_लिखो_data_transferred = 1;

		ha->tgt.tgt_ops->handle_data(cmd);
		वापस;
	पूर्ण अन्यथा अगर (cmd->पातed) अणु
		cmd->trc_flags |= TRC_CTIO_ABORTED;
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf01e,
		  "Aborted command %p (tag %lld) finished\n", cmd, se_cmd->tag);
	पूर्ण अन्यथा अणु
		cmd->trc_flags |= TRC_CTIO_STRANGE;
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf05c,
		    "qla_target(%d): A command in state (%d) should "
		    "not return a CTIO complete\n", vha->vp_idx, cmd->state);
	पूर्ण

	अगर (unlikely(status != CTIO_SUCCESS) &&
		!cmd->पातed) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf01f, "Finishing failed CTIO\n");
		dump_stack();
	पूर्ण

	ha->tgt.tgt_ops->मुक्त_cmd(cmd);
पूर्ण

अटल अंतरभूत पूर्णांक qlt_get_fcp_task_attr(काष्ठा scsi_qla_host *vha,
	uपूर्णांक8_t task_codes)
अणु
	पूर्णांक fcp_task_attr;

	चयन (task_codes) अणु
	हाल ATIO_SIMPLE_QUEUE:
		fcp_task_attr = TCM_SIMPLE_TAG;
		अवरोध;
	हाल ATIO_HEAD_OF_QUEUE:
		fcp_task_attr = TCM_HEAD_TAG;
		अवरोध;
	हाल ATIO_ORDERED_QUEUE:
		fcp_task_attr = TCM_ORDERED_TAG;
		अवरोध;
	हाल ATIO_ACA_QUEUE:
		fcp_task_attr = TCM_ACA_TAG;
		अवरोध;
	हाल ATIO_UNTAGGED:
		fcp_task_attr = TCM_SIMPLE_TAG;
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf05d,
		    "qla_target: unknown task code %x, use ORDERED instead\n",
		    task_codes);
		fcp_task_attr = TCM_ORDERED_TAG;
		अवरोध;
	पूर्ण

	वापस fcp_task_attr;
पूर्ण

/*
 * Process context क्रम I/O path पूर्णांकo tcm_qla2xxx code
 */
अटल व्योम __qlt_करो_work(काष्ठा qla_tgt_cmd *cmd)
अणु
	scsi_qla_host_t *vha = cmd->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess = cmd->sess;
	काष्ठा atio_from_isp *atio = &cmd->atio;
	अचिन्हित अक्षर *cdb;
	अचिन्हित दीर्घ flags;
	uपूर्णांक32_t data_length;
	पूर्णांक ret, fcp_task_attr, data_dir, bidi = 0;
	काष्ठा qla_qpair *qpair = cmd->qpair;

	cmd->cmd_in_wq = 0;
	cmd->trc_flags |= TRC_DO_WORK;

	अगर (cmd->पातed) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf082,
		    "cmd with tag %u is aborted\n",
		    cmd->atio.u.isp24.exchange_addr);
		जाओ out_term;
	पूर्ण

	spin_lock_init(&cmd->cmd_lock);
	cdb = &atio->u.isp24.fcp_cmnd.cdb[0];
	cmd->se_cmd.tag = le32_to_cpu(atio->u.isp24.exchange_addr);

	अगर (atio->u.isp24.fcp_cmnd.rddata &&
	    atio->u.isp24.fcp_cmnd.wrdata) अणु
		bidi = 1;
		data_dir = DMA_TO_DEVICE;
	पूर्ण अन्यथा अगर (atio->u.isp24.fcp_cmnd.rddata)
		data_dir = DMA_FROM_DEVICE;
	अन्यथा अगर (atio->u.isp24.fcp_cmnd.wrdata)
		data_dir = DMA_TO_DEVICE;
	अन्यथा
		data_dir = DMA_NONE;

	fcp_task_attr = qlt_get_fcp_task_attr(vha,
	    atio->u.isp24.fcp_cmnd.task_attr);
	data_length = get_datalen_क्रम_atio(atio);

	ret = ha->tgt.tgt_ops->handle_cmd(vha, cmd, cdb, data_length,
				          fcp_task_attr, data_dir, bidi);
	अगर (ret != 0)
		जाओ out_term;
	/*
	 * Drop extra session reference from qlt_handle_cmd_क्रम_atio().
	 */
	ha->tgt.tgt_ops->put_sess(sess);
	वापस;

out_term:
	ql_dbg(ql_dbg_io, vha, 0x3060, "Terminating work cmd %p", cmd);
	/*
	 * cmd has not sent to target yet, so pass शून्य as the second
	 * argument to qlt_send_term_exchange() and मुक्त the memory here.
	 */
	cmd->trc_flags |= TRC_DO_WORK_ERR;
	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	qlt_send_term_exchange(qpair, शून्य, &cmd->atio, 1, 0);

	qlt_decr_num_pend_cmds(vha);
	cmd->vha->hw->tgt.tgt_ops->rel_cmd(cmd);
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	ha->tgt.tgt_ops->put_sess(sess);
पूर्ण

अटल व्योम qlt_करो_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_tgt_cmd *cmd = container_of(work, काष्ठा qla_tgt_cmd, work);
	scsi_qla_host_t *vha = cmd->vha;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vha->cmd_list_lock, flags);
	list_del(&cmd->cmd_list);
	spin_unlock_irqrestore(&vha->cmd_list_lock, flags);

	__qlt_करो_work(cmd);
पूर्ण

व्योम qlt_clr_qp_table(काष्ठा scsi_qla_host *vha)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	व्योम *node;
	u64 key = 0;

	ql_log(ql_log_info, vha, 0x706c,
	    "User update Number of Active Qpairs %d\n",
	    ha->tgt.num_act_qpairs);

	spin_lock_irqsave(&ha->tgt.atio_lock, flags);

	btree_क्रम_each_safe64(&tgt->lun_qpair_map, key, node)
		btree_हटाओ64(&tgt->lun_qpair_map, key);

	ha->base_qpair->lun_cnt = 0;
	क्रम (key = 0; key < ha->max_qpairs; key++)
		अगर (ha->queue_pair_map[key])
			ha->queue_pair_map[key]->lun_cnt = 0;

	spin_unlock_irqrestore(&ha->tgt.atio_lock, flags);
पूर्ण

अटल व्योम qlt_assign_qpair(काष्ठा scsi_qla_host *vha,
	काष्ठा qla_tgt_cmd *cmd)
अणु
	काष्ठा qla_qpair *qpair, *qp;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा qla_qpair_hपूर्णांक *h;

	अगर (vha->flags.qpairs_available) अणु
		h = btree_lookup64(&tgt->lun_qpair_map, cmd->unpacked_lun);
		अगर (unlikely(!h)) अणु
			/* spपढ़ो lun to qpair ratio evently */
			पूर्णांक lcnt = 0, rc;
			काष्ठा scsi_qla_host *base_vha =
				pci_get_drvdata(vha->hw->pdev);

			qpair = vha->hw->base_qpair;
			अगर (qpair->lun_cnt == 0) अणु
				qpair->lun_cnt++;
				h = qla_qpair_to_hपूर्णांक(tgt, qpair);
				BUG_ON(!h);
				rc = btree_insert64(&tgt->lun_qpair_map,
					cmd->unpacked_lun, h, GFP_ATOMIC);
				अगर (rc) अणु
					qpair->lun_cnt--;
					ql_log(ql_log_info, vha, 0xd037,
					    "Unable to insert lun %llx into lun_qpair_map\n",
					    cmd->unpacked_lun);
				पूर्ण
				जाओ out;
			पूर्ण अन्यथा अणु
				lcnt = qpair->lun_cnt;
			पूर्ण

			h = शून्य;
			list_क्रम_each_entry(qp, &base_vha->qp_list,
			    qp_list_elem) अणु
				अगर (qp->lun_cnt == 0) अणु
					qp->lun_cnt++;
					h = qla_qpair_to_hपूर्णांक(tgt, qp);
					BUG_ON(!h);
					rc = btree_insert64(&tgt->lun_qpair_map,
					    cmd->unpacked_lun, h, GFP_ATOMIC);
					अगर (rc) अणु
						qp->lun_cnt--;
						ql_log(ql_log_info, vha, 0xd038,
							"Unable to insert lun %llx into lun_qpair_map\n",
							cmd->unpacked_lun);
					पूर्ण
					qpair = qp;
					जाओ out;
				पूर्ण अन्यथा अणु
					अगर (qp->lun_cnt < lcnt) अणु
						lcnt = qp->lun_cnt;
						qpair = qp;
						जारी;
					पूर्ण
				पूर्ण
			पूर्ण
			BUG_ON(!qpair);
			qpair->lun_cnt++;
			h = qla_qpair_to_hपूर्णांक(tgt, qpair);
			BUG_ON(!h);
			rc = btree_insert64(&tgt->lun_qpair_map,
				cmd->unpacked_lun, h, GFP_ATOMIC);
			अगर (rc) अणु
				qpair->lun_cnt--;
				ql_log(ql_log_info, vha, 0xd039,
				   "Unable to insert lun %llx into lun_qpair_map\n",
				   cmd->unpacked_lun);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		h = &tgt->qphपूर्णांकs[0];
	पूर्ण
out:
	cmd->qpair = h->qpair;
	cmd->se_cmd.cpuid = h->cpuid;
पूर्ण

अटल काष्ठा qla_tgt_cmd *qlt_get_tag(scsi_qla_host_t *vha,
				       काष्ठा fc_port *sess,
				       काष्ठा atio_from_isp *atio)
अणु
	काष्ठा qla_tgt_cmd *cmd;

	cmd = vha->hw->tgt.tgt_ops->get_cmd(sess);
	अगर (!cmd)
		वापस शून्य;

	cmd->cmd_type = TYPE_TGT_CMD;
	स_नकल(&cmd->atio, atio, माप(*atio));
	INIT_LIST_HEAD(&cmd->sess_cmd_list);
	cmd->state = QLA_TGT_STATE_NEW;
	cmd->tgt = vha->vha_tgt.qla_tgt;
	qlt_incr_num_pend_cmds(vha);
	cmd->vha = vha;
	cmd->sess = sess;
	cmd->loop_id = sess->loop_id;
	cmd->conf_compl_supported = sess->conf_compl_supported;

	cmd->trc_flags = 0;
	cmd->jअगरfies_at_alloc = get_jअगरfies_64();

	cmd->unpacked_lun = scsilun_to_पूर्णांक(
	    (काष्ठा scsi_lun *)&atio->u.isp24.fcp_cmnd.lun);
	qlt_assign_qpair(vha, cmd);
	cmd->reset_count = vha->hw->base_qpair->chip_reset;
	cmd->vp_idx = vha->vp_idx;

	वापस cmd;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक qlt_handle_cmd_क्रम_atio(काष्ठा scsi_qla_host *vha,
	काष्ठा atio_from_isp *atio)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा fc_port *sess;
	काष्ठा qla_tgt_cmd *cmd;
	अचिन्हित दीर्घ flags;
	port_id_t id;

	अगर (unlikely(tgt->tgt_stop)) अणु
		ql_dbg(ql_dbg_io, vha, 0x3061,
		    "New command while device %p is shutting down\n", tgt);
		वापस -ENODEV;
	पूर्ण

	id = be_to_port_id(atio->u.isp24.fcp_hdr.s_id);
	अगर (IS_SW_RESV_ADDR(id))
		वापस -EBUSY;

	sess = ha->tgt.tgt_ops->find_sess_by_s_id(vha, atio->u.isp24.fcp_hdr.s_id);
	अगर (unlikely(!sess))
		वापस -EFAULT;

	/* Another WWN used to have our s_id. Our PLOGI scheduled its
	 * session deletion, but it's still in sess_del_work wq */
	अगर (sess->deleted) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf002,
		    "New command while old session %p is being deleted\n",
		    sess);
		वापस -EFAULT;
	पूर्ण

	/*
	 * Do kref_get() beक्रमe वापसing + dropping qla_hw_data->hardware_lock.
	 */
	अगर (!kref_get_unless_zero(&sess->sess_kref)) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf004,
		    "%s: kref_get fail, %8phC oxid %x \n",
		    __func__, sess->port_name,
		     be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id));
		वापस -EFAULT;
	पूर्ण

	cmd = qlt_get_tag(vha, sess, atio);
	अगर (!cmd) अणु
		ql_dbg(ql_dbg_io, vha, 0x3062,
		    "qla_target(%d): Allocation of cmd failed\n", vha->vp_idx);
		ha->tgt.tgt_ops->put_sess(sess);
		वापस -EBUSY;
	पूर्ण

	cmd->cmd_in_wq = 1;
	cmd->trc_flags |= TRC_NEW_CMD;

	spin_lock_irqsave(&vha->cmd_list_lock, flags);
	list_add_tail(&cmd->cmd_list, &vha->qla_cmd_list);
	spin_unlock_irqrestore(&vha->cmd_list_lock, flags);

	INIT_WORK(&cmd->work, qlt_करो_work);
	अगर (vha->flags.qpairs_available) अणु
		queue_work_on(cmd->se_cmd.cpuid, qla_tgt_wq, &cmd->work);
	पूर्ण अन्यथा अगर (ha->msix_count) अणु
		अगर (cmd->atio.u.isp24.fcp_cmnd.rddata)
			queue_work_on(smp_processor_id(), qla_tgt_wq,
			    &cmd->work);
		अन्यथा
			queue_work_on(cmd->se_cmd.cpuid, qla_tgt_wq,
			    &cmd->work);
	पूर्ण अन्यथा अणु
		queue_work(qla_tgt_wq, &cmd->work);
	पूर्ण

	वापस 0;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक qlt_issue_task_mgmt(काष्ठा fc_port *sess, u64 lun,
	पूर्णांक fn, व्योम *iocb, पूर्णांक flags)
अणु
	काष्ठा scsi_qla_host *vha = sess->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt_mgmt_cmd *mcmd;
	काष्ठा atio_from_isp *a = (काष्ठा atio_from_isp *)iocb;
	काष्ठा qla_qpair_hपूर्णांक *h = &vha->vha_tgt.qla_tgt->qphपूर्णांकs[0];

	mcmd = mempool_alloc(qla_tgt_mgmt_cmd_mempool, GFP_ATOMIC);
	अगर (!mcmd) अणु
		ql_dbg(ql_dbg_tgt_पंचांगr, vha, 0x10009,
		    "qla_target(%d): Allocation of management "
		    "command failed, some commands and their data could "
		    "leak\n", vha->vp_idx);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(mcmd, 0, माप(*mcmd));
	mcmd->sess = sess;

	अगर (iocb) अणु
		स_नकल(&mcmd->orig_iocb.imm_ntfy, iocb,
		    माप(mcmd->orig_iocb.imm_ntfy));
	पूर्ण
	mcmd->पंचांगr_func = fn;
	mcmd->flags = flags;
	mcmd->reset_count = ha->base_qpair->chip_reset;
	mcmd->qpair = h->qpair;
	mcmd->vha = vha;
	mcmd->se_cmd.cpuid = h->cpuid;
	mcmd->unpacked_lun = lun;

	चयन (fn) अणु
	हाल QLA_TGT_LUN_RESET:
	हाल QLA_TGT_CLEAR_TS:
	हाल QLA_TGT_ABORT_TS:
		पात_cmds_क्रम_lun(vha, lun, a->u.isp24.fcp_hdr.s_id);
		fallthrough;
	हाल QLA_TGT_CLEAR_ACA:
		h = qlt_find_qphपूर्णांक(vha, mcmd->unpacked_lun);
		mcmd->qpair = h->qpair;
		mcmd->se_cmd.cpuid = h->cpuid;
		अवरोध;

	हाल QLA_TGT_TARGET_RESET:
	हाल QLA_TGT_NEXUS_LOSS_SESS:
	हाल QLA_TGT_NEXUS_LOSS:
	हाल QLA_TGT_ABORT_ALL:
	शेष:
		/* no-op */
		अवरोध;
	पूर्ण

	INIT_WORK(&mcmd->work, qlt_करो_पंचांगr_work);
	queue_work_on(mcmd->se_cmd.cpuid, qla_tgt_wq,
	    &mcmd->work);

	वापस 0;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक qlt_handle_task_mgmt(काष्ठा scsi_qla_host *vha, व्योम *iocb)
अणु
	काष्ठा atio_from_isp *a = (काष्ठा atio_from_isp *)iocb;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess;
	u64 unpacked_lun;
	पूर्णांक fn;
	अचिन्हित दीर्घ flags;

	fn = a->u.isp24.fcp_cmnd.task_mgmt_flags;

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	sess = ha->tgt.tgt_ops->find_sess_by_s_id(vha,
	    a->u.isp24.fcp_hdr.s_id);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	unpacked_lun =
	    scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&a->u.isp24.fcp_cmnd.lun);

	अगर (sess == शून्य || sess->deleted)
		वापस -EFAULT;

	वापस qlt_issue_task_mgmt(sess, unpacked_lun, fn, iocb, 0);
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक __qlt_पात_task(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *iocb, काष्ठा fc_port *sess)
अणु
	काष्ठा atio_from_isp *a = (काष्ठा atio_from_isp *)iocb;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt_mgmt_cmd *mcmd;
	u64 unpacked_lun;
	पूर्णांक rc;

	mcmd = mempool_alloc(qla_tgt_mgmt_cmd_mempool, GFP_ATOMIC);
	अगर (mcmd == शून्य) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf05f,
		    "qla_target(%d): %s: Allocation of ABORT cmd failed\n",
		    vha->vp_idx, __func__);
		वापस -ENOMEM;
	पूर्ण
	स_रखो(mcmd, 0, माप(*mcmd));

	mcmd->sess = sess;
	स_नकल(&mcmd->orig_iocb.imm_ntfy, iocb,
	    माप(mcmd->orig_iocb.imm_ntfy));

	unpacked_lun =
	    scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&a->u.isp24.fcp_cmnd.lun);
	mcmd->reset_count = ha->base_qpair->chip_reset;
	mcmd->पंचांगr_func = QLA_TGT_2G_ABORT_TASK;
	mcmd->qpair = ha->base_qpair;

	rc = ha->tgt.tgt_ops->handle_पंचांगr(mcmd, unpacked_lun, mcmd->पंचांगr_func,
	    le16_to_cpu(iocb->u.isp2x.seq_id));
	अगर (rc != 0) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf060,
		    "qla_target(%d): tgt_ops->handle_tmr() failed: %d\n",
		    vha->vp_idx, rc);
		mempool_मुक्त(mcmd, qla_tgt_mgmt_cmd_mempool);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
अटल पूर्णांक qlt_पात_task(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *iocb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess;
	पूर्णांक loop_id;
	अचिन्हित दीर्घ flags;

	loop_id = GET_TARGET_ID(ha, (काष्ठा atio_from_isp *)iocb);

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	sess = ha->tgt.tgt_ops->find_sess_by_loop_id(vha, loop_id);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	अगर (sess == शून्य) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf025,
		    "qla_target(%d): task abort for unexisting "
		    "session\n", vha->vp_idx);
		वापस qlt_sched_sess_work(vha->vha_tgt.qla_tgt,
		    QLA_TGT_SESS_WORK_ABORT, iocb, माप(*iocb));
	पूर्ण

	वापस __qlt_पात_task(vha, iocb, sess);
पूर्ण

व्योम qlt_logo_completion_handler(fc_port_t *fcport, पूर्णांक rc)
अणु
	अगर (rc != MBS_COMMAND_COMPLETE) अणु
		ql_dbg(ql_dbg_tgt_mgt, fcport->vha, 0xf093,
			"%s: se_sess %p / sess %p from"
			" port %8phC loop_id %#04x s_id %02x:%02x:%02x"
			" LOGO failed: %#x\n",
			__func__,
			fcport->se_sess,
			fcport,
			fcport->port_name, fcport->loop_id,
			fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
			fcport->d_id.b.al_pa, rc);
	पूर्ण

	fcport->logout_completed = 1;
पूर्ण

/*
* ha->hardware_lock supposed to be held on entry (to protect tgt->sess_list)
*
* Schedules sessions with matching port_id/loop_id but dअगरferent wwn क्रम
* deletion. Returns existing session with matching wwn अगर present.
* Null otherwise.
*/
काष्ठा fc_port *
qlt_find_sess_invalidate_other(scsi_qla_host_t *vha, uपूर्णांक64_t wwn,
    port_id_t port_id, uपूर्णांक16_t loop_id, काष्ठा fc_port **conflict_sess)
अणु
	काष्ठा fc_port *sess = शून्य, *other_sess;
	uपूर्णांक64_t other_wwn;

	*conflict_sess = शून्य;

	list_क्रम_each_entry(other_sess, &vha->vp_fcports, list) अणु

		other_wwn = wwn_to_u64(other_sess->port_name);

		अगर (wwn == other_wwn) अणु
			WARN_ON(sess);
			sess = other_sess;
			जारी;
		पूर्ण

		/* find other sess with nport_id collision */
		अगर (port_id.b24 == other_sess->d_id.b24) अणु
			अगर (loop_id != other_sess->loop_id) अणु
				ql_dbg(ql_dbg_disc, vha, 0x1000c,
				    "Invalidating sess %p loop_id %d wwn %llx.\n",
				    other_sess, other_sess->loop_id, other_wwn);

				/*
				 * logout_on_delete is set by शेष, but another
				 * session that has the same s_id/loop_id combo
				 * might have cleared it when requested this session
				 * deletion, so करोn't touch it
				 */
				qlt_schedule_sess_क्रम_deletion(other_sess);
			पूर्ण अन्यथा अणु
				/*
				 * Another wwn used to have our s_id/loop_id
				 * समाप्त the session, but करोn't मुक्त the loop_id
				 */
				ql_dbg(ql_dbg_disc, vha, 0xf01b,
				    "Invalidating sess %p loop_id %d wwn %llx.\n",
				    other_sess, other_sess->loop_id, other_wwn);

				other_sess->keep_nport_handle = 1;
				अगर (other_sess->disc_state != DSC_DELETED)
					*conflict_sess = other_sess;
				qlt_schedule_sess_क्रम_deletion(other_sess);
			पूर्ण
			जारी;
		पूर्ण

		/* find other sess with nport handle collision */
		अगर ((loop_id == other_sess->loop_id) &&
			(loop_id != FC_NO_LOOP_ID)) अणु
			ql_dbg(ql_dbg_disc, vha, 0x1000d,
			       "Invalidating sess %p loop_id %d wwn %llx.\n",
			       other_sess, other_sess->loop_id, other_wwn);

			/* Same loop_id but dअगरferent s_id
			 * Ok to समाप्त and logout */
			qlt_schedule_sess_क्रम_deletion(other_sess);
		पूर्ण
	पूर्ण

	वापस sess;
पूर्ण

/* Abort any commands क्रम this s_id रुकोing on qla_tgt_wq workqueue */
अटल पूर्णांक पात_cmds_क्रम_s_id(काष्ठा scsi_qla_host *vha, port_id_t *s_id)
अणु
	काष्ठा qla_tgt_sess_op *op;
	काष्ठा qla_tgt_cmd *cmd;
	uपूर्णांक32_t key;
	पूर्णांक count = 0;
	अचिन्हित दीर्घ flags;

	key = (((u32)s_id->b.करोमुख्य << 16) |
	       ((u32)s_id->b.area   <<  8) |
	       ((u32)s_id->b.al_pa));

	spin_lock_irqsave(&vha->cmd_list_lock, flags);
	list_क्रम_each_entry(op, &vha->qla_sess_op_cmd_list, cmd_list) अणु
		uपूर्णांक32_t op_key = sid_to_key(op->atio.u.isp24.fcp_hdr.s_id);

		अगर (op_key == key) अणु
			op->पातed = true;
			count++;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(op, &vha->unknown_atio_list, cmd_list) अणु
		uपूर्णांक32_t op_key = sid_to_key(op->atio.u.isp24.fcp_hdr.s_id);

		अगर (op_key == key) अणु
			op->पातed = true;
			count++;
		पूर्ण
	पूर्ण

	list_क्रम_each_entry(cmd, &vha->qla_cmd_list, cmd_list) अणु
		uपूर्णांक32_t cmd_key = sid_to_key(cmd->atio.u.isp24.fcp_hdr.s_id);

		अगर (cmd_key == key) अणु
			cmd->पातed = 1;
			count++;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&vha->cmd_list_lock, flags);

	वापस count;
पूर्ण

अटल पूर्णांक qlt_handle_login(काष्ठा scsi_qla_host *vha,
    काष्ठा imm_ntfy_from_isp *iocb)
अणु
	काष्ठा fc_port *sess = शून्य, *conflict_sess = शून्य;
	uपूर्णांक64_t wwn;
	port_id_t port_id;
	uपूर्णांक16_t loop_id, wd3_lo;
	पूर्णांक res = 0;
	काष्ठा qlt_plogi_ack_t *pla;
	अचिन्हित दीर्घ flags;

	lockdep_निश्चित_held(&vha->hw->hardware_lock);

	wwn = wwn_to_u64(iocb->u.isp24.port_name);

	port_id.b.करोमुख्य = iocb->u.isp24.port_id[2];
	port_id.b.area   = iocb->u.isp24.port_id[1];
	port_id.b.al_pa  = iocb->u.isp24.port_id[0];
	port_id.b.rsvd_1 = 0;

	loop_id = le16_to_cpu(iocb->u.isp24.nport_handle);

	/* Mark all stale commands sitting in qla_tgt_wq क्रम deletion */
	पात_cmds_क्रम_s_id(vha, &port_id);

	अगर (wwn) अणु
		spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
		sess = qlt_find_sess_invalidate_other(vha, wwn,
		    port_id, loop_id, &conflict_sess);
		spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0xffff,
		    "%s %d Term INOT due to WWN=0 lid=%d, NportID %06X ",
		    __func__, __LINE__, loop_id, port_id.b24);
		qlt_send_term_imm_notअगर(vha, iocb, 1);
		जाओ out;
	पूर्ण

	अगर (IS_SW_RESV_ADDR(port_id)) अणु
		res = 1;
		जाओ out;
	पूर्ण

	pla = qlt_plogi_ack_find_add(vha, &port_id, iocb);
	अगर (!pla) अणु
		ql_dbg(ql_dbg_disc + ql_dbg_verbose, vha, 0xffff,
		    "%s %d %8phC Term INOT due to mem alloc fail",
		    __func__, __LINE__,
		    iocb->u.isp24.port_name);
		qlt_send_term_imm_notअगर(vha, iocb, 1);
		जाओ out;
	पूर्ण

	अगर (conflict_sess) अणु
		conflict_sess->login_gen++;
		qlt_plogi_ack_link(vha, pla, conflict_sess,
		    QLT_PLOGI_LINK_CONFLICT);
	पूर्ण

	अगर (!sess) अणु
		pla->ref_count++;
		ql_dbg(ql_dbg_disc, vha, 0xffff,
		    "%s %d %8phC post new sess\n",
		    __func__, __LINE__, iocb->u.isp24.port_name);
		अगर (iocb->u.isp24.status_subcode == ELS_PLOGI)
			qla24xx_post_newsess_work(vha, &port_id,
			    iocb->u.isp24.port_name,
			    iocb->u.isp24.u.plogi.node_name,
			    pla, 0);
		अन्यथा
			qla24xx_post_newsess_work(vha, &port_id,
			    iocb->u.isp24.port_name, शून्य,
			    pla, 0);

		जाओ out;
	पूर्ण

	अगर (sess->disc_state == DSC_UPD_FCPORT) अणु
		u16 sec;

		/*
		 * Remote port registration is still going on from
		 * previous login. Allow it to finish beक्रमe we
		 * accept the new login.
		 */
		sess->next_disc_state = DSC_DELETE_PEND;
		sec = jअगरfies_to_msecs(jअगरfies -
		    sess->jअगरfies_at_registration) / 1000;
		अगर (sess->sec_since_registration < sec && sec &&
		    !(sec % 5)) अणु
			sess->sec_since_registration = sec;
			ql_dbg(ql_dbg_disc, vha, 0xffff,
			    "%s %8phC - Slow Rport registration (%d Sec)\n",
			    __func__, sess->port_name, sec);
		पूर्ण

		अगर (!conflict_sess) अणु
			list_del(&pla->list);
			kmem_cache_मुक्त(qla_tgt_plogi_cachep, pla);
		पूर्ण

		qlt_send_term_imm_notअगर(vha, iocb, 1);
		जाओ out;
	पूर्ण

	qlt_plogi_ack_link(vha, pla, sess, QLT_PLOGI_LINK_SAME_WWN);
	sess->d_id = port_id;
	sess->login_gen++;

	अगर (iocb->u.isp24.status_subcode == ELS_PRLI) अणु
		sess->fw_login_state = DSC_LS_PRLI_PEND;
		sess->local = 0;
		sess->loop_id = loop_id;
		sess->d_id = port_id;
		sess->fw_login_state = DSC_LS_PRLI_PEND;
		wd3_lo = le16_to_cpu(iocb->u.isp24.u.prli.wd3_lo);

		अगर (wd3_lo & BIT_7)
			sess->conf_compl_supported = 1;

		अगर ((wd3_lo & BIT_4) == 0)
			sess->port_type = FCT_INITIATOR;
		अन्यथा
			sess->port_type = FCT_TARGET;

	पूर्ण अन्यथा
		sess->fw_login_state = DSC_LS_PLOGI_PEND;


	ql_dbg(ql_dbg_disc, vha, 0x20f9,
	    "%s %d %8phC  DS %d\n",
	    __func__, __LINE__, sess->port_name, sess->disc_state);

	चयन (sess->disc_state) अणु
	हाल DSC_DELETED:
	हाल DSC_LOGIN_PEND:
		qlt_plogi_ack_unref(vha, pla);
		अवरोध;

	शेष:
		/*
		 * Under normal circumstances we want to release nport handle
		 * during LOGO process to aव्योम nport handle leaks inside FW.
		 * The exception is when LOGO is करोne जबतक another PLOGI with
		 * the same nport handle is रुकोing as might be the हाल here.
		 * Note: there is always a possibily of a race where session
		 * deletion has alपढ़ोy started क्रम other reasons (e.g. ACL
		 * removal) and now PLOGI arrives:
		 * 1. अगर PLOGI arrived in FW after nport handle has been मुक्तd,
		 *    FW must have asचिन्हित this PLOGI a new/same handle and we
		 *    can proceed ACK'ing it as usual when session deletion
		 *    completes.
		 * 2. अगर PLOGI arrived in FW beक्रमe LOGO with LCF_FREE_NPORT
		 *    bit reached it, the handle has now been released. We'll
		 *    get an error when we ACK this PLOGI. Nothing will be sent
		 *    back to initiator. Initiator should eventually retry
		 *    PLOGI and situation will correct itself.
		 */
		sess->keep_nport_handle = ((sess->loop_id == loop_id) &&
		    (sess->d_id.b24 == port_id.b24));

		ql_dbg(ql_dbg_disc, vha, 0x20f9,
		    "%s %d %8phC post del sess\n",
		    __func__, __LINE__, sess->port_name);


		qlt_schedule_sess_क्रम_deletion(sess);
		अवरोध;
	पूर्ण
out:
	वापस res;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल पूर्णांक qlt_24xx_handle_els(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *iocb)
अणु
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess = शून्य, *conflict_sess = शून्य;
	uपूर्णांक64_t wwn;
	port_id_t port_id;
	uपूर्णांक16_t loop_id;
	uपूर्णांक16_t wd3_lo;
	पूर्णांक res = 0;
	अचिन्हित दीर्घ flags;

	lockdep_निश्चित_held(&ha->hardware_lock);

	wwn = wwn_to_u64(iocb->u.isp24.port_name);

	port_id.b.करोमुख्य = iocb->u.isp24.port_id[2];
	port_id.b.area   = iocb->u.isp24.port_id[1];
	port_id.b.al_pa  = iocb->u.isp24.port_id[0];
	port_id.b.rsvd_1 = 0;

	loop_id = le16_to_cpu(iocb->u.isp24.nport_handle);

	ql_dbg(ql_dbg_disc, vha, 0xf026,
	    "qla_target(%d): Port ID: %02x:%02x:%02x ELS opcode: 0x%02x lid %d %8phC\n",
	    vha->vp_idx, iocb->u.isp24.port_id[2],
		iocb->u.isp24.port_id[1], iocb->u.isp24.port_id[0],
		   iocb->u.isp24.status_subcode, loop_id,
		iocb->u.isp24.port_name);

	/* res = 1 means ack at the end of thपढ़ो
	 * res = 0 means ack async/later.
	 */
	चयन (iocb->u.isp24.status_subcode) अणु
	हाल ELS_PLOGI:
		res = qlt_handle_login(vha, iocb);
		अवरोध;

	हाल ELS_PRLI:
		अगर (N2N_TOPO(ha)) अणु
			sess = qla2x00_find_fcport_by_wwpn(vha,
			    iocb->u.isp24.port_name, 1);

			अगर (sess && sess->plogi_link[QLT_PLOGI_LINK_SAME_WWN]) अणु
				ql_dbg(ql_dbg_disc, vha, 0xffff,
				    "%s %d %8phC Term PRLI due to PLOGI ACK not completed\n",
				    __func__, __LINE__,
				    iocb->u.isp24.port_name);
				qlt_send_term_imm_notअगर(vha, iocb, 1);
				अवरोध;
			पूर्ण

			res = qlt_handle_login(vha, iocb);
			अवरोध;
		पूर्ण

		अगर (IS_SW_RESV_ADDR(port_id)) अणु
			res = 1;
			अवरोध;
		पूर्ण

		wd3_lo = le16_to_cpu(iocb->u.isp24.u.prli.wd3_lo);

		अगर (wwn) अणु
			spin_lock_irqsave(&tgt->ha->tgt.sess_lock, flags);
			sess = qlt_find_sess_invalidate_other(vha, wwn, port_id,
				loop_id, &conflict_sess);
			spin_unlock_irqrestore(&tgt->ha->tgt.sess_lock, flags);
		पूर्ण

		अगर (conflict_sess) अणु
			चयन (conflict_sess->disc_state) अणु
			हाल DSC_DELETED:
			हाल DSC_DELETE_PEND:
				अवरोध;
			शेष:
				ql_dbg(ql_dbg_tgt_mgt, vha, 0xf09b,
				    "PRLI with conflicting sess %p port %8phC\n",
				    conflict_sess, conflict_sess->port_name);
				conflict_sess->fw_login_state =
				    DSC_LS_PORT_UNAVAIL;
				qlt_send_term_imm_notअगर(vha, iocb, 1);
				res = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (sess != शून्य) अणु
			bool delete = false;
			पूर्णांक sec;

			spin_lock_irqsave(&tgt->ha->tgt.sess_lock, flags);
			चयन (sess->fw_login_state) अणु
			हाल DSC_LS_PLOGI_PEND:
			हाल DSC_LS_PLOGI_COMP:
			हाल DSC_LS_PRLI_COMP:
				अवरोध;
			शेष:
				delete = true;
				अवरोध;
			पूर्ण

			चयन (sess->disc_state) अणु
			हाल DSC_UPD_FCPORT:
				spin_unlock_irqrestore(&tgt->ha->tgt.sess_lock,
				    flags);

				sec = jअगरfies_to_msecs(jअगरfies -
				    sess->jअगरfies_at_registration)/1000;
				अगर (sess->sec_since_registration < sec && sec &&
				    !(sec % 5)) अणु
					sess->sec_since_registration = sec;
					ql_dbg(ql_dbg_disc, sess->vha, 0xffff,
					    "%s %8phC : Slow Rport registration(%d Sec)\n",
					    __func__, sess->port_name, sec);
				पूर्ण
				qlt_send_term_imm_notअगर(vha, iocb, 1);
				वापस 0;

			हाल DSC_LOGIN_PEND:
			हाल DSC_GPDB:
			हाल DSC_LOGIN_COMPLETE:
			हाल DSC_ADISC:
				delete = false;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण

			अगर (delete) अणु
				spin_unlock_irqrestore(&tgt->ha->tgt.sess_lock,
				    flags);
				/*
				 * Impatient initiator sent PRLI beक्रमe last
				 * PLOGI could finish. Will क्रमce him to re-try,
				 * जबतक last one finishes.
				 */
				ql_log(ql_log_warn, sess->vha, 0xf095,
				    "sess %p PRLI received, before plogi ack.\n",
				    sess);
				qlt_send_term_imm_notअगर(vha, iocb, 1);
				res = 0;
				अवरोध;
			पूर्ण

			/*
			 * This shouldn't happen under normal circumstances,
			 * since we have deleted the old session during PLOGI
			 */
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf096,
			    "PRLI (loop_id %#04x) for existing sess %p (loop_id %#04x)\n",
			    sess->loop_id, sess, iocb->u.isp24.nport_handle);

			sess->local = 0;
			sess->loop_id = loop_id;
			sess->d_id = port_id;
			sess->fw_login_state = DSC_LS_PRLI_PEND;

			अगर (wd3_lo & BIT_7)
				sess->conf_compl_supported = 1;

			अगर ((wd3_lo & BIT_4) == 0)
				sess->port_type = FCT_INITIATOR;
			अन्यथा
				sess->port_type = FCT_TARGET;

			spin_unlock_irqrestore(&tgt->ha->tgt.sess_lock, flags);
		पूर्ण
		res = 1; /* send notअगरy ack */

		/* Make session global (not used in fabric mode) */
		अगर (ha->current_topology != ISP_CFG_F) अणु
			अगर (sess) अणु
				ql_dbg(ql_dbg_disc, vha, 0x20fa,
				    "%s %d %8phC post nack\n",
				    __func__, __LINE__, sess->port_name);
				qla24xx_post_nack_work(vha, sess, iocb,
					SRB_NACK_PRLI);
				res = 0;
			पूर्ण अन्यथा अणु
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sess) अणु
				ql_dbg(ql_dbg_disc, vha, 0x20fb,
				    "%s %d %8phC post nack\n",
				    __func__, __LINE__, sess->port_name);
				qla24xx_post_nack_work(vha, sess, iocb,
					SRB_NACK_PRLI);
				res = 0;
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ELS_TPRLO:
		अगर (le16_to_cpu(iocb->u.isp24.flags) &
			NOTIFY24XX_FLAGS_GLOBAL_TPRLO) अणु
			loop_id = 0xFFFF;
			qlt_reset(vha, iocb, QLA_TGT_NEXUS_LOSS);
			res = 1;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल ELS_LOGO:
	हाल ELS_PRLO:
		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
		sess = qla2x00_find_fcport_by_loopid(vha, loop_id);
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

		अगर (sess) अणु
			sess->login_gen++;
			sess->fw_login_state = DSC_LS_LOGO_PEND;
			sess->logo_ack_needed = 1;
			स_नकल(sess->iocb, iocb, IOCB_SIZE);
		पूर्ण

		res = qlt_reset(vha, iocb, QLA_TGT_NEXUS_LOSS_SESS);

		ql_dbg(ql_dbg_disc, vha, 0x20fc,
		    "%s: logo %llx res %d sess %p ",
		    __func__, wwn, res, sess);
		अगर (res == 0) अणु
			/*
			 * cmd went upper layer, look क्रम qlt_xmit_पंचांग_rsp()
			 * क्रम LOGO_ACK & sess delete
			 */
			BUG_ON(!sess);
			res = 0;
		पूर्ण अन्यथा अणु
			/* cmd did not go to upper layer. */
			अगर (sess) अणु
				qlt_schedule_sess_क्रम_deletion(sess);
				res = 0;
			पूर्ण
			/* अन्यथा logo will be ack */
		पूर्ण
		अवरोध;
	हाल ELS_PDISC:
	हाल ELS_ADISC:
	अणु
		काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;

		अगर (tgt->link_reinit_iocb_pending) अणु
			qlt_send_notअगरy_ack(ha->base_qpair,
			    &tgt->link_reinit_iocb, 0, 0, 0, 0, 0, 0);
			tgt->link_reinit_iocb_pending = 0;
		पूर्ण

		sess = qla2x00_find_fcport_by_wwpn(vha,
		    iocb->u.isp24.port_name, 1);
		अगर (sess) अणु
			ql_dbg(ql_dbg_disc, vha, 0x20fd,
				"sess %p lid %d|%d DS %d LS %d\n",
				sess, sess->loop_id, loop_id,
				sess->disc_state, sess->fw_login_state);
		पूर्ण

		res = 1; /* send notअगरy ack */
		अवरोध;
	पूर्ण

	हाल ELS_FLOGI:	/* should never happen */
	शेष:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf061,
		    "qla_target(%d): Unsupported ELS command %x "
		    "received\n", vha->vp_idx, iocb->u.isp24.status_subcode);
		res = qlt_reset(vha, iocb, QLA_TGT_NEXUS_LOSS_SESS);
		अवरोध;
	पूर्ण

	ql_dbg(ql_dbg_disc, vha, 0xf026,
	    "qla_target(%d): Exit ELS opcode: 0x%02x res %d\n",
	    vha->vp_idx, iocb->u.isp24.status_subcode, res);

	वापस res;
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
अटल व्योम qlt_handle_imm_notअगरy(काष्ठा scsi_qla_host *vha,
	काष्ठा imm_ntfy_from_isp *iocb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t add_flags = 0;
	पूर्णांक send_notअगरy_ack = 1;
	uपूर्णांक16_t status;

	lockdep_निश्चित_held(&ha->hardware_lock);

	status = le16_to_cpu(iocb->u.isp2x.status);
	चयन (status) अणु
	हाल IMM_NTFY_LIP_RESET:
	अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf032,
		    "qla_target(%d): LIP reset (loop %#x), subcode %x\n",
		    vha->vp_idx, le16_to_cpu(iocb->u.isp24.nport_handle),
		    iocb->u.isp24.status_subcode);

		अगर (qlt_reset(vha, iocb, QLA_TGT_ABORT_ALL) == 0)
			send_notअगरy_ack = 0;
		अवरोध;
	पूर्ण

	हाल IMM_NTFY_LIP_LINK_REINIT:
	अणु
		काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;

		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf033,
		    "qla_target(%d): LINK REINIT (loop %#x, "
		    "subcode %x)\n", vha->vp_idx,
		    le16_to_cpu(iocb->u.isp24.nport_handle),
		    iocb->u.isp24.status_subcode);
		अगर (tgt->link_reinit_iocb_pending) अणु
			qlt_send_notअगरy_ack(ha->base_qpair,
			    &tgt->link_reinit_iocb, 0, 0, 0, 0, 0, 0);
		पूर्ण
		स_नकल(&tgt->link_reinit_iocb, iocb, माप(*iocb));
		tgt->link_reinit_iocb_pending = 1;
		/*
		 * QLogic requires to रुको after LINK REINIT क्रम possible
		 * PDISC or ADISC ELS commands
		 */
		send_notअगरy_ack = 0;
		अवरोध;
	पूर्ण

	हाल IMM_NTFY_PORT_LOGOUT:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf034,
		    "qla_target(%d): Port logout (loop "
		    "%#x, subcode %x)\n", vha->vp_idx,
		    le16_to_cpu(iocb->u.isp24.nport_handle),
		    iocb->u.isp24.status_subcode);

		अगर (qlt_reset(vha, iocb, QLA_TGT_NEXUS_LOSS_SESS) == 0)
			send_notअगरy_ack = 0;
		/* The sessions will be cleared in the callback, अगर needed */
		अवरोध;

	हाल IMM_NTFY_GLBL_TPRLO:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf035,
		    "qla_target(%d): Global TPRLO (%x)\n", vha->vp_idx, status);
		अगर (qlt_reset(vha, iocb, QLA_TGT_NEXUS_LOSS) == 0)
			send_notअगरy_ack = 0;
		/* The sessions will be cleared in the callback, अगर needed */
		अवरोध;

	हाल IMM_NTFY_PORT_CONFIG:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf036,
		    "qla_target(%d): Port config changed (%x)\n", vha->vp_idx,
		    status);
		अगर (qlt_reset(vha, iocb, QLA_TGT_ABORT_ALL) == 0)
			send_notअगरy_ack = 0;
		/* The sessions will be cleared in the callback, अगर needed */
		अवरोध;

	हाल IMM_NTFY_GLBL_LOGO:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf06a,
		    "qla_target(%d): Link failure detected\n",
		    vha->vp_idx);
		/* I_T nexus loss */
		अगर (qlt_reset(vha, iocb, QLA_TGT_NEXUS_LOSS) == 0)
			send_notअगरy_ack = 0;
		अवरोध;

	हाल IMM_NTFY_IOCB_OVERFLOW:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf06b,
		    "qla_target(%d): Cannot provide requested "
		    "capability (IOCB overflowed the immediate notify "
		    "resource count)\n", vha->vp_idx);
		अवरोध;

	हाल IMM_NTFY_ABORT_TASK:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf037,
		    "qla_target(%d): Abort Task (S %08x I %#x -> "
		    "L %#x)\n", vha->vp_idx,
		    le16_to_cpu(iocb->u.isp2x.seq_id),
		    GET_TARGET_ID(ha, (काष्ठा atio_from_isp *)iocb),
		    le16_to_cpu(iocb->u.isp2x.lun));
		अगर (qlt_पात_task(vha, iocb) == 0)
			send_notअगरy_ack = 0;
		अवरोध;

	हाल IMM_NTFY_RESOURCE:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf06c,
		    "qla_target(%d): Out of resources, host %ld\n",
		    vha->vp_idx, vha->host_no);
		अवरोध;

	हाल IMM_NTFY_MSG_RX:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf038,
		    "qla_target(%d): Immediate notify task %x\n",
		    vha->vp_idx, iocb->u.isp2x.task_flags);
		अवरोध;

	हाल IMM_NTFY_ELS:
		अगर (qlt_24xx_handle_els(vha, iocb) == 0)
			send_notअगरy_ack = 0;
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf06d,
		    "qla_target(%d): Received unknown immediate "
		    "notify status %x\n", vha->vp_idx, status);
		अवरोध;
	पूर्ण

	अगर (send_notअगरy_ack)
		qlt_send_notअगरy_ack(ha->base_qpair, iocb, add_flags, 0, 0, 0,
		    0, 0);
पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 * This function sends busy to ISP 2xxx or 24xx.
 */
अटल पूर्णांक __qlt_send_busy(काष्ठा qla_qpair *qpair,
	काष्ठा atio_from_isp *atio, uपूर्णांक16_t status)
अणु
	काष्ठा scsi_qla_host *vha = qpair->vha;
	काष्ठा ctio7_to_24xx *ctio24;
	काष्ठा qla_hw_data *ha = vha->hw;
	request_t *pkt;
	काष्ठा fc_port *sess = शून्य;
	अचिन्हित दीर्घ flags;
	u16 temp;
	port_id_t id;

	id = be_to_port_id(atio->u.isp24.fcp_hdr.s_id);

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);
	sess = qla2x00_find_fcport_by_nportid(vha, &id, 1);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
	अगर (!sess) अणु
		qlt_send_term_exchange(qpair, शून्य, atio, 1, 0);
		वापस 0;
	पूर्ण
	/* Sending marker isn't necessary, since we called from ISR */

	pkt = (request_t *)__qla2x00_alloc_iocbs(qpair, शून्य);
	अगर (!pkt) अणु
		ql_dbg(ql_dbg_io, vha, 0x3063,
		    "qla_target(%d): %s failed: unable to allocate "
		    "request packet", vha->vp_idx, __func__);
		वापस -ENOMEM;
	पूर्ण

	qpair->tgt_counters.num_q_full_sent++;
	pkt->entry_count = 1;
	pkt->handle = QLA_TGT_SKIP_HANDLE | CTIO_COMPLETION_HANDLE_MARK;

	ctio24 = (काष्ठा ctio7_to_24xx *)pkt;
	ctio24->entry_type = CTIO_TYPE7;
	ctio24->nport_handle = cpu_to_le16(sess->loop_id);
	ctio24->समयout = cpu_to_le16(QLA_TGT_TIMEOUT);
	ctio24->vp_index = vha->vp_idx;
	ctio24->initiator_id = be_id_to_le(atio->u.isp24.fcp_hdr.s_id);
	ctio24->exchange_addr = atio->u.isp24.exchange_addr;
	temp = (atio->u.isp24.attr << 9) |
		CTIO7_FLAGS_STATUS_MODE_1 | CTIO7_FLAGS_SEND_STATUS |
		CTIO7_FLAGS_DONT_RET_CTIO;
	ctio24->u.status1.flags = cpu_to_le16(temp);
	/*
	 * CTIO from fw w/o se_cmd करोesn't provide enough info to retry it,
	 * अगर the explicit conक्रमmation is used.
	 */
	ctio24->u.status1.ox_id =
		cpu_to_le16(be16_to_cpu(atio->u.isp24.fcp_hdr.ox_id));
	ctio24->u.status1.scsi_status = cpu_to_le16(status);

	ctio24->u.status1.residual = cpu_to_le32(get_datalen_क्रम_atio(atio));

	अगर (ctio24->u.status1.residual != 0)
		ctio24->u.status1.scsi_status |= cpu_to_le16(SS_RESIDUAL_UNDER);

	/* Memory Barrier */
	wmb();
	अगर (qpair->reqq_start_iocbs)
		qpair->reqq_start_iocbs(qpair);
	अन्यथा
		qla2x00_start_iocbs(vha, qpair->req);
	वापस 0;
पूर्ण

/*
 * This routine is used to allocate a command क्रम either a QFull condition
 * (ie reply SAM_STAT_BUSY) or to terminate an exchange that did not go
 * out previously.
 */
अटल व्योम
qlt_alloc_qfull_cmd(काष्ठा scsi_qla_host *vha,
	काष्ठा atio_from_isp *atio, uपूर्णांक16_t status, पूर्णांक qfull)
अणु
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess;
	काष्ठा qla_tgt_cmd *cmd;
	अचिन्हित दीर्घ flags;

	अगर (unlikely(tgt->tgt_stop)) अणु
		ql_dbg(ql_dbg_io, vha, 0x300a,
			"New command while device %p is shutting down\n", tgt);
		वापस;
	पूर्ण

	अगर ((vha->hw->tgt.num_qfull_cmds_alloc + 1) > MAX_QFULL_CMDS_ALLOC) अणु
		vha->hw->tgt.num_qfull_cmds_dropped++;
		अगर (vha->hw->tgt.num_qfull_cmds_dropped >
			vha->qla_stats.stat_max_qfull_cmds_dropped)
			vha->qla_stats.stat_max_qfull_cmds_dropped =
				vha->hw->tgt.num_qfull_cmds_dropped;

		ql_dbg(ql_dbg_io, vha, 0x3068,
			"qla_target(%d): %s: QFull CMD dropped[%d]\n",
			vha->vp_idx, __func__,
			vha->hw->tgt.num_qfull_cmds_dropped);

		qlt_chk_exch_leak_thresh_hold(vha);
		वापस;
	पूर्ण

	sess = ha->tgt.tgt_ops->find_sess_by_s_id
		(vha, atio->u.isp24.fcp_hdr.s_id);
	अगर (!sess)
		वापस;

	cmd = ha->tgt.tgt_ops->get_cmd(sess);
	अगर (!cmd) अणु
		ql_dbg(ql_dbg_io, vha, 0x3009,
			"qla_target(%d): %s: Allocation of cmd failed\n",
			vha->vp_idx, __func__);

		vha->hw->tgt.num_qfull_cmds_dropped++;
		अगर (vha->hw->tgt.num_qfull_cmds_dropped >
			vha->qla_stats.stat_max_qfull_cmds_dropped)
			vha->qla_stats.stat_max_qfull_cmds_dropped =
				vha->hw->tgt.num_qfull_cmds_dropped;

		qlt_chk_exch_leak_thresh_hold(vha);
		वापस;
	पूर्ण

	qlt_incr_num_pend_cmds(vha);
	INIT_LIST_HEAD(&cmd->cmd_list);
	स_नकल(&cmd->atio, atio, माप(*atio));

	cmd->tgt = vha->vha_tgt.qla_tgt;
	cmd->vha = vha;
	cmd->reset_count = ha->base_qpair->chip_reset;
	cmd->q_full = 1;
	cmd->qpair = ha->base_qpair;

	अगर (qfull) अणु
		cmd->q_full = 1;
		/* NOTE: borrowing the state field to carry the status */
		cmd->state = status;
	पूर्ण अन्यथा
		cmd->term_exchg = 1;

	spin_lock_irqsave(&vha->hw->tgt.q_full_lock, flags);
	list_add_tail(&cmd->cmd_list, &vha->hw->tgt.q_full_list);

	vha->hw->tgt.num_qfull_cmds_alloc++;
	अगर (vha->hw->tgt.num_qfull_cmds_alloc >
		vha->qla_stats.stat_max_qfull_cmds_alloc)
		vha->qla_stats.stat_max_qfull_cmds_alloc =
			vha->hw->tgt.num_qfull_cmds_alloc;
	spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);
पूर्ण

पूर्णांक
qlt_मुक्त_qfull_cmds(काष्ठा qla_qpair *qpair)
अणु
	काष्ठा scsi_qla_host *vha = qpair->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_tgt_cmd *cmd, *tcmd;
	काष्ठा list_head मुक्त_list, q_full_list;
	पूर्णांक rc = 0;

	अगर (list_empty(&ha->tgt.q_full_list))
		वापस 0;

	INIT_LIST_HEAD(&मुक्त_list);
	INIT_LIST_HEAD(&q_full_list);

	spin_lock_irqsave(&vha->hw->tgt.q_full_lock, flags);
	अगर (list_empty(&ha->tgt.q_full_list)) अणु
		spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);
		वापस 0;
	पूर्ण

	list_splice_init(&vha->hw->tgt.q_full_list, &q_full_list);
	spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);

	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	list_क्रम_each_entry_safe(cmd, tcmd, &q_full_list, cmd_list) अणु
		अगर (cmd->q_full)
			/* cmd->state is a borrowed field to hold status */
			rc = __qlt_send_busy(qpair, &cmd->atio, cmd->state);
		अन्यथा अगर (cmd->term_exchg)
			rc = __qlt_send_term_exchange(qpair, शून्य, &cmd->atio);

		अगर (rc == -ENOMEM)
			अवरोध;

		अगर (cmd->q_full)
			ql_dbg(ql_dbg_io, vha, 0x3006,
			    "%s: busy sent for ox_id[%04x]\n", __func__,
			    be16_to_cpu(cmd->atio.u.isp24.fcp_hdr.ox_id));
		अन्यथा अगर (cmd->term_exchg)
			ql_dbg(ql_dbg_io, vha, 0x3007,
			    "%s: Term exchg sent for ox_id[%04x]\n", __func__,
			    be16_to_cpu(cmd->atio.u.isp24.fcp_hdr.ox_id));
		अन्यथा
			ql_dbg(ql_dbg_io, vha, 0x3008,
			    "%s: Unexpected cmd in QFull list %p\n", __func__,
			    cmd);

		list_del(&cmd->cmd_list);
		list_add_tail(&cmd->cmd_list, &मुक्त_list);

		/* piggy back on hardware_lock क्रम protection */
		vha->hw->tgt.num_qfull_cmds_alloc--;
	पूर्ण
	spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	cmd = शून्य;

	list_क्रम_each_entry_safe(cmd, tcmd, &मुक्त_list, cmd_list) अणु
		list_del(&cmd->cmd_list);
		/* This cmd was never sent to TCM.  There is no need
		 * to schedule मुक्त or call मुक्त_cmd
		 */
		qlt_मुक्त_cmd(cmd);
	पूर्ण

	अगर (!list_empty(&q_full_list)) अणु
		spin_lock_irqsave(&vha->hw->tgt.q_full_lock, flags);
		list_splice(&q_full_list, &vha->hw->tgt.q_full_list);
		spin_unlock_irqrestore(&vha->hw->tgt.q_full_lock, flags);
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम
qlt_send_busy(काष्ठा qla_qpair *qpair, काष्ठा atio_from_isp *atio,
    uपूर्णांक16_t status)
अणु
	पूर्णांक rc = 0;
	काष्ठा scsi_qla_host *vha = qpair->vha;

	rc = __qlt_send_busy(qpair, atio, status);
	अगर (rc == -ENOMEM)
		qlt_alloc_qfull_cmd(vha, atio, status, 1);
पूर्ण

अटल पूर्णांक
qlt_chk_qfull_thresh_hold(काष्ठा scsi_qla_host *vha, काष्ठा qla_qpair *qpair,
	काष्ठा atio_from_isp *atio, uपूर्णांक8_t ha_locked)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;

	अगर (ha->tgt.num_pend_cmds < Q_FULL_THRESH_HOLD(ha))
		वापस 0;

	अगर (!ha_locked)
		spin_lock_irqsave(&ha->hardware_lock, flags);
	qlt_send_busy(qpair, atio, qla_sam_status);
	अगर (!ha_locked)
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस 1;
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
/* called via callback from qla2xxx */
अटल व्योम qlt_24xx_atio_pkt(काष्ठा scsi_qla_host *vha,
	काष्ठा atio_from_isp *atio, uपूर्णांक8_t ha_locked)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags = 0;

	अगर (unlikely(tgt == शून्य)) अणु
		ql_dbg(ql_dbg_tgt, vha, 0x3064,
		    "ATIO pkt, but no tgt (ha %p)", ha);
		वापस;
	पूर्ण
	/*
	 * In tgt_stop mode we also should allow all requests to pass.
	 * Otherwise, some commands can stuck.
	 */

	tgt->atio_irq_cmd_count++;

	चयन (atio->u.raw.entry_type) अणु
	हाल ATIO_TYPE7:
		अगर (unlikely(atio->u.isp24.exchange_addr ==
			     cpu_to_le32(ATIO_EXCHANGE_ADDRESS_UNKNOWN))) अणु
			ql_dbg(ql_dbg_io, vha, 0x3065,
			    "qla_target(%d): ATIO_TYPE7 "
			    "received with UNKNOWN exchange address, "
			    "sending QUEUE_FULL\n", vha->vp_idx);
			अगर (!ha_locked)
				spin_lock_irqsave(&ha->hardware_lock, flags);
			qlt_send_busy(ha->base_qpair, atio, qla_sam_status);
			अगर (!ha_locked)
				spin_unlock_irqrestore(&ha->hardware_lock,
				    flags);
			अवरोध;
		पूर्ण

		अगर (likely(atio->u.isp24.fcp_cmnd.task_mgmt_flags == 0)) अणु
			rc = qlt_chk_qfull_thresh_hold(vha, ha->base_qpair,
			    atio, ha_locked);
			अगर (rc != 0) अणु
				tgt->atio_irq_cmd_count--;
				वापस;
			पूर्ण
			rc = qlt_handle_cmd_क्रम_atio(vha, atio);
		पूर्ण अन्यथा अणु
			rc = qlt_handle_task_mgmt(vha, atio);
		पूर्ण
		अगर (unlikely(rc != 0)) अणु
			अगर (!ha_locked)
				spin_lock_irqsave(&ha->hardware_lock, flags);
			चयन (rc) अणु
			हाल -ENODEV:
				ql_dbg(ql_dbg_tgt, vha, 0xe05f,
				    "qla_target: Unable to send command to target\n");
				अवरोध;
			हाल -EBADF:
				ql_dbg(ql_dbg_tgt, vha, 0xe05f,
				    "qla_target: Unable to send command to target, sending TERM EXCHANGE for rsp\n");
				qlt_send_term_exchange(ha->base_qpair, शून्य,
				    atio, 1, 0);
				अवरोध;
			हाल -EBUSY:
				ql_dbg(ql_dbg_tgt, vha, 0xe060,
				    "qla_target(%d): Unable to send command to target, sending BUSY status\n",
				    vha->vp_idx);
				qlt_send_busy(ha->base_qpair, atio,
				    tc_sam_status);
				अवरोध;
			शेष:
				ql_dbg(ql_dbg_tgt, vha, 0xe060,
				    "qla_target(%d): Unable to send command to target, sending BUSY status\n",
				    vha->vp_idx);
				qlt_send_busy(ha->base_qpair, atio,
				    qla_sam_status);
				अवरोध;
			पूर्ण
			अगर (!ha_locked)
				spin_unlock_irqrestore(&ha->hardware_lock,
				    flags);
		पूर्ण
		अवरोध;

	हाल IMMED_NOTIFY_TYPE:
	अणु
		अगर (unlikely(atio->u.isp2x.entry_status != 0)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe05b,
			    "qla_target(%d): Received ATIO packet %x "
			    "with error status %x\n", vha->vp_idx,
			    atio->u.raw.entry_type,
			    atio->u.isp2x.entry_status);
			अवरोध;
		पूर्ण
		ql_dbg(ql_dbg_tgt, vha, 0xe02e, "%s", "IMMED_NOTIFY ATIO");

		अगर (!ha_locked)
			spin_lock_irqsave(&ha->hardware_lock, flags);
		qlt_handle_imm_notअगरy(vha, (काष्ठा imm_ntfy_from_isp *)atio);
		अगर (!ha_locked)
			spin_unlock_irqrestore(&ha->hardware_lock, flags);
		अवरोध;
	पूर्ण

	शेष:
		ql_dbg(ql_dbg_tgt, vha, 0xe05c,
		    "qla_target(%d): Received unknown ATIO atio "
		    "type %x\n", vha->vp_idx, atio->u.raw.entry_type);
		अवरोध;
	पूर्ण

	tgt->atio_irq_cmd_count--;
पूर्ण

/*
 * qpair lock is assume to be held
 * rc = 0 : send terminate & abts respond
 * rc != 0: करो not send term & abts respond
 */
अटल पूर्णांक qlt_chk_unresolv_exchg(काष्ठा scsi_qla_host *vha,
    काष्ठा qla_qpair *qpair, काष्ठा abts_resp_from_24xx_fw *entry)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rc = 0;

	/*
	 * Detect unresolved exchange. If the same ABTS is unable
	 * to terminate an existing command and the same ABTS loops
	 * between FW & Driver, then क्रमce FW dump. Under 1 jअगरf,
	 * we should see multiple loops.
	 */
	अगर (qpair->retry_term_exchg_addr == entry->exchange_addr_to_पात &&
	    qpair->retry_term_jअगरf == jअगरfies) अणु
		/* found existing exchange */
		qpair->retry_term_cnt++;
		अगर (qpair->retry_term_cnt >= 5) अणु
			rc = -EIO;
			qpair->retry_term_cnt = 0;
			ql_log(ql_log_warn, vha, 0xffff,
			    "Unable to send ABTS Respond. Dumping firmware.\n");
			ql_dump_buffer(ql_dbg_tgt_mgt + ql_dbg_buffer,
			    vha, 0xffff, (uपूर्णांक8_t *)entry, माप(*entry));

			अगर (qpair == ha->base_qpair)
				ha->isp_ops->fw_dump(vha);
			अन्यथा
				qla2xxx_dump_fw(vha);

			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण
	पूर्ण अन्यथा अगर (qpair->retry_term_jअगरf != jअगरfies) अणु
		qpair->retry_term_exchg_addr = entry->exchange_addr_to_पात;
		qpair->retry_term_cnt = 0;
		qpair->retry_term_jअगरf = jअगरfies;
	पूर्ण

	वापस rc;
पूर्ण


अटल व्योम qlt_handle_abts_completion(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp, response_t *pkt)
अणु
	काष्ठा abts_resp_from_24xx_fw *entry =
		(काष्ठा abts_resp_from_24xx_fw *)pkt;
	u32 h = pkt->handle & ~QLA_TGT_HANDLE_MASK;
	काष्ठा qla_tgt_mgmt_cmd *mcmd;
	काष्ठा qla_hw_data *ha = vha->hw;

	mcmd = qlt_ctio_to_cmd(vha, rsp, pkt->handle, pkt);
	अगर (mcmd == शून्य && h != QLA_TGT_SKIP_HANDLE) अणु
		ql_dbg(ql_dbg_async, vha, 0xe064,
		    "qla_target(%d): ABTS Comp without mcmd\n",
		    vha->vp_idx);
		वापस;
	पूर्ण

	अगर (mcmd)
		vha  = mcmd->vha;
	vha->vha_tgt.qla_tgt->abts_resp_expected--;

	ql_dbg(ql_dbg_tgt, vha, 0xe038,
	    "ABTS_RESP_24XX: compl_status %x\n",
	    entry->compl_status);

	अगर (le16_to_cpu(entry->compl_status) != ABTS_RESP_COMPL_SUCCESS) अणु
		अगर (le32_to_cpu(entry->error_subcode1) == 0x1E &&
		    le32_to_cpu(entry->error_subcode2) == 0) अणु
			अगर (qlt_chk_unresolv_exchg(vha, rsp->qpair, entry)) अणु
				ha->tgt.tgt_ops->मुक्त_mcmd(mcmd);
				वापस;
			पूर्ण
			qlt_24xx_retry_term_exchange(vha, rsp->qpair,
			    pkt, mcmd);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe063,
			    "qla_target(%d): ABTS_RESP_24XX failed %x (subcode %x:%x)",
			    vha->vp_idx, entry->compl_status,
			    entry->error_subcode1,
			    entry->error_subcode2);
			ha->tgt.tgt_ops->मुक्त_mcmd(mcmd);
		पूर्ण
	पूर्ण अन्यथा अगर (mcmd) अणु
		ha->tgt.tgt_ops->मुक्त_mcmd(mcmd);
	पूर्ण
पूर्ण

/* ha->hardware_lock supposed to be held on entry */
/* called via callback from qla2xxx */
अटल व्योम qlt_response_pkt(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp, response_t *pkt)
अणु
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;

	अगर (unlikely(tgt == शून्य)) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe05d,
		    "qla_target(%d): Response pkt %x received, but no tgt (ha %p)\n",
		    vha->vp_idx, pkt->entry_type, vha->hw);
		वापस;
	पूर्ण

	/*
	 * In tgt_stop mode we also should allow all requests to pass.
	 * Otherwise, some commands can stuck.
	 */

	चयन (pkt->entry_type) अणु
	हाल CTIO_CRC2:
	हाल CTIO_TYPE7:
	अणु
		काष्ठा ctio7_from_24xx *entry = (काष्ठा ctio7_from_24xx *)pkt;

		qlt_करो_ctio_completion(vha, rsp, entry->handle,
		    le16_to_cpu(entry->status)|(pkt->entry_status << 16),
		    entry);
		अवरोध;
	पूर्ण

	हाल ACCEPT_TGT_IO_TYPE:
	अणु
		काष्ठा atio_from_isp *atio = (काष्ठा atio_from_isp *)pkt;
		पूर्णांक rc;

		अगर (atio->u.isp2x.status !=
		    cpu_to_le16(ATIO_CDB_VALID)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe05e,
			    "qla_target(%d): ATIO with error "
			    "status %x received\n", vha->vp_idx,
			    le16_to_cpu(atio->u.isp2x.status));
			अवरोध;
		पूर्ण

		rc = qlt_chk_qfull_thresh_hold(vha, rsp->qpair, atio, 1);
		अगर (rc != 0)
			वापस;

		rc = qlt_handle_cmd_क्रम_atio(vha, atio);
		अगर (unlikely(rc != 0)) अणु
			चयन (rc) अणु
			हाल -ENODEV:
				ql_dbg(ql_dbg_tgt, vha, 0xe05f,
				    "qla_target: Unable to send command to target\n");
				अवरोध;
			हाल -EBADF:
				ql_dbg(ql_dbg_tgt, vha, 0xe05f,
				    "qla_target: Unable to send command to target, sending TERM EXCHANGE for rsp\n");
				qlt_send_term_exchange(rsp->qpair, शून्य,
				    atio, 1, 0);
				अवरोध;
			हाल -EBUSY:
				ql_dbg(ql_dbg_tgt, vha, 0xe060,
				    "qla_target(%d): Unable to send command to target, sending BUSY status\n",
				    vha->vp_idx);
				qlt_send_busy(rsp->qpair, atio,
				    tc_sam_status);
				अवरोध;
			शेष:
				ql_dbg(ql_dbg_tgt, vha, 0xe060,
				    "qla_target(%d): Unable to send command to target, sending BUSY status\n",
				    vha->vp_idx);
				qlt_send_busy(rsp->qpair, atio,
				    qla_sam_status);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अवरोध;

	हाल CONTINUE_TGT_IO_TYPE:
	अणु
		काष्ठा ctio_to_2xxx *entry = (काष्ठा ctio_to_2xxx *)pkt;

		qlt_करो_ctio_completion(vha, rsp, entry->handle,
		    le16_to_cpu(entry->status)|(pkt->entry_status << 16),
		    entry);
		अवरोध;
	पूर्ण

	हाल CTIO_A64_TYPE:
	अणु
		काष्ठा ctio_to_2xxx *entry = (काष्ठा ctio_to_2xxx *)pkt;

		qlt_करो_ctio_completion(vha, rsp, entry->handle,
		    le16_to_cpu(entry->status)|(pkt->entry_status << 16),
		    entry);
		अवरोध;
	पूर्ण

	हाल IMMED_NOTIFY_TYPE:
		ql_dbg(ql_dbg_tgt, vha, 0xe035, "%s", "IMMED_NOTIFY\n");
		qlt_handle_imm_notअगरy(vha, (काष्ठा imm_ntfy_from_isp *)pkt);
		अवरोध;

	हाल NOTIFY_ACK_TYPE:
		अगर (tgt->notअगरy_ack_expected > 0) अणु
			काष्ठा nack_to_isp *entry = (काष्ठा nack_to_isp *)pkt;

			ql_dbg(ql_dbg_tgt, vha, 0xe036,
			    "NOTIFY_ACK seq %08x status %x\n",
			    le16_to_cpu(entry->u.isp2x.seq_id),
			    le16_to_cpu(entry->u.isp2x.status));
			tgt->notअगरy_ack_expected--;
			अगर (entry->u.isp2x.status !=
			    cpu_to_le16(NOTIFY_ACK_SUCCESS)) अणु
				ql_dbg(ql_dbg_tgt, vha, 0xe061,
				    "qla_target(%d): NOTIFY_ACK "
				    "failed %x\n", vha->vp_idx,
				    le16_to_cpu(entry->u.isp2x.status));
			पूर्ण
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe062,
			    "qla_target(%d): Unexpected NOTIFY_ACK received\n",
			    vha->vp_idx);
		पूर्ण
		अवरोध;

	हाल ABTS_RECV_24XX:
		ql_dbg(ql_dbg_tgt, vha, 0xe037,
		    "ABTS_RECV_24XX: instance %d\n", vha->vp_idx);
		qlt_24xx_handle_abts(vha, (काष्ठा abts_recv_from_24xx *)pkt);
		अवरोध;

	हाल ABTS_RESP_24XX:
		अगर (tgt->abts_resp_expected > 0) अणु
			qlt_handle_abts_completion(vha, rsp, pkt);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe064,
			    "qla_target(%d): Unexpected ABTS_RESP_24XX "
			    "received\n", vha->vp_idx);
		पूर्ण
		अवरोध;

	शेष:
		ql_dbg(ql_dbg_tgt, vha, 0xe065,
		    "qla_target(%d): Received unknown response pkt "
		    "type %x\n", vha->vp_idx, pkt->entry_type);
		अवरोध;
	पूर्ण

पूर्ण

/*
 * ha->hardware_lock supposed to be held on entry. Might drop it, then reaquire
 */
व्योम qlt_async_event(uपूर्णांक16_t code, काष्ठा scsi_qla_host *vha,
	uपूर्णांक16_t *mailbox)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	पूर्णांक login_code;

	अगर (!tgt || tgt->tgt_stop || tgt->tgt_stopped)
		वापस;

	अगर (((code == MBA_POINT_TO_POINT) || (code == MBA_CHG_IN_CONNECTION)) &&
	    IS_QLA2100(ha))
		वापस;
	/*
	 * In tgt_stop mode we also should allow all requests to pass.
	 * Otherwise, some commands can stuck.
	 */


	चयन (code) अणु
	हाल MBA_RESET:			/* Reset */
	हाल MBA_SYSTEM_ERR:		/* System Error */
	हाल MBA_REQ_TRANSFER_ERR:	/* Request Transfer Error */
	हाल MBA_RSP_TRANSFER_ERR:	/* Response Transfer Error */
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03a,
		    "qla_target(%d): System error async event %#x "
		    "occurred", vha->vp_idx, code);
		अवरोध;
	हाल MBA_WAKEUP_THRES:		/* Request Queue Wake-up. */
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MBA_LOOP_UP:
	अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03b,
		    "qla_target(%d): Async LOOP_UP occurred "
		    "(m[0]=%x, m[1]=%x, m[2]=%x, m[3]=%x)", vha->vp_idx,
		    mailbox[0], mailbox[1], mailbox[2], mailbox[3]);
		अगर (tgt->link_reinit_iocb_pending) अणु
			qlt_send_notअगरy_ack(ha->base_qpair,
			    &tgt->link_reinit_iocb,
			    0, 0, 0, 0, 0, 0);
			tgt->link_reinit_iocb_pending = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	हाल MBA_LIP_OCCURRED:
	हाल MBA_LOOP_DOWN:
	हाल MBA_LIP_RESET:
	हाल MBA_RSCN_UPDATE:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03c,
		    "qla_target(%d): Async event %#x occurred "
		    "(m[0]=%x, m[1]=%x, m[2]=%x, m[3]=%x)", vha->vp_idx, code,
		    mailbox[0], mailbox[1], mailbox[2], mailbox[3]);
		अवरोध;

	हाल MBA_REJECTED_FCP_CMD:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf017,
		    "qla_target(%d): Async event LS_REJECT occurred (m[0]=%x, m[1]=%x, m[2]=%x, m[3]=%x)",
		    vha->vp_idx,
		    mailbox[0], mailbox[1], mailbox[2], mailbox[3]);

		अगर (mailbox[3] == 1) अणु
			/* exchange starvation. */
			vha->hw->exch_starvation++;
			अगर (vha->hw->exch_starvation > 5) अणु
				ql_log(ql_log_warn, vha, 0xd03a,
				    "Exchange starvation-. Resetting RISC\n");

				vha->hw->exch_starvation = 0;
				अगर (IS_P3P_TYPE(vha->hw))
					set_bit(FCOE_CTX_RESET_NEEDED,
					    &vha->dpc_flags);
				अन्यथा
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल MBA_PORT_UPDATE:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03d,
		    "qla_target(%d): Port update async event %#x "
		    "occurred: updating the ports database (m[0]=%x, m[1]=%x, "
		    "m[2]=%x, m[3]=%x)", vha->vp_idx, code,
		    mailbox[0], mailbox[1], mailbox[2], mailbox[3]);

		login_code = mailbox[2];
		अगर (login_code == 0x4) अणु
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03e,
			    "Async MB 2: Got PLOGI Complete\n");
			vha->hw->exch_starvation = 0;
		पूर्ण अन्यथा अगर (login_code == 0x7)
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf03f,
			    "Async MB 2: Port Logged Out\n");
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

पूर्ण

अटल fc_port_t *qlt_get_port_database(काष्ठा scsi_qla_host *vha,
	uपूर्णांक16_t loop_id)
अणु
	fc_port_t *fcport, *tfcp, *del;
	पूर्णांक rc;
	अचिन्हित दीर्घ flags;
	u8 newfcport = 0;

	fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (!fcport) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf06f,
		    "qla_target(%d): Allocation of tmp FC port failed",
		    vha->vp_idx);
		वापस शून्य;
	पूर्ण

	fcport->loop_id = loop_id;

	rc = qla24xx_gpdb_रुको(vha, fcport, 0);
	अगर (rc != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf070,
		    "qla_target(%d): Failed to retrieve fcport "
		    "information -- get_port_database() returned %x "
		    "(loop_id=0x%04x)", vha->vp_idx, rc, loop_id);
		kमुक्त(fcport);
		वापस शून्य;
	पूर्ण

	del = शून्य;
	spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
	tfcp = qla2x00_find_fcport_by_wwpn(vha, fcport->port_name, 1);

	अगर (tfcp) अणु
		tfcp->d_id = fcport->d_id;
		tfcp->port_type = fcport->port_type;
		tfcp->supported_classes = fcport->supported_classes;
		tfcp->flags |= fcport->flags;
		tfcp->scan_state = QLA_FCPORT_FOUND;

		del = fcport;
		fcport = tfcp;
	पूर्ण अन्यथा अणु
		अगर (vha->hw->current_topology == ISP_CFG_F)
			fcport->flags |= FCF_FABRIC_DEVICE;

		list_add_tail(&fcport->list, &vha->vp_fcports);
		अगर (!IS_SW_RESV_ADDR(fcport->d_id))
		   vha->fcport_count++;
		fcport->login_gen++;
		qla2x00_set_fcport_disc_state(fcport, DSC_LOGIN_COMPLETE);
		fcport->login_succ = 1;
		newfcport = 1;
	पूर्ण

	fcport->deleted = 0;
	spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);

	चयन (vha->host->active_mode) अणु
	हाल MODE_INITIATOR:
	हाल MODE_DUAL:
		अगर (newfcport) अणु
			अगर (!IS_IIDMA_CAPABLE(vha->hw) || !vha->hw->flags.gpsc_supported) अणु
				qla24xx_sched_upd_fcport(fcport);
			पूर्ण अन्यथा अणु
				ql_dbg(ql_dbg_disc, vha, 0x20ff,
				   "%s %d %8phC post gpsc fcp_cnt %d\n",
				   __func__, __LINE__, fcport->port_name, vha->fcport_count);
				qla24xx_post_gpsc_work(vha, fcport);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल MODE_TARGET:
	शेष:
		अवरोध;
	पूर्ण
	अगर (del)
		qla2x00_मुक्त_fcport(del);

	वापस fcport;
पूर्ण

/* Must be called under tgt_mutex */
अटल काष्ठा fc_port *qlt_make_local_sess(काष्ठा scsi_qla_host *vha,
					   be_id_t s_id)
अणु
	काष्ठा fc_port *sess = शून्य;
	fc_port_t *fcport = शून्य;
	पूर्णांक rc, global_resets;
	uपूर्णांक16_t loop_id = 0;

	अगर (s_id.करोमुख्य == 0xFF && s_id.area == 0xFC) अणु
		/*
		 * This is Doमुख्य Controller, so it should be
		 * OK to drop SCSI commands from it.
		 */
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf042,
		    "Unable to find initiator with S_ID %x:%x:%x",
		    s_id.करोमुख्य, s_id.area, s_id.al_pa);
		वापस शून्य;
	पूर्ण

	mutex_lock(&vha->vha_tgt.tgt_mutex);

retry:
	global_resets =
	    atomic_पढ़ो(&vha->vha_tgt.qla_tgt->tgt_global_resets_count);

	rc = qla24xx_get_loop_id(vha, s_id, &loop_id);
	अगर (rc != 0) अणु
		mutex_unlock(&vha->vha_tgt.tgt_mutex);

		ql_log(ql_log_info, vha, 0xf071,
		    "qla_target(%d): Unable to find "
		    "initiator with S_ID %x:%x:%x",
		    vha->vp_idx, s_id.करोमुख्य, s_id.area, s_id.al_pa);

		अगर (rc == -ENOENT) अणु
			qlt_port_logo_t logo;

			logo.id = be_to_port_id(s_id);
			logo.cmd_count = 1;
			qlt_send_first_logo(vha, &logo);
		पूर्ण

		वापस शून्य;
	पूर्ण

	fcport = qlt_get_port_database(vha, loop_id);
	अगर (!fcport) अणु
		mutex_unlock(&vha->vha_tgt.tgt_mutex);
		वापस शून्य;
	पूर्ण

	अगर (global_resets !=
	    atomic_पढ़ो(&vha->vha_tgt.qla_tgt->tgt_global_resets_count)) अणु
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf043,
		    "qla_target(%d): global reset during session discovery "
		    "(counter was %d, new %d), retrying", vha->vp_idx,
		    global_resets,
		    atomic_पढ़ो(&vha->vha_tgt.
			qla_tgt->tgt_global_resets_count));
		जाओ retry;
	पूर्ण

	sess = qlt_create_sess(vha, fcport, true);

	mutex_unlock(&vha->vha_tgt.tgt_mutex);

	वापस sess;
पूर्ण

अटल व्योम qlt_पात_work(काष्ठा qla_tgt *tgt,
	काष्ठा qla_tgt_sess_work_param *prm)
अणु
	काष्ठा scsi_qla_host *vha = tgt->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess = शून्य;
	अचिन्हित दीर्घ flags = 0, flags2 = 0;
	be_id_t s_id;
	पूर्णांक rc;

	spin_lock_irqsave(&ha->tgt.sess_lock, flags2);

	अगर (tgt->tgt_stop)
		जाओ out_term2;

	s_id = le_id_to_be(prm->abts.fcp_hdr_le.s_id);

	sess = ha->tgt.tgt_ops->find_sess_by_s_id(vha, s_id);
	अगर (!sess) अणु
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags2);

		sess = qlt_make_local_sess(vha, s_id);
		/* sess has got an extra creation ref */

		spin_lock_irqsave(&ha->tgt.sess_lock, flags2);
		अगर (!sess)
			जाओ out_term2;
	पूर्ण अन्यथा अणु
		अगर (sess->deleted) अणु
			sess = शून्य;
			जाओ out_term2;
		पूर्ण

		अगर (!kref_get_unless_zero(&sess->sess_kref)) अणु
			ql_dbg(ql_dbg_tgt_पंचांगr, vha, 0xf01c,
			    "%s: kref_get fail %8phC \n",
			     __func__, sess->port_name);
			sess = शून्य;
			जाओ out_term2;
		पूर्ण
	पूर्ण

	rc = __qlt_24xx_handle_abts(vha, &prm->abts, sess);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags2);

	ha->tgt.tgt_ops->put_sess(sess);

	अगर (rc != 0)
		जाओ out_term;
	वापस;

out_term2:
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags2);

out_term:
	spin_lock_irqsave(&ha->hardware_lock, flags);
	qlt_24xx_send_abts_resp(ha->base_qpair, &prm->abts,
	    FCP_TMF_REJECTED, false);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

अटल व्योम qlt_पंचांगr_work(काष्ठा qla_tgt *tgt,
	काष्ठा qla_tgt_sess_work_param *prm)
अणु
	काष्ठा atio_from_isp *a = &prm->पंचांग_iocb2;
	काष्ठा scsi_qla_host *vha = tgt->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा fc_port *sess;
	अचिन्हित दीर्घ flags;
	be_id_t s_id;
	पूर्णांक rc;
	u64 unpacked_lun;
	पूर्णांक fn;
	व्योम *iocb;

	spin_lock_irqsave(&ha->tgt.sess_lock, flags);

	अगर (tgt->tgt_stop)
		जाओ out_term2;

	s_id = prm->पंचांग_iocb2.u.isp24.fcp_hdr.s_id;
	sess = ha->tgt.tgt_ops->find_sess_by_s_id(vha, s_id);
	अगर (!sess) अणु
		spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

		sess = qlt_make_local_sess(vha, s_id);
		/* sess has got an extra creation ref */

		spin_lock_irqsave(&ha->tgt.sess_lock, flags);
		अगर (!sess)
			जाओ out_term2;
	पूर्ण अन्यथा अणु
		अगर (sess->deleted) अणु
			जाओ out_term2;
		पूर्ण

		अगर (!kref_get_unless_zero(&sess->sess_kref)) अणु
			ql_dbg(ql_dbg_tgt_पंचांगr, vha, 0xf020,
			    "%s: kref_get fail %8phC\n",
			     __func__, sess->port_name);
			जाओ out_term2;
		पूर्ण
	पूर्ण

	iocb = a;
	fn = a->u.isp24.fcp_cmnd.task_mgmt_flags;
	unpacked_lun =
	    scsilun_to_पूर्णांक((काष्ठा scsi_lun *)&a->u.isp24.fcp_cmnd.lun);

	rc = qlt_issue_task_mgmt(sess, unpacked_lun, fn, iocb, 0);
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);

	ha->tgt.tgt_ops->put_sess(sess);

	अगर (rc != 0)
		जाओ out_term;
	वापस;

out_term2:
	spin_unlock_irqrestore(&ha->tgt.sess_lock, flags);
out_term:
	qlt_send_term_exchange(ha->base_qpair, शून्य, &prm->पंचांग_iocb2, 1, 0);
पूर्ण

अटल व्योम qlt_sess_work_fn(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_tgt *tgt = container_of(work, काष्ठा qla_tgt, sess_work);
	काष्ठा scsi_qla_host *vha = tgt->vha;
	अचिन्हित दीर्घ flags;

	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf000, "Sess work (tgt %p)", tgt);

	spin_lock_irqsave(&tgt->sess_work_lock, flags);
	जबतक (!list_empty(&tgt->sess_works_list)) अणु
		काष्ठा qla_tgt_sess_work_param *prm = list_entry(
		    tgt->sess_works_list.next, typeof(*prm),
		    sess_works_list_entry);

		/*
		 * This work can be scheduled on several CPUs at समय, so we
		 * must delete the entry to eliminate द्विगुन processing
		 */
		list_del(&prm->sess_works_list_entry);

		spin_unlock_irqrestore(&tgt->sess_work_lock, flags);

		चयन (prm->type) अणु
		हाल QLA_TGT_SESS_WORK_ABORT:
			qlt_पात_work(tgt, prm);
			अवरोध;
		हाल QLA_TGT_SESS_WORK_TM:
			qlt_पंचांगr_work(tgt, prm);
			अवरोध;
		शेष:
			BUG_ON(1);
			अवरोध;
		पूर्ण

		spin_lock_irqsave(&tgt->sess_work_lock, flags);

		kमुक्त(prm);
	पूर्ण
	spin_unlock_irqrestore(&tgt->sess_work_lock, flags);
पूर्ण

/* Must be called under tgt_host_action_mutex */
पूर्णांक qlt_add_target(काष्ठा qla_hw_data *ha, काष्ठा scsi_qla_host *base_vha)
अणु
	काष्ठा qla_tgt *tgt;
	पूर्णांक rc, i;
	काष्ठा qla_qpair_hपूर्णांक *h;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस 0;

	अगर (!IS_TGT_MODE_CAPABLE(ha)) अणु
		ql_log(ql_log_warn, base_vha, 0xe070,
		    "This adapter does not support target mode.\n");
		वापस 0;
	पूर्ण

	ql_dbg(ql_dbg_tgt, base_vha, 0xe03b,
	    "Registering target for host %ld(%p).\n", base_vha->host_no, ha);

	BUG_ON(base_vha->vha_tgt.qla_tgt != शून्य);

	tgt = kzalloc(माप(काष्ठा qla_tgt), GFP_KERNEL);
	अगर (!tgt) अणु
		ql_dbg(ql_dbg_tgt, base_vha, 0xe066,
		    "Unable to allocate struct qla_tgt\n");
		वापस -ENOMEM;
	पूर्ण

	tgt->qphपूर्णांकs = kसुस्मृति(ha->max_qpairs + 1,
			       माप(काष्ठा qla_qpair_hपूर्णांक),
			       GFP_KERNEL);
	अगर (!tgt->qphपूर्णांकs) अणु
		kमुक्त(tgt);
		ql_log(ql_log_warn, base_vha, 0x0197,
		    "Unable to allocate qpair hints.\n");
		वापस -ENOMEM;
	पूर्ण

	अगर (!(base_vha->host->hostt->supported_mode & MODE_TARGET))
		base_vha->host->hostt->supported_mode |= MODE_TARGET;

	rc = btree_init64(&tgt->lun_qpair_map);
	अगर (rc) अणु
		kमुक्त(tgt->qphपूर्णांकs);
		kमुक्त(tgt);
		ql_log(ql_log_info, base_vha, 0x0198,
			"Unable to initialize lun_qpair_map btree\n");
		वापस -EIO;
	पूर्ण
	h = &tgt->qphपूर्णांकs[0];
	h->qpair = ha->base_qpair;
	INIT_LIST_HEAD(&h->hपूर्णांक_elem);
	h->cpuid = ha->base_qpair->cpuid;
	list_add_tail(&h->hपूर्णांक_elem, &ha->base_qpair->hपूर्णांकs_list);

	क्रम (i = 0; i < ha->max_qpairs; i++) अणु
		अचिन्हित दीर्घ flags;

		काष्ठा qla_qpair *qpair = ha->queue_pair_map[i];

		h = &tgt->qphपूर्णांकs[i + 1];
		INIT_LIST_HEAD(&h->hपूर्णांक_elem);
		अगर (qpair) अणु
			h->qpair = qpair;
			spin_lock_irqsave(qpair->qp_lock_ptr, flags);
			list_add_tail(&h->hपूर्णांक_elem, &qpair->hपूर्णांकs_list);
			spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);
			h->cpuid = qpair->cpuid;
		पूर्ण
	पूर्ण

	tgt->ha = ha;
	tgt->vha = base_vha;
	init_रुकोqueue_head(&tgt->रुकोQ);
	INIT_LIST_HEAD(&tgt->del_sess_list);
	spin_lock_init(&tgt->sess_work_lock);
	INIT_WORK(&tgt->sess_work, qlt_sess_work_fn);
	INIT_LIST_HEAD(&tgt->sess_works_list);
	atomic_set(&tgt->tgt_global_resets_count, 0);

	base_vha->vha_tgt.qla_tgt = tgt;

	ql_dbg(ql_dbg_tgt, base_vha, 0xe067,
		"qla_target(%d): using 64 Bit PCI addressing",
		base_vha->vp_idx);
	/* 3 is reserved */
	tgt->sg_tablesize = QLA_TGT_MAX_SG_24XX(base_vha->req->length - 3);

	mutex_lock(&qla_tgt_mutex);
	list_add_tail(&tgt->tgt_list_entry, &qla_tgt_glist);
	mutex_unlock(&qla_tgt_mutex);

	अगर (ha->tgt.tgt_ops && ha->tgt.tgt_ops->add_target)
		ha->tgt.tgt_ops->add_target(base_vha);

	वापस 0;
पूर्ण

/* Must be called under tgt_host_action_mutex */
पूर्णांक qlt_हटाओ_target(काष्ठा qla_hw_data *ha, काष्ठा scsi_qla_host *vha)
अणु
	अगर (!vha->vha_tgt.qla_tgt)
		वापस 0;

	अगर (vha->fc_vport) अणु
		qlt_release(vha->vha_tgt.qla_tgt);
		वापस 0;
	पूर्ण

	/* मुक्त left over qfull cmds */
	qlt_init_term_exchange(vha);

	ql_dbg(ql_dbg_tgt, vha, 0xe03c, "Unregistering target for host %ld(%p)",
	    vha->host_no, ha);
	qlt_release(vha->vha_tgt.qla_tgt);

	वापस 0;
पूर्ण

व्योम qlt_हटाओ_target_resources(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा scsi_qla_host *node;
	u32 key = 0;

	btree_क्रम_each_safe32(&ha->tgt.host_map, key, node)
		btree_हटाओ32(&ha->tgt.host_map, key);

	btree_destroy32(&ha->tgt.host_map);
पूर्ण

अटल व्योम qlt_lport_dump(काष्ठा scsi_qla_host *vha, u64 wwpn,
	अचिन्हित अक्षर *b)
अणु
	pr_debug("qla2xxx HW vha->node_name: %8phC\n", vha->node_name);
	pr_debug("qla2xxx HW vha->port_name: %8phC\n", vha->port_name);
	put_unaligned_be64(wwpn, b);
	pr_debug("qla2xxx passed configfs WWPN: %8phC\n", b);
पूर्ण

/**
 * qlt_lport_रेजिस्टर - रेजिस्टर lport with बाह्यal module
 *
 * @target_lport_ptr: poपूर्णांकer क्रम tcm_qla2xxx specअगरic lport data
 * @phys_wwpn: physical port WWPN
 * @npiv_wwpn: NPIV WWPN
 * @npiv_wwnn: NPIV WWNN
 * @callback:  lport initialization callback क्रम tcm_qla2xxx code
 */
पूर्णांक qlt_lport_रेजिस्टर(व्योम *target_lport_ptr, u64 phys_wwpn,
		       u64 npiv_wwpn, u64 npiv_wwnn,
		       पूर्णांक (*callback)(काष्ठा scsi_qla_host *, व्योम *, u64, u64))
अणु
	काष्ठा qla_tgt *tgt;
	काष्ठा scsi_qla_host *vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा Scsi_Host *host;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;
	u8 b[WWN_SIZE];

	mutex_lock(&qla_tgt_mutex);
	list_क्रम_each_entry(tgt, &qla_tgt_glist, tgt_list_entry) अणु
		vha = tgt->vha;
		ha = vha->hw;

		host = vha->host;
		अगर (!host)
			जारी;

		अगर (!(host->hostt->supported_mode & MODE_TARGET))
			जारी;

		अगर (vha->qlini_mode == QLA2XXX_INI_MODE_ENABLED)
			जारी;

		spin_lock_irqsave(&ha->hardware_lock, flags);
		अगर ((!npiv_wwpn || !npiv_wwnn) && host->active_mode & MODE_TARGET) अणु
			pr_debug("MODE_TARGET already active on qla2xxx(%d)\n",
			    host->host_no);
			spin_unlock_irqrestore(&ha->hardware_lock, flags);
			जारी;
		पूर्ण
		अगर (tgt->tgt_stop) अणु
			pr_debug("MODE_TARGET in shutdown on qla2xxx(%d)\n",
				 host->host_no);
			spin_unlock_irqrestore(&ha->hardware_lock, flags);
			जारी;
		पूर्ण
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		अगर (!scsi_host_get(host)) अणु
			ql_dbg(ql_dbg_tgt, vha, 0xe068,
			    "Unable to scsi_host_get() for"
			    " qla2xxx scsi_host\n");
			जारी;
		पूर्ण
		qlt_lport_dump(vha, phys_wwpn, b);

		अगर (स_भेद(vha->port_name, b, WWN_SIZE)) अणु
			scsi_host_put(host);
			जारी;
		पूर्ण
		rc = (*callback)(vha, target_lport_ptr, npiv_wwpn, npiv_wwnn);
		अगर (rc != 0)
			scsi_host_put(host);

		mutex_unlock(&qla_tgt_mutex);
		वापस rc;
	पूर्ण
	mutex_unlock(&qla_tgt_mutex);

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL(qlt_lport_रेजिस्टर);

/**
 * qlt_lport_deरेजिस्टर - Degister lport
 *
 * @vha:  Registered scsi_qla_host poपूर्णांकer
 */
व्योम qlt_lport_deरेजिस्टर(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा Scsi_Host *sh = vha->host;
	/*
	 * Clear the target_lport_ptr qla_target_ढाँचा poपूर्णांकer in qla_hw_data
	 */
	vha->vha_tgt.target_lport_ptr = शून्य;
	ha->tgt.tgt_ops = शून्य;
	/*
	 * Release the Scsi_Host reference क्रम the underlying qla2xxx host
	 */
	scsi_host_put(sh);
पूर्ण
EXPORT_SYMBOL(qlt_lport_deरेजिस्टर);

/* Must be called under HW lock */
व्योम qlt_set_mode(काष्ठा scsi_qla_host *vha)
अणु
	चयन (vha->qlini_mode) अणु
	हाल QLA2XXX_INI_MODE_DISABLED:
	हाल QLA2XXX_INI_MODE_EXCLUSIVE:
		vha->host->active_mode = MODE_TARGET;
		अवरोध;
	हाल QLA2XXX_INI_MODE_ENABLED:
		vha->host->active_mode = MODE_INITIATOR;
		अवरोध;
	हाल QLA2XXX_INI_MODE_DUAL:
		vha->host->active_mode = MODE_DUAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/* Must be called under HW lock */
अटल व्योम qlt_clear_mode(काष्ठा scsi_qla_host *vha)
अणु
	चयन (vha->qlini_mode) अणु
	हाल QLA2XXX_INI_MODE_DISABLED:
		vha->host->active_mode = MODE_UNKNOWN;
		अवरोध;
	हाल QLA2XXX_INI_MODE_EXCLUSIVE:
		vha->host->active_mode = MODE_INITIATOR;
		अवरोध;
	हाल QLA2XXX_INI_MODE_ENABLED:
	हाल QLA2XXX_INI_MODE_DUAL:
		vha->host->active_mode = MODE_INITIATOR;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*
 * qla_tgt_enable_vha - NO LOCK HELD
 *
 * host_reset, bring up w/ Target Mode Enabled
 */
व्योम
qlt_enable_vha(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	अचिन्हित दीर्घ flags;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	अगर (!tgt) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe069,
		    "Unable to locate qla_tgt pointer from"
		    " struct qla_hw_data\n");
		dump_stack();
		वापस;
	पूर्ण
	अगर (vha->qlini_mode == QLA2XXX_INI_MODE_ENABLED)
		वापस;

	अगर (ha->tgt.num_act_qpairs > ha->max_qpairs)
		ha->tgt.num_act_qpairs = ha->max_qpairs;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	tgt->tgt_stopped = 0;
	qlt_set_mode(vha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	mutex_lock(&ha->optrom_mutex);
	ql_dbg(ql_dbg_tgt_mgt, vha, 0xf021,
	    "%s.\n", __func__);
	अगर (vha->vp_idx) अणु
		qla24xx_disable_vp(vha);
		qla24xx_enable_vp(vha);
	पूर्ण अन्यथा अणु
		set_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags);
		qla2xxx_wake_dpc(base_vha);
		WARN_ON_ONCE(qla2x00_रुको_क्रम_hba_online(base_vha) !=
			     QLA_SUCCESS);
	पूर्ण
	mutex_unlock(&ha->optrom_mutex);
पूर्ण
EXPORT_SYMBOL(qlt_enable_vha);

/*
 * qla_tgt_disable_vha - NO LOCK HELD
 *
 * Disable Target Mode and reset the adapter
 */
अटल व्योम qlt_disable_vha(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	अचिन्हित दीर्घ flags;

	अगर (!tgt) अणु
		ql_dbg(ql_dbg_tgt, vha, 0xe06a,
		    "Unable to locate qla_tgt pointer from"
		    " struct qla_hw_data\n");
		dump_stack();
		वापस;
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);
	qlt_clear_mode(vha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);

	/*
	 * We are expecting the offline state.
	 * QLA_FUNCTION_FAILED means that adapter is offline.
	 */
	अगर (qla2x00_रुको_क्रम_hba_online(vha) != QLA_SUCCESS)
		ql_dbg(ql_dbg_tgt, vha, 0xe081,
		       "adapter is offline\n");
पूर्ण

/*
 * Called from qla_init.c:qla24xx_vport_create() contex to setup
 * the target mode specअगरic काष्ठा scsi_qla_host and काष्ठा qla_hw_data
 * members.
 */
व्योम
qlt_vport_create(काष्ठा scsi_qla_host *vha, काष्ठा qla_hw_data *ha)
अणु
	vha->vha_tgt.qla_tgt = शून्य;

	mutex_init(&vha->vha_tgt.tgt_mutex);
	mutex_init(&vha->vha_tgt.tgt_host_action_mutex);

	qlt_clear_mode(vha);

	/*
	 * NOTE: Currently the value is kept the same क्रम <24xx and
	 * >=24xx ISPs. If it is necessary to change it,
	 * the check should be added क्रम specअगरic ISPs,
	 * assigning the value appropriately.
	 */
	ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;

	qlt_add_target(ha, vha);
पूर्ण

u8
qlt_rff_id(काष्ठा scsi_qla_host *vha)
अणु
	u8 fc4_feature = 0;
	/*
	 * FC-4 Feature bit 0 indicates target functionality to the name server.
	 */
	अगर (qla_tgt_mode_enabled(vha)) अणु
		fc4_feature = BIT_0;
	पूर्ण अन्यथा अगर (qla_ini_mode_enabled(vha)) अणु
		fc4_feature = BIT_1;
	पूर्ण अन्यथा अगर (qla_dual_mode_enabled(vha))
		fc4_feature = BIT_0 | BIT_1;

	वापस fc4_feature;
पूर्ण

/*
 * qlt_init_atio_q_entries() - Initializes ATIO queue entries.
 * @ha: HA context
 *
 * Beginning of ATIO ring has initialization control block alपढ़ोy built
 * by nvram config routine.
 *
 * Returns 0 on success.
 */
व्योम
qlt_init_atio_q_entries(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t cnt;
	काष्ठा atio_from_isp *pkt = (काष्ठा atio_from_isp *)ha->tgt.atio_ring;

	अगर (qla_ini_mode_enabled(vha))
		वापस;

	क्रम (cnt = 0; cnt < ha->tgt.atio_q_length; cnt++) अणु
		pkt->u.raw.signature = cpu_to_le32(ATIO_PROCESSED);
		pkt++;
	पूर्ण

पूर्ण

/*
 * qlt_24xx_process_atio_queue() - Process ATIO queue entries.
 * @ha: SCSI driver HA context
 */
व्योम
qlt_24xx_process_atio_queue(काष्ठा scsi_qla_host *vha, uपूर्णांक8_t ha_locked)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा atio_from_isp *pkt;
	पूर्णांक cnt, i;

	अगर (!ha->flags.fw_started)
		वापस;

	जबतक ((ha->tgt.atio_ring_ptr->signature != ATIO_PROCESSED) ||
	    fcpcmd_is_corrupted(ha->tgt.atio_ring_ptr)) अणु
		pkt = (काष्ठा atio_from_isp *)ha->tgt.atio_ring_ptr;
		cnt = pkt->u.raw.entry_count;

		अगर (unlikely(fcpcmd_is_corrupted(ha->tgt.atio_ring_ptr))) अणु
			/*
			 * This packet is corrupted. The header + payload
			 * can not be trusted. There is no poपूर्णांक in passing
			 * it further up.
			 */
			ql_log(ql_log_warn, vha, 0xd03c,
			    "corrupted fcp frame SID[%3phN] OXID[%04x] EXCG[%x] %64phN\n",
			    &pkt->u.isp24.fcp_hdr.s_id,
			    be16_to_cpu(pkt->u.isp24.fcp_hdr.ox_id),
			    pkt->u.isp24.exchange_addr, pkt);

			adjust_corrupted_atio(pkt);
			qlt_send_term_exchange(ha->base_qpair, शून्य, pkt,
			    ha_locked, 0);
		पूर्ण अन्यथा अणु
			qlt_24xx_atio_pkt_all_vps(vha,
			    (काष्ठा atio_from_isp *)pkt, ha_locked);
		पूर्ण

		क्रम (i = 0; i < cnt; i++) अणु
			ha->tgt.atio_ring_index++;
			अगर (ha->tgt.atio_ring_index == ha->tgt.atio_q_length) अणु
				ha->tgt.atio_ring_index = 0;
				ha->tgt.atio_ring_ptr = ha->tgt.atio_ring;
			पूर्ण अन्यथा
				ha->tgt.atio_ring_ptr++;

			pkt->u.raw.signature = cpu_to_le32(ATIO_PROCESSED);
			pkt = (काष्ठा atio_from_isp *)ha->tgt.atio_ring_ptr;
		पूर्ण
		wmb();
	पूर्ण

	/* Adjust ring index */
	wrt_reg_dword(ISP_ATIO_Q_OUT(vha), ha->tgt.atio_ring_index);
पूर्ण

व्योम
qlt_24xx_config_rings(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा qla_msix_entry *msix = &ha->msix_entries[2];
	काष्ठा init_cb_24xx *icb = (काष्ठा init_cb_24xx *)ha->init_cb;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	wrt_reg_dword(ISP_ATIO_Q_IN(vha), 0);
	wrt_reg_dword(ISP_ATIO_Q_OUT(vha), 0);
	rd_reg_dword(ISP_ATIO_Q_OUT(vha));

	अगर (ha->flags.msix_enabled) अणु
		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			अगर (IS_QLA2071(ha)) अणु
				/* 4 ports Baker: Enable Interrupt Handshake */
				icb->msix_atio = 0;
				icb->firmware_options_2 |= cpu_to_le32(BIT_26);
			पूर्ण अन्यथा अणु
				icb->msix_atio = cpu_to_le16(msix->entry);
				icb->firmware_options_2 &= cpu_to_le32(~BIT_26);
			पूर्ण
			ql_dbg(ql_dbg_init, vha, 0xf072,
			    "Registering ICB vector 0x%x for atio que.\n",
			    msix->entry);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* INTx|MSI */
		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			icb->msix_atio = 0;
			icb->firmware_options_2 |= cpu_to_le32(BIT_26);
			ql_dbg(ql_dbg_init, vha, 0xf072,
			    "%s: Use INTx for ATIOQ.\n", __func__);
		पूर्ण
	पूर्ण
पूर्ण

व्योम
qlt_24xx_config_nvram_stage1(काष्ठा scsi_qla_host *vha, काष्ठा nvram_24xx *nv)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	u32 पंचांगp;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	अगर (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha)) अणु
		अगर (!ha->tgt.saved_set) अणु
			/* We save only once */
			ha->tgt.saved_exchange_count = nv->exchange_count;
			ha->tgt.saved_firmware_options_1 =
			    nv->firmware_options_1;
			ha->tgt.saved_firmware_options_2 =
			    nv->firmware_options_2;
			ha->tgt.saved_firmware_options_3 =
			    nv->firmware_options_3;
			ha->tgt.saved_set = 1;
		पूर्ण

		अगर (qla_tgt_mode_enabled(vha))
			nv->exchange_count = cpu_to_le16(0xFFFF);
		अन्यथा			/* dual */
			nv->exchange_count = cpu_to_le16(vha->ql2xexchoffld);

		/* Enable target mode */
		nv->firmware_options_1 |= cpu_to_le32(BIT_4);

		/* Disable ini mode, अगर requested */
		अगर (qla_tgt_mode_enabled(vha))
			nv->firmware_options_1 |= cpu_to_le32(BIT_5);

		/* Disable Full Login after LIP */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_13);
		/* Enable initial LIP */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_9);
		अगर (ql2xtgt_tape_enable)
			/* Enable FC Tape support */
			nv->firmware_options_2 |= cpu_to_le32(BIT_12);
		अन्यथा
			/* Disable FC Tape support */
			nv->firmware_options_2 &= cpu_to_le32(~BIT_12);

		/* Disable Full Login after LIP */
		nv->host_p &= cpu_to_le32(~BIT_10);

		/*
		 * clear BIT 15 explicitly as we have seen at least
		 * a couple of instances where this was set and this
		 * was causing the firmware to not be initialized.
		 */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_15);
		/* Enable target PRLI control */
		nv->firmware_options_2 |= cpu_to_le32(BIT_14);

		अगर (IS_QLA25XX(ha)) अणु
			/* Change Loop-prefer to Pt-Pt */
			पंचांगp = ~(BIT_4|BIT_5|BIT_6);
			nv->firmware_options_2 &= cpu_to_le32(पंचांगp);
			पंचांगp = P2P << 4;
			nv->firmware_options_2 |= cpu_to_le32(पंचांगp);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ha->tgt.saved_set) अणु
			nv->exchange_count = ha->tgt.saved_exchange_count;
			nv->firmware_options_1 =
			    ha->tgt.saved_firmware_options_1;
			nv->firmware_options_2 =
			    ha->tgt.saved_firmware_options_2;
			nv->firmware_options_3 =
			    ha->tgt.saved_firmware_options_3;
		पूर्ण
		वापस;
	पूर्ण

	अगर (ha->base_qpair->enable_class_2) अणु
		अगर (vha->flags.init_करोne)
			fc_host_supported_classes(vha->host) =
				FC_COS_CLASS2 | FC_COS_CLASS3;

		nv->firmware_options_2 |= cpu_to_le32(BIT_8);
	पूर्ण अन्यथा अणु
		अगर (vha->flags.init_करोne)
			fc_host_supported_classes(vha->host) = FC_COS_CLASS3;

		nv->firmware_options_2 &= ~cpu_to_le32(BIT_8);
	पूर्ण
पूर्ण

व्योम
qlt_24xx_config_nvram_stage2(काष्ठा scsi_qla_host *vha,
	काष्ठा init_cb_24xx *icb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	अगर (ha->tgt.node_name_set) अणु
		स_नकल(icb->node_name, ha->tgt.tgt_node_name, WWN_SIZE);
		icb->firmware_options_1 |= cpu_to_le32(BIT_14);
	पूर्ण
पूर्ण

व्योम
qlt_81xx_config_nvram_stage1(काष्ठा scsi_qla_host *vha, काष्ठा nvram_81xx *nv)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	u32 पंचांगp;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	अगर (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha)) अणु
		अगर (!ha->tgt.saved_set) अणु
			/* We save only once */
			ha->tgt.saved_exchange_count = nv->exchange_count;
			ha->tgt.saved_firmware_options_1 =
			    nv->firmware_options_1;
			ha->tgt.saved_firmware_options_2 =
			    nv->firmware_options_2;
			ha->tgt.saved_firmware_options_3 =
			    nv->firmware_options_3;
			ha->tgt.saved_set = 1;
		पूर्ण

		अगर (qla_tgt_mode_enabled(vha))
			nv->exchange_count = cpu_to_le16(0xFFFF);
		अन्यथा			/* dual */
			nv->exchange_count = cpu_to_le16(vha->ql2xexchoffld);

		/* Enable target mode */
		nv->firmware_options_1 |= cpu_to_le32(BIT_4);

		/* Disable ini mode, अगर requested */
		अगर (qla_tgt_mode_enabled(vha))
			nv->firmware_options_1 |= cpu_to_le32(BIT_5);
		/* Disable Full Login after LIP */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_13);
		/* Enable initial LIP */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_9);
		/*
		 * clear BIT 15 explicitly as we have seen at
		 * least a couple of instances where this was set
		 * and this was causing the firmware to not be
		 * initialized.
		 */
		nv->firmware_options_1 &= cpu_to_le32(~BIT_15);
		अगर (ql2xtgt_tape_enable)
			/* Enable FC tape support */
			nv->firmware_options_2 |= cpu_to_le32(BIT_12);
		अन्यथा
			/* Disable FC tape support */
			nv->firmware_options_2 &= cpu_to_le32(~BIT_12);

		/* Disable Full Login after LIP */
		nv->host_p &= cpu_to_le32(~BIT_10);
		/* Enable target PRLI control */
		nv->firmware_options_2 |= cpu_to_le32(BIT_14);

		/* Change Loop-prefer to Pt-Pt */
		पंचांगp = ~(BIT_4|BIT_5|BIT_6);
		nv->firmware_options_2 &= cpu_to_le32(पंचांगp);
		पंचांगp = P2P << 4;
		nv->firmware_options_2 |= cpu_to_le32(पंचांगp);
	पूर्ण अन्यथा अणु
		अगर (ha->tgt.saved_set) अणु
			nv->exchange_count = ha->tgt.saved_exchange_count;
			nv->firmware_options_1 =
			    ha->tgt.saved_firmware_options_1;
			nv->firmware_options_2 =
			    ha->tgt.saved_firmware_options_2;
			nv->firmware_options_3 =
			    ha->tgt.saved_firmware_options_3;
		पूर्ण
		वापस;
	पूर्ण

	अगर (ha->base_qpair->enable_class_2) अणु
		अगर (vha->flags.init_करोne)
			fc_host_supported_classes(vha->host) =
				FC_COS_CLASS2 | FC_COS_CLASS3;

		nv->firmware_options_2 |= cpu_to_le32(BIT_8);
	पूर्ण अन्यथा अणु
		अगर (vha->flags.init_करोne)
			fc_host_supported_classes(vha->host) = FC_COS_CLASS3;

		nv->firmware_options_2 &= ~cpu_to_le32(BIT_8);
	पूर्ण
पूर्ण

व्योम
qlt_81xx_config_nvram_stage2(काष्ठा scsi_qla_host *vha,
	काष्ठा init_cb_81xx *icb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	अगर (ha->tgt.node_name_set) अणु
		स_नकल(icb->node_name, ha->tgt.tgt_node_name, WWN_SIZE);
		icb->firmware_options_1 |= cpu_to_le32(BIT_14);
	पूर्ण
पूर्ण

व्योम
qlt_83xx_iospace_config(काष्ठा qla_hw_data *ha)
अणु
	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	ha->msix_count += 1; /* For ATIO Q */
पूर्ण


व्योम
qlt_modअगरy_vp_config(काष्ठा scsi_qla_host *vha,
	काष्ठा vp_config_entry_24xx *vpmod)
अणु
	/* enable target mode.  Bit5 = 1 => disable */
	अगर (qla_tgt_mode_enabled(vha) || qla_dual_mode_enabled(vha))
		vpmod->options_idx1 &= ~BIT_5;

	/* Disable ini mode, अगर requested.  bit4 = 1 => disable */
	अगर (qla_tgt_mode_enabled(vha))
		vpmod->options_idx1 &= ~BIT_4;
पूर्ण

व्योम
qlt_probe_one_stage1(काष्ठा scsi_qla_host *base_vha, काष्ठा qla_hw_data *ha)
अणु
	पूर्णांक rc;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	अगर  ((ql2xenablemsix == 0) || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) अणु
		ISP_ATIO_Q_IN(base_vha) = &ha->mqiobase->isp25mq.atio_q_in;
		ISP_ATIO_Q_OUT(base_vha) = &ha->mqiobase->isp25mq.atio_q_out;
	पूर्ण अन्यथा अणु
		ISP_ATIO_Q_IN(base_vha) = &ha->iobase->isp24.atio_q_in;
		ISP_ATIO_Q_OUT(base_vha) = &ha->iobase->isp24.atio_q_out;
	पूर्ण

	mutex_init(&base_vha->vha_tgt.tgt_mutex);
	mutex_init(&base_vha->vha_tgt.tgt_host_action_mutex);

	INIT_LIST_HEAD(&base_vha->unknown_atio_list);
	INIT_DELAYED_WORK(&base_vha->unknown_atio_work,
	    qlt_unknown_atio_work_fn);

	qlt_clear_mode(base_vha);

	rc = btree_init32(&ha->tgt.host_map);
	अगर (rc)
		ql_log(ql_log_info, base_vha, 0xd03d,
		    "Unable to initialize ha->host_map btree\n");

	qlt_update_vp_map(base_vha, SET_VP_IDX);
पूर्ण

irqवापस_t
qla83xx_msix_atio_q(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rsp_que *rsp;
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	अचिन्हित दीर्घ flags;

	rsp = (काष्ठा rsp_que *) dev_id;
	ha = rsp->hw;
	vha = pci_get_drvdata(ha->pdev);

	spin_lock_irqsave(&ha->tgt.atio_lock, flags);

	qlt_24xx_process_atio_queue(vha, 0);

	spin_unlock_irqrestore(&ha->tgt.atio_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम
qlt_handle_abts_recv_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qla_tgt_sess_op *op = container_of(work,
		काष्ठा qla_tgt_sess_op, work);
	scsi_qla_host_t *vha = op->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ flags;

	अगर (qla2x00_reset_active(vha) ||
	    (op->chip_reset != ha->base_qpair->chip_reset))
		वापस;

	spin_lock_irqsave(&ha->tgt.atio_lock, flags);
	qlt_24xx_process_atio_queue(vha, 0);
	spin_unlock_irqrestore(&ha->tgt.atio_lock, flags);

	spin_lock_irqsave(&ha->hardware_lock, flags);
	qlt_response_pkt_all_vps(vha, op->rsp, (response_t *)&op->atio);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	kमुक्त(op);
पूर्ण

व्योम
qlt_handle_abts_recv(काष्ठा scsi_qla_host *vha, काष्ठा rsp_que *rsp,
    response_t *pkt)
अणु
	काष्ठा qla_tgt_sess_op *op;

	op = kzalloc(माप(*op), GFP_ATOMIC);

	अगर (!op) अणु
		/* करो not reach क्रम ATIO queue here.  This is best efक्रमt err
		 * recovery at this poपूर्णांक.
		 */
		qlt_response_pkt_all_vps(vha, rsp, pkt);
		वापस;
	पूर्ण

	स_नकल(&op->atio, pkt, माप(*pkt));
	op->vha = vha;
	op->chip_reset = vha->hw->base_qpair->chip_reset;
	op->rsp = rsp;
	INIT_WORK(&op->work, qlt_handle_abts_recv_work);
	queue_work(qla_tgt_wq, &op->work);
	वापस;
पूर्ण

पूर्णांक
qlt_mem_alloc(काष्ठा qla_hw_data *ha)
अणु
	अगर (!QLA_TGT_MODE_ENABLED())
		वापस 0;

	ha->tgt.tgt_vp_map = kसुस्मृति(MAX_MULTI_ID_FABRIC,
				     माप(काष्ठा qla_tgt_vp_map),
				     GFP_KERNEL);
	अगर (!ha->tgt.tgt_vp_map)
		वापस -ENOMEM;

	ha->tgt.atio_ring = dma_alloc_coherent(&ha->pdev->dev,
	    (ha->tgt.atio_q_length + 1) * माप(काष्ठा atio_from_isp),
	    &ha->tgt.atio_dma, GFP_KERNEL);
	अगर (!ha->tgt.atio_ring) अणु
		kमुक्त(ha->tgt.tgt_vp_map);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम
qlt_mem_मुक्त(काष्ठा qla_hw_data *ha)
अणु
	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	अगर (ha->tgt.atio_ring) अणु
		dma_मुक्त_coherent(&ha->pdev->dev, (ha->tgt.atio_q_length + 1) *
		    माप(काष्ठा atio_from_isp), ha->tgt.atio_ring,
		    ha->tgt.atio_dma);
	पूर्ण
	ha->tgt.atio_ring = शून्य;
	ha->tgt.atio_dma = 0;
	kमुक्त(ha->tgt.tgt_vp_map);
	ha->tgt.tgt_vp_map = शून्य;
पूर्ण

/* vport_slock to be held by the caller */
व्योम
qlt_update_vp_map(काष्ठा scsi_qla_host *vha, पूर्णांक cmd)
अणु
	व्योम *slot;
	u32 key;
	पूर्णांक rc;

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	key = vha->d_id.b24;

	चयन (cmd) अणु
	हाल SET_VP_IDX:
		vha->hw->tgt.tgt_vp_map[vha->vp_idx].vha = vha;
		अवरोध;
	हाल SET_AL_PA:
		slot = btree_lookup32(&vha->hw->tgt.host_map, key);
		अगर (!slot) अणु
			ql_dbg(ql_dbg_tgt_mgt, vha, 0xf018,
			    "Save vha in host_map %p %06x\n", vha, key);
			rc = btree_insert32(&vha->hw->tgt.host_map,
				key, vha, GFP_ATOMIC);
			अगर (rc)
				ql_log(ql_log_info, vha, 0xd03e,
				    "Unable to insert s_id into host_map: %06x\n",
				    key);
			वापस;
		पूर्ण
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf019,
		    "replace existing vha in host_map %p %06x\n", vha, key);
		btree_update32(&vha->hw->tgt.host_map, key, vha);
		अवरोध;
	हाल RESET_VP_IDX:
		vha->hw->tgt.tgt_vp_map[vha->vp_idx].vha = शून्य;
		अवरोध;
	हाल RESET_AL_PA:
		ql_dbg(ql_dbg_tgt_mgt, vha, 0xf01a,
		   "clear vha in host_map %p %06x\n", vha, key);
		slot = btree_lookup32(&vha->hw->tgt.host_map, key);
		अगर (slot)
			btree_हटाओ32(&vha->hw->tgt.host_map, key);
		vha->d_id.b24 = 0;
		अवरोध;
	पूर्ण
पूर्ण

व्योम qlt_update_host_map(काष्ठा scsi_qla_host *vha, port_id_t id)
अणु

	अगर (!vha->d_id.b24) अणु
		vha->d_id = id;
		qlt_update_vp_map(vha, SET_AL_PA);
	पूर्ण अन्यथा अगर (vha->d_id.b24 != id.b24) अणु
		qlt_update_vp_map(vha, RESET_AL_PA);
		vha->d_id = id;
		qlt_update_vp_map(vha, SET_AL_PA);
	पूर्ण
पूर्ण

अटल पूर्णांक __init qlt_parse_ini_mode(व्योम)
अणु
	अगर (strहालcmp(qlini_mode, QLA2XXX_INI_MODE_STR_EXCLUSIVE) == 0)
		ql2x_ini_mode = QLA2XXX_INI_MODE_EXCLUSIVE;
	अन्यथा अगर (strहालcmp(qlini_mode, QLA2XXX_INI_MODE_STR_DISABLED) == 0)
		ql2x_ini_mode = QLA2XXX_INI_MODE_DISABLED;
	अन्यथा अगर (strहालcmp(qlini_mode, QLA2XXX_INI_MODE_STR_ENABLED) == 0)
		ql2x_ini_mode = QLA2XXX_INI_MODE_ENABLED;
	अन्यथा अगर (strहालcmp(qlini_mode, QLA2XXX_INI_MODE_STR_DUAL) == 0)
		ql2x_ini_mode = QLA2XXX_INI_MODE_DUAL;
	अन्यथा
		वापस false;

	वापस true;
पूर्ण

पूर्णांक __init qlt_init(व्योम)
अणु
	पूर्णांक ret;

	BUILD_BUG_ON(माप(काष्ठा ctio7_to_24xx) != 64);
	BUILD_BUG_ON(माप(काष्ठा ctio_to_2xxx) != 64);

	अगर (!qlt_parse_ini_mode()) अणु
		ql_log(ql_log_fatal, शून्य, 0xe06b,
		    "qlt_parse_ini_mode() failed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!QLA_TGT_MODE_ENABLED())
		वापस 0;

	qla_tgt_mgmt_cmd_cachep = kmem_cache_create("qla_tgt_mgmt_cmd_cachep",
	    माप(काष्ठा qla_tgt_mgmt_cmd), __alignof__(काष्ठा
	    qla_tgt_mgmt_cmd), 0, शून्य);
	अगर (!qla_tgt_mgmt_cmd_cachep) अणु
		ql_log(ql_log_fatal, शून्य, 0xd04b,
		    "kmem_cache_create for qla_tgt_mgmt_cmd_cachep failed\n");
		वापस -ENOMEM;
	पूर्ण

	qla_tgt_plogi_cachep = kmem_cache_create("qla_tgt_plogi_cachep",
	    माप(काष्ठा qlt_plogi_ack_t), __alignof__(काष्ठा qlt_plogi_ack_t),
	    0, शून्य);

	अगर (!qla_tgt_plogi_cachep) अणु
		ql_log(ql_log_fatal, शून्य, 0xe06d,
		    "kmem_cache_create for qla_tgt_plogi_cachep failed\n");
		ret = -ENOMEM;
		जाओ out_mgmt_cmd_cachep;
	पूर्ण

	qla_tgt_mgmt_cmd_mempool = mempool_create(25, mempool_alloc_slab,
	    mempool_मुक्त_slab, qla_tgt_mgmt_cmd_cachep);
	अगर (!qla_tgt_mgmt_cmd_mempool) अणु
		ql_log(ql_log_fatal, शून्य, 0xe06e,
		    "mempool_create for qla_tgt_mgmt_cmd_mempool failed\n");
		ret = -ENOMEM;
		जाओ out_plogi_cachep;
	पूर्ण

	qla_tgt_wq = alloc_workqueue("qla_tgt_wq", 0, 0);
	अगर (!qla_tgt_wq) अणु
		ql_log(ql_log_fatal, शून्य, 0xe06f,
		    "alloc_workqueue for qla_tgt_wq failed\n");
		ret = -ENOMEM;
		जाओ out_cmd_mempool;
	पूर्ण
	/*
	 * Return 1 to संकेत that initiator-mode is being disabled
	 */
	वापस (ql2x_ini_mode == QLA2XXX_INI_MODE_DISABLED) ? 1 : 0;

out_cmd_mempool:
	mempool_destroy(qla_tgt_mgmt_cmd_mempool);
out_plogi_cachep:
	kmem_cache_destroy(qla_tgt_plogi_cachep);
out_mgmt_cmd_cachep:
	kmem_cache_destroy(qla_tgt_mgmt_cmd_cachep);
	वापस ret;
पूर्ण

व्योम qlt_निकास(व्योम)
अणु
	अगर (!QLA_TGT_MODE_ENABLED())
		वापस;

	destroy_workqueue(qla_tgt_wq);
	mempool_destroy(qla_tgt_mgmt_cmd_mempool);
	kmem_cache_destroy(qla_tgt_plogi_cachep);
	kmem_cache_destroy(qla_tgt_mgmt_cmd_cachep);
पूर्ण
