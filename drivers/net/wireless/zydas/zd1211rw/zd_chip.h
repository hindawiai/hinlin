<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ZD1211 USB-WLAN driver क्रम Linux
 *
 * Copyright (C) 2005-2007 Ulrich Kunitz <kune@deine-taler.de>
 * Copyright (C) 2006-2007 Daniel Drake <dsd@gentoo.org>
 */

#अगर_अघोषित _ZD_CHIP_H
#घोषणा _ZD_CHIP_H

#समावेश <net/mac80211.h>

#समावेश "zd_rf.h"
#समावेश "zd_usb.h"

/* Header क्रम the Media Access Controller (MAC) and the Baseband Processor
 * (BBP). It appears that the ZD1211 wraps the old ZD1205 with USB glue and
 * adds a processor क्रम handling the USB protocol.
 */

/* Address space */
क्रमागत अणु
	/* CONTROL REGISTERS */
	CR_START			= 0x9000,


	/* FIRMWARE */
	FW_START			= 0xee00,


	/* EEPROM */
	E2P_START			= 0xf800,
	E2P_LEN				= 0x800,

	/* EEPROM layout */
	E2P_LOAD_CODE_LEN		= 0xe,		/* base 0xf800 */
	E2P_LOAD_VECT_LEN		= 0x9,		/* base 0xf80e */
	/* E2P_DATA indexes पूर्णांकo this */
	E2P_DATA_LEN			= 0x7e,		/* base 0xf817 */
	E2P_BOOT_CODE_LEN		= 0x760,	/* base 0xf895 */
	E2P_INTR_VECT_LEN		= 0xb,		/* base 0xfff5 */

	/* Some precomputed offsets पूर्णांकo the EEPROM */
	E2P_DATA_OFFSET			= E2P_LOAD_CODE_LEN + E2P_LOAD_VECT_LEN,
	E2P_BOOT_CODE_OFFSET		= E2P_DATA_OFFSET + E2P_DATA_LEN,
पूर्ण;

#घोषणा CTL_REG(offset) ((zd_addr_t)(CR_START + (offset)))
#घोषणा E2P_DATA(offset) ((zd_addr_t)(E2P_START + E2P_DATA_OFFSET + (offset)))
#घोषणा FWRAW_DATA(offset) ((zd_addr_t)(FW_START + (offset)))

/* 8-bit hardware रेजिस्टरs */
#घोषणा ZD_CR0   CTL_REG(0x0000)
#घोषणा ZD_CR1   CTL_REG(0x0004)
#घोषणा ZD_CR2   CTL_REG(0x0008)
#घोषणा ZD_CR3   CTL_REG(0x000C)

#घोषणा ZD_CR5   CTL_REG(0x0010)
/*	bit 5: अगर set लघु preamble used
 *	bit 6: filter band - Japan channel 14 on, अन्यथा off
 */
#घोषणा ZD_CR6   CTL_REG(0x0014)
#घोषणा ZD_CR7   CTL_REG(0x0018)
#घोषणा ZD_CR8   CTL_REG(0x001C)

#घोषणा ZD_CR4   CTL_REG(0x0020)

#घोषणा ZD_CR9   CTL_REG(0x0024)
/*	bit 2: antenna चयन (together with ZD_CR10) */
#घोषणा ZD_CR10  CTL_REG(0x0028)
/*	bit 1: antenna चयन (together with ZD_CR9)
 *	RF2959 controls with ZD_CR11 radion on and off
 */
#घोषणा ZD_CR11  CTL_REG(0x002C)
/*	bit 6:  TX घातer control क्रम OFDM
 *	RF2959 controls with ZD_CR10 radio on and off
 */
#घोषणा ZD_CR12  CTL_REG(0x0030)
#घोषणा ZD_CR13  CTL_REG(0x0034)
#घोषणा ZD_CR14  CTL_REG(0x0038)
#घोषणा ZD_CR15  CTL_REG(0x003C)
#घोषणा ZD_CR16  CTL_REG(0x0040)
#घोषणा ZD_CR17  CTL_REG(0x0044)
#घोषणा ZD_CR18  CTL_REG(0x0048)
#घोषणा ZD_CR19  CTL_REG(0x004C)
#घोषणा ZD_CR20  CTL_REG(0x0050)
#घोषणा ZD_CR21  CTL_REG(0x0054)
#घोषणा ZD_CR22  CTL_REG(0x0058)
#घोषणा ZD_CR23  CTL_REG(0x005C)
#घोषणा ZD_CR24  CTL_REG(0x0060)	/* CCA threshold */
#घोषणा ZD_CR25  CTL_REG(0x0064)
#घोषणा ZD_CR26  CTL_REG(0x0068)
#घोषणा ZD_CR27  CTL_REG(0x006C)
#घोषणा ZD_CR28  CTL_REG(0x0070)
#घोषणा ZD_CR29  CTL_REG(0x0074)
#घोषणा ZD_CR30  CTL_REG(0x0078)
#घोषणा ZD_CR31  CTL_REG(0x007C)	/* TX घातer control क्रम RF in
					 * CCK mode
					 */
#घोषणा ZD_CR32  CTL_REG(0x0080)
#घोषणा ZD_CR33  CTL_REG(0x0084)
#घोषणा ZD_CR34  CTL_REG(0x0088)
#घोषणा ZD_CR35  CTL_REG(0x008C)
#घोषणा ZD_CR36  CTL_REG(0x0090)
#घोषणा ZD_CR37  CTL_REG(0x0094)
#घोषणा ZD_CR38  CTL_REG(0x0098)
#घोषणा ZD_CR39  CTL_REG(0x009C)
#घोषणा ZD_CR40  CTL_REG(0x00A0)
#घोषणा ZD_CR41  CTL_REG(0x00A4)
#घोषणा ZD_CR42  CTL_REG(0x00A8)
#घोषणा ZD_CR43  CTL_REG(0x00AC)
#घोषणा ZD_CR44  CTL_REG(0x00B0)
#घोषणा ZD_CR45  CTL_REG(0x00B4)
#घोषणा ZD_CR46  CTL_REG(0x00B8)
#घोषणा ZD_CR47  CTL_REG(0x00BC)	/* CCK baseband gain
					 * (patch value might be in EEPROM)
					 */
#घोषणा ZD_CR48  CTL_REG(0x00C0)
#घोषणा ZD_CR49  CTL_REG(0x00C4)
#घोषणा ZD_CR50  CTL_REG(0x00C8)
#घोषणा ZD_CR51  CTL_REG(0x00CC)	/* TX घातer control क्रम RF in
					 * 6-36M modes
					 */
#घोषणा ZD_CR52  CTL_REG(0x00D0)	/* TX घातer control क्रम RF in
					 * 48M mode
					 */
#घोषणा ZD_CR53  CTL_REG(0x00D4)	/* TX घातer control क्रम RF in
					 * 54M mode
					 */
