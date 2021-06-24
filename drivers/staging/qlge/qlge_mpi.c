<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "qlge.h"

पूर्णांक qlge_unछोड़ो_mpi_risc(काष्ठा qlge_adapter *qdev)
अणु
	u32 पंचांगp;

	/* Un-छोड़ो the RISC */
	पंचांगp = qlge_पढ़ो32(qdev, CSR);
	अगर (!(पंचांगp & CSR_RP))
		वापस -EIO;

	qlge_ग_लिखो32(qdev, CSR, CSR_CMD_CLR_PAUSE);
	वापस 0;
पूर्ण

पूर्णांक qlge_छोड़ो_mpi_risc(काष्ठा qlge_adapter *qdev)
अणु
	u32 पंचांगp;
	पूर्णांक count;

	/* Pause the RISC */
	qlge_ग_लिखो32(qdev, CSR, CSR_CMD_SET_PAUSE);
	क्रम (count = UDELAY_COUNT; count; count--) अणु
		पंचांगp = qlge_पढ़ो32(qdev, CSR);
		अगर (पंचांगp & CSR_RP)
			अवरोध;
		mdelay(UDELAY_DELAY);
	पूर्ण
	वापस (count == 0) ? -ETIMEDOUT : 0;
पूर्ण

पूर्णांक qlge_hard_reset_mpi_risc(काष्ठा qlge_adapter *qdev)
अणु
	u32 पंचांगp;
	पूर्णांक count;

	/* Reset the RISC */
	qlge_ग_लिखो32(qdev, CSR, CSR_CMD_SET_RST);
	क्रम (count = UDELAY_COUNT; count; count--) अणु
		पंचांगp = qlge_पढ़ो32(qdev, CSR);
		अगर (पंचांगp & CSR_RR) अणु
			qlge_ग_लिखो32(qdev, CSR, CSR_CMD_CLR_RST);
			अवरोध;
		पूर्ण
		mdelay(UDELAY_DELAY);
	पूर्ण
	वापस (count == 0) ? -ETIMEDOUT : 0;
पूर्ण

पूर्णांक qlge_पढ़ो_mpi_reg(काष्ठा qlge_adapter *qdev, u32 reg, u32 *data)
अणु
	पूर्णांक status;
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev, PROC_ADDR, PROC_ADDR_RDY, PROC_ADDR_ERR);
	अगर (status)
		जाओ निकास;
	/* set up क्रम reg पढ़ो */
	qlge_ग_लिखो32(qdev, PROC_ADDR, reg | PROC_ADDR_R);
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev, PROC_ADDR, PROC_ADDR_RDY, PROC_ADDR_ERR);
	अगर (status)
		जाओ निकास;
	/* get the data */
	*data = qlge_पढ़ो32(qdev, PROC_DATA);
निकास:
	वापस status;
पूर्ण

पूर्णांक qlge_ग_लिखो_mpi_reg(काष्ठा qlge_adapter *qdev, u32 reg, u32 data)
अणु
	पूर्णांक status = 0;
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev, PROC_ADDR, PROC_ADDR_RDY, PROC_ADDR_ERR);
	अगर (status)
		जाओ निकास;
	/* ग_लिखो the data to the data reg */
	qlge_ग_लिखो32(qdev, PROC_DATA, data);
	/* trigger the ग_लिखो */
	qlge_ग_लिखो32(qdev, PROC_ADDR, reg);
	/* रुको क्रम reg to come पढ़ोy */
	status = qlge_रुको_reg_rdy(qdev, PROC_ADDR, PROC_ADDR_RDY, PROC_ADDR_ERR);
	अगर (status)
		जाओ निकास;
निकास:
	वापस status;
पूर्ण

पूर्णांक qlge_soft_reset_mpi_risc(काष्ठा qlge_adapter *qdev)
अणु
	वापस qlge_ग_लिखो_mpi_reg(qdev, 0x00001010, 1);
पूर्ण

/* Determine अगर we are in अक्षरge of the firmware. If
 * we are the lower of the 2 NIC pcie functions, or अगर
 * we are the higher function and the lower function
 * is not enabled.
 */
पूर्णांक qlge_own_firmware(काष्ठा qlge_adapter *qdev)
अणु
	u32 temp;

	/* If we are the lower of the 2 NIC functions
	 * on the chip the we are responsible क्रम
	 * core dump and firmware reset after an error.
	 */
	अगर (qdev->func < qdev->alt_func)
		वापस 1;

	/* If we are the higher of the 2 NIC functions
	 * on the chip and the lower function is not
	 * enabled, then we are responsible क्रम
	 * core dump and firmware reset after an error.
	 */
	temp =  qlge_पढ़ो32(qdev, STS);
	अगर (!(temp & (1 << (8 + qdev->alt_func))))
		वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक qlge_get_mb_sts(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक i, status;

	status = qlge_sem_spinlock(qdev, SEM_PROC_REG_MASK);
	अगर (status)
		वापस -EBUSY;
	क्रम (i = 0; i < mbcp->out_count; i++) अणु
		status =
		    qlge_पढ़ो_mpi_reg(qdev, qdev->mailbox_out + i,
				      &mbcp->mbox_out[i]);
		अगर (status) अणु
			netअगर_err(qdev, drv, qdev->ndev, "Failed mailbox read.\n");
			अवरोध;
		पूर्ण
	पूर्ण
	qlge_sem_unlock(qdev, SEM_PROC_REG_MASK);	/* करोes flush too */
	वापस status;
पूर्ण

/* Wait क्रम a single mailbox command to complete.
 * Returns zero on success.
 */
अटल पूर्णांक qlge_रुको_mbx_cmd_cmplt(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक count;
	u32 value;

	क्रम (count = 100; count; count--) अणु
		value = qlge_पढ़ो32(qdev, STS);
		अगर (value & STS_PI)
			वापस 0;
		mdelay(UDELAY_DELAY); /* 100ms */
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

/* Execute a single mailbox command.
 * Caller must hold PROC_ADDR semaphore.
 */
अटल पूर्णांक qlge_exec_mb_cmd(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक i, status;

	/*
	 * Make sure there's nothing pending.
	 * This shouldn't happen.
	 */
	अगर (qlge_पढ़ो32(qdev, CSR) & CSR_HRI)
		वापस -EIO;

	status = qlge_sem_spinlock(qdev, SEM_PROC_REG_MASK);
	अगर (status)
		वापस status;

	/*
	 * Fill the outbound mailboxes.
	 */
	क्रम (i = 0; i < mbcp->in_count; i++) अणु
		status = qlge_ग_लिखो_mpi_reg(qdev, qdev->mailbox_in + i,
					    mbcp->mbox_in[i]);
		अगर (status)
			जाओ end;
	पूर्ण
	/*
	 * Wake up the MPI firmware.
	 */
	qlge_ग_लिखो32(qdev, CSR, CSR_CMD_SET_H2R_INT);
end:
	qlge_sem_unlock(qdev, SEM_PROC_REG_MASK);
	वापस status;
पूर्ण

/* We are being asked by firmware to accept
 * a change to the port.  This is only
 * a change to max frame sizes (Tx/Rx), छोड़ो
 * parameters, or loopback mode. We wake up a worker
 * to handler processing this since a mailbox command
 * will need to be sent to ACK the request.
 */
अटल पूर्णांक qlge_idc_req_aen(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;
	काष्ठा mbox_params *mbcp = &qdev->idc_mbc;

	netअगर_err(qdev, drv, qdev->ndev, "Enter!\n");
	/* Get the status data and start up a thपढ़ो to
	 * handle the request.
	 */
	mbcp->out_count = 4;
	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Could not read MPI, resetting ASIC!\n");
		qlge_queue_asic_error(qdev);
	पूर्ण अन्यथा	अणु
		/* Begin polled mode early so
		 * we करोn't get another पूर्णांकerrupt
		 * when we leave mpi_worker.
		 */
		qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16));
		queue_delayed_work(qdev->workqueue, &qdev->mpi_idc_work, 0);
	पूर्ण
	वापस status;
पूर्ण

/* Process an पूर्णांकer-device event completion.
 * If good, संकेत the caller's completion.
 */
अटल पूर्णांक qlge_idc_cmplt_aen(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;
	काष्ठा mbox_params *mbcp = &qdev->idc_mbc;

	mbcp->out_count = 4;
	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Could not read MPI, resetting RISC!\n");
		qlge_queue_fw_error(qdev);
	पूर्ण अन्यथा अणु
		/* Wake up the sleeping mpi_idc_work thपढ़ो that is
		 * रुकोing क्रम this event.
		 */
		complete(&qdev->ide_completion);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम qlge_link_up(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;

	mbcp->out_count = 2;

	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "%s: Could not get mailbox status.\n", __func__);
		वापस;
	पूर्ण

	qdev->link_status = mbcp->mbox_out[1];
	netअगर_err(qdev, drv, qdev->ndev, "Link Up.\n");

	/* If we're coming back from an IDC event
	 * then set up the CAM and frame routing.
	 */
	अगर (test_bit(QL_CAM_RT_SET, &qdev->flags)) अणु
		status = qlge_cam_route_initialize(qdev);
		अगर (status) अणु
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Failed to init CAM/Routing tables.\n");
			वापस;
		पूर्ण
		clear_bit(QL_CAM_RT_SET, &qdev->flags);
	पूर्ण

	/* Queue up a worker to check the frame
	 * size inक्रमmation, and fix it अगर it's not
	 * to our liking.
	 */
	अगर (!test_bit(QL_PORT_CFG, &qdev->flags)) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Queue Port Config Worker!\n");
		set_bit(QL_PORT_CFG, &qdev->flags);
		/* Begin polled mode early so
		 * we करोn't get another पूर्णांकerrupt
		 * when we leave mpi_worker dpc.
		 */
		qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16));
		queue_delayed_work(qdev->workqueue,
				   &qdev->mpi_port_cfg_work, 0);
	पूर्ण

	qlge_link_on(qdev);
पूर्ण

अटल व्योम qlge_link_करोwn(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;

	mbcp->out_count = 3;

	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status)
		netअगर_err(qdev, drv, qdev->ndev, "Link down AEN broken!\n");

	qlge_link_off(qdev);
पूर्ण

अटल पूर्णांक qlge_sfp_in(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;

	mbcp->out_count = 5;

	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status)
		netअगर_err(qdev, drv, qdev->ndev, "SFP in AEN broken!\n");
	अन्यथा
		netअगर_err(qdev, drv, qdev->ndev, "SFP insertion detected.\n");

	वापस status;
पूर्ण

अटल पूर्णांक qlge_sfp_out(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;

	mbcp->out_count = 1;

	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status)
		netअगर_err(qdev, drv, qdev->ndev, "SFP out AEN broken!\n");
	अन्यथा
		netअगर_err(qdev, drv, qdev->ndev, "SFP removal detected.\n");

	वापस status;
पूर्ण

अटल पूर्णांक qlge_aen_lost(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;

	mbcp->out_count = 6;

	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Lost AEN broken!\n");
	पूर्ण अन्यथा अणु
		पूर्णांक i;

		netअगर_err(qdev, drv, qdev->ndev, "Lost AEN detected.\n");
		क्रम (i = 0; i < mbcp->out_count; i++)
			netअगर_err(qdev, drv, qdev->ndev, "mbox_out[%d] = 0x%.08x.\n",
				  i, mbcp->mbox_out[i]);
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम qlge_init_fw_करोne(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;

	mbcp->out_count = 2;

	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Firmware did not initialize!\n");
	पूर्ण अन्यथा अणु
		netअगर_err(qdev, drv, qdev->ndev, "Firmware Revision  = 0x%.08x.\n",
			  mbcp->mbox_out[1]);
		qdev->fw_rev_id = mbcp->mbox_out[1];
		status = qlge_cam_route_initialize(qdev);
		अगर (status)
			netअगर_err(qdev, अगरup, qdev->ndev,
				  "Failed to init CAM/Routing tables.\n");
	पूर्ण
पूर्ण

/* Process an async event and clear it unless it's an
 * error condition.
 *  This can get called iteratively from the mpi_work thपढ़ो
 *  when events arrive via an पूर्णांकerrupt.
 *  It also माला_लो called when a mailbox command is polling क्रम
 *  it's completion.
 */
अटल पूर्णांक qlge_mpi_handler(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;
	पूर्णांक orig_count = mbcp->out_count;

	/* Just get mailbox zero क्रम now. */
	mbcp->out_count = 1;
	status = qlge_get_mb_sts(qdev, mbcp);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Could not read MPI, resetting ASIC!\n");
		qlge_queue_asic_error(qdev);
		जाओ end;
	पूर्ण

	चयन (mbcp->mbox_out[0]) अणु
		/* This हाल is only active when we arrive here
		 * as a result of issuing a mailbox command to
		 * the firmware.
		 */
	हाल MB_CMD_STS_INTRMDT:
	हाल MB_CMD_STS_GOOD:
	हाल MB_CMD_STS_INVLD_CMD:
	हाल MB_CMD_STS_XFC_ERR:
	हाल MB_CMD_STS_CSUM_ERR:
	हाल MB_CMD_STS_ERR:
	हाल MB_CMD_STS_PARAM_ERR:
		/* We can only get mailbox status अगर we're polling from an
		 * unfinished command.  Get the rest of the status data and
		 * वापस back to the caller.
		 * We only end up here when we're polling क्रम a mailbox
		 * command completion.
		 */
		mbcp->out_count = orig_count;
		status = qlge_get_mb_sts(qdev, mbcp);
		वापस status;

		/* We are being asked by firmware to accept
		 * a change to the port.  This is only
		 * a change to max frame sizes (Tx/Rx), छोड़ो
		 * parameters, or loopback mode.
		 */
	हाल AEN_IDC_REQ:
		status = qlge_idc_req_aen(qdev);
		अवरोध;

		/* Process and inbound IDC event.
		 * This will happen when we're trying to
		 * change tx/rx max frame size, change छोड़ो
		 * parameters or loopback mode.
		 */
	हाल AEN_IDC_CMPLT:
	हाल AEN_IDC_EXT:
		status = qlge_idc_cmplt_aen(qdev);
		अवरोध;

	हाल AEN_LINK_UP:
		qlge_link_up(qdev, mbcp);
		अवरोध;

	हाल AEN_LINK_DOWN:
		qlge_link_करोwn(qdev, mbcp);
		अवरोध;

	हाल AEN_FW_INIT_DONE:
		/* If we're in process on executing the firmware,
		 * then convert the status to normal mailbox status.
		 */
		अगर (mbcp->mbox_in[0] == MB_CMD_EX_FW) अणु
			mbcp->out_count = orig_count;
			status = qlge_get_mb_sts(qdev, mbcp);
			mbcp->mbox_out[0] = MB_CMD_STS_GOOD;
			वापस status;
		पूर्ण
		qlge_init_fw_करोne(qdev, mbcp);
		अवरोध;

	हाल AEN_AEN_SFP_IN:
		qlge_sfp_in(qdev, mbcp);
		अवरोध;

	हाल AEN_AEN_SFP_OUT:
		qlge_sfp_out(qdev, mbcp);
		अवरोध;

		/* This event can arrive at boot समय or after an
		 * MPI reset अगर the firmware failed to initialize.
		 */
	हाल AEN_FW_INIT_FAIL:
		/* If we're in process on executing the firmware,
		 * then convert the status to normal mailbox status.
		 */
		अगर (mbcp->mbox_in[0] == MB_CMD_EX_FW) अणु
			mbcp->out_count = orig_count;
			status = qlge_get_mb_sts(qdev, mbcp);
			mbcp->mbox_out[0] = MB_CMD_STS_ERR;
			वापस status;
		पूर्ण
		netअगर_err(qdev, drv, qdev->ndev,
			  "Firmware initialization failed.\n");
		status = -EIO;
		qlge_queue_fw_error(qdev);
		अवरोध;

	हाल AEN_SYS_ERR:
		netअगर_err(qdev, drv, qdev->ndev, "System Error.\n");
		qlge_queue_fw_error(qdev);
		status = -EIO;
		अवरोध;

	हाल AEN_AEN_LOST:
		qlge_aen_lost(qdev, mbcp);
		अवरोध;

	हाल AEN_DCBX_CHG:
		/* Need to support AEN 8110 */
		अवरोध;
	शेष:
		netअगर_err(qdev, drv, qdev->ndev,
			  "Unsupported AE %.08x.\n", mbcp->mbox_out[0]);
		/* Clear the MPI firmware status. */
	पूर्ण
end:
	qlge_ग_लिखो32(qdev, CSR, CSR_CMD_CLR_R2PCI_INT);
	/* Restore the original mailbox count to
	 * what the caller asked क्रम.  This can get
	 * changed when a mailbox command is रुकोing
	 * क्रम a response and an AEN arrives and
	 * is handled.
	 */
	mbcp->out_count = orig_count;
	वापस status;
पूर्ण

/* Execute a single mailbox command.
 * mbcp is a poपूर्णांकer to an array of u32.  Each
 * element in the array contains the value क्रम it's
 * respective mailbox रेजिस्टर.
 */
अटल पूर्णांक qlge_mailbox_command(काष्ठा qlge_adapter *qdev, काष्ठा mbox_params *mbcp)
अणु
	पूर्णांक status;
	अचिन्हित दीर्घ count;

	mutex_lock(&qdev->mpi_mutex);

	/* Begin polled mode क्रम MPI */
	qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16));

	/* Load the mailbox रेजिस्टरs and wake up MPI RISC. */
	status = qlge_exec_mb_cmd(qdev, mbcp);
	अगर (status)
		जाओ end;

	/* If we're generating a system error, then there's nothing
	 * to रुको क्रम.
	 */
	अगर (mbcp->mbox_in[0] == MB_CMD_MAKE_SYS_ERR)
		जाओ end;

	/* Wait क्रम the command to complete. We loop
	 * here because some AEN might arrive जबतक
	 * we're रुकोing क्रम the mailbox command to
	 * complete. If more than 5 seconds expire we can
	 * assume something is wrong.
	 */
	count = jअगरfies + HZ * MAILBOX_TIMEOUT;
	करो अणु
		/* Wait क्रम the पूर्णांकerrupt to come in. */
		status = qlge_रुको_mbx_cmd_cmplt(qdev);
		अगर (status)
			जारी;

		/* Process the event.  If it's an AEN, it
		 * will be handled in-line or a worker
		 * will be spawned. If it's our completion
		 * we will catch it below.
		 */
		status = qlge_mpi_handler(qdev, mbcp);
		अगर (status)
			जाओ end;

		/* It's either the completion क्रम our mailbox
		 * command complete or an AEN.  If it's our
		 * completion then get out.
		 */
		अगर (((mbcp->mbox_out[0] & 0x0000f000) ==
		     MB_CMD_STS_GOOD) ||
		    ((mbcp->mbox_out[0] & 0x0000f000) ==
		     MB_CMD_STS_INTRMDT))
			जाओ करोne;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, count));

	netअगर_err(qdev, drv, qdev->ndev,
		  "Timed out waiting for mailbox complete.\n");
	status = -ETIMEDOUT;
	जाओ end;

