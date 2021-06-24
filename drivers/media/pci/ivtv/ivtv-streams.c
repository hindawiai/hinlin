<शैली गुरु>
/*
    init/start/stop/निकास stream functions
    Copyright (C) 2003-2004  Kevin Thayer <nufan_wfk at yahoo.com>
    Copyright (C) 2004  Chris Kennedy <c@groovy.org>
    Copyright (C) 2005-2007  Hans Verkuil <hverkuil@xs4all.nl>

    This program is मुक्त software; you can redistribute it and/or modअगरy
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License क्रम more details.

    You should have received a copy of the GNU General Public License
    aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* License: GPL
 * Author: Kevin Thayer <nufan_wfk at yahoo करोt com>
 *
 * This file will hold API related functions, both पूर्णांकernal (firmware api)
 * and बाह्यal (v4l2, etc)
 *
 * -----
 * MPG600/MPG160 support by  T.Adachi <tadachi@tadachi-net.com>
 *                      and Takeru KOMORIYA<komoriya@paken.org>
 *
 * AVerMedia M179 GPIO info by Chris Pinkham <cpinkham@bc2va.org>
 *                using inक्रमmation provided by Jiun-Kuei Jung @ AVerMedia.
 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-fileops.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-mailbox.h"
#समावेश "ivtv-ioctl.h"
#समावेश "ivtv-irq.h"
#समावेश "ivtv-yuv.h"
#समावेश "ivtv-cards.h"
#समावेश "ivtv-streams.h"
#समावेश "ivtv-firmware.h"
#समावेश <media/v4l2-event.h>

अटल स्थिर काष्ठा v4l2_file_operations ivtv_v4l2_enc_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = ivtv_v4l2_पढ़ो,
	.ग_लिखो = ivtv_v4l2_ग_लिखो,
	.खोलो = ivtv_v4l2_खोलो,
	.unlocked_ioctl = video_ioctl2,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl32 = video_ioctl2, /* क्रम ivtv_शेष() */
#पूर्ण_अगर
	.release = ivtv_v4l2_बंद,
	.poll = ivtv_v4l2_enc_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations ivtv_v4l2_dec_fops = अणु
	.owner = THIS_MODULE,
	.पढ़ो = ivtv_v4l2_पढ़ो,
	.ग_लिखो = ivtv_v4l2_ग_लिखो,
	.खोलो = ivtv_v4l2_खोलो,
	.unlocked_ioctl = video_ioctl2,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl32 = video_ioctl2, /* क्रम ivtv_शेष() */
#पूर्ण_अगर
	.release = ivtv_v4l2_बंद,
	.poll = ivtv_v4l2_dec_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations ivtv_v4l2_radio_fops = अणु
	.owner = THIS_MODULE,
	.खोलो = ivtv_v4l2_खोलो,
	.unlocked_ioctl = video_ioctl2,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl32 = video_ioctl2, /* क्रम ivtv_शेष() */
#पूर्ण_अगर
	.release = ivtv_v4l2_बंद,
	.poll = ivtv_v4l2_enc_poll,
पूर्ण;

#घोषणा IVTV_V4L2_DEC_MPG_OFFSET  16	/* offset from 0 to रेजिस्टर decoder mpg v4l2 minors on */
#घोषणा IVTV_V4L2_ENC_PCM_OFFSET  24	/* offset from 0 to रेजिस्टर pcm v4l2 minors on */
#घोषणा IVTV_V4L2_ENC_YUV_OFFSET  32	/* offset from 0 to रेजिस्टर yuv v4l2 minors on */
#घोषणा IVTV_V4L2_DEC_YUV_OFFSET  48	/* offset from 0 to रेजिस्टर decoder yuv v4l2 minors on */
#घोषणा IVTV_V4L2_DEC_VBI_OFFSET   8	/* offset from 0 to रेजिस्टर decoder vbi input v4l2 minors on */
#घोषणा IVTV_V4L2_DEC_VOUT_OFFSET 16	/* offset from 0 to रेजिस्टर vbi output v4l2 minors on */

अटल काष्ठा अणु
	स्थिर अक्षर *name;
	पूर्णांक vfl_type;
	पूर्णांक num_offset;
	पूर्णांक dma, pio;
	u32 v4l2_caps;
	स्थिर काष्ठा v4l2_file_operations *fops;