#घोषणा ZD_CR54  CTL_REG(0x00D8)
#घोषणा ZD_CR55  CTL_REG(0x00DC)
#घोषणा ZD_CR56  CTL_REG(0x00E0)
#घोषणा ZD_CR57  CTL_REG(0x00E4)
#घोषणा ZD_CR58  CTL_REG(0x00E8)
#घोषणा ZD_CR59  CTL_REG(0x00EC)
#घोषणा ZD_CR60  CTL_REG(0x00F0)
#घोषणा ZD_CR61  CTL_REG(0x00F4)
#घोषणा ZD_CR62  CTL_REG(0x00F8)
#घोषणा ZD_CR63  CTL_REG(0x00FC)
#घोषणा ZD_CR64  CTL_REG(0x0100)
#घोषणा ZD_CR65  CTL_REG(0x0104) /* OFDM 54M calibration */
#घोषणा ZD_CR66  CTL_REG(0x0108) /* OFDM 48M calibration */
#घोषणा ZD_CR67  CTL_REG(0x010C) /* OFDM 36M calibration */
#घोषणा ZD_CR68  CTL_REG(0x0110) /* CCK calibration */
#घोषणा ZD_CR69  CTL_REG(0x0114)
#घोषणा ZD_CR70  CTL_REG(0x0118)
#घोषणा ZD_CR71  CTL_REG(0x011C)
#घोषणा ZD_CR72  CTL_REG(0x0120)
#घोषणा ZD_CR73  CTL_REG(0x0124)
#घोषणा ZD_CR74  CTL_REG(0x0128)
#घोषणा ZD_CR75  CTL_REG(0x012C)
#घोषणा ZD_CR76  CTL_REG(0x0130)
#घोषणा ZD_CR77  CTL_REG(0x0134)
#घोषणा ZD_CR78  CTL_REG(0x0138)
#घोषणा ZD_CR79  CTL_REG(0x013C)
#घोषणा ZD_CR80  CTL_REG(0x0140)
#घोषणा ZD_CR81  CTL_REG(0x0144)
#घोषणा ZD_CR82  CTL_REG(0x0148)
#घोषणा ZD_CR83  CTL_REG(0x014C)
#घोषणा ZD_CR84  CTL_REG(0x0150)
#घोषणा ZD_CR85  CTL_REG(0x0154)
#घोषणा ZD_CR86  CTL_REG(0x0158)
#घोषणा ZD_CR87  CTL_REG(0x015C)
#घोषणा ZD_CR88  CTL_REG(0x0160)
#घोषणा ZD_CR89  CTL_REG(0x0164)
#घोषणा ZD_CR90  CTL_REG(0x0168)
#घोषणा ZD_CR91  CTL_REG(0x016C)
#घोषणा ZD_CR92  CTL_REG(0x0170)
#घोषणा ZD_CR93  CTL_REG(0x0174)
#घोषणा ZD_CR94  CTL_REG(0x0178)
#घोषणा ZD_CR95  CTL_REG(0x017C)
#घोषणा ZD_CR96  CTL_REG(0x0180)
#घोषणा ZD_CR97  CTL_REG(0x0184)
#घोषणा ZD_CR98  CTL_REG(0x0188)
#घोषणा ZD_CR99  CTL_REG(0x018C)
#घोषणा ZD_CR100 CTL_REG(0x0190)
#घोषणा ZD_CR101 CTL_REG(0x0194)
#घोषणा ZD_CR102 CTL_REG(0x0198)
#घोषणा ZD_CR103 CTL_REG(0x019C)
#घोषणा ZD_CR104 CTL_REG(0x01A0)
#घोषणा ZD_CR105 CTL_REG(0x01A4)
#घोषणा ZD_CR106 CTL_REG(0x01A8)
#घोषणा ZD_CR107 CTL_REG(0x01AC)
#घोषणा ZD_CR108 CTL_REG(0x01B0)
#घोषणा ZD_CR109 CTL_REG(0x01B4)
#घोषणा ZD_CR110 CTL_REG(0x01B8)
#घोषणा ZD_CR111 CTL_REG(0x01BC)
#घोषणा ZD_CR112 CTL_REG(0x01C0)
#घोषणा ZD_CR113 CTL_REG(0x01C4)
#घोषणा ZD_CR114 CTL_REG(0x01C8)
#घोषणा ZD_CR115 CTL_REG(0x01CC)
#घोषणा ZD_CR116 CTL_REG(0x01D0)
#घोषणा ZD_CR117 CTL_REG(0x01D4)
#घोषणा ZD_CR118 CTL_REG(0x01D8)
#घोषणा ZD_CR119 CTL_REG(0x01DC)
#घोषणा ZD_CR120 CTL_REG(0x01E0)
#घोषणा ZD_CR121 CTL_REG(0x01E4)
#घोषणा ZD_CR122 CTL_REG(0x01E8)
#घोषणा ZD_CR123 CTL_REG(0x01EC)
#घोषणा ZD_CR124 CTL_REG(0x01F0)
#घोषणा ZD_CR125 CTL_REG(0x01F4)
#घोषणा ZD_CR126 CTL_REG(0x01F8)
#घोषणा ZD_CR127 CTL_REG(0x01FC)
#घोषणा ZD_CR128 CTL_REG(0x0200)
#घोषणा ZD_CR129 CTL_REG(0x0204)
#घोषणा ZD_CR130 CTL_REG(0x0208)
#घोषणा ZD_CR131 CTL_REG(0x020C)
#घोषणा ZD_CR132 CTL_REG(0x0210)
#घोषणा ZD_CR133 CTL_REG(0x0214)
#घोषणा ZD_CR134 CTL_REG(0x0218)
#घोषणा ZD_CR135 CTL_REG(0x021C)
#घोषणा ZD_CR136 CTL_REG(0x0220)
#घोषणा ZD_CR137 CTL_REG(0x0224)
#घोषणा ZD_CR138 CTL_REG(0x0228)
#घोषणा ZD_CR139 CTL_REG(0x022C)
#घोषणा ZD_CR140 CTL_REG(0x0230)
#घोषणा ZD_CR141 CTL_REG(0x0234)
#घोषणा ZD_CR142 CTL_REG(0x0238)
#घोषणा ZD_CR143 CTL_REG(0x023C)
#घोषणा ZD_CR144 CTL_REG(0x0240)
#घोषणा ZD_CR145 CTL_REG(0x0244)
#घोषणा ZD_CR146 CTL_REG(0x0248)
#घोषणा ZD_CR147 CTL_REG(0x024C)
#घोषणा ZD_CR148 CTL_REG(0x0250)
#घोषणा ZD_CR149 CTL_REG(0x0254)
#घोषणा ZD_CR150 CTL_REG(0x0258)
#घोषणा ZD_CR151 CTL_REG(0x025C)
#घोषणा ZD_CR152 CTL_REG(0x0260)
#घोषणा ZD_CR153 CTL_REG(0x0264)
#घोषणा ZD_CR154 CTL_REG(0x0268)
#घोषणा ZD_CR155 CTL_REG(0x026C)
#घोषणा ZD_CR156 CTL_REG(0x0270)
#घोषणा ZD_CR157 CTL_REG(0x0274)
#घोषणा ZD_CR158 CTL_REG(0x0278)
#घोषणा ZD_CR159 CTL_REG(0x027C)
#घोषणा ZD_CR160 CTL_REG(0x0280)
#घोषणा ZD_CR161 CTL_REG(0x0284)
#घोषणा ZD_CR162 CTL_REG(0x0288)
#घोषणा ZD_CR163 CTL_REG(0x028C)
#घोषणा ZD_CR164 CTL_REG(0x0290)
#घोषणा ZD_CR165 CTL_REG(0x0294)
#घोषणा ZD_CR166 CTL_REG(0x0298)
#घोषणा ZD_CR167 CTL_REG(0x029C)
#घोषणा ZD_CR168 CTL_REG(0x02A0)
#घोषणा ZD_CR169 CTL_REG(0x02A4)
#घोषणा ZD_CR170 CTL_REG(0x02A8)
#घोषणा ZD_CR171 CTL_REG(0x02AC)
#घोषणा ZD_CR172 CTL_REG(0x02B0)
#घोषणा ZD_CR173 CTL_REG(0x02B4)
#घोषणा ZD_CR174 CTL_REG(0x02B8)
#घोषणा ZD_CR175 CTL_REG(0x02BC)
#घोषणा ZD_CR176 CTL_REG(0x02C0)
#घोषणा ZD_CR177 CTL_REG(0x02C4)
#घोषणा ZD_CR178 CTL_REG(0x02C8)
#घोषणा ZD_CR179 CTL_REG(0x02CC)
#घोषणा ZD_CR180 CTL_REG(0x02D0)
#घोषणा ZD_CR181 CTL_REG(0x02D4)
#घोषणा ZD_CR182 CTL_REG(0x02D8)
#घोषणा ZD_CR183 CTL_REG(0x02DC)
#घोषणा ZD_CR184 CTL_REG(0x02E0)
#घोषणा ZD_CR185 CTL_REG(0x02E4)
#घोषणा ZD_CR186 CTL_REG(0x02E8)
#घोषणा ZD_CR187 CTL_REG(0x02EC)
#घोषणा ZD_CR188 CTL_REG(0x02F0)
#घोषणा ZD_CR189 CTL_REG(0x02F4)
#घोषणा ZD_CR190 CTL_REG(0x02F8)
#घोषणा ZD_CR191 CTL_REG(0x02FC)
#घोषणा ZD_CR192 CTL_REG(0x0300)
#घोषणा ZD_CR193 CTL_REG(0x0304)
#घोषणा ZD_CR194 CTL_REG(0x0308)
#घोषणा ZD_CR195 CTL_REG(0x030C)
#घोषणा ZD_CR196 CTL_REG(0x0310)
#घोषणा ZD_CR197 CTL_REG(0x0314)
#घोषणा ZD_CR198 CTL_REG(0x0318)
#घोषणा ZD_CR199 CTL_REG(0x031C)
#घोषणा ZD_CR200 CTL_REG(0x0320)
#घोषणा ZD_CR201 CTL_REG(0x0324)
#घोषणा ZD_CR202 CTL_REG(0x0328)
#घोषणा ZD_CR203 CTL_REG(0x032C)	/* I2C bus ढाँचा value & flash
					 * control
					 */
