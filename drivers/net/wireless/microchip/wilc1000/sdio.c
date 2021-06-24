<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#समावेश <linux/clk.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/of_irq.h>

#समावेश "netdev.h"
#समावेश "cfg80211.h"

#घोषणा SDIO_MODALIAS "wilc1000_sdio"

अटल स्थिर काष्ठा sdio_device_id wilc_sdio_ids[] = अणु
	अणु SDIO_DEVICE(SDIO_VENDOR_ID_MICROCHIP_WILC, SDIO_DEVICE_ID_MICROCHIP_WILC1000) पूर्ण,
	अणु पूर्ण,
पूर्ण;

#घोषणा WILC_SDIO_BLOCK_SIZE 512

काष्ठा wilc_sdio अणु
	bool irq_gpio;
	u32 block_size;
	पूर्णांक has_thrpt_enh3;
पूर्ण;

काष्ठा sdio_cmd52 अणु
	u32 पढ़ो_ग_लिखो:		1;
	u32 function:		3;
	u32 raw:		1;
	u32 address:		17;
	u32 data:		8;
पूर्ण;

काष्ठा sdio_cmd53 अणु
	u32 पढ़ो_ग_लिखो:		1;
	u32 function:		3;
	u32 block_mode:		1;
	u32 increment:		1;
	u32 address:		17;
	u32 count:		9;
	u8 *buffer;
	u32 block_size;
पूर्ण;

अटल स्थिर काष्ठा wilc_hअगर_func wilc_hअगर_sdio;

अटल व्योम wilc_sdio_पूर्णांकerrupt(काष्ठा sdio_func *func)
अणु
	sdio_release_host(func);
	wilc_handle_isr(sdio_get_drvdata(func));
	sdio_claim_host(func);
पूर्ण

