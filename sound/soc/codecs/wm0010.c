<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * wm0010.c  --  WM0010 DSP Driver
 *
 * Copyright 2012 Wolfson Microelectronics PLC.
 *
 * Authors: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 *          Dimitris Papastamos <dp@खोलोsource.wolfsonmicro.com>
 *          Scott Ling <sl@खोलोsource.wolfsonmicro.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqवापस.h>
#समावेश <linux/init.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/firmware.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>

#समावेश <sound/soc.h>
#समावेश <sound/wm0010.h>

#घोषणा DEVICE_ID_WM0010	10

/* We only support v1 of the .dfw INFO record */
#घोषणा INFO_VERSION		1

क्रमागत dfw_cmd अणु
	DFW_CMD_FUSE = 0x01,
	DFW_CMD_CODE_HDR,
	DFW_CMD_CODE_DATA,
	DFW_CMD_PLL,
	DFW_CMD_INFO = 0xff
पूर्ण;

काष्ठा dfw_binrec अणु
	u8 command;
	u32 length:24;
	u32 address;
	uपूर्णांक8_t data[];
पूर्ण __packed;

काष्ठा dfw_inक्रमec अणु
	u8 info_version;
	u8 tool_major_version;
	u8 tool_minor_version;
	u8 dsp_target;
पूर्ण;

काष्ठा dfw_pllrec अणु
	u8 command;
	u32 length:24;
	u32 address;
	u32 clkctrl1;
	u32 clkctrl2;
	u32 clkctrl3;
	u32 ldetctrl;
	u32 uart_भाग;
	u32 spi_भाग;
पूर्ण __packed;

अटल काष्ठा pll_घड़ी_map अणु
	पूर्णांक max_sysclk;
	पूर्णांक max_pll_spi_speed;
	u32 pll_clkctrl1;
पूर्ण pll_घड़ी_map[] = अणु			   /* Dividers */
	अणु 22000000, 26000000, 0x00201f11 पूर्ण, /* 2,32,2  */
	अणु 18000000, 26000000, 0x00203f21 पूर्ण, /* 2,64,4  */
	अणु 14000000, 26000000, 0x00202620 पूर्ण, /* 1,39,4  */
	अणु 10000000, 22000000, 0x00203120 पूर्ण, /* 1,50,4  */
	अणु  6500000, 22000000, 0x00204520 पूर्ण, /* 1,70,4  */
	अणु  5500000, 22000000, 0x00103f10 पूर्ण, /* 1,64,2  */
पूर्ण;

क्रमागत wm0010_state अणु
	WM0010_POWER_OFF,
	WM0010_OUT_OF_RESET,
	WM0010_BOOTROM,
	WM0010_STAGE2,
	WM0010_FIRMWARE,
पूर्ण;

काष्ठा wm0010_priv अणु
	काष्ठा snd_soc_component *component;

	काष्ठा mutex lock;
	काष्ठा device *dev;

	काष्ठा wm0010_pdata pdata;

	पूर्णांक gpio_reset;
	पूर्णांक gpio_reset_value;

	काष्ठा regulator_bulk_data core_supplies[2];
	काष्ठा regulator *dbvdd;

	पूर्णांक sysclk;

	क्रमागत wm0010_state state;
	bool boot_failed;
	bool पढ़ोy;
	bool pll_running;
	पूर्णांक max_spi_freq;
	पूर्णांक board_max_spi_speed;
	u32 pll_clkctrl1;

	spinlock_t irq_lock;
	पूर्णांक irq;

	काष्ठा completion boot_completion;
पूर्ण;

काष्ठा wm0010_spi_msg अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	u8 *tx_buf;
	u8 *rx_buf;
	माप_प्रकार len;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget wm0010_dapm_widमाला_लो[] = अणु
