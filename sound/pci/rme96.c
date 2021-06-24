<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम RME Digi96, Digi96/8 and Digi96/8 PRO/PAD/PST audio
 *   पूर्णांकerfaces 
 *
 *	Copyright (c) 2000, 2001 Anders Torger <torger@ludd.luth.se>
 *    
 *      Thanks to Henk Hesselink <henk@anda.nl> क्रम the analog volume control
 *      code.
 */      

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>

/* note, two last pcis should be equal, it is not a bug */

MODULE_AUTHOR("Anders Torger <torger@ludd.luth.se>");
MODULE_DESCRIPTION("RME Digi96, Digi96/8, Digi96/8 PRO, Digi96/8 PST, "
		   "Digi96/8 PAD");
MODULE_LICENSE("GPL");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for RME Digi96 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for RME Digi96 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable RME Digi96 soundcard.");

/*
 * Defines क्रम RME Digi96 series, from पूर्णांकernal RME reference करोcuments
 * dated 12.01.00
 */

#घोषणा RME96_SPDIF_NCHANNELS 2

/* Playback and capture buffer size */
#घोषणा RME96_BUFFER_SIZE 0x10000

/* IO area size */
#घोषणा RME96_IO_SIZE 0x60000

/* IO area offsets */
#घोषणा RME96_IO_PLAY_BUFFER      0x0
#घोषणा RME96_IO_REC_BUFFER       0x10000
#घोषणा RME96_IO_CONTROL_REGISTER 0x20000
#घोषणा RME96_IO_ADDITIONAL_REG   0x20004
#घोषणा RME96_IO_CONFIRM_PLAY_IRQ 0x20008
#घोषणा RME96_IO_CONFIRM_REC_IRQ  0x2000C
#घोषणा RME96_IO_SET_PLAY_POS     0x40000
#घोषणा RME96_IO_RESET_PLAY_POS   0x4FFFC
#घोषणा RME96_IO_SET_REC_POS      0x50000
#घोषणा RME96_IO_RESET_REC_POS    0x5FFFC
#घोषणा RME96_IO_GET_PLAY_POS     0x20000
#घोषणा RME96_IO_GET_REC_POS      0x30000

/* Write control रेजिस्टर bits */
#घोषणा RME96_WCR_START     (1 << 0)
#घोषणा RME96_WCR_START_2   (1 << 1)
#घोषणा RME96_WCR_GAIN_0    (1 << 2)
#घोषणा RME96_WCR_GAIN_1    (1 << 3)
#घोषणा RME96_WCR_MODE24    (1 << 4)
#घोषणा RME96_WCR_MODE24_2  (1 << 5)
#घोषणा RME96_WCR_BM        (1 << 6)
#घोषणा RME96_WCR_BM_2      (1 << 7)
#घोषणा RME96_WCR_ADAT      (1 << 8)
#घोषणा RME96_WCR_FREQ_0    (1 << 9)
#घोषणा RME96_WCR_FREQ_1    (1 << 10)
#घोषणा RME96_WCR_DS        (1 << 11)
#घोषणा RME96_WCR_PRO       (1 << 12)
#घोषणा RME96_WCR_EMP       (1 << 13)
#घोषणा RME96_WCR_SEL       (1 << 14)
#घोषणा RME96_WCR_MASTER    (1 << 15)
#घोषणा RME96_WCR_PD        (1 << 16)
#घोषणा RME96_WCR_INP_0     (1 << 17)
#घोषणा RME96_WCR_INP_1     (1 << 18)
#घोषणा RME96_WCR_THRU_0    (1 << 19)
#घोषणा RME96_WCR_THRU_1    (1 << 20)
#घोषणा RME96_WCR_THRU_2    (1 << 21)
#घोषणा RME96_WCR_THRU_3    (1 << 22)
#घोषणा RME96_WCR_THRU_4    (1 << 23)
#घोषणा RME96_WCR_THRU_5    (1 << 24)
#घोषणा RME96_WCR_THRU_6    (1 << 25)
#घोषणा RME96_WCR_THRU_7    (1 << 26)
#घोषणा RME96_WCR_DOLBY     (1 << 27)
#घोषणा RME96_WCR_MONITOR_0 (1 << 28)
#घोषणा RME96_WCR_MONITOR_1 (1 << 29)
#घोषणा RME96_WCR_ISEL      (1 << 30)
#घोषणा RME96_WCR_IDIS      (1 << 31)

#घोषणा RME96_WCR_BITPOS_GAIN_0 2
#घोषणा RME96_WCR_BITPOS_GAIN_1 3
#घोषणा RME96_WCR_BITPOS_FREQ_0 9
#घोषणा RME96_WCR_BITPOS_FREQ_1 10
#घोषणा RME96_WCR_BITPOS_INP_0 17
#घोषणा RME96_WCR_BITPOS_INP_1 18
#घोषणा RME96_WCR_BITPOS_MONITOR_0 28
#घोषणा RME96_WCR_BITPOS_MONITOR_1 29

/* Read control रेजिस्टर bits */
#घोषणा RME96_RCR_AUDIO_ADDR_MASK 0xFFFF
#घोषणा RME96_RCR_IRQ_2     (1 << 16)
#घोषणा RME96_RCR_T_OUT     (1 << 17)
#घोषणा RME96_RCR_DEV_ID_0  (1 << 21)
#घोषणा RME96_RCR_DEV_ID_1  (1 << 22)
#घोषणा RME96_RCR_LOCK      (1 << 23)
#घोषणा RME96_RCR_VERF      (1 << 26)
#घोषणा RME96_RCR_F0        (1 << 27)
#घोषणा RME96_RCR_F1        (1 << 28)
#घोषणा RME96_RCR_F2        (1 << 29)
#घोषणा RME96_RCR_AUTOSYNC  (1 << 30)
#घोषणा RME96_RCR_IRQ       (1 << 31)

#घोषणा RME96_RCR_BITPOS_F0 27
#घोषणा RME96_RCR_BITPOS_F1 28
#घोषणा RME96_RCR_BITPOS_F2 29

/* Additional रेजिस्टर bits */
#घोषणा RME96_AR_WSEL       (1 << 0)
#घोषणा RME96_AR_ANALOG     (1 << 1)
#घोषणा RME96_AR_FREQPAD_0  (1 << 2)
#घोषणा RME96_AR_FREQPAD_1  (1 << 3)
#घोषणा RME96_AR_FREQPAD_2  (1 << 4)
#घोषणा RME96_AR_PD2        (1 << 5)
#घोषणा RME96_AR_DAC_EN     (1 << 6)
#घोषणा RME96_AR_CLATCH     (1 << 7)
#घोषणा RME96_AR_CCLK       (1 << 8)
#घोषणा RME96_AR_CDATA      (1 << 9)

#घोषणा RME96_AR_BITPOS_F0 2
#घोषणा RME96_AR_BITPOS_F1 3
#घोषणा RME96_AR_BITPOS_F2 4

/* Monitor tracks */
#घोषणा RME96_MONITOR_TRACKS_1_2 0
#घोषणा RME96_MONITOR_TRACKS_3_4 1
#घोषणा RME96_MONITOR_TRACKS_5_6 2
#घोषणा RME96_MONITOR_TRACKS_7_8 3

/* Attenuation */
#घोषणा RME96_ATTENUATION_0 0
#घोषणा RME96_ATTENUATION_6 1
#घोषणा RME96_ATTENUATION_12 2
#घोषणा RME96_ATTENUATION_18 3

/* Input types */
#घोषणा RME96_INPUT_OPTICAL 0
#घोषणा RME96_INPUT_COAXIAL 1
#घोषणा RME96_INPUT_INTERNAL 2
#घोषणा RME96_INPUT_XLR 3
#घोषणा RME96_INPUT_ANALOG 4

/* Clock modes */
#घोषणा RME96_CLOCKMODE_SLAVE 0
#घोषणा RME96_CLOCKMODE_MASTER 1
#घोषणा RME96_CLOCKMODE_WORDCLOCK 2

/* Block sizes in bytes */
#घोषणा RME96_SMALL_BLOCK_SIZE 2048
#घोषणा RME96_LARGE_BLOCK_SIZE 8192

/* Volume control */
#घोषणा RME96_AD1852_VOL_BITS 14
#घोषणा RME96_AD1855_VOL_BITS 10

/* Defines क्रम snd_rme96_trigger */
#घोषणा RME96_TB_START_PLAYBACK 1
#घोषणा RME96_TB_START_CAPTURE 2
#घोषणा RME96_TB_STOP_PLAYBACK 4
#घोषणा RME96_TB_STOP_CAPTURE 8
#घोषणा RME96_TB_RESET_PLAYPOS 16
#घोषणा RME96_TB_RESET_CAPTUREPOS 32
#घोषणा RME96_TB_CLEAR_PLAYBACK_IRQ 64
#घोषणा RME96_TB_CLEAR_CAPTURE_IRQ 128
#घोषणा RME96_RESUME_PLAYBACK	(RME96_TB_START_PLAYBACK)
#घोषणा RME96_RESUME_CAPTURE	(RME96_TB_START_CAPTURE)
#घोषणा RME96_RESUME_BOTH	(RME96_RESUME_PLAYBACK \
				| RME96_RESUME_CAPTURE)
#घोषणा RME96_START_PLAYBACK	(RME96_TB_START_PLAYBACK \
				| RME96_TB_RESET_PLAYPOS)
#घोषणा RME96_START_CAPTURE	(RME96_TB_START_CAPTURE \
				| RME96_TB_RESET_CAPTUREPOS)
#घोषणा RME96_START_BOTH	(RME96_START_PLAYBACK \
				| RME96_START_CAPTURE)
#घोषणा RME96_STOP_PLAYBACK	(RME96_TB_STOP_PLAYBACK \
				| RME96_TB_CLEAR_PLAYBACK_IRQ)
#घोषणा RME96_STOP_CAPTURE	(RME96_TB_STOP_CAPTURE \
				| RME96_TB_CLEAR_CAPTURE_IRQ)
#घोषणा RME96_STOP_BOTH		(RME96_STOP_PLAYBACK \
				| RME96_STOP_CAPTURE)

काष्ठा rme96 अणु
	spinlock_t    lock;
	पूर्णांक irq;
	अचिन्हित दीर्घ port;
	व्योम __iomem *iobase;
	
	u32 wcreg;    /* cached ग_लिखो control रेजिस्टर value */
	u32 wcreg_spdअगर;		/* S/PDIF setup */
	u32 wcreg_spdअगर_stream;		/* S/PDIF setup (temporary) */
	u32 rcreg;    /* cached पढ़ो control रेजिस्टर value */
	u32 areg;     /* cached additional रेजिस्टर value */
	u16 vol[2]; /* cached volume of analog output */

	u8 rev; /* card revision number */

#अगर_घोषित CONFIG_PM_SLEEP
	u32 playback_poपूर्णांकer;
	u32 capture_poपूर्णांकer;
	व्योम *playback_suspend_buffer;
	व्योम *capture_suspend_buffer;
