<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Mac bong noise generator. Note - we ought to put a boingy noise
 *	here 8)
 *
 *	----------------------------------------------------------------------
 *	16.11.98:
 *	rewrote some functions, added support क्रम Enhanced ASC (Quadras)
 *	after the NetBSD asc.c console bell patch by Colin Wood/Frederick Bruck
 *	Juergen Mellinger (juergen.mellinger@t-online.de)
 */

#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>

#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/mac_asc.h>

अटल पूर्णांक mac_asc_inited;
/*
 * dumb triangular wave table
 */
अटल __u8 mac_asc_wave_tab[ 0x800 ];

/*
 * Alan's original sine table; needs पूर्णांकerpolating to 0x800
 * (hपूर्णांक: पूर्णांकerpolate or hardwire [0 -> Pi/2[, it's symmetric)
 */
अटल स्थिर चिन्हित अक्षर sine_data[] = अणु
	0,  39,  75,  103,  121,  127,  121,  103,  75,  39,
	0, -39, -75, -103, -121, -127, -121, -103, -75, -39
पूर्ण;

/*
 * where the ASC hides ...
 */
अटल अस्थिर __u8* mac_asc_regs = ( व्योम* )0x50F14000;

/*
 * sample rate; is this a good शेष value?
 */
अटल अचिन्हित दीर्घ mac_asc_samplespersec = 11050;
अटल पूर्णांक mac_bell_duration;
अटल अचिन्हित दीर्घ mac_bell_phase; /* 0..2*Pi -> 0..0x800 (wavetable size) */
अटल अचिन्हित दीर्घ mac_bell_phasepersample;

/*
 * some function protos
 */
अटल व्योम mac_init_asc( व्योम );
अटल व्योम mac_nosound(काष्ठा समयr_list *);
अटल व्योम mac_quadra_start_bell( अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक );
अटल व्योम mac_quadra_ring_bell(काष्ठा समयr_list *);
अटल व्योम mac_av_start_bell( अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक );
अटल व्योम ( *mac_special_bell )( अचिन्हित पूर्णांक, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक );

/*
 * our समयr to start/जारी/stop the bell
 */
अटल DEFINE_TIMER(mac_sound_समयr, mac_nosound);

/*
 * Sort of initialize the sound chip (called from mac_mksound on the first
 * beep).
 */
