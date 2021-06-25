<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Audio support क्रम PS3
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2006, 2007 Sony Corporation
 * All rights reserved.
 */

/*
 * पूर्णांकerrupt / configure रेजिस्टरs
 */

#घोषणा PS3_AUDIO_INTR_0                 (0x00000100)
#घोषणा PS3_AUDIO_INTR_EN_0              (0x00000140)
#घोषणा PS3_AUDIO_CONFIG                 (0x00000200)

/*
 * DMAC रेजिस्टरs
 * n:0..9
 */
#घोषणा PS3_AUDIO_DMAC_REGBASE(x)         (0x0000210 + 0x20 * (x))

#घोषणा PS3_AUDIO_KICK(n)                 (PS3_AUDIO_DMAC_REGBASE(n) + 0x00)
#घोषणा PS3_AUDIO_SOURCE(n)               (PS3_AUDIO_DMAC_REGBASE(n) + 0x04)
#घोषणा PS3_AUDIO_DEST(n)                 (PS3_AUDIO_DMAC_REGBASE(n) + 0x08)
#घोषणा PS3_AUDIO_DMASIZE(n)              (PS3_AUDIO_DMAC_REGBASE(n) + 0x0C)

/*
 * mute control
 */
#घोषणा PS3_AUDIO_AX_MCTRL                (0x00004000)
#घोषणा PS3_AUDIO_AX_ISBP                 (0x00004004)
#घोषणा PS3_AUDIO_AX_AOBP                 (0x00004008)
#घोषणा PS3_AUDIO_AX_IC                   (0x00004010)
#घोषणा PS3_AUDIO_AX_IE                   (0x00004014)
#घोषणा PS3_AUDIO_AX_IS                   (0x00004018)

/*
 * three wire serial
 * n:0..3
 */
#घोषणा PS3_AUDIO_AO_MCTRL                (0x00006000)
#घोषणा PS3_AUDIO_AO_3WMCTRL              (0x00006004)

#घोषणा PS3_AUDIO_AO_3WCTRL(n)            (0x00006200 + 0x200 * (n))

/*
 * S/PDIF
 * n:0..1
 * x:0..11
 * y:0..5
 */
#घोषणा PS3_AUDIO_AO_SPD_REGBASE(n)       (0x00007200 + 0x200 * (n))

#घोषणा PS3_AUDIO_AO_SPDCTRL(n) \
	(PS3_AUDIO_AO_SPD_REGBASE(n) + 0x00)
#घोषणा PS3_AUDIO_AO_SPDUB(n, x) \
	(PS3_AUDIO_AO_SPD_REGBASE(n) + 0x04 + 0x04 * (x))
#घोषणा PS3_AUDIO_AO_SPDCS(n, y) \
	(PS3_AUDIO_AO_SPD_REGBASE(n) + 0x34 + 0x04 * (y))


/*
  PS3_AUDIO_INTR_0 रेजिस्टर tells an पूर्णांकerrupt handler which audio
  DMA channel triggered the पूर्णांकerrupt.  The पूर्णांकerrupt status क्रम a channel
  can be cleared by writing a '1' to the corresponding bit.  A new पूर्णांकerrupt
  cannot be generated until the previous पूर्णांकerrupt has been cleared.

  Note that the status reported by PS3_AUDIO_INTR_0 is independent of the
  value of PS3_AUDIO_INTR_EN_0.

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0 0 0 0 0 0|C|0|C|0|C|0|C|0|C|0|C|0|C|0|C|0|C|0|C| INTR_0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/
#घोषणा PS3_AUDIO_INTR_0_CHAN(n)	(1 << ((n) * 2))
#घोषणा PS3_AUDIO_INTR_0_CHAN9     PS3_AUDIO_INTR_0_CHAN(9)
#घोषणा PS3_AUDIO_INTR_0_CHAN8     PS3_AUDIO_INTR_0_CHAN(8)
#घोषणा PS3_AUDIO_INTR_0_CHAN7     PS3_AUDIO_INTR_0_CHAN(7)
#घोषणा PS3_AUDIO_INTR_0_CHAN6     PS3_AUDIO_INTR_0_CHAN(6)
#घोषणा PS3_AUDIO_INTR_0_CHAN5     PS3_AUDIO_INTR_0_CHAN(5)
#घोषणा PS3_AUDIO_INTR_0_CHAN4     PS3_AUDIO_INTR_0_CHAN(4)
#घोषणा PS3_AUDIO_INTR_0_CHAN3     PS3_AUDIO_INTR_0_CHAN(3)
#घोषणा PS3_AUDIO_INTR_0_CHAN2     PS3_AUDIO_INTR_0_CHAN(2)
#घोषणा PS3_AUDIO_INTR_0_CHAN1     PS3_AUDIO_INTR_0_CHAN(1)
#घोषणा PS3_AUDIO_INTR_0_CHAN0     PS3_AUDIO_INTR_0_CHAN(0)

/*
  The PS3_AUDIO_INTR_EN_0 रेजिस्टर specअगरies which DMA channels can generate
  an पूर्णांकerrupt to the PU.  Each bit of PS3_AUDIO_INTR_EN_0 is ANDed with the
  corresponding bit in PS3_AUDIO_INTR_0.  The resulting bits are OR'd together
  to generate the Audio पूर्णांकerrupt.

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0 0 0 0 0 0|C|0|C|0|C|0|C|0|C|0|C|0|C|0|C|0|C|0|C| INTR_EN_0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

  Bit assignments are same as PS3_AUDIO_INTR_0
*/

