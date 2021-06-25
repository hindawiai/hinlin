<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_target.h"
#समावेश "qla_gbl.h"

#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/cpu.h>
#समावेश <linux/t10-pi.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_bsg_fc.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/fc/fc_fs.h>
#समावेश <linux/nvme-fc-driver.h>

अटल व्योम qla2x00_mbx_completion(scsi_qla_host_t *, uपूर्णांक16_t);
अटल व्योम qla2x00_status_entry(scsi_qla_host_t *, काष्ठा rsp_que *, व्योम *);
अटल व्योम qla2x00_status_cont_entry(काष्ठा rsp_que *, sts_cont_entry_t *);
अटल पूर्णांक qla2x00_error_entry(scsi_qla_host_t *, काष्ठा rsp_que *,
	sts_entry_t *);
अटल व्योम qla27xx_process_purex_fpin(काष्ठा scsi_qla_host *vha,
	काष्ठा purex_item *item);
अटल काष्ठा purex_item *qla24xx_alloc_purex_item(scsi_qla_host_t *vha,
	uपूर्णांक16_t size);
अटल काष्ठा purex_item *qla24xx_copy_std_pkt(काष्ठा scsi_qla_host *vha,
	व्योम *pkt);
अटल काष्ठा purex_item *qla27xx_copy_fpin_pkt(काष्ठा scsi_qla_host *vha,
	व्योम **pkt, काष्ठा rsp_que **rsp);

अटल व्योम
qla27xx_process_purex_fpin(काष्ठा scsi_qla_host *vha, काष्ठा purex_item *item)
अणु
	व्योम *pkt = &item->iocb;
	uपूर्णांक16_t pkt_size = item->size;

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x508d,
	       "%s: Enter\n", __func__);

	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x508e,
	       "-------- ELS REQ -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x508f,
		       pkt, pkt_size);

	fc_host_fpin_rcv(vha->host, pkt_size, (अक्षर *)pkt);
पूर्ण

स्थिर अक्षर *स्थिर port_state_str[] = अणु
	"Unknown",
	"UNCONFIGURED",
	"DEAD",
	"LOST",
	"ONLINE"
पूर्ण;

अटल व्योम
qla24xx_process_abts(काष्ठा scsi_qla_host *vha, काष्ठा purex_item *pkt)
अणु
	काष्ठा abts_entry_24xx *abts =
	    (काष्ठा abts_entry_24xx *)&pkt->iocb;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा els_entry_24xx *rsp_els;
	काष्ठा abts_entry_24xx *abts_rsp;
	dma_addr_t dma;
	uपूर्णांक32_t fctl;
	पूर्णांक rval;

	ql_dbg(ql_dbg_init, vha, 0x0286, "%s: entered.\n", __func__);

	ql_log(ql_log_warn, vha, 0x0287,
	    "Processing ABTS xchg=%#x oxid=%#x rxid=%#x seqid=%#x seqcnt=%#x\n",
	    abts->rx_xch_addr_to_पात, abts->ox_id, abts->rx_id,
	    abts->seq_id, abts->seq_cnt);
	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x0287,
	    "-------- ABTS RCV -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x0287,
	    (uपूर्णांक8_t *)abts, माप(*abts));

	rsp_els = dma_alloc_coherent(&ha->pdev->dev, माप(*rsp_els), &dma,
	    GFP_KERNEL);
	अगर (!rsp_els) अणु
		ql_log(ql_log_warn, vha, 0x0287,
		    "Failed allocate dma buffer ABTS/ELS RSP.\n");
		वापस;
	पूर्ण

	/* terminate exchange */
	rsp_els->entry_type = ELS_IOCB_TYPE;
	rsp_els->entry_count = 1;
	rsp_els->nport_handle = cpu_to_le16(~0);
	rsp_els->rx_xchg_address = abts->rx_xch_addr_to_पात;
	rsp_els->control_flags = cpu_to_le16(EPD_RX_XCHG);
	ql_dbg(ql_dbg_init, vha, 0x0283,
	    "Sending ELS Response to terminate exchange %#x...\n",
	    abts->rx_xch_addr_to_पात);
	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x0283,
	    "-------- ELS RSP -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x0283,
	    (uपूर्णांक8_t *)rsp_els, माप(*rsp_els));
	rval = qla2x00_issue_iocb(vha, rsp_els, dma, 0);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0288,
		    "%s: iocb failed to execute -> %x\n", __func__, rval);
	पूर्ण अन्यथा अगर (rsp_els->comp_status) अणु
		ql_log(ql_log_warn, vha, 0x0289,
		    "%s: iocb failed to complete -> completion=%#x subcode=(%#x,%#x)\n",
		    __func__, rsp_els->comp_status,
		    rsp_els->error_subcode_1, rsp_els->error_subcode_2);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_init, vha, 0x028a,
		    "%s: abort exchange done.\n", __func__);
	पूर्ण

	/* send ABTS response */
	abts_rsp = (व्योम *)rsp_els;
	स_रखो(abts_rsp, 0, माप(*abts_rsp));
	abts_rsp->entry_type = ABTS_RSP_TYPE;
	abts_rsp->entry_count = 1;
	abts_rsp->nport_handle = abts->nport_handle;
	abts_rsp->vp_idx = abts->vp_idx;
	abts_rsp->sof_type = abts->sof_type & 0xf0;
	abts_rsp->rx_xch_addr = abts->rx_xch_addr;
	abts_rsp->d_id[0] = abts->s_id[0];
	abts_rsp->d_id[1] = abts->s_id[1];
	abts_rsp->d_id[2] = abts->s_id[2];
	abts_rsp->r_ctl = FC_ROUTING_BLD | FC_R_CTL_BLD_BA_ACC;
	abts_rsp->s_id[0] = abts->d_id[0];
	abts_rsp->s_id[1] = abts->d_id[1];
	abts_rsp->s_id[2] = abts->d_id[2];
	abts_rsp->cs_ctl = abts->cs_ctl;
	/* include flipping bit23 in fctl */
	fctl = ~(abts->f_ctl[2] | 0x7F) << 16 |
	    FC_F_CTL_LAST_SEQ | FC_F_CTL_END_SEQ | FC_F_CTL_SEQ_INIT;
	abts_rsp->f_ctl[0] = fctl >> 0 & 0xff;
	abts_rsp->f_ctl[1] = fctl >> 8 & 0xff;
	abts_rsp->f_ctl[2] = fctl >> 16 & 0xff;
	abts_rsp->type = FC_TYPE_BLD;
	abts_rsp->rx_id = abts->rx_id;
	abts_rsp->ox_id = abts->ox_id;
	abts_rsp->payload.ba_acc.पातed_rx_id = abts->rx_id;
	abts_rsp->payload.ba_acc.पातed_ox_id = abts->ox_id;
	abts_rsp->payload.ba_acc.high_seq_cnt = cpu_to_le16(~0);
	abts_rsp->rx_xch_addr_to_पात = abts->rx_xch_addr_to_पात;
	ql_dbg(ql_dbg_init, vha, 0x028b,
	    "Sending BA ACC response to ABTS %#x...\n",
	    abts->rx_xch_addr_to_पात);
	ql_dbg(ql_dbg_init + ql_dbg_verbose, vha, 0x028b,
	    "-------- ELS RSP -------\n");
	ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha, 0x028b,
	    (uपूर्णांक8_t *)abts_rsp, माप(*abts_rsp));
	rval = qla2x00_issue_iocb(vha, abts_rsp, dma, 0);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x028c,
		    "%s: iocb failed to execute -> %x\n", __func__, rval);
	पूर्ण अन्यथा अगर (abts_rsp->comp_status) अणु
		ql_log(ql_log_warn, vha, 0x028d,
		    "%s: iocb failed to complete -> completion=%#x subcode=(%#x,%#x)\n",
		    __func__, abts_rsp->comp_status,
		    abts_rsp->payload.error.subcode1,
		    abts_rsp->payload.error.subcode2);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_init, vha, 0x028ea,
		    "%s: done.\n", __func__);
	पूर्ण

	dma_मुक्त_coherent(&ha->pdev->dev, माप(*rsp_els), rsp_els, dma);
पूर्ण

/**
 * qla2100_पूर्णांकr_handler() - Process पूर्णांकerrupts क्रम the ISP2100 and ISP2200.
 * @irq: पूर्णांकerrupt number
 * @dev_id: SCSI driver HA context
 *
 * Called by प्रणाली whenever the host adapter generates an पूर्णांकerrupt.
 *
 * Returns handled flag.
 */
irqवापस_t
qla2100_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा device_reg_2xxx __iomem *reg;
	पूर्णांक		status;
	अचिन्हित दीर्घ	iter;
	uपूर्णांक16_t	hccr;
	uपूर्णांक16_t	mb[8];
	काष्ठा rsp_que *rsp;
	अचिन्हित दीर्घ	flags;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0x505d,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस (IRQ_NONE);
	पूर्ण

	ha = rsp->hw;
	reg = &ha->iobase->isp;
	status = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	क्रम (iter = 50; iter--; ) अणु
		hccr = rd_reg_word(&reg->hccr);
		अगर (qla2x00_check_reg16_क्रम_disconnect(vha, hccr))
			अवरोध;
		अगर (hccr & HCCR_RISC_PAUSE) अणु
			अगर (pci_channel_offline(ha->pdev))
				अवरोध;

			/*
			 * Issue a "HARD" reset in order क्रम the RISC पूर्णांकerrupt
			 * bit to be cleared.  Schedule a big hammer to get
			 * out of the RISC PAUSED state.
			 */
			wrt_reg_word(&reg->hccr, HCCR_RESET_RISC);
			rd_reg_word(&reg->hccr);

			ha->isp_ops->fw_dump(vha);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			अवरोध;
		पूर्ण अन्यथा अगर ((rd_reg_word(&reg->istatus) & ISR_RISC_INT) == 0)
			अवरोध;

		अगर (rd_reg_word(&reg->semaphore) & BIT_0) अणु
			wrt_reg_word(&reg->hccr, HCCR_CLR_RISC_INT);
			rd_reg_word(&reg->hccr);

			/* Get mailbox data. */
			mb[0] = RD_MAILBOX_REG(ha, reg, 0);
			अगर (mb[0] > 0x3fff && mb[0] < 0x8000) अणु
				qla2x00_mbx_completion(vha, mb[0]);
				status |= MBX_INTERRUPT;
			पूर्ण अन्यथा अगर (mb[0] > 0x7fff && mb[0] < 0xc000) अणु
				mb[1] = RD_MAILBOX_REG(ha, reg, 1);
				mb[2] = RD_MAILBOX_REG(ha, reg, 2);
				mb[3] = RD_MAILBOX_REG(ha, reg, 3);
				qla2x00_async_event(vha, rsp, mb);
			पूर्ण अन्यथा अणु
				/*EMPTY*/
				ql_dbg(ql_dbg_async, vha, 0x5025,
				    "Unrecognized interrupt type (%d).\n",
				    mb[0]);
			पूर्ण
			/* Release mailbox रेजिस्टरs. */
			wrt_reg_word(&reg->semaphore, 0);
			rd_reg_word(&reg->semaphore);
		पूर्ण अन्यथा अणु
			qla2x00_process_response_queue(rsp);

			wrt_reg_word(&reg->hccr, HCCR_CLR_RISC_INT);
			rd_reg_word(&reg->hccr);
		पूर्ण
	पूर्ण
	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस (IRQ_HANDLED);
पूर्ण

bool
qla2x00_check_reg32_क्रम_disconnect(scsi_qla_host_t *vha, uपूर्णांक32_t reg)
अणु
	/* Check क्रम PCI disconnection */
	अगर (reg == 0xffffffff && !pci_channel_offline(vha->hw->pdev)) अणु
		अगर (!test_and_set_bit(PFLG_DISCONNECTED, &vha->pci_flags) &&
		    !test_bit(PFLG_DRIVER_REMOVING, &vha->pci_flags) &&
		    !test_bit(PFLG_DRIVER_PROBING, &vha->pci_flags)) अणु
			qla_schedule_eeh_work(vha);
		पूर्ण
		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

bool
qla2x00_check_reg16_क्रम_disconnect(scsi_qla_host_t *vha, uपूर्णांक16_t reg)
अणु
	वापस qla2x00_check_reg32_क्रम_disconnect(vha, 0xffff0000 | reg);
पूर्ण

/**
 * qla2300_पूर्णांकr_handler() - Process पूर्णांकerrupts क्रम the ISP23xx and ISP63xx.
 * @irq: पूर्णांकerrupt number
 * @dev_id: SCSI driver HA context
 *
 * Called by प्रणाली whenever the host adapter generates an पूर्णांकerrupt.
 *
 * Returns handled flag.
 */
irqवापस_t
qla2300_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा device_reg_2xxx __iomem *reg;
	पूर्णांक		status;
	अचिन्हित दीर्घ	iter;
	uपूर्णांक32_t	stat;
	uपूर्णांक16_t	hccr;
	uपूर्णांक16_t	mb[8];
	काष्ठा rsp_que *rsp;
	काष्ठा qla_hw_data *ha;
	अचिन्हित दीर्घ	flags;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0x5058,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस (IRQ_NONE);
	पूर्ण

	ha = rsp->hw;
	reg = &ha->iobase->isp;
	status = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	क्रम (iter = 50; iter--; ) अणु
		stat = rd_reg_dword(&reg->u.isp2300.host_status);
		अगर (qla2x00_check_reg32_क्रम_disconnect(vha, stat))
			अवरोध;
		अगर (stat & HSR_RISC_PAUSED) अणु
			अगर (unlikely(pci_channel_offline(ha->pdev)))
				अवरोध;

			hccr = rd_reg_word(&reg->hccr);

			अगर (hccr & (BIT_15 | BIT_13 | BIT_11 | BIT_8))
				ql_log(ql_log_warn, vha, 0x5026,
				    "Parity error -- HCCR=%x, Dumping "
				    "firmware.\n", hccr);
			अन्यथा
				ql_log(ql_log_warn, vha, 0x5027,
				    "RISC paused -- HCCR=%x, Dumping "
				    "firmware.\n", hccr);

			/*
			 * Issue a "HARD" reset in order क्रम the RISC
			 * पूर्णांकerrupt bit to be cleared.  Schedule a big
			 * hammer to get out of the RISC PAUSED state.
			 */
			wrt_reg_word(&reg->hccr, HCCR_RESET_RISC);
			rd_reg_word(&reg->hccr);

			ha->isp_ops->fw_dump(vha);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			अवरोध;
		पूर्ण अन्यथा अगर ((stat & HSR_RISC_INT) == 0)
			अवरोध;

		चयन (stat & 0xff) अणु
		हाल 0x1:
		हाल 0x2:
		हाल 0x10:
		हाल 0x11:
			qla2x00_mbx_completion(vha, MSW(stat));
			status |= MBX_INTERRUPT;

			/* Release mailbox रेजिस्टरs. */
			wrt_reg_word(&reg->semaphore, 0);
			अवरोध;
		हाल 0x12:
			mb[0] = MSW(stat);
			mb[1] = RD_MAILBOX_REG(ha, reg, 1);
			mb[2] = RD_MAILBOX_REG(ha, reg, 2);
			mb[3] = RD_MAILBOX_REG(ha, reg, 3);
			qla2x00_async_event(vha, rsp, mb);
			अवरोध;
		हाल 0x13:
			qla2x00_process_response_queue(rsp);
			अवरोध;
		हाल 0x15:
			mb[0] = MBA_CMPLT_1_16BIT;
			mb[1] = MSW(stat);
			qla2x00_async_event(vha, rsp, mb);
			अवरोध;
		हाल 0x16:
			mb[0] = MBA_SCSI_COMPLETION;
			mb[1] = MSW(stat);
			mb[2] = RD_MAILBOX_REG(ha, reg, 2);
			qla2x00_async_event(vha, rsp, mb);
			अवरोध;
		शेष:
			ql_dbg(ql_dbg_async, vha, 0x5028,
			    "Unrecognized interrupt type (%d).\n", stat & 0xff);
			अवरोध;
		पूर्ण
		wrt_reg_word(&reg->hccr, HCCR_CLR_RISC_INT);
		rd_reg_word_relaxed(&reg->hccr);
	पूर्ण
	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस (IRQ_HANDLED);
पूर्ण

/**
 * qla2x00_mbx_completion() - Process mailbox command completions.
 * @vha: SCSI driver HA context
 * @mb0: Mailbox0 रेजिस्टर
 */
अटल व्योम
qla2x00_mbx_completion(scsi_qla_host_t *vha, uपूर्णांक16_t mb0)
अणु
	uपूर्णांक16_t	cnt;
	uपूर्णांक32_t	mboxes;
	__le16 __iomem *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;

	/* Read all mbox रेजिस्टरs? */
	WARN_ON_ONCE(ha->mbx_count > 32);
	mboxes = (1ULL << ha->mbx_count) - 1;
	अगर (!ha->mcp)
		ql_dbg(ql_dbg_async, vha, 0x5001, "MBX pointer ERROR.\n");
	अन्यथा
		mboxes = ha->mcp->in_mb;

	/* Load वापस mailbox रेजिस्टरs. */
	ha->flags.mbox_पूर्णांक = 1;
	ha->mailbox_out[0] = mb0;
	mboxes >>= 1;
	wptr = MAILBOX_REG(ha, reg, 1);

	क्रम (cnt = 1; cnt < ha->mbx_count; cnt++) अणु
		अगर (IS_QLA2200(ha) && cnt == 8)
			wptr = MAILBOX_REG(ha, reg, 8);
		अगर ((cnt == 4 || cnt == 5) && (mboxes & BIT_0))
			ha->mailbox_out[cnt] = qla2x00_debounce_रेजिस्टर(wptr);
		अन्यथा अगर (mboxes & BIT_0)
			ha->mailbox_out[cnt] = rd_reg_word(wptr);

		wptr++;
		mboxes >>= 1;
	पूर्ण
पूर्ण

अटल व्योम
qla81xx_idc_event(scsi_qla_host_t *vha, uपूर्णांक16_t aen, uपूर्णांक16_t descr)
अणु
	अटल अक्षर *event[] =
		अणु "Complete", "Request Notification", "Time Extension" पूर्ण;
	पूर्णांक rval;
	काष्ठा device_reg_24xx __iomem *reg24 = &vha->hw->iobase->isp24;
	काष्ठा device_reg_82xx __iomem *reg82 = &vha->hw->iobase->isp82;
	__le16 __iomem *wptr;
	uपूर्णांक16_t cnt, समयout, mb[QLA_IDC_ACK_REGS];

	/* Seed data -- mailbox1 -> mailbox7. */
	अगर (IS_QLA81XX(vha->hw) || IS_QLA83XX(vha->hw))
		wptr = &reg24->mailbox1;
	अन्यथा अगर (IS_QLA8044(vha->hw))
		wptr = &reg82->mailbox_out[1];
	अन्यथा
		वापस;

	क्रम (cnt = 0; cnt < QLA_IDC_ACK_REGS; cnt++, wptr++)
		mb[cnt] = rd_reg_word(wptr);

	ql_dbg(ql_dbg_async, vha, 0x5021,
	    "Inter-Driver Communication %s -- "
	    "%04x %04x %04x %04x %04x %04x %04x.\n",
	    event[aen & 0xff], mb[0], mb[1], mb[2], mb[3],
	    mb[4], mb[5], mb[6]);
	चयन (aen) अणु
	/* Handle IDC Error completion हाल. */
	हाल MBA_IDC_COMPLETE:
		अगर (mb[1] >> 15) अणु
			vha->hw->flags.idc_compl_status = 1;
			अगर (vha->hw->notअगरy_dcbx_comp && !vha->vp_idx)
				complete(&vha->hw->dcbx_comp);
		पूर्ण
		अवरोध;

	हाल MBA_IDC_NOTIFY:
		/* Acknowledgement needed? [Notअगरy && non-zero समयout]. */
		समयout = (descr >> 8) & 0xf;
		ql_dbg(ql_dbg_async, vha, 0x5022,
		    "%lu Inter-Driver Communication %s -- ACK timeout=%d.\n",
		    vha->host_no, event[aen & 0xff], समयout);

		अगर (!समयout)
			वापस;
		rval = qla2x00_post_idc_ack_work(vha, mb);
		अगर (rval != QLA_SUCCESS)
			ql_log(ql_log_warn, vha, 0x5023,
			    "IDC failed to post ACK.\n");
		अवरोध;
	हाल MBA_IDC_TIME_EXT:
		vha->hw->idc_extend_पंचांगo = descr;
		ql_dbg(ql_dbg_async, vha, 0x5087,
		    "%lu Inter-Driver Communication %s -- "
		    "Extend timeout by=%d.\n",
		    vha->host_no, event[aen & 0xff], vha->hw->idc_extend_पंचांगo);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा LS_UNKNOWN	2
स्थिर अक्षर *
qla2x00_get_link_speed_str(काष्ठा qla_hw_data *ha, uपूर्णांक16_t speed)
अणु
	अटल स्थिर अक्षर *स्थिर link_speeds[] = अणु
		"1", "2", "?", "4", "8", "16", "32", "10"
	पूर्ण;
