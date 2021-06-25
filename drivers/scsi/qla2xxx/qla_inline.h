<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */

#समावेश "qla_target.h"
/**
 * qla24xx_calc_iocbs() - Determine number of Command Type 3 and
 * Continuation Type 1 IOCBs to allocate.
 *
 * @vha: HA context
 * @dsds: number of data segment descriptors needed
 *
 * Returns the number of IOCB entries needed to store @dsds.
 */
अटल अंतरभूत uपूर्णांक16_t
qla24xx_calc_iocbs(scsi_qla_host_t *vha, uपूर्णांक16_t dsds)
अणु
	uपूर्णांक16_t iocbs;

	iocbs = 1;
	अगर (dsds > 1) अणु
		iocbs += (dsds - 1) / 5;
		अगर ((dsds - 1) % 5)
			iocbs++;
	पूर्ण
	वापस iocbs;
पूर्ण

/*
 * qla2x00_debounce_रेजिस्टर
 *      Debounce रेजिस्टर.
 *
 * Input:
 *      port = रेजिस्टर address.
 *
 * Returns:
 *      रेजिस्टर value.
 */
अटल __अंतरभूत__ uपूर्णांक16_t
qla2x00_debounce_रेजिस्टर(अस्थिर __le16 __iomem *addr)
अणु
	अस्थिर uपूर्णांक16_t first;
	अस्थिर uपूर्णांक16_t second;

	करो अणु
		first = rd_reg_word(addr);
		barrier();
		cpu_relax();
		second = rd_reg_word(addr);
	पूर्ण जबतक (first != second);

	वापस (first);
पूर्ण

अटल अंतरभूत व्योम
qla2x00_poll(काष्ठा rsp_que *rsp)
अणु
	काष्ठा qla_hw_data *ha = rsp->hw;

	अगर (IS_P3P_TYPE(ha))
		qla82xx_poll(0, rsp);
	अन्यथा
		ha->isp_ops->पूर्णांकr_handler(0, rsp);
पूर्ण

अटल अंतरभूत uपूर्णांक8_t *
host_to_fcp_swap(uपूर्णांक8_t *fcp, uपूर्णांक32_t bsize)
अणु
       uपूर्णांक32_t *अगरcp = (uपूर्णांक32_t *) fcp;
       uपूर्णांक32_t *ofcp = (uपूर्णांक32_t *) fcp;
       uपूर्णांक32_t iter = bsize >> 2;

       क्रम (; iter ; iter--)
               *ofcp++ = swab32(*अगरcp++);

       वापस fcp;
पूर्ण

अटल अंतरभूत व्योम
host_to_adap(uपूर्णांक8_t *src, uपूर्णांक8_t *dst, uपूर्णांक32_t bsize)
अणु
	uपूर्णांक32_t *isrc = (uपूर्णांक32_t *) src;
	__le32 *odest = (__le32 *) dst;
	uपूर्णांक32_t iter = bsize >> 2;

	क्रम ( ; iter--; isrc++)
		*odest++ = cpu_to_le32(*isrc);
पूर्ण

अटल अंतरभूत व्योम
qla2x00_clean_dsd_pool(काष्ठा qla_hw_data *ha, काष्ठा crc_context *ctx)
अणु
	काष्ठा dsd_dma *dsd, *tdsd;

	/* clean up allocated prev pool */
	list_क्रम_each_entry_safe(dsd, tdsd, &ctx->dsd_list, list) अणु
		dma_pool_मुक्त(ha->dl_dma_pool, dsd->dsd_addr,
		    dsd->dsd_list_dma);
		list_del(&dsd->list);
		kमुक्त(dsd);
	पूर्ण
	INIT_LIST_HEAD(&ctx->dsd_list);
पूर्ण

अटल अंतरभूत व्योम
qla2x00_set_fcport_disc_state(fc_port_t *fcport, पूर्णांक state)
अणु
	पूर्णांक old_val;
	uपूर्णांक8_t shअगरtbits, mask;

	/* This will have to change when the max no. of states > 16 */
	shअगरtbits = 4;
	mask = (1 << shअगरtbits) - 1;

	fcport->disc_state = state;
	जबतक (1) अणु
		old_val = atomic_पढ़ो(&fcport->shaकरोw_disc_state);
		अगर (old_val == atomic_cmpxchg(&fcport->shaकरोw_disc_state,
		    old_val, (old_val << shअगरtbits) | state)) अणु
			ql_dbg(ql_dbg_disc, fcport->vha, 0x2134,
			    "FCPort %8phC disc_state transition: %s to %s - portid=%06x.\n",
			    fcport->port_name, port_dstate_str[old_val & mask],
			    port_dstate_str[state], fcport->d_id.b24);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
