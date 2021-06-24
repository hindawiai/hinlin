<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *    Support क्रम NXT2002 and NXT2004 - VSB/QAM
 *
 *    Copyright (C) 2005 Kirk Lapray <kirk.lapray@gmail.com>
 *    Copyright (C) 2006-2014 Michael Krufky <mkrufky@linuxtv.org>
 *    based on nxt2002 by Taylor Jacob <rtjacob@earthlink.net>
 *    and nxt2004 by Jean-Francois Thibert <jeanfrancois@sagetv.com>
*/

/*
 *                      NOTES ABOUT THIS DRIVER
 *
 * This Linux driver supports:
 *   B2C2/BBTI Technisat Air2PC - ATSC (NXT2002)
 *   AverTVHD MCE A180 (NXT2004)
 *   ATI HDTV Wonder (NXT2004)
 *
 * This driver needs बाह्यal firmware. Please use the command
 * "<kerneldir>/scripts/get_dvb_firmware nxt2002" or
 * "<kerneldir>/scripts/get_dvb_firmware nxt2004" to
 * करोwnload/extract the appropriate firmware, and then copy it to
 * /usr/lib/hotplug/firmware/ or /lib/firmware/
 * (depending on configuration of firmware hotplug).
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MAX_XFER_SIZE  256

#घोषणा NXT2002_DEFAULT_FIRMWARE "dvb-fe-nxt2002.fw"
#घोषणा NXT2004_DEFAULT_FIRMWARE "dvb-fe-nxt2004.fw"
#घोषणा CRC_CCIT_MASK 0x1021

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>

#समावेश <media/dvb_frontend.h>
#समावेश "nxt200x.h"

काष्ठा nxt200x_state अणु

	काष्ठा i2c_adapter* i2c;
	स्थिर काष्ठा nxt200x_config* config;
	काष्ठा dvb_frontend frontend;

	/* demodulator निजी data */
	nxt_chip_type demod_chip;
	u8 initialised:1;
पूर्ण;

अटल पूर्णांक debug;
#घोषणा dprपूर्णांकk(args...)	करो अणु अगर (debug) pr_debug(args); पूर्ण जबतक (0)

