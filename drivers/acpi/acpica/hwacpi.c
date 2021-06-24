<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: hwacpi - ACPI Hardware Initialization/Mode Interface
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwacpi")

#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/******************************************************************************
 *
 * FUNCTION:    acpi_hw_set_mode
 *
 * PARAMETERS:  mode            - SYS_MODE_ACPI or SYS_MODE_LEGACY
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Transitions the प्रणाली पूर्णांकo the requested mode.
 *
 ******************************************************************************/
acpi_status acpi_hw_set_mode(u32 mode)
अणु

	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_set_mode);

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * ACPI 2.0 clarअगरied that अगर SMI_CMD in FADT is zero,
	 * प्रणाली करोes not support mode transition.
	 */
	अगर (!acpi_gbl_FADT.smi_command) अणु
		ACPI_ERROR((AE_INFO,
			    "No SMI_CMD in FADT, mode transition failed"));
		वापस_ACPI_STATUS(AE_NO_HARDWARE_RESPONSE);
	पूर्ण

	/*
	 * ACPI 2.0 clarअगरied the meaning of ACPI_ENABLE and ACPI_DISABLE
	 * in FADT: If it is zero, enabling or disabling is not supported.
	 * As old प्रणालीs may have used zero क्रम mode transition,
	 * we make sure both the numbers are zero to determine these
	 * transitions are not supported.
	 */
	अगर (!acpi_gbl_FADT.acpi_enable && !acpi_gbl_FADT.acpi_disable) अणु
		ACPI_ERROR((AE_INFO,
			    "No ACPI mode transition supported in this system "
			    "(enable/disable both zero)"));
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	चयन (mode) अणु
	हाल ACPI_SYS_MODE_ACPI:

		/* BIOS should have disabled ALL fixed and GP events */

		status = acpi_hw_ग_लिखो_port(acpi_gbl_FADT.smi_command,
					    (u32) acpi_gbl_FADT.acpi_enable, 8);
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Attempting to enable ACPI mode\n"));
		अवरोध;

	हाल ACPI_SYS_MODE_LEGACY:
		/*
		 * BIOS should clear all fixed status bits and restore fixed event
		 * enable bits to शेष
		 */
		status = acpi_hw_ग_लिखो_port(acpi_gbl_FADT.smi_command,
					    (u32)acpi_gbl_FADT.acpi_disable, 8);
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Attempting to enable Legacy (non-ACPI) mode\n"));
		अवरोध;

	शेष:

		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not write ACPI mode change"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_mode
 *
 * PARAMETERS:  none
 *
 * RETURN:      SYS_MODE_ACPI or SYS_MODE_LEGACY
 *
 * DESCRIPTION: Return current operating state of प्रणाली. Determined by
 *              querying the SCI_EN bit.
 *
 ******************************************************************************/

u32 acpi_hw_get_mode(व्योम)
अणु
	acpi_status status;
	u32 value;

	ACPI_FUNCTION_TRACE(hw_get_mode);

	/* If the Hardware Reduced flag is set, machine is always in acpi mode */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_UINT32(ACPI_SYS_MODE_ACPI);
	पूर्ण

	/*
	 * ACPI 2.0 clarअगरied that अगर SMI_CMD in FADT is zero,
	 * प्रणाली करोes not support mode transition.
	 */
	अगर (!acpi_gbl_FADT.smi_command) अणु
		वापस_UINT32(ACPI_SYS_MODE_ACPI);
	पूर्ण

	status = acpi_पढ़ो_bit_रेजिस्टर(ACPI_BITREG_SCI_ENABLE, &value);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_UINT32(ACPI_SYS_MODE_LEGACY);
	पूर्ण

	अगर (value) अणु
		वापस_UINT32(ACPI_SYS_MODE_ACPI);
	पूर्ण अन्यथा अणु
		वापस_UINT32(ACPI_SYS_MODE_LEGACY);
	पूर्ण
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
