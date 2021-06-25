<शैली गुरु>
/*
 * Copyright (c) 2013,2016 Lubomir Rपूर्णांकel
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
 * Product web site:
 * http://www.fushicai.com/products_detail/&productId=d05449ee-b690-42f9-a661-aa7353894bed.hपंचांगl
 *
 * Following LWN articles were very useful in स्थिरruction of this driver:
 * Video4Linux2 API series: http://lwn.net/Articles/203924/
 * videobuf2 API explanation: http://lwn.net/Articles/447435/
 * Thanks go to Jonathan Corbet क्रम providing this quality करोcumentation.
 * He is awesome.
 *
 * No physical hardware was harmed running Winकरोws during the
 * reverse-engineering activity
 */

#समावेश <media/v4l2-ioctl.h>
#समावेश <media/videobuf2-v4l2.h>

#समावेश "usbtv.h"

अटल स्थिर काष्ठा usbtv_norm_params norm_params[] = अणु
	अणु
		.norm = V4L2_STD_525_60,
		.cap_width = 720,
		.cap_height = 480,
	पूर्ण,
	अणु
		.norm = V4L2_STD_625_50,
		.cap_width = 720,
		.cap_height = 576,
	पूर्ण
पूर्ण;

अटल पूर्णांक usbtv_configure_क्रम_norm(काष्ठा usbtv *usbtv, v4l2_std_id norm)
अणु
	पूर्णांक i, ret = 0;
	स्थिर काष्ठा usbtv_norm_params *params = शून्य;

	क्रम (i = 0; i < ARRAY_SIZE(norm_params); i++) अणु
		अगर (norm_params[i].norm & norm) अणु
			params = &norm_params[i];
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (params) अणु
		usbtv->width = params->cap_width;
		usbtv->height = params->cap_height;
		usbtv->n_chunks = usbtv->width * usbtv->height
						/ 4 / USBTV_CHUNK;
		usbtv->norm = norm;
	पूर्ण अन्यथा
		ret = -EINVAL;

	वापस ret;
पूर्ण

अटल पूर्णांक usbtv_select_input(काष्ठा usbtv *usbtv, पूर्णांक input)
अणु
	पूर्णांक ret;

	अटल स्थिर u16 composite[][2] = अणु
		अणु USBTV_BASE + 0x0105, 0x0060 पूर्ण,
		अणु USBTV_BASE + 0x011f, 0x00f2 पूर्ण,
		अणु USBTV_BASE + 0x0127, 0x0060 पूर्ण,
		अणु USBTV_BASE + 0x00ae, 0x0010 पूर्ण,
		अणु USBTV_BASE + 0x0239, 0x0060 पूर्ण,
	पूर्ण;

	अटल स्थिर u16 svideo[][2] = अणु
		अणु USBTV_BASE + 0x0105, 0x0010 पूर्ण,
		अणु USBTV_BASE + 0x011f, 0x00ff पूर्ण,
		अणु USBTV_BASE + 0x0127, 0x0060 पूर्ण,
		अणु USBTV_BASE + 0x00ae, 0x0030 पूर्ण,
		अणु USBTV_BASE + 0x0239, 0x0060 पूर्ण,
	पूर्ण;

	चयन (input) अणु
	हाल USBTV_COMPOSITE_INPUT:
		ret = usbtv_set_regs(usbtv, composite, ARRAY_SIZE(composite));
		अवरोध;
	हाल USBTV_SVIDEO_INPUT:
		ret = usbtv_set_regs(usbtv, svideo, ARRAY_SIZE(svideo));
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	अगर (!ret)
		usbtv->input = input;

	वापस ret;
पूर्ण

अटल uपूर्णांक16_t usbtv_norm_to_16f_reg(v4l2_std_id norm)
अणु
	/* NTSC M/M-JP/M-KR */
	अगर (norm & V4L2_STD_NTSC)
		वापस 0x00b8;
	/* PAL BG/DK/H/I */
	अगर (norm & V4L2_STD_PAL)
		वापस 0x00ee;
	/* SECAM B/D/G/H/K/K1/L/Lc */
	अगर (norm & V4L2_STD_SECAM)
		वापस 0x00ff;
	अगर (norm & V4L2_STD_NTSC_443)
		वापस 0x00a8;
	अगर (norm & (V4L2_STD_PAL_M | V4L2_STD_PAL_60))
		वापस 0x00bc;
	/* Fallback to स्वतःmatic detection क्रम other standards */
	वापस 0x0000;
पूर्ण