पूर्ण ivtv_stream_info[] = अणु
	अणु	/* IVTV_ENC_STREAM_TYPE_MPG */
		"encoder MPG",
		VFL_TYPE_VIDEO, 0,
		PCI_DMA_FROMDEVICE, 0,
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER |
			V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_enc_fops
	पूर्ण,
	अणु	/* IVTV_ENC_STREAM_TYPE_YUV */
		"encoder YUV",
		VFL_TYPE_VIDEO, IVTV_V4L2_ENC_YUV_OFFSET,
		PCI_DMA_FROMDEVICE, 0,
		V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_TUNER |
			V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_enc_fops
	पूर्ण,
	अणु	/* IVTV_ENC_STREAM_TYPE_VBI */
		"encoder VBI",
		VFL_TYPE_VBI, 0,
		PCI_DMA_FROMDEVICE, 0,
		V4L2_CAP_VBI_CAPTURE | V4L2_CAP_SLICED_VBI_CAPTURE | V4L2_CAP_TUNER |
			V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_enc_fops
	पूर्ण,
	अणु	/* IVTV_ENC_STREAM_TYPE_PCM */
		"encoder PCM",
		VFL_TYPE_VIDEO, IVTV_V4L2_ENC_PCM_OFFSET,
		PCI_DMA_FROMDEVICE, 0,
		V4L2_CAP_TUNER | V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_enc_fops
	पूर्ण,
	अणु	/* IVTV_ENC_STREAM_TYPE_RAD */
		"encoder radio",
		VFL_TYPE_RADIO, 0,
		PCI_DMA_NONE, 1,
		V4L2_CAP_RADIO | V4L2_CAP_TUNER,
		&ivtv_v4l2_radio_fops
	पूर्ण,
	अणु	/* IVTV_DEC_STREAM_TYPE_MPG */
		"decoder MPG",
		VFL_TYPE_VIDEO, IVTV_V4L2_DEC_MPG_OFFSET,
		PCI_DMA_TODEVICE, 0,
		V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_dec_fops
	पूर्ण,
	अणु	/* IVTV_DEC_STREAM_TYPE_VBI */
		"decoder VBI",
		VFL_TYPE_VBI, IVTV_V4L2_DEC_VBI_OFFSET,
		PCI_DMA_NONE, 1,
		V4L2_CAP_SLICED_VBI_CAPTURE | V4L2_CAP_READWRITE,
		&ivtv_v4l2_enc_fops
	पूर्ण,
	अणु	/* IVTV_DEC_STREAM_TYPE_VOUT */
		"decoder VOUT",
		VFL_TYPE_VBI, IVTV_V4L2_DEC_VOUT_OFFSET,
		PCI_DMA_NONE, 1,
		V4L2_CAP_SLICED_VBI_OUTPUT | V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_dec_fops
	पूर्ण,
	अणु	/* IVTV_DEC_STREAM_TYPE_YUV */
		"decoder YUV",
		VFL_TYPE_VIDEO, IVTV_V4L2_DEC_YUV_OFFSET,
		PCI_DMA_TODEVICE, 0,
		V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_AUDIO | V4L2_CAP_READWRITE,
		&ivtv_v4l2_dec_fops
	पूर्ण
पूर्ण;

अटल व्योम ivtv_stream_init(काष्ठा ivtv *itv, पूर्णांक type)
अणु
	काष्ठा ivtv_stream *s = &itv->streams[type];

	/* we need to keep vdev, so restore it afterwards */
	स_रखो(s, 0, माप(*s));

	/* initialize ivtv_stream fields */
	s->itv = itv;
	s->type = type;
	s->name = ivtv_stream_info[type].name;
	s->caps = ivtv_stream_info[type].v4l2_caps;

	अगर (ivtv_stream_info[type].pio)
		s->dma = PCI_DMA_NONE;
	अन्यथा
		s->dma = ivtv_stream_info[type].dma;
	s->buf_size = itv->stream_buf_size[type];
	अगर (s->buf_size)
		s->buffers = (itv->options.kilobytes[type] * 1024 + s->buf_size - 1) / s->buf_size;
	spin_lock_init(&s->qlock);
	init_रुकोqueue_head(&s->रुकोq);
	s->sg_handle = IVTV_DMA_UNMAPPED;
	ivtv_queue_init(&s->q_मुक्त);
	ivtv_queue_init(&s->q_full);
	ivtv_queue_init(&s->q_dma);
	ivtv_queue_init(&s->q_predma);
	ivtv_queue_init(&s->q_io);
पूर्ण

अटल पूर्णांक ivtv_prep_dev(काष्ठा ivtv *itv, पूर्णांक type)
अणु
	काष्ठा ivtv_stream *s = &itv->streams[type];
	पूर्णांक num_offset = ivtv_stream_info[type].num_offset;
	पूर्णांक num = itv->instance + ivtv_first_minor + num_offset;

	/* These four fields are always initialized. If vdev.v4l2_dev == शून्य, then
	   this stream is not in use. In that हाल no other fields but these
	   four can be used. */
	s->vdev.v4l2_dev = शून्य;
	s->itv = itv;
	s->type = type;
	s->name = ivtv_stream_info[type].name;

	/* Check whether the radio is supported */
	अगर (type == IVTV_ENC_STREAM_TYPE_RAD && !(itv->v4l2_cap & V4L2_CAP_RADIO))
		वापस 0;
	अगर (type >= IVTV_DEC_STREAM_TYPE_MPG && !(itv->v4l2_cap & V4L2_CAP_VIDEO_OUTPUT))
		वापस 0;

	/* User explicitly selected 0 buffers क्रम these streams, so करोn't
	   create them. */
	अगर (ivtv_stream_info[type].dma != PCI_DMA_NONE &&
	    itv->options.kilobytes[type] == 0) अणु
		IVTV_INFO("Disabled %s device\n", ivtv_stream_info[type].name);
		वापस 0;
	पूर्ण

	ivtv_stream_init(itv, type);

	snम_लिखो(s->vdev.name, माप(s->vdev.name), "%s %s",
			itv->v4l2_dev.name, s->name);

	s->vdev.num = num;
	s->vdev.v4l2_dev = &itv->v4l2_dev;
	अगर (ivtv_stream_info[type].v4l2_caps &
			(V4L2_CAP_VIDEO_OUTPUT | V4L2_CAP_SLICED_VBI_OUTPUT))
		s->vdev.vfl_dir = VFL_सूची_TX;
	s->vdev.fops = ivtv_stream_info[type].fops;
	s->vdev.ctrl_handler = itv->v4l2_dev.ctrl_handler;
	s->vdev.release = video_device_release_empty;
	s->vdev.tvnorms = V4L2_STD_ALL;
	s->vdev.lock = &itv->serialize_lock;
	अगर (s->type == IVTV_DEC_STREAM_TYPE_VBI) अणु
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_AUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_AUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_ENUMAUDIO);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_ENUMINPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_INPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_INPUT);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_FREQUENCY);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_FREQUENCY);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_TUNER);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_G_TUNER);
		v4l2_disable_ioctl(&s->vdev, VIDIOC_S_STD);
	पूर्ण
	ivtv_set_funcs(&s->vdev);
	वापस 0;
पूर्ण

