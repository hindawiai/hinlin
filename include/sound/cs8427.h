<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_CS8427_H
#घोषणा __SOUND_CS8427_H

/*
 *  Routines क्रम Cirrus Logic CS8427
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 */

#समावेश <sound/i2c.h>

#घोषणा CS8427_BASE_ADDR	0x10	/* base I2C address */

#घोषणा CS8427_REG_AUTOINC	0x80	/* flag - स्वतःincrement */
#घोषणा CS8427_REG_CONTROL1	0x01
#घोषणा CS8427_REG_CONTROL2	0x02
#घोषणा CS8427_REG_DATAFLOW	0x03
#घोषणा CS8427_REG_CLOCKSOURCE	0x04
#घोषणा CS8427_REG_SERIALINPUT	0x05
#घोषणा CS8427_REG_SERIALOUTPUT	0x06
#घोषणा CS8427_REG_INT1STATUS	0x07
#घोषणा CS8427_REG_INT2STATUS	0x08
#घोषणा CS8427_REG_INT1MASK	0x09
#घोषणा CS8427_REG_INT1MODEMSB	0x0a
#घोषणा CS8427_REG_INT1MODELSB	0x0b
#घोषणा CS8427_REG_INT2MASK	0x0c
#घोषणा CS8427_REG_INT2MODEMSB	0x0d
#घोषणा CS8427_REG_INT2MODELSB	0x0e
#घोषणा CS8427_REG_RECVCSDATA	0x0f
#घोषणा CS8427_REG_RECVERRORS	0x10
#घोषणा CS8427_REG_RECVERRMASK	0x11
#घोषणा CS8427_REG_CSDATABUF	0x12
#घोषणा CS8427_REG_UDATABUF	0x13
#घोषणा CS8427_REG_QSUBCODE	0x14	/* 0x14-0x1d (10 bytes) */
#घोषणा CS8427_REG_OMCKRMCKRATIO 0x1e
#घोषणा CS8427_REG_CORU_DATABUF	0x20	/* 24 byte buffer area */
#घोषणा CS8427_REG_ID_AND_VER	0x7f

/* CS8427_REG_CONTROL1 bits */
#घोषणा CS8427_SWCLK		(1<<7)	/* 0 = RMCK शेष, 1 = OMCK output on RMCK pin */
#घोषणा CS8427_VSET		(1<<6)	/* 0 = valid PCM data, 1 = invalid PCM data */
#घोषणा CS8427_MUTESAO		(1<<5)	/* mute control क्रम the serial audio output port, 0 = disabled, 1 = enabled */
#घोषणा CS8427_MUTEAES		(1<<4)	/* mute control क्रम the AES transmitter output, 0 = disabled, 1 = enabled */
#घोषणा CS8427_INTMASK		(3<<1)	/* पूर्णांकerrupt output pin setup mask */
#घोषणा CS8427_INTACTHIGH	(0<<1)	/* active high */
#घोषणा CS8427_INTACTLOW	(1<<1)	/* active low */
#घोषणा CS8427_INTOPENDRAIN	(2<<1)	/* खोलो drain, active low */
#घोषणा CS8427_TCBLसूची		(1<<0)	/* 0 = TCBL is an input, 1 = TCBL is an output */

/* CS8427_REQ_CONTROL2 bits */
#घोषणा CS8427_HOLDMASK		(3<<5)	/* action when a receiver error occurs */
#घोषणा CS8427_HOLDLASTSAMPLE	(0<<5)	/* hold the last valid sample */
#घोषणा CS8427_HOLDZERO		(1<<5)	/* replace the current audio sample with zero (mute) */
#घोषणा CS8427_HOLDNOCHANGE	(2<<5)	/* करो not change the received audio sample */
#घोषणा CS8427_RMCKF		(1<<4)	/* 0 = 256*Fsi, 1 = 128*Fsi */
#घोषणा CS8427_MMR		(1<<3)	/* AES3 receiver operation, 0 = stereo, 1 = mono */
#घोषणा CS8427_MMT		(1<<2)	/* AES3 transmitter operation, 0 = stereo, 1 = mono */
#घोषणा CS8427_MMTCS		(1<<1)	/* 0 = use A + B CS data, 1 = use MMTLR CS data */
#घोषणा CS8427_MMTLR		(1<<0)	/* 0 = use A CS data, 1 = use B CS data */

