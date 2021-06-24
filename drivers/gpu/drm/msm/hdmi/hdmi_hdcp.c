<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2010-2015, The Linux Foundation. All rights reserved.
 */

#समावेश "hdmi.h"
#समावेश <linux/qcom_scm.h>

#घोषणा HDCP_REG_ENABLE 0x01
#घोषणा HDCP_REG_DISABLE 0x00
#घोषणा HDCP_PORT_ADDR 0x74

#घोषणा HDCP_INT_STATUS_MASK ( \
		HDMI_HDCP_INT_CTRL_AUTH_SUCCESS_INT | \
		HDMI_HDCP_INT_CTRL_AUTH_FAIL_INT | \
		HDMI_HDCP_INT_CTRL_AUTH_XFER_REQ_INT | \
		HDMI_HDCP_INT_CTRL_AUTH_XFER_DONE_INT)

#घोषणा AUTH_WORK_RETRIES_TIME 100
#घोषणा AUTH_RETRIES_TIME 30

/* QFPROM Registers क्रम HDMI/HDCP */
#घोषणा QFPROM_RAW_FEAT_CONFIG_ROW0_LSB  0x000000F8
#घोषणा QFPROM_RAW_FEAT_CONFIG_ROW0_MSB  0x000000FC
#घोषणा HDCP_KSV_LSB                     0x000060D8
#घोषणा HDCP_KSV_MSB                     0x000060DC

क्रमागत DS_TYPE अणु  /* type of करोwnstream device */
	DS_UNKNOWN,
	DS_RECEIVER,
	DS_REPEATER,
पूर्ण;

क्रमागत hdmi_hdcp_state अणु
	HDCP_STATE_NO_AKSV,
	HDCP_STATE_INACTIVE,
	HDCP_STATE_AUTHENTICATING,
	HDCP_STATE_AUTHENTICATED,
	HDCP_STATE_AUTH_FAILED
पूर्ण;

काष्ठा hdmi_hdcp_reg_data अणु
	u32 reg_id;
	u32 off;
	अक्षर *name;
	u32 reg_val;
पूर्ण;

काष्ठा hdmi_hdcp_ctrl अणु
	काष्ठा hdmi *hdmi;
	u32 auth_retries;
	bool tz_hdcp;
	क्रमागत hdmi_hdcp_state hdcp_state;
	काष्ठा work_काष्ठा hdcp_auth_work;
	काष्ठा work_काष्ठा hdcp_reauth_work;

#घोषणा AUTH_ABORT_EV 1
#घोषणा AUTH_RESULT_RDY_EV 2
	अचिन्हित दीर्घ auth_event;
	रुको_queue_head_t auth_event_queue;

	u32 ksv_fअगरo_w_index;
	/*
	 * store aksv from qfprom
	 */
	u32 aksv_lsb;
	u32 aksv_msb;
	bool aksv_valid;
	u32 ds_type;
	u32 bksv_lsb;
	u32 bksv_msb;
	u8 dev_count;
	u8 depth;
	u8 ksv_list[5 * 127];
	bool max_cascade_exceeded;
	bool max_dev_exceeded;
पूर्ण;

अटल पूर्णांक msm_hdmi_ddc_पढ़ो(काष्ठा hdmi *hdmi, u16 addr, u8 offset,
	u8 *data, u16 data_len)
अणु
	पूर्णांक rc;
	पूर्णांक retry = 5;
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= addr >> 1,
			.flags	= 0,
			.len	= 1,
			.buf	= &offset,
		पूर्ण, अणु
			.addr	= addr >> 1,
			.flags	= I2C_M_RD,
			.len	= data_len,
			.buf	= data,
		पूर्ण
	पूर्ण;

	DBG("Start DDC read");
retry:
	rc = i2c_transfer(hdmi->i2c, msgs, 2);

	retry--;
	अगर (rc == 2)
		rc = 0;
	अन्यथा अगर (retry > 0)
		जाओ retry;
	अन्यथा
		rc = -EIO;

	DBG("End DDC read %d", rc);

	वापस rc;
पूर्ण

#घोषणा HDCP_DDC_WRITE_MAX_BYTE_NUM 32

अटल पूर्णांक msm_hdmi_ddc_ग_लिखो(काष्ठा hdmi *hdmi, u16 addr, u8 offset,
	u8 *data, u16 data_len)
अणु
	पूर्णांक rc;
	पूर्णांक retry = 10;
	u8 buf[HDCP_DDC_WRITE_MAX_BYTE_NUM];
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= addr >> 1,
			.flags	= 0,
			.len	= 1,
		पूर्ण
	पूर्ण;

	DBG("Start DDC write");
	अगर (data_len > (HDCP_DDC_WRITE_MAX_BYTE_NUM - 1)) अणु
		pr_err("%s: write size too big\n", __func__);
		वापस -दुस्फल;
	पूर्ण

	buf[0] = offset;
	स_नकल(&buf[1], data, data_len);
	msgs[0].buf = buf;
	msgs[0].len = data_len + 1;
retry:
	rc = i2c_transfer(hdmi->i2c, msgs, 1);

	retry--;
	अगर (rc == 1)
		rc = 0;
	अन्यथा अगर (retry > 0)
		जाओ retry;
	अन्यथा
		rc = -EIO;

	DBG("End DDC write %d", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_scm_wr(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl, u32 *preg,
	u32 *pdata, u32 count)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	काष्ठा qcom_scm_hdcp_req scm_buf[QCOM_SCM_HDCP_MAX_REQ_CNT];
	u32 resp, phy_addr, idx = 0;
	पूर्णांक i, ret = 0;

	WARN_ON(!pdata || !preg || (count == 0));

	अगर (hdcp_ctrl->tz_hdcp) अणु
		phy_addr = (u32)hdmi->mmio_phy_addr;

		जबतक (count) अणु
			स_रखो(scm_buf, 0, माप(scm_buf));
			क्रम (i = 0; i < count && i < QCOM_SCM_HDCP_MAX_REQ_CNT;
				i++) अणु
				scm_buf[i].addr = phy_addr + preg[idx];
				scm_buf[i].val  = pdata[idx];
				idx++;
			पूर्ण
			ret = qcom_scm_hdcp_req(scm_buf, i, &resp);

			अगर (ret || resp) अणु
				pr_err("%s: error: scm_call ret=%d resp=%u\n",
					__func__, ret, resp);
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			count -= i;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < count; i++)
			hdmi_ग_लिखो(hdmi, preg[i], pdata[i]);
	पूर्ण

	वापस ret;
