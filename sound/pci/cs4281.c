<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Cirrus Logic CS4281 based PCI soundcard
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/tlv.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>


MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Cirrus Logic CS4281");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable चयनes */
अटल bool dual_codec[SNDRV_CARDS];	/* dual codec */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for CS4281 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for CS4281 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable CS4281 soundcard.");
module_param_array(dual_codec, bool, शून्य, 0444);
MODULE_PARM_DESC(dual_codec, "Secondary Codec ID (0 = disabled).");

/*
 *  Direct रेजिस्टरs
 */

#घोषणा CS4281_BA0_SIZE		0x1000
#घोषणा CS4281_BA1_SIZE		0x10000

/*
 *  BA0 रेजिस्टरs
 */
#घोषणा BA0_HISR		0x0000	/* Host Interrupt Status Register */
#घोषणा BA0_HISR_INTENA		(1<<31)	/* Internal Interrupt Enable Bit */
#घोषणा BA0_HISR_MIDI		(1<<22)	/* MIDI port पूर्णांकerrupt */
#घोषणा BA0_HISR_FIFOI		(1<<20)	/* FIFO polled पूर्णांकerrupt */
#घोषणा BA0_HISR_DMAI		(1<<18)	/* DMA पूर्णांकerrupt (half or end) */
#घोषणा BA0_HISR_FIFO(c)	(1<<(12+(c))) /* FIFO channel पूर्णांकerrupt */
#घोषणा BA0_HISR_DMA(c)		(1<<(8+(c)))  /* DMA channel पूर्णांकerrupt */
#घोषणा BA0_HISR_GPPI		(1<<5)	/* General Purpose Input (Primary chip) */
#घोषणा BA0_HISR_GPSI		(1<<4)	/* General Purpose Input (Secondary chip) */
#घोषणा BA0_HISR_GP3I		(1<<3)	/* GPIO3 pin Interrupt */
#घोषणा BA0_HISR_GP1I		(1<<2)	/* GPIO1 pin Interrupt */
#घोषणा BA0_HISR_VUPI		(1<<1)	/* VOLUP pin Interrupt */
#घोषणा BA0_HISR_VDNI		(1<<0)	/* VOLDN pin Interrupt */

#घोषणा BA0_HICR		0x0008	/* Host Interrupt Control Register */
#घोषणा BA0_HICR_CHGM		(1<<1)	/* INTENA Change Mask */
#घोषणा BA0_HICR_IEV		(1<<0)	/* INTENA Value */
#घोषणा BA0_HICR_EOI		(3<<0)	/* End of Interrupt command */

#घोषणा BA0_HIMR		0x000c	/* Host Interrupt Mask Register */
					/* Use same contants as क्रम BA0_HISR */

#घोषणा BA0_IIER		0x0010	/* ISA Interrupt Enable Register */

#घोषणा BA0_HDSR0		0x00f0	/* Host DMA Engine 0 Status Register */
#घोषणा BA0_HDSR1		0x00f4	/* Host DMA Engine 1 Status Register */
#घोषणा BA0_HDSR2		0x00f8	/* Host DMA Engine 2 Status Register */
#घोषणा BA0_HDSR3		0x00fc	/* Host DMA Engine 3 Status Register */

#घोषणा BA0_HDSR_CH1P		(1<<25)	/* Channel 1 Pending */
#घोषणा BA0_HDSR_CH2P		(1<<24)	/* Channel 2 Pending */
#घोषणा BA0_HDSR_DHTC		(1<<17)	/* DMA Half Terminal Count */
#घोषणा BA0_HDSR_DTC		(1<<16)	/* DMA Terminal Count */
#घोषणा BA0_HDSR_DRUN		(1<<15)	/* DMA Running */
#घोषणा BA0_HDSR_RQ		(1<<7)	/* Pending Request */

#घोषणा BA0_DCA0		0x0110	/* Host DMA Engine 0 Current Address */
#घोषणा BA0_DCC0		0x0114	/* Host DMA Engine 0 Current Count */
#घोषणा BA0_DBA0		0x0118	/* Host DMA Engine 0 Base Address */
#घोषणा BA0_DBC0		0x011c	/* Host DMA Engine 0 Base Count */
#घोषणा BA0_DCA1		0x0120	/* Host DMA Engine 1 Current Address */
#घोषणा BA0_DCC1		0x0124	/* Host DMA Engine 1 Current Count */
#घोषणा BA0_DBA1		0x0128	/* Host DMA Engine 1 Base Address */
#घोषणा BA0_DBC1		0x012c	/* Host DMA Engine 1 Base Count */
#घोषणा BA0_DCA2		0x0130	/* Host DMA Engine 2 Current Address */
#घोषणा BA0_DCC2		0x0134	/* Host DMA Engine 2 Current Count */
#घोषणा BA0_DBA2		0x0138	/* Host DMA Engine 2 Base Address */
#घोषणा BA0_DBC2		0x013c	/* Host DMA Engine 2 Base Count */
#घोषणा BA0_DCA3		0x0140	/* Host DMA Engine 3 Current Address */
#घोषणा BA0_DCC3		0x0144	/* Host DMA Engine 3 Current Count */
#घोषणा BA0_DBA3		0x0148	/* Host DMA Engine 3 Base Address */
#घोषणा BA0_DBC3		0x014c	/* Host DMA Engine 3 Base Count */
#घोषणा BA0_DMR0		0x0150	/* Host DMA Engine 0 Mode */
#घोषणा BA0_DCR0		0x0154	/* Host DMA Engine 0 Command */
#घोषणा BA0_DMR1		0x0158	/* Host DMA Engine 1 Mode */
#घोषणा BA0_DCR1		0x015c	/* Host DMA Engine 1 Command */
#घोषणा BA0_DMR2		0x0160	/* Host DMA Engine 2 Mode */
#घोषणा BA0_DCR2		0x0164	/* Host DMA Engine 2 Command */
#घोषणा BA0_DMR3		0x0168	/* Host DMA Engine 3 Mode */
#घोषणा BA0_DCR3		0x016c	/* Host DMA Engine 3 Command */

#घोषणा BA0_DMR_DMA		(1<<29)	/* Enable DMA mode */
#घोषणा BA0_DMR_POLL		(1<<28)	/* Enable poll mode */
#घोषणा BA0_DMR_TBC		(1<<25)	/* Transfer By Channel */
#घोषणा BA0_DMR_CBC		(1<<24)	/* Count By Channel (0 = frame resolution) */
#घोषणा BA0_DMR_SWAPC		(1<<22)	/* Swap Left/Right Channels */
#घोषणा BA0_DMR_SIZE20		(1<<20)	/* Sample is 20-bit */
#घोषणा BA0_DMR_USIGN		(1<<19)	/* Unचिन्हित */
#घोषणा BA0_DMR_BEND		(1<<18)	/* Big Endian */
#घोषणा BA0_DMR_MONO		(1<<17)	/* Mono */
#घोषणा BA0_DMR_SIZE8		(1<<16)	/* Sample is 8-bit */
#घोषणा BA0_DMR_TYPE_DEMAND	(0<<6)
#घोषणा BA0_DMR_TYPE_SINGLE	(1<<6)
#घोषणा BA0_DMR_TYPE_BLOCK	(2<<6)
#घोषणा BA0_DMR_TYPE_CASCADE	(3<<6)	/* Not supported */
#घोषणा BA0_DMR_DEC		(1<<5)	/* Access Increment (0) or Decrement (1) */
#घोषणा BA0_DMR_AUTO		(1<<4)	/* Auto-Initialize */
#घोषणा BA0_DMR_TR_VERIFY	(0<<2)	/* Verअगरy Transfer */
#घोषणा BA0_DMR_TR_WRITE	(1<<2)	/* Write Transfer */
#घोषणा BA0_DMR_TR_READ		(2<<2)	/* Read Transfer */

#घोषणा BA0_DCR_HTCIE		(1<<17)	/* Half Terminal Count Interrupt */
#घोषणा BA0_DCR_TCIE		(1<<16)	/* Terminal Count Interrupt */
#घोषणा BA0_DCR_MSK		(1<<0)	/* DMA Mask bit */

#घोषणा BA0_FCR0		0x0180	/* FIFO Control 0 */
#घोषणा BA0_FCR1		0x0184	/* FIFO Control 1 */
#घोषणा BA0_FCR2		0x0188	/* FIFO Control 2 */
#घोषणा BA0_FCR3		0x018c	/* FIFO Control 3 */

#घोषणा BA0_FCR_FEN		(1<<31)	/* FIFO Enable bit */
#घोषणा BA0_FCR_DACZ		(1<<30)	/* DAC Zero */
#घोषणा BA0_FCR_PSH		(1<<29)	/* Previous Sample Hold */
#घोषणा BA0_FCR_RS(x)		(((x)&0x1f)<<24) /* Right Slot Mapping */
#घोषणा BA0_FCR_LS(x)		(((x)&0x1f)<<16) /* Left Slot Mapping */
#घोषणा BA0_FCR_SZ(x)		(((x)&0x7f)<<8)	/* FIFO buffer size (in samples) */
#घोषणा BA0_FCR_OF(x)		(((x)&0x7f)<<0)	/* FIFO starting offset (in samples) */

#घोषणा BA0_FPDR0		0x0190	/* FIFO Polled Data 0 */
#घोषणा BA0_FPDR1		0x0194	/* FIFO Polled Data 1 */
#घोषणा BA0_FPDR2		0x0198	/* FIFO Polled Data 2 */
#घोषणा BA0_FPDR3		0x019c	/* FIFO Polled Data 3 */

#घोषणा BA0_FCHS		0x020c	/* FIFO Channel Status */
#घोषणा BA0_FCHS_RCO(x)		(1<<(7+(((x)&3)<<3))) /* Right Channel Out */
#घोषणा BA0_FCHS_LCO(x)		(1<<(6+(((x)&3)<<3))) /* Left Channel Out */
#घोषणा BA0_FCHS_MRP(x)		(1<<(5+(((x)&3)<<3))) /* Move Read Poपूर्णांकer */
#घोषणा BA0_FCHS_FE(x)		(1<<(4+(((x)&3)<<3))) /* FIFO Empty */
#घोषणा BA0_FCHS_FF(x)		(1<<(3+(((x)&3)<<3))) /* FIFO Full */
#घोषणा BA0_FCHS_IOR(x)		(1<<(2+(((x)&3)<<3))) /* Internal Overrun Flag */
#घोषणा BA0_FCHS_RCI(x)		(1<<(1+(((x)&3)<<3))) /* Right Channel In */
#घोषणा BA0_FCHS_LCI(x)		(1<<(0+(((x)&3)<<3))) /* Left Channel In */

