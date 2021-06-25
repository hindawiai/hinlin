<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * H/W layer of ISHTP provider device (ISH)
 *
 * Copyright (c) 2014-2016, Intel Corporation.
 */

#समावेश <linux/sched.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/jअगरfies.h>
#समावेश "client.h"
#समावेश "hw-ish.h"
#समावेश "hbm.h"

/* For FW reset flow */
अटल काष्ठा work_काष्ठा fw_reset_work;
अटल काष्ठा ishtp_device *ishtp_dev;

/**
 * ish_reg_पढ़ो() - Read रेजिस्टर
 * @dev: ISHTP device poपूर्णांकer
 * @offset: Register offset
 *
 * Read 32 bit रेजिस्टर at a given offset
 *
 * Return: Read रेजिस्टर value
 */
अटल अंतरभूत uपूर्णांक32_t ish_reg_पढ़ो(स्थिर काष्ठा ishtp_device *dev,
	अचिन्हित दीर्घ offset)
अणु
	काष्ठा ish_hw *hw = to_ish_hw(dev);

	वापस पढ़ोl(hw->mem_addr + offset);
पूर्ण

/**
 * ish_reg_ग_लिखो() - Write रेजिस्टर
 * @dev: ISHTP device poपूर्णांकer
 * @offset: Register offset
 * @value: Value to ग_लिखो
 *
 * Writes 32 bit रेजिस्टर at a give offset
 */
अटल अंतरभूत व्योम ish_reg_ग_लिखो(काष्ठा ishtp_device *dev,
				 अचिन्हित दीर्घ offset,
				 uपूर्णांक32_t value)
अणु
	काष्ठा ish_hw *hw = to_ish_hw(dev);

	ग_लिखोl(value, hw->mem_addr + offset);
पूर्ण

/**
 * _ish_पढ़ो_fw_sts_reg() - Read FW status रेजिस्टर
 * @dev: ISHTP device poपूर्णांकer
 *
 * Read FW status रेजिस्टर
 *
 * Return: Read रेजिस्टर value
 */
अटल अंतरभूत uपूर्णांक32_t _ish_पढ़ो_fw_sts_reg(काष्ठा ishtp_device *dev)
अणु
	वापस ish_reg_पढ़ो(dev, IPC_REG_ISH_HOST_FWSTS);
पूर्ण

/**
 * check_generated_पूर्णांकerrupt() - Check अगर ISH पूर्णांकerrupt
 * @dev: ISHTP device poपूर्णांकer
 *
 * Check अगर an पूर्णांकerrupt was generated क्रम ISH
 *
 * Return: Read true or false
 */
अटल bool check_generated_पूर्णांकerrupt(काष्ठा ishtp_device *dev)
अणु
	bool पूर्णांकerrupt_generated = true;
	uपूर्णांक32_t pisr_val = 0;

	अगर (dev->pdev->device == CHV_DEVICE_ID) अणु
		pisr_val = ish_reg_पढ़ो(dev, IPC_REG_PISR_CHV_AB);
		पूर्णांकerrupt_generated =
			IPC_INT_FROM_ISH_TO_HOST_CHV_AB(pisr_val);
	पूर्ण अन्यथा अणु
		pisr_val = ish_reg_पढ़ो(dev, IPC_REG_PISR_BXT);
		पूर्णांकerrupt_generated = !!pisr_val;
		/* only busy-clear bit is RW, others are RO */
		अगर (pisr_val)
			ish_reg_ग_लिखो(dev, IPC_REG_PISR_BXT, pisr_val);
	पूर्ण

	वापस पूर्णांकerrupt_generated;
पूर्ण

/**
 * ish_is_input_पढ़ोy() - Check अगर FW पढ़ोy क्रम RX
 * @dev: ISHTP device poपूर्णांकer
 *
 * Check अगर ISH FW is पढ़ोy क्रम receiving data
 *
 * Return: Read true or false
 */
