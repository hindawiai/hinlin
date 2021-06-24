<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2005-2011 Atheros Communications Inc.
 * Copyright (c) 2011-2014,2016-2017 Qualcomm Atheros, Inc.
 */

#समावेश "bmi.h"
#समावेश "hif.h"
#समावेश "debug.h"
#समावेश "htc.h"
#समावेश "hw.h"

व्योम ath10k_bmi_start(काष्ठा ath10k *ar)
अणु
	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi start\n");

	ar->bmi.करोne_sent = false;
पूर्ण
EXPORT_SYMBOL(ath10k_bmi_start);

पूर्णांक ath10k_bmi_करोne(काष्ठा ath10k *ar)
अणु
	काष्ठा bmi_cmd cmd;
	u32 cmdlen = माप(cmd.id) + माप(cmd.करोne);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi done\n");

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi skipped\n");
		वापस 0;
	पूर्ण

	ar->bmi.करोne_sent = true;
	cmd.id = __cpu_to_le32(BMI_DONE);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, शून्य, शून्य);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to write to the device: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_get_target_info(काष्ठा ath10k *ar,
			       काष्ठा bmi_target_info *target_info)
अणु
	काष्ठा bmi_cmd cmd;
	जोड़ bmi_resp resp;
	u32 cmdlen = माप(cmd.id) + माप(cmd.get_target_info);
	u32 resplen = माप(resp.get_target_info);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi get target info\n");

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "BMI Get Target Info Command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id = __cpu_to_le32(BMI_GET_TARGET_INFO);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, &resp, &resplen);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to get target info from device\n");
		वापस ret;
	पूर्ण

	अगर (resplen < माप(resp.get_target_info)) अणु
		ath10k_warn(ar, "invalid get_target_info response length (%d)\n",
			    resplen);
		वापस -EIO;
	पूर्ण

	target_info->version = __le32_to_cpu(resp.get_target_info.version);
	target_info->type    = __le32_to_cpu(resp.get_target_info.type);

	वापस 0;
पूर्ण

#घोषणा TARGET_VERSION_SENTINAL 0xffffffffu

पूर्णांक ath10k_bmi_get_target_info_sdio(काष्ठा ath10k *ar,
				    काष्ठा bmi_target_info *target_info)
अणु
	काष्ठा bmi_cmd cmd;
	जोड़ bmi_resp resp;
	u32 cmdlen = माप(cmd.id) + माप(cmd.get_target_info);
	u32 resplen, ver_len;
	__le32 पंचांगp;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi get target info SDIO\n");

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "BMI Get Target Info Command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id = __cpu_to_le32(BMI_GET_TARGET_INFO);

	/* Step 1: Read 4 bytes of the target info and check अगर it is
	 * the special sentinal version word or the first word in the
	 * version response.
	 */
	resplen = माप(u32);
	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, &पंचांगp, &resplen);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to read from device\n");
		वापस ret;
	पूर्ण

	/* Some SDIO boards have a special sentinal byte beक्रमe the real
	 * version response.
	 */
	अगर (__le32_to_cpu(पंचांगp) == TARGET_VERSION_SENTINAL) अणु
		/* Step 1b: Read the version length */
		resplen = माप(u32);
		ret = ath10k_hअगर_exchange_bmi_msg(ar, शून्य, 0, &पंचांगp,
						  &resplen);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to read from device\n");
			वापस ret;
		पूर्ण
	पूर्ण

	ver_len = __le32_to_cpu(पंचांगp);

	/* Step 2: Check the target info length */
	अगर (ver_len != माप(resp.get_target_info)) अणु
		ath10k_warn(ar, "Unexpected target info len: %u. Expected: %zu\n",
			    ver_len, माप(resp.get_target_info));
		वापस -EINVAL;
	पूर्ण

	/* Step 3: Read the rest of the version response */
	resplen = माप(resp.get_target_info) - माप(u32);
	ret = ath10k_hअगर_exchange_bmi_msg(ar, शून्य, 0,
					  &resp.get_target_info.version,
					  &resplen);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to read from device\n");
		वापस ret;
	पूर्ण

	target_info->version = __le32_to_cpu(resp.get_target_info.version);
	target_info->type    = __le32_to_cpu(resp.get_target_info.type);

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_पढ़ो_memory(काष्ठा ath10k *ar,
			   u32 address, व्योम *buffer, u32 length)
अणु
	काष्ठा bmi_cmd cmd;
	जोड़ bmi_resp resp;
	u32 cmdlen = माप(cmd.id) + माप(cmd.पढ़ो_mem);
	u32 rxlen;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi read address 0x%x length %d\n",
		   address, length);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	जबतक (length) अणु
		rxlen = min_t(u32, length, BMI_MAX_DATA_SIZE);

		cmd.id            = __cpu_to_le32(BMI_READ_MEMORY);
		cmd.पढ़ो_mem.addr = __cpu_to_le32(address);
		cmd.पढ़ो_mem.len  = __cpu_to_le32(rxlen);

		ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen,
						  &resp, &rxlen);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to read from the device (%d)\n",
				    ret);
			वापस ret;
		पूर्ण

		स_नकल(buffer, resp.पढ़ो_mem.payload, rxlen);
		address += rxlen;
		buffer  += rxlen;
		length  -= rxlen;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ath10k_bmi_पढ़ो_memory);

