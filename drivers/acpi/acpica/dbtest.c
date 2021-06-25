<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbtest - Various debug-related tests
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"
#समावेश "acnamesp.h"
#समावेश "acpredef.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbtest")

/* Local prototypes */
अटल व्योम acpi_db_test_all_objects(व्योम);

अटल acpi_status
acpi_db_test_one_object(acpi_handle obj_handle,
			u32 nesting_level, व्योम *context, व्योम **वापस_value);

अटल acpi_status
acpi_db_test_पूर्णांकeger_type(काष्ठा acpi_namespace_node *node, u32 bit_length);

अटल acpi_status
acpi_db_test_buffer_type(काष्ठा acpi_namespace_node *node, u32 bit_length);

अटल acpi_status
acpi_db_test_string_type(काष्ठा acpi_namespace_node *node, u32 byte_length);

अटल acpi_status acpi_db_test_package_type(काष्ठा acpi_namespace_node *node);

अटल acpi_status
acpi_db_test_field_unit_type(जोड़ acpi_opeअक्रम_object *obj_desc);

अटल acpi_status
acpi_db_पढ़ो_from_object(काष्ठा acpi_namespace_node *node,
			 acpi_object_type expected_type,
			 जोड़ acpi_object **value);

अटल acpi_status
acpi_db_ग_लिखो_to_object(काष्ठा acpi_namespace_node *node,
			जोड़ acpi_object *value);

अटल व्योम acpi_db_evaluate_all_predefined_names(अक्षर *count_arg);

अटल acpi_status
acpi_db_evaluate_one_predefined_name(acpi_handle obj_handle,
				     u32 nesting_level,
				     व्योम *context, व्योम **वापस_value);

/*
 * Test subcommands
 */
अटल काष्ठा acpi_db_argument_info acpi_db_test_types[] = अणु
	अणु"OBJECTS"पूर्ण,
	अणु"PREDEFINED"पूर्ण,
	अणुशून्यपूर्ण			/* Must be null terminated */
पूर्ण;

#घोषणा CMD_TEST_OBJECTS        0
#घोषणा CMD_TEST_PREDEFINED     1

#घोषणा BUFFER_FILL_VALUE       0xFF

/*
 * Support क्रम the special debugger पढ़ो/ग_लिखो control methods.
 * These methods are installed पूर्णांकo the current namespace and are
 * used to पढ़ो and ग_लिखो the various namespace objects. The poपूर्णांक
 * is to क्रमce the AML पूर्णांकerpreter करो all of the work.
 */
#घोषणा ACPI_DB_READ_METHOD     "\\_T98"
#घोषणा ACPI_DB_WRITE_METHOD    "\\_T99"

अटल acpi_handle पढ़ो_handle = शून्य;
अटल acpi_handle ग_लिखो_handle = शून्य;

/* ASL Definitions of the debugger पढ़ो/ग_लिखो control methods. AML below. */

#अगर 0
definition_block("ssdt.aml", "SSDT", 2, "Intel", "DEBUG", 0x00000001)
अणु
	method(_T98, 1, not_serialized) अणु	/* Read */
		वापस (de_ref_of(arg0))
	पूर्ण
पूर्ण

definition_block("ssdt2.aml", "SSDT", 2, "Intel", "DEBUG", 0x00000001)
अणु
	method(_T99, 2, not_serialized) अणु	/* Write */
		store(arg1, arg0)
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल अचिन्हित अक्षर पढ़ो_method_code[] = अणु
	0x53, 0x53, 0x44, 0x54, 0x2E, 0x00, 0x00, 0x00,	/* 00000000    "SSDT...." */
	0x02, 0xC9, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,	/* 00000008    "..Intel." */
	0x44, 0x45, 0x42, 0x55, 0x47, 0x00, 0x00, 0x00,	/* 00000010    "DEBUG..." */
	0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,	/* 00000018    "....INTL" */
	0x18, 0x12, 0x13, 0x20, 0x14, 0x09, 0x5F, 0x54,	/* 00000020    "... .._T" */
	0x39, 0x38, 0x01, 0xA4, 0x83, 0x68	/* 00000028    "98...h"   */
