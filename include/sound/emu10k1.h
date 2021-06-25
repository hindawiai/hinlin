<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *		     Creative Lअसल, Inc.
 *  Definitions क्रम EMU10K1 (SB Live!) chips
 */
#अगर_अघोषित __SOUND_EMU10K1_H
#घोषणा __SOUND_EMU10K1_H


#समावेश <sound/pcm.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/hwdep.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/util_स्मृति.स>
#समावेश <sound/pcm-indirect.h>
#समावेश <sound/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>

#समावेश <uapi/sound/emu10k1.h>

/* ------------------- DEFINES -------------------- */

#घोषणा EMUPAGESIZE     4096
#घोषणा MAXREQVOICES    8
#घोषणा MAXPAGES0       4096	/* 32 bit mode */
#घोषणा MAXPAGES1       8192	/* 31 bit mode */
#घोषणा RESERVED        0
#घोषणा NUM_MIDI        16
#घोषणा NUM_G           64              /* use all channels */
#घोषणा NUM_FXSENDS     4
#घोषणा NUM_EFX_PLAYBACK    16

/* FIXME? - according to the OSS driver the EMU10K1 needs a 29 bit DMA mask */
#घोषणा EMU10K1_DMA_MASK	0x7fffffffUL	/* 31bit */
#घोषणा AUDIGY_DMA_MASK		0xffffffffUL	/* 32bit mode */

#घोषणा TMEMSIZE        256*1024
#घोषणा TMEMSIZEREG     4

#घोषणा IP_TO_CP(ip) ((ip == 0) ? 0 : (((0x00001000uL | (ip & 0x00000FFFL)) << (((ip >> 12) & 0x000FL) + 4)) & 0xFFFF0000uL))

// Audigy specअगरy रेजिस्टरs are prefixed with 'A_'

/************************************************************************************************/
/* PCI function 0 रेजिस्टरs, address = <val> + PCIBASE0						*/
/************************************************************************************************/

#घोषणा PTR			0x00		/* Indexed रेजिस्टर set poपूर्णांकer रेजिस्टर	*/
						/* NOTE: The CHANNELNUM and ADDRESS words can	*/
						/* be modअगरied independently of each other.	*/
#घोषणा PTR_CHANNELNUM_MASK	0x0000003f	/* For each per-channel रेजिस्टर, indicates the	*/
						/* channel number of the रेजिस्टर to be		*/
						/* accessed.  For non per-channel रेजिस्टरs the	*/
						/* value should be set to zero.			*/
#घोषणा PTR_ADDRESS_MASK	0x07ff0000	/* Register index				*/
#घोषणा A_PTR_ADDRESS_MASK	0x0fff0000

#घोषणा DATA			0x04		/* Indexed रेजिस्टर set data रेजिस्टर		*/

#घोषणा IPR			0x08		/* Global पूर्णांकerrupt pending रेजिस्टर		*/
						/* Clear pending पूर्णांकerrupts by writing a 1 to	*/
						/* the relevant bits and zero to the other bits	*/
#घोषणा IPR_P16V		0x80000000	/* Bit set when the CA0151 P16V chip wishes
						   to पूर्णांकerrupt */
#घोषणा IPR_GPIOMSG		0x20000000	/* GPIO message पूर्णांकerrupt (RE'd, still not sure 
						   which INTE bits enable it)			*/

/* The next two पूर्णांकerrupts are क्रम the midi port on the Audigy Drive (A_MPU1)			*/
#घोषणा IPR_A_MIDITRANSBUFEMPTY2 0x10000000	/* MIDI UART transmit buffer empty		*/
#घोषणा IPR_A_MIसूचीECVBUFEMPTY2	0x08000000	/* MIDI UART receive buffer empty		*/

#घोषणा IPR_SPDIFBUFFULL	0x04000000	/* SPDIF capture related, 10k2 only? (RE)	*/
#घोषणा IPR_SPDIFBUFHALFFULL	0x02000000	/* SPDIF capture related? (RE)			*/

#घोषणा IPR_SAMPLERATETRACKER	0x01000000	/* Sample rate tracker lock status change	*/
#घोषणा IPR_FXDSP		0x00800000	/* Enable FX DSP पूर्णांकerrupts			*/
#घोषणा IPR_FORCEINT		0x00400000	/* Force Sound Blaster पूर्णांकerrupt		*/
#घोषणा IPR_PCIERROR		0x00200000	/* PCI bus error				*/
#घोषणा IPR_VOLINCR		0x00100000	/* Volume increment button pressed		*/
#घोषणा IPR_VOLDECR		0x00080000	/* Volume decrement button pressed		*/
#घोषणा IPR_MUTE		0x00040000	/* Mute button pressed				*/
#घोषणा IPR_MICBUFFULL		0x00020000	/* Microphone buffer full			*/
#घोषणा IPR_MICBUFHALFFULL	0x00010000	/* Microphone buffer half full			*/
#घोषणा IPR_ADCBUFFULL		0x00008000	/* ADC buffer full				*/
#घोषणा IPR_ADCBUFHALFFULL	0x00004000	/* ADC buffer half full				*/
#घोषणा IPR_EFXBUFFULL		0x00002000	/* Effects buffer full				*/
#घोषणा IPR_EFXBUFHALFFULL	0x00001000	/* Effects buffer half full			*/
#घोषणा IPR_GPSPDIFSTATUSCHANGE	0x00000800	/* GPSPDIF channel status change		*/
#घोषणा IPR_CDROMSTATUSCHANGE	0x00000400	/* CD-ROM channel status change			*/
#घोषणा IPR_INTERVALTIMER	0x00000200	/* Interval समयr terminal count		*/
#घोषणा IPR_MIDITRANSBUFEMPTY	0x00000100	/* MIDI UART transmit buffer empty		*/
#घोषणा IPR_MIसूचीECVBUFEMPTY	0x00000080	/* MIDI UART receive buffer empty		*/
#घोषणा IPR_CHANNELLOOP		0x00000040	/* Channel (half) loop पूर्णांकerrupt(s) pending	*/
#घोषणा IPR_CHANNELNUMBERMASK	0x0000003f	/* When IPR_CHANNELLOOP is set, indicates the	*/
						/* highest set channel in CLIPL, CLIPH, HLIPL,  */
						/* or HLIPH.  When IP is written with CL set,	*/
						/* the bit in H/CLIPL or H/CLIPH corresponding	*/
						/* to the CIN value written will be cleared.	*/

#घोषणा INTE			0x0c		/* Interrupt enable रेजिस्टर			*/
#घोषणा INTE_VIRTUALSB_MASK	0xc0000000	/* Virtual Soundblaster I/O port capture	*/
#घोषणा INTE_VIRTUALSB_220	0x00000000	/* Capture at I/O base address 0x220-0x22f	*/
#घोषणा INTE_VIRTUALSB_240	0x40000000	/* Capture at I/O base address 0x240		*/
#घोषणा INTE_VIRTUALSB_260	0x80000000	/* Capture at I/O base address 0x260		*/
#घोषणा INTE_VIRTUALSB_280	0xc0000000	/* Capture at I/O base address 0x280		*/
#घोषणा INTE_VIRTUALMPU_MASK	0x30000000	/* Virtual MPU I/O port capture			*/
#घोषणा INTE_VIRTUALMPU_300	0x00000000	/* Capture at I/O base address 0x300-0x301	*/
#घोषणा INTE_VIRTUALMPU_310	0x10000000	/* Capture at I/O base address 0x310		*/
#घोषणा INTE_VIRTUALMPU_320	0x20000000	/* Capture at I/O base address 0x320		*/
#घोषणा INTE_VIRTUALMPU_330	0x30000000	/* Capture at I/O base address 0x330		*/
#घोषणा INTE_MASTERDMAENABLE	0x08000000	/* Master DMA emulation at 0x000-0x00f		*/
#घोषणा INTE_SLAVEDMAENABLE	0x04000000	/* Slave DMA emulation at 0x0c0-0x0df		*/
#घोषणा INTE_MASTERPICENABLE	0x02000000	/* Master PIC emulation at 0x020-0x021		*/
#घोषणा INTE_SLAVEPICENABLE	0x01000000	/* Slave PIC emulation at 0x0a0-0x0a1		*/
#घोषणा INTE_VSBENABLE		0x00800000	/* Enable भव Soundblaster			*/
#घोषणा INTE_ADLIBENABLE	0x00400000	/* Enable AdLib emulation at 0x388-0x38b	*/
#घोषणा INTE_MPUENABLE		0x00200000	/* Enable भव MPU				*/
#घोषणा INTE_FORCEINT		0x00100000	/* Continuously निश्चित INTAN			*/

#घोषणा INTE_MRHANDENABLE	0x00080000	/* Enable the "Mr. Hand" logic			*/
						/* NOTE: There is no reason to use this under	*/
						/* Linux, and it will cause odd hardware 	*/
						/* behavior and possibly अक्रमom segfaults and	*/
						/* lockups अगर enabled.				*/

/* The next two पूर्णांकerrupts are क्रम the midi port on the Audigy Drive (A_MPU1)			*/
#घोषणा INTE_A_MIDITXENABLE2	0x00020000	/* Enable MIDI transmit-buffer-empty पूर्णांकerrupts	*/
#घोषणा INTE_A_MIसूचीXENABLE2	0x00010000	/* Enable MIDI receive-buffer-empty पूर्णांकerrupts	*/


#घोषणा INTE_SAMPLERATETRACKER	0x00002000	/* Enable sample rate tracker पूर्णांकerrupts	*/
						/* NOTE: This bit must always be enabled       	*/
#घोषणा INTE_FXDSPENABLE	0x00001000	/* Enable FX DSP पूर्णांकerrupts			*/
#घोषणा INTE_PCIERRORENABLE	0x00000800	/* Enable PCI bus error पूर्णांकerrupts		*/
#घोषणा INTE_VOLINCRENABLE	0x00000400	/* Enable volume increment button पूर्णांकerrupts	*/
#घोषणा INTE_VOLDECRENABLE	0x00000200	/* Enable volume decrement button पूर्णांकerrupts	*/
#घोषणा INTE_MUTEENABLE		0x00000100	/* Enable mute button पूर्णांकerrupts		*/
#घोषणा INTE_MICBUFENABLE	0x00000080	/* Enable microphone buffer पूर्णांकerrupts		*/
#घोषणा INTE_ADCBUFENABLE	0x00000040	/* Enable ADC buffer पूर्णांकerrupts			*/
#घोषणा INTE_EFXBUFENABLE	0x00000020	/* Enable Effects buffer पूर्णांकerrupts		*/
#घोषणा INTE_GPSPDIFENABLE	0x00000010	/* Enable GPSPDIF status पूर्णांकerrupts		*/
#घोषणा INTE_CDSPDIFENABLE	0x00000008	/* Enable CDSPDIF status पूर्णांकerrupts		*/
#घोषणा INTE_INTERVALTIMERENB	0x00000004	/* Enable पूर्णांकerval समयr पूर्णांकerrupts		*/
#घोषणा INTE_MIDITXENABLE	0x00000002	/* Enable MIDI transmit-buffer-empty पूर्णांकerrupts	*/
#घोषणा INTE_MIसूचीXENABLE	0x00000001	/* Enable MIDI receive-buffer-empty पूर्णांकerrupts	*/

#घोषणा WC			0x10		/* Wall Clock रेजिस्टर				*/
#घोषणा WC_SAMPLECOUNTER_MASK	0x03FFFFC0	/* Sample periods elapsed since reset		*/
#घोषणा WC_SAMPLECOUNTER	0x14060010
#घोषणा WC_CURRENTCHANNEL	0x0000003F	/* Channel [0..63] currently being serviced	*/
						/* NOTE: Each channel takes 1/64th of a sample	*/
						/* period to be serviced.			*/

#घोषणा HCFG			0x14		/* Hardware config रेजिस्टर			*/
						/* NOTE: There is no reason to use the legacy	*/
						/* SoundBlaster emulation stuff described below	*/
						/* under Linux, and all kinds of weird hardware	*/
						/* behavior can result अगर you try.  Don't.	*/
#घोषणा HCFG_LEGACYFUNC_MASK	0xe0000000	/* Legacy function number 			*/
#घोषणा HCFG_LEGACYFUNC_MPU	0x00000000	/* Legacy MPU	 				*/
#घोषणा HCFG_LEGACYFUNC_SB	0x40000000	/* Legacy SB					*/
#घोषणा HCFG_LEGACYFUNC_AD	0x60000000	/* Legacy AD					*/
#घोषणा HCFG_LEGACYFUNC_MPIC	0x80000000	/* Legacy MPIC					*/
#घोषणा HCFG_LEGACYFUNC_MDMA	0xa0000000	/* Legacy MDMA					*/
#घोषणा HCFG_LEGACYFUNC_SPCI	0xc0000000	/* Legacy SPCI					*/
#घोषणा HCFG_LEGACYFUNC_SDMA	0xe0000000	/* Legacy SDMA					*/
#घोषणा HCFG_IOCAPTUREADDR	0x1f000000	/* The 4 LSBs of the captured I/O address.	*/
#घोषणा HCFG_LEGACYWRITE	0x00800000	/* 1 = ग_लिखो, 0 = पढ़ो 				*/
#घोषणा HCFG_LEGACYWORD		0x00400000	/* 1 = word, 0 = byte 				*/
#घोषणा HCFG_LEGACYINT		0x00200000	/* 1 = legacy event captured. Write 1 to clear.	*/
						/* NOTE: The rest of the bits in this रेजिस्टर	*/
						/* _are_ relevant under Linux.			*/
#घोषणा HCFG_PUSH_BUTTON_ENABLE 0x00100000	/* Enables Volume Inc/Dec and Mute functions    */
#घोषणा HCFG_BAUD_RATE		0x00080000	/* 0 = 48kHz, 1 = 44.1kHz			*/
#घोषणा HCFG_EXPANDED_MEM	0x00040000	/* 1 = any 16M of 4G addr, 0 = 32M of 2G addr	*/
#घोषणा HCFG_CODECFORMAT_MASK	0x00030000	/* CODEC क्रमmat					*/

/* Specअगरic to Alice2, CA0102 */
#घोषणा HCFG_CODECFORMAT_AC97_1	0x00000000	/* AC97 CODEC क्रमmat -- Ver 1.03		*/
#घोषणा HCFG_CODECFORMAT_AC97_2	0x00010000	/* AC97 CODEC क्रमmat -- Ver 2.1			*/
#घोषणा HCFG_AUTOMUTE_ASYNC	0x00008000	/* When set, the async sample rate convertors	*/
						/* will स्वतःmatically mute their output when	*/
						/* they are not rate-locked to the बाह्यal	*/
						/* async audio source  				*/
#घोषणा HCFG_AUTOMUTE_SPDIF	0x00004000	/* When set, the async sample rate convertors	*/
						/* will स्वतःmatically mute their output when	*/
						/* the SPDIF V-bit indicates invalid audio	*/
#घोषणा HCFG_EMU32_SLAVE	0x00002000	/* 0 = Master, 1 = Slave. Slave क्रम EMU1010	*/
#घोषणा HCFG_SLOW_RAMP		0x00001000	/* Increases Send Smoothing समय स्थिरant	*/
/* 0x00000800 not used on Alice2 */
#घोषणा HCFG_PHASE_TRACK_MASK	0x00000700	/* When set, क्रमces corresponding input to	*/
						/* phase track the previous input.		*/
						/* I2S0 can phase track the last S/PDIF input	*/
#घोषणा HCFG_I2S_ASRC_ENABLE	0x00000070	/* When set, enables asynchronous sample rate   */
						/* conversion क्रम the corresponding		*/
 						/* I2S क्रमmat input				*/
/* Rest of HCFG 0x0000000f same as below. LOCKSOUNDCACHE etc.  */



/* Older chips */
#घोषणा HCFG_CODECFORMAT_AC97	0x00000000	/* AC97 CODEC क्रमmat -- Primary Output		*/
#घोषणा HCFG_CODECFORMAT_I2S	0x00010000	/* I2S CODEC क्रमmat -- Secondary (Rear) Output	*/
#घोषणा HCFG_GPINPUT0		0x00004000	/* External pin112				*/
#घोषणा HCFG_GPINPUT1		0x00002000	/* External pin110				*/
#घोषणा HCFG_GPOUTPUT_MASK	0x00001c00	/* External pins which may be controlled	*/
#घोषणा HCFG_GPOUT0		0x00001000	/* External pin? (spdअगर enable on 5.1)		*/
#घोषणा HCFG_GPOUT1		0x00000800	/* External pin? (IR)				*/
#घोषणा HCFG_GPOUT2		0x00000400	/* External pin? (IR)				*/
#घोषणा HCFG_JOYENABLE      	0x00000200	/* Internal joystick enable    			*/
#घोषणा HCFG_PHASETRACKENABLE	0x00000100	/* Phase tracking enable			*/
						/* 1 = Force all 3 async digital inमाला_दो to use	*/
						/* the same async sample rate tracker (ZVIDEO)	*/
