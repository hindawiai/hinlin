<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _dmasound_h_
/*
 *  linux/sound/oss/dmasound/dmasound.h
 *
 *
 *  Minor numbers क्रम the sound driver.
 *
 *  Unक्रमtunately Creative called the codec chip of SB as a DSP. For this
 *  reason the /dev/dsp is reserved क्रम digitized audio use. There is a
 *  device क्रम true DSP processors but it will be called something अन्यथा.
 *  In v3.0 it's /dev/sndproc but this could be a temporary solution.
 */
#घोषणा _dmasound_h_

#समावेश <linux/types.h>

#घोषणा SND_NDEVS	256	/* Number of supported devices */
#घोषणा SND_DEV_CTL	0	/* Control port /dev/mixer */
#घोषणा SND_DEV_SEQ	1	/* Sequencer output /dev/sequencer (FM
				   synthesizer and MIDI output) */
#घोषणा SND_DEV_MIDIN	2	/* Raw midi access */
#घोषणा SND_DEV_DSP	3	/* Digitized voice /dev/dsp */
#घोषणा SND_DEV_AUDIO	4	/* Sparc compatible /dev/audio */
#घोषणा SND_DEV_DSP16	5	/* Like /dev/dsp but 16 bits/sample */
#घोषणा SND_DEV_STATUS	6	/* /dev/sndstat */
/* #7 not in use now. Was in 2.4. Free क्रम use after v3.0. */
#घोषणा SND_DEV_SEQ2	8	/* /dev/sequencer, level 2 पूर्णांकerface */
#घोषणा SND_DEV_SNDPROC 9	/* /dev/sndproc क्रम programmable devices */
#घोषणा SND_DEV_PSS	SND_DEV_SNDPROC

/* चयन on various prinks */
#घोषणा DEBUG_DMASOUND 1

#घोषणा MAX_AUDIO_DEV	5
#घोषणा MAX_MIXER_DEV	4
#घोषणा MAX_SYNTH_DEV	3
#घोषणा MAX_MIDI_DEV	6
#घोषणा MAX_TIMER_DEV	3

#घोषणा MAX_CATCH_RADIUS	10

#घोषणा le2be16(x)	(((x)<<8 & 0xff00) | ((x)>>8 & 0x00ff))
#घोषणा le2be16dbl(x)	(((x)<<8 & 0xff00ff00) | ((x)>>8 & 0x00ff00ff))

#घोषणा IOCTL_IN(arg, ret) \
	करो अणु पूर्णांक error = get_user(ret, (पूर्णांक __user *)(arg)); \
		अगर (error) वापस error; \
	पूर्ण जबतक (0)
#घोषणा IOCTL_OUT(arg, ret)	ioctl_वापस((पूर्णांक __user *)(arg), ret)

अटल अंतरभूत पूर्णांक ioctl_वापस(पूर्णांक __user *addr, पूर्णांक value)
अणु
	वापस value < 0 ? value : put_user(value, addr);
पूर्ण


    /*
     *  Configuration
     */

#अघोषित HAS_8BIT_TABLES

#अगर defined(CONFIG_DMASOUND_ATARI) || defined(CONFIG_DMASOUND_ATARI_MODULE) ||\
    defined(CONFIG_DMASOUND_PAULA) || defined(CONFIG_DMASOUND_PAULA_MODULE) ||\
    defined(CONFIG_DMASOUND_Q40) || defined(CONFIG_DMASOUND_Q40_MODULE)
#घोषणा HAS_8BIT_TABLES
#घोषणा MIN_BUFFERS	4
#घोषणा MIN_बफ_मानE	(1<<12)	/* in bytes (- where करोes this come from ?) */
#घोषणा MIN_FRAG_SIZE	8	/* not 100% sure about this */
#घोषणा MAX_बफ_मानE	(1<<17)	/* Limit क्रम Amiga is 128 kb */
#घोषणा MAX_FRAG_SIZE	15	/* allow *4 क्रम mono-8 => stereo-16 (क्रम multi) */

#अन्यथा /* is pmac and multi is off */

#घोषणा MIN_BUFFERS	2
#घोषणा MIN_बफ_मानE	(1<<8)	/* in bytes */
#घोषणा MIN_FRAG_SIZE	8
#घोषणा MAX_बफ_मानE	(1<<18)	/* this is somewhat arbitrary क्रम pmac */
#घोषणा MAX_FRAG_SIZE	16	/* need to allow *4 क्रम mono-8 => stereo-16 */
#पूर्ण_अगर

#घोषणा DEFAULT_N_BUFFERS 4
#घोषणा DEFAULT_BUFF_SIZE (1<<15)

    /*
     *  Initialization
     */

बाह्य पूर्णांक dmasound_init(व्योम);
#अगर_घोषित MODULE
बाह्य व्योम dmasound_deinit(व्योम);
#अन्यथा
#घोषणा dmasound_deinit()	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/* description of the set-up applies to either hard or soft settings */

प्रकार काष्ठा अणु
    पूर्णांक क्रमmat;		/* AFMT_* */
    पूर्णांक stereo;		/* 0 = mono, 1 = stereo */
    पूर्णांक size;		/* 8/16 bit*/
    पूर्णांक speed;		/* speed */
पूर्ण SETTINGS;

    /*
     *  Machine definitions
     */

प्रकार काष्ठा अणु
    स्थिर अक्षर *name;
    स्थिर अक्षर *name2;
    काष्ठा module *owner;
    व्योम *(*dma_alloc)(अचिन्हित पूर्णांक, gfp_t);
    व्योम (*dma_मुक्त)(व्योम *, अचिन्हित पूर्णांक);
    पूर्णांक (*irqinit)(व्योम);
#अगर_घोषित MODULE
    व्योम (*irqcleanup)(व्योम);
#पूर्ण_अगर
    व्योम (*init)(व्योम);
    व्योम (*silence)(व्योम);
    पूर्णांक (*setFormat)(पूर्णांक);
    पूर्णांक (*setVolume)(पूर्णांक);
    पूर्णांक (*setBass)(पूर्णांक);
    पूर्णांक (*setTreble)(पूर्णांक);
    पूर्णांक (*setGain)(पूर्णांक);
    व्योम (*play)(व्योम);
    व्योम (*record)(व्योम);		/* optional */
    व्योम (*mixer_init)(व्योम);		/* optional */
    पूर्णांक (*mixer_ioctl)(u_पूर्णांक, u_दीर्घ);	/* optional */
    पूर्णांक (*ग_लिखो_sq_setup)(व्योम);	/* optional */
    पूर्णांक (*पढ़ो_sq_setup)(व्योम);		/* optional */
    पूर्णांक (*sq_खोलो)(भ_शेषe_t);		/* optional */
    पूर्णांक (*state_info)(अक्षर *, माप_प्रकार);	/* optional */
    व्योम (*पात_पढ़ो)(व्योम);		/* optional */
    पूर्णांक min_dsp_speed;
    पूर्णांक max_dsp_speed;
    पूर्णांक version ;
    पूर्णांक hardware_afmts ;		/* OSS says we only वापस h'ware info */
					/* when queried via SNDCTL_DSP_GETFMTS */
    पूर्णांक capabilities ;		/* low-level reply to SNDCTL_DSP_GETCAPS */
    SETTINGS शेष_hard ;	/* खोलो() or init() should set something valid */
    SETTINGS शेष_soft ;	/* you can make it look like old OSS, अगर you want to */
पूर्ण MACHINE;

    /*
     *  Low level stuff
     */

प्रकार काष्ठा अणु
    sमाप_प्रकार (*ct_ulaw)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_alaw)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_s8)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_u8)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_s16be)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_u16be)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_s16le)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
    sमाप_प्रकार (*ct_u16le)(स्थिर u_अक्षर __user *, माप_प्रकार, u_अक्षर *, sमाप_प्रकार *, sमाप_प्रकार);
पूर्ण TRANS;

काष्ठा sound_settings अणु
    MACHINE mach;	/* machine dependent things */
    SETTINGS hard;	/* hardware settings */
    SETTINGS soft;	/* software settings */
    SETTINGS dsp;	/* /dev/dsp शेष settings */
    TRANS *trans_ग_लिखो;	/* supported translations */
    पूर्णांक volume_left;	/* volume (range is machine dependent) */
    पूर्णांक volume_right;
    पूर्णांक bass;		/* tone (range is machine dependent) */
    पूर्णांक treble;
    पूर्णांक gain;
    पूर्णांक minDev;		/* minor device number currently खोलो */
    spinlock_t lock;
पूर्ण;

बाह्य काष्ठा sound_settings dmasound;

#अगर_घोषित HAS_8BIT_TABLES
बाह्य अक्षर dmasound_ulaw2dma8[];
बाह्य अक्षर dmasound_alaw2dma8[];
#पूर्ण_अगर

    /*
     *  Mid level stuff
     */

अटल अंतरभूत पूर्णांक dmasound_set_volume(पूर्णांक volume)
अणु
	वापस dmasound.mach.setVolume(volume);
पूर्ण

अटल अंतरभूत पूर्णांक dmasound_set_bass(पूर्णांक bass)
अणु
	वापस dmasound.mach.setBass ? dmasound.mach.setBass(bass) : 50;
पूर्ण

अटल अंतरभूत पूर्णांक dmasound_set_treble(पूर्णांक treble)
अणु
	वापस dmasound.mach.setTreble ? dmasound.mach.setTreble(treble) : 50;
पूर्ण

अटल अंतरभूत पूर्णांक dmasound_set_gain(पूर्णांक gain)
अणु
	वापस dmasound.mach.setGain ? dmasound.mach.setGain(gain) : 100;
पूर्ण


    /*
     * Sound queue stuff, the heart of the driver
     */

काष्ठा sound_queue अणु
    /* buffers allocated क्रम this queue */
    पूर्णांक numBufs;		/* real limits on what the user can have */
    पूर्णांक bufSize;		/* in bytes */
    अक्षर **buffers;

    /* current parameters */
    पूर्णांक locked ;		/* params cannot be modअगरied when != 0 */
    पूर्णांक user_frags ;		/* user requests this many */
    पूर्णांक user_frag_size ;	/* of this size */
    पूर्णांक max_count;		/* actual # fragments <= numBufs */
    पूर्णांक block_size;		/* पूर्णांकernal block size in bytes */
    पूर्णांक max_active;		/* in-use fragments <= max_count */

    /* it shouldn't be necessary to declare any of these अस्थिर */
    पूर्णांक front, rear, count;
    पूर्णांक rear_size;
    /*
     *	The use of the playing field depends on the hardware
     *
     *	Atari, PMac: The number of frames that are loaded/playing
     *
     *	Amiga: Bit 0 is set: a frame is loaded
     *	       Bit 1 is set: a frame is playing
     */
    पूर्णांक active;
    रुको_queue_head_t action_queue, खोलो_queue, sync_queue;
    पूर्णांक non_blocking;
    पूर्णांक busy, syncing, xruns, died;
पूर्ण;

#घोषणा WAKE_UP(queue)		(wake_up_पूर्णांकerruptible(&queue))

बाह्य काष्ठा sound_queue dmasound_ग_लिखो_sq;
#घोषणा ग_लिखो_sq	dmasound_ग_लिखो_sq

बाह्य पूर्णांक dmasound_catchRadius;
#घोषणा catchRadius	dmasound_catchRadius

/* define the value to be put in the byte-swap reg in mac-io
   when we want it to swap क्रम us.
*/
#घोषणा BS_VAL 1

#घोषणा SW_INPUT_VOLUME_SCALE	4
#घोषणा SW_INPUT_VOLUME_DEFAULT	(128 / SW_INPUT_VOLUME_SCALE)

बाह्य पूर्णांक expand_पढ़ो_bal;	/* Balance factor क्रम पढ़ोing */
बाह्य uपूर्णांक software_input_volume; /* software implemented recording volume! */

#पूर्ण_अगर /* _dmasound_h_ */