अटल पूर्णांक usbtv_select_norm(काष्ठा usbtv *usbtv, v4l2_std_id norm)
अणु
	पूर्णांक ret;
	/* These are the series of रेजिस्टर values used to configure the
	 * decoder क्रम a specअगरic standard.
	 * The first 21 रेजिस्टर ग_लिखोs are copied from the
	 * Settings\DecoderDefaults registry keys present in the Winकरोws driver
	 * .INF file, and control various image tuning parameters (color
	 * correction, sharpness, ...).
	 */
	अटल स्थिर u16 pal[][2] = अणु
		/* "AVPAL" tuning sequence from .INF file */
		अणु USBTV_BASE + 0x0003, 0x0004 पूर्ण,
		अणु USBTV_BASE + 0x001a, 0x0068 पूर्ण,
		अणु USBTV_BASE + 0x0100, 0x00d3 पूर्ण,
		अणु USBTV_BASE + 0x010e, 0x0072 पूर्ण,
		अणु USBTV_BASE + 0x010f, 0x00a2 पूर्ण,
		अणु USBTV_BASE + 0x0112, 0x00b0 पूर्ण,
		अणु USBTV_BASE + 0x0115, 0x0015 पूर्ण,
		अणु USBTV_BASE + 0x0117, 0x0001 पूर्ण,
		अणु USBTV_BASE + 0x0118, 0x002c पूर्ण,
		अणु USBTV_BASE + 0x012d, 0x0010 पूर्ण,
		अणु USBTV_BASE + 0x012f, 0x0020 पूर्ण,
		अणु USBTV_BASE + 0x0220, 0x002e पूर्ण,
		अणु USBTV_BASE + 0x0225, 0x0008 पूर्ण,
		अणु USBTV_BASE + 0x024e, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x024f, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x0254, 0x0059 पूर्ण,
		अणु USBTV_BASE + 0x025a, 0x0016 पूर्ण,
		अणु USBTV_BASE + 0x025b, 0x0035 पूर्ण,
		अणु USBTV_BASE + 0x0263, 0x0017 पूर्ण,
		अणु USBTV_BASE + 0x0266, 0x0016 पूर्ण,
		अणु USBTV_BASE + 0x0267, 0x0036 पूर्ण,
		/* End image tuning */
		अणु USBTV_BASE + 0x024e, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x024f, 0x0002 पूर्ण,
	पूर्ण;

	अटल स्थिर u16 ntsc[][2] = अणु
		/* "AVNTSC" tuning sequence from .INF file */
		अणु USBTV_BASE + 0x0003, 0x0004 पूर्ण,
		अणु USBTV_BASE + 0x001a, 0x0079 पूर्ण,
		अणु USBTV_BASE + 0x0100, 0x00d3 पूर्ण,
		अणु USBTV_BASE + 0x010e, 0x0068 पूर्ण,
		अणु USBTV_BASE + 0x010f, 0x009c पूर्ण,
		अणु USBTV_BASE + 0x0112, 0x00f0 पूर्ण,
		अणु USBTV_BASE + 0x0115, 0x0015 पूर्ण,
		अणु USBTV_BASE + 0x0117, 0x0000 पूर्ण,
		अणु USBTV_BASE + 0x0118, 0x00fc पूर्ण,
		अणु USBTV_BASE + 0x012d, 0x0004 पूर्ण,
		अणु USBTV_BASE + 0x012f, 0x0008 पूर्ण,
		अणु USBTV_BASE + 0x0220, 0x002e पूर्ण,
		अणु USBTV_BASE + 0x0225, 0x0008 पूर्ण,
		अणु USBTV_BASE + 0x024e, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x024f, 0x0001 पूर्ण,
		अणु USBTV_BASE + 0x0254, 0x005f पूर्ण,
		अणु USBTV_BASE + 0x025a, 0x0012 पूर्ण,
		अणु USBTV_BASE + 0x025b, 0x0001 पूर्ण,
		अणु USBTV_BASE + 0x0263, 0x001c पूर्ण,
		अणु USBTV_BASE + 0x0266, 0x0011 पूर्ण,
		अणु USBTV_BASE + 0x0267, 0x0005 पूर्ण,
		/* End image tuning */
		अणु USBTV_BASE + 0x024e, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x024f, 0x0002 पूर्ण,
	पूर्ण;

	अटल स्थिर u16 secam[][2] = अणु
		/* "AVSECAM" tuning sequence from .INF file */
		अणु USBTV_BASE + 0x0003, 0x0004 पूर्ण,
		अणु USBTV_BASE + 0x001a, 0x0073 पूर्ण,
		अणु USBTV_BASE + 0x0100, 0x00dc पूर्ण,
		अणु USBTV_BASE + 0x010e, 0x0072 पूर्ण,
		अणु USBTV_BASE + 0x010f, 0x00a2 पूर्ण,
		अणु USBTV_BASE + 0x0112, 0x0090 पूर्ण,
		अणु USBTV_BASE + 0x0115, 0x0035 पूर्ण,
		अणु USBTV_BASE + 0x0117, 0x0001 पूर्ण,
		अणु USBTV_BASE + 0x0118, 0x0030 पूर्ण,
		अणु USBTV_BASE + 0x012d, 0x0004 पूर्ण,
		अणु USBTV_BASE + 0x012f, 0x0008 पूर्ण,
		अणु USBTV_BASE + 0x0220, 0x002d पूर्ण,
		अणु USBTV_BASE + 0x0225, 0x0028 पूर्ण,
		अणु USBTV_BASE + 0x024e, 0x0008 पूर्ण,
		अणु USBTV_BASE + 0x024f, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x0254, 0x0069 पूर्ण,
		अणु USBTV_BASE + 0x025a, 0x0016 पूर्ण,
		अणु USBTV_BASE + 0x025b, 0x0035 पूर्ण,
		अणु USBTV_BASE + 0x0263, 0x0021 पूर्ण,
		अणु USBTV_BASE + 0x0266, 0x0016 पूर्ण,
		अणु USBTV_BASE + 0x0267, 0x0036 पूर्ण,
		/* End image tuning */
		अणु USBTV_BASE + 0x024e, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x024f, 0x0002 पूर्ण,
	पूर्ण;

	ret = usbtv_configure_क्रम_norm(usbtv, norm);

	अगर (!ret) अणु
		/* Masks क्रम norms using a NTSC or PAL color encoding. */
		अटल स्थिर v4l2_std_id ntsc_mask =
			V4L2_STD_NTSC | V4L2_STD_NTSC_443;
		अटल स्थिर v4l2_std_id pal_mask =
			V4L2_STD_PAL | V4L2_STD_PAL_60 | V4L2_STD_PAL_M;

		अगर (norm & ntsc_mask)
			ret = usbtv_set_regs(usbtv, ntsc, ARRAY_SIZE(ntsc));
		अन्यथा अगर (norm & pal_mask)
			ret = usbtv_set_regs(usbtv, pal, ARRAY_SIZE(pal));
		अन्यथा अगर (norm & V4L2_STD_SECAM)
			ret = usbtv_set_regs(usbtv, secam, ARRAY_SIZE(secam));
		अन्यथा
			ret = -EINVAL;
	पूर्ण

	अगर (!ret) अणु
		/* Configure the decoder क्रम the color standard */
		स्थिर u16 cfg[][2] = अणु
			अणु USBTV_BASE + 0x016f, usbtv_norm_to_16f_reg(norm) पूर्ण
		पूर्ण;
		ret = usbtv_set_regs(usbtv, cfg, ARRAY_SIZE(cfg));
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक usbtv_setup_capture(काष्ठा usbtv *usbtv)
अणु
	पूर्णांक ret;
	अटल स्थिर u16 setup[][2] = अणु
		/* These seem to enable the device. */
		अणु USBTV_BASE + 0x0008, 0x0001 पूर्ण,
		अणु USBTV_BASE + 0x01d0, 0x00ff पूर्ण,
		अणु USBTV_BASE + 0x01d9, 0x0002 पूर्ण,

		/* These seem to influence color parameters, such as
		 * brightness, etc. */
		अणु USBTV_BASE + 0x0239, 0x0040 पूर्ण,
		अणु USBTV_BASE + 0x0240, 0x0000 पूर्ण,
		अणु USBTV_BASE + 0x0241, 0x0000 पूर्ण,
		अणु USBTV_BASE + 0x0242, 0x0002 पूर्ण,
		अणु USBTV_BASE + 0x0243, 0x0080 पूर्ण,
		अणु USBTV_BASE + 0x0244, 0x0012 पूर्ण,
		अणु USBTV_BASE + 0x0245, 0x0090 पूर्ण,
		अणु USBTV_BASE + 0x0246, 0x0000 पूर्ण,

		अणु USBTV_BASE + 0x0278, 0x002d पूर्ण,
		अणु USBTV_BASE + 0x0279, 0x000a पूर्ण,
		अणु USBTV_BASE + 0x027a, 0x0032 पूर्ण,
		अणु 0xf890, 0x000c पूर्ण,
		अणु 0xf894, 0x0086 पूर्ण,

		अणु USBTV_BASE + 0x00ac, 0x00c0 पूर्ण,
		अणु USBTV_BASE + 0x00ad, 0x0000 पूर्ण,
		अणु USBTV_BASE + 0x00a2, 0x0012 पूर्ण,
		अणु USBTV_BASE + 0x00a3, 0x00e0 पूर्ण,
		अणु USBTV_BASE + 0x00a4, 0x0028 पूर्ण,
		अणु USBTV_BASE + 0x00a5, 0x0082 पूर्ण,
		अणु USBTV_BASE + 0x00a7, 0x0080 पूर्ण,
		अणु USBTV_BASE + 0x0000, 0x0014 पूर्ण,
		अणु USBTV_BASE + 0x0006, 0x0003 पूर्ण,
		अणु USBTV_BASE + 0x0090, 0x0099 पूर्ण,
		अणु USBTV_BASE + 0x0091, 0x0090 पूर्ण,
		अणु USBTV_BASE + 0x0094, 0x0068 पूर्ण,
		अणु USBTV_BASE + 0x0095, 0x0070 पूर्ण,
		अणु USBTV_BASE + 0x009c, 0x0030 पूर्ण,
		अणु USBTV_BASE + 0x009d, 0x00c0 पूर्ण,
		अणु USBTV_BASE + 0x009e, 0x00e0 पूर्ण,
		अणु USBTV_BASE + 0x0019, 0x0006 पूर्ण,
		अणु USBTV_BASE + 0x008c, 0x00ba पूर्ण,
		अणु USBTV_BASE + 0x0101, 0x00ff पूर्ण,
		अणु USBTV_BASE + 0x010c, 0x00b3 पूर्ण,
		अणु USBTV_BASE + 0x01b2, 0x0080 पूर्ण,
		अणु USBTV_BASE + 0x01b4, 0x00a0 पूर्ण,
		अणु USBTV_BASE + 0x014c, 0x00ff पूर्ण,
		अणु USBTV_BASE + 0x014d, 0x00ca पूर्ण,
		अणु USBTV_BASE + 0x0113, 0x0053 पूर्ण,
		अणु USBTV_BASE + 0x0119, 0x008a पूर्ण,
		अणु USBTV_BASE + 0x013c, 0x0003 पूर्ण,
		अणु USBTV_BASE + 0x0150, 0x009c पूर्ण,
		अणु USBTV_BASE + 0x0151, 0x0071 पूर्ण,
		अणु USBTV_BASE + 0x0152, 0x00c6 पूर्ण,
		अणु USBTV_BASE + 0x0153, 0x0084 पूर्ण,
		अणु USBTV_BASE + 0x0154, 0x00bc पूर्ण,
		अणु USBTV_BASE + 0x0155, 0x00a0 पूर्ण,
		अणु USBTV_BASE + 0x0156, 0x00a0 पूर्ण,
		अणु USBTV_BASE + 0x0157, 0x009c पूर्ण,
		अणु USBTV_BASE + 0x0158, 0x001f पूर्ण,
		अणु USBTV_BASE + 0x0159, 0x0006 पूर्ण,
		अणु USBTV_BASE + 0x015d, 0x0000 पूर्ण,
	पूर्ण;

	ret = usbtv_set_regs(usbtv, setup, ARRAY_SIZE(setup));
	अगर (ret)
		वापस ret;

	ret = usbtv_select_norm(usbtv, usbtv->norm);
	अगर (ret)
		वापस ret;

	ret = usbtv_select_input(usbtv, usbtv->input);
	अगर (ret)
		वापस ret;

	ret = v4l2_ctrl_handler_setup(&usbtv->ctrl);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

