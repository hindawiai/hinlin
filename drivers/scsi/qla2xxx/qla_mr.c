<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/pci.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <linux/utsname.h>


/* QLAFX00 specअगरic Mailbox implementation functions */

/*
 * qlafx00_mailbox_command
 *	Issue mailbox command and रुकोs क्रम completion.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	mcp = driver पूर्णांकernal mbx काष्ठा poपूर्णांकer.
 *
 * Output:
 *	mb[MAX_MAILBOX_REGISTER_COUNT] = वापसed mailbox data.
 *
 * Returns:
 *	0 : QLA_SUCCESS = cmd perक्रमmed success
 *	1 : QLA_FUNCTION_FAILED   (error encountered)
 *	6 : QLA_FUNCTION_TIMEOUT (समयout condition encountered)
 *
 * Context:
 *	Kernel context.
 */
अटल पूर्णांक
qlafx00_mailbox_command(scsi_qla_host_t *vha, काष्ठा mbx_cmd_32 *mcp)

अणु
	पूर्णांक		rval;
	अचिन्हित दीर्घ    flags = 0;
	device_reg_t *reg;
	uपूर्णांक8_t		पात_active;
	uपूर्णांक8_t		io_lock_on;
	uपूर्णांक16_t	command = 0;
	uपूर्णांक32_t	*iptr;
	__le32 __iomem *optr;
	uपूर्णांक32_t	cnt;
	uपूर्णांक32_t	mboxes;
	अचिन्हित दीर्घ	रुको_समय;
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	अगर (ha->pdev->error_state == pci_channel_io_perm_failure) अणु
		ql_log(ql_log_warn, vha, 0x115c,
		    "PCI channel failed permanently, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	अगर (vha->device_flags & DFLG_DEV_FAILED) अणु
		ql_log(ql_log_warn, vha, 0x115f,
		    "Device in failed state, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	reg = ha->iobase;
	io_lock_on = base_vha->flags.init_करोne;

	rval = QLA_SUCCESS;
	पात_active = test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);

	अगर (ha->flags.pci_channel_io_perm_failure) अणु
		ql_log(ql_log_warn, vha, 0x1175,
		    "Perm failure on EEH timeout MBX, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	अगर (ha->flags.isp82xx_fw_hung) अणु
		/* Setting Link-Down error */
		mcp->mb[0] = MBS_LINK_DOWN_ERROR;
		ql_log(ql_log_warn, vha, 0x1176,
		    "FW hung = %d.\n", ha->flags.isp82xx_fw_hung);
		rval = QLA_FUNCTION_FAILED;
		जाओ premature_निकास;
	पूर्ण

	/*
	 * Wait क्रम active mailbox commands to finish by रुकोing at most tov
	 * seconds. This is to serialize actual issuing of mailbox cmds during
	 * non ISP पात समय.
	 */
	अगर (!रुको_क्रम_completion_समयout(&ha->mbx_cmd_comp, mcp->tov * HZ)) अणु
		/* Timeout occurred. Return error. */
		ql_log(ql_log_warn, vha, 0x1177,
		    "Cmd access timeout, cmd=0x%x, Exiting.\n",
		    mcp->mb[0]);
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	ha->flags.mbox_busy = 1;
	/* Save mailbox command क्रम debug */
	ha->mcp32 = mcp;

	ql_dbg(ql_dbg_mbx, vha, 0x1178,
	    "Prepare to issue mbox cmd=0x%x.\n", mcp->mb[0]);

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Load mailbox रेजिस्टरs. */
	optr = &reg->ispfx00.mailbox0;

	iptr = mcp->mb;
	command = mcp->mb[0];
	mboxes = mcp->out_mb;

	क्रम (cnt = 0; cnt < ha->mbx_count; cnt++) अणु
		अगर (mboxes & BIT_0)
			wrt_reg_dword(optr, *iptr);

		mboxes >>= 1;
		optr++;
		iptr++;
	पूर्ण

	/* Issue set host पूर्णांकerrupt command to send cmd out. */
	ha->flags.mbox_पूर्णांक = 0;
	clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

	ql_dump_buffer(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1172,
	    (uपूर्णांक8_t *)mcp->mb, 16);
	ql_dump_buffer(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1173,
	    ((uपूर्णांक8_t *)mcp->mb + 0x10), 16);
	ql_dump_buffer(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1174,
	    ((uपूर्णांक8_t *)mcp->mb + 0x20), 8);

	/* Unlock mbx रेजिस्टरs and रुको क्रम पूर्णांकerrupt */
	ql_dbg(ql_dbg_mbx, vha, 0x1179,
	    "Going to unlock irq & waiting for interrupts. "
	    "jiffies=%lx.\n", jअगरfies);

	/* Wait क्रम mbx cmd completion until समयout */
	अगर ((!पात_active && io_lock_on) || IS_NOPOLLING_TYPE(ha)) अणु
		set_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags);

		QLAFX00_SET_HST_INTR(ha, ha->mbx_पूर्णांकr_code);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		WARN_ON_ONCE(रुको_क्रम_completion_समयout(&ha->mbx_पूर्णांकr_comp,
							 mcp->tov * HZ) != 0);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx, vha, 0x112c,
		    "Cmd=%x Polling Mode.\n", command);

		QLAFX00_SET_HST_INTR(ha, ha->mbx_पूर्णांकr_code);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		रुको_समय = jअगरfies + mcp->tov * HZ; /* रुको at most tov secs */
		जबतक (!ha->flags.mbox_पूर्णांक) अणु
			अगर (समय_after(jअगरfies, रुको_समय))
				अवरोध;

			/* Check क्रम pending पूर्णांकerrupts. */
			qla2x00_poll(ha->rsp_q_map[0]);

			अगर (!ha->flags.mbox_पूर्णांक &&
			    !(IS_QLA2200(ha) &&
			    command == MBC_LOAD_RISC_RAM_EXTENDED))
				usleep_range(10000, 11000);
		पूर्ण /* जबतक */
		ql_dbg(ql_dbg_mbx, vha, 0x112d,
		    "Waited %d sec.\n",
		    (uपूर्णांक)((jअगरfies - (रुको_समय - (mcp->tov * HZ)))/HZ));
	पूर्ण

	/* Check whether we समयd out */
	अगर (ha->flags.mbox_पूर्णांक) अणु
		uपूर्णांक32_t *iptr2;

		ql_dbg(ql_dbg_mbx, vha, 0x112e,
		    "Cmd=%x completed.\n", command);

		/* Got पूर्णांकerrupt. Clear the flag. */
		ha->flags.mbox_पूर्णांक = 0;
		clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

		अगर (ha->mailbox_out32[0] != MBS_COMMAND_COMPLETE)
			rval = QLA_FUNCTION_FAILED;

		/* Load वापस mailbox रेजिस्टरs. */
		iptr2 = mcp->mb;
		iptr = (uपूर्णांक32_t *)&ha->mailbox_out32[0];
		mboxes = mcp->in_mb;
		क्रम (cnt = 0; cnt < ha->mbx_count; cnt++) अणु
			अगर (mboxes & BIT_0)
				*iptr2 = *iptr;

			mboxes >>= 1;
			iptr2++;
			iptr++;
		पूर्ण
	पूर्ण अन्यथा अणु

		rval = QLA_FUNCTION_TIMEOUT;
	पूर्ण

	ha->flags.mbox_busy = 0;

	/* Clean up */
	ha->mcp32 = शून्य;

	अगर ((पात_active || !io_lock_on) && !IS_NOPOLLING_TYPE(ha)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x113a,
		    "checking for additional resp interrupt.\n");

		/* polling mode क्रम non isp_पात commands. */
		qla2x00_poll(ha->rsp_q_map[0]);
	पूर्ण

	अगर (rval == QLA_FUNCTION_TIMEOUT &&
	    mcp->mb[0] != MBC_GEN_SYSTEM_ERROR) अणु
		अगर (!io_lock_on || (mcp->flags & IOCTL_CMD) ||
		    ha->flags.eeh_busy) अणु
			/* not in dpc. schedule it क्रम dpc to take over. */
			ql_dbg(ql_dbg_mbx, vha, 0x115d,
			    "Timeout, schedule isp_abort_needed.\n");

			अगर (!test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) &&
			    !test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) &&
			    !test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु

				ql_log(ql_log_info, base_vha, 0x115e,
				    "Mailbox cmd timeout occurred, cmd=0x%x, "
				    "mb[0]=0x%x, eeh_busy=0x%x. Scheduling ISP "
				    "abort.\n", command, mcp->mb[0],
				    ha->flags.eeh_busy);
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण
		पूर्ण अन्यथा अगर (!पात_active) अणु
			/* call पात directly since we are in the DPC thपढ़ो */
			ql_dbg(ql_dbg_mbx, vha, 0x1160,
			    "Timeout, calling abort_isp.\n");

			अगर (!test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) &&
			    !test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) &&
			    !test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु

				ql_log(ql_log_info, base_vha, 0x1161,
				    "Mailbox cmd timeout occurred, cmd=0x%x, "
				    "mb[0]=0x%x. Scheduling ISP abort ",
				    command, mcp->mb[0]);

				set_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags);
				clear_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				अगर (ha->isp_ops->पात_isp(vha)) अणु
					/* Failed. retry later. */
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				पूर्ण
				clear_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags);
				ql_dbg(ql_dbg_mbx, vha, 0x1162,
				    "Finished abort_isp.\n");
			पूर्ण
		पूर्ण
	पूर्ण

premature_निकास:
	/* Allow next mbx cmd to come in. */
	complete(&ha->mbx_cmd_comp);

	अगर (rval) अणु
		ql_log(ql_log_warn, base_vha, 0x1163,
		       "**** Failed=%x mbx[0]=%x, mb[1]=%x, mb[2]=%x, mb[3]=%x, cmd=%x ****.\n",
		       rval, mcp->mb[0], mcp->mb[1], mcp->mb[2], mcp->mb[3],
		       command);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx, base_vha, 0x1164, "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qlafx00_driver_shutकरोwn
 *	Indicate a driver shutकरोwn to firmware.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *	local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qlafx00_driver_shutकरोwn(scsi_qla_host_t *vha, पूर्णांक पंचांगo)
अणु
	पूर्णांक rval;
	काष्ठा mbx_cmd_32 mc;
	काष्ठा mbx_cmd_32 *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1166,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_MR_DRV_SHUTDOWN;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0;
	अगर (पंचांगo)
		mcp->tov = पंचांगo;
	अन्यथा
		mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qlafx00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1167,
		    "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1168,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qlafx00_get_firmware_state
 *	Get adapter firmware state.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla7xxx local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
अटल पूर्णांक
qlafx00_get_firmware_state(scsi_qla_host_t *vha, uपूर्णांक32_t *states)
अणु
	पूर्णांक rval;
	काष्ठा mbx_cmd_32 mc;
	काष्ठा mbx_cmd_32 *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1169,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_FIRMWARE_STATE;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qlafx00_mailbox_command(vha, mcp);

	/* Return firmware states. */
	states[0] = mcp->mb[1];

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x116a,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x116b,
		    "Done %s.\n", __func__);
	पूर्ण
	वापस rval;
पूर्ण

/*
 * qlafx00_init_firmware
 *	Initialize adapter firmware.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	dptr = Initialization control block poपूर्णांकer.
 *	size = size of initialization control block.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qlafx00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qlafx00_init_firmware(scsi_qla_host_t *vha, uपूर्णांक16_t size)
अणु
	पूर्णांक rval;
	काष्ठा mbx_cmd_32 mc;
	काष्ठा mbx_cmd_32 *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x116c,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_INITIALIZE_FIRMWARE;

	mcp->mb[1] = 0;
	mcp->mb[2] = MSD(ha->init_cb_dma);
	mcp->mb[3] = LSD(ha->init_cb_dma);

	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->buf_size = size;
	mcp->flags = MBX_DMA_OUT;
	mcp->tov = MBX_TOV_SECONDS;
	rval = qlafx00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x116d,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x116e,
		    "Done %s.\n", __func__);
	पूर्ण
	वापस rval;
पूर्ण

/*
 * qlafx00_mbx_reg_test
 */
अटल पूर्णांक
qlafx00_mbx_reg_test(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	काष्ठा mbx_cmd_32 mc;
	काष्ठा mbx_cmd_32 *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x116f,
	    "Entered %s.\n", __func__);


	mcp->mb[0] = MBC_MAILBOX_REGISTER_TEST;
	mcp->mb[1] = 0xAAAA;
	mcp->mb[2] = 0x5555;
	mcp->mb[3] = 0xAA55;
	mcp->mb[4] = 0x55AA;
	mcp->mb[5] = 0xA5A5;
	mcp->mb[6] = 0x5A5A;
	mcp->mb[7] = 0x2525;
	mcp->mb[8] = 0xBBBB;
	mcp->mb[9] = 0x6666;
	mcp->mb[10] = 0xBB66;
	mcp->mb[11] = 0x66BB;
	mcp->mb[12] = 0xB6B6;
	mcp->mb[13] = 0x6B6B;
	mcp->mb[14] = 0x3636;
	mcp->mb[15] = 0xCCCC;


	mcp->out_mb = MBX_15|MBX_14|MBX_13|MBX_12|MBX_11|MBX_10|MBX_9|MBX_8|
			MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_15|MBX_14|MBX_13|MBX_12|MBX_11|MBX_10|MBX_9|MBX_8|
			MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->buf_size = 0;
	mcp->flags = MBX_DMA_OUT;
	mcp->tov = MBX_TOV_SECONDS;
	rval = qlafx00_mailbox_command(vha, mcp);
	अगर (rval == QLA_SUCCESS) अणु
		अगर (mcp->mb[17] != 0xAAAA || mcp->mb[18] != 0x5555 ||
		    mcp->mb[19] != 0xAA55 || mcp->mb[20] != 0x55AA)
			rval = QLA_FUNCTION_FAILED;
		अगर (mcp->mb[21] != 0xA5A5 || mcp->mb[22] != 0x5A5A ||
		    mcp->mb[23] != 0x2525 || mcp->mb[24] != 0xBBBB)
			rval = QLA_FUNCTION_FAILED;
		अगर (mcp->mb[25] != 0x6666 || mcp->mb[26] != 0xBB66 ||
		    mcp->mb[27] != 0x66BB || mcp->mb[28] != 0xB6B6)
			rval = QLA_FUNCTION_FAILED;
		अगर (mcp->mb[29] != 0x6B6B || mcp->mb[30] != 0x3636 ||
		    mcp->mb[31] != 0xCCCC)
			rval = QLA_FUNCTION_FAILED;
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1170,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1171,
		    "Done %s.\n", __func__);
	पूर्ण
	वापस rval;
पूर्ण

/**
 * qlafx00_pci_config() - Setup ISPFx00 PCI configuration रेजिस्टरs.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qlafx00_pci_config(scsi_qla_host_t *vha)
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
		pcie_set_पढ़ोrq(ha->pdev, 2048);

	ha->chip_revision = ha->pdev->revision;

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qlafx00_soc_cpu_reset() - Perक्रमm warm reset of iSA(CPUs being reset on SOC).
 * @vha: HA context
 *
 */
