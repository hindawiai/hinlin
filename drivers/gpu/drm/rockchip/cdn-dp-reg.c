<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Fuzhou Rockchip Electronics Co.Ltd
 * Author: Chris Zhong <zyw@rock-chips.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/iopoll.h>
#समावेश <linux/reset.h>

#समावेश "cdn-dp-core.h"
#समावेश "cdn-dp-reg.h"

#घोषणा CDN_DP_SPDIF_CLK		200000000
#घोषणा FW_ALIVE_TIMEOUT_US		1000000
#घोषणा MAILBOX_RETRY_US		1000
#घोषणा MAILBOX_TIMEOUT_US		5000000
#घोषणा LINK_TRAINING_RETRY_MS		20
#घोषणा LINK_TRAINING_TIMEOUT_MS	500

व्योम cdn_dp_set_fw_clk(काष्ठा cdn_dp_device *dp, अचिन्हित दीर्घ clk)
अणु
	ग_लिखोl(clk / 1000000, dp->regs + SW_CLK_H);
पूर्ण

व्योम cdn_dp_घड़ी_reset(काष्ठा cdn_dp_device *dp)
अणु
	u32 val;

	val = DPTX_FRMR_DATA_CLK_RSTN_EN |
	      DPTX_FRMR_DATA_CLK_EN |
	      DPTX_PHY_DATA_RSTN_EN |
	      DPTX_PHY_DATA_CLK_EN |
	      DPTX_PHY_CHAR_RSTN_EN |
	      DPTX_PHY_CHAR_CLK_EN |
	      SOURCE_AUX_SYS_CLK_RSTN_EN |
	      SOURCE_AUX_SYS_CLK_EN |
	      DPTX_SYS_CLK_RSTN_EN |
	      DPTX_SYS_CLK_EN |
	      CFG_DPTX_VIF_CLK_RSTN_EN |
	      CFG_DPTX_VIF_CLK_EN;
	ग_लिखोl(val, dp->regs + SOURCE_DPTX_CAR);

	val = SOURCE_PHY_RSTN_EN | SOURCE_PHY_CLK_EN;
	ग_लिखोl(val, dp->regs + SOURCE_PHY_CAR);

	val = SOURCE_PKT_SYS_RSTN_EN |
	      SOURCE_PKT_SYS_CLK_EN |
	      SOURCE_PKT_DATA_RSTN_EN |
	      SOURCE_PKT_DATA_CLK_EN;
	ग_लिखोl(val, dp->regs + SOURCE_PKT_CAR);

	val = SPDIF_CDR_CLK_RSTN_EN |
	      SPDIF_CDR_CLK_EN |
	      SOURCE_AIF_SYS_RSTN_EN |
	      SOURCE_AIF_SYS_CLK_EN |
	      SOURCE_AIF_CLK_RSTN_EN |
	      SOURCE_AIF_CLK_EN;
	ग_लिखोl(val, dp->regs + SOURCE_AIF_CAR);

	val = SOURCE_CIPHER_SYSTEM_CLK_RSTN_EN |
	      SOURCE_CIPHER_SYS_CLK_EN |
	      SOURCE_CIPHER_CHAR_CLK_RSTN_EN |
	      SOURCE_CIPHER_CHAR_CLK_EN;
	ग_लिखोl(val, dp->regs + SOURCE_CIPHER_CAR);

	val = SOURCE_CRYPTO_SYS_CLK_RSTN_EN |
	      SOURCE_CRYPTO_SYS_CLK_EN;
	ग_लिखोl(val, dp->regs + SOURCE_CRYPTO_CAR);

	/* enable Mailbox and PIF पूर्णांकerrupt */
	ग_लिखोl(0, dp->regs + APB_INT_MASK);
पूर्ण