अटल bool ish_is_input_पढ़ोy(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t करोorbell_val;

	करोorbell_val = ish_reg_पढ़ो(dev, IPC_REG_HOST2ISH_DRBL);
	वापस !IPC_IS_BUSY(करोorbell_val);
पूर्ण

/**
 * set_host_पढ़ोy() - Indicate host पढ़ोy
 * @dev: ISHTP device poपूर्णांकer
 *
 * Set host पढ़ोy indication to FW
 */
अटल व्योम set_host_पढ़ोy(काष्ठा ishtp_device *dev)
अणु
	अगर (dev->pdev->device == CHV_DEVICE_ID) अणु
		अगर (dev->pdev->revision == REVISION_ID_CHT_A0 ||
				(dev->pdev->revision & REVISION_ID_SI_MASK) ==
				REVISION_ID_CHT_Ax_SI)
			ish_reg_ग_लिखो(dev, IPC_REG_HOST_COMM, 0x81);
		अन्यथा अगर (dev->pdev->revision == REVISION_ID_CHT_B0 ||
				(dev->pdev->revision & REVISION_ID_SI_MASK) ==
				REVISION_ID_CHT_Bx_SI ||
				(dev->pdev->revision & REVISION_ID_SI_MASK) ==
				REVISION_ID_CHT_Kx_SI ||
				(dev->pdev->revision & REVISION_ID_SI_MASK) ==
				REVISION_ID_CHT_Dx_SI) अणु
			uपूर्णांक32_t host_comm_val;

			host_comm_val = ish_reg_पढ़ो(dev, IPC_REG_HOST_COMM);
			host_comm_val |= IPC_HOSTCOMM_INT_EN_BIT_CHV_AB | 0x81;
			ish_reg_ग_लिखो(dev, IPC_REG_HOST_COMM, host_comm_val);
		पूर्ण
	पूर्ण अन्यथा अणु
			uपूर्णांक32_t host_pimr_val;

			host_pimr_val = ish_reg_पढ़ो(dev, IPC_REG_PIMR_BXT);
			host_pimr_val |= IPC_PIMR_INT_EN_BIT_BXT;
			/*
			 * disable पूर्णांकerrupt generated instead of
			 * RX_complete_msg
			 */
			host_pimr_val &= ~IPC_HOST2ISH_BUSYCLEAR_MASK_BIT;

			ish_reg_ग_लिखो(dev, IPC_REG_PIMR_BXT, host_pimr_val);
	पूर्ण
पूर्ण

/**
 * ishtp_fw_is_पढ़ोy() - Check अगर FW पढ़ोy
 * @dev: ISHTP device poपूर्णांकer
 *
 * Check अगर ISH FW is पढ़ोy
 *
 * Return: Read true or false
 */
अटल bool ishtp_fw_is_पढ़ोy(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t ish_status = _ish_पढ़ो_fw_sts_reg(dev);

	वापस IPC_IS_ISH_ILUP(ish_status) &&
		IPC_IS_ISH_ISHTP_READY(ish_status);
पूर्ण

/**
 * ish_set_host_rdy() - Indicate host पढ़ोy
 * @dev: ISHTP device poपूर्णांकer
 *
 * Set host पढ़ोy indication to FW
 */
अटल व्योम ish_set_host_rdy(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t host_status = ish_reg_पढ़ो(dev, IPC_REG_HOST_COMM);

	IPC_SET_HOST_READY(host_status);
	ish_reg_ग_लिखो(dev, IPC_REG_HOST_COMM, host_status);
पूर्ण

/**
 * ish_clr_host_rdy() - Indicate host not पढ़ोy
 * @dev: ISHTP device poपूर्णांकer
 *
 * Send host not पढ़ोy indication to FW
 */
अटल व्योम ish_clr_host_rdy(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t host_status = ish_reg_पढ़ो(dev, IPC_REG_HOST_COMM);

	IPC_CLEAR_HOST_READY(host_status);
	ish_reg_ग_लिखो(dev, IPC_REG_HOST_COMM, host_status);
पूर्ण

अटल bool ish_chk_host_rdy(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t host_status = ish_reg_पढ़ो(dev, IPC_REG_HOST_COMM);

	वापस (host_status & IPC_HOSTCOMM_READY_BIT);
पूर्ण

/**
 * ish_set_host_पढ़ोy() - reconfig ipc host रेजिस्टरs
 * @dev: ishtp device poपूर्णांकer
 *
 * Set host to पढ़ोy state
 * This API is called in some हाल:
 *    fw is still on, but ipc is घातered करोwn.
 *    such as OOB हाल.
 *
 * Return: 0 क्रम success अन्यथा error fault code
 */
व्योम ish_set_host_पढ़ोy(काष्ठा ishtp_device *dev)
अणु
	अगर (ish_chk_host_rdy(dev))
		वापस;

	ish_set_host_rdy(dev);
	set_host_पढ़ोy(dev);
पूर्ण

/**
 * _ishtp_पढ़ो_hdr() - Read message header
 * @dev: ISHTP device poपूर्णांकer
 *
 * Read header of 32bit length
 *
 * Return: Read रेजिस्टर value
 */
अटल uपूर्णांक32_t _ishtp_पढ़ो_hdr(स्थिर काष्ठा ishtp_device *dev)
अणु
	वापस ish_reg_पढ़ो(dev, IPC_REG_ISH2HOST_MSG);
पूर्ण

/**
 * _ishtp_पढ़ो - Read message
 * @dev: ISHTP device poपूर्णांकer
 * @buffer: message buffer
 * @buffer_length: length of message buffer
 *
 * Read message from FW
 *
 * Return: Always 0
 */
अटल पूर्णांक _ishtp_पढ़ो(काष्ठा ishtp_device *dev, अचिन्हित अक्षर *buffer,
	अचिन्हित दीर्घ buffer_length)
अणु
	uपूर्णांक32_t	i;
	uपूर्णांक32_t	*r_buf = (uपूर्णांक32_t *)buffer;
	uपूर्णांक32_t	msg_offs;

	msg_offs = IPC_REG_ISH2HOST_MSG + माप(काष्ठा ishtp_msg_hdr);
	क्रम (i = 0; i < buffer_length; i += माप(uपूर्णांक32_t))
		*r_buf++ = ish_reg_पढ़ो(dev, msg_offs + i);

	वापस 0;
पूर्ण

/**
 * ग_लिखो_ipc_from_queue() - try to ग_लिखो ipc msg from Tx queue to device
 * @dev: ishtp device poपूर्णांकer
 *
 * Check अगर DRBL is cleared. अगर it is - ग_लिखो the first IPC msg,  then call
 * the callback function (unless it's शून्य)
 *
 * Return: 0 क्रम success अन्यथा failure code
 */
अटल पूर्णांक ग_लिखो_ipc_from_queue(काष्ठा ishtp_device *dev)
अणु
	काष्ठा wr_msg_ctl_info	*ipc_link;
	अचिन्हित दीर्घ	length;
	अचिन्हित दीर्घ	rem;
	अचिन्हित दीर्घ	flags;
	uपूर्णांक32_t	करोorbell_val;
	uपूर्णांक32_t	*r_buf;
	uपूर्णांक32_t	reg_addr;
	पूर्णांक	i;
	व्योम	(*ipc_send_compl)(व्योम *);
	व्योम	*ipc_send_compl_prm;

	अगर (dev->dev_state == ISHTP_DEV_DISABLED)
		वापस -EINVAL;

	spin_lock_irqsave(&dev->wr_processing_spinlock, flags);
	अगर (!ish_is_input_पढ़ोy(dev)) अणु
		spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);
		वापस -EBUSY;
	पूर्ण

	/*
	 * अगर tx send list is empty - वापस 0;
	 * may happen, as RX_COMPLETE handler करोesn't check list emptiness.
	 */
	अगर (list_empty(&dev->wr_processing_list)) अणु
		spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);
		वापस	0;
	पूर्ण

	ipc_link = list_first_entry(&dev->wr_processing_list,
				    काष्ठा wr_msg_ctl_info, link);
	/* first 4 bytes of the data is the करोorbell value (IPC header) */
	length = ipc_link->length - माप(uपूर्णांक32_t);
	करोorbell_val = *(uपूर्णांक32_t *)ipc_link->अंतरभूत_data;
	r_buf = (uपूर्णांक32_t *)(ipc_link->अंतरभूत_data + माप(uपूर्णांक32_t));

	/* If sending MNG_SYNC_FW_CLOCK, update घड़ी again */
	अगर (IPC_HEADER_GET_PROTOCOL(करोorbell_val) == IPC_PROTOCOL_MNG &&
		IPC_HEADER_GET_MNG_CMD(करोorbell_val) == MNG_SYNC_FW_CLOCK) अणु
		uपूर्णांक64_t usec_प्रणाली, usec_utc;
		काष्ठा ipc_समय_update_msg समय_update;
		काष्ठा समय_sync_क्रमmat ts_क्रमmat;

		usec_प्रणाली = kसमय_प्रकारo_us(kसमय_get_bootसमय());
		usec_utc = kसमय_प्रकारo_us(kसमय_get_real());
		ts_क्रमmat.ts1_source = HOST_SYSTEM_TIME_USEC;
		ts_क्रमmat.ts2_source = HOST_UTC_TIME_USEC;
		ts_क्रमmat.reserved = 0;

		समय_update.primary_host_समय = usec_प्रणाली;
		समय_update.secondary_host_समय = usec_utc;
		समय_update.sync_info = ts_क्रमmat;

		स_नकल(r_buf, &समय_update,
		       माप(काष्ठा ipc_समय_update_msg));
	पूर्ण

	क्रम (i = 0, reg_addr = IPC_REG_HOST2ISH_MSG; i < length >> 2; i++,
			reg_addr += 4)
		ish_reg_ग_लिखो(dev, reg_addr, r_buf[i]);

	rem = length & 0x3;
	अगर (rem > 0) अणु
		uपूर्णांक32_t reg = 0;

		स_नकल(&reg, &r_buf[length >> 2], rem);
		ish_reg_ग_लिखो(dev, reg_addr, reg);
	पूर्ण
	ish_reg_ग_लिखो(dev, IPC_REG_HOST2ISH_DRBL, करोorbell_val);

	/* Flush ग_लिखोs to msg रेजिस्टरs and करोorbell */
	ish_reg_पढ़ो(dev, IPC_REG_ISH_HOST_FWSTS);

	/* Update IPC counters */
	++dev->ipc_tx_cnt;
	dev->ipc_tx_bytes_cnt += IPC_HEADER_GET_LENGTH(करोorbell_val);

	ipc_send_compl = ipc_link->ipc_send_compl;
	ipc_send_compl_prm = ipc_link->ipc_send_compl_prm;
	list_del_init(&ipc_link->link);
	list_add(&ipc_link->link, &dev->wr_मुक्त_list);
	spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);

	/*
	 * callback will be called out of spinlock,
	 * after ipc_link वापसed to मुक्त list
	 */
	अगर (ipc_send_compl)
		ipc_send_compl(ipc_send_compl_prm);

	वापस 0;
पूर्ण

/**
 * ग_लिखो_ipc_to_queue() - ग_लिखो ipc msg to Tx queue
 * @dev: ishtp device instance
 * @ipc_send_compl: Send complete callback
 * @ipc_send_compl_prm:	Parameter to send in complete callback
 * @msg: Poपूर्णांकer to message
 * @length: Length of message
 *
 * Recived msg with IPC (and upper protocol) header  and add it to the device
 *  Tx-to-ग_लिखो list then try to send the first IPC रुकोing msg
 *  (अगर DRBL is cleared)
 * This function वापसs negative value क्रम failure (means मुक्त list
 *  is empty, or msg too दीर्घ) and 0 क्रम success.
 *
 * Return: 0 क्रम success अन्यथा failure code
 */
अटल पूर्णांक ग_लिखो_ipc_to_queue(काष्ठा ishtp_device *dev,
	व्योम (*ipc_send_compl)(व्योम *), व्योम *ipc_send_compl_prm,
	अचिन्हित अक्षर *msg, पूर्णांक length)
अणु
	काष्ठा wr_msg_ctl_info *ipc_link;
	अचिन्हित दीर्घ flags;

	अगर (length > IPC_FULL_MSG_SIZE)
		वापस -EMSGSIZE;

	spin_lock_irqsave(&dev->wr_processing_spinlock, flags);
	अगर (list_empty(&dev->wr_मुक्त_list)) अणु
		spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);
		वापस -ENOMEM;
	पूर्ण
	ipc_link = list_first_entry(&dev->wr_मुक्त_list,
				    काष्ठा wr_msg_ctl_info, link);
	list_del_init(&ipc_link->link);

	ipc_link->ipc_send_compl = ipc_send_compl;
	ipc_link->ipc_send_compl_prm = ipc_send_compl_prm;
	ipc_link->length = length;
	स_नकल(ipc_link->अंतरभूत_data, msg, length);

	list_add_tail(&ipc_link->link, &dev->wr_processing_list);
	spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);

	ग_लिखो_ipc_from_queue(dev);

	वापस 0;
