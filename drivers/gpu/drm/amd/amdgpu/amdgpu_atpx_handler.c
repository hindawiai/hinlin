<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010 Red Hat Inc.
 * Author : Dave Airlie <airlied@redhat.com>
 *
 * ATPX support क्रम both Intel/ATI
 */
#समावेश <linux/vga_चयनeroo.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/delay.h>

#समावेश "amd_acpi.h"

#घोषणा AMDGPU_PX_QUIRK_FORCE_ATPX  (1 << 0)

काष्ठा amdgpu_px_quirk अणु
	u32 chip_venकरोr;
	u32 chip_device;
	u32 subsys_venकरोr;
	u32 subsys_device;
	u32 px_quirk_flags;
पूर्ण;

काष्ठा amdgpu_atpx_functions अणु
	bool px_params;
	bool घातer_cntl;
	bool disp_mux_cntl;
	bool i2c_mux_cntl;
	bool चयन_start;
	bool चयन_end;
	bool disp_connectors_mapping;
	bool disp_detection_ports;
पूर्ण;

काष्ठा amdgpu_atpx अणु
	acpi_handle handle;
	काष्ठा amdgpu_atpx_functions functions;
	bool is_hybrid;
	bool dgpu_req_घातer_क्रम_displays;
पूर्ण;

अटल काष्ठा amdgpu_atpx_priv अणु
	bool atpx_detected;
	bool bridge_pm_usable;
	अचिन्हित पूर्णांक quirks;
	/* handle क्रम device - and atpx */
	acpi_handle dhandle;
	acpi_handle other_handle;
	काष्ठा amdgpu_atpx atpx;
पूर्ण amdgpu_atpx_priv;

काष्ठा atpx_verअगरy_पूर्णांकerface अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u16 version;		/* version */
	u32 function_bits;	/* supported functions bit vector */
पूर्ण __packed;

काष्ठा atpx_px_params अणु
	u16 size;		/* काष्ठाure size in bytes (includes size field) */
	u32 valid_flags;	/* which flags are valid */
	u32 flags;		/* flags */
पूर्ण __packed;

काष्ठा atpx_घातer_control अणु
	u16 size;
	u8 dgpu_state;
पूर्ण __packed;

काष्ठा atpx_mux अणु
	u16 size;
	u16 mux;
पूर्ण __packed;

bool amdgpu_has_atpx(व्योम) अणु
	वापस amdgpu_atpx_priv.atpx_detected;
पूर्ण

bool amdgpu_has_atpx_dgpu_घातer_cntl(व्योम) अणु
	वापस amdgpu_atpx_priv.atpx.functions.घातer_cntl;
पूर्ण

bool amdgpu_is_atpx_hybrid(व्योम) अणु
	वापस amdgpu_atpx_priv.atpx.is_hybrid;
पूर्ण

bool amdgpu_atpx_dgpu_req_घातer_क्रम_displays(व्योम) अणु
	वापस amdgpu_atpx_priv.atpx.dgpu_req_घातer_क्रम_displays;
पूर्ण

#अगर defined(CONFIG_ACPI)
व्योम *amdgpu_atpx_get_dhandle(व्योम) अणु
	वापस amdgpu_atpx_priv.dhandle;
पूर्ण
#पूर्ण_अगर

/**
 * amdgpu_atpx_call - call an ATPX method
 *
 * @handle: acpi handle
 * @function: the ATPX function to execute
 * @params: ATPX function params
 *
 * Executes the requested ATPX function (all asics).
 * Returns a poपूर्णांकer to the acpi output buffer.
 */
अटल जोड़ acpi_object *amdgpu_atpx_call(acpi_handle handle, पूर्णांक function,
					   काष्ठा acpi_buffer *params)
