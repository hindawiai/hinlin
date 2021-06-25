<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Name: hwxfsleep.c - ACPI Hardware Sleep/Wake External Interfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwxfsleep")

/* Local prototypes */
#अगर (!ACPI_REDUCED_HARDWARE)
अटल acpi_status
acpi_hw_set_firmware_waking_vector(काष्ठा acpi_table_facs *facs,
				   acpi_physical_address physical_address,
				   acpi_physical_address physical_address64);
#पूर्ण_अगर

/*
 * These functions are हटाओd क्रम the ACPI_REDUCED_HARDWARE हाल:
 *      acpi_set_firmware_waking_vector
 *      acpi_enter_sleep_state_s4bios
 */

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_set_firmware_waking_vector
 *
 * PARAMETERS:  facs                - Poपूर्णांकer to FACS table
 *              physical_address    - 32-bit physical address of ACPI real mode
 *                                    entry poपूर्णांक
 *              physical_address64  - 64-bit physical address of ACPI रक्षित
 *                                    mode entry poपूर्णांक
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Sets the firmware_waking_vector fields of the FACS
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_set_firmware_waking_vector(काष्ठा acpi_table_facs *facs,
				   acpi_physical_address physical_address,
				   acpi_physical_address physical_address64)
अणु
	ACPI_FUNCTION_TRACE(acpi_hw_set_firmware_waking_vector);


	/*
	 * According to the ACPI specअगरication 2.0c and later, the 64-bit
	 * waking vector should be cleared and the 32-bit waking vector should
	 * be used, unless we want the wake-up code to be called by the BIOS in
	 * Protected Mode.  Some प्रणालीs (क्रम example HP dv5-1004nr) are known
	 * to fail to resume अगर the 64-bit vector is used.
	 */

	/* Set the 32-bit vector */

	facs->firmware_waking_vector = (u32)physical_address;

	अगर (facs->length > 32) अणु
		अगर (facs->version >= 1) अणु

			/* Set the 64-bit vector */

			facs->xfirmware_waking_vector = physical_address64;
		पूर्ण अन्यथा अणु
			/* Clear the 64-bit vector अगर it exists */

			facs->xfirmware_waking_vector = 0;
		पूर्ण
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_set_firmware_waking_vector
 *
 * PARAMETERS:  physical_address    - 32-bit physical address of ACPI real mode
 *                                    entry poपूर्णांक
 *              physical_address64  - 64-bit physical address of ACPI रक्षित
 *                                    mode entry poपूर्णांक
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Sets the firmware_waking_vector fields of the FACS
 *
 ******************************************************************************/

acpi_status
acpi_set_firmware_waking_vector(acpi_physical_address physical_address,
				acpi_physical_address physical_address64)
अणु

	ACPI_FUNCTION_TRACE(acpi_set_firmware_waking_vector);

	अगर (acpi_gbl_FACS) अणु
		(व्योम)acpi_hw_set_firmware_waking_vector(acpi_gbl_FACS,
							 physical_address,
							 physical_address64);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_set_firmware_waking_vector)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enter_sleep_state_s4bios
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm a S4 bios request.
 *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED
 *
 ******************************************************************************/
acpi_status acpi_enter_sleep_state_s4bios(व्योम)
अणु
	u32 in_value;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_enter_sleep_state_s4bios);

	/* Clear the wake status bit (PM1) */

	status =
	    acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_WAKE_STATUS, ACPI_CLEAR_STATUS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_hw_clear_acpi_status();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * 1) Disable all GPEs
	 * 2) Enable all wakeup GPEs
	 */
	status = acpi_hw_disable_all_gpes();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण
	acpi_gbl_प्रणाली_awake_and_running = FALSE;

	status = acpi_hw_enable_all_wakeup_gpes();
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	ACPI_FLUSH_CPU_CACHE();

	status = acpi_hw_ग_लिखो_port(acpi_gbl_FADT.smi_command,
				    (u32)acpi_gbl_FADT.s4_bios_request, 8);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	करो अणु
		acpi_os_stall(ACPI_USEC_PER_MSEC);
		status =
		    acpi_पढ़ो_bit_रेजिस्टर(ACPI_BITREG_WAKE_STATUS, &in_value);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

	पूर्ण जबतक (!in_value);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enter_sleep_state_s4bios)
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*******************************************************************************
 *
 * FUNCTION:    acpi_enter_sleep_state_prep
 *
 * PARAMETERS:  sleep_state         - Which sleep state to enter
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Prepare to enter a प्रणाली sleep state.
 *              This function must execute with पूर्णांकerrupts enabled.
 *              We अवरोध sleeping पूर्णांकo 2 stages so that OSPM can handle
 *              various OS-specअगरic tasks between the two steps.
 *
 ******************************************************************************/