पूर्ण;

अटल अचिन्हित अक्षर ग_लिखो_method_code[] = अणु
	0x53, 0x53, 0x44, 0x54, 0x2E, 0x00, 0x00, 0x00,	/* 00000000    "SSDT...." */
	0x02, 0x15, 0x49, 0x6E, 0x74, 0x65, 0x6C, 0x00,	/* 00000008    "..Intel." */
	0x44, 0x45, 0x42, 0x55, 0x47, 0x00, 0x00, 0x00,	/* 00000010    "DEBUG..." */
	0x01, 0x00, 0x00, 0x00, 0x49, 0x4E, 0x54, 0x4C,	/* 00000018    "....INTL" */
	0x18, 0x12, 0x13, 0x20, 0x14, 0x09, 0x5F, 0x54,	/* 00000020    "... .._T" */
	0x39, 0x39, 0x02, 0x70, 0x69, 0x68	/* 00000028    "99.pih"   */
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute_test
 *
 * PARAMETERS:  type_arg        - Subcommand
 *
 * RETURN:      None
 *
 * DESCRIPTION: Execute various debug tests.
 *
 * Note: Code is prepared क्रम future expansion of the TEST command.
 *
 ******************************************************************************/

व्योम acpi_db_execute_test(अक्षर *type_arg)
अणु
	u32 temp;

	acpi_ut_strupr(type_arg);
	temp = acpi_db_match_argument(type_arg, acpi_db_test_types);
	अगर (temp == ACPI_TYPE_NOT_FOUND) अणु
		acpi_os_म_लिखो("Invalid or unsupported argument\n");
		वापस;
	पूर्ण

	चयन (temp) अणु
	हाल CMD_TEST_OBJECTS:

		acpi_db_test_all_objects();
		अवरोध;

	हाल CMD_TEST_PREDEFINED:

		acpi_db_evaluate_all_predefined_names(शून्य);
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_all_objects
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: This test implements the OBJECTS subcommand. It exercises the
 *              namespace by पढ़ोing/writing/comparing all data objects such
 *              as पूर्णांकegers, strings, buffers, fields, buffer fields, etc.
 *
 ******************************************************************************/