पूर्ण

व्योम msm_hdmi_hdcp_irq(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg_val, hdcp_पूर्णांक_status;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_INT_CTRL);
	hdcp_पूर्णांक_status = reg_val & HDCP_INT_STATUS_MASK;
	अगर (!hdcp_पूर्णांक_status) अणु
		spin_unlock_irqrestore(&hdmi->reg_lock, flags);
		वापस;
	पूर्ण
	/* Clear Interrupts */
	reg_val |= hdcp_पूर्णांक_status << 1;
	/* Clear AUTH_FAIL_INFO as well */
	अगर (hdcp_पूर्णांक_status & HDMI_HDCP_INT_CTRL_AUTH_FAIL_INT)
		reg_val |= HDMI_HDCP_INT_CTRL_AUTH_FAIL_INFO_ACK;
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_INT_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	DBG("hdcp irq %x", hdcp_पूर्णांक_status);

	अगर (hdcp_पूर्णांक_status & HDMI_HDCP_INT_CTRL_AUTH_SUCCESS_INT) अणु
		pr_info("%s:AUTH_SUCCESS_INT received\n", __func__);
		अगर (HDCP_STATE_AUTHENTICATING == hdcp_ctrl->hdcp_state) अणु
			set_bit(AUTH_RESULT_RDY_EV, &hdcp_ctrl->auth_event);
			wake_up_all(&hdcp_ctrl->auth_event_queue);
		पूर्ण
	पूर्ण

	अगर (hdcp_पूर्णांक_status & HDMI_HDCP_INT_CTRL_AUTH_FAIL_INT) अणु
		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_LINK0_STATUS);
		pr_info("%s: AUTH_FAIL_INT rcvd, LINK0_STATUS=0x%08x\n",
			__func__, reg_val);
		अगर (HDCP_STATE_AUTHENTICATED == hdcp_ctrl->hdcp_state)
			queue_work(hdmi->workq, &hdcp_ctrl->hdcp_reauth_work);
		अन्यथा अगर (HDCP_STATE_AUTHENTICATING ==
				hdcp_ctrl->hdcp_state) अणु
			set_bit(AUTH_RESULT_RDY_EV, &hdcp_ctrl->auth_event);
			wake_up_all(&hdcp_ctrl->auth_event_queue);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_msleep(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl, u32 ms, u32 ev)
