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

#समावेश "tmacro.h"
#समावेश "upc.h"

/*---------------------  Export Definitions -------------------------*/
/* Registers in the MAC */
#घोषणा MAC_MAX_CONTEXT_SIZE_PAGE0  256
#घोषणा MAC_MAX_CONTEXT_SIZE_PAGE1  128

/* Registers not related to 802.11b */
#घोषणा MAC_REG_BCFG0       0x00
#घोषणा MAC_REG_BCFG1       0x01
#घोषणा MAC_REG_FCR0        0x02
#घोषणा MAC_REG_FCR1        0x03
#घोषणा MAC_REG_BISTCMD     0x04
#घोषणा MAC_REG_BISTSR0     0x05
#घोषणा MAC_REG_BISTSR1     0x06
#घोषणा MAC_REG_BISTSR2     0x07
#घोषणा MAC_REG_I2MCSR      0x08
#घोषणा MAC_REG_I2MTGID     0x09
#घोषणा MAC_REG_I2MTGAD     0x0A
#घोषणा MAC_REG_I2MCFG      0x0B
#घोषणा MAC_REG_I2MDIPT     0x0C
#घोषणा MAC_REG_I2MDOPT     0x0E
#घोषणा MAC_REG_PMC0        0x10
#घोषणा MAC_REG_PMC1        0x11
#घोषणा MAC_REG_STICKHW     0x12
#घोषणा MAC_REG_LOCALID     0x14
#घोषणा MAC_REG_TESTCFG     0x15
#घोषणा MAC_REG_JUMPER0     0x16
#घोषणा MAC_REG_JUMPER1     0x17
#घोषणा MAC_REG_TMCTL0      0x18
#घोषणा MAC_REG_TMCTL1      0x19
#घोषणा MAC_REG_TMDATA0     0x1C

/* MAC Parameter related */
#घोषणा MAC_REG_LRT         0x20
#घोषणा MAC_REG_SRT         0x21
#घोषणा MAC_REG_SIFS        0x22
#घोषणा MAC_REG_DIFS        0x23
#घोषणा MAC_REG_EIFS        0x24
#घोषणा MAC_REG_SLOT        0x25
#घोषणा MAC_REG_BI          0x26
#घोषणा MAC_REG_CWMAXMIN0   0x28
#घोषणा MAC_REG_LINKOFFTOTM 0x2A
#घोषणा MAC_REG_SWTMOT      0x2B
#घोषणा MAC_REG_MIBCNTR     0x2C
#घोषणा MAC_REG_RTSOKCNT    0x2C
#घोषणा MAC_REG_RTSFAILCNT  0x2D
#घोषणा MAC_REG_ACKFAILCNT  0x2E
#घोषणा MAC_REG_FCSERRCNT   0x2F

/* TSF Related */
#घोषणा MAC_REG_TSFCNTR     0x30
#घोषणा MAC_REG_NEXTTBTT    0x38
#घोषणा MAC_REG_TSFOFST     0x40
#घोषणा MAC_REG_TFTCTL      0x48

/* WMAC Control/Status Related */
#घोषणा MAC_REG_ENCFG       0x4C
#घोषणा MAC_REG_PAGE1SEL    0x4F
#घोषणा MAC_REG_CFG         0x50
#घोषणा MAC_REG_TEST        0x52
#घोषणा MAC_REG_HOSTCR      0x54
#घोषणा MAC_REG_MACCR       0x55
#घोषणा MAC_REG_RCR         0x56
#घोषणा MAC_REG_TCR         0x57
#घोषणा MAC_REG_IMR         0x58
#घोषणा MAC_REG_ISR         0x5C

/* Power Saving Related */
#घोषणा MAC_REG_PSCFG       0x60
#घोषणा MAC_REG_PSCTL       0x61
#घोषणा MAC_REG_PSPWRSIG    0x62
#घोषणा MAC_REG_BBCR13      0x63
#घोषणा MAC_REG_AIDATIM     0x64
#घोषणा MAC_REG_PWBT        0x66
#घोषणा MAC_REG_WAKEOKTMR   0x68
#घोषणा MAC_REG_CALTMR      0x69
#घोषणा MAC_REG_SYNSPACCNT  0x6A
#घोषणा MAC_REG_WAKSYNOPT   0x6B

/* Baseband/IF Control Group */
#घोषणा MAC_REG_BBREGCTL    0x6C
#घोषणा MAC_REG_CHANNEL     0x6D
#घोषणा MAC_REG_BBREGADR    0x6E
#घोषणा MAC_REG_BBREGDATA   0x6F
#घोषणा MAC_REG_IFREGCTL    0x70
#घोषणा MAC_REG_IFDATA      0x71
#घोषणा MAC_REG_ITRTMSET    0x74
#घोषणा MAC_REG_PAPEDELAY   0x77
#घोषणा MAC_REG_SOFTPWRCTL  0x78
#घोषणा MAC_REG_GPIOCTL0    0x7A
#घोषणा MAC_REG_GPIOCTL1    0x7B

/* MAC DMA Related Group */
#घोषणा MAC_REG_TXDMACTL0   0x7C
#घोषणा MAC_REG_TXDMAPTR0   0x80
#घोषणा MAC_REG_AC0DMACTL   0x84
#घोषणा MAC_REG_AC0DMAPTR   0x88
#घोषणा MAC_REG_BCNDMACTL   0x8C
#घोषणा MAC_REG_BCNDMAPTR   0x90
#घोषणा MAC_REG_RXDMACTL0   0x94
#घोषणा MAC_REG_RXDMAPTR0   0x98
#घोषणा MAC_REG_RXDMACTL1   0x9C
#घोषणा MAC_REG_RXDMAPTR1   0xA0
#घोषणा MAC_REG_SYNCDMACTL  0xA4
#घोषणा MAC_REG_SYNCDMAPTR  0xA8
#घोषणा MAC_REG_ATIMDMACTL  0xAC
#घोषणा MAC_REG_ATIMDMAPTR  0xB0

