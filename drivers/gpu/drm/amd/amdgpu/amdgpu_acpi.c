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

#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <acpi/video.h>
#समावेश <acpi/actbl.h>

#समावेश <drm/drm_crtc_helper.h>
#समावेश "amdgpu.h"
#समावेश "amdgpu_pm.h"
#समावेश "amdgpu_display.h"
#समावेश "amd_acpi.h"
#समावेश "atom.h"

काष्ठा amdgpu_atअगर_notअगरication_cfg अणु
	bool enabled;
	पूर्णांक command_code;
पूर्ण;

काष्ठा amdgpu_atअगर_notअगरications अणु
	bool thermal_state;
	bool क्रमced_घातer_state;
	bool प्रणाली_घातer_state;
	bool brightness_change;
	bool dgpu_display_event;
	bool gpu_package_घातer_limit;
पूर्ण;

काष्ठा amdgpu_atअगर_functions अणु
	bool प्रणाली_params;
	bool sbios_requests;
	bool temperature_change;
	bool query_backlight_transfer_अक्षरacteristics;
	bool पढ़ोy_to_unकरोck;
	bool बाह्यal_gpu_inक्रमmation;
पूर्ण;

काष्ठा amdgpu_atअगर अणु
	acpi_handle handle;

	काष्ठा amdgpu_atअगर_notअगरications notअगरications;
	काष्ठा amdgpu_atअगर_functions functions;
	काष्ठा amdgpu_atअगर_notअगरication_cfg notअगरication_cfg;
#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)
	काष्ठा backlight_device *bd;
#पूर्ण_अगर
	काष्ठा amdgpu_dm_backlight_caps backlight_caps;
पूर्ण;

/* Call the ATIF method
 */
/**
 * amdgpu_atअगर_call - call an ATIF method
 *
 * @handle: acpi handle
 * @function: the ATIF function to execute
 * @params: ATIF function params
 *
 * Executes the requested ATIF function (all asics).
 * Returns a poपूर्णांकer to the acpi output buffer.
 */
