<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: uपंचांगisc - common utility procedures
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utmisc")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_is_pci_root_bridge
 *
 * PARAMETERS:  id              - The HID/CID in string क्रमmat
 *
 * RETURN:      TRUE अगर the Id is a match क्रम a PCI/PCI-Express Root Bridge
 *
 * DESCRIPTION: Determine अगर the input ID is a PCI Root Bridge ID.
 *
 ******************************************************************************/
u8 acpi_ut_is_pci_root_bridge(अक्षर *id)
अणु

	/*
	 * Check अगर this is a PCI root bridge.
	 * ACPI 3.0+: check क्रम a PCI Express root also.
	 */
	अगर (!(म_भेद(id,
		     PCI_ROOT_HID_STRING)) ||
	    !(म_भेद(id, PCI_EXPRESS_ROOT_HID_STRING))) अणु
		वापस (TRUE);
	पूर्ण

	वापस (FALSE);
पूर्ण

#अगर (defined ACPI_ASL_COMPILER || defined ACPI_EXEC_APP || defined ACPI_NAMES_APP)
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_is_aml_table
 *
 * PARAMETERS:  table               - An ACPI table
 *
 * RETURN:      TRUE अगर table contains executable AML; FALSE otherwise
 *
 * DESCRIPTION: Check ACPI Signature क्रम a table that contains AML code.
 *              Currently, these are DSDT,SSDT,PSDT. All other table types are
 *              data tables that करो not contain AML code.
 *
 ******************************************************************************/

u8 acpi_ut_is_aml_table(काष्ठा acpi_table_header *table)
अणु

	/* These are the only tables that contain executable AML */

	अगर (ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_DSDT) ||
	    ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_PSDT) ||
	    ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_SSDT) ||
	    ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_OSDT) ||
	    ACPI_IS_OEM_SIG(table->signature)) अणु
		वापस (TRUE);
	पूर्ण

	वापस (FALSE);
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_dword_byte_swap
 *
 * PARAMETERS:  value           - Value to be converted
 *
 * RETURN:      u32 पूर्णांकeger with bytes swapped
 *
 * DESCRIPTION: Convert a 32-bit value to big-endian (swap the bytes)
 *
 ******************************************************************************/

u32 acpi_ut_dword_byte_swap(u32 value)
अणु
	जोड़ अणु
		u32 value;
		u8 bytes[4];
	पूर्ण out;
	जोड़ अणु
		u32 value;
		u8 bytes[4];
	पूर्ण in;

	ACPI_FUNCTION_ENTRY();

	in.value = value;

	out.bytes[0] = in.bytes[3];
	out.bytes[1] = in.bytes[2];
	out.bytes[2] = in.bytes[1];
	out.bytes[3] = in.bytes[0];

	वापस (out.value);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_set_पूर्णांकeger_width
 *
 * PARAMETERS:  Revision            From DSDT header
 *
 * RETURN:      None
 *
 * DESCRIPTION: Set the global पूर्णांकeger bit width based upon the revision
 *              of the DSDT. For Revision 1 and 0, Integers are 32 bits.
 *              For Revision 2 and above, Integers are 64 bits. Yes, this
 *              makes a dअगरference.
 *
 ******************************************************************************/

व्योम acpi_ut_set_पूर्णांकeger_width(u8 revision)
अणु

	अगर (revision < 2) अणु

		/* 32-bit हाल */

		acpi_gbl_पूर्णांकeger_bit_width = 32;
		acpi_gbl_पूर्णांकeger_nybble_width = 8;
		acpi_gbl_पूर्णांकeger_byte_width = 4;
	पूर्ण अन्यथा अणु
		/* 64-bit हाल (ACPI 2.0+) */

		acpi_gbl_पूर्णांकeger_bit_width = 64;
		acpi_gbl_पूर्णांकeger_nybble_width = 16;
		acpi_gbl_पूर्णांकeger_byte_width = 8;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_create_update_state_and_push
 *
 * PARAMETERS:  object          - Object to be added to the new state
 *              action          - Increment/Decrement
 *              state_list      - List the state will be added to
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create a new state and push it
 *
 ******************************************************************************/

acpi_status
acpi_ut_create_update_state_and_push(जोड़ acpi_opeअक्रम_object *object,
				     u16 action,
				     जोड़ acpi_generic_state **state_list)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_ENTRY();

	/* Ignore null objects; these are expected */

	अगर (!object) अणु
		वापस (AE_OK);
	पूर्ण

	state = acpi_ut_create_update_state(object, action);
	अगर (!state) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	acpi_ut_push_generic_state(state_list, state);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_walk_package_tree
 *
 * PARAMETERS:  source_object       - The package to walk
 *              target_object       - Target object (अगर package is being copied)
 *              walk_callback       - Called once क्रम each package element
 *              context             - Passed to the callback function
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk through a package, including subpackages
 *
 ******************************************************************************/

