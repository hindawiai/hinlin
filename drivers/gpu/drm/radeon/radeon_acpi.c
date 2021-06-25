<शैली गुरु>
/*
 * Copyright 2012 Advanced Micro Devices, Inc.
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
 */

#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/slab.h>

#समावेश <acpi/acpi_bus.h>
#समावेश <acpi/video.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_acpi.h"
#समावेश "radeon_pm.h"

#अगर defined(CONFIG_VGA_SWITCHEROO)
bool radeon_atpx_dgpu_req_घातer_क्रम_displays(व्योम);
#अन्यथा
अटल अंतरभूत bool radeon_atpx_dgpu_req_घातer_क्रम_displays(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#घोषणा ACPI_AC_CLASS           "ac_adapter"

काष्ठा atअगर_verअगरy_पूर्णांकerface अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 version;		/* version */
	u32 notअगरication_mask;	/* supported notअगरications mask */
	u32 function_bits;	/* supported functions bit vector */
पूर्ण __packed;

काष्ठा atअगर_प्रणाली_params अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u32 valid_mask;		/* valid flags mask */
	u32 flags;		/* flags */
	u8 command_code;	/* notअगरy command code */
पूर्ण __packed;

काष्ठा atअगर_sbios_requests अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u32 pending;		/* pending sbios requests */
	u8 panel_exp_mode;	/* panel expansion mode */
	u8 thermal_gfx;		/* thermal state: target gfx controller */
	u8 thermal_state;	/* thermal state: state id (0: निकास state, non-0: state) */
	u8 क्रमced_घातer_gfx;	/* क्रमced घातer state: target gfx controller */
	u8 क्रमced_घातer_state;	/* क्रमced घातer state: state id */
	u8 प्रणाली_घातer_src;	/* प्रणाली घातer source */
	u8 backlight_level;	/* panel backlight level (0-255) */
पूर्ण __packed;

#घोषणा ATIF_NOTIFY_MASK	0x3
#घोषणा ATIF_NOTIFY_NONE	0
#घोषणा ATIF_NOTIFY_81		1
#घोषणा ATIF_NOTIFY_N		2

काष्ठा atcs_verअगरy_पूर्णांकerface अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 version;		/* version */
	u32 function_bits;	/* supported functions bit vector */
पूर्ण __packed;

#घोषणा ATCS_VALID_FLAGS_MASK	0x3

काष्ठा atcs_pref_req_input अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 client_id;		/* client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	u16 valid_flags_mask;	/* valid flags mask */
	u16 flags;		/* flags */
	u8 req_type;		/* request type */
	u8 perf_req;		/* perक्रमmance request */
पूर्ण __packed;

काष्ठा atcs_pref_req_output अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u8 ret_val;		/* वापस value */
पूर्ण __packed;

/* Call the ATIF method
 */
/**
 * radeon_atअगर_call - call an ATIF method
 *
 * @handle: acpi handle
 * @function: the ATIF function to execute
 * @params: ATIF function params
 *
 * Executes the requested ATIF function (all asics).
 * Returns a poपूर्णांकer to the acpi output buffer.
 */
अटल जोड़ acpi_object *radeon_atअगर_call(acpi_handle handle, पूर्णांक function,
		काष्ठा acpi_buffer *params)
अणु
	acpi_status status;
	जोड़ acpi_object atअगर_arg_elements[2];
	काष्ठा acpi_object_list atअगर_arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	atअगर_arg.count = 2;
	atअगर_arg.poपूर्णांकer = &atअगर_arg_elements[0];

	atअगर_arg_elements[0].type = ACPI_TYPE_INTEGER;
	atअगर_arg_elements[0].पूर्णांकeger.value = function;

	अगर (params) अणु
		atअगर_arg_elements[1].type = ACPI_TYPE_BUFFER;
		atअगर_arg_elements[1].buffer.length = params->length;
		atअगर_arg_elements[1].buffer.poपूर्णांकer = params->poपूर्णांकer;
	पूर्ण अन्यथा अणु
		/* We need a second fake parameter */
		atअगर_arg_elements[1].type = ACPI_TYPE_INTEGER;
		atअगर_arg_elements[1].पूर्णांकeger.value = 0;
	पूर्ण

	status = acpi_evaluate_object(handle, "ATIF", &atअगर_arg, &buffer);

	/* Fail only अगर calling the method fails and ATIF is supported */
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		DRM_DEBUG_DRIVER("failed to evaluate ATIF got %s\n",
				 acpi_क्रमmat_exception(status));
		kमुक्त(buffer.poपूर्णांकer);
		वापस शून्य;
	पूर्ण

	वापस buffer.poपूर्णांकer;
पूर्ण

/**
 * radeon_atअगर_parse_notअगरication - parse supported notअगरications
 *
 * @n: supported notअगरications काष्ठा
 * @mask: supported notअगरications mask from ATIF
 *
 * Use the supported notअगरications mask from ATIF function
 * ATIF_FUNCTION_VERIFY_INTERFACE to determine what notअगरications
 * are supported (all asics).
 */
अटल व्योम radeon_atअगर_parse_notअगरication(काष्ठा radeon_atअगर_notअगरications *n, u32 mask)
अणु
	n->display_चयन = mask & ATIF_DISPLAY_SWITCH_REQUEST_SUPPORTED;
	n->expansion_mode_change = mask & ATIF_EXPANSION_MODE_CHANGE_REQUEST_SUPPORTED;
	n->thermal_state = mask & ATIF_THERMAL_STATE_CHANGE_REQUEST_SUPPORTED;
	n->क्रमced_घातer_state = mask & ATIF_FORCED_POWER_STATE_CHANGE_REQUEST_SUPPORTED;
	n->प्रणाली_घातer_state = mask & ATIF_SYSTEM_POWER_SOURCE_CHANGE_REQUEST_SUPPORTED;
	n->display_conf_change = mask & ATIF_DISPLAY_CONF_CHANGE_REQUEST_SUPPORTED;
	n->px_gfx_चयन = mask & ATIF_PX_GFX_SWITCH_REQUEST_SUPPORTED;
	n->brightness_change = mask & ATIF_PANEL_BRIGHTNESS_CHANGE_REQUEST_SUPPORTED;
	n->dgpu_display_event = mask & ATIF_DGPU_DISPLAY_EVENT_SUPPORTED;
पूर्ण

/**
 * radeon_atअगर_parse_functions - parse supported functions
 *
 * @f: supported functions काष्ठा
 * @mask: supported functions mask from ATIF
 *
 * Use the supported functions mask from ATIF function
 * ATIF_FUNCTION_VERIFY_INTERFACE to determine what functions
 * are supported (all asics).
 */
अटल व्योम radeon_atअगर_parse_functions(काष्ठा radeon_atअगर_functions *f, u32 mask)
अणु
	f->प्रणाली_params = mask & ATIF_GET_SYSTEM_PARAMETERS_SUPPORTED;
	f->sbios_requests = mask & ATIF_GET_SYSTEM_BIOS_REQUESTS_SUPPORTED;
	f->select_active_disp = mask & ATIF_SELECT_ACTIVE_DISPLAYS_SUPPORTED;
	f->lid_state = mask & ATIF_GET_LID_STATE_SUPPORTED;
	f->get_tv_standard = mask & ATIF_GET_TV_STANDARD_FROM_CMOS_SUPPORTED;
	f->set_tv_standard = mask & ATIF_SET_TV_STANDARD_IN_CMOS_SUPPORTED;
	f->get_panel_expansion_mode = mask & ATIF_GET_PANEL_EXPANSION_MODE_FROM_CMOS_SUPPORTED;
	f->set_panel_expansion_mode = mask & ATIF_SET_PANEL_EXPANSION_MODE_IN_CMOS_SUPPORTED;
	f->temperature_change = mask & ATIF_TEMPERATURE_CHANGE_NOTIFICATION_SUPPORTED;
	f->graphics_device_types = mask & ATIF_GET_GRAPHICS_DEVICE_TYPES_SUPPORTED;
पूर्ण

/**
 * radeon_atअगर_verअगरy_पूर्णांकerface - verअगरy ATIF
 *
 * @handle: acpi handle
 * @atअगर: radeon atअगर काष्ठा
 *
 * Execute the ATIF_FUNCTION_VERIFY_INTERFACE ATIF function
 * to initialize ATIF and determine what features are supported
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
अटल पूर्णांक radeon_atअगर_verअगरy_पूर्णांकerface(acpi_handle handle,
		काष्ठा radeon_atअगर *atअगर)
अणु
	जोड़ acpi_object *info;
	काष्ठा atअगर_verअगरy_पूर्णांकerface output;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = radeon_atअगर_call(handle, ATIF_FUNCTION_VERIFY_INTERFACE, शून्य);
	अगर (!info)
		वापस -EIO;

	स_रखो(&output, 0, माप(output));

	size = *(u16 *) info->buffer.poपूर्णांकer;
	अगर (size < 12) अणु
		DRM_INFO("ATIF buffer is too small: %zu\n", size);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	size = min(माप(output), size);

	स_नकल(&output, info->buffer.poपूर्णांकer, size);

	/* TODO: check version? */
	DRM_DEBUG_DRIVER("ATIF version %u\n", output.version);

	radeon_atअगर_parse_notअगरication(&atअगर->notअगरications, output.notअगरication_mask);
	radeon_atअगर_parse_functions(&atअगर->functions, output.function_bits);

out:
	kमुक्त(info);
	वापस err;
पूर्ण

/**
 * radeon_atअगर_get_notअगरication_params - determine notअगरy configuration
 *
 * @handle: acpi handle
 * @n: atअगर notअगरication configuration काष्ठा
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_PARAMETERS ATIF function
 * to determine अगर a notअगरier is used and अगर so which one
 * (all asics).  This is either Notअगरy(VGA, 0x81) or Notअगरy(VGA, n)
 * where n is specअगरied in the result अगर a notअगरier is used.
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक radeon_atअगर_get_notअगरication_params(acpi_handle handle,
		काष्ठा radeon_atअगर_notअगरication_cfg *n)
अणु
	जोड़ acpi_object *info;
	काष्ठा atअगर_प्रणाली_params params;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = radeon_atअगर_call(handle, ATIF_FUNCTION_GET_SYSTEM_PARAMETERS, शून्य);
	अगर (!info) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	size = *(u16 *) info->buffer.poपूर्णांकer;
	अगर (size < 10) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	size = min(माप(params), size);
	स_नकल(&params, info->buffer.poपूर्णांकer, size);

	DRM_DEBUG_DRIVER("SYSTEM_PARAMS: mask = %#x, flags = %#x\n",
			params.flags, params.valid_mask);
	params.flags = params.flags & params.valid_mask;

	अगर ((params.flags & ATIF_NOTIFY_MASK) == ATIF_NOTIFY_NONE) अणु
		n->enabled = false;
		n->command_code = 0;
	पूर्ण अन्यथा अगर ((params.flags & ATIF_NOTIFY_MASK) == ATIF_NOTIFY_81) अणु
		n->enabled = true;
		n->command_code = 0x81;
	पूर्ण अन्यथा अणु
		अगर (size < 11) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		n->enabled = true;
		n->command_code = params.command_code;
	पूर्ण

out:
	DRM_DEBUG_DRIVER("Notification %s, command code = %#x\n",
			(n->enabled ? "enabled" : "disabled"),
			n->command_code);
	kमुक्त(info);
	वापस err;
पूर्ण

/**
 * radeon_atअगर_get_sbios_requests - get requested sbios event
 *
 * @handle: acpi handle
 * @req: atअगर sbios request काष्ठा
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS ATIF function
 * to determine what requests the sbios is making to the driver
 * (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक radeon_atअगर_get_sbios_requests(acpi_handle handle,
		काष्ठा atअगर_sbios_requests *req)
अणु
	जोड़ acpi_object *info;
	माप_प्रकार size;
	पूर्णांक count = 0;

	info = radeon_atअगर_call(handle, ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS, शून्य);
	अगर (!info)
		वापस -EIO;

	size = *(u16 *)info->buffer.poपूर्णांकer;
	अगर (size < 0xd) अणु
		count = -EINVAL;
		जाओ out;
	पूर्ण
	स_रखो(req, 0, माप(*req));

	size = min(माप(*req), size);
	स_नकल(req, info->buffer.poपूर्णांकer, size);
	DRM_DEBUG_DRIVER("SBIOS pending requests: %#x\n", req->pending);

	count = hweight32(req->pending);

out:
	kमुक्त(info);
	वापस count;
पूर्ण

/**
 * radeon_atअगर_handler - handle ATIF notअगरy requests
 *
 * @rdev: radeon_device poपूर्णांकer
 * @event: atअगर sbios request काष्ठा
 *
 * Checks the acpi event and अगर it matches an atअगर event,
 * handles it.
 * Returns NOTIFY code
 */
अटल पूर्णांक radeon_atअगर_handler(काष्ठा radeon_device *rdev,
		काष्ठा acpi_bus_event *event)
अणु
	काष्ठा radeon_atअगर *atअगर = &rdev->atअगर;
	काष्ठा atअगर_sbios_requests req;
	acpi_handle handle;
	पूर्णांक count;

	DRM_DEBUG_DRIVER("event, device_class = %s, type = %#x\n",
			event->device_class, event->type);

	अगर (म_भेद(event->device_class, ACPI_VIDEO_CLASS) != 0)
		वापस NOTIFY_DONE;

	अगर (!atअगर->notअगरication_cfg.enabled ||
			event->type != atअगर->notअगरication_cfg.command_code)
		/* Not our event */
		वापस NOTIFY_DONE;

	/* Check pending SBIOS requests */
	handle = ACPI_HANDLE(&rdev->pdev->dev);
	count = radeon_atअगर_get_sbios_requests(handle, &req);

	अगर (count <= 0)
		वापस NOTIFY_DONE;

	DRM_DEBUG_DRIVER("ATIF: %d pending SBIOS requests\n", count);

	अगर (req.pending & ATIF_PANEL_BRIGHTNESS_CHANGE_REQUEST) अणु
		काष्ठा radeon_encoder *enc = atअगर->encoder_क्रम_bl;

		अगर (enc) अणु
			DRM_DEBUG_DRIVER("Changing brightness to %d\n",
					req.backlight_level);

			radeon_set_backlight_level(rdev, enc, req.backlight_level);

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)
			अगर (rdev->is_atom_bios) अणु
				काष्ठा radeon_encoder_atom_dig *dig = enc->enc_priv;
				backlight_क्रमce_update(dig->bl_dev,
						       BACKLIGHT_UPDATE_HOTKEY);
			पूर्ण अन्यथा अणु
				काष्ठा radeon_encoder_lvds *dig = enc->enc_priv;
				backlight_क्रमce_update(dig->bl_dev,
						       BACKLIGHT_UPDATE_HOTKEY);
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण
	अगर (req.pending & ATIF_DGPU_DISPLAY_EVENT) अणु
		अगर ((rdev->flags & RADEON_IS_PX) &&
		    radeon_atpx_dgpu_req_घातer_क्रम_displays()) अणु
			pm_runसमय_get_sync(rdev->ddev->dev);
			/* Just fire off a uevent and let userspace tell us what to करो */
			drm_helper_hpd_irq_event(rdev->ddev);
			pm_runसमय_mark_last_busy(rdev->ddev->dev);
			pm_runसमय_put_स्वतःsuspend(rdev->ddev->dev);
		पूर्ण
	पूर्ण
	/* TODO: check other events */

	/* We've handled the event, stop the notअगरier chain. The ACPI पूर्णांकerface
	 * overloads ACPI_VIDEO_NOTIFY_PROBE, we करोn't want to send that to
	 * userspace अगर the event was generated only to संकेत a SBIOS
	 * request.
	 */
	वापस NOTIFY_BAD;