अटल व्योम acpi_db_test_all_objects(व्योम)
अणु
	acpi_status status;

	/* Install the debugger पढ़ो-object control method अगर necessary */

	अगर (!पढ़ो_handle) अणु
		status = acpi_install_method(पढ़ो_method_code);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    ("%s, Could not install debugger read method\n",
			     acpi_क्रमmat_exception(status));
			वापस;
		पूर्ण

		status =
		    acpi_get_handle(शून्य, ACPI_DB_READ_METHOD, &पढ़ो_handle);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    ("Could not obtain handle for debug method %s\n",
			     ACPI_DB_READ_METHOD);
			वापस;
		पूर्ण
	पूर्ण

	/* Install the debugger ग_लिखो-object control method अगर necessary */

	अगर (!ग_लिखो_handle) अणु
		status = acpi_install_method(ग_लिखो_method_code);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    ("%s, Could not install debugger write method\n",
			     acpi_क्रमmat_exception(status));
			वापस;
		पूर्ण

		status =
		    acpi_get_handle(शून्य, ACPI_DB_WRITE_METHOD, &ग_लिखो_handle);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    ("Could not obtain handle for debug method %s\n",
			     ACPI_DB_WRITE_METHOD);
			वापस;
		पूर्ण
	पूर्ण

	/* Walk the entire namespace, testing each supported named data object */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX, acpi_db_test_one_object,
				  शून्य, शून्य, शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_one_object
 *
 * PARAMETERS:  acpi_walk_callback
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test one namespace object. Supported types are Integer,
 *              String, Buffer, Package, buffer_field, and field_unit.
 *              All other object types are simply ignored.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_test_one_object(acpi_handle obj_handle,
			u32 nesting_level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_object_type local_type;
	u32 bit_length = 0;
	u32 byte_length = 0;
	acpi_status status = AE_OK;

	node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_handle);
	obj_desc = node->object;

	/*
	 * For the supported types, get the actual bit length or
	 * byte length. Map the type to one of Integer/String/Buffer.
	 */
	चयन (node->type) अणु
	हाल ACPI_TYPE_INTEGER:

		/* Integer width is either 32 or 64 */

		local_type = ACPI_TYPE_INTEGER;
		bit_length = acpi_gbl_पूर्णांकeger_bit_width;
		अवरोध;

	हाल ACPI_TYPE_STRING:

		local_type = ACPI_TYPE_STRING;
		byte_length = obj_desc->string.length;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		local_type = ACPI_TYPE_BUFFER;
		byte_length = obj_desc->buffer.length;
		bit_length = byte_length * 8;
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		local_type = ACPI_TYPE_PACKAGE;
		अवरोध;

	हाल ACPI_TYPE_FIELD_UNIT:
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		local_type = ACPI_TYPE_FIELD_UNIT;
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:
		/*
		 * The वापसed object will be a Buffer अगर the field length
		 * is larger than the size of an Integer (32 or 64 bits
		 * depending on the DSDT version).
		 */
		local_type = ACPI_TYPE_INTEGER;
		अगर (obj_desc) अणु
			bit_length = obj_desc->common_field.bit_length;
			byte_length = ACPI_ROUND_BITS_UP_TO_BYTES(bit_length);
			अगर (bit_length > acpi_gbl_पूर्णांकeger_bit_width) अणु
				local_type = ACPI_TYPE_BUFFER;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:

		/* Ignore all non-data types - Methods, Devices, Scopes, etc. */

		वापस (AE_OK);
	पूर्ण

	/* Emit the common prefix: Type:Name */

	acpi_os_म_लिखो("%14s: %4.4s",
		       acpi_ut_get_type_name(node->type), node->name.ascii);

	अगर (!obj_desc) अणु
		acpi_os_म_लिखो(" No attached sub-object, ignoring\n");
		वापस (AE_OK);
	पूर्ण

	/* At this poपूर्णांक, we have resolved the object to one of the major types */

	चयन (local_type) अणु
	हाल ACPI_TYPE_INTEGER:

		status = acpi_db_test_पूर्णांकeger_type(node, bit_length);
		अवरोध;

	हाल ACPI_TYPE_STRING:

		status = acpi_db_test_string_type(node, byte_length);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		status = acpi_db_test_buffer_type(node, bit_length);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		status = acpi_db_test_package_type(node);
		अवरोध;

	हाल ACPI_TYPE_FIELD_UNIT:

		status = acpi_db_test_field_unit_type(obj_desc);
		अवरोध;

	शेष:

		acpi_os_म_लिखो(" Ignoring, type not implemented (%2.2X)",
			       local_type);
		अवरोध;
	पूर्ण

	/* Exit on error, but करोn't पात the namespace walk */

	अगर (ACPI_FAILURE(status)) अणु
		status = AE_OK;
	पूर्ण

	acpi_os_म_लिखो("\n");
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_पूर्णांकeger_type
 *
 * PARAMETERS:  node                - Parent NS node क्रम the object
 *              bit_length          - Actual length of the object. Used क्रम
 *                                    support of arbitrary length field_unit
 *                                    and buffer_field objects.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test पढ़ो/ग_लिखो क्रम an Integer-valued object. Perक्रमms a
 *              ग_लिखो/पढ़ो/compare of an arbitrary new value, then perक्रमms
 *              a ग_लिखो/पढ़ो/compare of the original value.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_test_पूर्णांकeger_type(काष्ठा acpi_namespace_node *node, u32 bit_length)