#घोषणा HCFG_AC3ENABLE_MASK	0x000000e0	/* AC3 async input control - Not implemented	*/
#घोषणा HCFG_AC3ENABLE_ZVIDEO	0x00000080	/* Channels 0 and 1 replace ZVIDEO		*/
#घोषणा HCFG_AC3ENABLE_CDSPDIF	0x00000040	/* Channels 0 and 1 replace CDSPDIF		*/
#घोषणा HCFG_AC3ENABLE_GPSPDIF  0x00000020      /* Channels 0 and 1 replace GPSPDIF             */
#घोषणा HCFG_AUTOMUTE		0x00000010	/* When set, the async sample rate convertors	*/
						/* will स्वतःmatically mute their output when	*/
						/* they are not rate-locked to the बाह्यal	*/
						/* async audio source  				*/
#घोषणा HCFG_LOCKSOUNDCACHE	0x00000008	/* 1 = Cancel busपंचांगaster accesses to soundcache */
						/* NOTE: This should generally never be used.  	*/
#घोषणा HCFG_LOCKTANKCACHE_MASK	0x00000004	/* 1 = Cancel busपंचांगaster accesses to tankcache	*/
						/* NOTE: This should generally never be used.  	*/
#घोषणा HCFG_LOCKTANKCACHE	0x01020014
#घोषणा HCFG_MUTEBUTTONENABLE	0x00000002	/* 1 = Master mute button sets AUDIOENABLE = 0.	*/
						/* NOTE: This is a 'cheap' way to implement a	*/
						/* master mute function on the mute button, and	*/
						/* in general should not be used unless a more	*/
						/* sophisticated master mute function has not	*/
						/* been written.       				*/
#घोषणा HCFG_AUDIOENABLE	0x00000001	/* 0 = CODECs transmit zero-valued samples	*/
						/* Should be set to 1 when the EMU10K1 is	*/
						/* completely initialized.			*/

//For Audigy, MPU port move to 0x70-0x74 ptr रेजिस्टर

#घोषणा MUDATA			0x18		/* MPU401 data रेजिस्टर (8 bits)       		*/

#घोषणा MUCMD			0x19		/* MPU401 command रेजिस्टर (8 bits)    		*/
#घोषणा MUCMD_RESET		0xff		/* RESET command				*/
#घोषणा MUCMD_ENTERUARTMODE	0x3f		/* Enter_UART_mode command			*/
						/* NOTE: All other commands are ignored		*/

#घोषणा MUSTAT			MUCMD		/* MPU401 status रेजिस्टर (8 bits)     		*/
#घोषणा MUSTAT_IRDYN		0x80		/* 0 = MIDI data or command ACK			*/
#घोषणा MUSTAT_ORDYN		0x40		/* 0 = MUDATA can accept a command or data	*/

#घोषणा A_IOCFG			0x18		/* GPIO on Audigy card (16bits)			*/
#घोषणा A_GPINPUT_MASK		0xff00
#घोषणा A_GPOUTPUT_MASK		0x00ff

// Audigy output/GPIO stuff taken from the kX drivers
#घोषणा A_IOCFG_GPOUT0		0x0044		/* analog/digital				*/
#घोषणा A_IOCFG_DISABLE_ANALOG	0x0040		/* = 'enable' क्रम Audigy2 (chiprev=4)		*/
#घोषणा A_IOCFG_ENABLE_DIGITAL	0x0004
#घोषणा A_IOCFG_ENABLE_DIGITAL_AUDIGY4	0x0080
#घोषणा A_IOCFG_UNKNOWN_20      0x0020
#घोषणा A_IOCFG_DISABLE_AC97_FRONT      0x0080  /* turn off ac97 front -> front (10k2.1)	*/
#घोषणा A_IOCFG_GPOUT1		0x0002		/* IR? drive's पूर्णांकernal bypass (?)		*/
#घोषणा A_IOCFG_GPOUT2		0x0001		/* IR */
#घोषणा A_IOCFG_MULTIPURPOSE_JACK	0x2000  /* center+lfe+rear_center (a2/a2ex)		*/
                                                /* + digital क्रम generic 10k2			*/
#घोषणा A_IOCFG_DIGITAL_JACK    0x1000          /* digital क्रम a2 platinum			*/
#घोषणा A_IOCFG_FRONT_JACK      0x4000
#घोषणा A_IOCFG_REAR_JACK       0x8000
#घोषणा A_IOCFG_PHONES_JACK     0x0100          /* LiveDrive					*/

/* outमाला_दो:
 *	क्रम audigy2 platinum:	0xa00
 *	क्रम a2 platinum ex:	0x1c00
 *	क्रम a1 platinum:	0x0
 */

#घोषणा TIMER			0x1a		/* Timer terminal count रेजिस्टर		*/
						/* NOTE: After the rate is changed, a maximum	*/
						/* of 1024 sample periods should be allowed	*/
						/* beक्रमe the new rate is guaranteed accurate.	*/
#घोषणा TIMER_RATE_MASK		0x000003ff	/* Timer पूर्णांकerrupt rate in sample periods	*/
						/* 0 == 1024 periods, [1..4] are not useful	*/
#घोषणा TIMER_RATE		0x0a00001a

#घोषणा AC97DATA		0x1c		/* AC97 रेजिस्टर set data रेजिस्टर (16 bit)	*/

#घोषणा AC97ADDRESS		0x1e		/* AC97 रेजिस्टर set address रेजिस्टर (8 bit)	*/
#घोषणा AC97ADDRESS_READY	0x80		/* Read-only bit, reflects CODEC READY संकेत	*/
#घोषणा AC97ADDRESS_ADDRESS	0x7f		/* Address of indexed AC97 रेजिस्टर		*/

/* Available on the Audigy 2 and Audigy 4 only. This is the P16V chip. */
#घोषणा PTR2			0x20		/* Indexed रेजिस्टर set poपूर्णांकer रेजिस्टर	*/
#घोषणा DATA2			0x24		/* Indexed रेजिस्टर set data रेजिस्टर		*/
#घोषणा IPR2			0x28		/* P16V पूर्णांकerrupt pending रेजिस्टर		*/
#घोषणा IPR2_PLAYBACK_CH_0_LOOP      0x00001000 /* Playback Channel 0 loop                               */
#घोषणा IPR2_PLAYBACK_CH_0_HALF_LOOP 0x00000100 /* Playback Channel 0 half loop                          */
#घोषणा IPR2_CAPTURE_CH_0_LOOP       0x00100000 /* Capture Channel 0 loop                               */
#घोषणा IPR2_CAPTURE_CH_0_HALF_LOOP  0x00010000 /* Capture Channel 0 half loop                          */
						/* 0x00000100 Playback. Only in once per period.
						 * 0x00110000 Capture. Int on half buffer.
						 */
#घोषणा INTE2			0x2c		/* P16V Interrupt enable रेजिस्टर. 	*/
#घोषणा INTE2_PLAYBACK_CH_0_LOOP      0x00001000 /* Playback Channel 0 loop                               */
#घोषणा INTE2_PLAYBACK_CH_0_HALF_LOOP 0x00000100 /* Playback Channel 0 half loop                          */
#घोषणा INTE2_PLAYBACK_CH_1_LOOP      0x00002000 /* Playback Channel 1 loop                               */
#घोषणा INTE2_PLAYBACK_CH_1_HALF_LOOP 0x00000200 /* Playback Channel 1 half loop                          */
#घोषणा INTE2_PLAYBACK_CH_2_LOOP      0x00004000 /* Playback Channel 2 loop                               */
#घोषणा INTE2_PLAYBACK_CH_2_HALF_LOOP 0x00000400 /* Playback Channel 2 half loop                          */
#घोषणा INTE2_PLAYBACK_CH_3_LOOP      0x00008000 /* Playback Channel 3 loop                               */
#घोषणा INTE2_PLAYBACK_CH_3_HALF_LOOP 0x00000800 /* Playback Channel 3 half loop                          */
#घोषणा INTE2_CAPTURE_CH_0_LOOP       0x00100000 /* Capture Channel 0 loop                               */
#घोषणा INTE2_CAPTURE_CH_0_HALF_LOOP  0x00010000 /* Caputre Channel 0 half loop                          */
#घोषणा HCFG2			0x34		/* Defaults: 0, win2000 sets it to 00004201 */
						/* 0x00000000 2-channel output. */
						/* 0x00000200 8-channel output. */
						/* 0x00000004 छोड़ोs stream/irq fail. */
						/* Rest of bits no nothing to sound output */
						/* bit 0: Enable P16V audio.
						 * bit 1: Lock P16V record memory cache.
						 * bit 2: Lock P16V playback memory cache.
						 * bit 3: Dummy record insert zero samples.
						 * bit 8: Record 8-channel in phase.
						 * bit 9: Playback 8-channel in phase.
						 * bit 11-12: Playback mixer attenuation: 0=0dB, 1=-6dB, 2=-12dB, 3=Mute.
						 * bit 13: Playback mixer enable.
						 * bit 14: Route SRC48 mixer output to fx engine.
						 * bit 15: Enable IEEE 1394 chip.
						 */
#घोषणा IPR3			0x38		/* Cdअगर पूर्णांकerrupt pending रेजिस्टर		*/
#घोषणा INTE3			0x3c		/* Cdअगर पूर्णांकerrupt enable रेजिस्टर. 	*/
/************************************************************************************************/
/* PCI function 1 रेजिस्टरs, address = <val> + PCIBASE1						*/
/************************************************************************************************/

#घोषणा JOYSTICK1		0x00		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK2		0x01		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK3		0x02		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK4		0x03		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK5		0x04		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK6		0x05		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK7		0x06		/* Analog joystick port रेजिस्टर		*/
#घोषणा JOYSTICK8		0x07		/* Analog joystick port रेजिस्टर		*/

/* When writing, any ग_लिखो causes JOYSTICK_COMPARATOR output enable to be pulsed on ग_लिखो.	*/
/* When पढ़ोing, use these bitfields: */
#घोषणा JOYSTICK_BUTTONS	0x0f		/* Joystick button data				*/
#घोषणा JOYSTICK_COMPARATOR	0xf0		/* Joystick comparator data			*/


/********************************************************************************************************/
/* Emu10k1 poपूर्णांकer-offset रेजिस्टर set, accessed through the PTR and DATA रेजिस्टरs			*/
/********************************************************************************************************/

#घोषणा CPF			0x00		/* Current pitch and fraction रेजिस्टर			*/
#घोषणा CPF_CURRENTPITCH_MASK	0xffff0000	/* Current pitch (linear, 0x4000 == unity pitch shअगरt) 	*/
#घोषणा CPF_CURRENTPITCH	0x10100000
#घोषणा CPF_STEREO_MASK		0x00008000	/* 1 = Even channel पूर्णांकerleave, odd channel locked	*/
#घोषणा CPF_STOP_MASK		0x00004000	/* 1 = Current pitch क्रमced to 0			*/
#घोषणा CPF_FRACADDRESS_MASK	0x00003fff	/* Linear fractional address of the current channel	*/

#घोषणा PTRX			0x01		/* Pitch target and send A/B amounts रेजिस्टर		*/
#घोषणा PTRX_PITCHTARGET_MASK	0xffff0000	/* Pitch target of specअगरied channel			*/
#घोषणा PTRX_PITCHTARGET	0x10100001
#घोषणा PTRX_FXSENDAMOUNT_A_MASK 0x0000ff00	/* Linear level of channel output sent to FX send bus A	*/
#घोषणा PTRX_FXSENDAMOUNT_A	0x08080001
#घोषणा PTRX_FXSENDAMOUNT_B_MASK 0x000000ff	/* Linear level of channel output sent to FX send bus B	*/
#घोषणा PTRX_FXSENDAMOUNT_B	0x08000001

#घोषणा CVCF			0x02		/* Current volume and filter cutoff रेजिस्टर		*/
#घोषणा CVCF_CURRENTVOL_MASK	0xffff0000	/* Current linear volume of specअगरied channel		*/
#घोषणा CVCF_CURRENTVOL		0x10100002
#घोषणा CVCF_CURRENTFILTER_MASK	0x0000ffff	/* Current filter cutoff frequency of specअगरied channel	*/
#घोषणा CVCF_CURRENTFILTER	0x10000002

#घोषणा VTFT			0x03		/* Volume target and filter cutoff target रेजिस्टर	*/
#घोषणा VTFT_VOLUMETARGET_MASK	0xffff0000	/* Volume target of specअगरied channel			*/
#घोषणा VTFT_VOLUMETARGET	0x10100003
#घोषणा VTFT_FILTERTARGET_MASK	0x0000ffff	/* Filter cutoff target of specअगरied channel		*/
#घोषणा VTFT_FILTERTARGET	0x10000003

#घोषणा Z1			0x05		/* Filter delay memory 1 रेजिस्टर			*/

#घोषणा Z2			0x04		/* Filter delay memory 2 रेजिस्टर			*/

#घोषणा PSST			0x06		/* Send C amount and loop start address रेजिस्टर	*/
#घोषणा PSST_FXSENDAMOUNT_C_MASK 0xff000000	/* Linear level of channel output sent to FX send bus C	*/

#घोषणा PSST_FXSENDAMOUNT_C	0x08180006

#घोषणा PSST_LOOPSTARTADDR_MASK	0x00ffffff	/* Loop start address of the specअगरied channel		*/
#घोषणा PSST_LOOPSTARTADDR	0x18000006

#घोषणा DSL			0x07		/* Send D amount and loop start address रेजिस्टर	*/
#घोषणा DSL_FXSENDAMOUNT_D_MASK	0xff000000	/* Linear level of channel output sent to FX send bus D	*/

#घोषणा DSL_FXSENDAMOUNT_D	0x08180007

#घोषणा DSL_LOOPENDADDR_MASK	0x00ffffff	/* Loop end address of the specअगरied channel		*/
#घोषणा DSL_LOOPENDADDR		0x18000007

#घोषणा CCCA			0x08		/* Filter Q, पूर्णांकerp. ROM, byte size, cur. addr रेजिस्टर */
#घोषणा CCCA_RESOन_अंकCE		0xf0000000	/* Lowpass filter resonance (Q) height			*/
#घोषणा CCCA_INTERPROMMASK	0x0e000000	/* Selects passband of पूर्णांकerpolation ROM		*/
						/* 1 == full band, 7 == lowpass				*/
						/* ROM 0 is used when pitch shअगरting करोwnward or less	*/
						/* then 3 semitones upward.  Increasingly higher ROM	*/
						/* numbers are used, typically in steps of 3 semitones,	*/
						/* as upward pitch shअगरting is perक्रमmed.		*/
#घोषणा CCCA_INTERPROM_0	0x00000000	/* Select पूर्णांकerpolation ROM 0				*/
#घोषणा CCCA_INTERPROM_1	0x02000000	/* Select पूर्णांकerpolation ROM 1				*/
#घोषणा CCCA_INTERPROM_2	0x04000000	/* Select पूर्णांकerpolation ROM 2				*/
#घोषणा CCCA_INTERPROM_3	0x06000000	/* Select पूर्णांकerpolation ROM 3				*/
#घोषणा CCCA_INTERPROM_4	0x08000000	/* Select पूर्णांकerpolation ROM 4				*/
#घोषणा CCCA_INTERPROM_5	0x0a000000	/* Select पूर्णांकerpolation ROM 5				*/
#घोषणा CCCA_INTERPROM_6	0x0c000000	/* Select पूर्णांकerpolation ROM 6				*/
#घोषणा CCCA_INTERPROM_7	0x0e000000	/* Select पूर्णांकerpolation ROM 7				*/
#घोषणा CCCA_8BITSELECT		0x01000000	/* 1 = Sound memory क्रम this channel uses 8-bit samples	*/
#घोषणा CCCA_CURRADDR_MASK	0x00ffffff	/* Current address of the selected channel		*/
#घोषणा CCCA_CURRADDR		0x18000008