अटल पूर्णांक wilc_sdio_cmd52(काष्ठा wilc *wilc, काष्ठा sdio_cmd52 *cmd)
अणु
	काष्ठा sdio_func *func = container_of(wilc->dev, काष्ठा sdio_func, dev);
	पूर्णांक ret;
	u8 data;

	sdio_claim_host(func);

	func->num = cmd->function;
	अगर (cmd->पढ़ो_ग_लिखो) अणु  /* ग_लिखो */
		अगर (cmd->raw) अणु
			sdio_ग_लिखोb(func, cmd->data, cmd->address, &ret);
			data = sdio_पढ़ोb(func, cmd->address, &ret);
			cmd->data = data;
		पूर्ण अन्यथा अणु
			sdio_ग_लिखोb(func, cmd->data, cmd->address, &ret);
		पूर्ण
	पूर्ण अन्यथा अणु        /* पढ़ो */
		data = sdio_पढ़ोb(func, cmd->address, &ret);
		cmd->data = data;
	पूर्ण

	sdio_release_host(func);

	अगर (ret)
		dev_err(&func->dev, "%s..failed, err(%d)\n", __func__, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक wilc_sdio_cmd53(काष्ठा wilc *wilc, काष्ठा sdio_cmd53 *cmd)
अणु
	काष्ठा sdio_func *func = container_of(wilc->dev, काष्ठा sdio_func, dev);
	पूर्णांक size, ret;

	sdio_claim_host(func);

	func->num = cmd->function;
	func->cur_blksize = cmd->block_size;
	अगर (cmd->block_mode)
		size = cmd->count * cmd->block_size;
	अन्यथा
		size = cmd->count;

	अगर (cmd->पढ़ो_ग_लिखो) अणु  /* ग_लिखो */
		ret = sdio_स_नकल_toio(func, cmd->address,
				       (व्योम *)cmd->buffer, size);
	पूर्ण अन्यथा अणु        /* पढ़ो */
		ret = sdio_स_नकल_fromio(func, (व्योम *)cmd->buffer,
					 cmd->address,  size);
	पूर्ण

	sdio_release_host(func);

	अगर (ret)
		dev_err(&func->dev, "%s..failed, err(%d)\n", __func__,  ret);

	वापस ret;
पूर्ण

अटल पूर्णांक wilc_sdio_probe(काष्ठा sdio_func *func,
			   स्थिर काष्ठा sdio_device_id *id)
अणु
	काष्ठा wilc *wilc;
	पूर्णांक ret;
	काष्ठा wilc_sdio *sdio_priv;

	sdio_priv = kzalloc(माप(*sdio_priv), GFP_KERNEL);
	अगर (!sdio_priv)
		वापस -ENOMEM;

	ret = wilc_cfg80211_init(&wilc, &func->dev, WILC_HIF_SDIO,
				 &wilc_hअगर_sdio);
	अगर (ret) अणु
		kमुक्त(sdio_priv);
		वापस ret;
	पूर्ण

	अगर (IS_ENABLED(CONFIG_WILC1000_HW_OOB_INTR)) अणु
		काष्ठा device_node *np = func->card->dev.of_node;
		पूर्णांक irq_num = of_irq_get(np, 0);

		अगर (irq_num > 0) अणु
			wilc->dev_irq_num = irq_num;
			sdio_priv->irq_gpio = true;
		पूर्ण
	पूर्ण

	sdio_set_drvdata(func, wilc);
	wilc->bus_data = sdio_priv;
	wilc->dev = &func->dev;

	wilc->rtc_clk = devm_clk_get(&func->card->dev, "rtc");
	अगर (PTR_ERR_OR_ZERO(wilc->rtc_clk) == -EPROBE_DEFER) अणु
		kमुक्त(sdio_priv);
		वापस -EPROBE_DEFER;
	पूर्ण अन्यथा अगर (!IS_ERR(wilc->rtc_clk))
		clk_prepare_enable(wilc->rtc_clk);

	dev_info(&func->dev, "Driver Initializing success\n");
	वापस 0;
पूर्ण

अटल व्योम wilc_sdio_हटाओ(काष्ठा sdio_func *func)
अणु
	काष्ठा wilc *wilc = sdio_get_drvdata(func);

	अगर (!IS_ERR(wilc->rtc_clk))
		clk_disable_unprepare(wilc->rtc_clk);

	wilc_netdev_cleanup(wilc);
पूर्ण

अटल पूर्णांक wilc_sdio_reset(काष्ठा wilc *wilc)
अणु
	काष्ठा sdio_cmd52 cmd;
	पूर्णांक ret;
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);

	cmd.पढ़ो_ग_लिखो = 1;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = SDIO_CCCR_ABORT;
	cmd.data = WILC_SDIO_CCCR_ABORT_RESET;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Fail cmd 52, reset cmd ...\n");
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_suspend(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा wilc *wilc = sdio_get_drvdata(func);
	पूर्णांक ret;

	dev_info(dev, "sdio suspend\n");
	chip_wakeup(wilc);

	अगर (!IS_ERR(wilc->rtc_clk))
		clk_disable_unprepare(wilc->rtc_clk);

	अगर (wilc->suspend_event) अणु
		host_sleep_notअगरy(wilc);
		chip_allow_sleep(wilc);
	पूर्ण

	ret = wilc_sdio_reset(wilc);
	अगर (ret) अणु
		dev_err(&func->dev, "Fail reset sdio\n");
		वापस ret;
	पूर्ण
	sdio_claim_host(func);

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_enable_पूर्णांकerrupt(काष्ठा wilc *dev)
अणु
	काष्ठा sdio_func *func = container_of(dev->dev, काष्ठा sdio_func, dev);
	पूर्णांक ret = 0;

	sdio_claim_host(func);
	ret = sdio_claim_irq(func, wilc_sdio_पूर्णांकerrupt);
	sdio_release_host(func);

	अगर (ret < 0) अणु
		dev_err(&func->dev, "can't claim sdio_irq, err(%d)\n", ret);
		ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम wilc_sdio_disable_पूर्णांकerrupt(काष्ठा wilc *dev)
अणु
	काष्ठा sdio_func *func = container_of(dev->dev, काष्ठा sdio_func, dev);
	पूर्णांक ret;

	sdio_claim_host(func);
	ret = sdio_release_irq(func);
	अगर (ret < 0)
		dev_err(&func->dev, "can't release sdio_irq, err(%d)\n", ret);
	sdio_release_host(func);
पूर्ण

/********************************************
 *
 *      Function 0
 *
 ********************************************/

अटल पूर्णांक wilc_sdio_set_func0_csa_address(काष्ठा wilc *wilc, u32 adr)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा sdio_cmd52 cmd;
	पूर्णांक ret;

	/**
	 *      Review: BIG ENDIAN
	 **/
	cmd.पढ़ो_ग_लिखो = 1;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = WILC_SDIO_FBR_CSA_REG;
	cmd.data = (u8)adr;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Failed cmd52, set %04x data...\n",
			cmd.address);
		वापस ret;
	पूर्ण

	cmd.address = WILC_SDIO_FBR_CSA_REG + 1;
	cmd.data = (u8)(adr >> 8);
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Failed cmd52, set %04x data...\n",
			cmd.address);
		वापस ret;
	पूर्ण

	cmd.address = WILC_SDIO_FBR_CSA_REG + 2;
	cmd.data = (u8)(adr >> 16);
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Failed cmd52, set %04x data...\n",
			cmd.address);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_set_block_size(काष्ठा wilc *wilc, u8 func_num,
				    u32 block_size)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा sdio_cmd52 cmd;
	पूर्णांक ret;

	cmd.पढ़ो_ग_लिखो = 1;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = SDIO_FBR_BASE(func_num) + SDIO_CCCR_BLKSIZE;
	cmd.data = (u8)block_size;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Failed cmd52, set %04x data...\n",
			cmd.address);
		वापस ret;
	पूर्ण

	cmd.address = SDIO_FBR_BASE(func_num) + SDIO_CCCR_BLKSIZE +  1;
	cmd.data = (u8)(block_size >> 8);
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Failed cmd52, set %04x data...\n",
			cmd.address);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/********************************************
 *
 *      Sdio पूर्णांकerfaces
 *
 ********************************************/
