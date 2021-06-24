<शैली गुरु>
/*
 * Copyright 2019 Advanced Micro Devices, Inc.
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

#समावेश "amdgpu_dm_hdcp.h"
#समावेश "amdgpu.h"
#समावेश "amdgpu_dm.h"
#समावेश "dm_helpers.h"
#समावेश <drm/drm_hdcp.h>
#समावेश "hdcp_psp.h"

/*
 * If the SRM version being loaded is less than or equal to the
 * currently loaded SRM, psp will वापस 0xFFFF as the version
 */
#घोषणा PSP_SRM_VERSION_MAX 0xFFFF

अटल bool
lp_ग_लिखो_i2c(व्योम *handle, uपूर्णांक32_t address, स्थिर uपूर्णांक8_t *data, uपूर्णांक32_t size)
अणु

	काष्ठा dc_link *link = handle;
	काष्ठा i2c_payload i2c_payloads[] = अणुअणुtrue, address, size, (व्योम *)dataपूर्ण पूर्ण;
	काष्ठा i2c_command cmd = अणुi2c_payloads, 1, I2C_COMMAND_ENGINE_HW, link->dc->caps.i2c_speed_in_khzपूर्ण;

	वापस dm_helpers_submit_i2c(link->ctx, link, &cmd);
पूर्ण

अटल bool
lp_पढ़ो_i2c(व्योम *handle, uपूर्णांक32_t address, uपूर्णांक8_t offset, uपूर्णांक8_t *data, uपूर्णांक32_t size)
अणु
	काष्ठा dc_link *link = handle;

	काष्ठा i2c_payload i2c_payloads[] = अणुअणुtrue, address, 1, &offsetपूर्ण, अणुfalse, address, size, dataपूर्ण पूर्ण;
	काष्ठा i2c_command cmd = अणुi2c_payloads, 2, I2C_COMMAND_ENGINE_HW, link->dc->caps.i2c_speed_in_khzपूर्ण;

	वापस dm_helpers_submit_i2c(link->ctx, link, &cmd);
पूर्ण

अटल bool
lp_ग_लिखो_dpcd(व्योम *handle, uपूर्णांक32_t address, स्थिर uपूर्णांक8_t *data, uपूर्णांक32_t size)
अणु
	काष्ठा dc_link *link = handle;

	वापस dm_helpers_dp_ग_लिखो_dpcd(link->ctx, link, address, data, size);
पूर्ण

अटल bool
lp_पढ़ो_dpcd(व्योम *handle, uपूर्णांक32_t address, uपूर्णांक8_t *data, uपूर्णांक32_t size)
अणु
	काष्ठा dc_link *link = handle;

	वापस dm_helpers_dp_पढ़ो_dpcd(link->ctx, link, address, data, size);
पूर्ण

अटल uपूर्णांक8_t *psp_get_srm(काष्ठा psp_context *psp, uपूर्णांक32_t *srm_version, uपूर्णांक32_t *srm_size)
अणु

	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;

	अगर (!psp->hdcp_context.hdcp_initialized) अणु
		DRM_WARN("Failed to get hdcp srm. HDCP TA is not initialized.");
		वापस शून्य;
	पूर्ण

	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP_GET_SRM;
	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS)
		वापस शून्य;

	*srm_version = hdcp_cmd->out_msg.hdcp_get_srm.srm_version;
	*srm_size = hdcp_cmd->out_msg.hdcp_get_srm.srm_buf_size;


	वापस hdcp_cmd->out_msg.hdcp_get_srm.srm_buf;
पूर्ण

