<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evxfevnt - External Interfaces, ACPI event disable/enable
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evxfevnt")

#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/*******************************************************************************
 *
 * FUNCTION:    acpi_enable
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Transfers the प्रणाली पूर्णांकo ACPI mode.
 *
 ******************************************************************************/
acpi_status acpi_enable(व्योम)
अणु
	acpi_status status;
	पूर्णांक retry;

	ACPI_FUNCTION_TRACE(acpi_enable);

	/* ACPI tables must be present */

	अगर (acpi_gbl_fadt_index == ACPI_INVALID_TABLE_INDEX) अणु
		वापस_ACPI_STATUS(AE_NO_ACPI_TABLES);
	पूर्ण

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Check current mode */

	अगर (acpi_hw_get_mode() == ACPI_SYS_MODE_ACPI) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INIT,
				  "System is already in ACPI mode\n"));
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Transition to ACPI mode */

	status = acpi_hw_set_mode(ACPI_SYS_MODE_ACPI);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not transition to ACPI mode"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Sanity check that transition succeeded */

	क्रम (retry = 0; retry < 30000; ++retry) अणु
		अगर (acpi_hw_get_mode() == ACPI_SYS_MODE_ACPI) अणु
			अगर (retry != 0)
				ACPI_WARNING((AE_INFO,
				"Platform took > %d00 usec to enter ACPI mode", retry));
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण
		acpi_os_stall(100);	/* 100 usec */
	पूर्ण

	ACPI_ERROR((AE_INFO, "Hardware did not enter ACPI mode"));
	वापस_ACPI_STATUS(AE_NO_HARDWARE_RESPONSE);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enable)

/*******************************************************************************
 *
 * FUNCTION:    acpi_disable
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Transfers the प्रणाली पूर्णांकo LEGACY (non-ACPI) mode.
 *
 ******************************************************************************/
acpi_status acpi_disable(व्योम)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(acpi_disable);

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (acpi_hw_get_mode() == ACPI_SYS_MODE_LEGACY) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_INIT,
				  "System is already in legacy (non-ACPI) mode\n"));
	पूर्ण अन्यथा अणु
		/* Transition to LEGACY mode */

		status = acpi_hw_set_mode(ACPI_SYS_MODE_LEGACY);

		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR((AE_INFO,
				    "Could not exit ACPI mode to legacy mode"));
			वापस_ACPI_STATUS(status);
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_INIT, "ACPI mode disabled\n"));
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_disable)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enable_event
 *
 * PARAMETERS:  event           - The fixed eventto be enabled
 *              flags           - Reserved
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enable an ACPI event (fixed)
 *
 ******************************************************************************/
acpi_status acpi_enable_event(u32 event, u32 flags)
अणु
	acpi_status status = AE_OK;
	u32 value;

	ACPI_FUNCTION_TRACE(acpi_enable_event);

	/* If Hardware Reduced flag is set, there are no fixed events */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Decode the Fixed Event */

	अगर (event > ACPI_EVENT_MAX) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Enable the requested fixed event (by writing a one to the enable
	 * रेजिस्टर bit)
	 */
	status =
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				    enable_रेजिस्टर_id, ACPI_ENABLE_EVENT);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Make sure that the hardware responded */

	status =
	    acpi_पढ़ो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				   enable_रेजिस्टर_id, &value);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (value != 1) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not enable %s event",
			    acpi_ut_get_event_name(event)));
		वापस_ACPI_STATUS(AE_NO_HARDWARE_RESPONSE);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enable_event)

/*******************************************************************************
 *
 * FUNCTION:    acpi_disable_event
 *
 * PARAMETERS:  event           - The fixed event to be disabled
 *              flags           - Reserved
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Disable an ACPI event (fixed)
 *
 ******************************************************************************/
acpi_status acpi_disable_event(u32 event, u32 flags)
अणु
	acpi_status status = AE_OK;
	u32 value;

	ACPI_FUNCTION_TRACE(acpi_disable_event);

	/* If Hardware Reduced flag is set, there are no fixed events */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Decode the Fixed Event */

	अगर (event > ACPI_EVENT_MAX) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Disable the requested fixed event (by writing a zero to the enable
	 * रेजिस्टर bit)
	 */
	status =
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				    enable_रेजिस्टर_id, ACPI_DISABLE_EVENT);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status =
	    acpi_पढ़ो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				   enable_रेजिस्टर_id, &value);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (value != 0) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not disable %s events",
			    acpi_ut_get_event_name(event)));
		वापस_ACPI_STATUS(AE_NO_HARDWARE_RESPONSE);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_disable_event)

/*******************************************************************************
 *
 * FUNCTION:    acpi_clear_event
 *
 * PARAMETERS:  event           - The fixed event to be cleared
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clear an ACPI event (fixed)
 *
 ******************************************************************************/
acpi_status acpi_clear_event(u32 event)
अणु
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE(acpi_clear_event);

	/* If Hardware Reduced flag is set, there are no fixed events */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Decode the Fixed Event */

	अगर (event > ACPI_EVENT_MAX) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Clear the requested fixed event (By writing a one to the status
	 * रेजिस्टर bit)
	 */
	status =
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				    status_रेजिस्टर_id, ACPI_CLEAR_STATUS);

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_clear_event)

/*******************************************************************************
 *
 * FUNCTION:    acpi_get_event_status
 *
 * PARAMETERS:  event           - The fixed event
 *              event_status    - Where the current status of the event will
 *                                be वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Obtains and वापसs the current status of the event
 *
 ******************************************************************************/
acpi_status acpi_get_event_status(u32 event, acpi_event_status * event_status)
अणु
	acpi_status status;
	acpi_event_status local_event_status = 0;
	u32 in_byte;

	ACPI_FUNCTION_TRACE(acpi_get_event_status);

	अगर (!event_status) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Decode the Fixed Event */

	अगर (event > ACPI_EVENT_MAX) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Fixed event currently can be dispatched? */

	अगर (acpi_gbl_fixed_event_handlers[event].handler) अणु
		local_event_status |= ACPI_EVENT_FLAG_HAS_HANDLER;
	पूर्ण

	/* Fixed event currently enabled? */

	status =
	    acpi_पढ़ो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				   enable_रेजिस्टर_id, &in_byte);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (in_byte) अणु
		local_event_status |=
		    (ACPI_EVENT_FLAG_ENABLED | ACPI_EVENT_FLAG_ENABLE_SET);
	पूर्ण

	/* Fixed event currently active? */

	status =
	    acpi_पढ़ो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				   status_रेजिस्टर_id, &in_byte);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (in_byte) अणु
		local_event_status |= ACPI_EVENT_FLAG_STATUS_SET;
	पूर्ण

	(*event_status) = local_event_status;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_event_status)
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
