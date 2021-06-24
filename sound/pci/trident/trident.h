<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित __SOUND_TRIDENT_H
#घोषणा __SOUND_TRIDENT_H

/*
 *  audio@tridenपंचांगicro.com
 *  Fri Feb 19 15:55:28 MST 1999
 *  Definitions क्रम Trident 4DWave DX/NX chips
 */

#समावेश <sound/pcm.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/util_स्मृति.स>

#घोषणा TRIDENT_DEVICE_ID_DX		((PCI_VENDOR_ID_TRIDENT<<16)|PCI_DEVICE_ID_TRIDENT_4DWAVE_DX)
#घोषणा TRIDENT_DEVICE_ID_NX		((PCI_VENDOR_ID_TRIDENT<<16)|PCI_DEVICE_ID_TRIDENT_4DWAVE_NX)
#घोषणा TRIDENT_DEVICE_ID_SI7018	((PCI_VENDOR_ID_SI<<16)|PCI_DEVICE_ID_SI_7018)

#घोषणा SNDRV_TRIDENT_VOICE_TYPE_PCM		0
#घोषणा SNDRV_TRIDENT_VOICE_TYPE_SYNTH		1
#घोषणा SNDRV_TRIDENT_VOICE_TYPE_MIDI		2

#घोषणा SNDRV_TRIDENT_VFLG_RUNNING		(1<<0)

/* TLB code स्थिरants */
#घोषणा SNDRV_TRIDENT_PAGE_SIZE			4096
#घोषणा SNDRV_TRIDENT_PAGE_SHIFT			12
#घोषणा SNDRV_TRIDENT_PAGE_MASK			((1<<SNDRV_TRIDENT_PAGE_SHIFT)-1)
#घोषणा SNDRV_TRIDENT_MAX_PAGES			4096

/*
 * Direct रेजिस्टरs
 */

#घोषणा TRID_REG(trident, x) ((trident)->port + (x))

#घोषणा ID_4DWAVE_DX        0x2000
#घोषणा ID_4DWAVE_NX        0x2001

/* Bank definitions */

#घोषणा T4D_BANK_A	0
#घोषणा T4D_BANK_B	1
#घोषणा T4D_NUM_BANKS	2

/* Register definitions */

/* Global रेजिस्टरs */

क्रमागत global_control_bits अणु
	CHANNEL_IDX	= 0x0000003f,
	OVERRUN_IE	= 0x00000400,	/* पूर्णांकerrupt enable: capture overrun */
	UNDERRUN_IE	= 0x00000800,	/* पूर्णांकerrupt enable: playback underrun */
	ENDLP_IE	= 0x00001000,	/* पूर्णांकerrupt enable: end of buffer */
	MIDLP_IE	= 0x00002000,	/* पूर्णांकerrupt enable: middle buffer */
	ETOG_IE		= 0x00004000,	/* पूर्णांकerrupt enable: envelope toggling */
	EDROP_IE	= 0x00008000,	/* पूर्णांकerrupt enable: envelope drop */
	BANK_B_EN	= 0x00010000,	/* SiS: enable bank B (64 channels) */
	PCMIN_B_MIX	= 0x00020000,	/* SiS: PCM IN B mixing enable */
	I2S_OUT_ASSIGN	= 0x00040000,	/* SiS: I2S Out contains surround PCM */
	SPDIF_OUT_ASSIGN= 0x00080000,	/* SiS: 0=S/PDIF L/R | 1=PCM Out FIFO */
	MAIN_OUT_ASSIGN = 0x00100000,	/* SiS: 0=PCM Out FIFO | 1=MMC Out buffer */
पूर्ण;

क्रमागत miscपूर्णांक_bits अणु
	PB_UNDERRUN_IRQ = 0x00000001, REC_OVERRUN_IRQ = 0x00000002,
	SB_IRQ		= 0x00000004, MPU401_IRQ      = 0x00000008,
	OPL3_IRQ        = 0x00000010, ADDRESS_IRQ     = 0x00000020,
	ENVELOPE_IRQ    = 0x00000040, PB_UNDERRUN     = 0x00000100,
	REC_OVERRUN	= 0x00000200, MIXER_UNDERFLOW = 0x00000400,
	MIXER_OVERFLOW  = 0x00000800, NX_SB_IRQ_DISABLE = 0x00001000,
        ST_TARGET_REACHED = 0x00008000,
	PB_24K_MODE     = 0x00010000, ST_IRQ_EN       = 0x00800000,
	ACGPIO_IRQ	= 0x01000000