#घोषणा	QLA_LAST_SPEED (ARRAY_SIZE(link_speeds) - 1)

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
		वापस link_speeds[0];
	अन्यथा अगर (speed == 0x13)
		वापस link_speeds[QLA_LAST_SPEED];
	अन्यथा अगर (speed < QLA_LAST_SPEED)
		वापस link_speeds[speed];
	अन्यथा
		वापस link_speeds[LS_UNKNOWN];
पूर्ण

अटल व्योम
qla83xx_handle_8200_aen(scsi_qla_host_t *vha, uपूर्णांक16_t *mb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	/*
	 * 8200 AEN Interpretation:
	 * mb[0] = AEN code
	 * mb[1] = AEN Reason code
	 * mb[2] = LSW of Peg-Halt Status-1 Register
	 * mb[6] = MSW of Peg-Halt Status-1 Register
	 * mb[3] = LSW of Peg-Halt Status-2 रेजिस्टर
	 * mb[7] = MSW of Peg-Halt Status-2 रेजिस्टर
	 * mb[4] = IDC Device-State Register value
	 * mb[5] = IDC Driver-Presence Register value
	 */
	ql_dbg(ql_dbg_async, vha, 0x506b, "AEN Code: mb[0] = 0x%x AEN reason: "
	    "mb[1] = 0x%x PH-status1: mb[2] = 0x%x PH-status1: mb[6] = 0x%x.\n",
	    mb[0], mb[1], mb[2], mb[6]);
	ql_dbg(ql_dbg_async, vha, 0x506c, "PH-status2: mb[3] = 0x%x "
	    "PH-status2: mb[7] = 0x%x Device-State: mb[4] = 0x%x "
	    "Drv-Presence: mb[5] = 0x%x.\n", mb[3], mb[7], mb[4], mb[5]);

	अगर (mb[1] & (IDC_PEG_HALT_STATUS_CHANGE | IDC_NIC_FW_REPORTED_FAILURE |
				IDC_HEARTBEAT_FAILURE)) अणु
		ha->flags.nic_core_hung = 1;
		ql_log(ql_log_warn, vha, 0x5060,
		    "83XX: F/W Error Reported: Check if reset required.\n");

		अगर (mb[1] & IDC_PEG_HALT_STATUS_CHANGE) अणु
			uपूर्णांक32_t protocol_engine_id, fw_err_code, err_level;

			/*
			 * IDC_PEG_HALT_STATUS_CHANGE पूर्णांकerpretation:
			 *  - PEG-Halt Status-1 Register:
			 *	(LSW = mb[2], MSW = mb[6])
			 *	Bits 0-7   = protocol-engine ID
			 *	Bits 8-28  = f/w error code
			 *	Bits 29-31 = Error-level
			 *	    Error-level 0x1 = Non-Fatal error
			 *	    Error-level 0x2 = Recoverable Fatal error
			 *	    Error-level 0x4 = UnRecoverable Fatal error
			 *  - PEG-Halt Status-2 Register:
			 *	(LSW = mb[3], MSW = mb[7])
			 */
			protocol_engine_id = (mb[2] & 0xff);
			fw_err_code = (((mb[2] & 0xff00) >> 8) |
			    ((mb[6] & 0x1fff) << 8));
			err_level = ((mb[6] & 0xe000) >> 13);
			ql_log(ql_log_warn, vha, 0x5061, "PegHalt Status-1 "
			    "Register: protocol_engine_id=0x%x "
			    "fw_err_code=0x%x err_level=0x%x.\n",
			    protocol_engine_id, fw_err_code, err_level);
			ql_log(ql_log_warn, vha, 0x5062, "PegHalt Status-2 "
			    "Register: 0x%x%x.\n", mb[7], mb[3]);
			अगर (err_level == ERR_LEVEL_NON_FATAL) अणु
				ql_log(ql_log_warn, vha, 0x5063,
				    "Not a fatal error, f/w has recovered itself.\n");
			पूर्ण अन्यथा अगर (err_level == ERR_LEVEL_RECOVERABLE_FATAL) अणु
				ql_log(ql_log_fatal, vha, 0x5064,
				    "Recoverable Fatal error: Chip reset "
				    "required.\n");
				qla83xx_schedule_work(vha,
				    QLA83XX_NIC_CORE_RESET);
			पूर्ण अन्यथा अगर (err_level == ERR_LEVEL_UNRECOVERABLE_FATAL) अणु
				ql_log(ql_log_fatal, vha, 0x5065,
				    "Unrecoverable Fatal error: Set FAILED "
				    "state, reboot required.\n");
				qla83xx_schedule_work(vha,
				    QLA83XX_NIC_CORE_UNRECOVERABLE);
			पूर्ण
		पूर्ण

		अगर (mb[1] & IDC_NIC_FW_REPORTED_FAILURE) अणु
			uपूर्णांक16_t peg_fw_state, nw_पूर्णांकerface_link_up;
			uपूर्णांक16_t nw_पूर्णांकerface_संकेत_detect, sfp_status;
			uपूर्णांक16_t htbt_counter, htbt_monitor_enable;
			uपूर्णांक16_t sfp_additional_info, sfp_multirate;
			uपूर्णांक16_t sfp_tx_fault, link_speed, dcbx_status;

			/*
			 * IDC_NIC_FW_REPORTED_FAILURE पूर्णांकerpretation:
			 *  - PEG-to-FC Status Register:
			 *	(LSW = mb[2], MSW = mb[6])
			 *	Bits 0-7   = Peg-Firmware state
			 *	Bit 8      = N/W Interface Link-up
			 *	Bit 9      = N/W Interface संकेत detected
			 *	Bits 10-11 = SFP Status
			 *	  SFP Status 0x0 = SFP+ transceiver not expected
			 *	  SFP Status 0x1 = SFP+ transceiver not present
			 *	  SFP Status 0x2 = SFP+ transceiver invalid
			 *	  SFP Status 0x3 = SFP+ transceiver present and
			 *	  valid
			 *	Bits 12-14 = Heartbeat Counter
			 *	Bit 15     = Heartbeat Monitor Enable
			 *	Bits 16-17 = SFP Additional Info
			 *	  SFP info 0x0 = Unregocnized transceiver क्रम
			 *	  Ethernet
			 *	  SFP info 0x1 = SFP+ bअक्रम validation failed
			 *	  SFP info 0x2 = SFP+ speed validation failed
			 *	  SFP info 0x3 = SFP+ access error
			 *	Bit 18     = SFP Multirate
			 *	Bit 19     = SFP Tx Fault
			 *	Bits 20-22 = Link Speed
			 *	Bits 23-27 = Reserved
			 *	Bits 28-30 = DCBX Status
			 *	  DCBX Status 0x0 = DCBX Disabled
			 *	  DCBX Status 0x1 = DCBX Enabled
			 *	  DCBX Status 0x2 = DCBX Exchange error
			 *	Bit 31     = Reserved
			 */
			peg_fw_state = (mb[2] & 0x00ff);
			nw_पूर्णांकerface_link_up = ((mb[2] & 0x0100) >> 8);
			nw_पूर्णांकerface_संकेत_detect = ((mb[2] & 0x0200) >> 9);
			sfp_status = ((mb[2] & 0x0c00) >> 10);
			htbt_counter = ((mb[2] & 0x7000) >> 12);
			htbt_monitor_enable = ((mb[2] & 0x8000) >> 15);
			sfp_additional_info = (mb[6] & 0x0003);
			sfp_multirate = ((mb[6] & 0x0004) >> 2);
			sfp_tx_fault = ((mb[6] & 0x0008) >> 3);
			link_speed = ((mb[6] & 0x0070) >> 4);
			dcbx_status = ((mb[6] & 0x7000) >> 12);

			ql_log(ql_log_warn, vha, 0x5066,
			    "Peg-to-Fc Status Register:\n"
			    "peg_fw_state=0x%x, nw_interface_link_up=0x%x, "
			    "nw_interface_signal_detect=0x%x"
			    "\nsfp_statis=0x%x.\n ", peg_fw_state,
			    nw_पूर्णांकerface_link_up, nw_पूर्णांकerface_संकेत_detect,
			    sfp_status);
			ql_log(ql_log_warn, vha, 0x5067,
			    "htbt_counter=0x%x, htbt_monitor_enable=0x%x, "
			    "sfp_additional_info=0x%x, sfp_multirate=0x%x.\n ",
			    htbt_counter, htbt_monitor_enable,
			    sfp_additional_info, sfp_multirate);
			ql_log(ql_log_warn, vha, 0x5068,
			    "sfp_tx_fault=0x%x, link_state=0x%x, "
			    "dcbx_status=0x%x.\n", sfp_tx_fault, link_speed,
			    dcbx_status);

			qla83xx_schedule_work(vha, QLA83XX_NIC_CORE_RESET);
		पूर्ण

		अगर (mb[1] & IDC_HEARTBEAT_FAILURE) अणु
			ql_log(ql_log_warn, vha, 0x5069,
			    "Heartbeat Failure encountered, chip reset "
			    "required.\n");

			qla83xx_schedule_work(vha, QLA83XX_NIC_CORE_RESET);
		पूर्ण
	पूर्ण

	अगर (mb[1] & IDC_DEVICE_STATE_CHANGE) अणु
		ql_log(ql_log_info, vha, 0x506a,
		    "IDC Device-State changed = 0x%x.\n", mb[4]);
		अगर (ha->flags.nic_core_reset_owner)
			वापस;
		qla83xx_schedule_work(vha, MBA_IDC_AEN);
	पूर्ण
पूर्ण

पूर्णांक
qla2x00_is_a_vp_did(scsi_qla_host_t *vha, uपूर्णांक32_t rscn_entry)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *vp;
	uपूर्णांक32_t vp_did;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	अगर (!ha->num_vhosts)
		वापस ret;

	spin_lock_irqsave(&ha->vport_slock, flags);
	list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
		vp_did = vp->d_id.b24;
		अगर (vp_did == rscn_entry) अणु
			ret = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ha->vport_slock, flags);

	वापस ret;
पूर्ण

fc_port_t *
qla2x00_find_fcport_by_loopid(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id)
अणु
	fc_port_t *f, *tf;

	f = tf = शून्य;
	list_क्रम_each_entry_safe(f, tf, &vha->vp_fcports, list)
		अगर (f->loop_id == loop_id)
			वापस f;
	वापस शून्य;
पूर्ण

fc_port_t *
qla2x00_find_fcport_by_wwpn(scsi_qla_host_t *vha, u8 *wwpn, u8 incl_deleted)
अणु
	fc_port_t *f, *tf;

	f = tf = शून्य;
	list_क्रम_each_entry_safe(f, tf, &vha->vp_fcports, list) अणु
		अगर (स_भेद(f->port_name, wwpn, WWN_SIZE) == 0) अणु
			अगर (incl_deleted)
				वापस f;
			अन्यथा अगर (f->deleted == 0)
				वापस f;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

fc_port_t *
qla2x00_find_fcport_by_nportid(scsi_qla_host_t *vha, port_id_t *id,
	u8 incl_deleted)
अणु
	fc_port_t *f, *tf;

	f = tf = शून्य;
	list_क्रम_each_entry_safe(f, tf, &vha->vp_fcports, list) अणु
		अगर (f->d_id.b24 == id->b24) अणु
			अगर (incl_deleted)
				वापस f;
			अन्यथा अगर (f->deleted == 0)
				वापस f;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* Shall be called only on supported adapters. */