अटल पूर्णांक wilc_sdio_ग_लिखो_reg(काष्ठा wilc *wilc, u32 addr, u32 data)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	पूर्णांक ret;

	cpu_to_le32s(&data);

	अगर (addr >= 0xf0 && addr <= 0xff) अणु /* only venकरोr specअगरic रेजिस्टरs */
		काष्ठा sdio_cmd52 cmd;

		cmd.पढ़ो_ग_लिखो = 1;
		cmd.function = 0;
		cmd.raw = 0;
		cmd.address = addr;
		cmd.data = data;
		ret = wilc_sdio_cmd52(wilc, &cmd);
		अगर (ret)
			dev_err(&func->dev,
				"Failed cmd 52, read reg (%08x) ...\n", addr);
	पूर्ण अन्यथा अणु
		काष्ठा sdio_cmd53 cmd;

		/**
		 *      set the AHB address
		 **/
		ret = wilc_sdio_set_func0_csa_address(wilc, addr);
		अगर (ret)
			वापस ret;

		cmd.पढ़ो_ग_लिखो = 1;
		cmd.function = 0;
		cmd.address = WILC_SDIO_FBR_DATA_REG;
		cmd.block_mode = 0;
		cmd.increment = 1;
		cmd.count = 4;
		cmd.buffer = (u8 *)&data;
		cmd.block_size = sdio_priv->block_size;
		ret = wilc_sdio_cmd53(wilc, &cmd);
		अगर (ret)
			dev_err(&func->dev,
				"Failed cmd53, write reg (%08x)...\n", addr);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक wilc_sdio_ग_लिखो(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	u32 block_size = sdio_priv->block_size;
	काष्ठा sdio_cmd53 cmd;
	पूर्णांक nblk, nleft, ret;

	cmd.पढ़ो_ग_लिखो = 1;
	अगर (addr > 0) अणु
		/**
		 *      func 0 access
		 **/
		cmd.function = 0;
		cmd.address = WILC_SDIO_FBR_DATA_REG;
	पूर्ण अन्यथा अणु
		/**
		 *      func 1 access
		 **/
		cmd.function = 1;
		cmd.address = WILC_SDIO_F1_DATA_REG;
	पूर्ण

	size = ALIGN(size, 4);
	nblk = size / block_size;
	nleft = size % block_size;

	अगर (nblk > 0) अणु
		cmd.block_mode = 1;
		cmd.increment = 1;
		cmd.count = nblk;
		cmd.buffer = buf;
		cmd.block_size = block_size;
		अगर (addr > 0) अणु
			ret = wilc_sdio_set_func0_csa_address(wilc, addr);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = wilc_sdio_cmd53(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd53 [%x], block send...\n", addr);
			वापस ret;
		पूर्ण
		अगर (addr > 0)
			addr += nblk * block_size;
		buf += nblk * block_size;
	पूर्ण

	अगर (nleft > 0) अणु
		cmd.block_mode = 0;
		cmd.increment = 1;
		cmd.count = nleft;
		cmd.buffer = buf;

		cmd.block_size = block_size;

		अगर (addr > 0) अणु
			ret = wilc_sdio_set_func0_csa_address(wilc, addr);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = wilc_sdio_cmd53(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd53 [%x], bytes send...\n", addr);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_पढ़ो_reg(काष्ठा wilc *wilc, u32 addr, u32 *data)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	पूर्णांक ret;

	अगर (addr >= 0xf0 && addr <= 0xff) अणु /* only venकरोr specअगरic रेजिस्टरs */
		काष्ठा sdio_cmd52 cmd;

		cmd.पढ़ो_ग_लिखो = 0;
		cmd.function = 0;
		cmd.raw = 0;
		cmd.address = addr;
		ret = wilc_sdio_cmd52(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd 52, read reg (%08x) ...\n", addr);
			वापस ret;
		पूर्ण
		*data = cmd.data;
	पूर्ण अन्यथा अणु
		काष्ठा sdio_cmd53 cmd;

		ret = wilc_sdio_set_func0_csa_address(wilc, addr);
		अगर (ret)
			वापस ret;

		cmd.पढ़ो_ग_लिखो = 0;
		cmd.function = 0;
		cmd.address = WILC_SDIO_FBR_DATA_REG;
		cmd.block_mode = 0;
		cmd.increment = 1;
		cmd.count = 4;
		cmd.buffer = (u8 *)data;

		cmd.block_size = sdio_priv->block_size;
		ret = wilc_sdio_cmd53(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd53, read reg (%08x)...\n", addr);
			वापस ret;
		पूर्ण
	पूर्ण

	le32_to_cpus(data);
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_पढ़ो(काष्ठा wilc *wilc, u32 addr, u8 *buf, u32 size)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	u32 block_size = sdio_priv->block_size;
	काष्ठा sdio_cmd53 cmd;
	पूर्णांक nblk, nleft, ret;

	cmd.पढ़ो_ग_लिखो = 0;
	अगर (addr > 0) अणु
		/**
		 *      func 0 access
		 **/
		cmd.function = 0;
		cmd.address = WILC_SDIO_FBR_DATA_REG;
	पूर्ण अन्यथा अणु
		/**
		 *      func 1 access
		 **/
		cmd.function = 1;
		cmd.address = WILC_SDIO_F1_DATA_REG;
	पूर्ण

	size = ALIGN(size, 4);
	nblk = size / block_size;
	nleft = size % block_size;

	अगर (nblk > 0) अणु
		cmd.block_mode = 1;
		cmd.increment = 1;
		cmd.count = nblk;
		cmd.buffer = buf;
		cmd.block_size = block_size;
		अगर (addr > 0) अणु
			ret = wilc_sdio_set_func0_csa_address(wilc, addr);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = wilc_sdio_cmd53(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd53 [%x], block read...\n", addr);
			वापस ret;
		पूर्ण
		अगर (addr > 0)
			addr += nblk * block_size;
		buf += nblk * block_size;
	पूर्ण       /* अगर (nblk > 0) */

	अगर (nleft > 0) अणु
		cmd.block_mode = 0;
		cmd.increment = 1;
		cmd.count = nleft;
		cmd.buffer = buf;

		cmd.block_size = block_size;

		अगर (addr > 0) अणु
			ret = wilc_sdio_set_func0_csa_address(wilc, addr);
			अगर (ret)
				वापस ret;
		पूर्ण
		ret = wilc_sdio_cmd53(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd53 [%x], bytes read...\n", addr);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/********************************************
 *
 *      Bus पूर्णांकerfaces
 *
 ********************************************/

अटल पूर्णांक wilc_sdio_deinit(काष्ठा wilc *wilc)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_init(काष्ठा wilc *wilc, bool resume)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	काष्ठा sdio_cmd52 cmd;
	पूर्णांक loop, ret;
	u32 chipid;

	/**
	 *      function 0 csa enable
	 **/
	cmd.पढ़ो_ग_लिखो = 1;
	cmd.function = 0;
	cmd.raw = 1;
	cmd.address = SDIO_FBR_BASE(func->num);
	cmd.data = SDIO_FBR_ENABLE_CSA;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Fail cmd 52, enable csa...\n");
		वापस ret;
	पूर्ण

	/**
	 *      function 0 block size
	 **/
	ret = wilc_sdio_set_block_size(wilc, 0, WILC_SDIO_BLOCK_SIZE);
	अगर (ret) अणु
		dev_err(&func->dev, "Fail cmd 52, set func 0 block size...\n");
		वापस ret;
	पूर्ण
	sdio_priv->block_size = WILC_SDIO_BLOCK_SIZE;

	/**
	 *      enable func1 IO
	 **/
	cmd.पढ़ो_ग_लिखो = 1;
	cmd.function = 0;
	cmd.raw = 1;
	cmd.address = SDIO_CCCR_IOEx;
	cmd.data = WILC_SDIO_CCCR_IO_EN_FUNC1;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev,
			"Fail cmd 52, set IOE register...\n");
		वापस ret;
	पूर्ण

	/**
	 *      make sure func 1 is up
	 **/
	cmd.पढ़ो_ग_लिखो = 0;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = SDIO_CCCR_IORx;
	loop = 3;
	करो अणु
		cmd.data = 0;
		ret = wilc_sdio_cmd52(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Fail cmd 52, get IOR register...\n");
			वापस ret;
		पूर्ण
		अगर (cmd.data == WILC_SDIO_CCCR_IO_EN_FUNC1)
			अवरोध;
	पूर्ण जबतक (loop--);

	अगर (loop <= 0) अणु
		dev_err(&func->dev, "Fail func 1 is not ready...\n");
		वापस -EINVAL;
	पूर्ण

	/**
	 *      func 1 is पढ़ोy, set func 1 block size
	 **/
	ret = wilc_sdio_set_block_size(wilc, 1, WILC_SDIO_BLOCK_SIZE);
	अगर (ret) अणु
		dev_err(&func->dev, "Fail set func 1 block size...\n");
		वापस ret;
	पूर्ण

	/**
	 *      func 1 पूर्णांकerrupt enable
	 **/
	cmd.पढ़ो_ग_लिखो = 1;
	cmd.function = 0;
	cmd.raw = 1;
	cmd.address = SDIO_CCCR_IENx;
	cmd.data = WILC_SDIO_CCCR_IEN_MASTER | WILC_SDIO_CCCR_IEN_FUNC1;
	ret = wilc_sdio_cmd52(wilc, &cmd);
	अगर (ret) अणु
		dev_err(&func->dev, "Fail cmd 52, set IEN register...\n");
		वापस ret;
	पूर्ण

	/**
	 *      make sure can पढ़ो back chip id correctly
	 **/
	अगर (!resume) अणु
		पूर्णांक rev;

		ret = wilc_sdio_पढ़ो_reg(wilc, WILC_CHIPID, &chipid);
		अगर (ret) अणु
			dev_err(&func->dev, "Fail cmd read chip id...\n");
			वापस ret;
		पूर्ण
		dev_err(&func->dev, "chipid (%08x)\n", chipid);
		rev = FIELD_GET(WILC_CHIP_REV_FIELD, chipid);
		अगर (rev > FIELD_GET(WILC_CHIP_REV_FIELD, WILC_1000_BASE_ID_2A))
			sdio_priv->has_thrpt_enh3 = 1;
		अन्यथा
			sdio_priv->has_thrpt_enh3 = 0;
		dev_info(&func->dev, "has_thrpt_enh3 = %d...\n",
			 sdio_priv->has_thrpt_enh3);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_पढ़ो_size(काष्ठा wilc *wilc, u32 *size)
अणु
	u32 पंचांगp;
	काष्ठा sdio_cmd52 cmd;

	/**
	 *      Read DMA count in words
	 **/
	cmd.पढ़ो_ग_लिखो = 0;
	cmd.function = 0;
	cmd.raw = 0;
	cmd.address = WILC_SDIO_INTERRUPT_DATA_SZ_REG;
	cmd.data = 0;
	wilc_sdio_cmd52(wilc, &cmd);
	पंचांगp = cmd.data;

	cmd.address = WILC_SDIO_INTERRUPT_DATA_SZ_REG + 1;
	cmd.data = 0;
	wilc_sdio_cmd52(wilc, &cmd);
	पंचांगp |= (cmd.data << 8);

	*size = पंचांगp;
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_पढ़ो_पूर्णांक(काष्ठा wilc *wilc, u32 *पूर्णांक_status)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	u32 पंचांगp;
	u8 irq_flags;
	काष्ठा sdio_cmd52 cmd;

	wilc_sdio_पढ़ो_size(wilc, &पंचांगp);

	/**
	 *      Read IRQ flags
	 **/
	अगर (!sdio_priv->irq_gpio) अणु
		cmd.function = 1;
		cmd.address = WILC_SDIO_EXT_IRQ_FLAG_REG;
	पूर्ण अन्यथा अणु
		cmd.function = 0;
		cmd.address = WILC_SDIO_IRQ_FLAG_REG;
	पूर्ण
	cmd.raw = 0;
	cmd.पढ़ो_ग_लिखो = 0;
	cmd.data = 0;
	wilc_sdio_cmd52(wilc, &cmd);
	irq_flags = cmd.data;
	पंचांगp |= FIELD_PREP(IRG_FLAGS_MASK, cmd.data);

	अगर (FIELD_GET(UNHANDLED_IRQ_MASK, irq_flags))
		dev_err(&func->dev, "Unexpected interrupt (1) int=%lx\n",
			FIELD_GET(UNHANDLED_IRQ_MASK, irq_flags));

	*पूर्णांक_status = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_clear_पूर्णांक_ext(काष्ठा wilc *wilc, u32 val)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	पूर्णांक ret;
	पूर्णांक vmm_ctl;

	अगर (sdio_priv->has_thrpt_enh3) अणु
		u32 reg = 0;

		अगर (sdio_priv->irq_gpio)
			reg = val & (BIT(MAX_NUM_INT) - 1);

		/* select VMM table 0 */
		अगर (val & SEL_VMM_TBL0)
			reg |= BIT(5);
		/* select VMM table 1 */
		अगर (val & SEL_VMM_TBL1)
			reg |= BIT(6);
		/* enable VMM */
		अगर (val & EN_VMM)
			reg |= BIT(7);
		अगर (reg) अणु
			काष्ठा sdio_cmd52 cmd;

			cmd.पढ़ो_ग_लिखो = 1;
			cmd.function = 0;
			cmd.raw = 0;
			cmd.address = WILC_SDIO_IRQ_CLEAR_FLAG_REG;
			cmd.data = reg;

			ret = wilc_sdio_cmd52(wilc, &cmd);
			अगर (ret) अणु
				dev_err(&func->dev,
					"Failed cmd52, set (%02x) data (%d) ...\n",
					cmd.address, __LINE__);
				वापस ret;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण
	अगर (sdio_priv->irq_gpio) अणु
		/* has_thrpt_enh2 uses रेजिस्टर 0xf8 to clear पूर्णांकerrupts. */
		/*
		 * Cannot clear multiple पूर्णांकerrupts.
		 * Must clear each पूर्णांकerrupt inभागidually.
		 */
		u32 flags;
		पूर्णांक i;

		flags = val & (BIT(MAX_NUM_INT) - 1);
		क्रम (i = 0; i < NUM_INT_EXT && flags; i++) अणु
			अगर (flags & BIT(i)) अणु
				काष्ठा sdio_cmd52 cmd;

				cmd.पढ़ो_ग_लिखो = 1;
				cmd.function = 0;
				cmd.raw = 0;
				cmd.address = WILC_SDIO_IRQ_CLEAR_FLAG_REG;
				cmd.data = BIT(i);

				ret = wilc_sdio_cmd52(wilc, &cmd);
				अगर (ret) अणु
					dev_err(&func->dev,
						"Failed cmd52, set (%02x) data (%d) ...\n",
						cmd.address, __LINE__);
					वापस ret;
				पूर्ण
				flags &= ~BIT(i);
			पूर्ण
		पूर्ण

		क्रम (i = NUM_INT_EXT; i < MAX_NUM_INT && flags; i++) अणु
			अगर (flags & BIT(i)) अणु
				dev_err(&func->dev,
					"Unexpected interrupt cleared %d...\n",
					i);
				flags &= ~BIT(i);
			पूर्ण
		पूर्ण
	पूर्ण

	vmm_ctl = 0;
	/* select VMM table 0 */
	अगर (val & SEL_VMM_TBL0)
		vmm_ctl |= BIT(0);
	/* select VMM table 1 */
	अगर (val & SEL_VMM_TBL1)
		vmm_ctl |= BIT(1);
	/* enable VMM */
	अगर (val & EN_VMM)
		vmm_ctl |= BIT(2);

	अगर (vmm_ctl) अणु
		काष्ठा sdio_cmd52 cmd;

		cmd.पढ़ो_ग_लिखो = 1;
		cmd.function = 0;
		cmd.raw = 0;
		cmd.address = WILC_SDIO_VMM_TBL_CTRL_REG;
		cmd.data = vmm_ctl;
		ret = wilc_sdio_cmd52(wilc, &cmd);
		अगर (ret) अणु
			dev_err(&func->dev,
				"Failed cmd52, set (%02x) data (%d) ...\n",
				cmd.address, __LINE__);
			वापस ret;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक wilc_sdio_sync_ext(काष्ठा wilc *wilc, पूर्णांक nपूर्णांक)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(wilc->dev);
	काष्ठा wilc_sdio *sdio_priv = wilc->bus_data;
	u32 reg;

	अगर (nपूर्णांक > MAX_NUM_INT) अणु
		dev_err(&func->dev, "Too many interrupts (%d)...\n", nपूर्णांक);
		वापस -EINVAL;
	पूर्ण

	/**
	 *      Disable घातer sequencer
	 **/
	अगर (wilc_sdio_पढ़ो_reg(wilc, WILC_MISC, &reg)) अणु
		dev_err(&func->dev, "Failed read misc reg...\n");
		वापस -EINVAL;
	पूर्ण

	reg &= ~BIT(8);
	अगर (wilc_sdio_ग_लिखो_reg(wilc, WILC_MISC, reg)) अणु
		dev_err(&func->dev, "Failed write misc reg...\n");
		वापस -EINVAL;
	पूर्ण

	अगर (sdio_priv->irq_gpio) अणु
		u32 reg;
		पूर्णांक ret, i;

		/**
		 *      पूर्णांकerrupt pin mux select
		 **/
		ret = wilc_sdio_पढ़ो_reg(wilc, WILC_PIN_MUX_0, &reg);
		अगर (ret) अणु
			dev_err(&func->dev, "Failed read reg (%08x)...\n",
				WILC_PIN_MUX_0);
			वापस ret;
		पूर्ण
		reg |= BIT(8);
		ret = wilc_sdio_ग_लिखो_reg(wilc, WILC_PIN_MUX_0, reg);
		अगर (ret) अणु
			dev_err(&func->dev, "Failed write reg (%08x)...\n",
				WILC_PIN_MUX_0);
			वापस ret;
		पूर्ण

		/**
		 *      पूर्णांकerrupt enable
		 **/
		ret = wilc_sdio_पढ़ो_reg(wilc, WILC_INTR_ENABLE, &reg);
		अगर (ret) अणु
			dev_err(&func->dev, "Failed read reg (%08x)...\n",
				WILC_INTR_ENABLE);
			वापस ret;
		पूर्ण

		क्रम (i = 0; (i < 5) && (nपूर्णांक > 0); i++, nपूर्णांक--)
			reg |= BIT((27 + i));
		ret = wilc_sdio_ग_लिखो_reg(wilc, WILC_INTR_ENABLE, reg);
		अगर (ret) अणु
			dev_err(&func->dev, "Failed write reg (%08x)...\n",
				WILC_INTR_ENABLE);
			वापस ret;
		पूर्ण
		अगर (nपूर्णांक) अणु
			ret = wilc_sdio_पढ़ो_reg(wilc, WILC_INTR2_ENABLE, &reg);
			अगर (ret) अणु
				dev_err(&func->dev,
					"Failed read reg (%08x)...\n",
					WILC_INTR2_ENABLE);
				वापस ret;
			पूर्ण

			क्रम (i = 0; (i < 3) && (nपूर्णांक > 0); i++, nपूर्णांक--)
				reg |= BIT(i);

			ret = wilc_sdio_ग_लिखो_reg(wilc, WILC_INTR2_ENABLE, reg);
			अगर (ret) अणु
				dev_err(&func->dev,
					"Failed write reg (%08x)...\n",
					WILC_INTR2_ENABLE);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Global sdio HIF function table */
अटल स्थिर काष्ठा wilc_hअगर_func wilc_hअगर_sdio = अणु
	.hअगर_init = wilc_sdio_init,
	.hअगर_deinit = wilc_sdio_deinit,
	.hअगर_पढ़ो_reg = wilc_sdio_पढ़ो_reg,
	.hअगर_ग_लिखो_reg = wilc_sdio_ग_लिखो_reg,
	.hअगर_block_rx = wilc_sdio_पढ़ो,
	.hअगर_block_tx = wilc_sdio_ग_लिखो,
	.hअगर_पढ़ो_पूर्णांक = wilc_sdio_पढ़ो_पूर्णांक,
	.hअगर_clear_पूर्णांक_ext = wilc_sdio_clear_पूर्णांक_ext,
	.hअगर_पढ़ो_size = wilc_sdio_पढ़ो_size,
	.hअगर_block_tx_ext = wilc_sdio_ग_लिखो,
	.hअगर_block_rx_ext = wilc_sdio_पढ़ो,
	.hअगर_sync_ext = wilc_sdio_sync_ext,
	.enable_पूर्णांकerrupt = wilc_sdio_enable_पूर्णांकerrupt,
	.disable_पूर्णांकerrupt = wilc_sdio_disable_पूर्णांकerrupt,
पूर्ण;

अटल पूर्णांक wilc_sdio_resume(काष्ठा device *dev)
अणु
	काष्ठा sdio_func *func = dev_to_sdio_func(dev);
	काष्ठा wilc *wilc = sdio_get_drvdata(func);

	dev_info(dev, "sdio resume\n");
	sdio_release_host(func);
	chip_wakeup(wilc);
	wilc_sdio_init(wilc, true);

	अगर (wilc->suspend_event)
		host_wakeup_notअगरy(wilc);

	chip_allow_sleep(wilc);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wilc_of_match[] = अणु
	अणु .compatible = "microchip,wilc1000", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wilc_of_match);

अटल स्थिर काष्ठा dev_pm_ops wilc_sdio_pm_ops = अणु
	.suspend = wilc_sdio_suspend,
	.resume = wilc_sdio_resume,
पूर्ण;

अटल काष्ठा sdio_driver wilc_sdio_driver = अणु
	.name		= SDIO_MODALIAS,
	.id_table	= wilc_sdio_ids,
	.probe		= wilc_sdio_probe,
	.हटाओ		= wilc_sdio_हटाओ,
	.drv = अणु
		.pm = &wilc_sdio_pm_ops,
		.of_match_table = wilc_of_match,
	पूर्ण
पूर्ण;
module_driver(wilc_sdio_driver,
	      sdio_रेजिस्टर_driver,
	      sdio_unरेजिस्टर_driver);
MODULE_LICENSE("GPL");
