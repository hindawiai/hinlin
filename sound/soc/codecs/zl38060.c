<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
//
// Codec driver क्रम Microsemi ZL38060 Connected Home Audio Processor.
//
// Copyright(c) 2020 Sven Van Asbroeck

// The ZL38060 is very flexible and configurable. This driver implements only a
// tiny subset of the chip's possible configurations:
//
// - DSP block bypassed: DAI        routed straight to DACs
//                       microphone routed straight to DAI
// - chip's पूर्णांकernal घड़ी is driven by a 12 MHz बाह्यal crystal
// - chip's DAI connected to CPU is I2S, and bit + frame घड़ी master
// - chip must be strapped क्रम "host boot": in this mode, firmware will be
//   provided by this driver.

#समावेश <linux/gpio/consumer.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/property.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/regmap.h>
#समावेश <linux/module.h>
#समावेश <linux/ihex.h>

#समावेश <sound/pcm_params.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#घोषणा DRV_NAME		"zl38060"

#घोषणा ZL38_RATES		(SNDRV_PCM_RATE_8000  |\
				SNDRV_PCM_RATE_16000 |\
				SNDRV_PCM_RATE_48000)
#घोषणा ZL38_FORMATS		SNDRV_PCM_FMTBIT_S16_LE

#घोषणा HBI_FIRMWARE_PAGE	0xFF
#घोषणा ZL38_MAX_RAW_XFER	0x100

#घोषणा REG_TDMA_CFG_CLK	0x0262
#घोषणा CFG_CLK_PCLK_SHIFT	4
#घोषणा CFG_CLK_PCLK_MASK	(0x7ff << CFG_CLK_PCLK_SHIFT)
#घोषणा CFG_CLK_PCLK(bits)	((bits - 1) << CFG_CLK_PCLK_SHIFT)
#घोषणा CFG_CLK_MASTER		BIT(15)
#घोषणा CFG_CLK_FSRATE_MASK	0x7
#घोषणा CFG_CLK_FSRATE_8KHZ	0x1
#घोषणा CFG_CLK_FSRATE_16KHZ	0x2
#घोषणा CFG_CLK_FSRATE_48KHZ	0x6

#घोषणा REG_CLK_CFG		0x0016
#घोषणा CLK_CFG_SOURCE_XTAL	BIT(15)

#घोषणा REG_CLK_STATUS		0x0014
#घोषणा CLK_STATUS_HWRST	BIT(0)

#घोषणा REG_PARAM_RESULT	0x0034
#घोषणा PARAM_RESULT_READY	0xD3D3

#घोषणा REG_PG255_BASE_HI	0x000C
#घोषणा REG_PG255_OFFS(addr)	((HBI_FIRMWARE_PAGE << 8) | (addr & 0xFF))
#घोषणा REG_FWR_EXEC		0x012C

#घोषणा REG_CMD			0x0032
#घोषणा REG_HW_REV		0x0020
#घोषणा REG_FW_PROD		0x0022
#घोषणा REG_FW_REV		0x0024

#घोषणा REG_SEMA_FLAGS		0x0006
#घोषणा SEMA_FLAGS_BOOT_CMD	BIT(0)
#घोषणा SEMA_FLAGS_APP_REBOOT	BIT(1)

#घोषणा REG_HW_REV		0x0020
#घोषणा REG_FW_PROD		0x0022
#घोषणा REG_FW_REV		0x0024
#घोषणा REG_GPIO_सूची		0x02DC
#घोषणा REG_GPIO_DAT		0x02DA

#घोषणा BOOTCMD_LOAD_COMPLETE	0x000D
#घोषणा BOOTCMD_FW_GO		0x0008

#घोषणा FIRMWARE_MAJOR		2
#घोषणा FIRMWARE_MINOR		2

काष्ठा zl38_codec_priv अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
	bool is_stream_in_use[2];
	काष्ठा gpio_chip *gpio_chip;
पूर्ण;