#घोषणा ZD_CR204 CTL_REG(0x0330)
#घोषणा ZD_CR205 CTL_REG(0x0334)
#घोषणा ZD_CR206 CTL_REG(0x0338)
#घोषणा ZD_CR207 CTL_REG(0x033C)
#घोषणा ZD_CR208 CTL_REG(0x0340)
#घोषणा ZD_CR209 CTL_REG(0x0344)
#घोषणा ZD_CR210 CTL_REG(0x0348)
#घोषणा ZD_CR211 CTL_REG(0x034C)
#घोषणा ZD_CR212 CTL_REG(0x0350)
#घोषणा ZD_CR213 CTL_REG(0x0354)
#घोषणा ZD_CR214 CTL_REG(0x0358)
#घोषणा ZD_CR215 CTL_REG(0x035C)
#घोषणा ZD_CR216 CTL_REG(0x0360)
#घोषणा ZD_CR217 CTL_REG(0x0364)
#घोषणा ZD_CR218 CTL_REG(0x0368)
#घोषणा ZD_CR219 CTL_REG(0x036C)
#घोषणा ZD_CR220 CTL_REG(0x0370)
#घोषणा ZD_CR221 CTL_REG(0x0374)
#घोषणा ZD_CR222 CTL_REG(0x0378)
#घोषणा ZD_CR223 CTL_REG(0x037C)
#घोषणा ZD_CR224 CTL_REG(0x0380)
#घोषणा ZD_CR225 CTL_REG(0x0384)
#घोषणा ZD_CR226 CTL_REG(0x0388)
#घोषणा ZD_CR227 CTL_REG(0x038C)
#घोषणा ZD_CR228 CTL_REG(0x0390)
#घोषणा ZD_CR229 CTL_REG(0x0394)
#घोषणा ZD_CR230 CTL_REG(0x0398)
#घोषणा ZD_CR231 CTL_REG(0x039C)
#घोषणा ZD_CR232 CTL_REG(0x03A0)
#घोषणा ZD_CR233 CTL_REG(0x03A4)
#घोषणा ZD_CR234 CTL_REG(0x03A8)
#घोषणा ZD_CR235 CTL_REG(0x03AC)
#घोषणा ZD_CR236 CTL_REG(0x03B0)

#घोषणा ZD_CR240 CTL_REG(0x03C0)
/*             bit 7: host-controlled RF रेजिस्टर ग_लिखोs
 * ZD_CR241-ZD_CR245: क्रम hardware controlled writing of RF bits, not needed क्रम
 *                    USB
 */
#घोषणा ZD_CR241 CTL_REG(0x03C4)
#घोषणा ZD_CR242 CTL_REG(0x03C8)
#घोषणा ZD_CR243 CTL_REG(0x03CC)
#घोषणा ZD_CR244 CTL_REG(0x03D0)
#घोषणा ZD_CR245 CTL_REG(0x03D4)

#घोषणा ZD_CR251 CTL_REG(0x03EC)	/* only used क्रम activation and
					 * deactivation of Airoha RFs AL2230
					 * and AL7230B
					 */
#घोषणा ZD_CR252 CTL_REG(0x03F0)
#घोषणा ZD_CR253 CTL_REG(0x03F4)
#घोषणा ZD_CR254 CTL_REG(0x03F8)
#घोषणा ZD_CR255 CTL_REG(0x03FC)

#घोषणा CR_MAX_PHY_REG 255

/* Taken from the ZYDAS driver, not all of them are relevant क्रम the ZD1211
 * driver.
 */

