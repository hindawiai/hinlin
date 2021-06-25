<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SOUND_SND_WAVEFRONT_H__
#घोषणा __SOUND_SND_WAVEFRONT_H__

#समावेश <sound/mpu401.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/wavefront.h>  /* generic OSS/ALSA/user-level wavefront header */

/* MIDI पूर्णांकerface */

काष्ठा _snd_wavefront_midi;
काष्ठा _snd_wavefront_card;
काष्ठा _snd_wavefront;

प्रकार काष्ठा _snd_wavefront_midi snd_wavefront_midi_t;
प्रकार काष्ठा _snd_wavefront_card snd_wavefront_card_t;
प्रकार काष्ठा _snd_wavefront snd_wavefront_t;

प्रकार क्रमागत अणु पूर्णांकernal_mpu = 0, बाह्यal_mpu = 1 पूर्ण snd_wavefront_mpu_id;

काष्ठा _snd_wavefront_midi अणु
        अचिन्हित दीर्घ            base;        /* I/O port address */
	अक्षर                     isभव;   /* करोing भव MIDI stuff ? */
	अक्षर			 isसमयr;     /* समयr is used */
        snd_wavefront_mpu_id     output_mpu;  /* most-recently-used */
        snd_wavefront_mpu_id     input_mpu;   /* most-recently-used */
        अचिन्हित पूर्णांक             mode[2];     /* MPU401_MODE_XXX */
	काष्ठा snd_rawmidi_substream	 *substream_output[2];
	काष्ठा snd_rawmidi_substream	 *substream_input[2];
	काष्ठा समयr_list	 समयr;
	snd_wavefront_card_t	 *समयr_card;
        spinlock_t               खोलो;
        spinlock_t               भव;     /* protects isभव */
पूर्ण;

#घोषणा	OUTPUT_READY	0x40
#घोषणा	INPUT_AVAIL	0x80
#घोषणा	MPU_ACK		0xFE
#घोषणा	UART_MODE_ON	0x3F

बाह्य स्थिर काष्ठा snd_rawmidi_ops snd_wavefront_midi_output;
बाह्य स्थिर काष्ठा snd_rawmidi_ops snd_wavefront_midi_input;

बाह्य व्योम   snd_wavefront_midi_enable_भव (snd_wavefront_card_t *);
बाह्य व्योम   snd_wavefront_midi_disable_भव (snd_wavefront_card_t *);
बाह्य व्योम   snd_wavefront_midi_पूर्णांकerrupt (snd_wavefront_card_t *);
बाह्य पूर्णांक    snd_wavefront_midi_start (snd_wavefront_card_t *);

काष्ठा _snd_wavefront अणु
	अचिन्हित दीर्घ    irq;   /* "you were one, one of the few ..." */
	अचिन्हित दीर्घ    base;  /* low i/o port address */
	काष्ठा resource	 *res_base; /* i/o port resource allocation */

#घोषणा mpu_data_port    base 
#घोषणा mpu_command_port base + 1 /* ग_लिखो semantics */
#घोषणा mpu_status_port  base + 1 /* पढ़ो semantics */
#घोषणा data_port        base + 2 
#घोषणा status_port      base + 3 /* पढ़ो semantics */
#घोषणा control_port     base + 3 /* ग_लिखो semantics  */
#घोषणा block_port       base + 4 /* 16 bit, ग_लिखोonly */
#घोषणा last_block_port  base + 6 /* 16 bit, ग_लिखोonly */

	/* FX ports. These are mapped through the ICS2115 to the YS225.
	   The ICS2115 takes care of flipping the relevant pins on the
	   YS225 so that access to each of these ports करोes the right
	   thing. Note: these are NOT करोcumented by Turtle Beach.
	*/