अटल पूर्णांक cdn_dp_mailbox_पढ़ो(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक val, ret;

	ret = पढ़ोx_poll_समयout(पढ़ोl, dp->regs + MAILBOX_EMPTY_ADDR,
				 val, !val, MAILBOX_RETRY_US,
				 MAILBOX_TIMEOUT_US);
	अगर (ret < 0)
		वापस ret;

	वापस पढ़ोl(dp->regs + MAILBOX0_RD_DATA) & 0xff;
पूर्ण

अटल पूर्णांक cdp_dp_mailbox_ग_लिखो(काष्ठा cdn_dp_device *dp, u8 val)
अणु
	पूर्णांक ret, full;

	ret = पढ़ोx_poll_समयout(पढ़ोl, dp->regs + MAILBOX_FULL_ADDR,
				 full, !full, MAILBOX_RETRY_US,
				 MAILBOX_TIMEOUT_US);
	अगर (ret < 0)
		वापस ret;

	ग_लिखोl(val, dp->regs + MAILBOX0_WR_DATA);

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_mailbox_validate_receive(काष्ठा cdn_dp_device *dp,
					   u8 module_id, u8 opcode,
					   u16 req_size)
अणु
	u32 mbox_size, i;
	u8 header[4];
	पूर्णांक ret;

	/* पढ़ो the header of the message */
	क्रम (i = 0; i < 4; i++) अणु
		ret = cdn_dp_mailbox_पढ़ो(dp);
		अगर (ret < 0)
			वापस ret;

		header[i] = ret;
	पूर्ण

	mbox_size = (header[2] << 8) | header[3];

	अगर (opcode != header[0] || module_id != header[1] ||
	    req_size != mbox_size) अणु
		/*
		 * If the message in mailbox is not what we want, we need to
		 * clear the mailbox by पढ़ोing its contents.
		 */
		क्रम (i = 0; i < mbox_size; i++)
			अगर (cdn_dp_mailbox_पढ़ो(dp) < 0)
				अवरोध;

		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_mailbox_पढ़ो_receive(काष्ठा cdn_dp_device *dp,
				       u8 *buff, u16 buff_size)
अणु
	u32 i;
	पूर्णांक ret;

	क्रम (i = 0; i < buff_size; i++) अणु
		ret = cdn_dp_mailbox_पढ़ो(dp);
		अगर (ret < 0)
			वापस ret;

		buff[i] = ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_mailbox_send(काष्ठा cdn_dp_device *dp, u8 module_id,
			       u8 opcode, u16 size, u8 *message)
अणु
	u8 header[4];
	पूर्णांक ret, i;

	header[0] = opcode;
	header[1] = module_id;
	header[2] = (size >> 8) & 0xff;
	header[3] = size & 0xff;

	क्रम (i = 0; i < 4; i++) अणु
		ret = cdp_dp_mailbox_ग_लिखो(dp, header[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < size; i++) अणु
		ret = cdp_dp_mailbox_ग_लिखो(dp, message[i]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cdn_dp_reg_ग_लिखो(काष्ठा cdn_dp_device *dp, u16 addr, u32 val)
अणु
	u8 msg[6];

	msg[0] = (addr >> 8) & 0xff;
	msg[1] = addr & 0xff;
	msg[2] = (val >> 24) & 0xff;
	msg[3] = (val >> 16) & 0xff;
	msg[4] = (val >> 8) & 0xff;
	msg[5] = val & 0xff;
	वापस cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_WRITE_REGISTER,
				   माप(msg), msg);
पूर्ण

अटल पूर्णांक cdn_dp_reg_ग_लिखो_bit(काष्ठा cdn_dp_device *dp, u16 addr,
				u8 start_bit, u8 bits_no, u32 val)
अणु
	u8 field[8];

	field[0] = (addr >> 8) & 0xff;
	field[1] = addr & 0xff;
	field[2] = start_bit;
	field[3] = bits_no;
	field[4] = (val >> 24) & 0xff;
	field[5] = (val >> 16) & 0xff;
	field[6] = (val >> 8) & 0xff;
	field[7] = val & 0xff;

	वापस cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_WRITE_FIELD,
				   माप(field), field);
पूर्ण

पूर्णांक cdn_dp_dpcd_पढ़ो(काष्ठा cdn_dp_device *dp, u32 addr, u8 *data, u16 len)
अणु
	u8 msg[5], reg[5];
	पूर्णांक ret;

	msg[0] = (len >> 8) & 0xff;
	msg[1] = len & 0xff;
	msg[2] = (addr >> 16) & 0xff;
	msg[3] = (addr >> 8) & 0xff;
	msg[4] = addr & 0xff;
	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_READ_DPCD,
				  माप(msg), msg);
	अगर (ret)
		जाओ err_dpcd_पढ़ो;

	ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
					      DPTX_READ_DPCD,
					      माप(reg) + len);
	अगर (ret)
		जाओ err_dpcd_पढ़ो;

	ret = cdn_dp_mailbox_पढ़ो_receive(dp, reg, माप(reg));
	अगर (ret)
		जाओ err_dpcd_पढ़ो;

	ret = cdn_dp_mailbox_पढ़ो_receive(dp, data, len);