#घोषणा BA0_FSIC0		0x0210	/* FIFO Status and Interrupt Control 0 */
#घोषणा BA0_FSIC1		0x0214	/* FIFO Status and Interrupt Control 1 */
#घोषणा BA0_FSIC2		0x0218	/* FIFO Status and Interrupt Control 2 */
#घोषणा BA0_FSIC3		0x021c	/* FIFO Status and Interrupt Control 3 */

#घोषणा BA0_FSIC_FIC(x)		(((x)&0x7f)<<24) /* FIFO Interrupt Count */
#घोषणा BA0_FSIC_FORIE		(1<<23) /* FIFO OverRun Interrupt Enable */
#घोषणा BA0_FSIC_FURIE		(1<<22) /* FIFO UnderRun Interrupt Enable */
#घोषणा BA0_FSIC_FSCIE		(1<<16)	/* FIFO Sample Count Interrupt Enable */
#घोषणा BA0_FSIC_FSC(x)		(((x)&0x7f)<<8) /* FIFO Sample Count */
#घोषणा BA0_FSIC_FOR		(1<<7)	/* FIFO OverRun */
#घोषणा BA0_FSIC_FUR		(1<<6)	/* FIFO UnderRun */
#घोषणा BA0_FSIC_FSCR		(1<<0)	/* FIFO Sample Count Reached */

#घोषणा BA0_PMCS		0x0344	/* Power Management Control/Status */
#घोषणा BA0_CWPR		0x03e0	/* Configuration Write Protect */

#घोषणा BA0_EPPMC		0x03e4	/* Extended PCI Power Management Control */
#घोषणा BA0_EPPMC_FPDN		(1<<14) /* Full Power DowN */

#घोषणा BA0_GPIOR		0x03e8	/* GPIO Pin Interface Register */

#घोषणा BA0_SPMC		0x03ec	/* Serial Port Power Management Control (& ASDIN2 enable) */
#घोषणा BA0_SPMC_GIPPEN		(1<<15)	/* GP INT Primary PME# Enable */
#घोषणा BA0_SPMC_GISPEN		(1<<14)	/* GP INT Secondary PME# Enable */
#घोषणा BA0_SPMC_EESPD		(1<<9)	/* EEPROM Serial Port Disable */
#घोषणा BA0_SPMC_ASDI2E		(1<<8)	/* ASDIN2 Enable */
#घोषणा BA0_SPMC_ASDO		(1<<7)	/* Asynchronous ASDOUT Assertion */
#घोषणा BA0_SPMC_WUP2		(1<<3)	/* Wakeup क्रम Secondary Input */
#घोषणा BA0_SPMC_WUP1		(1<<2)	/* Wakeup क्रम Primary Input */
#घोषणा BA0_SPMC_ASYNC		(1<<1)	/* Asynchronous ASYNC Assertion */
#घोषणा BA0_SPMC_RSTN		(1<<0)	/* Reset Not! */

#घोषणा BA0_CFLR		0x03f0	/* Configuration Load Register (EEPROM or BIOS) */
#घोषणा BA0_CFLR_DEFAULT	0x00000001 /* CFLR must be in AC97 link mode */
#घोषणा BA0_IISR		0x03f4	/* ISA Interrupt Select */
#घोषणा BA0_TMS			0x03f8	/* Test Register */
#घोषणा BA0_SSVID		0x03fc	/* Subप्रणाली ID रेजिस्टर */

#घोषणा BA0_CLKCR1		0x0400	/* Clock Control Register 1 */
#घोषणा BA0_CLKCR1_CLKON	(1<<25)	/* Read Only */
#घोषणा BA0_CLKCR1_DLLRDY	(1<<24)	/* DLL Ready */
#घोषणा BA0_CLKCR1_DLLOS	(1<<6)	/* DLL Output Select */
#घोषणा BA0_CLKCR1_SWCE		(1<<5)	/* Clock Enable */
#घोषणा BA0_CLKCR1_DLLP		(1<<4)	/* DLL PowerUp */
#घोषणा BA0_CLKCR1_DLLSS	(((x)&3)<<3) /* DLL Source Select */

#घोषणा BA0_FRR			0x0410	/* Feature Reporting Register */
#घोषणा BA0_SLT12O		0x041c	/* Slot 12 GPIO Output Register क्रम AC-Link */

#घोषणा BA0_SERMC		0x0420	/* Serial Port Master Control */
#घोषणा BA0_SERMC_FCRN		(1<<27)	/* Force Codec Ready Not */
#घोषणा BA0_SERMC_ODSEN2	(1<<25)	/* On-Demand Support Enable ASDIN2 */
#घोषणा BA0_SERMC_ODSEN1	(1<<24)	/* On-Demand Support Enable ASDIN1 */
#घोषणा BA0_SERMC_SXLB		(1<<21)	/* ASDIN2 to ASDOUT Loopback */
#घोषणा BA0_SERMC_SLB		(1<<20)	/* ASDOUT to ASDIN2 Loopback */
#घोषणा BA0_SERMC_LOVF		(1<<19)	/* Loopback Output Valid Frame bit */
#घोषणा BA0_SERMC_TCID(x)	(((x)&3)<<16) /* Target Secondary Codec ID */
#घोषणा BA0_SERMC_PXLB		(5<<1)	/* Primary Port External Loopback */
#घोषणा BA0_SERMC_PLB		(4<<1)	/* Primary Port Internal Loopback */
#घोषणा BA0_SERMC_PTC		(7<<1)	/* Port Timing Configuration */
#घोषणा BA0_SERMC_PTC_AC97	(1<<1)	/* AC97 mode */
#घोषणा BA0_SERMC_MSPE		(1<<0)	/* Master Serial Port Enable */

#घोषणा BA0_SERC1		0x0428	/* Serial Port Configuration 1 */
#घोषणा BA0_SERC1_SO1F(x)	(((x)&7)>>1) /* Primary Output Port Format */
#घोषणा BA0_SERC1_AC97		(1<<1)
#घोषणा BA0_SERC1_SO1EN		(1<<0)	/* Primary Output Port Enable */

#घोषणा BA0_SERC2		0x042c	/* Serial Port Configuration 2 */
#घोषणा BA0_SERC2_SI1F(x)	(((x)&7)>>1) /* Primary Input Port Format */
#घोषणा BA0_SERC2_AC97		(1<<1)
#घोषणा BA0_SERC2_SI1EN		(1<<0)	/* Primary Input Port Enable */

#घोषणा BA0_SLT12M		0x045c	/* Slot 12 Monitor Register क्रम Primary AC-Link */

#घोषणा BA0_ACCTL		0x0460	/* AC'97 Control */
#घोषणा BA0_ACCTL_TC		(1<<6)	/* Target Codec */
#घोषणा BA0_ACCTL_CRW		(1<<4)	/* 0=Write, 1=Read Command */
#घोषणा BA0_ACCTL_DCV		(1<<3)	/* Dynamic Command Valid */
#घोषणा BA0_ACCTL_VFRM		(1<<2)	/* Valid Frame */
#घोषणा BA0_ACCTL_ESYN		(1<<1)	/* Enable Sync */

#घोषणा BA0_ACSTS		0x0464	/* AC'97 Status */
#घोषणा BA0_ACSTS_VSTS		(1<<1)	/* Valid Status */
#घोषणा BA0_ACSTS_CRDY		(1<<0)	/* Codec Ready */

#घोषणा BA0_ACOSV		0x0468	/* AC'97 Output Slot Valid */
#घोषणा BA0_ACOSV_SLV(x)	(1<<((x)-3))

#घोषणा BA0_ACCAD		0x046c	/* AC'97 Command Address */
#घोषणा BA0_ACCDA		0x0470	/* AC'97 Command Data */

#घोषणा BA0_ACISV		0x0474	/* AC'97 Input Slot Valid */
#घोषणा BA0_ACISV_SLV(x)	(1<<((x)-3))

#घोषणा BA0_ACSAD		0x0478	/* AC'97 Status Address */
#घोषणा BA0_ACSDA		0x047c	/* AC'97 Status Data */
#घोषणा BA0_JSPT		0x0480	/* Joystick poll/trigger */
#घोषणा BA0_JSCTL		0x0484	/* Joystick control */
#घोषणा BA0_JSC1		0x0488	/* Joystick control */
#घोषणा BA0_JSC2		0x048c	/* Joystick control */
#घोषणा BA0_JSIO		0x04a0

#घोषणा BA0_MIDCR		0x0490	/* MIDI Control */
#घोषणा BA0_MIDCR_MRST		(1<<5)	/* Reset MIDI Interface */
#घोषणा BA0_MIDCR_MLB		(1<<4)	/* MIDI Loop Back Enable */
#घोषणा BA0_MIDCR_TIE		(1<<3)	/* MIDI Transmuit Interrupt Enable */
#घोषणा BA0_MIDCR_RIE		(1<<2)	/* MIDI Receive Interrupt Enable */
#घोषणा BA0_MIDCR_RXE		(1<<1)	/* MIDI Receive Enable */
#घोषणा BA0_MIDCR_TXE		(1<<0)	/* MIDI Transmit Enable */

#घोषणा BA0_MIDCMD		0x0494	/* MIDI Command (wo) */

#घोषणा BA0_MIDSR		0x0494	/* MIDI Status (ro) */
#घोषणा BA0_MIDSR_RDA		(1<<15)	/* Sticky bit (RBE 1->0) */
#घोषणा BA0_MIDSR_TBE		(1<<14) /* Sticky bit (TBF 0->1) */
#घोषणा BA0_MIDSR_RBE		(1<<7)	/* Receive Buffer Empty */
#घोषणा BA0_MIDSR_TBF		(1<<6)	/* Transmit Buffer Full */

#घोषणा BA0_MIDWP		0x0498	/* MIDI Write */
#घोषणा BA0_MIDRP		0x049c	/* MIDI Read (ro) */

#घोषणा BA0_AODSD1		0x04a8	/* AC'97 On-Demand Slot Disable क्रम primary link (ro) */
#घोषणा BA0_AODSD1_NDS(x)	(1<<((x)-3))

#घोषणा BA0_AODSD2		0x04ac	/* AC'97 On-Demand Slot Disable क्रम secondary link (ro) */
#घोषणा BA0_AODSD2_NDS(x)	(1<<((x)-3))

#घोषणा BA0_CFGI		0x04b0	/* Configure Interface (EEPROM पूर्णांकerface) */
#घोषणा BA0_SLT12M2		0x04dc	/* Slot 12 Monitor Register 2 क्रम secondary AC-link */
#घोषणा BA0_ACSTS2		0x04e4	/* AC'97 Status Register 2 */
#घोषणा BA0_ACISV2		0x04f4	/* AC'97 Input Slot Valid Register 2 */
#घोषणा BA0_ACSAD2		0x04f8	/* AC'97 Status Address Register 2 */
#घोषणा BA0_ACSDA2		0x04fc	/* AC'97 Status Data Register 2 */
#घोषणा BA0_FMSR		0x0730	/* FM Synthesis Status (ro) */
#घोषणा BA0_B0AP		0x0730	/* FM Bank 0 Address Port (wo) */
#घोषणा BA0_FMDP		0x0734	/* FM Data Port */
#घोषणा BA0_B1AP		0x0738	/* FM Bank 1 Address Port */
#घोषणा BA0_B1DP		0x073c	/* FM Bank 1 Data Port */

