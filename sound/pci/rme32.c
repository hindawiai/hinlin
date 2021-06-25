<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA driver क्रम RME Digi32, Digi32/8 and Digi32 PRO audio पूर्णांकerfaces
 *
 *      Copyright (c) 2002-2004 Martin Langer <martin-langer@gmx.de>,
 *                              Pilo Chambert <pilo.c@wanaकरोo.fr>
 *
 *      Thanks to :        Anders Torger <torger@ludd.luth.se>,
 *                         Henk Hesselink <henk@anda.nl>
 *                         क्रम writing the digi96-driver 
 *                         and RME क्रम all inक्रमmations.
 * 
 * ****************************************************************************
 * 
 * Note #1 "Sek'd models" ................................... martin 2002-12-07
 * 
 * Identical soundcards by Sek'd were labeled:
 * RME Digi 32     = Sek'd Prodअगर 32
 * RME Digi 32 Pro = Sek'd Prodअगर 96
 * RME Digi 32/8   = Sek'd Prodअगर Gold
 * 
 * ****************************************************************************
 * 
 * Note #2 "full duplex mode" ............................... martin 2002-12-07
 * 
 * Full duplex करोesn't work. All cards (32, 32/8, 32Pro) are working identical
 * in this mode. Rec data and play data are using the same buffer thereक्रमe. At
 * first you have got the playing bits in the buffer and then (after playing
 * them) they were overwitten by the captured sound of the CS8412/14. Both 
 * modes (play/record) are running harmonically hand in hand in the same buffer
 * and you have only one start bit plus one पूर्णांकerrupt bit to control this 
 * paired action.
 * This is opposite to the latter rme96 where playing and capturing is totally
 * separated and so their full duplex mode is supported by alsa (using two 
 * start bits and two पूर्णांकerrupts क्रम two dअगरferent buffers). 
 * But due to the wrong sequence of playing and capturing ALSA shows no solved
 * full duplex support क्रम the rme32 at the moment. That's bad, but I'm not
 * able to solve it. Are you motivated enough to solve this problem now? Your
 * patch would be welcome!
 * 
 * ****************************************************************************
 *
 * "The story after the long seeking" -- tiwai
 *
 * Ok, the situation regarding the full duplex is now improved a bit.
 * In the fullduplex mode (given by the module parameter), the hardware buffer
 * is split to halves क्रम पढ़ो and ग_लिखो directions at the DMA poपूर्णांकer.
 * That is, the half above the current DMA poपूर्णांकer is used क्रम ग_लिखो, and
 * the half below is used क्रम पढ़ो.  To mangle this strange behavior, an
 * software पूर्णांकermediate buffer is पूर्णांकroduced.  This is, of course, not good
 * from the viewpoपूर्णांक of the data transfer efficiency.  However, this allows
 * you to use arbitrary buffer sizes, instead of the fixed I/O buffer size.
 *
 * ****************************************************************************
 */


#समावेश <linux/delay.h>
#समावेश <linux/gfp.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/pcm-indirect.h>
#समावेश <sound/asoundef.h>
#समावेश <sound/initval.h>

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;	/* Index 0-MAX */
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;	/* ID क्रम this card */
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE_PNP;	/* Enable this card */
अटल bool fullduplex[SNDRV_CARDS]; // = अणु[0 ... (SNDRV_CARDS - 1)] = 1पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for RME Digi32 soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for RME Digi32 soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable RME Digi32 soundcard.");
module_param_array(fullduplex, bool, शून्य, 0444);
MODULE_PARM_DESC(fullduplex, "Support full-duplex mode.");
MODULE_AUTHOR("Martin Langer <martin-langer@gmx.de>, Pilo Chambert <pilo.c@wanadoo.fr>");
MODULE_DESCRIPTION("RME Digi32, Digi32/8, Digi32 PRO");
MODULE_LICENSE("GPL");

/* Defines क्रम RME Digi32 series */
#घोषणा RME32_SPDIF_NCHANNELS 2

/* Playback and capture buffer size */
#घोषणा RME32_BUFFER_SIZE 0x20000

/* IO area size */
#घोषणा RME32_IO_SIZE 0x30000

/* IO area offsets */
#घोषणा RME32_IO_DATA_BUFFER        0x0
#घोषणा RME32_IO_CONTROL_REGISTER   0x20000
#घोषणा RME32_IO_GET_POS            0x20000
#घोषणा RME32_IO_CONFIRM_ACTION_IRQ 0x20004
#घोषणा RME32_IO_RESET_POS          0x20100

/* Write control रेजिस्टर bits */
#घोषणा RME32_WCR_START     (1 << 0)    /* startbit */
#घोषणा RME32_WCR_MONO      (1 << 1)    /* 0=stereo, 1=mono
                                           Setting the whole card to mono
                                           करोesn't seem to be very useful.
                                           A software-solution can handle 
                                           full-duplex with one direction in
                                           stereo and the other way in mono. 
                                           So, the hardware should work all 
                                           the समय in stereo! */
#घोषणा RME32_WCR_MODE24    (1 << 2)    /* 0=16bit, 1=32bit */
#घोषणा RME32_WCR_SEL       (1 << 3)    /* 0=input on output, 1=normal playback/capture */
#घोषणा RME32_WCR_FREQ_0    (1 << 4)    /* frequency (play) */
#घोषणा RME32_WCR_FREQ_1    (1 << 5)
#घोषणा RME32_WCR_INP_0     (1 << 6)    /* input चयन */
#घोषणा RME32_WCR_INP_1     (1 << 7)
#घोषणा RME32_WCR_RESET     (1 << 8)    /* Reset address */
#घोषणा RME32_WCR_MUTE      (1 << 9)    /* digital mute क्रम output */
#घोषणा RME32_WCR_PRO       (1 << 10)   /* 1=professional, 0=consumer */
#घोषणा RME32_WCR_DS_BM     (1 << 11)	/* 1=DoubleSpeed (only PRO-Version); 1=BlockMode (only Adat-Version) */
#घोषणा RME32_WCR_ADAT      (1 << 12)	/* Adat Mode (only Adat-Version) */
#घोषणा RME32_WCR_AUTOSYNC  (1 << 13)   /* AutoSync */
#घोषणा RME32_WCR_PD        (1 << 14)	/* DAC Reset (only PRO-Version) */
#घोषणा RME32_WCR_EMP       (1 << 15)	/* 1=Emphasis on (only PRO-Version) */

#घोषणा RME32_WCR_BITPOS_FREQ_0 4
#घोषणा RME32_WCR_BITPOS_FREQ_1 5
#घोषणा RME32_WCR_BITPOS_INP_0 6
#घोषणा RME32_WCR_BITPOS_INP_1 7

/* Read control रेजिस्टर bits */
#घोषणा RME32_RCR_AUDIO_ADDR_MASK 0x1ffff
#घोषणा RME32_RCR_LOCK      (1 << 23)   /* 1=locked, 0=not locked */
#घोषणा RME32_RCR_ERF       (1 << 26)   /* 1=Error, 0=no Error */
#घोषणा RME32_RCR_FREQ_0    (1 << 27)   /* CS841x frequency (record) */
#घोषणा RME32_RCR_FREQ_1    (1 << 28)
#घोषणा RME32_RCR_FREQ_2    (1 << 29)
#घोषणा RME32_RCR_KMODE     (1 << 30)   /* card mode: 1=PLL, 0=quartz */
#घोषणा RME32_RCR_IRQ       (1 << 31)   /* पूर्णांकerrupt */

#घोषणा RME32_RCR_BITPOS_F0 27
#घोषणा RME32_RCR_BITPOS_F1 28
#घोषणा RME32_RCR_BITPOS_F2 29

/* Input types */
#घोषणा RME32_INPUT_OPTICAL 0
#घोषणा RME32_INPUT_COAXIAL 1
#घोषणा RME32_INPUT_INTERNAL 2
#घोषणा RME32_INPUT_XLR 3

/* Clock modes */
#घोषणा RME32_CLOCKMODE_SLAVE 0
#घोषणा RME32_CLOCKMODE_MASTER_32 1
#घोषणा RME32_CLOCKMODE_MASTER_44 2
#घोषणा RME32_CLOCKMODE_MASTER_48 3

/* Block sizes in bytes */
#घोषणा RME32_BLOCK_SIZE 8192

/* Software पूर्णांकermediate buffer (max) size */
#घोषणा RME32_MID_BUFFER_SIZE (1024*1024)

/* Hardware revisions */
#घोषणा RME32_32_REVISION 192
#घोषणा RME32_328_REVISION_OLD 100
#घोषणा RME32_328_REVISION_NEW 101
#घोषणा RME32_PRO_REVISION_WITH_8412 192
#घोषणा RME32_PRO_REVISION_WITH_8414 150