अटल जोड़ acpi_object *amdgpu_atअगर_call(काष्ठा amdgpu_atअगर *atअगर,
					   पूर्णांक function,
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

	status = acpi_evaluate_object(atअगर->handle, शून्य, &atअगर_arg,
				      &buffer);

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
 * amdgpu_atअगर_parse_notअगरication - parse supported notअगरications
 *
 * @n: supported notअगरications काष्ठा
 * @mask: supported notअगरications mask from ATIF
 *
 * Use the supported notअगरications mask from ATIF function
 * ATIF_FUNCTION_VERIFY_INTERFACE to determine what notअगरications
 * are supported (all asics).
 */
अटल व्योम amdgpu_atअगर_parse_notअगरication(काष्ठा amdgpu_atअगर_notअगरications *n, u32 mask)
अणु
	n->thermal_state = mask & ATIF_THERMAL_STATE_CHANGE_REQUEST_SUPPORTED;
	n->क्रमced_घातer_state = mask & ATIF_FORCED_POWER_STATE_CHANGE_REQUEST_SUPPORTED;
	n->प्रणाली_घातer_state = mask & ATIF_SYSTEM_POWER_SOURCE_CHANGE_REQUEST_SUPPORTED;
	n->brightness_change = mask & ATIF_PANEL_BRIGHTNESS_CHANGE_REQUEST_SUPPORTED;
	n->dgpu_display_event = mask & ATIF_DGPU_DISPLAY_EVENT_SUPPORTED;
	n->gpu_package_घातer_limit = mask & ATIF_GPU_PACKAGE_POWER_LIMIT_REQUEST_SUPPORTED;
पूर्ण

/**
 * amdgpu_atअगर_parse_functions - parse supported functions
 *
 * @f: supported functions काष्ठा
 * @mask: supported functions mask from ATIF
 *
 * Use the supported functions mask from ATIF function
 * ATIF_FUNCTION_VERIFY_INTERFACE to determine what functions
 * are supported (all asics).
 */
अटल व्योम amdgpu_atअगर_parse_functions(काष्ठा amdgpu_atअगर_functions *f, u32 mask)
अणु
	f->प्रणाली_params = mask & ATIF_GET_SYSTEM_PARAMETERS_SUPPORTED;
	f->sbios_requests = mask & ATIF_GET_SYSTEM_BIOS_REQUESTS_SUPPORTED;
	f->temperature_change = mask & ATIF_TEMPERATURE_CHANGE_NOTIFICATION_SUPPORTED;
	f->query_backlight_transfer_अक्षरacteristics =
		mask & ATIF_QUERY_BACKLIGHT_TRANSFER_CHARACTERISTICS_SUPPORTED;
	f->पढ़ोy_to_unकरोck = mask & ATIF_READY_TO_UNDOCK_NOTIFICATION_SUPPORTED;
	f->बाह्यal_gpu_inक्रमmation = mask & ATIF_GET_EXTERNAL_GPU_INFORMATION_SUPPORTED;
पूर्ण

/**
 * amdgpu_atअगर_verअगरy_पूर्णांकerface - verअगरy ATIF
 *
 * @handle: acpi handle
 * @atअगर: amdgpu atअगर काष्ठा
 *
 * Execute the ATIF_FUNCTION_VERIFY_INTERFACE ATIF function
 * to initialize ATIF and determine what features are supported
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atअगर_verअगरy_पूर्णांकerface(काष्ठा amdgpu_atअगर *atअगर)
अणु
	जोड़ acpi_object *info;
	काष्ठा atअगर_verअगरy_पूर्णांकerface output;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = amdgpu_atअगर_call(atअगर, ATIF_FUNCTION_VERIFY_INTERFACE, शून्य);
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

	amdgpu_atअगर_parse_notअगरication(&atअगर->notअगरications, output.notअगरication_mask);
	amdgpu_atअगर_parse_functions(&atअगर->functions, output.function_bits);

out:
	kमुक्त(info);
	वापस err;
पूर्ण

अटल acpi_handle amdgpu_atअगर_probe_handle(acpi_handle dhandle)
अणु
	acpi_handle handle = शून्य;
	अक्षर acpi_method_name[255] = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणु माप(acpi_method_name), acpi_method_name पूर्ण;
	acpi_status status;

	/* For PX/HG प्रणालीs, ATIF and ATPX are in the iGPU's namespace, on dGPU only
	 * प्रणालीs, ATIF is in the dGPU's namespace.
	 */
	status = acpi_get_handle(dhandle, "ATIF", &handle);
	अगर (ACPI_SUCCESS(status))
		जाओ out;

	अगर (amdgpu_has_atpx()) अणु
		status = acpi_get_handle(amdgpu_atpx_get_dhandle(), "ATIF",
					 &handle);
		अगर (ACPI_SUCCESS(status))
			जाओ out;
	पूर्ण

	DRM_DEBUG_DRIVER("No ATIF handle found\n");
	वापस शून्य;
out:
	acpi_get_name(handle, ACPI_FULL_PATHNAME, &buffer);
	DRM_DEBUG_DRIVER("Found ATIF handle %s\n", acpi_method_name);
	वापस handle;
पूर्ण

/**
 * amdgpu_atअगर_get_notअगरication_params - determine notअगरy configuration
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
अटल पूर्णांक amdgpu_atअगर_get_notअगरication_params(काष्ठा amdgpu_atअगर *atअगर)
अणु
	जोड़ acpi_object *info;
	काष्ठा amdgpu_atअगर_notअगरication_cfg *n = &atअगर->notअगरication_cfg;
	काष्ठा atअगर_प्रणाली_params params;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = amdgpu_atअगर_call(atअगर, ATIF_FUNCTION_GET_SYSTEM_PARAMETERS,
				शून्य);
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
 * amdgpu_atअगर_query_backlight_caps - get min and max backlight input संकेत
 *
 * @handle: acpi handle
 *
 * Execute the QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS ATIF function
 * to determine the acceptable range of backlight values
 *
 * Backlight_caps.caps_valid will be set to true अगर the query is successful
 *
 * The input संकेतs are in range 0-255
 *
 * This function assumes the display with backlight is the first LCD
 *
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atअगर_query_backlight_caps(काष्ठा amdgpu_atअगर *atअगर)
अणु
	जोड़ acpi_object *info;
	काष्ठा atअगर_qbtc_output अक्षरacteristics;
	काष्ठा atअगर_qbtc_arguments arguments;
	काष्ठा acpi_buffer params;
	माप_प्रकार size;
	पूर्णांक err = 0;

	arguments.size = माप(arguments);
	arguments.requested_display = ATIF_QBTC_REQUEST_LCD1;

	params.length = माप(arguments);
	params.poपूर्णांकer = (व्योम *)&arguments;

	info = amdgpu_atअगर_call(atअगर,
		ATIF_FUNCTION_QUERY_BRIGHTNESS_TRANSFER_CHARACTERISTICS,
		&params);
	अगर (!info) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	size = *(u16 *) info->buffer.poपूर्णांकer;
	अगर (size < 10) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	स_रखो(&अक्षरacteristics, 0, माप(अक्षरacteristics));
	size = min(माप(अक्षरacteristics), size);
	स_नकल(&अक्षरacteristics, info->buffer.poपूर्णांकer, size);

	atअगर->backlight_caps.caps_valid = true;
	atअगर->backlight_caps.min_input_संकेत =
			अक्षरacteristics.min_input_संकेत;
	atअगर->backlight_caps.max_input_संकेत =
			अक्षरacteristics.max_input_संकेत;
out:
	kमुक्त(info);
	वापस err;
पूर्ण

/**
 * amdgpu_atअगर_get_sbios_requests - get requested sbios event
 *
 * @handle: acpi handle
 * @req: atअगर sbios request काष्ठा
 *
 * Execute the ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS ATIF function
 * to determine what requests the sbios is making to the driver
 * (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atअगर_get_sbios_requests(काष्ठा amdgpu_atअगर *atअगर,
					  काष्ठा atअगर_sbios_requests *req)
अणु
	जोड़ acpi_object *info;
	माप_प्रकार size;
	पूर्णांक count = 0;

	info = amdgpu_atअगर_call(atअगर, ATIF_FUNCTION_GET_SYSTEM_BIOS_REQUESTS,
				शून्य);
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
 * amdgpu_atअगर_handler - handle ATIF notअगरy requests
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @event: atअगर sbios request काष्ठा
 *
 * Checks the acpi event and अगर it matches an atअगर event,
 * handles it.
 *
 * Returns:
 * NOTIFY_BAD or NOTIFY_DONE, depending on the event.
 */
अटल पूर्णांक amdgpu_atअगर_handler(काष्ठा amdgpu_device *adev,
			       काष्ठा acpi_bus_event *event)
अणु
	काष्ठा amdgpu_atअगर *atअगर = adev->atअगर;
	पूर्णांक count;

	DRM_DEBUG_DRIVER("event, device_class = %s, type = %#x\n",
			event->device_class, event->type);

	अगर (म_भेद(event->device_class, ACPI_VIDEO_CLASS) != 0)
		वापस NOTIFY_DONE;

	/* Is this actually our event? */
	अगर (!atअगर ||
	    !atअगर->notअगरication_cfg.enabled ||
	    event->type != atअगर->notअगरication_cfg.command_code) अणु
		/* These events will generate keypresses otherwise */
		अगर (event->type == ACPI_VIDEO_NOTIFY_PROBE)
			वापस NOTIFY_BAD;
		अन्यथा
			वापस NOTIFY_DONE;
	पूर्ण

	अगर (atअगर->functions.sbios_requests) अणु
		काष्ठा atअगर_sbios_requests req;

		/* Check pending SBIOS requests */
		count = amdgpu_atअगर_get_sbios_requests(atअगर, &req);

		अगर (count <= 0)
			वापस NOTIFY_BAD;

		DRM_DEBUG_DRIVER("ATIF: %d pending SBIOS requests\n", count);

		अगर (req.pending & ATIF_PANEL_BRIGHTNESS_CHANGE_REQUEST) अणु
#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)
			अगर (atअगर->bd) अणु
				DRM_DEBUG_DRIVER("Changing brightness to %d\n",
						 req.backlight_level);
				/*
				 * XXX backlight_device_set_brightness() is
				 * hardwired to post BACKLIGHT_UPDATE_SYSFS.
				 * It probably should accept 'reason' parameter.
				 */
				backlight_device_set_brightness(atअगर->bd, req.backlight_level);
			पूर्ण
#पूर्ण_अगर
		पूर्ण

		अगर (req.pending & ATIF_DGPU_DISPLAY_EVENT) अणु
			अगर (adev->flags & AMD_IS_PX) अणु
				pm_runसमय_get_sync(adev_to_drm(adev)->dev);
				/* Just fire off a uevent and let userspace tell us what to करो */
				drm_helper_hpd_irq_event(adev_to_drm(adev));
				pm_runसमय_mark_last_busy(adev_to_drm(adev)->dev);
				pm_runसमय_put_स्वतःsuspend(adev_to_drm(adev)->dev);
			पूर्ण
		पूर्ण
		/* TODO: check other events */
	पूर्ण

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
 * amdgpu_atcs_call - call an ATCS method
 *
 * @handle: acpi handle
 * @function: the ATCS function to execute
 * @params: ATCS function params
 *
 * Executes the requested ATCS function (all asics).
 * Returns a poपूर्णांकer to the acpi output buffer.
 */
अटल जोड़ acpi_object *amdgpu_atcs_call(acpi_handle handle, पूर्णांक function,
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
 * amdgpu_atcs_parse_functions - parse supported functions
 *
 * @f: supported functions काष्ठा
 * @mask: supported functions mask from ATCS
 *
 * Use the supported functions mask from ATCS function
 * ATCS_FUNCTION_VERIFY_INTERFACE to determine what functions
 * are supported (all asics).
 */
अटल व्योम amdgpu_atcs_parse_functions(काष्ठा amdgpu_atcs_functions *f, u32 mask)
अणु
	f->get_ext_state = mask & ATCS_GET_EXTERNAL_STATE_SUPPORTED;
	f->pcie_perf_req = mask & ATCS_PCIE_PERFORMANCE_REQUEST_SUPPORTED;
	f->pcie_dev_rdy = mask & ATCS_PCIE_DEVICE_READY_NOTIFICATION_SUPPORTED;
	f->pcie_bus_width = mask & ATCS_SET_PCIE_BUS_WIDTH_SUPPORTED;
पूर्ण

/**
 * amdgpu_atcs_verअगरy_पूर्णांकerface - verअगरy ATCS
 *
 * @handle: acpi handle
 * @atcs: amdgpu atcs काष्ठा
 *
 * Execute the ATCS_FUNCTION_VERIFY_INTERFACE ATCS function
 * to initialize ATCS and determine what features are supported
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atcs_verअगरy_पूर्णांकerface(acpi_handle handle,
					काष्ठा amdgpu_atcs *atcs)
अणु
	जोड़ acpi_object *info;
	काष्ठा atcs_verअगरy_पूर्णांकerface output;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = amdgpu_atcs_call(handle, ATCS_FUNCTION_VERIFY_INTERFACE, शून्य);
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

	amdgpu_atcs_parse_functions(&atcs->functions, output.function_bits);

out:
	kमुक्त(info);
	वापस err;
पूर्ण

/**
 * amdgpu_acpi_is_pcie_perक्रमmance_request_supported
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Check अगर the ATCS pcie_perf_req and pcie_dev_rdy methods
 * are supported (all asics).
 * वापसs true अगर supported, false अगर not.
 */
bool amdgpu_acpi_is_pcie_perक्रमmance_request_supported(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा amdgpu_atcs *atcs = &adev->atcs;

	अगर (atcs->functions.pcie_perf_req && atcs->functions.pcie_dev_rdy)
		वापस true;

	वापस false;
पूर्ण

/**
 * amdgpu_acpi_pcie_notअगरy_device_पढ़ोy
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Executes the PCIE_DEVICE_READY_NOTIFICATION method
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
पूर्णांक amdgpu_acpi_pcie_notअगरy_device_पढ़ोy(काष्ठा amdgpu_device *adev)
अणु
	acpi_handle handle;
	जोड़ acpi_object *info;
	काष्ठा amdgpu_atcs *atcs = &adev->atcs;

	/* Get the device handle */
	handle = ACPI_HANDLE(&adev->pdev->dev);
	अगर (!handle)
		वापस -EINVAL;

	अगर (!atcs->functions.pcie_dev_rdy)
		वापस -EINVAL;

	info = amdgpu_atcs_call(handle, ATCS_FUNCTION_PCIE_DEVICE_READY_NOTIFICATION, शून्य);
	अगर (!info)
		वापस -EIO;

	kमुक्त(info);

	वापस 0;
पूर्ण

/**
 * amdgpu_acpi_pcie_perक्रमmance_request
 *
 * @adev: amdgpu_device poपूर्णांकer
 * @perf_req: requested perf level (pcie gen speed)
 * @advertise: set advertise caps flag अगर set
 *
 * Executes the PCIE_PERFORMANCE_REQUEST method to
 * change the pcie gen speed (all asics).
 * वापसs 0 on success, error on failure.
 */
पूर्णांक amdgpu_acpi_pcie_perक्रमmance_request(काष्ठा amdgpu_device *adev,
					 u8 perf_req, bool advertise)
अणु
	acpi_handle handle;
	जोड़ acpi_object *info;
	काष्ठा amdgpu_atcs *atcs = &adev->atcs;
	काष्ठा atcs_pref_req_input atcs_input;
	काष्ठा atcs_pref_req_output atcs_output;
	काष्ठा acpi_buffer params;
	माप_प्रकार size;
	u32 retry = 3;

	अगर (amdgpu_acpi_pcie_notअगरy_device_पढ़ोy(adev))
		वापस -EINVAL;

	/* Get the device handle */
	handle = ACPI_HANDLE(&adev->pdev->dev);
	अगर (!handle)
		वापस -EINVAL;

	अगर (!atcs->functions.pcie_perf_req)
		वापस -EINVAL;

	atcs_input.size = माप(काष्ठा atcs_pref_req_input);
	/* client id (bit 2-0: func num, 7-3: dev num, 15-8: bus num) */
	atcs_input.client_id = adev->pdev->devfn | (adev->pdev->bus->number << 8);
	atcs_input.valid_flags_mask = ATCS_VALID_FLAGS_MASK;
	atcs_input.flags = ATCS_WAIT_FOR_COMPLETION;
	अगर (advertise)
		atcs_input.flags |= ATCS_ADVERTISE_CAPS;
	atcs_input.req_type = ATCS_PCIE_LINK_SPEED;
	atcs_input.perf_req = perf_req;

	params.length = माप(काष्ठा atcs_pref_req_input);
	params.poपूर्णांकer = &atcs_input;

	जबतक (retry--) अणु
		info = amdgpu_atcs_call(handle, ATCS_FUNCTION_PCIE_PERFORMANCE_REQUEST, &params);
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
 * amdgpu_acpi_event - handle notअगरy events
 *
 * @nb: notअगरier block
 * @val: val
 * @data: acpi event
 *
 * Calls relevant amdgpu functions in response to various
 * acpi events.
 * Returns NOTIFY code
 */
अटल पूर्णांक amdgpu_acpi_event(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ val,
			     व्योम *data)
अणु
	काष्ठा amdgpu_device *adev = container_of(nb, काष्ठा amdgpu_device, acpi_nb);
	काष्ठा acpi_bus_event *entry = (काष्ठा acpi_bus_event *)data;

	अगर (म_भेद(entry->device_class, ACPI_AC_CLASS) == 0) अणु
		अगर (घातer_supply_is_प्रणाली_supplied() > 0)
			DRM_DEBUG_DRIVER("pm: AC\n");
		अन्यथा
			DRM_DEBUG_DRIVER("pm: DC\n");

		amdgpu_pm_acpi_event_handler(adev);
	पूर्ण

	/* Check क्रम pending SBIOS requests */
	वापस amdgpu_atअगर_handler(adev, entry);
पूर्ण

/* Call all ACPI methods here */
/**
 * amdgpu_acpi_init - init driver acpi support
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Verअगरies the AMD ACPI पूर्णांकerfaces and रेजिस्टरs with the acpi
 * notअगरier chain (all asics).
 * Returns 0 on success, error on failure.
 */
पूर्णांक amdgpu_acpi_init(काष्ठा amdgpu_device *adev)
अणु
	acpi_handle handle, atअगर_handle;
	काष्ठा amdgpu_atअगर *atअगर;
	काष्ठा amdgpu_atcs *atcs = &adev->atcs;
	पूर्णांक ret;

	/* Get the device handle */
	handle = ACPI_HANDLE(&adev->pdev->dev);

	अगर (!adev->bios || !handle)
		वापस 0;

	/* Call the ATCS method */
	ret = amdgpu_atcs_verअगरy_पूर्णांकerface(handle, atcs);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Call to ATCS verify_interface failed: %d\n", ret);
	पूर्ण

	/* Probe क्रम ATIF, and initialize it अगर found */
	atअगर_handle = amdgpu_atअगर_probe_handle(handle);
	अगर (!atअगर_handle)
		जाओ out;

	atअगर = kzalloc(माप(*atअगर), GFP_KERNEL);
	अगर (!atअगर) अणु
		DRM_WARN("Not enough memory to initialize ATIF\n");
		जाओ out;
	पूर्ण
	atअगर->handle = atअगर_handle;

	/* Call the ATIF method */
	ret = amdgpu_atअगर_verअगरy_पूर्णांकerface(atअगर);
	अगर (ret) अणु
		DRM_DEBUG_DRIVER("Call to ATIF verify_interface failed: %d\n", ret);
		kमुक्त(atअगर);
		जाओ out;
	पूर्ण
	adev->atअगर = atअगर;

#अगर defined(CONFIG_BACKLIGHT_CLASS_DEVICE) || defined(CONFIG_BACKLIGHT_CLASS_DEVICE_MODULE)
	अगर (atअगर->notअगरications.brightness_change) अणु
		अगर (amdgpu_device_has_dc_support(adev)) अणु
#अगर defined(CONFIG_DRM_AMD_DC)
			काष्ठा amdgpu_display_manager *dm = &adev->dm;
			atअगर->bd = dm->backlight_dev;
#पूर्ण_अगर
		पूर्ण अन्यथा अणु
			काष्ठा drm_encoder *पंचांगp;

			/* Find the encoder controlling the brightness */
			list_क्रम_each_entry(पंचांगp, &adev_to_drm(adev)->mode_config.encoder_list,
					    head) अणु
				काष्ठा amdgpu_encoder *enc = to_amdgpu_encoder(पंचांगp);

				अगर ((enc->devices & (ATOM_DEVICE_LCD_SUPPORT)) &&
				    enc->enc_priv) अणु
					काष्ठा amdgpu_encoder_atom_dig *dig = enc->enc_priv;
					अगर (dig->bl_dev) अणु
						atअगर->bd = dig->bl_dev;
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	अगर (atअगर->functions.sbios_requests && !atअगर->functions.प्रणाली_params) अणु
		/* XXX check this workraround, अगर sbios request function is
		 * present we have to see how it's configured in the प्रणाली
		 * params
		 */
		atअगर->functions.प्रणाली_params = true;
	पूर्ण

	अगर (atअगर->functions.प्रणाली_params) अणु
		ret = amdgpu_atअगर_get_notअगरication_params(atअगर);
		अगर (ret) अणु
			DRM_DEBUG_DRIVER("Call to GET_SYSTEM_PARAMS failed: %d\n",
					ret);
			/* Disable notअगरication */
			atअगर->notअगरication_cfg.enabled = false;
		पूर्ण
	पूर्ण

	अगर (atअगर->functions.query_backlight_transfer_अक्षरacteristics) अणु
		ret = amdgpu_atअगर_query_backlight_caps(atअगर);
		अगर (ret) अणु
			DRM_DEBUG_DRIVER("Call to QUERY_BACKLIGHT_TRANSFER_CHARACTERISTICS failed: %d\n",
					ret);
			atअगर->backlight_caps.caps_valid = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		atअगर->backlight_caps.caps_valid = false;
	पूर्ण

out:
	adev->acpi_nb.notअगरier_call = amdgpu_acpi_event;
	रेजिस्टर_acpi_notअगरier(&adev->acpi_nb);

	वापस ret;
पूर्ण

व्योम amdgpu_acpi_get_backlight_caps(काष्ठा amdgpu_device *adev,
		काष्ठा amdgpu_dm_backlight_caps *caps)
अणु
	अगर (!adev->atअगर) अणु
		caps->caps_valid = false;
		वापस;
	पूर्ण
	caps->caps_valid = adev->atअगर->backlight_caps.caps_valid;
	caps->min_input_संकेत = adev->atअगर->backlight_caps.min_input_संकेत;
	caps->max_input_संकेत = adev->atअगर->backlight_caps.max_input_संकेत;
पूर्ण

/**
 * amdgpu_acpi_fini - tear करोwn driver acpi support
 *
 * @adev: amdgpu_device poपूर्णांकer
 *
 * Unरेजिस्टरs with the acpi notअगरier chain (all asics).
 */
व्योम amdgpu_acpi_fini(काष्ठा amdgpu_device *adev)
अणु
	unरेजिस्टर_acpi_notअगरier(&adev->acpi_nb);
	kमुक्त(adev->atअगर);
पूर्ण

/**
 * amdgpu_acpi_is_s0ix_supported
 *
 * वापसs true अगर supported, false अगर not.
 */
bool amdgpu_acpi_is_s0ix_supported(काष्ठा amdgpu_device *adev)
अणु
#अगर defined(CONFIG_AMD_PMC) || defined(CONFIG_AMD_PMC_MODULE)
	अगर (acpi_gbl_FADT.flags & ACPI_FADT_LOW_POWER_S0) अणु
		अगर (adev->flags & AMD_IS_APU)
			वापस true;
	पूर्ण
#पूर्ण_अगर
	वापस false;
पूर्ण
