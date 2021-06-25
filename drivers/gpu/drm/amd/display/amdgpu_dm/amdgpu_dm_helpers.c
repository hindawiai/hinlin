<शैली गुरु>
/*
 * Copyright 2015 Advanced Micro Devices, Inc.
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

#समावेश <linux/माला.स>
#समावेश <linux/acpi.h>
#समावेश <linux/i2c.h>

#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/amdgpu_drm.h>
#समावेश <drm/drm_edid.h>

#समावेश "dm_services.h"
#समावेश "amdgpu.h"
#समावेश "dc.h"
#समावेश "amdgpu_dm.h"
#समावेश "amdgpu_dm_irq.h"
#समावेश "amdgpu_dm_mst_types.h"

#समावेश "dm_helpers.h"

/* dm_helpers_parse_edid_caps
 *
 * Parse edid caps
 *
 * @edid:	[in] poपूर्णांकer to edid
 *  edid_caps:	[in] poपूर्णांकer to edid caps
 * @वापस
 *	व्योम
 * */
क्रमागत dc_edid_status dm_helpers_parse_edid_caps(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_edid *edid,
		काष्ठा dc_edid_caps *edid_caps)
अणु
	काष्ठा edid *edid_buf = (काष्ठा edid *) edid->raw_edid;
	काष्ठा cea_sad *sads;
	पूर्णांक sad_count = -1;
	पूर्णांक sadb_count = -1;
	पूर्णांक i = 0;
	पूर्णांक j = 0;
	uपूर्णांक8_t *sadb = शून्य;

	क्रमागत dc_edid_status result = EDID_OK;

	अगर (!edid_caps || !edid)
		वापस EDID_BAD_INPUT;

	अगर (!drm_edid_is_valid(edid_buf))
		result = EDID_BAD_CHECKSUM;

	edid_caps->manufacturer_id = (uपूर्णांक16_t) edid_buf->mfg_id[0] |
					((uपूर्णांक16_t) edid_buf->mfg_id[1])<<8;
	edid_caps->product_id = (uपूर्णांक16_t) edid_buf->prod_code[0] |
					((uपूर्णांक16_t) edid_buf->prod_code[1])<<8;
	edid_caps->serial_number = edid_buf->serial;
	edid_caps->manufacture_week = edid_buf->mfg_week;
	edid_caps->manufacture_year = edid_buf->mfg_year;

	/* One of the four detailed_timings stores the monitor name. It's
	 * stored in an array of length 13. */
	क्रम (i = 0; i < 4; i++) अणु
		अगर (edid_buf->detailed_timings[i].data.other_data.type == 0xfc) अणु
			जबतक (j < 13 && edid_buf->detailed_timings[i].data.other_data.data.str.str[j]) अणु
				अगर (edid_buf->detailed_timings[i].data.other_data.data.str.str[j] == '\n')
					अवरोध;

				edid_caps->display_name[j] =
					edid_buf->detailed_timings[i].data.other_data.data.str.str[j];
				j++;
			पूर्ण
		पूर्ण
	पूर्ण

	edid_caps->edid_hdmi = drm_detect_hdmi_monitor(
			(काष्ठा edid *) edid->raw_edid);

	sad_count = drm_edid_to_sad((काष्ठा edid *) edid->raw_edid, &sads);
	अगर (sad_count <= 0)
		वापस result;

	edid_caps->audio_mode_count = sad_count < DC_MAX_AUDIO_DESC_COUNT ? sad_count : DC_MAX_AUDIO_DESC_COUNT;
	क्रम (i = 0; i < edid_caps->audio_mode_count; ++i) अणु
		काष्ठा cea_sad *sad = &sads[i];

		edid_caps->audio_modes[i].क्रमmat_code = sad->क्रमmat;
		edid_caps->audio_modes[i].channel_count = sad->channels + 1;
		edid_caps->audio_modes[i].sample_rate = sad->freq;
		edid_caps->audio_modes[i].sample_size = sad->byte2;
	पूर्ण

	sadb_count = drm_edid_to_speaker_allocation((काष्ठा edid *) edid->raw_edid, &sadb);

	अगर (sadb_count < 0) अणु
		DRM_ERROR("Couldn't read Speaker Allocation Data Block: %d\n", sadb_count);
		sadb_count = 0;
	पूर्ण

	अगर (sadb_count)
		edid_caps->speaker_flags = sadb[0];
	अन्यथा
		edid_caps->speaker_flags = DEFAULT_SPEAKER_LOCATION;

	kमुक्त(sads);
	kमुक्त(sadb);

	वापस result;
