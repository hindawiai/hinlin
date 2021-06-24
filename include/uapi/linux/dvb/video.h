<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * video.h - DEPRECATED MPEG-TS video decoder API
 *
 * NOTE: should not be used on future drivers
 *
 * Copyright (C) 2000 Marcus Metzler <marcus@convergence.de>
 *                  & Ralph  Metzler <ralph@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _UAPI_DVBVIDEO_H_
#घोषणा _UAPI_DVBVIDEO_H_

#समावेश <linux/types.h>
#अगर_अघोषित __KERNEL__
#समावेश <समय.स>
#पूर्ण_अगर

प्रकार क्रमागत अणु
	VIDEO_FORMAT_4_3,     /* Select 4:3 क्रमmat */
	VIDEO_FORMAT_16_9,    /* Select 16:9 क्रमmat. */
	VIDEO_FORMAT_221_1    /* 2.21:1 */
पूर्ण video_क्रमmat_t;


प्रकार क्रमागत अणु
	VIDEO_PAN_SCAN,       /* use pan and scan क्रमmat */
	VIDEO_LETTER_BOX,     /* use letterbox क्रमmat */
	VIDEO_CENTER_CUT_OUT  /* use center cut out क्रमmat */
पूर्ण video_displayक्रमmat_t;

प्रकार काष्ठा अणु
	पूर्णांक w;
	पूर्णांक h;
	video_क्रमmat_t aspect_ratio;
पूर्ण video_माप_प्रकार;

प्रकार क्रमागत अणु
	VIDEO_SOURCE_DEMUX, /* Select the demux as the मुख्य source */
	VIDEO_SOURCE_MEMORY /* If this source is selected, the stream
			       comes from the user through the ग_लिखो
			       प्रणाली call */
पूर्ण video_stream_source_t;


प्रकार क्रमागत अणु
	VIDEO_STOPPED, /* Video is stopped */
	VIDEO_PLAYING, /* Video is currently playing */
	VIDEO_FREEZED  /* Video is मुक्तzed */
पूर्ण video_play_state_t;


/* Decoder commands */
#घोषणा VIDEO_CMD_PLAY        (0)
#घोषणा VIDEO_CMD_STOP        (1)
#घोषणा VIDEO_CMD_FREEZE      (2)
#घोषणा VIDEO_CMD_CONTINUE    (3)

/* Flags क्रम VIDEO_CMD_FREEZE */
#घोषणा VIDEO_CMD_FREEZE_TO_BLACK	(1 << 0)

/* Flags क्रम VIDEO_CMD_STOP */
#घोषणा VIDEO_CMD_STOP_TO_BLACK		(1 << 0)
#घोषणा VIDEO_CMD_STOP_IMMEDIATELY	(1 << 1)

/* Play input क्रमmats: */
/* The decoder has no special क्रमmat requirements */
#घोषणा VIDEO_PLAY_FMT_NONE         (0)
/* The decoder requires full GOPs */
#घोषणा VIDEO_PLAY_FMT_GOP          (1)

/* The काष्ठाure must be zeroed beक्रमe use by the application
   This ensures it can be extended safely in the future. */
काष्ठा video_command अणु
	__u32 cmd;
	__u32 flags;
	जोड़ अणु
		काष्ठा अणु
			__u64 pts;
		पूर्ण stop;

		काष्ठा अणु
			/* 0 or 1000 specअगरies normal speed,
			   1 specअगरies क्रमward single stepping,
			   -1 specअगरies backward single stepping,
			   >1: playback at speed/1000 of the normal speed,
			   <-1: reverse playback at (-speed/1000) of the normal speed. */
			__s32 speed;
			__u32 क्रमmat;
		पूर्ण play;

		काष्ठा अणु
			__u32 data[16];
		पूर्ण raw;
	पूर्ण;
पूर्ण;

/* FIELD_UNKNOWN can be used अगर the hardware करोes not know whether
   the Vsync is क्रम an odd, even or progressive (i.e. non-पूर्णांकerlaced)
   field. */
#घोषणा VIDEO_VSYNC_FIELD_UNKNOWN	(0)
#घोषणा VIDEO_VSYNC_FIELD_ODD		(1)
#घोषणा VIDEO_VSYNC_FIELD_EVEN		(2)
#घोषणा VIDEO_VSYNC_FIELD_PROGRESSIVE	(3)

काष्ठा video_event अणु
	__s32 type;
#घोषणा VIDEO_EVENT_SIZE_CHANGED	1
#घोषणा VIDEO_EVENT_FRAME_RATE_CHANGED	2
#घोषणा VIDEO_EVENT_DECODER_STOPPED	3
#घोषणा VIDEO_EVENT_VSYNC		4
	/* unused, make sure to use atomic समय क्रम y2038 अगर it ever माला_लो used */
	दीर्घ बारtamp;
	जोड़ अणु
		video_माप_प्रकार size;
		अचिन्हित पूर्णांक frame_rate;	/* in frames per 1000sec */
		अचिन्हित अक्षर vsync_field;	/* unknown/odd/even/progressive */
	पूर्ण u;
