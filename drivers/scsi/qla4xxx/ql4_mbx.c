<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * QLogic iSCSI HBA Driver
 * Copyright (c)  2003-2013 QLogic Corporation
 */

#समावेश <linux/प्रकार.स>
#समावेश "ql4_def.h"
#समावेश "ql4_glbl.h"
#समावेश "ql4_dbg.h"
#समावेश "ql4_inline.h"
#समावेश "ql4_version.h"

व्योम qla4xxx_queue_mbox_cmd(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbx_cmd,
			    पूर्णांक in_count)
अणु
	पूर्णांक i;

	/* Load all mailbox रेजिस्टरs, except mailbox 0. */
	क्रम (i = 1; i < in_count; i++)
		ग_लिखोl(mbx_cmd[i], &ha->reg->mailbox[i]);

	/* Wakeup firmware  */
	ग_लिखोl(mbx_cmd[0], &ha->reg->mailbox[0]);
	पढ़ोl(&ha->reg->mailbox[0]);
	ग_लिखोl(set_rmask(CSR_INTR_RISC), &ha->reg->ctrl_status);
	पढ़ोl(&ha->reg->ctrl_status);
पूर्ण

व्योम qla4xxx_process_mbox_पूर्णांकr(काष्ठा scsi_qla_host *ha, पूर्णांक out_count)
अणु
	पूर्णांक पूर्णांकr_status;

	पूर्णांकr_status = पढ़ोl(&ha->reg->ctrl_status);
	अगर (पूर्णांकr_status & INTR_PENDING) अणु
		/*
		 * Service the पूर्णांकerrupt.
		 * The ISR will save the mailbox status रेजिस्टरs
		 * to a temporary storage location in the adapter काष्ठाure.
		 */
		ha->mbox_status_count = out_count;
		ha->isp_ops->पूर्णांकerrupt_service_routine(ha, पूर्णांकr_status);
	पूर्ण
पूर्ण

/**
 * qla4xxx_is_पूर्णांकr_poll_mode - Are we allowed to poll क्रम पूर्णांकerrupts?
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * वापसs: 1=polling mode, 0=non-polling mode
 **/
अटल पूर्णांक qla4xxx_is_पूर्णांकr_poll_mode(काष्ठा scsi_qla_host *ha)
अणु
	पूर्णांक rval = 1;

	अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
		अगर (test_bit(AF_IRQ_ATTACHED, &ha->flags) &&
		    test_bit(AF_83XX_MBOX_INTR_ON, &ha->flags))
			rval = 0;
	पूर्ण अन्यथा अणु
		अगर (test_bit(AF_IRQ_ATTACHED, &ha->flags) &&
		    test_bit(AF_INTERRUPTS_ON, &ha->flags) &&
		    test_bit(AF_ONLINE, &ha->flags) &&
		    !test_bit(AF_HA_REMOVAL, &ha->flags))
			rval = 0;
	पूर्ण

	वापस rval;
पूर्ण

/**
 * qla4xxx_mailbox_command - issues mailbox commands
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @inCount: number of mailbox रेजिस्टरs to load.
 * @outCount: number of mailbox रेजिस्टरs to वापस.
 * @mbx_cmd: data poपूर्णांकer क्रम mailbox in रेजिस्टरs.
 * @mbx_sts: data poपूर्णांकer क्रम mailbox out रेजिस्टरs.
 *
 * This routine issue mailbox commands and रुकोs क्रम completion.
 * If outCount is 0, this routine completes successfully WITHOUT रुकोing
 * क्रम the mailbox command to complete.
 **/
पूर्णांक qla4xxx_mailbox_command(काष्ठा scsi_qla_host *ha, uपूर्णांक8_t inCount,
			    uपूर्णांक8_t outCount, uपूर्णांक32_t *mbx_cmd,
			    uपूर्णांक32_t *mbx_sts)
अणु
	पूर्णांक status = QLA_ERROR;
	uपूर्णांक8_t i;
	u_दीर्घ रुको_count;
	अचिन्हित दीर्घ flags = 0;
	uपूर्णांक32_t dev_state;

	/* Make sure that poपूर्णांकers are valid */
	अगर (!mbx_cmd || !mbx_sts) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Invalid mbx_cmd or mbx_sts "
			      "pointer\n", ha->host_no, __func__));
		वापस status;
	पूर्ण

	अगर (is_qla40XX(ha)) अणु
		अगर (test_bit(AF_HA_REMOVAL, &ha->flags)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: "
					  "prematurely completing mbx cmd as "
					  "adapter removal detected\n",
					  ha->host_no, __func__));
			वापस status;
		पूर्ण
	पूर्ण

	अगर ((is_aer_supported(ha)) &&
	    (test_bit(AF_PCI_CHANNEL_IO_PERM_FAILURE, &ha->flags))) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING "scsi%ld: %s: Perm failure on EEH, "
		    "timeout MBX Exiting.\n", ha->host_no, __func__));
		वापस status;
	पूर्ण

	/* Mailbox code active */
	रुको_count = MBOX_TOV * 100;

	जबतक (रुको_count--) अणु
		mutex_lock(&ha->mbox_sem);
		अगर (!test_bit(AF_MBOX_COMMAND, &ha->flags)) अणु
			set_bit(AF_MBOX_COMMAND, &ha->flags);
			mutex_unlock(&ha->mbox_sem);
			अवरोध;
		पूर्ण
		mutex_unlock(&ha->mbox_sem);
		अगर (!रुको_count) अणु
			DEBUG2(prपूर्णांकk("scsi%ld: %s: mbox_sem failed\n",
				ha->host_no, __func__));
			वापस status;
		पूर्ण
		msleep(10);
	पूर्ण

	अगर (is_qla80XX(ha)) अणु
		अगर (test_bit(AF_FW_RECOVERY, &ha->flags)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
					  "scsi%ld: %s: prematurely completing mbx cmd as firmware recovery detected\n",
					  ha->host_no, __func__));
			जाओ mbox_निकास;
		पूर्ण
		/* Do not send any mbx cmd अगर h/w is in failed state*/
		ha->isp_ops->idc_lock(ha);
		dev_state = qla4_8xxx_rd_direct(ha, QLA8XXX_CRB_DEV_STATE);
		ha->isp_ops->idc_unlock(ha);
		अगर (dev_state == QLA8XXX_DEV_FAILED) अणु
			ql4_prपूर्णांकk(KERN_WARNING, ha,
				   "scsi%ld: %s: H/W is in failed state, do not send any mailbox commands\n",
				   ha->host_no, __func__);
			जाओ mbox_निकास;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ha->hardware_lock, flags);

	ha->mbox_status_count = outCount;
	क्रम (i = 0; i < outCount; i++)
		ha->mbox_status[i] = 0;

	/* Queue the mailbox command to the firmware */
	ha->isp_ops->queue_mailbox_command(ha, mbx_cmd, inCount);

	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/* Wait क्रम completion */

	/*
	 * If we करोn't want status, don't रुको क्रम the mailbox command to
	 * complete.  For example, MBOX_CMD_RESET_FW करोesn't वापस status,
	 * you must poll the inbound Interrupt Mask क्रम completion.
	 */
	अगर (outCount == 0) अणु
		status = QLA_SUCCESS;
		जाओ mbox_निकास;
	पूर्ण

	/*
	 * Wait क्रम completion: Poll or completion queue
	 */
	अगर (qla4xxx_is_पूर्णांकr_poll_mode(ha)) अणु
		/* Poll क्रम command to complete */
		रुको_count = jअगरfies + MBOX_TOV * HZ;
		जबतक (test_bit(AF_MBOX_COMMAND_DONE, &ha->flags) == 0) अणु
			अगर (समय_after_eq(jअगरfies, रुको_count))
				अवरोध;
			/*
			 * Service the पूर्णांकerrupt.
			 * The ISR will save the mailbox status रेजिस्टरs
			 * to a temporary storage location in the adapter
			 * काष्ठाure.
			 */
			spin_lock_irqsave(&ha->hardware_lock, flags);
			ha->isp_ops->process_mailbox_पूर्णांकerrupt(ha, outCount);
			spin_unlock_irqrestore(&ha->hardware_lock, flags);
			msleep(10);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Do not poll क्रम completion. Use completion queue */
		set_bit(AF_MBOX_COMMAND_NOPOLL, &ha->flags);
		रुको_क्रम_completion_समयout(&ha->mbx_पूर्णांकr_comp, MBOX_TOV * HZ);
		clear_bit(AF_MBOX_COMMAND_NOPOLL, &ha->flags);
	पूर्ण

	/* Check क्रम mailbox समयout. */
	अगर (!test_bit(AF_MBOX_COMMAND_DONE, &ha->flags)) अणु
		अगर (is_qla80XX(ha) &&
		    test_bit(AF_FW_RECOVERY, &ha->flags)) अणु
			DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			    "scsi%ld: %s: prematurely completing mbx cmd as "
			    "firmware recovery detected\n",
			    ha->host_no, __func__));
			जाओ mbox_निकास;
		पूर्ण
		ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: Mailbox Cmd 0x%08X timed out, Scheduling Adapter Reset\n",
			   ha->host_no, mbx_cmd[0]);
		ha->mailbox_समयout_count++;
		mbx_sts[0] = (-1);
		set_bit(DPC_RESET_HA, &ha->dpc_flags);
		अगर (is_qla8022(ha)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha,
				   "disabling pause transmit on port 0 & 1.\n");
			qla4_82xx_wr_32(ha, QLA82XX_CRB_NIU + 0x98,
					CRB_NIU_XG_PAUSE_CTL_P0 |
					CRB_NIU_XG_PAUSE_CTL_P1);
		पूर्ण अन्यथा अगर (is_qla8032(ha) || is_qla8042(ha)) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, " %s: disabling pause transmit on port 0 & 1.\n",
				   __func__);
			qla4_83xx_disable_छोड़ो(ha);
		पूर्ण
		जाओ mbox_निकास;
	पूर्ण

	/*
	 * Copy the mailbox out रेजिस्टरs to the caller's mailbox in/out
	 * काष्ठाure.
	 */
	spin_lock_irqsave(&ha->hardware_lock, flags);
	क्रम (i = 0; i < outCount; i++)
		mbx_sts[i] = ha->mbox_status[i];

	/* Set वापस status and error flags (अगर applicable). */
	चयन (ha->mbox_status[0]) अणु
	हाल MBOX_STS_COMMAND_COMPLETE:
		status = QLA_SUCCESS;
		अवरोध;

	हाल MBOX_STS_INTERMEDIATE_COMPLETION:
		status = QLA_SUCCESS;
		अवरोध;

	हाल MBOX_STS_BUSY:
		ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: Cmd = %08X, ISP BUSY\n",
			   ha->host_no, __func__, mbx_cmd[0]);
		ha->mailbox_समयout_count++;
		अवरोध;

	शेष:
		ql4_prपूर्णांकk(KERN_WARNING, ha, "scsi%ld: %s: FAILED, MBOX CMD = %08X, MBOX STS = %08X %08X %08X %08X %08X %08X %08X %08X\n",
			   ha->host_no, __func__, mbx_cmd[0], mbx_sts[0],
			   mbx_sts[1], mbx_sts[2], mbx_sts[3], mbx_sts[4],
			   mbx_sts[5], mbx_sts[6], mbx_sts[7]);
		अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

mbox_निकास:
	mutex_lock(&ha->mbox_sem);
	clear_bit(AF_MBOX_COMMAND, &ha->flags);
	mutex_unlock(&ha->mbox_sem);
	clear_bit(AF_MBOX_COMMAND_DONE, &ha->flags);

	वापस status;
पूर्ण

/**
 * qla4xxx_get_minidump_ढाँचा - Get the firmware ढाँचा
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @phys_addr: dma address क्रम ढाँचा
 *
 * Obtain the minidump ढाँचा from firmware during initialization
 * as it may not be available when minidump is desired.
 **/
