<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Xceive XC5000 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2007 Xceive Corporation
 *  Copyright (c) 2007 Steven Toth <stoth@linuxtv.org>
 *  Copyright (c) 2009 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>

#समावेश <media/dvb_frontend.h>

#समावेश "xc5000.h"
#समावेश "tuner-i2c.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Turn on/off debugging (default:off).");

अटल पूर्णांक no_घातeroff;
module_param(no_घातeroff, पूर्णांक, 0644);
MODULE_PARM_DESC(no_घातeroff, "0 (default) powers device off when not used.\n"
	"\t\t1 keep device energized and with tuner ready all the times.\n"
	"\t\tFaster, but consumes more power and keeps the device hotter");

अटल DEFINE_MUTEX(xc5000_list_mutex);
अटल LIST_HEAD(hybrid_tuner_instance_list);

#घोषणा dprपूर्णांकk(level, fmt, arg...) अगर (debug >= level) \
	prपूर्णांकk(KERN_INFO "%s: " fmt, "xc5000", ## arg)

काष्ठा xc5000_priv अणु
	काष्ठा tuner_i2c_props i2c_props;
	काष्ठा list_head hybrid_tuner_instance_list;

	u32 अगर_khz;
	u16 xtal_khz;
	u32 freq_hz, freq_offset;
	u32 bandwidth;
	u8  video_standard;
	अचिन्हित पूर्णांक mode;
	u8  rf_mode;
	u8  radio_input;
	u16  output_amp;

	पूर्णांक chip_id;
	u16 pll_रेजिस्टर_no;
	u8 init_status_supported;
	u8 fw_checksum_supported;

	काष्ठा dvb_frontend *fe;
	काष्ठा delayed_work समयr_sleep;

	स्थिर काष्ठा firmware   *firmware;
पूर्ण;

/* Misc Defines */
#घोषणा MAX_TV_STANDARD			24
#घोषणा XC_MAX_I2C_WRITE_LENGTH		64

/* Time to suspend after the .sleep callback is called */
#घोषणा XC5000_SLEEP_TIME		5000 /* ms */

/* Signal Types */
#घोषणा XC_RF_MODE_AIR			0
#घोषणा XC_RF_MODE_CABLE		1

/* Product id */
#घोषणा XC_PRODUCT_ID_FW_NOT_LOADED	0x2000
#घोषणा XC_PRODUCT_ID_FW_LOADED	0x1388

/* Registers */
#घोषणा XREG_INIT         0x00
#घोषणा XREG_VIDEO_MODE   0x01
#घोषणा XREG_AUDIO_MODE   0x02
#घोषणा XREG_RF_FREQ      0x03
#घोषणा XREG_D_CODE       0x04
#घोषणा XREG_IF_OUT       0x05
#घोषणा XREG_SEEK_MODE    0x07
#घोषणा XREG_POWER_DOWN   0x0A /* Obsolete */
/* Set the output amplitude - SIF क्रम analog, DTVP/DTVN क्रम digital */
#घोषणा XREG_OUTPUT_AMP   0x0B
#घोषणा XREG_SIGNALSOURCE 0x0D /* 0=Air, 1=Cable */
#घोषणा XREG_SMOOTHEDCVBS 0x0E
#घोषणा XREG_XTALFREQ     0x0F
#घोषणा XREG_FINERFREQ    0x10
#घोषणा XREG_DDIMODE      0x11

#घोषणा XREG_ADC_ENV      0x00
#घोषणा XREG_QUALITY      0x01
#घोषणा XREG_FRAME_LINES  0x02
#घोषणा XREG_HSYNC_FREQ   0x03
#घोषणा XREG_LOCK         0x04
#घोषणा XREG_FREQ_ERROR   0x05
#घोषणा XREG_SNR          0x06
#घोषणा XREG_VERSION      0x07
#घोषणा XREG_PRODUCT_ID   0x08
#घोषणा XREG_BUSY         0x09
#घोषणा XREG_BUILD        0x0D
#घोषणा XREG_TOTALGAIN    0x0F
#घोषणा XREG_FW_CHECKSUM  0x12
#घोषणा XREG_INIT_STATUS  0x13

/*
   Basic firmware description. This will reमुख्य with
   the driver क्रम करोcumentation purposes.

   This represents an I2C firmware file encoded as a
   string of अचिन्हित अक्षर. Format is as follows:

   अक्षर[0  ]=len0_MSB  -> len = len_MSB * 256 + len_LSB
   अक्षर[1  ]=len0_LSB  -> length of first ग_लिखो transaction
   अक्षर[2  ]=data0 -> first byte to be sent
   अक्षर[3  ]=data1
   अक्षर[4  ]=data2
   अक्षर[   ]=...
   अक्षर[M  ]=dataN  -> last byte to be sent
   अक्षर[M+1]=len1_MSB  -> len = len_MSB * 256 + len_LSB
   अक्षर[M+2]=len1_LSB  -> length of second ग_लिखो transaction
   अक्षर[M+3]=data0
   अक्षर[M+4]=data1
   ...
   etc.

   The [len] value should be पूर्णांकerpreted as follows:

   len= len_MSB _ len_LSB
   len=1111_1111_1111_1111   : End of I2C_SEQUENCE
   len=0000_0000_0000_0000   : Reset command: Do hardware reset
   len=0NNN_NNNN_NNNN_NNNN   : Normal transaction: number of bytes = अणु1:32767)
   len=1WWW_WWWW_WWWW_WWWW   : Wait command: रुको क्रम अणु1:32767पूर्ण ms

   For the RESET and WAIT commands, the two following bytes will contain
   immediately the length of the following transaction.

*/
काष्ठा XC_TV_STANDARD अणु
	अक्षर *name;
	u16 audio_mode;
	u16 video_mode;
पूर्ण;

/* Tuner standards */
#घोषणा MN_NTSC_PAL_BTSC	0
#घोषणा MN_NTSC_PAL_A2		1
#घोषणा MN_NTSC_PAL_EIAJ	2
#घोषणा MN_NTSC_PAL_MONO	3
#घोषणा BG_PAL_A2		4
#घोषणा BG_PAL_NICAM		5
#घोषणा BG_PAL_MONO		6
#घोषणा I_PAL_NICAM		7
#घोषणा I_PAL_NICAM_MONO	8
#घोषणा DK_PAL_A2		9
#घोषणा DK_PAL_NICAM		10
#घोषणा DK_PAL_MONO		11
#घोषणा DK_SECAM_A2DK1		12
#घोषणा DK_SECAM_A2LDK3		13
#घोषणा DK_SECAM_A2MONO		14
#घोषणा L_SECAM_NICAM		15
#घोषणा LC_SECAM_NICAM		16
#घोषणा DTV6			17
#घोषणा DTV8			18
#घोषणा DTV7_8			19
#घोषणा DTV7			20
#घोषणा FM_RADIO_INPUT2		21
#घोषणा FM_RADIO_INPUT1		22
#घोषणा FM_RADIO_INPUT1_MONO	23

अटल काष्ठा XC_TV_STANDARD xc5000_standard[MAX_TV_STANDARD] = अणु
	अणु"M/N-NTSC/PAL-BTSC", 0x0400, 0x8020पूर्ण,
	अणु"M/N-NTSC/PAL-A2",   0x0600, 0x8020पूर्ण,
	अणु"M/N-NTSC/PAL-EIAJ", 0x0440, 0x8020पूर्ण,
	अणु"M/N-NTSC/PAL-Mono", 0x0478, 0x8020पूर्ण,
	अणु"B/G-PAL-A2",        0x0A00, 0x8049पूर्ण,
	अणु"B/G-PAL-NICAM",     0x0C04, 0x8049पूर्ण,
	अणु"B/G-PAL-MONO",      0x0878, 0x8059पूर्ण,
	अणु"I-PAL-NICAM",       0x1080, 0x8009पूर्ण,
	अणु"I-PAL-NICAM-MONO",  0x0E78, 0x8009पूर्ण,
	अणु"D/K-PAL-A2",        0x1600, 0x8009पूर्ण,
	अणु"D/K-PAL-NICAM",     0x0E80, 0x8009पूर्ण,
	अणु"D/K-PAL-MONO",      0x1478, 0x8009पूर्ण,
	अणु"D/K-SECAM-A2 DK1",  0x1200, 0x8009पूर्ण,
	अणु"D/K-SECAM-A2 L/DK3", 0x0E00, 0x8009पूर्ण,
	अणु"D/K-SECAM-A2 MONO", 0x1478, 0x8009पूर्ण,
	अणु"L-SECAM-NICAM",     0x8E82, 0x0009पूर्ण,
	अणु"L'-SECAM-NICAM",    0x8E82, 0x4009पूर्ण,
	अणु"DTV6",              0x00C0, 0x8002पूर्ण,
	अणु"DTV8",              0x00C0, 0x800Bपूर्ण,
	अणु"DTV7/8",            0x00C0, 0x801Bपूर्ण,
	अणु"DTV7",              0x00C0, 0x8007पूर्ण,
	अणु"FM Radio-INPUT2",   0x9802, 0x9002पूर्ण,
	अणु"FM Radio-INPUT1",   0x0208, 0x9002पूर्ण,
	अणु"FM Radio-INPUT1_MONO", 0x0278, 0x9002पूर्ण
पूर्ण;


काष्ठा xc5000_fw_cfg अणु
	अक्षर *name;
	u16 size;
	u16 pll_reg;
	u8 init_status_supported;
	u8 fw_checksum_supported;
पूर्ण;

#घोषणा XC5000A_FIRMWARE "dvb-fe-xc5000-1.6.114.fw"
अटल स्थिर काष्ठा xc5000_fw_cfg xc5000a_1_6_114 = अणु
	.name = XC5000A_FIRMWARE,
	.size = 12401,
	.pll_reg = 0x806c,
पूर्ण;

#घोषणा XC5000C_FIRMWARE "dvb-fe-xc5000c-4.1.30.7.fw"
अटल स्थिर काष्ठा xc5000_fw_cfg xc5000c_41_024_5 = अणु
	.name = XC5000C_FIRMWARE,
	.size = 16497,
	.pll_reg = 0x13,
	.init_status_supported = 1,
	.fw_checksum_supported = 1,
पूर्ण;

अटल अंतरभूत स्थिर काष्ठा xc5000_fw_cfg *xc5000_assign_firmware(पूर्णांक chip_id)
अणु
	चयन (chip_id) अणु
	शेष:
	हाल XC5000A:
		वापस &xc5000a_1_6_114;
	हाल XC5000C:
		वापस &xc5000c_41_024_5;
	पूर्ण
पूर्ण

अटल पूर्णांक xc_load_fw_and_init_tuner(काष्ठा dvb_frontend *fe, पूर्णांक क्रमce);
अटल पूर्णांक xc5000_is_firmware_loaded(काष्ठा dvb_frontend *fe);
अटल पूर्णांक xc5000_पढ़ोreg(काष्ठा xc5000_priv *priv, u16 reg, u16 *val);
अटल पूर्णांक xc5000_tuner_reset(काष्ठा dvb_frontend *fe);

अटल पूर्णांक xc_send_i2c_data(काष्ठा xc5000_priv *priv, u8 *buf, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_props.addr,
			       .flags = 0, .buf = buf, .len = len पूर्ण;

	अगर (i2c_transfer(priv->i2c_props.adap, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_ERR "xc5000: I2C write failed (len=%i)\n", len);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण

#अगर 0
/* This routine is never used because the only समय we पढ़ो data from the
   i2c bus is when we पढ़ो रेजिस्टरs, and we want that to be an atomic i2c
   transaction in हाल we are on a multi-master bus */
अटल पूर्णांक xc_पढ़ो_i2c_data(काष्ठा xc5000_priv *priv, u8 *buf, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_props.addr,
		.flags = I2C_M_RD, .buf = buf, .len = len पूर्ण;

	अगर (i2c_transfer(priv->i2c_props.adap, &msg, 1) != 1) अणु
		prपूर्णांकk(KERN_ERR "xc5000 I2C read failed (len=%i)\n", len);
		वापस -EREMOTEIO;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xc5000_पढ़ोreg(काष्ठा xc5000_priv *priv, u16 reg, u16 *val)
अणु
	u8 buf[2] = अणु reg >> 8, reg & 0xff पूर्ण;
	u8 bval[2] = अणु 0, 0 पूर्ण;
	काष्ठा i2c_msg msg[2] = अणु
		अणु .addr = priv->i2c_props.addr,
			.flags = 0, .buf = &buf[0], .len = 2 पूर्ण,
		अणु .addr = priv->i2c_props.addr,
			.flags = I2C_M_RD, .buf = &bval[0], .len = 2 पूर्ण,
	पूर्ण;

	अगर (i2c_transfer(priv->i2c_props.adap, msg, 2) != 2) अणु
		prपूर्णांकk(KERN_WARNING "xc5000: I2C read failed\n");
		वापस -EREMOTEIO;
	पूर्ण

	*val = (bval[0] << 8) | bval[1];
	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_tuner_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (fe->callback) अणु
		ret = fe->callback(((fe->dvb) && (fe->dvb->priv)) ?
					   fe->dvb->priv :
					   priv->i2c_props.adap->algo_data,
					   DVB_FRONTEND_COMPONENT_TUNER,
					   XC5000_TUNER_RESET, 0);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "xc5000: reset failed\n");
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "xc5000: no tuner reset callback function, fatal\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xc_ग_लिखो_reg(काष्ठा xc5000_priv *priv, u16 reg_addr, u16 i2c_data)
अणु
	u8 buf[4];
	पूर्णांक watch_करोg_समयr = 100;
	पूर्णांक result;

	buf[0] = (reg_addr >> 8) & 0xFF;
	buf[1] = reg_addr & 0xFF;
	buf[2] = (i2c_data >> 8) & 0xFF;
	buf[3] = i2c_data & 0xFF;
	result = xc_send_i2c_data(priv, buf, 4);
	अगर (result == 0) अणु
		/* रुको क्रम busy flag to clear */
		जबतक ((watch_करोg_समयr > 0) && (result == 0)) अणु
			result = xc5000_पढ़ोreg(priv, XREG_BUSY, (u16 *)buf);
			अगर (result == 0) अणु
				अगर ((buf[0] == 0) && (buf[1] == 0)) अणु
					/* busy flag cleared */
					अवरोध;
				पूर्ण अन्यथा अणु
					msleep(5); /* रुको 5 ms */
					watch_करोg_समयr--;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (watch_करोg_समयr <= 0)
		result = -EREMOTEIO;

	वापस result;
पूर्ण

अटल पूर्णांक xc_load_i2c_sequence(काष्ठा dvb_frontend *fe, स्थिर u8 *i2c_sequence)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	पूर्णांक i, nbytes_to_send, result;
	अचिन्हित पूर्णांक len, pos, index;
	u8 buf[XC_MAX_I2C_WRITE_LENGTH];

	index = 0;
	जबतक ((i2c_sequence[index] != 0xFF) ||
		(i2c_sequence[index + 1] != 0xFF)) अणु
		len = i2c_sequence[index] * 256 + i2c_sequence[index+1];
		अगर (len == 0x0000) अणु
			/* RESET command */
			result = xc5000_tuner_reset(fe);
			index += 2;
			अगर (result != 0)
				वापस result;
		पूर्ण अन्यथा अगर (len & 0x8000) अणु
			/* WAIT command */
			msleep(len & 0x7FFF);
			index += 2;
		पूर्ण अन्यथा अणु
			/* Send i2c data whilst ensuring inभागidual transactions
			 * करो not exceed XC_MAX_I2C_WRITE_LENGTH bytes.
			 */
			index += 2;
			buf[0] = i2c_sequence[index];
			buf[1] = i2c_sequence[index + 1];
			pos = 2;
			जबतक (pos < len) अणु
				अगर ((len - pos) > XC_MAX_I2C_WRITE_LENGTH - 2)
					nbytes_to_send =
						XC_MAX_I2C_WRITE_LENGTH;
				अन्यथा
					nbytes_to_send = (len - pos + 2);
				क्रम (i = 2; i < nbytes_to_send; i++) अणु
					buf[i] = i2c_sequence[index + pos +
						i - 2];
				पूर्ण
				result = xc_send_i2c_data(priv, buf,
					nbytes_to_send);

				अगर (result != 0)
					वापस result;

				pos += nbytes_to_send - 2;
			पूर्ण
			index += len;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xc_initialize(काष्ठा xc5000_priv *priv)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);
	वापस xc_ग_लिखो_reg(priv, XREG_INIT, 0);
पूर्ण

अटल पूर्णांक xc_set_tv_standard(काष्ठा xc5000_priv *priv,
	u16 video_mode, u16 audio_mode, u8 radio_mode)
अणु
	पूर्णांक ret;
	dprपूर्णांकk(1, "%s(0x%04x,0x%04x)\n", __func__, video_mode, audio_mode);
	अगर (radio_mode) अणु
		dprपूर्णांकk(1, "%s() Standard = %s\n",
			__func__,
			xc5000_standard[radio_mode].name);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(1, "%s() Standard = %s\n",
			__func__,
			xc5000_standard[priv->video_standard].name);
	पूर्ण

	ret = xc_ग_लिखो_reg(priv, XREG_VIDEO_MODE, video_mode);
	अगर (ret == 0)
		ret = xc_ग_लिखो_reg(priv, XREG_AUDIO_MODE, audio_mode);

	वापस ret;
पूर्ण

अटल पूर्णांक xc_set_संकेत_source(काष्ठा xc5000_priv *priv, u16 rf_mode)
अणु
	dprपूर्णांकk(1, "%s(%d) Source = %s\n", __func__, rf_mode,
		rf_mode == XC_RF_MODE_AIR ? "ANTENNA" : "CABLE");

	अगर ((rf_mode != XC_RF_MODE_AIR) && (rf_mode != XC_RF_MODE_CABLE)) अणु
		rf_mode = XC_RF_MODE_CABLE;
		prपूर्णांकk(KERN_ERR
			"%s(), Invalid mode, defaulting to CABLE",
			__func__);
	पूर्ण
	वापस xc_ग_लिखो_reg(priv, XREG_SIGNALSOURCE, rf_mode);
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops xc5000_tuner_ops;

अटल पूर्णांक xc_set_rf_frequency(काष्ठा xc5000_priv *priv, u32 freq_hz)
अणु
	u16 freq_code;

	dprपूर्णांकk(1, "%s(%u)\n", __func__, freq_hz);

	अगर ((freq_hz > xc5000_tuner_ops.info.frequency_max_hz) ||
		(freq_hz < xc5000_tuner_ops.info.frequency_min_hz))
		वापस -EINVAL;

	freq_code = (u16)(freq_hz / 15625);

	/* Starting in firmware version 1.1.44, Xceive recommends using the
	   FINERFREQ क्रम all normal tuning (the करोc indicates reg 0x03 should
	   only be used क्रम fast scanning क्रम channel lock) */
	वापस xc_ग_लिखो_reg(priv, XREG_FINERFREQ, freq_code);
पूर्ण


अटल पूर्णांक xc_set_IF_frequency(काष्ठा xc5000_priv *priv, u32 freq_khz)
अणु
	u32 freq_code = (freq_khz * 1024)/1000;
	dprपूर्णांकk(1, "%s(freq_khz = %d) freq_code = 0x%x\n",
		__func__, freq_khz, freq_code);

	वापस xc_ग_लिखो_reg(priv, XREG_IF_OUT, freq_code);
पूर्ण


अटल पूर्णांक xc_get_adc_envelope(काष्ठा xc5000_priv *priv, u16 *adc_envelope)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_ADC_ENV, adc_envelope);
पूर्ण

अटल पूर्णांक xc_get_frequency_error(काष्ठा xc5000_priv *priv, u32 *freq_error_hz)
अणु
	पूर्णांक result;
	u16 reg_data;
	u32 पंचांगp;

	result = xc5000_पढ़ोreg(priv, XREG_FREQ_ERROR, &reg_data);
	अगर (result != 0)
		वापस result;

	पंचांगp = (u32)reg_data;
	(*freq_error_hz) = (पंचांगp * 15625) / 1000;
	वापस result;
पूर्ण

अटल पूर्णांक xc_get_lock_status(काष्ठा xc5000_priv *priv, u16 *lock_status)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_LOCK, lock_status);
पूर्ण