अटल अंतरभूत व्योम
qlafx00_soc_cpu_reset(scsi_qla_host_t *vha)
अणु
	अचिन्हित दीर्घ flags = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक i, core;
	uपूर्णांक32_t cnt;
	uपूर्णांक32_t reg_val;

	spin_lock_irqsave(&ha->hardware_lock, flags);

	QLAFX00_SET_HBA_SOC_REG(ha, 0x80004, 0);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x82004, 0);

	/* stop the XOR DMA engines */
	QLAFX00_SET_HBA_SOC_REG(ha, 0x60920, 0x02);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x60924, 0x02);
	QLAFX00_SET_HBA_SOC_REG(ha, 0xf0920, 0x02);
	QLAFX00_SET_HBA_SOC_REG(ha, 0xf0924, 0x02);

	/* stop the IDMA engines */
	reg_val = QLAFX00_GET_HBA_SOC_REG(ha, 0x60840);
	reg_val &= ~(1<<12);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x60840, reg_val);

	reg_val = QLAFX00_GET_HBA_SOC_REG(ha, 0x60844);
	reg_val &= ~(1<<12);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x60844, reg_val);

	reg_val = QLAFX00_GET_HBA_SOC_REG(ha, 0x60848);
	reg_val &= ~(1<<12);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x60848, reg_val);

	reg_val = QLAFX00_GET_HBA_SOC_REG(ha, 0x6084C);
	reg_val &= ~(1<<12);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x6084C, reg_val);

	क्रम (i = 0; i < 100000; i++) अणु
		अगर ((QLAFX00_GET_HBA_SOC_REG(ha, 0xd0000) & 0x10000000) == 0 &&
		    (QLAFX00_GET_HBA_SOC_REG(ha, 0x10600) & 0x1) == 0)
			अवरोध;
		udelay(100);
	पूर्ण

	/* Set all 4 cores in reset */
	क्रम (i = 0; i < 4; i++) अणु
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_SW_RST_CONTROL_REG_CORE0 + 8*i), (0xF01));
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_SW_RST_CONTROL_REG_CORE0 + 4 + 8*i), (0x01010101));
	पूर्ण

	/* Reset all units in Fabric */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_RST_CONTROL_REG, (0x011f0101));

	/* */
	QLAFX00_SET_HBA_SOC_REG(ha, 0x10610, 1);
	QLAFX00_SET_HBA_SOC_REG(ha, 0x10600, 0);

	/* Set all 4 core Memory Power Down Registers */
	क्रम (i = 0; i < 5; i++) अणु
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_PWR_MANAGEMENT_PWR_DOWN_REG + 4*i), (0x0));
	पूर्ण

	/* Reset all पूर्णांकerrupt control रेजिस्टरs */
	क्रम (i = 0; i < 115; i++) अणु
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_INTERRUPT_SOURCE_I_CONTROL_REG + 4*i), (0x0));
	पूर्ण

	/* Reset Timers control रेजिस्टरs. per core */
	क्रम (core = 0; core < 4; core++)
		क्रम (i = 0; i < 8; i++)
			QLAFX00_SET_HBA_SOC_REG(ha,
			    (SOC_CORE_TIMER_REG + 0x100*core + 4*i), (0x0));

	/* Reset per core IRQ ack रेजिस्टर */
	क्रम (core = 0; core < 4; core++)
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_IRQ_ACK_REG + 0x100*core), (0x3FF));

	/* Set Fabric control and config to शेषs */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_CONTROL_REG, (0x2));
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_CONFIG_REG, (0x3));

	/* Kick in Fabric units */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_RST_CONTROL_REG, (0x0));

	/* Kick in Core0 to start boot process */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_SW_RST_CONTROL_REG_CORE0, (0xF00));

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/* Wait 10secs क्रम soft-reset to complete. */
	क्रम (cnt = 10; cnt; cnt--) अणु
		msleep(1000);
		barrier();
	पूर्ण
पूर्ण

/**
 * qlafx00_soft_reset() - Soft Reset ISPFx00.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qlafx00_soft_reset(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	अगर (unlikely(pci_channel_offline(ha->pdev) &&
	    ha->flags.pci_channel_io_perm_failure))
		वापस rval;

	ha->isp_ops->disable_पूर्णांकrs(ha);
	qlafx00_soc_cpu_reset(vha);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qlafx00_chip_diag() - Test ISPFx00 क्रम proper operation.
 * @vha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qlafx00_chip_diag(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];

	ha->fw_transfer_size = REQUEST_ENTRY_SIZE * req->length;

	rval = qlafx00_mbx_reg_test(vha);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x1165,
		    "Failed mailbox send register test\n");
	पूर्ण अन्यथा अणु
		/* Flag a successful rval */
		rval = QLA_SUCCESS;
	पूर्ण
	वापस rval;
पूर्ण

