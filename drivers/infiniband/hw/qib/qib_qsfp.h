<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* QSFP support common definitions, क्रम ib_qib driver */

#घोषणा QSFP_DEV 0xA0
#घोषणा QSFP_PWR_LAG_MSEC 2000
#घोषणा QSFP_MODPRS_LAG_MSEC 20

/*
 * Below are masks क्रम various QSFP संकेतs, क्रम Port 1.
 * Port2 equivalents are shअगरted by QSFP_GPIO_PORT2_SHIFT.
 * _N means निश्चितed low
 */
#घोषणा QSFP_GPIO_MOD_SEL_N (4)
#घोषणा QSFP_GPIO_MOD_PRS_N (8)
#घोषणा QSFP_GPIO_INT_N (0x10)
#घोषणा QSFP_GPIO_MOD_RST_N (0x20)
#घोषणा QSFP_GPIO_LP_MODE (0x40)
#घोषणा QSFP_GPIO_PORT2_SHIFT 5

#घोषणा QSFP_PAGESIZE 128
/* Defined fields that QLogic requires of qualअगरied cables */
/* Byte 0 is Identअगरier, not checked */
/* Byte 1 is reserved "status MSB" */
/* Byte 2 is "status LSB" We only care that D2 "Flat Mem" is set. */
/*
 * Rest of first 128 not used, although 127 is reserved क्रम page select
 * अगर module is not "Flat memory".
 */
/* Byte 128 is Identअगरier: must be 0x0c क्रम QSFP, or 0x0d क्रम QSFP+ */
#घोषणा QSFP_MOD_ID_OFFS 128
/*
 * Byte 129 is "Extended Identifier". We only care about D7,D6: Power class
 *  0:1.5W, 1:2.0W, 2:2.5W, 3:3.5W
 */
#घोषणा QSFP_MOD_PWR_OFFS 129
/* Byte 130 is Connector type. Not QLogic req'd */
/* Bytes 131..138 are Transceiver types, bit maps क्रम various tech, none IB */
/* Byte 139 is encoding. code 0x01 is 8b10b. Not QLogic req'd */
/* byte 140 is nominal bit-rate, in units of 100Mbits/sec Not QLogic req'd */
/* Byte 141 is Extended Rate Select. Not QLogic req'd */
/* Bytes 142..145 are lengths क्रम various fiber types. Not QLogic req'd */
/* Byte 146 is length क्रम Copper. Units of 1 meter */
#घोषणा QSFP_MOD_LEN_OFFS 146
/*
 * Byte 147 is Device technology. D0..3 not Qlogc req'd
 * D4..7 select from 15 choices, translated by table:
 */
#घोषणा QSFP_MOD_TECH_OFFS 147
बाह्य स्थिर अक्षर *स्थिर qib_qsfp_devtech[16];
/* Active Equalization includes fiber, copper full EQ, and copper near Eq */
#घोषणा QSFP_IS_ACTIVE(tech) ((0xA2FF >> ((tech) >> 4)) & 1)
/* Active Equalization includes fiber, copper full EQ, and copper far Eq */
#घोषणा QSFP_IS_ACTIVE_FAR(tech) ((0x32FF >> ((tech) >> 4)) & 1)
/* Attenuation should be valid क्रम copper other than full/near Eq */
#घोषणा QSFP_HAS_ATTEN(tech) ((0x4D00 >> ((tech) >> 4)) & 1)
/* Length is only valid अगर technology is "copper" */
#घोषणा QSFP_IS_CU(tech) ((0xED00 >> ((tech) >> 4)) & 1)
#घोषणा QSFP_TECH_1490 9

#घोषणा QSFP_OUI(oui) (((अचिन्हित)oui[0] << 16) | ((अचिन्हित)oui[1] << 8) | \
			oui[2])
#घोषणा QSFP_OUI_AMPHENOL 0x415048
#घोषणा QSFP_OUI_FINISAR  0x009065
#घोषणा QSFP_OUI_GORE     0x002177

