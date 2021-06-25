<शैली गुरु>
/****************************************************************************

   Copyright Echo Digital Audio Corporation (c) 1998 - 2004
   All rights reserved
   www.echoaudio.com

   This file is part of Echo Digital Audio's generic driver library.

   Echo Digital Audio's generic driver library is मुक्त software;
   you can redistribute it and/or modअगरy it under the terms of
   the GNU General Public License as published by the Free Software
   Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA  02111-1307, USA.

   *************************************************************************

 Translation from C++ and adaptation क्रम use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

****************************************************************************/

#अगर_अघोषित _ECHO_DSP_
#घोषणा _ECHO_DSP_


/**** Echogals: Darla20, Gina20, Layla20, and Darla24 ****/
#अगर defined(ECHOGALS_FAMILY)

#घोषणा NUM_ASIC_TESTS		5
#घोषणा READ_DSP_TIMEOUT	1000000L	/* one second */

/**** Echo24: Gina24, Layla24, Mona, Mia, Mia-midi ****/
#या_अगर defined(ECHO24_FAMILY)

#घोषणा DSP_56361			/* Some Echo24 cards use the 56361 DSP */
#घोषणा READ_DSP_TIMEOUT	100000L		/* .1 second */

/**** 3G: Gina3G, Layla3G ****/
#या_अगर defined(ECHO3G_FAMILY)

#घोषणा DSP_56361
#घोषणा READ_DSP_TIMEOUT 	100000L		/* .1 second */
#घोषणा MIN_MTC_1X_RATE		32000

/**** Indigo: Indigo, Indigo IO, Indigo DJ ****/
#या_अगर defined(INDIGO_FAMILY)

#घोषणा DSP_56361
#घोषणा READ_DSP_TIMEOUT	100000L		/* .1 second */

#अन्यथा

#त्रुटि No family is defined

#पूर्ण_अगर



/*
 *
 *  Max inमाला_दो and outमाला_दो
 *
 */

#घोषणा DSP_MAXAUDIOINPUTS		16	/* Max audio input channels */
#घोषणा DSP_MAXAUDIOOUTPUTS		16	/* Max audio output channels */
#घोषणा DSP_MAXPIPES			32	/* Max total pipes (input + output) */


/*
 *
 * These are the offsets क्रम the memory-mapped DSP रेजिस्टरs; the DSP base
 * address is treated as the start of a u32 array.
 */

#घोषणा CHI32_CONTROL_REG		4
#घोषणा CHI32_STATUS_REG		5
#घोषणा CHI32_VECTOR_REG		6
#घोषणा CHI32_DATA_REG			7


/*
 *
 * Interesting bits within the DSP रेजिस्टरs
 *
 */

#घोषणा CHI32_VECTOR_BUSY		0x00000001
#घोषणा CHI32_STATUS_REG_HF3		0x00000008
#घोषणा CHI32_STATUS_REG_HF4		0x00000010
#घोषणा CHI32_STATUS_REG_HF5		0x00000020
#घोषणा CHI32_STATUS_HOST_READ_FULL	0x00000004
#घोषणा CHI32_STATUS_HOST_WRITE_EMPTY	0x00000002
#घोषणा CHI32_STATUS_IRQ		0x00000040


/* 
 *
 * DSP commands sent via slave mode; these are sent to the DSP by ग_लिखो_dsp()
 *
 */

#घोषणा DSP_FNC_SET_COMMPAGE_ADDR		0x02
#घोषणा DSP_FNC_LOAD_LAYLA_ASIC			0xa0
#घोषणा DSP_FNC_LOAD_GINA24_ASIC		0xa0
#घोषणा DSP_FNC_LOAD_MONA_PCI_CARD_ASIC		0xa0
#घोषणा DSP_FNC_LOAD_LAYLA24_PCI_CARD_ASIC	0xa0
#घोषणा DSP_FNC_LOAD_MONA_EXTERNAL_ASIC		0xa1
#घोषणा DSP_FNC_LOAD_LAYLA24_EXTERNAL_ASIC	0xa1
#घोषणा DSP_FNC_LOAD_3G_ASIC			0xa0