/* MiscFF PIO related */
#घोषणा MAC_REG_MISCFFNDEX  0xB4
#घोषणा MAC_REG_MISCFFCTL   0xB6
#घोषणा MAC_REG_MISCFFDATA  0xB8

/* Extend SW Timer */
#घोषणा MAC_REG_TMDATA1     0xBC

/* WOW Related Group */
#घोषणा MAC_REG_WAKEUPEN0   0xC0
#घोषणा MAC_REG_WAKEUPEN1   0xC1
#घोषणा MAC_REG_WAKEUPSR0   0xC2
#घोषणा MAC_REG_WAKEUPSR1   0xC3
#घोषणा MAC_REG_WAKE128_0   0xC4
#घोषणा MAC_REG_WAKE128_1   0xD4
#घोषणा MAC_REG_WAKE128_2   0xE4
#घोषणा MAC_REG_WAKE128_3   0xF4

/************** Page 1 ******************/
#घोषणा MAC_REG_CRC_128_0   0x04
#घोषणा MAC_REG_CRC_128_1   0x06
#घोषणा MAC_REG_CRC_128_2   0x08
#घोषणा MAC_REG_CRC_128_3   0x0A

/* MAC Configuration Group */
#घोषणा MAC_REG_PAR0        0x0C
#घोषणा MAC_REG_PAR4        0x10
#घोषणा MAC_REG_BSSID0      0x14
#घोषणा MAC_REG_BSSID4      0x18
#घोषणा MAC_REG_MAR0        0x1C
#घोषणा MAC_REG_MAR4        0x20

/* MAC RSPPKT INFO Group */
#घोषणा MAC_REG_RSPINF_B_1  0x24
#घोषणा MAC_REG_RSPINF_B_2  0x28
#घोषणा MAC_REG_RSPINF_B_5  0x2C
#घोषणा MAC_REG_RSPINF_B_11 0x30
#घोषणा MAC_REG_RSPINF_A_6  0x34
#घोषणा MAC_REG_RSPINF_A_9  0x36
#घोषणा MAC_REG_RSPINF_A_12 0x38
#घोषणा MAC_REG_RSPINF_A_18 0x3A
#घोषणा MAC_REG_RSPINF_A_24 0x3C
#घोषणा MAC_REG_RSPINF_A_36 0x3E
#घोषणा MAC_REG_RSPINF_A_48 0x40
#घोषणा MAC_REG_RSPINF_A_54 0x42
#घोषणा MAC_REG_RSPINF_A_72 0x44

/* 802.11h relative */
#घोषणा MAC_REG_QUIETINIT   0x60
#घोषणा MAC_REG_QUIETGAP    0x62
#घोषणा MAC_REG_QUIETDUR    0x64
#घोषणा MAC_REG_MSRCTL      0x66
#घोषणा MAC_REG_MSRBBSTS    0x67
#घोषणा MAC_REG_MSRSTART    0x68
#घोषणा MAC_REG_MSRDURATION 0x70
#घोषणा MAC_REG_CCAFRACTION 0x72
#घोषणा MAC_REG_PWRCCK      0x73
#घोषणा MAC_REG_PWROFDM     0x7C

/* Bits in the BCFG0 रेजिस्टर */
#घोषणा BCFG0_PERROFF       0x40
#घोषणा BCFG0_MRDMDIS       0x20
#घोषणा BCFG0_MRDLDIS       0x10
#घोषणा BCFG0_MWMEN         0x08
#घोषणा BCFG0_VSERREN       0x02
#घोषणा BCFG0_LATMEN        0x01

/* Bits in the BCFG1 रेजिस्टर */
#घोषणा BCFG1_CFUNOPT       0x80
#घोषणा BCFG1_CREQOPT       0x40
#घोषणा BCFG1_DMA8          0x10
#घोषणा BCFG1_ARBITOPT      0x08
#घोषणा BCFG1_PCIMEN        0x04
#घोषणा BCFG1_MIOEN         0x02
#घोषणा BCFG1_CISDLYEN      0x01

/* Bits in RAMBIST रेजिस्टरs */
#घोषणा BISTCMD_TSTPAT5     0x00
#घोषणा BISTCMD_TSTPATA     0x80
#घोषणा BISTCMD_TSTERR      0x20
#घोषणा BISTCMD_TSTPATF     0x18
#घोषणा BISTCMD_TSTPAT0     0x10
#घोषणा BISTCMD_TSTMODE     0x04
#घोषणा BISTCMD_TSTITTX     0x03
#घोषणा BISTCMD_TSTATRX     0x02
#घोषणा BISTCMD_TSTATTX     0x01
#घोषणा BISTCMD_TSTRX       0x00
#घोषणा BISTSR0_BISTGO      0x01
#घोषणा BISTSR1_TSTSR       0x01
#घोषणा BISTSR2_CMDPRTEN    0x02
#घोषणा BISTSR2_RAMTSTEN    0x01

/* Bits in the I2MCFG EEPROM रेजिस्टर */
#घोषणा I2MCFG_BOUNDCTL     0x80
#घोषणा I2MCFG_WAITCTL      0x20
#घोषणा I2MCFG_SCLOECTL     0x10
#घोषणा I2MCFG_WBUSYCTL     0x08
#घोषणा I2MCFG_NORETRY      0x04
#घोषणा I2MCFG_I2MLDSEQ     0x02
#घोषणा I2MCFG_I2CMFAST     0x01

/* Bits in the I2MCSR EEPROM रेजिस्टर */
#घोषणा I2MCSR_EEMW         0x80
#घोषणा I2MCSR_EEMR         0x40
#घोषणा I2MCSR_AUTOLD       0x08
#घोषणा I2MCSR_NACK         0x02
#घोषणा I2MCSR_DONE         0x01

/* Bits in the PMC1 रेजिस्टर */
#घोषणा SPS_RST             0x80
#घोषणा PCISTIKY            0x40
#घोषणा PME_OVR             0x02