अटल पूर्णांक psp_set_srm(काष्ठा psp_context *psp, uपूर्णांक8_t *srm, uपूर्णांक32_t srm_size, uपूर्णांक32_t *srm_version)
अणु

	काष्ठा ta_hdcp_shared_memory *hdcp_cmd;

	अगर (!psp->hdcp_context.hdcp_initialized) अणु
		DRM_WARN("Failed to get hdcp srm. HDCP TA is not initialized.");
		वापस -EINVAL;
	पूर्ण

	hdcp_cmd = (काष्ठा ta_hdcp_shared_memory *)psp->hdcp_context.hdcp_shared_buf;
	स_रखो(hdcp_cmd, 0, माप(काष्ठा ta_hdcp_shared_memory));

	स_नकल(hdcp_cmd->in_msg.hdcp_set_srm.srm_buf, srm, srm_size);
	hdcp_cmd->in_msg.hdcp_set_srm.srm_buf_size = srm_size;
	hdcp_cmd->cmd_id = TA_HDCP_COMMAND__HDCP_SET_SRM;

	psp_hdcp_invoke(psp, hdcp_cmd->cmd_id);

	अगर (hdcp_cmd->hdcp_status != TA_HDCP_STATUS__SUCCESS || hdcp_cmd->out_msg.hdcp_set_srm.valid_signature != 1 ||
	    hdcp_cmd->out_msg.hdcp_set_srm.srm_version == PSP_SRM_VERSION_MAX)
		वापस -EINVAL;

	*srm_version = hdcp_cmd->out_msg.hdcp_set_srm.srm_version;
	वापस 0;
पूर्ण

अटल व्योम process_output(काष्ठा hdcp_workqueue *hdcp_work)
अणु
	काष्ठा mod_hdcp_output output = hdcp_work->output;

	अगर (output.callback_stop)
		cancel_delayed_work(&hdcp_work->callback_dwork);

	अगर (output.callback_needed)
		schedule_delayed_work(&hdcp_work->callback_dwork,
				      msecs_to_jअगरfies(output.callback_delay));

	अगर (output.watchकरोg_समयr_stop)
		cancel_delayed_work(&hdcp_work->watchकरोg_समयr_dwork);

	अगर (output.watchकरोg_समयr_needed)
		schedule_delayed_work(&hdcp_work->watchकरोg_समयr_dwork,
				      msecs_to_jअगरfies(output.watchकरोg_समयr_delay));

	schedule_delayed_work(&hdcp_work->property_validate_dwork, msecs_to_jअगरfies(0));
पूर्ण

अटल व्योम link_lock(काष्ठा hdcp_workqueue *work, bool lock)
अणु

	पूर्णांक i = 0;

	क्रम (i = 0; i < work->max_link; i++) अणु
		अगर (lock)
			mutex_lock(&work[i].mutex);
		अन्यथा
			mutex_unlock(&work[i].mutex);
	पूर्ण
पूर्ण
व्योम hdcp_update_display(काष्ठा hdcp_workqueue *hdcp_work,
			 अचिन्हित पूर्णांक link_index,
			 काष्ठा amdgpu_dm_connector *aconnector,
			 uपूर्णांक8_t content_type,
			 bool enable_encryption)
अणु
	काष्ठा hdcp_workqueue *hdcp_w = &hdcp_work[link_index];
	काष्ठा mod_hdcp_display *display = &hdcp_work[link_index].display;
	काष्ठा mod_hdcp_link *link = &hdcp_work[link_index].link;
	काष्ठा mod_hdcp_display_query query;

	mutex_lock(&hdcp_w->mutex);
	hdcp_w->aconnector = aconnector;

	query.display = शून्य;
	mod_hdcp_query_display(&hdcp_w->hdcp, aconnector->base.index, &query);

	अगर (query.display != शून्य) अणु
		स_नकल(display, query.display, माप(काष्ठा mod_hdcp_display));
		mod_hdcp_हटाओ_display(&hdcp_w->hdcp, aconnector->base.index, &hdcp_w->output);

		hdcp_w->link.adjust.hdcp2.क्रमce_type = MOD_HDCP_FORCE_TYPE_0;

		अगर (enable_encryption) अणु
			/* Explicitly set the saved SRM as sysfs call will be after we alपढ़ोy enabled hdcp
			 * (s3 resume हाल)
			 */
			अगर (hdcp_work->srm_size > 0)
				psp_set_srm(hdcp_work->hdcp.config.psp.handle, hdcp_work->srm, hdcp_work->srm_size,
					    &hdcp_work->srm_version);

			display->adjust.disable = MOD_HDCP_DISPLAY_NOT_DISABLE;
			अगर (content_type == DRM_MODE_HDCP_CONTENT_TYPE0) अणु
				hdcp_w->link.adjust.hdcp1.disable = 0;
				hdcp_w->link.adjust.hdcp2.क्रमce_type = MOD_HDCP_FORCE_TYPE_0;
			पूर्ण अन्यथा अगर (content_type == DRM_MODE_HDCP_CONTENT_TYPE1) अणु
				hdcp_w->link.adjust.hdcp1.disable = 1;
				hdcp_w->link.adjust.hdcp2.क्रमce_type = MOD_HDCP_FORCE_TYPE_1;
			पूर्ण

			schedule_delayed_work(&hdcp_w->property_validate_dwork,
					      msecs_to_jअगरfies(DRM_HDCP_CHECK_PERIOD_MS));
		पूर्ण अन्यथा अणु
			display->adjust.disable = MOD_HDCP_DISPLAY_DISABLE_AUTHENTICATION;
			hdcp_w->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;
			cancel_delayed_work(&hdcp_w->property_validate_dwork);
		पूर्ण

		display->state = MOD_HDCP_DISPLAY_ACTIVE;
	पूर्ण

	mod_hdcp_add_display(&hdcp_w->hdcp, link, display, &hdcp_w->output);

	process_output(hdcp_w);
	mutex_unlock(&hdcp_w->mutex);
