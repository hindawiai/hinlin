<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exnames - पूर्णांकerpreter/scanner name load/execute
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exnames")

/* Local prototypes */
अटल अक्षर *acpi_ex_allocate_name_string(u32 prefix_count, u32 num_name_segs);

अटल acpi_status acpi_ex_name_segment(u8 **in_aml_address, अक्षर *name_string);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_allocate_name_string
 *
 * PARAMETERS:  prefix_count        - Count of parent levels. Special हालs:
 *                                    (-1)==root,  0==none
 *              num_name_segs       - count of 4-अक्षरacter name segments
 *
 * RETURN:      A poपूर्णांकer to the allocated string segment. This segment must
 *              be deleted by the caller.
 *
 * DESCRIPTION: Allocate a buffer क्रम a name string. Ensure allocated name
 *              string is दीर्घ enough, and set up prefix अगर any.
 *
 ******************************************************************************/

अटल अक्षर *acpi_ex_allocate_name_string(u32 prefix_count, u32 num_name_segs)
अणु
	अक्षर *temp_ptr;
	अक्षर *name_string;
	u32 size_needed;

	ACPI_FUNCTION_TRACE(ex_allocate_name_string);

	/*
	 * Allow room क्रम all \ and ^ prefixes, all segments and a multi_name_prefix.
	 * Also, one byte क्रम the null terminator.
	 * This may actually be somewhat दीर्घer than needed.
	 */
	अगर (prefix_count == ACPI_UINT32_MAX) अणु

		/* Special हाल क्रम root */

		size_needed = 1 + (ACPI_NAMESEG_SIZE * num_name_segs) + 2 + 1;
	पूर्ण अन्यथा अणु
		size_needed =
		    prefix_count + (ACPI_NAMESEG_SIZE * num_name_segs) + 2 + 1;
	पूर्ण

	/*
	 * Allocate a buffer क्रम the name.
	 * This buffer must be deleted by the caller!
	 */
	name_string = ACPI_ALLOCATE(size_needed);
	अगर (!name_string) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not allocate size %u", size_needed));
		वापस_PTR(शून्य);
	पूर्ण

	temp_ptr = name_string;

	/* Set up Root or Parent prefixes अगर needed */

	अगर (prefix_count == ACPI_UINT32_MAX) अणु
		*temp_ptr++ = AML_ROOT_PREFIX;
	पूर्ण अन्यथा अणु
		जबतक (prefix_count--) अणु
			*temp_ptr++ = AML_PARENT_PREFIX;
		पूर्ण
	पूर्ण

	/* Set up Dual or Multi prefixes अगर needed */

	अगर (num_name_segs > 2) अणु

		/* Set up multi prefixes   */

		*temp_ptr++ = AML_MULTI_NAME_PREFIX;
		*temp_ptr++ = (अक्षर)num_name_segs;
	पूर्ण अन्यथा अगर (2 == num_name_segs) अणु

		/* Set up dual prefixes */

		*temp_ptr++ = AML_DUAL_NAME_PREFIX;
	पूर्ण

	/*
	 * Terminate string following prefixes. acpi_ex_name_segment() will
	 * append the segment(s)
	 */
	*temp_ptr = 0;

	वापस_PTR(name_string);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_name_segment
 *
 * PARAMETERS:  in_aml_address  - Poपूर्णांकer to the name in the AML code
 *              name_string     - Where to वापस the name. The name is appended
 *                                to any existing string to क्रमm a namepath
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Extract an ACPI name (4 bytes) from the AML byte stream
 *
 ******************************************************************************/

अटल acpi_status acpi_ex_name_segment(u8 ** in_aml_address, अक्षर *name_string)
अणु
	अक्षर *aml_address = (व्योम *)*in_aml_address;
	acpi_status status = AE_OK;
	u32 index;
	अक्षर अक्षर_buf[5];

	ACPI_FUNCTION_TRACE(ex_name_segment);

	/*
	 * If first अक्षरacter is a digit, then we know that we aren't looking
	 * at a valid name segment
	 */
	अक्षर_buf[0] = *aml_address;

	अगर ('0' <= char_buf[0] && char_buf[0] <= '9') अणु
		ACPI_ERROR((AE_INFO, "Invalid leading digit: %c", अक्षर_buf[0]));
		वापस_ACPI_STATUS(AE_CTRL_PENDING);
	पूर्ण

	क्रम (index = 0;
	     (index < ACPI_NAMESEG_SIZE)
	     && (acpi_ut_valid_name_अक्षर(*aml_address, 0)); index++) अणु
		अक्षर_buf[index] = *aml_address++;
	पूर्ण

	/* Valid name segment  */

	अगर (index == 4) अणु

		/* Found 4 valid अक्षरacters */

		अक्षर_buf[4] = '\0';

		अगर (name_string) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "Appending NameSeg %s\n", अक्षर_buf));
			म_जोड़ो(name_string, अक्षर_buf);
		पूर्ण अन्यथा अणु
			ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
					  "No Name string - %s\n", अक्षर_buf));
		पूर्ण
	पूर्ण अन्यथा अगर (index == 0) अणु
		/*
		 * First अक्षरacter was not a valid name अक्षरacter,
		 * so we are looking at something other than a name.
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				  "Leading character is not alpha: %02Xh (not a name)\n",
				  अक्षर_buf[0]));
		status = AE_CTRL_PENDING;
	पूर्ण अन्यथा अणु
		/*
		 * Segment started with one or more valid अक्षरacters, but fewer than
		 * the required 4
		 */
		status = AE_AML_BAD_NAME;
		ACPI_ERROR((AE_INFO,
			    "Bad character 0x%02x in name, at %p",
			    *aml_address, aml_address));
	पूर्ण

	*in_aml_address = ACPI_CAST_PTR(u8, aml_address);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_get_name_string
 *
 * PARAMETERS:  data_type           - Object type to be associated with this
 *                                    name
 *              in_aml_address      - Poपूर्णांकer to the namestring in the AML code
 *              out_name_string     - Where the namestring is वापसed
 *              out_name_length     - Length of the वापसed string
 *
 * RETURN:      Status, namestring and length
 *
 * DESCRIPTION: Extract a full namepath from the AML byte stream,
 *              including any prefixes.
 *
 ******************************************************************************/

