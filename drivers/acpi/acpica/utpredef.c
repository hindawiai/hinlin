<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utpredef - support functions क्रम predefined names
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acpredef.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utpredef")

/*
 * Names क्रम the types that can be वापसed by the predefined objects.
 * Used क्रम warning messages. Must be in the same order as the ACPI_RTYPEs
 */
अटल स्थिर अक्षर *ut_rtype_names[] = अणु
	"/Integer",
	"/String",
	"/Buffer",
	"/Package",
	"/Reference",
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_next_predefined_method
 *
 * PARAMETERS:  this_name           - Entry in the predefined method/name table
 *
 * RETURN:      Poपूर्णांकer to next entry in predefined table.
 *
 * DESCRIPTION: Get the next entry in the predefine method table. Handles the
 *              हालs where a package info entry follows a method name that
 *              वापसs a package.
 *
 ******************************************************************************/

स्थिर जोड़ acpi_predefined_info *acpi_ut_get_next_predefined_method(स्थिर जोड़
								     acpi_predefined_info
								     *this_name)
अणु

	/*
	 * Skip next entry in the table अगर this name वापसs a Package
	 * (next entry contains the package info)
	 */
	अगर ((this_name->info.expected_btypes & ACPI_RTYPE_PACKAGE) &&
	    (this_name->info.expected_btypes != ACPI_RTYPE_ALL)) अणु
		this_name++;
	पूर्ण

	this_name++;
	वापस (this_name);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_match_predefined_method
 *
 * PARAMETERS:  name                - Name to find
 *
 * RETURN:      Poपूर्णांकer to entry in predefined table. शून्य indicates not found.
 *
 * DESCRIPTION: Check an object name against the predefined object list.
 *
 ******************************************************************************/

स्थिर जोड़ acpi_predefined_info *acpi_ut_match_predefined_method(अक्षर *name)
अणु
	स्थिर जोड़ acpi_predefined_info *this_name;

	/* Quick check क्रम a predefined name, first अक्षरacter must be underscore */

	अगर (name[0] != '_') अणु
		वापस (शून्य);
	पूर्ण

	/* Search info table क्रम a predefined method/object name */

	this_name = acpi_gbl_predefined_methods;
	जबतक (this_name->info.name[0]) अणु
		अगर (ACPI_COMPARE_NAMESEG(name, this_name->info.name)) अणु
			वापस (this_name);
		पूर्ण

		this_name = acpi_ut_get_next_predefined_method(this_name);
	पूर्ण

	वापस (शून्य);		/* Not found */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_expected_वापस_types
 *
 * PARAMETERS:  buffer              - Where the क्रमmatted string is वापसed
 *              expected_Btypes     - Bitfield of expected data types
 *
 * RETURN:      Formatted string in Buffer.
 *
 * DESCRIPTION: Format the expected object types पूर्णांकo a prपूर्णांकable string.
 *
 ******************************************************************************/

व्योम acpi_ut_get_expected_वापस_types(अक्षर *buffer, u32 expected_btypes)
अणु
	u32 this_rtype;
	u32 i;
	u32 j;

	अगर (!expected_btypes) अणु
		म_नकल(buffer, "NONE");
		वापस;
	पूर्ण

	j = 1;
	buffer[0] = 0;
	this_rtype = ACPI_RTYPE_INTEGER;

	क्रम (i = 0; i < ACPI_NUM_RTYPES; i++) अणु

		/* If one of the expected types, concatenate the name of this type */

		अगर (expected_btypes & this_rtype) अणु
			म_जोड़ो(buffer, &ut_rtype_names[i][j]);
			j = 0;	/* Use name separator from now on */
		पूर्ण

		this_rtype <<= 1;	/* Next Rtype */
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * The reमुख्यing functions are used by iASL and acpi_help only
 *
 ******************************************************************************/

#अगर (defined ACPI_ASL_COMPILER || defined ACPI_HELP_APP)

/* Local prototypes */

अटल u32 acpi_ut_get_argument_types(अक्षर *buffer, u16 argument_types);

/* Types that can be वापसed बाह्यally by a predefined name */

अटल स्थिर अक्षर *ut_बाह्यal_type_names[] =	/* Indexed by ACPI_TYPE_* */
अणु
	", Type_ANY",
	", Integer",
	", String",
	", Buffer",
	", Package"
पूर्ण;

/* Bit widths क्रम resource descriptor predefined names */

अटल स्थिर अक्षर *ut_resource_type_names[] = अणु
	"/1",
	"/2",
	"/3",
	"/8",
	"/16",
	"/32",
	"/64",
	"/variable",
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_match_resource_name
 *
 * PARAMETERS:  name                - Name to find
 *
 * RETURN:      Poपूर्णांकer to entry in the resource table. शून्य indicates not
 *              found.
 *
 * DESCRIPTION: Check an object name against the predefined resource
 *              descriptor object list.
 *
 ******************************************************************************/