/* Copy data from chunk पूर्णांकo a frame buffer, deपूर्णांकerlacing the data
 * पूर्णांकo every second line. Unक्रमtunately, they करोn't align nicely पूर्णांकo
 * 720 pixel lines, as the chunk is 240 words दीर्घ, which is 480 pixels.
 * Thereक्रमe, we अवरोध करोwn the chunk पूर्णांकo two halves beक्रमe copying,
 * so that we can पूर्णांकerleave a line अगर needed.
 *
 * Each "chunk" is 240 words; a word in this context equals 4 bytes.
 * Image क्रमmat is YUYV/YUV 4:2:2, consisting of Y Cr Y Cb, defining two
 * pixels, the Cr and Cb shared between the two pixels, but each having
 * separate Y values. Thus, the 240 words equal 480 pixels. It thereक्रमe,
 * takes 1.5 chunks to make a 720 pixel-wide line क्रम the frame.
 * The image is पूर्णांकerlaced, so there is a "scan" of odd lines, followed
 * by "scan" of even numbered lines.
 *
 * Following code is writing the chunks in correct sequence, skipping
 * the rows based on "odd" value.
 * line 1: chunk[0][  0..479] chunk[0][480..959] chunk[1][  0..479]
 * line 3: chunk[1][480..959] chunk[2][  0..479] chunk[2][480..959]
 * ...etc.
 */