अटल व्योम
qla27xx_handle_8200_aen(scsi_qla_host_t *vha, uपूर्णांक16_t *mb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	bool reset_isp_needed = false;

	ql_log(ql_log_warn, vha, 0x02f0,
	       "MPI Heartbeat stop. MPI reset is%s needed. "
	       "MB0[%xh] MB1[%xh] MB2[%xh] MB3[%xh]\n",
	       mb[1] & BIT_8 ? "" : " not",
	       mb[0], mb[1], mb[2], mb[3]);

	अगर ((mb[1] & BIT_8) == 0)
		वापस;

	ql_log(ql_log_warn, vha, 0x02f1,
	       "MPI Heartbeat stop. FW dump needed\n");

	अगर (ql2xfulldump_on_mpअगरail) अणु
		ha->isp_ops->fw_dump(vha);
		reset_isp_needed = true;
	पूर्ण

	ha->isp_ops->mpi_fw_dump(vha, 1);

	अगर (reset_isp_needed) अणु
		vha->hw->flags.fw_init_करोne = 0;
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
	पूर्ण
पूर्ण

अटल काष्ठा purex_item *
qla24xx_alloc_purex_item(scsi_qla_host_t *vha, uपूर्णांक16_t size)
अणु
	काष्ठा purex_item *item = शून्य;
	uपूर्णांक8_t item_hdr_size = माप(*item);

	अगर (size > QLA_DEFAULT_PAYLOAD_SIZE) अणु
		item = kzalloc(item_hdr_size +
		    (size - QLA_DEFAULT_PAYLOAD_SIZE), GFP_ATOMIC);
	पूर्ण अन्यथा अणु
		अगर (atomic_inc_वापस(&vha->शेष_item.in_use) == 1) अणु
			item = &vha->शेष_item;
			जाओ initialize_purex_header;
		पूर्ण अन्यथा अणु
			item = kzalloc(item_hdr_size, GFP_ATOMIC);
		पूर्ण
	पूर्ण
	अगर (!item) अणु
		ql_log(ql_log_warn, vha, 0x5092,
		       ">> Failed allocate purex list item.\n");

		वापस शून्य;
	पूर्ण

initialize_purex_header:
	item->vha = vha;
	item->size = size;
	वापस item;
पूर्ण

अटल व्योम
qla24xx_queue_purex_item(scsi_qla_host_t *vha, काष्ठा purex_item *pkt,
			 व्योम (*process_item)(काष्ठा scsi_qla_host *vha,
					      काष्ठा purex_item *pkt))
अणु
	काष्ठा purex_list *list = &vha->purex_list;
	uदीर्घ flags;

	pkt->process_item = process_item;

	spin_lock_irqsave(&list->lock, flags);
	list_add_tail(&pkt->list, &list->head);
	spin_unlock_irqrestore(&list->lock, flags);

	set_bit(PROCESS_PUREX_IOCB, &vha->dpc_flags);
पूर्ण

/**
 * qla24xx_copy_std_pkt() - Copy over purex ELS which is
 * contained in a single IOCB.
 * purex packet.
 * @vha: SCSI driver HA context
 * @pkt: ELS packet
 */
अटल काष्ठा purex_item
*qla24xx_copy_std_pkt(काष्ठा scsi_qla_host *vha, व्योम *pkt)
अणु
	काष्ठा purex_item *item;

	item = qla24xx_alloc_purex_item(vha,
					QLA_DEFAULT_PAYLOAD_SIZE);
	अगर (!item)
		वापस item;

	स_नकल(&item->iocb, pkt, माप(item->iocb));
	वापस item;
पूर्ण

/**
 * qla27xx_copy_fpin_pkt() - Copy over fpin packets that can
 * span over multiple IOCBs.
 * @vha: SCSI driver HA context
 * @pkt: ELS packet
 * @rsp: Response queue
 */
अटल काष्ठा purex_item *
qla27xx_copy_fpin_pkt(काष्ठा scsi_qla_host *vha, व्योम **pkt,
		      काष्ठा rsp_que **rsp)
अणु
	काष्ठा purex_entry_24xx *purex = *pkt;
	काष्ठा rsp_que *rsp_q = *rsp;
	sts_cont_entry_t *new_pkt;
	uपूर्णांक16_t no_bytes = 0, total_bytes = 0, pending_bytes = 0;
	uपूर्णांक16_t buffer_copy_offset = 0;
	uपूर्णांक16_t entry_count, entry_count_reमुख्यing;
	काष्ठा purex_item *item;
	व्योम *fpin_pkt = शून्य;

	total_bytes = (le16_to_cpu(purex->frame_size) & 0x0FFF)
	    - PURX_ELS_HEADER_SIZE;
	pending_bytes = total_bytes;
	entry_count = entry_count_reमुख्यing = purex->entry_count;
	no_bytes = (pending_bytes > माप(purex->els_frame_payload))  ?
		   माप(purex->els_frame_payload) : pending_bytes;
	ql_log(ql_log_info, vha, 0x509a,
	       "FPIN ELS, frame_size 0x%x, entry count %d\n",
	       total_bytes, entry_count);

	item = qla24xx_alloc_purex_item(vha, total_bytes);
	अगर (!item)
		वापस item;

	fpin_pkt = &item->iocb;

	स_नकल(fpin_pkt, &purex->els_frame_payload[0], no_bytes);
	buffer_copy_offset += no_bytes;
	pending_bytes -= no_bytes;
	--entry_count_reमुख्यing;

	((response_t *)purex)->signature = RESPONSE_PROCESSED;
	wmb();

	करो अणु
		जबतक ((total_bytes > 0) && (entry_count_reमुख्यing > 0)) अणु
			अगर (rsp_q->ring_ptr->signature == RESPONSE_PROCESSED) अणु
				ql_dbg(ql_dbg_async, vha, 0x5084,
				       "Ran out of IOCBs, partial data 0x%x\n",
				       buffer_copy_offset);
				cpu_relax();
				जारी;
			पूर्ण

			new_pkt = (sts_cont_entry_t *)rsp_q->ring_ptr;
			*pkt = new_pkt;

			अगर (new_pkt->entry_type != STATUS_CONT_TYPE) अणु
				ql_log(ql_log_warn, vha, 0x507a,
				       "Unexpected IOCB type, partial data 0x%x\n",
				       buffer_copy_offset);
				अवरोध;
			पूर्ण

			rsp_q->ring_index++;
			अगर (rsp_q->ring_index == rsp_q->length) अणु
				rsp_q->ring_index = 0;
				rsp_q->ring_ptr = rsp_q->ring;
			पूर्ण अन्यथा अणु
				rsp_q->ring_ptr++;
			पूर्ण
			no_bytes = (pending_bytes > माप(new_pkt->data)) ?
			    माप(new_pkt->data) : pending_bytes;
			अगर ((buffer_copy_offset + no_bytes) <= total_bytes) अणु
				स_नकल(((uपूर्णांक8_t *)fpin_pkt +
				    buffer_copy_offset), new_pkt->data,
				    no_bytes);
				buffer_copy_offset += no_bytes;
				pending_bytes -= no_bytes;
				--entry_count_reमुख्यing;
			पूर्ण अन्यथा अणु
				ql_log(ql_log_warn, vha, 0x5044,
				       "Attempt to copy more that we got, optimizing..%x\n",
				       buffer_copy_offset);
				स_नकल(((uपूर्णांक8_t *)fpin_pkt +
				    buffer_copy_offset), new_pkt->data,
				    total_bytes - buffer_copy_offset);
			पूर्ण

			((response_t *)new_pkt)->signature = RESPONSE_PROCESSED;
			wmb();
		पूर्ण

		अगर (pending_bytes != 0 || entry_count_reमुख्यing != 0) अणु
			ql_log(ql_log_fatal, vha, 0x508b,
			       "Dropping partial FPIN, underrun bytes = 0x%x, entry cnts 0x%x\n",
			       total_bytes, entry_count_reमुख्यing);
			qla24xx_मुक्त_purex_item(item);
			वापस शून्य;
		पूर्ण
	पूर्ण जबतक (entry_count_reमुख्यing > 0);
	host_to_fcp_swap((uपूर्णांक8_t *)&item->iocb, total_bytes);
	वापस item;
पूर्ण

/**
 * qla2x00_async_event() - Process aynchronous events.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 * @mb: Mailbox रेजिस्टरs (0 - 3)
 */
व्योम
qla2x00_async_event(scsi_qla_host_t *vha, काष्ठा rsp_que *rsp, uपूर्णांक16_t *mb)
अणु
	uपूर्णांक16_t	handle_cnt;
	uपूर्णांक16_t	cnt, mbx;
	uपूर्णांक32_t	handles[5];
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	काष्ठा device_reg_24xx __iomem *reg24 = &ha->iobase->isp24;
	काष्ठा device_reg_82xx __iomem *reg82 = &ha->iobase->isp82;
	uपूर्णांक32_t	rscn_entry, host_pid;
	अचिन्हित दीर्घ	flags;
	fc_port_t	*fcport = शून्य;

	अगर (!vha->hw->flags.fw_started)
		वापस;

	/* Setup to process RIO completion. */
	handle_cnt = 0;
	अगर (IS_CNA_CAPABLE(ha))
		जाओ skip_rio;
	चयन (mb[0]) अणु
	हाल MBA_SCSI_COMPLETION:
		handles[0] = make_handle(mb[2], mb[1]);
		handle_cnt = 1;
		अवरोध;
	हाल MBA_CMPLT_1_16BIT:
		handles[0] = mb[1];
		handle_cnt = 1;
		mb[0] = MBA_SCSI_COMPLETION;
		अवरोध;
	हाल MBA_CMPLT_2_16BIT:
		handles[0] = mb[1];
		handles[1] = mb[2];
		handle_cnt = 2;
		mb[0] = MBA_SCSI_COMPLETION;
		अवरोध;
	हाल MBA_CMPLT_3_16BIT:
		handles[0] = mb[1];
		handles[1] = mb[2];
		handles[2] = mb[3];
		handle_cnt = 3;
		mb[0] = MBA_SCSI_COMPLETION;
		अवरोध;
	हाल MBA_CMPLT_4_16BIT:
		handles[0] = mb[1];
		handles[1] = mb[2];
		handles[2] = mb[3];
		handles[3] = (uपूर्णांक32_t)RD_MAILBOX_REG(ha, reg, 6);
		handle_cnt = 4;
		mb[0] = MBA_SCSI_COMPLETION;
		अवरोध;
	हाल MBA_CMPLT_5_16BIT:
		handles[0] = mb[1];
		handles[1] = mb[2];
		handles[2] = mb[3];
		handles[3] = (uपूर्णांक32_t)RD_MAILBOX_REG(ha, reg, 6);
		handles[4] = (uपूर्णांक32_t)RD_MAILBOX_REG(ha, reg, 7);
		handle_cnt = 5;
		mb[0] = MBA_SCSI_COMPLETION;
		अवरोध;
	हाल MBA_CMPLT_2_32BIT:
		handles[0] = make_handle(mb[2], mb[1]);
		handles[1] = make_handle(RD_MAILBOX_REG(ha, reg, 7),
					 RD_MAILBOX_REG(ha, reg, 6));
		handle_cnt = 2;
		mb[0] = MBA_SCSI_COMPLETION;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
skip_rio:
	चयन (mb[0]) अणु
	हाल MBA_SCSI_COMPLETION:	/* Fast Post */
		अगर (!vha->flags.online)
			अवरोध;

		क्रम (cnt = 0; cnt < handle_cnt; cnt++)
			qla2x00_process_completed_request(vha, rsp->req,
				handles[cnt]);
		अवरोध;

	हाल MBA_RESET:			/* Reset */
		ql_dbg(ql_dbg_async, vha, 0x5002,
		    "Asynchronous RESET.\n");

		set_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MBA_SYSTEM_ERR:		/* System Error */
		mbx = 0;

		vha->hw_err_cnt++;

		अगर (IS_QLA81XX(ha) || IS_QLA83XX(ha) ||
		    IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			u16 m[4];

			m[0] = rd_reg_word(&reg24->mailbox4);
			m[1] = rd_reg_word(&reg24->mailbox5);
			m[2] = rd_reg_word(&reg24->mailbox6);
			mbx = m[3] = rd_reg_word(&reg24->mailbox7);

			ql_log(ql_log_warn, vha, 0x5003,
			    "ISP System Error - mbx1=%xh mbx2=%xh mbx3=%xh mbx4=%xh mbx5=%xh mbx6=%xh mbx7=%xh.\n",
			    mb[1], mb[2], mb[3], m[0], m[1], m[2], m[3]);
		पूर्ण अन्यथा
			ql_log(ql_log_warn, vha, 0x5003,
			    "ISP System Error - mbx1=%xh mbx2=%xh mbx3=%xh.\n ",
			    mb[1], mb[2], mb[3]);

		अगर ((IS_QLA27XX(ha) || IS_QLA28XX(ha)) &&
		    rd_reg_word(&reg24->mailbox7) & BIT_8)
			ha->isp_ops->mpi_fw_dump(vha, 1);
		ha->isp_ops->fw_dump(vha);
		ha->flags.fw_init_करोne = 0;
		QLA_FW_STOPPED(ha);

		अगर (IS_FWI2_CAPABLE(ha)) अणु
			अगर (mb[1] == 0 && mb[2] == 0) अणु
				ql_log(ql_log_fatal, vha, 0x5004,
				    "Unrecoverable Hardware Error: adapter "
				    "marked OFFLINE!\n");
				vha->flags.online = 0;
				vha->device_flags |= DFLG_DEV_FAILED;
			पूर्ण अन्यथा अणु
				/* Check to see अगर MPI समयout occurred */
				अगर ((mbx & MBX_3) && (ha->port_no == 0))
					set_bit(MPI_RESET_NEEDED,
					    &vha->dpc_flags);

				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			पूर्ण
		पूर्ण अन्यथा अगर (mb[1] == 0) अणु
			ql_log(ql_log_fatal, vha, 0x5005,
			    "Unrecoverable Hardware Error: adapter marked "
			    "OFFLINE!\n");
			vha->flags.online = 0;
			vha->device_flags |= DFLG_DEV_FAILED;
		पूर्ण अन्यथा
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MBA_REQ_TRANSFER_ERR:	/* Request Transfer Error */
		ql_log(ql_log_warn, vha, 0x5006,
		    "ISP Request Transfer Error (%x).\n",  mb[1]);

		vha->hw_err_cnt++;

		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MBA_RSP_TRANSFER_ERR:	/* Response Transfer Error */
		ql_log(ql_log_warn, vha, 0x5007,
		    "ISP Response Transfer Error (%x).\n", mb[1]);

		vha->hw_err_cnt++;

		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MBA_WAKEUP_THRES:		/* Request Queue Wake-up */
		ql_dbg(ql_dbg_async, vha, 0x5008,
		    "Asynchronous WAKEUP_THRES (%x).\n", mb[1]);
		अवरोध;

	हाल MBA_LOOP_INIT_ERR:
		ql_log(ql_log_warn, vha, 0x5090,
		    "LOOP INIT ERROR (%x).\n", mb[1]);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल MBA_LIP_OCCURRED:		/* Loop Initialization Procedure */
		ha->flags.lip_ae = 1;

		ql_dbg(ql_dbg_async, vha, 0x5009,
		    "LIP occurred (%x).\n", mb[1]);

		अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
			atomic_set(&vha->loop_state, LOOP_DOWN);
			atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
			qla2x00_mark_all_devices_lost(vha);
		पूर्ण

		अगर (vha->vp_idx) अणु
			atomic_set(&vha->vp_state, VP_FAILED);
			fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		पूर्ण

		set_bit(REGISTER_FC4_NEEDED, &vha->dpc_flags);
		set_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags);

		vha->flags.management_server_logged_in = 0;
		qla2x00_post_aen_work(vha, FCH_EVT_LIP, mb[1]);
		अवरोध;

	हाल MBA_LOOP_UP:		/* Loop Up Event */
		अगर (IS_QLA2100(ha) || IS_QLA2200(ha))
			ha->link_data_rate = PORT_SPEED_1GB;
		अन्यथा
			ha->link_data_rate = mb[1];

		ql_log(ql_log_info, vha, 0x500a,
		    "LOOP UP detected (%s Gbps).\n",
		    qla2x00_get_link_speed_str(ha, ha->link_data_rate));

		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			अगर (mb[2] & BIT_0)
				ql_log(ql_log_info, vha, 0x11a0,
				    "FEC=enabled (link up).\n");
		पूर्ण

		vha->flags.management_server_logged_in = 0;
		qla2x00_post_aen_work(vha, FCH_EVT_LINKUP, ha->link_data_rate);

		अगर (vha->link_करोwn_समय < vha->hw->port_करोwn_retry_count) अणु
			vha->लघु_link_करोwn_cnt++;
			vha->link_करोwn_समय = QLA2XX_MAX_LINK_DOWN_TIME;
		पूर्ण

		अवरोध;

	हाल MBA_LOOP_DOWN:		/* Loop Down Event */
		SAVE_TOPO(ha);
		ha->flags.lip_ae = 0;
		ha->current_topology = 0;
		vha->link_करोwn_समय = 0;

		mbx = (IS_QLA81XX(ha) || IS_QLA8031(ha))
			? rd_reg_word(&reg24->mailbox4) : 0;
		mbx = (IS_P3P_TYPE(ha)) ? rd_reg_word(&reg82->mailbox_out[4])
			: mbx;
		ql_log(ql_log_info, vha, 0x500b,
		    "LOOP DOWN detected (%x %x %x %x).\n",
		    mb[1], mb[2], mb[3], mbx);

		अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
			atomic_set(&vha->loop_state, LOOP_DOWN);
			atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
			/*
			 * In हाल of loop करोwn, restore WWPN from
			 * NVRAM in हाल of FA-WWPN capable ISP
			 * Restore क्रम Physical Port only
			 */
			अगर (!vha->vp_idx) अणु
				अगर (ha->flags.fawwpn_enabled &&
				    (ha->current_topology == ISP_CFG_F)) अणु
					व्योम *wwpn = ha->init_cb->port_name;

					स_नकल(vha->port_name, wwpn, WWN_SIZE);
					fc_host_port_name(vha->host) =
					    wwn_to_u64(vha->port_name);
					ql_dbg(ql_dbg_init + ql_dbg_verbose,
					    vha, 0x00d8, "LOOP DOWN detected,"
					    "restore WWPN %016llx\n",
					    wwn_to_u64(vha->port_name));
				पूर्ण

				clear_bit(VP_CONFIG_OK, &vha->vp_flags);
			पूर्ण

			vha->device_flags |= DFLG_NO_CABLE;
			qla2x00_mark_all_devices_lost(vha);
		पूर्ण

		अगर (vha->vp_idx) अणु
			atomic_set(&vha->vp_state, VP_FAILED);
			fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		पूर्ण

		vha->flags.management_server_logged_in = 0;
		ha->link_data_rate = PORT_SPEED_UNKNOWN;
		qla2x00_post_aen_work(vha, FCH_EVT_LINKDOWN, 0);
		अवरोध;

	हाल MBA_LIP_RESET:		/* LIP reset occurred */
		ql_dbg(ql_dbg_async, vha, 0x500c,
		    "LIP reset occurred (%x).\n", mb[1]);

		अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
			atomic_set(&vha->loop_state, LOOP_DOWN);
			atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
			qla2x00_mark_all_devices_lost(vha);
		पूर्ण

		अगर (vha->vp_idx) अणु
			atomic_set(&vha->vp_state, VP_FAILED);
			fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		पूर्ण

		set_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);

		ha->operating_mode = LOOP;
		vha->flags.management_server_logged_in = 0;
		qla2x00_post_aen_work(vha, FCH_EVT_LIPRESET, mb[1]);
		अवरोध;

	/* हाल MBA_DCBX_COMPLETE: */
	हाल MBA_POINT_TO_POINT:	/* Poपूर्णांक-to-Poपूर्णांक */
		ha->flags.lip_ae = 0;

		अगर (IS_QLA2100(ha))
			अवरोध;

		अगर (IS_CNA_CAPABLE(ha)) अणु
			ql_dbg(ql_dbg_async, vha, 0x500d,
			    "DCBX Completed -- %04x %04x %04x.\n",
			    mb[1], mb[2], mb[3]);
			अगर (ha->notअगरy_dcbx_comp && !vha->vp_idx)
				complete(&ha->dcbx_comp);

		पूर्ण अन्यथा
			ql_dbg(ql_dbg_async, vha, 0x500e,
			    "Asynchronous P2P MODE received.\n");

		/*
		 * Until there's a transition from loop करोwn to loop up, treat
		 * this as loop करोwn only.
		 */
		अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
			atomic_set(&vha->loop_state, LOOP_DOWN);
			अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr))
				atomic_set(&vha->loop_करोwn_समयr,
				    LOOP_DOWN_TIME);
			अगर (!N2N_TOPO(ha))
				qla2x00_mark_all_devices_lost(vha);
		पूर्ण

		अगर (vha->vp_idx) अणु
			atomic_set(&vha->vp_state, VP_FAILED);
			fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		पूर्ण

		अगर (!(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)))
			set_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);

		set_bit(REGISTER_FC4_NEEDED, &vha->dpc_flags);
		set_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags);

		vha->flags.management_server_logged_in = 0;
		अवरोध;

	हाल MBA_CHG_IN_CONNECTION:	/* Change in connection mode */
		अगर (IS_QLA2100(ha))
			अवरोध;

		ql_dbg(ql_dbg_async, vha, 0x500f,
		    "Configuration change detected: value=%x.\n", mb[1]);

		अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
			atomic_set(&vha->loop_state, LOOP_DOWN);
			अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr))
				atomic_set(&vha->loop_करोwn_समयr,
				    LOOP_DOWN_TIME);
			qla2x00_mark_all_devices_lost(vha);
		पूर्ण

		अगर (vha->vp_idx) अणु
			atomic_set(&vha->vp_state, VP_FAILED);
			fc_vport_set_state(vha->fc_vport, FC_VPORT_FAILED);
		पूर्ण

		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		अवरोध;

	हाल MBA_PORT_UPDATE:		/* Port database update */
		/*
		 * Handle only global and vn-port update events
		 *
		 * Relevant inमाला_दो:
		 * mb[1] = N_Port handle of changed port
		 * OR 0xffff क्रम global event
		 * mb[2] = New login state
		 * 7 = Port logged out
		 * mb[3] = LSB is vp_idx, 0xff = all vps
		 *
		 * Skip processing अगर:
		 *       Event is global, vp_idx is NOT all vps,
		 *           vp_idx करोes not match
		 *       Event is not global, vp_idx करोes not match
		 */
		अगर (IS_QLA2XXX_MIDTYPE(ha) &&
		    ((mb[1] == 0xffff && (mb[3] & 0xff) != 0xff) ||
			(mb[1] != 0xffff)) && vha->vp_idx != (mb[3] & 0xff))
			अवरोध;

		अगर (mb[2] == 0x7) अणु
			ql_dbg(ql_dbg_async, vha, 0x5010,
			    "Port %s %04x %04x %04x.\n",
			    mb[1] == 0xffff ? "unavailable" : "logout",
			    mb[1], mb[2], mb[3]);

			अगर (mb[1] == 0xffff)
				जाओ global_port_update;

			अगर (mb[1] == NPH_SNS_LID(ha)) अणु
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
				अवरोध;
			पूर्ण

			/* use handle_cnt क्रम loop id/nport handle */
			अगर (IS_FWI2_CAPABLE(ha))
				handle_cnt = NPH_SNS;
			अन्यथा
				handle_cnt = SIMPLE_NAME_SERVER;
			अगर (mb[1] == handle_cnt) अणु
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
				अवरोध;
			पूर्ण

			/* Port logout */
			fcport = qla2x00_find_fcport_by_loopid(vha, mb[1]);
			अगर (!fcport)
				अवरोध;
			अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE)
				अवरोध;
			ql_dbg(ql_dbg_async, vha, 0x508a,
			    "Marking port lost loopid=%04x portid=%06x.\n",
			    fcport->loop_id, fcport->d_id.b24);
			अगर (qla_ini_mode_enabled(vha)) अणु
				fcport->logout_on_delete = 0;
				qlt_schedule_sess_क्रम_deletion(fcport);
			पूर्ण
			अवरोध;

global_port_update:
			अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
				atomic_set(&vha->loop_state, LOOP_DOWN);
				atomic_set(&vha->loop_करोwn_समयr,
				    LOOP_DOWN_TIME);
				vha->device_flags |= DFLG_NO_CABLE;
				qla2x00_mark_all_devices_lost(vha);
			पूर्ण

			अगर (vha->vp_idx) अणु
				atomic_set(&vha->vp_state, VP_FAILED);
				fc_vport_set_state(vha->fc_vport,
				    FC_VPORT_FAILED);
				qla2x00_mark_all_devices_lost(vha);
			पूर्ण

			vha->flags.management_server_logged_in = 0;
			ha->link_data_rate = PORT_SPEED_UNKNOWN;
			अवरोध;
		पूर्ण

		/*
		 * If PORT UPDATE is global (received LIP_OCCURRED/LIP_RESET
		 * event etc. earlier indicating loop is करोwn) then process
		 * it.  Otherwise ignore it and Wait क्रम RSCN to come in.
		 */
		atomic_set(&vha->loop_करोwn_समयr, 0);
		अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN &&
			!ha->flags.n2n_ae  &&
		    atomic_पढ़ो(&vha->loop_state) != LOOP_DEAD) अणु
			ql_dbg(ql_dbg_async, vha, 0x5011,
			    "Asynchronous PORT UPDATE ignored %04x/%04x/%04x.\n",
			    mb[1], mb[2], mb[3]);
			अवरोध;
		पूर्ण

		ql_dbg(ql_dbg_async, vha, 0x5012,
		    "Port database changed %04x %04x %04x.\n",
		    mb[1], mb[2], mb[3]);

		/*
		 * Mark all devices as missing so we will login again.
		 */
		atomic_set(&vha->loop_state, LOOP_UP);
		vha->scan.scan_retry = 0;

		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		set_bit(LOCAL_LOOP_UPDATE, &vha->dpc_flags);
		set_bit(VP_CONFIG_OK, &vha->vp_flags);
		अवरोध;

	हाल MBA_RSCN_UPDATE:		/* State Change Registration */
		/* Check अगर the Vport has issued a SCR */
		अगर (vha->vp_idx && test_bit(VP_SCR_NEEDED, &vha->vp_flags))
			अवरोध;
		/* Only handle SCNs क्रम our Vport index. */
		अगर (ha->flags.npiv_supported && vha->vp_idx != (mb[3] & 0xff))
			अवरोध;

		ql_log(ql_log_warn, vha, 0x5013,
		       "RSCN database changed -- %04x %04x %04x.\n",
		       mb[1], mb[2], mb[3]);

		rscn_entry = ((mb[1] & 0xff) << 16) | mb[2];
		host_pid = (vha->d_id.b.करोमुख्य << 16) | (vha->d_id.b.area << 8)
				| vha->d_id.b.al_pa;
		अगर (rscn_entry == host_pid) अणु
			ql_dbg(ql_dbg_async, vha, 0x5014,
			    "Ignoring RSCN update to local host "
			    "port ID (%06x).\n", host_pid);
			अवरोध;
		पूर्ण

		/* Ignore reserved bits from RSCN-payload. */
		rscn_entry = ((mb[1] & 0x3ff) << 16) | mb[2];

		/* Skip RSCNs क्रम भव ports on the same physical port */
		अगर (qla2x00_is_a_vp_did(vha, rscn_entry))
			अवरोध;

		atomic_set(&vha->loop_करोwn_समयr, 0);
		vha->flags.management_server_logged_in = 0;
		अणु
			काष्ठा event_arg ea;

			स_रखो(&ea, 0, माप(ea));
			ea.id.b24 = rscn_entry;
			ea.id.b.rsvd_1 = rscn_entry >> 24;
			qla2x00_handle_rscn(vha, &ea);
			qla2x00_post_aen_work(vha, FCH_EVT_RSCN, rscn_entry);
		पूर्ण
		अवरोध;
	हाल MBA_CONGN_NOTI_RECV:
		अगर (!ha->flags.scm_enabled ||
		    mb[1] != QLA_CON_PRIMITIVE_RECEIVED)
			अवरोध;

		अगर (mb[2] == QLA_CONGESTION_ARB_WARNING) अणु
			ql_dbg(ql_dbg_async, vha, 0x509b,
			       "Congestion Warning %04x %04x.\n", mb[1], mb[2]);
		पूर्ण अन्यथा अगर (mb[2] == QLA_CONGESTION_ARB_ALARM) अणु
			ql_log(ql_log_warn, vha, 0x509b,
			       "Congestion Alarm %04x %04x.\n", mb[1], mb[2]);
		पूर्ण
		अवरोध;
	/* हाल MBA_RIO_RESPONSE: */
	हाल MBA_ZIO_RESPONSE:
		ql_dbg(ql_dbg_async, vha, 0x5015,
		    "[R|Z]IO update completion.\n");

		अगर (IS_FWI2_CAPABLE(ha))
			qla24xx_process_response_queue(vha, rsp);
		अन्यथा
			qla2x00_process_response_queue(rsp);
		अवरोध;

	हाल MBA_DISCARD_RND_FRAME:
		ql_dbg(ql_dbg_async, vha, 0x5016,
		    "Discard RND Frame -- %04x %04x %04x.\n",
		    mb[1], mb[2], mb[3]);
		vha->पूर्णांकerface_err_cnt++;
		अवरोध;

	हाल MBA_TRACE_NOTIFICATION:
		ql_dbg(ql_dbg_async, vha, 0x5017,
		    "Trace Notification -- %04x %04x.\n", mb[1], mb[2]);
		अवरोध;

	हाल MBA_ISP84XX_ALERT:
		ql_dbg(ql_dbg_async, vha, 0x5018,
		    "ISP84XX Alert Notification -- %04x %04x %04x.\n",
		    mb[1], mb[2], mb[3]);

		spin_lock_irqsave(&ha->cs84xx->access_lock, flags);
		चयन (mb[1]) अणु
		हाल A84_PANIC_RECOVERY:
			ql_log(ql_log_info, vha, 0x5019,
			    "Alert 84XX: panic recovery %04x %04x.\n",
			    mb[2], mb[3]);
			अवरोध;
		हाल A84_OP_LOGIN_COMPLETE:
			ha->cs84xx->op_fw_version = mb[3] << 16 | mb[2];
			ql_log(ql_log_info, vha, 0x501a,
			    "Alert 84XX: firmware version %x.\n",
			    ha->cs84xx->op_fw_version);
			अवरोध;
		हाल A84_DIAG_LOGIN_COMPLETE:
			ha->cs84xx->diag_fw_version = mb[3] << 16 | mb[2];
			ql_log(ql_log_info, vha, 0x501b,
			    "Alert 84XX: diagnostic firmware version %x.\n",
			    ha->cs84xx->diag_fw_version);
			अवरोध;
		हाल A84_GOLD_LOGIN_COMPLETE:
			ha->cs84xx->diag_fw_version = mb[3] << 16 | mb[2];
			ha->cs84xx->fw_update = 1;
			ql_log(ql_log_info, vha, 0x501c,
			    "Alert 84XX: gold firmware version %x.\n",
			    ha->cs84xx->gold_fw_version);
			अवरोध;
		शेष:
			ql_log(ql_log_warn, vha, 0x501d,
			    "Alert 84xx: Invalid Alert %04x %04x %04x.\n",
			    mb[1], mb[2], mb[3]);
		पूर्ण
		spin_unlock_irqrestore(&ha->cs84xx->access_lock, flags);
		अवरोध;
	हाल MBA_DCBX_START:
		ql_dbg(ql_dbg_async, vha, 0x501e,
		    "DCBX Started -- %04x %04x %04x.\n",
		    mb[1], mb[2], mb[3]);
		अवरोध;
	हाल MBA_DCBX_PARAM_UPDATE:
		ql_dbg(ql_dbg_async, vha, 0x501f,
		    "DCBX Parameters Updated -- %04x %04x %04x.\n",
		    mb[1], mb[2], mb[3]);
		अवरोध;
	हाल MBA_FCF_CONF_ERR:
		ql_dbg(ql_dbg_async, vha, 0x5020,
		    "FCF Configuration Error -- %04x %04x %04x.\n",
		    mb[1], mb[2], mb[3]);
		अवरोध;
	हाल MBA_IDC_NOTIFY:
		अगर (IS_QLA8031(vha->hw) || IS_QLA8044(ha)) अणु
			mb[4] = rd_reg_word(&reg24->mailbox4);
			अगर (((mb[2] & 0x7fff) == MBC_PORT_RESET ||
			    (mb[2] & 0x7fff) == MBC_SET_PORT_CONFIG) &&
			    (mb[4] & INTERNAL_LOOPBACK_MASK) != 0) अणु
				set_bit(ISP_QUIESCE_NEEDED, &vha->dpc_flags);
				/*
				 * Extend loop करोwn समयr since port is active.
				 */
				अगर (atomic_पढ़ो(&vha->loop_state) == LOOP_DOWN)
					atomic_set(&vha->loop_करोwn_समयr,
					    LOOP_DOWN_TIME);
				qla2xxx_wake_dpc(vha);
			पूर्ण
		पूर्ण
		fallthrough;
	हाल MBA_IDC_COMPLETE:
		अगर (ha->notअगरy_lb_portup_comp && !vha->vp_idx)
			complete(&ha->lb_portup_comp);
		fallthrough;
	हाल MBA_IDC_TIME_EXT:
		अगर (IS_QLA81XX(vha->hw) || IS_QLA8031(vha->hw) ||
		    IS_QLA8044(ha))
			qla81xx_idc_event(vha, mb[0], mb[1]);
		अवरोध;

	हाल MBA_IDC_AEN:
		अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			vha->hw_err_cnt++;
			qla27xx_handle_8200_aen(vha, mb);
		पूर्ण अन्यथा अगर (IS_QLA83XX(ha)) अणु
			mb[4] = rd_reg_word(&reg24->mailbox4);
			mb[5] = rd_reg_word(&reg24->mailbox5);
			mb[6] = rd_reg_word(&reg24->mailbox6);
			mb[7] = rd_reg_word(&reg24->mailbox7);
			qla83xx_handle_8200_aen(vha, mb);
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_async, vha, 0x5052,
			    "skip Heartbeat processing mb0-3=[0x%04x] [0x%04x] [0x%04x] [0x%04x]\n",
			    mb[0], mb[1], mb[2], mb[3]);
		पूर्ण
		अवरोध;

	हाल MBA_DPORT_DIAGNOSTICS:
		ql_dbg(ql_dbg_async, vha, 0x5052,
		    "D-Port Diagnostics: %04x %04x %04x %04x\n",
		    mb[0], mb[1], mb[2], mb[3]);
		स_नकल(vha->dport_data, mb, माप(vha->dport_data));
		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			अटल अक्षर *results[] = अणु
			    "start", "done(pass)", "done(error)", "undefined" पूर्ण;
			अटल अक्षर *types[] = अणु
			    "none", "dynamic", "static", "other" पूर्ण;
			uपूर्णांक result = mb[1] >> 0 & 0x3;
			uपूर्णांक type = mb[1] >> 6 & 0x3;
			uपूर्णांक sw = mb[1] >> 15 & 0x1;
			ql_dbg(ql_dbg_async, vha, 0x5052,
			    "D-Port Diagnostics: result=%s type=%s [sw=%u]\n",
			    results[result], types[type], sw);
			अगर (result == 2) अणु
				अटल अक्षर *reasons[] = अणु
				    "reserved", "unexpected reject",
				    "unexpected phase", "retry exceeded",
				    "timed out", "not supported",
				    "user stopped" पूर्ण;
				uपूर्णांक reason = mb[2] >> 0 & 0xf;
				uपूर्णांक phase = mb[2] >> 12 & 0xf;
				ql_dbg(ql_dbg_async, vha, 0x5052,
				    "D-Port Diagnostics: reason=%s phase=%u \n",
				    reason < 7 ? reasons[reason] : "other",
				    phase >> 1);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल MBA_TEMPERATURE_ALERT:
		ql_dbg(ql_dbg_async, vha, 0x505e,
		    "TEMPERATURE ALERT: %04x %04x %04x\n", mb[1], mb[2], mb[3]);
		अवरोध;

	हाल MBA_TRANS_INSERT:
		ql_dbg(ql_dbg_async, vha, 0x5091,
		    "Transceiver Insertion: %04x\n", mb[1]);
		set_bit(DETECT_SFP_CHANGE, &vha->dpc_flags);
		अवरोध;

	हाल MBA_TRANS_REMOVE:
		ql_dbg(ql_dbg_async, vha, 0x5091, "Transceiver Removal\n");
		अवरोध;

	शेष:
		ql_dbg(ql_dbg_async, vha, 0x5057,
		    "Unknown AEN:%04x %04x %04x %04x\n",
		    mb[0], mb[1], mb[2], mb[3]);
	पूर्ण

	qlt_async_event(mb[0], vha, mb);

	अगर (!vha->vp_idx && ha->num_vhosts)
		qla2x00_alert_all_vps(rsp, mb);
