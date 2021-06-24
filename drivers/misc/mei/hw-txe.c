<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2013-2020, Intel Corporation. All rights reserved.
 * Intel Management Engine Interface (Intel MEI) Linux driver
 */

#समावेश <linux/pci.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/delay.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mei.h>

#समावेश "mei_dev.h"
#समावेश "hw-txe.h"
#समावेश "client.h"
#समावेश "hbm.h"

#समावेश "mei-trace.h"

#घोषणा TXE_HBUF_DEPTH (PAYLOAD_SIZE / MEI_SLOT_SIZE)

/**
 * mei_txe_reg_पढ़ो - Reads 32bit data from the txe device
 *
 * @base_addr: रेजिस्टरs base address
 * @offset: रेजिस्टर offset
 *
 * Return: रेजिस्टर value
 */
अटल अंतरभूत u32 mei_txe_reg_पढ़ो(व्योम __iomem *base_addr,
					अचिन्हित दीर्घ offset)
अणु
	वापस ioपढ़ो32(base_addr + offset);
पूर्ण

/**
 * mei_txe_reg_ग_लिखो - Writes 32bit data to the txe device
 *
 * @base_addr: रेजिस्टरs base address
 * @offset: रेजिस्टर offset
 * @value: the value to ग_लिखो
 */
अटल अंतरभूत व्योम mei_txe_reg_ग_लिखो(व्योम __iomem *base_addr,
				अचिन्हित दीर्घ offset, u32 value)
अणु
	ioग_लिखो32(value, base_addr + offset);
पूर्ण

/**
 * mei_txe_sec_reg_पढ़ो_silent - Reads 32bit data from the SeC BAR
 *
 * @hw: the txe hardware काष्ठाure
 * @offset: रेजिस्टर offset
 *
 * Doesn't check क्रम aliveness जबतक Reads 32bit data from the SeC BAR
 *
 * Return: रेजिस्टर value
 */
अटल अंतरभूत u32 mei_txe_sec_reg_पढ़ो_silent(काष्ठा mei_txe_hw *hw,
				अचिन्हित दीर्घ offset)
अणु
	वापस mei_txe_reg_पढ़ो(hw->mem_addr[SEC_BAR], offset);
पूर्ण

/**
 * mei_txe_sec_reg_पढ़ो - Reads 32bit data from the SeC BAR
 *
 * @hw: the txe hardware काष्ठाure
 * @offset: रेजिस्टर offset
 *
 * Reads 32bit data from the SeC BAR and shout loud अगर aliveness is not set
 *
 * Return: रेजिस्टर value
 */
अटल अंतरभूत u32 mei_txe_sec_reg_पढ़ो(काष्ठा mei_txe_hw *hw,
				अचिन्हित दीर्घ offset)
अणु
	WARN(!hw->aliveness, "sec read: aliveness not asserted\n");
	वापस mei_txe_sec_reg_पढ़ो_silent(hw, offset);
पूर्ण
/**
 * mei_txe_sec_reg_ग_लिखो_silent - Writes 32bit data to the SeC BAR
 *   करोesn't check क्रम aliveness
 *
 * @hw: the txe hardware काष्ठाure
 * @offset: रेजिस्टर offset
 * @value: value to ग_लिखो
 *
 * Doesn't check क्रम aliveness जबतक ग_लिखोs 32bit data from to the SeC BAR
 */
अटल अंतरभूत व्योम mei_txe_sec_reg_ग_लिखो_silent(काष्ठा mei_txe_hw *hw,
				अचिन्हित दीर्घ offset, u32 value)
अणु
	mei_txe_reg_ग_लिखो(hw->mem_addr[SEC_BAR], offset, value);
पूर्ण

/**
 * mei_txe_sec_reg_ग_लिखो - Writes 32bit data to the SeC BAR
 *
 * @hw: the txe hardware काष्ठाure
 * @offset: रेजिस्टर offset
 * @value: value to ग_लिखो
 *
 * Writes 32bit data from the SeC BAR and shout loud अगर aliveness is not set
 */
अटल अंतरभूत व्योम mei_txe_sec_reg_ग_लिखो(काष्ठा mei_txe_hw *hw,
				अचिन्हित दीर्घ offset, u32 value)
अणु
	WARN(!hw->aliveness, "sec write: aliveness not asserted\n");
	mei_txe_sec_reg_ग_लिखो_silent(hw, offset, value);
पूर्ण
/**
 * mei_txe_br_reg_पढ़ो - Reads 32bit data from the Bridge BAR
 *
 * @hw: the txe hardware काष्ठाure
 * @offset: offset from which to पढ़ो the data
 *
 * Return: the byte पढ़ो.
 */
अटल अंतरभूत u32 mei_txe_br_reg_पढ़ो(काष्ठा mei_txe_hw *hw,
				अचिन्हित दीर्घ offset)
अणु
	वापस mei_txe_reg_पढ़ो(hw->mem_addr[BRIDGE_BAR], offset);
पूर्ण

/**
 * mei_txe_br_reg_ग_लिखो - Writes 32bit data to the Bridge BAR
 *
 * @hw: the txe hardware काष्ठाure
 * @offset: offset from which to ग_लिखो the data
 * @value: the byte to ग_लिखो
 */
अटल अंतरभूत व्योम mei_txe_br_reg_ग_लिखो(काष्ठा mei_txe_hw *hw,
				अचिन्हित दीर्घ offset, u32 value)
अणु
	mei_txe_reg_ग_लिखो(hw->mem_addr[BRIDGE_BAR], offset, value);
पूर्ण

/**
 * mei_txe_aliveness_set - request क्रम aliveness change
 *
 * @dev: the device काष्ठाure
 * @req: requested aliveness value
 *
 * Request क्रम aliveness change and वापसs true अगर the change is
 *   really needed and false अगर aliveness is alपढ़ोy
 *   in the requested state
 *
 * Locking: called under "dev->device_lock" lock
 *
 * Return: true अगर request was send
 */