/* CS8427_REG_DATAFLOW */
#घोषणा CS8427_TXOFF		(1<<6)	/* AES3 transmitter Output, 0 = normal operation, 1 = off (0V) */
#घोषणा CS8427_AESBP		(1<<5)	/* AES3 hardware bypass mode, 0 = normal, 1 = bypass (RX->TX) */
#घोषणा CS8427_TXDMASK		(3<<3)	/* AES3 Transmitter Data Source Mask */
#घोषणा CS8427_TXDSERIAL	(1<<3)	/* TXD - serial audio input port */
#घोषणा CS8427_TXAES3DRECEIVER	(2<<3)	/* TXD - AES3 receiver */
#घोषणा CS8427_SPDMASK		(3<<1)	/* Serial Audio Output Port Data Source Mask */
#घोषणा CS8427_SPDSERIAL	(1<<1)	/* SPD - serial audio input port */
#घोषणा CS8427_SPDAES3RECEIVER	(2<<1)	/* SPD - AES3 receiver */

/* CS8427_REG_CLOCKSOURCE */
#घोषणा CS8427_RUN		(1<<6)	/* 0 = घड़ी off, 1 = घड़ी on */
#घोषणा CS8427_CLKMASK		(3<<4)	/* OMCK frequency mask */
#घोषणा CS8427_CLK256		(0<<4)	/* 256*Fso */
#घोषणा CS8427_CLK384		(1<<4)	/* 384*Fso */
#घोषणा CS8427_CLK512		(2<<4)	/* 512*Fso */
#घोषणा CS8427_OUTC		(1<<3)	/* Output Time Base, 0 = OMCK, 1 = recovered input घड़ी */
#घोषणा CS8427_INC		(1<<2)	/* Input Time Base Clock Source, 0 = recoverd input घड़ी, 1 = OMCK input pin */
#घोषणा CS8427_RXDMASK		(3<<0)	/* Recovered Input Clock Source Mask */
#घोषणा CS8427_RXDILRCK		(0<<0)	/* 256*Fsi from ILRCK pin */
#घोषणा CS8427_RXDAES3INPUT	(1<<0)	/* 256*Fsi from AES3 input */
#घोषणा CS8427_EXTCLOCKRESET	(2<<0)	/* bypass PLL, 256*Fsi घड़ी, synchronous reset */
#घोषणा CS8427_EXTCLOCK		(3<<0)	/* bypass PLL, 256*Fsi घड़ी */

/* CS8427_REG_SERIALINPUT */
#घोषणा CS8427_SIMS		(1<<7)	/* 0 = slave, 1 = master mode */
#घोषणा CS8427_SISF		(1<<6)	/* ISCLK freq, 0 = 64*Fsi, 1 = 128*Fsi */
#घोषणा CS8427_SIRESMASK	(3<<4)	/* Resolution of the input data क्रम right justअगरied क्रमmats */
#घोषणा CS8427_SIRES24		(0<<4)	/* SIRES 24-bit */
#घोषणा CS8427_SIRES20		(1<<4)	/* SIRES 20-bit */
#घोषणा CS8427_SIRES16		(2<<4)	/* SIRES 16-bit */
#घोषणा CS8427_SIJUST		(1<<3)	/* Justअगरication of SDIN data relative to ILRCK, 0 = left-justअगरied, 1 = right-justअगरied */
#घोषणा CS8427_SIDEL		(1<<2)	/* Delay of SDIN data relative to ILRCK क्रम left-justअगरied data क्रमmats, 0 = first ISCLK period, 1 = second ISCLK period */
#घोषणा CS8427_SISPOL		(1<<1)	/* ICLK घड़ी polarity, 0 = rising edge of ISCLK, 1 = falling edge of ISCLK */
#घोषणा CS8427_SILRPOL		(1<<0)	/* ILRCK घड़ी polarity, 0 = SDIN data left channel when ILRCK is high, 1 = SDIN right when ILRCK is high */

