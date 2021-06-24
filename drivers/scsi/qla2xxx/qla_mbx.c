<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic Fibre Channel HBA Driver
 * Copyright (c)  2003-2014 QLogic Corporation
 */
#समावेश "qla_def.h"
#समावेश "qla_target.h"

#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>

अटल काष्ठा mb_cmd_name अणु
	uपूर्णांक16_t cmd;
	स्थिर अक्षर *str;
पूर्ण mb_str[] = अणु
	अणुMBC_GET_PORT_DATABASE,		"GPDB"पूर्ण,
	अणुMBC_GET_ID_LIST,		"GIDList"पूर्ण,
	अणुMBC_GET_LINK_PRIV_STATS,	"Stats"पूर्ण,
	अणुMBC_GET_RESOURCE_COUNTS,	"ResCnt"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *mb_to_str(uपूर्णांक16_t cmd)
अणु
	पूर्णांक i;
	काष्ठा mb_cmd_name *e;

	क्रम (i = 0; i < ARRAY_SIZE(mb_str); i++) अणु
		e = mb_str + i;
		अगर (cmd == e->cmd)
			वापस e->str;
	पूर्ण
	वापस "unknown";
पूर्ण

अटल काष्ठा rom_cmd अणु
	uपूर्णांक16_t cmd;
पूर्ण rom_cmds[] = अणु
	अणु MBC_LOAD_RAM पूर्ण,
	अणु MBC_EXECUTE_FIRMWARE पूर्ण,
	अणु MBC_READ_RAM_WORD पूर्ण,
	अणु MBC_MAILBOX_REGISTER_TEST पूर्ण,
	अणु MBC_VERIFY_CHECKSUM पूर्ण,
	अणु MBC_GET_FIRMWARE_VERSION पूर्ण,
	अणु MBC_LOAD_RISC_RAM पूर्ण,
	अणु MBC_DUMP_RISC_RAM पूर्ण,
	अणु MBC_LOAD_RISC_RAM_EXTENDED पूर्ण,
	अणु MBC_DUMP_RISC_RAM_EXTENDED पूर्ण,
	अणु MBC_WRITE_RAM_WORD_EXTENDED पूर्ण,
	अणु MBC_READ_RAM_EXTENDED पूर्ण,
	अणु MBC_GET_RESOURCE_COUNTS पूर्ण,
	अणु MBC_SET_FIRMWARE_OPTION पूर्ण,
	अणु MBC_MID_INITIALIZE_FIRMWARE पूर्ण,
	अणु MBC_GET_FIRMWARE_STATE पूर्ण,
	अणु MBC_GET_MEM_OFFLOAD_CNTRL_STAT पूर्ण,
	अणु MBC_GET_RETRY_COUNT पूर्ण,
	अणु MBC_TRACE_CONTROL पूर्ण,
	अणु MBC_INITIALIZE_MULTIQ पूर्ण,
	अणु MBC_IOCB_COMMAND_A64 पूर्ण,
	अणु MBC_GET_ADAPTER_LOOP_ID पूर्ण,
	अणु MBC_READ_SFP पूर्ण,
	अणु MBC_SET_RNID_PARAMS पूर्ण,
	अणु MBC_GET_RNID_PARAMS पूर्ण,
	अणु MBC_GET_SET_ZIO_THRESHOLD पूर्ण,
पूर्ण;

अटल पूर्णांक is_rom_cmd(uपूर्णांक16_t cmd)
अणु
	पूर्णांक i;
	काष्ठा  rom_cmd *wc;

	क्रम (i = 0; i < ARRAY_SIZE(rom_cmds); i++) अणु
		wc = rom_cmds + i;
		अगर (wc->cmd == cmd)
			वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * qla2x00_mailbox_command
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
qla2x00_mailbox_command(scsi_qla_host_t *vha, mbx_cmd_t *mcp)
अणु
	पूर्णांक		rval, i;
	अचिन्हित दीर्घ    flags = 0;
	device_reg_t *reg;
	uपूर्णांक8_t		पात_active, eeh_delay;
	uपूर्णांक8_t		io_lock_on;
	uपूर्णांक16_t	command = 0;
	uपूर्णांक16_t	*iptr;
	__le16 __iomem  *optr;
	uपूर्णांक32_t	cnt;
	uपूर्णांक32_t	mboxes;
	अचिन्हित दीर्घ	रुको_समय;
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);
	u32 chip_reset;


	ql_dbg(ql_dbg_mbx, vha, 0x1000, "Entered %s.\n", __func__);

	अगर (ha->pdev->error_state == pci_channel_io_perm_failure) अणु
		ql_log(ql_log_warn, vha, 0x1001,
		    "PCI channel failed permanently, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	अगर (vha->device_flags & DFLG_DEV_FAILED) अणु
		ql_log(ql_log_warn, vha, 0x1002,
		    "Device in failed state, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	/* अगर PCI error, then aव्योम mbx processing.*/
	अगर (test_bit(PFLG_DISCONNECTED, &base_vha->dpc_flags) &&
	    test_bit(UNLOADING, &base_vha->dpc_flags)) अणु
		ql_log(ql_log_warn, vha, 0xd04e,
		    "PCI error, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण
	eeh_delay = 0;
	reg = ha->iobase;
	io_lock_on = base_vha->flags.init_करोne;

	rval = QLA_SUCCESS;
	पात_active = test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags);
	chip_reset = ha->chip_reset;

	अगर (ha->flags.pci_channel_io_perm_failure) अणु
		ql_log(ql_log_warn, vha, 0x1003,
		    "Perm failure on EEH timeout MBX, exiting.\n");
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	अगर (IS_P3P_TYPE(ha) && ha->flags.isp82xx_fw_hung) अणु
		/* Setting Link-Down error */
		mcp->mb[0] = MBS_LINK_DOWN_ERROR;
		ql_log(ql_log_warn, vha, 0x1004,
		    "FW hung = %d.\n", ha->flags.isp82xx_fw_hung);
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	/* check अगर ISP पात is active and वापस cmd with समयout */
	अगर (((test_bit(ABORT_ISP_ACTIVE, &base_vha->dpc_flags) ||
	      test_bit(ISP_ABORT_RETRY, &base_vha->dpc_flags) ||
	      test_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags)) &&
	      !is_rom_cmd(mcp->mb[0])) || ha->flags.eeh_busy) अणु
		ql_log(ql_log_info, vha, 0x1005,
		    "Cmd 0x%x aborted with timeout since ISP Abort is pending\n",
		    mcp->mb[0]);
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण

	atomic_inc(&ha->num_pend_mbx_stage1);
	/*
	 * Wait क्रम active mailbox commands to finish by रुकोing at most tov
	 * seconds. This is to serialize actual issuing of mailbox cmds during
	 * non ISP पात समय.
	 */
	अगर (!रुको_क्रम_completion_समयout(&ha->mbx_cmd_comp, mcp->tov * HZ)) अणु
		/* Timeout occurred. Return error. */
		ql_log(ql_log_warn, vha, 0xd035,
		    "Cmd access timeout, cmd=0x%x, Exiting.\n",
		    mcp->mb[0]);
		vha->hw_err_cnt++;
		atomic_dec(&ha->num_pend_mbx_stage1);
		वापस QLA_FUNCTION_TIMEOUT;
	पूर्ण
	atomic_dec(&ha->num_pend_mbx_stage1);
	अगर (ha->flags.purge_mbox || chip_reset != ha->chip_reset ||
	    ha->flags.eeh_busy) अणु
		ql_log(ql_log_warn, vha, 0xd035,
		       "Error detected: purge[%d] eeh[%d] cmd=0x%x, Exiting.\n",
		       ha->flags.purge_mbox, ha->flags.eeh_busy, mcp->mb[0]);
		rval = QLA_ABORTED;
		जाओ premature_निकास;
	पूर्ण


	/* Save mailbox command क्रम debug */
	ha->mcp = mcp;

	ql_dbg(ql_dbg_mbx, vha, 0x1006,
	    "Prepare to issue mbox cmd=0x%x.\n", mcp->mb[0]);

	spin_lock_irqsave(&ha->hardware_lock, flags);

	अगर (ha->flags.purge_mbox || chip_reset != ha->chip_reset ||
	    ha->flags.mbox_busy) अणु
		rval = QLA_ABORTED;
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
		जाओ premature_निकास;
	पूर्ण
	ha->flags.mbox_busy = 1;

	/* Load mailbox रेजिस्टरs. */
	अगर (IS_P3P_TYPE(ha))
		optr = &reg->isp82.mailbox_in[0];
	अन्यथा अगर (IS_FWI2_CAPABLE(ha) && !(IS_P3P_TYPE(ha)))
		optr = &reg->isp24.mailbox0;
	अन्यथा
		optr = MAILBOX_REG(ha, &reg->isp, 0);

	iptr = mcp->mb;
	command = mcp->mb[0];
	mboxes = mcp->out_mb;

	ql_dbg(ql_dbg_mbx, vha, 0x1111,
	    "Mailbox registers (OUT):\n");
	क्रम (cnt = 0; cnt < ha->mbx_count; cnt++) अणु
		अगर (IS_QLA2200(ha) && cnt == 8)
			optr = MAILBOX_REG(ha, &reg->isp, 8);
		अगर (mboxes & BIT_0) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1112,
			    "mbox[%d]<-0x%04x\n", cnt, *iptr);
			wrt_reg_word(optr, *iptr);
		पूर्ण

		mboxes >>= 1;
		optr++;
		iptr++;
	पूर्ण

	ql_dbg(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1117,
	    "I/O Address = %p.\n", optr);

	/* Issue set host पूर्णांकerrupt command to send cmd out. */
	ha->flags.mbox_पूर्णांक = 0;
	clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

	/* Unlock mbx रेजिस्टरs and रुको क्रम पूर्णांकerrupt */
	ql_dbg(ql_dbg_mbx, vha, 0x100f,
	    "Going to unlock irq & waiting for interrupts. "
	    "jiffies=%lx.\n", jअगरfies);

	/* Wait क्रम mbx cmd completion until समयout */
	atomic_inc(&ha->num_pend_mbx_stage2);
	अगर ((!पात_active && io_lock_on) || IS_NOPOLLING_TYPE(ha)) अणु
		set_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags);

		अगर (IS_P3P_TYPE(ha))
			wrt_reg_dword(&reg->isp82.hपूर्णांक, HINT_MBX_INT_PENDING);
		अन्यथा अगर (IS_FWI2_CAPABLE(ha))
			wrt_reg_dword(&reg->isp24.hccr, HCCRX_SET_HOST_INT);
		अन्यथा
			wrt_reg_word(&reg->isp.hccr, HCCR_SET_HOST_INT);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		रुको_समय = jअगरfies;
		atomic_inc(&ha->num_pend_mbx_stage3);
		अगर (!रुको_क्रम_completion_समयout(&ha->mbx_पूर्णांकr_comp,
		    mcp->tov * HZ)) अणु
			अगर (chip_reset != ha->chip_reset) अणु
				eeh_delay = ha->flags.eeh_busy ? 1 : 0;

				spin_lock_irqsave(&ha->hardware_lock, flags);
				ha->flags.mbox_busy = 0;
				spin_unlock_irqrestore(&ha->hardware_lock,
				    flags);
				atomic_dec(&ha->num_pend_mbx_stage2);
				atomic_dec(&ha->num_pend_mbx_stage3);
				rval = QLA_ABORTED;
				जाओ premature_निकास;
			पूर्ण
			ql_dbg(ql_dbg_mbx, vha, 0x117a,
			    "cmd=%x Timeout.\n", command);
			spin_lock_irqsave(&ha->hardware_lock, flags);
			clear_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags);
			spin_unlock_irqrestore(&ha->hardware_lock, flags);

		पूर्ण अन्यथा अगर (ha->flags.purge_mbox ||
		    chip_reset != ha->chip_reset) अणु
			eeh_delay = ha->flags.eeh_busy ? 1 : 0;

			spin_lock_irqsave(&ha->hardware_lock, flags);
			ha->flags.mbox_busy = 0;
			spin_unlock_irqrestore(&ha->hardware_lock, flags);
			atomic_dec(&ha->num_pend_mbx_stage2);
			atomic_dec(&ha->num_pend_mbx_stage3);
			rval = QLA_ABORTED;
			जाओ premature_निकास;
		पूर्ण
		atomic_dec(&ha->num_pend_mbx_stage3);

		अगर (समय_after(jअगरfies, रुको_समय + 5 * HZ))
			ql_log(ql_log_warn, vha, 0x1015, "cmd=0x%x, waited %d msecs\n",
			    command, jअगरfies_to_msecs(jअगरfies - रुको_समय));
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1011,
		    "Cmd=%x Polling Mode.\n", command);

		अगर (IS_P3P_TYPE(ha)) अणु
			अगर (rd_reg_dword(&reg->isp82.hपूर्णांक) &
				HINT_MBX_INT_PENDING) अणु
				ha->flags.mbox_busy = 0;
				spin_unlock_irqrestore(&ha->hardware_lock,
					flags);
				atomic_dec(&ha->num_pend_mbx_stage2);
				ql_dbg(ql_dbg_mbx, vha, 0x1012,
				    "Pending mailbox timeout, exiting.\n");
				vha->hw_err_cnt++;
				rval = QLA_FUNCTION_TIMEOUT;
				जाओ premature_निकास;
			पूर्ण
			wrt_reg_dword(&reg->isp82.hपूर्णांक, HINT_MBX_INT_PENDING);
		पूर्ण अन्यथा अगर (IS_FWI2_CAPABLE(ha))
			wrt_reg_dword(&reg->isp24.hccr, HCCRX_SET_HOST_INT);
		अन्यथा
			wrt_reg_word(&reg->isp.hccr, HCCR_SET_HOST_INT);
		spin_unlock_irqrestore(&ha->hardware_lock, flags);

		रुको_समय = jअगरfies + mcp->tov * HZ; /* रुको at most tov secs */
		जबतक (!ha->flags.mbox_पूर्णांक) अणु
			अगर (ha->flags.purge_mbox ||
			    chip_reset != ha->chip_reset) अणु
				eeh_delay = ha->flags.eeh_busy ? 1 : 0;

				spin_lock_irqsave(&ha->hardware_lock, flags);
				ha->flags.mbox_busy = 0;
				spin_unlock_irqrestore(&ha->hardware_lock,
				    flags);
				atomic_dec(&ha->num_pend_mbx_stage2);
				rval = QLA_ABORTED;
				जाओ premature_निकास;
			पूर्ण

			अगर (समय_after(jअगरfies, रुको_समय))
				अवरोध;

			/* Check क्रम pending पूर्णांकerrupts. */
			qla2x00_poll(ha->rsp_q_map[0]);

			अगर (!ha->flags.mbox_पूर्णांक &&
			    !(IS_QLA2200(ha) &&
			    command == MBC_LOAD_RISC_RAM_EXTENDED))
				msleep(10);
		पूर्ण /* जबतक */
		ql_dbg(ql_dbg_mbx, vha, 0x1013,
		    "Waited %d sec.\n",
		    (uपूर्णांक)((jअगरfies - (रुको_समय - (mcp->tov * HZ)))/HZ));
	पूर्ण
	atomic_dec(&ha->num_pend_mbx_stage2);

	/* Check whether we समयd out */
	अगर (ha->flags.mbox_पूर्णांक) अणु
		uपूर्णांक16_t *iptr2;

		ql_dbg(ql_dbg_mbx, vha, 0x1014,
		    "Cmd=%x completed.\n", command);

		/* Got पूर्णांकerrupt. Clear the flag. */
		ha->flags.mbox_पूर्णांक = 0;
		clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

		अगर (IS_P3P_TYPE(ha) && ha->flags.isp82xx_fw_hung) अणु
			spin_lock_irqsave(&ha->hardware_lock, flags);
			ha->flags.mbox_busy = 0;
			spin_unlock_irqrestore(&ha->hardware_lock, flags);

			/* Setting Link-Down error */
			mcp->mb[0] = MBS_LINK_DOWN_ERROR;
			ha->mcp = शून्य;
			rval = QLA_FUNCTION_FAILED;
			ql_log(ql_log_warn, vha, 0xd048,
			    "FW hung = %d.\n", ha->flags.isp82xx_fw_hung);
			जाओ premature_निकास;
		पूर्ण

		अगर (ha->mailbox_out[0] != MBS_COMMAND_COMPLETE) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x11ff,
			       "mb_out[0] = %#x <> %#x\n", ha->mailbox_out[0],
			       MBS_COMMAND_COMPLETE);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण

		/* Load वापस mailbox रेजिस्टरs. */
		iptr2 = mcp->mb;
		iptr = (uपूर्णांक16_t *)&ha->mailbox_out[0];
		mboxes = mcp->in_mb;

		ql_dbg(ql_dbg_mbx, vha, 0x1113,
		    "Mailbox registers (IN):\n");
		क्रम (cnt = 0; cnt < ha->mbx_count; cnt++) अणु
			अगर (mboxes & BIT_0) अणु
				*iptr2 = *iptr;
				ql_dbg(ql_dbg_mbx, vha, 0x1114,
				    "mbox[%d]->0x%04x\n", cnt, *iptr2);
			पूर्ण

			mboxes >>= 1;
			iptr2++;
			iptr++;
		पूर्ण
	पूर्ण अन्यथा अणु

		uपूर्णांक16_t mb[8];
		uपूर्णांक32_t ictrl, host_status, hccr;
		uपूर्णांक16_t        w;

		अगर (IS_FWI2_CAPABLE(ha)) अणु
			mb[0] = rd_reg_word(&reg->isp24.mailbox0);
			mb[1] = rd_reg_word(&reg->isp24.mailbox1);
			mb[2] = rd_reg_word(&reg->isp24.mailbox2);
			mb[3] = rd_reg_word(&reg->isp24.mailbox3);
			mb[7] = rd_reg_word(&reg->isp24.mailbox7);
			ictrl = rd_reg_dword(&reg->isp24.ictrl);
			host_status = rd_reg_dword(&reg->isp24.host_status);
			hccr = rd_reg_dword(&reg->isp24.hccr);

			ql_log(ql_log_warn, vha, 0xd04c,
			    "MBX Command timeout for cmd %x, iocontrol=%x jiffies=%lx "
			    "mb[0-3]=[0x%x 0x%x 0x%x 0x%x] mb7 0x%x host_status 0x%x hccr 0x%x\n",
			    command, ictrl, jअगरfies, mb[0], mb[1], mb[2], mb[3],
			    mb[7], host_status, hccr);
			vha->hw_err_cnt++;

		पूर्ण अन्यथा अणु
			mb[0] = RD_MAILBOX_REG(ha, &reg->isp, 0);
			ictrl = rd_reg_word(&reg->isp.ictrl);
			ql_dbg(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1119,
			    "MBX Command timeout for cmd %x, iocontrol=%x jiffies=%lx "
			    "mb[0]=0x%x\n", command, ictrl, jअगरfies, mb[0]);
			vha->hw_err_cnt++;
		पूर्ण
		ql_dump_regs(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1019);

		/* Capture FW dump only, अगर PCI device active */
		अगर (!pci_channel_offline(vha->hw->pdev)) अणु
			pci_पढ़ो_config_word(ha->pdev, PCI_VENDOR_ID, &w);
			अगर (w == 0xffff || ictrl == 0xffffffff ||
			    (chip_reset != ha->chip_reset)) अणु
				/* This is special हाल अगर there is unload
				 * of driver happening and अगर PCI device go
				 * पूर्णांकo bad state due to PCI error condition
				 * then only PCI ERR flag would be set.
				 * we will करो premature निकास क्रम above हाल.
				 */
				spin_lock_irqsave(&ha->hardware_lock, flags);
				ha->flags.mbox_busy = 0;
				spin_unlock_irqrestore(&ha->hardware_lock,
				    flags);
				rval = QLA_FUNCTION_TIMEOUT;
				जाओ premature_निकास;
			पूर्ण

			/* Attempt to capture firmware dump क्रम further
			 * anallysis of the current क्रमmware state. we करो not
			 * need to करो this अगर we are पूर्णांकentionally generating
			 * a dump
			 */
			अगर (mcp->mb[0] != MBC_GEN_SYSTEM_ERROR)
				qla2xxx_dump_fw(vha);
			rval = QLA_FUNCTION_TIMEOUT;
		 पूर्ण
	पूर्ण
	spin_lock_irqsave(&ha->hardware_lock, flags);
	ha->flags.mbox_busy = 0;
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/* Clean up */
	ha->mcp = शून्य;

	अगर ((पात_active || !io_lock_on) && !IS_NOPOLLING_TYPE(ha)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x101a,
		    "Checking for additional resp interrupt.\n");

		/* polling mode क्रम non isp_पात commands. */
		qla2x00_poll(ha->rsp_q_map[0]);
	पूर्ण

	अगर (rval == QLA_FUNCTION_TIMEOUT &&
	    mcp->mb[0] != MBC_GEN_SYSTEM_ERROR) अणु
		अगर (!io_lock_on || (mcp->flags & IOCTL_CMD) ||
		    ha->flags.eeh_busy) अणु
			/* not in dpc. schedule it क्रम dpc to take over. */
			ql_dbg(ql_dbg_mbx, vha, 0x101b,
			    "Timeout, schedule isp_abort_needed.\n");

			अगर (!test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) &&
			    !test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) &&
			    !test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु
				अगर (IS_QLA82XX(ha)) अणु
					ql_dbg(ql_dbg_mbx, vha, 0x112a,
					    "disabling pause transmit on port "
					    "0 & 1.\n");
					qla82xx_wr_32(ha,
					    QLA82XX_CRB_NIU + 0x98,
					    CRB_NIU_XG_PAUSE_CTL_P0|
					    CRB_NIU_XG_PAUSE_CTL_P1);
				पूर्ण
				ql_log(ql_log_info, base_vha, 0x101c,
				    "Mailbox cmd timeout occurred, cmd=0x%x, "
				    "mb[0]=0x%x, eeh_busy=0x%x. Scheduling ISP "
				    "abort.\n", command, mcp->mb[0],
				    ha->flags.eeh_busy);
				vha->hw_err_cnt++;
				set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				qla2xxx_wake_dpc(vha);
			पूर्ण
		पूर्ण अन्यथा अगर (current == ha->dpc_thपढ़ो) अणु
			/* call पात directly since we are in the DPC thपढ़ो */
			ql_dbg(ql_dbg_mbx, vha, 0x101d,
			    "Timeout, calling abort_isp.\n");

			अगर (!test_bit(ISP_ABORT_NEEDED, &vha->dpc_flags) &&
			    !test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags) &&
			    !test_bit(ISP_ABORT_RETRY, &vha->dpc_flags)) अणु
				अगर (IS_QLA82XX(ha)) अणु
					ql_dbg(ql_dbg_mbx, vha, 0x112b,
					    "disabling pause transmit on port "
					    "0 & 1.\n");
					qla82xx_wr_32(ha,
					    QLA82XX_CRB_NIU + 0x98,
					    CRB_NIU_XG_PAUSE_CTL_P0|
					    CRB_NIU_XG_PAUSE_CTL_P1);
				पूर्ण
				ql_log(ql_log_info, base_vha, 0x101e,
				    "Mailbox cmd timeout occurred, cmd=0x%x, "
				    "mb[0]=0x%x. Scheduling ISP abort ",
				    command, mcp->mb[0]);
				vha->hw_err_cnt++;
				set_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags);
				clear_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
				/* Allow next mbx cmd to come in. */
				complete(&ha->mbx_cmd_comp);
				अगर (ha->isp_ops->पात_isp(vha) &&
				    !ha->flags.eeh_busy) अणु
					/* Failed. retry later. */
					set_bit(ISP_ABORT_NEEDED,
					    &vha->dpc_flags);
				पूर्ण
				clear_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags);
				ql_dbg(ql_dbg_mbx, vha, 0x101f,
				    "Finished abort_isp.\n");
				जाओ mbx_करोne;
			पूर्ण
		पूर्ण
	पूर्ण

premature_निकास:
	/* Allow next mbx cmd to come in. */
	complete(&ha->mbx_cmd_comp);