अणु
	पूर्णांक rc;

	rc = रुको_event_समयout(hdcp_ctrl->auth_event_queue,
		!!test_bit(ev, &hdcp_ctrl->auth_event),
		msecs_to_jअगरfies(ms));
	अगर (rc) अणु
		pr_info("%s: msleep is canceled by event %d\n",
				__func__, ev);
		clear_bit(ev, &hdcp_ctrl->auth_event);
		वापस -ECANCELED;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_पढ़ो_validate_aksv(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;

	/* Fetch aksv from QFPROM, this info should be खुला. */
	hdcp_ctrl->aksv_lsb = hdmi_qfprom_पढ़ो(hdmi, HDCP_KSV_LSB);
	hdcp_ctrl->aksv_msb = hdmi_qfprom_पढ़ो(hdmi, HDCP_KSV_MSB);

	/* check there are 20 ones in AKSV */
	अगर ((hweight32(hdcp_ctrl->aksv_lsb) + hweight32(hdcp_ctrl->aksv_msb))
			!= 20) अणु
		pr_err("%s: AKSV QFPROM doesn't have 20 1's, 20 0's\n",
			__func__);
		pr_err("%s: QFPROM AKSV chk failed (AKSV=%02x%08x)\n",
			__func__, hdcp_ctrl->aksv_msb,
			hdcp_ctrl->aksv_lsb);
		वापस -EINVAL;
	पूर्ण
	DBG("AKSV=%02x%08x", hdcp_ctrl->aksv_msb, hdcp_ctrl->aksv_lsb);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_reset_hdcp_ddc_failures(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg_val, failure, nack0;
	पूर्णांक rc = 0;

	/* Check क्रम any DDC transfer failures */
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_DDC_STATUS);
	failure = reg_val & HDMI_HDCP_DDC_STATUS_FAILED;
	nack0 = reg_val & HDMI_HDCP_DDC_STATUS_NACK0;
	DBG("HDCP_DDC_STATUS=0x%x, FAIL=%d, NACK0=%d",
		reg_val, failure, nack0);

	अगर (failure) अणु
		/*
		 * Indicates that the last HDCP HW DDC transfer failed.
		 * This occurs when a transfer is attempted with HDCP DDC
		 * disabled (HDCP_DDC_DISABLE=1) or the number of retries
		 * matches HDCP_DDC_RETRY_CNT.
		 * Failure occurred,  let's clear it.
		 */
		DBG("DDC failure detected");

		/* First, Disable DDC */
		hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_DDC_CTRL_0,
			HDMI_HDCP_DDC_CTRL_0_DISABLE);

		/* ACK the Failure to Clear it */
		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_DDC_CTRL_1);
		reg_val |= HDMI_HDCP_DDC_CTRL_1_FAILED_ACK;
		hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_DDC_CTRL_1, reg_val);

		/* Check अगर the FAILURE got Cleared */
		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_DDC_STATUS);
		अगर (reg_val & HDMI_HDCP_DDC_STATUS_FAILED)
			pr_info("%s: Unable to clear HDCP DDC Failure\n",
				__func__);

		/* Re-Enable HDCP DDC */
		hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_DDC_CTRL_0, 0);
	पूर्ण

	अगर (nack0) अणु
		DBG("Before: HDMI_DDC_SW_STATUS=0x%08x",
			hdmi_पढ़ो(hdmi, REG_HDMI_DDC_SW_STATUS));
		/* Reset HDMI DDC software status */
		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_CTRL);
		reg_val |= HDMI_DDC_CTRL_SW_STATUS_RESET;
		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL, reg_val);

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);

		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_CTRL);
		reg_val &= ~HDMI_DDC_CTRL_SW_STATUS_RESET;
		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL, reg_val);

		/* Reset HDMI DDC Controller */
		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_CTRL);
		reg_val |= HDMI_DDC_CTRL_SOFT_RESET;
		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL, reg_val);

		/* If previous msleep is पातed, skip this msleep */
		अगर (!rc)
			rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);

		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_CTRL);
		reg_val &= ~HDMI_DDC_CTRL_SOFT_RESET;
		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL, reg_val);
		DBG("After: HDMI_DDC_SW_STATUS=0x%08x",
			hdmi_पढ़ो(hdmi, REG_HDMI_DDC_SW_STATUS));
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_hw_ddc_clean(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc;
	u32 hdcp_ddc_status, ddc_hw_status;
	u32 xfer_करोne, xfer_req, hw_करोne;
	bool hw_not_पढ़ोy;
	u32 समयout_count;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;

	अगर (hdmi_पढ़ो(hdmi, REG_HDMI_DDC_HW_STATUS) == 0)
		वापस 0;

	/* Wait to be clean on DDC HW engine */
	समयout_count = 100;
	करो अणु
		hdcp_ddc_status = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_DDC_STATUS);
		ddc_hw_status = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_HW_STATUS);

		xfer_करोne = hdcp_ddc_status & HDMI_HDCP_DDC_STATUS_XFER_DONE;
		xfer_req = hdcp_ddc_status & HDMI_HDCP_DDC_STATUS_XFER_REQ;
		hw_करोne = ddc_hw_status & HDMI_DDC_HW_STATUS_DONE;
		hw_not_पढ़ोy = !xfer_करोne || xfer_req || !hw_करोne;

		अगर (hw_not_पढ़ोy)
			अवरोध;

		समयout_count--;
		अगर (!समयout_count) अणु
			pr_warn("%s: hw_ddc_clean failed\n", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल व्योम msm_hdmi_hdcp_reauth_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl = container_of(work,
		काष्ठा hdmi_hdcp_ctrl, hdcp_reauth_work);
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	अचिन्हित दीर्घ flags;
	u32 reg_val;

	DBG("HDCP REAUTH WORK");
	/*
	 * Disable HPD circuitry.
	 * This is needed to reset the HDCP cipher engine so that when we
	 * attempt a re-authentication, HW would clear the AN0_READY and
	 * AN1_READY bits in HDMI_HDCP_LINK0_STATUS रेजिस्टर
	 */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_CTRL);
	reg_val &= ~HDMI_HPD_CTRL_ENABLE;
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_CTRL, reg_val);

	/* Disable HDCP पूर्णांकerrupts */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_INT_CTRL, 0);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_RESET,
		HDMI_HDCP_RESET_LINK0_DEAUTHENTICATE);

	/* Wait to be clean on DDC HW engine */
	अगर (msm_hdmi_hdcp_hw_ddc_clean(hdcp_ctrl)) अणु
		pr_info("%s: reauth work aborted\n", __func__);
		वापस;
	पूर्ण

	/* Disable encryption and disable the HDCP block */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_CTRL, 0);

	/* Enable HPD circuitry */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_CTRL);
	reg_val |= HDMI_HPD_CTRL_ENABLE;
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	/*
	 * Only retry defined बार then पात current authenticating process
	 */
	अगर (++hdcp_ctrl->auth_retries == AUTH_RETRIES_TIME) अणु
		hdcp_ctrl->hdcp_state = HDCP_STATE_INACTIVE;
		hdcp_ctrl->auth_retries = 0;
		pr_info("%s: abort reauthentication!\n", __func__);

		वापस;
	पूर्ण

	DBG("Queue AUTH WORK");
	hdcp_ctrl->hdcp_state = HDCP_STATE_AUTHENTICATING;
	queue_work(hdmi->workq, &hdcp_ctrl->hdcp_auth_work);
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_auth_prepare(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 link0_status;
	u32 reg_val;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	अगर (!hdcp_ctrl->aksv_valid) अणु
		rc = msm_hdmi_hdcp_पढ़ो_validate_aksv(hdcp_ctrl);
		अगर (rc) अणु
			pr_err("%s: ASKV validation failed\n", __func__);
			hdcp_ctrl->hdcp_state = HDCP_STATE_NO_AKSV;
			वापस -ENOTSUPP;
		पूर्ण
		hdcp_ctrl->aksv_valid = true;
	पूर्ण

	spin_lock_irqsave(&hdmi->reg_lock, flags);
	/* disable HDMI Encrypt */
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_CTRL);
	reg_val &= ~HDMI_CTRL_ENCRYPTED;
	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, reg_val);

	/* Enabling Software DDC */
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_ARBITRATION);
	reg_val &= ~HDMI_DDC_ARBITRATION_HW_ARBITRATION;
	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_ARBITRATION, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	/*
	 * Write AKSV पढ़ो from QFPROM to the HDCP रेजिस्टरs.
	 * This step is needed क्रम HDCP authentication and must be
	 * written beक्रमe enabling HDCP.
	 */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_SW_LOWER_AKSV, hdcp_ctrl->aksv_lsb);
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_SW_UPPER_AKSV, hdcp_ctrl->aksv_msb);

	/*
	 * HDCP setup prior to enabling HDCP_CTRL.
	 * Setup seed values क्रम अक्रमom number An.
	 */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_ENTROPY_CTRL0, 0xB1FFB0FF);
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_ENTROPY_CTRL1, 0xF00DFACE);

	/* Disable the RngCipher state */
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_DEBUG_CTRL);
	reg_val &= ~HDMI_HDCP_DEBUG_CTRL_RNG_CIPHER;
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_DEBUG_CTRL, reg_val);
	DBG("HDCP_DEBUG_CTRL=0x%08x",
		hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_DEBUG_CTRL));

	/*
	 * Ensure that all रेजिस्टर ग_लिखोs are completed beक्रमe
	 * enabling HDCP cipher
	 */
	wmb();

	/*
	 * Enable HDCP
	 * This needs to be करोne as early as possible in order क्रम the
	 * hardware to make An available to पढ़ो
	 */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_CTRL, HDMI_HDCP_CTRL_ENABLE);

	/*
	 * If we had stale values क्रम the An पढ़ोy bit, it should most
	 * likely be cleared now after enabling HDCP cipher
	 */
	link0_status = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_LINK0_STATUS);
	DBG("After enabling HDCP Link0_Status=0x%08x", link0_status);
	अगर (!(link0_status &
		(HDMI_HDCP_LINK0_STATUS_AN_0_READY |
		HDMI_HDCP_LINK0_STATUS_AN_1_READY)))
		DBG("An not ready after enabling HDCP");

	/* Clear any DDC failures from previous tries beक्रमe enable HDCP*/
	rc = msm_reset_hdcp_ddc_failures(hdcp_ctrl);

	वापस rc;