व्योम
qlafx00_config_rings(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;

	wrt_reg_dword(&reg->req_q_in, 0);
	wrt_reg_dword(&reg->req_q_out, 0);

	wrt_reg_dword(&reg->rsp_q_in, 0);
	wrt_reg_dword(&reg->rsp_q_out, 0);

	/* PCI posting */
	rd_reg_dword(&reg->rsp_q_out);
पूर्ण

अक्षर *
qlafx00_pci_info_str(काष्ठा scsi_qla_host *vha, अक्षर *str, माप_प्रकार str_len)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (pci_is_pcie(ha->pdev))
		strlcpy(str, "PCIe iSA", str_len);
	वापस str;
पूर्ण

अक्षर *
qlafx00_fw_version_str(काष्ठा scsi_qla_host *vha, अक्षर *str, माप_प्रकार size)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	snम_लिखो(str, size, "%s", ha->mr.fw_version);
	वापस str;
पूर्ण

व्योम
qlafx00_enable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->पूर्णांकerrupts_on = 1;
	QLAFX00_ENABLE_ICNTRL_REG(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

व्योम
qlafx00_disable_पूर्णांकrs(काष्ठा qla_hw_data *ha)
अणु
	अचिन्हित दीर्घ flags = 0;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->पूर्णांकerrupts_on = 0;
	QLAFX00_DISABLE_ICNTRL_REG(ha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
पूर्ण

पूर्णांक
qlafx00_पात_target(fc_port_t *fcport, uपूर्णांक64_t l, पूर्णांक tag)
अणु
	वापस qla2x00_async_पंचांग_cmd(fcport, TCF_TARGET_RESET, l, tag);
पूर्ण

पूर्णांक
qlafx00_lun_reset(fc_port_t *fcport, uपूर्णांक64_t l, पूर्णांक tag)
अणु
	वापस qla2x00_async_पंचांग_cmd(fcport, TCF_LUN_RESET, l, tag);
पूर्ण

पूर्णांक
qlafx00_loop_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक ret;
	काष्ठा fc_port *fcport;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (ql2xtargetreset) अणु
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (fcport->port_type != FCT_TARGET)
				जारी;

			ret = ha->isp_ops->target_reset(fcport, 0, 0);
			अगर (ret != QLA_SUCCESS) अणु
				ql_dbg(ql_dbg_taskm, vha, 0x803d,
				    "Bus Reset failed: Reset=%d "
				    "d_id=%x.\n", ret, fcport->d_id.b24);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक
qlafx00_iospace_config(काष्ठा qla_hw_data *ha)
अणु
	अगर (pci_request_selected_regions(ha->pdev, ha->bars,
	    QLA2XXX_DRIVER_NAME)) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x014e,
		    "Failed to reserve PIO/MMIO regions (%s), aborting.\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	/* Use MMIO operations क्रम all accesses. */
	अगर (!(pci_resource_flags(ha->pdev, 0) & IORESOURCE_MEM)) अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x014f,
		    "Invalid pci I/O region size (%s).\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण
	अगर (pci_resource_len(ha->pdev, 0) < BAR0_LEN_FX00) अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x0127,
		    "Invalid PCI mem BAR0 region size (%s), aborting\n",
			pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	ha->cregbase =
	    ioremap(pci_resource_start(ha->pdev, 0), BAR0_LEN_FX00);
	अगर (!ha->cregbase) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0128,
		    "cannot remap MMIO (%s), aborting\n", pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	अगर (!(pci_resource_flags(ha->pdev, 2) & IORESOURCE_MEM)) अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x0129,
		    "region #2 not an MMIO resource (%s), aborting\n",
		    pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण
	अगर (pci_resource_len(ha->pdev, 2) < BAR2_LEN_FX00) अणु
		ql_log_pci(ql_log_warn, ha->pdev, 0x012a,
		    "Invalid PCI mem BAR2 region size (%s), aborting\n",
			pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	ha->iobase =
	    ioremap(pci_resource_start(ha->pdev, 2), BAR2_LEN_FX00);
	अगर (!ha->iobase) अणु
		ql_log_pci(ql_log_fatal, ha->pdev, 0x012b,
		    "cannot remap MMIO (%s), aborting\n", pci_name(ha->pdev));
		जाओ iospace_error_निकास;
	पूर्ण

	/* Determine queue resources */
	ha->max_req_queues = ha->max_rsp_queues = 1;

	ql_log_pci(ql_log_info, ha->pdev, 0x012c,
	    "Bars 0x%x, iobase0 0x%p, iobase2 0x%p\n",
	    ha->bars, ha->cregbase, ha->iobase);

	वापस 0;

iospace_error_निकास:
	वापस -ENOMEM;
पूर्ण

अटल व्योम
qlafx00_save_queue_ptrs(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];

	req->length_fx00 = req->length;
	req->ring_fx00 = req->ring;
	req->dma_fx00 = req->dma;

	rsp->length_fx00 = rsp->length;
	rsp->ring_fx00 = rsp->ring;
	rsp->dma_fx00 = rsp->dma;

	ql_dbg(ql_dbg_init, vha, 0x012d,
	    "req: %p, ring_fx00: %p, length_fx00: 0x%x,"
	    "req->dma_fx00: 0x%llx\n", req, req->ring_fx00,
	    req->length_fx00, (u64)req->dma_fx00);

	ql_dbg(ql_dbg_init, vha, 0x012e,
	    "rsp: %p, ring_fx00: %p, length_fx00: 0x%x,"
	    "rsp->dma_fx00: 0x%llx\n", rsp, rsp->ring_fx00,
	    rsp->length_fx00, (u64)rsp->dma_fx00);
पूर्ण

अटल पूर्णांक
qlafx00_config_queues(काष्ठा scsi_qla_host *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = ha->req_q_map[0];
	काष्ठा rsp_que *rsp = ha->rsp_q_map[0];
	dma_addr_t bar2_hdl = pci_resource_start(ha->pdev, 2);

	req->length = ha->req_que_len;
	req->ring = (व्योम __क्रमce *)ha->iobase + ha->req_que_off;
	req->dma = bar2_hdl + ha->req_que_off;
	अगर ((!req->ring) || (req->length == 0)) अणु
		ql_log_pci(ql_log_info, ha->pdev, 0x012f,
		    "Unable to allocate memory for req_ring\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x0130,
	    "req: %p req_ring pointer %p req len 0x%x "
	    "req off 0x%x\n, req->dma: 0x%llx",
	    req, req->ring, req->length,
	    ha->req_que_off, (u64)req->dma);

	rsp->length = ha->rsp_que_len;
	rsp->ring = (व्योम __क्रमce *)ha->iobase + ha->rsp_que_off;
	rsp->dma = bar2_hdl + ha->rsp_que_off;
	अगर ((!rsp->ring) || (rsp->length == 0)) अणु
		ql_log_pci(ql_log_info, ha->pdev, 0x0131,
		    "Unable to allocate memory for rsp_ring\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	ql_dbg(ql_dbg_init, vha, 0x0132,
	    "rsp: %p rsp_ring pointer %p rsp len 0x%x "
	    "rsp off 0x%x, rsp->dma: 0x%llx\n",
	    rsp, rsp->ring, rsp->length,
	    ha->rsp_que_off, (u64)rsp->dma);

	वापस QLA_SUCCESS;
पूर्ण

अटल पूर्णांक
qlafx00_init_fw_पढ़ोy(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = 0;
	अचिन्हित दीर्घ wसमय;
	uपूर्णांक16_t रुको_समय;	/* Wait समय */
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;
	uपूर्णांक32_t aenmbx, aenmbx7 = 0;
	uपूर्णांक32_t pseuकरो_aen;
	uपूर्णांक32_t state[5];
	bool करोne = false;

	/* 30 seconds रुको - Adjust अगर required */
	रुको_समय = 30;

	pseuकरो_aen = rd_reg_dword(&reg->pseuकरोaen);
	अगर (pseuकरो_aen == 1) अणु
		aenmbx7 = rd_reg_dword(&reg->initval7);
		ha->mbx_पूर्णांकr_code = MSW(aenmbx7);
		ha->rqstq_पूर्णांकr_code = LSW(aenmbx7);
		rval = qlafx00_driver_shutकरोwn(vha, 10);
		अगर (rval != QLA_SUCCESS)
			qlafx00_soft_reset(vha);
	पूर्ण

	/* रुको समय beक्रमe firmware पढ़ोy */
	wसमय = jअगरfies + (रुको_समय * HZ);
	करो अणु
		aenmbx = rd_reg_dword(&reg->aenmailbox0);
		barrier();
		ql_dbg(ql_dbg_mbx, vha, 0x0133,
		    "aenmbx: 0x%x\n", aenmbx);

		चयन (aenmbx) अणु
		हाल MBA_FW_NOT_STARTED:
		हाल MBA_FW_STARTING:
			अवरोध;

		हाल MBA_SYSTEM_ERR:
		हाल MBA_REQ_TRANSFER_ERR:
		हाल MBA_RSP_TRANSFER_ERR:
		हाल MBA_FW_INIT_FAILURE:
			qlafx00_soft_reset(vha);
			अवरोध;

		हाल MBA_FW_RESTART_CMPLT:
			/* Set the mbx and rqstq पूर्णांकr code */
			aenmbx7 = rd_reg_dword(&reg->aenmailbox7);
			ha->mbx_पूर्णांकr_code = MSW(aenmbx7);
			ha->rqstq_पूर्णांकr_code = LSW(aenmbx7);
			ha->req_que_off = rd_reg_dword(&reg->aenmailbox1);
			ha->rsp_que_off = rd_reg_dword(&reg->aenmailbox3);
			ha->req_que_len = rd_reg_dword(&reg->aenmailbox5);
			ha->rsp_que_len = rd_reg_dword(&reg->aenmailbox6);
			wrt_reg_dword(&reg->aenmailbox0, 0);
			rd_reg_dword_relaxed(&reg->aenmailbox0);
			ql_dbg(ql_dbg_init, vha, 0x0134,
			    "f/w returned mbx_intr_code: 0x%x, "
			    "rqstq_intr_code: 0x%x\n",
			    ha->mbx_पूर्णांकr_code, ha->rqstq_पूर्णांकr_code);
			QLAFX00_CLR_INTR_REG(ha, QLAFX00_HST_INT_STS_BITS);
			rval = QLA_SUCCESS;
			करोne = true;
			अवरोध;

		शेष:
			अगर ((aenmbx & 0xFF00) == MBA_FW_INIT_INPROGRESS)
				अवरोध;

			/* If fw is apparently not पढ़ोy. In order to जारी,
			 * we might need to issue Mbox cmd, but the problem is
			 * that the DoorBell vector values that come with the
			 * 8060 AEN are most likely gone by now (and thus no
			 * bell would be rung on the fw side when mbox cmd is
			 * issued). We have to thereक्रमe grab the 8060 AEN
			 * shaकरोw regs (filled in by FW when the last 8060
			 * AEN was being posted).
			 * Do the following to determine what is needed in
			 * order to get the FW पढ़ोy:
			 * 1. reload the 8060 AEN values from the shaकरोw regs
			 * 2. clear पूर्णांक status to get rid of possible pending
			 *    पूर्णांकerrupts
			 * 3. issue Get FW State Mbox cmd to determine fw state
			 * Set the mbx and rqstq पूर्णांकr code from Shaकरोw Regs
			 */
			aenmbx7 = rd_reg_dword(&reg->initval7);
			ha->mbx_पूर्णांकr_code = MSW(aenmbx7);
			ha->rqstq_पूर्णांकr_code = LSW(aenmbx7);
			ha->req_que_off = rd_reg_dword(&reg->initval1);
			ha->rsp_que_off = rd_reg_dword(&reg->initval3);
			ha->req_que_len = rd_reg_dword(&reg->initval5);
			ha->rsp_que_len = rd_reg_dword(&reg->initval6);
			ql_dbg(ql_dbg_init, vha, 0x0135,
			    "f/w returned mbx_intr_code: 0x%x, "
			    "rqstq_intr_code: 0x%x\n",
			    ha->mbx_पूर्णांकr_code, ha->rqstq_पूर्णांकr_code);
			QLAFX00_CLR_INTR_REG(ha, QLAFX00_HST_INT_STS_BITS);

			/* Get the FW state */
			rval = qlafx00_get_firmware_state(vha, state);
			अगर (rval != QLA_SUCCESS) अणु
				/* Retry अगर समयr has not expired */
				अवरोध;
			पूर्ण

			अगर (state[0] == FSTATE_FX00_CONFIG_WAIT) अणु
				/* Firmware is रुकोing to be
				 * initialized by driver
				 */
				rval = QLA_SUCCESS;
				करोne = true;
				अवरोध;
			पूर्ण

			/* Issue driver shutकरोwn and रुको until f/w recovers.
			 * Driver should जारी to poll until 8060 AEN is
			 * received indicating firmware recovery.
			 */
			ql_dbg(ql_dbg_init, vha, 0x0136,
			    "Sending Driver shutdown fw_state 0x%x\n",
			    state[0]);

			rval = qlafx00_driver_shutकरोwn(vha, 10);
			अगर (rval != QLA_SUCCESS) अणु
				rval = QLA_FUNCTION_FAILED;
				अवरोध;
			पूर्ण
			msleep(500);

			wसमय = jअगरfies + (रुको_समय * HZ);
			अवरोध;
		पूर्ण

		अगर (!करोne) अणु
			अगर (समय_after_eq(jअगरfies, wसमय)) अणु
				ql_dbg(ql_dbg_init, vha, 0x0137,
				    "Init f/w failed: aen[7]: 0x%x\n",
				    rd_reg_dword(&reg->aenmailbox7));
				rval = QLA_FUNCTION_FAILED;
				करोne = true;
				अवरोध;
			पूर्ण
			/* Delay क्रम a जबतक */
			msleep(500);
		पूर्ण
	पूर्ण जबतक (!करोne);

	अगर (rval)
		ql_dbg(ql_dbg_init, vha, 0x0138,
		    "%s **** FAILED ****.\n", __func__);
	अन्यथा
		ql_dbg(ql_dbg_init, vha, 0x0139,
		    "%s **** SUCCESS ****.\n", __func__);

	वापस rval;
पूर्ण

/*
 * qlafx00_fw_पढ़ोy() - Waits क्रम firmware पढ़ोy.
 * @ha: HA context
 *
 * Returns 0 on success.
 */
पूर्णांक
qlafx00_fw_पढ़ोy(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	अचिन्हित दीर्घ	wसमय;
	uपूर्णांक16_t	रुको_समय;	/* Wait समय अगर loop is coming पढ़ोy */
	uपूर्णांक32_t	state[5];

	rval = QLA_SUCCESS;

	रुको_समय = 10;

	/* रुको समय beक्रमe firmware पढ़ोy */
	wसमय = jअगरfies + (रुको_समय * HZ);

	/* Wait क्रम ISP to finish init */
	अगर (!vha->flags.init_करोne)
		ql_dbg(ql_dbg_init, vha, 0x013a,
		    "Waiting for init to complete...\n");

	करो अणु
		rval = qlafx00_get_firmware_state(vha, state);

		अगर (rval == QLA_SUCCESS) अणु
			अगर (state[0] == FSTATE_FX00_INITIALIZED) अणु
				ql_dbg(ql_dbg_init, vha, 0x013b,
				    "fw_state=%x\n", state[0]);
				rval = QLA_SUCCESS;
					अवरोध;
			पूर्ण
		पूर्ण
		rval = QLA_FUNCTION_FAILED;

		अगर (समय_after_eq(jअगरfies, wसमय))
			अवरोध;

		/* Delay क्रम a जबतक */
		msleep(500);

		ql_dbg(ql_dbg_init, vha, 0x013c,
		    "fw_state=%x curr time=%lx.\n", state[0], jअगरfies);
	पूर्ण जबतक (1);


	अगर (rval)
		ql_dbg(ql_dbg_init, vha, 0x013d,
		    "Firmware ready **** FAILED ****.\n");
	अन्यथा
		ql_dbg(ql_dbg_init, vha, 0x013e,
		    "Firmware ready **** SUCCESS ****.\n");

	वापस rval;
पूर्ण

अटल पूर्णांक
qlafx00_find_all_tarमाला_लो(scsi_qla_host_t *vha,
	काष्ठा list_head *new_fcports)
अणु
	पूर्णांक		rval;
	uपूर्णांक16_t	tgt_id;
	fc_port_t	*fcport, *new_fcport;
	पूर्णांक		found;
	काष्ठा qla_hw_data *ha = vha->hw;

	rval = QLA_SUCCESS;

	अगर (!test_bit(LOOP_RESYNC_ACTIVE, &vha->dpc_flags))
		वापस QLA_FUNCTION_FAILED;

	अगर ((atomic_पढ़ो(&vha->loop_करोwn_समयr) ||
	     STATE_TRANSITION(vha))) अणु
		atomic_set(&vha->loop_करोwn_समयr, 0);
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	ql_dbg(ql_dbg_disc + ql_dbg_init, vha, 0x2088,
	    "Listing Target bit map...\n");
	ql_dump_buffer(ql_dbg_disc + ql_dbg_init, vha, 0x2089,
	    ha->gid_list, 32);

	/* Allocate temporary rmtport क्रम any new rmtports discovered. */
	new_fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
	अगर (new_fcport == शून्य)
		वापस QLA_MEMORY_ALLOC_FAILED;

	क्रम_each_set_bit(tgt_id, (व्योम *)ha->gid_list,
	    QLAFX00_TGT_NODE_LIST_SIZE) अणु

		/* Send get target node info */
		new_fcport->tgt_id = tgt_id;
		rval = qlafx00_fx_disc(vha, new_fcport,
		    FXDISC_GET_TGT_NODE_INFO);
		अगर (rval != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x208a,
			    "Target info scan failed -- assuming zero-entry "
			    "result...\n");
			जारी;
		पूर्ण

		/* Locate matching device in database. */
		found = 0;
		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			अगर (स_भेद(new_fcport->port_name,
			    fcport->port_name, WWN_SIZE))
				जारी;

			found++;

			/*
			 * If tgt_id is same and state FCS_ONLINE, nothing
			 * changed.
			 */
			अगर (fcport->tgt_id == new_fcport->tgt_id &&
			    atomic_पढ़ो(&fcport->state) == FCS_ONLINE)
				अवरोध;

			/*
			 * Tgt ID changed or device was marked to be updated.
			 */
			ql_dbg(ql_dbg_disc + ql_dbg_init, vha, 0x208b,
			    "TGT-ID Change(%s): Present tgt id: "
			    "0x%x state: 0x%x "
			    "wwnn = %llx wwpn = %llx.\n",
			    __func__, fcport->tgt_id,
			    atomic_पढ़ो(&fcport->state),
			    (अचिन्हित दीर्घ दीर्घ)wwn_to_u64(fcport->node_name),
			    (अचिन्हित दीर्घ दीर्घ)wwn_to_u64(fcport->port_name));

			ql_log(ql_log_info, vha, 0x208c,
			    "TGT-ID Announce(%s): Discovered tgt "
			    "id 0x%x wwnn = %llx "
			    "wwpn = %llx.\n", __func__, new_fcport->tgt_id,
			    (अचिन्हित दीर्घ दीर्घ)
			    wwn_to_u64(new_fcport->node_name),
			    (अचिन्हित दीर्घ दीर्घ)
			    wwn_to_u64(new_fcport->port_name));

			अगर (atomic_पढ़ो(&fcport->state) != FCS_ONLINE) अणु
				fcport->old_tgt_id = fcport->tgt_id;
				fcport->tgt_id = new_fcport->tgt_id;
				ql_log(ql_log_info, vha, 0x208d,
				   "TGT-ID: New fcport Added: %p\n", fcport);
				qla2x00_update_fcport(vha, fcport);
			पूर्ण अन्यथा अणु
				ql_log(ql_log_info, vha, 0x208e,
				    " Existing TGT-ID %x did not get "
				    " offline event from firmware.\n",
				    fcport->old_tgt_id);
				qla2x00_mark_device_lost(vha, fcport, 0);
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				qla2x00_मुक्त_fcport(new_fcport);
				वापस rval;
			पूर्ण
			अवरोध;
		पूर्ण

		अगर (found)
			जारी;

		/* If device was not in our fcports list, then add it. */
		list_add_tail(&new_fcport->list, new_fcports);

		/* Allocate a new replacement fcport. */
		new_fcport = qla2x00_alloc_fcport(vha, GFP_KERNEL);
		अगर (new_fcport == शून्य)
			वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	qla2x00_मुक्त_fcport(new_fcport);
	वापस rval;
पूर्ण

/*
 * qlafx00_configure_all_tarमाला_लो
 *      Setup target devices with node ID's.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success.
 *      BIT_0 = error
 */
अटल पूर्णांक
qlafx00_configure_all_tarमाला_लो(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	fc_port_t *fcport, *rmptemp;
	LIST_HEAD(new_fcports);

	rval = qlafx00_fx_disc(vha, &vha->hw->mr.fcport,
	    FXDISC_GET_TGT_NODE_LIST);
	अगर (rval != QLA_SUCCESS) अणु
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		वापस rval;
	पूर्ण

	rval = qlafx00_find_all_tarमाला_लो(vha, &new_fcports);
	अगर (rval != QLA_SUCCESS) अणु
		set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
		वापस rval;
	पूर्ण

	/*
	 * Delete all previous devices marked lost.
	 */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
			अवरोध;

		अगर (atomic_पढ़ो(&fcport->state) == FCS_DEVICE_LOST) अणु
			अगर (fcport->port_type != FCT_INITIATOR)
				qla2x00_mark_device_lost(vha, fcport, 0);
		पूर्ण
	पूर्ण

	/*
	 * Add the new devices to our devices list.
	 */
	list_क्रम_each_entry_safe(fcport, rmptemp, &new_fcports, list) अणु
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags))
			अवरोध;

		qla2x00_update_fcport(vha, fcport);
		list_move_tail(&fcport->list, &vha->vp_fcports);
		ql_log(ql_log_info, vha, 0x208f,
		    "Attach new target id 0x%x wwnn = %llx "
		    "wwpn = %llx.\n",
		    fcport->tgt_id,
		    (अचिन्हित दीर्घ दीर्घ)wwn_to_u64(fcport->node_name),
		    (अचिन्हित दीर्घ दीर्घ)wwn_to_u64(fcport->port_name));
	पूर्ण

	/* Free all new device काष्ठाures not processed. */
	list_क्रम_each_entry_safe(fcport, rmptemp, &new_fcports, list) अणु
		list_del(&fcport->list);
		qla2x00_मुक्त_fcport(fcport);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qlafx00_configure_devices
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
पूर्णांक
qlafx00_configure_devices(scsi_qla_host_t *vha)
अणु
	पूर्णांक  rval;
	अचिन्हित दीर्घ flags;

	rval = QLA_SUCCESS;

	flags = vha->dpc_flags;

	ql_dbg(ql_dbg_disc, vha, 0x2090,
	    "Configure devices -- dpc flags =0x%lx\n", flags);

	rval = qlafx00_configure_all_tarमाला_लो(vha);

	अगर (rval == QLA_SUCCESS) अणु
		अगर (test_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags)) अणु
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			atomic_set(&vha->loop_state, LOOP_READY);
			ql_log(ql_log_info, vha, 0x2091,
			    "Device Ready\n");
		पूर्ण
	पूर्ण

	अगर (rval) अणु
		ql_dbg(ql_dbg_disc, vha, 0x2092,
		    "%s *** FAILED ***.\n", __func__);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_disc, vha, 0x2093,
		    "%s: exiting normally.\n", __func__);
	पूर्ण
	वापस rval;
पूर्ण

अटल व्योम
qlafx00_पात_isp_cleanup(scsi_qla_host_t *vha, bool critemp)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	fc_port_t *fcport;

	vha->flags.online = 0;
	ha->mr.fw_hbt_en = 0;

	अगर (!critemp) अणु
		ha->flags.chip_reset_करोne = 0;
		clear_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		vha->qla_stats.total_isp_पातs++;
		ql_log(ql_log_info, vha, 0x013f,
		    "Performing ISP error recovery - ha = %p.\n", ha);
		ha->isp_ops->reset_chip(vha);
	पूर्ण

	अगर (atomic_पढ़ो(&vha->loop_state) != LOOP_DOWN) अणु
		atomic_set(&vha->loop_state, LOOP_DOWN);
		atomic_set(&vha->loop_करोwn_समयr,
		    QLAFX00_LOOP_DOWN_TIME);
	पूर्ण अन्यथा अणु
		अगर (!atomic_पढ़ो(&vha->loop_करोwn_समयr))
			atomic_set(&vha->loop_करोwn_समयr,
			    QLAFX00_LOOP_DOWN_TIME);
	पूर्ण

	/* Clear all async request states across all VPs. */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		fcport->flags = 0;
		अगर (atomic_पढ़ो(&fcport->state) == FCS_ONLINE)
			qla2x00_set_fcport_state(fcport, FCS_DEVICE_LOST);
	पूर्ण

	अगर (!ha->flags.eeh_busy) अणु
		अगर (critemp) अणु
			qla2x00_पात_all_cmds(vha, DID_NO_CONNECT << 16);
		पूर्ण अन्यथा अणु
			/* Requeue all commands in outstanding command list. */
			qla2x00_पात_all_cmds(vha, DID_RESET << 16);
		पूर्ण
	पूर्ण

	qla2x00_मुक्त_irqs(vha);
	अगर (critemp)
		set_bit(FX00_CRITEMP_RECOVERY, &vha->dpc_flags);
	अन्यथा
		set_bit(FX00_RESET_RECOVERY, &vha->dpc_flags);

	/* Clear the Interrupts */
	QLAFX00_CLR_INTR_REG(ha, QLAFX00_HST_INT_STS_BITS);

	ql_log(ql_log_info, vha, 0x0140,
	    "%s Done done - ha=%p.\n", __func__, ha);
पूर्ण

/**
 * qlafx00_init_response_q_entries() - Initializes response queue entries.
 * @rsp: response queue
 *
 * Beginning of request ring has initialization control block alपढ़ोy built
 * by nvram config routine.
 *
 * Returns 0 on success.
 */
व्योम
qlafx00_init_response_q_entries(काष्ठा rsp_que *rsp)
अणु
	uपूर्णांक16_t cnt;
	response_t *pkt;

	rsp->ring_ptr = rsp->ring;
	rsp->ring_index    = 0;
	rsp->status_srb = शून्य;
	pkt = rsp->ring_ptr;
	क्रम (cnt = 0; cnt < rsp->length; cnt++) अणु
		pkt->signature = RESPONSE_PROCESSED;
		wrt_reg_dword((व्योम __क्रमce __iomem *)&pkt->signature,
		    RESPONSE_PROCESSED);
		pkt++;
	पूर्ण
पूर्ण

पूर्णांक
qlafx00_rescan_isp(scsi_qla_host_t *vha)
अणु
	uपूर्णांक32_t status = QLA_FUNCTION_FAILED;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;
	uपूर्णांक32_t aenmbx7;

	qla2x00_request_irqs(ha, ha->rsp_q_map[0]);

	aenmbx7 = rd_reg_dword(&reg->aenmailbox7);
	ha->mbx_पूर्णांकr_code = MSW(aenmbx7);
	ha->rqstq_पूर्णांकr_code = LSW(aenmbx7);
	ha->req_que_off = rd_reg_dword(&reg->aenmailbox1);
	ha->rsp_que_off = rd_reg_dword(&reg->aenmailbox3);
	ha->req_que_len = rd_reg_dword(&reg->aenmailbox5);
	ha->rsp_que_len = rd_reg_dword(&reg->aenmailbox6);

	ql_dbg(ql_dbg_disc, vha, 0x2094,
	    "fw returned mbx_intr_code: 0x%x, rqstq_intr_code: 0x%x "
	    " Req que offset 0x%x Rsp que offset 0x%x\n",
	    ha->mbx_पूर्णांकr_code, ha->rqstq_पूर्णांकr_code,
	    ha->req_que_off, ha->rsp_que_len);

	/* Clear the Interrupts */
	QLAFX00_CLR_INTR_REG(ha, QLAFX00_HST_INT_STS_BITS);

	status = qla2x00_init_rings(vha);
	अगर (!status) अणु
		vha->flags.online = 1;

		/* अगर no cable then assume it's good */
		अगर ((vha->device_flags & DFLG_NO_CABLE))
			status = 0;
		/* Register प्रणाली inक्रमmation */
		अगर (qlafx00_fx_disc(vha,
		    &vha->hw->mr.fcport, FXDISC_REG_HOST_INFO))
			ql_dbg(ql_dbg_disc, vha, 0x2095,
			    "failed to register host info\n");
	पूर्ण
	scsi_unblock_requests(vha->host);
	वापस status;
पूर्ण

व्योम
qlafx00_समयr_routine(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t fw_heart_beat;
	uपूर्णांक32_t aenmbx0;
	काष्ठा device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;
	uपूर्णांक32_t tempc;

	/* Check firmware health */
	अगर (ha->mr.fw_hbt_cnt)
		ha->mr.fw_hbt_cnt--;
	अन्यथा अणु
		अगर ((!ha->flags.mr_reset_hdlr_active) &&
		    (!test_bit(UNLOADING, &vha->dpc_flags)) &&
		    (!test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags)) &&
		    (ha->mr.fw_hbt_en)) अणु
			fw_heart_beat = rd_reg_dword(&reg->fwheartbeat);
			अगर (fw_heart_beat != ha->mr.old_fw_hbt_cnt) अणु
				ha->mr.old_fw_hbt_cnt = fw_heart_beat;
				ha->mr.fw_hbt_miss_cnt = 0;
			पूर्ण अन्यथा अणु
				ha->mr.fw_hbt_miss_cnt++;
				अगर (ha->mr.fw_hbt_miss_cnt ==
				    QLAFX00_HEARTBEAT_MISS_CNT) अणु
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
					qla2xxx_wake_dpc(vha);
					ha->mr.fw_hbt_miss_cnt = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		ha->mr.fw_hbt_cnt = QLAFX00_HEARTBEAT_INTERVAL;
	पूर्ण

	अगर (test_bit(FX00_RESET_RECOVERY, &vha->dpc_flags)) अणु
		/* Reset recovery to be perक्रमmed in समयr routine */
		aenmbx0 = rd_reg_dword(&reg->aenmailbox0);
		अगर (ha->mr.fw_reset_समयr_exp) अणु
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			ha->mr.fw_reset_समयr_exp = 0;
		पूर्ण अन्यथा अगर (aenmbx0 == MBA_FW_RESTART_CMPLT) अणु
			/* Wake up DPC to rescan the tarमाला_लो */
			set_bit(FX00_TARGET_SCAN, &vha->dpc_flags);
			clear_bit(FX00_RESET_RECOVERY, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			ha->mr.fw_reset_समयr_tick = QLAFX00_RESET_INTERVAL;
		पूर्ण अन्यथा अगर ((aenmbx0 == MBA_FW_STARTING) &&
		    (!ha->mr.fw_hbt_en)) अणु
			ha->mr.fw_hbt_en = 1;
		पूर्ण अन्यथा अगर (!ha->mr.fw_reset_समयr_tick) अणु
			अगर (aenmbx0 == ha->mr.old_aenmbx0_state)
				ha->mr.fw_reset_समयr_exp = 1;
			ha->mr.fw_reset_समयr_tick = QLAFX00_RESET_INTERVAL;
		पूर्ण अन्यथा अगर (aenmbx0 == 0xFFFFFFFF) अणु
			uपूर्णांक32_t data0, data1;

			data0 = QLAFX00_RD_REG(ha,
			    QLAFX00_BAR1_BASE_ADDR_REG);
			data1 = QLAFX00_RD_REG(ha,
			    QLAFX00_PEX0_WIN0_BASE_ADDR_REG);

			data0 &= 0xffff0000;
			data1 &= 0x0000ffff;

			QLAFX00_WR_REG(ha,
			    QLAFX00_PEX0_WIN0_BASE_ADDR_REG,
			    (data0 | data1));
		पूर्ण अन्यथा अगर ((aenmbx0 & 0xFF00) == MBA_FW_POLL_STATE) अणु
			ha->mr.fw_reset_समयr_tick =
			    QLAFX00_MAX_RESET_INTERVAL;
		पूर्ण अन्यथा अगर (aenmbx0 == MBA_FW_RESET_FCT) अणु
			ha->mr.fw_reset_समयr_tick =
			    QLAFX00_MAX_RESET_INTERVAL;
		पूर्ण
		अगर (ha->mr.old_aenmbx0_state != aenmbx0) अणु
			ha->mr.old_aenmbx0_state = aenmbx0;
			ha->mr.fw_reset_समयr_tick = QLAFX00_RESET_INTERVAL;
		पूर्ण
		ha->mr.fw_reset_समयr_tick--;
	पूर्ण
	अगर (test_bit(FX00_CRITEMP_RECOVERY, &vha->dpc_flags)) अणु
		/*
		 * Critical temperature recovery to be
		 * perक्रमmed in समयr routine
		 */
		अगर (ha->mr.fw_critemp_समयr_tick == 0) अणु
			tempc = QLAFX00_GET_TEMPERATURE(ha);
			ql_dbg(ql_dbg_समयr, vha, 0x6012,
			    "ISPFx00(%s): Critical temp timer, "
			    "current SOC temperature: %d\n",
			    __func__, tempc);
			अगर (tempc < ha->mr.critical_temperature) अणु
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				clear_bit(FX00_CRITEMP_RECOVERY,
				    &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण
			ha->mr.fw_critemp_समयr_tick =
			    QLAFX00_CRITEMP_INTERVAL;
		पूर्ण अन्यथा अणु
			ha->mr.fw_critemp_समयr_tick--;
		पूर्ण
	पूर्ण
	अगर (ha->mr.host_info_resend) अणु
		/*
		 * Incomplete host info might be sent to firmware
		 * durinng प्रणाली boot - info should be resend
		 */
		अगर (ha->mr.hinfo_resend_समयr_tick == 0) अणु
			ha->mr.host_info_resend = false;
			set_bit(FX00_HOST_INFO_RESEND, &vha->dpc_flags);
			ha->mr.hinfo_resend_समयr_tick =
			    QLAFX00_HINFO_RESEND_INTERVAL;
			qla2xxx_wake_dpc(vha);
		पूर्ण अन्यथा अणु
			ha->mr.hinfo_resend_समयr_tick--;
		पूर्ण
	पूर्ण

पूर्ण

/*
 *  qlfx00a_reset_initialize
 *      Re-initialize after a iSA device reset.
 *
 * Input:
 *      ha  = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
पूर्णांक
qlafx00_reset_initialize(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->device_flags & DFLG_DEV_FAILED) अणु
		ql_dbg(ql_dbg_init, vha, 0x0142,
		    "Device in failed state\n");
		वापस QLA_SUCCESS;
	पूर्ण

	ha->flags.mr_reset_hdlr_active = 1;

	अगर (vha->flags.online) अणु
		scsi_block_requests(vha->host);
		qlafx00_पात_isp_cleanup(vha, false);
	पूर्ण

	ql_log(ql_log_info, vha, 0x0143,
	    "(%s): succeeded.\n", __func__);
	ha->flags.mr_reset_hdlr_active = 0;
	वापस QLA_SUCCESS;
पूर्ण

/*
 *  qlafx00_पात_isp
 *      Resets ISP and पातs all outstanding commands.
 *
 * Input:
 *      ha  = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
पूर्णांक
qlafx00_पात_isp(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (vha->flags.online) अणु
		अगर (unlikely(pci_channel_offline(ha->pdev) &&
		    ha->flags.pci_channel_io_perm_failure)) अणु
			clear_bit(ISP_ABORT_RETRY, &vha->dpc_flags);
			वापस QLA_SUCCESS;
		पूर्ण

		scsi_block_requests(vha->host);
		qlafx00_पात_isp_cleanup(vha, false);
	पूर्ण अन्यथा अणु
		scsi_block_requests(vha->host);
		clear_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		vha->qla_stats.total_isp_पातs++;
		ha->isp_ops->reset_chip(vha);
		set_bit(FX00_RESET_RECOVERY, &vha->dpc_flags);
		/* Clear the Interrupts */
		QLAFX00_CLR_INTR_REG(ha, QLAFX00_HST_INT_STS_BITS);
	पूर्ण

	ql_log(ql_log_info, vha, 0x0145,
	    "(%s): succeeded.\n", __func__);

	वापस QLA_SUCCESS;
पूर्ण

अटल अंतरभूत fc_port_t*
qlafx00_get_fcport(काष्ठा scsi_qla_host *vha, पूर्णांक tgt_id)
अणु
	fc_port_t	*fcport;

	/* Check क्रम matching device in remote port list. */
	list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
		अगर (fcport->tgt_id == tgt_id) अणु
			ql_dbg(ql_dbg_async, vha, 0x5072,
			    "Matching fcport(%p) found with TGT-ID: 0x%x "
			    "and Remote TGT_ID: 0x%x\n",
			    fcport, fcport->tgt_id, tgt_id);
			वापस fcport;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
qlafx00_tgt_detach(काष्ठा scsi_qla_host *vha, पूर्णांक tgt_id)
अणु
	fc_port_t	*fcport;

	ql_log(ql_log_info, vha, 0x5073,
	    "Detach TGT-ID: 0x%x\n", tgt_id);

	fcport = qlafx00_get_fcport(vha, tgt_id);
	अगर (!fcport)
		वापस;

	qla2x00_mark_device_lost(vha, fcport, 0);

	वापस;
पूर्ण

व्योम
qlafx00_process_aen(काष्ठा scsi_qla_host *vha, काष्ठा qla_work_evt *evt)
अणु
	uपूर्णांक32_t aen_code, aen_data;

	aen_code = FCH_EVT_VENDOR_UNIQUE;
	aen_data = evt->u.aenfx.evtcode;

	चयन (evt->u.aenfx.evtcode) अणु
	हाल QLAFX00_MBA_PORT_UPDATE:		/* Port database update */
		अगर (evt->u.aenfx.mbx[1] == 0) अणु
			अगर (evt->u.aenfx.mbx[2] == 1) अणु
				अगर (!vha->flags.fw_tgt_reported)
					vha->flags.fw_tgt_reported = 1;
				atomic_set(&vha->loop_करोwn_समयr, 0);
				atomic_set(&vha->loop_state, LOOP_UP);
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण अन्यथा अगर (evt->u.aenfx.mbx[2] == 2) अणु
				qlafx00_tgt_detach(vha, evt->u.aenfx.mbx[3]);
			पूर्ण
		पूर्ण अन्यथा अगर (evt->u.aenfx.mbx[1] == 0xffff) अणु
			अगर (evt->u.aenfx.mbx[2] == 1) अणु
				अगर (!vha->flags.fw_tgt_reported)
					vha->flags.fw_tgt_reported = 1;
				set_bit(LOOP_RESYNC_NEEDED, &vha->dpc_flags);
			पूर्ण अन्यथा अगर (evt->u.aenfx.mbx[2] == 2) अणु
				vha->device_flags |= DFLG_NO_CABLE;
				qla2x00_mark_all_devices_lost(vha);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल QLAFX00_MBA_LINK_UP:
		aen_code = FCH_EVT_LINKUP;
		aen_data = 0;
		अवरोध;
	हाल QLAFX00_MBA_LINK_DOWN:
		aen_code = FCH_EVT_LINKDOWN;
		aen_data = 0;
		अवरोध;
	हाल QLAFX00_MBA_TEMP_CRIT:	/* Critical temperature event */
		ql_log(ql_log_info, vha, 0x5082,
		    "Process critical temperature event "
		    "aenmb[0]: %x\n",
		    evt->u.aenfx.evtcode);
		scsi_block_requests(vha->host);
		qlafx00_पात_isp_cleanup(vha, true);
		scsi_unblock_requests(vha->host);
		अवरोध;
	पूर्ण

	fc_host_post_event(vha->host, fc_get_event_number(),
	    aen_code, aen_data);
पूर्ण

अटल व्योम
qlafx00_update_host_attr(scsi_qla_host_t *vha, काष्ठा port_info_data *pinfo)
अणु
	u64 port_name = 0, node_name = 0;

	port_name = (अचिन्हित दीर्घ दीर्घ)wwn_to_u64(pinfo->port_name);
	node_name = (अचिन्हित दीर्घ दीर्घ)wwn_to_u64(pinfo->node_name);

	fc_host_node_name(vha->host) = node_name;
	fc_host_port_name(vha->host) = port_name;
	अगर (!pinfo->port_type)
		vha->hw->current_topology = ISP_CFG_F;
	अगर (pinfo->link_status == QLAFX00_LINK_STATUS_UP)
		atomic_set(&vha->loop_state, LOOP_READY);
	अन्यथा अगर (pinfo->link_status == QLAFX00_LINK_STATUS_DOWN)
		atomic_set(&vha->loop_state, LOOP_DOWN);
	vha->hw->link_data_rate = (uपूर्णांक16_t)pinfo->link_config;
पूर्ण

अटल व्योम
qla2x00_fxdisc_iocb_समयout(व्योम *data)
अणु
	srb_t *sp = data;
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;

	complete(&lio->u.fxiocb.fxiocb_comp);
पूर्ण

अटल व्योम qla2x00_fxdisc_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	काष्ठा srb_iocb *lio = &sp->u.iocb_cmd;

	complete(&lio->u.fxiocb.fxiocb_comp);
पूर्ण

पूर्णांक
qlafx00_fx_disc(scsi_qla_host_t *vha, fc_port_t *fcport, uपूर्णांक16_t fx_type)
अणु
	srb_t *sp;
	काष्ठा srb_iocb *fdisc;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा host_प्रणाली_info *phost_info;
	काष्ठा रेजिस्टर_host_info *preg_hsi;
	काष्ठा new_utsname *p_sysid = शून्य;

	sp = qla2x00_get_sp(vha, fcport, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_FXIOCB_DCMD;
	sp->name = "fxdisc";

	fdisc = &sp->u.iocb_cmd;
	fdisc->समयout = qla2x00_fxdisc_iocb_समयout;
	qla2x00_init_समयr(sp, FXDISC_TIMEOUT);

	चयन (fx_type) अणु
	हाल FXDISC_GET_CONFIG_INFO:
	fdisc->u.fxiocb.flags =
		    SRB_FXDISC_RESP_DMA_VALID;
		fdisc->u.fxiocb.rsp_len = माप(काष्ठा config_info_data);
		अवरोध;
	हाल FXDISC_GET_PORT_INFO:
		fdisc->u.fxiocb.flags =
		    SRB_FXDISC_RESP_DMA_VALID | SRB_FXDISC_REQ_DWRD_VALID;
		fdisc->u.fxiocb.rsp_len = QLAFX00_PORT_DATA_INFO;
		fdisc->u.fxiocb.req_data = cpu_to_le32(fcport->port_id);
		अवरोध;
	हाल FXDISC_GET_TGT_NODE_INFO:
		fdisc->u.fxiocb.flags =
		    SRB_FXDISC_RESP_DMA_VALID | SRB_FXDISC_REQ_DWRD_VALID;
		fdisc->u.fxiocb.rsp_len = QLAFX00_TGT_NODE_INFO;
		fdisc->u.fxiocb.req_data = cpu_to_le32(fcport->tgt_id);
		अवरोध;
	हाल FXDISC_GET_TGT_NODE_LIST:
		fdisc->u.fxiocb.flags =
		    SRB_FXDISC_RESP_DMA_VALID | SRB_FXDISC_REQ_DWRD_VALID;
		fdisc->u.fxiocb.rsp_len = QLAFX00_TGT_NODE_LIST_SIZE;
		अवरोध;
	हाल FXDISC_REG_HOST_INFO:
		fdisc->u.fxiocb.flags = SRB_FXDISC_REQ_DMA_VALID;
		fdisc->u.fxiocb.req_len = माप(काष्ठा रेजिस्टर_host_info);
		p_sysid = utsname();
		अगर (!p_sysid) अणु
			ql_log(ql_log_warn, vha, 0x303c,
			    "Not able to get the system information\n");
			जाओ करोne_मुक्त_sp;
		पूर्ण
		अवरोध;
	हाल FXDISC_ABORT_IOCTL:
	शेष:
		अवरोध;
	पूर्ण

	अगर (fdisc->u.fxiocb.flags & SRB_FXDISC_REQ_DMA_VALID) अणु
		fdisc->u.fxiocb.req_addr = dma_alloc_coherent(&ha->pdev->dev,
		    fdisc->u.fxiocb.req_len,
		    &fdisc->u.fxiocb.req_dma_handle, GFP_KERNEL);
		अगर (!fdisc->u.fxiocb.req_addr)
			जाओ करोne_मुक्त_sp;

		अगर (fx_type == FXDISC_REG_HOST_INFO) अणु
			preg_hsi = (काष्ठा रेजिस्टर_host_info *)
				fdisc->u.fxiocb.req_addr;
			phost_info = &preg_hsi->hsi;
			स_रखो(preg_hsi, 0, माप(काष्ठा रेजिस्टर_host_info));
			phost_info->os_type = OS_TYPE_LINUX;
			strlcpy(phost_info->sysname, p_sysid->sysname,
				माप(phost_info->sysname));
			strlcpy(phost_info->nodename, p_sysid->nodename,
				माप(phost_info->nodename));
			अगर (!म_भेद(phost_info->nodename, "(none)"))
				ha->mr.host_info_resend = true;
			strlcpy(phost_info->release, p_sysid->release,
				माप(phost_info->release));
			strlcpy(phost_info->version, p_sysid->version,
				माप(phost_info->version));
			strlcpy(phost_info->machine, p_sysid->machine,
				माप(phost_info->machine));
			strlcpy(phost_info->करोमुख्यname, p_sysid->करोमुख्यname,
				माप(phost_info->करोमुख्यname));
			strlcpy(phost_info->hostdriver, QLA2XXX_VERSION,
				माप(phost_info->hostdriver));
			preg_hsi->utc = (uपूर्णांक64_t)kसमय_get_real_seconds();
			ql_dbg(ql_dbg_init, vha, 0x0149,
			    "ISP%04X: Host registration with firmware\n",
			    ha->pdev->device);
			ql_dbg(ql_dbg_init, vha, 0x014a,
			    "os_type = '%d', sysname = '%s', nodname = '%s'\n",
			    phost_info->os_type,
			    phost_info->sysname,
			    phost_info->nodename);
			ql_dbg(ql_dbg_init, vha, 0x014b,
			    "release = '%s', version = '%s'\n",
			    phost_info->release,
			    phost_info->version);
			ql_dbg(ql_dbg_init, vha, 0x014c,
			    "machine = '%s' "
			    "domainname = '%s', hostdriver = '%s'\n",
			    phost_info->machine,
			    phost_info->करोमुख्यname,
			    phost_info->hostdriver);
			ql_dump_buffer(ql_dbg_init + ql_dbg_disc, vha, 0x014d,
			    phost_info, माप(*phost_info));
		पूर्ण
	पूर्ण

	अगर (fdisc->u.fxiocb.flags & SRB_FXDISC_RESP_DMA_VALID) अणु
		fdisc->u.fxiocb.rsp_addr = dma_alloc_coherent(&ha->pdev->dev,
		    fdisc->u.fxiocb.rsp_len,
		    &fdisc->u.fxiocb.rsp_dma_handle, GFP_KERNEL);
		अगर (!fdisc->u.fxiocb.rsp_addr)
			जाओ करोne_unmap_req;
	पूर्ण

	fdisc->u.fxiocb.req_func_type = cpu_to_le16(fx_type);
	sp->करोne = qla2x00_fxdisc_sp_करोne;

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS)
		जाओ करोne_unmap_dma;

	रुको_क्रम_completion(&fdisc->u.fxiocb.fxiocb_comp);

	अगर (fx_type == FXDISC_GET_CONFIG_INFO) अणु
		काष्ठा config_info_data *pinfo =
		    (काष्ठा config_info_data *) fdisc->u.fxiocb.rsp_addr;
		strlcpy(vha->hw->model_number, pinfo->model_num,
			ARRAY_SIZE(vha->hw->model_number));
		strlcpy(vha->hw->model_desc, pinfo->model_description,
			ARRAY_SIZE(vha->hw->model_desc));
		स_नकल(&vha->hw->mr.symbolic_name, pinfo->symbolic_name,
		    माप(vha->hw->mr.symbolic_name));
		स_नकल(&vha->hw->mr.serial_num, pinfo->serial_num,
		    माप(vha->hw->mr.serial_num));
		स_नकल(&vha->hw->mr.hw_version, pinfo->hw_version,
		    माप(vha->hw->mr.hw_version));
		स_नकल(&vha->hw->mr.fw_version, pinfo->fw_version,
		    माप(vha->hw->mr.fw_version));
		strim(vha->hw->mr.fw_version);
		स_नकल(&vha->hw->mr.uboot_version, pinfo->uboot_version,
		    माप(vha->hw->mr.uboot_version));
		स_नकल(&vha->hw->mr.fru_serial_num, pinfo->fru_serial_num,
		    माप(vha->hw->mr.fru_serial_num));
		vha->hw->mr.critical_temperature =
		    (pinfo->nominal_temp_value) ?
		    pinfo->nominal_temp_value : QLAFX00_CRITEMP_THRSHLD;
		ha->mr.extended_io_enabled = (pinfo->enabled_capabilities &
		    QLAFX00_EXTENDED_IO_EN_MASK) != 0;
	पूर्ण अन्यथा अगर (fx_type == FXDISC_GET_PORT_INFO) अणु
		काष्ठा port_info_data *pinfo =
		    (काष्ठा port_info_data *) fdisc->u.fxiocb.rsp_addr;
		स_नकल(vha->node_name, pinfo->node_name, WWN_SIZE);
		स_नकल(vha->port_name, pinfo->port_name, WWN_SIZE);
		vha->d_id.b.करोमुख्य = pinfo->port_id[0];
		vha->d_id.b.area = pinfo->port_id[1];
		vha->d_id.b.al_pa = pinfo->port_id[2];
		qlafx00_update_host_attr(vha, pinfo);
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0141,
		    pinfo, 16);
	पूर्ण अन्यथा अगर (fx_type == FXDISC_GET_TGT_NODE_INFO) अणु
		काष्ठा qlafx00_tgt_node_info *pinfo =
		    (काष्ठा qlafx00_tgt_node_info *) fdisc->u.fxiocb.rsp_addr;
		स_नकल(fcport->node_name, pinfo->tgt_node_wwnn, WWN_SIZE);
		स_नकल(fcport->port_name, pinfo->tgt_node_wwpn, WWN_SIZE);
		fcport->port_type = FCT_TARGET;
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0144,
		    pinfo, 16);
	पूर्ण अन्यथा अगर (fx_type == FXDISC_GET_TGT_NODE_LIST) अणु
		काष्ठा qlafx00_tgt_node_info *pinfo =
		    (काष्ठा qlafx00_tgt_node_info *) fdisc->u.fxiocb.rsp_addr;
		ql_dump_buffer(ql_dbg_init + ql_dbg_buffer, vha, 0x0146,
		    pinfo, 16);
		स_नकल(vha->hw->gid_list, pinfo, QLAFX00_TGT_NODE_LIST_SIZE);
	पूर्ण अन्यथा अगर (fx_type == FXDISC_ABORT_IOCTL)
		fdisc->u.fxiocb.result =
		    (fdisc->u.fxiocb.result ==
			cpu_to_le32(QLAFX00_IOCTL_ICOB_ABORT_SUCCESS)) ?
		    cpu_to_le32(QLA_SUCCESS) : cpu_to_le32(QLA_FUNCTION_FAILED);

	rval = le32_to_cpu(fdisc->u.fxiocb.result);

करोne_unmap_dma:
	अगर (fdisc->u.fxiocb.rsp_addr)
		dma_मुक्त_coherent(&ha->pdev->dev, fdisc->u.fxiocb.rsp_len,
		    fdisc->u.fxiocb.rsp_addr, fdisc->u.fxiocb.rsp_dma_handle);

करोne_unmap_req:
	अगर (fdisc->u.fxiocb.req_addr)
		dma_मुक्त_coherent(&ha->pdev->dev, fdisc->u.fxiocb.req_len,
		    fdisc->u.fxiocb.req_addr, fdisc->u.fxiocb.req_dma_handle);
करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

/*
 * qlafx00_initialize_adapter
 *      Initialize board.
 *
 * Input:
 *      ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *      0 = success
 */
पूर्णांक
qlafx00_initialize_adapter(scsi_qla_host_t *vha)
अणु
	पूर्णांक	rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t tempc;

	/* Clear adapter flags. */
	vha->flags.online = 0;
	ha->flags.chip_reset_करोne = 0;
	vha->flags.reset_active = 0;
	ha->flags.pci_channel_io_perm_failure = 0;
	ha->flags.eeh_busy = 0;
	atomic_set(&vha->loop_करोwn_समयr, LOOP_DOWN_TIME);
	atomic_set(&vha->loop_state, LOOP_DOWN);
	vha->device_flags = DFLG_NO_CABLE;
	vha->dpc_flags = 0;
	vha->flags.management_server_logged_in = 0;
	ha->isp_पात_cnt = 0;
	ha->beacon_blink_led = 0;

	set_bit(0, ha->req_qid_map);
	set_bit(0, ha->rsp_qid_map);

	ql_dbg(ql_dbg_init, vha, 0x0147,
	    "Configuring PCI space...\n");

	rval = ha->isp_ops->pci_config(vha);
	अगर (rval) अणु
		ql_log(ql_log_warn, vha, 0x0148,
		    "Unable to configure PCI space.\n");
		वापस rval;
	पूर्ण

	rval = qlafx00_init_fw_पढ़ोy(vha);
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	qlafx00_save_queue_ptrs(vha);

	rval = qlafx00_config_queues(vha);
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	/*
	 * Allocate the array of outstanding commands
	 * now that we know the firmware resources.
	 */
	rval = qla2x00_alloc_outstanding_cmds(ha, vha->req);
	अगर (rval != QLA_SUCCESS)
		वापस rval;

	rval = qla2x00_init_rings(vha);
	ha->flags.chip_reset_करोne = 1;

	tempc = QLAFX00_GET_TEMPERATURE(ha);
	ql_dbg(ql_dbg_init, vha, 0x0152,
	    "ISPFx00(%s): Critical temp timer, current SOC temperature: 0x%x\n",
	    __func__, tempc);

	वापस rval;
पूर्ण

uपूर्णांक32_t
qlafx00_fw_state_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		      अक्षर *buf)
अणु
	scsi_qla_host_t *vha = shost_priv(class_to_shost(dev));
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	uपूर्णांक32_t state[1];

	अगर (qla2x00_reset_active(vha))
		ql_log(ql_log_warn, vha, 0x70ce,
		    "ISP reset active.\n");
	अन्यथा अगर (!vha->hw->flags.eeh_busy) अणु
		rval = qlafx00_get_firmware_state(vha, state);
	पूर्ण
	अगर (rval != QLA_SUCCESS)
		स_रखो(state, -1, माप(state));

	वापस state[0];
पूर्ण

व्योम
qlafx00_get_host_speed(काष्ठा Scsi_Host *shost)
अणु
	काष्ठा qla_hw_data *ha = ((काष्ठा scsi_qla_host *)
					(shost_priv(shost)))->hw;
	u32 speed = FC_PORTSPEED_UNKNOWN;

	चयन (ha->link_data_rate) अणु
	हाल QLAFX00_PORT_SPEED_2G:
		speed = FC_PORTSPEED_2GBIT;
		अवरोध;
	हाल QLAFX00_PORT_SPEED_4G:
		speed = FC_PORTSPEED_4GBIT;
		अवरोध;
	हाल QLAFX00_PORT_SPEED_8G:
		speed = FC_PORTSPEED_8GBIT;
		अवरोध;
	हाल QLAFX00_PORT_SPEED_10G:
		speed = FC_PORTSPEED_10GBIT;
		अवरोध;
	पूर्ण
	fc_host_speed(shost) = speed;
पूर्ण

/** QLAFX00 specअगरic ISR implementation functions */

अटल अंतरभूत व्योम
qlafx00_handle_sense(srb_t *sp, uपूर्णांक8_t *sense_data, uपूर्णांक32_t par_sense_len,
		     uपूर्णांक32_t sense_len, काष्ठा rsp_que *rsp, पूर्णांक res)
अणु
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा scsi_cmnd *cp = GET_CMD_SP(sp);
	uपूर्णांक32_t track_sense_len;

	SET_FW_SENSE_LEN(sp, sense_len);

	अगर (sense_len >= SCSI_SENSE_BUFFERSIZE)
		sense_len = SCSI_SENSE_BUFFERSIZE;

	SET_CMD_SENSE_LEN(sp, sense_len);
	SET_CMD_SENSE_PTR(sp, cp->sense_buffer);
	track_sense_len = sense_len;

	अगर (sense_len > par_sense_len)
		sense_len = par_sense_len;

	स_नकल(cp->sense_buffer, sense_data, sense_len);

	SET_FW_SENSE_LEN(sp, GET_FW_SENSE_LEN(sp) - sense_len);

	SET_CMD_SENSE_PTR(sp, cp->sense_buffer + sense_len);
	track_sense_len -= sense_len;
	SET_CMD_SENSE_LEN(sp, track_sense_len);

	ql_dbg(ql_dbg_io, vha, 0x304d,
	    "sense_len=0x%x par_sense_len=0x%x track_sense_len=0x%x.\n",
	    sense_len, par_sense_len, track_sense_len);
	अगर (GET_FW_SENSE_LEN(sp) > 0) अणु
		rsp->status_srb = sp;
		cp->result = res;
	पूर्ण

	अगर (sense_len) अणु
		ql_dbg(ql_dbg_io + ql_dbg_buffer, vha, 0x3039,
		    "Check condition Sense data, nexus%ld:%d:%llu cmd=%p.\n",
		    sp->vha->host_no, cp->device->id, cp->device->lun,
		    cp);
		ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x3049,
		    cp->sense_buffer, sense_len);
	पूर्ण
पूर्ण

अटल व्योम
qlafx00_पंचांग_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
		      काष्ठा tsk_mgmt_entry_fx00 *pkt, srb_t *sp,
		      __le16 sstatus, __le16 cpstatus)
अणु
	काष्ठा srb_iocb *पंचांगf;

	पंचांगf = &sp->u.iocb_cmd;
	अगर (cpstatus != cpu_to_le16((uपूर्णांक16_t)CS_COMPLETE) ||
	    (sstatus & cpu_to_le16((uपूर्णांक16_t)SS_RESPONSE_INFO_LEN_VALID)))
		cpstatus = cpu_to_le16((uपूर्णांक16_t)CS_INCOMPLETE);
	पंचांगf->u.पंचांगf.comp_status = cpstatus;
	sp->करोne(sp, 0);
पूर्ण

अटल व्योम
qlafx00_पात_iocb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
			 काष्ठा पात_iocb_entry_fx00 *pkt)