mbx_करोne:
	अगर (rval == QLA_ABORTED) अणु
		ql_log(ql_log_info, vha, 0xd035,
		    "Chip Reset in progress. Purging Mbox cmd=0x%x.\n",
		    mcp->mb[0]);
	पूर्ण अन्यथा अगर (rval) अणु
		अगर (ql2xextended_error_logging & (ql_dbg_disc|ql_dbg_mbx)) अणु
			pr_warn("%s [%s]-%04x:%ld: **** Failed=%x", QL_MSGHDR,
			    dev_name(&ha->pdev->dev), 0x1020+0x800,
			    vha->host_no, rval);
			mboxes = mcp->in_mb;
			cnt = 4;
			क्रम (i = 0; i < ha->mbx_count && cnt; i++, mboxes >>= 1)
				अगर (mboxes & BIT_0) अणु
					prपूर्णांकk(" mb[%u]=%x", i, mcp->mb[i]);
					cnt--;
				पूर्ण
			pr_warn(" cmd=%x ****\n", command);
		पूर्ण
		अगर (IS_FWI2_CAPABLE(ha) && !(IS_P3P_TYPE(ha))) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1198,
			    "host_status=%#x intr_ctrl=%#x intr_status=%#x\n",
			    rd_reg_dword(&reg->isp24.host_status),
			    rd_reg_dword(&reg->isp24.ictrl),
			    rd_reg_dword(&reg->isp24.istatus));
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1206,
			    "ctrl_status=%#x ictrl=%#x istatus=%#x\n",
			    rd_reg_word(&reg->isp.ctrl_status),
			    rd_reg_word(&reg->isp.ictrl),
			    rd_reg_word(&reg->isp.istatus));
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx, base_vha, 0x1021, "Done %s.\n", __func__);
	पूर्ण

	i = 500;
	जबतक (i && eeh_delay && (ha->pci_error_state < QLA_PCI_SLOT_RESET)) अणु
		/*
		 * The caller of this mailbox encounter pci error.
		 * Hold the thपढ़ो until PCIE link reset complete to make
		 * sure caller करोes not unmap dma जबतक recovery is
		 * in progress.
		 */
		msleep(1);
		i--;
	पूर्ण
	वापस rval;
पूर्ण

पूर्णांक
qla2x00_load_ram(scsi_qla_host_t *vha, dma_addr_t req_dma, uपूर्णांक32_t risc_addr,
    uपूर्णांक32_t risc_code_size)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1022,
	    "Entered %s.\n", __func__);

	अगर (MSW(risc_addr) || IS_FWI2_CAPABLE(ha)) अणु
		mcp->mb[0] = MBC_LOAD_RISC_RAM_EXTENDED;
		mcp->mb[8] = MSW(risc_addr);
		mcp->out_mb = MBX_8|MBX_0;
	पूर्ण अन्यथा अणु
		mcp->mb[0] = MBC_LOAD_RISC_RAM;
		mcp->out_mb = MBX_0;
	पूर्ण
	mcp->mb[1] = LSW(risc_addr);
	mcp->mb[2] = MSW(req_dma);
	mcp->mb[3] = LSW(req_dma);
	mcp->mb[6] = MSW(MSD(req_dma));
	mcp->mb[7] = LSW(MSD(req_dma));
	mcp->out_mb |= MBX_7|MBX_6|MBX_3|MBX_2|MBX_1;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		mcp->mb[4] = MSW(risc_code_size);
		mcp->mb[5] = LSW(risc_code_size);
		mcp->out_mb |= MBX_5|MBX_4;
	पूर्ण अन्यथा अणु
		mcp->mb[4] = LSW(risc_code_size);
		mcp->out_mb |= MBX_4;
	पूर्ण

	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1023,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
		vha->hw_err_cnt++;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1024,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

#घोषणा	NVME_ENABLE_FLAG	BIT_3

/*
 * qla2x00_execute_fw
 *     Start adapter firmware.
 *
 * Input:
 *     ha = adapter block poपूर्णांकer.
 *     TARGET_QUEUE_LOCK must be released.
 *     ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *     qla2x00 local function वापस status code.
 *
 * Context:
 *     Kernel context.
 */
पूर्णांक
qla2x00_execute_fw(scsi_qla_host_t *vha, uपूर्णांक32_t risc_addr)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	u8 semaphore = 0;
#घोषणा EXE_FW_FORCE_SEMAPHORE BIT_7
	u8 retry = 3;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1025,
	    "Entered %s.\n", __func__);

again:
	mcp->mb[0] = MBC_EXECUTE_FIRMWARE;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		mcp->mb[1] = MSW(risc_addr);
		mcp->mb[2] = LSW(risc_addr);
		mcp->mb[3] = 0;
		mcp->mb[4] = 0;
		mcp->mb[11] = 0;

		/* Enable BPM? */
		अगर (ha->flags.lr_detected) अणु
			mcp->mb[4] = BIT_0;
			अगर (IS_BPM_RANGE_CAPABLE(ha))
				mcp->mb[4] |=
				    ha->lr_distance << LR_DIST_FW_POS;
		पूर्ण

		अगर (ql2xnvmeenable && (IS_QLA27XX(ha) || IS_QLA28XX(ha)))
			mcp->mb[4] |= NVME_ENABLE_FLAG;

		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			काष्ठा nvram_81xx *nv = ha->nvram;
			/* set minimum speed अगर specअगरied in nvram */
			अगर (nv->min_supported_speed >= 2 &&
			    nv->min_supported_speed <= 5) अणु
				mcp->mb[4] |= BIT_4;
				mcp->mb[11] |= nv->min_supported_speed & 0xF;
				mcp->out_mb |= MBX_11;
				mcp->in_mb |= BIT_5;
				vha->min_supported_speed =
				    nv->min_supported_speed;
			पूर्ण
		पूर्ण

		अगर (ha->flags.exlogins_enabled)
			mcp->mb[4] |= ENABLE_EXTENDED_LOGIN;

		अगर (ha->flags.exchoffld_enabled)
			mcp->mb[4] |= ENABLE_EXCHANGE_OFFLD;

		अगर (semaphore)
			mcp->mb[11] |= EXE_FW_FORCE_SEMAPHORE;

		mcp->out_mb |= MBX_4 | MBX_3 | MBX_2 | MBX_1 | MBX_11;
		mcp->in_mb |= MBX_3 | MBX_2 | MBX_1;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = LSW(risc_addr);
		mcp->out_mb |= MBX_1;
		अगर (IS_QLA2322(ha) || IS_QLA6322(ha)) अणु
			mcp->mb[2] = 0;
			mcp->out_mb |= MBX_2;
		पूर्ण
	पूर्ण

	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		अगर (IS_QLA28XX(ha) && rval == QLA_COMMAND_ERROR &&
		    mcp->mb[1] == 0x27 && retry) अणु
			semaphore = 1;
			retry--;
			ql_dbg(ql_dbg_async, vha, 0x1026,
			    "Exe FW: force semaphore.\n");
			जाओ again;
		पूर्ण

		ql_dbg(ql_dbg_mbx, vha, 0x1026,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
		vha->hw_err_cnt++;
		वापस rval;
	पूर्ण

	अगर (!IS_FWI2_CAPABLE(ha))
		जाओ करोne;

	ha->fw_ability_mask = mcp->mb[3] << 16 | mcp->mb[2];
	ql_dbg(ql_dbg_mbx, vha, 0x119a,
	    "fw_ability_mask=%x.\n", ha->fw_ability_mask);
	ql_dbg(ql_dbg_mbx, vha, 0x1027, "exchanges=%x.\n", mcp->mb[1]);
	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		ha->max_supported_speed = mcp->mb[2] & (BIT_0|BIT_1);
		ql_dbg(ql_dbg_mbx, vha, 0x119b, "max_supported_speed=%s.\n",
		    ha->max_supported_speed == 0 ? "16Gps" :
		    ha->max_supported_speed == 1 ? "32Gps" :
		    ha->max_supported_speed == 2 ? "64Gps" : "unknown");
		अगर (vha->min_supported_speed) अणु
			ha->min_supported_speed = mcp->mb[5] &
			    (BIT_0 | BIT_1 | BIT_2);
			ql_dbg(ql_dbg_mbx, vha, 0x119c,
			    "min_supported_speed=%s.\n",
			    ha->min_supported_speed == 6 ? "64Gps" :
			    ha->min_supported_speed == 5 ? "32Gps" :
			    ha->min_supported_speed == 4 ? "16Gps" :
			    ha->min_supported_speed == 3 ? "8Gps" :
			    ha->min_supported_speed == 2 ? "4Gps" : "unknown");
		पूर्ण
	पूर्ण

करोne:
	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1028,
	    "Done %s.\n", __func__);

	वापस rval;
पूर्ण

/*
 * qla_get_exlogin_status
 *	Get extended login status
 *	uses the memory offload control/status Mailbox
 *
 * Input:
 *	ha:		adapter state poपूर्णांकer.
 *	fwopt:		firmware options
 *
 * Returns:
 *	qla2x00 local function status
 *
 * Context:
 *	Kernel context.
 */
#घोषणा	FETCH_XLOGINS_STAT	0x8
पूर्णांक
qla_get_exlogin_status(scsi_qla_host_t *vha, uपूर्णांक16_t *buf_sz,
	uपूर्णांक16_t *ex_logins_cnt)
अणु
	पूर्णांक rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x118f,
	    "Entered %s\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_GET_MEM_OFFLOAD_CNTRL_STAT;
	mcp->mb[1] = FETCH_XLOGINS_STAT;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_10|MBX_4|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1115, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		*buf_sz = mcp->mb[4];
		*ex_logins_cnt = mcp->mb[10];

		ql_log(ql_log_info, vha, 0x1190,
		    "buffer size 0x%x, exchange login count=%d\n",
		    mcp->mb[4], mcp->mb[10]);

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1116,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla_set_exlogin_mem_cfg
 *	set extended login memory configuration
 *	Mbx needs to be issues beक्रमe init_cb is set
 *
 * Input:
 *	ha:		adapter state poपूर्णांकer.
 *	buffer:		buffer poपूर्णांकer
 *	phys_addr:	physical address of buffer
 *	size:		size of buffer
 *	TARGET_QUEUE_LOCK must be released
 *	ADAPTER_STATE_LOCK must be release
 *
 * Returns:
 *	qla2x00 local funxtion status code.
 *
 * Context:
 *	Kernel context.
 */
#घोषणा CONFIG_XLOGINS_MEM	0x9
पूर्णांक
qla_set_exlogin_mem_cfg(scsi_qla_host_t *vha, dma_addr_t phys_addr)
अणु
	पूर्णांक		rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x111a,
	    "Entered %s.\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_GET_MEM_OFFLOAD_CNTRL_STAT;
	mcp->mb[1] = CONFIG_XLOGINS_MEM;
	mcp->mb[2] = MSW(phys_addr);
	mcp->mb[3] = LSW(phys_addr);
	mcp->mb[6] = MSW(MSD(phys_addr));
	mcp->mb[7] = LSW(MSD(phys_addr));
	mcp->mb[8] = MSW(ha->exlogin_size);
	mcp->mb[9] = LSW(ha->exlogin_size);
	mcp->out_mb = MBX_9|MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_11|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x111b,
		       "EXlogin Failed=%x. MB0=%x MB11=%x\n",
		       rval, mcp->mb[0], mcp->mb[11]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x118c,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla_get_exchoffld_status
 *	Get exchange offload status
 *	uses the memory offload control/status Mailbox
 *
 * Input:
 *	ha:		adapter state poपूर्णांकer.
 *	fwopt:		firmware options
 *
 * Returns:
 *	qla2x00 local function status
 *
 * Context:
 *	Kernel context.
 */
#घोषणा	FETCH_XCHOFFLD_STAT	0x2
पूर्णांक
qla_get_exchoffld_status(scsi_qla_host_t *vha, uपूर्णांक16_t *buf_sz,
	uपूर्णांक16_t *ex_logins_cnt)
अणु
	पूर्णांक rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1019,
	    "Entered %s\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_GET_MEM_OFFLOAD_CNTRL_STAT;
	mcp->mb[1] = FETCH_XCHOFFLD_STAT;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_10|MBX_4|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1155, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		*buf_sz = mcp->mb[4];
		*ex_logins_cnt = mcp->mb[10];

		ql_log(ql_log_info, vha, 0x118e,
		    "buffer size 0x%x, exchange offload count=%d\n",
		    mcp->mb[4], mcp->mb[10]);

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1156,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla_set_exchoffld_mem_cfg
 *	Set exchange offload memory configuration
 *	Mbx needs to be issues beक्रमe init_cb is set
 *
 * Input:
 *	ha:		adapter state poपूर्णांकer.
 *	buffer:		buffer poपूर्णांकer
 *	phys_addr:	physical address of buffer
 *	size:		size of buffer
 *	TARGET_QUEUE_LOCK must be released
 *	ADAPTER_STATE_LOCK must be release
 *
 * Returns:
 *	qla2x00 local funxtion status code.
 *
 * Context:
 *	Kernel context.
 */
#घोषणा CONFIG_XCHOFFLD_MEM	0x3
पूर्णांक
qla_set_exchoffld_mem_cfg(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1157,
	    "Entered %s.\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_GET_MEM_OFFLOAD_CNTRL_STAT;
	mcp->mb[1] = CONFIG_XCHOFFLD_MEM;
	mcp->mb[2] = MSW(ha->exchoffld_buf_dma);
	mcp->mb[3] = LSW(ha->exchoffld_buf_dma);
	mcp->mb[6] = MSW(MSD(ha->exchoffld_buf_dma));
	mcp->mb[7] = LSW(MSD(ha->exchoffld_buf_dma));
	mcp->mb[8] = MSW(ha->exchoffld_size);
	mcp->mb[9] = LSW(ha->exchoffld_size);
	mcp->out_mb = MBX_9|MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_11|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1158, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1192,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_fw_version
 *	Get firmware version.
 *
 * Input:
 *	ha:		adapter state poपूर्णांकer.
 *	major:		poपूर्णांकer क्रम major number.
 *	minor:		poपूर्णांकer क्रम minor number.
 *	subminor:	poपूर्णांकer क्रम subminor number.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_fw_version(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1029,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_FIRMWARE_VERSION;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA81XX(vha->hw) || IS_QLA8031(ha) || IS_QLA8044(ha))
		mcp->in_mb |= MBX_13|MBX_12|MBX_11|MBX_10|MBX_9|MBX_8;
	अगर (IS_FWI2_CAPABLE(ha))
		mcp->in_mb |= MBX_17|MBX_16|MBX_15;
	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->in_mb |=
		    MBX_25|MBX_24|MBX_23|MBX_22|MBX_21|MBX_20|MBX_19|MBX_18|
		    MBX_14|MBX_13|MBX_11|MBX_10|MBX_9|MBX_8|MBX_7;

	mcp->flags = 0;
	mcp->tov = MBX_TOV_SECONDS;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS)
		जाओ failed;

	/* Return mailbox data. */
	ha->fw_major_version = mcp->mb[1];
	ha->fw_minor_version = mcp->mb[2];
	ha->fw_subminor_version = mcp->mb[3];
	ha->fw_attributes = mcp->mb[6];
	अगर (IS_QLA2100(vha->hw) || IS_QLA2200(vha->hw))
		ha->fw_memory_size = 0x1FFFF;		/* Defaults to 128KB. */
	अन्यथा
		ha->fw_memory_size = (mcp->mb[5] << 16) | mcp->mb[4];

	अगर (IS_QLA81XX(vha->hw) || IS_QLA8031(vha->hw) || IS_QLA8044(ha)) अणु
		ha->mpi_version[0] = mcp->mb[10] & 0xff;
		ha->mpi_version[1] = mcp->mb[11] >> 8;
		ha->mpi_version[2] = mcp->mb[11] & 0xff;
		ha->mpi_capabilities = (mcp->mb[12] << 16) | mcp->mb[13];
		ha->phy_version[0] = mcp->mb[8] & 0xff;
		ha->phy_version[1] = mcp->mb[9] >> 8;
		ha->phy_version[2] = mcp->mb[9] & 0xff;
	पूर्ण

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		ha->fw_attributes_h = mcp->mb[15];
		ha->fw_attributes_ext[0] = mcp->mb[16];
		ha->fw_attributes_ext[1] = mcp->mb[17];
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1139,
		    "%s: FW_attributes Upper: 0x%x, Lower: 0x%x.\n",
		    __func__, mcp->mb[15], mcp->mb[6]);
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x112f,
		    "%s: Ext_FwAttributes Upper: 0x%x, Lower: 0x%x.\n",
		    __func__, mcp->mb[17], mcp->mb[16]);

		अगर (ha->fw_attributes_h & 0x4)
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x118d,
			    "%s: Firmware supports Extended Login 0x%x\n",
			    __func__, ha->fw_attributes_h);

		अगर (ha->fw_attributes_h & 0x8)
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1191,
			    "%s: Firmware supports Exchange Offload 0x%x\n",
			    __func__, ha->fw_attributes_h);

		/*
		 * FW supports nvme and driver load parameter requested nvme.
		 * BIT 26 of fw_attributes indicates NVMe support.
		 */
		अगर ((ha->fw_attributes_h &
		    (FW_ATTR_H_NVME | FW_ATTR_H_NVME_UPDATED)) &&
			ql2xnvmeenable) अणु
			अगर (ha->fw_attributes_h & FW_ATTR_H_NVME_FBURST)
				vha->flags.nvme_first_burst = 1;

			vha->flags.nvme_enabled = 1;
			ql_log(ql_log_info, vha, 0xd302,
			    "%s: FC-NVMe is Enabled (0x%x)\n",
			     __func__, ha->fw_attributes_h);
		पूर्ण

		/* BIT_13 of Extended FW Attributes inक्रमms about NVMe2 support */
		अगर (ha->fw_attributes_ext[0] & FW_ATTR_EXT0_NVME2) अणु
			ql_log(ql_log_info, vha, 0xd302,
			       "Firmware supports NVMe2 0x%x\n",
			       ha->fw_attributes_ext[0]);
			vha->flags.nvme2_enabled = 1;
		पूर्ण
	पूर्ण

	अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		ha->serdes_version[0] = mcp->mb[7] & 0xff;
		ha->serdes_version[1] = mcp->mb[8] >> 8;
		ha->serdes_version[2] = mcp->mb[8] & 0xff;
		ha->mpi_version[0] = mcp->mb[10] & 0xff;
		ha->mpi_version[1] = mcp->mb[11] >> 8;
		ha->mpi_version[2] = mcp->mb[11] & 0xff;
		ha->pep_version[0] = mcp->mb[13] & 0xff;
		ha->pep_version[1] = mcp->mb[14] >> 8;
		ha->pep_version[2] = mcp->mb[14] & 0xff;
		ha->fw_shared_ram_start = (mcp->mb[19] << 16) | mcp->mb[18];
		ha->fw_shared_ram_end = (mcp->mb[21] << 16) | mcp->mb[20];
		ha->fw_ddr_ram_start = (mcp->mb[23] << 16) | mcp->mb[22];
		ha->fw_ddr_ram_end = (mcp->mb[25] << 16) | mcp->mb[24];
		अगर (IS_QLA28XX(ha)) अणु
			अगर (mcp->mb[16] & BIT_10)
				ha->flags.secure_fw = 1;

			ql_log(ql_log_info, vha, 0xffff,
			    "Secure Flash Update in FW: %s\n",
			    (ha->flags.secure_fw) ? "Supported" :
			    "Not Supported");
		पूर्ण

		अगर (ha->flags.scm_supported_a &&
		    (ha->fw_attributes_ext[0] & FW_ATTR_EXT0_SCM_SUPPORTED)) अणु
			ha->flags.scm_supported_f = 1;
			ha->sf_init_cb->flags |= cpu_to_le16(BIT_13);
		पूर्ण
		ql_log(ql_log_info, vha, 0x11a3, "SCM in FW: %s\n",
		       (ha->flags.scm_supported_f) ? "Supported" :
		       "Not Supported");

		अगर (vha->flags.nvme2_enabled) अणु
			/* set BIT_15 of special feature control block क्रम SLER */
			ha->sf_init_cb->flags |= cpu_to_le16(BIT_15);
			/* set BIT_14 of special feature control block क्रम PI CTRL*/
			ha->sf_init_cb->flags |= cpu_to_le16(BIT_14);
		पूर्ण
	पूर्ण

failed:
	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x102a, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x102b,
		    "Done %s.\n", __func__);
	पूर्ण
	वापस rval;
पूर्ण

/*
 * qla2x00_get_fw_options
 *	Set firmware options.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	fwopt = poपूर्णांकer क्रम firmware options.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_fw_options(scsi_qla_host_t *vha, uपूर्णांक16_t *fwopts)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x102c,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_FIRMWARE_OPTION;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x102d, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		fwopts[0] = mcp->mb[0];
		fwopts[1] = mcp->mb[1];
		fwopts[2] = mcp->mb[2];
		fwopts[3] = mcp->mb[3];

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x102e,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण


/*
 * qla2x00_set_fw_options
 *	Set firmware options.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	fwopt = poपूर्णांकer क्रम firmware options.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_set_fw_options(scsi_qla_host_t *vha, uपूर्णांक16_t *fwopts)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x102f,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SET_FIRMWARE_OPTION;
	mcp->mb[1] = fwopts[1];
	mcp->mb[2] = fwopts[2];
	mcp->mb[3] = fwopts[3];
	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(vha->hw)) अणु
		mcp->in_mb |= MBX_1;
		mcp->mb[10] = fwopts[10];
		mcp->out_mb |= MBX_10;
	पूर्ण अन्यथा अणु
		mcp->mb[10] = fwopts[10];
		mcp->mb[11] = fwopts[11];
		mcp->mb[12] = 0;	/* Unकरोcumented, but used */
		mcp->out_mb |= MBX_12|MBX_11|MBX_10;
	पूर्ण
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	fwopts[0] = mcp->mb[0];

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1030,
		    "Failed=%x (%x/%x).\n", rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1031,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_mbx_reg_test
 *	Mailbox रेजिस्टर wrap test.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_mbx_reg_test(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1032,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_MAILBOX_REGISTER_TEST;
	mcp->mb[1] = 0xAAAA;
	mcp->mb[2] = 0x5555;
	mcp->mb[3] = 0xAA55;
	mcp->mb[4] = 0x55AA;
	mcp->mb[5] = 0xA5A5;
	mcp->mb[6] = 0x5A5A;
	mcp->mb[7] = 0x2525;
	mcp->out_mb = MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval == QLA_SUCCESS) अणु
		अगर (mcp->mb[1] != 0xAAAA || mcp->mb[2] != 0x5555 ||
		    mcp->mb[3] != 0xAA55 || mcp->mb[4] != 0x55AA)
			rval = QLA_FUNCTION_FAILED;
		अगर (mcp->mb[5] != 0xA5A5 || mcp->mb[6] != 0x5A5A ||
		    mcp->mb[7] != 0x2525)
			rval = QLA_FUNCTION_FAILED;
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1033, "Failed=%x.\n", rval);
		vha->hw_err_cnt++;
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1034,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_verअगरy_checksum
 *	Verअगरy firmware checksum.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_verअगरy_checksum(scsi_qla_host_t *vha, uपूर्णांक32_t risc_addr)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1035,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_VERIFY_CHECKSUM;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(vha->hw)) अणु
		mcp->mb[1] = MSW(risc_addr);
		mcp->mb[2] = LSW(risc_addr);
		mcp->out_mb |= MBX_2|MBX_1;
		mcp->in_mb |= MBX_2|MBX_1;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = LSW(risc_addr);
		mcp->out_mb |= MBX_1;
		mcp->in_mb |= MBX_1;
	पूर्ण

	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1036,
		    "Failed=%x chm sum=%x.\n", rval, IS_FWI2_CAPABLE(vha->hw) ?
		    (mcp->mb[2] << 16) | mcp->mb[1] : mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1037,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_issue_iocb
 *	Issue IOCB using mailbox command
 *
 * Input:
 *	ha = adapter state poपूर्णांकer.
 *	buffer = buffer poपूर्णांकer.
 *	phys_addr = physical address of buffer.
 *	size = size of buffer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_issue_iocb_समयout(scsi_qla_host_t *vha, व्योम *buffer,
    dma_addr_t phys_addr, माप_प्रकार size, uपूर्णांक32_t tov)
अणु
	पूर्णांक		rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;

	अगर (!vha->hw->flags.fw_started)
		वापस QLA_INVALID_COMMAND;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1038,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_IOCB_COMMAND_A64;
	mcp->mb[1] = 0;
	mcp->mb[2] = MSW(LSD(phys_addr));
	mcp->mb[3] = LSW(LSD(phys_addr));
	mcp->mb[6] = MSW(MSD(phys_addr));
	mcp->mb[7] = LSW(MSD(phys_addr));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = tov;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1039, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		sts_entry_t *sts_entry = buffer;

		/* Mask reserved bits. */
		sts_entry->entry_status &=
		    IS_FWI2_CAPABLE(vha->hw) ? RF_MASK_24XX : RF_MASK;
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x103a,
		    "Done %s (status=%x).\n", __func__,
		    sts_entry->entry_status);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_issue_iocb(scsi_qla_host_t *vha, व्योम *buffer, dma_addr_t phys_addr,
    माप_प्रकार size)
