<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#अगर_अघोषित __MESON_VDEC_HELPERS_H_
#घोषणा __MESON_VDEC_HELPERS_H_

#समावेश "vdec.h"

/**
 * amvdec_set_canvases() - Map VB2 buffers to canvases
 *
 * @sess: current session
 * @reg_base: Registry bases of where to ग_लिखो the canvas indexes
 * @reg_num: number of contiguous रेजिस्टरs after each reg_base (including it)
 */
पूर्णांक amvdec_set_canvases(काष्ठा amvdec_session *sess,
			u32 reg_base[], u32 reg_num[]);

/* Helpers to पढ़ो/ग_लिखो to the various IPs (DOS, PARSER) */
u32 amvdec_पढ़ो_करोs(काष्ठा amvdec_core *core, u32 reg);
व्योम amvdec_ग_लिखो_करोs(काष्ठा amvdec_core *core, u32 reg, u32 val);
व्योम amvdec_ग_लिखो_करोs_bits(काष्ठा amvdec_core *core, u32 reg, u32 val);
व्योम amvdec_clear_करोs_bits(काष्ठा amvdec_core *core, u32 reg, u32 val);
u32 amvdec_पढ़ो_parser(काष्ठा amvdec_core *core, u32 reg);
व्योम amvdec_ग_लिखो_parser(काष्ठा amvdec_core *core, u32 reg, u32 val);

u32 amvdec_am21c_body_size(u32 width, u32 height);
u32 amvdec_am21c_head_size(u32 width, u32 height);
u32 amvdec_am21c_size(u32 width, u32 height);

/**
 * amvdec_dst_buf_करोne_idx() - Signal that a buffer is करोne decoding
 *
 * @sess: current session
 * @buf_idx: hardware buffer index
 * @offset: VIFIFO bitstream offset corresponding to the buffer
 * @field: V4L2 पूर्णांकerlaced field
 */
व्योम amvdec_dst_buf_करोne_idx(काष्ठा amvdec_session *sess, u32 buf_idx,
			     u32 offset, u32 field);
व्योम amvdec_dst_buf_करोne(काष्ठा amvdec_session *sess,
			 काष्ठा vb2_v4l2_buffer *vbuf, u32 field);
व्योम amvdec_dst_buf_करोne_offset(काष्ठा amvdec_session *sess,
				काष्ठा vb2_v4l2_buffer *vbuf,
				u32 offset, u32 field, bool allow_drop);

/**
 * amvdec_add_ts() - Add a बारtamp to the list
 *
 * @sess: current session
 * @ts: बारtamp to add
 * @offset: offset in the VIFIFO where the associated packet was written
 * @flags the vb2_v4l2_buffer flags
 */
व्योम amvdec_add_ts(काष्ठा amvdec_session *sess, u64 ts,
		   काष्ठा v4l2_समयcode tc, u32 offset, u32 flags);
व्योम amvdec_हटाओ_ts(काष्ठा amvdec_session *sess, u64 ts);

/**
 * amvdec_set_par_from_dar() - Set Pixel Aspect Ratio from Display Aspect Ratio
 *
 * @sess: current session
 * @dar_num: numerator of the DAR
 * @dar_den: denominator of the DAR
 */
व्योम amvdec_set_par_from_dar(काष्ठा amvdec_session *sess,
			     u32 dar_num, u32 dar_den);

/**
 * amvdec_src_change() - Notअगरy new resolution/DPB size to the core
 *
 * @sess: current session
 * @width: picture width detected by the hardware
 * @height: picture height detected by the hardware
 * @dpb_size: Decoded Picture Buffer size (= amount of buffers क्रम decoding)
 */
व्योम amvdec_src_change(काष्ठा amvdec_session *sess, u32 width,
		       u32 height, u32 dpb_size);

/**
 * amvdec_पात() - Abort the current decoding session
 *
 * @sess: current session
 */
व्योम amvdec_पात(काष्ठा amvdec_session *sess);
#पूर्ण_अगर
