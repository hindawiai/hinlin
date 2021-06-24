<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Advanced Linux Sound Architecture - ALSA - Driver
 *  Copyright (c) 1994-2003 by Jaroslav Kysela <perex@perex.cz>,
 *                             Abramo Bagnara <abramo@alsa-project.org>
 *
 *
 *   This program is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#अगर_अघोषित _UAPI__SOUND_ASOUND_H
#घोषणा _UAPI__SOUND_ASOUND_H

#अगर defined(__KERNEL__) || defined(__linux__)
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>
#अन्यथा
#समावेश <endian.h>
#समावेश <sys/ioctl.h>
#पूर्ण_अगर

#अगर_अघोषित __KERNEL__
#समावेश <मानककोष.स>
#समावेश <समय.स>
#पूर्ण_अगर

/*
 *  protocol version
 */

#घोषणा SNDRV_PROTOCOL_VERSION(major, minor, subminor) (((major)<<16)|((minor)<<8)|(subminor))
#घोषणा SNDRV_PROTOCOL_MAJOR(version) (((version)>>16)&0xffff)
#घोषणा SNDRV_PROTOCOL_MINOR(version) (((version)>>8)&0xff)
#घोषणा SNDRV_PROTOCOL_MICRO(version) ((version)&0xff)
#घोषणा SNDRV_PROTOCOL_INCOMPATIBLE(kversion, uversion) \
	(SNDRV_PROTOCOL_MAJOR(kversion) != SNDRV_PROTOCOL_MAJOR(uversion) || \
	 (SNDRV_PROTOCOL_MAJOR(kversion) == SNDRV_PROTOCOL_MAJOR(uversion) && \
	   SNDRV_PROTOCOL_MINOR(kversion) != SNDRV_PROTOCOL_MINOR(uversion)))

/****************************************************************************
 *                                                                          *
 *        Digital audio पूर्णांकerface					    *
 *                                                                          *
 ****************************************************************************/

काष्ठा snd_aes_iec958 अणु
	अचिन्हित अक्षर status[24];	/* AES/IEC958 channel status bits */
	अचिन्हित अक्षर subcode[147];	/* AES/IEC958 subcode bits */
	अचिन्हित अक्षर pad;		/* nothing */
	अचिन्हित अक्षर dig_subframe[4];	/* AES/IEC958 subframe bits */
पूर्ण;

/****************************************************************************
 *                                                                          *
 *        CEA-861 Audio InfoFrame. Used in HDMI and DisplayPort		    *
 *                                                                          *
 ****************************************************************************/

काष्ठा snd_cea_861_aud_अगर अणु
	अचिन्हित अक्षर db1_ct_cc; /* coding type and channel count */
	अचिन्हित अक्षर db2_sf_ss; /* sample frequency and size */
	अचिन्हित अक्षर db3; /* not used, all zeros */
	अचिन्हित अक्षर db4_ca; /* channel allocation code */
	अचिन्हित अक्षर db5_dminh_lsv; /* करोwnmix inhibit & level-shit values */
पूर्ण;

/****************************************************************************
 *                                                                          *
 *      Section क्रम driver hardware dependent पूर्णांकerface - /dev/snd/hw?      *
 *                                                                          *
 ****************************************************************************/

#घोषणा SNDRV_HWDEP_VERSION		SNDRV_PROTOCOL_VERSION(1, 0, 1)

क्रमागत अणु
	SNDRV_HWDEP_IFACE_OPL2 = 0,
	SNDRV_HWDEP_IFACE_OPL3,
	SNDRV_HWDEP_IFACE_OPL4,
	SNDRV_HWDEP_IFACE_SB16CSP,	/* Creative Signal Processor */
	SNDRV_HWDEP_IFACE_EMU10K1,	/* FX8010 processor in EMU10K1 chip */
	SNDRV_HWDEP_IFACE_YSS225,	/* Yamaha FX processor */
	SNDRV_HWDEP_IFACE_ICS2115,	/* Wavetable synth */
	SNDRV_HWDEP_IFACE_SSCAPE,	/* Ensoniq SoundScape ISA card (MC68EC000) */
	SNDRV_HWDEP_IFACE_VX,		/* Digigram VX cards */
	SNDRV_HWDEP_IFACE_MIXART,	/* Digigram miXart cards */
	SNDRV_HWDEP_IFACE_USX2Y,	/* Tascam US122, US224 & US428 usb */
	SNDRV_HWDEP_IFACE_EMUX_WAVETABLE, /* EmuX wavetable */
	SNDRV_HWDEP_IFACE_BLUETOOTH,	/* Bluetooth audio */
	SNDRV_HWDEP_IFACE_USX2Y_PCM,	/* Tascam US122, US224 & US428 rawusb pcm */
	SNDRV_HWDEP_IFACE_PCXHR,	/* Digigram PCXHR */
	SNDRV_HWDEP_IFACE_SB_RC,	/* SB Extigy/Audigy2NX remote control */
	SNDRV_HWDEP_IFACE_HDA,		/* HD-audio */
	SNDRV_HWDEP_IFACE_USB_STREAM,	/* direct access to usb stream */
	SNDRV_HWDEP_IFACE_FW_DICE,	/* TC DICE FireWire device */
	SNDRV_HWDEP_IFACE_FW_FIREWORKS,	/* Echo Audio Fireworks based device */
	SNDRV_HWDEP_IFACE_FW_BEBOB,	/* BridgeCo BeBoB based device */
	SNDRV_HWDEP_IFACE_FW_OXFW,	/* Oxक्रमd OXFW970/971 based device */
	SNDRV_HWDEP_IFACE_FW_DIGI00X,	/* Digidesign Digi 002/003 family */
	SNDRV_HWDEP_IFACE_FW_TASCAM,	/* TASCAM FireWire series */
	SNDRV_HWDEP_IFACE_LINE6,	/* Line6 USB processors */
	SNDRV_HWDEP_IFACE_FW_MOTU,	/* MOTU FireWire series */
	SNDRV_HWDEP_IFACE_FW_FIREFACE,	/* RME Fireface series */

	/* Don't क्रमget to change the following: */
	SNDRV_HWDEP_IFACE_LAST = SNDRV_HWDEP_IFACE_FW_FIREFACE
पूर्ण;

काष्ठा snd_hwdep_info अणु
	अचिन्हित पूर्णांक device;		/* WR: device number */
	पूर्णांक card;			/* R: card number */
	अचिन्हित अक्षर id[64];		/* ID (user selectable) */
	अचिन्हित अक्षर name[80];		/* hwdep name */
	पूर्णांक अगरace;			/* hwdep पूर्णांकerface */
	अचिन्हित अक्षर reserved[64];	/* reserved क्रम future */
पूर्ण;

/* generic DSP loader */
काष्ठा snd_hwdep_dsp_status अणु
	अचिन्हित पूर्णांक version;		/* R: driver-specअगरic version */
	अचिन्हित अक्षर id[32];		/* R: driver-specअगरic ID string */
	अचिन्हित पूर्णांक num_dsps;		/* R: number of DSP images to transfer */
	अचिन्हित पूर्णांक dsp_loaded;	/* R: bit flags indicating the loaded DSPs */
	अचिन्हित पूर्णांक chip_पढ़ोy;	/* R: 1 = initialization finished */
	अचिन्हित अक्षर reserved[16];	/* reserved क्रम future use */
पूर्ण;

काष्ठा snd_hwdep_dsp_image अणु
	अचिन्हित पूर्णांक index;		/* W: DSP index */
	अचिन्हित अक्षर name[64];		/* W: ID (e.g. file name) */
	अचिन्हित अक्षर __user *image;	/* W: binary image */
	माप_प्रकार length;			/* W: size of image in bytes */
	अचिन्हित दीर्घ driver_data;	/* W: driver-specअगरic data */
पूर्ण;

#घोषणा SNDRV_HWDEP_IOCTL_PVERSION	_IOR ('H', 0x00, पूर्णांक)
#घोषणा SNDRV_HWDEP_IOCTL_INFO		_IOR ('H', 0x01, काष्ठा snd_hwdep_info)
#घोषणा SNDRV_HWDEP_IOCTL_DSP_STATUS	_IOR('H', 0x02, काष्ठा snd_hwdep_dsp_status)
#घोषणा SNDRV_HWDEP_IOCTL_DSP_LOAD	_IOW('H', 0x03, काष्ठा snd_hwdep_dsp_image)

/*****************************************************************************
 *                                                                           *
 *             Digital Audio (PCM) पूर्णांकerface - /dev/snd/pcm??                *
 *                                                                           *
 *****************************************************************************/

#घोषणा SNDRV_PCM_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 15)

प्रकार अचिन्हित दीर्घ snd_pcm_uframes_t;
प्रकार चिन्हित दीर्घ snd_pcm_sframes_t;

क्रमागत अणु
	SNDRV_PCM_CLASS_GENERIC = 0,	/* standard mono or stereo device */
	SNDRV_PCM_CLASS_MULTI,		/* multichannel device */
	SNDRV_PCM_CLASS_MODEM,		/* software modem class */
	SNDRV_PCM_CLASS_DIGITIZER,	/* digitizer class */
	/* Don't क्रमget to change the following: */
	SNDRV_PCM_CLASS_LAST = SNDRV_PCM_CLASS_DIGITIZER,
पूर्ण;

क्रमागत अणु
	SNDRV_PCM_SUBCLASS_GENERIC_MIX = 0, /* mono or stereo subdevices are mixed together */
	SNDRV_PCM_SUBCLASS_MULTI_MIX,	/* multichannel subdevices are mixed together */
	/* Don't क्रमget to change the following: */
	SNDRV_PCM_SUBCLASS_LAST = SNDRV_PCM_SUBCLASS_MULTI_MIX,
पूर्ण;

क्रमागत अणु
	SNDRV_PCM_STREAM_PLAYBACK = 0,
	SNDRV_PCM_STREAM_CAPTURE,
	SNDRV_PCM_STREAM_LAST = SNDRV_PCM_STREAM_CAPTURE,
पूर्ण;

