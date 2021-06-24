<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Silicon Lअसल Si2161 DVB-T and Si2165 DVB-C/-T Demodulator
 *
 *  Copyright (C) 2013-2017 Matthias Schwarzott <zzam@gentoo.org>
 *
 *  References:
 *  https://www.siद_असल.com/Support%20Documents/TechnicalDocs/Si2165-लघु.pdf
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/regmap.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_गणित.स>
#समावेश "si2165_priv.h"
#समावेश "si2165.h"

/*
 * Hauppauge WinTV-HVR-930C-HD B130 / PCTV QuatroStick 521e 1113xx
 * uses 16 MHz xtal
 *
 * Hauppauge WinTV-HVR-930C-HD B131 / PCTV QuatroStick 522e 1114xx
 * uses 24 MHz घड़ी provided by tuner
 */

काष्ठा si2165_state अणु
	काष्ठा i2c_client *client;

	काष्ठा regmap *regmap;

	काष्ठा dvb_frontend fe;

	काष्ठा si2165_config config;

	u8 chip_revcode;
	u8 chip_type;

	/* calculated by xtal and भाग settings */
	u32 fvco_hz;
	u32 sys_clk;
	u32 adc_clk;

	/* DVBv3 stats */
	u64 ber_prev;

	bool has_dvbc;
	bool has_dvbt;
	bool firmware_loaded;
पूर्ण;

अटल पूर्णांक si2165_ग_लिखो(काष्ठा si2165_state *state, स्थिर u16 reg,
			स्थिर u8 *src, स्थिर पूर्णांक count)