#घोषणा BA0_SSPM		0x0740	/* Sound System Power Management */
#घोषणा BA0_SSPM_MIXEN		(1<<6)	/* Playback SRC + FM/Wavetable MIX */
#घोषणा BA0_SSPM_CSRCEN		(1<<5)	/* Capture Sample Rate Converter Enable */
#घोषणा BA0_SSPM_PSRCEN		(1<<4)	/* Playback Sample Rate Converter Enable */
#घोषणा BA0_SSPM_JSEN		(1<<3)	/* Joystick Enable */
#घोषणा BA0_SSPM_ACLEN		(1<<2)	/* Serial Port Engine and AC-Link Enable */
#घोषणा BA0_SSPM_FMEN		(1<<1)	/* FM Synthesis Block Enable */

#घोषणा BA0_DACSR		0x0744	/* DAC Sample Rate - Playback SRC */
#घोषणा BA0_ADCSR		0x0748	/* ADC Sample Rate - Capture SRC */

#घोषणा BA0_SSCR		0x074c	/* Sound System Control Register */
#घोषणा BA0_SSCR_HVS1		(1<<23)	/* Hardwave Volume Step (0=1,1=2) */
#घोषणा BA0_SSCR_MVCS		(1<<19)	/* Master Volume Codec Select */
#घोषणा BA0_SSCR_MVLD		(1<<18)	/* Master Volume Line Out Disable */
#घोषणा BA0_SSCR_MVAD		(1<<17)	/* Master Volume Alternate Out Disable */
#घोषणा BA0_SSCR_MVMD		(1<<16)	/* Master Volume Mono Out Disable */
#घोषणा BA0_SSCR_XLPSRC		(1<<8)	/* External SRC Loopback Mode */
#घोषणा BA0_SSCR_LPSRC		(1<<7)	/* SRC Loopback Mode */
#घोषणा BA0_SSCR_CDTX		(1<<5)	/* CD Transfer Data */
#घोषणा BA0_SSCR_HVC		(1<<3)	/* Harware Volume Control Enable */

#घोषणा BA0_FMLVC		0x0754	/* FM Synthesis Left Volume Control */
#घोषणा BA0_FMRVC		0x0758	/* FM Synthesis Right Volume Control */
#घोषणा BA0_SRCSA		0x075c	/* SRC Slot Assignments */
#घोषणा BA0_PPLVC		0x0760	/* PCM Playback Left Volume Control */
#घोषणा BA0_PPRVC		0x0764	/* PCM Playback Right Volume Control */
#घोषणा BA0_PASR		0x0768	/* playback sample rate */
#घोषणा BA0_CASR		0x076C	/* capture sample rate */

/* Source Slot Numbers - Playback */
#घोषणा SRCSLOT_LEFT_PCM_PLAYBACK		0
#घोषणा SRCSLOT_RIGHT_PCM_PLAYBACK		1
#घोषणा SRCSLOT_PHONE_LINE_1_DAC		2
#घोषणा SRCSLOT_CENTER_PCM_PLAYBACK		3
#घोषणा SRCSLOT_LEFT_SURROUND_PCM_PLAYBACK	4
#घोषणा SRCSLOT_RIGHT_SURROUND_PCM_PLAYBACK	5
#घोषणा SRCSLOT_LFE_PCM_PLAYBACK		6
#घोषणा SRCSLOT_PHONE_LINE_2_DAC		7
#घोषणा SRCSLOT_HEADSET_DAC			8
#घोषणा SRCSLOT_LEFT_WT				29  /* invalid क्रम BA0_SRCSA */
#घोषणा SRCSLOT_RIGHT_WT			30  /* invalid क्रम BA0_SRCSA */

/* Source Slot Numbers - Capture */
#घोषणा SRCSLOT_LEFT_PCM_RECORD			10
#घोषणा SRCSLOT_RIGHT_PCM_RECORD		11
#घोषणा SRCSLOT_PHONE_LINE_1_ADC		12
#घोषणा SRCSLOT_MIC_ADC				13
#घोषणा SRCSLOT_PHONE_LINE_2_ADC		17
#घोषणा SRCSLOT_HEADSET_ADC			18
#घोषणा SRCSLOT_SECONDARY_LEFT_PCM_RECORD	20
#घोषणा SRCSLOT_SECONDARY_RIGHT_PCM_RECORD	21
#घोषणा SRCSLOT_SECONDARY_PHONE_LINE_1_ADC	22
#घोषणा SRCSLOT_SECONDARY_MIC_ADC		23
#घोषणा SRCSLOT_SECONDARY_PHONE_LINE_2_ADC	27
#घोषणा SRCSLOT_SECONDARY_HEADSET_ADC		28

/* Source Slot Numbers - Others */
#घोषणा SRCSLOT_POWER_DOWN			31

/* MIDI modes */
#घोषणा CS4281_MODE_OUTPUT		(1<<0)
#घोषणा CS4281_MODE_INPUT		(1<<1)

/* joystick bits */
/* Bits क्रम JSPT */
#घोषणा JSPT_CAX                                0x00000001
#घोषणा JSPT_CAY                                0x00000002
#घोषणा JSPT_CBX                                0x00000004
#घोषणा JSPT_CBY                                0x00000008
#घोषणा JSPT_BA1                                0x00000010
#घोषणा JSPT_BA2                                0x00000020
#घोषणा JSPT_BB1                                0x00000040
#घोषणा JSPT_BB2                                0x00000080

/* Bits क्रम JSCTL */
#घोषणा JSCTL_SP_MASK                           0x00000003
#घोषणा JSCTL_SP_SLOW                           0x00000000
#घोषणा JSCTL_SP_MEDIUM_SLOW                    0x00000001
#घोषणा JSCTL_SP_MEDIUM_FAST                    0x00000002
#घोषणा JSCTL_SP_FAST                           0x00000003
#घोषणा JSCTL_ARE                               0x00000004

/* Data रेजिस्टर pairs masks */
#घोषणा JSC1_Y1V_MASK                           0x0000FFFF
#घोषणा JSC1_X1V_MASK                           0xFFFF0000
#घोषणा JSC1_Y1V_SHIFT                          0
#घोषणा JSC1_X1V_SHIFT                          16
#घोषणा JSC2_Y2V_MASK                           0x0000FFFF
#घोषणा JSC2_X2V_MASK                           0xFFFF0000
#घोषणा JSC2_Y2V_SHIFT                          0
#घोषणा JSC2_X2V_SHIFT                          16

/* JS GPIO */
#घोषणा JSIO_DAX                                0x00000001
#घोषणा JSIO_DAY                                0x00000002
#घोषणा JSIO_DBX                                0x00000004
#घोषणा JSIO_DBY                                0x00000008
#घोषणा JSIO_AXOE                               0x00000010
#घोषणा JSIO_AYOE                               0x00000020
#घोषणा JSIO_BXOE                               0x00000040
#घोषणा JSIO_BYOE                               0x00000080

/*
 *
 */

काष्ठा cs4281_dma अणु
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक regDBA;		/* offset to DBA रेजिस्टर */
	अचिन्हित पूर्णांक regDCA;		/* offset to DCA रेजिस्टर */
	अचिन्हित पूर्णांक regDBC;		/* offset to DBC रेजिस्टर */
	अचिन्हित पूर्णांक regDCC;		/* offset to DCC रेजिस्टर */
	अचिन्हित पूर्णांक regDMR;		/* offset to DMR रेजिस्टर */
	अचिन्हित पूर्णांक regDCR;		/* offset to DCR रेजिस्टर */
	अचिन्हित पूर्णांक regHDSR;		/* offset to HDSR रेजिस्टर */
	अचिन्हित पूर्णांक regFCR;		/* offset to FCR रेजिस्टर */
	अचिन्हित पूर्णांक regFSIC;		/* offset to FSIC रेजिस्टर */
	अचिन्हित पूर्णांक valDMR;		/* DMA mode */
	अचिन्हित पूर्णांक valDCR;		/* DMA command */
	अचिन्हित पूर्णांक valFCR;		/* FIFO control */
	अचिन्हित पूर्णांक fअगरo_offset;	/* FIFO offset within BA1 */
	अचिन्हित अक्षर left_slot;	/* FIFO left slot */
	अचिन्हित अक्षर right_slot;	/* FIFO right slot */
	पूर्णांक frag;			/* period number */
पूर्ण;

#घोषणा SUSPEND_REGISTERS	20

काष्ठा cs4281 अणु
	पूर्णांक irq;

	व्योम __iomem *ba0;		/* भव (accessible) address */
	व्योम __iomem *ba1;		/* भव (accessible) address */
	अचिन्हित दीर्घ ba0_addr;
	अचिन्हित दीर्घ ba1_addr;

	पूर्णांक dual_codec;

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_ac97 *ac97_secondary;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_input;
	काष्ठा snd_rawmidi_substream *midi_output;

	काष्ठा cs4281_dma dma[4];

	अचिन्हित अक्षर src_left_play_slot;
	अचिन्हित अक्षर src_right_play_slot;
	अचिन्हित अक्षर src_left_rec_slot;
	अचिन्हित अक्षर src_right_rec_slot;

	अचिन्हित पूर्णांक spurious_dhtc_irq;
	अचिन्हित पूर्णांक spurious_dtc_irq;

	spinlock_t reg_lock;
	अचिन्हित पूर्णांक midcr;
	अचिन्हित पूर्णांक uarपंचांग;

	काष्ठा gameport *gameport;

#अगर_घोषित CONFIG_PM_SLEEP
	u32 suspend_regs[SUSPEND_REGISTERS];
#पूर्ण_अगर

पूर्ण;

अटल irqवापस_t snd_cs4281_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल स्थिर काष्ठा pci_device_id snd_cs4281_ids[] = अणु
	अणु PCI_VDEVICE(CIRRUS, 0x6005), 0, पूर्ण,	/* CS4281 */
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_cs4281_ids);

/*
 *  स्थिरants
 */

#घोषणा CS4281_FIFO_SIZE	32

/*
 *  common I/O routines
 */

अटल अंतरभूत व्योम snd_cs4281_pokeBA0(काष्ठा cs4281 *chip, अचिन्हित दीर्घ offset,
				      अचिन्हित पूर्णांक val)
अणु
        ग_लिखोl(val, chip->ba0 + offset);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_cs4281_peekBA0(काष्ठा cs4281 *chip, अचिन्हित दीर्घ offset)
अणु
        वापस पढ़ोl(chip->ba0 + offset);
पूर्ण