अणु
	स्थिर अक्षर func[] = "ABT_IOCB";
	srb_t *sp;
	काष्ठा srb_iocb *abt;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	abt = &sp->u.iocb_cmd;
	abt->u.abt.comp_status = pkt->tgt_id_sts;
	sp->करोne(sp, 0);
पूर्ण

अटल व्योम
qlafx00_ioctl_iosb_entry(scsi_qla_host_t *vha, काष्ठा req_que *req,
			 काष्ठा ioctl_iocb_entry_fx00 *pkt)
अणु
	स्थिर अक्षर func[] = "IOSB_IOCB";
	srb_t *sp;
	काष्ठा bsg_job *bsg_job;
	काष्ठा fc_bsg_reply *bsg_reply;
	काष्ठा srb_iocb *iocb_job;
	पूर्णांक res = 0;
	काष्ठा qla_mt_iocb_rsp_fx00 ख_स्थितिus;
	uपूर्णांक8_t	*fw_sts_ptr;

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (!sp)
		वापस;

	अगर (sp->type == SRB_FXIOCB_DCMD) अणु
		iocb_job = &sp->u.iocb_cmd;
		iocb_job->u.fxiocb.seq_number = pkt->seq_no;
		iocb_job->u.fxiocb.fw_flags = pkt->fw_iotcl_flags;
		iocb_job->u.fxiocb.result = pkt->status;
		अगर (iocb_job->u.fxiocb.flags & SRB_FXDISC_RSP_DWRD_VALID)
			iocb_job->u.fxiocb.req_data =
			    pkt->dataword_r;
	पूर्ण अन्यथा अणु
		bsg_job = sp->u.bsg_job;
		bsg_reply = bsg_job->reply;

		स_रखो(&ख_स्थितिus, 0, माप(काष्ठा qla_mt_iocb_rsp_fx00));

		ख_स्थितिus.reserved_1 = pkt->reserved_0;
		ख_स्थितिus.func_type = pkt->comp_func_num;
		ख_स्थितिus.ioctl_flags = pkt->fw_iotcl_flags;
		ख_स्थितिus.ioctl_data = pkt->dataword_r;
		ख_स्थितिus.adapid = pkt->adapid;
		ख_स्थितिus.reserved_2 = pkt->dataword_r_extra;
		ख_स्थितिus.res_count = pkt->residuallen;
		ख_स्थितिus.status = pkt->status;
		ख_स्थितिus.seq_number = pkt->seq_no;
		स_नकल(ख_स्थितिus.reserved_3,
		    pkt->reserved_2, 20 * माप(uपूर्णांक8_t));

		fw_sts_ptr = bsg_job->reply + माप(काष्ठा fc_bsg_reply);

		स_नकल(fw_sts_ptr, &ख_स्थितिus, माप(ख_स्थितिus));
		bsg_job->reply_len = माप(काष्ठा fc_bsg_reply) +
			माप(काष्ठा qla_mt_iocb_rsp_fx00) + माप(uपूर्णांक8_t);

		ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
		    sp->vha, 0x5080, pkt, माप(*pkt));

		ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
		    sp->vha, 0x5074,
		    fw_sts_ptr, माप(ख_स्थितिus));

		res = bsg_reply->result = DID_OK << 16;
		bsg_reply->reply_payload_rcv_len =
		    bsg_job->reply_payload.payload_len;
	पूर्ण
	sp->करोne(sp, res);
