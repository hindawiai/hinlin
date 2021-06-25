<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (c) 1996, 2003 VIA Networking Technologies, Inc.
 * All rights reserved.
 *
 * File: mac.h
 *
 * Purpose: MAC routines
 *
 * Author: Tevin Chen
 *
 * Date: May 21, 1996
 *
 * Revision History:
 *      07-01-2003 Bryan YC Fan:  Re-ग_लिखो codes to support VT3253 spec.
 *      08-25-2003 Kyle Hsu:      Porting MAC functions from sim53.
 *      09-03-2003 Bryan YC Fan:  Add MACvDisableProtectMD & MACvEnableProtectMD
 */

#अगर_अघोषित __MAC_H__
#घोषणा __MAC_H__

#समावेश <linux/bits.h>
#समावेश "device.h"

#घोषणा REV_ID_VT3253_A0	0x00
#घोषणा REV_ID_VT3253_A1	0x01
#घोषणा REV_ID_VT3253_B0	0x08
#घोषणा REV_ID_VT3253_B1	0x09

/* Registers in the MAC */
#घोषणा MAC_REG_BISTCMD		0x04
#घोषणा MAC_REG_BISTSR0		0x05
#घोषणा MAC_REG_BISTSR1		0x06
#घोषणा MAC_REG_BISTSR2		0x07
#घोषणा MAC_REG_I2MCSR		0x08
#घोषणा MAC_REG_I2MTGID		0x09
#घोषणा MAC_REG_I2MTGAD		0x0a
#घोषणा MAC_REG_I2MCFG		0x0b
#घोषणा MAC_REG_I2MDIPT		0x0c
#घोषणा MAC_REG_I2MDOPT		0x0e
#घोषणा MAC_REG_USBSUS		0x0f

#घोषणा MAC_REG_LOCALID		0x14
#घोषणा MAC_REG_TESTCFG		0x15
#घोषणा MAC_REG_JUMPER0		0x16
#घोषणा MAC_REG_JUMPER1		0x17
#घोषणा MAC_REG_TMCTL		0x18
#घोषणा MAC_REG_TMDATA0		0x1c
#घोषणा MAC_REG_TMDATA1		0x1d
#घोषणा MAC_REG_TMDATA2		0x1e
#घोषणा MAC_REG_TMDATA3		0x1f

/* MAC Parameter related */
#घोषणा MAC_REG_LRT		0x20
#घोषणा MAC_REG_SRT		0x21
#घोषणा MAC_REG_SIFS		0x22
#घोषणा MAC_REG_DIFS		0x23
#घोषणा MAC_REG_EIFS		0x24
#घोषणा MAC_REG_SLOT		0x25
#घोषणा MAC_REG_BI		0x26
#घोषणा MAC_REG_CWMAXMIN0	0x28
#घोषणा MAC_REG_LINKOFFTOTM	0x2a
#घोषणा MAC_REG_SWTMOT		0x2b
#घोषणा MAC_REG_RTSOKCNT	0x2c
#घोषणा MAC_REG_RTSFAILCNT	0x2d
#घोषणा MAC_REG_ACKFAILCNT	0x2e
#घोषणा MAC_REG_FCSERRCNT	0x2f

/* TSF Related */
#घोषणा MAC_REG_TSFCNTR		0x30
#घोषणा MAC_REG_NEXTTBTT	0x38
#घोषणा MAC_REG_TSFOFST		0x40
#घोषणा MAC_REG_TFTCTL		0x48

/* WMAC Control/Status Related */
#घोषणा MAC_REG_ENCFG0		0x4c
#घोषणा MAC_REG_ENCFG1		0x4d
#घोषणा MAC_REG_ENCFG2		0x4e

#घोषणा MAC_REG_CFG		0x50
#घोषणा MAC_REG_TEST		0x52
#घोषणा MAC_REG_HOSTCR		0x54
#घोषणा MAC_REG_MACCR		0x55
#घोषणा MAC_REG_RCR		0x56
#घोषणा MAC_REG_TCR		0x57
#घोषणा MAC_REG_IMR		0x58
#घोषणा MAC_REG_ISR		0x5c
#घोषणा MAC_REG_ISR1		0x5d

