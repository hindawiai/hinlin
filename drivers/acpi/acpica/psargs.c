<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: psargs - Parse AML opcode arguments
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"
#समावेश "acdispat.h"
#समावेश "acconvert.h"

#घोषणा _COMPONENT          ACPI_PARSER
ACPI_MODULE_NAME("psargs")

/* Local prototypes */
अटल u32
acpi_ps_get_next_package_length(काष्ठा acpi_parse_state *parser_state);

अटल जोड़ acpi_parse_object *acpi_ps_get_next_field(काष्ठा acpi_parse_state
						       *parser_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_package_length
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      Decoded package length. On completion, the AML poपूर्णांकer poपूर्णांकs
 *              past the length byte or bytes.
 *
 * DESCRIPTION: Decode and वापस a package length field.
 *              Note: Largest package length is 28 bits, from ACPI specअगरication
 *
 ******************************************************************************/

अटल u32
acpi_ps_get_next_package_length(काष्ठा acpi_parse_state *parser_state)
अणु
	u8 *aml = parser_state->aml;
	u32 package_length = 0;
	u32 byte_count;
	u8 byte_zero_mask = 0x3F;	/* Default [0:5] */

	ACPI_FUNCTION_TRACE(ps_get_next_package_length);

	/*
	 * Byte 0 bits [6:7] contain the number of additional bytes
	 * used to encode the package length, either 0,1,2, or 3
	 */
	byte_count = (aml[0] >> 6);
	parser_state->aml += ((acpi_size)byte_count + 1);

	/* Get bytes 3, 2, 1 as needed */

	जबतक (byte_count) अणु
		/*
		 * Final bit positions क्रम the package length bytes:
		 *      Byte3->[20:27]
		 *      Byte2->[12:19]
		 *      Byte1->[04:11]
		 *      Byte0->[00:03]
		 */
		package_length |= (aml[byte_count] << ((byte_count << 3) - 4));

		byte_zero_mask = 0x0F;	/* Use bits [0:3] of byte 0 */
		byte_count--;
	पूर्ण

	/* Byte 0 is a special हाल, either bits [0:3] or [0:5] are used */

	package_length |= (aml[0] & byte_zero_mask);
	वापस_UINT32(package_length);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_package_end
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      Poपूर्णांकer to end-of-package +1
 *
 * DESCRIPTION: Get next package length and वापस a poपूर्णांकer past the end of
 *              the package. Consumes the package length field
 *
 ******************************************************************************/

u8 *acpi_ps_get_next_package_end(काष्ठा acpi_parse_state *parser_state)
अणु
	u8 *start = parser_state->aml;
	u32 package_length;

	ACPI_FUNCTION_TRACE(ps_get_next_package_end);

	/* Function below updates parser_state->Aml */

	package_length = acpi_ps_get_next_package_length(parser_state);

	वापस_PTR(start + package_length);	/* end of package */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_namestring
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      Poपूर्णांकer to the start of the name string (poपूर्णांकer poपूर्णांकs पूर्णांकo
 *              the AML.
 *
 * DESCRIPTION: Get next raw namestring within the AML stream. Handles all name
 *              prefix अक्षरacters. Set parser state to poपूर्णांक past the string.
 *              (Name is consumed from the AML.)
 *
 ******************************************************************************/

अक्षर *acpi_ps_get_next_namestring(काष्ठा acpi_parse_state *parser_state)
अणु
	u8 *start = parser_state->aml;
	u8 *end = parser_state->aml;

	ACPI_FUNCTION_TRACE(ps_get_next_namestring);

	/* Poपूर्णांक past any namestring prefix अक्षरacters (backslash or carat) */

	जबतक (ACPI_IS_ROOT_PREFIX(*end) || ACPI_IS_PARENT_PREFIX(*end)) अणु
		end++;
	पूर्ण

	/* Decode the path prefix अक्षरacter */

	चयन (*end) अणु
	हाल 0:

		/* null_name */

		अगर (end == start) अणु
			start = शून्य;
		पूर्ण
		end++;
		अवरोध;

	हाल AML_DUAL_NAME_PREFIX:

		/* Two name segments */

		end += 1 + (2 * ACPI_NAMESEG_SIZE);
		अवरोध;

	हाल AML_MULTI_NAME_PREFIX:

		/* Multiple name segments, 4 अक्षरs each, count in next byte */

		end += 2 + (*(end + 1) * ACPI_NAMESEG_SIZE);
		अवरोध;

	शेष:

		/* Single name segment */

		end += ACPI_NAMESEG_SIZE;
		अवरोध;
	पूर्ण

	parser_state->aml = end;
	वापस_PTR((अक्षर *)start);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_namepath
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *              arg                 - Where the namepath will be stored
 *              arg_count           - If the namepath poपूर्णांकs to a control method
 *                                    the method's argument is वापसed here.
 *              possible_method_call - Whether the namepath can possibly be the
 *                                    start of a method call
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Get next name (अगर method call, वापस # of required args).
 *              Names are looked up in the पूर्णांकernal namespace to determine
 *              अगर the name represents a control method. If a method
 *              is found, the number of arguments to the method is वापसed.
 *              This inक्रमmation is critical क्रम parsing to जारी correctly.
 *
 ******************************************************************************/

acpi_status
acpi_ps_get_next_namepath(काष्ठा acpi_walk_state *walk_state,
			  काष्ठा acpi_parse_state *parser_state,
			  जोड़ acpi_parse_object *arg, u8 possible_method_call)
अणु
	acpi_status status;
	अक्षर *path;
	जोड़ acpi_parse_object *name_op;
	जोड़ acpi_opeअक्रम_object *method_desc;
	काष्ठा acpi_namespace_node *node;
	u8 *start = parser_state->aml;

	ACPI_FUNCTION_TRACE(ps_get_next_namepath);

	path = acpi_ps_get_next_namestring(parser_state);
	acpi_ps_init_op(arg, AML_INT_NAMEPATH_OP);

	/* Null path हाल is allowed, just निकास */

	अगर (!path) अणु
		arg->common.value.name = path;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Lookup the name in the पूर्णांकernal namespace, starting with the current
	 * scope. We करोn't want to add anything new to the namespace here,
	 * however, so we use MODE_EXECUTE.
	 * Allow searching of the parent tree, but करोn't खोलो a new scope -
	 * we just want to lookup the object (must be mode EXECUTE to perक्रमm
	 * the upsearch)
	 */
	status = acpi_ns_lookup(walk_state->scope_info, path,
				ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE,
				ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
				शून्य, &node);

	/*
	 * If this name is a control method invocation, we must
	 * setup the method call
	 */
	अगर (ACPI_SUCCESS(status) &&
	    possible_method_call && (node->type == ACPI_TYPE_METHOD)) अणु
		अगर ((GET_CURRENT_ARG_TYPE(walk_state->arg_types) ==
		     ARGP_SUPERNAME)
		    || (GET_CURRENT_ARG_TYPE(walk_state->arg_types) ==
			ARGP_TARGET)) अणु
			/*
			 * acpi_ps_get_next_namestring has increased the AML poपूर्णांकer past
			 * the method invocation namestring, so we need to restore the
			 * saved AML poपूर्णांकer back to the original method invocation
			 * namestring.
			 */
			walk_state->parser_state.aml = start;
			walk_state->arg_count = 1;
			acpi_ps_init_op(arg, AML_INT_METHODCALL_OP);
		पूर्ण

		/* This name is actually a control method invocation */

		method_desc = acpi_ns_get_attached_object(node);
		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Control Method invocation %4.4s - %p Desc %p Path=%p\n",
				  node->name.ascii, node, method_desc, path));

		name_op = acpi_ps_alloc_op(AML_INT_NAMEPATH_OP, start);
		अगर (!name_op) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		/* Change Arg पूर्णांकo a METHOD CALL and attach name to it */

		acpi_ps_init_op(arg, AML_INT_METHODCALL_OP);
		name_op->common.value.name = path;

		/* Poपूर्णांक METHODCALL/NAME to the METHOD Node */

		name_op->common.node = node;
		acpi_ps_append_arg(arg, name_op);

		अगर (!method_desc) अणु
			ACPI_ERROR((AE_INFO,
				    "Control Method %p has no attached object",
				    node));
			वापस_ACPI_STATUS(AE_AML_INTERNAL);
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "Control Method - %p Args %X\n",
				  node, method_desc->method.param_count));

		/* Get the number of arguments to expect */

		walk_state->arg_count = method_desc->method.param_count;
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Special handling अगर the name was not found during the lookup -
	 * some not_found हालs are allowed
	 */
	अगर (status == AE_NOT_FOUND) अणु

		/* 1) not_found is ok during load pass 1/2 (allow क्रमward references) */

		अगर ((walk_state->parse_flags & ACPI_PARSE_MODE_MASK) !=
		    ACPI_PARSE_EXECUTE) अणु
			status = AE_OK;
		पूर्ण

		/* 2) not_found during a cond_ref_of(x) is ok by definition */

		अन्यथा अगर (walk_state->op->common.aml_opcode ==
			 AML_CONDITIONAL_REF_OF_OP) अणु
			status = AE_OK;
		पूर्ण

		/*
		 * 3) not_found जबतक building a Package is ok at this poपूर्णांक, we
		 * may flag as an error later अगर slack mode is not enabled.
		 * (Some ASL code depends on allowing this behavior)
		 */
		अन्यथा अगर ((arg->common.parent) &&
			 ((arg->common.parent->common.aml_opcode ==
			   AML_PACKAGE_OP)
			  || (arg->common.parent->common.aml_opcode ==
			      AML_VARIABLE_PACKAGE_OP))) अणु
			status = AE_OK;
		पूर्ण
	पूर्ण

	/* Final exception check (may have been changed from code above) */

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR_NAMESPACE(walk_state->scope_info, path, status);

		अगर ((walk_state->parse_flags & ACPI_PARSE_MODE_MASK) ==
		    ACPI_PARSE_EXECUTE) अणु

			/* Report a control method execution error */

			status = acpi_ds_method_error(status, walk_state);
		पूर्ण
	पूर्ण

	/* Save the namepath */

	arg->common.value.name = path;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_simple_arg
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *              arg_type            - The argument type (AML_*_ARG)
 *              arg                 - Where the argument is वापसed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get the next simple argument (स्थिरant, string, or namestring)
 *
 ******************************************************************************/