प्रकार पूर्णांक __bitwise snd_pcm_access_t;
#घोषणा	SNDRV_PCM_ACCESS_MMAP_INTERLEAVED	((__क्रमce snd_pcm_access_t) 0) /* पूर्णांकerleaved mmap */
#घोषणा	SNDRV_PCM_ACCESS_MMAP_NONINTERLEAVED	((__क्रमce snd_pcm_access_t) 1) /* nonपूर्णांकerleaved mmap */
#घोषणा	SNDRV_PCM_ACCESS_MMAP_COMPLEX		((__क्रमce snd_pcm_access_t) 2) /* complex mmap */
#घोषणा	SNDRV_PCM_ACCESS_RW_INTERLEAVED		((__क्रमce snd_pcm_access_t) 3) /* पढ़ोi/ग_लिखोi */
#घोषणा	SNDRV_PCM_ACCESS_RW_NONINTERLEAVED	((__क्रमce snd_pcm_access_t) 4) /* पढ़ोn/ग_लिखोn */
#घोषणा	SNDRV_PCM_ACCESS_LAST		SNDRV_PCM_ACCESS_RW_NONINTERLEAVED

प्रकार पूर्णांक __bitwise snd_pcm_क्रमmat_t;
#घोषणा	SNDRV_PCM_FORMAT_S8	((__क्रमce snd_pcm_क्रमmat_t) 0)
#घोषणा	SNDRV_PCM_FORMAT_U8	((__क्रमce snd_pcm_क्रमmat_t) 1)
#घोषणा	SNDRV_PCM_FORMAT_S16_LE	((__क्रमce snd_pcm_क्रमmat_t) 2)
#घोषणा	SNDRV_PCM_FORMAT_S16_BE	((__क्रमce snd_pcm_क्रमmat_t) 3)
#घोषणा	SNDRV_PCM_FORMAT_U16_LE	((__क्रमce snd_pcm_क्रमmat_t) 4)
#घोषणा	SNDRV_PCM_FORMAT_U16_BE	((__क्रमce snd_pcm_क्रमmat_t) 5)
#घोषणा	SNDRV_PCM_FORMAT_S24_LE	((__क्रमce snd_pcm_क्रमmat_t) 6) /* low three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S24_BE	((__क्रमce snd_pcm_क्रमmat_t) 7) /* low three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U24_LE	((__क्रमce snd_pcm_क्रमmat_t) 8) /* low three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U24_BE	((__क्रमce snd_pcm_क्रमmat_t) 9) /* low three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S32_LE	((__क्रमce snd_pcm_क्रमmat_t) 10)
#घोषणा	SNDRV_PCM_FORMAT_S32_BE	((__क्रमce snd_pcm_क्रमmat_t) 11)
#घोषणा	SNDRV_PCM_FORMAT_U32_LE	((__क्रमce snd_pcm_क्रमmat_t) 12)
#घोषणा	SNDRV_PCM_FORMAT_U32_BE	((__क्रमce snd_pcm_क्रमmat_t) 13)
#घोषणा	SNDRV_PCM_FORMAT_FLOAT_LE	((__क्रमce snd_pcm_क्रमmat_t) 14) /* 4-byte भग्न, IEEE-754 32-bit, range -1.0 to 1.0 */
#घोषणा	SNDRV_PCM_FORMAT_FLOAT_BE	((__क्रमce snd_pcm_क्रमmat_t) 15) /* 4-byte भग्न, IEEE-754 32-bit, range -1.0 to 1.0 */
#घोषणा	SNDRV_PCM_FORMAT_FLOAT64_LE	((__क्रमce snd_pcm_क्रमmat_t) 16) /* 8-byte भग्न, IEEE-754 64-bit, range -1.0 to 1.0 */
#घोषणा	SNDRV_PCM_FORMAT_FLOAT64_BE	((__क्रमce snd_pcm_क्रमmat_t) 17) /* 8-byte भग्न, IEEE-754 64-bit, range -1.0 to 1.0 */
#घोषणा	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE ((__क्रमce snd_pcm_क्रमmat_t) 18) /* IEC-958 subframe, Little Endian */
#घोषणा	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE ((__क्रमce snd_pcm_क्रमmat_t) 19) /* IEC-958 subframe, Big Endian */
#घोषणा	SNDRV_PCM_FORMAT_MU_LAW		((__क्रमce snd_pcm_क्रमmat_t) 20)
#घोषणा	SNDRV_PCM_FORMAT_A_LAW		((__क्रमce snd_pcm_क्रमmat_t) 21)
#घोषणा	SNDRV_PCM_FORMAT_IMA_ADPCM	((__क्रमce snd_pcm_क्रमmat_t) 22)
#घोषणा	SNDRV_PCM_FORMAT_MPEG		((__क्रमce snd_pcm_क्रमmat_t) 23)
#घोषणा	SNDRV_PCM_FORMAT_GSM		((__क्रमce snd_pcm_क्रमmat_t) 24)
#घोषणा	SNDRV_PCM_FORMAT_S20_LE	((__क्रमce snd_pcm_क्रमmat_t) 25) /* in four bytes, LSB justअगरied */
#घोषणा	SNDRV_PCM_FORMAT_S20_BE	((__क्रमce snd_pcm_क्रमmat_t) 26) /* in four bytes, LSB justअगरied */
#घोषणा	SNDRV_PCM_FORMAT_U20_LE	((__क्रमce snd_pcm_क्रमmat_t) 27) /* in four bytes, LSB justअगरied */
#घोषणा	SNDRV_PCM_FORMAT_U20_BE	((__क्रमce snd_pcm_क्रमmat_t) 28) /* in four bytes, LSB justअगरied */
/* gap in the numbering क्रम a future standard linear क्रमmat */
#घोषणा	SNDRV_PCM_FORMAT_SPECIAL	((__क्रमce snd_pcm_क्रमmat_t) 31)
#घोषणा	SNDRV_PCM_FORMAT_S24_3LE	((__क्रमce snd_pcm_क्रमmat_t) 32)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S24_3BE	((__क्रमce snd_pcm_क्रमmat_t) 33)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U24_3LE	((__क्रमce snd_pcm_क्रमmat_t) 34)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U24_3BE	((__क्रमce snd_pcm_क्रमmat_t) 35)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S20_3LE	((__क्रमce snd_pcm_क्रमmat_t) 36)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S20_3BE	((__क्रमce snd_pcm_क्रमmat_t) 37)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U20_3LE	((__क्रमce snd_pcm_क्रमmat_t) 38)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U20_3BE	((__क्रमce snd_pcm_क्रमmat_t) 39)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S18_3LE	((__क्रमce snd_pcm_क्रमmat_t) 40)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_S18_3BE	((__क्रमce snd_pcm_क्रमmat_t) 41)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U18_3LE	((__क्रमce snd_pcm_क्रमmat_t) 42)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_U18_3BE	((__क्रमce snd_pcm_क्रमmat_t) 43)	/* in three bytes */
#घोषणा	SNDRV_PCM_FORMAT_G723_24	((__क्रमce snd_pcm_क्रमmat_t) 44) /* 8 samples in 3 bytes */
#घोषणा	SNDRV_PCM_FORMAT_G723_24_1B	((__क्रमce snd_pcm_क्रमmat_t) 45) /* 1 sample in 1 byte */
#घोषणा	SNDRV_PCM_FORMAT_G723_40	((__क्रमce snd_pcm_क्रमmat_t) 46) /* 8 Samples in 5 bytes */
#घोषणा	SNDRV_PCM_FORMAT_G723_40_1B	((__क्रमce snd_pcm_क्रमmat_t) 47) /* 1 sample in 1 byte */
#घोषणा	SNDRV_PCM_FORMAT_DSD_U8		((__क्रमce snd_pcm_क्रमmat_t) 48) /* DSD, 1-byte samples DSD (x8) */
#घोषणा	SNDRV_PCM_FORMAT_DSD_U16_LE	((__क्रमce snd_pcm_क्रमmat_t) 49) /* DSD, 2-byte samples DSD (x16), little endian */
#घोषणा	SNDRV_PCM_FORMAT_DSD_U32_LE	((__क्रमce snd_pcm_क्रमmat_t) 50) /* DSD, 4-byte samples DSD (x32), little endian */
#घोषणा	SNDRV_PCM_FORMAT_DSD_U16_BE	((__क्रमce snd_pcm_क्रमmat_t) 51) /* DSD, 2-byte samples DSD (x16), big endian */
#घोषणा	SNDRV_PCM_FORMAT_DSD_U32_BE	((__क्रमce snd_pcm_क्रमmat_t) 52) /* DSD, 4-byte samples DSD (x32), big endian */
#घोषणा	SNDRV_PCM_FORMAT_LAST		SNDRV_PCM_FORMAT_DSD_U32_BE
#घोषणा	SNDRV_PCM_FORMAT_FIRST		SNDRV_PCM_FORMAT_S8

#अगर_घोषित SNDRV_LITTLE_ENDIAN
#घोषणा	SNDRV_PCM_FORMAT_S16		SNDRV_PCM_FORMAT_S16_LE
#घोषणा	SNDRV_PCM_FORMAT_U16		SNDRV_PCM_FORMAT_U16_LE
#घोषणा	SNDRV_PCM_FORMAT_S24		SNDRV_PCM_FORMAT_S24_LE
#घोषणा	SNDRV_PCM_FORMAT_U24		SNDRV_PCM_FORMAT_U24_LE
#घोषणा	SNDRV_PCM_FORMAT_S32		SNDRV_PCM_FORMAT_S32_LE
#घोषणा	SNDRV_PCM_FORMAT_U32		SNDRV_PCM_FORMAT_U32_LE
#घोषणा	SNDRV_PCM_FORMAT_FLOAT		SNDRV_PCM_FORMAT_FLOAT_LE
#घोषणा	SNDRV_PCM_FORMAT_FLOAT64	SNDRV_PCM_FORMAT_FLOAT64_LE
#घोषणा	SNDRV_PCM_FORMAT_IEC958_SUBFRAME SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
#घोषणा	SNDRV_PCM_FORMAT_S20		SNDRV_PCM_FORMAT_S20_LE
#घोषणा	SNDRV_PCM_FORMAT_U20		SNDRV_PCM_FORMAT_U20_LE
#पूर्ण_अगर
#अगर_घोषित SNDRV_BIG_ENDIAN
#घोषणा	SNDRV_PCM_FORMAT_S16		SNDRV_PCM_FORMAT_S16_BE
#घोषणा	SNDRV_PCM_FORMAT_U16		SNDRV_PCM_FORMAT_U16_BE
#घोषणा	SNDRV_PCM_FORMAT_S24		SNDRV_PCM_FORMAT_S24_BE
#घोषणा	SNDRV_PCM_FORMAT_U24		SNDRV_PCM_FORMAT_U24_BE
#घोषणा	SNDRV_PCM_FORMAT_S32		SNDRV_PCM_FORMAT_S32_BE
#घोषणा	SNDRV_PCM_FORMAT_U32		SNDRV_PCM_FORMAT_U32_BE
#घोषणा	SNDRV_PCM_FORMAT_FLOAT		SNDRV_PCM_FORMAT_FLOAT_BE
#घोषणा	SNDRV_PCM_FORMAT_FLOAT64	SNDRV_PCM_FORMAT_FLOAT64_BE
#घोषणा	SNDRV_PCM_FORMAT_IEC958_SUBFRAME SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
#घोषणा	SNDRV_PCM_FORMAT_S20		SNDRV_PCM_FORMAT_S20_BE
#घोषणा	SNDRV_PCM_FORMAT_U20		SNDRV_PCM_FORMAT_U20_BE
#पूर्ण_अगर