अटल व्योम mac_init_asc( व्योम )
अणु
	पूर्णांक i;

	/*
	 * करो some machine specअगरic initialization
	 * BTW:
	 * the NetBSD Quadra patch identअगरies the Enhanced Apple Sound Chip via
	 *	mac_asc_regs[ 0x800 ] & 0xF0 != 0
	 * this makes no sense here, because we have to set the शेष sample
	 * rate anyway अगर we want correct frequencies
	 */
	चयन ( macपूर्णांकosh_config->ident )
	अणु
		हाल MAC_MODEL_IIFX:
			/*
			 * The IIfx is always special ...
			 */
			mac_asc_regs = ( व्योम* )0x50010000;
			अवरोध;
			/*
			 * not sure about how correct this list is
			 * machines with the EASC enhanced apple sound chip
			 */
		हाल MAC_MODEL_Q630:
		हाल MAC_MODEL_P475:
			mac_special_bell = mac_quadra_start_bell;
			mac_asc_samplespersec = 22150;
			अवरोध;
		हाल MAC_MODEL_C660:
		हाल MAC_MODEL_Q840:
			/*
			 * The Quadra 660AV and 840AV use the "Singer" custom ASIC क्रम sound I/O.
			 * It appears to be similar to the "AWACS" custom ASIC in the Power Mac
			 * [678]100.  Because Singer and AWACS may have a similar hardware
			 * पूर्णांकerface, this would imply that the code in drivers/sound/dmasound.c
			 * क्रम AWACS could be used as a basis क्रम Singer support.  All we have to
			 * करो is figure out how to करो DMA on the 660AV/840AV through the PSC and
			 * figure out where the Singer hardware sits in memory. (I'd look in the
			 * vicinity of the AWACS location in a Power Mac [678]100 first, or the
			 * current location of the Apple Sound Chip--ASC--in other Macs.)  The
			 * Power Mac [678]100 info can be found in MkLinux Mach kernel sources.
			 *
			 * Quoted from Apple's Tech Info Library, article number 16405:
			 *   "Among desktop Macपूर्णांकosh computers, only the 660AV, 840AV, and Power
			 *   Macपूर्णांकosh models have 16-bit audio input and output capability
			 *   because of the AT&T DSP3210 hardware circuitry and the 16-bit Singer
			 *   codec circuitry in the AVs.  The Audio Waveक्रमm Amplअगरier and
			 *   Converter (AWAC) chip in the Power Macपूर्णांकosh perक्रमms the same
			 *   16-bit I/O functionality.  The PowerBook 500 series computers
			 *   support 16-bit stereo output, but only mono input."
			 *
			 *   Technical Inक्रमmation Library (TIL) article number 16405. 
			 *   https://support.apple.com/kb/TA32601
			 *
			 * --David Kilzer
			 */
			mac_special_bell = mac_av_start_bell;
			अवरोध;
		हाल MAC_MODEL_Q650:
		हाल MAC_MODEL_Q700:
		हाल MAC_MODEL_Q800:
		हाल MAC_MODEL_Q900:
		हाल MAC_MODEL_Q950:
			/*
			 * Currently not implemented!
			 */
			mac_special_bell = शून्य;
			अवरोध;
		शेष:
			/*
			 * Every चयन needs a शेष
			 */
			mac_special_bell = शून्य;
			अवरोध;
	पूर्ण

	/*
	 * init the wave table with a simple triangular wave
	 * A sine wave would sure be nicer here ...
	 */
	क्रम ( i = 0; i < 0x400; i++ )
	अणु
		mac_asc_wave_tab[ i ] = i / 4;
		mac_asc_wave_tab[ i + 0x400 ] = 0xFF - i / 4;
	पूर्ण
	mac_asc_inited = 1;
पूर्ण

/*
 * Called to make noise; current single entry to the boing driver.
 * Does the job क्रम simple ASC, calls other routines अन्यथा.
 * XXX Fixme:
 * Should be split पूर्णांकo asc_mksound, easc_mksound, av_mksound and
 * function poपूर्णांकer set in mac_init_asc which would be called at
 * init समय.
 * _This_ is rather ugly ...
 */
व्योम mac_mksound( अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक length )
अणु
	__u32 cfreq = ( freq << 5 ) / 468;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	अगर ( mac_special_bell == शून्य )
	अणु
		/* Do nothing */
		वापस;
	पूर्ण

	अगर ( !mac_asc_inited )
		mac_init_asc();

	अगर ( mac_special_bell )
	अणु
		mac_special_bell( freq, length, 128 );
		वापस;
	पूर्ण

	अगर ( freq < 20 || freq > 20000 || length == 0 )
	अणु
		mac_nosound( 0 );
		वापस;
	पूर्ण

	local_irq_save(flags);

	del_समयr( &mac_sound_समयr );

	क्रम ( i = 0; i < 0x800; i++ )
		mac_asc_regs[ i ] = 0;
	क्रम ( i = 0; i < 0x800; i++ )
		mac_asc_regs[ i ] = mac_asc_wave_tab[ i ];

	क्रम ( i = 0; i < 8; i++ )
		*( __u32* )( ( __u32 )mac_asc_regs + ASC_CONTROL + 0x814 + 8 * i ) = cfreq;

	mac_asc_regs[ 0x807 ] = 0;
	mac_asc_regs[ ASC_VOLUME ] = 128;
	mac_asc_regs[ 0x805 ] = 0;
	mac_asc_regs[ 0x80F ] = 0;
	mac_asc_regs[ ASC_MODE ] = ASC_MODE_SAMPLE;
	mac_asc_regs[ ASC_ENABLE ] = ASC_ENABLE_SAMPLE;

	mac_sound_समयr.expires = jअगरfies + length;
	add_समयr( &mac_sound_समयr );

	local_irq_restore(flags);
