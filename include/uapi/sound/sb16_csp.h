<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  Copyright (c) 1999 by Uros Bizjak <uros@kss-loka.si>
 *                        Takashi Iwai <tiwai@suse.de>
 *
 *  SB16ASP/AWE32 CSP control
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
#अगर_अघोषित _UAPI__SOUND_SB16_CSP_H
#घोषणा _UAPI__SOUND_SB16_CSP_H


/* CSP modes */
#घोषणा SNDRV_SB_CSP_MODE_NONE		0x00
#घोषणा SNDRV_SB_CSP_MODE_DSP_READ	0x01	/* Record from DSP */
#घोषणा SNDRV_SB_CSP_MODE_DSP_WRITE	0x02	/* Play to DSP */
#घोषणा SNDRV_SB_CSP_MODE_QSOUND		0x04	/* QSound */

/* CSP load flags */
#घोषणा SNDRV_SB_CSP_LOAD_FROMUSER	0x01
#घोषणा SNDRV_SB_CSP_LOAD_INITBLOCK	0x02

/* CSP sample width */
#घोषणा SNDRV_SB_CSP_SAMPLE_8BIT		0x01
#घोषणा SNDRV_SB_CSP_SAMPLE_16BIT		0x02

/* CSP channels */
#घोषणा SNDRV_SB_CSP_MONO			0x01
#घोषणा SNDRV_SB_CSP_STEREO		0x02

/* CSP rates */
#घोषणा SNDRV_SB_CSP_RATE_8000		0x01
#घोषणा SNDRV_SB_CSP_RATE_11025		0x02
#घोषणा SNDRV_SB_CSP_RATE_22050		0x04
#घोषणा SNDRV_SB_CSP_RATE_44100		0x08
#घोषणा SNDRV_SB_CSP_RATE_ALL		0x0f

/* CSP running state */
#घोषणा SNDRV_SB_CSP_ST_IDLE		0x00
#घोषणा SNDRV_SB_CSP_ST_LOADED		0x01
#घोषणा SNDRV_SB_CSP_ST_RUNNING		0x02
#घोषणा SNDRV_SB_CSP_ST_PAUSED		0x04
#घोषणा SNDRV_SB_CSP_ST_AUTO		0x08
#घोषणा SNDRV_SB_CSP_ST_QSOUND		0x10

/* maximum QSound value (180 degrees right) */
#घोषणा SNDRV_SB_CSP_QSOUND_MAX_RIGHT	0x20

/* maximum microcode RIFF file size */
#घोषणा SNDRV_SB_CSP_MAX_MICROCODE_खाता_SIZE	0x3000

/* microcode header */
काष्ठा snd_sb_csp_mc_header अणु
	अक्षर codec_name[16];		/* id name of codec */
	अचिन्हित लघु func_req;	/* requested function */
पूर्ण;

/* microcode to be loaded */
काष्ठा snd_sb_csp_microcode अणु
	काष्ठा snd_sb_csp_mc_header info;
	अचिन्हित अक्षर data[SNDRV_SB_CSP_MAX_MICROCODE_खाता_SIZE];
पूर्ण;

/* start CSP with sample_width in mono/stereo */
काष्ठा snd_sb_csp_start अणु
	पूर्णांक sample_width;	/* sample width, look above */
	पूर्णांक channels;		/* channels, look above */
पूर्ण;

/* CSP inक्रमmation */
काष्ठा snd_sb_csp_info अणु
	अक्षर codec_name[16];		/* id name of codec */
	अचिन्हित लघु func_nr;		/* function number */
	अचिन्हित पूर्णांक acc_क्रमmat;	/* accepted PCM क्रमmats */
	अचिन्हित लघु acc_channels;	/* accepted channels */
	अचिन्हित लघु acc_width;	/* accepted sample width */
	अचिन्हित लघु acc_rates;	/* accepted sample rates */
	अचिन्हित लघु csp_mode;	/* CSP mode, see above */
	अचिन्हित लघु run_channels;	/* current channels  */
	अचिन्हित लघु run_width;	/* current sample width */
	अचिन्हित लघु version;		/* version id: 0x10 - 0x1f */
	अचिन्हित लघु state;		/* state bits */
पूर्ण;

/* HWDEP controls */
/* get CSP inक्रमmation */
#घोषणा SNDRV_SB_CSP_IOCTL_INFO		_IOR('H', 0x10, काष्ठा snd_sb_csp_info)
/* load microcode to CSP */
/* NOTE: काष्ठा snd_sb_csp_microcode overflows the max size (13 bits)
 * defined क्रम some architectures like MIPS, and it leads to build errors.
 * (x86 and co have 14-bit size, thus it's valid, though.)
 * As a workaround क्रम skipping the size-limit check, here we करोn't use the
 * normal _IOW() macro but _IOC() with the manual argument.
 */
#घोषणा SNDRV_SB_CSP_IOCTL_LOAD_CODE	\
	_IOC(_IOC_WRITE, 'H', 0x11, माप(काष्ठा snd_sb_csp_microcode))
/* unload microcode from CSP */
#घोषणा SNDRV_SB_CSP_IOCTL_UNLOAD_CODE	_IO('H', 0x12)
/* start CSP */
#घोषणा SNDRV_SB_CSP_IOCTL_START		_IOW('H', 0x13, काष्ठा snd_sb_csp_start)
/* stop CSP */
#घोषणा SNDRV_SB_CSP_IOCTL_STOP		_IO('H', 0x14)
/* छोड़ो CSP and DMA transfer */
#घोषणा SNDRV_SB_CSP_IOCTL_PAUSE		_IO('H', 0x15)
/* restart CSP and DMA transfer */
#घोषणा SNDRV_SB_CSP_IOCTL_RESTART	_IO('H', 0x16)


#पूर्ण_अगर /* _UAPI__SOUND_SB16_CSP_H */