/*
 *
 * Defines to handle the MIDI input state engine; these are used to properly
 * extract MIDI समय code bytes and their बारtamps from the MIDI input stream.
 *
 */

#घोषणा MIDI_IN_STATE_NORMAL	0
#घोषणा MIDI_IN_STATE_TS_HIGH	1
#घोषणा MIDI_IN_STATE_TS_LOW	2
#घोषणा MIDI_IN_STATE_F1_DATA 	3
#घोषणा MIDI_IN_SKIP_DATA	(-1)


/*----------------------------------------------------------------------------

Setting the sample rates on Layla24 is somewhat schizophrenic.

For standard rates, it works exactly like Mona and Gina24.  That is, क्रम
8, 11.025, 16, 22.05, 32, 44.1, 48, 88.2, and 96 kHz, you just set the
appropriate bits in the control रेजिस्टर and ग_लिखो the control रेजिस्टर.

In order to support MIDI समय code sync (and possibly SMPTE LTC sync in
the future), Layla24 also has "continuous sample rate mode".  In this mode,
Layla24 can generate any sample rate between 25 and 50 kHz inclusive, or
50 to 100 kHz inclusive क्रम द्विगुन speed mode.

To use continuous mode:

-Set the घड़ी select bits in the control रेजिस्टर to 0xe (see the #घोषणा
 below)

-Set द्विगुन-speed mode अगर you want to use sample rates above 50 kHz

-Write the control रेजिस्टर as you would normally

-Now, you need to set the frequency रेजिस्टर. First, you need to determine the
 value क्रम the frequency रेजिस्टर.  This is given by the following क्रमmula:

frequency_reg = (LAYLA24_MAGIC_NUMBER / sample_rate) - 2

Note the #घोषणा below क्रम the magic number

-Wait क्रम the DSP handshake
-Write the frequency_reg value to the .SampleRate field of the comm page
-Send the vector command SET_LAYLA24_FREQUENCY_REG (see vmonkey.h)

Once you have set the control रेजिस्टर up क्रम continuous mode, you can just
ग_लिखो the frequency रेजिस्टर to change the sample rate.  This could be
used क्रम MIDI समय code sync. For MTC sync, the control रेजिस्टर is set क्रम
continuous mode.  The driver then just keeps writing the
SET_LAYLA24_FREQUENCY_REG command.

-----------------------------------------------------------------------------*/

#घोषणा LAYLA24_MAGIC_NUMBER			677376000
#घोषणा LAYLA24_CONTINUOUS_CLOCK		0x000e


/*
 *
 * DSP vector commands
 *
 */

#घोषणा DSP_VC_RESET				0x80ff

#अगर_अघोषित DSP_56361

#घोषणा DSP_VC_ACK_INT				0x8073
#घोषणा DSP_VC_SET_VMIXER_GAIN			0x0000	/* Not used, only क्रम compile */
#घोषणा DSP_VC_START_TRANSFER			0x0075	/* Handshke rqd. */
#घोषणा DSP_VC_METERS_ON			0x0079
#घोषणा DSP_VC_METERS_OFF			0x007b
#घोषणा DSP_VC_UPDATE_OUTVOL			0x007d	/* Handshke rqd. */
#घोषणा DSP_VC_UPDATE_INGAIN			0x007f	/* Handshke rqd. */
#घोषणा DSP_VC_ADD_AUDIO_BUFFER			0x0081	/* Handshke rqd. */
#घोषणा DSP_VC_TEST_ASIC			0x00eb
#घोषणा DSP_VC_UPDATE_CLOCKS			0x00ef	/* Handshke rqd. */
#घोषणा DSP_VC_SET_LAYLA_SAMPLE_RATE		0x00f1	/* Handshke rqd. */
#घोषणा DSP_VC_SET_GD_AUDIO_STATE		0x00f1	/* Handshke rqd. */
#घोषणा DSP_VC_WRITE_CONTROL_REG		0x00f1	/* Handshke rqd. */
#घोषणा DSP_VC_MIDI_WRITE			0x00f5	/* Handshke rqd. */
#घोषणा DSP_VC_STOP_TRANSFER			0x00f7	/* Handshke rqd. */
#घोषणा DSP_VC_UPDATE_FLAGS			0x00fd	/* Handshke rqd. */
#घोषणा DSP_VC_GO_COMATOSE			0x00f9

