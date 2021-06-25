<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Driver क्रम Ensoniq ES1370/ES1371 AudioPCI soundcard
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *		     Thomas Sailer <sailer@अगरe.ee.ethz.ch>
 */

/* Power-Management-Code ( CONFIG_PM )
 * क्रम ens1371 only ( FIXME )
 * derived from cs4281.c, atiixp.c and via82xx.c
 * using http://www.alsa-project.org/~tiwai/writing-an-alsa-driver/ 
 * by Kurt J. Bosch
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/gameport.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <sound/core.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#अगर_घोषित CHIP1371
#समावेश <sound/ac97_codec.h>
#अन्यथा
#समावेश <sound/ak4531_codec.h>
#पूर्ण_अगर
#समावेश <sound/initval.h>
#समावेश <sound/asoundef.h>

#अगर_अघोषित CHIP1371
#अघोषित CHIP1370
#घोषणा CHIP1370
#पूर्ण_अगर

#अगर_घोषित CHIP1370
#घोषणा DRIVER_NAME "ENS1370"
#घोषणा CHIP_NAME "ES1370" /* it can be ENS but just to keep compatibility... */
#अन्यथा
#घोषणा DRIVER_NAME "ENS1371"
#घोषणा CHIP_NAME "ES1371"
#पूर्ण_अगर


MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Thomas Sailer <sailer@ife.ee.ethz.ch>");
MODULE_LICENSE("GPL");
#अगर_घोषित CHIP1370
MODULE_DESCRIPTION("Ensoniq AudioPCI ES1370");
#पूर्ण_अगर
#अगर_घोषित CHIP1371
MODULE_DESCRIPTION("Ensoniq/Creative AudioPCI ES1371+");
#पूर्ण_अगर

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK
#पूर्ण_अगर

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable चयनes */
#अगर_घोषित SUPPORT_JOYSTICK
#अगर_घोषित CHIP1371
अटल पूर्णांक joystick_port[SNDRV_CARDS];
#अन्यथा
अटल bool joystick[SNDRV_CARDS];
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CHIP1371
अटल पूर्णांक spdअगर[SNDRV_CARDS];
अटल पूर्णांक lineio[SNDRV_CARDS];
#पूर्ण_अगर

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Ensoniq AudioPCI soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Ensoniq AudioPCI soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Ensoniq AudioPCI soundcard.");
#अगर_घोषित SUPPORT_JOYSTICK
#अगर_घोषित CHIP1371
module_param_hw_array(joystick_port, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(joystick_port, "Joystick port address.");
#अन्यथा
module_param_array(joystick, bool, शून्य, 0444);
MODULE_PARM_DESC(joystick, "Enable joystick.");
#पूर्ण_अगर
#पूर्ण_अगर /* SUPPORT_JOYSTICK */
#अगर_घोषित CHIP1371
module_param_array(spdअगर, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(spdअगर, "S/PDIF output (-1 = none, 0 = auto, 1 = force).");
module_param_array(lineio, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(lineio, "Line In to Rear Out (0 = auto, 1 = force).");
#पूर्ण_अगर

/* ES1371 chip ID */
/* This is a little confusing because all ES1371 compatible chips have the
   same DEVICE_ID, the only thing dअगरferentiating them is the REV_ID field.
   This is only signअगरicant अगर you want to enable features on the later parts.
   Yes, I know it's stupid and why didn't we use the sub IDs?
*/
#घोषणा ES1371REV_ES1373_A  0x04
#घोषणा ES1371REV_ES1373_B  0x06
#घोषणा ES1371REV_CT5880_A  0x07
#घोषणा CT5880REV_CT5880_C  0x02
#घोषणा CT5880REV_CT5880_D  0x03	/* ??? -jk */
#घोषणा CT5880REV_CT5880_E  0x04	/* mw */
#घोषणा ES1371REV_ES1371_B  0x09
#घोषणा EV1938REV_EV1938_A  0x00
#घोषणा ES1371REV_ES1373_8  0x08

/*
 * Direct रेजिस्टरs
 */

#घोषणा ES_REG(ensoniq, x) ((ensoniq)->port + ES_REG_##x)

#घोषणा ES_REG_CONTROL	0x00	/* R/W: Interrupt/Chip select control रेजिस्टर */
#घोषणा   ES_1370_ADC_STOP	(1<<31)		/* disable capture buffer transfers */
#घोषणा   ES_1370_XCTL1 	(1<<30)		/* general purpose output bit */
#घोषणा   ES_1373_BYPASS_P1	(1<<31)		/* bypass SRC क्रम PB1 */
#घोषणा   ES_1373_BYPASS_P2	(1<<30)		/* bypass SRC क्रम PB2 */
#घोषणा   ES_1373_BYPASS_R	(1<<29)		/* bypass SRC क्रम REC */
#घोषणा   ES_1373_TEST_BIT	(1<<28)		/* should be set to 0 क्रम normal operation */
#घोषणा   ES_1373_RECEN_B	(1<<27)		/* mix record with playback क्रम I2S/SPDIF out */
#घोषणा   ES_1373_SPDIF_THRU	(1<<26)		/* 0 = SPDIF thru mode, 1 = SPDIF == dig out */
#घोषणा   ES_1371_JOY_ASEL(o)	(((o)&0x03)<<24)/* joystick port mapping */
#घोषणा   ES_1371_JOY_ASELM	(0x03<<24)	/* mask क्रम above */
#घोषणा   ES_1371_JOY_ASELI(i)  (((i)>>24)&0x03)
#घोषणा   ES_1371_GPIO_IN(i)	(((i)>>20)&0x0f)/* GPIO in [3:0] pins - R/O */
#घोषणा   ES_1370_PCLKDIVO(o)	(((o)&0x1fff)<<16)/* घड़ी भागide ratio क्रम DAC2 */
#घोषणा   ES_1370_PCLKDIVM	((0x1fff)<<16)	/* mask क्रम above */
#घोषणा   ES_1370_PCLKDIVI(i)	(((i)>>16)&0x1fff)/* घड़ी भागide ratio क्रम DAC2 */
#घोषणा   ES_1371_GPIO_OUT(o)	(((o)&0x0f)<<16)/* GPIO out [3:0] pins - W/R */
#घोषणा   ES_1371_GPIO_OUTM     (0x0f<<16)	/* mask क्रम above */
#घोषणा   ES_MSFMTSEL		(1<<15)		/* MPEG serial data क्रमmat; 0 = SONY, 1 = I2S */
#घोषणा   ES_1370_M_SBB		(1<<14)		/* घड़ी source क्रम DAC - 0 = घड़ी generator; 1 = MPEG घड़ीs */
#घोषणा   ES_1371_SYNC_RES	(1<<14)		/* Warm AC97 reset */
#घोषणा   ES_1370_WTSRSEL(o)	(((o)&0x03)<<12)/* fixed frequency घड़ी क्रम DAC1 */
#घोषणा   ES_1370_WTSRSELM	(0x03<<12)	/* mask क्रम above */
#घोषणा   ES_1371_ADC_STOP	(1<<13)		/* disable CCB transfer capture inक्रमmation */
#घोषणा   ES_1371_PWR_INTRM	(1<<12)		/* घातer level change पूर्णांकerrupts enable */
#घोषणा   ES_1370_DAC_SYNC	(1<<11)		/* DAC's are synchronous */
#घोषणा   ES_1371_M_CB		(1<<11)		/* capture घड़ी source; 0 = AC'97 ADC; 1 = I2S */
#घोषणा   ES_CCB_INTRM		(1<<10)		/* CCB voice पूर्णांकerrupts enable */
#घोषणा   ES_1370_M_CB		(1<<9)		/* capture घड़ी source; 0 = ADC; 1 = MPEG */
#घोषणा   ES_1370_XCTL0		(1<<8)		/* generap purpose output bit */
#घोषणा   ES_1371_PDLEV(o)	(((o)&0x03)<<8)	/* current घातer करोwn level */
#घोषणा   ES_1371_PDLEVM	(0x03<<8)	/* mask क्रम above */
#घोषणा   ES_BREQ		(1<<7)		/* memory bus request enable */
#घोषणा   ES_DAC1_EN		(1<<6)		/* DAC1 playback channel enable */
#घोषणा   ES_DAC2_EN		(1<<5)		/* DAC2 playback channel enable */
#घोषणा   ES_ADC_EN		(1<<4)		/* ADC capture channel enable */
#घोषणा   ES_UART_EN		(1<<3)		/* UART enable */
#घोषणा   ES_JYSTK_EN		(1<<2)		/* Joystick module enable */
#घोषणा   ES_1370_CDC_EN	(1<<1)		/* Codec पूर्णांकerface enable */
#घोषणा   ES_1371_XTALCKDIS	(1<<1)		/* Xtal घड़ी disable */
#घोषणा   ES_1370_SERR_DISABLE	(1<<0)		/* PCI serr संकेत disable */
#घोषणा   ES_1371_PCICLKDIS     (1<<0)		/* PCI घड़ी disable */
#घोषणा ES_REG_STATUS	0x04	/* R/O: Interrupt/Chip select status रेजिस्टर */
#घोषणा   ES_INTR               (1<<31)		/* Interrupt is pending */
#घोषणा   ES_1371_ST_AC97_RST	(1<<29)		/* CT5880 AC'97 Reset bit */
#घोषणा   ES_1373_REAR_BIT27	(1<<27)		/* rear bits: 000 - front, 010 - mirror, 101 - separate */
#घोषणा   ES_1373_REAR_BIT26	(1<<26)
#घोषणा   ES_1373_REAR_BIT24	(1<<24)
#घोषणा   ES_1373_GPIO_INT_EN(o)(((o)&0x0f)<<20)/* GPIO [3:0] pins - पूर्णांकerrupt enable */
#घोषणा   ES_1373_SPDIF_EN	(1<<18)		/* SPDIF enable */
#घोषणा   ES_1373_SPDIF_TEST	(1<<17)		/* SPDIF test */
#घोषणा   ES_1371_TEST          (1<<16)		/* test ASIC */
#घोषणा   ES_1373_GPIO_INT(i)	(((i)&0x0f)>>12)/* GPIO [3:0] pins - पूर्णांकerrupt pending */
#घोषणा   ES_1370_CSTAT		(1<<10)		/* CODEC is busy or रेजिस्टर ग_लिखो in progress */
#घोषणा   ES_1370_CBUSY         (1<<9)		/* CODEC is busy */
#घोषणा   ES_1370_CWRIP		(1<<8)		/* CODEC रेजिस्टर ग_लिखो in progress */
#घोषणा   ES_1371_SYNC_ERR	(1<<8)		/* CODEC synchronization error occurred */
#घोषणा   ES_1371_VC(i)         (((i)>>6)&0x03)	/* voice code from CCB module */
#घोषणा   ES_1370_VC(i)		(((i)>>5)&0x03)	/* voice code from CCB module */
#घोषणा   ES_1371_MPWR          (1<<5)		/* घातer level पूर्णांकerrupt pending */
#घोषणा   ES_MCCB		(1<<4)		/* CCB पूर्णांकerrupt pending */
#घोषणा   ES_UART		(1<<3)		/* UART पूर्णांकerrupt pending */
#घोषणा   ES_DAC1		(1<<2)		/* DAC1 channel पूर्णांकerrupt pending */
#घोषणा   ES_DAC2		(1<<1)		/* DAC2 channel पूर्णांकerrupt pending */
#घोषणा   ES_ADC		(1<<0)		/* ADC channel पूर्णांकerrupt pending */
#घोषणा ES_REG_UART_DATA 0x08	/* R/W: UART data रेजिस्टर */
#घोषणा ES_REG_UART_STATUS 0x09	/* R/O: UART status रेजिस्टर */
#घोषणा   ES_RXINT		(1<<7)		/* RX पूर्णांकerrupt occurred */
#घोषणा   ES_TXINT		(1<<2)		/* TX पूर्णांकerrupt occurred */
#घोषणा   ES_TXRDY		(1<<1)		/* transmitter पढ़ोy */
#घोषणा   ES_RXRDY		(1<<0)		/* receiver पढ़ोy */
#घोषणा ES_REG_UART_CONTROL 0x09	/* W/O: UART control रेजिस्टर */
#घोषणा   ES_RXINTEN		(1<<7)		/* RX पूर्णांकerrupt enable */
#घोषणा   ES_TXINTENO(o)	(((o)&0x03)<<5)	/* TX पूर्णांकerrupt enable */
#घोषणा   ES_TXINTENM		(0x03<<5)	/* mask क्रम above */
#घोषणा   ES_TXINTENI(i)	(((i)>>5)&0x03)
#घोषणा   ES_CNTRL(o)		(((o)&0x03)<<0)	/* control */
#घोषणा   ES_CNTRLM		(0x03<<0)	/* mask क्रम above */
#घोषणा ES_REG_UART_RES	0x0a	/* R/W: UART reserver रेजिस्टर */
#घोषणा   ES_TEST_MODE		(1<<0)		/* test mode enabled */
#घोषणा ES_REG_MEM_PAGE	0x0c	/* R/W: Memory page रेजिस्टर */
#घोषणा   ES_MEM_PAGEO(o)	(((o)&0x0f)<<0)	/* memory page select - out */
#घोषणा   ES_MEM_PAGEM		(0x0f<<0)	/* mask क्रम above */
#घोषणा   ES_MEM_PAGEI(i)	(((i)>>0)&0x0f) /* memory page select - in */
#घोषणा ES_REG_1370_CODEC 0x10	/* W/O: Codec ग_लिखो रेजिस्टर address */
#घोषणा   ES_1370_CODEC_WRITE(a,d) ((((a)&0xff)<<8)|(((d)&0xff)<<0))
#घोषणा ES_REG_1371_CODEC 0x14	/* W/R: Codec Read/Write रेजिस्टर address */
#घोषणा   ES_1371_CODEC_RDY	   (1<<31)	/* codec पढ़ोy */
#घोषणा   ES_1371_CODEC_WIP	   (1<<30)	/* codec रेजिस्टर access in progress */
#घोषणा   EV_1938_CODEC_MAGIC	   (1<<26)
#घोषणा   ES_1371_CODEC_PIRD	   (1<<23)	/* codec पढ़ो/ग_लिखो select रेजिस्टर */
#घोषणा   ES_1371_CODEC_WRITE(a,d) ((((a)&0x7f)<<16)|(((d)&0xffff)<<0))
#घोषणा   ES_1371_CODEC_READS(a)   ((((a)&0x7f)<<16)|ES_1371_CODEC_PIRD)
#घोषणा   ES_1371_CODEC_READ(i)    (((i)>>0)&0xffff)

#घोषणा ES_REG_1371_SMPRATE 0x10	/* W/R: Codec rate converter पूर्णांकerface रेजिस्टर */
#घोषणा   ES_1371_SRC_RAM_ADDRO(o) (((o)&0x7f)<<25)/* address of the sample rate converter */
#घोषणा   ES_1371_SRC_RAM_ADDRM	   (0x7f<<25)	/* mask क्रम above */
#घोषणा   ES_1371_SRC_RAM_ADDRI(i) (((i)>>25)&0x7f)/* address of the sample rate converter */
#घोषणा   ES_1371_SRC_RAM_WE	   (1<<24)	/* R/W: पढ़ो/ग_लिखो control क्रम sample rate converter */
#घोषणा   ES_1371_SRC_RAM_BUSY     (1<<23)	/* R/O: sample rate memory is busy */
#घोषणा   ES_1371_SRC_DISABLE      (1<<22)	/* sample rate converter disable */
#घोषणा   ES_1371_DIS_P1	   (1<<21)	/* playback channel 1 accumulator update disable */
#घोषणा   ES_1371_DIS_P2	   (1<<20)	/* playback channel 1 accumulator update disable */
#घोषणा   ES_1371_DIS_R1	   (1<<19)	/* capture channel accumulator update disable */
#घोषणा   ES_1371_SRC_RAM_DATAO(o) (((o)&0xffff)<<0)/* current value of the sample rate converter */
#घोषणा   ES_1371_SRC_RAM_DATAM	   (0xffff<<0)	/* mask क्रम above */
#घोषणा   ES_1371_SRC_RAM_DATAI(i) (((i)>>0)&0xffff)/* current value of the sample rate converter */

#घोषणा ES_REG_1371_LEGACY 0x18	/* W/R: Legacy control/status रेजिस्टर */
#घोषणा   ES_1371_JFAST		(1<<31)		/* fast joystick timing */
#घोषणा   ES_1371_HIB		(1<<30)		/* host पूर्णांकerrupt blocking enable */
#घोषणा   ES_1371_VSB		(1<<29)		/* SB; 0 = addr 0x220xH, 1 = 0x22FxH */
#घोषणा   ES_1371_VMPUO(o)	(((o)&0x03)<<27)/* base रेजिस्टर address; 0 = 0x320xH; 1 = 0x330xH; 2 = 0x340xH; 3 = 0x350xH */
#घोषणा   ES_1371_VMPUM		(0x03<<27)	/* mask क्रम above */
#घोषणा   ES_1371_VMPUI(i)	(((i)>>27)&0x03)/* base रेजिस्टर address */
#घोषणा   ES_1371_VCDCO(o)	(((o)&0x03)<<25)/* CODEC; 0 = 0x530xH; 1 = undefined; 2 = 0xe80xH; 3 = 0xF40xH */
#घोषणा   ES_1371_VCDCM		(0x03<<25)	/* mask क्रम above */
#घोषणा   ES_1371_VCDCI(i)	(((i)>>25)&0x03)/* CODEC address */
#घोषणा   ES_1371_FIRQ		(1<<24)		/* क्रमce an पूर्णांकerrupt */
#घोषणा   ES_1371_SDMACAP	(1<<23)		/* enable event capture क्रम slave DMA controller */
#घोषणा   ES_1371_SPICAP	(1<<22)		/* enable event capture क्रम slave IRQ controller */
#घोषणा   ES_1371_MDMACAP	(1<<21)		/* enable event capture क्रम master DMA controller */
#घोषणा   ES_1371_MPICAP	(1<<20)		/* enable event capture क्रम master IRQ controller */
#घोषणा   ES_1371_ADCAP		(1<<19)		/* enable event capture क्रम ADLIB रेजिस्टर; 0x388xH */
#घोषणा   ES_1371_SVCAP		(1<<18)		/* enable event capture क्रम SB रेजिस्टरs */
#घोषणा   ES_1371_CDCCAP	(1<<17)		/* enable event capture क्रम CODEC रेजिस्टरs */
#घोषणा   ES_1371_BACAP		(1<<16)		/* enable event capture क्रम SoundScape base address */
#घोषणा   ES_1371_EXI(i)	(((i)>>8)&0x07)	/* event number */
#घोषणा   ES_1371_AI(i)		(((i)>>3)&0x1f)	/* event signअगरicant I/O address */
#घोषणा   ES_1371_WR		(1<<2)	/* event capture; 0 = पढ़ो; 1 = ग_लिखो */
#घोषणा   ES_1371_LEGINT	(1<<0)	/* पूर्णांकerrupt क्रम legacy events; 0 = पूर्णांकerrupt did occur */

#घोषणा ES_REG_CHANNEL_STATUS 0x1c /* R/W: first 32-bits from S/PDIF channel status block, es1373 */

#घोषणा ES_REG_SERIAL	0x20	/* R/W: Serial पूर्णांकerface control रेजिस्टर */
#घोषणा   ES_1371_DAC_TEST	(1<<22)		/* DAC test mode enable */
#घोषणा   ES_P2_END_INCO(o)	(((o)&0x07)<<19)/* binary offset value to increment / loop end */
#घोषणा   ES_P2_END_INCM	(0x07<<19)	/* mask क्रम above */
#घोषणा   ES_P2_END_INCI(i)	(((i)>>16)&0x07)/* binary offset value to increment / loop end */
#घोषणा   ES_P2_ST_INCO(o)	(((o)&0x07)<<16)/* binary offset value to increment / start */
#घोषणा   ES_P2_ST_INCM		(0x07<<16)	/* mask क्रम above */
#घोषणा   ES_P2_ST_INCI(i)	(((i)<<16)&0x07)/* binary offset value to increment / start */
#घोषणा   ES_R1_LOOP_SEL	(1<<15)		/* ADC; 0 - loop mode; 1 = stop mode */
#घोषणा   ES_P2_LOOP_SEL	(1<<14)		/* DAC2; 0 - loop mode; 1 = stop mode */
#घोषणा   ES_P1_LOOP_SEL	(1<<13)		/* DAC1; 0 - loop mode; 1 = stop mode */
#घोषणा   ES_P2_PAUSE		(1<<12)		/* DAC2; 0 - play mode; 1 = छोड़ो mode */
#घोषणा   ES_P1_PAUSE		(1<<11)		/* DAC1; 0 - play mode; 1 = छोड़ो mode */
#घोषणा   ES_R1_INT_EN		(1<<10)		/* ADC पूर्णांकerrupt enable */
#घोषणा   ES_P2_INT_EN		(1<<9)		/* DAC2 पूर्णांकerrupt enable */
#घोषणा   ES_P1_INT_EN		(1<<8)		/* DAC1 पूर्णांकerrupt enable */
#घोषणा   ES_P1_SCT_RLD		(1<<7)		/* क्रमce sample counter reload क्रम DAC1 */
#घोषणा   ES_P2_DAC_SEN		(1<<6)		/* when stop mode: 0 - DAC2 play back zeros; 1 = DAC2 play back last sample */
#घोषणा   ES_R1_MODEO(o)	(((o)&0x03)<<4)	/* ADC mode; 0 = 8-bit mono; 1 = 8-bit stereo; 2 = 16-bit mono; 3 = 16-bit stereo */
#घोषणा   ES_R1_MODEM		(0x03<<4)	/* mask क्रम above */
#घोषणा   ES_R1_MODEI(i)	(((i)>>4)&0x03)
#घोषणा   ES_P2_MODEO(o)	(((o)&0x03)<<2)	/* DAC2 mode; -- '' -- */
#घोषणा   ES_P2_MODEM		(0x03<<2)	/* mask क्रम above */
#घोषणा   ES_P2_MODEI(i)	(((i)>>2)&0x03)
#घोषणा   ES_P1_MODEO(o)	(((o)&0x03)<<0)	/* DAC1 mode; -- '' -- */
#घोषणा   ES_P1_MODEM		(0x03<<0)	/* mask क्रम above */
#घोषणा   ES_P1_MODEI(i)	(((i)>>0)&0x03)

#घोषणा ES_REG_DAC1_COUNT 0x24	/* R/W: DAC1 sample count रेजिस्टर */
#घोषणा ES_REG_DAC2_COUNT 0x28	/* R/W: DAC2 sample count रेजिस्टर */
#घोषणा ES_REG_ADC_COUNT  0x2c	/* R/W: ADC sample count रेजिस्टर */
#घोषणा   ES_REG_CURR_COUNT(i)  (((i)>>16)&0xffff)
#घोषणा   ES_REG_COUNTO(o)	(((o)&0xffff)<<0)
#घोषणा   ES_REG_COUNTM		(0xffff<<0)
#घोषणा   ES_REG_COUNTI(i)	(((i)>>0)&0xffff)

#घोषणा ES_REG_DAC1_FRAME 0x30	/* R/W: PAGE 0x0c; DAC1 frame address */
#घोषणा ES_REG_DAC1_SIZE  0x34	/* R/W: PAGE 0x0c; DAC1 frame size */
#घोषणा ES_REG_DAC2_FRAME 0x38	/* R/W: PAGE 0x0c; DAC2 frame address */
#घोषणा ES_REG_DAC2_SIZE  0x3c	/* R/W: PAGE 0x0c; DAC2 frame size */
#घोषणा ES_REG_ADC_FRAME  0x30	/* R/W: PAGE 0x0d; ADC frame address */
#घोषणा ES_REG_ADC_SIZE	  0x34	/* R/W: PAGE 0x0d; ADC frame size */
#घोषणा   ES_REG_FCURR_COUNTO(o) (((o)&0xffff)<<16)
#घोषणा   ES_REG_FCURR_COUNTM    (0xffff<<16)
#घोषणा   ES_REG_FCURR_COUNTI(i) (((i)>>14)&0x3fffc)
#घोषणा   ES_REG_FSIZEO(o)	 (((o)&0xffff)<<0)
#घोषणा   ES_REG_FSIZEM		 (0xffff<<0)
#घोषणा   ES_REG_FSIZEI(i)	 (((i)>>0)&0xffff)
#घोषणा ES_REG_PHANTOM_FRAME 0x38 /* R/W: PAGE 0x0d: phantom frame address */
#घोषणा ES_REG_PHANTOM_COUNT 0x3c /* R/W: PAGE 0x0d: phantom frame count */

#घोषणा ES_REG_UART_FIFO  0x30	/* R/W: PAGE 0x0e; UART FIFO रेजिस्टर */
#घोषणा   ES_REG_UF_VALID	 (1<<8)
#घोषणा   ES_REG_UF_BYTEO(o)	 (((o)&0xff)<<0)
#घोषणा   ES_REG_UF_BYTEM	 (0xff<<0)
#घोषणा   ES_REG_UF_BYTEI(i)	 (((i)>>0)&0xff)


/*
 *  Pages
 */

#घोषणा ES_PAGE_DAC	0x0c
#घोषणा ES_PAGE_ADC	0x0d
#घोषणा ES_PAGE_UART	0x0e
#घोषणा ES_PAGE_UART1	0x0f

/*
 *  Sample rate converter addresses
 */

#घोषणा ES_SMPREG_DAC1		0x70
#घोषणा ES_SMPREG_DAC2		0x74
#घोषणा ES_SMPREG_ADC		0x78
#घोषणा ES_SMPREG_VOL_ADC	0x6c
#घोषणा ES_SMPREG_VOL_DAC1	0x7c
#घोषणा ES_SMPREG_VOL_DAC2	0x7e
#घोषणा ES_SMPREG_TRUNC_N	0x00
#घोषणा ES_SMPREG_INT_REGS	0x01
#घोषणा ES_SMPREG_ACCUM_FRAC	0x02
#घोषणा ES_SMPREG_VFREQ_FRAC	0x03

/*
 *  Some contants
 */

#घोषणा ES_1370_SRCLOCK	   1411200
#घोषणा ES_1370_SRTODIV(x) (ES_1370_SRCLOCK/(x)-2)

/*
 *  Open modes
 */

#घोषणा ES_MODE_PLAY1	0x0001
#घोषणा ES_MODE_PLAY2	0x0002
#घोषणा ES_MODE_CAPTURE	0x0004

#घोषणा ES_MODE_OUTPUT	0x0001	/* क्रम MIDI */
#घोषणा ES_MODE_INPUT	0x0002	/* क्रम MIDI */

/*

 */

काष्ठा ensoniq अणु
	spinlock_t reg_lock;
	काष्ठा mutex src_mutex;

	पूर्णांक irq;

	अचिन्हित दीर्घ playback1size;
	अचिन्हित दीर्घ playback2size;
	अचिन्हित दीर्घ capture3size;

	अचिन्हित दीर्घ port;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक uarपंचांग;	/* UART mode */

	अचिन्हित पूर्णांक ctrl;	/* control रेजिस्टर */
	अचिन्हित पूर्णांक sctrl;	/* serial control रेजिस्टर */
	अचिन्हित पूर्णांक cssr;	/* control status रेजिस्टर */
	अचिन्हित पूर्णांक uartc;	/* uart control रेजिस्टर */
	अचिन्हित पूर्णांक rev;	/* chip revision */

	जोड़ अणु
#अगर_घोषित CHIP1371
		काष्ठा अणु
			काष्ठा snd_ac97 *ac97;
		पूर्ण es1371;
#अन्यथा
		काष्ठा अणु
			पूर्णांक pclkभाग_lock;
			काष्ठा snd_ak4531 *ak4531;
		पूर्ण es1370;
#पूर्ण_अगर
	पूर्ण u;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm1;	/* DAC1/ADC PCM */
	काष्ठा snd_pcm *pcm2;	/* DAC2 PCM */
	काष्ठा snd_pcm_substream *playback1_substream;
	काष्ठा snd_pcm_substream *playback2_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	अचिन्हित पूर्णांक p1_dma_size;
	अचिन्हित पूर्णांक p2_dma_size;
	अचिन्हित पूर्णांक c_dma_size;
	अचिन्हित पूर्णांक p1_period_size;
	अचिन्हित पूर्णांक p2_period_size;
	अचिन्हित पूर्णांक c_period_size;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *midi_input;
	काष्ठा snd_rawmidi_substream *midi_output;

	अचिन्हित पूर्णांक spdअगर;
	अचिन्हित पूर्णांक spdअगर_शेष;
	अचिन्हित पूर्णांक spdअगर_stream;

#अगर_घोषित CHIP1370
	काष्ठा snd_dma_buffer dma_bug;
#पूर्ण_अगर

#अगर_घोषित SUPPORT_JOYSTICK
	काष्ठा gameport *gameport;
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t snd_audiopci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

अटल स्थिर काष्ठा pci_device_id snd_audiopci_ids[] = अणु
#अगर_घोषित CHIP1370
	अणु PCI_VDEVICE(ENSONIQ, 0x5000), 0, पूर्ण,	/* ES1370 */
#पूर्ण_अगर
#अगर_घोषित CHIP1371
	अणु PCI_VDEVICE(ENSONIQ, 0x1371), 0, पूर्ण,	/* ES1371 */
	अणु PCI_VDEVICE(ENSONIQ, 0x5880), 0, पूर्ण,	/* ES1373 - CT5880 */
	अणु PCI_VDEVICE(ECTIVA, 0x8938), 0, पूर्ण,	/* Ectiva EV1938 */
#पूर्ण_अगर
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_audiopci_ids);

/*
 *  स्थिरants
 */

#घोषणा POLL_COUNT	0xa000

#अगर_घोषित CHIP1370
अटल स्थिर अचिन्हित पूर्णांक snd_es1370_fixed_rates[] =
	अणु5512, 11025, 22050, 44100पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list snd_es1370_hw_स्थिरraपूर्णांकs_rates = अणु
	.count = 4, 
	.list = snd_es1370_fixed_rates,
	.mask = 0,
पूर्ण;
अटल स्थिर काष्ठा snd_ratnum es1370_घड़ी = अणु
	.num = ES_1370_SRCLOCK,
	.den_min = 29, 
	.den_max = 353,
	.den_step = 1,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums snd_es1370_hw_स्थिरraपूर्णांकs_घड़ी = अणु
	.nrats = 1,
	.rats = &es1370_घड़ी,
पूर्ण;
#अन्यथा
अटल स्थिर काष्ठा snd_ratden es1371_dac_घड़ी = अणु
	.num_min = 3000 * (1 << 15),
	.num_max = 48000 * (1 << 15),
	.num_step = 3000,
	.den = 1 << 15,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratdens snd_es1371_hw_स्थिरraपूर्णांकs_dac_घड़ी = अणु
	.nrats = 1,
	.rats = &es1371_dac_घड़ी,
पूर्ण;
अटल स्थिर काष्ठा snd_ratnum es1371_adc_घड़ी = अणु
	.num = 48000 << 15,
	.den_min = 32768, 
	.den_max = 393216,
	.den_step = 1,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_ratnums snd_es1371_hw_स्थिरraपूर्णांकs_adc_घड़ी = अणु
	.nrats = 1,
	.rats = &es1371_adc_घड़ी,
पूर्ण;
#पूर्ण_अगर
अटल स्थिर अचिन्हित पूर्णांक snd_ensoniq_sample_shअगरt[] =
	अणु0, 1, 1, 2पूर्ण;

/*
 *  common I/O routines
 */

#अगर_घोषित CHIP1371

अटल अचिन्हित पूर्णांक snd_es1371_रुको_src_पढ़ोy(काष्ठा ensoniq * ensoniq)
अणु
	अचिन्हित पूर्णांक t, r = 0;

	क्रम (t = 0; t < POLL_COUNT; t++) अणु
		r = inl(ES_REG(ensoniq, 1371_SMPRATE));
		अगर ((r & ES_1371_SRC_RAM_BUSY) == 0)
			वापस r;
		cond_resched();
	पूर्ण
	dev_err(ensoniq->card->dev, "wait src ready timeout 0x%lx [0x%x]\n",
		   ES_REG(ensoniq, 1371_SMPRATE), r);
	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक snd_es1371_src_पढ़ो(काष्ठा ensoniq * ensoniq, अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक temp, i, orig, r;

	/* रुको क्रम पढ़ोy */
	temp = orig = snd_es1371_रुको_src_पढ़ोy(ensoniq);

	/* expose the SRC state bits */
	r = temp & (ES_1371_SRC_DISABLE | ES_1371_DIS_P1 |
		    ES_1371_DIS_P2 | ES_1371_DIS_R1);
	r |= ES_1371_SRC_RAM_ADDRO(reg) | 0x10000;
	outl(r, ES_REG(ensoniq, 1371_SMPRATE));

	/* now, रुको क्रम busy and the correct समय to पढ़ो */
	temp = snd_es1371_रुको_src_पढ़ोy(ensoniq);
	
	अगर ((temp & 0x00870000) != 0x00010000) अणु
		/* रुको क्रम the right state */
		क्रम (i = 0; i < POLL_COUNT; i++) अणु
			temp = inl(ES_REG(ensoniq, 1371_SMPRATE));
			अगर ((temp & 0x00870000) == 0x00010000)
				अवरोध;
		पूर्ण
	पूर्ण

	/* hide the state bits */	
	r = orig & (ES_1371_SRC_DISABLE | ES_1371_DIS_P1 |
		   ES_1371_DIS_P2 | ES_1371_DIS_R1);
	r |= ES_1371_SRC_RAM_ADDRO(reg);
	outl(r, ES_REG(ensoniq, 1371_SMPRATE));
	
	वापस temp;
पूर्ण

अटल व्योम snd_es1371_src_ग_लिखो(काष्ठा ensoniq * ensoniq,
				 अचिन्हित लघु reg, अचिन्हित लघु data)
अणु
	अचिन्हित पूर्णांक r;

	r = snd_es1371_रुको_src_पढ़ोy(ensoniq) &
	    (ES_1371_SRC_DISABLE | ES_1371_DIS_P1 |
	     ES_1371_DIS_P2 | ES_1371_DIS_R1);
	r |= ES_1371_SRC_RAM_ADDRO(reg) | ES_1371_SRC_RAM_DATAO(data);
	outl(r | ES_1371_SRC_RAM_WE, ES_REG(ensoniq, 1371_SMPRATE));
पूर्ण

#पूर्ण_अगर /* CHIP1371 */

#अगर_घोषित CHIP1370

अटल व्योम snd_es1370_codec_ग_लिखो(काष्ठा snd_ak4531 *ak4531,
				   अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा ensoniq *ensoniq = ak4531->निजी_data;
	अचिन्हित दीर्घ end_समय = jअगरfies + HZ / 10;

#अगर 0
	dev_dbg(ensoniq->card->dev,
	       "CODEC WRITE: reg = 0x%x, val = 0x%x (0x%x), creg = 0x%x\n",
	       reg, val, ES_1370_CODEC_WRITE(reg, val), ES_REG(ensoniq, 1370_CODEC));
#पूर्ण_अगर
	करो अणु
		अगर (!(inl(ES_REG(ensoniq, STATUS)) & ES_1370_CSTAT)) अणु
			outw(ES_1370_CODEC_WRITE(reg, val), ES_REG(ensoniq, 1370_CODEC));
			वापस;
		पूर्ण
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण जबतक (समय_after(end_समय, jअगरfies));
	dev_err(ensoniq->card->dev, "codec write timeout, status = 0x%x\n",
		   inl(ES_REG(ensoniq, STATUS)));
पूर्ण

#पूर्ण_अगर /* CHIP1370 */

#अगर_घोषित CHIP1371

अटल अंतरभूत bool is_ev1938(काष्ठा ensoniq *ensoniq)
अणु
	वापस ensoniq->pci->device == 0x8938;
पूर्ण

अटल व्योम snd_es1371_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				   अचिन्हित लघु reg, अचिन्हित लघु val)
अणु
	काष्ठा ensoniq *ensoniq = ac97->निजी_data;
	अचिन्हित पूर्णांक t, x, flag;

	flag = is_ev1938(ensoniq) ? EV_1938_CODEC_MAGIC : 0;
	mutex_lock(&ensoniq->src_mutex);
	क्रम (t = 0; t < POLL_COUNT; t++) अणु
		अगर (!(inl(ES_REG(ensoniq, 1371_CODEC)) & ES_1371_CODEC_WIP)) अणु
			/* save the current state क्रम latter */
			x = snd_es1371_रुको_src_पढ़ोy(ensoniq);
			outl((x & (ES_1371_SRC_DISABLE | ES_1371_DIS_P1 |
			           ES_1371_DIS_P2 | ES_1371_DIS_R1)) | 0x00010000,
			     ES_REG(ensoniq, 1371_SMPRATE));
			/* रुको क्रम not busy (state 0) first to aव्योम
			   transition states */
			क्रम (t = 0; t < POLL_COUNT; t++) अणु
				अगर ((inl(ES_REG(ensoniq, 1371_SMPRATE)) & 0x00870000) ==
				    0x00000000)
					अवरोध;
			पूर्ण
			/* रुको क्रम a SAFE समय to ग_लिखो addr/data and then करो it, dammit */
			क्रम (t = 0; t < POLL_COUNT; t++) अणु
				अगर ((inl(ES_REG(ensoniq, 1371_SMPRATE)) & 0x00870000) ==
				    0x00010000)
					अवरोध;
			पूर्ण
			outl(ES_1371_CODEC_WRITE(reg, val) | flag,
			     ES_REG(ensoniq, 1371_CODEC));
			/* restore SRC reg */
			snd_es1371_रुको_src_पढ़ोy(ensoniq);
			outl(x, ES_REG(ensoniq, 1371_SMPRATE));
			mutex_unlock(&ensoniq->src_mutex);
			वापस;
		पूर्ण
	पूर्ण
	mutex_unlock(&ensoniq->src_mutex);
	dev_err(ensoniq->card->dev, "codec write timeout at 0x%lx [0x%x]\n",
		   ES_REG(ensoniq, 1371_CODEC), inl(ES_REG(ensoniq, 1371_CODEC)));
पूर्ण

अटल अचिन्हित लघु snd_es1371_codec_पढ़ो(काष्ठा snd_ac97 *ac97,
					    अचिन्हित लघु reg)
अणु
	काष्ठा ensoniq *ensoniq = ac97->निजी_data;
	अचिन्हित पूर्णांक t, x, flag, fail = 0;

	flag = is_ev1938(ensoniq) ? EV_1938_CODEC_MAGIC : 0;
      __again:
	mutex_lock(&ensoniq->src_mutex);
	क्रम (t = 0; t < POLL_COUNT; t++) अणु
		अगर (!(inl(ES_REG(ensoniq, 1371_CODEC)) & ES_1371_CODEC_WIP)) अणु
			/* save the current state क्रम latter */
			x = snd_es1371_रुको_src_पढ़ोy(ensoniq);
			outl((x & (ES_1371_SRC_DISABLE | ES_1371_DIS_P1 |
			           ES_1371_DIS_P2 | ES_1371_DIS_R1)) | 0x00010000,
			     ES_REG(ensoniq, 1371_SMPRATE));
			/* रुको क्रम not busy (state 0) first to aव्योम
			   transition states */
			क्रम (t = 0; t < POLL_COUNT; t++) अणु
				अगर ((inl(ES_REG(ensoniq, 1371_SMPRATE)) & 0x00870000) ==
				    0x00000000)
					अवरोध;
			पूर्ण
			/* रुको क्रम a SAFE समय to ग_लिखो addr/data and then करो it, dammit */
			क्रम (t = 0; t < POLL_COUNT; t++) अणु
				अगर ((inl(ES_REG(ensoniq, 1371_SMPRATE)) & 0x00870000) ==
				    0x00010000)
					अवरोध;
			पूर्ण
			outl(ES_1371_CODEC_READS(reg) | flag,
			     ES_REG(ensoniq, 1371_CODEC));
			/* restore SRC reg */
			snd_es1371_रुको_src_पढ़ोy(ensoniq);
			outl(x, ES_REG(ensoniq, 1371_SMPRATE));
			/* रुको क्रम WIP again */
			क्रम (t = 0; t < POLL_COUNT; t++) अणु
				अगर (!(inl(ES_REG(ensoniq, 1371_CODEC)) & ES_1371_CODEC_WIP))
					अवरोध;		
			पूर्ण
			/* now रुको क्रम the stinkin' data (RDY) */
			क्रम (t = 0; t < POLL_COUNT; t++) अणु
				अगर ((x = inl(ES_REG(ensoniq, 1371_CODEC))) & ES_1371_CODEC_RDY) अणु
					अगर (is_ev1938(ensoniq)) अणु
						क्रम (t = 0; t < 100; t++)
							inl(ES_REG(ensoniq, CONTROL));
						x = inl(ES_REG(ensoniq, 1371_CODEC));
					पूर्ण
					mutex_unlock(&ensoniq->src_mutex);
					वापस ES_1371_CODEC_READ(x);
				पूर्ण
			पूर्ण
			mutex_unlock(&ensoniq->src_mutex);
			अगर (++fail > 10) अणु
				dev_err(ensoniq->card->dev,
					"codec read timeout (final) at 0x%lx, reg = 0x%x [0x%x]\n",
					   ES_REG(ensoniq, 1371_CODEC), reg,
					   inl(ES_REG(ensoniq, 1371_CODEC)));
				वापस 0;
			पूर्ण
			जाओ __again;
		पूर्ण
	पूर्ण
	mutex_unlock(&ensoniq->src_mutex);
	dev_err(ensoniq->card->dev, "codec read timeout at 0x%lx [0x%x]\n",
		   ES_REG(ensoniq, 1371_CODEC), inl(ES_REG(ensoniq, 1371_CODEC)));
	वापस 0;
पूर्ण

अटल व्योम snd_es1371_codec_रुको(काष्ठा snd_ac97 *ac97)
अणु
	msleep(750);
	snd_es1371_codec_पढ़ो(ac97, AC97_RESET);
	snd_es1371_codec_पढ़ो(ac97, AC97_VENDOR_ID1);
	snd_es1371_codec_पढ़ो(ac97, AC97_VENDOR_ID2);
	msleep(50);
पूर्ण

अटल व्योम snd_es1371_adc_rate(काष्ठा ensoniq * ensoniq, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक n, truncm, freq;

	mutex_lock(&ensoniq->src_mutex);
	n = rate / 3000;
	अगर ((1 << n) & ((1 << 15) | (1 << 13) | (1 << 11) | (1 << 9)))
		n--;
	truncm = (21 * n - 1) | 1;
	freq = ((48000UL << 15) / rate) * n;
	अगर (rate >= 24000) अणु
		अगर (truncm > 239)
			truncm = 239;
		snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_ADC + ES_SMPREG_TRUNC_N,
				(((239 - truncm) >> 1) << 9) | (n << 4));
	पूर्ण अन्यथा अणु
		अगर (truncm > 119)
			truncm = 119;
		snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_ADC + ES_SMPREG_TRUNC_N,
				0x8000 | (((119 - truncm) >> 1) << 9) | (n << 4));
	पूर्ण
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_ADC + ES_SMPREG_INT_REGS,
			     (snd_es1371_src_पढ़ो(ensoniq, ES_SMPREG_ADC +
						  ES_SMPREG_INT_REGS) & 0x00ff) |
			     ((freq >> 5) & 0xfc00));
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_ADC + ES_SMPREG_VFREQ_FRAC, freq & 0x7fff);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_ADC, n << 8);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_ADC + 1, n << 8);
	mutex_unlock(&ensoniq->src_mutex);
