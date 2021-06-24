<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) 2004 James Courtier-Dutton <James@superbug.demon.co.uk>
 *  Driver CA0106 chips. e.g. Sound Blaster Audigy LS and Live 24bit
 *  Version: 0.0.22
 *
 *  FEATURES currently supported:
 *    See ca0106_मुख्य.c क्रम features.
 * 
 *  Changelog:
 *    Support पूर्णांकerrupts per period.
 *    Removed noise from Center/LFE channel when in Analog mode.
 *    Rename and हटाओ mixer controls.
 *  0.0.6
 *    Use separate card based DMA buffer क्रम periods table list.
 *  0.0.7
 *    Change हटाओ and नाम ctrls पूर्णांकo lists.
 *  0.0.8
 *    Try to fix capture sources.
 *  0.0.9
 *    Fix AC3 output.
 *    Enable S32_LE क्रमmat support.
 *  0.0.10
 *    Enable playback 48000 and 96000 rates. (Rates other that these करो not work, even with "plug:front".)
 *  0.0.11
 *    Add Model name recognition.
 *  0.0.12
 *    Correct पूर्णांकerrupt timing. पूर्णांकerrupt at end of period, instead of in the middle of a playback period.
 *    Remove redundent "voice" handling.
 *  0.0.13
 *    Single trigger call क्रम multi channels.
 *  0.0.14
 *    Set limits based on what the sound card hardware can करो.
 *    playback periods_min=2, periods_max=8
 *    capture hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *    playback hw स्थिरraपूर्णांकs require period_size = n * 64 bytes.
 *  0.0.15
 *    Separated ca0106.c पूर्णांकo separate functional .c files.
 *  0.0.16
 *    Implement 192000 sample rate.
 *  0.0.17
 *    Add support क्रम SB0410 and SB0413.
 *  0.0.18
 *    Modअगरied Copyright message.
 *  0.0.19
 *    Added I2C and SPI रेजिस्टरs. Filled in पूर्णांकerrupt enable.
 *  0.0.20
 *    Added GPIO info क्रम SB Live 24bit.
 *  0.0.21
 *   Implement support क्रम Line-in capture on SB Live 24bit.
 *  0.0.22
 *    Add support क्रम mute control on SB Live 24bit (cards w/ SPI DAC)
 *
 *  This code was initially based on code from ALSA's emu10k1x.c which is:
 *  Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 */

/************************************************************************************************/
/* PCI function 0 रेजिस्टरs, address = <val> + PCIBASE0						*/
/************************************************************************************************/

#घोषणा PTR			0x00		/* Indexed रेजिस्टर set poपूर्णांकer रेजिस्टर	*/
						/* NOTE: The CHANNELNUM and ADDRESS words can	*/
						/* be modअगरied independently of each other.	*/
						/* CNL[1:0], ADDR[27:16]                        */

#घोषणा DATA			0x04		/* Indexed रेजिस्टर set data रेजिस्टर		*/
						/* DATA[31:0]					*/

#घोषणा IPR			0x08		/* Global पूर्णांकerrupt pending रेजिस्टर		*/
						/* Clear pending पूर्णांकerrupts by writing a 1 to	*/
						/* the relevant bits and zero to the other bits	*/
#घोषणा IPR_MIDI_RX_B		0x00020000	/* MIDI UART-B Receive buffer non-empty		*/
#घोषणा IPR_MIDI_TX_B		0x00010000	/* MIDI UART-B Transmit buffer empty		*/
#घोषणा IPR_SPDIF_IN_USER	0x00004000      /* SPDIF input user data has 16 more bits	*/
#घोषणा IPR_SPDIF_OUT_USER	0x00002000      /* SPDIF output user data needs 16 more bits	*/
#घोषणा IPR_SPDIF_OUT_FRAME	0x00001000      /* SPDIF frame about to start			*/
#घोषणा IPR_SPI			0x00000800      /* SPI transaction completed			*/
#घोषणा IPR_I2C_EEPROM		0x00000400      /* I2C EEPROM transaction completed		*/
#घोषणा IPR_I2C_DAC		0x00000200      /* I2C DAC transaction completed		*/
#घोषणा IPR_AI			0x00000100      /* Audio pending रेजिस्टर changed. See PTR reg 0x76	*/
#घोषणा IPR_GPI			0x00000080      /* General Purpose input changed		*/
#घोषणा IPR_SRC_LOCKED          0x00000040      /* SRC lock status changed			*/
#घोषणा IPR_SPDIF_STATUS        0x00000020      /* SPDIF status changed				*/
#घोषणा IPR_TIMER2              0x00000010      /* 192000Hz Timer				*/
#घोषणा IPR_TIMER1              0x00000008      /* 44100Hz Timer				*/
#घोषणा IPR_MIDI_RX_A		0x00000004	/* MIDI UART-A Receive buffer non-empty		*/
#घोषणा IPR_MIDI_TX_A		0x00000002	/* MIDI UART-A Transmit buffer empty		*/
#घोषणा IPR_PCI			0x00000001	/* PCI Bus error				*/

#घोषणा INTE			0x0c		/* Interrupt enable रेजिस्टर			*/

#घोषणा INTE_MIDI_RX_B		0x00020000	/* MIDI UART-B Receive buffer non-empty		*/
#घोषणा INTE_MIDI_TX_B		0x00010000	/* MIDI UART-B Transmit buffer empty		*/
#घोषणा INTE_SPDIF_IN_USER	0x00004000      /* SPDIF input user data has 16 more bits	*/
#घोषणा INTE_SPDIF_OUT_USER	0x00002000      /* SPDIF output user data needs 16 more bits	*/
#घोषणा INTE_SPDIF_OUT_FRAME	0x00001000      /* SPDIF frame about to start			*/
#घोषणा INTE_SPI		0x00000800      /* SPI transaction completed			*/
#घोषणा INTE_I2C_EEPROM		0x00000400      /* I2C EEPROM transaction completed		*/
#घोषणा INTE_I2C_DAC		0x00000200      /* I2C DAC transaction completed		*/
#घोषणा INTE_AI			0x00000100      /* Audio pending रेजिस्टर changed. See PTR reg 0x75 */
#घोषणा INTE_GPI		0x00000080      /* General Purpose input changed		*/
#घोषणा INTE_SRC_LOCKED         0x00000040      /* SRC lock status changed			*/
#घोषणा INTE_SPDIF_STATUS       0x00000020      /* SPDIF status changed				*/
#घोषणा INTE_TIMER2             0x00000010      /* 192000Hz Timer				*/
#घोषणा INTE_TIMER1             0x00000008      /* 44100Hz Timer				*/
#घोषणा INTE_MIDI_RX_A		0x00000004	/* MIDI UART-A Receive buffer non-empty		*/
#घोषणा INTE_MIDI_TX_A		0x00000002	/* MIDI UART-A Transmit buffer empty		*/
#घोषणा INTE_PCI		0x00000001	/* PCI Bus error				*/

