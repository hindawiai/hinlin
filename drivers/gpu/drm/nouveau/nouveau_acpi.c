<शैली गुरु>
// SPDX-License-Identअगरier: MIT
#समावेश <linux/pci.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/mxm-wmi.h>
#समावेश <linux/vga_चयनeroo.h>
#समावेश <drm/drm_edid.h>
#समावेश <acpi/video.h>

#समावेश "nouveau_drv.h"
#समावेश "nouveau_acpi.h"

#घोषणा NOUVEAU_DSM_LED 0x02
#घोषणा NOUVEAU_DSM_LED_STATE 0x00
#घोषणा NOUVEAU_DSM_LED_OFF 0x10
#घोषणा NOUVEAU_DSM_LED_STAMINA 0x11
#घोषणा NOUVEAU_DSM_LED_SPEED 0x12

#घोषणा NOUVEAU_DSM_POWER 0x03
#घोषणा NOUVEAU_DSM_POWER_STATE 0x00
#घोषणा NOUVEAU_DSM_POWER_SPEED 0x01
#घोषणा NOUVEAU_DSM_POWER_STAMINA 0x02

#घोषणा NOUVEAU_DSM_OPTIMUS_CAPS 0x1A
#घोषणा NOUVEAU_DSM_OPTIMUS_FLAGS 0x1B

#घोषणा NOUVEAU_DSM_OPTIMUS_POWERDOWN_PS3 (3 << 24)
#घोषणा NOUVEAU_DSM_OPTIMUS_NO_POWERDOWN_PS3 (2 << 24)
#घोषणा NOUVEAU_DSM_OPTIMUS_FLAGS_CHANGED (1)

#घोषणा NOUVEAU_DSM_OPTIMUS_SET_POWERDOWN (NOUVEAU_DSM_OPTIMUS_POWERDOWN_PS3 | NOUVEAU_DSM_OPTIMUS_FLAGS_CHANGED)

/* result of the optimus caps function */
#घोषणा OPTIMUS_ENABLED (1 << 0)
#घोषणा OPTIMUS_STATUS_MASK (3 << 3)
#घोषणा OPTIMUS_STATUS_OFF  (0 << 3)
#घोषणा OPTIMUS_STATUS_ON_ENABLED  (1 << 3)
#घोषणा OPTIMUS_STATUS_PWR_STABLE  (3 << 3)
#घोषणा OPTIMUS_DISPLAY_HOTPLUG (1 << 6)
#घोषणा OPTIMUS_CAPS_MASK (7 << 24)
#घोषणा OPTIMUS_DYNAMIC_PWR_CAP (1 << 24)

#घोषणा OPTIMUS_AUDIO_CAPS_MASK (3 << 27)
#घोषणा OPTIMUS_HDA_CODEC_MASK (2 << 27) /* hda bios control */

अटल काष्ठा nouveau_dsm_priv अणु
	bool dsm_detected;
	bool optimus_detected;
	bool optimus_flags_detected;
	bool optimus_skip_dsm;
	acpi_handle dhandle;
पूर्ण nouveau_dsm_priv;

bool nouveau_is_optimus(व्योम) अणु
	वापस nouveau_dsm_priv.optimus_detected;
पूर्ण

bool nouveau_is_v1_dsm(व्योम) अणु
	वापस nouveau_dsm_priv.dsm_detected;
पूर्ण

#अगर_घोषित CONFIG_VGA_SWITCHEROO
अटल स्थिर guid_t nouveau_dsm_muid =
	GUID_INIT(0x9D95A0A0, 0x0060, 0x4D48,
		  0xB3, 0x4D, 0x7E, 0x5F, 0xEA, 0x12, 0x9F, 0xD4);

अटल स्थिर guid_t nouveau_op_dsm_muid =
	GUID_INIT(0xA486D8F8, 0x0BDA, 0x471B,
		  0xA7, 0x2B, 0x60, 0x42, 0xA6, 0xB5, 0xBE, 0xE0);