अटल पूर्णांक xc_get_version(काष्ठा xc5000_priv *priv,
	u8 *hw_majorversion, u8 *hw_minorversion,
	u8 *fw_majorversion, u8 *fw_minorversion)
अणु
	u16 data;
	पूर्णांक result;

	result = xc5000_पढ़ोreg(priv, XREG_VERSION, &data);
	अगर (result != 0)
		वापस result;

	(*hw_majorversion) = (data >> 12) & 0x0F;
	(*hw_minorversion) = (data >>  8) & 0x0F;
	(*fw_majorversion) = (data >>  4) & 0x0F;
	(*fw_minorversion) = data & 0x0F;

	वापस 0;
पूर्ण

अटल पूर्णांक xc_get_buildversion(काष्ठा xc5000_priv *priv, u16 *buildrev)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_BUILD, buildrev);
पूर्ण

अटल पूर्णांक xc_get_hsync_freq(काष्ठा xc5000_priv *priv, u32 *hsync_freq_hz)
अणु
	u16 reg_data;
	पूर्णांक result;

	result = xc5000_पढ़ोreg(priv, XREG_HSYNC_FREQ, &reg_data);
	अगर (result != 0)
		वापस result;

	(*hsync_freq_hz) = ((reg_data & 0x0fff) * 763)/100;
	वापस result;