#घोषणा CCR			0x09		/* Cache control रेजिस्टर				*/
#घोषणा CCR_CACHEINVALIDSIZE	0x07190009
#घोषणा CCR_CACHEINVALIDSIZE_MASK	0xfe000000	/* Number of invalid samples cache क्रम this channel    	*/
#घोषणा CCR_CACHELOOPFLAG	0x01000000	/* 1 = Cache has a loop service pending			*/
#घोषणा CCR_INTERLEAVEDSAMPLES	0x00800000	/* 1 = A cache service will fetch पूर्णांकerleaved samples	*/
#घोषणा CCR_WORDSIZEDSAMPLES	0x00400000	/* 1 = A cache service will fetch word sized samples	*/
#घोषणा CCR_READADDRESS		0x06100009
#घोषणा CCR_READADDRESS_MASK	0x003f0000	/* Location of cache just beyond current cache service	*/
#घोषणा CCR_LOOPINVALSIZE	0x0000fe00	/* Number of invalid samples in cache prior to loop	*/
						/* NOTE: This is valid only अगर CACHELOOPFLAG is set	*/
#घोषणा CCR_LOOPFLAG		0x00000100	/* Set क्रम a single sample period when a loop occurs	*/
#घोषणा CCR_CACHELOOPADDRHI	0x000000ff	/* DSL_LOOPSTARTADDR's hi byte अगर CACHELOOPFLAG is set	*/

#घोषणा CLP			0x0a		/* Cache loop रेजिस्टर (valid अगर CCR_CACHELOOPFLAG = 1) */
						/* NOTE: This रेजिस्टर is normally not used		*/
#घोषणा CLP_CACHELOOPADDR	0x0000ffff	/* Cache loop address (DSL_LOOPSTARTADDR [0..15])	*/

#घोषणा FXRT			0x0b		/* Effects send routing रेजिस्टर			*/
						/* NOTE: It is illegal to assign the same routing to	*/
						/* two effects sends.					*/
#घोषणा FXRT_CHANNELA		0x000f0000	/* Effects send bus number क्रम channel's effects send A	*/
#घोषणा FXRT_CHANNELB		0x00f00000	/* Effects send bus number क्रम channel's effects send B	*/
#घोषणा FXRT_CHANNELC		0x0f000000	/* Effects send bus number क्रम channel's effects send C	*/
#घोषणा FXRT_CHANNELD		0xf0000000	/* Effects send bus number क्रम channel's effects send D	*/

#घोषणा A_HR			0x0b	/* High Resolution. 24bit playback from host to DSP. */
#घोषणा MAPA			0x0c		/* Cache map A						*/

#घोषणा MAPB			0x0d		/* Cache map B						*/

#घोषणा MAP_PTE_MASK0		0xfffff000	/* The 20 MSBs of the PTE indexed by the PTI		*/
#घोषणा MAP_PTI_MASK0		0x00000fff	/* The 12 bit index to one of the 4096 PTE dwords      	*/

#घोषणा MAP_PTE_MASK1		0xffffe000	/* The 19 MSBs of the PTE indexed by the PTI		*/
#घोषणा MAP_PTI_MASK1		0x00001fff	/* The 13 bit index to one of the 8192 PTE dwords      	*/

/* 0x0e, 0x0f: Not used */

#घोषणा ENVVOL			0x10		/* Volume envelope रेजिस्टर				*/
#घोषणा ENVVOL_MASK		0x0000ffff	/* Current value of volume envelope state variable	*/  
						/* 0x8000-n == 666*n usec delay	       			*/

#घोषणा ATKHLDV 		0x11		/* Volume envelope hold and attack रेजिस्टर		*/
#घोषणा ATKHLDV_PHASE0		0x00008000	/* 0 = Begin attack phase				*/
#घोषणा ATKHLDV_HOLDTIME_MASK	0x00007f00	/* Envelope hold समय (127-n == n*88.2msec)		*/
#घोषणा ATKHLDV_ATTACKTIME_MASK	0x0000007f	/* Envelope attack समय, log encoded			*/
						/* 0 = infinite, 1 = 10.9msec, ... 0x7f = 5.5msec	*/

#घोषणा DCYSUSV 		0x12		/* Volume envelope sustain and decay रेजिस्टर		*/
#घोषणा DCYSUSV_PHASE1_MASK	0x00008000	/* 0 = Begin attack phase, 1 = begin release phase	*/
#घोषणा DCYSUSV_SUSTAINLEVEL_MASK 0x00007f00	/* 127 = full, 0 = off, 0.75dB increments		*/
#घोषणा DCYSUSV_CHANNELENABLE_MASK 0x00000080	/* 1 = Inhibit envelope engine from writing values in	*/
						/* this channel and from writing to pitch, filter and	*/
						/* volume tarमाला_लो.					*/
#घोषणा DCYSUSV_DECAYTIME_MASK	0x0000007f	/* Volume envelope decay समय, log encoded     		*/
						/* 0 = 43.7msec, 1 = 21.8msec, 0x7f = 22msec		*/

#घोषणा LFOVAL1 		0x13		/* Modulation LFO value					*/
#घोषणा LFOVAL_MASK		0x0000ffff	/* Current value of modulation LFO state variable	*/
						/* 0x8000-n == 666*n usec delay				*/

#घोषणा ENVVAL			0x14		/* Modulation envelope रेजिस्टर				*/
#घोषणा ENVVAL_MASK		0x0000ffff	/* Current value of modulation envelope state variable 	*/
						/* 0x8000-n == 666*n usec delay				*/

#घोषणा ATKHLDM			0x15		/* Modulation envelope hold and attack रेजिस्टर		*/
#घोषणा ATKHLDM_PHASE0		0x00008000	/* 0 = Begin attack phase				*/
#घोषणा ATKHLDM_HOLDTIME	0x00007f00	/* Envelope hold समय (127-n == n*42msec)		*/
#घोषणा ATKHLDM_ATTACKTIME	0x0000007f	/* Envelope attack समय, log encoded			*/
						/* 0 = infinite, 1 = 11msec, ... 0x7f = 5.5msec		*/

#घोषणा DCYSUSM			0x16		/* Modulation envelope decay and sustain रेजिस्टर	*/
#घोषणा DCYSUSM_PHASE1_MASK	0x00008000	/* 0 = Begin attack phase, 1 = begin release phase	*/
#घोषणा DCYSUSM_SUSTAINLEVEL_MASK 0x00007f00	/* 127 = full, 0 = off, 0.75dB increments		*/
#घोषणा DCYSUSM_DECAYTIME_MASK	0x0000007f	/* Envelope decay समय, log encoded			*/
						/* 0 = 43.7msec, 1 = 21.8msec, 0x7f = 22msec		*/

#घोषणा LFOVAL2 		0x17		/* Vibrato LFO रेजिस्टर					*/
#घोषणा LFOVAL2_MASK		0x0000ffff	/* Current value of vibrato LFO state variable 		*/
						/* 0x8000-n == 666*n usec delay				*/

#घोषणा IP			0x18		/* Initial pitch रेजिस्टर				*/
#घोषणा IP_MASK			0x0000ffff	/* Exponential initial pitch shअगरt			*/
						/* 4 bits of octave, 12 bits of fractional octave	*/
#घोषणा IP_UNITY		0x0000e000	/* Unity pitch shअगरt					*/

#घोषणा IFATN			0x19		/* Initial filter cutoff and attenuation रेजिस्टर	*/
#घोषणा IFATN_FILTERCUTOFF_MASK	0x0000ff00	/* Initial filter cutoff frequency in exponential units	*/
						/* 6 most signअगरicant bits are semitones		*/
						/* 2 least signअगरicant bits are fractions		*/
#घोषणा IFATN_FILTERCUTOFF	0x08080019
#घोषणा IFATN_ATTENUATION_MASK	0x000000ff	/* Initial attenuation in 0.375dB steps			*/
#घोषणा IFATN_ATTENUATION	0x08000019


#घोषणा PEFE			0x1a		/* Pitch envelope and filter envelope amount रेजिस्टर	*/
#घोषणा PEFE_PITCHAMOUNT_MASK	0x0000ff00	/* Pitch envlope amount					*/
						/* Signed 2's complement, +/- one octave peak extremes	*/
#घोषणा PEFE_PITCHAMOUNT	0x0808001a
#घोषणा PEFE_FILTERAMOUNT_MASK	0x000000ff	/* Filter envlope amount				*/
						/* Signed 2's complement, +/- six octaves peak extremes */
#घोषणा PEFE_FILTERAMOUNT	0x0800001a
#घोषणा FMMOD			0x1b		/* Vibrato/filter modulation from LFO रेजिस्टर		*/
#घोषणा FMMOD_MODVIBRATO	0x0000ff00	/* Vibrato LFO modulation depth				*/
						/* Signed 2's complement, +/- one octave extremes	*/
#घोषणा FMMOD_MOFILTER		0x000000ff	/* Filter LFO modulation depth				*/
						/* Signed 2's complement, +/- three octave extremes	*/


#घोषणा TREMFRQ 		0x1c		/* Tremolo amount and modulation LFO frequency रेजिस्टर	*/
#घोषणा TREMFRQ_DEPTH		0x0000ff00	/* Tremolo depth					*/
						/* Signed 2's complement, with +/- 12dB extremes	*/

#घोषणा TREMFRQ_FREQUENCY	0x000000ff	/* Tremolo LFO frequency				*/
						/* ??Hz steps, maximum of ?? Hz.			*/
#घोषणा FM2FRQ2 		0x1d		/* Vibrato amount and vibrato LFO frequency रेजिस्टर	*/
#घोषणा FM2FRQ2_DEPTH		0x0000ff00	/* Vibrato LFO vibrato depth				*/
						/* Signed 2's complement, +/- one octave extremes	*/
#घोषणा FM2FRQ2_FREQUENCY	0x000000ff	/* Vibrato LFO frequency				*/
						/* 0.039Hz steps, maximum of 9.85 Hz.			*/

#घोषणा TEMPENV 		0x1e		/* Tempory envelope रेजिस्टर				*/
#घोषणा TEMPENV_MASK		0x0000ffff	/* 16-bit value						*/
						/* NOTE: All channels contain पूर्णांकernal variables; करो	*/
						/* not ग_लिखो to these locations.			*/

/* 0x1f: not used */

#घोषणा CD0			0x20		/* Cache data 0 रेजिस्टर				*/
#घोषणा CD1			0x21		/* Cache data 1 रेजिस्टर				*/
#घोषणा CD2			0x22		/* Cache data 2 रेजिस्टर				*/
#घोषणा CD3			0x23		/* Cache data 3 रेजिस्टर				*/
#घोषणा CD4			0x24		/* Cache data 4 रेजिस्टर				*/
#घोषणा CD5			0x25		/* Cache data 5 रेजिस्टर				*/
#घोषणा CD6			0x26		/* Cache data 6 रेजिस्टर				*/
#घोषणा CD7			0x27		/* Cache data 7 रेजिस्टर				*/
#घोषणा CD8			0x28		/* Cache data 8 रेजिस्टर				*/
#घोषणा CD9			0x29		/* Cache data 9 रेजिस्टर				*/
#घोषणा CDA			0x2a		/* Cache data A रेजिस्टर				*/
#घोषणा CDB			0x2b		/* Cache data B रेजिस्टर				*/
#घोषणा CDC			0x2c		/* Cache data C रेजिस्टर				*/
#घोषणा CDD			0x2d		/* Cache data D रेजिस्टर				*/
#घोषणा CDE			0x2e		/* Cache data E रेजिस्टर				*/
#घोषणा CDF			0x2f		/* Cache data F रेजिस्टर				*/

/* 0x30-3f seem to be the same as 0x20-2f */

#घोषणा PTB			0x40		/* Page table base रेजिस्टर				*/
#घोषणा PTB_MASK		0xfffff000	/* Physical address of the page table in host memory	*/

#घोषणा TCB			0x41		/* Tank cache base रेजिस्टर    				*/
#घोषणा TCB_MASK		0xfffff000	/* Physical address of the bottom of host based TRAM	*/

#घोषणा ADCCR			0x42		/* ADC sample rate/stereo control रेजिस्टर		*/
#घोषणा ADCCR_RCHANENABLE	0x00000010	/* Enables right channel क्रम writing to the host       	*/
#घोषणा ADCCR_LCHANENABLE	0x00000008	/* Enables left channel क्रम writing to the host		*/
						/* NOTE: To guarantee phase coherency, both channels	*/
						/* must be disabled prior to enabling both channels.	*/
#घोषणा A_ADCCR_RCHANENABLE	0x00000020
#घोषणा A_ADCCR_LCHANENABLE	0x00000010

#घोषणा A_ADCCR_SAMPLERATE_MASK 0x0000000F      /* Audigy sample rate convertor output rate		*/
#घोषणा ADCCR_SAMPLERATE_MASK	0x00000007	/* Sample rate convertor output rate			*/
#घोषणा ADCCR_SAMPLERATE_48	0x00000000	/* 48kHz sample rate					*/
#घोषणा ADCCR_SAMPLERATE_44	0x00000001	/* 44.1kHz sample rate					*/
#घोषणा ADCCR_SAMPLERATE_32	0x00000002	/* 32kHz sample rate					*/
#घोषणा ADCCR_SAMPLERATE_24	0x00000003	/* 24kHz sample rate					*/
#घोषणा ADCCR_SAMPLERATE_22	0x00000004	/* 22.05kHz sample rate					*/
#घोषणा ADCCR_SAMPLERATE_16	0x00000005	/* 16kHz sample rate					*/
#घोषणा ADCCR_SAMPLERATE_11	0x00000006	/* 11.025kHz sample rate				*/
#घोषणा ADCCR_SAMPLERATE_8	0x00000007	/* 8kHz sample rate					*/
#घोषणा A_ADCCR_SAMPLERATE_12	0x00000006	/* 12kHz sample rate					*/
#घोषणा A_ADCCR_SAMPLERATE_11	0x00000007	/* 11.025kHz sample rate				*/
#घोषणा A_ADCCR_SAMPLERATE_8	0x00000008	/* 8kHz sample rate					*/

#घोषणा FXWC			0x43		/* FX output ग_लिखो channels रेजिस्टर			*/
						/* When set, each bit enables the writing of the	*/
						/* corresponding FX output channel (पूर्णांकernal रेजिस्टरs  */
						/* 0x20-0x3f) to host memory.  This mode of recording   */
						/* is 16bit, 48KHz only. All 32 channels can be enabled */
						/* simultaneously.					*/

#घोषणा FXWC_DEFAULTROUTE_C     (1<<0)		/* left emu out? */
#घोषणा FXWC_DEFAULTROUTE_B     (1<<1)		/* right emu out? */
#घोषणा FXWC_DEFAULTROUTE_A     (1<<12)
#घोषणा FXWC_DEFAULTROUTE_D     (1<<13)
#घोषणा FXWC_ADCLEFT            (1<<18)
#घोषणा FXWC_CDROMSPDIFLEFT     (1<<18)
#घोषणा FXWC_ADCRIGHT           (1<<19)
#घोषणा FXWC_CDROMSPDIFRIGHT    (1<<19)
#घोषणा FXWC_MIC                (1<<20)
#घोषणा FXWC_ZOOMLEFT           (1<<20)
#घोषणा FXWC_ZOOMRIGHT          (1<<21)
#घोषणा FXWC_SPDIFLEFT          (1<<22)		/* 0x00400000 */
#घोषणा FXWC_SPDIFRIGHT         (1<<23)		/* 0x00800000 */

#घोषणा A_TBLSZ			0x43	/* Effects Tank Internal Table Size. Only low byte or रेजिस्टर used */

#घोषणा TCBS			0x44		/* Tank cache buffer size रेजिस्टर			*/
#घोषणा TCBS_MASK		0x00000007	/* Tank cache buffer size field				*/
#घोषणा TCBS_BUFFSIZE_16K	0x00000000
#घोषणा TCBS_BUFFSIZE_32K	0x00000001
#घोषणा TCBS_BUFFSIZE_64K	0x00000002
#घोषणा TCBS_BUFFSIZE_128K	0x00000003
#घोषणा TCBS_BUFFSIZE_256K	0x00000004
#घोषणा TCBS_BUFFSIZE_512K	0x00000005
#घोषणा TCBS_BUFFSIZE_1024K	0x00000006
#घोषणा TCBS_BUFFSIZE_2048K	0x00000007

#घोषणा MICBA			0x45		/* AC97 microphone buffer address रेजिस्टर		*/
#घोषणा MICBA_MASK		0xfffff000	/* 20 bit base address					*/