err_dpcd_पढ़ो:
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_dpcd_ग_लिखो(काष्ठा cdn_dp_device *dp, u32 addr, u8 value)
अणु
	u8 msg[6], reg[5];
	पूर्णांक ret;

	msg[0] = 0;
	msg[1] = 1;
	msg[2] = (addr >> 16) & 0xff;
	msg[3] = (addr >> 8) & 0xff;
	msg[4] = addr & 0xff;
	msg[5] = value;
	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_WRITE_DPCD,
				  माप(msg), msg);
	अगर (ret)
		जाओ err_dpcd_ग_लिखो;

	ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
					      DPTX_WRITE_DPCD, माप(reg));
	अगर (ret)
		जाओ err_dpcd_ग_लिखो;

	ret = cdn_dp_mailbox_पढ़ो_receive(dp, reg, माप(reg));
	अगर (ret)
		जाओ err_dpcd_ग_लिखो;

	अगर (addr != (reg[2] << 16 | reg[3] << 8 | reg[4]))
		ret = -EINVAL;

err_dpcd_ग_लिखो:
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "dpcd write failed: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_load_firmware(काष्ठा cdn_dp_device *dp, स्थिर u32 *i_mem,
			 u32 i_size, स्थिर u32 *d_mem, u32 d_size)
अणु
	u32 reg;
	पूर्णांक i, ret;

	/* reset ucpu beक्रमe load firmware*/
	ग_लिखोl(APB_IRAM_PATH | APB_DRAM_PATH | APB_XT_RESET,
	       dp->regs + APB_CTRL);

	क्रम (i = 0; i < i_size; i += 4)
		ग_लिखोl(*i_mem++, dp->regs + ADDR_IMEM + i);

	क्रम (i = 0; i < d_size; i += 4)
		ग_लिखोl(*d_mem++, dp->regs + ADDR_DMEM + i);

	/* un-reset ucpu */
	ग_लिखोl(0, dp->regs + APB_CTRL);

	/* check the keep alive रेजिस्टर to make sure fw working */
	ret = पढ़ोx_poll_समयout(पढ़ोl, dp->regs + KEEP_ALIVE,
				 reg, reg, 2000, FW_ALIVE_TIMEOUT_US);
	अगर (ret < 0) अणु
		DRM_DEV_ERROR(dp->dev, "failed to loaded the FW reg = %x\n",
			      reg);
		वापस -EINVAL;
	पूर्ण

	reg = पढ़ोl(dp->regs + VER_L) & 0xff;
	dp->fw_version = reg;
	reg = पढ़ोl(dp->regs + VER_H) & 0xff;
	dp->fw_version |= reg << 8;
	reg = पढ़ोl(dp->regs + VER_LIB_L_ADDR) & 0xff;
	dp->fw_version |= reg << 16;
	reg = पढ़ोl(dp->regs + VER_LIB_H_ADDR) & 0xff;
	dp->fw_version |= reg << 24;

	DRM_DEV_DEBUG(dp->dev, "firmware version: %x\n", dp->fw_version);

	वापस 0;
पूर्ण

पूर्णांक cdn_dp_set_firmware_active(काष्ठा cdn_dp_device *dp, bool enable)
अणु
	u8 msg[5];
	पूर्णांक ret, i;

	msg[0] = GENERAL_MAIN_CONTROL;
	msg[1] = MB_MODULE_ID_GENERAL;
	msg[2] = 0;
	msg[3] = 1;
	msg[4] = enable ? FW_ACTIVE : FW_STANDBY;

	क्रम (i = 0; i < माप(msg); i++) अणु
		ret = cdp_dp_mailbox_ग_लिखो(dp, msg[i]);
		अगर (ret)
			जाओ err_set_firmware_active;
	पूर्ण

	/* पढ़ो the firmware state */
	क्रम (i = 0; i < माप(msg); i++)  अणु
		ret = cdn_dp_mailbox_पढ़ो(dp);
		अगर (ret < 0)
			जाओ err_set_firmware_active;

		msg[i] = ret;
	पूर्ण

	ret = 0;

