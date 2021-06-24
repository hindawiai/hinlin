<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2012-2020, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/delay.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "dp_reg.h"
#समावेश "dp_aux.h"

#घोषणा DP_AUX_ENUM_STR(x)		#x

काष्ठा dp_aux_निजी अणु
	काष्ठा device *dev;
	काष्ठा dp_catalog *catalog;

	काष्ठा mutex mutex;
	काष्ठा completion comp;

	u32 aux_error_num;
	u32 retry_cnt;
	bool cmd_busy;
	bool native;
	bool पढ़ो;
	bool no_send_addr;
	bool no_send_stop;
	u32 offset;
	u32 segment;
	u32 isr;

	काष्ठा drm_dp_aux dp_aux;
पूर्ण;

#घोषणा MAX_AUX_RETRIES			5

अटल स्थिर अक्षर *dp_aux_get_error(u32 aux_error)
अणु
	चयन (aux_error) अणु
	हाल DP_AUX_ERR_NONE:
		वापस DP_AUX_ENUM_STR(DP_AUX_ERR_NONE);
	हाल DP_AUX_ERR_ADDR:
		वापस DP_AUX_ENUM_STR(DP_AUX_ERR_ADDR);
	हाल DP_AUX_ERR_TOUT:
		वापस DP_AUX_ENUM_STR(DP_AUX_ERR_TOUT);
	हाल DP_AUX_ERR_NACK:
		वापस DP_AUX_ENUM_STR(DP_AUX_ERR_NACK);
	हाल DP_AUX_ERR_DEFER:
		वापस DP_AUX_ENUM_STR(DP_AUX_ERR_DEFER);
	हाल DP_AUX_ERR_NACK_DEFER:
		वापस DP_AUX_ENUM_STR(DP_AUX_ERR_NACK_DEFER);
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल u32 dp_aux_ग_लिखो(काष्ठा dp_aux_निजी *aux,
			काष्ठा drm_dp_aux_msg *msg)
अणु
	u32 data[4], reg, len;
	u8 *msgdata = msg->buffer;
	पूर्णांक स्थिर AUX_CMD_FIFO_LEN = 128;
	पूर्णांक i = 0;

	अगर (aux->पढ़ो)
		len = 4;
	अन्यथा
		len = msg->size + 4;

	/*
	 * cmd fअगरo only has depth of 144 bytes
	 * limit buf length to 128 bytes here
	 */
	अगर (len > AUX_CMD_FIFO_LEN) अणु
		DRM_ERROR("buf size greater than allowed size of 128 bytes\n");
		वापस 0;
	पूर्ण

	/* Pack cmd and ग_लिखो to HW */
	data[0] = (msg->address >> 16) & 0xf; /* addr[19:16] */
	अगर (aux->पढ़ो)
		data[0] |=  BIT(4); /* R/W */

	data[1] = (msg->address >> 8) & 0xff;	/* addr[15:8] */
	data[2] = msg->address & 0xff;		/* addr[7:0] */
	data[3] = (msg->size - 1) & 0xff;	/* len[7:0] */

	क्रम (i = 0; i < len; i++) अणु
		reg = (i < 4) ? data[i] : msgdata[i - 4];
		/* index = 0, ग_लिखो */
		reg = (((reg) << DP_AUX_DATA_OFFSET)
		       & DP_AUX_DATA_MASK) | DP_AUX_DATA_WRITE;
		अगर (i == 0)
			reg |= DP_AUX_DATA_INDEX_WRITE;
		aux->catalog->aux_data = reg;
		dp_catalog_aux_ग_लिखो_data(aux->catalog);
	पूर्ण

	dp_catalog_aux_clear_trans(aux->catalog, false);
	dp_catalog_aux_clear_hw_पूर्णांकerrupts(aux->catalog);

	reg = 0; /* Transaction number == 1 */
	अगर (!aux->native) अणु /* i2c */
		reg |= DP_AUX_TRANS_CTRL_I2C;

		अगर (aux->no_send_addr)
			reg |= DP_AUX_TRANS_CTRL_NO_SEND_ADDR;

		अगर (aux->no_send_stop)
			reg |= DP_AUX_TRANS_CTRL_NO_SEND_STOP;
	पूर्ण

	reg |= DP_AUX_TRANS_CTRL_GO;
	aux->catalog->aux_data = reg;
	dp_catalog_aux_ग_लिखो_trans(aux->catalog);

	वापस len;
