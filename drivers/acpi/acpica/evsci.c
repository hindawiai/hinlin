<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: evsci - System Control Interrupt configuration and
 *                      legacy to ACPI mode state transition functions
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evsci")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/* Local prototypes */
अटल u32 ACPI_SYSTEM_XFACE acpi_ev_sci_xrupt_handler(व्योम *context);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_sci_dispatch
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status code indicates whether पूर्णांकerrupt was handled.
 *
 * DESCRIPTION: Dispatch the SCI to all host-installed SCI handlers.
 *
 ******************************************************************************/

u32 acpi_ev_sci_dispatch(व्योम)
अणु
	काष्ठा acpi_sci_handler_info *sci_handler;
	acpi_cpu_flags flags;
	u32 पूर्णांक_status = ACPI_INTERRUPT_NOT_HANDLED;

	ACPI_FUNCTION_NAME(ev_sci_dispatch);

	/* Are there any host-installed SCI handlers? */

	अगर (!acpi_gbl_sci_handler_list) अणु
		वापस (पूर्णांक_status);
	पूर्ण

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Invoke all host-installed SCI handlers */

	sci_handler = acpi_gbl_sci_handler_list;
	जबतक (sci_handler) अणु

		/* Invoke the installed handler (at पूर्णांकerrupt level) */

		पूर्णांक_status |= sci_handler->address(sci_handler->context);

		sci_handler = sci_handler->next;
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस (पूर्णांक_status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_sci_xrupt_handler
 *
 * PARAMETERS:  context   - Calling Context
 *
 * RETURN:      Status code indicates whether पूर्णांकerrupt was handled.
 *
 * DESCRIPTION: Interrupt handler that will figure out what function or
 *              control method to call to deal with a SCI.
 *
 ******************************************************************************/

अटल u32 ACPI_SYSTEM_XFACE acpi_ev_sci_xrupt_handler(व्योम *context)
अणु
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_list = context;
	u32 पूर्णांकerrupt_handled = ACPI_INTERRUPT_NOT_HANDLED;

	ACPI_FUNCTION_TRACE(ev_sci_xrupt_handler);

	/*
	 * We are guaranteed by the ACPICA initialization/shutकरोwn code that
	 * अगर this पूर्णांकerrupt handler is installed, ACPI is enabled.
	 */

	/*
	 * Fixed Events:
	 * Check क्रम and dispatch any Fixed Events that have occurred
	 */
	पूर्णांकerrupt_handled |= acpi_ev_fixed_event_detect();

	/*
	 * General Purpose Events:
	 * Check क्रम and dispatch any GPEs that have occurred
	 */
	पूर्णांकerrupt_handled |= acpi_ev_gpe_detect(gpe_xrupt_list);

	/* Invoke all host-installed SCI handlers */

	पूर्णांकerrupt_handled |= acpi_ev_sci_dispatch();

	acpi_sci_count++;
	वापस_UINT32(पूर्णांकerrupt_handled);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_xrupt_handler
 *
 * PARAMETERS:  context   - Calling Context
 *
 * RETURN:      Status code indicates whether पूर्णांकerrupt was handled.
 *
 * DESCRIPTION: Handler क्रम GPE Block Device पूर्णांकerrupts
 *
 ******************************************************************************/

u32 ACPI_SYSTEM_XFACE acpi_ev_gpe_xrupt_handler(व्योम *context)
अणु
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_list = context;
	u32 पूर्णांकerrupt_handled = ACPI_INTERRUPT_NOT_HANDLED;

	ACPI_FUNCTION_TRACE(ev_gpe_xrupt_handler);

	/*
	 * We are guaranteed by the ACPICA initialization/shutकरोwn code that
	 * अगर this पूर्णांकerrupt handler is installed, ACPI is enabled.
	 */

	/* GPEs: Check क्रम and dispatch any GPEs that have occurred */

	पूर्णांकerrupt_handled |= acpi_ev_gpe_detect(gpe_xrupt_list);
	वापस_UINT32(पूर्णांकerrupt_handled);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ev_install_sci_handler
 *
 * PARAMETERS:  none
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Installs SCI handler.
 *
 ******************************************************************************/

u32 acpi_ev_install_sci_handler(व्योम)
अणु
	u32 status = AE_OK;

	ACPI_FUNCTION_TRACE(ev_install_sci_handler);

	status =
	    acpi_os_install_पूर्णांकerrupt_handler((u32) acpi_gbl_FADT.sci_पूर्णांकerrupt,
					      acpi_ev_sci_xrupt_handler,
					      acpi_gbl_gpe_xrupt_list_head);
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_ev_हटाओ_all_sci_handlers
 *
 * PARAMETERS:  none
 *
 * RETURN:      AE_OK अगर handler uninstalled, AE_ERROR अगर handler was not
 *              installed to begin with
 *
 * DESCRIPTION: Remove the SCI पूर्णांकerrupt handler. No further SCIs will be
 *              taken. Remove all host-installed SCI handlers.
 *
 * Note:  It करोesn't seem important to disable all events or set the event
 *        enable रेजिस्टरs to their original values. The OS should disable
 *        the SCI पूर्णांकerrupt level when the handler is हटाओd, so no more
 *        events will come in.
 *
 ******************************************************************************/

acpi_status acpi_ev_हटाओ_all_sci_handlers(व्योम)
अणु
	काष्ठा acpi_sci_handler_info *sci_handler;
	acpi_cpu_flags flags;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ev_हटाओ_all_sci_handlers);

	/* Just let the OS हटाओ the handler and disable the level */

	status =
	    acpi_os_हटाओ_पूर्णांकerrupt_handler((u32) acpi_gbl_FADT.sci_पूर्णांकerrupt,
					     acpi_ev_sci_xrupt_handler);

	अगर (!acpi_gbl_sci_handler_list) अणु
		वापस (status);
	पूर्ण

	flags = acpi_os_acquire_lock(acpi_gbl_gpe_lock);

	/* Free all host-installed SCI handlers */

	जबतक (acpi_gbl_sci_handler_list) अणु
		sci_handler = acpi_gbl_sci_handler_list;
		acpi_gbl_sci_handler_list = sci_handler->next;
		ACPI_FREE(sci_handler);
	पूर्ण

	acpi_os_release_lock(acpi_gbl_gpe_lock, flags);
	वापस_ACPI_STATUS(status);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