पूर्ण

/**
 * qlafx00_status_entry() - Process a Status IOCB entry.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 * @pkt: Entry poपूर्णांकer
 */
अटल व्योम
qlafx00_status_entry(scsi_qla_host_t *vha, काष्ठा rsp_que *rsp, व्योम *pkt)
अणु
	srb_t		*sp;
	fc_port_t	*fcport;
	काष्ठा scsi_cmnd *cp;
	काष्ठा sts_entry_fx00 *sts;
	__le16		comp_status;
	__le16		scsi_status;
	__le16		lscsi_status;
	पूर्णांक32_t		resid;
	uपूर्णांक32_t	sense_len, par_sense_len, rsp_info_len, resid_len,
	    fw_resid_len;
	uपूर्णांक8_t		*rsp_info = शून्य, *sense_data = शून्य;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t hindex, handle;
	uपूर्णांक16_t que;
	काष्ठा req_que *req;
	पूर्णांक logit = 1;
	पूर्णांक res = 0;

	sts = (काष्ठा sts_entry_fx00 *) pkt;

	comp_status = sts->comp_status;
	scsi_status = sts->scsi_status & cpu_to_le16((uपूर्णांक16_t)SS_MASK);
	hindex = sts->handle;
	handle = LSW(hindex);

	que = MSW(hindex);
	req = ha->req_q_map[que];

	/* Validate handle. */
	अगर (handle < req->num_outstanding_cmds)
		sp = req->outstanding_cmds[handle];
	अन्यथा
		sp = शून्य;

	अगर (sp == शून्य) अणु
		ql_dbg(ql_dbg_io, vha, 0x3034,
		    "Invalid status handle (0x%x).\n", handle);

		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		वापस;
	पूर्ण

	अगर (sp->type == SRB_TM_CMD) अणु
		req->outstanding_cmds[handle] = शून्य;
		qlafx00_पंचांग_iocb_entry(vha, req, pkt, sp,
		    scsi_status, comp_status);
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
		ql_dbg(ql_dbg_io, vha, 0x3048,
		    "Command already returned (0x%x/%p).\n",
		    handle, sp);

		वापस;
	पूर्ण

	lscsi_status = scsi_status & cpu_to_le16((uपूर्णांक16_t)STATUS_MASK);

	fcport = sp->fcport;

	sense_len = par_sense_len = rsp_info_len = resid_len =
		fw_resid_len = 0;
	अगर (scsi_status & cpu_to_le16((uपूर्णांक16_t)SS_SENSE_LEN_VALID))
		sense_len = sts->sense_len;
	अगर (scsi_status & cpu_to_le16(((uपूर्णांक16_t)SS_RESIDUAL_UNDER
	    | (uपूर्णांक16_t)SS_RESIDUAL_OVER)))
		resid_len = le32_to_cpu(sts->residual_len);
	अगर (comp_status == cpu_to_le16((uपूर्णांक16_t)CS_DATA_UNDERRUN))
		fw_resid_len = le32_to_cpu(sts->residual_len);
	rsp_info = sense_data = sts->data;
	par_sense_len = माप(sts->data);

	/* Check क्रम overrun. */
	अगर (comp_status == CS_COMPLETE &&
	    scsi_status & cpu_to_le16((uपूर्णांक16_t)SS_RESIDUAL_OVER))
		comp_status = cpu_to_le16((uपूर्णांक16_t)CS_DATA_OVERRUN);

	/*
	 * Based on Host and scsi status generate status code क्रम Linux
	 */
	चयन (le16_to_cpu(comp_status)) अणु
	हाल CS_COMPLETE:
	हाल CS_QUEUE_FULL:
		अगर (scsi_status == 0) अणु
			res = DID_OK << 16;
			अवरोध;
		पूर्ण
		अगर (scsi_status & cpu_to_le16(((uपूर्णांक16_t)SS_RESIDUAL_UNDER
		    | (uपूर्णांक16_t)SS_RESIDUAL_OVER))) अणु
			resid = resid_len;
			scsi_set_resid(cp, resid);

			अगर (!lscsi_status &&
			    ((अचिन्हित)(scsi_bufflen(cp) - resid) <
			     cp->underflow)) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x3050,
				    "Mid-layer underflow "
				    "detected (0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16;
				अवरोध;
			पूर्ण
		पूर्ण
		res = DID_OK << 16 | le16_to_cpu(lscsi_status);

		अगर (lscsi_status ==
		    cpu_to_le16((uपूर्णांक16_t)SAM_STAT_TASK_SET_FULL)) अणु
			ql_dbg(ql_dbg_io, fcport->vha, 0x3051,
			    "QUEUE FULL detected.\n");
			अवरोध;
		पूर्ण
		logit = 0;
		अगर (lscsi_status != cpu_to_le16((uपूर्णांक16_t)SS_CHECK_CONDITION))
			अवरोध;

		स_रखो(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		अगर (!(scsi_status & cpu_to_le16((uपूर्णांक16_t)SS_SENSE_LEN_VALID)))
			अवरोध;

		qlafx00_handle_sense(sp, sense_data, par_sense_len, sense_len,
		    rsp, res);
		अवरोध;

	हाल CS_DATA_UNDERRUN:
		/* Use F/W calculated residual length. */
		अगर (IS_FWI2_CAPABLE(ha) || IS_QLAFX00(ha))
			resid = fw_resid_len;
		अन्यथा
			resid = resid_len;
		scsi_set_resid(cp, resid);
		अगर (scsi_status & cpu_to_le16((uपूर्णांक16_t)SS_RESIDUAL_UNDER)) अणु
			अगर ((IS_FWI2_CAPABLE(ha) || IS_QLAFX00(ha))
			    && fw_resid_len != resid_len) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x3052,
				    "Dropped frame(s) detected "
				    "(0x%x of 0x%x bytes).\n",
				    resid, scsi_bufflen(cp));

				res = DID_ERROR << 16 |
				    le16_to_cpu(lscsi_status);
				जाओ check_scsi_status;
			पूर्ण

			अगर (!lscsi_status &&
			    ((अचिन्हित)(scsi_bufflen(cp) - resid) <
			    cp->underflow)) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x3053,
				    "Mid-layer underflow "
				    "detected (0x%x of 0x%x bytes, "
				    "cp->underflow: 0x%x).\n",
				    resid, scsi_bufflen(cp), cp->underflow);

				res = DID_ERROR << 16;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (lscsi_status !=
		    cpu_to_le16((uपूर्णांक16_t)SAM_STAT_TASK_SET_FULL) &&
		    lscsi_status != cpu_to_le16((uपूर्णांक16_t)SAM_STAT_BUSY)) अणु
			/*
			 * scsi status of task set and busy are considered
			 * to be task not completed.
			 */

			ql_dbg(ql_dbg_io, fcport->vha, 0x3054,
			    "Dropped frame(s) detected (0x%x "
			    "of 0x%x bytes).\n", resid,
			    scsi_bufflen(cp));

			res = DID_ERROR << 16 | le16_to_cpu(lscsi_status);
			जाओ check_scsi_status;
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_io, fcport->vha, 0x3055,
			    "scsi_status: 0x%x, lscsi_status: 0x%x\n",
			    scsi_status, lscsi_status);
		पूर्ण

		res = DID_OK << 16 | le16_to_cpu(lscsi_status);
		logit = 0;

