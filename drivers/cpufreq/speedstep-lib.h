<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * (C) 2002 - 2003 Dominik Broकरोwski <linux@broकरो.de>
 *
 *  Library क्रम common functions क्रम Intel SpeedStep v.1 and v.2 support
 *
 *  BIG FAT DISCLAIMER: Work in progress code. Possibly *dangerous*
 */



/* processors */
क्रमागत speedstep_processor अणु
	SPEEDSTEP_CPU_PIII_C_EARLY = 0x00000001,  /* Coppermine core */
	SPEEDSTEP_CPU_PIII_C	   = 0x00000002,  /* Coppermine core */
	SPEEDSTEP_CPU_PIII_T	   = 0x00000003,  /* Tualatin core */
	SPEEDSTEP_CPU_P4M	   = 0x00000004,  /* P4-M  */
/* the following processors are not speedstep-capable and are not स्वतः-detected
 * in speedstep_detect_processor(). However, their speed can be detected using
 * the speedstep_get_frequency() call. */
	SPEEDSTEP_CPU_PM	   = 0xFFFFFF03,  /* Pentium M  */
	SPEEDSTEP_CPU_P4D	   = 0xFFFFFF04,  /* desktop P4  */
	SPEEDSTEP_CPU_PCORE	   = 0xFFFFFF05,  /* Core */
पूर्ण;

/* speedstep states -- only two of them */

#घोषणा SPEEDSTEP_HIGH	0x00000000
#घोषणा SPEEDSTEP_LOW	0x00000001


/* detect a speedstep-capable processor */
बाह्य क्रमागत speedstep_processor speedstep_detect_processor(व्योम);

/* detect the current speed (in khz) of the processor */
बाह्य अचिन्हित पूर्णांक speedstep_get_frequency(क्रमागत speedstep_processor processor);


/* detect the low and high speeds of the processor. The callback
 * set_state"'s first argument is either SPEEDSTEP_HIGH or
 * SPEEDSTEP_LOW; the second argument is zero so that no
 * cpufreq_notअगरy_transition calls are initiated.
 */
बाह्य अचिन्हित पूर्णांक speedstep_get_freqs(क्रमागत speedstep_processor processor,
	अचिन्हित पूर्णांक *low_speed,
	अचिन्हित पूर्णांक *high_speed,
	अचिन्हित पूर्णांक *transition_latency,
	व्योम (*set_state) (अचिन्हित पूर्णांक state));