पूर्ण

अटल व्योम get_payload_table(
		काष्ठा amdgpu_dm_connector *aconnector,
		काष्ठा dp_mst_stream_allocation_table *proposed_table)
अणु
	पूर्णांक i;
	काष्ठा drm_dp_mst_topology_mgr *mst_mgr =
			&aconnector->mst_port->mst_mgr;

	mutex_lock(&mst_mgr->payload_lock);

	proposed_table->stream_count = 0;

	/* number of active streams */
	क्रम (i = 0; i < mst_mgr->max_payloads; i++) अणु
		अगर (mst_mgr->payloads[i].num_slots == 0)
			अवरोध; /* end of vcp_id table */

		ASSERT(mst_mgr->payloads[i].payload_state !=
				DP_PAYLOAD_DELETE_LOCAL);

		अगर (mst_mgr->payloads[i].payload_state == DP_PAYLOAD_LOCAL ||
			mst_mgr->payloads[i].payload_state ==
					DP_PAYLOAD_REMOTE) अणु

			काष्ठा dp_mst_stream_allocation *sa =
					&proposed_table->stream_allocations[
						proposed_table->stream_count];

			sa->slot_count = mst_mgr->payloads[i].num_slots;
			sa->vcp_id = mst_mgr->proposed_vcpis[i]->vcpi;
			proposed_table->stream_count++;
		पूर्ण
	पूर्ण

	mutex_unlock(&mst_mgr->payload_lock);
पूर्ण

व्योम dm_helpers_dp_update_branch_info(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dc_link *link)
अणुपूर्ण

/*
 * Writes payload allocation table in immediate करोwnstream device.
 */
bool dm_helpers_dp_mst_ग_लिखो_payload_allocation_table(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream,
		काष्ठा dp_mst_stream_allocation_table *proposed_table,
		bool enable)
अणु
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा dm_connector_state *dm_conn_state;
	काष्ठा drm_dp_mst_topology_mgr *mst_mgr;
	काष्ठा drm_dp_mst_port *mst_port;
	bool ret;

	aconnector = (काष्ठा amdgpu_dm_connector *)stream->dm_stream_context;
	/* Accessing the connector state is required क्रम vcpi_slots allocation
	 * and directly relies on behaviour in commit check
	 * that blocks beक्रमe commit guaranteeing that the state
	 * is not gonna be swapped जबतक still in use in commit tail */

	अगर (!aconnector || !aconnector->mst_port)
		वापस false;

	dm_conn_state = to_dm_connector_state(aconnector->base.state);

	mst_mgr = &aconnector->mst_port->mst_mgr;

	अगर (!mst_mgr->mst_state)
		वापस false;

	mst_port = aconnector->port;

	अगर (enable) अणु

		ret = drm_dp_mst_allocate_vcpi(mst_mgr, mst_port,
					       dm_conn_state->pbn,
					       dm_conn_state->vcpi_slots);
		अगर (!ret)
			वापस false;

	पूर्ण अन्यथा अणु
		drm_dp_mst_reset_vcpi_slots(mst_mgr, mst_port);
	पूर्ण

	/* It's OK क्रम this to fail */
	drm_dp_update_payload_part1(mst_mgr);

	/* mst_mgr->->payloads are VC payload notअगरy MST branch using DPCD or
	 * AUX message. The sequence is slot 1-63 allocated sequence क्रम each
	 * stream. AMD ASIC stream slot allocation should follow the same
	 * sequence. copy DRM MST allocation to dc */

	get_payload_table(aconnector, proposed_table);

	वापस true;
पूर्ण

/*
 * poll pending करोwn reply
 */
व्योम dm_helpers_dp_mst_poll_pending_करोwn_reply(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dc_link *link)
अणुपूर्ण

/*
 * Clear payload allocation table beक्रमe enable MST DP link.
 */
व्योम dm_helpers_dp_mst_clear_payload_allocation_table(
	काष्ठा dc_context *ctx,
	स्थिर काष्ठा dc_link *link)