#अन्यथा /* !DSP_56361 */

/* Vector commands क्रम families that use either the 56301 or 56361 */
#घोषणा DSP_VC_ACK_INT				0x80F5
#घोषणा DSP_VC_SET_VMIXER_GAIN			0x00DB	/* Handshke rqd. */
#घोषणा DSP_VC_START_TRANSFER			0x00DD	/* Handshke rqd. */
#घोषणा DSP_VC_METERS_ON			0x00EF
#घोषणा DSP_VC_METERS_OFF			0x00F1
#घोषणा DSP_VC_UPDATE_OUTVOL			0x00E3	/* Handshke rqd. */
#घोषणा DSP_VC_UPDATE_INGAIN			0x00E5	/* Handshke rqd. */
#घोषणा DSP_VC_ADD_AUDIO_BUFFER			0x00E1	/* Handshke rqd. */
#घोषणा DSP_VC_TEST_ASIC			0x00ED
#घोषणा DSP_VC_UPDATE_CLOCKS			0x00E9	/* Handshke rqd. */
#घोषणा DSP_VC_SET_LAYLA24_FREQUENCY_REG	0x00E9	/* Handshke rqd. */
#घोषणा DSP_VC_SET_LAYLA_SAMPLE_RATE		0x00EB	/* Handshke rqd. */
#घोषणा DSP_VC_SET_GD_AUDIO_STATE		0x00EB	/* Handshke rqd. */
#घोषणा DSP_VC_WRITE_CONTROL_REG		0x00EB	/* Handshke rqd. */
#घोषणा DSP_VC_MIDI_WRITE			0x00E7	/* Handshke rqd. */
#घोषणा DSP_VC_STOP_TRANSFER			0x00DF	/* Handshke rqd. */
#घोषणा DSP_VC_UPDATE_FLAGS			0x00FB	/* Handshke rqd. */
#घोषणा DSP_VC_GO_COMATOSE			0x00d9

#पूर्ण_अगर /* !DSP_56361 */


/*
 *
 * Timeouts
 *
 */

#घोषणा HANDSHAKE_TIMEOUT		20000	/* send_vector command समयout (20ms) */
#घोषणा VECTOR_BUSY_TIMEOUT		100000	/* 100ms */
#घोषणा MIDI_OUT_DELAY_USEC		2000	/* How दीर्घ to रुको after MIDI fills up */


/*
 *
 * Flags क्रम .Flags field in the comm page
 *
 */

#घोषणा DSP_FLAG_MIDI_INPUT		0x0001	/* Enable MIDI input */
#घोषणा DSP_FLAG_SPDIF_NONAUDIO		0x0002	/* Sets the "non-audio" bit
						 * in the S/PDIF out status
						 * bits.  Clear this flag क्रम
						 * audio data;
						 * set it क्रम AC3 or WMA or
						 * some such */
#घोषणा DSP_FLAG_PROFESSIONAL_SPDIF	0x0008	/* 1 Professional, 0 Consumer */


/*
 *
 * Clock detect bits reported by the DSP क्रम Gina20, Layla20, Darla24, and Mia
 *
 */

#घोषणा GLDM_CLOCK_DETECT_BIT_WORD	0x0002
#घोषणा GLDM_CLOCK_DETECT_BIT_SUPER	0x0004
#घोषणा GLDM_CLOCK_DETECT_BIT_SPDIF	0x0008
#घोषणा GLDM_CLOCK_DETECT_BIT_ESYNC	0x0010


/*
 *
 * Clock detect bits reported by the DSP क्रम Gina24, Mona, and Layla24
 *
 */

