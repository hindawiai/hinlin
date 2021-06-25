<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    MaxLinear MXL5005S VSB/QAM/DVBT tuner driver

    Copyright (C) 2008 MaxLinear
    Copyright (C) 2008 Steven Toth <stoth@linuxtv.org>


*/

#अगर_अघोषित __MXL5005S_H
#घोषणा __MXL5005S_H

#समावेश <linux/i2c.h>
#समावेश <media/dvb_frontend.h>

काष्ठा mxl5005s_config अणु

	/* 7 bit i2c address */
	u8 i2c_address;

#घोषणा IF_FREQ_4570000HZ    4570000
#घोषणा IF_FREQ_4571429HZ    4571429
#घोषणा IF_FREQ_5380000HZ    5380000
#घोषणा IF_FREQ_36000000HZ  36000000
#घोषणा IF_FREQ_36125000HZ  36125000
#घोषणा IF_FREQ_36166667HZ  36166667
#घोषणा IF_FREQ_44000000HZ  44000000
	u32 अगर_freq;

#घोषणा CRYSTAL_FREQ_4000000HZ    4000000
#घोषणा CRYSTAL_FREQ_16000000HZ  16000000
#घोषणा CRYSTAL_FREQ_25000000HZ  25000000
#घोषणा CRYSTAL_FREQ_28800000HZ  28800000
	u32 xtal_freq;

#घोषणा MXL_DUAL_AGC   0
#घोषणा MXL_SINGLE_AGC 1
	u8 agc_mode;

#घोषणा MXL_TF_DEFAULT	0
#घोषणा MXL_TF_OFF	1
#घोषणा MXL_TF_C	2
#घोषणा MXL_TF_C_H	3
#घोषणा MXL_TF_D	4
#घोषणा MXL_TF_D_L	5
#घोषणा MXL_TF_E	6
#घोषणा MXL_TF_F	7
#घोषणा MXL_TF_E_2	8
#घोषणा MXL_TF_E_NA	9
#घोषणा MXL_TF_G	10
	u8 tracking_filter;

#घोषणा MXL_RSSI_DISABLE	0
#घोषणा MXL_RSSI_ENABLE		1
	u8 rssi_enable;

#घोषणा MXL_CAP_SEL_DISABLE	0
#घोषणा MXL_CAP_SEL_ENABLE	1
	u8 cap_select;

#घोषणा MXL_DIV_OUT_1	0
#घोषणा MXL_DIV_OUT_4	1
	u8 भाग_out;

#घोषणा MXL_CLOCK_OUT_DISABLE	0
#घोषणा MXL_CLOCK_OUT_ENABLE	1
	u8 घड़ी_out;

#घोषणा MXL5005S_IF_OUTPUT_LOAD_200_OHM 200
#घोषणा MXL5005S_IF_OUTPUT_LOAD_300_OHM 300
	u32 output_load;

#घोषणा MXL5005S_TOP_5P5   55
#घोषणा MXL5005S_TOP_7P2   72
#घोषणा MXL5005S_TOP_9P2   92
#घोषणा MXL5005S_TOP_11P0 110
#घोषणा MXL5005S_TOP_12P9 129
#घोषणा MXL5005S_TOP_14P7 147
#घोषणा MXL5005S_TOP_16P8 168
#घोषणा MXL5005S_TOP_19P4 194
#घोषणा MXL5005S_TOP_21P2 212
#घोषणा MXL5005S_TOP_23P2 232
#घोषणा MXL5005S_TOP_25P2 252
#घोषणा MXL5005S_TOP_27P1 271
#घोषणा MXL5005S_TOP_29P2 292
#घोषणा MXL5005S_TOP_31P7 317
#घोषणा MXL5005S_TOP_34P9 349
	u32 top;

#घोषणा MXL_ANALOG_MODE  0
#घोषणा MXL_DIGITAL_MODE 1
	u8 mod_mode;

#घोषणा MXL_ZERO_IF 0
#घोषणा MXL_LOW_IF  1
	u8 अगर_mode;

	/* Some boards need to override the built-in logic क्रम determining
	   the gain when in QAM mode (the HVR-1600 is one such हाल) */
	u8 qam_gain;

	/* Stuff I करोn't know what to करो with */
	u8 AgcMasterByte;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_MEDIA_TUNER_MXL5005S)
बाह्य काष्ठा dvb_frontend *mxl5005s_attach(काष्ठा dvb_frontend *fe,
					    काष्ठा i2c_adapter *i2c,
					    काष्ठा mxl5005s_config *config);
#अन्यथा
अटल अंतरभूत काष्ठा dvb_frontend *mxl5005s_attach(काष्ठा dvb_frontend *fe,
					    काष्ठा i2c_adapter *i2c,
					    काष्ठा mxl5005s_config *config)
अणु
	prपूर्णांकk(KERN_WARNING "%s: driver disabled by Kconfig\n", __func__);
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_DVB_TUNER_MXL5005S */

#पूर्ण_अगर /* __MXL5005S_H */

