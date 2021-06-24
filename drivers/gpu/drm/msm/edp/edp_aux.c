<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014-2015, The Linux Foundation. All rights reserved.
 */

#समावेश "edp.h"
#समावेश "edp.xml.h"

#घोषणा AUX_CMD_FIFO_LEN	144
#घोषणा AUX_CMD_NATIVE_MAX	16
#घोषणा AUX_CMD_I2C_MAX		128

#घोषणा EDP_INTR_AUX_I2C_ERR	\
	(EDP_INTERRUPT_REG_1_WRONG_ADDR | EDP_INTERRUPT_REG_1_TIMEOUT | \
	EDP_INTERRUPT_REG_1_NACK_DEFER | EDP_INTERRUPT_REG_1_WRONG_DATA_CNT | \
	EDP_INTERRUPT_REG_1_I2C_NACK | EDP_INTERRUPT_REG_1_I2C_DEFER)
#घोषणा EDP_INTR_TRANS_STATUS	\
	(EDP_INTERRUPT_REG_1_AUX_I2C_DONE | EDP_INTR_AUX_I2C_ERR)

काष्ठा edp_aux अणु
	व्योम __iomem *base;
	bool msg_err;

	काष्ठा completion msg_comp;

	/* To prevent the message transaction routine from reentry. */
	काष्ठा mutex msg_mutex;

	काष्ठा drm_dp_aux drm_aux;
पूर्ण;
#घोषणा to_edp_aux(x) container_of(x, काष्ठा edp_aux, drm_aux)

अटल पूर्णांक edp_msg_fअगरo_tx(काष्ठा edp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	u32 data[4];
	u32 reg, len;
	bool native = msg->request & (DP_AUX_NATIVE_WRITE & DP_AUX_NATIVE_READ);
	bool पढ़ो = msg->request & (DP_AUX_I2C_READ & DP_AUX_NATIVE_READ);
	u8 *msgdata = msg->buffer;
	पूर्णांक i;

	अगर (पढ़ो)
		len = 4;
	अन्यथा
		len = msg->size + 4;

	/*
	 * cmd fअगरo only has depth of 144 bytes
	 */
	अगर (len > AUX_CMD_FIFO_LEN)
		वापस -EINVAL;

	/* Pack cmd and ग_लिखो to HW */
	data[0] = (msg->address >> 16) & 0xf;	/* addr[19:16] */
	अगर (पढ़ो)
		data[0] |=  BIT(4);		/* R/W */

	data[1] = (msg->address >> 8) & 0xff;	/* addr[15:8] */
	data[2] = msg->address & 0xff;		/* addr[7:0] */
	data[3] = (msg->size - 1) & 0xff;	/* len[7:0] */

	क्रम (i = 0; i < len; i++) अणु
		reg = (i < 4) ? data[i] : msgdata[i - 4];
		reg = EDP_AUX_DATA_DATA(reg); /* index = 0, ग_लिखो */
		अगर (i == 0)
			reg |= EDP_AUX_DATA_INDEX_WRITE;
		edp_ग_लिखो(aux->base + REG_EDP_AUX_DATA, reg);
	पूर्ण

	reg = 0; /* Transaction number is always 1 */
	अगर (!native) /* i2c */
		reg |= EDP_AUX_TRANS_CTRL_I2C;

	reg |= EDP_AUX_TRANS_CTRL_GO;
	edp_ग_लिखो(aux->base + REG_EDP_AUX_TRANS_CTRL, reg);

	वापस 0;
पूर्ण

अटल पूर्णांक edp_msg_fअगरo_rx(काष्ठा edp_aux *aux, काष्ठा drm_dp_aux_msg *msg)
अणु
	u32 data;
	u8 *dp;
	पूर्णांक i;
	u32 len = msg->size;

	edp_ग_लिखो(aux->base + REG_EDP_AUX_DATA,
		EDP_AUX_DATA_INDEX_WRITE | EDP_AUX_DATA_READ); /* index = 0 */

	dp = msg->buffer;

	/* discard first byte */
	data = edp_पढ़ो(aux->base + REG_EDP_AUX_DATA);
	क्रम (i = 0; i < len; i++) अणु
		data = edp_पढ़ो(aux->base + REG_EDP_AUX_DATA);
		dp[i] = (u8)((data >> 8) & 0xff);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function करोes the real job to process an AUX transaction.
 * It will call msm_edp_aux_ctrl() function to reset the AUX channel,
 * अगर the रुकोing is समयout.
 * The caller who triggers the transaction should aव्योम the
 * msm_edp_aux_ctrl() running concurrently in other thपढ़ोs, i.e.
 * start transaction only when AUX channel is fully enabled.
 */
अटल sमाप_प्रकार edp_aux_transfer(काष्ठा drm_dp_aux *drm_aux,
		काष्ठा drm_dp_aux_msg *msg)
अणु
	काष्ठा edp_aux *aux = to_edp_aux(drm_aux);
	sमाप_प्रकार ret;
	अचिन्हित दीर्घ समय_left;
	bool native = msg->request & (DP_AUX_NATIVE_WRITE & DP_AUX_NATIVE_READ);
	bool पढ़ो = msg->request & (DP_AUX_I2C_READ & DP_AUX_NATIVE_READ);

	/* Ignore address only message */
	अगर ((msg->size == 0) || (msg->buffer == शून्य)) अणु
		msg->reply = native ?
			DP_AUX_NATIVE_REPLY_ACK : DP_AUX_I2C_REPLY_ACK;
		वापस msg->size;
	पूर्ण

	/* msg sanity check */
	अगर ((native && (msg->size > AUX_CMD_NATIVE_MAX)) ||
		(msg->size > AUX_CMD_I2C_MAX)) अणु
		pr_err("%s: invalid msg: size(%zu), request(%x)\n",
			__func__, msg->size, msg->request);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&aux->msg_mutex);

	aux->msg_err = false;
	reinit_completion(&aux->msg_comp);

	ret = edp_msg_fअगरo_tx(aux, msg);
	अगर (ret < 0)
		जाओ unlock_निकास;

	DBG("wait_for_completion");
	समय_left = रुको_क्रम_completion_समयout(&aux->msg_comp,
						msecs_to_jअगरfies(300));
	अगर (!समय_left) अणु
		/*
		 * Clear GO and reset AUX channel
		 * to cancel the current transaction.
		 */
		edp_ग_लिखो(aux->base + REG_EDP_AUX_TRANS_CTRL, 0);
		msm_edp_aux_ctrl(aux, 1);
		pr_err("%s: aux timeout,\n", __func__);
		ret = -ETIMEDOUT;
		जाओ unlock_निकास;
	पूर्ण
	DBG("completion");

	अगर (!aux->msg_err) अणु
		अगर (पढ़ो) अणु
			ret = edp_msg_fअगरo_rx(aux, msg);
			अगर (ret < 0)
				जाओ unlock_निकास;
		पूर्ण

		msg->reply = native ?
			DP_AUX_NATIVE_REPLY_ACK : DP_AUX_I2C_REPLY_ACK;
	पूर्ण अन्यथा अणु
		/* Reply defer to retry */
		msg->reply = native ?
			DP_AUX_NATIVE_REPLY_DEFER : DP_AUX_I2C_REPLY_DEFER;
		/*
		 * The sleep समय in caller is not दीर्घ enough to make sure
		 * our H/W completes transactions. Add more defer समय here.
		 */
		msleep(100);
	पूर्ण

	/* Return requested size क्रम success or retry */
	ret = msg->size;