पूर्ण

अटल व्योम msm_hdmi_hdcp_auth_fail(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg_val;
	अचिन्हित दीर्घ flags;

	DBG("hdcp auth failed, queue reauth work");
	/* clear HDMI Encrypt */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_CTRL);
	reg_val &= ~HDMI_CTRL_ENCRYPTED;
	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	hdcp_ctrl->hdcp_state = HDCP_STATE_AUTH_FAILED;
	queue_work(hdmi->workq, &hdcp_ctrl->hdcp_reauth_work);
पूर्ण

अटल व्योम msm_hdmi_hdcp_auth_करोne(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg_val;
	अचिन्हित दीर्घ flags;

	/*
	 * Disable software DDC beक्रमe going पूर्णांकo part3 to make sure
	 * there is no Arbitration between software and hardware क्रम DDC
	 */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_ARBITRATION);
	reg_val |= HDMI_DDC_ARBITRATION_HW_ARBITRATION;
	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_ARBITRATION, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	/* enable HDMI Encrypt */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_CTRL);
	reg_val |= HDMI_CTRL_ENCRYPTED;
	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	hdcp_ctrl->hdcp_state = HDCP_STATE_AUTHENTICATED;
	hdcp_ctrl->auth_retries = 0;
पूर्ण

/*
 * hdcp authenticating part 1
 * Wait Key/An पढ़ोy
 * Read BCAPS from sink
 * Write BCAPS and AKSV पूर्णांकo HDCP engine
 * Write An and AKSV to sink
 * Read BKSV from sink and ग_लिखो पूर्णांकo HDCP engine
 */