पूर्ण

अटल व्योम hdcp_हटाओ_display(काष्ठा hdcp_workqueue *hdcp_work,
			 अचिन्हित पूर्णांक link_index,
			 काष्ठा amdgpu_dm_connector *aconnector)
अणु
	काष्ठा hdcp_workqueue *hdcp_w = &hdcp_work[link_index];

	mutex_lock(&hdcp_w->mutex);
	hdcp_w->aconnector = aconnector;

	mod_hdcp_हटाओ_display(&hdcp_w->hdcp, aconnector->base.index, &hdcp_w->output);

	process_output(hdcp_w);
	mutex_unlock(&hdcp_w->mutex);
पूर्ण
व्योम hdcp_reset_display(काष्ठा hdcp_workqueue *hdcp_work, अचिन्हित पूर्णांक link_index)
अणु
	काष्ठा hdcp_workqueue *hdcp_w = &hdcp_work[link_index];

	mutex_lock(&hdcp_w->mutex);

	mod_hdcp_reset_connection(&hdcp_w->hdcp,  &hdcp_w->output);

	cancel_delayed_work(&hdcp_w->property_validate_dwork);
	hdcp_w->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;

	process_output(hdcp_w);

	mutex_unlock(&hdcp_w->mutex);
पूर्ण

व्योम hdcp_handle_cpirq(काष्ठा hdcp_workqueue *hdcp_work, अचिन्हित पूर्णांक link_index)
अणु
	काष्ठा hdcp_workqueue *hdcp_w = &hdcp_work[link_index];

	schedule_work(&hdcp_w->cpirq_work);
पूर्ण




अटल व्योम event_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdcp_workqueue *hdcp_work;

	hdcp_work = container_of(to_delayed_work(work), काष्ठा hdcp_workqueue,
				      callback_dwork);

	mutex_lock(&hdcp_work->mutex);

	cancel_delayed_work(&hdcp_work->callback_dwork);

	mod_hdcp_process_event(&hdcp_work->hdcp, MOD_HDCP_EVENT_CALLBACK,
			       &hdcp_work->output);

	process_output(hdcp_work);

	mutex_unlock(&hdcp_work->mutex);


पूर्ण
अटल व्योम event_property_update(काष्ठा work_काष्ठा *work)
अणु

	काष्ठा hdcp_workqueue *hdcp_work = container_of(work, काष्ठा hdcp_workqueue, property_update_work);
	काष्ठा amdgpu_dm_connector *aconnector = hdcp_work->aconnector;
	काष्ठा drm_device *dev = hdcp_work->aconnector->base.dev;
	दीर्घ ret;

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	mutex_lock(&hdcp_work->mutex);


	अगर (aconnector->base.state->commit) अणु
		ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&aconnector->base.state->commit->hw_करोne, 10 * HZ);

		अगर (ret == 0) अणु
			DRM_ERROR("HDCP state unknown! Setting it to DESIRED");
			hdcp_work->encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;
		पूर्ण
	पूर्ण

	अगर (hdcp_work->encryption_status != MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF) अणु
		अगर (aconnector->base.state->hdcp_content_type == DRM_MODE_HDCP_CONTENT_TYPE0 &&
		    hdcp_work->encryption_status <= MOD_HDCP_ENCRYPTION_STATUS_HDCP2_TYPE0_ON)
			drm_hdcp_update_content_protection(&aconnector->base, DRM_MODE_CONTENT_PROTECTION_ENABLED);
		अन्यथा अगर (aconnector->base.state->hdcp_content_type == DRM_MODE_HDCP_CONTENT_TYPE1 &&
			 hdcp_work->encryption_status == MOD_HDCP_ENCRYPTION_STATUS_HDCP2_TYPE1_ON)
			drm_hdcp_update_content_protection(&aconnector->base, DRM_MODE_CONTENT_PROTECTION_ENABLED);
	पूर्ण अन्यथा अणु
		drm_hdcp_update_content_protection(&aconnector->base, DRM_MODE_CONTENT_PROTECTION_DESIRED);
	पूर्ण


	mutex_unlock(&hdcp_work->mutex);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