अटल bool mei_txe_aliveness_set(काष्ठा mei_device *dev, u32 req)
अणु

	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	bool करो_req = hw->aliveness != req;

	dev_dbg(dev->dev, "Aliveness current=%d request=%d\n",
				hw->aliveness, req);
	अगर (करो_req) अणु
		dev->pg_event = MEI_PG_EVENT_WAIT;
		mei_txe_br_reg_ग_लिखो(hw, SICR_HOST_ALIVENESS_REQ_REG, req);
	पूर्ण
	वापस करो_req;
पूर्ण


/**
 * mei_txe_aliveness_req_get - get aliveness requested रेजिस्टर value
 *
 * @dev: the device काष्ठाure
 *
 * Extract HICR_HOST_ALIVENESS_RESP_ACK bit from
 * from HICR_HOST_ALIVENESS_REQ रेजिस्टर value
 *
 * Return: SICR_HOST_ALIVENESS_REQ_REQUESTED bit value
 */
अटल u32 mei_txe_aliveness_req_get(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 reg;

	reg = mei_txe_br_reg_पढ़ो(hw, SICR_HOST_ALIVENESS_REQ_REG);
	वापस reg & SICR_HOST_ALIVENESS_REQ_REQUESTED;
पूर्ण

/**
 * mei_txe_aliveness_get - get aliveness response रेजिस्टर value
 *
 * @dev: the device काष्ठाure
 *
 * Return: HICR_HOST_ALIVENESS_RESP_ACK bit from HICR_HOST_ALIVENESS_RESP
 *         रेजिस्टर
 */
अटल u32 mei_txe_aliveness_get(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 reg;

	reg = mei_txe_br_reg_पढ़ो(hw, HICR_HOST_ALIVENESS_RESP_REG);
	वापस reg & HICR_HOST_ALIVENESS_RESP_ACK;
पूर्ण

/**
 * mei_txe_aliveness_poll - रुकोs क्रम aliveness to settle
 *
 * @dev: the device काष्ठाure
 * @expected: expected aliveness value
 *
 * Polls क्रम HICR_HOST_ALIVENESS_RESP.ALIVENESS_RESP to be set
 *
 * Return: 0 अगर the expected value was received, -ETIME otherwise
 */
अटल पूर्णांक mei_txe_aliveness_poll(काष्ठा mei_device *dev, u32 expected)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	kसमय_प्रकार stop, start;

	start = kसमय_get();
	stop = kसमय_add(start, ms_to_kसमय(SEC_ALIVENESS_WAIT_TIMEOUT));
	करो अणु
		hw->aliveness = mei_txe_aliveness_get(dev);
		अगर (hw->aliveness == expected) अणु
			dev->pg_event = MEI_PG_EVENT_IDLE;
			dev_dbg(dev->dev, "aliveness settled after %lld usecs\n",
				kसमय_प्रकारo_us(kसमय_sub(kसमय_get(), start)));
			वापस 0;
		पूर्ण
		usleep_range(20, 50);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), stop));

	dev->pg_event = MEI_PG_EVENT_IDLE;
	dev_err(dev->dev, "aliveness timed out\n");
	वापस -ETIME;
पूर्ण

/**
 * mei_txe_aliveness_रुको - रुकोs क्रम aliveness to settle
 *
 * @dev: the device काष्ठाure
 * @expected: expected aliveness value
 *
 * Waits क्रम HICR_HOST_ALIVENESS_RESP.ALIVENESS_RESP to be set
 *
 * Return: 0 on success and < 0 otherwise
 */
अटल पूर्णांक mei_txe_aliveness_रुको(काष्ठा mei_device *dev, u32 expected)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	स्थिर अचिन्हित दीर्घ समयout =
			msecs_to_jअगरfies(SEC_ALIVENESS_WAIT_TIMEOUT);
	दीर्घ err;
	पूर्णांक ret;

	hw->aliveness = mei_txe_aliveness_get(dev);
	अगर (hw->aliveness == expected)
		वापस 0;

	mutex_unlock(&dev->device_lock);
	err = रुको_event_समयout(hw->रुको_aliveness_resp,
			dev->pg_event == MEI_PG_EVENT_RECEIVED, समयout);
	mutex_lock(&dev->device_lock);

	hw->aliveness = mei_txe_aliveness_get(dev);
	ret = hw->aliveness == expected ? 0 : -ETIME;

	अगर (ret)
		dev_warn(dev->dev, "aliveness timed out = %ld aliveness = %d event = %d\n",
			err, hw->aliveness, dev->pg_event);
	अन्यथा
		dev_dbg(dev->dev, "aliveness settled after = %d msec aliveness = %d event = %d\n",
			jअगरfies_to_msecs(समयout - err),
			hw->aliveness, dev->pg_event);

	dev->pg_event = MEI_PG_EVENT_IDLE;
	वापस ret;
पूर्ण

/**
 * mei_txe_aliveness_set_sync - sets an रुको क्रम aliveness to complete
 *
 * @dev: the device काष्ठाure
 * @req: requested aliveness value
 *
 * Return: 0 on success and < 0 otherwise
 */
पूर्णांक mei_txe_aliveness_set_sync(काष्ठा mei_device *dev, u32 req)
अणु
	अगर (mei_txe_aliveness_set(dev, req))
		वापस mei_txe_aliveness_रुको(dev, req);
	वापस 0;
पूर्ण

/**
 * mei_txe_pg_in_transition - is device now in pg transition
 *
 * @dev: the device काष्ठाure
 *
 * Return: true अगर in pg transition, false otherwise
 */
अटल bool mei_txe_pg_in_transition(काष्ठा mei_device *dev)
अणु
	वापस dev->pg_event == MEI_PG_EVENT_WAIT;
पूर्ण