पूर्ण

/**
 * qla2x00_process_completed_request() - Process a Fast Post response.
 * @vha: SCSI driver HA context
 * @req: request queue
 * @index: SRB index
 */
व्योम
qla2x00_process_completed_request(काष्ठा scsi_qla_host *vha,
				  काष्ठा req_que *req, uपूर्णांक32_t index)
अणु
	srb_t *sp;
	काष्ठा qla_hw_data *ha = vha->hw;

	/* Validate handle. */
	अगर (index >= req->num_outstanding_cmds) अणु
		ql_log(ql_log_warn, vha, 0x3014,
		    "Invalid SCSI command index (%x).\n", index);

		अगर (IS_P3P_TYPE(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		अन्यथा
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण

	sp = req->outstanding_cmds[index];
	अगर (sp) अणु
		/* Free outstanding command slot. */
		req->outstanding_cmds[index] = शून्य;

		/* Save ISP completion status */
		sp->करोne(sp, DID_OK << 16);
	पूर्ण अन्यथा अणु
		ql_log(ql_log_warn, vha, 0x3016, "Invalid SCSI SRB.\n");

		अगर (IS_P3P_TYPE(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		अन्यथा
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	पूर्ण
पूर्ण

srb_t *
qla2x00_get_sp_from_handle(scsi_qla_host_t *vha, स्थिर अक्षर *func,
    काष्ठा req_que *req, व्योम *iocb)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	sts_entry_t *pkt = iocb;
	srb_t *sp;
	uपूर्णांक16_t index;

	index = LSW(pkt->handle);
	अगर (index >= req->num_outstanding_cmds) अणु
		ql_log(ql_log_warn, vha, 0x5031,
			   "%s: Invalid command index (%x) type %8ph.\n",
			   func, index, iocb);
		अगर (IS_P3P_TYPE(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		अन्यथा
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		वापस शून्य;
	पूर्ण
	sp = req->outstanding_cmds[index];
	अगर (!sp) अणु
		ql_log(ql_log_warn, vha, 0x5032,
			"%s: Invalid completion handle (%x) -- timed-out.\n",
			func, index);
		वापस शून्य;
	पूर्ण
	अगर (sp->handle != index) अणु
		ql_log(ql_log_warn, vha, 0x5033,
			"%s: SRB handle (%x) mismatch %x.\n", func,
			sp->handle, index);
		वापस शून्य;
	पूर्ण

	req->outstanding_cmds[index] = शून्य;
	वापस sp;
पूर्ण

अटल व्योम
qla2x00_mbx_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    काष्ठा mbx_entry *mbx)
अणु
	स्थिर अक्षर func[] = "MBX-IOCB";
	स्थिर अक्षर *type;
	fc_port_t *fcport;
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	uपूर्णांक16_t *data;
	uपूर्णांक16_t status;

	sp = qla2x00_get_sp_from_handle(vha, func, req, mbx);
	अगर (!sp)
		वापस;

	lio = &sp->u.iocb_cmd;
	type = sp->name;
	fcport = sp->fcport;
	data = lio->u.logio.data;

	data[0] = MBS_COMMAND_ERROR;
	data[1] = lio->u.logio.flags & SRB_LOGIN_RETRIED ?
	    QLA_LOGIO_LOGIN_RETRIED : 0;
	अगर (mbx->entry_status) अणु
		ql_dbg(ql_dbg_async, vha, 0x5043,
		    "Async-%s error entry - hdl=%x portid=%02x%02x%02x "
		    "entry-status=%x status=%x state-flag=%x "
		    "status-flags=%x.\n", type, sp->handle,
		    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa, mbx->entry_status,
		    le16_to_cpu(mbx->status), le16_to_cpu(mbx->state_flags),
		    le16_to_cpu(mbx->status_flags));

		ql_dump_buffer(ql_dbg_async + ql_dbg_buffer, vha, 0x5029,
		    mbx, माप(*mbx));

		जाओ logio_करोne;
	पूर्ण

	status = le16_to_cpu(mbx->status);
	अगर (status == 0x30 && sp->type == SRB_LOGIN_CMD &&
	    le16_to_cpu(mbx->mb0) == MBS_COMMAND_COMPLETE)
		status = 0;
	अगर (!status && le16_to_cpu(mbx->mb0) == MBS_COMMAND_COMPLETE) अणु
		ql_dbg(ql_dbg_async, vha, 0x5045,
		    "Async-%s complete - hdl=%x portid=%02x%02x%02x mbx1=%x.\n",
		    type, sp->handle, fcport->d_id.b.करोमुख्य,
		    fcport->d_id.b.area, fcport->d_id.b.al_pa,
		    le16_to_cpu(mbx->mb1));

		data[0] = MBS_COMMAND_COMPLETE;
		अगर (sp->type == SRB_LOGIN_CMD) अणु
			fcport->port_type = FCT_TARGET;
			अगर (le16_to_cpu(mbx->mb1) & BIT_0)
				fcport->port_type = FCT_INITIATOR;
			अन्यथा अगर (le16_to_cpu(mbx->mb1) & BIT_1)
				fcport->flags |= FCF_FCP2_DEVICE;
		पूर्ण
		जाओ logio_करोne;
	पूर्ण

	data[0] = le16_to_cpu(mbx->mb0);
	चयन (data[0]) अणु
	हाल MBS_PORT_ID_USED:
		data[1] = le16_to_cpu(mbx->mb1);
		अवरोध;
	हाल MBS_LOOP_ID_USED:
		अवरोध;
	शेष:
		data[0] = MBS_COMMAND_ERROR;
		अवरोध;
	पूर्ण

	ql_log(ql_log_warn, vha, 0x5046,
	    "Async-%s failed - hdl=%x portid=%02x%02x%02x status=%x "
	    "mb0=%x mb1=%x mb2=%x mb6=%x mb7=%x.\n", type, sp->handle,
	    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area, fcport->d_id.b.al_pa,
	    status, le16_to_cpu(mbx->mb0), le16_to_cpu(mbx->mb1),
	    le16_to_cpu(mbx->mb2), le16_to_cpu(mbx->mb6),
	    le16_to_cpu(mbx->mb7));

logio_करोne:
	sp->करोne(sp, 0);
पूर्ण

अटल व्योम
qla24xx_mbx_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    काष्ठा mbx_24xx_entry *pkt)
अणु
	स्थिर अक्षर func[] = "MBX-IOCB2";
	काष्ठा qla_hw_data *ha = vha->hw;
	srb_t *sp;
	काष्ठा srb_iocb *si;
	u16 sz, i;
	पूर्णांक res;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	अगर (sp->type == SRB_SCSI_CMD ||
	    sp->type == SRB_NVME_CMD ||
	    sp->type == SRB_TM_CMD) अणु
		ql_log(ql_log_warn, vha, 0x509d,
			"Inconsistent event entry type %d\n", sp->type);
		अगर (IS_P3P_TYPE(ha))
			set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
		अन्यथा
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण

	si = &sp->u.iocb_cmd;
	sz = min(ARRAY_SIZE(pkt->mb), ARRAY_SIZE(sp->u.iocb_cmd.u.mbx.in_mb));

	क्रम (i = 0; i < sz; i++)
		si->u.mbx.in_mb[i] = pkt->mb[i];

	res = (si->u.mbx.in_mb[0] & MBS_MASK);

	sp->करोne(sp, res);
पूर्ण

अटल व्योम
qla24xxx_nack_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    काष्ठा nack_to_isp *pkt)
अणु
	स्थिर अक्षर func[] = "nack";
	srb_t *sp;
	पूर्णांक res = 0;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	अगर (pkt->u.isp2x.status != cpu_to_le16(NOTIFY_ACK_SUCCESS))
		res = QLA_FUNCTION_FAILED;

	sp->करोne(sp, res);
पूर्ण

अटल व्योम
qla2x00_ct_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    sts_entry_t *pkt, पूर्णांक iocb_type)
अणु
	स्थिर अक्षर func[] = "CT_IOCB";
	स्थिर अक्षर *type;
	srb_t *sp;
	काष्ठा bsg_job *bsg_job;
	काष्ठा fc_bsg_reply *bsg_reply;
	uपूर्णांक16_t comp_status;
	पूर्णांक res = 0;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	चयन (sp->type) अणु
	हाल SRB_CT_CMD:
	    bsg_job = sp->u.bsg_job;
	    bsg_reply = bsg_job->reply;

	    type = "ct pass-through";

	    comp_status = le16_to_cpu(pkt->comp_status);

	    /*
	     * वापस FC_CTELS_STATUS_OK and leave the decoding of the ELS/CT
	     * fc payload  to the caller
	     */
	    bsg_reply->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	    bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);

	    अगर (comp_status != CS_COMPLETE) अणु
		    अगर (comp_status == CS_DATA_UNDERRUN) अणु
			    res = DID_OK << 16;
			    bsg_reply->reply_payload_rcv_len =
				le16_to_cpu(pkt->rsp_info_len);

			    ql_log(ql_log_warn, vha, 0x5048,
				"CT pass-through-%s error comp_status=0x%x total_byte=0x%x.\n",
				type, comp_status,
				bsg_reply->reply_payload_rcv_len);
		    पूर्ण अन्यथा अणु
			    ql_log(ql_log_warn, vha, 0x5049,
				"CT pass-through-%s error comp_status=0x%x.\n",
				type, comp_status);
			    res = DID_ERROR << 16;
			    bsg_reply->reply_payload_rcv_len = 0;
		    पूर्ण
		    ql_dump_buffer(ql_dbg_async + ql_dbg_buffer, vha, 0x5035,
			pkt, माप(*pkt));
	    पूर्ण अन्यथा अणु
		    res = DID_OK << 16;
		    bsg_reply->reply_payload_rcv_len =
			bsg_job->reply_payload.payload_len;
		    bsg_job->reply_len = 0;
	    पूर्ण
	    अवरोध;
	हाल SRB_CT_PTHRU_CMD:
	    /*
	     * borrowing sts_entry_24xx.comp_status.
	     * same location as ct_entry_24xx.comp_status
	     */
	     res = qla2x00_chk_ms_status(vha, (ms_iocb_entry_t *)pkt,
		 (काष्ठा ct_sns_rsp *)sp->u.iocb_cmd.u.ctarg.rsp,
		 sp->name);
	     अवरोध;
	पूर्ण

	sp->करोne(sp, res);
पूर्ण

अटल व्योम
qla24xx_els_ct_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    काष्ठा sts_entry_24xx *pkt, पूर्णांक iocb_type)
अणु
	काष्ठा els_sts_entry_24xx *ese = (काष्ठा els_sts_entry_24xx *)pkt;
	स्थिर अक्षर func[] = "ELS_CT_IOCB";
	स्थिर अक्षर *type;
	srb_t *sp;
	काष्ठा bsg_job *bsg_job;
	काष्ठा fc_bsg_reply *bsg_reply;
	uपूर्णांक16_t comp_status;
	uपूर्णांक32_t fw_status[3];
	पूर्णांक res;
	काष्ठा srb_iocb *els;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	type = शून्य;
	चयन (sp->type) अणु
	हाल SRB_ELS_CMD_RPT:
	हाल SRB_ELS_CMD_HST:
		type = "els";
		अवरोध;
	हाल SRB_CT_CMD:
		type = "ct pass-through";
		अवरोध;
	हाल SRB_ELS_DCMD:
		type = "Driver ELS logo";
		अगर (iocb_type != ELS_IOCB_TYPE) अणु
			ql_dbg(ql_dbg_user, vha, 0x5047,
			    "Completing %s: (%p) type=%d.\n",
			    type, sp, sp->type);
			sp->करोne(sp, 0);
			वापस;
		पूर्ण
		अवरोध;
	हाल SRB_CT_PTHRU_CMD:
		/* borrowing sts_entry_24xx.comp_status.
		   same location as ct_entry_24xx.comp_status
		 */
		res = qla2x00_chk_ms_status(sp->vha, (ms_iocb_entry_t *)pkt,
			(काष्ठा ct_sns_rsp *)sp->u.iocb_cmd.u.ctarg.rsp,
			sp->name);
		sp->करोne(sp, res);
		वापस;
	शेष:
		ql_dbg(ql_dbg_user, vha, 0x503e,
		    "Unrecognized SRB: (%p) type=%d.\n", sp, sp->type);
		वापस;
	पूर्ण

	comp_status = fw_status[0] = le16_to_cpu(pkt->comp_status);
	fw_status[1] = le32_to_cpu(ese->error_subcode_1);
	fw_status[2] = le32_to_cpu(ese->error_subcode_2);

	अगर (iocb_type == ELS_IOCB_TYPE) अणु
		els = &sp->u.iocb_cmd;
		els->u.els_plogi.fw_status[0] = cpu_to_le32(fw_status[0]);
		els->u.els_plogi.fw_status[1] = cpu_to_le32(fw_status[1]);
		els->u.els_plogi.fw_status[2] = cpu_to_le32(fw_status[2]);
		els->u.els_plogi.comp_status = cpu_to_le16(fw_status[0]);
		अगर (comp_status == CS_COMPLETE) अणु
			res =  DID_OK << 16;
		पूर्ण अन्यथा अणु
			अगर (comp_status == CS_DATA_UNDERRUN) अणु
				res =  DID_OK << 16;
				els->u.els_plogi.len = cpu_to_le16(le32_to_cpu(
					ese->total_byte_count));
			पूर्ण अन्यथा अणु
				els->u.els_plogi.len = 0;
				res = DID_ERROR << 16;
			पूर्ण
		पूर्ण
		ql_dbg(ql_dbg_disc, vha, 0x503f,
		    "ELS IOCB Done -%s hdl=%x comp_status=0x%x error subcode 1=0x%x error subcode 2=0x%x total_byte=0x%x\n",
		    type, sp->handle, comp_status, fw_status[1], fw_status[2],
		    le32_to_cpu(ese->total_byte_count));
		जाओ els_ct_करोne;
	पूर्ण

	/* वापस FC_CTELS_STATUS_OK and leave the decoding of the ELS/CT
	 * fc payload  to the caller
	 */
	bsg_job = sp->u.bsg_job;
	bsg_reply = bsg_job->reply;
	bsg_reply->reply_data.ctels_reply.status = FC_CTELS_STATUS_OK;
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply) + माप(fw_status);

	अगर (comp_status != CS_COMPLETE) अणु
		अगर (comp_status == CS_DATA_UNDERRUN) अणु
			res = DID_OK << 16;
			bsg_reply->reply_payload_rcv_len =
				le32_to_cpu(ese->total_byte_count);

			ql_dbg(ql_dbg_user, vha, 0x503f,
			    "ELS-CT pass-through-%s error hdl=%x comp_status-status=0x%x "
			    "error subcode 1=0x%x error subcode 2=0x%x total_byte = 0x%x.\n",
			    type, sp->handle, comp_status, fw_status[1], fw_status[2],
			    le32_to_cpu(ese->total_byte_count));
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_user, vha, 0x5040,
			    "ELS-CT pass-through-%s error hdl=%x comp_status-status=0x%x "
			    "error subcode 1=0x%x error subcode 2=0x%x.\n",
			    type, sp->handle, comp_status,
			    le32_to_cpu(ese->error_subcode_1),
			    le32_to_cpu(ese->error_subcode_2));
			res = DID_ERROR << 16;
			bsg_reply->reply_payload_rcv_len = 0;
		पूर्ण
		स_नकल(bsg_job->reply + माप(काष्ठा fc_bsg_reply),
		       fw_status, माप(fw_status));
		ql_dump_buffer(ql_dbg_user + ql_dbg_buffer, vha, 0x5056,
		    pkt, माप(*pkt));
	पूर्ण
	अन्यथा अणु
		res =  DID_OK << 16;
		bsg_reply->reply_payload_rcv_len = bsg_job->reply_payload.payload_len;
		bsg_job->reply_len = 0;
	पूर्ण