अणुपूर्ण

/*
 * Polls क्रम ACT (allocation change trigger) handled and sends
 * ALLOCATE_PAYLOAD message.
 */
क्रमागत act_वापस_status dm_helpers_dp_mst_poll_क्रम_allocation_change_trigger(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream)
अणु
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_dp_mst_topology_mgr *mst_mgr;
	पूर्णांक ret;

	aconnector = (काष्ठा amdgpu_dm_connector *)stream->dm_stream_context;

	अगर (!aconnector || !aconnector->mst_port)
		वापस ACT_FAILED;

	mst_mgr = &aconnector->mst_port->mst_mgr;

	अगर (!mst_mgr->mst_state)
		वापस ACT_FAILED;

	ret = drm_dp_check_act_status(mst_mgr);

	अगर (ret)
		वापस ACT_FAILED;

	वापस ACT_SUCCESS;
पूर्ण

bool dm_helpers_dp_mst_send_payload_allocation(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream,
		bool enable)
अणु
	काष्ठा amdgpu_dm_connector *aconnector;
	काष्ठा drm_dp_mst_topology_mgr *mst_mgr;
	काष्ठा drm_dp_mst_port *mst_port;

	aconnector = (काष्ठा amdgpu_dm_connector *)stream->dm_stream_context;

	अगर (!aconnector || !aconnector->mst_port)
		वापस false;

	mst_port = aconnector->port;

	mst_mgr = &aconnector->mst_port->mst_mgr;

	अगर (!mst_mgr->mst_state)
		वापस false;

	/* It's OK क्रम this to fail */
	drm_dp_update_payload_part2(mst_mgr);

	अगर (!enable)
		drm_dp_mst_deallocate_vcpi(mst_mgr, mst_port);

	वापस true;
पूर्ण

व्योम dm_dtn_log_begin(काष्ठा dc_context *ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx)
अणु
	अटल स्थिर अक्षर msg[] = "[dtn begin]\n";

	अगर (!log_ctx) अणु
		pr_info("%s", msg);
		वापस;
	पूर्ण

	dm_dtn_log_append_v(ctx, log_ctx, "%s", msg);
पूर्ण

__म_लिखो(3, 4)
व्योम dm_dtn_log_append_v(काष्ठा dc_context *ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx,
	स्थिर अक्षर *msg, ...)
अणु
	बहु_सूची args;
	माप_प्रकार total;
	पूर्णांक n;

	अगर (!log_ctx) अणु
		/* No context, redirect to dmesg. */
		काष्ठा va_क्रमmat vaf;

		vaf.fmt = msg;
		vaf.va = &args;

		बहु_शुरू(args, msg);
		pr_info("%pV", &vaf);
		बहु_पूर्ण(args);

		वापस;
	पूर्ण

	/* Measure the output. */
	बहु_शुरू(args, msg);
	n = vsnम_लिखो(शून्य, 0, msg, args);
	बहु_पूर्ण(args);

	अगर (n <= 0)
		वापस;

	/* Reallocate the string buffer as needed. */
	total = log_ctx->pos + n + 1;

	अगर (total > log_ctx->size) अणु
		अक्षर *buf = (अक्षर *)kvसुस्मृति(total, माप(अक्षर), GFP_KERNEL);

		अगर (buf) अणु
			स_नकल(buf, log_ctx->buf, log_ctx->pos);
			kमुक्त(log_ctx->buf);

			log_ctx->buf = buf;
			log_ctx->size = total;
		पूर्ण
	पूर्ण

	अगर (!log_ctx->buf)
		वापस;

	/* Write the क्रमmatted string to the log buffer. */
	बहु_शुरू(args, msg);
	n = vscnम_लिखो(
		log_ctx->buf + log_ctx->pos,
		log_ctx->size - log_ctx->pos,
		msg,
		args);
	बहु_पूर्ण(args);

	अगर (n > 0)
		log_ctx->pos += n;
पूर्ण

व्योम dm_dtn_log_end(काष्ठा dc_context *ctx,
	काष्ठा dc_log_buffer_ctx *log_ctx)