#घोषणा CR_RF_IF_CLK			CTL_REG(0x0400)
#घोषणा CR_RF_IF_DATA			CTL_REG(0x0404)
#घोषणा CR_PE1_PE2			CTL_REG(0x0408)
#घोषणा CR_PE2_DLY			CTL_REG(0x040C)
#घोषणा CR_LE1				CTL_REG(0x0410)
#घोषणा CR_LE2				CTL_REG(0x0414)
/* Seems to enable/disable GPI (General Purpose IO?) */
#घोषणा CR_GPI_EN			CTL_REG(0x0418)
#घोषणा CR_RADIO_PD			CTL_REG(0x042C)
#घोषणा CR_RF2948_PD			CTL_REG(0x042C)
#घोषणा CR_ENABLE_PS_MANUAL_AGC		CTL_REG(0x043C)
#घोषणा CR_CONFIG_PHILIPS		CTL_REG(0x0440)
#घोषणा CR_SA2400_SER_AP		CTL_REG(0x0444)
#घोषणा CR_I2C_WRITE			CTL_REG(0x0444)
#घोषणा CR_SA2400_SER_RP		CTL_REG(0x0448)
#घोषणा CR_RADIO_PE			CTL_REG(0x0458)
#घोषणा CR_RST_BUS_MASTER		CTL_REG(0x045C)
#घोषणा CR_RFCFG			CTL_REG(0x0464)
#घोषणा CR_HSTSCHG			CTL_REG(0x046C)
#घोषणा CR_PHY_ON			CTL_REG(0x0474)
#घोषणा CR_RX_DELAY			CTL_REG(0x0478)
#घोषणा CR_RX_PE_DELAY			CTL_REG(0x047C)
#घोषणा CR_GPIO_1			CTL_REG(0x0490)
#घोषणा CR_GPIO_2			CTL_REG(0x0494)
#घोषणा CR_EncryBufMux			CTL_REG(0x04A8)
#घोषणा CR_PS_CTRL			CTL_REG(0x0500)
#घोषणा CR_ADDA_PWR_DWN			CTL_REG(0x0504)
#घोषणा CR_ADDA_MBIAS_WARMTIME		CTL_REG(0x0508)
#घोषणा CR_MAC_PS_STATE			CTL_REG(0x050C)

#घोषणा CR_INTERRUPT			CTL_REG(0x0510)
#घोषणा INT_TX_COMPLETE			(1 <<  0)
#घोषणा INT_RX_COMPLETE			(1 <<  1)
#घोषणा INT_RETRY_FAIL			(1 <<  2)
#घोषणा INT_WAKEUP			(1 <<  3)
#घोषणा INT_DTIM_NOTIFY			(1 <<  5)
#घोषणा INT_CFG_NEXT_BCN		(1 <<  6)
#घोषणा INT_BUS_ABORT			(1 <<  7)
#घोषणा INT_TX_FIFO_READY		(1 <<  8)
#घोषणा INT_UART			(1 <<  9)
#घोषणा INT_TX_COMPLETE_EN		(1 << 16)
#घोषणा INT_RX_COMPLETE_EN		(1 << 17)
#घोषणा INT_RETRY_FAIL_EN		(1 << 18)
#घोषणा INT_WAKEUP_EN			(1 << 19)
#घोषणा INT_DTIM_NOTIFY_EN		(1 << 21)
#घोषणा INT_CFG_NEXT_BCN_EN		(1 << 22)
#घोषणा INT_BUS_ABORT_EN		(1 << 23)
#घोषणा INT_TX_FIFO_READY_EN		(1 << 24)
#घोषणा INT_UART_EN			(1 << 25)

#घोषणा CR_TSF_LOW_PART			CTL_REG(0x0514)
#घोषणा CR_TSF_HIGH_PART		CTL_REG(0x0518)

/* Following three values are in समय units (1024us)
 * Following condition must be met:
 * atim < tbtt < bcn
 */
#घोषणा CR_ATIM_WND_PERIOD		CTL_REG(0x051C)
#घोषणा CR_BCN_INTERVAL			CTL_REG(0x0520)
#घोषणा CR_PRE_TBTT			CTL_REG(0x0524)
/* in units of TU(1024us) */

/* क्रम UART support */
#घोषणा CR_UART_RBR_THR_DLL		CTL_REG(0x0540)
#घोषणा CR_UART_DLM_IER			CTL_REG(0x0544)
#घोषणा CR_UART_IIR_FCR			CTL_REG(0x0548)
#घोषणा CR_UART_LCR			CTL_REG(0x054c)
#घोषणा CR_UART_MCR			CTL_REG(0x0550)
#घोषणा CR_UART_LSR			CTL_REG(0x0554)
#घोषणा CR_UART_MSR			CTL_REG(0x0558)
#घोषणा CR_UART_ECR			CTL_REG(0x055c)
#घोषणा CR_UART_STATUS			CTL_REG(0x0560)

#घोषणा CR_PCI_TX_ADDR_P1		CTL_REG(0x0600)
#घोषणा CR_PCI_TX_AddR_P2		CTL_REG(0x0604)
#घोषणा CR_PCI_RX_AddR_P1		CTL_REG(0x0608)
#घोषणा CR_PCI_RX_AddR_P2		CTL_REG(0x060C)

/* must be overwritten अगर custom MAC address will be used */
#घोषणा CR_MAC_ADDR_P1			CTL_REG(0x0610)
#घोषणा CR_MAC_ADDR_P2			CTL_REG(0x0614)
#घोषणा CR_BSSID_P1			CTL_REG(0x0618)
#घोषणा CR_BSSID_P2			CTL_REG(0x061C)
#घोषणा CR_BCN_PLCP_CFG			CTL_REG(0x0620)

/* Group hash table क्रम filtering incoming packets.
 *
 * The group hash table is 64 bit large and split over two parts. The first
 * part is the lower part. The upper 6 bits of the last byte of the target
 * address are used as index. Packets are received अगर the hash table bit is
 * set. This is used क्रम multicast handling, but क्रम broadcasts (address
 * ff:ff:ff:ff:ff:ff) the highest bit in the second table must also be set.
 */
#घोषणा CR_GROUP_HASH_P1		CTL_REG(0x0624)
#घोषणा CR_GROUP_HASH_P2		CTL_REG(0x0628)

#घोषणा CR_RX_TIMEOUT			CTL_REG(0x062C)

/* Basic rates supported by the BSS. When producing ACK or CTS messages, the
 * device will use a rate in this table that is less than or equal to the rate
 * of the incoming frame which prompted the response. */
#घोषणा CR_BASIC_RATE_TBL		CTL_REG(0x0630)
#घोषणा CR_RATE_1M	(1 <<  0)	/* 802.11b */
#घोषणा CR_RATE_2M	(1 <<  1)	/* 802.11b */
#घोषणा CR_RATE_5_5M	(1 <<  2)	/* 802.11b */
#घोषणा CR_RATE_11M	(1 <<  3)	/* 802.11b */
#घोषणा CR_RATE_6M      (1 <<  8)	/* 802.11g */
#घोषणा CR_RATE_9M      (1 <<  9)	/* 802.11g */
#घोषणा CR_RATE_12M	(1 << 10)	/* 802.11g */
#घोषणा CR_RATE_18M	(1 << 11)	/* 802.11g */
#घोषणा CR_RATE_24M     (1 << 12)	/* 802.11g */
#घोषणा CR_RATE_36M     (1 << 13)	/* 802.11g */
#घोषणा CR_RATE_48M     (1 << 14)	/* 802.11g */
#घोषणा CR_RATE_54M     (1 << 15)	/* 802.11g */
#घोषणा CR_RATES_80211G	0xff00
#घोषणा CR_RATES_80211B	0x000f

/* Mandatory rates required in the BSS. When producing ACK or CTS messages, अगर
 * the device could not find an appropriate rate in CR_BASIC_RATE_TBL, it will
 * look क्रम a rate in this table that is less than or equal to the rate of
 * the incoming frame. */