पूर्ण

अटल व्योम event_property_validate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdcp_workqueue *hdcp_work =
		container_of(to_delayed_work(work), काष्ठा hdcp_workqueue, property_validate_dwork);
	काष्ठा mod_hdcp_display_query query;
	काष्ठा amdgpu_dm_connector *aconnector = hdcp_work->aconnector;

	अगर (!aconnector)
		वापस;

	mutex_lock(&hdcp_work->mutex);

	query.encryption_status = MOD_HDCP_ENCRYPTION_STATUS_HDCP_OFF;
	mod_hdcp_query_display(&hdcp_work->hdcp, aconnector->base.index, &query);

	अगर (query.encryption_status != hdcp_work->encryption_status) अणु
		hdcp_work->encryption_status = query.encryption_status;
		schedule_work(&hdcp_work->property_update_work);
	पूर्ण

	mutex_unlock(&hdcp_work->mutex);
पूर्ण

अटल व्योम event_watchकरोg_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdcp_workqueue *hdcp_work;

	hdcp_work = container_of(to_delayed_work(work),
				      काष्ठा hdcp_workqueue,
				      watchकरोg_समयr_dwork);

	mutex_lock(&hdcp_work->mutex);

	cancel_delayed_work(&hdcp_work->watchकरोg_समयr_dwork);

	mod_hdcp_process_event(&hdcp_work->hdcp,
			       MOD_HDCP_EVENT_WATCHDOG_TIMEOUT,
			       &hdcp_work->output);

	process_output(hdcp_work);

	mutex_unlock(&hdcp_work->mutex);

पूर्ण

अटल व्योम event_cpirq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hdcp_workqueue *hdcp_work;

	hdcp_work = container_of(work, काष्ठा hdcp_workqueue, cpirq_work);

	mutex_lock(&hdcp_work->mutex);

	mod_hdcp_process_event(&hdcp_work->hdcp, MOD_HDCP_EVENT_CPIRQ, &hdcp_work->output);

	process_output(hdcp_work);

	mutex_unlock(&hdcp_work->mutex);

पूर्ण


व्योम hdcp_destroy(काष्ठा kobject *kobj, काष्ठा hdcp_workqueue *hdcp_work)
अणु
	पूर्णांक i = 0;

	क्रम (i = 0; i < hdcp_work->max_link; i++) अणु
		cancel_delayed_work_sync(&hdcp_work[i].callback_dwork);
		cancel_delayed_work_sync(&hdcp_work[i].watchकरोg_समयr_dwork);
	पूर्ण

	sysfs_हटाओ_bin_file(kobj, &hdcp_work[0].attr);
	kमुक्त(hdcp_work->srm);
	kमुक्त(hdcp_work->srm_temp);
	kमुक्त(hdcp_work);
पूर्ण