काष्ठा rme32 अणु
	spinlock_t lock;
	पूर्णांक irq;
	अचिन्हित दीर्घ port;
	व्योम __iomem *iobase;

	u32 wcreg;		/* cached ग_लिखो control रेजिस्टर value */
	u32 wcreg_spdअगर;	/* S/PDIF setup */
	u32 wcreg_spdअगर_stream;	/* S/PDIF setup (temporary) */
	u32 rcreg;		/* cached पढ़ो control रेजिस्टर value */

	u8 rev;			/* card revision number */

	काष्ठा snd_pcm_substream *playback_substream;
	काष्ठा snd_pcm_substream *capture_substream;

	पूर्णांक playback_frlog;	/* log2 of framesize */
	पूर्णांक capture_frlog;

	माप_प्रकार playback_periodsize;	/* in bytes, zero अगर not used */
	माप_प्रकार capture_periodsize;	/* in bytes, zero अगर not used */

	अचिन्हित पूर्णांक fullduplex_mode;
	पूर्णांक running;

	काष्ठा snd_pcm_indirect playback_pcm;
	काष्ठा snd_pcm_indirect capture_pcm;

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *spdअगर_pcm;
	काष्ठा snd_pcm *adat_pcm;
	काष्ठा pci_dev *pci;
	काष्ठा snd_kcontrol *spdअगर_ctl;
पूर्ण;

अटल स्थिर काष्ठा pci_device_id snd_rme32_ids[] = अणु
	अणुPCI_VDEVICE(XILINX_RME, PCI_DEVICE_ID_RME_DIGI32), 0,पूर्ण,
	अणुPCI_VDEVICE(XILINX_RME, PCI_DEVICE_ID_RME_DIGI32_8), 0,पूर्ण,
	अणुPCI_VDEVICE(XILINX_RME, PCI_DEVICE_ID_RME_DIGI32_PRO), 0,पूर्ण,
	अणु0,पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, snd_rme32_ids);

#घोषणा RME32_ISWORKING(rme32) ((rme32)->wcreg & RME32_WCR_START)
#घोषणा RME32_PRO_WITH_8414(rme32) ((rme32)->pci->device == PCI_DEVICE_ID_RME_DIGI32_PRO && (rme32)->rev == RME32_PRO_REVISION_WITH_8414)

अटल पूर्णांक snd_rme32_playback_prepare(काष्ठा snd_pcm_substream *substream);

अटल पूर्णांक snd_rme32_capture_prepare(काष्ठा snd_pcm_substream *substream);

अटल पूर्णांक snd_rme32_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);

अटल व्योम snd_rme32_proc_init(काष्ठा rme32 * rme32);

अटल पूर्णांक snd_rme32_create_चयनes(काष्ठा snd_card *card, काष्ठा rme32 * rme32);

अटल अंतरभूत अचिन्हित पूर्णांक snd_rme32_pcm_byteptr(काष्ठा rme32 * rme32)
अणु
	वापस (पढ़ोl(rme32->iobase + RME32_IO_GET_POS)
		& RME32_RCR_AUDIO_ADDR_MASK);
पूर्ण

/* silence callback क्रम halfduplex mode */
अटल पूर्णांक snd_rme32_playback_silence(काष्ठा snd_pcm_substream *substream,
				      पूर्णांक channel, अचिन्हित दीर्घ pos,
				      अचिन्हित दीर्घ count)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	स_रखो_io(rme32->iobase + RME32_IO_DATA_BUFFER + pos, 0, count);
	वापस 0;
पूर्ण

/* copy callback क्रम halfduplex mode */
अटल पूर्णांक snd_rme32_playback_copy(काष्ठा snd_pcm_substream *substream,
				   पूर्णांक channel, अचिन्हित दीर्घ pos,
				   व्योम __user *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	अगर (copy_from_user_toio(rme32->iobase + RME32_IO_DATA_BUFFER + pos,
				src, count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_playback_copy_kernel(काष्ठा snd_pcm_substream *substream,
					  पूर्णांक channel, अचिन्हित दीर्घ pos,
					  व्योम *src, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	स_नकल_toio(rme32->iobase + RME32_IO_DATA_BUFFER + pos, src, count);
	वापस 0;
पूर्ण

/* copy callback क्रम halfduplex mode */
अटल पूर्णांक snd_rme32_capture_copy(काष्ठा snd_pcm_substream *substream,
				  पूर्णांक channel, अचिन्हित दीर्घ pos,
				  व्योम __user *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	अगर (copy_to_user_fromio(dst,
			    rme32->iobase + RME32_IO_DATA_BUFFER + pos,
			    count))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_capture_copy_kernel(काष्ठा snd_pcm_substream *substream,
					 पूर्णांक channel, अचिन्हित दीर्घ pos,
					 व्योम *dst, अचिन्हित दीर्घ count)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	स_नकल_fromio(dst, rme32->iobase + RME32_IO_DATA_BUFFER + pos, count);
	वापस 0;
पूर्ण

/*
 * SPDIF I/O capabilities (half-duplex mode)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme32_spdअगर_info = अणु
	.info =		(SNDRV_PCM_INFO_MMAP_IOMEM |
			 SNDRV_PCM_INFO_MMAP_VALID |
			 SNDRV_PCM_INFO_INTERLEAVED | 
			 SNDRV_PCM_INFO_PAUSE |
			 SNDRV_PCM_INFO_SYNC_START |
			 SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats =	(SNDRV_PCM_FMTBIT_S16_LE | 
			 SNDRV_PCM_FMTBIT_S32_LE),
	.rates =	(SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 | 
			 SNDRV_PCM_RATE_48000),
	.rate_min =	32000,
	.rate_max =	48000,
	.channels_min =	2,
	.channels_max =	2,
	.buffer_bytes_max = RME32_BUFFER_SIZE,
	.period_bytes_min = RME32_BLOCK_SIZE,
	.period_bytes_max = RME32_BLOCK_SIZE,
	.periods_min =	RME32_BUFFER_SIZE / RME32_BLOCK_SIZE,
	.periods_max =	RME32_BUFFER_SIZE / RME32_BLOCK_SIZE,
	.fअगरo_size =	0,
पूर्ण;

/*
 * ADAT I/O capabilities (half-duplex mode)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme32_adat_info =
अणु
	.info =		     (SNDRV_PCM_INFO_MMAP_IOMEM |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_PAUSE |
			      SNDRV_PCM_INFO_SYNC_START |
			      SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats=            SNDRV_PCM_FMTBIT_S16_LE,
	.rates =             (SNDRV_PCM_RATE_44100 | 
			      SNDRV_PCM_RATE_48000),
	.rate_min =          44100,
	.rate_max =          48000,
	.channels_min =      8,
	.channels_max =	     8,
	.buffer_bytes_max =  RME32_BUFFER_SIZE,
	.period_bytes_min =  RME32_BLOCK_SIZE,
	.period_bytes_max =  RME32_BLOCK_SIZE,
	.periods_min =	    RME32_BUFFER_SIZE / RME32_BLOCK_SIZE,
	.periods_max =	    RME32_BUFFER_SIZE / RME32_BLOCK_SIZE,
	.fअगरo_size =	    0,
पूर्ण;

/*
 * SPDIF I/O capabilities (full-duplex mode)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme32_spdअगर_fd_info = अणु
	.info =		(SNDRV_PCM_INFO_MMAP |
			 SNDRV_PCM_INFO_MMAP_VALID |
			 SNDRV_PCM_INFO_INTERLEAVED | 
			 SNDRV_PCM_INFO_PAUSE |
			 SNDRV_PCM_INFO_SYNC_START |
			 SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats =	(SNDRV_PCM_FMTBIT_S16_LE | 
			 SNDRV_PCM_FMTBIT_S32_LE),
	.rates =	(SNDRV_PCM_RATE_32000 |
			 SNDRV_PCM_RATE_44100 | 
			 SNDRV_PCM_RATE_48000),
	.rate_min =	32000,
	.rate_max =	48000,
	.channels_min =	2,
	.channels_max =	2,
	.buffer_bytes_max = RME32_MID_BUFFER_SIZE,
	.period_bytes_min = RME32_BLOCK_SIZE,
	.period_bytes_max = RME32_BLOCK_SIZE,
	.periods_min =	2,
	.periods_max =	RME32_MID_BUFFER_SIZE / RME32_BLOCK_SIZE,
	.fअगरo_size =	0,
पूर्ण;

/*
 * ADAT I/O capabilities (full-duplex mode)
 */
अटल स्थिर काष्ठा snd_pcm_hardware snd_rme32_adat_fd_info =
अणु
	.info =		     (SNDRV_PCM_INFO_MMAP |
			      SNDRV_PCM_INFO_MMAP_VALID |
			      SNDRV_PCM_INFO_INTERLEAVED |
			      SNDRV_PCM_INFO_PAUSE |
			      SNDRV_PCM_INFO_SYNC_START |
			      SNDRV_PCM_INFO_SYNC_APPLPTR),
	.क्रमmats=            SNDRV_PCM_FMTBIT_S16_LE,
	.rates =             (SNDRV_PCM_RATE_44100 | 
			      SNDRV_PCM_RATE_48000),
	.rate_min =          44100,
	.rate_max =          48000,
	.channels_min =      8,
	.channels_max =	     8,
	.buffer_bytes_max =  RME32_MID_BUFFER_SIZE,
	.period_bytes_min =  RME32_BLOCK_SIZE,
	.period_bytes_max =  RME32_BLOCK_SIZE,
	.periods_min =	    2,
	.periods_max =	    RME32_MID_BUFFER_SIZE / RME32_BLOCK_SIZE,
	.fअगरo_size =	    0,
पूर्ण;

अटल व्योम snd_rme32_reset_dac(काष्ठा rme32 *rme32)
अणु
        ग_लिखोl(rme32->wcreg | RME32_WCR_PD,
               rme32->iobase + RME32_IO_CONTROL_REGISTER);
        ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
पूर्ण

अटल पूर्णांक snd_rme32_playback_getrate(काष्ठा rme32 * rme32)
अणु
	पूर्णांक rate;

	rate = ((rme32->wcreg >> RME32_WCR_BITPOS_FREQ_0) & 1) +
	       (((rme32->wcreg >> RME32_WCR_BITPOS_FREQ_1) & 1) << 1);
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
	वापस (rme32->wcreg & RME32_WCR_DS_BM) ? rate << 1 : rate;
पूर्ण

अटल पूर्णांक snd_rme32_capture_getrate(काष्ठा rme32 * rme32, पूर्णांक *is_adat)
अणु
	पूर्णांक n;

	*is_adat = 0;
	अगर (rme32->rcreg & RME32_RCR_LOCK) अणु 
                /* ADAT rate */
                *is_adat = 1;
	पूर्ण
	अगर (rme32->rcreg & RME32_RCR_ERF) अणु
		वापस -1;
	पूर्ण

        /* S/PDIF rate */
	n = ((rme32->rcreg >> RME32_RCR_BITPOS_F0) & 1) +
		(((rme32->rcreg >> RME32_RCR_BITPOS_F1) & 1) << 1) +
		(((rme32->rcreg >> RME32_RCR_BITPOS_F2) & 1) << 2);

	अगर (RME32_PRO_WITH_8414(rme32))
		चयन (n) अणु	/* supporting the CS8414 */
		हाल 0:
		हाल 1:
		हाल 2:
			वापस -1;
		हाल 3:
			वापस 96000;
		हाल 4:
			वापस 88200;
		हाल 5:
			वापस 48000;
		हाल 6:
			वापस 44100;
		हाल 7:
			वापस 32000;
		शेष:
			वापस -1;
		पूर्ण 
	अन्यथा
		चयन (n) अणु	/* supporting the CS8412 */
		हाल 0:
			वापस -1;
		हाल 1:
			वापस 48000;
		हाल 2:
			वापस 44100;
		हाल 3:
			वापस 32000;
		हाल 4:
			वापस 48000;
		हाल 5:
			वापस 44100;
		हाल 6:
			वापस 44056;
		हाल 7:
			वापस 32000;
		शेष:
			अवरोध;
		पूर्ण
	वापस -1;
पूर्ण

अटल पूर्णांक snd_rme32_playback_setrate(काष्ठा rme32 * rme32, पूर्णांक rate)
अणु
        पूर्णांक ds;

        ds = rme32->wcreg & RME32_WCR_DS_BM;
	चयन (rate) अणु
	हाल 32000:
		rme32->wcreg &= ~RME32_WCR_DS_BM;
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_0) & 
			~RME32_WCR_FREQ_1;
		अवरोध;
	हाल 44100:
		rme32->wcreg &= ~RME32_WCR_DS_BM;
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_1) & 
			~RME32_WCR_FREQ_0;
		अवरोध;
	हाल 48000:
		rme32->wcreg &= ~RME32_WCR_DS_BM;
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_0) | 
			RME32_WCR_FREQ_1;
		अवरोध;
	हाल 64000:
		अगर (rme32->pci->device != PCI_DEVICE_ID_RME_DIGI32_PRO)
			वापस -EINVAL;
		rme32->wcreg |= RME32_WCR_DS_BM;
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_0) & 
			~RME32_WCR_FREQ_1;
		अवरोध;
	हाल 88200:
		अगर (rme32->pci->device != PCI_DEVICE_ID_RME_DIGI32_PRO)
			वापस -EINVAL;
		rme32->wcreg |= RME32_WCR_DS_BM;
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_1) & 
			~RME32_WCR_FREQ_0;
		अवरोध;
	हाल 96000:
		अगर (rme32->pci->device != PCI_DEVICE_ID_RME_DIGI32_PRO)
			वापस -EINVAL;
		rme32->wcreg |= RME32_WCR_DS_BM;
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_0) | 
			RME32_WCR_FREQ_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
        अगर ((!ds && rme32->wcreg & RME32_WCR_DS_BM) ||
            (ds && !(rme32->wcreg & RME32_WCR_DS_BM)))
        अणु
                /* change to/from द्विगुन-speed: reset the DAC (अगर available) */
                snd_rme32_reset_dac(rme32);
        पूर्ण अन्यथा अणु
                ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_setघड़ीmode(काष्ठा rme32 * rme32, पूर्णांक mode)