#घोषणा UNKNOWN10		0x10		/* Unknown ??. Defaults to 0 */
#घोषणा HCFG			0x14		/* Hardware config रेजिस्टर			*/
						/* 0x1000 causes AC3 to fails. It adds a dither bit. */

#घोषणा HCFG_STAC		0x10000000	/* Special mode क्रम STAC9460 Codec. */
#घोषणा HCFG_CAPTURE_I2S_BYPASS	0x08000000	/* 1 = bypass I2S input async SRC. */
#घोषणा HCFG_CAPTURE_SPDIF_BYPASS 0x04000000	/* 1 = bypass SPDIF input async SRC. */
#घोषणा HCFG_PLAYBACK_I2S_BYPASS 0x02000000	/* 0 = I2S IN mixer output, 1 = I2S IN1. */
#घोषणा HCFG_FORCE_LOCK		0x01000000	/* For test only. Force input SRC tracker to lock. */
#घोषणा HCFG_PLAYBACK_ATTENUATION 0x00006000	/* Playback attenuation mask. 0 = 0dB, 1 = 6dB, 2 = 12dB, 3 = Mute. */
#घोषणा HCFG_PLAYBACK_DITHER	0x00001000	/* 1 = Add dither bit to all playback channels. */
#घोषणा HCFG_PLAYBACK_S32_LE	0x00000800	/* 1 = S32_LE, 0 = S16_LE                       */
#घोषणा HCFG_CAPTURE_S32_LE	0x00000400	/* 1 = S32_LE, 0 = S16_LE (S32_LE current not working)	*/
#घोषणा HCFG_8_CHANNEL_PLAY	0x00000200	/* 1 = 8 channels, 0 = 2 channels per substream.*/
#घोषणा HCFG_8_CHANNEL_CAPTURE	0x00000100	/* 1 = 8 channels, 0 = 2 channels per substream.*/
#घोषणा HCFG_MONO		0x00000080	/* 1 = I2S Input mono                           */
#घोषणा HCFG_I2S_OUTPUT		0x00000010	/* 1 = I2S Output disabled                      */
#घोषणा HCFG_AC97		0x00000008	/* 0 = AC97 1.0, 1 = AC97 2.0                   */
#घोषणा HCFG_LOCK_PLAYBACK_CACHE 0x00000004	/* 1 = Cancel busपंचांगaster accesses to soundcache */
						/* NOTE: This should generally never be used.  	*/
#घोषणा HCFG_LOCK_CAPTURE_CACHE	0x00000002	/* 1 = Cancel busपंचांगaster accesses to soundcache */
						/* NOTE: This should generally never be used.  	*/
#घोषणा HCFG_AUDIOENABLE	0x00000001	/* 0 = CODECs transmit zero-valued samples	*/
						/* Should be set to 1 when the EMU10K1 is	*/
						/* completely initialized.			*/
#घोषणा GPIO			0x18		/* Defaults: 005f03a3-Analog, 005f02a2-SPDIF.   */
						/* Here pins 0,1,2,3,4,,6 are output. 5,7 are input */
						/* For the Audigy LS, pin 0 (or bit 8) controls the SPDIF/Analog jack. */
						/* SB Live 24bit:
						 * bit 8 0 = SPDIF in and out / 1 = Analog (Mic or Line)-in.
						 * bit 9 0 = Mute / 1 = Analog out.
						 * bit 10 0 = Line-in / 1 = Mic-in.
						 * bit 11 0 = ? / 1 = ?
						 * bit 12 0 = 48 Khz / 1 = 96 Khz Analog out on SB Live 24bit.
						 * bit 13 0 = ? / 1 = ?
						 * bit 14 0 = Mute / 1 = Analog out
						 * bit 15 0 = ? / 1 = ?
						 * Both bit 9 and bit 14 have to be set क्रम analog sound to work on the SB Live 24bit.
						 */
						/* 8 general purpose programmable In/Out pins.
						 * GPI [8:0] Read only. Default 0.
						 * GPO [15:8] Default 0x9. (Default to SPDIF jack enabled क्रम SPDIF)
						 * GPO Enable [23:16] Default 0x0f. Setting a bit to 1, causes the pin to be an output pin.
						 */
#घोषणा AC97DATA		0x1c		/* AC97 रेजिस्टर set data रेजिस्टर (16 bit)	*/

#घोषणा AC97ADDRESS		0x1e		/* AC97 रेजिस्टर set address रेजिस्टर (8 bit)	*/

/********************************************************************************************************/
/* CA0106 poपूर्णांकer-offset रेजिस्टर set, accessed through the PTR and DATA रेजिस्टरs                     */
/********************************************************************************************************/
                                                                                                                           
/* Initially all रेजिस्टरs from 0x00 to 0x3f have zero contents. */
#घोषणा PLAYBACK_LIST_ADDR	0x00		/* Base DMA address of a list of poपूर्णांकers to each period/size */
						/* One list entry: 4 bytes क्रम DMA address, 
						 * 4 bytes क्रम period_size << 16.
						 * One list entry is 8 bytes दीर्घ.
						 * One list entry क्रम each period in the buffer.
						 */
						/* ADDR[31:0], Default: 0x0 */
#घोषणा PLAYBACK_LIST_SIZE	0x01		/* Size of list in bytes << 16. E.g. 8 periods -> 0x00380000  */
						/* SIZE[21:16], Default: 0x8 */
#घोषणा PLAYBACK_LIST_PTR	0x02		/* Poपूर्णांकer to the current period being played */
						/* PTR[5:0], Default: 0x0 */
#घोषणा PLAYBACK_UNKNOWN3	0x03		/* Not used ?? */
#घोषणा PLAYBACK_DMA_ADDR	0x04		/* Playback DMA address */
						/* DMA[31:0], Default: 0x0 */