अटल पूर्णांक nouveau_optimus_dsm(acpi_handle handle, पूर्णांक func, पूर्णांक arg, uपूर्णांक32_t *result)
अणु
	पूर्णांक i;
	जोड़ acpi_object *obj;
	अक्षर args_buff[4];
	जोड़ acpi_object argv4 = अणु
		.buffer.type = ACPI_TYPE_BUFFER,
		.buffer.length = 4,
		.buffer.poपूर्णांकer = args_buff
	पूर्ण;

	/* ACPI is little endian, AABBCCDD becomes अणुDD,CC,BB,AAपूर्ण */
	क्रम (i = 0; i < 4; i++)
		args_buff[i] = (arg >> i * 8) & 0xFF;

	*result = 0;
	obj = acpi_evaluate_dsm_typed(handle, &nouveau_op_dsm_muid, 0x00000100,
				      func, &argv4, ACPI_TYPE_BUFFER);
	अगर (!obj) अणु
		acpi_handle_info(handle, "failed to evaluate _DSM\n");
		वापस AE_ERROR;
	पूर्ण अन्यथा अणु
		अगर (obj->buffer.length == 4) अणु
			*result |= obj->buffer.poपूर्णांकer[0];
			*result |= (obj->buffer.poपूर्णांकer[1] << 8);
			*result |= (obj->buffer.poपूर्णांकer[2] << 16);
			*result |= (obj->buffer.poपूर्णांकer[3] << 24);
		पूर्ण
		ACPI_FREE(obj);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * On some platक्रमms, _DSM(nouveau_op_dsm_muid, func0) has special
 * requirements on the fourth parameter, so a निजी implementation
 * instead of using acpi_check_dsm().
 */
अटल पूर्णांक nouveau_dsm_get_optimus_functions(acpi_handle handle)
अणु
	पूर्णांक result;

	/*
	 * Function 0 वापसs a Buffer containing available functions.
	 * The args parameter is ignored क्रम function 0, so just put 0 in it
	 */
	अगर (nouveau_optimus_dsm(handle, 0, 0, &result))
		वापस 0;

	/*
	 * ACPI Spec v4 9.14.1: अगर bit 0 is zero, no function is supported.
	 * If the n-th bit is enabled, function n is supported
	 */
	अगर (result & 1 && result & (1 << NOUVEAU_DSM_OPTIMUS_CAPS))
		वापस result;
	वापस 0;
पूर्ण

अटल पूर्णांक nouveau_dsm(acpi_handle handle, पूर्णांक func, पूर्णांक arg)
अणु
	पूर्णांक ret = 0;
	जोड़ acpi_object *obj;
	जोड़ acpi_object argv4 = अणु
		.पूर्णांकeger.type = ACPI_TYPE_INTEGER,
		.पूर्णांकeger.value = arg,
	पूर्ण;

	obj = acpi_evaluate_dsm_typed(handle, &nouveau_dsm_muid, 0x00000102,
				      func, &argv4, ACPI_TYPE_INTEGER);
	अगर (!obj) अणु
		acpi_handle_info(handle, "failed to evaluate _DSM\n");
		वापस AE_ERROR;
	पूर्ण अन्यथा अणु
		अगर (obj->पूर्णांकeger.value == 0x80000002)
			ret = -ENODEV;
		ACPI_FREE(obj);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक nouveau_dsm_चयन_mux(acpi_handle handle, पूर्णांक mux_id)
अणु
	mxm_wmi_call_mxmx(mux_id == NOUVEAU_DSM_LED_STAMINA ? MXM_MXDS_ADAPTER_IGD : MXM_MXDS_ADAPTER_0);
	mxm_wmi_call_mxds(mux_id == NOUVEAU_DSM_LED_STAMINA ? MXM_MXDS_ADAPTER_IGD : MXM_MXDS_ADAPTER_0);
	वापस nouveau_dsm(handle, NOUVEAU_DSM_LED, mux_id);
पूर्ण

अटल पूर्णांक nouveau_dsm_set_discrete_state(acpi_handle handle, क्रमागत vga_चयनeroo_state state)
अणु
	पूर्णांक arg;
	अगर (state == VGA_SWITCHEROO_ON)
		arg = NOUVEAU_DSM_POWER_SPEED;
	अन्यथा
		arg = NOUVEAU_DSM_POWER_STAMINA;
	nouveau_dsm(handle, NOUVEAU_DSM_POWER, arg);
	वापस 0;
पूर्ण

अटल पूर्णांक nouveau_dsm_चयनto(क्रमागत vga_चयनeroo_client_id id)
अणु
	अगर (!nouveau_dsm_priv.dsm_detected)
		वापस 0;
	अगर (id == VGA_SWITCHEROO_IGD)
		वापस nouveau_dsm_चयन_mux(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_LED_STAMINA);
	अन्यथा
		वापस nouveau_dsm_चयन_mux(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_LED_SPEED);