अटल पूर्णांक msm_hdmi_hdcp_रुको_key_an_पढ़ोy(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 link0_status, keys_state;
	u32 समयout_count;
	bool an_पढ़ोy;

	/* Wait क्रम HDCP keys to be checked and validated */
	समयout_count = 100;
	करो अणु
		link0_status = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_LINK0_STATUS);
		keys_state = (link0_status >> 28) & 0x7;
		अगर (keys_state == HDCP_KEYS_STATE_VALID)
			अवरोध;

		DBG("Keys not ready(%d). s=%d, l0=%0x08x",
			समयout_count, keys_state, link0_status);

		समयout_count--;
		अगर (!समयout_count) अणु
			pr_err("%s: Wait key state timedout", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	समयout_count = 100;
	करो अणु
		link0_status = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_LINK0_STATUS);
		an_पढ़ोy = (link0_status & HDMI_HDCP_LINK0_STATUS_AN_0_READY)
			&& (link0_status & HDMI_HDCP_LINK0_STATUS_AN_1_READY);
		अगर (an_पढ़ोy)
			अवरोध;

		DBG("An not ready(%d). l0_status=0x%08x",
			समयout_count, link0_status);

		समयout_count--;
		अगर (!समयout_count) अणु
			pr_err("%s: Wait An timedout", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_send_aksv_an(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc = 0;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 link0_aksv_0, link0_aksv_1;
	u32 link0_an[2];
	u8 aksv[5];

	/* Read An0 and An1 */
	link0_an[0] = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_RCVPORT_DATA5);
	link0_an[1] = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_RCVPORT_DATA6);

	/* Read AKSV */
	link0_aksv_0 = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_RCVPORT_DATA3);
	link0_aksv_1 = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_RCVPORT_DATA4);

	DBG("Link ASKV=%08x%08x", link0_aksv_0, link0_aksv_1);
	/* Copy An and AKSV to byte arrays क्रम transmission */
	aksv[0] =  link0_aksv_0        & 0xFF;
	aksv[1] = (link0_aksv_0 >> 8)  & 0xFF;
	aksv[2] = (link0_aksv_0 >> 16) & 0xFF;
	aksv[3] = (link0_aksv_0 >> 24) & 0xFF;
	aksv[4] =  link0_aksv_1        & 0xFF;

	/* Write An to offset 0x18 */
	rc = msm_hdmi_ddc_ग_लिखो(hdmi, HDCP_PORT_ADDR, 0x18, (u8 *)link0_an,
		(u16)माप(link0_an));
	अगर (rc) अणु
		pr_err("%s:An write failed\n", __func__);
		वापस rc;
	पूर्ण
	DBG("Link0-An=%08x%08x", link0_an[0], link0_an[1]);

	/* Write AKSV to offset 0x10 */
	rc = msm_hdmi_ddc_ग_लिखो(hdmi, HDCP_PORT_ADDR, 0x10, aksv, 5);
	अगर (rc) अणु
		pr_err("%s:AKSV write failed\n", __func__);
		वापस rc;
	पूर्ण
	DBG("Link0-AKSV=%02x%08x", link0_aksv_1 & 0xFF, link0_aksv_0);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_recv_bksv(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc = 0;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u8 bksv[5];
	u32 reg[2], data[2];

	/* Read BKSV at offset 0x00 */
	rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR, 0x00, bksv, 5);
	अगर (rc) अणु
		pr_err("%s:BKSV read failed\n", __func__);
		वापस rc;
	पूर्ण

	hdcp_ctrl->bksv_lsb = bksv[0] | (bksv[1] << 8) |
		(bksv[2] << 16) | (bksv[3] << 24);
	hdcp_ctrl->bksv_msb = bksv[4];
	DBG(":BKSV=%02x%08x", hdcp_ctrl->bksv_msb, hdcp_ctrl->bksv_lsb);

	/* check there are 20 ones in BKSV */
	अगर ((hweight32(hdcp_ctrl->bksv_lsb) + hweight32(hdcp_ctrl->bksv_msb))
			!= 20) अणु
		pr_err(": BKSV doesn't have 20 1's and 20 0's\n");
		pr_err(": BKSV chk fail. BKSV=%02x%02x%02x%02x%02x\n",
			bksv[4], bksv[3], bksv[2], bksv[1], bksv[0]);
		वापस -EINVAL;
	पूर्ण

	/* Write BKSV पढ़ो from sink to HDCP रेजिस्टरs */
	reg[0] = REG_HDMI_HDCP_RCVPORT_DATA0;
	data[0] = hdcp_ctrl->bksv_lsb;
	reg[1] = REG_HDMI_HDCP_RCVPORT_DATA1;
	data[1] = hdcp_ctrl->bksv_msb;
	rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, reg, data, 2);

	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_recv_bcaps(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc = 0;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg, data;
	u8 bcaps;

	rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR, 0x40, &bcaps, 1);
	अगर (rc) अणु
		pr_err("%s:BCAPS read failed\n", __func__);
		वापस rc;
	पूर्ण
	DBG("BCAPS=%02x", bcaps);

	/* receiver (0), repeater (1) */
	hdcp_ctrl->ds_type = (bcaps & BIT(6)) ? DS_REPEATER : DS_RECEIVER;

	/* Write BCAPS to the hardware */
	reg = REG_HDMI_HDCP_RCVPORT_DATA12;
	data = (u32)bcaps;
	rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, &reg, &data, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_auth_part1_key_exchange(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	अचिन्हित दीर्घ flags;
	पूर्णांक rc;

	/* Wait क्रम AKSV key and An पढ़ोy */
	rc = msm_hdmi_hdcp_रुको_key_an_पढ़ोy(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: wait key and an ready failed\n", __func__);
		वापस rc;
	पूर्ण

	/* Read BCAPS and send to HDCP engine */
	rc = msm_hdmi_hdcp_recv_bcaps(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: read bcaps error, abort\n", __func__);
		वापस rc;
	पूर्ण

	/*
	 * 1.1_Features turned off by शेष.
	 * No need to ग_लिखो AInfo since 1.1_Features is disabled.
	 */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_RCVPORT_DATA4, 0);

	/* Send AKSV and An to sink */
	rc = msm_hdmi_hdcp_send_aksv_an(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s:An/Aksv write failed\n", __func__);
		वापस rc;
	पूर्ण

	/* Read BKSV and send to HDCP engine*/
	rc = msm_hdmi_hdcp_recv_bksv(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s:BKSV Process failed\n", __func__);
		वापस rc;
	पूर्ण

	/* Enable HDCP पूर्णांकerrupts and ack/clear any stale पूर्णांकerrupts */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_INT_CTRL,
		HDMI_HDCP_INT_CTRL_AUTH_SUCCESS_ACK |
		HDMI_HDCP_INT_CTRL_AUTH_SUCCESS_MASK |
		HDMI_HDCP_INT_CTRL_AUTH_FAIL_ACK |
		HDMI_HDCP_INT_CTRL_AUTH_FAIL_MASK |
		HDMI_HDCP_INT_CTRL_AUTH_FAIL_INFO_ACK);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	वापस 0;
पूर्ण

/* पढ़ो R0' from sink and pass it to HDCP engine */
अटल पूर्णांक msm_hdmi_hdcp_auth_part1_recv_r0(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	पूर्णांक rc = 0;
	u8 buf[2];

	/*
	 * HDCP Compliance Test हाल 1A-01:
	 * Wait here at least 100ms beक्रमe पढ़ोing R0'
	 */
	rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 125, AUTH_ABORT_EV);
	अगर (rc)
		वापस rc;

	/* Read R0' at offset 0x08 */
	rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR, 0x08, buf, 2);
	अगर (rc) अणु
		pr_err("%s:R0' read failed\n", __func__);
		वापस rc;
	पूर्ण
	DBG("R0'=%02x%02x", buf[1], buf[0]);

	/* Write R0' to HDCP रेजिस्टरs and check to see अगर it is a match */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_RCVPORT_DATA2_0,
		(((u32)buf[1]) << 8) | buf[0]);

	वापस 0;
पूर्ण

/* Wait क्रम authenticating result: R0/R0' are matched or not */
अटल पूर्णांक msm_hdmi_hdcp_auth_part1_verअगरy_r0(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 link0_status;
	पूर्णांक rc;

	/* रुको क्रम hdcp irq, 10 sec should be दीर्घ enough */
	rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 10000, AUTH_RESULT_RDY_EV);
	अगर (!rc) अणु
		pr_err("%s: Wait Auth IRQ timeout\n", __func__);
		वापस -ETIMEDOUT;
	पूर्ण

	link0_status = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_LINK0_STATUS);
	अगर (!(link0_status & HDMI_HDCP_LINK0_STATUS_RI_MATCHES)) अणु
		pr_err("%s: Authentication Part I failed\n", __func__);
		वापस -EINVAL;
	पूर्ण

	/* Enable HDCP Encryption */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_CTRL,
		HDMI_HDCP_CTRL_ENABLE |
		HDMI_HDCP_CTRL_ENCRYPTION_ENABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_recv_check_bstatus(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl,
	u16 *pbstatus)
