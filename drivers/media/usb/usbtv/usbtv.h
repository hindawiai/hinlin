<शैली गुरु>
/*
 * Copyright (c) 2013 Lubomir Rपूर्णांकel
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL").
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 * Fushicai USBTV007 Audio-Video Grabber Driver
 *
 * No physical hardware was harmed running Winकरोws during the
 * reverse-engineering activity
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/usb.h>

#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ctrls.h>
#समावेश <media/videobuf2-v4l2.h>
#समावेश <media/videobuf2-vदो_स्मृति.h>

/* Hardware. */
#घोषणा USBTV_VIDEO_ENDP	0x81
#घोषणा USBTV_AUDIO_ENDP	0x83
#घोषणा USBTV_BASE		0xc000
#घोषणा USBTV_CONTROL_REG	11
#घोषणा USBTV_REQUEST_REG	12

/* Number of concurrent isochronous urbs submitted.
 * Higher numbers was seen to overly saturate the USB bus. */
#घोषणा USBTV_ISOC_TRANSFERS	16
#घोषणा USBTV_ISOC_PACKETS	8

#घोषणा USBTV_CHUNK_SIZE	256
#घोषणा USBTV_CHUNK		240

#घोषणा USBTV_AUDIO_URBSIZE	20480
#घोषणा USBTV_AUDIO_HDRSIZE	4
#घोषणा USBTV_AUDIO_BUFFER	65536

/* Chunk header. */
#घोषणा USBTV_MAGIC_OK(chunk)	((be32_to_cpu(chunk[0]) & 0xff000000) \
							== 0x88000000)
#घोषणा USBTV_FRAME_ID(chunk)	((be32_to_cpu(chunk[0]) & 0x00ff0000) >> 16)
#घोषणा USBTV_ODD(chunk)	((be32_to_cpu(chunk[0]) & 0x0000f000) >> 15)
#घोषणा USBTV_CHUNK_NO(chunk)	(be32_to_cpu(chunk[0]) & 0x00000fff)

#घोषणा USBTV_TV_STD  (V4L2_STD_525_60 | V4L2_STD_PAL | V4L2_STD_SECAM)

/* parameters क्रम supported TV norms */
काष्ठा usbtv_norm_params अणु
	v4l2_std_id norm;
	पूर्णांक cap_width, cap_height;
पूर्ण;

/* A single videobuf2 frame buffer. */
काष्ठा usbtv_buf अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

/* Per-device काष्ठाure. */
काष्ठा usbtv अणु
	काष्ठा device *dev;
	काष्ठा usb_device *udev;

	/* video */
	काष्ठा v4l2_device v4l2_dev;
	काष्ठा v4l2_ctrl_handler ctrl;
	काष्ठा video_device vdev;
	काष्ठा vb2_queue vb2q;
	काष्ठा mutex v4l2_lock;
	काष्ठा mutex vb2q_lock;

	/* List of videobuf2 buffers रक्षित by a lock. */
	spinlock_t buflock;
	काष्ठा list_head bufs;

	/* Number of currently processed frame, useful find
	 * out when a new one begins. */
	u32 frame_id;
	पूर्णांक chunks_करोne;

	क्रमागत अणु
		USBTV_COMPOSITE_INPUT,
		USBTV_SVIDEO_INPUT,
	पूर्ण input;
	v4l2_std_id norm;
	पूर्णांक width, height;
	पूर्णांक n_chunks;
	पूर्णांक iso_size;
	पूर्णांक last_odd;
	अचिन्हित पूर्णांक sequence;
	काष्ठा urb *isoc_urbs[USBTV_ISOC_TRANSFERS];

	/* audio */
	काष्ठा snd_card *snd;
	काष्ठा snd_pcm_substream *snd_substream;
	atomic_t snd_stream;
	काष्ठा work_काष्ठा snd_trigger;
	काष्ठा urb *snd_bulk_urb;
	माप_प्रकार snd_buffer_pos;
	माप_प्रकार snd_period_pos;
पूर्ण;

पूर्णांक usbtv_set_regs(काष्ठा usbtv *usbtv, स्थिर u16 regs[][2], पूर्णांक size);

पूर्णांक usbtv_video_init(काष्ठा usbtv *usbtv);
व्योम usbtv_video_मुक्त(काष्ठा usbtv *usbtv);

पूर्णांक usbtv_audio_init(काष्ठा usbtv *usbtv);
व्योम usbtv_audio_मुक्त(काष्ठा usbtv *usbtv);
व्योम usbtv_audio_suspend(काष्ठा usbtv *usbtv);
व्योम usbtv_audio_resume(काष्ठा usbtv *usbtv);