/*
  PS3_AUDIO_CONFIG
  31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0|0 0 0 0 0 0 0 0|0 0 0 0 0 0 0 C|0 0 0 0 0 0 0 0| CONFIG
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

*/

/* The CLEAR field cancels all pending transfers, and stops any running DMA
   transfers.  Any पूर्णांकerrupts associated with the canceled transfers
   will occur as अगर the transfer had finished.
   Since this bit is deचिन्हित to recover from DMA related issues
   which are caused by unpredictable situations, it is preferred to रुको
   क्रम normal DMA transfer end without using this bit.
*/
#घोषणा PS3_AUDIO_CONFIG_CLEAR          (1 << 8)  /* RWIVF */

/*
  PS3_AUDIO_AX_MCTRL: Audio Port Mute Control Register

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0|A|A|A|0 0 0 0 0 0 0|S|S|A|A|A|A| AX_MCTRL
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/

/* 3 Wire Audio Serial Output Channel Mutes (0..3)  */
#घोषणा PS3_AUDIO_AX_MCTRL_ASOMT(n)     (1 << (3 - (n)))  /* RWIVF */
#घोषणा PS3_AUDIO_AX_MCTRL_ASO3MT       (1 << 0)          /* RWIVF */
#घोषणा PS3_AUDIO_AX_MCTRL_ASO2MT       (1 << 1)          /* RWIVF */
#घोषणा PS3_AUDIO_AX_MCTRL_ASO1MT       (1 << 2)          /* RWIVF */
#घोषणा PS3_AUDIO_AX_MCTRL_ASO0MT       (1 << 3)          /* RWIVF */

/* S/PDIF mutes (0,1)*/
#घोषणा PS3_AUDIO_AX_MCTRL_SPOMT(n)     (1 << (5 - (n)))  /* RWIVF */
#घोषणा PS3_AUDIO_AX_MCTRL_SPO1MT       (1 << 4)          /* RWIVF */
#घोषणा PS3_AUDIO_AX_MCTRL_SPO0MT       (1 << 5)          /* RWIVF */

/* All 3 Wire Serial Outमाला_दो Mute */
#घोषणा PS3_AUDIO_AX_MCTRL_AASOMT       (1 << 13)         /* RWIVF */

/* All S/PDIF Mute */
#घोषणा PS3_AUDIO_AX_MCTRL_ASPOMT       (1 << 14)         /* RWIVF */

/* All Audio Outमाला_दो Mute */
#घोषणा PS3_AUDIO_AX_MCTRL_AAOMT        (1 << 15)         /* RWIVF */

/*
  S/PDIF Outमाला_दो Buffer Read/Write Poपूर्णांकer Register

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0|0|SPO0B|0|SPO1B|0 0 0 0 0 0 0 0|0|SPO0B|0|SPO1B| AX_ISBP
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

*/
/*
 S/PDIF Output Channel Read Buffer Numbers
 Buffer number is  value of field.
 Indicates current पढ़ो access buffer ID from Audio Data
 Transfer controller of S/PDIF Output
*/

#घोषणा PS3_AUDIO_AX_ISBP_SPOBRN_MASK(n) (0x7 << 4 * (1 - (n))) /* R-IUF */
#घोषणा PS3_AUDIO_AX_ISBP_SPO1BRN_MASK		(0x7 << 0) /* R-IUF */
#घोषणा PS3_AUDIO_AX_ISBP_SPO0BRN_MASK		(0x7 << 4) /* R-IUF */

/*
S/PDIF Output Channel Buffer Write Numbers
Indicates current ग_लिखो access buffer ID from bus master.
*/
#घोषणा PS3_AUDIO_AX_ISBP_SPOBWN_MASK(n) (0x7 <<  4 * (5 - (n))) /* R-IUF */
#घोषणा PS3_AUDIO_AX_ISBP_SPO1BWN_MASK		(0x7 << 16) /* R-IUF */
#घोषणा PS3_AUDIO_AX_ISBP_SPO0BWN_MASK		(0x7 << 20) /* R-IUF */

