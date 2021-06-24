<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: nsdump - table dumping routines क्रम debug
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>

/* TBD: This entire module is apparently obsolete and should be हटाओd */

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsdumpdv")
#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
#समावेश "acnamesp.h"
/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_one_device
 *
 * PARAMETERS:  handle              - Node to be dumped
 *              level               - Nesting level of the handle
 *              context             - Passed पूर्णांकo walk_namespace
 *              वापस_value        - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Dump a single Node that represents a device
 *              This procedure is a user_function called by acpi_ns_walk_namespace.
 *
 ******************************************************************************/
अटल acpi_status
acpi_ns_dump_one_device(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_buffer buffer;
	काष्ठा acpi_device_info *info;
	acpi_status status;
	u32 i;

	ACPI_FUNCTION_NAME(ns_dump_one_device);

	status =
	    acpi_ns_dump_one_object(obj_handle, level, context, वापस_value);

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_get_object_info(obj_handle, &buffer);
	अगर (ACPI_SUCCESS(status)) अणु
		info = buffer.poपूर्णांकer;
		क्रम (i = 0; i < level; i++) अणु
			ACPI_DEBUG_PRINT_RAW((ACPI_DB_TABLES, " "));
		पूर्ण

		ACPI_DEBUG_PRINT_RAW((ACPI_DB_TABLES,
				      "    HID: %s, ADR: %8.8X%8.8X\n",
				      info->hardware_id.value,
				      ACPI_FORMAT_UINT64(info->address)));
		ACPI_FREE(info);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_dump_root_devices
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump all objects of type "device"
 *
 ******************************************************************************/

व्योम acpi_ns_dump_root_devices(व्योम)
अणु
	acpi_handle sys_bus_handle;
	acpi_status status;

	ACPI_FUNCTION_NAME(ns_dump_root_devices);

	/* Only dump the table अगर tracing is enabled */

	अगर (!(ACPI_LV_TABLES & acpi_dbg_level)) अणु
		वापस;
	पूर्ण

	status = acpi_get_handle(शून्य, METHOD_NAME__SB_, &sys_bus_handle);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_TABLES,
			  "Display of all devices in the namespace:\n"));

	status = acpi_ns_walk_namespace(ACPI_TYPE_DEVICE, sys_bus_handle,
					ACPI_UINT32_MAX, ACPI_NS_WALK_NO_UNLOCK,
					acpi_ns_dump_one_device, शून्य, शून्य,
					शून्य);
पूर्ण

#पूर्ण_अगर
#पूर्ण_अगर