err_set_firmware_active:
	अगर (ret < 0)
		DRM_DEV_ERROR(dp->dev, "set firmware active failed\n");
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_set_host_cap(काष्ठा cdn_dp_device *dp, u8 lanes, bool flip)
अणु
	u8 msg[8];
	पूर्णांक ret;

	msg[0] = CDN_DP_MAX_LINK_RATE;
	msg[1] = lanes | SCRAMBLER_EN;
	msg[2] = VOLTAGE_LEVEL_2;
	msg[3] = PRE_EMPHASIS_LEVEL_3;
	msg[4] = PTS1 | PTS2 | PTS3 | PTS4;
	msg[5] = FAST_LT_NOT_SUPPORT;
	msg[6] = flip ? LANE_MAPPING_FLIPPED : LANE_MAPPING_NORMAL;
	msg[7] = ENHANCED;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX,
				  DPTX_SET_HOST_CAPABILITIES,
				  माप(msg), msg);
	अगर (ret)
		जाओ err_set_host_cap;

	ret = cdn_dp_reg_ग_लिखो(dp, DP_AUX_SWAP_INVERSION_CONTROL,
			       AUX_HOST_INVERT);

err_set_host_cap:
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "set host cap failed: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_event_config(काष्ठा cdn_dp_device *dp)
अणु
	u8 msg[5];
	पूर्णांक ret;

	स_रखो(msg, 0, माप(msg));

	msg[0] = DPTX_EVENT_ENABLE_HPD | DPTX_EVENT_ENABLE_TRAINING;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_ENABLE_EVENT,
				  माप(msg), msg);
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "set event config failed: %d\n", ret);

	वापस ret;
पूर्ण

u32 cdn_dp_get_event(काष्ठा cdn_dp_device *dp)
अणु
	वापस पढ़ोl(dp->regs + SW_EVENTS0);
पूर्ण

पूर्णांक cdn_dp_get_hpd_status(काष्ठा cdn_dp_device *dp)
अणु
	u8 status;
	पूर्णांक ret;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_HPD_STATE,
				  0, शून्य);
	अगर (ret)
		जाओ err_get_hpd;

	ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
					      DPTX_HPD_STATE, माप(status));
	अगर (ret)
		जाओ err_get_hpd;

	ret = cdn_dp_mailbox_पढ़ो_receive(dp, &status, माप(status));
	अगर (ret)
		जाओ err_get_hpd;

	वापस status;

err_get_hpd:
	DRM_DEV_ERROR(dp->dev, "get hpd status failed: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_get_edid_block(व्योम *data, u8 *edid,
			  अचिन्हित पूर्णांक block, माप_प्रकार length)
अणु
	काष्ठा cdn_dp_device *dp = data;
	u8 msg[2], reg[2], i;
	पूर्णांक ret;

	क्रम (i = 0; i < 4; i++) अणु
		msg[0] = block / 2;
		msg[1] = block % 2;

		ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_GET_EDID,
					  माप(msg), msg);
		अगर (ret)
			जारी;

		ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
						      DPTX_GET_EDID,
						      माप(reg) + length);
		अगर (ret)
			जारी;

		ret = cdn_dp_mailbox_पढ़ो_receive(dp, reg, माप(reg));
		अगर (ret)
			जारी;

		ret = cdn_dp_mailbox_पढ़ो_receive(dp, edid, length);
		अगर (ret)
			जारी;

		अगर (reg[0] == length && reg[1] == block / 2)
			अवरोध;
	पूर्ण

	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "get block[%d] edid failed: %d\n", block,
			      ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_training_start(काष्ठा cdn_dp_device *dp)
