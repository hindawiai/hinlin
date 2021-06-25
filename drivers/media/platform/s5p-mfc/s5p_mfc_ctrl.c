<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_ctrl.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/firmware.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश "s5p_mfc_cmd.h"
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_intr.h"
#समावेश "s5p_mfc_opr.h"
#समावेश "s5p_mfc_pm.h"
#समावेश "s5p_mfc_ctrl.h"

/* Allocate memory क्रम firmware */
पूर्णांक s5p_mfc_alloc_firmware(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा s5p_mfc_priv_buf *fw_buf = &dev->fw_buf;
	पूर्णांक err;

	fw_buf->size = dev->variant->buf_size->fw;

	अगर (fw_buf->virt) अणु
		mfc_err("Attempting to allocate firmware when it seems that it is already loaded\n");
		वापस -ENOMEM;
	पूर्ण

	err = s5p_mfc_alloc_priv_buf(dev, BANK_L_CTX, &dev->fw_buf);
	अगर (err) अणु
		mfc_err("Allocating bitprocessor buffer failed\n");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* Load firmware */
पूर्णांक s5p_mfc_load_firmware(काष्ठा s5p_mfc_dev *dev)
अणु
	काष्ठा firmware *fw_blob;
	पूर्णांक i, err = -EINVAL;

	/* Firmware has to be present as a separate file or compiled
	 * पूर्णांकo kernel. */
	mfc_debug_enter();

	अगर (dev->fw_get_करोne)
		वापस 0;

	क्रम (i = MFC_FW_MAX_VERSIONS - 1; i >= 0; i--) अणु
		अगर (!dev->variant->fw_name[i])
			जारी;
		err = request_firmware((स्थिर काष्ठा firmware **)&fw_blob,
				dev->variant->fw_name[i], &dev->plat_dev->dev);
		अगर (!err) अणु
			dev->fw_ver = (क्रमागत s5p_mfc_fw_ver) i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err != 0) अणु
		mfc_err("Firmware is not present in the /lib/firmware directory nor compiled in kernel\n");
		वापस -EINVAL;
	पूर्ण
	अगर (fw_blob->size > dev->fw_buf.size) अणु
		mfc_err("MFC firmware is too big to be loaded\n");
		release_firmware(fw_blob);
		वापस -ENOMEM;
	पूर्ण
	स_नकल(dev->fw_buf.virt, fw_blob->data, fw_blob->size);
	wmb();
	dev->fw_get_करोne = true;
	release_firmware(fw_blob);
	mfc_debug_leave();
	वापस 0;
पूर्ण

/* Release firmware memory */
पूर्णांक s5p_mfc_release_firmware(काष्ठा s5p_mfc_dev *dev)
अणु
	/* Beक्रमe calling this function one has to make sure
	 * that MFC is no दीर्घer processing */
	s5p_mfc_release_priv_buf(dev, &dev->fw_buf);
	dev->fw_get_करोne = false;
	वापस 0;
पूर्ण

अटल पूर्णांक s5p_mfc_bus_reset(काष्ठा s5p_mfc_dev *dev)
अणु
	अचिन्हित पूर्णांक status;
	अचिन्हित दीर्घ समयout;

	/* Reset */
	mfc_ग_लिखो(dev, 0x1, S5P_FIMV_MFC_BUS_RESET_CTRL);
	समयout = jअगरfies + msecs_to_jअगरfies(MFC_BW_TIMEOUT);
	/* Check bus status */
	करो अणु
		अगर (समय_after(jअगरfies, समयout)) अणु
			mfc_err("Timeout while resetting MFC.\n");
			वापस -EIO;
		पूर्ण
		status = mfc_पढ़ो(dev, S5P_FIMV_MFC_BUS_RESET_CTRL);
	पूर्ण जबतक ((status & 0x2) == 0);
	वापस 0;
पूर्ण