#घोषणा ADCBA			0x46		/* ADC buffer address रेजिस्टर				*/
#घोषणा ADCBA_MASK		0xfffff000	/* 20 bit base address					*/

#घोषणा FXBA			0x47		/* FX Buffer Address */
#घोषणा FXBA_MASK		0xfffff000	/* 20 bit base address					*/

#घोषणा A_HWM			0x48	/* High PCI Water Mark - word access, शेषs to 3f */

#घोषणा MICBS			0x49		/* Microphone buffer size रेजिस्टर			*/

#घोषणा ADCBS			0x4a		/* ADC buffer size रेजिस्टर				*/

#घोषणा FXBS			0x4b		/* FX buffer size रेजिस्टर				*/

/* रेजिस्टर: 0x4c..4f: ffff-ffff current amounts, per-channel */

/* The following mask values define the size of the ADC, MIX and FX buffers in bytes */
#घोषणा ADCBS_बफ_मानE_NONE	0x00000000
#घोषणा ADCBS_बफ_मानE_384	0x00000001
#घोषणा ADCBS_बफ_मानE_448	0x00000002
#घोषणा ADCBS_बफ_मानE_512	0x00000003
#घोषणा ADCBS_बफ_मानE_640	0x00000004
#घोषणा ADCBS_बफ_मानE_768	0x00000005
#घोषणा ADCBS_बफ_मानE_896	0x00000006
#घोषणा ADCBS_बफ_मानE_1024	0x00000007
#घोषणा ADCBS_बफ_मानE_1280	0x00000008
#घोषणा ADCBS_बफ_मानE_1536	0x00000009
#घोषणा ADCBS_बफ_मानE_1792	0x0000000a
#घोषणा ADCBS_बफ_मानE_2048	0x0000000b
#घोषणा ADCBS_बफ_मानE_2560	0x0000000c
#घोषणा ADCBS_बफ_मानE_3072	0x0000000d
#घोषणा ADCBS_बफ_मानE_3584	0x0000000e
#घोषणा ADCBS_बफ_मानE_4096	0x0000000f
#घोषणा ADCBS_बफ_मानE_5120	0x00000010
#घोषणा ADCBS_बफ_मानE_6144	0x00000011
#घोषणा ADCBS_बफ_मानE_7168	0x00000012
#घोषणा ADCBS_बफ_मानE_8192	0x00000013
#घोषणा ADCBS_बफ_मानE_10240	0x00000014
#घोषणा ADCBS_बफ_मानE_12288	0x00000015
#घोषणा ADCBS_बफ_मानE_14366	0x00000016
#घोषणा ADCBS_बफ_मानE_16384	0x00000017
#घोषणा ADCBS_बफ_मानE_20480	0x00000018
#घोषणा ADCBS_बफ_मानE_24576	0x00000019
#घोषणा ADCBS_बफ_मानE_28672	0x0000001a
#घोषणा ADCBS_बफ_मानE_32768	0x0000001b
#घोषणा ADCBS_बफ_मानE_40960	0x0000001c
#घोषणा ADCBS_बफ_मानE_49152	0x0000001d
#घोषणा ADCBS_बफ_मानE_57344	0x0000001e
#घोषणा ADCBS_बफ_मानE_65536	0x0000001f

/* Current Send B, A Amounts */
#घोषणा A_CSBA			0x4c

/* Current Send D, C Amounts */
#घोषणा A_CSDC			0x4d

/* Current Send F, E Amounts */
#घोषणा A_CSFE			0x4e

/* Current Send H, G Amounts */
#घोषणा A_CSHG			0x4f


#घोषणा CDCS			0x50		/* CD-ROM digital channel status रेजिस्टर	*/

#घोषणा GPSCS			0x51		/* General Purpose SPDIF channel status रेजिस्टर*/

#घोषणा DBG			0x52		/* DO NOT PROGRAM THIS REGISTER!!! MAY DESTROY CHIP */

/* S/PDIF Input C Channel Status */
#घोषणा A_SPSC			0x52

#घोषणा REG53			0x53		/* DO NOT PROGRAM THIS REGISTER!!! MAY DESTROY CHIP */

#घोषणा A_DBG			 0x53
#घोषणा A_DBG_SINGLE_STEP	 0x00020000	/* Set to zero to start dsp */
#घोषणा A_DBG_ZC		 0x40000000	/* zero tram counter */
#घोषणा A_DBG_STEP_ADDR		 0x000003ff
#घोषणा A_DBG_SATURATION_OCCURED 0x20000000
#घोषणा A_DBG_SATURATION_ADDR	 0x0ffc0000

// NOTE: 0x54,55,56: 64-bit
#घोषणा SPCS0			0x54		/* SPDIF output Channel Status 0 रेजिस्टर	*/

#घोषणा SPCS1			0x55		/* SPDIF output Channel Status 1 रेजिस्टर	*/

#घोषणा SPCS2			0x56		/* SPDIF output Channel Status 2 रेजिस्टर	*/

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

/* 0x57: Not used */

/* The 32-bit CLIx and SOLx रेजिस्टरs all have one bit per channel control/status      		*/
#घोषणा CLIEL			0x58		/* Channel loop पूर्णांकerrupt enable low रेजिस्टर	*/

#घोषणा CLIEH			0x59		/* Channel loop पूर्णांकerrupt enable high रेजिस्टर	*/

#घोषणा CLIPL			0x5a		/* Channel loop पूर्णांकerrupt pending low रेजिस्टर	*/

#घोषणा CLIPH			0x5b		/* Channel loop पूर्णांकerrupt pending high रेजिस्टर	*/

#घोषणा SOLEL			0x5c		/* Stop on loop enable low रेजिस्टर		*/

#घोषणा SOLEH			0x5d		/* Stop on loop enable high रेजिस्टर		*/

#घोषणा SPBYPASS		0x5e		/* SPDIF BYPASS mode रेजिस्टर			*/
#घोषणा SPBYPASS_SPDIF0_MASK	0x00000003	/* SPDIF 0 bypass mode				*/
#घोषणा SPBYPASS_SPDIF1_MASK	0x0000000c	/* SPDIF 1 bypass mode				*/
/* bypass mode: 0 - DSP; 1 - SPDIF A, 2 - SPDIF B, 3 - SPDIF C					*/
#घोषणा SPBYPASS_FORMAT		0x00000f00      /* If 1, SPDIF XX uses 24 bit, अगर 0 - 20 bit	*/

#घोषणा AC97SLOT		0x5f            /* additional AC97 slots enable bits		*/
#घोषणा AC97SLOT_REAR_RIGHT	0x01		/* Rear left */
#घोषणा AC97SLOT_REAR_LEFT	0x02		/* Rear right */
#घोषणा AC97SLOT_CNTR		0x10            /* Center enable */
#घोषणा AC97SLOT_LFE		0x20            /* LFE enable */

/* PCB Revision */
#घोषणा A_PCB			0x5f

// NOTE: 0x60,61,62: 64-bit
#घोषणा CDSRCS			0x60		/* CD-ROM Sample Rate Converter status रेजिस्टर	*/

#घोषणा GPSRCS			0x61		/* General Purpose SPDIF sample rate cvt status */

#घोषणा ZVSRCS			0x62		/* ZVideo sample rate converter status		*/
						/* NOTE: This one has no SPDIFLOCKED field	*/
						/* Assumes sample lock				*/

/* These three bitfields apply to CDSRCS, GPSRCS, and (except as noted) ZVSRCS.			*/
#घोषणा SRCS_SPDIFVALID		0x04000000	/* SPDIF stream valid				*/
#घोषणा SRCS_SPDIFLOCKED	0x02000000	/* SPDIF stream locked				*/
#घोषणा SRCS_RATELOCKED		0x01000000	/* Sample rate locked				*/
#घोषणा SRCS_ESTSAMPLERATE	0x0007ffff	/* Do not modअगरy this field.			*/

/* Note that these values can vary +/- by a small amount                                        */
#घोषणा SRCS_SPDIFRATE_44	0x0003acd9
#घोषणा SRCS_SPDIFRATE_48	0x00040000
#घोषणा SRCS_SPDIFRATE_96	0x00080000

#घोषणा MICIDX                  0x63            /* Microphone recording buffer index रेजिस्टर   */
#घोषणा MICIDX_MASK             0x0000ffff      /* 16-bit value                                 */
#घोषणा MICIDX_IDX		0x10000063

#घोषणा ADCIDX			0x64		/* ADC recording buffer index रेजिस्टर		*/
#घोषणा ADCIDX_MASK		0x0000ffff	/* 16 bit index field				*/
#घोषणा ADCIDX_IDX		0x10000064

#घोषणा A_ADCIDX		0x63
#घोषणा A_ADCIDX_IDX		0x10000063

#घोषणा A_MICIDX		0x64
#घोषणा A_MICIDX_IDX		0x10000064

#घोषणा FXIDX			0x65		/* FX recording buffer index रेजिस्टर		*/
#घोषणा FXIDX_MASK		0x0000ffff	/* 16-bit value					*/
#घोषणा FXIDX_IDX		0x10000065

/* The 32-bit HLIx and HLIPx रेजिस्टरs all have one bit per channel control/status      		*/
#घोषणा HLIEL			0x66		/* Channel half loop पूर्णांकerrupt enable low रेजिस्टर	*/

#घोषणा HLIEH			0x67		/* Channel half loop पूर्णांकerrupt enable high रेजिस्टर	*/

#घोषणा HLIPL			0x68		/* Channel half loop पूर्णांकerrupt pending low रेजिस्टर	*/

#घोषणा HLIPH			0x69		/* Channel half loop पूर्णांकerrupt pending high रेजिस्टर	*/

/* S/PDIF Host Record Index (bypasses SRC) */
#घोषणा A_SPRI			0x6a
/* S/PDIF Host Record Address */
#घोषणा A_SPRA			0x6b
/* S/PDIF Host Record Control */
#घोषणा A_SPRC			0x6c
/* Delayed Interrupt Counter & Enable */
#घोषणा A_DICE			0x6d
/* Tank Table Base */
#घोषणा A_TTB			0x6e
/* Tank Delay Offset */
#घोषणा A_TDOF			0x6f

/* This is the MPU port on the card (via the game port)						*/
#घोषणा A_MUDATA1		0x70
#घोषणा A_MUCMD1		0x71
#घोषणा A_MUSTAT1		A_MUCMD1

/* This is the MPU port on the Audigy Drive 							*/
#घोषणा A_MUDATA2		0x72
#घोषणा A_MUCMD2		0x73
#घोषणा A_MUSTAT2		A_MUCMD2	

/* The next two are the Audigy equivalent of FXWC						*/
/* the Audigy can record any output (16bit, 48kHz, up to 64 channel simultaneously) 		*/
/* Each bit selects a channel क्रम recording */
#घोषणा A_FXWC1			0x74            /* Selects 0x7f-0x60 क्रम FX recording           */
#घोषणा A_FXWC2			0x75		/* Selects 0x9f-0x80 क्रम FX recording           */

/* Extended Hardware Control */
#घोषणा A_SPDIF_SAMPLERATE	0x76		/* Set the sample rate of SPDIF output		*/
#घोषणा A_SAMPLE_RATE		0x76		/* Various sample rate settings. */
#घोषणा A_SAMPLE_RATE_NOT_USED  0x0ffc111e	/* Bits that are not used and cannot be set. 	*/
#घोषणा A_SAMPLE_RATE_UNKNOWN	0xf0030001	/* Bits that can be set, but have unknown use. 	*/
#घोषणा A_SPDIF_RATE_MASK	0x000000e0	/* Any other values क्रम rates, just use 48000	*/
#घोषणा A_SPDIF_48000		0x00000000
#घोषणा A_SPDIF_192000		0x00000020
#घोषणा A_SPDIF_96000		0x00000040
#घोषणा A_SPDIF_44100		0x00000080

#घोषणा A_I2S_CAPTURE_RATE_MASK	0x00000e00	/* This sets the capture PCM rate, but it is    */
#घोषणा A_I2S_CAPTURE_48000	0x00000000	/* unclear अगर this sets the ADC rate as well.	*/
#घोषणा A_I2S_CAPTURE_192000	0x00000200
#घोषणा A_I2S_CAPTURE_96000	0x00000400
#घोषणा A_I2S_CAPTURE_44100	0x00000800

#घोषणा A_PCM_RATE_MASK		0x0000e000	/* This sets the playback PCM rate on the P16V	*/
#घोषणा A_PCM_48000		0x00000000
#घोषणा A_PCM_192000		0x00002000
#घोषणा A_PCM_96000		0x00004000
#घोषणा A_PCM_44100		0x00008000

/* I2S0 Sample Rate Tracker Status */
#घोषणा A_SRT3			0x77

/* I2S1 Sample Rate Tracker Status */
#घोषणा A_SRT4			0x78

/* I2S2 Sample Rate Tracker Status */
#घोषणा A_SRT5			0x79
/* - शेष to 0x01080000 on my audigy 2 ZS --rlrevell	*/

/* Tank Table DMA Address */
#घोषणा A_TTDA			0x7a
/* Tank Table DMA Data */
#घोषणा A_TTDD			0x7b

#घोषणा A_FXRT2			0x7c
#घोषणा A_FXRT_CHANNELE		0x0000003f	/* Effects send bus number क्रम channel's effects send E	*/
#घोषणा A_FXRT_CHANNELF		0x00003f00	/* Effects send bus number क्रम channel's effects send F	*/
#घोषणा A_FXRT_CHANNELG		0x003f0000	/* Effects send bus number क्रम channel's effects send G	*/
#घोषणा A_FXRT_CHANNELH		0x3f000000	/* Effects send bus number क्रम channel's effects send H	*/

#घोषणा A_SENDAMOUNTS		0x7d
#घोषणा A_FXSENDAMOUNT_E_MASK	0xFF000000
#घोषणा A_FXSENDAMOUNT_F_MASK	0x00FF0000
#घोषणा A_FXSENDAMOUNT_G_MASK	0x0000FF00
#घोषणा A_FXSENDAMOUNT_H_MASK	0x000000FF
/* 0x7c, 0x7e "high bit is used for filtering" */
 
/* The send amounts क्रम this one are the same as used with the emu10k1 */
#घोषणा A_FXRT1			0x7e
#घोषणा A_FXRT_CHANNELA		0x0000003f
#घोषणा A_FXRT_CHANNELB		0x00003f00
#घोषणा A_FXRT_CHANNELC		0x003f0000
#घोषणा A_FXRT_CHANNELD		0x3f000000

/* 0x7f: Not used */
/* Each FX general purpose रेजिस्टर is 32 bits in length, all bits are used			*/
#घोषणा FXGPREGBASE		0x100		/* FX general purpose रेजिस्टरs base       	*/
#घोषणा A_FXGPREGBASE		0x400		/* Audigy GPRs, 0x400 to 0x5ff			*/

#घोषणा A_TANKMEMCTLREGBASE	0x100		/* Tank memory control रेजिस्टरs base - only क्रम Audigy */
#घोषणा A_TANKMEMCTLREG_MASK	0x1f		/* only 5 bits used - only क्रम Audigy */

/* Tank audio data is logarithmically compressed करोwn to 16 bits beक्रमe writing to TRAM and is	*/
/* decompressed back to 20 bits on a पढ़ो.  There are a total of 160 locations, the last 32	*/
/* locations are क्रम बाह्यal TRAM. 								*/
#घोषणा TANKMEMDATAREGBASE	0x200		/* Tank memory data रेजिस्टरs base     		*/
#घोषणा TANKMEMDATAREG_MASK	0x000fffff	/* 20 bit tank audio data field			*/

/* Combined address field and memory opcode or flag field.  160 locations, last 32 are बाह्यal	*/
#घोषणा TANKMEMADDRREGBASE	0x300		/* Tank memory address रेजिस्टरs base		*/
#घोषणा TANKMEMADDRREG_ADDR_MASK 0x000fffff	/* 20 bit tank address field			*/
#घोषणा TANKMEMADDRREG_CLEAR	0x00800000	/* Clear tank memory				*/
#घोषणा TANKMEMADDRREG_ALIGN	0x00400000	/* Align पढ़ो or ग_लिखो relative to tank access	*/
#घोषणा TANKMEMADDRREG_WRITE	0x00200000	/* Write to tank memory				*/
#घोषणा TANKMEMADDRREG_READ	0x00100000	/* Read from tank memory			*/

#घोषणा MICROCODEBASE		0x400		/* Microcode data base address			*/

