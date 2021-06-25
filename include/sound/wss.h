<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_WSS_H
#घोषणा __SOUND_WSS_H

/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Definitions क्रम CS4231 & InterWave chips & compatible chips
 */

#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/समयr.h>

#समावेश <sound/cs4231-regs.h>

/* defines क्रम codec.mode */

#घोषणा WSS_MODE_NONE	0x0000
#घोषणा WSS_MODE_PLAY	0x0001
#घोषणा WSS_MODE_RECORD	0x0002
#घोषणा WSS_MODE_TIMER	0x0004
#घोषणा WSS_MODE_OPEN	(WSS_MODE_PLAY|WSS_MODE_RECORD|WSS_MODE_TIMER)

/* defines क्रम codec.hardware */

#घोषणा WSS_HW_DETECT        0x0000	/* let CS4231 driver detect chip */
#घोषणा WSS_HW_DETECT3	0x0001	/* allow mode 3 */
#घोषणा WSS_HW_TYPE_MASK	0xff00	/* type mask */
#घोषणा WSS_HW_CS4231_MASK   0x0100	/* CS4231 serie */
#घोषणा WSS_HW_CS4231        0x0100	/* CS4231 chip */
#घोषणा WSS_HW_CS4231A       0x0101	/* CS4231A chip */
#घोषणा WSS_HW_AD1845	0x0102	/* AD1845 chip */
#घोषणा WSS_HW_CS4232_MASK   0x0200	/* CS4232 serie (has control ports) */
#घोषणा WSS_HW_CS4232        0x0200	/* CS4232 */
#घोषणा WSS_HW_CS4232A       0x0201	/* CS4232A */
#घोषणा WSS_HW_CS4236	0x0202	/* CS4236 */
#घोषणा WSS_HW_CS4236B_MASK	0x0400	/* CS4236B serie (has extended control regs) */
#घोषणा WSS_HW_CS4235	0x0400	/* CS4235 - Crystal Clear (पंचांग) stereo enhancement */
#घोषणा WSS_HW_CS4236B       0x0401	/* CS4236B */
#घोषणा WSS_HW_CS4237B       0x0402	/* CS4237B - SRS 3D */
#घोषणा WSS_HW_CS4238B	0x0403	/* CS4238B - QSOUND 3D */
#घोषणा WSS_HW_CS4239	0x0404	/* CS4239 - Crystal Clear (पंचांग) stereo enhancement */
#घोषणा WSS_HW_AD1848_MASK	0x0800	/* AD1848 serie (half duplex) */
#घोषणा WSS_HW_AD1847		0x0801	/* AD1847 chip */
#घोषणा WSS_HW_AD1848		0x0802	/* AD1848 chip */
#घोषणा WSS_HW_CS4248		0x0803	/* CS4248 chip */
#घोषणा WSS_HW_CMI8330		0x0804	/* CMI8330 chip */
#घोषणा WSS_HW_THINKPAD		0x0805	/* Thinkpad 360/750/755 */
/* compatible, but clones */
#घोषणा WSS_HW_INTERWAVE     0x1000	/* InterWave chip */
#घोषणा WSS_HW_OPL3SA2       0x1101	/* OPL3-SA2 chip, similar to cs4231 */
#घोषणा WSS_HW_OPTI93X 	0x1102	/* Opti 930/931/933 */

/* defines क्रम codec.hwshare */
#घोषणा WSS_HWSHARE_IRQ	(1<<0)
#घोषणा WSS_HWSHARE_DMA1	(1<<1)
#घोषणा WSS_HWSHARE_DMA2	(1<<2)

/* IBM Thinkpad specअगरic stuff */
#घोषणा AD1848_THINKPAD_CTL_PORT1		0x15e8
#घोषणा AD1848_THINKPAD_CTL_PORT2		0x15e9
#घोषणा AD1848_THINKPAD_CS4248_ENABLE_BIT	0x02

काष्ठा snd_wss अणु
	अचिन्हित दीर्घ port;		/* base i/o port */
	काष्ठा resource *res_port;
	अचिन्हित दीर्घ cport;		/* control base i/o port (CS4236) */
	काष्ठा resource *res_cport;
	पूर्णांक irq;			/* IRQ line */
	पूर्णांक dma1;			/* playback DMA */
	पूर्णांक dma2;			/* record DMA */
	अचिन्हित लघु version;		/* version of CODEC chip */
	अचिन्हित लघु mode;		/* see to WSS_MODE_XXXX */
	अचिन्हित लघु hardware;	/* see to WSS_HW_XXXX */
	अचिन्हित लघु hwshare;		/* shared resources */
	अचिन्हित लघु single_dma:1,	/* क्रमced single DMA mode (GUS 16-bit */
					/* daughter board) or dma1 == dma2 */
		       ebus_flag:1,	/* SPARC: EBUS present */
		       thinkpad_flag:1;	/* Thinkpad CS4248 needs extra help */

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;
	काष्ठा snd_समयr *समयr;

	अचिन्हित अक्षर image[32];	/* रेजिस्टरs image */
	अचिन्हित अक्षर eimage[32];	/* extended रेजिस्टरs image */
	अचिन्हित अक्षर cimage[16];	/* control रेजिस्टरs image */
	पूर्णांक mce_bit;
	पूर्णांक calibrate_mute;
	पूर्णांक sw_3d_bit;
	अचिन्हित पूर्णांक p_dma_size;
	अचिन्हित पूर्णांक c_dma_size;

	spinlock_t reg_lock;
	काष्ठा mutex mce_mutex;
	काष्ठा mutex खोलो_mutex;

	पूर्णांक (*rate_स्थिरraपूर्णांक) (काष्ठा snd_pcm_runसमय *runसमय);
	व्योम (*set_playback_क्रमmat) (काष्ठा snd_wss *chip,
				     काष्ठा snd_pcm_hw_params *hw_params,
				     अचिन्हित अक्षर pdfr);
	व्योम (*set_capture_क्रमmat) (काष्ठा snd_wss *chip,
				    काष्ठा snd_pcm_hw_params *hw_params,
				    अचिन्हित अक्षर cdfr);
	व्योम (*trigger) (काष्ठा snd_wss *chip, अचिन्हित पूर्णांक what, पूर्णांक start);
