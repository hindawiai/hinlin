<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/* QSFP support common definitions, क्रम hfi driver */

#घोषणा QSFP_DEV 0xA0
#घोषणा QSFP_PWR_LAG_MSEC 2000
#घोषणा QSFP_MODPRS_LAG_MSEC 20
/* 128 byte pages, per SFF 8636 rev 2.4 */
#घोषणा QSFP_MAX_NUM_PAGES	5

/*
 * Below are masks क्रम QSFP pins.  Pins are the same क्रम HFI0 and HFI1.
 * _N means निश्चितed low
 */
#घोषणा QSFP_HFI0_I2CCLK    BIT(0)
#घोषणा QSFP_HFI0_I2CDAT    BIT(1)
#घोषणा QSFP_HFI0_RESET_N   BIT(2)
#घोषणा QSFP_HFI0_INT_N	    BIT(3)
#घोषणा QSFP_HFI0_MODPRST_N BIT(4)

/* QSFP is paged at 256 bytes */
#घोषणा QSFP_PAGESIZE 256
/* Reads/ग_लिखोs cannot cross 128 byte boundaries */
#घोषणा QSFP_RW_BOUNDARY 128

/* number of bytes in i2c offset क्रम QSFP devices */
#घोषणा __QSFP_OFFSET_SIZE 1                           /* num address bytes */
#घोषणा QSFP_OFFSET_SIZE (__QSFP_OFFSET_SIZE << 8)     /* shअगरted value */

/* Defined fields that Intel requires of qualअगरied cables */
/* Byte 0 is Identअगरier, not checked */
/* Byte 1 is reserved "status MSB" */
#घोषणा QSFP_MONITOR_VAL_START 22
#घोषणा QSFP_MONITOR_VAL_END 81
#घोषणा QSFP_MONITOR_RANGE (QSFP_MONITOR_VAL_END - QSFP_MONITOR_VAL_START + 1)
#घोषणा QSFP_TX_CTRL_BYTE_OFFS 86
#घोषणा QSFP_PWR_CTRL_BYTE_OFFS 93
#घोषणा QSFP_CDR_CTRL_BYTE_OFFS 98

#घोषणा QSFP_PAGE_SELECT_BYTE_OFFS 127
/* Byte 128 is Identअगरier: must be 0x0c क्रम QSFP, or 0x0d क्रम QSFP+ */
#घोषणा QSFP_MOD_ID_OFFS 128
/*
 * Byte 129 is "Extended Identifier".
 * For bits [7:6]: 0:1.5W, 1:2.0W, 2:2.5W, 3:3.5W
 * For bits [1:0]: 0:Unused, 1:4W, 2:4.5W, 3:5W
 */
#घोषणा QSFP_MOD_PWR_OFFS 129
/* Byte 130 is Connector type. Not Intel req'd */
/* Bytes 131..138 are Transceiver types, bit maps क्रम various tech, none IB */
/* Byte 139 is encoding. code 0x01 is 8b10b. Not Intel req'd */
/* byte 140 is nominal bit-rate, in units of 100Mbits/sec */
#घोषणा QSFP_NOM_BIT_RATE_100_OFFS 140
/* Byte 141 is Extended Rate Select. Not Intel req'd */
/* Bytes 142..145 are lengths क्रम various fiber types. Not Intel req'd */
/* Byte 146 is length क्रम Copper. Units of 1 meter */
#घोषणा QSFP_MOD_LEN_OFFS 146
/*
 * Byte 147 is Device technology. D0..3 not Intel req'd
 * D4..7 select from 15 choices, translated by table:
 */
#घोषणा QSFP_MOD_TECH_OFFS 147
बाह्य स्थिर अक्षर *स्थिर hfi1_qsfp_devtech[16];
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
/* Byte 164 is IB Extended transceiver codes Bits D0..3 are SDR,DDR,QDR,EDR */
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
 * Bytes 186,187 are Wavelength, अगर Optical. Not Intel req'd
 *  If copper, they are attenuation in dB:
 * Byte 186 is at 2.5Gb/sec (SDR), Byte 187 at 5.0Gb/sec (DDR)
 */
#घोषणा QSFP_ATTEN_OFFS 186
#घोषणा QSFP_ATTEN_LEN 2
/*
 * Bytes 188,189 are Wavelength tolerance, अगर optical
 * If copper, they are attenuation in dB:
 * Byte 188 is at 12.5 Gb/s, Byte 189 at 25 Gb/s
 */