/* Each DSP microcode inकाष्ठाion is mapped पूर्णांकo 2 द्विगुनwords 					*/
/* NOTE: When writing, always ग_लिखो the LO द्विगुनword first.  Reads can be in either order.	*/
#घोषणा LOWORD_OPX_MASK		0x000ffc00	/* Inकाष्ठाion opeअक्रम X			*/
#घोषणा LOWORD_OPY_MASK		0x000003ff	/* Inकाष्ठाion opeअक्रम Y			*/
#घोषणा HIWORD_OPCODE_MASK	0x00f00000	/* Inकाष्ठाion opcode				*/
#घोषणा HIWORD_RESULT_MASK	0x000ffc00	/* Inकाष्ठाion result				*/
#घोषणा HIWORD_OPA_MASK		0x000003ff	/* Inकाष्ठाion opeअक्रम A			*/


/* Audigy Soundcard have a dअगरferent inकाष्ठाion क्रमmat */
#घोषणा A_MICROCODEBASE		0x600
#घोषणा A_LOWORD_OPY_MASK	0x000007ff
#घोषणा A_LOWORD_OPX_MASK	0x007ff000
#घोषणा A_HIWORD_OPCODE_MASK	0x0f000000
#घोषणा A_HIWORD_RESULT_MASK	0x007ff000
#घोषणा A_HIWORD_OPA_MASK	0x000007ff

/************************************************************************************************/
/* EMU1010m HANA FPGA रेजिस्टरs									*/
/************************************************************************************************/
#घोषणा EMU_HANA_DESTHI		0x00	/* 0000xxx  3 bits Link Destination */
#घोषणा EMU_HANA_DESTLO		0x01	/* 00xxxxx  5 bits */
#घोषणा EMU_HANA_SRCHI		0x02	/* 0000xxx  3 bits Link Source */
#घोषणा EMU_HANA_SRCLO		0x03	/* 00xxxxx  5 bits */
#घोषणा EMU_HANA_DOCK_PWR	0x04	/* 000000x  1 bits Audio Dock घातer */
#घोषणा EMU_HANA_DOCK_PWR_ON		0x01 /* Audio Dock घातer on */
#घोषणा EMU_HANA_WCLOCK		0x05	/* 0000xxx  3 bits Word Clock source select  */
					/* Must be written after घातer on to reset DLL */
					/* One is unable to detect the Audio करोck without this */
#घोषणा EMU_HANA_WCLOCK_SRC_MASK	0x07
#घोषणा EMU_HANA_WCLOCK_INT_48K		0x00
#घोषणा EMU_HANA_WCLOCK_INT_44_1K	0x01
#घोषणा EMU_HANA_WCLOCK_HANA_SPDIF_IN	0x02
#घोषणा EMU_HANA_WCLOCK_HANA_ADAT_IN	0x03
#घोषणा EMU_HANA_WCLOCK_SYNC_BNCN	0x04
#घोषणा EMU_HANA_WCLOCK_2ND_HANA	0x05
#घोषणा EMU_HANA_WCLOCK_SRC_RESERVED	0x06
#घोषणा EMU_HANA_WCLOCK_OFF		0x07 /* For testing, क्रमces fallback to DEFCLOCK */
#घोषणा EMU_HANA_WCLOCK_MULT_MASK	0x18
#घोषणा EMU_HANA_WCLOCK_1X		0x00
#घोषणा EMU_HANA_WCLOCK_2X		0x08
#घोषणा EMU_HANA_WCLOCK_4X		0x10
#घोषणा EMU_HANA_WCLOCK_MULT_RESERVED	0x18

#घोषणा EMU_HANA_DEFCLOCK	0x06	/* 000000x  1 bits Default Word Clock  */
#घोषणा EMU_HANA_DEFCLOCK_48K		0x00
#घोषणा EMU_HANA_DEFCLOCK_44_1K		0x01

#घोषणा EMU_HANA_UNMUTE		0x07	/* 000000x  1 bits Mute all audio outमाला_दो  */
#घोषणा EMU_MUTE			0x00
#घोषणा EMU_UNMUTE			0x01

#घोषणा EMU_HANA_FPGA_CONFIG	0x08	/* 00000xx  2 bits Config control of FPGAs  */
#घोषणा EMU_HANA_FPGA_CONFIG_AUDIODOCK	0x01 /* Set in order to program FPGA on Audio Dock */
#घोषणा EMU_HANA_FPGA_CONFIG_HANA	0x02 /* Set in order to program FPGA on Hana */

#घोषणा EMU_HANA_IRQ_ENABLE	0x09	/* 000xxxx  4 bits IRQ Enable  */
#घोषणा EMU_HANA_IRQ_WCLK_CHANGED	0x01
#घोषणा EMU_HANA_IRQ_ADAT		0x02
#घोषणा EMU_HANA_IRQ_DOCK		0x04
#घोषणा EMU_HANA_IRQ_DOCK_LOST		0x08

#घोषणा EMU_HANA_SPDIF_MODE	0x0a	/* 00xxxxx  5 bits SPDIF MODE  */
#घोषणा EMU_HANA_SPDIF_MODE_TX_COMSUMER	0x00
#घोषणा EMU_HANA_SPDIF_MODE_TX_PRO	0x01
#घोषणा EMU_HANA_SPDIF_MODE_TX_NOCOPY	0x02
#घोषणा EMU_HANA_SPDIF_MODE_RX_COMSUMER	0x00
#घोषणा EMU_HANA_SPDIF_MODE_RX_PRO	0x04
#घोषणा EMU_HANA_SPDIF_MODE_RX_NOCOPY	0x08
#घोषणा EMU_HANA_SPDIF_MODE_RX_INVALID	0x10

#घोषणा EMU_HANA_OPTICAL_TYPE	0x0b	/* 00000xx  2 bits ADAT or SPDIF in/out  */
#घोषणा EMU_HANA_OPTICAL_IN_SPDIF	0x00
#घोषणा EMU_HANA_OPTICAL_IN_ADAT	0x01
#घोषणा EMU_HANA_OPTICAL_OUT_SPDIF	0x00
#घोषणा EMU_HANA_OPTICAL_OUT_ADAT	0x02

#घोषणा EMU_HANA_MIDI_IN		0x0c	/* 000000x  1 bit  Control MIDI  */
#घोषणा EMU_HANA_MIDI_IN_FROM_HAMOA	0x00 /* HAMOA MIDI in to Alice 2 MIDI B */
#घोषणा EMU_HANA_MIDI_IN_FROM_DOCK	0x01 /* Audio Dock MIDI in to Alice 2 MIDI B */

#घोषणा EMU_HANA_DOCK_LEDS_1	0x0d	/* 000xxxx  4 bit  Audio Dock LEDs  */
#घोषणा EMU_HANA_DOCK_LEDS_1_MIDI1	0x01	/* MIDI 1 LED on */
#घोषणा EMU_HANA_DOCK_LEDS_1_MIDI2	0x02	/* MIDI 2 LED on */
#घोषणा EMU_HANA_DOCK_LEDS_1_SMPTE_IN	0x04	/* SMPTE IN LED on */
#घोषणा EMU_HANA_DOCK_LEDS_1_SMPTE_OUT	0x08	/* SMPTE OUT LED on */

#घोषणा EMU_HANA_DOCK_LEDS_2	0x0e	/* 0xxxxxx  6 bit  Audio Dock LEDs  */
#घोषणा EMU_HANA_DOCK_LEDS_2_44K	0x01	/* 44.1 kHz LED on */
#घोषणा EMU_HANA_DOCK_LEDS_2_48K	0x02	/* 48 kHz LED on */
#घोषणा EMU_HANA_DOCK_LEDS_2_96K	0x04	/* 96 kHz LED on */
#घोषणा EMU_HANA_DOCK_LEDS_2_192K	0x08	/* 192 kHz LED on */
#घोषणा EMU_HANA_DOCK_LEDS_2_LOCK	0x10	/* LOCK LED on */
#घोषणा EMU_HANA_DOCK_LEDS_2_EXT	0x20	/* EXT LED on */

#घोषणा EMU_HANA_DOCK_LEDS_3	0x0f	/* 0xxxxxx  6 bit  Audio Dock LEDs  */
#घोषणा EMU_HANA_DOCK_LEDS_3_CLIP_A	0x01	/* Mic A Clip LED on */
#घोषणा EMU_HANA_DOCK_LEDS_3_CLIP_B	0x02	/* Mic B Clip LED on */
#घोषणा EMU_HANA_DOCK_LEDS_3_SIGNAL_A	0x04	/* Signal A Clip LED on */
#घोषणा EMU_HANA_DOCK_LEDS_3_SIGNAL_B	0x08	/* Signal B Clip LED on */
#घोषणा EMU_HANA_DOCK_LEDS_3_MANUAL_CLIP	0x10	/* Manual Clip detection */
#घोषणा EMU_HANA_DOCK_LEDS_3_MANUAL_SIGNAL	0x20	/* Manual Signal detection */

#घोषणा EMU_HANA_ADC_PADS	0x10	/* 0000xxx  3 bit  Audio Dock ADC 14dB pads */
#घोषणा EMU_HANA_DOCK_ADC_PAD1	0x01	/* 14dB Attenuation on Audio Dock ADC 1 */
#घोषणा EMU_HANA_DOCK_ADC_PAD2	0x02	/* 14dB Attenuation on Audio Dock ADC 2 */
#घोषणा EMU_HANA_DOCK_ADC_PAD3	0x04	/* 14dB Attenuation on Audio Dock ADC 3 */
#घोषणा EMU_HANA_0202_ADC_PAD1	0x08	/* 14dB Attenuation on 0202 ADC 1 */

#घोषणा EMU_HANA_DOCK_MISC	0x11	/* 0xxxxxx  6 bit  Audio Dock misc bits */
#घोषणा EMU_HANA_DOCK_DAC1_MUTE	0x01	/* DAC 1 Mute */
#घोषणा EMU_HANA_DOCK_DAC2_MUTE	0x02	/* DAC 2 Mute */
#घोषणा EMU_HANA_DOCK_DAC3_MUTE	0x04	/* DAC 3 Mute */
#घोषणा EMU_HANA_DOCK_DAC4_MUTE	0x08	/* DAC 4 Mute */
#घोषणा EMU_HANA_DOCK_PHONES_192_DAC1	0x00	/* DAC 1 Headphones source at 192kHz */
#घोषणा EMU_HANA_DOCK_PHONES_192_DAC2	0x10	/* DAC 2 Headphones source at 192kHz */
#घोषणा EMU_HANA_DOCK_PHONES_192_DAC3	0x20	/* DAC 3 Headphones source at 192kHz */
#घोषणा EMU_HANA_DOCK_PHONES_192_DAC4	0x30	/* DAC 4 Headphones source at 192kHz */

#घोषणा EMU_HANA_MIDI_OUT	0x12	/* 00xxxxx  5 bit  Source क्रम each MIDI out port */
#घोषणा EMU_HANA_MIDI_OUT_0202	0x01 /* 0202 MIDI from Alice 2. 0 = A, 1 = B */
#घोषणा EMU_HANA_MIDI_OUT_DOCK1	0x02 /* Audio Dock MIDI1 front, from Alice 2. 0 = A, 1 = B */
#घोषणा EMU_HANA_MIDI_OUT_DOCK2	0x04 /* Audio Dock MIDI2 rear, from Alice 2. 0 = A, 1 = B */
#घोषणा EMU_HANA_MIDI_OUT_SYNC2	0x08 /* Sync card. Not the actual MIDI out jack. 0 = A, 1 = B */
#घोषणा EMU_HANA_MIDI_OUT_LOOP	0x10 /* 0 = bits (3:0) normal. 1 = MIDI loopback enabled. */

#घोषणा EMU_HANA_DAC_PADS	0x13	/* 00xxxxx  5 bit  DAC 14dB attenuation pads */
#घोषणा EMU_HANA_DOCK_DAC_PAD1	0x01	/* 14dB Attenuation on AudioDock DAC 1. Left and Right */
#घोषणा EMU_HANA_DOCK_DAC_PAD2	0x02	/* 14dB Attenuation on AudioDock DAC 2. Left and Right */
#घोषणा EMU_HANA_DOCK_DAC_PAD3	0x04	/* 14dB Attenuation on AudioDock DAC 3. Left and Right */
#घोषणा EMU_HANA_DOCK_DAC_PAD4	0x08	/* 14dB Attenuation on AudioDock DAC 4. Left and Right */
#घोषणा EMU_HANA_0202_DAC_PAD1	0x10	/* 14dB Attenuation on 0202 DAC 1. Left and Right */

/* 0x14 - 0x1f Unused R/W रेजिस्टरs */
#घोषणा EMU_HANA_IRQ_STATUS	0x20	/* 000xxxx  4 bits IRQ Status  */
#अगर 0  /* Alपढ़ोy defined क्रम reg 0x09 IRQ_ENABLE */
#घोषणा EMU_HANA_IRQ_WCLK_CHANGED	0x01
#घोषणा EMU_HANA_IRQ_ADAT		0x02
#घोषणा EMU_HANA_IRQ_DOCK		0x04
#घोषणा EMU_HANA_IRQ_DOCK_LOST		0x08
#पूर्ण_अगर

#घोषणा EMU_HANA_OPTION_CARDS	0x21	/* 000xxxx  4 bits Presence of option cards */
#घोषणा EMU_HANA_OPTION_HAMOA	0x01	/* HAMOA card present */
#घोषणा EMU_HANA_OPTION_SYNC	0x02	/* Sync card present */
#घोषणा EMU_HANA_OPTION_DOCK_ONLINE	0x04	/* Audio Dock online and FPGA configured */
#घोषणा EMU_HANA_OPTION_DOCK_OFFLINE	0x08	/* Audio Dock online and FPGA not configured */

#घोषणा EMU_HANA_ID		0x22	/* 1010101  7 bits ID byte & 0x7f = 0x55 */

#घोषणा EMU_HANA_MAJOR_REV	0x23	/* 0000xxx  3 bit  Hana FPGA Major rev */
#घोषणा EMU_HANA_MINOR_REV	0x24	/* 0000xxx  3 bit  Hana FPGA Minor rev */

#घोषणा EMU_DOCK_MAJOR_REV	0x25	/* 0000xxx  3 bit  Audio Dock FPGA Major rev */
#घोषणा EMU_DOCK_MINOR_REV	0x26	/* 0000xxx  3 bit  Audio Dock FPGA Minor rev */

#घोषणा EMU_DOCK_BOARD_ID	0x27	/* 00000xx  2 bits Audio Dock ID pins */
#घोषणा EMU_DOCK_BOARD_ID0	0x00	/* ID bit 0 */
#घोषणा EMU_DOCK_BOARD_ID1	0x03	/* ID bit 1 */

#घोषणा EMU_HANA_WC_SPDIF_HI	0x28	/* 0xxxxxx  6 bit  SPDIF IN Word घड़ी, upper 6 bits */
#घोषणा EMU_HANA_WC_SPDIF_LO	0x29	/* 0xxxxxx  6 bit  SPDIF IN Word घड़ी, lower 6 bits */

#घोषणा EMU_HANA_WC_ADAT_HI	0x2a	/* 0xxxxxx  6 bit  ADAT IN Word घड़ी, upper 6 bits */
#घोषणा EMU_HANA_WC_ADAT_LO	0x2b	/* 0xxxxxx  6 bit  ADAT IN Word घड़ी, lower 6 bits */

#घोषणा EMU_HANA_WC_BNC_LO	0x2c	/* 0xxxxxx  6 bit  BNC IN Word घड़ी, lower 6 bits */
#घोषणा EMU_HANA_WC_BNC_HI	0x2d	/* 0xxxxxx  6 bit  BNC IN Word घड़ी, upper 6 bits */

#घोषणा EMU_HANA2_WC_SPDIF_HI	0x2e	/* 0xxxxxx  6 bit  HANA2 SPDIF IN Word घड़ी, upper 6 bits */
#घोषणा EMU_HANA2_WC_SPDIF_LO	0x2f	/* 0xxxxxx  6 bit  HANA2 SPDIF IN Word घड़ी, lower 6 bits */
/* 0x30 - 0x3f Unused Read only रेजिस्टरs */