अणु
	जोड़ acpi_object *temp1 = शून्य;
	जोड़ acpi_object *temp2 = शून्य;
	जोड़ acpi_object *temp3 = शून्य;
	जोड़ acpi_object ग_लिखो_value;
	u64 value_to_ग_लिखो;
	acpi_status status;

	अगर (bit_length > 64) अणु
		acpi_os_म_लिखो(" Invalid length for an Integer: %u",
			       bit_length);
		वापस (AE_OK);
	पूर्ण

	/* Read the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_INTEGER, &temp1);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	acpi_os_म_लिखो(ACPI_DEBUG_LENGTH_FORMAT " %8.8X%8.8X",
		       bit_length, ACPI_ROUND_BITS_UP_TO_BYTES(bit_length),
		       ACPI_FORMAT_UINT64(temp1->पूर्णांकeger.value));

	value_to_ग_लिखो = ACPI_UINT64_MAX >> (64 - bit_length);
	अगर (temp1->पूर्णांकeger.value == value_to_ग_लिखो) अणु
		value_to_ग_लिखो = 0;
	पूर्ण
	/* Write a new value */

	ग_लिखो_value.type = ACPI_TYPE_INTEGER;
	ग_लिखो_value.पूर्णांकeger.value = value_to_ग_लिखो;
	status = acpi_db_ग_लिखो_to_object(node, &ग_लिखो_value);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Ensure that we can पढ़ो back the new value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_INTEGER, &temp2);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (temp2->पूर्णांकeger.value != value_to_ग_लिखो) अणु
		acpi_os_म_लिखो(" MISMATCH 2: %8.8X%8.8X, expecting %8.8X%8.8X",
			       ACPI_FORMAT_UINT64(temp2->पूर्णांकeger.value),
			       ACPI_FORMAT_UINT64(value_to_ग_लिखो));
	पूर्ण

	/* Write back the original value */

	ग_लिखो_value.पूर्णांकeger.value = temp1->पूर्णांकeger.value;
	status = acpi_db_ग_लिखो_to_object(node, &ग_लिखो_value);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Ensure that we can पढ़ो back the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_INTEGER, &temp3);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (temp3->पूर्णांकeger.value != temp1->पूर्णांकeger.value) अणु
		acpi_os_म_लिखो(" MISMATCH 3: %8.8X%8.8X, expecting %8.8X%8.8X",
			       ACPI_FORMAT_UINT64(temp3->पूर्णांकeger.value),
			       ACPI_FORMAT_UINT64(temp1->पूर्णांकeger.value));
	पूर्ण

निकास:
	अगर (temp1) अणु
		acpi_os_मुक्त(temp1);
	पूर्ण
	अगर (temp2) अणु
		acpi_os_मुक्त(temp2);
	पूर्ण
	अगर (temp3) अणु
		acpi_os_मुक्त(temp3);
	पूर्ण
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_buffer_type
 *
 * PARAMETERS:  node                - Parent NS node क्रम the object
 *              bit_length          - Actual length of the object.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test पढ़ो/ग_लिखो क्रम an Buffer-valued object. Perक्रमms a
 *              ग_लिखो/पढ़ो/compare of an arbitrary new value, then perक्रमms
 *              a ग_लिखो/पढ़ो/compare of the original value.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_test_buffer_type(काष्ठा acpi_namespace_node *node, u32 bit_length)