प्रकार पूर्णांक __bitwise snd_pcm_subक्रमmat_t;
#घोषणा	SNDRV_PCM_SUBFORMAT_STD		((__क्रमce snd_pcm_subक्रमmat_t) 0)
#घोषणा	SNDRV_PCM_SUBFORMAT_LAST	SNDRV_PCM_SUBFORMAT_STD

#घोषणा SNDRV_PCM_INFO_MMAP		0x00000001	/* hardware supports mmap */
#घोषणा SNDRV_PCM_INFO_MMAP_VALID	0x00000002	/* period data are valid during transfer */
#घोषणा SNDRV_PCM_INFO_DOUBLE		0x00000004	/* Double buffering needed क्रम PCM start/stop */
#घोषणा SNDRV_PCM_INFO_BATCH		0x00000010	/* द्विगुन buffering */
#घोषणा SNDRV_PCM_INFO_SYNC_APPLPTR	0x00000020	/* need the explicit sync of appl_ptr update */
#घोषणा SNDRV_PCM_INFO_INTERLEAVED	0x00000100	/* channels are पूर्णांकerleaved */
#घोषणा SNDRV_PCM_INFO_NONINTERLEAVED	0x00000200	/* channels are not पूर्णांकerleaved */
#घोषणा SNDRV_PCM_INFO_COMPLEX		0x00000400	/* complex frame organization (mmap only) */
#घोषणा SNDRV_PCM_INFO_BLOCK_TRANSFER	0x00010000	/* hardware transfer block of samples */
#घोषणा SNDRV_PCM_INFO_OVERRANGE	0x00020000	/* hardware supports ADC (capture) overrange detection */
#घोषणा SNDRV_PCM_INFO_RESUME		0x00040000	/* hardware supports stream resume after suspend */
#घोषणा SNDRV_PCM_INFO_PAUSE		0x00080000	/* छोड़ो ioctl is supported */
#घोषणा SNDRV_PCM_INFO_HALF_DUPLEX	0x00100000	/* only half duplex */
#घोषणा SNDRV_PCM_INFO_JOINT_DUPLEX	0x00200000	/* playback and capture stream are somewhat correlated */
#घोषणा SNDRV_PCM_INFO_SYNC_START	0x00400000	/* pcm support some kind of sync go */
#घोषणा SNDRV_PCM_INFO_NO_PERIOD_WAKEUP	0x00800000	/* period wakeup can be disabled */
#घोषणा SNDRV_PCM_INFO_HAS_WALL_CLOCK   0x01000000      /* (Deprecated)has audio wall घड़ी क्रम audio/प्रणाली समय sync */
#घोषणा SNDRV_PCM_INFO_HAS_LINK_ATIME              0x01000000  /* report hardware link audio समय, reset on startup */
#घोषणा SNDRV_PCM_INFO_HAS_LINK_ABSOLUTE_ATIME     0x02000000  /* report असलolute hardware link audio समय, not reset on startup */
#घोषणा SNDRV_PCM_INFO_HAS_LINK_ESTIMATED_ATIME    0x04000000  /* report estimated link audio समय */
#घोषणा SNDRV_PCM_INFO_HAS_LINK_SYNCHRONIZED_ATIME 0x08000000  /* report synchronized audio/प्रणाली समय */

#घोषणा SNDRV_PCM_INFO_DRAIN_TRIGGER	0x40000000		/* पूर्णांकernal kernel flag - trigger in drain */
#घोषणा SNDRV_PCM_INFO_FIFO_IN_FRAMES	0x80000000	/* पूर्णांकernal kernel flag - FIFO size is in frames */

#अगर (__BITS_PER_LONG == 32 && defined(__USE_TIME_BITS64)) || defined __KERNEL__
#घोषणा __SND_STRUCT_TIME64
#पूर्ण_अगर

प्रकार पूर्णांक __bitwise snd_pcm_state_t;
#घोषणा	SNDRV_PCM_STATE_OPEN		((__क्रमce snd_pcm_state_t) 0) /* stream is खोलो */
#घोषणा	SNDRV_PCM_STATE_SETUP		((__क्रमce snd_pcm_state_t) 1) /* stream has a setup */
#घोषणा	SNDRV_PCM_STATE_PREPARED	((__क्रमce snd_pcm_state_t) 2) /* stream is पढ़ोy to start */
#घोषणा	SNDRV_PCM_STATE_RUNNING		((__क्रमce snd_pcm_state_t) 3) /* stream is running */
#घोषणा	SNDRV_PCM_STATE_XRUN		((__क्रमce snd_pcm_state_t) 4) /* stream reached an xrun */
#घोषणा	SNDRV_PCM_STATE_DRAINING	((__क्रमce snd_pcm_state_t) 5) /* stream is draining */
#घोषणा	SNDRV_PCM_STATE_PAUSED		((__क्रमce snd_pcm_state_t) 6) /* stream is छोड़ोd */
#घोषणा	SNDRV_PCM_STATE_SUSPENDED	((__क्रमce snd_pcm_state_t) 7) /* hardware is suspended */
#घोषणा	SNDRV_PCM_STATE_DISCONNECTED	((__क्रमce snd_pcm_state_t) 8) /* hardware is disconnected */
#घोषणा	SNDRV_PCM_STATE_LAST		SNDRV_PCM_STATE_DISCONNECTED

क्रमागत अणु
	SNDRV_PCM_MMAP_OFFSET_DATA = 0x00000000,
	SNDRV_PCM_MMAP_OFFSET_STATUS_OLD = 0x80000000,
	SNDRV_PCM_MMAP_OFFSET_CONTROL_OLD = 0x81000000,
	SNDRV_PCM_MMAP_OFFSET_STATUS_NEW = 0x82000000,
	SNDRV_PCM_MMAP_OFFSET_CONTROL_NEW = 0x83000000,
#अगर_घोषित __SND_STRUCT_TIME64
	SNDRV_PCM_MMAP_OFFSET_STATUS = SNDRV_PCM_MMAP_OFFSET_STATUS_NEW,
	SNDRV_PCM_MMAP_OFFSET_CONTROL = SNDRV_PCM_MMAP_OFFSET_CONTROL_NEW,
#अन्यथा
	SNDRV_PCM_MMAP_OFFSET_STATUS = SNDRV_PCM_MMAP_OFFSET_STATUS_OLD,
	SNDRV_PCM_MMAP_OFFSET_CONTROL = SNDRV_PCM_MMAP_OFFSET_CONTROL_OLD,
#पूर्ण_अगर
पूर्ण;

जोड़ snd_pcm_sync_id अणु
	अचिन्हित अक्षर id[16];
	अचिन्हित लघु id16[8];
	अचिन्हित पूर्णांक id32[4];
पूर्ण;

काष्ठा snd_pcm_info अणु
	अचिन्हित पूर्णांक device;		/* RO/WR (control): device number */
	अचिन्हित पूर्णांक subdevice;		/* RO/WR (control): subdevice number */
	पूर्णांक stream;			/* RO/WR (control): stream direction */
	पूर्णांक card;			/* R: card number */
	अचिन्हित अक्षर id[64];		/* ID (user selectable) */
	अचिन्हित अक्षर name[80];		/* name of this device */
	अचिन्हित अक्षर subname[32];	/* subdevice name */
	पूर्णांक dev_class;			/* SNDRV_PCM_CLASS_* */
	पूर्णांक dev_subclass;		/* SNDRV_PCM_SUBCLASS_* */
	अचिन्हित पूर्णांक subdevices_count;
	अचिन्हित पूर्णांक subdevices_avail;
	जोड़ snd_pcm_sync_id sync;	/* hardware synchronization ID */
	अचिन्हित अक्षर reserved[64];	/* reserved क्रम future... */
पूर्ण;

प्रकार पूर्णांक snd_pcm_hw_param_t;
#घोषणा	SNDRV_PCM_HW_PARAM_ACCESS	0	/* Access type */
#घोषणा	SNDRV_PCM_HW_PARAM_FORMAT	1	/* Format */
#घोषणा	SNDRV_PCM_HW_PARAM_SUBFORMAT	2	/* Subक्रमmat */
#घोषणा	SNDRV_PCM_HW_PARAM_FIRST_MASK	SNDRV_PCM_HW_PARAM_ACCESS
#घोषणा	SNDRV_PCM_HW_PARAM_LAST_MASK	SNDRV_PCM_HW_PARAM_SUBFORMAT

#घोषणा	SNDRV_PCM_HW_PARAM_SAMPLE_BITS	8	/* Bits per sample */
#घोषणा	SNDRV_PCM_HW_PARAM_FRAME_BITS	9	/* Bits per frame */
#घोषणा	SNDRV_PCM_HW_PARAM_CHANNELS	10	/* Channels */
#घोषणा	SNDRV_PCM_HW_PARAM_RATE		11	/* Approx rate */
#घोषणा	SNDRV_PCM_HW_PARAM_PERIOD_TIME	12	/* Approx distance between
						 * पूर्णांकerrupts in us
						 */
#घोषणा	SNDRV_PCM_HW_PARAM_PERIOD_SIZE	13	/* Approx frames between
						 * पूर्णांकerrupts
						 */
#घोषणा	SNDRV_PCM_HW_PARAM_PERIOD_BYTES	14	/* Approx bytes between
						 * पूर्णांकerrupts
						 */