SND_SOC_DAPM_SUPPLY("CLKIN",  SND_SOC_NOPM, 0, 0, शून्य, 0),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route wm0010_dapm_routes[] = अणु
	अणु "SDI2 Capture", शून्य, "SDI1 Playback" पूर्ण,
	अणु "SDI1 Capture", शून्य, "SDI2 Playback" पूर्ण,

	अणु "SDI1 Capture", शून्य, "CLKIN" पूर्ण,
	अणु "SDI2 Capture", शून्य, "CLKIN" पूर्ण,
	अणु "SDI1 Playback", शून्य, "CLKIN" पूर्ण,
	अणु "SDI2 Playback", शून्य, "CLKIN" पूर्ण,
पूर्ण;

अटल स्थिर अक्षर *wm0010_state_to_str(क्रमागत wm0010_state state)
अणु
	अटल स्थिर अक्षर * स्थिर state_to_str[] = अणु
		"Power off",
		"Out of reset",
		"Boot ROM",
		"Stage2",
		"Firmware"
	पूर्ण;

	अगर (state < 0 || state >= ARRAY_SIZE(state_to_str))
		वापस "null";
	वापस state_to_str[state];
पूर्ण

/* Called with wm0010->lock held */
अटल व्योम wm0010_halt(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ flags;
	क्रमागत wm0010_state state;

	/* Fetch the wm0010 state */
	spin_lock_irqsave(&wm0010->irq_lock, flags);
	state = wm0010->state;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	चयन (state) अणु
	हाल WM0010_POWER_OFF:
		/* If there's nothing to करो, bail out */
		वापस;
	हाल WM0010_OUT_OF_RESET:
	हाल WM0010_BOOTROM:
	हाल WM0010_STAGE2:
	हाल WM0010_FIRMWARE:
		/* Remember to put chip back पूर्णांकo reset */
		gpio_set_value_cansleep(wm0010->gpio_reset,
					wm0010->gpio_reset_value);
		/* Disable the regulators */
		regulator_disable(wm0010->dbvdd);
		regulator_bulk_disable(ARRAY_SIZE(wm0010->core_supplies),
				       wm0010->core_supplies);
		अवरोध;
	पूर्ण

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_POWER_OFF;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);
पूर्ण

काष्ठा wm0010_boot_xfer अणु
	काष्ठा list_head list;
	काष्ठा snd_soc_component *component;
	काष्ठा completion *करोne;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
पूर्ण;

/* Called with wm0010->lock held */
अटल व्योम wm0010_mark_boot_failure(काष्ठा wm0010_priv *wm0010)
अणु
	क्रमागत wm0010_state state;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	state = wm0010->state;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	dev_err(wm0010->dev, "Failed to transition from `%s' state to `%s' state\n",
		wm0010_state_to_str(state), wm0010_state_to_str(state + 1));

	wm0010->boot_failed = true;
पूर्ण