#घोषणा GML_CLOCK_DETECT_BIT_WORD96	0x0002
#घोषणा GML_CLOCK_DETECT_BIT_WORD48	0x0004
#घोषणा GML_CLOCK_DETECT_BIT_SPDIF48	0x0008
#घोषणा GML_CLOCK_DETECT_BIT_SPDIF96	0x0010
#घोषणा GML_CLOCK_DETECT_BIT_WORD	(GML_CLOCK_DETECT_BIT_WORD96 | GML_CLOCK_DETECT_BIT_WORD48)
#घोषणा GML_CLOCK_DETECT_BIT_SPDIF	(GML_CLOCK_DETECT_BIT_SPDIF48 | GML_CLOCK_DETECT_BIT_SPDIF96)
#घोषणा GML_CLOCK_DETECT_BIT_ESYNC	0x0020
#घोषणा GML_CLOCK_DETECT_BIT_ADAT	0x0040


/*
 *
 * Layla घड़ी numbers to send to DSP
 *
 */

#घोषणा LAYLA20_CLOCK_INTERNAL		0
#घोषणा LAYLA20_CLOCK_SPDIF		1
#घोषणा LAYLA20_CLOCK_WORD		2
#घोषणा LAYLA20_CLOCK_SUPER		3


/*
 *
 * Gina/Darla घड़ी states
 *
 */

#घोषणा GD_CLOCK_NOCHANGE		0
#घोषणा GD_CLOCK_44			1
#घोषणा GD_CLOCK_48			2
#घोषणा GD_CLOCK_SPDIFIN		3
#घोषणा GD_CLOCK_UNDEF			0xff


/*
 *
 * Gina/Darla S/PDIF status bits
 *
 */

#घोषणा GD_SPDIF_STATUS_NOCHANGE	0
#घोषणा GD_SPDIF_STATUS_44		1
#घोषणा GD_SPDIF_STATUS_48		2
#घोषणा GD_SPDIF_STATUS_UNDEF		0xff


/*
 *
 * Layla20 output घड़ीs
 *
 */

#घोषणा LAYLA20_OUTPUT_CLOCK_SUPER	0
#घोषणा LAYLA20_OUTPUT_CLOCK_WORD	1


/****************************************************************************

   Magic स्थिरants क्रम the Darla24 hardware

 ****************************************************************************/

#घोषणा GD24_96000	0x0
#घोषणा GD24_48000	0x1
#घोषणा GD24_44100	0x2
#घोषणा GD24_32000	0x3
#घोषणा GD24_22050	0x4
#घोषणा GD24_16000	0x5
#घोषणा GD24_11025	0x6
#घोषणा GD24_8000	0x7
#घोषणा GD24_88200	0x8
#घोषणा GD24_EXT_SYNC	0x9


/*
 *
 * Return values from the DSP when ASIC is loaded
 *
 */

#घोषणा ASIC_ALREADY_LOADED	0x1
#घोषणा ASIC_NOT_LOADED		0x0


/*
 *
 * DSP Audio क्रमmats
 *
 * These are the audio क्रमmats that the DSP can transfer
 * via input and output pipes.  LE means little-endian,
 * BE means big-endian.
 *
 * DSP_AUDIOFORM_MS_8   
 *
 *    8-bit mono अचिन्हित samples.  For playback,
 *    mono data is duplicated out the left and right channels
 *    of the output bus.  The "MS" part of the name
 *    means mono->stereo.
 *
 * DSP_AUDIOFORM_MS_16LE
 *
 *    16-bit चिन्हित little-endian mono samples.  Playback works
 *    like the previous code.
 *
 * DSP_AUDIOFORM_MS_24LE
 *
 *    24-bit चिन्हित little-endian mono samples.  Data is packed
 *    three bytes per sample; अगर you had two samples 0x112233 and 0x445566
 *    they would be stored in memory like this: 33 22 11 66 55 44.
 *
 * DSP_AUDIOFORM_MS_32LE
 * 
 *    24-bit चिन्हित little-endian mono samples in a 32-bit 
 *    container.  In other words, each sample is a 32-bit चिन्हित 
 *    पूर्णांकeger, where the actual audio data is left-justअगरied 
 *    in the 32 bits and only the 24 most signअगरicant bits are valid.
 *
 * DSP_AUDIOFORM_SS_8
 * DSP_AUDIOFORM_SS_16LE
 * DSP_AUDIOFORM_SS_24LE
 * DSP_AUDIOFORM_SS_32LE
 *
 *    Like the previous ones, except now with stereo पूर्णांकerleaved
 *    data.  "SS" means stereo->stereo.
 *
 * DSP_AUDIOFORM_MM_32LE
 *
 *    Similar to DSP_AUDIOFORM_MS_32LE, except that the mono
 *    data is not duplicated out both the left and right outमाला_दो.
 *    This mode is used by the ASIO driver.  Here, "MM" means
 *    mono->mono.
 *
 * DSP_AUDIOFORM_MM_32BE
 *
 *    Just like DSP_AUDIOFORM_MM_32LE, but now the data is
 *    in big-endian क्रमmat.
 *
 */