अणु
	वापस qla2x00_issue_iocb_समयout(vha, buffer, phys_addr, size,
	    MBX_TOV_SECONDS);
पूर्ण

/*
 * qla2x00_पात_command
 *	Abort command पातs a specअगरied IOCB.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	sp = SB काष्ठाure poपूर्णांकer.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_पात_command(srb_t *sp)
अणु
	अचिन्हित दीर्घ   flags = 0;
	पूर्णांक		rval;
	uपूर्णांक32_t	handle = 0;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;
	fc_port_t	*fcport = sp->fcport;
	scsi_qla_host_t *vha = fcport->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;
	काष्ठा scsi_cmnd *cmd = GET_CMD_SP(sp);

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x103b,
	    "Entered %s.\n", __func__);

	अगर (sp->qpair)
		req = sp->qpair->req;
	अन्यथा
		req = vha->req;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (handle = 1; handle < req->num_outstanding_cmds; handle++) अणु
		अगर (req->outstanding_cmds[handle] == sp)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	अगर (handle == req->num_outstanding_cmds) अणु
		/* command not found */
		वापस QLA_FUNCTION_FAILED;
	पूर्ण

	mcp->mb[0] = MBC_ABORT_COMMAND;
	अगर (HAS_EXTENDED_IDS(ha))
		mcp->mb[1] = fcport->loop_id;
	अन्यथा
		mcp->mb[1] = fcport->loop_id << 8;
	mcp->mb[2] = (uपूर्णांक16_t)handle;
	mcp->mb[3] = (uपूर्णांक16_t)(handle >> 16);
	mcp->mb[6] = (uपूर्णांक16_t)cmd->device->lun;
	mcp->out_mb = MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x103c, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x103d,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_पात_target(काष्ठा fc_port *fcport, uपूर्णांक64_t l, पूर्णांक tag)
अणु
	पूर्णांक rval, rval2;
	mbx_cmd_t  mc;
	mbx_cmd_t  *mcp = &mc;
	scsi_qla_host_t *vha;

	vha = fcport->vha;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x103e,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_ABORT_TARGET;
	mcp->out_mb = MBX_9|MBX_2|MBX_1|MBX_0;
	अगर (HAS_EXTENDED_IDS(vha->hw)) अणु
		mcp->mb[1] = fcport->loop_id;
		mcp->mb[10] = 0;
		mcp->out_mb |= MBX_10;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = fcport->loop_id << 8;
	पूर्ण
	mcp->mb[2] = vha->hw->loop_reset_delay;
	mcp->mb[9] = vha->vp_idx;

	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x103f,
		    "Failed=%x.\n", rval);
	पूर्ण

	/* Issue marker IOCB. */
	rval2 = qla2x00_marker(vha, vha->hw->base_qpair, fcport->loop_id, 0,
							MK_SYNC_ID);
	अगर (rval2 != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1040,
		    "Failed to issue marker IOCB (%x).\n", rval2);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1041,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_lun_reset(काष्ठा fc_port *fcport, uपूर्णांक64_t l, पूर्णांक tag)
अणु
	पूर्णांक rval, rval2;
	mbx_cmd_t  mc;
	mbx_cmd_t  *mcp = &mc;
	scsi_qla_host_t *vha;

	vha = fcport->vha;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1042,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_LUN_RESET;
	mcp->out_mb = MBX_9|MBX_3|MBX_2|MBX_1|MBX_0;
	अगर (HAS_EXTENDED_IDS(vha->hw))
		mcp->mb[1] = fcport->loop_id;
	अन्यथा
		mcp->mb[1] = fcport->loop_id << 8;
	mcp->mb[2] = (u32)l;
	mcp->mb[3] = 0;
	mcp->mb[9] = vha->vp_idx;

	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1043, "Failed=%x.\n", rval);
	पूर्ण

	/* Issue marker IOCB. */
	rval2 = qla2x00_marker(vha, vha->hw->base_qpair, fcport->loop_id, l,
								MK_SYNC_ID_LUN);
	अगर (rval2 != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1044,
		    "Failed to issue marker IOCB (%x).\n", rval2);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1045,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_adapter_id
 *	Get adapter ID and topology.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	id = poपूर्णांकer क्रम loop ID.
 *	al_pa = poपूर्णांकer क्रम AL_PA.
 *	area = poपूर्णांकer क्रम area.
 *	करोमुख्य = poपूर्णांकer क्रम करोमुख्य.
 *	top = poपूर्णांकer क्रम topology.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_adapter_id(scsi_qla_host_t *vha, uपूर्णांक16_t *id, uपूर्णांक8_t *al_pa,
    uपूर्णांक8_t *area, uपूर्णांक8_t *करोमुख्य, uपूर्णांक16_t *top, uपूर्णांक16_t *sw_cap)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1046,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_ADAPTER_LOOP_ID;
	mcp->mb[9] = vha->vp_idx;
	mcp->out_mb = MBX_9|MBX_0;
	mcp->in_mb = MBX_9|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	अगर (IS_CNA_CAPABLE(vha->hw))
		mcp->in_mb |= MBX_13|MBX_12|MBX_11|MBX_10;
	अगर (IS_FWI2_CAPABLE(vha->hw))
		mcp->in_mb |= MBX_19|MBX_18|MBX_17|MBX_16;
	अगर (IS_QLA27XX(vha->hw) || IS_QLA28XX(vha->hw)) अणु
		mcp->in_mb |= MBX_15;
		mcp->out_mb |= MBX_7|MBX_21|MBX_22|MBX_23;
	पूर्ण

	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (mcp->mb[0] == MBS_COMMAND_ERROR)
		rval = QLA_COMMAND_ERROR;
	अन्यथा अगर (mcp->mb[0] == MBS_INVALID_COMMAND)
		rval = QLA_INVALID_COMMAND;

	/* Return data. */
	*id = mcp->mb[1];
	*al_pa = LSB(mcp->mb[2]);
	*area = MSB(mcp->mb[2]);
	*करोमुख्य	= LSB(mcp->mb[3]);
	*top = mcp->mb[6];
	*sw_cap = mcp->mb[7];

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1047, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1048,
		    "Done %s.\n", __func__);

		अगर (IS_CNA_CAPABLE(vha->hw)) अणु
			vha->fcoe_vlan_id = mcp->mb[9] & 0xfff;
			vha->fcoe_fcf_idx = mcp->mb[10];
			vha->fcoe_vn_port_mac[5] = mcp->mb[11] >> 8;
			vha->fcoe_vn_port_mac[4] = mcp->mb[11] & 0xff;
			vha->fcoe_vn_port_mac[3] = mcp->mb[12] >> 8;
			vha->fcoe_vn_port_mac[2] = mcp->mb[12] & 0xff;
			vha->fcoe_vn_port_mac[1] = mcp->mb[13] >> 8;
			vha->fcoe_vn_port_mac[0] = mcp->mb[13] & 0xff;
		पूर्ण
		/* If FA-WWN supported */
		अगर (IS_FAWWN_CAPABLE(vha->hw)) अणु
			अगर (mcp->mb[7] & BIT_14) अणु
				vha->port_name[0] = MSB(mcp->mb[16]);
				vha->port_name[1] = LSB(mcp->mb[16]);
				vha->port_name[2] = MSB(mcp->mb[17]);
				vha->port_name[3] = LSB(mcp->mb[17]);
				vha->port_name[4] = MSB(mcp->mb[18]);
				vha->port_name[5] = LSB(mcp->mb[18]);
				vha->port_name[6] = MSB(mcp->mb[19]);
				vha->port_name[7] = LSB(mcp->mb[19]);
				fc_host_port_name(vha->host) =
				    wwn_to_u64(vha->port_name);
				ql_dbg(ql_dbg_mbx, vha, 0x10ca,
				    "FA-WWN acquired %016llx\n",
				    wwn_to_u64(vha->port_name));
			पूर्ण
		पूर्ण

		अगर (IS_QLA27XX(vha->hw) || IS_QLA28XX(vha->hw)) अणु
			vha->bbcr = mcp->mb[15];
			अगर (mcp->mb[7] & SCM_EDC_ACC_RECEIVED) अणु
				ql_log(ql_log_info, vha, 0x11a4,
				       "SCM: EDC ELS completed, flags 0x%x\n",
				       mcp->mb[21]);
			पूर्ण
			अगर (mcp->mb[7] & SCM_RDF_ACC_RECEIVED) अणु
				vha->hw->flags.scm_enabled = 1;
				vha->scm_fabric_connection_flags |=
				    SCM_FLAG_RDF_COMPLETED;
				ql_log(ql_log_info, vha, 0x11a5,
				       "SCM: RDF ELS completed, flags 0x%x\n",
				       mcp->mb[23]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_retry_cnt
 *	Get current firmware login retry count and delay.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	retry_cnt = poपूर्णांकer to login retry count.
 *	tov = poपूर्णांकer to login समयout value.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_retry_cnt(scsi_qla_host_t *vha, uपूर्णांक8_t *retry_cnt, uपूर्णांक8_t *tov,
    uपूर्णांक16_t *r_a_tov)
अणु
	पूर्णांक rval;
	uपूर्णांक16_t ratov;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1049,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_RETRY_COUNT;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x104a,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		/* Convert वापसed data and check our values. */
		*r_a_tov = mcp->mb[3] / 2;
		ratov = (mcp->mb[3]/2) / 10;  /* mb[3] value is in 100ms */
		अगर (mcp->mb[1] * ratov > (*retry_cnt) * (*tov)) अणु
			/* Update to the larger values */
			*retry_cnt = (uपूर्णांक8_t)mcp->mb[1];
			*tov = ratov;
		पूर्ण

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x104b,
		    "Done %s mb3=%d ratov=%d.\n", __func__, mcp->mb[3], ratov);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_init_firmware
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
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_init_firmware(scsi_qla_host_t *vha, uपूर्णांक16_t size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x104c,
	    "Entered %s.\n", __func__);

	अगर (IS_P3P_TYPE(ha) && ql2xdbwr)
		qla82xx_wr_32(ha, (uपूर्णांकptr_t __क्रमce)ha->nxdb_wr_ptr,
			(0x04 | (ha->portnum << 5) | (0 << 8) | (0 << 16)));

	अगर (ha->flags.npiv_supported)
		mcp->mb[0] = MBC_MID_INITIALIZE_FIRMWARE;
	अन्यथा
		mcp->mb[0] = MBC_INITIALIZE_FIRMWARE;

	mcp->mb[1] = 0;
	mcp->mb[2] = MSW(ha->init_cb_dma);
	mcp->mb[3] = LSW(ha->init_cb_dma);
	mcp->mb[6] = MSW(MSD(ha->init_cb_dma));
	mcp->mb[7] = LSW(MSD(ha->init_cb_dma));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	अगर (ha->ex_init_cb && ha->ex_init_cb->ex_version) अणु
		mcp->mb[1] = BIT_0;
		mcp->mb[10] = MSW(ha->ex_init_cb_dma);
		mcp->mb[11] = LSW(ha->ex_init_cb_dma);
		mcp->mb[12] = MSW(MSD(ha->ex_init_cb_dma));
		mcp->mb[13] = LSW(MSD(ha->ex_init_cb_dma));
		mcp->mb[14] = माप(*ha->ex_init_cb);
		mcp->out_mb |= MBX_14|MBX_13|MBX_12|MBX_11|MBX_10;
	पूर्ण

	अगर (ha->flags.scm_supported_f || vha->flags.nvme2_enabled) अणु
		mcp->mb[1] |= BIT_1;
		mcp->mb[16] = MSW(ha->sf_init_cb_dma);
		mcp->mb[17] = LSW(ha->sf_init_cb_dma);
		mcp->mb[18] = MSW(MSD(ha->sf_init_cb_dma));
		mcp->mb[19] = LSW(MSD(ha->sf_init_cb_dma));
		mcp->mb[15] = माप(*ha->sf_init_cb);
		mcp->out_mb |= MBX_19|MBX_18|MBX_17|MBX_16|MBX_15;
	पूर्ण

	/* 1 and 2 should normally be captured. */
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		/* mb3 is additional info about the installed SFP. */
		mcp->in_mb  |= MBX_3;
	mcp->buf_size = size;
	mcp->flags = MBX_DMA_OUT;
	mcp->tov = MBX_TOV_SECONDS;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x104d,
		    "Failed=%x mb[0]=%x, mb[1]=%x, mb[2]=%x, mb[3]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2], mcp->mb[3]);
		अगर (ha->init_cb) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x104d, "init_cb:\n");
			ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha,
			    0x0104d, ha->init_cb, माप(*ha->init_cb));
		पूर्ण
		अगर (ha->ex_init_cb && ha->ex_init_cb->ex_version) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x104d, "ex_init_cb:\n");
			ql_dump_buffer(ql_dbg_init + ql_dbg_verbose, vha,
			    0x0104d, ha->ex_init_cb, माप(*ha->ex_init_cb));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			अगर (mcp->mb[2] == 6 || mcp->mb[3] == 2)
				ql_dbg(ql_dbg_mbx, vha, 0x119d,
				    "Invalid SFP/Validation Failed\n");
		पूर्ण
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x104e,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण


/*
 * qla2x00_get_port_database
 *	Issue normal/enhanced get port database mailbox command
 *	and copy device name as necessary.
 *
 * Input:
 *	ha = adapter state poपूर्णांकer.
 *	dev = काष्ठाure poपूर्णांकer.
 *	opt = enhanced cmd option byte.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_port_database(scsi_qla_host_t *vha, fc_port_t *fcport, uपूर्णांक8_t opt)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	port_database_t *pd;
	काष्ठा port_database_24xx *pd24;
	dma_addr_t pd_dma;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x104f,
	    "Entered %s.\n", __func__);

	pd24 = शून्य;
	pd = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &pd_dma);
	अगर (pd  == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x1050,
		    "Failed to allocate port database structure.\n");
		fcport->query = 0;
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	mcp->mb[0] = MBC_GET_PORT_DATABASE;
	अगर (opt != 0 && !IS_FWI2_CAPABLE(ha))
		mcp->mb[0] = MBC_ENHANCED_GET_PORT_DATABASE;
	mcp->mb[2] = MSW(pd_dma);
	mcp->mb[3] = LSW(pd_dma);
	mcp->mb[6] = MSW(MSD(pd_dma));
	mcp->mb[7] = LSW(MSD(pd_dma));
	mcp->mb[9] = vha->vp_idx;
	mcp->out_mb = MBX_9|MBX_7|MBX_6|MBX_3|MBX_2|MBX_0;
	mcp->in_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		mcp->mb[1] = fcport->loop_id;
		mcp->mb[10] = opt;
		mcp->out_mb |= MBX_10|MBX_1;
		mcp->in_mb |= MBX_1;
	पूर्ण अन्यथा अगर (HAS_EXTENDED_IDS(ha)) अणु
		mcp->mb[1] = fcport->loop_id;
		mcp->mb[10] = opt;
		mcp->out_mb |= MBX_10|MBX_1;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = fcport->loop_id << 8 | opt;
		mcp->out_mb |= MBX_1;
	पूर्ण
	mcp->buf_size = IS_FWI2_CAPABLE(ha) ?
	    PORT_DATABASE_24XX_SIZE : PORT_DATABASE_SIZE;
	mcp->flags = MBX_DMA_IN;
	mcp->tov = (ha->login_समयout * 2) + (ha->login_समयout / 2);
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS)
		जाओ gpd_error_out;

	अगर (IS_FWI2_CAPABLE(ha)) अणु
		uपूर्णांक64_t zero = 0;
		u8 current_login_state, last_login_state;

		pd24 = (काष्ठा port_database_24xx *) pd;

		/* Check क्रम logged in state. */
		अगर (NVME_TARGET(ha, fcport)) अणु
			current_login_state = pd24->current_login_state >> 4;
			last_login_state = pd24->last_login_state >> 4;
		पूर्ण अन्यथा अणु
			current_login_state = pd24->current_login_state & 0xf;
			last_login_state = pd24->last_login_state & 0xf;
		पूर्ण
		fcport->current_login_state = pd24->current_login_state;
		fcport->last_login_state = pd24->last_login_state;

		/* Check क्रम logged in state. */
		अगर (current_login_state != PDS_PRLI_COMPLETE &&
		    last_login_state != PDS_PRLI_COMPLETE) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x119a,
			    "Unable to verify login-state (%x/%x) for loop_id %x.\n",
			    current_login_state, last_login_state,
			    fcport->loop_id);
			rval = QLA_FUNCTION_FAILED;

			अगर (!fcport->query)
				जाओ gpd_error_out;
		पूर्ण

		अगर (fcport->loop_id == FC_NO_LOOP_ID ||
		    (स_भेद(fcport->port_name, (uपूर्णांक8_t *)&zero, 8) &&
		     स_भेद(fcport->port_name, pd24->port_name, 8))) अणु
			/* We lost the device mid way. */
			rval = QLA_NOT_LOGGED_IN;
			जाओ gpd_error_out;
		पूर्ण

		/* Names are little-endian. */
		स_नकल(fcport->node_name, pd24->node_name, WWN_SIZE);
		स_नकल(fcport->port_name, pd24->port_name, WWN_SIZE);

		/* Get port_id of device. */
		fcport->d_id.b.करोमुख्य = pd24->port_id[0];
		fcport->d_id.b.area = pd24->port_id[1];
		fcport->d_id.b.al_pa = pd24->port_id[2];
		fcport->d_id.b.rsvd_1 = 0;

		/* If not target must be initiator or unknown type. */
		अगर ((pd24->prli_svc_param_word_3[0] & BIT_4) == 0)
			fcport->port_type = FCT_INITIATOR;
		अन्यथा
			fcport->port_type = FCT_TARGET;

		/* Passback COS inक्रमmation. */
		fcport->supported_classes = (pd24->flags & PDF_CLASS_2) ?
				FC_COS_CLASS2 : FC_COS_CLASS3;

		अगर (pd24->prli_svc_param_word_3[0] & BIT_7)
			fcport->flags |= FCF_CONF_COMP_SUPPORTED;
	पूर्ण अन्यथा अणु
		uपूर्णांक64_t zero = 0;

		/* Check क्रम logged in state. */
		अगर (pd->master_state != PD_STATE_PORT_LOGGED_IN &&
		    pd->slave_state != PD_STATE_PORT_LOGGED_IN) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x100a,
			    "Unable to verify login-state (%x/%x) - "
			    "portid=%02x%02x%02x.\n", pd->master_state,
			    pd->slave_state, fcport->d_id.b.करोमुख्य,
			    fcport->d_id.b.area, fcport->d_id.b.al_pa);
			rval = QLA_FUNCTION_FAILED;
			जाओ gpd_error_out;
		पूर्ण

		अगर (fcport->loop_id == FC_NO_LOOP_ID ||
		    (स_भेद(fcport->port_name, (uपूर्णांक8_t *)&zero, 8) &&
		     स_भेद(fcport->port_name, pd->port_name, 8))) अणु
			/* We lost the device mid way. */
			rval = QLA_NOT_LOGGED_IN;
			जाओ gpd_error_out;
		पूर्ण

		/* Names are little-endian. */
		स_नकल(fcport->node_name, pd->node_name, WWN_SIZE);
		स_नकल(fcport->port_name, pd->port_name, WWN_SIZE);

		/* Get port_id of device. */
		fcport->d_id.b.करोमुख्य = pd->port_id[0];
		fcport->d_id.b.area = pd->port_id[3];
		fcport->d_id.b.al_pa = pd->port_id[2];
		fcport->d_id.b.rsvd_1 = 0;

		/* If not target must be initiator or unknown type. */
		अगर ((pd->prli_svc_param_word_3[0] & BIT_4) == 0)
			fcport->port_type = FCT_INITIATOR;
		अन्यथा
			fcport->port_type = FCT_TARGET;

		/* Passback COS inक्रमmation. */
		fcport->supported_classes = (pd->options & BIT_4) ?
		    FC_COS_CLASS2 : FC_COS_CLASS3;
	पूर्ण

gpd_error_out:
	dma_pool_मुक्त(ha->s_dma_pool, pd, pd_dma);
	fcport->query = 0;

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1052,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n", rval,
		    mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1053,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_get_port_database(scsi_qla_host_t *vha, u16 nport_handle,
	काष्ठा port_database_24xx *pdb)
अणु
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	dma_addr_t pdb_dma;
	पूर्णांक rval;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1115,
	    "Entered %s.\n", __func__);

	स_रखो(pdb, 0, माप(*pdb));

	pdb_dma = dma_map_single(&vha->hw->pdev->dev, pdb,
	    माप(*pdb), DMA_FROM_DEVICE);
	अगर (!pdb_dma) अणु
		ql_log(ql_log_warn, vha, 0x1116, "Failed to map dma buffer.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	mcp->mb[0] = MBC_GET_PORT_DATABASE;
	mcp->mb[1] = nport_handle;
	mcp->mb[2] = MSW(LSD(pdb_dma));
	mcp->mb[3] = LSW(LSD(pdb_dma));
	mcp->mb[6] = MSW(MSD(pdb_dma));
	mcp->mb[7] = LSW(MSD(pdb_dma));
	mcp->mb[9] = 0;
	mcp->mb[10] = 0;
	mcp->out_mb = MBX_10|MBX_9|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->buf_size = माप(*pdb);
	mcp->flags = MBX_DMA_IN;
	mcp->tov = vha->hw->login_समयout * 2;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x111a,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x111b,
		    "Done %s.\n", __func__);
	पूर्ण

	dma_unmap_single(&vha->hw->pdev->dev, pdb_dma,
	    माप(*pdb), DMA_FROM_DEVICE);

	वापस rval;
पूर्ण