/* Bytes 148..163 are Venकरोr Name, Left-justअगरied Blank-filled */
#घोषणा QSFP_VEND_OFFS 148
#घोषणा QSFP_VEND_LEN 16
/* Byte 164 is IB Extended tranceiver codes Bits D0..3 are SDR,DDR,QDR,EDR */
#घोषणा QSFP_IBXCV_OFFS 164
/* Bytes 165..167 are Venकरोr OUI number */
#घोषणा QSFP_VOUI_OFFS 165
#घोषणा QSFP_VOUI_LEN 3
/* Bytes 168..183 are Venकरोr Part Number, string */
#घोषणा QSFP_PN_OFFS 168
#घोषणा QSFP_PN_LEN 16
/* Bytes 184,185 are Venकरोr Rev. Left Justअगरied, Blank-filled */
#घोषणा QSFP_REV_OFFS 184
#घोषणा QSFP_REV_LEN 2
/*
 * Bytes 186,187 are Wavelength, अगर Optical. Not Qlogic req'd
 *  If copper, they are attenuation in dB:
 * Byte 186 is at 2.5Gb/sec (SDR), Byte 187 at 5.0Gb/sec (DDR)
 */
#घोषणा QSFP_ATTEN_OFFS 186
#घोषणा QSFP_ATTEN_LEN 2
/* Bytes 188,189 are Wavelength tolerance, not QLogic req'd */
/* Byte 190 is Max Case Temp. Not QLogic req'd */
/* Byte 191 is LSB of sum of bytes 128..190. Not QLogic req'd */
#घोषणा QSFP_CC_OFFS 191
/* Bytes 192..195 are Options implemented in qsfp. Not Qlogic req'd */
/* Bytes 196..211 are Serial Number, String */
#घोषणा QSFP_SN_OFFS 196
#घोषणा QSFP_SN_LEN 16
/* Bytes 212..219 are date-code YYMMDD (MM==1 क्रम Jan) */
#घोषणा QSFP_DATE_OFFS 212
#घोषणा QSFP_DATE_LEN 6
/* Bytes 218,219 are optional lot-code, string */
#घोषणा QSFP_LOT_OFFS 218
#घोषणा QSFP_LOT_LEN 2
/* Bytes 220, 221 indicate monitoring options, Not QLogic req'd */
/* Byte 223 is LSB of sum of bytes 192..222 */
#घोषणा QSFP_CC_EXT_OFFS 223

/*
 * काष्ठा qib_qsfp_data encapsulates state of QSFP device क्रम one port.
 * it will be part of port-chip-specअगरic data अगर a board supports QSFP.
 *
 * Since multiple board-types use QSFP, and their pport_data काष्ठाs
 * dअगरfer (in the chip-specअगरic section), we need a poपूर्णांकer to its head.
 *
 * Aव्योमing premature optimization, we will have one work_काष्ठा per port,
 * and let the (increasingly inaccurately named) eep_lock arbitrate
 * access to common resources.
 *
 */

/*
 * Hold the parts of the onboard EEPROM that we care about, so we aren't
 * coonstantly bit-boffing
 */
काष्ठा qib_qsfp_cache अणु
	u8 id;	/* must be 0x0C or 0x0D; 0 indicates invalid EEPROM पढ़ो */
	u8 pwr; /* in D6,7 */
	u8 len;	/* in meters, Cu only */
	u8 tech;
	अक्षर venकरोr[QSFP_VEND_LEN];
	u8 xt_xcv; /* Ext. tranceiver codes, 4 lsbs are IB speed supported */
	u8 oui[QSFP_VOUI_LEN];
	u8 partnum[QSFP_PN_LEN];
	u8 rev[QSFP_REV_LEN];
	u8 atten[QSFP_ATTEN_LEN];
	u8 cks1;	/* Checksum of bytes 128..190 */
	u8 serial[QSFP_SN_LEN];
	u8 date[QSFP_DATE_LEN];
	u8 lot[QSFP_LOT_LEN];
	u8 cks2;	/* Checsum of bytes 192..222 */
पूर्ण;

#घोषणा QSFP_PWR(pbyte) (((pbyte) >> 6) & 3)
#घोषणा QSFP_ATTEN_SDR(attenarray) (attenarray[0])
#घोषणा QSFP_ATTEN_DDR(attenarray) (attenarray[1])

काष्ठा qib_qsfp_data अणु
	/* Helps to find our way */
	काष्ठा qib_pportdata *ppd;
	काष्ठा work_काष्ठा work;
	काष्ठा qib_qsfp_cache cache;
	अचिन्हित दीर्घ t_insert;
	u8 modpresent;
पूर्ण;

बाह्य पूर्णांक qib_refresh_qsfp_cache(काष्ठा qib_pportdata *ppd,
				  काष्ठा qib_qsfp_cache *cp);
बाह्य पूर्णांक qib_qsfp_mod_present(काष्ठा qib_pportdata *ppd);
बाह्य व्योम qib_qsfp_init(काष्ठा qib_qsfp_data *qd,
			  व्योम (*fevent)(काष्ठा work_काष्ठा *));