/* Bits in the STICKYHW रेजिस्टर */
#घोषणा STICKHW_DS1_SHADOW  0x02
#घोषणा STICKHW_DS0_SHADOW  0x01

/* Bits in the TMCTL रेजिस्टर */
#घोषणा TMCTL_TSUSP         0x04
#घोषणा TMCTL_TMD           0x02
#घोषणा TMCTL_TE            0x01

/* Bits in the TFTCTL रेजिस्टर */
#घोषणा TFTCTL_HWUTSF       0x80
#घोषणा TFTCTL_TBTTSYNC     0x40
#घोषणा TFTCTL_HWUTSFEN     0x20
#घोषणा TFTCTL_TSFCNTRRD    0x10
#घोषणा TFTCTL_TBTTSYNCEN   0x08
#घोषणा TFTCTL_TSFSYNCEN    0x04
#घोषणा TFTCTL_TSFCNTRST    0x02
#घोषणा TFTCTL_TSFCNTREN    0x01

/* Bits in the EnhanceCFG रेजिस्टर */
#घोषणा EnCFG_BarkerPream   0x00020000
#घोषणा EnCFG_NXTBTTCFPSTR  0x00010000
#घोषणा EnCFG_BcnSusClr     0x00000200
#घोषणा EnCFG_BcnSusInd     0x00000100
#घोषणा EnCFG_CFP_ProtectEn 0x00000040
#घोषणा EnCFG_ProtectMd     0x00000020
#घोषणा EnCFG_HwParCFP      0x00000010
#घोषणा EnCFG_CFNULRSP      0x00000004
#घोषणा EnCFG_BBType_MASK   0x00000003
#घोषणा EnCFG_BBType_g      0x00000002
#घोषणा EnCFG_BBType_b      0x00000001
#घोषणा EnCFG_BBType_a      0x00000000

/* Bits in the Page1Sel रेजिस्टर */
#घोषणा PAGE1_SEL           0x01

/* Bits in the CFG रेजिस्टर */
#घोषणा CFG_TKIPOPT         0x80
#घोषणा CFG_RXDMAOPT        0x40
#घोषणा CFG_TMOT_SW         0x20
#घोषणा CFG_TMOT_HWLONG     0x10
#घोषणा CFG_TMOT_HW         0x00
#घोषणा CFG_CFPENDOPT       0x08
#घोषणा CFG_BCNSUSEN        0x04
#घोषणा CFG_NOTXTIMEOUT     0x02
#घोषणा CFG_NOBUFOPT        0x01

/* Bits in the TEST रेजिस्टर */
#घोषणा TEST_LBEXT          0x80
#घोषणा TEST_LBINT          0x40
#घोषणा TEST_LBNONE         0x00
#घोषणा TEST_SOFTINT        0x20
#घोषणा TEST_CONTTX         0x10
#घोषणा TEST_TXPE           0x08
#घोषणा TEST_NAVDIS         0x04
#घोषणा TEST_NOCTS          0x02
#घोषणा TEST_NOACK          0x01

/* Bits in the HOSTCR रेजिस्टर */
#घोषणा HOSTCR_TXONST       0x80
#घोषणा HOSTCR_RXONST       0x40
#घोषणा HOSTCR_ADHOC        0x20 /* Network Type 1 = Ad-hoc */
#घोषणा HOSTCR_AP           0x10 /* Port Type 1 = AP */
#घोषणा HOSTCR_TXON         0x08 /* 0000 1000 */
#घोषणा HOSTCR_RXON         0x04 /* 0000 0100 */
#घोषणा HOSTCR_MACEN        0x02 /* 0000 0010 */
#घोषणा HOSTCR_SOFTRST      0x01 /* 0000 0001 */

/* Bits in the MACCR रेजिस्टर */
#घोषणा MACCR_SYNCFLUSHOK   0x04
#घोषणा MACCR_SYNCFLUSH     0x02
#घोषणा MACCR_CLRNAV        0x01

/* Bits in the MAC_REG_GPIOCTL0 रेजिस्टर */
#घोषणा LED_ACTSET           0x01
#घोषणा LED_RFOFF            0x02
#घोषणा LED_NOCONNECT        0x04

/* Bits in the RCR रेजिस्टर */
#घोषणा RCR_SSID            0x80
#घोषणा RCR_RXALLTYPE       0x40
#घोषणा RCR_UNICAST         0x20
#घोषणा RCR_BROADCAST       0x10
#घोषणा RCR_MULTICAST       0x08
#घोषणा RCR_WPAERR          0x04
#घोषणा RCR_ERRCRC          0x02
#घोषणा RCR_BSSID           0x01

/* Bits in the TCR रेजिस्टर */
#घोषणा TCR_SYNCDCFOPT      0x02
#घोषणा TCR_AUTOBCNTX       0x01 /* Beacon स्वतःmatically transmit enable */

/* Bits in the IMR रेजिस्टर */
#घोषणा IMR_MEASURESTART    0x80000000
#घोषणा IMR_QUIETSTART      0x20000000
#घोषणा IMR_RADARDETECT     0x10000000
#घोषणा IMR_MEASUREEND      0x08000000
#घोषणा IMR_SOFTTIMER1      0x00200000
#घोषणा IMR_RXDMA1          0x00001000 /* 0000 0000 0001 0000 0000 0000 */
#घोषणा IMR_RXNOBUF         0x00000800
#घोषणा IMR_MIBNEARFULL     0x00000400
#घोषणा IMR_SOFTINT         0x00000200
#घोषणा IMR_FETALERR        0x00000100
#घोषणा IMR_WATCHDOG        0x00000080
#घोषणा IMR_SOFTTIMER       0x00000040
#घोषणा IMR_GPIO            0x00000020
#घोषणा IMR_TBTT            0x00000010
#घोषणा IMR_RXDMA0          0x00000008
#घोषणा IMR_BNTX            0x00000004
#घोषणा IMR_AC0DMA          0x00000002
#घोषणा IMR_TXDMA0          0x00000001