#घोषणा CR_MANDATORY_RATE_TBL		CTL_REG(0x0634)
#घोषणा CR_RTS_CTS_RATE			CTL_REG(0x0638)

/* These are all bit indexes in CR_RTS_CTS_RATE, so remember to shअगरt. */
#घोषणा RTSCTS_SH_RTS_RATE		0
#घोषणा RTSCTS_SH_EXP_CTS_RATE		4
#घोषणा RTSCTS_SH_RTS_MOD_TYPE		8
#घोषणा RTSCTS_SH_RTS_PMB_TYPE		9
#घोषणा RTSCTS_SH_CTS_RATE		16
#घोषणा RTSCTS_SH_CTS_MOD_TYPE		24
#घोषणा RTSCTS_SH_CTS_PMB_TYPE		25

#घोषणा CR_WEP_PROTECT			CTL_REG(0x063C)
#घोषणा CR_RX_THRESHOLD			CTL_REG(0x0640)

/* रेजिस्टर क्रम controlling the LEDS */
#घोषणा CR_LED				CTL_REG(0x0644)
/* masks क्रम controlling LEDs */
#घोषणा LED1				(1 <<  8)
#घोषणा LED2				(1 <<  9)
#घोषणा LED_SW				(1 << 10)

/* Seems to indicate that the configuration is over.
 */
#घोषणा CR_AFTER_PNP			CTL_REG(0x0648)
#घोषणा CR_ACK_TIME_80211		CTL_REG(0x0658)

#घोषणा CR_RX_OFFSET			CTL_REG(0x065c)

#घोषणा CR_BCN_LENGTH			CTL_REG(0x0664)
#घोषणा CR_PHY_DELAY			CTL_REG(0x066C)
#घोषणा CR_BCN_FIFO			CTL_REG(0x0670)
#घोषणा CR_SNIFFER_ON			CTL_REG(0x0674)

#घोषणा CR_ENCRYPTION_TYPE		CTL_REG(0x0678)
#घोषणा NO_WEP				0
#घोषणा WEP64				1
#घोषणा WEP128				5
#घोषणा WEP256				6
#घोषणा ENC_SNIFFER			8

#घोषणा CR_ZD1211_RETRY_MAX		CTL_REG(0x067C)

#घोषणा CR_REG1				CTL_REG(0x0680)
/* Setting the bit UNLOCK_PHY_REGS disallows the ग_लिखो access to physical
 * रेजिस्टरs, so one could argue it is a LOCK bit. But calling it
 * LOCK_PHY_REGS makes it confusing.
 */
#घोषणा UNLOCK_PHY_REGS			(1 << 7)

#घोषणा CR_DEVICE_STATE			CTL_REG(0x0684)
#घोषणा CR_UNDERRUN_CNT			CTL_REG(0x0688)

#घोषणा CR_RX_FILTER			CTL_REG(0x068c)
#घोषणा RX_FILTER_ASSOC_REQUEST		(1 <<  0)
#घोषणा RX_FILTER_ASSOC_RESPONSE	(1 <<  1)
#घोषणा RX_FILTER_REASSOC_REQUEST	(1 <<  2)
#घोषणा RX_FILTER_REASSOC_RESPONSE	(1 <<  3)
#घोषणा RX_FILTER_PROBE_REQUEST		(1 <<  4)
#घोषणा RX_FILTER_PROBE_RESPONSE	(1 <<  5)
/* bits 6 and 7 reserved */
#घोषणा RX_FILTER_BEACON		(1 <<  8)
#घोषणा RX_FILTER_ATIM			(1 <<  9)
#घोषणा RX_FILTER_DISASSOC		(1 << 10)
#घोषणा RX_FILTER_AUTH			(1 << 11)
#घोषणा RX_FILTER_DEAUTH		(1 << 12)
#घोषणा RX_FILTER_PSPOLL		(1 << 26)
#घोषणा RX_FILTER_RTS			(1 << 27)
#घोषणा RX_FILTER_CTS			(1 << 28)
#घोषणा RX_FILTER_ACK			(1 << 29)
#घोषणा RX_FILTER_CFEND			(1 << 30)
#घोषणा RX_FILTER_CFACK			(1 << 31)

/* Enable bits क्रम all frames you are पूर्णांकerested in. */
#घोषणा STA_RX_FILTER	(RX_FILTER_ASSOC_REQUEST | RX_FILTER_ASSOC_RESPONSE | \
	RX_FILTER_REASSOC_REQUEST | RX_FILTER_REASSOC_RESPONSE | \
	RX_FILTER_PROBE_REQUEST | RX_FILTER_PROBE_RESPONSE | \
	(0x3 << 6) /* venकरोr driver sets these reserved bits */ | \
	RX_FILTER_BEACON | RX_FILTER_ATIM | RX_FILTER_DISASSOC | \
	RX_FILTER_AUTH | RX_FILTER_DEAUTH | \
	(0x7 << 13) /* venकरोr driver sets these reserved bits */ | \
	RX_FILTER_PSPOLL | RX_FILTER_ACK) /* 0x2400ffff */

#घोषणा RX_FILTER_CTRL (RX_FILTER_RTS | RX_FILTER_CTS | \
	RX_FILTER_CFEND | RX_FILTER_CFACK)

#घोषणा BCN_MODE_AP			0x1000000
#घोषणा BCN_MODE_IBSS			0x2000000

/* Monitor mode sets filter to 0xfffff */

#घोषणा CR_ACK_TIMEOUT_EXT		CTL_REG(0x0690)
#घोषणा CR_BCN_FIFO_SEMAPHORE		CTL_REG(0x0694)

#घोषणा CR_IFS_VALUE			CTL_REG(0x0698)
#घोषणा IFS_VALUE_DIFS_SH		0
#घोषणा IFS_VALUE_EIFS_SH		12
#घोषणा IFS_VALUE_SIFS_SH		24
#घोषणा IFS_VALUE_DEFAULT		((  50 << IFS_VALUE_DIFS_SH) | \
					 (1148 << IFS_VALUE_EIFS_SH) | \
					 (  10 << IFS_VALUE_SIFS_SH))

#घोषणा CR_RX_TIME_OUT			CTL_REG(0x069C)
#घोषणा CR_TOTAL_RX_FRM			CTL_REG(0x06A0)
#घोषणा CR_CRC32_CNT			CTL_REG(0x06A4)
#घोषणा CR_CRC16_CNT			CTL_REG(0x06A8)
#घोषणा CR_DECRYPTION_ERR_UNI		CTL_REG(0x06AC)
#घोषणा CR_RX_FIFO_OVERRUN		CTL_REG(0x06B0)

#घोषणा CR_DECRYPTION_ERR_MUL		CTL_REG(0x06BC)

#घोषणा CR_NAV_CNT			CTL_REG(0x06C4)
#घोषणा CR_NAV_CCA			CTL_REG(0x06C8)
#घोषणा CR_RETRY_CNT			CTL_REG(0x06CC)

#घोषणा CR_READ_TCB_ADDR		CTL_REG(0x06E8)
#घोषणा CR_READ_RFD_ADDR		CTL_REG(0x06EC)
#घोषणा CR_CWMIN_CWMAX			CTL_REG(0x06F0)
#घोषणा CR_TOTAL_TX_FRM			CTL_REG(0x06F4)