व्योम
acpi_ps_get_next_simple_arg(काष्ठा acpi_parse_state *parser_state,
			    u32 arg_type, जोड़ acpi_parse_object *arg)
अणु
	u32 length;
	u16 opcode;
	u8 *aml = parser_state->aml;

	ACPI_FUNCTION_TRACE_U32(ps_get_next_simple_arg, arg_type);

	चयन (arg_type) अणु
	हाल ARGP_BYTEDATA:

		/* Get 1 byte from the AML stream */

		opcode = AML_BYTE_OP;
		arg->common.value.पूर्णांकeger = (u64) *aml;
		length = 1;
		अवरोध;

	हाल ARGP_WORDDATA:

		/* Get 2 bytes from the AML stream */

		opcode = AML_WORD_OP;
		ACPI_MOVE_16_TO_64(&arg->common.value.पूर्णांकeger, aml);
		length = 2;
		अवरोध;

	हाल ARGP_DWORDDATA:

		/* Get 4 bytes from the AML stream */

		opcode = AML_DWORD_OP;
		ACPI_MOVE_32_TO_64(&arg->common.value.पूर्णांकeger, aml);
		length = 4;
		अवरोध;

	हाल ARGP_QWORDDATA:

		/* Get 8 bytes from the AML stream */

		opcode = AML_QWORD_OP;
		ACPI_MOVE_64_TO_64(&arg->common.value.पूर्णांकeger, aml);
		length = 8;
		अवरोध;

	हाल ARGP_CHARLIST:

		/* Get a poपूर्णांकer to the string, poपूर्णांक past the string */

		opcode = AML_STRING_OP;
		arg->common.value.string = ACPI_CAST_PTR(अक्षर, aml);

		/* Find the null terminator */

		length = 0;
		जबतक (aml[length]) अणु
			length++;
		पूर्ण
		length++;
		अवरोध;

	हाल ARGP_NAME:
	हाल ARGP_NAMESTRING:

		acpi_ps_init_op(arg, AML_INT_NAMEPATH_OP);
		arg->common.value.name =
		    acpi_ps_get_next_namestring(parser_state);
		वापस_VOID;

	शेष:

		ACPI_ERROR((AE_INFO, "Invalid ArgType 0x%X", arg_type));
		वापस_VOID;
	पूर्ण

	acpi_ps_init_op(arg, opcode);
	parser_state->aml += length;
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_field
 *
 * PARAMETERS:  parser_state        - Current parser state object
 *
 * RETURN:      A newly allocated FIELD op
 *
 * DESCRIPTION: Get next field (named_field, reserved_field, or access_field)
 *
 ******************************************************************************/