अणु
	acpi_status status;
	जोड़ acpi_object atpx_arg_elements[2];
	काष्ठा acpi_object_list atpx_arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्य पूर्ण;

	atpx_arg.count = 2;
	atpx_arg.poपूर्णांकer = &atpx_arg_elements[0];

	atpx_arg_elements[0].type = ACPI_TYPE_INTEGER;
	atpx_arg_elements[0].पूर्णांकeger.value = function;

	अगर (params) अणु
		atpx_arg_elements[1].type = ACPI_TYPE_BUFFER;
		atpx_arg_elements[1].buffer.length = params->length;
		atpx_arg_elements[1].buffer.poपूर्णांकer = params->poपूर्णांकer;
	पूर्ण अन्यथा अणु
		/* We need a second fake parameter */
		atpx_arg_elements[1].type = ACPI_TYPE_INTEGER;
		atpx_arg_elements[1].पूर्णांकeger.value = 0;
	पूर्ण

	status = acpi_evaluate_object(handle, शून्य, &atpx_arg, &buffer);

	/* Fail only अगर calling the method fails and ATPX is supported */
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		prपूर्णांकk("failed to evaluate ATPX got %s\n",
		       acpi_क्रमmat_exception(status));
		kमुक्त(buffer.poपूर्णांकer);
		वापस शून्य;
	पूर्ण

	वापस buffer.poपूर्णांकer;
पूर्ण

/**
 * amdgpu_atpx_parse_functions - parse supported functions
 *
 * @f: supported functions काष्ठा
 * @mask: supported functions mask from ATPX
 *
 * Use the supported functions mask from ATPX function
 * ATPX_FUNCTION_VERIFY_INTERFACE to determine what functions
 * are supported (all asics).
 */
अटल व्योम amdgpu_atpx_parse_functions(काष्ठा amdgpu_atpx_functions *f, u32 mask)
अणु
	f->px_params = mask & ATPX_GET_PX_PARAMETERS_SUPPORTED;
	f->घातer_cntl = mask & ATPX_POWER_CONTROL_SUPPORTED;
	f->disp_mux_cntl = mask & ATPX_DISPLAY_MUX_CONTROL_SUPPORTED;
	f->i2c_mux_cntl = mask & ATPX_I2C_MUX_CONTROL_SUPPORTED;
	f->चयन_start = mask & ATPX_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION_SUPPORTED;
	f->चयन_end = mask & ATPX_GRAPHICS_DEVICE_SWITCH_END_NOTIFICATION_SUPPORTED;
	f->disp_connectors_mapping = mask & ATPX_GET_DISPLAY_CONNECTORS_MAPPING_SUPPORTED;
	f->disp_detection_ports = mask & ATPX_GET_DISPLAY_DETECTION_PORTS_SUPPORTED;
पूर्ण

/**
 * amdgpu_atpx_validate_functions - validate ATPX functions
 *
 * @atpx: amdgpu atpx काष्ठा
 *
 * Validate that required functions are enabled (all asics).
 * वापसs 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_validate(काष्ठा amdgpu_atpx *atpx)
अणु
	u32 valid_bits = 0;

	अगर (atpx->functions.px_params) अणु
		जोड़ acpi_object *info;
		काष्ठा atpx_px_params output;
		माप_प्रकार size;

		info = amdgpu_atpx_call(atpx->handle, ATPX_FUNCTION_GET_PX_PARAMETERS, शून्य);
		अगर (!info)
			वापस -EIO;

		स_रखो(&output, 0, माप(output));

		size = *(u16 *) info->buffer.poपूर्णांकer;
		अगर (size < 10) अणु
			prपूर्णांकk("ATPX buffer is too small: %zu\n", size);
			kमुक्त(info);
			वापस -EINVAL;
		पूर्ण
		size = min(माप(output), size);

		स_नकल(&output, info->buffer.poपूर्णांकer, size);

		valid_bits = output.flags & output.valid_flags;

		kमुक्त(info);
	पूर्ण

	/* अगर separate mux flag is set, mux controls are required */
	अगर (valid_bits & ATPX_SEPARATE_MUX_FOR_I2C) अणु
		atpx->functions.i2c_mux_cntl = true;
		atpx->functions.disp_mux_cntl = true;
	पूर्ण
	/* अगर any outमाला_दो are muxed, mux controls are required */
	अगर (valid_bits & (ATPX_CRT1_RGB_SIGNAL_MUXED |
			  ATPX_TV_SIGNAL_MUXED |
			  ATPX_DFP_SIGNAL_MUXED))
		atpx->functions.disp_mux_cntl = true;


	/* some bioses set these bits rather than flagging घातer_cntl as supported */
	अगर (valid_bits & (ATPX_DYNAMIC_PX_SUPPORTED |
			  ATPX_DYNAMIC_DGPU_POWER_OFF_SUPPORTED))
		atpx->functions.घातer_cntl = true;

	atpx->is_hybrid = false;
	अगर (valid_bits & ATPX_MS_HYBRID_GFX_SUPPORTED) अणु
		अगर (amdgpu_atpx_priv.quirks & AMDGPU_PX_QUIRK_FORCE_ATPX) अणु
			prपूर्णांकk("ATPX Hybrid Graphics, forcing to ATPX\n");
			atpx->functions.घातer_cntl = true;
			atpx->is_hybrid = false;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("ATPX Hybrid Graphics\n");
			/*
			 * Disable legacy PM methods only when pcie port PM is usable,
			 * otherwise the device might fail to घातer off or घातer on.
			 */
			atpx->functions.घातer_cntl = !amdgpu_atpx_priv.bridge_pm_usable;
			atpx->is_hybrid = true;
		पूर्ण
	पूर्ण

	atpx->dgpu_req_घातer_क्रम_displays = false;
	अगर (valid_bits & ATPX_DGPU_REQ_POWER_FOR_DISPLAYS)
		atpx->dgpu_req_घातer_क्रम_displays = true;

	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_verअगरy_पूर्णांकerface - verअगरy ATPX
 *
 * @atpx: amdgpu atpx काष्ठा
 *
 * Execute the ATPX_FUNCTION_VERIFY_INTERFACE ATPX function
 * to initialize ATPX and determine what features are supported
 * (all asics).
 * वापसs 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_verअगरy_पूर्णांकerface(काष्ठा amdgpu_atpx *atpx)