पूर्णांक ath10k_bmi_ग_लिखो_soc_reg(काष्ठा ath10k *ar, u32 address, u32 reg_val)
अणु
	काष्ठा bmi_cmd cmd;
	u32 cmdlen = माप(cmd.id) + माप(cmd.ग_लिखो_soc_reg);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI,
		   "bmi write soc register 0x%08x val 0x%08x\n",
		   address, reg_val);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "bmi write soc register command in progress\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id = __cpu_to_le32(BMI_WRITE_SOC_REGISTER);
	cmd.ग_लिखो_soc_reg.addr = __cpu_to_le32(address);
	cmd.ग_लिखो_soc_reg.value = __cpu_to_le32(reg_val);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, शून्य, शून्य);
	अगर (ret) अणु
		ath10k_warn(ar, "Unable to write soc register to device: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_पढ़ो_soc_reg(काष्ठा ath10k *ar, u32 address, u32 *reg_val)
अणु
	काष्ठा bmi_cmd cmd;
	जोड़ bmi_resp resp;
	u32 cmdlen = माप(cmd.id) + माप(cmd.पढ़ो_soc_reg);
	u32 resplen = माप(resp.पढ़ो_soc_reg);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi read soc register 0x%08x\n",
		   address);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "bmi read soc register command in progress\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id = __cpu_to_le32(BMI_READ_SOC_REGISTER);
	cmd.पढ़ो_soc_reg.addr = __cpu_to_le32(address);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, &resp, &resplen);
	अगर (ret) अणु
		ath10k_warn(ar, "Unable to read soc register from device: %d\n",
			    ret);
		वापस ret;
	पूर्ण

	*reg_val = __le32_to_cpu(resp.पढ़ो_soc_reg.value);

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi read soc register value 0x%08x\n",
		   *reg_val);

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_ग_लिखो_memory(काष्ठा ath10k *ar,
			    u32 address, स्थिर व्योम *buffer, u32 length)
अणु
	काष्ठा bmi_cmd cmd;
	u32 hdrlen = माप(cmd.id) + माप(cmd.ग_लिखो_mem);
	u32 txlen;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi write address 0x%x length %d\n",
		   address, length);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	जबतक (length) अणु
		txlen = min(length, BMI_MAX_DATA_SIZE - hdrlen);

		/* copy beक्रमe roundup to aव्योम पढ़ोing beyond buffer*/
		स_नकल(cmd.ग_लिखो_mem.payload, buffer, txlen);
		txlen = roundup(txlen, 4);

		cmd.id             = __cpu_to_le32(BMI_WRITE_MEMORY);
		cmd.ग_लिखो_mem.addr = __cpu_to_le32(address);
		cmd.ग_लिखो_mem.len  = __cpu_to_le32(txlen);

		ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, hdrlen + txlen,
						  शून्य, शून्य);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to write to the device (%d)\n",
				    ret);
			वापस ret;
		पूर्ण

		/* fixup roundup() so `length` zeroes out क्रम last chunk */
		txlen = min(txlen, length);

		address += txlen;
		buffer  += txlen;
		length  -= txlen;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_execute(काष्ठा ath10k *ar, u32 address, u32 param, u32 *result)
अणु
	काष्ठा bmi_cmd cmd;
	जोड़ bmi_resp resp;
	u32 cmdlen = माप(cmd.id) + माप(cmd.execute);
	u32 resplen = माप(resp.execute);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi execute address 0x%x param 0x%x\n",
		   address, param);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id            = __cpu_to_le32(BMI_EXECUTE);
	cmd.execute.addr  = __cpu_to_le32(address);
	cmd.execute.param = __cpu_to_le32(param);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, &resp, &resplen);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to read from the device\n");
		वापस ret;
	पूर्ण

	अगर (resplen < माप(resp.execute)) अणु
		ath10k_warn(ar, "invalid execute response length (%d)\n",
			    resplen);
		वापस -EIO;
	पूर्ण

	*result = __le32_to_cpu(resp.execute.result);

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi execute result 0x%x\n", *result);

	वापस 0;
पूर्ण