/************************************************************************************************/
/* EMU1010m HANA Destinations									*/
/************************************************************************************************/
/* Hana, original 1010,1212,1820 using Alice2
 * Destiniations क्रम SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00, 0x00-0x0f: 16 EMU32 channels to Alice2
 * 0x01, 0x10-0x1f: 32 Elink channels to Audio Dock
 * 0x01, 0x00: Dock DAC 1 Left
 * 0x01, 0x04: Dock DAC 1 Right
 * 0x01, 0x08: Dock DAC 2 Left
 * 0x01, 0x0c: Dock DAC 2 Right
 * 0x01, 0x10: Dock DAC 3 Left
 * 0x01, 0x12: PHONES Left
 * 0x01, 0x14: Dock DAC 3 Right
 * 0x01, 0x16: PHONES Right
 * 0x01, 0x18: Dock DAC 4 Left
 * 0x01, 0x1a: S/PDIF Left
 * 0x01, 0x1c: Dock DAC 4 Right
 * 0x01, 0x1e: S/PDIF Right
 * 0x02, 0x00: Hana S/PDIF Left
 * 0x02, 0x01: Hana S/PDIF Right
 * 0x03, 0x00: Hanoa DAC Left
 * 0x03, 0x01: Hanoa DAC Right
 * 0x04, 0x00-0x07: Hana ADAT
 * 0x05, 0x00: I2S0 Left to Alice2
 * 0x05, 0x01: I2S0 Right to Alice2
 * 0x06, 0x00: I2S0 Left to Alice2
 * 0x06, 0x01: I2S0 Right to Alice2
 * 0x07, 0x00: I2S0 Left to Alice2
 * 0x07, 0x01: I2S0 Right to Alice2
 *
 * Hana2 never released, but used Tina
 * Not needed.
 *
 * Hana3, rev2 1010,1212,1616 using Tina
 * Destinations क्रम SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00, 0x00-0x0f: 16 EMU32A channels to Tina
 * 0x01, 0x10-0x1f: 32 EDI channels to Micro Dock
 * 0x01, 0x00: Dock DAC 1 Left
 * 0x01, 0x04: Dock DAC 1 Right
 * 0x01, 0x08: Dock DAC 2 Left
 * 0x01, 0x0c: Dock DAC 2 Right
 * 0x01, 0x10: Dock DAC 3 Left
 * 0x01, 0x12: Dock S/PDIF Left
 * 0x01, 0x14: Dock DAC 3 Right
 * 0x01, 0x16: Dock S/PDIF Right
 * 0x01, 0x18-0x1f: Dock ADAT 0-7
 * 0x02, 0x00: Hana3 S/PDIF Left
 * 0x02, 0x01: Hana3 S/PDIF Right
 * 0x03, 0x00: Hanoa DAC Left
 * 0x03, 0x01: Hanoa DAC Right
 * 0x04, 0x00-0x07: Hana3 ADAT 0-7
 * 0x05, 0x00-0x0f: 16 EMU32B channels to Tina
 * 0x06-0x07: Not used
 *
 * HanaLite, rev1 0404 using Alice2
 * Destiniations क्रम SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00, 0x00-0x0f: 16 EMU32 channels to Alice2
 * 0x01: Not used
 * 0x02, 0x00: S/PDIF Left
 * 0x02, 0x01: S/PDIF Right
 * 0x03, 0x00: DAC Left
 * 0x03, 0x01: DAC Right
 * 0x04-0x07: Not used
 *
 * HanaLiteLite, rev2 0404 using Alice2
 * Destiniations क्रम SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00, 0x00-0x0f: 16 EMU32 channels to Alice2
 * 0x01: Not used
 * 0x02, 0x00: S/PDIF Left
 * 0x02, 0x01: S/PDIF Right
 * 0x03, 0x00: DAC Left
 * 0x03, 0x01: DAC Right
 * 0x04-0x07: Not used
 *
 * Mana, Cardbus 1616 using Tina2
 * Destinations क्रम SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00, 0x00-0x0f: 16 EMU32A channels to Tina2
 * 0x01, 0x10-0x1f: 32 EDI channels to Micro Dock
 * 0x01, 0x00: Dock DAC 1 Left
 * 0x01, 0x04: Dock DAC 1 Right
 * 0x01, 0x08: Dock DAC 2 Left
 * 0x01, 0x0c: Dock DAC 2 Right
 * 0x01, 0x10: Dock DAC 3 Left
 * 0x01, 0x12: Dock S/PDIF Left
 * 0x01, 0x14: Dock DAC 3 Right
 * 0x01, 0x16: Dock S/PDIF Right
 * 0x01, 0x18-0x1f: Dock ADAT 0-7
 * 0x02: Not used
 * 0x03, 0x00: Mana DAC Left
 * 0x03, 0x01: Mana DAC Right
 * 0x04, 0x00-0x0f: 16 EMU32B channels to Tina2
 * 0x05-0x07: Not used
 *
 *
 */
/* 32-bit destinations of संकेत in the Hana FPGA. Destinations are either
 * physical outमाला_दो of Hana, or outमाला_दो going to Alice2 (audigy) क्रम capture
 * - 16 x EMU_DST_ALICE2_EMU32_X.
 */
/* EMU32 = 32-bit serial channel between Alice2 (audigy) and Hana (FPGA) */
/* EMU_DST_ALICE2_EMU32_X - data channels from Hana to Alice2 used क्रम capture.
 * Which data is fed पूर्णांकo a EMU_DST_ALICE2_EMU32_X channel in Hana depends on
 * setup of mixer control क्रम each destination - see emumixer.c -
 * snd_emu1010_output_क्रमागत_ctls[], snd_emu1010_input_क्रमागत_ctls[]
 */
#घोषणा EMU_DST_ALICE2_EMU32_0	0x000f	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_1	0x0000	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_2	0x0001	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_3	0x0002	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_4	0x0003	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_5	0x0004	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_6	0x0005	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_7	0x0006	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_8	0x0007	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_9	0x0008	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_A	0x0009	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_B	0x000a	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_C	0x000b	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_D	0x000c	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_E	0x000d	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_ALICE2_EMU32_F	0x000e	/* 16 EMU32 channels to Alice2 +0 to +0xf */
#घोषणा EMU_DST_DOCK_DAC1_LEFT1	0x0100	/* Audio Dock DAC1 Left, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC1_LEFT2	0x0101	/* Audio Dock DAC1 Left, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC1_LEFT3	0x0102	/* Audio Dock DAC1 Left, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC1_LEFT4	0x0103	/* Audio Dock DAC1 Left, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_DAC1_RIGHT1	0x0104	/* Audio Dock DAC1 Right, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC1_RIGHT2	0x0105	/* Audio Dock DAC1 Right, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC1_RIGHT3	0x0106	/* Audio Dock DAC1 Right, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC1_RIGHT4	0x0107	/* Audio Dock DAC1 Right, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_DAC2_LEFT1	0x0108	/* Audio Dock DAC2 Left, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC2_LEFT2	0x0109	/* Audio Dock DAC2 Left, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC2_LEFT3	0x010a	/* Audio Dock DAC2 Left, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC2_LEFT4	0x010b	/* Audio Dock DAC2 Left, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_DAC2_RIGHT1	0x010c	/* Audio Dock DAC2 Right, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC2_RIGHT2	0x010d	/* Audio Dock DAC2 Right, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC2_RIGHT3	0x010e	/* Audio Dock DAC2 Right, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC2_RIGHT4	0x010f	/* Audio Dock DAC2 Right, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_DAC3_LEFT1	0x0110	/* Audio Dock DAC1 Left, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC3_LEFT2	0x0111	/* Audio Dock DAC1 Left, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC3_LEFT3	0x0112	/* Audio Dock DAC1 Left, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC3_LEFT4	0x0113	/* Audio Dock DAC1 Left, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_PHONES_LEFT1	0x0112	/* Audio Dock PHONES Left, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_PHONES_LEFT2	0x0113	/* Audio Dock PHONES Left, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC3_RIGHT1	0x0114	/* Audio Dock DAC1 Right, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC3_RIGHT2	0x0115	/* Audio Dock DAC1 Right, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC3_RIGHT3	0x0116	/* Audio Dock DAC1 Right, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC3_RIGHT4	0x0117	/* Audio Dock DAC1 Right, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_PHONES_RIGHT1	0x0116	/* Audio Dock PHONES Right, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_PHONES_RIGHT2	0x0117	/* Audio Dock PHONES Right, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC4_LEFT1	0x0118	/* Audio Dock DAC2 Left, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC4_LEFT2	0x0119	/* Audio Dock DAC2 Left, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC4_LEFT3	0x011a	/* Audio Dock DAC2 Left, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC4_LEFT4	0x011b	/* Audio Dock DAC2 Left, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_SPDIF_LEFT1	0x011a	/* Audio Dock SPDIF Left, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_SPDIF_LEFT2	0x011b	/* Audio Dock SPDIF Left, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC4_RIGHT1	0x011c	/* Audio Dock DAC2 Right, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_DAC4_RIGHT2	0x011d	/* Audio Dock DAC2 Right, 2nd or 96kHz */
#घोषणा EMU_DST_DOCK_DAC4_RIGHT3	0x011e	/* Audio Dock DAC2 Right, 3rd or 192kHz */
#घोषणा EMU_DST_DOCK_DAC4_RIGHT4	0x011f	/* Audio Dock DAC2 Right, 4th or 192kHz */
#घोषणा EMU_DST_DOCK_SPDIF_RIGHT1	0x011e	/* Audio Dock SPDIF Right, 1st or 48kHz only */
#घोषणा EMU_DST_DOCK_SPDIF_RIGHT2	0x011f	/* Audio Dock SPDIF Right, 2nd or 96kHz */
#घोषणा EMU_DST_HANA_SPDIF_LEFT1	0x0200	/* Hana SPDIF Left, 1st or 48kHz only */
#घोषणा EMU_DST_HANA_SPDIF_LEFT2	0x0202	/* Hana SPDIF Left, 2nd or 96kHz */
#घोषणा EMU_DST_HANA_SPDIF_RIGHT1	0x0201	/* Hana SPDIF Right, 1st or 48kHz only */
#घोषणा EMU_DST_HANA_SPDIF_RIGHT2	0x0203	/* Hana SPDIF Right, 2nd or 96kHz */
#घोषणा EMU_DST_HAMOA_DAC_LEFT1	0x0300	/* Hamoa DAC Left, 1st or 48kHz only */
#घोषणा EMU_DST_HAMOA_DAC_LEFT2	0x0302	/* Hamoa DAC Left, 2nd or 96kHz */
#घोषणा EMU_DST_HAMOA_DAC_LEFT3	0x0304	/* Hamoa DAC Left, 3rd or 192kHz */
#घोषणा EMU_DST_HAMOA_DAC_LEFT4	0x0306	/* Hamoa DAC Left, 4th or 192kHz */
#घोषणा EMU_DST_HAMOA_DAC_RIGHT1	0x0301	/* Hamoa DAC Right, 1st or 48kHz only */
#घोषणा EMU_DST_HAMOA_DAC_RIGHT2	0x0303	/* Hamoa DAC Right, 2nd or 96kHz */
#घोषणा EMU_DST_HAMOA_DAC_RIGHT3	0x0305	/* Hamoa DAC Right, 3rd or 192kHz */
#घोषणा EMU_DST_HAMOA_DAC_RIGHT4	0x0307	/* Hamoa DAC Right, 4th or 192kHz */
#घोषणा EMU_DST_HANA_ADAT	0x0400	/* Hana ADAT 8 channel out +0 to +7 */
#घोषणा EMU_DST_ALICE_I2S0_LEFT		0x0500	/* Alice2 I2S0 Left */
#घोषणा EMU_DST_ALICE_I2S0_RIGHT	0x0501	/* Alice2 I2S0 Right */
#घोषणा EMU_DST_ALICE_I2S1_LEFT		0x0600	/* Alice2 I2S1 Left */
#घोषणा EMU_DST_ALICE_I2S1_RIGHT	0x0601	/* Alice2 I2S1 Right */
#घोषणा EMU_DST_ALICE_I2S2_LEFT		0x0700	/* Alice2 I2S2 Left */
#घोषणा EMU_DST_ALICE_I2S2_RIGHT	0x0701	/* Alice2 I2S2 Right */

/* Additional destinations क्रम 1616(M)/Microकरोck */
/* Microकरोck S/PDIF OUT Left, 1st or 48kHz only */
#घोषणा EMU_DST_MDOCK_SPDIF_LEFT1	0x0112
/* Microकरोck S/PDIF OUT Left, 2nd or 96kHz */
#घोषणा EMU_DST_MDOCK_SPDIF_LEFT2	0x0113
/* Microकरोck S/PDIF OUT Right, 1st or 48kHz only */
#घोषणा EMU_DST_MDOCK_SPDIF_RIGHT1	0x0116
/* Microकरोck S/PDIF OUT Right, 2nd or 96kHz  */
#घोषणा EMU_DST_MDOCK_SPDIF_RIGHT2	0x0117
/* Microकरोck S/PDIF ADAT 8 channel out +8 to +f */
#घोषणा EMU_DST_MDOCK_ADAT		0x0118

/* Headphone jack on 1010 cardbus? 44.1/48kHz only? */
#घोषणा EMU_DST_MANA_DAC_LEFT		0x0300
/* Headphone jack on 1010 cardbus? 44.1/48kHz only? */
#घोषणा EMU_DST_MANA_DAC_RIGHT		0x0301

/************************************************************************************************/
/* EMU1010m HANA Sources									*/
/************************************************************************************************/
/* Hana, original 1010,1212,1820 using Alice2
 * Sources SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00,0x00-0x1f: Silence
 * 0x01, 0x10-0x1f: 32 Elink channels from Audio Dock
 * 0x01, 0x00: Dock Mic A
 * 0x01, 0x04: Dock Mic B
 * 0x01, 0x08: Dock ADC 1 Left
 * 0x01, 0x0c: Dock ADC 1 Right
 * 0x01, 0x10: Dock ADC 2 Left
 * 0x01, 0x14: Dock ADC 2 Right
 * 0x01, 0x18: Dock ADC 3 Left
 * 0x01, 0x1c: Dock ADC 3 Right
 * 0x02, 0x00: Hana ADC Left
 * 0x02, 0x01: Hana ADC Right
 * 0x03, 0x00-0x0f: 16 inमाला_दो from Alice2 Emu32A output
 * 0x03, 0x10-0x1f: 16 inमाला_दो from Alice2 Emu32B output
 * 0x04, 0x00-0x07: Hana ADAT
 * 0x05, 0x00: Hana S/PDIF Left
 * 0x05, 0x01: Hana S/PDIF Right
 * 0x06-0x07: Not used
 *
 * Hana2 never released, but used Tina
 * Not needed.
 *
 * Hana3, rev2 1010,1212,1616 using Tina
 * Sources SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00,0x00-0x1f: Silence
 * 0x01, 0x10-0x1f: 32 Elink channels from Audio Dock
 * 0x01, 0x00: Dock Mic A
 * 0x01, 0x04: Dock Mic B
 * 0x01, 0x08: Dock ADC 1 Left
 * 0x01, 0x0c: Dock ADC 1 Right
 * 0x01, 0x10: Dock ADC 2 Left
 * 0x01, 0x12: Dock S/PDIF Left
 * 0x01, 0x14: Dock ADC 2 Right
 * 0x01, 0x16: Dock S/PDIF Right
 * 0x01, 0x18-0x1f: Dock ADAT 0-7
 * 0x01, 0x18: Dock ADC 3 Left
 * 0x01, 0x1c: Dock ADC 3 Right
 * 0x02, 0x00: Hanoa ADC Left
 * 0x02, 0x01: Hanoa ADC Right
 * 0x03, 0x00-0x0f: 16 inमाला_दो from Tina Emu32A output
 * 0x03, 0x10-0x1f: 16 inमाला_दो from Tina Emu32B output
 * 0x04, 0x00-0x07: Hana3 ADAT
 * 0x05, 0x00: Hana3 S/PDIF Left
 * 0x05, 0x01: Hana3 S/PDIF Right
 * 0x06-0x07: Not used
 *
 * HanaLite, rev1 0404 using Alice2
 * Sources SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00,0x00-0x1f: Silence
 * 0x01: Not used
 * 0x02, 0x00: ADC Left
 * 0x02, 0x01: ADC Right
 * 0x03, 0x00-0x0f: 16 inमाला_दो from Alice2 Emu32A output
 * 0x03, 0x10-0x1f: 16 inमाला_दो from Alice2 Emu32B output
 * 0x04: Not used
 * 0x05, 0x00: S/PDIF Left
 * 0x05, 0x01: S/PDIF Right
 * 0x06-0x07: Not used
 *
 * HanaLiteLite, rev2 0404 using Alice2
 * Sources SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00,0x00-0x1f: Silence
 * 0x01: Not used
 * 0x02, 0x00: ADC Left
 * 0x02, 0x01: ADC Right
 * 0x03, 0x00-0x0f: 16 inमाला_दो from Alice2 Emu32A output
 * 0x03, 0x10-0x1f: 16 inमाला_दो from Alice2 Emu32B output
 * 0x04: Not used
 * 0x05, 0x00: S/PDIF Left
 * 0x05, 0x01: S/PDIF Right
 * 0x06-0x07: Not used
 *
 * Mana, Cardbus 1616 using Tina2
 * Sources SRATEX = 1X rates: 44.1 kHz or 48 kHz
 * 0x00,0x00-0x1f: Silence
 * 0x01, 0x10-0x1f: 32 Elink channels from Audio Dock
 * 0x01, 0x00: Dock Mic A
 * 0x01, 0x04: Dock Mic B
 * 0x01, 0x08: Dock ADC 1 Left
 * 0x01, 0x0c: Dock ADC 1 Right
 * 0x01, 0x10: Dock ADC 2 Left
 * 0x01, 0x12: Dock S/PDIF Left
 * 0x01, 0x14: Dock ADC 2 Right
 * 0x01, 0x16: Dock S/PDIF Right
 * 0x01, 0x18-0x1f: Dock ADAT 0-7
 * 0x01, 0x18: Dock ADC 3 Left
 * 0x01, 0x1c: Dock ADC 3 Right
 * 0x02: Not used
 * 0x03, 0x00-0x0f: 16 inमाला_दो from Tina Emu32A output
 * 0x03, 0x10-0x1f: 16 inमाला_दो from Tina Emu32B output
 * 0x04-0x07: Not used
 *
 */