अटल व्योम snd_cs4281_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97,
				  अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch क्रम AC97 रेजिस्टर address
	 *  2. Write ACCDA = Command Data Register = 470h    क्रम data to ग_लिखो to AC97
	 *  3. Write ACCTL = Control Register = 460h क्रम initiating the ग_लिखो
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 07h
	 *  5. अगर DCV not cleared, अवरोध and वापस error
	 */
	काष्ठा cs4281 *chip = ac97->निजी_data;
	पूर्णांक count;

	/*
	 *  Setup the AC97 control रेजिस्टरs on the CS461x to send the
	 *  appropriate command to the AC97 to perक्रमm the पढ़ो.
	 *  ACCAD = Command Address Register = 46Ch
	 *  ACCDA = Command Data Register = 470h
	 *  ACCTL = Control Register = 460h
	 *  set DCV - will clear when process completed
	 *  reset CRW - Write command
	 *  set VFRM - valid frame enabled
	 *  set ESYN - ASYNC generation enabled
	 *  set RSTN - ARST# inactive, AC97 codec not reset
         */
	snd_cs4281_pokeBA0(chip, BA0_ACCAD, reg);
	snd_cs4281_pokeBA0(chip, BA0_ACCDA, val);
	snd_cs4281_pokeBA0(chip, BA0_ACCTL, BA0_ACCTL_DCV | BA0_ACCTL_VFRM |
				            BA0_ACCTL_ESYN | (ac97->num ? BA0_ACCTL_TC : 0));
	क्रम (count = 0; count < 2000; count++) अणु
		/*
		 *  First, we want to रुको क्रम a लघु समय.
		 */
		udelay(10);
		/*
		 *  Now, check to see अगर the ग_लिखो has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 07h
		 */
		अगर (!(snd_cs4281_peekBA0(chip, BA0_ACCTL) & BA0_ACCTL_DCV)) अणु
			वापस;
		पूर्ण
	पूर्ण
	dev_err(chip->card->dev,
		"AC'97 write problem, reg = 0x%x, val = 0x%x\n", reg, val);
पूर्ण

अटल अचिन्हित लघु snd_cs4281_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
					   अचिन्हित लघु reg)
अणु
	काष्ठा cs4281 *chip = ac97->निजी_data;
	पूर्णांक count;
	अचिन्हित लघु result;
	// FIXME: अस्थिर is necessary in the following due to a bug of
	// some gcc versions
	अस्थिर पूर्णांक ac97_num = ((अस्थिर काष्ठा snd_ac97 *)ac97)->num;

	/*
	 *  1. Write ACCAD = Command Address Register = 46Ch क्रम AC97 रेजिस्टर address
	 *  2. Write ACCDA = Command Data Register = 470h    क्रम data to ग_लिखो to AC97 
	 *  3. Write ACCTL = Control Register = 460h क्रम initiating the ग_लिखो
	 *  4. Read ACCTL = 460h, DCV should be reset by now and 460h = 17h
	 *  5. अगर DCV not cleared, अवरोध and वापस error
	 *  6. Read ACSTS = Status Register = 464h, check VSTS bit
	 */

	snd_cs4281_peekBA0(chip, ac97_num ? BA0_ACSDA2 : BA0_ACSDA);

	/*
	 *  Setup the AC97 control रेजिस्टरs on the CS461x to send the
	 *  appropriate command to the AC97 to perक्रमm the पढ़ो.
	 *  ACCAD = Command Address Register = 46Ch
	 *  ACCDA = Command Data Register = 470h
	 *  ACCTL = Control Register = 460h
	 *  set DCV - will clear when process completed
	 *  set CRW - Read command
	 *  set VFRM - valid frame enabled
	 *  set ESYN - ASYNC generation enabled
	 *  set RSTN - ARST# inactive, AC97 codec not reset
	 */

	snd_cs4281_pokeBA0(chip, BA0_ACCAD, reg);
	snd_cs4281_pokeBA0(chip, BA0_ACCDA, 0);
	snd_cs4281_pokeBA0(chip, BA0_ACCTL, BA0_ACCTL_DCV | BA0_ACCTL_CRW |
					    BA0_ACCTL_VFRM | BA0_ACCTL_ESYN |
			   (ac97_num ? BA0_ACCTL_TC : 0));


	/*
	 *  Wait क्रम the पढ़ो to occur.
	 */
	क्रम (count = 0; count < 500; count++) अणु
		/*
		 *  First, we want to रुको क्रम a लघु समय.
	 	 */
		udelay(10);
		/*
		 *  Now, check to see अगर the पढ़ो has completed.
		 *  ACCTL = 460h, DCV should be reset by now and 460h = 17h
		 */
		अगर (!(snd_cs4281_peekBA0(chip, BA0_ACCTL) & BA0_ACCTL_DCV))
			जाओ __ok1;
	पूर्ण

	dev_err(chip->card->dev,
		"AC'97 read problem (ACCTL_DCV), reg = 0x%x\n", reg);
	result = 0xffff;
	जाओ __end;
	
      __ok1:
	/*
	 *  Wait क्रम the valid status bit to go active.
	 */
	क्रम (count = 0; count < 100; count++) अणु
		/*
		 *  Read the AC97 status रेजिस्टर.
		 *  ACSTS = Status Register = 464h
		 *  VSTS - Valid Status
		 */
		अगर (snd_cs4281_peekBA0(chip, ac97_num ? BA0_ACSTS2 : BA0_ACSTS) & BA0_ACSTS_VSTS)
			जाओ __ok2;
		udelay(10);
	पूर्ण
	
	dev_err(chip->card->dev,
		"AC'97 read problem (ACSTS_VSTS), reg = 0x%x\n", reg);
	result = 0xffff;
	जाओ __end;

      __ok2:
	/*
	 *  Read the data वापसed from the AC97 रेजिस्टर.
	 *  ACSDA = Status Data Register = 474h
	 */
	result = snd_cs4281_peekBA0(chip, ac97_num ? BA0_ACSDA2 : BA0_ACSDA);

      __end:
	वापस result;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_cs4281_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा cs4281_dma *dma = substream->runसमय->निजी_data;
	काष्ठा cs4281 *chip = snd_pcm_substream_chip(substream);

	spin_lock(&chip->reg_lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		dma->valDCR |= BA0_DCR_MSK;
		dma->valFCR |= BA0_FCR_FEN;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		dma->valDCR &= ~BA0_DCR_MSK;
		dma->valFCR &= ~BA0_FCR_FEN;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		snd_cs4281_pokeBA0(chip, dma->regDMR, dma->valDMR & ~BA0_DMR_DMA);
		dma->valDMR |= BA0_DMR_DMA;
		dma->valDCR &= ~BA0_DCR_MSK;
		dma->valFCR |= BA0_FCR_FEN;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		dma->valDMR &= ~(BA0_DMR_DMA|BA0_DMR_POLL);
		dma->valDCR |= BA0_DCR_MSK;
		dma->valFCR &= ~BA0_FCR_FEN;
		/* Leave wave playback FIFO enabled क्रम FM */
		अगर (dma->regFCR != BA0_FCR0)
			dma->valFCR &= ~BA0_FCR_FEN;
		अवरोध;
	शेष:
		spin_unlock(&chip->reg_lock);
		वापस -EINVAL;
	पूर्ण
	snd_cs4281_pokeBA0(chip, dma->regDMR, dma->valDMR);
	snd_cs4281_pokeBA0(chip, dma->regFCR, dma->valFCR);
	snd_cs4281_pokeBA0(chip, dma->regDCR, dma->valDCR);
	spin_unlock(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक snd_cs4281_rate(अचिन्हित पूर्णांक rate, अचिन्हित पूर्णांक *real_rate)
अणु
	अचिन्हित पूर्णांक val;
	
	अगर (real_rate)
		*real_rate = rate;
	/* special "hardcoded" rates */
	चयन (rate) अणु
	हाल 8000:	वापस 5;
	हाल 11025:	वापस 4;
	हाल 16000:	वापस 3;
	हाल 22050:	वापस 2;
	हाल 44100:	वापस 1;
	हाल 48000:	वापस 0;
	शेष:
		अवरोध;
	पूर्ण
	val = 1536000 / rate;
	अगर (real_rate)
		*real_rate = 1536000 / val;
	वापस val;
पूर्ण

अटल व्योम snd_cs4281_mode(काष्ठा cs4281 *chip, काष्ठा cs4281_dma *dma,
			    काष्ठा snd_pcm_runसमय *runसमय,
			    पूर्णांक capture, पूर्णांक src)
अणु
	पूर्णांक rec_mono;

	dma->valDMR = BA0_DMR_TYPE_SINGLE | BA0_DMR_AUTO |
		      (capture ? BA0_DMR_TR_WRITE : BA0_DMR_TR_READ);
	अगर (runसमय->channels == 1)
		dma->valDMR |= BA0_DMR_MONO;
	अगर (snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat) > 0)
		dma->valDMR |= BA0_DMR_USIGN;
	अगर (snd_pcm_क्रमmat_big_endian(runसमय->क्रमmat) > 0)
		dma->valDMR |= BA0_DMR_BEND;
	चयन (snd_pcm_क्रमmat_width(runसमय->क्रमmat)) अणु
	हाल 8: dma->valDMR |= BA0_DMR_SIZE8;
		अगर (runसमय->channels == 1)
			dma->valDMR |= BA0_DMR_SWAPC;
		अवरोध;
	हाल 32: dma->valDMR |= BA0_DMR_SIZE20; अवरोध;
	पूर्ण
	dma->frag = 0;	/* क्रम workaround */
	dma->valDCR = BA0_DCR_TCIE | BA0_DCR_MSK;
	अगर (runसमय->buffer_size != runसमय->period_size)
		dma->valDCR |= BA0_DCR_HTCIE;
	/* Initialize DMA */
	snd_cs4281_pokeBA0(chip, dma->regDBA, runसमय->dma_addr);
	snd_cs4281_pokeBA0(chip, dma->regDBC, runसमय->buffer_size - 1);
	rec_mono = (chip->dma[1].valDMR & BA0_DMR_MONO) == BA0_DMR_MONO;
	snd_cs4281_pokeBA0(chip, BA0_SRCSA, (chip->src_left_play_slot << 0) |
					    (chip->src_right_play_slot << 8) |
					    (chip->src_left_rec_slot << 16) |
					    ((rec_mono ? 31 : chip->src_right_rec_slot) << 24));
	अगर (!src)
		जाओ __skip_src;
	अगर (!capture) अणु
		अगर (dma->left_slot == chip->src_left_play_slot) अणु
			अचिन्हित पूर्णांक val = snd_cs4281_rate(runसमय->rate, शून्य);
			snd_BUG_ON(dma->right_slot != chip->src_right_play_slot);
			snd_cs4281_pokeBA0(chip, BA0_DACSR, val);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dma->left_slot == chip->src_left_rec_slot) अणु
			अचिन्हित पूर्णांक val = snd_cs4281_rate(runसमय->rate, शून्य);
			snd_BUG_ON(dma->right_slot != chip->src_right_rec_slot);
			snd_cs4281_pokeBA0(chip, BA0_ADCSR, val);
		पूर्ण
	पूर्ण
      __skip_src:
	/* Deactivate wave playback FIFO beक्रमe changing slot assignments */
	अगर (dma->regFCR == BA0_FCR0)
		snd_cs4281_pokeBA0(chip, dma->regFCR, snd_cs4281_peekBA0(chip, dma->regFCR) & ~BA0_FCR_FEN);
	/* Initialize FIFO */
	dma->valFCR = BA0_FCR_LS(dma->left_slot) |
		      BA0_FCR_RS(capture && (dma->valDMR & BA0_DMR_MONO) ? 31 : dma->right_slot) |
		      BA0_FCR_SZ(CS4281_FIFO_SIZE) |
		      BA0_FCR_OF(dma->fअगरo_offset);
	snd_cs4281_pokeBA0(chip, dma->regFCR, dma->valFCR | (capture ? BA0_FCR_PSH : 0));
	/* Activate FIFO again क्रम FM playback */
	अगर (dma->regFCR == BA0_FCR0)
		snd_cs4281_pokeBA0(chip, dma->regFCR, dma->valFCR | BA0_FCR_FEN);
	/* Clear FIFO Status and Interrupt Control Register */
	snd_cs4281_pokeBA0(chip, dma->regFSIC, 0);
