<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_cmd_v5.c
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#समावेश "regs-mfc.h"
#समावेश "s5p_mfc_cmd.h"
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_cmd_v5.h"

/* This function is used to send a command to the MFC */
अटल पूर्णांक s5p_mfc_cmd_host2risc_v5(काष्ठा s5p_mfc_dev *dev, पूर्णांक cmd,
				काष्ठा s5p_mfc_cmd_args *args)
अणु
	पूर्णांक cur_cmd;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + msecs_to_jअगरfies(MFC_BW_TIMEOUT);
	/* रुको until host to risc command रेजिस्टर becomes 'H2R_CMD_EMPTY' */
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			mfc_err("Timeout while waiting for hardware\n");
			वापस -EIO;
		पूर्ण
		cur_cmd = mfc_पढ़ो(dev, S5P_FIMV_HOST2RISC_CMD);
	पूर्ण जबतक (cur_cmd != S5P_FIMV_H2R_CMD_EMPTY);
	mfc_ग_लिखो(dev, args->arg[0], S5P_FIMV_HOST2RISC_ARG1);
	mfc_ग_लिखो(dev, args->arg[1], S5P_FIMV_HOST2RISC_ARG2);
	mfc_ग_लिखो(dev, args->arg[2], S5P_FIMV_HOST2RISC_ARG3);
	mfc_ग_लिखो(dev, args->arg[3], S5P_FIMV_HOST2RISC_ARG4);
	/* Issue the command */
	mfc_ग_लिखो(dev, cmd, S5P_FIMV_HOST2RISC_CMD);
	वापस 0;
पूर्ण

/* Initialize the MFC */
अटल पूर्णांक s5p_mfc_sys_init_cmd_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_cmd_args h2r_args;

	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	h2r_args.arg[0] = dev->fw_buf.size;
	वापस s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_SYS_INIT,
			&h2r_args);
पूर्ण

/* Suspend the MFC hardware */
अटल पूर्णांक s5p_mfc_sleep_cmd_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_cmd_args h2r_args;

	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	वापस s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_SLEEP, &h2r_args);
पूर्ण

/* Wake up the MFC hardware */
अटल पूर्णांक s5p_mfc_wakeup_cmd_v5(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_cmd_args h2r_args;

	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	वापस s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_WAKEUP,
			&h2r_args);
पूर्ण


अटल पूर्णांक s5p_mfc_खोलो_inst_cmd_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_cmd_args h2r_args;
	पूर्णांक ret;

	/* Preparing decoding - getting instance number */
	mfc_debug(2, "Getting instance number (codec: %d)\n", ctx->codec_mode);
	dev->curr_ctx = ctx->num;
	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	चयन (ctx->codec_mode) अणु
	हाल S5P_MFC_CODEC_H264_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H264_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_VC1_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_MPEG4_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG2_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_MPEG2_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H263_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_VC1RCV_DEC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_VC1RCV_DEC;
		अवरोध;
	हाल S5P_MFC_CODEC_H264_ENC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H264_ENC;
		अवरोध;
	हाल S5P_MFC_CODEC_MPEG4_ENC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_MPEG4_ENC;
		अवरोध;
	हाल S5P_MFC_CODEC_H263_ENC:
		h2r_args.arg[0] = S5P_FIMV_CODEC_H263_ENC;
		अवरोध;
	शेष:
		h2r_args.arg[0] = S5P_FIMV_CODEC_NONE;
	पूर्ण
	h2r_args.arg[1] = 0; /* no crc & no pixelcache */
	h2r_args.arg[2] = ctx->ctx.ofs;
	h2r_args.arg[3] = ctx->ctx.size;
	ret = s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_OPEN_INSTANCE,
								&h2r_args);
	अगर (ret) अणु
		mfc_err("Failed to create a new instance\n");
		ctx->state = MFCINST_ERROR;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_mfc_बंद_inst_cmd_v5(काष्ठा s5p_mfc_ctx *ctx)
अणु
	काष्ठा s5p_mfc_dev *dev = ctx->dev;
	काष्ठा s5p_mfc_cmd_args h2r_args;
	पूर्णांक ret;

	अगर (ctx->state == MFCINST_FREE) अणु
		mfc_err("Instance already returned\n");
		ctx->state = MFCINST_ERROR;
		वापस -EINVAL;
	पूर्ण
	/* Closing decoding instance  */
	mfc_debug(2, "Returning instance number %d\n", ctx->inst_no);
	dev->curr_ctx = ctx->num;
	स_रखो(&h2r_args, 0, माप(काष्ठा s5p_mfc_cmd_args));
	h2r_args.arg[0] = ctx->inst_no;
	ret = s5p_mfc_cmd_host2risc_v5(dev, S5P_FIMV_H2R_CMD_CLOSE_INSTANCE,
								&h2r_args);
	अगर (ret) अणु
		mfc_err("Failed to return an instance\n");
		ctx->state = MFCINST_ERROR;
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* Initialize cmd function poपूर्णांकers क्रम MFC v5 */
अटल काष्ठा s5p_mfc_hw_cmds s5p_mfc_cmds_v5 = अणु
	.cmd_host2risc = s5p_mfc_cmd_host2risc_v5,
	.sys_init_cmd = s5p_mfc_sys_init_cmd_v5,
	.sleep_cmd = s5p_mfc_sleep_cmd_v5,
	.wakeup_cmd = s5p_mfc_wakeup_cmd_v5,
	.खोलो_inst_cmd = s5p_mfc_खोलो_inst_cmd_v5,
	.बंद_inst_cmd = s5p_mfc_बंद_inst_cmd_v5,
पूर्ण;

काष्ठा s5p_mfc_hw_cmds *s5p_mfc_init_hw_cmds_v5(व्योम)
अणु
	वापस &s5p_mfc_cmds_v5;
पूर्ण