अटल bool enable_assr(व्योम *handle, काष्ठा dc_link *link)
अणु

	काष्ठा hdcp_workqueue *hdcp_work = handle;
	काष्ठा mod_hdcp hdcp = hdcp_work->hdcp;
	काष्ठा psp_context *psp = hdcp.config.psp.handle;
	काष्ठा ta_dपंचांग_shared_memory *dपंचांग_cmd;
	bool res = true;

	अगर (!psp->dपंचांग_context.dपंचांग_initialized) अणु
		DRM_INFO("Failed to enable ASSR, DTM TA is not initialized.");
		वापस false;
	पूर्ण

	dपंचांग_cmd = (काष्ठा ta_dपंचांग_shared_memory *)psp->dपंचांग_context.dपंचांग_shared_buf;

	mutex_lock(&psp->dपंचांग_context.mutex);
	स_रखो(dपंचांग_cmd, 0, माप(काष्ठा ta_dपंचांग_shared_memory));

	dपंचांग_cmd->cmd_id = TA_DTM_COMMAND__TOPOLOGY_ASSR_ENABLE;
	dपंचांग_cmd->dपंचांग_in_message.topology_assr_enable.display_topology_dig_be_index = link->link_enc_hw_inst;
	dपंचांग_cmd->dपंचांग_status = TA_DTM_STATUS__GENERIC_FAILURE;

	psp_dपंचांग_invoke(psp, dपंचांग_cmd->cmd_id);

	अगर (dपंचांग_cmd->dपंचांग_status != TA_DTM_STATUS__SUCCESS) अणु
		DRM_INFO("Failed to enable ASSR");
		res = false;
	पूर्ण

	mutex_unlock(&psp->dपंचांग_context.mutex);

	वापस res;
पूर्ण

अटल व्योम update_config(व्योम *handle, काष्ठा cp_psp_stream_config *config)
अणु
	काष्ठा hdcp_workqueue *hdcp_work = handle;
	काष्ठा amdgpu_dm_connector *aconnector = config->dm_stream_ctx;
	पूर्णांक link_index = aconnector->dc_link->link_index;
	काष्ठा mod_hdcp_display *display = &hdcp_work[link_index].display;
	काष्ठा mod_hdcp_link *link = &hdcp_work[link_index].link;
	काष्ठा drm_connector_state *conn_state;

	अगर (config->dpms_off) अणु
		hdcp_हटाओ_display(hdcp_work, link_index, aconnector);
		वापस;
	पूर्ण

	स_रखो(display, 0, माप(*display));
	स_रखो(link, 0, माप(*link));

	display->index = aconnector->base.index;
	display->state = MOD_HDCP_DISPLAY_ACTIVE;

	अगर (aconnector->dc_sink != शून्य)
		link->mode = mod_hdcp_संकेत_type_to_operation_mode(aconnector->dc_sink->sink_संकेत);

	display->controller = CONTROLLER_ID_D0 + config->otg_inst;
	display->dig_fe = config->dig_fe;
	link->dig_be = config->dig_be;
	link->ddc_line = aconnector->dc_link->ddc_hw_inst + 1;
	link->dp.rev = aconnector->dc_link->dpcd_caps.dpcd_rev.raw;
	link->dp.assr_enabled = config->assr_enabled;
	link->dp.mst_enabled = config->mst_enabled;
	display->adjust.disable = MOD_HDCP_DISPLAY_DISABLE_AUTHENTICATION;
	link->adjust.auth_delay = 3;
	link->adjust.hdcp1.disable = 0;
	conn_state = aconnector->base.state;

	pr_debug("[HDCP_DM] display %d, CP %d, type %d\n", aconnector->base.index,
			(!!aconnector->base.state) ? aconnector->base.state->content_protection : -1,
			(!!aconnector->base.state) ? aconnector->base.state->hdcp_content_type : -1);

	hdcp_update_display(hdcp_work, link_index, aconnector, conn_state->hdcp_content_type, false);
पूर्ण