अणु
	पूर्णांक ret;

	dev_dbg(&state->client->dev, "i2c write: reg: 0x%04x, data: %*ph\n",
		reg, count, src);

	ret = regmap_bulk_ग_लिखो(state->regmap, reg, src, count);

	अगर (ret)
		dev_err(&state->client->dev, "%s: ret == %d\n", __func__, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक si2165_पढ़ो(काष्ठा si2165_state *state,
		       स्थिर u16 reg, u8 *val, स्थिर पूर्णांक count)
अणु
	पूर्णांक ret = regmap_bulk_पढ़ो(state->regmap, reg, val, count);

	अगर (ret) अणु
		dev_err(&state->client->dev, "%s: error (addr %02x reg %04x error (ret == %i)\n",
			__func__, state->config.i2c_addr, reg, ret);
		वापस ret;
	पूर्ण

	dev_dbg(&state->client->dev, "i2c read: reg: 0x%04x, data: %*ph\n",
		reg, count, val);

	वापस 0;
पूर्ण

अटल पूर्णांक si2165_पढ़ोreg8(काष्ठा si2165_state *state,
			   स्थिर u16 reg, u8 *val)
अणु
	अचिन्हित पूर्णांक val_पंचांगp;
	पूर्णांक ret = regmap_पढ़ो(state->regmap, reg, &val_पंचांगp);
	*val = (u8)val_पंचांगp;
	dev_dbg(&state->client->dev, "reg read: R(0x%04x)=0x%02x\n", reg, *val);
	वापस ret;
पूर्ण

अटल पूर्णांक si2165_पढ़ोreg16(काष्ठा si2165_state *state,
			    स्थिर u16 reg, u16 *val)
अणु
	u8 buf[2];

	पूर्णांक ret = si2165_पढ़ो(state, reg, buf, 2);
	*val = buf[0] | buf[1] << 8;
	dev_dbg(&state->client->dev, "reg read: R(0x%04x)=0x%04x\n", reg, *val);
	वापस ret;
पूर्ण

अटल पूर्णांक si2165_पढ़ोreg24(काष्ठा si2165_state *state,
			    स्थिर u16 reg, u32 *val)
अणु
	u8 buf[3];

	पूर्णांक ret = si2165_पढ़ो(state, reg, buf, 3);
	*val = buf[0] | buf[1] << 8 | buf[2] << 16;
	dev_dbg(&state->client->dev, "reg read: R(0x%04x)=0x%06x\n", reg, *val);
	वापस ret;
पूर्ण

अटल पूर्णांक si2165_ग_लिखोreg8(काष्ठा si2165_state *state, स्थिर u16 reg, u8 val)
अणु
	वापस regmap_ग_लिखो(state->regmap, reg, val);
पूर्ण

अटल पूर्णांक si2165_ग_लिखोreg16(काष्ठा si2165_state *state, स्थिर u16 reg, u16 val)
अणु
	u8 buf[2] = अणु val & 0xff, (val >> 8) & 0xff पूर्ण;

	वापस si2165_ग_लिखो(state, reg, buf, 2);
पूर्ण

अटल पूर्णांक si2165_ग_लिखोreg24(काष्ठा si2165_state *state, स्थिर u16 reg, u32 val)
अणु
	u8 buf[3] = अणु val & 0xff, (val >> 8) & 0xff, (val >> 16) & 0xff पूर्ण;

	वापस si2165_ग_लिखो(state, reg, buf, 3);
पूर्ण

अटल पूर्णांक si2165_ग_लिखोreg32(काष्ठा si2165_state *state, स्थिर u16 reg, u32 val)
अणु
	u8 buf[4] = अणु
		val & 0xff,
		(val >> 8) & 0xff,
		(val >> 16) & 0xff,
		(val >> 24) & 0xff
	पूर्ण;
	वापस si2165_ग_लिखो(state, reg, buf, 4);
पूर्ण

अटल पूर्णांक si2165_ग_लिखोreg_mask8(काष्ठा si2165_state *state, स्थिर u16 reg,
				 u8 val, u8 mask)
अणु
	अगर (mask != 0xff) अणु
		u8 पंचांगp;
		पूर्णांक ret = si2165_पढ़ोreg8(state, reg, &पंचांगp);

		अगर (ret < 0)
			वापस ret;

		val &= mask;
		पंचांगp &= ~mask;
		val |= पंचांगp;
	पूर्ण
	वापस si2165_ग_लिखोreg8(state, reg, val);
पूर्ण

#घोषणा REG16(reg, val) \
	अणु (reg), (val) & 0xff पूर्ण, \
	अणु (reg) + 1, (val) >> 8 & 0xff पूर्ण
काष्ठा si2165_reg_value_pair अणु
	u16 reg;
	u8 val;
पूर्ण;

अटल पूर्णांक si2165_ग_लिखो_reg_list(काष्ठा si2165_state *state,
				 स्थिर काष्ठा si2165_reg_value_pair *regs,
				 पूर्णांक count)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < count; i++) अणु
		ret = si2165_ग_लिखोreg8(state, regs[i].reg, regs[i].val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक si2165_get_tune_settings(काष्ठा dvb_frontend *fe,
				    काष्ठा dvb_frontend_tune_settings *s)
अणु
	s->min_delay_ms = 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक si2165_init_pll(काष्ठा si2165_state *state)
अणु
	u32 ref_freq_hz = state->config.ref_freq_hz;
	u8 भागr = 1; /* 1..7 */
	u8 भागp = 1; /* only 1 or 4 */
	u8 भागn = 56; /* 1..63 */
	u8 भागm = 8;
	u8 भागl = 12;
	u8 buf[4];

	/*
	 * hardcoded values can be deleted अगर calculation is verअगरied
	 * or it yields the same values as the winकरोws driver
	 */
	चयन (ref_freq_hz) अणु
	हाल 16000000u:
		भागn = 56;
		अवरोध;
	हाल 24000000u:
		भागr = 2;
		भागp = 4;
		भागn = 19;
		अवरोध;
	शेष:
		/* ref_freq / भागr must be between 4 and 16 MHz */
		अगर (ref_freq_hz > 16000000u)
			भागr = 2;

		/*
		 * now select भागn and भागp such that
		 * fvco is in 1624..1824 MHz
		 */
		अगर (1624000000u * भागr > ref_freq_hz * 2u * 63u)
			भागp = 4;

		/* is this alपढ़ोy correct regarding rounding? */
		भागn = 1624000000u * भागr / (ref_freq_hz * 2u * भागp);
		अवरोध;
	पूर्ण

	/* adc_clk and sys_clk depend on xtal and pll settings */
	state->fvco_hz = ref_freq_hz / भागr
			* 2u * भागn * भागp;
	state->adc_clk = state->fvco_hz / (भागm * 4u);
	state->sys_clk = state->fvco_hz / (भागl * 2u);

	/* ग_लिखो all 4 pll रेजिस्टरs 0x00a0..0x00a3 at once */
	buf[0] = भागl;
	buf[1] = भागm;
	buf[2] = (भागn & 0x3f) | ((भागp == 1) ? 0x40 : 0x00) | 0x80;
	buf[3] = भागr;
	वापस si2165_ग_लिखो(state, REG_PLL_DIVL, buf, 4);
पूर्ण

अटल पूर्णांक si2165_adjust_pll_भागl(काष्ठा si2165_state *state, u8 भागl)
अणु
	state->sys_clk = state->fvco_hz / (भागl * 2u);
	वापस si2165_ग_लिखोreg8(state, REG_PLL_DIVL, भागl);
पूर्ण

अटल u32 si2165_get_fe_clk(काष्ठा si2165_state *state)
अणु
	/* assume Oversampling mode Ovr4 is used */
	वापस state->adc_clk;
पूर्ण

अटल पूर्णांक si2165_रुको_init_करोne(काष्ठा si2165_state *state)
अणु
	पूर्णांक ret;
	u8 val = 0;
	पूर्णांक i;

	क्रम (i = 0; i < 3; ++i) अणु
		ret = si2165_पढ़ोreg8(state, REG_INIT_DONE, &val);
		अगर (ret < 0)
			वापस ret;
		अगर (val == 0x01)
			वापस 0;
		usleep_range(1000, 50000);
	पूर्ण
	dev_err(&state->client->dev, "init_done was not set\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक si2165_upload_firmware_block(काष्ठा si2165_state *state,
					स्थिर u8 *data, u32 len, u32 *poffset,
					u32 block_count)
अणु
	पूर्णांक ret;
	u8 buf_ctrl[4] = अणु 0x00, 0x00, 0x00, 0xc0 पूर्ण;
	u8 wordcount;
	u32 cur_block = 0;
	u32 offset = poffset ? *poffset : 0;

	अगर (len < 4)
		वापस -EINVAL;
	अगर (len % 4 != 0)
		वापस -EINVAL;

	dev_dbg(&state->client->dev,
		"fw load: %s: called with len=0x%x offset=0x%x blockcount=0x%x\n",
		__func__, len, offset, block_count);
	जबतक (offset + 12 <= len && cur_block < block_count) अणु
		dev_dbg(&state->client->dev,
			"fw load: %s: in while len=0x%x offset=0x%x cur_block=0x%x blockcount=0x%x\n",
			__func__, len, offset, cur_block, block_count);
		wordcount = data[offset];
		अगर (wordcount < 1 || data[offset + 1] ||
		    data[offset + 2] || data[offset + 3]) अणु
			dev_warn(&state->client->dev,
				 "bad fw data[0..3] = %*ph\n",
				 4, data);
			वापस -EINVAL;
		पूर्ण

		अगर (offset + 8 + wordcount * 4 > len) अणु
			dev_warn(&state->client->dev,
				 "len is too small for block len=%d, wordcount=%d\n",
				len, wordcount);
			वापस -EINVAL;
		पूर्ण

		buf_ctrl[0] = wordcount - 1;

		ret = si2165_ग_लिखो(state, REG_DCOM_CONTROL_BYTE, buf_ctrl, 4);
		अगर (ret < 0)
			जाओ error;
		ret = si2165_ग_लिखो(state, REG_DCOM_ADDR, data + offset + 4, 4);
		अगर (ret < 0)
			जाओ error;

		offset += 8;

		जबतक (wordcount > 0) अणु
			ret = si2165_ग_लिखो(state, REG_DCOM_DATA,
					   data + offset, 4);
			अगर (ret < 0)
				जाओ error;
			wordcount--;
			offset += 4;
		पूर्ण
		cur_block++;
	पूर्ण

	dev_dbg(&state->client->dev,
		"fw load: %s: after while len=0x%x offset=0x%x cur_block=0x%x blockcount=0x%x\n",
		__func__, len, offset, cur_block, block_count);

	अगर (poffset)
		*poffset = offset;

	dev_dbg(&state->client->dev,
		"fw load: %s: returned offset=0x%x\n",
		__func__, offset);

	वापस 0;
error:
	वापस ret;
पूर्ण

अटल पूर्णांक si2165_upload_firmware(काष्ठा si2165_state *state)
अणु
	/* पूर्णांक ret; */
	u8 val[3];
	u16 val16;
	पूर्णांक ret;

	स्थिर काष्ठा firmware *fw = शून्य;
	u8 *fw_file;
	स्थिर u8 *data;
	u32 len;
	u32 offset;
	u8 patch_version;
	u8 block_count;
	u16 crc_expected;

	चयन (state->chip_revcode) अणु
	हाल 0x03: /* revision D */
		fw_file = SI2165_FIRMWARE_REV_D;
		अवरोध;
	शेष:
		dev_info(&state->client->dev, "no firmware file for revision=%d\n",
			 state->chip_revcode);
		वापस 0;
	पूर्ण

	/* request the firmware, this will block and समयout */
	ret = request_firmware(&fw, fw_file, &state->client->dev);
	अगर (ret) अणु
		dev_warn(&state->client->dev, "firmware file '%s' not found\n",
			 fw_file);
		जाओ error;
	पूर्ण

	data = fw->data;
	len = fw->size;

	dev_info(&state->client->dev, "downloading firmware from file '%s' size=%d\n",
		 fw_file, len);

	अगर (len % 4 != 0) अणु
		dev_warn(&state->client->dev, "firmware size is not multiple of 4\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* check header (8 bytes) */
	अगर (len < 8) अणु
		dev_warn(&state->client->dev, "firmware header is missing\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (data[0] != 1 || data[1] != 0) अणु
		dev_warn(&state->client->dev, "firmware file version is wrong\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	patch_version = data[2];
	block_count = data[4];
	crc_expected = data[7] << 8 | data[6];

	/* start uploading fw */
	/* boot/wकरोg status */
	ret = si2165_ग_लिखोreg8(state, REG_WDOG_AND_BOOT, 0x00);
	अगर (ret < 0)
		जाओ error;
	/* reset */
	ret = si2165_ग_लिखोreg8(state, REG_RST_ALL, 0x00);
	अगर (ret < 0)
		जाओ error;
	/* boot/wकरोg status */
	ret = si2165_पढ़ोreg8(state, REG_WDOG_AND_BOOT, val);
	अगर (ret < 0)
		जाओ error;

	/* enable reset on error */
	ret = si2165_पढ़ोreg8(state, REG_EN_RST_ERROR, val);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_पढ़ोreg8(state, REG_EN_RST_ERROR, val);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_ग_लिखोreg8(state, REG_EN_RST_ERROR, 0x02);
	अगर (ret < 0)
		जाओ error;

	/* start right after the header */
	offset = 8;

	dev_info(&state->client->dev, "%s: extracted patch_version=0x%02x, block_count=0x%02x, crc_expected=0x%04x\n",
		 __func__, patch_version, block_count, crc_expected);

	ret = si2165_upload_firmware_block(state, data, len, &offset, 1);
	अगर (ret < 0)
		जाओ error;

	ret = si2165_ग_लिखोreg8(state, REG_PATCH_VERSION, patch_version);
	अगर (ret < 0)
		जाओ error;

	/* reset crc */
	ret = si2165_ग_लिखोreg8(state, REG_RST_CRC, 0x01);
	अगर (ret)
		जाओ error;

	ret = si2165_upload_firmware_block(state, data, len,
					   &offset, block_count);
	अगर (ret < 0) अणु
		dev_err(&state->client->dev,
			"firmware could not be uploaded\n");
		जाओ error;
	पूर्ण

	/* पढ़ो crc */
	ret = si2165_पढ़ोreg16(state, REG_CRC, &val16);
	अगर (ret)
		जाओ error;

	अगर (val16 != crc_expected) अणु
		dev_err(&state->client->dev,
			"firmware crc mismatch %04x != %04x\n",
			val16, crc_expected);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	ret = si2165_upload_firmware_block(state, data, len, &offset, 5);
	अगर (ret)
		जाओ error;

	अगर (len != offset) अणु
		dev_err(&state->client->dev,
			"firmware len mismatch %04x != %04x\n",
			len, offset);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* reset watchकरोg error रेजिस्टर */
	ret = si2165_ग_लिखोreg_mask8(state, REG_WDOG_AND_BOOT, 0x02, 0x02);
	अगर (ret < 0)
		जाओ error;

	/* enable reset on error */
	ret = si2165_ग_लिखोreg_mask8(state, REG_EN_RST_ERROR, 0x01, 0x01);
	अगर (ret < 0)
		जाओ error;

	dev_info(&state->client->dev, "fw load finished\n");

	ret = 0;
	state->firmware_loaded = true;
error:
	अगर (fw) अणु
		release_firmware(fw);
		fw = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक si2165_init(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret = 0;
	काष्ठा si2165_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u8 val;
	u8 patch_version = 0x00;

	dev_dbg(&state->client->dev, "%s: called\n", __func__);

	/* घातerup */
	ret = si2165_ग_लिखोreg8(state, REG_CHIP_MODE, state->config.chip_mode);
	अगर (ret < 0)
		जाओ error;
	/* dsp_घड़ी_enable */
	ret = si2165_ग_लिखोreg8(state, REG_DSP_CLOCK, 0x01);
	अगर (ret < 0)
		जाओ error;
	/* verअगरy chip_mode */
	ret = si2165_पढ़ोreg8(state, REG_CHIP_MODE, &val);
	अगर (ret < 0)
		जाओ error;
	अगर (val != state->config.chip_mode) अणु
		dev_err(&state->client->dev, "could not set chip_mode\n");
		वापस -EINVAL;
	पूर्ण

	/* agc */
	ret = si2165_ग_लिखोreg8(state, REG_AGC_IF_TRI, 0x00);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_ग_लिखोreg8(state, REG_AGC_IF_SLR, 0x01);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_ग_लिखोreg8(state, REG_AGC2_OUTPUT, 0x00);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_ग_लिखोreg8(state, REG_AGC2_CLKDIV, 0x07);
	अगर (ret < 0)
		जाओ error;
	/* rssi pad */
	ret = si2165_ग_लिखोreg8(state, REG_RSSI_PAD_CTRL, 0x00);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_ग_लिखोreg8(state, REG_RSSI_ENABLE, 0x00);
	अगर (ret < 0)
		जाओ error;

	ret = si2165_init_pll(state);
	अगर (ret < 0)
		जाओ error;

	/* enable chip_init */
	ret = si2165_ग_लिखोreg8(state, REG_CHIP_INIT, 0x01);
	अगर (ret < 0)
		जाओ error;
	/* set start_init */
	ret = si2165_ग_लिखोreg8(state, REG_START_INIT, 0x01);
	अगर (ret < 0)
		जाओ error;
	ret = si2165_रुको_init_करोne(state);
	अगर (ret < 0)
		जाओ error;

	/* disable chip_init */
	ret = si2165_ग_लिखोreg8(state, REG_CHIP_INIT, 0x00);
	अगर (ret < 0)
		जाओ error;

	/* ber_pkt - शेष 65535 */
	ret = si2165_ग_लिखोreg16(state, REG_BER_PKT,
				STATISTICS_PERIOD_PKT_COUNT);
	अगर (ret < 0)
		जाओ error;

	ret = si2165_पढ़ोreg8(state, REG_PATCH_VERSION, &patch_version);
	अगर (ret < 0)
		जाओ error;

	ret = si2165_ग_लिखोreg8(state, REG_AUTO_RESET, 0x00);
	अगर (ret < 0)
		जाओ error;

	/* dsp_addr_jump */
	ret = si2165_ग_लिखोreg32(state, REG_ADDR_JUMP, 0xf4000000);
	अगर (ret < 0)
		जाओ error;
	/* boot/wकरोg status */
	ret = si2165_पढ़ोreg8(state, REG_WDOG_AND_BOOT, &val);
	अगर (ret < 0)
		जाओ error;

	अगर (patch_version == 0x00) अणु
		ret = si2165_upload_firmware(state);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	/* ts output config */
	ret = si2165_ग_लिखोreg8(state, REG_TS_DATA_MODE, 0x20);
	अगर (ret < 0)
		वापस ret;
	ret = si2165_ग_लिखोreg16(state, REG_TS_TRI, 0x00fe);
	अगर (ret < 0)
		वापस ret;
	ret = si2165_ग_लिखोreg24(state, REG_TS_SLR, 0x555555);
	अगर (ret < 0)
		वापस ret;
	ret = si2165_ग_लिखोreg8(state, REG_TS_CLK_MODE, 0x01);
	अगर (ret < 0)
		वापस ret;
	ret = si2165_ग_लिखोreg8(state, REG_TS_PARALLEL_MODE, 0x00);
	अगर (ret < 0)
		वापस ret;

	c = &state->fe.dtv_property_cache;
	c->cnr.len = 1;
	c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_error.len = 1;
	c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	c->post_bit_count.len = 1;
	c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	वापस 0;
error:
	वापस ret;
पूर्ण

अटल पूर्णांक si2165_sleep(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा si2165_state *state = fe->demodulator_priv;

	/* dsp घड़ी disable */
	ret = si2165_ग_लिखोreg8(state, REG_DSP_CLOCK, 0x00);
	अगर (ret < 0)
		वापस ret;
	/* chip mode */
	ret = si2165_ग_लिखोreg8(state, REG_CHIP_MODE, SI2165_MODE_OFF);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक si2165_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	पूर्णांक ret;
	u8 u8पंचांगp;
	u32 u32पंचांगp;
	काष्ठा si2165_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;

	*status = 0;

	चयन (delsys) अणु
	हाल SYS_DVBT:
		/* check fast संकेत type */
		ret = si2165_पढ़ोreg8(state, REG_CHECK_SIGNAL, &u8पंचांगp);
		अगर (ret < 0)
			वापस ret;
		चयन (u8पंचांगp & 0x3) अणु
		हाल 0: /* searching */
		हाल 1: /* nothing */
			अवरोध;
		हाल 2: /* digital संकेत */
			*status |= FE_HAS_SIGNAL | FE_HAS_CARRIER;
			अवरोध;
		पूर्ण
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		/* check packet sync lock */
		ret = si2165_पढ़ोreg8(state, REG_PS_LOCK, &u8पंचांगp);
		अगर (ret < 0)
			वापस ret;
		अगर (u8पंचांगp & 0x01) अणु
			*status |= FE_HAS_SIGNAL;
			*status |= FE_HAS_CARRIER;
			*status |= FE_HAS_VITERBI;
			*status |= FE_HAS_SYNC;
		पूर्ण
		अवरोध;
	पूर्ण

	/* check fec_lock */
	ret = si2165_पढ़ोreg8(state, REG_FEC_LOCK, &u8पंचांगp);
	अगर (ret < 0)
		वापस ret;
	अगर (u8पंचांगp & 0x01) अणु
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	पूर्ण

	/* CNR */
	अगर (delsys == SYS_DVBC_ANNEX_A && *status & FE_HAS_VITERBI) अणु
		ret = si2165_पढ़ोreg24(state, REG_C_N, &u32पंचांगp);
		अगर (ret < 0)
			वापस ret;
		/*
		 * svalue =
		 * 1000 * c_n/dB =
		 * 1000 * 10 * log10(2^24 / regval) =
		 * 1000 * 10 * (log10(2^24) - log10(regval)) =
		 * 1000 * 10 * (पूर्णांकlog10(2^24) - पूर्णांकlog10(regval)) / 2^24
		 *
		 * पूर्णांकlog10(x) = log10(x) * 2^24
		 * पूर्णांकlog10(2^24) = log10(2^24) * 2^24 = 121210686
		 */
		u32पंचांगp = (1000 * 10 * (121210686 - (u64)पूर्णांकlog10(u32पंचांगp)))
				>> 24;
		c->cnr.stat[0].scale = FE_SCALE_DECIBEL;
		c->cnr.stat[0].svalue = u32पंचांगp;
	पूर्ण अन्यथा
		c->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;

	/* BER */
	अगर (*status & FE_HAS_VITERBI) अणु
		अगर (c->post_bit_error.stat[0].scale == FE_SCALE_NOT_AVAILABLE) अणु
			/* start new sampling period to get rid of old data*/
			ret = si2165_ग_लिखोreg8(state, REG_BER_RST, 0x01);
			अगर (ret < 0)
				वापस ret;

			/* set scale to enter पढ़ो code on next call */
			c->post_bit_error.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_count.stat[0].scale = FE_SCALE_COUNTER;
			c->post_bit_error.stat[0].uvalue = 0;
			c->post_bit_count.stat[0].uvalue = 0;

			/*
			 * reset DVBv3 value to deliver a good result
			 * क्रम the first call
			 */
			state->ber_prev = 0;

		पूर्ण अन्यथा अणु
			ret = si2165_पढ़ोreg8(state, REG_BER_AVAIL, &u8पंचांगp);
			अगर (ret < 0)
				वापस ret;

			अगर (u8पंचांगp & 1) अणु
				u32 biterrcnt;

				ret = si2165_पढ़ोreg24(state, REG_BER_BIT,
							&biterrcnt);
				अगर (ret < 0)
					वापस ret;

				c->post_bit_error.stat[0].uvalue +=
					biterrcnt;
				c->post_bit_count.stat[0].uvalue +=
					STATISTICS_PERIOD_BIT_COUNT;

				/* start new sampling period */
				ret = si2165_ग_लिखोreg8(state,
							REG_BER_RST, 0x01);
				अगर (ret < 0)
					वापस ret;

				dev_dbg(&state->client->dev,
					"post_bit_error=%u post_bit_count=%u\n",
					biterrcnt, STATISTICS_PERIOD_BIT_COUNT);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		c->post_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
		c->post_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक si2165_पढ़ो_snr(काष्ठा dvb_frontend *fe, u16 *snr)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->cnr.stat[0].scale == FE_SCALE_DECIBEL)
		*snr = भाग_s64(c->cnr.stat[0].svalue, 100);
	अन्यथा
		*snr = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक si2165_पढ़ो_ber(काष्ठा dvb_frontend *fe, u32 *ber)
अणु
	काष्ठा si2165_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	अगर (c->post_bit_error.stat[0].scale != FE_SCALE_COUNTER) अणु
		*ber = 0;
		वापस 0;
	पूर्ण

	*ber = c->post_bit_error.stat[0].uvalue - state->ber_prev;
	state->ber_prev = c->post_bit_error.stat[0].uvalue;

	वापस 0;
पूर्ण

अटल पूर्णांक si2165_set_oversamp(काष्ठा si2165_state *state, u32 dvb_rate)
अणु
	u64 oversamp;
	u32 reg_value;

	अगर (!dvb_rate)
		वापस -EINVAL;

	oversamp = si2165_get_fe_clk(state);
	oversamp <<= 23;
	करो_भाग(oversamp, dvb_rate);
	reg_value = oversamp & 0x3fffffff;

	dev_dbg(&state->client->dev, "Write oversamp=%#x\n", reg_value);
	वापस si2165_ग_लिखोreg32(state, REG_OVERSAMP, reg_value);
पूर्ण

अटल पूर्णांक si2165_set_अगर_freq_shअगरt(काष्ठा si2165_state *state)
अणु
	काष्ठा dvb_frontend *fe = &state->fe;
	u64 अगर_freq_shअगरt;
	s32 reg_value = 0;
	u32 fe_clk = si2165_get_fe_clk(state);
	u32 IF = 0;

	अगर (!fe->ops.tuner_ops.get_अगर_frequency) अणु
		dev_err(&state->client->dev,
			"Error: get_if_frequency() not defined at tuner. Can't work without it!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!fe_clk)
		वापस -EINVAL;

	fe->ops.tuner_ops.get_अगर_frequency(fe, &IF);
	अगर_freq_shअगरt = IF;
	अगर_freq_shअगरt <<= 29;

	करो_भाग(अगर_freq_shअगरt, fe_clk);
	reg_value = (s32)अगर_freq_shअगरt;

	अगर (state->config.inversion)
		reg_value = -reg_value;

	reg_value = reg_value & 0x1fffffff;

	/* अगर_freq_shअगरt, usbdump contained 0x023ee08f; */
	वापस si2165_ग_लिखोreg32(state, REG_IF_FREQ_SHIFT, reg_value);
पूर्ण

अटल स्थिर काष्ठा si2165_reg_value_pair dvbt_regs[] = अणु
	/* standard = DVB-T */
	अणु REG_DVB_STANDARD, 0x01 पूर्ण,
	/* impulsive_noise_हटाओr */
	अणु REG_IMPULSIVE_NOISE_REM, 0x01 पूर्ण,
	अणु REG_AUTO_RESET, 0x00 पूर्ण,
	/* agc2 */
	अणु REG_AGC2_MIN, 0x41 पूर्ण,
	अणु REG_AGC2_KACQ, 0x0e पूर्ण,
	अणु REG_AGC2_KLOC, 0x10 पूर्ण,
	/* agc */
	अणु REG_AGC_UNFREEZE_THR, 0x03 पूर्ण,
	अणु REG_AGC_CRESTF_DBX8, 0x78 पूर्ण,
	/* agc */
	अणु REG_AAF_CRESTF_DBX8, 0x78 पूर्ण,
	अणु REG_ACI_CRESTF_DBX8, 0x68 पूर्ण,
	/* freq_sync_range */
	REG16(REG_FREQ_SYNC_RANGE, 0x0064),
	/* gp_reg0 */
	अणु REG_GP_REG0_MSB, 0x00 पूर्ण
पूर्ण;

अटल पूर्णांक si2165_set_frontend_dvbt(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा si2165_state *state = fe->demodulator_priv;
	u32 dvb_rate = 0;
	u16 bw10k;
	u32 bw_hz = p->bandwidth_hz;

	dev_dbg(&state->client->dev, "%s: called\n", __func__);

	अगर (!state->has_dvbt)
		वापस -EINVAL;

	/* no bandwidth स्वतः-detection */
	अगर (bw_hz == 0)
		वापस -EINVAL;

	dvb_rate = bw_hz * 8 / 7;
	bw10k = bw_hz / 10000;

	ret = si2165_adjust_pll_भागl(state, 12);
	अगर (ret < 0)
		वापस ret;

	/* bandwidth in 10KHz steps */
	ret = si2165_ग_लिखोreg16(state, REG_T_BANDWIDTH, bw10k);
	अगर (ret < 0)
		वापस ret;
	ret = si2165_set_oversamp(state, dvb_rate);
	अगर (ret < 0)
		वापस ret;

	ret = si2165_ग_लिखो_reg_list(state, dvbt_regs, ARRAY_SIZE(dvbt_regs));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा si2165_reg_value_pair dvbc_regs[] = अणु
	/* standard = DVB-C */
	अणु REG_DVB_STANDARD, 0x05 पूर्ण,

	/* agc2 */
	अणु REG_AGC2_MIN, 0x50 पूर्ण,
	अणु REG_AGC2_KACQ, 0x0e पूर्ण,
	अणु REG_AGC2_KLOC, 0x10 पूर्ण,
	/* agc */
	अणु REG_AGC_UNFREEZE_THR, 0x03 पूर्ण,
	अणु REG_AGC_CRESTF_DBX8, 0x68 पूर्ण,
	/* agc */
	अणु REG_AAF_CRESTF_DBX8, 0x68 पूर्ण,
	अणु REG_ACI_CRESTF_DBX8, 0x50 पूर्ण,

	अणु REG_EQ_AUTO_CONTROL, 0x0d पूर्ण,

	अणु REG_KP_LOCK, 0x05 पूर्ण,
	अणु REG_CENTRAL_TAP, 0x09 पूर्ण,
	REG16(REG_UNKNOWN_350, 0x3e80),

	अणु REG_AUTO_RESET, 0x01 पूर्ण,
	REG16(REG_UNKNOWN_24C, 0x0000),
	REG16(REG_UNKNOWN_27C, 0x0000),
	अणु REG_SWEEP_STEP, 0x03 पूर्ण,
	अणु REG_AGC_IF_TRI, 0x00 पूर्ण,
पूर्ण;

अटल पूर्णांक si2165_set_frontend_dvbc(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा si2165_state *state = fe->demodulator_priv;
	पूर्णांक ret;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	स्थिर u32 dvb_rate = p->symbol_rate;
	u8 u8पंचांगp;

	अगर (!state->has_dvbc)
		वापस -EINVAL;

	अगर (dvb_rate == 0)
		वापस -EINVAL;

	ret = si2165_adjust_pll_भागl(state, 14);
	अगर (ret < 0)
		वापस ret;

	/* Oversampling */
	ret = si2165_set_oversamp(state, dvb_rate);
	अगर (ret < 0)
		वापस ret;

	चयन (p->modulation) अणु
	हाल QPSK:
		u8पंचांगp = 0x3;
		अवरोध;
	हाल QAM_16:
		u8पंचांगp = 0x7;
		अवरोध;
	हाल QAM_32:
		u8पंचांगp = 0x8;
		अवरोध;
	हाल QAM_64:
		u8पंचांगp = 0x9;
		अवरोध;
	हाल QAM_128:
		u8पंचांगp = 0xa;
		अवरोध;
	हाल QAM_256:
	शेष:
		u8पंचांगp = 0xb;
		अवरोध;
	पूर्ण
	ret = si2165_ग_लिखोreg8(state, REG_REQ_CONSTELLATION, u8पंचांगp);
	अगर (ret < 0)
		वापस ret;

	ret = si2165_ग_लिखोreg32(state, REG_LOCK_TIMEOUT, 0x007a1200);
	अगर (ret < 0)
		वापस ret;

	ret = si2165_ग_लिखो_reg_list(state, dvbc_regs, ARRAY_SIZE(dvbc_regs));
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा si2165_reg_value_pair adc_reग_लिखो[] = अणु
	अणु REG_ADC_RI1, 0x46 पूर्ण,
	अणु REG_ADC_RI3, 0x00 पूर्ण,
	अणु REG_ADC_RI5, 0x0a पूर्ण,
	अणु REG_ADC_RI6, 0xff पूर्ण,
	अणु REG_ADC_RI8, 0x70 पूर्ण
पूर्ण;

अटल पूर्णांक si2165_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा si2165_state *state = fe->demodulator_priv;
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	u32 delsys = p->delivery_प्रणाली;
	पूर्णांक ret;
	u8 val[3];

	/* initial setting of अगर freq shअगरt */
	ret = si2165_set_अगर_freq_shअगरt(state);
	अगर (ret < 0)
		वापस ret;

	चयन (delsys) अणु
	हाल SYS_DVBT:
		ret = si2165_set_frontend_dvbt(fe);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		ret = si2165_set_frontend_dvbc(fe);
		अगर (ret < 0)
			वापस ret;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* dsp_addr_jump */
	ret = si2165_ग_लिखोreg32(state, REG_ADDR_JUMP, 0xf4000000);
	अगर (ret < 0)
		वापस ret;

	अगर (fe->ops.tuner_ops.set_params)
		fe->ops.tuner_ops.set_params(fe);

	/* recalc अगर_freq_shअगरt अगर IF might has changed */
	ret = si2165_set_अगर_freq_shअगरt(state);
	अगर (ret < 0)
		वापस ret;

	/* boot/wकरोg status */
	ret = si2165_पढ़ोreg8(state, REG_WDOG_AND_BOOT, val);
	अगर (ret < 0)
		वापस ret;
	ret = si2165_ग_लिखोreg8(state, REG_WDOG_AND_BOOT, 0x00);
	अगर (ret < 0)
		वापस ret;

	/* reset all */
	ret = si2165_ग_लिखोreg8(state, REG_RST_ALL, 0x00);
	अगर (ret < 0)
		वापस ret;
	/* gp_reg0 */
	ret = si2165_ग_लिखोreg32(state, REG_GP_REG0_LSB, 0x00000000);
	अगर (ret < 0)
		वापस ret;

	/* ग_लिखो adc values after each reset*/
	ret = si2165_ग_लिखो_reg_list(state, adc_reग_लिखो,
				    ARRAY_SIZE(adc_reग_लिखो));
	अगर (ret < 0)
		वापस ret;

	/* start_synchro */
	ret = si2165_ग_लिखोreg8(state, REG_START_SYNCHRO, 0x01);
	अगर (ret < 0)
		वापस ret;
	/* boot/wकरोg status */
	ret = si2165_पढ़ोreg8(state, REG_WDOG_AND_BOOT, val);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops si2165_ops = अणु
	.info = अणु
		.name = "Silicon Labs ",
		 /* For DVB-C */
		.symbol_rate_min = 1000000,
		.symbol_rate_max = 7200000,
		/* For DVB-T */
		.frequency_stepsize_hz = 166667,
		.caps = FE_CAN_FEC_1_2 |
			FE_CAN_FEC_2_3 |
			FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 |
			FE_CAN_FEC_7_8 |
			FE_CAN_FEC_AUTO |
			FE_CAN_QPSK |
			FE_CAN_QAM_16 |
			FE_CAN_QAM_32 |
			FE_CAN_QAM_64 |
			FE_CAN_QAM_128 |
			FE_CAN_QAM_256 |
			FE_CAN_GUARD_INTERVAL_AUTO |
			FE_CAN_HIERARCHY_AUTO |
			FE_CAN_MUTE_TS |
			FE_CAN_TRANSMISSION_MODE_AUTO |
			FE_CAN_RECOVER
	पूर्ण,

	.get_tune_settings = si2165_get_tune_settings,

	.init = si2165_init,
	.sleep = si2165_sleep,

	.set_frontend      = si2165_set_frontend,
	.पढ़ो_status       = si2165_पढ़ो_status,
	.पढ़ो_snr          = si2165_पढ़ो_snr,
	.पढ़ो_ber          = si2165_पढ़ो_ber,
पूर्ण;

अटल पूर्णांक si2165_probe(काष्ठा i2c_client *client,
			स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा si2165_state *state = शून्य;
	काष्ठा si2165_platक्रमm_data *pdata = client->dev.platक्रमm_data;
	पूर्णांक n;
	पूर्णांक ret = 0;
	u8 val;
	अक्षर rev_अक्षर;
	स्थिर अक्षर *chip_name;
	अटल स्थिर काष्ठा regmap_config regmap_config = अणु
		.reg_bits = 16,
		.val_bits = 8,
		.max_रेजिस्टर = 0x08ff,
	पूर्ण;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	/* create regmap */
	state->regmap = devm_regmap_init_i2c(client, &regmap_config);
	अगर (IS_ERR(state->regmap)) अणु
		ret = PTR_ERR(state->regmap);
		जाओ error;
	पूर्ण

	/* setup the state */
	state->client = client;
	state->config.i2c_addr = client->addr;
	state->config.chip_mode = pdata->chip_mode;
	state->config.ref_freq_hz = pdata->ref_freq_hz;
	state->config.inversion = pdata->inversion;

	अगर (state->config.ref_freq_hz < 4000000 ||
	    state->config.ref_freq_hz > 27000000) अणु
		dev_err(&state->client->dev, "ref_freq of %d Hz not supported by this driver\n",
			state->config.ref_freq_hz);
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->fe.ops, &si2165_ops,
	       माप(काष्ठा dvb_frontend_ops));
	state->fe.ops.release = शून्य;
	state->fe.demodulator_priv = state;
	i2c_set_clientdata(client, state);

	/* घातerup */
	ret = si2165_ग_लिखोreg8(state, REG_CHIP_MODE, state->config.chip_mode);
	अगर (ret < 0)
		जाओ nodev_error;

	ret = si2165_पढ़ोreg8(state, REG_CHIP_MODE, &val);
	अगर (ret < 0)
		जाओ nodev_error;
	अगर (val != state->config.chip_mode)
		जाओ nodev_error;

	ret = si2165_पढ़ोreg8(state, REG_CHIP_REVCODE, &state->chip_revcode);
	अगर (ret < 0)
		जाओ nodev_error;

	ret = si2165_पढ़ोreg8(state, REV_CHIP_TYPE, &state->chip_type);
	अगर (ret < 0)
		जाओ nodev_error;

	/* घातerकरोwn */
	ret = si2165_ग_लिखोreg8(state, REG_CHIP_MODE, SI2165_MODE_OFF);
	अगर (ret < 0)
		जाओ nodev_error;

	अगर (state->chip_revcode < 26)
		rev_अक्षर = 'A' + state->chip_revcode;
	अन्यथा
		rev_अक्षर = '?';

	चयन (state->chip_type) अणु
	हाल 0x06:
		chip_name = "Si2161";
		state->has_dvbt = true;
		अवरोध;
	हाल 0x07:
		chip_name = "Si2165";
		state->has_dvbt = true;
		state->has_dvbc = true;
		अवरोध;
	शेष:
		dev_err(&state->client->dev, "Unsupported Silicon Labs chip (type %d, rev %d)\n",
			state->chip_type, state->chip_revcode);
		जाओ nodev_error;
	पूर्ण

	dev_info(&state->client->dev,
		 "Detected Silicon Labs %s-%c (type %d, rev %d)\n",
		chip_name, rev_अक्षर, state->chip_type,
		state->chip_revcode);

	strlcat(state->fe.ops.info.name, chip_name,
		माप(state->fe.ops.info.name));

	n = 0;
	अगर (state->has_dvbt) अणु
		state->fe.ops.delsys[n++] = SYS_DVBT;
		strlcat(state->fe.ops.info.name, " DVB-T",
			माप(state->fe.ops.info.name));
	पूर्ण
	अगर (state->has_dvbc) अणु
		state->fe.ops.delsys[n++] = SYS_DVBC_ANNEX_A;
		strlcat(state->fe.ops.info.name, " DVB-C",
			माप(state->fe.ops.info.name));
	पूर्ण

	/* वापस fe poपूर्णांकer */
	*pdata->fe = &state->fe;

	वापस 0;

nodev_error:
	ret = -ENODEV;
error:
	kमुक्त(state);
	dev_dbg(&client->dev, "failed=%d\n", ret);
	वापस ret;
पूर्ण

अटल पूर्णांक si2165_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा si2165_state *state = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

	kमुक्त(state);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा i2c_device_id si2165_id_table[] = अणु
	अणु"si2165", 0पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, si2165_id_table);

अटल काष्ठा i2c_driver si2165_driver = अणु
	.driver = अणु
		.name	= "si2165",
	पूर्ण,
	.probe		= si2165_probe,
	.हटाओ		= si2165_हटाओ,
	.id_table	= si2165_id_table,
पूर्ण;

module_i2c_driver(si2165_driver);

MODULE_DESCRIPTION("Silicon Labs Si2165 DVB-C/-T Demodulator driver");
MODULE_AUTHOR("Matthias Schwarzott <zzam@gentoo.org>");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(SI2165_FIRMWARE_REV_D);
