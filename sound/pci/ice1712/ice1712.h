<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_ICE1712_H
#घोषणा __SOUND_ICE1712_H

/*
 *   ALSA driver क्रम ICEnsemble ICE1712 (Envy24)
 *
 *	Copyright (c) 2000 Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/पन.स>
#समावेश <sound/control.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/i2c.h>
#समावेश <sound/ak4xxx-adda.h>
#समावेश <sound/ak4114.h>
#समावेश <sound/pt2258.h>
#समावेश <sound/pcm.h>
#समावेश <sound/mpu401.h>


/*
 *  Direct रेजिस्टरs
 */

#घोषणा ICEREG(ice, x) ((ice)->port + ICE1712_REG_##x)

#घोषणा ICE1712_REG_CONTROL		0x00	/* byte */
#घोषणा   ICE1712_RESET			0x80	/* soft reset whole chip */
#घोषणा   ICE1712_SERR_ASSERT_DS_DMA	0x40    /* disabled SERR# निश्चितion क्रम the DS DMA Ch-C irq otherwise enabled */
#घोषणा   ICE1712_DOS_VOL		0x10    /* DOS WT/FM volume control */
#घोषणा   ICE1712_SERR_LEVEL		0x08	/* SERR# level otherwise edge */
#घोषणा   ICE1712_SERR_ASSERT_SB	0x02	/* disabled SERR# निश्चितion क्रम SB irq otherwise enabled */
#घोषणा   ICE1712_NATIVE		0x01	/* native mode otherwise SB */
#घोषणा ICE1712_REG_IRQMASK		0x01	/* byte */
#घोषणा   ICE1712_IRQ_MPU1		0x80	/* MIDI irq mask */
#घोषणा   ICE1712_IRQ_TIMER		0x40	/* Timer mask */
#घोषणा   ICE1712_IRQ_MPU2		0x20	/* Secondary MIDI irq mask */
#घोषणा   ICE1712_IRQ_PROPCM		0x10	/* professional multi-track */
#घोषणा   ICE1712_IRQ_FM		0x08	/* FM/MIDI - legacy */
#घोषणा   ICE1712_IRQ_PBKDS		0x04	/* playback DS channels */
#घोषणा   ICE1712_IRQ_CONCAP		0x02	/* consumer capture */
#घोषणा   ICE1712_IRQ_CONPBK		0x01	/* consumer playback */
#घोषणा ICE1712_REG_IRQSTAT		0x02	/* byte */
/* look to ICE1712_IRQ_* */
#घोषणा ICE1712_REG_INDEX		0x03	/* byte - indirect CCIxx regs */
#घोषणा ICE1712_REG_DATA		0x04	/* byte - indirect CCIxx regs */
#घोषणा ICE1712_REG_NMI_STAT1		0x05	/* byte */
#घोषणा ICE1712_REG_NMI_DATA		0x06	/* byte */
#घोषणा ICE1712_REG_NMI_INDEX		0x07	/* byte */
#घोषणा ICE1712_REG_AC97_INDEX		0x08	/* byte */
#घोषणा ICE1712_REG_AC97_CMD		0x09	/* byte */
#घोषणा   ICE1712_AC97_COLD		0x80	/* cold reset */
#घोषणा   ICE1712_AC97_WARM		0x40	/* warm reset */
#घोषणा   ICE1712_AC97_WRITE		0x20	/* W: ग_लिखो, R: ग_लिखो in progress */
#घोषणा   ICE1712_AC97_READ		0x10	/* W: पढ़ो, R: पढ़ो in progress */
#घोषणा   ICE1712_AC97_READY		0x08	/* codec पढ़ोy status bit */
#घोषणा   ICE1712_AC97_PBK_VSR		0x02	/* playback VSR */
#घोषणा   ICE1712_AC97_CAP_VSR		0x01	/* capture VSR */
#घोषणा ICE1712_REG_AC97_DATA		0x0a	/* word (little endian) */
#घोषणा ICE1712_REG_MPU1_CTRL		0x0c	/* byte */
#घोषणा ICE1712_REG_MPU1_DATA		0x0d	/* byte */
#घोषणा ICE1712_REG_I2C_DEV_ADDR	0x10	/* byte */
#घोषणा   ICE1712_I2C_WRITE		0x01	/* ग_लिखो direction */
#घोषणा ICE1712_REG_I2C_BYTE_ADDR	0x11	/* byte */
#घोषणा ICE1712_REG_I2C_DATA		0x12	/* byte */
#घोषणा ICE1712_REG_I2C_CTRL		0x13	/* byte */
#घोषणा   ICE1712_I2C_EEPROM		0x80	/* EEPROM exists */
#घोषणा   ICE1712_I2C_BUSY		0x01	/* busy bit */
#घोषणा ICE1712_REG_CONCAP_ADDR		0x14	/* dword - consumer capture */
#घोषणा ICE1712_REG_CONCAP_COUNT	0x18	/* word - current/base count */
#घोषणा ICE1712_REG_SERR_SHADOW		0x1b	/* byte */
#घोषणा ICE1712_REG_MPU2_CTRL		0x1c	/* byte */
#घोषणा ICE1712_REG_MPU2_DATA		0x1d	/* byte */
#घोषणा ICE1712_REG_TIMER		0x1e	/* word */