/* Reset the device */
पूर्णांक s5p_mfc_reset(काष्ठा s5p_mfc_dev *dev)
अणु
	अचिन्हित पूर्णांक mc_status;
	अचिन्हित दीर्घ समयout;
	पूर्णांक i;

	mfc_debug_enter();

	अगर (IS_MFCV6_PLUS(dev)) अणु
		/* Zero Initialization of MFC रेजिस्टरs */
		mfc_ग_लिखो(dev, 0, S5P_FIMV_RISC2HOST_CMD_V6);
		mfc_ग_लिखो(dev, 0, S5P_FIMV_HOST2RISC_CMD_V6);
		mfc_ग_लिखो(dev, 0, S5P_FIMV_FW_VERSION_V6);

		क्रम (i = 0; i < S5P_FIMV_REG_CLEAR_COUNT_V6; i++)
			mfc_ग_लिखो(dev, 0, S5P_FIMV_REG_CLEAR_BEGIN_V6 + (i*4));

		/* check bus reset control beक्रमe reset */
		अगर (dev->risc_on)
			अगर (s5p_mfc_bus_reset(dev))
				वापस -EIO;
		/* Reset
		 * set RISC_ON to 0 during घातer_on & wake_up.
		 * V6 needs RISC_ON set to 0 during reset also.
		 */
		अगर ((!dev->risc_on) || (!IS_MFCV7_PLUS(dev)))
			mfc_ग_लिखो(dev, 0, S5P_FIMV_RISC_ON_V6);

		mfc_ग_लिखो(dev, 0x1FFF, S5P_FIMV_MFC_RESET_V6);
		mfc_ग_लिखो(dev, 0, S5P_FIMV_MFC_RESET_V6);
	पूर्ण अन्यथा अणु
		/* Stop procedure */
		/*  reset RISC */
		mfc_ग_लिखो(dev, 0x3f6, S5P_FIMV_SW_RESET);
		/*  All reset except क्रम MC */
		mfc_ग_लिखो(dev, 0x3e2, S5P_FIMV_SW_RESET);
		mdelay(10);

		समयout = jअगरfies + msecs_to_jअगरfies(MFC_BW_TIMEOUT);
		/* Check MC status */
		करो अणु
			अगर (समय_after(jअगरfies, समयout)) अणु
				mfc_err("Timeout while resetting MFC\n");
				वापस -EIO;
			पूर्ण

			mc_status = mfc_पढ़ो(dev, S5P_FIMV_MC_STATUS);

		पूर्ण जबतक (mc_status & 0x3);

		mfc_ग_लिखो(dev, 0x0, S5P_FIMV_SW_RESET);
		mfc_ग_लिखो(dev, 0x3fe, S5P_FIMV_SW_RESET);
	पूर्ण

	mfc_debug_leave();
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम s5p_mfc_init_memctrl(काष्ठा s5p_mfc_dev *dev)
अणु
	अगर (IS_MFCV6_PLUS(dev)) अणु
		mfc_ग_लिखो(dev, dev->dma_base[BANK_L_CTX],
			  S5P_FIMV_RISC_BASE_ADDRESS_V6);
		mfc_debug(2, "Base Address : %pad\n",
			  &dev->dma_base[BANK_L_CTX]);
	पूर्ण अन्यथा अणु
		mfc_ग_लिखो(dev, dev->dma_base[BANK_L_CTX],
			  S5P_FIMV_MC_DRAMBASE_ADR_A);
		mfc_ग_लिखो(dev, dev->dma_base[BANK_R_CTX],
			  S5P_FIMV_MC_DRAMBASE_ADR_B);
		mfc_debug(2, "Bank1: %pad, Bank2: %pad\n",
			  &dev->dma_base[BANK_L_CTX],
			  &dev->dma_base[BANK_R_CTX]);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम s5p_mfc_clear_cmds(काष्ठा s5p_mfc_dev *dev)
अणु
	अगर (IS_MFCV6_PLUS(dev)) अणु
		/* Zero initialization should be करोne beक्रमe RESET.
		 * Nothing to करो here. */
	पूर्ण अन्यथा अणु
		mfc_ग_लिखो(dev, 0xffffffff, S5P_FIMV_SI_CH0_INST_ID);
		mfc_ग_लिखो(dev, 0xffffffff, S5P_FIMV_SI_CH1_INST_ID);
		mfc_ग_लिखो(dev, 0, S5P_FIMV_RISC2HOST_CMD);
		mfc_ग_लिखो(dev, 0, S5P_FIMV_HOST2RISC_CMD);
	पूर्ण