/* Bits in the ISR रेजिस्टर */
#घोषणा ISR_MEASURESTART    0x80000000
#घोषणा ISR_QUIETSTART      0x20000000
#घोषणा ISR_RADARDETECT     0x10000000
#घोषणा ISR_MEASUREEND      0x08000000
#घोषणा ISR_SOFTTIMER1      0x00200000
#घोषणा ISR_RXDMA1          0x00001000 /* 0000 0000 0001 0000 0000 0000 */
#घोषणा ISR_RXNOBUF         0x00000800 /* 0000 0000 0000 1000 0000 0000 */
#घोषणा ISR_MIBNEARFULL     0x00000400 /* 0000 0000 0000 0100 0000 0000 */
#घोषणा ISR_SOFTINT         0x00000200
#घोषणा ISR_FETALERR        0x00000100
#घोषणा ISR_WATCHDOG        0x00000080
#घोषणा ISR_SOFTTIMER       0x00000040
#घोषणा ISR_GPIO            0x00000020
#घोषणा ISR_TBTT            0x00000010
#घोषणा ISR_RXDMA0          0x00000008
#घोषणा ISR_BNTX            0x00000004
#घोषणा ISR_AC0DMA          0x00000002
#घोषणा ISR_TXDMA0          0x00000001

/* Bits in the PSCFG रेजिस्टर */
#घोषणा PSCFG_PHILIPMD      0x40
#घोषणा PSCFG_WAKECALEN     0x20
#घोषणा PSCFG_WAKETMREN     0x10
#घोषणा PSCFG_BBPSPROG      0x08
#घोषणा PSCFG_WAKESYN       0x04
#घोषणा PSCFG_SLEEPSYN      0x02
#घोषणा PSCFG_AUTOSLEEP     0x01

/* Bits in the PSCTL रेजिस्टर */
#घोषणा PSCTL_WAKEDONE      0x20
#घोषणा PSCTL_PS            0x10
#घोषणा PSCTL_GO2DOZE       0x08
#घोषणा PSCTL_LNBCN         0x04
#घोषणा PSCTL_ALBCN         0x02
#घोषणा PSCTL_PSEN          0x01

/* Bits in the PSPWSIG रेजिस्टर */
#घोषणा PSSIG_WPE3          0x80
#घोषणा PSSIG_WPE2          0x40
#घोषणा PSSIG_WPE1          0x20
#घोषणा PSSIG_WRADIOPE      0x10
#घोषणा PSSIG_SPE3          0x08
#घोषणा PSSIG_SPE2          0x04
#घोषणा PSSIG_SPE1          0x02
#घोषणा PSSIG_SRADIOPE      0x01

/* Bits in the BBREGCTL रेजिस्टर */
#घोषणा BBREGCTL_DONE       0x04
#घोषणा BBREGCTL_REGR       0x02
#घोषणा BBREGCTL_REGW       0x01

/* Bits in the IFREGCTL रेजिस्टर */
#घोषणा IFREGCTL_DONE       0x04
#घोषणा IFREGCTL_IFRF       0x02
#घोषणा IFREGCTL_REGW       0x01

/* Bits in the SOFTPWRCTL रेजिस्टर */
#घोषणा SOFTPWRCTL_RFLEOPT      0x0800
#घोषणा SOFTPWRCTL_TXPEINV      0x0200
#घोषणा SOFTPWRCTL_SWPECTI      0x0100
#घोषणा SOFTPWRCTL_SWPAPE       0x0020
#घोषणा SOFTPWRCTL_SWCALEN      0x0010
#घोषणा SOFTPWRCTL_SWRADIO_PE   0x0008
#घोषणा SOFTPWRCTL_SWPE2        0x0004
#घोषणा SOFTPWRCTL_SWPE1        0x0002
#घोषणा SOFTPWRCTL_SWPE3        0x0001

/* Bits in the GPIOCTL1 रेजिस्टर */
#घोषणा GPIO1_DATA1             0x20
#घोषणा GPIO1_MD1               0x10
#घोषणा GPIO1_DATA0             0x02
#घोषणा GPIO1_MD0               0x01

/* Bits in the DMACTL रेजिस्टर */
#घोषणा DMACTL_CLRRUN       0x00080000
#घोषणा DMACTL_RUN          0x00000008
#घोषणा DMACTL_WAKE         0x00000004
#घोषणा DMACTL_DEAD         0x00000002
#घोषणा DMACTL_ACTIVE       0x00000001

/* Bits in the RXDMACTL0 रेजिस्टर */
#घोषणा RX_PERPKT           0x00000100
#घोषणा RX_PERPKTCLR        0x01000000

/* Bits in the BCNDMACTL रेजिस्टर */
#घोषणा BEACON_READY        0x01

/* Bits in the MISCFFCTL रेजिस्टर */
#घोषणा MISCFFCTL_WRITE     0x0001

/* Bits in WAKEUPEN0 */
#घोषणा WAKEUPEN0_सूचीPKT    0x10
#घोषणा WAKEUPEN0_LINKOFF   0x08
#घोषणा WAKEUPEN0_ATIMEN    0x04
#घोषणा WAKEUPEN0_TIMEN     0x02
#घोषणा WAKEUPEN0_MAGICEN   0x01

/* Bits in WAKEUPEN1 */
#घोषणा WAKEUPEN1_128_3     0x08
#घोषणा WAKEUPEN1_128_2     0x04
#घोषणा WAKEUPEN1_128_1     0x02
#घोषणा WAKEUPEN1_128_0     0x01

/* Bits in WAKEUPSR0 */
#घोषणा WAKEUPSR0_सूचीPKT    0x10
#घोषणा WAKEUPSR0_LINKOFF   0x08
#घोषणा WAKEUPSR0_ATIMEN    0x04
#घोषणा WAKEUPSR0_TIMEN     0x02
#घोषणा WAKEUPSR0_MAGICEN   0x01

