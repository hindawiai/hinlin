<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_VT1724_H
#घोषणा __SOUND_VT1724_H

/*
 *   ALSA driver क्रम ICEnsemble VT1724 (Envy24)
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */      

#समावेश <sound/control.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/i2c.h>
#समावेश <sound/pcm.h>

#समावेश "ice1712.h"

क्रमागत अणु
	ICE_EEP2_SYSCONF = 0,	/* 06 */
	ICE_EEP2_ACLINK,	/* 07 */
	ICE_EEP2_I2S,		/* 08 */
	ICE_EEP2_SPDIF,		/* 09 */
	ICE_EEP2_GPIO_सूची,	/* 0a */
	ICE_EEP2_GPIO_सूची1,	/* 0b */
	ICE_EEP2_GPIO_सूची2,	/* 0c */
	ICE_EEP2_GPIO_MASK,	/* 0d */
	ICE_EEP2_GPIO_MASK1,	/* 0e */
	ICE_EEP2_GPIO_MASK2,	/* 0f */
	ICE_EEP2_GPIO_STATE,	/* 10 */
	ICE_EEP2_GPIO_STATE1,	/* 11 */
	ICE_EEP2_GPIO_STATE2	/* 12 */
पूर्ण;
	
/*
 *  Direct रेजिस्टरs
 */

#घोषणा ICEREG1724(ice, x) ((ice)->port + VT1724_REG_##x)

#घोषणा VT1724_REG_CONTROL		0x00	/* byte */
#घोषणा   VT1724_RESET			0x80	/* reset whole chip */
#घोषणा VT1724_REG_IRQMASK		0x01	/* byte */
#घोषणा   VT1724_IRQ_MPU_RX		0x80
#घोषणा   VT1724_IRQ_MPU_TX		0x20
#घोषणा   VT1724_IRQ_MTPCM		0x10
#घोषणा VT1724_REG_IRQSTAT		0x02	/* byte */
/* look to VT1724_IRQ_* */
#घोषणा VT1724_REG_SYS_CFG		0x04	/* byte - प्रणाली configuration PCI60 on Envy24*/
#घोषणा   VT1724_CFG_CLOCK	0xc0
#घोषणा     VT1724_CFG_CLOCK512	0x00	/* 22.5692Mhz, 44.1kHz*512 */
#घोषणा     VT1724_CFG_CLOCK384  0x40	/* 16.9344Mhz, 44.1kHz*384 */
#घोषणा   VT1724_CFG_MPU401	0x20		/* MPU401 UARTs */
#घोषणा   VT1724_CFG_ADC_MASK	0x0c	/* one, two or one and S/PDIF, stereo ADCs */
#घोषणा   VT1724_CFG_ADC_NONE	0x0c	/* no ADCs */
#घोषणा   VT1724_CFG_DAC_MASK	0x03	/* one, two, three, four stereo DACs */

#घोषणा VT1724_REG_AC97_CFG		0x05	/* byte */
#घोषणा   VT1724_CFG_PRO_I2S	0x80	/* multitrack converter: I2S or AC'97 */
#घोषणा   VT1724_CFG_AC97_PACKED	0x01	/* split or packed mode - AC'97 */

#घोषणा VT1724_REG_I2S_FEATURES		0x06	/* byte */
#घोषणा   VT1724_CFG_I2S_VOLUME	0x80	/* volume/mute capability */
#घोषणा   VT1724_CFG_I2S_96KHZ	0x40	/* supports 96kHz sampling */
#घोषणा   VT1724_CFG_I2S_RESMASK	0x30	/* resolution mask, 16,18,20,24-bit */
#घोषणा   VT1724_CFG_I2S_192KHZ	0x08	/* supports 192kHz sampling */
#घोषणा   VT1724_CFG_I2S_OTHER	0x07	/* other I2S IDs */

#घोषणा VT1724_REG_SPDIF_CFG		0x07	/* byte */
#घोषणा   VT1724_CFG_SPDIF_OUT_EN	0x80	/*Internal S/PDIF output is enabled*/
#घोषणा   VT1724_CFG_SPDIF_OUT_INT	0x40	/*Internal S/PDIF output is implemented*/
#घोषणा   VT1724_CFG_I2S_CHIPID	0x3c	/* I2S chip ID */
#घोषणा   VT1724_CFG_SPDIF_IN	0x02	/* S/PDIF input is present */
#घोषणा   VT1724_CFG_SPDIF_OUT	0x01	/* External S/PDIF output is present */

/*there is no consumer AC97 codec with the VT1724*/
//#घोषणा VT1724_REG_AC97_INDEX		0x08	/* byte */
//#घोषणा VT1724_REG_AC97_CMD		0x09	/* byte */

#घोषणा VT1724_REG_MPU_TXFIFO		0x0a	/*byte ro. number of bytes in TX fअगरo*/
#घोषणा VT1724_REG_MPU_RXFIFO		0x0b	/*byte ro. number of bytes in RX fअगरo*/