#पूर्ण_अगर

	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;

	पूर्णांक playback_frlog; /* log2 of framesize */
	पूर्णांक capture_frlog;
	
        माप_प्रकार playback_periodsize; /* in bytes, zero अगर not used */
	माप_प्रकार capture_periodsize; /* in bytes, zero अगर not used */

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *spdअगर_pcm;
	काष्ठा snd_pcm *adat_pcm; 
	काष्ठा pci_dev     *pci;
	काष्ठा snd_kcontrol   *spdअगर_ctl;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_rme96_ids[] = अणु
	अणु PCI_VDEVICE(XILINX, PCI_DEVICE_ID_RME_DIGI96), 0, पूर्ण,
	अणु PCI_VDEVICE(XILINX, PCI_DEVICE_ID_RME_DIGI96_8), 0, पूर्ण,
	अणु PCI_VDEVICE(XILINX, PCI_DEVICE_ID_RME_DIGI96_8_PRO), 0, पूर्ण,
	अणु PCI_VDEVICE(XILINX, PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST), 0, पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_rme96_ids);

#घोषणा RME96_ISPLAYING(rme96) ((rme96)->wcreg & RME96_WCR_START)
#घोषणा RME96_ISRECORDING(rme96) ((rme96)->wcreg & RME96_WCR_START_2)
#घोषणा	RME96_HAS_ANALOG_IN(rme96) ((rme96)->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST)
#घोषणा	RME96_HAS_ANALOG_OUT(rme96) ((rme96)->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PRO || \
				     (rme96)->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST)
#घोषणा	RME96_DAC_IS_1852(rme96) (RME96_HAS_ANALOG_OUT(rme96) && (rme96)->rev >= 4)
#घोषणा	RME96_DAC_IS_1855(rme96) (((rme96)->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST && (rme96)->rev < 4) || \
			          ((rme96)->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PRO && (rme96)->rev == 2))
#घोषणा	RME96_185X_MAX_OUT(rme96) ((1 << (RME96_DAC_IS_1852(rme96) ? RME96_AD1852_VOL_BITS : RME96_AD1855_VOL_BITS)) - 1)

अटल पूर्णांक
snd_rme96_playback_prepare(काष्ठा snd_pcm_substream *substream);

अटल पूर्णांक
snd_rme96_capture_prepare(काष्ठा snd_pcm_substream *substream);

अटल पूर्णांक
snd_rme96_playback_trigger(काष्ठा snd_pcm_substream *substream, 
			   पूर्णांक cmd);

अटल पूर्णांक
snd_rme96_capture_trigger(काष्ठा snd_pcm_substream *substream, 
			  पूर्णांक cmd);

अटल snd_pcm_uframes_t
snd_rme96_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream);

अटल snd_pcm_uframes_t
snd_rme96_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream);

अटल व्योम snd_rme96_proc_init(काष्ठा rme96 *rme96);

अटल पूर्णांक
snd_rme96_create_चयनes(काष्ठा snd_card *card,
			  काष्ठा rme96 *rme96);

अटल पूर्णांक
snd_rme96_getinputtype(काष्ठा rme96 *rme96);

अटल अंतरभूत अचिन्हित पूर्णांक
snd_rme96_playback_ptr(काष्ठा rme96 *rme96)
अणु
	वापस (पढ़ोl(rme96->iobase + RME96_IO_GET_PLAY_POS)
		& RME96_RCR_AUDIO_ADDR_MASK) >> rme96->playback_frlog;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
snd_rme96_capture_ptr(काष्ठा rme96 *rme96)
अणु
	वापस (पढ़ोl(rme96->iobase + RME96_IO_GET_REC_POS)
		& RME96_RCR_AUDIO_ADDR_MASK) >> rme96->capture_frlog;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_silence(काष्ठा snd_pcm_substream *substream,
			   पूर्णांक channel, अचिन्हित दीर्घ pos, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);

	स_रखो_io(rme96->iobase + RME96_IO_PLAY_BUFFER + pos,
		  0, count);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_copy(काष्ठा snd_pcm_substream *substream,
			पूर्णांक channel, अचिन्हित दीर्घ pos,
			व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);

	वापस copy_from_user_toio(rme96->iobase + RME96_IO_PLAY_BUFFER + pos,
				   src, count);
पूर्ण

अटल पूर्णांक
snd_rme96_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
			       पूर्णांक channel, अचिन्हित दीर्घ pos,
			       व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);

	स_नकल_toio(rme96->iobase + RME96_IO_PLAY_BUFFER + pos, src, count);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_copy(काष्ठा snd_pcm_substream *substream,
		       पूर्णांक channel, अचिन्हित दीर्घ pos,
		       व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);

	वापस copy_to_user_fromio(dst,
				   rme96->iobase + RME96_IO_REC_BUFFER + pos,
				   count);
पूर्ण

अटल पूर्णांक
snd_rme96_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
			      पूर्णांक channel, अचिन्हित दीर्घ pos,
			      व्योम *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);

	स_नकल_fromio(dst, rme96->iobase + RME96_IO_REC_BUFFER + pos, count);
	वापस 0;
पूर्ण

/*
 * Digital output capabilities (S/PDIF)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme96_playback_spdअगर_info =
अणु
	.info =		     (SNDRV_PCM_INFO_MMAP_IOMEM |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_SYNC_START |
			      SNDRV_PCM_INFO_RESUME |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =	     (SNDRV_PCM_FMTBIT_S16_LE |
			      SNDRV_PCM_FMTBIT_S32_LE),
	.rates =	     (SNDRV_PCM_RATE_32000 |
			      SNDRV_PCM_RATE_44100 | 
			      SNDRV_PCM_RATE_48000 | 
			      SNDRV_PCM_RATE_64000 |
			      SNDRV_PCM_RATE_88200 | 
			      SNDRV_PCM_RATE_96000),
	.rate_min =	     32000,
	.rate_max =	     96000,
	.channels_min =	     2,
	.channels_max =	     2,
	.buffer_bytes_max =  RME96_BUFFER_SIZE,
	.period_bytes_min =  RME96_SMALL_BLOCK_SIZE,
	.period_bytes_max =  RME96_LARGE_BLOCK_SIZE,
	.periods_min =	     RME96_BUFFER_SIZE / RME96_LARGE_BLOCK_SIZE,
	.periods_max =	     RME96_BUFFER_SIZE / RME96_SMALL_BLOCK_SIZE,
	.fअगरo_size =	     0,
पूर्ण;

/*
 * Digital input capabilities (S/PDIF)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme96_capture_spdअगर_info =
अणु
	.info =		     (SNDRV_PCM_INFO_MMAP_IOMEM |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_SYNC_START |
			      SNDRV_PCM_INFO_RESUME |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =	     (SNDRV_PCM_FMTBIT_S16_LE |
			      SNDRV_PCM_FMTBIT_S32_LE),
	.rates =	     (SNDRV_PCM_RATE_32000 |
			      SNDRV_PCM_RATE_44100 | 
			      SNDRV_PCM_RATE_48000 | 
			      SNDRV_PCM_RATE_64000 |
			      SNDRV_PCM_RATE_88200 | 
			      SNDRV_PCM_RATE_96000),
	.rate_min =	     32000,
	.rate_max =	     96000,
	.channels_min =	     2,
	.channels_max =	     2,
	.buffer_bytes_max =  RME96_BUFFER_SIZE,
	.period_bytes_min =  RME96_SMALL_BLOCK_SIZE,
	.period_bytes_max =  RME96_LARGE_BLOCK_SIZE,
	.periods_min =	     RME96_BUFFER_SIZE / RME96_LARGE_BLOCK_SIZE,
	.periods_max =	     RME96_BUFFER_SIZE / RME96_SMALL_BLOCK_SIZE,
	.fअगरo_size =	     0,
पूर्ण;

/*
 * Digital output capabilities (ADAT)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme96_playback_adat_info =
अणु
	.info =		     (SNDRV_PCM_INFO_MMAP_IOMEM |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_SYNC_START |
			      SNDRV_PCM_INFO_RESUME |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =	     (SNDRV_PCM_FMTBIT_S16_LE |
			      SNDRV_PCM_FMTBIT_S32_LE),
	.rates =             (SNDRV_PCM_RATE_44100 | 
			      SNDRV_PCM_RATE_48000),
	.rate_min =          44100,
	.rate_max =          48000,
	.channels_min =      8,
	.channels_max =	     8,
	.buffer_bytes_max =  RME96_BUFFER_SIZE,
	.period_bytes_min =  RME96_SMALL_BLOCK_SIZE,
	.period_bytes_max =  RME96_LARGE_BLOCK_SIZE,
	.periods_min =	     RME96_BUFFER_SIZE / RME96_LARGE_BLOCK_SIZE,
	.periods_max =	     RME96_BUFFER_SIZE / RME96_SMALL_BLOCK_SIZE,
	.fअगरo_size =	     0,
पूर्ण;

/*
 * Digital input capabilities (ADAT)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme96_capture_adat_info =
अणु
	.info =		     (SNDRV_PCM_INFO_MMAP_IOMEM |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_SYNC_START |
			      SNDRV_PCM_INFO_RESUME |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_PAUSE),
	.क्रमmats =	     (SNDRV_PCM_FMTBIT_S16_LE |
			      SNDRV_PCM_FMTBIT_S32_LE),
	.rates =	     (SNDRV_PCM_RATE_44100 | 
			      SNDRV_PCM_RATE_48000),
	.rate_min =          44100,
	.rate_max =          48000,
	.channels_min =      8,
	.channels_max =	     8,
	.buffer_bytes_max =  RME96_BUFFER_SIZE,
	.period_bytes_min =  RME96_SMALL_BLOCK_SIZE,
	.period_bytes_max =  RME96_LARGE_BLOCK_SIZE,
	.periods_min =	     RME96_BUFFER_SIZE / RME96_LARGE_BLOCK_SIZE,
	.periods_max =	     RME96_BUFFER_SIZE / RME96_SMALL_BLOCK_SIZE,
	.fअगरo_size =         0,
पूर्ण;

/*
 * The CDATA, CCLK and CLATCH bits can be used to ग_लिखो to the SPI पूर्णांकerface
 * of the AD1852 or AD1852 D/A converter on the board.  CDATA must be set up
 * on the falling edge of CCLK and be stable on the rising edge.  The rising
 * edge of CLATCH after the last data bit घड़ीs in the whole data word.
 * A fast processor could probably drive the SPI पूर्णांकerface faster than the
 * DAC can handle (3MHz क्रम the 1855, unknown क्रम the 1852).  The udelay(1)
 * limits the data rate to 500KHz and only causes a delay of 33 microsecs.
 *
 * NOTE: increased delay from 1 to 10, since there where problems setting
 * the volume.
 */