/*
 *  Indirect रेजिस्टरs
 */

#घोषणा ICE1712_IREG_PBK_COUNT_LO	0x00
#घोषणा ICE1712_IREG_PBK_COUNT_HI	0x01
#घोषणा ICE1712_IREG_PBK_CTRL		0x02
#घोषणा ICE1712_IREG_PBK_LEFT		0x03	/* left volume */
#घोषणा ICE1712_IREG_PBK_RIGHT		0x04	/* right volume */
#घोषणा ICE1712_IREG_PBK_SOFT		0x05	/* soft volume */
#घोषणा ICE1712_IREG_PBK_RATE_LO	0x06
#घोषणा ICE1712_IREG_PBK_RATE_MID	0x07
#घोषणा ICE1712_IREG_PBK_RATE_HI	0x08
#घोषणा ICE1712_IREG_CAP_COUNT_LO	0x10
#घोषणा ICE1712_IREG_CAP_COUNT_HI	0x11
#घोषणा ICE1712_IREG_CAP_CTRL		0x12
#घोषणा ICE1712_IREG_GPIO_DATA		0x20
#घोषणा ICE1712_IREG_GPIO_WRITE_MASK	0x21
#घोषणा ICE1712_IREG_GPIO_सूचीECTION	0x22
#घोषणा ICE1712_IREG_CONSUMER_POWERDOWN	0x30
#घोषणा ICE1712_IREG_PRO_POWERDOWN	0x31

/*
 *  Consumer section direct DMA रेजिस्टरs
 */

#घोषणा ICEDS(ice, x) ((ice)->dmapath_port + ICE1712_DS_##x)

#घोषणा ICE1712_DS_INTMASK		0x00	/* word - पूर्णांकerrupt mask */
#घोषणा ICE1712_DS_INTSTAT		0x02	/* word - पूर्णांकerrupt status */
#घोषणा ICE1712_DS_DATA			0x04	/* dword - channel data */
#घोषणा ICE1712_DS_INDEX		0x08	/* dword - channel index */

/*
 *  Consumer section channel रेजिस्टरs
 */