अणु
	अचिन्हित दीर्घ समयout;
	u8 msg, event[2];
	पूर्णांक ret;

	msg = LINK_TRAINING_RUN;

	/* start training */
	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_TRAINING_CONTROL,
				  माप(msg), &msg);
	अगर (ret)
		जाओ err_training_start;

	समयout = jअगरfies + msecs_to_jअगरfies(LINK_TRAINING_TIMEOUT_MS);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		msleep(LINK_TRAINING_RETRY_MS);
		ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX,
					  DPTX_READ_EVENT, 0, शून्य);
		अगर (ret)
			जाओ err_training_start;

		ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
						      DPTX_READ_EVENT,
						      माप(event));
		अगर (ret)
			जाओ err_training_start;

		ret = cdn_dp_mailbox_पढ़ो_receive(dp, event, माप(event));
		अगर (ret)
			जाओ err_training_start;

		अगर (event[1] & EQ_PHASE_FINISHED)
			वापस 0;
	पूर्ण

	ret = -ETIMEDOUT;

err_training_start:
	DRM_DEV_ERROR(dp->dev, "training failed: %d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_get_training_status(काष्ठा cdn_dp_device *dp)
अणु
	u8 status[10];
	पूर्णांक ret;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_READ_LINK_STAT,
				  0, शून्य);
	अगर (ret)
		जाओ err_get_training_status;

	ret = cdn_dp_mailbox_validate_receive(dp, MB_MODULE_ID_DP_TX,
					      DPTX_READ_LINK_STAT,
					      माप(status));
	अगर (ret)
		जाओ err_get_training_status;

	ret = cdn_dp_mailbox_पढ़ो_receive(dp, status, माप(status));
	अगर (ret)
		जाओ err_get_training_status;

	dp->max_rate = drm_dp_bw_code_to_link_rate(status[0]);
	dp->max_lanes = status[1];

err_get_training_status:
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "get training status failed: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_train_link(काष्ठा cdn_dp_device *dp)
अणु
	पूर्णांक ret;

	ret = cdn_dp_training_start(dp);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to start training %d\n", ret);
		वापस ret;
	पूर्ण

	ret = cdn_dp_get_training_status(dp);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "Failed to get training stat %d\n", ret);
		वापस ret;
	पूर्ण

	DRM_DEV_DEBUG_KMS(dp->dev, "rate:0x%x, lanes:%d\n", dp->max_rate,
			  dp->max_lanes);
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_set_video_status(काष्ठा cdn_dp_device *dp, पूर्णांक active)
अणु
	u8 msg;
	पूर्णांक ret;

	msg = !!active;

	ret = cdn_dp_mailbox_send(dp, MB_MODULE_ID_DP_TX, DPTX_SET_VIDEO,
				  माप(msg), &msg);
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "set video status failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक cdn_dp_get_msa_misc(काष्ठा video_info *video,
			       काष्ठा drm_display_mode *mode)
अणु
	u32 msa_misc;
	u8 val[2] = अणु0पूर्ण;

	चयन (video->color_fmt) अणु
	हाल PXL_RGB:
	हाल Y_ONLY:
		val[0] = 0;
		अवरोध;
	/* set YUV शेष color space conversion to BT601 */
	हाल YCBCR_4_4_4:
		val[0] = 6 + BT_601 * 8;
		अवरोध;
	हाल YCBCR_4_2_2:
		val[0] = 5 + BT_601 * 8;
		अवरोध;
	हाल YCBCR_4_2_0:
		val[0] = 5;
		अवरोध;
	पूर्ण

	चयन (video->color_depth) अणु
	हाल 6:
		val[1] = 0;
		अवरोध;
	हाल 8:
		val[1] = 1;
		अवरोध;
	हाल 10:
		val[1] = 2;
		अवरोध;
	हाल 12:
		val[1] = 3;
		अवरोध;
	हाल 16:
		val[1] = 4;
		अवरोध;
	पूर्ण

	msa_misc = 2 * val[0] + 32 * val[1] +
		   ((video->color_fmt == Y_ONLY) ? (1 << 14) : 0);

	वापस msa_misc;
पूर्ण

