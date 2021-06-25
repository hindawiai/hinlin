<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_SOUND_H
#घोषणा _UAPI_LINUX_SOUND_H

/*
 * Minor numbers क्रम the sound driver.
 */

#समावेश <linux/fs.h>

#घोषणा SND_DEV_CTL		0	/* Control port /dev/mixer */
#घोषणा SND_DEV_SEQ		1	/* Sequencer output /dev/sequencer (FM
						synthesizer and MIDI output) */
#घोषणा SND_DEV_MIDIN		2	/* Raw midi access */
#घोषणा SND_DEV_DSP		3	/* Digitized voice /dev/dsp */
#घोषणा SND_DEV_AUDIO		4	/* Sparc compatible /dev/audio */
#घोषणा SND_DEV_DSP16		5	/* Like /dev/dsp but 16 bits/sample */
/* #घोषणा SND_DEV_STATUS	6 */	/* /dev/sndstat (obsolete) */
#घोषणा SND_DEV_UNUSED		6
#घोषणा SND_DEV_AWFM		7	/* Reserved */
#घोषणा SND_DEV_SEQ2		8	/* /dev/sequencer, level 2 पूर्णांकerface */
/* #घोषणा SND_DEV_SNDPROC	9 */	/* /dev/sndproc क्रम programmable devices (not used) */
/* #घोषणा SND_DEV_DMMIDI	9 */
#घोषणा SND_DEV_SYNTH		9	/* Raw synth access /dev/synth (same as /dev/dmfm) */
#घोषणा SND_DEV_DMFM		10	/* Raw synth access /dev/dmfm */
#घोषणा SND_DEV_UNKNOWN11	11
#घोषणा SND_DEV_ADSP		12	/* Like /dev/dsp (obsolete) */
#घोषणा SND_DEV_AMIDI		13	/* Like /dev/midi (obsolete) */
#घोषणा SND_DEV_ADMMIDI		14	/* Like /dev/dmmidi (onsolete) */


#पूर्ण_अगर /* _UAPI_LINUX_SOUND_H */
