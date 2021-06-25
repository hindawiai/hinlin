<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Xceive XC4000 "QAM/8VSB single chip tuner"
 *
 *  Copyright (c) 2007 Xceive Corporation
 *  Copyright (c) 2007 Steven Toth <stoth@linuxtv.org>
 *  Copyright (c) 2009 Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 *  Copyright (c) 2009 Davide Ferri <d.ferri@zero11.it>
 *  Copyright (c) 2010 Istvan Varga <istvan_v@mailbox.hu>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/delay.h>
#समावेश <linux/dvb/frontend.h>
#समावेश <linux/i2c.h>
#समावेश <linux/mutex.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <media/dvb_frontend.h>

#समावेश "xc4000.h"
#समावेश "tuner-i2c.h"
#समावेश "tuner-xc2028-types.h"

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "Debugging level (0 to 2, default: 0 (off)).");

अटल पूर्णांक no_घातeroff;
module_param(no_घातeroff, पूर्णांक, 0644);
MODULE_PARM_DESC(no_घातeroff, "Power management (1: disabled, 2: enabled, 0 (default): use device-specific default mode).");

अटल पूर्णांक audio_std;
module_param(audio_std, पूर्णांक, 0644);
MODULE_PARM_DESC(audio_std, "Audio standard. XC4000 audio decoder explicitly needs to know what audio standard is needed for some video standards with audio A2 or NICAM. The valid settings are a sum of:\n"
	" 1: use NICAM/B or A2/B instead of NICAM/A or A2/A\n"
	" 2: use A2 instead of NICAM or BTSC\n"
	" 4: use SECAM/K3 instead of K1\n"
	" 8: use PAL-D/K audio for SECAM-D/K\n"
	"16: use FM radio input 1 instead of input 2\n"
	"32: use mono audio (the lower three bits are ignored)");

अटल अक्षर firmware_name[30];
module_param_string(firmware_name, firmware_name, माप(firmware_name), 0);
MODULE_PARM_DESC(firmware_name, "Firmware file name. Allows overriding the default firmware name.");

अटल DEFINE_MUTEX(xc4000_list_mutex);
अटल LIST_HEAD(hybrid_tuner_instance_list);

