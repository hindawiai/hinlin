<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evevent - Fixed Event handling and dispatch
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evevent")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/* Local prototypes */
अटल acpi_status acpi_ev_fixed_event_initialize(व्योम);

अटल u32 acpi_ev_fixed_event_dispatch(u32 event);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_initialize_events
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize global data काष्ठाures क्रम ACPI events (Fixed, GPE)
 *
 ******************************************************************************/

acpi_status acpi_ev_initialize_events(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_initialize_events);

	/* If Hardware Reduced flag is set, there are no fixed events */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Initialize the Fixed and General Purpose Events. This is करोne prior to
	 * enabling SCIs to prevent पूर्णांकerrupts from occurring beक्रमe the handlers
	 * are installed.
	 */
	status = acpi_ev_fixed_event_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to initialize fixed events"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	status = acpi_ev_gpe_initialize();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to initialize general purpose events"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_xrupt_handlers
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install पूर्णांकerrupt handlers क्रम the SCI and Global Lock
 *
 ******************************************************************************/

acpi_status acpi_ev_install_xrupt_handlers(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_install_xrupt_handlers);

	/* If Hardware Reduced flag is set, there is no ACPI h/w */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Install the SCI handler */

	status = acpi_ev_install_sci_handler();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to install System Control Interrupt handler"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Install the handler क्रम the Global Lock */

	status = acpi_ev_init_global_lock_handler();
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Unable to initialize Global Lock handler"));
		वापस_ACPI_STATUS(status);
	पूर्ण

	acpi_gbl_events_initialized = TRUE;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_fixed_event_initialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install the fixed event handlers and disable all fixed events.
 *
 ******************************************************************************/

अटल acpi_status acpi_ev_fixed_event_initialize(व्योम)
अणु
	u32 i;
	acpi_status status;

	/*
	 * Initialize the काष्ठाure that keeps track of fixed event handlers and
	 * disable all of the fixed events.
	 */
	क्रम (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) अणु
		acpi_gbl_fixed_event_handlers[i].handler = शून्य;
		acpi_gbl_fixed_event_handlers[i].context = शून्य;

		/* Disable the fixed event */

		अगर (acpi_gbl_fixed_event_info[i].enable_रेजिस्टर_id != 0xFF) अणु
			status =
			    acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info
						    [i].enable_रेजिस्टर_id,
						    ACPI_DISABLE_EVENT);
			अगर (ACPI_FAILURE(status)) अणु
				वापस (status);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_fixed_event_detect
 *
 * PARAMETERS:  None
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Checks the PM status रेजिस्टर क्रम active fixed events
 *
 ******************************************************************************/

u32 acpi_ev_fixed_event_detect(व्योम)
अणु
	u32 पूर्णांक_status = ACPI_INTERRUPT_NOT_HANDLED;
	u32 fixed_status;
	u32 fixed_enable;
	u32 i;
	acpi_status status;

	ACPI_FUNCTION_NAME(ev_fixed_event_detect);

	/*
	 * Read the fixed feature status and enable रेजिस्टरs, as all the हालs
	 * depend on their values. Ignore errors here.
	 */
	status = acpi_hw_रेजिस्टर_पढ़ो(ACPI_REGISTER_PM1_STATUS, &fixed_status);
	status |=
	    acpi_hw_रेजिस्टर_पढ़ो(ACPI_REGISTER_PM1_ENABLE, &fixed_enable);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (पूर्णांक_status);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_INTERRUPTS,
			  "Fixed Event Block: Enable %08X Status %08X\n",
			  fixed_enable, fixed_status));

	/*
	 * Check क्रम all possible Fixed Events and dispatch those that are active
	 */
	क्रम (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) अणु

		/* Both the status and enable bits must be on क्रम this event */

		अगर ((fixed_status & acpi_gbl_fixed_event_info[i].
		     status_bit_mask)
		    && (fixed_enable & acpi_gbl_fixed_event_info[i].
			enable_bit_mask)) अणु
			/*
			 * Found an active (संकेतled) event. Invoke global event
			 * handler अगर present.
			 */
			acpi_fixed_event_count[i]++;
			अगर (acpi_gbl_global_event_handler) अणु
				acpi_gbl_global_event_handler
				    (ACPI_EVENT_TYPE_FIXED, शून्य, i,
				     acpi_gbl_global_event_handler_context);
			पूर्ण

			पूर्णांक_status |= acpi_ev_fixed_event_dispatch(i);
		पूर्ण
	पूर्ण

	वापस (पूर्णांक_status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_fixed_event_dispatch
 *
 * PARAMETERS:  event               - Event type
 *
 * RETURN:      INTERRUPT_HANDLED or INTERRUPT_NOT_HANDLED
 *
 * DESCRIPTION: Clears the status bit क्रम the requested event, calls the
 *              handler that previously रेजिस्टरed क्रम the event.
 *              NOTE: If there is no handler क्रम the event, the event is
 *              disabled to prevent further पूर्णांकerrupts.
 *
 ******************************************************************************/

अटल u32 acpi_ev_fixed_event_dispatch(u32 event)
अणु

	ACPI_FUNCTION_ENTRY();

	/* Clear the status bit */

	(व्योम)acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
				      status_रेजिस्टर_id, ACPI_CLEAR_STATUS);

	/*
	 * Make sure that a handler exists. If not, report an error
	 * and disable the event to prevent further पूर्णांकerrupts.
	 */
	अगर (!acpi_gbl_fixed_event_handlers[event].handler) अणु
		(व्योम)acpi_ग_लिखो_bit_रेजिस्टर(acpi_gbl_fixed_event_info[event].
					      enable_रेजिस्टर_id,
					      ACPI_DISABLE_EVENT);

		ACPI_ERROR((AE_INFO,
			    "No installed handler for fixed event - %s (%u), disabling",
			    acpi_ut_get_event_name(event), event));

		वापस (ACPI_INTERRUPT_NOT_HANDLED);
	पूर्ण

	/* Invoke the Fixed Event handler */

	वापस ((acpi_gbl_fixed_event_handlers[event].
		 handler) (acpi_gbl_fixed_event_handlers[event].context));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_any_fixed_event_status_set
 *
 * PARAMETERS:  None
 *
 * RETURN:      TRUE or FALSE
 *
 * DESCRIPTION: Checks the PM status रेजिस्टर क्रम active fixed events
 *
 ******************************************************************************/

u32 acpi_any_fixed_event_status_set(व्योम)
अणु
	acpi_status status;
	u32 in_status;
	u32 in_enable;
	u32 i;

	status = acpi_hw_रेजिस्टर_पढ़ो(ACPI_REGISTER_PM1_ENABLE, &in_enable);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (FALSE);
	पूर्ण

	status = acpi_hw_रेजिस्टर_पढ़ो(ACPI_REGISTER_PM1_STATUS, &in_status);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (FALSE);
	पूर्ण

	/*
	 * Check क्रम all possible Fixed Events and dispatch those that are active
	 */
	क्रम (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++) अणु

		/* Both the status and enable bits must be on क्रम this event */

		अगर ((in_status & acpi_gbl_fixed_event_info[i].status_bit_mask) &&
		    (in_enable & acpi_gbl_fixed_event_info[i].enable_bit_mask)) अणु
			वापस (TRUE);
		पूर्ण
	पूर्ण

	वापस (FALSE);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