अणु
	जोड़ acpi_object *info;
	काष्ठा atpx_verअगरy_पूर्णांकerface output;
	माप_प्रकार size;
	पूर्णांक err = 0;

	info = amdgpu_atpx_call(atpx->handle, ATPX_FUNCTION_VERIFY_INTERFACE, शून्य);
	अगर (!info)
		वापस -EIO;

	स_रखो(&output, 0, माप(output));

	size = *(u16 *) info->buffer.poपूर्णांकer;
	अगर (size < 8) अणु
		prपूर्णांकk("ATPX buffer is too small: %zu\n", size);
		err = -EINVAL;
		जाओ out;
	पूर्ण
	size = min(माप(output), size);

	स_नकल(&output, info->buffer.poपूर्णांकer, size);

	/* TODO: check version? */
	prपूर्णांकk("ATPX version %u, functions 0x%08x\n",
	       output.version, output.function_bits);

	amdgpu_atpx_parse_functions(&atpx->functions, output.function_bits);

out:
	kमुक्त(info);
	वापस err;
पूर्ण

/**
 * amdgpu_atpx_set_discrete_state - घातer up/करोwn discrete GPU
 *
 * @atpx: atpx info काष्ठा
 * @state: discrete GPU state (0 = घातer करोwn, 1 = घातer up)
 *
 * Execute the ATPX_FUNCTION_POWER_CONTROL ATPX function to
 * घातer करोwn/up the discrete GPU (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_set_discrete_state(काष्ठा amdgpu_atpx *atpx, u8 state)
अणु
	काष्ठा acpi_buffer params;
	जोड़ acpi_object *info;
	काष्ठा atpx_घातer_control input;

	अगर (atpx->functions.घातer_cntl) अणु
		input.size = 3;
		input.dgpu_state = state;
		params.length = input.size;
		params.poपूर्णांकer = &input;
		info = amdgpu_atpx_call(atpx->handle,
					ATPX_FUNCTION_POWER_CONTROL,
					&params);
		अगर (!info)
			वापस -EIO;
		kमुक्त(info);

		/* 200ms delay is required after off */
		अगर (state == 0)
			msleep(200);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_चयन_disp_mux - चयन display mux
 *
 * @atpx: atpx info काष्ठा
 * @mux_id: mux state (0 = पूर्णांकegrated GPU, 1 = discrete GPU)
 *
 * Execute the ATPX_FUNCTION_DISPLAY_MUX_CONTROL ATPX function to
 * चयन the display mux between the discrete GPU and पूर्णांकegrated GPU
 * (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_चयन_disp_mux(काष्ठा amdgpu_atpx *atpx, u16 mux_id)
अणु
	काष्ठा acpi_buffer params;
	जोड़ acpi_object *info;
	काष्ठा atpx_mux input;

	अगर (atpx->functions.disp_mux_cntl) अणु
		input.size = 4;
		input.mux = mux_id;
		params.length = input.size;
		params.poपूर्णांकer = &input;
		info = amdgpu_atpx_call(atpx->handle,
					ATPX_FUNCTION_DISPLAY_MUX_CONTROL,
					&params);
		अगर (!info)
			वापस -EIO;
		kमुक्त(info);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_चयन_i2c_mux - चयन i2c/hpd mux
 *
 * @atpx: atpx info काष्ठा
 * @mux_id: mux state (0 = पूर्णांकegrated GPU, 1 = discrete GPU)
 *
 * Execute the ATPX_FUNCTION_I2C_MUX_CONTROL ATPX function to
 * चयन the i2c/hpd mux between the discrete GPU and पूर्णांकegrated GPU
 * (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_चयन_i2c_mux(काष्ठा amdgpu_atpx *atpx, u16 mux_id)
अणु
	काष्ठा acpi_buffer params;
	जोड़ acpi_object *info;
	काष्ठा atpx_mux input;

	अगर (atpx->functions.i2c_mux_cntl) अणु
		input.size = 4;
		input.mux = mux_id;
		params.length = input.size;
		params.poपूर्णांकer = &input;
		info = amdgpu_atpx_call(atpx->handle,
					ATPX_FUNCTION_I2C_MUX_CONTROL,
					&params);
		अगर (!info)
			वापस -EIO;
		kमुक्त(info);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_चयन_start - notअगरy the sbios of a GPU चयन
 *
 * @atpx: atpx info काष्ठा
 * @mux_id: mux state (0 = पूर्णांकegrated GPU, 1 = discrete GPU)
 *
 * Execute the ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION ATPX
 * function to notअगरy the sbios that a चयन between the discrete GPU and
 * पूर्णांकegrated GPU has begun (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_चयन_start(काष्ठा amdgpu_atpx *atpx, u16 mux_id)
अणु
	काष्ठा acpi_buffer params;
	जोड़ acpi_object *info;
	काष्ठा atpx_mux input;

	अगर (atpx->functions.चयन_start) अणु
		input.size = 4;
		input.mux = mux_id;
		params.length = input.size;
		params.poपूर्णांकer = &input;
		info = amdgpu_atpx_call(atpx->handle,
					ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_START_NOTIFICATION,
					&params);
		अगर (!info)
			वापस -EIO;
		kमुक्त(info);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_चयन_end - notअगरy the sbios of a GPU चयन
 *
 * @atpx: atpx info काष्ठा
 * @mux_id: mux state (0 = पूर्णांकegrated GPU, 1 = discrete GPU)
 *
 * Execute the ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_END_NOTIFICATION ATPX
 * function to notअगरy the sbios that a चयन between the discrete GPU and
 * पूर्णांकegrated GPU has ended (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_चयन_end(काष्ठा amdgpu_atpx *atpx, u16 mux_id)
अणु
	काष्ठा acpi_buffer params;
	जोड़ acpi_object *info;
	काष्ठा atpx_mux input;

	अगर (atpx->functions.चयन_end) अणु
		input.size = 4;
		input.mux = mux_id;
		params.length = input.size;
		params.poपूर्णांकer = &input;
		info = amdgpu_atpx_call(atpx->handle,
					ATPX_FUNCTION_GRAPHICS_DEVICE_SWITCH_END_NOTIFICATION,
					&params);
		अगर (!info)
			वापस -EIO;
		kमुक्त(info);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_चयनto - चयन to the requested GPU
 *
 * @id: GPU to चयन to
 *
 * Execute the necessary ATPX functions to चयन between the discrete GPU and
 * पूर्णांकegrated GPU (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_चयनto(क्रमागत vga_चयनeroo_client_id id)
अणु
	u16 gpu_id;

	अगर (id == VGA_SWITCHEROO_IGD)
		gpu_id = ATPX_INTEGRATED_GPU;
	अन्यथा
		gpu_id = ATPX_DISCRETE_GPU;

	amdgpu_atpx_चयन_start(&amdgpu_atpx_priv.atpx, gpu_id);
	amdgpu_atpx_चयन_disp_mux(&amdgpu_atpx_priv.atpx, gpu_id);
	amdgpu_atpx_चयन_i2c_mux(&amdgpu_atpx_priv.atpx, gpu_id);
	amdgpu_atpx_चयन_end(&amdgpu_atpx_priv.atpx, gpu_id);

	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_घातer_state - घातer करोwn/up the requested GPU
 *
 * @id: GPU to घातer करोwn/up
 * @state: requested घातer state (0 = off, 1 = on)
 *
 * Execute the necessary ATPX function to घातer करोwn/up the discrete GPU
 * (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_घातer_state(क्रमागत vga_चयनeroo_client_id id,
				   क्रमागत vga_चयनeroo_state state)
अणु
	/* on w500 ACPI can't change पूर्णांकel gpu state */
	अगर (id == VGA_SWITCHEROO_IGD)
		वापस 0;

	amdgpu_atpx_set_discrete_state(&amdgpu_atpx_priv.atpx, state);
	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_pci_probe_handle - look up the ATPX handle
 *
 * @pdev: pci device
 *
 * Look up the ATPX handles (all asics).
 * Returns true अगर the handles are found, false अगर not.
 */
अटल bool amdgpu_atpx_pci_probe_handle(काष्ठा pci_dev *pdev)
अणु
	acpi_handle dhandle, atpx_handle;
	acpi_status status;

	dhandle = ACPI_HANDLE(&pdev->dev);
	अगर (!dhandle)
		वापस false;

	status = acpi_get_handle(dhandle, "ATPX", &atpx_handle);
	अगर (ACPI_FAILURE(status)) अणु
		amdgpu_atpx_priv.other_handle = dhandle;
		वापस false;
	पूर्ण
	amdgpu_atpx_priv.dhandle = dhandle;
	amdgpu_atpx_priv.atpx.handle = atpx_handle;
	वापस true;
पूर्ण

/**
 * amdgpu_atpx_init - verअगरy the ATPX पूर्णांकerface
 *
 * Verअगरy the ATPX पूर्णांकerface (all asics).
 * Returns 0 on success, error on failure.
 */
अटल पूर्णांक amdgpu_atpx_init(व्योम)
अणु
	पूर्णांक r;

	/* set up the ATPX handle */
	r = amdgpu_atpx_verअगरy_पूर्णांकerface(&amdgpu_atpx_priv.atpx);
	अगर (r)
		वापस r;

	/* validate the atpx setup */
	r = amdgpu_atpx_validate(&amdgpu_atpx_priv.atpx);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

/**
 * amdgpu_atpx_get_client_id - get the client id
 *
 * @pdev: pci device
 *
 * look up whether we are the पूर्णांकegrated or discrete GPU (all asics).
 * Returns the client id.
 */
अटल क्रमागत vga_चयनeroo_client_id amdgpu_atpx_get_client_id(काष्ठा pci_dev *pdev)
अणु
	अगर (amdgpu_atpx_priv.dhandle == ACPI_HANDLE(&pdev->dev))
		वापस VGA_SWITCHEROO_IGD;
	अन्यथा
		वापस VGA_SWITCHEROO_DIS;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_handler amdgpu_atpx_handler = अणु
	.चयनto = amdgpu_atpx_चयनto,
	.घातer_state = amdgpu_atpx_घातer_state,
	.get_client_id = amdgpu_atpx_get_client_id,
पूर्ण;

अटल स्थिर काष्ठा amdgpu_px_quirk amdgpu_px_quirk_list[] = अणु
	/* HG _PR3 करोesn't seem to work on this A+A weston board */
	अणु 0x1002, 0x6900, 0x1002, 0x0124, AMDGPU_PX_QUIRK_FORCE_ATPX पूर्ण,
	अणु 0x1002, 0x6900, 0x1028, 0x0812, AMDGPU_PX_QUIRK_FORCE_ATPX पूर्ण,
	अणु 0x1002, 0x6900, 0x1028, 0x0813, AMDGPU_PX_QUIRK_FORCE_ATPX पूर्ण,
	अणु 0x1002, 0x699f, 0x1028, 0x0814, AMDGPU_PX_QUIRK_FORCE_ATPX पूर्ण,
	अणु 0x1002, 0x6900, 0x1025, 0x125A, AMDGPU_PX_QUIRK_FORCE_ATPX पूर्ण,
	अणु 0x1002, 0x6900, 0x17AA, 0x3806, AMDGPU_PX_QUIRK_FORCE_ATPX पूर्ण,
	अणु 0, 0, 0, 0, 0 पूर्ण,
पूर्ण;

अटल व्योम amdgpu_atpx_get_quirks(काष्ठा pci_dev *pdev)
अणु
	स्थिर काष्ठा amdgpu_px_quirk *p = amdgpu_px_quirk_list;

	/* Apply PX quirks */
	जबतक (p && p->chip_device != 0) अणु
		अगर (pdev->venकरोr == p->chip_venकरोr &&
		    pdev->device == p->chip_device &&
		    pdev->subप्रणाली_venकरोr == p->subsys_venकरोr &&
		    pdev->subप्रणाली_device == p->subsys_device) अणु
			amdgpu_atpx_priv.quirks |= p->px_quirk_flags;
			अवरोध;
		पूर्ण
		++p;
	पूर्ण
पूर्ण

/**
 * amdgpu_atpx_detect - detect whether we have PX
 *
 * Check अगर we have a PX प्रणाली (all asics).
 * Returns true अगर we have a PX प्रणाली, false अगर not.
 */
अटल bool amdgpu_atpx_detect(व्योम)
अणु
	अक्षर acpi_method_name[255] = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणुमाप(acpi_method_name), acpi_method_nameपूर्ण;
	काष्ठा pci_dev *pdev = शून्य;
	bool has_atpx = false;
	पूर्णांक vga_count = 0;
	bool d3_supported = false;
	काष्ठा pci_dev *parent_pdev;

	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != शून्य) अणु
		vga_count++;

		has_atpx |= amdgpu_atpx_pci_probe_handle(pdev);

		parent_pdev = pci_upstream_bridge(pdev);
		d3_supported |= parent_pdev && parent_pdev->bridge_d3;
		amdgpu_atpx_get_quirks(pdev);
	पूर्ण

	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_OTHER << 8, pdev)) != शून्य) अणु
		vga_count++;

		has_atpx |= amdgpu_atpx_pci_probe_handle(pdev);

		parent_pdev = pci_upstream_bridge(pdev);
		d3_supported |= parent_pdev && parent_pdev->bridge_d3;
		amdgpu_atpx_get_quirks(pdev);
	पूर्ण

	अगर (has_atpx && vga_count == 2) अणु
		acpi_get_name(amdgpu_atpx_priv.atpx.handle, ACPI_FULL_PATHNAME, &buffer);
		pr_info("vga_switcheroo: detected switching method %s handle\n",
			acpi_method_name);
		amdgpu_atpx_priv.atpx_detected = true;
		amdgpu_atpx_priv.bridge_pm_usable = d3_supported;
		amdgpu_atpx_init();
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * amdgpu_रेजिस्टर_atpx_handler - रेजिस्टर with vga_चयनeroo
 *
 * Register the PX callbacks with vga_चयनeroo (all asics).
 */
व्योम amdgpu_रेजिस्टर_atpx_handler(व्योम)
अणु
	bool r;
	क्रमागत vga_चयनeroo_handler_flags_t handler_flags = 0;

	/* detect अगर we have any ATPX + 2 VGA in the प्रणाली */
	r = amdgpu_atpx_detect();
	अगर (!r)
		वापस;

	vga_चयनeroo_रेजिस्टर_handler(&amdgpu_atpx_handler, handler_flags);
पूर्ण

/**
 * amdgpu_unरेजिस्टर_atpx_handler - unरेजिस्टर with vga_चयनeroo
 *
 * Unरेजिस्टर the PX callbacks with vga_चयनeroo (all asics).
 */
व्योम amdgpu_unरेजिस्टर_atpx_handler(व्योम)
अणु
	vga_चयनeroo_unरेजिस्टर_handler();
पूर्ण