अटल जोड़ acpi_parse_object *acpi_ps_get_next_field(काष्ठा acpi_parse_state
						       *parser_state)
अणु
	u8 *aml;
	जोड़ acpi_parse_object *field;
	जोड़ acpi_parse_object *arg = शून्य;
	u16 opcode;
	u32 name;
	u8 access_type;
	u8 access_attribute;
	u8 access_length;
	u32 pkg_length;
	u8 *pkg_end;
	u32 buffer_length;

	ACPI_FUNCTION_TRACE(ps_get_next_field);

	ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
	aml = parser_state->aml;

	/* Determine field type */

	चयन (ACPI_GET8(parser_state->aml)) अणु
	हाल AML_FIELD_OFFSET_OP:

		opcode = AML_INT_RESERVEDFIELD_OP;
		parser_state->aml++;
		अवरोध;

	हाल AML_FIELD_ACCESS_OP:

		opcode = AML_INT_ACCESSFIELD_OP;
		parser_state->aml++;
		अवरोध;

	हाल AML_FIELD_CONNECTION_OP:

		opcode = AML_INT_CONNECTION_OP;
		parser_state->aml++;
		अवरोध;

	हाल AML_FIELD_EXT_ACCESS_OP:

		opcode = AML_INT_EXTACCESSFIELD_OP;
		parser_state->aml++;
		अवरोध;

	शेष:

		opcode = AML_INT_NAMEDFIELD_OP;
		अवरोध;
	पूर्ण

	/* Allocate a new field op */

	field = acpi_ps_alloc_op(opcode, aml);
	अगर (!field) अणु
		वापस_PTR(शून्य);
	पूर्ण

	/* Decode the field type */

	ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
	चयन (opcode) अणु
	हाल AML_INT_NAMEDFIELD_OP:

		/* Get the 4-अक्षरacter name */

		ACPI_MOVE_32_TO_32(&name, parser_state->aml);
		acpi_ps_set_name(field, name);
		parser_state->aml += ACPI_NAMESEG_SIZE;

		ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);