acpi_status
acpi_ex_get_name_string(acpi_object_type data_type,
			u8 * in_aml_address,
			अक्षर **out_name_string, u32 * out_name_length)
अणु
	acpi_status status = AE_OK;
	u8 *aml_address = in_aml_address;
	अक्षर *name_string = शून्य;
	u32 num_segments;
	u32 prefix_count = 0;
	u8 has_prefix = FALSE;

	ACPI_FUNCTION_TRACE_PTR(ex_get_name_string, aml_address);

	अगर (ACPI_TYPE_LOCAL_REGION_FIELD == data_type ||
	    ACPI_TYPE_LOCAL_BANK_FIELD == data_type ||
	    ACPI_TYPE_LOCAL_INDEX_FIELD == data_type) अणु

		/* Disallow prefixes क्रम types associated with field_unit names */

		name_string = acpi_ex_allocate_name_string(0, 1);
		अगर (!name_string) अणु
			status = AE_NO_MEMORY;
		पूर्ण अन्यथा अणु
			status =
			    acpi_ex_name_segment(&aml_address, name_string);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * data_type is not a field name.
		 * Examine first अक्षरacter of name क्रम root or parent prefix चालकs
		 */
		चयन (*aml_address) अणु
		हाल AML_ROOT_PREFIX:

			ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
					  "RootPrefix(\\) at %p\n",
					  aml_address));

			/*
			 * Remember that we have a root_prefix --
			 * see comment in acpi_ex_allocate_name_string()
			 */
			aml_address++;
			prefix_count = ACPI_UINT32_MAX;
			has_prefix = TRUE;
			अवरोध;

		हाल AML_PARENT_PREFIX:

			/* Increment past possibly multiple parent prefixes */

			करो अणु
				ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
						  "ParentPrefix (^) at %p\न",
						  aml_address));

				aml_address++;
				prefix_count++;

			पूर्ण जबतक (*aml_address == AML_PARENT_PREFIX);

			has_prefix = TRUE;
			अवरोध;

		शेष:

			/* Not a prefix अक्षरacter */

			अवरोध;
		पूर्ण

		/* Examine first अक्षरacter of name क्रम name segment prefix चालक */

		चयन (*aml_address) अणु
		हाल AML_DUAL_NAME_PREFIX:

			ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
					  "DualNamePrefix at %p\n",
					  aml_address));

			aml_address++;
			name_string =
			    acpi_ex_allocate_name_string(prefix_count, 2);
			अगर (!name_string) अणु
				status = AE_NO_MEMORY;
				अवरोध;
			पूर्ण

			/* Indicate that we processed a prefix */

			has_prefix = TRUE;

			status =
			    acpi_ex_name_segment(&aml_address, name_string);
			अगर (ACPI_SUCCESS(status)) अणु
				status =
				    acpi_ex_name_segment(&aml_address,
							 name_string);
			पूर्ण
			अवरोध;

		हाल AML_MULTI_NAME_PREFIX:

			ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
					  "MultiNamePrefix at %p\n",
					  aml_address));

			/* Fetch count of segments reमुख्यing in name path */

			aml_address++;
			num_segments = *aml_address;

			name_string =
			    acpi_ex_allocate_name_string(prefix_count,
							 num_segments);
			अगर (!name_string) अणु
				status = AE_NO_MEMORY;
				अवरोध;
			पूर्ण

			/* Indicate that we processed a prefix */

			aml_address++;
			has_prefix = TRUE;

			जबतक (num_segments &&
			       (status =
				acpi_ex_name_segment(&aml_address,
						     name_string)) == AE_OK) अणु
				num_segments--;
			पूर्ण

			अवरोध;

		हाल 0:

			/* null_name valid as of 8-12-98 ASL/AML Grammar Update */

			अगर (prefix_count == ACPI_UINT32_MAX) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
						  "NameSeg is \"\\\" followed by NULL\n"));
			पूर्ण

			/* Consume the शून्य byte */

			aml_address++;
			name_string =
			    acpi_ex_allocate_name_string(prefix_count, 0);
			अगर (!name_string) अणु
				status = AE_NO_MEMORY;
				अवरोध;
			पूर्ण

			अवरोध;

		शेष:

			/* Name segment string */

			name_string =
			    acpi_ex_allocate_name_string(prefix_count, 1);
			अगर (!name_string) अणु
				status = AE_NO_MEMORY;
				अवरोध;
			पूर्ण

			status =
			    acpi_ex_name_segment(&aml_address, name_string);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (AE_CTRL_PENDING == status && has_prefix) अणु

		/* Ran out of segments after processing a prefix */

		ACPI_ERROR((AE_INFO, "Malformed Name at %p", name_string));
		status = AE_AML_BAD_NAME;
	पूर्ण

	अगर (ACPI_FAILURE(status)) अणु
		अगर (name_string) अणु
			ACPI_FREE(name_string);
		पूर्ण
		वापस_ACPI_STATUS(status);
	पूर्ण

	*out_name_string = name_string;
	*out_name_length = (u32) (aml_address - in_aml_address);

	वापस_ACPI_STATUS(status);
पूर्ण