/* Power Saving Related */
#घोषणा MAC_REG_PSCFG		0x60
#घोषणा MAC_REG_PSCTL		0x61
#घोषणा MAC_REG_PSPWRSIG	0x62
#घोषणा MAC_REG_BBCR13		0x63
#घोषणा MAC_REG_AIDATIM		0x64
#घोषणा MAC_REG_PWBT		0x66
#घोषणा MAC_REG_WAKEOKTMR	0x68
#घोषणा MAC_REG_CALTMR		0x69
#घोषणा MAC_REG_SYNSPACCNT	0x6a
#घोषणा MAC_REG_WAKSYNOPT	0x6b

/* Baseband/IF Control Group */
#घोषणा MAC_REG_BBREGCTL	0x6c
#घोषणा MAC_REG_CHANNEL		0x6d
#घोषणा MAC_REG_BBREGADR	0x6e
#घोषणा MAC_REG_BBREGDATA	0x6f
#घोषणा MAC_REG_IFREGCTL	0x70
#घोषणा MAC_REG_IFDATA		0x71
#घोषणा MAC_REG_ITRTMSET	0x74
#घोषणा MAC_REG_PAPEDELAY	0x77
#घोषणा MAC_REG_SOFTPWRCTL	0x78
#घोषणा MAC_REG_SOFTPWRCTL2	0x79
#घोषणा MAC_REG_GPIOCTL0	0x7a
#घोषणा MAC_REG_GPIOCTL1	0x7b

/* MiscFF PIO related */
#घोषणा MAC_REG_MISCFFNDEX	0xbc
#घोषणा MAC_REG_MISCFFCTL	0xbe
#घोषणा MAC_REG_MISCFFDATA	0xc0

/* MAC Configuration Group */
#घोषणा MAC_REG_PAR0		0xc4
#घोषणा MAC_REG_PAR4		0xc8
#घोषणा MAC_REG_BSSID0		0xcc
#घोषणा MAC_REG_BSSID4		0xd0
#घोषणा MAC_REG_MAR0		0xd4
#घोषणा MAC_REG_MAR4		0xd8

/* MAC RSPPKT INFO Group */
#घोषणा MAC_REG_RSPINF_B_1	0xdC
#घोषणा MAC_REG_RSPINF_B_2	0xe0
#घोषणा MAC_REG_RSPINF_B_5	0xe4
#घोषणा MAC_REG_RSPINF_B_11	0xe8
#घोषणा MAC_REG_RSPINF_A_6	0xec
#घोषणा MAC_REG_RSPINF_A_9	0xee
#घोषणा MAC_REG_RSPINF_A_12	0xf0
#घोषणा MAC_REG_RSPINF_A_18	0xf2
#घोषणा MAC_REG_RSPINF_A_24	0xf4
#घोषणा MAC_REG_RSPINF_A_36	0xf6
#घोषणा MAC_REG_RSPINF_A_48	0xf8
#घोषणा MAC_REG_RSPINF_A_54	0xfa
#घोषणा MAC_REG_RSPINF_A_72	0xfc

/* Bits in the I2MCFG EEPROM रेजिस्टर */
#घोषणा I2MCFG_BOUNDCTL		BIT(7)
#घोषणा I2MCFG_WAITCTL		BIT(5)
#घोषणा I2MCFG_SCLOECTL		BIT(4)
#घोषणा I2MCFG_WBUSYCTL		BIT(3)
#घोषणा I2MCFG_NORETRY		BIT(2)
#घोषणा I2MCFG_I2MLDSEQ		BIT(1)
#घोषणा I2MCFG_I2CMFAST		BIT(0)

/* Bits in the I2MCSR EEPROM रेजिस्टर */
#घोषणा I2MCSR_EEMW		BIT(7)
#घोषणा I2MCSR_EEMR		BIT(6)
#घोषणा I2MCSR_AUTOLD		BIT(3)
#घोषणा I2MCSR_NACK		BIT(1)
#घोषणा I2MCSR_DONE		BIT(0)