#घोषणा DSP_AUDIOFORM_MS_8	0	/* 8 bit mono */
#घोषणा DSP_AUDIOFORM_MS_16LE	1	/* 16 bit mono */
#घोषणा DSP_AUDIOFORM_MS_24LE	2	/* 24 bit mono */
#घोषणा DSP_AUDIOFORM_MS_32LE	3	/* 32 bit mono */
#घोषणा DSP_AUDIOFORM_SS_8	4	/* 8 bit stereo */
#घोषणा DSP_AUDIOFORM_SS_16LE	5	/* 16 bit stereo */
#घोषणा DSP_AUDIOFORM_SS_24LE	6	/* 24 bit stereo */
#घोषणा DSP_AUDIOFORM_SS_32LE	7	/* 32 bit stereo */
#घोषणा DSP_AUDIOFORM_MM_32LE	8	/* 32 bit mono->mono little-endian */
#घोषणा DSP_AUDIOFORM_MM_32BE	9	/* 32 bit mono->mono big-endian */
#घोषणा DSP_AUDIOFORM_SS_32BE	10	/* 32 bit stereo big endian */
#घोषणा DSP_AUDIOFORM_INVALID	0xFF	/* Invalid audio क्रमmat */


/*
 *
 * Super-पूर्णांकerleave is defined as पूर्णांकerleaving by 4 or more.  Darla20 and Gina20
 * करो not support super पूर्णांकerleave.
 *
 * 16 bit, 24 bit, and 32 bit little endian samples are supported क्रम super 
 * पूर्णांकerleave.  The पूर्णांकerleave factor must be even.  16 - way पूर्णांकerleave is the 
 * current maximum, so you can पूर्णांकerleave by 4, 6, 8, 10, 12, 14, and 16.
 *
 * The actual क्रमmat code is derived by taking the define below and or-ing with
 * the पूर्णांकerleave factor.  So, 32 bit पूर्णांकerleave by 6 is 0x86 and
 * 16 bit पूर्णांकerleave by 16 is (0x40 | 0x10) = 0x50.
 *
 */

#घोषणा DSP_AUDIOFORM_SUPER_INTERLEAVE_16LE	0x40
#घोषणा DSP_AUDIOFORM_SUPER_INTERLEAVE_24LE	0xc0
#घोषणा DSP_AUDIOFORM_SUPER_INTERLEAVE_32LE	0x80


/*
 *
 * Gina24, Mona, and Layla24 control रेजिस्टर defines
 *
 */

#घोषणा GML_CONVERTER_ENABLE	0x0010
#घोषणा GML_SPDIF_PRO_MODE	0x0020	/* Professional S/PDIF == 1,
					   consumer == 0 */
#घोषणा GML_SPDIF_SAMPLE_RATE0	0x0040
#घोषणा GML_SPDIF_SAMPLE_RATE1	0x0080
#घोषणा GML_SPDIF_TWO_CHANNEL	0x0100	/* 1 == two channels,
					   0 == one channel */
#घोषणा GML_SPDIF_NOT_AUDIO	0x0200
#घोषणा GML_SPDIF_COPY_PERMIT	0x0400
#घोषणा GML_SPDIF_24_BIT	0x0800	/* 1 == 24 bit, 0 == 20 bit */
#घोषणा GML_ADAT_MODE		0x1000	/* 1 == ADAT mode, 0 == S/PDIF mode */
#घोषणा GML_SPDIF_OPTICAL_MODE	0x2000	/* 1 == optical mode, 0 == RCA mode */
#घोषणा GML_SPDIF_CDROM_MODE	0x3000	/* 1 == CDROM mode,
					 * 0 == RCA or optical mode */