अटल पूर्णांक i2c_ग_लिखोbytes (काष्ठा nxt200x_state* state, u8 addr, u8 *buf, u8 len)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg = अणु .addr = addr, .flags = 0, .buf = buf, .len = len पूर्ण;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		pr_warn("%s: i2c write error (addr 0x%02x, err == %i)\n",
			__func__, addr, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_पढ़ोbytes(काष्ठा nxt200x_state *state, u8 addr, u8 *buf, u8 len)
अणु
	पूर्णांक err;
	काष्ठा i2c_msg msg = अणु .addr = addr, .flags = I2C_M_RD, .buf = buf, .len = len पूर्ण;

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		pr_warn("%s: i2c read error (addr 0x%02x, err == %i)\n",
			__func__, addr, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_ग_लिखोbytes (काष्ठा nxt200x_state* state, u8 reg,
			       स्थिर u8 *buf, u8 len)
अणु
	u8 buf2[MAX_XFER_SIZE];
	पूर्णांक err;
	काष्ठा i2c_msg msg = अणु .addr = state->config->demod_address, .flags = 0, .buf = buf2, .len = len + 1 पूर्ण;

	अगर (1 + len > माप(buf2)) अणु
		pr_warn("%s: i2c wr reg=%04x: len=%d is too big!\n",
			 __func__, reg, len);
		वापस -EINVAL;
	पूर्ण

	buf2[0] = reg;
	स_नकल(&buf2[1], buf, len);

	अगर ((err = i2c_transfer (state->i2c, &msg, 1)) != 1) अणु
		pr_warn("%s: i2c write error (addr 0x%02x, err == %i)\n",
			__func__, state->config->demod_address, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ोbytes(काष्ठा nxt200x_state *state, u8 reg, u8 *buf, u8 len)
अणु
	u8 reg2 [] = अणु reg पूर्ण;

	काष्ठा i2c_msg msg [] = अणु अणु .addr = state->config->demod_address, .flags = 0, .buf = reg2, .len = 1 पूर्ण,
			अणु .addr = state->config->demod_address, .flags = I2C_M_RD, .buf = buf, .len = len पूर्ण पूर्ण;

	पूर्णांक err;

	अगर ((err = i2c_transfer (state->i2c, msg, 2)) != 2) अणु
		pr_warn("%s: i2c read error (addr 0x%02x, err == %i)\n",
			__func__, state->config->demod_address, err);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल u16 nxt200x_crc(u16 crc, u8 c)
अणु
	u8 i;
	u16 input = (u16) c & 0xFF;

	input<<=8;
	क्रम(i=0; i<8; i++) अणु
		अगर((crc^input) & 0x8000)
			crc=(crc<<1)^CRC_CCIT_MASK;
		अन्यथा
			crc<<=1;
		input<<=1;
	पूर्ण
	वापस crc;
पूर्ण

अटल पूर्णांक nxt200x_ग_लिखोreg_multibyte (काष्ठा nxt200x_state* state, u8 reg, u8* data, u8 len)
अणु
	u8 attr, len2, buf;
	dprपूर्णांकk("%s\n", __func__);

	/* set multi रेजिस्टर रेजिस्टर */
	nxt200x_ग_लिखोbytes(state, 0x35, &reg, 1);

	/* send the actual data */
	nxt200x_ग_लिखोbytes(state, 0x36, data, len);

	चयन (state->demod_chip) अणु
		हाल NXT2002:
			len2 = len;
			buf = 0x02;
			अवरोध;
		हाल NXT2004:
			/* probably not right, but gives correct values */
			attr = 0x02;
			अगर (reg & 0x80) अणु
				attr = attr << 1;
				अगर (reg & 0x04)
					attr = attr >> 1;
			पूर्ण
			/* set ग_लिखो bit */
			len2 = ((attr << 4) | 0x10) | len;
			buf = 0x80;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	/* set multi रेजिस्टर length */
	nxt200x_ग_लिखोbytes(state, 0x34, &len2, 1);

	/* toggle the multireg ग_लिखो bit */
	nxt200x_ग_लिखोbytes(state, 0x21, &buf, 1);

	nxt200x_पढ़ोbytes(state, 0x21, &buf, 1);

	चयन (state->demod_chip) अणु
		हाल NXT2002:
			अगर ((buf & 0x02) == 0)
				वापस 0;
			अवरोध;
		हाल NXT2004:
			अगर (buf == 0)
				वापस 0;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	pr_warn("Error writing multireg register 0x%02X\n", reg);

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ोreg_multibyte (काष्ठा nxt200x_state* state, u8 reg, u8* data, u8 len)
अणु
	पूर्णांक i;
	u8 buf, len2, attr;
	dprपूर्णांकk("%s\n", __func__);

	/* set multi रेजिस्टर रेजिस्टर */
	nxt200x_ग_लिखोbytes(state, 0x35, &reg, 1);

	चयन (state->demod_chip) अणु
		हाल NXT2002:
			/* set multi रेजिस्टर length */
			len2 = len & 0x80;
			nxt200x_ग_लिखोbytes(state, 0x34, &len2, 1);

			/* पढ़ो the actual data */
			nxt200x_पढ़ोbytes(state, reg, data, len);
			वापस 0;
		हाल NXT2004:
			/* probably not right, but gives correct values */
			attr = 0x02;
			अगर (reg & 0x80) अणु
				attr = attr << 1;
				अगर (reg & 0x04)
					attr = attr >> 1;
			पूर्ण

			/* set multi रेजिस्टर length */
			len2 = (attr << 4) | len;
			nxt200x_ग_लिखोbytes(state, 0x34, &len2, 1);

			/* toggle the multireg bit*/
			buf = 0x80;
			nxt200x_ग_लिखोbytes(state, 0x21, &buf, 1);

			/* पढ़ो the actual data */
			क्रम(i = 0; i < len; i++) अणु
				nxt200x_पढ़ोbytes(state, 0x36 + i, &data[i], 1);
			पूर्ण
			वापस 0;
		शेष:
			वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम nxt200x_microcontroller_stop (काष्ठा nxt200x_state* state)
अणु
	u8 buf, stopval, counter = 0;
	dprपूर्णांकk("%s\n", __func__);

	/* set correct stop value */
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			stopval = 0x40;
			अवरोध;
		हाल NXT2004:
			stopval = 0x10;
			अवरोध;
		शेष:
			stopval = 0;
			अवरोध;
	पूर्ण

	buf = 0x80;
	nxt200x_ग_लिखोbytes(state, 0x22, &buf, 1);

	जबतक (counter < 20) अणु
		nxt200x_पढ़ोbytes(state, 0x31, &buf, 1);
		अगर (buf & stopval)
			वापस;
		msleep(10);
		counter++;
	पूर्ण

	pr_warn("Timeout waiting for nxt200x to stop. This is ok after firmware upload.\n");
	वापस;
पूर्ण

अटल व्योम nxt200x_microcontroller_start (काष्ठा nxt200x_state* state)
अणु
	u8 buf;
	dprपूर्णांकk("%s\n", __func__);

	buf = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x22, &buf, 1);
पूर्ण

अटल व्योम nxt2004_microcontroller_init (काष्ठा nxt200x_state* state)
अणु
	u8 buf[9];
	u8 counter = 0;
	dprपूर्णांकk("%s\n", __func__);

	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x2b, buf, 1);
	buf[0] = 0x70;
	nxt200x_ग_लिखोbytes(state, 0x34, buf, 1);
	buf[0] = 0x04;
	nxt200x_ग_लिखोbytes(state, 0x35, buf, 1);
	buf[0] = 0x01; buf[1] = 0x23; buf[2] = 0x45; buf[3] = 0x67; buf[4] = 0x89;
	buf[5] = 0xAB; buf[6] = 0xCD; buf[7] = 0xEF; buf[8] = 0xC0;
	nxt200x_ग_लिखोbytes(state, 0x36, buf, 9);
	buf[0] = 0x80;
	nxt200x_ग_लिखोbytes(state, 0x21, buf, 1);

	जबतक (counter < 20) अणु
		nxt200x_पढ़ोbytes(state, 0x21, buf, 1);
		अगर (buf[0] == 0)
			वापस;
		msleep(10);
		counter++;
	पूर्ण

	pr_warn("Timeout waiting for nxt2004 to init.\n");

	वापस;
पूर्ण

अटल पूर्णांक nxt200x_ग_लिखोtuner (काष्ठा nxt200x_state* state, u8* data)
अणु
	u8 buf, count = 0;

	dprपूर्णांकk("%s\n", __func__);

	dprपूर्णांकk("Tuner Bytes: %*ph\n", 4, data + 1);

	/* अगर NXT2004, ग_लिखो directly to tuner. अगर NXT2002, ग_लिखो through NXT chip.
	 * direct ग_लिखो is required क्रम Philips TUV1236D and ALPS TDHU2 */
	चयन (state->demod_chip) अणु
		हाल NXT2004:
			अगर (i2c_ग_लिखोbytes(state, data[0], data+1, 4))
				pr_warn("error writing to tuner\n");
			/* रुको until we have a lock */
			जबतक (count < 20) अणु
				i2c_पढ़ोbytes(state, data[0], &buf, 1);
				अगर (buf & 0x40)
					वापस 0;
				msleep(100);
				count++;
			पूर्ण
			pr_warn("timeout waiting for tuner lock\n");
			अवरोध;
		हाल NXT2002:
			/* set the i2c transfer speed to the tuner */
			buf = 0x03;
			nxt200x_ग_लिखोbytes(state, 0x20, &buf, 1);

			/* setup to transfer 4 bytes via i2c */
			buf = 0x04;
			nxt200x_ग_लिखोbytes(state, 0x34, &buf, 1);

			/* ग_लिखो actual tuner bytes */
			nxt200x_ग_लिखोbytes(state, 0x36, data+1, 4);

			/* set tuner i2c address */
			buf = data[0] << 1;
			nxt200x_ग_लिखोbytes(state, 0x35, &buf, 1);

			/* ग_लिखो UC Opmode to begin transfer */
			buf = 0x80;
			nxt200x_ग_लिखोbytes(state, 0x21, &buf, 1);

			जबतक (count < 20) अणु
				nxt200x_पढ़ोbytes(state, 0x21, &buf, 1);
				अगर ((buf & 0x80)== 0x00)
					वापस 0;
				msleep(100);
				count++;
			पूर्ण
			pr_warn("timeout error writing to tuner\n");
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम nxt200x_agc_reset(काष्ठा nxt200x_state* state)
अणु
	u8 buf;
	dprपूर्णांकk("%s\n", __func__);

	चयन (state->demod_chip) अणु
		हाल NXT2002:
			buf = 0x08;
			nxt200x_ग_लिखोbytes(state, 0x08, &buf, 1);
			buf = 0x00;
			nxt200x_ग_लिखोbytes(state, 0x08, &buf, 1);
			अवरोध;
		हाल NXT2004:
			nxt200x_पढ़ोreg_multibyte(state, 0x08, &buf, 1);
			buf = 0x08;
			nxt200x_ग_लिखोreg_multibyte(state, 0x08, &buf, 1);
			buf = 0x00;
			nxt200x_ग_लिखोreg_multibyte(state, 0x08, &buf, 1);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण
	वापस;
पूर्ण

अटल पूर्णांक nxt2002_load_firmware (काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware *fw)
अणु

	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 buf[3], written = 0, chunkpos = 0;
	u16 rambase, position, crc = 0;

	dprपूर्णांकk("%s\n", __func__);
	dprपूर्णांकk("Firmware is %zu bytes\n", fw->size);

	/* Get the RAM base क्रम this nxt2002 */
	nxt200x_पढ़ोbytes(state, 0x10, buf, 1);

	अगर (buf[0] & 0x10)
		rambase = 0x1000;
	अन्यथा
		rambase = 0x0000;

	dprपूर्णांकk("rambase on this nxt2002 is %04X\n", rambase);

	/* Hold the micro in reset जबतक loading firmware */
	buf[0] = 0x80;
	nxt200x_ग_लिखोbytes(state, 0x2B, buf, 1);

	क्रम (position = 0; position < fw->size; position++) अणु
		अगर (written == 0) अणु
			crc = 0;
			chunkpos = 0x28;
			buf[0] = ((rambase + position) >> 8);
			buf[1] = (rambase + position) & 0xFF;
			buf[2] = 0x81;
			/* ग_लिखो starting address */
			nxt200x_ग_लिखोbytes(state, 0x29, buf, 3);
		पूर्ण
		written++;
		chunkpos++;

		अगर ((written % 4) == 0)
			nxt200x_ग_लिखोbytes(state, chunkpos, &fw->data[position-3], 4);

		crc = nxt200x_crc(crc, fw->data[position]);

		अगर ((written == 255) || (position+1 == fw->size)) अणु
			/* ग_लिखो reमुख्यing bytes of firmware */
			nxt200x_ग_लिखोbytes(state, chunkpos+4-(written %4),
				&fw->data[position-(written %4) + 1],
				written %4);
			buf[0] = crc << 8;
			buf[1] = crc & 0xFF;

			/* ग_लिखो crc */
			nxt200x_ग_लिखोbytes(state, 0x2C, buf, 2);

			/* करो a पढ़ो to stop things */
			nxt200x_पढ़ोbytes(state, 0x2A, buf, 1);

			/* set transfer mode to complete */
			buf[0] = 0x80;
			nxt200x_ग_लिखोbytes(state, 0x2B, buf, 1);

			written = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण;

अटल पूर्णांक nxt2004_load_firmware (काष्ठा dvb_frontend* fe, स्थिर काष्ठा firmware *fw)
अणु

	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 buf[3];
	u16 rambase, position, crc=0;

	dprपूर्णांकk("%s\n", __func__);
	dprपूर्णांकk("Firmware is %zu bytes\n", fw->size);

	/* set rambase */
	rambase = 0x1000;

	/* hold the micro in reset जबतक loading firmware */
	buf[0] = 0x80;
	nxt200x_ग_लिखोbytes(state, 0x2B, buf,1);

	/* calculate firmware CRC */
	क्रम (position = 0; position < fw->size; position++) अणु
		crc = nxt200x_crc(crc, fw->data[position]);
	पूर्ण

	buf[0] = rambase >> 8;
	buf[1] = rambase & 0xFF;
	buf[2] = 0x81;
	/* ग_लिखो starting address */
	nxt200x_ग_लिखोbytes(state,0x29,buf,3);

	क्रम (position = 0; position < fw->size;) अणु
		nxt200x_ग_लिखोbytes(state, 0x2C, &fw->data[position],
			fw->size-position > 255 ? 255 : fw->size-position);
		position += (fw->size-position > 255 ? 255 : fw->size-position);
	पूर्ण
	buf[0] = crc >> 8;
	buf[1] = crc & 0xFF;

	dprपूर्णांकk("firmware crc is 0x%02X 0x%02X\n", buf[0], buf[1]);

	/* ग_लिखो crc */
	nxt200x_ग_लिखोbytes(state, 0x2C, buf,2);

	/* करो a पढ़ो to stop things */
	nxt200x_पढ़ोbytes(state, 0x2C, buf, 1);

	/* set transfer mode to complete */
	buf[0] = 0x80;
	nxt200x_ग_लिखोbytes(state, 0x2B, buf,1);

	वापस 0;
पूर्ण;

अटल पूर्णांक nxt200x_setup_frontend_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *p = &fe->dtv_property_cache;
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 buf[5];

	/* stop the micro first */
	nxt200x_microcontroller_stop(state);

	अगर (state->demod_chip == NXT2004) अणु
		/* make sure demod is set to digital */
		buf[0] = 0x04;
		nxt200x_ग_लिखोbytes(state, 0x14, buf, 1);
		buf[0] = 0x00;
		nxt200x_ग_लिखोbytes(state, 0x17, buf, 1);
	पूर्ण

	/* set additional params */
	चयन (p->modulation) अणु
		हाल QAM_64:
		हाल QAM_256:
			/* Set punctured घड़ी क्रम QAM */
			/* This is just a guess since I am unable to test it */
			अगर (state->config->set_ts_params)
				state->config->set_ts_params(fe, 1);
			अवरोध;
		हाल VSB_8:
			/* Set non-punctured घड़ी क्रम VSB */
			अगर (state->config->set_ts_params)
				state->config->set_ts_params(fe, 0);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	अगर (fe->ops.tuner_ops.calc_regs) अणु
		/* get tuning inक्रमmation */
		fe->ops.tuner_ops.calc_regs(fe, buf, 5);

		/* ग_लिखो frequency inक्रमmation */
		nxt200x_ग_लिखोtuner(state, buf);
	पूर्ण

	/* reset the agc now that tuning has been completed */
	nxt200x_agc_reset(state);

	/* set target घातer level */
	चयन (p->modulation) अणु
		हाल QAM_64:
		हाल QAM_256:
			buf[0] = 0x74;
			अवरोध;
		हाल VSB_8:
			buf[0] = 0x70;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	nxt200x_ग_लिखोbytes(state, 0x42, buf, 1);

	/* configure sdm */
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			buf[0] = 0x87;
			अवरोध;
		हाल NXT2004:
			buf[0] = 0x07;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण
	nxt200x_ग_लिखोbytes(state, 0x57, buf, 1);

	/* ग_लिखो sdm1 input */
	buf[0] = 0x10;
	buf[1] = 0x00;
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			nxt200x_ग_लिखोreg_multibyte(state, 0x58, buf, 2);
			अवरोध;
		हाल NXT2004:
			nxt200x_ग_लिखोbytes(state, 0x58, buf, 2);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	/* ग_लिखो sdmx input */
	चयन (p->modulation) अणु
		हाल QAM_64:
				buf[0] = 0x68;
				अवरोध;
		हाल QAM_256:
				buf[0] = 0x64;
				अवरोध;
		हाल VSB_8:
				buf[0] = 0x60;
				अवरोध;
		शेष:
				वापस -EINVAL;
	पूर्ण
	buf[1] = 0x00;
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			nxt200x_ग_लिखोreg_multibyte(state, 0x5C, buf, 2);
			अवरोध;
		हाल NXT2004:
			nxt200x_ग_लिखोbytes(state, 0x5C, buf, 2);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	/* ग_लिखो adc घातer lpf fc */
	buf[0] = 0x05;
	nxt200x_ग_लिखोbytes(state, 0x43, buf, 1);

	अगर (state->demod_chip == NXT2004) अणु
		/* ग_लिखो ??? */
		buf[0] = 0x00;
		buf[1] = 0x00;
		nxt200x_ग_लिखोbytes(state, 0x46, buf, 2);
	पूर्ण

	/* ग_लिखो accumulator2 input */
	buf[0] = 0x80;
	buf[1] = 0x00;
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			nxt200x_ग_लिखोreg_multibyte(state, 0x4B, buf, 2);
			अवरोध;
		हाल NXT2004:
			nxt200x_ग_लिखोbytes(state, 0x4B, buf, 2);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	/* ग_लिखो kg1 */
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x4D, buf, 1);

	/* ग_लिखो sdm12 lpf fc */
	buf[0] = 0x44;
	nxt200x_ग_लिखोbytes(state, 0x55, buf, 1);

	/* ग_लिखो agc control reg */
	buf[0] = 0x04;
	nxt200x_ग_लिखोbytes(state, 0x41, buf, 1);

	अगर (state->demod_chip == NXT2004) अणु
		nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x24;
		nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);

		/* soft reset? */
		nxt200x_पढ़ोreg_multibyte(state, 0x08, buf, 1);
		buf[0] = 0x10;
		nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);
		nxt200x_पढ़ोreg_multibyte(state, 0x08, buf, 1);
		buf[0] = 0x00;
		nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);

		nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x04;
		nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x00;
		nxt200x_ग_लिखोreg_multibyte(state, 0x81, buf, 1);
		buf[0] = 0x80; buf[1] = 0x00; buf[2] = 0x00;
		nxt200x_ग_लिखोreg_multibyte(state, 0x82, buf, 3);
		nxt200x_पढ़ोreg_multibyte(state, 0x88, buf, 1);
		buf[0] = 0x11;
		nxt200x_ग_लिखोreg_multibyte(state, 0x88, buf, 1);
		nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
		buf[0] = 0x44;
		nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);
	पूर्ण

	/* ग_लिखो agc ucgp0 */
	चयन (p->modulation) अणु
		हाल QAM_64:
				buf[0] = 0x02;
				अवरोध;
		हाल QAM_256:
				buf[0] = 0x03;
				अवरोध;
		हाल VSB_8:
				buf[0] = 0x00;
				अवरोध;
		शेष:
				वापस -EINVAL;
	पूर्ण
	nxt200x_ग_लिखोbytes(state, 0x30, buf, 1);

	/* ग_लिखो agc control reg */
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x41, buf, 1);

	/* ग_लिखो accumulator2 input */
	buf[0] = 0x80;
	buf[1] = 0x00;
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			nxt200x_ग_लिखोreg_multibyte(state, 0x49, buf, 2);
			nxt200x_ग_लिखोreg_multibyte(state, 0x4B, buf, 2);
			अवरोध;
		हाल NXT2004:
			nxt200x_ग_लिखोbytes(state, 0x49, buf, 2);
			nxt200x_ग_लिखोbytes(state, 0x4B, buf, 2);
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	/* ग_लिखो agc control reg */
	buf[0] = 0x04;
	nxt200x_ग_लिखोbytes(state, 0x41, buf, 1);

	nxt200x_microcontroller_start(state);

	अगर (state->demod_chip == NXT2004) अणु
		nxt2004_microcontroller_init(state);

		/* ???? */
		buf[0] = 0xF0;
		buf[1] = 0x00;
		nxt200x_ग_लिखोbytes(state, 0x5C, buf, 2);
	पूर्ण

	/* adjacent channel detection should be करोne here, but I करोn't
	have any stations with this need so I cannot test it */

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ो_status(काष्ठा dvb_frontend *fe, क्रमागत fe_status *status)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 lock;
	nxt200x_पढ़ोbytes(state, 0x31, &lock, 1);

	*status = 0;
	अगर (lock & 0x20) अणु
		*status |= FE_HAS_SIGNAL;
		*status |= FE_HAS_CARRIER;
		*status |= FE_HAS_VITERBI;
		*status |= FE_HAS_SYNC;
		*status |= FE_HAS_LOCK;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ो_ber(काष्ठा dvb_frontend* fe, u32* ber)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 b[3];

	nxt200x_पढ़ोreg_multibyte(state, 0xE6, b, 3);

	*ber = ((b[0] << 8) + b[1]) * 8;

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ो_संकेत_strength(काष्ठा dvb_frontend* fe, u16* strength)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 b[2];
	u16 temp = 0;

	/* setup to पढ़ो cluster variance */
	b[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xA1, b, 1);

	/* get multreg val */
	nxt200x_पढ़ोreg_multibyte(state, 0xA6, b, 2);

	temp = (b[0] << 8) | b[1];
	*strength = ((0x7FFF - temp) & 0x0FFF) * 16;

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ो_snr(काष्ठा dvb_frontend* fe, u16* snr)
अणु

	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 b[2];
	u16 temp = 0, temp2;
	u32 snrdb = 0;

	/* setup to पढ़ो cluster variance */
	b[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xA1, b, 1);

	/* get multreg val from 0xA6 */
	nxt200x_पढ़ोreg_multibyte(state, 0xA6, b, 2);

	temp = (b[0] << 8) | b[1];
	temp2 = 0x7FFF - temp;

	/* snr will be in db */
	अगर (temp2 > 0x7F00)
		snrdb = 1000*24 + ( 1000*(30-24) * ( temp2 - 0x7F00 ) / ( 0x7FFF - 0x7F00 ) );
	अन्यथा अगर (temp2 > 0x7EC0)
		snrdb = 1000*18 + ( 1000*(24-18) * ( temp2 - 0x7EC0 ) / ( 0x7F00 - 0x7EC0 ) );
	अन्यथा अगर (temp2 > 0x7C00)
		snrdb = 1000*12 + ( 1000*(18-12) * ( temp2 - 0x7C00 ) / ( 0x7EC0 - 0x7C00 ) );
	अन्यथा
		snrdb = 1000*0 + ( 1000*(12-0) * ( temp2 - 0 ) / ( 0x7C00 - 0 ) );

	/* the value reported back from the frontend will be FFFF=32db 0000=0db */
	*snr = snrdb * (0xFFFF/32000);

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_पढ़ो_ucblocks(काष्ठा dvb_frontend* fe, u32* ucblocks)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	u8 b[3];

	nxt200x_पढ़ोreg_multibyte(state, 0xE6, b, 3);
	*ucblocks = b[2];

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_sleep(काष्ठा dvb_frontend* fe)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nxt2002_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;
	u8 buf[2];

	/* request the firmware, this will block until someone uploads it */
	pr_debug("%s: Waiting for firmware upload (%s)...\n",
		 __func__, NXT2002_DEFAULT_FIRMWARE);
	ret = request_firmware(&fw, NXT2002_DEFAULT_FIRMWARE,
			       state->i2c->dev.parent);
	pr_debug("%s: Waiting for firmware upload(2)...\n", __func__);
	अगर (ret) अणु
		pr_err("%s: No firmware uploaded (timeout or file not found?)\n",
		       __func__);
		वापस ret;
	पूर्ण

	ret = nxt2002_load_firmware(fe, fw);
	release_firmware(fw);
	अगर (ret) अणु
		pr_err("%s: Writing firmware to device failed\n", __func__);
		वापस ret;
	पूर्ण
	pr_info("%s: Firmware upload complete\n", __func__);

	/* Put the micro पूर्णांकo reset */
	nxt200x_microcontroller_stop(state);

	/* ensure transfer is complete */
	buf[0]=0x00;
	nxt200x_ग_लिखोbytes(state, 0x2B, buf, 1);

	/* Put the micro पूर्णांकo reset क्रम real this समय */
	nxt200x_microcontroller_stop(state);

	/* soft reset everything (agc,frontend,eq,fec)*/
	buf[0] = 0x0F;
	nxt200x_ग_लिखोbytes(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x08, buf, 1);

	/* ग_लिखो agc sdm configure */
	buf[0] = 0xF1;
	nxt200x_ग_लिखोbytes(state, 0x57, buf, 1);

	/* ग_लिखो mod output क्रमmat */
	buf[0] = 0x20;
	nxt200x_ग_लिखोbytes(state, 0x09, buf, 1);

	/* ग_लिखो fec mpeg mode */
	buf[0] = 0x7E;
	buf[1] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xE9, buf, 2);

	/* ग_लिखो mux selection */
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xCC, buf, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक nxt2004_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;
	u8 buf[3];

	/* ??? */
	buf[0]=0x00;
	nxt200x_ग_लिखोbytes(state, 0x1E, buf, 1);

	/* request the firmware, this will block until someone uploads it */
	pr_debug("%s: Waiting for firmware upload (%s)...\n",
		 __func__, NXT2004_DEFAULT_FIRMWARE);
	ret = request_firmware(&fw, NXT2004_DEFAULT_FIRMWARE,
			       state->i2c->dev.parent);
	pr_debug("%s: Waiting for firmware upload(2)...\n", __func__);
	अगर (ret) अणु
		pr_err("%s: No firmware uploaded (timeout or file not found?)\n",
		       __func__);
		वापस ret;
	पूर्ण

	ret = nxt2004_load_firmware(fe, fw);
	release_firmware(fw);
	अगर (ret) अणु
		pr_err("%s: Writing firmware to device failed\n", __func__);
		वापस ret;
	पूर्ण
	pr_info("%s: Firmware upload complete\n", __func__);

	/* ensure transfer is complete */
	buf[0] = 0x01;
	nxt200x_ग_लिखोbytes(state, 0x19, buf, 1);

	nxt2004_microcontroller_init(state);
	nxt200x_microcontroller_stop(state);
	nxt200x_microcontroller_stop(state);
	nxt2004_microcontroller_init(state);
	nxt200x_microcontroller_stop(state);

	/* soft reset everything (agc,frontend,eq,fec)*/
	buf[0] = 0xFF;
	nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);

	/* ग_लिखो agc sdm configure */
	buf[0] = 0xD7;
	nxt200x_ग_लिखोbytes(state, 0x57, buf, 1);

	/* ???*/
	buf[0] = 0x07;
	buf[1] = 0xfe;
	nxt200x_ग_लिखोbytes(state, 0x35, buf, 2);
	buf[0] = 0x12;
	nxt200x_ग_लिखोbytes(state, 0x34, buf, 1);
	buf[0] = 0x80;
	nxt200x_ग_लिखोbytes(state, 0x21, buf, 1);

	/* ???*/
	buf[0] = 0x21;
	nxt200x_ग_लिखोbytes(state, 0x0A, buf, 1);

	/* ???*/
	buf[0] = 0x01;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);

	/* ग_लिखो fec mpeg mode */
	buf[0] = 0x7E;
	buf[1] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xE9, buf, 2);

	/* ग_लिखो mux selection */
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xCC, buf, 1);

	/* ???*/
	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);

	/* soft reset? */
	nxt200x_पढ़ोreg_multibyte(state, 0x08, buf, 1);
	buf[0] = 0x10;
	nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);
	nxt200x_पढ़ोreg_multibyte(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);

	/* ???*/
	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x01;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x70;
	nxt200x_ग_लिखोreg_multibyte(state, 0x81, buf, 1);
	buf[0] = 0x31; buf[1] = 0x5E; buf[2] = 0x66;
	nxt200x_ग_लिखोreg_multibyte(state, 0x82, buf, 3);

	nxt200x_पढ़ोreg_multibyte(state, 0x88, buf, 1);
	buf[0] = 0x11;
	nxt200x_ग_लिखोreg_multibyte(state, 0x88, buf, 1);
	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x40;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);

	nxt200x_पढ़ोbytes(state, 0x10, buf, 1);
	buf[0] = 0x10;
	nxt200x_ग_लिखोbytes(state, 0x10, buf, 1);
	nxt200x_पढ़ोbytes(state, 0x0A, buf, 1);
	buf[0] = 0x21;
	nxt200x_ग_लिखोbytes(state, 0x0A, buf, 1);

	nxt2004_microcontroller_init(state);

	buf[0] = 0x21;
	nxt200x_ग_लिखोbytes(state, 0x0A, buf, 1);
	buf[0] = 0x7E;
	nxt200x_ग_लिखोbytes(state, 0xE9, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0xEA, buf, 1);

	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);
	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);

	/* soft reset? */
	nxt200x_पढ़ोreg_multibyte(state, 0x08, buf, 1);
	buf[0] = 0x10;
	nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);
	nxt200x_पढ़ोreg_multibyte(state, 0x08, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x08, buf, 1);

	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x04;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x81, buf, 1);
	buf[0] = 0x80; buf[1] = 0x00; buf[2] = 0x00;
	nxt200x_ग_लिखोreg_multibyte(state, 0x82, buf, 3);

	nxt200x_पढ़ोreg_multibyte(state, 0x88, buf, 1);
	buf[0] = 0x11;
	nxt200x_ग_लिखोreg_multibyte(state, 0x88, buf, 1);

	nxt200x_पढ़ोreg_multibyte(state, 0x80, buf, 1);
	buf[0] = 0x44;
	nxt200x_ग_लिखोreg_multibyte(state, 0x80, buf, 1);

	/* initialize tuner */
	nxt200x_पढ़ोbytes(state, 0x10, buf, 1);
	buf[0] = 0x12;
	nxt200x_ग_लिखोbytes(state, 0x10, buf, 1);
	buf[0] = 0x04;
	nxt200x_ग_लिखोbytes(state, 0x13, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x16, buf, 1);
	buf[0] = 0x04;
	nxt200x_ग_लिखोbytes(state, 0x14, buf, 1);
	buf[0] = 0x00;
	nxt200x_ग_लिखोbytes(state, 0x14, buf, 1);
	nxt200x_ग_लिखोbytes(state, 0x17, buf, 1);
	nxt200x_ग_लिखोbytes(state, 0x14, buf, 1);
	nxt200x_ग_लिखोbytes(state, 0x17, buf, 1);

	वापस 0;
