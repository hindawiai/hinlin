<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbconvert - debugger miscellaneous conversion routines
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbconvert")

#घोषणा DB_DEFAULT_PKG_ELEMENTS     33
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_hex_अक्षर_to_value
 *
 * PARAMETERS:  hex_अक्षर            - Ascii Hex digit, 0-9|a-f|A-F
 *              वापस_value        - Where the converted value is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a single hex अक्षरacter to a 4-bit number (0-16).
 *
 ******************************************************************************/
acpi_status acpi_db_hex_अक्षर_to_value(पूर्णांक hex_अक्षर, u8 *वापस_value)
अणु
	u8 value;

	/* Digit must be ascii [0-9a-fA-F] */

	अगर (!है_षष्ठादशक(hex_अक्षर)) अणु
		वापस (AE_BAD_HEX_CONSTANT);
	पूर्ण

	अगर (hex_अक्षर <= 0x39) अणु
		value = (u8)(hex_अक्षर - 0x30);
	पूर्ण अन्यथा अणु
		value = (u8)(बड़े(hex_अक्षर) - 0x37);
	पूर्ण

	*वापस_value = value;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_hex_byte_to_binary
 *
 * PARAMETERS:  hex_byte            - Double hex digit (0x00 - 0xFF) in क्रमmat:
 *                                    hi_byte then lo_byte.
 *              वापस_value        - Where the converted value is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert two hex अक्षरacters to an 8 bit number (0 - 255).
 *
 ******************************************************************************/

अटल acpi_status acpi_db_hex_byte_to_binary(अक्षर *hex_byte, u8 *वापस_value)
अणु
	u8 local0;
	u8 local1;
	acpi_status status;

	/* High byte */

	status = acpi_db_hex_अक्षर_to_value(hex_byte[0], &local0);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Low byte */

	status = acpi_db_hex_अक्षर_to_value(hex_byte[1], &local1);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	*वापस_value = (u8)((local0 << 4) | local1);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convert_to_buffer
 *
 * PARAMETERS:  string              - Input string to be converted
 *              object              - Where the buffer object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a string to a buffer object. String is treated a list
 *              of buffer elements, each separated by a space or comma.
 *
 ******************************************************************************/

अटल acpi_status
acpi_db_convert_to_buffer(अक्षर *string, जोड़ acpi_object *object)
अणु
	u32 i;
	u32 j;
	u32 length;
	u8 *buffer;
	acpi_status status;

	/* Skip all preceding white space */

	acpi_ut_हटाओ_whitespace(&string);

	/* Generate the final buffer length */

	क्रम (i = 0, length = 0; string[i];) अणु
		i += 2;
		length++;

		जबतक (string[i] && ((string[i] == ',') || (string[i] == ' '))) अणु
			i++;
		पूर्ण
	पूर्ण

	buffer = ACPI_ALLOCATE(length);
	अगर (!buffer) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Convert the command line bytes to the buffer */

	क्रम (i = 0, j = 0; string[i];) अणु
		status = acpi_db_hex_byte_to_binary(&string[i], &buffer[j]);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_FREE(buffer);
			वापस (status);
		पूर्ण

		j++;
		i += 2;
		जबतक (string[i] && ((string[i] == ',') || (string[i] == ' '))) अणु
			i++;
		पूर्ण
	पूर्ण

	object->type = ACPI_TYPE_BUFFER;
	object->buffer.poपूर्णांकer = buffer;
	object->buffer.length = length;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convert_to_package
 *
 * PARAMETERS:  string              - Input string to be converted
 *              object              - Where the package object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a string to a package object. Handles nested packages
 *              via recursion with acpi_db_convert_to_object.
 *
 ******************************************************************************/