पूर्ण

अटल व्योम snd_es1371_dac1_rate(काष्ठा ensoniq * ensoniq, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक freq, r;

	mutex_lock(&ensoniq->src_mutex);
	freq = DIV_ROUND_CLOSEST(rate << 15, 3000);
	r = (snd_es1371_रुको_src_पढ़ोy(ensoniq) & (ES_1371_SRC_DISABLE |
						   ES_1371_DIS_P2 | ES_1371_DIS_R1)) |
		ES_1371_DIS_P1;
	outl(r, ES_REG(ensoniq, 1371_SMPRATE));
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC1 + ES_SMPREG_INT_REGS,
			     (snd_es1371_src_पढ़ो(ensoniq, ES_SMPREG_DAC1 +
						  ES_SMPREG_INT_REGS) & 0x00ff) |
			     ((freq >> 5) & 0xfc00));
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC1 + ES_SMPREG_VFREQ_FRAC, freq & 0x7fff);
	r = (snd_es1371_रुको_src_पढ़ोy(ensoniq) & (ES_1371_SRC_DISABLE |
						   ES_1371_DIS_P2 | ES_1371_DIS_R1));
	outl(r, ES_REG(ensoniq, 1371_SMPRATE));
	mutex_unlock(&ensoniq->src_mutex);