acpi_status
acpi_ut_walk_package_tree(जोड़ acpi_opeअक्रम_object *source_object,
			  व्योम *target_object,
			  acpi_pkg_callback walk_callback, व्योम *context)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_generic_state *state_list = शून्य;
	जोड़ acpi_generic_state *state;
	जोड़ acpi_opeअक्रम_object *this_source_obj;
	u32 this_index;

	ACPI_FUNCTION_TRACE(ut_walk_package_tree);

	state = acpi_ut_create_pkg_state(source_object, target_object, 0);
	अगर (!state) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	जबतक (state) अणु

		/* Get one element of the package */

		this_index = state->pkg.index;
		this_source_obj =
		    state->pkg.source_object->package.elements[this_index];
		state->pkg.this_target_obj =
		    &state->pkg.source_object->package.elements[this_index];

		/*
		 * Check क्रम:
		 * 1) An uninitialized package element. It is completely
		 *    legal to declare a package and leave it uninitialized
		 * 2) Not an पूर्णांकernal object - can be a namespace node instead
		 * 3) Any type other than a package. Packages are handled in अन्यथा
		 *    हाल below.
		 */
		अगर ((!this_source_obj) ||
		    (ACPI_GET_DESCRIPTOR_TYPE(this_source_obj) !=
		     ACPI_DESC_TYPE_OPERAND) ||
		    (this_source_obj->common.type != ACPI_TYPE_PACKAGE)) अणु
			status =
			    walk_callback(ACPI_COPY_TYPE_SIMPLE,
					  this_source_obj, state, context);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			state->pkg.index++;
			जबतक (state->pkg.index >=
			       state->pkg.source_object->package.count) अणु
				/*
				 * We've handled all of the objects at this level,  This means
				 * that we have just completed a package. That package may
				 * have contained one or more packages itself.
				 *
				 * Delete this state and pop the previous state (package).
				 */
				acpi_ut_delete_generic_state(state);
				state = acpi_ut_pop_generic_state(&state_list);

				/* Finished when there are no more states */

				अगर (!state) अणु
					/*
					 * We have handled all of the objects in the top level
					 * package just add the length of the package objects
					 * and निकास
					 */
					वापस_ACPI_STATUS(AE_OK);
				पूर्ण

				/*
				 * Go back up a level and move the index past the just
				 * completed package object.
				 */
				state->pkg.index++;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* This is a subobject of type package */

			status =
			    walk_callback(ACPI_COPY_TYPE_PACKAGE,
					  this_source_obj, state, context);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			/*
			 * Push the current state and create a new one
			 * The callback above वापसed a new target package object.
			 */
			acpi_ut_push_generic_state(&state_list, state);
			state =
			    acpi_ut_create_pkg_state(this_source_obj,
						     state->pkg.this_target_obj,
						     0);
			अगर (!state) अणु

				/* Free any stacked Update State objects */

				जबतक (state_list) अणु
					state =
					    acpi_ut_pop_generic_state
					    (&state_list);
					acpi_ut_delete_generic_state(state);
				पूर्ण
				वापस_ACPI_STATUS(AE_NO_MEMORY);
			पूर्ण
		पूर्ण
	पूर्ण

	/* We should never get here */

	ACPI_ERROR((AE_INFO, "State list did not terminate correctly"));

	वापस_ACPI_STATUS(AE_AML_INTERNAL);
पूर्ण

#अगर_घोषित ACPI_DEBUG_OUTPUT
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_display_init_pathname
 *
 * PARAMETERS:  type                - Object type of the node
 *              obj_handle          - Handle whose pathname will be displayed
 *              path                - Additional path string to be appended.
 *                                      (शून्य अगर no extra path)
 *
 * RETURN:      acpi_status
 *
 * DESCRIPTION: Display full pathname of an object, DEBUG ONLY
 *
 ******************************************************************************/

व्योम
acpi_ut_display_init_pathname(u8 type,
			      काष्ठा acpi_namespace_node *obj_handle,
			      स्थिर अक्षर *path)
अणु
	acpi_status status;
	काष्ठा acpi_buffer buffer;

	ACPI_FUNCTION_ENTRY();

	/* Only prपूर्णांक the path अगर the appropriate debug level is enabled */

	अगर (!(acpi_dbg_level & ACPI_LV_INIT_NAMES)) अणु
		वापस;
	पूर्ण

	/* Get the full pathname to the node */

	buffer.length = ACPI_ALLOCATE_LOCAL_BUFFER;
	status = acpi_ns_handle_to_pathname(obj_handle, &buffer, TRUE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	/* Prपूर्णांक what we're करोing */

	चयन (type) अणु
	हाल ACPI_TYPE_METHOD:

		acpi_os_म_लिखो("Executing  ");
		अवरोध;

	शेष:

		acpi_os_म_लिखो("Initializing ");
		अवरोध;
	पूर्ण

	/* Prपूर्णांक the object type and pathname */

	acpi_os_म_लिखो("%-12s %s",
		       acpi_ut_get_type_name(type), (अक्षर *)buffer.poपूर्णांकer);

	/* Extra path is used to append names like _STA, _INI, etc. */

	अगर (path) अणु
		acpi_os_म_लिखो(".%s", path);
	पूर्ण
	acpi_os_म_लिखो("\n");

	ACPI_FREE(buffer.poपूर्णांकer);
पूर्ण
#पूर्ण_अगर