/*
  3 Wire Audio Serial Outमाला_दो Buffer Read/Write
  Poपूर्णांकer Register
  Buffer number is  value of field

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0|ASO0B|0|ASO1B|0|ASO2B|0|ASO3B|0|ASO0B|0|ASO1B|0|ASO2B|0|ASO3B| AX_AOBP
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/

/*
3 Wire Audio Serial Output Channel Buffer Read Numbers
Indicates current पढ़ो access buffer Id from Audio Data Transfer
Controller of 3 Wire Audio Serial Output Channels
*/
#घोषणा PS3_AUDIO_AX_AOBP_ASOBRN_MASK(n) (0x7 << 4 * (3 - (n))) /* R-IUF */

#घोषणा PS3_AUDIO_AX_AOBP_ASO3BRN_MASK	(0x7 << 0) /* R-IUF */
#घोषणा PS3_AUDIO_AX_AOBP_ASO2BRN_MASK	(0x7 << 4) /* R-IUF */
#घोषणा PS3_AUDIO_AX_AOBP_ASO1BRN_MASK	(0x7 << 8) /* R-IUF */
#घोषणा PS3_AUDIO_AX_AOBP_ASO0BRN_MASK	(0x7 << 12) /* R-IUF */

/*
3 Wire Audio Serial Output Channel Buffer Write Numbers
Indicates current ग_लिखो access buffer ID from bus master.
*/
#घोषणा PS3_AUDIO_AX_AOBP_ASOBWN_MASK(n) (0x7 << 4 * (7 - (n))) /* R-IUF */

#घोषणा PS3_AUDIO_AX_AOBP_ASO3BWN_MASK        (0x7 << 16) /* R-IUF */
#घोषणा PS3_AUDIO_AX_AOBP_ASO2BWN_MASK        (0x7 << 20) /* R-IUF */
#घोषणा PS3_AUDIO_AX_AOBP_ASO1BWN_MASK        (0x7 << 24) /* R-IUF */
#घोषणा PS3_AUDIO_AX_AOBP_ASO0BWN_MASK        (0x7 << 28) /* R-IUF */



/*
Audio Port Interrupt Condition Register
For the fields in this रेजिस्टर, the following values apply:
0 = Interrupt is generated every पूर्णांकerrupt event.
1 = Interrupt is generated every 2 पूर्णांकerrupt events.
2 = Interrupt is generated every 4 पूर्णांकerrupt events.
3 = Reserved


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0|0 0|SPO|0 0|SPO|0 0|AAS|0 0 0 0 0 0 0 0 0 0 0 0| AX_IC
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/
/*
All 3-Wire Audio Serial Outमाला_दो Interrupt Mode
Configures the Interrupt and Signal Notअगरication
condition of all 3-wire Audio Serial Outमाला_दो.
*/
#घोषणा PS3_AUDIO_AX_IC_AASOIMD_MASK          (0x3 << 12) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IC_AASOIMD_EVERY1        (0x0 << 12) /* RWI-V */
#घोषणा PS3_AUDIO_AX_IC_AASOIMD_EVERY2        (0x1 << 12) /* RW--V */
#घोषणा PS3_AUDIO_AX_IC_AASOIMD_EVERY4        (0x2 << 12) /* RW--V */

/*
S/PDIF Output Channel Interrupt Modes
Configures the Interrupt and संकेत Notअगरication
conditions of S/PDIF output channels.
*/
#घोषणा PS3_AUDIO_AX_IC_SPO1IMD_MASK          (0x3 << 16) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IC_SPO1IMD_EVERY1        (0x0 << 16) /* RWI-V */
#घोषणा PS3_AUDIO_AX_IC_SPO1IMD_EVERY2        (0x1 << 16) /* RW--V */
#घोषणा PS3_AUDIO_AX_IC_SPO1IMD_EVERY4        (0x2 << 16) /* RW--V */

#घोषणा PS3_AUDIO_AX_IC_SPO0IMD_MASK          (0x3 << 20) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IC_SPO0IMD_EVERY1        (0x0 << 20) /* RWI-V */
#घोषणा PS3_AUDIO_AX_IC_SPO0IMD_EVERY2        (0x1 << 20) /* RW--V */
#घोषणा PS3_AUDIO_AX_IC_SPO0IMD_EVERY4        (0x2 << 20) /* RW--V */

/*
Audio Port पूर्णांकerrupt Enable Register
Configures whether to enable or disable each Interrupt Generation.


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0|S|S|0 0|A|A|A|A|0 0 0 0|S|S|0 0|S|S|0 0|A|A|A|A| AX_IE
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

*/

/*
3 Wire Audio Serial Output Channel Buffer Underflow
Interrupt Enables
Select enable/disable of Buffer Underflow Interrupts क्रम
3-Wire Audio Serial Output Channels
DISABLED=Interrupt generation disabled.
*/
#घोषणा PS3_AUDIO_AX_IE_ASOBUIE(n)      (1 << (3 - (n))) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO3BUIE        (1 << 0) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO2BUIE        (1 << 1) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO1BUIE        (1 << 2) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO0BUIE        (1 << 3) /* RWIVF */