अणु
	पूर्णांक rc;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	bool max_devs_exceeded = false, max_cascade_exceeded = false;
	u32 repeater_cascade_depth = 0, करोwn_stream_devices = 0;
	u16 bstatus;
	u8 buf[2];

	/* Read BSTATUS at offset 0x41 */
	rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR, 0x41, buf, 2);
	अगर (rc) अणु
		pr_err("%s: BSTATUS read failed\n", __func__);
		जाओ error;
	पूर्ण
	*pbstatus = bstatus = (buf[1] << 8) | buf[0];


	करोwn_stream_devices = bstatus & 0x7F;
	repeater_cascade_depth = (bstatus >> 8) & 0x7;
	max_devs_exceeded = (bstatus & BIT(7)) ? true : false;
	max_cascade_exceeded = (bstatus & BIT(11)) ? true : false;

	अगर (करोwn_stream_devices == 0) अणु
		/*
		 * If no करोwnstream devices are attached to the repeater
		 * then part II fails.
		 * toकरो: The other approach would be to जारी PART II.
		 */
		pr_err("%s: No downstream devices\n", __func__);
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * HDCP Compliance 1B-05:
	 * Check अगर no. of devices connected to repeater
	 * exceed max_devices_connected from bit 7 of Bstatus.
	 */
	अगर (max_devs_exceeded) अणु
		pr_err("%s: no. of devs connected exceeds max allowed",
			__func__);
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	/*
	 * HDCP Compliance 1B-06:
	 * Check अगर no. of cascade connected to repeater
	 * exceed max_cascade_connected from bit 11 of Bstatus.
	 */
	अगर (max_cascade_exceeded) अणु
		pr_err("%s: no. of cascade conn exceeds max allowed",
			__func__);
		rc = -EINVAL;
		जाओ error;
	पूर्ण

error:
	hdcp_ctrl->dev_count = करोwn_stream_devices;
	hdcp_ctrl->max_cascade_exceeded = max_cascade_exceeded;
	hdcp_ctrl->max_dev_exceeded = max_devs_exceeded;
	hdcp_ctrl->depth = repeater_cascade_depth;
	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_auth_part2_रुको_ksv_fअगरo_पढ़ोy(
	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg, data;
	u32 समयout_count;
	u16 bstatus;
	u8 bcaps;

	/*
	 * Wait until READY bit is set in BCAPS, as per HDCP specअगरications
	 * maximum permitted समय to check क्रम READY bit is five seconds.
	 */
	समयout_count = 100;
	करो अणु
		/* Read BCAPS at offset 0x40 */
		rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR, 0x40, &bcaps, 1);
		अगर (rc) अणु
			pr_err("%s: BCAPS read failed\n", __func__);
			वापस rc;
		पूर्ण

		अगर (bcaps & BIT(5))
			अवरोध;

		समयout_count--;
		अगर (!समयout_count) अणु
			pr_err("%s: Wait KSV fifo ready timedout", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	rc = msm_hdmi_hdcp_recv_check_bstatus(hdcp_ctrl, &bstatus);
	अगर (rc) अणु
		pr_err("%s: bstatus error\n", __func__);
		वापस rc;
	पूर्ण

	/* Write BSTATUS and BCAPS to HDCP रेजिस्टरs */
	reg = REG_HDMI_HDCP_RCVPORT_DATA12;
	data = bcaps | (bstatus << 8);
	rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, &reg, &data, 1);
	अगर (rc) अणु
		pr_err("%s: BSTATUS write failed\n", __func__);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * hdcp authenticating part 2: 2nd
 * पढ़ो ksv fअगरo from sink
 * transfer V' from sink to HDCP engine
 * reset SHA engine
 */
अटल पूर्णांक msm_hdmi_hdcp_transfer_v_h(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	पूर्णांक rc = 0;
	काष्ठा hdmi_hdcp_reg_data reg_data[]  = अणु
		अणुREG_HDMI_HDCP_RCVPORT_DATA7,  0x20, "V' H0"पूर्ण,
		अणुREG_HDMI_HDCP_RCVPORT_DATA8,  0x24, "V' H1"पूर्ण,
		अणुREG_HDMI_HDCP_RCVPORT_DATA9,  0x28, "V' H2"पूर्ण,
		अणुREG_HDMI_HDCP_RCVPORT_DATA10, 0x2C, "V' H3"पूर्ण,
		अणुREG_HDMI_HDCP_RCVPORT_DATA11, 0x30, "V' H4"पूर्ण,
	पूर्ण;
	काष्ठा hdmi_hdcp_reg_data *rd;
	u32 size = ARRAY_SIZE(reg_data);
	u32 reg[ARRAY_SIZE(reg_data)];
	u32 data[ARRAY_SIZE(reg_data)];
	पूर्णांक i;

	क्रम (i = 0; i < size; i++) अणु
		rd = &reg_data[i];
		rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR,
			rd->off, (u8 *)&data[i], (u16)माप(data[i]));
		अगर (rc) अणु
			pr_err("%s: Read %s failed\n", __func__, rd->name);
			जाओ error;
		पूर्ण

		DBG("%s =%x", rd->name, data[i]);
		reg[i] = reg_data[i].reg_id;
	पूर्ण

	rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, reg, data, size);