पूर्णांक qla4xxx_get_minidump_ढाँचा(काष्ठा scsi_qla_host *ha,
				  dma_addr_t phys_addr)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_MINIDUMP;
	mbox_cmd[1] = MINIDUMP_GET_TMPLT_SUBCOMMAND;
	mbox_cmd[2] = LSDW(phys_addr);
	mbox_cmd[3] = MSDW(phys_addr);
	mbox_cmd[4] = ha->fw_dump_पंचांगplt_size;
	mbox_cmd[5] = 0;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 2, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "scsi%ld: %s: Cmd = %08X, mbx[0] = 0x%04x, mbx[1] = 0x%04x\n",
				  ha->host_no, __func__, mbox_cmd[0],
				  mbox_sts[0], mbox_sts[1]));
	पूर्ण
	वापस status;
पूर्ण

/**
 * qla4xxx_req_ढाँचा_size - Get minidump ढाँचा size from firmware.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4xxx_req_ढाँचा_size(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_MINIDUMP;
	mbox_cmd[1] = MINIDUMP_GET_SIZE_SUBCOMMAND;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 8, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status == QLA_SUCCESS) अणु
		ha->fw_dump_पंचांगplt_size = mbox_sts[1];
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: sts[0]=0x%04x, template  size=0x%04x, size_cm_02=0x%04x, size_cm_04=0x%04x, size_cm_08=0x%04x, size_cm_10=0x%04x, size_cm_FF=0x%04x, version=0x%04x\n",
				  __func__, mbox_sts[0], mbox_sts[1],
				  mbox_sts[2], mbox_sts[3], mbox_sts[4],
				  mbox_sts[5], mbox_sts[6], mbox_sts[7]));
		अगर (ha->fw_dump_पंचांगplt_size == 0)
			status = QLA_ERROR;
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_WARNING, ha,
			   "%s: Error sts[0]=0x%04x, mbx[1]=0x%04x\n",
			   __func__, mbox_sts[0], mbox_sts[1]);
		status = QLA_ERROR;
	पूर्ण

	वापस status;
पूर्ण

व्योम qla4xxx_mailbox_premature_completion(काष्ठा scsi_qla_host *ha)
अणु
	set_bit(AF_FW_RECOVERY, &ha->flags);
	ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: set FW RECOVERY!\n",
	    ha->host_no, __func__);

	अगर (test_bit(AF_MBOX_COMMAND, &ha->flags)) अणु
		अगर (test_bit(AF_MBOX_COMMAND_NOPOLL, &ha->flags)) अणु
			complete(&ha->mbx_पूर्णांकr_comp);
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: Due to fw "
			    "recovery, doing premature completion of "
			    "mbx cmd\n", ha->host_no, __func__);

		पूर्ण अन्यथा अणु
			set_bit(AF_MBOX_COMMAND_DONE, &ha->flags);
			ql4_prपूर्णांकk(KERN_INFO, ha, "scsi%ld: %s: Due to fw "
			    "recovery, doing premature completion of "
			    "polling mbx cmd\n", ha->host_no, __func__);
		पूर्ण
	पूर्ण
पूर्ण

अटल uपूर्णांक8_t
qla4xxx_set_अगरcb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbox_cmd,
		 uपूर्णांक32_t *mbox_sts, dma_addr_t init_fw_cb_dma)
अणु
	स_रखो(mbox_cmd, 0, माप(mbox_cmd[0]) * MBOX_REG_COUNT);
	स_रखो(mbox_sts, 0, माप(mbox_sts[0]) * MBOX_REG_COUNT);

	अगर (is_qla8022(ha))
		qla4_82xx_wr_32(ha, ha->nx_db_wr_ptr, 0);

	mbox_cmd[0] = MBOX_CMD_INITIALIZE_FIRMWARE;
	mbox_cmd[1] = 0;
	mbox_cmd[2] = LSDW(init_fw_cb_dma);
	mbox_cmd[3] = MSDW(init_fw_cb_dma);
	mbox_cmd[4] = माप(काष्ठा addr_ctrl_blk);

	अगर (qla4xxx_mailbox_command(ha, 6, 6, mbox_cmd, mbox_sts) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING "scsi%ld: %s: "
			      "MBOX_CMD_INITIALIZE_FIRMWARE"
			      " failed w/ status %04X\n",
			      ha->host_no, __func__, mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

uपूर्णांक8_t
qla4xxx_get_अगरcb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbox_cmd,
		 uपूर्णांक32_t *mbox_sts, dma_addr_t init_fw_cb_dma)
अणु
	स_रखो(mbox_cmd, 0, माप(mbox_cmd[0]) * MBOX_REG_COUNT);
	स_रखो(mbox_sts, 0, माप(mbox_sts[0]) * MBOX_REG_COUNT);
	mbox_cmd[0] = MBOX_CMD_GET_INIT_FW_CTRL_BLOCK;
	mbox_cmd[2] = LSDW(init_fw_cb_dma);
	mbox_cmd[3] = MSDW(init_fw_cb_dma);
	mbox_cmd[4] = माप(काष्ठा addr_ctrl_blk);

	अगर (qla4xxx_mailbox_command(ha, 5, 5, mbox_cmd, mbox_sts) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING "scsi%ld: %s: "
			      "MBOX_CMD_GET_INIT_FW_CTRL_BLOCK"
			      " failed w/ status %04X\n",
			      ha->host_no, __func__, mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

uपूर्णांक8_t qla4xxx_set_ipaddr_state(uपूर्णांक8_t fw_ipaddr_state)
अणु
	uपूर्णांक8_t ipaddr_state;

	चयन (fw_ipaddr_state) अणु
	हाल IP_ADDRSTATE_UNCONFIGURED:
		ipaddr_state = ISCSI_IPDDRESS_STATE_UNCONFIGURED;
		अवरोध;
	हाल IP_ADDRSTATE_INVALID:
		ipaddr_state = ISCSI_IPDDRESS_STATE_INVALID;
		अवरोध;
	हाल IP_ADDRSTATE_ACQUIRING:
		ipaddr_state = ISCSI_IPDDRESS_STATE_ACQUIRING;
		अवरोध;
	हाल IP_ADDRSTATE_TENTATIVE:
		ipaddr_state = ISCSI_IPDDRESS_STATE_TENTATIVE;
		अवरोध;
	हाल IP_ADDRSTATE_DEPRICATED:
		ipaddr_state = ISCSI_IPDDRESS_STATE_DEPRECATED;
		अवरोध;
	हाल IP_ADDRSTATE_PREFERRED:
		ipaddr_state = ISCSI_IPDDRESS_STATE_VALID;
		अवरोध;
	हाल IP_ADDRSTATE_DISABLING:
		ipaddr_state = ISCSI_IPDDRESS_STATE_DISABLING;
		अवरोध;
	शेष:
		ipaddr_state = ISCSI_IPDDRESS_STATE_UNCONFIGURED;
	पूर्ण
	वापस ipaddr_state;
पूर्ण

अटल व्योम
qla4xxx_update_local_ip(काष्ठा scsi_qla_host *ha,
			काष्ठा addr_ctrl_blk *init_fw_cb)
अणु
	ha->ip_config.tcp_options = le16_to_cpu(init_fw_cb->ipv4_tcp_opts);
	ha->ip_config.ipv4_options = le16_to_cpu(init_fw_cb->ipv4_ip_opts);
	ha->ip_config.ipv4_addr_state =
			qla4xxx_set_ipaddr_state(init_fw_cb->ipv4_addr_state);
	ha->ip_config.eth_mtu_size =
				le16_to_cpu(init_fw_cb->eth_mtu_size);
	ha->ip_config.ipv4_port = le16_to_cpu(init_fw_cb->ipv4_port);

	अगर (ha->acb_version == ACB_SUPPORTED) अणु
		ha->ip_config.ipv6_options = le16_to_cpu(init_fw_cb->ipv6_opts);
		ha->ip_config.ipv6_addl_options =
				le16_to_cpu(init_fw_cb->ipv6_addtl_opts);
		ha->ip_config.ipv6_tcp_options =
				le16_to_cpu(init_fw_cb->ipv6_tcp_opts);
	पूर्ण

	/* Save IPv4 Address Info */
	स_नकल(ha->ip_config.ip_address, init_fw_cb->ipv4_addr,
	       min(माप(ha->ip_config.ip_address),
		   माप(init_fw_cb->ipv4_addr)));
	स_नकल(ha->ip_config.subnet_mask, init_fw_cb->ipv4_subnet,
	       min(माप(ha->ip_config.subnet_mask),
		   माप(init_fw_cb->ipv4_subnet)));
	स_नकल(ha->ip_config.gateway, init_fw_cb->ipv4_gw_addr,
	       min(माप(ha->ip_config.gateway),
		   माप(init_fw_cb->ipv4_gw_addr)));

	ha->ip_config.ipv4_vlan_tag = be16_to_cpu(init_fw_cb->ipv4_vlan_tag);
	ha->ip_config.control = init_fw_cb->control;
	ha->ip_config.tcp_wsf = init_fw_cb->ipv4_tcp_wsf;
	ha->ip_config.ipv4_tos = init_fw_cb->ipv4_tos;
	ha->ip_config.ipv4_cache_id = init_fw_cb->ipv4_cacheid;
	ha->ip_config.ipv4_alt_cid_len = init_fw_cb->ipv4_dhcp_alt_cid_len;
	स_नकल(ha->ip_config.ipv4_alt_cid, init_fw_cb->ipv4_dhcp_alt_cid,
	       min(माप(ha->ip_config.ipv4_alt_cid),
		   माप(init_fw_cb->ipv4_dhcp_alt_cid)));
	ha->ip_config.ipv4_vid_len = init_fw_cb->ipv4_dhcp_vid_len;
	स_नकल(ha->ip_config.ipv4_vid, init_fw_cb->ipv4_dhcp_vid,
	       min(माप(ha->ip_config.ipv4_vid),
		   माप(init_fw_cb->ipv4_dhcp_vid)));
	ha->ip_config.ipv4_ttl = init_fw_cb->ipv4_ttl;
	ha->ip_config.def_समयout = le16_to_cpu(init_fw_cb->def_समयout);
	ha->ip_config.पात_समयr = init_fw_cb->पात_समयr;
	ha->ip_config.iscsi_options = le16_to_cpu(init_fw_cb->iscsi_opts);
	ha->ip_config.iscsi_max_pdu_size =
				le16_to_cpu(init_fw_cb->iscsi_max_pdu_size);
	ha->ip_config.iscsi_first_burst_len =
				le16_to_cpu(init_fw_cb->iscsi_fburst_len);
	ha->ip_config.iscsi_max_outstnd_r2t =
				le16_to_cpu(init_fw_cb->iscsi_max_outstnd_r2t);
	ha->ip_config.iscsi_max_burst_len =
				le16_to_cpu(init_fw_cb->iscsi_max_burst_len);
	स_नकल(ha->ip_config.iscsi_name, init_fw_cb->iscsi_name,
	       min(माप(ha->ip_config.iscsi_name),
		   माप(init_fw_cb->iscsi_name)));

	अगर (is_ipv6_enabled(ha)) अणु
		/* Save IPv6 Address */
		ha->ip_config.ipv6_link_local_state =
		  qla4xxx_set_ipaddr_state(init_fw_cb->ipv6_lnk_lcl_addr_state);
		ha->ip_config.ipv6_addr0_state =
			qla4xxx_set_ipaddr_state(init_fw_cb->ipv6_addr0_state);
		ha->ip_config.ipv6_addr1_state =
			qla4xxx_set_ipaddr_state(init_fw_cb->ipv6_addr1_state);

		चयन (le16_to_cpu(init_fw_cb->ipv6_dflt_rtr_state)) अणु
		हाल IPV6_RTRSTATE_UNKNOWN:
			ha->ip_config.ipv6_शेष_router_state =
						ISCSI_ROUTER_STATE_UNKNOWN;
			अवरोध;
		हाल IPV6_RTRSTATE_MANUAL:
			ha->ip_config.ipv6_शेष_router_state =
						ISCSI_ROUTER_STATE_MANUAL;
			अवरोध;
		हाल IPV6_RTRSTATE_ADVERTISED:
			ha->ip_config.ipv6_शेष_router_state =
						ISCSI_ROUTER_STATE_ADVERTISED;
			अवरोध;
		हाल IPV6_RTRSTATE_STALE:
			ha->ip_config.ipv6_शेष_router_state =
						ISCSI_ROUTER_STATE_STALE;
			अवरोध;
		शेष:
			ha->ip_config.ipv6_शेष_router_state =
						ISCSI_ROUTER_STATE_UNKNOWN;
		पूर्ण

		ha->ip_config.ipv6_link_local_addr.in6_u.u6_addr8[0] = 0xFE;
		ha->ip_config.ipv6_link_local_addr.in6_u.u6_addr8[1] = 0x80;

		स_नकल(&ha->ip_config.ipv6_link_local_addr.in6_u.u6_addr8[8],
		       init_fw_cb->ipv6_अगर_id,
		       min(माप(ha->ip_config.ipv6_link_local_addr)/2,
			   माप(init_fw_cb->ipv6_अगर_id)));
		स_नकल(&ha->ip_config.ipv6_addr0, init_fw_cb->ipv6_addr0,
		       min(माप(ha->ip_config.ipv6_addr0),
			   माप(init_fw_cb->ipv6_addr0)));
		स_नकल(&ha->ip_config.ipv6_addr1, init_fw_cb->ipv6_addr1,
		       min(माप(ha->ip_config.ipv6_addr1),
			   माप(init_fw_cb->ipv6_addr1)));
		स_नकल(&ha->ip_config.ipv6_शेष_router_addr,
		       init_fw_cb->ipv6_dflt_rtr_addr,
		       min(माप(ha->ip_config.ipv6_शेष_router_addr),
			   माप(init_fw_cb->ipv6_dflt_rtr_addr)));
		ha->ip_config.ipv6_vlan_tag =
				be16_to_cpu(init_fw_cb->ipv6_vlan_tag);
		ha->ip_config.ipv6_port = le16_to_cpu(init_fw_cb->ipv6_port);
		ha->ip_config.ipv6_cache_id = init_fw_cb->ipv6_cache_id;
		ha->ip_config.ipv6_flow_lbl =
				le16_to_cpu(init_fw_cb->ipv6_flow_lbl);
		ha->ip_config.ipv6_traffic_class =
				init_fw_cb->ipv6_traffic_class;
		ha->ip_config.ipv6_hop_limit = init_fw_cb->ipv6_hop_limit;
		ha->ip_config.ipv6_nd_reach_समय =
				le32_to_cpu(init_fw_cb->ipv6_nd_reach_समय);
		ha->ip_config.ipv6_nd_rexmit_समयr =
				le32_to_cpu(init_fw_cb->ipv6_nd_rexmit_समयr);
		ha->ip_config.ipv6_nd_stale_समयout =
				le32_to_cpu(init_fw_cb->ipv6_nd_stale_समयout);
		ha->ip_config.ipv6_dup_addr_detect_count =
					init_fw_cb->ipv6_dup_addr_detect_count;
		ha->ip_config.ipv6_gw_advrt_mtu =
				le32_to_cpu(init_fw_cb->ipv6_gw_advrt_mtu);
		ha->ip_config.ipv6_tcp_wsf = init_fw_cb->ipv6_tcp_wsf;
	पूर्ण