#घोषणा dprपूर्णांकk(level, fmt, arg...) अगर (debug >= level) \
	prपूर्णांकk(KERN_INFO "%s: " fmt, "xc4000", ## arg)

/* काष्ठा क्रम storing firmware table */
काष्ठा firmware_description अणु
	अचिन्हित पूर्णांक  type;
	v4l2_std_id   id;
	__u16         पूर्णांक_freq;
	अचिन्हित अक्षर *ptr;
	अचिन्हित पूर्णांक  size;
पूर्ण;

काष्ठा firmware_properties अणु
	अचिन्हित पूर्णांक	type;
	v4l2_std_id	id;
	v4l2_std_id	std_req;
	__u16		पूर्णांक_freq;
	अचिन्हित पूर्णांक	scode_table;
	पूर्णांक		scode_nr;
पूर्ण;

काष्ठा xc4000_priv अणु
	काष्ठा tuner_i2c_props i2c_props;
	काष्ठा list_head hybrid_tuner_instance_list;
	काष्ठा firmware_description *firm;
	पूर्णांक	firm_size;
	u32	अगर_khz;
	u32	freq_hz, freq_offset;
	u32	bandwidth;
	u8	video_standard;
	u8	rf_mode;
	u8	शेष_pm;
	u8	dvb_amplitude;
	u8	set_smoothedcvbs;
	u8	ignore_i2c_ग_लिखो_errors;
	__u16	firm_version;
	काष्ठा firmware_properties cur_fw;
	__u16	hwmodel;
	__u16	hwvers;
	काष्ठा mutex	lock;
पूर्ण;

#घोषणा XC4000_AUDIO_STD_B		 1
#घोषणा XC4000_AUDIO_STD_A2		 2
#घोषणा XC4000_AUDIO_STD_K3		 4
#घोषणा XC4000_AUDIO_STD_L		 8
#घोषणा XC4000_AUDIO_STD_INPUT1		16
#घोषणा XC4000_AUDIO_STD_MONO		32

#घोषणा XC4000_DEFAULT_FIRMWARE "dvb-fe-xc4000-1.4.fw"
#घोषणा XC4000_DEFAULT_FIRMWARE_NEW "dvb-fe-xc4000-1.4.1.fw"

/* Misc Defines */
#घोषणा MAX_TV_STANDARD			24
#घोषणा XC_MAX_I2C_WRITE_LENGTH		64
#घोषणा XC_POWERED_DOWN			0x80000000U

/* Signal Types */
#घोषणा XC_RF_MODE_AIR			0
#घोषणा XC_RF_MODE_CABLE		1

/* Product id */
#घोषणा XC_PRODUCT_ID_FW_NOT_LOADED	0x2000
#घोषणा XC_PRODUCT_ID_XC4000		0x0FA0
#घोषणा XC_PRODUCT_ID_XC4100		0x1004

/* Registers (Write-only) */
#घोषणा XREG_INIT         0x00
#घोषणा XREG_VIDEO_MODE   0x01
#घोषणा XREG_AUDIO_MODE   0x02
#घोषणा XREG_RF_FREQ      0x03
#घोषणा XREG_D_CODE       0x04
#घोषणा XREG_सूचीECTSITTING_MODE 0x05
#घोषणा XREG_SEEK_MODE    0x06
#घोषणा XREG_POWER_DOWN   0x08
#घोषणा XREG_SIGNALSOURCE 0x0A
#घोषणा XREG_SMOOTHEDCVBS 0x0E
#घोषणा XREG_AMPLITUDE    0x10

/* Registers (Read-only) */
#घोषणा XREG_ADC_ENV      0x00
#घोषणा XREG_QUALITY      0x01
#घोषणा XREG_FRAME_LINES  0x02
#घोषणा XREG_HSYNC_FREQ   0x03
#घोषणा XREG_LOCK         0x04
#घोषणा XREG_FREQ_ERROR   0x05
#घोषणा XREG_SNR          0x06
#घोषणा XREG_VERSION      0x07
#घोषणा XREG_PRODUCT_ID   0x08
#घोषणा XREG_SIGNAL_LEVEL 0x0A
#घोषणा XREG_NOISE_LEVEL  0x0B

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
	स्थिर अक्षर  *Name;
	u16	    audio_mode;
	u16	    video_mode;
	u16	    पूर्णांक_freq;
पूर्ण;

/* Tuner standards */
#घोषणा XC4000_MN_NTSC_PAL_BTSC		0
#घोषणा XC4000_MN_NTSC_PAL_A2		1
#घोषणा XC4000_MN_NTSC_PAL_EIAJ		2
#घोषणा XC4000_MN_NTSC_PAL_Mono		3
#घोषणा XC4000_BG_PAL_A2		4
#घोषणा XC4000_BG_PAL_NICAM		5
#घोषणा XC4000_BG_PAL_MONO		6
#घोषणा XC4000_I_PAL_NICAM		7
#घोषणा XC4000_I_PAL_NICAM_MONO		8
#घोषणा XC4000_DK_PAL_A2		9
#घोषणा XC4000_DK_PAL_NICAM		10
#घोषणा XC4000_DK_PAL_MONO		11
#घोषणा XC4000_DK_SECAM_A2DK1		12
#घोषणा XC4000_DK_SECAM_A2LDK3		13
#घोषणा XC4000_DK_SECAM_A2MONO		14
#घोषणा XC4000_DK_SECAM_NICAM		15
#घोषणा XC4000_L_SECAM_NICAM		16
#घोषणा XC4000_LC_SECAM_NICAM		17
#घोषणा XC4000_DTV6			18
#घोषणा XC4000_DTV8			19
#घोषणा XC4000_DTV7_8			20
#घोषणा XC4000_DTV7			21
#घोषणा XC4000_FM_Radio_INPUT2		22
#घोषणा XC4000_FM_Radio_INPUT1		23

अटल काष्ठा XC_TV_STANDARD xc4000_standard[MAX_TV_STANDARD] = अणु
	अणु"M/N-NTSC/PAL-BTSC",	0x0000, 0x80A0, 4500पूर्ण,
	अणु"M/N-NTSC/PAL-A2",	0x0000, 0x80A0, 4600पूर्ण,
	अणु"M/N-NTSC/PAL-EIAJ",	0x0040, 0x80A0, 4500पूर्ण,
	अणु"M/N-NTSC/PAL-Mono",	0x0078, 0x80A0, 4500पूर्ण,
	अणु"B/G-PAL-A2",		0x0000, 0x8159, 5640पूर्ण,
	अणु"B/G-PAL-NICAM",	0x0004, 0x8159, 5740पूर्ण,
	अणु"B/G-PAL-MONO",	0x0078, 0x8159, 5500पूर्ण,
	अणु"I-PAL-NICAM",		0x0080, 0x8049, 6240पूर्ण,
	अणु"I-PAL-NICAM-MONO",	0x0078, 0x8049, 6000पूर्ण,
	अणु"D/K-PAL-A2",		0x0000, 0x8049, 6380पूर्ण,
	अणु"D/K-PAL-NICAM",	0x0080, 0x8049, 6200पूर्ण,
	अणु"D/K-PAL-MONO",	0x0078, 0x8049, 6500पूर्ण,
	अणु"D/K-SECAM-A2 DK1",	0x0000, 0x8049, 6340पूर्ण,
	अणु"D/K-SECAM-A2 L/DK3",	0x0000, 0x8049, 6000पूर्ण,
	अणु"D/K-SECAM-A2 MONO",	0x0078, 0x8049, 6500पूर्ण,
	अणु"D/K-SECAM-NICAM",	0x0080, 0x8049, 6200पूर्ण,
	अणु"L-SECAM-NICAM",	0x8080, 0x0009, 6200पूर्ण,
	अणु"L'-SECAM-NICAM",	0x8080, 0x4009, 6200पूर्ण,
	अणु"DTV6",		0x00C0, 0x8002,    0पूर्ण,
	अणु"DTV8",		0x00C0, 0x800B,    0पूर्ण,
	अणु"DTV7/8",		0x00C0, 0x801B,    0पूर्ण,
	अणु"DTV7",		0x00C0, 0x8007,    0पूर्ण,
	अणु"FM Radio-INPUT2",	0x0008, 0x9800, 10700पूर्ण,
	अणु"FM Radio-INPUT1",	0x0008, 0x9000, 10700पूर्ण
पूर्ण;

अटल पूर्णांक xc4000_पढ़ोreg(काष्ठा xc4000_priv *priv, u16 reg, u16 *val);
अटल पूर्णांक xc4000_tuner_reset(काष्ठा dvb_frontend *fe);
अटल व्योम xc_debug_dump(काष्ठा xc4000_priv *priv);

अटल पूर्णांक xc_send_i2c_data(काष्ठा xc4000_priv *priv, u8 *buf, पूर्णांक len)
अणु
	काष्ठा i2c_msg msg = अणु .addr = priv->i2c_props.addr,
			       .flags = 0, .buf = buf, .len = len पूर्ण;
	अगर (i2c_transfer(priv->i2c_props.adap, &msg, 1) != 1) अणु
		अगर (priv->ignore_i2c_ग_लिखो_errors == 0) अणु
			prपूर्णांकk(KERN_ERR "xc4000: I2C write failed (len=%i)\n",
			       len);
			अगर (len == 4) अणु
				prपूर्णांकk(KERN_ERR "bytes %*ph\n", 4, buf);
			पूर्ण
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xc4000_tuner_reset(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	पूर्णांक ret;

	dprपूर्णांकk(1, "%s()\n", __func__);

	अगर (fe->callback) अणु
		ret = fe->callback(((fe->dvb) && (fe->dvb->priv)) ?
					   fe->dvb->priv :
					   priv->i2c_props.adap->algo_data,
					   DVB_FRONTEND_COMPONENT_TUNER,
					   XC4000_TUNER_RESET, 0);
		अगर (ret) अणु
			prपूर्णांकk(KERN_ERR "xc4000: reset failed\n");
			वापस -EREMOTEIO;
		पूर्ण
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_ERR "xc4000: no tuner reset callback function, fatal\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक xc_ग_लिखो_reg(काष्ठा xc4000_priv *priv, u16 regAddr, u16 i2cData)
अणु
	u8 buf[4];
	पूर्णांक result;

	buf[0] = (regAddr >> 8) & 0xFF;
	buf[1] = regAddr & 0xFF;
	buf[2] = (i2cData >> 8) & 0xFF;
	buf[3] = i2cData & 0xFF;
	result = xc_send_i2c_data(priv, buf, 4);

	वापस result;
पूर्ण

अटल पूर्णांक xc_load_i2c_sequence(काष्ठा dvb_frontend *fe, स्थिर u8 *i2c_sequence)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;

	पूर्णांक i, nbytes_to_send, result;
	अचिन्हित पूर्णांक len, pos, index;
	u8 buf[XC_MAX_I2C_WRITE_LENGTH];

	index = 0;
	जबतक ((i2c_sequence[index] != 0xFF) ||
		(i2c_sequence[index + 1] != 0xFF)) अणु
		len = i2c_sequence[index] * 256 + i2c_sequence[index+1];
		अगर (len == 0x0000) अणु
			/* RESET command */
			/* NOTE: this is ignored, as the reset callback was */
			/* alपढ़ोy called by check_firmware() */
			index += 2;
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

अटल पूर्णांक xc_set_tv_standard(काष्ठा xc4000_priv *priv,
	u16 video_mode, u16 audio_mode)
अणु
	पूर्णांक ret;
	dprपूर्णांकk(1, "%s(0x%04x,0x%04x)\n", __func__, video_mode, audio_mode);
	dprपूर्णांकk(1, "%s() Standard = %s\n",
		__func__,
		xc4000_standard[priv->video_standard].Name);

	/* Don't complain when the request fails because of i2c stretching */
	priv->ignore_i2c_ग_लिखो_errors = 1;

	ret = xc_ग_लिखो_reg(priv, XREG_VIDEO_MODE, video_mode);
	अगर (ret == 0)
		ret = xc_ग_लिखो_reg(priv, XREG_AUDIO_MODE, audio_mode);

	priv->ignore_i2c_ग_लिखो_errors = 0;

	वापस ret;
पूर्ण

अटल पूर्णांक xc_set_संकेत_source(काष्ठा xc4000_priv *priv, u16 rf_mode)
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

अटल स्थिर काष्ठा dvb_tuner_ops xc4000_tuner_ops;

अटल पूर्णांक xc_set_rf_frequency(काष्ठा xc4000_priv *priv, u32 freq_hz)
अणु
	u16 freq_code;

	dprपूर्णांकk(1, "%s(%u)\n", __func__, freq_hz);

	अगर ((freq_hz > xc4000_tuner_ops.info.frequency_max_hz) ||
	    (freq_hz < xc4000_tuner_ops.info.frequency_min_hz))
		वापस -EINVAL;

	freq_code = (u16)(freq_hz / 15625);

	/* WAS: Starting in firmware version 1.1.44, Xceive recommends using the
	   FINERFREQ क्रम all normal tuning (the करोc indicates reg 0x03 should
	   only be used क्रम fast scanning क्रम channel lock) */
	/* WAS: XREG_FINERFREQ */
	वापस xc_ग_लिखो_reg(priv, XREG_RF_FREQ, freq_code);
पूर्ण

अटल पूर्णांक xc_get_adc_envelope(काष्ठा xc4000_priv *priv, u16 *adc_envelope)
अणु
	वापस xc4000_पढ़ोreg(priv, XREG_ADC_ENV, adc_envelope);
पूर्ण

अटल पूर्णांक xc_get_frequency_error(काष्ठा xc4000_priv *priv, u32 *freq_error_hz)
अणु
	पूर्णांक result;
	u16 regData;
	u32 पंचांगp;

	result = xc4000_पढ़ोreg(priv, XREG_FREQ_ERROR, &regData);
	अगर (result != 0)
		वापस result;

	पंचांगp = (u32)regData & 0xFFFFU;
	पंचांगp = (पंचांगp < 0x8000U ? पंचांगp : 0x10000U - पंचांगp);
	(*freq_error_hz) = पंचांगp * 15625;
	वापस result;
पूर्ण

अटल पूर्णांक xc_get_lock_status(काष्ठा xc4000_priv *priv, u16 *lock_status)
अणु
	वापस xc4000_पढ़ोreg(priv, XREG_LOCK, lock_status);
पूर्ण

अटल पूर्णांक xc_get_version(काष्ठा xc4000_priv *priv,
	u8 *hw_majorversion, u8 *hw_minorversion,
	u8 *fw_majorversion, u8 *fw_minorversion)
अणु
	u16 data;
	पूर्णांक result;

	result = xc4000_पढ़ोreg(priv, XREG_VERSION, &data);
	अगर (result != 0)
		वापस result;

	(*hw_majorversion) = (data >> 12) & 0x0F;
	(*hw_minorversion) = (data >>  8) & 0x0F;
	(*fw_majorversion) = (data >>  4) & 0x0F;
	(*fw_minorversion) = data & 0x0F;

	वापस 0;
पूर्ण

अटल पूर्णांक xc_get_hsync_freq(काष्ठा xc4000_priv *priv, u32 *hsync_freq_hz)
अणु
	u16 regData;
	पूर्णांक result;

	result = xc4000_पढ़ोreg(priv, XREG_HSYNC_FREQ, &regData);
	अगर (result != 0)
		वापस result;

	(*hsync_freq_hz) = ((regData & 0x0fff) * 763)/100;
	वापस result;
पूर्ण

अटल पूर्णांक xc_get_frame_lines(काष्ठा xc4000_priv *priv, u16 *frame_lines)
अणु
	वापस xc4000_पढ़ोreg(priv, XREG_FRAME_LINES, frame_lines);
पूर्ण

अटल पूर्णांक xc_get_quality(काष्ठा xc4000_priv *priv, u16 *quality)
अणु
	वापस xc4000_पढ़ोreg(priv, XREG_QUALITY, quality);
पूर्ण

अटल पूर्णांक xc_get_संकेत_level(काष्ठा xc4000_priv *priv, u16 *संकेत)
अणु
	वापस xc4000_पढ़ोreg(priv, XREG_SIGNAL_LEVEL, संकेत);
पूर्ण

अटल पूर्णांक xc_get_noise_level(काष्ठा xc4000_priv *priv, u16 *noise)
अणु
	वापस xc4000_पढ़ोreg(priv, XREG_NOISE_LEVEL, noise);
पूर्ण

अटल u16 xc_रुको_क्रम_lock(काष्ठा xc4000_priv *priv)
अणु
	u16	lock_state = 0;
	पूर्णांक	watchकरोg_count = 40;

	जबतक ((lock_state == 0) && (watchकरोg_count > 0)) अणु
		xc_get_lock_status(priv, &lock_state);
		अगर (lock_state != 1) अणु
			msleep(5);
			watchकरोg_count--;
		पूर्ण
	पूर्ण
	वापस lock_state;
पूर्ण

अटल पूर्णांक xc_tune_channel(काष्ठा xc4000_priv *priv, u32 freq_hz)
अणु
	पूर्णांक	found = 1;
	पूर्णांक	result;

	dprपूर्णांकk(1, "%s(%u)\n", __func__, freq_hz);

	/* Don't complain when the request fails because of i2c stretching */
	priv->ignore_i2c_ग_लिखो_errors = 1;
	result = xc_set_rf_frequency(priv, freq_hz);
	priv->ignore_i2c_ग_लिखो_errors = 0;

	अगर (result != 0)
		वापस 0;

	/* रुको क्रम lock only in analog TV mode */
	अगर ((priv->cur_fw.type & (FM | DTV6 | DTV7 | DTV78 | DTV8)) == 0) अणु
		अगर (xc_रुको_क्रम_lock(priv) != 1)
			found = 0;
	पूर्ण

	/* Wait क्रम stats to stabilize.
	 * Frame Lines needs two frame बार after initial lock
	 * beक्रमe it is valid.
	 */
	msleep(debug ? 100 : 10);

	अगर (debug)
		xc_debug_dump(priv);

	वापस found;
पूर्ण

अटल पूर्णांक xc4000_पढ़ोreg(काष्ठा xc4000_priv *priv, u16 reg, u16 *val)
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
		prपूर्णांकk(KERN_ERR "xc4000: I2C read failed\n");
		वापस -EREMOTEIO;
	पूर्ण

	*val = (bval[0] << 8) | bval[1];
	वापस 0;
पूर्ण

#घोषणा dump_firm_type(t)	dump_firm_type_and_पूर्णांक_freq(t, 0)
अटल व्योम dump_firm_type_and_पूर्णांक_freq(अचिन्हित पूर्णांक type, u16 पूर्णांक_freq)
अणु
	अगर (type & BASE)
		prपूर्णांकk(KERN_CONT "BASE ");
	अगर (type & INIT1)
		prपूर्णांकk(KERN_CONT "INIT1 ");
	अगर (type & F8MHZ)
		prपूर्णांकk(KERN_CONT "F8MHZ ");
	अगर (type & MTS)
		prपूर्णांकk(KERN_CONT "MTS ");
	अगर (type & D2620)
		prपूर्णांकk(KERN_CONT "D2620 ");
	अगर (type & D2633)
		prपूर्णांकk(KERN_CONT "D2633 ");
	अगर (type & DTV6)
		prपूर्णांकk(KERN_CONT "DTV6 ");
	अगर (type & QAM)
		prपूर्णांकk(KERN_CONT "QAM ");
	अगर (type & DTV7)
		prपूर्णांकk(KERN_CONT "DTV7 ");
	अगर (type & DTV78)
		prपूर्णांकk(KERN_CONT "DTV78 ");
	अगर (type & DTV8)
		prपूर्णांकk(KERN_CONT "DTV8 ");
	अगर (type & FM)
		prपूर्णांकk(KERN_CONT "FM ");
	अगर (type & INPUT1)
		prपूर्णांकk(KERN_CONT "INPUT1 ");
	अगर (type & LCD)
		prपूर्णांकk(KERN_CONT "LCD ");
	अगर (type & NOGD)
		prपूर्णांकk(KERN_CONT "NOGD ");
	अगर (type & MONO)
		prपूर्णांकk(KERN_CONT "MONO ");
	अगर (type & ATSC)
		prपूर्णांकk(KERN_CONT "ATSC ");
	अगर (type & IF)
		prपूर्णांकk(KERN_CONT "IF ");
	अगर (type & LG60)
		prपूर्णांकk(KERN_CONT "LG60 ");
	अगर (type & ATI638)
		prपूर्णांकk(KERN_CONT "ATI638 ");
	अगर (type & OREN538)
		prपूर्णांकk(KERN_CONT "OREN538 ");
	अगर (type & OREN36)
		prपूर्णांकk(KERN_CONT "OREN36 ");
	अगर (type & TOYOTA388)
		prपूर्णांकk(KERN_CONT "TOYOTA388 ");
	अगर (type & TOYOTA794)
		prपूर्णांकk(KERN_CONT "TOYOTA794 ");
	अगर (type & DIBCOM52)
		prपूर्णांकk(KERN_CONT "DIBCOM52 ");
	अगर (type & ZARLINK456)
		prपूर्णांकk(KERN_CONT "ZARLINK456 ");
	अगर (type & CHINA)
		prपूर्णांकk(KERN_CONT "CHINA ");
	अगर (type & F6MHZ)
		prपूर्णांकk(KERN_CONT "F6MHZ ");
	अगर (type & INPUT2)
		prपूर्णांकk(KERN_CONT "INPUT2 ");
	अगर (type & SCODE)
		prपूर्णांकk(KERN_CONT "SCODE ");
	अगर (type & HAS_IF)
		prपूर्णांकk(KERN_CONT "HAS_IF_%d ", पूर्णांक_freq);
पूर्ण

अटल पूर्णांक seek_firmware(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			 v4l2_std_id *id)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	पूर्णांक		i, best_i = -1;
	अचिन्हित पूर्णांक	best_nr_dअगरfs = 255U;

	अगर (!priv->firm) अणु
		prपूर्णांकk(KERN_ERR "Error! firmware not loaded\n");
		वापस -EINVAL;
	पूर्ण

	अगर (((type & ~SCODE) == 0) && (*id == 0))
		*id = V4L2_STD_PAL;

	/* Seek क्रम generic video standard match */
	क्रम (i = 0; i < priv->firm_size; i++) अणु
		v4l2_std_id	id_dअगरf_mask =
			(priv->firm[i].id ^ (*id)) & (*id);
		अचिन्हित पूर्णांक	type_dअगरf_mask =
			(priv->firm[i].type ^ type)
			& (BASE_TYPES | DTV_TYPES | LCD | NOGD | MONO | SCODE);
		अचिन्हित पूर्णांक	nr_dअगरfs;

		अगर (type_dअगरf_mask
		    & (BASE | INIT1 | FM | DTV6 | DTV7 | DTV78 | DTV8 | SCODE))
			जारी;

		nr_dअगरfs = hweight64(id_dअगरf_mask) + hweight32(type_dअगरf_mask);
		अगर (!nr_dअगरfs)	/* Supports all the requested standards */
			जाओ found;

		अगर (nr_dअगरfs < best_nr_dअगरfs) अणु
			best_nr_dअगरfs = nr_dअगरfs;
			best_i = i;
		पूर्ण
	पूर्ण

	/* FIXME: Would make sense to seek क्रम type "hint" match ? */
	अगर (best_i < 0) अणु
		i = -ENOENT;
		जाओ ret;
	पूर्ण

	अगर (best_nr_dअगरfs > 0U) अणु
		prपूर्णांकk(KERN_WARNING
		       "Selecting best matching firmware (%u bits differ) for type=(%x), id %016llx:\n",
		       best_nr_dअगरfs, type, (अचिन्हित दीर्घ दीर्घ)*id);
		i = best_i;
	पूर्ण

found:
	*id = priv->firm[i].id;

ret:
	अगर (debug) अणु
		prपूर्णांकk(KERN_DEBUG "%s firmware for type=",
		       (i < 0) ? "Can't find" : "Found");
		dump_firm_type(type);
		prपूर्णांकk(KERN_DEBUG "(%x), id %016llx.\n", type, (अचिन्हित दीर्घ दीर्घ)*id);
	पूर्ण
	वापस i;
पूर्ण

अटल पूर्णांक load_firmware(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			 v4l2_std_id *id)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	पूर्णांक                pos, rc;
	अचिन्हित अक्षर      *p;

	pos = seek_firmware(fe, type, id);
	अगर (pos < 0)
		वापस pos;

	p = priv->firm[pos].ptr;

	/* Don't complain when the request fails because of i2c stretching */
	priv->ignore_i2c_ग_लिखो_errors = 1;

	rc = xc_load_i2c_sequence(fe, p);

	priv->ignore_i2c_ग_लिखो_errors = 0;

	वापस rc;
पूर्ण

अटल पूर्णांक xc4000_fwupload(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	स्थिर काष्ठा firmware *fw   = शून्य;
	स्थिर अचिन्हित अक्षर   *p, *endp;
	पूर्णांक                   rc = 0;
	पूर्णांक		      n, n_array;
	अक्षर		      name[33];
	स्थिर अक्षर	      *fname;

	अगर (firmware_name[0] != '\0') अणु
		fname = firmware_name;

		dprपूर्णांकk(1, "Reading custom firmware %s\n", fname);
		rc = request_firmware(&fw, fname,
				      priv->i2c_props.adap->dev.parent);
	पूर्ण अन्यथा अणु
		fname = XC4000_DEFAULT_FIRMWARE_NEW;
		dprपूर्णांकk(1, "Trying to read firmware %s\n", fname);
		rc = request_firmware(&fw, fname,
				      priv->i2c_props.adap->dev.parent);
		अगर (rc == -ENOENT) अणु
			fname = XC4000_DEFAULT_FIRMWARE;
			dprपूर्णांकk(1, "Trying to read firmware %s\n", fname);
			rc = request_firmware(&fw, fname,
					      priv->i2c_props.adap->dev.parent);
		पूर्ण
	पूर्ण

	अगर (rc < 0) अणु
		अगर (rc == -ENOENT)
			prपूर्णांकk(KERN_ERR "Error: firmware %s not found.\n", fname);
		अन्यथा
			prपूर्णांकk(KERN_ERR "Error %d while requesting firmware %s\n",
			       rc, fname);

		वापस rc;
	पूर्ण
	dprपूर्णांकk(1, "Loading Firmware: %s\n", fname);

	p = fw->data;
	endp = p + fw->size;

	अगर (fw->size < माप(name) - 1 + 2 + 2) अणु
		prपूर्णांकk(KERN_ERR "Error: firmware file %s has invalid size!\n",
		       fname);
		जाओ corrupt;
	पूर्ण

	स_नकल(name, p, माप(name) - 1);
	name[माप(name) - 1] = '\0';
	p += माप(name) - 1;

	priv->firm_version = get_unaligned_le16(p);
	p += 2;

	n_array = get_unaligned_le16(p);
	p += 2;

	dprपूर्णांकk(1, "Loading %d firmware images from %s, type: %s, ver %d.%d\n",
		n_array, fname, name,
		priv->firm_version >> 8, priv->firm_version & 0xff);

	priv->firm = kसुस्मृति(n_array, माप(*priv->firm), GFP_KERNEL);
	अगर (priv->firm == शून्य) अणु
		prपूर्णांकk(KERN_ERR "Not enough memory to load firmware file.\n");
		rc = -ENOMEM;
		जाओ करोne;
	पूर्ण
	priv->firm_size = n_array;

	n = -1;
	जबतक (p < endp) अणु
		__u32 type, size;
		v4l2_std_id id;
		__u16 पूर्णांक_freq = 0;

		n++;
		अगर (n >= n_array) अणु
			prपूर्णांकk(KERN_ERR "More firmware images in file than were expected!\n");
			जाओ corrupt;
		पूर्ण

		/* Checks अगर there's enough bytes to पढ़ो */
		अगर (endp - p < माप(type) + माप(id) + माप(size))
			जाओ header;

		type = get_unaligned_le32(p);
		p += माप(type);

		id = get_unaligned_le64(p);
		p += माप(id);

		अगर (type & HAS_IF) अणु
			पूर्णांक_freq = get_unaligned_le16(p);
			p += माप(पूर्णांक_freq);
			अगर (endp - p < माप(size))
				जाओ header;
		पूर्ण

		size = get_unaligned_le32(p);
		p += माप(size);

		अगर (!size || size > endp - p) अणु
			prपूर्णांकk(KERN_ERR "Firmware type (%x), id %llx is corrupted (size=%zd, expected %d)\n",
			       type, (अचिन्हित दीर्घ दीर्घ)id,
			       endp - p, size);
			जाओ corrupt;
		पूर्ण

		priv->firm[n].ptr = kmemdup(p, size, GFP_KERNEL);
		अगर (priv->firm[n].ptr == शून्य) अणु
			prपूर्णांकk(KERN_ERR "Not enough memory to load firmware file.\n");
			rc = -ENOMEM;
			जाओ करोne;
		पूर्ण

		अगर (debug) अणु
			prपूर्णांकk(KERN_DEBUG "Reading firmware type ");
			dump_firm_type_and_पूर्णांक_freq(type, पूर्णांक_freq);
			prपूर्णांकk(KERN_DEBUG "(%x), id %llx, size=%d.\n",
			       type, (अचिन्हित दीर्घ दीर्घ)id, size);
		पूर्ण

		priv->firm[n].type = type;
		priv->firm[n].id   = id;
		priv->firm[n].size = size;
		priv->firm[n].पूर्णांक_freq = पूर्णांक_freq;

		p += size;
	पूर्ण

	अगर (n + 1 != priv->firm_size) अणु
		prपूर्णांकk(KERN_ERR "Firmware file is incomplete!\n");
		जाओ corrupt;
	पूर्ण

	जाओ करोne;

header:
	prपूर्णांकk(KERN_ERR "Firmware header is incomplete!\n");
corrupt:
	rc = -EINVAL;
	prपूर्णांकk(KERN_ERR "Error: firmware file is corrupted!\n");

करोne:
	release_firmware(fw);
	अगर (rc == 0)
		dprपूर्णांकk(1, "Firmware files loaded.\n");

	वापस rc;
पूर्ण

अटल पूर्णांक load_scode(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			 v4l2_std_id *id, __u16 पूर्णांक_freq, पूर्णांक scode)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	पूर्णांक		pos, rc;
	अचिन्हित अक्षर	*p;
	u8		scode_buf[13];
	u8		indirect_mode[5];

	dprपूर्णांकk(1, "%s called int_freq=%d\n", __func__, पूर्णांक_freq);

	अगर (!पूर्णांक_freq) अणु
		pos = seek_firmware(fe, type, id);
		अगर (pos < 0)
			वापस pos;
	पूर्ण अन्यथा अणु
		क्रम (pos = 0; pos < priv->firm_size; pos++) अणु
			अगर ((priv->firm[pos].पूर्णांक_freq == पूर्णांक_freq) &&
			    (priv->firm[pos].type & HAS_IF))
				अवरोध;
		पूर्ण
		अगर (pos == priv->firm_size)
			वापस -ENOENT;
	पूर्ण

	p = priv->firm[pos].ptr;

	अगर (priv->firm[pos].size != 12 * 16 || scode >= 16)
		वापस -EINVAL;
	p += 12 * scode;

	अगर (debug) अणु
		tuner_info("Loading SCODE for type=");
		dump_firm_type_and_पूर्णांक_freq(priv->firm[pos].type,
					    priv->firm[pos].पूर्णांक_freq);
		prपूर्णांकk(KERN_CONT "(%x), id %016llx.\n", priv->firm[pos].type,
		       (अचिन्हित दीर्घ दीर्घ)*id);
	पूर्ण

	scode_buf[0] = 0x00;
	स_नकल(&scode_buf[1], p, 12);

	/* Enter direct-mode */
	rc = xc_ग_लिखो_reg(priv, XREG_सूचीECTSITTING_MODE, 0);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "failed to put device into direct mode!\n");
		वापस -EIO;
	पूर्ण

	rc = xc_send_i2c_data(priv, scode_buf, 13);
	अगर (rc != 0) अणु
		/* Even अगर the send failed, make sure we set back to indirect
		   mode */
		prपूर्णांकk(KERN_ERR "Failed to set scode %d\n", rc);
	पूर्ण

	/* Switch back to indirect-mode */
	स_रखो(indirect_mode, 0, माप(indirect_mode));
	indirect_mode[4] = 0x88;
	xc_send_i2c_data(priv, indirect_mode, माप(indirect_mode));
	msleep(10);

	वापस 0;
पूर्ण

अटल पूर्णांक check_firmware(काष्ठा dvb_frontend *fe, अचिन्हित पूर्णांक type,
			  v4l2_std_id std, __u16 पूर्णांक_freq)
अणु
	काष्ठा xc4000_priv         *priv = fe->tuner_priv;
	काष्ठा firmware_properties new_fw;
	पूर्णांक			   rc = 0, is_retry = 0;
	u16			   hwmodel;
	v4l2_std_id		   std0;
	u8			   hw_major = 0, hw_minor = 0, fw_major = 0, fw_minor = 0;

	dprपूर्णांकk(1, "%s called\n", __func__);

	अगर (!priv->firm) अणु
		rc = xc4000_fwupload(fe);
		अगर (rc < 0)
			वापस rc;
	पूर्ण

retry:
	new_fw.type = type;
	new_fw.id = std;
	new_fw.std_req = std;
	new_fw.scode_table = SCODE;
	new_fw.scode_nr = 0;
	new_fw.पूर्णांक_freq = पूर्णांक_freq;

	dprपूर्णांकk(1, "checking firmware, user requested type=");
	अगर (debug) अणु
		dump_firm_type(new_fw.type);
		prपूर्णांकk(KERN_CONT "(%x), id %016llx, ", new_fw.type,
		       (अचिन्हित दीर्घ दीर्घ)new_fw.std_req);
		अगर (!पूर्णांक_freq)
			prपूर्णांकk(KERN_CONT "scode_tbl ");
		अन्यथा
			prपूर्णांकk(KERN_CONT "int_freq %d, ", new_fw.पूर्णांक_freq);
		prपूर्णांकk(KERN_CONT "scode_nr %d\n", new_fw.scode_nr);
	पूर्ण

	/* No need to reload base firmware अगर it matches */
	अगर (priv->cur_fw.type & BASE) अणु
		dprपूर्णांकk(1, "BASE firmware not changed.\n");
		जाओ skip_base;
	पूर्ण

	/* Updating BASE - क्रमget about all currently loaded firmware */
	स_रखो(&priv->cur_fw, 0, माप(priv->cur_fw));

	/* Reset is needed beक्रमe loading firmware */
	rc = xc4000_tuner_reset(fe);
	अगर (rc < 0)
		जाओ fail;

	/* BASE firmwares are all std0 */
	std0 = 0;
	rc = load_firmware(fe, BASE, &std0);
	अगर (rc < 0) अणु
		prपूर्णांकk(KERN_ERR "Error %d while loading base firmware\n", rc);
		जाओ fail;
	पूर्ण

	/* Load INIT1, अगर needed */
	dprपूर्णांकk(1, "Load init1 firmware, if exists\n");

	rc = load_firmware(fe, BASE | INIT1, &std0);
	अगर (rc == -ENOENT)
		rc = load_firmware(fe, BASE | INIT1, &std0);
	अगर (rc < 0 && rc != -ENOENT) अणु
		tuner_err("Error %d while loading init1 firmware\n",
			  rc);
		जाओ fail;
	पूर्ण

skip_base:
	/*
	 * No need to reload standard specअगरic firmware अगर base firmware
	 * was not reloaded and requested video standards have not changed.
	 */
	अगर (priv->cur_fw.type == (BASE | new_fw.type) &&
	    priv->cur_fw.std_req == std) अणु
		dprपूर्णांकk(1, "Std-specific firmware already loaded.\n");
		जाओ skip_std_specअगरic;
	पूर्ण

	/* Reloading std-specअगरic firmware क्रमces a SCODE update */
	priv->cur_fw.scode_table = 0;

	/* Load the standard firmware */
	rc = load_firmware(fe, new_fw.type, &new_fw.id);

	अगर (rc < 0)
		जाओ fail;

skip_std_specअगरic:
	अगर (priv->cur_fw.scode_table == new_fw.scode_table &&
	    priv->cur_fw.scode_nr == new_fw.scode_nr) अणु
		dprपूर्णांकk(1, "SCODE firmware already loaded.\n");
		जाओ check_device;
	पूर्ण

	/* Load SCODE firmware, अगर exists */
	rc = load_scode(fe, new_fw.type | new_fw.scode_table, &new_fw.id,
			new_fw.पूर्णांक_freq, new_fw.scode_nr);
	अगर (rc != 0)
		dprपूर्णांकk(1, "load scode failed %d\n", rc);

check_device:
	अगर (xc4000_पढ़ोreg(priv, XREG_PRODUCT_ID, &hwmodel) < 0) अणु
		prपूर्णांकk(KERN_ERR "Unable to read tuner registers.\n");
		जाओ fail;
	पूर्ण

	अगर (xc_get_version(priv, &hw_major, &hw_minor, &fw_major,
			   &fw_minor) != 0) अणु
		prपूर्णांकk(KERN_ERR "Unable to read tuner registers.\n");
		जाओ fail;
	पूर्ण

	dprपूर्णांकk(1, "Device is Xceive %d version %d.%d, firmware version %d.%d\n",
		hwmodel, hw_major, hw_minor, fw_major, fw_minor);

	/* Check firmware version against what we करोwnloaded. */
	अगर (priv->firm_version != ((fw_major << 8) | fw_minor)) अणु
		prपूर्णांकk(KERN_WARNING
		       "Incorrect readback of firmware version %d.%d.\n",
		       fw_major, fw_minor);
		जाओ fail;
	पूर्ण

	/* Check that the tuner hardware model reमुख्यs consistent over समय. */
	अगर (priv->hwmodel == 0 &&
	    (hwmodel == XC_PRODUCT_ID_XC4000 ||
	     hwmodel == XC_PRODUCT_ID_XC4100)) अणु
		priv->hwmodel = hwmodel;
		priv->hwvers = (hw_major << 8) | hw_minor;
	पूर्ण अन्यथा अगर (priv->hwmodel == 0 || priv->hwmodel != hwmodel ||
		   priv->hwvers != ((hw_major << 8) | hw_minor)) अणु
		prपूर्णांकk(KERN_WARNING
		       "Read invalid device hardware information - tuner hung?\n");
		जाओ fail;
	पूर्ण

	priv->cur_fw = new_fw;

	/*
	 * By setting BASE in cur_fw.type only after successfully loading all
	 * firmwares, we can:
	 * 1. Identअगरy that BASE firmware with type=0 has been loaded;
	 * 2. Tell whether BASE firmware was just changed the next समय through.
	 */
	priv->cur_fw.type |= BASE;

	वापस 0;

fail:
	स_रखो(&priv->cur_fw, 0, माप(priv->cur_fw));
	अगर (!is_retry) अणु
		msleep(50);
		is_retry = 1;
		dprपूर्णांकk(1, "Retrying firmware load\n");
		जाओ retry;
	पूर्ण

	अगर (rc == -ENOENT)
		rc = -EINVAL;
	वापस rc;
पूर्ण

अटल व्योम xc_debug_dump(काष्ठा xc4000_priv *priv)
अणु
	u16	adc_envelope;
	u32	freq_error_hz = 0;
	u16	lock_status;
	u32	hsync_freq_hz = 0;
	u16	frame_lines;
	u16	quality;
	u16	संकेत = 0;
	u16	noise = 0;
	u8	hw_majorversion = 0, hw_minorversion = 0;
	u8	fw_majorversion = 0, fw_minorversion = 0;

	xc_get_adc_envelope(priv, &adc_envelope);
	dprपूर्णांकk(1, "*** ADC envelope (0-1023) = %d\n", adc_envelope);

	xc_get_frequency_error(priv, &freq_error_hz);
	dprपूर्णांकk(1, "*** Frequency error = %d Hz\n", freq_error_hz);

	xc_get_lock_status(priv, &lock_status);
	dprपूर्णांकk(1, "*** Lock status (0-Wait, 1-Locked, 2-No-signal) = %d\n",
		lock_status);

	xc_get_version(priv, &hw_majorversion, &hw_minorversion,
		       &fw_majorversion, &fw_minorversion);
	dprपूर्णांकk(1, "*** HW: V%02x.%02x, FW: V%02x.%02x\n",
		hw_majorversion, hw_minorversion,
		fw_majorversion, fw_minorversion);

	अगर (priv->video_standard < XC4000_DTV6) अणु
		xc_get_hsync_freq(priv, &hsync_freq_hz);
		dprपूर्णांकk(1, "*** Horizontal sync frequency = %d Hz\n",
			hsync_freq_hz);

		xc_get_frame_lines(priv, &frame_lines);
		dprपूर्णांकk(1, "*** Frame lines = %d\n", frame_lines);
	पूर्ण

	xc_get_quality(priv, &quality);
	dprपूर्णांकk(1, "*** Quality (0:<8dB, 7:>56dB) = %d\n", quality);

	xc_get_संकेत_level(priv, &संकेत);
	dprपूर्णांकk(1, "*** Signal level = -%ddB (%d)\n", संकेत >> 8, संकेत);

	xc_get_noise_level(priv, &noise);
	dprपूर्णांकk(1, "*** Noise level = %ddB (%d)\n", noise >> 8, noise);
पूर्ण

अटल पूर्णांक xc4000_set_params(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 delsys = c->delivery_प्रणाली;
	u32 bw = c->bandwidth_hz;
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक type;
	पूर्णांक	ret = -EREMOTEIO;

	dprपूर्णांकk(1, "%s() frequency=%d (Hz)\n", __func__, c->frequency);

	mutex_lock(&priv->lock);

	चयन (delsys) अणु
	हाल SYS_ATSC:
		dprपूर्णांकk(1, "%s() VSB modulation\n", __func__);
		priv->rf_mode = XC_RF_MODE_AIR;
		priv->freq_offset = 1750000;
		priv->video_standard = XC4000_DTV6;
		type = DTV6;
		अवरोध;
	हाल SYS_DVBC_ANNEX_B:
		dprपूर्णांकk(1, "%s() QAM modulation\n", __func__);
		priv->rf_mode = XC_RF_MODE_CABLE;
		priv->freq_offset = 1750000;
		priv->video_standard = XC4000_DTV6;
		type = DTV6;
		अवरोध;
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
		dprपूर्णांकk(1, "%s() OFDM\n", __func__);
		अगर (bw == 0) अणु
			अगर (c->frequency < 400000000) अणु
				priv->freq_offset = 2250000;
			पूर्ण अन्यथा अणु
				priv->freq_offset = 2750000;
			पूर्ण
			priv->video_standard = XC4000_DTV7_8;
			type = DTV78;
		पूर्ण अन्यथा अगर (bw <= 6000000) अणु
			priv->video_standard = XC4000_DTV6;
			priv->freq_offset = 1750000;
			type = DTV6;
		पूर्ण अन्यथा अगर (bw <= 7000000) अणु
			priv->video_standard = XC4000_DTV7;
			priv->freq_offset = 2250000;
			type = DTV7;
		पूर्ण अन्यथा अणु
			priv->video_standard = XC4000_DTV8;
			priv->freq_offset = 2750000;
			type = DTV8;
		पूर्ण
		priv->rf_mode = XC_RF_MODE_AIR;
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "xc4000 delivery system not supported!\n");
		ret = -EINVAL;
		जाओ fail;
	पूर्ण

	priv->freq_hz = c->frequency - priv->freq_offset;

	dprपूर्णांकk(1, "%s() frequency=%d (compensated)\n",
		__func__, priv->freq_hz);

	/* Make sure the correct firmware type is loaded */
	अगर (check_firmware(fe, type, 0, priv->अगर_khz) != 0)
		जाओ fail;

	priv->bandwidth = c->bandwidth_hz;

	ret = xc_set_संकेत_source(priv, priv->rf_mode);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc4000: xc_set_signal_source(%d) failed\n",
		       priv->rf_mode);
		जाओ fail;
	पूर्ण अन्यथा अणु
		u16	video_mode, audio_mode;
		video_mode = xc4000_standard[priv->video_standard].video_mode;
		audio_mode = xc4000_standard[priv->video_standard].audio_mode;
		अगर (type == DTV6 && priv->firm_version != 0x0102)
			video_mode |= 0x0001;
		ret = xc_set_tv_standard(priv, video_mode, audio_mode);
		अगर (ret != 0) अणु
			prपूर्णांकk(KERN_ERR "xc4000: xc_set_tv_standard failed\n");
			/* DJH - करो not वापस when it fails... */
			/* जाओ fail; */
		पूर्ण
	पूर्ण

	अगर (xc_ग_लिखो_reg(priv, XREG_D_CODE, 0) == 0)
		ret = 0;
	अगर (priv->dvb_amplitude != 0) अणु
		अगर (xc_ग_लिखो_reg(priv, XREG_AMPLITUDE,
				 (priv->firm_version != 0x0102 ||
				  priv->dvb_amplitude != 134 ?
				  priv->dvb_amplitude : 132)) != 0)
			ret = -EREMOTEIO;
	पूर्ण
	अगर (priv->set_smoothedcvbs != 0) अणु
		अगर (xc_ग_लिखो_reg(priv, XREG_SMOOTHEDCVBS, 1) != 0)
			ret = -EREMOTEIO;
	पूर्ण
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc4000: setting registers failed\n");
		/* जाओ fail; */
	पूर्ण

	xc_tune_channel(priv, priv->freq_hz);

	ret = 0;

fail:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक xc4000_set_analog_params(काष्ठा dvb_frontend *fe,
	काष्ठा analog_parameters *params)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	अचिन्हित पूर्णांक type = 0;
	पूर्णांक	ret = -EREMOTEIO;

	अगर (params->mode == V4L2_TUNER_RADIO) अणु
		dprपूर्णांकk(1, "%s() frequency=%d (in units of 62.5Hz)\n",
			__func__, params->frequency);

		mutex_lock(&priv->lock);

		params->std = 0;
		priv->freq_hz = params->frequency * 125L / 2;

		अगर (audio_std & XC4000_AUDIO_STD_INPUT1) अणु
			priv->video_standard = XC4000_FM_Radio_INPUT1;
			type = FM | INPUT1;
		पूर्ण अन्यथा अणु
			priv->video_standard = XC4000_FM_Radio_INPUT2;
			type = FM | INPUT2;
		पूर्ण

		जाओ tune_channel;
	पूर्ण

	dprपूर्णांकk(1, "%s() frequency=%d (in units of 62.5khz)\n",
		__func__, params->frequency);

	mutex_lock(&priv->lock);

	/* params->frequency is in units of 62.5khz */
	priv->freq_hz = params->frequency * 62500;

	params->std &= V4L2_STD_ALL;
	/* अगर std is not defined, choose one */
	अगर (!params->std)
		params->std = V4L2_STD_PAL_BG;

	अगर (audio_std & XC4000_AUDIO_STD_MONO)
		type = MONO;

	अगर (params->std & V4L2_STD_MN) अणु
		params->std = V4L2_STD_MN;
		अगर (audio_std & XC4000_AUDIO_STD_MONO) अणु
			priv->video_standard = XC4000_MN_NTSC_PAL_Mono;
		पूर्ण अन्यथा अगर (audio_std & XC4000_AUDIO_STD_A2) अणु
			params->std |= V4L2_STD_A2;
			priv->video_standard = XC4000_MN_NTSC_PAL_A2;
		पूर्ण अन्यथा अणु
			params->std |= V4L2_STD_BTSC;
			priv->video_standard = XC4000_MN_NTSC_PAL_BTSC;
		पूर्ण
		जाओ tune_channel;
	पूर्ण

	अगर (params->std & V4L2_STD_PAL_BG) अणु
		params->std = V4L2_STD_PAL_BG;
		अगर (audio_std & XC4000_AUDIO_STD_MONO) अणु
			priv->video_standard = XC4000_BG_PAL_MONO;
		पूर्ण अन्यथा अगर (!(audio_std & XC4000_AUDIO_STD_A2)) अणु
			अगर (!(audio_std & XC4000_AUDIO_STD_B)) अणु
				params->std |= V4L2_STD_NICAM_A;
				priv->video_standard = XC4000_BG_PAL_NICAM;
			पूर्ण अन्यथा अणु
				params->std |= V4L2_STD_NICAM_B;
				priv->video_standard = XC4000_BG_PAL_NICAM;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (!(audio_std & XC4000_AUDIO_STD_B)) अणु
				params->std |= V4L2_STD_A2_A;
				priv->video_standard = XC4000_BG_PAL_A2;
			पूर्ण अन्यथा अणु
				params->std |= V4L2_STD_A2_B;
				priv->video_standard = XC4000_BG_PAL_A2;
			पूर्ण
		पूर्ण
		जाओ tune_channel;
	पूर्ण

	अगर (params->std & V4L2_STD_PAL_I) अणु
		/* शेष to NICAM audio standard */
		params->std = V4L2_STD_PAL_I | V4L2_STD_NICAM;
		अगर (audio_std & XC4000_AUDIO_STD_MONO)
			priv->video_standard = XC4000_I_PAL_NICAM_MONO;
		अन्यथा
			priv->video_standard = XC4000_I_PAL_NICAM;
		जाओ tune_channel;
	पूर्ण

	अगर (params->std & V4L2_STD_PAL_DK) अणु
		params->std = V4L2_STD_PAL_DK;
		अगर (audio_std & XC4000_AUDIO_STD_MONO) अणु
			priv->video_standard = XC4000_DK_PAL_MONO;
		पूर्ण अन्यथा अगर (audio_std & XC4000_AUDIO_STD_A2) अणु
			params->std |= V4L2_STD_A2;
			priv->video_standard = XC4000_DK_PAL_A2;
		पूर्ण अन्यथा अणु
			params->std |= V4L2_STD_NICAM;
			priv->video_standard = XC4000_DK_PAL_NICAM;
		पूर्ण
		जाओ tune_channel;
	पूर्ण

	अगर (params->std & V4L2_STD_SECAM_DK) अणु
		/* शेष to A2 audio standard */
		params->std = V4L2_STD_SECAM_DK | V4L2_STD_A2;
		अगर (audio_std & XC4000_AUDIO_STD_L) अणु
			type = 0;
			priv->video_standard = XC4000_DK_SECAM_NICAM;
		पूर्ण अन्यथा अगर (audio_std & XC4000_AUDIO_STD_MONO) अणु
			priv->video_standard = XC4000_DK_SECAM_A2MONO;
		पूर्ण अन्यथा अगर (audio_std & XC4000_AUDIO_STD_K3) अणु
			params->std |= V4L2_STD_SECAM_K3;
			priv->video_standard = XC4000_DK_SECAM_A2LDK3;
		पूर्ण अन्यथा अणु
			priv->video_standard = XC4000_DK_SECAM_A2DK1;
		पूर्ण
		जाओ tune_channel;
	पूर्ण

	अगर (params->std & V4L2_STD_SECAM_L) अणु
		/* शेष to NICAM audio standard */
		type = 0;
		params->std = V4L2_STD_SECAM_L | V4L2_STD_NICAM;
		priv->video_standard = XC4000_L_SECAM_NICAM;
		जाओ tune_channel;
	पूर्ण

	अगर (params->std & V4L2_STD_SECAM_LC) अणु
		/* शेष to NICAM audio standard */
		type = 0;
		params->std = V4L2_STD_SECAM_LC | V4L2_STD_NICAM;
		priv->video_standard = XC4000_LC_SECAM_NICAM;
		जाओ tune_channel;
	पूर्ण

tune_channel:
	/* FIXME: it could be air. */
	priv->rf_mode = XC_RF_MODE_CABLE;

	अगर (check_firmware(fe, type, params->std,
			   xc4000_standard[priv->video_standard].पूर्णांक_freq) != 0)
		जाओ fail;

	ret = xc_set_संकेत_source(priv, priv->rf_mode);
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR
		       "xc4000: xc_set_signal_source(%d) failed\n",
		       priv->rf_mode);
		जाओ fail;
	पूर्ण अन्यथा अणु
		u16	video_mode, audio_mode;
		video_mode = xc4000_standard[priv->video_standard].video_mode;
		audio_mode = xc4000_standard[priv->video_standard].audio_mode;
		अगर (priv->video_standard < XC4000_BG_PAL_A2) अणु
			अगर (type & NOGD)
				video_mode &= 0xFF7F;
		पूर्ण अन्यथा अगर (priv->video_standard < XC4000_I_PAL_NICAM) अणु
			अगर (priv->firm_version == 0x0102)
				video_mode &= 0xFEFF;
			अगर (audio_std & XC4000_AUDIO_STD_B)
				video_mode |= 0x0080;
		पूर्ण
		ret = xc_set_tv_standard(priv, video_mode, audio_mode);
		अगर (ret != 0) अणु
			prपूर्णांकk(KERN_ERR "xc4000: xc_set_tv_standard failed\n");
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (xc_ग_लिखो_reg(priv, XREG_D_CODE, 0) == 0)
		ret = 0;
	अगर (xc_ग_लिखो_reg(priv, XREG_AMPLITUDE, 1) != 0)
		ret = -EREMOTEIO;
	अगर (priv->set_smoothedcvbs != 0) अणु
		अगर (xc_ग_लिखो_reg(priv, XREG_SMOOTHEDCVBS, 1) != 0)
			ret = -EREMOTEIO;
	पूर्ण
	अगर (ret != 0) अणु
		prपूर्णांकk(KERN_ERR "xc4000: setting registers failed\n");
		जाओ fail;
	पूर्ण

	xc_tune_channel(priv, priv->freq_hz);

	ret = 0;