अटल व्योम usbtv_chunk_to_vbuf(u32 *frame, __be32 *src, पूर्णांक chunk_no, पूर्णांक odd)
अणु
	पूर्णांक half;

	क्रम (half = 0; half < 2; half++) अणु
		पूर्णांक part_no = chunk_no * 2 + half;
		पूर्णांक line = part_no / 3;
		पूर्णांक part_index = (line * 2 + !odd) * 3 + (part_no % 3);

		u32 *dst = &frame[part_index * USBTV_CHUNK/2];

		स_नकल(dst, src, USBTV_CHUNK/2 * माप(*src));
		src += USBTV_CHUNK/2;
	पूर्ण
पूर्ण

/* Called क्रम each 256-byte image chunk.
 * First word identअगरies the chunk, followed by 240 words of image
 * data and padding. */
अटल व्योम usbtv_image_chunk(काष्ठा usbtv *usbtv, __be32 *chunk)
अणु
	पूर्णांक frame_id, odd, chunk_no;
	u32 *frame;
	काष्ठा usbtv_buf *buf;
	अचिन्हित दीर्घ flags;

	/* Ignore corrupted lines. */
	अगर (!USBTV_MAGIC_OK(chunk))
		वापस;
	frame_id = USBTV_FRAME_ID(chunk);
	odd = USBTV_ODD(chunk);
	chunk_no = USBTV_CHUNK_NO(chunk);
	अगर (chunk_no >= usbtv->n_chunks)
		वापस;

	/* Beginning of a frame. */
	अगर (chunk_no == 0) अणु
		usbtv->frame_id = frame_id;
		usbtv->chunks_करोne = 0;
	पूर्ण

	अगर (usbtv->frame_id != frame_id)
		वापस;

	spin_lock_irqsave(&usbtv->buflock, flags);
	अगर (list_empty(&usbtv->bufs)) अणु
		/* No मुक्त buffers. Userspace likely too slow. */
		spin_unlock_irqrestore(&usbtv->buflock, flags);
		वापस;
	पूर्ण

	/* First available buffer. */
	buf = list_first_entry(&usbtv->bufs, काष्ठा usbtv_buf, list);
	frame = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);

	/* Copy the chunk data. */
	usbtv_chunk_to_vbuf(frame, &chunk[1], chunk_no, odd);
	usbtv->chunks_करोne++;

	/* Last chunk in a field */
	अगर (chunk_no == usbtv->n_chunks-1) अणु
		/* Last chunk in a frame, संकेतling an end */
		अगर (odd && !usbtv->last_odd) अणु
			पूर्णांक size = vb2_plane_size(&buf->vb.vb2_buf, 0);
			क्रमागत vb2_buffer_state state = usbtv->chunks_करोne ==
				usbtv->n_chunks ?
				VB2_BUF_STATE_DONE :
				VB2_BUF_STATE_ERROR;

			buf->vb.field = V4L2_FIELD_INTERLACED;
			buf->vb.sequence = usbtv->sequence++;
			buf->vb.vb2_buf.बारtamp = kसमय_get_ns();
			vb2_set_plane_payload(&buf->vb.vb2_buf, 0, size);
			vb2_buffer_करोne(&buf->vb.vb2_buf, state);
			list_del(&buf->list);
		पूर्ण
		usbtv->last_odd = odd;
	पूर्ण

	spin_unlock_irqrestore(&usbtv->buflock, flags);