अणु
	जोड़ acpi_object *temp1 = शून्य;
	जोड़ acpi_object *temp2 = शून्य;
	जोड़ acpi_object *temp3 = शून्य;
	u8 *buffer;
	जोड़ acpi_object ग_लिखो_value;
	acpi_status status;
	u32 byte_length;
	u32 i;
	u8 extra_bits;

	byte_length = ACPI_ROUND_BITS_UP_TO_BYTES(bit_length);
	अगर (byte_length == 0) अणु
		acpi_os_म_लिखो(" Ignoring zero length buffer");
		वापस (AE_OK);
	पूर्ण

	/* Allocate a local buffer */

	buffer = ACPI_ALLOCATE_ZEROED(byte_length);
	अगर (!buffer) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Read the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_BUFFER, &temp1);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Emit a few bytes of the buffer */

	acpi_os_म_लिखो(ACPI_DEBUG_LENGTH_FORMAT, bit_length,
		       temp1->buffer.length);
	क्रम (i = 0; ((i < 8) && (i < byte_length)); i++) अणु
		acpi_os_म_लिखो(" %2.2X", temp1->buffer.poपूर्णांकer[i]);
	पूर्ण
	acpi_os_म_लिखो("... ");

	/*
	 * Write a new value.
	 *
	 * Handle possible extra bits at the end of the buffer. Can
	 * happen क्रम field_units larger than an पूर्णांकeger, but the bit
	 * count is not an पूर्णांकegral number of bytes. Zero out the
	 * unused bits.
	 */
	स_रखो(buffer, BUFFER_FILL_VALUE, byte_length);
	extra_bits = bit_length % 8;
	अगर (extra_bits) अणु
		buffer[byte_length - 1] = ACPI_MASK_BITS_ABOVE(extra_bits);
	पूर्ण

	ग_लिखो_value.type = ACPI_TYPE_BUFFER;
	ग_लिखो_value.buffer.length = byte_length;
	ग_लिखो_value.buffer.poपूर्णांकer = buffer;

	status = acpi_db_ग_लिखो_to_object(node, &ग_लिखो_value);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Ensure that we can पढ़ो back the new value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_BUFFER, &temp2);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (स_भेद(temp2->buffer.poपूर्णांकer, buffer, byte_length)) अणु
		acpi_os_म_लिखो(" MISMATCH 2: New buffer value");
	पूर्ण

	/* Write back the original value */

	ग_लिखो_value.buffer.length = byte_length;
	ग_लिखो_value.buffer.poपूर्णांकer = temp1->buffer.poपूर्णांकer;

	status = acpi_db_ग_लिखो_to_object(node, &ग_लिखो_value);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Ensure that we can पढ़ो back the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_BUFFER, &temp3);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (स_भेद(temp1->buffer.poपूर्णांकer, temp3->buffer.poपूर्णांकer, byte_length)) अणु
		acpi_os_म_लिखो(" MISMATCH 3: While restoring original buffer");
	पूर्ण

निकास:
	ACPI_FREE(buffer);
	अगर (temp1) अणु
		acpi_os_मुक्त(temp1);
	पूर्ण
	अगर (temp2) अणु
		acpi_os_मुक्त(temp2);
	पूर्ण
	अगर (temp3) अणु
		acpi_os_मुक्त(temp3);
	पूर्ण
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_string_type
 *
 * PARAMETERS:  node                - Parent NS node क्रम the object
 *              byte_length         - Actual length of the object.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test पढ़ो/ग_लिखो क्रम an String-valued object. Perक्रमms a
 *              ग_लिखो/पढ़ो/compare of an arbitrary new value, then perक्रमms
 *              a ग_लिखो/पढ़ो/compare of the original value.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_test_string_type(काष्ठा acpi_namespace_node *node, u32 byte_length)
अणु
	जोड़ acpi_object *temp1 = शून्य;
	जोड़ acpi_object *temp2 = शून्य;
	जोड़ acpi_object *temp3 = शून्य;
	अक्षर *value_to_ग_लिखो = "Test String from AML Debugger";
	जोड़ acpi_object ग_लिखो_value;
	acpi_status status;

	/* Read the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_STRING, &temp1);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	acpi_os_म_लिखो(ACPI_DEBUG_LENGTH_FORMAT " \"%s\"",
		       (temp1->string.length * 8), temp1->string.length,
		       temp1->string.poपूर्णांकer);

	/* Write a new value */

	ग_लिखो_value.type = ACPI_TYPE_STRING;
	ग_लिखो_value.string.length = म_माप(value_to_ग_लिखो);
	ग_लिखो_value.string.poपूर्णांकer = value_to_ग_लिखो;

	status = acpi_db_ग_लिखो_to_object(node, &ग_लिखो_value);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Ensure that we can पढ़ो back the new value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_STRING, &temp2);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (म_भेद(temp2->string.poपूर्णांकer, value_to_ग_लिखो)) अणु
		acpi_os_म_लिखो(" MISMATCH 2: %s, expecting %s",
			       temp2->string.poपूर्णांकer, value_to_ग_लिखो);
	पूर्ण

	/* Write back the original value */

	ग_लिखो_value.string.length = म_माप(temp1->string.poपूर्णांकer);
	ग_लिखो_value.string.poपूर्णांकer = temp1->string.poपूर्णांकer;

	status = acpi_db_ग_लिखो_to_object(node, &ग_लिखो_value);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Ensure that we can पढ़ो back the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_STRING, &temp3);
	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	अगर (म_भेद(temp1->string.poपूर्णांकer, temp3->string.poपूर्णांकer)) अणु
		acpi_os_म_लिखो(" MISMATCH 3: %s, expecting %s",
			       temp3->string.poपूर्णांकer, temp1->string.poपूर्णांकer);
	पूर्ण