स्थिर जोड़ acpi_predefined_info *acpi_ut_match_resource_name(अक्षर *name)
अणु
	स्थिर जोड़ acpi_predefined_info *this_name;

	/*
	 * Quick check क्रम a predefined name, first अक्षरacter must
	 * be underscore
	 */
	अगर (name[0] != '_') अणु
		वापस (शून्य);
	पूर्ण

	/* Search info table क्रम a predefined method/object name */

	this_name = acpi_gbl_resource_names;
	जबतक (this_name->info.name[0]) अणु
		अगर (ACPI_COMPARE_NAMESEG(name, this_name->info.name)) अणु
			वापस (this_name);
		पूर्ण

		this_name++;
	पूर्ण

	वापस (शून्य);		/* Not found */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_display_predefined_method
 *
 * PARAMETERS:  buffer              - Scratch buffer क्रम this function
 *              this_name           - Entry in the predefined method/name table
 *              multi_line          - TRUE अगर output should be on >1 line
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display inक्रमmation about a predefined method. Number and
 *              type of the input arguments, and expected type(s) क्रम the
 *              वापस value, अगर any.
 *
 ******************************************************************************/

व्योम
acpi_ut_display_predefined_method(अक्षर *buffer,
				  स्थिर जोड़ acpi_predefined_info *this_name,
				  u8 multi_line)
अणु
	u32 arg_count;

	/*
	 * Get the argument count and the string buffer
	 * containing all argument types
	 */
	arg_count = acpi_ut_get_argument_types(buffer,
					       this_name->info.argument_list);

	अगर (multi_line) अणु
		म_लिखो("      ");
	पूर्ण

	म_लिखो("%4.4s    Requires %s%u argument%s",
	       this_name->info.name,
	       (this_name->info.argument_list & ARG_COUNT_IS_MINIMUM) ?
	       "(at least) " : "", arg_count, arg_count != 1 ? "s" : "");

	/* Display the types क्रम any arguments */

	अगर (arg_count > 0) अणु
		म_लिखो(" (%s)", buffer);
	पूर्ण

	अगर (multi_line) अणु
		म_लिखो("\n    ");
	पूर्ण

	/* Get the वापस value type(s) allowed */

	अगर (this_name->info.expected_btypes) अणु
		acpi_ut_get_expected_वापस_types(buffer,
						  this_name->info.
						  expected_btypes);
		म_लिखो("  Return value types: %s\n", buffer);
	पूर्ण अन्यथा अणु
		म_लिखो("  No return value\n");
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_argument_types
 *
 * PARAMETERS:  buffer              - Where to वापस the क्रमmatted types
 *              argument_types      - Types field क्रम this method
 *
 * RETURN:      count - the number of arguments required क्रम this method
 *
 * DESCRIPTION: Format the required data types क्रम this method (Integer,
 *              String, Buffer, or Package) and वापस the required argument
 *              count.
 *
 ******************************************************************************/

अटल u32 acpi_ut_get_argument_types(अक्षर *buffer, u16 argument_types)
अणु
	u16 this_argument_type;
	u16 sub_index;
	u16 arg_count;
	u32 i;

	*buffer = 0;
	sub_index = 2;

	/* First field in the types list is the count of args to follow */

	arg_count = METHOD_GET_ARG_COUNT(argument_types);
	अगर (arg_count > METHOD_PREDEF_ARGS_MAX) अणु
		म_लिखो("**** Invalid argument count (%u) "
		       "in predefined info structure\n", arg_count);
		वापस (arg_count);
	पूर्ण

	/* Get each argument from the list, convert to ascii, store to buffer */

	क्रम (i = 0; i < arg_count; i++) अणु
		this_argument_type = METHOD_GET_NEXT_TYPE(argument_types);

		अगर (this_argument_type > METHOD_MAX_ARG_TYPE) अणु
			म_लिखो("**** Invalid argument type (%u) "
			       "in predefined info structure\n",
			       this_argument_type);
			वापस (arg_count);
		पूर्ण

		म_जोड़ो(buffer,
		       ut_बाह्यal_type_names[this_argument_type] + sub_index);
		sub_index = 0;
	पूर्ण

	वापस (arg_count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_resource_bit_width
 *
 * PARAMETERS:  buffer              - Where the क्रमmatted string is वापसed
 *              types               - Bitfield of expected data types
 *
 * RETURN:      Count of वापस types. Formatted string in Buffer.
 *
 * DESCRIPTION: Format the resource bit widths पूर्णांकo a prपूर्णांकable string.
 *
 ******************************************************************************/

u32 acpi_ut_get_resource_bit_width(अक्षर *buffer, u16 types)
अणु
	u32 i;
	u16 sub_index;
	u32 found;

	*buffer = 0;
	sub_index = 1;
	found = 0;

	क्रम (i = 0; i < NUM_RESOURCE_WIDTHS; i++) अणु
		अगर (types & 1) अणु
			म_जोड़ो(buffer, &(ut_resource_type_names[i][sub_index]));
			sub_index = 0;
			found++;
		पूर्ण

		types >>= 1;
	पूर्ण

	वापस (found);
पूर्ण
#पूर्ण_अगर