पूर्ण

/* Got image data. Each packet contains a number of 256-word chunks we
 * compose the image from. */
अटल व्योम usbtv_iso_cb(काष्ठा urb *ip)
अणु
	पूर्णांक ret;
	पूर्णांक i;
	काष्ठा usbtv *usbtv = (काष्ठा usbtv *)ip->context;

	चयन (ip->status) अणु
	/* All fine. */
	हाल 0:
		अवरोध;
	/* Device disconnected or capture stopped? */
	हाल -ENODEV:
	हाल -ENOENT:
	हाल -ECONNRESET:
	हाल -ESHUTDOWN:
		वापस;
	/* Unknown error. Retry. */
	शेष:
		dev_warn(usbtv->dev, "Bad response for ISO request.\n");
		जाओ resubmit;
	पूर्ण

	क्रम (i = 0; i < ip->number_of_packets; i++) अणु
		पूर्णांक size = ip->iso_frame_desc[i].actual_length;
		अचिन्हित अक्षर *data = ip->transfer_buffer +
				ip->iso_frame_desc[i].offset;
		पूर्णांक offset;

		क्रम (offset = 0; USBTV_CHUNK_SIZE * offset < size; offset++)
			usbtv_image_chunk(usbtv,
				(__be32 *)&data[USBTV_CHUNK_SIZE * offset]);
	पूर्ण

resubmit:
	ret = usb_submit_urb(ip, GFP_ATOMIC);
	अगर (ret < 0)
		dev_warn(usbtv->dev, "Could not resubmit ISO URB\n");
पूर्ण

अटल काष्ठा urb *usbtv_setup_iso_transfer(काष्ठा usbtv *usbtv)
अणु
	काष्ठा urb *ip;
	पूर्णांक size = usbtv->iso_size;
	पूर्णांक i;

	ip = usb_alloc_urb(USBTV_ISOC_PACKETS, GFP_KERNEL);
	अगर (ip == शून्य)
		वापस शून्य;

	ip->dev = usbtv->udev;
	ip->context = usbtv;
	ip->pipe = usb_rcvisocpipe(usbtv->udev, USBTV_VIDEO_ENDP);
	ip->पूर्णांकerval = 1;
	ip->transfer_flags = URB_ISO_ASAP;
	ip->transfer_buffer = kसुस्मृति(USBTV_ISOC_PACKETS, size,
						GFP_KERNEL);
	अगर (!ip->transfer_buffer) अणु
		usb_मुक्त_urb(ip);
		वापस शून्य;
	पूर्ण
	ip->complete = usbtv_iso_cb;
	ip->number_of_packets = USBTV_ISOC_PACKETS;
	ip->transfer_buffer_length = size * USBTV_ISOC_PACKETS;
	क्रम (i = 0; i < USBTV_ISOC_PACKETS; i++) अणु
		ip->iso_frame_desc[i].offset = size * i;
		ip->iso_frame_desc[i].length = size;
	पूर्ण

	वापस ip;
पूर्ण

अटल व्योम usbtv_stop(काष्ठा usbtv *usbtv)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	/* Cancel running transfers. */
	क्रम (i = 0; i < USBTV_ISOC_TRANSFERS; i++) अणु
		काष्ठा urb *ip = usbtv->isoc_urbs[i];

		अगर (ip == शून्य)
			जारी;
		usb_समाप्त_urb(ip);
		kमुक्त(ip->transfer_buffer);
		usb_मुक्त_urb(ip);
		usbtv->isoc_urbs[i] = शून्य;
	पूर्ण

	/* Return buffers to userspace. */
	spin_lock_irqsave(&usbtv->buflock, flags);
	जबतक (!list_empty(&usbtv->bufs)) अणु
		काष्ठा usbtv_buf *buf = list_first_entry(&usbtv->bufs,
						काष्ठा usbtv_buf, list);
		vb2_buffer_करोne(&buf->vb.vb2_buf, VB2_BUF_STATE_ERROR);
		list_del(&buf->list);
	पूर्ण
	spin_unlock_irqrestore(&usbtv->buflock, flags);
पूर्ण