पूर्ण

अटल पूर्णांक nouveau_dsm_घातer_state(क्रमागत vga_चयनeroo_client_id id,
				   क्रमागत vga_चयनeroo_state state)
अणु
	अगर (id == VGA_SWITCHEROO_IGD)
		वापस 0;

	/* Optimus laptops have the card alपढ़ोy disabled in
	 * nouveau_चयनeroo_set_state */
	अगर (!nouveau_dsm_priv.dsm_detected)
		वापस 0;

	वापस nouveau_dsm_set_discrete_state(nouveau_dsm_priv.dhandle, state);
पूर्ण

अटल क्रमागत vga_चयनeroo_client_id nouveau_dsm_get_client_id(काष्ठा pci_dev *pdev)
अणु
	/* easy option one - पूर्णांकel venकरोr ID means Integrated */
	अगर (pdev->venकरोr == PCI_VENDOR_ID_INTEL)
		वापस VGA_SWITCHEROO_IGD;

	/* is this device on Bus 0? - this may need improving */
	अगर (pdev->bus->number == 0)
		वापस VGA_SWITCHEROO_IGD;

	वापस VGA_SWITCHEROO_DIS;
पूर्ण

अटल स्थिर काष्ठा vga_चयनeroo_handler nouveau_dsm_handler = अणु
	.चयनto = nouveau_dsm_चयनto,
	.घातer_state = nouveau_dsm_घातer_state,
	.get_client_id = nouveau_dsm_get_client_id,
पूर्ण;

अटल व्योम nouveau_dsm_pci_probe(काष्ठा pci_dev *pdev, acpi_handle *dhandle_out,
				  bool *has_mux, bool *has_opt,
				  bool *has_opt_flags, bool *has_pr3)
अणु
	acpi_handle dhandle;
	bool supports_mux;
	पूर्णांक optimus_funcs;
	काष्ठा pci_dev *parent_pdev;

	*has_pr3 = false;
	parent_pdev = pci_upstream_bridge(pdev);
	अगर (parent_pdev) अणु
		अगर (parent_pdev->bridge_d3)
			*has_pr3 = pci_pr3_present(parent_pdev);
		अन्यथा
			pci_d3cold_disable(pdev);
	पूर्ण

	dhandle = ACPI_HANDLE(&pdev->dev);
	अगर (!dhandle)
		वापस;

	अगर (!acpi_has_method(dhandle, "_DSM"))
		वापस;

	supports_mux = acpi_check_dsm(dhandle, &nouveau_dsm_muid, 0x00000102,
				      1 << NOUVEAU_DSM_POWER);
	optimus_funcs = nouveau_dsm_get_optimus_functions(dhandle);

	/* Does not look like a Nvidia device. */
	अगर (!supports_mux && !optimus_funcs)
		वापस;

	*dhandle_out = dhandle;
	*has_mux = supports_mux;
	*has_opt = !!optimus_funcs;
	*has_opt_flags = optimus_funcs & (1 << NOUVEAU_DSM_OPTIMUS_FLAGS);

	अगर (optimus_funcs) अणु
		uपूर्णांक32_t result;
		nouveau_optimus_dsm(dhandle, NOUVEAU_DSM_OPTIMUS_CAPS, 0,
				    &result);
		dev_info(&pdev->dev, "optimus capabilities: %s, status %s%s\n",
			 (result & OPTIMUS_ENABLED) ? "enabled" : "disabled",
			 (result & OPTIMUS_DYNAMIC_PWR_CAP) ? "dynamic power, " : "",
			 (result & OPTIMUS_HDA_CODEC_MASK) ? "hda bios codec supported" : "");
	पूर्ण
पूर्ण