/* CS8427_REG_SERIALOUTPUT */
#घोषणा CS8427_SOMS		(1<<7)	/* 0 = slave, 1 = master mode */
#घोषणा CS8427_SOSF		(1<<6)	/* OSCLK freq, 0 = 64*Fso, 1 = 128*Fso */
#घोषणा CS8427_SORESMASK	(3<<4)	/* Resolution of the output data on SDOUT and AES3 output */
#घोषणा CS8427_SORES24		(0<<4)	/* SIRES 24-bit */
#घोषणा CS8427_SORES20		(1<<4)	/* SIRES 20-bit */
#घोषणा CS8427_SORES16		(2<<4)	/* SIRES 16-bit */
#घोषणा CS8427_SORESसूचीECT	(2<<4)	/* SIRES direct copy from AES3 receiver */
#घोषणा CS8427_SOJUST		(1<<3)	/* Justअगरication of SDOUT data relative to OLRCK, 0 = left-justअगरied, 1 = right-justअगरied */
#घोषणा CS8427_SODEL		(1<<2)	/* Delay of SDOUT data relative to OLRCK क्रम left-justअगरied data क्रमmats, 0 = first OSCLK period, 1 = second OSCLK period */
#घोषणा CS8427_SOSPOL		(1<<1)	/* OSCLK घड़ी polarity, 0 = rising edge of ISCLK, 1 = falling edge of ISCLK */
#घोषणा CS8427_SOLRPOL		(1<<0)	/* OLRCK घड़ी polarity, 0 = SDOUT data left channel when OLRCK is high, 1 = SDOUT right when OLRCK is high */

/* CS8427_REG_INT1STATUS */
#घोषणा CS8427_TSLIP		(1<<7)	/* AES3 transmitter source data slip पूर्णांकerrupt */
#घोषणा CS8427_OSLIP		(1<<6)	/* Serial audio output port data slip पूर्णांकerrupt */
#घोषणा CS8427_DETC		(1<<2)	/* D to E C-buffer transfer पूर्णांकerrupt */
#घोषणा CS8427_EFTC		(1<<1)	/* E to F C-buffer transfer पूर्णांकerrupt */
#घोषणा CS8427_RERR		(1<<0)	/* A receiver error has occurred */

/* CS8427_REG_INT2STATUS */
#घोषणा CS8427_DETU		(1<<3)	/* D to E U-buffer transfer पूर्णांकerrupt */
#घोषणा CS8427_EFTU		(1<<2)	/* E to F U-buffer transfer पूर्णांकerrupt */
#घोषणा CS8427_QCH		(1<<1)	/* A new block of Q-subcode data is available क्रम पढ़ोing */

/* CS8427_REG_INT1MODEMSB && CS8427_REG_INT1MODELSB */
/* bits are defined in CS8427_REG_INT1STATUS */
/* CS8427_REG_INT2MODEMSB && CS8427_REG_INT2MODELSB */
/* bits are defined in CS8427_REG_INT2STATUS */
#घोषणा CS8427_INTMODERISINGMSB	0
#घोषणा CS8427_INTMODERESINGLSB	0
#घोषणा CS8427_INTMODEFALLINGMSB 0
#घोषणा CS8427_INTMODEFALLINGLSB 1
#घोषणा CS8427_INTMODELEVELMSB	1
#घोषणा CS8427_INTMODELEVELLSB	0

/* CS8427_REG_RECVCSDATA */
#घोषणा CS8427_AUXMASK		(15<<4)	/* auxiliary data field width */
#घोषणा CS8427_AUXSHIFT		4
#घोषणा CS8427_PRO		(1<<3)	/* Channel status block क्रमmat indicator */
#घोषणा CS8427_AUDIO		(1<<2)	/* Audio indicator (0 = audio, 1 = nonaudio */
#घोषणा CS8427_COPY		(1<<1)	/* 0 = copyright निश्चितed, 1 = copyright not निश्चितed */
#घोषणा CS8427_ORIG		(1<<0)	/* SCMS generation indicator, 0 = 1st generation or highter, 1 = original */

