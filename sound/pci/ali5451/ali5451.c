<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Matt Wu <Matt_Wu@acersoftech.com.cn>
 *  Apr 26, 2001
 *  Routines क्रम control of ALi pci audio M5451
 *
 *  BUGS:
 *    --
 *
 *  TODO:
 *    --
 */

#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/info.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Matt Wu <Matt_Wu@acersoftech.com.cn>");
MODULE_DESCRIPTION("ALI M5451");
MODULE_LICENSE("GPL");

अटल पूर्णांक index = SNDRV_DEFAULT_IDX1;	/* Index */
अटल अक्षर *id = SNDRV_DEFAULT_STR1;	/* ID क्रम this card */
अटल पूर्णांक pcm_channels = 32;
अटल bool spdअगर;

module_param(index, पूर्णांक, 0444);
MODULE_PARM_DESC(index, "Index value for ALI M5451 PCI Audio.");
module_param(id, अक्षरp, 0444);
MODULE_PARM_DESC(id, "ID string for ALI M5451 PCI Audio.");
module_param(pcm_channels, पूर्णांक, 0444);
MODULE_PARM_DESC(pcm_channels, "PCM Channels");
module_param(spdअगर, bool, 0444);
MODULE_PARM_DESC(spdअगर, "Support SPDIF I/O");

/* just क्रम backward compatibility */
अटल bool enable;
module_param(enable, bool, 0444);


/*
 *  Constants definition
 */

#घोषणा DEVICE_ID_ALI5451	((PCI_VENDOR_ID_AL<<16)|PCI_DEVICE_ID_AL_M5451)


#घोषणा ALI_CHANNELS		32

#घोषणा ALI_PCM_IN_CHANNEL	31
#घोषणा ALI_SPDIF_IN_CHANNEL	19
#घोषणा ALI_SPDIF_OUT_CHANNEL	15
#घोषणा ALI_CENTER_CHANNEL	24
#घोषणा ALI_LEF_CHANNEL		23
#घोषणा ALI_SURR_LEFT_CHANNEL	26
#घोषणा ALI_SURR_RIGHT_CHANNEL	25
#घोषणा ALI_MODEM_IN_CHANNEL    21
#घोषणा ALI_MODEM_OUT_CHANNEL   20

#घोषणा	SNDRV_ALI_VOICE_TYPE_PCM	01
#घोषणा SNDRV_ALI_VOICE_TYPE_OTH	02

#घोषणा	ALI_5451_V02		0x02

/*
 *  Direct Registers
 */

#घोषणा ALI_LEGACY_DMAR0        0x00  /* ADR0 */
#घोषणा ALI_LEGACY_DMAR4        0x04  /* CNT0 */
#घोषणा ALI_LEGACY_DMAR11       0x0b  /* MOD  */
#घोषणा ALI_LEGACY_DMAR15       0x0f  /* MMR  */
#घोषणा ALI_MPUR0		0x20
#घोषणा ALI_MPUR1		0x21
#घोषणा ALI_MPUR2		0x22
#घोषणा ALI_MPUR3		0x23

#घोषणा	ALI_AC97_WRITE		0x40
#घोषणा ALI_AC97_READ		0x44

#घोषणा ALI_SCTRL		0x48
#घोषणा   ALI_SPDIF_OUT_ENABLE		0x20
#घोषणा   ALI_SCTRL_LINE_IN2		(1 << 9)
#घोषणा   ALI_SCTRL_GPIO_IN2		(1 << 13)
#घोषणा   ALI_SCTRL_LINE_OUT_EN 	(1 << 20)
#घोषणा   ALI_SCTRL_GPIO_OUT_EN 	(1 << 23)
#घोषणा   ALI_SCTRL_CODEC1_READY	(1 << 24)
#घोषणा   ALI_SCTRL_CODEC2_READY	(1 << 25)
#घोषणा ALI_AC97_GPIO		0x4c
#घोषणा   ALI_AC97_GPIO_ENABLE		0x8000
#घोषणा   ALI_AC97_GPIO_DATA_SHIFT	16
#घोषणा ALI_SPDIF_CS		0x70
#घोषणा ALI_SPDIF_CTRL		0x74
#घोषणा   ALI_SPDIF_IN_FUNC_ENABLE	0x02
#घोषणा   ALI_SPDIF_IN_CH_STATUS	0x40
#घोषणा   ALI_SPDIF_OUT_CH_STATUS	0xbf
#घोषणा ALI_START		0x80
#घोषणा ALI_STOP		0x84
#घोषणा ALI_CSPF		0x90
#घोषणा ALI_AINT		0x98
#घोषणा ALI_GC_CIR		0xa0
	#घोषणा ENDLP_IE		0x00001000
	#घोषणा MIDLP_IE		0x00002000
#घोषणा ALI_AINTEN		0xa4
#घोषणा ALI_VOLUME		0xa8
#घोषणा ALI_SBDELTA_DELTA_R     0xac
#घोषणा ALI_MISCINT		0xb0
	#घोषणा ADDRESS_IRQ		0x00000020
	#घोषणा TARGET_REACHED		0x00008000
	#घोषणा MIXER_OVERFLOW		0x00000800
	#घोषणा MIXER_UNDERFLOW		0x00000400
	#घोषणा GPIO_IRQ		0x01000000
#घोषणा ALI_SBBL_SBCL           0xc0
#घोषणा ALI_SBCTRL_SBE2R_SBDD   0xc4
#घोषणा ALI_STIMER		0xc8
#घोषणा ALI_GLOBAL_CONTROL	0xd4
#घोषणा   ALI_SPDIF_OUT_SEL_PCM		0x00000400 /* bit 10 */
#घोषणा   ALI_SPDIF_IN_SUPPORT		0x00000800 /* bit 11 */
#घोषणा   ALI_SPDIF_OUT_CH_ENABLE	0x00008000 /* bit 15 */
#घोषणा   ALI_SPDIF_IN_CH_ENABLE	0x00080000 /* bit 19 */
#घोषणा   ALI_PCM_IN_ENABLE		0x80000000 /* bit 31 */

#घोषणा ALI_CSO_ALPHA_FMS	0xe0
#घोषणा ALI_LBA			0xe4
#घोषणा ALI_ESO_DELTA		0xe8
#घोषणा ALI_GVSEL_PAN_VOC_CTRL_EC	0xf0
#घोषणा ALI_EBUF1		0xf4
#घोषणा ALI_EBUF2		0xf8

#घोषणा ALI_REG(codec, x) ((codec)->port + x)

#घोषणा MAX_CODECS 2


काष्ठा snd_ali;
काष्ठा snd_ali_voice;

काष्ठा snd_ali_channel_control अणु
	/* रेजिस्टर data */
	काष्ठा REGDATA अणु
		अचिन्हित पूर्णांक start;
		अचिन्हित पूर्णांक stop;
		अचिन्हित पूर्णांक aपूर्णांक;
		अचिन्हित पूर्णांक aपूर्णांकen;
	पूर्ण data;
		
	/* रेजिस्टर addresses */
	काष्ठा REGS अणु
		अचिन्हित पूर्णांक start;
		अचिन्हित पूर्णांक stop;
		अचिन्हित पूर्णांक aपूर्णांक;
		अचिन्हित पूर्णांक aपूर्णांकen;
		अचिन्हित पूर्णांक ac97पढ़ो;
		अचिन्हित पूर्णांक ac97ग_लिखो;
	पूर्ण regs;

पूर्ण;

काष्ठा snd_ali_voice अणु
	अचिन्हित पूर्णांक number;
	अचिन्हित पूर्णांक use :1,
		pcm :1,
		midi :1,
		mode :1,
		synth :1,
		running :1;

	/* PCM data */
	काष्ठा snd_ali *codec;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_ali_voice *extra;
	
	पूर्णांक eso;                /* final ESO value क्रम channel */
	पूर्णांक count;              /* runसमय->period_size */

	/* --- */

	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(व्योम *निजी_data);
पूर्ण;


काष्ठा snd_alidev अणु

	काष्ठा snd_ali_voice voices[ALI_CHANNELS];	

	अचिन्हित पूर्णांक	chcnt;			/* num of खोलोed channels */
	अचिन्हित पूर्णांक	chmap;			/* biपंचांगap क्रम खोलोed channels */
	अचिन्हित पूर्णांक synthcount;

पूर्ण;


#घोषणा ALI_GLOBAL_REGS		56
#घोषणा ALI_CHANNEL_REGS	8
काष्ठा snd_ali_image अणु
	u32 regs[ALI_GLOBAL_REGS];
	u32 channel_regs[ALI_CHANNELS][ALI_CHANNEL_REGS];
पूर्ण;


काष्ठा snd_ali अणु
	पूर्णांक		irq;
	अचिन्हित दीर्घ	port;
	अचिन्हित अक्षर	revision;

	अचिन्हित पूर्णांक hw_initialized :1;
	अचिन्हित पूर्णांक spdअगर_support :1;

	काष्ठा pci_dev	*pci;
	काष्ठा pci_dev	*pci_m1533;
	काष्ठा pci_dev	*pci_m7101;

	काष्ठा snd_card	*card;
	काष्ठा snd_pcm	*pcm[MAX_CODECS];
	काष्ठा snd_alidev	synth;
	काष्ठा snd_ali_channel_control chregs;

	/* S/PDIF Mask */
	अचिन्हित पूर्णांक	spdअगर_mask;

	अचिन्हित पूर्णांक spurious_irq_count;
	अचिन्हित पूर्णांक spurious_irq_max_delta;

	अचिन्हित पूर्णांक num_of_codecs;

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97[MAX_CODECS];
	अचिन्हित लघु	ac97_ext_id;
	अचिन्हित लघु	ac97_ext_status;

	spinlock_t	reg_lock;
	spinlock_t	voice_alloc;

#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा snd_ali_image *image;
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_ali_ids[] = अणु
	अणुPCI_DEVICE(PCI_VENDOR_ID_AL, PCI_DEVICE_ID_AL_M5451), 0, 0, 0पूर्ण,
	अणु0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, snd_ali_ids);

