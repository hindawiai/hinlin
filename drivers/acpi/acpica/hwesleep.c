<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Name: hwesleep.c - ACPI Hardware Sleep/Wake Support functions क्रम the
 *                    extended FADT-V5 sleep रेजिस्टरs.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwesleep")

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_execute_sleep_method
 *
 * PARAMETERS:  method_pathname     - Pathname of method to execute
 *              पूर्णांकeger_argument    - Argument to pass to the method
 *
 * RETURN:      None
 *
 * DESCRIPTION: Execute a sleep/wake related method with one पूर्णांकeger argument
 *              and no वापस value.
 *
 ******************************************************************************/
व्योम acpi_hw_execute_sleep_method(अक्षर *method_pathname, u32 पूर्णांकeger_argument)
अणु
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object arg;
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_execute_sleep_method);

	/* One argument, पूर्णांकeger_argument; No वापस value expected */

	arg_list.count = 1;
	arg_list.poपूर्णांकer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.पूर्णांकeger.value = (u64)पूर्णांकeger_argument;

	status = acpi_evaluate_object(शून्य, method_pathname, &arg_list, शून्य);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		ACPI_EXCEPTION((AE_INFO, status, "While executing method %s",
				method_pathname));
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_extended_sleep
 *
 * PARAMETERS:  sleep_state         - Which sleep state to enter
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enter a प्रणाली sleep state via the extended FADT sleep
 *              रेजिस्टरs (V5 FADT).
 *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED
 *
 ******************************************************************************/

acpi_status acpi_hw_extended_sleep(u8 sleep_state)
अणु
	acpi_status status;
	u8 sleep_control;
	u64 sleep_status;

	ACPI_FUNCTION_TRACE(hw_extended_sleep);

	/* Extended sleep रेजिस्टरs must be valid */

	अगर (!acpi_gbl_FADT.sleep_control.address ||
	    !acpi_gbl_FADT.sleep_status.address) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	/* Clear wake status (WAK_STS) */

	status = acpi_ग_लिखो((u64)ACPI_X_WAKE_STATUS,
			    &acpi_gbl_FADT.sleep_status);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	acpi_gbl_प्रणाली_awake_and_running = FALSE;

	/*
	 * Set the SLP_TYP and SLP_EN bits.
	 *
	 * Note: We only use the first value वापसed by the \_Sx method
	 * (acpi_gbl_sleep_type_a) - As per ACPI specअगरication.
	 */
	ACPI_DEBUG_PRINT((ACPI_DB_INIT,
			  "Entering sleep state [S%u]\n", sleep_state));

	sleep_control = ((acpi_gbl_sleep_type_a << ACPI_X_SLEEP_TYPE_POSITION) &
			 ACPI_X_SLEEP_TYPE_MASK) | ACPI_X_SLEEP_ENABLE;

	/* Flush caches, as per ACPI specअगरication */

	ACPI_FLUSH_CPU_CACHE();

	status = acpi_os_enter_sleep(sleep_state, sleep_control, 0);
	अगर (status == AE_CTRL_TERMINATE) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ग_लिखो((u64)sleep_control, &acpi_gbl_FADT.sleep_control);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Wait क्रम transition back to Working State */

	करो अणु
		status = acpi_पढ़ो(&sleep_status, &acpi_gbl_FADT.sleep_status);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

	पूर्ण जबतक (!(((u8)sleep_status) & ACPI_X_WAKE_STATUS));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_extended_wake_prep
 *
 * PARAMETERS:  sleep_state         - Which sleep state we just निकासed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm first part of OS-independent ACPI cleanup after
 *              a sleep. Called with पूर्णांकerrupts ENABLED.
 *
 ******************************************************************************/

acpi_status acpi_hw_extended_wake_prep(u8 sleep_state)
अणु
	acpi_status status;
	u8 sleep_type_value;

	ACPI_FUNCTION_TRACE(hw_extended_wake_prep);

	status = acpi_get_sleep_type_data(ACPI_STATE_S0,
					  &acpi_gbl_sleep_type_a,
					  &acpi_gbl_sleep_type_b);
	अगर (ACPI_SUCCESS(status)) अणु
		sleep_type_value =
		    ((acpi_gbl_sleep_type_a << ACPI_X_SLEEP_TYPE_POSITION) &
		     ACPI_X_SLEEP_TYPE_MASK);

		(व्योम)acpi_ग_लिखो((u64)(sleep_type_value | ACPI_X_SLEEP_ENABLE),
				 &acpi_gbl_FADT.sleep_control);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_extended_wake
 *
 * PARAMETERS:  sleep_state         - Which sleep state we just निकासed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm OS-independent ACPI cleanup after a sleep
 *              Called with पूर्णांकerrupts ENABLED.
 *
 ******************************************************************************/

acpi_status acpi_hw_extended_wake(u8 sleep_state)
अणु
	ACPI_FUNCTION_TRACE(hw_extended_wake);

	/* Ensure enter_sleep_state_prep -> enter_sleep_state ordering */

	acpi_gbl_sleep_type_a = ACPI_SLEEP_TYPE_INVALID;

	/* Execute the wake methods */

	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, ACPI_SST_WAKING);
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__WAK, sleep_state);

	/*
	 * Some BIOS code assumes that WAK_STS will be cleared on resume
	 * and use it to determine whether the प्रणाली is rebooting or
	 * resuming. Clear WAK_STS क्रम compatibility.
	 */
	(व्योम)acpi_ग_लिखो((u64)ACPI_X_WAKE_STATUS, &acpi_gbl_FADT.sleep_status);
	acpi_gbl_प्रणाली_awake_and_running = TRUE;

	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, ACPI_SST_WORKING);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