#अगर_घोषित CONFIG_PM
	व्योम (*suspend) (काष्ठा snd_wss *chip);
	व्योम (*resume) (काष्ठा snd_wss *chip);
#पूर्ण_अगर
	व्योम *dma_निजी_data;
	पूर्णांक (*claim_dma) (काष्ठा snd_wss *chip,
			  व्योम *dma_निजी_data, पूर्णांक dma);
	पूर्णांक (*release_dma) (काष्ठा snd_wss *chip,
			    व्योम *dma_निजी_data, पूर्णांक dma);
पूर्ण;

/* exported functions */

व्योम snd_wss_out(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg, अचिन्हित अक्षर val);
अचिन्हित अक्षर snd_wss_in(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg);
व्योम snd_cs4236_ext_out(काष्ठा snd_wss *chip,
			अचिन्हित अक्षर reg, अचिन्हित अक्षर val);
अचिन्हित अक्षर snd_cs4236_ext_in(काष्ठा snd_wss *chip, अचिन्हित अक्षर reg);
व्योम snd_wss_mce_up(काष्ठा snd_wss *chip);
व्योम snd_wss_mce_करोwn(काष्ठा snd_wss *chip);

व्योम snd_wss_overrange(काष्ठा snd_wss *chip);

irqवापस_t snd_wss_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

स्थिर अक्षर *snd_wss_chip_id(काष्ठा snd_wss *chip);

पूर्णांक snd_wss_create(काष्ठा snd_card *card,
		      अचिन्हित दीर्घ port,
		      अचिन्हित दीर्घ cport,
		      पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		      अचिन्हित लघु hardware,
		      अचिन्हित लघु hwshare,
		      काष्ठा snd_wss **rchip);
पूर्णांक snd_wss_pcm(काष्ठा snd_wss *chip, पूर्णांक device);
पूर्णांक snd_wss_समयr(काष्ठा snd_wss *chip, पूर्णांक device);
पूर्णांक snd_wss_mixer(काष्ठा snd_wss *chip);

स्थिर काष्ठा snd_pcm_ops *snd_wss_get_pcm_ops(पूर्णांक direction);

पूर्णांक snd_cs4236_create(काष्ठा snd_card *card,
		      अचिन्हित दीर्घ port,
		      अचिन्हित दीर्घ cport,
		      पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		      अचिन्हित लघु hardware,
		      अचिन्हित लघु hwshare,
		      काष्ठा snd_wss **rchip);
पूर्णांक snd_cs4236_pcm(काष्ठा snd_wss *chip, पूर्णांक device);
पूर्णांक snd_cs4236_mixer(काष्ठा snd_wss *chip);

/*
 *  mixer library
 */

#घोषणा WSS_SINGLE(xname, xindex, reg, shअगरt, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_wss_info_single, \
  .get = snd_wss_get_single, \
  .put = snd_wss_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24) पूर्ण

पूर्णांक snd_wss_info_single(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_wss_get_single(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_wss_put_single(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);

#घोषणा WSS_DOUBLE(xname, xindex, left_reg, right_reg, shअगरt_left, shअगरt_right, mask, invert) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .name = xname, \
  .index = xindex, \
  .info = snd_wss_info_द्विगुन, \
  .get = snd_wss_get_द्विगुन, \
  .put = snd_wss_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | \
		   (shअगरt_right << 19) | (mask << 24) | (invert << 22) पूर्ण

#घोषणा WSS_SINGLE_TLV(xname, xindex, reg, shअगरt, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, \
  .index = xindex, \
  .info = snd_wss_info_single, \
  .get = snd_wss_get_single, \
  .put = snd_wss_put_single, \
  .निजी_value = reg | (shअगरt << 8) | (mask << 16) | (invert << 24), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण

#घोषणा WSS_DOUBLE_TLV(xname, xindex, left_reg, right_reg, \
			shअगरt_left, shअगरt_right, mask, invert, xtlv) \
अणु .अगरace = SNDRV_CTL_ELEM_IFACE_MIXER, \
  .access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_TLV_READ, \
  .name = xname, \
  .index = xindex, \
  .info = snd_wss_info_द्विगुन, \
  .get = snd_wss_get_द्विगुन, \
  .put = snd_wss_put_द्विगुन, \
  .निजी_value = left_reg | (right_reg << 8) | (shअगरt_left << 16) | \
		   (shअगरt_right << 19) | (mask << 24) | (invert << 22), \
  .tlv = अणु .p = (xtlv) पूर्ण पूर्ण


पूर्णांक snd_wss_info_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_info *uinfo);
पूर्णांक snd_wss_get_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);
पूर्णांक snd_wss_put_द्विगुन(काष्ठा snd_kcontrol *kcontrol,
			काष्ठा snd_ctl_elem_value *ucontrol);

#पूर्ण_अगर /* __SOUND_WSS_H */