#घोषणा	SNDRV_PCM_HW_PARAM_PERIODS	15	/* Approx पूर्णांकerrupts per
						 * buffer
						 */
#घोषणा	SNDRV_PCM_HW_PARAM_BUFFER_TIME	16	/* Approx duration of buffer
						 * in us
						 */
#घोषणा	SNDRV_PCM_HW_PARAM_BUFFER_SIZE	17	/* Size of buffer in frames */
#घोषणा	SNDRV_PCM_HW_PARAM_BUFFER_BYTES	18	/* Size of buffer in bytes */
#घोषणा	SNDRV_PCM_HW_PARAM_TICK_TIME	19	/* Approx tick duration in us */
#घोषणा	SNDRV_PCM_HW_PARAM_FIRST_INTERVAL	SNDRV_PCM_HW_PARAM_SAMPLE_BITS
#घोषणा	SNDRV_PCM_HW_PARAM_LAST_INTERVAL	SNDRV_PCM_HW_PARAM_TICK_TIME

#घोषणा SNDRV_PCM_HW_PARAMS_NORESAMPLE	(1<<0)	/* aव्योम rate resampling */
#घोषणा SNDRV_PCM_HW_PARAMS_EXPORT_BUFFER	(1<<1)	/* export buffer */
#घोषणा SNDRV_PCM_HW_PARAMS_NO_PERIOD_WAKEUP	(1<<2)	/* disable period wakeups */

काष्ठा snd_पूर्णांकerval अणु
	अचिन्हित पूर्णांक min, max;
	अचिन्हित पूर्णांक खोलोmin:1,
		     खोलोmax:1,
		     पूर्णांकeger:1,
		     empty:1;
पूर्ण;

#घोषणा SNDRV_MASK_MAX	256

काष्ठा snd_mask अणु
	__u32 bits[(SNDRV_MASK_MAX+31)/32];
पूर्ण;

काष्ठा snd_pcm_hw_params अणु
	अचिन्हित पूर्णांक flags;
	काष्ठा snd_mask masks[SNDRV_PCM_HW_PARAM_LAST_MASK -
			       SNDRV_PCM_HW_PARAM_FIRST_MASK + 1];
	काष्ठा snd_mask mres[5];	/* reserved masks */
	काष्ठा snd_पूर्णांकerval पूर्णांकervals[SNDRV_PCM_HW_PARAM_LAST_INTERVAL -
				        SNDRV_PCM_HW_PARAM_FIRST_INTERVAL + 1];
	काष्ठा snd_पूर्णांकerval ires[9];	/* reserved पूर्णांकervals */
	अचिन्हित पूर्णांक rmask;		/* W: requested masks */
	अचिन्हित पूर्णांक cmask;		/* R: changed masks */
	अचिन्हित पूर्णांक info;		/* R: Info flags क्रम वापसed setup */
	अचिन्हित पूर्णांक msbits;		/* R: used most signअगरicant bits */
	अचिन्हित पूर्णांक rate_num;		/* R: rate numerator */
	अचिन्हित पूर्णांक rate_den;		/* R: rate denominator */
	snd_pcm_uframes_t fअगरo_size;	/* R: chip FIFO size in frames */
	अचिन्हित अक्षर reserved[64];	/* reserved क्रम future */
पूर्ण;

क्रमागत अणु
	SNDRV_PCM_TSTAMP_NONE = 0,
	SNDRV_PCM_TSTAMP_ENABLE,
	SNDRV_PCM_TSTAMP_LAST = SNDRV_PCM_TSTAMP_ENABLE,
पूर्ण;

काष्ठा snd_pcm_sw_params अणु
	पूर्णांक tstamp_mode;			/* बारtamp mode */
	अचिन्हित पूर्णांक period_step;
	अचिन्हित पूर्णांक sleep_min;			/* min ticks to sleep */
	snd_pcm_uframes_t avail_min;		/* min avail frames क्रम wakeup */
	snd_pcm_uframes_t xfer_align;		/* obsolete: xfer size need to be a multiple */
	snd_pcm_uframes_t start_threshold;	/* min hw_avail frames क्रम स्वतःmatic start */
	snd_pcm_uframes_t stop_threshold;	/* min avail frames क्रम स्वतःmatic stop */
	snd_pcm_uframes_t silence_threshold;	/* min distance from noise क्रम silence filling */
	snd_pcm_uframes_t silence_size;		/* silence block size */
	snd_pcm_uframes_t boundary;		/* poपूर्णांकers wrap poपूर्णांक */
	अचिन्हित पूर्णांक proto;			/* protocol version */
	अचिन्हित पूर्णांक tstamp_type;		/* बारtamp type (req. proto >= 2.0.12) */
	अचिन्हित अक्षर reserved[56];		/* reserved क्रम future */
पूर्ण;

काष्ठा snd_pcm_channel_info अणु
	अचिन्हित पूर्णांक channel;
	__kernel_off_t offset;		/* mmap offset */
	अचिन्हित पूर्णांक first;		/* offset to first sample in bits */
	अचिन्हित पूर्णांक step;		/* samples distance in bits */
पूर्ण;

क्रमागत अणु
	/*
	 *  first definition क्रम backwards compatibility only,
	 *  maps to wallघड़ी/link समय क्रम HDAudio playback and DEFAULT/DMA समय क्रम everything अन्यथा
	 */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_COMPAT = 0,

	/* बारtamp definitions */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_DEFAULT = 1,           /* DMA समय, reported as per hw_ptr */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK = 2,	           /* link समय reported by sample or wallघड़ी counter, reset on startup */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_ABSOLUTE = 3,	   /* link समय reported by sample or wallघड़ी counter, not reset on startup */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_ESTIMATED = 4,    /* link समय estimated indirectly */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED = 5, /* link समय synchronized with प्रणाली समय */
	SNDRV_PCM_AUDIO_TSTAMP_TYPE_LAST = SNDRV_PCM_AUDIO_TSTAMP_TYPE_LINK_SYNCHRONIZED
पूर्ण;

#अगर_अघोषित __KERNEL__
/* explicit padding aव्योमs incompatibility between i386 and x86-64 */
प्रकार काष्ठा अणु अचिन्हित अक्षर pad[माप(समय_प्रकार) - माप(पूर्णांक)]; पूर्ण __समय_pad;

काष्ठा snd_pcm_status अणु
	snd_pcm_state_t state;		/* stream state */
	__समय_pad pad1;		/* align to बारpec */
	काष्ठा बारpec trigger_tstamp;	/* समय when stream was started/stopped/छोड़ोd */
	काष्ठा बारpec tstamp;		/* reference बारtamp */
	snd_pcm_uframes_t appl_ptr;	/* appl ptr */
	snd_pcm_uframes_t hw_ptr;	/* hw ptr */
	snd_pcm_sframes_t delay;	/* current delay in frames */
	snd_pcm_uframes_t avail;	/* number of frames available */
	snd_pcm_uframes_t avail_max;	/* max frames available on hw since last status */
	snd_pcm_uframes_t overrange;	/* count of ADC (capture) overrange detections from last status */
	snd_pcm_state_t suspended_state; /* suspended stream state */
	__u32 audio_tstamp_data;	 /* needed क्रम 64-bit alignment, used क्रम configs/report to/from userspace */
	काष्ठा बारpec audio_tstamp;	/* sample counter, wall घड़ी, PHC or on-demand sync'ed */
	काष्ठा बारpec driver_tstamp;	/* useful in हाल reference प्रणाली tstamp is reported with delay */
	__u32 audio_tstamp_accuracy;	/* in ns units, only valid अगर indicated in audio_tstamp_data */
	अचिन्हित अक्षर reserved[52-2*माप(काष्ठा बारpec)]; /* must be filled with zero */
पूर्ण;
#पूर्ण_अगर

/*
 * For mmap operations, we need the 64-bit layout, both क्रम compat mode,
 * and क्रम y2038 compatibility. For 64-bit applications, the two definitions
 * are identical, so we keep the traditional version.
 */
#अगर_घोषित __SND_STRUCT_TIME64
#घोषणा __snd_pcm_mmap_status64		snd_pcm_mmap_status
#घोषणा __snd_pcm_mmap_control64	snd_pcm_mmap_control
#घोषणा __snd_pcm_sync_ptr64		snd_pcm_sync_ptr
#अगर_घोषित __KERNEL__
#घोषणा __snd_बारpec64		__kernel_बारpec
#अन्यथा
#घोषणा __snd_बारpec64		बारpec
#पूर्ण_अगर
काष्ठा __snd_बारpec अणु
	__s32 tv_sec;
	__s32 tv_nsec;
पूर्ण;
#अन्यथा
#घोषणा __snd_pcm_mmap_status		snd_pcm_mmap_status
#घोषणा __snd_pcm_mmap_control		snd_pcm_mmap_control
#घोषणा __snd_pcm_sync_ptr		snd_pcm_sync_ptr
#घोषणा __snd_बारpec			बारpec
काष्ठा __snd_बारpec64 अणु
	__s64 tv_sec;
	__s64 tv_nsec;
पूर्ण;

#पूर्ण_अगर

काष्ठा __snd_pcm_mmap_status अणु
	snd_pcm_state_t state;		/* RO: state - SNDRV_PCM_STATE_XXXX */
	पूर्णांक pad1;			/* Needed क्रम 64 bit alignment */
	snd_pcm_uframes_t hw_ptr;	/* RO: hw ptr (0...boundary-1) */
	काष्ठा __snd_बारpec tstamp;	/* Timestamp */
	snd_pcm_state_t suspended_state; /* RO: suspended stream state */
	काष्ठा __snd_बारpec audio_tstamp; /* from sample counter or wall घड़ी */
पूर्ण;

काष्ठा __snd_pcm_mmap_control अणु
	snd_pcm_uframes_t appl_ptr;	/* RW: appl ptr (0...boundary-1) */
	snd_pcm_uframes_t avail_min;	/* RW: min available frames क्रम wakeup */
पूर्ण;

#घोषणा SNDRV_PCM_SYNC_PTR_HWSYNC	(1<<0)	/* execute hwsync */
#घोषणा SNDRV_PCM_SYNC_PTR_APPL		(1<<1)	/* get appl_ptr from driver (r/w op) */
#घोषणा SNDRV_PCM_SYNC_PTR_AVAIL_MIN	(1<<2)	/* get avail_min from driver */