पूर्ण

/*
 * regular ASC: stop whining ..
 */
अटल व्योम mac_nosound(काष्ठा समयr_list *unused)
अणु
	mac_asc_regs[ ASC_ENABLE ] = 0;
पूर्ण

/*
 * EASC entry; init EASC, करोn't load wavetable, schedule 'start whining'.
 */
अटल व्योम mac_quadra_start_bell( अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक volume )
अणु
	अचिन्हित दीर्घ flags;

	/* अगर the bell is alपढ़ोy ringing, ring दीर्घer */
	अगर ( mac_bell_duration > 0 )
	अणु
		mac_bell_duration += length;
		वापस;
	पूर्ण

	mac_bell_duration = length;
	mac_bell_phase = 0;
	mac_bell_phasepersample = ( freq * माप( mac_asc_wave_tab ) ) / mac_asc_samplespersec;
	/* this is reasonably big क्रम small frequencies */

	local_irq_save(flags);

	/* set the volume */
	mac_asc_regs[ 0x806 ] = volume;

	/* set up the ASC रेजिस्टरs */
	अगर ( mac_asc_regs[ 0x801 ] != 1 )
	अणु
		/* select mono mode */
		mac_asc_regs[ 0x807 ] = 0;
		/* select sampled sound mode */
		mac_asc_regs[ 0x802 ] = 0;
		/* ??? */
		mac_asc_regs[ 0x801 ] = 1;
		mac_asc_regs[ 0x803 ] |= 0x80;
		mac_asc_regs[ 0x803 ] &= 0x7F;
	पूर्ण

	mac_sound_समयr.function = mac_quadra_ring_bell;
	mac_sound_समयr.expires = jअगरfies + 1;
	add_समयr( &mac_sound_समयr );

	local_irq_restore(flags);
पूर्ण

/*
 * EASC 'start/continue whining'; I'm not sure why the above function didn't
 * alपढ़ोy load the wave table, or at least call this one...
 * This piece keeps reloading the wave table until करोne.
 */
अटल व्योम mac_quadra_ring_bell(काष्ठा समयr_list *unused)
अणु
	पूर्णांक	i, count = mac_asc_samplespersec / HZ;
	अचिन्हित दीर्घ flags;

	/*
	 * we neither want a sound buffer overflow nor underflow, so we need to match
	 * the number of samples per समयr पूर्णांकerrupt as exactly as possible.
	 * using the asc पूर्णांकerrupt will give better results in the future
	 * ...and the possibility to use a real sample (a boingy noise, maybe...)
	 */

	local_irq_save(flags);

	del_समयr( &mac_sound_समयr );

	अगर ( mac_bell_duration-- > 0 )
	अणु
		क्रम ( i = 0; i < count; i++ )
		अणु
			mac_bell_phase += mac_bell_phasepersample;
			mac_asc_regs[ 0 ] = mac_asc_wave_tab[ mac_bell_phase & ( माप( mac_asc_wave_tab ) - 1 ) ];
		पूर्ण
		mac_sound_समयr.expires = jअगरfies + 1;
		add_समयr( &mac_sound_समयr );
	पूर्ण
	अन्यथा
		mac_asc_regs[ 0x801 ] = 0;

	local_irq_restore(flags);
पूर्ण

/*
 * AV code - please fill in.
 */
अटल व्योम mac_av_start_bell( अचिन्हित पूर्णांक freq, अचिन्हित पूर्णांक length, अचिन्हित पूर्णांक volume )
अणु
पूर्ण