/* S/PDIF Output Channel Buffer Underflow Interrupt Enables */

#घोषणा PS3_AUDIO_AX_IE_SPOBUIE(n)      (1 << (7 - (n))) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_SPO1BUIE        (1 << 6) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_SPO0BUIE        (1 << 7) /* RWIVF */

/* S/PDIF Output Channel One Block Transfer Completion Interrupt Enables */

#घोषणा PS3_AUDIO_AX_IE_SPOBTCIE(n)     (1 << (11 - (n))) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_SPO1BTCIE       (1 << 10) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_SPO0BTCIE       (1 << 11) /* RWIVF */

/* 3-Wire Audio Serial Output Channel Buffer Empty Interrupt Enables */

#घोषणा PS3_AUDIO_AX_IE_ASOBEIE(n)      (1 << (19 - (n))) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO3BEIE        (1 << 16) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO2BEIE        (1 << 17) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO1BEIE        (1 << 18) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_ASO0BEIE        (1 << 19) /* RWIVF */

/* S/PDIF Output Channel Buffer Empty Interrupt Enables */

#घोषणा PS3_AUDIO_AX_IE_SPOBEIE(n)      (1 << (23 - (n))) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_SPO1BEIE        (1 << 22) /* RWIVF */
#घोषणा PS3_AUDIO_AX_IE_SPO0BEIE        (1 << 23) /* RWIVF */

/*
Audio Port Interrupt Status Register
Indicates Interrupt status, which पूर्णांकerrupt has occurred, and can clear
each पूर्णांकerrupt in this रेजिस्टर.
Writing 1b to a field containing 1b clears field and de-निश्चितs पूर्णांकerrupt.
Writing 0b to a field has no effect.
Field values are the following:
0 - Interrupt hasn't occurred.
1 - Interrupt has occurred.


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0|S|S|0 0|A|A|A|A|0 0 0 0|S|S|0 0|S|S|0 0|A|A|A|A| AX_IS
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

 Bit assignment are same as AX_IE
*/

/*
Audio Output Master Control Register
Configures Master Clock and other master Audio Output Settings


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0|SCKSE|0|SCKSE|  MR0  |  MR1  |MCL|MCL|0 0 0 0|0 0 0 0 0 0 0 0| AO_MCTRL
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/

/*
MCLK Output Control
Controls mclko[1] output.
0 - Disable output (fixed at High)
1 - Output घड़ी produced by घड़ी selected
with scksel1 by mr1
2 - Reserved
3 - Reserved
*/

#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC1_MASK		(0x3 << 12) /* RWIVF */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC1_DISABLED	(0x0 << 12) /* RWI-V */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC1_ENABLED	(0x1 << 12) /* RW--V */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC1_RESVD2	(0x2 << 12) /* RW--V */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC1_RESVD3	(0x3 << 12) /* RW--V */

/*
MCLK Output Control
Controls mclko[0] output.
0 - Disable output (fixed at High)
1 - Output घड़ी produced by घड़ी selected
with SCKSEL0 by MR0
2 - Reserved
3 - Reserved
*/
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC0_MASK		(0x3 << 14) /* RWIVF */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC0_DISABLED	(0x0 << 14) /* RWI-V */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC0_ENABLED	(0x1 << 14) /* RW--V */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC0_RESVD2	(0x2 << 14) /* RW--V */
#घोषणा PS3_AUDIO_AO_MCTRL_MCLKC0_RESVD3	(0x3 << 14) /* RW--V */
/*
Master Clock Rate 1
Sets the भागide ration of Master Clock1 (घड़ी output from
mclko[1] क्रम the input घड़ी selected by scksel1.
*/
#घोषणा PS3_AUDIO_AO_MCTRL_MR1_MASK	(0xf << 16)
#घोषणा PS3_AUDIO_AO_MCTRL_MR1_DEFAULT	(0x0 << 16) /* RWI-V */
/*
Master Clock Rate 0
Sets the भागide ratio of Master Clock0 (घड़ी output from
mclko[0] क्रम the input घड़ी selected by scksel0).
*/
#घोषणा PS3_AUDIO_AO_MCTRL_MR0_MASK	(0xf << 20) /* RWIVF */
#घोषणा PS3_AUDIO_AO_MCTRL_MR0_DEFAULT	(0x0 << 20) /* RWI-V */
/*
System Clock Select 0/1
Selects the प्रणाली घड़ी to be used as Master Clock 0/1
Input the प्रणाली घड़ी that is appropriate क्रम the sampling
rate.
*/
#घोषणा PS3_AUDIO_AO_MCTRL_SCKSEL1_MASK		(0x7 << 24) /* RWIVF */
#घोषणा PS3_AUDIO_AO_MCTRL_SCKSEL1_DEFAULT	(0x2 << 24) /* RWI-V */