काष्ठा __snd_pcm_sync_ptr अणु
	अचिन्हित पूर्णांक flags;
	जोड़ अणु
		काष्ठा __snd_pcm_mmap_status status;
		अचिन्हित अक्षर reserved[64];
	पूर्ण s;
	जोड़ अणु
		काष्ठा __snd_pcm_mmap_control control;
		अचिन्हित अक्षर reserved[64];
	पूर्ण c;
पूर्ण;

#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __BIG_ENDIAN : defined(__BIG_ENDIAN)
प्रकार अक्षर __pad_beक्रमe_uframe[माप(__u64) - माप(snd_pcm_uframes_t)];
प्रकार अक्षर __pad_after_uframe[0];
#पूर्ण_अगर

#अगर defined(__BYTE_ORDER) ? __BYTE_ORDER == __LITTLE_ENDIAN : defined(__LITTLE_ENDIAN)
प्रकार अक्षर __pad_beक्रमe_uframe[0];
प्रकार अक्षर __pad_after_uframe[माप(__u64) - माप(snd_pcm_uframes_t)];
#पूर्ण_अगर

काष्ठा __snd_pcm_mmap_status64 अणु
	snd_pcm_state_t state;		/* RO: state - SNDRV_PCM_STATE_XXXX */
	__u32 pad1;			/* Needed क्रम 64 bit alignment */
	__pad_beक्रमe_uframe __pad1;
	snd_pcm_uframes_t hw_ptr;	/* RO: hw ptr (0...boundary-1) */
	__pad_after_uframe __pad2;
	काष्ठा __snd_बारpec64 tstamp;	/* Timestamp */
	snd_pcm_state_t suspended_state;/* RO: suspended stream state */
	__u32 pad3;			/* Needed क्रम 64 bit alignment */
	काष्ठा __snd_बारpec64 audio_tstamp; /* sample counter or wall घड़ी */
पूर्ण;

काष्ठा __snd_pcm_mmap_control64 अणु
	__pad_beक्रमe_uframe __pad1;
	snd_pcm_uframes_t appl_ptr;	 /* RW: appl ptr (0...boundary-1) */
	__pad_beक्रमe_uframe __pad2;

	__pad_beक्रमe_uframe __pad3;
	snd_pcm_uframes_t  avail_min;	 /* RW: min available frames क्रम wakeup */
	__pad_after_uframe __pad4;
पूर्ण;

काष्ठा __snd_pcm_sync_ptr64 अणु
	__u32 flags;
	__u32 pad1;
	जोड़ अणु
		काष्ठा __snd_pcm_mmap_status64 status;
		अचिन्हित अक्षर reserved[64];
	पूर्ण s;
	जोड़ अणु
		काष्ठा __snd_pcm_mmap_control64 control;
		अचिन्हित अक्षर reserved[64];
	पूर्ण c;
पूर्ण;

काष्ठा snd_xferi अणु
	snd_pcm_sframes_t result;
	व्योम __user *buf;
	snd_pcm_uframes_t frames;
पूर्ण;

काष्ठा snd_xfern अणु
	snd_pcm_sframes_t result;
	व्योम __user * __user *bufs;
	snd_pcm_uframes_t frames;
पूर्ण;

क्रमागत अणु
	SNDRV_PCM_TSTAMP_TYPE_GETTIMखातापूर्णDAY = 0,	/* समय_लोofday equivalent */
	SNDRV_PCM_TSTAMP_TYPE_MONOTONIC,	/* posix_घड़ी_monotonic equivalent */
	SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW,    /* monotonic_raw (no NTP) */
	SNDRV_PCM_TSTAMP_TYPE_LAST = SNDRV_PCM_TSTAMP_TYPE_MONOTONIC_RAW,
पूर्ण;

/* channel positions */
क्रमागत अणु
	SNDRV_CHMAP_UNKNOWN = 0,
	SNDRV_CHMAP_NA,		/* N/A, silent */
	SNDRV_CHMAP_MONO,	/* mono stream */
	/* this follows the alsa-lib mixer channel value + 3 */
	SNDRV_CHMAP_FL,		/* front left */
	SNDRV_CHMAP_FR,		/* front right */
	SNDRV_CHMAP_RL,		/* rear left */
	SNDRV_CHMAP_RR,		/* rear right */
	SNDRV_CHMAP_FC,		/* front center */
	SNDRV_CHMAP_LFE,	/* LFE */
	SNDRV_CHMAP_SL,		/* side left */
	SNDRV_CHMAP_SR,		/* side right */
	SNDRV_CHMAP_RC,		/* rear center */
	/* new definitions */
	SNDRV_CHMAP_FLC,	/* front left center */
	SNDRV_CHMAP_FRC,	/* front right center */
	SNDRV_CHMAP_RLC,	/* rear left center */
	SNDRV_CHMAP_RRC,	/* rear right center */
	SNDRV_CHMAP_FLW,	/* front left wide */
	SNDRV_CHMAP_FRW,	/* front right wide */
	SNDRV_CHMAP_FLH,	/* front left high */
	SNDRV_CHMAP_FCH,	/* front center high */
	SNDRV_CHMAP_FRH,	/* front right high */
	SNDRV_CHMAP_TC,		/* top center */
	SNDRV_CHMAP_TFL,	/* top front left */
	SNDRV_CHMAP_TFR,	/* top front right */
	SNDRV_CHMAP_TFC,	/* top front center */
	SNDRV_CHMAP_TRL,	/* top rear left */
	SNDRV_CHMAP_TRR,	/* top rear right */
	SNDRV_CHMAP_TRC,	/* top rear center */
	/* new definitions क्रम UAC2 */
	SNDRV_CHMAP_TFLC,	/* top front left center */
	SNDRV_CHMAP_TFRC,	/* top front right center */
	SNDRV_CHMAP_TSL,	/* top side left */
	SNDRV_CHMAP_TSR,	/* top side right */
	SNDRV_CHMAP_LLFE,	/* left LFE */
	SNDRV_CHMAP_RLFE,	/* right LFE */
	SNDRV_CHMAP_BC,		/* bottom center */
	SNDRV_CHMAP_BLC,	/* bottom left center */
	SNDRV_CHMAP_BRC,	/* bottom right center */
	SNDRV_CHMAP_LAST = SNDRV_CHMAP_BRC,
पूर्ण;

#घोषणा SNDRV_CHMAP_POSITION_MASK	0xffff
#घोषणा SNDRV_CHMAP_PHASE_INVERSE	(0x01 << 16)
#घोषणा SNDRV_CHMAP_DRIVER_SPEC		(0x02 << 16)

#घोषणा SNDRV_PCM_IOCTL_PVERSION	_IOR('A', 0x00, पूर्णांक)
#घोषणा SNDRV_PCM_IOCTL_INFO		_IOR('A', 0x01, काष्ठा snd_pcm_info)
#घोषणा SNDRV_PCM_IOCTL_TSTAMP		_IOW('A', 0x02, पूर्णांक)
#घोषणा SNDRV_PCM_IOCTL_TTSTAMP		_IOW('A', 0x03, पूर्णांक)
#घोषणा SNDRV_PCM_IOCTL_USER_PVERSION	_IOW('A', 0x04, पूर्णांक)
#घोषणा SNDRV_PCM_IOCTL_HW_REFINE	_IOWR('A', 0x10, काष्ठा snd_pcm_hw_params)
#घोषणा SNDRV_PCM_IOCTL_HW_PARAMS	_IOWR('A', 0x11, काष्ठा snd_pcm_hw_params)
#घोषणा SNDRV_PCM_IOCTL_HW_FREE		_IO('A', 0x12)
#घोषणा SNDRV_PCM_IOCTL_SW_PARAMS	_IOWR('A', 0x13, काष्ठा snd_pcm_sw_params)
#घोषणा SNDRV_PCM_IOCTL_STATUS		_IOR('A', 0x20, काष्ठा snd_pcm_status)
#घोषणा SNDRV_PCM_IOCTL_DELAY		_IOR('A', 0x21, snd_pcm_sframes_t)
#घोषणा SNDRV_PCM_IOCTL_HWSYNC		_IO('A', 0x22)
#घोषणा __SNDRV_PCM_IOCTL_SYNC_PTR	_IOWR('A', 0x23, काष्ठा __snd_pcm_sync_ptr)
#घोषणा __SNDRV_PCM_IOCTL_SYNC_PTR64	_IOWR('A', 0x23, काष्ठा __snd_pcm_sync_ptr64)
#घोषणा SNDRV_PCM_IOCTL_SYNC_PTR	_IOWR('A', 0x23, काष्ठा snd_pcm_sync_ptr)
#घोषणा SNDRV_PCM_IOCTL_STATUS_EXT	_IOWR('A', 0x24, काष्ठा snd_pcm_status)
#घोषणा SNDRV_PCM_IOCTL_CHANNEL_INFO	_IOR('A', 0x32, काष्ठा snd_pcm_channel_info)
#घोषणा SNDRV_PCM_IOCTL_PREPARE		_IO('A', 0x40)
#घोषणा SNDRV_PCM_IOCTL_RESET		_IO('A', 0x41)
#घोषणा SNDRV_PCM_IOCTL_START		_IO('A', 0x42)
#घोषणा SNDRV_PCM_IOCTL_DROP		_IO('A', 0x43)
#घोषणा SNDRV_PCM_IOCTL_DRAIN		_IO('A', 0x44)
#घोषणा SNDRV_PCM_IOCTL_PAUSE		_IOW('A', 0x45, पूर्णांक)
#घोषणा SNDRV_PCM_IOCTL_REWIND		_IOW('A', 0x46, snd_pcm_uframes_t)
#घोषणा SNDRV_PCM_IOCTL_RESUME		_IO('A', 0x47)
#घोषणा SNDRV_PCM_IOCTL_XRUN		_IO('A', 0x48)
#घोषणा SNDRV_PCM_IOCTL_FORWARD		_IOW('A', 0x49, snd_pcm_uframes_t)
#घोषणा SNDRV_PCM_IOCTL_WRITEI_FRAMES	_IOW('A', 0x50, काष्ठा snd_xferi)
#घोषणा SNDRV_PCM_IOCTL_READI_FRAMES	_IOR('A', 0x51, काष्ठा snd_xferi)
#घोषणा SNDRV_PCM_IOCTL_WRITEN_FRAMES	_IOW('A', 0x52, काष्ठा snd_xfern)
#घोषणा SNDRV_PCM_IOCTL_READN_FRAMES	_IOR('A', 0x53, काष्ठा snd_xfern)
#घोषणा SNDRV_PCM_IOCTL_LINK		_IOW('A', 0x60, पूर्णांक)
#घोषणा SNDRV_PCM_IOCTL_UNLINK		_IO('A', 0x61)