पूर्ण;

/* T2 legacy dma control रेजिस्टरs. */
#घोषणा LEGACY_DMAR0                0x00  // ADR0
#घोषणा LEGACY_DMAR4                0x04  // CNT0
#घोषणा LEGACY_DMAR6		    0x06  // CNT0 - High bits
#घोषणा LEGACY_DMAR11               0x0b  // MOD 
#घोषणा LEGACY_DMAR15               0x0f  // MMR 

#घोषणा T4D_START_A		     0x80
#घोषणा T4D_STOP_A		     0x84
#घोषणा T4D_DLY_A		     0x88
#घोषणा T4D_SIGN_CSO_A		     0x8c
#घोषणा T4D_CSPF_A		     0x90
#घोषणा T4D_CSPF_B		     0xbc
#घोषणा T4D_CEBC_A		     0x94
#घोषणा T4D_AINT_A		     0x98
#घोषणा T4D_AINTEN_A		     0x9c
#घोषणा T4D_LFO_GC_CIR               0xa0
#घोषणा T4D_MUSICVOL_WAVEVOL         0xa8
#घोषणा T4D_SBDELTA_DELTA_R          0xac
#घोषणा T4D_MISCINT                  0xb0
#घोषणा T4D_START_B                  0xb4
#घोषणा T4D_STOP_B                   0xb8
#घोषणा T4D_SBBL_SBCL                0xc0
#घोषणा T4D_SBCTRL_SBE2R_SBDD        0xc4
#घोषणा T4D_STIMER		     0xc8
#घोषणा T4D_AINT_B                   0xd8
#घोषणा T4D_AINTEN_B                 0xdc
#घोषणा T4D_RCI                      0x70

/* MPU-401 UART */
#घोषणा T4D_MPU401_BASE             0x20
#घोषणा T4D_MPUR0                   0x20
#घोषणा T4D_MPUR1                   0x21
#घोषणा T4D_MPUR2                   0x22
#घोषणा T4D_MPUR3                   0x23

/* S/PDIF Registers */
#घोषणा NX_SPCTRL_SPCSO             0x24
#घोषणा NX_SPLBA                    0x28
#घोषणा NX_SPESO                    0x2c
#घोषणा NX_SPCSTATUS                0x64

/* Joystick */
#घोषणा GAMEPORT_GCR                0x30
#घोषणा GAMEPORT_MODE_ADC           0x80
#घोषणा GAMEPORT_LEGACY             0x31
#घोषणा GAMEPORT_AXES               0x34

/* NX Specअगरic Registers */
#घोषणा NX_TLBC                     0x6c

/* Channel Registers */

#घोषणा CH_START		    0xe0

#घोषणा CH_DX_CSO_ALPHA_FMS         0xe0
#घोषणा CH_DX_ESO_DELTA             0xe8
#घोषणा CH_DX_FMC_RVOL_CVOL         0xec

#घोषणा CH_NX_DELTA_CSO             0xe0
#घोषणा CH_NX_DELTA_ESO             0xe8
#घोषणा CH_NX_ALPHA_FMS_FMC_RVOL_CVOL 0xec

#घोषणा CH_LBA                      0xe4
#घोषणा CH_GVSEL_PAN_VOL_CTRL_EC    0xf0
#घोषणा CH_EBUF1                    0xf4
#घोषणा CH_EBUF2                    0xf8

/* AC-97 Registers */

#घोषणा DX_ACR0_AC97_W              0x40
#घोषणा DX_ACR1_AC97_R              0x44
#घोषणा DX_ACR2_AC97_COM_STAT       0x48

#घोषणा NX_ACR0_AC97_COM_STAT       0x40
#घोषणा NX_ACR1_AC97_W              0x44
#घोषणा NX_ACR2_AC97_R_PRIMARY      0x48
#घोषणा NX_ACR3_AC97_R_SECONDARY    0x4c

#घोषणा SI_AC97_WRITE		    0x40
#घोषणा SI_AC97_READ		    0x44
#घोषणा SI_SERIAL_INTF_CTRL	    0x48
#घोषणा SI_AC97_GPIO		    0x4c
#घोषणा SI_ASR0			    0x50
#घोषणा SI_SPDIF_CS		    0x70
#घोषणा SI_GPIO			    0x7c