पूर्ण

अटल व्योम snd_es1371_dac2_rate(काष्ठा ensoniq * ensoniq, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित पूर्णांक freq, r;

	mutex_lock(&ensoniq->src_mutex);
	freq = DIV_ROUND_CLOSEST(rate << 15, 3000);
	r = (snd_es1371_रुको_src_पढ़ोy(ensoniq) & (ES_1371_SRC_DISABLE |
						   ES_1371_DIS_P1 | ES_1371_DIS_R1)) |
		ES_1371_DIS_P2;
	outl(r, ES_REG(ensoniq, 1371_SMPRATE));
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC2 + ES_SMPREG_INT_REGS,
			     (snd_es1371_src_पढ़ो(ensoniq, ES_SMPREG_DAC2 +
						  ES_SMPREG_INT_REGS) & 0x00ff) |
			     ((freq >> 5) & 0xfc00));
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC2 + ES_SMPREG_VFREQ_FRAC,
			     freq & 0x7fff);
	r = (snd_es1371_रुको_src_पढ़ोy(ensoniq) & (ES_1371_SRC_DISABLE |
						   ES_1371_DIS_P1 | ES_1371_DIS_R1));
	outl(r, ES_REG(ensoniq, 1371_SMPRATE));
	mutex_unlock(&ensoniq->src_mutex);
पूर्ण

#पूर्ण_अगर /* CHIP1371 */

अटल पूर्णांक snd_ensoniq_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	अणु
		अचिन्हित पूर्णांक what = 0;
		काष्ठा snd_pcm_substream *s;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == ensoniq->playback1_substream) अणु
				what |= ES_P1_PAUSE;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा अगर (s == ensoniq->playback2_substream) अणु
				what |= ES_P2_PAUSE;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा अगर (s == ensoniq->capture_substream)
				वापस -EINVAL;
		पूर्ण
		spin_lock(&ensoniq->reg_lock);
		अगर (cmd == SNDRV_PCM_TRIGGER_PAUSE_PUSH)
			ensoniq->sctrl |= what;
		अन्यथा
			ensoniq->sctrl &= ~what;
		outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
		spin_unlock(&ensoniq->reg_lock);
		अवरोध;
	पूर्ण
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_STOP:
	अणु
		अचिन्हित पूर्णांक what = 0;
		काष्ठा snd_pcm_substream *s;
		snd_pcm_group_क्रम_each_entry(s, substream) अणु
			अगर (s == ensoniq->playback1_substream) अणु
				what |= ES_DAC1_EN;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा अगर (s == ensoniq->playback2_substream) अणु
				what |= ES_DAC2_EN;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण अन्यथा अगर (s == ensoniq->capture_substream) अणु
				what |= ES_ADC_EN;
				snd_pcm_trigger_करोne(s, substream);
			पूर्ण
		पूर्ण
		spin_lock(&ensoniq->reg_lock);
		अगर (cmd == SNDRV_PCM_TRIGGER_START)
			ensoniq->ctrl |= what;
		अन्यथा
			ensoniq->ctrl &= ~what;
		outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
		spin_unlock(&ensoniq->reg_lock);
		अवरोध;
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_ensoniq_playback1_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक mode = 0;

	ensoniq->p1_dma_size = snd_pcm_lib_buffer_bytes(substream);
	ensoniq->p1_period_size = snd_pcm_lib_period_bytes(substream);
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		mode |= 0x02;
	अगर (runसमय->channels > 1)
		mode |= 0x01;
	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->ctrl &= ~ES_DAC1_EN;
#अगर_घोषित CHIP1371
	/* 48k करोesn't need SRC (it अवरोधs AC3-passthru) */
	अगर (runसमय->rate == 48000)
		ensoniq->ctrl |= ES_1373_BYPASS_P1;
	अन्यथा
		ensoniq->ctrl &= ~ES_1373_BYPASS_P1;
#पूर्ण_अगर
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ES_MEM_PAGEO(ES_PAGE_DAC), ES_REG(ensoniq, MEM_PAGE));
	outl(runसमय->dma_addr, ES_REG(ensoniq, DAC1_FRAME));
	outl((ensoniq->p1_dma_size >> 2) - 1, ES_REG(ensoniq, DAC1_SIZE));
	ensoniq->sctrl &= ~(ES_P1_LOOP_SEL | ES_P1_PAUSE | ES_P1_SCT_RLD | ES_P1_MODEM);
	ensoniq->sctrl |= ES_P1_INT_EN | ES_P1_MODEO(mode);
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl((ensoniq->p1_period_size >> snd_ensoniq_sample_shअगरt[mode]) - 1,
	     ES_REG(ensoniq, DAC1_COUNT));
#अगर_घोषित CHIP1370
	ensoniq->ctrl &= ~ES_1370_WTSRSELM;
	चयन (runसमय->rate) अणु
	हाल 5512: ensoniq->ctrl |= ES_1370_WTSRSEL(0); अवरोध;
	हाल 11025: ensoniq->ctrl |= ES_1370_WTSRSEL(1); अवरोध;
	हाल 22050: ensoniq->ctrl |= ES_1370_WTSRSEL(2); अवरोध;
	हाल 44100: ensoniq->ctrl |= ES_1370_WTSRSEL(3); अवरोध;
	शेष: snd_BUG();
	पूर्ण
#पूर्ण_अगर
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
#अगर_अघोषित CHIP1370
	snd_es1371_dac1_rate(ensoniq, runसमय->rate);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_playback2_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक mode = 0;

	ensoniq->p2_dma_size = snd_pcm_lib_buffer_bytes(substream);
	ensoniq->p2_period_size = snd_pcm_lib_period_bytes(substream);
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		mode |= 0x02;
	अगर (runसमय->channels > 1)
		mode |= 0x01;
	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->ctrl &= ~ES_DAC2_EN;
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ES_MEM_PAGEO(ES_PAGE_DAC), ES_REG(ensoniq, MEM_PAGE));
	outl(runसमय->dma_addr, ES_REG(ensoniq, DAC2_FRAME));
	outl((ensoniq->p2_dma_size >> 2) - 1, ES_REG(ensoniq, DAC2_SIZE));
	ensoniq->sctrl &= ~(ES_P2_LOOP_SEL | ES_P2_PAUSE | ES_P2_DAC_SEN |
			    ES_P2_END_INCM | ES_P2_ST_INCM | ES_P2_MODEM);
	ensoniq->sctrl |= ES_P2_INT_EN | ES_P2_MODEO(mode) |
			  ES_P2_END_INCO(mode & 2 ? 2 : 1) | ES_P2_ST_INCO(0);
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl((ensoniq->p2_period_size >> snd_ensoniq_sample_shअगरt[mode]) - 1,
	     ES_REG(ensoniq, DAC2_COUNT));