/*
 * qla2x00_get_firmware_state
 *	Get adapter firmware state.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	dptr = poपूर्णांकer क्रम firmware state.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_firmware_state(scsi_qla_host_t *vha, uपूर्णांक16_t *states)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1054,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_FIRMWARE_STATE;
	mcp->out_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(vha->hw))
		mcp->in_mb = MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	अन्यथा
		mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	/* Return firmware states. */
	states[0] = mcp->mb[1];
	अगर (IS_FWI2_CAPABLE(vha->hw)) अणु
		states[1] = mcp->mb[2];
		states[2] = mcp->mb[3];  /* SFP info */
		states[3] = mcp->mb[4];
		states[4] = mcp->mb[5];
		states[5] = mcp->mb[6];  /* DPORT status */
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1055, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		अगर (IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			अगर (mcp->mb[2] == 6 || mcp->mb[3] == 2)
				ql_dbg(ql_dbg_mbx, vha, 0x119e,
				    "Invalid SFP/Validation Failed\n");
		पूर्ण
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1056,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_port_name
 *	Issue get port name mailbox command.
 *	Returned name is in big endian क्रमmat.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	loop_id = loop ID of device.
 *	name = poपूर्णांकer क्रम name.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_port_name(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id, uपूर्णांक8_t *name,
    uपूर्णांक8_t opt)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1057,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_PORT_NAME;
	mcp->mb[9] = vha->vp_idx;
	mcp->out_mb = MBX_9|MBX_1|MBX_0;
	अगर (HAS_EXTENDED_IDS(vha->hw)) अणु
		mcp->mb[1] = loop_id;
		mcp->mb[10] = opt;
		mcp->out_mb |= MBX_10;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = loop_id << 8 | opt;
	पूर्ण

	mcp->in_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1058, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		अगर (name != शून्य) अणु
			/* This function वापसs name in big endian. */
			name[0] = MSB(mcp->mb[2]);
			name[1] = LSB(mcp->mb[2]);
			name[2] = MSB(mcp->mb[3]);
			name[3] = LSB(mcp->mb[3]);
			name[4] = MSB(mcp->mb[6]);
			name[5] = LSB(mcp->mb[6]);
			name[6] = MSB(mcp->mb[7]);
			name[7] = LSB(mcp->mb[7]);
		पूर्ण

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1059,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla24xx_link_initialization
 *	Issue link initialization mailbox command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla24xx_link_initialize(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1152,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(vha->hw) || IS_CNA_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_LINK_INITIALIZATION;
	mcp->mb[1] = BIT_4;
	अगर (vha->hw->operating_mode == LOOP)
		mcp->mb[1] |= BIT_6;
	अन्यथा
		mcp->mb[1] |= BIT_5;
	mcp->mb[2] = 0;
	mcp->mb[3] = 0;
	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1153, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1154,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_lip_reset
 *	Issue LIP reset mailbox command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_lip_reset(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_disc, vha, 0x105a,
	    "Entered %s.\n", __func__);

	अगर (IS_CNA_CAPABLE(vha->hw)) अणु
		/* Logout across all FCFs. */
		mcp->mb[0] = MBC_LIP_FULL_LOGIN;
		mcp->mb[1] = BIT_1;
		mcp->mb[2] = 0;
		mcp->out_mb = MBX_2|MBX_1|MBX_0;
	पूर्ण अन्यथा अगर (IS_FWI2_CAPABLE(vha->hw)) अणु
		mcp->mb[0] = MBC_LIP_FULL_LOGIN;
		mcp->mb[1] = BIT_4;
		mcp->mb[2] = 0;
		mcp->mb[3] = vha->hw->loop_reset_delay;
		mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	पूर्ण अन्यथा अणु
		mcp->mb[0] = MBC_LIP_RESET;
		mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
		अगर (HAS_EXTENDED_IDS(vha->hw)) अणु
			mcp->mb[1] = 0x00ff;
			mcp->mb[10] = 0;
			mcp->out_mb |= MBX_10;
		पूर्ण अन्यथा अणु
			mcp->mb[1] = 0xff00;
		पूर्ण
		mcp->mb[2] = vha->hw->loop_reset_delay;
		mcp->mb[3] = 0;
	पूर्ण
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x105b, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x105c,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_send_sns
 *	Send SNS command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	sns = poपूर्णांकer क्रम command.
 *	cmd_size = command size.
 *	buf_size = response/command size.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_send_sns(scsi_qla_host_t *vha, dma_addr_t sns_phys_address,
    uपूर्णांक16_t cmd_size, माप_प्रकार buf_size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x105d,
	    "Entered %s.\n", __func__);

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x105e,
	    "Retry cnt=%d ratov=%d total tov=%d.\n",
	    vha->hw->retry_count, vha->hw->login_समयout, mcp->tov);

	mcp->mb[0] = MBC_SEND_SNS_COMMAND;
	mcp->mb[1] = cmd_size;
	mcp->mb[2] = MSW(sns_phys_address);
	mcp->mb[3] = LSW(sns_phys_address);
	mcp->mb[6] = MSW(MSD(sns_phys_address));
	mcp->mb[7] = LSW(MSD(sns_phys_address));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0|MBX_1;
	mcp->buf_size = buf_size;
	mcp->flags = MBX_DMA_OUT|MBX_DMA_IN;
	mcp->tov = (vha->hw->login_समयout * 2) + (vha->hw->login_समयout / 2);
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x105f,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1060,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_login_fabric(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id, uपूर्णांक8_t करोमुख्य,
    uपूर्णांक8_t area, uपूर्णांक8_t al_pa, uपूर्णांक16_t *mb, uपूर्णांक8_t opt)
अणु
	पूर्णांक		rval;

	काष्ठा logio_entry_24xx *lg;
	dma_addr_t	lg_dma;
	uपूर्णांक32_t	iop[2];
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1061,
	    "Entered %s.\n", __func__);

	अगर (vha->vp_idx && vha->qpair)
		req = vha->qpair->req;
	अन्यथा
		req = ha->req_q_map[0];

	lg = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &lg_dma);
	अगर (lg == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x1062,
		    "Failed to allocate login IOCB.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	lg->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	lg->entry_count = 1;
	lg->handle = make_handle(req->id, lg->handle);
	lg->nport_handle = cpu_to_le16(loop_id);
	lg->control_flags = cpu_to_le16(LCF_COMMAND_PLOGI);
	अगर (opt & BIT_0)
		lg->control_flags |= cpu_to_le16(LCF_COND_PLOGI);
	अगर (opt & BIT_1)
		lg->control_flags |= cpu_to_le16(LCF_SKIP_PRLI);
	lg->port_id[0] = al_pa;
	lg->port_id[1] = area;
	lg->port_id[2] = करोमुख्य;
	lg->vp_index = vha->vp_idx;
	rval = qla2x00_issue_iocb_समयout(vha, lg, lg_dma, 0,
	    (ha->r_a_tov / 10 * 2) + 2);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1063,
		    "Failed to issue login IOCB (%x).\n", rval);
	पूर्ण अन्यथा अगर (lg->entry_status != 0) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1064,
		    "Failed to complete IOCB -- error status (%x).\n",
		    lg->entry_status);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (lg->comp_status != cpu_to_le16(CS_COMPLETE)) अणु
		iop[0] = le32_to_cpu(lg->io_parameter[0]);
		iop[1] = le32_to_cpu(lg->io_parameter[1]);

		ql_dbg(ql_dbg_mbx, vha, 0x1065,
		    "Failed to complete IOCB -- completion  status (%x) "
		    "ioparam=%x/%x.\n", le16_to_cpu(lg->comp_status),
		    iop[0], iop[1]);

		चयन (iop[0]) अणु
		हाल LSC_SCODE_PORTID_USED:
			mb[0] = MBS_PORT_ID_USED;
			mb[1] = LSW(iop[1]);
			अवरोध;
		हाल LSC_SCODE_NPORT_USED:
			mb[0] = MBS_LOOP_ID_USED;
			अवरोध;
		हाल LSC_SCODE_NOLINK:
		हाल LSC_SCODE_NOIOCB:
		हाल LSC_SCODE_NOXCB:
		हाल LSC_SCODE_CMD_FAILED:
		हाल LSC_SCODE_NOFABRIC:
		हाल LSC_SCODE_FW_NOT_READY:
		हाल LSC_SCODE_NOT_LOGGED_IN:
		हाल LSC_SCODE_NOPCB:
		हाल LSC_SCODE_ELS_REJECT:
		हाल LSC_SCODE_CMD_PARAM_ERR:
		हाल LSC_SCODE_NONPORT:
		हाल LSC_SCODE_LOGGED_IN:
		हाल LSC_SCODE_NOFLOGI_ACC:
		शेष:
			mb[0] = MBS_COMMAND_ERROR;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1066,
		    "Done %s.\n", __func__);

		iop[0] = le32_to_cpu(lg->io_parameter[0]);

		mb[0] = MBS_COMMAND_COMPLETE;
		mb[1] = 0;
		अगर (iop[0] & BIT_4) अणु
			अगर (iop[0] & BIT_8)
				mb[1] |= BIT_1;
		पूर्ण अन्यथा
			mb[1] = BIT_0;

		/* Passback COS inक्रमmation. */
		mb[10] = 0;
		अगर (lg->io_parameter[7] || lg->io_parameter[8])
			mb[10] |= BIT_0;	/* Class 2. */
		अगर (lg->io_parameter[9] || lg->io_parameter[10])
			mb[10] |= BIT_1;	/* Class 3. */
		अगर (lg->io_parameter[0] & cpu_to_le32(BIT_7))
			mb[10] |= BIT_7;	/* Confirmed Completion
						 * Allowed
						 */
	पूर्ण

	dma_pool_मुक्त(ha->s_dma_pool, lg, lg_dma);

	वापस rval;
पूर्ण

/*
 * qla2x00_login_fabric
 *	Issue login fabric port mailbox command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	loop_id = device loop ID.
 *	करोमुख्य = device करोमुख्य.
 *	area = device area.
 *	al_pa = device AL_PA.
 *	status = poपूर्णांकer क्रम वापस status.
 *	opt = command options.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_login_fabric(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id, uपूर्णांक8_t करोमुख्य,
    uपूर्णांक8_t area, uपूर्णांक8_t al_pa, uपूर्णांक16_t *mb, uपूर्णांक8_t opt)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1067,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_LOGIN_FABRIC_PORT;
	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	अगर (HAS_EXTENDED_IDS(ha)) अणु
		mcp->mb[1] = loop_id;
		mcp->mb[10] = opt;
		mcp->out_mb |= MBX_10;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = (loop_id << 8) | opt;
	पूर्ण
	mcp->mb[2] = करोमुख्य;
	mcp->mb[3] = area << 8 | al_pa;

	mcp->in_mb = MBX_7|MBX_6|MBX_2|MBX_1|MBX_0;
	mcp->tov = (ha->login_समयout * 2) + (ha->login_समयout / 2);
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	/* Return mailbox statuses. */
	अगर (mb != शून्य) अणु
		mb[0] = mcp->mb[0];
		mb[1] = mcp->mb[1];
		mb[2] = mcp->mb[2];
		mb[6] = mcp->mb[6];
		mb[7] = mcp->mb[7];
		/* COS retrieved from Get-Port-Database mailbox command. */
		mb[10] = 0;
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		/* RLU पंचांगp code: need to change मुख्य mailbox_command function to
		 * वापस ok even when the mailbox completion value is not
		 * SUCCESS. The caller needs to be responsible to पूर्णांकerpret
		 * the वापस values of this mailbox command अगर we're not
		 * to change too much of the existing code.
		 */
		अगर (mcp->mb[0] == 0x4001 || mcp->mb[0] == 0x4002 ||
		    mcp->mb[0] == 0x4003 || mcp->mb[0] == 0x4005 ||
		    mcp->mb[0] == 0x4006)
			rval = QLA_SUCCESS;

		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1068,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1069,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_login_local_device
 *           Issue login loop port mailbox command.
 *
 * Input:
 *           ha = adapter block poपूर्णांकer.
 *           loop_id = device loop ID.
 *           opt = command options.
 *
 * Returns:
 *            Return status code.
 *
 * Context:
 *            Kernel context.
 *
 */
पूर्णांक
qla2x00_login_local_device(scsi_qla_host_t *vha, fc_port_t *fcport,
    uपूर्णांक16_t *mb_ret, uपूर्णांक8_t opt)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x106a,
	    "Entered %s.\n", __func__);

	अगर (IS_FWI2_CAPABLE(ha))
		वापस qla24xx_login_fabric(vha, fcport->loop_id,
		    fcport->d_id.b.करोमुख्य, fcport->d_id.b.area,
		    fcport->d_id.b.al_pa, mb_ret, opt);

	mcp->mb[0] = MBC_LOGIN_LOOP_PORT;
	अगर (HAS_EXTENDED_IDS(ha))
		mcp->mb[1] = fcport->loop_id;
	अन्यथा
		mcp->mb[1] = fcport->loop_id << 8;
	mcp->mb[2] = opt;
	mcp->out_mb = MBX_2|MBX_1|MBX_0;
 	mcp->in_mb = MBX_7|MBX_6|MBX_1|MBX_0;
	mcp->tov = (ha->login_समयout * 2) + (ha->login_समयout / 2);
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

 	/* Return mailbox statuses. */
 	अगर (mb_ret != शून्य) अणु
 		mb_ret[0] = mcp->mb[0];
 		mb_ret[1] = mcp->mb[1];
 		mb_ret[6] = mcp->mb[6];
 		mb_ret[7] = mcp->mb[7];
 	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
 		/* AV पंचांगp code: need to change मुख्य mailbox_command function to
 		 * वापस ok even when the mailbox completion value is not
 		 * SUCCESS. The caller needs to be responsible to पूर्णांकerpret
 		 * the वापस values of this mailbox command अगर we're not
 		 * to change too much of the existing code.
 		 */
 		अगर (mcp->mb[0] == 0x4005 || mcp->mb[0] == 0x4006)
 			rval = QLA_SUCCESS;

		ql_dbg(ql_dbg_mbx, vha, 0x106b,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[6]=%x mb[7]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[6], mcp->mb[7]);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x106c,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस (rval);
पूर्ण

पूर्णांक
qla24xx_fabric_logout(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id, uपूर्णांक8_t करोमुख्य,
    uपूर्णांक8_t area, uपूर्णांक8_t al_pa)
अणु
	पूर्णांक		rval;
	काष्ठा logio_entry_24xx *lg;
	dma_addr_t	lg_dma;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x106d,
	    "Entered %s.\n", __func__);

	lg = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &lg_dma);
	अगर (lg == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x106e,
		    "Failed to allocate logout IOCB.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	req = vha->req;
	lg->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	lg->entry_count = 1;
	lg->handle = make_handle(req->id, lg->handle);
	lg->nport_handle = cpu_to_le16(loop_id);
	lg->control_flags =
	    cpu_to_le16(LCF_COMMAND_LOGO|LCF_IMPL_LOGO|
		LCF_FREE_NPORT);
	lg->port_id[0] = al_pa;
	lg->port_id[1] = area;
	lg->port_id[2] = करोमुख्य;
	lg->vp_index = vha->vp_idx;
	rval = qla2x00_issue_iocb_समयout(vha, lg, lg_dma, 0,
	    (ha->r_a_tov / 10 * 2) + 2);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x106f,
		    "Failed to issue logout IOCB (%x).\n", rval);
	पूर्ण अन्यथा अगर (lg->entry_status != 0) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1070,
		    "Failed to complete IOCB -- error status (%x).\n",
		    lg->entry_status);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (lg->comp_status != cpu_to_le16(CS_COMPLETE)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1071,
		    "Failed to complete IOCB -- completion status (%x) "
		    "ioparam=%x/%x.\n", le16_to_cpu(lg->comp_status),
		    le32_to_cpu(lg->io_parameter[0]),
		    le32_to_cpu(lg->io_parameter[1]));
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1072,
		    "Done %s.\n", __func__);
	पूर्ण

	dma_pool_मुक्त(ha->s_dma_pool, lg, lg_dma);

	वापस rval;
पूर्ण

/*
 * qla2x00_fabric_logout
 *	Issue logout fabric port mailbox command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	loop_id = device loop ID.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_fabric_logout(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id, uपूर्णांक8_t करोमुख्य,
    uपूर्णांक8_t area, uपूर्णांक8_t al_pa)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1073,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_LOGOUT_FABRIC_PORT;
	mcp->out_mb = MBX_1|MBX_0;
	अगर (HAS_EXTENDED_IDS(vha->hw)) अणु
		mcp->mb[1] = loop_id;
		mcp->mb[10] = 0;
		mcp->out_mb |= MBX_10;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = loop_id << 8;
	पूर्ण

	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1074,
		    "Failed=%x mb[1]=%x.\n", rval, mcp->mb[1]);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1075,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_full_login_lip
 *	Issue full login LIP mailbox command.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	TARGET_QUEUE_LOCK must be released.
 *	ADAPTER_STATE_LOCK must be released.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_full_login_lip(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1076,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_LIP_FULL_LOGIN;
	mcp->mb[1] = IS_FWI2_CAPABLE(vha->hw) ? BIT_4 : 0;
	mcp->mb[2] = 0;
	mcp->mb[3] = 0;
	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x1077, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1078,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_id_list
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_id_list(scsi_qla_host_t *vha, व्योम *id_list, dma_addr_t id_list_dma,
    uपूर्णांक16_t *entries)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1079,
	    "Entered %s.\n", __func__);

	अगर (id_list == शून्य)
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_GET_ID_LIST;
	mcp->out_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(vha->hw)) अणु
		mcp->mb[2] = MSW(id_list_dma);
		mcp->mb[3] = LSW(id_list_dma);
		mcp->mb[6] = MSW(MSD(id_list_dma));
		mcp->mb[7] = LSW(MSD(id_list_dma));
		mcp->mb[8] = 0;
		mcp->mb[9] = vha->vp_idx;
		mcp->out_mb |= MBX_9|MBX_8|MBX_7|MBX_6|MBX_3|MBX_2;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = MSW(id_list_dma);
		mcp->mb[2] = LSW(id_list_dma);
		mcp->mb[3] = MSW(MSD(id_list_dma));
		mcp->mb[6] = LSW(MSD(id_list_dma));
		mcp->out_mb |= MBX_6|MBX_3|MBX_2|MBX_1;
	पूर्ण
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x107a, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		*entries = mcp->mb[1];
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x107b,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_resource_cnts
 *	Get current firmware resource counts.
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_resource_cnts(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x107c,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_RESOURCE_COUNTS;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_11|MBX_10|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA81XX(ha) || IS_QLA83XX(ha) ||
	    IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->in_mb |= MBX_12;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x107d,
		    "Failed mb[0]=%x.\n", mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x107e,
		    "Done %s mb1=%x mb2=%x mb3=%x mb6=%x mb7=%x mb10=%x "
		    "mb11=%x mb12=%x.\n", __func__, mcp->mb[1], mcp->mb[2],
		    mcp->mb[3], mcp->mb[6], mcp->mb[7], mcp->mb[10],
		    mcp->mb[11], mcp->mb[12]);

		ha->orig_fw_tgt_xcb_count =  mcp->mb[1];
		ha->cur_fw_tgt_xcb_count = mcp->mb[2];
		ha->cur_fw_xcb_count = mcp->mb[3];
		ha->orig_fw_xcb_count = mcp->mb[6];
		ha->cur_fw_iocb_count = mcp->mb[7];
		ha->orig_fw_iocb_count = mcp->mb[10];
		अगर (ha->flags.npiv_supported)
			ha->max_npiv_vports = mcp->mb[11];
		अगर (IS_QLA81XX(ha) || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
		    IS_QLA28XX(ha))
			ha->fw_max_fcf_count = mcp->mb[12];
	पूर्ण

	वापस (rval);
पूर्ण

/*
 * qla2x00_get_fcal_position_map
 *	Get FCAL (LILP) position map using mailbox command
 *
 * Input:
 *	ha = adapter state poपूर्णांकer.
 *	pos_map = buffer poपूर्णांकer (can be शून्य).
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla2x00_get_fcal_position_map(scsi_qla_host_t *vha, अक्षर *pos_map)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	अक्षर *pmap;
	dma_addr_t pmap_dma;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x107f,
	    "Entered %s.\n", __func__);

	pmap = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &pmap_dma);
	अगर (pmap  == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x1080,
		    "Memory alloc failed.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	mcp->mb[0] = MBC_GET_FC_AL_POSITION_MAP;
	mcp->mb[2] = MSW(pmap_dma);
	mcp->mb[3] = LSW(pmap_dma);
	mcp->mb[6] = MSW(MSD(pmap_dma));
	mcp->mb[7] = LSW(MSD(pmap_dma));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->buf_size = FCAL_MAP_SIZE;
	mcp->flags = MBX_DMA_IN;
	mcp->tov = (ha->login_समयout * 2) + (ha->login_समयout / 2);
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval == QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1081,
		    "mb0/mb1=%x/%X FC/AL position map size (%x).\n",
		    mcp->mb[0], mcp->mb[1], (अचिन्हित)pmap[0]);
		ql_dump_buffer(ql_dbg_mbx + ql_dbg_buffer, vha, 0x111d,
		    pmap, pmap[0] + 1);

		अगर (pos_map)
			स_नकल(pos_map, pmap, FCAL_MAP_SIZE);
	पूर्ण
	dma_pool_मुक्त(ha->s_dma_pool, pmap, pmap_dma);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1082, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1083,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/*
 * qla2x00_get_link_status
 *
 * Input:
 *	ha = adapter block poपूर्णांकer.
 *	loop_id = device loop ID.
 *	ret_buf = poपूर्णांकer to link status वापस buffer.
 *
 * Returns:
 *	0 = success.
 *	BIT_0 = mem alloc error.
 *	BIT_1 = mailbox error.
 */
पूर्णांक
qla2x00_get_link_status(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id,
    काष्ठा link_statistics *stats, dma_addr_t stats_dma)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	uपूर्णांक32_t *iter = (uपूर्णांक32_t *)stats;
	uलघु dwords = दुरत्व(typeof(*stats), link_up_cnt)/माप(*iter);
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1084,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_LINK_STATUS;
	mcp->mb[2] = MSW(LSD(stats_dma));
	mcp->mb[3] = LSW(LSD(stats_dma));
	mcp->mb[6] = MSW(MSD(stats_dma));
	mcp->mb[7] = LSW(MSD(stats_dma));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_0;
	mcp->in_mb = MBX_0;
	अगर (IS_FWI2_CAPABLE(ha)) अणु
		mcp->mb[1] = loop_id;
		mcp->mb[4] = 0;
		mcp->mb[10] = 0;
		mcp->out_mb |= MBX_10|MBX_4|MBX_1;
		mcp->in_mb |= MBX_1;
	पूर्ण अन्यथा अगर (HAS_EXTENDED_IDS(ha)) अणु
		mcp->mb[1] = loop_id;
		mcp->mb[10] = 0;
		mcp->out_mb |= MBX_10|MBX_1;
	पूर्ण अन्यथा अणु
		mcp->mb[1] = loop_id << 8;
		mcp->out_mb |= MBX_1;
	पूर्ण
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = IOCTL_CMD;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval == QLA_SUCCESS) अणु
		अगर (mcp->mb[0] != MBS_COMMAND_COMPLETE) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1085,
			    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			/* Re-endianize - firmware data is le32. */
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1086,
			    "Done %s.\n", __func__);
			क्रम ( ; dwords--; iter++)
				le32_to_cpus(iter);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Failed. */
		ql_dbg(ql_dbg_mbx, vha, 0x1087, "Failed=%x.\n", rval);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_get_isp_stats(scsi_qla_host_t *vha, काष्ठा link_statistics *stats,
    dma_addr_t stats_dma, uपूर्णांक16_t options)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	uपूर्णांक32_t *iter = (uपूर्णांक32_t *)stats;
	uलघु dwords = माप(*stats)/माप(*iter);

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1088,
	    "Entered %s.\n", __func__);

	स_रखो(&mc, 0, माप(mc));
	mc.mb[0] = MBC_GET_LINK_PRIV_STATS;
	mc.mb[2] = MSW(LSD(stats_dma));
	mc.mb[3] = LSW(LSD(stats_dma));
	mc.mb[6] = MSW(MSD(stats_dma));
	mc.mb[7] = LSW(MSD(stats_dma));
	mc.mb[8] = dwords;
	mc.mb[9] = vha->vp_idx;
	mc.mb[10] = options;

	rval = qla24xx_send_mb_cmd(vha, &mc);

	अगर (rval == QLA_SUCCESS) अणु
		अगर (mcp->mb[0] != MBS_COMMAND_COMPLETE) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1089,
			    "Failed mb[0]=%x.\n", mcp->mb[0]);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x108a,
			    "Done %s.\n", __func__);
			/* Re-endianize - firmware data is le32. */
			क्रम ( ; dwords--; iter++)
				le32_to_cpus(iter);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Failed. */
		ql_dbg(ql_dbg_mbx, vha, 0x108b, "Failed=%x.\n", rval);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_पात_command(srb_t *sp)
अणु
	पूर्णांक		rval;
	अचिन्हित दीर्घ   flags = 0;

	काष्ठा पात_entry_24xx *abt;
	dma_addr_t	abt_dma;
	uपूर्णांक32_t	handle;
	fc_port_t	*fcport = sp->fcport;
	काष्ठा scsi_qla_host *vha = fcport->vha;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा req_que *req = vha->req;
	काष्ठा qla_qpair *qpair = sp->qpair;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x108c,
	    "Entered %s.\n", __func__);

	अगर (sp->qpair)
		req = sp->qpair->req;
	अन्यथा
		वापस QLA_FUNCTION_FAILED;

	अगर (ql2xasyncपंचांगfenable)
		वापस qla24xx_async_पात_command(sp);

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

	abt = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &abt_dma);
	अगर (abt == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x108d,
		    "Failed to allocate abort IOCB.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	abt->entry_type = ABORT_IOCB_TYPE;
	abt->entry_count = 1;
	abt->handle = make_handle(req->id, abt->handle);
	abt->nport_handle = cpu_to_le16(fcport->loop_id);
	abt->handle_to_पात = make_handle(req->id, handle);
	abt->port_id[0] = fcport->d_id.b.al_pa;
	abt->port_id[1] = fcport->d_id.b.area;
	abt->port_id[2] = fcport->d_id.b.करोमुख्य;
	abt->vp_index = fcport->vha->vp_idx;

	abt->req_que_no = cpu_to_le16(req->id);
	/* Need to pass original sp */
	qla_nvme_पात_set_option(abt, sp);

	rval = qla2x00_issue_iocb(vha, abt, abt_dma, 0);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x108e,
		    "Failed to issue IOCB (%x).\n", rval);
	पूर्ण अन्यथा अगर (abt->entry_status != 0) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x108f,
		    "Failed to complete IOCB -- error status (%x).\n",
		    abt->entry_status);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (abt->nport_handle != cpu_to_le16(0)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1090,
		    "Failed to complete IOCB -- completion status (%x).\n",
		    le16_to_cpu(abt->nport_handle));
		अगर (abt->nport_handle == cpu_to_le16(CS_IOCB_ERROR))
			rval = QLA_FUNCTION_PARAMETER_ERROR;
		अन्यथा
			rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1091,
		    "Done %s.\n", __func__);
	पूर्ण
	अगर (rval == QLA_SUCCESS)
		qla_nvme_पात_process_comp_status(abt, sp);

	qla_रुको_nvme_release_cmd_kref(sp);

	dma_pool_मुक्त(ha->s_dma_pool, abt, abt_dma);

	वापस rval;