/* Initialize v4l2 variables and prepare v4l2 devices */
पूर्णांक ivtv_streams_setup(काष्ठा ivtv *itv)
अणु
	पूर्णांक type;

	/* Setup V4L2 Devices */
	क्रम (type = 0; type < IVTV_MAX_STREAMS; type++) अणु
		/* Prepare device */
		अगर (ivtv_prep_dev(itv, type))
			अवरोध;

		अगर (itv->streams[type].vdev.v4l2_dev == शून्य)
			जारी;

		/* Allocate Stream */
		अगर (ivtv_stream_alloc(&itv->streams[type]))
			अवरोध;
	पूर्ण
	अगर (type == IVTV_MAX_STREAMS)
		वापस 0;

	/* One or more streams could not be initialized. Clean 'em all up. */
	ivtv_streams_cleanup(itv);
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक ivtv_reg_dev(काष्ठा ivtv *itv, पूर्णांक type)
अणु
	काष्ठा ivtv_stream *s = &itv->streams[type];
	पूर्णांक vfl_type = ivtv_stream_info[type].vfl_type;
	स्थिर अक्षर *name;
	पूर्णांक num;

	अगर (s->vdev.v4l2_dev == शून्य)
		वापस 0;

	num = s->vdev.num;
	/* card number + user defined offset + device offset */
	अगर (type != IVTV_ENC_STREAM_TYPE_MPG) अणु
		काष्ठा ivtv_stream *s_mpg = &itv->streams[IVTV_ENC_STREAM_TYPE_MPG];

		अगर (s_mpg->vdev.v4l2_dev)
			num = s_mpg->vdev.num + ivtv_stream_info[type].num_offset;
	पूर्ण
	s->vdev.device_caps = s->caps;
	अगर (itv->osd_video_pbase) अणु
		itv->streams[IVTV_DEC_STREAM_TYPE_YUV].vdev.device_caps |=
			V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
		itv->streams[IVTV_DEC_STREAM_TYPE_MPG].vdev.device_caps |=
			V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
		itv->v4l2_cap |= V4L2_CAP_VIDEO_OUTPUT_OVERLAY;
	पूर्ण
	video_set_drvdata(&s->vdev, s);

	/* Register device. First try the desired minor, then any मुक्त one. */
	अगर (video_रेजिस्टर_device_no_warn(&s->vdev, vfl_type, num)) अणु
		IVTV_ERR("Couldn't register v4l2 device for %s (device node number %d)\n",
				s->name, num);
		वापस -ENOMEM;
	पूर्ण
	name = video_device_node_name(&s->vdev);

	चयन (vfl_type) अणु
	हाल VFL_TYPE_VIDEO:
		IVTV_INFO("Registered device %s for %s (%d kB)\n",
			name, s->name, itv->options.kilobytes[type]);
		अवरोध;
	हाल VFL_TYPE_RADIO:
		IVTV_INFO("Registered device %s for %s\n",
			name, s->name);
		अवरोध;
	हाल VFL_TYPE_VBI:
		अगर (itv->options.kilobytes[type])
			IVTV_INFO("Registered device %s for %s (%d kB)\n",
				name, s->name, itv->options.kilobytes[type]);
		अन्यथा
			IVTV_INFO("Registered device %s for %s\n",
				name, s->name);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/* Register v4l2 devices */
पूर्णांक ivtv_streams_रेजिस्टर(काष्ठा ivtv *itv)
अणु
	पूर्णांक type;
	पूर्णांक err = 0;

	/* Register V4L2 devices */
	क्रम (type = 0; type < IVTV_MAX_STREAMS; type++)
		err |= ivtv_reg_dev(itv, type);

	अगर (err == 0)
		वापस 0;

	/* One or more streams could not be initialized. Clean 'em all up. */
	ivtv_streams_cleanup(itv);
	वापस -ENOMEM;
पूर्ण

/* Unरेजिस्टर v4l2 devices */
व्योम ivtv_streams_cleanup(काष्ठा ivtv *itv)
अणु
	पूर्णांक type;

	/* Tearकरोwn all streams */
	क्रम (type = 0; type < IVTV_MAX_STREAMS; type++) अणु
		काष्ठा video_device *vdev = &itv->streams[type].vdev;

		अगर (vdev->v4l2_dev == शून्य)
			जारी;

		video_unरेजिस्टर_device(vdev);
		ivtv_stream_मुक्त(&itv->streams[type]);
		itv->streams[type].vdev.v4l2_dev = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ivtv_vbi_setup(काष्ठा ivtv *itv)