अटल पूर्णांक ath10k_bmi_lz_data_large(काष्ठा ath10k *ar, स्थिर व्योम *buffer, u32 length)
अणु
	काष्ठा bmi_cmd *cmd;
	u32 hdrlen = माप(cmd->id) + माप(cmd->lz_data);
	u32 txlen;
	पूर्णांक ret;
	माप_प्रकार buf_len;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "large bmi lz data buffer 0x%pK length %d\n",
		   buffer, length);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	buf_len = माप(*cmd) + BMI_MAX_LARGE_DATA_SIZE - BMI_MAX_DATA_SIZE;
	cmd = kzalloc(buf_len, GFP_KERNEL);
	अगर (!cmd)
		वापस -ENOMEM;

	जबतक (length) अणु
		txlen = min(length, BMI_MAX_LARGE_DATA_SIZE - hdrlen);

		WARN_ON_ONCE(txlen & 3);

		cmd->id          = __cpu_to_le32(BMI_LZ_DATA);
		cmd->lz_data.len = __cpu_to_le32(txlen);
		स_नकल(cmd->lz_data.payload, buffer, txlen);

		ret = ath10k_hअगर_exchange_bmi_msg(ar, cmd, hdrlen + txlen,
						  शून्य, शून्य);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to write to the device\n");
			kमुक्त(cmd);
			वापस ret;
		पूर्ण

		buffer += txlen;
		length -= txlen;
	पूर्ण

	kमुक्त(cmd);

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_lz_data(काष्ठा ath10k *ar, स्थिर व्योम *buffer, u32 length)
अणु
	काष्ठा bmi_cmd cmd;
	u32 hdrlen = माप(cmd.id) + माप(cmd.lz_data);
	u32 txlen;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi lz data buffer 0x%pK length %d\n",
		   buffer, length);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	जबतक (length) अणु
		txlen = min(length, BMI_MAX_DATA_SIZE - hdrlen);

		WARN_ON_ONCE(txlen & 3);

		cmd.id          = __cpu_to_le32(BMI_LZ_DATA);
		cmd.lz_data.len = __cpu_to_le32(txlen);
		स_नकल(cmd.lz_data.payload, buffer, txlen);

		ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, hdrlen + txlen,
						  शून्य, शून्य);
		अगर (ret) अणु
			ath10k_warn(ar, "unable to write to the device\n");
			वापस ret;
		पूर्ण

		buffer += txlen;
		length -= txlen;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_lz_stream_start(काष्ठा ath10k *ar, u32 address)
अणु
	काष्ठा bmi_cmd cmd;
	u32 cmdlen = माप(cmd.id) + माप(cmd.lz_start);
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI, "bmi lz stream start address 0x%x\n",
		   address);

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id            = __cpu_to_le32(BMI_LZ_STREAM_START);
	cmd.lz_start.addr = __cpu_to_le32(address);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, शून्य, शून्य);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to Start LZ Stream to the device\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक ath10k_bmi_fast_करोwnload(काष्ठा ath10k *ar,
			     u32 address, स्थिर व्योम *buffer, u32 length)
अणु
	u8 trailer[4] = अणुपूर्ण;
	u32 head_len = roundकरोwn(length, 4);
	u32 trailer_len = length - head_len;
	पूर्णांक ret;

	ath10k_dbg(ar, ATH10K_DBG_BMI,
		   "bmi fast download address 0x%x buffer 0x%pK length %d\n",
		   address, buffer, length);

	ret = ath10k_bmi_lz_stream_start(ar, address);
	अगर (ret)
		वापस ret;

	/* copy the last word पूर्णांकo a zero padded buffer */
	अगर (trailer_len > 0)
		स_नकल(trailer, buffer + head_len, trailer_len);

	अगर (ar->hw_params.bmi_large_size_करोwnload)
		ret = ath10k_bmi_lz_data_large(ar, buffer, head_len);
	अन्यथा
		ret = ath10k_bmi_lz_data(ar, buffer, head_len);

	अगर (ret)
		वापस ret;

	अगर (trailer_len > 0)
		ret = ath10k_bmi_lz_data(ar, trailer, 4);

	अगर (ret != 0)
		वापस ret;

	/*
	 * Close compressed stream and खोलो a new (fake) one.
	 * This serves मुख्यly to flush Target caches.
	 */
	ret = ath10k_bmi_lz_stream_start(ar, 0x00);

	वापस ret;
पूर्ण

पूर्णांक ath10k_bmi_set_start(काष्ठा ath10k *ar, u32 address)
अणु
	काष्ठा bmi_cmd cmd;
	u32 cmdlen = माप(cmd.id) + माप(cmd.set_app_start);
	पूर्णांक ret;

	अगर (ar->bmi.करोne_sent) अणु
		ath10k_warn(ar, "bmi set start command disallowed\n");
		वापस -EBUSY;
	पूर्ण

	cmd.id = __cpu_to_le32(BMI_SET_APP_START);
	cmd.set_app_start.addr = __cpu_to_le32(address);

	ret = ath10k_hअगर_exchange_bmi_msg(ar, &cmd, cmdlen, शून्य, शून्य);
	अगर (ret) अणु
		ath10k_warn(ar, "unable to set start to the device:%d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