check_scsi_status:
		/*
		 * Check to see अगर SCSI Status is non zero. If so report SCSI
		 * Status.
		 */
		अगर (lscsi_status != 0) अणु
			अगर (lscsi_status ==
			    cpu_to_le16((uपूर्णांक16_t)SAM_STAT_TASK_SET_FULL)) अणु
				ql_dbg(ql_dbg_io, fcport->vha, 0x3056,
				    "QUEUE FULL detected.\n");
				logit = 1;
				अवरोध;
			पूर्ण
			अगर (lscsi_status !=
			    cpu_to_le16((uपूर्णांक16_t)SS_CHECK_CONDITION))
				अवरोध;

			स_रखो(cp->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
			अगर (!(scsi_status &
			    cpu_to_le16((uपूर्णांक16_t)SS_SENSE_LEN_VALID)))
				अवरोध;

			qlafx00_handle_sense(sp, sense_data, par_sense_len,
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

		ql_dbg(ql_dbg_io, fcport->vha, 0x3057,
		    "Port down status: port-state=0x%x.\n",
		    atomic_पढ़ो(&fcport->state));

		अगर (atomic_पढ़ो(&fcport->state) == FCS_ONLINE)
			qla2x00_mark_device_lost(fcport->vha, fcport, 1);
		अवरोध;

	हाल CS_ABORTED:
		res = DID_RESET << 16;
		अवरोध;

	शेष:
		res = DID_ERROR << 16;
		अवरोध;
	पूर्ण

	अगर (logit)
		ql_dbg(ql_dbg_io, fcport->vha, 0x3058,
		    "FCP command status: 0x%x-0x%x (0x%x) nexus=%ld:%d:%llu "
		    "tgt_id: 0x%x lscsi_status: 0x%x cdb=%10phN len=0x%x "
		    "rsp_info=%p resid=0x%x fw_resid=0x%x sense_len=0x%x, "
		    "par_sense_len=0x%x, rsp_info_len=0x%x\n",
		    comp_status, scsi_status, res, vha->host_no,
		    cp->device->id, cp->device->lun, fcport->tgt_id,
		    lscsi_status, cp->cmnd, scsi_bufflen(cp),
		    rsp_info, resid_len, fw_resid_len, sense_len,
		    par_sense_len, rsp_info_len);

	अगर (rsp->status_srb == शून्य)
		sp->करोne(sp, res);
	अन्यथा
		WARN_ON_ONCE(true);
पूर्ण

/**
 * qlafx00_status_cont_entry() - Process a Status Continuations entry.
 * @rsp: response queue
 * @pkt: Entry poपूर्णांकer
 *
 * Extended sense data.
 */
अटल व्योम
qlafx00_status_cont_entry(काष्ठा rsp_que *rsp, sts_cont_entry_t *pkt)
अणु
	uपूर्णांक8_t	sense_sz = 0;
	काष्ठा qla_hw_data *ha = rsp->hw;
	काष्ठा scsi_qla_host *vha = pci_get_drvdata(ha->pdev);
	srb_t *sp = rsp->status_srb;
	काष्ठा scsi_cmnd *cp;
	uपूर्णांक32_t sense_len;
	uपूर्णांक8_t *sense_ptr;

	अगर (!sp) अणु
		ql_dbg(ql_dbg_io, vha, 0x3037,
		    "no SP, sp = %p\n", sp);
		वापस;
	पूर्ण

	अगर (!GET_FW_SENSE_LEN(sp)) अणु
		ql_dbg(ql_dbg_io, vha, 0x304b,
		    "no fw sense data, sp = %p\n", sp);
		वापस;
	पूर्ण
	cp = GET_CMD_SP(sp);
	अगर (cp == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x303b,
		    "cmd is NULL: already returned to OS (sp=%p).\n", sp);

		rsp->status_srb = शून्य;
		वापस;
	पूर्ण

	अगर (!GET_CMD_SENSE_LEN(sp)) अणु
		ql_dbg(ql_dbg_io, vha, 0x304c,
		    "no sense data, sp = %p\n", sp);
	पूर्ण अन्यथा अणु
		sense_len = GET_CMD_SENSE_LEN(sp);
		sense_ptr = GET_CMD_SENSE_PTR(sp);
		ql_dbg(ql_dbg_io, vha, 0x304f,
		    "sp=%p sense_len=0x%x sense_ptr=%p.\n",
		    sp, sense_len, sense_ptr);

		अगर (sense_len > माप(pkt->data))
			sense_sz = माप(pkt->data);
		अन्यथा
			sense_sz = sense_len;

		/* Move sense data. */
		ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x304e,
		    pkt, माप(*pkt));
		स_नकल(sense_ptr, pkt->data, sense_sz);
		ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x304a,
		    sense_ptr, sense_sz);

		sense_len -= sense_sz;
		sense_ptr += sense_sz;

		SET_CMD_SENSE_PTR(sp, sense_ptr);
		SET_CMD_SENSE_LEN(sp, sense_len);
	पूर्ण
	sense_len = GET_FW_SENSE_LEN(sp);
	sense_len = (sense_len > माप(pkt->data)) ?
	    (sense_len - माप(pkt->data)) : 0;
	SET_FW_SENSE_LEN(sp, sense_len);

	/* Place command on करोne queue. */
	अगर (sense_len == 0) अणु
		rsp->status_srb = शून्य;
		sp->करोne(sp, cp->result);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(true);
	पूर्ण
पूर्ण

/**
 * qlafx00_multistatus_entry() - Process Multi response queue entries.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 * @pkt: received packet
 */
अटल व्योम
qlafx00_multistatus_entry(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp, व्योम *pkt)
अणु
	srb_t		*sp;
	काष्ठा multi_sts_entry_fx00 *stsmfx;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक32_t handle, hindex, handle_count, i;
	uपूर्णांक16_t que;
	काष्ठा req_que *req;
	__le32 *handle_ptr;

	stsmfx = (काष्ठा multi_sts_entry_fx00 *) pkt;

	handle_count = stsmfx->handle_count;

	अगर (handle_count > MAX_HANDLE_COUNT) अणु
		ql_dbg(ql_dbg_io, vha, 0x3035,
		    "Invalid handle count (0x%x).\n", handle_count);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		वापस;
	पूर्ण

	handle_ptr =  &stsmfx->handles[0];

	क्रम (i = 0; i < handle_count; i++) अणु
		hindex = le32_to_cpu(*handle_ptr);
		handle = LSW(hindex);
		que = MSW(hindex);
		req = ha->req_q_map[que];

		/* Validate handle. */
		अगर (handle < req->num_outstanding_cmds)
			sp = req->outstanding_cmds[handle];
		अन्यथा
			sp = शून्य;

		अगर (sp == शून्य) अणु
			ql_dbg(ql_dbg_io, vha, 0x3044,
			    "Invalid status handle (0x%x).\n", handle);
			set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
			qla2xxx_wake_dpc(vha);
			वापस;
		पूर्ण
		qla2x00_process_completed_request(vha, req, handle);
		handle_ptr++;
	पूर्ण