अणु
	पूर्णांक raw = ivtv_raw_vbi(itv);
	u32 data[CX2341X_MBOX_MAX_DATA];
	पूर्णांक lines;
	पूर्णांक i;

	/* Reset VBI */
	ivtv_vapi(itv, CX2341X_ENC_SET_VBI_LINE, 5, 0xffff , 0, 0, 0, 0);

	/* setup VBI रेजिस्टरs */
	अगर (raw)
		v4l2_subdev_call(itv->sd_video, vbi, s_raw_fmt, &itv->vbi.in.fmt.vbi);
	अन्यथा
		v4l2_subdev_call(itv->sd_video, vbi, s_sliced_fmt, &itv->vbi.in.fmt.sliced);

	/* determine number of lines and total number of VBI bytes.
	   A raw line takes 1443 bytes: 2 * 720 + 4 byte frame header - 1
	   The '- 1' byte is probably an unused U or V byte. Or something...
	   A sliced line takes 51 bytes: 4 byte frame header, 4 byte पूर्णांकernal
	   header, 42 data bytes + checksum (to be confirmed) */
	अगर (raw) अणु
		lines = itv->vbi.count * 2;
	पूर्ण अन्यथा अणु
		lines = itv->is_60hz ? 24 : 38;
		अगर (itv->is_60hz && (itv->hw_flags & IVTV_HW_CX25840))
			lines += 2;
	पूर्ण

	itv->vbi.enc_size = lines * (raw ? itv->vbi.raw_size : itv->vbi.sliced_size);

	/* Note: sliced vs raw flag करोesn't seem to have any effect
	   TODO: check mode (0x02) value with older ivtv versions. */
	data[0] = raw | 0x02 | (0xbd << 8);

	/* Every X number of frames a VBI पूर्णांकerrupt arrives (frames as in 25 or 30 fps) */
	data[1] = 1;
	/* The VBI frames are stored in a ringbuffer with this size (with a VBI frame as unit) */
	data[2] = raw ? 4 : 4 * (itv->vbi.raw_size / itv->vbi.enc_size);
	/* The start/stop codes determine which VBI lines end up in the raw VBI data area.
	   The codes are from table 24 in the saa7115 datasheet. Each raw/sliced/video line
	   is framed with codes FF0000XX where XX is the SAV/EAV (Start/End of Active Video)
	   code. These values क्रम raw VBI are obtained from a driver disassembly. The sliced
	   start/stop codes was deduced from this, but they करो not appear in the driver.
	   Other code pairs that I found are: 0x250E6249/0x13545454 and 0x25256262/0x38137F54.
	   However, I have no idea what these values are क्रम. */
	अगर (itv->hw_flags & IVTV_HW_CX25840) अणु
		/* Setup VBI क्रम the cx25840 digitizer */
		अगर (raw) अणु
			data[3] = 0x20602060;
			data[4] = 0x30703070;
		पूर्ण अन्यथा अणु
			data[3] = 0xB0F0B0F0;
			data[4] = 0xA0E0A0E0;
		पूर्ण
		/* Lines per frame */
		data[5] = lines;
		/* bytes per line */
		data[6] = (raw ? itv->vbi.raw_size : itv->vbi.sliced_size);
	पूर्ण अन्यथा अणु
		/* Setup VBI क्रम the saa7115 digitizer */
		अगर (raw) अणु
			data[3] = 0x25256262;
			data[4] = 0x387F7F7F;
		पूर्ण अन्यथा अणु
			data[3] = 0xABABECEC;
			data[4] = 0xB6F1F1F1;
		पूर्ण
		/* Lines per frame */
		data[5] = lines;
		/* bytes per line */
		data[6] = itv->vbi.enc_size / lines;
	पूर्ण

	IVTV_DEBUG_INFO(
		"Setup VBI API header 0x%08x pkts %d buffs %d ln %d sz %d\n",
			data[0], data[1], data[2], data[5], data[6]);

	ivtv_api(itv, CX2341X_ENC_SET_VBI_CONFIG, 7, data);

	/* वापसs the VBI encoder memory area. */
	itv->vbi.enc_start = data[2];
	itv->vbi.fpi = data[0];
	अगर (!itv->vbi.fpi)
		itv->vbi.fpi = 1;

	IVTV_DEBUG_INFO("Setup VBI start 0x%08x frames %d fpi %d\n",
		itv->vbi.enc_start, data[1], itv->vbi.fpi);

	/* select VBI lines.
	   Note that the sliced argument seems to have no effect. */
	क्रम (i = 2; i <= 24; i++) अणु
		पूर्णांक valid;

		अगर (itv->is_60hz) अणु
			valid = i >= 10 && i < 22;
		पूर्ण अन्यथा अणु
			valid = i >= 6 && i < 24;
		पूर्ण
		ivtv_vapi(itv, CX2341X_ENC_SET_VBI_LINE, 5, i - 1,
				valid, 0 , 0, 0);
		ivtv_vapi(itv, CX2341X_ENC_SET_VBI_LINE, 5, (i - 1) | 0x80000000,
				valid, 0, 0, 0);
	पूर्ण

	/* Reमुख्यing VBI questions:
	   - Is it possible to select particular VBI lines only क्रम inclusion in the MPEG
	   stream? Currently you can only get the first X lines.
	   - Is mixed raw and sliced VBI possible?
	   - What's the meaning of the raw/sliced flag?
	   - What's the meaning of params 2, 3 & 4 of the Select VBI command? */
पूर्ण

