<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
   cx231xx-pcb-cfg.h - driver क्रम Conexant
		Cx23100/101/102 USB video capture devices

   Copyright (C) 2008 <srinivasa.deevi at conexant करोt com>

 */

#अगर_अघोषित _PCB_CONFIG_H_
#घोषणा _PCB_CONFIG_H_

#समावेश <linux/init.h>
#समावेश <linux/module.h>

/***************************************************************************
				* Class Inक्रमmation *
***************************************************************************/
#घोषणा CLASS_DEFAULT       0xFF

क्रमागत VENDOR_REQUEST_TYPE अणु
	/* Set/Get I2C */
	VRT_SET_I2C0 = 0x0,
	VRT_SET_I2C1 = 0x1,
	VRT_SET_I2C2 = 0x2,
	VRT_GET_I2C0 = 0x4,
	VRT_GET_I2C1 = 0x5,
	VRT_GET_I2C2 = 0x6,

	/* Set/Get GPIO */
	VRT_SET_GPIO = 0x8,
	VRT_GET_GPIO = 0x9,

	/* Set/Get GPIE */
	VRT_SET_GPIE = 0xA,
	VRT_GET_GPIE = 0xB,

	/* Set/Get Register Control/Status */
	VRT_SET_REGISTER = 0xC,
	VRT_GET_REGISTER = 0xD,

	/* Get Extended Compat ID Descriptor */
	VRT_GET_EXTCID_DESC = 0xFF,
पूर्ण;

क्रमागत BYTE_ENABLE_MASK अणु
	ENABLE_ONE_BYTE = 0x1,
	ENABLE_TWE_BYTE = 0x3,
	ENABLE_THREE_BYTE = 0x7,
	ENABLE_FOUR_BYTE = 0xF,
पूर्ण;

#घोषणा SPEED_MASK      0x1
क्रमागत USB_SPEEDअणु
	FULL_SPEED = 0x0,	/* 0: full speed */
	HIGH_SPEED = 0x1	/* 1: high speed */
पूर्ण;

#घोषणा TS_MASK         0x6
क्रमागत TS_PORTअणु
	NO_TS_PORT = 0x0,	/* 2'b00: Neither port used. PCB not a Hybrid,
				   only offers Analog TV or Video */
	TS1_PORT = 0x4,		/* 2'b10: TS1 Input (Hybrid mode :
				Digital or External Analog/Compressed source) */
	TS1_TS2_PORT = 0x6,	/* 2'b11: TS1 & TS2 Inमाला_दो
				(Dual inमाला_दो from Digital and/or
				External Analog/Compressed sources) */
	TS1_EXT_CLOCK = 0x6,	/* 2'b11: TS1 & TS2 as selector
						to बाह्यal घड़ी */
	TS1VIP_TS2_PORT = 0x2	/* 2'b01: TS1 used as 656/VIP Output,
				   TS2 Input (from Compressor) */
पूर्ण;

#घोषणा EAVP_MASK       0x8
क्रमागत EAV_PRESENTअणु
	NO_EXTERNAL_AV = 0x0,	/* 0: No External A/V inमाला_दो
						(no need क्रम i2s block),
						Analog Tuner must be present */
	EXTERNAL_AV = 0x8	/* 1: External A/V inमाला_दो
						present (requires i2s blk) */
पूर्ण;

#घोषणा ATM_MASK        0x30
क्रमागत AT_MODEअणु
	DIF_TUNER = 0x30,	/* 2'b11: IF Tuner (requires use of DIF) */
	BASEBAND_SOUND = 0x20,	/* 2'b10: Baseband Composite &
						Sound-IF Signals present */
	NO_TUNER = 0x10		/* 2'b0x: No Analog Tuner present */
पूर्ण;

#घोषणा PWR_SEL_MASK    0x40
क्रमागत POWE_TYPEअणु
	SELF_POWER = 0x0,	/* 0: self घातer */
	BUS_POWER = 0x40	/* 1: bus घातer */
पूर्ण;

क्रमागत USB_POWE_TYPEअणु
	USB_SELF_POWER = 0,
	USB_BUS_POWER
पूर्ण;

#घोषणा BO_0_MASK       0x80
क्रमागत AVDEC_STATUSअणु
	AVDEC_DISABLE = 0x0,	/* 0: A/V Decoder Disabled */
	AVDEC_ENABLE = 0x80	/* 1: A/V Decoder Enabled */
पूर्ण;

#घोषणा BO_1_MASK       0x100

