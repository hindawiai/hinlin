<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश "hdmi.h"

काष्ठा hdmi_i2c_adapter अणु
	काष्ठा i2c_adapter base;
	काष्ठा hdmi *hdmi;
	bool sw_करोne;
	रुको_queue_head_t ddc_event;
पूर्ण;
#घोषणा to_hdmi_i2c_adapter(x) container_of(x, काष्ठा hdmi_i2c_adapter, base)

अटल व्योम init_ddc(काष्ठा hdmi_i2c_adapter *hdmi_i2c)
अणु
	काष्ठा hdmi *hdmi = hdmi_i2c->hdmi;

	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL,
			HDMI_DDC_CTRL_SW_STATUS_RESET);
	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL,
			HDMI_DDC_CTRL_SOFT_RESET);

	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_SPEED,
			HDMI_DDC_SPEED_THRESHOLD(2) |
			HDMI_DDC_SPEED_PRESCALE(10));

	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_SETUP,
			HDMI_DDC_SETUP_TIMEOUT(0xff));

	/* enable reference समयr क्रम 27us */
	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_REF,
			HDMI_DDC_REF_REFTIMER_ENABLE |
			HDMI_DDC_REF_REFTIMER(27));
पूर्ण

अटल पूर्णांक ddc_clear_irq(काष्ठा hdmi_i2c_adapter *hdmi_i2c)
अणु
	काष्ठा hdmi *hdmi = hdmi_i2c->hdmi;
	काष्ठा drm_device *dev = hdmi->dev;
	uपूर्णांक32_t retry = 0xffff;
	uपूर्णांक32_t ddc_पूर्णांक_ctrl;

	करो अणु
		--retry;

		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_INT_CTRL,
				HDMI_DDC_INT_CTRL_SW_DONE_ACK |
				HDMI_DDC_INT_CTRL_SW_DONE_MASK);

		ddc_पूर्णांक_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_INT_CTRL);

	पूर्ण जबतक ((ddc_पूर्णांक_ctrl & HDMI_DDC_INT_CTRL_SW_DONE_INT) && retry);

	अगर (!retry) अणु
		DRM_DEV_ERROR(dev->dev, "timeout waiting for DDC\n");
		वापस -ETIMEDOUT;
	पूर्ण

	hdmi_i2c->sw_करोne = false;

	वापस 0;
पूर्ण

#घोषणा MAX_TRANSACTIONS 4

अटल bool sw_करोne(काष्ठा hdmi_i2c_adapter *hdmi_i2c)
अणु
	काष्ठा hdmi *hdmi = hdmi_i2c->hdmi;

	अगर (!hdmi_i2c->sw_करोne) अणु
		uपूर्णांक32_t ddc_पूर्णांक_ctrl;

		ddc_पूर्णांक_ctrl = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_INT_CTRL);

		अगर ((ddc_पूर्णांक_ctrl & HDMI_DDC_INT_CTRL_SW_DONE_MASK) &&
				(ddc_पूर्णांक_ctrl & HDMI_DDC_INT_CTRL_SW_DONE_INT)) अणु
			hdmi_i2c->sw_करोne = true;
			hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_INT_CTRL,
					HDMI_DDC_INT_CTRL_SW_DONE_ACK);
		पूर्ण
	पूर्ण

	वापस hdmi_i2c->sw_करोne;
पूर्ण

अटल पूर्णांक msm_hdmi_i2c_xfer(काष्ठा i2c_adapter *i2c,
		काष्ठा i2c_msg *msgs, पूर्णांक num)