पूर्ण

अटल पूर्णांक dp_aux_cmd_fअगरo_tx(काष्ठा dp_aux_निजी *aux,
			      काष्ठा drm_dp_aux_msg *msg)
अणु
	u32 ret, len, समयout;
	पूर्णांक aux_समयout_ms = HZ/4;

	reinit_completion(&aux->comp);

	len = dp_aux_ग_लिखो(aux, msg);
	अगर (len == 0) अणु
		DRM_ERROR("DP AUX write failed\n");
		वापस -EINVAL;
	पूर्ण

	समयout = रुको_क्रम_completion_समयout(&aux->comp, aux_समयout_ms);
	अगर (!समयout) अणु
		DRM_ERROR("aux %s timeout\n", (aux->पढ़ो ? "read" : "write"));
		वापस -ETIMEDOUT;
	पूर्ण

	अगर (aux->aux_error_num == DP_AUX_ERR_NONE) अणु
		ret = len;
	पूर्ण अन्यथा अणु
		DRM_ERROR_RATELIMITED("aux err: %s\n",
			dp_aux_get_error(aux->aux_error_num));

		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम dp_aux_cmd_fअगरo_rx(काष्ठा dp_aux_निजी *aux,
		काष्ठा drm_dp_aux_msg *msg)
अणु
	u32 data;
	u8 *dp;
	u32 i, actual_i;
	u32 len = msg->size;

	dp_catalog_aux_clear_trans(aux->catalog, true);

	data = DP_AUX_DATA_INDEX_WRITE; /* INDEX_WRITE */
	data |= DP_AUX_DATA_READ;  /* पढ़ो */

	aux->catalog->aux_data = data;
	dp_catalog_aux_ग_लिखो_data(aux->catalog);

	dp = msg->buffer;

	/* discard first byte */
	data = dp_catalog_aux_पढ़ो_data(aux->catalog);

	क्रम (i = 0; i < len; i++) अणु
		data = dp_catalog_aux_पढ़ो_data(aux->catalog);
		*dp++ = (u8)((data >> DP_AUX_DATA_OFFSET) & 0xff);

		actual_i = (data >> DP_AUX_DATA_INDEX_OFFSET) & 0xFF;
		अगर (i != actual_i)
			DRM_ERROR("Index mismatch: expected %d, found %d\n",
				i, actual_i);
	पूर्ण
पूर्ण

अटल व्योम dp_aux_native_handler(काष्ठा dp_aux_निजी *aux)
अणु
	u32 isr = aux->isr;

	अगर (isr & DP_INTR_AUX_I2C_DONE)
		aux->aux_error_num = DP_AUX_ERR_NONE;
	अन्यथा अगर (isr & DP_INTR_WRONG_ADDR)
		aux->aux_error_num = DP_AUX_ERR_ADDR;
	अन्यथा अगर (isr & DP_INTR_TIMEOUT)
		aux->aux_error_num = DP_AUX_ERR_TOUT;
	अगर (isr & DP_INTR_NACK_DEFER)
		aux->aux_error_num = DP_AUX_ERR_NACK;
	अगर (isr & DP_INTR_AUX_ERROR) अणु
		aux->aux_error_num = DP_AUX_ERR_PHY;
		dp_catalog_aux_clear_hw_पूर्णांकerrupts(aux->catalog);
	पूर्ण

	complete(&aux->comp);
पूर्ण