पूर्ण

काष्ठा tsk_mgmt_cmd अणु
	जोड़ अणु
		काष्ठा tsk_mgmt_entry tsk;
		काष्ठा sts_entry_24xx sts;
	पूर्ण p;
पूर्ण;

अटल पूर्णांक
__qla24xx_issue_पंचांगf(अक्षर *name, uपूर्णांक32_t type, काष्ठा fc_port *fcport,
    uपूर्णांक64_t l, पूर्णांक tag)
अणु
	पूर्णांक		rval, rval2;
	काष्ठा tsk_mgmt_cmd *tsk;
	काष्ठा sts_entry_24xx *sts;
	dma_addr_t	tsk_dma;
	scsi_qla_host_t *vha;
	काष्ठा qla_hw_data *ha;
	काष्ठा req_que *req;
	काष्ठा qla_qpair *qpair;

	vha = fcport->vha;
	ha = vha->hw;
	req = vha->req;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1092,
	    "Entered %s.\n", __func__);

	अगर (vha->vp_idx && vha->qpair) अणु
		/* NPIV port */
		qpair = vha->qpair;
		req = qpair->req;
	पूर्ण

	tsk = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &tsk_dma);
	अगर (tsk == शून्य) अणु
		ql_log(ql_log_warn, vha, 0x1093,
		    "Failed to allocate task management IOCB.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	tsk->p.tsk.entry_type = TSK_MGMT_IOCB_TYPE;
	tsk->p.tsk.entry_count = 1;
	tsk->p.tsk.handle = make_handle(req->id, tsk->p.tsk.handle);
	tsk->p.tsk.nport_handle = cpu_to_le16(fcport->loop_id);
	tsk->p.tsk.समयout = cpu_to_le16(ha->r_a_tov / 10 * 2);
	tsk->p.tsk.control_flags = cpu_to_le32(type);
	tsk->p.tsk.port_id[0] = fcport->d_id.b.al_pa;
	tsk->p.tsk.port_id[1] = fcport->d_id.b.area;
	tsk->p.tsk.port_id[2] = fcport->d_id.b.करोमुख्य;
	tsk->p.tsk.vp_index = fcport->vha->vp_idx;
	अगर (type == TCF_LUN_RESET) अणु
		पूर्णांक_to_scsilun(l, &tsk->p.tsk.lun);
		host_to_fcp_swap((uपूर्णांक8_t *)&tsk->p.tsk.lun,
		    माप(tsk->p.tsk.lun));
	पूर्ण

	sts = &tsk->p.sts;
	rval = qla2x00_issue_iocb(vha, tsk, tsk_dma, 0);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1094,
		    "Failed to issue %s reset IOCB (%x).\n", name, rval);
	पूर्ण अन्यथा अगर (sts->entry_status != 0) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1095,
		    "Failed to complete IOCB -- error status (%x).\n",
		    sts->entry_status);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (sts->comp_status != cpu_to_le16(CS_COMPLETE)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1096,
		    "Failed to complete IOCB -- completion status (%x).\n",
		    le16_to_cpu(sts->comp_status));
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (le16_to_cpu(sts->scsi_status) &
	    SS_RESPONSE_INFO_LEN_VALID) अणु
		अगर (le32_to_cpu(sts->rsp_data_len) < 4) अणु
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1097,
			    "Ignoring inconsistent data length -- not enough "
			    "response info (%d).\n",
			    le32_to_cpu(sts->rsp_data_len));
		पूर्ण अन्यथा अगर (sts->data[3]) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1098,
			    "Failed to complete IOCB -- response (%x).\n",
			    sts->data[3]);
			rval = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण

	/* Issue marker IOCB. */
	rval2 = qla2x00_marker(vha, ha->base_qpair, fcport->loop_id, l,
	    type == TCF_LUN_RESET ? MK_SYNC_ID_LUN : MK_SYNC_ID);
	अगर (rval2 != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1099,
		    "Failed to issue marker IOCB (%x).\n", rval2);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x109a,
		    "Done %s.\n", __func__);
	पूर्ण

	dma_pool_मुक्त(ha->s_dma_pool, tsk, tsk_dma);

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_पात_target(काष्ठा fc_port *fcport, uपूर्णांक64_t l, पूर्णांक tag)
अणु
	काष्ठा qla_hw_data *ha = fcport->vha->hw;

	अगर ((ql2xasyncपंचांगfenable) && IS_FWI2_CAPABLE(ha))
		वापस qla2x00_async_पंचांग_cmd(fcport, TCF_TARGET_RESET, l, tag);

	वापस __qla24xx_issue_पंचांगf("Target", TCF_TARGET_RESET, fcport, l, tag);
पूर्ण

पूर्णांक
qla24xx_lun_reset(काष्ठा fc_port *fcport, uपूर्णांक64_t l, पूर्णांक tag)
अणु
	काष्ठा qla_hw_data *ha = fcport->vha->hw;

	अगर ((ql2xasyncपंचांगfenable) && IS_FWI2_CAPABLE(ha))
		वापस qla2x00_async_पंचांग_cmd(fcport, TCF_LUN_RESET, l, tag);

	वापस __qla24xx_issue_पंचांगf("Lun", TCF_LUN_RESET, fcport, l, tag);
पूर्ण

पूर्णांक
qla2x00_प्रणाली_error(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA23XX(ha) && !IS_FWI2_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x109b,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GEN_SYSTEM_ERROR;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = 5;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x109c, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x109d,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_ग_लिखो_serdes_word(scsi_qla_host_t *vha, uपूर्णांक16_t addr, uपूर्णांक16_t data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA25XX(vha->hw) && !IS_QLA2031(vha->hw) &&
	    !IS_QLA27XX(vha->hw) && !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1182,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_WRITE_SERDES;
	mcp->mb[1] = addr;
	अगर (IS_QLA2031(vha->hw))
		mcp->mb[2] = data & 0xff;
	अन्यथा
		mcp->mb[2] = data;

	mcp->mb[3] = 0;
	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1183,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1184,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_पढ़ो_serdes_word(scsi_qla_host_t *vha, uपूर्णांक16_t addr, uपूर्णांक16_t *data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA25XX(vha->hw) && !IS_QLA2031(vha->hw) &&
	    !IS_QLA27XX(vha->hw) && !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1185,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_READ_SERDES;
	mcp->mb[1] = addr;
	mcp->mb[3] = 0;
	mcp->out_mb = MBX_3|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (IS_QLA2031(vha->hw))
		*data = mcp->mb[1] & 0xff;
	अन्यथा
		*data = mcp->mb[1];

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1186,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1187,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla8044_ग_लिखो_serdes_word(scsi_qla_host_t *vha, uपूर्णांक32_t addr, uपूर्णांक32_t data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA8044(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x11a0,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SET_GET_ETH_SERDES_REG;
	mcp->mb[1] = HCS_WRITE_SERDES;
	mcp->mb[3] = LSW(addr);
	mcp->mb[4] = MSW(addr);
	mcp->mb[5] = LSW(data);
	mcp->mb[6] = MSW(data);
	mcp->out_mb = MBX_6|MBX_5|MBX_4|MBX_3|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x11a1,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1188,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla8044_पढ़ो_serdes_word(scsi_qla_host_t *vha, uपूर्णांक32_t addr, uपूर्णांक32_t *data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA8044(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1189,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SET_GET_ETH_SERDES_REG;
	mcp->mb[1] = HCS_READ_SERDES;
	mcp->mb[3] = LSW(addr);
	mcp->mb[4] = MSW(addr);
	mcp->out_mb = MBX_4|MBX_3|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	*data = mcp->mb[2] << 16 | mcp->mb[1];

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x118a,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x118b,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/**
 * qla2x00_set_serdes_params() -
 * @vha: HA context
 * @sw_em_1g: serial link options
 * @sw_em_2g: serial link options
 * @sw_em_4g: serial link options
 *
 * Returns
 */
पूर्णांक
qla2x00_set_serdes_params(scsi_qla_host_t *vha, uपूर्णांक16_t sw_em_1g,
    uपूर्णांक16_t sw_em_2g, uपूर्णांक16_t sw_em_4g)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x109e,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SERDES_PARAMS;
	mcp->mb[1] = BIT_0;
	mcp->mb[2] = sw_em_1g | BIT_15;
	mcp->mb[3] = sw_em_2g | BIT_15;
	mcp->mb[4] = sw_em_4g | BIT_15;
	mcp->out_mb = MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx, vha, 0x109f,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		/*EMPTY*/
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a0,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_stop_firmware(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a1,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_STOP_FIRMWARE;
	mcp->mb[1] = 0;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = 5;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10a2, "Failed=%x.\n", rval);
		अगर (mcp->mb[0] == MBS_INVALID_COMMAND)
			rval = QLA_INVALID_COMMAND;
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a3,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_enable_eft_trace(scsi_qla_host_t *vha, dma_addr_t eft_dma,
    uपूर्णांक16_t buffers)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a4,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	अगर (unlikely(pci_channel_offline(vha->hw->pdev)))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_TRACE_CONTROL;
	mcp->mb[1] = TC_EFT_ENABLE;
	mcp->mb[2] = LSW(eft_dma);
	mcp->mb[3] = MSW(eft_dma);
	mcp->mb[4] = LSW(MSD(eft_dma));
	mcp->mb[5] = MSW(MSD(eft_dma));
	mcp->mb[6] = buffers;
	mcp->mb[7] = TC_AEN_DISABLE;
	mcp->out_mb = MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10a5,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a6,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_disable_eft_trace(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a7,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	अगर (unlikely(pci_channel_offline(vha->hw->pdev)))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_TRACE_CONTROL;
	mcp->mb[1] = TC_EFT_DISABLE;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10a8,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10a9,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_enable_fce_trace(scsi_qla_host_t *vha, dma_addr_t fce_dma,
    uपूर्णांक16_t buffers, uपूर्णांक16_t *mb, uपूर्णांक32_t *dwords)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10aa,
	    "Entered %s.\n", __func__);

	अगर (!IS_QLA25XX(vha->hw) && !IS_QLA81XX(vha->hw) &&
	    !IS_QLA83XX(vha->hw) && !IS_QLA27XX(vha->hw) &&
	    !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	अगर (unlikely(pci_channel_offline(vha->hw->pdev)))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_TRACE_CONTROL;
	mcp->mb[1] = TC_FCE_ENABLE;
	mcp->mb[2] = LSW(fce_dma);
	mcp->mb[3] = MSW(fce_dma);
	mcp->mb[4] = LSW(MSD(fce_dma));
	mcp->mb[5] = MSW(MSD(fce_dma));
	mcp->mb[6] = buffers;
	mcp->mb[7] = TC_AEN_DISABLE;
	mcp->mb[8] = 0;
	mcp->mb[9] = TC_FCE_DEFAULT_RX_SIZE;
	mcp->mb[10] = TC_FCE_DEFAULT_TX_SIZE;
	mcp->out_mb = MBX_10|MBX_9|MBX_8|MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|
	    MBX_1|MBX_0;
	mcp->in_mb = MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10ab,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ac,
		    "Done %s.\n", __func__);

		अगर (mb)
			स_नकल(mb, mcp->mb, 8 * माप(*mb));
		अगर (dwords)
			*dwords = buffers;
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_disable_fce_trace(scsi_qla_host_t *vha, uपूर्णांक64_t *wr, uपूर्णांक64_t *rd)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ad,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	अगर (unlikely(pci_channel_offline(vha->hw->pdev)))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_TRACE_CONTROL;
	mcp->mb[1] = TC_FCE_DISABLE;
	mcp->mb[2] = TC_FCE_DISABLE_TRACE;
	mcp->out_mb = MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_9|MBX_8|MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|
	    MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10ae,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10af,
		    "Done %s.\n", __func__);

		अगर (wr)
			*wr = (uपूर्णांक64_t) mcp->mb[5] << 48 |
			    (uपूर्णांक64_t) mcp->mb[4] << 32 |
			    (uपूर्णांक64_t) mcp->mb[3] << 16 |
			    (uपूर्णांक64_t) mcp->mb[2];
		अगर (rd)
			*rd = (uपूर्णांक64_t) mcp->mb[9] << 48 |
			    (uपूर्णांक64_t) mcp->mb[8] << 32 |
			    (uपूर्णांक64_t) mcp->mb[7] << 16 |
			    (uपूर्णांक64_t) mcp->mb[6];
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_get_idma_speed(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id,
	uपूर्णांक16_t *port_speed, uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10b0,
	    "Entered %s.\n", __func__);

	अगर (!IS_IIDMA_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_PORT_PARAMS;
	mcp->mb[1] = loop_id;
	mcp->mb[2] = mcp->mb[3] = 0;
	mcp->mb[9] = vha->vp_idx;
	mcp->out_mb = MBX_9|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_3|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	/* Return mailbox statuses. */
	अगर (mb) अणु
		mb[0] = mcp->mb[0];
		mb[1] = mcp->mb[1];
		mb[3] = mcp->mb[3];
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10b1, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10b2,
		    "Done %s.\n", __func__);
		अगर (port_speed)
			*port_speed = mcp->mb[3];
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_set_idma_speed(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id,
    uपूर्णांक16_t port_speed, uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10b3,
	    "Entered %s.\n", __func__);

	अगर (!IS_IIDMA_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_PORT_PARAMS;
	mcp->mb[1] = loop_id;
	mcp->mb[2] = BIT_0;
	mcp->mb[3] = port_speed & 0x3F;
	mcp->mb[9] = vha->vp_idx;
	mcp->out_mb = MBX_9|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_3|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	/* Return mailbox statuses. */
	अगर (mb) अणु
		mb[0] = mcp->mb[0];
		mb[1] = mcp->mb[1];
		mb[3] = mcp->mb[3];
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10b4,
		    "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10b5,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

व्योम
qla24xx_report_id_acquisition(scsi_qla_host_t *vha,
	काष्ठा vp_rpt_id_entry_24xx *rptid_entry)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	scsi_qla_host_t *vp = शून्य;
	अचिन्हित दीर्घ   flags;
	पूर्णांक found;
	port_id_t id;
	काष्ठा fc_port *fcport;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10b6,
	    "Entered %s.\n", __func__);

	अगर (rptid_entry->entry_status != 0)
		वापस;

	id.b.करोमुख्य = rptid_entry->port_id[2];
	id.b.area   = rptid_entry->port_id[1];
	id.b.al_pa  = rptid_entry->port_id[0];
	id.b.rsvd_1 = 0;
	ha->flags.n2n_ae = 0;

	अगर (rptid_entry->क्रमmat == 0) अणु
		/* loop */
		ql_dbg(ql_dbg_async, vha, 0x10b7,
		    "Format 0 : Number of VPs setup %d, number of "
		    "VPs acquired %d.\n", rptid_entry->vp_setup,
		    rptid_entry->vp_acquired);
		ql_dbg(ql_dbg_async, vha, 0x10b8,
		    "Primary port id %02x%02x%02x.\n",
		    rptid_entry->port_id[2], rptid_entry->port_id[1],
		    rptid_entry->port_id[0]);
		ha->current_topology = ISP_CFG_NL;
		qlt_update_host_map(vha, id);

	पूर्ण अन्यथा अगर (rptid_entry->क्रमmat == 1) अणु
		/* fabric */
		ql_dbg(ql_dbg_async, vha, 0x10b9,
		    "Format 1: VP[%d] enabled - status %d - with "
		    "port id %02x%02x%02x.\n", rptid_entry->vp_idx,
			rptid_entry->vp_status,
		    rptid_entry->port_id[2], rptid_entry->port_id[1],
		    rptid_entry->port_id[0]);
		ql_dbg(ql_dbg_async, vha, 0x5075,
		   "Format 1: Remote WWPN %8phC.\n",
		   rptid_entry->u.f1.port_name);

		ql_dbg(ql_dbg_async, vha, 0x5075,
		   "Format 1: WWPN %8phC.\n",
		   vha->port_name);

		चयन (rptid_entry->u.f1.flags & TOPO_MASK) अणु
		हाल TOPO_N2N:
			ha->current_topology = ISP_CFG_N;
			spin_lock_irqsave(&vha->hw->tgt.sess_lock, flags);
			list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
				fcport->scan_state = QLA_FCPORT_SCAN;
				fcport->n2n_flag = 0;
			पूर्ण
			id.b24 = 0;
			अगर (wwn_to_u64(vha->port_name) >
			    wwn_to_u64(rptid_entry->u.f1.port_name)) अणु
				vha->d_id.b24 = 0;
				vha->d_id.b.al_pa = 1;
				ha->flags.n2n_bigger = 1;

				id.b.al_pa = 2;
				ql_dbg(ql_dbg_async, vha, 0x5075,
				    "Format 1: assign local id %x remote id %x\n",
				    vha->d_id.b24, id.b24);
			पूर्ण अन्यथा अणु
				ql_dbg(ql_dbg_async, vha, 0x5075,
				    "Format 1: Remote login - Waiting for WWPN %8phC.\n",
				    rptid_entry->u.f1.port_name);
				ha->flags.n2n_bigger = 0;
			पूर्ण

			fcport = qla2x00_find_fcport_by_wwpn(vha,
			    rptid_entry->u.f1.port_name, 1);
			spin_unlock_irqrestore(&vha->hw->tgt.sess_lock, flags);


			अगर (fcport) अणु
				fcport->plogi_nack_करोne_deadline = jअगरfies + HZ;
				fcport->dm_login_expire = jअगरfies +
					QLA_N2N_WAIT_TIME * HZ;
				fcport->scan_state = QLA_FCPORT_FOUND;
				fcport->n2n_flag = 1;
				fcport->keep_nport_handle = 1;

				अगर (wwn_to_u64(vha->port_name) >
				    wwn_to_u64(fcport->port_name)) अणु
					fcport->d_id = id;
				पूर्ण

				चयन (fcport->disc_state) अणु
				हाल DSC_DELETED:
					set_bit(RELOGIN_NEEDED,
					    &vha->dpc_flags);
					अवरोध;
				हाल DSC_DELETE_PEND:
					अवरोध;
				शेष:
					qlt_schedule_sess_क्रम_deletion(fcport);
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				qla24xx_post_newsess_work(vha, &id,
				    rptid_entry->u.f1.port_name,
				    rptid_entry->u.f1.node_name,
				    शून्य,
				    FS_FCP_IS_N2N);
			पूर्ण

			/* अगर our portname is higher then initiate N2N login */

			set_bit(N2N_LOGIN_NEEDED, &vha->dpc_flags);
			वापस;
		हाल TOPO_FL:
			ha->current_topology = ISP_CFG_FL;
			अवरोध;
		हाल TOPO_F:
			ha->current_topology = ISP_CFG_F;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		ha->flags.gpsc_supported = 1;
		ha->current_topology = ISP_CFG_F;
		/* buffer to buffer credit flag */
		vha->flags.bbcr_enable = (rptid_entry->u.f1.bbcr & 0xf) != 0;

		अगर (rptid_entry->vp_idx == 0) अणु
			अगर (rptid_entry->vp_status == VP_STAT_COMPL) अणु
				/* FA-WWN is only क्रम physical port */
				अगर (qla_ini_mode_enabled(vha) &&
				    ha->flags.fawwpn_enabled &&
				    (rptid_entry->u.f1.flags &
				     BIT_6)) अणु
					स_नकल(vha->port_name,
					    rptid_entry->u.f1.port_name,
					    WWN_SIZE);
				पूर्ण

				qlt_update_host_map(vha, id);
			पूर्ण

			set_bit(REGISTER_FC4_NEEDED, &vha->dpc_flags);
			set_bit(REGISTER_FDMI_NEEDED, &vha->dpc_flags);
		पूर्ण अन्यथा अणु
			अगर (rptid_entry->vp_status != VP_STAT_COMPL &&
				rptid_entry->vp_status != VP_STAT_ID_CHG) अणु
				ql_dbg(ql_dbg_mbx, vha, 0x10ba,
				    "Could not acquire ID for VP[%d].\n",
				    rptid_entry->vp_idx);
				वापस;
			पूर्ण

			found = 0;
			spin_lock_irqsave(&ha->vport_slock, flags);
			list_क्रम_each_entry(vp, &ha->vp_list, list) अणु
				अगर (rptid_entry->vp_idx == vp->vp_idx) अणु
					found = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			spin_unlock_irqrestore(&ha->vport_slock, flags);

			अगर (!found)
				वापस;

			qlt_update_host_map(vp, id);

			/*
			 * Cannot configure here as we are still sitting on the
			 * response queue. Handle it in dpc context.
			 */
			set_bit(VP_IDX_ACQUIRED, &vp->vp_flags);
			set_bit(REGISTER_FC4_NEEDED, &vp->dpc_flags);
			set_bit(REGISTER_FDMI_NEEDED, &vp->dpc_flags);
		पूर्ण
		set_bit(VP_DPC_NEEDED, &vha->dpc_flags);
		qla2xxx_wake_dpc(vha);
	पूर्ण अन्यथा अगर (rptid_entry->क्रमmat == 2) अणु
		ql_dbg(ql_dbg_async, vha, 0x505f,
		    "RIDA: format 2/N2N Primary port id %02x%02x%02x.\n",
		    rptid_entry->port_id[2], rptid_entry->port_id[1],
		    rptid_entry->port_id[0]);

		ql_dbg(ql_dbg_async, vha, 0x5075,
		    "N2N: Remote WWPN %8phC.\n",
		    rptid_entry->u.f2.port_name);

		/* N2N.  direct connect */
		ha->current_topology = ISP_CFG_N;
		ha->flags.rida_fmt2 = 1;
		vha->d_id.b.करोमुख्य = rptid_entry->port_id[2];
		vha->d_id.b.area = rptid_entry->port_id[1];
		vha->d_id.b.al_pa = rptid_entry->port_id[0];

		ha->flags.n2n_ae = 1;
		spin_lock_irqsave(&ha->vport_slock, flags);
		qlt_update_vp_map(vha, SET_AL_PA);
		spin_unlock_irqrestore(&ha->vport_slock, flags);

		list_क्रम_each_entry(fcport, &vha->vp_fcports, list) अणु
			fcport->scan_state = QLA_FCPORT_SCAN;
			fcport->n2n_flag = 0;
		पूर्ण

		fcport = qla2x00_find_fcport_by_wwpn(vha,
		    rptid_entry->u.f2.port_name, 1);

		अगर (fcport) अणु
			fcport->login_retry = vha->hw->login_retry_count;
			fcport->plogi_nack_करोne_deadline = jअगरfies + HZ;
			fcport->scan_state = QLA_FCPORT_FOUND;
			fcport->keep_nport_handle = 1;
			fcport->n2n_flag = 1;
			fcport->d_id.b.करोमुख्य =
				rptid_entry->u.f2.remote_nport_id[2];
			fcport->d_id.b.area =
				rptid_entry->u.f2.remote_nport_id[1];
			fcport->d_id.b.al_pa =
				rptid_entry->u.f2.remote_nport_id[0];
		पूर्ण
	पूर्ण
पूर्ण

/*
 * qla24xx_modअगरy_vp_config
 *	Change VP configuration क्रम vha
 *
 * Input:
 *	vha = adapter block poपूर्णांकer.
 *
 * Returns:
 *	qla2xxx local function वापस status code.
 *
 * Context:
 *	Kernel context.
 */
पूर्णांक
qla24xx_modअगरy_vp_config(scsi_qla_host_t *vha)
अणु
	पूर्णांक		rval;
	काष्ठा vp_config_entry_24xx *vpmod;
	dma_addr_t	vpmod_dma;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा scsi_qla_host *base_vha = pci_get_drvdata(ha->pdev);

	/* This can be called by the parent */

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10bb,
	    "Entered %s.\n", __func__);

	vpmod = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &vpmod_dma);
	अगर (!vpmod) अणु
		ql_log(ql_log_warn, vha, 0x10bc,
		    "Failed to allocate modify VP IOCB.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	vpmod->entry_type = VP_CONFIG_IOCB_TYPE;
	vpmod->entry_count = 1;
	vpmod->command = VCT_COMMAND_MOD_ENABLE_VPS;
	vpmod->vp_count = 1;
	vpmod->vp_index1 = vha->vp_idx;
	vpmod->options_idx1 = BIT_3|BIT_4|BIT_5;

	qlt_modअगरy_vp_config(vha, vpmod);

	स_नकल(vpmod->node_name_idx1, vha->node_name, WWN_SIZE);
	स_नकल(vpmod->port_name_idx1, vha->port_name, WWN_SIZE);
	vpmod->entry_count = 1;

	rval = qla2x00_issue_iocb(base_vha, vpmod, vpmod_dma, 0);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10bd,
		    "Failed to issue VP config IOCB (%x).\n", rval);
	पूर्ण अन्यथा अगर (vpmod->comp_status != 0) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10be,
		    "Failed to complete IOCB -- error status (%x).\n",
		    vpmod->comp_status);
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अगर (vpmod->comp_status != cpu_to_le16(CS_COMPLETE)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10bf,
		    "Failed to complete IOCB -- completion status (%x).\n",
		    le16_to_cpu(vpmod->comp_status));
		rval = QLA_FUNCTION_FAILED;
	पूर्ण अन्यथा अणु
		/* EMPTY */
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10c0,
		    "Done %s.\n", __func__);
		fc_vport_set_state(vha->fc_vport, FC_VPORT_INITIALIZING);
	पूर्ण
	dma_pool_मुक्त(ha->s_dma_pool, vpmod, vpmod_dma);

	वापस rval;
पूर्ण

/*
 * qla2x00_send_change_request
 *	Receive or disable RSCN request from fabric controller
 *
 * Input:
 *	ha = adapter block poपूर्णांकer
 *	क्रमmat = registration क्रमmat:
 *		0 - Reserved
 *		1 - Fabric detected registration
 *		2 - N_port detected registration
 *		3 - Full registration
 *		FF - clear registration
 *	vp_idx = Virtual port index
 *
 * Returns:
 *	qla2x00 local function वापस status code.
 *
 * Context:
 *	Kernel Context
 */

पूर्णांक
qla2x00_send_change_request(scsi_qla_host_t *vha, uपूर्णांक16_t क्रमmat,
			    uपूर्णांक16_t vp_idx)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10c7,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SEND_CHANGE_REQUEST;
	mcp->mb[1] = क्रमmat;
	mcp->mb[9] = vp_idx;
	mcp->out_mb = MBX_9|MBX_1|MBX_0;
	mcp->in_mb = MBX_0|MBX_1;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval == QLA_SUCCESS) अणु
		अगर (mcp->mb[0] != MBS_COMMAND_COMPLETE) अणु
			rval = BIT_1;
		पूर्ण
	पूर्ण अन्यथा
		rval = BIT_1;

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_dump_ram(scsi_qla_host_t *vha, dma_addr_t req_dma, uपूर्णांक32_t addr,
    uपूर्णांक32_t size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1009,
	    "Entered %s.\n", __func__);

	अगर (MSW(addr) || IS_FWI2_CAPABLE(vha->hw)) अणु
		mcp->mb[0] = MBC_DUMP_RISC_RAM_EXTENDED;
		mcp->mb[8] = MSW(addr);
		mcp->mb[10] = 0;
		mcp->out_mb = MBX_10|MBX_8|MBX_0;
	पूर्ण अन्यथा अणु
		mcp->mb[0] = MBC_DUMP_RISC_RAM;
		mcp->out_mb = MBX_0;
	पूर्ण
	mcp->mb[1] = LSW(addr);
	mcp->mb[2] = MSW(req_dma);
	mcp->mb[3] = LSW(req_dma);
	mcp->mb[6] = MSW(MSD(req_dma));
	mcp->mb[7] = LSW(MSD(req_dma));
	mcp->out_mb |= MBX_7|MBX_6|MBX_3|MBX_2|MBX_1;
	अगर (IS_FWI2_CAPABLE(vha->hw)) अणु
		mcp->mb[4] = MSW(size);
		mcp->mb[5] = LSW(size);
		mcp->out_mb |= MBX_5|MBX_4;
	पूर्ण अन्यथा अणु
		mcp->mb[4] = LSW(size);
		mcp->out_mb |= MBX_4;
	पूर्ण

	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1008,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1007,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण
/* 84XX Support **************************************************************/

काष्ठा cs84xx_mgmt_cmd अणु
	जोड़ अणु
		काष्ठा verअगरy_chip_entry_84xx req;
		काष्ठा verअगरy_chip_rsp_84xx rsp;
	पूर्ण p;
पूर्ण;

पूर्णांक
qla84xx_verअगरy_chip(काष्ठा scsi_qla_host *vha, uपूर्णांक16_t *status)
अणु
	पूर्णांक rval, retry;
	काष्ठा cs84xx_mgmt_cmd *mn;
	dma_addr_t mn_dma;
	uपूर्णांक16_t options;
	अचिन्हित दीर्घ flags;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10c8,
	    "Entered %s.\n", __func__);

	mn = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &mn_dma);
	अगर (mn == शून्य) अणु
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	/* Force Update? */
	options = ha->cs84xx->fw_update ? VCO_FORCE_UPDATE : 0;
	/* Diagnostic firmware? */
	/* options |= MENLO_DIAG_FW; */
	/* We update the firmware with only one data sequence. */
	options |= VCO_END_OF_DATA;

	करो अणु
		retry = 0;
		स_रखो(mn, 0, माप(*mn));
		mn->p.req.entry_type = VERIFY_CHIP_IOCB_TYPE;
		mn->p.req.entry_count = 1;
		mn->p.req.options = cpu_to_le16(options);

		ql_dbg(ql_dbg_mbx + ql_dbg_buffer, vha, 0x111c,
		    "Dump of Verify Request.\n");
		ql_dump_buffer(ql_dbg_mbx + ql_dbg_buffer, vha, 0x111e,
		    mn, माप(*mn));

		rval = qla2x00_issue_iocb_समयout(vha, mn, mn_dma, 0, 120);
		अगर (rval != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x10cb,
			    "Failed to issue verify IOCB (%x).\n", rval);
			जाओ verअगरy_करोne;
		पूर्ण

		ql_dbg(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1110,
		    "Dump of Verify Response.\n");
		ql_dump_buffer(ql_dbg_mbx + ql_dbg_buffer, vha, 0x1118,
		    mn, माप(*mn));

		status[0] = le16_to_cpu(mn->p.rsp.comp_status);
		status[1] = status[0] == CS_VCS_CHIP_FAILURE ?
		    le16_to_cpu(mn->p.rsp.failure_code) : 0;
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ce,
		    "cs=%x fc=%x.\n", status[0], status[1]);

		अगर (status[0] != CS_COMPLETE) अणु
			rval = QLA_FUNCTION_FAILED;
			अगर (!(options & VCO_DONT_UPDATE_FW)) अणु
				ql_dbg(ql_dbg_mbx, vha, 0x10cf,
				    "Firmware update failed. Retrying "
				    "without update firmware.\n");
				options |= VCO_DONT_UPDATE_FW;
				options &= ~VCO_FORCE_UPDATE;
				retry = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d0,
			    "Firmware updated to %x.\n",
			    le32_to_cpu(mn->p.rsp.fw_ver));

			/* NOTE: we only update OP firmware. */
			spin_lock_irqsave(&ha->cs84xx->access_lock, flags);
			ha->cs84xx->op_fw_version =
			    le32_to_cpu(mn->p.rsp.fw_ver);
			spin_unlock_irqrestore(&ha->cs84xx->access_lock,
			    flags);
		पूर्ण
	पूर्ण जबतक (retry);