अटल bool nouveau_dsm_detect(व्योम)
अणु
	अक्षर acpi_method_name[255] = अणु 0 पूर्ण;
	काष्ठा acpi_buffer buffer = अणुमाप(acpi_method_name), acpi_method_nameपूर्ण;
	काष्ठा pci_dev *pdev = शून्य;
	acpi_handle dhandle = शून्य;
	bool has_mux = false;
	bool has_optimus = false;
	bool has_optimus_flags = false;
	bool has_घातer_resources = false;
	पूर्णांक vga_count = 0;
	bool guid_valid;
	bool ret = false;

	/* lookup the MXM GUID */
	guid_valid = mxm_wmi_supported();

	अगर (guid_valid)
		prपूर्णांकk("MXM: GUID detected in BIOS\n");

	/* now करो DSM detection */
	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != शून्य) अणु
		vga_count++;

		nouveau_dsm_pci_probe(pdev, &dhandle, &has_mux, &has_optimus,
				      &has_optimus_flags, &has_घातer_resources);
	पूर्ण

	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_3D << 8, pdev)) != शून्य) अणु
		vga_count++;

		nouveau_dsm_pci_probe(pdev, &dhandle, &has_mux, &has_optimus,
				      &has_optimus_flags, &has_घातer_resources);
	पूर्ण

	/* find the optimus DSM or the old v1 DSM */
	अगर (has_optimus) अणु
		nouveau_dsm_priv.dhandle = dhandle;
		acpi_get_name(nouveau_dsm_priv.dhandle, ACPI_FULL_PATHNAME,
			&buffer);
		pr_info("VGA switcheroo: detected Optimus DSM method %s handle\n",
			acpi_method_name);
		अगर (has_घातer_resources)
			pr_info("nouveau: detected PR support, will not use DSM\n");
		nouveau_dsm_priv.optimus_detected = true;
		nouveau_dsm_priv.optimus_flags_detected = has_optimus_flags;
		nouveau_dsm_priv.optimus_skip_dsm = has_घातer_resources;
		ret = true;
	पूर्ण अन्यथा अगर (vga_count == 2 && has_mux && guid_valid) अणु
		nouveau_dsm_priv.dhandle = dhandle;
		acpi_get_name(nouveau_dsm_priv.dhandle, ACPI_FULL_PATHNAME,
			&buffer);
		pr_info("VGA switcheroo: detected DSM switching method %s handle\n",
			acpi_method_name);
		nouveau_dsm_priv.dsm_detected = true;
		ret = true;
	पूर्ण


	वापस ret;
पूर्ण

व्योम nouveau_रेजिस्टर_dsm_handler(व्योम)
अणु
	bool r;

	r = nouveau_dsm_detect();
	अगर (!r)
		वापस;

	vga_चयनeroo_रेजिस्टर_handler(&nouveau_dsm_handler, 0);
पूर्ण

/* Must be called क्रम Optimus models beक्रमe the card can be turned off */
व्योम nouveau_चयनeroo_optimus_dsm(व्योम)
अणु
	u32 result = 0;
	अगर (!nouveau_dsm_priv.optimus_detected || nouveau_dsm_priv.optimus_skip_dsm)
		वापस;

	अगर (nouveau_dsm_priv.optimus_flags_detected)
		nouveau_optimus_dsm(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_OPTIMUS_FLAGS,
				    0x3, &result);

	nouveau_optimus_dsm(nouveau_dsm_priv.dhandle, NOUVEAU_DSM_OPTIMUS_CAPS,
		NOUVEAU_DSM_OPTIMUS_SET_POWERDOWN, &result);

पूर्ण

व्योम nouveau_unरेजिस्टर_dsm_handler(व्योम)
अणु
	अगर (nouveau_dsm_priv.optimus_detected || nouveau_dsm_priv.dsm_detected)
		vga_चयनeroo_unरेजिस्टर_handler();
पूर्ण
#अन्यथा
व्योम nouveau_रेजिस्टर_dsm_handler(व्योम) अणुपूर्ण
व्योम nouveau_unरेजिस्टर_dsm_handler(व्योम) अणुपूर्ण
व्योम nouveau_चयनeroo_optimus_dsm(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम *
nouveau_acpi_edid(काष्ठा drm_device *dev, काष्ठा drm_connector *connector)
अणु
	काष्ठा acpi_device *acpidev;
	acpi_handle handle;
	पूर्णांक type, ret;
	व्योम *edid;

	चयन (connector->connector_type) अणु
	हाल DRM_MODE_CONNECTOR_LVDS:
	हाल DRM_MODE_CONNECTOR_eDP:
		type = ACPI_VIDEO_DISPLAY_LCD;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	handle = ACPI_HANDLE(dev->dev);
	अगर (!handle)
		वापस शून्य;

	ret = acpi_bus_get_device(handle, &acpidev);
	अगर (ret)
		वापस शून्य;

	ret = acpi_video_get_edid(acpidev, type, -1, &edid);
	अगर (ret < 0)
		वापस शून्य;

	वापस kmemdup(edid, EDID_LENGTH, GFP_KERNEL);
पूर्ण