पूर्णांक cdn_dp_config_video(काष्ठा cdn_dp_device *dp)
अणु
	काष्ठा video_info *video = &dp->video_info;
	काष्ठा drm_display_mode *mode = &dp->mode;
	u64 symbol;
	u32 val, link_rate, rem;
	u8 bit_per_pix, tu_size_reg = TU_SIZE;
	पूर्णांक ret;

	bit_per_pix = (video->color_fmt == YCBCR_4_2_2) ?
		      (video->color_depth * 2) : (video->color_depth * 3);

	link_rate = dp->max_rate / 1000;

	ret = cdn_dp_reg_ग_लिखो(dp, BND_HSYNC2VSYNC, VIF_BYPASS_INTERLACE);
	अगर (ret)
		जाओ err_config_video;

	ret = cdn_dp_reg_ग_लिखो(dp, HSYNC2VSYNC_POL_CTRL, 0);
	अगर (ret)
		जाओ err_config_video;

	/*
	 * get a best tu_size and valid symbol:
	 * 1. chose Lclk freq(162Mhz, 270Mhz, 540Mhz), set TU to 32
	 * 2. calculate VS(valid symbol) = TU * Pclk * Bpp / (Lclk * Lanes)
	 * 3. अगर VS > *.85 or VS < *.1 or VS < 2 or TU < VS + 4, then set
	 *    TU += 2 and repeat 2nd step.
	 */
	करो अणु
		tu_size_reg += 2;
		symbol = tu_size_reg * mode->घड़ी * bit_per_pix;
		करो_भाग(symbol, dp->max_lanes * link_rate * 8);
		rem = करो_भाग(symbol, 1000);
		अगर (tu_size_reg > 64) अणु
			ret = -EINVAL;
			DRM_DEV_ERROR(dp->dev,
				      "tu error, clk:%d, lanes:%d, rate:%d\n",
				      mode->घड़ी, dp->max_lanes, link_rate);
			जाओ err_config_video;
		पूर्ण
	पूर्ण जबतक ((symbol <= 1) || (tu_size_reg - symbol < 4) ||
		 (rem > 850) || (rem < 100));

	val = symbol + (tu_size_reg << 8);
	val |= TU_CNT_RST_EN;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_FRAMER_TU, val);
	अगर (ret)
		जाओ err_config_video;

	/* set the FIFO Buffer size */
	val = भाग_u64(mode->घड़ी * (symbol + 1), 1000) + link_rate;
	val /= (dp->max_lanes * link_rate);
	val = भाग_u64(8 * (symbol + 1), bit_per_pix) - val;
	val += 2;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_VC_TABLE(15), val);

	चयन (video->color_depth) अणु
	हाल 6:
		val = BCS_6;
		अवरोध;
	हाल 8:
		val = BCS_8;
		अवरोध;
	हाल 10:
		val = BCS_10;
		अवरोध;
	हाल 12:
		val = BCS_12;
		अवरोध;
	हाल 16:
		val = BCS_16;
		अवरोध;
	पूर्ण

	val += video->color_fmt << 8;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_FRAMER_PXL_REPR, val);
	अगर (ret)
		जाओ err_config_video;

	val = video->h_sync_polarity ? DP_FRAMER_SP_HSP : 0;
	val |= video->v_sync_polarity ? DP_FRAMER_SP_VSP : 0;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_FRAMER_SP, val);
	अगर (ret)
		जाओ err_config_video;

	val = (mode->hsync_start - mode->hdisplay) << 16;
	val |= mode->htotal - mode->hsync_end;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_FRONT_BACK_PORCH, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->hdisplay * bit_per_pix / 8;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_BYTE_COUNT, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->htotal | ((mode->htotal - mode->hsync_start) << 16);
	ret = cdn_dp_reg_ग_लिखो(dp, MSA_HORIZONTAL_0, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->hsync_end - mode->hsync_start;
	val |= (mode->hdisplay << 16) | (video->h_sync_polarity << 15);
	ret = cdn_dp_reg_ग_लिखो(dp, MSA_HORIZONTAL_1, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->vtotal;
	val |= (mode->vtotal - mode->vsync_start) << 16;
	ret = cdn_dp_reg_ग_लिखो(dp, MSA_VERTICAL_0, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->vsync_end - mode->vsync_start;
	val |= (mode->vdisplay << 16) | (video->v_sync_polarity << 15);
	ret = cdn_dp_reg_ग_लिखो(dp, MSA_VERTICAL_1, val);
	अगर (ret)
		जाओ err_config_video;

	val = cdn_dp_get_msa_misc(video, mode);
	ret = cdn_dp_reg_ग_लिखो(dp, MSA_MISC, val);
	अगर (ret)
		जाओ err_config_video;

	ret = cdn_dp_reg_ग_लिखो(dp, STREAM_CONFIG, 1);
	अगर (ret)
		जाओ err_config_video;

	val = mode->hsync_end - mode->hsync_start;
	val |= mode->hdisplay << 16;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_HORIZONTAL, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->vdisplay;
	val |= (mode->vtotal - mode->vsync_start) << 16;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_VERTICAL_0, val);
	अगर (ret)
		जाओ err_config_video;

	val = mode->vtotal;
	ret = cdn_dp_reg_ग_लिखो(dp, DP_VERTICAL_1, val);
	अगर (ret)
		जाओ err_config_video;

	ret = cdn_dp_reg_ग_लिखो_bit(dp, DP_VB_ID, 2, 1, 0);

err_config_video:
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "config video failed: %d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक cdn_dp_audio_stop(काष्ठा cdn_dp_device *dp, काष्ठा audio_info *audio)
अणु
	पूर्णांक ret;

	ret = cdn_dp_reg_ग_लिखो(dp, AUDIO_PACK_CONTROL, 0);
	अगर (ret) अणु
		DRM_DEV_ERROR(dp->dev, "audio stop failed: %d\n", ret);
		वापस ret;
	पूर्ण

	ग_लिखोl(0, dp->regs + SPDIF_CTRL_ADDR);

	/* clearn the audio config and reset */
	ग_लिखोl(0, dp->regs + AUDIO_SRC_CNTL);
	ग_लिखोl(0, dp->regs + AUDIO_SRC_CNFG);
	ग_लिखोl(AUDIO_SW_RST, dp->regs + AUDIO_SRC_CNTL);
	ग_लिखोl(0, dp->regs + AUDIO_SRC_CNTL);

	/* reset smpl2pckt component  */
	ग_लिखोl(0, dp->regs + SMPL2PKT_CNTL);
	ग_लिखोl(AUDIO_SW_RST, dp->regs + SMPL2PKT_CNTL);
	ग_लिखोl(0, dp->regs + SMPL2PKT_CNTL);

	/* reset FIFO */
	ग_लिखोl(AUDIO_SW_RST, dp->regs + FIFO_CNTL);
	ग_लिखोl(0, dp->regs + FIFO_CNTL);

	अगर (audio->क्रमmat == AFMT_SPDIF)
		clk_disable_unprepare(dp->spdअगर_clk);

	वापस 0;
पूर्ण

पूर्णांक cdn_dp_audio_mute(काष्ठा cdn_dp_device *dp, bool enable)
अणु
	पूर्णांक ret;

	ret = cdn_dp_reg_ग_लिखो_bit(dp, DP_VB_ID, 4, 1, enable);
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "audio mute failed: %d\n", ret);

	वापस ret;
पूर्ण

अटल व्योम cdn_dp_audio_config_i2s(काष्ठा cdn_dp_device *dp,
				    काष्ठा audio_info *audio)
अणु
	पूर्णांक sub_pckt_num = 1, i2s_port_en_val = 0xf, i;
	u32 val;

	अगर (audio->channels == 2) अणु
		अगर (dp->max_lanes == 1)
			sub_pckt_num = 2;
		अन्यथा
			sub_pckt_num = 4;

		i2s_port_en_val = 1;
	पूर्ण अन्यथा अगर (audio->channels == 4) अणु
		i2s_port_en_val = 3;
	पूर्ण

	ग_लिखोl(0x0, dp->regs + SPDIF_CTRL_ADDR);

	ग_लिखोl(SYNC_WR_TO_CH_ZERO, dp->regs + FIFO_CNTL);

	val = MAX_NUM_CH(audio->channels);
	val |= NUM_OF_I2S_PORTS(audio->channels);
	val |= AUDIO_TYPE_LPCM;
	val |= CFG_SUB_PCKT_NUM(sub_pckt_num);
	ग_लिखोl(val, dp->regs + SMPL2PKT_CNFG);

	अगर (audio->sample_width == 16)
		val = 0;
	अन्यथा अगर (audio->sample_width == 24)
		val = 1 << 9;
	अन्यथा
		val = 2 << 9;

	val |= AUDIO_CH_NUM(audio->channels);
	val |= I2S_DEC_PORT_EN(i2s_port_en_val);
	val |= TRANS_SMPL_WIDTH_32;
	ग_लिखोl(val, dp->regs + AUDIO_SRC_CNFG);

	क्रम (i = 0; i < (audio->channels + 1) / 2; i++) अणु
		अगर (audio->sample_width == 16)
			val = (0x02 << 8) | (0x02 << 20);
		अन्यथा अगर (audio->sample_width == 24)
			val = (0x0b << 8) | (0x0b << 20);

		val |= ((2 * i) << 4) | ((2 * i + 1) << 16);
		ग_लिखोl(val, dp->regs + STTS_BIT_CH(i));
	पूर्ण

	चयन (audio->sample_rate) अणु
	हाल 32000:
		val = SAMPLING_FREQ(3) |
		      ORIGINAL_SAMP_FREQ(0xc);
		अवरोध;
	हाल 44100:
		val = SAMPLING_FREQ(0) |
		      ORIGINAL_SAMP_FREQ(0xf);
		अवरोध;
	हाल 48000:
		val = SAMPLING_FREQ(2) |
		      ORIGINAL_SAMP_FREQ(0xd);
		अवरोध;
	हाल 88200:
		val = SAMPLING_FREQ(8) |
		      ORIGINAL_SAMP_FREQ(0x7);
		अवरोध;
	हाल 96000:
		val = SAMPLING_FREQ(0xa) |
		      ORIGINAL_SAMP_FREQ(5);
		अवरोध;
	हाल 176400:
		val = SAMPLING_FREQ(0xc) |
		      ORIGINAL_SAMP_FREQ(3);
		अवरोध;
	हाल 192000:
		val = SAMPLING_FREQ(0xe) |
		      ORIGINAL_SAMP_FREQ(1);
		अवरोध;
	पूर्ण
	val |= 4;
	ग_लिखोl(val, dp->regs + COM_CH_STTS_BITS);

	ग_लिखोl(SMPL2PKT_EN, dp->regs + SMPL2PKT_CNTL);
	ग_लिखोl(I2S_DEC_START, dp->regs + AUDIO_SRC_CNTL);
पूर्ण

अटल व्योम cdn_dp_audio_config_spdअगर(काष्ठा cdn_dp_device *dp)
अणु
	u32 val;

	ग_लिखोl(SYNC_WR_TO_CH_ZERO, dp->regs + FIFO_CNTL);

	val = MAX_NUM_CH(2) | AUDIO_TYPE_LPCM | CFG_SUB_PCKT_NUM(4);
	ग_लिखोl(val, dp->regs + SMPL2PKT_CNFG);
	ग_लिखोl(SMPL2PKT_EN, dp->regs + SMPL2PKT_CNTL);

	val = SPDIF_ENABLE | SPDIF_AVG_SEL | SPDIF_JITTER_BYPASS;
	ग_लिखोl(val, dp->regs + SPDIF_CTRL_ADDR);

	clk_prepare_enable(dp->spdअगर_clk);
	clk_set_rate(dp->spdअगर_clk, CDN_DP_SPDIF_CLK);
पूर्ण

पूर्णांक cdn_dp_audio_config(काष्ठा cdn_dp_device *dp, काष्ठा audio_info *audio)
अणु
	पूर्णांक ret;

	/* reset the spdअगर clk beक्रमe config */
	अगर (audio->क्रमmat == AFMT_SPDIF) अणु
		reset_control_निश्चित(dp->spdअगर_rst);
		reset_control_deनिश्चित(dp->spdअगर_rst);
	पूर्ण

	ret = cdn_dp_reg_ग_लिखो(dp, CM_LANE_CTRL, LANE_REF_CYC);
	अगर (ret)
		जाओ err_audio_config;

	ret = cdn_dp_reg_ग_लिखो(dp, CM_CTRL, 0);
	अगर (ret)
		जाओ err_audio_config;

	अगर (audio->क्रमmat == AFMT_I2S)
		cdn_dp_audio_config_i2s(dp, audio);
	अन्यथा अगर (audio->क्रमmat == AFMT_SPDIF)
		cdn_dp_audio_config_spdअगर(dp);

	ret = cdn_dp_reg_ग_लिखो(dp, AUDIO_PACK_CONTROL, AUDIO_PACK_EN);

err_audio_config:
	अगर (ret)
		DRM_DEV_ERROR(dp->dev, "audio config failed: %d\n", ret);
	वापस ret;
पूर्ण