#घोषणा BUSPOWER_MASK   0xC4	/* क्रम Polaris spec 0.8 */
#घोषणा SELFPOWER_MASK  0x86

/***************************************************************************/
#घोषणा NOT_DECIDE_YET  0xFE
#घोषणा NOT_SUPPORTED   0xFF

/***************************************************************************
				* क्रम mod field use *
***************************************************************************/
#घोषणा MOD_DIGITAL     0x1
#घोषणा MOD_ANALOG      0x2
#घोषणा MOD_DIF         0x4
#घोषणा MOD_EXTERNAL    0x8
#घोषणा CAP_ALL_MOD     0x0f

/***************************************************************************
				* source define *
***************************************************************************/
#घोषणा SOURCE_DIGITAL          0x1
#घोषणा SOURCE_ANALOG           0x2
#घोषणा SOURCE_DIF              0x4
#घोषणा SOURCE_EXTERNAL         0x8
#घोषणा SOURCE_TS_BDA			0x10
#घोषणा SOURCE_TS_ENCODE		0x20
#घोषणा SOURCE_TS_EXTERNAL	0x40

/***************************************************************************
				* पूर्णांकerface inक्रमmation define *
***************************************************************************/
काष्ठा INTERFACE_INFO अणु
	u8 पूर्णांकerrupt_index;
	u8 ts1_index;
	u8 ts2_index;
	u8 audio_index;
	u8 video_index;
	u8 vanc_index;		/* VBI */
	u8 hanc_index;		/* Sliced CC */
	u8 ir_index;
पूर्ण;

क्रमागत INDEX_INTERFACE_INFOअणु
	INDEX_INTERRUPT = 0x0,
	INDEX_TS1,
	INDEX_TS2,
	INDEX_AUDIO,
	INDEX_VIDEO,
	INDEX_VANC,
	INDEX_HANC,
	INDEX_IR,
पूर्ण;

/***************************************************************************
				* configuration inक्रमmation define *
***************************************************************************/
काष्ठा CONFIG_INFO अणु
	u8 config_index;
	काष्ठा INTERFACE_INFO पूर्णांकerface_info;
पूर्ण;

काष्ठा pcb_config अणु
	u8 index;
	u8 type;		/* bus घातer or self घातer,
					   self घातer--0, bus_घातer--1 */
	u8 speed;		/* usb speed, 2.0--1, 1.1--0 */
	u8 mode;		/* digital , anlog, dअगर or बाह्यal A/V */
	u32 ts1_source;		/* three source -- BDA,External,encode */
	u32 ts2_source;
	u32 analog_source;
	u8 digital_index;	/* bus-घातer used */
	u8 analog_index;	/* bus-घातer used */
	u8 dअगर_index;		/* bus-घातer used */
	u8 बाह्यal_index;	/* bus-घातer used */
	u8 config_num;		/* current config num, 0,1,2,
						   क्रम self-घातer, always 0 */
	काष्ठा CONFIG_INFO hs_config_info[3];
	काष्ठा CONFIG_INFO fs_config_info[3];
पूर्ण;

क्रमागत INDEX_PCB_CONFIGअणु
	INDEX_SELFPOWER_DIGITAL_ONLY = 0x0,
	INDEX_SELFPOWER_DUAL_DIGITAL,
	INDEX_SELFPOWER_ANALOG_ONLY,
	INDEX_SELFPOWER_DUAL,
	INDEX_SELFPOWER_TRIPLE,
	INDEX_SELFPOWER_COMPRESSOR,
	INDEX_BUSPOWER_DIGITAL_ONLY,
	INDEX_BUSPOWER_ANALOG_ONLY,
	INDEX_BUSPOWER_DIF_ONLY,
	INDEX_BUSPOWER_EXTERNAL_ONLY,
	INDEX_BUSPOWER_EXTERNAL_ANALOG,
	INDEX_BUSPOWER_EXTERNAL_DIF,
	INDEX_BUSPOWER_EXTERNAL_DIGITAL,
	INDEX_BUSPOWER_DIGITAL_ANALOG,
	INDEX_BUSPOWER_DIGITAL_DIF,
	INDEX_BUSPOWER_DIGITAL_ANALOG_EXTERNAL,
	INDEX_BUSPOWER_DIGITAL_DIF_EXTERNAL,
पूर्ण;

/***************************************************************************/
काष्ठा cx231xx;

पूर्णांक initialize_cx231xx(काष्ठा cx231xx *p_dev);

#पूर्ण_अगर