#घोषणा PLAYBACK_PERIOD_SIZE	0x05		/* Playback period size. win2000 uses 0x04000000 */
						/* SIZE[31:16], Default: 0x0 */
#घोषणा PLAYBACK_POINTER	0x06		/* Playback period poपूर्णांकer. Used with PLAYBACK_LIST_PTR to determine buffer position currently in DAC */
						/* POINTER[15:0], Default: 0x0 */
#घोषणा PLAYBACK_PERIOD_END_ADDR 0x07		/* Playback fअगरo end address */
						/* END_ADDR[15:0], FLAG[16] 0 = करोn't stop, 1 = stop */
#घोषणा PLAYBACK_FIFO_OFFSET_ADDRESS	0x08	/* Current fअगरo offset address [21:16] */
						/* Cache size valid [5:0] */
#घोषणा PLAYBACK_UNKNOWN9	0x09		/* 0x9 to 0xf Unused */
#घोषणा CAPTURE_DMA_ADDR	0x10		/* Capture DMA address */
						/* DMA[31:0], Default: 0x0 */
#घोषणा CAPTURE_BUFFER_SIZE	0x11		/* Capture buffer size */
						/* SIZE[31:16], Default: 0x0 */
#घोषणा CAPTURE_POINTER		0x12		/* Capture buffer poपूर्णांकer. Sample currently in ADC */
						/* POINTER[15:0], Default: 0x0 */
#घोषणा CAPTURE_FIFO_OFFSET_ADDRESS	0x13	/* Current fअगरo offset address [21:16] */
						/* Cache size valid [5:0] */
#घोषणा PLAYBACK_LAST_SAMPLE    0x20		/* The sample currently being played */
/* 0x21 - 0x3f unused */
#घोषणा BASIC_INTERRUPT         0x40		/* Used by both playback and capture पूर्णांकerrupt handler */
						/* Playback (0x1<<channel_id) */
						/* Capture  (0x100<<channel_id) */
						/* Playback sample rate 96000 = 0x20000 */
						/* Start Playback [3:0] (one bit per channel)
						 * Start Capture [11:8] (one bit per channel)
						 * Playback rate [23:16] (2 bits per channel) (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * Playback mixer in enable [27:24] (one bit per channel)
						 * Playback mixer out enable [31:28] (one bit per channel)
						 */
/* The Digital out jack is shared with the Center/LFE Analogue output. 
 * The jack has 4 poles. I will call 1 - Tip, 2 - Next to 1, 3 - Next to 2, 4 - Next to 3
 * For Analogue: 1 -> Center Speaker, 2 -> Sub Woofer, 3 -> Ground, 4 -> Ground
 * For Digital: 1 -> Front SPDIF, 2 -> Rear SPDIF, 3 -> Center/Subwoofer SPDIF, 4 -> Ground.
 * Standard 4 pole Video A/V cable with RCA outमाला_दो: 1 -> White, 2 -> Yellow, 3 -> Shield on all three, 4 -> Red.
 * So, from this you can see that you cannot use a Standard 4 pole Video A/V cable with the SB Audigy LS card.
 */
/* The Front SPDIF PCM माला_लो mixed with samples from the AC97 codec, so can only work क्रम Stereo PCM and not AC3/DTS
 * The Rear SPDIF can be used क्रम Stereo PCM and also AC3/DTS
 * The Center/LFE SPDIF cannot be used क्रम AC3/DTS, but can be used क्रम Stereo PCM.
 * Summary: For ALSA we use the Rear channel क्रम SPDIF Digital AC3/DTS output
 */
/* A standard 2 pole mono mini-jack to RCA plug can be used क्रम SPDIF Stereo PCM output from the Front channel.
 * A standard 3 pole stereo mini-jack to 2 RCA plugs can be used क्रम SPDIF AC3/DTS and Stereo PCM output utilising the Rear channel and just one of the RCA plugs. 
 */
#घोषणा SPCS0			0x41		/* SPDIF output Channel Status 0 रेजिस्टर. For Rear. शेष=0x02108004, non-audio=0x02108006	*/
#घोषणा SPCS1			0x42		/* SPDIF output Channel Status 1 रेजिस्टर. For Front */
#घोषणा SPCS2			0x43		/* SPDIF output Channel Status 2 रेजिस्टर. For Center/LFE */
#घोषणा SPCS3			0x44		/* SPDIF output Channel Status 3 रेजिस्टर. Unknown */
						/* When Channel set to 0: */
#घोषणा SPCS_CLKACCYMASK	0x30000000	/* Clock accuracy				*/
#घोषणा SPCS_CLKACCY_1000PPM	0x00000000	/* 1000 parts per million			*/
#घोषणा SPCS_CLKACCY_50PPM	0x10000000	/* 50 parts per million				*/
#घोषणा SPCS_CLKACCY_VARIABLE	0x20000000	/* Variable accuracy				*/
#घोषणा SPCS_SAMPLERATEMASK	0x0f000000	/* Sample rate					*/
#घोषणा SPCS_SAMPLERATE_44	0x00000000	/* 44.1kHz sample rate				*/
#घोषणा SPCS_SAMPLERATE_48	0x02000000	/* 48kHz sample rate				*/
#घोषणा SPCS_SAMPLERATE_32	0x03000000	/* 32kHz sample rate				*/
#घोषणा SPCS_CHANNELNUMMASK	0x00f00000	/* Channel number				*/
#घोषणा SPCS_CHANNELNUM_UNSPEC	0x00000000	/* Unspecअगरied channel number			*/
#घोषणा SPCS_CHANNELNUM_LEFT	0x00100000	/* Left channel					*/
#घोषणा SPCS_CHANNELNUM_RIGHT	0x00200000	/* Right channel				*/
#घोषणा SPCS_SOURCENUMMASK	0x000f0000	/* Source number				*/
#घोषणा SPCS_SOURCENUM_UNSPEC	0x00000000	/* Unspecअगरied source number			*/
#घोषणा SPCS_GENERATIONSTATUS	0x00008000	/* Originality flag (see IEC-958 spec)		*/
#घोषणा SPCS_CATEGORYCODEMASK	0x00007f00	/* Category code (see IEC-958 spec)		*/
#घोषणा SPCS_MODEMASK		0x000000c0	/* Mode (see IEC-958 spec)			*/
#घोषणा SPCS_EMPHASISMASK	0x00000038	/* Emphasis					*/
#घोषणा SPCS_EMPHASIS_NONE	0x00000000	/* No emphasis					*/
#घोषणा SPCS_EMPHASIS_50_15	0x00000008	/* 50/15 usec 2 channel				*/
#घोषणा SPCS_COPYRIGHT		0x00000004	/* Copyright निश्चितed flag -- करो not modअगरy	*/
#घोषणा SPCS_NOTAUDIODATA	0x00000002	/* 0 = Digital audio, 1 = not audio		*/
#घोषणा SPCS_PROFESSIONAL	0x00000001	/* 0 = Consumer (IEC-958), 1 = pro (AES3-1992)	*/

						/* When Channel set to 1: */