els_ct_करोne:

	sp->करोne(sp, res);
पूर्ण

अटल व्योम
qla24xx_logio_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    काष्ठा logio_entry_24xx *logio)
अणु
	स्थिर अक्षर func[] = "LOGIO-IOCB";
	स्थिर अक्षर *type;
	fc_port_t *fcport;
	srb_t *sp;
	काष्ठा srb_iocb *lio;
	uपूर्णांक16_t *data;
	uपूर्णांक32_t iop[2];

	sp = qla2x00_get_sp_from_handle(vha, func, req, logio);
	अगर (!sp)
		वापस;

	lio = &sp->u.iocb_cmd;
	type = sp->name;
	fcport = sp->fcport;
	data = lio->u.logio.data;

	data[0] = MBS_COMMAND_ERROR;
	data[1] = lio->u.logio.flags & SRB_LOGIN_RETRIED ?
		QLA_LOGIO_LOGIN_RETRIED : 0;
	अगर (logio->entry_status) अणु
		ql_log(ql_log_warn, fcport->vha, 0x5034,
		    "Async-%s error entry - %8phC hdl=%x"
		    "portid=%02x%02x%02x entry-status=%x.\n",
		    type, fcport->port_name, sp->handle, fcport->d_id.b.करोमुख्य,
		    fcport->d_id.b.area, fcport->d_id.b.al_pa,
		    logio->entry_status);
		ql_dump_buffer(ql_dbg_async + ql_dbg_buffer, vha, 0x504d,
		    logio, माप(*logio));

		जाओ logio_करोne;
	पूर्ण

	अगर (le16_to_cpu(logio->comp_status) == CS_COMPLETE) अणु
		ql_dbg(ql_dbg_async, sp->vha, 0x5036,
		    "Async-%s complete: handle=%x pid=%06x wwpn=%8phC iop0=%x\n",
		    type, sp->handle, fcport->d_id.b24, fcport->port_name,
		    le32_to_cpu(logio->io_parameter[0]));

		vha->hw->exch_starvation = 0;
		data[0] = MBS_COMMAND_COMPLETE;

		अगर (sp->type == SRB_PRLI_CMD) अणु
			lio->u.logio.iop[0] =
			    le32_to_cpu(logio->io_parameter[0]);
			lio->u.logio.iop[1] =
			    le32_to_cpu(logio->io_parameter[1]);
			जाओ logio_करोne;
		पूर्ण

		अगर (sp->type != SRB_LOGIN_CMD)
			जाओ logio_करोne;

		iop[0] = le32_to_cpu(logio->io_parameter[0]);
		अगर (iop[0] & BIT_4) अणु
			fcport->port_type = FCT_TARGET;
			अगर (iop[0] & BIT_8)
				fcport->flags |= FCF_FCP2_DEVICE;
		पूर्ण अन्यथा अगर (iop[0] & BIT_5)
			fcport->port_type = FCT_INITIATOR;

		अगर (iop[0] & BIT_7)
			fcport->flags |= FCF_CONF_COMP_SUPPORTED;

		अगर (logio->io_parameter[7] || logio->io_parameter[8])
			fcport->supported_classes |= FC_COS_CLASS2;
		अगर (logio->io_parameter[9] || logio->io_parameter[10])
			fcport->supported_classes |= FC_COS_CLASS3;

		जाओ logio_करोne;
	पूर्ण

	iop[0] = le32_to_cpu(logio->io_parameter[0]);
	iop[1] = le32_to_cpu(logio->io_parameter[1]);
	lio->u.logio.iop[0] = iop[0];
	lio->u.logio.iop[1] = iop[1];
	चयन (iop[0]) अणु
	हाल LSC_SCODE_PORTID_USED:
		data[0] = MBS_PORT_ID_USED;
		data[1] = LSW(iop[1]);
		अवरोध;
	हाल LSC_SCODE_NPORT_USED:
		data[0] = MBS_LOOP_ID_USED;
		अवरोध;
	हाल LSC_SCODE_CMD_FAILED:
		अगर (iop[1] == 0x0606) अणु
			/*
			 * PLOGI/PRLI Completed. We must have Recv PLOGI/PRLI,
			 * Target side acked.
			 */
			data[0] = MBS_COMMAND_COMPLETE;
			जाओ logio_करोne;
		पूर्ण
		data[0] = MBS_COMMAND_ERROR;
		अवरोध;
	हाल LSC_SCODE_NOXCB:
		vha->hw->exch_starvation++;
		अगर (vha->hw->exch_starvation > 5) अणु
			ql_log(ql_log_warn, vha, 0xd046,
			    "Exchange starvation. Resetting RISC\n");

			vha->hw->exch_starvation = 0;

			अगर (IS_P3P_TYPE(vha->hw))
				set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
			अन्यथा
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण
		fallthrough;
	शेष:
		data[0] = MBS_COMMAND_ERROR;
		अवरोध;
	पूर्ण

	ql_log(ql_log_warn, sp->vha, 0x5037,
	       "Async-%s failed: handle=%x pid=%06x wwpn=%8phC comp_status=%x iop0=%x iop1=%x\n",
	       type, sp->handle, fcport->d_id.b24, fcport->port_name,
	       le16_to_cpu(logio->comp_status),
	       le32_to_cpu(logio->io_parameter[0]),
	       le32_to_cpu(logio->io_parameter[1]));

logio_करोne:
	sp->करोne(sp, 0);
पूर्ण

अटल व्योम
qla24xx_पंचांग_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req, व्योम *tsk)
अणु
	स्थिर अक्षर func[] = "TMF-IOCB";
	स्थिर अक्षर *type;
	fc_port_t *fcport;
	srb_t *sp;
	काष्ठा srb_iocb *iocb;
	काष्ठा sts_entry_24xx *sts = (काष्ठा sts_entry_24xx *)tsk;
	u16 comp_status;

	sp = qla2x00_get_sp_from_handle(vha, func, req, tsk);
	अगर (!sp)
		वापस;

	comp_status = le16_to_cpu(sts->comp_status);
	iocb = &sp->u.iocb_cmd;
	type = sp->name;
	fcport = sp->fcport;
	iocb->u.पंचांगf.data = QLA_SUCCESS;

	अगर (sts->entry_status) अणु
		ql_log(ql_log_warn, fcport->vha, 0x5038,
		    "Async-%s error - hdl=%x entry-status(%x).\n",
		    type, sp->handle, sts->entry_status);
		iocb->u.पंचांगf.data = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (sts->comp_status != cpu_to_le16(CS_COMPLETE)) अणु
		ql_log(ql_log_warn, fcport->vha, 0x5039,
		    "Async-%s error - hdl=%x completion status(%x).\n",
		    type, sp->handle, comp_status);
		iocb->u.पंचांगf.data = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर ((le16_to_cpu(sts->scsi_status) &
	    SS_RESPONSE_INFO_LEN_VALID)) अणु
		अगर (le32_to_cpu(sts->rsp_data_len) < 4) अणु
			ql_log(ql_log_warn, fcport->vha, 0x503b,
			    "Async-%s error - hdl=%x not enough response(%d).\n",
			    type, sp->handle, sts->rsp_data_len);
		पूर्ण अन्यथा अगर (sts->data[3]) अणु
			ql_log(ql_log_warn, fcport->vha, 0x503c,
			    "Async-%s error - hdl=%x response(%x).\n",
			    type, sp->handle, sts->data[3]);
			iocb->u.पंचांगf.data = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	चयन (comp_status) अणु
	हाल CS_PORT_LOGGED_OUT:
	हाल CS_PORT_CONFIG_CHG:
	हाल CS_PORT_BUSY:
	हाल CS_INCOMPLETE:
	हाल CS_PORT_UNAVAILABLE:
	हाल CS_TIMEOUT:
	हाल CS_RESET:
		अगर (atomic_पढ़ो(&fcport->state) == FCS_ONLINE) अणु
			ql_dbg(ql_dbg_disc, fcport->vha, 0x3021,
			       "-Port to be marked lost on fcport=%02x%02x%02x, current port state= %s comp_status %x.\n",
			       fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
			       fcport->d_id.b.al_pa,
			       port_state_str[FCS_ONLINE],
			       comp_status);

			qlt_schedule_sess_क्रम_deletion(fcport);
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	अगर (iocb->u.पंचांगf.data != QLA_SUCCESS)
		ql_dump_buffer(ql_dbg_async + ql_dbg_buffer, sp->vha, 0x5055,
		    sts, माप(*sts));

	sp->करोne(sp, 0);
पूर्ण

अटल व्योम qla24xx_nvme_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
    व्योम *tsk, srb_t *sp)
अणु
	fc_port_t *fcport;
	काष्ठा srb_iocb *iocb;
	काष्ठा sts_entry_24xx *sts = (काष्ठा sts_entry_24xx *)tsk;
	uपूर्णांक16_t        state_flags;
	काष्ठा nvmefc_fcp_req *fd;
	uपूर्णांक16_t        ret = QLA_SUCCESS;
	__le16		comp_status = sts->comp_status;
	पूर्णांक		logit = 0;

	iocb = &sp->u.iocb_cmd;
	fcport = sp->fcport;
	iocb->u.nvme.comp_status = comp_status;
	state_flags  = le16_to_cpu(sts->state_flags);
	fd = iocb->u.nvme.desc;

	अगर (unlikely(iocb->u.nvme.aen_op))
		atomic_dec(&sp->vha->hw->nvme_active_aen_cnt);

	अगर (unlikely(comp_status != CS_COMPLETE))
		logit = 1;

	fd->transferred_length = fd->payload_length -
	    le32_to_cpu(sts->residual_len);

	/*
	 * State flags: Bit 6 and 0.
	 * If 0 is set, we करोn't care about 6.
	 * both हालs resp was dma'd to host buffer
	 * अगर both are 0, that is good path हाल.
	 * अगर six is set and 0 is clear, we need to
	 * copy resp data from status iocb to resp buffer.
	 */
	अगर (!(state_flags & (SF_FCP_RSP_DMA | SF_NVME_ERSP))) अणु
		iocb->u.nvme.rsp_pyld_len = 0;
	पूर्ण अन्यथा अगर ((state_flags & (SF_FCP_RSP_DMA | SF_NVME_ERSP)) ==
			(SF_FCP_RSP_DMA | SF_NVME_ERSP)) अणु
		/* Response alपढ़ोy DMA'd to fd->rspaddr. */
		iocb->u.nvme.rsp_pyld_len = sts->nvme_rsp_pyld_len;
	पूर्ण अन्यथा अगर ((state_flags & SF_FCP_RSP_DMA)) अणु
		/*
		 * Non-zero value in first 12 bytes of NVMe_RSP IU, treat this
		 * as an error.
		 */
		iocb->u.nvme.rsp_pyld_len = 0;
		fd->transferred_length = 0;
		ql_dbg(ql_dbg_io, fcport->vha, 0x307a,
			"Unexpected values in NVMe_RSP IU.\n");
		logit = 1;
	पूर्ण अन्यथा अगर (state_flags & SF_NVME_ERSP) अणु
		uपूर्णांक32_t *inbuf, *outbuf;
		uपूर्णांक16_t iter;

		inbuf = (uपूर्णांक32_t *)&sts->nvme_ersp_data;
		outbuf = (uपूर्णांक32_t *)fd->rspaddr;
		iocb->u.nvme.rsp_pyld_len = sts->nvme_rsp_pyld_len;
		अगर (unlikely(le16_to_cpu(iocb->u.nvme.rsp_pyld_len) >
		    माप(काष्ठा nvme_fc_ersp_iu))) अणु
			अगर (ql_mask_match(ql_dbg_io)) अणु
				WARN_ONCE(1, "Unexpected response payload length %u.\n",
				    iocb->u.nvme.rsp_pyld_len);
				ql_log(ql_log_warn, fcport->vha, 0x5100,
				    "Unexpected response payload length %u.\n",
				    iocb->u.nvme.rsp_pyld_len);
			पूर्ण
			iocb->u.nvme.rsp_pyld_len =
				cpu_to_le16(माप(काष्ठा nvme_fc_ersp_iu));
		पूर्ण
		iter = le16_to_cpu(iocb->u.nvme.rsp_pyld_len) >> 2;
		क्रम (; iter; iter--)
			*outbuf++ = swab32(*inbuf++);
	पूर्ण

	अगर (state_flags & SF_NVME_ERSP) अणु
		काष्ठा nvme_fc_ersp_iu *rsp_iu = fd->rspaddr;
		u32 tgt_xfer_len;

		tgt_xfer_len = be32_to_cpu(rsp_iu->xfrd_len);
		अगर (fd->transferred_length != tgt_xfer_len) अणु
			ql_log(ql_log_warn, fcport->vha, 0x3079,
			       "Dropped frame(s) detected (sent/rcvd=%u/%u).\n",
			       tgt_xfer_len, fd->transferred_length);
			logit = 1;
		पूर्ण अन्यथा अगर (le16_to_cpu(comp_status) == CS_DATA_UNDERRUN) अणु
			/*
			 * Do not log अगर this is just an underflow and there
			 * is no data loss.
			 */
			logit = 0;
		पूर्ण
	पूर्ण

	अगर (unlikely(logit))
		ql_log(ql_log_warn, fcport->vha, 0x5060,
		   "NVME-%s ERR Handling - hdl=%x status(%x) tr_len:%x resid=%x  ox_id=%x\n",
		   sp->name, sp->handle, comp_status,
		   fd->transferred_length, le32_to_cpu(sts->residual_len),
		   sts->ox_id);

	/*
	 * If transport error then Failure (HBA rejects request)
	 * otherwise transport will handle.
	 */
	चयन (le16_to_cpu(comp_status)) अणु
	हाल CS_COMPLETE:
		अवरोध;

	हाल CS_RESET:
	हाल CS_PORT_UNAVAILABLE:
	हाल CS_PORT_LOGGED_OUT:
		fcport->nvme_flag |= NVME_FLAG_RESETTING;
		fallthrough;
	हाल CS_ABORTED:
	हाल CS_PORT_BUSY:
		fd->transferred_length = 0;
		iocb->u.nvme.rsp_pyld_len = 0;
		ret = QLA_ABORTED;
		अवरोध;
	हाल CS_DATA_UNDERRUN:
		अवरोध;
	शेष:
		ret = QLA_FUNCTION_FAILED;
		अवरोध;
	पूर्ण
	sp->करोne(sp, ret);
पूर्ण

अटल व्योम qla_ctrlvp_completed(scsi_qla_host_t *vha, काष्ठा req_que *req,
    काष्ठा vp_ctrl_entry_24xx *vce)
अणु
	स्थिर अक्षर func[] = "CTRLVP-IOCB";
	srb_t *sp;
	पूर्णांक rval = QLA_SUCCESS;

	sp = qla2x00_get_sp_from_handle(vha, func, req, vce);
	अगर (!sp)
		वापस;

	अगर (vce->entry_status != 0) अणु
		ql_dbg(ql_dbg_vport, vha, 0x10c4,
		    "%s: Failed to complete IOCB -- error status (%x)\n",
		    sp->name, vce->entry_status);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (vce->comp_status != cpu_to_le16(CS_COMPLETE)) अणु
		ql_dbg(ql_dbg_vport, vha, 0x10c5,
		    "%s: Failed to complete IOCB -- completion status (%x) vpidx %x\n",
		    sp->name, le16_to_cpu(vce->comp_status),
		    le16_to_cpu(vce->vp_idx_failed));
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_vport, vha, 0x10c6,
		    "Done %s.\n", __func__);
	पूर्ण

	sp->rc = rval;
	sp->करोne(sp, rval);
पूर्ण

/* Process a single response queue entry. */
अटल व्योम qla2x00_process_response_entry(काष्ठा scsi_qla_host *vha,
					   काष्ठा rsp_que *rsp,
					   sts_entry_t *pkt)
अणु
	sts21_entry_t *sts21_entry;
	sts22_entry_t *sts22_entry;
	uपूर्णांक16_t handle_cnt;
	uपूर्णांक16_t cnt;

	चयन (pkt->entry_type) अणु
	हाल STATUS_TYPE:
		qla2x00_status_entry(vha, rsp, pkt);
		अवरोध;
	हाल STATUS_TYPE_21:
		sts21_entry = (sts21_entry_t *)pkt;
		handle_cnt = sts21_entry->handle_count;
		क्रम (cnt = 0; cnt < handle_cnt; cnt++)
			qla2x00_process_completed_request(vha, rsp->req,
						sts21_entry->handle[cnt]);
		अवरोध;
	हाल STATUS_TYPE_22:
		sts22_entry = (sts22_entry_t *)pkt;
		handle_cnt = sts22_entry->handle_count;
		क्रम (cnt = 0; cnt < handle_cnt; cnt++)
			qla2x00_process_completed_request(vha, rsp->req,
						sts22_entry->handle[cnt]);
		अवरोध;
	हाल STATUS_CONT_TYPE:
		qla2x00_status_cont_entry(rsp, (sts_cont_entry_t *)pkt);
		अवरोध;
	हाल MBX_IOCB_TYPE:
		qla2x00_mbx_iocb_entry(vha, rsp->req, (काष्ठा mbx_entry *)pkt);
		अवरोध;
	हाल CT_IOCB_TYPE:
		qla2x00_ct_entry(vha, rsp->req, pkt, CT_IOCB_TYPE);
		अवरोध;
	शेष:
		/* Type Not Supported. */
		ql_log(ql_log_warn, vha, 0x504a,
		       "Received unknown response pkt type %x entry status=%x.\n",
		       pkt->entry_type, pkt->entry_status);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * qla2x00_process_response_queue() - Process response queue entries.
 * @rsp: response queue
 */
व्योम
qla2x00_process_response_queue(काष्ठा rsp_que *rsp)
अणु
	काष्ठा scsi_qla_host *vha;
	काष्ठा qla_hw_data *ha = rsp->hw;
	काष्ठा device_reg_2xxx __iomem *reg = &ha->iobase->isp;
	sts_entry_t	*pkt;

	vha = pci_get_drvdata(ha->pdev);

	अगर (!vha->flags.online)
		वापस;

	जबतक (rsp->ring_ptr->signature != RESPONSE_PROCESSED) अणु
		pkt = (sts_entry_t *)rsp->ring_ptr;

		rsp->ring_index++;
		अगर (rsp->ring_index == rsp->length) अणु
			rsp->ring_index = 0;
			rsp->ring_ptr = rsp->ring;
		पूर्ण अन्यथा अणु
			rsp->ring_ptr++;
		पूर्ण

		अगर (pkt->entry_status != 0) अणु
			qla2x00_error_entry(vha, rsp, pkt);
			((response_t *)pkt)->signature = RESPONSE_PROCESSED;
			wmb();
			जारी;
		पूर्ण

		qla2x00_process_response_entry(vha, rsp, pkt);
		((response_t *)pkt)->signature = RESPONSE_PROCESSED;
		wmb();
	पूर्ण

	/* Adjust ring index */
	wrt_reg_word(ISP_RSP_Q_OUT(ha, reg), rsp->ring_index);
पूर्ण

अटल अंतरभूत व्योम
qla2x00_handle_sense(srb_t *sp, uपूर्णांक8_t *sense_data, uपूर्णांक32_t par_sense_len,
		     uपूर्णांक32_t sense_len, काष्ठा rsp_que *rsp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा scsi_cmnd *cp = GET_CMD_SP(sp);
	uपूर्णांक32_t track_sense_len;

	अगर (sense_len >= SCSI_SENSE_BUFFERSIZE)
		sense_len = SCSI_SENSE_BUFFERSIZE;

	SET_CMD_SENSE_LEN(sp, sense_len);
	SET_CMD_SENSE_PTR(sp, cp->sense_buffer);
	track_sense_len = sense_len;

	अगर (sense_len > par_sense_len)
		sense_len = par_sense_len;

	स_नकल(cp->sense_buffer, sense_data, sense_len);

	SET_CMD_SENSE_PTR(sp, cp->sense_buffer + sense_len);
	track_sense_len -= sense_len;
	SET_CMD_SENSE_LEN(sp, track_sense_len);

	अगर (track_sense_len != 0) अणु
		rsp->status_srb = sp;
		cp->result = res;
	पूर्ण

	अगर (sense_len) अणु
		ql_dbg(ql_dbg_io + ql_dbg_buffer, vha, 0x301c,
		    "Check condition Sense data, nexus%ld:%d:%llu cmd=%p.\n",
		    sp->vha->host_no, cp->device->id, cp->device->lun,
		    cp);
		ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x302b,
		    cp->sense_buffer, sense_len);
	पूर्ण