करोne:

	/* Now we can clear the पूर्णांकerrupt condition
	 * and look at our status.
	 */
	qlge_ग_लिखो32(qdev, CSR, CSR_CMD_CLR_R2PCI_INT);

	अगर (((mbcp->mbox_out[0] & 0x0000f000) !=
	     MB_CMD_STS_GOOD) &&
	    ((mbcp->mbox_out[0] & 0x0000f000) !=
	     MB_CMD_STS_INTRMDT)) अणु
		status = -EIO;
	पूर्ण
end:
	/* End polled mode क्रम MPI */
	qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16) | INTR_MASK_PI);
	mutex_unlock(&qdev->mpi_mutex);
	वापस status;
पूर्ण

/* Get MPI firmware version. This will be used क्रम
 * driver banner and क्रम ethtool info.
 * Returns zero on success.
 */
पूर्णांक qlge_mb_about_fw(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status = 0;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 1;
	mbcp->out_count = 3;

	mbcp->mbox_in[0] = MB_CMD_ABOUT_FW;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed about firmware command\n");
		status = -EIO;
	पूर्ण

	/* Store the firmware version */
	qdev->fw_rev_id = mbcp->mbox_out[1];

	वापस status;
पूर्ण

/* Get functional state क्रम MPI firmware.
 * Returns zero on success.
 */
पूर्णांक qlge_mb_get_fw_state(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status = 0;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 1;
	mbcp->out_count = 2;

	mbcp->mbox_in[0] = MB_CMD_GET_FW_STATE;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed Get Firmware State.\n");
		status = -EIO;
	पूर्ण

	/* If bit zero is set in mbx 1 then the firmware is
	 * running, but not initialized.  This should never
	 * happen.
	 */
	अगर (mbcp->mbox_out[1] & 1) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Firmware waiting for initialization.\n");
		status = -EIO;
	पूर्ण

	वापस status;
पूर्ण

/* Send and ACK mailbox command to the firmware to
 * let it जारी with the change.
 */
अटल पूर्णांक qlge_mb_idc_ack(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status = 0;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 5;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_IDC_ACK;
	mbcp->mbox_in[1] = qdev->idc_mbc.mbox_out[1];
	mbcp->mbox_in[2] = qdev->idc_mbc.mbox_out[2];
	mbcp->mbox_in[3] = qdev->idc_mbc.mbox_out[3];
	mbcp->mbox_in[4] = qdev->idc_mbc.mbox_out[4];

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Failed IDC ACK send.\n");
		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

/* Get link settings and maximum frame size settings
 * क्रम the current port.
 * Most likely will block.
 */
पूर्णांक qlge_mb_set_port_cfg(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status = 0;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 3;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_SET_PORT_CFG;
	mbcp->mbox_in[1] = qdev->link_config;
	mbcp->mbox_in[2] = qdev->max_frame_size;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] == MB_CMD_STS_INTRMDT) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Port Config sent, wait for IDC.\n");
	पूर्ण अन्यथा	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed Set Port Configuration.\n");
		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

अटल पूर्णांक qlge_mb_dump_ram(काष्ठा qlge_adapter *qdev, u64 req_dma, u32 addr,
			    u32 size)
अणु
	पूर्णांक status = 0;
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 9;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_DUMP_RISC_RAM;
	mbcp->mbox_in[1] = LSW(addr);
	mbcp->mbox_in[2] = MSW(req_dma);
	mbcp->mbox_in[3] = LSW(req_dma);
	mbcp->mbox_in[4] = MSW(size);
	mbcp->mbox_in[5] = LSW(size);
	mbcp->mbox_in[6] = MSW(MSD(req_dma));
	mbcp->mbox_in[7] = LSW(MSD(req_dma));
	mbcp->mbox_in[8] = MSW(addr);

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Failed to dump risc RAM.\n");
		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

/* Issue a mailbox command to dump RISC RAM. */
पूर्णांक qlge_dump_risc_ram_area(काष्ठा qlge_adapter *qdev, व्योम *buf,
			    u32 ram_addr, पूर्णांक word_count)
अणु
	पूर्णांक status;
	अक्षर *my_buf;
	dma_addr_t buf_dma;

	my_buf = dma_alloc_coherent(&qdev->pdev->dev,
				    word_count * माप(u32), &buf_dma,
				    GFP_ATOMIC);
	अगर (!my_buf)
		वापस -EIO;

	status = qlge_mb_dump_ram(qdev, buf_dma, ram_addr, word_count);
	अगर (!status)
		स_नकल(buf, my_buf, word_count * माप(u32));

	dma_मुक्त_coherent(&qdev->pdev->dev, word_count * माप(u32), my_buf,
			  buf_dma);
	वापस status;
पूर्ण

/* Get link settings and maximum frame size settings
 * क्रम the current port.
 * Most likely will block.
 */
पूर्णांक qlge_mb_get_port_cfg(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status = 0;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 1;
	mbcp->out_count = 3;

	mbcp->mbox_in[0] = MB_CMD_GET_PORT_CFG;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed Get Port Configuration.\n");
		status = -EIO;
	पूर्ण अन्यथा	अणु
		netअगर_prपूर्णांकk(qdev, drv, KERN_DEBUG, qdev->ndev,
			     "Passed Get Port Configuration.\n");
		qdev->link_config = mbcp->mbox_out[1];
		qdev->max_frame_size = mbcp->mbox_out[2];
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qlge_mb_wol_mode(काष्ठा qlge_adapter *qdev, u32 wol)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 2;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_SET_WOL_MODE;
	mbcp->mbox_in[1] = wol;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Failed to set WOL mode.\n");
		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qlge_mb_wol_set_magic(काष्ठा qlge_adapter *qdev, u32 enable_wol)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status;
	u8 *addr = qdev->ndev->dev_addr;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 8;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_SET_WOL_MAGIC;
	अगर (enable_wol) अणु
		mbcp->mbox_in[1] = (u32)addr[0];
		mbcp->mbox_in[2] = (u32)addr[1];
		mbcp->mbox_in[3] = (u32)addr[2];
		mbcp->mbox_in[4] = (u32)addr[3];
		mbcp->mbox_in[5] = (u32)addr[4];
		mbcp->mbox_in[6] = (u32)addr[5];
		mbcp->mbox_in[7] = 0;
	पूर्ण अन्यथा अणु
		mbcp->mbox_in[1] = 0;
		mbcp->mbox_in[2] = 1;
		mbcp->mbox_in[3] = 1;
		mbcp->mbox_in[4] = 1;
		mbcp->mbox_in[5] = 1;
		mbcp->mbox_in[6] = 1;
		mbcp->mbox_in[7] = 0;
	पूर्ण

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Failed to set WOL mode.\n");
		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

/* IDC - Inter Device Communication...
 * Some firmware commands require consent of adjacent FCOE
 * function.  This function रुकोs क्रम the OK, or a
 * counter-request क्रम a little more समय.i
 * The firmware will complete the request अगर the other
 * function करोesn't respond.
 */
अटल पूर्णांक qlge_idc_रुको(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status = -ETIMEDOUT;
	काष्ठा mbox_params *mbcp = &qdev->idc_mbc;
	दीर्घ रुको_समय;

	क्रम (रुको_समय = 1 * HZ; रुको_समय;) अणु
		/* Wait here क्रम the command to complete
		 * via the IDC process.
		 */
		रुको_समय =
			रुको_क्रम_completion_समयout(&qdev->ide_completion,
						    रुको_समय);
		अगर (!रुको_समय) अणु
			netअगर_err(qdev, drv, qdev->ndev, "IDC Timeout.\n");
			अवरोध;
		पूर्ण
		/* Now examine the response from the IDC process.
		 * We might have a good completion or a request क्रम
		 * more रुको समय.
		 */
		अगर (mbcp->mbox_out[0] == AEN_IDC_EXT) अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "IDC Time Extension from function.\n");
			रुको_समय += (mbcp->mbox_out[1] >> 8) & 0x0000000f;
		पूर्ण अन्यथा अगर (mbcp->mbox_out[0] == AEN_IDC_CMPLT) अणु
			netअगर_err(qdev, drv, qdev->ndev, "IDC Success.\n");
			status = 0;
			अवरोध;
		पूर्ण अन्यथा अणु
			netअगर_err(qdev, drv, qdev->ndev,
				  "IDC: Invalid State 0x%.04x.\n",
				  mbcp->mbox_out[0]);
			status = -EIO;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक qlge_mb_set_led_cfg(काष्ठा qlge_adapter *qdev, u32 led_config)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 2;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_SET_LED_CFG;
	mbcp->mbox_in[1] = led_config;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed to set LED Configuration.\n");
		status = -EIO;
	पूर्ण

	वापस status;
पूर्ण

पूर्णांक qlge_mb_get_led_cfg(काष्ठा qlge_adapter *qdev)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 1;
	mbcp->out_count = 2;

	mbcp->mbox_in[0] = MB_CMD_GET_LED_CFG;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] != MB_CMD_STS_GOOD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed to get LED Configuration.\n");
		status = -EIO;
	पूर्ण अन्यथा अणु
		qdev->led_config = mbcp->mbox_out[1];
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qlge_mb_set_mgmnt_traffic_ctl(काष्ठा qlge_adapter *qdev, u32 control)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));

	mbcp->in_count = 1;
	mbcp->out_count = 2;

	mbcp->mbox_in[0] = MB_CMD_SET_MGMNT_TFK_CTL;
	mbcp->mbox_in[1] = control;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] == MB_CMD_STS_GOOD)
		वापस status;

	अगर (mbcp->mbox_out[0] == MB_CMD_STS_INVLD_CMD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Command not supported by firmware.\n");
		status = -EINVAL;
	पूर्ण अन्यथा अगर (mbcp->mbox_out[0] == MB_CMD_STS_ERR) अणु
		/* This indicates that the firmware is
		 * alपढ़ोy in the state we are trying to
		 * change it to.
		 */
		netअगर_err(qdev, drv, qdev->ndev,
			  "Command parameters make no change.\n");
	पूर्ण
	वापस status;
पूर्ण

/* Returns a negative error code or the mailbox command status. */
अटल पूर्णांक qlge_mb_get_mgmnt_traffic_ctl(काष्ठा qlge_adapter *qdev, u32 *control)
अणु
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक status;

	स_रखो(mbcp, 0, माप(काष्ठा mbox_params));
	*control = 0;

	mbcp->in_count = 1;
	mbcp->out_count = 1;

	mbcp->mbox_in[0] = MB_CMD_GET_MGMNT_TFK_CTL;

	status = qlge_mailbox_command(qdev, mbcp);
	अगर (status)
		वापस status;

	अगर (mbcp->mbox_out[0] == MB_CMD_STS_GOOD) अणु
		*control = mbcp->mbox_in[1];
		वापस status;
	पूर्ण

	अगर (mbcp->mbox_out[0] == MB_CMD_STS_INVLD_CMD) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Command not supported by firmware.\n");
		status = -EINVAL;
	पूर्ण अन्यथा अगर (mbcp->mbox_out[0] == MB_CMD_STS_ERR) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Failed to get MPI traffic control.\n");
		status = -EIO;
	पूर्ण
	वापस status;
पूर्ण

पूर्णांक qlge_रुको_fअगरo_empty(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक count;
	u32 mgmnt_fअगरo_empty;
	u32 nic_fअगरo_empty;

	क्रम (count = 6; count; count--) अणु
		nic_fअगरo_empty = qlge_पढ़ो32(qdev, STS) & STS_NFE;
		qlge_mb_get_mgmnt_traffic_ctl(qdev, &mgmnt_fअगरo_empty);
		mgmnt_fअगरo_empty &= MB_GET_MPI_TFK_FIFO_EMPTY;
		अगर (nic_fअगरo_empty && mgmnt_fअगरo_empty)
			वापस 0;
		msleep(100);
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

/* API called in work thपढ़ो context to set new TX/RX
 * maximum frame size values to match MTU.
 */
अटल पूर्णांक qlge_set_port_cfg(काष्ठा qlge_adapter *qdev)
अणु
	पूर्णांक status;

	status = qlge_mb_set_port_cfg(qdev);
	अगर (status)
		वापस status;
	status = qlge_idc_रुको(qdev);
	वापस status;
पूर्ण

/* The following routines are worker thपढ़ोs that process
 * events that may sleep रुकोing क्रम completion.
 */

/* This thपढ़ो माला_लो the maximum TX and RX frame size values
 * from the firmware and, अगर necessary, changes them to match
 * the MTU setting.
 */
व्योम qlge_mpi_port_cfg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlge_adapter *qdev =
		container_of(work, काष्ठा qlge_adapter, mpi_port_cfg_work.work);
	पूर्णांक status;

	status = qlge_mb_get_port_cfg(qdev);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Bug: Failed to get port config data.\n");
		जाओ err;
	पूर्ण

	अगर (qdev->link_config & CFG_JUMBO_FRAME_SIZE &&
	    qdev->max_frame_size == CFG_DEFAULT_MAX_FRAME_SIZE)
		जाओ end;

	qdev->link_config |=	CFG_JUMBO_FRAME_SIZE;
	qdev->max_frame_size = CFG_DEFAULT_MAX_FRAME_SIZE;
	status = qlge_set_port_cfg(qdev);
	अगर (status) अणु
		netअगर_err(qdev, drv, qdev->ndev,
			  "Bug: Failed to set port config data.\n");
		जाओ err;
	पूर्ण
end:
	clear_bit(QL_PORT_CFG, &qdev->flags);
	वापस;
err:
	qlge_queue_fw_error(qdev);
	जाओ end;
पूर्ण

/* Process an पूर्णांकer-device request.  This is issues by
 * the firmware in response to another function requesting
 * a change to the port. We set a flag to indicate a change
 * has been made and then send a mailbox command ACKing
 * the change request.
 */
व्योम qlge_mpi_idc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlge_adapter *qdev =
		container_of(work, काष्ठा qlge_adapter, mpi_idc_work.work);
	पूर्णांक status;
	काष्ठा mbox_params *mbcp = &qdev->idc_mbc;
	u32 aen;
	पूर्णांक समयout;

	aen = mbcp->mbox_out[1] >> 16;
	समयout = (mbcp->mbox_out[1] >> 8) & 0xf;

	चयन (aen) अणु
	शेष:
		netअगर_err(qdev, drv, qdev->ndev,
			  "Bug: Unhandled IDC action.\n");
		अवरोध;
	हाल MB_CMD_PORT_RESET:
	हाल MB_CMD_STOP_FW:
		qlge_link_off(qdev);
		fallthrough;
	हाल MB_CMD_SET_PORT_CFG:
		/* Signal the resulting link up AEN
		 * that the frame routing and mac addr
		 * needs to be set.
		 */
		set_bit(QL_CAM_RT_SET, &qdev->flags);
		/* Do ACK अगर required */
		अगर (समयout) अणु
			status = qlge_mb_idc_ack(qdev);
			अगर (status)
				netअगर_err(qdev, drv, qdev->ndev,
					  "Bug: No pending IDC!\n");
		पूर्ण अन्यथा अणु
			netअगर_prपूर्णांकk(qdev, drv, KERN_DEBUG, qdev->ndev,
				     "IDC ACK not required\n");
			status = 0; /* success */
		पूर्ण
		अवरोध;

		/* These sub-commands issued by another (FCoE)
		 * function are requesting to करो an operation
		 * on the shared resource (MPI environment).
		 * We currently करोn't issue these so we just
		 * ACK the request.
		 */
	हाल MB_CMD_IOP_RESTART_MPI:
	हाल MB_CMD_IOP_PREP_LINK_DOWN:
		/* Drop the link, reload the routing
		 * table when link comes up.
		 */
		qlge_link_off(qdev);
		set_bit(QL_CAM_RT_SET, &qdev->flags);
		fallthrough;
	हाल MB_CMD_IOP_DVR_START:
	हाल MB_CMD_IOP_FLASH_ACC:
	हाल MB_CMD_IOP_CORE_DUMP_MPI:
	हाल MB_CMD_IOP_PREP_UPDATE_MPI:
	हाल MB_CMD_IOP_COMP_UPDATE_MPI:
	हाल MB_CMD_IOP_NONE:	/*  an IDC without params */
		/* Do ACK अगर required */
		अगर (समयout) अणु
			status = qlge_mb_idc_ack(qdev);
			अगर (status)
				netअगर_err(qdev, drv, qdev->ndev,
					  "Bug: No pending IDC!\n");
		पूर्ण अन्यथा अणु
			netअगर_prपूर्णांकk(qdev, drv, KERN_DEBUG, qdev->ndev,
				     "IDC ACK not required\n");
			status = 0; /* success */
		पूर्ण
		अवरोध;
	पूर्ण
पूर्ण

व्योम qlge_mpi_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlge_adapter *qdev =
		container_of(work, काष्ठा qlge_adapter, mpi_work.work);
	काष्ठा mbox_params mbc;
	काष्ठा mbox_params *mbcp = &mbc;
	पूर्णांक err = 0;

	mutex_lock(&qdev->mpi_mutex);
	/* Begin polled mode क्रम MPI */
	qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16));

	जबतक (qlge_पढ़ो32(qdev, STS) & STS_PI) अणु
		स_रखो(mbcp, 0, माप(काष्ठा mbox_params));
		mbcp->out_count = 1;
		/* Don't जारी अगर an async event
		 * did not complete properly.
		 */
		err = qlge_mpi_handler(qdev, mbcp);
		अगर (err)
			अवरोध;
	पूर्ण

	/* End polled mode क्रम MPI */
	qlge_ग_लिखो32(qdev, INTR_MASK, (INTR_MASK_PI << 16) | INTR_MASK_PI);
	mutex_unlock(&qdev->mpi_mutex);
पूर्ण

व्योम qlge_mpi_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qlge_adapter *qdev =
		container_of(work, काष्ठा qlge_adapter, mpi_reset_work.work);
	cancel_delayed_work_sync(&qdev->mpi_work);
	cancel_delayed_work_sync(&qdev->mpi_port_cfg_work);
	cancel_delayed_work_sync(&qdev->mpi_idc_work);
	/* If we're not the करोminant NIC function,
	 * then there is nothing to करो.
	 */
	अगर (!qlge_own_firmware(qdev)) अणु
		netअगर_err(qdev, drv, qdev->ndev, "Don't own firmware!\n");
		वापस;
	पूर्ण

	qlge_soft_reset_mpi_risc(qdev);
पूर्ण