पूर्णांक ivtv_start_v4l2_encode_stream(काष्ठा ivtv_stream *s)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv *itv = s->itv;
	पूर्णांक captype = 0, subtype = 0;
	पूर्णांक enable_passthrough = 0;

	अगर (s->vdev.v4l2_dev == शून्य)
		वापस -EINVAL;

	IVTV_DEBUG_INFO("Start encoder stream %s\n", s->name);

	चयन (s->type) अणु
	हाल IVTV_ENC_STREAM_TYPE_MPG:
		captype = 0;
		subtype = 3;

		/* Stop Passthrough */
		अगर (itv->output_mode == OUT_PASSTHROUGH) अणु
			ivtv_passthrough_mode(itv, 0);
			enable_passthrough = 1;
		पूर्ण
		itv->mpg_data_received = itv->vbi_data_inserted = 0;
		itv->dualwatch_jअगरfies = jअगरfies;
		itv->dualwatch_stereo_mode = v4l2_ctrl_g_ctrl(itv->cxhdl.audio_mode);
		itv->search_pack_header = 0;
		अवरोध;

	हाल IVTV_ENC_STREAM_TYPE_YUV:
		अगर (itv->output_mode == OUT_PASSTHROUGH) अणु
			captype = 2;
			subtype = 11;	/* video+audio+decoder */
			अवरोध;
		पूर्ण
		captype = 1;
		subtype = 1;
		अवरोध;
	हाल IVTV_ENC_STREAM_TYPE_PCM:
		captype = 1;
		subtype = 2;
		अवरोध;
	हाल IVTV_ENC_STREAM_TYPE_VBI:
		captype = 1;
		subtype = 4;

		itv->vbi.frame = 0;
		itv->vbi.inserted_frame = 0;
		स_रखो(itv->vbi.sliced_mpeg_size,
			0, माप(itv->vbi.sliced_mpeg_size));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	s->subtype = subtype;
	s->buffers_stolen = 0;

	/* Clear Streamoff flags in हाल left from last capture */
	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);

	अगर (atomic_पढ़ो(&itv->capturing) == 0) अणु
		पूर्णांक digitizer;

		/* Always use frame based mode. Experiments have demonstrated that byte
		   stream based mode results in dropped frames and corruption. Not often,
		   but occasionally. Many thanks go to Leonard Orb who spent a lot of
		   efक्रमt and समय trying to trace the cause of the drop outs. */
		/* 1 frame per DMA */
		/*ivtv_vapi(itv, CX2341X_ENC_SET_DMA_BLOCK_SIZE, 2, 128, 0); */
		ivtv_vapi(itv, CX2341X_ENC_SET_DMA_BLOCK_SIZE, 2, 1, 1);

		/* Stuff from Winकरोws, we करोn't know what it is */
		ivtv_vapi(itv, CX2341X_ENC_SET_VERT_CROP_LINE, 1, 0);
		/* According to the करोcs, this should be correct. However, this is
		   untested. I करोn't dare enable this without having tested it.
		   Only very few old cards actually have this hardware combination.
		ivtv_vapi(itv, CX2341X_ENC_SET_VERT_CROP_LINE, 1,
			((itv->hw_flags & IVTV_HW_SAA7114) && itv->is_60hz) ? 10001 : 0);
		*/
		ivtv_vapi(itv, CX2341X_ENC_MISC, 2, 3, !itv->has_cx23415);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 2, 8, 0);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 2, 4, 1);
		ivtv_vapi(itv, CX2341X_ENC_MISC, 1, 12);

		/* assign placeholder */
		ivtv_vapi(itv, CX2341X_ENC_SET_PLACEHOLDER, 12,
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

		अगर (itv->card->hw_all & (IVTV_HW_SAA7115 | IVTV_HW_SAA717X))
		    digitizer = 0xF1;
		अन्यथा अगर (itv->card->hw_all & IVTV_HW_SAA7114)
		    digitizer = 0xEF;
		अन्यथा /* cx25840 */
		    digitizer = 0x140;

		ivtv_vapi(itv, CX2341X_ENC_SET_NUM_VSYNC_LINES, 2, digitizer, digitizer);

		/* Setup VBI */
		अगर (itv->v4l2_cap & V4L2_CAP_VBI_CAPTURE) अणु
			ivtv_vbi_setup(itv);
		पूर्ण

		/* assign program index info. Mask 7: select I/P/B, Num_req: 400 max */
		ivtv_vapi_result(itv, data, CX2341X_ENC_SET_PGM_INDEX_INFO, 2, 7, 400);
		itv->pgm_info_offset = data[0];
		itv->pgm_info_num = data[1];
		itv->pgm_info_ग_लिखो_idx = 0;
		itv->pgm_info_पढ़ो_idx = 0;

		IVTV_DEBUG_INFO("PGM Index at 0x%08x with %d elements\n",
				itv->pgm_info_offset, itv->pgm_info_num);

		/* Setup API क्रम Stream */
		cx2341x_handler_setup(&itv->cxhdl);

		/* mute अगर capturing radio */
		अगर (test_bit(IVTV_F_I_RADIO_USER, &itv->i_flags))
			ivtv_vapi(itv, CX2341X_ENC_MUTE_VIDEO, 1,
				1 | (v4l2_ctrl_g_ctrl(itv->cxhdl.video_mute_yuv) << 8));
	पूर्ण

	/* Vsync Setup */
	अगर (itv->has_cx23415 && !test_and_set_bit(IVTV_F_I_DIG_RST, &itv->i_flags)) अणु
		/* event notअगरication (on) */
		ivtv_vapi(itv, CX2341X_ENC_SET_EVENT_NOTIFICATION, 4, 0, 1, IVTV_IRQ_ENC_VIM_RST, -1);
		ivtv_clear_irq_mask(itv, IVTV_IRQ_ENC_VIM_RST);
	पूर्ण

	अगर (atomic_पढ़ो(&itv->capturing) == 0) अणु
		/* Clear all Pending Interrupts */
		ivtv_set_irq_mask(itv, IVTV_IRQ_MASK_CAPTURE);

		clear_bit(IVTV_F_I_EOS, &itv->i_flags);

		cx2341x_handler_set_busy(&itv->cxhdl, 1);

		/* Initialize Digitizer क्रम Capture */
		/* Aव्योम tinny audio problem - ensure audio घड़ीs are going */
		v4l2_subdev_call(itv->sd_audio, audio, s_stream, 1);
		/* Aव्योम unpredictable PCI bus hang - disable video घड़ीs */
		v4l2_subdev_call(itv->sd_video, video, s_stream, 0);
		ivtv_msleep_समयout(300, 0);
		ivtv_vapi(itv, CX2341X_ENC_INITIALIZE_INPUT, 0);
		v4l2_subdev_call(itv->sd_video, video, s_stream, 1);
	पूर्ण

	/* begin_capture */
	अगर (ivtv_vapi(itv, CX2341X_ENC_START_CAPTURE, 2, captype, subtype))
	अणु
		IVTV_DEBUG_WARN( "Error starting capture!\n");
		वापस -EINVAL;
	पूर्ण

	/* Start Passthrough */
	अगर (enable_passthrough) अणु
		ivtv_passthrough_mode(itv, 1);
	पूर्ण

	अगर (s->type == IVTV_ENC_STREAM_TYPE_VBI)
		ivtv_clear_irq_mask(itv, IVTV_IRQ_ENC_VBI_CAP);
	अन्यथा
		ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_CAPTURE);

	/* you're live! sit back and aरुको पूर्णांकerrupts :) */
	atomic_inc(&itv->capturing);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ivtv_start_v4l2_encode_stream);

