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

#समावेश "link_enc_cfg.h"
#समावेश "resource.h"
#समावेश "dc_link_dp.h"

/* Check whether stream is supported by DIG link encoders. */
अटल bool is_dig_link_enc_stream(काष्ठा dc_stream_state *stream)
अणु
	bool is_dig_stream = false;
	काष्ठा link_encoder *link_enc = शून्य;
	पूर्णांक i;

	/* Loop over created link encoder objects. */
	क्रम (i = 0; i < stream->ctx->dc->res_pool->res_cap->num_dig_link_enc; i++) अणु
		link_enc = stream->ctx->dc->res_pool->link_encoders[i];

		अगर (link_enc &&
				((uपूर्णांक32_t)stream->संकेत & link_enc->output_संकेतs)) अणु
			अगर (dc_is_dp_संकेत(stream->संकेत)) अणु
				/* DIGs करो not support DP2.0 streams with 128b/132b encoding. */
				काष्ठा dc_link_settings link_settings = अणु0पूर्ण;

				decide_link_settings(stream, &link_settings);
				अगर ((link_settings.link_rate >= LINK_RATE_LOW) &&
						link_settings.link_rate <= LINK_RATE_HIGH3) अणु
					is_dig_stream = true;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				is_dig_stream = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस is_dig_stream;
पूर्ण

/* Update DIG link encoder resource tracking variables in dc_state. */
अटल व्योम update_link_enc_assignment(
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *stream,
		क्रमागत engine_id eng_id,
		bool add_enc)
अणु
	पूर्णांक eng_idx;
	पूर्णांक stream_idx;
	पूर्णांक i;

	अगर (eng_id != ENGINE_ID_UNKNOWN) अणु
		eng_idx = eng_id - ENGINE_ID_DIGA;
		stream_idx = -1;

		/* Index of stream in dc_state used to update correct entry in
		 * link_enc_assignments table.
		 */
		क्रम (i = 0; i < state->stream_count; i++) अणु
			अगर (stream == state->streams[i]) अणु
				stream_idx = i;
				अवरोध;
			पूर्ण
		पूर्ण

		/* Update link encoder assignments table, link encoder availability
		 * pool and link encoder asचिन्हित to stream in state.
		 * Add/हटाओ encoder resource to/from stream.
		 */
		अगर (stream_idx != -1) अणु
			अगर (add_enc) अणु
				state->res_ctx.link_enc_assignments[stream_idx] = (काष्ठा link_enc_assignment)अणु
					.valid = true,
					.ep_id = (काष्ठा display_endpoपूर्णांक_id) अणु
						.link_id = stream->link->link_id,
						.ep_type = stream->link->ep_typeपूर्ण,
					.eng_id = eng_idपूर्ण;
				state->res_ctx.link_enc_avail[eng_idx] = ENGINE_ID_UNKNOWN;
				stream->link_enc = stream->ctx->dc->res_pool->link_encoders[eng_idx];
			पूर्ण अन्यथा अणु
				state->res_ctx.link_enc_assignments[stream_idx].valid = false;
				state->res_ctx.link_enc_avail[eng_idx] = eng_id;
				stream->link_enc = शून्य;
			पूर्ण
		पूर्ण अन्यथा अणु
			dm_output_to_console("%s: Stream not found in dc_state.\n", __func__);
		पूर्ण
	पूर्ण
पूर्ण

/* Return first available DIG link encoder. */
अटल क्रमागत engine_id find_first_avail_link_enc(
		काष्ठा dc_context *ctx,
		काष्ठा dc_state *state)
अणु
	क्रमागत engine_id eng_id = ENGINE_ID_UNKNOWN;
	पूर्णांक i;

	क्रम (i = 0; i < ctx->dc->res_pool->res_cap->num_dig_link_enc; i++) अणु
		eng_id = state->res_ctx.link_enc_avail[i];
		अगर (eng_id != ENGINE_ID_UNKNOWN)
			अवरोध;
	पूर्ण

	वापस eng_id;
पूर्ण

/* Return stream using DIG link encoder resource. शून्य अगर unused. */
अटल काष्ठा dc_stream_state *get_stream_using_link_enc(
		काष्ठा dc_state *state,
		क्रमागत engine_id eng_id)
अणु
	काष्ठा dc_stream_state *stream = शून्य;
	पूर्णांक stream_idx = -1;
	पूर्णांक i;

	क्रम (i = 0; i < state->stream_count; i++) अणु
		काष्ठा link_enc_assignment assignment = state->res_ctx.link_enc_assignments[i];

		अगर (assignment.valid && (assignment.eng_id == eng_id)) अणु
			stream_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stream_idx != -1)
		stream = state->streams[stream_idx];
	अन्यथा
		dm_output_to_console("%s: No stream using DIG(%d).\n", __func__, eng_id);

	वापस stream;
पूर्ण

व्योम link_enc_cfg_init(
		काष्ठा dc *dc,
		काष्ठा dc_state *state)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < dc->res_pool->res_cap->num_dig_link_enc; i++) अणु
		अगर (dc->res_pool->link_encoders[i])
			state->res_ctx.link_enc_avail[i] = (क्रमागत engine_id) i;
		अन्यथा
			state->res_ctx.link_enc_avail[i] = ENGINE_ID_UNKNOWN;
	पूर्ण