क्रमागत trident_nx_ac97_bits अणु
	/* ACR1-3 */
	NX_AC97_BUSY_WRITE 	= 0x0800,
	NX_AC97_BUSY_READ	= 0x0800,
	NX_AC97_BUSY_DATA 	= 0x0400,
	NX_AC97_WRITE_SECONDARY = 0x0100,
	/* ACR0 */
	NX_AC97_SECONDARY_READY = 0x0040,
	NX_AC97_SECONDARY_RECORD = 0x0020,
	NX_AC97_SURROUND_OUTPUT = 0x0010,
	NX_AC97_PRIMARY_READY	= 0x0008,
	NX_AC97_PRIMARY_RECORD	= 0x0004,
	NX_AC97_PCM_OUTPUT	= 0x0002,
	NX_AC97_WARM_RESET	= 0x0001
पूर्ण;

क्रमागत trident_dx_ac97_bits अणु
	DX_AC97_BUSY_WRITE	= 0x8000,
	DX_AC97_BUSY_READ	= 0x8000,
	DX_AC97_READY		= 0x0010,
	DX_AC97_RECORD		= 0x0008,
	DX_AC97_PLAYBACK	= 0x0002
पूर्ण;

क्रमागत sis7018_ac97_bits अणु
	SI_AC97_BUSY_WRITE =	0x00008000,
	SI_AC97_AUDIO_BUSY =	0x00004000,
	SI_AC97_MODEM_BUSY =	0x00002000,
	SI_AC97_BUSY_READ =	0x00008000,
	SI_AC97_SECONDARY =	0x00000080,
पूर्ण;

क्रमागत serial_पूर्णांकf_ctrl_bits अणु
	WARM_RESET	= 0x00000001,
	COLD_RESET	= 0x00000002,
	I2S_CLOCK	= 0x00000004,
	PCM_SEC_AC97	= 0x00000008,
	AC97_DBL_RATE	= 0x00000010,
	SPDIF_EN	= 0x00000020,
	I2S_OUTPUT_EN	= 0x00000040,
	I2S_INPUT_EN	= 0x00000080,
	PCMIN		= 0x00000100,
	LINE1IN		= 0x00000200,
	MICIN		= 0x00000400,
	LINE2IN		= 0x00000800,
	HEAD_SET_IN	= 0x00001000,
	GPIOIN		= 0x00002000,
	/* 7018 spec says id = 01 but the demo board routed to 10
	   SECONDARY_ID= 0x00004000, */
	SECONDARY_ID	= 0x00004000,
	PCMOUT		= 0x00010000,
	SURROUT		= 0x00020000,
	CENTEROUT	= 0x00040000,
	LFEOUT		= 0x00080000,
	LINE1OUT	= 0x00100000,
	LINE2OUT	= 0x00200000,
	GPIOOUT		= 0x00400000,
	SI_AC97_PRIMARY_READY = 0x01000000,
	SI_AC97_SECONDARY_READY = 0x02000000,
	SI_AC97_POWERDOWN = 0x04000000,
पूर्ण;
                                                                                                                                   
/* PCM शेषs */

#घोषणा T4D_DEFAULT_PCM_VOL	10	/* 0 - 255 */
#घोषणा T4D_DEFAULT_PCM_PAN	0	/* 0 - 127 */
#घोषणा T4D_DEFAULT_PCM_RVOL	127	/* 0 - 127 */
#घोषणा T4D_DEFAULT_PCM_CVOL	127	/* 0 - 127 */

काष्ठा snd_trident;
काष्ठा snd_trident_voice;
काष्ठा snd_trident_pcm_mixer;

काष्ठा snd_trident_port अणु
	काष्ठा snd_midi_channel_set * chset;
	काष्ठा snd_trident * trident;
	पूर्णांक mode;		/* operation mode */
	पूर्णांक client;		/* sequencer client number */
	पूर्णांक port;		/* sequencer port number */
	अचिन्हित पूर्णांक midi_has_voices: 1;
पूर्ण;

काष्ठा snd_trident_memblk_arg अणु
	लघु first_page, last_page;
पूर्ण;

काष्ठा snd_trident_tlb अणु
	__le32 *entries;		/* 16k-aligned TLB table */
	dma_addr_t entries_dmaaddr;	/* 16k-aligned PCI address to TLB table */
	अचिन्हित दीर्घ * shaकरोw_entries;	/* shaकरोw entries with भव addresses */
	काष्ठा snd_dma_buffer buffer;
	काष्ठा snd_util_memhdr * memhdr;	/* page allocation list */
	काष्ठा snd_dma_buffer silent_page;