अणु
	चयन (mode) अणु
	हाल RME32_CLOCKMODE_SLAVE:
		/* AutoSync */
		rme32->wcreg = (rme32->wcreg & ~RME32_WCR_FREQ_0) & 
			~RME32_WCR_FREQ_1;
		अवरोध;
	हाल RME32_CLOCKMODE_MASTER_32:
		/* Internal 32.0kHz */
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_0) & 
			~RME32_WCR_FREQ_1;
		अवरोध;
	हाल RME32_CLOCKMODE_MASTER_44:
		/* Internal 44.1kHz */
		rme32->wcreg = (rme32->wcreg & ~RME32_WCR_FREQ_0) | 
			RME32_WCR_FREQ_1;
		अवरोध;
	हाल RME32_CLOCKMODE_MASTER_48:
		/* Internal 48.0kHz */
		rme32->wcreg = (rme32->wcreg | RME32_WCR_FREQ_0) | 
			RME32_WCR_FREQ_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_अ_लोlockmode(काष्ठा rme32 * rme32)
अणु
	वापस ((rme32->wcreg >> RME32_WCR_BITPOS_FREQ_0) & 1) +
	    (((rme32->wcreg >> RME32_WCR_BITPOS_FREQ_1) & 1) << 1);
पूर्ण

अटल पूर्णांक snd_rme32_setinputtype(काष्ठा rme32 * rme32, पूर्णांक type)
अणु
	चयन (type) अणु
	हाल RME32_INPUT_OPTICAL:
		rme32->wcreg = (rme32->wcreg & ~RME32_WCR_INP_0) & 
			~RME32_WCR_INP_1;
		अवरोध;
	हाल RME32_INPUT_COAXIAL:
		rme32->wcreg = (rme32->wcreg | RME32_WCR_INP_0) & 
			~RME32_WCR_INP_1;
		अवरोध;
	हाल RME32_INPUT_INTERNAL:
		rme32->wcreg = (rme32->wcreg & ~RME32_WCR_INP_0) | 
			RME32_WCR_INP_1;
		अवरोध;
	हाल RME32_INPUT_XLR:
		rme32->wcreg = (rme32->wcreg | RME32_WCR_INP_0) | 
			RME32_WCR_INP_1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_getinputtype(काष्ठा rme32 * rme32)
अणु
	वापस ((rme32->wcreg >> RME32_WCR_BITPOS_INP_0) & 1) +
	    (((rme32->wcreg >> RME32_WCR_BITPOS_INP_1) & 1) << 1);
पूर्ण

अटल व्योम
snd_rme32_setframelog(काष्ठा rme32 * rme32, पूर्णांक n_channels, पूर्णांक is_playback)
अणु
	पूर्णांक frlog;

	अगर (n_channels == 2) अणु
		frlog = 1;
	पूर्ण अन्यथा अणु
		/* assume 8 channels */
		frlog = 3;
	पूर्ण
	अगर (is_playback) अणु
		frlog += (rme32->wcreg & RME32_WCR_MODE24) ? 2 : 1;
		rme32->playback_frlog = frlog;
	पूर्ण अन्यथा अणु
		frlog += (rme32->wcreg & RME32_WCR_MODE24) ? 2 : 1;
		rme32->capture_frlog = frlog;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_rme32_setक्रमmat(काष्ठा rme32 *rme32, snd_pcm_क्रमmat_t क्रमmat)
