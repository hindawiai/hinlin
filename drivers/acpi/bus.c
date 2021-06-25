<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  acpi_bus.c - ACPI Bus Driver ($Revision: 80 $)
 *
 *  Copyright (C) 2001, 2002 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "ACPI: " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/pm.h>
#समावेश <linux/device.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/acpi.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/reboot.h>
#समावेश <linux/delay.h>
#अगर_घोषित CONFIG_X86
#समावेश <यंत्र/mpspec.h>
#समावेश <linux/dmi.h>
#पूर्ण_अगर
#समावेश <linux/acpi_iort.h>
#समावेश <linux/pci.h>
#समावेश <acpi/apei.h>
#समावेश <linux/suspend.h>

#समावेश "internal.h"

काष्ठा acpi_device *acpi_root;
काष्ठा proc_dir_entry *acpi_root_dir;
EXPORT_SYMBOL(acpi_root_dir);

#अगर_घोषित CONFIG_X86
#अगर_घोषित CONFIG_ACPI_CUSTOM_DSDT
अटल अंतरभूत पूर्णांक set_copy_dsdt(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	वापस 0;
पूर्ण
#अन्यथा
अटल पूर्णांक set_copy_dsdt(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	pr_notice("%s detected - force copy of DSDT to local memory\n", id->ident);
	acpi_gbl_copy_dsdt_locally = 1;
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा dmi_प्रणाली_id dsdt_dmi_table[] __initस्थिर = अणु
	/*
	 * Invoke DSDT corruption work-around on all Toshiba Satellite.
	 * https://bugzilla.kernel.org/show_bug.cgi?id=14679
	 */
	अणु
	 .callback = set_copy_dsdt,
	 .ident = "TOSHIBA Satellite",
	 .matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "TOSHIBA"),
		DMI_MATCH(DMI_PRODUCT_NAME, "Satellite"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

/* --------------------------------------------------------------------------
                                Device Management
   -------------------------------------------------------------------------- */

acpi_status acpi_bus_get_status_handle(acpi_handle handle,
				       अचिन्हित दीर्घ दीर्घ *sta)
अणु
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(handle, "_STA", शून्य, sta);
	अगर (ACPI_SUCCESS(status))
		वापस AE_OK;

	अगर (status == AE_NOT_FOUND) अणु
		*sta = ACPI_STA_DEVICE_PRESENT | ACPI_STA_DEVICE_ENABLED |
		       ACPI_STA_DEVICE_UI      | ACPI_STA_DEVICE_FUNCTIONING;
		वापस AE_OK;
	पूर्ण
	वापस status;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_get_status_handle);

पूर्णांक acpi_bus_get_status(काष्ठा acpi_device *device)
अणु
	acpi_status status;
	अचिन्हित दीर्घ दीर्घ sta;

	अगर (acpi_device_always_present(device)) अणु
		acpi_set_device_status(device, ACPI_STA_DEFAULT);
		वापस 0;
	पूर्ण

	/* Battery devices must have their deps met beक्रमe calling _STA */
	अगर (acpi_device_is_battery(device) && device->dep_unmet) अणु
		acpi_set_device_status(device, 0);
		वापस 0;
	पूर्ण

	status = acpi_bus_get_status_handle(device->handle, &sta);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	acpi_set_device_status(device, sta);

	अगर (device->status.functional && !device->status.present) अणु
		pr_debug("Device [%s] status [%08x]: functional but not present\n",
			 device->pnp.bus_id, (u32)sta);
	पूर्ण

	pr_debug("Device [%s] status [%08x]\n", device->pnp.bus_id, (u32)sta);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(acpi_bus_get_status);

व्योम acpi_bus_निजी_data_handler(acpi_handle handle,
				   व्योम *context)
अणु
	वापस;
पूर्ण
EXPORT_SYMBOL(acpi_bus_निजी_data_handler);

पूर्णांक acpi_bus_attach_निजी_data(acpi_handle handle, व्योम *data)
अणु
	acpi_status status;

	status = acpi_attach_data(handle,
			acpi_bus_निजी_data_handler, data);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_debug(handle, "Error attaching device data\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_attach_निजी_data);

पूर्णांक acpi_bus_get_निजी_data(acpi_handle handle, व्योम **data)
अणु
	acpi_status status;

	अगर (!data)
		वापस -EINVAL;

	status = acpi_get_data(handle, acpi_bus_निजी_data_handler, data);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_handle_debug(handle, "No context for object\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_get_निजी_data);

व्योम acpi_bus_detach_निजी_data(acpi_handle handle)
अणु
	acpi_detach_data(handle, acpi_bus_निजी_data_handler);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_detach_निजी_data);

अटल व्योम acpi_prपूर्णांक_osc_error(acpi_handle handle,
				 काष्ठा acpi_osc_context *context, अक्षर *error)
अणु
	पूर्णांक i;

	acpi_handle_debug(handle, "(%s): %s\n", context->uuid_str, error);

	pr_debug("_OSC request data:");
	क्रम (i = 0; i < context->cap.length; i += माप(u32))
		pr_debug(" %x", *((u32 *)(context->cap.poपूर्णांकer + i)));

	pr_debug("\n");
पूर्ण

acpi_status acpi_run_osc(acpi_handle handle, काष्ठा acpi_osc_context *context)
अणु
	acpi_status status;
	काष्ठा acpi_object_list input;
	जोड़ acpi_object in_params[4];
	जोड़ acpi_object *out_obj;
	guid_t guid;
	u32 errors;
	काष्ठा acpi_buffer output = अणुACPI_ALLOCATE_BUFFER, शून्यपूर्ण;

	अगर (!context)
		वापस AE_ERROR;
	अगर (guid_parse(context->uuid_str, &guid))
		वापस AE_ERROR;
	context->ret.length = ACPI_ALLOCATE_BUFFER;
	context->ret.poपूर्णांकer = शून्य;

	/* Setting up input parameters */
	input.count = 4;
	input.poपूर्णांकer = in_params;
	in_params[0].type 		= ACPI_TYPE_BUFFER;
	in_params[0].buffer.length 	= 16;
	in_params[0].buffer.poपूर्णांकer	= (u8 *)&guid;
	in_params[1].type 		= ACPI_TYPE_INTEGER;
	in_params[1].पूर्णांकeger.value 	= context->rev;
	in_params[2].type 		= ACPI_TYPE_INTEGER;
	in_params[2].पूर्णांकeger.value	= context->cap.length/माप(u32);
	in_params[3].type		= ACPI_TYPE_BUFFER;
	in_params[3].buffer.length 	= context->cap.length;
	in_params[3].buffer.poपूर्णांकer 	= context->cap.poपूर्णांकer;

	status = acpi_evaluate_object(handle, "_OSC", &input, &output);
	अगर (ACPI_FAILURE(status))
		वापस status;

	अगर (!output.length)
		वापस AE_शून्य_OBJECT;

	out_obj = output.poपूर्णांकer;
	अगर (out_obj->type != ACPI_TYPE_BUFFER
		|| out_obj->buffer.length != context->cap.length) अणु
		acpi_prपूर्णांक_osc_error(handle, context,
			"_OSC evaluation returned wrong type");
		status = AE_TYPE;
		जाओ out_kमुक्त;
	पूर्ण
	/* Need to ignore the bit0 in result code */
	errors = *((u32 *)out_obj->buffer.poपूर्णांकer) & ~(1 << 0);
	अगर (errors) अणु
		अगर (errors & OSC_REQUEST_ERROR)
			acpi_prपूर्णांक_osc_error(handle, context,
				"_OSC request failed");
		अगर (errors & OSC_INVALID_UUID_ERROR)
			acpi_prपूर्णांक_osc_error(handle, context,
				"_OSC invalid UUID");
		अगर (errors & OSC_INVALID_REVISION_ERROR)
			acpi_prपूर्णांक_osc_error(handle, context,
				"_OSC invalid revision");
		अगर (errors & OSC_CAPABILITIES_MASK_ERROR) अणु
			अगर (((u32 *)context->cap.poपूर्णांकer)[OSC_QUERY_DWORD]
			    & OSC_QUERY_ENABLE)
				जाओ out_success;
			status = AE_SUPPORT;
			जाओ out_kमुक्त;
		पूर्ण
		status = AE_ERROR;
		जाओ out_kमुक्त;
	पूर्ण
out_success:
	context->ret.length = out_obj->buffer.length;
	context->ret.poपूर्णांकer = kmemdup(out_obj->buffer.poपूर्णांकer,
				       context->ret.length, GFP_KERNEL);
	अगर (!context->ret.poपूर्णांकer) अणु
		status =  AE_NO_MEMORY;
		जाओ out_kमुक्त;
	पूर्ण
	status =  AE_OK;

out_kमुक्त:
	kमुक्त(output.poपूर्णांकer);
	अगर (status != AE_OK)
		context->ret.poपूर्णांकer = शून्य;
	वापस status;
पूर्ण
EXPORT_SYMBOL(acpi_run_osc);

bool osc_sb_apei_support_acked;

/*
 * ACPI 6.0 Section 8.4.4.2 Idle State Coordination
 * OSPM supports platक्रमm coordinated low घातer idle(LPI) states
 */
bool osc_pc_lpi_support_confirmed;
EXPORT_SYMBOL_GPL(osc_pc_lpi_support_confirmed);

/*
 * ACPI 6.4 Operating System Capabilities क्रम USB.
 */
bool osc_sb_native_usb4_support_confirmed;
EXPORT_SYMBOL_GPL(osc_sb_native_usb4_support_confirmed);

अटल u8 sb_uuid_str[] = "0811B06E-4A27-44F9-8D60-3CBBC22E7B48";
अटल व्योम acpi_bus_osc_negotiate_platक्रमm_control(व्योम)
अणु
	u32 capbuf[2], *capbuf_ret;
	काष्ठा acpi_osc_context context = अणु
		.uuid_str = sb_uuid_str,
		.rev = 1,
		.cap.length = 8,
		.cap.poपूर्णांकer = capbuf,
	पूर्ण;
	acpi_handle handle;

	capbuf[OSC_QUERY_DWORD] = OSC_QUERY_ENABLE;
	capbuf[OSC_SUPPORT_DWORD] = OSC_SB_PR3_SUPPORT; /* _PR3 is in use */
	अगर (IS_ENABLED(CONFIG_ACPI_PROCESSOR_AGGREGATOR))
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_PAD_SUPPORT;
	अगर (IS_ENABLED(CONFIG_ACPI_PROCESSOR))
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_PPC_OST_SUPPORT;

	capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_HOTPLUG_OST_SUPPORT;
	capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_PCLPI_SUPPORT;

#अगर_घोषित CONFIG_ARM64
	capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_GENERIC_INITIATOR_SUPPORT;
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86
	capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_GENERIC_INITIATOR_SUPPORT;
	अगर (boot_cpu_has(X86_FEATURE_HWP)) अणु
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_CPC_SUPPORT;
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_CPCV2_SUPPORT;
	पूर्ण
#पूर्ण_अगर

	अगर (IS_ENABLED(CONFIG_SCHED_MC_PRIO))
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_CPC_DIVERSE_HIGH_SUPPORT;

	अगर (IS_ENABLED(CONFIG_USB4))
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_NATIVE_USB4_SUPPORT;

	अगर (!ghes_disable)
		capbuf[OSC_SUPPORT_DWORD] |= OSC_SB_APEI_SUPPORT;
	अगर (ACPI_FAILURE(acpi_get_handle(शून्य, "\\_SB", &handle)))
		वापस;

	अगर (ACPI_FAILURE(acpi_run_osc(handle, &context)))
		वापस;

	kमुक्त(context.ret.poपूर्णांकer);

	/* Now run _OSC again with query flag clear */
	capbuf[OSC_QUERY_DWORD] = 0;

	अगर (ACPI_FAILURE(acpi_run_osc(handle, &context)))
		वापस;

	capbuf_ret = context.ret.poपूर्णांकer;
	osc_sb_apei_support_acked =
		capbuf_ret[OSC_SUPPORT_DWORD] & OSC_SB_APEI_SUPPORT;
	osc_pc_lpi_support_confirmed =
		capbuf_ret[OSC_SUPPORT_DWORD] & OSC_SB_PCLPI_SUPPORT;
	osc_sb_native_usb4_support_confirmed =
		capbuf_ret[OSC_SUPPORT_DWORD] & OSC_SB_NATIVE_USB4_SUPPORT;

	kमुक्त(context.ret.poपूर्णांकer);
पूर्ण

/*
 * Native control of USB4 capabilities. If any of the tunneling bits is
 * set it means OS is in control and we use software based connection
 * manager.
 */
u32 osc_sb_native_usb4_control;
EXPORT_SYMBOL_GPL(osc_sb_native_usb4_control);

अटल व्योम acpi_bus_decode_usb_osc(स्थिर अक्षर *msg, u32 bits)
अणु
	prपूर्णांकk(KERN_INFO PREFIX "%s USB3%c DisplayPort%c PCIe%c XDomain%c\n", msg,
	       (bits & OSC_USB_USB3_TUNNELING) ? '+' : '-',
	       (bits & OSC_USB_DP_TUNNELING) ? '+' : '-',
	       (bits & OSC_USB_PCIE_TUNNELING) ? '+' : '-',
	       (bits & OSC_USB_XDOMAIN) ? '+' : '-');
पूर्ण

अटल u8 sb_usb_uuid_str[] = "23A0D13A-26AB-486C-9C5F-0FFA525A575A";
अटल व्योम acpi_bus_osc_negotiate_usb_control(व्योम)
अणु
	u32 capbuf[3];
	काष्ठा acpi_osc_context context = अणु
		.uuid_str = sb_usb_uuid_str,
		.rev = 1,
		.cap.length = माप(capbuf),
		.cap.poपूर्णांकer = capbuf,
	पूर्ण;
	acpi_handle handle;
	acpi_status status;
	u32 control;

	अगर (!osc_sb_native_usb4_support_confirmed)
		वापस;

	अगर (ACPI_FAILURE(acpi_get_handle(शून्य, "\\_SB", &handle)))
		वापस;

	control = OSC_USB_USB3_TUNNELING | OSC_USB_DP_TUNNELING |
		  OSC_USB_PCIE_TUNNELING | OSC_USB_XDOMAIN;

	capbuf[OSC_QUERY_DWORD] = 0;
	capbuf[OSC_SUPPORT_DWORD] = 0;
	capbuf[OSC_CONTROL_DWORD] = control;

	status = acpi_run_osc(handle, &context);
	अगर (ACPI_FAILURE(status))
		वापस;

	अगर (context.ret.length != माप(capbuf)) अणु
		prपूर्णांकk(KERN_INFO PREFIX "USB4 _OSC: returned invalid length buffer\n");
		जाओ out_मुक्त;
	पूर्ण

	osc_sb_native_usb4_control =
		control & ((u32 *)context.ret.poपूर्णांकer)[OSC_CONTROL_DWORD];

	acpi_bus_decode_usb_osc("USB4 _OSC: OS supports", control);
	acpi_bus_decode_usb_osc("USB4 _OSC: OS controls",
				osc_sb_native_usb4_control);

out_मुक्त:
	kमुक्त(context.ret.poपूर्णांकer);
पूर्ण

/* --------------------------------------------------------------------------
                             Notअगरication Handling
   -------------------------------------------------------------------------- */

/**
 * acpi_bus_notअगरy
 * ---------------
 * Callback क्रम all 'system-level' device notअगरications (values 0x00-0x7F).
 */
अटल व्योम acpi_bus_notअगरy(acpi_handle handle, u32 type, व्योम *data)
अणु
	काष्ठा acpi_device *adev;
	काष्ठा acpi_driver *driver;
	u32 ost_code = ACPI_OST_SC_NON_SPECIFIC_FAILURE;
	bool hotplug_event = false;

	चयन (type) अणु
	हाल ACPI_NOTIFY_BUS_CHECK:
		acpi_handle_debug(handle, "ACPI_NOTIFY_BUS_CHECK event\n");
		hotplug_event = true;
		अवरोध;

	हाल ACPI_NOTIFY_DEVICE_CHECK:
		acpi_handle_debug(handle, "ACPI_NOTIFY_DEVICE_CHECK event\n");
		hotplug_event = true;
		अवरोध;

	हाल ACPI_NOTIFY_DEVICE_WAKE:
		acpi_handle_debug(handle, "ACPI_NOTIFY_DEVICE_WAKE event\n");
		अवरोध;

	हाल ACPI_NOTIFY_EJECT_REQUEST:
		acpi_handle_debug(handle, "ACPI_NOTIFY_EJECT_REQUEST event\n");
		hotplug_event = true;
		अवरोध;

	हाल ACPI_NOTIFY_DEVICE_CHECK_LIGHT:
		acpi_handle_debug(handle, "ACPI_NOTIFY_DEVICE_CHECK_LIGHT event\n");
		/* TBD: Exactly what करोes 'light' mean? */
		अवरोध;

	हाल ACPI_NOTIFY_FREQUENCY_MISMATCH:
		acpi_handle_err(handle, "Device cannot be configured due "
				"to a frequency mismatch\n");
		अवरोध;

	हाल ACPI_NOTIFY_BUS_MODE_MISMATCH:
		acpi_handle_err(handle, "Device cannot be configured due "
				"to a bus mode mismatch\n");
		अवरोध;

	हाल ACPI_NOTIFY_POWER_FAULT:
		acpi_handle_err(handle, "Device has suffered a power fault\n");
		अवरोध;

	शेष:
		acpi_handle_debug(handle, "Unknown event type 0x%x\n", type);
		अवरोध;
	पूर्ण

	adev = acpi_bus_get_acpi_device(handle);
	अगर (!adev)
		जाओ err;

	driver = adev->driver;
	अगर (driver && driver->ops.notअगरy &&
	    (driver->flags & ACPI_DRIVER_ALL_NOTIFY_EVENTS))
		driver->ops.notअगरy(adev, type);

	अगर (!hotplug_event) अणु
		acpi_bus_put_acpi_device(adev);
		वापस;
	पूर्ण

	अगर (ACPI_SUCCESS(acpi_hotplug_schedule(adev, type)))
		वापस;

	acpi_bus_put_acpi_device(adev);

 err:
	acpi_evaluate_ost(handle, type, ost_code, शून्य);
पूर्ण

अटल व्योम acpi_device_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	काष्ठा acpi_device *device = data;

	device->driver->ops.notअगरy(device, event);
पूर्ण

अटल व्योम acpi_device_notअगरy_fixed(व्योम *data)
अणु
	काष्ठा acpi_device *device = data;

	/* Fixed hardware devices have no handles */
	acpi_device_notअगरy(शून्य, ACPI_FIXED_HARDWARE_EVENT, device);
पूर्ण

अटल u32 acpi_device_fixed_event(व्योम *data)
अणु
	acpi_os_execute(OSL_NOTIFY_HANDLER, acpi_device_notअगरy_fixed, data);
	वापस ACPI_INTERRUPT_HANDLED;
पूर्ण

अटल पूर्णांक acpi_device_install_notअगरy_handler(काष्ठा acpi_device *device)
अणु
	acpi_status status;

	अगर (device->device_type == ACPI_BUS_TYPE_POWER_BUTTON)
		status =
		    acpi_install_fixed_event_handler(ACPI_EVENT_POWER_BUTTON,
						     acpi_device_fixed_event,
						     device);
	अन्यथा अगर (device->device_type == ACPI_BUS_TYPE_SLEEP_BUTTON)
		status =
		    acpi_install_fixed_event_handler(ACPI_EVENT_SLEEP_BUTTON,
						     acpi_device_fixed_event,
						     device);
	अन्यथा
		status = acpi_install_notअगरy_handler(device->handle,
						     ACPI_DEVICE_NOTIFY,
						     acpi_device_notअगरy,
						     device);

	अगर (ACPI_FAILURE(status))
		वापस -EINVAL;
	वापस 0;
पूर्ण

अटल व्योम acpi_device_हटाओ_notअगरy_handler(काष्ठा acpi_device *device)
अणु
	अगर (device->device_type == ACPI_BUS_TYPE_POWER_BUTTON)
		acpi_हटाओ_fixed_event_handler(ACPI_EVENT_POWER_BUTTON,
						acpi_device_fixed_event);
	अन्यथा अगर (device->device_type == ACPI_BUS_TYPE_SLEEP_BUTTON)
		acpi_हटाओ_fixed_event_handler(ACPI_EVENT_SLEEP_BUTTON,
						acpi_device_fixed_event);
	अन्यथा
		acpi_हटाओ_notअगरy_handler(device->handle, ACPI_DEVICE_NOTIFY,
					   acpi_device_notअगरy);
पूर्ण

/* Handle events targeting \_SB device (at present only graceful shutकरोwn) */

#घोषणा ACPI_SB_NOTIFY_SHUTDOWN_REQUEST 0x81
#घोषणा ACPI_SB_INDICATE_INTERVAL	10000

अटल व्योम sb_notअगरy_work(काष्ठा work_काष्ठा *dummy)
अणु
	acpi_handle sb_handle;

	orderly_घातeroff(true);

	/*
	 * After initiating graceful shutकरोwn, the ACPI spec requires OSPM
	 * to evaluate _OST method once every 10seconds to indicate that
	 * the shutकरोwn is in progress
	 */
	acpi_get_handle(शून्य, "\\_SB", &sb_handle);
	जबतक (1) अणु
		pr_info("Graceful shutdown in progress.\n");
		acpi_evaluate_ost(sb_handle, ACPI_OST_EC_OSPM_SHUTDOWN,
				ACPI_OST_SC_OS_SHUTDOWN_IN_PROGRESS, शून्य);
		msleep(ACPI_SB_INDICATE_INTERVAL);
	पूर्ण
पूर्ण

अटल व्योम acpi_sb_notअगरy(acpi_handle handle, u32 event, व्योम *data)
अणु
	अटल DECLARE_WORK(acpi_sb_work, sb_notअगरy_work);

	अगर (event == ACPI_SB_NOTIFY_SHUTDOWN_REQUEST) अणु
		अगर (!work_busy(&acpi_sb_work))
			schedule_work(&acpi_sb_work);
	पूर्ण अन्यथा
		pr_warn("event %x is not supported by \\_SB device\n", event);
पूर्ण

अटल पूर्णांक __init acpi_setup_sb_notअगरy_handler(व्योम)
अणु
	acpi_handle sb_handle;

	अगर (ACPI_FAILURE(acpi_get_handle(शून्य, "\\_SB", &sb_handle)))
		वापस -ENXIO;

	अगर (ACPI_FAILURE(acpi_install_notअगरy_handler(sb_handle, ACPI_DEVICE_NOTIFY,
						acpi_sb_notअगरy, शून्य)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* --------------------------------------------------------------------------
                             Device Matching
   -------------------------------------------------------------------------- */

/**
 * acpi_get_first_physical_node - Get first physical node of an ACPI device
 * @adev:	ACPI device in question
 *
 * Return: First physical node of ACPI device @adev
 */
काष्ठा device *acpi_get_first_physical_node(काष्ठा acpi_device *adev)
अणु
	काष्ठा mutex *physical_node_lock = &adev->physical_node_lock;
	काष्ठा device *phys_dev;

	mutex_lock(physical_node_lock);
	अगर (list_empty(&adev->physical_node_list)) अणु
		phys_dev = शून्य;
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा acpi_device_physical_node *node;

		node = list_first_entry(&adev->physical_node_list,
					काष्ठा acpi_device_physical_node, node);

		phys_dev = node->dev;
	पूर्ण
	mutex_unlock(physical_node_lock);
	वापस phys_dev;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_get_first_physical_node);

अटल काष्ठा acpi_device *acpi_primary_dev_companion(काष्ठा acpi_device *adev,
						      स्थिर काष्ठा device *dev)
अणु
	स्थिर काष्ठा device *phys_dev = acpi_get_first_physical_node(adev);

	वापस phys_dev && phys_dev == dev ? adev : शून्य;
पूर्ण

/**
 * acpi_device_is_first_physical_node - Is given dev first physical node
 * @adev: ACPI companion device
 * @dev: Physical device to check
 *
 * Function checks अगर given @dev is the first physical devices attached to
 * the ACPI companion device. This distinction is needed in some हालs
 * where the same companion device is shared between many physical devices.
 *
 * Note that the caller have to provide valid @adev poपूर्णांकer.
 */
bool acpi_device_is_first_physical_node(काष्ठा acpi_device *adev,
					स्थिर काष्ठा device *dev)
अणु
	वापस !!acpi_primary_dev_companion(adev, dev);
पूर्ण

/*
 * acpi_companion_match() - Can we match via ACPI companion device
 * @dev: Device in question
 *
 * Check अगर the given device has an ACPI companion and अगर that companion has
 * a valid list of PNP IDs, and अगर the device is the first (primary) physical
 * device associated with it.  Return the companion poपूर्णांकer अगर that's the हाल
 * or शून्य otherwise.
 *
 * If multiple physical devices are attached to a single ACPI companion, we need
 * to be careful.  The usage scenario क्रम this kind of relationship is that all
 * of the physical devices in question use resources provided by the ACPI
 * companion.  A typical हाल is an MFD device where all the sub-devices share
 * the parent's ACPI companion.  In such हालs we can only allow the primary
 * (first) physical device to be matched with the help of the companion's PNP
 * IDs.
 *
 * Additional physical devices sharing the ACPI companion can still use
 * resources available from it but they will be matched normally using functions
 * provided by their bus types (and analogously क्रम their modalias).
 */
काष्ठा acpi_device *acpi_companion_match(स्थिर काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev;

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस शून्य;

	अगर (list_empty(&adev->pnp.ids))
		वापस शून्य;

	वापस acpi_primary_dev_companion(adev, dev);
पूर्ण

/**
 * acpi_of_match_device - Match device object using the "compatible" property.
 * @adev: ACPI device object to match.
 * @of_match_table: List of device IDs to match against.
 * @of_id: OF ID अगर matched
 *
 * If @dev has an ACPI companion which has ACPI_DT_NAMESPACE_HID in its list of
 * identअगरiers and a _DSD object with the "compatible" property, use that
 * property to match against the given list of identअगरiers.
 */
अटल bool acpi_of_match_device(काष्ठा acpi_device *adev,
				 स्थिर काष्ठा of_device_id *of_match_table,
				 स्थिर काष्ठा of_device_id **of_id)
अणु
	स्थिर जोड़ acpi_object *of_compatible, *obj;
	पूर्णांक i, nval;

	अगर (!adev)
		वापस false;

	of_compatible = adev->data.of_compatible;
	अगर (!of_match_table || !of_compatible)
		वापस false;

	अगर (of_compatible->type == ACPI_TYPE_PACKAGE) अणु
		nval = of_compatible->package.count;
		obj = of_compatible->package.elements;
	पूर्ण अन्यथा अणु /* Must be ACPI_TYPE_STRING. */
		nval = 1;
		obj = of_compatible;
	पूर्ण
	/* Now we can look क्रम the driver DT compatible strings */
	क्रम (i = 0; i < nval; i++, obj++) अणु
		स्थिर काष्ठा of_device_id *id;

		क्रम (id = of_match_table; id->compatible[0]; id++)
			अगर (!strहालcmp(obj->string.poपूर्णांकer, id->compatible)) अणु
				अगर (of_id)
					*of_id = id;
				वापस true;
			पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool acpi_of_modalias(काष्ठा acpi_device *adev,
			     अक्षर *modalias, माप_प्रकार len)
अणु
	स्थिर जोड़ acpi_object *of_compatible;
	स्थिर जोड़ acpi_object *obj;
	स्थिर अक्षर *str, *chr;

	of_compatible = adev->data.of_compatible;
	अगर (!of_compatible)
		वापस false;

	अगर (of_compatible->type == ACPI_TYPE_PACKAGE)
		obj = of_compatible->package.elements;
	अन्यथा /* Must be ACPI_TYPE_STRING. */
		obj = of_compatible;

	str = obj->string.poपूर्णांकer;
	chr = म_अक्षर(str, ',');
	strlcpy(modalias, chr ? chr + 1 : str, len);

	वापस true;
पूर्ण

/**
 * acpi_set_modalias - Set modalias using "compatible" property or supplied ID
 * @adev:	ACPI device object to match
 * @शेष_id:	ID string to use as शेष अगर no compatible string found
 * @modalias:   Poपूर्णांकer to buffer that modalias value will be copied पूर्णांकo
 * @len:	Length of modalias buffer
 *
 * This is a counterpart of of_modalias_node() क्रम काष्ठा acpi_device objects.
 * If there is a compatible string क्रम @adev, it will be copied to @modalias
 * with the venकरोr prefix stripped; otherwise, @शेष_id will be used.
 */
व्योम acpi_set_modalias(काष्ठा acpi_device *adev, स्थिर अक्षर *शेष_id,
		       अक्षर *modalias, माप_प्रकार len)
अणु
	अगर (!acpi_of_modalias(adev, modalias, len))
		strlcpy(modalias, शेष_id, len);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_set_modalias);

अटल bool __acpi_match_device_cls(स्थिर काष्ठा acpi_device_id *id,
				    काष्ठा acpi_hardware_id *hwid)
अणु
	पूर्णांक i, msk, byte_shअगरt;
	अक्षर buf[3];

	अगर (!id->cls)
		वापस false;

	/* Apply class-code biपंचांगask, beक्रमe checking each class-code byte */
	क्रम (i = 1; i <= 3; i++) अणु
		byte_shअगरt = 8 * (3 - i);
		msk = (id->cls_msk >> byte_shअगरt) & 0xFF;
		अगर (!msk)
			जारी;

		प्र_लिखो(buf, "%02x", (id->cls >> byte_shअगरt) & msk);
		अगर (म_भेदन(buf, &hwid->id[(i - 1) * 2], 2))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool __acpi_match_device(काष्ठा acpi_device *device,
				स्थिर काष्ठा acpi_device_id *acpi_ids,
				स्थिर काष्ठा of_device_id *of_ids,
				स्थिर काष्ठा acpi_device_id **acpi_id,
				स्थिर काष्ठा of_device_id **of_id)
अणु
	स्थिर काष्ठा acpi_device_id *id;
	काष्ठा acpi_hardware_id *hwid;

	/*
	 * If the device is not present, it is unnecessary to load device
	 * driver क्रम it.
	 */
	अगर (!device || !device->status.present)
		वापस false;

	list_क्रम_each_entry(hwid, &device->pnp.ids, list) अणु
		/* First, check the ACPI/PNP IDs provided by the caller. */
		अगर (acpi_ids) अणु
			क्रम (id = acpi_ids; id->id[0] || id->cls; id++) अणु
				अगर (id->id[0] && !म_भेद((अक्षर *)id->id, hwid->id))
					जाओ out_acpi_match;
				अगर (id->cls && __acpi_match_device_cls(id, hwid))
					जाओ out_acpi_match;
			पूर्ण
		पूर्ण

		/*
		 * Next, check ACPI_DT_NAMESPACE_HID and try to match the
		 * "compatible" property अगर found.
		 */
		अगर (!म_भेद(ACPI_DT_NAMESPACE_HID, hwid->id))
			वापस acpi_of_match_device(device, of_ids, of_id);
	पूर्ण
	वापस false;

out_acpi_match:
	अगर (acpi_id)
		*acpi_id = id;
	वापस true;
पूर्ण

/**
 * acpi_match_device - Match a काष्ठा device against a given list of ACPI IDs
 * @ids: Array of काष्ठा acpi_device_id object to match against.
 * @dev: The device काष्ठाure to match.
 *
 * Check अगर @dev has a valid ACPI handle and अगर there is a काष्ठा acpi_device
 * object क्रम that handle and use that object to match against a given list of
 * device IDs.
 *
 * Return a poपूर्णांकer to the first matching ID on success or %शून्य on failure.
 */
स्थिर काष्ठा acpi_device_id *acpi_match_device(स्थिर काष्ठा acpi_device_id *ids,
					       स्थिर काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *id = शून्य;

	__acpi_match_device(acpi_companion_match(dev), ids, शून्य, &id, शून्य);
	वापस id;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_match_device);

अटल स्थिर व्योम *acpi_of_device_get_match_data(स्थिर काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	स्थिर काष्ठा of_device_id *match = शून्य;

	अगर (!acpi_of_match_device(adev, dev->driver->of_match_table, &match))
		वापस शून्य;

	वापस match->data;
पूर्ण

स्थिर व्योम *acpi_device_get_match_data(स्थिर काष्ठा device *dev)
अणु
	स्थिर काष्ठा acpi_device_id *match;

	अगर (!dev->driver->acpi_match_table)
		वापस acpi_of_device_get_match_data(dev);

	match = acpi_match_device(dev->driver->acpi_match_table, dev);
	अगर (!match)
		वापस शून्य;

	वापस (स्थिर व्योम *)match->driver_data;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_device_get_match_data);

पूर्णांक acpi_match_device_ids(काष्ठा acpi_device *device,
			  स्थिर काष्ठा acpi_device_id *ids)
अणु
	वापस __acpi_match_device(device, ids, शून्य, शून्य, शून्य) ? 0 : -ENOENT;
पूर्ण
EXPORT_SYMBOL(acpi_match_device_ids);

bool acpi_driver_match_device(काष्ठा device *dev,
			      स्थिर काष्ठा device_driver *drv)
अणु
	अगर (!drv->acpi_match_table)
		वापस acpi_of_match_device(ACPI_COMPANION(dev),
					    drv->of_match_table,
					    शून्य);

	वापस __acpi_match_device(acpi_companion_match(dev),
				   drv->acpi_match_table, drv->of_match_table,
				   शून्य, शून्य);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_driver_match_device);

/* --------------------------------------------------------------------------
                              ACPI Driver Management
   -------------------------------------------------------------------------- */

/**
 * acpi_bus_रेजिस्टर_driver - रेजिस्टर a driver with the ACPI bus
 * @driver: driver being रेजिस्टरed
 *
 * Registers a driver with the ACPI bus.  Searches the namespace क्रम all
 * devices that match the driver's criteria and binds.  Returns zero क्रम
 * success or a negative error status क्रम failure.
 */
पूर्णांक acpi_bus_रेजिस्टर_driver(काष्ठा acpi_driver *driver)
अणु
	पूर्णांक ret;

	अगर (acpi_disabled)
		वापस -ENODEV;
	driver->drv.name = driver->name;
	driver->drv.bus = &acpi_bus_type;
	driver->drv.owner = driver->owner;

	ret = driver_रेजिस्टर(&driver->drv);
	वापस ret;
पूर्ण

EXPORT_SYMBOL(acpi_bus_रेजिस्टर_driver);

/**
 * acpi_bus_unरेजिस्टर_driver - unरेजिस्टरs a driver with the ACPI bus
 * @driver: driver to unरेजिस्टर
 *
 * Unरेजिस्टरs a driver with the ACPI bus.  Searches the namespace क्रम all
 * devices that match the driver's criteria and unbinds.
 */
व्योम acpi_bus_unरेजिस्टर_driver(काष्ठा acpi_driver *driver)
अणु
	driver_unरेजिस्टर(&driver->drv);
पूर्ण

EXPORT_SYMBOL(acpi_bus_unरेजिस्टर_driver);

/* --------------------------------------------------------------------------
                              ACPI Bus operations
   -------------------------------------------------------------------------- */

अटल पूर्णांक acpi_bus_match(काष्ठा device *dev, काष्ठा device_driver *drv)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_driver *acpi_drv = to_acpi_driver(drv);

	वापस acpi_dev->flags.match_driver
		&& !acpi_match_device_ids(acpi_dev, acpi_drv->ids);
पूर्ण

अटल पूर्णांक acpi_device_uevent(काष्ठा device *dev, काष्ठा kobj_uevent_env *env)
अणु
	वापस __acpi_device_uevent_modalias(to_acpi_device(dev), env);
पूर्ण

अटल पूर्णांक acpi_device_probe(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_driver *acpi_drv = to_acpi_driver(dev->driver);
	पूर्णांक ret;

	अगर (acpi_dev->handler && !acpi_is_pnp_device(acpi_dev))
		वापस -EINVAL;

	अगर (!acpi_drv->ops.add)
		वापस -ENOSYS;

	ret = acpi_drv->ops.add(acpi_dev);
	अगर (ret)
		वापस ret;

	acpi_dev->driver = acpi_drv;

	pr_debug("Driver [%s] successfully bound to device [%s]\n",
		 acpi_drv->name, acpi_dev->pnp.bus_id);

	अगर (acpi_drv->ops.notअगरy) अणु
		ret = acpi_device_install_notअगरy_handler(acpi_dev);
		अगर (ret) अणु
			अगर (acpi_drv->ops.हटाओ)
				acpi_drv->ops.हटाओ(acpi_dev);

			acpi_dev->driver = शून्य;
			acpi_dev->driver_data = शून्य;
			वापस ret;
		पूर्ण
	पूर्ण

	pr_debug("Found driver [%s] for device [%s]\n", acpi_drv->name,
		 acpi_dev->pnp.bus_id);

	get_device(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_device_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *acpi_dev = to_acpi_device(dev);
	काष्ठा acpi_driver *acpi_drv = acpi_dev->driver;

	अगर (acpi_drv) अणु
		अगर (acpi_drv->ops.notअगरy)
			acpi_device_हटाओ_notअगरy_handler(acpi_dev);
		अगर (acpi_drv->ops.हटाओ)
			acpi_drv->ops.हटाओ(acpi_dev);
	पूर्ण
	acpi_dev->driver = शून्य;
	acpi_dev->driver_data = शून्य;

	put_device(dev);
	वापस 0;
पूर्ण

काष्ठा bus_type acpi_bus_type = अणु
	.name		= "acpi",
	.match		= acpi_bus_match,
	.probe		= acpi_device_probe,
	.हटाओ		= acpi_device_हटाओ,
	.uevent		= acpi_device_uevent,
पूर्ण;

/* --------------------------------------------------------------------------
                             Initialization/Cleanup
   -------------------------------------------------------------------------- */

अटल पूर्णांक __init acpi_bus_init_irq(व्योम)
अणु
	acpi_status status;
	अक्षर *message = शून्य;


	/*
	 * Let the प्रणाली know what पूर्णांकerrupt model we are using by
	 * evaluating the \_PIC object, अगर exists.
	 */

	चयन (acpi_irq_model) अणु
	हाल ACPI_IRQ_MODEL_PIC:
		message = "PIC";
		अवरोध;
	हाल ACPI_IRQ_MODEL_IOAPIC:
		message = "IOAPIC";
		अवरोध;
	हाल ACPI_IRQ_MODEL_IOSAPIC:
		message = "IOSAPIC";
		अवरोध;
	हाल ACPI_IRQ_MODEL_GIC:
		message = "GIC";
		अवरोध;
	हाल ACPI_IRQ_MODEL_PLATFORM:
		message = "platform specific model";
		अवरोध;
	शेष:
		pr_info("Unknown interrupt routing model\n");
		वापस -ENODEV;
	पूर्ण

	pr_info("Using %s for interrupt routing\n", message);

	status = acpi_execute_simple_method(शून्य, "\\_PIC", acpi_irq_model);
	अगर (ACPI_FAILURE(status) && (status != AE_NOT_FOUND)) अणु
		pr_info("_PIC evaluation failed: %s\n", acpi_क्रमmat_exception(status));
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * acpi_early_init - Initialize ACPICA and populate the ACPI namespace.
 *
 * The ACPI tables are accessible after this, but the handling of events has not
 * been initialized and the global lock is not available yet, so AML should not
 * be executed at this poपूर्णांक.
 *
 * Doing this beक्रमe चयनing the EFI runसमय services to भव mode allows
 * the EfiBootServices memory to be मुक्तd slightly earlier on boot.
 */
व्योम __init acpi_early_init(व्योम)
अणु
	acpi_status status;

	अगर (acpi_disabled)
		वापस;

	pr_info("Core revision %08x\n", ACPI_CA_VERSION);

	/* enable workarounds, unless strict ACPI spec. compliance */
	अगर (!acpi_strict)
		acpi_gbl_enable_पूर्णांकerpreter_slack = TRUE;

	acpi_permanent_mmap = true;

#अगर_घोषित CONFIG_X86
	/*
	 * If the machine falls पूर्णांकo the DMI check table,
	 * DSDT will be copied to memory.
	 * Note that calling dmi_check_प्रणाली() here on other architectures
	 * would not be OK because only x86 initializes dmi early enough.
	 * Thankfully only x86 प्रणालीs need such quirks क्रम now.
	 */
	dmi_check_प्रणाली(dsdt_dmi_table);
#पूर्ण_अगर

	status = acpi_पुनः_स्मृतिate_root_table();
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to reallocate ACPI tables\n");
		जाओ error0;
	पूर्ण

	status = acpi_initialize_subप्रणाली();
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to initialize the ACPI Interpreter\n");
		जाओ error0;
	पूर्ण

#अगर_घोषित CONFIG_X86
	अगर (!acpi_ioapic) अणु
		/* compatible (0) means level (3) */
		अगर (!(acpi_sci_flags & ACPI_MADT_TRIGGER_MASK)) अणु
			acpi_sci_flags &= ~ACPI_MADT_TRIGGER_MASK;
			acpi_sci_flags |= ACPI_MADT_TRIGGER_LEVEL;
		पूर्ण
		/* Set PIC-mode SCI trigger type */
		acpi_pic_sci_set_trigger(acpi_gbl_FADT.sci_पूर्णांकerrupt,
					 (acpi_sci_flags & ACPI_MADT_TRIGGER_MASK) >> 2);
	पूर्ण अन्यथा अणु
		/*
		 * now that acpi_gbl_FADT is initialized,
		 * update it with result from INT_SRC_OVR parsing
		 */
		acpi_gbl_FADT.sci_पूर्णांकerrupt = acpi_sci_override_gsi;
	पूर्ण
#पूर्ण_अगर
	वापस;

 error0:
	disable_acpi();
पूर्ण

/**
 * acpi_subप्रणाली_init - Finalize the early initialization of ACPI.
 *
 * Switch over the platक्रमm to the ACPI mode (अगर possible).
 *
 * Doing this too early is generally unsafe, but at the same समय it needs to be
 * करोne beक्रमe all things that really depend on ACPI.  The right spot appears to
 * be beक्रमe finalizing the EFI initialization.
 */
व्योम __init acpi_subप्रणाली_init(व्योम)
अणु
	acpi_status status;

	अगर (acpi_disabled)
		वापस;

	status = acpi_enable_subप्रणाली(~ACPI_NO_ACPI_ENABLE);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to enable ACPI\n");
		disable_acpi();
	पूर्ण अन्यथा अणु
		/*
		 * If the प्रणाली is using ACPI then we can be reasonably
		 * confident that any regulators are managed by the firmware
		 * so tell the regulator core it has everything it needs to
		 * know.
		 */
		regulator_has_full_स्थिरraपूर्णांकs();
	पूर्ण
पूर्ण

अटल acpi_status acpi_bus_table_handler(u32 event, व्योम *table, व्योम *context)
अणु
	acpi_scan_table_handler(event, table, context);

	वापस acpi_sysfs_table_handler(event, table, context);
पूर्ण

अटल पूर्णांक __init acpi_bus_init(व्योम)
अणु
	पूर्णांक result;
	acpi_status status;

	acpi_os_initialize1();

	status = acpi_load_tables();
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to load the System Description Tables\n");
		जाओ error1;
	पूर्ण

	/*
	 * ACPI 2.0 requires the EC driver to be loaded and work beक्रमe the EC
	 * device is found in the namespace.
	 *
	 * This is accomplished by looking क्रम the ECDT table and getting the EC
	 * parameters out of that.
	 *
	 * Do that beक्रमe calling acpi_initialize_objects() which may trigger EC
	 * address space accesses.
	 */
	acpi_ec_ecdt_probe();

	status = acpi_enable_subप्रणाली(ACPI_NO_ACPI_ENABLE);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to start the ACPI Interpreter\n");
		जाओ error1;
	पूर्ण

	status = acpi_initialize_objects(ACPI_FULL_INITIALIZATION);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to initialize ACPI objects\n");
		जाओ error1;
	पूर्ण

	/* Set capability bits क्रम _OSC under processor scope */
	acpi_early_processor_osc();

	/*
	 * _OSC method may exist in module level code,
	 * so it must be run after ACPI_FULL_INITIALIZATION
	 */
	acpi_bus_osc_negotiate_platक्रमm_control();
	acpi_bus_osc_negotiate_usb_control();

	/*
	 * _PDC control method may load dynamic SSDT tables,
	 * and we need to install the table handler beक्रमe that.
	 */
	status = acpi_install_table_handler(acpi_bus_table_handler, शून्य);

	acpi_sysfs_init();

	acpi_early_processor_set_pdc();

	/*
	 * Maybe EC region is required at bus_scan/acpi_get_devices. So it
	 * is necessary to enable it as early as possible.
	 */
	acpi_ec_dsdt_probe();

	pr_info("Interpreter enabled\n");

	/* Initialize sleep काष्ठाures */
	acpi_sleep_init();

	/*
	 * Get the प्रणाली पूर्णांकerrupt model and evaluate \_PIC.
	 */
	result = acpi_bus_init_irq();
	अगर (result)
		जाओ error1;

	/*
	 * Register the क्रम all standard device notअगरications.
	 */
	status =
	    acpi_install_notअगरy_handler(ACPI_ROOT_OBJECT, ACPI_SYSTEM_NOTIFY,
					&acpi_bus_notअगरy, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		pr_err("Unable to register for system notifications\n");
		जाओ error1;
	पूर्ण

	/*
	 * Create the top ACPI proc directory
	 */
	acpi_root_dir = proc_सूची_गढ़ो(ACPI_BUS_खाता_ROOT, शून्य);

	result = bus_रेजिस्टर(&acpi_bus_type);
	अगर (!result)
		वापस 0;

	/* Mimic काष्ठाured exception handling */
      error1:
	acpi_terminate();
	वापस -ENODEV;
पूर्ण

काष्ठा kobject *acpi_kobj;
EXPORT_SYMBOL_GPL(acpi_kobj);

अटल पूर्णांक __init acpi_init(व्योम)
अणु
	पूर्णांक result;

	अगर (acpi_disabled) अणु
		pr_info("Interpreter disabled.\n");
		वापस -ENODEV;
	पूर्ण

	acpi_kobj = kobject_create_and_add("acpi", firmware_kobj);
	अगर (!acpi_kobj) अणु
		pr_debug("%s: kset create error\n", __func__);
		acpi_kobj = शून्य;
	पूर्ण

	result = acpi_bus_init();
	अगर (result) अणु
		disable_acpi();
		वापस result;
	पूर्ण

	pci_mmcfg_late_init();
	acpi_iort_init();
	acpi_scan_init();
	acpi_ec_init();
	acpi_debugfs_init();
	acpi_sleep_proc_init();
	acpi_wakeup_device_init();
	acpi_debugger_init();
	acpi_setup_sb_notअगरy_handler();
	वापस 0;
पूर्ण

subsys_initcall(acpi_init);