verअगरy_करोne:
	dma_pool_मुक्त(ha->s_dma_pool, mn, mn_dma);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10d1,
		    "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d2,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla25xx_init_req_que(काष्ठा scsi_qla_host *vha, काष्ठा req_que *req)
अणु
	पूर्णांक rval;
	अचिन्हित दीर्घ flags;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->flags.fw_started)
		वापस QLA_SUCCESS;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d3,
	    "Entered %s.\n", __func__);

	अगर (IS_SHADOW_REG_CAPABLE(ha))
		req->options |= BIT_13;

	mcp->mb[0] = MBC_INITIALIZE_MULTIQ;
	mcp->mb[1] = req->options;
	mcp->mb[2] = MSW(LSD(req->dma));
	mcp->mb[3] = LSW(LSD(req->dma));
	mcp->mb[6] = MSW(MSD(req->dma));
	mcp->mb[7] = LSW(MSD(req->dma));
	mcp->mb[5] = req->length;
	अगर (req->rsp)
		mcp->mb[10] = req->rsp->id;
	mcp->mb[12] = req->qos;
	mcp->mb[11] = req->vp_idx;
	mcp->mb[13] = req->rid;
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->mb[15] = 0;

	mcp->mb[4] = req->id;
	/* que in ptr index */
	mcp->mb[8] = 0;
	/* que out ptr index */
	mcp->mb[9] = *req->out_ptr = 0;
	mcp->out_mb = MBX_14|MBX_13|MBX_12|MBX_11|MBX_10|MBX_9|MBX_8|MBX_7|
			MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->flags = MBX_DMA_OUT;
	mcp->tov = MBX_TOV_SECONDS * 2;

	अगर (IS_QLA81XX(ha) || IS_QLA83XX(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha))
		mcp->in_mb |= MBX_1;
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		mcp->out_mb |= MBX_15;
		/* debug q create issue in SR-IOV */
		mcp->in_mb |= MBX_9 | MBX_8 | MBX_7;
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);
	अगर (!(req->options & BIT_0)) अणु
		wrt_reg_dword(req->req_q_in, 0);
		अगर (!IS_QLA83XX(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
			wrt_reg_dword(req->req_q_out, 0);
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10d4,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d5,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla25xx_init_rsp_que(काष्ठा scsi_qla_host *vha, काष्ठा rsp_que *rsp)
अणु
	पूर्णांक rval;
	अचिन्हित दीर्घ flags;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!ha->flags.fw_started)
		वापस QLA_SUCCESS;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d6,
	    "Entered %s.\n", __func__);

	अगर (IS_SHADOW_REG_CAPABLE(ha))
		rsp->options |= BIT_13;

	mcp->mb[0] = MBC_INITIALIZE_MULTIQ;
	mcp->mb[1] = rsp->options;
	mcp->mb[2] = MSW(LSD(rsp->dma));
	mcp->mb[3] = LSW(LSD(rsp->dma));
	mcp->mb[6] = MSW(MSD(rsp->dma));
	mcp->mb[7] = LSW(MSD(rsp->dma));
	mcp->mb[5] = rsp->length;
	mcp->mb[14] = rsp->msix->entry;
	mcp->mb[13] = rsp->rid;
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->mb[15] = 0;

	mcp->mb[4] = rsp->id;
	/* que in ptr index */
	mcp->mb[8] = *rsp->in_ptr = 0;
	/* que out ptr index */
	mcp->mb[9] = 0;
	mcp->out_mb = MBX_14|MBX_13|MBX_9|MBX_8|MBX_7
			|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->flags = MBX_DMA_OUT;
	mcp->tov = MBX_TOV_SECONDS * 2;

	अगर (IS_QLA81XX(ha)) अणु
		mcp->out_mb |= MBX_12|MBX_11|MBX_10;
		mcp->in_mb |= MBX_1;
	पूर्ण अन्यथा अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
		mcp->out_mb |= MBX_15|MBX_12|MBX_11|MBX_10;
		mcp->in_mb |= MBX_1;
		/* debug q create issue in SR-IOV */
		mcp->in_mb |= MBX_9 | MBX_8 | MBX_7;
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);
	अगर (!(rsp->options & BIT_0)) अणु
		wrt_reg_dword(rsp->rsp_q_out, 0);
		अगर (!IS_QLA83XX(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
			wrt_reg_dword(rsp->rsp_q_in, 0);
	पूर्ण

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10d7,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d8,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_idc_ack(scsi_qla_host_t *vha, uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10d9,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_IDC_ACK;
	स_नकल(&mcp->mb[1], mb, QLA_IDC_ACK_REGS * माप(uपूर्णांक16_t));
	mcp->out_mb = MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10da,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10db,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_fac_get_sector_size(scsi_qla_host_t *vha, uपूर्णांक32_t *sector_size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10dc,
	    "Entered %s.\n", __func__);

	अगर (!IS_QLA81XX(vha->hw) && !IS_QLA83XX(vha->hw) &&
	    !IS_QLA27XX(vha->hw) && !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_FLASH_ACCESS_CTRL;
	mcp->mb[1] = FAC_OPT_CMD_GET_SECTOR_SIZE;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10dd,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10de,
		    "Done %s.\n", __func__);
		*sector_size = mcp->mb[1];
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_fac_करो_ग_लिखो_enable(scsi_qla_host_t *vha, पूर्णांक enable)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA81XX(vha->hw) && !IS_QLA83XX(vha->hw) &&
	    !IS_QLA27XX(vha->hw) && !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10df,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_FLASH_ACCESS_CTRL;
	mcp->mb[1] = enable ? FAC_OPT_CMD_WRITE_ENABLE :
	    FAC_OPT_CMD_WRITE_PROTECT;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e0,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e1,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_fac_erase_sector(scsi_qla_host_t *vha, uपूर्णांक32_t start, uपूर्णांक32_t finish)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA81XX(vha->hw) && !IS_QLA83XX(vha->hw) &&
	    !IS_QLA27XX(vha->hw) && !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e2,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_FLASH_ACCESS_CTRL;
	mcp->mb[1] = FAC_OPT_CMD_ERASE_SECTOR;
	mcp->mb[2] = LSW(start);
	mcp->mb[3] = MSW(start);
	mcp->mb[4] = LSW(finish);
	mcp->mb[5] = MSW(finish);
	mcp->out_mb = MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e3,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e4,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_fac_semaphore_access(scsi_qla_host_t *vha, पूर्णांक lock)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA81XX(ha) && !IS_QLA83XX(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस rval;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e2,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_FLASH_ACCESS_CTRL;
	mcp->mb[1] = (lock ? FAC_OPT_CMD_LOCK_SEMAPHORE :
	    FAC_OPT_CMD_UNLOCK_SEMAPHORE);
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e3,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e4,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_restart_mpi_firmware(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval = 0;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e5,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_RESTART_MPI_FW;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_0|MBX_1;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e6,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e7,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla82xx_set_driver_version(scsi_qla_host_t *vha, अक्षर *version)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	पूर्णांक i;
	पूर्णांक len;
	__le16 *str;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_P3P_TYPE(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x117b,
	    "Entered %s.\n", __func__);

	str = (__क्रमce __le16 *)version;
	len = म_माप(version);

	mcp->mb[0] = MBC_SET_RNID_PARAMS;
	mcp->mb[1] = RNID_TYPE_SET_VERSION << 8;
	mcp->out_mb = MBX_1|MBX_0;
	क्रम (i = 4; i < 16 && len; i++, str++, len -= 2) अणु
		mcp->mb[i] = le16_to_cpup(str);
		mcp->out_mb |= 1<<i;
	पूर्ण
	क्रम (; i < 16; i++) अणु
		mcp->mb[i] = 0;
		mcp->out_mb |= 1<<i;
	पूर्ण
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x117c,
		    "Failed=%x mb[0]=%x,%x.\n", rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x117d,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla25xx_set_driver_version(scsi_qla_host_t *vha, अक्षर *version)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	पूर्णांक len;
	uपूर्णांक16_t dwlen;
	uपूर्णांक8_t *str;
	dma_addr_t str_dma;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_FWI2_CAPABLE(ha) || IS_QLA24XX_TYPE(ha) || IS_QLA81XX(ha) ||
	    IS_P3P_TYPE(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x117e,
	    "Entered %s.\n", __func__);

	str = dma_pool_alloc(ha->s_dma_pool, GFP_KERNEL, &str_dma);
	अगर (!str) अणु
		ql_log(ql_log_warn, vha, 0x117f,
		    "Failed to allocate driver version param.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	स_नकल(str, "\x7\x3\x11\x0", 4);
	dwlen = str[0];
	len = dwlen * 4 - 4;
	स_रखो(str + 4, 0, len);
	अगर (len > म_माप(version))
		len = म_माप(version);
	स_नकल(str + 4, version, len);

	mcp->mb[0] = MBC_SET_RNID_PARAMS;
	mcp->mb[1] = RNID_TYPE_SET_VERSION << 8 | dwlen;
	mcp->mb[2] = MSW(LSD(str_dma));
	mcp->mb[3] = LSW(LSD(str_dma));
	mcp->mb[6] = MSW(MSD(str_dma));
	mcp->mb[7] = LSW(MSD(str_dma));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1180,
		    "Failed=%x mb[0]=%x,%x.\n", rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1181,
		    "Done %s.\n", __func__);
	पूर्ण

	dma_pool_मुक्त(ha->s_dma_pool, str, str_dma);

	वापस rval;
पूर्ण

पूर्णांक
qla24xx_get_port_login_templ(scsi_qla_host_t *vha, dma_addr_t buf_dma,
			     व्योम *buf, uपूर्णांक16_t bufsiz)
अणु
	पूर्णांक rval, i;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	uपूर्णांक32_t	*bp;

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1159,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_RNID_PARAMS;
	mcp->mb[1] = RNID_TYPE_PORT_LOGIN << 8;
	mcp->mb[2] = MSW(buf_dma);
	mcp->mb[3] = LSW(buf_dma);
	mcp->mb[6] = MSW(MSD(buf_dma));
	mcp->mb[7] = LSW(MSD(buf_dma));
	mcp->mb[8] = bufsiz/4;
	mcp->out_mb = MBX_8|MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x115a,
		    "Failed=%x mb[0]=%x,%x.\n", rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x115b,
		    "Done %s.\n", __func__);
		bp = (uपूर्णांक32_t *) buf;
		क्रम (i = 0; i < (bufsiz-4)/4; i++, bp++)
			*bp = le32_to_cpu((__क्रमce __le32)*bp);
	पूर्ण

	वापस rval;
पूर्ण

#घोषणा PUREX_CMD_COUNT	2
पूर्णांक
qla25xx_set_els_cmds_supported(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	uपूर्णांक8_t *els_cmd_map;
	dma_addr_t els_cmd_map_dma;
	uपूर्णांक8_t cmd_opcode[PUREX_CMD_COUNT];
	uपूर्णांक8_t i, index, purex_bit;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA25XX(ha) && !IS_QLA2031(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_SUCCESS;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1197,
	    "Entered %s.\n", __func__);

	els_cmd_map = dma_alloc_coherent(&ha->pdev->dev, ELS_CMD_MAP_SIZE,
	    &els_cmd_map_dma, GFP_KERNEL);
	अगर (!els_cmd_map) अणु
		ql_log(ql_log_warn, vha, 0x7101,
		    "Failed to allocate RDP els command param.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	/* List of Purex ELS */
	cmd_opcode[0] = ELS_FPIN;
	cmd_opcode[1] = ELS_RDP;

	क्रम (i = 0; i < PUREX_CMD_COUNT; i++) अणु
		index = cmd_opcode[i] / 8;
		purex_bit = cmd_opcode[i] % 8;
		els_cmd_map[index] |= 1 << purex_bit;
	पूर्ण

	mcp->mb[0] = MBC_SET_RNID_PARAMS;
	mcp->mb[1] = RNID_TYPE_ELS_CMD << 8;
	mcp->mb[2] = MSW(LSD(els_cmd_map_dma));
	mcp->mb[3] = LSW(LSD(els_cmd_map_dma));
	mcp->mb[6] = MSW(MSD(els_cmd_map_dma));
	mcp->mb[7] = LSW(MSD(els_cmd_map_dma));
	mcp->out_mb = MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = MBX_DMA_OUT;
	mcp->buf_size = ELS_CMD_MAP_SIZE;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x118d,
		    "Failed=%x (%x,%x).\n", rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x118c,
		    "Done %s.\n", __func__);
	पूर्ण

	dma_मुक्त_coherent(&ha->pdev->dev, ELS_CMD_MAP_SIZE,
	   els_cmd_map, els_cmd_map_dma);

	वापस rval;
पूर्ण

अटल पूर्णांक
qla2x00_पढ़ो_asic_temperature(scsi_qla_host_t *vha, uपूर्णांक16_t *temp)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1159,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_GET_RNID_PARAMS;
	mcp->mb[1] = RNID_TYPE_ASIC_TEMP << 8;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	*temp = mcp->mb[1];

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x115a,
		    "Failed=%x mb[0]=%x,%x.\n", rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x115b,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_पढ़ो_sfp(scsi_qla_host_t *vha, dma_addr_t sfp_dma, uपूर्णांक8_t *sfp,
	uपूर्णांक16_t dev, uपूर्णांक16_t off, uपूर्णांक16_t len, uपूर्णांक16_t opt)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e8,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	अगर (len == 1)
		opt |= BIT_0;

	mcp->mb[0] = MBC_READ_SFP;
	mcp->mb[1] = dev;
	mcp->mb[2] = MSW(LSD(sfp_dma));
	mcp->mb[3] = LSW(LSD(sfp_dma));
	mcp->mb[6] = MSW(MSD(sfp_dma));
	mcp->mb[7] = LSW(MSD(sfp_dma));
	mcp->mb[8] = len;
	mcp->mb[9] = off;
	mcp->mb[10] = opt;
	mcp->out_mb = MBX_10|MBX_9|MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (opt & BIT_0)
		*sfp = mcp->mb[1];

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e9,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
		अगर (mcp->mb[0] == MBS_COMMAND_ERROR && mcp->mb[1] == 0x22) अणु
			/* sfp is not there */
			rval = QLA_INTERFACE_ERROR;
		पूर्ण
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ea,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_ग_लिखो_sfp(scsi_qla_host_t *vha, dma_addr_t sfp_dma, uपूर्णांक8_t *sfp,
	uपूर्णांक16_t dev, uपूर्णांक16_t off, uपूर्णांक16_t len, uपूर्णांक16_t opt)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10eb,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	अगर (len == 1)
		opt |= BIT_0;

	अगर (opt & BIT_0)
		len = *sfp;

	mcp->mb[0] = MBC_WRITE_SFP;
	mcp->mb[1] = dev;
	mcp->mb[2] = MSW(LSD(sfp_dma));
	mcp->mb[3] = LSW(LSD(sfp_dma));
	mcp->mb[6] = MSW(MSD(sfp_dma));
	mcp->mb[7] = LSW(MSD(sfp_dma));
	mcp->mb[8] = len;
	mcp->mb[9] = off;
	mcp->mb[10] = opt;
	mcp->out_mb = MBX_10|MBX_9|MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10ec,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ed,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_get_xgmac_stats(scsi_qla_host_t *vha, dma_addr_t stats_dma,
    uपूर्णांक16_t size_in_bytes, uपूर्णांक16_t *actual_size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ee,
	    "Entered %s.\n", __func__);

	अगर (!IS_CNA_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_GET_XGMAC_STATS;
	mcp->mb[2] = MSW(stats_dma);
	mcp->mb[3] = LSW(stats_dma);
	mcp->mb[6] = MSW(MSD(stats_dma));
	mcp->mb[7] = LSW(MSD(stats_dma));
	mcp->mb[8] = size_in_bytes >> 2;
	mcp->out_mb = MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10ef,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f0,
		    "Done %s.\n", __func__);


		*actual_size = mcp->mb[2] << 2;
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_get_dcbx_params(scsi_qla_host_t *vha, dma_addr_t tlv_dma,
    uपूर्णांक16_t size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f1,
	    "Entered %s.\n", __func__);

	अगर (!IS_CNA_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_GET_DCBX_PARAMS;
	mcp->mb[1] = 0;
	mcp->mb[2] = MSW(tlv_dma);
	mcp->mb[3] = LSW(tlv_dma);
	mcp->mb[6] = MSW(MSD(tlv_dma));
	mcp->mb[7] = LSW(MSD(tlv_dma));
	mcp->mb[8] = size;
	mcp->out_mb = MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10f2,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f3,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_पढ़ो_ram_word(scsi_qla_host_t *vha, uपूर्णांक32_t risc_addr, uपूर्णांक32_t *data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f4,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_READ_RAM_EXTENDED;
	mcp->mb[1] = LSW(risc_addr);
	mcp->mb[8] = MSW(risc_addr);
	mcp->out_mb = MBX_8|MBX_1|MBX_0;
	mcp->in_mb = MBX_3|MBX_2|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10f5,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f6,
		    "Done %s.\n", __func__);
		*data = mcp->mb[3] << 16 | mcp->mb[2];
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_loopback_test(scsi_qla_host_t *vha, काष्ठा msg_echo_lb *mreq,
	uपूर्णांक16_t *mresp)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f7,
	    "Entered %s.\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_DIAGNOSTIC_LOOP_BACK;
	mcp->mb[1] = mreq->options | BIT_6;	// BIT_6 specअगरies 64 bit addressing

	/* transfer count */
	mcp->mb[10] = LSW(mreq->transfer_size);
	mcp->mb[11] = MSW(mreq->transfer_size);

	/* send data address */
	mcp->mb[14] = LSW(mreq->send_dma);
	mcp->mb[15] = MSW(mreq->send_dma);
	mcp->mb[20] = LSW(MSD(mreq->send_dma));
	mcp->mb[21] = MSW(MSD(mreq->send_dma));

	/* receive data address */
	mcp->mb[16] = LSW(mreq->rcv_dma);
	mcp->mb[17] = MSW(mreq->rcv_dma);
	mcp->mb[6] = LSW(MSD(mreq->rcv_dma));
	mcp->mb[7] = MSW(MSD(mreq->rcv_dma));

	/* Iteration count */
	mcp->mb[18] = LSW(mreq->iteration_count);
	mcp->mb[19] = MSW(mreq->iteration_count);

	mcp->out_mb = MBX_21|MBX_20|MBX_19|MBX_18|MBX_17|MBX_16|MBX_15|
	    MBX_14|MBX_13|MBX_12|MBX_11|MBX_10|MBX_7|MBX_6|MBX_1|MBX_0;
	अगर (IS_CNA_CAPABLE(vha->hw))
		mcp->out_mb |= MBX_2;
	mcp->in_mb = MBX_19|MBX_18|MBX_3|MBX_2|MBX_1|MBX_0;

	mcp->buf_size = mreq->transfer_size;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = MBX_DMA_OUT|MBX_DMA_IN|IOCTL_CMD;

	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10f8,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x mb[3]=%x mb[18]=%x "
		    "mb[19]=%x.\n", rval, mcp->mb[0], mcp->mb[1], mcp->mb[2],
		    mcp->mb[3], mcp->mb[18], mcp->mb[19]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10f9,
		    "Done %s.\n", __func__);
	पूर्ण

	/* Copy mailbox inक्रमmation */
	स_नकल( mresp, mcp->mb, 64);
	वापस rval;
पूर्ण

पूर्णांक
qla2x00_echo_test(scsi_qla_host_t *vha, काष्ठा msg_echo_lb *mreq,
	uपूर्णांक16_t *mresp)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10fa,
	    "Entered %s.\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_DIAGNOSTIC_ECHO;
	/* BIT_6 specअगरies 64bit address */
	mcp->mb[1] = mreq->options | BIT_15 | BIT_6;
	अगर (IS_CNA_CAPABLE(ha)) अणु
		mcp->mb[2] = vha->fcoe_fcf_idx;
	पूर्ण
	mcp->mb[16] = LSW(mreq->rcv_dma);
	mcp->mb[17] = MSW(mreq->rcv_dma);
	mcp->mb[6] = LSW(MSD(mreq->rcv_dma));
	mcp->mb[7] = MSW(MSD(mreq->rcv_dma));

	mcp->mb[10] = LSW(mreq->transfer_size);

	mcp->mb[14] = LSW(mreq->send_dma);
	mcp->mb[15] = MSW(mreq->send_dma);
	mcp->mb[20] = LSW(MSD(mreq->send_dma));
	mcp->mb[21] = MSW(MSD(mreq->send_dma));

	mcp->out_mb = MBX_21|MBX_20|MBX_17|MBX_16|MBX_15|
	    MBX_14|MBX_10|MBX_7|MBX_6|MBX_1|MBX_0;
	अगर (IS_CNA_CAPABLE(ha))
		mcp->out_mb |= MBX_2;

	mcp->in_mb = MBX_0;
	अगर (IS_CNA_CAPABLE(ha) || IS_QLA24XX_TYPE(ha) || IS_QLA25XX(ha) ||
	    IS_QLA2031(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->in_mb |= MBX_1;
	अगर (IS_CNA_CAPABLE(ha) || IS_QLA2031(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha))
		mcp->in_mb |= MBX_3;

	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = MBX_DMA_OUT|MBX_DMA_IN|IOCTL_CMD;
	mcp->buf_size = mreq->transfer_size;

	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10fb,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10fc,
		    "Done %s.\n", __func__);
	पूर्ण

	/* Copy mailbox inक्रमmation */
	स_नकल(mresp, mcp->mb, 64);
	वापस rval;
पूर्ण

पूर्णांक
qla84xx_reset_chip(scsi_qla_host_t *vha, uपूर्णांक16_t enable_diagnostic)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10fd,
	    "Entered %s enable_diag=%d.\n", __func__, enable_diagnostic);

	mcp->mb[0] = MBC_ISP84XX_RESET;
	mcp->mb[1] = enable_diagnostic;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = MBX_DMA_OUT|MBX_DMA_IN|IOCTL_CMD;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS)
		ql_dbg(ql_dbg_mbx, vha, 0x10fe, "Failed=%x.\n", rval);
	अन्यथा
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ff,
		    "Done %s.\n", __func__);

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_ग_लिखो_ram_word(scsi_qla_host_t *vha, uपूर्णांक32_t risc_addr, uपूर्णांक32_t data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1100,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_WRITE_RAM_WORD_EXTENDED;
	mcp->mb[1] = LSW(risc_addr);
	mcp->mb[2] = LSW(data);
	mcp->mb[3] = MSW(data);
	mcp->mb[8] = MSW(risc_addr);
	mcp->out_mb = MBX_8|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1101,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1102,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_ग_लिखो_mpi_रेजिस्टर(scsi_qla_host_t *vha, uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	uपूर्णांक32_t stat, समयr;
	uपूर्णांक16_t mb0 = 0;
	काष्ठा qla_hw_data *ha = vha->hw;
	काष्ठा device_reg_24xx __iomem *reg = &ha->iobase->isp24;

	rval = QLA_SUCCESS;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1103,
	    "Entered %s.\n", __func__);

	clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);

	/* Write the MBC data to the रेजिस्टरs */
	wrt_reg_word(&reg->mailbox0, MBC_WRITE_MPI_REGISTER);
	wrt_reg_word(&reg->mailbox1, mb[0]);
	wrt_reg_word(&reg->mailbox2, mb[1]);
	wrt_reg_word(&reg->mailbox3, mb[2]);
	wrt_reg_word(&reg->mailbox4, mb[3]);

	wrt_reg_dword(&reg->hccr, HCCRX_SET_HOST_INT);

	/* Poll क्रम MBC पूर्णांकerrupt */
	क्रम (समयr = 6000000; समयr; समयr--) अणु
		/* Check क्रम pending पूर्णांकerrupts. */
		stat = rd_reg_dword(&reg->host_status);
		अगर (stat & HSRX_RISC_INT) अणु
			stat &= 0xff;

			अगर (stat == 0x1 || stat == 0x2 ||
			    stat == 0x10 || stat == 0x11) अणु
				set_bit(MBX_INTERRUPT,
				    &ha->mbx_cmd_flags);
				mb0 = rd_reg_word(&reg->mailbox0);
				wrt_reg_dword(&reg->hccr,
				    HCCRX_CLR_RISC_INT);
				rd_reg_dword(&reg->hccr);
				अवरोध;
			पूर्ण
		पूर्ण
		udelay(5);
	पूर्ण

	अगर (test_and_clear_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags))
		rval = mb0 & MBS_MASK;
	अन्यथा
		rval = QLA_FUNCTION_FAILED;

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1104,
		    "Failed=%x mb[0]=%x.\n", rval, mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1105,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

/* Set the specअगरied data rate */
पूर्णांक
qla2x00_set_data_rate(scsi_qla_host_t *vha, uपूर्णांक16_t mode)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t val;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1106,
	    "Entered %s speed:0x%x mode:0x%x.\n", __func__, ha->set_data_rate,
	    mode);

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	स_रखो(mcp, 0, माप(*mcp));
	चयन (ha->set_data_rate) अणु
	हाल PORT_SPEED_AUTO:
	हाल PORT_SPEED_4GB:
	हाल PORT_SPEED_8GB:
	हाल PORT_SPEED_16GB:
	हाल PORT_SPEED_32GB:
		val = ha->set_data_rate;
		अवरोध;
	शेष:
		ql_log(ql_log_warn, vha, 0x1199,
		    "Unrecognized speed setting:%d. Setting Autoneg\n",
		    ha->set_data_rate);
		val = ha->set_data_rate = PORT_SPEED_AUTO;
		अवरोध;
	पूर्ण

	mcp->mb[0] = MBC_DATA_RATE;
	mcp->mb[1] = mode;
	mcp->mb[2] = val;

	mcp->out_mb = MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->in_mb |= MBX_4|MBX_3;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1107,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		अगर (mcp->mb[1] != 0x7)
			ql_dbg(ql_dbg_mbx, vha, 0x1179,
				"Speed set:0x%x\n", mcp->mb[1]);

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1108,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_get_data_rate(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1106,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_DATA_RATE;
	mcp->mb[1] = QLA_GET_DATA_RATE;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha))
		mcp->in_mb |= MBX_3;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1107,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		अगर (mcp->mb[1] != 0x7)
			ha->link_data_rate = mcp->mb[1];

		अगर (IS_QLA83XX(ha) || IS_QLA27XX(ha) || IS_QLA28XX(ha)) अणु
			अगर (mcp->mb[4] & BIT_0)
				ql_log(ql_log_info, vha, 0x11a2,
				    "FEC=enabled (data rate).\n");
		पूर्ण

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1108,
		    "Done %s.\n", __func__);
		अगर (mcp->mb[1] != 0x7)
			ha->link_data_rate = mcp->mb[1];
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_get_port_config(scsi_qla_host_t *vha, uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1109,
	    "Entered %s.\n", __func__);

	अगर (!IS_QLA81XX(ha) && !IS_QLA83XX(ha) && !IS_QLA8044(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_FUNCTION_FAILED;
	mcp->mb[0] = MBC_GET_PORT_CONFIG;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x110a,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		/* Copy all bits to preserve original value */
		स_नकल(mb, &mcp->mb[1], माप(uपूर्णांक16_t) * 4);

		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x110b,
		    "Done %s.\n", __func__);
	पूर्ण
	वापस rval;
पूर्ण

पूर्णांक
qla81xx_set_port_config(scsi_qla_host_t *vha, uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x110c,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SET_PORT_CONFIG;
	/* Copy all bits to preserve original setting */
	स_नकल(&mcp->mb[1], mb, माप(uपूर्णांक16_t) * 4);
	mcp->out_mb = MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x110d,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x110e,
		    "Done %s.\n", __func__);

	वापस rval;
पूर्ण


पूर्णांक
qla24xx_set_fcp_prio(scsi_qla_host_t *vha, uपूर्णांक16_t loop_id, uपूर्णांक16_t priority,
		uपूर्णांक16_t *mb)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x110f,
	    "Entered %s.\n", __func__);

	अगर (!IS_QLA24XX_TYPE(ha) && !IS_QLA25XX(ha))
		वापस QLA_FUNCTION_FAILED;

	mcp->mb[0] = MBC_PORT_PARAMS;
	mcp->mb[1] = loop_id;
	अगर (ha->flags.fcp_prio_enabled)
		mcp->mb[2] = BIT_1;
	अन्यथा
		mcp->mb[2] = BIT_2;
	mcp->mb[4] = priority & 0xf;
	mcp->mb[9] = vha->vp_idx;
	mcp->out_mb = MBX_9|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_4|MBX_3|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (mb != शून्य) अणु
		mb[0] = mcp->mb[0];
		mb[1] = mcp->mb[1];
		mb[3] = mcp->mb[3];
		mb[4] = mcp->mb[4];
	पूर्ण

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10cd, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10cc,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_get_thermal_temp(scsi_qla_host_t *vha, uपूर्णांक16_t *temp)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक8_t byte;

	अगर (!IS_FWI2_CAPABLE(ha) || IS_QLA24XX_TYPE(ha) || IS_QLA81XX(ha)) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1150,
		    "Thermal not supported by this card.\n");
		वापस rval;
	पूर्ण

	अगर (IS_QLA25XX(ha)) अणु
		अगर (ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_QLOGIC &&
		    ha->pdev->subप्रणाली_device == 0x0175) अणु
			rval = qla2x00_पढ़ो_sfp(vha, 0, &byte,
			    0x98, 0x1, 1, BIT_13|BIT_0);
			*temp = byte;
			वापस rval;
		पूर्ण
		अगर (ha->pdev->subप्रणाली_venकरोr == PCI_VENDOR_ID_HP &&
		    ha->pdev->subप्रणाली_device == 0x338e) अणु
			rval = qla2x00_पढ़ो_sfp(vha, 0, &byte,
			    0x98, 0x1, 1, BIT_15|BIT_14|BIT_0);
			*temp = byte;
			वापस rval;
		पूर्ण
		ql_dbg(ql_dbg_mbx, vha, 0x10c9,
		    "Thermal not supported by this card.\n");
		वापस rval;
	पूर्ण

	अगर (IS_QLA82XX(ha)) अणु
		*temp = qla82xx_पढ़ो_temperature(vha);
		rval = QLA_SUCCESS;
		वापस rval;
	पूर्ण अन्यथा अगर (IS_QLA8044(ha)) अणु
		*temp = qla8044_पढ़ो_temperature(vha);
		rval = QLA_SUCCESS;
		वापस rval;
	पूर्ण

	rval = qla2x00_पढ़ो_asic_temperature(vha, temp);
	वापस rval;