अटल पूर्णांक ivtv_setup_v4l2_decode_stream(काष्ठा ivtv_stream *s)
अणु
	u32 data[CX2341X_MBOX_MAX_DATA];
	काष्ठा ivtv *itv = s->itv;
	पूर्णांक datatype;
	u16 width;
	u16 height;

	अगर (s->vdev.v4l2_dev == शून्य)
		वापस -EINVAL;

	IVTV_DEBUG_INFO("Setting some initial decoder settings\n");

	width = itv->cxhdl.width;
	height = itv->cxhdl.height;

	/* set audio mode to left/stereo  क्रम dual/stereo mode. */
	ivtv_vapi(itv, CX2341X_DEC_SET_AUDIO_MODE, 2, itv->audio_bilingual_mode, itv->audio_stereo_mode);

	/* set number of पूर्णांकernal decoder buffers */
	ivtv_vapi(itv, CX2341X_DEC_SET_DISPLAY_BUFFERS, 1, 0);

	/* prebuffering */
	ivtv_vapi(itv, CX2341X_DEC_SET_PREBUFFERING, 1, 1);

	/* extract from user packets */
	ivtv_vapi_result(itv, data, CX2341X_DEC_EXTRACT_VBI, 1, 1);
	itv->vbi.dec_start = data[0];

	IVTV_DEBUG_INFO("Decoder VBI RE-Insert start 0x%08x size 0x%08x\n",
		itv->vbi.dec_start, data[1]);

	/* set decoder source settings */
	/* Data type: 0 = mpeg from host,
	   1 = yuv from encoder,
	   2 = yuv_from_host */
	चयन (s->type) अणु
	हाल IVTV_DEC_STREAM_TYPE_YUV:
		अगर (itv->output_mode == OUT_PASSTHROUGH) अणु
			datatype = 1;
		पूर्ण अन्यथा अणु
			/* Fake size to aव्योम चयनing video standard */
			datatype = 2;
			width = 720;
			height = itv->is_out_50hz ? 576 : 480;
		पूर्ण
		IVTV_DEBUG_INFO("Setup DEC YUV Stream data[0] = %d\n", datatype);
		अवरोध;
	हाल IVTV_DEC_STREAM_TYPE_MPG:
	शेष:
		datatype = 0;
		अवरोध;
	पूर्ण
	अगर (ivtv_vapi(itv, CX2341X_DEC_SET_DECODER_SOURCE, 4, datatype,
			width, height, itv->cxhdl.audio_properties)) अणु
		IVTV_DEBUG_WARN("Couldn't initialize decoder source\n");
	पूर्ण

	/* Decoder someबार dies here, so रुको a moment */
	ivtv_msleep_समयout(10, 0);

	/* Known failure poपूर्णांक क्रम firmware, so check */
	वापस ivtv_firmware_check(itv, "ivtv_setup_v4l2_decode_stream");
पूर्ण

पूर्णांक ivtv_start_v4l2_decode_stream(काष्ठा ivtv_stream *s, पूर्णांक gop_offset)
अणु
	काष्ठा ivtv *itv = s->itv;
	पूर्णांक rc;

	अगर (s->vdev.v4l2_dev == शून्य)
		वापस -EINVAL;

	अगर (test_and_set_bit(IVTV_F_S_STREAMING, &s->s_flags))
		वापस 0;	/* alपढ़ोy started */

	IVTV_DEBUG_INFO("Starting decode stream %s (gop_offset %d)\n", s->name, gop_offset);

	rc = ivtv_setup_v4l2_decode_stream(s);
	अगर (rc < 0) अणु
		clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
		वापस rc;
	पूर्ण

	/* set dma size to 65536 bytes */
	ivtv_vapi(itv, CX2341X_DEC_SET_DMA_BLOCK_SIZE, 1, 65536);

	/* Clear Streamoff */
	clear_bit(IVTV_F_S_STREAMOFF, &s->s_flags);

	/* Zero out decoder counters */
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[0]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[1]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[2]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA_END].data[3]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[0]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[1]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[2]);
	ग_लिखोl(0, &itv->dec_mbox.mbox[IVTV_MBOX_DMA].data[3]);

	/* turn on notअगरication of dual/stereo mode change */
	ivtv_vapi(itv, CX2341X_DEC_SET_EVENT_NOTIFICATION, 4, 0, 1, IVTV_IRQ_DEC_AUD_MODE_CHG, -1);

	/* start playback */
	ivtv_vapi(itv, CX2341X_DEC_START_PLAYBACK, 2, gop_offset, 0);

	/* Let things settle beक्रमe we actually start */
	ivtv_msleep_समयout(10, 0);

	/* Clear the following Interrupt mask bits क्रम decoding */
	ivtv_clear_irq_mask(itv, IVTV_IRQ_MASK_DECODE);
	IVTV_DEBUG_IRQ("IRQ Mask is now: 0x%08x\n", itv->irqmask);

	/* you're live! sit back and aरुको पूर्णांकerrupts :) */
	atomic_inc(&itv->decoding);
	वापस 0;
पूर्ण