पूर्ण;

काष्ठा snd_trident_voice अणु
	अचिन्हित पूर्णांक number;
	अचिन्हित पूर्णांक use: 1,
	    pcm: 1,
	    synth:1,
	    midi: 1;
	अचिन्हित पूर्णांक flags;
	अचिन्हित अक्षर client;
	अचिन्हित अक्षर port;
	अचिन्हित अक्षर index;

	काष्ठा snd_trident_sample_ops *sample_ops;

	/* channel parameters */
	अचिन्हित पूर्णांक CSO;		/* 24 bits (16 on DX) */
	अचिन्हित पूर्णांक ESO;		/* 24 bits (16 on DX) */
	अचिन्हित पूर्णांक LBA;		/* 30 bits */
	अचिन्हित लघु EC;		/* 12 bits */
	अचिन्हित लघु Alpha;		/* 12 bits */
	अचिन्हित लघु Delta;		/* 16 bits */
	अचिन्हित लघु Attribute;	/* 16 bits - SiS 7018 */
	अचिन्हित लघु Vol;		/* 12 bits (6.6) */
	अचिन्हित अक्षर Pan;		/* 7 bits (1.4.2) */
	अचिन्हित अक्षर GVSel;		/* 1 bit */
	अचिन्हित अक्षर RVol;		/* 7 bits (5.2) */
	अचिन्हित अक्षर CVol;		/* 7 bits (5.2) */
	अचिन्हित अक्षर FMC;		/* 2 bits */
	अचिन्हित अक्षर CTRL;		/* 4 bits */
	अचिन्हित अक्षर FMS;		/* 4 bits */
	अचिन्हित अक्षर LFO;		/* 8 bits */

	अचिन्हित पूर्णांक negCSO;	/* nonzero - use negative CSO */

	काष्ठा snd_util_memblk *memblk;	/* memory block अगर TLB enabled */

	/* PCM data */

	काष्ठा snd_trident *trident;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_trident_voice *extra;	/* extra PCM voice (acts as पूर्णांकerrupt generator) */
	अचिन्हित पूर्णांक running: 1,
            capture: 1,
            spdअगर: 1,
            foldback: 1,
            isync: 1,
            isync2: 1,
            isync3: 1;
	पूर्णांक foldback_chan;		/* foldback subdevice number */
	अचिन्हित पूर्णांक sसमयr;		/* global sample समयr (to detect spurious पूर्णांकerrupts) */
	अचिन्हित पूर्णांक spurious_threshold; /* spurious threshold */
	अचिन्हित पूर्णांक isync_mark;
	अचिन्हित पूर्णांक isync_max;
	अचिन्हित पूर्णांक isync_ESO;

	/* --- */

	व्योम *निजी_data;
	व्योम (*निजी_मुक्त)(काष्ठा snd_trident_voice *voice);
पूर्ण;

काष्ठा snd_4dwave अणु
	पूर्णांक seq_client;

	काष्ठा snd_trident_port seq_ports[4];
	काष्ठा snd_trident_voice voices[64];	

	पूर्णांक ChanSynthCount;		/* number of allocated synth channels */
	पूर्णांक max_size;			/* maximum synth memory size in bytes */
	पूर्णांक current_size;		/* current allocated synth mem in bytes */
पूर्ण;

काष्ठा snd_trident_pcm_mixer अणु
	काष्ठा snd_trident_voice *voice;	/* active voice */
	अचिन्हित लघु vol;		/* front volume */
	अचिन्हित अक्षर pan;		/* pan control */
	अचिन्हित अक्षर rvol;		/* rear volume */
	अचिन्हित अक्षर cvol;		/* center volume */
	अचिन्हित अक्षर pad;
पूर्ण;