पूर्ण

पूर्णांक
qla82xx_mbx_पूर्णांकr_enable(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1017,
	    "Entered %s.\n", __func__);

	अगर (!IS_FWI2_CAPABLE(ha))
		वापस QLA_FUNCTION_FAILED;

	स_रखो(mcp, 0, माप(mbx_cmd_t));
	mcp->mb[0] = MBC_TOGGLE_INTERRUPT;
	mcp->mb[1] = 1;

	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1016,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x100e,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla82xx_mbx_पूर्णांकr_disable(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x100d,
	    "Entered %s.\n", __func__);

	अगर (!IS_P3P_TYPE(ha))
		वापस QLA_FUNCTION_FAILED;

	स_रखो(mcp, 0, माप(mbx_cmd_t));
	mcp->mb[0] = MBC_TOGGLE_INTERRUPT;
	mcp->mb[1] = 0;

	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x100c,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x100b,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla82xx_md_get_ढाँचा_size(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x111f,
	    "Entered %s.\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = LSW(MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE);
	mcp->mb[1] = MSW(MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE);
	mcp->mb[2] = LSW(RQST_TMPLT_SIZE);
	mcp->mb[3] = MSW(RQST_TMPLT_SIZE);

	mcp->out_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_14|MBX_13|MBX_12|MBX_11|MBX_10|MBX_9|MBX_8|
	    MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;

	mcp->flags = MBX_DMA_OUT|MBX_DMA_IN|IOCTL_CMD;
	mcp->tov = MBX_TOV_SECONDS;
	rval = qla2x00_mailbox_command(vha, mcp);

	/* Always copy back वापस mailbox values. */
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1120,
		    "mailbox command FAILED=0x%x, subcode=%x.\n",
		    (mcp->mb[1] << 16) | mcp->mb[0],
		    (mcp->mb[3] << 16) | mcp->mb[2]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1121,
		    "Done %s.\n", __func__);
		ha->md_ढाँचा_size = ((mcp->mb[3] << 16) | mcp->mb[2]);
		अगर (!ha->md_ढाँचा_size) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1122,
			    "Null template size obtained.\n");
			rval = QLA_FUNCTION_FAILED;
		पूर्ण
	पूर्ण
	वापस rval;
पूर्ण

पूर्णांक
qla82xx_md_get_ढाँचा(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	पूर्णांक rval = QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1123,
	    "Entered %s.\n", __func__);

	ha->md_पंचांगplt_hdr = dma_alloc_coherent(&ha->pdev->dev,
	   ha->md_ढाँचा_size, &ha->md_पंचांगplt_hdr_dma, GFP_KERNEL);
	अगर (!ha->md_पंचांगplt_hdr) अणु
		ql_log(ql_log_warn, vha, 0x1124,
		    "Unable to allocate memory for Minidump template.\n");
		वापस rval;
	पूर्ण

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = LSW(MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE);
	mcp->mb[1] = MSW(MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE);
	mcp->mb[2] = LSW(RQST_TMPLT);
	mcp->mb[3] = MSW(RQST_TMPLT);
	mcp->mb[4] = LSW(LSD(ha->md_पंचांगplt_hdr_dma));
	mcp->mb[5] = MSW(LSD(ha->md_पंचांगplt_hdr_dma));
	mcp->mb[6] = LSW(MSD(ha->md_पंचांगplt_hdr_dma));
	mcp->mb[7] = MSW(MSD(ha->md_पंचांगplt_hdr_dma));
	mcp->mb[8] = LSW(ha->md_ढाँचा_size);
	mcp->mb[9] = MSW(ha->md_ढाँचा_size);

	mcp->flags = MBX_DMA_OUT|MBX_DMA_IN|IOCTL_CMD;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->out_mb = MBX_11|MBX_10|MBX_9|MBX_8|
	    MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1125,
		    "mailbox command FAILED=0x%x, subcode=%x.\n",
		    ((mcp->mb[1] << 16) | mcp->mb[0]),
		    ((mcp->mb[3] << 16) | mcp->mb[2]));
	पूर्ण अन्यथा
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1126,
		    "Done %s.\n", __func__);
	वापस rval;
पूर्ण

पूर्णांक
qla8044_md_get_ढाँचा(scsi_qla_host_t *vha)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	पूर्णांक offset = 0, size = MINIDUMP_SIZE_36K;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0xb11f,
	    "Entered %s.\n", __func__);

	ha->md_पंचांगplt_hdr = dma_alloc_coherent(&ha->pdev->dev,
	   ha->md_ढाँचा_size, &ha->md_पंचांगplt_hdr_dma, GFP_KERNEL);
	अगर (!ha->md_पंचांगplt_hdr) अणु
		ql_log(ql_log_warn, vha, 0xb11b,
		    "Unable to allocate memory for Minidump template.\n");
		वापस rval;
	पूर्ण

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	जबतक (offset < ha->md_ढाँचा_size) अणु
		mcp->mb[0] = LSW(MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE);
		mcp->mb[1] = MSW(MBC_DIAGNOSTIC_MINIDUMP_TEMPLATE);
		mcp->mb[2] = LSW(RQST_TMPLT);
		mcp->mb[3] = MSW(RQST_TMPLT);
		mcp->mb[4] = LSW(LSD(ha->md_पंचांगplt_hdr_dma + offset));
		mcp->mb[5] = MSW(LSD(ha->md_पंचांगplt_hdr_dma + offset));
		mcp->mb[6] = LSW(MSD(ha->md_पंचांगplt_hdr_dma + offset));
		mcp->mb[7] = MSW(MSD(ha->md_पंचांगplt_hdr_dma + offset));
		mcp->mb[8] = LSW(size);
		mcp->mb[9] = MSW(size);
		mcp->mb[10] = offset & 0x0000FFFF;
		mcp->mb[11] = offset & 0xFFFF0000;
		mcp->flags = MBX_DMA_OUT|MBX_DMA_IN|IOCTL_CMD;
		mcp->tov = MBX_TOV_SECONDS;
		mcp->out_mb = MBX_11|MBX_10|MBX_9|MBX_8|
			MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
		mcp->in_mb = MBX_3|MBX_2|MBX_1|MBX_0;
		rval = qla2x00_mailbox_command(vha, mcp);

		अगर (rval != QLA_SUCCESS) अणु
			ql_dbg(ql_dbg_mbx, vha, 0xb11c,
				"mailbox command FAILED=0x%x, subcode=%x.\n",
				((mcp->mb[1] << 16) | mcp->mb[0]),
				((mcp->mb[3] << 16) | mcp->mb[2]));
			वापस rval;
		पूर्ण अन्यथा
			ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0xb11d,
				"Done %s.\n", __func__);
		offset = offset + size;
	पूर्ण
	वापस rval;
पूर्ण

पूर्णांक
qla81xx_set_led_config(scsi_qla_host_t *vha, uपूर्णांक16_t *led_cfg)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA81XX(ha) && !IS_QLA8031(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1133,
	    "Entered %s.\n", __func__);

	स_रखो(mcp, 0, माप(mbx_cmd_t));
	mcp->mb[0] = MBC_SET_LED_CONFIG;
	mcp->mb[1] = led_cfg[0];
	mcp->mb[2] = led_cfg[1];
	अगर (IS_QLA8031(ha)) अणु
		mcp->mb[3] = led_cfg[2];
		mcp->mb[4] = led_cfg[3];
		mcp->mb[5] = led_cfg[4];
		mcp->mb[6] = led_cfg[5];
	पूर्ण

	mcp->out_mb = MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA8031(ha))
		mcp->out_mb |= MBX_6|MBX_5|MBX_4|MBX_3;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1134,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1135,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla81xx_get_led_config(scsi_qla_host_t *vha, uपूर्णांक16_t *led_cfg)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA81XX(ha) && !IS_QLA8031(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1136,
	    "Entered %s.\n", __func__);

	स_रखो(mcp, 0, माप(mbx_cmd_t));
	mcp->mb[0] = MBC_GET_LED_CONFIG;

	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	अगर (IS_QLA8031(ha))
		mcp->in_mb |= MBX_6|MBX_5|MBX_4|MBX_3;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1137,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		led_cfg[0] = mcp->mb[1];
		led_cfg[1] = mcp->mb[2];
		अगर (IS_QLA8031(ha)) अणु
			led_cfg[2] = mcp->mb[3];
			led_cfg[3] = mcp->mb[4];
			led_cfg[4] = mcp->mb[5];
			led_cfg[5] = mcp->mb[6];
		पूर्ण
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1138,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla82xx_mbx_beacon_ctl(scsi_qla_host_t *vha, पूर्णांक enable)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_P3P_TYPE(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1127,
		"Entered %s.\n", __func__);

	स_रखो(mcp, 0, माप(mbx_cmd_t));
	mcp->mb[0] = MBC_SET_LED_CONFIG;
	अगर (enable)
		mcp->mb[7] = 0xE;
	अन्यथा
		mcp->mb[7] = 0xD;

	mcp->out_mb = MBX_7|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1128,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1129,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla83xx_wr_reg(scsi_qla_host_t *vha, uपूर्णांक32_t reg, uपूर्णांक32_t data)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_QLA83XX(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1130,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_WRITE_REMOTE_REG;
	mcp->mb[1] = LSW(reg);
	mcp->mb[2] = MSW(reg);
	mcp->mb[3] = LSW(data);
	mcp->mb[4] = MSW(data);
	mcp->out_mb = MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;

	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1131,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1132,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_port_logout(scsi_qla_host_t *vha, काष्ठा fc_port *fcport)
अणु
	पूर्णांक rval;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (IS_QLA2100(ha) || IS_QLA2200(ha)) अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x113b,
		    "Implicit LOGO Unsupported.\n");
		वापस QLA_FUNCTION_FAILED;
	पूर्ण


	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x113c,
	    "Entering %s.\n",  __func__);

	/* Perक्रमm Implicit LOGO. */
	mcp->mb[0] = MBC_PORT_LOGOUT;
	mcp->mb[1] = fcport->loop_id;
	mcp->mb[10] = BIT_15;
	mcp->out_mb = MBX_10|MBX_1|MBX_0;
	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval != QLA_SUCCESS)
		ql_dbg(ql_dbg_mbx, vha, 0x113d,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	अन्यथा
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x113e,
		    "Done %s.\n", __func__);

	वापस rval;
पूर्ण