error:
	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_recv_ksv_fअगरo(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 ksv_bytes;

	ksv_bytes = 5 * hdcp_ctrl->dev_count;

	rc = msm_hdmi_ddc_पढ़ो(hdmi, HDCP_PORT_ADDR, 0x43,
		hdcp_ctrl->ksv_list, ksv_bytes);
	अगर (rc)
		pr_err("%s: KSV FIFO read failed\n", __func__);

	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_reset_sha_engine(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	u32 reg[2], data[2];
	u32 rc  = 0;

	reg[0] = REG_HDMI_HDCP_SHA_CTRL;
	data[0] = HDCP_REG_ENABLE;
	reg[1] = REG_HDMI_HDCP_SHA_CTRL;
	data[1] = HDCP_REG_DISABLE;

	rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, reg, data, 2);

	वापस rc;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_auth_part2_recv_ksv_fअगरo(
	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc;
	u32 समयout_count;

	/*
	 * Read KSV FIFO over DDC
	 * Key Selection vector FIFO Used to pull करोwnstream KSVs
	 * from HDCP Repeaters.
	 * All bytes (DEVICE_COUNT * 5) must be पढ़ो in a single,
	 * स्वतः incrementing access.
	 * All bytes पढ़ो as 0x00 क्रम HDCP Receivers that are not
	 * HDCP Repeaters (REPEATER == 0).
	 */
	समयout_count = 100;
	करो अणु
		rc = msm_hdmi_hdcp_recv_ksv_fअगरo(hdcp_ctrl);
		अगर (!rc)
			अवरोध;

		समयout_count--;
		अगर (!समयout_count) अणु
			pr_err("%s: Recv ksv fifo timedout", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 25, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	rc = msm_hdmi_hdcp_transfer_v_h(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: transfer V failed\n", __func__);
		वापस rc;
	पूर्ण

	/* reset SHA engine beक्रमe ग_लिखो ksv fअगरo */
	rc = msm_hdmi_hdcp_reset_sha_engine(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: fail to reset sha engine\n", __func__);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Write KSV FIFO to HDCP_SHA_DATA.
 * This is करोne 1 byte at समय starting with the LSB.
 * Once 64 bytes have been written, we need to poll क्रम
 * HDCP_SHA_BLOCK_DONE beक्रमe writing any further
 * If the last byte is written, we need to poll क्रम
 * HDCP_SHA_COMP_DONE to रुको until HW finish
 */
अटल पूर्णांक msm_hdmi_hdcp_ग_लिखो_ksv_fअगरo(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक i;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 ksv_bytes, last_byte = 0;
	u8 *ksv_fअगरo = शून्य;
	u32 reg_val, data, reg;
	u32 rc  = 0;

	ksv_bytes  = 5 * hdcp_ctrl->dev_count;

	/* Check अगर need to रुको क्रम HW completion */
	अगर (hdcp_ctrl->ksv_fअगरo_w_index) अणु
		reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_SHA_STATUS);
		DBG("HDCP_SHA_STATUS=%08x", reg_val);
		अगर (hdcp_ctrl->ksv_fअगरo_w_index == ksv_bytes) अणु
			/* check COMP_DONE अगर last ग_लिखो */
			अगर (reg_val & HDMI_HDCP_SHA_STATUS_COMP_DONE) अणु
				DBG("COMP_DONE");
				वापस 0;
			पूर्ण अन्यथा अणु
				वापस -EAGAIN;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* check BLOCK_DONE अगर not last ग_लिखो */
			अगर (!(reg_val & HDMI_HDCP_SHA_STATUS_BLOCK_DONE))
				वापस -EAGAIN;

			DBG("BLOCK_DONE");
		पूर्ण
	पूर्ण

	ksv_bytes  -= hdcp_ctrl->ksv_fअगरo_w_index;
	अगर (ksv_bytes <= 64)
		last_byte = 1;
	अन्यथा
		ksv_bytes = 64;

	ksv_fअगरo = hdcp_ctrl->ksv_list;
	ksv_fअगरo += hdcp_ctrl->ksv_fअगरo_w_index;

	क्रम (i = 0; i < ksv_bytes; i++) अणु
		/* Write KSV byte and set DONE bit[0] क्रम last byte*/
		reg_val = ksv_fअगरo[i] << 16;
		अगर ((i == (ksv_bytes - 1)) && last_byte)
			reg_val |= HDMI_HDCP_SHA_DATA_DONE;

		reg = REG_HDMI_HDCP_SHA_DATA;
		data = reg_val;
		rc = msm_hdmi_hdcp_scm_wr(hdcp_ctrl, &reg, &data, 1);

		अगर (rc)
			वापस rc;
	पूर्ण

	hdcp_ctrl->ksv_fअगरo_w_index += ksv_bytes;

	/*
	 *वापस -EAGAIN to notअगरy caller to रुको क्रम COMP_DONE or BLOCK_DONE
	 */
	वापस -EAGAIN;
पूर्ण

/* ग_लिखो ksv fअगरo पूर्णांकo HDCP engine */
अटल पूर्णांक msm_hdmi_hdcp_auth_part2_ग_लिखो_ksv_fअगरo(
	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc;
	u32 समयout_count;

	hdcp_ctrl->ksv_fअगरo_w_index = 0;
	समयout_count = 100;
	करो अणु
		rc = msm_hdmi_hdcp_ग_लिखो_ksv_fअगरo(hdcp_ctrl);
		अगर (!rc)
			अवरोध;

		अगर (rc != -EAGAIN)
			वापस rc;

		समयout_count--;
		अगर (!समयout_count) अणु
			pr_err("%s: Write KSV fifo timedout", __func__);
			वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल पूर्णांक msm_hdmi_hdcp_auth_part2_check_v_match(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	पूर्णांक rc = 0;
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 link0_status;
	u32 समयout_count = 100;

	करो अणु
		link0_status = hdmi_पढ़ो(hdmi, REG_HDMI_HDCP_LINK0_STATUS);
		अगर (link0_status & HDMI_HDCP_LINK0_STATUS_V_MATCHES)
			अवरोध;

		समयout_count--;
		अगर (!समयout_count) अणु
				pr_err("%s: HDCP V Match timedout", __func__);
				वापस -ETIMEDOUT;
		पूर्ण

		rc = msm_hdmi_hdcp_msleep(hdcp_ctrl, 20, AUTH_ABORT_EV);
		अगर (rc)
			वापस rc;
	पूर्ण जबतक (1);

	वापस 0;
पूर्ण

अटल व्योम msm_hdmi_hdcp_auth_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl = container_of(work,
		काष्ठा hdmi_hdcp_ctrl, hdcp_auth_work);
	पूर्णांक rc;

	rc = msm_hdmi_hdcp_auth_prepare(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: auth prepare failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण

	/* HDCP PartI */
	rc = msm_hdmi_hdcp_auth_part1_key_exchange(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: key exchange failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण

	rc = msm_hdmi_hdcp_auth_part1_recv_r0(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: receive r0 failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण

	rc = msm_hdmi_hdcp_auth_part1_verअगरy_r0(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: verify r0 failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण
	pr_info("%s: Authentication Part I successful\n", __func__);
	अगर (hdcp_ctrl->ds_type == DS_RECEIVER)
		जाओ end;

	/* HDCP PartII */
	rc = msm_hdmi_hdcp_auth_part2_रुको_ksv_fअगरo_पढ़ोy(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: wait ksv fifo ready failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण

	rc = msm_hdmi_hdcp_auth_part2_recv_ksv_fअगरo(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: recv ksv fifo failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण

	rc = msm_hdmi_hdcp_auth_part2_ग_लिखो_ksv_fअगरo(hdcp_ctrl);
	अगर (rc) अणु
		pr_err("%s: write ksv fifo failed %d\n", __func__, rc);
		जाओ end;
	पूर्ण

	rc = msm_hdmi_hdcp_auth_part2_check_v_match(hdcp_ctrl);
	अगर (rc)
		pr_err("%s: check v match failed %d\n", __func__, rc);

end:
	अगर (rc == -ECANCELED) अणु
		pr_info("%s: hdcp authentication canceled\n", __func__);
	पूर्ण अन्यथा अगर (rc == -ENOTSUPP) अणु
		pr_info("%s: hdcp is not supported\n", __func__);
	पूर्ण अन्यथा अगर (rc) अणु
		pr_err("%s: hdcp authentication failed\n", __func__);
		msm_hdmi_hdcp_auth_fail(hdcp_ctrl);
	पूर्ण अन्यथा अणु
		msm_hdmi_hdcp_auth_करोne(hdcp_ctrl);
	पूर्ण
पूर्ण

व्योम msm_hdmi_hdcp_on(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	u32 reg_val;
	अचिन्हित दीर्घ flags;

	अगर ((HDCP_STATE_INACTIVE != hdcp_ctrl->hdcp_state) ||
		(HDCP_STATE_NO_AKSV == hdcp_ctrl->hdcp_state)) अणु
		DBG("still active or activating or no askv. returning");
		वापस;
	पूर्ण

	/* clear HDMI Encrypt */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_CTRL);
	reg_val &= ~HDMI_CTRL_ENCRYPTED;
	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	hdcp_ctrl->auth_event = 0;
	hdcp_ctrl->hdcp_state = HDCP_STATE_AUTHENTICATING;
	hdcp_ctrl->auth_retries = 0;
	queue_work(hdmi->workq, &hdcp_ctrl->hdcp_auth_work);
पूर्ण

व्योम msm_hdmi_hdcp_off(काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl)
अणु
	काष्ठा hdmi *hdmi = hdcp_ctrl->hdmi;
	अचिन्हित दीर्घ flags;
	u32 reg_val;

	अगर ((HDCP_STATE_INACTIVE == hdcp_ctrl->hdcp_state) ||
		(HDCP_STATE_NO_AKSV == hdcp_ctrl->hdcp_state)) अणु
		DBG("hdcp inactive or no aksv. returning");
		वापस;
	पूर्ण

	/*
	 * Disable HPD circuitry.
	 * This is needed to reset the HDCP cipher engine so that when we
	 * attempt a re-authentication, HW would clear the AN0_READY and
	 * AN1_READY bits in HDMI_HDCP_LINK0_STATUS रेजिस्टर
	 */
	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_CTRL);
	reg_val &= ~HDMI_HPD_CTRL_ENABLE;
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_CTRL, reg_val);

	/*
	 * Disable HDCP पूर्णांकerrupts.
	 * Also, need to set the state to inactive here so that any ongoing
	 * reauth works will know that the HDCP session has been turned off.
	 */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_INT_CTRL, 0);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	/*
	 * Cancel any pending auth/reauth attempts.
	 * If one is ongoing, this will रुको क्रम it to finish.
	 * No more reauthentication attempts will be scheduled since we
	 * set the current state to inactive.
	 */
	set_bit(AUTH_ABORT_EV, &hdcp_ctrl->auth_event);
	wake_up_all(&hdcp_ctrl->auth_event_queue);
	cancel_work_sync(&hdcp_ctrl->hdcp_auth_work);
	cancel_work_sync(&hdcp_ctrl->hdcp_reauth_work);

	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_RESET,
		HDMI_HDCP_RESET_LINK0_DEAUTHENTICATE);

	/* Disable encryption and disable the HDCP block */
	hdmi_ग_लिखो(hdmi, REG_HDMI_HDCP_CTRL, 0);

	spin_lock_irqsave(&hdmi->reg_lock, flags);
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_CTRL);
	reg_val &= ~HDMI_CTRL_ENCRYPTED;
	hdmi_ग_लिखो(hdmi, REG_HDMI_CTRL, reg_val);

	/* Enable HPD circuitry */
	reg_val = hdmi_पढ़ो(hdmi, REG_HDMI_HPD_CTRL);
	reg_val |= HDMI_HPD_CTRL_ENABLE;
	hdmi_ग_लिखो(hdmi, REG_HDMI_HPD_CTRL, reg_val);
	spin_unlock_irqrestore(&hdmi->reg_lock, flags);

	hdcp_ctrl->hdcp_state = HDCP_STATE_INACTIVE;

	DBG("HDCP: Off");
पूर्ण

काष्ठा hdmi_hdcp_ctrl *msm_hdmi_hdcp_init(काष्ठा hdmi *hdmi)
अणु
	काष्ठा hdmi_hdcp_ctrl *hdcp_ctrl = शून्य;

	अगर (!hdmi->qfprom_mmio) अणु
		pr_err("%s: HDCP is not supported without qfprom\n",
			__func__);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	hdcp_ctrl = kzalloc(माप(*hdcp_ctrl), GFP_KERNEL);
	अगर (!hdcp_ctrl)
		वापस ERR_PTR(-ENOMEM);

	INIT_WORK(&hdcp_ctrl->hdcp_auth_work, msm_hdmi_hdcp_auth_work);
	INIT_WORK(&hdcp_ctrl->hdcp_reauth_work, msm_hdmi_hdcp_reauth_work);
	init_रुकोqueue_head(&hdcp_ctrl->auth_event_queue);
	hdcp_ctrl->hdmi = hdmi;
	hdcp_ctrl->hdcp_state = HDCP_STATE_INACTIVE;
	hdcp_ctrl->aksv_valid = false;

	अगर (qcom_scm_hdcp_available())
		hdcp_ctrl->tz_hdcp = true;
	अन्यथा
		hdcp_ctrl->tz_hdcp = false;

	वापस hdcp_ctrl;
पूर्ण

व्योम msm_hdmi_hdcp_destroy(काष्ठा hdmi *hdmi)
अणु
	अगर (hdmi) अणु
		kमुक्त(hdmi->hdcp_ctrl);
		hdmi->hdcp_ctrl = शून्य;
	पूर्ण
पूर्ण