पूर्ण

/* Initialize hardware */
पूर्णांक s5p_mfc_init_hw(काष्ठा s5p_mfc_dev *dev)
अणु
	अचिन्हित पूर्णांक ver;
	पूर्णांक ret;

	mfc_debug_enter();
	अगर (!dev->fw_buf.virt) अणु
		mfc_err("Firmware memory is not allocated.\n");
		वापस -EINVAL;
	पूर्ण

	/* 0. MFC reset */
	mfc_debug(2, "MFC reset..\n");
	s5p_mfc_घड़ी_on();
	dev->risc_on = 0;
	ret = s5p_mfc_reset(dev);
	अगर (ret) अणु
		mfc_err("Failed to reset MFC - timeout\n");
		वापस ret;
	पूर्ण
	mfc_debug(2, "Done MFC reset..\n");
	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);
	/* 2. Initialize रेजिस्टरs of channel I/F */
	s5p_mfc_clear_cmds(dev);
	/* 3. Release reset संकेत to the RISC */
	s5p_mfc_clean_dev_पूर्णांक_flags(dev);
	अगर (IS_MFCV6_PLUS(dev)) अणु
		dev->risc_on = 1;
		mfc_ग_लिखो(dev, 0x1, S5P_FIMV_RISC_ON_V6);
	पूर्ण
	अन्यथा
		mfc_ग_लिखो(dev, 0x3ff, S5P_FIMV_SW_RESET);

	अगर (IS_MFCV10(dev))
		mfc_ग_लिखो(dev, 0x0, S5P_FIMV_MFC_CLOCK_OFF_V10);

	mfc_debug(2, "Will now wait for completion of firmware transfer\n");
	अगर (s5p_mfc_रुको_क्रम_करोne_dev(dev, S5P_MFC_R2H_CMD_FW_STATUS_RET)) अणु
		mfc_err("Failed to load firmware\n");
		s5p_mfc_reset(dev);
		s5p_mfc_घड़ी_off();
		वापस -EIO;
	पूर्ण
	s5p_mfc_clean_dev_पूर्णांक_flags(dev);
	/* 4. Initialize firmware */
	ret = s5p_mfc_hw_call(dev->mfc_cmds, sys_init_cmd, dev);
	अगर (ret) अणु
		mfc_err("Failed to send command to MFC - timeout\n");
		s5p_mfc_reset(dev);
		s5p_mfc_घड़ी_off();
		वापस ret;
	पूर्ण
	mfc_debug(2, "Ok, now will wait for completion of hardware init\n");
	अगर (s5p_mfc_रुको_क्रम_करोne_dev(dev, S5P_MFC_R2H_CMD_SYS_INIT_RET)) अणु
		mfc_err("Failed to init hardware\n");
		s5p_mfc_reset(dev);
		s5p_mfc_घड़ी_off();
		वापस -EIO;
	पूर्ण
	dev->पूर्णांक_cond = 0;
	अगर (dev->पूर्णांक_err != 0 || dev->पूर्णांक_type !=
					S5P_MFC_R2H_CMD_SYS_INIT_RET) अणु
		/* Failure. */
		mfc_err("Failed to init firmware - error: %d int: %d\n",
						dev->पूर्णांक_err, dev->पूर्णांक_type);
		s5p_mfc_reset(dev);
		s5p_mfc_घड़ी_off();
		वापस -EIO;
	पूर्ण
	अगर (IS_MFCV6_PLUS(dev))
		ver = mfc_पढ़ो(dev, S5P_FIMV_FW_VERSION_V6);
	अन्यथा
		ver = mfc_पढ़ो(dev, S5P_FIMV_FW_VERSION);

	mfc_debug(2, "MFC F/W version : %02xyy, %02xmm, %02xdd\n",
		(ver >> 16) & 0xFF, (ver >> 8) & 0xFF, ver & 0xFF);
	s5p_mfc_घड़ी_off();
	mfc_debug_leave();
	वापस 0;
पूर्ण