अटल व्योम
snd_rme96_ग_लिखो_SPI(काष्ठा rme96 *rme96, u16 val)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (val & 0x8000) अणु
			rme96->areg |= RME96_AR_CDATA;
		पूर्ण अन्यथा अणु
			rme96->areg &= ~RME96_AR_CDATA;
		पूर्ण
		rme96->areg &= ~(RME96_AR_CCLK | RME96_AR_CLATCH);
		ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
		udelay(10);
		rme96->areg |= RME96_AR_CCLK;
		ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
		udelay(10);
		val <<= 1;
	पूर्ण
	rme96->areg &= ~(RME96_AR_CCLK | RME96_AR_CDATA);
	rme96->areg |= RME96_AR_CLATCH;
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	udelay(10);
	rme96->areg &= ~RME96_AR_CLATCH;
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
पूर्ण

अटल व्योम
snd_rme96_apply_dac_volume(काष्ठा rme96 *rme96)
अणु
	अगर (RME96_DAC_IS_1852(rme96)) अणु
		snd_rme96_ग_लिखो_SPI(rme96, (rme96->vol[0] << 2) | 0x0);
		snd_rme96_ग_लिखो_SPI(rme96, (rme96->vol[1] << 2) | 0x2);
	पूर्ण अन्यथा अगर (RME96_DAC_IS_1855(rme96)) अणु
		snd_rme96_ग_लिखो_SPI(rme96, (rme96->vol[0] & 0x3FF) | 0x000);
		snd_rme96_ग_लिखो_SPI(rme96, (rme96->vol[1] & 0x3FF) | 0x400);
	पूर्ण
पूर्ण

अटल व्योम
snd_rme96_reset_dac(काष्ठा rme96 *rme96)
अणु
	ग_लिखोl(rme96->wcreg | RME96_WCR_PD,
	       rme96->iobase + RME96_IO_CONTROL_REGISTER);
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
पूर्ण

अटल पूर्णांक
snd_rme96_geपंचांगontracks(काष्ठा rme96 *rme96)
अणु
	वापस ((rme96->wcreg >> RME96_WCR_BITPOS_MONITOR_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_MONITOR_1) & 1) << 1);
पूर्ण

अटल पूर्णांक
snd_rme96_seपंचांगontracks(काष्ठा rme96 *rme96,
		       पूर्णांक montracks)
अणु
	अगर (montracks & 1) अणु
		rme96->wcreg |= RME96_WCR_MONITOR_0;
	पूर्ण अन्यथा अणु
		rme96->wcreg &= ~RME96_WCR_MONITOR_0;
	पूर्ण
	अगर (montracks & 2) अणु
		rme96->wcreg |= RME96_WCR_MONITOR_1;
	पूर्ण अन्यथा अणु
		rme96->wcreg &= ~RME96_WCR_MONITOR_1;
	पूर्ण
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_getattenuation(काष्ठा rme96 *rme96)
अणु
	वापस ((rme96->wcreg >> RME96_WCR_BITPOS_GAIN_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_GAIN_1) & 1) << 1);
पूर्ण

अटल पूर्णांक
snd_rme96_setattenuation(काष्ठा rme96 *rme96,
			 पूर्णांक attenuation)
अणु
	चयन (attenuation) अणु
	हाल 0:
		rme96->wcreg = (rme96->wcreg & ~RME96_WCR_GAIN_0) &
			~RME96_WCR_GAIN_1;
		अवरोध;
	हाल 1:
		rme96->wcreg = (rme96->wcreg | RME96_WCR_GAIN_0) &
			~RME96_WCR_GAIN_1;
		अवरोध;
	हाल 2:
		rme96->wcreg = (rme96->wcreg & ~RME96_WCR_GAIN_0) |
			RME96_WCR_GAIN_1;
		अवरोध;
	हाल 3:
		rme96->wcreg = (rme96->wcreg | RME96_WCR_GAIN_0) |
			RME96_WCR_GAIN_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_getrate(काष्ठा rme96 *rme96,
			  पूर्णांक *is_adat)
अणु	
	पूर्णांक n, rate;

	*is_adat = 0;
	अगर (rme96->areg & RME96_AR_ANALOG) अणु
		/* Analog input, overrides S/PDIF setting */
		n = ((rme96->areg >> RME96_AR_BITPOS_F0) & 1) +
			(((rme96->areg >> RME96_AR_BITPOS_F1) & 1) << 1);
		चयन (n) अणु
		हाल 1:
			rate = 32000;
			अवरोध;
		हाल 2:
			rate = 44100;
			अवरोध;
		हाल 3:
			rate = 48000;
			अवरोध;
		शेष:
			वापस -1;
		पूर्ण
		वापस (rme96->areg & RME96_AR_BITPOS_F2) ? rate << 1 : rate;
	पूर्ण

	rme96->rcreg = पढ़ोl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
	अगर (rme96->rcreg & RME96_RCR_LOCK) अणु
		/* ADAT rate */
		*is_adat = 1;
		अगर (rme96->rcreg & RME96_RCR_T_OUT) अणु
			वापस 48000;
		पूर्ण
		वापस 44100;
	पूर्ण

	अगर (rme96->rcreg & RME96_RCR_VERF) अणु
		वापस -1;
	पूर्ण
	
	/* S/PDIF rate */
	n = ((rme96->rcreg >> RME96_RCR_BITPOS_F0) & 1) +
		(((rme96->rcreg >> RME96_RCR_BITPOS_F1) & 1) << 1) +
		(((rme96->rcreg >> RME96_RCR_BITPOS_F2) & 1) << 2);
	
	चयन (n) अणु
	हाल 0:		
		अगर (rme96->rcreg & RME96_RCR_T_OUT) अणु
			वापस 64000;
		पूर्ण
		वापस -1;
	हाल 3: वापस 96000;
	हाल 4: वापस 88200;
	हाल 5: वापस 48000;
	हाल 6: वापस 44100;
	हाल 7: वापस 32000;
	शेष:
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_getrate(काष्ठा rme96 *rme96)
अणु
	पूर्णांक rate, dummy;

	अगर (!(rme96->wcreg & RME96_WCR_MASTER) &&
            snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
	    (rate = snd_rme96_capture_getrate(rme96, &dummy)) > 0)
	अणु
	        /* slave घड़ी */
	        वापस rate;
	पूर्ण
	rate = ((rme96->wcreg >> RME96_WCR_BITPOS_FREQ_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_FREQ_1) & 1) << 1);
	चयन (rate) अणु
	हाल 1:
		rate = 32000;
		अवरोध;
	हाल 2:
		rate = 44100;
		अवरोध;
	हाल 3:
		rate = 48000;
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	वापस (rme96->wcreg & RME96_WCR_DS) ? rate << 1 : rate;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_setrate(काष्ठा rme96 *rme96,
			   पूर्णांक rate)
अणु
	पूर्णांक ds;

	ds = rme96->wcreg & RME96_WCR_DS;
	चयन (rate) अणु
	हाल 32000:
		rme96->wcreg &= ~RME96_WCR_DS;
		rme96->wcreg = (rme96->wcreg | RME96_WCR_FREQ_0) &
			~RME96_WCR_FREQ_1;
		अवरोध;
	हाल 44100:
		rme96->wcreg &= ~RME96_WCR_DS;
		rme96->wcreg = (rme96->wcreg | RME96_WCR_FREQ_1) &
			~RME96_WCR_FREQ_0;
		अवरोध;
	हाल 48000:
		rme96->wcreg &= ~RME96_WCR_DS;
		rme96->wcreg = (rme96->wcreg | RME96_WCR_FREQ_0) |
			RME96_WCR_FREQ_1;
		अवरोध;
	हाल 64000:
		rme96->wcreg |= RME96_WCR_DS;
		rme96->wcreg = (rme96->wcreg | RME96_WCR_FREQ_0) &
			~RME96_WCR_FREQ_1;
		अवरोध;
	हाल 88200:
		rme96->wcreg |= RME96_WCR_DS;
		rme96->wcreg = (rme96->wcreg | RME96_WCR_FREQ_1) &
			~RME96_WCR_FREQ_0;
		अवरोध;
	हाल 96000:
		rme96->wcreg |= RME96_WCR_DS;
		rme96->wcreg = (rme96->wcreg | RME96_WCR_FREQ_0) |
			RME96_WCR_FREQ_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर ((!ds && rme96->wcreg & RME96_WCR_DS) ||
	    (ds && !(rme96->wcreg & RME96_WCR_DS)))
	अणु
		/* change to/from द्विगुन-speed: reset the DAC (अगर available) */
		snd_rme96_reset_dac(rme96);
		वापस 1; /* need to restore volume */
	पूर्ण अन्यथा अणु
		ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक
snd_rme96_capture_analog_setrate(काष्ठा rme96 *rme96,
				 पूर्णांक rate)