/* 32-bit sources of संकेत in the Hana FPGA. The sources are routed to
 * destinations using mixer control क्रम each destination - see emumixer.c
 * Sources are either physical inमाला_दो of FPGA,
 * or outमाला_दो from Alice (audigy) - 16 x EMU_SRC_ALICE_EMU32A +
 * 16 x EMU_SRC_ALICE_EMU32B
 */
#घोषणा EMU_SRC_SILENCE		0x0000	/* Silence */
#घोषणा EMU_SRC_DOCK_MIC_A1	0x0100	/* Audio Dock Mic A, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_MIC_A2	0x0101	/* Audio Dock Mic A, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_MIC_A3	0x0102	/* Audio Dock Mic A, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_MIC_A4	0x0103	/* Audio Dock Mic A, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_MIC_B1	0x0104	/* Audio Dock Mic B, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_MIC_B2	0x0105	/* Audio Dock Mic B, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_MIC_B3	0x0106	/* Audio Dock Mic B, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_MIC_B4	0x0107	/* Audio Dock Mic B, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC1_LEFT1	0x0108	/* Audio Dock ADC1 Left, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_ADC1_LEFT2	0x0109	/* Audio Dock ADC1 Left, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_ADC1_LEFT3	0x010a	/* Audio Dock ADC1 Left, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC1_LEFT4	0x010b	/* Audio Dock ADC1 Left, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC1_RIGHT1	0x010c	/* Audio Dock ADC1 Right, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_ADC1_RIGHT2	0x010d	/* Audio Dock ADC1 Right, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_ADC1_RIGHT3	0x010e	/* Audio Dock ADC1 Right, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC1_RIGHT4	0x010f	/* Audio Dock ADC1 Right, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC2_LEFT1	0x0110	/* Audio Dock ADC2 Left, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_ADC2_LEFT2	0x0111	/* Audio Dock ADC2 Left, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_ADC2_LEFT3	0x0112	/* Audio Dock ADC2 Left, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC2_LEFT4	0x0113	/* Audio Dock ADC2 Left, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC2_RIGHT1	0x0114	/* Audio Dock ADC2 Right, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_ADC2_RIGHT2	0x0115	/* Audio Dock ADC2 Right, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_ADC2_RIGHT3	0x0116	/* Audio Dock ADC2 Right, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC2_RIGHT4	0x0117	/* Audio Dock ADC2 Right, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC3_LEFT1	0x0118	/* Audio Dock ADC3 Left, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_ADC3_LEFT2	0x0119	/* Audio Dock ADC3 Left, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_ADC3_LEFT3	0x011a	/* Audio Dock ADC3 Left, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC3_LEFT4	0x011b	/* Audio Dock ADC3 Left, 4th or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC3_RIGHT1	0x011c	/* Audio Dock ADC3 Right, 1st or 48kHz only */
#घोषणा EMU_SRC_DOCK_ADC3_RIGHT2	0x011d	/* Audio Dock ADC3 Right, 2nd or 96kHz */
#घोषणा EMU_SRC_DOCK_ADC3_RIGHT3	0x011e	/* Audio Dock ADC3 Right, 3rd or 192kHz */
#घोषणा EMU_SRC_DOCK_ADC3_RIGHT4	0x011f	/* Audio Dock ADC3 Right, 4th or 192kHz */
#घोषणा EMU_SRC_HAMOA_ADC_LEFT1	0x0200	/* Hamoa ADC Left, 1st or 48kHz only */
#घोषणा EMU_SRC_HAMOA_ADC_LEFT2	0x0202	/* Hamoa ADC Left, 2nd or 96kHz */
#घोषणा EMU_SRC_HAMOA_ADC_LEFT3	0x0204	/* Hamoa ADC Left, 3rd or 192kHz */
#घोषणा EMU_SRC_HAMOA_ADC_LEFT4	0x0206	/* Hamoa ADC Left, 4th or 192kHz */
#घोषणा EMU_SRC_HAMOA_ADC_RIGHT1	0x0201	/* Hamoa ADC Right, 1st or 48kHz only */
#घोषणा EMU_SRC_HAMOA_ADC_RIGHT2	0x0203	/* Hamoa ADC Right, 2nd or 96kHz */
#घोषणा EMU_SRC_HAMOA_ADC_RIGHT3	0x0205	/* Hamoa ADC Right, 3rd or 192kHz */
#घोषणा EMU_SRC_HAMOA_ADC_RIGHT4	0x0207	/* Hamoa ADC Right, 4th or 192kHz */
#घोषणा EMU_SRC_ALICE_EMU32A		0x0300	/* Alice2 EMU32a 16 outमाला_दो. +0 to +0xf */
#घोषणा EMU_SRC_ALICE_EMU32B		0x0310	/* Alice2 EMU32b 16 outमाला_दो. +0 to +0xf */
#घोषणा EMU_SRC_HANA_ADAT	0x0400	/* Hana ADAT 8 channel in +0 to +7 */
#घोषणा EMU_SRC_HANA_SPDIF_LEFT1	0x0500	/* Hana SPDIF Left, 1st or 48kHz only */
#घोषणा EMU_SRC_HANA_SPDIF_LEFT2	0x0502	/* Hana SPDIF Left, 2nd or 96kHz */
#घोषणा EMU_SRC_HANA_SPDIF_RIGHT1	0x0501	/* Hana SPDIF Right, 1st or 48kHz only */
#घोषणा EMU_SRC_HANA_SPDIF_RIGHT2	0x0503	/* Hana SPDIF Right, 2nd or 96kHz */

/* Additional inमाला_दो क्रम 1616(M)/Microकरोck */
/* Microकरोck S/PDIF Left, 1st or 48kHz only */
#घोषणा EMU_SRC_MDOCK_SPDIF_LEFT1	0x0112
/* Microकरोck S/PDIF Left, 2nd or 96kHz */
#घोषणा EMU_SRC_MDOCK_SPDIF_LEFT2	0x0113
/* Microकरोck S/PDIF Right, 1st or 48kHz only */
#घोषणा EMU_SRC_MDOCK_SPDIF_RIGHT1	0x0116
/* Microकरोck S/PDIF Right, 2nd or 96kHz */
#घोषणा EMU_SRC_MDOCK_SPDIF_RIGHT2	0x0117
/* Microकरोck ADAT 8 channel in +8 to +f */
#घोषणा EMU_SRC_MDOCK_ADAT		0x0118

/* 0x600 and 0x700 no used */

/* ------------------- STRUCTURES -------------------- */

क्रमागत अणु
	EMU10K1_EFX,
	EMU10K1_PCM,
	EMU10K1_SYNTH,
	EMU10K1_MIDI
पूर्ण;

काष्ठा snd_emu10k1;

काष्ठा snd_emu10k1_voice अणु
	काष्ठा snd_emu10k1 *emu;
	पूर्णांक number;
	अचिन्हित पूर्णांक use: 1,
	    pcm: 1,
	    efx: 1,
	    synth: 1,
	    midi: 1;
	व्योम (*पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_voice *pvoice);

	काष्ठा snd_emu10k1_pcm *epcm;
पूर्ण;

क्रमागत अणु
	PLAYBACK_EMUVOICE,
	PLAYBACK_EFX,
	CAPTURE_AC97ADC,
	CAPTURE_AC97MIC,
	CAPTURE_EFX
पूर्ण;

काष्ठा snd_emu10k1_pcm अणु
	काष्ठा snd_emu10k1 *emu;
	पूर्णांक type;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_emu10k1_voice *voices[NUM_EFX_PLAYBACK];
	काष्ठा snd_emu10k1_voice *extra;
	अचिन्हित लघु running;
	अचिन्हित लघु first_ptr;
	काष्ठा snd_util_memblk *memblk;
	अचिन्हित पूर्णांक start_addr;
	अचिन्हित पूर्णांक ccca_start_addr;
	अचिन्हित पूर्णांक capture_ipr;	/* पूर्णांकerrupt acknowledge mask */
	अचिन्हित पूर्णांक capture_पूर्णांकe;	/* पूर्णांकerrupt enable mask */
	अचिन्हित पूर्णांक capture_ba_reg;	/* buffer address रेजिस्टर */
	अचिन्हित पूर्णांक capture_bs_reg;	/* buffer size रेजिस्टर */
	अचिन्हित पूर्णांक capture_idx_reg;	/* buffer index रेजिस्टर */
	अचिन्हित पूर्णांक capture_cr_val;	/* control value */
	अचिन्हित पूर्णांक capture_cr_val2;	/* control value2 (क्रम audigy) */
	अचिन्हित पूर्णांक capture_bs_val;	/* buffer size value */
	अचिन्हित पूर्णांक capture_bufsize;	/* buffer size in bytes */
पूर्ण;

काष्ठा snd_emu10k1_pcm_mixer अणु
	/* mono, left, right x 8 sends (4 on emu10k1) */
	अचिन्हित अक्षर send_routing[3][8];
	अचिन्हित अक्षर send_volume[3][8];
	अचिन्हित लघु attn[3];
	काष्ठा snd_emu10k1_pcm *epcm;
पूर्ण;

#घोषणा snd_emu10k1_compose_send_routing(route) \
((route[0] | (route[1] << 4) | (route[2] << 8) | (route[3] << 12)) << 16)

#घोषणा snd_emu10k1_compose_audigy_fxrt1(route) \
((अचिन्हित पूर्णांक)route[0] | ((अचिन्हित पूर्णांक)route[1] << 8) | ((अचिन्हित पूर्णांक)route[2] << 16) | ((अचिन्हित पूर्णांक)route[3] << 24))

#घोषणा snd_emu10k1_compose_audigy_fxrt2(route) \
((अचिन्हित पूर्णांक)route[4] | ((अचिन्हित पूर्णांक)route[5] << 8) | ((अचिन्हित पूर्णांक)route[6] << 16) | ((अचिन्हित पूर्णांक)route[7] << 24))

काष्ठा snd_emu10k1_memblk अणु
	काष्ठा snd_util_memblk mem;
	/* निजी part */
	पूर्णांक first_page, last_page, pages, mapped_page;
	अचिन्हित पूर्णांक map_locked;
	काष्ठा list_head mapped_link;
	काष्ठा list_head mapped_order_link;
पूर्ण;

#घोषणा snd_emu10k1_memblk_offset(blk)	(((blk)->mapped_page << PAGE_SHIFT) | ((blk)->mem.offset & (PAGE_SIZE - 1)))

#घोषणा EMU10K1_MAX_TRAM_BLOCKS_PER_CODE	16

काष्ठा snd_emu10k1_fx8010_ctl अणु
	काष्ठा list_head list;		/* list link container */
	अचिन्हित पूर्णांक vcount;
	अचिन्हित पूर्णांक count;		/* count of GPR (1..16) */
	अचिन्हित लघु gpr[32];		/* GPR number(s) */
	अचिन्हित पूर्णांक value[32];
	अचिन्हित पूर्णांक min;		/* minimum range */
	अचिन्हित पूर्णांक max;		/* maximum range */
	अचिन्हित पूर्णांक translation;	/* translation type (EMU10K1_GPR_TRANSLATION*) */
	काष्ठा snd_kcontrol *kcontrol;
पूर्ण;

प्रकार व्योम (snd_fx8010_irq_handler_t)(काष्ठा snd_emu10k1 *emu, व्योम *निजी_data);

काष्ठा snd_emu10k1_fx8010_irq अणु
	काष्ठा snd_emu10k1_fx8010_irq *next;
	snd_fx8010_irq_handler_t *handler;
	अचिन्हित लघु gpr_running;
	व्योम *निजी_data;
पूर्ण;

काष्ठा snd_emu10k1_fx8010_pcm अणु
	अचिन्हित पूर्णांक valid: 1,
		     खोलोed: 1,
		     active: 1;
	अचिन्हित पूर्णांक channels;		/* 16-bit channels count */
	अचिन्हित पूर्णांक tram_start;	/* initial ring buffer position in TRAM (in samples) */
	अचिन्हित पूर्णांक buffer_size;	/* count of buffered samples */
	अचिन्हित लघु gpr_size;		/* GPR containing size of ring buffer in samples (host) */
	अचिन्हित लघु gpr_ptr;		/* GPR containing current poपूर्णांकer in the ring buffer (host = reset, FX8010) */
	अचिन्हित लघु gpr_count;	/* GPR containing count of samples between two पूर्णांकerrupts (host) */
	अचिन्हित लघु gpr_पंचांगpcount;	/* GPR containing current count of samples to पूर्णांकerrupt (host = set, FX8010) */
	अचिन्हित लघु gpr_trigger;	/* GPR containing trigger (activate) inक्रमmation (host) */
	अचिन्हित लघु gpr_running;	/* GPR containing info अगर PCM is running (FX8010) */
	अचिन्हित अक्षर etram[32];	/* बाह्यal TRAM address & data */
	काष्ठा snd_pcm_indirect pcm_rec;
	अचिन्हित पूर्णांक tram_pos;
	अचिन्हित पूर्णांक tram_shअगरt;
	काष्ठा snd_emu10k1_fx8010_irq irq;
पूर्ण;

काष्ठा snd_emu10k1_fx8010 अणु
	अचिन्हित लघु fxbus_mask;	/* used FX buses (biपंचांगask) */
	अचिन्हित लघु extin_mask;	/* used बाह्यal inमाला_दो (biपंचांगask) */
	अचिन्हित लघु extout_mask;	/* used बाह्यal outमाला_दो (biपंचांगask) */
	अचिन्हित लघु pad1;
	अचिन्हित पूर्णांक itram_size;	/* पूर्णांकernal TRAM size in samples */
	काष्ठा snd_dma_buffer etram_pages; /* बाह्यal TRAM pages and size */
	अचिन्हित पूर्णांक dbg;		/* FX debugger रेजिस्टर */
	अचिन्हित अक्षर name[128];
	पूर्णांक gpr_size;			/* size of allocated GPR controls */
	पूर्णांक gpr_count;			/* count of used kcontrols */
	काष्ठा list_head gpr_ctl;	/* GPR controls */
	काष्ठा mutex lock;
	काष्ठा snd_emu10k1_fx8010_pcm pcm[8];
	spinlock_t irq_lock;
	काष्ठा snd_emu10k1_fx8010_irq *irq_handlers;
पूर्ण;

काष्ठा snd_emu10k1_midi अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *substream_input;
	काष्ठा snd_rawmidi_substream *substream_output;
	अचिन्हित पूर्णांक midi_mode;
	spinlock_t input_lock;
	spinlock_t output_lock;
	spinlock_t खोलो_lock;
	पूर्णांक tx_enable, rx_enable;
	पूर्णांक port;
	पूर्णांक ipr_tx, ipr_rx;
	व्योम (*पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status);
पूर्ण;

क्रमागत अणु
	EMU_MODEL_SB,
	EMU_MODEL_EMU1010,
	EMU_MODEL_EMU1010B,
	EMU_MODEL_EMU1616,
	EMU_MODEL_EMU0404,