#घोषणा ICE1712_DSC_ADDR0		0x00	/* dword - base address 0 */
#घोषणा ICE1712_DSC_COUNT0		0x01	/* word - count 0 */
#घोषणा ICE1712_DSC_ADDR1		0x02	/* dword - base address 1 */
#घोषणा ICE1712_DSC_COUNT1		0x03	/* word - count 1 */
#घोषणा ICE1712_DSC_CONTROL		0x04	/* byte - control & status */
#घोषणा   ICE1712_BUFFER1		0x80	/* buffer1 is active */
#घोषणा   ICE1712_BUFFER1_AUTO		0x40	/* buffer1 स्वतः init */
#घोषणा   ICE1712_BUFFER0_AUTO		0x20	/* buffer0 स्वतः init */
#घोषणा   ICE1712_FLUSH			0x10	/* flush FIFO */
#घोषणा   ICE1712_STEREO		0x08	/* stereo */
#घोषणा   ICE1712_16BIT			0x04	/* 16-bit data */
#घोषणा   ICE1712_PAUSE			0x02	/* छोड़ो */
#घोषणा   ICE1712_START			0x01	/* start */
#घोषणा ICE1712_DSC_RATE		0x05	/* dword - rate */
#घोषणा ICE1712_DSC_VOLUME		0x06	/* word - volume control */

/*
 *  Professional multi-track direct control रेजिस्टरs
 */

#घोषणा ICEMT(ice, x) ((ice)->profi_port + ICE1712_MT_##x)

#घोषणा ICE1712_MT_IRQ			0x00	/* byte - पूर्णांकerrupt mask */
#घोषणा   ICE1712_MULTI_CAPTURE		0x80	/* capture IRQ */
#घोषणा   ICE1712_MULTI_PLAYBACK	0x40	/* playback IRQ */
#घोषणा   ICE1712_MULTI_CAPSTATUS	0x02	/* capture IRQ status */
#घोषणा   ICE1712_MULTI_PBKSTATUS	0x01	/* playback IRQ status */
#घोषणा ICE1712_MT_RATE			0x01	/* byte - sampling rate select */
#घोषणा   ICE1712_SPDIF_MASTER		0x10	/* S/PDIF input is master घड़ी */
#घोषणा ICE1712_MT_I2S_FORMAT		0x02	/* byte - I2S data क्रमmat */
#घोषणा ICE1712_MT_AC97_INDEX		0x04	/* byte - AC'97 index */
#घोषणा ICE1712_MT_AC97_CMD		0x05	/* byte - AC'97 command & status */
/* look to ICE1712_AC97_* */
#घोषणा ICE1712_MT_AC97_DATA		0x06	/* word - AC'97 data */
#घोषणा ICE1712_MT_PLAYBACK_ADDR	0x10	/* dword - playback address */
#घोषणा ICE1712_MT_PLAYBACK_SIZE	0x14	/* word - playback size */
#घोषणा ICE1712_MT_PLAYBACK_COUNT	0x16	/* word - playback count */
#घोषणा ICE1712_MT_PLAYBACK_CONTROL	0x18	/* byte - control */
#घोषणा   ICE1712_CAPTURE_START_SHADOW	0x04	/* capture start */
#घोषणा   ICE1712_PLAYBACK_PAUSE	0x02	/* playback छोड़ो */
#घोषणा   ICE1712_PLAYBACK_START	0x01	/* playback start */
#घोषणा ICE1712_MT_CAPTURE_ADDR		0x20	/* dword - capture address */
#घोषणा ICE1712_MT_CAPTURE_SIZE		0x24	/* word - capture size */
#घोषणा ICE1712_MT_CAPTURE_COUNT	0x26	/* word - capture count */
#घोषणा ICE1712_MT_CAPTURE_CONTROL	0x28	/* byte - control */
#घोषणा   ICE1712_CAPTURE_START		0x01	/* capture start */
#घोषणा ICE1712_MT_ROUTE_PSDOUT03	0x30	/* word */
#घोषणा ICE1712_MT_ROUTE_SPDOUT		0x32	/* word */
#घोषणा ICE1712_MT_ROUTE_CAPTURE	0x34	/* dword */
#घोषणा ICE1712_MT_MONITOR_VOLUME	0x38	/* word */
#घोषणा ICE1712_MT_MONITOR_INDEX	0x3a	/* byte */
#घोषणा ICE1712_MT_MONITOR_RATE		0x3b	/* byte */
#घोषणा ICE1712_MT_MONITOR_ROUTECTRL	0x3c	/* byte */
#घोषणा   ICE1712_ROUTE_AC97		0x01	/* route digital mixer output to AC'97 */
#घोषणा ICE1712_MT_MONITOR_PEAKINDEX	0x3e	/* byte */
#घोषणा ICE1712_MT_MONITOR_PEAKDATA	0x3f	/* byte */