#घोषणा SPCS_WORD_LENGTH_MASK	0x0000000f	/* Word Length Mask				*/
#घोषणा SPCS_WORD_LENGTH_16	0x00000008	/* Word Length 16 bit				*/
#घोषणा SPCS_WORD_LENGTH_17	0x00000006	/* Word Length 17 bit				*/
#घोषणा SPCS_WORD_LENGTH_18	0x00000004	/* Word Length 18 bit				*/
#घोषणा SPCS_WORD_LENGTH_19	0x00000002	/* Word Length 19 bit				*/
#घोषणा SPCS_WORD_LENGTH_20A	0x0000000a	/* Word Length 20 bit				*/
#घोषणा SPCS_WORD_LENGTH_20	0x00000009	/* Word Length 20 bit (both 0xa and 0x9 are 20 bit) */
#घोषणा SPCS_WORD_LENGTH_21	0x00000007	/* Word Length 21 bit				*/
#घोषणा SPCS_WORD_LENGTH_22	0x00000005	/* Word Length 22 bit				*/
#घोषणा SPCS_WORD_LENGTH_23	0x00000003	/* Word Length 23 bit				*/
#घोषणा SPCS_WORD_LENGTH_24	0x0000000b	/* Word Length 24 bit				*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_MASK	0x000000f0 /* Original Sample rate			*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_NONE	0x00000000 /* Original Sample rate not indicated	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_16000	0x00000010 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_RES1	0x00000020 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_32000	0x00000030 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_12000	0x00000040 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_11025	0x00000050 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_8000	0x00000060 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_RES2	0x00000070 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_192000 0x00000080 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_24000	0x00000090 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_96000	0x000000a0 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_48000	0x000000b0 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_176400 0x000000c0 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_22050	0x000000d0 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_88200	0x000000e0 /* Original Sample rate	*/
#घोषणा SPCS_ORIGINAL_SAMPLE_RATE_44100	0x000000f0 /* Original Sample rate	*/

#घोषणा SPDIF_SELECT1		0x45		/* Enables SPDIF or Analogue outमाला_दो 0-SPDIF, 0xf00-Analogue */
						/* 0x100 - Front, 0x800 - Rear, 0x200 - Center/LFE.
						 * But as the jack is shared, use 0xf00.
						 * The Winकरोws2000 driver uses 0x0000000f क्रम both digital and analog.
						 * 0xf00 पूर्णांकroduces पूर्णांकeresting noises onto the Center/LFE.
						 * If you turn the volume up, you hear computer noise,
						 * e.g. mouse moving, changing between app winकरोws etc.
						 * So, I am going to set this to 0x0000000f all the समय now,
						 * same as the winकरोws driver करोes.
						 * Use रेजिस्टर SPDIF_SELECT2(0x72) to चयन between SPDIF and Analog.
						 */
						/* When Channel = 0:
						 * Wide SPDIF क्रमmat [3:0] (one bit क्रम each channel) (0=20bit, 1=24bit)
						 * Tristate SPDIF Output [11:8] (one bit क्रम each channel) (0=Not tristate, 1=Tristate)
						 * SPDIF Bypass enable [19:16] (one bit क्रम each channel) (0=Not bypass, 1=Bypass)
						 */
						/* When Channel = 1:
						 * SPDIF 0 User data [7:0]
						 * SPDIF 1 User data [15:8]
						 * SPDIF 0 User data [23:16]
						 * SPDIF 0 User data [31:24]
						 * User data can be sent by using the SPDIF output frame pending and SPDIF output user bit पूर्णांकerrupts.
						 */
#घोषणा WATERMARK		0x46		/* Test bit to indicate cache usage level */
#घोषणा SPDIF_INPUT_STATUS	0x49		/* SPDIF Input status रेजिस्टर. Bits the same as SPCS.
						 * When Channel = 0: Bits the same as SPCS channel 0.
						 * When Channel = 1: Bits the same as SPCS channel 1.
						 * When Channel = 2:
						 * SPDIF Input User data [16:0]
						 * SPDIF Input Frame count [21:16]
						 */
#घोषणा CAPTURE_CACHE_DATA	0x50		/* 0x50-0x5f Recorded samples. */
#घोषणा CAPTURE_SOURCE          0x60            /* Capture Source 0 = MIC */
#घोषणा CAPTURE_SOURCE_CHANNEL0 0xf0000000	/* Mask क्रम selecting the Capture sources */
#घोषणा CAPTURE_SOURCE_CHANNEL1 0x0f000000	/* 0 - SPDIF mixer output. */
#घोषणा CAPTURE_SOURCE_CHANNEL2 0x00f00000      /* 1 - What you hear or . 2 - ?? */
#घोषणा CAPTURE_SOURCE_CHANNEL3 0x000f0000	/* 3 - Mic in, Line in, TAD in, Aux in. */
#घोषणा CAPTURE_SOURCE_RECORD_MAP 0x0000ffff	/* Default 0x00e4 */
						/* Record Map [7:0] (2 bits per channel) 0=mapped to channel 0, 1=mapped to channel 1, 2=mapped to channel2, 3=mapped to channel3 
						 * Record source select क्रम channel 0 [18:16]
						 * Record source select क्रम channel 1 [22:20]
						 * Record source select क्रम channel 2 [26:24]
						 * Record source select क्रम channel 3 [30:28]
						 * 0 - SPDIF mixer output.
						 * 1 - i2s mixer output.
						 * 2 - SPDIF input.
						 * 3 - i2s input.
						 * 4 - AC97 capture.
						 * 5 - SRC output.
						 */
#घोषणा CAPTURE_VOLUME1         0x61            /* Capture  volume per channel 0-3 */
#घोषणा CAPTURE_VOLUME2         0x62            /* Capture  volume per channel 4-7 */