#घोषणा PS3_AUDIO_AO_MCTRL_SCKSEL0_MASK		(0x7 << 28) /* RWIVF */
#घोषणा PS3_AUDIO_AO_MCTRL_SCKSEL0_DEFAULT	(0x2 << 28) /* RWI-V */


/*
3-Wire Audio Output Master Control Register
Configures घड़ी, 3-Wire Audio Serial Output Enable, and
other 3-Wire Audio Serial Output Master Settings


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |A|A|A|A|0 0 0|A| ASOSR |0 0 0 0|A|A|A|A|A|A|0|1|0 0 0 0 0 0 0 0| AO_3WMCTRL
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/


/*
LRCKO Polarity
0 - Reserved
1 - शेष
*/
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOPLRCK 		(1 << 8) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOPLRCK_DEFAULT	(1 << 8) /* RW--V */

/* LRCK Output Disable */

#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOLRCKD		(1 << 10) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOLRCKD_ENABLED	(0 << 10) /* RW--V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOLRCKD_DISABLED	(1 << 10) /* RWI-V */

/* Bit Clock Output Disable */

#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOBCLKD		(1 << 11) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOBCLKD_ENABLED	(0 << 11) /* RW--V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOBCLKD_DISABLED	(1 << 11) /* RWI-V */

/*
3-Wire Audio Serial Output Channel 0-3 Operational
Status.  Each bit becomes 1 after each 3-Wire Audio
Serial Output Channel N is in action by setting 1 to
asoen.
Each bit becomes 0 after each 3-Wire Audio Serial Output
Channel N is out of action by setting 0 to asoen.
*/
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN(n)		(1 << (15 - (n))) /* R-IVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN_STOPPED(n)	(0 << (15 - (n))) /* R-I-V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN_RUNNING(n)	(1 << (15 - (n))) /* R---V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN0		\
	PS3_AUDIO_AO_3WMCTRL_ASORUN(0)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN0_STOPPED	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_STOPPED(0)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN0_RUNNING	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_RUNNING(0)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN1		\
	PS3_AUDIO_AO_3WMCTRL_ASORUN(1)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN1_STOPPED	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_STOPPED(1)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN1_RUNNING	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_RUNNING(1)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN2		\
	PS3_AUDIO_AO_3WMCTRL_ASORUN(2)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN2_STOPPED	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_STOPPED(2)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN2_RUNNING	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_RUNNING(2)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN3		\
	PS3_AUDIO_AO_3WMCTRL_ASORUN(3)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN3_STOPPED	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_STOPPED(3)
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASORUN3_RUNNING	\
	PS3_AUDIO_AO_3WMCTRL_ASORUN_RUNNING(3)

/*
Sampling Rate
Specअगरies the भागide ratio of the bit घड़ी (घड़ी output
from bclko) used by the 3-wire Audio Output Clock, which
is applied to the master घड़ी selected by mcksel.
Data output is synchronized with this घड़ी.
*/
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOSR_MASK		(0xf << 20) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOSR_DIV2		(0x1 << 20) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOSR_DIV4		(0x2 << 20) /* RW--V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOSR_DIV8		(0x4 << 20) /* RW--V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOSR_DIV12	(0x6 << 20) /* RW--V */

/*
Master Clock Select
0 - Master Clock 0
1 - Master Clock 1
*/
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOMCKSEL		(1 << 24) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOMCKSEL_CLK0	(0 << 24) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOMCKSEL_CLK1	(1 << 24) /* RW--V */

/*
Enables and disables 4ch 3-Wire Audio Serial Output
operation.  Each Bit from 0 to 3 corresponds to an
output channel, which means that each output channel
can be enabled or disabled inभागidually.  When
multiple channels are enabled at the same समय, output
operations are perक्रमmed in synchronization.
Bit 0 - Output Channel 0 (SDOUT[0])
Bit 1 - Output Channel 1 (SDOUT[1])
Bit 2 - Output Channel 2 (SDOUT[2])
Bit 3 - Output Channel 3 (SDOUT[3])
*/
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOEN(n)		(1 << (31 - (n))) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOEN_DISABLED(n)	(0 << (31 - (n))) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOEN_ENABLED(n)	(1 << (31 - (n))) /* RW--V */

#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOEN0 \
	PS3_AUDIO_AO_3WMCTRL_ASOEN(0) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOEN0_DISABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_DISABLED(0) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WMCTRL_ASOEN0_ENABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_ENABLED(0) /* RW--V */
#घोषणा PS3_AUDIO_A1_3WMCTRL_ASOEN0 \
	PS3_AUDIO_AO_3WMCTRL_ASOEN(1) /* RWIVF */
#घोषणा PS3_AUDIO_A1_3WMCTRL_ASOEN0_DISABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_DISABLED(1) /* RWI-V */
#घोषणा PS3_AUDIO_A1_3WMCTRL_ASOEN0_ENABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_ENABLED(1) /* RW--V */
#घोषणा PS3_AUDIO_A2_3WMCTRL_ASOEN0 \
	PS3_AUDIO_AO_3WMCTRL_ASOEN(2) /* RWIVF */
