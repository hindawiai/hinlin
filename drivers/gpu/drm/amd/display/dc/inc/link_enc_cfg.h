<शैली गुरु>
/*
 * Copyright 2021 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित DC_INC_LINK_ENC_CFG_H_
#घोषणा DC_INC_LINK_ENC_CFG_H_

/* This module implements functionality क्रम dynamically assigning DIG link
 * encoder resources to display endpoपूर्णांकs (links).
 */

#समावेश "core_types.h"

/*
 * Initialise link encoder resource tracking.
 */
व्योम link_enc_cfg_init(
		काष्ठा dc *dc,
		काष्ठा dc_state *state);

/*
 * Algorithm क्रम assigning available DIG link encoders to streams.
 *
 * Update link_enc_assignments table and link_enc_avail list accordingly in
 * काष्ठा resource_context.
 *
 * Loop over all streams twice:
 * a) First assign encoders to unmappable endpoपूर्णांकs.
 * b) Then assign encoders to mappable endpoपूर्णांकs.
 */
व्योम link_enc_cfg_link_encs_assign(
		काष्ठा dc *dc,
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *streams[],
		uपूर्णांक8_t stream_count);

/*
 * Unassign a link encoder from a stream.
 *
 * Update link_enc_assignments table and link_enc_avail list accordingly in
 * काष्ठा resource_context.
 */
व्योम link_enc_cfg_link_enc_unassign(
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *stream);

/*
 * Check whether the transmitter driven by a link encoder is a mappable
 * endpoपूर्णांक.
 */
bool link_enc_cfg_is_transmitter_mappable(
		काष्ठा dc_state *state,
		काष्ठा link_encoder *link_enc);

/* Return link using DIG link encoder resource. शून्य अगर unused. */
काष्ठा dc_link *link_enc_cfg_get_link_using_link_enc(
		काष्ठा dc_state *state,
		क्रमागत engine_id eng_id);

/* Return DIG link encoder used by link. शून्य अगर unused. */
काष्ठा link_encoder *link_enc_cfg_get_link_enc_used_by_link(
		काष्ठा dc_state *state,
		काष्ठा dc_link *link);

#पूर्ण_अगर /* DC_INC_LINK_ENC_CFG_H_ */