पूर्ण

uपूर्णांक8_t
qla4xxx_update_local_अगरcb(काष्ठा scsi_qla_host *ha,
			  uपूर्णांक32_t *mbox_cmd,
			  uपूर्णांक32_t *mbox_sts,
			  काष्ठा addr_ctrl_blk  *init_fw_cb,
			  dma_addr_t init_fw_cb_dma)
अणु
	अगर (qla4xxx_get_अगरcb(ha, mbox_cmd, mbox_sts, init_fw_cb_dma)
	    != QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING
			      "scsi%ld: %s: Failed to get init_fw_ctrl_blk\n",
			      ha->host_no, __func__));
		वापस QLA_ERROR;
	पूर्ण

	DEBUG2(qla4xxx_dump_buffer(init_fw_cb, माप(काष्ठा addr_ctrl_blk)));

	/* Save some info in adapter काष्ठाure. */
	ha->acb_version = init_fw_cb->acb_version;
	ha->firmware_options = le16_to_cpu(init_fw_cb->fw_options);
	ha->heartbeat_पूर्णांकerval = init_fw_cb->hb_पूर्णांकerval;
	स_नकल(ha->name_string, init_fw_cb->iscsi_name,
		min(माप(ha->name_string),
		माप(init_fw_cb->iscsi_name)));
	ha->def_समयout = le16_to_cpu(init_fw_cb->def_समयout);
	/*स_नकल(ha->alias, init_fw_cb->Alias,
	       min(माप(ha->alias), माप(init_fw_cb->Alias)));*/

	qla4xxx_update_local_ip(ha, init_fw_cb);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_initialize_fw_cb - initializes firmware control block.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4xxx_initialize_fw_cb(काष्ठा scsi_qla_host * ha)
अणु
	काष्ठा addr_ctrl_blk *init_fw_cb;
	dma_addr_t init_fw_cb_dma;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_ERROR;

	init_fw_cb = dma_alloc_coherent(&ha->pdev->dev,
					माप(काष्ठा addr_ctrl_blk),
					&init_fw_cb_dma, GFP_KERNEL);
	अगर (init_fw_cb == शून्य) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Unable to alloc init_cb\n",
			      ha->host_no, __func__));
		जाओ निकास_init_fw_cb_no_मुक्त;
	पूर्ण

	/* Get Initialize Firmware Control Block. */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	अगर (qla4xxx_get_अगरcb(ha, &mbox_cmd[0], &mbox_sts[0], init_fw_cb_dma) !=
	    QLA_SUCCESS) अणु
		जाओ निकास_init_fw_cb;
	पूर्ण

	/* Fill in the request and response queue inक्रमmation. */
	init_fw_cb->rqq_consumer_idx = cpu_to_le16(ha->request_out);
	init_fw_cb->compq_producer_idx = cpu_to_le16(ha->response_in);
	init_fw_cb->rqq_len = __स्थिरant_cpu_to_le16(REQUEST_QUEUE_DEPTH);
	init_fw_cb->compq_len = __स्थिरant_cpu_to_le16(RESPONSE_QUEUE_DEPTH);
	init_fw_cb->rqq_addr_lo = cpu_to_le32(LSDW(ha->request_dma));
	init_fw_cb->rqq_addr_hi = cpu_to_le32(MSDW(ha->request_dma));
	init_fw_cb->compq_addr_lo = cpu_to_le32(LSDW(ha->response_dma));
	init_fw_cb->compq_addr_hi = cpu_to_le32(MSDW(ha->response_dma));
	init_fw_cb->shdwreg_addr_lo = cpu_to_le32(LSDW(ha->shaकरोw_regs_dma));
	init_fw_cb->shdwreg_addr_hi = cpu_to_le32(MSDW(ha->shaकरोw_regs_dma));

	/* Set up required options. */
	init_fw_cb->fw_options |=
		__स्थिरant_cpu_to_le16(FWOPT_SESSION_MODE |
				       FWOPT_INITIATOR_MODE);

	अगर (is_qla80XX(ha))
		init_fw_cb->fw_options |=
		    __स्थिरant_cpu_to_le16(FWOPT_ENABLE_CRBDB);

	init_fw_cb->fw_options &= __स्थिरant_cpu_to_le16(~FWOPT_TARGET_MODE);

	init_fw_cb->add_fw_options = 0;
	init_fw_cb->add_fw_options |=
			__स्थिरant_cpu_to_le16(ADFWOPT_SERIALIZE_TASK_MGMT);
	init_fw_cb->add_fw_options |=
			__स्थिरant_cpu_to_le16(ADFWOPT_AUTOCONN_DISABLE);

	अगर (qla4xxx_set_अगरcb(ha, &mbox_cmd[0], &mbox_sts[0], init_fw_cb_dma)
		!= QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk(KERN_WARNING
			      "scsi%ld: %s: Failed to set init_fw_ctrl_blk\n",
			      ha->host_no, __func__));
		जाओ निकास_init_fw_cb;
	पूर्ण

	अगर (qla4xxx_update_local_अगरcb(ha, &mbox_cmd[0], &mbox_sts[0],
		init_fw_cb, init_fw_cb_dma) != QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Failed to update local ifcb\n",
				ha->host_no, __func__));
		जाओ निकास_init_fw_cb;
	पूर्ण
	status = QLA_SUCCESS;

निकास_init_fw_cb:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा addr_ctrl_blk),
				init_fw_cb, init_fw_cb_dma);
निकास_init_fw_cb_no_मुक्त:
	वापस status;
पूर्ण

/**
 * qla4xxx_get_dhcp_ip_address - माला_लो HBA ip address via DHCP
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4xxx_get_dhcp_ip_address(काष्ठा scsi_qla_host * ha)
अणु
	काष्ठा addr_ctrl_blk *init_fw_cb;
	dma_addr_t init_fw_cb_dma;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	init_fw_cb = dma_alloc_coherent(&ha->pdev->dev,
					माप(काष्ठा addr_ctrl_blk),
					&init_fw_cb_dma, GFP_KERNEL);
	अगर (init_fw_cb == शून्य) अणु
		prपूर्णांकk("scsi%ld: %s: Unable to alloc init_cb\n", ha->host_no,
		       __func__);
		वापस QLA_ERROR;
	पूर्ण

	/* Get Initialize Firmware Control Block. */
	अगर (qla4xxx_get_अगरcb(ha, &mbox_cmd[0], &mbox_sts[0], init_fw_cb_dma) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: Failed to get init_fw_ctrl_blk\n",
			      ha->host_no, __func__));
		dma_मुक्त_coherent(&ha->pdev->dev,
				  माप(काष्ठा addr_ctrl_blk),
				  init_fw_cb, init_fw_cb_dma);
		वापस QLA_ERROR;
	पूर्ण

	/* Save IP Address. */
	qla4xxx_update_local_ip(ha, init_fw_cb);
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा addr_ctrl_blk),
				init_fw_cb, init_fw_cb_dma);

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_get_firmware_state - माला_लो firmware state of HBA
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4xxx_get_firmware_state(काष्ठा scsi_qla_host * ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	/* Get firmware version */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_FW_STATE;

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 4, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: MBOX_CMD_GET_FW_STATE failed w/ "
			      "status %04X\n", ha->host_no, __func__,
			      mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण
	ha->firmware_state = mbox_sts[1];
	ha->board_id = mbox_sts[2];
	ha->addl_fw_state = mbox_sts[3];
	DEBUG2(prपूर्णांकk("scsi%ld: %s firmware_state=0x%x\n",
		      ha->host_no, __func__, ha->firmware_state);)

	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_get_firmware_status - retrieves firmware status
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
पूर्णांक qla4xxx_get_firmware_status(काष्ठा scsi_qla_host * ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	/* Get firmware version */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_FW_STATUS;

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 3, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: MBOX_CMD_GET_FW_STATUS failed w/ "
			      "status %04X\n", ha->host_no, __func__,
			      mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण

	/* High-water mark of IOCBs */
	ha->iocb_hiwat = mbox_sts[2];
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: firmware IOCBs available = %d\n", __func__,
			  ha->iocb_hiwat));

	अगर (ha->iocb_hiwat > IOCB_HIWAT_CUSHION)
		ha->iocb_hiwat -= IOCB_HIWAT_CUSHION;

	/* Ideally, we should not enter this code, as the # of firmware
	 * IOCBs is hard-coded in the firmware. We set a शेष
	 * iocb_hiwat here just in हाल */
	अगर (ha->iocb_hiwat == 0) अणु
		ha->iocb_hiwat = REQUEST_QUEUE_DEPTH / 4;
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
				  "%s: Setting IOCB's to = %d\n", __func__,
				  ha->iocb_hiwat));
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