#घोषणा PS3_AUDIO_A2_3WMCTRL_ASOEN0_DISABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_DISABLED(2) /* RWI-V */
#घोषणा PS3_AUDIO_A2_3WMCTRL_ASOEN0_ENABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_ENABLED(2) /* RW--V */
#घोषणा PS3_AUDIO_A3_3WMCTRL_ASOEN0 \
	PS3_AUDIO_AO_3WMCTRL_ASOEN(3) /* RWIVF */
#घोषणा PS3_AUDIO_A3_3WMCTRL_ASOEN0_DISABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_DISABLED(3) /* RWI-V */
#घोषणा PS3_AUDIO_A3_3WMCTRL_ASOEN0_ENABLED \
	PS3_AUDIO_AO_3WMCTRL_ASOEN_ENABLED(3) /* RW--V */

/*
3-Wire Audio Serial output Channel 0-3 Control Register
Configures settings क्रम 3-Wire Serial Audio Output Channel 0-3


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0|A|0 0 0 0|A|0|ASO|0 0 0|0|0|0|0|0| AO_3WCTRL
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

*/
/*
Data Bit Mode
Specअगरies the number of data bits
0 - 16 bits
1 - reserved
2 - 20 bits
3 - 24 bits
*/
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODB_MASK	(0x3 << 8) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODB_16BIT	(0x0 << 8) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODB_RESVD	(0x1 << 8) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODB_20BIT	(0x2 << 8) /* RW--V */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODB_24BIT	(0x3 << 8) /* RW--V */
/*
Data Format Mode
Specअगरies the data क्रमmat where (LSB side or MSB) the data(in 20 bit
or 24 bit resolution mode) is put in a 32 bit field.
0 - Data put on LSB side
1 - Data put on MSB side
*/
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODF 	(1 << 11) /* RWIVF */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODF_LSB	(0 << 11) /* RWI-V */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASODF_MSB	(1 << 11) /* RW--V */
/*
Buffer Reset
Perक्रमms buffer reset.  Writing 1 to this bit initializes the
corresponding 3-Wire Audio Output buffers(both L and R).
*/
#घोषणा PS3_AUDIO_AO_3WCTRL_ASOBRST 		(1 << 16) /* CWIVF */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASOBRST_IDLE	(0 << 16) /* -WI-V */
#घोषणा PS3_AUDIO_AO_3WCTRL_ASOBRST_RESET	(1 << 16) /* -W--T */

/*
S/PDIF Audio Output Channel 0/1 Control Register
Configures settings क्रम S/PDIF Audio Output Channel 0/1.

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |S|0 0 0|S|0 0|S| SPOSR |0 0|SPO|0 0 0 0|S|0|SPO|0 0 0 0 0 0 0|S| AO_SPDCTRL
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/
/*
Buffer reset.  Writing 1 to this bit initializes the
corresponding S/PDIF output buffer poपूर्णांकer.
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOBRST		(1 << 0) /* CWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOBRST_IDLE	(0 << 0) /* -WI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOBRST_RESET	(1 << 0) /* -W--T */

/*
Data Bit Mode
Specअगरies number of data bits
0 - 16 bits
1 - Reserved
2 - 20 bits
3 - 24 bits
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODB_MASK		(0x3 << 8) /* RWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODB_16BIT	(0x0 << 8) /* RWI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODB_RESVD	(0x1 << 8) /* RW--V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODB_20BIT	(0x2 << 8) /* RW--V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODB_24BIT	(0x3 << 8) /* RW--V */
/*
Data क्रमmat Mode
Specअगरies the data क्रमmat, where (LSB side or MSB)
the data(in 20 or 24 bit resolution) is put in the
32 bit field.
0 - LSB Side
1 - MSB Side
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODF	(1 << 11) /* RWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODF_LSB	(0 << 11) /* RWI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPODF_MSB	(1 << 11) /* RW--V */
/*
Source Select
Specअगरies the source of the S/PDIF output.  When 0, output
operation is controlled by 3wen[0] of AO_3WMCTRL रेजिस्टर.
The SR must have the same setting as the a0_3wmctrl reg.
0 - 3-Wire Audio OUT Ch0 Buffer
1 - S/PDIF buffer
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSS_MASK		(0x3 << 16) /* RWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSS_3WEN		(0x0 << 16) /* RWI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSS_SPDIF	(0x1 << 16) /* RW--V */
/*
Sampling Rate
Specअगरies the भागide ratio of the bit घड़ी (घड़ी output
from bclko) used by the S/PDIF Output Clock, which
is applied to the master घड़ी selected by mcksel.
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSR		(0xf << 20) /* RWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSR_DIV2		(0x1 << 20) /* RWI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSR_DIV4		(0x2 << 20) /* RW--V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSR_DIV8		(0x4 << 20) /* RW--V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOSR_DIV12	(0x6 << 20) /* RW--V */
/*
Master Clock Select
0 - Master Clock 0
1 - Master Clock 1
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOMCKSEL		(1 << 24) /* RWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOMCKSEL_CLK0	(0 << 24) /* RWI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOMCKSEL_CLK1	(1 << 24) /* RW--V */