पूर्ण

/**
 * qlafx00_error_entry() - Process an error entry.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 * @pkt: Entry poपूर्णांकer
 */
अटल व्योम
qlafx00_error_entry(scsi_qla_host_t *vha, काष्ठा rsp_que *rsp,
		    काष्ठा sts_entry_fx00 *pkt)
अणु
	srb_t *sp;
	काष्ठा qla_hw_data *ha = vha->hw;
	स्थिर अक्षर func[] = "ERROR-IOCB";
	uपूर्णांक16_t que = 0;
	काष्ठा req_que *req = शून्य;
	पूर्णांक res = DID_ERROR << 16;

	req = ha->req_q_map[que];

	sp = qla2x00_get_sp_from_handle(vha, func, req, pkt);
	अगर (sp) अणु
		sp->करोne(sp, res);
		वापस;
	पूर्ण

	set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
	qla2xxx_wake_dpc(vha);
पूर्ण

/**
 * qlafx00_process_response_queue() - Process response queue entries.
 * @vha: SCSI driver HA context
 * @rsp: response queue
 */
अटल व्योम
qlafx00_process_response_queue(काष्ठा scsi_qla_host *vha,
	काष्ठा rsp_que *rsp)
अणु
	काष्ठा sts_entry_fx00 *pkt;
	response_t *lptr;
	uपूर्णांक16_t lreq_q_in = 0;
	uपूर्णांक16_t lreq_q_out = 0;

	lreq_q_in = rd_reg_dword(rsp->rsp_q_in);
	lreq_q_out = rsp->ring_index;

	जबतक (lreq_q_in != lreq_q_out) अणु
		lptr = rsp->ring_ptr;
		स_नकल_fromio(rsp->rsp_pkt, (व्योम __iomem *)lptr,
		    माप(rsp->rsp_pkt));
		pkt = (काष्ठा sts_entry_fx00 *)rsp->rsp_pkt;

		rsp->ring_index++;
		lreq_q_out++;
		अगर (rsp->ring_index == rsp->length) अणु
			lreq_q_out = 0;
			rsp->ring_index = 0;
			rsp->ring_ptr = rsp->ring;
		पूर्ण अन्यथा अणु
			rsp->ring_ptr++;
		पूर्ण

		अगर (pkt->entry_status != 0 &&
		    pkt->entry_type != IOCTL_IOSB_TYPE_FX00) अणु
			ql_dbg(ql_dbg_async, vha, 0x507f,
			       "type of error status in response: 0x%x\n",
			       pkt->entry_status);
			qlafx00_error_entry(vha, rsp,
					    (काष्ठा sts_entry_fx00 *)pkt);
			जारी;
		पूर्ण

		चयन (pkt->entry_type) अणु
		हाल STATUS_TYPE_FX00:
			qlafx00_status_entry(vha, rsp, pkt);
			अवरोध;

		हाल STATUS_CONT_TYPE_FX00:
			qlafx00_status_cont_entry(rsp, (sts_cont_entry_t *)pkt);
			अवरोध;

		हाल MULTI_STATUS_TYPE_FX00:
			qlafx00_multistatus_entry(vha, rsp, pkt);
			अवरोध;

		हाल ABORT_IOCB_TYPE_FX00:
			qlafx00_पात_iocb_entry(vha, rsp->req,
			   (काष्ठा पात_iocb_entry_fx00 *)pkt);
			अवरोध;

		हाल IOCTL_IOSB_TYPE_FX00:
			qlafx00_ioctl_iosb_entry(vha, rsp->req,
			    (काष्ठा ioctl_iocb_entry_fx00 *)pkt);
			अवरोध;
		शेष:
			/* Type Not Supported. */
			ql_dbg(ql_dbg_async, vha, 0x5081,
			    "Received unknown response pkt type %x "
			    "entry status=%x.\n",
			    pkt->entry_type, pkt->entry_status);
			अवरोध;
		पूर्ण
	पूर्ण

	/* Adjust ring index */
	wrt_reg_dword(rsp->rsp_q_out, rsp->ring_index);
पूर्ण

/**
 * qlafx00_async_event() - Process aynchronous events.
 * @vha: SCSI driver HA context
 */
अटल व्योम
qlafx00_async_event(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_fx00 __iomem *reg;
	पूर्णांक data_size = 1;

	reg = &ha->iobase->ispfx00;
	/* Setup to process RIO completion. */
	चयन (ha->aenmb[0]) अणु
	हाल QLAFX00_MBA_SYSTEM_ERR:		/* System Error */
		ql_log(ql_log_warn, vha, 0x5079,
		    "ISP System Error - mbx1=%x\n", ha->aenmb[0]);
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		अवरोध;

	हाल QLAFX00_MBA_SHUTDOWN_RQSTD:	/* Shutकरोwn requested */
		ql_dbg(ql_dbg_async, vha, 0x5076,
		    "Asynchronous FW shutdown requested.\n");
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
		अवरोध;

	हाल QLAFX00_MBA_PORT_UPDATE:		/* Port database update */
		ha->aenmb[1] = rd_reg_dword(&reg->aenmailbox1);
		ha->aenmb[2] = rd_reg_dword(&reg->aenmailbox2);
		ha->aenmb[3] = rd_reg_dword(&reg->aenmailbox3);
		ql_dbg(ql_dbg_async, vha, 0x5077,
		    "Asynchronous port Update received "
		    "aenmb[0]: %x, aenmb[1]: %x, aenmb[2]: %x, aenmb[3]: %x\n",
		    ha->aenmb[0], ha->aenmb[1], ha->aenmb[2], ha->aenmb[3]);
		data_size = 4;
		अवरोध;

	हाल QLAFX00_MBA_TEMP_OVER:	/* Over temperature event */
		ql_log(ql_log_info, vha, 0x5085,
		    "Asynchronous over temperature event received "
		    "aenmb[0]: %x\n",
		    ha->aenmb[0]);
		अवरोध;

	हाल QLAFX00_MBA_TEMP_NORM:	/* Normal temperature event */
		ql_log(ql_log_info, vha, 0x5086,
		    "Asynchronous normal temperature event received "
		    "aenmb[0]: %x\n",
		    ha->aenmb[0]);
		अवरोध;

	हाल QLAFX00_MBA_TEMP_CRIT:	/* Critical temperature event */
		ql_log(ql_log_info, vha, 0x5083,
		    "Asynchronous critical temperature event received "
		    "aenmb[0]: %x\n",
		ha->aenmb[0]);
		अवरोध;

	शेष:
		ha->aenmb[1] = rd_reg_dword(&reg->aenmailbox1);
		ha->aenmb[2] = rd_reg_dword(&reg->aenmailbox2);
		ha->aenmb[3] = rd_reg_dword(&reg->aenmailbox3);
		ha->aenmb[4] = rd_reg_dword(&reg->aenmailbox4);
		ha->aenmb[5] = rd_reg_dword(&reg->aenmailbox5);
		ha->aenmb[6] = rd_reg_dword(&reg->aenmailbox6);
		ha->aenmb[7] = rd_reg_dword(&reg->aenmailbox7);
		ql_dbg(ql_dbg_async, vha, 0x5078,
		    "AEN:%04x %04x %04x %04x :%04x %04x %04x %04x\n",
		    ha->aenmb[0], ha->aenmb[1], ha->aenmb[2], ha->aenmb[3],
		    ha->aenmb[4], ha->aenmb[5], ha->aenmb[6], ha->aenmb[7]);
		अवरोध;
	पूर्ण
	qlafx00_post_aenfx_work(vha, ha->aenmb[0],
	    (uपूर्णांक32_t *)ha->aenmb, data_size);
पूर्ण

/**
 * qlafx00_mbx_completion() - Process mailbox command completions.
 * @vha: SCSI driver HA context
 * @mb0: value to be written पूर्णांकo mailbox रेजिस्टर 0
 */
अटल व्योम
qlafx00_mbx_completion(scsi_qla_host_t *vha, uपूर्णांक32_t mb0)
अणु
	uपूर्णांक16_t	cnt;
	__le32 __iomem *wptr;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_fx00 __iomem *reg = &ha->iobase->ispfx00;

	अगर (!ha->mcp32)
		ql_dbg(ql_dbg_async, vha, 0x507e, "MBX pointer ERROR.\n");

	/* Load वापस mailbox रेजिस्टरs. */
	ha->flags.mbox_पूर्णांक = 1;
	ha->mailbox_out32[0] = mb0;
	wptr = &reg->mailbox17;

	क्रम (cnt = 1; cnt < ha->mbx_count; cnt++) अणु
		ha->mailbox_out32[cnt] = rd_reg_dword(wptr);
		wptr++;
	पूर्ण
पूर्ण

/**
 * qlafx00_पूर्णांकr_handler() - Process पूर्णांकerrupts क्रम the ISPFX00.
 * @irq: पूर्णांकerrupt number
 * @dev_id: SCSI driver HA context
 *
 * Called by प्रणाली whenever the host adapter generates an पूर्णांकerrupt.
 *
 * Returns handled flag.
 */
irqवापस_t
qlafx00_पूर्णांकr_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	scsi_qla_host_t	*vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा device_reg_fx00 __iomem *reg;
	पूर्णांक		status;
	अचिन्हित दीर्घ	iter;
	uपूर्णांक32_t	stat;
	uपूर्णांक32_t	mb[8];
	काष्ठा rsp_que *rsp;
	अचिन्हित दीर्घ	flags;
	uपूर्णांक32_t clr_पूर्णांकr = 0;
	uपूर्णांक32_t पूर्णांकr_stat = 0;

	rsp = (काष्ठा rsp_que *) dev_id;
	अगर (!rsp) अणु
		ql_log(ql_log_info, शून्य, 0x507d,
		    "%s: NULL response queue pointer.\n", __func__);
		वापस IRQ_NONE;
	पूर्ण

	ha = rsp->hw;
	reg = &ha->iobase->ispfx00;
	status = 0;

	अगर (unlikely(pci_channel_offline(ha->pdev)))
		वापस IRQ_HANDLED;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	vha = pci_get_drvdata(ha->pdev);
	क्रम (iter = 50; iter--; clr_पूर्णांकr = 0) अणु
		stat = QLAFX00_RD_INTR_REG(ha);
		अगर (qla2x00_check_reg32_क्रम_disconnect(vha, stat))
			अवरोध;
		पूर्णांकr_stat = stat & QLAFX00_HST_INT_STS_BITS;
		अगर (!पूर्णांकr_stat)
			अवरोध;

		अगर (stat & QLAFX00_INTR_MB_CMPLT) अणु
			mb[0] = rd_reg_dword(&reg->mailbox16);
			qlafx00_mbx_completion(vha, mb[0]);
			status |= MBX_INTERRUPT;
			clr_पूर्णांकr |= QLAFX00_INTR_MB_CMPLT;
		पूर्ण
		अगर (पूर्णांकr_stat & QLAFX00_INTR_ASYNC_CMPLT) अणु
			ha->aenmb[0] = rd_reg_dword(&reg->aenmailbox0);
			qlafx00_async_event(vha);
			clr_पूर्णांकr |= QLAFX00_INTR_ASYNC_CMPLT;
		पूर्ण
		अगर (पूर्णांकr_stat & QLAFX00_INTR_RSP_CMPLT) अणु
			qlafx00_process_response_queue(vha, rsp);
			clr_पूर्णांकr |= QLAFX00_INTR_RSP_CMPLT;
		पूर्ण

		QLAFX00_CLR_INTR_REG(ha, clr_पूर्णांकr);
		QLAFX00_RD_INTR_REG(ha);
	पूर्ण

	qla2x00_handle_mbx_completion(ha, status);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

/** QLAFX00 specअगरic IOCB implementation functions */

अटल अंतरभूत cont_a64_entry_t *
qlafx00_prep_cont_type1_iocb(काष्ठा req_que *req,
			     cont_a64_entry_t *lcont_pkt)
अणु
	cont_a64_entry_t *cont_pkt;

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा अणु
		req->ring_ptr++;
	पूर्ण

	cont_pkt = (cont_a64_entry_t *)req->ring_ptr;

	/* Load packet शेषs. */
	lcont_pkt->entry_type = CONTINUE_A64_TYPE_FX00;

	वापस cont_pkt;
पूर्ण

अटल अंतरभूत व्योम
qlafx00_build_scsi_iocbs(srb_t *sp, काष्ठा cmd_type_7_fx00 *cmd_pkt,
			 uपूर्णांक16_t tot_dsds, काष्ठा cmd_type_7_fx00 *lcmd_pkt)
अणु
	uपूर्णांक16_t	avail_dsds;
	काष्ठा dsd64	*cur_dsd;
	scsi_qla_host_t	*vha;
	काष्ठा scsi_cmnd *cmd;
	काष्ठा scatterlist *sg;
	पूर्णांक i, cont;
	काष्ठा req_que *req;
	cont_a64_entry_t lcont_pkt;
	cont_a64_entry_t *cont_pkt;

	vha = sp->vha;
	req = vha->req;

	cmd = GET_CMD_SP(sp);
	cont = 0;
	cont_pkt = शून्य;

	/* Update entry type to indicate Command Type 3 IOCB */
	lcmd_pkt->entry_type = FX00_COMMAND_TYPE_7;

	/* No data transfer */
	अगर (!scsi_bufflen(cmd) || cmd->sc_data_direction == DMA_NONE) अणु
		lcmd_pkt->byte_count = cpu_to_le32(0);
		वापस;
	पूर्ण

	/* Set transfer direction */
	अगर (cmd->sc_data_direction == DMA_TO_DEVICE) अणु
		lcmd_pkt->cntrl_flags = TMF_WRITE_DATA;
		vha->qla_stats.output_bytes += scsi_bufflen(cmd);
	पूर्ण अन्यथा अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
		lcmd_pkt->cntrl_flags = TMF_READ_DATA;
		vha->qla_stats.input_bytes += scsi_bufflen(cmd);
	पूर्ण

	/* One DSD is available in the Command Type 3 IOCB */
	avail_dsds = 1;
	cur_dsd = &lcmd_pkt->dsd;

	/* Load data segments */
	scsi_क्रम_each_sg(cmd, sg, tot_dsds, i) अणु
		/* Allocate additional continuation packets? */
		अगर (avail_dsds == 0) अणु
			/*
			 * Five DSDs are available in the Continuation
			 * Type 1 IOCB.
			 */
			स_रखो(&lcont_pkt, 0, REQUEST_ENTRY_SIZE);
			cont_pkt =
			    qlafx00_prep_cont_type1_iocb(req, &lcont_pkt);
			cur_dsd = lcont_pkt.dsd;
			avail_dsds = 5;
			cont = 1;
		पूर्ण

		append_dsd64(&cur_dsd, sg);
		avail_dsds--;
		अगर (avail_dsds == 0 && cont == 1) अणु
			cont = 0;
			स_नकल_toio((व्योम __iomem *)cont_pkt, &lcont_pkt,
			    माप(lcont_pkt));
		पूर्ण

	पूर्ण
	अगर (avail_dsds != 0 && cont == 1) अणु
		स_नकल_toio((व्योम __iomem *)cont_pkt, &lcont_pkt,
		    माप(lcont_pkt));
	पूर्ण
पूर्ण

/**
 * qlafx00_start_scsi() - Send a SCSI command to the ISP
 * @sp: command to send to the ISP
 *
 * Returns non-zero अगर a failure occurred, अन्यथा zero.
 */
पूर्णांक
qlafx00_start_scsi(srb_t *sp)
अणु
	पूर्णांक		nseg;
	अचिन्हित दीर्घ   flags;
	uपूर्णांक32_t	handle;
	uपूर्णांक16_t	cnt;
	uपूर्णांक16_t	req_cnt;
	uपूर्णांक16_t	tot_dsds;
	काष्ठा req_que *req = शून्य;
	काष्ठा rsp_que *rsp = शून्य;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);
	काष्ठा scsi_qla_host *vha = sp->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा cmd_type_7_fx00 *cmd_pkt;
	काष्ठा cmd_type_7_fx00 lcmd_pkt;
	काष्ठा scsi_lun llun;

	/* Setup device poपूर्णांकers. */
	rsp = ha->rsp_q_map[0];
	req = vha->req;

	/* So we know we haven't pci_map'ed anything yet */
	tot_dsds = 0;

	/* Acquire ring specअगरic lock */
	spin_lock_irqsave(&ha->hardware_lock, flags);

	handle = qla2xxx_get_next_handle(req);
	अगर (handle == 0)
		जाओ queuing_error;

	/* Map the sg table so we have an accurate count of sg entries needed */
	अगर (scsi_sg_count(cmd)) अणु
		nseg = dma_map_sg(&ha->pdev->dev, scsi_sglist(cmd),
		    scsi_sg_count(cmd), cmd->sc_data_direction);
		अगर (unlikely(!nseg))
			जाओ queuing_error;
	पूर्ण अन्यथा
		nseg = 0;

	tot_dsds = nseg;
	req_cnt = qla24xx_calc_iocbs(vha, tot_dsds);
	अगर (req->cnt < (req_cnt + 2)) अणु
		cnt = rd_reg_dword_relaxed(req->req_q_out);

		अगर (req->ring_index < cnt)
			req->cnt = cnt - req->ring_index;
		अन्यथा
			req->cnt = req->length -
				(req->ring_index - cnt);
		अगर (req->cnt < (req_cnt + 2))
			जाओ queuing_error;
	पूर्ण

	/* Build command packet. */
	req->current_outstanding_cmd = handle;
	req->outstanding_cmds[handle] = sp;
	sp->handle = handle;
	cmd->host_scribble = (अचिन्हित अक्षर *)(अचिन्हित दीर्घ)handle;
	req->cnt -= req_cnt;

	cmd_pkt = (काष्ठा cmd_type_7_fx00 *)req->ring_ptr;

	स_रखो(&lcmd_pkt, 0, REQUEST_ENTRY_SIZE);

	lcmd_pkt.handle = make_handle(req->id, sp->handle);
	lcmd_pkt.reserved_0 = 0;
	lcmd_pkt.port_path_ctrl = 0;
	lcmd_pkt.reserved_1 = 0;
	lcmd_pkt.dseg_count = cpu_to_le16(tot_dsds);
	lcmd_pkt.tgt_idx = cpu_to_le16(sp->fcport->tgt_id);

	पूर्णांक_to_scsilun(cmd->device->lun, &llun);
	host_to_adap((uपूर्णांक8_t *)&llun, (uपूर्णांक8_t *)&lcmd_pkt.lun,
	    माप(lcmd_pkt.lun));

	/* Load SCSI command packet. */
	host_to_adap(cmd->cmnd, lcmd_pkt.fcp_cdb, माप(lcmd_pkt.fcp_cdb));
	lcmd_pkt.byte_count = cpu_to_le32((uपूर्णांक32_t)scsi_bufflen(cmd));

	/* Build IOCB segments */
	qlafx00_build_scsi_iocbs(sp, cmd_pkt, tot_dsds, &lcmd_pkt);

	/* Set total data segment count. */
	lcmd_pkt.entry_count = (uपूर्णांक8_t)req_cnt;

	/* Specअगरy response queue number where completion should happen */
	lcmd_pkt.entry_status = (uपूर्णांक8_t) rsp->id;

	ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x302e,
	    cmd->cmnd, cmd->cmd_len);
	ql_dump_buffer(ql_dbg_io + ql_dbg_buffer, vha, 0x3032,
	    &lcmd_pkt, माप(lcmd_pkt));

	स_नकल_toio((व्योम __iomem *)cmd_pkt, &lcmd_pkt, REQUEST_ENTRY_SIZE);
	wmb();

	/* Adjust ring index. */
	req->ring_index++;
	अगर (req->ring_index == req->length) अणु
		req->ring_index = 0;
		req->ring_ptr = req->ring;
	पूर्ण अन्यथा
		req->ring_ptr++;

	sp->flags |= SRB_DMA_VALID;

	/* Set chip new ring index. */
	wrt_reg_dword(req->req_q_in, req->ring_index);
	QLAFX00_SET_HST_INTR(ha, ha->rqstq_पूर्णांकr_code);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	वापस QLA_SUCCESS;

