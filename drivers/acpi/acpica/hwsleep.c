<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Name: hwsleep.c - ACPI Hardware Sleep/Wake Support functions क्रम the
 *                   original/legacy sleep/PM रेजिस्टरs.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwsleep")

#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_legacy_sleep
 *
 * PARAMETERS:  sleep_state         - Which sleep state to enter
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enter a प्रणाली sleep state via the legacy FADT PM रेजिस्टरs
 *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED
 *
 ******************************************************************************/
acpi_status acpi_hw_legacy_sleep(u8 sleep_state)
अणु
	काष्ठा acpi_bit_रेजिस्टर_info *sleep_type_reg_info;
	काष्ठा acpi_bit_रेजिस्टर_info *sleep_enable_reg_info;
	u32 pm1a_control;
	u32 pm1b_control;
	u32 in_value;
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_legacy_sleep);

	sleep_type_reg_info =
	    acpi_hw_get_bit_रेजिस्टर_info(ACPI_BITREG_SLEEP_TYPE);
	sleep_enable_reg_info =
	    acpi_hw_get_bit_रेजिस्टर_info(ACPI_BITREG_SLEEP_ENABLE);

	/* Clear wake status */

	status = acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_WAKE_STATUS,
					 ACPI_CLEAR_STATUS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Disable all GPEs */
	status = acpi_hw_disable_all_gpes();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण
	status = acpi_hw_clear_acpi_status();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण
	acpi_gbl_प्रणाली_awake_and_running = FALSE;

	 /* Enable all wakeup GPEs */
	status = acpi_hw_enable_all_wakeup_gpes();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get current value of PM1A control */

	status = acpi_hw_रेजिस्टर_पढ़ो(ACPI_REGISTER_PM1_CONTROL,
				       &pm1a_control);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण
	ACPI_DEBUG_PRINT((ACPI_DB_INIT,
			  "Entering sleep state [S%u]\n", sleep_state));

	/* Clear the SLP_EN and SLP_TYP fields */

	pm1a_control &= ~(sleep_type_reg_info->access_bit_mask |
			  sleep_enable_reg_info->access_bit_mask);
	pm1b_control = pm1a_control;

	/* Insert the SLP_TYP bits */

	pm1a_control |=
	    (acpi_gbl_sleep_type_a << sleep_type_reg_info->bit_position);
	pm1b_control |=
	    (acpi_gbl_sleep_type_b << sleep_type_reg_info->bit_position);

	/*
	 * We split the ग_लिखोs of SLP_TYP and SLP_EN to workaround
	 * poorly implemented hardware.
	 */

	/* Write #1: ग_लिखो the SLP_TYP data to the PM1 Control रेजिस्टरs */

	status = acpi_hw_ग_लिखो_pm1_control(pm1a_control, pm1b_control);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Insert the sleep enable (SLP_EN) bit */

	pm1a_control |= sleep_enable_reg_info->access_bit_mask;
	pm1b_control |= sleep_enable_reg_info->access_bit_mask;

	/* Flush caches, as per ACPI specअगरication */

	ACPI_FLUSH_CPU_CACHE();

	status = acpi_os_enter_sleep(sleep_state, pm1a_control, pm1b_control);
	अगर (status == AE_CTRL_TERMINATE) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Write #2: Write both SLP_TYP + SLP_EN */

	status = acpi_hw_ग_लिखो_pm1_control(pm1a_control, pm1b_control);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (sleep_state > ACPI_STATE_S3) अणु
		/*
		 * We wanted to sleep > S3, but it didn't happen (by virtue of the
		 * fact that we are still executing!)
		 *
		 * Wait ten seconds, then try again. This is to get S4/S5 to work on
		 * all machines.
		 *
		 * We रुको so दीर्घ to allow chipsets that poll this reg very slowly
		 * to still पढ़ो the right value. Ideally, this block would go
		 * away entirely.
		 */
		acpi_os_stall(10 * ACPI_USEC_PER_SEC);

		status = acpi_hw_रेजिस्टर_ग_लिखो(ACPI_REGISTER_PM1_CONTROL,
						sleep_enable_reg_info->
						access_bit_mask);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/* Wait क्रम transition back to Working State */

	करो अणु
		status =
		    acpi_पढ़ो_bit_रेजिस्टर(ACPI_BITREG_WAKE_STATUS, &in_value);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

	पूर्ण जबतक (!in_value);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_legacy_wake_prep
 *
 * PARAMETERS:  sleep_state         - Which sleep state we just निकासed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm the first state of OS-independent ACPI cleanup after a
 *              sleep.
 *              Called with पूर्णांकerrupts ENABLED.
 *
 ******************************************************************************/