पूर्ण

काष्ठा scsi_dअगर_tuple अणु
	__be16 guard;       /* Checksum */
	__be16 app_tag;         /* APPL identअगरier */
	__be32 ref_tag;         /* Target LBA or indirect LBA */
पूर्ण;

/*
 * Checks the guard or meta-data क्रम the type of error
 * detected by the HBA. In हाल of errors, we set the
 * ASC/ASCQ fields in the sense buffer with ILLEGAL_REQUEST
 * to indicate to the kernel that the HBA detected error.
 */
अटल अंतरभूत पूर्णांक
qla2x00_handle_dअगर_error(srb_t *sp, काष्ठा sts_entry_24xx *sts24)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	uपूर्णांक8_t		*ap = &sts24->data[12];
	uपूर्णांक8_t		*ep = &sts24->data[20];
	uपूर्णांक32_t	e_ref_tag, a_ref_tag;
	uपूर्णांक16_t	e_app_tag, a_app_tag;
	uपूर्णांक16_t	e_guard, a_guard;

	/*
	 * swab32 of the "data" field in the beginning of qla2x00_status_entry()
	 * would make guard field appear at offset 2
	 */
	a_guard   = get_unaligned_le16(ap + 2);
	a_app_tag = get_unaligned_le16(ap + 0);
	a_ref_tag = get_unaligned_le32(ap + 4);
	e_guard   = get_unaligned_le16(ep + 2);
	e_app_tag = get_unaligned_le16(ep + 0);
	e_ref_tag = get_unaligned_le32(ep + 4);

	ql_dbg(ql_dbg_io, vha, 0x3023,
	    "iocb(s) %p Returned STATUS.\n", sts24);

	ql_dbg(ql_dbg_io, vha, 0x3024,
	    "DIF ERROR in cmd 0x%x lba 0x%llx act ref"
	    " tag=0x%x, exp ref_tag=0x%x, act app tag=0x%x, exp app"
	    " tag=0x%x, act guard=0x%x, exp guard=0x%x.\n",
	    cmd->cmnd[0], (u64)scsi_get_lba(cmd), a_ref_tag, e_ref_tag,
	    a_app_tag, e_app_tag, a_guard, e_guard);

	/*
	 * Ignore sector अगर:
	 * For type     3: ref & app tag is all 'f's
	 * For type 0,1,2: app tag is all 'f's
	 */
	अगर (a_app_tag == be16_to_cpu(T10_PI_APP_ESCAPE) &&
	    (scsi_get_prot_type(cmd) != SCSI_PROT_DIF_TYPE3 ||
	     a_ref_tag == be32_to_cpu(T10_PI_REF_ESCAPE))) अणु
		uपूर्णांक32_t blocks_करोne, resid;
		sector_t lba_s = scsi_get_lba(cmd);

		/* 2TB boundary हाल covered स्वतःmatically with this */
		blocks_करोne = e_ref_tag - (uपूर्णांक32_t)lba_s + 1;

		resid = scsi_bufflen(cmd) - (blocks_करोne *
		    cmd->device->sector_size);

		scsi_set_resid(cmd, resid);
		cmd->result = DID_OK << 16;

		/* Update protection tag */
		अगर (scsi_prot_sg_count(cmd)) अणु
			uपूर्णांक32_t i, j = 0, k = 0, num_ent;
			काष्ठा scatterlist *sg;
			काष्ठा t10_pi_tuple *spt;

			/* Patch the corresponding protection tags */
			scsi_क्रम_each_prot_sg(cmd, sg,
			    scsi_prot_sg_count(cmd), i) अणु
				num_ent = sg_dma_len(sg) / 8;
				अगर (k + num_ent < blocks_करोne) अणु
					k += num_ent;
					जारी;
				पूर्ण
				j = blocks_करोne - k - 1;
				k = blocks_करोne;
				अवरोध;
			पूर्ण

			अगर (k != blocks_करोne) अणु
				ql_log(ql_log_warn, vha, 0x302f,
				    "unexpected tag values tag:lba=%x:%llx)\n",
				    e_ref_tag, (अचिन्हित दीर्घ दीर्घ)lba_s);
				वापस 1;
			पूर्ण

			spt = page_address(sg_page(sg)) + sg->offset;
			spt += j;

			spt->app_tag = T10_PI_APP_ESCAPE;
			अगर (scsi_get_prot_type(cmd) == SCSI_PROT_DIF_TYPE3)
				spt->ref_tag = T10_PI_REF_ESCAPE;
		पूर्ण

		वापस 0;
	पूर्ण

	/* check guard */
	अगर (e_guard != a_guard) अणु
		scsi_build_sense_buffer(1, cmd->sense_buffer, ILLEGAL_REQUEST,
		    0x10, 0x1);
		set_driver_byte(cmd, DRIVER_SENSE);
		set_host_byte(cmd, DID_ABORT);
		cmd->result |= SAM_STAT_CHECK_CONDITION;
		वापस 1;
	पूर्ण

	/* check ref tag */
	अगर (e_ref_tag != a_ref_tag) अणु
		scsi_build_sense_buffer(1, cmd->sense_buffer, ILLEGAL_REQUEST,
		    0x10, 0x3);
		set_driver_byte(cmd, DRIVER_SENSE);
		set_host_byte(cmd, DID_ABORT);
		cmd->result |= SAM_STAT_CHECK_CONDITION;
		वापस 1;
	पूर्ण

	/* check appl tag */
	अगर (e_app_tag != a_app_tag) अणु
		scsi_build_sense_buffer(1, cmd->sense_buffer, ILLEGAL_REQUEST,
		    0x10, 0x2);
		set_driver_byte(cmd, DRIVER_SENSE);
		set_host_byte(cmd, DID_ABORT);
		cmd->result |= SAM_STAT_CHECK_CONDITION;
		वापस 1;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम
qla25xx_process_bidir_status_iocb(scsi_qla_host_t *vha, व्योम *pkt,
				  काष्ठा req_que *req, uपूर्णांक32_t index)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	srb_t *sp;
	uपूर्णांक16_t	comp_status;
	uपूर्णांक16_t	scsi_status;
	uपूर्णांक16_t thपढ़ो_id;
	uपूर्णांक32_t rval = EXT_STATUS_OK;
	काष्ठा bsg_job *bsg_job = शून्य;
	काष्ठा fc_bsg_request *bsg_request;
	काष्ठा fc_bsg_reply *bsg_reply;
	sts_entry_t *sts = pkt;
	काष्ठा sts_entry_24xx *sts24 = pkt;

	/* Validate handle. */
	अगर (index >= req->num_outstanding_cmds) अणु
		ql_log(ql_log_warn, vha, 0x70af,
		    "Invalid SCSI completion handle 0x%x.\n", index);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण

	sp = req->outstanding_cmds[index];
	अगर (!sp) अणु
		ql_log(ql_log_warn, vha, 0x70b0,
		    "Req:%d: Invalid ISP SCSI completion handle(0x%x)\n",
		    req->id, index);

		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		वापस;
	पूर्ण

	/* Free outstanding command slot. */
	req->outstanding_cmds[index] = शून्य;
	bsg_job = sp->u.bsg_job;
	bsg_request = bsg_job->request;
	bsg_reply = bsg_job->reply;

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		comp_status = le16_to_cpu(sts24->comp_status);
		scsi_status = le16_to_cpu(sts24->scsi_status) & SS_MASK;
	पूर्ण अन्यथा अणु
		comp_status = le16_to_cpu(sts->comp_status);
		scsi_status = le16_to_cpu(sts->scsi_status) & SS_MASK;
	पूर्ण

	thपढ़ो_id = bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];
	चयन (comp_status) अणु
	हाल CS_COMPLETE:
		अगर (scsi_status == 0) अणु
			bsg_reply->reply_payload_rcv_len =
					bsg_job->reply_payload.payload_len;
			vha->qla_stats.input_bytes +=
				bsg_reply->reply_payload_rcv_len;
			vha->qla_stats.input_requests++;
			rval = EXT_STATUS_OK;
		पूर्ण
		जाओ करोne;

	हाल CS_DATA_OVERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b1,
		    "Command completed with data overrun thread_id=%d\n",
		    thपढ़ो_id);
		rval = EXT_STATUS_DATA_OVERRUN;
		अवरोध;

	हाल CS_DATA_UNDERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b2,
		    "Command completed with data underrun thread_id=%d\n",
		    thपढ़ो_id);
		rval = EXT_STATUS_DATA_UNDERRUN;
		अवरोध;
	हाल CS_BIसूची_RD_OVERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b3,
		    "Command completed with read data overrun thread_id=%d\n",
		    thपढ़ो_id);
		rval = EXT_STATUS_DATA_OVERRUN;
		अवरोध;

	हाल CS_BIसूची_RD_WR_OVERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b4,
		    "Command completed with read and write data overrun "
		    "thread_id=%d\n", thपढ़ो_id);
		rval = EXT_STATUS_DATA_OVERRUN;
		अवरोध;

	हाल CS_BIसूची_RD_OVERRUN_WR_UNDERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b5,
		    "Command completed with read data over and write data "
		    "underrun thread_id=%d\n", thपढ़ो_id);
		rval = EXT_STATUS_DATA_OVERRUN;
		अवरोध;

	हाल CS_BIसूची_RD_UNDERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b6,
		    "Command completed with read data underrun "
		    "thread_id=%d\n", thपढ़ो_id);
		rval = EXT_STATUS_DATA_UNDERRUN;
		अवरोध;

	हाल CS_BIसूची_RD_UNDERRUN_WR_OVERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b7,
		    "Command completed with read data under and write data "
		    "overrun thread_id=%d\n", thपढ़ो_id);
		rval = EXT_STATUS_DATA_UNDERRUN;
		अवरोध;

	हाल CS_BIसूची_RD_WR_UNDERRUN:
		ql_dbg(ql_dbg_user, vha, 0x70b8,
		    "Command completed with read and write data underrun "
		    "thread_id=%d\n", thपढ़ो_id);
		rval = EXT_STATUS_DATA_UNDERRUN;
		अवरोध;

	हाल CS_BIसूची_DMA:
		ql_dbg(ql_dbg_user, vha, 0x70b9,
		    "Command completed with data DMA error thread_id=%d\n",
		    thपढ़ो_id);
		rval = EXT_STATUS_DMA_ERR;
		अवरोध;

	हाल CS_TIMEOUT:
		ql_dbg(ql_dbg_user, vha, 0x70ba,
		    "Command completed with timeout thread_id=%d\n",
		    thपढ़ो_id);
		rval = EXT_STATUS_TIMEOUT;
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_user, vha, 0x70bb,
		    "Command completed with completion status=0x%x "
		    "thread_id=%d\n", comp_status, thपढ़ो_id);
		rval = EXT_STATUS_ERR;
		अवरोध;
	पूर्ण
	bsg_reply->reply_payload_rcv_len = 0;

करोne:
	/* Return the venकरोr specअगरic reply to API */
	bsg_reply->reply_data.venकरोr_reply.venकरोr_rsp[0] = rval;
	bsg_job->reply_len = माप(काष्ठा fc_bsg_reply);
	/* Always वापस DID_OK, bsg will send the venकरोr specअगरic response
	 * in this हाल only */
	sp->करोne(sp, DID_OK << 16);

पूर्ण

/**
 * qla2x00_status_entry() - Process a Status IOCB entry.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 * @pkt: Entry poपूर्णांकer
 */
अटल व्योम
qla2x00_status_entry(scsi_qla_host_t *vha, काष्ठा rsp_que *rsp, व्योम *pkt)
अणु
	srb_t		*sp;
	fc_port_t	*fcport;
	काष्ठा scsi_cmnd *cp;
	sts_entry_t *sts = pkt;
	काष्ठा sts_entry_24xx *sts24 = pkt;
	uपूर्णांक16_t	comp_status;
	uपूर्णांक16_t	scsi_status;
	uपूर्णांक16_t	ox_id;
	uपूर्णांक8_t		lscsi_status;
	पूर्णांक32_t		resid;
	uपूर्णांक32_t sense_len, par_sense_len, rsp_info_len, resid_len,
	    fw_resid_len;
	uपूर्णांक8_t		*rsp_info, *sense_data;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t handle;
	uपूर्णांक16_t que;
	काष्ठा req_que *req;
	पूर्णांक logit = 1;
	पूर्णांक res = 0;
	uपूर्णांक16_t state_flags = 0;
	uपूर्णांक16_t sts_qual = 0;

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		comp_status = le16_to_cpu(sts24->comp_status);
		scsi_status = le16_to_cpu(sts24->scsi_status) & SS_MASK;
		state_flags = le16_to_cpu(sts24->state_flags);
	पूर्ण अन्यथा अणु
		comp_status = le16_to_cpu(sts->comp_status);
		scsi_status = le16_to_cpu(sts->scsi_status) & SS_MASK;
	पूर्ण
	handle = (uपूर्णांक32_t) LSW(sts->handle);
	que = MSW(sts->handle);
	req = ha->req_q_map[que];

	/* Check क्रम invalid queue poपूर्णांकer */
	अगर (req == शून्य ||
	    que >= find_first_zero_bit(ha->req_qid_map, ha->max_req_queues)) अणु
		ql_dbg(ql_dbg_io, vha, 0x3059,
		    "Invalid status handle (0x%x): Bad req pointer. req=%p, "
		    "que=%u.\n", sts->handle, req, que);
		वापस;
	पूर्ण

	/* Validate handle. */
	अगर (handle < req->num_outstanding_cmds) अणु
		sp = req->outstanding_cmds[handle];
		अगर (!sp) अणु
			ql_dbg(ql_dbg_io, vha, 0x3075,
			    "%s(%ld): Already returned command for status handle (0x%x).\n",
			    __func__, vha->host_no, sts->handle);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_io, vha, 0x3017,
		    "Invalid status handle, out of range (0x%x).\n",
		    sts->handle);

		अगर (!test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) अणु
			अगर (IS_P3P_TYPE(ha))
				set_bit(FCOE_CTX_RESET_NEEDED, &vha->dpc_flags);
			अन्यथा
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
		पूर्ण
		वापस;
	पूर्ण
	qla_put_iocbs(sp->qpair, &sp->iores);

	अगर (sp->cmd_type != TYPE_SRB) अणु
		req->outstanding_cmds[handle] = शून्य;
		ql_dbg(ql_dbg_io, vha, 0x3015,
		    "Unknown sp->cmd_type %x %p).\n",
		    sp->cmd_type, sp);
		वापस;
	पूर्ण

	/* NVME completion. */
	अगर (sp->type == SRB_NVME_CMD) अणु
		req->outstanding_cmds[handle] = शून्य;
		qla24xx_nvme_iocb_entry(vha, req, pkt, sp);
		वापस;
	पूर्ण

	अगर (unlikely((state_flags & BIT_1) && (sp->type == SRB_BIDI_CMD))) अणु
		qla25xx_process_bidir_status_iocb(vha, pkt, req, handle);
		वापस;
	पूर्ण

	/* Task Management completion. */
	अगर (sp->type == SRB_TM_CMD) अणु
		qla24xx_पंचांग_iocb_entry(vha, req, pkt);
		वापस;
	पूर्ण

	/* Fast path completion. */
	अगर (comp_status == CS_COMPLETE && scsi_status == 0) अणु
		qla2x00_process_completed_request(vha, req, handle);

		वापस;
	पूर्ण

	req->outstanding_cmds[handle] = शून्य;
	cp = GET_CMD_SP(sp);
	अगर (cp == शून्य) अणु
		ql_dbg(ql_dbg_io, vha, 0x3018,
		    "Command already returned (0x%x/%p).\n",
		    sts->handle, sp);

		वापस;
	पूर्ण

	lscsi_status = scsi_status & STATUS_MASK;

	fcport = sp->fcport;

	ox_id = 0;
	sense_len = par_sense_len = rsp_info_len = resid_len =
	    fw_resid_len = 0;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		अगर (scsi_status & SS_SENSE_LEN_VALID)
			sense_len = le32_to_cpu(sts24->sense_len);
		अगर (scsi_status & SS_RESPONSE_INFO_LEN_VALID)
			rsp_info_len = le32_to_cpu(sts24->rsp_data_len);
		अगर (scsi_status & (SS_RESIDUAL_UNDER | SS_RESIDUAL_OVER))
			resid_len = le32_to_cpu(sts24->rsp_residual_count);
		अगर (comp_status == CS_DATA_UNDERRUN)
			fw_resid_len = le32_to_cpu(sts24->residual_len);
		rsp_info = sts24->data;
		sense_data = sts24->data;
		host_to_fcp_swap(sts24->data, माप(sts24->data));
		ox_id = le16_to_cpu(sts24->ox_id);
		par_sense_len = माप(sts24->data);
		sts_qual = le16_to_cpu(sts24->status_qualअगरier);
	पूर्ण अन्यथा अणु
		अगर (scsi_status & SS_SENSE_LEN_VALID)
			sense_len = le16_to_cpu(sts->req_sense_length);
		अगर (scsi_status & SS_RESPONSE_INFO_LEN_VALID)
			rsp_info_len = le16_to_cpu(sts->rsp_info_len);
		resid_len = le32_to_cpu(sts->residual_length);
		rsp_info = sts->rsp_info;
		sense_data = sts->req_sense_data;
		par_sense_len = माप(sts->req_sense_data);
	पूर्ण

	/* Check क्रम any FCP transport errors. */
	अगर (scsi_status & SS_RESPONSE_INFO_LEN_VALID) अणु
		/* Sense data lies beyond any FCP RESPONSE data. */
		अगर (IS_FWI2_CAPABLE(ha)) अणु
			sense_data += rsp_info_len;
			par_sense_len -= rsp_info_len;
		पूर्ण
		अगर (rsp_info_len > 3 && rsp_info[3]) अणु
			ql_dbg(ql_dbg_io, fcport->vha, 0x3019,
			    "FCP I/O protocol failure (0x%x/0x%x).\n",
			    rsp_info_len, rsp_info[3]);

			res = DID_BUS_BUSY << 16;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Check क्रम overrun. */
	अगर (IS_FWI2_CAPABLE(ha) && comp_status == CS_COMPLETE &&
	    scsi_status & SS_RESIDUAL_OVER)
		comp_status = CS_DATA_OVERRUN;

	/*
	 * Check retry_delay_समयr value अगर we receive a busy or
	 * queue full.
	 */
	अगर (unlikely(lscsi_status == SAM_STAT_TASK_SET_FULL ||
		     lscsi_status == SAM_STAT_BUSY))
		qla2x00_set_retry_delay_बारtamp(fcport, sts_qual);

	/*
	 * Based on Host and scsi status generate status code क्रम Linux
	 */
	चयन (comp_status) अणु
	हाल CS_COMPLETE:
	हाल CS_QUEUE_FULL:
		अगर (scsi_status == 0) अणु
			res = DID_OK << 16;
			अवरोध;
		पूर्ण
		अगर (scsi_status & (SS_RESIDUAL_UNDER | SS_RESIDUAL_OVER)) अणु
			resid = resid_len;
			scsi_set_resid(cp, resid);

			अगर (!lscsi_status &&
			    ((अचिन्हित)(scsi_bufflen(cp) - resid) <
			     cp->underflow)) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x301a,
				    "Mid-layer underflow detected (0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16;
				अवरोध;
			पूर्ण
		पूर्ण
		res = DID_OK << 16 | lscsi_status;

		अगर (lscsi_status == SAM_STAT_TASK_SET_FULL) अणु
			ql_dbg(ql_dbg_io, fcport->vha, 0x301b,
			    "QUEUE FULL detected.\n");
			अवरोध;
		पूर्ण
		logit = 0;
		अगर (lscsi_status != SS_CHECK_CONDITION)
			अवरोध;

		स_रखो(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		अगर (!(scsi_status & SS_SENSE_LEN_VALID))
			अवरोध;

		qla2x00_handle_sense(sp, sense_data, par_sense_len, sense_len,
		    rsp, res);
		अवरोध;

	हाल CS_DATA_UNDERRUN:
		/* Use F/W calculated residual length. */
		resid = IS_FWI2_CAPABLE(ha) ? fw_resid_len : resid_len;
		scsi_set_resid(cp, resid);
		अगर (scsi_status & SS_RESIDUAL_UNDER) अणु
			अगर (IS_FWI2_CAPABLE(ha) && fw_resid_len != resid_len) अणु
				ql_log(ql_log_warn, fcport->vha, 0x301d,
				       "Dropped frame(s) detected (0x%x of 0x%x bytes).\n",
				       resid, scsi_bufflen(cp));

				vha->पूर्णांकerface_err_cnt++;

				res = DID_ERROR << 16 | lscsi_status;
				जाओ check_scsi_status;
			पूर्ण

			अगर (!lscsi_status &&
			    ((अचिन्हित)(scsi_bufflen(cp) - resid) <
			    cp->underflow)) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x301e,
				    "Mid-layer underflow detected (0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (lscsi_status != SAM_STAT_TASK_SET_FULL &&
			    lscsi_status != SAM_STAT_BUSY) अणु
			/*
			 * scsi status of task set and busy are considered to be
			 * task not completed.
			 */

			ql_log(ql_log_warn, fcport->vha, 0x301f,
			       "Dropped frame(s) detected (0x%x of 0x%x bytes).\n",
			       resid, scsi_bufflen(cp));

			vha->पूर्णांकerface_err_cnt++;

			res = DID_ERROR << 16 | lscsi_status;
			जाओ check_scsi_status;
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_io, fcport->vha, 0x3030,
			    "scsi_status: 0x%x, lscsi_status: 0x%x\n",
			    scsi_status, lscsi_status);
		पूर्ण

		res = DID_OK << 16 | lscsi_status;
		logit = 0;