पूर्ण

अटल पूर्णांक xc_get_frame_lines(काष्ठा xc5000_priv *priv, u16 *frame_lines)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_FRAME_LINES, frame_lines);
पूर्ण

अटल पूर्णांक xc_get_quality(काष्ठा xc5000_priv *priv, u16 *quality)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_QUALITY, quality);
पूर्ण

अटल पूर्णांक xc_get_analogsnr(काष्ठा xc5000_priv *priv, u16 *snr)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_SNR, snr);
पूर्ण

अटल पूर्णांक xc_get_totalgain(काष्ठा xc5000_priv *priv, u16 *totalgain)
अणु
	वापस xc5000_पढ़ोreg(priv, XREG_TOTALGAIN, totalgain);
पूर्ण

#घोषणा XC_TUNE_ANALOG  0
#घोषणा XC_TUNE_DIGITAL 1
अटल पूर्णांक xc_tune_channel(काष्ठा xc5000_priv *priv, u32 freq_hz, पूर्णांक mode)
अणु
	dprपूर्णांकk(1, "%s(%u)\n", __func__, freq_hz);

	अगर (xc_set_rf_frequency(priv, freq_hz) != 0)
		वापस -EREMOTEIO;

	वापस 0;
पूर्ण

अटल पूर्णांक xc_set_xtal(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret = 0;

	चयन (priv->chip_id) अणु
	शेष:
	हाल XC5000A:
		/* 32.000 MHz xtal is शेष */
		अवरोध;
	हाल XC5000C:
		चयन (priv->xtal_khz) अणु
		शेष:
		हाल 32000:
			/* 32.000 MHz xtal is शेष */
			अवरोध;
		हाल 31875:
			/* 31.875 MHz xtal configuration */
			ret = xc_ग_लिखो_reg(priv, 0x000f, 0x8081);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक xc5000_fwupload(काष्ठा dvb_frontend *fe,
			   स्थिर काष्ठा xc5000_fw_cfg *desired_fw,
			   स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	/* request the firmware, this will block and समयout */
	dprपूर्णांकk(1, "waiting for firmware upload (%s)...\n",
		desired_fw->name);

	priv->pll_रेजिस्टर_no = desired_fw->pll_reg;
	priv->init_status_supported = desired_fw->init_status_supported;
	priv->fw_checksum_supported = desired_fw->fw_checksum_supported;


	dprपूर्णांकk(1, "firmware uploading...\n");
	ret = xc_load_i2c_sequence(fe,  fw->data);
	अगर (!ret) अणु
		ret = xc_set_xtal(fe);
		dprपूर्णांकk(1, "Firmware upload complete...\n");
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_ERR "xc5000: firmware upload failed...\n");

	वापस ret;
पूर्ण

अटल व्योम xc_debug_dump(काष्ठा xc5000_priv *priv)
अणु
	u16 adc_envelope;
	u32 freq_error_hz = 0;
	u16 lock_status;
	u32 hsync_freq_hz = 0;
	u16 frame_lines;
	u16 quality;
	u16 snr;
	u16 totalgain;
	u8 hw_majorversion = 0, hw_minorversion = 0;
	u8 fw_majorversion = 0, fw_minorversion = 0;
	u16 fw_buildversion = 0;
	u16 regval;

	/* Wait क्रम stats to stabilize.
	 * Frame Lines needs two frame बार after initial lock
	 * beक्रमe it is valid.
	 */
	msleep(100);

	xc_get_adc_envelope(priv,  &adc_envelope);
	dprपूर्णांकk(1, "*** ADC envelope (0-1023) = %d\n", adc_envelope);

	xc_get_frequency_error(priv, &freq_error_hz);
	dprपूर्णांकk(1, "*** Frequency error = %d Hz\n", freq_error_hz);

	xc_get_lock_status(priv,  &lock_status);
	dprपूर्णांकk(1, "*** Lock status (0-Wait, 1-Locked, 2-No-signal) = %d\n",
		lock_status);

	xc_get_version(priv,  &hw_majorversion, &hw_minorversion,
		&fw_majorversion, &fw_minorversion);
	xc_get_buildversion(priv,  &fw_buildversion);
	dprपूर्णांकk(1, "*** HW: V%d.%d, FW: V %d.%d.%d\n",
		hw_majorversion, hw_minorversion,
		fw_majorversion, fw_minorversion, fw_buildversion);

	xc_get_hsync_freq(priv,  &hsync_freq_hz);
	dprपूर्णांकk(1, "*** Horizontal sync frequency = %d Hz\n", hsync_freq_hz);

	xc_get_frame_lines(priv,  &frame_lines);
	dprपूर्णांकk(1, "*** Frame lines = %d\n", frame_lines);

	xc_get_quality(priv,  &quality);
	dprपूर्णांकk(1, "*** Quality (0:<8dB, 7:>56dB) = %d\n", quality & 0x07);

	xc_get_analogsnr(priv,  &snr);
	dprपूर्णांकk(1, "*** Unweighted analog SNR = %d dB\n", snr & 0x3f);

	xc_get_totalgain(priv,  &totalgain);
	dprपूर्णांकk(1, "*** Total gain = %d.%d dB\n", totalgain / 256,
		(totalgain % 256) * 100 / 256);

	अगर (priv->pll_रेजिस्टर_no) अणु
		अगर (!xc5000_पढ़ोreg(priv, priv->pll_रेजिस्टर_no, &regval))
			dprपूर्णांकk(1, "*** PLL lock status = 0x%04x\n", regval);
	पूर्ण
पूर्ण

अटल पूर्णांक xc5000_tune_digital(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u32 bw = fe->dtv_property_cache.bandwidth_hz;

	ret = xc_set_संकेत_source(priv, priv->rf_mode);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR
			"xc5000: xc_set_signal_source(%d) failed\n",
			priv->rf_mode);
		वापस -EREMOTEIO;
	पूर्ण

	ret = xc_set_tv_standard(priv,
		xc5000_standard[priv->video_standard].video_mode,
		xc5000_standard[priv->video_standard].audio_mode, 0);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc5000: xc_set_tv_standard failed\n");
		वापस -EREMOTEIO;
	पूर्ण

	ret = xc_set_IF_frequency(priv, priv->अगर_khz);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc5000: xc_Set_IF_frequency(%d) failed\n",
		       priv->अगर_khz);
		वापस -EIO;
	पूर्ण

	dprपूर्णांकk(1, "%s() setting OUTPUT_AMP to 0x%x\n",
		__func__, priv->output_amp);
	xc_ग_लिखो_reg(priv, XREG_OUTPUT_AMP, priv->output_amp);

	xc_tune_channel(priv, priv->freq_hz, XC_TUNE_DIGITAL);

	अगर (debug)
		xc_debug_dump(priv);

	priv->bandwidth = bw;

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_set_digital_params(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक b;
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	u32 freq = fe->dtv_property_cache.frequency;
	u32 delsys  = fe->dtv_property_cache.delivery_प्रणाली;

	अगर (xc_load_fw_and_init_tuner(fe, 0) != 0) अणु
		dprपूर्णांकk(1, "Unable to load firmware and init tuner\n");
		वापस -EINVAL;
	पूर्ण

	dprपूर्णांकk(1, "%s() frequency=%d (Hz)\n", __func__, freq);

	चयन (delsys) अणु
	हाल SYS_ATSC:
		dprपूर्णांकk(1, "%s() VSB modulation\n", __func__);
		priv->rf_mode = XC_RF_MODE_AIR;
		priv->freq_offset = 1750000;
		priv->video_standard = DTV6;
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		dprपूर्णांकk(1, "%s() QAM modulation\n", __func__);
		priv->rf_mode = XC_RF_MODE_CABLE;
		priv->freq_offset = 1750000;
		priv->video_standard = DTV6;
		अवरोध;
	हाल SYS_ISDBT:
		/* All ISDB-T are currently क्रम 6 MHz bw */
		अगर (!bw)
			bw = 6000000;
		/* fall to OFDM handling */
		fallthrough;
	हाल SYS_DMBTH:
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		dprपूर्णांकk(1, "%s() OFDM\n", __func__);
		चयन (bw) अणु
		हाल 6000000:
			priv->video_standard = DTV6;
			priv->freq_offset = 1750000;
			अवरोध;
		हाल 7000000:
			priv->video_standard = DTV7;
			priv->freq_offset = 2250000;
			अवरोध;
		हाल 8000000:
			priv->video_standard = DTV8;
			priv->freq_offset = 2750000;
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "xc5000 bandwidth not set!\n");
			वापस -EINVAL;
		पूर्ण
		priv->rf_mode = XC_RF_MODE_AIR;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		dprपूर्णांकk(1, "%s() QAM modulation\n", __func__);
		priv->rf_mode = XC_RF_MODE_CABLE;
		अगर (bw <= 6000000) अणु
			priv->video_standard = DTV6;
			priv->freq_offset = 1750000;
			b = 6;
		पूर्ण अन्यथा अगर (bw <= 7000000) अणु
			priv->video_standard = DTV7;
			priv->freq_offset = 2250000;
			b = 7;
		पूर्ण अन्यथा अणु
			priv->video_standard = DTV7_8;
			priv->freq_offset = 2750000;
			b = 8;
		पूर्ण
		dprपूर्णांकk(1, "%s() Bandwidth %dMHz (%d)\n", __func__,
			b, bw);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "xc5000: delivery system is not supported!\n");
		वापस -EINVAL;
	पूर्ण

	priv->freq_hz = freq - priv->freq_offset;
	priv->mode = V4L2_TUNER_DIGITAL_TV;

	dprपूर्णांकk(1, "%s() frequency=%d (compensated to %d)\n",
		__func__, freq, priv->freq_hz);

	वापस xc5000_tune_digital(fe);