/**
 * mei_txe_pg_is_enabled - detect अगर PG is supported by HW
 *
 * @dev: the device काष्ठाure
 *
 * Return: true is pg supported, false otherwise
 */
अटल bool mei_txe_pg_is_enabled(काष्ठा mei_device *dev)
अणु
	वापस true;
पूर्ण

/**
 * mei_txe_pg_state  - translate aliveness रेजिस्टर value
 *   to the mei घातer gating state
 *
 * @dev: the device काष्ठाure
 *
 * Return: MEI_PG_OFF अगर aliveness is on and MEI_PG_ON otherwise
 */
अटल अंतरभूत क्रमागत mei_pg_state mei_txe_pg_state(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	वापस hw->aliveness ? MEI_PG_OFF : MEI_PG_ON;
पूर्ण

/**
 * mei_txe_input_पढ़ोy_पूर्णांकerrupt_enable - sets the Input Ready Interrupt
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_txe_input_पढ़ोy_पूर्णांकerrupt_enable(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 hपूर्णांकmsk;
	/* Enable the SEC_IPC_HOST_INT_MASK_IN_RDY पूर्णांकerrupt */
	hपूर्णांकmsk = mei_txe_sec_reg_पढ़ो(hw, SEC_IPC_HOST_INT_MASK_REG);
	hपूर्णांकmsk |= SEC_IPC_HOST_INT_MASK_IN_RDY;
	mei_txe_sec_reg_ग_लिखो(hw, SEC_IPC_HOST_INT_MASK_REG, hपूर्णांकmsk);
पूर्ण

/**
 * mei_txe_input_करोorbell_set - sets bit 0 in
 *    SEC_IPC_INPUT_DOORBELL.IPC_INPUT_DOORBELL.
 *
 * @hw: the txe hardware काष्ठाure
 */
अटल व्योम mei_txe_input_करोorbell_set(काष्ठा mei_txe_hw *hw)
अणु
	/* Clear the पूर्णांकerrupt cause */
	clear_bit(TXE_INTR_IN_READY_BIT, &hw->पूर्णांकr_cause);
	mei_txe_sec_reg_ग_लिखो(hw, SEC_IPC_INPUT_DOORBELL_REG, 1);
पूर्ण

/**
 * mei_txe_output_पढ़ोy_set - Sets the SICR_SEC_IPC_OUTPUT_STATUS bit to 1
 *
 * @hw: the txe hardware काष्ठाure
 */
अटल व्योम mei_txe_output_पढ़ोy_set(काष्ठा mei_txe_hw *hw)
अणु
	mei_txe_br_reg_ग_लिखो(hw,
			SICR_SEC_IPC_OUTPUT_STATUS_REG,
			SEC_IPC_OUTPUT_STATUS_RDY);
पूर्ण

/**
 * mei_txe_is_input_पढ़ोy - check अगर TXE is पढ़ोy क्रम receiving data
 *
 * @dev: the device काष्ठाure
 *
 * Return: true अगर INPUT STATUS READY bit is set
 */
अटल bool mei_txe_is_input_पढ़ोy(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 status;

	status = mei_txe_sec_reg_पढ़ो(hw, SEC_IPC_INPUT_STATUS_REG);
	वापस !!(SEC_IPC_INPUT_STATUS_RDY & status);
पूर्ण

/**
 * mei_txe_पूर्णांकr_clear - clear all पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 */
अटल अंतरभूत व्योम mei_txe_पूर्णांकr_clear(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_sec_reg_ग_लिखो_silent(hw, SEC_IPC_HOST_INT_STATUS_REG,
		SEC_IPC_HOST_INT_STATUS_PENDING);
	mei_txe_br_reg_ग_लिखो(hw, HISR_REG, HISR_INT_STS_MSK);
	mei_txe_br_reg_ग_लिखो(hw, HHISR_REG, IPC_HHIER_MSK);
पूर्ण

/**
 * mei_txe_पूर्णांकr_disable - disable all पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_txe_पूर्णांकr_disable(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_br_reg_ग_लिखो(hw, HHIER_REG, 0);
	mei_txe_br_reg_ग_लिखो(hw, HIER_REG, 0);
पूर्ण
/**
 * mei_txe_पूर्णांकr_enable - enable all पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_txe_पूर्णांकr_enable(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_br_reg_ग_लिखो(hw, HHIER_REG, IPC_HHIER_MSK);
	mei_txe_br_reg_ग_लिखो(hw, HIER_REG, HIER_INT_EN_MSK);
पूर्ण

/**
 * mei_txe_synchronize_irq - रुको क्रम pending IRQ handlers
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_txe_synchronize_irq(काष्ठा mei_device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	synchronize_irq(pdev->irq);
पूर्ण

/**
 * mei_txe_pending_पूर्णांकerrupts - check अगर there are pending पूर्णांकerrupts
 *	only Aliveness, Input पढ़ोy, and output करोorbell are of relevance
 *
 * @dev: the device काष्ठाure
 *
 * Checks अगर there are pending पूर्णांकerrupts
 * only Aliveness, Readiness, Input पढ़ोy, and Output करोorbell are relevant
 *
 * Return: true अगर there are pending पूर्णांकerrupts
 */
अटल bool mei_txe_pending_पूर्णांकerrupts(काष्ठा mei_device *dev)
अणु

	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	bool ret = (hw->पूर्णांकr_cause & (TXE_INTR_READINESS |
				      TXE_INTR_ALIVENESS |
				      TXE_INTR_IN_READY  |
				      TXE_INTR_OUT_DB));

	अगर (ret) अणु
		dev_dbg(dev->dev,
			"Pending Interrupts InReady=%01d Readiness=%01d, Aliveness=%01d, OutDoor=%01d\n",
			!!(hw->पूर्णांकr_cause & TXE_INTR_IN_READY),
			!!(hw->पूर्णांकr_cause & TXE_INTR_READINESS),
			!!(hw->पूर्णांकr_cause & TXE_INTR_ALIVENESS),
			!!(hw->पूर्णांकr_cause & TXE_INTR_OUT_DB));
	पूर्ण
	वापस ret;
पूर्ण

/**
 * mei_txe_input_payload_ग_लिखो - ग_लिखो a dword to the host buffer
 *	at offset idx
 *
 * @dev: the device काष्ठाure
 * @idx: index in the host buffer
 * @value: value
 */
अटल व्योम mei_txe_input_payload_ग_लिखो(काष्ठा mei_device *dev,
			अचिन्हित दीर्घ idx, u32 value)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_sec_reg_ग_लिखो(hw, SEC_IPC_INPUT_PAYLOAD_REG +
			(idx * माप(u32)), value);
पूर्ण

/**
 * mei_txe_out_data_पढ़ो - पढ़ो dword from the device buffer
 *	at offset idx
 *
 * @dev: the device काष्ठाure
 * @idx: index in the device buffer
 *
 * Return: रेजिस्टर value at index
 */
अटल u32 mei_txe_out_data_पढ़ो(स्थिर काष्ठा mei_device *dev,
					अचिन्हित दीर्घ idx)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	वापस mei_txe_br_reg_पढ़ो(hw,
		BRIDGE_IPC_OUTPUT_PAYLOAD_REG + (idx * माप(u32)));
पूर्ण

/* Readiness */

/**
 * mei_txe_पढ़ोiness_set_host_rdy - set host पढ़ोiness bit
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_txe_पढ़ोiness_set_host_rdy(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_br_reg_ग_लिखो(hw,
		SICR_HOST_IPC_READINESS_REQ_REG,
		SICR_HOST_IPC_READINESS_HOST_RDY);
पूर्ण

/**
 * mei_txe_पढ़ोiness_clear - clear host पढ़ोiness bit
 *
 * @dev: the device काष्ठाure
 */
अटल व्योम mei_txe_पढ़ोiness_clear(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	mei_txe_br_reg_ग_लिखो(hw, SICR_HOST_IPC_READINESS_REQ_REG,
				SICR_HOST_IPC_READINESS_RDY_CLR);
पूर्ण
/**
 * mei_txe_पढ़ोiness_get - Reads and वापसs
 *	the HICR_SEC_IPC_READINESS रेजिस्टर value
 *
 * @dev: the device काष्ठाure
 *
 * Return: the HICR_SEC_IPC_READINESS रेजिस्टर value
 */
अटल u32 mei_txe_पढ़ोiness_get(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	वापस mei_txe_br_reg_पढ़ो(hw, HICR_SEC_IPC_READINESS_REG);
पूर्ण


/**
 * mei_txe_पढ़ोiness_is_sec_rdy - check पढ़ोiness
 *  क्रम HICR_SEC_IPC_READINESS_SEC_RDY
 *
 * @पढ़ोiness: cached पढ़ोiness state
 *
 * Return: true अगर पढ़ोiness bit is set
 */
अटल अंतरभूत bool mei_txe_पढ़ोiness_is_sec_rdy(u32 पढ़ोiness)
अणु
	वापस !!(पढ़ोiness & HICR_SEC_IPC_READINESS_SEC_RDY);
पूर्ण

/**
 * mei_txe_hw_is_पढ़ोy - check अगर the hw is पढ़ोy
 *
 * @dev: the device काष्ठाure
 *
 * Return: true अगर sec is पढ़ोy
 */
अटल bool mei_txe_hw_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	u32 पढ़ोiness =  mei_txe_पढ़ोiness_get(dev);

	वापस mei_txe_पढ़ोiness_is_sec_rdy(पढ़ोiness);
पूर्ण

/**
 * mei_txe_host_is_पढ़ोy - check अगर the host is पढ़ोy
 *
 * @dev: the device काष्ठाure
 *
 * Return: true अगर host is पढ़ोy
 */
अटल अंतरभूत bool mei_txe_host_is_पढ़ोy(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 reg = mei_txe_br_reg_पढ़ो(hw, HICR_SEC_IPC_READINESS_REG);

	वापस !!(reg & HICR_SEC_IPC_READINESS_HOST_RDY);
पूर्ण

/**
 * mei_txe_पढ़ोiness_रुको - रुको till पढ़ोiness settles
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success and -ETIME on समयout
 */
अटल पूर्णांक mei_txe_पढ़ोiness_रुको(काष्ठा mei_device *dev)
अणु
	अगर (mei_txe_hw_is_पढ़ोy(dev))
		वापस 0;

	mutex_unlock(&dev->device_lock);
	रुको_event_समयout(dev->रुको_hw_पढ़ोy, dev->recvd_hw_पढ़ोy,
			msecs_to_jअगरfies(SEC_RESET_WAIT_TIMEOUT));
	mutex_lock(&dev->device_lock);
	अगर (!dev->recvd_hw_पढ़ोy) अणु
		dev_err(dev->dev, "wait for readiness failed\n");
		वापस -ETIME;
	पूर्ण

	dev->recvd_hw_पढ़ोy = false;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mei_fw_status mei_txe_fw_sts = अणु
	.count = 2,
	.status[0] = PCI_CFG_TXE_FW_STS0,
	.status[1] = PCI_CFG_TXE_FW_STS1
पूर्ण;

/**
 * mei_txe_fw_status - पढ़ो fw status रेजिस्टर from pci config space
 *
 * @dev: mei device
 * @fw_status: fw status रेजिस्टर values
 *
 * Return: 0 on success, error otherwise
 */
अटल पूर्णांक mei_txe_fw_status(काष्ठा mei_device *dev,
			     काष्ठा mei_fw_status *fw_status)
अणु
	स्थिर काष्ठा mei_fw_status *fw_src = &mei_txe_fw_sts;
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!fw_status)
		वापस -EINVAL;

	fw_status->count = fw_src->count;
	क्रम (i = 0; i < fw_src->count && i < MEI_FW_STATUS_MAX; i++) अणु
		ret = pci_पढ़ो_config_dword(pdev, fw_src->status[i],
					    &fw_status->status[i]);
		trace_mei_pci_cfg_पढ़ो(dev->dev, "PCI_CFG_HSF_X",
				       fw_src->status[i],
				       fw_status->status[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * mei_txe_hw_config - configure hardware at the start of the devices
 *
 * @dev: the device काष्ठाure
 *
 * Configure hardware at the start of the device should be करोne only
 *   once at the device probe समय
 *
 * Return: always 0
 */
अटल पूर्णांक mei_txe_hw_config(काष्ठा mei_device *dev)
अणु

	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	hw->aliveness = mei_txe_aliveness_get(dev);
	hw->पढ़ोiness = mei_txe_पढ़ोiness_get(dev);

	dev_dbg(dev->dev, "aliveness_resp = 0x%08x, readiness = 0x%08x.\n",
		hw->aliveness, hw->पढ़ोiness);

	वापस 0;
पूर्ण

/**
 * mei_txe_ग_लिखो - ग_लिखोs a message to device.
 *
 * @dev: the device काष्ठाure
 * @hdr: header of message
 * @hdr_len: header length in bytes - must multiplication of a slot (4bytes)
 * @data: payload
 * @data_len: paylead length in bytes
 *
 * Return: 0 अगर success, < 0 - otherwise.
 */
अटल पूर्णांक mei_txe_ग_लिखो(काष्ठा mei_device *dev,
			 स्थिर व्योम *hdr, माप_प्रकार hdr_len,
			 स्थिर व्योम *data, माप_प्रकार data_len)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	अचिन्हित दीर्घ rem;
	स्थिर u32 *reg_buf;
	u32 slots = TXE_HBUF_DEPTH;
	u32 dw_cnt;
	अचिन्हित दीर्घ i, j;

	अगर (WARN_ON(!hdr || !data || hdr_len & 0x3))
		वापस -EINVAL;

	dev_dbg(dev->dev, MEI_HDR_FMT, MEI_HDR_PRM((काष्ठा mei_msg_hdr *)hdr));

	dw_cnt = mei_data2slots(hdr_len + data_len);
	अगर (dw_cnt > slots)
		वापस -EMSGSIZE;

	अगर (WARN(!hw->aliveness, "txe write: aliveness not asserted\n"))
		वापस -EAGAIN;

	/* Enable Input Ready Interrupt. */
	mei_txe_input_पढ़ोy_पूर्णांकerrupt_enable(dev);

	अगर (!mei_txe_is_input_पढ़ोy(dev)) अणु
		अक्षर fw_sts_str[MEI_FW_STATUS_STR_SZ];

		mei_fw_status_str(dev, fw_sts_str, MEI_FW_STATUS_STR_SZ);
		dev_err(dev->dev, "Input is not ready %s\n", fw_sts_str);
		वापस -EAGAIN;
	पूर्ण

	reg_buf = hdr;
	क्रम (i = 0; i < hdr_len / MEI_SLOT_SIZE; i++)
		mei_txe_input_payload_ग_लिखो(dev, i, reg_buf[i]);

	reg_buf = data;
	क्रम (j = 0; j < data_len / MEI_SLOT_SIZE; j++)
		mei_txe_input_payload_ग_लिखो(dev, i + j, reg_buf[j]);

	rem = data_len & 0x3;
	अगर (rem > 0) अणु
		u32 reg = 0;

		स_नकल(&reg, (स्थिर u8 *)data + data_len - rem, rem);
		mei_txe_input_payload_ग_लिखो(dev, i + j, reg);
	पूर्ण

	/* after each ग_लिखो the whole buffer is consumed */
	hw->slots = 0;

	/* Set Input-Doorbell */
	mei_txe_input_करोorbell_set(hw);

	वापस 0;
पूर्ण

/**
 * mei_txe_hbuf_depth - mimics the me hbuf circular buffer
 *
 * @dev: the device काष्ठाure
 *
 * Return: the TXE_HBUF_DEPTH
 */
अटल u32 mei_txe_hbuf_depth(स्थिर काष्ठा mei_device *dev)
अणु
	वापस TXE_HBUF_DEPTH;
पूर्ण

/**
 * mei_txe_hbuf_empty_slots - mimics the me hbuf circular buffer
 *
 * @dev: the device काष्ठाure
 *
 * Return: always TXE_HBUF_DEPTH
 */
अटल पूर्णांक mei_txe_hbuf_empty_slots(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	वापस hw->slots;
पूर्ण

/**
 * mei_txe_count_full_पढ़ो_slots - mimics the me device circular buffer
 *
 * @dev: the device काष्ठाure
 *
 * Return: always buffer size in dwords count
 */
अटल पूर्णांक mei_txe_count_full_पढ़ो_slots(काष्ठा mei_device *dev)
अणु
	/* पढ़ो buffers has अटल size */
	वापस TXE_HBUF_DEPTH;
पूर्ण

/**
 * mei_txe_पढ़ो_hdr - पढ़ो message header which is always in 4 first bytes
 *
 * @dev: the device काष्ठाure
 *
 * Return: mei message header
 */

अटल u32 mei_txe_पढ़ो_hdr(स्थिर काष्ठा mei_device *dev)
अणु
	वापस mei_txe_out_data_पढ़ो(dev, 0);
पूर्ण
/**
 * mei_txe_पढ़ो - पढ़ोs a message from the txe device.
 *
 * @dev: the device काष्ठाure
 * @buf: message buffer will be written
 * @len: message size will be पढ़ो
 *
 * Return: -EINVAL on error wrong argument and 0 on success
 */
अटल पूर्णांक mei_txe_पढ़ो(काष्ठा mei_device *dev,
		अचिन्हित अक्षर *buf, अचिन्हित दीर्घ len)
अणु

	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 *reg_buf, reg;
	u32 rem;
	u32 i;

	अगर (WARN_ON(!buf || !len))
		वापस -EINVAL;

	reg_buf = (u32 *)buf;
	rem = len & 0x3;

	dev_dbg(dev->dev, "buffer-length = %lu buf[0]0x%08X\n",
		len, mei_txe_out_data_पढ़ो(dev, 0));

	क्रम (i = 0; i < len / MEI_SLOT_SIZE; i++) अणु
		/* skip header: index starts from 1 */
		reg = mei_txe_out_data_पढ़ो(dev, i + 1);
		dev_dbg(dev->dev, "buf[%d] = 0x%08X\n", i, reg);
		*reg_buf++ = reg;
	पूर्ण

	अगर (rem) अणु
		reg = mei_txe_out_data_पढ़ो(dev, i + 1);
		स_नकल(reg_buf, &reg, rem);
	पूर्ण

	mei_txe_output_पढ़ोy_set(hw);
	वापस 0;
पूर्ण

/**
 * mei_txe_hw_reset - resets host and fw.
 *
 * @dev: the device काष्ठाure
 * @पूर्णांकr_enable: अगर पूर्णांकerrupt should be enabled after reset.
 *
 * Return: 0 on success and < 0 in हाल of error
 */
अटल पूर्णांक mei_txe_hw_reset(काष्ठा mei_device *dev, bool पूर्णांकr_enable)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	u32 aliveness_req;
	/*
	 * पढ़ो input करोorbell to ensure consistency between  Bridge and SeC
	 * वापस value might be garbage वापस
	 */
	(व्योम)mei_txe_sec_reg_पढ़ो_silent(hw, SEC_IPC_INPUT_DOORBELL_REG);

	aliveness_req = mei_txe_aliveness_req_get(dev);
	hw->aliveness = mei_txe_aliveness_get(dev);

	/* Disable पूर्णांकerrupts in this stage we will poll */
	mei_txe_पूर्णांकr_disable(dev);

	/*
	 * If Aliveness Request and Aliveness Response are not equal then
	 * रुको क्रम them to be equal
	 * Since we might have पूर्णांकerrupts disabled - poll क्रम it
	 */
	अगर (aliveness_req != hw->aliveness)
		अगर (mei_txe_aliveness_poll(dev, aliveness_req) < 0) अणु
			dev_err(dev->dev, "wait for aliveness settle failed ... bailing out\n");
			वापस -EIO;
		पूर्ण

	/*
	 * If Aliveness Request and Aliveness Response are set then clear them
	 */
	अगर (aliveness_req) अणु
		mei_txe_aliveness_set(dev, 0);
		अगर (mei_txe_aliveness_poll(dev, 0) < 0) अणु
			dev_err(dev->dev, "wait for aliveness failed ... bailing out\n");
			वापस -EIO;
		पूर्ण
	पूर्ण

	/*
	 * Set पढ़ोiness RDY_CLR bit
	 */
	mei_txe_पढ़ोiness_clear(dev);

	वापस 0;
पूर्ण

/**
 * mei_txe_hw_start - start the hardware after reset
 *
 * @dev: the device काष्ठाure
 *
 * Return: 0 on success an error code otherwise
 */
अटल पूर्णांक mei_txe_hw_start(काष्ठा mei_device *dev)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	पूर्णांक ret;

	u32 hisr;

	/* bring back पूर्णांकerrupts */
	mei_txe_पूर्णांकr_enable(dev);

	ret = mei_txe_पढ़ोiness_रुको(dev);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "waiting for readiness failed\n");
		वापस ret;
	पूर्ण

	/*
	 * If HISR.INT2_STS पूर्णांकerrupt status bit is set then clear it.
	 */
	hisr = mei_txe_br_reg_पढ़ो(hw, HISR_REG);
	अगर (hisr & HISR_INT_2_STS)
		mei_txe_br_reg_ग_लिखो(hw, HISR_REG, HISR_INT_2_STS);

	/* Clear the पूर्णांकerrupt cause of OutputDoorbell */
	clear_bit(TXE_INTR_OUT_DB_BIT, &hw->पूर्णांकr_cause);

	ret = mei_txe_aliveness_set_sync(dev, 1);
	अगर (ret < 0) अणु
		dev_err(dev->dev, "wait for aliveness failed ... bailing out\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_active(dev->dev);

	/* enable input पढ़ोy पूर्णांकerrupts:
	 * SEC_IPC_HOST_INT_MASK.IPC_INPUT_READY_INT_MASK
	 */
	mei_txe_input_पढ़ोy_पूर्णांकerrupt_enable(dev);


	/*  Set the SICR_SEC_IPC_OUTPUT_STATUS.IPC_OUTPUT_READY bit */
	mei_txe_output_पढ़ोy_set(hw);

	/* Set bit SICR_HOST_IPC_READINESS.HOST_RDY
	 */
	mei_txe_पढ़ोiness_set_host_rdy(dev);

	वापस 0;
पूर्ण

/**
 * mei_txe_check_and_ack_पूर्णांकrs - translate multi BAR पूर्णांकerrupt पूर्णांकo
 *  single bit mask and acknowledge the पूर्णांकerrupts
 *
 * @dev: the device काष्ठाure
 * @करो_ack: acknowledge पूर्णांकerrupts
 *
 * Return: true अगर found पूर्णांकerrupts to process.
 */
अटल bool mei_txe_check_and_ack_पूर्णांकrs(काष्ठा mei_device *dev, bool करो_ack)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	u32 hisr;
	u32 hhisr;
	u32 ipc_isr;
	u32 aliveness;
	bool generated;

	/* पढ़ो पूर्णांकerrupt रेजिस्टरs */
	hhisr = mei_txe_br_reg_पढ़ो(hw, HHISR_REG);
	generated = (hhisr & IPC_HHIER_MSK);
	अगर (!generated)
		जाओ out;

	hisr = mei_txe_br_reg_पढ़ो(hw, HISR_REG);

	aliveness = mei_txe_aliveness_get(dev);
	अगर (hhisr & IPC_HHIER_SEC && aliveness) अणु
		ipc_isr = mei_txe_sec_reg_पढ़ो_silent(hw,
				SEC_IPC_HOST_INT_STATUS_REG);
	पूर्ण अन्यथा अणु
		ipc_isr = 0;
		hhisr &= ~IPC_HHIER_SEC;
	पूर्ण

	generated = generated ||
		(hisr & HISR_INT_STS_MSK) ||
		(ipc_isr & SEC_IPC_HOST_INT_STATUS_PENDING);

	अगर (generated && करो_ack) अणु
		/* Save the पूर्णांकerrupt causes */
		hw->पूर्णांकr_cause |= hisr & HISR_INT_STS_MSK;
		अगर (ipc_isr & SEC_IPC_HOST_INT_STATUS_IN_RDY)
			hw->पूर्णांकr_cause |= TXE_INTR_IN_READY;


		mei_txe_पूर्णांकr_disable(dev);
		/* Clear the पूर्णांकerrupts in hierarchy:
		 * IPC and Bridge, than the High Level */
		mei_txe_sec_reg_ग_लिखो_silent(hw,
			SEC_IPC_HOST_INT_STATUS_REG, ipc_isr);
		mei_txe_br_reg_ग_लिखो(hw, HISR_REG, hisr);
		mei_txe_br_reg_ग_लिखो(hw, HHISR_REG, hhisr);
	पूर्ण

out:
	वापस generated;
पूर्ण

/**
 * mei_txe_irq_quick_handler - The ISR of the MEI device
 *
 * @irq: The irq number
 * @dev_id: poपूर्णांकer to the device काष्ठाure
 *
 * Return: IRQ_WAKE_THREAD अगर पूर्णांकerrupt is deचिन्हित क्रम the device
 *         IRQ_NONE otherwise
 */
irqवापस_t mei_txe_irq_quick_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mei_device *dev = dev_id;

	अगर (mei_txe_check_and_ack_पूर्णांकrs(dev, true))
		वापस IRQ_WAKE_THREAD;
	वापस IRQ_NONE;
पूर्ण


/**
 * mei_txe_irq_thपढ़ो_handler - txe पूर्णांकerrupt thपढ़ो
 *
 * @irq: The irq number
 * @dev_id: poपूर्णांकer to the device काष्ठाure
 *
 * Return: IRQ_HANDLED
 */
irqवापस_t mei_txe_irq_thपढ़ो_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा mei_device *dev = (काष्ठा mei_device *) dev_id;
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);
	काष्ठा list_head cmpl_list;
	s32 slots;
	पूर्णांक rets = 0;

	dev_dbg(dev->dev, "irq thread: Interrupt Registers HHISR|HISR|SEC=%02X|%04X|%02X\n",
		mei_txe_br_reg_पढ़ो(hw, HHISR_REG),
		mei_txe_br_reg_पढ़ो(hw, HISR_REG),
		mei_txe_sec_reg_पढ़ो_silent(hw, SEC_IPC_HOST_INT_STATUS_REG));


	/* initialize our complete list */
	mutex_lock(&dev->device_lock);
	INIT_LIST_HEAD(&cmpl_list);

	अगर (pci_dev_msi_enabled(to_pci_dev(dev->dev)))
		mei_txe_check_and_ack_पूर्णांकrs(dev, true);

	/* show irq events */
	mei_txe_pending_पूर्णांकerrupts(dev);

	hw->aliveness = mei_txe_aliveness_get(dev);
	hw->पढ़ोiness = mei_txe_पढ़ोiness_get(dev);

	/* Readiness:
	 * Detection of TXE driver going through reset
	 * or TXE driver resetting the HECI पूर्णांकerface.
	 */
	अगर (test_and_clear_bit(TXE_INTR_READINESS_BIT, &hw->पूर्णांकr_cause)) अणु
		dev_dbg(dev->dev, "Readiness Interrupt was received...\n");

		/* Check अगर SeC is going through reset */
		अगर (mei_txe_पढ़ोiness_is_sec_rdy(hw->पढ़ोiness)) अणु
			dev_dbg(dev->dev, "we need to start the dev.\n");
			dev->recvd_hw_पढ़ोy = true;
		पूर्ण अन्यथा अणु
			dev->recvd_hw_पढ़ोy = false;
			अगर (dev->dev_state != MEI_DEV_RESETTING) अणु

				dev_warn(dev->dev, "FW not ready: resetting.\n");
				schedule_work(&dev->reset_work);
				जाओ end;

			पूर्ण
		पूर्ण
		wake_up(&dev->रुको_hw_पढ़ोy);
	पूर्ण

	/************************************************************/
	/* Check पूर्णांकerrupt cause:
	 * Aliveness: Detection of SeC acknowledge of host request that
	 * it reमुख्य alive or host cancellation of that request.
	 */

	अगर (test_and_clear_bit(TXE_INTR_ALIVENESS_BIT, &hw->पूर्णांकr_cause)) अणु
		/* Clear the पूर्णांकerrupt cause */
		dev_dbg(dev->dev,
			"Aliveness Interrupt: Status: %d\n", hw->aliveness);
		dev->pg_event = MEI_PG_EVENT_RECEIVED;
		अगर (रुकोqueue_active(&hw->रुको_aliveness_resp))
			wake_up(&hw->रुको_aliveness_resp);
	पूर्ण


	/* Output Doorbell:
	 * Detection of SeC having sent output to host
	 */
	slots = mei_count_full_पढ़ो_slots(dev);
	अगर (test_and_clear_bit(TXE_INTR_OUT_DB_BIT, &hw->पूर्णांकr_cause)) अणु
		/* Read from TXE */
		rets = mei_irq_पढ़ो_handler(dev, &cmpl_list, &slots);
		अगर (rets &&
		    (dev->dev_state != MEI_DEV_RESETTING &&
		     dev->dev_state != MEI_DEV_POWER_DOWN)) अणु
			dev_err(dev->dev,
				"mei_irq_read_handler ret = %d.\n", rets);

			schedule_work(&dev->reset_work);
			जाओ end;
		पूर्ण
	पूर्ण
	/* Input Ready: Detection अगर host can ग_लिखो to SeC */
	अगर (test_and_clear_bit(TXE_INTR_IN_READY_BIT, &hw->पूर्णांकr_cause)) अणु
		dev->hbuf_is_पढ़ोy = true;
		hw->slots = TXE_HBUF_DEPTH;
	पूर्ण

	अगर (hw->aliveness && dev->hbuf_is_पढ़ोy) अणु
		/* get the real रेजिस्टर value */
		dev->hbuf_is_पढ़ोy = mei_hbuf_is_पढ़ोy(dev);
		rets = mei_irq_ग_लिखो_handler(dev, &cmpl_list);
		अगर (rets && rets != -EMSGSIZE)
			dev_err(dev->dev, "mei_irq_write_handler ret = %d.\n",
				rets);
		dev->hbuf_is_पढ़ोy = mei_hbuf_is_पढ़ोy(dev);
	पूर्ण

	mei_irq_compl_handler(dev, &cmpl_list);

end:
	dev_dbg(dev->dev, "interrupt thread end ret = %d\n", rets);

	mutex_unlock(&dev->device_lock);

	mei_enable_पूर्णांकerrupts(dev);
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर काष्ठा mei_hw_ops mei_txe_hw_ops = अणु

	.host_is_पढ़ोy = mei_txe_host_is_पढ़ोy,

	.fw_status = mei_txe_fw_status,
	.pg_state = mei_txe_pg_state,

	.hw_is_पढ़ोy = mei_txe_hw_is_पढ़ोy,
	.hw_reset = mei_txe_hw_reset,
	.hw_config = mei_txe_hw_config,
	.hw_start = mei_txe_hw_start,

	.pg_in_transition = mei_txe_pg_in_transition,
	.pg_is_enabled = mei_txe_pg_is_enabled,

	.पूर्णांकr_clear = mei_txe_पूर्णांकr_clear,
	.पूर्णांकr_enable = mei_txe_पूर्णांकr_enable,
	.पूर्णांकr_disable = mei_txe_पूर्णांकr_disable,
	.synchronize_irq = mei_txe_synchronize_irq,

	.hbuf_मुक्त_slots = mei_txe_hbuf_empty_slots,
	.hbuf_is_पढ़ोy = mei_txe_is_input_पढ़ोy,
	.hbuf_depth = mei_txe_hbuf_depth,

	.ग_लिखो = mei_txe_ग_लिखो,

	.rdbuf_full_slots = mei_txe_count_full_पढ़ो_slots,
	.पढ़ो_hdr = mei_txe_पढ़ो_hdr,

	.पढ़ो = mei_txe_पढ़ो,

पूर्ण;

/**
 * mei_txe_dev_init - allocates and initializes txe hardware specअगरic काष्ठाure
 *
 * @pdev: pci device
 *
 * Return: काष्ठा mei_device * on success or शून्य
 */
काष्ठा mei_device *mei_txe_dev_init(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mei_device *dev;
	काष्ठा mei_txe_hw *hw;

	dev = devm_kzalloc(&pdev->dev, माप(*dev) + माप(*hw), GFP_KERNEL);
	अगर (!dev)
		वापस शून्य;

	mei_device_init(dev, &pdev->dev, &mei_txe_hw_ops);

	hw = to_txe_hw(dev);

	init_रुकोqueue_head(&hw->रुको_aliveness_resp);

	वापस dev;
पूर्ण

/**
 * mei_txe_setup_satt2 - SATT2 configuration क्रम DMA support.
 *
 * @dev:   the device काष्ठाure
 * @addr:  physical address start of the range
 * @range: physical range size
 *
 * Return: 0 on success an error code otherwise
 */
पूर्णांक mei_txe_setup_satt2(काष्ठा mei_device *dev, phys_addr_t addr, u32 range)
अणु
	काष्ठा mei_txe_hw *hw = to_txe_hw(dev);

	u32 lo32 = lower_32_bits(addr);
	u32 hi32 = upper_32_bits(addr);
	u32 ctrl;

	/* SATT is limited to 36 Bits */
	अगर (hi32 & ~0xF)
		वापस -EINVAL;

	/* SATT has to be 16Byte aligned */
	अगर (lo32 & 0xF)
		वापस -EINVAL;

	/* SATT range has to be 4Bytes aligned */
	अगर (range & 0x4)
		वापस -EINVAL;

	/* SATT is limited to 32 MB range*/
	अगर (range > SATT_RANGE_MAX)
		वापस -EINVAL;

	ctrl = SATT2_CTRL_VALID_MSK;
	ctrl |= hi32  << SATT2_CTRL_BR_BASE_ADDR_REG_SHIFT;

	mei_txe_br_reg_ग_लिखो(hw, SATT2_SAP_SIZE_REG, range);
	mei_txe_br_reg_ग_लिखो(hw, SATT2_BRG_BA_LSB_REG, lo32);
	mei_txe_br_reg_ग_लिखो(hw, SATT2_CTRL_REG, ctrl);
	dev_dbg(dev->dev, "SATT2: SAP_SIZE_OFFSET=0x%08X, BRG_BA_LSB_OFFSET=0x%08X, CTRL_OFFSET=0x%08X\n",
		range, lo32, ctrl);

	वापस 0;
पूर्ण