पूर्ण

अटल पूर्णांक snd_cs4281_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cs4281_dma *dma = runसमय->निजी_data;
	काष्ठा cs4281 *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	snd_cs4281_mode(chip, dma, runसमय, 0, 1);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cs4281_dma *dma = runसमय->निजी_data;
	काष्ठा cs4281 *chip = snd_pcm_substream_chip(substream);

	spin_lock_irq(&chip->reg_lock);
	snd_cs4281_mode(chip, dma, runसमय, 1, 1);
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_cs4281_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cs4281_dma *dma = runसमय->निजी_data;
	काष्ठा cs4281 *chip = snd_pcm_substream_chip(substream);

	/*
	dev_dbg(chip->card->dev,
		"DCC = 0x%x, buffer_size = 0x%x, jiffies = %li\n",
		snd_cs4281_peekBA0(chip, dma->regDCC), runसमय->buffer_size,
	       jअगरfies);
	*/
	वापस runसमय->buffer_size -
	       snd_cs4281_peekBA0(chip, dma->regDCC) - 1;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs4281_playback =
अणु
	.info =			SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_PAUSE |
				SNDRV_PCM_INFO_RESUME,
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_U16_BE | SNDRV_PCM_FMTBIT_S16_BE |
				SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_S32_LE |
				SNDRV_PCM_FMTBIT_U32_BE | SNDRV_PCM_FMTBIT_S32_BE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(512*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(512*1024),
	.periods_min =		1,
	.periods_max =		2,
	.fअगरo_size =		CS4281_FIFO_SIZE,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_cs4281_capture =
अणु
	.info =			SNDRV_PCM_INFO_MMAP |
				SNDRV_PCM_INFO_INTERLEAVED |
				SNDRV_PCM_INFO_MMAP_VALID |
				SNDRV_PCM_INFO_PAUSE |
				SNDRV_PCM_INFO_RESUME,
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 |
				SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_S16_LE |
				SNDRV_PCM_FMTBIT_U16_BE | SNDRV_PCM_FMTBIT_S16_BE |
				SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_S32_LE |
				SNDRV_PCM_FMTBIT_U32_BE | SNDRV_PCM_FMTBIT_S32_BE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(512*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(512*1024),
	.periods_min =		1,
	.periods_max =		2,
	.fअगरo_size =		CS4281_FIFO_SIZE,
पूर्ण;

अटल पूर्णांक snd_cs4281_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs4281 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cs4281_dma *dma;

	dma = &chip->dma[0];
	dma->substream = substream;
	dma->left_slot = 0;
	dma->right_slot = 1;
	runसमय->निजी_data = dma;
	runसमय->hw = snd_cs4281_playback;
	/* should be detected from the AC'97 layer, but it seems
	   that although CS4297A rev B reports 18-bit ADC resolution,
	   samples are 20-bit */
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 20);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs4281 *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cs4281_dma *dma;

	dma = &chip->dma[1];
	dma->substream = substream;
	dma->left_slot = 10;
	dma->right_slot = 11;
	runसमय->निजी_data = dma;
	runसमय->hw = snd_cs4281_capture;
	/* should be detected from the AC'97 layer, but it seems
	   that although CS4297A rev B reports 18-bit ADC resolution,
	   samples are 20-bit */
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 20);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs4281_dma *dma = substream->runसमय->निजी_data;

	dma->substream = शून्य;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा cs4281_dma *dma = substream->runसमय->निजी_data;

	dma->substream = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_cs4281_playback_ops = अणु
	.खोलो =		snd_cs4281_playback_खोलो,
	.बंद =	snd_cs4281_playback_बंद,
	.prepare =	snd_cs4281_playback_prepare,
	.trigger =	snd_cs4281_trigger,
	.poपूर्णांकer =	snd_cs4281_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cs4281_capture_ops = अणु
	.खोलो =		snd_cs4281_capture_खोलो,
	.बंद =	snd_cs4281_capture_बंद,
	.prepare =	snd_cs4281_capture_prepare,
	.trigger =	snd_cs4281_trigger,
	.poपूर्णांकer =	snd_cs4281_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_cs4281_pcm(काष्ठा cs4281 *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(chip->card, "CS4281", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_cs4281_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_cs4281_capture_ops);

	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "CS4281");
	chip->pcm = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV, &chip->pci->dev,
				       64*1024, 512*1024);

	वापस 0;
पूर्ण

/*
 *  Mixer section
 */

#घोषणा CS_VOL_MASK	0x1f

अटल पूर्णांक snd_cs4281_info_volume(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type              = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count             = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = CS_VOL_MASK;
	वापस 0;
पूर्ण
 
अटल पूर्णांक snd_cs4281_get_volume(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cs4281 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक regL = (kcontrol->निजी_value >> 16) & 0xffff;
	पूर्णांक regR = kcontrol->निजी_value & 0xffff;
	पूर्णांक volL, volR;

	volL = CS_VOL_MASK - (snd_cs4281_peekBA0(chip, regL) & CS_VOL_MASK);
	volR = CS_VOL_MASK - (snd_cs4281_peekBA0(chip, regR) & CS_VOL_MASK);

	ucontrol->value.पूर्णांकeger.value[0] = volL;
	ucontrol->value.पूर्णांकeger.value[1] = volR;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_put_volume(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा cs4281 *chip = snd_kcontrol_chip(kcontrol);
	पूर्णांक change = 0;
	पूर्णांक regL = (kcontrol->निजी_value >> 16) & 0xffff;
	पूर्णांक regR = kcontrol->निजी_value & 0xffff;
	पूर्णांक volL, volR;

	volL = CS_VOL_MASK - (snd_cs4281_peekBA0(chip, regL) & CS_VOL_MASK);
	volR = CS_VOL_MASK - (snd_cs4281_peekBA0(chip, regR) & CS_VOL_MASK);

	अगर (ucontrol->value.पूर्णांकeger.value[0] != volL) अणु
		volL = CS_VOL_MASK - (ucontrol->value.पूर्णांकeger.value[0] & CS_VOL_MASK);
		snd_cs4281_pokeBA0(chip, regL, volL);
		change = 1;
	पूर्ण
	अगर (ucontrol->value.पूर्णांकeger.value[1] != volR) अणु
		volR = CS_VOL_MASK - (ucontrol->value.पूर्णांकeger.value[1] & CS_VOL_MASK);
		snd_cs4281_pokeBA0(chip, regR, volR);
		change = 1;
	पूर्ण
	वापस change;
पूर्ण

अटल स्थिर DECLARE_TLV_DB_SCALE(db_scale_dsp, -4650, 150, 0);

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4281_fm_vol =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "Synth Playback Volume",
	.info = snd_cs4281_info_volume, 
	.get = snd_cs4281_get_volume,
	.put = snd_cs4281_put_volume, 
	.निजी_value = ((BA0_FMLVC << 16) | BA0_FMRVC),
	.tlv = अणु .p = db_scale_dsp पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new snd_cs4281_pcm_vol =
अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
	.name = "PCM Stream Playback Volume",
	.info = snd_cs4281_info_volume, 
	.get = snd_cs4281_get_volume,
	.put = snd_cs4281_put_volume, 
	.निजी_value = ((BA0_PPLVC << 16) | BA0_PPRVC),
	.tlv = अणु .p = db_scale_dsp पूर्ण,
पूर्ण;

अटल व्योम snd_cs4281_mixer_मुक्त_ac97_bus(काष्ठा snd_ac97_bus *bus)
अणु
	काष्ठा cs4281 *chip = bus->निजी_data;
	chip->ac97_bus = शून्य;
पूर्ण

अटल व्योम snd_cs4281_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा cs4281 *chip = ac97->निजी_data;
	अगर (ac97->num)
		chip->ac97_secondary = शून्य;
	अन्यथा
		chip->ac97 = शून्य;
पूर्ण

अटल पूर्णांक snd_cs4281_mixer(काष्ठा cs4281 *chip)
अणु
	काष्ठा snd_card *card = chip->card;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_cs4281_ac97_ग_लिखो,
		.पढ़ो = snd_cs4281_ac97_पढ़ो,
	पूर्ण;

	अगर ((err = snd_ac97_bus(card, 0, &ops, chip, &chip->ac97_bus)) < 0)
		वापस err;
	chip->ac97_bus->निजी_मुक्त = snd_cs4281_mixer_मुक्त_ac97_bus;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.निजी_मुक्त = snd_cs4281_mixer_मुक्त_ac97;
	अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97)) < 0)
		वापस err;
	अगर (chip->dual_codec) अणु
		ac97.num = 1;
		अगर ((err = snd_ac97_mixer(chip->ac97_bus, &ac97, &chip->ac97_secondary)) < 0)
			वापस err;
	पूर्ण
	अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cs4281_fm_vol, chip))) < 0)
		वापस err;
	अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_cs4281_pcm_vol, chip))) < 0)
		वापस err;
	वापस 0;
पूर्ण


/*
 * proc पूर्णांकerface
 */

अटल व्योम snd_cs4281_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा cs4281 *chip = entry->निजी_data;

	snd_iम_लिखो(buffer, "Cirrus Logic CS4281\n\n");
	snd_iम_लिखो(buffer, "Spurious half IRQs   : %u\n", chip->spurious_dhtc_irq);
	snd_iम_लिखो(buffer, "Spurious end IRQs    : %u\n", chip->spurious_dtc_irq);