अणु
	चयन (rate) अणु
	हाल 32000:
		rme96->areg = ((rme96->areg | RME96_AR_FREQPAD_0) &
			       ~RME96_AR_FREQPAD_1) & ~RME96_AR_FREQPAD_2;
		अवरोध;
	हाल 44100:
		rme96->areg = ((rme96->areg & ~RME96_AR_FREQPAD_0) |
			       RME96_AR_FREQPAD_1) & ~RME96_AR_FREQPAD_2;
		अवरोध;
	हाल 48000:
		rme96->areg = ((rme96->areg | RME96_AR_FREQPAD_0) |
			       RME96_AR_FREQPAD_1) & ~RME96_AR_FREQPAD_2;
		अवरोध;
	हाल 64000:
		अगर (rme96->rev < 4) अणु
			वापस -EINVAL;
		पूर्ण
		rme96->areg = ((rme96->areg | RME96_AR_FREQPAD_0) &
			       ~RME96_AR_FREQPAD_1) | RME96_AR_FREQPAD_2;
		अवरोध;
	हाल 88200:
		अगर (rme96->rev < 4) अणु
			वापस -EINVAL;
		पूर्ण
		rme96->areg = ((rme96->areg & ~RME96_AR_FREQPAD_0) |
			       RME96_AR_FREQPAD_1) | RME96_AR_FREQPAD_2;
		अवरोध;
	हाल 96000:
		rme96->areg = ((rme96->areg | RME96_AR_FREQPAD_0) |
			       RME96_AR_FREQPAD_1) | RME96_AR_FREQPAD_2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_setघड़ीmode(काष्ठा rme96 *rme96,
		       पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल RME96_CLOCKMODE_SLAVE:
	        /* AutoSync */ 
		rme96->wcreg &= ~RME96_WCR_MASTER;
		rme96->areg &= ~RME96_AR_WSEL;
		अवरोध;
	हाल RME96_CLOCKMODE_MASTER:
	        /* Internal */
		rme96->wcreg |= RME96_WCR_MASTER;
		rme96->areg &= ~RME96_AR_WSEL;
		अवरोध;
	हाल RME96_CLOCKMODE_WORDCLOCK:
		/* Word घड़ी is a master mode */
		rme96->wcreg |= RME96_WCR_MASTER; 
		rme96->areg |= RME96_AR_WSEL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_अ_लोlockmode(काष्ठा rme96 *rme96)
अणु
	अगर (rme96->areg & RME96_AR_WSEL) अणु
		वापस RME96_CLOCKMODE_WORDCLOCK;
	पूर्ण
	वापस (rme96->wcreg & RME96_WCR_MASTER) ? RME96_CLOCKMODE_MASTER :
		RME96_CLOCKMODE_SLAVE;
पूर्ण

अटल पूर्णांक
snd_rme96_setinputtype(काष्ठा rme96 *rme96,
		       पूर्णांक type)
अणु
	पूर्णांक n;

	चयन (type) अणु
	हाल RME96_INPUT_OPTICAL:
		rme96->wcreg = (rme96->wcreg & ~RME96_WCR_INP_0) &
			~RME96_WCR_INP_1;
		अवरोध;
	हाल RME96_INPUT_COAXIAL:
		rme96->wcreg = (rme96->wcreg | RME96_WCR_INP_0) &
			~RME96_WCR_INP_1;
		अवरोध;
	हाल RME96_INPUT_INTERNAL:
		rme96->wcreg = (rme96->wcreg & ~RME96_WCR_INP_0) |
			RME96_WCR_INP_1;
		अवरोध;
	हाल RME96_INPUT_XLR:
		अगर ((rme96->pci->device != PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST &&
		     rme96->pci->device != PCI_DEVICE_ID_RME_DIGI96_8_PRO) ||
		    (rme96->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST &&
		     rme96->rev > 4))
		अणु
			/* Only Digi96/8 PRO and Digi96/8 PAD supports XLR */
			वापस -EINVAL;
		पूर्ण
		rme96->wcreg = (rme96->wcreg | RME96_WCR_INP_0) |
			RME96_WCR_INP_1;
		अवरोध;
	हाल RME96_INPUT_ANALOG:
		अगर (!RME96_HAS_ANALOG_IN(rme96)) अणु
			वापस -EINVAL;
		पूर्ण
		rme96->areg |= RME96_AR_ANALOG;
		ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
		अगर (rme96->rev < 4) अणु
			/*
			 * Revision less than 004 करोes not support 64 and
			 * 88.2 kHz
			 */
			अगर (snd_rme96_capture_getrate(rme96, &n) == 88200) अणु
				snd_rme96_capture_analog_setrate(rme96, 44100);
			पूर्ण
			अगर (snd_rme96_capture_getrate(rme96, &n) == 64000) अणु
				snd_rme96_capture_analog_setrate(rme96, 32000);
			पूर्ण
		पूर्ण
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	अगर (type != RME96_INPUT_ANALOG && RME96_HAS_ANALOG_IN(rme96)) अणु
		rme96->areg &= ~RME96_AR_ANALOG;
		ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	पूर्ण
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_getinputtype(काष्ठा rme96 *rme96)
अणु
	अगर (rme96->areg & RME96_AR_ANALOG) अणु
		वापस RME96_INPUT_ANALOG;
	पूर्ण
	वापस ((rme96->wcreg >> RME96_WCR_BITPOS_INP_0) & 1) +
		(((rme96->wcreg >> RME96_WCR_BITPOS_INP_1) & 1) << 1);
पूर्ण

अटल व्योम
snd_rme96_setframelog(काष्ठा rme96 *rme96,
		      पूर्णांक n_channels,
		      पूर्णांक is_playback)
अणु
	पूर्णांक frlog;
	
	अगर (n_channels == 2) अणु
		frlog = 1;
	पूर्ण अन्यथा अणु
		/* assume 8 channels */
		frlog = 3;
	पूर्ण
	अगर (is_playback) अणु
		frlog += (rme96->wcreg & RME96_WCR_MODE24) ? 2 : 1;
		rme96->playback_frlog = frlog;
	पूर्ण अन्यथा अणु
		frlog += (rme96->wcreg & RME96_WCR_MODE24_2) ? 2 : 1;
		rme96->capture_frlog = frlog;
	पूर्ण
पूर्ण

अटल पूर्णांक
snd_rme96_playback_setक्रमmat(काष्ठा rme96 *rme96, snd_pcm_क्रमmat_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		rme96->wcreg &= ~RME96_WCR_MODE24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		rme96->wcreg |= RME96_WCR_MODE24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_setक्रमmat(काष्ठा rme96 *rme96, snd_pcm_क्रमmat_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		rme96->wcreg &= ~RME96_WCR_MODE24_2;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		rme96->wcreg |= RME96_WCR_MODE24_2;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल व्योम
snd_rme96_set_period_properties(काष्ठा rme96 *rme96,
				माप_प्रकार period_bytes)
अणु
	चयन (period_bytes) अणु
	हाल RME96_LARGE_BLOCK_SIZE:
		rme96->wcreg &= ~RME96_WCR_ISEL;
		अवरोध;
	हाल RME96_SMALL_BLOCK_SIZE:
		rme96->wcreg |= RME96_WCR_ISEL;
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	rme96->wcreg &= ~RME96_WCR_IDIS;
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
पूर्ण

अटल पूर्णांक
snd_rme96_playback_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err, rate, dummy;
	bool apply_dac_volume = false;

	runसमय->dma_area = (व्योम __क्रमce *)(rme96->iobase +
					     RME96_IO_PLAY_BUFFER);
	runसमय->dma_addr = rme96->port + RME96_IO_PLAY_BUFFER;
	runसमय->dma_bytes = RME96_BUFFER_SIZE;

	spin_lock_irq(&rme96->lock);
	अगर (!(rme96->wcreg & RME96_WCR_MASTER) &&
            snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
	    (rate = snd_rme96_capture_getrate(rme96, &dummy)) > 0)
	अणु
                /* slave घड़ी */
                अगर ((पूर्णांक)params_rate(params) != rate) अणु
			err = -EIO;
			जाओ error;
		पूर्ण
	पूर्ण अन्यथा अणु
		err = snd_rme96_playback_setrate(rme96, params_rate(params));
		अगर (err < 0)
			जाओ error;
		apply_dac_volume = err > 0; /* need to restore volume later? */
	पूर्ण

	err = snd_rme96_playback_setक्रमmat(rme96, params_क्रमmat(params));
	अगर (err < 0)
		जाओ error;
	snd_rme96_setframelog(rme96, params_channels(params), 1);
	अगर (rme96->capture_periodsize != 0) अणु
		अगर (params_period_size(params) << rme96->playback_frlog !=
		    rme96->capture_periodsize)
		अणु
			err = -EBUSY;
			जाओ error;
		पूर्ण
	पूर्ण
	rme96->playback_periodsize =
		params_period_size(params) << rme96->playback_frlog;
	snd_rme96_set_period_properties(rme96, rme96->playback_periodsize);
	/* S/PDIF setup */
	अगर ((rme96->wcreg & RME96_WCR_ADAT) == 0) अणु
		rme96->wcreg &= ~(RME96_WCR_PRO | RME96_WCR_DOLBY | RME96_WCR_EMP);
		ग_लिखोl(rme96->wcreg |= rme96->wcreg_spdअगर_stream, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	पूर्ण

	err = 0;
 error:
	spin_unlock_irq(&rme96->lock);
	अगर (apply_dac_volume) अणु
		usleep_range(3000, 10000);
		snd_rme96_apply_dac_volume(rme96);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक err, isadat, rate;
	
	runसमय->dma_area = (व्योम __क्रमce *)(rme96->iobase +
					     RME96_IO_REC_BUFFER);
	runसमय->dma_addr = rme96->port + RME96_IO_REC_BUFFER;
	runसमय->dma_bytes = RME96_BUFFER_SIZE;

	spin_lock_irq(&rme96->lock);
	अगर ((err = snd_rme96_capture_setक्रमmat(rme96, params_क्रमmat(params))) < 0) अणु
		spin_unlock_irq(&rme96->lock);
		वापस err;
	पूर्ण
	अगर (snd_rme96_getinputtype(rme96) == RME96_INPUT_ANALOG) अणु
		अगर ((err = snd_rme96_capture_analog_setrate(rme96,
							    params_rate(params))) < 0)
		अणु
			spin_unlock_irq(&rme96->lock);
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर ((rate = snd_rme96_capture_getrate(rme96, &isadat)) > 0) अणु
                अगर ((पूर्णांक)params_rate(params) != rate) अणु
			spin_unlock_irq(&rme96->lock);
			वापस -EIO;                    
                पूर्ण
                अगर ((isadat && runसमय->hw.channels_min == 2) ||
                    (!isadat && runसमय->hw.channels_min == 8))
                अणु
			spin_unlock_irq(&rme96->lock);
			वापस -EIO;
                पूर्ण
        पूर्ण
	snd_rme96_setframelog(rme96, params_channels(params), 0);
	अगर (rme96->playback_periodsize != 0) अणु
		अगर (params_period_size(params) << rme96->capture_frlog !=
		    rme96->playback_periodsize)
		अणु
			spin_unlock_irq(&rme96->lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	rme96->capture_periodsize =
		params_period_size(params) << rme96->capture_frlog;
	snd_rme96_set_period_properties(rme96, rme96->capture_periodsize);
	spin_unlock_irq(&rme96->lock);

	वापस 0;
पूर्ण

अटल व्योम
snd_rme96_trigger(काष्ठा rme96 *rme96,
		  पूर्णांक op)
अणु
	अगर (op & RME96_TB_RESET_PLAYPOS)
		ग_लिखोl(0, rme96->iobase + RME96_IO_RESET_PLAY_POS);
	अगर (op & RME96_TB_RESET_CAPTUREPOS)
		ग_लिखोl(0, rme96->iobase + RME96_IO_RESET_REC_POS);
	अगर (op & RME96_TB_CLEAR_PLAYBACK_IRQ) अणु
		rme96->rcreg = पढ़ोl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
		अगर (rme96->rcreg & RME96_RCR_IRQ)
			ग_लिखोl(0, rme96->iobase + RME96_IO_CONFIRM_PLAY_IRQ);
	पूर्ण
	अगर (op & RME96_TB_CLEAR_CAPTURE_IRQ) अणु
		rme96->rcreg = पढ़ोl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
		अगर (rme96->rcreg & RME96_RCR_IRQ_2)
			ग_लिखोl(0, rme96->iobase + RME96_IO_CONFIRM_REC_IRQ);
	पूर्ण
	अगर (op & RME96_TB_START_PLAYBACK)
		rme96->wcreg |= RME96_WCR_START;
	अगर (op & RME96_TB_STOP_PLAYBACK)
		rme96->wcreg &= ~RME96_WCR_START;
	अगर (op & RME96_TB_START_CAPTURE)
		rme96->wcreg |= RME96_WCR_START_2;
	अगर (op & RME96_TB_STOP_CAPTURE)
		rme96->wcreg &= ~RME96_WCR_START_2;
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
पूर्ण



अटल irqवापस_t
snd_rme96_पूर्णांकerrupt(पूर्णांक irq,
		    व्योम *dev_id)
अणु
	काष्ठा rme96 *rme96 = (काष्ठा rme96 *)dev_id;

	rme96->rcreg = पढ़ोl(rme96->iobase + RME96_IO_CONTROL_REGISTER);
	/* fastpath out, to ease पूर्णांकerrupt sharing */
	अगर (!((rme96->rcreg & RME96_RCR_IRQ) ||
	      (rme96->rcreg & RME96_RCR_IRQ_2)))
	अणु
		वापस IRQ_NONE;
	पूर्ण
	
	अगर (rme96->rcreg & RME96_RCR_IRQ) अणु
		/* playback */
                snd_pcm_period_elapsed(rme96->playback_substream);
		ग_लिखोl(0, rme96->iobase + RME96_IO_CONFIRM_PLAY_IRQ);
	पूर्ण
	अगर (rme96->rcreg & RME96_RCR_IRQ_2) अणु
		/* capture */
		snd_pcm_period_elapsed(rme96->capture_substream);		
		ग_लिखोl(0, rme96->iobase + RME96_IO_CONFIRM_REC_IRQ);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक period_bytes[] = अणु RME96_SMALL_BLOCK_SIZE, RME96_LARGE_BLOCK_SIZE पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_period_bytes = अणु
	.count = ARRAY_SIZE(period_bytes),
	.list = period_bytes,
	.mask = 0
पूर्ण;

अटल व्योम
rme96_set_buffer_size_स्थिरraपूर्णांक(काष्ठा rme96 *rme96,
				 काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अचिन्हित पूर्णांक size;

	snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय, SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
				     RME96_BUFFER_SIZE);
	अगर ((size = rme96->playback_periodsize) != 0 ||
	    (size = rme96->capture_periodsize) != 0)
		snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय,
					     SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					     size);
	अन्यथा
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					   &hw_स्थिरraपूर्णांकs_period_bytes);
पूर्ण

अटल पूर्णांक
snd_rme96_playback_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
        पूर्णांक rate, dummy;
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_set_sync(substream);
	spin_lock_irq(&rme96->lock);	
	अगर (rme96->playback_substream) अणु
		spin_unlock_irq(&rme96->lock);
                वापस -EBUSY;
        पूर्ण
	rme96->wcreg &= ~RME96_WCR_ADAT;
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	rme96->playback_substream = substream;
	spin_unlock_irq(&rme96->lock);

	runसमय->hw = snd_rme96_playback_spdअगर_info;
	अगर (!(rme96->wcreg & RME96_WCR_MASTER) &&
            snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
	    (rate = snd_rme96_capture_getrate(rme96, &dummy)) > 0)
	अणु
                /* slave घड़ी */
                runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runसमय->hw.rate_min = rate;
                runसमय->hw.rate_max = rate;
	पूर्ण        
	rme96_set_buffer_size_स्थिरraपूर्णांक(rme96, runसमय);

	rme96->wcreg_spdअगर_stream = rme96->wcreg_spdअगर;
	rme96->spdअगर_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(rme96->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &rme96->spdअगर_ctl->id);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
        पूर्णांक isadat, rate;
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_set_sync(substream);
	runसमय->hw = snd_rme96_capture_spdअगर_info;
        अगर (snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
            (rate = snd_rme96_capture_getrate(rme96, &isadat)) > 0)
        अणु
                अगर (isadat) अणु
                        वापस -EIO;
                पूर्ण
                runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runसमय->hw.rate_min = rate;
                runसमय->hw.rate_max = rate;
        पूर्ण
        
	spin_lock_irq(&rme96->lock);
	अगर (rme96->capture_substream) अणु
		spin_unlock_irq(&rme96->lock);
                वापस -EBUSY;
        पूर्ण
	rme96->capture_substream = substream;
	spin_unlock_irq(&rme96->lock);
	
	rme96_set_buffer_size_स्थिरraपूर्णांक(rme96, runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_adat_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
        पूर्णांक rate, dummy;
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;        
	
	snd_pcm_set_sync(substream);
	spin_lock_irq(&rme96->lock);	
	अगर (rme96->playback_substream) अणु
		spin_unlock_irq(&rme96->lock);
                वापस -EBUSY;
        पूर्ण
	rme96->wcreg |= RME96_WCR_ADAT;
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	rme96->playback_substream = substream;
	spin_unlock_irq(&rme96->lock);
	
	runसमय->hw = snd_rme96_playback_adat_info;
	अगर (!(rme96->wcreg & RME96_WCR_MASTER) &&
            snd_rme96_getinputtype(rme96) != RME96_INPUT_ANALOG &&
	    (rate = snd_rme96_capture_getrate(rme96, &dummy)) > 0)
	अणु
                /* slave घड़ी */
                runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runसमय->hw.rate_min = rate;
                runसमय->hw.rate_max = rate;
	पूर्ण        
	rme96_set_buffer_size_स्थिरraपूर्णांक(rme96, runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_adat_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
        पूर्णांक isadat, rate;
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_set_sync(substream);
	runसमय->hw = snd_rme96_capture_adat_info;
        अगर (snd_rme96_getinputtype(rme96) == RME96_INPUT_ANALOG) अणु
                /* makes no sense to use analog input. Note that analog
                   expension cards AEB4/8-I are RME96_INPUT_INTERNAL */
                वापस -EIO;
        पूर्ण
        अगर ((rate = snd_rme96_capture_getrate(rme96, &isadat)) > 0) अणु
                अगर (!isadat) अणु
                        वापस -EIO;
                पूर्ण
                runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runसमय->hw.rate_min = rate;
                runसमय->hw.rate_max = rate;
        पूर्ण
        
	spin_lock_irq(&rme96->lock);	
	अगर (rme96->capture_substream) अणु
		spin_unlock_irq(&rme96->lock);
                वापस -EBUSY;
        पूर्ण
	rme96->capture_substream = substream;
	spin_unlock_irq(&rme96->lock);

	rme96_set_buffer_size_स्थिरraपूर्णांक(rme96, runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	पूर्णांक spdअगर = 0;

	spin_lock_irq(&rme96->lock);	
	अगर (RME96_ISPLAYING(rme96)) अणु
		snd_rme96_trigger(rme96, RME96_STOP_PLAYBACK);
	पूर्ण
	rme96->playback_substream = शून्य;
	rme96->playback_periodsize = 0;
	spdअगर = (rme96->wcreg & RME96_WCR_ADAT) == 0;
	spin_unlock_irq(&rme96->lock);
	अगर (spdअगर) अणु
		rme96->spdअगर_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(rme96->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO, &rme96->spdअगर_ctl->id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	
	spin_lock_irq(&rme96->lock);	
	अगर (RME96_ISRECORDING(rme96)) अणु
		snd_rme96_trigger(rme96, RME96_STOP_CAPTURE);
	पूर्ण
	rme96->capture_substream = शून्य;
	rme96->capture_periodsize = 0;
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	
	spin_lock_irq(&rme96->lock);	
	अगर (RME96_ISPLAYING(rme96)) अणु
		snd_rme96_trigger(rme96, RME96_STOP_PLAYBACK);
	पूर्ण
	ग_लिखोl(0, rme96->iobase + RME96_IO_RESET_PLAY_POS);
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	
	spin_lock_irq(&rme96->lock);	
	अगर (RME96_ISRECORDING(rme96)) अणु
		snd_rme96_trigger(rme96, RME96_STOP_CAPTURE);
	पूर्ण
	ग_लिखोl(0, rme96->iobase + RME96_IO_RESET_REC_POS);
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_playback_trigger(काष्ठा snd_pcm_substream *substream, 
			   पूर्णांक cmd)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	bool sync;

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (snd_pcm_substream_chip(s) == rme96)
			snd_pcm_trigger_करोne(s, substream);
	पूर्ण

	sync = (rme96->playback_substream && rme96->capture_substream) &&
	       (rme96->playback_substream->group ==
		rme96->capture_substream->group);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (!RME96_ISPLAYING(rme96)) अणु
			अगर (substream != rme96->playback_substream)
				वापस -EBUSY;
			snd_rme96_trigger(rme96, sync ? RME96_START_BOTH
						 : RME96_START_PLAYBACK);
		पूर्ण
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (RME96_ISPLAYING(rme96)) अणु
			अगर (substream != rme96->playback_substream)
				वापस -EBUSY;
			snd_rme96_trigger(rme96, sync ? RME96_STOP_BOTH
						 :  RME96_STOP_PLAYBACK);
		पूर्ण
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (RME96_ISPLAYING(rme96))
			snd_rme96_trigger(rme96, sync ? RME96_STOP_BOTH
						 : RME96_STOP_PLAYBACK);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!RME96_ISPLAYING(rme96))
			snd_rme96_trigger(rme96, sync ? RME96_RESUME_BOTH
						 : RME96_RESUME_PLAYBACK);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_capture_trigger(काष्ठा snd_pcm_substream *substream, 
			  पूर्णांक cmd)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;
	bool sync;

	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (snd_pcm_substream_chip(s) == rme96)
			snd_pcm_trigger_करोne(s, substream);
	पूर्ण

	sync = (rme96->playback_substream && rme96->capture_substream) &&
	       (rme96->playback_substream->group ==
		rme96->capture_substream->group);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (!RME96_ISRECORDING(rme96)) अणु
			अगर (substream != rme96->capture_substream)
				वापस -EBUSY;
			snd_rme96_trigger(rme96, sync ? RME96_START_BOTH
						 : RME96_START_CAPTURE);
		पूर्ण
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (RME96_ISRECORDING(rme96)) अणु
			अगर (substream != rme96->capture_substream)
				वापस -EBUSY;
			snd_rme96_trigger(rme96, sync ? RME96_STOP_BOTH
						 : RME96_STOP_CAPTURE);
		पूर्ण
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (RME96_ISRECORDING(rme96))
			snd_rme96_trigger(rme96, sync ? RME96_STOP_BOTH
						 : RME96_STOP_CAPTURE);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (!RME96_ISRECORDING(rme96))
			snd_rme96_trigger(rme96, sync ? RME96_RESUME_BOTH
						 : RME96_RESUME_CAPTURE);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
snd_rme96_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	वापस snd_rme96_playback_ptr(rme96);
पूर्ण

अटल snd_pcm_uframes_t
snd_rme96_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme96 *rme96 = snd_pcm_substream_chip(substream);
	वापस snd_rme96_capture_ptr(rme96);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_rme96_playback_spdअगर_ops = अणु
	.खोलो =		snd_rme96_playback_spdअगर_खोलो,
	.बंद =	snd_rme96_playback_बंद,
	.hw_params =	snd_rme96_playback_hw_params,
	.prepare =	snd_rme96_playback_prepare,
	.trigger =	snd_rme96_playback_trigger,
	.poपूर्णांकer =	snd_rme96_playback_poपूर्णांकer,
	.copy_user =	snd_rme96_playback_copy,
	.copy_kernel =	snd_rme96_playback_copy_kernel,
	.fill_silence =	snd_rme96_playback_silence,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme96_capture_spdअगर_ops = अणु
	.खोलो =		snd_rme96_capture_spdअगर_खोलो,
	.बंद =	snd_rme96_capture_बंद,
	.hw_params =	snd_rme96_capture_hw_params,
	.prepare =	snd_rme96_capture_prepare,
	.trigger =	snd_rme96_capture_trigger,
	.poपूर्णांकer =	snd_rme96_capture_poपूर्णांकer,
	.copy_user =	snd_rme96_capture_copy,
	.copy_kernel =	snd_rme96_capture_copy_kernel,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme96_playback_adat_ops = अणु
	.खोलो =		snd_rme96_playback_adat_खोलो,
	.बंद =	snd_rme96_playback_बंद,
	.hw_params =	snd_rme96_playback_hw_params,
	.prepare =	snd_rme96_playback_prepare,
	.trigger =	snd_rme96_playback_trigger,
	.poपूर्णांकer =	snd_rme96_playback_poपूर्णांकer,
	.copy_user =	snd_rme96_playback_copy,
	.copy_kernel =	snd_rme96_playback_copy_kernel,
	.fill_silence =	snd_rme96_playback_silence,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme96_capture_adat_ops = अणु
	.खोलो =		snd_rme96_capture_adat_खोलो,
	.बंद =	snd_rme96_capture_बंद,
	.hw_params =	snd_rme96_capture_hw_params,
	.prepare =	snd_rme96_capture_prepare,
	.trigger =	snd_rme96_capture_trigger,
	.poपूर्णांकer =	snd_rme96_capture_poपूर्णांकer,
	.copy_user =	snd_rme96_capture_copy,
	.copy_kernel =	snd_rme96_capture_copy_kernel,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल व्योम
snd_rme96_मुक्त(व्योम *निजी_data)
अणु
	काष्ठा rme96 *rme96 = (काष्ठा rme96 *)निजी_data;

	अगर (!rme96)
	        वापस;

	अगर (rme96->irq >= 0) अणु
		snd_rme96_trigger(rme96, RME96_STOP_BOTH);
		rme96->areg &= ~RME96_AR_DAC_EN;
		ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
		मुक्त_irq(rme96->irq, (व्योम *)rme96);
		rme96->irq = -1;
	पूर्ण
	अगर (rme96->iobase) अणु
		iounmap(rme96->iobase);
		rme96->iobase = शून्य;
	पूर्ण
	अगर (rme96->port) अणु
		pci_release_regions(rme96->pci);
		rme96->port = 0;
	पूर्ण
#अगर_घोषित CONFIG_PM_SLEEP
	vमुक्त(rme96->playback_suspend_buffer);
	vमुक्त(rme96->capture_suspend_buffer);
#पूर्ण_अगर
	pci_disable_device(rme96->pci);
पूर्ण

अटल व्योम
snd_rme96_मुक्त_spdअगर_pcm(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा rme96 *rme96 = pcm->निजी_data;
	rme96->spdअगर_pcm = शून्य;
पूर्ण

अटल व्योम
snd_rme96_मुक्त_adat_pcm(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा rme96 *rme96 = pcm->निजी_data;
	rme96->adat_pcm = शून्य;
पूर्ण

अटल पूर्णांक
snd_rme96_create(काष्ठा rme96 *rme96)
अणु
	काष्ठा pci_dev *pci = rme96->pci;
	पूर्णांक err;

	rme96->irq = -1;
	spin_lock_init(&rme96->lock);

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर ((err = pci_request_regions(pci, "RME96")) < 0)
		वापस err;
	rme96->port = pci_resource_start(rme96->pci, 0);

	rme96->iobase = ioremap(rme96->port, RME96_IO_SIZE);
	अगर (!rme96->iobase) अणु
		dev_err(rme96->card->dev,
			"unable to remap memory region 0x%lx-0x%lx\n",
			rme96->port, rme96->port + RME96_IO_SIZE - 1);
		वापस -ENOMEM;
	पूर्ण

	अगर (request_irq(pci->irq, snd_rme96_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, rme96)) अणु
		dev_err(rme96->card->dev, "unable to grab IRQ %d\n", pci->irq);
		वापस -EBUSY;
	पूर्ण
	rme96->irq = pci->irq;
	rme96->card->sync_irq = rme96->irq;

	/* पढ़ो the card's revision number */
	pci_पढ़ो_config_byte(pci, 8, &rme96->rev);	
	
	/* set up ALSA pcm device क्रम S/PDIF */
	अगर ((err = snd_pcm_new(rme96->card, "Digi96 IEC958", 0,
			       1, 1, &rme96->spdअगर_pcm)) < 0)
	अणु
		वापस err;
	पूर्ण
	rme96->spdअगर_pcm->निजी_data = rme96;
	rme96->spdअगर_pcm->निजी_मुक्त = snd_rme96_मुक्त_spdअगर_pcm;
	म_नकल(rme96->spdअगर_pcm->name, "Digi96 IEC958");
	snd_pcm_set_ops(rme96->spdअगर_pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_rme96_playback_spdअगर_ops);
	snd_pcm_set_ops(rme96->spdअगर_pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_rme96_capture_spdअगर_ops);

	rme96->spdअगर_pcm->info_flags = 0;

	/* set up ALSA pcm device क्रम ADAT */
	अगर (pci->device == PCI_DEVICE_ID_RME_DIGI96) अणु
		/* ADAT is not available on the base model */
		rme96->adat_pcm = शून्य;
	पूर्ण अन्यथा अणु
		अगर ((err = snd_pcm_new(rme96->card, "Digi96 ADAT", 1,
				       1, 1, &rme96->adat_pcm)) < 0)
		अणु
			वापस err;
		पूर्ण		
		rme96->adat_pcm->निजी_data = rme96;
		rme96->adat_pcm->निजी_मुक्त = snd_rme96_मुक्त_adat_pcm;
		म_नकल(rme96->adat_pcm->name, "Digi96 ADAT");
		snd_pcm_set_ops(rme96->adat_pcm, SNDRV_PCM_STREAM_PLAYBACK, &snd_rme96_playback_adat_ops);
		snd_pcm_set_ops(rme96->adat_pcm, SNDRV_PCM_STREAM_CAPTURE, &snd_rme96_capture_adat_ops);
		
		rme96->adat_pcm->info_flags = 0;
	पूर्ण

	rme96->playback_periodsize = 0;
	rme96->capture_periodsize = 0;
	
	/* make sure playback/capture is stopped, अगर by some reason active */
	snd_rme96_trigger(rme96, RME96_STOP_BOTH);
	
	/* set शेष values in रेजिस्टरs */
	rme96->wcreg =
		RME96_WCR_FREQ_1 | /* set 44.1 kHz playback */
		RME96_WCR_SEL |    /* normal playback */
		RME96_WCR_MASTER | /* set to master घड़ी mode */
		RME96_WCR_INP_0;   /* set coaxial input */

	rme96->areg = RME96_AR_FREQPAD_1; /* set 44.1 kHz analog capture */

	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	
	/* reset the ADC */
	ग_लिखोl(rme96->areg | RME96_AR_PD2,
	       rme96->iobase + RME96_IO_ADDITIONAL_REG);
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);	

	/* reset and enable the DAC (order is important). */
	snd_rme96_reset_dac(rme96);
	rme96->areg |= RME96_AR_DAC_EN;
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);

	/* reset playback and record buffer poपूर्णांकers */
	ग_लिखोl(0, rme96->iobase + RME96_IO_RESET_PLAY_POS);
	ग_लिखोl(0, rme96->iobase + RME96_IO_RESET_REC_POS);

	/* reset volume */
	rme96->vol[0] = rme96->vol[1] = 0;
	अगर (RME96_HAS_ANALOG_OUT(rme96)) अणु
		snd_rme96_apply_dac_volume(rme96);
	पूर्ण
	
	/* init चयन पूर्णांकerface */
	अगर ((err = snd_rme96_create_चयनes(rme96->card, rme96)) < 0) अणु
		वापस err;
	पूर्ण

        /* init proc पूर्णांकerface */
	snd_rme96_proc_init(rme96);
	
	वापस 0;
पूर्ण

/*
 * proc पूर्णांकerface
 */

अटल व्योम 
snd_rme96_proc_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक n;
	काष्ठा rme96 *rme96 = entry->निजी_data;
	
	rme96->rcreg = पढ़ोl(rme96->iobase + RME96_IO_CONTROL_REGISTER);

	snd_iम_लिखो(buffer, rme96->card->दीर्घname);
	snd_iम_लिखो(buffer, " (index #%d)\n", rme96->card->number + 1);

	snd_iम_लिखो(buffer, "\nGeneral settings\n");
	अगर (rme96->wcreg & RME96_WCR_IDIS) अणु
		snd_iम_लिखो(buffer, "  period size: N/A (interrupts "
			    "disabled)\n");
	पूर्ण अन्यथा अगर (rme96->wcreg & RME96_WCR_ISEL) अणु
		snd_iम_लिखो(buffer, "  period size: 2048 bytes\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  period size: 8192 bytes\n");
	पूर्ण	
	snd_iम_लिखो(buffer, "\nInput settings\n");
	चयन (snd_rme96_getinputtype(rme96)) अणु
	हाल RME96_INPUT_OPTICAL:
		snd_iम_लिखो(buffer, "  input: optical");
		अवरोध;
	हाल RME96_INPUT_COAXIAL:
		snd_iम_लिखो(buffer, "  input: coaxial");
		अवरोध;
	हाल RME96_INPUT_INTERNAL:
		snd_iम_लिखो(buffer, "  input: internal");
		अवरोध;
	हाल RME96_INPUT_XLR:
		snd_iम_लिखो(buffer, "  input: XLR");
		अवरोध;
	हाल RME96_INPUT_ANALOG:
		snd_iम_लिखो(buffer, "  input: analog");
		अवरोध;
	पूर्ण
	अगर (snd_rme96_capture_getrate(rme96, &n) < 0) अणु
		snd_iम_लिखो(buffer, "\n  sample rate: no valid signal\n");
	पूर्ण अन्यथा अणु
		अगर (n) अणु
			snd_iम_लिखो(buffer, " (8 channels)\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, " (2 channels)\n");
		पूर्ण
		snd_iम_लिखो(buffer, "  sample rate: %d Hz\n",
			    snd_rme96_capture_getrate(rme96, &n));
	पूर्ण
	अगर (rme96->wcreg & RME96_WCR_MODE24_2) अणु
		snd_iम_लिखो(buffer, "  sample format: 24 bit\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  sample format: 16 bit\n");
	पूर्ण
	
	snd_iम_लिखो(buffer, "\nOutput settings\n");
	अगर (rme96->wcreg & RME96_WCR_SEL) अणु
		snd_iम_लिखो(buffer, "  output signal: normal playback\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  output signal: same as input\n");
	पूर्ण
	snd_iम_लिखो(buffer, "  sample rate: %d Hz\n",
		    snd_rme96_playback_getrate(rme96));
	अगर (rme96->wcreg & RME96_WCR_MODE24) अणु
		snd_iम_लिखो(buffer, "  sample format: 24 bit\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  sample format: 16 bit\n");
	पूर्ण
	अगर (rme96->areg & RME96_AR_WSEL) अणु
		snd_iम_लिखो(buffer, "  sample clock source: word clock\n");
	पूर्ण अन्यथा अगर (rme96->wcreg & RME96_WCR_MASTER) अणु
		snd_iम_लिखो(buffer, "  sample clock source: internal\n");
	पूर्ण अन्यथा अगर (snd_rme96_getinputtype(rme96) == RME96_INPUT_ANALOG) अणु
		snd_iम_लिखो(buffer, "  sample clock source: autosync (internal anyway due to analog input setting)\n");
	पूर्ण अन्यथा अगर (snd_rme96_capture_getrate(rme96, &n) < 0) अणु
		snd_iम_लिखो(buffer, "  sample clock source: autosync (internal anyway due to no valid signal)\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  sample clock source: autosync\n");
	पूर्ण
	अगर (rme96->wcreg & RME96_WCR_PRO) अणु
		snd_iम_लिखो(buffer, "  format: AES/EBU (professional)\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  format: IEC958 (consumer)\n");
	पूर्ण
	अगर (rme96->wcreg & RME96_WCR_EMP) अणु
		snd_iम_लिखो(buffer, "  emphasis: on\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  emphasis: off\n");
	पूर्ण
	अगर (rme96->wcreg & RME96_WCR_DOLBY) अणु
		snd_iम_लिखो(buffer, "  non-audio (dolby): on\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  non-audio (dolby): off\n");
	पूर्ण
	अगर (RME96_HAS_ANALOG_IN(rme96)) अणु
		snd_iम_लिखो(buffer, "\nAnalog output settings\n");
		चयन (snd_rme96_geपंचांगontracks(rme96)) अणु
		हाल RME96_MONITOR_TRACKS_1_2:
			snd_iम_लिखो(buffer, "  monitored ADAT tracks: 1+2\n");
			अवरोध;
		हाल RME96_MONITOR_TRACKS_3_4:
			snd_iम_लिखो(buffer, "  monitored ADAT tracks: 3+4\n");
			अवरोध;
		हाल RME96_MONITOR_TRACKS_5_6:
			snd_iम_लिखो(buffer, "  monitored ADAT tracks: 5+6\n");
			अवरोध;
		हाल RME96_MONITOR_TRACKS_7_8:
			snd_iम_लिखो(buffer, "  monitored ADAT tracks: 7+8\n");
			अवरोध;
		पूर्ण
		चयन (snd_rme96_getattenuation(rme96)) अणु
		हाल RME96_ATTENUATION_0:
			snd_iम_लिखो(buffer, "  attenuation: 0 dB\n");
			अवरोध;
		हाल RME96_ATTENUATION_6:
			snd_iम_लिखो(buffer, "  attenuation: -6 dB\n");
			अवरोध;
		हाल RME96_ATTENUATION_12:
			snd_iम_लिखो(buffer, "  attenuation: -12 dB\n");
			अवरोध;
		हाल RME96_ATTENUATION_18:
			snd_iम_लिखो(buffer, "  attenuation: -18 dB\n");
			अवरोध;
		पूर्ण
		snd_iम_लिखो(buffer, "  volume left: %u\n", rme96->vol[0]);
		snd_iम_लिखो(buffer, "  volume right: %u\n", rme96->vol[1]);
	पूर्ण
पूर्ण

अटल व्योम snd_rme96_proc_init(काष्ठा rme96 *rme96)
अणु
	snd_card_ro_proc_new(rme96->card, "rme96", rme96, snd_rme96_proc_पढ़ो);
पूर्ण

/*
 * control पूर्णांकerface
 */

#घोषणा snd_rme96_info_loopback_control		snd_ctl_boolean_mono_info

अटल पूर्णांक
snd_rme96_get_loopback_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme96->lock);
	ucontrol->value.पूर्णांकeger.value[0] = rme96->wcreg & RME96_WCR_SEL ? 0 : 1;
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme96_put_loopback_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;
	
	val = ucontrol->value.पूर्णांकeger.value[0] ? 0 : RME96_WCR_SEL;
	spin_lock_irq(&rme96->lock);
	val = (rme96->wcreg & ~RME96_WCR_SEL) | val;
	change = val != rme96->wcreg;
	rme96->wcreg = val;
	ग_लिखोl(val, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल पूर्णांक
snd_rme96_info_inputtype_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर _texts[5] = अणु
		"Optical", "Coaxial", "Internal", "XLR", "Analog"
	पूर्ण;
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	स्थिर अक्षर *texts[5] = अणु
		_texts[0], _texts[1], _texts[2], _texts[3], _texts[4]
	पूर्ण;
	पूर्णांक num_items;
	
	चयन (rme96->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI96:
	हाल PCI_DEVICE_ID_RME_DIGI96_8:
		num_items = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PRO:
		num_items = 4;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST:
		अगर (rme96->rev > 4) अणु
			/* PST */
			num_items = 4;
			texts[3] = _texts[4]; /* Analog instead of XLR */
		पूर्ण अन्यथा अणु
			/* PAD */
			num_items = 5;
		पूर्ण
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_items, texts);
पूर्ण
अटल पूर्णांक
snd_rme96_get_inputtype_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक items = 3;
	
	spin_lock_irq(&rme96->lock);
	ucontrol->value.क्रमागतerated.item[0] = snd_rme96_getinputtype(rme96);
	
	चयन (rme96->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI96:
	हाल PCI_DEVICE_ID_RME_DIGI96_8:
		items = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PRO:
		items = 4;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST:
		अगर (rme96->rev > 4) अणु
			/* क्रम handling PST हाल, (INPUT_ANALOG is moved to INPUT_XLR */
			अगर (ucontrol->value.क्रमागतerated.item[0] == RME96_INPUT_ANALOG) अणु
				ucontrol->value.क्रमागतerated.item[0] = RME96_INPUT_XLR;
			पूर्ण
			items = 4;
		पूर्ण अन्यथा अणु
			items = 5;
		पूर्ण
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	अगर (ucontrol->value.क्रमागतerated.item[0] >= items) अणु
		ucontrol->value.क्रमागतerated.item[0] = items - 1;
	पूर्ण
	
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme96_put_inputtype_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change, items = 3;
	
	चयन (rme96->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI96:
	हाल PCI_DEVICE_ID_RME_DIGI96_8:
		items = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PRO:
		items = 4;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST:
		अगर (rme96->rev > 4) अणु
			items = 4;
		पूर्ण अन्यथा अणु
			items = 5;
		पूर्ण
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	val = ucontrol->value.क्रमागतerated.item[0] % items;
	
	/* special हाल क्रम PST */
	अगर (rme96->pci->device == PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST && rme96->rev > 4) अणु
		अगर (val == RME96_INPUT_XLR) अणु
			val = RME96_INPUT_ANALOG;
		पूर्ण
	पूर्ण
	
	spin_lock_irq(&rme96->lock);
	change = (पूर्णांक)val != snd_rme96_getinputtype(rme96);
	snd_rme96_setinputtype(rme96, val);
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल पूर्णांक
snd_rme96_info_घड़ीmode_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[3] = अणु "AutoSync", "Internal", "Word" पूर्ण;
	
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 3, texts);
पूर्ण
अटल पूर्णांक
snd_rme96_get_घड़ीmode_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme96->lock);
	ucontrol->value.क्रमागतerated.item[0] = snd_rme96_अ_लोlockmode(rme96);
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme96_put_घड़ीmode_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;
	
	val = ucontrol->value.क्रमागतerated.item[0] % 3;
	spin_lock_irq(&rme96->lock);
	change = (पूर्णांक)val != snd_rme96_अ_लोlockmode(rme96);
	snd_rme96_setघड़ीmode(rme96, val);
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल पूर्णांक
snd_rme96_info_attenuation_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"0 dB", "-6 dB", "-12 dB", "-18 dB"
	पूर्ण;
	
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण
अटल पूर्णांक
snd_rme96_get_attenuation_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme96->lock);
	ucontrol->value.क्रमागतerated.item[0] = snd_rme96_getattenuation(rme96);
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme96_put_attenuation_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;
	
	val = ucontrol->value.क्रमागतerated.item[0] % 4;
	spin_lock_irq(&rme96->lock);

	change = (पूर्णांक)val != snd_rme96_getattenuation(rme96);
	snd_rme96_setattenuation(rme96, val);
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल पूर्णांक
snd_rme96_info_montracks_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु "1+2", "3+4", "5+6", "7+8" पूर्ण;
	
	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण
अटल पूर्णांक
snd_rme96_get_montracks_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
	spin_lock_irq(&rme96->lock);
	ucontrol->value.क्रमागतerated.item[0] = snd_rme96_geपंचांगontracks(rme96);
	spin_unlock_irq(&rme96->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme96_put_montracks_control(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;
	
	val = ucontrol->value.क्रमागतerated.item[0] % 4;
	spin_lock_irq(&rme96->lock);
	change = (पूर्णांक)val != snd_rme96_geपंचांगontracks(rme96);
	snd_rme96_seपंचांगontracks(rme96, val);
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल u32 snd_rme96_convert_from_aes(काष्ठा snd_aes_iec958 *aes)
अणु
	u32 val = 0;
	val |= (aes->status[0] & IEC958_AES0_PROFESSIONAL) ? RME96_WCR_PRO : 0;
	val |= (aes->status[0] & IEC958_AES0_NONAUDIO) ? RME96_WCR_DOLBY : 0;
	अगर (val & RME96_WCR_PRO)
		val |= (aes->status[0] & IEC958_AES0_PRO_EMPHASIS_5015) ? RME96_WCR_EMP : 0;
	अन्यथा
		val |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? RME96_WCR_EMP : 0;
	वापस val;
पूर्ण

अटल व्योम snd_rme96_convert_to_aes(काष्ठा snd_aes_iec958 *aes, u32 val)
अणु
	aes->status[0] = ((val & RME96_WCR_PRO) ? IEC958_AES0_PROFESSIONAL : 0) |
			 ((val & RME96_WCR_DOLBY) ? IEC958_AES0_NONAUDIO : 0);
	अगर (val & RME96_WCR_PRO)
		aes->status[0] |= (val & RME96_WCR_EMP) ? IEC958_AES0_PRO_EMPHASIS_5015 : 0;
	अन्यथा
		aes->status[0] |= (val & RME96_WCR_EMP) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
	snd_rme96_convert_to_aes(&ucontrol->value.iec958, rme96->wcreg_spdअगर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;
	
	val = snd_rme96_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&rme96->lock);
	change = val != rme96->wcreg_spdअगर;
	rme96->wcreg_spdअगर = val;
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
	snd_rme96_convert_to_aes(&ucontrol->value.iec958, rme96->wcreg_spdअगर_stream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;
	
	val = snd_rme96_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&rme96->lock);
	change = val != rme96->wcreg_spdअगर_stream;
	rme96->wcreg_spdअगर_stream = val;
	rme96->wcreg &= ~(RME96_WCR_PRO | RME96_WCR_DOLBY | RME96_WCR_EMP);
	rme96->wcreg |= val;
	ग_लिखोl(rme96->wcreg, rme96->iobase + RME96_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme96->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme96_control_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	ucontrol->value.iec958.status[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_dac_volume_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
	
        uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
        uinfo->count = 2;
        uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = RME96_185X_MAX_OUT(rme96);
        वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_dac_volume_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&rme96->lock);
        u->value.पूर्णांकeger.value[0] = rme96->vol[0];
        u->value.पूर्णांकeger.value[1] = rme96->vol[1];
	spin_unlock_irq(&rme96->lock);

        वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme96_dac_volume_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *u)
अणु
	काष्ठा rme96 *rme96 = snd_kcontrol_chip(kcontrol);
        पूर्णांक change = 0;
	अचिन्हित पूर्णांक vol, maxvol;


	अगर (!RME96_HAS_ANALOG_OUT(rme96))
		वापस -EINVAL;
	maxvol = RME96_185X_MAX_OUT(rme96);
	spin_lock_irq(&rme96->lock);
	vol = u->value.पूर्णांकeger.value[0];
	अगर (vol != rme96->vol[0] && vol <= maxvol) अणु
		rme96->vol[0] = vol;
		change = 1;
	पूर्ण
	vol = u->value.पूर्णांकeger.value[1];
	अगर (vol != rme96->vol[1] && vol <= maxvol) अणु
		rme96->vol[1] = vol;
		change = 1;
	पूर्ण
	अगर (change)
		snd_rme96_apply_dac_volume(rme96);
	spin_unlock_irq(&rme96->lock);

        वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_rme96_controls[] = अणु
अणु
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,DEFAULT),
	.info =		snd_rme96_control_spdअगर_info,
	.get =		snd_rme96_control_spdअगर_get,
	.put =		snd_rme96_control_spdअगर_put
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PCM_STREAM),
	.info =		snd_rme96_control_spdअगर_stream_info,
	.get =		snd_rme96_control_spdअगर_stream_get,
	.put =		snd_rme96_control_spdअगर_stream_put
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,CON_MASK),
	.info =		snd_rme96_control_spdअगर_mask_info,
	.get =		snd_rme96_control_spdअगर_mask_get,
	.निजी_value = IEC958_AES0_NONAUDIO |
			IEC958_AES0_PROFESSIONAL |
			IEC958_AES0_CON_EMPHASIS
पूर्ण,
अणु
	.access =	SNDRV_CTL_ELEM_ACCESS_READ,
	.अगरace =	SNDRV_CTL_ELEM_IFACE_PCM,
	.name =		SNDRV_CTL_NAME_IEC958("",PLAYBACK,PRO_MASK),
	.info =		snd_rme96_control_spdअगर_mask_info,
	.get =		snd_rme96_control_spdअगर_mask_get,
	.निजी_value = IEC958_AES0_NONAUDIO |
			IEC958_AES0_PROFESSIONAL |
			IEC958_AES0_PRO_EMPHASIS
पूर्ण,
अणु
        .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Input Connector",
	.info =         snd_rme96_info_inputtype_control, 
	.get =          snd_rme96_get_inputtype_control,
	.put =          snd_rme96_put_inputtype_control 
पूर्ण,
अणु
        .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Loopback Input",
	.info =         snd_rme96_info_loopback_control,
	.get =          snd_rme96_get_loopback_control,
	.put =          snd_rme96_put_loopback_control
पूर्ण,
अणु
        .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Sample Clock Source",
	.info =         snd_rme96_info_घड़ीmode_control, 
	.get =          snd_rme96_get_घड़ीmode_control,
	.put =          snd_rme96_put_घड़ीmode_control
पूर्ण,
अणु
        .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Monitor Tracks",
	.info =         snd_rme96_info_montracks_control, 
	.get =          snd_rme96_get_montracks_control,
	.put =          snd_rme96_put_montracks_control
पूर्ण,
अणु
        .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "Attenuation",
	.info =         snd_rme96_info_attenuation_control, 
	.get =          snd_rme96_get_attenuation_control,
	.put =          snd_rme96_put_attenuation_control
पूर्ण,
अणु
        .अगरace =        SNDRV_CTL_ELEM_IFACE_MIXER,
	.name =         "DAC Playback Volume",
	.info =         snd_rme96_dac_volume_info,
	.get =          snd_rme96_dac_volume_get,
	.put =          snd_rme96_dac_volume_put
पूर्ण
पूर्ण;

अटल पूर्णांक
snd_rme96_create_चयनes(काष्ठा snd_card *card,
			  काष्ठा rme96 *rme96)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_kcontrol *kctl;

	क्रम (idx = 0; idx < 7; idx++) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme96_controls[idx], rme96))) < 0)
			वापस err;
		अगर (idx == 1)	/* IEC958 (S/PDIF) Stream */
			rme96->spdअगर_ctl = kctl;
	पूर्ण

	अगर (RME96_HAS_ANALOG_OUT(rme96)) अणु
		क्रम (idx = 7; idx < 10; idx++)
			अगर ((err = snd_ctl_add(card, snd_ctl_new1(&snd_rme96_controls[idx], rme96))) < 0)
				वापस err;
	पूर्ण
	
	वापस 0;
पूर्ण

/*
 * Card initialisation
 */

#अगर_घोषित CONFIG_PM_SLEEP

अटल पूर्णांक rme96_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा rme96 *rme96 = card->निजी_data;

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);

	/* save capture & playback poपूर्णांकers */
	rme96->playback_poपूर्णांकer = पढ़ोl(rme96->iobase + RME96_IO_GET_PLAY_POS)
				  & RME96_RCR_AUDIO_ADDR_MASK;
	rme96->capture_poपूर्णांकer = पढ़ोl(rme96->iobase + RME96_IO_GET_REC_POS)
				 & RME96_RCR_AUDIO_ADDR_MASK;

	/* save playback and capture buffers */
	स_नकल_fromio(rme96->playback_suspend_buffer,
		      rme96->iobase + RME96_IO_PLAY_BUFFER, RME96_BUFFER_SIZE);
	स_नकल_fromio(rme96->capture_suspend_buffer,
		      rme96->iobase + RME96_IO_REC_BUFFER, RME96_BUFFER_SIZE);

	/* disable the DAC  */
	rme96->areg &= ~RME96_AR_DAC_EN;
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	वापस 0;
पूर्ण