निकास:
	अगर (temp1) अणु
		acpi_os_मुक्त(temp1);
	पूर्ण
	अगर (temp2) अणु
		acpi_os_मुक्त(temp2);
	पूर्ण
	अगर (temp3) अणु
		acpi_os_मुक्त(temp3);
	पूर्ण
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_package_type
 *
 * PARAMETERS:  node                - Parent NS node क्रम the object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test पढ़ो क्रम a Package object.
 *
 ******************************************************************************/

अटल acpi_status acpi_db_test_package_type(काष्ठा acpi_namespace_node *node)
अणु
	जोड़ acpi_object *temp1 = शून्य;
	acpi_status status;

	/* Read the original value */

	status = acpi_db_पढ़ो_from_object(node, ACPI_TYPE_PACKAGE, &temp1);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	acpi_os_म_लिखो(" %.2X Elements", temp1->package.count);
	acpi_os_मुक्त(temp1);
	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_test_field_unit_type
 *
 * PARAMETERS:  obj_desc                - A field unit object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Test पढ़ो/ग_लिखो on a named field unit.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_test_field_unit_type(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	जोड़ acpi_opeअक्रम_object *region_obj;
	u32 bit_length = 0;
	u32 byte_length = 0;
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *ret_buffer_desc;

	/* Supported spaces are memory/io/pci_config */

	region_obj = obj_desc->field.region_obj;
	चयन (region_obj->region.space_id) अणु
	हाल ACPI_ADR_SPACE_SYSTEM_MEMORY:
	हाल ACPI_ADR_SPACE_SYSTEM_IO:
	हाल ACPI_ADR_SPACE_PCI_CONFIG:

		/* Need the पूर्णांकerpreter to execute */

		acpi_ut_acquire_mutex(ACPI_MTX_INTERPRETER);
		acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);

		/* Exercise पढ़ो-then-ग_लिखो */

		status =
		    acpi_ex_पढ़ो_data_from_field(शून्य, obj_desc,
						 &ret_buffer_desc);
		अगर (status == AE_OK) अणु
			acpi_ex_ग_लिखो_data_to_field(ret_buffer_desc, obj_desc,
						    शून्य);
			acpi_ut_हटाओ_reference(ret_buffer_desc);
		पूर्ण

		acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
		acpi_ut_release_mutex(ACPI_MTX_INTERPRETER);

		bit_length = obj_desc->common_field.bit_length;
		byte_length = ACPI_ROUND_BITS_UP_TO_BYTES(bit_length);

		acpi_os_म_लिखो(ACPI_DEBUG_LENGTH_FORMAT " [%s]", bit_length,
			       byte_length,
			       acpi_ut_get_region_name(region_obj->region.
						       space_id));
		वापस (status);

	शेष:

		acpi_os_म_लिखो
		    ("      %s address space is not supported in this command [%4.4s]",
		     acpi_ut_get_region_name(region_obj->region.space_id),
		     region_obj->region.node->name.ascii);
		वापस (AE_OK);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_पढ़ो_from_object
 *
 * PARAMETERS:  node                - Parent NS node क्रम the object
 *              expected_type       - Object type expected from the पढ़ो
 *              value               - Where the value पढ़ो is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमms a पढ़ो from the specअगरied object by invoking the
 *              special debugger control method that पढ़ोs the object. Thus,
 *              the AML पूर्णांकerpreter is करोing all of the work, increasing the
 *              validity of the test.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_पढ़ो_from_object(काष्ठा acpi_namespace_node *node,
			 acpi_object_type expected_type,
			 जोड़ acpi_object **value)
