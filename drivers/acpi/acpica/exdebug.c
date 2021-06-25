<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exdebug - Support क्रम stores to the AML Debug Object
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exdebug")

#अगर_अघोषित ACPI_NO_ERROR_MESSAGES
/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_करो_debug_object
 *
 * PARAMETERS:  source_desc         - Object to be output to "Debug Object"
 *              level               - Indentation level (used क्रम packages)
 *              index               - Current package element, zero अगर not pkg
 *
 * RETURN:      None
 *
 * DESCRIPTION: Handles stores to the AML Debug Object. For example:
 *              Store(INT1, Debug)
 *
 * This function is not compiled अगर ACPI_NO_ERROR_MESSAGES is set.
 *
 * This function is only enabled अगर acpi_gbl_enable_aml_debug_object is set, or
 * अगर ACPI_LV_DEBUG_OBJECT is set in the acpi_dbg_level. Thus, in the normal
 * operational हाल, stores to the debug object are ignored but can be easily
 * enabled अगर necessary.
 *
 ******************************************************************************/
व्योम
acpi_ex_करो_debug_object(जोड़ acpi_opeअक्रम_object *source_desc,
			u32 level, u32 index)
अणु
	u32 i;
	u32 समयr;
	जोड़ acpi_opeअक्रम_object *object_desc;
	u32 value;

	ACPI_FUNCTION_TRACE_PTR(ex_करो_debug_object, source_desc);

	/* Output must be enabled via the debug_object global or the dbg_level */

	अगर (!acpi_gbl_enable_aml_debug_object &&
	    !(acpi_dbg_level & ACPI_LV_DEBUG_OBJECT)) अणु
		वापस_VOID;
	पूर्ण

	/* Newline -- करोn't emit the line header */

	अगर (source_desc &&
	    (ACPI_GET_DESCRIPTOR_TYPE(source_desc) == ACPI_DESC_TYPE_OPERAND) &&
	    (source_desc->common.type == ACPI_TYPE_STRING)) अणु
		अगर ((source_desc->string.length == 1) &&
		    (*source_desc->string.poपूर्णांकer == '\n')) अणु
			acpi_os_म_लिखो("\n");
			वापस_VOID;
		पूर्ण
	पूर्ण

	/*
	 * Prपूर्णांक line header as दीर्घ as we are not in the middle of an
	 * object display
	 */
	अगर (!((level > 0) && index == 0)) अणु
		अगर (acpi_gbl_display_debug_समयr) अणु
			/*
			 * We will emit the current समयr value (in microseconds) with each
			 * debug output. Only need the lower 26 bits. This allows क्रम 67
			 * million microseconds or 67 seconds beक्रमe rollover.
			 *
			 * Convert 100 nanosecond units to microseconds
			 */
			समयr = ((u32)acpi_os_get_समयr() / 10);
			समयr &= 0x03FFFFFF;

			acpi_os_म_लिखो("ACPI Debug: T=0x%8.8X %*s", समयr,
				       level, " ");
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("ACPI Debug: %*s", level, " ");
		पूर्ण
	पूर्ण

	/* Display the index क्रम package output only */

	अगर (index > 0) अणु
		acpi_os_म_लिखो("(%.2u) ", index - 1);
	पूर्ण

	अगर (!source_desc) अणु
		acpi_os_म_लिखो("[Null Object]\n");
		वापस_VOID;
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(source_desc) == ACPI_DESC_TYPE_OPERAND) अणु

		/* No object type prefix needed क्रम पूर्णांकegers and strings */

		अगर ((source_desc->common.type != ACPI_TYPE_INTEGER) &&
		    (source_desc->common.type != ACPI_TYPE_STRING)) अणु
			acpi_os_म_लिखो("%s ",
				       acpi_ut_get_object_type_name
				       (source_desc));
		पूर्ण

		अगर (!acpi_ut_valid_पूर्णांकernal_object(source_desc)) अणु
			acpi_os_म_लिखो("%p, Invalid Internal Object!\n",
				       source_desc);
			वापस_VOID;
		पूर्ण
	पूर्ण अन्यथा अगर (ACPI_GET_DESCRIPTOR_TYPE(source_desc) ==
		   ACPI_DESC_TYPE_NAMED) अणु
		acpi_os_म_लिखो("%s (Node %p)\n",
			       acpi_ut_get_type_name(((काष्ठा
						       acpi_namespace_node *)
						      source_desc)->type),
			       source_desc);
		वापस_VOID;
	पूर्ण अन्यथा अणु
		वापस_VOID;
	पूर्ण

	/* source_desc is of type ACPI_DESC_TYPE_OPERAND */

	चयन (source_desc->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		/* Output correct पूर्णांकeger width */

		अगर (acpi_gbl_पूर्णांकeger_byte_width == 4) अणु
			acpi_os_म_लिखो("0x%8.8X\n",
				       (u32)source_desc->पूर्णांकeger.value);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("0x%8.8X%8.8X\n",
				       ACPI_FORMAT_UINT64(source_desc->पूर्णांकeger.
							  value));
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		acpi_os_म_लिखो("[0x%.2X]\n", (u32)source_desc->buffer.length);
		acpi_ut_dump_buffer(source_desc->buffer.poपूर्णांकer,
				    (source_desc->buffer.length < 256) ?
				    source_desc->buffer.length : 256,
				    DB_BYTE_DISPLAY, 0);
		अवरोध;

	हाल ACPI_TYPE_STRING:

		acpi_os_म_लिखो("\"%s\"\n", source_desc->string.poपूर्णांकer);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		acpi_os_म_लिखो("(Contains 0x%.2X Elements):\n",
			       source_desc->package.count);

		/* Output the entire contents of the package */

		क्रम (i = 0; i < source_desc->package.count; i++) अणु
			acpi_ex_करो_debug_object(source_desc->package.
						elements[i], level + 4, i + 1);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		acpi_os_म_लिखो("[%s] ",
			       acpi_ut_get_reference_name(source_desc));

		/* Decode the reference */

		चयन (source_desc->reference.class) अणु
		हाल ACPI_REFCLASS_INDEX:

			acpi_os_म_लिखो("0x%X\n", source_desc->reference.value);
			अवरोध;

		हाल ACPI_REFCLASS_TABLE:

			/* Case क्रम ddb_handle */

			acpi_os_म_लिखो("Table Index 0x%X\n",
				       source_desc->reference.value);
			वापस_VOID;

		शेष:

			अवरोध;
		पूर्ण

		acpi_os_म_लिखो(" ");

		/* Check क्रम valid node first, then valid object */

		अगर (source_desc->reference.node) अणु
			अगर (ACPI_GET_DESCRIPTOR_TYPE
			    (source_desc->reference.node) !=
			    ACPI_DESC_TYPE_NAMED) अणु
				acpi_os_म_लिखो
				    (" %p - Not a valid namespace node\n",
				     source_desc->reference.node);
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो("Node %p [%4.4s] ",
					       source_desc->reference.node,
					       (source_desc->reference.node)->
					       name.ascii);

				चयन ((source_desc->reference.node)->type) अणु

					/* These types have no attached object */

				हाल ACPI_TYPE_DEVICE:
					acpi_os_म_लिखो("Device\n");
					अवरोध;

				हाल ACPI_TYPE_THERMAL:
					acpi_os_म_लिखो("Thermal Zone\n");
					अवरोध;

				शेष:

					acpi_ex_करो_debug_object((source_desc->
								 reference.
								 node)->object,
								level + 4, 0);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अगर (source_desc->reference.object) अणु
			अगर (ACPI_GET_DESCRIPTOR_TYPE
			    (source_desc->reference.object) ==
			    ACPI_DESC_TYPE_NAMED) अणु

				/* Reference object is a namespace node */

				acpi_ex_करो_debug_object(ACPI_CAST_PTR
							(जोड़
							 acpi_opeअक्रम_object,
							 source_desc->reference.
							 object), level + 4, 0);
			पूर्ण अन्यथा अणु
				object_desc = source_desc->reference.object;
				value = source_desc->reference.value;

				चयन (object_desc->common.type) अणु
				हाल ACPI_TYPE_BUFFER:

					acpi_os_म_लिखो("Buffer[%u] = 0x%2.2X\n",
						       value,
						       *source_desc->reference.
						       index_poपूर्णांकer);
					अवरोध;

				हाल ACPI_TYPE_STRING:

					acpi_os_म_लिखो
					    ("String[%u] = \"%c\" (0x%2.2X)\n",
					     value,
					     *source_desc->reference.
					     index_poपूर्णांकer,
					     *source_desc->reference.
					     index_poपूर्णांकer);
					अवरोध;

				हाल ACPI_TYPE_PACKAGE:

					acpi_os_म_लिखो("Package[%u] = ", value);
					अगर (!(*source_desc->reference.where)) अणु
						acpi_os_म_लिखो
						    ("[Uninitialized Package Element]\n");
					पूर्ण अन्यथा अणु
						acpi_ex_करो_debug_object
						    (*source_desc->reference.
						     where, level + 4, 0);
					पूर्ण
					अवरोध;

				शेष:

					acpi_os_म_लिखो
					    ("Unknown Reference object type %X\n",
					     object_desc->common.type);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:

		acpi_os_म_लिखो("(Descriptor %p)\n", source_desc);
		अवरोध;
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EXEC, "\n"));
	वापस_VOID;
पूर्ण
#पूर्ण_अगर