unlock_निकास:
	mutex_unlock(&aux->msg_mutex);
	वापस ret;
पूर्ण

व्योम *msm_edp_aux_init(काष्ठा device *dev, व्योम __iomem *regbase,
	काष्ठा drm_dp_aux **drm_aux)
अणु
	काष्ठा edp_aux *aux = शून्य;
	पूर्णांक ret;

	DBG("");
	aux = devm_kzalloc(dev, माप(*aux), GFP_KERNEL);
	अगर (!aux)
		वापस शून्य;

	aux->base = regbase;
	mutex_init(&aux->msg_mutex);
	init_completion(&aux->msg_comp);

	aux->drm_aux.name = "msm_edp_aux";
	aux->drm_aux.dev = dev;
	aux->drm_aux.transfer = edp_aux_transfer;
	ret = drm_dp_aux_रेजिस्टर(&aux->drm_aux);
	अगर (ret) अणु
		pr_err("%s: failed to register drm aux: %d\n", __func__, ret);
		mutex_destroy(&aux->msg_mutex);
	पूर्ण

	अगर (drm_aux && aux)
		*drm_aux = &aux->drm_aux;

	वापस aux;
पूर्ण

व्योम msm_edp_aux_destroy(काष्ठा device *dev, काष्ठा edp_aux *aux)
अणु
	अगर (aux) अणु
		drm_dp_aux_unरेजिस्टर(&aux->drm_aux);
		mutex_destroy(&aux->msg_mutex);
	पूर्ण
पूर्ण

irqवापस_t msm_edp_aux_irq(काष्ठा edp_aux *aux, u32 isr)
अणु
	अगर (isr & EDP_INTR_TRANS_STATUS) अणु
		DBG("isr=%x", isr);
		edp_ग_लिखो(aux->base + REG_EDP_AUX_TRANS_CTRL, 0);

		अगर (isr & EDP_INTR_AUX_I2C_ERR)
			aux->msg_err = true;
		अन्यथा
			aux->msg_err = false;

		complete(&aux->msg_comp);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

व्योम msm_edp_aux_ctrl(काष्ठा edp_aux *aux, पूर्णांक enable)
अणु
	u32 data;

	DBG("enable=%d", enable);
	data = edp_पढ़ो(aux->base + REG_EDP_AUX_CTRL);

	अगर (enable) अणु
		data |= EDP_AUX_CTRL_RESET;
		edp_ग_लिखो(aux->base + REG_EDP_AUX_CTRL, data);
		/* Make sure full reset */
		wmb();
		usleep_range(500, 1000);

		data &= ~EDP_AUX_CTRL_RESET;
		data |= EDP_AUX_CTRL_ENABLE;
		edp_ग_लिखो(aux->base + REG_EDP_AUX_CTRL, data);
	पूर्ण अन्यथा अणु
		data &= ~EDP_AUX_CTRL_ENABLE;
		edp_ग_लिखो(aux->base + REG_EDP_AUX_CTRL, data);
	पूर्ण
पूर्ण