/* Bits in WAKEUPSR1 */
#घोषणा WAKEUPSR1_128_3     0x08
#घोषणा WAKEUPSR1_128_2     0x04
#घोषणा WAKEUPSR1_128_1     0x02
#घोषणा WAKEUPSR1_128_0     0x01

/* Bits in the MAC_REG_GPIOCTL रेजिस्टर */
#घोषणा GPIO0_MD            0x01
#घोषणा GPIO0_DATA          0x02
#घोषणा GPIO0_INTMD         0x04
#घोषणा GPIO1_MD            0x10
#घोषणा GPIO1_DATA          0x20

/* Bits in the MSRCTL रेजिस्टर */
#घोषणा MSRCTL_FINISH       0x80
#घोषणा MSRCTL_READY        0x40
#घोषणा MSRCTL_RADARDETECT  0x20
#घोषणा MSRCTL_EN           0x10
#घोषणा MSRCTL_QUIETTXCHK   0x08
#घोषणा MSRCTL_QUIETRPT     0x04
#घोषणा MSRCTL_QUIETINT     0x02
#घोषणा MSRCTL_QUIETEN      0x01

/* Bits in the MSRCTL1 रेजिस्टर */
#घोषणा MSRCTL1_TXPWR       0x08
#घोषणा MSRCTL1_CSAPAREN    0x04
#घोषणा MSRCTL1_TXPAUSE     0x01

/* Loopback mode */
#घोषणा MAC_LB_EXT          0x02
#घोषणा MAC_LB_INTERNAL     0x01
#घोषणा MAC_LB_NONE         0x00

#घोषणा Default_BI              0x200

/* MiscFIFO Offset */
#घोषणा MISCFIFO_KEYETRY0       32
#घोषणा MISCFIFO_KEYENTRYSIZE   22
#घोषणा MISCFIFO_SYNINFO_IDX    10
#घोषणा MISCFIFO_SYNDATA_IDX    11
#घोषणा MISCFIFO_SYNDATASIZE    21

/* enabled mask value of irq */
#घोषणा IMR_MASK_VALUE     (IMR_SOFTTIMER1 |	\
			    IMR_RXDMA1 |	\
			    IMR_RXNOBUF |	\
			    IMR_MIBNEARFULL |	\
			    IMR_SOFTINT |	\
			    IMR_FETALERR |	\
			    IMR_WATCHDOG |	\
			    IMR_SOFTTIMER |	\
			    IMR_GPIO |		\
			    IMR_TBTT |		\
			    IMR_RXDMA0 |	\
			    IMR_BNTX |		\
			    IMR_AC0DMA |	\
			    IMR_TXDMA0)

/* max समय out delay समय */
#घोषणा W_MAX_TIMEOUT       0xFFF0U

/* रुको समय within loop */
#घोषणा CB_DELAY_LOOP_WAIT  10 /* 10ms */

/* revision id */
#घोषणा REV_ID_VT3253_A0    0x00
#घोषणा REV_ID_VT3253_A1    0x01
#घोषणा REV_ID_VT3253_B0    0x08
#घोषणा REV_ID_VT3253_B1    0x09

/*---------------------  Export Types  ------------------------------*/

/*---------------------  Export Macros ------------------------------*/

#घोषणा MACvRegBitsOn(iobase, byRegOfs, byBits)			\
करो अणु									\
	अचिन्हित अक्षर byData;						\
	VNSvInPortB(iobase + byRegOfs, &byData);			\
	VNSvOutPortB(iobase + byRegOfs, byData | (byBits));		\
पूर्ण जबतक (0)

#घोषणा MACvWordRegBitsOn(iobase, byRegOfs, wBits)			\
करो अणु									\
	अचिन्हित लघु wData;						\
	VNSvInPortW(iobase + byRegOfs, &wData);			\
	VNSvOutPortW(iobase + byRegOfs, wData | (wBits));		\
पूर्ण जबतक (0)

#घोषणा MACvDWordRegBitsOn(iobase, byRegOfs, dwBits)			\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + byRegOfs, &dwData);			\
	VNSvOutPortD(iobase + byRegOfs, dwData | (dwBits));		\
पूर्ण जबतक (0)

#घोषणा MACvRegBitsOnEx(iobase, byRegOfs, byMask, byBits)		\
करो अणु									\
	अचिन्हित अक्षर byData;						\
	VNSvInPortB(iobase + byRegOfs, &byData);			\
	byData &= byMask;						\
	VNSvOutPortB(iobase + byRegOfs, byData | (byBits));		\
पूर्ण जबतक (0)

#घोषणा MACvRegBitsOff(iobase, byRegOfs, byBits)			\
करो अणु									\
	अचिन्हित अक्षर byData;						\
	VNSvInPortB(iobase + byRegOfs, &byData);			\
	VNSvOutPortB(iobase + byRegOfs, byData & ~(byBits));		\
पूर्ण जबतक (0)

#घोषणा MACvWordRegBitsOff(iobase, byRegOfs, wBits)			\
करो अणु									\
	अचिन्हित लघु wData;						\
	VNSvInPortW(iobase + byRegOfs, &wData);			\
	VNSvOutPortW(iobase + byRegOfs, wData & ~(wBits));		\
पूर्ण जबतक (0)

#घोषणा MACvDWordRegBitsOff(iobase, byRegOfs, dwBits)			\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + byRegOfs, &dwData);			\
	VNSvOutPortD(iobase + byRegOfs, dwData & ~(dwBits));		\
पूर्ण जबतक (0)

#घोषणा MACvGetCurrRx0DescAddr(iobase, pdwCurrDescAddr)	\
	VNSvInPortD(iobase + MAC_REG_RXDMAPTR0,		\
		    (अचिन्हित दीर्घ *)pdwCurrDescAddr)

#घोषणा MACvGetCurrRx1DescAddr(iobase, pdwCurrDescAddr)	\
	VNSvInPortD(iobase + MAC_REG_RXDMAPTR1,		\
		    (अचिन्हित दीर्घ *)pdwCurrDescAddr)

