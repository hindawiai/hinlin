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

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_vblank.h>

#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "dc.h"
#समावेश "amdgpu_securedisplay.h"

अटल स्थिर अक्षर *स्थिर pipe_crc_sources[] = अणु
	"none",
	"crtc",
	"crtc dither",
	"dprx",
	"dprx dither",
	"auto",
पूर्ण;

अटल क्रमागत amdgpu_dm_pipe_crc_source dm_parse_crc_source(स्थिर अक्षर *source)
अणु
	अगर (!source || !म_भेद(source, "none"))
		वापस AMDGPU_DM_PIPE_CRC_SOURCE_NONE;
	अगर (!म_भेद(source, "auto") || !म_भेद(source, "crtc"))
		वापस AMDGPU_DM_PIPE_CRC_SOURCE_CRTC;
	अगर (!म_भेद(source, "dprx"))
		वापस AMDGPU_DM_PIPE_CRC_SOURCE_DPRX;
	अगर (!म_भेद(source, "crtc dither"))
		वापस AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER;
	अगर (!म_भेद(source, "dprx dither"))
		वापस AMDGPU_DM_PIPE_CRC_SOURCE_DPRX_DITHER;

	वापस AMDGPU_DM_PIPE_CRC_SOURCE_INVALID;
पूर्ण

अटल bool dm_is_crc_source_crtc(क्रमागत amdgpu_dm_pipe_crc_source src)
अणु
	वापस (src == AMDGPU_DM_PIPE_CRC_SOURCE_CRTC) ||
	       (src == AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER);
पूर्ण

अटल bool dm_is_crc_source_dprx(क्रमागत amdgpu_dm_pipe_crc_source src)
अणु
	वापस (src == AMDGPU_DM_PIPE_CRC_SOURCE_DPRX) ||
	       (src == AMDGPU_DM_PIPE_CRC_SOURCE_DPRX_DITHER);
पूर्ण

अटल bool dm_need_crc_dither(क्रमागत amdgpu_dm_pipe_crc_source src)
अणु
	वापस (src == AMDGPU_DM_PIPE_CRC_SOURCE_CRTC_DITHER) ||
	       (src == AMDGPU_DM_PIPE_CRC_SOURCE_DPRX_DITHER) ||
	       (src == AMDGPU_DM_PIPE_CRC_SOURCE_NONE);
पूर्ण

स्थिर अक्षर *स्थिर *amdgpu_dm_crtc_get_crc_sources(काष्ठा drm_crtc *crtc,
						  माप_प्रकार *count)
अणु
	*count = ARRAY_SIZE(pipe_crc_sources);
	वापस pipe_crc_sources;
पूर्ण

#अगर_घोषित CONFIG_DRM_AMD_SECURE_DISPLAY
अटल व्योम amdgpu_dm_set_crc_winकरोw_शेष(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);

	spin_lock_irq(&drm_dev->event_lock);
	acrtc->dm_irq_params.crc_winकरोw.x_start = 0;
	acrtc->dm_irq_params.crc_winकरोw.y_start = 0;
	acrtc->dm_irq_params.crc_winकरोw.x_end = 0;
	acrtc->dm_irq_params.crc_winकरोw.y_end = 0;
	acrtc->dm_irq_params.crc_winकरोw.activated = false;
	acrtc->dm_irq_params.crc_winकरोw.update_win = false;
	acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 0;
	spin_unlock_irq(&drm_dev->event_lock);
पूर्ण