/*
 *  Codec configuration bits
 */

/* PCI[60] System Configuration */
#घोषणा ICE1712_CFG_CLOCK	0xc0
#घोषणा   ICE1712_CFG_CLOCK512	0x00	/* 22.5692Mhz, 44.1kHz*512 */
#घोषणा   ICE1712_CFG_CLOCK384  0x40	/* 16.9344Mhz, 44.1kHz*384 */
#घोषणा   ICE1712_CFG_EXT	0x80	/* बाह्यal घड़ी */
#घोषणा ICE1712_CFG_2xMPU401	0x20	/* two MPU401 UARTs */
#घोषणा ICE1712_CFG_NO_CON_AC97 0x10	/* consumer AC'97 codec is not present */
#घोषणा ICE1712_CFG_ADC_MASK	0x0c	/* one, two, three, four stereo ADCs */
#घोषणा ICE1712_CFG_DAC_MASK	0x03	/* one, two, three, four stereo DACs */
/* PCI[61] AC-Link Configuration */
#घोषणा ICE1712_CFG_PRO_I2S	0x80	/* multitrack converter: I2S or AC'97 */
#घोषणा ICE1712_CFG_AC97_PACKED	0x01	/* split or packed mode - AC'97 */
/* PCI[62] I2S Features */
#घोषणा ICE1712_CFG_I2S_VOLUME	0x80	/* volume/mute capability */
#घोषणा ICE1712_CFG_I2S_96KHZ	0x40	/* supports 96kHz sampling */
#घोषणा ICE1712_CFG_I2S_RESMASK	0x30	/* resolution mask, 16,18,20,24-bit */
#घोषणा ICE1712_CFG_I2S_OTHER	0x0f	/* other I2S IDs */
/* PCI[63] S/PDIF Configuration */
#घोषणा ICE1712_CFG_I2S_CHIPID	0xfc	/* I2S chip ID */
#घोषणा ICE1712_CFG_SPDIF_IN	0x02	/* S/PDIF input is present */
#घोषणा ICE1712_CFG_SPDIF_OUT	0x01	/* S/PDIF output is present */

/*
 * DMA mode values
 * identical with DMA_XXX on i386 architecture.
 */
#घोषणा ICE1712_DMA_MODE_WRITE		0x48
#घोषणा ICE1712_DMA_AUTOINIT		0x10


/*
 * I2C EEPROM Address
 */
#घोषणा ICE_I2C_EEPROM_ADDR		0xA0

काष्ठा snd_ice1712;

काष्ठा snd_ice1712_eeprom अणु
	अचिन्हित पूर्णांक subvenकरोr;	/* PCI[2c-2f] */
	अचिन्हित अक्षर size;	/* size of EEPROM image in bytes */
	अचिन्हित अक्षर version;	/* must be 1 (or 2 क्रम vt1724) */
	अचिन्हित अक्षर data[32];
	अचिन्हित पूर्णांक gpiomask;
	अचिन्हित पूर्णांक gpiostate;
	अचिन्हित पूर्णांक gpiodir;
पूर्ण;