/* CAM: Continuous Access Mode (घातer management) */
#घोषणा CR_CAM_MODE			CTL_REG(0x0700)
#घोषणा MODE_IBSS			0x0
#घोषणा MODE_AP				0x1
#घोषणा MODE_STA			0x2
#घोषणा MODE_AP_WDS			0x3

#घोषणा CR_CAM_ROLL_TB_LOW		CTL_REG(0x0704)
#घोषणा CR_CAM_ROLL_TB_HIGH		CTL_REG(0x0708)
#घोषणा CR_CAM_ADDRESS			CTL_REG(0x070C)
#घोषणा CR_CAM_DATA			CTL_REG(0x0710)

#घोषणा CR_ROMसूची			CTL_REG(0x0714)

#घोषणा CR_DECRY_ERR_FLG_LOW		CTL_REG(0x0714)
#घोषणा CR_DECRY_ERR_FLG_HIGH		CTL_REG(0x0718)

#घोषणा CR_WEPKEY0			CTL_REG(0x0720)
#घोषणा CR_WEPKEY1			CTL_REG(0x0724)
#घोषणा CR_WEPKEY2			CTL_REG(0x0728)
#घोषणा CR_WEPKEY3			CTL_REG(0x072C)
#घोषणा CR_WEPKEY4			CTL_REG(0x0730)
#घोषणा CR_WEPKEY5			CTL_REG(0x0734)
#घोषणा CR_WEPKEY6			CTL_REG(0x0738)
#घोषणा CR_WEPKEY7			CTL_REG(0x073C)
#घोषणा CR_WEPKEY8			CTL_REG(0x0740)
#घोषणा CR_WEPKEY9			CTL_REG(0x0744)
#घोषणा CR_WEPKEY10			CTL_REG(0x0748)
#घोषणा CR_WEPKEY11			CTL_REG(0x074C)
#घोषणा CR_WEPKEY12			CTL_REG(0x0750)
#घोषणा CR_WEPKEY13			CTL_REG(0x0754)
#घोषणा CR_WEPKEY14			CTL_REG(0x0758)
#घोषणा CR_WEPKEY15			CTL_REG(0x075c)
#घोषणा CR_TKIP_MODE			CTL_REG(0x0760)

#घोषणा CR_EEPROM_PROTECT0		CTL_REG(0x0758)
#घोषणा CR_EEPROM_PROTECT1		CTL_REG(0x075C)

#घोषणा CR_DBG_FIFO_RD			CTL_REG(0x0800)
#घोषणा CR_DBG_SELECT			CTL_REG(0x0804)
#घोषणा CR_FIFO_Length			CTL_REG(0x0808)


#घोषणा CR_RSSI_MGC			CTL_REG(0x0810)

#घोषणा CR_PON				CTL_REG(0x0818)
#घोषणा CR_RX_ON			CTL_REG(0x081C)
#घोषणा CR_TX_ON			CTL_REG(0x0820)
#घोषणा CR_CHIP_EN			CTL_REG(0x0824)
#घोषणा CR_LO_SW			CTL_REG(0x0828)
#घोषणा CR_TXRX_SW			CTL_REG(0x082C)
#घोषणा CR_S_MD				CTL_REG(0x0830)

#घोषणा CR_USB_DEBUG_PORT		CTL_REG(0x0888)
#घोषणा CR_ZD1211B_CWIN_MAX_MIN_AC0	CTL_REG(0x0b00)
#घोषणा CR_ZD1211B_CWIN_MAX_MIN_AC1	CTL_REG(0x0b04)
#घोषणा CR_ZD1211B_CWIN_MAX_MIN_AC2	CTL_REG(0x0b08)
#घोषणा CR_ZD1211B_CWIN_MAX_MIN_AC3	CTL_REG(0x0b0c)
#घोषणा CR_ZD1211B_AIFS_CTL1		CTL_REG(0x0b10)
#घोषणा CR_ZD1211B_AIFS_CTL2		CTL_REG(0x0b14)
#घोषणा CR_ZD1211B_TXOP			CTL_REG(0x0b20)
#घोषणा CR_ZD1211B_RETRY_MAX		CTL_REG(0x0b28)

/* Value क्रम CR_ZD1211_RETRY_MAX & CR_ZD1211B_RETRY_MAX. Venकरोr driver uses 2,
 * we use 0. The first rate is tried (count+2), then all next rates are tried
 * twice, until 1 Mbits is tried. */
#घोषणा	ZD1211_RETRY_COUNT		0
#घोषणा	ZD1211B_RETRY_COUNT	\
	(ZD1211_RETRY_COUNT <<  0)|	\
	(ZD1211_RETRY_COUNT <<  8)|	\
	(ZD1211_RETRY_COUNT << 16)|	\
	(ZD1211_RETRY_COUNT << 24)

/* Used to detect PLL lock */
#घोषणा UW2453_INTR_REG			((zd_addr_t)0x85c1)

#घोषणा CWIN_SIZE			0x007f043f


#घोषणा HWINT_ENABLED			\
	(INT_TX_COMPLETE_EN|		\
	 INT_RX_COMPLETE_EN|		\
	 INT_RETRY_FAIL_EN|		\
	 INT_WAKEUP_EN|			\
	 INT_CFG_NEXT_BCN_EN)

#घोषणा HWINT_DISABLED			0

#घोषणा E2P_PWR_INT_GUARD		8
#घोषणा E2P_CHANNEL_COUNT		14

/* If you compare this addresses with the ZYDAS orignal driver, please notअगरy
 * that we use word mapping क्रम the EEPROM.
 */

/*
 * Upper 16 bit contains the regulatory करोमुख्य.
 */
#घोषणा E2P_SUBID		E2P_DATA(0x00)
#घोषणा E2P_POD			E2P_DATA(0x02)
#घोषणा E2P_MAC_ADDR_P1		E2P_DATA(0x04)
#घोषणा E2P_MAC_ADDR_P2		E2P_DATA(0x06)
#घोषणा E2P_PWR_CAL_VALUE1	E2P_DATA(0x08)
#घोषणा E2P_PWR_CAL_VALUE2	E2P_DATA(0x0a)
#घोषणा E2P_PWR_CAL_VALUE3	E2P_DATA(0x0c)
#घोषणा E2P_PWR_CAL_VALUE4      E2P_DATA(0x0e)
#घोषणा E2P_PWR_INT_VALUE1	E2P_DATA(0x10)
#घोषणा E2P_PWR_INT_VALUE2	E2P_DATA(0x12)
#घोषणा E2P_PWR_INT_VALUE3	E2P_DATA(0x14)
#घोषणा E2P_PWR_INT_VALUE4	E2P_DATA(0x16)

/* Contains a bit क्रम each allowed channel. It gives क्रम Europe (ETSI 0x30)
 * also only 11 channels. */
#घोषणा E2P_ALLOWED_CHANNEL	E2P_DATA(0x18)