अटल व्योम amdgpu_dm_crtc_notअगरy_ta_to_पढ़ो(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा crc_rd_work *crc_rd_wrk;
	काष्ठा amdgpu_device *adev;
	काष्ठा psp_context *psp;
	काष्ठा securedisplay_cmd *securedisplay_cmd;
	काष्ठा drm_crtc *crtc;
	uपूर्णांक8_t phy_id;
	पूर्णांक ret;

	crc_rd_wrk = container_of(work, काष्ठा crc_rd_work, notअगरy_ta_work);
	spin_lock_irq(&crc_rd_wrk->crc_rd_work_lock);
	crtc = crc_rd_wrk->crtc;

	अगर (!crtc) अणु
		spin_unlock_irq(&crc_rd_wrk->crc_rd_work_lock);
		वापस;
	पूर्ण

	adev = drm_to_adev(crtc->dev);
	psp = &adev->psp;
	phy_id = crc_rd_wrk->phy_inst;
	spin_unlock_irq(&crc_rd_wrk->crc_rd_work_lock);

	psp_prep_securedisplay_cmd_buf(psp, &securedisplay_cmd,
						TA_SECUREDISPLAY_COMMAND__SEND_ROI_CRC);
	securedisplay_cmd->securedisplay_in_message.send_roi_crc.phy_id =
						phy_id;
	ret = psp_securedisplay_invoke(psp, TA_SECUREDISPLAY_COMMAND__SEND_ROI_CRC);
	अगर (!ret) अणु
		अगर (securedisplay_cmd->status != TA_SECUREDISPLAY_STATUS__SUCCESS) अणु
			psp_securedisplay_parse_resp_status(psp, securedisplay_cmd->status);
		पूर्ण
	पूर्ण
पूर्ण

bool amdgpu_dm_crc_winकरोw_is_activated(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);
	bool ret = false;

	spin_lock_irq(&drm_dev->event_lock);
	ret = acrtc->dm_irq_params.crc_winकरोw.activated;
	spin_unlock_irq(&drm_dev->event_lock);

	वापस ret;
पूर्ण
#पूर्ण_अगर

पूर्णांक
amdgpu_dm_crtc_verअगरy_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *src_name,
				 माप_प्रकार *values_cnt)
अणु
	क्रमागत amdgpu_dm_pipe_crc_source source = dm_parse_crc_source(src_name);

	अगर (source < 0) अणु
		DRM_DEBUG_DRIVER("Unknown CRC source %s for CRTC%d\n",
				 src_name, crtc->index);
		वापस -EINVAL;
	पूर्ण

	*values_cnt = 3;
	वापस 0;
पूर्ण

पूर्णांक amdgpu_dm_crtc_configure_crc_source(काष्ठा drm_crtc *crtc,
					काष्ठा dm_crtc_state *dm_crtc_state,
					क्रमागत amdgpu_dm_pipe_crc_source source)
अणु
	काष्ठा amdgpu_device *adev = drm_to_adev(crtc->dev);
	काष्ठा dc_stream_state *stream_state = dm_crtc_state->stream;
	bool enable = amdgpu_dm_is_valid_crc_source(source);
	पूर्णांक ret = 0;

	/* Configuration will be deferred to stream enable. */
	अगर (!stream_state)
		वापस 0;

	mutex_lock(&adev->dm.dc_lock);

	/* Enable CRTC CRC generation अगर necessary. */
	अगर (dm_is_crc_source_crtc(source) || source == AMDGPU_DM_PIPE_CRC_SOURCE_NONE) अणु
#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
		अगर (!enable) अणु
			अगर (adev->dm.crc_rd_wrk) अणु
				flush_work(&adev->dm.crc_rd_wrk->notअगरy_ta_work);
				spin_lock_irq(&adev->dm.crc_rd_wrk->crc_rd_work_lock);
				अगर (adev->dm.crc_rd_wrk->crtc == crtc) अणु
					dc_stream_stop_dmcu_crc_win_update(stream_state->ctx->dc,
									dm_crtc_state->stream);
					adev->dm.crc_rd_wrk->crtc = शून्य;
				पूर्ण
				spin_unlock_irq(&adev->dm.crc_rd_wrk->crc_rd_work_lock);
			पूर्ण
		पूर्ण
#पूर्ण_अगर
		अगर (!dc_stream_configure_crc(stream_state->ctx->dc,
					     stream_state, शून्य, enable, enable)) अणु
			ret = -EINVAL;
			जाओ unlock;
		पूर्ण
	पूर्ण

	/* Configure dithering */
	अगर (!dm_need_crc_dither(source)) अणु
		dc_stream_set_dither_option(stream_state, DITHER_OPTION_TRUN8);
		dc_stream_set_dyn_expansion(stream_state->ctx->dc, stream_state,
					    DYN_EXPANSION_DISABLE);
	पूर्ण अन्यथा अणु
		dc_stream_set_dither_option(stream_state,
					    DITHER_OPTION_DEFAULT);
		dc_stream_set_dyn_expansion(stream_state->ctx->dc, stream_state,
					    DYN_EXPANSION_AUTO);
	पूर्ण

