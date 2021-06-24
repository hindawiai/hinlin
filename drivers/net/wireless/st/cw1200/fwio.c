<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Firmware I/O code क्रम mac80211 ST-Ericsson CW1200 drivers
 *
 * Copyright (c) 2010, ST-Ericsson
 * Author: Dmitry Tarnyagin <dmitry.tarnyagin@lockless.no>
 *
 * Based on:
 * ST-Ericsson UMAC CW1200 driver which is
 * Copyright (c) 2010, ST-Ericsson
 * Author: Ajitpal Singh <ajitpal.singh@stericsson.com>
 */

#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/sched.h>
#समावेश <linux/firmware.h>

#समावेश "cw1200.h"
#समावेश "fwio.h"
#समावेश "hwio.h"
#समावेश "hwbus.h"
#समावेश "bh.h"

अटल पूर्णांक cw1200_get_hw_type(u32 config_reg_val, पूर्णांक *major_revision)
अणु
	पूर्णांक hw_type = -1;
	u32 silicon_type = (config_reg_val >> 24) & 0x7;
	u32 silicon_vers = (config_reg_val >> 31) & 0x1;

	चयन (silicon_type) अणु
	हाल 0x00:
		*major_revision = 1;
		hw_type = HIF_9000_SILICON_VERSATILE;
		अवरोध;
	हाल 0x01:
	हाल 0x02: /* CW1x00 */
	हाल 0x04: /* CW1x60 */
		*major_revision = silicon_type;
		अगर (silicon_vers)
			hw_type = HIF_8601_VERSATILE;
		अन्यथा
			hw_type = HIF_8601_SILICON;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस hw_type;
पूर्ण