/*****************************************************************************
 *                                                                           *
 *                            MIDI v1.0 पूर्णांकerface                            *
 *                                                                           *
 *****************************************************************************/

/*
 *  Raw MIDI section - /dev/snd/midi??
 */

#घोषणा SNDRV_RAWMIDI_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 1)

क्रमागत अणु
	SNDRV_RAWMIDI_STREAM_OUTPUT = 0,
	SNDRV_RAWMIDI_STREAM_INPUT,
	SNDRV_RAWMIDI_STREAM_LAST = SNDRV_RAWMIDI_STREAM_INPUT,
पूर्ण;

#घोषणा SNDRV_RAWMIDI_INFO_OUTPUT		0x00000001
#घोषणा SNDRV_RAWMIDI_INFO_INPUT		0x00000002
#घोषणा SNDRV_RAWMIDI_INFO_DUPLEX		0x00000004

काष्ठा snd_rawmidi_info अणु
	अचिन्हित पूर्णांक device;		/* RO/WR (control): device number */
	अचिन्हित पूर्णांक subdevice;		/* RO/WR (control): subdevice number */
	पूर्णांक stream;			/* WR: stream */
	पूर्णांक card;			/* R: card number */
	अचिन्हित पूर्णांक flags;		/* SNDRV_RAWMIDI_INFO_XXXX */
	अचिन्हित अक्षर id[64];		/* ID (user selectable) */
	अचिन्हित अक्षर name[80];		/* name of device */
	अचिन्हित अक्षर subname[32];	/* name of active or selected subdevice */
	अचिन्हित पूर्णांक subdevices_count;
	अचिन्हित पूर्णांक subdevices_avail;
	अचिन्हित अक्षर reserved[64];	/* reserved क्रम future use */
पूर्ण;

काष्ठा snd_rawmidi_params अणु
	पूर्णांक stream;
	माप_प्रकार buffer_size;		/* queue size in bytes */
	माप_प्रकार avail_min;		/* minimum avail bytes क्रम wakeup */
	अचिन्हित पूर्णांक no_active_sensing: 1; /* करो not send active sensing byte in बंद() */
	अचिन्हित अक्षर reserved[16];	/* reserved क्रम future use */
पूर्ण;

#अगर_अघोषित __KERNEL__
काष्ठा snd_rawmidi_status अणु
	पूर्णांक stream;
	__समय_pad pad1;
	काष्ठा बारpec tstamp;		/* Timestamp */
	माप_प्रकार avail;			/* available bytes */
	माप_प्रकार xruns;			/* count of overruns since last status (in bytes) */
	अचिन्हित अक्षर reserved[16];	/* reserved क्रम future use */
पूर्ण;
#पूर्ण_अगर

#घोषणा SNDRV_RAWMIDI_IOCTL_PVERSION	_IOR('W', 0x00, पूर्णांक)
#घोषणा SNDRV_RAWMIDI_IOCTL_INFO	_IOR('W', 0x01, काष्ठा snd_rawmidi_info)
#घोषणा SNDRV_RAWMIDI_IOCTL_PARAMS	_IOWR('W', 0x10, काष्ठा snd_rawmidi_params)
#घोषणा SNDRV_RAWMIDI_IOCTL_STATUS	_IOWR('W', 0x20, काष्ठा snd_rawmidi_status)
#घोषणा SNDRV_RAWMIDI_IOCTL_DROP	_IOW('W', 0x30, पूर्णांक)
#घोषणा SNDRV_RAWMIDI_IOCTL_DRAIN	_IOW('W', 0x31, पूर्णांक)

/*
 *  Timer section - /dev/snd/समयr
 */

#घोषणा SNDRV_TIMER_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 7)

क्रमागत अणु
	SNDRV_TIMER_CLASS_NONE = -1,
	SNDRV_TIMER_CLASS_SLAVE = 0,
	SNDRV_TIMER_CLASS_GLOBAL,
	SNDRV_TIMER_CLASS_CARD,
	SNDRV_TIMER_CLASS_PCM,
	SNDRV_TIMER_CLASS_LAST = SNDRV_TIMER_CLASS_PCM,
पूर्ण;

/* slave समयr classes */
क्रमागत अणु
	SNDRV_TIMER_SCLASS_NONE = 0,
	SNDRV_TIMER_SCLASS_APPLICATION,
	SNDRV_TIMER_SCLASS_SEQUENCER,		/* alias */
	SNDRV_TIMER_SCLASS_OSS_SEQUENCER,	/* alias */
	SNDRV_TIMER_SCLASS_LAST = SNDRV_TIMER_SCLASS_OSS_SEQUENCER,
पूर्ण;

/* global समयrs (device member) */
#घोषणा SNDRV_TIMER_GLOBAL_SYSTEM	0
#घोषणा SNDRV_TIMER_GLOBAL_RTC		1	/* unused */
#घोषणा SNDRV_TIMER_GLOBAL_HPET		2
#घोषणा SNDRV_TIMER_GLOBAL_HRTIMER	3

/* info flags */
#घोषणा SNDRV_TIMER_FLG_SLAVE		(1<<0)	/* cannot be controlled */

काष्ठा snd_समयr_id अणु
	पूर्णांक dev_class;
	पूर्णांक dev_sclass;
	पूर्णांक card;
	पूर्णांक device;
	पूर्णांक subdevice;
पूर्ण;

काष्ठा snd_समयr_ginfo अणु
	काष्ठा snd_समयr_id tid;	/* requested समयr ID */
	अचिन्हित पूर्णांक flags;		/* समयr flags - SNDRV_TIMER_FLG_* */
	पूर्णांक card;			/* card number */
	अचिन्हित अक्षर id[64];		/* समयr identअगरication */
	अचिन्हित अक्षर name[80];		/* समयr name */
	अचिन्हित दीर्घ reserved0;	/* reserved क्रम future use */
	अचिन्हित दीर्घ resolution;	/* average period resolution in ns */
	अचिन्हित दीर्घ resolution_min;	/* minimal period resolution in ns */
	अचिन्हित दीर्घ resolution_max;	/* maximal period resolution in ns */
	अचिन्हित पूर्णांक clients;		/* active समयr clients */
	अचिन्हित अक्षर reserved[32];
पूर्ण;

काष्ठा snd_समयr_gparams अणु
	काष्ठा snd_समयr_id tid;	/* requested समयr ID */
	अचिन्हित दीर्घ period_num;	/* requested precise period duration (in seconds) - numerator */
	अचिन्हित दीर्घ period_den;	/* requested precise period duration (in seconds) - denominator */
	अचिन्हित अक्षर reserved[32];
पूर्ण;

काष्ठा snd_समयr_gstatus अणु
	काष्ठा snd_समयr_id tid;	/* requested समयr ID */
	अचिन्हित दीर्घ resolution;	/* current period resolution in ns */
	अचिन्हित दीर्घ resolution_num;	/* precise current period resolution (in seconds) - numerator */
	अचिन्हित दीर्घ resolution_den;	/* precise current period resolution (in seconds) - denominator */
	अचिन्हित अक्षर reserved[32];
पूर्ण;

काष्ठा snd_समयr_select अणु
	काष्ठा snd_समयr_id id;	/* bind to समयr ID */
	अचिन्हित अक्षर reserved[32];	/* reserved */
पूर्ण;

काष्ठा snd_समयr_info अणु
	अचिन्हित पूर्णांक flags;		/* समयr flags - SNDRV_TIMER_FLG_* */
	पूर्णांक card;			/* card number */
	अचिन्हित अक्षर id[64];		/* समयr identअगरicator */
	अचिन्हित अक्षर name[80];		/* समयr name */
	अचिन्हित दीर्घ reserved0;	/* reserved क्रम future use */
	अचिन्हित दीर्घ resolution;	/* average period resolution in ns */
	अचिन्हित अक्षर reserved[64];	/* reserved */
पूर्ण;

#घोषणा SNDRV_TIMER_PSFLG_AUTO		(1<<0)	/* स्वतः start, otherwise one-shot */
#घोषणा SNDRV_TIMER_PSFLG_EXCLUSIVE	(1<<1)	/* exclusive use, precise start/stop/छोड़ो/जारी */
#घोषणा SNDRV_TIMER_PSFLG_EARLY_EVENT	(1<<2)	/* ग_लिखो early event to the poll queue */

काष्ठा snd_समयr_params अणु
	अचिन्हित पूर्णांक flags;		/* flags - SNDRV_TIMER_PSFLG_* */
	अचिन्हित पूर्णांक ticks;		/* requested resolution in ticks */
	अचिन्हित पूर्णांक queue_size;	/* total size of queue (32-1024) */
	अचिन्हित पूर्णांक reserved0;		/* reserved, was: failure locations */
	अचिन्हित पूर्णांक filter;		/* event filter (biपंचांगask of SNDRV_TIMER_EVENT_*) */
	अचिन्हित अक्षर reserved[60];	/* reserved */
पूर्ण;

#अगर_अघोषित __KERNEL__
काष्ठा snd_समयr_status अणु
	काष्ठा बारpec tstamp;		/* Timestamp - last update */
	अचिन्हित पूर्णांक resolution;	/* current period resolution in ns */
	अचिन्हित पूर्णांक lost;		/* counter of master tick lost */
	अचिन्हित पूर्णांक overrun;		/* count of पढ़ो queue overruns */
	अचिन्हित पूर्णांक queue;		/* used queue size */
	अचिन्हित अक्षर reserved[64];	/* reserved */
पूर्ण;
#पूर्ण_अगर