#घोषणा E2P_DEVICE_VER		E2P_DATA(0x20)
#घोषणा E2P_PHY_REG		E2P_DATA(0x25)
#घोषणा E2P_36M_CAL_VALUE1	E2P_DATA(0x28)
#घोषणा E2P_36M_CAL_VALUE2      E2P_DATA(0x2a)
#घोषणा E2P_36M_CAL_VALUE3      E2P_DATA(0x2c)
#घोषणा E2P_36M_CAL_VALUE4	E2P_DATA(0x2e)
#घोषणा E2P_11A_INT_VALUE1	E2P_DATA(0x30)
#घोषणा E2P_11A_INT_VALUE2	E2P_DATA(0x32)
#घोषणा E2P_11A_INT_VALUE3	E2P_DATA(0x34)
#घोषणा E2P_11A_INT_VALUE4	E2P_DATA(0x36)
#घोषणा E2P_48M_CAL_VALUE1	E2P_DATA(0x38)
#घोषणा E2P_48M_CAL_VALUE2	E2P_DATA(0x3a)
#घोषणा E2P_48M_CAL_VALUE3	E2P_DATA(0x3c)
#घोषणा E2P_48M_CAL_VALUE4	E2P_DATA(0x3e)
#घोषणा E2P_48M_INT_VALUE1	E2P_DATA(0x40)
#घोषणा E2P_48M_INT_VALUE2	E2P_DATA(0x42)
#घोषणा E2P_48M_INT_VALUE3	E2P_DATA(0x44)
#घोषणा E2P_48M_INT_VALUE4	E2P_DATA(0x46)
#घोषणा E2P_54M_CAL_VALUE1	E2P_DATA(0x48)	/* ??? */
#घोषणा E2P_54M_CAL_VALUE2	E2P_DATA(0x4a)
#घोषणा E2P_54M_CAL_VALUE3	E2P_DATA(0x4c)
#घोषणा E2P_54M_CAL_VALUE4	E2P_DATA(0x4e)
#घोषणा E2P_54M_INT_VALUE1	E2P_DATA(0x50)
#घोषणा E2P_54M_INT_VALUE2	E2P_DATA(0x52)
#घोषणा E2P_54M_INT_VALUE3	E2P_DATA(0x54)
#घोषणा E2P_54M_INT_VALUE4	E2P_DATA(0x56)

/* This word contains the base address of the FW_REG_ रेजिस्टरs below */
#घोषणा FWRAW_REGS_ADDR		FWRAW_DATA(0x1d)

/* All 16 bit values, offset from the address in FWRAW_REGS_ADDR */
क्रमागत अणु
	FW_REG_FIRMWARE_VER	= 0,
	/* non-zero अगर USB high speed connection */
	FW_REG_USB_SPEED	= 1,
	FW_REG_FIX_TX_RATE	= 2,
	/* Seems to be able to control LEDs over the firmware */
	FW_REG_LED_LINK_STATUS	= 3,
	FW_REG_SOFT_RESET	= 4,
	FW_REG_FLASH_CHK	= 5,
पूर्ण;

/* Values क्रम FW_LINK_STATUS */
#घोषणा FW_LINK_OFF		0x0
#घोषणा FW_LINK_TX		0x1
/* 0x2 - link led on? */

क्रमागत अणु
	/* indices क्रम ofdm_cal_values */
	OFDM_36M_INDEX = 0,
	OFDM_48M_INDEX = 1,
	OFDM_54M_INDEX = 2,
पूर्ण;

काष्ठा zd_chip अणु
	काष्ठा zd_usb usb;
	काष्ठा zd_rf rf;
	काष्ठा mutex mutex;
	/* Base address of FW_REG_ रेजिस्टरs */
	zd_addr_t fw_regs_base;
	/* EepSetPoपूर्णांक in the venकरोr driver */
	u8 pwr_cal_values[E2P_CHANNEL_COUNT];
	/* पूर्णांकegration values in the venकरोr driver */
	u8 pwr_पूर्णांक_values[E2P_CHANNEL_COUNT];
	/* SetPoपूर्णांकOFDM in the venकरोr driver */
	u8 ofdm_cal_values[3][E2P_CHANNEL_COUNT];
	u16 link_led;
	अचिन्हित पूर्णांक pa_type:4,
		patch_cck_gain:1, patch_cr157:1, patch_6m_band_edge:1,
		new_phy_layout:1, al2230s_bit:1,
		supports_tx_led:1;
पूर्ण;

अटल अंतरभूत काष्ठा zd_chip *zd_usb_to_chip(काष्ठा zd_usb *usb)
अणु
	वापस container_of(usb, काष्ठा zd_chip, usb);
पूर्ण

अटल अंतरभूत काष्ठा zd_chip *zd_rf_to_chip(काष्ठा zd_rf *rf)
अणु
	वापस container_of(rf, काष्ठा zd_chip, rf);
पूर्ण

#घोषणा zd_chip_dev(chip) (&(chip)->usb.पूर्णांकf->dev)

व्योम zd_chip_init(काष्ठा zd_chip *chip,
	         काष्ठा ieee80211_hw *hw,
	         काष्ठा usb_पूर्णांकerface *पूर्णांकf);