अटल पूर्णांक rme96_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा rme96 *rme96 = card->निजी_data;

	/* reset playback and record buffer poपूर्णांकers */
	ग_लिखोl(0, rme96->iobase + RME96_IO_SET_PLAY_POS
		  + rme96->playback_poपूर्णांकer);
	ग_लिखोl(0, rme96->iobase + RME96_IO_SET_REC_POS
		  + rme96->capture_poपूर्णांकer);

	/* restore playback and capture buffers */
	स_नकल_toio(rme96->iobase + RME96_IO_PLAY_BUFFER,
		    rme96->playback_suspend_buffer, RME96_BUFFER_SIZE);
	स_नकल_toio(rme96->iobase + RME96_IO_REC_BUFFER,
		    rme96->capture_suspend_buffer, RME96_BUFFER_SIZE);

	/* reset the ADC */
	ग_लिखोl(rme96->areg | RME96_AR_PD2,
	       rme96->iobase + RME96_IO_ADDITIONAL_REG);
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);

	/* reset and enable DAC, restore analog volume */
	snd_rme96_reset_dac(rme96);
	rme96->areg |= RME96_AR_DAC_EN;
	ग_लिखोl(rme96->areg, rme96->iobase + RME96_IO_ADDITIONAL_REG);
	अगर (RME96_HAS_ANALOG_OUT(rme96)) अणु
		usleep_range(3000, 10000);
		snd_rme96_apply_dac_volume(rme96);
	पूर्ण

	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(rme96_pm, rme96_suspend, rme96_resume);