व्योम ivtv_stop_all_captures(काष्ठा ivtv *itv)
अणु
	पूर्णांक i;

	क्रम (i = IVTV_MAX_STREAMS - 1; i >= 0; i--) अणु
		काष्ठा ivtv_stream *s = &itv->streams[i];

		अगर (s->vdev.v4l2_dev == शून्य)
			जारी;
		अगर (test_bit(IVTV_F_S_STREAMING, &s->s_flags)) अणु
			ivtv_stop_v4l2_encode_stream(s, 0);
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक ivtv_stop_v4l2_encode_stream(काष्ठा ivtv_stream *s, पूर्णांक gop_end)
अणु
	काष्ठा ivtv *itv = s->itv;
	DECLARE_WAITQUEUE(रुको, current);
	पूर्णांक cap_type;
	पूर्णांक stopmode;

	अगर (s->vdev.v4l2_dev == शून्य)
		वापस -EINVAL;

	/* This function assumes that you are allowed to stop the capture
	   and that we are actually capturing */

	IVTV_DEBUG_INFO("Stop Capture\n");

	अगर (s->type == IVTV_DEC_STREAM_TYPE_VOUT)
		वापस 0;
	अगर (atomic_पढ़ो(&itv->capturing) == 0)
		वापस 0;

	चयन (s->type) अणु
	हाल IVTV_ENC_STREAM_TYPE_YUV:
		cap_type = 1;
		अवरोध;
	हाल IVTV_ENC_STREAM_TYPE_PCM:
		cap_type = 1;
		अवरोध;
	हाल IVTV_ENC_STREAM_TYPE_VBI:
		cap_type = 1;
		अवरोध;
	हाल IVTV_ENC_STREAM_TYPE_MPG:
	शेष:
		cap_type = 0;
		अवरोध;
	पूर्ण

	/* Stop Capture Mode */
	अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG && gop_end) अणु
		stopmode = 0;
	पूर्ण अन्यथा अणु
		stopmode = 1;
	पूर्ण

	/* end_capture */
	/* when: 0 =  end of GOP  1 = NOW!, type: 0 = mpeg, subtype: 3 = video+audio */
	ivtv_vapi(itv, CX2341X_ENC_STOP_CAPTURE, 3, stopmode, cap_type, s->subtype);

	अगर (!test_bit(IVTV_F_S_PASSTHROUGH, &s->s_flags)) अणु
		अगर (s->type == IVTV_ENC_STREAM_TYPE_MPG && gop_end) अणु
			/* only run these अगर we're shutting करोwn the last cap */
			अचिन्हित दीर्घ duration;
			अचिन्हित दीर्घ then = jअगरfies;

			add_रुको_queue(&itv->eos_रुकोq, &रुको);

			set_current_state(TASK_INTERRUPTIBLE);

			/* रुको 2s क्रम EOS पूर्णांकerrupt */
			जबतक (!test_bit(IVTV_F_I_EOS, &itv->i_flags) &&
				समय_beक्रमe(jअगरfies,
					    then + msecs_to_jअगरfies(2000))) अणु
				schedule_समयout(msecs_to_jअगरfies(10));
			पूर्ण

			/* To convert jअगरfies to ms, we must multiply by 1000
			 * and भागide by HZ.  To aव्योम runसमय भागision, we
			 * convert this to multiplication by 1000/HZ.
			 * Since पूर्णांकeger भागision truncates, we get the best
			 * accuracy अगर we करो a rounding calculation of the स्थिरant.
			 * Think of the हाल where HZ is 1024.
			 */
			duration = ((1000 + HZ / 2) / HZ) * (jअगरfies - then);

			अगर (!test_bit(IVTV_F_I_EOS, &itv->i_flags)) अणु
				IVTV_DEBUG_WARN("%s: EOS interrupt not received! stopping anyway.\n", s->name);
				IVTV_DEBUG_WARN("%s: waited %lu ms.\n", s->name, duration);
			पूर्ण अन्यथा अणु
				IVTV_DEBUG_INFO("%s: EOS took %lu ms to occur.\n", s->name, duration);
			पूर्ण
			set_current_state(TASK_RUNNING);
			हटाओ_रुको_queue(&itv->eos_रुकोq, &रुको);
			set_bit(IVTV_F_S_STREAMOFF, &s->s_flags);
		पूर्ण

		/* Handle any pending पूर्णांकerrupts */
		ivtv_msleep_समयout(100, 0);
	पूर्ण

	atomic_dec(&itv->capturing);

	/* Clear capture and no-पढ़ो bits */
	clear_bit(IVTV_F_S_STREAMING, &s->s_flags);

	अगर (s->type == IVTV_ENC_STREAM_TYPE_VBI)
		ivtv_set_irq_mask(itv, IVTV_IRQ_ENC_VBI_CAP);

	अगर (atomic_पढ़ो(&itv->capturing) > 0) अणु
		वापस 0;
	पूर्ण

	cx2341x_handler_set_busy(&itv->cxhdl, 0);

	/* Set the following Interrupt mask bits क्रम capture */
	ivtv_set_irq_mask(itv, IVTV_IRQ_MASK_CAPTURE);
	del_समयr(&itv->dma_समयr);

	/* event notअगरication (off) */
	अगर (test_and_clear_bit(IVTV_F_I_DIG_RST, &itv->i_flags)) अणु
		/* type: 0 = refresh */
		/* on/off: 0 = off, पूर्णांकr: 0x10000000, mbox_id: -1: none */
		ivtv_vapi(itv, CX2341X_ENC_SET_EVENT_NOTIFICATION, 4, 0, 0, IVTV_IRQ_ENC_VIM_RST, -1);
		ivtv_set_irq_mask(itv, IVTV_IRQ_ENC_VIM_RST);
	पूर्ण

	/* Raw-passthrough is implied on start. Make sure it's stopped so
	   the encoder will re-initialize when next started */
	ivtv_vapi(itv, CX2341X_ENC_STOP_CAPTURE, 3, 1, 2, 7);

	wake_up(&s->रुकोq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ivtv_stop_v4l2_encode_stream);

