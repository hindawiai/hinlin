<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utstate - state object support procedures
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utstate")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_push_generic_state
 *
 * PARAMETERS:  list_head           - Head of the state stack
 *              state               - State object to push
 *
 * RETURN:      None
 *
 * DESCRIPTION: Push a state object onto a state stack
 *
 ******************************************************************************/
व्योम
acpi_ut_push_generic_state(जोड़ acpi_generic_state **list_head,
			   जोड़ acpi_generic_state *state)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Push the state object onto the front of the list (stack) */

	state->common.next = *list_head;
	*list_head = state;
	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_pop_generic_state
 *
 * PARAMETERS:  list_head           - Head of the state stack
 *
 * RETURN:      The popped state object
 *
 * DESCRIPTION: Pop a state object from a state stack
 *
 ******************************************************************************/

जोड़ acpi_generic_state *acpi_ut_pop_generic_state(जोड़ acpi_generic_state
						    **list_head)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Remove the state object at the head of the list (stack) */

	state = *list_head;
	अगर (state) अणु

		/* Update the list head */

		*list_head = state->common.next;
	पूर्ण

	वापस (state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_generic_state
 *
 * PARAMETERS:  None
 *
 * RETURN:      The new state object. शून्य on failure.
 *
 * DESCRIPTION: Create a generic state object. Attempt to obtain one from
 *              the global state cache;  If none available, create a new one.
 *
 ******************************************************************************/

जोड़ acpi_generic_state *acpi_ut_create_generic_state(व्योम)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	state = acpi_os_acquire_object(acpi_gbl_state_cache);
	अगर (state) अणु

		/* Initialize */
		state->common.descriptor_type = ACPI_DESC_TYPE_STATE;
	पूर्ण

	वापस (state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_thपढ़ो_state
 *
 * PARAMETERS:  None
 *
 * RETURN:      New Thपढ़ो State. शून्य on failure
 *
 * DESCRIPTION: Create a "Thread State" - a flavor of the generic state used
 *              to track per-thपढ़ो info during method execution
 *
 ******************************************************************************/

काष्ठा acpi_thपढ़ो_state *acpi_ut_create_thपढ़ो_state(व्योम)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Create the generic state object */

	state = acpi_ut_create_generic_state();
	अगर (!state) अणु
		वापस (शून्य);
	पूर्ण

	/* Init fields specअगरic to the update काष्ठा */

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_THREAD;
	state->thपढ़ो.thपढ़ो_id = acpi_os_get_thपढ़ो_id();

	/* Check क्रम invalid thपढ़ो ID - zero is very bad, it will अवरोध things */

	अगर (!state->thपढ़ो.thपढ़ो_id) अणु
		ACPI_ERROR((AE_INFO, "Invalid zero ID from AcpiOsGetThreadId"));
		state->thपढ़ो.thपढ़ो_id = (acpi_thपढ़ो_id) 1;
	पूर्ण

	वापस ((काष्ठा acpi_thपढ़ो_state *)state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_update_state
 *
 * PARAMETERS:  object          - Initial Object to be installed in the state
 *              action          - Update action to be perक्रमmed
 *
 * RETURN:      New state object, null on failure
 *
 * DESCRIPTION: Create an "Update State" - a flavor of the generic state used
 *              to update reference counts and delete complex objects such
 *              as packages.
 *
 ******************************************************************************/

जोड़ acpi_generic_state *acpi_ut_create_update_state(जोड़ acpi_opeअक्रम_object
						      *object, u16 action)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Create the generic state object */

	state = acpi_ut_create_generic_state();
	अगर (!state) अणु
		वापस (शून्य);
	पूर्ण

	/* Init fields specअगरic to the update काष्ठा */

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_UPDATE;
	state->update.object = object;
	state->update.value = action;
	वापस (state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_pkg_state
 *
 * PARAMETERS:  object          - Initial Object to be installed in the state
 *              action          - Update action to be perक्रमmed
 *
 * RETURN:      New state object, null on failure
 *
 * DESCRIPTION: Create a "Package State"
 *
 ******************************************************************************/

जोड़ acpi_generic_state *acpi_ut_create_pkg_state(व्योम *पूर्णांकernal_object,
						   व्योम *बाह्यal_object,
						   u32 index)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Create the generic state object */

	state = acpi_ut_create_generic_state();
	अगर (!state) अणु
		वापस (शून्य);
	पूर्ण

	/* Init fields specअगरic to the update काष्ठा */

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_PACKAGE;
	state->pkg.source_object = (जोड़ acpi_opeअक्रम_object *)पूर्णांकernal_object;
	state->pkg.dest_object = बाह्यal_object;
	state->pkg.index = index;
	state->pkg.num_packages = 1;

	वापस (state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_control_state
 *
 * PARAMETERS:  None
 *
 * RETURN:      New state object, null on failure
 *
 * DESCRIPTION: Create a "Control State" - a flavor of the generic state used
 *              to support nested IF/WHILE स्थिरructs in the AML.
 *
 ******************************************************************************/

जोड़ acpi_generic_state *acpi_ut_create_control_state(व्योम)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Create the generic state object */

	state = acpi_ut_create_generic_state();
	अगर (!state) अणु
		वापस (शून्य);
	पूर्ण

	/* Init fields specअगरic to the control काष्ठा */

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_CONTROL;
	state->common.state = ACPI_CONTROL_CONDITIONAL_EXECUTING;

	वापस (state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_delete_generic_state
 *
 * PARAMETERS:  state               - The state object to be deleted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release a state object to the state cache. शून्य state objects
 *              are ignored.
 *
 ******************************************************************************/

व्योम acpi_ut_delete_generic_state(जोड़ acpi_generic_state *state)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Ignore null state */

	अगर (state) अणु
		(व्योम)acpi_os_release_object(acpi_gbl_state_cache, state);
	पूर्ण

	वापस;
पूर्ण