#घोषणा MACvGetCurrTx0DescAddr(iobase, pdwCurrDescAddr)	\
	VNSvInPortD(iobase + MAC_REG_TXDMAPTR0,		\
		    (अचिन्हित दीर्घ *)pdwCurrDescAddr)

#घोषणा MACvGetCurrAC0DescAddr(iobase, pdwCurrDescAddr)	\
	VNSvInPortD(iobase + MAC_REG_AC0DMAPTR,		\
		    (अचिन्हित दीर्घ *)pdwCurrDescAddr)

#घोषणा MACvGetCurrSyncDescAddr(iobase, pdwCurrDescAddr)	\
	VNSvInPortD(iobase + MAC_REG_SYNCDMAPTR,		\
		    (अचिन्हित दीर्घ *)pdwCurrDescAddr)

#घोषणा MACvGetCurrATIMDescAddr(iobase, pdwCurrDescAddr)	\
	VNSvInPortD(iobase + MAC_REG_ATIMDMAPTR,		\
		    (अचिन्हित दीर्घ *)pdwCurrDescAddr)

/* set the chip with current BCN tx descriptor address */
#घोषणा MACvSetCurrBCNTxDescAddr(iobase, dwCurrDescAddr)	\
	VNSvOutPortD(iobase + MAC_REG_BCNDMAPTR,		\
		     dwCurrDescAddr)

/* set the chip with current BCN length */
#घोषणा MACvSetCurrBCNLength(iobase, wCurrBCNLength)		\
	VNSvOutPortW(iobase + MAC_REG_BCNDMACTL + 2,		\
		     wCurrBCNLength)

#घोषणा MACvReadBSSIDAddress(iobase, pbyEtherAddr)		\
करो अणु								\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 1);		\
	VNSvInPortB(iobase + MAC_REG_BSSID0,			\
		    (अचिन्हित अक्षर *)pbyEtherAddr);		\
	VNSvInPortB(iobase + MAC_REG_BSSID0 + 1,		\
		    pbyEtherAddr + 1);				\
	VNSvInPortB(iobase + MAC_REG_BSSID0 + 2,		\
		    pbyEtherAddr + 2);				\
	VNSvInPortB(iobase + MAC_REG_BSSID0 + 3,		\
		    pbyEtherAddr + 3);				\
	VNSvInPortB(iobase + MAC_REG_BSSID0 + 4,		\
		    pbyEtherAddr + 4);				\
	VNSvInPortB(iobase + MAC_REG_BSSID0 + 5,		\
		    pbyEtherAddr + 5);				\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 0);		\
पूर्ण जबतक (0)

#घोषणा MACvWriteBSSIDAddress(iobase, pbyEtherAddr)		\
करो अणु								\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 1);		\
	VNSvOutPortB(iobase + MAC_REG_BSSID0,			\
		     *(pbyEtherAddr));				\
	VNSvOutPortB(iobase + MAC_REG_BSSID0 + 1,		\
		     *(pbyEtherAddr + 1));			\
	VNSvOutPortB(iobase + MAC_REG_BSSID0 + 2,		\
		     *(pbyEtherAddr + 2));			\
	VNSvOutPortB(iobase + MAC_REG_BSSID0 + 3,		\
		     *(pbyEtherAddr + 3));			\
	VNSvOutPortB(iobase + MAC_REG_BSSID0 + 4,		\
		     *(pbyEtherAddr + 4));			\
	VNSvOutPortB(iobase + MAC_REG_BSSID0 + 5,		\
		     *(pbyEtherAddr + 5));			\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 0);		\
पूर्ण जबतक (0)

#घोषणा MACvReadEtherAddress(iobase, pbyEtherAddr)		\
करो अणु								\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 1);		\
	VNSvInPortB(iobase + MAC_REG_PAR0,			\
		    (अचिन्हित अक्षर *)pbyEtherAddr);		\
	VNSvInPortB(iobase + MAC_REG_PAR0 + 1,		\
		    pbyEtherAddr + 1);				\
	VNSvInPortB(iobase + MAC_REG_PAR0 + 2,		\
		    pbyEtherAddr + 2);				\
	VNSvInPortB(iobase + MAC_REG_PAR0 + 3,		\
		    pbyEtherAddr + 3);				\
	VNSvInPortB(iobase + MAC_REG_PAR0 + 4,		\
		    pbyEtherAddr + 4);				\
	VNSvInPortB(iobase + MAC_REG_PAR0 + 5,		\
		    pbyEtherAddr + 5);				\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 0);		\
पूर्ण जबतक (0)

#घोषणा MACvWriteEtherAddress(iobase, pbyEtherAddr)		\
करो अणु								\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 1);		\
	VNSvOutPortB(iobase + MAC_REG_PAR0,			\
		     *pbyEtherAddr);				\
	VNSvOutPortB(iobase + MAC_REG_PAR0 + 1,		\
		     *(pbyEtherAddr + 1));			\
	VNSvOutPortB(iobase + MAC_REG_PAR0 + 2,		\
		     *(pbyEtherAddr + 2));			\
	VNSvOutPortB(iobase + MAC_REG_PAR0 + 3,		\
		     *(pbyEtherAddr + 3));			\
	VNSvOutPortB(iobase + MAC_REG_PAR0 + 4,		\
		     *(pbyEtherAddr + 4));			\
	VNSvOutPortB(iobase + MAC_REG_PAR0 + 5,		\
		     *(pbyEtherAddr + 5));			\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 0);		\
पूर्ण जबतक (0)

#घोषणा MACvClearISR(iobase)						\
	VNSvOutPortD(iobase + MAC_REG_ISR, IMR_MASK_VALUE)

#घोषणा MACvStart(iobase)						\
	VNSvOutPortB(iobase + MAC_REG_HOSTCR,				\
		     (HOSTCR_MACEN | HOSTCR_RXON | HOSTCR_TXON))

#घोषणा MACvRx0PerPktMode(iobase)					\
	VNSvOutPortD(iobase + MAC_REG_RXDMACTL0, RX_PERPKT)