/* NOTE: From the usermodes prospective you only need to call ग_लिखो *ONCE*, the kernel
 *      will स्वतःmatically call once or twice depending on the size
 *
 * call: "cat file > /sys/class/drm/card0/device/hdcp_srm" from usermode no matter what the size is
 *
 * The kernel can only send PAGE_SIZE at once and since MAX_SRM_खाता(5120) > PAGE_SIZE(4096),
 * srm_data_ग_लिखो can be called multiple बार.
 *
 * sysfs पूर्णांकerface करोesn't tell us the size we will get so we are sending partial SRMs to psp and on
 * the last call we will send the full SRM. PSP will fail on every call beक्रमe the last.
 *
 * This means we करोn't know अगर the SRM is good until the last call. And because of this limitation we
 * cannot throw errors early as it will stop the kernel from writing to sysfs
 *
 * Example 1:
 * 	Good SRM size = 5096
 * 	first call to ग_लिखो 4096 -> PSP fails
 * 	Second call to ग_लिखो 1000 -> PSP Pass -> SRM is set
 *
 * Example 2:
 * 	Bad SRM size = 4096
 * 	first call to ग_लिखो 4096 -> PSP fails (This is the same as above, but we करोn't know अगर this
 * 	is the last call)
 *
 * Solution?:
 * 	1: Parse the SRM? -> It is चिन्हित so we करोn't know the खातापूर्ण
 * 	2: We can have another sysfs that passes the size beक्रमe calling set. -> simpler solution
 * 	below
 *
 * Easy Solution:
 * Always call get after Set to verअगरy अगर set was successful.
 * +----------------------+
 * |   Why it works:      |
 * +----------------------+
 * PSP will only update its srm अगर its older than the one we are trying to load.
 * Always करो set first than get.
 * 	-अगर we try to "1. SET" a older version PSP will reject it and we can "2. GET" the newer
 * 	version and save it
 *
 * 	-अगर we try to "1. SET" a newer version PSP will accept it and we can "2. GET" the
 * 	same(newer) version back and save it
 *
 * 	-अगर we try to "1. SET" a newer version and PSP rejects it. That means the क्रमmat is
 * 	incorrect/corrupted and we should correct our SRM by getting it from PSP
 */
अटल sमाप_प्रकार srm_data_ग_लिखो(काष्ठा file *filp, काष्ठा kobject *kobj, काष्ठा bin_attribute *bin_attr, अक्षर *buffer,
			      loff_t pos, माप_प्रकार count)
अणु
	काष्ठा hdcp_workqueue *work;
	uपूर्णांक32_t srm_version = 0;

	work = container_of(bin_attr, काष्ठा hdcp_workqueue, attr);
	link_lock(work, true);

	स_नकल(work->srm_temp + pos, buffer, count);

	अगर (!psp_set_srm(work->hdcp.config.psp.handle, work->srm_temp, pos + count, &srm_version)) अणु
		DRM_DEBUG_DRIVER("HDCP SRM SET version 0x%X", srm_version);
		स_नकल(work->srm, work->srm_temp, pos + count);
		work->srm_size = pos + count;
		work->srm_version = srm_version;
	पूर्ण


	link_lock(work, false);

	वापस count;
पूर्ण

अटल sमाप_प्रकार srm_data_पढ़ो(काष्ठा file *filp, काष्ठा kobject *kobj, काष्ठा bin_attribute *bin_attr, अक्षर *buffer,
			     loff_t pos, माप_प्रकार count)
अणु
	काष्ठा hdcp_workqueue *work;
	uपूर्णांक8_t *srm = शून्य;
	uपूर्णांक32_t srm_version;
	uपूर्णांक32_t srm_size;
	माप_प्रकार ret = count;

	work = container_of(bin_attr, काष्ठा hdcp_workqueue, attr);

	link_lock(work, true);

	srm = psp_get_srm(work->hdcp.config.psp.handle, &srm_version, &srm_size);

	अगर (!srm) अणु
		ret = -EINVAL;
		जाओ ret;
	पूर्ण

	अगर (pos >= srm_size)
		ret = 0;

	अगर (srm_size - pos < count) अणु
		स_नकल(buffer, srm + pos, srm_size - pos);
		ret = srm_size - pos;
		जाओ ret;
	पूर्ण

	स_नकल(buffer, srm + pos, count);

ret:
	link_lock(work, false);
	वापस ret;
पूर्ण

/* From the hdcp spec (5.Renewability) SRM needs to be stored in a non-अस्थिर memory.
 *
 * For example,
 * 	अगर Application "A" sets the SRM (ver 2) and we reboot/suspend and later when Application "B"
 * 	needs to use HDCP, the version in PSP should be SRM(ver 2). So SRM should be persistent
 * 	across boot/reboots/suspend/resume/shutकरोwn
 *
 * Currently when the प्रणाली goes करोwn (suspend/shutकरोwn) the SRM is cleared from PSP. For HDCP we need
 * to make the SRM persistent.
 *
 * -PSP owns the checking of SRM but करोesn't have the ability to store it in a non-अस्थिर memory.
 * -The kernel cannot ग_लिखो to the file प्रणालीs.
 * -So we need usermode to करो this क्रम us, which is why an पूर्णांकerface क्रम usermode is needed
 *
 *
 *
 * Usermode can पढ़ो/ग_लिखो to/from PSP using the sysfs पूर्णांकerface
 * For example:
 * 	to save SRM from PSP to storage : cat /sys/class/drm/card0/device/hdcp_srm > srmfile
 * 	to load from storage to PSP: cat srmfile > /sys/class/drm/card0/device/hdcp_srm
 */