/*
 * qla4xxx_get_fwddb_entry - retrieves firmware ddb entry
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @fw_ddb_index: Firmware's device database index
 * @fw_ddb_entry: Poपूर्णांकer to firmware's device database entry काष्ठाure
 * @num_valid_ddb_entries: Poपूर्णांकer to number of valid ddb entries
 * @next_ddb_index: Poपूर्णांकer to next valid device database index
 * @fw_ddb_device_state: Poपूर्णांकer to device state
 **/
पूर्णांक qla4xxx_get_fwddb_entry(काष्ठा scsi_qla_host *ha,
			    uपूर्णांक16_t fw_ddb_index,
			    काष्ठा dev_db_entry *fw_ddb_entry,
			    dma_addr_t fw_ddb_entry_dma,
			    uपूर्णांक32_t *num_valid_ddb_entries,
			    uपूर्णांक32_t *next_ddb_index,
			    uपूर्णांक32_t *fw_ddb_device_state,
			    uपूर्णांक32_t *conn_err_detail,
			    uपूर्णांक16_t *tcp_source_port_num,
			    uपूर्णांक16_t *connection_id)
अणु
	पूर्णांक status = QLA_ERROR;
	uपूर्णांक16_t options;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	/* Make sure the device index is valid */
	अगर (fw_ddb_index >= MAX_DDB_ENTRIES) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: ddb [%d] out of range.\n",
			      ha->host_no, __func__, fw_ddb_index));
		जाओ निकास_get_fwddb;
	पूर्ण
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));
	अगर (fw_ddb_entry)
		स_रखो(fw_ddb_entry, 0, माप(काष्ठा dev_db_entry));

	mbox_cmd[0] = MBOX_CMD_GET_DATABASE_ENTRY;
	mbox_cmd[1] = (uपूर्णांक32_t) fw_ddb_index;
	mbox_cmd[2] = LSDW(fw_ddb_entry_dma);
	mbox_cmd[3] = MSDW(fw_ddb_entry_dma);
	mbox_cmd[4] = माप(काष्ठा dev_db_entry);

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 7, &mbox_cmd[0], &mbox_sts[0]) ==
	    QLA_ERROR) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: MBOX_CMD_GET_DATABASE_ENTRY failed"
			      " with status 0x%04X\n", ha->host_no, __func__,
			      mbox_sts[0]));
		जाओ निकास_get_fwddb;
	पूर्ण
	अगर (fw_ddb_index != mbox_sts[1]) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: ddb mismatch [%d] != [%d].\n",
			      ha->host_no, __func__, fw_ddb_index,
			      mbox_sts[1]));
		जाओ निकास_get_fwddb;
	पूर्ण
	अगर (fw_ddb_entry) अणु
		options = le16_to_cpu(fw_ddb_entry->options);
		अगर (options & DDB_OPT_IPV6_DEVICE) अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: DDB[%d] MB0 %04x Tot %d "
				"Next %d State %04x ConnErr %08x %pI6 "
				":%04d \"%s\"\n", __func__, fw_ddb_index,
				mbox_sts[0], mbox_sts[2], mbox_sts[3],
				mbox_sts[4], mbox_sts[5],
				fw_ddb_entry->ip_addr,
				le16_to_cpu(fw_ddb_entry->port),
				fw_ddb_entry->iscsi_name);
		पूर्ण अन्यथा अणु
			ql4_prपूर्णांकk(KERN_INFO, ha, "%s: DDB[%d] MB0 %04x Tot %d "
				"Next %d State %04x ConnErr %08x %pI4 "
				":%04d \"%s\"\n", __func__, fw_ddb_index,
				mbox_sts[0], mbox_sts[2], mbox_sts[3],
				mbox_sts[4], mbox_sts[5],
				fw_ddb_entry->ip_addr,
				le16_to_cpu(fw_ddb_entry->port),
				fw_ddb_entry->iscsi_name);
		पूर्ण
	पूर्ण
	अगर (num_valid_ddb_entries)
		*num_valid_ddb_entries = mbox_sts[2];
	अगर (next_ddb_index)
		*next_ddb_index = mbox_sts[3];
	अगर (fw_ddb_device_state)
		*fw_ddb_device_state = mbox_sts[4];

	/*
	 * RA: This mailbox has been changed to pass connection error and
	 * details.  Its true क्रम ISP4010 as per Version E - Not sure when it
	 * was changed.	 Get the समय2रुको from the fw_dd_entry field :
	 * शेष_समय2रुको which we call it as minTime2Wait DEV_DB_ENTRY
	 * काष्ठा.
	 */
	अगर (conn_err_detail)
		*conn_err_detail = mbox_sts[5];
	अगर (tcp_source_port_num)
		*tcp_source_port_num = (uपूर्णांक16_t) (mbox_sts[6] >> 16);
	अगर (connection_id)
		*connection_id = (uपूर्णांक16_t) mbox_sts[6] & 0x00FF;
	status = QLA_SUCCESS;

निकास_get_fwddb:
	वापस status;
पूर्ण

पूर्णांक qla4xxx_conn_खोलो(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t fw_ddb_index)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_CONN_OPEN;
	mbox_cmd[1] = fw_ddb_index;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 2, &mbox_cmd[0],
					 &mbox_sts[0]);
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s: status = %d mbx0 = 0x%x mbx1 = 0x%x\n",
			  __func__, status, mbox_sts[0], mbox_sts[1]));
	वापस status;
पूर्ण

/**
 * qla4xxx_set_ddb_entry - sets a ddb entry.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @fw_ddb_index: Firmware's device database index
 * @fw_ddb_entry_dma: dma address of ddb entry
 * @mbx_sts: mailbox 0 to be वापसed or शून्य
 *
 * This routine initializes or updates the adapter's device database
 * entry क्रम the specअगरied device.
 **/
पूर्णांक qla4xxx_set_ddb_entry(काष्ठा scsi_qla_host * ha, uपूर्णांक16_t fw_ddb_index,
			  dma_addr_t fw_ddb_entry_dma, uपूर्णांक32_t *mbx_sts)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	/* Do not रुको क्रम completion. The firmware will send us an
	 * ASTS_DATABASE_CHANGED (0x8014) to notअगरy us of the login status.
	 */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_SET_DATABASE_ENTRY;
	mbox_cmd[1] = (uपूर्णांक32_t) fw_ddb_index;
	mbox_cmd[2] = LSDW(fw_ddb_entry_dma);
	mbox_cmd[3] = MSDW(fw_ddb_entry_dma);
	mbox_cmd[4] = माप(काष्ठा dev_db_entry);

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (mbx_sts)
		*mbx_sts = mbox_sts[0];
	DEBUG2(prपूर्णांकk("scsi%ld: %s: status=%d mbx0=0x%x mbx4=0x%x\n",
	    ha->host_no, __func__, status, mbox_sts[0], mbox_sts[4]);)

	वापस status;
पूर्ण

पूर्णांक qla4xxx_session_logout_ddb(काष्ठा scsi_qla_host *ha,
			       काष्ठा ddb_entry *ddb_entry, पूर्णांक options)
अणु
	पूर्णांक status;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_CONN_CLOSE_SESS_LOGOUT;
	mbox_cmd[1] = ddb_entry->fw_ddb_index;
	mbox_cmd[3] = options;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 2, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: MBOX_CMD_CONN_CLOSE_SESS_LOGOUT "
				  "failed sts %04X %04X", __func__,
				  mbox_sts[0], mbox_sts[1]));
		अगर ((mbox_sts[0] == MBOX_STS_COMMAND_ERROR) &&
		    (mbox_sts[1] == DDB_NOT_LOGGED_IN)) अणु
			set_bit(DDB_CONN_CLOSE_FAILURE, &ddb_entry->flags);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * qla4xxx_get_crash_record - retrieves crash record.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * This routine retrieves a crash record from the QLA4010 after an 8002h aen.
 **/
व्योम qla4xxx_get_crash_record(काष्ठा scsi_qla_host * ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	काष्ठा crash_record *crash_record = शून्य;
	dma_addr_t crash_record_dma = 0;
	uपूर्णांक32_t crash_record_size = 0;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_cmd));

	/* Get size of crash record. */
	mbox_cmd[0] = MBOX_CMD_GET_CRASH_RECORD;

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: ERROR: Unable to retrieve size!\n",
			      ha->host_no, __func__));
		जाओ निकास_get_crash_record;
	पूर्ण
	crash_record_size = mbox_sts[4];
	अगर (crash_record_size == 0) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: ERROR: Crash record size is 0!\n",
			      ha->host_no, __func__));
		जाओ निकास_get_crash_record;
	पूर्ण

	/* Alloc Memory क्रम Crash Record. */
	crash_record = dma_alloc_coherent(&ha->pdev->dev, crash_record_size,
					  &crash_record_dma, GFP_KERNEL);
	अगर (crash_record == शून्य)
		जाओ निकास_get_crash_record;

	/* Get Crash Record. */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_cmd));

	mbox_cmd[0] = MBOX_CMD_GET_CRASH_RECORD;
	mbox_cmd[2] = LSDW(crash_record_dma);
	mbox_cmd[3] = MSDW(crash_record_dma);
	mbox_cmd[4] = crash_record_size;

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS)
		जाओ निकास_get_crash_record;

	/* Dump Crash Record. */

निकास_get_crash_record:
	अगर (crash_record)
		dma_मुक्त_coherent(&ha->pdev->dev, crash_record_size,
				  crash_record, crash_record_dma);
पूर्ण

/**
 * qla4xxx_get_conn_event_log - retrieves connection event log
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 **/
व्योम qla4xxx_get_conn_event_log(काष्ठा scsi_qla_host * ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	काष्ठा conn_event_log_entry *event_log = शून्य;
	dma_addr_t event_log_dma = 0;
	uपूर्णांक32_t event_log_size = 0;
	uपूर्णांक32_t num_valid_entries;
	uपूर्णांक32_t      oldest_entry = 0;
	uपूर्णांक32_t	max_event_log_entries;
	uपूर्णांक8_t		i;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_cmd));

	/* Get size of crash record. */
	mbox_cmd[0] = MBOX_CMD_GET_CONN_EVENT_LOG;

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS)
		जाओ निकास_get_event_log;

	event_log_size = mbox_sts[4];
	अगर (event_log_size == 0)
		जाओ निकास_get_event_log;

	/* Alloc Memory क्रम Crash Record. */
	event_log = dma_alloc_coherent(&ha->pdev->dev, event_log_size,
				       &event_log_dma, GFP_KERNEL);
	अगर (event_log == शून्य)
		जाओ निकास_get_event_log;

	/* Get Crash Record. */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_cmd));

	mbox_cmd[0] = MBOX_CMD_GET_CONN_EVENT_LOG;
	mbox_cmd[2] = LSDW(event_log_dma);
	mbox_cmd[3] = MSDW(event_log_dma);

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: ERROR: Unable to retrieve event "
			      "log!\n", ha->host_no, __func__));
		जाओ निकास_get_event_log;
	पूर्ण

	/* Dump Event Log. */
	num_valid_entries = mbox_sts[1];

	max_event_log_entries = event_log_size /
		माप(काष्ठा conn_event_log_entry);

	अगर (num_valid_entries > max_event_log_entries)
		oldest_entry = num_valid_entries % max_event_log_entries;

	DEBUG3(prपूर्णांकk("scsi%ld: Connection Event Log Dump (%d entries):\n",
		      ha->host_no, num_valid_entries));

	अगर (ql4xextended_error_logging == 3) अणु
		अगर (oldest_entry == 0) अणु
			/* Circular Buffer has not wrapped around */
			क्रम (i=0; i < num_valid_entries; i++) अणु
				qla4xxx_dump_buffer((uपूर्णांक8_t *)event_log+
						    (i*माप(*event_log)),
						    माप(*event_log));
			पूर्ण
		पूर्ण
		अन्यथा अणु
			/* Circular Buffer has wrapped around -
			 * display accordingly*/
			क्रम (i=oldest_entry; i < max_event_log_entries; i++) अणु
				qla4xxx_dump_buffer((uपूर्णांक8_t *)event_log+
						    (i*माप(*event_log)),
						    माप(*event_log));
			पूर्ण
			क्रम (i=0; i < oldest_entry; i++) अणु
				qla4xxx_dump_buffer((uपूर्णांक8_t *)event_log+
						    (i*माप(*event_log)),
						    माप(*event_log));
			पूर्ण
		पूर्ण
	पूर्ण