अटल पूर्णांक zl38_fw_issue_command(काष्ठा regmap *regmap, u16 cmd)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो_poll_समयout(regmap, REG_SEMA_FLAGS, val,
				       !(val & SEMA_FLAGS_BOOT_CMD), 10000,
				       10000 * 100);
	अगर (err)
		वापस err;
	err = regmap_ग_लिखो(regmap, REG_CMD, cmd);
	अगर (err)
		वापस err;
	err = regmap_update_bits(regmap, REG_SEMA_FLAGS, SEMA_FLAGS_BOOT_CMD,
				 SEMA_FLAGS_BOOT_CMD);
	अगर (err)
		वापस err;

	वापस regmap_पढ़ो_poll_समयout(regmap, REG_CMD, val, !val, 10000,
					10000 * 100);
पूर्ण

अटल पूर्णांक zl38_fw_go(काष्ठा regmap *regmap)
अणु
	पूर्णांक err;

	err = zl38_fw_issue_command(regmap, BOOTCMD_LOAD_COMPLETE);
	अगर (err)
		वापस err;

	वापस zl38_fw_issue_command(regmap, BOOTCMD_FW_GO);
पूर्ण

अटल पूर्णांक zl38_fw_enter_boot_mode(काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_update_bits(regmap, REG_CLK_STATUS, CLK_STATUS_HWRST,
				 CLK_STATUS_HWRST);
	अगर (err)
		वापस err;

	वापस regmap_पढ़ो_poll_समयout(regmap, REG_PARAM_RESULT, val,
					val == PARAM_RESULT_READY, 1000, 50000);
पूर्ण

अटल पूर्णांक
zl38_fw_send_data(काष्ठा regmap *regmap, u32 addr, स्थिर व्योम *data, u16 len)
अणु
	__be32 addr_base = cpu_to_be32(addr & ~0xFF);
	पूर्णांक err;

	err = regmap_raw_ग_लिखो(regmap, REG_PG255_BASE_HI, &addr_base,
			       माप(addr_base));
	अगर (err)
		वापस err;
	वापस regmap_raw_ग_लिखो(regmap, REG_PG255_OFFS(addr), data, len);
पूर्ण

अटल पूर्णांक zl38_fw_send_xaddr(काष्ठा regmap *regmap, स्थिर व्योम *data)
अणु
	/* execution address from ihex: 32-bit little endian.
	 * device रेजिस्टर expects 32-bit big endian.
	 */
	u32 addr = le32_to_cpup(data);
	__be32 baddr = cpu_to_be32(addr);

	वापस regmap_raw_ग_लिखो(regmap, REG_FWR_EXEC, &baddr, माप(baddr));
पूर्ण

अटल पूर्णांक zl38_load_firmware(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	स्थिर काष्ठा ihex_binrec *rec;
	स्थिर काष्ठा firmware *fw;
	u32 addr;
	u16 len;
	पूर्णांक err;

	/* how to get this firmware:
	 * 1. request and करोwnload chip firmware from Microsemi
	 *    (provided by Microsemi in srec क्रमmat)
	 * 2. convert करोwnloaded firmware from srec to ihex. Simple tool:
	 *    https://gitlab.com/TheSven73/s3-to-irec
	 * 3. convert ihex to binary (.fw) using ihex2fw tool which is included
	 *    with the Linux kernel sources
	 */
	err = request_ihex_firmware(&fw, "zl38060.fw", dev);
	अगर (err)
		वापस err;
	err = zl38_fw_enter_boot_mode(regmap);
	अगर (err)
		जाओ out;
	rec = (स्थिर काष्ठा ihex_binrec *)fw->data;
	जबतक (rec) अणु
		addr = be32_to_cpu(rec->addr);
		len = be16_to_cpu(rec->len);
		अगर (addr) अणु
			/* regular data ihex record */
			err = zl38_fw_send_data(regmap, addr, rec->data, len);
		पूर्ण अन्यथा अगर (len == 4) अणु
			/* execution address ihex record */
			err = zl38_fw_send_xaddr(regmap, rec->data);
		पूर्ण अन्यथा अणु
			err = -EINVAL;
		पूर्ण
		अगर (err)
			जाओ out;
		/* next ! */
		rec = ihex_next_binrec(rec);
	पूर्ण
	err = zl38_fw_go(regmap);

out:
	release_firmware(fw);
	वापस err;
पूर्ण


अटल पूर्णांक zl38_software_reset(काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_update_bits(regmap, REG_SEMA_FLAGS, SEMA_FLAGS_APP_REBOOT,
				 SEMA_FLAGS_APP_REBOOT);
	अगर (err)
		वापस err;

	/* रुको क्रम host bus पूर्णांकerface to settle.
	 * Not sure अगर this is required: Microsemi's venकरोr driver करोes this,
	 * but the firmware manual करोes not mention it. Leave it in, there's
	 * little करोwnside, apart from a slower reset.
	 */
	msleep(50);

	वापस regmap_पढ़ो_poll_समयout(regmap, REG_SEMA_FLAGS, val,
					!(val & SEMA_FLAGS_APP_REBOOT), 10000,
					10000 * 100);
पूर्ण

अटल पूर्णांक zl38_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा zl38_codec_priv *priv = snd_soc_dai_get_drvdata(dai);
	पूर्णांक err;

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* firmware शेष is normal i2s */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		/* firmware शेष is normal bitघड़ी and frame */
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* always 32 bits per frame (= 16 bits/channel, 2 channels) */
		err = regmap_update_bits(priv->regmap, REG_TDMA_CFG_CLK,
					 CFG_CLK_MASTER | CFG_CLK_PCLK_MASK,
					 CFG_CLK_MASTER | CFG_CLK_PCLK(32));
		अगर (err)
			वापस err;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zl38_hw_params(काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा zl38_codec_priv *priv = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;
	अचिन्हित पूर्णांक fsrate;
	पूर्णांक err;

	/* We cannot change hw_params जबतक the dai is alपढ़ोy in use - the
	 * software reset will corrupt the audio. However, this is not required,
	 * as the chip's TDM buses are fully symmetric, which mandates identical
	 * rates, channels, and samplebits क्रम record and playback.
	 */
	अगर (priv->is_stream_in_use[!tx])
		जाओ skip_setup;

	चयन (params_rate(params)) अणु
	हाल 8000:
		fsrate = CFG_CLK_FSRATE_8KHZ;
		अवरोध;
	हाल 16000:
		fsrate = CFG_CLK_FSRATE_16KHZ;
		अवरोध;
	हाल 48000:
		fsrate = CFG_CLK_FSRATE_48KHZ;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	err = regmap_update_bits(priv->regmap, REG_TDMA_CFG_CLK,
				 CFG_CLK_FSRATE_MASK, fsrate);
	अगर (err)
		वापस err;

	/* chip requires a software reset to apply audio रेजिस्टर changes */
	err = zl38_software_reset(priv->regmap);
	अगर (err)
		वापस err;

skip_setup:
	priv->is_stream_in_use[tx] = true;

	वापस 0;
पूर्ण

अटल पूर्णांक zl38_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा zl38_codec_priv *priv = snd_soc_dai_get_drvdata(dai);
	bool tx = substream->stream == SNDRV_PCM_STREAM_PLAYBACK;

	priv->is_stream_in_use[tx] = false;

	वापस 0;
पूर्ण

/* stereo bypass with no AEC */
अटल स्थिर काष्ठा reg_sequence cp_config_stereo_bypass[] = अणु
	/* पूर्णांकerconnects must be programmed first */
	अणु 0x0210, 0x0005 पूर्ण,	/* DAC1   in <= I2S1-L */
	अणु 0x0212, 0x0006 पूर्ण,	/* DAC2   in <= I2S1-R */
	अणु 0x0214, 0x0001 पूर्ण,	/* I2S1-L in <= MIC1   */
	अणु 0x0216, 0x0001 पूर्ण,	/* I2S1-R in <= MIC1   */
	अणु 0x0224, 0x0000 पूर्ण,	/* AEC-S  in <= n/a    */
	अणु 0x0226, 0x0000 पूर्ण,	/* AEC-R  in <= n/a    */
	/* output enables must be programmed next */
	अणु 0x0202, 0x000F पूर्ण,	/* enable I2S1 + DAC   */
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops zl38_dai_ops = अणु
	.set_fmt = zl38_set_fmt,
	.hw_params = zl38_hw_params,
	.hw_मुक्त = zl38_hw_मुक्त,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver zl38_dai = अणु
	.name = "zl38060-tdma",
	.playback = अणु
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 2,
		.rates = ZL38_RATES,
		.क्रमmats = ZL38_FORMATS,
	पूर्ण,
	.capture = अणु
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 2,
		.rates = ZL38_RATES,
		.क्रमmats = ZL38_FORMATS,
	पूर्ण,
	.ops = &zl38_dai_ops,
	.symmetric_rate = 1,
	.symmetric_sample_bits = 1,
	.symmetric_channels = 1,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget zl38_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_OUTPUT("DAC1"),
	SND_SOC_DAPM_OUTPUT("DAC2"),

	SND_SOC_DAPM_INPUT("DMICL"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route zl38_dapm_routes[] = अणु
	अणु "DAC1",  शून्य, "Playback" पूर्ण,
	अणु "DAC2",  शून्य, "Playback" पूर्ण,

	अणु "Capture",  शून्य, "DMICL" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver zl38_component_dev = अणु
	.dapm_widमाला_लो		= zl38_dapm_widमाला_लो,
	.num_dapm_widमाला_लो	= ARRAY_SIZE(zl38_dapm_widमाला_लो),
	.dapm_routes		= zl38_dapm_routes,
	.num_dapm_routes	= ARRAY_SIZE(zl38_dapm_routes),
	.endianness		= 1,
	.non_legacy_dai_naming	= 1,
पूर्ण;

अटल व्योम chip_gpio_set(काष्ठा gpio_chip *c, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा regmap *regmap = gpiochip_get_data(c);
	अचिन्हित पूर्णांक mask = BIT(offset);

	regmap_update_bits(regmap, REG_GPIO_DAT, mask, val ? mask : 0);
पूर्ण

अटल पूर्णांक chip_gpio_get(काष्ठा gpio_chip *c, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा regmap *regmap = gpiochip_get_data(c);
	अचिन्हित पूर्णांक mask = BIT(offset);
	अचिन्हित पूर्णांक val;
	पूर्णांक err;

	err = regmap_पढ़ो(regmap, REG_GPIO_DAT, &val);
	अगर (err)
		वापस err;

	वापस !!(val & mask);
पूर्ण

अटल पूर्णांक chip_direction_input(काष्ठा gpio_chip *c, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा regmap *regmap = gpiochip_get_data(c);
	अचिन्हित पूर्णांक mask = BIT(offset);

	वापस regmap_update_bits(regmap, REG_GPIO_सूची, mask, 0);
पूर्ण

अटल पूर्णांक
chip_direction_output(काष्ठा gpio_chip *c, अचिन्हित पूर्णांक offset, पूर्णांक val)
अणु
	काष्ठा regmap *regmap = gpiochip_get_data(c);
	अचिन्हित पूर्णांक mask = BIT(offset);

	chip_gpio_set(c, offset, val);
	वापस regmap_update_bits(regmap, REG_GPIO_सूची, mask, mask);
पूर्ण

अटल स्थिर काष्ठा gpio_chip ढाँचा_chip = अणु
	.owner = THIS_MODULE,
	.label = DRV_NAME,

	.base = -1,
	.ngpio = 14,
	.direction_input = chip_direction_input,
	.direction_output = chip_direction_output,
	.get = chip_gpio_get,
	.set = chip_gpio_set,

	.can_sleep = true,
पूर्ण;

अटल पूर्णांक zl38_check_revision(काष्ठा device *dev, काष्ठा regmap *regmap)
अणु
	अचिन्हित पूर्णांक hwrev, fwprod, fwrev;
	पूर्णांक fw_major, fw_minor, fw_micro;
	पूर्णांक err;

	err = regmap_पढ़ो(regmap, REG_HW_REV, &hwrev);
	अगर (err)
		वापस err;
	err = regmap_पढ़ो(regmap, REG_FW_PROD, &fwprod);
	अगर (err)
		वापस err;
	err = regmap_पढ़ो(regmap, REG_FW_REV, &fwrev);
	अगर (err)
		वापस err;

	fw_major = (fwrev >> 12) & 0xF;
	fw_minor = (fwrev >>  8) & 0xF;
	fw_micro = fwrev & 0xFF;
	dev_info(dev, "hw rev 0x%x, fw product code %d, firmware rev %d.%d.%d",
		 hwrev & 0x1F, fwprod, fw_major, fw_minor, fw_micro);

	अगर (fw_major != FIRMWARE_MAJOR || fw_minor < FIRMWARE_MINOR) अणु
		dev_err(dev, "unsupported firmware. driver supports %d.%d",
			FIRMWARE_MAJOR, FIRMWARE_MINOR);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक zl38_bus_पढ़ो(व्योम *context,
			 स्थिर व्योम *reg_buf, माप_प्रकार reg_size,
			 व्योम *val_buf, माप_प्रकार val_size)
अणु
	काष्ठा spi_device *spi = context;
	स्थिर u8 *reg_buf8 = reg_buf;
	माप_प्रकार len = 0;
	u8 offs, page;
	u8 txbuf[4];

	अगर (reg_size != 2 || val_size > ZL38_MAX_RAW_XFER)
		वापस -EINVAL;

	offs = reg_buf8[1] >> 1;
	page = reg_buf8[0];

	अगर (page) अणु
		txbuf[len++] = 0xFE;
		txbuf[len++] = page == HBI_FIRMWARE_PAGE ? 0xFF : page - 1;
		txbuf[len++] = offs;
		txbuf[len++] = val_size / 2 - 1;
	पूर्ण अन्यथा अणु
		txbuf[len++] = offs | 0x80;
		txbuf[len++] = val_size / 2 - 1;
	पूर्ण

	वापस spi_ग_लिखो_then_पढ़ो(spi, txbuf, len, val_buf, val_size);
पूर्ण

अटल पूर्णांक zl38_bus_ग_लिखो(व्योम *context, स्थिर व्योम *data, माप_प्रकार count)
अणु
	काष्ठा spi_device *spi = context;
	u8 buf[4 + ZL38_MAX_RAW_XFER];
	माप_प्रकार val_len, len = 0;
	स्थिर u8 *data8 = data;
	u8 offs, page;

	अगर (count > (2 + ZL38_MAX_RAW_XFER) || count < 4)
		वापस -EINVAL;
	val_len = count - 2;
	offs = data8[1] >> 1;
	page = data8[0];

	अगर (page) अणु
		buf[len++] = 0xFE;
		buf[len++] = page == HBI_FIRMWARE_PAGE ? 0xFF : page - 1;
		buf[len++] = offs;
		buf[len++] = (val_len / 2 - 1) | 0x80;
	पूर्ण अन्यथा अणु
		buf[len++] = offs | 0x80;
		buf[len++] = (val_len / 2 - 1) | 0x80;
	पूर्ण
	स_नकल(buf + len, data8 + 2, val_len);
	len += val_len;

	वापस spi_ग_लिखो(spi, buf, len);
पूर्ण

अटल स्थिर काष्ठा regmap_bus zl38_regmap_bus = अणु
	.पढ़ो = zl38_bus_पढ़ो,
	.ग_लिखो = zl38_bus_ग_लिखो,
	.max_raw_ग_लिखो = ZL38_MAX_RAW_XFER,
	.max_raw_पढ़ो = ZL38_MAX_RAW_XFER,
पूर्ण;

अटल स्थिर काष्ठा regmap_config zl38_regmap_conf = अणु
	.reg_bits = 16,
	.val_bits = 16,
	.reg_stride = 2,
	.use_single_पढ़ो = true,
	.use_single_ग_लिखो = true,
पूर्ण;

अटल पूर्णांक zl38_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा device *dev = &spi->dev;
	काष्ठा zl38_codec_priv *priv;
	काष्ठा gpio_desc *reset_gpio;
	पूर्णांक err;

	/* get the chip to a known state by putting it in reset */
	reset_gpio = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_HIGH);
	अगर (IS_ERR(reset_gpio))
		वापस PTR_ERR(reset_gpio);
	अगर (reset_gpio) अणु
		/* datasheet: need > 10us क्रम a digital + analog reset */
		usleep_range(15, 50);
		/* take the chip out of reset */
		gpiod_set_value_cansleep(reset_gpio, 0);
		/* datasheet: need > 3ms क्रम digital section to become stable */
		usleep_range(3000, 10000);
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->dev = dev;
	dev_set_drvdata(dev, priv);
	priv->regmap = devm_regmap_init(dev, &zl38_regmap_bus, spi,
					&zl38_regmap_conf);
	अगर (IS_ERR(priv->regmap))
		वापस PTR_ERR(priv->regmap);

	err = zl38_load_firmware(dev, priv->regmap);
	अगर (err)
		वापस err;

	err = zl38_check_revision(dev, priv->regmap);
	अगर (err)
		वापस err;

	priv->gpio_chip = devm_kmemdup(dev, &ढाँचा_chip,
				       माप(ढाँचा_chip), GFP_KERNEL);
	अगर (!priv->gpio_chip)
		वापस -ENOMEM;
#अगर_घोषित CONFIG_OF_GPIO
	priv->gpio_chip->of_node = dev->of_node;
#पूर्ण_अगर
	err = devm_gpiochip_add_data(dev, priv->gpio_chip, priv->regmap);
	अगर (err)
		वापस err;

	/* setup the cross-poपूर्णांक चयन क्रम stereo bypass */
	err = regmap_multi_reg_ग_लिखो(priv->regmap, cp_config_stereo_bypass,
				     ARRAY_SIZE(cp_config_stereo_bypass));
	अगर (err)
		वापस err;
	/* setup क्रम 12MHz crystal connected to the chip */
	err = regmap_update_bits(priv->regmap, REG_CLK_CFG, CLK_CFG_SOURCE_XTAL,
				 CLK_CFG_SOURCE_XTAL);
	अगर (err)
		वापस err;

	वापस devm_snd_soc_रेजिस्टर_component(dev, &zl38_component_dev,
					       &zl38_dai, 1);
पूर्ण

अटल स्थिर काष्ठा of_device_id zl38_dt_ids[] = अणु
	अणु .compatible = "mscc,zl38060", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, zl38_dt_ids);

अटल स्थिर काष्ठा spi_device_id zl38_spi_ids[] = अणु
	अणु "zl38060", 0 पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, zl38_spi_ids);

अटल काष्ठा spi_driver zl38060_spi_driver = अणु
	.driver	= अणु
		.name = DRV_NAME,
		.of_match_table = of_match_ptr(zl38_dt_ids),
	पूर्ण,
	.probe = zl38_spi_probe,
	.id_table = zl38_spi_ids,
पूर्ण;
module_spi_driver(zl38060_spi_driver);

MODULE_DESCRIPTION("ASoC ZL38060 driver");
MODULE_AUTHOR("Sven Van Asbroeck <TheSven73@gmail.com>");
MODULE_LICENSE("GPL v2");
