<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exresop - AML Interpreter opeअक्रम/object resolution
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acparser.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exresop")

/* Local prototypes */
अटल acpi_status
acpi_ex_check_object_type(acpi_object_type type_needed,
			  acpi_object_type this_type, व्योम *object);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_check_object_type
 *
 * PARAMETERS:  type_needed         Object type needed
 *              this_type           Actual object type
 *              Object              Object poपूर्णांकer
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Check required type against actual type
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_check_object_type(acpi_object_type type_needed,
			  acpi_object_type this_type, व्योम *object)
अणु
	ACPI_FUNCTION_ENTRY();

	अगर (type_needed == ACPI_TYPE_ANY) अणु

		/* All types OK, so we करोn't perक्रमm any typechecks */

		वापस (AE_OK);
	पूर्ण

	अगर (type_needed == ACPI_TYPE_LOCAL_REFERENCE) अणु
		/*
		 * Allow the AML "Constant" opcodes (Zero, One, etc.) to be reference
		 * objects and thus allow them to be tarमाला_लो. (As per the ACPI
		 * specअगरication, a store to a स्थिरant is a noop.)
		 */
		अगर ((this_type == ACPI_TYPE_INTEGER) &&
		    (((जोड़ acpi_opeअक्रम_object *)object)->common.flags &
		     AOPOBJ_AML_CONSTANT)) अणु
			वापस (AE_OK);
		पूर्ण
	पूर्ण

	अगर (type_needed != this_type) अणु
		ACPI_ERROR((AE_INFO,
			    "Needed type [%s], found [%s] %p",
			    acpi_ut_get_type_name(type_needed),
			    acpi_ut_get_type_name(this_type), object));

		वापस (AE_AML_OPERAND_TYPE);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_resolve_opeअक्रमs
 *
 * PARAMETERS:  opcode              - Opcode being पूर्णांकerpreted
 *              stack_ptr           - Poपूर्णांकer to the opeअक्रम stack to be
 *                                    resolved
 *              walk_state          - Current state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert multiple input opeअक्रमs to the types required by the
 *              target चालक.
 *
 *      Each 5-bit group in arg_types represents one required
 *      opeअक्रम and indicates the required Type. The corresponding opeअक्रम
 *      will be converted to the required type अगर possible, otherwise we
 *      पात with an exception.
 *
 ******************************************************************************/