पूर्ण

/**
 * ipc_send_mng_msg() - Send management message
 * @dev: ishtp device instance
 * @msg_code: Message code
 * @msg: Poपूर्णांकer to message
 * @size: Length of message
 *
 * Send management message to FW
 *
 * Return: 0 क्रम success अन्यथा failure code
 */
अटल पूर्णांक ipc_send_mng_msg(काष्ठा ishtp_device *dev, uपूर्णांक32_t msg_code,
	व्योम *msg, माप_प्रकार size)
अणु
	अचिन्हित अक्षर	ipc_msg[IPC_FULL_MSG_SIZE];
	uपूर्णांक32_t	drbl_val = IPC_BUILD_MNG_MSG(msg_code, size);

	स_नकल(ipc_msg, &drbl_val, माप(uपूर्णांक32_t));
	स_नकल(ipc_msg + माप(uपूर्णांक32_t), msg, size);
	वापस	ग_लिखो_ipc_to_queue(dev, शून्य, शून्य, ipc_msg,
		माप(uपूर्णांक32_t) + size);
पूर्ण

#घोषणा WAIT_FOR_FW_RDY			0x1
#घोषणा WAIT_FOR_INPUT_RDY		0x2

/**
 * समयd_रुको_क्रम_समयout() - रुको special event with समयout
 * @dev: ISHTP device poपूर्णांकer
 * @condition: indicate the condition क्रम रुकोing
 * @समयinc: समय slice क्रम every रुको cycle, in ms
 * @समयout: समय in ms क्रम समयout
 *
 * This function will check special event to be पढ़ोy in a loop, the loop
 * period is specअगरicd in समयinc. Wait समयout will causes failure.
 *
 * Return: 0 क्रम success अन्यथा failure code
 */