पूर्ण

अटल पूर्णांक xc5000_is_firmware_loaded(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u16 id;

	ret = xc5000_पढ़ोreg(priv, XREG_PRODUCT_ID, &id);
	अगर (!ret) अणु
		अगर (id == XC_PRODUCT_ID_FW_NOT_LOADED)
			ret = -ENOENT;
		अन्यथा
			ret = 0;
		dprपूर्णांकk(1, "%s() returns id = 0x%x\n", __func__, id);
	पूर्ण अन्यथा अणु
		dprपूर्णांकk(1, "%s() returns error %d\n", __func__, ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम xc5000_config_tv(काष्ठा dvb_frontend *fe,
			     काष्ठा analog_parameters *params)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	dprपूर्णांकk(1, "%s() frequency=%d (in units of 62.5khz)\n",
		__func__, params->frequency);

	/* Fix me: it could be air. */
	priv->rf_mode = params->mode;
	अगर (params->mode > XC_RF_MODE_CABLE)
		priv->rf_mode = XC_RF_MODE_CABLE;

	/* params->frequency is in units of 62.5khz */
	priv->freq_hz = params->frequency * 62500;

	/* FIX ME: Some video standards may have several possible audio
		   standards. We simply शेष to one of them here.
	 */
	अगर (params->std & V4L2_STD_MN) अणु
		/* शेष to BTSC audio standard */
		priv->video_standard = MN_NTSC_PAL_BTSC;
		वापस;
	पूर्ण

	अगर (params->std & V4L2_STD_PAL_BG) अणु
		/* शेष to NICAM audio standard */
		priv->video_standard = BG_PAL_NICAM;
		वापस;
	पूर्ण

	अगर (params->std & V4L2_STD_PAL_I) अणु
		/* शेष to NICAM audio standard */
		priv->video_standard = I_PAL_NICAM;
		वापस;
	पूर्ण

	अगर (params->std & V4L2_STD_PAL_DK) अणु
		/* शेष to NICAM audio standard */
		priv->video_standard = DK_PAL_NICAM;
		वापस;
	पूर्ण

	अगर (params->std & V4L2_STD_SECAM_DK) अणु
		/* शेष to A2 DK1 audio standard */
		priv->video_standard = DK_SECAM_A2DK1;
		वापस;
	पूर्ण

	अगर (params->std & V4L2_STD_SECAM_L) अणु
		priv->video_standard = L_SECAM_NICAM;
		वापस;
	पूर्ण

	अगर (params->std & V4L2_STD_SECAM_LC) अणु
		priv->video_standard = LC_SECAM_NICAM;
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक xc5000_set_tv_freq(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	u16 pll_lock_status;
	पूर्णांक ret;

tune_channel:
	ret = xc_set_संकेत_source(priv, priv->rf_mode);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR
			"xc5000: xc_set_signal_source(%d) failed\n",
			priv->rf_mode);
		वापस -EREMOTEIO;
	पूर्ण

	ret = xc_set_tv_standard(priv,
		xc5000_standard[priv->video_standard].video_mode,
		xc5000_standard[priv->video_standard].audio_mode, 0);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc5000: xc_set_tv_standard failed\n");
		वापस -EREMOTEIO;
	पूर्ण

	xc_ग_लिखो_reg(priv, XREG_OUTPUT_AMP, 0x09);

	xc_tune_channel(priv, priv->freq_hz, XC_TUNE_ANALOG);

	अगर (debug)
		xc_debug_dump(priv);

	अगर (priv->pll_रेजिस्टर_no != 0) अणु
		msleep(20);
		ret = xc5000_पढ़ोreg(priv, priv->pll_रेजिस्टर_no,
				     &pll_lock_status);
		अगर (ret)
			वापस ret;
		अगर (pll_lock_status > 63) अणु
			/* PLL is unlocked, क्रमce reload of the firmware */
			dprपूर्णांकk(1, "xc5000: PLL not locked (0x%x).  Reloading...\n",
				pll_lock_status);
			अगर (xc_load_fw_and_init_tuner(fe, 1) != 0) अणु
				prपूर्णांकk(KERN_ERR "xc5000: Unable to reload fw\n");
				वापस -EREMOTEIO;
			पूर्ण
			जाओ tune_channel;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_config_radio(काष्ठा dvb_frontend *fe,
			       काष्ठा analog_parameters *params)

अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	dprपूर्णांकk(1, "%s() frequency=%d (in units of khz)\n",
		__func__, params->frequency);

	अगर (priv->radio_input == XC5000_RADIO_NOT_CONFIGURED) अणु
		dprपूर्णांकk(1, "%s() radio input not configured\n", __func__);
		वापस -EINVAL;
	पूर्ण

	priv->freq_hz = params->frequency * 125 / 2;
	priv->rf_mode = XC_RF_MODE_AIR;

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_set_radio_freq(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;
	u8 radio_input;

	अगर (priv->radio_input == XC5000_RADIO_FM1)
		radio_input = FM_RADIO_INPUT1;
	अन्यथा अगर  (priv->radio_input == XC5000_RADIO_FM2)
		radio_input = FM_RADIO_INPUT2;
	अन्यथा अगर  (priv->radio_input == XC5000_RADIO_FM1_MONO)
		radio_input = FM_RADIO_INPUT1_MONO;
	अन्यथा अणु
		dprपूर्णांकk(1, "%s() unknown radio input %d\n", __func__,
			priv->radio_input);
		वापस -EINVAL;
	पूर्ण

	ret = xc_set_tv_standard(priv, xc5000_standard[radio_input].video_mode,
			       xc5000_standard[radio_input].audio_mode, radio_input);

	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc5000: xc_set_tv_standard failed\n");
		वापस -EREMOTEIO;
	पूर्ण

	ret = xc_set_संकेत_source(priv, priv->rf_mode);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR
			"xc5000: xc_set_signal_source(%d) failed\n",
			priv->rf_mode);
		वापस -EREMOTEIO;
	पूर्ण

	अगर ((priv->radio_input == XC5000_RADIO_FM1) ||
				(priv->radio_input == XC5000_RADIO_FM2))
		xc_ग_लिखो_reg(priv, XREG_OUTPUT_AMP, 0x09);
	अन्यथा अगर  (priv->radio_input == XC5000_RADIO_FM1_MONO)
		xc_ग_लिखो_reg(priv, XREG_OUTPUT_AMP, 0x06);

	xc_tune_channel(priv, priv->freq_hz, XC_TUNE_ANALOG);

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	अगर (xc_load_fw_and_init_tuner(fe, 0) != 0) अणु
		dprपूर्णांकk(1, "Unable to load firmware and init tuner\n");
		वापस -EINVAL;
	पूर्ण

	चयन (priv->mode) अणु
	हाल V4L2_TUNER_RADIO:
		वापस xc5000_set_radio_freq(fe);
	हाल V4L2_TUNER_ANALOG_TV:
		वापस xc5000_set_tv_freq(fe);
	हाल V4L2_TUNER_DIGITAL_TV:
		वापस xc5000_tune_digital(fe);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_set_analog_params(काष्ठा dvb_frontend *fe,
			     काष्ठा analog_parameters *params)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	अगर (priv->i2c_props.adap == शून्य)
		वापस -EINVAL;

	चयन (params->mode) अणु
	हाल V4L2_TUNER_RADIO:
		ret = xc5000_config_radio(fe, params);
		अगर (ret)
			वापस ret;
		अवरोध;
	हाल V4L2_TUNER_ANALOG_TV:
		xc5000_config_tv(fe, params);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	priv->mode = params->mode;

	वापस xc5000_set_params(fe);
पूर्ण

अटल पूर्णांक xc5000_get_frequency(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);
	*freq = priv->freq_hz + priv->freq_offset;
	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_get_अगर_frequency(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);
	*freq = priv->अगर_khz * 1000;
	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bw)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);

	*bw = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	u16 lock_status = 0;

	xc_get_lock_status(priv, &lock_status);

	dprपूर्णांकk(1, "%s() lock_status = 0x%08x\n", __func__, lock_status);

	*status = lock_status;

	वापस 0;