क्रमागत अणु
	ICE_EEP1_CODEC = 0,	/* 06 */
	ICE_EEP1_ACLINK,	/* 07 */
	ICE_EEP1_I2SID,		/* 08 */
	ICE_EEP1_SPDIF,		/* 09 */
	ICE_EEP1_GPIO_MASK,	/* 0a */
	ICE_EEP1_GPIO_STATE,	/* 0b */
	ICE_EEP1_GPIO_सूची,	/* 0c */
	ICE_EEP1_AC97_MAIN_LO,	/* 0d */
	ICE_EEP1_AC97_MAIN_HI,	/* 0e */
	ICE_EEP1_AC97_PCM_LO,	/* 0f */
	ICE_EEP1_AC97_PCM_HI,	/* 10 */
	ICE_EEP1_AC97_REC_LO,	/* 11 */
	ICE_EEP1_AC97_REC_HI,	/* 12 */
	ICE_EEP1_AC97_RECSRC,	/* 13 */
	ICE_EEP1_DAC_ID,	/* 14 */
	ICE_EEP1_DAC_ID1,
	ICE_EEP1_DAC_ID2,
	ICE_EEP1_DAC_ID3,
	ICE_EEP1_ADC_ID,	/* 18 */
	ICE_EEP1_ADC_ID1,
	ICE_EEP1_ADC_ID2,
	ICE_EEP1_ADC_ID3
पूर्ण;

#घोषणा ice_has_con_ac97(ice)	(!((ice)->eeprom.data[ICE_EEP1_CODEC] & ICE1712_CFG_NO_CON_AC97))


काष्ठा snd_ak4xxx_निजी अणु
	अचिन्हित पूर्णांक cअगर:1;		/* CIF mode */
	अचिन्हित अक्षर caddr;		/* C0 and C1 bits */
	अचिन्हित पूर्णांक data_mask;		/* DATA gpio bit */
	अचिन्हित पूर्णांक clk_mask;		/* CLK gpio bit */
	अचिन्हित पूर्णांक cs_mask;		/* bit mask क्रम select/deselect address */
	अचिन्हित पूर्णांक cs_addr;		/* bits to select address */
	अचिन्हित पूर्णांक cs_none;		/* bits to deselect address */
	अचिन्हित पूर्णांक add_flags;		/* additional bits at init */
	अचिन्हित पूर्णांक mask_flags;	/* total mask bits */
	काष्ठा snd_akm4xxx_ops अणु
		व्योम (*set_rate_val)(काष्ठा snd_akm4xxx *ak, अचिन्हित पूर्णांक rate);
	पूर्ण ops;
पूर्ण;

काष्ठा snd_ice1712_spdअगर अणु
	अचिन्हित अक्षर cs8403_bits;
	अचिन्हित अक्षर cs8403_stream_bits;
	काष्ठा snd_kcontrol *stream_ctl;

	काष्ठा snd_ice1712_spdअगर_ops अणु
		व्योम (*खोलो)(काष्ठा snd_ice1712 *, काष्ठा snd_pcm_substream *);
		व्योम (*setup_rate)(काष्ठा snd_ice1712 *, पूर्णांक rate);
		व्योम (*बंद)(काष्ठा snd_ice1712 *, काष्ठा snd_pcm_substream *);
		व्योम (*शेष_get)(काष्ठा snd_ice1712 *, काष्ठा snd_ctl_elem_value *ucontrol);
		पूर्णांक (*शेष_put)(काष्ठा snd_ice1712 *, काष्ठा snd_ctl_elem_value *ucontrol);
		व्योम (*stream_get)(काष्ठा snd_ice1712 *, काष्ठा snd_ctl_elem_value *ucontrol);
		पूर्णांक (*stream_put)(काष्ठा snd_ice1712 *, काष्ठा snd_ctl_elem_value *ucontrol);
	पूर्ण ops;
पूर्ण;

काष्ठा snd_ice1712_card_info;