अटल व्योम dp_aux_i2c_handler(काष्ठा dp_aux_निजी *aux)
अणु
	u32 isr = aux->isr;

	अगर (isr & DP_INTR_AUX_I2C_DONE) अणु
		अगर (isr & (DP_INTR_I2C_NACK | DP_INTR_I2C_DEFER))
			aux->aux_error_num = DP_AUX_ERR_NACK;
		अन्यथा
			aux->aux_error_num = DP_AUX_ERR_NONE;
	पूर्ण अन्यथा अणु
		अगर (isr & DP_INTR_WRONG_ADDR)
			aux->aux_error_num = DP_AUX_ERR_ADDR;
		अन्यथा अगर (isr & DP_INTR_TIMEOUT)
			aux->aux_error_num = DP_AUX_ERR_TOUT;
		अगर (isr & DP_INTR_NACK_DEFER)
			aux->aux_error_num = DP_AUX_ERR_NACK_DEFER;
		अगर (isr & DP_INTR_I2C_NACK)
			aux->aux_error_num = DP_AUX_ERR_NACK;
		अगर (isr & DP_INTR_I2C_DEFER)
			aux->aux_error_num = DP_AUX_ERR_DEFER;
		अगर (isr & DP_INTR_AUX_ERROR) अणु
			aux->aux_error_num = DP_AUX_ERR_PHY;
			dp_catalog_aux_clear_hw_पूर्णांकerrupts(aux->catalog);
		पूर्ण
	पूर्ण

	complete(&aux->comp);
पूर्ण

अटल व्योम dp_aux_update_offset_and_segment(काष्ठा dp_aux_निजी *aux,
					     काष्ठा drm_dp_aux_msg *input_msg)
अणु
	u32 edid_address = 0x50;
	u32 segment_address = 0x30;
	bool i2c_पढ़ो = input_msg->request &
		(DP_AUX_I2C_READ & DP_AUX_NATIVE_READ);
	u8 *data;

	अगर (aux->native || i2c_पढ़ो || ((input_msg->address != edid_address) &&
		(input_msg->address != segment_address)))
		वापस;


	data = input_msg->buffer;
	अगर (input_msg->address == segment_address)
		aux->segment = *data;
	अन्यथा
		aux->offset = *data;
पूर्ण

/**
 * dp_aux_transfer_helper() - helper function क्रम EDID पढ़ो transactions
 *
 * @aux: DP AUX निजी काष्ठाure
 * @input_msg: input message from DRM upstream APIs
 * @send_seg: send the segment to sink
 *
 * वापस: व्योम
 *
 * This helper function is used to fix EDID पढ़ोs क्रम non-compliant
 * sinks that करो not handle the i2c middle-of-transaction flag correctly.
 */
अटल व्योम dp_aux_transfer_helper(काष्ठा dp_aux_निजी *aux,
				   काष्ठा drm_dp_aux_msg *input_msg,
				   bool send_seg)
अणु
	काष्ठा drm_dp_aux_msg helper_msg;
	u32 message_size = 0x10;
	u32 segment_address = 0x30;
	u32 स्थिर edid_block_length = 0x80;
	bool i2c_mot = input_msg->request & DP_AUX_I2C_MOT;
	bool i2c_पढ़ो = input_msg->request &
		(DP_AUX_I2C_READ & DP_AUX_NATIVE_READ);

	अगर (!i2c_mot || !i2c_पढ़ो || (input_msg->size == 0))
		वापस;

	/*
	 * Sending the segment value and EDID offset will be perक्रमmed
	 * from the DRM upstream EDID driver क्रम each block. Aव्योम
	 * duplicate AUX transactions related to this जबतक पढ़ोing the
	 * first 16 bytes of each block.
	 */
	अगर (!(aux->offset % edid_block_length) || !send_seg)
		जाओ end;

	aux->पढ़ो = false;
	aux->cmd_busy = true;
	aux->no_send_addr = true;
	aux->no_send_stop = true;

	/*
	 * Send the segment address क्रम every i2c पढ़ो in which the
	 * middle-of-tranaction flag is set. This is required to support EDID
	 * पढ़ोs of more than 2 blocks as the segment address is reset to 0
	 * since we are overriding the middle-of-transaction flag क्रम पढ़ो
	 * transactions.
	 */

	अगर (aux->segment) अणु
		स_रखो(&helper_msg, 0, माप(helper_msg));
		helper_msg.address = segment_address;
		helper_msg.buffer = &aux->segment;
		helper_msg.size = 1;
		dp_aux_cmd_fअगरo_tx(aux, &helper_msg);
	पूर्ण

	/*
	 * Send the offset address क्रम every i2c पढ़ो in which the
	 * middle-of-transaction flag is set. This will ensure that the sink
	 * will update its पढ़ो poपूर्णांकer and वापस the correct portion of the
	 * EDID buffer in the subsequent i2c पढ़ो trasntion triggered in the
	 * native AUX transfer function.
	 */
	स_रखो(&helper_msg, 0, माप(helper_msg));
	helper_msg.address = input_msg->address;
	helper_msg.buffer = &aux->offset;
	helper_msg.size = 1;
	dp_aux_cmd_fअगरo_tx(aux, &helper_msg);