अटल स्थिर काष्ठा bin_attribute data_attr = अणु
	.attr = अणु.name = "hdcp_srm", .mode = 0664पूर्ण,
	.size = PSP_HDCP_SRM_FIRST_GEN_MAX_SIZE, /* Limit SRM size */
	.ग_लिखो = srm_data_ग_लिखो,
	.पढ़ो = srm_data_पढ़ो,
पूर्ण;


काष्ठा hdcp_workqueue *hdcp_create_workqueue(काष्ठा amdgpu_device *adev, काष्ठा cp_psp *cp_psp, काष्ठा dc *dc)
अणु

	पूर्णांक max_caps = dc->caps.max_links;
	काष्ठा hdcp_workqueue *hdcp_work;
	पूर्णांक i = 0;

	hdcp_work = kसुस्मृति(max_caps, माप(*hdcp_work), GFP_KERNEL);
	अगर (ZERO_OR_शून्य_PTR(hdcp_work))
		वापस शून्य;

	hdcp_work->srm = kसुस्मृति(PSP_HDCP_SRM_FIRST_GEN_MAX_SIZE, माप(*hdcp_work->srm), GFP_KERNEL);

	अगर (hdcp_work->srm == शून्य)
		जाओ fail_alloc_context;

	hdcp_work->srm_temp = kसुस्मृति(PSP_HDCP_SRM_FIRST_GEN_MAX_SIZE, माप(*hdcp_work->srm_temp), GFP_KERNEL);

	अगर (hdcp_work->srm_temp == शून्य)
		जाओ fail_alloc_context;

	hdcp_work->max_link = max_caps;

	क्रम (i = 0; i < max_caps; i++) अणु
		mutex_init(&hdcp_work[i].mutex);

		INIT_WORK(&hdcp_work[i].cpirq_work, event_cpirq);
		INIT_WORK(&hdcp_work[i].property_update_work, event_property_update);
		INIT_DELAYED_WORK(&hdcp_work[i].callback_dwork, event_callback);
		INIT_DELAYED_WORK(&hdcp_work[i].watchकरोg_समयr_dwork, event_watchकरोg_समयr);
		INIT_DELAYED_WORK(&hdcp_work[i].property_validate_dwork, event_property_validate);

		hdcp_work[i].hdcp.config.psp.handle = &adev->psp;
		hdcp_work[i].hdcp.config.ddc.handle = dc_get_link_at_index(dc, i);
		hdcp_work[i].hdcp.config.ddc.funcs.ग_लिखो_i2c = lp_ग_लिखो_i2c;
		hdcp_work[i].hdcp.config.ddc.funcs.पढ़ो_i2c = lp_पढ़ो_i2c;
		hdcp_work[i].hdcp.config.ddc.funcs.ग_लिखो_dpcd = lp_ग_लिखो_dpcd;
		hdcp_work[i].hdcp.config.ddc.funcs.पढ़ो_dpcd = lp_पढ़ो_dpcd;
	पूर्ण

	cp_psp->funcs.update_stream_config = update_config;
	cp_psp->funcs.enable_assr = enable_assr;
	cp_psp->handle = hdcp_work;

	/* File created at /sys/class/drm/card0/device/hdcp_srm*/
	hdcp_work[0].attr = data_attr;
	sysfs_bin_attr_init(&hdcp_work[0].attr);

	अगर (sysfs_create_bin_file(&adev->dev->kobj, &hdcp_work[0].attr))
		DRM_WARN("Failed to create device file hdcp_srm");

	वापस hdcp_work;

fail_alloc_context:
	kमुक्त(hdcp_work->srm);
	kमुक्त(hdcp_work->srm_temp);
	kमुक्त(hdcp_work);

	वापस शून्य;



पूर्ण