अणु
	चयन (क्रमmat) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
		rme32->wcreg &= ~RME32_WCR_MODE24;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S32_LE:
		rme32->wcreg |= RME32_WCR_MODE24;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme32_playback_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक err, rate, dummy;
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (!rme32->fullduplex_mode) अणु
		runसमय->dma_area = (व्योम __क्रमce *)(rme32->iobase +
						     RME32_IO_DATA_BUFFER);
		runसमय->dma_addr = rme32->port + RME32_IO_DATA_BUFFER;
		runसमय->dma_bytes = RME32_BUFFER_SIZE;
	पूर्ण

	spin_lock_irq(&rme32->lock);
	अगर ((rme32->rcreg & RME32_RCR_KMODE) &&
	    (rate = snd_rme32_capture_getrate(rme32, &dummy)) > 0) अणु
		/* AutoSync */
		अगर ((पूर्णांक)params_rate(params) != rate) अणु
			spin_unlock_irq(&rme32->lock);
			वापस -EIO;
		पूर्ण
	पूर्ण अन्यथा अगर ((err = snd_rme32_playback_setrate(rme32, params_rate(params))) < 0) अणु
		spin_unlock_irq(&rme32->lock);
		वापस err;
	पूर्ण
	अगर ((err = snd_rme32_setक्रमmat(rme32, params_क्रमmat(params))) < 0) अणु
		spin_unlock_irq(&rme32->lock);
		वापस err;
	पूर्ण

	snd_rme32_setframelog(rme32, params_channels(params), 1);
	अगर (rme32->capture_periodsize != 0) अणु
		अगर (params_period_size(params) << rme32->playback_frlog != rme32->capture_periodsize) अणु
			spin_unlock_irq(&rme32->lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	rme32->playback_periodsize = params_period_size(params) << rme32->playback_frlog;
	/* S/PDIF setup */
	अगर ((rme32->wcreg & RME32_WCR_ADAT) == 0) अणु
		rme32->wcreg &= ~(RME32_WCR_PRO | RME32_WCR_EMP);
		rme32->wcreg |= rme32->wcreg_spdअगर_stream;
		ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	पूर्ण
	spin_unlock_irq(&rme32->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme32_capture_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक err, isadat, rate;
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (!rme32->fullduplex_mode) अणु
		runसमय->dma_area = (व्योम __क्रमce *)rme32->iobase +
					RME32_IO_DATA_BUFFER;
		runसमय->dma_addr = rme32->port + RME32_IO_DATA_BUFFER;
		runसमय->dma_bytes = RME32_BUFFER_SIZE;
	पूर्ण

	spin_lock_irq(&rme32->lock);
	/* enable AutoSync क्रम record-preparing */
	rme32->wcreg |= RME32_WCR_AUTOSYNC;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);

	अगर ((err = snd_rme32_setक्रमmat(rme32, params_क्रमmat(params))) < 0) अणु
		spin_unlock_irq(&rme32->lock);
		वापस err;
	पूर्ण
	अगर ((err = snd_rme32_playback_setrate(rme32, params_rate(params))) < 0) अणु
		spin_unlock_irq(&rme32->lock);
		वापस err;
	पूर्ण
	अगर ((rate = snd_rme32_capture_getrate(rme32, &isadat)) > 0) अणु
                अगर ((पूर्णांक)params_rate(params) != rate) अणु
			spin_unlock_irq(&rme32->lock);
                        वापस -EIO;                    
                पूर्ण
                अगर ((isadat && runसमय->hw.channels_min == 2) ||
                    (!isadat && runसमय->hw.channels_min == 8)) अणु
			spin_unlock_irq(&rme32->lock);
                        वापस -EIO;
                पूर्ण
	पूर्ण
	/* AutoSync off क्रम recording */
	rme32->wcreg &= ~RME32_WCR_AUTOSYNC;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);

	snd_rme32_setframelog(rme32, params_channels(params), 0);
	अगर (rme32->playback_periodsize != 0) अणु
		अगर (params_period_size(params) << rme32->capture_frlog !=
		    rme32->playback_periodsize) अणु
			spin_unlock_irq(&rme32->lock);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	rme32->capture_periodsize =
	    params_period_size(params) << rme32->capture_frlog;
	spin_unlock_irq(&rme32->lock);

	वापस 0;
पूर्ण

अटल व्योम snd_rme32_pcm_start(काष्ठा rme32 * rme32, पूर्णांक from_छोड़ो)
अणु
	अगर (!from_छोड़ो) अणु
		ग_लिखोl(0, rme32->iobase + RME32_IO_RESET_POS);
	पूर्ण

	rme32->wcreg |= RME32_WCR_START;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
पूर्ण

अटल व्योम snd_rme32_pcm_stop(काष्ठा rme32 * rme32, पूर्णांक to_छोड़ो)
अणु
	/*
	 * Check अगर there is an unconfirmed IRQ, अगर so confirm it, or अन्यथा
	 * the hardware will not stop generating पूर्णांकerrupts
	 */
	rme32->rcreg = पढ़ोl(rme32->iobase + RME32_IO_CONTROL_REGISTER);
	अगर (rme32->rcreg & RME32_RCR_IRQ) अणु
		ग_लिखोl(0, rme32->iobase + RME32_IO_CONFIRM_ACTION_IRQ);
	पूर्ण
	rme32->wcreg &= ~RME32_WCR_START;
	अगर (rme32->wcreg & RME32_WCR_SEL)
		rme32->wcreg |= RME32_WCR_MUTE;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	अगर (! to_छोड़ो)
		ग_लिखोl(0, rme32->iobase + RME32_IO_RESET_POS);
पूर्ण

अटल irqवापस_t snd_rme32_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा rme32 *rme32 = (काष्ठा rme32 *) dev_id;

	rme32->rcreg = पढ़ोl(rme32->iobase + RME32_IO_CONTROL_REGISTER);
	अगर (!(rme32->rcreg & RME32_RCR_IRQ)) अणु
		वापस IRQ_NONE;
	पूर्ण अन्यथा अणु
		अगर (rme32->capture_substream) अणु
			snd_pcm_period_elapsed(rme32->capture_substream);
		पूर्ण
		अगर (rme32->playback_substream) अणु
			snd_pcm_period_elapsed(rme32->playback_substream);
		पूर्ण
		ग_लिखोl(0, rme32->iobase + RME32_IO_CONFIRM_ACTION_IRQ);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक period_bytes[] = अणु RME32_BLOCK_SIZE पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_स्थिरraपूर्णांकs_period_bytes = अणु
	.count = ARRAY_SIZE(period_bytes),
	.list = period_bytes,
	.mask = 0
पूर्ण;