#घोषणा fx_status       base + 8 
#घोषणा fx_op           base + 8 
#घोषणा fx_lcr          base + 9 
#घोषणा fx_dsp_addr     base + 0xa
#घोषणा fx_dsp_page     base + 0xb 
#घोषणा fx_dsp_lsb      base + 0xc 
#घोषणा fx_dsp_msb      base + 0xd 
#घोषणा fx_mod_addr     base + 0xe
#घोषणा fx_mod_data     base + 0xf 

	अस्थिर पूर्णांक irq_ok;               /* set by पूर्णांकerrupt handler */
        अस्थिर पूर्णांक irq_cnt;              /* ditto */
	अक्षर debug;                        /* debugging flags */
	पूर्णांक मुक्तmem;                       /* installed RAM, in bytes */ 

	अक्षर fw_version[2];                /* major = [0], minor = [1] */
	अक्षर hw_version[2];                /* major = [0], minor = [1] */
	अक्षर israw;                        /* needs Motorola microcode */
	अक्षर has_fx;                       /* has FX processor (Tropez+) */
	अक्षर fx_initialized;               /* FX's रेजिस्टर pages initialized */
	अक्षर prog_status[WF_MAX_PROGRAM];  /* WF_SLOT_* */
	अक्षर patch_status[WF_MAX_PATCH];   /* WF_SLOT_* */
	अक्षर sample_status[WF_MAX_SAMPLE]; /* WF_ST_* | WF_SLOT_* */
	पूर्णांक samples_used;                  /* how many */
	अक्षर पूर्णांकerrupts_are_midi;          /* h/w MPU पूर्णांकerrupts enabled ? */
	अक्षर rom_samples_rकरोnly;           /* can we ग_लिखो on ROM samples */
	spinlock_t irq_lock;
	रुको_queue_head_t पूर्णांकerrupt_sleeper; 
	snd_wavefront_midi_t midi;         /* ICS2115 MIDI पूर्णांकerface */
	काष्ठा snd_card *card;
पूर्ण;

काष्ठा _snd_wavefront_card अणु
	snd_wavefront_t wavefront;
#अगर_घोषित CONFIG_PNP
	काष्ठा pnp_dev *wss;
	काष्ठा pnp_dev *ctrl;
	काष्ठा pnp_dev *mpu;
	काष्ठा pnp_dev *synth;
#पूर्ण_अगर /* CONFIG_PNP */
पूर्ण;

बाह्य व्योम snd_wavefront_पूर्णांकernal_पूर्णांकerrupt (snd_wavefront_card_t *card);
बाह्य पूर्णांक  snd_wavefront_detect_irq (snd_wavefront_t *dev) ;
बाह्य पूर्णांक  snd_wavefront_check_irq (snd_wavefront_t *dev, पूर्णांक irq);
बाह्य पूर्णांक  snd_wavefront_restart (snd_wavefront_t *dev);
बाह्य पूर्णांक  snd_wavefront_start (snd_wavefront_t *dev);
बाह्य पूर्णांक  snd_wavefront_detect (snd_wavefront_card_t *card);
बाह्य पूर्णांक  snd_wavefront_config_midi (snd_wavefront_t *dev) ;
बाह्य पूर्णांक  snd_wavefront_cmd (snd_wavefront_t *, पूर्णांक, अचिन्हित अक्षर *,
			       अचिन्हित अक्षर *);

बाह्य पूर्णांक snd_wavefront_synth_ioctl   (काष्ठा snd_hwdep *, 
					काष्ठा file *,
					अचिन्हित पूर्णांक cmd, 
					अचिन्हित दीर्घ arg);
बाह्य पूर्णांक  snd_wavefront_synth_खोलो    (काष्ठा snd_hwdep *, काष्ठा file *);
बाह्य पूर्णांक  snd_wavefront_synth_release (काष्ठा snd_hwdep *, काष्ठा file *);

/* FX processor - see also yss225.[ch] */

बाह्य पूर्णांक  snd_wavefront_fx_start  (snd_wavefront_t *);
बाह्य पूर्णांक  snd_wavefront_fx_detect (snd_wavefront_t *);
बाह्य पूर्णांक  snd_wavefront_fx_ioctl  (काष्ठा snd_hwdep *, 
				     काष्ठा file *,
				     अचिन्हित पूर्णांक cmd, 
				     अचिन्हित दीर्घ arg);
बाह्य पूर्णांक snd_wavefront_fx_खोलो    (काष्ठा snd_hwdep *, काष्ठा file *);
बाह्य पूर्णांक snd_wavefront_fx_release (काष्ठा snd_hwdep *, काष्ठा file *);

/* prefix in all snd_prपूर्णांकk() delivered messages */

#घोषणा LOGNAME "WaveFront: "

#पूर्ण_अगर  /* __SOUND_SND_WAVEFRONT_H__ */