/* Deinitialize hardware */
व्योम s5p_mfc_deinit_hw(काष्ठा s5p_mfc_dev *dev)
अणु
	s5p_mfc_घड़ी_on();

	s5p_mfc_reset(dev);
	s5p_mfc_hw_call(dev->mfc_ops, release_dev_context_buffer, dev);

	s5p_mfc_घड़ी_off();
पूर्ण

पूर्णांक s5p_mfc_sleep(काष्ठा s5p_mfc_dev *dev)
अणु
	पूर्णांक ret;

	mfc_debug_enter();
	s5p_mfc_घड़ी_on();
	s5p_mfc_clean_dev_पूर्णांक_flags(dev);
	ret = s5p_mfc_hw_call(dev->mfc_cmds, sleep_cmd, dev);
	अगर (ret) अणु
		mfc_err("Failed to send command to MFC - timeout\n");
		वापस ret;
	पूर्ण
	अगर (s5p_mfc_रुको_क्रम_करोne_dev(dev, S5P_MFC_R2H_CMD_SLEEP_RET)) अणु
		mfc_err("Failed to sleep\n");
		वापस -EIO;
	पूर्ण
	s5p_mfc_घड़ी_off();
	dev->पूर्णांक_cond = 0;
	अगर (dev->पूर्णांक_err != 0 || dev->पूर्णांक_type !=
						S5P_MFC_R2H_CMD_SLEEP_RET) अणु
		/* Failure. */
		mfc_err("Failed to sleep - error: %d int: %d\n", dev->पूर्णांक_err,
								dev->पूर्णांक_type);
		वापस -EIO;
	पूर्ण
	mfc_debug_leave();
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_mfc_v8_रुको_wakeup(काष्ठा s5p_mfc_dev *dev)
अणु
	पूर्णांक ret;

	/* Release reset संकेत to the RISC */
	dev->risc_on = 1;
	mfc_ग_लिखो(dev, 0x1, S5P_FIMV_RISC_ON_V6);

	अगर (s5p_mfc_रुको_क्रम_करोne_dev(dev, S5P_MFC_R2H_CMD_FW_STATUS_RET)) अणु
		mfc_err("Failed to reset MFCV8\n");
		वापस -EIO;
	पूर्ण
	mfc_debug(2, "Write command to wakeup MFCV8\n");
	ret = s5p_mfc_hw_call(dev->mfc_cmds, wakeup_cmd, dev);
	अगर (ret) अणु
		mfc_err("Failed to send command to MFCV8 - timeout\n");
		वापस ret;
	पूर्ण

	अगर (s5p_mfc_रुको_क्रम_करोne_dev(dev, S5P_MFC_R2H_CMD_WAKEUP_RET)) अणु
		mfc_err("Failed to wakeup MFC\n");
		वापस -EIO;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक s5p_mfc_रुको_wakeup(काष्ठा s5p_mfc_dev *dev)
अणु
	पूर्णांक ret;

	/* Send MFC wakeup command */
	ret = s5p_mfc_hw_call(dev->mfc_cmds, wakeup_cmd, dev);
	अगर (ret) अणु
		mfc_err("Failed to send command to MFC - timeout\n");
		वापस ret;
	पूर्ण

	/* Release reset संकेत to the RISC */
	अगर (IS_MFCV6_PLUS(dev)) अणु
		dev->risc_on = 1;
		mfc_ग_लिखो(dev, 0x1, S5P_FIMV_RISC_ON_V6);
	पूर्ण अन्यथा अणु
		mfc_ग_लिखो(dev, 0x3ff, S5P_FIMV_SW_RESET);
	पूर्ण

	अगर (s5p_mfc_रुको_क्रम_करोne_dev(dev, S5P_MFC_R2H_CMD_WAKEUP_RET)) अणु
		mfc_err("Failed to wakeup MFC\n");
		वापस -EIO;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक s5p_mfc_wakeup(काष्ठा s5p_mfc_dev *dev)