पूर्ण

अटल पूर्णांक xc_load_fw_and_init_tuner(काष्ठा dvb_frontend *fe, पूर्णांक क्रमce)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	स्थिर काष्ठा xc5000_fw_cfg *desired_fw = xc5000_assign_firmware(priv->chip_id);
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret, i;
	u16 pll_lock_status;
	u16 fw_ck;

	cancel_delayed_work(&priv->समयr_sleep);

	अगर (!क्रमce && xc5000_is_firmware_loaded(fe) == 0)
		वापस 0;

	अगर (!priv->firmware) अणु
		ret = request_firmware(&fw, desired_fw->name,
					priv->i2c_props.adap->dev.parent);
		अगर (ret) अणु
			pr_err("xc5000: Upload failed. rc %d\n", ret);
			वापस ret;
		पूर्ण
		dprपूर्णांकk(1, "firmware read %zu bytes.\n", fw->size);

		अगर (fw->size != desired_fw->size) अणु
			pr_err("xc5000: Firmware file with incorrect size\n");
			release_firmware(fw);
			वापस -EINVAL;
		पूर्ण
		priv->firmware = fw;
	पूर्ण अन्यथा
		fw = priv->firmware;

	/* Try up to 5 बार to load firmware */
	क्रम (i = 0; i < 5; i++) अणु
		अगर (i)
			prपूर्णांकk(KERN_CONT " - retrying to upload firmware.\n");

		ret = xc5000_fwupload(fe, desired_fw, fw);
		अगर (ret != 0)
			जाओ err;

		msleep(20);

		अगर (priv->fw_checksum_supported) अणु
			अगर (xc5000_पढ़ोreg(priv, XREG_FW_CHECKSUM, &fw_ck)) अणु
				prपूर्णांकk(KERN_ERR
				       "xc5000: FW checksum reading failed.");
				जारी;
			पूर्ण

			अगर (!fw_ck) अणु
				prपूर्णांकk(KERN_ERR
				       "xc5000: FW checksum failed = 0x%04x.",
				       fw_ck);
				जारी;
			पूर्ण
		पूर्ण

		/* Start the tuner self-calibration process */
		ret = xc_initialize(priv);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "xc5000: Can't request self-calibration.");
			जारी;
		पूर्ण

		/* Wait क्रम calibration to complete.
		 * We could जारी but XC5000 will घड़ी stretch subsequent
		 * I2C transactions until calibration is complete.  This way we
		 * करोn't have to rely on घड़ी stretching working.
		 */
		msleep(100);

		अगर (priv->init_status_supported) अणु
			अगर (xc5000_पढ़ोreg(priv, XREG_INIT_STATUS, &fw_ck)) अणु
				prपूर्णांकk(KERN_ERR
				       "xc5000: FW failed reading init status.");
				जारी;
			पूर्ण

			अगर (!fw_ck) अणु
				prपूर्णांकk(KERN_ERR
				       "xc5000: FW init status failed = 0x%04x.",
				       fw_ck);
				जारी;
			पूर्ण
		पूर्ण

		अगर (priv->pll_रेजिस्टर_no) अणु
			ret = xc5000_पढ़ोreg(priv, priv->pll_रेजिस्टर_no,
					     &pll_lock_status);
			अगर (ret)
				जारी;
			अगर (pll_lock_status > 63) अणु
				/* PLL is unlocked, क्रमce reload of the firmware */
				prपूर्णांकk(KERN_ERR
				       "xc5000: PLL not running after fwload.");
				जारी;
			पूर्ण
		पूर्ण

		/* Default to "CABLE" mode */
		ret = xc_ग_लिखो_reg(priv, XREG_SIGNALSOURCE, XC_RF_MODE_CABLE);
		अगर (!ret)
			अवरोध;
		prपूर्णांकk(KERN_ERR "xc5000: can't set to cable mode.");
	पूर्ण