queuing_error:
	अगर (tot_dsds)
		scsi_dma_unmap(cmd);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	वापस QLA_FUNCTION_FAILED;
पूर्ण

व्योम
qlafx00_पंचांग_iocb(srb_t *sp, काष्ठा tsk_mgmt_entry_fx00 *pपंचांग_iocb)
अणु
	काष्ठा srb_iocb *fxio = &sp->u.iocb_cmd;
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा req_que *req = vha->req;
	काष्ठा tsk_mgmt_entry_fx00 पंचांग_iocb;
	काष्ठा scsi_lun llun;

	स_रखो(&पंचांग_iocb, 0, माप(काष्ठा tsk_mgmt_entry_fx00));
	पंचांग_iocb.entry_type = TSK_MGMT_IOCB_TYPE_FX00;
	पंचांग_iocb.entry_count = 1;
	पंचांग_iocb.handle = make_handle(req->id, sp->handle);
	पंचांग_iocb.reserved_0 = 0;
	पंचांग_iocb.tgt_id = cpu_to_le16(sp->fcport->tgt_id);
	पंचांग_iocb.control_flags = cpu_to_le32(fxio->u.पंचांगf.flags);
	अगर (पंचांग_iocb.control_flags == cpu_to_le32((uपूर्णांक32_t)TCF_LUN_RESET)) अणु
		पूर्णांक_to_scsilun(fxio->u.पंचांगf.lun, &llun);
		host_to_adap((uपूर्णांक8_t *)&llun, (uपूर्णांक8_t *)&पंचांग_iocb.lun,
		    माप(काष्ठा scsi_lun));
	पूर्ण

	स_नकल(pपंचांग_iocb, &पंचांग_iocb,
	    माप(काष्ठा tsk_mgmt_entry_fx00));
	wmb();
पूर्ण

व्योम
qlafx00_पात_iocb(srb_t *sp, काष्ठा पात_iocb_entry_fx00 *pabt_iocb)
अणु
	काष्ठा srb_iocb *fxio = &sp->u.iocb_cmd;
	scsi_qla_host_t *vha = sp->vha;
	काष्ठा req_que *req = vha->req;
	काष्ठा पात_iocb_entry_fx00 abt_iocb;

	स_रखो(&abt_iocb, 0, माप(काष्ठा पात_iocb_entry_fx00));
	abt_iocb.entry_type = ABORT_IOCB_TYPE_FX00;
	abt_iocb.entry_count = 1;
	abt_iocb.handle = make_handle(req->id, sp->handle);
	abt_iocb.पात_handle = make_handle(req->id, fxio->u.abt.cmd_hndl);
	abt_iocb.tgt_id_sts = cpu_to_le16(sp->fcport->tgt_id);
	abt_iocb.req_que_no = cpu_to_le16(req->id);

	स_नकल(pabt_iocb, &abt_iocb,
	    माप(काष्ठा पात_iocb_entry_fx00));
	wmb();
पूर्ण

व्योम
qlafx00_fxdisc_iocb(srb_t *sp, काष्ठा fxdisc_entry_fx00 *pfxiocb)
अणु
	काष्ठा srb_iocb *fxio = &sp->u.iocb_cmd;
	काष्ठा qla_mt_iocb_rqst_fx00 *piocb_rqst;
	काष्ठा bsg_job *bsg_job;
	काष्ठा fc_bsg_request *bsg_request;
	काष्ठा fxdisc_entry_fx00 fx_iocb;
	uपूर्णांक8_t entry_cnt = 1;

	स_रखो(&fx_iocb, 0, माप(काष्ठा fxdisc_entry_fx00));
	fx_iocb.entry_type = FX00_IOCB_TYPE;
	fx_iocb.handle = sp->handle;
	fx_iocb.entry_count = entry_cnt;

	अगर (sp->type == SRB_FXIOCB_DCMD) अणु
		fx_iocb.func_num =
		    sp->u.iocb_cmd.u.fxiocb.req_func_type;
		fx_iocb.adapid = fxio->u.fxiocb.adapter_id;
		fx_iocb.adapid_hi = fxio->u.fxiocb.adapter_id_hi;
		fx_iocb.reserved_0 = fxio->u.fxiocb.reserved_0;
		fx_iocb.reserved_1 = fxio->u.fxiocb.reserved_1;
		fx_iocb.dataword_extra = fxio->u.fxiocb.req_data_extra;

		अगर (fxio->u.fxiocb.flags & SRB_FXDISC_REQ_DMA_VALID) अणु
			fx_iocb.req_dsdcnt = cpu_to_le16(1);
			fx_iocb.req_xfrcnt =
			    cpu_to_le16(fxio->u.fxiocb.req_len);
			put_unaligned_le64(fxio->u.fxiocb.req_dma_handle,
					   &fx_iocb.dseg_rq[0].address);
			fx_iocb.dseg_rq[0].length =
			    cpu_to_le32(fxio->u.fxiocb.req_len);
		पूर्ण

		अगर (fxio->u.fxiocb.flags & SRB_FXDISC_RESP_DMA_VALID) अणु
			fx_iocb.rsp_dsdcnt = cpu_to_le16(1);
			fx_iocb.rsp_xfrcnt =
			    cpu_to_le16(fxio->u.fxiocb.rsp_len);
			put_unaligned_le64(fxio->u.fxiocb.rsp_dma_handle,
					   &fx_iocb.dseg_rsp[0].address);
			fx_iocb.dseg_rsp[0].length =
			    cpu_to_le32(fxio->u.fxiocb.rsp_len);
		पूर्ण

		अगर (fxio->u.fxiocb.flags & SRB_FXDISC_REQ_DWRD_VALID) अणु
			fx_iocb.dataword = fxio->u.fxiocb.req_data;
		पूर्ण
		fx_iocb.flags = fxio->u.fxiocb.flags;
	पूर्ण अन्यथा अणु
		काष्ठा scatterlist *sg;

		bsg_job = sp->u.bsg_job;
		bsg_request = bsg_job->request;
		piocb_rqst = (काष्ठा qla_mt_iocb_rqst_fx00 *)
			&bsg_request->rqst_data.h_venकरोr.venकरोr_cmd[1];

		fx_iocb.func_num = piocb_rqst->func_type;
		fx_iocb.adapid = piocb_rqst->adapid;
		fx_iocb.adapid_hi = piocb_rqst->adapid_hi;
		fx_iocb.reserved_0 = piocb_rqst->reserved_0;
		fx_iocb.reserved_1 = piocb_rqst->reserved_1;
		fx_iocb.dataword_extra = piocb_rqst->dataword_extra;
		fx_iocb.dataword = piocb_rqst->dataword;
		fx_iocb.req_xfrcnt = piocb_rqst->req_len;
		fx_iocb.rsp_xfrcnt = piocb_rqst->rsp_len;

		अगर (piocb_rqst->flags & SRB_FXDISC_REQ_DMA_VALID) अणु
			पूर्णांक avail_dsds, tot_dsds;
			cont_a64_entry_t lcont_pkt;
			cont_a64_entry_t *cont_pkt = शून्य;
			काष्ठा dsd64 *cur_dsd;
			पूर्णांक index = 0, cont = 0;

			fx_iocb.req_dsdcnt =
			    cpu_to_le16(bsg_job->request_payload.sg_cnt);
			tot_dsds =
			    bsg_job->request_payload.sg_cnt;
			cur_dsd = &fx_iocb.dseg_rq[0];
			avail_dsds = 1;
			क्रम_each_sg(bsg_job->request_payload.sg_list, sg,
			    tot_dsds, index) अणु
				/* Allocate additional continuation packets? */
				अगर (avail_dsds == 0) अणु
					/*
					 * Five DSDs are available in the Cont.
					 * Type 1 IOCB.
					 */
					स_रखो(&lcont_pkt, 0,
					    REQUEST_ENTRY_SIZE);
					cont_pkt =
					    qlafx00_prep_cont_type1_iocb(
						sp->vha->req, &lcont_pkt);
					cur_dsd = lcont_pkt.dsd;
					avail_dsds = 5;
					cont = 1;
					entry_cnt++;
				पूर्ण

				append_dsd64(&cur_dsd, sg);
				avail_dsds--;

				अगर (avail_dsds == 0 && cont == 1) अणु
					cont = 0;
					स_नकल_toio(
					    (व्योम __iomem *)cont_pkt,
					    &lcont_pkt, REQUEST_ENTRY_SIZE);
					ql_dump_buffer(
					    ql_dbg_user + ql_dbg_verbose,
					    sp->vha, 0x3042,
					    (uपूर्णांक8_t *)&lcont_pkt,
					     REQUEST_ENTRY_SIZE);
				पूर्ण
			पूर्ण
			अगर (avail_dsds != 0 && cont == 1) अणु
				स_नकल_toio((व्योम __iomem *)cont_pkt,
				    &lcont_pkt, REQUEST_ENTRY_SIZE);
				ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
				    sp->vha, 0x3043,
				    (uपूर्णांक8_t *)&lcont_pkt, REQUEST_ENTRY_SIZE);
			पूर्ण
		पूर्ण

		अगर (piocb_rqst->flags & SRB_FXDISC_RESP_DMA_VALID) अणु
			पूर्णांक avail_dsds, tot_dsds;
			cont_a64_entry_t lcont_pkt;
			cont_a64_entry_t *cont_pkt = शून्य;
			काष्ठा dsd64 *cur_dsd;
			पूर्णांक index = 0, cont = 0;

			fx_iocb.rsp_dsdcnt =
			   cpu_to_le16(bsg_job->reply_payload.sg_cnt);
			tot_dsds = bsg_job->reply_payload.sg_cnt;
			cur_dsd = &fx_iocb.dseg_rsp[0];
			avail_dsds = 1;

			क्रम_each_sg(bsg_job->reply_payload.sg_list, sg,
			    tot_dsds, index) अणु
				/* Allocate additional continuation packets? */
				अगर (avail_dsds == 0) अणु
					/*
					* Five DSDs are available in the Cont.
					* Type 1 IOCB.
					*/
					स_रखो(&lcont_pkt, 0,
					    REQUEST_ENTRY_SIZE);
					cont_pkt =
					    qlafx00_prep_cont_type1_iocb(
						sp->vha->req, &lcont_pkt);
					cur_dsd = lcont_pkt.dsd;
					avail_dsds = 5;
					cont = 1;
					entry_cnt++;
				पूर्ण

				append_dsd64(&cur_dsd, sg);
				avail_dsds--;

				अगर (avail_dsds == 0 && cont == 1) अणु
					cont = 0;
					स_नकल_toio((व्योम __iomem *)cont_pkt,
					    &lcont_pkt,
					    REQUEST_ENTRY_SIZE);
					ql_dump_buffer(
					    ql_dbg_user + ql_dbg_verbose,
					    sp->vha, 0x3045,
					    (uपूर्णांक8_t *)&lcont_pkt,
					    REQUEST_ENTRY_SIZE);
				पूर्ण
			पूर्ण
			अगर (avail_dsds != 0 && cont == 1) अणु
				स_नकल_toio((व्योम __iomem *)cont_pkt,
				    &lcont_pkt, REQUEST_ENTRY_SIZE);
				ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
				    sp->vha, 0x3046,
				    (uपूर्णांक8_t *)&lcont_pkt, REQUEST_ENTRY_SIZE);
			पूर्ण
		पूर्ण

		अगर (piocb_rqst->flags & SRB_FXDISC_REQ_DWRD_VALID)
			fx_iocb.dataword = piocb_rqst->dataword;
		fx_iocb.flags = piocb_rqst->flags;
		fx_iocb.entry_count = entry_cnt;
	पूर्ण

	ql_dump_buffer(ql_dbg_user + ql_dbg_verbose,
	    sp->vha, 0x3047, &fx_iocb, माप(fx_iocb));

	स_नकल_toio((व्योम __iomem *)pfxiocb, &fx_iocb, माप(fx_iocb));
	wmb();
पूर्ण