#घोषणा RME96_PM_OPS	&rme96_pm
#अन्यथा
#घोषणा RME96_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल व्योम snd_rme96_card_मुक्त(काष्ठा snd_card *card)
अणु
	snd_rme96_मुक्त(card->निजी_data);
पूर्ण

अटल पूर्णांक
snd_rme96_probe(काष्ठा pci_dev *pci,
		स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा rme96 *rme96;
	काष्ठा snd_card *card;
	पूर्णांक err;
	u8 val;

	अगर (dev >= SNDRV_CARDS) अणु
		वापस -ENODEV;
	पूर्ण
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण
	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा rme96), &card);
	अगर (err < 0)
		वापस err;
	card->निजी_मुक्त = snd_rme96_card_मुक्त;
	rme96 = card->निजी_data;
	rme96->card = card;
	rme96->pci = pci;
	err = snd_rme96_create(rme96);
	अगर (err)
		जाओ मुक्त_card;
	
#अगर_घोषित CONFIG_PM_SLEEP
	rme96->playback_suspend_buffer = vदो_स्मृति(RME96_BUFFER_SIZE);
	अगर (!rme96->playback_suspend_buffer) अणु
		err = -ENOMEM;
		जाओ मुक्त_card;
	पूर्ण
	rme96->capture_suspend_buffer = vदो_स्मृति(RME96_BUFFER_SIZE);
	अगर (!rme96->capture_suspend_buffer) अणु
		err = -ENOMEM;
		जाओ मुक्त_card;
	पूर्ण