/*
S/PDIF Output Channel Operational Status
This bit becomes 1 after S/PDIF Output Channel is in
action by setting 1 to spoen.  This bit becomes 0
after S/PDIF Output Channel is out of action by setting
0 to spoen.
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPORUN		(1 << 27) /* R-IVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPORUN_STOPPED	(0 << 27) /* R-I-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPORUN_RUNNING	(1 << 27) /* R---V */

/*
S/PDIF Audio Output Channel Output Enable
Enables and disables output operation.  This bit is used
only when sposs = 1
*/
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOEN		(1 << 31) /* RWIVF */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOEN_DISABLED	(0 << 31) /* RWI-V */
#घोषणा PS3_AUDIO_AO_SPDCTRL_SPOEN_ENABLED	(1 << 31) /* RW--V */

/*
S/PDIF Audio Output Channel Channel Status
Setting Registers.
Configures channel status bit settings क्रम each block
(192 bits).
Output is perक्रमmed from the MSB(AO_SPDCS0 रेजिस्टर bit 31).
The same value is added क्रम subframes within the same frame.
 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |                             SPOCS                             | AO_SPDCS
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+

S/PDIF Audio Output Channel User Bit Setting
Configures user bit settings क्रम each block (384 bits).
Output is perक्रमmed from the MSB(ao_spdub0 रेजिस्टर bit 31).


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |                             SPOUB                             | AO_SPDUB
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/
/*****************************************************************************
 *
 * DMAC रेजिस्टर
 *
 *****************************************************************************/
/*
The PS3_AUDIO_KICK रेजिस्टर is used to initiate a DMA transfer and monitor
its status

 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0|STATU|0 0 0|  EVENT  |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0|R| KICK
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/
/*
The REQUEST field is written to ACTIVE to initiate a DMA request when EVENT
occurs.
It will वापस to the DONE state when the request is completed.
The रेजिस्टरs क्रम a DMA channel should only be written अगर REQUEST is IDLE.
*/

#घोषणा PS3_AUDIO_KICK_REQUEST                (1 << 0) /* RWIVF */
#घोषणा PS3_AUDIO_KICK_REQUEST_IDLE           (0 << 0) /* RWI-V */
#घोषणा PS3_AUDIO_KICK_REQUEST_ACTIVE         (1 << 0) /* -W--T */

/*
 *The EVENT field is used to set the event in which
 *the DMA request becomes active.
 */