fail:
	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक xc4000_get_संकेत(काष्ठा dvb_frontend *fe, u16 *strength)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	u16 value = 0;
	पूर्णांक rc;

	mutex_lock(&priv->lock);
	rc = xc4000_पढ़ोreg(priv, XREG_SIGNAL_LEVEL, &value);
	mutex_unlock(&priv->lock);

	अगर (rc < 0)
		जाओ ret;

	/* Inक्रमmation from real testing of DVB-T and radio part,
	   coefficient क्रम one dB is 0xff.
	 */
	tuner_dbg("Signal strength: -%ddB (%05d)\n", value >> 8, value);

	/* all known digital modes */
	अगर ((priv->video_standard == XC4000_DTV6) ||
	    (priv->video_standard == XC4000_DTV7) ||
	    (priv->video_standard == XC4000_DTV7_8) ||
	    (priv->video_standard == XC4000_DTV8))
		जाओ digital;

	/* Analog mode has NOISE LEVEL important, संकेत
	   depends only on gain of antenna and amplअगरiers,
	   but it करोesn't tell anything about real quality
	   of reception.
	 */
	mutex_lock(&priv->lock);
	rc = xc4000_पढ़ोreg(priv, XREG_NOISE_LEVEL, &value);
	mutex_unlock(&priv->lock);

	tuner_dbg("Noise level: %ddB (%05d)\n", value >> 8, value);

	/* highest noise level: 32dB */
	अगर (value >= 0x2000) अणु
		value = 0;
	पूर्ण अन्यथा अणु
		value = (~value << 3) & 0xffff;
	पूर्ण

	जाओ ret;

	/* Digital mode has SIGNAL LEVEL important and real
	   noise level is stored in demodulator रेजिस्टरs.
	 */