अणु
	जोड़ acpi_object *ret_value;
	काष्ठा acpi_object_list param_objects;
	जोड़ acpi_object params[2];
	काष्ठा acpi_buffer वापस_obj;
	acpi_status status;

	params[0].type = ACPI_TYPE_LOCAL_REFERENCE;
	params[0].reference.actual_type = node->type;
	params[0].reference.handle = ACPI_CAST_PTR(acpi_handle, node);

	param_objects.count = 1;
	param_objects.poपूर्णांकer = params;

	वापस_obj.length = ACPI_ALLOCATE_BUFFER;

	acpi_gbl_method_executing = TRUE;
	status = acpi_evaluate_object(पढ़ो_handle, शून्य,
				      &param_objects, &वापस_obj);

	acpi_gbl_method_executing = FALSE;
	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not read from object, %s",
			       acpi_क्रमmat_exception(status));
		वापस (status);
	पूर्ण

	ret_value = (जोड़ acpi_object *)वापस_obj.poपूर्णांकer;

	चयन (ret_value->type) अणु
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_BUFFER:
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_PACKAGE:
		/*
		 * Did we receive the type we wanted? Most important क्रम the
		 * Integer/Buffer हाल (when a field is larger than an Integer,
		 * it should वापस a Buffer).
		 */
		अगर (ret_value->type != expected_type) अणु
			acpi_os_म_लिखो
			    (" Type mismatch: Expected %s, Received %s",
			     acpi_ut_get_type_name(expected_type),
			     acpi_ut_get_type_name(ret_value->type));

			acpi_os_मुक्त(वापस_obj.poपूर्णांकer);
			वापस (AE_TYPE);
		पूर्ण

		*value = ret_value;
		अवरोध;

	शेष:

		acpi_os_म_लिखो(" Unsupported return object type, %s",
			       acpi_ut_get_type_name(ret_value->type));

		acpi_os_मुक्त(वापस_obj.poपूर्णांकer);
		वापस (AE_TYPE);
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_ग_लिखो_to_object
 *
 * PARAMETERS:  node                - Parent NS node क्रम the object
 *              value               - Value to be written
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Perक्रमms a ग_लिखो to the specअगरied object by invoking the
 *              special debugger control method that ग_लिखोs the object. Thus,
 *              the AML पूर्णांकerpreter is करोing all of the work, increasing the
 *              validity of the test.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_ग_लिखो_to_object(काष्ठा acpi_namespace_node *node,
			जोड़ acpi_object *value)
अणु
	काष्ठा acpi_object_list param_objects;
	जोड़ acpi_object params[2];
	acpi_status status;

	params[0].type = ACPI_TYPE_LOCAL_REFERENCE;
	params[0].reference.actual_type = node->type;
	params[0].reference.handle = ACPI_CAST_PTR(acpi_handle, node);

	/* Copy the incoming user parameter */

	स_नकल(&params[1], value, माप(जोड़ acpi_object));

	param_objects.count = 2;
	param_objects.poपूर्णांकer = params;

	acpi_gbl_method_executing = TRUE;
	status = acpi_evaluate_object(ग_लिखो_handle, शून्य, &param_objects, शून्य);
	acpi_gbl_method_executing = FALSE;

	अगर (ACPI_FAILURE(status)) अणु
		acpi_os_म_लिखो("Could not write to object, %s",
			       acpi_क्रमmat_exception(status));
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evaluate_all_predefined_names
 *
 * PARAMETERS:  count_arg           - Max number of methods to execute
 *
 * RETURN:      None
 *
 * DESCRIPTION: Namespace batch execution. Execute predefined names in the
 *              namespace, up to the max count, अगर specअगरied.
 *
 ******************************************************************************/