#घोषणा PS3_AUDIO_KICK_EVENT_MASK             (0x1f << 16) /* RWIVF */
#घोषणा PS3_AUDIO_KICK_EVENT_ALWAYS           (0x00 << 16) /* RWI-V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT0_EMPTY (0x01 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT0_UNDERFLOW	(0x02 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT1_EMPTY		(0x03 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT1_UNDERFLOW	(0x04 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT2_EMPTY		(0x05 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT2_UNDERFLOW	(0x06 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT3_EMPTY		(0x07 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SERIALOUT3_UNDERFLOW	(0x08 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SPDIF0_BLOCKTRANSFERCOMPLETE \
	(0x09 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SPDIF0_UNDERFLOW		(0x0A << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SPDIF0_EMPTY		(0x0B << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SPDIF1_BLOCKTRANSFERCOMPLETE \
	(0x0C << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SPDIF1_UNDERFLOW		(0x0D << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_SPDIF1_EMPTY		(0x0E << 16) /* RW--V */

#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA(n) \
	((0x13 + (n)) << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA0         (0x13 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA1         (0x14 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA2         (0x15 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA3         (0x16 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA4         (0x17 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA5         (0x18 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA6         (0x19 << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA7         (0x1A << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA8         (0x1B << 16) /* RW--V */
#घोषणा PS3_AUDIO_KICK_EVENT_AUDIO_DMA9         (0x1C << 16) /* RW--V */

/*
The STATUS field can be used to monitor the progress of a DMA request.
DONE indicates the previous request has completed.
EVENT indicates that the DMA engine is रुकोing क्रम the EVENT to occur.
PENDING indicates that the DMA engine has not started processing this
request, but the EVENT has occurred.
DMA indicates that the data transfer is in progress.
NOTIFY indicates that the notअगरier संकेतling end of transfer is being written.
CLEAR indicated that the previous transfer was cleared.
ERROR indicates the previous transfer requested an unsupported
source/destination combination.
*/

#घोषणा PS3_AUDIO_KICK_STATUS_MASK	(0x7 << 24) /* R-IVF */
#घोषणा PS3_AUDIO_KICK_STATUS_DONE	(0x0 << 24) /* R-I-V */
#घोषणा PS3_AUDIO_KICK_STATUS_EVENT	(0x1 << 24) /* R---V */
#घोषणा PS3_AUDIO_KICK_STATUS_PENDING	(0x2 << 24) /* R---V */
#घोषणा PS3_AUDIO_KICK_STATUS_DMA	(0x3 << 24) /* R---V */
#घोषणा PS3_AUDIO_KICK_STATUS_NOTIFY	(0x4 << 24) /* R---V */
#घोषणा PS3_AUDIO_KICK_STATUS_CLEAR	(0x5 << 24) /* R---V */
#घोषणा PS3_AUDIO_KICK_STATUS_ERROR	(0x6 << 24) /* R---V */

/*
The PS3_AUDIO_SOURCE रेजिस्टर specअगरies the source address क्रम transfers.


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |                      START                      |0 0 0 0 0|TAR| SOURCE
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/

/*
The Audio DMA engine uses 128-byte transfers, thus the address must be aligned
to a 128 byte boundary.  The low seven bits are assumed to be 0.
*/

#घोषणा PS3_AUDIO_SOURCE_START_MASK	(0x01FFFFFF << 7) /* RWIUF */

/*
The TARGET field specअगरies the memory space containing the source address.
*/

#घोषणा PS3_AUDIO_SOURCE_TARGET_MASK 		(3 << 0) /* RWIVF */
#घोषणा PS3_AUDIO_SOURCE_TARGET_SYSTEM_MEMORY	(2 << 0) /* RW--V */

/*
The PS3_AUDIO_DEST रेजिस्टर specअगरies the destination address क्रम transfers.


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |                      START                      |0 0 0 0 0|TAR| DEST
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/

/*
The Audio DMA engine uses 128-byte transfers, thus the address must be aligned
to a 128 byte boundary.  The low seven bits are assumed to be 0.
*/

#घोषणा PS3_AUDIO_DEST_START_MASK	(0x01FFFFFF << 7) /* RWIUF */

/*
The TARGET field specअगरies the memory space containing the destination address
AUDIOFIFO = Audio WriteData FIFO,
*/

#घोषणा PS3_AUDIO_DEST_TARGET_MASK		(3 << 0) /* RWIVF */
#घोषणा PS3_AUDIO_DEST_TARGET_AUDIOFIFO		(1 << 0) /* RW--V */

/*
PS3_AUDIO_DMASIZE specअगरies the number of 128-byte blocks + 1 to transfer.
So a value of 0 means 128-bytes will get transferred.


 31            24 23           16 15            8 7             0
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
 |0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0|   BLOCKS    | DMASIZE
 +-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-|-+-+-+-+-+-+-+-+
*/


#घोषणा PS3_AUDIO_DMASIZE_BLOCKS_MASK 	(0x7f << 0) /* RWIUF */

/*
 * source/destination address क्रम पूर्णांकernal fअगरos
 */
#घोषणा PS3_AUDIO_AO_3W_LDATA(n)	(0x1000 + (0x100 * (n)))
#घोषणा PS3_AUDIO_AO_3W_RDATA(n)	(0x1080 + (0x100 * (n)))

#घोषणा PS3_AUDIO_AO_SPD_DATA(n)	(0x2000 + (0x400 * (n)))


/*
 * field attiribute
 *
 *	Read
 *	  ' ' = Other Inक्रमmation
 *	  '-' = Field is part of a ग_लिखो-only रेजिस्टर
 *	  'C' = Value पढ़ो is always the same, स्थिरant value line follows (C)
 *	  'R' = Value is पढ़ो
 *
 *	Write
 *	  ' ' = Other Inक्रमmation
 *	  '-' = Must not be written (D), value ignored when written (R,A,F)
 *	  'W' = Can be written
 *
 *	Internal State
 *	  ' ' = Other Inक्रमmation
 *	  '-' = No पूर्णांकernal state
 *	  'X' = Internal state, initial value is unknown
 *	  'I' = Internal state, initial value is known and follows (I)
 *
 *	Declaration/Size
 *	  ' ' = Other Inक्रमmation
 *	  '-' = Does Not Apply
 *	  'V' = Type is व्योम
 *	  'U' = Type is अचिन्हित पूर्णांकeger
 *	  'S' = Type is चिन्हित पूर्णांकeger
 *	  'F' = Type is IEEE भग्नing poपूर्णांक
 *	  '1' = Byte size (008)
 *	  '2' = Short size (016)
 *	  '3' = Three byte size (024)
 *	  '4' = Word size (032)
 *	  '8' = Double size (064)
 *
 *	Define Indicator
 *	  ' ' = Other Inक्रमmation
 *	  'D' = Device
 *	  'M' = Memory
 *	  'R' = Register
 *	  'A' = Array of Registers
 *	  'F' = Field
 *	  'V' = Value
 *	  'T' = Task
 */