err:
	अगर (!ret)
		prपूर्णांकk(KERN_INFO "xc5000: Firmware %s loaded and running.\n",
		       desired_fw->name);
	अन्यथा
		prपूर्णांकk(KERN_CONT " - too many retries. Giving up\n");

	वापस ret;
पूर्ण

अटल व्योम xc5000_करो_समयr_sleep(काष्ठा work_काष्ठा *समयr_sleep)
अणु
	काष्ठा xc5000_priv *priv =container_of(समयr_sleep, काष्ठा xc5000_priv,
					       समयr_sleep.work);
	काष्ठा dvb_frontend *fe = priv->fe;
	पूर्णांक ret;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* According to Xceive technical support, the "powerdown" रेजिस्टर
	   was हटाओd in newer versions of the firmware.  The "supported"
	   way to sleep the tuner is to pull the reset pin low क्रम 10ms */
	ret = xc5000_tuner_reset(fe);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR
			"xc5000: %s() unable to shutdown tuner\n",
			__func__);
पूर्ण

अटल पूर्णांक xc5000_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* Aव्योम firmware reload on slow devices */
	अगर (no_घातeroff)
		वापस 0;

	schedule_delayed_work(&priv->समयr_sleep,
			      msecs_to_jअगरfies(XC5000_SLEEP_TIME));

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_suspend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	dprपूर्णांकk(1, "%s()\n", __func__);

	cancel_delayed_work(&priv->समयr_sleep);

	ret = xc5000_tuner_reset(fe);
	अगर (ret != 0)
		prपूर्णांकk(KERN_ERR
			"xc5000: %s() unable to shutdown tuner\n",
			__func__);

	वापस 0;