अटल पूर्णांक समयd_रुको_क्रम_समयout(काष्ठा ishtp_device *dev, पूर्णांक condition,
				अचिन्हित पूर्णांक समयinc, अचिन्हित पूर्णांक समयout)
अणु
	bool complete = false;
	पूर्णांक ret;

	करो अणु
		अगर (condition == WAIT_FOR_FW_RDY) अणु
			complete = ishtp_fw_is_पढ़ोy(dev);
		पूर्ण अन्यथा अगर (condition == WAIT_FOR_INPUT_RDY) अणु
			complete = ish_is_input_पढ़ोy(dev);
		पूर्ण अन्यथा अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!complete) अणु
			अचिन्हित दीर्घ left_समय;

			left_समय = msleep_पूर्णांकerruptible(समयinc);
			समयout -= (समयinc - left_समय);
		पूर्ण
	पूर्ण जबतक (!complete && समयout > 0);

	अगर (complete)
		ret = 0;
	अन्यथा
		ret = -EBUSY;

out:
	वापस ret;
पूर्ण

#घोषणा TIME_SLICE_FOR_FW_RDY_MS		100
#घोषणा TIME_SLICE_FOR_INPUT_RDY_MS		100
#घोषणा TIMEOUT_FOR_FW_RDY_MS			2000
#घोषणा TIMEOUT_FOR_INPUT_RDY_MS		2000