अटल व्योम snd_rme32_set_buffer_स्थिरraपूर्णांक(काष्ठा rme32 *rme32, काष्ठा snd_pcm_runसमय *runसमय)
अणु
	अगर (! rme32->fullduplex_mode) अणु
		snd_pcm_hw_स्थिरraपूर्णांक_single(runसमय,
					     SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					     RME32_BUFFER_SIZE);
		snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					   SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					   &hw_स्थिरraपूर्णांकs_period_bytes);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_rme32_playback_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक rate, dummy;
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_set_sync(substream);

	spin_lock_irq(&rme32->lock);
	अगर (rme32->playback_substream != शून्य) अणु
		spin_unlock_irq(&rme32->lock);
		वापस -EBUSY;
	पूर्ण
	rme32->wcreg &= ~RME32_WCR_ADAT;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	rme32->playback_substream = substream;
	spin_unlock_irq(&rme32->lock);

	अगर (rme32->fullduplex_mode)
		runसमय->hw = snd_rme32_spdअगर_fd_info;
	अन्यथा
		runसमय->hw = snd_rme32_spdअगर_info;
	अगर (rme32->pci->device == PCI_DEVICE_ID_RME_DIGI32_PRO) अणु
		runसमय->hw.rates |= SNDRV_PCM_RATE_64000 | SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000;
		runसमय->hw.rate_max = 96000;
	पूर्ण
	अगर ((rme32->rcreg & RME32_RCR_KMODE) &&
	    (rate = snd_rme32_capture_getrate(rme32, &dummy)) > 0) अणु
		/* AutoSync */
		runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
		runसमय->hw.rate_min = rate;
		runसमय->hw.rate_max = rate;
	पूर्ण       

	snd_rme32_set_buffer_स्थिरraपूर्णांक(rme32, runसमय);

	rme32->wcreg_spdअगर_stream = rme32->wcreg_spdअगर;
	rme32->spdअगर_ctl->vd[0].access &= ~SNDRV_CTL_ELEM_ACCESS_INACTIVE;
	snd_ctl_notअगरy(rme32->card, SNDRV_CTL_EVENT_MASK_VALUE |
		       SNDRV_CTL_EVENT_MASK_INFO, &rme32->spdअगर_ctl->id);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_capture_spdअगर_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक isadat, rate;
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_set_sync(substream);

	spin_lock_irq(&rme32->lock);
        अगर (rme32->capture_substream != शून्य) अणु
		spin_unlock_irq(&rme32->lock);
                वापस -EBUSY;
        पूर्ण
	rme32->capture_substream = substream;
	spin_unlock_irq(&rme32->lock);

	अगर (rme32->fullduplex_mode)
		runसमय->hw = snd_rme32_spdअगर_fd_info;
	अन्यथा
		runसमय->hw = snd_rme32_spdअगर_info;
	अगर (RME32_PRO_WITH_8414(rme32)) अणु
		runसमय->hw.rates |= SNDRV_PCM_RATE_88200 | SNDRV_PCM_RATE_96000;
		runसमय->hw.rate_max = 96000;
	पूर्ण
	अगर ((rate = snd_rme32_capture_getrate(rme32, &isadat)) > 0) अणु
		अगर (isadat) अणु
			वापस -EIO;
		पूर्ण
		runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
		runसमय->hw.rate_min = rate;
		runसमय->hw.rate_max = rate;
	पूर्ण

	snd_rme32_set_buffer_स्थिरraपूर्णांक(rme32, runसमय);

	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme32_playback_adat_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक rate, dummy;
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	
	snd_pcm_set_sync(substream);

	spin_lock_irq(&rme32->lock);	
        अगर (rme32->playback_substream != शून्य) अणु
		spin_unlock_irq(&rme32->lock);
                वापस -EBUSY;
        पूर्ण
	rme32->wcreg |= RME32_WCR_ADAT;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	rme32->playback_substream = substream;
	spin_unlock_irq(&rme32->lock);
	
	अगर (rme32->fullduplex_mode)
		runसमय->hw = snd_rme32_adat_fd_info;
	अन्यथा
		runसमय->hw = snd_rme32_adat_info;
	अगर ((rme32->rcreg & RME32_RCR_KMODE) &&
	    (rate = snd_rme32_capture_getrate(rme32, &dummy)) > 0) अणु
                /* AutoSync */
                runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runसमय->hw.rate_min = rate;
                runसमय->hw.rate_max = rate;
	पूर्ण        

	snd_rme32_set_buffer_स्थिरraपूर्णांक(rme32, runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme32_capture_adat_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	पूर्णांक isadat, rate;
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (rme32->fullduplex_mode)
		runसमय->hw = snd_rme32_adat_fd_info;
	अन्यथा
		runसमय->hw = snd_rme32_adat_info;
	अगर ((rate = snd_rme32_capture_getrate(rme32, &isadat)) > 0) अणु
		अगर (!isadat) अणु
			वापस -EIO;
		पूर्ण
                runसमय->hw.rates = snd_pcm_rate_to_rate_bit(rate);
                runसमय->hw.rate_min = rate;
                runसमय->hw.rate_max = rate;
        पूर्ण

	snd_pcm_set_sync(substream);
        
	spin_lock_irq(&rme32->lock);	
	अगर (rme32->capture_substream != शून्य) अणु
		spin_unlock_irq(&rme32->lock);
		वापस -EBUSY;
        पूर्ण
	rme32->capture_substream = substream;
	spin_unlock_irq(&rme32->lock);

	snd_rme32_set_buffer_स्थिरraपूर्णांक(rme32, runसमय);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	पूर्णांक spdअगर = 0;

	spin_lock_irq(&rme32->lock);
	rme32->playback_substream = शून्य;
	rme32->playback_periodsize = 0;
	spdअगर = (rme32->wcreg & RME32_WCR_ADAT) == 0;
	spin_unlock_irq(&rme32->lock);
	अगर (spdअगर) अणु
		rme32->spdअगर_ctl->vd[0].access |= SNDRV_CTL_ELEM_ACCESS_INACTIVE;
		snd_ctl_notअगरy(rme32->card, SNDRV_CTL_EVENT_MASK_VALUE |
			       SNDRV_CTL_EVENT_MASK_INFO,
			       &rme32->spdअगर_ctl->id);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme32->lock);
	rme32->capture_substream = शून्य;
	rme32->capture_periodsize = 0;
	spin_unlock_irq(&rme32->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_playback_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme32->lock);
	अगर (rme32->fullduplex_mode) अणु
		स_रखो(&rme32->playback_pcm, 0, माप(rme32->playback_pcm));
		rme32->playback_pcm.hw_buffer_size = RME32_BUFFER_SIZE;
		rme32->playback_pcm.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, rme32->iobase + RME32_IO_RESET_POS);
	पूर्ण
	अगर (rme32->wcreg & RME32_WCR_SEL)
		rme32->wcreg &= ~RME32_WCR_MUTE;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme32->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_capture_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);

	spin_lock_irq(&rme32->lock);
	अगर (rme32->fullduplex_mode) अणु
		स_रखो(&rme32->capture_pcm, 0, माप(rme32->capture_pcm));
		rme32->capture_pcm.hw_buffer_size = RME32_BUFFER_SIZE;
		rme32->capture_pcm.hw_queue_size = RME32_BUFFER_SIZE / 2;
		rme32->capture_pcm.sw_buffer_size = snd_pcm_lib_buffer_bytes(substream);
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, rme32->iobase + RME32_IO_RESET_POS);
	पूर्ण
	spin_unlock_irq(&rme32->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक
snd_rme32_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_substream *s;

	spin_lock(&rme32->lock);
	snd_pcm_group_क्रम_each_entry(s, substream) अणु
		अगर (s != rme32->playback_substream &&
		    s != rme32->capture_substream)
			जारी;
		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
			rme32->running |= (1 << s->stream);
			अगर (rme32->fullduplex_mode) अणु
				/* remember the current DMA position */
				अगर (s == rme32->playback_substream) अणु
					rme32->playback_pcm.hw_io =
					rme32->playback_pcm.hw_data = snd_rme32_pcm_byteptr(rme32);
				पूर्ण अन्यथा अणु
					rme32->capture_pcm.hw_io =
					rme32->capture_pcm.hw_data = snd_rme32_pcm_byteptr(rme32);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
			rme32->running &= ~(1 << s->stream);
			अवरोध;
		पूर्ण
		snd_pcm_trigger_करोne(s, substream);
	पूर्ण
	
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (rme32->running && ! RME32_ISWORKING(rme32))
			snd_rme32_pcm_start(rme32, 0);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
		अगर (! rme32->running && RME32_ISWORKING(rme32))
			snd_rme32_pcm_stop(rme32, 0);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (rme32->running && RME32_ISWORKING(rme32))
			snd_rme32_pcm_stop(rme32, 1);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (rme32->running && ! RME32_ISWORKING(rme32))
			snd_rme32_pcm_start(rme32, 1);
		अवरोध;
	पूर्ण
	spin_unlock(&rme32->lock);
	वापस 0;
पूर्ण

/* poपूर्णांकer callback क्रम halfduplex mode */
अटल snd_pcm_uframes_t
snd_rme32_playback_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	वापस snd_rme32_pcm_byteptr(rme32) >> rme32->playback_frlog;
पूर्ण

अटल snd_pcm_uframes_t
snd_rme32_capture_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	वापस snd_rme32_pcm_byteptr(rme32) >> rme32->capture_frlog;
पूर्ण


/* ack and poपूर्णांकer callbacks क्रम fullduplex mode */
अटल व्योम snd_rme32_pb_trans_copy(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	स_नकल_toio(rme32->iobase + RME32_IO_DATA_BUFFER + rec->hw_data,
		    substream->runसमय->dma_area + rec->sw_data, bytes);
पूर्ण

अटल पूर्णांक snd_rme32_playback_fd_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_indirect *rec, *cprec;

	rec = &rme32->playback_pcm;
	cprec = &rme32->capture_pcm;
	spin_lock(&rme32->lock);
	rec->hw_queue_size = RME32_BUFFER_SIZE;
	अगर (rme32->running & (1 << SNDRV_PCM_STREAM_CAPTURE))
		rec->hw_queue_size -= cprec->hw_पढ़ोy;
	spin_unlock(&rme32->lock);
	वापस snd_pcm_indirect_playback_transfer(substream, rec,
						  snd_rme32_pb_trans_copy);
पूर्ण

अटल व्योम snd_rme32_cp_trans_copy(काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_indirect *rec, माप_प्रकार bytes)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	स_नकल_fromio(substream->runसमय->dma_area + rec->sw_data,
		      rme32->iobase + RME32_IO_DATA_BUFFER + rec->hw_data,
		      bytes);
पूर्ण

अटल पूर्णांक snd_rme32_capture_fd_ack(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	वापस snd_pcm_indirect_capture_transfer(substream, &rme32->capture_pcm,
						 snd_rme32_cp_trans_copy);
पूर्ण

अटल snd_pcm_uframes_t
snd_rme32_playback_fd_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	वापस snd_pcm_indirect_playback_poपूर्णांकer(substream, &rme32->playback_pcm,
						 snd_rme32_pcm_byteptr(rme32));
पूर्ण

अटल snd_pcm_uframes_t
snd_rme32_capture_fd_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा rme32 *rme32 = snd_pcm_substream_chip(substream);
	वापस snd_pcm_indirect_capture_poपूर्णांकer(substream, &rme32->capture_pcm,
						snd_rme32_pcm_byteptr(rme32));
पूर्ण

/* क्रम halfduplex mode */
अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_playback_spdअगर_ops = अणु
	.खोलो =		snd_rme32_playback_spdअगर_खोलो,
	.बंद =	snd_rme32_playback_बंद,
	.hw_params =	snd_rme32_playback_hw_params,
	.prepare =	snd_rme32_playback_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_playback_poपूर्णांकer,
	.copy_user =	snd_rme32_playback_copy,
	.copy_kernel =	snd_rme32_playback_copy_kernel,
	.fill_silence =	snd_rme32_playback_silence,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_capture_spdअगर_ops = अणु
	.खोलो =		snd_rme32_capture_spdअगर_खोलो,
	.बंद =	snd_rme32_capture_बंद,
	.hw_params =	snd_rme32_capture_hw_params,
	.prepare =	snd_rme32_capture_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_capture_poपूर्णांकer,
	.copy_user =	snd_rme32_capture_copy,
	.copy_kernel =	snd_rme32_capture_copy_kernel,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_playback_adat_ops = अणु
	.खोलो =		snd_rme32_playback_adat_खोलो,
	.बंद =	snd_rme32_playback_बंद,
	.hw_params =	snd_rme32_playback_hw_params,
	.prepare =	snd_rme32_playback_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_playback_poपूर्णांकer,
	.copy_user =	snd_rme32_playback_copy,
	.copy_kernel =	snd_rme32_playback_copy_kernel,
	.fill_silence =	snd_rme32_playback_silence,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_capture_adat_ops = अणु
	.खोलो =		snd_rme32_capture_adat_खोलो,
	.बंद =	snd_rme32_capture_बंद,
	.hw_params =	snd_rme32_capture_hw_params,
	.prepare =	snd_rme32_capture_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_capture_poपूर्णांकer,
	.copy_user =	snd_rme32_capture_copy,
	.copy_kernel =	snd_rme32_capture_copy_kernel,
	.mmap =		snd_pcm_lib_mmap_iomem,
पूर्ण;

/* क्रम fullduplex mode */
अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_playback_spdअगर_fd_ops = अणु
	.खोलो =		snd_rme32_playback_spdअगर_खोलो,
	.बंद =	snd_rme32_playback_बंद,
	.hw_params =	snd_rme32_playback_hw_params,
	.prepare =	snd_rme32_playback_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_playback_fd_poपूर्णांकer,
	.ack =		snd_rme32_playback_fd_ack,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_capture_spdअगर_fd_ops = अणु
	.खोलो =		snd_rme32_capture_spdअगर_खोलो,
	.बंद =	snd_rme32_capture_बंद,
	.hw_params =	snd_rme32_capture_hw_params,
	.prepare =	snd_rme32_capture_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_capture_fd_poपूर्णांकer,
	.ack =		snd_rme32_capture_fd_ack,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_playback_adat_fd_ops = अणु
	.खोलो =		snd_rme32_playback_adat_खोलो,
	.बंद =	snd_rme32_playback_बंद,
	.hw_params =	snd_rme32_playback_hw_params,
	.prepare =	snd_rme32_playback_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_playback_fd_poपूर्णांकer,
	.ack =		snd_rme32_playback_fd_ack,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_rme32_capture_adat_fd_ops = अणु
	.खोलो =		snd_rme32_capture_adat_खोलो,
	.बंद =	snd_rme32_capture_बंद,
	.hw_params =	snd_rme32_capture_hw_params,
	.prepare =	snd_rme32_capture_prepare,
	.trigger =	snd_rme32_pcm_trigger,
	.poपूर्णांकer =	snd_rme32_capture_fd_poपूर्णांकer,
	.ack =		snd_rme32_capture_fd_ack,
पूर्ण;

अटल व्योम snd_rme32_मुक्त(व्योम *निजी_data)
अणु
	काष्ठा rme32 *rme32 = (काष्ठा rme32 *) निजी_data;

	अगर (rme32 == शून्य) अणु
		वापस;
	पूर्ण
	अगर (rme32->irq >= 0) अणु
		snd_rme32_pcm_stop(rme32, 0);
		मुक्त_irq(rme32->irq, (व्योम *) rme32);
		rme32->irq = -1;
	पूर्ण
	अगर (rme32->iobase) अणु
		iounmap(rme32->iobase);
		rme32->iobase = शून्य;
	पूर्ण
	अगर (rme32->port) अणु
		pci_release_regions(rme32->pci);
		rme32->port = 0;
	पूर्ण
	pci_disable_device(rme32->pci);
पूर्ण

अटल व्योम snd_rme32_मुक्त_spdअगर_pcm(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा rme32 *rme32 = (काष्ठा rme32 *) pcm->निजी_data;
	rme32->spdअगर_pcm = शून्य;
पूर्ण

अटल व्योम
snd_rme32_मुक्त_adat_pcm(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा rme32 *rme32 = (काष्ठा rme32 *) pcm->निजी_data;
	rme32->adat_pcm = शून्य;
पूर्ण

अटल पूर्णांक snd_rme32_create(काष्ठा rme32 *rme32)
अणु
	काष्ठा pci_dev *pci = rme32->pci;
	पूर्णांक err;

	rme32->irq = -1;
	spin_lock_init(&rme32->lock);

	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;

	अगर ((err = pci_request_regions(pci, "RME32")) < 0)
		वापस err;
	rme32->port = pci_resource_start(rme32->pci, 0);

	rme32->iobase = ioremap(rme32->port, RME32_IO_SIZE);
	अगर (!rme32->iobase) अणु
		dev_err(rme32->card->dev,
			"unable to remap memory region 0x%lx-0x%lx\n",
			   rme32->port, rme32->port + RME32_IO_SIZE - 1);
		वापस -ENOMEM;
	पूर्ण

	अगर (request_irq(pci->irq, snd_rme32_पूर्णांकerrupt, IRQF_SHARED,
			KBUILD_MODNAME, rme32)) अणु
		dev_err(rme32->card->dev, "unable to grab IRQ %d\n", pci->irq);
		वापस -EBUSY;
	पूर्ण
	rme32->irq = pci->irq;
	rme32->card->sync_irq = rme32->irq;

	/* पढ़ो the card's revision number */
	pci_पढ़ो_config_byte(pci, 8, &rme32->rev);

	/* set up ALSA pcm device क्रम S/PDIF */
	अगर ((err = snd_pcm_new(rme32->card, "Digi32 IEC958", 0, 1, 1, &rme32->spdअगर_pcm)) < 0) अणु
		वापस err;
	पूर्ण
	rme32->spdअगर_pcm->निजी_data = rme32;
	rme32->spdअगर_pcm->निजी_मुक्त = snd_rme32_मुक्त_spdअगर_pcm;
	म_नकल(rme32->spdअगर_pcm->name, "Digi32 IEC958");
	अगर (rme32->fullduplex_mode) अणु
		snd_pcm_set_ops(rme32->spdअगर_pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_rme32_playback_spdअगर_fd_ops);
		snd_pcm_set_ops(rme32->spdअगर_pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_rme32_capture_spdअगर_fd_ops);
		snd_pcm_set_managed_buffer_all(rme32->spdअगर_pcm, SNDRV_DMA_TYPE_CONTINUOUS,
					       शून्य, 0, RME32_MID_BUFFER_SIZE);
		rme32->spdअगर_pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;
	पूर्ण अन्यथा अणु
		snd_pcm_set_ops(rme32->spdअगर_pcm, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_rme32_playback_spdअगर_ops);
		snd_pcm_set_ops(rme32->spdअगर_pcm, SNDRV_PCM_STREAM_CAPTURE,
				&snd_rme32_capture_spdअगर_ops);
		rme32->spdअगर_pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
	पूर्ण

	/* set up ALSA pcm device क्रम ADAT */
	अगर ((pci->device == PCI_DEVICE_ID_RME_DIGI32) ||
	    (pci->device == PCI_DEVICE_ID_RME_DIGI32_PRO)) अणु
		/* ADAT is not available on DIGI32 and DIGI32 Pro */
		rme32->adat_pcm = शून्य;
	पूर्ण
	अन्यथा अणु
		अगर ((err = snd_pcm_new(rme32->card, "Digi32 ADAT", 1,
				       1, 1, &rme32->adat_pcm)) < 0)
		अणु
			वापस err;
		पूर्ण		
		rme32->adat_pcm->निजी_data = rme32;
		rme32->adat_pcm->निजी_मुक्त = snd_rme32_मुक्त_adat_pcm;
		म_नकल(rme32->adat_pcm->name, "Digi32 ADAT");
		अगर (rme32->fullduplex_mode) अणु
			snd_pcm_set_ops(rme32->adat_pcm, SNDRV_PCM_STREAM_PLAYBACK, 
					&snd_rme32_playback_adat_fd_ops);
			snd_pcm_set_ops(rme32->adat_pcm, SNDRV_PCM_STREAM_CAPTURE, 
					&snd_rme32_capture_adat_fd_ops);
			snd_pcm_set_managed_buffer_all(rme32->adat_pcm, SNDRV_DMA_TYPE_CONTINUOUS,
						       शून्य,
						       0, RME32_MID_BUFFER_SIZE);
			rme32->adat_pcm->info_flags = SNDRV_PCM_INFO_JOINT_DUPLEX;
		पूर्ण अन्यथा अणु
			snd_pcm_set_ops(rme32->adat_pcm, SNDRV_PCM_STREAM_PLAYBACK, 
					&snd_rme32_playback_adat_ops);
			snd_pcm_set_ops(rme32->adat_pcm, SNDRV_PCM_STREAM_CAPTURE, 
					&snd_rme32_capture_adat_ops);
			rme32->adat_pcm->info_flags = SNDRV_PCM_INFO_HALF_DUPLEX;
		पूर्ण
	पूर्ण


	rme32->playback_periodsize = 0;
	rme32->capture_periodsize = 0;

	/* make sure playback/capture is stopped, अगर by some reason active */
	snd_rme32_pcm_stop(rme32, 0);

        /* reset DAC */
        snd_rme32_reset_dac(rme32);

	/* reset buffer poपूर्णांकer */
	ग_लिखोl(0, rme32->iobase + RME32_IO_RESET_POS);

	/* set शेष values in रेजिस्टरs */
	rme32->wcreg = RME32_WCR_SEL |	 /* normal playback */
		RME32_WCR_INP_0 | /* input select */
		RME32_WCR_MUTE;	 /* muting on */
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);


	/* init चयन पूर्णांकerface */
	अगर ((err = snd_rme32_create_चयनes(rme32->card, rme32)) < 0) अणु
		वापस err;
	पूर्ण

	/* init proc पूर्णांकerface */
	snd_rme32_proc_init(rme32);

	rme32->capture_substream = शून्य;
	rme32->playback_substream = शून्य;

	वापस 0;
पूर्ण

/*
 * proc पूर्णांकerface
 */

अटल व्योम
snd_rme32_proc_पढ़ो(काष्ठा snd_info_entry * entry, काष्ठा snd_info_buffer *buffer)
अणु
	पूर्णांक n;
	काष्ठा rme32 *rme32 = (काष्ठा rme32 *) entry->निजी_data;

	rme32->rcreg = पढ़ोl(rme32->iobase + RME32_IO_CONTROL_REGISTER);

	snd_iम_लिखो(buffer, rme32->card->दीर्घname);
	snd_iम_लिखो(buffer, " (index #%d)\n", rme32->card->number + 1);

	snd_iम_लिखो(buffer, "\nGeneral settings\n");
	अगर (rme32->fullduplex_mode)
		snd_iम_लिखो(buffer, "  Full-duplex mode\n");
	अन्यथा
		snd_iम_लिखो(buffer, "  Half-duplex mode\n");
	अगर (RME32_PRO_WITH_8414(rme32)) अणु
		snd_iम_लिखो(buffer, "  receiver: CS8414\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  receiver: CS8412\n");
	पूर्ण
	अगर (rme32->wcreg & RME32_WCR_MODE24) अणु
		snd_iम_लिखो(buffer, "  format: 24 bit");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  format: 16 bit");
	पूर्ण
	अगर (rme32->wcreg & RME32_WCR_MONO) अणु
		snd_iम_लिखो(buffer, ", Mono\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, ", Stereo\n");
	पूर्ण

	snd_iम_लिखो(buffer, "\nInput settings\n");
	चयन (snd_rme32_getinputtype(rme32)) अणु
	हाल RME32_INPUT_OPTICAL:
		snd_iम_लिखो(buffer, "  input: optical");
		अवरोध;
	हाल RME32_INPUT_COAXIAL:
		snd_iम_लिखो(buffer, "  input: coaxial");
		अवरोध;
	हाल RME32_INPUT_INTERNAL:
		snd_iम_लिखो(buffer, "  input: internal");
		अवरोध;
	हाल RME32_INPUT_XLR:
		snd_iम_लिखो(buffer, "  input: XLR");
		अवरोध;
	पूर्ण
	अगर (snd_rme32_capture_getrate(rme32, &n) < 0) अणु
		snd_iम_लिखो(buffer, "\n  sample rate: no valid signal\n");
	पूर्ण अन्यथा अणु
		अगर (n) अणु
			snd_iम_लिखो(buffer, " (8 channels)\n");
		पूर्ण अन्यथा अणु
			snd_iम_लिखो(buffer, " (2 channels)\n");
		पूर्ण
		snd_iम_लिखो(buffer, "  sample rate: %d Hz\n",
			    snd_rme32_capture_getrate(rme32, &n));
	पूर्ण

	snd_iम_लिखो(buffer, "\nOutput settings\n");
	अगर (rme32->wcreg & RME32_WCR_SEL) अणु
		snd_iम_लिखो(buffer, "  output signal: normal playback");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  output signal: same as input");
	पूर्ण
	अगर (rme32->wcreg & RME32_WCR_MUTE) अणु
		snd_iम_लिखो(buffer, " (muted)\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "\n");
	पूर्ण

	/* master output frequency */
	अगर (!
	    ((!(rme32->wcreg & RME32_WCR_FREQ_0))
	     && (!(rme32->wcreg & RME32_WCR_FREQ_1)))) अणु
		snd_iम_लिखो(buffer, "  sample rate: %d Hz\n",
			    snd_rme32_playback_getrate(rme32));
	पूर्ण
	अगर (rme32->rcreg & RME32_RCR_KMODE) अणु
		snd_iम_लिखो(buffer, "  sample clock source: AutoSync\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  sample clock source: Internal\n");
	पूर्ण
	अगर (rme32->wcreg & RME32_WCR_PRO) अणु
		snd_iम_लिखो(buffer, "  format: AES/EBU (professional)\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  format: IEC958 (consumer)\n");
	पूर्ण
	अगर (rme32->wcreg & RME32_WCR_EMP) अणु
		snd_iम_लिखो(buffer, "  emphasis: on\n");
	पूर्ण अन्यथा अणु
		snd_iम_लिखो(buffer, "  emphasis: off\n");
	पूर्ण
पूर्ण

अटल व्योम snd_rme32_proc_init(काष्ठा rme32 *rme32)
अणु
	snd_card_ro_proc_new(rme32->card, "rme32", rme32, snd_rme32_proc_पढ़ो);
पूर्ण

/*
 * control पूर्णांकerface
 */

#घोषणा snd_rme32_info_loopback_control		snd_ctl_boolean_mono_info

अटल पूर्णांक
snd_rme32_get_loopback_control(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&rme32->lock);
	ucontrol->value.पूर्णांकeger.value[0] =
	    rme32->wcreg & RME32_WCR_SEL ? 0 : 1;
	spin_unlock_irq(&rme32->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme32_put_loopback_control(काष्ठा snd_kcontrol *kcontrol,
			       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ucontrol->value.पूर्णांकeger.value[0] ? 0 : RME32_WCR_SEL;
	spin_lock_irq(&rme32->lock);
	val = (rme32->wcreg & ~RME32_WCR_SEL) | val;
	change = val != rme32->wcreg;
	अगर (ucontrol->value.पूर्णांकeger.value[0])
		val &= ~RME32_WCR_MUTE;
	अन्यथा
		val |= RME32_WCR_MUTE;
	rme32->wcreg = val;
	ग_लिखोl(val, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme32->lock);
	वापस change;
पूर्ण

अटल पूर्णांक
snd_rme32_info_inputtype_control(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु
		"Optical", "Coaxial", "Internal", "XLR"
	पूर्ण;
	पूर्णांक num_items;

	चयन (rme32->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI32:
	हाल PCI_DEVICE_ID_RME_DIGI32_8:
		num_items = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI32_PRO:
		num_items = 4;
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	वापस snd_ctl_क्रमागत_info(uinfo, 1, num_items, texts);
पूर्ण
अटल पूर्णांक
snd_rme32_get_inputtype_control(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक items = 3;

	spin_lock_irq(&rme32->lock);
	ucontrol->value.क्रमागतerated.item[0] = snd_rme32_getinputtype(rme32);

	चयन (rme32->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI32:
	हाल PCI_DEVICE_ID_RME_DIGI32_8:
		items = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI32_PRO:
		items = 4;
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	अगर (ucontrol->value.क्रमागतerated.item[0] >= items) अणु
		ucontrol->value.क्रमागतerated.item[0] = items - 1;
	पूर्ण

	spin_unlock_irq(&rme32->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme32_put_inputtype_control(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change, items = 3;

	चयन (rme32->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI32:
	हाल PCI_DEVICE_ID_RME_DIGI32_8:
		items = 3;
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI32_PRO:
		items = 4;
		अवरोध;
	शेष:
		snd_BUG();
		अवरोध;
	पूर्ण
	val = ucontrol->value.क्रमागतerated.item[0] % items;

	spin_lock_irq(&rme32->lock);
	change = val != (अचिन्हित पूर्णांक)snd_rme32_getinputtype(rme32);
	snd_rme32_setinputtype(rme32, val);
	spin_unlock_irq(&rme32->lock);
	वापस change;
पूर्ण

अटल पूर्णांक
snd_rme32_info_घड़ीmode_control(काष्ठा snd_kcontrol *kcontrol,
				 काष्ठा snd_ctl_elem_info *uinfo)
अणु
	अटल स्थिर अक्षर * स्थिर texts[4] = अणु "AutoSync",
				  "Internal 32.0kHz", 
				  "Internal 44.1kHz", 
				  "Internal 48.0kHz" पूर्ण;

	वापस snd_ctl_क्रमागत_info(uinfo, 1, 4, texts);
पूर्ण
अटल पूर्णांक
snd_rme32_get_घड़ीmode_control(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&rme32->lock);
	ucontrol->value.क्रमागतerated.item[0] = snd_rme32_अ_लोlockmode(rme32);
	spin_unlock_irq(&rme32->lock);
	वापस 0;
पूर्ण
अटल पूर्णांक
snd_rme32_put_घड़ीmode_control(काष्ठा snd_kcontrol *kcontrol,
				काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	अचिन्हित पूर्णांक val;
	पूर्णांक change;

	val = ucontrol->value.क्रमागतerated.item[0] % 3;
	spin_lock_irq(&rme32->lock);
	change = val != (अचिन्हित पूर्णांक)snd_rme32_अ_लोlockmode(rme32);
	snd_rme32_setघड़ीmode(rme32, val);
	spin_unlock_irq(&rme32->lock);
	वापस change;
पूर्ण

अटल u32 snd_rme32_convert_from_aes(काष्ठा snd_aes_iec958 * aes)
अणु
	u32 val = 0;
	val |= (aes->status[0] & IEC958_AES0_PROFESSIONAL) ? RME32_WCR_PRO : 0;
	अगर (val & RME32_WCR_PRO)
		val |= (aes->status[0] & IEC958_AES0_PRO_EMPHASIS_5015) ? RME32_WCR_EMP : 0;
	अन्यथा
		val |= (aes->status[0] & IEC958_AES0_CON_EMPHASIS_5015) ? RME32_WCR_EMP : 0;
	वापस val;
पूर्ण

अटल व्योम snd_rme32_convert_to_aes(काष्ठा snd_aes_iec958 * aes, u32 val)
अणु
	aes->status[0] = ((val & RME32_WCR_PRO) ? IEC958_AES0_PROFESSIONAL : 0);
	अगर (val & RME32_WCR_PRO)
		aes->status[0] |= (val & RME32_WCR_EMP) ? IEC958_AES0_PRO_EMPHASIS_5015 : 0;
	अन्यथा
		aes->status[0] |= (val & RME32_WCR_EMP) ? IEC958_AES0_CON_EMPHASIS_5015 : 0;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_info(काष्ठा snd_kcontrol *kcontrol,
					काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_get(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);

	snd_rme32_convert_to_aes(&ucontrol->value.iec958,
				 rme32->wcreg_spdअगर);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_put(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;

	val = snd_rme32_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&rme32->lock);
	change = val != rme32->wcreg_spdअगर;
	rme32->wcreg_spdअगर = val;
	spin_unlock_irq(&rme32->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_stream_info(काष्ठा snd_kcontrol *kcontrol,
					       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_stream_get(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value *
					      ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);

	snd_rme32_convert_to_aes(&ucontrol->value.iec958,
				 rme32->wcreg_spdअगर_stream);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_stream_put(काष्ठा snd_kcontrol *kcontrol,
					      काष्ठा snd_ctl_elem_value *
					      ucontrol)
अणु
	काष्ठा rme32 *rme32 = snd_kcontrol_chip(kcontrol);
	पूर्णांक change;
	u32 val;

	val = snd_rme32_convert_from_aes(&ucontrol->value.iec958);
	spin_lock_irq(&rme32->lock);
	change = val != rme32->wcreg_spdअगर_stream;
	rme32->wcreg_spdअगर_stream = val;
	rme32->wcreg &= ~(RME32_WCR_PRO | RME32_WCR_EMP);
	rme32->wcreg |= val;
	ग_लिखोl(rme32->wcreg, rme32->iobase + RME32_IO_CONTROL_REGISTER);
	spin_unlock_irq(&rme32->lock);
	वापस change;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_mask_info(काष्ठा snd_kcontrol *kcontrol,
					     काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_IEC958;
	uinfo->count = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rme32_control_spdअगर_mask_get(काष्ठा snd_kcontrol *kcontrol,
					    काष्ठा snd_ctl_elem_value *
					    ucontrol)
अणु
	ucontrol->value.iec958.status[0] = kcontrol->निजी_value;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_rme32_controls[] = अणु
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name =	SNDRV_CTL_NAME_IEC958("", PLAYBACK, DEFAULT),
		.info =	snd_rme32_control_spdअगर_info,
		.get =	snd_rme32_control_spdअगर_get,
		.put =	snd_rme32_control_spdअगर_put
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READWRITE | SNDRV_CTL_ELEM_ACCESS_INACTIVE,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name =	SNDRV_CTL_NAME_IEC958("", PLAYBACK, PCM_STREAM),
		.info =	snd_rme32_control_spdअगर_stream_info,
		.get =	snd_rme32_control_spdअगर_stream_get,
		.put =	snd_rme32_control_spdअगर_stream_put
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name =	SNDRV_CTL_NAME_IEC958("", PLAYBACK, CON_MASK),
		.info =	snd_rme32_control_spdअगर_mask_info,
		.get =	snd_rme32_control_spdअगर_mask_get,
		.निजी_value = IEC958_AES0_PROFESSIONAL | IEC958_AES0_CON_EMPHASIS
	पूर्ण,
	अणु
		.access = SNDRV_CTL_ELEM_ACCESS_READ,
		.अगरace = SNDRV_CTL_ELEM_IFACE_PCM,
		.name =	SNDRV_CTL_NAME_IEC958("", PLAYBACK, PRO_MASK),
		.info =	snd_rme32_control_spdअगर_mask_info,
		.get =	snd_rme32_control_spdअगर_mask_get,
		.निजी_value = IEC958_AES0_PROFESSIONAL | IEC958_AES0_PRO_EMPHASIS
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =	"Input Connector",
		.info =	snd_rme32_info_inputtype_control,
		.get =	snd_rme32_get_inputtype_control,
		.put =	snd_rme32_put_inputtype_control
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =	"Loopback Input",
		.info =	snd_rme32_info_loopback_control,
		.get =	snd_rme32_get_loopback_control,
		.put =	snd_rme32_put_loopback_control
	पूर्ण,
	अणु
		.अगरace = SNDRV_CTL_ELEM_IFACE_MIXER,
		.name =	"Sample Clock Source",
		.info =	snd_rme32_info_घड़ीmode_control,
		.get =	snd_rme32_get_घड़ीmode_control,
		.put =	snd_rme32_put_घड़ीmode_control
	पूर्ण
पूर्ण;

अटल पूर्णांक snd_rme32_create_चयनes(काष्ठा snd_card *card, काष्ठा rme32 * rme32)
अणु
	पूर्णांक idx, err;
	काष्ठा snd_kcontrol *kctl;

	क्रम (idx = 0; idx < (पूर्णांक)ARRAY_SIZE(snd_rme32_controls); idx++) अणु
		अगर ((err = snd_ctl_add(card, kctl = snd_ctl_new1(&snd_rme32_controls[idx], rme32))) < 0)
			वापस err;
		अगर (idx == 1)	/* IEC958 (S/PDIF) Stream */
			rme32->spdअगर_ctl = kctl;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Card initialisation
 */

अटल व्योम snd_rme32_card_मुक्त(काष्ठा snd_card *card)
अणु
	snd_rme32_मुक्त(card->निजी_data);
पूर्ण

अटल पूर्णांक
snd_rme32_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा rme32 *rme32;
	काष्ठा snd_card *card;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS) अणु
		वापस -ENODEV;
	पूर्ण
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   माप(काष्ठा rme32), &card);
	अगर (err < 0)
		वापस err;
	card->निजी_मुक्त = snd_rme32_card_मुक्त;
	rme32 = (काष्ठा rme32 *) card->निजी_data;
	rme32->card = card;
	rme32->pci = pci;
        अगर (fullduplex[dev])
		rme32->fullduplex_mode = 1;
	अगर ((err = snd_rme32_create(rme32)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण

	म_नकल(card->driver, "Digi32");
	चयन (rme32->pci->device) अणु
	हाल PCI_DEVICE_ID_RME_DIGI32:
		म_नकल(card->लघुname, "RME Digi32");
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI32_8:
		म_नकल(card->लघुname, "RME Digi32/8");
		अवरोध;
	हाल PCI_DEVICE_ID_RME_DIGI32_PRO:
		म_नकल(card->लघुname, "RME Digi32 PRO");
		अवरोध;
	पूर्ण
	प्र_लिखो(card->दीर्घname, "%s (Rev. %d) at 0x%lx, irq %d",
		card->लघुname, rme32->rev, rme32->port, rme32->irq);

	अगर ((err = snd_card_रेजिस्टर(card)) < 0) अणु
		snd_card_मुक्त(card);
		वापस err;
	पूर्ण
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;
पूर्ण

अटल व्योम snd_rme32_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver rme32_driver = अणु
	.name =		KBUILD_MODNAME,
	.id_table =	snd_rme32_ids,
	.probe =	snd_rme32_probe,
	.हटाओ =	snd_rme32_हटाओ,
पूर्ण;

module_pci_driver(rme32_driver);