#घोषणा PLAYBACK_ROUTING1       0x63            /* Playback routing of channels 0-7. Effects AC3 output. Default 0x32765410 */
#घोषणा ROUTING1_REAR           0x77000000      /* Channel_id 0 sends to 10, Channel_id 1 sends to 32 */
#घोषणा ROUTING1_शून्य           0x00770000      /* Channel_id 2 sends to 54, Channel_id 3 sends to 76 */
#घोषणा ROUTING1_CENTER_LFE     0x00007700      /* 0x32765410 means, send Channel_id 0 to FRONT, Channel_id 1 to REAR */
#घोषणा ROUTING1_FRONT          0x00000077	/* Channel_id 2 to CENTER_LFE, Channel_id 3 to शून्य. */
						/* Channel_id's handle stereo channels. Channel X is a single mono channel */
						/* Host is input from the PCI bus. */
						/* Host channel 0 [2:0] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 1 [6:4] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 2 [10:8] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 3 [14:12] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 4 [18:16] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 5 [22:20] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 6 [26:24] -> SPDIF Mixer/Router channel 0-7.
						 * Host channel 7 [30:28] -> SPDIF Mixer/Router channel 0-7.
						 */

#घोषणा PLAYBACK_ROUTING2       0x64            /* Playback Routing . Feeding Capture channels back पूर्णांकo Playback. Effects AC3 output. Default 0x76767676 */
						/* SRC is input from the capture inमाला_दो. */
						/* SRC channel 0 [2:0] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 1 [6:4] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 2 [10:8] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 3 [14:12] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 4 [18:16] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 5 [22:20] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 6 [26:24] -> SPDIF Mixer/Router channel 0-7.
						 * SRC channel 7 [30:28] -> SPDIF Mixer/Router channel 0-7.
						 */

#घोषणा PLAYBACK_MUTE           0x65            /* Unknown. While playing 0x0, जबतक silent 0x00fc0000 */
						/* SPDIF Mixer input control:
						 * Invert SRC to SPDIF Mixer [7-0] (One bit per channel)
						 * Invert Host to SPDIF Mixer [15:8] (One bit per channel)
						 * SRC to SPDIF Mixer disable [23:16] (One bit per channel)
						 * Host to SPDIF Mixer disable [31:24] (One bit per channel)
						 */
#घोषणा PLAYBACK_VOLUME1        0x66            /* Playback SPDIF volume per channel. Set to the same PLAYBACK_VOLUME(0x6a) */
						/* PLAYBACK_VOLUME1 must be set to 30303030 क्रम SPDIF AC3 Playback */
						/* SPDIF mixer input volume. 0=12dB, 0x30=0dB, 0xFE=-51.5dB, 0xff=Mute */
						/* One रेजिस्टर क्रम each of the 4 stereo streams. */
						/* SRC Right volume [7:0]
						 * SRC Left  volume [15:8]
						 * Host Right volume [23:16]
						 * Host Left  volume [31:24]
						 */
#घोषणा CAPTURE_ROUTING1        0x67            /* Capture Routing. Default 0x32765410 */
						/* Similar to रेजिस्टर 0x63, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outमाला_दो to the Analog outमाला_दो instead of SPDIF. */
#घोषणा CAPTURE_ROUTING2        0x68            /* Unknown Routing. Default 0x76767676 */
						/* Similar to रेजिस्टर 0x64, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outमाला_दो to the Analog outमाला_दो instead of SPDIF. */
#घोषणा CAPTURE_MUTE            0x69            /* Unknown. While capturing 0x0, जबतक silent 0x00fc0000 */
						/* Similar to रेजिस्टर 0x65, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outमाला_दो to the Analog outमाला_दो instead of SPDIF. */
#घोषणा PLAYBACK_VOLUME2        0x6a            /* Playback Analog volume per channel. Does not effect AC3 output */
						/* Similar to रेजिस्टर 0x66, except that the destination is the I2S mixer instead of the SPDIF mixer. I.E. Outमाला_दो to the Analog outमाला_दो instead of SPDIF. */
#घोषणा UNKNOWN6b               0x6b            /* Unknown. Reaकरोnly. Default 00400000 00400000 00400000 00400000 */
#घोषणा MIDI_UART_A_DATA		0x6c            /* Midi Uart A Data */
#घोषणा MIDI_UART_A_CMD		0x6d            /* Midi Uart A Command/Status */
#घोषणा MIDI_UART_B_DATA		0x6e            /* Midi Uart B Data (currently unused) */
#घोषणा MIDI_UART_B_CMD		0x6f            /* Midi Uart B Command/Status (currently unused) */

/* unique channel identअगरier क्रम midi->channel */

#घोषणा CA0106_MIDI_CHAN_A		0x1
#घोषणा CA0106_MIDI_CHAN_B		0x2

/* from mpu401 */

#घोषणा CA0106_MIDI_INPUT_AVAIL 	0x80
#घोषणा CA0106_MIDI_OUTPUT_READY	0x40
#घोषणा CA0106_MPU401_RESET		0xff
#घोषणा CA0106_MPU401_ENTER_UART	0x3f
#घोषणा CA0106_MPU401_ACK		0xfe

#घोषणा SAMPLE_RATE_TRACKER_STATUS 0x70         /* Reaकरोnly. Default 00108000 00108000 00500000 00500000 */
						/* Estimated sample rate [19:0] Relative to 48kHz. 0x8000 =  1.0
						 * Rate Locked [20]
						 * SPDIF Locked [21] For SPDIF channel only.
						 * Valid Audio [22] For SPDIF channel only.
						 */