check_scsi_status:
		/*
		 * Check to see अगर SCSI Status is non zero. If so report SCSI
		 * Status.
		 */
		अगर (lscsi_status != 0) अणु
			अगर (lscsi_status == SAM_STAT_TASK_SET_FULL) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x3020,
				    "QUEUE FULL detected.\n");
				logit = 1;
				अवरोध;
			पूर्ण
			अगर (lscsi_status != SS_CHECK_CONDITION)
				अवरोध;

			स_रखो(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			अगर (!(scsi_status & SS_SENSE_LEN_VALID))
				अवरोध;

			qla2x00_handle_sense(sp, sense_data, par_sense_len,
			    sense_len, rsp, res);
		पूर्ण
		अवरोध;

	हाल CS_PORT_LOGGED_OUT:
	हाल CS_PORT_CONFIG_CHG:
	हाल CS_PORT_BUSY:
	हाल CS_INCOMPLETE:
	हाल CS_PORT_UNAVAILABLE:
	हाल CS_TIMEOUT:
	हाल CS_RESET:

		/*
		 * We are going to have the fc class block the rport
		 * जबतक we try to recover so inकाष्ठा the mid layer
		 * to requeue until the class decides how to handle this.
		 */
		res = DID_TRANSPORT_DISRUPTED << 16;

		अगर (comp_status == CS_TIMEOUT) अणु
			अगर (IS_FWI2_CAPABLE(ha))
				अवरोध;
			अन्यथा अगर ((le16_to_cpu(sts->status_flags) &
			    SF_LOGOUT_SENT) == 0)
				अवरोध;
		पूर्ण

		अगर (atomic_पढ़ो(&fcport->state) == FCS_ONLINE) अणु
			ql_dbg(ql_dbg_disc, fcport->vha, 0x3021,
				"Port to be marked lost on fcport=%02x%02x%02x, current "
				"port state= %s comp_status %x.\n", fcport->d_id.b.करोमुख्य,
				fcport->d_id.b.area, fcport->d_id.b.al_pa,
				port_state_str[FCS_ONLINE],
				comp_status);

			qlt_schedule_sess_क्रम_deletion(fcport);
		पूर्ण

		अवरोध;

	हाल CS_ABORTED:
		res = DID_RESET << 16;
		अवरोध;

	हाल CS_DIF_ERROR:
		logit = qla2x00_handle_dअगर_error(sp, sts24);
		res = cp->result;
		अवरोध;

	हाल CS_TRANSPORT:
		res = DID_ERROR << 16;
		vha->hw_err_cnt++;

		अगर (!IS_PI_SPLIT_DET_CAPABLE(ha))
			अवरोध;

		अगर (state_flags & BIT_4)
			scmd_prपूर्णांकk(KERN_WARNING, cp,
			    "Unsupported device '%s' found.\n",
			    cp->device->venकरोr);
		अवरोध;

	हाल CS_DMA:
		ql_log(ql_log_info, fcport->vha, 0x3022,
		    "CS_DMA error: 0x%x-0x%x (0x%x) nexus=%ld:%d:%llu portid=%06x oxid=0x%x cdb=%10phN len=0x%x rsp_info=0x%x resid=0x%x fw_resid=0x%x sp=%p cp=%p.\n",
		    comp_status, scsi_status, res, vha->host_no,
		    cp->device->id, cp->device->lun, fcport->d_id.b24,
		    ox_id, cp->cmnd, scsi_bufflen(cp), rsp_info_len,
		    resid_len, fw_resid_len, sp, cp);
		ql_dump_buffer(ql_dbg_tgt + ql_dbg_verbose, vha, 0xe0ee,
		    pkt, माप(*sts24));
		res = DID_ERROR << 16;
		vha->hw_err_cnt++;
		अवरोध;
	शेष:
		res = DID_ERROR << 16;
		अवरोध;
	पूर्ण

out:
	अगर (logit)
		ql_log(ql_log_warn, fcport->vha, 0x3022,
		       "FCP command status: 0x%x-0x%x (0x%x) nexus=%ld:%d:%llu portid=%02x%02x%02x oxid=0x%x cdb=%10phN len=0x%x rsp_info=0x%x resid=0x%x fw_resid=0x%x sp=%p cp=%p.\n",
		       comp_status, scsi_status, res, vha->host_no,
		       cp->device->id, cp->device->lun, fcport->d_id.b.करोमुख्य,
		       fcport->d_id.b.area, fcport->d_id.b.al_pa, ox_id,
		       cp->cmnd, scsi_bufflen(cp), rsp_info_len,
		       resid_len, fw_resid_len, sp, cp);

	अगर (rsp->status_srb == शून्य)
		sp->करोne(sp, res);
पूर्ण

/**
 * qla2x00_status_cont_entry() - Process a Status Continuations entry.
 * @rsp: response queue
 * @pkt: Entry poपूर्णांकer
 *
 * Extended sense data.
 */
अटल व्योम
qla2x00_status_cont_entry(काष्ठा rsp_que *rsp, sts_cont_entry_t *pkt)
अणु
	uपूर्णांक8_t	sense_sz = 0;
	काष्ठा qla_hw_data *ha = rsp->hw;
	काष्ठा scsi_qla_host *vha = pci_get_drvdata(ha->pdev);
	srb_t *sp = rsp->status_srb;
	काष्ठा scsi_cmnd *cp;
	uपूर्णांक32_t sense_len;
	uपूर्णांक8_t *sense_ptr;

	अगर (!sp || !GET_CMD_SENSE_LEN(sp))
		वापस;

	sense_len = GET_CMD_SENSE_LEN(sp);
	sense_ptr = GET_CMD_SENSE_PTR(sp);

	cp = GET_CMD_SP(sp);
	अगर (cp == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x3025,
		    "cmd is NULL: already returned to OS (sp=%p).\n", sp);

		rsp->status_srb = शून्य;
		वापस;
	पूर्ण

	अगर (sense_len > माप(pkt->data))
		sense_sz = माप(pkt->data);
	अन्यथा
		sense_sz = sense_len;

	/* Move sense data. */
	अगर (IS_FWI2_CAPABLE(ha))
		host_to_fcp_swap(pkt->data, माप(pkt->data));
	स_नकल(sense_ptr, pkt->data, sense_sz);
	ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x302c,
		sense_ptr, sense_sz);

	sense_len -= sense_sz;
	sense_ptr += sense_sz;

	SET_CMD_SENSE_PTR(sp, sense_ptr);
	SET_CMD_SENSE_LEN(sp, sense_len);

	/* Place command on करोne queue. */
	अगर (sense_len == 0) अणु
		rsp->status_srb = शून्य;
		sp->करोne(sp, cp->result);
	पूर्ण
पूर्ण

/**
 * qla2x00_error_entry() - Process an error entry.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 * @pkt: Entry poपूर्णांकer
 * वापस : 1=allow further error analysis. 0=no additional error analysis.
 */
अटल पूर्णांक
qla2x00_error_entry(scsi_qla_host_t *vha, काष्ठा rsp_que *rsp, sts_entry_t *pkt)
अणु
	srb_t *sp;
	काष्ठा qla_hw_data *ha = vha->hw;
	स्थिर अक्षर func[] = "ERROR-IOCB";
	uपूर्णांक16_t que = MSW(pkt->handle);
	काष्ठा req_que *req = शून्य;
	पूर्णांक res = DID_ERROR << 16;

	ql_dbg(ql_dbg_async, vha, 0x502a,
	    "iocb type %xh with error status %xh, handle %xh, rspq id %d\n",
	    pkt->entry_type, pkt->entry_status, pkt->handle, rsp->id);

	अगर (que >= ha->max_req_queues || !ha->req_q_map[que])
		जाओ fatal;

	req = ha->req_q_map[que];

	अगर (pkt->entry_status & RF_BUSY)
		res = DID_BUS_BUSY << 16;

	अगर ((pkt->handle & ~QLA_TGT_HANDLE_MASK) == QLA_TGT_SKIP_HANDLE)
		वापस 0;

	चयन (pkt->entry_type) अणु
	हाल NOTIFY_ACK_TYPE:
	हाल STATUS_TYPE:
	हाल STATUS_CONT_TYPE:
	हाल LOGINOUT_PORT_IOCB_TYPE:
	हाल CT_IOCB_TYPE:
	हाल ELS_IOCB_TYPE:
	हाल ABORT_IOCB_TYPE:
	हाल MBX_IOCB_TYPE:
	शेष:
		sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
		अगर (sp) अणु
			qla_put_iocbs(sp->qpair, &sp->iores);
			sp->करोne(sp, res);
			वापस 0;
		पूर्ण
		अवरोध;

	हाल ABTS_RESP_24XX:
	हाल CTIO_TYPE7:
	हाल CTIO_CRC2:
		वापस 1;
	पूर्ण
fatal:
	ql_log(ql_log_warn, vha, 0x5030,
	    "Error entry - invalid handle/queue (%04x).\n", que);
	वापस 0;
पूर्ण

/**
 * qla24xx_mbx_completion() - Process mailbox command completions.
 * @vha: SCSI driver HA context
 * @mb0: Mailbox0 रेजिस्टर
 */
अटल व्योम
qla24xx_mbx_completion(scsi_qla_host_t *vha, uपूर्णांक16_t mb0)
अणु
	uपूर्णांक16_t	cnt;
	uपूर्णांक32_t	mboxes;
	__le16 __iomem *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	/* Read all mbox रेजिस्टरs? */
	WARN_ON_ONCE(ha->mbx_count > 32);
	mboxes = (1ULL << ha->mbx_count) - 1;
	अगर (!ha->mcp)
		ql_dbg(ql_dbg_async, vha, 0x504e, "MBX pointer ERROR.\n");
	अन्यथा
		mboxes = ha->mcp->in_mb;

	/* Load वापस mailbox रेजिस्टरs. */
	ha->flags.mbox_पूर्णांक = 1;
	ha->mailbox_out[0] = mb0;
	mboxes >>= 1;
	wptr = &reg->mailbox1;

	क्रम (cnt = 1; cnt < ha->mbx_count; cnt++) अणु
		अगर (mboxes & BIT_0)
			ha->mailbox_out[cnt] = rd_reg_word(wptr);

		mboxes >>= 1;
		wptr++;
	पूर्ण
पूर्ण

अटल व्योम
qla24xx_पात_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
	काष्ठा पात_entry_24xx *pkt)
अणु
	स्थिर अक्षर func[] = "ABT_IOCB";
	srb_t *sp;
	srb_t *orig_sp = शून्य;
	काष्ठा srb_iocb *abt;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	abt = &sp->u.iocb_cmd;
	abt->u.abt.comp_status = pkt->comp_status;
	orig_sp = sp->cmd_sp;
	/* Need to pass original sp */
	अगर (orig_sp)
		qla_nvme_पात_process_comp_status(pkt, orig_sp);

	sp->करोne(sp, 0);
पूर्ण

व्योम qla24xx_nvme_ls4_iocb(काष्ठा scsi_qla_host *vha,
    काष्ठा pt_ls4_request *pkt, काष्ठा req_que *req)
अणु
	srb_t *sp;
	स्थिर अक्षर func[] = "LS4_IOCB";
	uपूर्णांक16_t comp_status;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	comp_status = le16_to_cpu(pkt->status);
	sp->करोne(sp, comp_status);
पूर्ण

/**
 * qla24xx_process_response_queue() - Process response queue entries.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 */
व्योम qla24xx_process_response_queue(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp)
अणु
	काष्ठा sts_entry_24xx *pkt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा purex_entry_24xx *purex_entry;
	काष्ठा purex_item *pure_item;

	अगर (!ha->flags.fw_started)
		वापस;

	अगर (rsp->qpair->cpuid != smp_processor_id() || !rsp->qpair->rcv_पूर्णांकr) अणु
		rsp->qpair->rcv_पूर्णांकr = 1;
		qla_cpu_update(rsp->qpair, smp_processor_id());
	पूर्ण

	जबतक (rsp->ring_ptr->signature != RESPONSE_PROCESSED) अणु
		pkt = (काष्ठा sts_entry_24xx *)rsp->ring_ptr;

		rsp->ring_index++;
		अगर (rsp->ring_index == rsp->length) अणु
			rsp->ring_index = 0;
			rsp->ring_ptr = rsp->ring;
		पूर्ण अन्यथा अणु
			rsp->ring_ptr++;
		पूर्ण

		अगर (pkt->entry_status != 0) अणु
			अगर (qla2x00_error_entry(vha, rsp, (sts_entry_t *) pkt))
				जाओ process_err;

			((response_t *)pkt)->signature = RESPONSE_PROCESSED;
			wmb();
			जारी;
		पूर्ण
process_err:

		चयन (pkt->entry_type) अणु
		हाल STATUS_TYPE:
			qla2x00_status_entry(vha, rsp, pkt);
			अवरोध;
		हाल STATUS_CONT_TYPE:
			qla2x00_status_cont_entry(rsp, (sts_cont_entry_t *)pkt);
			अवरोध;
		हाल VP_RPT_ID_IOCB_TYPE:
			qla24xx_report_id_acquisition(vha,
			    (काष्ठा vp_rpt_id_entry_24xx *)pkt);
			अवरोध;
		हाल LOGINOUT_PORT_IOCB_TYPE:
			qla24xx_logio_entry(vha, rsp->req,
			    (काष्ठा logio_entry_24xx *)pkt);
			अवरोध;
		हाल CT_IOCB_TYPE:
			qla24xx_els_ct_entry(vha, rsp->req, pkt, CT_IOCB_TYPE);
			अवरोध;
		हाल ELS_IOCB_TYPE:
			qla24xx_els_ct_entry(vha, rsp->req, pkt, ELS_IOCB_TYPE);
			अवरोध;
		हाल ABTS_RECV_24XX:
			अगर (qla_ini_mode_enabled(vha)) अणु
				pure_item = qla24xx_copy_std_pkt(vha, pkt);
				अगर (!pure_item)
					अवरोध;
				qla24xx_queue_purex_item(vha, pure_item,
							 qla24xx_process_abts);
				अवरोध;
			पूर्ण
			अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
			    IS_QLA28XX(ha)) अणु
				/* ensure that the ATIO queue is empty */
				qlt_handle_abts_recv(vha, rsp,
				    (response_t *)pkt);
				अवरोध;
			पूर्ण अन्यथा अणु
				qlt_24xx_process_atio_queue(vha, 1);
			पूर्ण
			fallthrough;
		हाल ABTS_RESP_24XX:
		हाल CTIO_TYPE7:
		हाल CTIO_CRC2:
			qlt_response_pkt_all_vps(vha, rsp, (response_t *)pkt);
			अवरोध;
		हाल PT_LS4_REQUEST:
			qla24xx_nvme_ls4_iocb(vha, (काष्ठा pt_ls4_request *)pkt,
			    rsp->req);
			अवरोध;
		हाल NOTIFY_ACK_TYPE:
			अगर (pkt->handle == QLA_TGT_SKIP_HANDLE)
				qlt_response_pkt_all_vps(vha, rsp,
				    (response_t *)pkt);
			अन्यथा
				qla24xxx_nack_iocb_entry(vha, rsp->req,
					(काष्ठा nack_to_isp *)pkt);
			अवरोध;
		हाल MARKER_TYPE:
			/* Do nothing in this हाल, this check is to prevent it
			 * from falling पूर्णांकo शेष हाल
			 */
			अवरोध;
		हाल ABORT_IOCB_TYPE:
			qla24xx_पात_iocb_entry(vha, rsp->req,
			    (काष्ठा पात_entry_24xx *)pkt);
			अवरोध;
		हाल MBX_IOCB_TYPE:
			qla24xx_mbx_iocb_entry(vha, rsp->req,
			    (काष्ठा mbx_24xx_entry *)pkt);
			अवरोध;
		हाल VP_CTRL_IOCB_TYPE:
			qla_ctrlvp_completed(vha, rsp->req,
			    (काष्ठा vp_ctrl_entry_24xx *)pkt);
			अवरोध;
		हाल PUREX_IOCB_TYPE:
			purex_entry = (व्योम *)pkt;
			चयन (purex_entry->els_frame_payload[3]) अणु
			हाल ELS_RDP:
				pure_item = qla24xx_copy_std_pkt(vha, pkt);
				अगर (!pure_item)
					अवरोध;
				qla24xx_queue_purex_item(vha, pure_item,
						 qla24xx_process_purex_rdp);
				अवरोध;
			हाल ELS_FPIN:
				अगर (!vha->hw->flags.scm_enabled) अणु
					ql_log(ql_log_warn, vha, 0x5094,
					       "SCM not active for this port\n");
					अवरोध;
				पूर्ण
				pure_item = qla27xx_copy_fpin_pkt(vha,
							  (व्योम **)&pkt, &rsp);
				अगर (!pure_item)
					अवरोध;
				qla24xx_queue_purex_item(vha, pure_item,
						 qla27xx_process_purex_fpin);
				अवरोध;

			शेष:
				ql_log(ql_log_warn, vha, 0x509c,
				       "Discarding ELS Request opcode 0x%x\n",
				       purex_entry->els_frame_payload[3]);
			पूर्ण
			अवरोध;
		शेष:
			/* Type Not Supported. */
			ql_dbg(ql_dbg_async, vha, 0x5042,
			       "Received unknown response pkt type 0x%x entry status=%x.\n",
			       pkt->entry_type, pkt->entry_status);
			अवरोध;
		पूर्ण
		((response_t *)pkt)->signature = RESPONSE_PROCESSED;
		wmb();
	पूर्ण

	/* Adjust ring index */
	अगर (IS_P3P_TYPE(ha)) अणु
		काष्ठा device_reg_82xx __iomem *reg = &ha->iobase->isp82;

		wrt_reg_dword(&reg->rsp_q_out[0], rsp->ring_index);
	पूर्ण अन्यथा अणु
		wrt_reg_dword(rsp->rsp_q_out, rsp->ring_index);
	पूर्ण
पूर्ण