निकास_get_event_log:
	अगर (event_log)
		dma_मुक्त_coherent(&ha->pdev->dev, event_log_size, event_log,
				  event_log_dma);
पूर्ण

/**
 * qla4xxx_पात_task - issues Abort Task
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @srb: Poपूर्णांकer to srb entry
 *
 * This routine perक्रमms a LUN RESET on the specअगरied target/lun.
 * The caller must ensure that the ddb_entry and lun_entry poपूर्णांकers
 * are valid beक्रमe calling this routine.
 **/
पूर्णांक qla4xxx_पात_task(काष्ठा scsi_qla_host *ha, काष्ठा srb *srb)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	काष्ठा scsi_cmnd *cmd = srb->cmd;
	पूर्णांक status = QLA_SUCCESS;
	अचिन्हित दीर्घ flags = 0;
	uपूर्णांक32_t index;

	/*
	 * Send पात task command to ISP, so that the ISP will वापस
	 * request with ABORT status
	 */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	spin_lock_irqsave(&ha->hardware_lock, flags);
	index = (अचिन्हित दीर्घ)(अचिन्हित अक्षर *)cmd->host_scribble;
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	/* Firmware alपढ़ोy posted completion on response queue */
	अगर (index == MAX_SRBS)
		वापस status;

	mbox_cmd[0] = MBOX_CMD_ABORT_TASK;
	mbox_cmd[1] = srb->ddb->fw_ddb_index;
	mbox_cmd[2] = index;
	/* Immediate Command Enable */
	mbox_cmd[5] = 0x01;

	qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 5, &mbox_cmd[0],
	    &mbox_sts[0]);
	अगर (mbox_sts[0] != MBOX_STS_COMMAND_COMPLETE) अणु
		status = QLA_ERROR;

		DEBUG2(prपूर्णांकk(KERN_WARNING "scsi%ld:%d:%llu: abort task FAILED: "
		    "mbx0=%04X, mb1=%04X, mb2=%04X, mb3=%04X, mb4=%04X\n",
		    ha->host_no, cmd->device->id, cmd->device->lun, mbox_sts[0],
		    mbox_sts[1], mbox_sts[2], mbox_sts[3], mbox_sts[4]));
	पूर्ण

	वापस status;
पूर्ण

/**
 * qla4xxx_reset_lun - issues LUN Reset
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @ddb_entry: Poपूर्णांकer to device database entry
 * @lun: lun number
 *
 * This routine perक्रमms a LUN RESET on the specअगरied target/lun.
 * The caller must ensure that the ddb_entry and lun_entry poपूर्णांकers
 * are valid beक्रमe calling this routine.
 **/
पूर्णांक qla4xxx_reset_lun(काष्ठा scsi_qla_host * ha, काष्ठा ddb_entry * ddb_entry,
		      uपूर्णांक64_t lun)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	uपूर्णांक32_t scsi_lun[2];
	पूर्णांक status = QLA_SUCCESS;

	DEBUG2(prपूर्णांकk("scsi%ld:%d:%llu: lun reset issued\n", ha->host_no,
		      ddb_entry->fw_ddb_index, lun));

	/*
	 * Send lun reset command to ISP, so that the ISP will वापस all
	 * outstanding requests with RESET status
	 */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));
	पूर्णांक_to_scsilun(lun, (काष्ठा scsi_lun *) scsi_lun);

	mbox_cmd[0] = MBOX_CMD_LUN_RESET;
	mbox_cmd[1] = ddb_entry->fw_ddb_index;
	/* FW expects LUN bytes 0-3 in Incoming Mailbox 2
	 * (LUN byte 0 is LSByte, byte 3 is MSByte) */
	mbox_cmd[2] = cpu_to_le32(scsi_lun[0]);
	/* FW expects LUN bytes 4-7 in Incoming Mailbox 3
	 * (LUN byte 4 is LSByte, byte 7 is MSByte) */
	mbox_cmd[3] = cpu_to_le32(scsi_lun[1]);
	mbox_cmd[5] = 0x01;	/* Immediate Command Enable */

	qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0], &mbox_sts[0]);
	अगर (mbox_sts[0] != MBOX_STS_COMMAND_COMPLETE &&
	    mbox_sts[0] != MBOX_STS_COMMAND_ERROR)
		status = QLA_ERROR;

	वापस status;
पूर्ण

/**
 * qla4xxx_reset_target - issues target Reset
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @ddb_entry: Poपूर्णांकer to device database entry
 *
 * This routine perक्रमms a TARGET RESET on the specअगरied target.
 * The caller must ensure that the ddb_entry poपूर्णांकers
 * are valid beक्रमe calling this routine.
 **/
पूर्णांक qla4xxx_reset_target(काष्ठा scsi_qla_host *ha,
			 काष्ठा ddb_entry *ddb_entry)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_SUCCESS;

	DEBUG2(prपूर्णांकk("scsi%ld:%d: target reset issued\n", ha->host_no,
		      ddb_entry->fw_ddb_index));

	/*
	 * Send target reset command to ISP, so that the ISP will वापस all
	 * outstanding requests with RESET status
	 */
	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_TARGET_WARM_RESET;
	mbox_cmd[1] = ddb_entry->fw_ddb_index;
	mbox_cmd[5] = 0x01;	/* Immediate Command Enable */

	qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0],
				&mbox_sts[0]);
	अगर (mbox_sts[0] != MBOX_STS_COMMAND_COMPLETE &&
	    mbox_sts[0] != MBOX_STS_COMMAND_ERROR)
		status = QLA_ERROR;

	वापस status;
पूर्ण

पूर्णांक qla4xxx_get_flash(काष्ठा scsi_qla_host * ha, dma_addr_t dma_addr,
		      uपूर्णांक32_t offset, uपूर्णांक32_t len)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_READ_FLASH;
	mbox_cmd[1] = LSDW(dma_addr);
	mbox_cmd[2] = MSDW(dma_addr);
	mbox_cmd[3] = offset;
	mbox_cmd[4] = len;

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 2, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: MBOX_CMD_READ_FLASH, failed w/ "
		    "status %04X %04X, offset %08x, len %08x\n", ha->host_no,
		    __func__, mbox_sts[0], mbox_sts[1], offset, len));
		वापस QLA_ERROR;
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

/**
 * qla4xxx_about_firmware - माला_लो FW, iscsi draft and boot loader version
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * Retrieves the FW version, iSCSI draft version & bootloader version of HBA.
 * Mailboxes 2 & 3 may hold an address क्रम data. Make sure that we ग_लिखो 0 to
 * those mailboxes, अगर unused.
 **/
पूर्णांक qla4xxx_about_firmware(काष्ठा scsi_qla_host *ha)
अणु
	काष्ठा about_fw_info *about_fw = शून्य;
	dma_addr_t about_fw_dma;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_ERROR;

	about_fw = dma_alloc_coherent(&ha->pdev->dev,
				      माप(काष्ठा about_fw_info),
				      &about_fw_dma, GFP_KERNEL);
	अगर (!about_fw) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Unable to alloc memory "
				  "for about_fw\n", __func__));
		वापस status;
	पूर्ण

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_ABOUT_FW;
	mbox_cmd[2] = LSDW(about_fw_dma);
	mbox_cmd[3] = MSDW(about_fw_dma);
	mbox_cmd[4] = माप(काष्ठा about_fw_info);

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, MBOX_REG_COUNT,
					 &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: MBOX_CMD_ABOUT_FW "
				  "failed w/ status %04X\n", __func__,
				  mbox_sts[0]));
		जाओ निकास_about_fw;
	पूर्ण

	/* Save version inक्रमmation. */
	ha->fw_info.fw_major = le16_to_cpu(about_fw->fw_major);
	ha->fw_info.fw_minor = le16_to_cpu(about_fw->fw_minor);
	ha->fw_info.fw_patch = le16_to_cpu(about_fw->fw_patch);
	ha->fw_info.fw_build = le16_to_cpu(about_fw->fw_build);
	स_नकल(ha->fw_info.fw_build_date, about_fw->fw_build_date,
	       माप(about_fw->fw_build_date));
	स_नकल(ha->fw_info.fw_build_समय, about_fw->fw_build_समय,
	       माप(about_fw->fw_build_समय));
	म_नकल((अक्षर *)ha->fw_info.fw_build_user,
	       skip_spaces((अक्षर *)about_fw->fw_build_user));
	ha->fw_info.fw_load_source = le16_to_cpu(about_fw->fw_load_source);
	ha->fw_info.iscsi_major = le16_to_cpu(about_fw->iscsi_major);
	ha->fw_info.iscsi_minor = le16_to_cpu(about_fw->iscsi_minor);
	ha->fw_info.bootload_major = le16_to_cpu(about_fw->bootload_major);
	ha->fw_info.bootload_minor = le16_to_cpu(about_fw->bootload_minor);
	ha->fw_info.bootload_patch = le16_to_cpu(about_fw->bootload_patch);
	ha->fw_info.bootload_build = le16_to_cpu(about_fw->bootload_build);
	म_नकल((अक्षर *)ha->fw_info.extended_बारtamp,
	       skip_spaces((अक्षर *)about_fw->extended_बारtamp));

	ha->fw_upसमय_secs = le32_to_cpu(mbox_sts[5]);
	ha->fw_upसमय_msecs = le32_to_cpu(mbox_sts[6]);
	status = QLA_SUCCESS;

निकास_about_fw:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा about_fw_info),
			  about_fw, about_fw_dma);
	वापस status;
पूर्ण

पूर्णांक qla4xxx_get_शेष_ddb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t options,
			    dma_addr_t dma_addr)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_DATABASE_ENTRY_DEFAULTS;
	mbox_cmd[1] = options;
	mbox_cmd[2] = LSDW(dma_addr);
	mbox_cmd[3] = MSDW(dma_addr);

	अगर (qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0], &mbox_sts[0]) !=
	    QLA_SUCCESS) अणु
		DEBUG2(prपूर्णांकk("scsi%ld: %s: failed status %04X\n",
		     ha->host_no, __func__, mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण
	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक qla4xxx_req_ddb_entry(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t ddb_index,
			  uपूर्णांक32_t *mbx_sts)
अणु
	पूर्णांक status;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_REQUEST_DATABASE_ENTRY;
	mbox_cmd[1] = ddb_index;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed status %04X\n",
				   __func__, mbox_sts[0]));
	पूर्ण

	*mbx_sts = mbox_sts[0];
	वापस status;
पूर्ण