#घोषणा CAPTURE_CONTROL         0x71            /* Some sort of routing. शेष = 40c81000 30303030 30300000 00700000 */
						/* Channel_id 0: 0x40c81000 must be changed to 0x40c80000 क्रम SPDIF AC3 input or output. */
						/* Channel_id 1: 0xffffffff(mute) 0x30303030(max) controls CAPTURE feedback पूर्णांकo PLAYBACK. */
						/* Sample rate output control रेजिस्टर Channel=0
						 * Sample output rate [1:0] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * Sample input rate [3:2] (0=48kHz, 1=Not available, 2=96kHz, 3=192Khz)
						 * SRC input source select [4] 0=Audio from digital mixer, 1=Audio from analog source.
						 * Record rate [9:8] (0=48kHz, 1=Not available, 2=96kHz, 3=192Khz)
						 * Record mixer output enable [12:10] 
						 * I2S input rate master mode [15:14] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * I2S output rate [17:16] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * I2S output source select [18] (0=Audio from host, 1=Audio from SRC)
						 * Record mixer I2S enable [20:19] (enable/disable i2sin1 and i2sin0)
						 * I2S output master घड़ी select [21] (0=256*I2S output rate, 1=512*I2S output rate.)
						 * I2S input master घड़ी select [22] (0=256*I2S input rate, 1=512*I2S input rate.)
						 * I2S input mode [23] (0=Slave, 1=Master)
						 * SPDIF output rate [25:24] (0=48kHz, 1=44.1kHz, 2=96kHz, 3=192Khz)
						 * SPDIF output source select [26] (0=host, 1=SRC)
						 * Not used [27]
						 * Record Source 0 input [29:28] (0=SPDIF in, 1=I2S in, 2=AC97 Mic, 3=AC97 PCM)
						 * Record Source 1 input [31:30] (0=SPDIF in, 1=I2S in, 2=AC97 Mic, 3=AC97 PCM)
						 */ 
						/* Sample rate output control रेजिस्टर Channel=1
						 * I2S Input 0 volume Right [7:0]
						 * I2S Input 0 volume Left [15:8]
						 * I2S Input 1 volume Right [23:16]
						 * I2S Input 1 volume Left [31:24]
						 */
						/* Sample rate output control रेजिस्टर Channel=2
						 * SPDIF Input volume Right [23:16]
						 * SPDIF Input volume Left [31:24]
						 */
						/* Sample rate output control रेजिस्टर Channel=3
						 * No used
						 */
#घोषणा SPDIF_SELECT2           0x72            /* Some sort of routing. Channel_id 0 only. शेष = 0x0f0f003f. Analog 0x000b0000, Digital 0x0b000000 */
#घोषणा ROUTING2_FRONT_MASK     0x00010000      /* Enable क्रम Front speakers. */
#घोषणा ROUTING2_CENTER_LFE_MASK 0x00020000     /* Enable क्रम Center/LFE speakers. */
#घोषणा ROUTING2_REAR_MASK      0x00080000      /* Enable क्रम Rear speakers. */
						/* Audio output control
						 * AC97 output enable [5:0]
						 * I2S output enable [19:16]
						 * SPDIF output enable [27:24]
						 */ 
#घोषणा UNKNOWN73               0x73            /* Unknown. Reaकरोnly. Default 0x0 */
#घोषणा CHIP_VERSION            0x74            /* P17 Chip version. Channel_id 0 only. Default 00000071 */
#घोषणा EXTENDED_INT_MASK       0x75            /* Used by both playback and capture पूर्णांकerrupt handler */
						/* Sets which Interrupts are enabled. */
						/* 0x00000001 = Half period. Playback.
						 * 0x00000010 = Full period. Playback.
						 * 0x00000100 = Half buffer. Playback.
						 * 0x00001000 = Full buffer. Playback.
						 * 0x00010000 = Half buffer. Capture.
						 * 0x00100000 = Full buffer. Capture.
						 * Capture can only करो 2 periods.
						 * 0x01000000 = End audio. Playback.
						 * 0x40000000 = Half buffer Playback,Caputre xrun.
						 * 0x80000000 = Full buffer Playback,Caputre xrun.
						 */
#घोषणा EXTENDED_INT            0x76            /* Used by both playback and capture पूर्णांकerrupt handler */
						/* Shows which पूर्णांकerrupts are active at the moment. */
						/* Same bit layout as EXTENDED_INT_MASK */
#घोषणा COUNTER77               0x77		/* Counter range 0 to 0x3fffff, 192000 counts per second. */
#घोषणा COUNTER78               0x78		/* Counter range 0 to 0x3fffff, 44100 counts per second. */
#घोषणा EXTENDED_INT_TIMER      0x79            /* Channel_id 0 only. Used by both playback and capture पूर्णांकerrupt handler */
						/* Causes पूर्णांकerrupts based on समयr पूर्णांकervals. */
#घोषणा SPI			0x7a		/* SPI: Serial Interface Register */
#घोषणा I2C_A			0x7b		/* I2C Address. 32 bit */
#घोषणा I2C_D0			0x7c		/* I2C Data Port 0. 32 bit */
#घोषणा I2C_D1			0x7d		/* I2C Data Port 1. 32 bit */
//I2C values
#घोषणा I2C_A_ADC_ADD_MASK	0x000000fe	//The address is a 7 bit address
#घोषणा I2C_A_ADC_RW_MASK	0x00000001	//bit mask क्रम R/W
#घोषणा I2C_A_ADC_TRANS_MASK	0x00000010  	//Bit mask क्रम I2c address DAC value
#घोषणा I2C_A_ADC_ABORT_MASK	0x00000020	//Bit mask क्रम I2C transaction पात flag
#घोषणा I2C_A_ADC_LAST_MASK	0x00000040	//Bit mask क्रम Last word transaction
#घोषणा I2C_A_ADC_BYTE_MASK	0x00000080	//Bit mask क्रम Byte Mode

#घोषणा I2C_A_ADC_ADD		0x00000034	//This is the Device address क्रम ADC 
#घोषणा I2C_A_ADC_READ		0x00000001	//To perक्रमm a पढ़ो operation
#घोषणा I2C_A_ADC_START		0x00000100	//Start I2C transaction
#घोषणा I2C_A_ADC_ABORT		0x00000200	//I2C transaction पात
#घोषणा I2C_A_ADC_LAST		0x00000400	//I2C last transaction
#घोषणा I2C_A_ADC_BYTE		0x00000800	//I2C one byte mode

#घोषणा I2C_D_ADC_REG_MASK	0xfe000000  	//ADC address रेजिस्टर 
#घोषणा I2C_D_ADC_DAT_MASK	0x01ff0000  	//ADC data रेजिस्टर

#घोषणा ADC_TIMEOUT		0x00000007	//ADC Timeout Clock Disable
#घोषणा ADC_IFC_CTRL		0x0000000b	//ADC Interface Control
#घोषणा ADC_MASTER		0x0000000c	//ADC Master Mode Control
#घोषणा ADC_POWER		0x0000000d	//ADC PowerDown Control
#घोषणा ADC_ATTEN_ADCL		0x0000000e	//ADC Attenuation ADCL
#घोषणा ADC_ATTEN_ADCR		0x0000000f	//ADC Attenuation ADCR
#घोषणा ADC_ALC_CTRL1		0x00000010	//ADC ALC Control 1
#घोषणा ADC_ALC_CTRL2		0x00000011	//ADC ALC Control 2
#घोषणा ADC_ALC_CTRL3		0x00000012	//ADC ALC Control 3
#घोषणा ADC_NOISE_CTRL		0x00000013	//ADC Noise Gate Control
#घोषणा ADC_LIMIT_CTRL		0x00000014	//ADC Limiter Control
#घोषणा ADC_MUX			0x00000015  	//ADC Mux offset