acpi_status acpi_db_convert_to_package(अक्षर *string, जोड़ acpi_object *object)
अणु
	अक्षर *this;
	अक्षर *next;
	u32 i;
	acpi_object_type type;
	जोड़ acpi_object *elements;
	acpi_status status;

	elements =
	    ACPI_ALLOCATE_ZEROED(DB_DEFAULT_PKG_ELEMENTS *
				 माप(जोड़ acpi_object));

	this = string;
	क्रम (i = 0; i < (DB_DEFAULT_PKG_ELEMENTS - 1); i++) अणु
		this = acpi_db_get_next_token(this, &next, &type);
		अगर (!this) अणु
			अवरोध;
		पूर्ण

		/* Recursive call to convert each package element */

		status = acpi_db_convert_to_object(type, this, &elements[i]);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_db_delete_objects(i + 1, elements);
			ACPI_FREE(elements);
			वापस (status);
		पूर्ण

		this = next;
	पूर्ण

	object->type = ACPI_TYPE_PACKAGE;
	object->package.count = i;
	object->package.elements = elements;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_convert_to_object
 *
 * PARAMETERS:  type                - Object type as determined by parser
 *              string              - Input string to be converted
 *              object              - Where the new object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert a typed and tokenized string to a जोड़ acpi_object. Typing:
 *              1) String objects were surrounded by quotes.
 *              2) Buffer objects were surrounded by parentheses.
 *              3) Package objects were surrounded by brackets "[]".
 *              4) All standalone tokens are treated as पूर्णांकegers.
 *
 ******************************************************************************/

acpi_status
acpi_db_convert_to_object(acpi_object_type type,
			  अक्षर *string, जोड़ acpi_object *object)
अणु
	acpi_status status = AE_OK;

	चयन (type) अणु
	हाल ACPI_TYPE_STRING:

		object->type = ACPI_TYPE_STRING;
		object->string.poपूर्णांकer = string;
		object->string.length = (u32)म_माप(string);
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		status = acpi_db_convert_to_buffer(string, object);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		status = acpi_db_convert_to_package(string, object);
		अवरोध;

	शेष:

		object->type = ACPI_TYPE_INTEGER;
		status = acpi_ut_म_से_अदीर्घ64(string, &object->पूर्णांकeger.value);
		अवरोध;
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_encode_pld_buffer
 *
 * PARAMETERS:  pld_info            - _PLD buffer काष्ठा (Using local काष्ठा)
 *
 * RETURN:      Encode _PLD buffer suitable क्रम वापस value from _PLD
 *
 * DESCRIPTION: Bit-packs a _PLD buffer काष्ठा. Used to test the _PLD macros
 *
 ******************************************************************************/

u8 *acpi_db_encode_pld_buffer(काष्ठा acpi_pld_info *pld_info)
अणु
	u32 *buffer;
	u32 dword;

	buffer = ACPI_ALLOCATE_ZEROED(ACPI_PLD_BUFFER_SIZE);
	अगर (!buffer) अणु
		वापस (शून्य);
	पूर्ण

	/* First 32 bits */

	dword = 0;
	ACPI_PLD_SET_REVISION(&dword, pld_info->revision);
	ACPI_PLD_SET_IGNORE_COLOR(&dword, pld_info->ignore_color);
	ACPI_PLD_SET_RED(&dword, pld_info->red);
	ACPI_PLD_SET_GREEN(&dword, pld_info->green);
	ACPI_PLD_SET_BLUE(&dword, pld_info->blue);
	ACPI_MOVE_32_TO_32(&buffer[0], &dword);

	/* Second 32 bits */

	dword = 0;
	ACPI_PLD_SET_WIDTH(&dword, pld_info->width);
	ACPI_PLD_SET_HEIGHT(&dword, pld_info->height);
	ACPI_MOVE_32_TO_32(&buffer[1], &dword);

	/* Third 32 bits */

	dword = 0;
	ACPI_PLD_SET_USER_VISIBLE(&dword, pld_info->user_visible);
	ACPI_PLD_SET_DOCK(&dword, pld_info->करोck);
	ACPI_PLD_SET_LID(&dword, pld_info->lid);
	ACPI_PLD_SET_PANEL(&dword, pld_info->panel);
	ACPI_PLD_SET_VERTICAL(&dword, pld_info->vertical_position);
	ACPI_PLD_SET_HORIZONTAL(&dword, pld_info->horizontal_position);
	ACPI_PLD_SET_SHAPE(&dword, pld_info->shape);
	ACPI_PLD_SET_ORIENTATION(&dword, pld_info->group_orientation);
	ACPI_PLD_SET_TOKEN(&dword, pld_info->group_token);
	ACPI_PLD_SET_POSITION(&dword, pld_info->group_position);
	ACPI_PLD_SET_BAY(&dword, pld_info->bay);
	ACPI_MOVE_32_TO_32(&buffer[2], &dword);

	/* Fourth 32 bits */

	dword = 0;
	ACPI_PLD_SET_EJECTABLE(&dword, pld_info->ejectable);
	ACPI_PLD_SET_OSPM_EJECT(&dword, pld_info->ospm_eject_required);
	ACPI_PLD_SET_CABINET(&dword, pld_info->cabinet_number);
	ACPI_PLD_SET_CARD_CAGE(&dword, pld_info->card_cage_number);
	ACPI_PLD_SET_REFERENCE(&dword, pld_info->reference);
	ACPI_PLD_SET_ROTATION(&dword, pld_info->rotation);
	ACPI_PLD_SET_ORDER(&dword, pld_info->order);
	ACPI_MOVE_32_TO_32(&buffer[3], &dword);

	अगर (pld_info->revision >= 2) अणु

		/* Fअगरth 32 bits */

		dword = 0;
		ACPI_PLD_SET_VERT_OFFSET(&dword, pld_info->vertical_offset);
		ACPI_PLD_SET_HORIZ_OFFSET(&dword, pld_info->horizontal_offset);
		ACPI_MOVE_32_TO_32(&buffer[4], &dword);
	पूर्ण

	वापस (ACPI_CAST_PTR(u8, buffer));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_dump_pld_buffer
 *
 * PARAMETERS:  obj_desc            - Object वापसed from _PLD method
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Dumps क्रमmatted contents of a _PLD वापस buffer.
 *
 ******************************************************************************/