पूर्ण

अटल sमाप_प्रकार snd_cs4281_BA0_पढ़ो(काष्ठा snd_info_entry *entry,
				   व्योम *file_निजी_data,
				   काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t pos)
अणु
	काष्ठा cs4281 *chip = entry->निजी_data;
	
	अगर (copy_to_user_fromio(buf, chip->ba0 + pos, count))
		वापस -EFAULT;
	वापस count;
पूर्ण

अटल sमाप_प्रकार snd_cs4281_BA1_पढ़ो(काष्ठा snd_info_entry *entry,
				   व्योम *file_निजी_data,
				   काष्ठा file *file, अक्षर __user *buf,
				   माप_प्रकार count, loff_t pos)
अणु
	काष्ठा cs4281 *chip = entry->निजी_data;
	
	अगर (copy_to_user_fromio(buf, chip->ba1 + pos, count))
		वापस -EFAULT;
	वापस count;
पूर्ण

अटल स्थिर काष्ठा snd_info_entry_ops snd_cs4281_proc_ops_BA0 = अणु
	.पढ़ो = snd_cs4281_BA0_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा snd_info_entry_ops snd_cs4281_proc_ops_BA1 = अणु
	.पढ़ो = snd_cs4281_BA1_पढ़ो,
पूर्ण;

अटल व्योम snd_cs4281_proc_init(काष्ठा cs4281 *chip)
अणु
	काष्ठा snd_info_entry *entry;

	snd_card_ro_proc_new(chip->card, "cs4281", chip, snd_cs4281_proc_पढ़ो);
	अगर (! snd_card_proc_new(chip->card, "cs4281_BA0", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = chip;
		entry->c.ops = &snd_cs4281_proc_ops_BA0;
		entry->size = CS4281_BA0_SIZE;
	पूर्ण
	अगर (! snd_card_proc_new(chip->card, "cs4281_BA1", &entry)) अणु
		entry->content = SNDRV_INFO_CONTENT_DATA;
		entry->निजी_data = chip;
		entry->c.ops = &snd_cs4281_proc_ops_BA1;
		entry->size = CS4281_BA1_SIZE;
	पूर्ण
पूर्ण

/*
 * joystick support
 */

#अगर IS_REACHABLE(CONFIG_GAMEPORT)

अटल व्योम snd_cs4281_gameport_trigger(काष्ठा gameport *gameport)
अणु
	काष्ठा cs4281 *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस;
	snd_cs4281_pokeBA0(chip, BA0_JSPT, 0xff);
पूर्ण

अटल अचिन्हित अक्षर snd_cs4281_gameport_पढ़ो(काष्ठा gameport *gameport)
अणु
	काष्ठा cs4281 *chip = gameport_get_port_data(gameport);

	अगर (snd_BUG_ON(!chip))
		वापस 0;
	वापस snd_cs4281_peekBA0(chip, BA0_JSPT);
पूर्ण

#अगर_घोषित COOKED_MODE
अटल पूर्णांक snd_cs4281_gameport_cooked_पढ़ो(काष्ठा gameport *gameport,
					   पूर्णांक *axes, पूर्णांक *buttons)
अणु
	काष्ठा cs4281 *chip = gameport_get_port_data(gameport);
	अचिन्हित js1, js2, jst;
	
	अगर (snd_BUG_ON(!chip))
		वापस 0;

	js1 = snd_cs4281_peekBA0(chip, BA0_JSC1);
	js2 = snd_cs4281_peekBA0(chip, BA0_JSC2);
	jst = snd_cs4281_peekBA0(chip, BA0_JSPT);
	
	*buttons = (~jst >> 4) & 0x0F; 
	
	axes[0] = ((js1 & JSC1_Y1V_MASK) >> JSC1_Y1V_SHIFT) & 0xFFFF;
	axes[1] = ((js1 & JSC1_X1V_MASK) >> JSC1_X1V_SHIFT) & 0xFFFF;
	axes[2] = ((js2 & JSC2_Y2V_MASK) >> JSC2_Y2V_SHIFT) & 0xFFFF;
	axes[3] = ((js2 & JSC2_X2V_MASK) >> JSC2_X2V_SHIFT) & 0xFFFF;

	क्रम (jst = 0; jst < 4; ++jst)
		अगर (axes[jst] == 0xFFFF) axes[jst] = -1;
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा snd_cs4281_gameport_cooked_पढ़ो	शून्य
#पूर्ण_अगर

अटल पूर्णांक snd_cs4281_gameport_खोलो(काष्ठा gameport *gameport, पूर्णांक mode)
अणु
	चयन (mode) अणु
#अगर_घोषित COOKED_MODE
	हाल GAMEPORT_MODE_COOKED:
		वापस 0;
#पूर्ण_अगर
	हाल GAMEPORT_MODE_RAW:
		वापस 0;
	शेष:
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_create_gameport(काष्ठा cs4281 *chip)
अणु
	काष्ठा gameport *gp;

	chip->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(chip->card->dev,
			"cannot allocate memory for gameport\n");
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "CS4281 Gameport");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(chip->pci));
	gameport_set_dev_parent(gp, &chip->pci->dev);
	gp->खोलो = snd_cs4281_gameport_खोलो;
	gp->पढ़ो = snd_cs4281_gameport_पढ़ो;
	gp->trigger = snd_cs4281_gameport_trigger;
	gp->cooked_पढ़ो = snd_cs4281_gameport_cooked_पढ़ो;
	gameport_set_port_data(gp, chip);

	snd_cs4281_pokeBA0(chip, BA0_JSIO, 0xFF); // ?
	snd_cs4281_pokeBA0(chip, BA0_JSCTL, JSCTL_SP_MEDIUM_SLOW);

	gameport_रेजिस्टर_port(gp);

	वापस 0;
पूर्ण

अटल व्योम snd_cs4281_मुक्त_gameport(काष्ठा cs4281 *chip)
अणु
	अगर (chip->gameport) अणु
		gameport_unरेजिस्टर_port(chip->gameport);
		chip->gameport = शून्य;
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_cs4281_create_gameport(काष्ठा cs4281 *chip) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_cs4281_मुक्त_gameport(काष्ठा cs4281 *chip) अणु पूर्ण
#पूर्ण_अगर /* IS_REACHABLE(CONFIG_GAMEPORT) */

अटल पूर्णांक snd_cs4281_मुक्त(काष्ठा cs4281 *chip)
अणु
	snd_cs4281_मुक्त_gameport(chip);

	/* Mask पूर्णांकerrupts */
	snd_cs4281_pokeBA0(chip, BA0_HIMR, 0x7fffffff);
	/* Stop the DLL Clock logic. */
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, 0);
	/* Sound System Power Management - Turn Everything OFF */
	snd_cs4281_pokeBA0(chip, BA0_SSPM, 0);
	/* PCI पूर्णांकerface - D3 state */
	pci_set_घातer_state(chip->pci, PCI_D3hot);

	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	iounmap(chip->ba0);
	iounmap(chip->ba1);
	pci_release_regions(chip->pci);
	pci_disable_device(chip->pci);

	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा cs4281 *chip = device->device_data;
	वापस snd_cs4281_मुक्त(chip);
पूर्ण

अटल पूर्णांक snd_cs4281_chip_init(काष्ठा cs4281 *chip); /* defined below */

अटल पूर्णांक snd_cs4281_create(काष्ठा snd_card *card,
			     काष्ठा pci_dev *pci,
			     काष्ठा cs4281 **rchip,
			     पूर्णांक dual_codec)