/**
 * ish_fw_reset_handler() - FW reset handler
 * @dev: ishtp device poपूर्णांकer
 *
 * Handle FW reset
 *
 * Return: 0 क्रम success अन्यथा failure code
 */
अटल पूर्णांक ish_fw_reset_handler(काष्ठा ishtp_device *dev)
अणु
	uपूर्णांक32_t	reset_id;
	अचिन्हित दीर्घ	flags;

	/* Read reset ID */
	reset_id = ish_reg_पढ़ो(dev, IPC_REG_ISH2HOST_MSG) & 0xFFFF;

	/* Clear IPC output queue */
	spin_lock_irqsave(&dev->wr_processing_spinlock, flags);
	list_splice_init(&dev->wr_processing_list, &dev->wr_मुक्त_list);
	spin_unlock_irqrestore(&dev->wr_processing_spinlock, flags);

	/* ISHTP notअगरication in IPC_RESET */
	ishtp_reset_handler(dev);

	अगर (!ish_is_input_पढ़ोy(dev))
		समयd_रुको_क्रम_समयout(dev, WAIT_FOR_INPUT_RDY,
			TIME_SLICE_FOR_INPUT_RDY_MS, TIMEOUT_FOR_INPUT_RDY_MS);

	/* ISH FW is dead */
	अगर (!ish_is_input_पढ़ोy(dev))
		वापस	-EPIPE;
	/*
	 * Set HOST2ISH.ILUP. Apparently we need this BEFORE sending
	 * RESET_NOTIFY_ACK - FW will be checking क्रम it
	 */
	ish_set_host_rdy(dev);
	/* Send RESET_NOTIFY_ACK (with reset_id) */
	ipc_send_mng_msg(dev, MNG_RESET_NOTIFY_ACK, &reset_id,
			 माप(uपूर्णांक32_t));

	/* Wait क्रम ISH FW'es ILUP and ISHTP_READY */
	समयd_रुको_क्रम_समयout(dev, WAIT_FOR_FW_RDY,
			TIME_SLICE_FOR_FW_RDY_MS, TIMEOUT_FOR_FW_RDY_MS);
	अगर (!ishtp_fw_is_पढ़ोy(dev)) अणु
		/* ISH FW is dead */
		uपूर्णांक32_t	ish_status;

		ish_status = _ish_पढ़ो_fw_sts_reg(dev);
		dev_err(dev->devc,
			"[ishtp-ish]: completed reset, ISH is dead (FWSTS = %08X)\n",
			ish_status);
		वापस -ENODEV;
	पूर्ण
	वापस	0;
पूर्ण

#घोषणा TIMEOUT_FOR_HW_RDY_MS			300

/**
 * ish_fw_reset_work_fn() - FW reset worker function
 * @unused: not used
 *
 * Call ish_fw_reset_handler to complete FW reset
 */
अटल व्योम fw_reset_work_fn(काष्ठा work_काष्ठा *unused)
अणु
	पूर्णांक	rv;

	rv = ish_fw_reset_handler(ishtp_dev);
	अगर (!rv) अणु
		/* ISH is ILUP & ISHTP-पढ़ोy. Restart ISHTP */
		msleep_पूर्णांकerruptible(TIMEOUT_FOR_HW_RDY_MS);
		ishtp_dev->recvd_hw_पढ़ोy = 1;
		wake_up_पूर्णांकerruptible(&ishtp_dev->रुको_hw_पढ़ोy);

		/* ISHTP notअगरication in IPC_RESET sequence completion */
		ishtp_reset_compl_handler(ishtp_dev);
	पूर्ण अन्यथा
		dev_err(ishtp_dev->devc, "[ishtp-ish]: FW reset failed (%d)\n",
			rv);
पूर्ण

/**
 * _ish_sync_fw_घड़ी() -Sync FW घड़ी with the OS घड़ी
 * @dev: ishtp device poपूर्णांकer
 *
 * Sync FW and OS समय
 */
अटल व्योम _ish_sync_fw_घड़ी(काष्ठा ishtp_device *dev)
अणु
	अटल अचिन्हित दीर्घ	prev_sync;
	uपूर्णांक64_t	usec;

	अगर (prev_sync && jअगरfies - prev_sync < 20 * HZ)
		वापस;

	prev_sync = jअगरfies;
	usec = kसमय_प्रकारo_us(kसमय_get_bootसमय());
	ipc_send_mng_msg(dev, MNG_SYNC_FW_CLOCK, &usec, माप(uपूर्णांक64_t));