#घोषणा ACPI_PLD_OUTPUT     "%20s : %-6X\n"

व्योम acpi_db_dump_pld_buffer(जोड़ acpi_object *obj_desc)
अणु
	जोड़ acpi_object *buffer_desc;
	काष्ठा acpi_pld_info *pld_info;
	u8 *new_buffer;
	acpi_status status;

	/* Object must be of type Package with at least one Buffer element */

	अगर (obj_desc->type != ACPI_TYPE_PACKAGE) अणु
		वापस;
	पूर्ण

	buffer_desc = &obj_desc->package.elements[0];
	अगर (buffer_desc->type != ACPI_TYPE_BUFFER) अणु
		वापस;
	पूर्ण

	/* Convert _PLD buffer to local _PLD काष्ठा */

	status = acpi_decode_pld_buffer(buffer_desc->buffer.poपूर्णांकer,
					buffer_desc->buffer.length, &pld_info);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	/* Encode local _PLD काष्ठा back to a _PLD buffer */

	new_buffer = acpi_db_encode_pld_buffer(pld_info);
	अगर (!new_buffer) अणु
		जाओ निकास;
	पूर्ण

	/* The two bit-packed buffers should match */

	अगर (स_भेद(new_buffer, buffer_desc->buffer.poपूर्णांकer,
		   buffer_desc->buffer.length)) अणु
		acpi_os_म_लिखो
		    ("Converted _PLD buffer does not compare. New:\n");

		acpi_ut_dump_buffer(new_buffer,
				    buffer_desc->buffer.length, DB_BYTE_DISPLAY,
				    0);
	पूर्ण

	/* First 32-bit dword */

	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Revision", pld_info->revision);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_IgnoreColor",
		       pld_info->ignore_color);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Red", pld_info->red);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Green", pld_info->green);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Blue", pld_info->blue);

	/* Second 32-bit dword */

	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Width", pld_info->width);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Height", pld_info->height);

	/* Third 32-bit dword */

	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_UserVisible",
		       pld_info->user_visible);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Dock", pld_info->करोck);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Lid", pld_info->lid);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Panel", pld_info->panel);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_VerticalPosition",
		       pld_info->vertical_position);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_HorizontalPosition",
		       pld_info->horizontal_position);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Shape", pld_info->shape);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_GroupOrientation",
		       pld_info->group_orientation);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_GroupToken",
		       pld_info->group_token);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_GroupPosition",
		       pld_info->group_position);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Bay", pld_info->bay);

	/* Fourth 32-bit dword */

	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Ejectable", pld_info->ejectable);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_EjectRequired",
		       pld_info->ospm_eject_required);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_CabinetNumber",
		       pld_info->cabinet_number);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_CardCageNumber",
		       pld_info->card_cage_number);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Reference", pld_info->reference);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Rotation", pld_info->rotation);
	acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_Order", pld_info->order);

	/* Fअगरth 32-bit dword */

	अगर (buffer_desc->buffer.length > 16) अणु
		acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_VerticalOffset",
			       pld_info->vertical_offset);
		acpi_os_म_लिखो(ACPI_PLD_OUTPUT, "PLD_HorizontalOffset",
			       pld_info->horizontal_offset);
	पूर्ण

	ACPI_FREE(new_buffer);
निकास:
	ACPI_FREE(pld_info);
पूर्ण