#अगर 0
/* FIXME: Not tested yet. */
#घोषणा ADC_GAIN_MASK		0x000000ff	//Mask क्रम ADC Gain
#घोषणा ADC_ZERODB		0x000000cf	//Value to set ADC to 0dB
#घोषणा ADC_MUTE_MASK		0x000000c0	//Mask क्रम ADC mute
#घोषणा ADC_MUTE		0x000000c0	//Value to mute ADC
#घोषणा ADC_OSR			0x00000008	//Mask क्रम ADC oversample rate select
#घोषणा ADC_TIMEOUT_DISABLE	0x00000008	//Value and mask to disable Timeout घड़ी
#घोषणा ADC_HPF_DISABLE		0x00000100	//Value and mask to disable High pass filter
#घोषणा ADC_TRANWIN_MASK	0x00000070	//Mask क्रम Length of Transient Winकरोw
#पूर्ण_अगर

#घोषणा ADC_MUX_MASK		0x0000000f	//Mask क्रम ADC Mux
#घोषणा ADC_MUX_PHONE		0x00000001	//Value to select TAD at ADC Mux (Not used)
#घोषणा ADC_MUX_MIC		0x00000002	//Value to select Mic at ADC Mux
#घोषणा ADC_MUX_LINEIN		0x00000004	//Value to select LineIn at ADC Mux
#घोषणा ADC_MUX_AUX		0x00000008	//Value to select Aux at ADC Mux

#घोषणा SET_CHANNEL 0  /* Testing channel outमाला_दो 0=Front, 1=Center/LFE, 2=Unknown, 3=Rear */
#घोषणा PCM_FRONT_CHANNEL 0
#घोषणा PCM_REAR_CHANNEL 1
#घोषणा PCM_CENTER_LFE_CHANNEL 2
#घोषणा PCM_UNKNOWN_CHANNEL 3
#घोषणा CONTROL_FRONT_CHANNEL 0
#घोषणा CONTROL_REAR_CHANNEL 3
#घोषणा CONTROL_CENTER_LFE_CHANNEL 1
#घोषणा CONTROL_UNKNOWN_CHANNEL 2


/* Based on WM8768 Datasheet Rev 4.2 page 32 */
#घोषणा SPI_REG_MASK	0x1ff	/* 16-bit SPI ग_लिखोs have a 7-bit address */
#घोषणा SPI_REG_SHIFT	9	/* followed by 9 bits of data */

#घोषणा SPI_LDA1_REG		0	/* digital attenuation */
#घोषणा SPI_RDA1_REG		1
#घोषणा SPI_LDA2_REG		4
#घोषणा SPI_RDA2_REG		5
#घोषणा SPI_LDA3_REG		6
#घोषणा SPI_RDA3_REG		7
#घोषणा SPI_LDA4_REG		13
#घोषणा SPI_RDA4_REG		14
#घोषणा SPI_MASTDA_REG		8

#घोषणा SPI_DA_BIT_UPDATE	(1<<8)	/* update attenuation values */
#घोषणा SPI_DA_BIT_0dB		0xff	/* 0 dB */
#घोषणा SPI_DA_BIT_infdB	0x00	/* inf dB attenuation (mute) */

#घोषणा SPI_PL_REG		2
#घोषणा SPI_PL_BIT_L_M		(0<<5)	/* left channel = mute */
#घोषणा SPI_PL_BIT_L_L		(1<<5)	/* left channel = left */
#घोषणा SPI_PL_BIT_L_R		(2<<5)	/* left channel = right */
#घोषणा SPI_PL_BIT_L_C		(3<<5)	/* left channel = (L+R)/2 */
#घोषणा SPI_PL_BIT_R_M		(0<<7)	/* right channel = mute */
#घोषणा SPI_PL_BIT_R_L		(1<<7)	/* right channel = left */
#घोषणा SPI_PL_BIT_R_R		(2<<7)	/* right channel = right */
#घोषणा SPI_PL_BIT_R_C		(3<<7)	/* right channel = (L+R)/2 */
#घोषणा SPI_IZD_REG		2
#घोषणा SPI_IZD_BIT		(0<<4)	/* infinite zero detect */

#घोषणा SPI_FMT_REG		3
#घोषणा SPI_FMT_BIT_RJ		(0<<0)	/* right justअगरied mode */
#घोषणा SPI_FMT_BIT_LJ		(1<<0)	/* left justअगरied mode */
#घोषणा SPI_FMT_BIT_I2S		(2<<0)	/* I2S mode */
#घोषणा SPI_FMT_BIT_DSP		(3<<0)	/* DSP Modes A or B */
#घोषणा SPI_LRP_REG		3
#घोषणा SPI_LRP_BIT		(1<<2)	/* invert LRCLK polarity */
#घोषणा SPI_BCP_REG		3
#घोषणा SPI_BCP_BIT		(1<<3)	/* invert BCLK polarity */
#घोषणा SPI_IWL_REG		3
#घोषणा SPI_IWL_BIT_16		(0<<4)	/* 16-bit world length */
#घोषणा SPI_IWL_BIT_20		(1<<4)	/* 20-bit world length */
#घोषणा SPI_IWL_BIT_24		(2<<4)	/* 24-bit world length */
#घोषणा SPI_IWL_BIT_32		(3<<4)	/* 32-bit world length */

#घोषणा SPI_MS_REG		10
#घोषणा SPI_MS_BIT		(1<<5)	/* master mode */
#घोषणा SPI_RATE_REG		10	/* only applies in master mode */
#घोषणा SPI_RATE_BIT_128	(0<<6)	/* MCLK = LRCLK * 128 */
#घोषणा SPI_RATE_BIT_192	(1<<6)
#घोषणा SPI_RATE_BIT_256	(2<<6)
#घोषणा SPI_RATE_BIT_384	(3<<6)
#घोषणा SPI_RATE_BIT_512	(4<<6)
#घोषणा SPI_RATE_BIT_768	(5<<6)