end:
	aux->offset += message_size;
	अगर (aux->offset == 0x80 || aux->offset == 0x100)
		aux->segment = 0x0; /* reset segment at end of block */
पूर्ण

/*
 * This function करोes the real job to process an AUX transaction.
 * It will call aux_reset() function to reset the AUX channel,
 * अगर the रुकोing is समयout.
 */
अटल sमाप_प्रकार dp_aux_transfer(काष्ठा drm_dp_aux *dp_aux,
			       काष्ठा drm_dp_aux_msg *msg)
अणु
	sमाप_प्रकार ret;
	पूर्णांक स्थिर aux_cmd_native_max = 16;
	पूर्णांक स्थिर aux_cmd_i2c_max = 128;
	काष्ठा dp_aux_निजी *aux = container_of(dp_aux,
		काष्ठा dp_aux_निजी, dp_aux);

	mutex_lock(&aux->mutex);

	aux->native = msg->request & (DP_AUX_NATIVE_WRITE & DP_AUX_NATIVE_READ);

	/* Ignore address only message */
	अगर ((msg->size == 0) || (msg->buffer == शून्य)) अणु
		msg->reply = aux->native ?
			DP_AUX_NATIVE_REPLY_ACK : DP_AUX_I2C_REPLY_ACK;
		ret = msg->size;
		जाओ unlock_निकास;
	पूर्ण

	/* msg sanity check */
	अगर ((aux->native && (msg->size > aux_cmd_native_max)) ||
		(msg->size > aux_cmd_i2c_max)) अणु
		DRM_ERROR("%s: invalid msg: size(%zu), request(%x)\n",
			__func__, msg->size, msg->request);
		ret = -EINVAL;
		जाओ unlock_निकास;
	पूर्ण

	dp_aux_update_offset_and_segment(aux, msg);
	dp_aux_transfer_helper(aux, msg, true);

	aux->पढ़ो = msg->request & (DP_AUX_I2C_READ & DP_AUX_NATIVE_READ);
	aux->cmd_busy = true;

	अगर (aux->पढ़ो) अणु
		aux->no_send_addr = true;
		aux->no_send_stop = false;
	पूर्ण अन्यथा अणु
		aux->no_send_addr = true;
		aux->no_send_stop = true;
	पूर्ण

	ret = dp_aux_cmd_fअगरo_tx(aux, msg);

	अगर (ret < 0) अणु
		अगर (aux->native) अणु
			aux->retry_cnt++;
			अगर (!(aux->retry_cnt % MAX_AUX_RETRIES))
				dp_catalog_aux_update_cfg(aux->catalog);
		पूर्ण
		usleep_range(400, 500); /* at least 400us to next try */
		जाओ unlock_निकास;
	पूर्ण

	अगर (aux->aux_error_num == DP_AUX_ERR_NONE) अणु
		अगर (aux->पढ़ो)
			dp_aux_cmd_fअगरo_rx(aux, msg);

		msg->reply = aux->native ?
			DP_AUX_NATIVE_REPLY_ACK : DP_AUX_I2C_REPLY_ACK;
	पूर्ण अन्यथा अणु
		/* Reply defer to retry */
		msg->reply = aux->native ?
			DP_AUX_NATIVE_REPLY_DEFER : DP_AUX_I2C_REPLY_DEFER;
	पूर्ण

	/* Return requested size क्रम success or retry */
	ret = msg->size;
	aux->retry_cnt = 0;