/* Bits in the TMCTL रेजिस्टर */
#घोषणा TMCTL_TSUSP		BIT(2)
#घोषणा TMCTL_TMD		BIT(1)
#घोषणा TMCTL_TE		BIT(0)

/* Bits in the TFTCTL रेजिस्टर */
#घोषणा TFTCTL_HWUTSF		BIT(7)
#घोषणा TFTCTL_TBTTSYNC		BIT(6)
#घोषणा TFTCTL_HWUTSFEN		BIT(5)
#घोषणा TFTCTL_TSFCNTRRD	BIT(4)
#घोषणा TFTCTL_TBTTSYNCEN	BIT(3)
#घोषणा TFTCTL_TSFSYNCEN	BIT(2)
#घोषणा TFTCTL_TSFCNTRST	BIT(1)
#घोषणा TFTCTL_TSFCNTREN	BIT(0)

/* Bits in the EnhanceCFG_0 रेजिस्टर */
#घोषणा EnCFG_BBType_a		0x00
#घोषणा EnCFG_BBType_b		BIT(0)
#घोषणा EnCFG_BBType_g		BIT(1)
#घोषणा EnCFG_BBType_MASK	(EnCFG_BBType_b | EnCFG_BBType_g)
#घोषणा EnCFG_ProtectMd		BIT(5)

/* Bits in the EnhanceCFG_1 रेजिस्टर */
#घोषणा EnCFG_BcnSusInd		BIT(0)
#घोषणा EnCFG_BcnSusClr		BIT(1)

/* Bits in the EnhanceCFG_2 रेजिस्टर */
#घोषणा EnCFG_NXTBTTCFPSTR	BIT(0)
#घोषणा EnCFG_BarkerPream	BIT(1)
#घोषणा EnCFG_PktBurstMode	BIT(2)

/* Bits in the CFG रेजिस्टर */
#घोषणा CFG_TKIPOPT		BIT(7)
#घोषणा CFG_RXDMAOPT		BIT(6)
#घोषणा CFG_TMOT_SW		BIT(5)
#घोषणा CFG_TMOT_HWLONG		BIT(4)
#घोषणा CFG_TMOT_HW		0x00
#घोषणा CFG_CFPENDOPT		BIT(3)
#घोषणा CFG_BCNSUSEN		BIT(2)
#घोषणा CFG_NOTXTIMEOUT		BIT(1)
#घोषणा CFG_NOBUFOPT		BIT(0)

/* Bits in the TEST रेजिस्टर */
#घोषणा TEST_LBEXT		BIT(7)
#घोषणा TEST_LBINT		BIT(6)
#घोषणा TEST_LBNONE		0x00
#घोषणा TEST_SOFTINT		BIT(5)
#घोषणा TEST_CONTTX		BIT(4)
#घोषणा TEST_TXPE		BIT(3)
#घोषणा TEST_NAVDIS		BIT(2)
#घोषणा TEST_NOCTS		BIT(1)
#घोषणा TEST_NOACK		BIT(0)

/* Bits in the HOSTCR रेजिस्टर */
#घोषणा HOSTCR_TXONST		BIT(7)
#घोषणा HOSTCR_RXONST		BIT(6)
#घोषणा HOSTCR_ADHOC		BIT(5)
#घोषणा HOSTCR_AP		BIT(4)
#घोषणा HOSTCR_TXON		BIT(3)
#घोषणा HOSTCR_RXON		BIT(2)
#घोषणा HOSTCR_MACEN		BIT(1)
#घोषणा HOSTCR_SOFTRST		BIT(0)

/* Bits in the MACCR रेजिस्टर */
#घोषणा MACCR_SYNCFLUSHOK	BIT(2)
#घोषणा MACCR_SYNCFLUSH		BIT(1)
#घोषणा MACCR_CLRNAV		BIT(0)