काष्ठा snd_ice1712 अणु
	अचिन्हित दीर्घ conp_dma_size;
	अचिन्हित दीर्घ conc_dma_size;
	अचिन्हित दीर्घ prop_dma_size;
	अचिन्हित दीर्घ proc_dma_size;
	पूर्णांक irq;

	अचिन्हित दीर्घ port;
	अचिन्हित दीर्घ ddma_port;
	अचिन्हित दीर्घ dmapath_port;
	अचिन्हित दीर्घ profi_port;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm *pcm_ds;
	काष्ठा snd_pcm *pcm_pro;
	काष्ठा snd_pcm_substream *playback_con_substream;
	काष्ठा snd_pcm_substream *playback_con_substream_ds[6];
	काष्ठा snd_pcm_substream *capture_con_substream;
	काष्ठा snd_pcm_substream *playback_pro_substream;
	काष्ठा snd_pcm_substream *capture_pro_substream;
	अचिन्हित पूर्णांक playback_pro_size;
	अचिन्हित पूर्णांक capture_pro_size;
	अचिन्हित पूर्णांक playback_con_virt_addr[6];
	अचिन्हित पूर्णांक playback_con_active_buf[6];
	अचिन्हित पूर्णांक capture_con_virt_addr;
	अचिन्हित पूर्णांक ac97_ext_id;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_rawmidi *rmidi[2];

	spinlock_t reg_lock;
	काष्ठा snd_info_entry *proc_entry;

	काष्ठा snd_ice1712_eeprom eeprom;
	स्थिर काष्ठा snd_ice1712_card_info *card_info;

	अचिन्हित पूर्णांक pro_volumes[20];
	अचिन्हित पूर्णांक omni:1;		/* Delta Omni I/O */
	अचिन्हित पूर्णांक dxr_enable:1;	/* Terratec DXR enable क्रम DMX6FIRE */
	अचिन्हित पूर्णांक vt1724:1;
	अचिन्हित पूर्णांक vt1720:1;
	अचिन्हित पूर्णांक has_spdअगर:1;	/* VT1720/4 - has SPDIF I/O */
	अचिन्हित पूर्णांक क्रमce_pdma4:1;	/* VT1720/4 - PDMA4 as non-spdअगर */
	अचिन्हित पूर्णांक क्रमce_rdma1:1;	/* VT1720/4 - RDMA1 as non-spdअगर */
	अचिन्हित पूर्णांक midi_output:1;	/* VT1720/4: MIDI output triggered */
	अचिन्हित पूर्णांक midi_input:1;	/* VT1720/4: MIDI input triggered */
	अचिन्हित पूर्णांक own_routing:1;	/* VT1720/4: use own routing ctls */
	अचिन्हित पूर्णांक num_total_dacs;	/* total DACs */
	अचिन्हित पूर्णांक num_total_adcs;	/* total ADCs */
	अचिन्हित पूर्णांक cur_rate;		/* current rate */

	काष्ठा mutex खोलो_mutex;
	काष्ठा snd_pcm_substream *pcm_reserved[4];
	स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *hw_rates; /* card-specअगरic rate स्थिरraपूर्णांकs */

	अचिन्हित पूर्णांक akm_codecs;
	काष्ठा snd_akm4xxx *akm;
	काष्ठा snd_ice1712_spdअगर spdअगर;

	काष्ठा mutex i2c_mutex;	/* I2C mutex क्रम ICE1724 रेजिस्टरs */
	काष्ठा snd_i2c_bus *i2c;		/* I2C bus */
	काष्ठा snd_i2c_device *cs8427;	/* CS8427 I2C device */
	अचिन्हित पूर्णांक cs8427_समयout;	/* CS8427 reset समयout in HZ/100 */

	काष्ठा ice1712_gpio अणु
		अचिन्हित पूर्णांक direction;		/* current direction bits */
		अचिन्हित पूर्णांक ग_लिखो_mask;	/* current mask bits */
		अचिन्हित पूर्णांक saved[2];		/* क्रम ewx_i2c */
		/* चालकs */
		व्योम (*set_mask)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data);
		अचिन्हित पूर्णांक (*get_mask)(काष्ठा snd_ice1712 *ice);
		व्योम (*set_dir)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data);
		अचिन्हित पूर्णांक (*get_dir)(काष्ठा snd_ice1712 *ice);
		व्योम (*set_data)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक data);
		अचिन्हित पूर्णांक (*get_data)(काष्ठा snd_ice1712 *ice);
		/* misc चालकs - move to another place? */
		व्योम (*set_pro_rate)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate);
		व्योम (*i2s_mclk_changed)(काष्ठा snd_ice1712 *ice);
	पूर्ण gpio;
	काष्ठा mutex gpio_mutex;

	/* other board-specअगरic data */
	व्योम *spec;

	/* VT172x specअगरic */
	पूर्णांक pro_rate_शेष;
	पूर्णांक (*is_spdअगर_master)(काष्ठा snd_ice1712 *ice);
	अचिन्हित पूर्णांक (*get_rate)(काष्ठा snd_ice1712 *ice);
	व्योम (*set_rate)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate);
	अचिन्हित अक्षर (*set_mclk)(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक rate);
	पूर्णांक (*set_spdअगर_घड़ी)(काष्ठा snd_ice1712 *ice, पूर्णांक type);
	पूर्णांक (*get_spdअगर_master_type)(काष्ठा snd_ice1712 *ice);
	स्थिर अक्षर * स्थिर *ext_घड़ी_names;
	पूर्णांक ext_घड़ी_count;
	व्योम (*pro_खोलो)(काष्ठा snd_ice1712 *, काष्ठा snd_pcm_substream *);