पूर्ण

/* Call the ATCS method
 */
/**
 * radeon_atcs_call - call an ATCS method
 *
 * @handle: acpi handle
 * @function: the ATCS function to execute
 * @params: ATCS function params
 *
 * Executes the requested ATCS function (all asics).
 * Returns a poपूर्णांकer to the acpi output buffer.
 */
अटल जोड़ acpi_object *radeon_atcs_call(acpi_handle handle, पूर्णांक function,
					   काष्ठा acpi_buffer *params)
अणु
	acpi_status status;
	जोड़ acpi_object atcs_arg_elements[2];
	काष्ठा acpi_object_list atcs_arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	atcs_arg.count = 2;
	atcs_arg.poपूर्णांकer = &atcs_arg_elements[0];

	atcs_arg_elements[0].type = ACPI_TYPE_INTEGER;
	atcs_arg_elements[0].पूर्णांकeger.value = function;

	अगर (params) अणु
		atcs_arg_elements[1].type = ACPI_TYPE_BUFFER;
		atcs_arg_elements[1].buffer.length = params->length;
		atcs_arg_elements[1].buffer.poपूर्णांकer = params->poपूर्णांकer;
	पूर्ण अन्यथा अणु
		/* We need a second fake parameter */
		atcs_arg_elements[1].type = ACPI_TYPE_INTEGER;
		atcs_arg_elements[1].पूर्णांकeger.value = 0;
	पूर्ण

	status = acpi_evaluate_object(handle, "ATCS", &atcs_arg, &buffer);

	/* Fail only अगर calling the method fails and ATIF is supported */
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		DRM_DEBUG_DRIVER("failed to evaluate ATCS got %s\n",
				 acpi_क्रमmat_exception(status));
		kमुक्त(buffer.poपूर्णांकer);
		वापस शून्य;
	पूर्ण

	वापस buffer.poपूर्णांकer;