digital:
	/* best संकेत: -50dB */
	अगर (value <= 0x3200) अणु
		value = 0xffff;
	/* minimum: -114dB - should be 0x7200 but real zero is 0x713A */
	पूर्ण अन्यथा अगर (value >= 0x713A) अणु
		value = 0;
	पूर्ण अन्यथा अणु
		value = ~(value - 0x3200) << 2;
	पूर्ण

ret:
	*strength = value;

	वापस rc;
पूर्ण

अटल पूर्णांक xc4000_get_frequency(काष्ठा dvb_frontend *fe, u32 *freq)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;

	*freq = priv->freq_hz + priv->freq_offset;

	अगर (debug) अणु
		mutex_lock(&priv->lock);
		अगर ((priv->cur_fw.type
		     & (BASE | FM | DTV6 | DTV7 | DTV78 | DTV8)) == BASE) अणु
			u16	snr = 0;
			अगर (xc4000_पढ़ोreg(priv, XREG_SNR, &snr) == 0) अणु
				mutex_unlock(&priv->lock);
				dprपूर्णांकk(1, "%s() freq = %u, SNR = %d\n",
					__func__, *freq, snr);
				वापस 0;
			पूर्ण
		पूर्ण
		mutex_unlock(&priv->lock);
	पूर्ण

	dprपूर्णांकk(1, "%s()\n", __func__);

	वापस 0;