पूर्ण

/**
 * recv_ipc() - Receive and process IPC management messages
 * @dev: ishtp device instance
 * @करोorbell_val: करोorbell value
 *
 * This function runs in ISR context.
 * NOTE: Any other mng command than reset_notअगरy and reset_notअगरy_ack
 * won't wake BH handler
 */
अटल व्योम	recv_ipc(काष्ठा ishtp_device *dev, uपूर्णांक32_t करोorbell_val)
अणु
	uपूर्णांक32_t	mng_cmd;

	mng_cmd = IPC_HEADER_GET_MNG_CMD(करोorbell_val);

	चयन (mng_cmd) अणु
	शेष:
		अवरोध;

	हाल MNG_RX_CMPL_INDICATION:
		अगर (dev->suspend_flag) अणु
			dev->suspend_flag = 0;
			wake_up_पूर्णांकerruptible(&dev->suspend_रुको);
		पूर्ण
		अगर (dev->resume_flag) अणु
			dev->resume_flag = 0;
			wake_up_पूर्णांकerruptible(&dev->resume_रुको);
		पूर्ण

		ग_लिखो_ipc_from_queue(dev);
		अवरोध;

	हाल MNG_RESET_NOTIFY:
		अगर (!ishtp_dev) अणु
			ishtp_dev = dev;
			INIT_WORK(&fw_reset_work, fw_reset_work_fn);
		पूर्ण
		schedule_work(&fw_reset_work);
		अवरोध;

	हाल MNG_RESET_NOTIFY_ACK:
		dev->recvd_hw_पढ़ोy = 1;
		wake_up_पूर्णांकerruptible(&dev->रुको_hw_पढ़ोy);
		अवरोध;
	पूर्ण
पूर्ण

/**
 * ish_irq_handler() - ISH IRQ handler
 * @irq: irq number
 * @dev_id: ishtp device poपूर्णांकer
 *
 * ISH IRQ handler. If पूर्णांकerrupt is generated and is क्रम ISH it will process
 * the पूर्णांकerrupt.
 */
irqवापस_t ish_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ishtp_device	*dev = dev_id;
	uपूर्णांक32_t	करोorbell_val;
	bool	पूर्णांकerrupt_generated;

	/* Check that it's पूर्णांकerrupt from ISH (may be shared) */
	पूर्णांकerrupt_generated = check_generated_पूर्णांकerrupt(dev);

	अगर (!पूर्णांकerrupt_generated)
		वापस IRQ_NONE;

	करोorbell_val = ish_reg_पढ़ो(dev, IPC_REG_ISH2HOST_DRBL);
	अगर (!IPC_IS_BUSY(करोorbell_val))
		वापस IRQ_HANDLED;

	अगर (dev->dev_state == ISHTP_DEV_DISABLED)
		वापस	IRQ_HANDLED;

	/* Sanity check: IPC dgram length in header */
	अगर (IPC_HEADER_GET_LENGTH(करोorbell_val) > IPC_PAYLOAD_SIZE) अणु
		dev_err(dev->devc,
			"IPC hdr - bad length: %u; dropped\n",
			(अचिन्हित पूर्णांक)IPC_HEADER_GET_LENGTH(करोorbell_val));
		जाओ	eoi;
	पूर्ण

	चयन (IPC_HEADER_GET_PROTOCOL(करोorbell_val)) अणु
	शेष:
		अवरोध;
	हाल IPC_PROTOCOL_MNG:
		recv_ipc(dev, करोorbell_val);
		अवरोध;
	हाल IPC_PROTOCOL_ISHTP:
		ishtp_recv(dev);
		अवरोध;
	पूर्ण

eoi:
	/* Update IPC counters */
	++dev->ipc_rx_cnt;
	dev->ipc_rx_bytes_cnt += IPC_HEADER_GET_LENGTH(करोorbell_val);

	ish_reg_ग_लिखो(dev, IPC_REG_ISH2HOST_DRBL, 0);
	/* Flush ग_लिखो to करोorbell */
	ish_reg_पढ़ो(dev, IPC_REG_ISH_HOST_FWSTS);

	वापस	IRQ_HANDLED;
पूर्ण

/**
 * ish_disable_dma() - disable dma communication between host and ISHFW
 * @dev: ishtp device poपूर्णांकer
 *
 * Clear the dma enable bit and रुको क्रम dma inactive.
 *
 * Return: 0 क्रम success अन्यथा error code.
 */