पूर्णांक qla4xxx_clear_ddb_entry(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t ddb_index)
अणु
	पूर्णांक status;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_CLEAR_DATABASE_ENTRY;
	mbox_cmd[1] = ddb_index;

	status = qla4xxx_mailbox_command(ha, 2, 1, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed status %04X\n",
				   __func__, mbox_sts[0]));
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक qla4xxx_set_flash(काष्ठा scsi_qla_host *ha, dma_addr_t dma_addr,
		      uपूर्णांक32_t offset, uपूर्णांक32_t length, uपूर्णांक32_t options)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_SUCCESS;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_WRITE_FLASH;
	mbox_cmd[1] = LSDW(dma_addr);
	mbox_cmd[2] = MSDW(dma_addr);
	mbox_cmd[3] = offset;
	mbox_cmd[4] = length;
	mbox_cmd[5] = options;

	status = qla4xxx_mailbox_command(ha, 6, 2, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: MBOX_CMD_WRITE_FLASH "
				  "failed w/ status %04X, mbx1 %04X\n",
				  __func__, mbox_sts[0], mbox_sts[1]));
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_bootdb_by_index(काष्ठा scsi_qla_host *ha,
			    काष्ठा dev_db_entry *fw_ddb_entry,
			    dma_addr_t fw_ddb_entry_dma, uपूर्णांक16_t ddb_index)
अणु
	uपूर्णांक32_t dev_db_start_offset = FLASH_OFFSET_DB_INFO;
	uपूर्णांक32_t dev_db_end_offset;
	पूर्णांक status = QLA_ERROR;

	स_रखो(fw_ddb_entry, 0, माप(*fw_ddb_entry));

	dev_db_start_offset += (ddb_index * माप(*fw_ddb_entry));
	dev_db_end_offset = FLASH_OFFSET_DB_END;

	अगर (dev_db_start_offset > dev_db_end_offset) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s:Invalid DDB index %d", __func__,
				  ddb_index));
		जाओ निकास_bootdb_failed;
	पूर्ण

	अगर (qla4xxx_get_flash(ha, fw_ddb_entry_dma, dev_db_start_offset,
			      माप(*fw_ddb_entry)) != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: Get Flash"
			   "failed\n", ha->host_no, __func__);
		जाओ निकास_bootdb_failed;
	पूर्ण

	अगर (fw_ddb_entry->cookie == DDB_VALID_COOKIE)
		status = QLA_SUCCESS;

निकास_bootdb_failed:
	वापस status;
पूर्ण

पूर्णांक qla4xxx_flashdb_by_index(काष्ठा scsi_qla_host *ha,
			     काष्ठा dev_db_entry *fw_ddb_entry,
			     dma_addr_t fw_ddb_entry_dma, uपूर्णांक16_t ddb_index)
अणु
	uपूर्णांक32_t dev_db_start_offset;
	uपूर्णांक32_t dev_db_end_offset;
	पूर्णांक status = QLA_ERROR;

	स_रखो(fw_ddb_entry, 0, माप(*fw_ddb_entry));

	अगर (is_qla40XX(ha)) अणु
		dev_db_start_offset = FLASH_OFFSET_DB_INFO;
		dev_db_end_offset = FLASH_OFFSET_DB_END;
	पूर्ण अन्यथा अणु
		dev_db_start_offset = FLASH_RAW_ACCESS_ADDR +
				      (ha->hw.flt_region_ddb << 2);
		/* flt_ddb_size is DDB table size क्रम both ports
		 * so भागide it by 2 to calculate the offset क्रम second port
		 */
		अगर (ha->port_num == 1)
			dev_db_start_offset += (ha->hw.flt_ddb_size / 2);

		dev_db_end_offset = dev_db_start_offset +
				    (ha->hw.flt_ddb_size / 2);
	पूर्ण

	dev_db_start_offset += (ddb_index * माप(*fw_ddb_entry));

	अगर (dev_db_start_offset > dev_db_end_offset) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s:Invalid DDB index %d", __func__,
				  ddb_index));
		जाओ निकास_fdb_failed;
	पूर्ण

	अगर (qla4xxx_get_flash(ha, fw_ddb_entry_dma, dev_db_start_offset,
			      माप(*fw_ddb_entry)) != QLA_SUCCESS) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: Get Flash failed\n",
			   ha->host_no, __func__);
		जाओ निकास_fdb_failed;
	पूर्ण

	अगर (fw_ddb_entry->cookie == DDB_VALID_COOKIE)
		status = QLA_SUCCESS;

निकास_fdb_failed:
	वापस status;
पूर्ण

पूर्णांक qla4xxx_get_chap(काष्ठा scsi_qla_host *ha, अक्षर *username, अक्षर *password,
		     uपूर्णांक16_t idx)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rval = QLA_ERROR;
	uपूर्णांक32_t offset = 0, chap_size;
	काष्ठा ql4_chap_table *chap_table;
	dma_addr_t chap_dma;

	chap_table = dma_pool_zalloc(ha->chap_dma_pool, GFP_KERNEL, &chap_dma);
	अगर (chap_table == शून्य)
		वापस -ENOMEM;

	chap_size = माप(काष्ठा ql4_chap_table);

	अगर (is_qla40XX(ha))
		offset = FLASH_CHAP_OFFSET | (idx * chap_size);
	अन्यथा अणु
		offset = FLASH_RAW_ACCESS_ADDR + (ha->hw.flt_region_chap << 2);
		/* flt_chap_size is CHAP table size क्रम both ports
		 * so भागide it by 2 to calculate the offset क्रम second port
		 */
		अगर (ha->port_num == 1)
			offset += (ha->hw.flt_chap_size / 2);
		offset += (idx * chap_size);
	पूर्ण

	rval = qla4xxx_get_flash(ha, chap_dma, offset, chap_size);
	अगर (rval != QLA_SUCCESS) अणु
		ret = -EINVAL;
		जाओ निकास_get_chap;
	पूर्ण

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "Chap Cookie: x%x\n",
		__le16_to_cpu(chap_table->cookie)));

	अगर (__le16_to_cpu(chap_table->cookie) != CHAP_VALID_COOKIE) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "No valid chap entry found\n");
		जाओ निकास_get_chap;
	पूर्ण

	strlcpy(password, chap_table->secret, QL4_CHAP_MAX_SECRET_LEN);
	strlcpy(username, chap_table->name, QL4_CHAP_MAX_NAME_LEN);
	chap_table->cookie = __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE);

निकास_get_chap:
	dma_pool_मुक्त(ha->chap_dma_pool, chap_table, chap_dma);
	वापस ret;
पूर्ण

/**
 * qla4xxx_set_chap - Make a chap entry at the given index
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @username: CHAP username to set
 * @password: CHAP password to set
 * @idx: CHAP index at which to make the entry
 * @bidi: type of chap entry (chap_in or chap_out)
 *
 * Create chap entry at the given index with the inक्रमmation provided.
 *
 * Note: Caller should acquire the chap lock beक्रमe getting here.
 **/
पूर्णांक qla4xxx_set_chap(काष्ठा scsi_qla_host *ha, अक्षर *username, अक्षर *password,
		     uपूर्णांक16_t idx, पूर्णांक bidi)
अणु
	पूर्णांक ret = 0;
	पूर्णांक rval = QLA_ERROR;
	uपूर्णांक32_t offset = 0;
	काष्ठा ql4_chap_table *chap_table;
	uपूर्णांक32_t chap_size = 0;
	dma_addr_t chap_dma;

	chap_table = dma_pool_zalloc(ha->chap_dma_pool, GFP_KERNEL, &chap_dma);
	अगर (chap_table == शून्य) अणु
		ret =  -ENOMEM;
		जाओ निकास_set_chap;
	पूर्ण

	अगर (bidi)
		chap_table->flags |= BIT_6; /* peer */
	अन्यथा
		chap_table->flags |= BIT_7; /* local */
	chap_table->secret_len = म_माप(password);
	म_नकलन(chap_table->secret, password, MAX_CHAP_SECRET_LEN - 1);
	म_नकलन(chap_table->name, username, MAX_CHAP_NAME_LEN - 1);
	chap_table->cookie = __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE);

	अगर (is_qla40XX(ha)) अणु
		chap_size = MAX_CHAP_ENTRIES_40XX * माप(*chap_table);
		offset = FLASH_CHAP_OFFSET;
	पूर्ण अन्यथा अणु /* Single region contains CHAP info क्रम both ports which is
		  * भागided पूर्णांकo half क्रम each port.
		  */
		chap_size = ha->hw.flt_chap_size / 2;
		offset = FLASH_RAW_ACCESS_ADDR + (ha->hw.flt_region_chap << 2);
		अगर (ha->port_num == 1)
			offset += chap_size;
	पूर्ण

	offset += (idx * माप(काष्ठा ql4_chap_table));
	rval = qla4xxx_set_flash(ha, chap_dma, offset,
				माप(काष्ठा ql4_chap_table),
				FLASH_OPT_RMW_COMMIT);

	अगर (rval == QLA_SUCCESS && ha->chap_list) अणु
		/* Update ha chap_list cache */
		स_नकल((काष्ठा ql4_chap_table *)ha->chap_list + idx,
		       chap_table, माप(काष्ठा ql4_chap_table));
	पूर्ण
	dma_pool_मुक्त(ha->chap_dma_pool, chap_table, chap_dma);
	अगर (rval != QLA_SUCCESS)
		ret =  -EINVAL;

निकास_set_chap:
	वापस ret;
पूर्ण


पूर्णांक qla4xxx_get_uni_chap_at_index(काष्ठा scsi_qla_host *ha, अक्षर *username,
				  अक्षर *password, uपूर्णांक16_t chap_index)
अणु
	पूर्णांक rval = QLA_ERROR;
	काष्ठा ql4_chap_table *chap_table = शून्य;
	पूर्णांक max_chap_entries;

	अगर (!ha->chap_list) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Do not have CHAP table cache\n");
		rval = QLA_ERROR;
		जाओ निकास_uni_chap;
	पूर्ण

	अगर (!username || !password) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "No memory for username & secret\n");
		rval = QLA_ERROR;
		जाओ निकास_uni_chap;
	पूर्ण

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
				   माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	अगर (chap_index > max_chap_entries) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Invalid Chap index\n");
		rval = QLA_ERROR;
		जाओ निकास_uni_chap;
	पूर्ण

	mutex_lock(&ha->chap_sem);
	chap_table = (काष्ठा ql4_chap_table *)ha->chap_list + chap_index;
	अगर (chap_table->cookie != __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE)) अणु
		rval = QLA_ERROR;
		जाओ निकास_unlock_uni_chap;
	पूर्ण

	अगर (!(chap_table->flags & BIT_7)) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Unidirectional entry not set\n");
		rval = QLA_ERROR;
		जाओ निकास_unlock_uni_chap;
	पूर्ण

	strlcpy(password, chap_table->secret, MAX_CHAP_SECRET_LEN);
	strlcpy(username, chap_table->name, MAX_CHAP_NAME_LEN);

	rval = QLA_SUCCESS;

निकास_unlock_uni_chap:
	mutex_unlock(&ha->chap_sem);
निकास_uni_chap:
	वापस rval;
पूर्ण

/**
 * qla4xxx_get_chap_index - Get chap index given username and secret
 * @ha: poपूर्णांकer to adapter काष्ठाure
 * @username: CHAP username to be searched
 * @password: CHAP password to be searched
 * @bidi: Is this a BIDI CHAP
 * @chap_index: CHAP index to be वापसed
 *
 * Match the username and password in the chap_list, वापस the index अगर a
 * match is found. If a match is not found then add the entry in FLASH and
 * वापस the index at which entry is written in the FLASH.
 **/
पूर्णांक qla4xxx_get_chap_index(काष्ठा scsi_qla_host *ha, अक्षर *username,
			   अक्षर *password, पूर्णांक bidi, uपूर्णांक16_t *chap_index)