पूर्ण

अटल पूर्णांक xc5000_resume(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	/* suspended beक्रमe firmware is loaded.
	   Aव्योम firmware load in resume path. */
	अगर (!priv->firmware)
		वापस 0;

	वापस xc5000_set_params(fe);
पूर्ण

अटल पूर्णांक xc5000_init(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (xc_load_fw_and_init_tuner(fe, 0) != 0) अणु
		prपूर्णांकk(KERN_ERR "xc5000: Unable to initialise tuner\n");
		वापस -EREMOTEIO;
	पूर्ण

	अगर (debug)
		xc_debug_dump(priv);

	वापस 0;
पूर्ण

अटल व्योम xc5000_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	mutex_lock(&xc5000_list_mutex);

	अगर (priv) अणु
		cancel_delayed_work(&priv->समयr_sleep);
		अगर (priv->firmware) अणु
			release_firmware(priv->firmware);
			priv->firmware = शून्य;
		पूर्ण
		hybrid_tuner_release_state(priv);
	पूर्ण

	mutex_unlock(&xc5000_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

अटल पूर्णांक xc5000_set_config(काष्ठा dvb_frontend *fe, व्योम *priv_cfg)
अणु
	काष्ठा xc5000_priv *priv = fe->tuner_priv;
	काष्ठा xc5000_config *p = priv_cfg;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (p->अगर_khz)
		priv->अगर_khz = p->अगर_khz;

	अगर (p->radio_input)
		priv->radio_input = p->radio_input;

	अगर (p->output_amp)
		priv->output_amp = p->output_amp;

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा dvb_tuner_ops xc5000_tuner_ops = अणु
	.info = अणु
		.name              = "Xceive XC5000",
		.frequency_min_hz  =    1 * MHz,
		.frequency_max_hz  = 1023 * MHz,
		.frequency_step_hz =   50 * kHz,
	पूर्ण,

	.release	   = xc5000_release,
	.init		   = xc5000_init,
	.sleep		   = xc5000_sleep,
	.suspend	   = xc5000_suspend,
	.resume		   = xc5000_resume,

	.set_config	   = xc5000_set_config,
	.set_params	   = xc5000_set_digital_params,
	.set_analog_params = xc5000_set_analog_params,
	.get_frequency	   = xc5000_get_frequency,
	.get_अगर_frequency  = xc5000_get_अगर_frequency,
	.get_bandwidth	   = xc5000_get_bandwidth,
	.get_status	   = xc5000_get_status
पूर्ण;

काष्ठा dvb_frontend *xc5000_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा i2c_adapter *i2c,
				   स्थिर काष्ठा xc5000_config *cfg)
अणु
	काष्ठा xc5000_priv *priv = शून्य;
	पूर्णांक instance;
	u16 id = 0;

	dprपूर्णांकk(1, "%s(%d-%04x)\n", __func__,
		i2c ? i2c_adapter_id(i2c) : -1,
		cfg ? cfg->i2c_address : -1);

	mutex_lock(&xc5000_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा xc5000_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c, cfg->i2c_address, "xc5000");
	चयन (instance) अणु
	हाल 0:
		जाओ fail;
	हाल 1:
		/* new tuner instance */
		priv->bandwidth = 6000000;
		fe->tuner_priv = priv;
		priv->fe = fe;
		INIT_DELAYED_WORK(&priv->समयr_sleep, xc5000_करो_समयr_sleep);
		अवरोध;
	शेष:
		/* existing tuner instance */
		fe->tuner_priv = priv;
		अवरोध;
	पूर्ण

	अगर (priv->अगर_khz == 0) अणु
		/* If the IF hasn't been set yet, use the value provided by
		   the caller (occurs in hybrid devices where the analog
		   call to xc5000_attach occurs beक्रमe the digital side) */
		priv->अगर_khz = cfg->अगर_khz;
	पूर्ण

	अगर (priv->xtal_khz == 0)
		priv->xtal_khz = cfg->xtal_khz;

	अगर (priv->radio_input == 0)
		priv->radio_input = cfg->radio_input;

	/* करोn't override chip id if it's alपढ़ोy been set
	   unless explicitly specअगरied */
	अगर ((priv->chip_id == 0) || (cfg->chip_id))
		/* use शेष chip id अगर none specअगरied, set to 0 so
		   it can be overridden अगर this is a hybrid driver */
		priv->chip_id = (cfg->chip_id) ? cfg->chip_id : 0;

	/* करोn't override output_amp if it's alपढ़ोy been set
	   unless explicitly specअगरied */
	अगर ((priv->output_amp == 0) || (cfg->output_amp))
		/* use शेष output_amp value अगर none specअगरied */
		priv->output_amp = (cfg->output_amp) ? cfg->output_amp : 0x8a;

	/* Check अगर firmware has been loaded. It is possible that another
	   instance of the driver has loaded the firmware.
	 */
	अगर (xc5000_पढ़ोreg(priv, XREG_PRODUCT_ID, &id) != 0)
		जाओ fail;

	चयन (id) अणु
	हाल XC_PRODUCT_ID_FW_LOADED:
		prपूर्णांकk(KERN_INFO
			"xc5000: Successfully identified at address 0x%02x\n",
			cfg->i2c_address);
		prपूर्णांकk(KERN_INFO
			"xc5000: Firmware has been loaded previously\n");
		अवरोध;
	हाल XC_PRODUCT_ID_FW_NOT_LOADED:
		prपूर्णांकk(KERN_INFO
			"xc5000: Successfully identified at address 0x%02x\n",
			cfg->i2c_address);
		prपूर्णांकk(KERN_INFO
			"xc5000: Firmware has not been loaded previously\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR
			"xc5000: Device not found at addr 0x%02x (0x%x)\n",
			cfg->i2c_address, id);
		जाओ fail;
	पूर्ण

	mutex_unlock(&xc5000_list_mutex);

	स_नकल(&fe->ops.tuner_ops, &xc5000_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));

	वापस fe;
fail:
	mutex_unlock(&xc5000_list_mutex);

	xc5000_release(fe);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(xc5000_attach);

MODULE_AUTHOR("Steven Toth");
MODULE_DESCRIPTION("Xceive xc5000 silicon tuner driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(XC5000A_FIRMWARE);
MODULE_FIRMWARE(XC5000C_FIRMWARE);