#घोषणा GML_DOUBLE_SPEED_MODE	0x4000	/* 1 == द्विगुन speed,
					   0 == single speed */

#घोषणा GML_DIGITAL_IN_AUTO_MUTE 0x800000

#घोषणा GML_96KHZ		(0x0 | GML_DOUBLE_SPEED_MODE)
#घोषणा GML_88KHZ		(0x1 | GML_DOUBLE_SPEED_MODE)
#घोषणा GML_48KHZ		0x2
#घोषणा GML_44KHZ		0x3
#घोषणा GML_32KHZ		0x4
#घोषणा GML_22KHZ		0x5
#घोषणा GML_16KHZ		0x6
#घोषणा GML_11KHZ		0x7
#घोषणा GML_8KHZ		0x8
#घोषणा GML_SPDIF_CLOCK		0x9
#घोषणा GML_ADAT_CLOCK		0xA
#घोषणा GML_WORD_CLOCK		0xB
#घोषणा GML_ESYNC_CLOCK		0xC
#घोषणा GML_ESYNCx2_CLOCK	0xD

#घोषणा GML_CLOCK_CLEAR_MASK		0xffffbff0
#घोषणा GML_SPDIF_RATE_CLEAR_MASK	(~(GML_SPDIF_SAMPLE_RATE0|GML_SPDIF_SAMPLE_RATE1))
#घोषणा GML_DIGITAL_MODE_CLEAR_MASK	0xffffcfff
#घोषणा GML_SPDIF_FORMAT_CLEAR_MASK	0xfffff01f


/*
 *
 * Mia sample rate and घड़ी setting स्थिरants
 *
 */

#घोषणा MIA_32000	0x0040
#घोषणा MIA_44100	0x0042
#घोषणा MIA_48000	0x0041
#घोषणा MIA_88200	0x0142
#घोषणा MIA_96000	0x0141

#घोषणा MIA_SPDIF	0x00000044
#घोषणा MIA_SPDIF96	0x00000144

#घोषणा MIA_MIDI_REV	1	/* Must be Mia rev 1 क्रम MIDI support */


/*
 *
 * 3G रेजिस्टर bits
 *
 */

#घोषणा E3G_CONVERTER_ENABLE	0x0010
#घोषणा E3G_SPDIF_PRO_MODE	0x0020	/* Professional S/PDIF == 1,
					   consumer == 0 */
#घोषणा E3G_SPDIF_SAMPLE_RATE0	0x0040
#घोषणा E3G_SPDIF_SAMPLE_RATE1	0x0080
#घोषणा E3G_SPDIF_TWO_CHANNEL	0x0100	/* 1 == two channels,
					   0 == one channel */
#घोषणा E3G_SPDIF_NOT_AUDIO	0x0200
#घोषणा E3G_SPDIF_COPY_PERMIT	0x0400
#घोषणा E3G_SPDIF_24_BIT	0x0800	/* 1 == 24 bit, 0 == 20 bit */
#घोषणा E3G_DOUBLE_SPEED_MODE	0x4000	/* 1 == द्विगुन speed,
					   0 == single speed */
#घोषणा E3G_PHANTOM_POWER	0x8000	/* 1 == phantom घातer on,
					   0 == phantom घातer off */

#घोषणा E3G_96KHZ		(0x0 | E3G_DOUBLE_SPEED_MODE)
#घोषणा E3G_88KHZ		(0x1 | E3G_DOUBLE_SPEED_MODE)
#घोषणा E3G_48KHZ		0x2
#घोषणा E3G_44KHZ		0x3
#घोषणा E3G_32KHZ		0x4
#घोषणा E3G_22KHZ		0x5
#घोषणा E3G_16KHZ		0x6
#घोषणा E3G_11KHZ		0x7
#घोषणा E3G_8KHZ		0x8
#घोषणा E3G_SPDIF_CLOCK		0x9
#घोषणा E3G_ADAT_CLOCK		0xA
#घोषणा E3G_WORD_CLOCK		0xB
#घोषणा E3G_CONTINUOUS_CLOCK	0xE