/* Bits in the RCR रेजिस्टर */
#घोषणा RCR_SSID		BIT(7)
#घोषणा RCR_RXALLTYPE		BIT(6)
#घोषणा RCR_UNICAST		BIT(5)
#घोषणा RCR_BROADCAST		BIT(4)
#घोषणा RCR_MULTICAST		BIT(3)
#घोषणा RCR_WPAERR		BIT(2)
#घोषणा RCR_ERRCRC		BIT(1)
#घोषणा RCR_BSSID		BIT(0)

/* Bits in the TCR रेजिस्टर */
#घोषणा TCR_SYNCDCFOPT		BIT(1)
#घोषणा TCR_AUTOBCNTX		BIT(0)

/* ISR1 */
#घोषणा ISR_GPIO3		BIT(6)
#घोषणा ISR_RXNOBUF		BIT(3)
#घोषणा ISR_MIBNEARFULL		BIT(2)
#घोषणा ISR_SOFTINT		BIT(1)
#घोषणा ISR_FETALERR		BIT(0)

#घोषणा LEDSTS_STS		0x06
#घोषणा LEDSTS_TMLEN		0x78
#घोषणा LEDSTS_OFF		0x00
#घोषणा LEDSTS_ON		0x02
#घोषणा LEDSTS_SLOW		0x04
#घोषणा LEDSTS_INTER		0x06

/* ISR0 */
#घोषणा ISR_WATCHDOG		BIT(7)
#घोषणा ISR_SOFTTIMER		BIT(6)
#घोषणा ISR_GPIO0		BIT(5)
#घोषणा ISR_TBTT		BIT(4)
#घोषणा ISR_RXDMA0		BIT(3)
#घोषणा ISR_BNTX		BIT(2)
#घोषणा ISR_ACTX		BIT(0)

/* Bits in the PSCFG रेजिस्टर */
#घोषणा PSCFG_PHILIPMD		BIT(6)
#घोषणा PSCFG_WAKECALEN		BIT(5)
#घोषणा PSCFG_WAKETMREN		BIT(4)
#घोषणा PSCFG_BBPSPROG		BIT(3)
#घोषणा PSCFG_WAKESYN		BIT(2)
#घोषणा PSCFG_SLEEPSYN		BIT(1)
#घोषणा PSCFG_AUTOSLEEP		BIT(0)

/* Bits in the PSCTL रेजिस्टर */
#घोषणा PSCTL_WAKEDONE		BIT(5)
#घोषणा PSCTL_PS		BIT(4)
#घोषणा PSCTL_GO2DOZE		BIT(3)
#घोषणा PSCTL_LNBCN		BIT(2)
#घोषणा PSCTL_ALBCN		BIT(1)
#घोषणा PSCTL_PSEN		BIT(0)

/* Bits in the PSPWSIG रेजिस्टर */
#घोषणा PSSIG_WPE3		BIT(7)
#घोषणा PSSIG_WPE2		BIT(6)
#घोषणा PSSIG_WPE1		BIT(5)
#घोषणा PSSIG_WRADIOPE		BIT(4)
#घोषणा PSSIG_SPE3		BIT(3)
#घोषणा PSSIG_SPE2		BIT(2)
#घोषणा PSSIG_SPE1		BIT(1)
#घोषणा PSSIG_SRADIOPE		BIT(0)

/* Bits in the BBREGCTL रेजिस्टर */
#घोषणा BBREGCTL_DONE		BIT(2)
#घोषणा BBREGCTL_REGR		BIT(1)
#घोषणा BBREGCTL_REGW		BIT(0)

/* Bits in the IFREGCTL रेजिस्टर */
#घोषणा IFREGCTL_DONE		BIT(2)
#घोषणा IFREGCTL_IFRF		BIT(1)
#घोषणा IFREGCTL_REGW		BIT(0)

/* Bits in the SOFTPWRCTL रेजिस्टर */
#घोषणा SOFTPWRCTL_RFLEOPT	BIT(3)
#घोषणा SOFTPWRCTL_TXPEINV	BIT(1)
#घोषणा SOFTPWRCTL_SWPECTI	BIT(0)
#घोषणा SOFTPWRCTL_SWPAPE	BIT(5)
#घोषणा SOFTPWRCTL_SWCALEN	BIT(4)
#घोषणा SOFTPWRCTL_SWRADIO_PE	BIT(3)
#घोषणा SOFTPWRCTL_SWPE2	BIT(2)
#घोषणा SOFTPWRCTL_SWPE1	BIT(1)
#घोषणा SOFTPWRCTL_SWPE3	BIT(0)