#घोषणा SNDRV_TIMER_IOCTL_PVERSION	_IOR('T', 0x00, पूर्णांक)
#घोषणा SNDRV_TIMER_IOCTL_NEXT_DEVICE	_IOWR('T', 0x01, काष्ठा snd_समयr_id)
#घोषणा SNDRV_TIMER_IOCTL_TREAD_OLD	_IOW('T', 0x02, पूर्णांक)
#घोषणा SNDRV_TIMER_IOCTL_GINFO		_IOWR('T', 0x03, काष्ठा snd_समयr_ginfo)
#घोषणा SNDRV_TIMER_IOCTL_GPARAMS	_IOW('T', 0x04, काष्ठा snd_समयr_gparams)
#घोषणा SNDRV_TIMER_IOCTL_GSTATUS	_IOWR('T', 0x05, काष्ठा snd_समयr_gstatus)
#घोषणा SNDRV_TIMER_IOCTL_SELECT	_IOW('T', 0x10, काष्ठा snd_समयr_select)
#घोषणा SNDRV_TIMER_IOCTL_INFO		_IOR('T', 0x11, काष्ठा snd_समयr_info)
#घोषणा SNDRV_TIMER_IOCTL_PARAMS	_IOW('T', 0x12, काष्ठा snd_समयr_params)
#घोषणा SNDRV_TIMER_IOCTL_STATUS	_IOR('T', 0x14, काष्ठा snd_समयr_status)
/* The following four ioctls are changed since 1.0.9 due to confliction */
#घोषणा SNDRV_TIMER_IOCTL_START		_IO('T', 0xa0)
#घोषणा SNDRV_TIMER_IOCTL_STOP		_IO('T', 0xa1)
#घोषणा SNDRV_TIMER_IOCTL_CONTINUE	_IO('T', 0xa2)
#घोषणा SNDRV_TIMER_IOCTL_PAUSE		_IO('T', 0xa3)
#घोषणा SNDRV_TIMER_IOCTL_TREAD64	_IOW('T', 0xa4, पूर्णांक)

#अगर __BITS_PER_LONG == 64
#घोषणा SNDRV_TIMER_IOCTL_TREAD SNDRV_TIMER_IOCTL_TREAD_OLD
#अन्यथा
#घोषणा SNDRV_TIMER_IOCTL_TREAD ((माप(__kernel_दीर्घ_t) >= माप(समय_प्रकार)) ? \
				 SNDRV_TIMER_IOCTL_TREAD_OLD : \
				 SNDRV_TIMER_IOCTL_TREAD64)
#पूर्ण_अगर

काष्ठा snd_समयr_पढ़ो अणु
	अचिन्हित पूर्णांक resolution;
	अचिन्हित पूर्णांक ticks;
पूर्ण;

क्रमागत अणु
	SNDRV_TIMER_EVENT_RESOLUTION = 0,	/* val = resolution in ns */
	SNDRV_TIMER_EVENT_TICK,			/* val = ticks */
	SNDRV_TIMER_EVENT_START,		/* val = resolution in ns */
	SNDRV_TIMER_EVENT_STOP,			/* val = 0 */
	SNDRV_TIMER_EVENT_CONTINUE,		/* val = resolution in ns */
	SNDRV_TIMER_EVENT_PAUSE,		/* val = 0 */
	SNDRV_TIMER_EVENT_EARLY,		/* val = 0, early event */
	SNDRV_TIMER_EVENT_SUSPEND,		/* val = 0 */
	SNDRV_TIMER_EVENT_RESUME,		/* val = resolution in ns */
	/* master समयr events क्रम slave समयr instances */
	SNDRV_TIMER_EVENT_MSTART = SNDRV_TIMER_EVENT_START + 10,
	SNDRV_TIMER_EVENT_MSTOP = SNDRV_TIMER_EVENT_STOP + 10,
	SNDRV_TIMER_EVENT_MCONTINUE = SNDRV_TIMER_EVENT_CONTINUE + 10,
	SNDRV_TIMER_EVENT_MPAUSE = SNDRV_TIMER_EVENT_PAUSE + 10,
	SNDRV_TIMER_EVENT_MSUSPEND = SNDRV_TIMER_EVENT_SUSPEND + 10,
	SNDRV_TIMER_EVENT_MRESUME = SNDRV_TIMER_EVENT_RESUME + 10,
पूर्ण;

#अगर_अघोषित __KERNEL__
काष्ठा snd_समयr_tपढ़ो अणु
	पूर्णांक event;
	__समय_pad pad1;
	काष्ठा बारpec tstamp;
	अचिन्हित पूर्णांक val;
	__समय_pad pad2;
पूर्ण;
#पूर्ण_अगर

/****************************************************************************
 *                                                                          *
 *        Section क्रम driver control पूर्णांकerface - /dev/snd/control?          *
 *                                                                          *
 ****************************************************************************/

#घोषणा SNDRV_CTL_VERSION		SNDRV_PROTOCOL_VERSION(2, 0, 8)

काष्ठा snd_ctl_card_info अणु
	पूर्णांक card;			/* card number */
	पूर्णांक pad;			/* reserved क्रम future (was type) */
	अचिन्हित अक्षर id[16];		/* ID of card (user selectable) */
	अचिन्हित अक्षर driver[16];	/* Driver name */
	अचिन्हित अक्षर name[32];		/* Short name of soundcard */
	अचिन्हित अक्षर दीर्घname[80];	/* name + info text about soundcard */
	अचिन्हित अक्षर reserved_[16];	/* reserved क्रम future (was ID of mixer) */
	अचिन्हित अक्षर mixername[80];	/* visual mixer identअगरication */
	अचिन्हित अक्षर components[128];	/* card components / fine identअगरication, delimited with one space (AC97 etc..) */
पूर्ण;

प्रकार पूर्णांक __bitwise snd_ctl_elem_type_t;
#घोषणा	SNDRV_CTL_ELEM_TYPE_NONE	((__क्रमce snd_ctl_elem_type_t) 0) /* invalid */
#घोषणा	SNDRV_CTL_ELEM_TYPE_BOOLEAN	((__क्रमce snd_ctl_elem_type_t) 1) /* boolean type */
#घोषणा	SNDRV_CTL_ELEM_TYPE_INTEGER	((__क्रमce snd_ctl_elem_type_t) 2) /* पूर्णांकeger type */
#घोषणा	SNDRV_CTL_ELEM_TYPE_ENUMERATED	((__क्रमce snd_ctl_elem_type_t) 3) /* क्रमागतerated type */
#घोषणा	SNDRV_CTL_ELEM_TYPE_BYTES	((__क्रमce snd_ctl_elem_type_t) 4) /* byte array */
#घोषणा	SNDRV_CTL_ELEM_TYPE_IEC958	((__क्रमce snd_ctl_elem_type_t) 5) /* IEC958 (S/PDIF) setup */
#घोषणा	SNDRV_CTL_ELEM_TYPE_INTEGER64	((__क्रमce snd_ctl_elem_type_t) 6) /* 64-bit पूर्णांकeger type */
#घोषणा	SNDRV_CTL_ELEM_TYPE_LAST	SNDRV_CTL_ELEM_TYPE_INTEGER64

प्रकार पूर्णांक __bitwise snd_ctl_elem_अगरace_t;
#घोषणा	SNDRV_CTL_ELEM_IFACE_CARD	((__क्रमce snd_ctl_elem_अगरace_t) 0) /* global control */
#घोषणा	SNDRV_CTL_ELEM_IFACE_HWDEP	((__क्रमce snd_ctl_elem_अगरace_t) 1) /* hardware dependent device */
#घोषणा	SNDRV_CTL_ELEM_IFACE_MIXER	((__क्रमce snd_ctl_elem_अगरace_t) 2) /* भव mixer device */
#घोषणा	SNDRV_CTL_ELEM_IFACE_PCM	((__क्रमce snd_ctl_elem_अगरace_t) 3) /* PCM device */
#घोषणा	SNDRV_CTL_ELEM_IFACE_RAWMIDI	((__क्रमce snd_ctl_elem_अगरace_t) 4) /* RawMidi device */
#घोषणा	SNDRV_CTL_ELEM_IFACE_TIMER	((__क्रमce snd_ctl_elem_अगरace_t) 5) /* समयr device */
#घोषणा	SNDRV_CTL_ELEM_IFACE_SEQUENCER	((__क्रमce snd_ctl_elem_अगरace_t) 6) /* sequencer client */
#घोषणा	SNDRV_CTL_ELEM_IFACE_LAST	SNDRV_CTL_ELEM_IFACE_SEQUENCER

#घोषणा SNDRV_CTL_ELEM_ACCESS_READ		(1<<0)
#घोषणा SNDRV_CTL_ELEM_ACCESS_WRITE		(1<<1)
#घोषणा SNDRV_CTL_ELEM_ACCESS_READWRITE		(SNDRV_CTL_ELEM_ACCESS_READ|SNDRV_CTL_ELEM_ACCESS_WRITE)
#घोषणा SNDRV_CTL_ELEM_ACCESS_VOLATILE		(1<<2)	/* control value may be changed without a notअगरication */
// (1 << 3) is unused.
#घोषणा SNDRV_CTL_ELEM_ACCESS_TLV_READ		(1<<4)	/* TLV पढ़ो is possible */
#घोषणा SNDRV_CTL_ELEM_ACCESS_TLV_WRITE		(1<<5)	/* TLV ग_लिखो is possible */
#घोषणा SNDRV_CTL_ELEM_ACCESS_TLV_READWRITE	(SNDRV_CTL_ELEM_ACCESS_TLV_READ|SNDRV_CTL_ELEM_ACCESS_TLV_WRITE)
#घोषणा SNDRV_CTL_ELEM_ACCESS_TLV_COMMAND	(1<<6)	/* TLV command is possible */
#घोषणा SNDRV_CTL_ELEM_ACCESS_INACTIVE		(1<<8)	/* control करोes actually nothing, but may be updated */
#घोषणा SNDRV_CTL_ELEM_ACCESS_LOCK		(1<<9)	/* ग_लिखो lock */
#घोषणा SNDRV_CTL_ELEM_ACCESS_OWNER		(1<<10)	/* ग_लिखो lock owner */
#घोषणा SNDRV_CTL_ELEM_ACCESS_TLV_CALLBACK	(1<<28)	/* kernel use a TLV callback */
#घोषणा SNDRV_CTL_ELEM_ACCESS_USER		(1<<29) /* user space element */
/* bits 30 and 31 are obsoleted (क्रम indirect access) */