अटल पूर्णांक cw1200_load_firmware_cw1200(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret, block, num_blocks;
	अचिन्हित i;
	u32 val32;
	u32 put = 0, get = 0;
	u8 *buf = शून्य;
	स्थिर अक्षर *fw_path;
	स्थिर काष्ठा firmware *firmware = शून्य;

	/* Macroses are local. */
#घोषणा APB_WRITE(reg, val) \
	करो अणु \
		ret = cw1200_apb_ग_लिखो_32(priv, CW1200_APB(reg), (val)); \
		अगर (ret < 0) \
			जाओ निकास; \
	पूर्ण जबतक (0)
#घोषणा APB_WRITE2(reg, val) \
	करो अणु \
		ret = cw1200_apb_ग_लिखो_32(priv, CW1200_APB(reg), (val)); \
		अगर (ret < 0) \
			जाओ मुक्त_buffer; \
	पूर्ण जबतक (0)
#घोषणा APB_READ(reg, val) \
	करो अणु \
		ret = cw1200_apb_पढ़ो_32(priv, CW1200_APB(reg), &(val)); \
		अगर (ret < 0) \
			जाओ मुक्त_buffer; \
	पूर्ण जबतक (0)
#घोषणा REG_WRITE(reg, val) \
	करो अणु \
		ret = cw1200_reg_ग_लिखो_32(priv, (reg), (val)); \
		अगर (ret < 0) \
			जाओ निकास; \
	पूर्ण जबतक (0)
#घोषणा REG_READ(reg, val) \
	करो अणु \
		ret = cw1200_reg_पढ़ो_32(priv, (reg), &(val)); \
		अगर (ret < 0) \
			जाओ निकास; \
	पूर्ण जबतक (0)

	चयन (priv->hw_revision) अणु
	हाल CW1200_HW_REV_CUT10:
		fw_path = FIRMWARE_CUT10;
		अगर (!priv->sdd_path)
			priv->sdd_path = SDD_खाता_10;
		अवरोध;
	हाल CW1200_HW_REV_CUT11:
		fw_path = FIRMWARE_CUT11;
		अगर (!priv->sdd_path)
			priv->sdd_path = SDD_खाता_11;
		अवरोध;
	हाल CW1200_HW_REV_CUT20:
		fw_path = FIRMWARE_CUT20;
		अगर (!priv->sdd_path)
			priv->sdd_path = SDD_खाता_20;
		अवरोध;
	हाल CW1200_HW_REV_CUT22:
		fw_path = FIRMWARE_CUT22;
		अगर (!priv->sdd_path)
			priv->sdd_path = SDD_खाता_22;
		अवरोध;
	हाल CW1X60_HW_REV:
		fw_path = FIRMWARE_CW1X60;
		अगर (!priv->sdd_path)
			priv->sdd_path = SDD_खाता_CW1X60;
		अवरोध;
	शेष:
		pr_err("Invalid silicon revision %d.\n", priv->hw_revision);
		वापस -EINVAL;
	पूर्ण

	/* Initialize common रेजिस्टरs */
	APB_WRITE(DOWNLOAD_IMAGE_SIZE_REG, DOWNLOAD_ARE_YOU_HERE);
	APB_WRITE(DOWNLOAD_PUT_REG, 0);
	APB_WRITE(DOWNLOAD_GET_REG, 0);
	APB_WRITE(DOWNLOAD_STATUS_REG, DOWNLOAD_PENDING);
	APB_WRITE(DOWNLOAD_FLAGS_REG, 0);

	/* Write the NOP Inकाष्ठाion */
	REG_WRITE(ST90TDS_SRAM_BASE_ADDR_REG_ID, 0xFFF20000);
	REG_WRITE(ST90TDS_AHB_DPORT_REG_ID, 0xEAFFFFFE);

	/* Release CPU from RESET */
	REG_READ(ST90TDS_CONFIG_REG_ID, val32);
	val32 &= ~ST90TDS_CONFIG_CPU_RESET_BIT;
	REG_WRITE(ST90TDS_CONFIG_REG_ID, val32);

	/* Enable Clock */
	val32 &= ~ST90TDS_CONFIG_CPU_CLK_DIS_BIT;
	REG_WRITE(ST90TDS_CONFIG_REG_ID, val32);

	/* Load a firmware file */
	ret = request_firmware(&firmware, fw_path, priv->pdev);
	अगर (ret) अणु
		pr_err("Can't load firmware file %s.\n", fw_path);
		जाओ निकास;
	पूर्ण

	buf = kदो_स्मृति(DOWNLOAD_BLOCK_SIZE, GFP_KERNEL | GFP_DMA);
	अगर (!buf) अणु
		pr_err("Can't allocate firmware load buffer.\n");
		ret = -ENOMEM;
		जाओ firmware_release;
	पूर्ण

	/* Check अगर the bootloader is पढ़ोy */
	क्रम (i = 0; i < 100; i += 1 + i / 2) अणु
		APB_READ(DOWNLOAD_IMAGE_SIZE_REG, val32);
		अगर (val32 == DOWNLOAD_I_AM_HERE)
			अवरोध;
		mdelay(i);
	पूर्ण /* End of क्रम loop */

	अगर (val32 != DOWNLOAD_I_AM_HERE) अणु
		pr_err("Bootloader is not ready.\n");
		ret = -ETIMEDOUT;
		जाओ मुक्त_buffer;
	पूर्ण

	/* Calculcate number of करोwnload blocks */
	num_blocks = (firmware->size - 1) / DOWNLOAD_BLOCK_SIZE + 1;

	/* Updating the length in Download Ctrl Area */
	val32 = firmware->size; /* Explicit cast from माप_प्रकार to u32 */
	APB_WRITE2(DOWNLOAD_IMAGE_SIZE_REG, val32);

	/* Firmware करोwnloading loop */
	क्रम (block = 0; block < num_blocks; block++) अणु
		माप_प्रकार tx_size;
		माप_प्रकार block_size;

		/* check the करोwnload status */
		APB_READ(DOWNLOAD_STATUS_REG, val32);
		अगर (val32 != DOWNLOAD_PENDING) अणु
			pr_err("Bootloader reported error %d.\n", val32);
			ret = -EIO;
			जाओ मुक्त_buffer;
		पूर्ण

		/* loop until put - get <= 24K */
		क्रम (i = 0; i < 100; i++) अणु
			APB_READ(DOWNLOAD_GET_REG, get);
			अगर ((put - get) <=
			    (DOWNLOAD_FIFO_SIZE - DOWNLOAD_BLOCK_SIZE))
				अवरोध;
			mdelay(i);
		पूर्ण

		अगर ((put - get) > (DOWNLOAD_FIFO_SIZE - DOWNLOAD_BLOCK_SIZE)) अणु
			pr_err("Timeout waiting for FIFO.\n");
			ret = -ETIMEDOUT;
			जाओ मुक्त_buffer;
		पूर्ण

		/* calculate the block size */
		tx_size = block_size = min_t(माप_प्रकार, firmware->size - put,
					DOWNLOAD_BLOCK_SIZE);

		स_नकल(buf, &firmware->data[put], block_size);
		अगर (block_size < DOWNLOAD_BLOCK_SIZE) अणु
			स_रखो(&buf[block_size], 0,
			       DOWNLOAD_BLOCK_SIZE - block_size);
			tx_size = DOWNLOAD_BLOCK_SIZE;
		पूर्ण

		/* send the block to sram */
		ret = cw1200_apb_ग_लिखो(priv,
			CW1200_APB(DOWNLOAD_FIFO_OFFSET +
				   (put & (DOWNLOAD_FIFO_SIZE - 1))),
			buf, tx_size);
		अगर (ret < 0) अणु
			pr_err("Can't write firmware block @ %d!\n",
			       put & (DOWNLOAD_FIFO_SIZE - 1));
			जाओ मुक्त_buffer;
		पूर्ण

		/* update the put रेजिस्टर */
		put += block_size;
		APB_WRITE2(DOWNLOAD_PUT_REG, put);
	पूर्ण /* End of firmware करोwnload loop */

	/* Wait क्रम the करोwnload completion */
	क्रम (i = 0; i < 300; i += 1 + i / 2) अणु
		APB_READ(DOWNLOAD_STATUS_REG, val32);
		अगर (val32 != DOWNLOAD_PENDING)
			अवरोध;
		mdelay(i);
	पूर्ण
	अगर (val32 != DOWNLOAD_SUCCESS) अणु
		pr_err("Wait for download completion failed: 0x%.8X\n", val32);
		ret = -ETIMEDOUT;
		जाओ मुक्त_buffer;
	पूर्ण अन्यथा अणु
		pr_info("Firmware download completed.\n");
		ret = 0;
	पूर्ण

मुक्त_buffer:
	kमुक्त(buf);
firmware_release:
	release_firmware(firmware);
निकास:
	वापस ret;

#अघोषित APB_WRITE
#अघोषित APB_WRITE2
#अघोषित APB_READ
#अघोषित REG_WRITE
#अघोषित REG_READ
पूर्ण


अटल पूर्णांक config_reg_पढ़ो(काष्ठा cw1200_common *priv, u32 *val)
अणु
	चयन (priv->hw_type) अणु
	हाल HIF_9000_SILICON_VERSATILE: अणु
		u16 val16;
		पूर्णांक ret = cw1200_reg_पढ़ो_16(priv,
					     ST90TDS_CONFIG_REG_ID,
					     &val16);
		अगर (ret < 0)
			वापस ret;
		*val = val16;
		वापस 0;
	पूर्ण
	हाल HIF_8601_VERSATILE:
	हाल HIF_8601_SILICON:
	शेष:
		cw1200_reg_पढ़ो_32(priv, ST90TDS_CONFIG_REG_ID, val);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक config_reg_ग_लिखो(काष्ठा cw1200_common *priv, u32 val)
अणु
	चयन (priv->hw_type) अणु
	हाल HIF_9000_SILICON_VERSATILE:
		वापस cw1200_reg_ग_लिखो_16(priv,
					   ST90TDS_CONFIG_REG_ID,
					   (u16)val);
	हाल HIF_8601_VERSATILE:
	हाल HIF_8601_SILICON:
	शेष:
		वापस cw1200_reg_ग_लिखो_32(priv, ST90TDS_CONFIG_REG_ID, val);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक cw1200_load_firmware(काष्ठा cw1200_common *priv)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	u32 val32;
	u16 val16;
	पूर्णांक major_revision = -1;

	/* Read CONFIG Register */
	ret = cw1200_reg_पढ़ो_32(priv, ST90TDS_CONFIG_REG_ID, &val32);
	अगर (ret < 0) अणु
		pr_err("Can't read config register.\n");
		जाओ out;
	पूर्ण

	अगर (val32 == 0 || val32 == 0xffffffff) अणु
		pr_err("Bad config register value (0x%08x)\n", val32);
		ret = -EIO;
		जाओ out;
	पूर्ण

	ret = cw1200_get_hw_type(val32, &major_revision);
	अगर (ret < 0) अणु
		pr_err("Can't deduce hardware type.\n");
		जाओ out;
	पूर्ण
	priv->hw_type = ret;

	/* Set DPLL Reg value, and पढ़ो back to confirm ग_लिखोs work */
	ret = cw1200_reg_ग_लिखो_32(priv, ST90TDS_TSET_GEN_R_W_REG_ID,
				  cw1200_dpll_from_clk(priv->hw_refclk));
	अगर (ret < 0) अणु
		pr_err("Can't write DPLL register.\n");
		जाओ out;
	पूर्ण

	msleep(20);

	ret = cw1200_reg_पढ़ो_32(priv,
		ST90TDS_TSET_GEN_R_W_REG_ID, &val32);
	अगर (ret < 0) अणु
		pr_err("Can't read DPLL register.\n");
		जाओ out;
	पूर्ण

	अगर (val32 != cw1200_dpll_from_clk(priv->hw_refclk)) अणु
		pr_err("Unable to initialise DPLL register. Wrote 0x%.8X, Read 0x%.8X.\n",
		       cw1200_dpll_from_clk(priv->hw_refclk), val32);
		ret = -EIO;
		जाओ out;
	पूर्ण

	/* Set wakeup bit in device */
	ret = cw1200_reg_पढ़ो_16(priv, ST90TDS_CONTROL_REG_ID, &val16);
	अगर (ret < 0) अणु
		pr_err("set_wakeup: can't read control register.\n");
		जाओ out;
	पूर्ण

	ret = cw1200_reg_ग_लिखो_16(priv, ST90TDS_CONTROL_REG_ID,
		val16 | ST90TDS_CONT_WUP_BIT);
	अगर (ret < 0) अणु
		pr_err("set_wakeup: can't write control register.\n");
		जाओ out;
	पूर्ण

	/* Wait क्रम wakeup */
	क्रम (i = 0; i < 300; i += (1 + i / 2)) अणु
		ret = cw1200_reg_पढ़ो_16(priv,
			ST90TDS_CONTROL_REG_ID, &val16);
		अगर (ret < 0) अणु
			pr_err("wait_for_wakeup: can't read control register.\n");
			जाओ out;
		पूर्ण

		अगर (val16 & ST90TDS_CONT_RDY_BIT)
			अवरोध;

		msleep(i);
	पूर्ण

	अगर ((val16 & ST90TDS_CONT_RDY_BIT) == 0) अणु
		pr_err("wait_for_wakeup: device is not responding.\n");
		ret = -ETIMEDOUT;
		जाओ out;
	पूर्ण

	चयन (major_revision) अणु
	हाल 1:
		/* CW1200 Hardware detection logic : Check क्रम CUT1.1 */
		ret = cw1200_ahb_पढ़ो_32(priv, CW1200_CUT_ID_ADDR, &val32);
		अगर (ret) अणु
			pr_err("HW detection: can't read CUT ID.\n");
			जाओ out;
		पूर्ण

		चयन (val32) अणु
		हाल CW1200_CUT_11_ID_STR:
			pr_info("CW1x00 Cut 1.1 silicon detected.\n");
			priv->hw_revision = CW1200_HW_REV_CUT11;
			अवरोध;
		शेष:
			pr_info("CW1x00 Cut 1.0 silicon detected.\n");
			priv->hw_revision = CW1200_HW_REV_CUT10;
			अवरोध;
		पूर्ण

		/* According to ST-E, CUT<2.0 has busted BA TID0-3.
		   Just disable it entirely...
		*/
		priv->ba_rx_tid_mask = 0;
		priv->ba_tx_tid_mask = 0;
		अवरोध;
	हाल 2: अणु
		u32 ar1, ar2, ar3;
		ret = cw1200_ahb_पढ़ो_32(priv, CW1200_CUT2_ID_ADDR, &ar1);
		अगर (ret) अणु
			pr_err("(1) HW detection: can't read CUT ID\n");
			जाओ out;
		पूर्ण
		ret = cw1200_ahb_पढ़ो_32(priv, CW1200_CUT2_ID_ADDR + 4, &ar2);
		अगर (ret) अणु
			pr_err("(2) HW detection: can't read CUT ID.\n");
			जाओ out;
		पूर्ण

		ret = cw1200_ahb_पढ़ो_32(priv, CW1200_CUT2_ID_ADDR + 8, &ar3);
		अगर (ret) अणु
			pr_err("(3) HW detection: can't read CUT ID.\n");
			जाओ out;
		पूर्ण

		अगर (ar1 == CW1200_CUT_22_ID_STR1 &&
		    ar2 == CW1200_CUT_22_ID_STR2 &&
		    ar3 == CW1200_CUT_22_ID_STR3) अणु
			pr_info("CW1x00 Cut 2.2 silicon detected.\n");
			priv->hw_revision = CW1200_HW_REV_CUT22;
		पूर्ण अन्यथा अणु
			pr_info("CW1x00 Cut 2.0 silicon detected.\n");
			priv->hw_revision = CW1200_HW_REV_CUT20;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल 4:
		pr_info("CW1x60 silicon detected.\n");
		priv->hw_revision = CW1X60_HW_REV;
		अवरोध;
	शेष:
		pr_err("Unsupported silicon major revision %d.\n",
		       major_revision);
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण

	/* Checking क्रम access mode */
	ret = config_reg_पढ़ो(priv, &val32);
	अगर (ret < 0) अणु
		pr_err("Can't read config register.\n");
		जाओ out;
	पूर्ण

	अगर (!(val32 & ST90TDS_CONFIG_ACCESS_MODE_BIT)) अणु
		pr_err("Device is already in QUEUE mode!\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	चयन (priv->hw_type)  अणु
	हाल HIF_8601_SILICON:
		अगर (priv->hw_revision == CW1X60_HW_REV) अणु
			pr_err("Can't handle CW1160/1260 firmware load yet.\n");
			ret = -ENOTSUPP;
			जाओ out;
		पूर्ण
		ret = cw1200_load_firmware_cw1200(priv);
		अवरोध;
	शेष:
		pr_err("Can't perform firmware load for hw type %d.\n",
		       priv->hw_type);
		ret = -ENOTSUPP;
		जाओ out;
	पूर्ण
	अगर (ret < 0) अणु
		pr_err("Firmware load error.\n");
		जाओ out;
	पूर्ण

	/* Enable पूर्णांकerrupt संकेतling */
	priv->hwbus_ops->lock(priv->hwbus_priv);
	ret = __cw1200_irq_enable(priv, 1);
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	अगर (ret < 0)
		जाओ unsubscribe;

	/* Configure device क्रम MESSSAGE MODE */
	ret = config_reg_पढ़ो(priv, &val32);
	अगर (ret < 0) अणु
		pr_err("Can't read config register.\n");
		जाओ unsubscribe;
	पूर्ण
	ret = config_reg_ग_लिखो(priv, val32 & ~ST90TDS_CONFIG_ACCESS_MODE_BIT);
	अगर (ret < 0) अणु
		pr_err("Can't write config register.\n");
		जाओ unsubscribe;
	पूर्ण

	/* Unless we पढ़ो the CONFIG Register we are
	 * not able to get an पूर्णांकerrupt
	 */
	mdelay(10);
	config_reg_पढ़ो(priv, &val32);

out:
	वापस ret;

unsubscribe:
	/* Disable पूर्णांकerrupt संकेतling */
	priv->hwbus_ops->lock(priv->hwbus_priv);
	ret = __cw1200_irq_enable(priv, 0);
	priv->hwbus_ops->unlock(priv->hwbus_priv);
	वापस ret;
पूर्ण