अटल व्योम wm0010_boot_xfer_complete(व्योम *data)
अणु
	काष्ठा wm0010_boot_xfer *xfer = data;
	काष्ठा snd_soc_component *component = xfer->component;
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	u32 *out32 = xfer->t.rx_buf;
	पूर्णांक i;

	अगर (xfer->m.status != 0) अणु
		dev_err(component->dev, "SPI transfer failed: %d\n",
			xfer->m.status);
		wm0010_mark_boot_failure(wm0010);
		अगर (xfer->करोne)
			complete(xfer->करोne);
		वापस;
	पूर्ण

	क्रम (i = 0; i < xfer->t.len / 4; i++) अणु
		dev_dbg(component->dev, "%d: %04x\n", i, out32[i]);

		चयन (be32_to_cpu(out32[i])) अणु
		हाल 0xe0e0e0e0:
			dev_err(component->dev,
				"%d: ROM error reported in stage 2\n", i);
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x55555555:
			अगर (wm0010->state < WM0010_STAGE2)
				अवरोध;
			dev_err(component->dev,
				"%d: ROM bootloader running in stage 2\n", i);
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0000:
			dev_dbg(component->dev, "Stage2 loader running\n");
			अवरोध;

		हाल 0x0fed0007:
			dev_dbg(component->dev, "CODE_HDR packet received\n");
			अवरोध;

		हाल 0x0fed0008:
			dev_dbg(component->dev, "CODE_DATA packet received\n");
			अवरोध;

		हाल 0x0fed0009:
			dev_dbg(component->dev, "Download complete\n");
			अवरोध;

		हाल 0x0fed000c:
			dev_dbg(component->dev, "Application start\n");
			अवरोध;

		हाल 0x0fed000e:
			dev_dbg(component->dev, "PLL packet received\n");
			wm0010->pll_running = true;
			अवरोध;

		हाल 0x0fed0025:
			dev_err(component->dev, "Device reports image too long\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed002c:
			dev_err(component->dev, "Device reports bad SPI packet\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0031:
			dev_err(component->dev, "Device reports SPI read overflow\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0032:
			dev_err(component->dev, "Device reports SPI underclock\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0033:
			dev_err(component->dev, "Device reports bad header packet\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0034:
			dev_err(component->dev, "Device reports invalid packet type\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0035:
			dev_err(component->dev, "Device reports data before header error\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		हाल 0x0fed0038:
			dev_err(component->dev, "Device reports invalid PLL packet\n");
			अवरोध;

		हाल 0x0fed003a:
			dev_err(component->dev, "Device reports packet alignment error\n");
			wm0010_mark_boot_failure(wm0010);
			अवरोध;

		शेष:
			dev_err(component->dev, "Unrecognised return 0x%x\n",
			    be32_to_cpu(out32[i]));
			wm0010_mark_boot_failure(wm0010);
			अवरोध;
		पूर्ण

		अगर (wm0010->boot_failed)
			अवरोध;
	पूर्ण

	अगर (xfer->करोne)
		complete(xfer->करोne);
पूर्ण

अटल व्योम byte_swap_64(u64 *data_in, u64 *data_out, u32 len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len / 8; i++)
		data_out[i] = cpu_to_be64(le64_to_cpu(data_in[i]));
पूर्ण

अटल पूर्णांक wm0010_firmware_load(स्थिर अक्षर *name, काष्ठा snd_soc_component *component)
अणु
	काष्ठा spi_device *spi = to_spi_device(component->dev);
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	काष्ठा list_head xfer_list;
	काष्ठा wm0010_boot_xfer *xfer;
	पूर्णांक ret;
	DECLARE_COMPLETION_ONSTACK(करोne);
	स्थिर काष्ठा firmware *fw;
	स्थिर काष्ठा dfw_binrec *rec;
	स्थिर काष्ठा dfw_inक्रमec *inक्रमec;
	u64 *img;
	u8 *out, dsp;
	u32 len, offset;

	INIT_LIST_HEAD(&xfer_list);

	ret = request_firmware(&fw, name, component->dev);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to request application(%s): %d\n",
			name, ret);
		वापस ret;
	पूर्ण

	rec = (स्थिर काष्ठा dfw_binrec *)fw->data;
	inक्रमec = (स्थिर काष्ठा dfw_inक्रमec *)rec->data;
	offset = 0;
	dsp = inक्रमec->dsp_target;
	wm0010->boot_failed = false;
	अगर (WARN_ON(!list_empty(&xfer_list)))
		वापस -EINVAL;

	/* First record should be INFO */
	अगर (rec->command != DFW_CMD_INFO) अणु
		dev_err(component->dev, "First record not INFO\r\n");
		ret = -EINVAL;
		जाओ पात;
	पूर्ण

	अगर (inक्रमec->info_version != INFO_VERSION) अणु
		dev_err(component->dev,
			"Unsupported version (%02d) of INFO record\r\n",
			inक्रमec->info_version);
		ret = -EINVAL;
		जाओ पात;
	पूर्ण

	dev_dbg(component->dev, "Version v%02d INFO record found\r\n",
		inक्रमec->info_version);

	/* Check it's a DSP file */
	अगर (dsp != DEVICE_ID_WM0010) अणु
		dev_err(component->dev, "Not a WM0010 firmware file.\r\n");
		ret = -EINVAL;
		जाओ पात;
	पूर्ण

	/* Skip the info record as we करोn't need to send it */
	offset += ((rec->length) + 8);
	rec = (व्योम *)&rec->data[rec->length];

	जबतक (offset < fw->size) अणु
		dev_dbg(component->dev,
			"Packet: command %d, data length = 0x%x\r\n",
			rec->command, rec->length);
		len = rec->length + 8;

		xfer = kzalloc(माप(*xfer), GFP_KERNEL);
		अगर (!xfer) अणु
			ret = -ENOMEM;
			जाओ पात;
		पूर्ण

		xfer->component = component;
		list_add_tail(&xfer->list, &xfer_list);

		out = kzalloc(len, GFP_KERNEL | GFP_DMA);
		अगर (!out) अणु
			ret = -ENOMEM;
			जाओ पात1;
		पूर्ण
		xfer->t.rx_buf = out;

		img = kzalloc(len, GFP_KERNEL | GFP_DMA);
		अगर (!img) अणु
			ret = -ENOMEM;
			जाओ पात1;
		पूर्ण
		xfer->t.tx_buf = img;

		byte_swap_64((u64 *)&rec->command, img, len);

		spi_message_init(&xfer->m);
		xfer->m.complete = wm0010_boot_xfer_complete;
		xfer->m.context = xfer;
		xfer->t.len = len;
		xfer->t.bits_per_word = 8;

		अगर (!wm0010->pll_running) अणु
			xfer->t.speed_hz = wm0010->sysclk / 6;
		पूर्ण अन्यथा अणु
			xfer->t.speed_hz = wm0010->max_spi_freq;

			अगर (wm0010->board_max_spi_speed &&
			   (wm0010->board_max_spi_speed < wm0010->max_spi_freq))
					xfer->t.speed_hz = wm0010->board_max_spi_speed;
		पूर्ण

		/* Store max usable spi frequency क्रम later use */
		wm0010->max_spi_freq = xfer->t.speed_hz;

		spi_message_add_tail(&xfer->t, &xfer->m);

		offset += ((rec->length) + 8);
		rec = (व्योम *)&rec->data[rec->length];

		अगर (offset >= fw->size) अणु
			dev_dbg(component->dev, "All transfers scheduled\n");
			xfer->करोne = &करोne;
		पूर्ण

		ret = spi_async(spi, &xfer->m);
		अगर (ret != 0) अणु
			dev_err(component->dev, "Write failed: %d\n", ret);
			जाओ पात1;
		पूर्ण

		अगर (wm0010->boot_failed) अणु
			dev_dbg(component->dev, "Boot fail!\n");
			ret = -EINVAL;
			जाओ पात1;
		पूर्ण
	पूर्ण

	रुको_क्रम_completion(&करोne);

	ret = 0;

पात1:
	जबतक (!list_empty(&xfer_list)) अणु
		xfer = list_first_entry(&xfer_list, काष्ठा wm0010_boot_xfer,
					list);
		kमुक्त(xfer->t.rx_buf);
		kमुक्त(xfer->t.tx_buf);
		list_del(&xfer->list);
		kमुक्त(xfer);
	पूर्ण

पात:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक wm0010_stage2_load(काष्ठा snd_soc_component *component)
अणु
	काष्ठा spi_device *spi = to_spi_device(component->dev);
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	स्थिर काष्ठा firmware *fw;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	u32 *img;
	u8 *out;
	पूर्णांक i;
	पूर्णांक ret = 0;

	ret = request_firmware(&fw, "wm0010_stage2.bin", component->dev);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Failed to request stage2 loader: %d\n",
			ret);
		वापस ret;
	पूर्ण

	dev_dbg(component->dev, "Downloading %zu byte stage 2 loader\n", fw->size);

	/* Copy to local buffer first as vदो_स्मृति causes problems क्रम dma */
	img = kmemdup(&fw->data[0], fw->size, GFP_KERNEL | GFP_DMA);
	अगर (!img) अणु
		ret = -ENOMEM;
		जाओ पात2;
	पूर्ण

	out = kzalloc(fw->size, GFP_KERNEL | GFP_DMA);
	अगर (!out) अणु
		ret = -ENOMEM;
		जाओ पात1;
	पूर्ण

	spi_message_init(&m);
	स_रखो(&t, 0, माप(t));
	t.rx_buf = out;
	t.tx_buf = img;
	t.len = fw->size;
	t.bits_per_word = 8;
	t.speed_hz = wm0010->sysclk / 10;
	spi_message_add_tail(&t, &m);

	dev_dbg(component->dev, "Starting initial download at %dHz\n",
		t.speed_hz);

	ret = spi_sync(spi, &m);
	अगर (ret != 0) अणु
		dev_err(component->dev, "Initial download failed: %d\n", ret);
		जाओ पात;
	पूर्ण

	/* Look क्रम errors from the boot ROM */
	क्रम (i = 0; i < fw->size; i++) अणु
		अगर (out[i] != 0x55) अणु
			dev_err(component->dev, "Boot ROM error: %x in %d\n",
				out[i], i);
			wm0010_mark_boot_failure(wm0010);
			ret = -EBUSY;
			जाओ पात;
		पूर्ण
	पूर्ण
पात:
	kमुक्त(out);
पात1:
	kमुक्त(img);
पात2:
	release_firmware(fw);

	वापस ret;
पूर्ण

अटल पूर्णांक wm0010_boot(काष्ठा snd_soc_component *component)
अणु
	काष्ठा spi_device *spi = to_spi_device(component->dev);
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t;
	काष्ठा dfw_pllrec pll_rec;
	u32 *p, len;
	u64 *img_swap;
	u8 *out;
	पूर्णांक i;

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	अगर (wm0010->state != WM0010_POWER_OFF)
		dev_warn(wm0010->dev, "DSP already powered up!\n");
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	अगर (wm0010->sysclk > 26000000) अणु
		dev_err(component->dev, "Max DSP clock frequency is 26MHz\n");
		ret = -ECANCELED;
		जाओ err;
	पूर्ण

	mutex_lock(&wm0010->lock);
	wm0010->pll_running = false;

	dev_dbg(component->dev, "max_spi_freq: %d\n", wm0010->max_spi_freq);

	ret = regulator_bulk_enable(ARRAY_SIZE(wm0010->core_supplies),
				    wm0010->core_supplies);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "Failed to enable core supplies: %d\n",
			ret);
		mutex_unlock(&wm0010->lock);
		जाओ err;
	पूर्ण

	ret = regulator_enable(wm0010->dbvdd);
	अगर (ret != 0) अणु
		dev_err(&spi->dev, "Failed to enable DBVDD: %d\n", ret);
		जाओ err_core;
	पूर्ण

	/* Release reset */
	gpio_set_value_cansleep(wm0010->gpio_reset, !wm0010->gpio_reset_value);
	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_OUT_OF_RESET;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	अगर (!रुको_क्रम_completion_समयout(&wm0010->boot_completion,
					 msecs_to_jअगरfies(20)))
		dev_err(component->dev, "Failed to get interrupt from DSP\n");

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_BOOTROM;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	ret = wm0010_stage2_load(component);
	अगर (ret)
		जाओ पात;

	अगर (!रुको_क्रम_completion_समयout(&wm0010->boot_completion,
					 msecs_to_jअगरfies(20)))
		dev_err(component->dev, "Failed to get interrupt from DSP loader.\n");

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_STAGE2;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	/* Only initialise PLL अगर max_spi_freq initialised */
	अगर (wm0010->max_spi_freq) अणु

		/* Initialise a PLL record */
		स_रखो(&pll_rec, 0, माप(pll_rec));
		pll_rec.command = DFW_CMD_PLL;
		pll_rec.length = (माप(pll_rec) - 8);

		/* On wm0010 only the CLKCTRL1 value is used */
		pll_rec.clkctrl1 = wm0010->pll_clkctrl1;

		ret = -ENOMEM;
		len = pll_rec.length + 8;
		out = kzalloc(len, GFP_KERNEL | GFP_DMA);
		अगर (!out)
			जाओ पात;

		img_swap = kzalloc(len, GFP_KERNEL | GFP_DMA);
		अगर (!img_swap)
			जाओ पात_out;

		/* We need to re-order क्रम 0010 */
		byte_swap_64((u64 *)&pll_rec, img_swap, len);

		spi_message_init(&m);
		स_रखो(&t, 0, माप(t));
		t.rx_buf = out;
		t.tx_buf = img_swap;
		t.len = len;
		t.bits_per_word = 8;
		t.speed_hz = wm0010->sysclk / 6;
		spi_message_add_tail(&t, &m);

		ret = spi_sync(spi, &m);
		अगर (ret) अणु
			dev_err(component->dev, "First PLL write failed: %d\n", ret);
			जाओ पात_swap;
		पूर्ण

		/* Use a second send of the message to get the वापस status */
		ret = spi_sync(spi, &m);
		अगर (ret) अणु
			dev_err(component->dev, "Second PLL write failed: %d\n", ret);
			जाओ पात_swap;
		पूर्ण

		p = (u32 *)out;

		/* Look क्रम PLL active code from the DSP */
		क्रम (i = 0; i < len / 4; i++) अणु
			अगर (*p == 0x0e00ed0f) अणु
				dev_dbg(component->dev, "PLL packet received\n");
				wm0010->pll_running = true;
				अवरोध;
			पूर्ण
			p++;
		पूर्ण

		kमुक्त(img_swap);
		kमुक्त(out);
	पूर्ण अन्यथा
		dev_dbg(component->dev, "Not enabling DSP PLL.");

	ret = wm0010_firmware_load("wm0010.dfw", component);

	अगर (ret != 0)
		जाओ पात;

	spin_lock_irqsave(&wm0010->irq_lock, flags);
	wm0010->state = WM0010_FIRMWARE;
	spin_unlock_irqrestore(&wm0010->irq_lock, flags);

	mutex_unlock(&wm0010->lock);

	वापस 0;

पात_swap:
	kमुक्त(img_swap);
पात_out:
	kमुक्त(out);
पात:
	/* Put the chip back पूर्णांकo reset */
	wm0010_halt(component);
	mutex_unlock(&wm0010->lock);
	वापस ret;

err_core:
	mutex_unlock(&wm0010->lock);
	regulator_bulk_disable(ARRAY_SIZE(wm0010->core_supplies),
			       wm0010->core_supplies);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक wm0010_set_bias_level(काष्ठा snd_soc_component *component,
				 क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);

	चयन (level) अणु
	हाल SND_SOC_BIAS_ON:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE)
			wm0010_boot(component);
		अवरोध;
	हाल SND_SOC_BIAS_PREPARE:
		अवरोध;
	हाल SND_SOC_BIAS_STANDBY:
		अगर (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE) अणु
			mutex_lock(&wm0010->lock);
			wm0010_halt(component);
			mutex_unlock(&wm0010->lock);
		पूर्ण
		अवरोध;
	हाल SND_SOC_BIAS_OFF:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm0010_set_sysclk(काष्ठा snd_soc_component *component, पूर्णांक source,
			     पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक i;

	wm0010->sysclk = freq;

	अगर (freq < pll_घड़ी_map[ARRAY_SIZE(pll_घड़ी_map)-1].max_sysclk) अणु
		wm0010->max_spi_freq = 0;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < ARRAY_SIZE(pll_घड़ी_map); i++)
			अगर (freq >= pll_घड़ी_map[i].max_sysclk) अणु
				wm0010->max_spi_freq = pll_घड़ी_map[i].max_pll_spi_speed;
				wm0010->pll_clkctrl1 = pll_घड़ी_map[i].pll_clkctrl1;
				अवरोध;
			पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wm0010_probe(काष्ठा snd_soc_component *component);

अटल स्थिर काष्ठा snd_soc_component_driver soc_component_dev_wm0010 = अणु
	.probe			= wm0010_probe,
	.set_bias_level		= wm0010_set_bias_level,
	.set_sysclk		= wm0010_set_sysclk,
	.dapm_widमाला_लो		= wm0010_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(wm0010_dapm_widमाला_लो),
	.dapm_routes		= wm0010_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(wm0010_dapm_routes),
	.use_pmकरोwn_समय	= 1,
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

#घोषणा WM0010_RATES (SNDRV_PCM_RATE_44100 | SNDRV_PCM_RATE_48000)
#घोषणा WM0010_FORMATS (SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_S16_LE |\
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE |\
			SNDRV_PCM_FMTBIT_S32_LE)

अटल काष्ठा snd_soc_dai_driver wm0010_dai[] = अणु
	अणु
		.name = "wm0010-sdi1",
		.playback = अणु
			.stream_name = "SDI1 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM0010_RATES,
			.क्रमmats = WM0010_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "SDI1 Capture",
			 .channels_min = 1,
			 .channels_max = 2,
			 .rates = WM0010_RATES,
			 .क्रमmats = WM0010_FORMATS,
		 पूर्ण,
	पूर्ण,
	अणु
		.name = "wm0010-sdi2",
		.playback = अणु
			.stream_name = "SDI2 Playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = WM0010_RATES,
			.क्रमmats = WM0010_FORMATS,
		पूर्ण,
		.capture = अणु
			 .stream_name = "SDI2 Capture",
			 .channels_min = 1,
			 .channels_max = 2,
			 .rates = WM0010_RATES,
			 .क्रमmats = WM0010_FORMATS,
		 पूर्ण,
	पूर्ण,
पूर्ण;

अटल irqवापस_t wm0010_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा wm0010_priv *wm0010 = data;

	चयन (wm0010->state) अणु
	हाल WM0010_OUT_OF_RESET:
	हाल WM0010_BOOTROM:
	हाल WM0010_STAGE2:
		spin_lock(&wm0010->irq_lock);
		complete(&wm0010->boot_completion);
		spin_unlock(&wm0010->irq_lock);
		वापस IRQ_HANDLED;
	शेष:
		वापस IRQ_NONE;
	पूर्ण

	वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक wm0010_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);

	wm0010->component = component;

	वापस 0;
पूर्ण

अटल पूर्णांक wm0010_spi_probe(काष्ठा spi_device *spi)
अणु
	अचिन्हित दीर्घ gpio_flags;
	पूर्णांक ret;
	पूर्णांक trigger;
	पूर्णांक irq;
	काष्ठा wm0010_priv *wm0010;

	wm0010 = devm_kzalloc(&spi->dev, माप(*wm0010),
			      GFP_KERNEL);
	अगर (!wm0010)
		वापस -ENOMEM;

	mutex_init(&wm0010->lock);
	spin_lock_init(&wm0010->irq_lock);

	spi_set_drvdata(spi, wm0010);
	wm0010->dev = &spi->dev;

	अगर (dev_get_platdata(&spi->dev))
		स_नकल(&wm0010->pdata, dev_get_platdata(&spi->dev),
		       माप(wm0010->pdata));

	init_completion(&wm0010->boot_completion);

	wm0010->core_supplies[0].supply = "AVDD";
	wm0010->core_supplies[1].supply = "DCVDD";
	ret = devm_regulator_bulk_get(wm0010->dev, ARRAY_SIZE(wm0010->core_supplies),
				      wm0010->core_supplies);
	अगर (ret != 0) अणु
		dev_err(wm0010->dev, "Failed to obtain core supplies: %d\n",
			ret);
		वापस ret;
	पूर्ण

	wm0010->dbvdd = devm_regulator_get(wm0010->dev, "DBVDD");
	अगर (IS_ERR(wm0010->dbvdd)) अणु
		ret = PTR_ERR(wm0010->dbvdd);
		dev_err(wm0010->dev, "Failed to obtain DBVDD: %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (wm0010->pdata.gpio_reset) अणु
		wm0010->gpio_reset = wm0010->pdata.gpio_reset;

		अगर (wm0010->pdata.reset_active_high)
			wm0010->gpio_reset_value = 1;
		अन्यथा
			wm0010->gpio_reset_value = 0;

		अगर (wm0010->gpio_reset_value)
			gpio_flags = GPIOF_OUT_INIT_HIGH;
		अन्यथा
			gpio_flags = GPIOF_OUT_INIT_LOW;

		ret = devm_gpio_request_one(wm0010->dev, wm0010->gpio_reset,
					    gpio_flags, "wm0010 reset");
		अगर (ret < 0) अणु
			dev_err(wm0010->dev,
				"Failed to request GPIO for DSP reset: %d\n",
				ret);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_err(wm0010->dev, "No reset GPIO configured\n");
		वापस -EINVAL;
	पूर्ण

	wm0010->state = WM0010_POWER_OFF;

	irq = spi->irq;
	अगर (wm0010->pdata.irq_flags)
		trigger = wm0010->pdata.irq_flags;
	अन्यथा
		trigger = IRQF_TRIGGER_FALLING;
	trigger |= IRQF_ONESHOT;

	ret = request_thपढ़ोed_irq(irq, शून्य, wm0010_irq, trigger,
				   "wm0010", wm0010);
	अगर (ret) अणु
		dev_err(wm0010->dev, "Failed to request IRQ %d: %d\n",
			irq, ret);
		वापस ret;
	पूर्ण
	wm0010->irq = irq;

	ret = irq_set_irq_wake(irq, 1);
	अगर (ret) अणु
		dev_err(wm0010->dev, "Failed to set IRQ %d as wake source: %d\n",
			irq, ret);
		वापस ret;
	पूर्ण

	अगर (spi->max_speed_hz)
		wm0010->board_max_spi_speed = spi->max_speed_hz;
	अन्यथा
		wm0010->board_max_spi_speed = 0;

	ret = devm_snd_soc_रेजिस्टर_component(&spi->dev,
				     &soc_component_dev_wm0010, wm0010_dai,
				     ARRAY_SIZE(wm0010_dai));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wm0010_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा wm0010_priv *wm0010 = spi_get_drvdata(spi);

	gpio_set_value_cansleep(wm0010->gpio_reset,
				wm0010->gpio_reset_value);

	irq_set_irq_wake(wm0010->irq, 0);

	अगर (wm0010->irq)
		मुक्त_irq(wm0010->irq, wm0010);

	वापस 0;
पूर्ण

अटल काष्ठा spi_driver wm0010_spi_driver = अणु
	.driver = अणु
		.name	= "wm0010",
	पूर्ण,
	.probe		= wm0010_spi_probe,
	.हटाओ		= wm0010_spi_हटाओ,
पूर्ण;

module_spi_driver(wm0010_spi_driver);

MODULE_DESCRIPTION("ASoC WM0010 driver");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