पूर्ण;


काष्ठा video_status अणु
	पूर्णांक                   video_blank;   /* blank video on मुक्तze? */
	video_play_state_t    play_state;    /* current state of playback */
	video_stream_source_t stream_source; /* current source (demux/memory) */
	video_क्रमmat_t        video_क्रमmat;  /* current aspect ratio of stream*/
	video_displayक्रमmat_t display_क्रमmat;/* selected cropping mode */
पूर्ण;


काष्ठा video_still_picture अणु
	अक्षर __user *iFrame;        /* poपूर्णांकer to a single अगरrame in memory */
	__s32 size;
पूर्ण;


प्रकार __u16 video_attributes_t;
/*   bits: descr. */
/*   15-14 Video compression mode (0=MPEG-1, 1=MPEG-2) */
/*   13-12 TV प्रणाली (0=525/60, 1=625/50) */
/*   11-10 Aspect ratio (0=4:3, 3=16:9) */
/*    9- 8 permitted display mode on 4:3 monitor (0=both, 1=only pan-sca */
/*    7    line 21-1 data present in GOP (1=yes, 0=no) */
/*    6    line 21-2 data present in GOP (1=yes, 0=no) */
/*    5- 3 source resolution (0=720x480/576, 1=704x480/576, 2=352x480/57 */
/*    2    source letterboxed (1=yes, 0=no) */
/*    0    film/camera mode (0=
 *camera, 1=film (625/50 only)) */


/* bit definitions क्रम capabilities: */
/* can the hardware decode MPEG1 and/or MPEG2? */
#घोषणा VIDEO_CAP_MPEG1   1
#घोषणा VIDEO_CAP_MPEG2   2
/* can you send a प्रणाली and/or program stream to video device?
   (you still have to खोलो the video and the audio device but only
    send the stream to the video device) */
#घोषणा VIDEO_CAP_SYS     4
#घोषणा VIDEO_CAP_PROG    8
/* can the driver also handle SPU, NAVI and CSS encoded data?
   (CSS API is not present yet) */
#घोषणा VIDEO_CAP_SPU    16
#घोषणा VIDEO_CAP_NAVI   32
#घोषणा VIDEO_CAP_CSS    64


#घोषणा VIDEO_STOP                 _IO('o', 21)
#घोषणा VIDEO_PLAY                 _IO('o', 22)
#घोषणा VIDEO_FREEZE               _IO('o', 23)
#घोषणा VIDEO_CONTINUE             _IO('o', 24)
#घोषणा VIDEO_SELECT_SOURCE        _IO('o', 25)
#घोषणा VIDEO_SET_BLANK            _IO('o', 26)
#घोषणा VIDEO_GET_STATUS           _IOR('o', 27, काष्ठा video_status)
#घोषणा VIDEO_GET_EVENT            _IOR('o', 28, काष्ठा video_event)
#घोषणा VIDEO_SET_DISPLAY_FORMAT   _IO('o', 29)
#घोषणा VIDEO_STILLPICTURE         _IOW('o', 30, काष्ठा video_still_picture)
#घोषणा VIDEO_FAST_FORWARD         _IO('o', 31)
#घोषणा VIDEO_SLOWMOTION           _IO('o', 32)
#घोषणा VIDEO_GET_CAPABILITIES     _IOR('o', 33, अचिन्हित पूर्णांक)
#घोषणा VIDEO_CLEAR_BUFFER         _IO('o',  34)
#घोषणा VIDEO_SET_STREAMTYPE       _IO('o', 36)
#घोषणा VIDEO_SET_FORMAT           _IO('o', 37)
#घोषणा VIDEO_GET_SIZE             _IOR('o', 55, video_माप_प्रकार)

/**
 * VIDEO_GET_PTS
 *
 * Read the 33 bit presentation समय stamp as defined
 * in ITU T-REC-H.222.0 / ISO/IEC 13818-1.
 *
 * The PTS should beदीर्घ to the currently played
 * frame अगर possible, but may also be a value बंद to it
 * like the PTS of the last decoded frame or the last PTS
 * extracted by the PES parser.
 */
#घोषणा VIDEO_GET_PTS              _IOR('o', 57, __u64)

/* Read the number of displayed frames since the decoder was started */
#घोषणा VIDEO_GET_FRAME_COUNT	   _IOR('o', 58, __u64)

#घोषणा VIDEO_COMMAND		   _IOWR('o', 59, काष्ठा video_command)
#घोषणा VIDEO_TRY_COMMAND	   _IOWR('o', 60, काष्ठा video_command)

#पूर्ण_अगर /* _UAPI_DVBVIDEO_H_ */