#अगर_घोषित CHIP1370
	अगर (!(ensoniq->u.es1370.pclkभाग_lock & ES_MODE_CAPTURE)) अणु
		ensoniq->ctrl &= ~ES_1370_PCLKDIVM;
		ensoniq->ctrl |= ES_1370_PCLKDIVO(ES_1370_SRTODIV(runसमय->rate));
		ensoniq->u.es1370.pclkभाग_lock |= ES_MODE_PLAY2;
	पूर्ण
#पूर्ण_अगर
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
#अगर_अघोषित CHIP1370
	snd_es1371_dac2_rate(ensoniq, runसमय->rate);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक mode = 0;

	ensoniq->c_dma_size = snd_pcm_lib_buffer_bytes(substream);
	ensoniq->c_period_size = snd_pcm_lib_period_bytes(substream);
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		mode |= 0x02;
	अगर (runसमय->channels > 1)
		mode |= 0x01;
	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->ctrl &= ~ES_ADC_EN;
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ES_MEM_PAGEO(ES_PAGE_ADC), ES_REG(ensoniq, MEM_PAGE));
	outl(runसमय->dma_addr, ES_REG(ensoniq, ADC_FRAME));
	outl((ensoniq->c_dma_size >> 2) - 1, ES_REG(ensoniq, ADC_SIZE));
	ensoniq->sctrl &= ~(ES_R1_LOOP_SEL | ES_R1_MODEM);
	ensoniq->sctrl |= ES_R1_INT_EN | ES_R1_MODEO(mode);
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl((ensoniq->c_period_size >> snd_ensoniq_sample_shअगरt[mode]) - 1,
	     ES_REG(ensoniq, ADC_COUNT));
#अगर_घोषित CHIP1370
	अगर (!(ensoniq->u.es1370.pclkभाग_lock & ES_MODE_PLAY2)) अणु
		ensoniq->ctrl &= ~ES_1370_PCLKDIVM;
		ensoniq->ctrl |= ES_1370_PCLKDIVO(ES_1370_SRTODIV(runसमय->rate));
		ensoniq->u.es1370.pclkभाग_lock |= ES_MODE_CAPTURE;
	पूर्ण
#पूर्ण_अगर
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
#अगर_अघोषित CHIP1370
	snd_es1371_adc_rate(ensoniq, runसमय->rate);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t snd_ensoniq_playback1_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	spin_lock(&ensoniq->reg_lock);
	अगर (inl(ES_REG(ensoniq, CONTROL)) & ES_DAC1_EN) अणु
		outl(ES_MEM_PAGEO(ES_PAGE_DAC), ES_REG(ensoniq, MEM_PAGE));
		ptr = ES_REG_FCURR_COUNTI(inl(ES_REG(ensoniq, DAC1_SIZE)));
		ptr = bytes_to_frames(substream->runसमय, ptr);
	पूर्ण अन्यथा अणु
		ptr = 0;
	पूर्ण
	spin_unlock(&ensoniq->reg_lock);
	वापस ptr;
पूर्ण

अटल snd_pcm_uframes_t snd_ensoniq_playback2_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	spin_lock(&ensoniq->reg_lock);
	अगर (inl(ES_REG(ensoniq, CONTROL)) & ES_DAC2_EN) अणु
		outl(ES_MEM_PAGEO(ES_PAGE_DAC), ES_REG(ensoniq, MEM_PAGE));
		ptr = ES_REG_FCURR_COUNTI(inl(ES_REG(ensoniq, DAC2_SIZE)));
		ptr = bytes_to_frames(substream->runसमय, ptr);
	पूर्ण अन्यथा अणु
		ptr = 0;
	पूर्ण
	spin_unlock(&ensoniq->reg_lock);
	वापस ptr;
पूर्ण

अटल snd_pcm_uframes_t snd_ensoniq_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	spin_lock(&ensoniq->reg_lock);
	अगर (inl(ES_REG(ensoniq, CONTROL)) & ES_ADC_EN) अणु
		outl(ES_MEM_PAGEO(ES_PAGE_ADC), ES_REG(ensoniq, MEM_PAGE));
		ptr = ES_REG_FCURR_COUNTI(inl(ES_REG(ensoniq, ADC_SIZE)));
		ptr = bytes_to_frames(substream->runसमय, ptr);
	पूर्ण अन्यथा अणु
		ptr = 0;
	पूर्ण
	spin_unlock(&ensoniq->reg_lock);
	वापस ptr;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ensoniq_playback1 =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID |
				 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =
#अगर_अघोषित CHIP1370
				SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
#अन्यथा
				(SNDRV_PCM_RATE_KNOT | 	/* 5512Hz rate */
				 SNDRV_PCM_RATE_11025 | SNDRV_PCM_RATE_22050 | 
				 SNDRV_PCM_RATE_44100),
#पूर्ण_अगर
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ensoniq_playback2 =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_PAUSE | 
				 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_ensoniq_capture =
अणु
	.info =			(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
				 SNDRV_PCM_INFO_BLOCK_TRANSFER |
				 SNDRV_PCM_INFO_MMAP_VALID | SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =		SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE,
	.rates =		SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(128*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(128*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_ensoniq_playback1_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	ensoniq->mode |= ES_MODE_PLAY1;
	ensoniq->playback1_substream = substream;
	runसमय->hw = snd_ensoniq_playback1;
	snd_pcm_set_sync(substream);
	spin_lock_irq(&ensoniq->reg_lock);
	अगर (ensoniq->spdअगर && ensoniq->playback2_substream == शून्य)
		ensoniq->spdअगर_stream = ensoniq->spdअगर_शेष;
	spin_unlock_irq(&ensoniq->reg_lock);
#अगर_घोषित CHIP1370
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				   &snd_es1370_hw_स्थिरraपूर्णांकs_rates);
#अन्यथा
	snd_pcm_hw_स्थिरraपूर्णांक_ratdens(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1371_hw_स्थिरraपूर्णांकs_dac_घड़ी);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_playback2_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	ensoniq->mode |= ES_MODE_PLAY2;
	ensoniq->playback2_substream = substream;
	runसमय->hw = snd_ensoniq_playback2;
	snd_pcm_set_sync(substream);
	spin_lock_irq(&ensoniq->reg_lock);
	अगर (ensoniq->spdअगर && ensoniq->playback1_substream == शून्य)
		ensoniq->spdअगर_stream = ensoniq->spdअगर_शेष;
	spin_unlock_irq(&ensoniq->reg_lock);
#अगर_घोषित CHIP1370
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1370_hw_स्थिरraपूर्णांकs_घड़ी);
#अन्यथा
	snd_pcm_hw_स्थिरraपूर्णांक_ratdens(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1371_hw_स्थिरraपूर्णांकs_dac_घड़ी);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	ensoniq->mode |= ES_MODE_CAPTURE;
	ensoniq->capture_substream = substream;
	runसमय->hw = snd_ensoniq_capture;
	snd_pcm_set_sync(substream);
#अगर_घोषित CHIP1370
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1370_hw_स्थिरraपूर्णांकs_घड़ी);
#अन्यथा
	snd_pcm_hw_स्थिरraपूर्णांक_ratnums(runसमय, 0, SNDRV_PCM_HW_PARAM_RATE,
				      &snd_es1371_hw_स्थिरraपूर्णांकs_adc_घड़ी);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_playback1_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);

	ensoniq->playback1_substream = शून्य;
	ensoniq->mode &= ~ES_MODE_PLAY1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_playback2_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);

	ensoniq->playback2_substream = शून्य;
	spin_lock_irq(&ensoniq->reg_lock);
#अगर_घोषित CHIP1370
	ensoniq->u.es1370.pclkभाग_lock &= ~ES_MODE_PLAY2;
#पूर्ण_अगर
	ensoniq->mode &= ~ES_MODE_PLAY2;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = snd_pcm_substream_chip(substream);

	ensoniq->capture_substream = शून्य;
	spin_lock_irq(&ensoniq->reg_lock);
#अगर_घोषित CHIP1370
	ensoniq->u.es1370.pclkभाग_lock &= ~ES_MODE_CAPTURE;
#पूर्ण_अगर
	ensoniq->mode &= ~ES_MODE_CAPTURE;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ensoniq_playback1_ops = अणु
	.खोलो =		snd_ensoniq_playback1_खोलो,
	.बंद =	snd_ensoniq_playback1_बंद,
	.prepare =	snd_ensoniq_playback1_prepare,
	.trigger =	snd_ensoniq_trigger,
	.poपूर्णांकer =	snd_ensoniq_playback1_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ensoniq_playback2_ops = अणु
	.खोलो =		snd_ensoniq_playback2_खोलो,
	.बंद =	snd_ensoniq_playback2_बंद,
	.prepare =	snd_ensoniq_playback2_prepare,
	.trigger =	snd_ensoniq_trigger,
	.poपूर्णांकer =	snd_ensoniq_playback2_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ensoniq_capture_ops = अणु
	.खोलो =		snd_ensoniq_capture_खोलो,
	.बंद =	snd_ensoniq_capture_बंद,
	.prepare =	snd_ensoniq_capture_prepare,
	.trigger =	snd_ensoniq_trigger,
	.poपूर्णांकer =	snd_ensoniq_capture_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_chmap_elem surround_map[] = अणु
	अणु .channels = 1,
	  .map = अणु SNDRV_CHMAP_MONO पूर्ण पूर्ण,
	अणु .channels = 2,
	  .map = अणु SNDRV_CHMAP_RL, SNDRV_CHMAP_RR पूर्ण पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक snd_ensoniq_pcm(काष्ठा ensoniq *ensoniq, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(ensoniq->card, CHIP_NAME "/1", device, 1, 1, &pcm);
	अगर (err < 0)
		वापस err;

#अगर_घोषित CHIP1370
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ensoniq_playback2_ops);
#अन्यथा
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ensoniq_playback1_ops);
#पूर्ण_अगर
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_ensoniq_capture_ops);

	pcm->निजी_data = ensoniq;
	pcm->info_flags = 0;
	म_नकल(pcm->name, CHIP_NAME " DAC2/ADC");
	ensoniq->pcm1 = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ensoniq->pci->dev, 64*1024, 128*1024);

#अगर_घोषित CHIP1370
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     surround_map, 2, 0, शून्य);
#अन्यथा
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_std_chmaps, 2, 0, शून्य);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल पूर्णांक snd_ensoniq_pcm2(काष्ठा ensoniq *ensoniq, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(ensoniq->card, CHIP_NAME "/2", device, 1, 0, &pcm);
	अगर (err < 0)
		वापस err;

#अगर_घोषित CHIP1370
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ensoniq_playback1_ops);
#अन्यथा
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_ensoniq_playback2_ops);
#पूर्ण_अगर
	pcm->निजी_data = ensoniq;
	pcm->info_flags = 0;
	म_नकल(pcm->name, CHIP_NAME " DAC1");
	ensoniq->pcm2 = pcm;

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &ensoniq->pci->dev, 64*1024, 128*1024);

#अगर_घोषित CHIP1370
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     snd_pcm_std_chmaps, 2, 0, शून्य);
#अन्यथा
	err = snd_pcm_add_chmap_ctls(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				     surround_map, 2, 0, शून्य);
#पूर्ण_अगर
	वापस err;
पूर्ण

/*
 *  Mixer section
 */

/*
 * ENS1371 mixer (including SPDIF पूर्णांकerface)
 */