पूर्ण

/**
 * radeon_atcs_parse_functions - parse supported functions
 *
 * @f: supported functions काष्ठा
 * @mask: supported functions mask from ATCS
 *
 * Use the supported functions mask from ATCS function
 * ATCS_FUNCTION_VERIFY_INTERFACE to determine what functions
 * are supported (all asics).
 */
अटल व्योम radeon_atcs_parse_functions(काष्ठा radeon_atcs_functions *f, u32 mask)
अणु
	f->get_ext_state = mask & ATCS_GET_EXTERNAL_STATE_SUPPORTED;
	f->pcie_perf_req = mask & ATCS_PCIE_PERFORMANCE_REQUEST_SUPPORTED;
	f->pcie_dev_rdy = mask & ATCS_PCIE_DEVICE_READY_NOTIFICATION_SUPPORTED;
	f->pcie_bus_width = mask & ATCS_SET_PCIE_BUS_WIDTH_SUPPORTED;
पूर्ण

/**
 * radeon_atcs_verअगरy_पूर्णांकerface - verअगरy ATCS
 *
 * @handle: acpi handle
 * @atcs: radeon atcs काष्ठा
 *
 * Execute the ATCS_FUNCTION_VERIFY_INTERFACE ATCS function
 * to initialize ATCS and determine what features are supported
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
अटल पूर्णांक radeon_atcs_verअगरy_पूर्णांकerface(acpi_handle handle,
					काष्ठा radeon_atcs *atcs)
अणु
	जोड़ acpi_object *info;
	काष्ठा atcs_verअगरy_पूर्णांकerface output;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = radeon_atcs_call(handle, ATCS_FUNCTION_VERIFY_INTERFACE, शून्य);
	अगर (!info)
		वापस -EIO;

	स_रखो(&output, 0, माप(output));

	size = *(u16 *) info->buffer.poपूर्णांकer;
	अगर (size < 8) अणु
		DRM_INFO("ATCS buffer is too small: %zu\n", size);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	size = min(माप(output), size);

	स_नकल(&output, info->buffer.poपूर्णांकer, size);

	/* TODO: check version? */
	DRM_DEBUG_DRIVER("ATCS version %u\n", output.version);

	radeon_atcs_parse_functions(&atcs->functions, output.function_bits);