#अगर_घोषित ACPI_ASL_COMPILER
		/*
		 * Because the package length isn't represented as a parse tree object,
		 * take comments surrounding this and add to the previously created
		 * parse node.
		 */
		अगर (field->common.अंतरभूत_comment) अणु
			field->common.name_comment =
			    field->common.अंतरभूत_comment;
		पूर्ण
		field->common.अंतरभूत_comment = acpi_gbl_current_अंतरभूत_comment;
		acpi_gbl_current_अंतरभूत_comment = शून्य;
#पूर्ण_अगर

		/* Get the length which is encoded as a package length */

		field->common.value.size =
		    acpi_ps_get_next_package_length(parser_state);
		अवरोध;

	हाल AML_INT_RESERVEDFIELD_OP:

		/* Get the length which is encoded as a package length */

		field->common.value.size =
		    acpi_ps_get_next_package_length(parser_state);
		अवरोध;

	हाल AML_INT_ACCESSFIELD_OP:
	हाल AML_INT_EXTACCESSFIELD_OP:

		/*
		 * Get access_type and access_attrib and merge पूर्णांकo the field Op
		 * access_type is first opeअक्रम, access_attribute is second. stuff
		 * these bytes पूर्णांकo the node पूर्णांकeger value क्रम convenience.
		 */

		/* Get the two bytes (Type/Attribute) */

		access_type = ACPI_GET8(parser_state->aml);
		parser_state->aml++;
		access_attribute = ACPI_GET8(parser_state->aml);
		parser_state->aml++;

		field->common.value.पूर्णांकeger = (u8)access_type;
		field->common.value.पूर्णांकeger |= (u16)(access_attribute << 8);

		/* This opcode has a third byte, access_length */

		अगर (opcode == AML_INT_EXTACCESSFIELD_OP) अणु
			access_length = ACPI_GET8(parser_state->aml);
			parser_state->aml++;

			field->common.value.पूर्णांकeger |=
			    (u32)(access_length << 16);
		पूर्ण
		अवरोध;

	हाल AML_INT_CONNECTION_OP:

		/*
		 * Argument क्रम Connection चालक can be either a Buffer
		 * (resource descriptor), or a name_string.
		 */
		aml = parser_state->aml;
		अगर (ACPI_GET8(parser_state->aml) == AML_BUFFER_OP) अणु
			parser_state->aml++;

			ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
			pkg_end = parser_state->aml;
			pkg_length =
			    acpi_ps_get_next_package_length(parser_state);
			pkg_end += pkg_length;

			ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
			अगर (parser_state->aml < pkg_end) अणु

				/* Non-empty list */

				arg =
				    acpi_ps_alloc_op(AML_INT_BYTELIST_OP, aml);
				अगर (!arg) अणु
					acpi_ps_मुक्त_op(field);
					वापस_PTR(शून्य);
				पूर्ण

				/* Get the actual buffer length argument */

				opcode = ACPI_GET8(parser_state->aml);
				parser_state->aml++;

				ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
				चयन (opcode) अणु
				हाल AML_BYTE_OP:	/* AML_BYTEDATA_ARG */

					buffer_length =
					    ACPI_GET8(parser_state->aml);
					parser_state->aml += 1;
					अवरोध;

				हाल AML_WORD_OP:	/* AML_WORDDATA_ARG */

					buffer_length =
					    ACPI_GET16(parser_state->aml);
					parser_state->aml += 2;
					अवरोध;

				हाल AML_DWORD_OP:	/* AML_DWORDATA_ARG */

					buffer_length =
					    ACPI_GET32(parser_state->aml);
					parser_state->aml += 4;
					अवरोध;

				शेष:

					buffer_length = 0;
					अवरोध;
				पूर्ण

				/* Fill in bytelist data */

				ASL_CV_CAPTURE_COMMENTS_ONLY(parser_state);
				arg->named.value.size = buffer_length;
				arg->named.data = parser_state->aml;
			पूर्ण

			/* Skip to End of byte data */

			parser_state->aml = pkg_end;
		पूर्ण अन्यथा अणु
			arg = acpi_ps_alloc_op(AML_INT_NAMEPATH_OP, aml);
			अगर (!arg) अणु
				acpi_ps_मुक्त_op(field);
				वापस_PTR(शून्य);
			पूर्ण

			/* Get the Namestring argument */

			arg->common.value.name =
			    acpi_ps_get_next_namestring(parser_state);
		पूर्ण

		/* Link the buffer/namestring to parent (CONNECTION_OP) */

		acpi_ps_append_arg(field, arg);
		अवरोध;

	शेष:

		/* Opcode was set in previous चयन */
		अवरोध;
	पूर्ण

	वापस_PTR(field);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ps_get_next_arg
 *
 * PARAMETERS:  walk_state          - Current state
 *              parser_state        - Current parser state object
 *              arg_type            - The argument type (AML_*_ARG)
 *              वापस_arg          - Where the next arg is वापसed
 *
 * RETURN:      Status, and an op object containing the next argument.
 *
 * DESCRIPTION: Get next argument (including complex list arguments that require
 *              pushing the parser stack)
 *
 ******************************************************************************/