पूर्ण

अटल पूर्णांक nxt200x_init(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	पूर्णांक ret = 0;

	अगर (!state->initialised) अणु
		चयन (state->demod_chip) अणु
			हाल NXT2002:
				ret = nxt2002_init(fe);
				अवरोध;
			हाल NXT2004:
				ret = nxt2004_init(fe);
				अवरोध;
			शेष:
				वापस -EINVAL;
		पूर्ण
		state->initialised = 1;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक nxt200x_get_tune_settings(काष्ठा dvb_frontend* fe, काष्ठा dvb_frontend_tune_settings* fesettings)
अणु
	fesettings->min_delay_ms = 500;
	fesettings->step_size = 0;
	fesettings->max_drअगरt = 0;
	वापस 0;
पूर्ण

अटल व्योम nxt200x_release(काष्ठा dvb_frontend* fe)
अणु
	काष्ठा nxt200x_state* state = fe->demodulator_priv;
	kमुक्त(state);
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops nxt200x_ops;

काष्ठा dvb_frontend* nxt200x_attach(स्थिर काष्ठा nxt200x_config* config,
				   काष्ठा i2c_adapter* i2c)
अणु
	काष्ठा nxt200x_state* state = शून्य;
	u8 buf [] = अणु0,0,0,0,0पूर्ण;

	/* allocate memory क्रम the पूर्णांकernal state */
	state = kzalloc(माप(काष्ठा nxt200x_state), GFP_KERNEL);
	अगर (state == शून्य)
		जाओ error;

	/* setup the state */
	state->config = config;
	state->i2c = i2c;
	state->initialised = 0;

	/* पढ़ो card id */
	nxt200x_पढ़ोbytes(state, 0x00, buf, 5);
	dprपूर्णांकk("NXT info: %*ph\n", 5, buf);

	/* set demod chip */
	चयन (buf[0]) अणु
		हाल 0x04:
			state->demod_chip = NXT2002;
			pr_info("NXT2002 Detected\n");
			अवरोध;
		हाल 0x05:
			state->demod_chip = NXT2004;
			pr_info("NXT2004 Detected\n");
			अवरोध;
		शेष:
			जाओ error;
	पूर्ण

	/* make sure demod chip is supported */
	चयन (state->demod_chip) अणु
		हाल NXT2002:
			अगर (buf[0] != 0x04) जाओ error;		/* device id */
			अगर (buf[1] != 0x02) जाओ error;		/* fab id */
			अगर (buf[2] != 0x11) जाओ error;		/* month */
			अगर (buf[3] != 0x20) जाओ error;		/* year msb */
			अगर (buf[4] != 0x00) जाओ error;		/* year lsb */
			अवरोध;
		हाल NXT2004:
			अगर (buf[0] != 0x05) जाओ error;		/* device id */
			अवरोध;
		शेष:
			जाओ error;
	पूर्ण

	/* create dvb_frontend */
	स_नकल(&state->frontend.ops, &nxt200x_ops, माप(काष्ठा dvb_frontend_ops));
	state->frontend.demodulator_priv = state;
	वापस &state->frontend;

error:
	kमुक्त(state);
	pr_err("Unknown/Unsupported NXT chip: %*ph\n", 5, buf);
	वापस शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_frontend_ops nxt200x_ops = अणु
	.delsys = अणु SYS_ATSC, SYS_DVBC_ANNEX_B पूर्ण,
	.info = अणु
		.name = "Nextwave NXT200X VSB/QAM frontend",
		.frequency_min_hz =  54 * MHz,
		.frequency_max_hz = 860 * MHz,
		.frequency_stepsize_hz = 166666,	/* stepsize is just a guess */
		.caps = FE_CAN_FEC_1_2 | FE_CAN_FEC_2_3 | FE_CAN_FEC_3_4 |
			FE_CAN_FEC_5_6 | FE_CAN_FEC_7_8 | FE_CAN_FEC_AUTO |
			FE_CAN_8VSB | FE_CAN_QAM_64 | FE_CAN_QAM_256
	पूर्ण,

	.release = nxt200x_release,

	.init = nxt200x_init,
	.sleep = nxt200x_sleep,

	.set_frontend = nxt200x_setup_frontend_parameters,
	.get_tune_settings = nxt200x_get_tune_settings,

	.पढ़ो_status = nxt200x_पढ़ो_status,
	.पढ़ो_ber = nxt200x_पढ़ो_ber,
	.पढ़ो_संकेत_strength = nxt200x_पढ़ो_संकेत_strength,
	.पढ़ो_snr = nxt200x_पढ़ो_snr,
	.पढ़ो_ucblocks = nxt200x_पढ़ो_ucblocks,
पूर्ण;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off frontend debugging (default:off).");

MODULE_DESCRIPTION("NXT200X (ATSC 8VSB & ITU-T J.83 AnnexB 64/256 QAM) Demodulator Driver");
MODULE_AUTHOR("Kirk Lapray, Michael Krufky, Jean-Francois Thibert, and Taylor Jacob");
MODULE_LICENSE("GPL");

EXPORT_SYMBOL(nxt200x_attach);