अणु
	पूर्णांक i, rval;
	पूर्णांक मुक्त_index = -1;
	पूर्णांक found_index = 0;
	पूर्णांक max_chap_entries = 0;
	काष्ठा ql4_chap_table *chap_table;

	अगर (is_qla80XX(ha))
		max_chap_entries = (ha->hw.flt_chap_size / 2) /
						माप(काष्ठा ql4_chap_table);
	अन्यथा
		max_chap_entries = MAX_CHAP_ENTRIES_40XX;

	अगर (!ha->chap_list) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Do not have CHAP table cache\n");
		वापस QLA_ERROR;
	पूर्ण

	अगर (!username || !password) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "Do not have username and psw\n");
		वापस QLA_ERROR;
	पूर्ण

	mutex_lock(&ha->chap_sem);
	क्रम (i = 0; i < max_chap_entries; i++) अणु
		chap_table = (काष्ठा ql4_chap_table *)ha->chap_list + i;
		अगर (chap_table->cookie !=
		    __स्थिरant_cpu_to_le16(CHAP_VALID_COOKIE)) अणु
			अगर (i > MAX_RESRV_CHAP_IDX && मुक्त_index == -1)
				मुक्त_index = i;
			जारी;
		पूर्ण
		अगर (bidi) अणु
			अगर (chap_table->flags & BIT_7)
				जारी;
		पूर्ण अन्यथा अणु
			अगर (chap_table->flags & BIT_6)
				जारी;
		पूर्ण
		अगर (!म_भेदन(chap_table->secret, password,
			     MAX_CHAP_SECRET_LEN) &&
		    !म_भेदन(chap_table->name, username,
			     MAX_CHAP_NAME_LEN)) अणु
			*chap_index = i;
			found_index = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If chap entry is not present and a मुक्त index is available then
	 * ग_लिखो the entry in flash
	 */
	अगर (!found_index && मुक्त_index != -1) अणु
		rval = qla4xxx_set_chap(ha, username, password,
					मुक्त_index, bidi);
		अगर (!rval) अणु
			*chap_index = मुक्त_index;
			found_index = 1;
		पूर्ण
	पूर्ण

	mutex_unlock(&ha->chap_sem);

	अगर (found_index)
		वापस QLA_SUCCESS;
	वापस QLA_ERROR;
पूर्ण

पूर्णांक qla4xxx_conn_बंद_sess_logout(काष्ठा scsi_qla_host *ha,
				   uपूर्णांक16_t fw_ddb_index,
				   uपूर्णांक16_t connection_id,
				   uपूर्णांक16_t option)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_SUCCESS;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_CONN_CLOSE_SESS_LOGOUT;
	mbox_cmd[1] = fw_ddb_index;
	mbox_cmd[2] = connection_id;
	mbox_cmd[3] = option;

	status = qla4xxx_mailbox_command(ha, 4, 2, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: MBOX_CMD_CONN_CLOSE "
				  "option %04x failed w/ status %04X %04X\n",
				  __func__, option, mbox_sts[0], mbox_sts[1]));
	पूर्ण
	वापस status;
पूर्ण

/**
 * qla4_84xx_extend_idc_पंचांगo - Extend IDC Timeout.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @ext_पंचांगo: idc समयout value
 *
 * Requests firmware to extend the idc समयout value.
 **/
अटल पूर्णांक qla4_84xx_extend_idc_पंचांगo(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t ext_पंचांगo)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));
	ext_पंचांगo &= 0xf;

	mbox_cmd[0] = MBOX_CMD_IDC_TIME_EXTEND;
	mbox_cmd[1] = ((ha->idc_info.request_desc & 0xfffff0ff) |
		       (ext_पंचांगo << 8));		/* new समयout */
	mbox_cmd[2] = ha->idc_info.info1;
	mbox_cmd[3] = ha->idc_info.info2;
	mbox_cmd[4] = ha->idc_info.info3;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, MBOX_REG_COUNT,
					 mbox_cmd, mbox_sts);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "scsi%ld: %s: failed status %04X\n",
				  ha->host_no, __func__, mbox_sts[0]));
		वापस QLA_ERROR;
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC timeout extended by %d secs\n",
			   __func__, ext_पंचांगo);
	पूर्ण

	वापस QLA_SUCCESS;
पूर्ण

पूर्णांक qla4xxx_disable_acb(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_SUCCESS;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_DISABLE_ACB;

	status = qla4xxx_mailbox_command(ha, 8, 5, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: MBOX_CMD_DISABLE_ACB "
				  "failed w/ status %04X %04X %04X", __func__,
				  mbox_sts[0], mbox_sts[1], mbox_sts[2]));
	पूर्ण अन्यथा अणु
		अगर (is_qla8042(ha) &&
		    test_bit(DPC_POST_IDC_ACK, &ha->dpc_flags) &&
		    (mbox_sts[0] != MBOX_STS_COMMAND_COMPLETE)) अणु
			/*
			 * Disable ACB mailbox command takes समय to complete
			 * based on the total number of tarमाला_लो connected.
			 * For 512 tarमाला_लो, it took approximately 5 secs to
			 * complete. Setting the समयout value to 8, with the 3
			 * secs buffer.
			 */
			qla4_84xx_extend_idc_पंचांगo(ha, IDC_EXTEND_TOV);
			अगर (!रुको_क्रम_completion_समयout(&ha->disable_acb_comp,
							 IDC_EXTEND_TOV * HZ)) अणु
				ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: Disable ACB Completion not received\n",
					   __func__);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_get_acb(काष्ठा scsi_qla_host *ha, dma_addr_t acb_dma,
		    uपूर्णांक32_t acb_type, uपूर्णांक32_t len)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_SUCCESS;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_ACB;
	mbox_cmd[1] = acb_type;
	mbox_cmd[2] = LSDW(acb_dma);
	mbox_cmd[3] = MSDW(acb_dma);
	mbox_cmd[4] = len;

	status = qla4xxx_mailbox_command(ha, 5, 5, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha, "%s: MBOX_CMD_GET_ACB "
				  "failed w/ status %04X\n", __func__,
				  mbox_sts[0]));
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_set_acb(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *mbox_cmd,
		    uपूर्णांक32_t *mbox_sts, dma_addr_t acb_dma)
अणु
	पूर्णांक status = QLA_SUCCESS;

	स_रखो(mbox_cmd, 0, माप(mbox_cmd[0]) * MBOX_REG_COUNT);
	स_रखो(mbox_sts, 0, माप(mbox_sts[0]) * MBOX_REG_COUNT);
	mbox_cmd[0] = MBOX_CMD_SET_ACB;
	mbox_cmd[1] = 0; /* Primary ACB */
	mbox_cmd[2] = LSDW(acb_dma);
	mbox_cmd[3] = MSDW(acb_dma);
	mbox_cmd[4] = माप(काष्ठा addr_ctrl_blk);

	status = qla4xxx_mailbox_command(ha, 5, 5, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,  "%s: MBOX_CMD_SET_ACB "
				  "failed w/ status %04X\n", __func__,
				  mbox_sts[0]));
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_set_param_ddbentry(काष्ठा scsi_qla_host *ha,
			       काष्ठा ddb_entry *ddb_entry,
			       काष्ठा iscsi_cls_conn *cls_conn,
			       uपूर्णांक32_t *mbx_sts)
अणु
	काष्ठा dev_db_entry *fw_ddb_entry;
	काष्ठा iscsi_conn *conn;
	काष्ठा iscsi_session *sess;
	काष्ठा qla_conn *qla_conn;
	काष्ठा sockaddr *dst_addr;
	dma_addr_t fw_ddb_entry_dma;
	पूर्णांक status = QLA_SUCCESS;
	पूर्णांक rval = 0;
	काष्ठा sockaddr_in *addr;
	काष्ठा sockaddr_in6 *addr6;
	अक्षर *ip;
	uपूर्णांक16_t iscsi_opts = 0;
	uपूर्णांक32_t options = 0;
	uपूर्णांक16_t idx, *ptid;

	fw_ddb_entry = dma_alloc_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
					  &fw_ddb_entry_dma, GFP_KERNEL);
	अगर (!fw_ddb_entry) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha,
				  "%s: Unable to allocate dma buffer.\n",
				  __func__));
		rval = -ENOMEM;
		जाओ निकास_set_param_no_मुक्त;
	पूर्ण

	conn = cls_conn->dd_data;
	qla_conn = conn->dd_data;
	sess = conn->session;
	dst_addr = (काष्ठा sockaddr *)&qla_conn->qla_ep->dst_addr;

	अगर (dst_addr->sa_family == AF_INET6)
		options |= IPV6_DEFAULT_DDB_ENTRY;

	status = qla4xxx_get_शेष_ddb(ha, options, fw_ddb_entry_dma);
	अगर (status == QLA_ERROR) अणु
		rval = -EINVAL;
		जाओ निकास_set_param;
	पूर्ण

	ptid = (uपूर्णांक16_t *)&fw_ddb_entry->isid[1];
	*ptid = cpu_to_le16((uपूर्णांक16_t)ddb_entry->sess->target_id);

	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha, "ISID [%pmR]\n", fw_ddb_entry->isid));

	iscsi_opts = le16_to_cpu(fw_ddb_entry->iscsi_options);
	स_रखो(fw_ddb_entry->iscsi_alias, 0, माप(fw_ddb_entry->iscsi_alias));

	स_रखो(fw_ddb_entry->iscsi_name, 0, माप(fw_ddb_entry->iscsi_name));

	अगर (sess->targetname != शून्य) अणु
		स_नकल(fw_ddb_entry->iscsi_name, sess->targetname,
		       min(म_माप(sess->targetname),
		       माप(fw_ddb_entry->iscsi_name)));
	पूर्ण

	स_रखो(fw_ddb_entry->ip_addr, 0, माप(fw_ddb_entry->ip_addr));
	स_रखो(fw_ddb_entry->tgt_addr, 0, माप(fw_ddb_entry->tgt_addr));

	fw_ddb_entry->options =  DDB_OPT_TARGET | DDB_OPT_AUTO_SENDTGTS_DISABLE;

	अगर (dst_addr->sa_family == AF_INET) अणु
		addr = (काष्ठा sockaddr_in *)dst_addr;
		ip = (अक्षर *)&addr->sin_addr;
		स_नकल(fw_ddb_entry->ip_addr, ip, IP_ADDR_LEN);
		fw_ddb_entry->port = cpu_to_le16(ntohs(addr->sin_port));
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Destination Address [%pI4]: index [%d]\n",
				   __func__, fw_ddb_entry->ip_addr,
				  ddb_entry->fw_ddb_index));
	पूर्ण अन्यथा अगर (dst_addr->sa_family == AF_INET6) अणु
		addr6 = (काष्ठा sockaddr_in6 *)dst_addr;
		ip = (अक्षर *)&addr6->sin6_addr;
		स_नकल(fw_ddb_entry->ip_addr, ip, IPv6_ADDR_LEN);
		fw_ddb_entry->port = cpu_to_le16(ntohs(addr6->sin6_port));
		fw_ddb_entry->options |= DDB_OPT_IPV6_DEVICE;
		DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
				  "%s: Destination Address [%pI6]: index [%d]\n",
				   __func__, fw_ddb_entry->ip_addr,
				  ddb_entry->fw_ddb_index));
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_ERR, ha,
			   "%s: Failed to get IP Address\n",
			   __func__);
		rval = -EINVAL;
		जाओ निकास_set_param;
	पूर्ण

	/* CHAP */
	अगर (sess->username != शून्य && sess->password != शून्य) अणु
		अगर (म_माप(sess->username) && म_माप(sess->password)) अणु
			iscsi_opts |= BIT_7;

			rval = qla4xxx_get_chap_index(ha, sess->username,
						sess->password,
						LOCAL_CHAP, &idx);
			अगर (rval)
				जाओ निकास_set_param;

			fw_ddb_entry->chap_tbl_idx = cpu_to_le16(idx);
		पूर्ण
	पूर्ण

	अगर (sess->username_in != शून्य && sess->password_in != शून्य) अणु
		/* Check अगर BIDI CHAP */
		अगर (म_माप(sess->username_in) && म_माप(sess->password_in)) अणु
			iscsi_opts |= BIT_4;

			rval = qla4xxx_get_chap_index(ha, sess->username_in,
						      sess->password_in,
						      BIDI_CHAP, &idx);
			अगर (rval)
				जाओ निकास_set_param;
		पूर्ण
	पूर्ण

	अगर (sess->initial_r2t_en)
		iscsi_opts |= BIT_10;

	अगर (sess->imm_data_en)
		iscsi_opts |= BIT_11;

	fw_ddb_entry->iscsi_options = cpu_to_le16(iscsi_opts);

	अगर (conn->max_recv_dlength)
		fw_ddb_entry->iscsi_max_rcv_data_seg_len =
		  __स्थिरant_cpu_to_le16((conn->max_recv_dlength / BYTE_UNITS));

	अगर (sess->max_r2t)
		fw_ddb_entry->iscsi_max_outsnd_r2t = cpu_to_le16(sess->max_r2t);

	अगर (sess->first_burst)
		fw_ddb_entry->iscsi_first_burst_len =
		       __स्थिरant_cpu_to_le16((sess->first_burst / BYTE_UNITS));

	अगर (sess->max_burst)
		fw_ddb_entry->iscsi_max_burst_len =
			__स्थिरant_cpu_to_le16((sess->max_burst / BYTE_UNITS));

	अगर (sess->समय2रुको)
		fw_ddb_entry->iscsi_def_समय2रुको =
			cpu_to_le16(sess->समय2रुको);

	अगर (sess->समय2retain)
		fw_ddb_entry->iscsi_def_समय2retain =
			cpu_to_le16(sess->समय2retain);

	status = qla4xxx_set_ddb_entry(ha, ddb_entry->fw_ddb_index,
				       fw_ddb_entry_dma, mbx_sts);

	अगर (status != QLA_SUCCESS)
		rval = -EINVAL;