/* CS8427_REG_RECVERRORS */
/* CS8427_REG_RECVERRMASK क्रम CS8427_RERR */
#घोषणा CS8427_QCRC		(1<<6)	/* Q-subcode data CRC error indicator */
#घोषणा CS8427_CCRC		(1<<5)	/* Chancnel Status Block Cyclick Redundancy Check Bit */
#घोषणा CS8427_UNLOCK		(1<<4)	/* PLL lock status bit */
#घोषणा CS8427_V		(1<<3)	/* 0 = valid data */
#घोषणा CS8427_CONF		(1<<2)	/* Confidence bit */
#घोषणा CS8427_BIP		(1<<1)	/* Bi-phase error bit */
#घोषणा CS8427_PAR		(1<<0)	/* Parity error */

/* CS8427_REG_CSDATABUF	*/
#घोषणा CS8427_BSEL		(1<<5)	/* 0 = CS data, 1 = U data */
#घोषणा CS8427_CBMR		(1<<4)	/* 0 = overग_लिखो first 5 bytes क्रम CS D to E buffer, 1 = prevent */
#घोषणा CS8427_DETCI		(1<<3)	/* D to E CS data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
#घोषणा CS8427_EFTCI		(1<<2)	/* E to F CS data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
#घोषणा CS8427_CAM		(1<<1)	/* CS data buffer control port access mode bit, 0 = one byte, 1 = two byte */
#घोषणा CS8427_CHS		(1<<0)	/* Channel select bit, 0 = Channel A, 1 = Channel B */

/* CS8427_REG_UDATABUF */
#घोषणा CS8427_UD		(1<<4)	/* User data pin (U) direction, 0 = input, 1 = output */
#घोषणा CS8427_UBMMASK		(3<<2)	/* Operating mode of the AES3 U bit manager */
#घोषणा CS8427_UBMZEROS		(0<<2)	/* transmit all zeros mode */
#घोषणा CS8427_UBMBLOCK		(1<<2)	/* block mode */
#घोषणा CS8427_DETUI		(1<<1)	/* D to E U-data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */
#घोषणा CS8427_EFTUI		(1<<1)	/* E to F U-data buffer transfer inhibit bit, 0 = allow, 1 = inhibit */

/* CS8427_REG_ID_AND_VER */
#घोषणा CS8427_IDMASK		(15<<4)
#घोषणा CS8427_IDSHIFT		4
#घोषणा CS8427_VERMASK		(15<<0)
#घोषणा CS8427_VERSHIFT		0
#घोषणा CS8427_VER8427A		0x71

काष्ठा snd_pcm_substream;

पूर्णांक snd_cs8427_init(काष्ठा snd_i2c_bus *bus, काष्ठा snd_i2c_device *device);
पूर्णांक snd_cs8427_create(काष्ठा snd_i2c_bus *bus, अचिन्हित अक्षर addr,
		      अचिन्हित पूर्णांक reset_समयout, काष्ठा snd_i2c_device **r_cs8427);
पूर्णांक snd_cs8427_reg_ग_लिखो(काष्ठा snd_i2c_device *device, अचिन्हित अक्षर reg,
			 अचिन्हित अक्षर val);
पूर्णांक snd_cs8427_iec958_build(काष्ठा snd_i2c_device *cs8427,
			    काष्ठा snd_pcm_substream *playback_substream,
			    काष्ठा snd_pcm_substream *capture_substream);
पूर्णांक snd_cs8427_iec958_active(काष्ठा snd_i2c_device *cs8427, पूर्णांक active);
पूर्णांक snd_cs8427_iec958_pcm(काष्ठा snd_i2c_device *cs8427, अचिन्हित पूर्णांक rate);

#पूर्ण_अगर /* __SOUND_CS8427_H */