/* क्रम further details see the ACPI and PCI घातer management specअगरication */
#घोषणा SNDRV_CTL_POWER_D0		0x0000	/* full On */
#घोषणा SNDRV_CTL_POWER_D1		0x0100	/* partial On */
#घोषणा SNDRV_CTL_POWER_D2		0x0200	/* partial On */
#घोषणा SNDRV_CTL_POWER_D3		0x0300	/* Off */
#घोषणा SNDRV_CTL_POWER_D3hot		(SNDRV_CTL_POWER_D3|0x0000)	/* Off, with घातer */
#घोषणा SNDRV_CTL_POWER_D3cold		(SNDRV_CTL_POWER_D3|0x0001)	/* Off, without घातer */

#घोषणा SNDRV_CTL_ELEM_ID_NAME_MAXLEN	44

काष्ठा snd_ctl_elem_id अणु
	अचिन्हित पूर्णांक numid;		/* numeric identअगरier, zero = invalid */
	snd_ctl_elem_अगरace_t अगरace;	/* पूर्णांकerface identअगरier */
	अचिन्हित पूर्णांक device;		/* device/client number */
	अचिन्हित पूर्णांक subdevice;		/* subdevice (substream) number */
	अचिन्हित अक्षर name[SNDRV_CTL_ELEM_ID_NAME_MAXLEN];		/* ASCII name of item */
	अचिन्हित पूर्णांक index;		/* index of item */
पूर्ण;

काष्ठा snd_ctl_elem_list अणु
	अचिन्हित पूर्णांक offset;		/* W: first element ID to get */
	अचिन्हित पूर्णांक space;		/* W: count of element IDs to get */
	अचिन्हित पूर्णांक used;		/* R: count of element IDs set */
	अचिन्हित पूर्णांक count;		/* R: count of all elements */
	काष्ठा snd_ctl_elem_id __user *pids; /* R: IDs */
	अचिन्हित अक्षर reserved[50];
पूर्ण;

काष्ठा snd_ctl_elem_info अणु
	काष्ठा snd_ctl_elem_id id;	/* W: element ID */
	snd_ctl_elem_type_t type;	/* R: value type - SNDRV_CTL_ELEM_TYPE_* */
	अचिन्हित पूर्णांक access;		/* R: value access (biपंचांगask) - SNDRV_CTL_ELEM_ACCESS_* */
	अचिन्हित पूर्णांक count;		/* count of values */
	__kernel_pid_t owner;		/* owner's PID of this control */
	जोड़ अणु
		काष्ठा अणु
			दीर्घ min;		/* R: minimum value */
			दीर्घ max;		/* R: maximum value */
			दीर्घ step;		/* R: step (0 variable) */
		पूर्ण पूर्णांकeger;
		काष्ठा अणु
			दीर्घ दीर्घ min;		/* R: minimum value */
			दीर्घ दीर्घ max;		/* R: maximum value */
			दीर्घ दीर्घ step;		/* R: step (0 variable) */
		पूर्ण पूर्णांकeger64;
		काष्ठा अणु
			अचिन्हित पूर्णांक items;	/* R: number of items */
			अचिन्हित पूर्णांक item;	/* W: item number */
			अक्षर name[64];		/* R: value name */
			__u64 names_ptr;	/* W: names list (ELEM_ADD only) */
			अचिन्हित पूर्णांक names_length;
		पूर्ण क्रमागतerated;
		अचिन्हित अक्षर reserved[128];
	पूर्ण value;
	अचिन्हित अक्षर reserved[64];
पूर्ण;

काष्ठा snd_ctl_elem_value अणु
	काष्ठा snd_ctl_elem_id id;	/* W: element ID */
	अचिन्हित पूर्णांक indirect: 1;	/* W: indirect access - obsoleted */
	जोड़ अणु
		जोड़ अणु
			दीर्घ value[128];
			दीर्घ *value_ptr;	/* obsoleted */
		पूर्ण पूर्णांकeger;
		जोड़ अणु
			दीर्घ दीर्घ value[64];
			दीर्घ दीर्घ *value_ptr;	/* obsoleted */
		पूर्ण पूर्णांकeger64;
		जोड़ अणु
			अचिन्हित पूर्णांक item[128];
			अचिन्हित पूर्णांक *item_ptr;	/* obsoleted */
		पूर्ण क्रमागतerated;
		जोड़ अणु
			अचिन्हित अक्षर data[512];
			अचिन्हित अक्षर *data_ptr;	/* obsoleted */
		पूर्ण bytes;
		काष्ठा snd_aes_iec958 iec958;
	पूर्ण value;		/* RO */
	अचिन्हित अक्षर reserved[128];
पूर्ण;

काष्ठा snd_ctl_tlv अणु
	अचिन्हित पूर्णांक numid;	/* control element numeric identअगरication */
	अचिन्हित पूर्णांक length;	/* in bytes aligned to 4 */
	अचिन्हित पूर्णांक tlv[0];	/* first TLV */
पूर्ण;

#घोषणा SNDRV_CTL_IOCTL_PVERSION	_IOR('U', 0x00, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_CARD_INFO	_IOR('U', 0x01, काष्ठा snd_ctl_card_info)
#घोषणा SNDRV_CTL_IOCTL_ELEM_LIST	_IOWR('U', 0x10, काष्ठा snd_ctl_elem_list)
#घोषणा SNDRV_CTL_IOCTL_ELEM_INFO	_IOWR('U', 0x11, काष्ठा snd_ctl_elem_info)
#घोषणा SNDRV_CTL_IOCTL_ELEM_READ	_IOWR('U', 0x12, काष्ठा snd_ctl_elem_value)
#घोषणा SNDRV_CTL_IOCTL_ELEM_WRITE	_IOWR('U', 0x13, काष्ठा snd_ctl_elem_value)
#घोषणा SNDRV_CTL_IOCTL_ELEM_LOCK	_IOW('U', 0x14, काष्ठा snd_ctl_elem_id)
#घोषणा SNDRV_CTL_IOCTL_ELEM_UNLOCK	_IOW('U', 0x15, काष्ठा snd_ctl_elem_id)
#घोषणा SNDRV_CTL_IOCTL_SUBSCRIBE_EVENTS _IOWR('U', 0x16, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_ELEM_ADD	_IOWR('U', 0x17, काष्ठा snd_ctl_elem_info)
#घोषणा SNDRV_CTL_IOCTL_ELEM_REPLACE	_IOWR('U', 0x18, काष्ठा snd_ctl_elem_info)
#घोषणा SNDRV_CTL_IOCTL_ELEM_REMOVE	_IOWR('U', 0x19, काष्ठा snd_ctl_elem_id)
#घोषणा SNDRV_CTL_IOCTL_TLV_READ	_IOWR('U', 0x1a, काष्ठा snd_ctl_tlv)
#घोषणा SNDRV_CTL_IOCTL_TLV_WRITE	_IOWR('U', 0x1b, काष्ठा snd_ctl_tlv)
#घोषणा SNDRV_CTL_IOCTL_TLV_COMMAND	_IOWR('U', 0x1c, काष्ठा snd_ctl_tlv)
#घोषणा SNDRV_CTL_IOCTL_HWDEP_NEXT_DEVICE _IOWR('U', 0x20, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_HWDEP_INFO	_IOR('U', 0x21, काष्ठा snd_hwdep_info)
#घोषणा SNDRV_CTL_IOCTL_PCM_NEXT_DEVICE	_IOR('U', 0x30, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_PCM_INFO	_IOWR('U', 0x31, काष्ठा snd_pcm_info)
#घोषणा SNDRV_CTL_IOCTL_PCM_PREFER_SUBDEVICE _IOW('U', 0x32, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_RAWMIDI_NEXT_DEVICE _IOWR('U', 0x40, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_RAWMIDI_INFO	_IOWR('U', 0x41, काष्ठा snd_rawmidi_info)
#घोषणा SNDRV_CTL_IOCTL_RAWMIDI_PREFER_SUBDEVICE _IOW('U', 0x42, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_POWER		_IOWR('U', 0xd0, पूर्णांक)
#घोषणा SNDRV_CTL_IOCTL_POWER_STATE	_IOR('U', 0xd1, पूर्णांक)

/*
 *  Read पूर्णांकerface.
 */

क्रमागत sndrv_ctl_event_type अणु
	SNDRV_CTL_EVENT_ELEM = 0,
	SNDRV_CTL_EVENT_LAST = SNDRV_CTL_EVENT_ELEM,
पूर्ण;

#घोषणा SNDRV_CTL_EVENT_MASK_VALUE	(1<<0)	/* element value was changed */
#घोषणा SNDRV_CTL_EVENT_MASK_INFO	(1<<1)	/* element info was changed */
#घोषणा SNDRV_CTL_EVENT_MASK_ADD	(1<<2)	/* element was added */
#घोषणा SNDRV_CTL_EVENT_MASK_TLV	(1<<3)	/* element TLV tree was changed */
#घोषणा SNDRV_CTL_EVENT_MASK_REMOVE	(~0U)	/* element was हटाओd */

काष्ठा snd_ctl_event अणु
	पूर्णांक type;	/* event type - SNDRV_CTL_EVENT_* */
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित पूर्णांक mask;
			काष्ठा snd_ctl_elem_id id;
		पूर्ण elem;
		अचिन्हित अक्षर data8[60];
	पूर्ण data;
पूर्ण;

/*
 *  Control names
 */

#घोषणा SNDRV_CTL_NAME_NONE				""
#घोषणा SNDRV_CTL_NAME_PLAYBACK				"Playback "
#घोषणा SNDRV_CTL_NAME_CAPTURE				"Capture "

#घोषणा SNDRV_CTL_NAME_IEC958_NONE			""
#घोषणा SNDRV_CTL_NAME_IEC958_SWITCH			"Switch"
#घोषणा SNDRV_CTL_NAME_IEC958_VOLUME			"Volume"
#घोषणा SNDRV_CTL_NAME_IEC958_DEFAULT			"Default"
#घोषणा SNDRV_CTL_NAME_IEC958_MASK			"Mask"
#घोषणा SNDRV_CTL_NAME_IEC958_CON_MASK			"Con Mask"
#घोषणा SNDRV_CTL_NAME_IEC958_PRO_MASK			"Pro Mask"
#घोषणा SNDRV_CTL_NAME_IEC958_PCM_STREAM		"PCM Stream"
#घोषणा SNDRV_CTL_NAME_IEC958(expl,direction,what)	"IEC958 " expl SNDRV_CTL_NAME_##direction SNDRV_CTL_NAME_IEC958_##what

#पूर्ण_अगर /* _UAPI__SOUND_ASOUND_H */