पूर्णांक ish_disable_dma(काष्ठा ishtp_device *dev)
अणु
	अचिन्हित पूर्णांक	dma_delay;

	/* Clear the dma enable bit */
	ish_reg_ग_लिखो(dev, IPC_REG_ISH_RMP2, 0);

	/* रुको क्रम dma inactive */
	क्रम (dma_delay = 0; dma_delay < MAX_DMA_DELAY &&
		_ish_पढ़ो_fw_sts_reg(dev) & (IPC_ISH_IN_DMA);
		dma_delay += 5)
		mdelay(5);

	अगर (dma_delay >= MAX_DMA_DELAY) अणु
		dev_err(dev->devc,
			"Wait for DMA inactive timeout\n");
		वापस	-EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ish_wakeup() - wakeup ishfw from रुकोing-क्रम-host state
 * @dev: ishtp device poपूर्णांकer
 *
 * Set the dma enable bit and send a व्योम message to FW,
 * it wil wakeup FW from रुकोing-क्रम-host state.
 */
अटल व्योम ish_wakeup(काष्ठा ishtp_device *dev)
अणु
	/* Set dma enable bit */
	ish_reg_ग_लिखो(dev, IPC_REG_ISH_RMP2, IPC_RMP2_DMA_ENABLED);

	/*
	 * Send 0 IPC message so that ISH FW wakes up अगर it was alपढ़ोy
	 * asleep.
	 */
	ish_reg_ग_लिखो(dev, IPC_REG_HOST2ISH_DRBL, IPC_DRBL_BUSY_BIT);

	/* Flush ग_लिखोs to करोorbell and REMAP2 */
	ish_reg_पढ़ो(dev, IPC_REG_ISH_HOST_FWSTS);
पूर्ण

/**
 * _ish_hw_reset() - HW reset
 * @dev: ishtp device poपूर्णांकer
 *
 * Reset ISH HW to recover अगर any error
 *
 * Return: 0 क्रम success अन्यथा error fault code
 */
अटल पूर्णांक _ish_hw_reset(काष्ठा ishtp_device *dev)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक	rv;
	uपूर्णांक16_t csr;

	अगर (!pdev)
		वापस	-ENODEV;

	rv = pci_reset_function(pdev);
	अगर (!rv)
		dev->dev_state = ISHTP_DEV_RESETTING;

	अगर (!pdev->pm_cap) अणु
		dev_err(&pdev->dev, "Can't reset - no PM caps\n");
		वापस	-EINVAL;
	पूर्ण

	/* Disable dma communication between FW and host */
	अगर (ish_disable_dma(dev)) अणु
		dev_err(&pdev->dev,
			"Can't reset - stuck with DMA in-progress\n");
		वापस	-EBUSY;
	पूर्ण

	pci_पढ़ो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, &csr);

	csr &= ~PCI_PM_CTRL_STATE_MASK;
	csr |= PCI_D3hot;
	pci_ग_लिखो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, csr);

	mdelay(pdev->d3hot_delay);

	csr &= ~PCI_PM_CTRL_STATE_MASK;
	csr |= PCI_D0;
	pci_ग_लिखो_config_word(pdev, pdev->pm_cap + PCI_PM_CTRL, csr);

	/* Now we can enable ISH DMA operation and wakeup ISHFW */
	ish_wakeup(dev);

	वापस	0;
पूर्ण

/**
 * _ish_ipc_reset() - IPC reset
 * @dev: ishtp device poपूर्णांकer
 *
 * Resets host and fw IPC and upper layers
 *
 * Return: 0 क्रम success अन्यथा error fault code
 */
अटल पूर्णांक _ish_ipc_reset(काष्ठा ishtp_device *dev)
अणु
	काष्ठा ipc_rst_payload_type ipc_mng_msg;
	पूर्णांक	rv = 0;

	ipc_mng_msg.reset_id = 1;
	ipc_mng_msg.reserved = 0;

	set_host_पढ़ोy(dev);

	/* Clear the incoming करोorbell */
	ish_reg_ग_लिखो(dev, IPC_REG_ISH2HOST_DRBL, 0);
	/* Flush ग_लिखो to करोorbell */
	ish_reg_पढ़ो(dev, IPC_REG_ISH_HOST_FWSTS);

	dev->recvd_hw_पढ़ोy = 0;

	/* send message */
	rv = ipc_send_mng_msg(dev, MNG_RESET_NOTIFY, &ipc_mng_msg,
		माप(काष्ठा ipc_rst_payload_type));
	अगर (rv) अणु
		dev_err(dev->devc, "Failed to send IPC MNG_RESET_NOTIFY\n");
		वापस	rv;
	पूर्ण

	रुको_event_पूर्णांकerruptible_समयout(dev->रुको_hw_पढ़ोy,
					 dev->recvd_hw_पढ़ोy, 2 * HZ);
	अगर (!dev->recvd_hw_पढ़ोy) अणु
		dev_err(dev->devc, "Timed out waiting for HW ready\n");
		rv = -ENODEV;
	पूर्ण

	वापस rv;
पूर्ण