अटल व्योम snd_ali_clear_voices(काष्ठा snd_ali *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
अटल अचिन्हित लघु snd_ali_codec_peek(काष्ठा snd_ali *, पूर्णांक, अचिन्हित लघु);
अटल व्योम snd_ali_codec_poke(काष्ठा snd_ali *, पूर्णांक, अचिन्हित लघु,
			       अचिन्हित लघु);

/*
 *  AC97 ACCESS
 */

अटल अंतरभूत अचिन्हित पूर्णांक snd_ali_5451_peek(काष्ठा snd_ali *codec,
					     अचिन्हित पूर्णांक port)
अणु
	वापस (अचिन्हित पूर्णांक)inl(ALI_REG(codec, port)); 
पूर्ण

अटल अंतरभूत व्योम snd_ali_5451_poke(काष्ठा snd_ali *codec,
				     अचिन्हित पूर्णांक port,
				     अचिन्हित पूर्णांक val)
अणु
	outl((अचिन्हित पूर्णांक)val, ALI_REG(codec, port));
पूर्ण

अटल पूर्णांक snd_ali_codec_पढ़ोy(काष्ठा snd_ali *codec,
			       अचिन्हित पूर्णांक port)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित पूर्णांक res;
	
	end_समय = jअगरfies + msecs_to_jअगरfies(250);

	क्रम (;;) अणु
		res = snd_ali_5451_peek(codec,port);
		अगर (!(res & 0x8000))
			वापस 0;
		अगर (!समय_after_eq(end_समय, jअगरfies))
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	snd_ali_5451_poke(codec, port, res & ~0x8000);
	dev_dbg(codec->card->dev, "ali_codec_ready: codec is not ready.\n ");
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_ali_sसमयr_पढ़ोy(काष्ठा snd_ali *codec)
अणु
	अचिन्हित दीर्घ end_समय;
	अचिन्हित दीर्घ dwChk1,dwChk2;
	
	dwChk1 = snd_ali_5451_peek(codec, ALI_STIMER);
	end_समय = jअगरfies + msecs_to_jअगरfies(250);

	क्रम (;;) अणु
		dwChk2 = snd_ali_5451_peek(codec, ALI_STIMER);
		अगर (dwChk2 != dwChk1)
			वापस 0;
		अगर (!समय_after_eq(end_समय, jअगरfies))
			अवरोध;
		schedule_समयout_unपूर्णांकerruptible(1);
	पूर्ण

	dev_err(codec->card->dev, "ali_stimer_read: stimer is not ready.\n");
	वापस -EIO;
पूर्ण

अटल व्योम snd_ali_codec_poke(काष्ठा snd_ali *codec,पूर्णांक secondary,
			       अचिन्हित लघु reg,
			       अचिन्हित लघु val)
अणु
	अचिन्हित पूर्णांक dwVal;
	अचिन्हित पूर्णांक port;

	अगर (reg >= 0x80) अणु
		dev_err(codec->card->dev,
			"ali_codec_poke: reg(%xh) invalid.\n", reg);
		वापस;
	पूर्ण

	port = codec->chregs.regs.ac97ग_लिखो;

	अगर (snd_ali_codec_पढ़ोy(codec, port) < 0)
		वापस;
	अगर (snd_ali_sसमयr_पढ़ोy(codec) < 0)
		वापस;

	dwVal  = (अचिन्हित पूर्णांक) (reg & 0xff);
	dwVal |= 0x8000 | (val << 16);
	अगर (secondary)
		dwVal |= 0x0080;
	अगर (codec->revision == ALI_5451_V02)
		dwVal |= 0x0100;

	snd_ali_5451_poke(codec, port, dwVal);

	वापस ;
पूर्ण

अटल अचिन्हित लघु snd_ali_codec_peek(काष्ठा snd_ali *codec,
					 पूर्णांक secondary,
					 अचिन्हित लघु reg)
अणु
	अचिन्हित पूर्णांक dwVal;
	अचिन्हित पूर्णांक port;

	अगर (reg >= 0x80) अणु
		dev_err(codec->card->dev,
			"ali_codec_peek: reg(%xh) invalid.\n", reg);
		वापस ~0;
	पूर्ण

	port = codec->chregs.regs.ac97पढ़ो;

	अगर (snd_ali_codec_पढ़ोy(codec, port) < 0)
		वापस ~0;
	अगर (snd_ali_sसमयr_पढ़ोy(codec) < 0)
		वापस ~0;

	dwVal  = (अचिन्हित पूर्णांक) (reg & 0xff);
	dwVal |= 0x8000;				/* bit 15*/
	अगर (secondary)
		dwVal |= 0x0080;

	snd_ali_5451_poke(codec, port, dwVal);

	अगर (snd_ali_sसमयr_पढ़ोy(codec) < 0)
		वापस ~0;
	अगर (snd_ali_codec_पढ़ोy(codec, port) < 0)
		वापस ~0;
	
	वापस (snd_ali_5451_peek(codec, port) & 0xffff0000) >> 16;
पूर्ण

अटल व्योम snd_ali_codec_ग_लिखो(काष्ठा snd_ac97 *ac97,
				अचिन्हित लघु reg,
				अचिन्हित लघु val )
अणु
	काष्ठा snd_ali *codec = ac97->निजी_data;

	dev_dbg(codec->card->dev, "codec_write: reg=%xh data=%xh.\n", reg, val);
	अगर (reg == AC97_GPIO_STATUS) अणु
		outl((val << ALI_AC97_GPIO_DATA_SHIFT) | ALI_AC97_GPIO_ENABLE,
		     ALI_REG(codec, ALI_AC97_GPIO));
		वापस;
	पूर्ण
	snd_ali_codec_poke(codec, ac97->num, reg, val);
	वापस ;
पूर्ण


अटल अचिन्हित लघु snd_ali_codec_पढ़ो(काष्ठा snd_ac97 *ac97,
					 अचिन्हित लघु reg)
अणु
	काष्ठा snd_ali *codec = ac97->निजी_data;

	dev_dbg(codec->card->dev, "codec_read reg=%xh.\n", reg);
	वापस snd_ali_codec_peek(codec, ac97->num, reg);
पूर्ण

/*
 *	AC97 Reset
 */

अटल पूर्णांक snd_ali_reset_5451(काष्ठा snd_ali *codec)
अणु
	काष्ठा pci_dev *pci_dev;
	अचिन्हित लघु wCount, wReg;
	अचिन्हित पूर्णांक   dwVal;
	
	pci_dev = codec->pci_m1533;
	अगर (pci_dev) अणु
		pci_पढ़ो_config_dword(pci_dev, 0x7c, &dwVal);
		pci_ग_लिखो_config_dword(pci_dev, 0x7c, dwVal | 0x08000000);
		mdelay(5);
		pci_पढ़ो_config_dword(pci_dev, 0x7c, &dwVal);
		pci_ग_लिखो_config_dword(pci_dev, 0x7c, dwVal & 0xf7ffffff);
		mdelay(5);
	पूर्ण
	
	pci_dev = codec->pci;
	pci_पढ़ो_config_dword(pci_dev, 0x44, &dwVal);
	pci_ग_लिखो_config_dword(pci_dev, 0x44, dwVal | 0x000c0000);
	udelay(500);
	pci_पढ़ो_config_dword(pci_dev, 0x44, &dwVal);
	pci_ग_लिखो_config_dword(pci_dev, 0x44, dwVal & 0xfffbffff);
	mdelay(5);
	
	wCount = 200;
	जबतक(wCount--) अणु
		wReg = snd_ali_codec_peek(codec, 0, AC97_POWERDOWN);
		अगर ((wReg & 0x000f) == 0x000f)
			वापस 0;
		mdelay(5);
	पूर्ण

	/* non-fatal अगर you have a non PM capable codec */
	/* dev_warn(codec->card->dev, "ali5451: reset time out\n"); */
	वापस 0;
पूर्ण

/*
 *  ALI 5451 Controller
 */

अटल व्योम snd_ali_enable_special_channel(काष्ठा snd_ali *codec,
					   अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित दीर्घ dwVal;

	dwVal  = inl(ALI_REG(codec, ALI_GLOBAL_CONTROL));
	dwVal |= 1 << (channel & 0x0000001f);
	outl(dwVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));
पूर्ण

अटल व्योम snd_ali_disable_special_channel(काष्ठा snd_ali *codec,
					    अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित दीर्घ dwVal;

	dwVal  = inl(ALI_REG(codec, ALI_GLOBAL_CONTROL));
	dwVal &= ~(1 << (channel & 0x0000001f));
	outl(dwVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));
पूर्ण

अटल व्योम snd_ali_enable_address_पूर्णांकerrupt(काष्ठा snd_ali *codec)
अणु
	अचिन्हित पूर्णांक gc;

	gc  = inl(ALI_REG(codec, ALI_GC_CIR));
	gc |= ENDLP_IE;
	gc |= MIDLP_IE;
	outl( gc, ALI_REG(codec, ALI_GC_CIR));
पूर्ण

अटल व्योम snd_ali_disable_address_पूर्णांकerrupt(काष्ठा snd_ali *codec)
अणु
	अचिन्हित पूर्णांक gc;

	gc  = inl(ALI_REG(codec, ALI_GC_CIR));
	gc &= ~ENDLP_IE;
	gc &= ~MIDLP_IE;
	outl(gc, ALI_REG(codec, ALI_GC_CIR));
पूर्ण

अटल व्योम snd_ali_disable_voice_irq(काष्ठा snd_ali *codec,
				      अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक mask;
	काष्ठा snd_ali_channel_control *pchregs = &(codec->chregs);

	dev_dbg(codec->card->dev, "disable_voice_irq channel=%d\n", channel);

	mask = 1 << (channel & 0x1f);
	pchregs->data.aपूर्णांकen  = inl(ALI_REG(codec, pchregs->regs.aपूर्णांकen));
	pchregs->data.aपूर्णांकen &= ~mask;
	outl(pchregs->data.aपूर्णांकen, ALI_REG(codec, pchregs->regs.aपूर्णांकen));
पूर्ण

अटल पूर्णांक snd_ali_alloc_pcm_channel(काष्ठा snd_ali *codec, पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक idx =  channel & 0x1f;

	अगर (codec->synth.chcnt >= ALI_CHANNELS)अणु
		dev_err(codec->card->dev,
			   "ali_alloc_pcm_channel: no free channels.\n");
		वापस -1;
	पूर्ण

	अगर (!(codec->synth.chmap & (1 << idx))) अणु
		codec->synth.chmap |= 1 << idx;
		codec->synth.chcnt++;
		dev_dbg(codec->card->dev, "alloc_pcm_channel no. %d.\n", idx);
		वापस idx;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक snd_ali_find_मुक्त_channel(काष्ठा snd_ali * codec, पूर्णांक rec)
अणु
	पूर्णांक idx;
	पूर्णांक result = -1;

	dev_dbg(codec->card->dev,
		"find_free_channel: for %s\n", rec ? "rec" : "pcm");

	/* recording */
	अगर (rec) अणु
		अगर (codec->spdअगर_support &&
		    (inl(ALI_REG(codec, ALI_GLOBAL_CONTROL)) &
		     ALI_SPDIF_IN_SUPPORT))
			idx = ALI_SPDIF_IN_CHANNEL;
		अन्यथा
			idx = ALI_PCM_IN_CHANNEL;

		result = snd_ali_alloc_pcm_channel(codec, idx);
		अगर (result >= 0)
			वापस result;
		अन्यथा अणु
			dev_err(codec->card->dev,
				"ali_find_free_channel: record channel is busy now.\n");
			वापस -1;
		पूर्ण
	पूर्ण

	/* playback... */
	अगर (codec->spdअगर_support &&
	    (inl(ALI_REG(codec, ALI_GLOBAL_CONTROL)) &
	     ALI_SPDIF_OUT_CH_ENABLE)) अणु
		idx = ALI_SPDIF_OUT_CHANNEL;
		result = snd_ali_alloc_pcm_channel(codec, idx);
		अगर (result >= 0)
			वापस result;
		अन्यथा
			dev_err(codec->card->dev,
				"ali_find_free_channel: S/PDIF out channel is in busy now.\n");
	पूर्ण

	क्रम (idx = 0; idx < ALI_CHANNELS; idx++) अणु
		result = snd_ali_alloc_pcm_channel(codec, idx);
		अगर (result >= 0)
			वापस result;
	पूर्ण
	dev_err(codec->card->dev, "ali_find_free_channel: no free channels.\n");
	वापस -1;
पूर्ण

अटल व्योम snd_ali_मुक्त_channel_pcm(काष्ठा snd_ali *codec, पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक idx = channel & 0x0000001f;

	dev_dbg(codec->card->dev, "free_channel_pcm channel=%d\n", channel);

	अगर (channel < 0 || channel >= ALI_CHANNELS)
		वापस;

	अगर (!(codec->synth.chmap & (1 << idx))) अणु
		dev_err(codec->card->dev,
			"ali_free_channel_pcm: channel %d is not in use.\n",
			channel);
		वापस;
	पूर्ण अन्यथा अणु
		codec->synth.chmap &= ~(1 << idx);
		codec->synth.chcnt--;
	पूर्ण
पूर्ण

अटल व्योम snd_ali_stop_voice(काष्ठा snd_ali *codec, अचिन्हित पूर्णांक channel)
अणु
	अचिन्हित पूर्णांक mask = 1 << (channel & 0x1f);

	dev_dbg(codec->card->dev, "stop_voice: channel=%d\n", channel);
	outl(mask, ALI_REG(codec, codec->chregs.regs.stop));
पूर्ण

/*
 *    S/PDIF Part
 */

अटल व्योम snd_ali_delay(काष्ठा snd_ali *codec,पूर्णांक पूर्णांकerval)
अणु
	अचिन्हित दीर्घ  begपूर्णांकimer,currentसमयr;

	begपूर्णांकimer   = inl(ALI_REG(codec, ALI_STIMER));
	currentसमयr = inl(ALI_REG(codec, ALI_STIMER));

	जबतक (currentसमयr < begपूर्णांकimer + पूर्णांकerval) अणु
		अगर (snd_ali_sसमयr_पढ़ोy(codec) < 0)
			अवरोध;
		currentसमयr = inl(ALI_REG(codec,  ALI_STIMER));
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम snd_ali_detect_spdअगर_rate(काष्ठा snd_ali *codec)
अणु
	u16 wval;
	u16 count = 0;
	u8  bval, R1 = 0, R2;

	bval  = inb(ALI_REG(codec, ALI_SPDIF_CTRL + 1));
	bval |= 0x1F;
	outb(bval, ALI_REG(codec, ALI_SPDIF_CTRL + 1));

	जबतक ((R1 < 0x0b || R1 > 0x0e) && R1 != 0x12 && count <= 50000) अणु
		count ++;
		snd_ali_delay(codec, 6);
		bval = inb(ALI_REG(codec, ALI_SPDIF_CTRL + 1));
		R1 = bval & 0x1F;
	पूर्ण

	अगर (count > 50000) अणु
		dev_err(codec->card->dev, "ali_detect_spdif_rate: timeout!\n");
		वापस;
	पूर्ण

	क्रम (count = 0; count <= 50000; count++) अणु
		snd_ali_delay(codec, 6);
		bval = inb(ALI_REG(codec,ALI_SPDIF_CTRL + 1));
		R2 = bval & 0x1F;
		अगर (R2 != R1)
			R1 = R2;
		अन्यथा
			अवरोध;
	पूर्ण

	अगर (count > 50000) अणु
		dev_err(codec->card->dev, "ali_detect_spdif_rate: timeout!\n");
		वापस;
	पूर्ण

	अगर (R2 >= 0x0b && R2 <= 0x0e) अणु
		wval  = inw(ALI_REG(codec, ALI_SPDIF_CTRL + 2));
		wval &= 0xe0f0;
		wval |= (0x09 << 8) | 0x05;
		outw(wval, ALI_REG(codec, ALI_SPDIF_CTRL + 2));

		bval  = inb(ALI_REG(codec, ALI_SPDIF_CS + 3)) & 0xf0;
		outb(bval | 0x02, ALI_REG(codec, ALI_SPDIF_CS + 3));
	पूर्ण अन्यथा अगर (R2 == 0x12) अणु
		wval  = inw(ALI_REG(codec, ALI_SPDIF_CTRL + 2));
		wval &= 0xe0f0;
		wval |= (0x0e << 8) | 0x08;
		outw(wval, ALI_REG(codec, ALI_SPDIF_CTRL + 2));

		bval  = inb(ALI_REG(codec,ALI_SPDIF_CS + 3)) & 0xf0;
		outb(bval | 0x03, ALI_REG(codec, ALI_SPDIF_CS + 3));
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक snd_ali_get_spdअगर_in_rate(काष्ठा snd_ali *codec)
अणु
	u32	dwRate;
	u8	bval;

	bval  = inb(ALI_REG(codec, ALI_SPDIF_CTRL));
	bval &= 0x7f;
	bval |= 0x40;
	outb(bval, ALI_REG(codec, ALI_SPDIF_CTRL));

	snd_ali_detect_spdअगर_rate(codec);

	bval  = inb(ALI_REG(codec, ALI_SPDIF_CS + 3));
	bval &= 0x0f;

	चयन (bval) अणु
	हाल 0: dwRate = 44100; अवरोध;
	हाल 1: dwRate = 48000; अवरोध;
	हाल 2: dwRate = 32000; अवरोध;
	शेष: dwRate = 0; अवरोध;
	पूर्ण

	वापस dwRate;
पूर्ण

अटल व्योम snd_ali_enable_spdअगर_in(काष्ठा snd_ali *codec)
अणु	
	अचिन्हित पूर्णांक dwVal;

	dwVal = inl(ALI_REG(codec, ALI_GLOBAL_CONTROL));
	dwVal |= ALI_SPDIF_IN_SUPPORT;
	outl(dwVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));

	dwVal = inb(ALI_REG(codec, ALI_SPDIF_CTRL));
	dwVal |= 0x02;
	outb(dwVal, ALI_REG(codec, ALI_SPDIF_CTRL));

	snd_ali_enable_special_channel(codec, ALI_SPDIF_IN_CHANNEL);
पूर्ण

अटल व्योम snd_ali_disable_spdअगर_in(काष्ठा snd_ali *codec)
अणु
	अचिन्हित पूर्णांक dwVal;
	
	dwVal = inl(ALI_REG(codec, ALI_GLOBAL_CONTROL));
	dwVal &= ~ALI_SPDIF_IN_SUPPORT;
	outl(dwVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));
	
	snd_ali_disable_special_channel(codec, ALI_SPDIF_IN_CHANNEL);	
पूर्ण


अटल व्योम snd_ali_set_spdअगर_out_rate(काष्ठा snd_ali *codec, अचिन्हित पूर्णांक rate)
अणु
	अचिन्हित अक्षर  bVal;
	अचिन्हित पूर्णांक  dwRate;
	
	चयन (rate) अणु
	हाल 32000: dwRate = 0x300; अवरोध;
	हाल 48000: dwRate = 0x200; अवरोध;
	शेष: dwRate = 0; अवरोध;
	पूर्ण
	
	bVal  = inb(ALI_REG(codec, ALI_SPDIF_CTRL));
	bVal &= (अचिन्हित अक्षर)(~(1<<6));
	
	bVal |= 0x80;		/* select right */
	outb(bVal, ALI_REG(codec, ALI_SPDIF_CTRL));
	outb(dwRate | 0x20, ALI_REG(codec, ALI_SPDIF_CS + 2));
	
	bVal &= ~0x80;	/* select left */
	outb(bVal, ALI_REG(codec, ALI_SPDIF_CTRL));
	outw(rate | 0x10, ALI_REG(codec, ALI_SPDIF_CS + 2));
पूर्ण

अटल व्योम snd_ali_enable_spdअगर_out(काष्ठा snd_ali *codec)
अणु
	अचिन्हित लघु wVal;
	अचिन्हित अक्षर bVal;
        काष्ठा pci_dev *pci_dev;

        pci_dev = codec->pci_m1533;
        अगर (pci_dev == शून्य)
                वापस;
        pci_पढ़ो_config_byte(pci_dev, 0x61, &bVal);
        bVal |= 0x40;
        pci_ग_लिखो_config_byte(pci_dev, 0x61, bVal);
        pci_पढ़ो_config_byte(pci_dev, 0x7d, &bVal);
        bVal |= 0x01;
        pci_ग_लिखो_config_byte(pci_dev, 0x7d, bVal);

        pci_पढ़ो_config_byte(pci_dev, 0x7e, &bVal);
        bVal &= (~0x20);
        bVal |= 0x10;
        pci_ग_लिखो_config_byte(pci_dev, 0x7e, bVal);

	bVal = inb(ALI_REG(codec, ALI_SCTRL));
	outb(bVal | ALI_SPDIF_OUT_ENABLE, ALI_REG(codec, ALI_SCTRL));

	bVal = inb(ALI_REG(codec, ALI_SPDIF_CTRL));
	outb(bVal & ALI_SPDIF_OUT_CH_STATUS, ALI_REG(codec, ALI_SPDIF_CTRL));
   
	wVal = inw(ALI_REG(codec, ALI_GLOBAL_CONTROL));
	wVal |= ALI_SPDIF_OUT_SEL_PCM;
	outw(wVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));
	snd_ali_disable_special_channel(codec, ALI_SPDIF_OUT_CHANNEL);
पूर्ण

अटल व्योम snd_ali_enable_spdअगर_chnout(काष्ठा snd_ali *codec)
अणु
	अचिन्हित लघु wVal;

	wVal  = inw(ALI_REG(codec, ALI_GLOBAL_CONTROL));
   	wVal &= ~ALI_SPDIF_OUT_SEL_PCM;
   	outw(wVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));