#घोषणा E3G_ADAT_MODE		0x1000
#घोषणा E3G_SPDIF_OPTICAL_MODE	0x2000

#घोषणा E3G_CLOCK_CLEAR_MASK		0xbfffbff0
#घोषणा E3G_DIGITAL_MODE_CLEAR_MASK	0xffffcfff
#घोषणा E3G_SPDIF_FORMAT_CLEAR_MASK	0xfffff01f

/* Clock detect bits reported by the DSP */
#घोषणा E3G_CLOCK_DETECT_BIT_WORD96	0x0001
#घोषणा E3G_CLOCK_DETECT_BIT_WORD48	0x0002
#घोषणा E3G_CLOCK_DETECT_BIT_SPDIF48	0x0004
#घोषणा E3G_CLOCK_DETECT_BIT_ADAT	0x0004
#घोषणा E3G_CLOCK_DETECT_BIT_SPDIF96	0x0008
#घोषणा E3G_CLOCK_DETECT_BIT_WORD	(E3G_CLOCK_DETECT_BIT_WORD96|E3G_CLOCK_DETECT_BIT_WORD48)
#घोषणा E3G_CLOCK_DETECT_BIT_SPDIF	(E3G_CLOCK_DETECT_BIT_SPDIF48|E3G_CLOCK_DETECT_BIT_SPDIF96)

/* Frequency control रेजिस्टर */
#घोषणा E3G_MAGIC_NUMBER		677376000
#घोषणा E3G_FREQ_REG_DEFAULT		(E3G_MAGIC_NUMBER / 48000 - 2)
#घोषणा E3G_FREQ_REG_MAX		0xffff

/* 3G बाह्यal box types */
#घोषणा E3G_GINA3G_BOX_TYPE		0x00
#घोषणा E3G_LAYLA3G_BOX_TYPE		0x10
#घोषणा E3G_ASIC_NOT_LOADED		0xffff
#घोषणा E3G_BOX_TYPE_MASK		0xf0

/* Indigo express control रेजिस्टर values */
#घोषणा INDIGO_EXPRESS_32000		0x02
#घोषणा INDIGO_EXPRESS_44100		0x01
#घोषणा INDIGO_EXPRESS_48000		0x00
#घोषणा INDIGO_EXPRESS_DOUBLE_SPEED	0x10
#घोषणा INDIGO_EXPRESS_QUAD_SPEED	0x04
#घोषणा INDIGO_EXPRESS_CLOCK_MASK	0x17


/*
 *
 * Gina20 & Layla20 have input gain controls क्रम the analog inमाला_दो;
 * this is the magic number क्रम the hardware that gives you 0 dB at -10.
 *
 */

#घोषणा GL20_INPUT_GAIN_MAGIC_NUMBER	0xC8


/*
 *
 * Defines how much समय must pass between DSP load attempts
 *
 */

#घोषणा DSP_LOAD_ATTEMPT_PERIOD		1000000L	/* One second */


/*
 *
 * Size of arrays क्रम the comm page.  MAX_PLAY_TAPS and MAX_REC_TAPS are
 * no दीर्घer used, but the sizes must still be right क्रम the DSP to see
 * the comm page correctly.
 *
 */

#घोषणा MONITOR_ARRAY_SIZE	0x180
#घोषणा VMIXER_ARRAY_SIZE	0x40
#घोषणा MIDI_OUT_BUFFER_SIZE	32
#घोषणा MIDI_IN_BUFFER_SIZE	256
#घोषणा MAX_PLAY_TAPS		168
#घोषणा MAX_REC_TAPS		192
#घोषणा DSP_MIDI_OUT_FIFO_SIZE	64


/* sg_entry is a single entry क्रम the scatter-gather list.  The array of काष्ठा
sg_entry काष्ठा is पढ़ो by the DSP, so all values must be little-endian. */

#घोषणा MAX_SGLIST_ENTRIES 512

काष्ठा sg_entry अणु
	__le32 addr;
	__le32 size;
पूर्ण;