/**
 * ish_hw_start() -Start ISH HW
 * @dev: ishtp device poपूर्णांकer
 *
 * Set host to पढ़ोy state and रुको क्रम FW reset
 *
 * Return: 0 क्रम success अन्यथा error fault code
 */
पूर्णांक ish_hw_start(काष्ठा ishtp_device *dev)
अणु
	ish_set_host_rdy(dev);

	set_host_पढ़ोy(dev);

	/* After that we can enable ISH DMA operation and wakeup ISHFW */
	ish_wakeup(dev);

	/* रुको क्रम FW-initiated reset flow */
	अगर (!dev->recvd_hw_पढ़ोy)
		रुको_event_पूर्णांकerruptible_समयout(dev->रुको_hw_पढ़ोy,
						 dev->recvd_hw_पढ़ोy,
						 10 * HZ);

	अगर (!dev->recvd_hw_पढ़ोy) अणु
		dev_err(dev->devc,
			"[ishtp-ish]: Timed out waiting for FW-initiated reset\n");
		वापस	-ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ish_ipc_get_header() -Get करोorbell value
 * @dev: ishtp device poपूर्णांकer
 * @length: length of message
 * @busy: busy status
 *
 * Get करोor bell value from message header
 *
 * Return: करोor bell value
 */
अटल uपूर्णांक32_t ish_ipc_get_header(काष्ठा ishtp_device *dev, पूर्णांक length,
				   पूर्णांक busy)
अणु
	uपूर्णांक32_t drbl_val;

	drbl_val = IPC_BUILD_HEADER(length, IPC_PROTOCOL_ISHTP, busy);

	वापस drbl_val;
पूर्ण

अटल स्थिर काष्ठा ishtp_hw_ops ish_hw_ops = अणु
	.hw_reset = _ish_hw_reset,
	.ipc_reset = _ish_ipc_reset,
	.ipc_get_header = ish_ipc_get_header,
	.ishtp_पढ़ो = _ishtp_पढ़ो,
	.ग_लिखो = ग_लिखो_ipc_to_queue,
	.get_fw_status = _ish_पढ़ो_fw_sts_reg,
	.sync_fw_घड़ी = _ish_sync_fw_घड़ी,
	.ishtp_पढ़ो_hdr = _ishtp_पढ़ो_hdr
पूर्ण;

/**
 * ish_dev_init() -Initialize ISH devoce
 * @pdev: PCI device
 *
 * Allocate ISHTP device and initialize IPC processing
 *
 * Return: ISHTP device instance on success अन्यथा शून्य
 */
काष्ठा ishtp_device *ish_dev_init(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ishtp_device *dev;
	पूर्णांक	i;

	dev = devm_kzalloc(&pdev->dev,
			   माप(काष्ठा ishtp_device) + माप(काष्ठा ish_hw),
			   GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	ishtp_device_init(dev);

	init_रुकोqueue_head(&dev->रुको_hw_पढ़ोy);

	spin_lock_init(&dev->wr_processing_spinlock);

	/* Init IPC processing and मुक्त lists */
	INIT_LIST_HEAD(&dev->wr_processing_list);
	INIT_LIST_HEAD(&dev->wr_मुक्त_list);
	क्रम (i = 0; i < IPC_TX_FIFO_SIZE; i++) अणु
		काष्ठा wr_msg_ctl_info	*tx_buf;

		tx_buf = devm_kzalloc(&pdev->dev,
				      माप(काष्ठा wr_msg_ctl_info),
				      GFP_KERNEL);
		अगर (!tx_buf) अणु
			/*
			 * IPC buffers may be limited or not available
			 * at all - although this shouldn't happen
			 */
			dev_err(dev->devc,
				"[ishtp-ish]: failure in Tx FIFO allocations (%d)\n",
				i);
			अवरोध;
		पूर्ण
		list_add_tail(&tx_buf->link, &dev->wr_मुक्त_list);
	पूर्ण

	dev->ops = &ish_hw_ops;
	dev->devc = &pdev->dev;
	dev->mtu = IPC_PAYLOAD_SIZE - माप(काष्ठा ishtp_msg_hdr);
	वापस dev;
पूर्ण

/**
 * ish_device_disable() - Disable ISH device
 * @dev: ISHTP device poपूर्णांकer
 *
 * Disable ISH by clearing host पढ़ोy to inक्रमm firmware.
 */
व्योम	ish_device_disable(काष्ठा ishtp_device *dev)
अणु
	काष्ठा pci_dev *pdev = dev->pdev;

	अगर (!pdev)
		वापस;

	/* Disable dma communication between FW and host */
	अगर (ish_disable_dma(dev)) अणु
		dev_err(&pdev->dev,
			"Can't reset - stuck with DMA in-progress\n");
		वापस;
	पूर्ण

	/* Put ISH to D3hot state क्रम घातer saving */
	pci_set_घातer_state(pdev, PCI_D3hot);

	dev->dev_state = ISHTP_DEV_DISABLED;
	ish_clr_host_rdy(dev);
पूर्ण