unlock:
	mutex_unlock(&adev->dm.dc_lock);

	वापस ret;
पूर्ण

पूर्णांक amdgpu_dm_crtc_set_crc_source(काष्ठा drm_crtc *crtc, स्थिर अक्षर *src_name)
अणु
	क्रमागत amdgpu_dm_pipe_crc_source source = dm_parse_crc_source(src_name);
	क्रमागत amdgpu_dm_pipe_crc_source cur_crc_src;
	काष्ठा drm_crtc_commit *commit;
	काष्ठा dm_crtc_state *crtc_state;
	काष्ठा drm_device *drm_dev = crtc->dev;
	काष्ठा amdgpu_crtc *acrtc = to_amdgpu_crtc(crtc);
	काष्ठा drm_dp_aux *aux = शून्य;
	bool enable = false;
	bool enabled = false;
	पूर्णांक ret = 0;

	अगर (source < 0) अणु
		DRM_DEBUG_DRIVER("Unknown CRC source %s for CRTC%d\n",
				 src_name, crtc->index);
		वापस -EINVAL;
	पूर्ण

	ret = drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (ret)
		वापस ret;

	spin_lock(&crtc->commit_lock);
	commit = list_first_entry_or_null(&crtc->commit_list,
					  काष्ठा drm_crtc_commit, commit_entry);
	अगर (commit)
		drm_crtc_commit_get(commit);
	spin_unlock(&crtc->commit_lock);

	अगर (commit) अणु
		/*
		 * Need to रुको क्रम all outstanding programming to complete
		 * in commit tail since it can modअगरy CRC related fields and
		 * hardware state. Since we're holding the CRTC lock we're
		 * guaranteed that no other commit work can be queued off
		 * beक्रमe we modअगरy the state below.
		 */
		ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&commit->hw_करोne, 10 * HZ);
		अगर (ret)
			जाओ cleanup;
	पूर्ण

	enable = amdgpu_dm_is_valid_crc_source(source);
	crtc_state = to_dm_crtc_state(crtc->state);
	spin_lock_irq(&drm_dev->event_lock);
	cur_crc_src = acrtc->dm_irq_params.crc_src;
	spin_unlock_irq(&drm_dev->event_lock);

	/*
	 * USER REQ SRC | CURRENT SRC | BEHAVIOR
	 * -----------------------------
	 * None         | None        | Do nothing
	 * None         | CRTC        | Disable CRTC CRC, set शेष to dither
	 * None         | DPRX        | Disable DPRX CRC, need 'aux', set शेष to dither
	 * None         | CRTC DITHER | Disable CRTC CRC
	 * None         | DPRX DITHER | Disable DPRX CRC, need 'aux'
	 * CRTC         | XXXX        | Enable CRTC CRC, no dither
	 * DPRX         | XXXX        | Enable DPRX CRC, need 'aux', no dither
	 * CRTC DITHER  | XXXX        | Enable CRTC CRC, set dither
	 * DPRX DITHER  | XXXX        | Enable DPRX CRC, need 'aux', set dither
	 */
	अगर (dm_is_crc_source_dprx(source) ||
	    (source == AMDGPU_DM_PIPE_CRC_SOURCE_NONE &&
	     dm_is_crc_source_dprx(cur_crc_src))) अणु
		काष्ठा amdgpu_dm_connector *aconn = शून्य;
		काष्ठा drm_connector *connector;
		काष्ठा drm_connector_list_iter conn_iter;

		drm_connector_list_iter_begin(crtc->dev, &conn_iter);
		drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
			अगर (!connector->state || connector->state->crtc != crtc)
				जारी;

			aconn = to_amdgpu_dm_connector(connector);
			अवरोध;
		पूर्ण
		drm_connector_list_iter_end(&conn_iter);

		अगर (!aconn) अणु
			DRM_DEBUG_DRIVER("No amd connector matching CRTC-%d\n", crtc->index);
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण

		aux = (aconn->port) ? &aconn->port->aux : &aconn->dm_dp_aux.aux;

		अगर (!aux) अणु
			DRM_DEBUG_DRIVER("No dp aux for amd connector\n");
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
	amdgpu_dm_set_crc_winकरोw_शेष(crtc);