#घोषणा QSFP_CU_ATTEN_7G_OFFS 188
#घोषणा QSFP_CU_ATTEN_12G_OFFS 189
/* Byte 190 is Max Case Temp. Not Intel req'd */
/* Byte 191 is LSB of sum of bytes 128..190. Not Intel req'd */
#घोषणा QSFP_CC_OFFS 191
#घोषणा QSFP_EQ_INFO_OFFS 193
#घोषणा QSFP_CDR_INFO_OFFS 194
/* Bytes 196..211 are Serial Number, String */
#घोषणा QSFP_SN_OFFS 196
#घोषणा QSFP_SN_LEN 16
/* Bytes 212..219 are date-code YYMMDD (MM==1 क्रम Jan) */
#घोषणा QSFP_DATE_OFFS 212
#घोषणा QSFP_DATE_LEN 6
/* Bytes 218,219 are optional lot-code, string */
#घोषणा QSFP_LOT_OFFS 218
#घोषणा QSFP_LOT_LEN 2
/* Bytes 220, 221 indicate monitoring options, Not Intel req'd */
/* Byte 222 indicates nominal bitrate in units of 250Mbits/sec */
#घोषणा QSFP_NOM_BIT_RATE_250_OFFS 222
/* Byte 223 is LSB of sum of bytes 192..222 */
#घोषणा QSFP_CC_EXT_OFFS 223

/*
 * Interrupt flag masks
 */
#घोषणा QSFP_DATA_NOT_READY		0x01

#घोषणा QSFP_HIGH_TEMP_ALARM		0x80
#घोषणा QSFP_LOW_TEMP_ALARM		0x40
#घोषणा QSFP_HIGH_TEMP_WARNING		0x20
#घोषणा QSFP_LOW_TEMP_WARNING		0x10

#घोषणा QSFP_HIGH_VCC_ALARM		0x80
#घोषणा QSFP_LOW_VCC_ALARM		0x40
#घोषणा QSFP_HIGH_VCC_WARNING		0x20
#घोषणा QSFP_LOW_VCC_WARNING		0x10

#घोषणा QSFP_HIGH_POWER_ALARM		0x88
#घोषणा QSFP_LOW_POWER_ALARM		0x44
#घोषणा QSFP_HIGH_POWER_WARNING		0x22
#घोषणा QSFP_LOW_POWER_WARNING		0x11

#घोषणा QSFP_HIGH_BIAS_ALARM		0x88
#घोषणा QSFP_LOW_BIAS_ALARM		0x44
#घोषणा QSFP_HIGH_BIAS_WARNING		0x22
#घोषणा QSFP_LOW_BIAS_WARNING		0x11

#घोषणा QSFP_ATTEN_SDR(attenarray) (attenarray[0])
#घोषणा QSFP_ATTEN_DDR(attenarray) (attenarray[1])

/*
 * काष्ठा qsfp_data encapsulates state of QSFP device क्रम one port.
 * it will be part of port-specअगरic data अगर a board supports QSFP.
 *
 * Since multiple board-types use QSFP, and their pport_data काष्ठाs
 * dअगरfer (in the chip-specअगरic section), we need a poपूर्णांकer to its head.
 *
 * Aव्योमing premature optimization, we will have one work_काष्ठा per port,
 * and let the qsfp_lock arbitrate access to common resources.
 *
 */
काष्ठा qsfp_data अणु
	/* Helps to find our way */
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा work_काष्ठा qsfp_work;
	u8 cache[QSFP_MAX_NUM_PAGES * 128];
	/* protect qsfp data */
	spinlock_t qsfp_lock;
	u8 check_पूर्णांकerrupt_flags;
	u8 reset_needed;
	u8 limiting_active;
	u8 cache_valid;
	u8 cache_refresh_required;
पूर्ण;

पूर्णांक refresh_qsfp_cache(काष्ठा hfi1_pportdata *ppd,
		       काष्ठा qsfp_data *cp);
पूर्णांक get_qsfp_घातer_class(u8 घातer_byte);
पूर्णांक qsfp_mod_present(काष्ठा hfi1_pportdata *ppd);
पूर्णांक get_cable_info(काष्ठा hfi1_devdata *dd, u32 port_num, u32 addr,
		   u32 len, u8 *data);

पूर्णांक i2c_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक i2c_addr,
	      पूर्णांक offset, व्योम *bp, पूर्णांक len);
पूर्णांक i2c_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक i2c_addr,
	     पूर्णांक offset, व्योम *bp, पूर्णांक len);
पूर्णांक qsfp_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
	       पूर्णांक len);
पूर्णांक qsfp_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
	      पूर्णांक len);
पूर्णांक one_qsfp_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
		   पूर्णांक len);
पूर्णांक one_qsfp_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
		  पूर्णांक len);
काष्ठा hfi1_asic_data;
पूर्णांक set_up_i2c(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_asic_data *ad);
व्योम clean_up_i2c(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_asic_data *ad);