unlock_निकास:
	aux->cmd_busy = false;
	mutex_unlock(&aux->mutex);
	वापस ret;
पूर्ण

व्योम dp_aux_isr(काष्ठा drm_dp_aux *dp_aux)
अणु
	काष्ठा dp_aux_निजी *aux;

	अगर (!dp_aux) अणु
		DRM_ERROR("invalid input\n");
		वापस;
	पूर्ण

	aux = container_of(dp_aux, काष्ठा dp_aux_निजी, dp_aux);

	aux->isr = dp_catalog_aux_get_irq(aux->catalog);

	अगर (!aux->cmd_busy)
		वापस;

	अगर (aux->native)
		dp_aux_native_handler(aux);
	अन्यथा
		dp_aux_i2c_handler(aux);
पूर्ण

व्योम dp_aux_reconfig(काष्ठा drm_dp_aux *dp_aux)
अणु
	काष्ठा dp_aux_निजी *aux;

	aux = container_of(dp_aux, काष्ठा dp_aux_निजी, dp_aux);

	dp_catalog_aux_update_cfg(aux->catalog);
	dp_catalog_aux_reset(aux->catalog);
पूर्ण

व्योम dp_aux_init(काष्ठा drm_dp_aux *dp_aux)
अणु
	काष्ठा dp_aux_निजी *aux;

	अगर (!dp_aux) अणु
		DRM_ERROR("invalid input\n");
		वापस;
	पूर्ण

	aux = container_of(dp_aux, काष्ठा dp_aux_निजी, dp_aux);

	dp_catalog_aux_enable(aux->catalog, true);
	aux->retry_cnt = 0;
पूर्ण

व्योम dp_aux_deinit(काष्ठा drm_dp_aux *dp_aux)
अणु
	काष्ठा dp_aux_निजी *aux;

	aux = container_of(dp_aux, काष्ठा dp_aux_निजी, dp_aux);

	dp_catalog_aux_enable(aux->catalog, false);
पूर्ण

पूर्णांक dp_aux_रेजिस्टर(काष्ठा drm_dp_aux *dp_aux)
अणु
	काष्ठा dp_aux_निजी *aux;
	पूर्णांक ret;

	अगर (!dp_aux) अणु
		DRM_ERROR("invalid input\n");
		वापस -EINVAL;
	पूर्ण

	aux = container_of(dp_aux, काष्ठा dp_aux_निजी, dp_aux);

	aux->dp_aux.name = "dpu_dp_aux";
	aux->dp_aux.dev = aux->dev;
	aux->dp_aux.transfer = dp_aux_transfer;
	ret = drm_dp_aux_रेजिस्टर(&aux->dp_aux);
	अगर (ret) अणु
		DRM_ERROR("%s: failed to register drm aux: %d\n", __func__,
				ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dp_aux_unरेजिस्टर(काष्ठा drm_dp_aux *dp_aux)
अणु
	drm_dp_aux_unरेजिस्टर(dp_aux);
पूर्ण

काष्ठा drm_dp_aux *dp_aux_get(काष्ठा device *dev, काष्ठा dp_catalog *catalog)
अणु
	काष्ठा dp_aux_निजी *aux;

	अगर (!catalog) अणु
		DRM_ERROR("invalid input\n");
		वापस ERR_PTR(-ENODEV);
	पूर्ण

	aux = devm_kzalloc(dev, माप(*aux), GFP_KERNEL);
	अगर (!aux)
		वापस ERR_PTR(-ENOMEM);

	init_completion(&aux->comp);
	aux->cmd_busy = false;
	mutex_init(&aux->mutex);

	aux->dev = dev;
	aux->catalog = catalog;
	aux->retry_cnt = 0;

	वापस &aux->dp_aux;
पूर्ण

व्योम dp_aux_put(काष्ठा drm_dp_aux *dp_aux)
अणु
	काष्ठा dp_aux_निजी *aux;

	अगर (!dp_aux)
		वापस;

	aux = container_of(dp_aux, काष्ठा dp_aux_निजी, dp_aux);

	mutex_destroy(&aux->mutex);

	devm_kमुक्त(aux->dev, aux);
पूर्ण