/*
	wVal = inw(ALI_REG(codec, ALI_SPDIF_CS));
	अगर (flag & ALI_SPDIF_OUT_NON_PCM)
   		wVal |= 0x0002;
	अन्यथा	
		wVal &= (~0x0002);
   	outw(wVal, ALI_REG(codec, ALI_SPDIF_CS));
*/
	snd_ali_enable_special_channel(codec, ALI_SPDIF_OUT_CHANNEL);
पूर्ण

अटल व्योम snd_ali_disable_spdअगर_chnout(काष्ठा snd_ali *codec)
अणु
	अचिन्हित लघु wVal;

  	wVal  = inw(ALI_REG(codec, ALI_GLOBAL_CONTROL));
   	wVal |= ALI_SPDIF_OUT_SEL_PCM;
   	outw(wVal, ALI_REG(codec, ALI_GLOBAL_CONTROL));

	snd_ali_enable_special_channel(codec, ALI_SPDIF_OUT_CHANNEL);
पूर्ण

अटल व्योम snd_ali_disable_spdअगर_out(काष्ठा snd_ali *codec)
अणु
	अचिन्हित अक्षर  bVal;

	bVal = inb(ALI_REG(codec, ALI_SCTRL));
	outb(bVal & ~ALI_SPDIF_OUT_ENABLE, ALI_REG(codec, ALI_SCTRL));

	snd_ali_disable_spdअगर_chnout(codec);