पूर्णांक
qla83xx_rd_reg(scsi_qla_host_t *vha, uपूर्णांक32_t reg, uपूर्णांक32_t *data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;
	अचिन्हित दीर्घ retry_max_समय = jअगरfies + (2 * HZ);

	अगर (!IS_QLA83XX(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx, vha, 0x114b, "Entered %s.\n", __func__);

retry_rd_reg:
	mcp->mb[0] = MBC_READ_REMOTE_REG;
	mcp->mb[1] = LSW(reg);
	mcp->mb[2] = MSW(reg);
	mcp->out_mb = MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_4|MBX_3|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x114c,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
	पूर्ण अन्यथा अणु
		*data = (mcp->mb[3] | (mcp->mb[4] << 16));
		अगर (*data == QLA8XXX_BAD_VALUE) अणु
			/*
			 * During soft-reset CAMRAM रेजिस्टर पढ़ोs might
			 * वापस 0xbad0bad0. So retry क्रम MAX of 2 sec
			 * जबतक पढ़ोing camram रेजिस्टरs.
			 */
			अगर (समय_after(jअगरfies, retry_max_समय)) अणु
				ql_dbg(ql_dbg_mbx, vha, 0x1141,
				    "Failure to read CAMRAM register. "
				    "data=0x%x.\n", *data);
				वापस QLA_FUNCTION_FAILED;
			पूर्ण
			msleep(100);
			जाओ retry_rd_reg;
		पूर्ण
		ql_dbg(ql_dbg_mbx, vha, 0x1142, "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla83xx_restart_nic_firmware(scsi_qla_host_t *vha)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA83XX(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx, vha, 0x1143, "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_RESTART_NIC_FIRMWARE;
	mcp->out_mb = MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1144,
		    "Failed=%x mb[0]=%x mb[1]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1]);
		qla2xxx_dump_fw(vha);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1145, "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla83xx_access_control(scsi_qla_host_t *vha, uपूर्णांक16_t options,
	uपूर्णांक32_t start_addr, uपूर्णांक32_t end_addr, uपूर्णांक16_t *sector_size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	uपूर्णांक8_t subcode = (uपूर्णांक8_t)options;
	काष्ठा qla_hw_data *ha = vha->hw;

	अगर (!IS_QLA8031(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx, vha, 0x1146, "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_SET_ACCESS_CONTROL;
	mcp->mb[1] = options;
	mcp->out_mb = MBX_1|MBX_0;
	अगर (subcode & BIT_2) अणु
		mcp->mb[2] = LSW(start_addr);
		mcp->mb[3] = MSW(start_addr);
		mcp->mb[4] = LSW(end_addr);
		mcp->mb[5] = MSW(end_addr);
		mcp->out_mb |= MBX_5|MBX_4|MBX_3|MBX_2;
	पूर्ण
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	अगर (!(subcode & (BIT_2 | BIT_5)))
		mcp->in_mb |= MBX_4|MBX_3;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1147,
		    "Failed=%x mb[0]=%x mb[1]=%x mb[2]=%x mb[3]=%x mb[4]=%x.\n",
		    rval, mcp->mb[0], mcp->mb[1], mcp->mb[2], mcp->mb[3],
		    mcp->mb[4]);
		qla2xxx_dump_fw(vha);
	पूर्ण अन्यथा अणु
		अगर (subcode & BIT_5)
			*sector_size = mcp->mb[1];
		अन्यथा अगर (subcode & (BIT_6 | BIT_7)) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1148,
			    "Driver-lock id=%x%x", mcp->mb[4], mcp->mb[3]);
		पूर्ण अन्यथा अगर (subcode & (BIT_3 | BIT_4)) अणु
			ql_dbg(ql_dbg_mbx, vha, 0x1149,
			    "Flash-lock id=%x%x", mcp->mb[4], mcp->mb[3]);
		पूर्ण
		ql_dbg(ql_dbg_mbx, vha, 0x114a, "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_dump_mctp_data(scsi_qla_host_t *vha, dma_addr_t req_dma, uपूर्णांक32_t addr,
	uपूर्णांक32_t size)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	अगर (!IS_MCTP_CAPABLE(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x114f,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_DUMP_RISC_RAM_EXTENDED;
	mcp->mb[1] = LSW(addr);
	mcp->mb[2] = MSW(req_dma);
	mcp->mb[3] = LSW(req_dma);
	mcp->mb[4] = MSW(size);
	mcp->mb[5] = LSW(size);
	mcp->mb[6] = MSW(MSD(req_dma));
	mcp->mb[7] = LSW(MSD(req_dma));
	mcp->mb[8] = MSW(addr);
	/* Setting RAM ID to valid */
	/* For MCTP RAM ID is 0x40 */
	mcp->mb[10] = BIT_7 | 0x40;

	mcp->out_mb |= MBX_10|MBX_8|MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|
	    MBX_0;

	mcp->in_mb = MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x114e,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x114d,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
qla26xx_dport_diagnostics(scsi_qla_host_t *vha,
	व्योम *dd_buf, uपूर्णांक size, uपूर्णांक options)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	dma_addr_t dd_dma;

	अगर (!IS_QLA83XX(vha->hw) && !IS_QLA27XX(vha->hw) &&
	    !IS_QLA28XX(vha->hw))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x119f,
	    "Entered %s.\n", __func__);

	dd_dma = dma_map_single(&vha->hw->pdev->dev,
	    dd_buf, size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&vha->hw->pdev->dev, dd_dma)) अणु
		ql_log(ql_log_warn, vha, 0x1194, "Failed to map dma buffer.\n");
		वापस QLA_MEMORY_ALLOC_FAILED;
	पूर्ण

	स_रखो(dd_buf, 0, size);

	mcp->mb[0] = MBC_DPORT_DIAGNOSTICS;
	mcp->mb[1] = options;
	mcp->mb[2] = MSW(LSD(dd_dma));
	mcp->mb[3] = LSW(LSD(dd_dma));
	mcp->mb[6] = MSW(MSD(dd_dma));
	mcp->mb[7] = LSW(MSD(dd_dma));
	mcp->mb[8] = size;
	mcp->out_mb = MBX_8|MBX_7|MBX_6|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->buf_size = size;
	mcp->flags = MBX_DMA_IN;
	mcp->tov = MBX_TOV_SECONDS * 4;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1195, "Failed=%x.\n", rval);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1196,
		    "Done %s.\n", __func__);
	पूर्ण

	dma_unmap_single(&vha->hw->pdev->dev, dd_dma,
	    size, DMA_FROM_DEVICE);

	वापस rval;
पूर्ण

अटल व्योम qla2x00_async_mb_sp_करोne(srb_t *sp, पूर्णांक res)
अणु
	sp->u.iocb_cmd.u.mbx.rc = res;

	complete(&sp->u.iocb_cmd.u.mbx.comp);
	/* करोn't मुक्त sp here. Let the caller करो the मुक्त */
पूर्ण

/*
 * This mailbox uses the iocb पूर्णांकerface to send MB command.
 * This allows non-critial (non chip setup) command to go
 * out in parrallel.
 */
पूर्णांक qla24xx_send_mb_cmd(काष्ठा scsi_qla_host *vha, mbx_cmd_t *mcp)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	srb_t *sp;
	काष्ठा srb_iocb *c;

	अगर (!vha->hw->flags.fw_started)
		जाओ करोne;

	sp = qla2x00_get_sp(vha, शून्य, GFP_KERNEL);
	अगर (!sp)
		जाओ करोne;

	sp->type = SRB_MB_IOCB;
	sp->name = mb_to_str(mcp->mb[0]);

	c = &sp->u.iocb_cmd;
	c->समयout = qla2x00_async_iocb_समयout;
	init_completion(&c->u.mbx.comp);

	qla2x00_init_समयr(sp, qla2x00_get_async_समयout(vha) + 2);

	स_नकल(sp->u.iocb_cmd.u.mbx.out_mb, mcp->mb, SIZखातापूर्ण_IOCB_MB_REG);

	sp->करोne = qla2x00_async_mb_sp_करोne;

	rval = qla2x00_start_sp(sp);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1018,
		    "%s: %s Failed submission. %x.\n",
		    __func__, sp->name, rval);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	ql_dbg(ql_dbg_mbx, vha, 0x113f, "MB:%s hndl %x submitted\n",
	    sp->name, sp->handle);

	रुको_क्रम_completion(&c->u.mbx.comp);
	स_नकल(mcp->mb, sp->u.iocb_cmd.u.mbx.in_mb, SIZखातापूर्ण_IOCB_MB_REG);

	rval = c->u.mbx.rc;
	चयन (rval) अणु
	हाल QLA_FUNCTION_TIMEOUT:
		ql_dbg(ql_dbg_mbx, vha, 0x1140, "%s: %s Timeout. %x.\n",
		    __func__, sp->name, rval);
		अवरोध;
	हाल  QLA_SUCCESS:
		ql_dbg(ql_dbg_mbx, vha, 0x119d, "%s: %s done.\n",
		    __func__, sp->name);
		अवरोध;
	शेष:
		ql_dbg(ql_dbg_mbx, vha, 0x119e, "%s: %s Failed. %x.\n",
		    __func__, sp->name, rval);
		अवरोध;
	पूर्ण

करोne_मुक्त_sp:
	sp->मुक्त(sp);
करोne:
	वापस rval;
पूर्ण

/*
 * qla24xx_gpdb_रुको
 * NOTE: Do not call this routine from DPC thपढ़ो
 */
पूर्णांक qla24xx_gpdb_रुको(काष्ठा scsi_qla_host *vha, fc_port_t *fcport, u8 opt)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	dma_addr_t pd_dma;
	काष्ठा port_database_24xx *pd;
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;

	अगर (!vha->hw->flags.fw_started)
		जाओ करोne;

	pd = dma_pool_zalloc(ha->s_dma_pool, GFP_KERNEL, &pd_dma);
	अगर (pd  == शून्य) अणु
		ql_log(ql_log_warn, vha, 0xd047,
		    "Failed to allocate port database structure.\n");
		जाओ करोne_मुक्त_sp;
	पूर्ण

	स_रखो(&mc, 0, माप(mc));
	mc.mb[0] = MBC_GET_PORT_DATABASE;
	mc.mb[1] = fcport->loop_id;
	mc.mb[2] = MSW(pd_dma);
	mc.mb[3] = LSW(pd_dma);
	mc.mb[6] = MSW(MSD(pd_dma));
	mc.mb[7] = LSW(MSD(pd_dma));
	mc.mb[9] = vha->vp_idx;
	mc.mb[10] = opt;

	rval = qla24xx_send_mb_cmd(vha, &mc);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x1193,
		    "%s: %8phC fail\n", __func__, fcport->port_name);
		जाओ करोne_मुक्त_sp;
	पूर्ण

	rval = __qla24xx_parse_gpdb(vha, fcport, pd);

	ql_dbg(ql_dbg_mbx, vha, 0x1197, "%s: %8phC done\n",
	    __func__, fcport->port_name);

करोne_मुक्त_sp:
	अगर (pd)
		dma_pool_मुक्त(ha->s_dma_pool, pd, pd_dma);
करोne:
	वापस rval;
पूर्ण

पूर्णांक __qla24xx_parse_gpdb(काष्ठा scsi_qla_host *vha, fc_port_t *fcport,
    काष्ठा port_database_24xx *pd)
अणु
	पूर्णांक rval = QLA_SUCCESS;
	uपूर्णांक64_t zero = 0;
	u8 current_login_state, last_login_state;

	अगर (NVME_TARGET(vha->hw, fcport)) अणु
		current_login_state = pd->current_login_state >> 4;
		last_login_state = pd->last_login_state >> 4;
	पूर्ण अन्यथा अणु
		current_login_state = pd->current_login_state & 0xf;
		last_login_state = pd->last_login_state & 0xf;
	पूर्ण

	/* Check क्रम logged in state. */
	अगर (current_login_state != PDS_PRLI_COMPLETE) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x119a,
		    "Unable to verify login-state (%x/%x) for loop_id %x.\n",
		    current_login_state, last_login_state, fcport->loop_id);
		rval = QLA_FUNCTION_FAILED;
		जाओ gpd_error_out;
	पूर्ण

	अगर (fcport->loop_id == FC_NO_LOOP_ID ||
	    (स_भेद(fcport->port_name, (uपूर्णांक8_t *)&zero, 8) &&
	     स_भेद(fcport->port_name, pd->port_name, 8))) अणु
		/* We lost the device mid way. */
		rval = QLA_NOT_LOGGED_IN;
		जाओ gpd_error_out;
	पूर्ण

	/* Names are little-endian. */
	स_नकल(fcport->node_name, pd->node_name, WWN_SIZE);
	स_नकल(fcport->port_name, pd->port_name, WWN_SIZE);

	/* Get port_id of device. */
	fcport->d_id.b.करोमुख्य = pd->port_id[0];
	fcport->d_id.b.area = pd->port_id[1];
	fcport->d_id.b.al_pa = pd->port_id[2];
	fcport->d_id.b.rsvd_1 = 0;

	अगर (NVME_TARGET(vha->hw, fcport)) अणु
		fcport->port_type = FCT_NVME;
		अगर ((pd->prli_svc_param_word_3[0] & BIT_5) == 0)
			fcport->port_type |= FCT_NVME_INITIATOR;
		अगर ((pd->prli_svc_param_word_3[0] & BIT_4) == 0)
			fcport->port_type |= FCT_NVME_TARGET;
		अगर ((pd->prli_svc_param_word_3[0] & BIT_3) == 0)
			fcport->port_type |= FCT_NVME_DISCOVERY;
	पूर्ण अन्यथा अणु
		/* If not target must be initiator or unknown type. */
		अगर ((pd->prli_svc_param_word_3[0] & BIT_4) == 0)
			fcport->port_type = FCT_INITIATOR;
		अन्यथा
			fcport->port_type = FCT_TARGET;
	पूर्ण
	/* Passback COS inक्रमmation. */
	fcport->supported_classes = (pd->flags & PDF_CLASS_2) ?
		FC_COS_CLASS2 : FC_COS_CLASS3;

	अगर (pd->prli_svc_param_word_3[0] & BIT_7) अणु
		fcport->flags |= FCF_CONF_COMP_SUPPORTED;
		fcport->conf_compl_supported = 1;
	पूर्ण

gpd_error_out:
	वापस rval;
पूर्ण

/*
 * qla24xx_gidlist__रुको
 * NOTE: करोn't call this routine from DPC thपढ़ो.
 */
पूर्णांक qla24xx_gidlist_रुको(काष्ठा scsi_qla_host *vha,
	व्योम *id_list, dma_addr_t id_list_dma, uपूर्णांक16_t *entries)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	mbx_cmd_t mc;

	अगर (!vha->hw->flags.fw_started)
		जाओ करोne;

	स_रखो(&mc, 0, माप(mc));
	mc.mb[0] = MBC_GET_ID_LIST;
	mc.mb[2] = MSW(id_list_dma);
	mc.mb[3] = LSW(id_list_dma);
	mc.mb[6] = MSW(MSD(id_list_dma));
	mc.mb[7] = LSW(MSD(id_list_dma));
	mc.mb[8] = 0;
	mc.mb[9] = vha->vp_idx;

	rval = qla24xx_send_mb_cmd(vha, &mc);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x119b,
		    "%s:  fail\n", __func__);
	पूर्ण अन्यथा अणु
		*entries = mc.mb[1];
		ql_dbg(ql_dbg_mbx, vha, 0x119c,
		    "%s:  done\n", __func__);
	पूर्ण
करोne:
	वापस rval;
पूर्ण

पूर्णांक qla27xx_set_zio_threshold(scsi_qla_host_t *vha, uपूर्णांक16_t value)
अणु
	पूर्णांक rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1200,
	    "Entered %s\n", __func__);

	स_रखो(mcp->mb, 0 , माप(mcp->mb));
	mcp->mb[0] = MBC_GET_SET_ZIO_THRESHOLD;
	mcp->mb[1] = 1;
	mcp->mb[2] = value;
	mcp->out_mb = MBX_2 | MBX_1 | MBX_0;
	mcp->in_mb = MBX_2 | MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);

	ql_dbg(ql_dbg_mbx, vha, 0x1201, "%s %x\n",
	    (rval != QLA_SUCCESS) ? "Failed"  : "Done", rval);

	वापस rval;
पूर्ण

पूर्णांक qla27xx_get_zio_threshold(scsi_qla_host_t *vha, uपूर्णांक16_t *value)
अणु
	पूर्णांक rval;
	mbx_cmd_t	mc;
	mbx_cmd_t	*mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x1203,
	    "Entered %s\n", __func__);

	स_रखो(mcp->mb, 0, माप(mcp->mb));
	mcp->mb[0] = MBC_GET_SET_ZIO_THRESHOLD;
	mcp->mb[1] = 0;
	mcp->out_mb = MBX_1 | MBX_0;
	mcp->in_mb = MBX_2 | MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;

	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval == QLA_SUCCESS)
		*value = mc.mb[2];

	ql_dbg(ql_dbg_mbx, vha, 0x1205, "%s %x\n",
	    (rval != QLA_SUCCESS) ? "Failed" : "Done", rval);

	वापस rval;
पूर्ण

पूर्णांक
qla2x00_पढ़ो_sfp_dev(काष्ठा scsi_qla_host *vha, अक्षर *buf, पूर्णांक count)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	uपूर्णांक16_t iter, addr, offset;
	dma_addr_t phys_addr;
	पूर्णांक rval, c;
	u8 *sfp_data;

	स_रखो(ha->sfp_data, 0, SFP_DEV_SIZE);
	addr = 0xa0;
	phys_addr = ha->sfp_data_dma;
	sfp_data = ha->sfp_data;
	offset = c = 0;

	क्रम (iter = 0; iter < SFP_DEV_SIZE / SFP_BLOCK_SIZE; iter++) अणु
		अगर (iter == 4) अणु
			/* Skip to next device address. */
			addr = 0xa2;
			offset = 0;
		पूर्ण

		rval = qla2x00_पढ़ो_sfp(vha, phys_addr, sfp_data,
		    addr, offset, SFP_BLOCK_SIZE, BIT_1);
		अगर (rval != QLA_SUCCESS) अणु
			ql_log(ql_log_warn, vha, 0x706d,
			    "Unable to read SFP data (%x/%x/%x).\n", rval,
			    addr, offset);

			वापस rval;
		पूर्ण

		अगर (buf && (c < count)) अणु
			u16 sz;

			अगर ((count - c) >= SFP_BLOCK_SIZE)
				sz = SFP_BLOCK_SIZE;
			अन्यथा
				sz = count - c;

			स_नकल(buf, sfp_data, sz);
			buf += SFP_BLOCK_SIZE;
			c += sz;
		पूर्ण
		phys_addr += SFP_BLOCK_SIZE;
		sfp_data  += SFP_BLOCK_SIZE;
		offset += SFP_BLOCK_SIZE;
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक qla24xx_res_count_रुको(काष्ठा scsi_qla_host *vha,
    uपूर्णांक16_t *out_mb, पूर्णांक out_mb_sz)
अणु
	पूर्णांक rval = QLA_FUNCTION_FAILED;
	mbx_cmd_t mc;

	अगर (!vha->hw->flags.fw_started)
		जाओ करोne;

	स_रखो(&mc, 0, माप(mc));
	mc.mb[0] = MBC_GET_RESOURCE_COUNTS;

	rval = qla24xx_send_mb_cmd(vha, &mc);
	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0xffff,
			"%s:  fail\n", __func__);
	पूर्ण अन्यथा अणु
		अगर (out_mb_sz <= SIZखातापूर्ण_IOCB_MB_REG)
			स_नकल(out_mb, mc.mb, out_mb_sz);
		अन्यथा
			स_नकल(out_mb, mc.mb, SIZखातापूर्ण_IOCB_MB_REG);

		ql_dbg(ql_dbg_mbx, vha, 0xffff,
			"%s:  done\n", __func__);
	पूर्ण
करोne:
	वापस rval;
पूर्ण

पूर्णांक qla28xx_secure_flash_update(scsi_qla_host_t *vha, uपूर्णांक16_t opts,
    uपूर्णांक16_t region, uपूर्णांक32_t len, dma_addr_t sfub_dma_addr,
    uपूर्णांक32_t sfub_len)
अणु
	पूर्णांक		rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	mcp->mb[0] = MBC_SECURE_FLASH_UPDATE;
	mcp->mb[1] = opts;
	mcp->mb[2] = region;
	mcp->mb[3] = MSW(len);
	mcp->mb[4] = LSW(len);
	mcp->mb[5] = MSW(sfub_dma_addr);
	mcp->mb[6] = LSW(sfub_dma_addr);
	mcp->mb[7] = MSW(MSD(sfub_dma_addr));
	mcp->mb[8] = LSW(MSD(sfub_dma_addr));
	mcp->mb[9] = sfub_len;
	mcp->out_mb =
	    MBX_9|MBX_8|MBX_7|MBX_6|MBX_5|MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0xffff, "%s(%ld): failed rval 0x%x, %x %x %x",
			__func__, vha->host_no, rval, mcp->mb[0], mcp->mb[1],
			mcp->mb[2]);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक qla2xxx_ग_लिखो_remote_रेजिस्टर(scsi_qla_host_t *vha, uपूर्णांक32_t addr,
    uपूर्णांक32_t data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e8,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_WRITE_REMOTE_REG;
	mcp->mb[1] = LSW(addr);
	mcp->mb[2] = MSW(addr);
	mcp->mb[3] = LSW(data);
	mcp->mb[4] = MSW(data);
	mcp->out_mb = MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e9,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ea,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक qla2xxx_पढ़ो_remote_रेजिस्टर(scsi_qla_host_t *vha, uपूर्णांक32_t addr,
    uपूर्णांक32_t *data)
अणु
	पूर्णांक rval;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;

	ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10e8,
	    "Entered %s.\n", __func__);

	mcp->mb[0] = MBC_READ_REMOTE_REG;
	mcp->mb[1] = LSW(addr);
	mcp->mb[2] = MSW(addr);
	mcp->out_mb = MBX_2|MBX_1|MBX_0;
	mcp->in_mb = MBX_4|MBX_3|MBX_2|MBX_1|MBX_0;
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);

	*data = (uपूर्णांक32_t)((((uपूर्णांक32_t)mcp->mb[4]) << 16) | mcp->mb[3]);

	अगर (rval != QLA_SUCCESS) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x10e9,
		    "Failed=%x mb[0]=%x.\n", rval, mcp->mb[0]);
	पूर्ण अन्यथा अणु
		ql_dbg(ql_dbg_mbx + ql_dbg_verbose, vha, 0x10ea,
		    "Done %s.\n", __func__);
	पूर्ण

	वापस rval;
पूर्ण

पूर्णांक
ql26xx_led_config(scsi_qla_host_t *vha, uपूर्णांक16_t options, uपूर्णांक16_t *led)
अणु
	काष्ठा qla_hw_data *ha = vha->hw;
	mbx_cmd_t mc;
	mbx_cmd_t *mcp = &mc;
	पूर्णांक rval;

	अगर (!IS_QLA2031(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		वापस QLA_FUNCTION_FAILED;

	ql_dbg(ql_dbg_mbx, vha, 0x7070, "Entered %s (options=%x).\n",
	    __func__, options);

	mcp->mb[0] = MBC_SET_GET_FC_LED_CONFIG;
	mcp->mb[1] = options;
	mcp->out_mb = MBX_1|MBX_0;
	mcp->in_mb = MBX_1|MBX_0;
	अगर (options & BIT_0) अणु
		अगर (options & BIT_1) अणु
			mcp->mb[2] = led[2];
			mcp->out_mb |= MBX_2;
		पूर्ण
		अगर (options & BIT_2) अणु
			mcp->mb[3] = led[0];
			mcp->out_mb |= MBX_3;
		पूर्ण
		अगर (options & BIT_3) अणु
			mcp->mb[4] = led[1];
			mcp->out_mb |= MBX_4;
		पूर्ण
	पूर्ण अन्यथा अणु
		mcp->in_mb |= MBX_4|MBX_3|MBX_2;
	पूर्ण
	mcp->tov = MBX_TOV_SECONDS;
	mcp->flags = 0;
	rval = qla2x00_mailbox_command(vha, mcp);
	अगर (rval) अणु
		ql_dbg(ql_dbg_mbx, vha, 0x7071, "Failed %s %x (mb=%x,%x)\n",
		    __func__, rval, mcp->mb[0], mcp->mb[1]);
		वापस rval;
	पूर्ण

	अगर (options & BIT_0) अणु
		ha->beacon_blink_led = 0;
		ql_dbg(ql_dbg_mbx, vha, 0x7072, "Done %s\n", __func__);
	पूर्ण अन्यथा अणु
		led[2] = mcp->mb[2];
		led[0] = mcp->mb[3];
		led[1] = mcp->mb[4];
		ql_dbg(ql_dbg_mbx, vha, 0x7073, "Done %s (led=%x,%x,%x)\n",
		    __func__, led[0], led[1], led[2]);
	पूर्ण

	वापस rval;
पूर्ण