अटल पूर्णांक usbtv_start(काष्ठा usbtv *usbtv)
अणु
	पूर्णांक i;
	पूर्णांक ret;

	usbtv_audio_suspend(usbtv);

	ret = usb_set_पूर्णांकerface(usbtv->udev, 0, 0);
	अगर (ret < 0)
		वापस ret;

	ret = usbtv_setup_capture(usbtv);
	अगर (ret < 0)
		वापस ret;

	ret = usb_set_पूर्णांकerface(usbtv->udev, 0, 1);
	अगर (ret < 0)
		वापस ret;

	usbtv_audio_resume(usbtv);

	क्रम (i = 0; i < USBTV_ISOC_TRANSFERS; i++) अणु
		काष्ठा urb *ip;

		ip = usbtv_setup_iso_transfer(usbtv);
		अगर (ip == शून्य) अणु
			ret = -ENOMEM;
			जाओ start_fail;
		पूर्ण
		usbtv->isoc_urbs[i] = ip;

		ret = usb_submit_urb(ip, GFP_KERNEL);
		अगर (ret < 0)
			जाओ start_fail;
	पूर्ण

	वापस 0;

start_fail:
	usbtv_stop(usbtv);
	वापस ret;
पूर्ण

अटल पूर्णांक usbtv_querycap(काष्ठा file *file, व्योम *priv,
				काष्ठा v4l2_capability *cap)
अणु
	काष्ठा usbtv *dev = video_drvdata(file);

	strscpy(cap->driver, "usbtv", माप(cap->driver));
	strscpy(cap->card, "usbtv", माप(cap->card));
	usb_make_path(dev->udev, cap->bus_info, माप(cap->bus_info));
	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_क्रमागत_input(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_input *i)
अणु
	काष्ठा usbtv *dev = video_drvdata(file);

	चयन (i->index) अणु
	हाल USBTV_COMPOSITE_INPUT:
		strscpy(i->name, "Composite", माप(i->name));
		अवरोध;
	हाल USBTV_SVIDEO_INPUT:
		strscpy(i->name, "S-Video", माप(i->name));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	i->type = V4L2_INPUT_TYPE_CAMERA;
	i->std = dev->vdev.tvnorms;
	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम  *priv,
					काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index > 0)
		वापस -EINVAL;

	f->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_fmt_vid_cap(काष्ठा file *file, व्योम *priv,
					काष्ठा v4l2_क्रमmat *f)
अणु
	काष्ठा usbtv *usbtv = video_drvdata(file);

	f->fmt.pix.width = usbtv->width;
	f->fmt.pix.height = usbtv->height;
	f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUYV;
	f->fmt.pix.field = V4L2_FIELD_INTERLACED;
	f->fmt.pix.bytesperline = usbtv->width * 2;
	f->fmt.pix.sizeimage = (f->fmt.pix.bytesperline * f->fmt.pix.height);
	f->fmt.pix.colorspace = V4L2_COLORSPACE_SMPTE170M;

	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_g_std(काष्ठा file *file, व्योम *priv, v4l2_std_id *norm)
अणु
	काष्ठा usbtv *usbtv = video_drvdata(file);
	*norm = usbtv->norm;
	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_s_std(काष्ठा file *file, व्योम *priv, v4l2_std_id norm)
अणु
	पूर्णांक ret = -EINVAL;
	काष्ठा usbtv *usbtv = video_drvdata(file);

	अगर (norm & USBTV_TV_STD)
		ret = usbtv_select_norm(usbtv, norm);

	वापस ret;
पूर्ण

अटल पूर्णांक usbtv_g_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक *i)
अणु
	काष्ठा usbtv *usbtv = video_drvdata(file);
	*i = usbtv->input;
	वापस 0;
पूर्ण

अटल पूर्णांक usbtv_s_input(काष्ठा file *file, व्योम *priv, अचिन्हित पूर्णांक i)
अणु
	काष्ठा usbtv *usbtv = video_drvdata(file);

	वापस usbtv_select_input(usbtv, i);
पूर्ण

अटल स्थिर काष्ठा v4l2_ioctl_ops usbtv_ioctl_ops = अणु
	.vidioc_querycap = usbtv_querycap,
	.vidioc_क्रमागत_input = usbtv_क्रमागत_input,
	.vidioc_क्रमागत_fmt_vid_cap = usbtv_क्रमागत_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap = usbtv_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap = usbtv_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap = usbtv_fmt_vid_cap,
	.vidioc_g_std = usbtv_g_std,
	.vidioc_s_std = usbtv_s_std,
	.vidioc_g_input = usbtv_g_input,
	.vidioc_s_input = usbtv_s_input,

	.vidioc_reqbufs = vb2_ioctl_reqbufs,
	.vidioc_prepare_buf = vb2_ioctl_prepare_buf,
	.vidioc_querybuf = vb2_ioctl_querybuf,
	.vidioc_create_bufs = vb2_ioctl_create_bufs,
	.vidioc_qbuf = vb2_ioctl_qbuf,
	.vidioc_dqbuf = vb2_ioctl_dqbuf,
	.vidioc_streamon = vb2_ioctl_streamon,
	.vidioc_streamoff = vb2_ioctl_streamoff,
पूर्ण;

अटल स्थिर काष्ठा v4l2_file_operations usbtv_fops = अणु
	.owner = THIS_MODULE,
	.unlocked_ioctl = video_ioctl2,
	.mmap = vb2_fop_mmap,
	.खोलो = v4l2_fh_खोलो,
	.release = vb2_fop_release,
	.पढ़ो = vb2_fop_पढ़ो,
	.poll = vb2_fop_poll,