acpi_status
acpi_ps_get_next_arg(काष्ठा acpi_walk_state *walk_state,
		     काष्ठा acpi_parse_state *parser_state,
		     u32 arg_type, जोड़ acpi_parse_object **वापस_arg)
अणु
	जोड़ acpi_parse_object *arg = शून्य;
	जोड़ acpi_parse_object *prev = शून्य;
	जोड़ acpi_parse_object *field;
	u32 subop;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_PTR(ps_get_next_arg, parser_state);

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
			  "Expected argument type ARGP: %s (%2.2X)\n",
			  acpi_ut_get_argument_type_name(arg_type), arg_type));

	चयन (arg_type) अणु
	हाल ARGP_BYTEDATA:
	हाल ARGP_WORDDATA:
	हाल ARGP_DWORDDATA:
	हाल ARGP_CHARLIST:
	हाल ARGP_NAME:
	हाल ARGP_NAMESTRING:

		/* Constants, strings, and namestrings are all the same size */

		arg = acpi_ps_alloc_op(AML_BYTE_OP, parser_state->aml);
		अगर (!arg) अणु
			वापस_ACPI_STATUS(AE_NO_MEMORY);
		पूर्ण

		acpi_ps_get_next_simple_arg(parser_state, arg_type, arg);
		अवरोध;

	हाल ARGP_PKGLENGTH:

		/* Package length, nothing वापसed */

		parser_state->pkg_end =
		    acpi_ps_get_next_package_end(parser_state);
		अवरोध;

	हाल ARGP_FIELDLIST:

		अगर (parser_state->aml < parser_state->pkg_end) अणु

			/* Non-empty list */

			जबतक (parser_state->aml < parser_state->pkg_end) अणु
				field = acpi_ps_get_next_field(parser_state);
				अगर (!field) अणु
					वापस_ACPI_STATUS(AE_NO_MEMORY);
				पूर्ण

				अगर (prev) अणु
					prev->common.next = field;
				पूर्ण अन्यथा अणु
					arg = field;
				पूर्ण
				prev = field;
			पूर्ण

			/* Skip to End of byte data */

			parser_state->aml = parser_state->pkg_end;
		पूर्ण
		अवरोध;

	हाल ARGP_BYTELIST:

		अगर (parser_state->aml < parser_state->pkg_end) अणु

			/* Non-empty list */

			arg = acpi_ps_alloc_op(AML_INT_BYTELIST_OP,
					       parser_state->aml);
			अगर (!arg) अणु
				वापस_ACPI_STATUS(AE_NO_MEMORY);
			पूर्ण

			/* Fill in bytelist data */

			arg->common.value.size = (u32)
			    ACPI_PTR_DIFF(parser_state->pkg_end,
					  parser_state->aml);
			arg->named.data = parser_state->aml;

			/* Skip to End of byte data */

			parser_state->aml = parser_state->pkg_end;
		पूर्ण
		अवरोध;

	हाल ARGP_SIMPLENAME:
	हाल ARGP_NAME_OR_REF:

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "**** SimpleName/NameOrRef: %s (%2.2X)\n",
				  acpi_ut_get_argument_type_name(arg_type),
				  arg_type));

		subop = acpi_ps_peek_opcode(parser_state);
		अगर (subop == 0 ||
		    acpi_ps_is_leading_अक्षर(subop) ||
		    ACPI_IS_ROOT_PREFIX(subop) ||
		    ACPI_IS_PARENT_PREFIX(subop)) अणु

			/* null_name or name_string */

			arg =
			    acpi_ps_alloc_op(AML_INT_NAMEPATH_OP,
					     parser_state->aml);
			अगर (!arg) अणु
				वापस_ACPI_STATUS(AE_NO_MEMORY);
			पूर्ण

			status =
			    acpi_ps_get_next_namepath(walk_state, parser_state,
						      arg,
						      ACPI_NOT_METHOD_CALL);
		पूर्ण अन्यथा अणु
			/* Single complex argument, nothing वापसed */

			walk_state->arg_count = 1;
		पूर्ण
		अवरोध;

	हाल ARGP_TARGET:
	हाल ARGP_SUPERNAME:

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "**** Target/Supername: %s (%2.2X)\n",
				  acpi_ut_get_argument_type_name(arg_type),
				  arg_type));

		subop = acpi_ps_peek_opcode(parser_state);
		अगर (subop == 0 ||
		    acpi_ps_is_leading_अक्षर(subop) ||
		    ACPI_IS_ROOT_PREFIX(subop) ||
		    ACPI_IS_PARENT_PREFIX(subop)) अणु

			/* शून्य target (zero). Convert to a शून्य namepath */

			arg =
			    acpi_ps_alloc_op(AML_INT_NAMEPATH_OP,
					     parser_state->aml);
			अगर (!arg) अणु
				वापस_ACPI_STATUS(AE_NO_MEMORY);
			पूर्ण

			status =
			    acpi_ps_get_next_namepath(walk_state, parser_state,
						      arg,
						      ACPI_POSSIBLE_METHOD_CALL);

			अगर (arg->common.aml_opcode == AML_INT_METHODCALL_OP) अणु

				/* Free method call op and corresponding namestring sub-ob */

				acpi_ps_मुक्त_op(arg->common.value.arg);
				acpi_ps_मुक्त_op(arg);
				arg = शून्य;
				walk_state->arg_count = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Single complex argument, nothing वापसed */

			walk_state->arg_count = 1;
		पूर्ण
		अवरोध;

	हाल ARGP_DATAOBJ:
	हाल ARGP_TERMARG:

		ACPI_DEBUG_PRINT((ACPI_DB_PARSE,
				  "**** TermArg/DataObj: %s (%2.2X)\n",
				  acpi_ut_get_argument_type_name(arg_type),
				  arg_type));

		/* Single complex argument, nothing वापसed */

		walk_state->arg_count = 1;
		अवरोध;

	हाल ARGP_DATAOBJLIST:
	हाल ARGP_TERMLIST:
	हाल ARGP_OBJLIST:

		अगर (parser_state->aml < parser_state->pkg_end) अणु

			/* Non-empty list of variable arguments, nothing वापसed */

			walk_state->arg_count = ACPI_VAR_ARGS;
		पूर्ण
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Invalid ArgType: 0x%X", arg_type));
		status = AE_AML_OPERAND_TYPE;
		अवरोध;
	पूर्ण

	*वापस_arg = arg;
	वापस_ACPI_STATUS(status);
पूर्ण