अणु
	अटल स्थिर अक्षर msg[] = "[dtn end]\n";

	अगर (!log_ctx) अणु
		pr_info("%s", msg);
		वापस;
	पूर्ण

	dm_dtn_log_append_v(ctx, log_ctx, "%s", msg);
पूर्ण

bool dm_helpers_dp_mst_start_top_mgr(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		bool boot)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;

	अगर (!aconnector) अणु
		DRM_ERROR("Failed to find connector for link!");
		वापस false;
	पूर्ण

	अगर (boot) अणु
		DRM_INFO("DM_MST: Differing MST start on aconnector: %p [id: %d]\n",
					aconnector, aconnector->base.base.id);
		वापस true;
	पूर्ण

	DRM_INFO("DM_MST: starting TM on aconnector: %p [id: %d]\n",
			aconnector, aconnector->base.base.id);

	वापस (drm_dp_mst_topology_mgr_set_mst(&aconnector->mst_mgr, true) == 0);
पूर्ण

व्योम dm_helpers_dp_mst_stop_top_mgr(
		काष्ठा dc_context *ctx,
		काष्ठा dc_link *link)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;
	uपूर्णांक8_t i;

	अगर (!aconnector) अणु
		DRM_ERROR("Failed to find connector for link!");
		वापस;
	पूर्ण

	DRM_INFO("DM_MST: stopping TM on aconnector: %p [id: %d]\n",
			aconnector, aconnector->base.base.id);

	अगर (aconnector->mst_mgr.mst_state == true) अणु
		drm_dp_mst_topology_mgr_set_mst(&aconnector->mst_mgr, false);

		क्रम (i = 0; i < MAX_SINKS_PER_LINK; i++) अणु
			अगर (link->remote_sinks[i] == शून्य)
				जारी;

			अगर (link->remote_sinks[i]->sink_संकेत ==
			    SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
				dc_link_हटाओ_remote_sink(link, link->remote_sinks[i]);

				अगर (aconnector->dc_sink) अणु
					dc_sink_release(aconnector->dc_sink);
					aconnector->dc_sink = शून्य;
					aconnector->dc_link->cur_link_settings.lane_count = 0;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

bool dm_helpers_dp_पढ़ो_dpcd(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		uपूर्णांक32_t address,
		uपूर्णांक8_t *data,
		uपूर्णांक32_t size)
अणु

	काष्ठा amdgpu_dm_connector *aconnector = link->priv;

	अगर (!aconnector) अणु
		DC_LOG_DC("Failed to find connector for link!\n");
		वापस false;
	पूर्ण

	वापस drm_dp_dpcd_पढ़ो(&aconnector->dm_dp_aux.aux, address,
			data, size) > 0;
पूर्ण

bool dm_helpers_dp_ग_लिखो_dpcd(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		uपूर्णांक32_t address,
		स्थिर uपूर्णांक8_t *data,
		uपूर्णांक32_t size)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;

	अगर (!aconnector) अणु
		DRM_ERROR("Failed to find connector for link!");
		वापस false;
	पूर्ण

	वापस drm_dp_dpcd_ग_लिखो(&aconnector->dm_dp_aux.aux,
			address, (uपूर्णांक8_t *)data, size) > 0;
पूर्ण

bool dm_helpers_submit_i2c(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_link *link,
		काष्ठा i2c_command *cmd)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;
	काष्ठा i2c_msg *msgs;
	पूर्णांक i = 0;
	पूर्णांक num = cmd->number_of_payloads;
	bool result;

	अगर (!aconnector) अणु
		DRM_ERROR("Failed to find connector for link!");
		वापस false;
	पूर्ण

	msgs = kसुस्मृति(num, माप(काष्ठा i2c_msg), GFP_KERNEL);

	अगर (!msgs)
		वापस false;

	क्रम (i = 0; i < num; i++) अणु
		msgs[i].flags = cmd->payloads[i].ग_लिखो ? 0 : I2C_M_RD;
		msgs[i].addr = cmd->payloads[i].address;
		msgs[i].len = cmd->payloads[i].length;
		msgs[i].buf = cmd->payloads[i].data;
	पूर्ण

	result = i2c_transfer(&aconnector->i2c->base, msgs, num) == num;

	kमुक्त(msgs);

	वापस result;
पूर्ण
bool dm_helpers_dp_ग_लिखो_dsc_enable(
		काष्ठा dc_context *ctx,
		स्थिर काष्ठा dc_stream_state *stream,
		bool enable)
अणु
	uपूर्णांक8_t enable_dsc = enable ? 1 : 0;
	काष्ठा amdgpu_dm_connector *aconnector;
	uपूर्णांक8_t ret = 0;

	अगर (!stream)
		वापस false;

	अगर (stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT_MST) अणु
		aconnector = (काष्ठा amdgpu_dm_connector *)stream->dm_stream_context;

		अगर (!aconnector->dsc_aux)
			वापस false;

		ret = drm_dp_dpcd_ग_लिखो(aconnector->dsc_aux, DP_DSC_ENABLE, &enable_dsc, 1);
	पूर्ण

	अगर (stream->संकेत == SIGNAL_TYPE_DISPLAY_PORT)
		वापस dm_helpers_dp_ग_लिखो_dpcd(ctx, stream->link, DP_DSC_ENABLE, &enable_dsc, 1);

	वापस (ret > 0);
पूर्ण

bool dm_helpers_is_dp_sink_present(काष्ठा dc_link *link)
अणु
	bool dp_sink_present;
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;

	अगर (!aconnector) अणु
		BUG_ON("Failed to find connector for link!");
		वापस true;
	पूर्ण

	mutex_lock(&aconnector->dm_dp_aux.aux.hw_mutex);
	dp_sink_present = dc_link_is_dp_sink_present(link);
	mutex_unlock(&aconnector->dm_dp_aux.aux.hw_mutex);
	वापस dp_sink_present;
पूर्ण

क्रमागत dc_edid_status dm_helpers_पढ़ो_local_edid(
		काष्ठा dc_context *ctx,
		काष्ठा dc_link *link,
		काष्ठा dc_sink *sink)
अणु
	काष्ठा amdgpu_dm_connector *aconnector = link->priv;
	काष्ठा drm_connector *connector = &aconnector->base;
	काष्ठा i2c_adapter *ddc;
	पूर्णांक retry = 3;
	क्रमागत dc_edid_status edid_status;
	काष्ठा edid *edid;

	अगर (link->aux_mode)
		ddc = &aconnector->dm_dp_aux.aux.ddc;
	अन्यथा
		ddc = &aconnector->i2c->base;

	/* some करोngles पढ़ो edid incorrectly the first समय,
	 * करो check sum and retry to make sure पढ़ो correct edid.
	 */
	करो अणु

		edid = drm_get_edid(&aconnector->base, ddc);

		/* DP Compliance Test 4.2.2.6 */
		अगर (link->aux_mode && connector->edid_corrupt)
			drm_dp_send_real_edid_checksum(&aconnector->dm_dp_aux.aux, connector->real_edid_checksum);

		अगर (!edid && connector->edid_corrupt) अणु
			connector->edid_corrupt = false;
			वापस EDID_BAD_CHECKSUM;
		पूर्ण

		अगर (!edid)
			वापस EDID_NO_RESPONSE;

		sink->dc_edid.length = EDID_LENGTH * (edid->extensions + 1);
		स_हटाओ(sink->dc_edid.raw_edid, (uपूर्णांक8_t *)edid, sink->dc_edid.length);

		/* We करोn't need the original edid anymore */
		kमुक्त(edid);

		/* connector->display_info will be parsed from EDID and saved
		 * पूर्णांकo drm_connector->display_info from edid by call stack
		 * below:
		 * drm_parse_ycbcr420_deep_color_info
		 * drm_parse_hdmi_क्रमum_vsdb
		 * drm_parse_cea_ext
		 * drm_add_display_info
		 * drm_connector_update_edid_property
		 *
		 * drm_connector->display_info will be used by amdgpu_dm funcs,
		 * like fill_stream_properties_from_drm_display_mode
		 */
		amdgpu_dm_update_connector_after_detect(aconnector);

		edid_status = dm_helpers_parse_edid_caps(
						ctx,
						&sink->dc_edid,
						&sink->edid_caps);

	पूर्ण जबतक (edid_status == EDID_BAD_CHECKSUM && --retry > 0);

	अगर (edid_status != EDID_OK)
		DRM_ERROR("EDID err: %d, on connector: %s",
				edid_status,
				aconnector->base.name);

	/* DP Compliance Test 4.2.2.3 */
	अगर (link->aux_mode)
		drm_dp_send_real_edid_checksum(&aconnector->dm_dp_aux.aux, sink->dc_edid.raw_edid[sink->dc_edid.length-1]);

	वापस edid_status;
पूर्ण

व्योम dm_set_dcn_घड़ीs(काष्ठा dc_context *ctx, काष्ठा dc_घड़ीs *clks)
अणु
	/* TODO: something */
पूर्ण

व्योम *dm_helpers_allocate_gpu_mem(
		काष्ठा dc_context *ctx,
		क्रमागत dc_gpu_mem_alloc_type type,
		माप_प्रकार size,
		दीर्घ दीर्घ *addr)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	काष्ठा dal_allocation *da;
	u32 करोमुख्य = (type == DC_MEM_ALLOC_TYPE_GART) ?
		AMDGPU_GEM_DOMAIN_GTT : AMDGPU_GEM_DOMAIN_VRAM;
	पूर्णांक ret;

	da = kzalloc(माप(काष्ठा dal_allocation), GFP_KERNEL);
	अगर (!da)
		वापस शून्य;

	ret = amdgpu_bo_create_kernel(adev, size, PAGE_SIZE,
				      करोमुख्य, &da->bo,
				      &da->gpu_addr, &da->cpu_ptr);

	*addr = da->gpu_addr;

	अगर (ret) अणु
		kमुक्त(da);
		वापस शून्य;
	पूर्ण

	/* add da to list in dm */
	list_add(&da->list, &adev->dm.da_list);

	वापस da->cpu_ptr;
पूर्ण

व्योम dm_helpers_मुक्त_gpu_mem(
		काष्ठा dc_context *ctx,
		क्रमागत dc_gpu_mem_alloc_type type,
		व्योम *pvMem)
अणु
	काष्ठा amdgpu_device *adev = ctx->driver_context;
	काष्ठा dal_allocation *da;

	/* walk the da list in DM */
	list_क्रम_each_entry(da, &adev->dm.da_list, list) अणु
		अगर (pvMem == da->cpu_ptr) अणु
			amdgpu_bo_मुक्त_kernel(&da->bo, &da->gpu_addr, &da->cpu_ptr);
			list_del(&da->list);
			kमुक्त(da);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

bool dm_helpers_dmub_outbox0_पूर्णांकerrupt_control(काष्ठा dc_context *ctx, bool enable)
अणु
	क्रमागत dc_irq_source irq_source;
	bool ret;

	irq_source = DC_IRQ_SOURCE_DMCUB_OUTBOX0;

	ret = dc_पूर्णांकerrupt_set(ctx->dc, irq_source, enable);

	DRM_DEBUG_DRIVER("Dmub trace irq %sabling: r=%d\n",
			 enable ? "en" : "dis", ret);
	वापस ret;
पूर्ण

व्योम dm_helpers_mst_enable_stream_features(स्थिर काष्ठा dc_stream_state *stream)
अणु
	/* TODO: भव DPCD */
	काष्ठा dc_link *link = stream->link;
	जोड़ करोwn_spपढ़ो_ctrl old_करोwnspपढ़ो;
	जोड़ करोwn_spपढ़ो_ctrl new_करोwnspपढ़ो;

	अगर (link->aux_access_disabled)
		वापस;

	अगर (!dm_helpers_dp_पढ़ो_dpcd(link->ctx, link, DP_DOWNSPREAD_CTRL,
				     &old_करोwnspपढ़ो.raw,
				     माप(old_करोwnspपढ़ो)))
		वापस;

	new_करोwnspपढ़ो.raw = old_करोwnspपढ़ो.raw;
	new_करोwnspपढ़ो.bits.IGNORE_MSA_TIMING_PARAM =
		(stream->ignore_msa_timing_param) ? 1 : 0;

	अगर (new_करोwnspपढ़ो.raw != old_करोwnspपढ़ो.raw)
		dm_helpers_dp_ग_लिखो_dpcd(link->ctx, link, DP_DOWNSPREAD_CTRL,
					 &new_करोwnspपढ़ो.raw,
					 माप(new_करोwnspपढ़ो));
पूर्ण