/* Bits in the GPIOCTL1 रेजिस्टर */
#घोषणा GPIO3_MD		BIT(5)
#घोषणा GPIO3_DATA		BIT(6)
#घोषणा GPIO3_INTMD		BIT(7)

/* Bits in the MISCFFCTL रेजिस्टर */
#घोषणा MISCFFCTL_WRITE		BIT(0)

/* Loopback mode */
#घोषणा MAC_LB_EXT		BIT(1)
#घोषणा MAC_LB_INTERNAL		BIT(0)
#घोषणा MAC_LB_NONE		0x00

/* Ethernet address filter type */
#घोषणा PKT_TYPE_NONE		0x00 /* turn off receiver */
#घोषणा PKT_TYPE_ALL_MULTICAST	BIT(7)
#घोषणा PKT_TYPE_PROMISCUOUS	BIT(6)
#घोषणा PKT_TYPE_सूचीECTED	BIT(5)	/* obselete */
#घोषणा PKT_TYPE_BROADCAST	BIT(4)
#घोषणा PKT_TYPE_MULTICAST	BIT(3)
#घोषणा PKT_TYPE_ERROR_WPA	BIT(2)
#घोषणा PKT_TYPE_ERROR_CRC	BIT(1)
#घोषणा PKT_TYPE_BSSID		BIT(0)

#घोषणा Default_BI              0x200

/* MiscFIFO Offset */
#घोषणा MISCFIFO_KEYETRY0	32
#घोषणा MISCFIFO_KEYENTRYSIZE	22

#घोषणा MAC_REVISION_A0		0x00
#घोषणा MAC_REVISION_A1		0x01

काष्ठा vnt_mac_set_key अणु
	जोड़ अणु
		काष्ठा अणु
			u8 addr[ETH_ALEN];
			__le16 key_ctl;
		पूर्ण ग_लिखो __packed;
		u32 swap[2];
	पूर्ण u;
	u8 key[WLAN_KEY_LEN_CCMP];
पूर्ण __packed;

पूर्णांक vnt_mac_set_filter(काष्ठा vnt_निजी *priv, u64 mc_filter);
पूर्णांक vnt_mac_shutकरोwn(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_mac_set_bb_type(काष्ठा vnt_निजी *priv, u8 type);
पूर्णांक vnt_mac_disable_keyentry(काष्ठा vnt_निजी *priv, u8 entry_idx);
पूर्णांक vnt_mac_set_keyentry(काष्ठा vnt_निजी *priv, u16 key_ctl, u32 entry_idx,
			 u32 key_idx, u8 *addr, u8 *key);
पूर्णांक vnt_mac_reg_bits_off(काष्ठा vnt_निजी *priv, u8 reg_ofs, u8 bits);
पूर्णांक vnt_mac_reg_bits_on(काष्ठा vnt_निजी *priv, u8 reg_ofs, u8 bits);
पूर्णांक vnt_mac_ग_लिखो_word(काष्ठा vnt_निजी *priv, u8 reg_ofs, u16 word);
पूर्णांक vnt_mac_set_bssid_addr(काष्ठा vnt_निजी *priv, u8 *addr);
पूर्णांक vnt_mac_enable_protect_mode(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_mac_disable_protect_mode(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_mac_enable_barker_preamble_mode(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_mac_disable_barker_preamble_mode(काष्ठा vnt_निजी *priv);
पूर्णांक vnt_mac_set_beacon_पूर्णांकerval(काष्ठा vnt_निजी *priv, u16 पूर्णांकerval);
पूर्णांक vnt_mac_set_led(काष्ठा vnt_निजी *privpriv, u8 state, u8 led);

#पूर्ण_अगर /* __MAC_H__ */