अटल व्योम
qla2xxx_check_risc_status(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t cnt;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	अगर (!IS_QLA25XX(ha) && !IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस;

	rval = QLA_SUCCESS;
	wrt_reg_dword(&reg->iobase_addr, 0x7C00);
	rd_reg_dword(&reg->iobase_addr);
	wrt_reg_dword(&reg->iobase_winकरोw, 0x0001);
	क्रम (cnt = 10000; (rd_reg_dword(&reg->iobase_winकरोw) & BIT_0) == 0 &&
	    rval == QLA_SUCCESS; cnt--) अणु
		अगर (cnt) अणु
			wrt_reg_dword(&reg->iobase_winकरोw, 0x0001);
			udelay(10);
		पूर्ण अन्यथा
			rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण
	अगर (rval == QLA_SUCCESS)
		जाओ next_test;

	rval = QLA_SUCCESS;
	wrt_reg_dword(&reg->iobase_winकरोw, 0x0003);
	क्रम (cnt = 100; (rd_reg_dword(&reg->iobase_winकरोw) & BIT_0) == 0 &&
	    rval == QLA_SUCCESS; cnt--) अणु
		अगर (cnt) अणु
			wrt_reg_dword(&reg->iobase_winकरोw, 0x0003);
			udelay(10);
		पूर्ण अन्यथा
			rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण
	अगर (rval != QLA_SUCCESS)
		जाओ करोne;

next_test:
	अगर (rd_reg_dword(&reg->iobase_c8) & BIT_3)
		ql_log(ql_log_info, vha, 0x504c,
		    "Additional code -- 0x55AA.\n");

करोne:
	wrt_reg_dword(&reg->iobase_winकरोw, 0x0000);
	rd_reg_dword(&reg->iobase_winकरोw);
पूर्ण

/**
 * qla24xx_पूर्णांकr_handler() - Process पूर्णांकerrupts क्रम the ISP23xx and ISP24xx.
 * @irq: पूर्णांकerrupt number
 * @dev_id: SCSI driver HA context
 *
 * Called by प्रणाली whenever the host adapter generates an पूर्णांकerrupt.
 *
 * Returns handled flag.
 */
irqवापस_t
qla24xx_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा device_reg_24xx __iomem *reg;
	पूर्णांक		status;
	अचिन्हित दीर्घ	iter;
	uपूर्णांक32_t	stat;
	uपूर्णांक32_t	hccr;
	uपूर्णांक16_t	mb[8];
	काष्ठा rsp_que *rsp;
	अचिन्हित दीर्घ	flags;
	bool process_atio = false;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0x5059,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	ha = rsp->hw;
	reg = &ha->iobase->isp24;
	status = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	क्रम (iter = 50; iter--; ) अणु
		stat = rd_reg_dword(&reg->host_status);
		अगर (qla2x00_check_reg32_क्रम_disconnect(vha, stat))
			अवरोध;
		अगर (stat & HSRX_RISC_PAUSED) अणु
			अगर (unlikely(pci_channel_offline(ha->pdev)))
				अवरोध;

			hccr = rd_reg_dword(&reg->hccr);

			ql_log(ql_log_warn, vha, 0x504b,
			    "RISC paused -- HCCR=%x, Dumping firmware.\n",
			    hccr);

			qla2xxx_check_risc_status(vha);

			ha->isp_ops->fw_dump(vha);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			अवरोध;
		पूर्ण अन्यथा अगर ((stat & HSRX_RISC_INT) == 0)
			अवरोध;

		चयन (stat & 0xff) अणु
		हाल INTR_ROM_MB_SUCCESS:
		हाल INTR_ROM_MB_FAILED:
		हाल INTR_MB_SUCCESS:
		हाल INTR_MB_FAILED:
			qla24xx_mbx_completion(vha, MSW(stat));
			status |= MBX_INTERRUPT;

			अवरोध;
		हाल INTR_ASYNC_EVENT:
			mb[0] = MSW(stat);
			mb[1] = rd_reg_word(&reg->mailbox1);
			mb[2] = rd_reg_word(&reg->mailbox2);
			mb[3] = rd_reg_word(&reg->mailbox3);
			qla2x00_async_event(vha, rsp, mb);
			अवरोध;
		हाल INTR_RSP_QUE_UPDATE:
		हाल INTR_RSP_QUE_UPDATE_83XX:
			qla24xx_process_response_queue(vha, rsp);
			अवरोध;
		हाल INTR_ATIO_QUE_UPDATE_27XX:
		हाल INTR_ATIO_QUE_UPDATE:
			process_atio = true;
			अवरोध;
		हाल INTR_ATIO_RSP_QUE_UPDATE:
			process_atio = true;
			qla24xx_process_response_queue(vha, rsp);
			अवरोध;
		शेष:
			ql_dbg(ql_dbg_async, vha, 0x504f,
			    "Unrecognized interrupt type (%d).\n", stat * 0xff);
			अवरोध;
		पूर्ण
		wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
		rd_reg_dword_relaxed(&reg->hccr);
		अगर (unlikely(IS_QLA83XX(ha) && (ha->pdev->revision == 1)))
			ndelay(3500);
	पूर्ण
	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (process_atio) अणु
		spin_lock_irqsave(&ha->tgt.atio_lock, flags);
		qlt_24xx_process_atio_queue(vha, 0);
		spin_unlock_irqrestore(&ha->tgt.atio_lock, flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
qla24xx_msix_rsp_q(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_24xx __iomem *reg;
	काष्ठा scsi_qla_host *vha;
	अचिन्हित दीर्घ flags;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0x505a,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = rsp->hw;
	reg = &ha->iobase->isp24;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	vha = pci_get_drvdata(ha->pdev);
	qla24xx_process_response_queue(vha, rsp);
	अगर (!ha->flags.disable_msix_handshake) अणु
		wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
		rd_reg_dword_relaxed(&reg->hccr);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
qla24xx_msix_शेष(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा rsp_que *rsp;
	काष्ठा device_reg_24xx __iomem *reg;
	पूर्णांक		status;
	uपूर्णांक32_t	stat;
	uपूर्णांक32_t	hccr;
	uपूर्णांक16_t	mb[8];
	अचिन्हित दीर्घ flags;
	bool process_atio = false;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0x505c,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = rsp->hw;
	reg = &ha->iobase->isp24;
	status = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	करो अणु
		stat = rd_reg_dword(&reg->host_status);
		अगर (qla2x00_check_reg32_क्रम_disconnect(vha, stat))
			अवरोध;
		अगर (stat & HSRX_RISC_PAUSED) अणु
			अगर (unlikely(pci_channel_offline(ha->pdev)))
				अवरोध;

			hccr = rd_reg_dword(&reg->hccr);

			ql_log(ql_log_info, vha, 0x5050,
			    "RISC paused -- HCCR=%x, Dumping firmware.\n",
			    hccr);

			qla2xxx_check_risc_status(vha);
			vha->hw_err_cnt++;

			ha->isp_ops->fw_dump(vha);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			अवरोध;
		पूर्ण अन्यथा अगर ((stat & HSRX_RISC_INT) == 0)
			अवरोध;

		चयन (stat & 0xff) अणु
		हाल INTR_ROM_MB_SUCCESS:
		हाल INTR_ROM_MB_FAILED:
		हाल INTR_MB_SUCCESS:
		हाल INTR_MB_FAILED:
			qla24xx_mbx_completion(vha, MSW(stat));
			status |= MBX_INTERRUPT;

			अवरोध;
		हाल INTR_ASYNC_EVENT:
			mb[0] = MSW(stat);
			mb[1] = rd_reg_word(&reg->mailbox1);
			mb[2] = rd_reg_word(&reg->mailbox2);
			mb[3] = rd_reg_word(&reg->mailbox3);
			qla2x00_async_event(vha, rsp, mb);
			अवरोध;
		हाल INTR_RSP_QUE_UPDATE:
		हाल INTR_RSP_QUE_UPDATE_83XX:
			qla24xx_process_response_queue(vha, rsp);
			अवरोध;
		हाल INTR_ATIO_QUE_UPDATE_27XX:
		हाल INTR_ATIO_QUE_UPDATE:
			process_atio = true;
			अवरोध;
		हाल INTR_ATIO_RSP_QUE_UPDATE:
			process_atio = true;
			qla24xx_process_response_queue(vha, rsp);
			अवरोध;
		शेष:
			ql_dbg(ql_dbg_async, vha, 0x5051,
			    "Unrecognized interrupt type (%d).\n", stat & 0xff);
			अवरोध;
		पूर्ण
		wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
	पूर्ण जबतक (0);
	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (process_atio) अणु
		spin_lock_irqsave(&ha->tgt.atio_lock, flags);
		qlt_24xx_process_atio_queue(vha, 0);
		spin_unlock_irqrestore(&ha->tgt.atio_lock, flags);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t
qla2xxx_msix_rsp_q(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qla_hw_data *ha;
	काष्ठा qla_qpair *qpair;

	qpair = dev_id;
	अगर (!qpair) अणु
		ql_log(ql_log_info, शून्य, 0x505b,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = qpair->hw;

	queue_work_on(smp_processor_id(), ha->wq, &qpair->q_work);

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t
qla2xxx_msix_rsp_q_hs(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qla_hw_data *ha;
	काष्ठा qla_qpair *qpair;
	काष्ठा device_reg_24xx __iomem *reg;
	अचिन्हित दीर्घ flags;

	qpair = dev_id;
	अगर (!qpair) अणु
		ql_log(ql_log_info, शून्य, 0x505b,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण
	ha = qpair->hw;

	reg = &ha->iobase->isp24;
	spin_lock_irqsave(&ha->hardware_lock, flags);
	wrt_reg_dword(&reg->hccr, HCCRX_CLR_RISC_INT);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	queue_work_on(smp_processor_id(), ha->wq, &qpair->q_work);

	वापस IRQ_HANDLED;
पूर्ण

/* Interrupt handling helpers. */

काष्ठा qla_init_msix_entry अणु
	स्थिर अक्षर *name;
	irq_handler_t handler;
पूर्ण;

अटल स्थिर काष्ठा qla_init_msix_entry msix_entries[] = अणु
	अणु "default", qla24xx_msix_शेष पूर्ण,
	अणु "rsp_q", qla24xx_msix_rsp_q पूर्ण,
	अणु "atio_q", qla83xx_msix_atio_q पूर्ण,
	अणु "qpair_multiq", qla2xxx_msix_rsp_q पूर्ण,
	अणु "qpair_multiq_hs", qla2xxx_msix_rsp_q_hs पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा qla_init_msix_entry qla82xx_msix_entries[] = अणु
	अणु "qla2xxx (default)", qla82xx_msix_शेष पूर्ण,
	अणु "qla2xxx (rsp_q)", qla82xx_msix_rsp_q पूर्ण,
पूर्ण;

अटल पूर्णांक
qla24xx_enable_msix(काष्ठा qla_hw_data *ha, काष्ठा rsp_que *rsp)
अणु
	पूर्णांक i, ret;
	काष्ठा qla_msix_entry *qentry;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	पूर्णांक min_vecs = QLA_BASE_VECTORS;
	काष्ठा irq_affinity desc = अणु
		.pre_vectors = QLA_BASE_VECTORS,
	पूर्ण;

	अगर (QLA_TGT_MODE_ENABLED() && (ql2xenablemsix != 0) &&
	    IS_ATIO_MSIX_CAPABLE(ha)) अणु
		desc.pre_vectors++;
		min_vecs++;
	पूर्ण

	अगर (USER_CTRL_IRQ(ha) || !ha->mqiobase) अणु
		/* user wants to control IRQ setting क्रम target mode */
		ret = pci_alloc_irq_vectors(ha->pdev, min_vecs,
		    min((u16)ha->msix_count, (u16)(num_online_cpus() + min_vecs)),
		    PCI_IRQ_MSIX);
	पूर्ण अन्यथा
		ret = pci_alloc_irq_vectors_affinity(ha->pdev, min_vecs,
		    min((u16)ha->msix_count, (u16)(num_online_cpus() + min_vecs)),
		    PCI_IRQ_MSIX | PCI_IRQ_AFFINITY,
		    &desc);

	अगर (ret < 0) अणु
		ql_log(ql_log_fatal, vha, 0x00c7,
		    "MSI-X: Failed to enable support, "
		    "giving   up -- %d/%d.\n",
		    ha->msix_count, ret);
		जाओ msix_out;
	पूर्ण अन्यथा अगर (ret < ha->msix_count) अणु
		ql_log(ql_log_info, vha, 0x00c6,
		    "MSI-X: Using %d vectors\n", ret);
		ha->msix_count = ret;
		/* Recalculate queue values */
		अगर (ha->mqiobase && (ql2xmqsupport || ql2xnvmeenable)) अणु
			ha->max_req_queues = ha->msix_count - 1;

			/* ATIOQ needs 1 vector. That's 1 less QPair */
			अगर (QLA_TGT_MODE_ENABLED())
				ha->max_req_queues--;

			ha->max_rsp_queues = ha->max_req_queues;

			ha->max_qpairs = ha->max_req_queues - 1;
			ql_dbg_pci(ql_dbg_init, ha->pdev, 0x0190,
			    "Adjusted Max no of queues pairs: %d.\n", ha->max_qpairs);
		पूर्ण
	पूर्ण
	vha->irq_offset = desc.pre_vectors;
	ha->msix_entries = kसुस्मृति(ha->msix_count,
				   माप(काष्ठा qla_msix_entry),
				   GFP_KERNEL);
	अगर (!ha->msix_entries) अणु
		ql_log(ql_log_fatal, vha, 0x00c8,
		    "Failed to allocate memory for ha->msix_entries.\n");
		ret = -ENOMEM;
		जाओ मुक्त_irqs;
	पूर्ण
	ha->flags.msix_enabled = 1;

	क्रम (i = 0; i < ha->msix_count; i++) अणु
		qentry = &ha->msix_entries[i];
		qentry->vector = pci_irq_vector(ha->pdev, i);
		qentry->entry = i;
		qentry->have_irq = 0;
		qentry->in_use = 0;
		qentry->handle = शून्य;
	पूर्ण

	/* Enable MSI-X vectors क्रम the base queue */
	क्रम (i = 0; i < QLA_BASE_VECTORS; i++) अणु
		qentry = &ha->msix_entries[i];
		qentry->handle = rsp;
		rsp->msix = qentry;
		scnम_लिखो(qentry->name, माप(qentry->name),
		    "qla2xxx%lu_%s", vha->host_no, msix_entries[i].name);
		अगर (IS_P3P_TYPE(ha))
			ret = request_irq(qentry->vector,
				qla82xx_msix_entries[i].handler,
				0, qla82xx_msix_entries[i].name, rsp);
		अन्यथा
			ret = request_irq(qentry->vector,
				msix_entries[i].handler,
				0, qentry->name, rsp);
		अगर (ret)
			जाओ msix_रेजिस्टर_fail;
		qentry->have_irq = 1;
		qentry->in_use = 1;
	पूर्ण

	/*
	 * If target mode is enable, also request the vector क्रम the ATIO
	 * queue.
	 */
	अगर (QLA_TGT_MODE_ENABLED() && (ql2xenablemsix != 0) &&
	    IS_ATIO_MSIX_CAPABLE(ha)) अणु
		qentry = &ha->msix_entries[QLA_ATIO_VECTOR];
		rsp->msix = qentry;
		qentry->handle = rsp;
		scnम_लिखो(qentry->name, माप(qentry->name),
		    "qla2xxx%lu_%s", vha->host_no,
		    msix_entries[QLA_ATIO_VECTOR].name);
		qentry->in_use = 1;
		ret = request_irq(qentry->vector,
			msix_entries[QLA_ATIO_VECTOR].handler,
			0, qentry->name, rsp);
		qentry->have_irq = 1;
	पूर्ण

msix_रेजिस्टर_fail:
	अगर (ret) अणु
		ql_log(ql_log_fatal, vha, 0x00cb,
		    "MSI-X: unable to register handler -- %x/%d.\n",
		    qentry->vector, ret);
		qla2x00_मुक्त_irqs(vha);
		ha->mqenable = 0;
		जाओ msix_out;
	पूर्ण

	/* Enable MSI-X vector क्रम response queue update क्रम queue 0 */
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		अगर (ha->msixbase && ha->mqiobase &&
		    (ha->max_rsp_queues > 1 || ha->max_req_queues > 1 ||
		     ql2xmqsupport))
			ha->mqenable = 1;
	पूर्ण अन्यथा
		अगर (ha->mqiobase &&
		    (ha->max_rsp_queues > 1 || ha->max_req_queues > 1 ||
		     ql2xmqsupport))
			ha->mqenable = 1;
	ql_dbg(ql_dbg_multiq, vha, 0xc005,
	    "mqiobase=%p, max_rsp_queues=%d, max_req_queues=%d.\n",
	    ha->mqiobase, ha->max_rsp_queues, ha->max_req_queues);
	ql_dbg(ql_dbg_init, vha, 0x0055,
	    "mqiobase=%p, max_rsp_queues=%d, max_req_queues=%d.\n",
	    ha->mqiobase, ha->max_rsp_queues, ha->max_req_queues);

msix_out:
	वापस ret;

मुक्त_irqs:
	pci_मुक्त_irq_vectors(ha->pdev);
	जाओ msix_out;
पूर्ण

पूर्णांक
qla2x00_request_irqs(काष्ठा qla_hw_data *ha, काष्ठा rsp_que *rsp)
अणु
	पूर्णांक ret = QLA_FUNCTION_FAILED;
	device_reg_t *reg = ha->iobase;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	/* If possible, enable MSI-X. */
	अगर (ql2xenablemsix == 0 || (!IS_QLA2432(ha) && !IS_QLA2532(ha) &&
	    !IS_QLA8432(ha) && !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha) &&
	    !IS_QLAFX00(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha)))
		जाओ skip_msi;

	अगर (ql2xenablemsix == 2)
		जाओ skip_msix;

	अगर (ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP &&
		(ha->pdev->subप्रणाली_device == 0x7040 ||
		ha->pdev->subप्रणाली_device == 0x7041 ||
		ha->pdev->subप्रणाली_device == 0x1705)) अणु
		ql_log(ql_log_warn, vha, 0x0034,
		    "MSI-X: Unsupported ISP 2432 SSVID/SSDID (0x%X,0x%X).\n",
			ha->pdev->subप्रणाली_venकरोr,
			ha->pdev->subप्रणाली_device);
		जाओ skip_msi;
	पूर्ण

	अगर (IS_QLA2432(ha) && (ha->pdev->revision < QLA_MSIX_CHIP_REV_24XX)) अणु
		ql_log(ql_log_warn, vha, 0x0035,
		    "MSI-X; Unsupported ISP2432 (0x%X, 0x%X).\n",
		    ha->pdev->revision, QLA_MSIX_CHIP_REV_24XX);
		जाओ skip_msix;
	पूर्ण

	ret = qla24xx_enable_msix(ha, rsp);
	अगर (!ret) अणु
		ql_dbg(ql_dbg_init, vha, 0x0036,
		    "MSI-X: Enabled (0x%X, 0x%X).\n",
		    ha->chip_revision, ha->fw_attributes);
		जाओ clear_risc_पूर्णांकs;
	पूर्ण

skip_msix:

	ql_log(ql_log_info, vha, 0x0037,
	    "Falling back-to MSI mode -- ret=%d.\n", ret);

	अगर (!IS_QLA24XX(ha) && !IS_QLA2532(ha) && !IS_QLA8432(ha) &&
	    !IS_QLA8001(ha) && !IS_P3P_TYPE(ha) && !IS_QLAFX00(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		जाओ skip_msi;

	ret = pci_alloc_irq_vectors(ha->pdev, 1, 1, PCI_IRQ_MSI);
	अगर (ret > 0) अणु
		ql_dbg(ql_dbg_init, vha, 0x0038,
		    "MSI: Enabled.\n");
		ha->flags.msi_enabled = 1;
	पूर्ण अन्यथा
		ql_log(ql_log_warn, vha, 0x0039,
		    "Falling back-to INTa mode -- ret=%d.\n", ret);
skip_msi:

	/* Skip INTx on ISP82xx. */
	अगर (!ha->flags.msi_enabled && IS_QLA82XX(ha))
		वापस QLA_FUNCTION_FAILED;

	ret = request_irq(ha->pdev->irq, ha->isp_ops->पूर्णांकr_handler,
	    ha->flags.msi_enabled ? 0 : IRQF_SHARED,
	    QLA2XXX_DRIVER_NAME, rsp);
	अगर (ret) अणु
		ql_log(ql_log_warn, vha, 0x003a,
		    "Failed to reserve interrupt %d already in use.\n",
		    ha->pdev->irq);
		जाओ fail;
	पूर्ण अन्यथा अगर (!ha->flags.msi_enabled) अणु
		ql_dbg(ql_dbg_init, vha, 0x0125,
		    "INTa mode: Enabled.\n");
		ha->flags.mr_पूर्णांकr_valid = 1;
	पूर्ण

clear_risc_पूर्णांकs:
	अगर (IS_FWI2_CAPABLE(ha) || IS_QLAFX00(ha))
		जाओ fail;

	spin_lock_irq(&ha->hardware_lock);
	wrt_reg_word(&reg->isp.semaphore, 0);
	spin_unlock_irq(&ha->hardware_lock);

fail:
	वापस ret;
पूर्ण

व्योम
qla2x00_मुक्त_irqs(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा rsp_que *rsp;
	काष्ठा qla_msix_entry *qentry;
	पूर्णांक i;

	/*
	 * We need to check that ha->rsp_q_map is valid in हाल we are called
	 * from a probe failure context.
	 */
	अगर (!ha->rsp_q_map || !ha->rsp_q_map[0])
		जाओ मुक्त_irqs;
	rsp = ha->rsp_q_map[0];

	अगर (ha->flags.msix_enabled) अणु
		क्रम (i = 0; i < ha->msix_count; i++) अणु
			qentry = &ha->msix_entries[i];
			अगर (qentry->have_irq) अणु
				irq_set_affinity_notअगरier(qentry->vector, शून्य);
				मुक्त_irq(pci_irq_vector(ha->pdev, i), qentry->handle);
			पूर्ण
		पूर्ण
		kमुक्त(ha->msix_entries);
		ha->msix_entries = शून्य;
		ha->flags.msix_enabled = 0;
		ql_dbg(ql_dbg_init, vha, 0x0042,
			"Disabled MSI-X.\n");
	पूर्ण अन्यथा अणु
		मुक्त_irq(pci_irq_vector(ha->pdev, 0), rsp);
	पूर्ण

मुक्त_irqs:
	pci_मुक्त_irq_vectors(ha->pdev);
पूर्ण

पूर्णांक qla25xx_request_irq(काष्ठा qla_hw_data *ha, काष्ठा qla_qpair *qpair,
	काष्ठा qla_msix_entry *msix, पूर्णांक vector_type)
अणु
	स्थिर काष्ठा qla_init_msix_entry *पूर्णांकr = &msix_entries[vector_type];
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	पूर्णांक ret;

	scnम_लिखो(msix->name, माप(msix->name),
	    "qla2xxx%lu_qpair%d", vha->host_no, qpair->id);
	ret = request_irq(msix->vector, पूर्णांकr->handler, 0, msix->name, qpair);
	अगर (ret) अणु
		ql_log(ql_log_fatal, vha, 0x00e6,
		    "MSI-X: Unable to register handler -- %x/%d.\n",
		    msix->vector, ret);
		वापस ret;
	पूर्ण
	msix->have_irq = 1;
	msix->handle = qpair;
	वापस ret;
पूर्ण