#पूर्ण_अगर

	अगर (amdgpu_dm_crtc_configure_crc_source(crtc, crtc_state, source)) अणु
		ret = -EINVAL;
		जाओ cleanup;
	पूर्ण

	/*
	 * Reading the CRC requires the vblank पूर्णांकerrupt handler to be
	 * enabled. Keep a reference until CRC capture stops.
	 */
	enabled = amdgpu_dm_is_valid_crc_source(cur_crc_src);
	अगर (!enabled && enable) अणु
		ret = drm_crtc_vblank_get(crtc);
		अगर (ret)
			जाओ cleanup;

		अगर (dm_is_crc_source_dprx(source)) अणु
			अगर (drm_dp_start_crc(aux, crtc)) अणु
				DRM_DEBUG_DRIVER("dp start crc failed\n");
				ret = -EINVAL;
				जाओ cleanup;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (enabled && !enable) अणु
		drm_crtc_vblank_put(crtc);
		अगर (dm_is_crc_source_dprx(source)) अणु
			अगर (drm_dp_stop_crc(aux)) अणु
				DRM_DEBUG_DRIVER("dp stop crc failed\n");
				ret = -EINVAL;
				जाओ cleanup;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irq(&drm_dev->event_lock);
	acrtc->dm_irq_params.crc_src = source;
	spin_unlock_irq(&drm_dev->event_lock);

	/* Reset crc_skipped on dm state */
	crtc_state->crc_skip_count = 0;

cleanup:
	अगर (commit)
		drm_crtc_commit_put(commit);

	drm_modeset_unlock(&crtc->mutex);

	वापस ret;
पूर्ण

/**
 * amdgpu_dm_crtc_handle_crc_irq: Report to DRM the CRC on given CRTC.
 * @crtc: DRM CRTC object.
 *
 * This function should be called at the end of a vblank, when the fb has been
 * fully processed through the pipe.
 */