/* They really करो label the bit क्रम the 4th channel "4" and not "3" */
#घोषणा SPI_DMUTE0_REG		9
#घोषणा SPI_DMUTE1_REG		9
#घोषणा SPI_DMUTE2_REG		9
#घोषणा SPI_DMUTE4_REG		15
#घोषणा SPI_DMUTE0_BIT		(1<<3)
#घोषणा SPI_DMUTE1_BIT		(1<<4)
#घोषणा SPI_DMUTE2_BIT		(1<<5)
#घोषणा SPI_DMUTE4_BIT		(1<<2)

#घोषणा SPI_PHASE0_REG		3
#घोषणा SPI_PHASE1_REG		3
#घोषणा SPI_PHASE2_REG		3
#घोषणा SPI_PHASE4_REG		15
#घोषणा SPI_PHASE0_BIT		(1<<6)
#घोषणा SPI_PHASE1_BIT		(1<<7)
#घोषणा SPI_PHASE2_BIT		(1<<8)
#घोषणा SPI_PHASE4_BIT		(1<<3)

#घोषणा SPI_PDWN_REG		2	/* घातer करोwn all DACs */
#घोषणा SPI_PDWN_BIT		(1<<2)
#घोषणा SPI_DACD0_REG		10	/* घातer करोwn inभागidual DACs */
#घोषणा SPI_DACD1_REG		10
#घोषणा SPI_DACD2_REG		10
#घोषणा SPI_DACD4_REG		15
#घोषणा SPI_DACD0_BIT		(1<<1)
#घोषणा SPI_DACD1_BIT		(1<<2)
#घोषणा SPI_DACD2_BIT		(1<<3)
#घोषणा SPI_DACD4_BIT		(1<<0)	/* datasheet error says it's 1 */

#घोषणा SPI_PWRDNALL_REG	10	/* घातer करोwn everything */
#घोषणा SPI_PWRDNALL_BIT	(1<<4)

#समावेश "ca_midi.h"

काष्ठा snd_ca0106;

काष्ठा snd_ca0106_channel अणु
	काष्ठा snd_ca0106 *emu;
	पूर्णांक number;
	पूर्णांक use;
	व्योम (*पूर्णांकerrupt)(काष्ठा snd_ca0106 *emu, काष्ठा snd_ca0106_channel *channel);
	काष्ठा snd_ca0106_pcm *epcm;
पूर्ण;

काष्ठा snd_ca0106_pcm अणु
	काष्ठा snd_ca0106 *emu;
	काष्ठा snd_pcm_substream *substream;
        पूर्णांक channel_id;
	अचिन्हित लघु running;
पूर्ण;

काष्ठा snd_ca0106_details अणु
        u32 serial;
        अक्षर * name;
	पूर्णांक ac97;	/* ac97 = 0 -> Select MIC, Line in, TAD in, AUX in.
			   ac97 = 1 -> Default to AC97 in. */
	पूर्णांक gpio_type;	/* gpio_type = 1 -> shared mic-in/line-in
			   gpio_type = 2 -> shared side-out/line-in. */
	पूर्णांक i2c_adc;	/* with i2c_adc=1, the driver adds some capture volume
			   controls, phone, mic, line-in and aux. */
	u16 spi_dac;	/* spi_dac = 0 -> no spi पूर्णांकerface क्रम DACs
			   spi_dac = 0x<front><rear><center-lfe><side>
			   -> specअगरies DAC id क्रम each channel pair. */
पूर्ण;

// definition of the chip-specअगरic record
काष्ठा snd_ca0106 अणु
	काष्ठा snd_card *card;
	स्थिर काष्ठा snd_ca0106_details *details;
	काष्ठा pci_dev *pci;

	अचिन्हित दीर्घ port;
	काष्ठा resource *res_port;
	पूर्णांक irq;

	अचिन्हित पूर्णांक serial;            /* serial number */
	अचिन्हित लघु model;		/* subप्रणाली id */

	spinlock_t emu_lock;

	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_pcm *pcm[4];

	काष्ठा snd_ca0106_channel playback_channels[4];
	काष्ठा snd_ca0106_channel capture_channels[4];
	u32 spdअगर_bits[4];             /* s/pdअगर out शेष setup */
	u32 spdअगर_str_bits[4];         /* s/pdअगर out per-stream setup */
	पूर्णांक spdअगर_enable;
	पूर्णांक capture_source;
	पूर्णांक i2c_capture_source;
	u8 i2c_capture_volume[4][2];
	पूर्णांक capture_mic_line_in;

	काष्ठा snd_dma_buffer buffer;

	काष्ठा snd_ca_midi midi;
	काष्ठा snd_ca_midi midi2;

	u16 spi_dac_reg[16];

#अगर_घोषित CONFIG_PM_SLEEP
#घोषणा NUM_SAVED_VOLUMES	9
	अचिन्हित पूर्णांक saved_vol[NUM_SAVED_VOLUMES];
#पूर्ण_अगर
पूर्ण;

पूर्णांक snd_ca0106_mixer(काष्ठा snd_ca0106 *emu);
पूर्णांक snd_ca0106_proc_init(काष्ठा snd_ca0106 * emu);

अचिन्हित पूर्णांक snd_ca0106_ptr_पढ़ो(काष्ठा snd_ca0106 * emu, 
				 अचिन्हित पूर्णांक reg, 
				 अचिन्हित पूर्णांक chn);

व्योम snd_ca0106_ptr_ग_लिखो(काष्ठा snd_ca0106 *emu, 
			  अचिन्हित पूर्णांक reg, 
			  अचिन्हित पूर्णांक chn, 
			  अचिन्हित पूर्णांक data);

पूर्णांक snd_ca0106_i2c_ग_लिखो(काष्ठा snd_ca0106 *emu, u32 reg, u32 value);

पूर्णांक snd_ca0106_spi_ग_लिखो(काष्ठा snd_ca0106 * emu,
				   अचिन्हित पूर्णांक data);

#अगर_घोषित CONFIG_PM_SLEEP
व्योम snd_ca0106_mixer_suspend(काष्ठा snd_ca0106 *chip);
व्योम snd_ca0106_mixer_resume(काष्ठा snd_ca0106 *chip);
#अन्यथा
#घोषणा snd_ca0106_mixer_suspend(chip)	करो अणु पूर्ण जबतक (0)
#घोषणा snd_ca0106_mixer_resume(chip)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर
