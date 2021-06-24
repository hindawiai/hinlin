<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SOUND_CS5535AUDIO_H
#घोषणा __SOUND_CS5535AUDIO_H

#घोषणा cs_ग_लिखोl(cs5535au, reg, val)	outl(val, (cs5535au)->port + reg)
#घोषणा cs_ग_लिखोb(cs5535au, reg, val)	outb(val, (cs5535au)->port + reg)
#घोषणा cs_पढ़ोl(cs5535au, reg)		inl((cs5535au)->port + reg)
#घोषणा cs_पढ़ोw(cs5535au, reg)		inw((cs5535au)->port + reg)
#घोषणा cs_पढ़ोb(cs5535au, reg)		inb((cs5535au)->port + reg)

#घोषणा CS5535AUDIO_MAX_DESCRIPTORS	128

/* acc_codec bar0 reg addrs */
#घोषणा ACC_GPIO_STATUS			0x00
#घोषणा ACC_CODEC_STATUS		0x08
#घोषणा ACC_CODEC_CNTL			0x0C
#घोषणा ACC_IRQ_STATUS			0x12
#घोषणा ACC_BM0_CMD			0x20
#घोषणा ACC_BM1_CMD			0x28
#घोषणा ACC_BM0_PRD			0x24
#घोषणा ACC_BM1_PRD			0x2C
#घोषणा ACC_BM0_STATUS			0x21
#घोषणा ACC_BM1_STATUS			0x29
#घोषणा ACC_BM0_PNTR			0x60
#घोषणा ACC_BM1_PNTR			0x64

/* acc_codec bar0 reg bits */
/* ACC_IRQ_STATUS */
#घोषणा IRQ_STS 			0
#घोषणा WU_IRQ_STS 			1
#घोषणा BM0_IRQ_STS 			2
#घोषणा BM1_IRQ_STS 			3
/* ACC_BMX_STATUS */
#घोषणा EOP				(1<<0)
#घोषणा BM_EOP_ERR			(1<<1)
/* ACC_BMX_CTL */
#घोषणा BM_CTL_EN			0x01
#घोषणा BM_CTL_PAUSE			0x03
#घोषणा BM_CTL_DIS			0x00
#घोषणा BM_CTL_BYTE_ORD_LE		0x00
#घोषणा BM_CTL_BYTE_ORD_BE		0x04
/* cs5535 specअगरic ac97 codec रेजिस्टर defines */
#घोषणा CMD_MASK			0xFF00FFFF
#घोषणा CMD_NEW				0x00010000
#घोषणा STS_NEW				0x00020000
#घोषणा PRM_RDY_STS			0x00800000
#घोषणा ACC_CODEC_CNTL_WR_CMD		(~0x80000000)
#घोषणा ACC_CODEC_CNTL_RD_CMD		0x80000000
#घोषणा ACC_CODEC_CNTL_LNK_SHUTDOWN	0x00040000
#घोषणा ACC_CODEC_CNTL_LNK_WRM_RST	0x00020000
#घोषणा PRD_JMP				0x2000
#घोषणा PRD_EOP				0x4000
#घोषणा PRD_EOT				0x8000

क्रमागत अणु CS5535AUDIO_DMA_PLAYBACK, CS5535AUDIO_DMA_CAPTURE, NUM_CS5535AUDIO_DMAS पूर्ण;

काष्ठा cs5535audio;

काष्ठा cs5535audio_dma_ops अणु
	पूर्णांक type;
	व्योम (*enable_dma)(काष्ठा cs5535audio *cs5535au);
	व्योम (*disable_dma)(काष्ठा cs5535audio *cs5535au);
	व्योम (*छोड़ो_dma)(काष्ठा cs5535audio *cs5535au);
	व्योम (*setup_prd)(काष्ठा cs5535audio *cs5535au, u32 prd_addr);
	u32 (*पढ़ो_prd)(काष्ठा cs5535audio *cs5535au);
	u32 (*पढ़ो_dma_pntr)(काष्ठा cs5535audio *cs5535au);
पूर्ण;

काष्ठा cs5535audio_dma_desc अणु
	__le32 addr;
	__le16 size;
	__le16 ctlreserved;
पूर्ण;

काष्ठा cs5535audio_dma अणु
	स्थिर काष्ठा cs5535audio_dma_ops *ops;
	काष्ठा snd_dma_buffer desc_buf;
	काष्ठा snd_pcm_substream *substream;
	अचिन्हित पूर्णांक buf_addr, buf_bytes;
	अचिन्हित पूर्णांक period_bytes, periods;
	u32 saved_prd;
	पूर्णांक pcm_खोलो_flag;
पूर्ण;

काष्ठा cs5535audio अणु
	काष्ठा snd_card *card;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_pcm *pcm;
	पूर्णांक irq;
	काष्ठा pci_dev *pci;
	अचिन्हित दीर्घ port;
	spinlock_t reg_lock;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	काष्ठा cs5535audio_dma dmas[NUM_CS5535AUDIO_DMAS];
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops snd_cs5535audio_pm;

#अगर_घोषित CONFIG_OLPC
व्योम olpc_prequirks(काष्ठा snd_card *card,
		    काष्ठा snd_ac97_ढाँचा *ac97);
पूर्णांक olpc_quirks(काष्ठा snd_card *card, काष्ठा snd_ac97 *ac97);
व्योम olpc_quirks_cleanup(व्योम);
व्योम olpc_analog_input(काष्ठा snd_ac97 *ac97, पूर्णांक on);
व्योम olpc_mic_bias(काष्ठा snd_ac97 *ac97, पूर्णांक on);

अटल अंतरभूत व्योम olpc_capture_खोलो(काष्ठा snd_ac97 *ac97)
अणु
	/* शेष to Analog Input off */
	olpc_analog_input(ac97, 0);
	/* enable MIC Bias क्रम recording */
	olpc_mic_bias(ac97, 1);
पूर्ण

अटल अंतरभूत व्योम olpc_capture_बंद(काष्ठा snd_ac97 *ac97)
अणु
	/* disable Analog Input */
	olpc_analog_input(ac97, 0);
	/* disable the MIC Bias (so the recording LED turns off) */
	olpc_mic_bias(ac97, 0);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम olpc_prequirks(काष्ठा snd_card *card,
		काष्ठा snd_ac97_ढाँचा *ac97) अणु पूर्ण
अटल अंतरभूत पूर्णांक olpc_quirks(काष्ठा snd_card *card, काष्ठा snd_ac97 *ac97)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम olpc_quirks_cleanup(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम olpc_analog_input(काष्ठा snd_ac97 *ac97, पूर्णांक on) अणु पूर्ण
अटल अंतरभूत व्योम olpc_mic_bias(काष्ठा snd_ac97 *ac97, पूर्णांक on) अणु पूर्ण
अटल अंतरभूत व्योम olpc_capture_खोलो(काष्ठा snd_ac97 *ac97) अणु पूर्ण
अटल अंतरभूत व्योम olpc_capture_बंद(काष्ठा snd_ac97 *ac97) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक snd_cs5535audio_pcm(काष्ठा cs5535audio *cs5535audio);

#पूर्ण_अगर /* __SOUND_CS5535AUDIO_H */