पूर्ण

अटल व्योम snd_ali_update_ptr(काष्ठा snd_ali *codec, पूर्णांक channel)
अणु
	काष्ठा snd_ali_voice *pvoice;
	काष्ठा snd_ali_channel_control *pchregs;
	अचिन्हित पूर्णांक old, mask;

	pchregs = &(codec->chregs);

	/* check अगर पूर्णांकerrupt occurred क्रम channel */
	old  = pchregs->data.aपूर्णांक;
	mask = 1U << (channel & 0x1f);

	अगर (!(old & mask))
		वापस;

	pvoice = &codec->synth.voices[channel];

	udelay(100);
	spin_lock(&codec->reg_lock);

	अगर (pvoice->pcm && pvoice->substream) अणु
		/* pcm पूर्णांकerrupt */
		अगर (pvoice->running) अणु
			dev_dbg(codec->card->dev,
				"update_ptr: cso=%4.4x cspf=%d.\n",
				inw(ALI_REG(codec, ALI_CSO_ALPHA_FMS + 2)),
				(inl(ALI_REG(codec, ALI_CSPF)) & mask) == mask);
			spin_unlock(&codec->reg_lock);
			snd_pcm_period_elapsed(pvoice->substream);
			spin_lock(&codec->reg_lock);
		पूर्ण अन्यथा अणु
			snd_ali_stop_voice(codec, channel);
			snd_ali_disable_voice_irq(codec, channel);
		पूर्ण	
	पूर्ण अन्यथा अगर (codec->synth.voices[channel].synth) अणु
		/* synth पूर्णांकerrupt */
	पूर्ण अन्यथा अगर (codec->synth.voices[channel].midi) अणु
		/* midi पूर्णांकerrupt */
	पूर्ण अन्यथा अणु
		/* unknown पूर्णांकerrupt */
		snd_ali_stop_voice(codec, channel);
		snd_ali_disable_voice_irq(codec, channel);
	पूर्ण
	spin_unlock(&codec->reg_lock);
	outl(mask,ALI_REG(codec,pchregs->regs.aपूर्णांक));
	pchregs->data.aपूर्णांक = old & (~mask);
पूर्ण

अटल irqवापस_t snd_ali_card_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_ali 	*codec = dev_id;
	पूर्णांक channel;
	अचिन्हित पूर्णांक audio_पूर्णांक;
	काष्ठा snd_ali_channel_control *pchregs;

	अगर (codec == शून्य || !codec->hw_initialized)
		वापस IRQ_NONE;

	audio_पूर्णांक = inl(ALI_REG(codec, ALI_MISCINT));
	अगर (!audio_पूर्णांक)
		वापस IRQ_NONE;

	pchregs = &(codec->chregs);
	अगर (audio_पूर्णांक & ADDRESS_IRQ) अणु
		/* get पूर्णांकerrupt status क्रम all channels */
		pchregs->data.aपूर्णांक = inl(ALI_REG(codec, pchregs->regs.aपूर्णांक));
		क्रम (channel = 0; channel < ALI_CHANNELS; channel++)
			snd_ali_update_ptr(codec, channel);
	पूर्ण
	outl((TARGET_REACHED | MIXER_OVERFLOW | MIXER_UNDERFLOW),
		ALI_REG(codec, ALI_MISCINT));

	वापस IRQ_HANDLED;
पूर्ण


अटल काष्ठा snd_ali_voice *snd_ali_alloc_voice(काष्ठा snd_ali * codec,
						 पूर्णांक type, पूर्णांक rec, पूर्णांक channel)
अणु
	काष्ठा snd_ali_voice *pvoice;
	पूर्णांक idx;

	dev_dbg(codec->card->dev, "alloc_voice: type=%d rec=%d\n", type, rec);

	spin_lock_irq(&codec->voice_alloc);
	अगर (type == SNDRV_ALI_VOICE_TYPE_PCM) अणु
		idx = channel > 0 ? snd_ali_alloc_pcm_channel(codec, channel) :
			snd_ali_find_मुक्त_channel(codec,rec);
		अगर (idx < 0) अणु
			dev_err(codec->card->dev, "ali_alloc_voice: err.\n");
			spin_unlock_irq(&codec->voice_alloc);
			वापस शून्य;
		पूर्ण
		pvoice = &(codec->synth.voices[idx]);
		pvoice->codec = codec;
		pvoice->use = 1;
		pvoice->pcm = 1;
		pvoice->mode = rec;
		spin_unlock_irq(&codec->voice_alloc);
		वापस pvoice;
	पूर्ण
	spin_unlock_irq(&codec->voice_alloc);
	वापस शून्य;
पूर्ण


अटल व्योम snd_ali_मुक्त_voice(काष्ठा snd_ali * codec,
			       काष्ठा snd_ali_voice *pvoice)
अणु
	व्योम (*निजी_मुक्त)(व्योम *);
	व्योम *निजी_data;

	dev_dbg(codec->card->dev, "free_voice: channel=%d\n", pvoice->number);
	अगर (!pvoice->use)
		वापस;
	snd_ali_clear_voices(codec, pvoice->number, pvoice->number);
	spin_lock_irq(&codec->voice_alloc);
	निजी_मुक्त = pvoice->निजी_मुक्त;
	निजी_data = pvoice->निजी_data;
	pvoice->निजी_मुक्त = शून्य;
	pvoice->निजी_data = शून्य;
	अगर (pvoice->pcm)
		snd_ali_मुक्त_channel_pcm(codec, pvoice->number);
	pvoice->use = pvoice->pcm = pvoice->synth = 0;
	pvoice->substream = शून्य;
	spin_unlock_irq(&codec->voice_alloc);
	अगर (निजी_मुक्त)
		निजी_मुक्त(निजी_data);
पूर्ण


अटल व्योम snd_ali_clear_voices(काष्ठा snd_ali *codec,
				 अचिन्हित पूर्णांक v_min,
				 अचिन्हित पूर्णांक v_max)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = v_min; i <= v_max; i++) अणु
		snd_ali_stop_voice(codec, i);
		snd_ali_disable_voice_irq(codec, i);
	पूर्ण
पूर्ण

अटल व्योम snd_ali_ग_लिखो_voice_regs(काष्ठा snd_ali *codec,
			 अचिन्हित पूर्णांक Channel,
			 अचिन्हित पूर्णांक LBA,
			 अचिन्हित पूर्णांक CSO,
			 अचिन्हित पूर्णांक ESO,
			 अचिन्हित पूर्णांक DELTA,
			 अचिन्हित पूर्णांक ALPHA_FMS,
			 अचिन्हित पूर्णांक GVSEL,
			 अचिन्हित पूर्णांक PAN,
			 अचिन्हित पूर्णांक VOL,
			 अचिन्हित पूर्णांक CTRL,
			 अचिन्हित पूर्णांक EC)
अणु
	अचिन्हित पूर्णांक ctlcmds[4];
	
	outb((अचिन्हित अक्षर)(Channel & 0x001f), ALI_REG(codec, ALI_GC_CIR));

	ctlcmds[0] =  (CSO << 16) | (ALPHA_FMS & 0x0000ffff);
	ctlcmds[1] =  LBA;
	ctlcmds[2] =  (ESO << 16) | (DELTA & 0x0ffff);
	ctlcmds[3] =  (GVSEL << 31) |
		      ((PAN & 0x0000007f) << 24) |
		      ((VOL & 0x000000ff) << 16) |
		      ((CTRL & 0x0000000f) << 12) |
		      (EC & 0x00000fff);

	outb(Channel, ALI_REG(codec, ALI_GC_CIR));

	outl(ctlcmds[0], ALI_REG(codec, ALI_CSO_ALPHA_FMS));
	outl(ctlcmds[1], ALI_REG(codec, ALI_LBA));
	outl(ctlcmds[2], ALI_REG(codec, ALI_ESO_DELTA));
	outl(ctlcmds[3], ALI_REG(codec, ALI_GVSEL_PAN_VOC_CTRL_EC));

	outl(0x30000000, ALI_REG(codec, ALI_EBUF1));	/* Still Mode */
	outl(0x30000000, ALI_REG(codec, ALI_EBUF2));	/* Still Mode */