व्योम zd_chip_clear(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_पढ़ो_mac_addr_fw(काष्ठा zd_chip *chip, u8 *addr);
पूर्णांक zd_chip_init_hw(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_reset(काष्ठा zd_chip *chip);

अटल अंतरभूत पूर्णांक zd_chip_is_zd1211b(काष्ठा zd_chip *chip)
अणु
	वापस chip->usb.is_zd1211b;
पूर्ण

अटल अंतरभूत पूर्णांक zd_ioपढ़ो16v_locked(काष्ठा zd_chip *chip, u16 *values,
	                              स्थिर zd_addr_t *addresses,
				      अचिन्हित पूर्णांक count)
अणु
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	वापस zd_usb_ioपढ़ो16v(&chip->usb, values, addresses, count);
पूर्ण

अटल अंतरभूत पूर्णांक zd_ioपढ़ो16_locked(काष्ठा zd_chip *chip, u16 *value,
	                             स्थिर zd_addr_t addr)
अणु
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	वापस zd_usb_ioपढ़ो16(&chip->usb, value, addr);
पूर्ण

पूर्णांक zd_ioपढ़ो32v_locked(काष्ठा zd_chip *chip, u32 *values,
	                स्थिर zd_addr_t *addresses, अचिन्हित पूर्णांक count);

अटल अंतरभूत पूर्णांक zd_ioपढ़ो32_locked(काष्ठा zd_chip *chip, u32 *value,
	                             स्थिर zd_addr_t addr)
अणु
	वापस zd_ioपढ़ो32v_locked(chip, value, &addr, 1);
पूर्ण

अटल अंतरभूत पूर्णांक zd_ioग_लिखो16_locked(काष्ठा zd_chip *chip, u16 value,
	                              zd_addr_t addr)
अणु
	काष्ठा zd_ioreq16 ioreq;

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	ioreq.addr = addr;
	ioreq.value = value;

	वापस zd_usb_ioग_लिखो16v(&chip->usb, &ioreq, 1);
पूर्ण

पूर्णांक zd_ioग_लिखो16a_locked(काष्ठा zd_chip *chip,
                         स्थिर काष्ठा zd_ioreq16 *ioreqs, अचिन्हित पूर्णांक count);

पूर्णांक _zd_ioग_लिखो32v_locked(काष्ठा zd_chip *chip, स्थिर काष्ठा zd_ioreq32 *ioreqs,
			  अचिन्हित पूर्णांक count);

अटल अंतरभूत पूर्णांक zd_ioग_लिखो32_locked(काष्ठा zd_chip *chip, u32 value,
	                              zd_addr_t addr)
अणु
	काष्ठा zd_ioreq32 ioreq;

	ioreq.addr = addr;
	ioreq.value = value;

	वापस _zd_ioग_लिखो32v_locked(chip, &ioreq, 1);
पूर्ण

पूर्णांक zd_ioग_लिखो32a_locked(काष्ठा zd_chip *chip,
	                 स्थिर काष्ठा zd_ioreq32 *ioreqs, अचिन्हित पूर्णांक count);

अटल अंतरभूत पूर्णांक zd_rख_डालो_locked(काष्ठा zd_chip *chip, u32 value, u8 bits)
अणु
	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	वापस zd_usb_rख_डालो(&chip->usb, value, bits);
पूर्ण

पूर्णांक zd_rख_डालो_cr_locked(काष्ठा zd_chip *chip, u32 value);

पूर्णांक zd_rख_डालोv_locked(काष्ठा zd_chip *chip,
	               स्थिर u32* values, अचिन्हित पूर्णांक count, u8 bits);
पूर्णांक zd_rख_डालोv_cr_locked(काष्ठा zd_chip *chip,
	                  स्थिर u32* values, अचिन्हित पूर्णांक count);

/* Locking functions क्रम पढ़ोing and writing रेजिस्टरs.
 * The dअगरferent parameters are पूर्णांकentional.
 */
पूर्णांक zd_ioपढ़ो16(काष्ठा zd_chip *chip, zd_addr_t addr, u16 *value);
पूर्णांक zd_ioग_लिखो16(काष्ठा zd_chip *chip, zd_addr_t addr, u16 value);
पूर्णांक zd_ioपढ़ो32(काष्ठा zd_chip *chip, zd_addr_t addr, u32 *value);
पूर्णांक zd_ioग_लिखो32(काष्ठा zd_chip *chip, zd_addr_t addr, u32 value);
पूर्णांक zd_ioपढ़ो32v(काष्ठा zd_chip *chip, स्थिर zd_addr_t *addresses,
	          u32 *values, अचिन्हित पूर्णांक count);
पूर्णांक zd_ioग_लिखो32a(काष्ठा zd_chip *chip, स्थिर काष्ठा zd_ioreq32 *ioreqs,
	           अचिन्हित पूर्णांक count);

पूर्णांक zd_chip_set_channel(काष्ठा zd_chip *chip, u8 channel);
अटल अंतरभूत u8 _zd_chip_get_channel(काष्ठा zd_chip *chip)
अणु
	वापस chip->rf.channel;
पूर्ण
u8  zd_chip_get_channel(काष्ठा zd_chip *chip);
पूर्णांक zd_पढ़ो_regकरोमुख्य(काष्ठा zd_chip *chip, u8 *regकरोमुख्य);
पूर्णांक zd_ग_लिखो_mac_addr(काष्ठा zd_chip *chip, स्थिर u8 *mac_addr);
पूर्णांक zd_ग_लिखो_bssid(काष्ठा zd_chip *chip, स्थिर u8 *bssid);
पूर्णांक zd_chip_चयन_radio_on(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_चयन_radio_off(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_enable_पूर्णांक(काष्ठा zd_chip *chip);
व्योम zd_chip_disable_पूर्णांक(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_enable_rxtx(काष्ठा zd_chip *chip);
व्योम zd_chip_disable_rxtx(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_enable_hwपूर्णांक(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_disable_hwपूर्णांक(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_generic_patch_6m_band(काष्ठा zd_chip *chip, पूर्णांक channel);
पूर्णांक zd_chip_set_rts_cts_rate_locked(काष्ठा zd_chip *chip, पूर्णांक preamble);

अटल अंतरभूत पूर्णांक zd_get_encryption_type(काष्ठा zd_chip *chip, u32 *type)
अणु
	वापस zd_ioपढ़ो32(chip, CR_ENCRYPTION_TYPE, type);
पूर्ण

अटल अंतरभूत पूर्णांक zd_set_encryption_type(काष्ठा zd_chip *chip, u32 type)
अणु
	वापस zd_ioग_लिखो32(chip, CR_ENCRYPTION_TYPE, type);
पूर्ण

अटल अंतरभूत पूर्णांक zd_chip_get_basic_rates(काष्ठा zd_chip *chip, u16 *cr_rates)
अणु
	वापस zd_ioपढ़ो16(chip, CR_BASIC_RATE_TBL, cr_rates);
पूर्ण

पूर्णांक zd_chip_set_basic_rates(काष्ठा zd_chip *chip, u16 cr_rates);

पूर्णांक zd_chip_lock_phy_regs(काष्ठा zd_chip *chip);
पूर्णांक zd_chip_unlock_phy_regs(काष्ठा zd_chip *chip);

क्रमागत led_status अणु
	ZD_LED_OFF = 0,
	ZD_LED_SCANNING = 1,
	ZD_LED_ASSOCIATED = 2,
पूर्ण;

पूर्णांक zd_chip_control_leds(काष्ठा zd_chip *chip, क्रमागत led_status status);

पूर्णांक zd_set_beacon_पूर्णांकerval(काष्ठा zd_chip *chip, u16 पूर्णांकerval, u8 dtim_period,
			   पूर्णांक type);

अटल अंतरभूत पूर्णांक zd_get_beacon_पूर्णांकerval(काष्ठा zd_chip *chip, u32 *पूर्णांकerval)
अणु
	वापस zd_ioपढ़ो32(chip, CR_BCN_INTERVAL, पूर्णांकerval);
पूर्ण

काष्ठा rx_status;

u8 zd_rx_rate(स्थिर व्योम *rx_frame, स्थिर काष्ठा rx_status *status);

काष्ठा zd_mc_hash अणु
	u32 low;
	u32 high;
पूर्ण;

अटल अंतरभूत व्योम zd_mc_clear(काष्ठा zd_mc_hash *hash)
अणु
	hash->low = 0;
	/* The पूर्णांकerfaces must always received broadcasts.
	 * The hash of the broadcast address ff:ff:ff:ff:ff:ff is 63.
	 */
	hash->high = 0x80000000;
पूर्ण

अटल अंतरभूत व्योम zd_mc_add_all(काष्ठा zd_mc_hash *hash)
अणु
	hash->low = hash->high = 0xffffffff;
पूर्ण

अटल अंतरभूत व्योम zd_mc_add_addr(काष्ठा zd_mc_hash *hash, u8 *addr)
अणु
	अचिन्हित पूर्णांक i = addr[5] >> 2;
	अगर (i < 32) अणु
		hash->low |= 1 << i;
	पूर्ण अन्यथा अणु
		hash->high |= 1 << (i-32);
	पूर्ण
पूर्ण

पूर्णांक zd_chip_set_multicast_hash(काष्ठा zd_chip *chip,
	                       काष्ठा zd_mc_hash *hash);

u64 zd_chip_get_tsf(काष्ठा zd_chip *chip);

#पूर्ण_अगर /* _ZD_CHIP_H */