अणु
	काष्ठा cs4281 *chip;
	अचिन्हित पूर्णांक पंचांगp;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_cs4281_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&chip->reg_lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	pci_set_master(pci);
	अगर (dual_codec < 0 || dual_codec > 3) अणु
		dev_err(card->dev, "invalid dual_codec option %d\n", dual_codec);
		dual_codec = 0;
	पूर्ण
	chip->dual_codec = dual_codec;

	अगर ((err = pci_request_regions(pci, "CS4281")) < 0) अणु
		kमुक्त(chip);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	chip->ba0_addr = pci_resource_start(pci, 0);
	chip->ba1_addr = pci_resource_start(pci, 1);

	chip->ba0 = pci_ioremap_bar(pci, 0);
	chip->ba1 = pci_ioremap_bar(pci, 1);
	अगर (!chip->ba0 || !chip->ba1) अणु
		snd_cs4281_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण
	
	अगर (request_irq(pci->irq, snd_cs4281_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, chip)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_cs4281_मुक्त(chip);
		वापस -ENOMEM;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;

	पंचांगp = snd_cs4281_chip_init(chip);
	अगर (पंचांगp) अणु
		snd_cs4281_मुक्त(chip);
		वापस पंचांगp;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_cs4281_मुक्त(chip);
		वापस err;
	पूर्ण

	snd_cs4281_proc_init(chip);

	*rchip = chip;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_chip_init(काष्ठा cs4281 *chip)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित दीर्घ end_समय;
	पूर्णांक retry_count = 2;

	/* Having EPPMC.FPDN=1 prevent proper chip initialisation */
	पंचांगp = snd_cs4281_peekBA0(chip, BA0_EPPMC);
	अगर (पंचांगp & BA0_EPPMC_FPDN)
		snd_cs4281_pokeBA0(chip, BA0_EPPMC, पंचांगp & ~BA0_EPPMC_FPDN);

      __retry:
	पंचांगp = snd_cs4281_peekBA0(chip, BA0_CFLR);
	अगर (पंचांगp != BA0_CFLR_DEFAULT) अणु
		snd_cs4281_pokeBA0(chip, BA0_CFLR, BA0_CFLR_DEFAULT);
		पंचांगp = snd_cs4281_peekBA0(chip, BA0_CFLR);
		अगर (पंचांगp != BA0_CFLR_DEFAULT) अणु
			dev_err(chip->card->dev,
				"CFLR setup failed (0x%x)\n", पंचांगp);
			वापस -EIO;
		पूर्ण
	पूर्ण

	/* Set the 'Configuration Write Protect' रेजिस्टर
	 * to 4281h.  Allows venकरोr-defined configuration
         * space between 0e4h and 0ffh to be written. */	
	snd_cs4281_pokeBA0(chip, BA0_CWPR, 0x4281);
	
	अगर ((पंचांगp = snd_cs4281_peekBA0(chip, BA0_SERC1)) != (BA0_SERC1_SO1EN | BA0_SERC1_AC97)) अणु
		dev_err(chip->card->dev,
			"SERC1 AC'97 check failed (0x%x)\n", पंचांगp);
		वापस -EIO;
	पूर्ण
	अगर ((पंचांगp = snd_cs4281_peekBA0(chip, BA0_SERC2)) != (BA0_SERC2_SI1EN | BA0_SERC2_AC97)) अणु
		dev_err(chip->card->dev,
			"SERC2 AC'97 check failed (0x%x)\n", पंचांगp);
		वापस -EIO;
	पूर्ण

	/* Sound System Power Management */
	snd_cs4281_pokeBA0(chip, BA0_SSPM, BA0_SSPM_MIXEN | BA0_SSPM_CSRCEN |
				           BA0_SSPM_PSRCEN | BA0_SSPM_JSEN |
				           BA0_SSPM_ACLEN | BA0_SSPM_FMEN);

	/* Serial Port Power Management */
 	/* Blast the घड़ी control रेजिस्टर to zero so that the
         * PLL starts out in a known state, and blast the master serial
         * port control रेजिस्टर to zero so that the serial ports also
         * start out in a known state. */
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, 0);
	snd_cs4281_pokeBA0(chip, BA0_SERMC, 0);

        /* Make ESYN go to zero to turn off
         * the Sync pulse on the AC97 link. */
	snd_cs4281_pokeBA0(chip, BA0_ACCTL, 0);
	udelay(50);
                
	/*  Drive the ARST# pin low क्रम a minimum of 1uS (as defined in the AC97
	 *  spec) and then drive it high.  This is करोne क्रम non AC97 modes since
	 *  there might be logic बाह्यal to the CS4281 that uses the ARST# line
	 *  क्रम a reset. */
	snd_cs4281_pokeBA0(chip, BA0_SPMC, 0);
	udelay(50);
	snd_cs4281_pokeBA0(chip, BA0_SPMC, BA0_SPMC_RSTN);
	msleep(50);

	अगर (chip->dual_codec)
		snd_cs4281_pokeBA0(chip, BA0_SPMC, BA0_SPMC_RSTN | BA0_SPMC_ASDI2E);

	/*
	 *  Set the serial port timing configuration.
	 */
	snd_cs4281_pokeBA0(chip, BA0_SERMC,
			   (chip->dual_codec ? BA0_SERMC_TCID(chip->dual_codec) : BA0_SERMC_TCID(1)) |
			   BA0_SERMC_PTC_AC97 | BA0_SERMC_MSPE);

	/*
	 *  Start the DLL Clock logic.
	 */
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, BA0_CLKCR1_DLLP);
	msleep(50);
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, BA0_CLKCR1_SWCE | BA0_CLKCR1_DLLP);

	/*
	 * Wait क्रम the DLL पढ़ोy संकेत from the घड़ी logic.
	 */
	end_समय = jअगरfies + HZ;
	करो अणु
		/*
		 *  Read the AC97 status रेजिस्टर to see अगर we've seen a CODEC
		 *  संकेत from the AC97 codec.
		 */
		अगर (snd_cs4281_peekBA0(chip, BA0_CLKCR1) & BA0_CLKCR1_DLLRDY)
			जाओ __ok0;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));

	dev_err(chip->card->dev, "DLLRDY not seen\n");
	वापस -EIO;

      __ok0:

	/*
	 *  The first thing we करो here is to enable sync generation.  As soon
	 *  as we start receiving bit घड़ी, we'll start producing the SYNC
	 *  संकेत.
	 */
	snd_cs4281_pokeBA0(chip, BA0_ACCTL, BA0_ACCTL_ESYN);

	/*
	 * Wait क्रम the codec पढ़ोy संकेत from the AC97 codec.
	 */
	end_समय = jअगरfies + HZ;
	करो अणु
		/*
		 *  Read the AC97 status रेजिस्टर to see अगर we've seen a CODEC
		 *  संकेत from the AC97 codec.
		 */
		अगर (snd_cs4281_peekBA0(chip, BA0_ACSTS) & BA0_ACSTS_CRDY)
			जाओ __ok1;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));

	dev_err(chip->card->dev,
		"never read codec ready from AC'97 (0x%x)\n",
		snd_cs4281_peekBA0(chip, BA0_ACSTS));
	वापस -EIO;

      __ok1:
	अगर (chip->dual_codec) अणु
		end_समय = jअगरfies + HZ;
		करो अणु
			अगर (snd_cs4281_peekBA0(chip, BA0_ACSTS2) & BA0_ACSTS_CRDY)
				जाओ __codec2_ok;
			schedule_समयout_unपूर्णांकerruptible(1);
		पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));
		dev_info(chip->card->dev,
			 "secondary codec doesn't respond. disable it...\n");
		chip->dual_codec = 0;
	__codec2_ok: ;
	पूर्ण

	/*
	 *  Assert the valid frame संकेत so that we can start sending commands
	 *  to the AC97 codec.
	 */

	snd_cs4281_pokeBA0(chip, BA0_ACCTL, BA0_ACCTL_VFRM | BA0_ACCTL_ESYN);

	/*
	 *  Wait until we've sampled input slots 3 and 4 as valid, meaning that
	 *  the codec is pumping ADC data across the AC-link.
	 */

	end_समय = jअगरfies + HZ;
	करो अणु
		/*
		 *  Read the input slot valid रेजिस्टर and see अगर input slots 3
		 *  4 are valid yet.
		 */
                अगर ((snd_cs4281_peekBA0(chip, BA0_ACISV) & (BA0_ACISV_SLV(3) | BA0_ACISV_SLV(4))) == (BA0_ACISV_SLV(3) | BA0_ACISV_SLV(4)))
                        जाओ __ok2;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after_eq(end_समय, jअगरfies));

	अगर (--retry_count > 0)
		जाओ __retry;
	dev_err(chip->card->dev, "never read ISV3 and ISV4 from AC'97\n");
	वापस -EIO;

      __ok2:

	/*
	 *  Now, निश्चित valid frame and the slot 3 and 4 valid bits.  This will
	 *  commense the transfer of digital audio data to the AC97 codec.
	 */
	snd_cs4281_pokeBA0(chip, BA0_ACOSV, BA0_ACOSV_SLV(3) | BA0_ACOSV_SLV(4));

	/*
	 *  Initialize DMA काष्ठाures
	 */
	क्रम (पंचांगp = 0; पंचांगp < 4; पंचांगp++) अणु
		काष्ठा cs4281_dma *dma = &chip->dma[पंचांगp];
		dma->regDBA = BA0_DBA0 + (पंचांगp * 0x10);
		dma->regDCA = BA0_DCA0 + (पंचांगp * 0x10);
		dma->regDBC = BA0_DBC0 + (पंचांगp * 0x10);
		dma->regDCC = BA0_DCC0 + (पंचांगp * 0x10);
		dma->regDMR = BA0_DMR0 + (पंचांगp * 8);
		dma->regDCR = BA0_DCR0 + (पंचांगp * 8);
		dma->regHDSR = BA0_HDSR0 + (पंचांगp * 4);
		dma->regFCR = BA0_FCR0 + (पंचांगp * 4);
		dma->regFSIC = BA0_FSIC0 + (पंचांगp * 4);
		dma->fअगरo_offset = पंचांगp * CS4281_FIFO_SIZE;
		snd_cs4281_pokeBA0(chip, dma->regFCR,
				   BA0_FCR_LS(31) |
				   BA0_FCR_RS(31) |
				   BA0_FCR_SZ(CS4281_FIFO_SIZE) |
				   BA0_FCR_OF(dma->fअगरo_offset));
	पूर्ण

	chip->src_left_play_slot = 0;	/* AC'97 left PCM playback (3) */
	chip->src_right_play_slot = 1;	/* AC'97 right PCM playback (4) */
	chip->src_left_rec_slot = 10;	/* AC'97 left PCM record (3) */
	chip->src_right_rec_slot = 11;	/* AC'97 right PCM record (4) */

	/* Activate wave playback FIFO क्रम FM playback */
	chip->dma[0].valFCR = BA0_FCR_FEN | BA0_FCR_LS(0) |
		              BA0_FCR_RS(1) |
 	  	              BA0_FCR_SZ(CS4281_FIFO_SIZE) |
		              BA0_FCR_OF(chip->dma[0].fअगरo_offset);
	snd_cs4281_pokeBA0(chip, chip->dma[0].regFCR, chip->dma[0].valFCR);
	snd_cs4281_pokeBA0(chip, BA0_SRCSA, (chip->src_left_play_slot << 0) |
					    (chip->src_right_play_slot << 8) |
					    (chip->src_left_rec_slot << 16) |
					    (chip->src_right_rec_slot << 24));

	/* Initialize digital volume */
	snd_cs4281_pokeBA0(chip, BA0_PPLVC, 0);
	snd_cs4281_pokeBA0(chip, BA0_PPRVC, 0);

	/* Enable IRQs */
	snd_cs4281_pokeBA0(chip, BA0_HICR, BA0_HICR_EOI);
	/* Unmask पूर्णांकerrupts */
	snd_cs4281_pokeBA0(chip, BA0_HIMR, 0x7fffffff & ~(
					BA0_HISR_MIDI |
					BA0_HISR_DMAI |
					BA0_HISR_DMA(0) |
					BA0_HISR_DMA(1) |
					BA0_HISR_DMA(2) |
					BA0_HISR_DMA(3)));

	वापस 0;
पूर्ण

/*
 *  MIDI section
 */

अटल व्योम snd_cs4281_midi_reset(काष्ठा cs4281 *chip)
अणु
	snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr | BA0_MIDCR_MRST);
	udelay(100);
	snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
पूर्ण

अटल पूर्णांक snd_cs4281_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा cs4281 *chip = substream->rmidi->निजी_data;

	spin_lock_irq(&chip->reg_lock);
 	chip->midcr |= BA0_MIDCR_RXE;
	chip->midi_input = substream;
	अगर (!(chip->uarपंचांग & CS4281_MODE_OUTPUT)) अणु
		snd_cs4281_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा cs4281 *chip = substream->rmidi->निजी_data;

	spin_lock_irq(&chip->reg_lock);
	chip->midcr &= ~(BA0_MIDCR_RXE | BA0_MIDCR_RIE);
	chip->midi_input = शून्य;
	अगर (!(chip->uarपंचांग & CS4281_MODE_OUTPUT)) अणु
		snd_cs4281_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	chip->uarपंचांग &= ~CS4281_MODE_INPUT;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा cs4281 *chip = substream->rmidi->निजी_data;

	spin_lock_irq(&chip->reg_lock);
	chip->uarपंचांग |= CS4281_MODE_OUTPUT;
	chip->midcr |= BA0_MIDCR_TXE;
	chip->midi_output = substream;
	अगर (!(chip->uarपंचांग & CS4281_MODE_INPUT)) अणु
		snd_cs4281_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cs4281_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा cs4281 *chip = substream->rmidi->निजी_data;

	spin_lock_irq(&chip->reg_lock);
	chip->midcr &= ~(BA0_MIDCR_TXE | BA0_MIDCR_TIE);
	chip->midi_output = शून्य;
	अगर (!(chip->uarपंचांग & CS4281_MODE_INPUT)) अणु
		snd_cs4281_midi_reset(chip);
	पूर्ण अन्यथा अणु
		snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
	पूर्ण
	chip->uarपंचांग &= ~CS4281_MODE_OUTPUT;
	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल व्योम snd_cs4281_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cs4281 *chip = substream->rmidi->निजी_data;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (up) अणु
		अगर ((chip->midcr & BA0_MIDCR_RIE) == 0) अणु
			chip->midcr |= BA0_MIDCR_RIE;
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->midcr & BA0_MIDCR_RIE) अणु
			chip->midcr &= ~BA0_MIDCR_RIE;
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल व्योम snd_cs4281_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cs4281 *chip = substream->rmidi->निजी_data;
	अचिन्हित अक्षर byte;

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (up) अणु
		अगर ((chip->midcr & BA0_MIDCR_TIE) == 0) अणु
			chip->midcr |= BA0_MIDCR_TIE;
			/* fill UART FIFO buffer at first, and turn Tx पूर्णांकerrupts only अगर necessary */
			जबतक ((chip->midcr & BA0_MIDCR_TIE) &&
			       (snd_cs4281_peekBA0(chip, BA0_MIDSR) & BA0_MIDSR_TBF) == 0) अणु
				अगर (snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					chip->midcr &= ~BA0_MIDCR_TIE;
				पूर्ण अन्यथा अणु
					snd_cs4281_pokeBA0(chip, BA0_MIDWP, byte);
				पूर्ण
			पूर्ण
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->midcr & BA0_MIDCR_TIE) अणु
			chip->midcr &= ~BA0_MIDCR_TIE;
			snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_cs4281_midi_output =
