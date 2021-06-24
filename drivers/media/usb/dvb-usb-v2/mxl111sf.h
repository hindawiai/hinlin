<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2010-2014 Michael Krufky (mkrufky@linuxtv.org)
 *
 * see Documentation/driver-api/media/drivers/dvb-usb.rst क्रम more inक्रमmation
 */

#अगर_अघोषित _DVB_USB_MXL111SF_H_
#घोषणा _DVB_USB_MXL111SF_H_

#अगर_घोषित DVB_USB_LOG_PREFIX
#अघोषित DVB_USB_LOG_PREFIX
#पूर्ण_अगर
#घोषणा DVB_USB_LOG_PREFIX "mxl111sf"
#समावेश "dvb_usb.h"
#समावेश <media/tveeprom.h>
#समावेश <media/media-entity.h>

/* Max transfer size करोne by I2C transfer functions */
#घोषणा MXL_MAX_XFER_SIZE  64

#घोषणा MXL_EP1_REG_READ     1
#घोषणा MXL_EP2_REG_WRITE    2
#घोषणा MXL_EP3_INTERRUPT    3
#घोषणा MXL_EP4_MPEG2        4
#घोषणा MXL_EP5_I2S          5
#घोषणा MXL_EP6_656          6
#घोषणा MXL_EP6_MPEG2        6

#अगर_घोषित USING_ENUM_mxl111sf_current_mode
क्रमागत mxl111sf_current_mode अणु
	mxl_mode_dvbt = MXL_EP4_MPEG2,
	mxl_mode_mh   = MXL_EP5_I2S,
	mxl_mode_atsc = MXL_EP6_MPEG2,
पूर्ण;
#पूर्ण_अगर

क्रमागत mxl111sf_gpio_port_expander अणु
	mxl111sf_gpio_hw,
	mxl111sf_PCA9534,
पूर्ण;

काष्ठा mxl111sf_adap_state अणु
	पूर्णांक alt_mode;
	पूर्णांक gpio_mode;
	पूर्णांक device_mode;
	पूर्णांक ep6_घड़ीphase;
	पूर्णांक (*fe_init)(काष्ठा dvb_frontend *);
	पूर्णांक (*fe_sleep)(काष्ठा dvb_frontend *);
पूर्ण;

क्रमागत mxl111sf_pads अणु
	MXL111SF_PAD_RF_INPUT,
	MXL111SF_PAD_OUTPUT,
	MXL111SF_NUM_PADS
पूर्ण;

काष्ठा mxl111sf_state अणु
	काष्ठा dvb_usb_device *d;

	क्रमागत mxl111sf_gpio_port_expander gpio_port_expander;
	u8 port_expander_addr;

	u8 chip_id;
	u8 chip_ver;
#घोषणा MXL111SF_V6     1
#घोषणा MXL111SF_V8_100 2
#घोषणा MXL111SF_V8_200 3
	u8 chip_rev;

#अगर_घोषित USING_ENUM_mxl111sf_current_mode
	क्रमागत mxl111sf_current_mode current_mode;
#पूर्ण_अगर

#घोषणा MXL_TUNER_MODE         0
#घोषणा MXL_SOC_MODE           1
#घोषणा MXL_DEV_MODE_MASK      0x01
#अगर 1
	पूर्णांक device_mode;
#पूर्ण_अगर
	/* use usb alt setting 1 क्रम EP4 ISOC transfer (dvb-t),
				     EP5 BULK transfer (atsc-mh),
				     EP6 BULK transfer (atsc/qam),
	   use usb alt setting 2 क्रम EP4 BULK transfer (dvb-t),
				     EP5 ISOC transfer (atsc-mh),
				     EP6 ISOC transfer (atsc/qam),
	 */
	पूर्णांक alt_mode;
	पूर्णांक gpio_mode;
	काष्ठा tveeprom tv;

	काष्ठा mutex fe_lock;
	u8 num_frontends;
	काष्ठा mxl111sf_adap_state adap_state[3];
	u8 sndbuf[MXL_MAX_XFER_SIZE];
	u8 rcvbuf[MXL_MAX_XFER_SIZE];
	काष्ठा mutex msg_lock;
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	काष्ठा media_entity tuner;
	काष्ठा media_pad tuner_pads[MXL111SF_NUM_PADS];