अटल व्योम acpi_db_evaluate_all_predefined_names(अक्षर *count_arg)
अणु
	काष्ठा acpi_db_execute_walk info;

	info.count = 0;
	info.max_count = ACPI_UINT32_MAX;

	अगर (count_arg) अणु
		info.max_count = म_से_अदीर्घ(count_arg, शून्य, 0);
	पूर्ण

	/* Search all nodes in namespace */

	(व्योम)acpi_walk_namespace(ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
				  ACPI_UINT32_MAX,
				  acpi_db_evaluate_one_predefined_name, शून्य,
				  (व्योम *)&info, शून्य);

	acpi_os_म_लिखो("Evaluated %u predefined names in the namespace\n",
		       info.count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_evaluate_one_predefined_name
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Batch execution module. Currently only executes predefined
 *              ACPI names.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_evaluate_one_predefined_name(acpi_handle obj_handle,
				     u32 nesting_level,
				     व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	काष्ठा acpi_db_execute_walk *info =
	    (काष्ठा acpi_db_execute_walk *)context;
	अक्षर *pathname;
	स्थिर जोड़ acpi_predefined_info *predefined;
	काष्ठा acpi_device_info *obj_info;
	काष्ठा acpi_object_list param_objects;
	जोड़ acpi_object params[ACPI_METHOD_NUM_ARGS];
	जोड़ acpi_object *this_param;
	काष्ठा acpi_buffer वापस_obj;
	acpi_status status;
	u16 arg_type_list;
	u8 arg_count;
	u8 arg_type;
	u32 i;

	/* The name must be a predefined ACPI name */

	predefined = acpi_ut_match_predefined_method(node->name.ascii);
	अगर (!predefined) अणु
		वापस (AE_OK);
	पूर्ण

	अगर (node->type == ACPI_TYPE_LOCAL_SCOPE) अणु
		वापस (AE_OK);
	पूर्ण

	pathname = acpi_ns_get_normalized_pathname(node, TRUE);
	अगर (!pathname) अणु
		वापस (AE_OK);
	पूर्ण

	/* Get the object info क्रम number of method parameters */

	status = acpi_get_object_info(obj_handle, &obj_info);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_FREE(pathname);
		वापस (status);
	पूर्ण

	param_objects.count = 0;
	param_objects.poपूर्णांकer = शून्य;

	अगर (obj_info->type == ACPI_TYPE_METHOD) अणु

		/* Setup शेष parameters (with proper types) */

		arg_type_list = predefined->info.argument_list;
		arg_count = METHOD_GET_ARG_COUNT(arg_type_list);

		/*
		 * Setup the ACPI-required number of arguments, regardless of what
		 * the actual method defines. If there is a dअगरference, then the
		 * method is wrong and a warning will be issued during execution.
		 */
		this_param = params;
		क्रम (i = 0; i < arg_count; i++) अणु
			arg_type = METHOD_GET_NEXT_TYPE(arg_type_list);
			this_param->type = arg_type;

			चयन (arg_type) अणु
			हाल ACPI_TYPE_INTEGER:

				this_param->पूर्णांकeger.value = 1;
				अवरोध;

			हाल ACPI_TYPE_STRING:

				this_param->string.poपूर्णांकer =
				    "This is the default argument string";
				this_param->string.length =
				    म_माप(this_param->string.poपूर्णांकer);
				अवरोध;

			हाल ACPI_TYPE_BUFFER:

				this_param->buffer.poपूर्णांकer = (u8 *)params;	/* just a garbage buffer */
				this_param->buffer.length = 48;
				अवरोध;

			हाल ACPI_TYPE_PACKAGE:

				this_param->package.elements = शून्य;
				this_param->package.count = 0;
				अवरोध;

			शेष:

				acpi_os_म_लिखो
				    ("%s: Unsupported argument type: %u\n",
				     pathname, arg_type);
				अवरोध;
			पूर्ण

			this_param++;
		पूर्ण

		param_objects.count = arg_count;
		param_objects.poपूर्णांकer = params;
	पूर्ण

	ACPI_FREE(obj_info);
	वापस_obj.poपूर्णांकer = शून्य;
	वापस_obj.length = ACPI_ALLOCATE_BUFFER;

	/* Do the actual method execution */

	acpi_gbl_method_executing = TRUE;

	status = acpi_evaluate_object(node, शून्य, &param_objects, &वापस_obj);

	acpi_os_म_लिखो("%-32s returned %s\n",
		       pathname, acpi_क्रमmat_exception(status));
	acpi_gbl_method_executing = FALSE;
	ACPI_FREE(pathname);

	/* Ignore status from method execution */

	status = AE_OK;

	/* Update count, check अगर we have executed enough methods */

	info->count++;
	अगर (info->count >= info->max_count) अणु
		status = AE_CTRL_TERMINATE;
	पूर्ण

	वापस (status);
पूर्ण