अणु
	पूर्णांक ret;

	mfc_debug_enter();
	/* 0. MFC reset */
	mfc_debug(2, "MFC reset..\n");
	s5p_mfc_घड़ी_on();
	dev->risc_on = 0;
	ret = s5p_mfc_reset(dev);
	अगर (ret) अणु
		mfc_err("Failed to reset MFC - timeout\n");
		s5p_mfc_घड़ी_off();
		वापस ret;
	पूर्ण
	mfc_debug(2, "Done MFC reset..\n");
	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);
	/* 2. Initialize रेजिस्टरs of channel I/F */
	s5p_mfc_clear_cmds(dev);
	s5p_mfc_clean_dev_पूर्णांक_flags(dev);
	/* 3. Send MFC wakeup command and रुको क्रम completion*/
	अगर (IS_MFCV8_PLUS(dev))
		ret = s5p_mfc_v8_रुको_wakeup(dev);
	अन्यथा
		ret = s5p_mfc_रुको_wakeup(dev);

	s5p_mfc_घड़ी_off();
	अगर (ret)
		वापस ret;

	dev->पूर्णांक_cond = 0;
	अगर (dev->पूर्णांक_err != 0 || dev->पूर्णांक_type !=
						S5P_MFC_R2H_CMD_WAKEUP_RET) अणु
		/* Failure. */
		mfc_err("Failed to wakeup - error: %d int: %d\n", dev->पूर्णांक_err,
								dev->पूर्णांक_type);
		वापस -EIO;
	पूर्ण
	mfc_debug_leave();
	वापस 0;
पूर्ण

पूर्णांक s5p_mfc_खोलो_mfc_inst(काष्ठा s5p_mfc_dev *dev, काष्ठा s5p_mfc_ctx *ctx)
अणु
	पूर्णांक ret = 0;

	ret = s5p_mfc_hw_call(dev->mfc_ops, alloc_instance_buffer, ctx);
	अगर (ret) अणु
		mfc_err("Failed allocating instance buffer\n");
		जाओ err;
	पूर्ण

	अगर (ctx->type == MFCINST_DECODER) अणु
		ret = s5p_mfc_hw_call(dev->mfc_ops,
					alloc_dec_temp_buffers, ctx);
		अगर (ret) अणु
			mfc_err("Failed allocating temporary buffers\n");
			जाओ err_मुक्त_inst_buf;
		पूर्ण
	पूर्ण

	set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
	अगर (s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
		S5P_MFC_R2H_CMD_OPEN_INSTANCE_RET, 0)) अणु
		/* Error or समयout */
		mfc_err("Error getting instance from hardware\n");
		ret = -EIO;
		जाओ err_मुक्त_desc_buf;
	पूर्ण

	mfc_debug(2, "Got instance number: %d\n", ctx->inst_no);
	वापस ret;

err_मुक्त_desc_buf:
	अगर (ctx->type == MFCINST_DECODER)
		s5p_mfc_hw_call(dev->mfc_ops, release_dec_desc_buffer, ctx);
err_मुक्त_inst_buf:
	s5p_mfc_hw_call(dev->mfc_ops, release_instance_buffer, ctx);
err:
	वापस ret;
पूर्ण

व्योम s5p_mfc_बंद_mfc_inst(काष्ठा s5p_mfc_dev *dev, काष्ठा s5p_mfc_ctx *ctx)
अणु
	ctx->state = MFCINST_RETURN_INST;
	set_work_bit_irqsave(ctx);
	s5p_mfc_hw_call(dev->mfc_ops, try_run, dev);
	/* Wait until instance is वापसed or समयout occurred */
	अगर (s5p_mfc_रुको_क्रम_करोne_ctx(ctx,
				S5P_MFC_R2H_CMD_CLOSE_INSTANCE_RET, 0))
		mfc_err("Err returning instance\n");

	/* Free resources */
	s5p_mfc_hw_call(dev->mfc_ops, release_codec_buffers, ctx);
	s5p_mfc_hw_call(dev->mfc_ops, release_instance_buffer, ctx);
	अगर (ctx->type == MFCINST_DECODER)
		s5p_mfc_hw_call(dev->mfc_ops, release_dec_desc_buffer, ctx);

	ctx->inst_no = MFC_NO_INSTANCE_SET;
	ctx->state = MFCINST_FREE;
पूर्ण