#पूर्ण_अगर
पूर्ण;

पूर्णांक mxl111sf_पढ़ो_reg(काष्ठा mxl111sf_state *state, u8 addr, u8 *data);
पूर्णांक mxl111sf_ग_लिखो_reg(काष्ठा mxl111sf_state *state, u8 addr, u8 data);

काष्ठा mxl111sf_reg_ctrl_info अणु
	u8 addr;
	u8 mask;
	u8 data;
पूर्ण;

पूर्णांक mxl111sf_ग_लिखो_reg_mask(काष्ठा mxl111sf_state *state,
			    u8 addr, u8 mask, u8 data);
पूर्णांक mxl111sf_ctrl_program_regs(काष्ठा mxl111sf_state *state,
			       काष्ठा mxl111sf_reg_ctrl_info *ctrl_reg_info);

/* needed क्रम hardware i2c functions in mxl111sf-i2c.c:
 * mxl111sf_i2c_send_data / mxl111sf_i2c_get_data */
पूर्णांक mxl111sf_ctrl_msg(काष्ठा mxl111sf_state *state,
		      u8 cmd, u8 *wbuf, पूर्णांक wlen, u8 *rbuf, पूर्णांक rlen);

#घोषणा mxl_prपूर्णांकk(kern, fmt, arg...) \
	prपूर्णांकk(kern "%s: " fmt "\n", __func__, ##arg)

#घोषणा mxl_info(fmt, arg...) \
	mxl_prपूर्णांकk(KERN_INFO, fmt, ##arg)

बाह्य पूर्णांक dvb_usb_mxl111sf_debug;
#घोषणा mxl_debug(fmt, arg...) \
	अगर (dvb_usb_mxl111sf_debug) \
		mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg)

#घोषणा MXL_I2C_DBG 0x04
#घोषणा MXL_ADV_DBG 0x10
#घोषणा mxl_debug_adv(fmt, arg...) \
	अगर (dvb_usb_mxl111sf_debug & MXL_ADV_DBG) \
		mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg)

#घोषणा mxl_i2c(fmt, arg...) \
	अगर (dvb_usb_mxl111sf_debug & MXL_I2C_DBG) \
		mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg)

#घोषणा mxl_i2c_adv(fmt, arg...) \
	अगर ((dvb_usb_mxl111sf_debug & (MXL_I2C_DBG | MXL_ADV_DBG)) == \
		(MXL_I2C_DBG | MXL_ADV_DBG)) \
			mxl_prपूर्णांकk(KERN_DEBUG, fmt, ##arg)

/* The following allows the mxl_fail() macro defined below to work
 * in बाह्यel modules, such as mxl111sf-tuner.ko, even though
 * dvb_usb_mxl111sf_debug is not defined within those modules */
#अगर (defined(__MXL111SF_TUNER_H__)) || (defined(__MXL111SF_DEMOD_H__))
#घोषणा MXL_ADV_DEBUG_ENABLED MXL_ADV_DBG
#अन्यथा
#घोषणा MXL_ADV_DEBUG_ENABLED dvb_usb_mxl111sf_debug
#पूर्ण_अगर

#घोषणा mxl_fail(ret)							\
(अणु									\
	पूर्णांक __ret;							\
	__ret = (ret < 0);						\
	अगर ((__ret) && (MXL_ADV_DEBUG_ENABLED & MXL_ADV_DBG))		\
		mxl_prपूर्णांकk(KERN_ERR, "error %d on line %d",		\
			   ret, __LINE__);				\
	__ret;								\
पूर्ण)

#पूर्ण_अगर /* _DVB_USB_MXL111SF_H_ */