पूर्ण

अटल अचिन्हित पूर्णांक snd_ali_convert_rate(अचिन्हित पूर्णांक rate, पूर्णांक rec)
अणु
	अचिन्हित पूर्णांक delta;

	अगर (rate < 4000)
		rate = 4000;
	अगर (rate > 48000)
		rate = 48000;

	अगर (rec) अणु
		अगर (rate == 44100)
			delta = 0x116a;
		अन्यथा अगर (rate == 8000)
			delta = 0x6000;
		अन्यथा अगर (rate == 48000)
			delta = 0x1000;
		अन्यथा
			delta = ((48000 << 12) / rate) & 0x0000ffff;
	पूर्ण अन्यथा अणु
		अगर (rate == 44100)
			delta = 0xeb3;
		अन्यथा अगर (rate == 8000)
			delta = 0x2ab;
		अन्यथा अगर (rate == 48000)
			delta = 0x1000;
		अन्यथा 
			delta = (((rate << 12) + rate) / 48000) & 0x0000ffff;
	पूर्ण

	वापस delta;
पूर्ण

अटल अचिन्हित पूर्णांक snd_ali_control_mode(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित पूर्णांक CTRL;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/* set ctrl mode
	   CTRL शेष: 8-bit (अचिन्हित) mono, loop mode enabled
	 */
	CTRL = 0x00000001;
	अगर (snd_pcm_क्रमmat_width(runसमय->क्रमmat) == 16)
		CTRL |= 0x00000008;	/* 16-bit data */
	अगर (!snd_pcm_क्रमmat_अचिन्हित(runसमय->क्रमmat))
		CTRL |= 0x00000002;	/* चिन्हित data */
	अगर (runसमय->channels > 1)
		CTRL |= 0x00000004;	/* stereo data */
	वापस CTRL;
पूर्ण

/*
 *  PCM part
 */

अटल पूर्णांक snd_ali_trigger(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक cmd)
				    
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	अचिन्हित पूर्णांक what, whati;
	काष्ठा snd_ali_voice *pvoice, *evoice;
	अचिन्हित पूर्णांक val;
	पूर्णांक करो_start;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		करो_start = 1;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		करो_start = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	what = whati = 0;
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर ((काष्ठा snd_ali *) snd_pcm_substream_chip(s) == codec) अणु
			pvoice = s->runसमय->निजी_data;
			evoice = pvoice->extra;
			what |= 1 << (pvoice->number & 0x1f);
			अगर (evoice == शून्य)
				whati |= 1 << (pvoice->number & 0x1f);
			अन्यथा अणु
				whati |= 1 << (evoice->number & 0x1f);
				what |= 1 << (evoice->number & 0x1f);
			पूर्ण
			अगर (करो_start) अणु
				pvoice->running = 1;
				अगर (evoice != शून्य)
					evoice->running = 1;
			पूर्ण अन्यथा अणु
				pvoice->running = 0;
				अगर (evoice != शून्य)
					evoice->running = 0;
			पूर्ण
			snd_pcm_trigger_करोne(s, substream);
		पूर्ण
	पूर्ण
	spin_lock(&codec->reg_lock);
	अगर (!करो_start)
		outl(what, ALI_REG(codec, ALI_STOP));
	val = inl(ALI_REG(codec, ALI_AINTEN));
	अगर (करो_start)
		val |= whati;
	अन्यथा
		val &= ~whati;
	outl(val, ALI_REG(codec, ALI_AINTEN));
	अगर (करो_start)
		outl(what, ALI_REG(codec, ALI_START));
	dev_dbg(codec->card->dev, "trigger: what=%xh whati=%xh\n", what, whati);
	spin_unlock(&codec->reg_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_playback_hw_params(काष्ठा snd_pcm_substream *substream,
				      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;
	काष्ठा snd_ali_voice *evoice = pvoice->extra;

	/* voice management */

	अगर (params_buffer_size(hw_params) / 2 !=
	    params_period_size(hw_params)) अणु
		अगर (!evoice) अणु
			evoice = snd_ali_alloc_voice(codec,
						     SNDRV_ALI_VOICE_TYPE_PCM,
						     0, -1);
			अगर (!evoice)
				वापस -ENOMEM;
			pvoice->extra = evoice;
			evoice->substream = substream;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (evoice) अणु
			snd_ali_मुक्त_voice(codec, evoice);
			pvoice->extra = evoice = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_playback_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;
	काष्ठा snd_ali_voice *evoice = pvoice ? pvoice->extra : शून्य;

	अगर (evoice) अणु
		snd_ali_मुक्त_voice(codec, evoice);
		pvoice->extra = शून्य;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;
	काष्ठा snd_ali_voice *evoice = pvoice->extra;

	अचिन्हित पूर्णांक LBA;
	अचिन्हित पूर्णांक Delta;
	अचिन्हित पूर्णांक ESO;
	अचिन्हित पूर्णांक CTRL;
	अचिन्हित पूर्णांक GVSEL;
	अचिन्हित पूर्णांक PAN;
	अचिन्हित पूर्णांक VOL;
	अचिन्हित पूर्णांक EC;
	
	dev_dbg(codec->card->dev, "playback_prepare ...\n");

	spin_lock_irq(&codec->reg_lock);	
	
	/* set Delta (rate) value */
	Delta = snd_ali_convert_rate(runसमय->rate, 0);

	अगर (pvoice->number == ALI_SPDIF_IN_CHANNEL || 
	    pvoice->number == ALI_PCM_IN_CHANNEL)
		snd_ali_disable_special_channel(codec, pvoice->number);
	अन्यथा अगर (codec->spdअगर_support &&
		 (inl(ALI_REG(codec, ALI_GLOBAL_CONTROL)) &
		  ALI_SPDIF_OUT_CH_ENABLE)
		 && pvoice->number == ALI_SPDIF_OUT_CHANNEL) अणु
		snd_ali_set_spdअगर_out_rate(codec, runसमय->rate);
		Delta = 0x1000;
	पूर्ण
	
	/* set Loop Back Address */
	LBA = runसमय->dma_addr;

	/* set पूर्णांकerrupt count size */
	pvoice->count = runसमय->period_size;

	/* set target ESO क्रम channel */
	pvoice->eso = runसमय->buffer_size; 

	dev_dbg(codec->card->dev, "playback_prepare: eso=%xh count=%xh\n",
		       pvoice->eso, pvoice->count);

	/* set ESO to capture first MIDLP पूर्णांकerrupt */
	ESO = pvoice->eso -1;
	/* set ctrl mode */
	CTRL = snd_ali_control_mode(substream);

	GVSEL = 1;
	PAN = 0;
	VOL = 0;
	EC = 0;
	dev_dbg(codec->card->dev, "playback_prepare:\n");
	dev_dbg(codec->card->dev,
		"ch=%d, Rate=%d Delta=%xh,GVSEL=%xh,PAN=%xh,CTRL=%xh\n",
		       pvoice->number,runसमय->rate,Delta,GVSEL,PAN,CTRL);
	snd_ali_ग_लिखो_voice_regs(codec,
				 pvoice->number,
				 LBA,
				 0,	/* cso */
				 ESO,
				 Delta,
				 0,	/* alpha */
				 GVSEL,
				 PAN,
				 VOL,
				 CTRL,
				 EC);
	अगर (evoice) अणु
		evoice->count = pvoice->count;
		evoice->eso = pvoice->count << 1;
		ESO = evoice->eso - 1;
		snd_ali_ग_लिखो_voice_regs(codec,
					 evoice->number,
					 LBA,
					 0,	/* cso */
					 ESO,
					 Delta,
					 0,	/* alpha */
					 GVSEL,
					 0x7f,
					 0x3ff,
					 CTRL,
					 EC);
	पूर्ण
	spin_unlock_irq(&codec->reg_lock);
	वापस 0;
पूर्ण


अटल पूर्णांक snd_ali_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;
	अचिन्हित पूर्णांक LBA;
	अचिन्हित पूर्णांक Delta;
	अचिन्हित पूर्णांक ESO;
	अचिन्हित पूर्णांक CTRL;
	अचिन्हित पूर्णांक GVSEL;
	अचिन्हित पूर्णांक PAN;
	अचिन्हित पूर्णांक VOL;
	अचिन्हित पूर्णांक EC;
	u8	 bValue;

	spin_lock_irq(&codec->reg_lock);

	dev_dbg(codec->card->dev, "ali_prepare...\n");

	snd_ali_enable_special_channel(codec,pvoice->number);

	Delta = (pvoice->number == ALI_MODEM_IN_CHANNEL ||
		 pvoice->number == ALI_MODEM_OUT_CHANNEL) ? 
		0x1000 : snd_ali_convert_rate(runसमय->rate, pvoice->mode);

	/* Prepare capture पूर्णांकr channel */
	अगर (pvoice->number == ALI_SPDIF_IN_CHANNEL) अणु

		अचिन्हित पूर्णांक rate;
		
		spin_unlock_irq(&codec->reg_lock);
		अगर (codec->revision != ALI_5451_V02)
			वापस -1;

		rate = snd_ali_get_spdअगर_in_rate(codec);
		अगर (rate == 0) अणु
			dev_warn(codec->card->dev,
				 "ali_capture_prepare: spdif rate detect err!\n");
			rate = 48000;
		पूर्ण
		spin_lock_irq(&codec->reg_lock);
		bValue = inb(ALI_REG(codec,ALI_SPDIF_CTRL));
		अगर (bValue & 0x10) अणु
			outb(bValue,ALI_REG(codec,ALI_SPDIF_CTRL));
			dev_warn(codec->card->dev,
				 "clear SPDIF parity error flag.\n");
		पूर्ण

		अगर (rate != 48000)
			Delta = ((rate << 12) / runसमय->rate) & 0x00ffff;
	पूर्ण

	/* set target ESO क्रम channel  */
	pvoice->eso = runसमय->buffer_size; 

	/* set पूर्णांकerrupt count size  */
	pvoice->count = runसमय->period_size;

	/* set Loop Back Address  */
	LBA = runसमय->dma_addr;

	/* set ESO to capture first MIDLP पूर्णांकerrupt  */
	ESO = pvoice->eso - 1;
	CTRL = snd_ali_control_mode(substream);
	GVSEL = 0;
	PAN = 0x00;
	VOL = 0x00;
	EC = 0;

	snd_ali_ग_लिखो_voice_regs(    codec,
				     pvoice->number,
				     LBA,
				     0,	/* cso */
				     ESO,
				     Delta,
				     0,	/* alpha */
				     GVSEL,
				     PAN,
				     VOL,
				     CTRL,
				     EC);

	spin_unlock_irq(&codec->reg_lock);

	वापस 0;
पूर्ण


अटल snd_pcm_uframes_t
snd_ali_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;
	अचिन्हित पूर्णांक cso;

	spin_lock(&codec->reg_lock);
	अगर (!pvoice->running) अणु
		spin_unlock(&codec->reg_lock);
		वापस 0;
	पूर्ण
	outb(pvoice->number, ALI_REG(codec, ALI_GC_CIR));
	cso = inw(ALI_REG(codec, ALI_CSO_ALPHA_FMS + 2));
	spin_unlock(&codec->reg_lock);
	dev_dbg(codec->card->dev, "playback pointer returned cso=%xh.\n", cso);

	cso %= runसमय->buffer_size;
	वापस cso;
पूर्ण


अटल snd_pcm_uframes_t snd_ali_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;
	अचिन्हित पूर्णांक cso;

	spin_lock(&codec->reg_lock);
	अगर (!pvoice->running) अणु
		spin_unlock(&codec->reg_lock);
		वापस 0;
	पूर्ण
	outb(pvoice->number, ALI_REG(codec, ALI_GC_CIR));
	cso = inw(ALI_REG(codec, ALI_CSO_ALPHA_FMS + 2));
	spin_unlock(&codec->reg_lock);

	cso %= runसमय->buffer_size;
	वापस cso;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ali_playback =
अणु
	.info =		(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
			 SNDRV_PCM_INFO_BLOCK_TRANSFER |
			 SNDRV_PCM_INFO_MMAP_VALID |
			 SNDRV_PCM_INFO_RESUME |
			 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =	(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
			 SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =	SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
	.rate_min =		4000,
	.rate_max =		48000,
	.channels_min =		1,
	.channels_max =		2,
	.buffer_bytes_max =	(256*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(256*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

/*
 *  Capture support device description
 */

अटल स्थिर काष्ठा snd_pcm_hardware snd_ali_capture =
अणु
	.info =		(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
			 SNDRV_PCM_INFO_BLOCK_TRANSFER |
			 SNDRV_PCM_INFO_MMAP_VALID |
			 SNDRV_PCM_INFO_RESUME |
			 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =	(SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE |
			 SNDRV_PCM_FMTBIT_S8 | SNDRV_PCM_FMTBIT_U16_LE),
	.rates =	SNDRV_PCM_RATE_CONTINUOUS | SNDRV_PCM_RATE_8000_48000,
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

अटल व्योम snd_ali_pcm_मुक्त_substream(काष्ठा snd_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_ali_voice *pvoice = runसमय->निजी_data;

	अगर (pvoice)
		snd_ali_मुक्त_voice(pvoice->codec, pvoice);
पूर्ण

अटल पूर्णांक snd_ali_खोलो(काष्ठा snd_pcm_substream *substream, पूर्णांक rec,
			पूर्णांक channel, स्थिर काष्ठा snd_pcm_hardware *phw)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_ali_voice *pvoice;

	pvoice = snd_ali_alloc_voice(codec, SNDRV_ALI_VOICE_TYPE_PCM, rec,
				     channel);
	अगर (!pvoice)
		वापस -EAGAIN;

	pvoice->substream = substream;
	runसमय->निजी_data = pvoice;
	runसमय->निजी_मुक्त = snd_ali_pcm_मुक्त_substream;

	runसमय->hw = *phw;
	snd_pcm_set_sync(substream);
	snd_pcm_hw_स्थिरraपूर्णांक_minmax(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_SIZE,
				     0, 64*1024);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ali_खोलो(substream, 0, -1, &snd_ali_playback);
पूर्ण

अटल पूर्णांक snd_ali_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ali_खोलो(substream, 1, -1, &snd_ali_capture);
पूर्ण

अटल पूर्णांक snd_ali_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ali *codec = snd_pcm_substream_chip(substream);
	काष्ठा snd_ali_voice *pvoice = substream->runसमय->निजी_data;

	snd_ali_disable_special_channel(codec,pvoice->number);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ali_playback_ops = अणु
	.खोलो =		snd_ali_playback_खोलो,
	.बंद =	snd_ali_playback_बंद,
	.hw_params =	snd_ali_playback_hw_params,
	.hw_मुक्त =	snd_ali_playback_hw_मुक्त,
	.prepare =	snd_ali_playback_prepare,
	.trigger =	snd_ali_trigger,
	.poपूर्णांकer =	snd_ali_playback_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ali_capture_ops = अणु
	.खोलो =		snd_ali_capture_खोलो,
	.बंद =	snd_ali_बंद,
	.prepare =	snd_ali_prepare,
	.trigger =	snd_ali_trigger,
	.poपूर्णांकer =	snd_ali_poपूर्णांकer,
पूर्ण;

/*
 * Modem PCM
 */

अटल पूर्णांक snd_ali_modem_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_ali *chip = snd_pcm_substream_chip(substream);
	अचिन्हित पूर्णांक modem_num = chip->num_of_codecs - 1;
	snd_ac97_ग_लिखो(chip->ac97[modem_num], AC97_LINE1_RATE,
		       params_rate(hw_params));
	snd_ac97_ग_लिखो(chip->ac97[modem_num], AC97_LINE1_LEVEL, 0);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_ali_modem =
अणु
	.info =		(SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
			 SNDRV_PCM_INFO_BLOCK_TRANSFER |
			 SNDRV_PCM_INFO_MMAP_VALID |
			 SNDRV_PCM_INFO_RESUME |
			 SNDRV_PCM_INFO_SYNC_START),
	.क्रमmats =	SNDRV_PCM_FMTBIT_S16_LE,
	.rates =	(SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000 |
			 SNDRV_PCM_RATE_16000),
	.rate_min =		8000,
	.rate_max =		16000,
	.channels_min =		1,
	.channels_max =		1,
	.buffer_bytes_max =	(256*1024),
	.period_bytes_min =	64,
	.period_bytes_max =	(256*1024),
	.periods_min =		1,
	.periods_max =		1024,
	.fअगरo_size =		0,
पूर्ण;

अटल पूर्णांक snd_ali_modem_खोलो(काष्ठा snd_pcm_substream *substream, पूर्णांक rec,
			      पूर्णांक channel)
अणु
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु8000, 9600, 12000, 16000पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांक_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list = rates,
		.mask = 0,
	पूर्ण;
	पूर्णांक err = snd_ali_खोलो(substream, rec, channel, &snd_ali_modem);

	अगर (err)
		वापस err;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &hw_स्थिरraपूर्णांक_rates);
पूर्ण

अटल पूर्णांक snd_ali_modem_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ali_modem_खोलो(substream, 0, ALI_MODEM_OUT_CHANNEL);
पूर्ण

अटल पूर्णांक snd_ali_modem_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_ali_modem_खोलो(substream, 1, ALI_MODEM_IN_CHANNEL);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ali_modem_playback_ops = अणु
	.खोलो =		snd_ali_modem_playback_खोलो,
	.बंद =	snd_ali_बंद,
	.hw_params =	snd_ali_modem_hw_params,
	.prepare =	snd_ali_prepare,
	.trigger =	snd_ali_trigger,
	.poपूर्णांकer =	snd_ali_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_ali_modem_capture_ops = अणु
	.खोलो =		snd_ali_modem_capture_खोलो,
	.बंद =	snd_ali_बंद,
	.hw_params =	snd_ali_modem_hw_params,
	.prepare =	snd_ali_prepare,
	.trigger =	snd_ali_trigger,
	.poपूर्णांकer =	snd_ali_poपूर्णांकer,
पूर्ण;


काष्ठा ali_pcm_description अणु
	अक्षर *name;
	अचिन्हित पूर्णांक playback_num;
	अचिन्हित पूर्णांक capture_num;
	स्थिर काष्ठा snd_pcm_ops *playback_ops;
	स्थिर काष्ठा snd_pcm_ops *capture_ops;
	अचिन्हित लघु class;
पूर्ण;


अटल व्योम snd_ali_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_ali *codec = pcm->निजी_data;
	codec->pcm[pcm->device] = शून्य;
पूर्ण


अटल पूर्णांक snd_ali_pcm(काष्ठा snd_ali *codec, पूर्णांक device,
		       काष्ठा ali_pcm_description *desc)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	err = snd_pcm_new(codec->card, desc->name, device,
			  desc->playback_num, desc->capture_num, &pcm);
	अगर (err < 0) अणु
		dev_err(codec->card->dev,
			"snd_ali_pcm: err called snd_pcm_new.\n");
		वापस err;
	पूर्ण
	pcm->निजी_data = codec;
	pcm->निजी_मुक्त = snd_ali_pcm_मुक्त;
	अगर (desc->playback_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
				desc->playback_ops);
	अगर (desc->capture_ops)
		snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
				desc->capture_ops);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV,
				       &codec->pci->dev, 64*1024, 128*1024);

	pcm->info_flags = 0;
	pcm->dev_class = desc->class;
	pcm->dev_subclass = SNDRV_PCM_SUBCLASS_GENERIC_MIX;
	म_नकल(pcm->name, desc->name);
	codec->pcm[0] = pcm;
	वापस 0;
पूर्ण

अटल काष्ठा ali_pcm_description ali_pcms[] = अणु
	अणु .name = "ALI 5451",
	  .playback_num = ALI_CHANNELS,
	  .capture_num = 1,
	  .playback_ops = &snd_ali_playback_ops,
	  .capture_ops = &snd_ali_capture_ops
	पूर्ण,
	अणु .name = "ALI 5451 modem",
	  .playback_num = 1,
	  .capture_num = 1,
	  .playback_ops = &snd_ali_modem_playback_ops,
	  .capture_ops = &snd_ali_modem_capture_ops,
	  .class = SNDRV_PCM_CLASS_MODEM
	पूर्ण
पूर्ण;

अटल पूर्णांक snd_ali_build_pcms(काष्ठा snd_ali *codec)
अणु
	पूर्णांक i, err;
	क्रम (i = 0; i < codec->num_of_codecs && i < ARRAY_SIZE(ali_pcms); i++) अणु
		err = snd_ali_pcm(codec, i, &ali_pcms[i]);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण


#घोषणा ALI5451_SPDIF(xname, xindex, value) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, .name = xname, .index = xindex,\
.info = snd_ali5451_spdअगर_info, .get = snd_ali5451_spdअगर_get, \
.put = snd_ali5451_spdअगर_put, .निजी_value = valueपूर्ण

#घोषणा snd_ali5451_spdअगर_info		snd_ctl_boolean_mono_info

अटल पूर्णांक snd_ali5451_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ali *codec = kcontrol->निजी_data;
	अचिन्हित पूर्णांक spdअगर_enable;

	spdअगर_enable = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;

	spin_lock_irq(&codec->reg_lock);
	चयन (kcontrol->निजी_value) अणु
	हाल 0:
		spdअगर_enable = (codec->spdअगर_mask & 0x02) ? 1 : 0;
		अवरोध;
	हाल 1:
		spdअगर_enable = ((codec->spdअगर_mask & 0x02) &&
			  (codec->spdअगर_mask & 0x04)) ? 1 : 0;
		अवरोध;
	हाल 2:
		spdअगर_enable = (codec->spdअगर_mask & 0x01) ? 1 : 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	ucontrol->value.पूर्णांकeger.value[0] = spdअगर_enable;
	spin_unlock_irq(&codec->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali5451_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_ali *codec = kcontrol->निजी_data;
	अचिन्हित पूर्णांक change = 0, spdअगर_enable = 0;

	spdअगर_enable = ucontrol->value.पूर्णांकeger.value[0] ? 1 : 0;

	spin_lock_irq(&codec->reg_lock);
	चयन (kcontrol->निजी_value) अणु
	हाल 0:
		change = (codec->spdअगर_mask & 0x02) ? 1 : 0;
		change = change ^ spdअगर_enable;
		अगर (change) अणु
			अगर (spdअगर_enable) अणु
				codec->spdअगर_mask |= 0x02;
				snd_ali_enable_spdअगर_out(codec);
			पूर्ण अन्यथा अणु
				codec->spdअगर_mask &= ~(0x02);
				codec->spdअगर_mask &= ~(0x04);
				snd_ali_disable_spdअगर_out(codec);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 1: 
		change = (codec->spdअगर_mask & 0x04) ? 1 : 0;
		change = change ^ spdअगर_enable;
		अगर (change && (codec->spdअगर_mask & 0x02)) अणु
			अगर (spdअगर_enable) अणु
				codec->spdअगर_mask |= 0x04;
				snd_ali_enable_spdअगर_chnout(codec);
			पूर्ण अन्यथा अणु
				codec->spdअगर_mask &= ~(0x04);
				snd_ali_disable_spdअगर_chnout(codec);
			पूर्ण
		पूर्ण
		अवरोध;
	हाल 2:
		change = (codec->spdअगर_mask & 0x01) ? 1 : 0;
		change = change ^ spdअगर_enable;
		अगर (change) अणु
			अगर (spdअगर_enable) अणु
				codec->spdअगर_mask |= 0x01;
				snd_ali_enable_spdअगर_in(codec);
			पूर्ण अन्यथा अणु
				codec->spdअगर_mask &= ~(0x01);
				snd_ali_disable_spdअगर_in(codec);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	spin_unlock_irq(&codec->reg_lock);
	
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_ali5451_mixer_spdअगर[] = अणु
	/* spdअगर aplayback चयन */
	/* FIXME: "IEC958 Playback Switch" may conflict with one on ac97_codec */
	ALI5451_SPDIF(SNDRV_CTL_NAME_IEC958("Output ",NONE,SWITCH), 0, 0),
	/* spdअगर out to spdअगर channel */
	ALI5451_SPDIF(SNDRV_CTL_NAME_IEC958("Channel Output ",NONE,SWITCH), 0, 1),
	/* spdअगर in from spdअगर channel */
	ALI5451_SPDIF(SNDRV_CTL_NAME_IEC958("",CAPTURE,SWITCH), 0, 2)
पूर्ण;

अटल पूर्णांक snd_ali_mixer(काष्ठा snd_ali *codec)
अणु
	काष्ठा snd_ac97_ढाँचा ac97;
	अचिन्हित पूर्णांक idx;
	पूर्णांक i, err;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_ali_codec_ग_लिखो,
		.पढ़ो = snd_ali_codec_पढ़ो,
	पूर्ण;

	err = snd_ac97_bus(codec->card, 0, &ops, codec, &codec->ac97_bus);
	अगर (err < 0)
		वापस err;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = codec;

	क्रम (i = 0; i < codec->num_of_codecs; i++) अणु
		ac97.num = i;
		err = snd_ac97_mixer(codec->ac97_bus, &ac97, &codec->ac97[i]);
		अगर (err < 0) अणु
			dev_err(codec->card->dev,
				   "ali mixer %d creating error.\n", i);
			अगर (i == 0)
				वापस err;
			codec->num_of_codecs = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (codec->spdअगर_support) अणु
		क्रम (idx = 0; idx < ARRAY_SIZE(snd_ali5451_mixer_spdअगर); idx++) अणु
			err = snd_ctl_add(codec->card,
					  snd_ctl_new1(&snd_ali5451_mixer_spdअगर[idx], codec));
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक ali_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ali *chip = card->निजी_data;
	काष्ठा snd_ali_image *im;
	पूर्णांक i, j;

	im = chip->image;
	अगर (!im)
		वापस 0;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	क्रम (i = 0; i < chip->num_of_codecs; i++)
		snd_ac97_suspend(chip->ac97[i]);

	spin_lock_irq(&chip->reg_lock);
	
	im->regs[ALI_MISCINT >> 2] = inl(ALI_REG(chip, ALI_MISCINT));
	/* im->regs[ALI_START >> 2] = inl(ALI_REG(chip, ALI_START)); */
	im->regs[ALI_STOP >> 2] = inl(ALI_REG(chip, ALI_STOP));
	
	/* disable all IRQ bits */
	outl(0, ALI_REG(chip, ALI_MISCINT));
	
	क्रम (i = 0; i < ALI_GLOBAL_REGS; i++) अणु	
		अगर ((i*4 == ALI_MISCINT) || (i*4 == ALI_STOP))
			जारी;
		im->regs[i] = inl(ALI_REG(chip, i*4));
	पूर्ण
	
	क्रम (i = 0; i < ALI_CHANNELS; i++) अणु
		outb(i, ALI_REG(chip, ALI_GC_CIR));
		क्रम (j = 0; j < ALI_CHANNEL_REGS; j++) 
			im->channel_regs[i][j] = inl(ALI_REG(chip, j*4 + 0xe0));
	पूर्ण

	/* stop all HW channel */
	outl(0xffffffff, ALI_REG(chip, ALI_STOP));

	spin_unlock_irq(&chip->reg_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक ali_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_ali *chip = card->निजी_data;
	काष्ठा snd_ali_image *im;
	पूर्णांक i, j;

	im = chip->image;
	अगर (!im)
		वापस 0;

	spin_lock_irq(&chip->reg_lock);
	
	क्रम (i = 0; i < ALI_CHANNELS; i++) अणु
		outb(i, ALI_REG(chip, ALI_GC_CIR));
		क्रम (j = 0; j < ALI_CHANNEL_REGS; j++) 
			outl(im->channel_regs[i][j], ALI_REG(chip, j*4 + 0xe0));
	पूर्ण
	
	क्रम (i = 0; i < ALI_GLOBAL_REGS; i++) अणु	
		अगर ((i*4 == ALI_MISCINT) || (i*4 == ALI_STOP) ||
		    (i*4 == ALI_START))
			जारी;
		outl(im->regs[i], ALI_REG(chip, i*4));
	पूर्ण
	
	/* start HW channel */
	outl(im->regs[ALI_START >> 2], ALI_REG(chip, ALI_START));
	/* restore IRQ enable bits */
	outl(im->regs[ALI_MISCINT >> 2], ALI_REG(chip, ALI_MISCINT));
	
	spin_unlock_irq(&chip->reg_lock);

	क्रम (i = 0 ; i < chip->num_of_codecs; i++)
		snd_ac97_resume(chip->ac97[i]);
	
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ali_pm, ali_suspend, ali_resume);
#घोषणा ALI_PM_OPS	&ali_pm
#अन्यथा
#घोषणा ALI_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक snd_ali_मुक्त(काष्ठा snd_ali * codec)
अणु
	अगर (codec->hw_initialized)
		snd_ali_disable_address_पूर्णांकerrupt(codec);
	अगर (codec->irq >= 0)
		मुक्त_irq(codec->irq, codec);
	अगर (codec->port)
		pci_release_regions(codec->pci);
	pci_disable_device(codec->pci);
#अगर_घोषित CONFIG_PM_SLEEP
	kमुक्त(codec->image);
#पूर्ण_अगर
	pci_dev_put(codec->pci_m1533);
	pci_dev_put(codec->pci_m7101);
	kमुक्त(codec);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_chip_init(काष्ठा snd_ali *codec)
अणु
	अचिन्हित पूर्णांक legacy;
	अचिन्हित अक्षर temp;
	काष्ठा pci_dev *pci_dev;

	dev_dbg(codec->card->dev, "chip initializing ...\n");

	अगर (snd_ali_reset_5451(codec)) अणु
		dev_err(codec->card->dev, "ali_chip_init: reset 5451 error.\n");
		वापस -1;
	पूर्ण

	अगर (codec->revision == ALI_5451_V02) अणु
        	pci_dev = codec->pci_m1533;
		pci_पढ़ो_config_byte(pci_dev, 0x59, &temp);
		temp |= 0x80;
		pci_ग_लिखो_config_byte(pci_dev, 0x59, temp);
	
		pci_dev = codec->pci_m7101;
		pci_पढ़ो_config_byte(pci_dev, 0xb8, &temp);
		temp |= 0x20;
		pci_ग_लिखो_config_byte(pci_dev, 0xB8, temp);
	पूर्ण

	pci_पढ़ो_config_dword(codec->pci, 0x44, &legacy);
	legacy &= 0xff00ff00;
	legacy |= 0x000800aa;
	pci_ग_लिखो_config_dword(codec->pci, 0x44, legacy);

	outl(0x80000001, ALI_REG(codec, ALI_GLOBAL_CONTROL));
	outl(0x00000000, ALI_REG(codec, ALI_AINTEN));
	outl(0xffffffff, ALI_REG(codec, ALI_AINT));
	outl(0x00000000, ALI_REG(codec, ALI_VOLUME));
	outb(0x10, 	 ALI_REG(codec, ALI_MPUR2));

	codec->ac97_ext_id = snd_ali_codec_peek(codec, 0, AC97_EXTENDED_ID);
	codec->ac97_ext_status = snd_ali_codec_peek(codec, 0,
						    AC97_EXTENDED_STATUS);
	अगर (codec->spdअगर_support) अणु
		snd_ali_enable_spdअगर_out(codec);
		codec->spdअगर_mask = 0x00000002;
	पूर्ण

	codec->num_of_codecs = 1;

	/* secondary codec - modem */
	अगर (inl(ALI_REG(codec, ALI_SCTRL)) & ALI_SCTRL_CODEC2_READY) अणु
		codec->num_of_codecs++;
		outl(inl(ALI_REG(codec, ALI_SCTRL)) |
		     (ALI_SCTRL_LINE_IN2 | ALI_SCTRL_GPIO_IN2 |
		      ALI_SCTRL_LINE_OUT_EN),
		     ALI_REG(codec, ALI_SCTRL));
	पूर्ण

	dev_dbg(codec->card->dev, "chip initialize succeed.\n");
	वापस 0;

पूर्ण

/* proc क्रम रेजिस्टर dump */
अटल व्योम snd_ali_proc_पढ़ो(काष्ठा snd_info_entry *entry,
			      काष्ठा snd_info_buffer *buf)
अणु
	काष्ठा snd_ali *codec = entry->निजी_data;
	पूर्णांक i;
	क्रम (i = 0; i < 256 ; i+= 4)
		snd_iम_लिखो(buf, "%02x: %08x\n", i, inl(ALI_REG(codec, i)));
पूर्ण

अटल व्योम snd_ali_proc_init(काष्ठा snd_ali *codec)
अणु
	snd_card_ro_proc_new(codec->card, "ali5451", codec, snd_ali_proc_पढ़ो);
पूर्ण

अटल पूर्णांक snd_ali_resources(काष्ठा snd_ali *codec)
अणु
	पूर्णांक err;

	dev_dbg(codec->card->dev, "resources allocation ...\n");
	err = pci_request_regions(codec->pci, "ALI 5451");
	अगर (err < 0)
		वापस err;
	codec->port = pci_resource_start(codec->pci, 0);

	अगर (request_irq(codec->pci->irq, snd_ali_card_पूर्णांकerrupt,
			IRQF_SHARED, KBUILD_MODNAME, codec)) अणु
		dev_err(codec->card->dev, "Unable to request irq.\n");
		वापस -EBUSY;
	पूर्ण
	codec->irq = codec->pci->irq;
	codec->card->sync_irq = codec->irq;
	dev_dbg(codec->card->dev, "resources allocated.\n");
	वापस 0;
पूर्ण
अटल पूर्णांक snd_ali_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_ali *codec = device->device_data;
	snd_ali_मुक्त(codec);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_create(काष्ठा snd_card *card,
			  काष्ठा pci_dev *pci,
			  पूर्णांक pcm_streams,
			  पूर्णांक spdअगर_support,
			  काष्ठा snd_ali **r_ali)
अणु
	काष्ठा snd_ali *codec;
	पूर्णांक i, err;
	अचिन्हित लघु cmdw;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_ali_dev_मुक्त,
        पूर्ण;

	*r_ali = शून्य;

	dev_dbg(card->dev, "creating ...\n");

	/* enable PCI device */
	err = pci_enable_device(pci);
	अगर (err < 0)
		वापस err;
	/* check, अगर we can restrict PCI DMA transfers to 31 bits */
	अगर (dma_set_mask_and_coherent(&pci->dev, DMA_BIT_MASK(31))) अणु
		dev_err(card->dev,
			"architecture does not support 31bit PCI busmaster DMA\n");
		pci_disable_device(pci);
		वापस -ENXIO;
	पूर्ण

	codec = kzalloc(माप(*codec), GFP_KERNEL);
	अगर (!codec) अणु
		pci_disable_device(pci);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_init(&codec->reg_lock);
	spin_lock_init(&codec->voice_alloc);

	codec->card = card;
	codec->pci = pci;
	codec->irq = -1;
	codec->revision = pci->revision;
	codec->spdअगर_support = spdअगर_support;

	अगर (pcm_streams < 1)
		pcm_streams = 1;
	अगर (pcm_streams > 32)
		pcm_streams = 32;
	
	pci_set_master(pci);
	pci_पढ़ो_config_word(pci, PCI_COMMAND, &cmdw);
	अगर ((cmdw & PCI_COMMAND_IO) != PCI_COMMAND_IO) अणु
		cmdw |= PCI_COMMAND_IO;
		pci_ग_लिखो_config_word(pci, PCI_COMMAND, cmdw);
	पूर्ण
	pci_set_master(pci);
	
	अगर (snd_ali_resources(codec)) अणु
		snd_ali_मुक्त(codec);
		वापस -EBUSY;
	पूर्ण

	codec->synth.chmap = 0;
	codec->synth.chcnt = 0;
	codec->spdअगर_mask = 0;
	codec->synth.synthcount = 0;

	अगर (codec->revision == ALI_5451_V02)
		codec->chregs.regs.ac97पढ़ो = ALI_AC97_WRITE;
	अन्यथा
		codec->chregs.regs.ac97पढ़ो = ALI_AC97_READ;
	codec->chregs.regs.ac97ग_लिखो = ALI_AC97_WRITE;

	codec->chregs.regs.start  = ALI_START;
	codec->chregs.regs.stop   = ALI_STOP;
	codec->chregs.regs.aपूर्णांक   = ALI_AINT;
	codec->chregs.regs.aपूर्णांकen = ALI_AINTEN;

	codec->chregs.data.start  = 0x00;
	codec->chregs.data.stop   = 0x00;
	codec->chregs.data.aपूर्णांक   = 0x00;
	codec->chregs.data.aपूर्णांकen = 0x00;

	/* M1533: southbridge */
	codec->pci_m1533 = pci_get_device(0x10b9, 0x1533, शून्य);
	अगर (!codec->pci_m1533) अणु
		dev_err(card->dev, "cannot find ALi 1533 chip.\n");
		snd_ali_मुक्त(codec);
		वापस -ENODEV;
	पूर्ण
	/* M7101: घातer management */
	codec->pci_m7101 = pci_get_device(0x10b9, 0x7101, शून्य);
	अगर (!codec->pci_m7101 && codec->revision == ALI_5451_V02) अणु
		dev_err(card->dev, "cannot find ALi 7101 chip.\n");
		snd_ali_मुक्त(codec);
		वापस -ENODEV;
	पूर्ण

	dev_dbg(card->dev, "snd_device_new is called.\n");
	err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, codec, &ops);
	अगर (err < 0) अणु
		snd_ali_मुक्त(codec);
		वापस err;
	पूर्ण

	/* initialise synth voices*/
	क्रम (i = 0; i < ALI_CHANNELS; i++)
		codec->synth.voices[i].number = i;

	err = snd_ali_chip_init(codec);
	अगर (err < 0) अणु
		dev_err(card->dev, "ali create: chip init error.\n");
		वापस err;
	पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
	codec->image = kदो_स्मृति(माप(*codec->image), GFP_KERNEL);
	अगर (!codec->image)
		dev_warn(card->dev, "can't allocate apm buffer\n");
#पूर्ण_अगर

	snd_ali_enable_address_पूर्णांकerrupt(codec);
	codec->hw_initialized = 1;

	*r_ali = codec;
	dev_dbg(card->dev, "created.\n");
	वापस 0;
पूर्ण

अटल पूर्णांक snd_ali_probe(काष्ठा pci_dev *pci,
			 स्थिर काष्ठा pci_device_id *pci_id)
अणु
	काष्ठा snd_card *card;
	काष्ठा snd_ali *codec;
	पूर्णांक err;

	dev_dbg(&pci->dev, "probe ...\n");

	err = snd_card_new(&pci->dev, index, id, THIS_MODULE, 0, &card);
	अगर (err < 0)
		वापस err;

	err = snd_ali_create(card, pci, pcm_channels, spdअगर, &codec);
	अगर (err < 0)
		जाओ error;
	card->निजी_data = codec;

	dev_dbg(&pci->dev, "mixer building ...\n");
	err = snd_ali_mixer(codec);
	अगर (err < 0)
		जाओ error;
	
	dev_dbg(&pci->dev, "pcm building ...\n");
	err = snd_ali_build_pcms(codec);
	अगर (err < 0)
		जाओ error;

	snd_ali_proc_init(codec);

	म_नकल(card->driver, "ALI5451");
	म_नकल(card->लघुname, "ALI 5451");
	
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %i",
		card->लघुname, codec->port, codec->irq);

	dev_dbg(&pci->dev, "register card.\n");
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;

	pci_set_drvdata(pci, card);
	वापस 0;

 error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_ali_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver ali5451_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_ali_ids,
	.probe = snd_ali_probe,
	.हटाओ = snd_ali_हटाओ,
	.driver = अणु
		.pm = ALI_PM_OPS,
	पूर्ण,
पूर्ण;                                

module_pci_driver(ali5451_driver);