qla2x00_hba_err_chk_enabled(srb_t *sp)
अणु
	/*
	 * Uncomment when corresponding SCSI changes are करोne.
	 *
	अगर (!sp->cmd->prot_chk)
		वापस 0;
	 *
	 */
	चयन (scsi_get_prot_op(GET_CMD_SP(sp))) अणु
	हाल SCSI_PROT_READ_STRIP:
	हाल SCSI_PROT_WRITE_INSERT:
		अगर (ql2xenablehba_err_chk >= 1)
			वापस 1;
		अवरोध;
	हाल SCSI_PROT_READ_PASS:
	हाल SCSI_PROT_WRITE_PASS:
		अगर (ql2xenablehba_err_chk >= 2)
			वापस 1;
		अवरोध;
	हाल SCSI_PROT_READ_INSERT:
	हाल SCSI_PROT_WRITE_STRIP:
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक
qla2x00_reset_active(scsi_qla_host_t *vha)
अणु
	scsi_qla_host_t *base_vha = pci_get_drvdata(vha->hw->pdev);

	/* Test appropriate base-vha and vha flags. */
	वापस test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags) ||
	    test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags) ||
	    test_bit(ISP_ABORT_RETRY, &base_vha->dpc_flags) ||
	    test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) ||
	    test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags);
पूर्ण

अटल अंतरभूत पूर्णांक
qla2x00_chip_is_करोwn(scsi_qla_host_t *vha)
अणु
	वापस (qla2x00_reset_active(vha) || !vha->hw->flags.fw_started);
पूर्ण

अटल व्योम qla2xxx_init_sp(srb_t *sp, scsi_qla_host_t *vha,
			    काष्ठा qla_qpair *qpair, fc_port_t *fcport)
अणु
	स_रखो(sp, 0, माप(*sp));
	sp->fcport = fcport;
	sp->iocbs = 1;
	sp->vha = vha;
	sp->qpair = qpair;
	sp->cmd_type = TYPE_SRB;
	INIT_LIST_HEAD(&sp->elem);
पूर्ण

अटल अंतरभूत srb_t *
qla2xxx_get_qpair_sp(scsi_qla_host_t *vha, काष्ठा qla_qpair *qpair,
    fc_port_t *fcport, gfp_t flag)
अणु
	srb_t *sp = शून्य;
	uपूर्णांक8_t bail;

	QLA_QPAIR_MARK_BUSY(qpair, bail);
	अगर (unlikely(bail))
		वापस शून्य;

	sp = mempool_alloc(qpair->srb_mempool, flag);
	अगर (sp)
		qla2xxx_init_sp(sp, vha, qpair, fcport);
	अन्यथा
		QLA_QPAIR_MARK_NOT_BUSY(qpair);
	वापस sp;
पूर्ण

व्योम qla2xxx_rel_करोne_warning(srb_t *sp, पूर्णांक res);
व्योम qla2xxx_rel_मुक्त_warning(srb_t *sp);

अटल अंतरभूत व्योम
qla2xxx_rel_qpair_sp(काष्ठा qla_qpair *qpair, srb_t *sp)
अणु
	sp->qpair = शून्य;
	sp->करोne = qla2xxx_rel_करोne_warning;
	sp->मुक्त = qla2xxx_rel_मुक्त_warning;
	mempool_मुक्त(sp, qpair->srb_mempool);
	QLA_QPAIR_MARK_NOT_BUSY(qpair);
पूर्ण

अटल अंतरभूत srb_t *
qla2x00_get_sp(scsi_qla_host_t *vha, fc_port_t *fcport, gfp_t flag)
अणु
	srb_t *sp = शून्य;
	uपूर्णांक8_t bail;
	काष्ठा qla_qpair *qpair;

	QLA_VHA_MARK_BUSY(vha, bail);
	अगर (unlikely(bail))
		वापस शून्य;

	qpair = vha->hw->base_qpair;
	sp = qla2xxx_get_qpair_sp(vha, qpair, fcport, flag);
	अगर (!sp)
		जाओ करोne;

	sp->vha = vha;
करोne:
	अगर (!sp)
		QLA_VHA_MARK_NOT_BUSY(vha);
	वापस sp;
पूर्ण