अणु
	काष्ठा hdmi_i2c_adapter *hdmi_i2c = to_hdmi_i2c_adapter(i2c);
	काष्ठा hdmi *hdmi = hdmi_i2c->hdmi;
	काष्ठा drm_device *dev = hdmi->dev;
	अटल स्थिर uपूर्णांक32_t nack[] = अणु
			HDMI_DDC_SW_STATUS_NACK0, HDMI_DDC_SW_STATUS_NACK1,
			HDMI_DDC_SW_STATUS_NACK2, HDMI_DDC_SW_STATUS_NACK3,
	पूर्ण;
	पूर्णांक indices[MAX_TRANSACTIONS];
	पूर्णांक ret, i, j, index = 0;
	uपूर्णांक32_t ddc_status, ddc_data, i2c_trans;

	num = min(num, MAX_TRANSACTIONS);

	WARN_ON(!(hdmi_पढ़ो(hdmi, REG_HDMI_CTRL) & HDMI_CTRL_ENABLE));

	अगर (num == 0)
		वापस num;

	init_ddc(hdmi_i2c);

	ret = ddc_clear_irq(hdmi_i2c);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < num; i++) अणु
		काष्ठा i2c_msg *p = &msgs[i];
		uपूर्णांक32_t raw_addr = p->addr << 1;

		अगर (p->flags & I2C_M_RD)
			raw_addr |= 1;

		ddc_data = HDMI_DDC_DATA_DATA(raw_addr) |
				HDMI_DDC_DATA_DATA_RW(DDC_WRITE);

		अगर (i == 0) अणु
			ddc_data |= HDMI_DDC_DATA_INDEX(0) |
					HDMI_DDC_DATA_INDEX_WRITE;
		पूर्ण

		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_DATA, ddc_data);
		index++;

		indices[i] = index;

		अगर (p->flags & I2C_M_RD) अणु
			index += p->len;
		पूर्ण अन्यथा अणु
			क्रम (j = 0; j < p->len; j++) अणु
				ddc_data = HDMI_DDC_DATA_DATA(p->buf[j]) |
						HDMI_DDC_DATA_DATA_RW(DDC_WRITE);
				hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_DATA, ddc_data);
				index++;
			पूर्ण
		पूर्ण

		i2c_trans = HDMI_I2C_TRANSACTION_REG_CNT(p->len) |
				HDMI_I2C_TRANSACTION_REG_RW(
						(p->flags & I2C_M_RD) ? DDC_READ : DDC_WRITE) |
				HDMI_I2C_TRANSACTION_REG_START;

		अगर (i == (num - 1))
			i2c_trans |= HDMI_I2C_TRANSACTION_REG_STOP;

		hdmi_ग_लिखो(hdmi, REG_HDMI_I2C_TRANSACTION(i), i2c_trans);
	पूर्ण

	/* trigger the transfer: */
	hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_CTRL,
			HDMI_DDC_CTRL_TRANSACTION_CNT(num - 1) |
			HDMI_DDC_CTRL_GO);

	ret = रुको_event_समयout(hdmi_i2c->ddc_event, sw_करोne(hdmi_i2c), HZ/4);
	अगर (ret <= 0) अणु
		अगर (ret == 0)
			ret = -ETIMEDOUT;
		dev_warn(dev->dev, "DDC timeout: %d\n", ret);
		DBG("sw_status=%08x, hw_status=%08x, int_ctrl=%08x",
				hdmi_पढ़ो(hdmi, REG_HDMI_DDC_SW_STATUS),
				hdmi_पढ़ो(hdmi, REG_HDMI_DDC_HW_STATUS),
				hdmi_पढ़ो(hdmi, REG_HDMI_DDC_INT_CTRL));
		वापस ret;
	पूर्ण

	ddc_status = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_SW_STATUS);

	/* पढ़ो back results of any पढ़ो transactions: */
	क्रम (i = 0; i < num; i++) अणु
		काष्ठा i2c_msg *p = &msgs[i];

		अगर (!(p->flags & I2C_M_RD))
			जारी;

		/* check क्रम NACK: */
		अगर (ddc_status & nack[i]) अणु
			DBG("ddc_status=%08x", ddc_status);
			अवरोध;
		पूर्ण

		ddc_data = HDMI_DDC_DATA_DATA_RW(DDC_READ) |
				HDMI_DDC_DATA_INDEX(indices[i]) |
				HDMI_DDC_DATA_INDEX_WRITE;

		hdmi_ग_लिखो(hdmi, REG_HDMI_DDC_DATA, ddc_data);

		/* discard first byte: */
		hdmi_पढ़ो(hdmi, REG_HDMI_DDC_DATA);

		क्रम (j = 0; j < p->len; j++) अणु
			ddc_data = hdmi_पढ़ो(hdmi, REG_HDMI_DDC_DATA);
			p->buf[j] = FIELD(ddc_data, HDMI_DDC_DATA_DATA);
		पूर्ण
	पूर्ण

	वापस i;
पूर्ण

अटल u32 msm_hdmi_i2c_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_I2C | I2C_FUNC_SMBUS_EMUL;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm msm_hdmi_i2c_algorithm = अणु
	.master_xfer	= msm_hdmi_i2c_xfer,
	.functionality	= msm_hdmi_i2c_func,
पूर्ण;

व्योम msm_hdmi_i2c_irq(काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा hdmi_i2c_adapter *hdmi_i2c = to_hdmi_i2c_adapter(i2c);

	अगर (sw_करोne(hdmi_i2c))
		wake_up_all(&hdmi_i2c->ddc_event);
पूर्ण

व्योम msm_hdmi_i2c_destroy(काष्ठा i2c_adapter *i2c)
अणु
	काष्ठा hdmi_i2c_adapter *hdmi_i2c = to_hdmi_i2c_adapter(i2c);
	i2c_del_adapter(i2c);
	kमुक्त(hdmi_i2c);
पूर्ण

काष्ठा i2c_adapter *msm_hdmi_i2c_init(काष्ठा hdmi *hdmi)
अणु
	काष्ठा hdmi_i2c_adapter *hdmi_i2c;
	काष्ठा i2c_adapter *i2c = शून्य;
	पूर्णांक ret;

	hdmi_i2c = kzalloc(माप(*hdmi_i2c), GFP_KERNEL);
	अगर (!hdmi_i2c) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	i2c = &hdmi_i2c->base;

	hdmi_i2c->hdmi = hdmi;
	init_रुकोqueue_head(&hdmi_i2c->ddc_event);


	i2c->owner = THIS_MODULE;
	i2c->class = I2C_CLASS_DDC;
	snम_लिखो(i2c->name, माप(i2c->name), "msm hdmi i2c");
	i2c->dev.parent = &hdmi->pdev->dev;
	i2c->algo = &msm_hdmi_i2c_algorithm;

	ret = i2c_add_adapter(i2c);
	अगर (ret)
		जाओ fail;

	वापस i2c;

fail:
	अगर (i2c)
		msm_hdmi_i2c_destroy(i2c);
	वापस ERR_PTR(ret);
पूर्ण