#अगर_घोषित CHIP1371
अटल पूर्णांक snd_ens1373_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
				  काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ens1373_spdअगर_शेष_get(काष्ठा snd_kcontrol *kcontrol,
                                         काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&ensoniq->reg_lock);
	ucontrol->value.iec958.status[0] = (ensoniq->spdअगर_शेष >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (ensoniq->spdअगर_शेष >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (ensoniq->spdअगर_शेष >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (ensoniq->spdअगर_शेष >> 24) & 0xff;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ens1373_spdअगर_शेष_put(काष्ठा snd_kcontrol *kcontrol,
                                         काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ((u32)ucontrol->value.iec958.status[0] << 0) |
	      ((u32)ucontrol->value.iec958.status[1] << 8) |
	      ((u32)ucontrol->value.iec958.status[2] << 16) |
	      ((u32)ucontrol->value.iec958.status[3] << 24);
	spin_lock_irq(&ensoniq->reg_lock);
	change = ensoniq->spdअगर_शेष != val;
	ensoniq->spdअगर_शेष = val;
	अगर (change && ensoniq->playback1_substream == शून्य &&
	    ensoniq->playback2_substream == शून्य)
		outl(val, ES_REG(ensoniq, CHANNEL_STATUS));
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_ens1373_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
				      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = 0xff;
	ucontrol->value.iec958.status[1] = 0xff;
	ucontrol->value.iec958.status[2] = 0xff;
	ucontrol->value.iec958.status[3] = 0xff;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ens1373_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	spin_lock_irq(&ensoniq->reg_lock);
	ucontrol->value.iec958.status[0] = (ensoniq->spdअगर_stream >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (ensoniq->spdअगर_stream >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (ensoniq->spdअगर_stream >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (ensoniq->spdअगर_stream >> 24) & 0xff;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ens1373_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
                                        काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ((u32)ucontrol->value.iec958.status[0] << 0) |
	      ((u32)ucontrol->value.iec958.status[1] << 8) |
	      ((u32)ucontrol->value.iec958.status[2] << 16) |
	      ((u32)ucontrol->value.iec958.status[3] << 24);
	spin_lock_irq(&ensoniq->reg_lock);
	change = ensoniq->spdअगर_stream != val;
	ensoniq->spdअगर_stream = val;
	अगर (change && (ensoniq->playback1_substream != शून्य ||
		       ensoniq->playback2_substream != शून्य))
		outl(val, ES_REG(ensoniq, CHANNEL_STATUS));
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस change;
पूर्ण

#घोषणा ES1371_SPDIF(xname) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .info = snd_es1371_spdअगर_info, \
  .get = snd_es1371_spdअगर_get, .put = snd_es1371_spdअगर_put पूर्ण

#घोषणा snd_es1371_spdअगर_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_es1371_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&ensoniq->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] = ensoniq->ctrl & ES_1373_SPDIF_THRU ? 1 : 0;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1371_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक nval1, nval2;
	पूर्णांक change;
	
	nval1 = ucontrol->value.पूर्णांकeger.value[0] ? ES_1373_SPDIF_THRU : 0;
	nval2 = ucontrol->value.पूर्णांकeger.value[0] ? ES_1373_SPDIF_EN : 0;
	spin_lock_irq(&ensoniq->reg_lock);
	change = (ensoniq->ctrl & ES_1373_SPDIF_THRU) != nval1;
	ensoniq->ctrl &= ~ES_1373_SPDIF_THRU;
	ensoniq->ctrl |= nval1;
	ensoniq->cssr &= ~ES_1373_SPDIF_EN;
	ensoniq->cssr |= nval2;
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ensoniq->cssr, ES_REG(ensoniq, STATUS));
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस change;
पूर्ण


/* spdअगर controls */
अटल स्थिर काष्ठा snd_kcontrol_new snd_es1371_mixer_spdअगर[] = अणु
	ES1371_SPDIF(SNDRV_CTL_NAME_IEC958("",PLAYBACK,SWITCH)),
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
		.info =		snd_ens1373_spdअगर_info,
		.get =		snd_ens1373_spdअगर_शेष_get,
		.put =		snd_ens1373_spdअगर_शेष_put,
	पूर्ण,
	अणु
		.access =	SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,MASK),
		.info =		snd_ens1373_spdअगर_info,
		.get =		snd_ens1373_spdअगर_mask_get
	पूर्ण,
	अणु
		.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
		.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
		.info =		snd_ens1373_spdअगर_info,
		.get =		snd_ens1373_spdअगर_stream_get,
		.put =		snd_ens1373_spdअगर_stream_put
	पूर्ण,
पूर्ण;


#घोषणा snd_es1373_rear_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_es1373_rear_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	पूर्णांक val = 0;
	
	spin_lock_irq(&ensoniq->reg_lock);
	अगर ((ensoniq->cssr & (ES_1373_REAR_BIT27|ES_1373_REAR_BIT26|
			      ES_1373_REAR_BIT24)) == ES_1373_REAR_BIT26)
	    	val = 1;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1373_rear_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक nval1;
	पूर्णांक change;
	
	nval1 = ucontrol->value.पूर्णांकeger.value[0] ?
		ES_1373_REAR_BIT26 : (ES_1373_REAR_BIT27|ES_1373_REAR_BIT24);
	spin_lock_irq(&ensoniq->reg_lock);
	change = (ensoniq->cssr & (ES_1373_REAR_BIT27|
				   ES_1373_REAR_BIT26|ES_1373_REAR_BIT24)) != nval1;
	ensoniq->cssr &= ~(ES_1373_REAR_BIT27|ES_1373_REAR_BIT26|ES_1373_REAR_BIT24);
	ensoniq->cssr |= nval1;
	outl(ensoniq->cssr, ES_REG(ensoniq, STATUS));
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ens1373_rear =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"AC97 2ch->4ch Copy Switch",
	.info =		snd_es1373_rear_info,
	.get =		snd_es1373_rear_get,
	.put =		snd_es1373_rear_put,
पूर्ण;

#घोषणा snd_es1373_line_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_es1373_line_get(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	पूर्णांक val = 0;
	
	spin_lock_irq(&ensoniq->reg_lock);
	अगर (ensoniq->ctrl & ES_1371_GPIO_OUT(4))
	    	val = 1;
	ucontrol->value.पूर्णांकeger.value[0] = val;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_es1373_line_put(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	पूर्णांक changed;
	अचिन्हित पूर्णांक ctrl;
	
	spin_lock_irq(&ensoniq->reg_lock);
	ctrl = ensoniq->ctrl;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		ensoniq->ctrl |= ES_1371_GPIO_OUT(4);	/* चयन line-in -> rear out */
	अन्यथा
		ensoniq->ctrl &= ~ES_1371_GPIO_OUT(4);
	changed = (ctrl != ensoniq->ctrl);
	अगर (changed)
		outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस changed;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ens1373_line =
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =		"Line In->Rear Out Switch",
	.info =		snd_es1373_line_info,
	.get =		snd_es1373_line_get,
	.put =		snd_es1373_line_put,
पूर्ण;

अटल व्योम snd_ensoniq_mixer_मुक्त_ac97(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा ensoniq *ensoniq = ac97->निजी_data;
	ensoniq->u.es1371.ac97 = शून्य;
पूर्ण

काष्ठा es1371_quirk अणु
	अचिन्हित लघु vid;		/* venकरोr ID */
	अचिन्हित लघु did;		/* device ID */
	अचिन्हित अक्षर rev;		/* revision */
पूर्ण;

अटल पूर्णांक es1371_quirk_lookup(काष्ठा ensoniq *ensoniq,
			       स्थिर काष्ठा es1371_quirk *list)
अणु
	जबतक (list->vid != (अचिन्हित लघु)PCI_ANY_ID) अणु
		अगर (ensoniq->pci->venकरोr == list->vid &&
		    ensoniq->pci->device == list->did &&
		    ensoniq->rev == list->rev)
			वापस 1;
		list++;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा es1371_quirk es1371_spdअगर_present[] = अणु
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .rev = CT5880REV_CT5880_C पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .rev = CT5880REV_CT5880_D पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .rev = CT5880REV_CT5880_E पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .rev = ES1371REV_CT5880_A पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .rev = ES1371REV_ES1373_8 पूर्ण,
	अणु .vid = PCI_ANY_ID, .did = PCI_ANY_ID पूर्ण
पूर्ण;

अटल स्थिर काष्ठा snd_pci_quirk ens1373_line_quirk[] = अणु
	SND_PCI_QUIRK_ID(0x1274, 0x2000), /* GA-7DXR */
	SND_PCI_QUIRK_ID(0x1458, 0xa000), /* GA-8IEXP */
	अणु पूर्ण /* end */
पूर्ण;

अटल पूर्णांक snd_ensoniq_1371_mixer(काष्ठा ensoniq *ensoniq,
				  पूर्णांक has_spdअगर, पूर्णांक has_line)
अणु
	काष्ठा snd_card *card = ensoniq->card;
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_es1371_codec_ग_लिखो,
		.पढ़ो = snd_es1371_codec_पढ़ो,
		.रुको = snd_es1371_codec_रुको,
	पूर्ण;

	अगर ((err = snd_ac97_bus(card, 0, &ops, शून्य, &pbus)) < 0)
		वापस err;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = ensoniq;
	ac97.निजी_मुक्त = snd_ensoniq_mixer_मुक्त_ac97;
	ac97.pci = ensoniq->pci;
	ac97.scaps = AC97_SCAP_AUDIO;
	अगर ((err = snd_ac97_mixer(pbus, &ac97, &ensoniq->u.es1371.ac97)) < 0)
		वापस err;
	अगर (has_spdअगर > 0 ||
	    (!has_spdअगर && es1371_quirk_lookup(ensoniq, es1371_spdअगर_present))) अणु
		काष्ठा snd_kcontrol *kctl;
		पूर्णांक i, is_spdअगर = 0;

		ensoniq->spdअगर_शेष = ensoniq->spdअगर_stream =
			SNDRV_PCM_DEFAULT_CON_SPDIF;
		outl(ensoniq->spdअगर_शेष, ES_REG(ensoniq, CHANNEL_STATUS));

		अगर (ensoniq->u.es1371.ac97->ext_id & AC97_EI_SPDIF)
			is_spdअगर++;

		क्रम (i = 0; i < ARRAY_SIZE(snd_es1371_mixer_spdअगर); i++) अणु
			kctl = snd_ctl_new1(&snd_es1371_mixer_spdअगर[i], ensoniq);
			अगर (!kctl)
				वापस -ENOMEM;
			kctl->id.index = is_spdअगर;
			err = snd_ctl_add(card, kctl);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	अगर (ensoniq->u.es1371.ac97->ext_id & AC97_EI_SDAC) अणु
		/* mirror rear to front speakers */
		ensoniq->cssr &= ~(ES_1373_REAR_BIT27|ES_1373_REAR_BIT24);
		ensoniq->cssr |= ES_1373_REAR_BIT26;
		err = snd_ctl_add(card, snd_ctl_new1(&snd_ens1373_rear, ensoniq));
		अगर (err < 0)
			वापस err;
	पूर्ण
	अगर (has_line > 0 ||
	    snd_pci_quirk_lookup(ensoniq->pci, ens1373_line_quirk)) अणु
		 err = snd_ctl_add(card, snd_ctl_new1(&snd_ens1373_line,
						      ensoniq));
		 अगर (err < 0)
			 वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर /* CHIP1371 */

/* generic control callbacks क्रम ens1370 */
#अगर_घोषित CHIP1370
#घोषणा ENSONIQ_CONTROL(xname, mask) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_CARD, .name = xname, .info = snd_ensoniq_control_info, \
  .get = snd_ensoniq_control_get, .put = snd_ensoniq_control_put, \
  .निजी_value = mask पूर्ण

#घोषणा snd_ensoniq_control_info	snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ensoniq_control_get(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	पूर्णांक mask = kcontrol->निजी_value;
	
	spin_lock_irq(&ensoniq->reg_lock);
	ucontrol->value.पूर्णांकeger.value[0] = ensoniq->ctrl & mask ? 1 : 0;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_control_put(काष्ठा snd_kcontrol *kcontrol,
				   काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा ensoniq *ensoniq = snd_kcontrol_chip(kcontrol);
	पूर्णांक mask = kcontrol->निजी_value;
	अचिन्हित पूर्णांक nval;
	पूर्णांक change;
	
	nval = ucontrol->value.पूर्णांकeger.value[0] ? mask : 0;
	spin_lock_irq(&ensoniq->reg_lock);
	change = (ensoniq->ctrl & mask) != nval;
	ensoniq->ctrl &= ~mask;
	ensoniq->ctrl |= nval;
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस change;
पूर्ण

/*
 * ENS1370 mixer
 */

अटल स्थिर काष्ठा snd_kcontrol_new snd_es1370_controls[2] = अणु
ENSONIQ_CONTROL("PCM 0 Output also on Line-In Jack", ES_1370_XCTL0),
ENSONIQ_CONTROL("Mic +5V bias", ES_1370_XCTL1)
पूर्ण;

#घोषणा ES1370_CONTROLS ARRAY_SIZE(snd_es1370_controls)

अटल व्योम snd_ensoniq_mixer_मुक्त_ak4531(काष्ठा snd_ak4531 *ak4531)
अणु
	काष्ठा ensoniq *ensoniq = ak4531->निजी_data;
	ensoniq->u.es1370.ak4531 = शून्य;
पूर्ण

अटल पूर्णांक snd_ensoniq_1370_mixer(काष्ठा ensoniq *ensoniq)
अणु
	काष्ठा snd_card *card = ensoniq->card;
	काष्ठा snd_ak4531 ak4531;
	अचिन्हित पूर्णांक idx;
	पूर्णांक err;

	/* try reset AK4531 */
	outw(ES_1370_CODEC_WRITE(AK4531_RESET, 0x02), ES_REG(ensoniq, 1370_CODEC));
	inw(ES_REG(ensoniq, 1370_CODEC));
	udelay(100);
	outw(ES_1370_CODEC_WRITE(AK4531_RESET, 0x03), ES_REG(ensoniq, 1370_CODEC));
	inw(ES_REG(ensoniq, 1370_CODEC));
	udelay(100);

	स_रखो(&ak4531, 0, माप(ak4531));
	ak4531.ग_लिखो = snd_es1370_codec_ग_लिखो;
	ak4531.निजी_data = ensoniq;
	ak4531.निजी_मुक्त = snd_ensoniq_mixer_मुक्त_ak4531;
	अगर ((err = snd_ak4531_mixer(card, &ak4531, &ensoniq->u.es1370.ak4531)) < 0)
		वापस err;
	क्रम (idx = 0; idx < ES1370_CONTROLS; idx++) अणु
		err = snd_ctl_add(card, snd_ctl_new1(&snd_es1370_controls[idx], ensoniq));
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CHIP1370 */

#अगर_घोषित SUPPORT_JOYSTICK

#अगर_घोषित CHIP1371
अटल पूर्णांक snd_ensoniq_get_joystick_port(काष्ठा ensoniq *ensoniq, पूर्णांक dev)
अणु
	चयन (joystick_port[dev]) अणु
	हाल 0: /* disabled */
	हाल 1: /* स्वतः-detect */
	हाल 0x200:
	हाल 0x208:
	हाल 0x210:
	हाल 0x218:
		वापस joystick_port[dev];

	शेष:
		dev_err(ensoniq->card->dev,
			"invalid joystick port %#x", joystick_port[dev]);
		वापस 0;
	पूर्ण
पूर्ण
#अन्यथा
अटल पूर्णांक snd_ensoniq_get_joystick_port(काष्ठा ensoniq *ensoniq, पूर्णांक dev)
अणु
	वापस joystick[dev] ? 0x200 : 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक snd_ensoniq_create_gameport(काष्ठा ensoniq *ensoniq, पूर्णांक dev)
अणु
	काष्ठा gameport *gp;
	पूर्णांक io_port;

	io_port = snd_ensoniq_get_joystick_port(ensoniq, dev);

	चयन (io_port) अणु
	हाल 0:
		वापस -ENOSYS;

	हाल 1: /* स्वतः_detect */
		क्रम (io_port = 0x200; io_port <= 0x218; io_port += 8)
			अगर (request_region(io_port, 8, "ens137x: gameport"))
				अवरोध;
		अगर (io_port > 0x218) अणु
			dev_warn(ensoniq->card->dev,
				 "no gameport ports available\n");
			वापस -EBUSY;
		पूर्ण
		अवरोध;

	शेष:
		अगर (!request_region(io_port, 8, "ens137x: gameport")) अणु
			dev_warn(ensoniq->card->dev,
				 "gameport io port %#x in use\n",
			       io_port);
			वापस -EBUSY;
		पूर्ण
		अवरोध;
	पूर्ण

	ensoniq->gameport = gp = gameport_allocate_port();
	अगर (!gp) अणु
		dev_err(ensoniq->card->dev,
			"cannot allocate memory for gameport\n");
		release_region(io_port, 8);
		वापस -ENOMEM;
	पूर्ण

	gameport_set_name(gp, "ES137x");
	gameport_set_phys(gp, "pci%s/gameport0", pci_name(ensoniq->pci));
	gameport_set_dev_parent(gp, &ensoniq->pci->dev);
	gp->io = io_port;

	ensoniq->ctrl |= ES_JYSTK_EN;
#अगर_घोषित CHIP1371
	ensoniq->ctrl &= ~ES_1371_JOY_ASELM;
	ensoniq->ctrl |= ES_1371_JOY_ASEL((io_port - 0x200) / 8);
#पूर्ण_अगर
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));

	gameport_रेजिस्टर_port(ensoniq->gameport);

	वापस 0;
पूर्ण

अटल व्योम snd_ensoniq_मुक्त_gameport(काष्ठा ensoniq *ensoniq)
अणु
	अगर (ensoniq->gameport) अणु
		पूर्णांक port = ensoniq->gameport->io;

		gameport_unरेजिस्टर_port(ensoniq->gameport);
		ensoniq->gameport = शून्य;
		ensoniq->ctrl &= ~ES_JYSTK_EN;
		outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
		release_region(port, 8);
	पूर्ण
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक snd_ensoniq_create_gameport(काष्ठा ensoniq *ensoniq, दीर्घ port) अणु वापस -ENOSYS; पूर्ण
अटल अंतरभूत व्योम snd_ensoniq_मुक्त_gameport(काष्ठा ensoniq *ensoniq) अणु पूर्ण
#पूर्ण_अगर /* SUPPORT_JOYSTICK */

/*

 */

अटल व्योम snd_ensoniq_proc_पढ़ो(काष्ठा snd_info_entry *entry, 
				  काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा ensoniq *ensoniq = entry->निजी_data;

	snd_iम_लिखो(buffer, "Ensoniq AudioPCI " CHIP_NAME "\n\n");
	snd_iम_लिखो(buffer, "Joystick enable  : %s\n",
		    ensoniq->ctrl & ES_JYSTK_EN ? "on" : "off");
#अगर_घोषित CHIP1370
	snd_iम_लिखो(buffer, "MIC +5V bias     : %s\n",
		    ensoniq->ctrl & ES_1370_XCTL1 ? "on" : "off");
	snd_iम_लिखो(buffer, "Line In to AOUT  : %s\n",
		    ensoniq->ctrl & ES_1370_XCTL0 ? "on" : "off");
#अन्यथा
	snd_iम_लिखो(buffer, "Joystick port    : 0x%x\n",
		    (ES_1371_JOY_ASELI(ensoniq->ctrl) * 8) + 0x200);
#पूर्ण_अगर
पूर्ण

अटल व्योम snd_ensoniq_proc_init(काष्ठा ensoniq *ensoniq)
अणु
	snd_card_ro_proc_new(ensoniq->card, "audiopci", ensoniq,
			     snd_ensoniq_proc_पढ़ो);
पूर्ण

/*

 */

अटल पूर्णांक snd_ensoniq_मुक्त(काष्ठा ensoniq *ensoniq)
अणु
	snd_ensoniq_मुक्त_gameport(ensoniq);
	अगर (ensoniq->irq < 0)
		जाओ __hw_end;
#अगर_घोषित CHIP1370
	outl(ES_1370_SERR_DISABLE, ES_REG(ensoniq, CONTROL));	/* चयन everything off */
	outl(0, ES_REG(ensoniq, SERIAL));	/* clear serial पूर्णांकerface */
#अन्यथा
	outl(0, ES_REG(ensoniq, CONTROL));	/* चयन everything off */
	outl(0, ES_REG(ensoniq, SERIAL));	/* clear serial पूर्णांकerface */
#पूर्ण_अगर
	pci_set_घातer_state(ensoniq->pci, PCI_D3hot);
      __hw_end:
#अगर_घोषित CHIP1370
	अगर (ensoniq->dma_bug.area)
		snd_dma_मुक्त_pages(&ensoniq->dma_bug);
#पूर्ण_अगर
	अगर (ensoniq->irq >= 0)
		मुक्त_irq(ensoniq->irq, ensoniq);
	pci_release_regions(ensoniq->pci);
	pci_disable_device(ensoniq->pci);
	kमुक्त(ensoniq);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा ensoniq *ensoniq = device->device_data;
	वापस snd_ensoniq_मुक्त(ensoniq);
पूर्ण

#अगर_घोषित CHIP1371
अटल स्थिर काष्ठा snd_pci_quirk es1371_amplअगरier_hack[] = अणु
	SND_PCI_QUIRK_ID(0x107b, 0x2150),	/* Gateway Solo 2150 */
	SND_PCI_QUIRK_ID(0x13bd, 0x100c),	/* EV1938 on Mebius PC-MJ100V */
	SND_PCI_QUIRK_ID(0x1102, 0x5938),	/* Targa Xtender300 */
	SND_PCI_QUIRK_ID(0x1102, 0x8938),	/* IPC Topnote G notebook */
	अणु पूर्ण /* end */
पूर्ण;

अटल स्थिर काष्ठा es1371_quirk es1371_ac97_reset_hack[] = अणु
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .rev = CT5880REV_CT5880_C पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .rev = CT5880REV_CT5880_D पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_CT5880, .rev = CT5880REV_CT5880_E पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .rev = ES1371REV_CT5880_A पूर्ण,
	अणु .vid = PCI_VENDOR_ID_ENSONIQ, .did = PCI_DEVICE_ID_ENSONIQ_ES1371, .rev = ES1371REV_ES1373_8 पूर्ण,
	अणु .vid = PCI_ANY_ID, .did = PCI_ANY_ID पूर्ण
पूर्ण;
#पूर्ण_अगर

अटल व्योम snd_ensoniq_chip_init(काष्ठा ensoniq *ensoniq)
अणु
#अगर_घोषित CHIP1371
	पूर्णांक idx;
#पूर्ण_अगर
	/* this code was part of snd_ensoniq_create beक्रमe पूर्णांकruduction
	  * of suspend/resume
	  */
#अगर_घोषित CHIP1370
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl(ES_MEM_PAGEO(ES_PAGE_ADC), ES_REG(ensoniq, MEM_PAGE));
	outl(ensoniq->dma_bug.addr, ES_REG(ensoniq, PHANTOM_FRAME));
	outl(0, ES_REG(ensoniq, PHANTOM_COUNT));
#अन्यथा
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	outl(0, ES_REG(ensoniq, 1371_LEGACY));
	अगर (es1371_quirk_lookup(ensoniq, es1371_ac97_reset_hack)) अणु
	    outl(ensoniq->cssr, ES_REG(ensoniq, STATUS));
	    /* need to delay around 20ms(bleech) to give
	       some CODECs enough समय to wakeup */
	    msleep(20);
	पूर्ण
	/* AC'97 warm reset to start the bitclk */
	outl(ensoniq->ctrl | ES_1371_SYNC_RES, ES_REG(ensoniq, CONTROL));
	inl(ES_REG(ensoniq, CONTROL));
	udelay(20);
	outl(ensoniq->ctrl, ES_REG(ensoniq, CONTROL));
	/* Init the sample rate converter */
	snd_es1371_रुको_src_पढ़ोy(ensoniq);	
	outl(ES_1371_SRC_DISABLE, ES_REG(ensoniq, 1371_SMPRATE));
	क्रम (idx = 0; idx < 0x80; idx++)
		snd_es1371_src_ग_लिखो(ensoniq, idx, 0);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC1 + ES_SMPREG_TRUNC_N, 16 << 4);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC1 + ES_SMPREG_INT_REGS, 16 << 10);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC2 + ES_SMPREG_TRUNC_N, 16 << 4);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_DAC2 + ES_SMPREG_INT_REGS, 16 << 10);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_ADC, 1 << 12);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_ADC + 1, 1 << 12);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_DAC1, 1 << 12);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_DAC1 + 1, 1 << 12);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_DAC2, 1 << 12);
	snd_es1371_src_ग_लिखो(ensoniq, ES_SMPREG_VOL_DAC2 + 1, 1 << 12);
	snd_es1371_adc_rate(ensoniq, 22050);
	snd_es1371_dac1_rate(ensoniq, 22050);
	snd_es1371_dac2_rate(ensoniq, 22050);
	/* WARNING:
	 * enabling the sample rate converter without properly programming
	 * its parameters causes the chip to lock up (the SRC busy bit will
	 * be stuck high, and I've found no way to rectअगरy this other than
	 * घातer cycle) - Thomas Sailer
	 */
	snd_es1371_रुको_src_पढ़ोy(ensoniq);
	outl(0, ES_REG(ensoniq, 1371_SMPRATE));
	/* try reset codec directly */
	outl(ES_1371_CODEC_WRITE(0, 0), ES_REG(ensoniq, 1371_CODEC));