पूर्ण

अटल पूर्णांक xc4000_get_bandwidth(काष्ठा dvb_frontend *fe, u32 *bw)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	dprपूर्णांकk(1, "%s()\n", __func__);

	*bw = priv->bandwidth;
	वापस 0;
पूर्ण

अटल पूर्णांक xc4000_get_status(काष्ठा dvb_frontend *fe, u32 *status)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	u16	lock_status = 0;

	mutex_lock(&priv->lock);

	अगर (priv->cur_fw.type & BASE)
		xc_get_lock_status(priv, &lock_status);

	*status = (lock_status == 1 ?
		   TUNER_STATUS_LOCKED | TUNER_STATUS_STEREO : 0);
	अगर (priv->cur_fw.type & (DTV6 | DTV7 | DTV78 | DTV8))
		*status &= (~TUNER_STATUS_STEREO);

	mutex_unlock(&priv->lock);

	dprपूर्णांकk(2, "%s() lock_status = %d\n", __func__, lock_status);

	वापस 0;
पूर्ण

अटल पूर्णांक xc4000_sleep(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;
	पूर्णांक	ret = 0;

	dprपूर्णांकk(1, "%s()\n", __func__);

	mutex_lock(&priv->lock);

	/* Aव्योम firmware reload on slow devices */
	अगर ((no_घातeroff == 2 ||
	     (no_घातeroff == 0 && priv->शेष_pm != 0)) &&
	    (priv->cur_fw.type & BASE) != 0) अणु
		/* क्रमce reset and firmware reload */
		priv->cur_fw.type = XC_POWERED_DOWN;

		अगर (xc_ग_लिखो_reg(priv, XREG_POWER_DOWN, 0) != 0) अणु
			prपूर्णांकk(KERN_ERR
			       "xc4000: %s() unable to shutdown tuner\n",
			       __func__);
			ret = -EREMOTEIO;
		पूर्ण
		msleep(20);
	पूर्ण

	mutex_unlock(&priv->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक xc4000_init(काष्ठा dvb_frontend *fe)
अणु
	dprपूर्णांकk(1, "%s()\n", __func__);

	वापस 0;
पूर्ण

अटल व्योम xc4000_release(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा xc4000_priv *priv = fe->tuner_priv;

	dprपूर्णांकk(1, "%s()\n", __func__);

	mutex_lock(&xc4000_list_mutex);

	अगर (priv)
		hybrid_tuner_release_state(priv);

	mutex_unlock(&xc4000_list_mutex);

	fe->tuner_priv = शून्य;
पूर्ण

अटल स्थिर काष्ठा dvb_tuner_ops xc4000_tuner_ops = अणु
	.info = अणु
		.name              = "Xceive XC4000",
		.frequency_min_hz  =    1 * MHz,
		.frequency_max_hz  = 1023 * MHz,
		.frequency_step_hz =   50 * kHz,
	पूर्ण,

	.release	   = xc4000_release,
	.init		   = xc4000_init,
	.sleep		   = xc4000_sleep,

	.set_params	   = xc4000_set_params,
	.set_analog_params = xc4000_set_analog_params,
	.get_frequency	   = xc4000_get_frequency,
	.get_rf_strength   = xc4000_get_संकेत,
	.get_bandwidth	   = xc4000_get_bandwidth,
	.get_status	   = xc4000_get_status
पूर्ण;

काष्ठा dvb_frontend *xc4000_attach(काष्ठा dvb_frontend *fe,
				   काष्ठा i2c_adapter *i2c,
				   काष्ठा xc4000_config *cfg)
अणु
	काष्ठा xc4000_priv *priv = शून्य;
	पूर्णांक	instance;
	u16	id = 0;

	dprपूर्णांकk(1, "%s(%d-%04x)\n", __func__,
		i2c ? i2c_adapter_id(i2c) : -1,
		cfg ? cfg->i2c_address : -1);

	mutex_lock(&xc4000_list_mutex);

	instance = hybrid_tuner_request_state(काष्ठा xc4000_priv, priv,
					      hybrid_tuner_instance_list,
					      i2c, cfg->i2c_address, "xc4000");
	चयन (instance) अणु
	हाल 0:
		जाओ fail;
	हाल 1:
		/* new tuner instance */
		priv->bandwidth = 6000000;
		/* set शेष configuration */
		priv->अगर_khz = 4560;
		priv->शेष_pm = 0;
		priv->dvb_amplitude = 134;
		priv->set_smoothedcvbs = 1;
		mutex_init(&priv->lock);
		fe->tuner_priv = priv;
		अवरोध;
	शेष:
		/* existing tuner instance */
		fe->tuner_priv = priv;
		अवरोध;
	पूर्ण

	अगर (cfg->अगर_khz != 0) अणु
		/* copy configuration अगर provided by the caller */
		priv->अगर_khz = cfg->अगर_khz;
		priv->शेष_pm = cfg->शेष_pm;
		priv->dvb_amplitude = cfg->dvb_amplitude;
		priv->set_smoothedcvbs = cfg->set_smoothedcvbs;
	पूर्ण

	/* Check अगर firmware has been loaded. It is possible that another
	   instance of the driver has loaded the firmware.
	 */

	अगर (instance == 1) अणु
		अगर (xc4000_पढ़ोreg(priv, XREG_PRODUCT_ID, &id) != 0)
			जाओ fail;
	पूर्ण अन्यथा अणु
		id = ((priv->cur_fw.type & BASE) != 0 ?
		      priv->hwmodel : XC_PRODUCT_ID_FW_NOT_LOADED);
	पूर्ण

	चयन (id) अणु
	हाल XC_PRODUCT_ID_XC4000:
	हाल XC_PRODUCT_ID_XC4100:
		prपूर्णांकk(KERN_INFO
			"xc4000: Successfully identified at address 0x%02x\n",
			cfg->i2c_address);
		prपूर्णांकk(KERN_INFO
			"xc4000: Firmware has been loaded previously\n");
		अवरोध;
	हाल XC_PRODUCT_ID_FW_NOT_LOADED:
		prपूर्णांकk(KERN_INFO
			"xc4000: Successfully identified at address 0x%02x\n",
			cfg->i2c_address);
		prपूर्णांकk(KERN_INFO
			"xc4000: Firmware has not been loaded previously\n");
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR
			"xc4000: Device not found at addr 0x%02x (0x%x)\n",
			cfg->i2c_address, id);
		जाओ fail;
	पूर्ण

	mutex_unlock(&xc4000_list_mutex);

	स_नकल(&fe->ops.tuner_ops, &xc4000_tuner_ops,
		माप(काष्ठा dvb_tuner_ops));

	अगर (instance == 1) अणु
		पूर्णांक	ret;
		mutex_lock(&priv->lock);
		ret = xc4000_fwupload(fe);
		mutex_unlock(&priv->lock);
		अगर (ret != 0)
			जाओ fail2;
	पूर्ण

	वापस fe;
fail:
	mutex_unlock(&xc4000_list_mutex);
fail2:
	xc4000_release(fe);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(xc4000_attach);

MODULE_AUTHOR("Steven Toth, Davide Ferri");
MODULE_DESCRIPTION("Xceive xc4000 silicon tuner driver");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE(XC4000_DEFAULT_FIRMWARE_NEW);
MODULE_FIRMWARE(XC4000_DEFAULT_FIRMWARE);