#घोषणा VT1724_REG_MPU_DATA		0x0c	/* byte */
#घोषणा VT1724_REG_MPU_CTRL		0x0d	/* byte */
#घोषणा   VT1724_MPU_UART	0x01
#घोषणा   VT1724_MPU_TX_EMPTY	0x02
#घोषणा   VT1724_MPU_TX_FULL	0x04
#घोषणा   VT1724_MPU_RX_EMPTY	0x08
#घोषणा   VT1724_MPU_RX_FULL	0x10

#घोषणा VT1724_REG_MPU_FIFO_WM	0x0e	/*byte set the high/low watermarks क्रम RX/TX fअगरos*/
#घोषणा   VT1724_MPU_RX_FIFO	0x20	//1=rx fअगरo watermark 0=tx fअगरo watermark
#घोषणा   VT1724_MPU_FIFO_MASK	0x1f	

#घोषणा VT1724_REG_I2C_DEV_ADDR	0x10	/* byte */
#घोषणा   VT1724_I2C_WRITE		0x01	/* ग_लिखो direction */
#घोषणा VT1724_REG_I2C_BYTE_ADDR	0x11	/* byte */
#घोषणा VT1724_REG_I2C_DATA		0x12	/* byte */
#घोषणा VT1724_REG_I2C_CTRL		0x13	/* byte */
#घोषणा   VT1724_I2C_EEPROM		0x80	/* 1 = EEPROM exists */
#घोषणा   VT1724_I2C_BUSY		0x01	/* busy bit */

#घोषणा VT1724_REG_GPIO_DATA	0x14	/* word */
#घोषणा VT1724_REG_GPIO_WRITE_MASK	0x16 /* word */
#घोषणा VT1724_REG_GPIO_सूचीECTION	0x18 /* dword? (3 bytes) 0=input 1=output. 
						bit3 - during reset used क्रम Eeprom घातer-on strapping
						अगर TESTEN# pin active, bit 2 always input*/
#घोषणा VT1724_REG_POWERDOWN	0x1c
#घोषणा VT1724_REG_GPIO_DATA_22	0x1e /* byte direction क्रम GPIO 16:22 */
#घोषणा VT1724_REG_GPIO_WRITE_MASK_22	0x1f /* byte ग_लिखो mask क्रम GPIO 16:22 */


/* 
 *  Professional multi-track direct control रेजिस्टरs
 */

#घोषणा ICEMT1724(ice, x) ((ice)->profi_port + VT1724_MT_##x)

#घोषणा VT1724_MT_IRQ			0x00	/* byte - पूर्णांकerrupt mask */
#घोषणा   VT1724_MULTI_PDMA4	0x80	/* SPDIF Out / PDMA4 */
#घोषणा	  VT1724_MULTI_PDMA3	0x40	/* PDMA3 */
#घोषणा   VT1724_MULTI_PDMA2	0x20	/* PDMA2 */
#घोषणा   VT1724_MULTI_PDMA1	0x10	/* PDMA1 */
#घोषणा   VT1724_MULTI_FIFO_ERR 0x08	/* DMA FIFO underrun/overrun. */
#घोषणा   VT1724_MULTI_RDMA1	0x04	/* RDMA1 (S/PDIF input) */
#घोषणा   VT1724_MULTI_RDMA0	0x02	/* RMDA0 */
#घोषणा   VT1724_MULTI_PDMA0	0x01	/* MC Interleave/PDMA0 */