out:
	kमुक्त(info);
	वापस err;
पूर्ण

/**
 * radeon_acpi_is_pcie_perक्रमmance_request_supported
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Check अगर the ATCS pcie_perf_req and pcie_dev_rdy methods
 * are supported (all asics).
 * वापसs true अगर supported, false अगर not.
 */
bool radeon_acpi_is_pcie_perक्रमmance_request_supported(काष्ठा radeon_device *rdev)
अणु
	काष्ठा radeon_atcs *atcs = &rdev->atcs;

	अगर (atcs->functions.pcie_perf_req && atcs->functions.pcie_dev_rdy)
		वापस true;

	वापस false;
पूर्ण

/**
 * radeon_acpi_pcie_notअगरy_device_पढ़ोy
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Executes the PCIE_DEVICE_READY_NOTIFICATION method
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
पूर्णांक radeon_acpi_pcie_notअगरy_device_पढ़ोy(काष्ठा radeon_device *rdev)
अणु
	acpi_handle handle;
	जोड़ acpi_object *info;
	काष्ठा radeon_atcs *atcs = &rdev->atcs;

	/* Get the device handle */
	handle = ACPI_HANDLE(&rdev->pdev->dev);
	अगर (!handle)
		वापस -EINVAL;

	अगर (!atcs->functions.pcie_dev_rdy)
		वापस -EINVAL;

	info = radeon_atcs_call(handle, ATCS_FUNCTION_PCIE_DEVICE_READY_NOTIFICATION, शून्य);
	अगर (!info)
		वापस -EIO;

	kमुक्त(info);

	वापस 0;