#पूर्ण_अगर
	outb(ensoniq->uartc = 0x00, ES_REG(ensoniq, UART_CONTROL));
	outb(0x00, ES_REG(ensoniq, UART_RES));
	outl(ensoniq->cssr, ES_REG(ensoniq, STATUS));
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक snd_ensoniq_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा ensoniq *ensoniq = card->निजी_data;
	
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

#अगर_घोषित CHIP1371	
	snd_ac97_suspend(ensoniq->u.es1371.ac97);
#अन्यथा
	/* try to reset AK4531 */
	outw(ES_1370_CODEC_WRITE(AK4531_RESET, 0x02), ES_REG(ensoniq, 1370_CODEC));
	inw(ES_REG(ensoniq, 1370_CODEC));
	udelay(100);
	outw(ES_1370_CODEC_WRITE(AK4531_RESET, 0x03), ES_REG(ensoniq, 1370_CODEC));
	inw(ES_REG(ensoniq, 1370_CODEC));
	udelay(100);
	snd_ak4531_suspend(ensoniq->u.es1370.ak4531);
#पूर्ण_अगर	
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा ensoniq *ensoniq = card->निजी_data;

	snd_ensoniq_chip_init(ensoniq);

#अगर_घोषित CHIP1371	
	snd_ac97_resume(ensoniq->u.es1371.ac97);
#अन्यथा
	snd_ak4531_resume(ensoniq->u.es1370.ak4531);
#पूर्ण_अगर	
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(snd_ensoniq_pm, snd_ensoniq_suspend, snd_ensoniq_resume);
#घोषणा SND_ENSONIQ_PM_OPS	&snd_ensoniq_pm
#अन्यथा
#घोषणा SND_ENSONIQ_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक snd_ensoniq_create(काष्ठा snd_card *card,
			      काष्ठा pci_dev *pci,
			      काष्ठा ensoniq **rensoniq)