#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक (*pm_suspend)(काष्ठा snd_ice1712 *);
	पूर्णांक (*pm_resume)(काष्ठा snd_ice1712 *);
	अचिन्हित पूर्णांक pm_suspend_enabled:1;
	अचिन्हित पूर्णांक pm_saved_is_spdअगर_master:1;
	अचिन्हित पूर्णांक pm_saved_spdअगर_ctrl;
	अचिन्हित अक्षर pm_saved_spdअगर_cfg;
	अचिन्हित पूर्णांक pm_saved_route;
#पूर्ण_अगर
पूर्ण;


/*
 * gpio access functions
 */
अटल अंतरभूत व्योम snd_ice1712_gpio_set_dir(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक bits)
अणु
	ice->gpio.set_dir(ice, bits);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_ice1712_gpio_get_dir(काष्ठा snd_ice1712 *ice)
अणु
	वापस ice->gpio.get_dir(ice);
पूर्ण

अटल अंतरभूत व्योम snd_ice1712_gpio_set_mask(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक bits)
अणु
	ice->gpio.set_mask(ice, bits);
पूर्ण

अटल अंतरभूत व्योम snd_ice1712_gpio_ग_लिखो(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val)
अणु
	ice->gpio.set_data(ice, val);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक snd_ice1712_gpio_पढ़ो(काष्ठा snd_ice1712 *ice)
अणु
	वापस ice->gpio.get_data(ice);
पूर्ण

/*
 * save and restore gpio status
 * The access to gpio will be रक्षित by mutex, so करोn't क्रमget to
 * restore!
 */
अटल अंतरभूत व्योम snd_ice1712_save_gpio_status(काष्ठा snd_ice1712 *ice)
अणु
	mutex_lock(&ice->gpio_mutex);
	ice->gpio.saved[0] = ice->gpio.direction;
	ice->gpio.saved[1] = ice->gpio.ग_लिखो_mask;
पूर्ण

अटल अंतरभूत व्योम snd_ice1712_restore_gpio_status(काष्ठा snd_ice1712 *ice)
अणु
	ice->gpio.set_dir(ice, ice->gpio.saved[0]);
	ice->gpio.set_mask(ice, ice->gpio.saved[1]);
	ice->gpio.direction = ice->gpio.saved[0];
	ice->gpio.ग_लिखो_mask = ice->gpio.saved[1];
	mutex_unlock(&ice->gpio_mutex);
पूर्ण

/* क्रम bit controls */
#घोषणा ICE1712_GPIO(xअगरace, xname, xindex, mask, invert, xaccess) \
अणु .अगरace = xअगरace, .name = xname, .access = xaccess, .info = snd_ctl_boolean_mono_info, \
  .get = snd_ice1712_gpio_get, .put = snd_ice1712_gpio_put, \
  .निजी_value = mask | (invert << 24) पूर्ण