पूर्ण

/**
 * radeon_acpi_pcie_perक्रमmance_request
 *
 * @rdev: radeon_device poपूर्णांकer
 * @perf_req: requested perf level (pcie gen speed)
 * @advertise: set advertise caps flag अगर set
 *
 * Executes the PCIE_PERFORMANCE_REQUEST method to
 * change the pcie gen speed (all asics).
 * वापसs 0 on success, error on failure.
 */
पूर्णांक radeon_acpi_pcie_perक्रमmance_request(काष्ठा radeon_device *rdev,
					 u8 perf_req, bool advertise)
अणु
	acpi_handle handle;
	जोड़ acpi_object *info;
	काष्ठा radeon_atcs *atcs = &rdev->atcs;
	काष्ठा atcs_pref_req_input atcs_input;
	काष्ठा atcs_pref_req_output atcs_output;
	काष्ठा acpi_buffer params;
	माप_प्रकार size;
	u32 retry = 3;

	/* Get the device handle */
	handle = ACPI_HANDLE(&rdev->pdev->dev);
	अगर (!handle)
		वापस -EINVAL;

	अगर (!atcs->functions.pcie_perf_req)
		वापस -EINVAL;

	atcs_input.size = माप(काष्ठा atcs_pref_req_input);
	/* client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	atcs_input.client_id = rdev->pdev->devfn | (rdev->pdev->bus->number << 8);
	atcs_input.valid_flags_mask = ATCS_VALID_FLAGS_MASK;
	atcs_input.flags = ATCS_WAIT_FOR_COMPLETION;
	अगर (advertise)
		atcs_input.flags |= ATCS_ADVERTISE_CAPS;
	atcs_input.req_type = ATCS_PCIE_LINK_SPEED;
	atcs_input.perf_req = perf_req;

	params.length = माप(काष्ठा atcs_pref_req_input);
	params.poपूर्णांकer = &atcs_input;

	जबतक (retry--) अणु
		info = radeon_atcs_call(handle, ATCS_FUNCTION_PCIE_PERFORMANCE_REQUEST, &params);
		अगर (!info)
			वापस -EIO;

		स_रखो(&atcs_output, 0, माप(atcs_output));

		size = *(u16 *) info->buffer.poपूर्णांकer;
		अगर (size < 3) अणु
			DRM_INFO("ATCS buffer is too small: %zu\n", size);
			kमुक्त(info);
			वापस -EINVAL;
		पूर्ण
		size = min(माप(atcs_output), size);

		स_नकल(&atcs_output, info->buffer.poपूर्णांकer, size);

		kमुक्त(info);

		चयन (atcs_output.ret_val) अणु
		हाल ATCS_REQUEST_REFUSED:
		शेष:
			वापस -EINVAL;
		हाल ATCS_REQUEST_COMPLETE:
			वापस 0;
		हाल ATCS_REQUEST_IN_PROGRESS:
			udelay(10);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * radeon_acpi_event - handle notअगरy events
 *
 * @nb: notअगरier block
 * @val: val
 * @data: acpi event
 *
 * Calls relevant radeon functions in response to various
 * acpi events.
 * Returns NOTIFY code
 */