#घोषणा MACvRx0BufferFillMode(iobase)					\
	VNSvOutPortD(iobase + MAC_REG_RXDMACTL0, RX_PERPKTCLR)

#घोषणा MACvRx1PerPktMode(iobase)					\
	VNSvOutPortD(iobase + MAC_REG_RXDMACTL1, RX_PERPKT)

#घोषणा MACvRx1BufferFillMode(iobase)					\
	VNSvOutPortD(iobase + MAC_REG_RXDMACTL1, RX_PERPKTCLR)

#घोषणा MACvRxOn(iobase)						\
	MACvRegBitsOn(iobase, MAC_REG_HOSTCR, HOSTCR_RXON)

#घोषणा MACvReceive0(iobase)						\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + MAC_REG_RXDMACTL0, &dwData);		\
	अगर (dwData & DMACTL_RUN)					\
		VNSvOutPortD(iobase + MAC_REG_RXDMACTL0, DMACTL_WAKE); \
	अन्यथा								\
		VNSvOutPortD(iobase + MAC_REG_RXDMACTL0, DMACTL_RUN); \
पूर्ण जबतक (0)

#घोषणा MACvReceive1(iobase)						\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + MAC_REG_RXDMACTL1, &dwData);		\
	अगर (dwData & DMACTL_RUN)					\
		VNSvOutPortD(iobase + MAC_REG_RXDMACTL1, DMACTL_WAKE); \
	अन्यथा								\
		VNSvOutPortD(iobase + MAC_REG_RXDMACTL1, DMACTL_RUN); \
पूर्ण जबतक (0)

#घोषणा MACvTxOn(iobase)						\
	MACvRegBitsOn(iobase, MAC_REG_HOSTCR, HOSTCR_TXON)

#घोषणा MACvTransmit0(iobase)						\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + MAC_REG_TXDMACTL0, &dwData);		\
	अगर (dwData & DMACTL_RUN)					\
		VNSvOutPortD(iobase + MAC_REG_TXDMACTL0, DMACTL_WAKE); \
	अन्यथा								\
		VNSvOutPortD(iobase + MAC_REG_TXDMACTL0, DMACTL_RUN); \
पूर्ण जबतक (0)

#घोषणा MACvTransmitAC0(iobase)					\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + MAC_REG_AC0DMACTL, &dwData);		\
	अगर (dwData & DMACTL_RUN)					\
		VNSvOutPortD(iobase + MAC_REG_AC0DMACTL, DMACTL_WAKE); \
	अन्यथा								\
		VNSvOutPortD(iobase + MAC_REG_AC0DMACTL, DMACTL_RUN); \
पूर्ण जबतक (0)

#घोषणा MACvTransmitSYNC(iobase)					\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + MAC_REG_SYNCDMACTL, &dwData);		\
	अगर (dwData & DMACTL_RUN)					\
		VNSvOutPortD(iobase + MAC_REG_SYNCDMACTL, DMACTL_WAKE); \
	अन्यथा								\
		VNSvOutPortD(iobase + MAC_REG_SYNCDMACTL, DMACTL_RUN); \
पूर्ण जबतक (0)

#घोषणा MACvTransmitATIM(iobase)					\
करो अणु									\
	अचिन्हित दीर्घ dwData;						\
	VNSvInPortD(iobase + MAC_REG_ATIMDMACTL, &dwData);		\
	अगर (dwData & DMACTL_RUN)					\
		VNSvOutPortD(iobase + MAC_REG_ATIMDMACTL, DMACTL_WAKE); \
	अन्यथा								\
		VNSvOutPortD(iobase + MAC_REG_ATIMDMACTL, DMACTL_RUN); \
पूर्ण जबतक (0)

#घोषणा MACvTransmitBCN(iobase)					\
	VNSvOutPortB(iobase + MAC_REG_BCNDMACTL, BEACON_READY)

#घोषणा MACvClearStckDS(iobase)					\
करो अणु									\
	अचिन्हित अक्षर byOrgValue;					\
	VNSvInPortB(iobase + MAC_REG_STICKHW, &byOrgValue);		\
	byOrgValue = byOrgValue & 0xFC;					\
	VNSvOutPortB(iobase + MAC_REG_STICKHW, byOrgValue);		\
पूर्ण जबतक (0)

#घोषणा MACvReadISR(iobase, pdwValue)				\
	VNSvInPortD(iobase + MAC_REG_ISR, pdwValue)

#घोषणा MACvWriteISR(iobase, dwValue)				\
	VNSvOutPortD(iobase + MAC_REG_ISR, dwValue)

#घोषणा MACvIntEnable(iobase, dwMask)				\
	VNSvOutPortD(iobase + MAC_REG_IMR, dwMask)

#घोषणा MACvIntDisable(iobase)				\
	VNSvOutPortD(iobase + MAC_REG_IMR, 0)

#घोषणा MACvSelectPage0(iobase)				\
		VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 0)

#घोषणा MACvSelectPage1(iobase)				\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 1)

#घोषणा MACvReadMIBCounter(iobase, pdwCounter)			\
	VNSvInPortD(iobase + MAC_REG_MIBCNTR, pdwCounter)

#घोषणा MACvPwrEvntDisable(iobase)					\
	VNSvOutPortW(iobase + MAC_REG_WAKEUPEN0, 0x0000)

#घोषणा MACvEnableProtectMD(iobase)					\
करो अणु									\
	अचिन्हित दीर्घ dwOrgValue;					\
	VNSvInPortD(iobase + MAC_REG_ENCFG, &dwOrgValue);		\
	dwOrgValue = dwOrgValue | EnCFG_ProtectMd;			\
	VNSvOutPortD(iobase + MAC_REG_ENCFG, dwOrgValue);		\
पूर्ण जबतक (0)