पूर्णांक snd_ice1712_gpio_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_ice1712_gpio_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol);

/*
 * set gpio direction, ग_लिखो mask and data
 */
अटल अंतरभूत व्योम snd_ice1712_gpio_ग_लिखो_bits(काष्ठा snd_ice1712 *ice,
					       अचिन्हित पूर्णांक mask, अचिन्हित पूर्णांक bits)
अणु
	अचिन्हित val;

	ice->gpio.direction |= mask;
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	val = snd_ice1712_gpio_पढ़ो(ice);
	val &= ~mask;
	val |= mask & bits;
	snd_ice1712_gpio_ग_लिखो(ice, val);
पूर्ण

अटल अंतरभूत पूर्णांक snd_ice1712_gpio_पढ़ो_bits(काष्ठा snd_ice1712 *ice,
					      अचिन्हित पूर्णांक mask)
अणु
	ice->gpio.direction &= ~mask;
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	वापस  snd_ice1712_gpio_पढ़ो(ice) & mask;
पूर्ण

/* route access functions */
पूर्णांक snd_ice1724_get_route_val(काष्ठा snd_ice1712 *ice, पूर्णांक shअगरt);
पूर्णांक snd_ice1724_put_route_val(काष्ठा snd_ice1712 *ice, अचिन्हित पूर्णांक val,
								पूर्णांक shअगरt);

पूर्णांक snd_ice1712_spdअगर_build_controls(काष्ठा snd_ice1712 *ice);

पूर्णांक snd_ice1712_akm4xxx_init(काष्ठा snd_akm4xxx *ak,
			     स्थिर काष्ठा snd_akm4xxx *ढाँचा,
			     स्थिर काष्ठा snd_ak4xxx_निजी *priv,
			     काष्ठा snd_ice1712 *ice);
व्योम snd_ice1712_akm4xxx_मुक्त(काष्ठा snd_ice1712 *ice);
पूर्णांक snd_ice1712_akm4xxx_build_controls(काष्ठा snd_ice1712 *ice);

पूर्णांक snd_ice1712_init_cs8427(काष्ठा snd_ice1712 *ice, पूर्णांक addr);

अटल अंतरभूत व्योम snd_ice1712_ग_लिखो(काष्ठा snd_ice1712 *ice, u8 addr, u8 data)
अणु
	outb(addr, ICEREG(ice, INDEX));
	outb(data, ICEREG(ice, DATA));
पूर्ण

अटल अंतरभूत u8 snd_ice1712_पढ़ो(काष्ठा snd_ice1712 *ice, u8 addr)
अणु
	outb(addr, ICEREG(ice, INDEX));
	वापस inb(ICEREG(ice, DATA));
पूर्ण


/*
 * entry poपूर्णांकer
 */

काष्ठा snd_ice1712_card_info अणु
	अचिन्हित पूर्णांक subvenकरोr;
	स्थिर अक्षर *name;
	स्थिर अक्षर *model;
	स्थिर अक्षर *driver;
	पूर्णांक (*chip_init)(काष्ठा snd_ice1712 *);
	व्योम (*chip_निकास)(काष्ठा snd_ice1712 *);
	पूर्णांक (*build_controls)(काष्ठा snd_ice1712 *);
	अचिन्हित पूर्णांक no_mpu401:1;
	अचिन्हित पूर्णांक mpu401_1_info_flags;
	अचिन्हित पूर्णांक mpu401_2_info_flags;
	स्थिर अक्षर *mpu401_1_name;
	स्थिर अक्षर *mpu401_2_name;
	स्थिर अचिन्हित पूर्णांक eeprom_size;
	स्थिर अचिन्हित अक्षर *eeprom_data;
पूर्ण;


#पूर्ण_अगर /* __SOUND_ICE1712_H */