#पूर्ण_अगर

	म_नकल(card->driver, "Digi96");
	चयन (rme96->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI96:
		म_नकल(card->लघुname, "RME Digi96");
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8:
		म_नकल(card->लघुname, "RME Digi96/8");
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PRO:
		म_नकल(card->लघुname, "RME Digi96/8 PRO");
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI96_8_PAD_OR_PST:
		pci_पढ़ो_config_byte(rme96->pci, 8, &val);
		अगर (val < 5) अणु
			म_नकल(card->लघुname, "RME Digi96/8 PAD");
		पूर्ण अन्यथा अणु
			म_नकल(card->लघुname, "RME Digi96/8 PST");
		पूर्ण
		अवरोध;
	पूर्ण
	प्र_लिखो(card->दीर्घname, "%s at 0x%lx, irq %d", card->लघुname,
		rme96->port, rme96->irq);
	err = snd_card_रेजिस्टर(card);
	अगर (err)
		जाओ मुक्त_card;

	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
मुक्त_card:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_rme96_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver rme96_driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_rme96_ids,
	.probe = snd_rme96_probe,
	.हटाओ = snd_rme96_हटाओ,
	.driver = अणु
		.pm = RME96_PM_OPS,
	पूर्ण,
पूर्ण;

module_pci_driver(rme96_driver);