acpi_status acpi_enter_sleep_state_prep(u8 sleep_state)
अणु
	acpi_status status;
	काष्ठा acpi_object_list arg_list;
	जोड़ acpi_object arg;
	u32 sst_value;

	ACPI_FUNCTION_TRACE(acpi_enter_sleep_state_prep);

	status = acpi_get_sleep_type_data(sleep_state,
					  &acpi_gbl_sleep_type_a,
					  &acpi_gbl_sleep_type_b);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Execute the _PTS method (Prepare To Sleep) */

	arg_list.count = 1;
	arg_list.poपूर्णांकer = &arg;
	arg.type = ACPI_TYPE_INTEGER;
	arg.पूर्णांकeger.value = sleep_state;

	status =
	    acpi_evaluate_object(शून्य, METHOD_PATHNAME__PTS, &arg_list, शून्य);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Setup the argument to the _SST method (System STatus) */

	चयन (sleep_state) अणु
	हाल ACPI_STATE_S0:

		sst_value = ACPI_SST_WORKING;
		अवरोध;

	हाल ACPI_STATE_S1:
	हाल ACPI_STATE_S2:
	हाल ACPI_STATE_S3:

		sst_value = ACPI_SST_SLEEPING;
		अवरोध;

	हाल ACPI_STATE_S4:

		sst_value = ACPI_SST_SLEEP_CONTEXT;
		अवरोध;

	शेष:

		sst_value = ACPI_SST_INDICATOR_OFF;	/* Default is off */
		अवरोध;
	पूर्ण

	/*
	 * Set the प्रणाली indicators to show the desired sleep state.
	 * _SST is an optional method (वापस no error अगर not found)
	 */
	acpi_hw_execute_sleep_method(METHOD_PATHNAME__SST, sst_value);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enter_sleep_state_prep)

/*******************************************************************************
 *
 * FUNCTION:    acpi_enter_sleep_state
 *
 * PARAMETERS:  sleep_state         - Which sleep state to enter
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Enter a प्रणाली sleep state
 *              THIS FUNCTION MUST BE CALLED WITH INTERRUPTS DISABLED
 *
 ******************************************************************************/
acpi_status acpi_enter_sleep_state(u8 sleep_state)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_enter_sleep_state);

	अगर ((acpi_gbl_sleep_type_a > ACPI_SLEEP_TYPE_MAX) ||
	    (acpi_gbl_sleep_type_b > ACPI_SLEEP_TYPE_MAX)) अणु
		ACPI_ERROR((AE_INFO, "Sleep values out of range: A=0x%X B=0x%X",
			    acpi_gbl_sleep_type_a, acpi_gbl_sleep_type_b));
		वापस_ACPI_STATUS(AE_AML_OPERAND_VALUE);
	पूर्ण

#अगर !ACPI_REDUCED_HARDWARE
	अगर (!acpi_gbl_reduced_hardware)
		status = acpi_hw_legacy_sleep(sleep_state);
	अन्यथा
#पूर्ण_अगर
		status = acpi_hw_extended_sleep(sleep_state);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_enter_sleep_state)

/*******************************************************************************
 *
 * FUNCTION:    acpi_leave_sleep_state_prep
 *
 * PARAMETERS:  sleep_state         - Which sleep state we are निकासing
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm the first state of OS-independent ACPI cleanup after a
 *              sleep. Called with पूर्णांकerrupts DISABLED.
 *              We अवरोध wake/resume पूर्णांकo 2 stages so that OSPM can handle
 *              various OS-specअगरic tasks between the two steps.
 *
 ******************************************************************************/
acpi_status acpi_leave_sleep_state_prep(u8 sleep_state)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_leave_sleep_state_prep);

#अगर !ACPI_REDUCED_HARDWARE
	अगर (!acpi_gbl_reduced_hardware)
		status = acpi_hw_legacy_wake_prep(sleep_state);
	अन्यथा
#पूर्ण_अगर
		status = acpi_hw_extended_wake_prep(sleep_state);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_leave_sleep_state_prep)

/*******************************************************************************
 *
 * FUNCTION:    acpi_leave_sleep_state
 *
 * PARAMETERS:  sleep_state         - Which sleep state we are निकासing
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमm OS-independent ACPI cleanup after a sleep
 *              Called with पूर्णांकerrupts ENABLED.
 *
 ******************************************************************************/
acpi_status acpi_leave_sleep_state(u8 sleep_state)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_leave_sleep_state);

#अगर !ACPI_REDUCED_HARDWARE
	अगर (!acpi_gbl_reduced_hardware)
		status = acpi_hw_legacy_wake(sleep_state);
	अन्यथा
#पूर्ण_अगर
		status = acpi_hw_extended_wake(sleep_state);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_leave_sleep_state)