acpi_status
acpi_ex_resolve_opeअक्रमs(u16 opcode,
			 जोड़ acpi_opeअक्रम_object **stack_ptr,
			 काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status = AE_OK;
	u8 object_type;
	u32 arg_types;
	स्थिर काष्ठा acpi_opcode_info *op_info;
	u32 this_arg_type;
	acpi_object_type type_needed;
	u16 target_op = 0;

	ACPI_FUNCTION_TRACE_U32(ex_resolve_opeअक्रमs, opcode);

	op_info = acpi_ps_get_opcode_info(opcode);
	अगर (op_info->class == AML_CLASS_UNKNOWN) अणु
		वापस_ACPI_STATUS(AE_AML_BAD_OPCODE);
	पूर्ण

	arg_types = op_info->runसमय_args;
	अगर (arg_types == ARGI_INVALID_OPCODE) अणु
		ACPI_ERROR((AE_INFO, "Unknown AML opcode 0x%X", opcode));

		वापस_ACPI_STATUS(AE_AML_INTERNAL);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Opcode %X [%s] RequiredOperandTypes=%8.8X\n",
			  opcode, op_info->name, arg_types));

	/*
	 * Normal निकास is with (arg_types == 0) at end of argument list.
	 * Function will वापस an exception from within the loop upon
	 * finding an entry which is not (or cannot be converted
	 * to) the required type; अगर stack underflows; or upon
	 * finding a शून्य stack entry (which should not happen).
	 */
	जबतक (GET_CURRENT_ARG_TYPE(arg_types)) अणु
		अगर (!stack_ptr || !*stack_ptr) अणु
			ACPI_ERROR((AE_INFO, "Null stack entry at %p",
				    stack_ptr));

			वापस_ACPI_STATUS(AE_AML_INTERNAL);
		पूर्ण

		/* Extract useful items */

		obj_desc = *stack_ptr;

		/* Decode the descriptor type */

		चयन (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) अणु
		हाल ACPI_DESC_TYPE_NAMED:

			/* Namespace Node */

			object_type =
			    ((काष्ठा acpi_namespace_node *)obj_desc)->type;

			/*
			 * Resolve an alias object. The स्थिरruction of these objects
			 * guarantees that there is only one level of alias indirection;
			 * thus, the attached object is always the aliased namespace node
			 */
			अगर (object_type == ACPI_TYPE_LOCAL_ALIAS) अणु
				obj_desc = acpi_ns_get_attached_object((काष्ठा
									acpi_namespace_node
									*)
								       obj_desc);
				*stack_ptr = obj_desc;
				object_type =
				    ((काष्ठा acpi_namespace_node *)obj_desc)->
				    type;
			पूर्ण
			अवरोध;

		हाल ACPI_DESC_TYPE_OPERAND:

			/* ACPI पूर्णांकernal object */

			object_type = obj_desc->common.type;

			/* Check क्रम bad acpi_object_type */

			अगर (!acpi_ut_valid_object_type(object_type)) अणु
				ACPI_ERROR((AE_INFO,
					    "Bad operand object type [0x%X]",
					    object_type));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण

			अगर (object_type == (u8) ACPI_TYPE_LOCAL_REFERENCE) अणु

				/* Validate the Reference */

				चयन (obj_desc->reference.class) अणु
				हाल ACPI_REFCLASS_DEBUG:

					target_op = AML_DEBUG_OP;

					ACPI_FALLTHROUGH;

				हाल ACPI_REFCLASS_ARG:
				हाल ACPI_REFCLASS_LOCAL:
				हाल ACPI_REFCLASS_INDEX:
				हाल ACPI_REFCLASS_REFOF:
				हाल ACPI_REFCLASS_TABLE:	/* ddb_handle from LOAD_OP or LOAD_TABLE_OP */
				हाल ACPI_REFCLASS_NAME:	/* Reference to a named object */

					ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
							  "Operand is a Reference, Class [%s] %2.2X\n",
							  acpi_ut_get_reference_name
							  (obj_desc),
							  obj_desc->reference.
							  class));
					अवरोध;

				शेष:

					ACPI_ERROR((AE_INFO,
						    "Unknown Reference Class 0x%2.2X in %p",
						    obj_desc->reference.class,
						    obj_desc));

					वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
				पूर्ण
			पूर्ण
			अवरोध;

		शेष:

			/* Invalid descriptor */

			ACPI_ERROR((AE_INFO, "Invalid descriptor %p [%s]",
				    obj_desc,
				    acpi_ut_get_descriptor_name(obj_desc)));

			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Get one argument type, poपूर्णांक to the next */

		this_arg_type = GET_CURRENT_ARG_TYPE(arg_types);
		INCREMENT_ARG_LIST(arg_types);

		/*
		 * Handle हालs where the object करोes not need to be
		 * resolved to a value
		 */
		चयन (this_arg_type) अणु
		हाल ARGI_REF_OR_STRING:	/* Can be a String or Reference */

			अगर ((ACPI_GET_DESCRIPTOR_TYPE(obj_desc) ==
			     ACPI_DESC_TYPE_OPERAND) &&
			    (obj_desc->common.type == ACPI_TYPE_STRING)) अणु
				/*
				 * String found - the string references a named object and
				 * must be resolved to a node
				 */
				जाओ next_opeअक्रम;
			पूर्ण

			/*
			 * Else not a string - fall through to the normal Reference
			 * हाल below
			 */
			ACPI_FALLTHROUGH;

		हाल ARGI_REFERENCE:	/* References: */
		हाल ARGI_INTEGER_REF:
		हाल ARGI_OBJECT_REF:
		हाल ARGI_DEVICE_REF:
		हाल ARGI_TARGETREF:	/* Allows implicit conversion rules beक्रमe store */
		हाल ARGI_FIXED_TARGET:	/* No implicit conversion beक्रमe store to target */
		हाल ARGI_SIMPLE_TARGET:	/* Name, Local, or arg - no implicit conversion  */
		हाल ARGI_STORE_TARGET:

			/*
			 * Need an opeअक्रम of type ACPI_TYPE_LOCAL_REFERENCE
			 * A Namespace Node is OK as-is
			 */
			अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) ==
			    ACPI_DESC_TYPE_NAMED) अणु
				जाओ next_opeअक्रम;
			पूर्ण

			status =
			    acpi_ex_check_object_type(ACPI_TYPE_LOCAL_REFERENCE,
						      object_type, obj_desc);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_DATAREFOBJ:	/* Store चालक only */
			/*
			 * We करोn't want to resolve index_op reference objects during
			 * a store because this would be an implicit de_ref_of operation.
			 * Instead, we just want to store the reference object.
			 * -- All others must be resolved below.
			 */
			अगर ((opcode == AML_STORE_OP) &&
			    ((*stack_ptr)->common.type ==
			     ACPI_TYPE_LOCAL_REFERENCE)
			    && ((*stack_ptr)->reference.class ==
				ACPI_REFCLASS_INDEX)) अणु
				जाओ next_opeअक्रम;
			पूर्ण
			अवरोध;

		शेष:

			/* All हालs covered above */

			अवरोध;
		पूर्ण

		/*
		 * Resolve this object to a value
		 */
		status = acpi_ex_resolve_to_value(stack_ptr, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Get the resolved object */

		obj_desc = *stack_ptr;

		/*
		 * Check the resulting object (value) type
		 */
		चयन (this_arg_type) अणु
			/*
			 * For the simple हालs, only one type of resolved object
			 * is allowed
			 */
		हाल ARGI_MUTEX:

			/* Need an opeअक्रम of type ACPI_TYPE_MUTEX */

			type_needed = ACPI_TYPE_MUTEX;
			अवरोध;

		हाल ARGI_EVENT:

			/* Need an opeअक्रम of type ACPI_TYPE_EVENT */

			type_needed = ACPI_TYPE_EVENT;
			अवरोध;

		हाल ARGI_PACKAGE:	/* Package */

			/* Need an opeअक्रम of type ACPI_TYPE_PACKAGE */

			type_needed = ACPI_TYPE_PACKAGE;
			अवरोध;

		हाल ARGI_ANYTYPE:

			/* Any opeअक्रम type will करो */

			type_needed = ACPI_TYPE_ANY;
			अवरोध;

		हाल ARGI_DDBHANDLE:

			/* Need an opeअक्रम of type ACPI_TYPE_DDB_HANDLE */

			type_needed = ACPI_TYPE_LOCAL_REFERENCE;
			अवरोध;

			/*
			 * The more complex हालs allow multiple resolved object types
			 */
		हाल ARGI_INTEGER:

			/*
			 * Need an opeअक्रम of type ACPI_TYPE_INTEGER, but we can
			 * implicitly convert from a STRING or BUFFER.
			 *
			 * Known as "Implicit Source Operand Conversion"
			 */
			status = acpi_ex_convert_to_पूर्णांकeger(obj_desc, stack_ptr,
							    ACPI_IMPLICIT_CONVERSION);
			अगर (ACPI_FAILURE(status)) अणु
				अगर (status == AE_TYPE) अणु
					ACPI_ERROR((AE_INFO,
						    "Needed [Integer/String/Buffer], found [%s] %p",
						    acpi_ut_get_object_type_name
						    (obj_desc), obj_desc));

					वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
				पूर्ण

				वापस_ACPI_STATUS(status);
			पूर्ण

			अगर (obj_desc != *stack_ptr) अणु
				acpi_ut_हटाओ_reference(obj_desc);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_BUFFER:
			/*
			 * Need an opeअक्रम of type ACPI_TYPE_BUFFER,
			 * But we can implicitly convert from a STRING or INTEGER
			 * aka - "Implicit Source Operand Conversion"
			 */
			status = acpi_ex_convert_to_buffer(obj_desc, stack_ptr);
			अगर (ACPI_FAILURE(status)) अणु
				अगर (status == AE_TYPE) अणु
					ACPI_ERROR((AE_INFO,
						    "Needed [Integer/String/Buffer], found [%s] %p",
						    acpi_ut_get_object_type_name
						    (obj_desc), obj_desc));

					वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
				पूर्ण

				वापस_ACPI_STATUS(status);
			पूर्ण

			अगर (obj_desc != *stack_ptr) अणु
				acpi_ut_हटाओ_reference(obj_desc);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_STRING:
			/*
			 * Need an opeअक्रम of type ACPI_TYPE_STRING,
			 * But we can implicitly convert from a BUFFER or INTEGER
			 * aka - "Implicit Source Operand Conversion"
			 */
			status =
			    acpi_ex_convert_to_string(obj_desc, stack_ptr,
						      ACPI_IMPLICIT_CONVERT_HEX);
			अगर (ACPI_FAILURE(status)) अणु
				अगर (status == AE_TYPE) अणु
					ACPI_ERROR((AE_INFO,
						    "Needed [Integer/String/Buffer], found [%s] %p",
						    acpi_ut_get_object_type_name
						    (obj_desc), obj_desc));

					वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
				पूर्ण

				वापस_ACPI_STATUS(status);
			पूर्ण

			अगर (obj_desc != *stack_ptr) अणु
				acpi_ut_हटाओ_reference(obj_desc);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_COMPUTEDATA:

			/* Need an opeअक्रम of type INTEGER, STRING or BUFFER */

			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_INTEGER:
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_BUFFER:

				/* Valid opeअक्रम */
				अवरोध;

			शेष:
				ACPI_ERROR((AE_INFO,
					    "Needed [Integer/String/Buffer], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_BUFFER_OR_STRING:

			/* Need an opeअक्रम of type STRING or BUFFER */

			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_BUFFER:

				/* Valid opeअक्रम */
				अवरोध;

			हाल ACPI_TYPE_INTEGER:

				/* Highest priority conversion is to type Buffer */

				status =
				    acpi_ex_convert_to_buffer(obj_desc,
							      stack_ptr);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				अगर (obj_desc != *stack_ptr) अणु
					acpi_ut_हटाओ_reference(obj_desc);
				पूर्ण
				अवरोध;

			शेष:
				ACPI_ERROR((AE_INFO,
					    "Needed [Integer/String/Buffer], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_DATAOBJECT:
			/*
			 * ARGI_DATAOBJECT is only used by the size_of चालक.
			 * Need a buffer, string, package, or ref_of reference.
			 *
			 * The only reference allowed here is a direct reference to
			 * a namespace node.
			 */
			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_PACKAGE:
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_BUFFER:
			हाल ACPI_TYPE_LOCAL_REFERENCE:

				/* Valid opeअक्रम */
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Needed [Buffer/String/Package/Reference], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_COMPLEXOBJ:

			/* Need a buffer or package or (ACPI 2.0) String */

			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_PACKAGE:
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_BUFFER:

				/* Valid opeअक्रम */
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Needed [Buffer/String/Package], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_REGION_OR_BUFFER:	/* Used by Load() only */

			/*
			 * Need an opeअक्रम of type REGION or a BUFFER
			 * (which could be a resolved region field)
			 */
			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_BUFFER:
			हाल ACPI_TYPE_REGION:

				/* Valid opeअक्रम */
				अवरोध;

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Needed [Region/Buffer], found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			जाओ next_opeअक्रम;

		हाल ARGI_DATAREFOBJ:

			/* Used by the Store() चालक only */

			चयन (obj_desc->common.type) अणु
			हाल ACPI_TYPE_INTEGER:
			हाल ACPI_TYPE_PACKAGE:
			हाल ACPI_TYPE_STRING:
			हाल ACPI_TYPE_BUFFER:
			हाल ACPI_TYPE_BUFFER_FIELD:
			हाल ACPI_TYPE_LOCAL_REFERENCE:
			हाल ACPI_TYPE_LOCAL_REGION_FIELD:
			हाल ACPI_TYPE_LOCAL_BANK_FIELD:
			हाल ACPI_TYPE_LOCAL_INDEX_FIELD:
			हाल ACPI_TYPE_DDB_HANDLE:

				/* Valid opeअक्रम */
				अवरोध;

			शेष:

				अगर (acpi_gbl_enable_पूर्णांकerpreter_slack) अणु
					/*
					 * Enable original behavior of Store(), allowing any
					 * and all objects as the source opeअक्रम. The ACPI
					 * spec करोes not allow this, however.
					 */
					अवरोध;
				पूर्ण

				अगर (target_op == AML_DEBUG_OP) अणु

					/* Allow store of any object to the Debug object */

					अवरोध;
				पूर्ण

				ACPI_ERROR((AE_INFO,
					    "Needed Integer/Buffer/String/Package/Ref/Ddb]"
					    ", found [%s] %p",
					    acpi_ut_get_object_type_name
					    (obj_desc), obj_desc));

				वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
			पूर्ण
			जाओ next_opeअक्रम;

		शेष:

			/* Unknown type */

			ACPI_ERROR((AE_INFO,
				    "Internal - Unknown ARGI (required operand) type 0x%X",
				    this_arg_type));

			वापस_ACPI_STATUS(AE_BAD_PARAMETER);
		पूर्ण

		/*
		 * Make sure that the original object was resolved to the
		 * required object type (Simple हालs only).
		 */
		status =
		    acpi_ex_check_object_type(type_needed,
					      (*stack_ptr)->common.type,
					      *stack_ptr);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

next_opeअक्रम:
		/*
		 * If more opeअक्रमs needed, decrement stack_ptr to poपूर्णांक
		 * to next opeअक्रम on stack
		 */
		अगर (GET_CURRENT_ARG_TYPE(arg_types)) अणु
			stack_ptr--;
		पूर्ण
	पूर्ण

	ACPI_DUMP_OPERANDS(walk_state->opeअक्रमs,
			   acpi_ps_get_opcode_name(opcode),
			   walk_state->num_opeअक्रमs);

	वापस_ACPI_STATUS(status);
पूर्ण