पूर्ण;

अटल पूर्णांक usbtv_queue_setup(काष्ठा vb2_queue *vq,
	अचिन्हित पूर्णांक *nbuffers,
	अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[], काष्ठा device *alloc_devs[])
अणु
	काष्ठा usbtv *usbtv = vb2_get_drv_priv(vq);
	अचिन्हित size = USBTV_CHUNK * usbtv->n_chunks * 2 * माप(u32);

	अगर (vq->num_buffers + *nbuffers < 2)
		*nbuffers = 2 - vq->num_buffers;
	अगर (*nplanes)
		वापस sizes[0] < size ? -EINVAL : 0;
	*nplanes = 1;
	sizes[0] = size;

	वापस 0;
पूर्ण

अटल व्योम usbtv_buf_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा usbtv *usbtv = vb2_get_drv_priv(vb->vb2_queue);
	काष्ठा usbtv_buf *buf = container_of(vbuf, काष्ठा usbtv_buf, vb);
	अचिन्हित दीर्घ flags;

	अगर (usbtv->udev == शून्य) अणु
		vb2_buffer_करोne(vb, VB2_BUF_STATE_ERROR);
		वापस;
	पूर्ण

	spin_lock_irqsave(&usbtv->buflock, flags);
	list_add_tail(&buf->list, &usbtv->bufs);
	spin_unlock_irqrestore(&usbtv->buflock, flags);
पूर्ण