काष्ठा snd_trident अणु
	पूर्णांक irq;

	अचिन्हित पूर्णांक device;	/* device ID */

        अचिन्हित अक्षर  bDMAStart;

	अचिन्हित दीर्घ port;
	अचिन्हित दीर्घ midi_port;

	अचिन्हित पूर्णांक spurious_irq_count;
	अचिन्हित पूर्णांक spurious_irq_max_delta;

        काष्ठा snd_trident_tlb tlb;	/* TLB entries क्रम NX cards */

	अचिन्हित अक्षर spdअगर_ctrl;
	अचिन्हित अक्षर spdअगर_pcm_ctrl;
	अचिन्हित पूर्णांक spdअगर_bits;
	अचिन्हित पूर्णांक spdअगर_pcm_bits;
	काष्ठा snd_kcontrol *spdअगर_pcm_ctl;	/* S/PDIF settings */
	अचिन्हित पूर्णांक ac97_ctrl;
        
        अचिन्हित पूर्णांक ChanMap[2];	/* allocation map क्रम hardware channels */
        
        पूर्णांक ChanPCM;			/* max number of PCM channels */
	पूर्णांक ChanPCMcnt;			/* actual number of PCM channels */

	अचिन्हित पूर्णांक ac97_detect: 1;	/* 1 = AC97 in detection phase */
	अचिन्हित पूर्णांक in_suspend: 1;	/* 1 during suspend/resume */

	काष्ठा snd_4dwave synth;	/* synth specअगरic variables */

	spinlock_t event_lock;
	spinlock_t voice_alloc;

	काष्ठा snd_dma_device dma_dev;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;		/* ADC/DAC PCM */
	काष्ठा snd_pcm *foldback;	/* Foldback PCM */
	काष्ठा snd_pcm *spdअगर;	/* SPDIF PCM */
	काष्ठा snd_rawmidi *rmidi;

	काष्ठा snd_ac97_bus *ac97_bus;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_ac97 *ac97_sec;

	अचिन्हित पूर्णांक musicvol_wavevol;
	काष्ठा snd_trident_pcm_mixer pcm_mixer[32];
	काष्ठा snd_kcontrol *ctl_vol;	/* front volume */
	काष्ठा snd_kcontrol *ctl_pan;	/* pan */
	काष्ठा snd_kcontrol *ctl_rvol;	/* rear volume */
	काष्ठा snd_kcontrol *ctl_cvol;	/* center volume */

	spinlock_t reg_lock;

	काष्ठा gameport *gameport;
पूर्ण;

पूर्णांक snd_trident_create(काष्ठा snd_card *card,
		       काष्ठा pci_dev *pci,
		       पूर्णांक pcm_streams,
		       पूर्णांक pcm_spdअगर_device,
		       पूर्णांक max_wavetable_size,
		       काष्ठा snd_trident ** rtrident);
पूर्णांक snd_trident_create_gameport(काष्ठा snd_trident *trident);

पूर्णांक snd_trident_pcm(काष्ठा snd_trident *trident, पूर्णांक device);
पूर्णांक snd_trident_foldback_pcm(काष्ठा snd_trident *trident, पूर्णांक device);
पूर्णांक snd_trident_spdअगर_pcm(काष्ठा snd_trident *trident, पूर्णांक device);
पूर्णांक snd_trident_attach_synthesizer(काष्ठा snd_trident * trident);
काष्ठा snd_trident_voice *snd_trident_alloc_voice(काष्ठा snd_trident * trident, पूर्णांक type,
					     पूर्णांक client, पूर्णांक port);
व्योम snd_trident_मुक्त_voice(काष्ठा snd_trident * trident, काष्ठा snd_trident_voice *voice);
व्योम snd_trident_start_voice(काष्ठा snd_trident * trident, अचिन्हित पूर्णांक voice);
व्योम snd_trident_stop_voice(काष्ठा snd_trident * trident, अचिन्हित पूर्णांक voice);
व्योम snd_trident_ग_लिखो_voice_regs(काष्ठा snd_trident * trident, काष्ठा snd_trident_voice *voice);
बाह्य स्थिर काष्ठा dev_pm_ops snd_trident_pm;

/* TLB memory allocation */
काष्ठा snd_util_memblk *snd_trident_alloc_pages(काष्ठा snd_trident *trident,
						काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_trident_मुक्त_pages(काष्ठा snd_trident *trident, काष्ठा snd_util_memblk *blk);
काष्ठा snd_util_memblk *snd_trident_synth_alloc(काष्ठा snd_trident *trident, अचिन्हित पूर्णांक size);
पूर्णांक snd_trident_synth_मुक्त(काष्ठा snd_trident *trident, काष्ठा snd_util_memblk *blk);
पूर्णांक snd_trident_synth_copy_from_user(काष्ठा snd_trident *trident, काष्ठा snd_util_memblk *blk,
				     पूर्णांक offset, स्थिर अक्षर __user *data, पूर्णांक size);

#पूर्ण_अगर /* __SOUND_TRIDENT_H */