अणु
	काष्ठा ensoniq *ensoniq;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_ensoniq_dev_मुक्त,
	पूर्ण;

	*rensoniq = शून्य;
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	ensoniq = kzalloc(माप(*ensoniq), GFP_KERNEL);
	अगर (ensoniq == शून्य) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण
	spin_lock_init(&ensoniq->reg_lock);
	mutex_init(&ensoniq->src_mutex);
	ensoniq->card = card;
	ensoniq->pci = pci;
	ensoniq->irq = -1;
	अगर ((err = pci_request_regions(pci, "Ensoniq AudioPCI")) < 0) अणु
		kमुक्त(ensoniq);
		pci_disable_device(pci);
		वापस err;
	पूर्ण
	ensoniq->port = pci_resource_start(pci, 0);
	अगर (request_irq(pci->irq, snd_audiopci_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, ensoniq)) अणु
		dev_err(card->dev, "unable to grab IRQ %d\n", pci->irq);
		snd_ensoniq_मुक्त(ensoniq);
		वापस -EBUSY;
	पूर्ण
	ensoniq->irq = pci->irq;
	card->sync_irq = ensoniq->irq;
#अगर_घोषित CHIP1370
	अगर (snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, &pci->dev,
				16, &ensoniq->dma_bug) < 0) अणु
		dev_err(card->dev, "unable to allocate space for phantom area - dma_bug\n");
		snd_ensoniq_मुक्त(ensoniq);
		वापस -EBUSY;
	पूर्ण
#पूर्ण_अगर
	pci_set_master(pci);
	ensoniq->rev = pci->revision;
#अगर_घोषित CHIP1370
#अगर 0
	ensoniq->ctrl = ES_1370_CDC_EN | ES_1370_SERR_DISABLE |
		ES_1370_PCLKDIVO(ES_1370_SRTODIV(8000));
#अन्यथा	/* get microphone working */
	ensoniq->ctrl = ES_1370_CDC_EN | ES_1370_PCLKDIVO(ES_1370_SRTODIV(8000));
#पूर्ण_अगर
	ensoniq->sctrl = 0;
#अन्यथा
	ensoniq->ctrl = 0;
	ensoniq->sctrl = 0;
	ensoniq->cssr = 0;
	अगर (snd_pci_quirk_lookup(pci, es1371_amplअगरier_hack))
		ensoniq->ctrl |= ES_1371_GPIO_OUT(1);	/* turn amplअगरier on */

	अगर (es1371_quirk_lookup(ensoniq, es1371_ac97_reset_hack))
		ensoniq->cssr |= ES_1371_ST_AC97_RST;
#पूर्ण_अगर

	snd_ensoniq_chip_init(ensoniq);

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, ensoniq, &ops)) < 0) अणु
		snd_ensoniq_मुक्त(ensoniq);
		वापस err;
	पूर्ण

	snd_ensoniq_proc_init(ensoniq);

	*rensoniq = ensoniq;
	वापस 0;
पूर्ण

/*
 *  MIDI section
 */

अटल व्योम snd_ensoniq_midi_पूर्णांकerrupt(काष्ठा ensoniq * ensoniq)
अणु
	काष्ठा snd_rawmidi *rmidi = ensoniq->rmidi;
	अचिन्हित अक्षर status, mask, byte;

	अगर (rmidi == शून्य)
		वापस;
	/* करो Rx at first */
	spin_lock(&ensoniq->reg_lock);
	mask = ensoniq->uarपंचांग & ES_MODE_INPUT ? ES_RXRDY : 0;
	जबतक (mask) अणु
		status = inb(ES_REG(ensoniq, UART_STATUS));
		अगर ((status & mask) == 0)
			अवरोध;
		byte = inb(ES_REG(ensoniq, UART_DATA));
		snd_rawmidi_receive(ensoniq->midi_input, &byte, 1);
	पूर्ण
	spin_unlock(&ensoniq->reg_lock);

	/* करो Tx at second */
	spin_lock(&ensoniq->reg_lock);
	mask = ensoniq->uarपंचांग & ES_MODE_OUTPUT ? ES_TXRDY : 0;
	जबतक (mask) अणु
		status = inb(ES_REG(ensoniq, UART_STATUS));
		अगर ((status & mask) == 0)
			अवरोध;
		अगर (snd_rawmidi_transmit(ensoniq->midi_output, &byte, 1) != 1) अणु
			ensoniq->uartc &= ~ES_TXINTENM;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
			mask &= ~ES_TXRDY;
		पूर्ण अन्यथा अणु
			outb(byte, ES_REG(ensoniq, UART_DATA));
		पूर्ण
	पूर्ण
	spin_unlock(&ensoniq->reg_lock);
पूर्ण

अटल पूर्णांक snd_ensoniq_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = substream->rmidi->निजी_data;

	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->uarपंचांग |= ES_MODE_INPUT;
	ensoniq->midi_input = substream;
	अगर (!(ensoniq->uarपंचांग & ES_MODE_OUTPUT)) अणु
		outb(ES_CNTRL(3), ES_REG(ensoniq, UART_CONTROL));
		outb(ensoniq->uartc = 0, ES_REG(ensoniq, UART_CONTROL));
		outl(ensoniq->ctrl |= ES_UART_EN, ES_REG(ensoniq, CONTROL));
	पूर्ण
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = substream->rmidi->निजी_data;

	spin_lock_irq(&ensoniq->reg_lock);
	अगर (!(ensoniq->uarपंचांग & ES_MODE_OUTPUT)) अणु
		outb(ensoniq->uartc = 0, ES_REG(ensoniq, UART_CONTROL));
		outl(ensoniq->ctrl &= ~ES_UART_EN, ES_REG(ensoniq, CONTROL));
	पूर्ण अन्यथा अणु
		outb(ensoniq->uartc &= ~ES_RXINTEN, ES_REG(ensoniq, UART_CONTROL));
	पूर्ण
	ensoniq->midi_input = शून्य;
	ensoniq->uarपंचांग &= ~ES_MODE_INPUT;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = substream->rmidi->निजी_data;

	spin_lock_irq(&ensoniq->reg_lock);
	ensoniq->uarपंचांग |= ES_MODE_OUTPUT;
	ensoniq->midi_output = substream;
	अगर (!(ensoniq->uarपंचांग & ES_MODE_INPUT)) अणु
		outb(ES_CNTRL(3), ES_REG(ensoniq, UART_CONTROL));
		outb(ensoniq->uartc = 0, ES_REG(ensoniq, UART_CONTROL));
		outl(ensoniq->ctrl |= ES_UART_EN, ES_REG(ensoniq, CONTROL));
	पूर्ण
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ensoniq_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा ensoniq *ensoniq = substream->rmidi->निजी_data;

	spin_lock_irq(&ensoniq->reg_lock);
	अगर (!(ensoniq->uarपंचांग & ES_MODE_INPUT)) अणु
		outb(ensoniq->uartc = 0, ES_REG(ensoniq, UART_CONTROL));
		outl(ensoniq->ctrl &= ~ES_UART_EN, ES_REG(ensoniq, CONTROL));
	पूर्ण अन्यथा अणु
		outb(ensoniq->uartc &= ~ES_TXINTENM, ES_REG(ensoniq, UART_CONTROL));
	पूर्ण
	ensoniq->midi_output = शून्य;
	ensoniq->uarपंचांग &= ~ES_MODE_OUTPUT;
	spin_unlock_irq(&ensoniq->reg_lock);
	वापस 0;
पूर्ण

अटल व्योम snd_ensoniq_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ensoniq *ensoniq = substream->rmidi->निजी_data;
	पूर्णांक idx;

	spin_lock_irqsave(&ensoniq->reg_lock, flags);
	अगर (up) अणु
		अगर ((ensoniq->uartc & ES_RXINTEN) == 0) अणु
			/* empty input FIFO */
			क्रम (idx = 0; idx < 32; idx++)
				inb(ES_REG(ensoniq, UART_DATA));
			ensoniq->uartc |= ES_RXINTEN;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ensoniq->uartc & ES_RXINTEN) अणु
			ensoniq->uartc &= ~ES_RXINTEN;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ensoniq->reg_lock, flags);
पूर्ण

अटल व्योम snd_ensoniq_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ensoniq *ensoniq = substream->rmidi->निजी_data;
	अचिन्हित अक्षर byte;

	spin_lock_irqsave(&ensoniq->reg_lock, flags);
	अगर (up) अणु
		अगर (ES_TXINTENI(ensoniq->uartc) == 0) अणु
			ensoniq->uartc |= ES_TXINTENO(1);
			/* fill UART FIFO buffer at first, and turn Tx पूर्णांकerrupts only अगर necessary */
			जबतक (ES_TXINTENI(ensoniq->uartc) == 1 &&
			       (inb(ES_REG(ensoniq, UART_STATUS)) & ES_TXRDY)) अणु
				अगर (snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					ensoniq->uartc &= ~ES_TXINTENM;
				पूर्ण अन्यथा अणु
					outb(byte, ES_REG(ensoniq, UART_DATA));
				पूर्ण
			पूर्ण
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (ES_TXINTENI(ensoniq->uartc) == 1) अणु
			ensoniq->uartc &= ~ES_TXINTENM;
			outb(ensoniq->uartc, ES_REG(ensoniq, UART_CONTROL));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&ensoniq->reg_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_ensoniq_midi_output =
अणु
	.खोलो =		snd_ensoniq_midi_output_खोलो,
	.बंद =	snd_ensoniq_midi_output_बंद,
	.trigger =	snd_ensoniq_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_ensoniq_midi_input =
अणु
	.खोलो =		snd_ensoniq_midi_input_खोलो,
	.बंद =	snd_ensoniq_midi_input_बंद,
	.trigger =	snd_ensoniq_midi_input_trigger,
पूर्ण;

अटल पूर्णांक snd_ensoniq_midi(काष्ठा ensoniq *ensoniq, पूर्णांक device)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(ensoniq->card, "ES1370/1", device, 1, 1, &rmidi)) < 0)
		वापस err;
	म_नकल(rmidi->name, CHIP_NAME);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_ensoniq_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_ensoniq_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT |
		SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = ensoniq;
	ensoniq->rmidi = rmidi;
	वापस 0;
पूर्ण

/*
 *  Interrupt handler
 */

अटल irqवापस_t snd_audiopci_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ensoniq *ensoniq = dev_id;
	अचिन्हित पूर्णांक status, sctrl;

	अगर (ensoniq == शून्य)
		वापस IRQ_NONE;

	status = inl(ES_REG(ensoniq, STATUS));
	अगर (!(status & ES_INTR))
		वापस IRQ_NONE;

	spin_lock(&ensoniq->reg_lock);
	sctrl = ensoniq->sctrl;
	अगर (status & ES_DAC1)
		sctrl &= ~ES_P1_INT_EN;
	अगर (status & ES_DAC2)
		sctrl &= ~ES_P2_INT_EN;
	अगर (status & ES_ADC)
		sctrl &= ~ES_R1_INT_EN;
	outl(sctrl, ES_REG(ensoniq, SERIAL));
	outl(ensoniq->sctrl, ES_REG(ensoniq, SERIAL));
	spin_unlock(&ensoniq->reg_lock);

	अगर (status & ES_UART)
		snd_ensoniq_midi_पूर्णांकerrupt(ensoniq);
	अगर ((status & ES_DAC2) && ensoniq->playback2_substream)
		snd_pcm_period_elapsed(ensoniq->playback2_substream);
	अगर ((status & ES_ADC) && ensoniq->capture_substream)
		snd_pcm_period_elapsed(ensoniq->capture_substream);
	अगर ((status & ES_DAC1) && ensoniq->playback1_substream)
		snd_pcm_period_elapsed(ensoniq->playback1_substream);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक snd_audiopci_probe(काष्ठा pci_dev *pci,
			      स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा ensoniq *ensoniq;
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

	अगर ((err = snd_ensoniq_create(card, pci, &ensoniq)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	card->निजी_data = ensoniq;

#अगर_घोषित CHIP1370
	अगर ((err = snd_ensoniq_1370_mixer(ensoniq)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CHIP1371
	अगर ((err = snd_ensoniq_1371_mixer(ensoniq, spdअगर[dev], lineio[dev])) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
#पूर्ण_अगर
	अगर ((err = snd_ensoniq_pcm(ensoniq, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_ensoniq_pcm2(ensoniq, 1)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	अगर ((err = snd_ensoniq_midi(ensoniq, 0)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	snd_ensoniq_create_gameport(ensoniq, dev);

	म_नकल(card->driver, DRIVER_NAME);

	म_नकल(card->लघुname, "Ensoniq AudioPCI");
	प्र_लिखो(card->दीर्घname, "%s %s at 0x%lx, irq %i",
		card->लघुname,
		card->driver,
		ensoniq->port,
		ensoniq->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_audiopci_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver ens137x_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_audiopci_ids,
	.probe = snd_audiopci_probe,
	.हटाओ = snd_audiopci_हटाओ,
	.driver = अणु
		.pm = SND_ENSONIQ_PM_OPS,
	पूर्ण,
पूर्ण;
	
module_pci_driver(ens137x_driver);