acpi_status acpi_hw_legacy_wake_prep(u8 sleep_state)
अणु
	acpi_status status;
	काष्ठा acpi_bit_रेजिस्टर_info *sleep_type_reg_info;
	काष्ठा acpi_bit_रेजिस्टर_info *sleep_enable_reg_info;
	u32 pm1a_control;
	u32 pm1b_control;

	ACPI_FUNCTION_TRACE(hw_legacy_wake_prep);

	/*
	 * Set SLP_TYPE and SLP_EN to state S0.
	 * This is unclear from the ACPI Spec, but it is required
	 * by some machines.
	 */
	status = acpi_get_sleep_type_data(ACPI_STATE_S0,
					  &acpi_gbl_sleep_type_a,
					  &acpi_gbl_sleep_type_b);
	अगर (ACPI_SUCCESS(status)) अणु
		sleep_type_reg_info =
		    acpi_hw_get_bit_रेजिस्टर_info(ACPI_BITREG_SLEEP_TYPE);
		sleep_enable_reg_info =
		    acpi_hw_get_bit_रेजिस्टर_info(ACPI_BITREG_SLEEP_ENABLE);

		/* Get current value of PM1A control */

		status = acpi_hw_रेजिस्टर_पढ़ो(ACPI_REGISTER_PM1_CONTROL,
					       &pm1a_control);
		अगर (ACPI_SUCCESS(status)) अणु

			/* Clear the SLP_EN and SLP_TYP fields */

			pm1a_control &= ~(sleep_type_reg_info->access_bit_mask |
					  sleep_enable_reg_info->
					  access_bit_mask);
			pm1b_control = pm1a_control;

			/* Insert the SLP_TYP bits */

			pm1a_control |= (acpi_gbl_sleep_type_a <<
					 sleep_type_reg_info->bit_position);
			pm1b_control |= (acpi_gbl_sleep_type_b <<
					 sleep_type_reg_info->bit_position);

			/* Write the control रेजिस्टरs and ignore any errors */

			(व्योम)acpi_hw_ग_लिखो_pm1_control(pm1a_control,
							pm1b_control);
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_legacy_wake
 *
 * PARAMETERS:  sleep_state         - Which sleep state we just निकासed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm OS-independent ACPI cleanup after a sleep
 *              Called with पूर्णांकerrupts ENABLED.
 *
 ******************************************************************************/

acpi_status acpi_hw_legacy_wake(u8 sleep_state)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_legacy_wake);

	/* Ensure enter_sleep_state_prep -> enter_sleep_state ordering */

	acpi_gbl_sleep_type_a = ACPI_SLEEP_TYPE_INVALID;
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, ACPI_SST_WAKING);

	/*
	 * GPEs must be enabled beक्रमe _WAK is called as GPEs
	 * might get fired there
	 *
	 * Restore the GPEs:
	 * 1) Disable all GPEs
	 * 2) Enable all runसमय GPEs
	 */
	status = acpi_hw_disable_all_gpes();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_hw_enable_all_runसमय_gpes();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Now we can execute _WAK, etc. Some machines require that the GPEs
	 * are enabled beक्रमe the wake methods are executed.
	 */
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__WAK, sleep_state);

	/*
	 * Some BIOS code assumes that WAK_STS will be cleared on resume
	 * and use it to determine whether the प्रणाली is rebooting or
	 * resuming. Clear WAK_STS क्रम compatibility.
	 */
	(व्योम)acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_WAKE_STATUS,
				      ACPI_CLEAR_STATUS);
	acpi_gbl_प्रणाली_awake_and_running = TRUE;

	/* Enable घातer button */

	(व्योम)
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info
				    [ACPI_EVENT_POWER_BUTTON].
				    enable_रेजिस्टर_id, ACPI_ENABLE_EVENT);

	(व्योम)
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info
				    [ACPI_EVENT_POWER_BUTTON].
				    status_रेजिस्टर_id, ACPI_CLEAR_STATUS);

	/* Enable sleep button */

	(व्योम)
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info
				    [ACPI_EVENT_SLEEP_BUTTON].
				    enable_रेजिस्टर_id, ACPI_ENABLE_EVENT);

	(व्योम)
	    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info
				    [ACPI_EVENT_SLEEP_BUTTON].
				    status_रेजिस्टर_id, ACPI_CLEAR_STATUS);

	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, ACPI_SST_WORKING);
	वापस_ACPI_STATUS(status);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
