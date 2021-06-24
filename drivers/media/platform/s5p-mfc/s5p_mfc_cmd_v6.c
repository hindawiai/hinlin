<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_cmd_v6.c
 *
 * Copyright (c) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#समावेश "s5p_mfc_common.h"

#समावेश "s5p_mfc_cmd.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_intr.h"
#समावेश "s5p_mfc_opr.h"
#समावेश "s5p_mfc_cmd_v6.h"

अटल पूर्णांक s5p_mfc_cmd_host2risc_v6(काष्ठा s5p_mfc_dev *dev, पूर्णांक cmd,
				काष्ठा s5p_mfc_cmd_args *args)
अणु
	mfc_debug(2, "Issue the command: %d\n", cmd);

	/* Reset RISC2HOST command */
	mfc_ग_लिखो(dev, 0x0, S5P_FIMV_RISC2HOST_CMD_V6);

	/* Issue the command */
	mfc_ग_लिखो(dev, cmd, S5P_FIMV_HOST2RISC_CMD_V6);
	mfc_ग_लिखो(dev, 0x1, S5P_FIMV_HOST2RISC_INT_V6);

	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_sys_init_cmd_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_cmd_args h2r_args;
	काष्ठा s5p_mfc_buf_size_v6 *buf_size = dev->variant->buf_size->priv;
	पूर्णांक ret;

	ret = s5p_mfc_hw_call(dev->mfc_ops, alloc_dev_context_buffer, dev);
	अगर (ret)
		वापस ret;

	mfc_ग_लिखो(dev, dev->ctx_buf.dma, S5P_FIMV_CONTEXT_MEM_ADDR_V6);
	mfc_ग_लिखो(dev, buf_size->dev_ctx, S5P_FIMV_CONTEXT_MEM_SIZE_V6);
	वापस s5p_mfc_cmd_host2risc_v6(dev, S5P_FIMV_H2R_CMD_SYS_INIT_V6,
					&h2r_args);
पूर्ण

अटल पूर्णांक s5p_mfc_sleep_cmd_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_cmd_args h2r_args;

	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	वापस s5p_mfc_cmd_host2risc_v6(dev, S5P_FIMV_H2R_CMD_SLEEP_V6,
			&h2r_args);
पूर्ण

अटल पूर्णांक s5p_mfc_wakeup_cmd_v6(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_cmd_args h2r_args;

	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	वापस s5p_mfc_cmd_host2risc_v6(dev, S5P_FIMV_H2R_CMD_WAKEUP_V6,
					&h2r_args);
पूर्ण

/* Open a new instance and get its number */
अटल पूर्णांक s5p_mfc_खोलो_inst_cmd_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_cmd_args h2r_args;
	पूर्णांक codec_type;

	mfc_debug(2, "Requested codec mode: %d\n", ctx->codec_mode);
	dev->curr_ctx = ctx->num;
	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_DEC:
		codec_type = S5P_FIMV_CODEC_H264_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_MVC_DEC:
		codec_type = S5P_FIMV_CODEC_H264_MVC_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1_DEC:
		codec_type = S5P_FIMV_CODEC_VC1_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_DEC:
		codec_type = S5P_FIMV_CODEC_MPEG4_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG2_DEC:
		codec_type = S5P_FIMV_CODEC_MPEG2_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_DEC:
		codec_type = S5P_FIMV_CODEC_H263_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1RCV_DEC:
		codec_type = S5P_FIMV_CODEC_VC1RCV_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_VP8_DEC:
		codec_type = S5P_FIMV_CODEC_VP8_DEC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_HEVC_DEC:
		codec_type = S5P_FIMV_CODEC_HEVC_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_VP9_DEC:
		codec_type = S5P_FIMV_CODEC_VP9_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_ENC:
		codec_type = S5P_FIMV_CODEC_H264_ENC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_MVC_ENC:
		codec_type = S5P_FIMV_CODEC_H264_MVC_ENC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_ENC:
		codec_type = S5P_FIMV_CODEC_MPEG4_ENC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_ENC:
		codec_type = S5P_FIMV_CODEC_H263_ENC_V6;
		अवरोध;
	हाल S5P_MFC_CODEC_VP8_ENC:
		codec_type = S5P_FIMV_CODEC_VP8_ENC_V7;
		अवरोध;
	हाल S5P_MFC_CODEC_HEVC_ENC:
		codec_type = S5P_FIMV_CODEC_HEVC_ENC;
		अवरोध;
	शेष:
		codec_type = S5P_FIMV_CODEC_NONE_V6;
	पूर्ण
	mfc_ग_लिखो(dev, codec_type, S5P_FIMV_CODEC_TYPE_V6);
	mfc_ग_लिखो(dev, ctx->ctx.dma, S5P_FIMV_CONTEXT_MEM_ADDR_V6);
	mfc_ग_लिखो(dev, ctx->ctx.size, S5P_FIMV_CONTEXT_MEM_SIZE_V6);
	mfc_ग_लिखो(dev, 0, S5P_FIMV_D_CRC_CTRL_V6); /* no crc */

	वापस s5p_mfc_cmd_host2risc_v6(dev, S5P_FIMV_H2R_CMD_OPEN_INSTANCE_V6,
					&h2r_args);
पूर्ण

/* Close instance */
अटल पूर्णांक s5p_mfc_बंद_inst_cmd_v6(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_cmd_args h2r_args;
	पूर्णांक ret = 0;

	dev->curr_ctx = ctx->num;
	अगर (ctx->state != MFCINST_FREE) अणु
		mfc_ग_लिखो(dev, ctx->inst_no, S5P_FIMV_INSTANCE_ID_V6);
		ret = s5p_mfc_cmd_host2risc_v6(dev,
					S5P_FIMV_H2R_CMD_CLOSE_INSTANCE_V6,
					&h2r_args);
	पूर्ण अन्यथा अणु
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

/* Initialize cmd function poपूर्णांकers क्रम MFC v6 */
अटल काष्ठा s5p_mfc_hw_cmds s5p_mfc_cmds_v6 = अणु
	.cmd_host2risc = s5p_mfc_cmd_host2risc_v6,
	.sys_init_cmd = s5p_mfc_sys_init_cmd_v6,
	.sleep_cmd = s5p_mfc_sleep_cmd_v6,
	.wakeup_cmd = s5p_mfc_wakeup_cmd_v6,
	.खोलो_inst_cmd = s5p_mfc_खोलो_inst_cmd_v6,
	.बंद_inst_cmd = s5p_mfc_बंद_inst_cmd_v6,
पूर्ण;

काष्ठा s5p_mfc_hw_cmds *s5p_mfc_init_hw_cmds_v6(व्योम)
अणु
	वापस &s5p_mfc_cmds_v6;
पूर्ण