निकास_set_param:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(*fw_ddb_entry),
			  fw_ddb_entry, fw_ddb_entry_dma);
निकास_set_param_no_मुक्त:
	वापस rval;
पूर्ण

पूर्णांक qla4xxx_get_mgmt_data(काष्ठा scsi_qla_host *ha, uपूर्णांक16_t fw_ddb_index,
			  uपूर्णांक16_t stats_size, dma_addr_t stats_dma)
अणु
	पूर्णांक status = QLA_SUCCESS;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(mbox_cmd, 0, माप(mbox_cmd[0]) * MBOX_REG_COUNT);
	स_रखो(mbox_sts, 0, माप(mbox_sts[0]) * MBOX_REG_COUNT);
	mbox_cmd[0] = MBOX_CMD_GET_MANAGEMENT_DATA;
	mbox_cmd[1] = fw_ddb_index;
	mbox_cmd[2] = LSDW(stats_dma);
	mbox_cmd[3] = MSDW(stats_dma);
	mbox_cmd[4] = stats_size;

	status = qla4xxx_mailbox_command(ha, 5, 1, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,
				  "%s: MBOX_CMD_GET_MANAGEMENT_DATA "
				  "failed w/ status %04X\n", __func__,
				  mbox_sts[0]));
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_get_ip_state(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t acb_idx,
			 uपूर्णांक32_t ip_idx, uपूर्णांक32_t *sts)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status = QLA_SUCCESS;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));
	mbox_cmd[0] = MBOX_CMD_GET_IP_ADDR_STATE;
	mbox_cmd[1] = acb_idx;
	mbox_cmd[2] = ip_idx;

	status = qla4xxx_mailbox_command(ha, 3, 8, &mbox_cmd[0], &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_WARNING, ha,  "%s: "
				  "MBOX_CMD_GET_IP_ADDR_STATE failed w/ "
				  "status %04X\n", __func__, mbox_sts[0]));
	पूर्ण
	स_नकल(sts, mbox_sts, माप(mbox_sts));
	वापस status;
पूर्ण

पूर्णांक qla4xxx_get_nvram(काष्ठा scsi_qla_host *ha, dma_addr_t nvram_dma,
		      uपूर्णांक32_t offset, uपूर्णांक32_t size)
अणु
	पूर्णांक status = QLA_SUCCESS;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_NVRAM;
	mbox_cmd[1] = LSDW(nvram_dma);
	mbox_cmd[2] = MSDW(nvram_dma);
	mbox_cmd[3] = offset;
	mbox_cmd[4] = size;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: failed "
				  "status %04X\n", ha->host_no, __func__,
				  mbox_sts[0]));
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_set_nvram(काष्ठा scsi_qla_host *ha, dma_addr_t nvram_dma,
		      uपूर्णांक32_t offset, uपूर्णांक32_t size)
अणु
	पूर्णांक status = QLA_SUCCESS;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_SET_NVRAM;
	mbox_cmd[1] = LSDW(nvram_dma);
	mbox_cmd[2] = MSDW(nvram_dma);
	mbox_cmd[3] = offset;
	mbox_cmd[4] = size;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 1, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: failed "
				  "status %04X\n", ha->host_no, __func__,
				  mbox_sts[0]));
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qla4xxx_restore_factory_शेषs(काष्ठा scsi_qla_host *ha,
				     uपूर्णांक32_t region, uपूर्णांक32_t field0,
				     uपूर्णांक32_t field1)
अणु
	पूर्णांक status = QLA_SUCCESS;
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_RESTORE_FACTORY_DEFAULTS;
	mbox_cmd[3] = region;
	mbox_cmd[4] = field0;
	mbox_cmd[5] = field1;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 3, &mbox_cmd[0],
					 &mbox_sts[0]);
	अगर (status != QLA_SUCCESS) अणु
		DEBUG2(ql4_prपूर्णांकk(KERN_ERR, ha, "scsi%ld: %s: failed "
				  "status %04X\n", ha->host_no, __func__,
				  mbox_sts[0]));
	पूर्ण
	वापस status;
पूर्ण

/**
 * qla4_8xxx_set_param - set driver version in firmware.
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 * @param: Parameter to set i.e driver version
 **/
पूर्णांक qla4_8xxx_set_param(काष्ठा scsi_qla_host *ha, पूर्णांक param)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	uपूर्णांक32_t status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_SET_PARAM;
	अगर (param == SET_DRVR_VERSION) अणु
		mbox_cmd[1] = SET_DRVR_VERSION;
		म_नकलन((अक्षर *)&mbox_cmd[2], QLA4XXX_DRIVER_VERSION,
			MAX_DRVR_VER_LEN - 1);
	पूर्ण अन्यथा अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: invalid parameter 0x%x\n",
			   __func__, param);
		status = QLA_ERROR;
		जाओ निकास_set_param;
	पूर्ण

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, 2, mbox_cmd,
					 mbox_sts);
	अगर (status == QLA_ERROR)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed status %04X\n",
			   __func__, mbox_sts[0]);

निकास_set_param:
	वापस status;
पूर्ण

/**
 * qla4_83xx_post_idc_ack - post IDC ACK
 * @ha: Poपूर्णांकer to host adapter काष्ठाure.
 *
 * Posts IDC ACK क्रम IDC Request Notअगरication AEN.
 **/
पूर्णांक qla4_83xx_post_idc_ack(काष्ठा scsi_qla_host *ha)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_IDC_ACK;
	mbox_cmd[1] = ha->idc_info.request_desc;
	mbox_cmd[2] = ha->idc_info.info1;
	mbox_cmd[3] = ha->idc_info.info2;
	mbox_cmd[4] = ha->idc_info.info3;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, MBOX_REG_COUNT,
					 mbox_cmd, mbox_sts);
	अगर (status == QLA_ERROR)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed status %04X\n", __func__,
			   mbox_sts[0]);
	अन्यथा
	       ql4_prपूर्णांकk(KERN_INFO, ha, "%s: IDC ACK posted\n", __func__);

	वापस status;
पूर्ण

पूर्णांक qla4_84xx_config_acb(काष्ठा scsi_qla_host *ha, पूर्णांक acb_config)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	काष्ठा addr_ctrl_blk *acb = शून्य;
	uपूर्णांक32_t acb_len = माप(काष्ठा addr_ctrl_blk);
	पूर्णांक rval = QLA_SUCCESS;
	dma_addr_t acb_dma;

	acb = dma_alloc_coherent(&ha->pdev->dev,
				 माप(काष्ठा addr_ctrl_blk),
				 &acb_dma, GFP_KERNEL);
	अगर (!acb) अणु
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Unable to alloc acb\n", __func__);
		rval = QLA_ERROR;
		जाओ निकास_config_acb;
	पूर्ण
	स_रखो(acb, 0, acb_len);

	चयन (acb_config) अणु
	हाल ACB_CONFIG_DISABLE:
		rval = qla4xxx_get_acb(ha, acb_dma, 0, acb_len);
		अगर (rval != QLA_SUCCESS)
			जाओ निकास_मुक्त_acb;

		rval = qla4xxx_disable_acb(ha);
		अगर (rval != QLA_SUCCESS)
			जाओ निकास_मुक्त_acb;

		अगर (!ha->saved_acb)
			ha->saved_acb = kzalloc(acb_len, GFP_KERNEL);

		अगर (!ha->saved_acb) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Unable to alloc acb\n",
				   __func__);
			rval = QLA_ERROR;
			जाओ निकास_मुक्त_acb;
		पूर्ण
		स_नकल(ha->saved_acb, acb, acb_len);
		अवरोध;
	हाल ACB_CONFIG_SET:

		अगर (!ha->saved_acb) अणु
			ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Can't set ACB, Saved ACB not available\n",
				   __func__);
			rval = QLA_ERROR;
			जाओ निकास_मुक्त_acb;
		पूर्ण

		स_नकल(acb, ha->saved_acb, acb_len);

		rval = qla4xxx_set_acb(ha, &mbox_cmd[0], &mbox_sts[0], acb_dma);
		अगर (rval != QLA_SUCCESS)
			जाओ निकास_मुक्त_acb;

		अवरोध;
	शेष:
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: Invalid ACB Configuration\n",
			   __func__);
	पूर्ण

निकास_मुक्त_acb:
	dma_मुक्त_coherent(&ha->pdev->dev, माप(काष्ठा addr_ctrl_blk), acb,
			  acb_dma);
निकास_config_acb:
	अगर ((acb_config == ACB_CONFIG_SET) && ha->saved_acb) अणु
		kमुक्त(ha->saved_acb);
		ha->saved_acb = शून्य;
	पूर्ण
	DEBUG2(ql4_prपूर्णांकk(KERN_INFO, ha,
			  "%s %s\n", __func__,
			  rval == QLA_SUCCESS ? "SUCCEEDED" : "FAILED"));
	वापस rval;
पूर्ण

पूर्णांक qla4_83xx_get_port_config(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *config)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_GET_PORT_CONFIG;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, MBOX_REG_COUNT,
					 mbox_cmd, mbox_sts);
	अगर (status == QLA_SUCCESS)
		*config = mbox_sts[1];
	अन्यथा
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed status %04X\n", __func__,
			   mbox_sts[0]);

	वापस status;
पूर्ण

पूर्णांक qla4_83xx_set_port_config(काष्ठा scsi_qla_host *ha, uपूर्णांक32_t *config)
अणु
	uपूर्णांक32_t mbox_cmd[MBOX_REG_COUNT];
	uपूर्णांक32_t mbox_sts[MBOX_REG_COUNT];
	पूर्णांक status;

	स_रखो(&mbox_cmd, 0, माप(mbox_cmd));
	स_रखो(&mbox_sts, 0, माप(mbox_sts));

	mbox_cmd[0] = MBOX_CMD_SET_PORT_CONFIG;
	mbox_cmd[1] = *config;

	status = qla4xxx_mailbox_command(ha, MBOX_REG_COUNT, MBOX_REG_COUNT,
				mbox_cmd, mbox_sts);
	अगर (status != QLA_SUCCESS)
		ql4_prपूर्णांकk(KERN_ERR, ha, "%s: failed status %04X\n", __func__,
			   mbox_sts[0]);

	वापस status;
पूर्ण