/****************************************************************************

  The comm page.  This काष्ठाure is पढ़ो and written by the DSP; the
  DSP code is a firm believer in the byte offsets written in the comments
  at the end of each line.  This काष्ठाure should not be changed.

  Any पढ़ोs from or ग_लिखोs to this काष्ठाure should be in little-endian क्रमmat.

 ****************************************************************************/

काष्ठा comm_page अणु		/*				Base	Length*/
	__le32 comm_size;	/* size of this object		0x000	4 */
	__le32 flags;		/* See Appendix A below		0x004	4 */
	__le32 unused;		/* Unused entry			0x008	4 */
	__le32 sample_rate;	/* Card sample rate in Hz	0x00c	4 */
	__le32 handshake;	/* DSP command handshake	0x010	4 */
	__le32 cmd_start;	/* Chs. to start mask		0x014	4 */
	__le32 cmd_stop;	/* Chs. to stop mask		0x018	4 */
	__le32 cmd_reset;	/* Chs. to reset mask		0x01c	4 */
	__le16 audio_क्रमmat[DSP_MAXPIPES];	/* Chs. audio क्रमmat	0x020	32*2 */
	काष्ठा sg_entry sglist_addr[DSP_MAXPIPES];
				/* Chs. Physical sglist addrs	0x060	32*8 */
	__le32 position[DSP_MAXPIPES];
				/* Positions क्रम ea. ch.	0x160	32*4 */
	s8 vu_meter[DSP_MAXPIPES];
				/* VU meters			0x1e0	32*1 */
	s8 peak_meter[DSP_MAXPIPES];
				/* Peak meters			0x200	32*1 */
	s8 line_out_level[DSP_MAXAUDIOOUTPUTS];
				/* Output gain			0x220	16*1 */
	s8 line_in_level[DSP_MAXAUDIOINPUTS];
				/* Input gain			0x230	16*1 */
	s8 monitors[MONITOR_ARRAY_SIZE];
				/* Monitor map			0x240	0x180 */
	__le32 play_coeff[MAX_PLAY_TAPS];
			/* Gina/Darla play filters - obsolete	0x3c0	168*4 */
	__le32 rec_coeff[MAX_REC_TAPS];
			/* Gina/Darla record filters - obsolete	0x660	192*4 */
	__le16 midi_input[MIDI_IN_BUFFER_SIZE];
			/* MIDI input data transfer buffer	0x960	256*2 */
	u8 gd_घड़ी_state;	/* Chg Gina/Darla घड़ी state	0xb60	1 */
	u8 gd_spdअगर_status;	/* Chg. Gina/Darla S/PDIF state	0xb61	1 */
	u8 gd_resampler_state;	/* Should always be 3		0xb62	1 */
	u8 filler2;		/*				0xb63	1 */
	__le32 nominal_level_mask;	/* -10 level enable mask	0xb64	4 */
	__le16 input_घड़ी;	/* Chg. Input घड़ी state	0xb68	2 */
	__le16 output_घड़ी;	/* Chg. Output घड़ी state	0xb6a	2 */
	__le32 status_घड़ीs;	/* Current Input घड़ी state	0xb6c	4 */
	__le32 ext_box_status;	/* External box status		0xb70	4 */
	__le32 cmd_add_buffer;	/* Pipes to add (obsolete)	0xb74	4 */
	__le32 midi_out_मुक्त_count;
			/* # of bytes मुक्त in MIDI output FIFO	0xb78	4 */
	__le32 unused2;		/* Cyclic pipes			0xb7c	4 */
	__le32 control_रेजिस्टर;
			/* Mona, Gina24, Layla24, 3G ctrl reg	0xb80	4 */
	__le32 e3g_frq_रेजिस्टर;	/* 3G frequency रेजिस्टर	0xb84	4 */
	u8 filler[24];		/* filler			0xb88	24*1 */
	s8 vmixer[VMIXER_ARRAY_SIZE];
				/* Vmixer levels		0xba0	64*1 */
	u8 midi_output[MIDI_OUT_BUFFER_SIZE];
				/* MIDI output data		0xbe0	32*1 */
पूर्ण;

#पूर्ण_अगर /* _ECHO_DSP_ */