अटल अंतरभूत व्योम
qla2x00_rel_sp(srb_t *sp)
अणु
	QLA_VHA_MARK_NOT_BUSY(sp->vha);
	qla2xxx_rel_qpair_sp(sp->qpair, sp);
पूर्ण

अटल अंतरभूत पूर्णांक
qla2x00_gid_list_size(काष्ठा qla_hw_data *ha)
अणु
	अगर (IS_QLAFX00(ha))
		वापस माप(uपूर्णांक32_t) * 32;
	अन्यथा
		वापस माप(काष्ठा gid_list_info) * ha->max_fibre_devices;
पूर्ण

अटल अंतरभूत व्योम
qla2x00_handle_mbx_completion(काष्ठा qla_hw_data *ha, पूर्णांक status)
अणु
	अगर (test_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags) &&
	    (status & MBX_INTERRUPT) && ha->flags.mbox_पूर्णांक) अणु
		set_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);
		clear_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags);
		complete(&ha->mbx_पूर्णांकr_comp);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qla2x00_set_retry_delay_बारtamp(fc_port_t *fcport, uपूर्णांक16_t sts_qual)
अणु
	u8 scope;
	u16 qual;
#घोषणा SQ_SCOPE_MASK		0xc000 /* SAM-6 rev5 5.3.2 */
#घोषणा SQ_SCOPE_SHIFT		14
#घोषणा SQ_QUAL_MASK		0x3fff

#घोषणा SQ_MAX_WAIT_SEC		60 /* Max I/O hold off समय in seconds. */
#घोषणा SQ_MAX_WAIT_TIME	(SQ_MAX_WAIT_SEC * 10) /* in 100ms. */

	अगर (!sts_qual) /* Common हाल. */
		वापस;

	scope = (sts_qual & SQ_SCOPE_MASK) >> SQ_SCOPE_SHIFT;
	/* Handle only scope 1 or 2, which is क्रम I-T nexus. */
	अगर (scope != 1 && scope != 2)
		वापस;

	/* Skip processing, अगर retry delay समयr is alपढ़ोy in effect. */
	अगर (fcport->retry_delay_बारtamp &&
	    समय_beक्रमe(jअगरfies, fcport->retry_delay_बारtamp))
		वापस;

	qual = sts_qual & SQ_QUAL_MASK;
	अगर (qual < 1 || qual > 0x3fef)
		वापस;
	qual = min(qual, (u16)SQ_MAX_WAIT_TIME);

	/* qual is expressed in 100ms increments. */
	fcport->retry_delay_बारtamp = jअगरfies + (qual * HZ / 10);

	ql_log(ql_log_warn, fcport->vha, 0x5101,
	       "%8phC: I/O throttling requested (status qualifier = %04xh), holding off I/Os for %ums.\n",
	       fcport->port_name, sts_qual, qual * 100);
पूर्ण

अटल अंतरभूत bool
qla_is_exch_offld_enabled(काष्ठा scsi_qla_host *vha)
अणु
	अगर (qla_ini_mode_enabled(vha) &&
	    (vha->ql2xiniexchg > FW_DEF_EXCHANGES_CNT))
		वापस true;
	अन्यथा अगर (qla_tgt_mode_enabled(vha) &&
	    (vha->ql2xexchoffld > FW_DEF_EXCHANGES_CNT))
		वापस true;
	अन्यथा अगर (qla_dual_mode_enabled(vha) &&
	    ((vha->ql2xiniexchg + vha->ql2xexchoffld) > FW_DEF_EXCHANGES_CNT))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल अंतरभूत व्योम
qla_cpu_update(काष्ठा qla_qpair *qpair, uपूर्णांक16_t cpuid)
अणु
	qpair->cpuid = cpuid;

	अगर (!list_empty(&qpair->hपूर्णांकs_list)) अणु
		काष्ठा qla_qpair_hपूर्णांक *h;

		list_क्रम_each_entry(h, &qpair->hपूर्णांकs_list, hपूर्णांक_elem)
			h->cpuid = qpair->cpuid;
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा qla_qpair_hपूर्णांक *
qla_qpair_to_hपूर्णांक(काष्ठा qla_tgt *tgt, काष्ठा qla_qpair *qpair)
अणु
	काष्ठा qla_qpair_hपूर्णांक *h;
	u16 i;

	क्रम (i = 0; i < tgt->ha->max_qpairs + 1; i++) अणु
		h = &tgt->qphपूर्णांकs[i];
		अगर (h->qpair == qpair)
			वापस h;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम
qla_83xx_start_iocbs(काष्ठा qla_qpair *qpair)
अणु
	काष्ठा req_que *req = qpair->req;

	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	wrt_reg_dword(req->req_q_in, req->ring_index);
पूर्ण

अटल अंतरभूत पूर्णांक
qla2xxx_get_fc4_priority(काष्ठा scsi_qla_host *vha)
अणु
	uपूर्णांक32_t data;

	data =
	    ((uपूर्णांक8_t *)vha->hw->nvram)[NVRAM_DUAL_FCP_NVME_FLAG_OFFSET];


	वापस (data >> 6) & BIT_0 ? FC4_PRIORITY_FCP : FC4_PRIORITY_NVME;
पूर्ण

क्रमागत अणु
	RESOURCE_NONE,
	RESOURCE_INI,
पूर्ण;

अटल अंतरभूत पूर्णांक
qla_get_iocbs(काष्ठा qla_qpair *qp, काष्ठा iocb_resource *iores)
अणु
	u16 iocbs_used, i;
	काष्ठा qla_hw_data *ha = qp->vha->hw;

	अगर (!ql2xenक्रमce_iocb_limit) अणु
		iores->res_type = RESOURCE_NONE;
		वापस 0;
	पूर्ण

	अगर ((iores->iocb_cnt + qp->fwres.iocbs_used) < qp->fwres.iocbs_qp_limit) अणु
		qp->fwres.iocbs_used += iores->iocb_cnt;
		वापस 0;
	पूर्ण अन्यथा अणु
		/* no need to acquire qpair lock. It's just rough calculation */
		iocbs_used = ha->base_qpair->fwres.iocbs_used;
		क्रम (i = 0; i < ha->max_qpairs; i++) अणु
			अगर (ha->queue_pair_map[i])
				iocbs_used += ha->queue_pair_map[i]->fwres.iocbs_used;
		पूर्ण

		अगर ((iores->iocb_cnt + iocbs_used) < qp->fwres.iocbs_limit) अणु
			qp->fwres.iocbs_used += iores->iocb_cnt;
			वापस 0;
		पूर्ण अन्यथा अणु
			iores->res_type = RESOURCE_NONE;
			वापस -ENOSPC;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
qla_put_iocbs(काष्ठा qla_qpair *qp, काष्ठा iocb_resource *iores)
अणु
	चयन (iores->res_type) अणु
	हाल RESOURCE_NONE:
		अवरोध;
	शेष:
		अगर (qp->fwres.iocbs_used >= iores->iocb_cnt) अणु
			qp->fwres.iocbs_used -= iores->iocb_cnt;
		पूर्ण अन्यथा अणु
			// should not happen
			qp->fwres.iocbs_used = 0;
		पूर्ण
		अवरोध;
	पूर्ण
	iores->res_type = RESOURCE_NONE;
पूर्ण

#घोषणा ISP_REG_DISCONNECT 0xffffffffU
/**************************************************************************
 * qla2x00_isp_reg_stat
 *
 * Description:
 *        Read the host status रेजिस्टर of ISP beक्रमe पातing the command.
 *
 * Input:
 *       ha = poपूर्णांकer to host adapter काष्ठाure.
 *
 *
 * Returns:
 *       Either true or false.
 *
 * Note: Return true अगर there is रेजिस्टर disconnect.
 **************************************************************************/
अटल अंतरभूत
uपूर्णांक32_t qla2x00_isp_reg_stat(काष्ठा qla_hw_data *ha)
अणु
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;
	काष्ठा device_reg_82xx __iomem *reg82 = &ha->iobase->isp82;

	अगर (IS_P3P_TYPE(ha))
		वापस ((rd_reg_dword(&reg82->host_पूर्णांक)) == ISP_REG_DISCONNECT);
	अन्यथा
		वापस ((rd_reg_dword(&reg->host_status)) ==
			ISP_REG_DISCONNECT);
पूर्ण

अटल अंतरभूत
bool qla_pci_disconnected(काष्ठा scsi_qla_host *vha,
			  काष्ठा device_reg_24xx __iomem *reg)
अणु
	uपूर्णांक32_t stat;
	bool ret = false;

	stat = rd_reg_dword(&reg->host_status);
	अगर (stat == 0xffffffff) अणु
		ql_log(ql_log_info, vha, 0x8041,
		       "detected PCI disconnect.\n");
		qla_schedule_eeh_work(vha);
		ret = true;
	पूर्ण
	वापस ret;
पूर्ण