#घोषणा MACvDisableProtectMD(iobase)					\
करो अणु									\
	अचिन्हित दीर्घ dwOrgValue;					\
	VNSvInPortD(iobase + MAC_REG_ENCFG, &dwOrgValue);		\
	dwOrgValue = dwOrgValue & ~EnCFG_ProtectMd;			\
	VNSvOutPortD(iobase + MAC_REG_ENCFG, dwOrgValue);		\
पूर्ण जबतक (0)

#घोषणा MACvEnableBarkerPreambleMd(iobase)				\
करो अणु									\
	अचिन्हित दीर्घ dwOrgValue;					\
	VNSvInPortD(iobase + MAC_REG_ENCFG, &dwOrgValue);		\
	dwOrgValue = dwOrgValue | EnCFG_BarkerPream;			\
	VNSvOutPortD(iobase + MAC_REG_ENCFG, dwOrgValue);		\
पूर्ण जबतक (0)

#घोषणा MACvDisableBarkerPreambleMd(iobase)				\
करो अणु									\
	अचिन्हित दीर्घ dwOrgValue;					\
	VNSvInPortD(iobase + MAC_REG_ENCFG, &dwOrgValue);		\
	dwOrgValue = dwOrgValue & ~EnCFG_BarkerPream;			\
	VNSvOutPortD(iobase + MAC_REG_ENCFG, dwOrgValue);		\
पूर्ण जबतक (0)

#घोषणा MACvSetBBType(iobase, byTyp)					\
करो अणु									\
	अचिन्हित दीर्घ dwOrgValue;					\
	VNSvInPortD(iobase + MAC_REG_ENCFG, &dwOrgValue);		\
	dwOrgValue = dwOrgValue & ~EnCFG_BBType_MASK;			\
	dwOrgValue = dwOrgValue | (अचिन्हित दीर्घ)byTyp;			\
	VNSvOutPortD(iobase + MAC_REG_ENCFG, dwOrgValue);		\
पूर्ण जबतक (0)

#घोषणा MACvReadATIMW(iobase, pwCounter)				\
	VNSvInPortW(iobase + MAC_REG_AIDATIM, pwCounter)

#घोषणा MACvWriteATIMW(iobase, wCounter)				\
	VNSvOutPortW(iobase + MAC_REG_AIDATIM, wCounter)

#घोषणा MACvWriteCRC16_128(iobase, byRegOfs, wCRC)		\
करो अणु								\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 1);		\
	VNSvOutPortW(iobase + byRegOfs, wCRC);		\
	VNSvOutPortB(iobase + MAC_REG_PAGE1SEL, 0);		\
पूर्ण जबतक (0)

#घोषणा MACvGPIOIn(iobase, pbyValue)					\
	VNSvInPortB(iobase + MAC_REG_GPIOCTL1, pbyValue)

#घोषणा MACvSetRFLE_LatchBase(iobase)                                 \
	MACvWordRegBitsOn(iobase, MAC_REG_SOFTPWRCTL, SOFTPWRCTL_RFLEOPT)

bool MACbIsRegBitsOff(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRegOfs,
		      अचिन्हित अक्षर byTestBits);

bool MACbIsIntDisable(काष्ठा vnt_निजी *priv);

व्योम MACvSetShortRetryLimit(काष्ठा vnt_निजी *priv,
			    अचिन्हित अक्षर byRetryLimit);

व्योम MACvSetLongRetryLimit(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byRetryLimit);

व्योम MACvSetLoopbackMode(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर byLoopbackMode);

व्योम MACvSaveContext(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर *pbyCxtBuf);
व्योम MACvRestoreContext(काष्ठा vnt_निजी *priv, अचिन्हित अक्षर *pbyCxtBuf);

bool MACbSoftwareReset(काष्ठा vnt_निजी *priv);
bool MACbSafeSoftwareReset(काष्ठा vnt_निजी *priv);
bool MACbSafeRxOff(काष्ठा vnt_निजी *priv);
bool MACbSafeTxOff(काष्ठा vnt_निजी *priv);
bool MACbSafeStop(काष्ठा vnt_निजी *priv);
bool MACbShutकरोwn(काष्ठा vnt_निजी *priv);
व्योम MACvInitialize(काष्ठा vnt_निजी *priv);
व्योम MACvSetCurrRx0DescAddr(काष्ठा vnt_निजी *priv,
			    u32 curr_desc_addr);
व्योम MACvSetCurrRx1DescAddr(काष्ठा vnt_निजी *priv,
			    u32 curr_desc_addr);
व्योम MACvSetCurrTXDescAddr(पूर्णांक iTxType, काष्ठा vnt_निजी *priv,
			   u32 curr_desc_addr);
व्योम MACvSetCurrTx0DescAddrEx(काष्ठा vnt_निजी *priv,
			      u32 curr_desc_addr);
व्योम MACvSetCurrAC0DescAddrEx(काष्ठा vnt_निजी *priv,
			      u32 curr_desc_addr);
व्योम MACvSetCurrSyncDescAddrEx(काष्ठा vnt_निजी *priv,
			       u32 curr_desc_addr);
व्योम MACvSetCurrATIMDescAddrEx(काष्ठा vnt_निजी *priv,
			       u32 curr_desc_addr);
व्योम MACvTimer0MicroSDelay(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक uDelay);
व्योम MACvOneShotTimer1MicroSec(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक uDelayTime);

व्योम MACvSetMISCFअगरo(काष्ठा vnt_निजी *priv, अचिन्हित लघु wOffset,
		     u32 dwData);

bool MACbPSWakeup(काष्ठा vnt_निजी *priv);

व्योम MACvSetKeyEntry(काष्ठा vnt_निजी *priv, अचिन्हित लघु wKeyCtl,
		     अचिन्हित पूर्णांक uEntryIdx, अचिन्हित पूर्णांक uKeyIdx,
		     अचिन्हित अक्षर *pbyAddr, u32 *pdwKey,
		     अचिन्हित अक्षर byLocalID);
व्योम MACvDisableKeyEntry(काष्ठा vnt_निजी *priv, अचिन्हित पूर्णांक uEntryIdx);

#पूर्ण_अगर /* __MAC_H__ */