पूर्ण

व्योम link_enc_cfg_link_encs_assign(
		काष्ठा dc *dc,
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *streams[],
		uपूर्णांक8_t stream_count)
अणु
	क्रमागत engine_id eng_id = ENGINE_ID_UNKNOWN;
	पूर्णांक i;

	/* Release DIG link encoder resources beक्रमe running assignment algorithm. */
	क्रम (i = 0; i < stream_count; i++)
		dc->res_pool->funcs->link_enc_unassign(state, streams[i]);

	/* (a) Assign DIG link encoders to physical (unmappable) endpoपूर्णांकs first. */
	क्रम (i = 0; i < stream_count; i++) अणु
		काष्ठा dc_stream_state *stream = streams[i];

		/* Skip stream अगर not supported by DIG link encoder. */
		अगर (!is_dig_link_enc_stream(stream))
			जारी;

		/* Physical endpoपूर्णांकs have a fixed mapping to DIG link encoders. */
		अगर (!stream->link->is_dig_mapping_flexible) अणु
			eng_id = stream->link->eng_id;
			update_link_enc_assignment(state, stream, eng_id, true);
		पूर्ण
	पूर्ण

	/* (b) Then assign encoders to mappable endpoपूर्णांकs. */
	eng_id = ENGINE_ID_UNKNOWN;

	क्रम (i = 0; i < stream_count; i++) अणु
		काष्ठा dc_stream_state *stream = streams[i];

		/* Skip stream अगर not supported by DIG link encoder. */
		अगर (!is_dig_link_enc_stream(stream))
			जारी;

		/* Mappable endpoपूर्णांकs have a flexible mapping to DIG link encoders. */
		अगर (stream->link->is_dig_mapping_flexible) अणु
			eng_id = find_first_avail_link_enc(stream->ctx, state);
			update_link_enc_assignment(state, stream, eng_id, true);
		पूर्ण
	पूर्ण
पूर्ण

व्योम link_enc_cfg_link_enc_unassign(
		काष्ठा dc_state *state,
		काष्ठा dc_stream_state *stream)
अणु
	क्रमागत engine_id eng_id = ENGINE_ID_UNKNOWN;

	/* Only DIG link encoders. */
	अगर (!is_dig_link_enc_stream(stream))
		वापस;

	अगर (stream->link_enc)
		eng_id = stream->link_enc->preferred_engine;

	update_link_enc_assignment(state, stream, eng_id, false);
पूर्ण

bool link_enc_cfg_is_transmitter_mappable(
		काष्ठा dc_state *state,
		काष्ठा link_encoder *link_enc)
अणु
	bool is_mappable = false;
	क्रमागत engine_id eng_id = link_enc->preferred_engine;
	काष्ठा dc_stream_state *stream = get_stream_using_link_enc(state, eng_id);

	अगर (stream)
		is_mappable = stream->link->is_dig_mapping_flexible;

	वापस is_mappable;
पूर्ण

काष्ठा dc_link *link_enc_cfg_get_link_using_link_enc(
		काष्ठा dc_state *state,
		क्रमागत engine_id eng_id)
अणु
	काष्ठा dc_link *link = शून्य;
	पूर्णांक stream_idx = -1;
	पूर्णांक i;

	क्रम (i = 0; i < state->stream_count; i++) अणु
		काष्ठा link_enc_assignment assignment = state->res_ctx.link_enc_assignments[i];

		अगर (assignment.valid && (assignment.eng_id == eng_id)) अणु
			stream_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stream_idx != -1)
		link = state->streams[stream_idx]->link;
	अन्यथा
		dm_output_to_console("%s: No link using DIG(%d).\n", __func__, eng_id);

	वापस link;
पूर्ण

काष्ठा link_encoder *link_enc_cfg_get_link_enc_used_by_link(
		काष्ठा dc_state *state,
		काष्ठा dc_link *link)
अणु
	काष्ठा link_encoder *link_enc = शून्य;
	काष्ठा display_endpoपूर्णांक_id ep_id;
	पूर्णांक stream_idx = -1;
	पूर्णांक i;

	ep_id = (काष्ठा display_endpoपूर्णांक_id) अणु
		.link_id = link->link_id,
		.ep_type = link->ep_typeपूर्ण;

	क्रम (i = 0; i < state->stream_count; i++) अणु
		काष्ठा link_enc_assignment assignment = state->res_ctx.link_enc_assignments[i];

		अगर (assignment.valid &&
				assignment.ep_id.link_id.id == ep_id.link_id.id &&
				assignment.ep_id.link_id.क्रमागत_id == ep_id.link_id.क्रमागत_id &&
				assignment.ep_id.link_id.type == ep_id.link_id.type &&
				assignment.ep_id.ep_type == ep_id.ep_type) अणु
			stream_idx = i;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (stream_idx != -1)
		link_enc = state->streams[stream_idx]->link_enc;
	अन्यथा
		dm_output_to_console("%s: No link encoder used by link(%d).\n", __func__, link->link_index);

	वापस link_enc;
पूर्ण