पूर्णांक ivtv_stop_v4l2_decode_stream(काष्ठा ivtv_stream *s, पूर्णांक flags, u64 pts)
अणु
	अटल स्थिर काष्ठा v4l2_event ev = अणु
		.type = V4L2_EVENT_EOS,
	पूर्ण;
	काष्ठा ivtv *itv = s->itv;

	अगर (s->vdev.v4l2_dev == शून्य)
		वापस -EINVAL;

	अगर (s->type != IVTV_DEC_STREAM_TYPE_YUV && s->type != IVTV_DEC_STREAM_TYPE_MPG)
		वापस -EINVAL;

	अगर (!test_bit(IVTV_F_S_STREAMING, &s->s_flags))
		वापस 0;

	IVTV_DEBUG_INFO("Stop Decode at %llu, flags: %x\n", (अचिन्हित दीर्घ दीर्घ)pts, flags);

	/* Stop Decoder */
	अगर (!(flags & V4L2_DEC_CMD_STOP_IMMEDIATELY) || pts) अणु
		u32 पंचांगp = 0;

		/* Wait until the decoder is no दीर्घer running */
		अगर (pts) अणु
			ivtv_vapi(itv, CX2341X_DEC_STOP_PLAYBACK, 3,
				0, (u32)(pts & 0xffffffff), (u32)(pts >> 32));
		पूर्ण
		जबतक (1) अणु
			u32 data[CX2341X_MBOX_MAX_DATA];
			ivtv_vapi_result(itv, data, CX2341X_DEC_GET_XFER_INFO, 0);
			अगर (s->q_full.buffers + s->q_dma.buffers == 0) अणु
				अगर (पंचांगp == data[3])
					अवरोध;
				पंचांगp = data[3];
			पूर्ण
			अगर (ivtv_msleep_समयout(100, 1))
				अवरोध;
		पूर्ण
	पूर्ण
	ivtv_vapi(itv, CX2341X_DEC_STOP_PLAYBACK, 3, flags & V4L2_DEC_CMD_STOP_TO_BLACK, 0, 0);

	/* turn off notअगरication of dual/stereo mode change */
	ivtv_vapi(itv, CX2341X_DEC_SET_EVENT_NOTIFICATION, 4, 0, 0, IVTV_IRQ_DEC_AUD_MODE_CHG, -1);

	ivtv_set_irq_mask(itv, IVTV_IRQ_MASK_DECODE);
	del_समयr(&itv->dma_समयr);

	clear_bit(IVTV_F_S_NEEDS_DATA, &s->s_flags);
	clear_bit(IVTV_F_S_STREAMING, &s->s_flags);
	ivtv_flush_queues(s);

	/* decoder needs समय to settle */
	ivtv_msleep_समयout(40, 0);

	/* decrement decoding */
	atomic_dec(&itv->decoding);

	set_bit(IVTV_F_I_EV_DEC_STOPPED, &itv->i_flags);
	wake_up(&itv->event_रुकोq);
	v4l2_event_queue(&s->vdev, &ev);

	/* wake up रुको queues */
	wake_up(&s->रुकोq);

	वापस 0;
पूर्ण

पूर्णांक ivtv_passthrough_mode(काष्ठा ivtv *itv, पूर्णांक enable)
अणु
	काष्ठा ivtv_stream *yuv_stream = &itv->streams[IVTV_ENC_STREAM_TYPE_YUV];
	काष्ठा ivtv_stream *dec_stream = &itv->streams[IVTV_DEC_STREAM_TYPE_YUV];

	अगर (yuv_stream->vdev.v4l2_dev == शून्य || dec_stream->vdev.v4l2_dev == शून्य)
		वापस -EINVAL;

	IVTV_DEBUG_INFO("ivtv ioctl: Select passthrough mode\n");

	/* Prevent others from starting/stopping streams जबतक we
	   initiate/terminate passthrough mode */
	अगर (enable) अणु
		अगर (itv->output_mode == OUT_PASSTHROUGH) अणु
			वापस 0;
		पूर्ण
		अगर (ivtv_set_output_mode(itv, OUT_PASSTHROUGH) != OUT_PASSTHROUGH)
			वापस -EBUSY;

		/* Fully initialize stream, and then unflag init */
		set_bit(IVTV_F_S_PASSTHROUGH, &dec_stream->s_flags);
		set_bit(IVTV_F_S_STREAMING, &dec_stream->s_flags);

		/* Setup YUV Decoder */
		ivtv_setup_v4l2_decode_stream(dec_stream);

		/* Start Decoder */
		ivtv_vapi(itv, CX2341X_DEC_START_PLAYBACK, 2, 0, 1);
		atomic_inc(&itv->decoding);

		/* Setup capture अगर not alपढ़ोy करोne */
		अगर (atomic_पढ़ो(&itv->capturing) == 0) अणु
			cx2341x_handler_setup(&itv->cxhdl);
			cx2341x_handler_set_busy(&itv->cxhdl, 1);
		पूर्ण

		/* Start Passthrough Mode */
		ivtv_vapi(itv, CX2341X_ENC_START_CAPTURE, 2, 2, 11);
		atomic_inc(&itv->capturing);
		वापस 0;
	पूर्ण

	अगर (itv->output_mode != OUT_PASSTHROUGH)
		वापस 0;

	/* Stop Passthrough Mode */
	ivtv_vapi(itv, CX2341X_ENC_STOP_CAPTURE, 3, 1, 2, 11);
	ivtv_vapi(itv, CX2341X_DEC_STOP_PLAYBACK, 3, 1, 0, 0);

	atomic_dec(&itv->capturing);
	atomic_dec(&itv->decoding);
	clear_bit(IVTV_F_S_PASSTHROUGH, &dec_stream->s_flags);
	clear_bit(IVTV_F_S_STREAMING, &dec_stream->s_flags);
	itv->output_mode = OUT_NONE;
	अगर (atomic_पढ़ो(&itv->capturing) == 0)
		cx2341x_handler_set_busy(&itv->cxhdl, 0);

	वापस 0;
पूर्ण