व्योम amdgpu_dm_crtc_handle_crc_irq(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dm_crtc_state *crtc_state;
	काष्ठा dc_stream_state *stream_state;
	काष्ठा drm_device *drm_dev = शून्य;
	क्रमागत amdgpu_dm_pipe_crc_source cur_crc_src;
	काष्ठा amdgpu_crtc *acrtc = शून्य;
	uपूर्णांक32_t crcs[3];
	अचिन्हित दीर्घ flags;

	अगर (crtc == शून्य)
		वापस;

	crtc_state = to_dm_crtc_state(crtc->state);
	stream_state = crtc_state->stream;
	acrtc = to_amdgpu_crtc(crtc);
	drm_dev = crtc->dev;

	spin_lock_irqsave(&drm_dev->event_lock, flags);
	cur_crc_src = acrtc->dm_irq_params.crc_src;
	spin_unlock_irqrestore(&drm_dev->event_lock, flags);

	/* Early वापस अगर CRC capture is not enabled. */
	अगर (!amdgpu_dm_is_valid_crc_source(cur_crc_src))
		वापस;

	/*
	 * Since flipping and crc enablement happen asynchronously, we - more
	 * often than not - will be वापसing an 'uncooked' crc on first frame.
	 * Probably because hw isn't पढ़ोy yet. For added security, skip the
	 * first two CRC values.
	 */
	अगर (crtc_state->crc_skip_count < 2) अणु
		crtc_state->crc_skip_count += 1;
		वापस;
	पूर्ण

	अगर (dm_is_crc_source_crtc(cur_crc_src)) अणु
		अगर (!dc_stream_get_crc(stream_state->ctx->dc, stream_state,
				       &crcs[0], &crcs[1], &crcs[2]))
			वापस;

		drm_crtc_add_crc_entry(crtc, true,
				       drm_crtc_accurate_vblank_count(crtc), crcs);
	पूर्ण
पूर्ण

#अगर defined(CONFIG_DRM_AMD_SECURE_DISPLAY)
व्योम amdgpu_dm_crtc_handle_crc_winकरोw_irq(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा dc_stream_state *stream_state;
	काष्ठा drm_device *drm_dev = शून्य;
	क्रमागत amdgpu_dm_pipe_crc_source cur_crc_src;
	काष्ठा amdgpu_crtc *acrtc = शून्य;
	काष्ठा amdgpu_device *adev = शून्य;
	काष्ठा crc_rd_work *crc_rd_wrk = शून्य;
	काष्ठा crc_params *crc_winकरोw = शून्य, पंचांगp_winकरोw;
	अचिन्हित दीर्घ flags1, flags2;
	काष्ठा crtc_position position;
	uपूर्णांक32_t v_blank;
	uपूर्णांक32_t v_back_porch;
	uपूर्णांक32_t crc_winकरोw_latch_up_line;
	काष्ठा dc_crtc_timing *timing_out;

	अगर (crtc == शून्य)
		वापस;

	acrtc = to_amdgpu_crtc(crtc);
	adev = drm_to_adev(crtc->dev);
	drm_dev = crtc->dev;

	spin_lock_irqsave(&drm_dev->event_lock, flags1);
	stream_state = acrtc->dm_irq_params.stream;
	cur_crc_src = acrtc->dm_irq_params.crc_src;
	timing_out = &stream_state->timing;

	/* Early वापस अगर CRC capture is not enabled. */
	अगर (!amdgpu_dm_is_valid_crc_source(cur_crc_src))
		जाओ cleanup;

	अगर (dm_is_crc_source_crtc(cur_crc_src)) अणु
		अगर (acrtc->dm_irq_params.crc_winकरोw.activated) अणु
			अगर (acrtc->dm_irq_params.crc_winकरोw.update_win) अणु
				अगर (acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt) अणु
					acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt -= 1;
					जाओ cleanup;
				पूर्ण
				crc_winकरोw = &पंचांगp_winकरोw;

				पंचांगp_winकरोw.winकरोwa_x_start =
							acrtc->dm_irq_params.crc_winकरोw.x_start;
				पंचांगp_winकरोw.winकरोwa_y_start =
							acrtc->dm_irq_params.crc_winकरोw.y_start;
				पंचांगp_winकरोw.winकरोwa_x_end =
							acrtc->dm_irq_params.crc_winकरोw.x_end;
				पंचांगp_winकरोw.winकरोwa_y_end =
							acrtc->dm_irq_params.crc_winकरोw.y_end;
				पंचांगp_winकरोw.winकरोwb_x_start =
							acrtc->dm_irq_params.crc_winकरोw.x_start;
				पंचांगp_winकरोw.winकरोwb_y_start =
							acrtc->dm_irq_params.crc_winकरोw.y_start;
				पंचांगp_winकरोw.winकरोwb_x_end =
							acrtc->dm_irq_params.crc_winकरोw.x_end;
				पंचांगp_winकरोw.winकरोwb_y_end =
							acrtc->dm_irq_params.crc_winकरोw.y_end;

				dc_stream_क्रमward_dmcu_crc_winकरोw(stream_state->ctx->dc,
									stream_state, crc_winकरोw);

				acrtc->dm_irq_params.crc_winकरोw.update_win = false;

				dc_stream_get_crtc_position(stream_state->ctx->dc, &stream_state, 1,
					&position.vertical_count,
					&position.nominal_vcount);

				v_blank = timing_out->v_total - timing_out->v_border_top -
					timing_out->v_addressable - timing_out->v_border_bottom;

				v_back_porch = v_blank - timing_out->v_front_porch -
					timing_out->v_sync_width;

				crc_winकरोw_latch_up_line = v_back_porch + timing_out->v_sync_width;

				/* take 3 lines margin*/
				अगर ((position.vertical_count + 3) >= crc_winकरोw_latch_up_line)
					acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 1;
				अन्यथा
					acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 0;
			पूर्ण अन्यथा अणु
				अगर (acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt == 0) अणु
					अगर (adev->dm.crc_rd_wrk) अणु
						crc_rd_wrk = adev->dm.crc_rd_wrk;
						spin_lock_irqsave(&crc_rd_wrk->crc_rd_work_lock, flags2);
						crc_rd_wrk->phy_inst =
							stream_state->link->link_enc_hw_inst;
						spin_unlock_irqrestore(&crc_rd_wrk->crc_rd_work_lock, flags2);
						schedule_work(&crc_rd_wrk->notअगरy_ta_work);
					पूर्ण
				पूर्ण अन्यथा अणु
					acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt -= 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

cleanup:
	spin_unlock_irqrestore(&drm_dev->event_lock, flags1);
पूर्ण

व्योम amdgpu_dm_crtc_secure_display_resume(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_crtc *crtc;
	क्रमागत amdgpu_dm_pipe_crc_source cur_crc_src;
	काष्ठा crc_rd_work *crc_rd_wrk = adev->dm.crc_rd_wrk;
	काष्ठा crc_winकरोw_parm cur_crc_winकरोw;
	काष्ठा amdgpu_crtc *acrtc = शून्य;

	drm_क्रम_each_crtc(crtc, &adev->ddev) अणु
		acrtc = to_amdgpu_crtc(crtc);

		spin_lock_irq(&adev_to_drm(adev)->event_lock);
		cur_crc_src = acrtc->dm_irq_params.crc_src;
		cur_crc_winकरोw = acrtc->dm_irq_params.crc_winकरोw;
		spin_unlock_irq(&adev_to_drm(adev)->event_lock);

		अगर (amdgpu_dm_is_valid_crc_source(cur_crc_src)) अणु
			amdgpu_dm_crtc_set_crc_source(crtc,
				pipe_crc_sources[cur_crc_src]);
			spin_lock_irq(&adev_to_drm(adev)->event_lock);
			acrtc->dm_irq_params.crc_winकरोw = cur_crc_winकरोw;
			अगर (acrtc->dm_irq_params.crc_winकरोw.activated) अणु
				acrtc->dm_irq_params.crc_winकरोw.update_win = true;
				acrtc->dm_irq_params.crc_winकरोw.skip_frame_cnt = 1;
				spin_lock_irq(&crc_rd_wrk->crc_rd_work_lock);
				crc_rd_wrk->crtc = crtc;
				spin_unlock_irq(&crc_rd_wrk->crc_rd_work_lock);
			पूर्ण
			spin_unlock_irq(&adev_to_drm(adev)->event_lock);
		पूर्ण
	पूर्ण
पूर्ण

व्योम amdgpu_dm_crtc_secure_display_suspend(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा crc_winकरोw_parm cur_crc_winकरोw;
	क्रमागत amdgpu_dm_pipe_crc_source cur_crc_src;
	काष्ठा amdgpu_crtc *acrtc = शून्य;

	drm_क्रम_each_crtc(crtc, &adev->ddev) अणु
		acrtc = to_amdgpu_crtc(crtc);

		spin_lock_irq(&adev_to_drm(adev)->event_lock);
		cur_crc_src = acrtc->dm_irq_params.crc_src;
		cur_crc_winकरोw = acrtc->dm_irq_params.crc_winकरोw;
		cur_crc_winकरोw.update_win = false;
		spin_unlock_irq(&adev_to_drm(adev)->event_lock);

		अगर (amdgpu_dm_is_valid_crc_source(cur_crc_src)) अणु
			amdgpu_dm_crtc_set_crc_source(crtc, शून्य);
			spin_lock_irq(&adev_to_drm(adev)->event_lock);
			/* For resume to set back crc source*/
			acrtc->dm_irq_params.crc_src = cur_crc_src;
			acrtc->dm_irq_params.crc_winकरोw = cur_crc_winकरोw;
			spin_unlock_irq(&adev_to_drm(adev)->event_lock);
		पूर्ण
	पूर्ण

पूर्ण

काष्ठा crc_rd_work *amdgpu_dm_crtc_secure_display_create_work(व्योम)
अणु
	काष्ठा crc_rd_work *crc_rd_wrk = शून्य;

	crc_rd_wrk = kzalloc(माप(*crc_rd_wrk), GFP_KERNEL);

	अगर (!crc_rd_wrk)
		वापस शून्य;

	spin_lock_init(&crc_rd_wrk->crc_rd_work_lock);
	INIT_WORK(&crc_rd_wrk->notअगरy_ta_work, amdgpu_dm_crtc_notअगरy_ta_to_पढ़ो);

	वापस crc_rd_wrk;
पूर्ण
#पूर्ण_अगर