अणु
	.खोलो =		snd_cs4281_midi_output_खोलो,
	.बंद =	snd_cs4281_midi_output_बंद,
	.trigger =	snd_cs4281_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_cs4281_midi_input =
अणु
	.खोलो = 	snd_cs4281_midi_input_खोलो,
	.बंद =	snd_cs4281_midi_input_बंद,
	.trigger =	snd_cs4281_midi_input_trigger,
पूर्ण;

अटल पूर्णांक snd_cs4281_midi(काष्ठा cs4281 *chip, पूर्णांक device)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(chip->card, "CS4281", device, 1, 1, &rmidi)) < 0)
		वापस err;
	म_नकल(rmidi->name, "CS4281");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_cs4281_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_cs4281_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = chip;
	chip->rmidi = rmidi;
	वापस 0;
पूर्ण

/*
 *  Interrupt handler
 */

अटल irqवापस_t snd_cs4281_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा cs4281 *chip = dev_id;
	अचिन्हित पूर्णांक status, dma, val;
	काष्ठा cs4281_dma *cdma;

	अगर (chip == शून्य)
		वापस IRQ_NONE;
	status = snd_cs4281_peekBA0(chip, BA0_HISR);
	अगर ((status & 0x7fffffff) == 0) अणु
		snd_cs4281_pokeBA0(chip, BA0_HICR, BA0_HICR_EOI);
		वापस IRQ_NONE;
	पूर्ण

	अगर (status & (BA0_HISR_DMA(0)|BA0_HISR_DMA(1)|BA0_HISR_DMA(2)|BA0_HISR_DMA(3))) अणु
		क्रम (dma = 0; dma < 4; dma++)
			अगर (status & BA0_HISR_DMA(dma)) अणु
				cdma = &chip->dma[dma];
				spin_lock(&chip->reg_lock);
				/* ack DMA IRQ */
				val = snd_cs4281_peekBA0(chip, cdma->regHDSR);
				/* workaround, someबार CS4281 acknowledges */
				/* end or middle transfer position twice */
				cdma->frag++;
				अगर ((val & BA0_HDSR_DHTC) && !(cdma->frag & 1)) अणु
					cdma->frag--;
					chip->spurious_dhtc_irq++;
					spin_unlock(&chip->reg_lock);
					जारी;
				पूर्ण
				अगर ((val & BA0_HDSR_DTC) && (cdma->frag & 1)) अणु
					cdma->frag--;
					chip->spurious_dtc_irq++;
					spin_unlock(&chip->reg_lock);
					जारी;
				पूर्ण
				spin_unlock(&chip->reg_lock);
				snd_pcm_period_elapsed(cdma->substream);
			पूर्ण
	पूर्ण

	अगर ((status & BA0_HISR_MIDI) && chip->rmidi) अणु
		अचिन्हित अक्षर c;
		
		spin_lock(&chip->reg_lock);
		जबतक ((snd_cs4281_peekBA0(chip, BA0_MIDSR) & BA0_MIDSR_RBE) == 0) अणु
			c = snd_cs4281_peekBA0(chip, BA0_MIDRP);
			अगर ((chip->midcr & BA0_MIDCR_RIE) == 0)
				जारी;
			snd_rawmidi_receive(chip->midi_input, &c, 1);
		पूर्ण
		जबतक ((snd_cs4281_peekBA0(chip, BA0_MIDSR) & BA0_MIDSR_TBF) == 0) अणु
			अगर ((chip->midcr & BA0_MIDCR_TIE) == 0)
				अवरोध;
			अगर (snd_rawmidi_transmit(chip->midi_output, &c, 1) != 1) अणु
				chip->midcr &= ~BA0_MIDCR_TIE;
				snd_cs4281_pokeBA0(chip, BA0_MIDCR, chip->midcr);
				अवरोध;
			पूर्ण
			snd_cs4281_pokeBA0(chip, BA0_MIDWP, c);
		पूर्ण
		spin_unlock(&chip->reg_lock);
	पूर्ण

	/* EOI to the PCI part... reenables पूर्णांकerrupts */
	snd_cs4281_pokeBA0(chip, BA0_HICR, BA0_HICR_EOI);

	वापस IRQ_HANDLED;
पूर्ण


/*
 * OPL3 command
 */
अटल व्योम snd_cs4281_opl3_command(काष्ठा snd_opl3 *opl3, अचिन्हित लघु cmd,
				    अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा cs4281 *chip = opl3->निजी_data;
	व्योम __iomem *port;

	अगर (cmd & OPL3_RIGHT)
		port = chip->ba0 + BA0_B1AP; /* right port */
	अन्यथा
		port = chip->ba0 + BA0_B0AP; /* left port */

	spin_lock_irqsave(&opl3->reg_lock, flags);

	ग_लिखोl((अचिन्हित पूर्णांक)cmd, port);
	udelay(10);

	ग_लिखोl((अचिन्हित पूर्णांक)val, port + 4);
	udelay(30);

	spin_unlock_irqrestore(&opl3->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_cs4281_probe(काष्ठा pci_dev *pci,
			    स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा cs4281 *chip;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

        अगर (dev >= SNDRV_CARDS)
                वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;

	अगर ((err = snd_cs4281_create(card, pci, &chip, dual_codec[dev])) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = chip;

	अगर ((err = snd_cs4281_mixer(chip)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_cs4281_pcm(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_cs4281_midi(chip, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_opl3_new(card, OPL3_HW_OPL3_CS4281, &opl3)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	opl3->निजी_data = chip;
	opl3->command = snd_cs4281_opl3_command;
	snd_opl3_init(opl3);
	अगर ((err = snd_opl3_hwdep_new(opl3, 0, 1, शून्य)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	snd_cs4281_create_gameport(chip);
	म_नकल(card->driver, "CS4281");
	म_नकल(card->लघुname, "Cirrus Logic CS4281");
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d",
		card->लघुname,
		chip->ba0_addr,
		chip->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_cs4281_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

/*
 * Power Management
 */
#अगर_घोषित CONFIG_PM_SLEEP

अटल स्थिर पूर्णांक saved_regs[SUSPEND_REGISTERS] = अणु
	BA0_JSCTL,
	BA0_GPIOR,
	BA0_SSCR,
	BA0_MIDCR,
	BA0_SRCSA,
	BA0_PASR,
	BA0_CASR,
	BA0_DACSR,
	BA0_ADCSR,
	BA0_FMLVC,
	BA0_FMRVC,
	BA0_PPLVC,
	BA0_PPRVC,
पूर्ण;

#घोषणा CLKCR1_CKRA                             0x00010000L

अटल पूर्णांक cs4281_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा cs4281 *chip = card->निजी_data;
	u32 ulCLK;
	अचिन्हित पूर्णांक i;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	snd_ac97_suspend(chip->ac97_secondary);

	ulCLK = snd_cs4281_peekBA0(chip, BA0_CLKCR1);
	ulCLK |= CLKCR1_CKRA;
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, ulCLK);

	/* Disable पूर्णांकerrupts. */
	snd_cs4281_pokeBA0(chip, BA0_HICR, BA0_HICR_CHGM);

	/* remember the status रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		अगर (saved_regs[i])
			chip->suspend_regs[i] = snd_cs4281_peekBA0(chip, saved_regs[i]);

	/* Turn off the serial ports. */
	snd_cs4281_pokeBA0(chip, BA0_SERMC, 0);

	/* Power off FM, Joystick, AC link, */
	snd_cs4281_pokeBA0(chip, BA0_SSPM, 0);

	/* DLL off. */
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, 0);

	/* AC link off. */
	snd_cs4281_pokeBA0(chip, BA0_SPMC, 0);

	ulCLK = snd_cs4281_peekBA0(chip, BA0_CLKCR1);
	ulCLK &= ~CLKCR1_CKRA;
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, ulCLK);
	वापस 0;
पूर्ण

अटल पूर्णांक cs4281_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा cs4281 *chip = card->निजी_data;
	अचिन्हित पूर्णांक i;
	u32 ulCLK;

	ulCLK = snd_cs4281_peekBA0(chip, BA0_CLKCR1);
	ulCLK |= CLKCR1_CKRA;
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, ulCLK);

	snd_cs4281_chip_init(chip);

	/* restore the status रेजिस्टरs */
	क्रम (i = 0; i < ARRAY_SIZE(saved_regs); i++)
		अगर (saved_regs[i])
			snd_cs4281_pokeBA0(chip, saved_regs[i], chip->suspend_regs[i]);

	snd_ac97_resume(chip->ac97);
	snd_ac97_resume(chip->ac97_secondary);

	ulCLK = snd_cs4281_peekBA0(chip, BA0_CLKCR1);
	ulCLK &= ~CLKCR1_CKRA;
	snd_cs4281_pokeBA0(chip, BA0_CLKCR1, ulCLK);

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(cs4281_pm, cs4281_suspend, cs4281_resume);
#घोषणा CS4281_PM_OPS	&cs4281_pm
#अन्यथा
#घोषणा CS4281_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा pci_driver cs4281_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_cs4281_ids,
	.probe = snd_cs4281_probe,
	.हटाओ = snd_cs4281_हटाओ,
	.driver = अणु
		.pm = CS4281_PM_OPS,
	पूर्ण,
पूर्ण;
	
module_pci_driver(cs4281_driver);