अटल पूर्णांक usbtv_start_streaming(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा usbtv *usbtv = vb2_get_drv_priv(vq);

	अगर (usbtv->udev == शून्य)
		वापस -ENODEV;

	usbtv->last_odd = 1;
	usbtv->sequence = 0;
	वापस usbtv_start(usbtv);
पूर्ण

अटल व्योम usbtv_stop_streaming(काष्ठा vb2_queue *vq)
अणु
	काष्ठा usbtv *usbtv = vb2_get_drv_priv(vq);

	अगर (usbtv->udev)
		usbtv_stop(usbtv);
पूर्ण

अटल स्थिर काष्ठा vb2_ops usbtv_vb2_ops = अणु
	.queue_setup = usbtv_queue_setup,
	.buf_queue = usbtv_buf_queue,
	.start_streaming = usbtv_start_streaming,
	.stop_streaming = usbtv_stop_streaming,
	.रुको_prepare = vb2_ops_रुको_prepare,
	.रुको_finish = vb2_ops_रुको_finish,
पूर्ण;

अटल पूर्णांक usbtv_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	काष्ठा usbtv *usbtv = container_of(ctrl->handler, काष्ठा usbtv,
								ctrl);
	u8 *data;
	u16 index, size;
	पूर्णांक ret;

	data = kदो_स्मृति(3, GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	/*
	 * Read in the current brightness/contrast रेजिस्टरs. We need them
	 * both, because the values are क्रम some reason पूर्णांकerleaved.
	 */
	अगर (ctrl->id == V4L2_CID_BRIGHTNESS || ctrl->id == V4L2_CID_CONTRAST) अणु
		ret = usb_control_msg(usbtv->udev,
			usb_rcvctrlpipe(usbtv->udev, 0), USBTV_CONTROL_REG,
			USB_सूची_IN | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, USBTV_BASE + 0x0244, (व्योम *)data, 3,
			USB_CTRL_GET_TIMEOUT);
		अगर (ret < 0)
			जाओ error;
	पूर्ण

	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		index = USBTV_BASE + 0x0244;
		size = 3;
		data[0] &= 0xf0;
		data[0] |= (ctrl->val >> 8) & 0xf;
		data[2] = ctrl->val & 0xff;
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		index = USBTV_BASE + 0x0244;
		size = 3;
		data[0] &= 0x0f;
		data[0] |= (ctrl->val >> 4) & 0xf0;
		data[1] = ctrl->val & 0xff;
		अवरोध;
	हाल V4L2_CID_SATURATION:
		index = USBTV_BASE + 0x0242;
		data[0] = ctrl->val >> 8;
		data[1] = ctrl->val & 0xff;
		size = 2;
		अवरोध;
	हाल V4L2_CID_HUE:
		index = USBTV_BASE + 0x0240;
		size = 2;
		अगर (ctrl->val > 0) अणु
			data[0] = 0x92 + (ctrl->val >> 8);
			data[1] = ctrl->val & 0xff;
		पूर्ण अन्यथा अणु
			data[0] = 0x82 + (-ctrl->val >> 8);
			data[1] = -ctrl->val & 0xff;
		पूर्ण
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		index = USBTV_BASE + 0x0239;
		data[0] = 0;
		data[1] = ctrl->val;
		size = 2;
		अवरोध;
	शेष:
		kमुक्त(data);
		वापस -EINVAL;
	पूर्ण

	ret = usb_control_msg(usbtv->udev, usb_sndctrlpipe(usbtv->udev, 0),
			USBTV_CONTROL_REG,
			USB_सूची_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
			0, index, (व्योम *)data, size, USB_CTRL_SET_TIMEOUT);

error:
	अगर (ret < 0)
		dev_warn(usbtv->dev, "Failed to submit a control request.\n");

	kमुक्त(data);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा v4l2_ctrl_ops usbtv_ctrl_ops = अणु
	.s_ctrl = usbtv_s_ctrl,
पूर्ण;

अटल व्योम usbtv_release(काष्ठा v4l2_device *v4l2_dev)
अणु
	काष्ठा usbtv *usbtv = container_of(v4l2_dev, काष्ठा usbtv, v4l2_dev);

	v4l2_device_unरेजिस्टर(&usbtv->v4l2_dev);
	v4l2_ctrl_handler_मुक्त(&usbtv->ctrl);
	kमुक्त(usbtv);
पूर्ण

पूर्णांक usbtv_video_init(काष्ठा usbtv *usbtv)
अणु
	पूर्णांक ret;

	(व्योम)usbtv_configure_क्रम_norm(usbtv, V4L2_STD_525_60);

	spin_lock_init(&usbtv->buflock);
	mutex_init(&usbtv->v4l2_lock);
	mutex_init(&usbtv->vb2q_lock);
	INIT_LIST_HEAD(&usbtv->bufs);

	/* videobuf2 काष्ठाure */
	usbtv->vb2q.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	usbtv->vb2q.io_modes = VB2_MMAP | VB2_USERPTR | VB2_READ;
	usbtv->vb2q.drv_priv = usbtv;
	usbtv->vb2q.buf_काष्ठा_size = माप(काष्ठा usbtv_buf);
	usbtv->vb2q.ops = &usbtv_vb2_ops;
	usbtv->vb2q.mem_ops = &vb2_vदो_स्मृति_memops;
	usbtv->vb2q.बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	usbtv->vb2q.lock = &usbtv->vb2q_lock;
	ret = vb2_queue_init(&usbtv->vb2q);
	अगर (ret < 0) अणु
		dev_warn(usbtv->dev, "Could not initialize videobuf2 queue\n");
		वापस ret;
	पूर्ण

	/* controls */
	v4l2_ctrl_handler_init(&usbtv->ctrl, 4);
	v4l2_ctrl_new_std(&usbtv->ctrl, &usbtv_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 0x3ff, 1, 0x1d0);
	v4l2_ctrl_new_std(&usbtv->ctrl, &usbtv_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 0x3ff, 1, 0x1c0);
	v4l2_ctrl_new_std(&usbtv->ctrl, &usbtv_ctrl_ops,
			V4L2_CID_SATURATION, 0, 0x3ff, 1, 0x200);
	v4l2_ctrl_new_std(&usbtv->ctrl, &usbtv_ctrl_ops,
			V4L2_CID_HUE, -0xdff, 0xdff, 1, 0x000);
	v4l2_ctrl_new_std(&usbtv->ctrl, &usbtv_ctrl_ops,
			V4L2_CID_SHARPNESS, 0x0, 0xff, 1, 0x60);
	ret = usbtv->ctrl.error;
	अगर (ret < 0) अणु
		dev_warn(usbtv->dev, "Could not initialize controls\n");
		जाओ ctrl_fail;
	पूर्ण

	/* v4l2 काष्ठाure */
	usbtv->v4l2_dev.ctrl_handler = &usbtv->ctrl;
	usbtv->v4l2_dev.release = usbtv_release;
	ret = v4l2_device_रेजिस्टर(usbtv->dev, &usbtv->v4l2_dev);
	अगर (ret < 0) अणु
		dev_warn(usbtv->dev, "Could not register v4l2 device\n");
		जाओ v4l2_fail;
	पूर्ण

	/* Video काष्ठाure */
	strscpy(usbtv->vdev.name, "usbtv", माप(usbtv->vdev.name));
	usbtv->vdev.v4l2_dev = &usbtv->v4l2_dev;
	usbtv->vdev.release = video_device_release_empty;
	usbtv->vdev.fops = &usbtv_fops;
	usbtv->vdev.ioctl_ops = &usbtv_ioctl_ops;
	usbtv->vdev.tvnorms = USBTV_TV_STD;
	usbtv->vdev.queue = &usbtv->vb2q;
	usbtv->vdev.lock = &usbtv->v4l2_lock;
	usbtv->vdev.device_caps = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_READWRITE |
				  V4L2_CAP_STREAMING;
	video_set_drvdata(&usbtv->vdev, usbtv);
	ret = video_रेजिस्टर_device(&usbtv->vdev, VFL_TYPE_VIDEO, -1);
	अगर (ret < 0) अणु
		dev_warn(usbtv->dev, "Could not register video device\n");
		जाओ vdev_fail;
	पूर्ण

	वापस 0;

vdev_fail:
	v4l2_device_unरेजिस्टर(&usbtv->v4l2_dev);
v4l2_fail:
ctrl_fail:
	v4l2_ctrl_handler_मुक्त(&usbtv->ctrl);

	वापस ret;
पूर्ण

व्योम usbtv_video_मुक्त(काष्ठा usbtv *usbtv)
अणु
	mutex_lock(&usbtv->vb2q_lock);
	mutex_lock(&usbtv->v4l2_lock);

	usbtv_stop(usbtv);
	vb2_video_unरेजिस्टर_device(&usbtv->vdev);
	v4l2_device_disconnect(&usbtv->v4l2_dev);

	mutex_unlock(&usbtv->v4l2_lock);
	mutex_unlock(&usbtv->vb2q_lock);

	v4l2_device_put(&usbtv->v4l2_dev);
पूर्ण