अटल पूर्णांक radeon_acpi_event(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ val,
			     व्योम *data)
अणु
	काष्ठा radeon_device *rdev = container_of(nb, काष्ठा radeon_device, acpi_nb);
	काष्ठा acpi_bus_event *entry = (काष्ठा acpi_bus_event *)data;

	अगर (म_भेद(entry->device_class, ACPI_AC_CLASS) == 0) अणु
		अगर (घातer_supply_is_प्रणाली_supplied() > 0)
			DRM_DEBUG_DRIVER("pm: AC\n");
		अन्यथा
			DRM_DEBUG_DRIVER("pm: DC\n");

		radeon_pm_acpi_event_handler(rdev);
	पूर्ण

	/* Check क्रम pending SBIOS requests */
	वापस radeon_atअगर_handler(rdev, entry);
पूर्ण

/* Call all ACPI methods here */
/**
 * radeon_acpi_init - init driver acpi support
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Verअगरies the AMD ACPI पूर्णांकerfaces and रेजिस्टरs with the acpi
 * notअगरier chain (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक radeon_acpi_init(काष्ठा radeon_device *rdev)
अणु
	acpi_handle handle;
	काष्ठा radeon_atअगर *atअगर = &rdev->atअगर;
	काष्ठा radeon_atcs *atcs = &rdev->atcs;
	पूर्णांक ret;

	/* Get the device handle */
	handle = ACPI_HANDLE(&rdev->pdev->dev);

	/* No need to proceed अगर we're sure that ATIF is not supported */
	अगर (!ASIC_IS_AVIVO(rdev) || !rdev->bios || !handle)
		वापस 0;

	/* Call the ATCS method */
	ret = radeon_atcs_verअगरy_पूर्णांकerface(handle, atcs);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Call to ATCS verify_interface failed: %d\n", ret);
	पूर्ण

	/* Call the ATIF method */
	ret = radeon_atअगर_verअगरy_पूर्णांकerface(handle, atअगर);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Call to ATIF verify_interface failed: %d\n", ret);
		जाओ out;
	पूर्ण

	अगर (atअगर->notअगरications.brightness_change) अणु
		काष्ठा drm_encoder *पंचांगp;
		काष्ठा radeon_encoder *target = शून्य;

		/* Find the encoder controlling the brightness */
		list_क्रम_each_entry(पंचांगp, &rdev->ddev->mode_config.encoder_list,
				head) अणु
			काष्ठा radeon_encoder *enc = to_radeon_encoder(पंचांगp);

			अगर ((enc->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
			    enc->enc_priv) अणु
				अगर (rdev->is_atom_bios) अणु
					काष्ठा radeon_encoder_atom_dig *dig = enc->enc_priv;
					अगर (dig->bl_dev) अणु
						target = enc;
						अवरोध;
					पूर्ण
				पूर्ण अन्यथा अणु
					काष्ठा radeon_encoder_lvds *dig = enc->enc_priv;
					अगर (dig->bl_dev) अणु
						target = enc;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		atअगर->encoder_क्रम_bl = target;
	पूर्ण

	अगर (atअगर->functions.sbios_requests && !atअगर->functions.प्रणाली_params) अणु
		/* XXX check this workraround, अगर sbios request function is
		 * present we have to see how it's configured in the प्रणाली
		 * params
		 */
		atअगर->functions.प्रणाली_params = true;
	पूर्ण

	अगर (atअगर->functions.प्रणाली_params) अणु
		ret = radeon_atअगर_get_notअगरication_params(handle,
				&atअगर->notअगरication_cfg);
		अगर (ret) अणु
			DRM_DEBUG_DRIVER("Call to GET_SYSTEM_PARAMS failed: %d\n",
					ret);
			/* Disable notअगरication */
			atअगर->notअगरication_cfg.enabled = false;
		पूर्ण
	पूर्ण

out:
	rdev->acpi_nb.notअगरier_call = radeon_acpi_event;
	रेजिस्टर_acpi_notअगरier(&rdev->acpi_nb);

	वापस ret;
पूर्ण

/**
 * radeon_acpi_fini - tear करोwn driver acpi support
 *
 * @rdev: radeon_device poपूर्णांकer
 *
 * Unरेजिस्टरs with the acpi notअगरier chain (all asics).
 */
व्योम radeon_acpi_fini(काष्ठा radeon_device *rdev)
अणु
	unरेजिस्टर_acpi_notअगरier(&rdev->acpi_nb);
पूर्ण
