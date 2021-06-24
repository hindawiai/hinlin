<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Driver क्रम the Integrant ITD1000 "Zero-IF Tuner IC for Direct Broadcast Satellite"
 *
 *  Copyright (c) 2007 Patrick Boettcher <pb@linuxtv.org>
 */

#अगर_अघोषित ITD1000_PRIV_H
#घोषणा ITD1000_PRIV_H

काष्ठा itd1000_state अणु
	काष्ठा itd1000_config *cfg;
	काष्ठा i2c_adapter    *i2c;

	u32 frequency; /* contains the value resulting from the LO-setting */

	/* ugly workaround क्रम flexcop's incapable i2c-controller
	 * FIXME, अगर possible
	 */
	u8 shaकरोw[256];
पूर्ण;

क्रमागत itd1000_रेजिस्टर अणु
	VCO_CHP1 = 0x65,
	VCO_CHP2,
	PLLCON1,
	PLLNH,
	PLLNL,
	PLLFH,
	PLLFM,
	PLLFL,
	RESERVED_0X6D,
	PLLLOCK,
	VCO_CHP2_I2C,
	VCO_CHP1_I2C,
	BW,
	RESERVED_0X73 = 0x73,
	RESERVED_0X74,
	RESERVED_0X75,
	GVBB,
	GVRF,
	GVBB_I2C,
	EXTGVBBRF,
	DIVAGCCK,
	BBTR,
	RFTR,
	BBGVMIN,
	RESERVED_0X7E,
	RESERVED_0X85 = 0x85,
	RESERVED_0X86,
	CON1,
	RESERVED_0X88,
	RESERVED_0X89,
	RFST0,
	RFST1,
	RFST2,
	RFST3,
	RFST4,
	RFST5,
	RFST6,
	RFST7,
	RFST8,
	RFST9,
	RESERVED_0X94,
	RESERVED_0X95,
	RESERVED_0X96,
	RESERVED_0X97,
	RESERVED_0X98,
	RESERVED_0X99,
	RESERVED_0X9A,
	RESERVED_0X9B,
पूर्ण;

#पूर्ण_अगर