पूर्ण;

काष्ठा snd_emu_chip_details अणु
	u32 venकरोr;
	u32 device;
	u32 subप्रणाली;
	अचिन्हित अक्षर revision;
	अचिन्हित अक्षर emu10k1_chip; /* Original SB Live. Not SB Live 24bit. */
	अचिन्हित अक्षर emu10k2_chip; /* Audigy 1 or Audigy 2. */
	अचिन्हित अक्षर ca0102_chip;  /* Audigy 1 or Audigy 2. Not SB Audigy 2 Value. */
	अचिन्हित अक्षर ca0108_chip;  /* Audigy 2 Value */
	अचिन्हित अक्षर ca_cardbus_chip; /* Audigy 2 ZS Notebook */
	अचिन्हित अक्षर ca0151_chip;  /* P16V */
	अचिन्हित अक्षर spk71;        /* Has 7.1 speakers */
	अचिन्हित अक्षर sblive51;	    /* SBLive! 5.1 - extout 0x11 -> center, 0x12 -> lfe */
	अचिन्हित अक्षर spdअगर_bug;    /* Has Spdअगर phasing bug */
	अचिन्हित अक्षर ac97_chip;    /* Has an AC97 chip: 1 = mandatory, 2 = optional */
	अचिन्हित अक्षर ecard;        /* APS EEPROM */
	अचिन्हित अक्षर emu_model;     /* EMU model type */
	अचिन्हित अक्षर spi_dac;      /* SPI पूर्णांकerface क्रम DAC */
	अचिन्हित अक्षर i2c_adc;      /* I2C पूर्णांकerface क्रम ADC */
	अचिन्हित अक्षर adc_1361t;    /* Use Philips 1361T ADC */
	अचिन्हित अक्षर invert_shared_spdअगर; /* analog/digital चयन inverted */
	स्थिर अक्षर *driver;
	स्थिर अक्षर *name;
	स्थिर अक्षर *id;		/* क्रम backward compatibility - can be शून्य अगर not needed */
पूर्ण;

काष्ठा snd_emu1010 अणु
	अचिन्हित पूर्णांक output_source[64];
	अचिन्हित पूर्णांक input_source[64];
	अचिन्हित पूर्णांक adc_pads; /* bit mask */
	अचिन्हित पूर्णांक dac_pads; /* bit mask */
	अचिन्हित पूर्णांक पूर्णांकernal_घड़ी; /* 44100 or 48000 */
	अचिन्हित पूर्णांक optical_in; /* 0:SPDIF, 1:ADAT */
	अचिन्हित पूर्णांक optical_out; /* 0:SPDIF, 1:ADAT */
	काष्ठा delayed_work firmware_work;
	u32 last_reg;
पूर्ण;

काष्ठा snd_emu10k1 अणु
	पूर्णांक irq;

	अचिन्हित दीर्घ port;			/* I/O port number */
	अचिन्हित पूर्णांक tos_link: 1,		/* tos link detected */
		rear_ac97: 1,			/* rear channels are on AC'97 */
		enable_ir: 1;
	अचिन्हित पूर्णांक support_tlv :1;
	/* Contains profile of card capabilities */
	स्थिर काष्ठा snd_emu_chip_details *card_capabilities;
	अचिन्हित पूर्णांक audigy;			/* is Audigy? */
	अचिन्हित पूर्णांक revision;			/* chip revision */
	अचिन्हित पूर्णांक serial;			/* serial number */
	अचिन्हित लघु model;			/* subप्रणाली id */
	अचिन्हित पूर्णांक card_type;			/* EMU10K1_CARD_* */
	अचिन्हित पूर्णांक ecard_ctrl;		/* ecard control bits */
	अचिन्हित पूर्णांक address_mode;		/* address mode */
	अचिन्हित दीर्घ dma_mask;			/* PCI DMA mask */
	bool iommu_workaround;			/* IOMMU workaround needed */
	अचिन्हित पूर्णांक delay_pcm_irq;		/* in samples */
	पूर्णांक max_cache_pages;			/* max memory size / PAGE_SIZE */
	काष्ठा snd_dma_buffer silent_page;	/* silent page */
	काष्ठा snd_dma_buffer ptb_pages;	/* page table pages */
	काष्ठा snd_dma_device p16v_dma_dev;
	काष्ठा snd_dma_buffer p16v_buffer;

	काष्ठा snd_util_memhdr *memhdr;		/* page allocation list */

	काष्ठा list_head mapped_link_head;
	काष्ठा list_head mapped_order_link_head;
	व्योम **page_ptr_table;
	अचिन्हित दीर्घ *page_addr_table;
	spinlock_t memblk_lock;

	अचिन्हित पूर्णांक spdअगर_bits[3];		/* s/pdअगर out setup */
	अचिन्हित पूर्णांक i2c_capture_source;
	u8 i2c_capture_volume[4][2];

	काष्ठा snd_emu10k1_fx8010 fx8010;		/* FX8010 info */
	पूर्णांक gpr_base;
	
	काष्ठा snd_ac97 *ac97;

	काष्ठा pci_dev *pci;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm *pcm_mic;
	काष्ठा snd_pcm *pcm_efx;
	काष्ठा snd_pcm *pcm_multi;
	काष्ठा snd_pcm *pcm_p16v;

	spinlock_t synth_lock;
	व्योम *synth;
	पूर्णांक (*get_synth_voice)(काष्ठा snd_emu10k1 *emu);

	spinlock_t reg_lock;
	spinlock_t emu_lock;
	spinlock_t voice_lock;
	spinlock_t spi_lock; /* serialises access to spi port */
	spinlock_t i2c_lock; /* serialises access to i2c port */

	काष्ठा snd_emu10k1_voice voices[NUM_G];
	काष्ठा snd_emu10k1_voice p16v_voices[4];
	काष्ठा snd_emu10k1_voice p16v_capture_voice;
	पूर्णांक p16v_device_offset;
	u32 p16v_capture_source;
	u32 p16v_capture_channel;
        काष्ठा snd_emu1010 emu1010;
	काष्ठा snd_emu10k1_pcm_mixer pcm_mixer[32];
	काष्ठा snd_emu10k1_pcm_mixer efx_pcm_mixer[NUM_EFX_PLAYBACK];
	काष्ठा snd_kcontrol *ctl_send_routing;
	काष्ठा snd_kcontrol *ctl_send_volume;
	काष्ठा snd_kcontrol *ctl_attn;
	काष्ठा snd_kcontrol *ctl_efx_send_routing;
	काष्ठा snd_kcontrol *ctl_efx_send_volume;
	काष्ठा snd_kcontrol *ctl_efx_attn;

	व्योम (*hwvol_पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status);
	व्योम (*capture_पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status);
	व्योम (*capture_mic_पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status);
	व्योम (*capture_efx_पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status);
	व्योम (*spdअगर_पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status);
	व्योम (*dsp_पूर्णांकerrupt)(काष्ठा snd_emu10k1 *emu);

	काष्ठा snd_pcm_substream *pcm_capture_substream;
	काष्ठा snd_pcm_substream *pcm_capture_mic_substream;
	काष्ठा snd_pcm_substream *pcm_capture_efx_substream;
	काष्ठा snd_pcm_substream *pcm_playback_efx_substream;

	काष्ठा snd_समयr *समयr;

	काष्ठा snd_emu10k1_midi midi;
	काष्ठा snd_emu10k1_midi midi2; /* क्रम audigy */

	अचिन्हित पूर्णांक efx_voices_mask[2];
	अचिन्हित पूर्णांक next_मुक्त_voice;

	स्थिर काष्ठा firmware *firmware;
	स्थिर काष्ठा firmware *करोck_fw;

#अगर_घोषित CONFIG_PM_SLEEP
	अचिन्हित पूर्णांक *saved_ptr;
	अचिन्हित पूर्णांक *saved_gpr;
	अचिन्हित पूर्णांक *tram_val_saved;
	अचिन्हित पूर्णांक *tram_addr_saved;
	अचिन्हित पूर्णांक *saved_icode;
	अचिन्हित पूर्णांक *p16v_saved;
	अचिन्हित पूर्णांक saved_a_iocfg, saved_hcfg;
	bool suspend;
#पूर्ण_अगर

पूर्ण;

पूर्णांक snd_emu10k1_create(काष्ठा snd_card *card,
		       काष्ठा pci_dev *pci,
		       अचिन्हित लघु extin_mask,
		       अचिन्हित लघु extout_mask,
		       दीर्घ max_cache_bytes,
		       पूर्णांक enable_ir,
		       uपूर्णांक subप्रणाली,
		       काष्ठा snd_emu10k1 ** remu);

पूर्णांक snd_emu10k1_pcm(काष्ठा snd_emu10k1 *emu, पूर्णांक device);
पूर्णांक snd_emu10k1_pcm_mic(काष्ठा snd_emu10k1 *emu, पूर्णांक device);
पूर्णांक snd_emu10k1_pcm_efx(काष्ठा snd_emu10k1 *emu, पूर्णांक device);
पूर्णांक snd_p16v_pcm(काष्ठा snd_emu10k1 *emu, पूर्णांक device);
पूर्णांक snd_p16v_मुक्त(काष्ठा snd_emu10k1 * emu);
पूर्णांक snd_p16v_mixer(काष्ठा snd_emu10k1 * emu);
पूर्णांक snd_emu10k1_pcm_multi(काष्ठा snd_emu10k1 *emu, पूर्णांक device);
पूर्णांक snd_emu10k1_fx8010_pcm(काष्ठा snd_emu10k1 *emu, पूर्णांक device);
पूर्णांक snd_emu10k1_mixer(काष्ठा snd_emu10k1 * emu, पूर्णांक pcm_device, पूर्णांक multi_device);
पूर्णांक snd_emu10k1_समयr(काष्ठा snd_emu10k1 * emu, पूर्णांक device);
पूर्णांक snd_emu10k1_fx8010_new(काष्ठा snd_emu10k1 *emu, पूर्णांक device);

irqवापस_t snd_emu10k1_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);

व्योम snd_emu10k1_voice_init(काष्ठा snd_emu10k1 * emu, पूर्णांक voice);
पूर्णांक snd_emu10k1_init_efx(काष्ठा snd_emu10k1 *emu);
व्योम snd_emu10k1_मुक्त_efx(काष्ठा snd_emu10k1 *emu);
पूर्णांक snd_emu10k1_fx8010_tram_setup(काष्ठा snd_emu10k1 *emu, u32 size);
पूर्णांक snd_emu10k1_करोne(काष्ठा snd_emu10k1 * emu);

/* I/O functions */
अचिन्हित पूर्णांक snd_emu10k1_ptr_पढ़ो(काष्ठा snd_emu10k1 * emu, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक chn);
व्योम snd_emu10k1_ptr_ग_लिखो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक chn, अचिन्हित पूर्णांक data);
अचिन्हित पूर्णांक snd_emu10k1_ptr20_पढ़ो(काष्ठा snd_emu10k1 * emu, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक chn);
व्योम snd_emu10k1_ptr20_ग_लिखो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक chn, अचिन्हित पूर्णांक data);
पूर्णांक snd_emu10k1_spi_ग_लिखो(काष्ठा snd_emu10k1 * emu, अचिन्हित पूर्णांक data);
पूर्णांक snd_emu10k1_i2c_ग_लिखो(काष्ठा snd_emu10k1 *emu, u32 reg, u32 value);
पूर्णांक snd_emu1010_fpga_ग_लिखो(काष्ठा snd_emu10k1 * emu, u32 reg, u32 value);
पूर्णांक snd_emu1010_fpga_पढ़ो(काष्ठा snd_emu10k1 * emu, u32 reg, u32 *value);
पूर्णांक snd_emu1010_fpga_link_dst_src_ग_लिखो(काष्ठा snd_emu10k1 * emu, u32 dst, u32 src);
अचिन्हित पूर्णांक snd_emu10k1_efx_पढ़ो(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक pc);
व्योम snd_emu10k1_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक पूर्णांकrenb);
व्योम snd_emu10k1_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक पूर्णांकrenb);
व्योम snd_emu10k1_voice_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_पूर्णांकr_ack(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_half_loop_पूर्णांकr_enable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_half_loop_पूर्णांकr_disable(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_half_loop_पूर्णांकr_ack(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_set_loop_stop(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_voice_clear_loop_stop(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक voicक्रमागत);
व्योम snd_emu10k1_रुको(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक रुको);
अटल अंतरभूत अचिन्हित पूर्णांक snd_emu10k1_wc(काष्ठा snd_emu10k1 *emu) अणु वापस (inl(emu->port + WC) >> 6) & 0xfffff; पूर्ण
अचिन्हित लघु snd_emu10k1_ac97_पढ़ो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg);
व्योम snd_emu10k1_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg, अचिन्हित लघु data);
अचिन्हित पूर्णांक snd_emu10k1_rate_to_pitch(अचिन्हित पूर्णांक rate);

#अगर_घोषित CONFIG_PM_SLEEP
व्योम snd_emu10k1_suspend_regs(काष्ठा snd_emu10k1 *emu);
व्योम snd_emu10k1_resume_init(काष्ठा snd_emu10k1 *emu);
व्योम snd_emu10k1_resume_regs(काष्ठा snd_emu10k1 *emu);
पूर्णांक snd_emu10k1_efx_alloc_pm_buffer(काष्ठा snd_emu10k1 *emu);
व्योम snd_emu10k1_efx_मुक्त_pm_buffer(काष्ठा snd_emu10k1 *emu);
व्योम snd_emu10k1_efx_suspend(काष्ठा snd_emu10k1 *emu);
व्योम snd_emu10k1_efx_resume(काष्ठा snd_emu10k1 *emu);
पूर्णांक snd_p16v_alloc_pm_buffer(काष्ठा snd_emu10k1 *emu);
व्योम snd_p16v_मुक्त_pm_buffer(काष्ठा snd_emu10k1 *emu);
व्योम snd_p16v_suspend(काष्ठा snd_emu10k1 *emu);
व्योम snd_p16v_resume(काष्ठा snd_emu10k1 *emu);
#पूर्ण_अगर

/* memory allocation */
काष्ठा snd_util_memblk *snd_emu10k1_alloc_pages(काष्ठा snd_emu10k1 *emu, काष्ठा snd_pcm_substream *substream);
पूर्णांक snd_emu10k1_मुक्त_pages(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk);
पूर्णांक snd_emu10k1_alloc_pages_maybe_wider(काष्ठा snd_emu10k1 *emu, माप_प्रकार size,
					काष्ठा snd_dma_buffer *dmab);
काष्ठा snd_util_memblk *snd_emu10k1_synth_alloc(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक size);
पूर्णांक snd_emu10k1_synth_मुक्त(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk);
पूर्णांक snd_emu10k1_synth_bzero(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk, पूर्णांक offset, पूर्णांक size);
पूर्णांक snd_emu10k1_synth_copy_from_user(काष्ठा snd_emu10k1 *emu, काष्ठा snd_util_memblk *blk, पूर्णांक offset, स्थिर अक्षर __user *data, पूर्णांक size);
पूर्णांक snd_emu10k1_memblk_map(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_memblk *blk);

/* voice allocation */
पूर्णांक snd_emu10k1_voice_alloc(काष्ठा snd_emu10k1 *emu, पूर्णांक type, पूर्णांक pair, काष्ठा snd_emu10k1_voice **rvoice);
पूर्णांक snd_emu10k1_voice_मुक्त(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_voice *pvoice);

/* MIDI uart */
पूर्णांक snd_emu10k1_midi(काष्ठा snd_emu10k1 * emu);
पूर्णांक snd_emu10k1_audigy_midi(काष्ठा snd_emu10k1 * emu);

/* proc पूर्णांकerface */
पूर्णांक snd_emu10k1_proc_init(काष्ठा snd_emu10k1 * emu);

/* fx8010 irq handler */
पूर्णांक snd_emu10k1_fx8010_रेजिस्टर_irq_handler(काष्ठा snd_emu10k1 *emu,
					    snd_fx8010_irq_handler_t *handler,
					    अचिन्हित अक्षर gpr_running,
					    व्योम *निजी_data,
					    काष्ठा snd_emu10k1_fx8010_irq *irq);
पूर्णांक snd_emu10k1_fx8010_unरेजिस्टर_irq_handler(काष्ठा snd_emu10k1 *emu,
					      काष्ठा snd_emu10k1_fx8010_irq *irq);

#पूर्ण_अगर	/* __SOUND_EMU10K1_H */
