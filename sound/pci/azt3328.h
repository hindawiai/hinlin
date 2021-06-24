<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SOUND_AZT3328_H
#घोषणा __SOUND_AZT3328_H

/* "PU" == "power-up value", as tested on PCI168 PCI rev. 10
 * "WRITE_ONLY"  == रेजिस्टर करोes not indicate actual bit values */

/*** मुख्य I/O area port indices ***/
/* (only 0x70 of 0x80 bytes saved/restored by Winकरोws driver) */
#घोषणा AZF_IO_SIZE_CTRL	0x80
#घोषणा AZF_IO_SIZE_CTRL_PM	0x70

/* the driver initialisation suggests a layout of 4 areas
 * within the मुख्य card control I/O:
 * from 0x00 (playback codec), from 0x20 (recording codec)
 * and from 0x40 (most certainly I2S out codec).
 * And another area from 0x60 to 0x6f (DirectX समयr, IRQ management,
 * घातer management etc.???). */

#घोषणा AZF_IO_OFFS_CODEC_PLAYBACK	0x00
#घोषणा AZF_IO_OFFS_CODEC_CAPTURE	0x20
#घोषणा AZF_IO_OFFS_CODEC_I2S_OUT	0x40

#घोषणा IDX_IO_CODEC_DMA_FLAGS       0x00 /* PU:0x0000 */
     /* able to reactivate output after output muting due to 8/16bit
      * output change, just like 0x0002.
      * 0x0001 is the only bit that's able to start the DMA counter */
  #घोषणा DMA_RESUME			0x0001 /* छोड़ोd अगर cleared? */
     /* 0x0002 *temporarily* set during DMA stopping. hmm
      * both 0x0002 and 0x0004 set in playback setup. */
     /* able to reactivate output after output muting due to 8/16bit
      * output change, just like 0x0001. */
  #घोषणा DMA_RUN_SOMETHING1		0x0002 /* \ alternated (toggled) */
     /* 0x0004: NOT able to reactivate output */
  #घोषणा DMA_RUN_SOMETHING2		0x0004 /* / bits */
  #घोषणा SOMETHING_ALMOST_ALWAYS_SET	0x0008 /* ???; can be modअगरied */
  #घोषणा DMA_EPILOGUE_SOMETHING	0x0010
  #घोषणा DMA_SOMETHING_ELSE		0x0020 /* ??? */
  #घोषणा SOMETHING_UNMODIFIABLE	0xffc0 /* unused? not modअगरiable */
#घोषणा IDX_IO_CODEC_IRQTYPE     0x02 /* PU:0x0001 */
  /* ग_लिखो back to flags in हाल flags are set, in order to ACK IRQ in handler
   * (bit 1 of port 0x64 indicates पूर्णांकerrupt क्रम one of these three types)
   * someबार in this हाल it just ग_लिखोs 0xffff to globally ACK all IRQs
   * settings written are not reflected when पढ़ोing back, though.
   * seems to be IRQ, too (frequently used: port |= 0x07 !), but who knows? */
  #घोषणा IRQ_SOMETHING			0x0001 /* something & ACK */
  #घोषणा IRQ_FINISHED_DMABUF_1		0x0002 /* 1st dmabuf finished & ACK */
  #घोषणा IRQ_FINISHED_DMABUF_2		0x0004 /* 2nd dmabuf finished & ACK */
  #घोषणा IRQMASK_SOME_STATUS_1		0x0008 /* \ related bits */
  #घोषणा IRQMASK_SOME_STATUS_2		0x0010 /* / (checked together in loop) */
  #घोषणा IRQMASK_UNMODIFIABLE		0xffe0 /* unused? not modअगरiable */
  /* start address of 1st DMA transfer area, PU:0x00000000 */
#घोषणा IDX_IO_CODEC_DMA_START_1 0x04
  /* start address of 2nd DMA transfer area, PU:0x00000000 */
#घोषणा IDX_IO_CODEC_DMA_START_2 0x08
  /* both lengths of DMA transfer areas, PU:0x00000000
     length1: offset 0x0c, length2: offset 0x0e */
#घोषणा IDX_IO_CODEC_DMA_LENGTHS 0x0c
#घोषणा IDX_IO_CODEC_DMA_CURRPOS 0x10 /* current DMA position, PU:0x00000000 */
  /* offset within current DMA transfer area, PU:0x0000 */
#घोषणा IDX_IO_CODEC_DMA_CURROFS 0x14
#घोषणा IDX_IO_CODEC_SOUNDFORMAT 0x16 /* PU:0x0010 */
  /* all unspecअगरied bits can't be modअगरied */
  #घोषणा SOUNDFORMAT_FREQUENCY_MASK	0x000f
  #घोषणा SOUNDFORMAT_XTAL1		0x00
  #घोषणा SOUNDFORMAT_XTAL2		0x01
    /* all _SUSPECTED_ values are not used by Winकरोws drivers, so we करोn't
     * have any hard facts, only rough measurements.
     * All we know is that the crystal used on the board has 24.576MHz,
     * like many soundcards (which results in the frequencies below when
     * using certain भागider values selected by the values below) */
    #घोषणा SOUNDFORMAT_FREQ_SUSPECTED_4000	0x0c | SOUNDFORMAT_XTAL1
    #घोषणा SOUNDFORMAT_FREQ_SUSPECTED_4800	0x0a | SOUNDFORMAT_XTAL1
    #घोषणा SOUNDFORMAT_FREQ_5510		0x0c | SOUNDFORMAT_XTAL2
    #घोषणा SOUNDFORMAT_FREQ_6620		0x0a | SOUNDFORMAT_XTAL2
    #घोषणा SOUNDFORMAT_FREQ_8000		0x00 | SOUNDFORMAT_XTAL1 /* also 0x0e | SOUNDFORMAT_XTAL1? */
    #घोषणा SOUNDFORMAT_FREQ_9600		0x08 | SOUNDFORMAT_XTAL1
    #घोषणा SOUNDFORMAT_FREQ_11025		0x00 | SOUNDFORMAT_XTAL2 /* also 0x0e | SOUNDFORMAT_XTAL2? */
    #घोषणा SOUNDFORMAT_FREQ_SUSPECTED_13240	0x08 | SOUNDFORMAT_XTAL2 /* seems to be 6620 *2 */
    #घोषणा SOUNDFORMAT_FREQ_16000		0x02 | SOUNDFORMAT_XTAL1
    #घोषणा SOUNDFORMAT_FREQ_22050		0x02 | SOUNDFORMAT_XTAL2
    #घोषणा SOUNDFORMAT_FREQ_32000		0x04 | SOUNDFORMAT_XTAL1
    #घोषणा SOUNDFORMAT_FREQ_44100		0x04 | SOUNDFORMAT_XTAL2
    #घोषणा SOUNDFORMAT_FREQ_48000		0x06 | SOUNDFORMAT_XTAL1
    #घोषणा SOUNDFORMAT_FREQ_SUSPECTED_66200	0x06 | SOUNDFORMAT_XTAL2 /* 66200 (13240 * 5); 64000 may have been nicer :-\ */
  #घोषणा SOUNDFORMAT_FLAG_16BIT	0x0010
  #घोषणा SOUNDFORMAT_FLAG_2CHANNELS	0x0020


/* define frequency helpers, क्रम maximum value safety */
क्रमागत azf_freq_t अणु
#घोषणा AZF_FREQ(rate) AZF_FREQ_##rate = rate
  AZF_FREQ(4000),
  AZF_FREQ(4800),
  AZF_FREQ(5512),
  AZF_FREQ(6620),
  AZF_FREQ(8000),
  AZF_FREQ(9600),
  AZF_FREQ(11025),
  AZF_FREQ(13240),
  AZF_FREQ(16000),
  AZF_FREQ(22050),
  AZF_FREQ(32000),
  AZF_FREQ(44100),
  AZF_FREQ(48000),
  AZF_FREQ(66200),
#अघोषित AZF_FREQ
पूर्ण;

/** DirectX समयr, मुख्य पूर्णांकerrupt area (FIXME: and something अन्यथा?) **/ 
#घोषणा IDX_IO_TIMER_VALUE	0x60 /* found this समयr area by pure luck :-) */
  /* समयr countकरोwn value; triggers IRQ when समयr is finished */
  #घोषणा TIMER_VALUE_MASK		0x000fffffUL
  /* activate समयr countकरोwn */
  #घोषणा TIMER_COUNTDOWN_ENABLE	0x01000000UL
  /* trigger समयr IRQ on zero transition */
  #घोषणा TIMER_IRQ_ENABLE		0x02000000UL
  /* being set in IRQ handler in हाल port 0x00 (hmm, not port 0x64!?!?)
   * had 0x0020 set upon IRQ handler */
  #घोषणा TIMER_IRQ_ACK			0x04000000UL
#घोषणा IDX_IO_IRQSTATUS        0x64
  /* some IRQ bit in here might also be used to संकेत a घातer-management समयr
   * समयout, to request shutकरोwn of the chip (e.g. AD1815JS has such a thing).
   * OPL3 hardware contains several समयrs which confusingly in most हालs
   * are NOT routed to an IRQ, but some designs (e.g. LM4560) DO support that,
   * so I wouldn't be surprised at all to discover that AZF3328
   * supports that thing as well... */

  #घोषणा IRQ_PLAYBACK	0x0001
  #घोषणा IRQ_RECORDING	0x0002
  #घोषणा IRQ_I2S_OUT	0x0004 /* this IS I2S, right!? (untested) */
  #घोषणा IRQ_GAMEPORT	0x0008 /* Interrupt of Digital(ly) Enhanced Game Port */
  #घोषणा IRQ_MPU401	0x0010
  #घोषणा IRQ_TIMER	0x0020 /* DirectX समयr */
  #घोषणा IRQ_UNKNOWN2	0x0040 /* probably unused, or possibly OPL3 समयr? */
  #घोषणा IRQ_UNKNOWN3	0x0080 /* probably unused, or possibly OPL3 समयr? */
#घोषणा IDX_IO_66H		0x66    /* writing 0xffff वापसs 0x0000 */
  /* this is set to e.g. 0x3ff or 0x300, and writable;
   * maybe some buffer limit, but I couldn't find out more, PU:0x00ff: */
#घोषणा IDX_IO_SOME_VALUE	0x68
  #घोषणा IO_68_RANDOM_TOGGLE1	0x0100	/* toggles अक्रमomly */
  #घोषणा IO_68_RANDOM_TOGGLE2	0x0200	/* toggles अक्रमomly */
  /* umm, nope, behaviour of these bits changes depending on what we wrote
   * to 0x6b!!
   * And they change upon playback/stop, too:
   * Writing a value to 0x68 will display this exact value during playback,
   * too but when stopped it can fall back to a rather dअगरferent
   * seemingly अक्रमom value). Hmm, possibly this is a रेजिस्टर which
   * has a remote shaकरोw which needs proper device supply which only exists
   * in हाल playback is active? Or is this driver-induced?
   */

/* this WORD can be set to have bits 0x0028 activated (FIXME: correct??);
 * actually inhibits PCM playback!!! maybe घातer management??: */
#घोषणा IDX_IO_6AH		0x6A /* WRITE_ONLY! */
  /* bit 5: enabling this will activate permanent counting of bytes 2/3
   * at gameport I/O (0xb402/3) (equal values each) and cause
   * gameport legacy I/O at 0x0200 to be _DISABLED_!
   * Is this Digital Enhanced Game Port Enable??? Or maybe it's Tesपंचांगode
   * क्रम Enhanced Digital Gameport (see 4D Wave DX card): */
  #घोषणा IO_6A_SOMETHING1_GAMEPORT	0x0020
  /* bit 8; sure, this _छोड़ोs_ playback (later resumes at same spot!),
   * but what the heck is this really about??: */
  #घोषणा IO_6A_PAUSE_PLAYBACK_BIT8	0x0100
  /* bit 9; sure, this _छोड़ोs_ playback (later resumes at same spot!),
   * but what the heck is this really about??: */
  #घोषणा IO_6A_PAUSE_PLAYBACK_BIT9	0x0200
	/* BIT8 and BIT9 are _NOT_ able to affect OPL3 MIDI playback,
	 * thus it suggests influence on PCM only!!
	 * However OTOH there seems to be no bit anywhere around here
	 * which is able to disable OPL3... */
  /* bit 10: enabling this actually changes values at legacy gameport
   * I/O address (0x200); is this enabling of the Digital Enhanced Game Port???
   * Or maybe this simply चयनes off the NE558 circuit, since enabling this
   * still lets us evaluate button states, but not axis states */
  #घोषणा IO_6A_SOMETHING2_GAMEPORT      0x0400
	/* writing 0x0300: causes quite some crackling during
	 * PC activity such as चयनing winकरोws (PCI traffic??
	 * --> FIFO/timing settings???) */
	/* writing 0x0100 plus/or 0x0200 inhibits playback */
	/* since the Winकरोws .INF file has Flag_Enable_JoyStick and
	 * Flag_Enable_SB_DOS_Emulation directly together, it stands to reason
	 * that some other bit in this same रेजिस्टर might be responsible
	 * क्रम SB DOS Emulation activation (note that the file did NOT define
	 * a चयन क्रम OPL3!) */
#घोषणा IDX_IO_6CH		0x6C	/* unknown; fully पढ़ो-writable */
#घोषणा IDX_IO_6EH		0x6E
	/* writing 0xffff वापसs 0x83fe (or 0x03fe only).
	 * writing 0x83 (and only 0x83!!) to 0x6f will cause 0x6c to चयन
	 * from 0000 to ffff. */

/* further I/O indices not saved/restored and not पढ़ोable after writing,
 * so probably not used */


/*** Gameport area port indices ***/
/* (only 0x06 of 0x08 bytes saved/restored by Winकरोws driver) */ 
#घोषणा AZF_IO_SIZE_GAME		0x08
#घोषणा AZF_IO_SIZE_GAME_PM		0x06

क्रमागत अणु
	AZF_GAME_LEGACY_IO_PORT = 0x200
पूर्ण;

#घोषणा IDX_GAME_LEGACY_COMPATIBLE	0x00
	/* in some operation mode, writing anything to this port
	 * triggers an पूर्णांकerrupt:
	 * yup, that's in हाल IDX_GAME_01H has one of the
	 * axis measurement bits enabled
	 * (and of course one needs to have GAME_HWCFG_IRQ_ENABLE, too) */

#घोषणा IDX_GAME_AXES_CONFIG            0x01
	/* NOTE: layout of this रेजिस्टर awfully similar (पढ़ो: "identical??")
	 * to AD1815JS.pdf (p.29) */

  /* enables axis 1 (X axis) measurement: */
  #घोषणा GAME_AXES_ENABLE_1		0x01
  /* enables axis 2 (Y axis) measurement: */
  #घोषणा GAME_AXES_ENABLE_2		0x02
  /* enables axis 3 (X axis) measurement: */
  #घोषणा GAME_AXES_ENABLE_3		0x04
  /* enables axis 4 (Y axis) measurement: */
  #घोषणा GAME_AXES_ENABLE_4		0x08
  /* selects the current axis to पढ़ो the measured value of
   * (at IDX_GAME_AXIS_VALUE):
   * 00 = axis 1, 01 = axis 2, 10 = axis 3, 11 = axis 4: */
  #घोषणा GAME_AXES_READ_MASK		0x30
  /* enable to have the latch continuously accept ADC values
   * (and continuously cause पूर्णांकerrupts in हाल पूर्णांकerrupts are enabled);
   * AD1815JS.pdf says it's ~16ms पूर्णांकerval there: */
  #घोषणा GAME_AXES_LATCH_ENABLE	0x40
  /* joystick data (measured axes) पढ़ोy क्रम पढ़ोing: */
  #घोषणा GAME_AXES_SAMPLING_READY	0x80

  /* NOTE: other card specs (SiS960 and others!) state that the
   * game position latches should be frozen when पढ़ोing and be मुक्तd
   * (== reset?) after पढ़ोing!!!
   * Freezing most likely means disabling 0x40 (GAME_AXES_LATCH_ENABLE),
   *  but how to मुक्त the value? */
  /* An पूर्णांकernet search क्रम "gameport latch ADC" should provide some insight
   * पूर्णांकo how to program such a gameport प्रणाली. */

  /* writing 0xf0 to 01H once reset both counters to 0, in some special mode!?
   * yup, in हाल 6AH 0x20 is not enabled
   * (and 0x40 is sufficient, 0xf0 is not needed) */

#घोषणा IDX_GAME_AXIS_VALUE	0x02
	/* R: value of currently configured axis (word value!);
	 * W: trigger axis measurement */

#घोषणा IDX_GAME_HWCONFIG	0x04
	/* note: bits 4 to 7 are never set (== 0) when पढ़ोing!
	 * --> reserved bits? */
  /* enables IRQ notअगरication upon axes measurement पढ़ोy: */
  #घोषणा GAME_HWCFG_IRQ_ENABLE			0x01
  /* these bits choose a dअगरferent frequency क्रम the
   *  पूर्णांकernal ADC counter increment.
   * hmm, seems to be a combo of bits:
   * 00 --> standard frequency
   * 10 --> 1/2
   * 01 --> 1/20
   * 11 --> 1/200: */
  #घोषणा GAME_HWCFG_ADC_COUNTER_FREQ_MASK	0x06

  /* FIXME: these values might be reversed... */
  #घोषणा GAME_HWCFG_ADC_COUNTER_FREQ_STD	0
  #घोषणा GAME_HWCFG_ADC_COUNTER_FREQ_1_2	1
  #घोषणा GAME_HWCFG_ADC_COUNTER_FREQ_1_20	2
  #घोषणा GAME_HWCFG_ADC_COUNTER_FREQ_1_200	3

  /* enable gameport legacy I/O address (0x200)
   * I was unable to locate any configurability क्रम a dअगरferent address: */
  #घोषणा GAME_HWCFG_LEGACY_ADDRESS_ENABLE	0x08

/*** MPU401 ***/
#घोषणा AZF_IO_SIZE_MPU		0x04
#घोषणा AZF_IO_SIZE_MPU_PM	0x04

/*** OPL3 synth ***/
/* (only 0x06 of 0x08 bytes saved/restored by Winकरोws driver) */
#घोषणा AZF_IO_SIZE_OPL3	0x08
#घोषणा AZF_IO_SIZE_OPL3_PM	0x06
/* hmm, given that a standard OPL3 has 4 रेजिस्टरs only,
 * there might be some enhanced functionality lurking at the end
 * (especially since रेजिस्टर 0x04 has a "non-empty" value 0xfe) */

/*** mixer I/O area port indices ***/
/* (only 0x22 of 0x40 bytes saved/restored by Winकरोws driver)
 * UNFORTUNATELY azf3328 is NOT truly AC97 compliant: see मुख्य file पूर्णांकro */
#घोषणा AZF_IO_SIZE_MIXER	0x40
#घोषणा AZF_IO_SIZE_MIXER_PM	0x22

  #घोषणा MIXER_VOLUME_RIGHT_MASK	0x001f
  #घोषणा MIXER_VOLUME_LEFT_MASK	0x1f00
  #घोषणा MIXER_MUTE_MASK		0x8000
#घोषणा IDX_MIXER_RESET		0x00 /* करोes NOT seem to have AC97 ID bits */
#घोषणा IDX_MIXER_PLAY_MASTER   0x02
#घोषणा IDX_MIXER_MODEMOUT      0x04
#घोषणा IDX_MIXER_BASSTREBLE    0x06
  #घोषणा MIXER_BASSTREBLE_TREBLE_VOLUME_MASK	0x000e
  #घोषणा MIXER_BASSTREBLE_BASS_VOLUME_MASK	0x0e00
#घोषणा IDX_MIXER_PCBEEP        0x08
#घोषणा IDX_MIXER_MODEMIN       0x0a
#घोषणा IDX_MIXER_MIC           0x0c
  #घोषणा MIXER_MIC_MICGAIN_20DB_ENHANCEMENT_MASK	0x0040
#घोषणा IDX_MIXER_LINEIN        0x0e
#घोषणा IDX_MIXER_CDAUDIO       0x10
#घोषणा IDX_MIXER_VIDEO         0x12
#घोषणा IDX_MIXER_AUX           0x14
#घोषणा IDX_MIXER_WAVEOUT       0x16
#घोषणा IDX_MIXER_FMSYNTH       0x18
#घोषणा IDX_MIXER_REC_SELECT    0x1a
  #घोषणा MIXER_REC_SELECT_MIC		0x00
  #घोषणा MIXER_REC_SELECT_CD		0x01
  #घोषणा MIXER_REC_SELECT_VIDEO	0x02
  #घोषणा MIXER_REC_SELECT_AUX		0x03
  #घोषणा MIXER_REC_SELECT_LINEIN	0x04
  #घोषणा MIXER_REC_SELECT_MIXSTEREO	0x05
  #घोषणा MIXER_REC_SELECT_MIXMONO	0x06
  #घोषणा MIXER_REC_SELECT_MONOIN	0x07
#घोषणा IDX_MIXER_REC_VOLUME    0x1c
#घोषणा IDX_MIXER_ADVCTL1       0x1e
  /* unlisted bits are unmodअगरiable */
  #घोषणा MIXER_ADVCTL1_3DWIDTH_MASK	0x000e
  #घोषणा MIXER_ADVCTL1_HIFI3D_MASK	0x0300 /* yup, this is missing the high bit that official AC97 contains, plus it करोesn't have linear bit value range behaviour but instead acts weirdly (possibly we're dealing with two *dअगरferent* 3D settings here??) */
#घोषणा IDX_MIXER_ADVCTL2       0x20 /* subset of AC97_GENERAL_PURPOSE reg! */
  /* unlisted bits are unmodअगरiable */
  #घोषणा MIXER_ADVCTL2_LPBK		0x0080 /* Loopback mode -- Win driver: "WaveOut3DBypass"? mutes WaveOut at LineOut */
  #घोषणा MIXER_ADVCTL2_MS		0x0100 /* Mic Select 0=Mic1, 1=Mic2 -- Win driver: "ModemOutSelect"?? */
  #घोषणा MIXER_ADVCTL2_MIX		0x0200 /* Mono output select 0=Mix, 1=Mic; Win driver: "MonoSelectSource"?? */
  #घोषणा MIXER_ADVCTL2_3D		0x2000 /* 3D Enhancement 1=on */
  #घोषणा MIXER_ADVCTL2_POP		0x8000 /* Pcm Out Path, 0=pre 3D, 1=post 3D */
  
#घोषणा IDX_MIXER_SOMETHING30H	0x30 /* used, but unknown??? */

/* driver पूर्णांकernal flags */
#घोषणा SET_CHAN_LEFT	1
#घोषणा SET_CHAN_RIGHT	2

/* helper macro to align I/O port ranges to 32bit I/O width */
#घोषणा AZF_ALIGN(x) (((x) + 3) & (~3))

#पूर्ण_अगर /* __SOUND_AZT3328_H  */