#घोषणा VT1724_MT_RATE			0x01	/* byte - sampling rate select */
#घोषणा   VT1724_SPDIF_MASTER		0x10	/* S/PDIF input is master घड़ी */
#घोषणा VT1724_MT_I2S_FORMAT		0x02	/* byte - I2S data क्रमmat */
#घोषणा   VT1724_MT_I2S_MCLK_128X	0x08
#घोषणा   VT1724_MT_I2S_FORMAT_MASK	0x03
#घोषणा   VT1724_MT_I2S_FORMAT_I2S	0x00
#घोषणा VT1724_MT_DMA_INT_MASK		0x03	/* byte -DMA Interrupt Mask */
/* lool to VT1724_MULTI_* */
#घोषणा VT1724_MT_AC97_INDEX		0x04	/* byte - AC'97 index */
#घोषणा VT1724_MT_AC97_CMD		0x05	/* byte - AC'97 command & status */
#घोषणा   VT1724_AC97_COLD	0x80	/* cold reset */
#घोषणा   VT1724_AC97_WARM	0x40	/* warm reset */
#घोषणा   VT1724_AC97_WRITE	0x20	/* W: ग_लिखो, R: ग_लिखो in progress */
#घोषणा   VT1724_AC97_READ	0x10	/* W: पढ़ो, R: पढ़ो in progress */
#घोषणा   VT1724_AC97_READY	0x08	/* codec पढ़ोy status bit */
#घोषणा   VT1724_AC97_ID_MASK	0x03	/* codec id mask */
#घोषणा VT1724_MT_AC97_DATA		0x06	/* word - AC'97 data */
#घोषणा VT1724_MT_PLAYBACK_ADDR		0x10	/* dword - playback address */
#घोषणा VT1724_MT_PLAYBACK_SIZE		0x14	/* dword - playback size */
#घोषणा VT1724_MT_DMA_CONTROL		0x18	/* byte - control */
#घोषणा   VT1724_PDMA4_START	0x80	/* SPDIF out / PDMA4 start */
#घोषणा   VT1724_PDMA3_START	0x40	/* PDMA3 start */
#घोषणा   VT1724_PDMA2_START	0x20	/* PDMA2 start */
#घोषणा   VT1724_PDMA1_START	0x10	/* PDMA1 start */
#घोषणा   VT1724_RDMA1_START	0x04	/* RDMA1 start */
#घोषणा   VT1724_RDMA0_START	0x02	/* RMDA0 start */
#घोषणा   VT1724_PDMA0_START	0x01	/* MC Interleave / PDMA0 start */
#घोषणा VT1724_MT_BURST			0x19	/* Interleaved playback DMA Active streams / PCI burst size */
#घोषणा VT1724_MT_DMA_FIFO_ERR		0x1a	/*Global playback and record DMA FIFO Underrun/Overrun */
#घोषणा   VT1724_PDMA4_UNDERRUN		0x80
#घोषणा   VT1724_PDMA2_UNDERRUN		0x40
#घोषणा   VT1724_PDMA3_UNDERRUN		0x20
#घोषणा   VT1724_PDMA1_UNDERRUN		0x10
#घोषणा   VT1724_RDMA1_UNDERRUN		0x04
#घोषणा   VT1724_RDMA0_UNDERRUN		0x02
#घोषणा   VT1724_PDMA0_UNDERRUN		0x01
#घोषणा VT1724_MT_DMA_PAUSE		0x1b	/*Global playback and record DMA FIFO छोड़ो/resume */
#घोषणा	  VT1724_PDMA4_PAUSE	0x80
#घोषणा	  VT1724_PDMA3_PAUSE	0x40
#घोषणा	  VT1724_PDMA2_PAUSE	0x20
#घोषणा	  VT1724_PDMA1_PAUSE	0x10
#घोषणा	  VT1724_RDMA1_PAUSE	0x04
#घोषणा	  VT1724_RDMA0_PAUSE	0x02
#घोषणा	  VT1724_PDMA0_PAUSE	0x01
#घोषणा VT1724_MT_PLAYBACK_COUNT	0x1c	/* word - playback count */
#घोषणा VT1724_MT_CAPTURE_ADDR		0x20	/* dword - capture address */
#घोषणा VT1724_MT_CAPTURE_SIZE		0x24	/* word - capture size */
#घोषणा VT1724_MT_CAPTURE_COUNT		0x26	/* word - capture count */

#घोषणा VT1724_MT_ROUTE_PLAYBACK	0x2c	/* word */

#घोषणा VT1724_MT_RDMA1_ADDR		0x30	/* dword - RDMA1 capture address */
#घोषणा VT1724_MT_RDMA1_SIZE		0x34	/* word - RDMA1 capture size */
#घोषणा VT1724_MT_RDMA1_COUNT		0x36	/* word - RDMA1 capture count */

#घोषणा VT1724_MT_SPDIF_CTRL		0x3c	/* word */
#घोषणा VT1724_MT_MONITOR_PEAKINDEX	0x3e	/* byte */
#घोषणा VT1724_MT_MONITOR_PEAKDATA	0x3f	/* byte */

/* concurrent stereo channels */
#घोषणा VT1724_MT_PDMA4_ADDR		0x40	/* dword */
#घोषणा VT1724_MT_PDMA4_SIZE		0x44	/* word */
#घोषणा VT1724_MT_PDMA4_COUNT		0x46	/* word */
#घोषणा VT1724_MT_PDMA3_ADDR		0x50	/* dword */
#घोषणा VT1724_MT_PDMA3_SIZE		0x54	/* word */
#घोषणा VT1724_MT_PDMA3_COUNT		0x56	/* word */
#घोषणा VT1724_MT_PDMA2_ADDR		0x60	/* dword */
#घोषणा VT1724_MT_PDMA2_SIZE		0x64	/* word */
#घोषणा VT1724_MT_PDMA2_COUNT		0x66	/* word */
#घोषणा VT1724_MT_PDMA1_ADDR		0x70	/* dword */
#घोषणा VT1724_MT_PDMA1_SIZE		0x74	/* word */
#घोषणा VT1724_MT_PDMA1_COUNT		0x76	/* word */


अचिन्हित अक्षर snd_vt1724_पढ़ो_i2c(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर dev, अचिन्हित अक्षर addr);
व्योम snd_vt1724_ग_लिखो_i2c(काष्ठा snd_ice1712 *ice, अचिन्हित अक्षर dev, अचिन्हित अक्षर addr, अचिन्हित अक्षर data);

#पूर्ण_अगर /* __SOUND_VT1724_H */
