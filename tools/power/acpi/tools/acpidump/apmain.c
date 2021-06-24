<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: apमुख्य - Main module क्रम the acpidump utility
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा _DECLARE_GLOBALS
#समावेश "acpidump.h"

/*
 * acpidump - A portable utility क्रम obtaining प्रणाली ACPI tables and dumping
 * them in an ASCII hex क्रमmat suitable क्रम binary extraction via acpixtract.
 *
 * Obtaining the प्रणाली ACPI tables is an OS-specअगरic operation.
 *
 * This utility can be ported to any host operating प्रणाली by providing a
 * module containing प्रणाली-specअगरic versions of these पूर्णांकerfaces:
 *
 *      acpi_os_get_table_by_address
 *      acpi_os_get_table_by_index
 *      acpi_os_get_table_by_name
 *
 * See the ACPICA Reference Guide क्रम the exact definitions of these
 * पूर्णांकerfaces. Also, see these ACPICA source code modules क्रम example
 * implementations:
 *
 *      source/os_specअगरic/service_layers/oswपूर्णांकbl.c
 *      source/os_specअगरic/service_layers/oslinuxtbl.c
 */

/* Local prototypes */

अटल व्योम ap_display_usage(व्योम);

अटल पूर्णांक ap_करो_options(पूर्णांक argc, अक्षर **argv);

अटल पूर्णांक ap_insert_action(अक्षर *argument, u32 to_be_करोne);

/* Table क्रम deferred actions from command line options */

काष्ठा ap_dump_action action_table[AP_MAX_ACTIONS];
u32 current_action = 0;

#घोषणा AP_UTILITY_NAME             "ACPI Binary Table Dump Utility"
#घोषणा AP_SUPPORTED_OPTIONS        "?a:bc:f:hn:o:r:sv^xz"

/******************************************************************************
 *
 * FUNCTION:    ap_display_usage
 *
 * DESCRIPTION: Usage message क्रम the acpi_dump utility
 *
 ******************************************************************************/

अटल व्योम ap_display_usage(व्योम)
अणु

	ACPI_USAGE_HEADER("acpidump [options]");

	ACPI_OPTION("-b", "Dump tables to binary files");
	ACPI_OPTION("-h -?", "This help message");
	ACPI_OPTION("-o <File>", "Redirect output to file");
	ACPI_OPTION("-r <Address>", "Dump tables from specified RSDP");
	ACPI_OPTION("-s", "Print table summaries only");
	ACPI_OPTION("-v", "Display version information");
	ACPI_OPTION("-vd", "Display build date and time");
	ACPI_OPTION("-z", "Verbose mode");

	ACPI_USAGE_TEXT("\nTable Options:\n");

	ACPI_OPTION("-a <Address>", "Get table via a physical address");
	ACPI_OPTION("-c <on|off>", "Turning on/off customized table dumping");
	ACPI_OPTION("-f <BinaryFile>", "Get table via a binary file");
	ACPI_OPTION("-n <Signature>", "Get table via a name/signature");
	ACPI_OPTION("-x", "Do not use but dump XSDT");
	ACPI_OPTION("-x -x", "Do not use or dump XSDT");

	ACPI_USAGE_TEXT("\n"
			"Invocation without parameters dumps all available tables\n"
			"Multiple mixed instances of -a, -f, and -n are supported\n\n");
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_insert_action
 *
 * PARAMETERS:  argument            - Poपूर्णांकer to the argument क्रम this action
 *              to_be_करोne          - What to करो to process this action
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Add an action item to the action table
 *
 ******************************************************************************/

अटल पूर्णांक ap_insert_action(अक्षर *argument, u32 to_be_करोne)
अणु

	/* Insert action and check क्रम table overflow */

	action_table[current_action].argument = argument;
	action_table[current_action].to_be_करोne = to_be_करोne;

	current_action++;
	अगर (current_action > AP_MAX_ACTIONS) अणु
		ख_लिखो(मानक_त्रुटि, "Too many table options (max %d)\n",
			AP_MAX_ACTIONS);
		वापस (-1);
	पूर्ण

	वापस (0);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    ap_करो_options
 *
 * PARAMETERS:  argc/argv           - Standard argc/argv
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Command line option processing. The मुख्य actions क्रम getting
 *              and dumping tables are deferred via the action table.
 *
 *****************************************************************************/

अटल पूर्णांक ap_करो_options(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक j;
	acpi_status status;

	/* Command line options */

	जबतक ((j =
		acpi_getopt(argc, argv, AP_SUPPORTED_OPTIONS)) != ACPI_OPT_END)
		चयन (j) अणु
			/*
			 * Global options
			 */
		हाल 'b':	/* Dump all input tables to binary files */

			gbl_binary_mode = TRUE;
			जारी;

		हाल 'c':	/* Dump customized tables */

			अगर (!म_भेद(acpi_gbl_optarg, "on")) अणु
				gbl_dump_customized_tables = TRUE;
			पूर्ण अन्यथा अगर (!म_भेद(acpi_gbl_optarg, "off")) अणु
				gbl_dump_customized_tables = FALSE;
			पूर्ण अन्यथा अणु
				ख_लिखो(मानक_त्रुटि,
					"%s: Cannot handle this switch, please use on|off\n",
					acpi_gbl_optarg);
				वापस (-1);
			पूर्ण
			जारी;

		हाल 'h':
		हाल '?':

			ap_display_usage();
			वापस (1);

		हाल 'o':	/* Redirect output to a single file */

			अगर (ap_खोलो_output_file(acpi_gbl_optarg)) अणु
				वापस (-1);
			पूर्ण
			जारी;

		हाल 'r':	/* Dump tables from specअगरied RSDP */

			status =
			    acpi_ut_म_से_अदीर्घ64(acpi_gbl_optarg, &gbl_rsdp_base);
			अगर (ACPI_FAILURE(status)) अणु
				ख_लिखो(मानक_त्रुटि,
					"%s: Could not convert to a physical address\n",
					acpi_gbl_optarg);
				वापस (-1);
			पूर्ण
			जारी;

		हाल 's':	/* Prपूर्णांक table summaries only */

			gbl_summary_mode = TRUE;
			जारी;

		हाल 'x':	/* Do not use XSDT */

			अगर (!acpi_gbl_करो_not_use_xsdt) अणु
				acpi_gbl_करो_not_use_xsdt = TRUE;
			पूर्ण अन्यथा अणु
				gbl_करो_not_dump_xsdt = TRUE;
			पूर्ण
			जारी;

		हाल 'v':	/* -v: (Version): signon alपढ़ोy emitted, just निकास */

			चयन (acpi_gbl_optarg[0]) अणु
			हाल '^':	/* -v: (Version) */

				ख_लिखो(मानक_त्रुटि,
					ACPI_COMMON_SIGNON(AP_UTILITY_NAME));
				वापस (1);

			हाल 'd':

				ख_लिखो(मानक_त्रुटि,
					ACPI_COMMON_SIGNON(AP_UTILITY_NAME));
				म_लिखो(ACPI_COMMON_BUILD_TIME);
				वापस (1);

			शेष:

				म_लिखो("Unknown option: -v%s\n",
				       acpi_gbl_optarg);
				वापस (-1);
			पूर्ण
			अवरोध;

		हाल 'z':	/* Verbose mode */

			gbl_verbose_mode = TRUE;
			ख_लिखो(मानक_त्रुटि, ACPI_COMMON_SIGNON(AP_UTILITY_NAME));
			जारी;

			/*
			 * Table options
			 */
		हाल 'a':	/* Get table by physical address */

			अगर (ap_insert_action
			    (acpi_gbl_optarg, AP_DUMP_TABLE_BY_ADDRESS)) अणु
				वापस (-1);
			पूर्ण
			अवरोध;

		हाल 'f':	/* Get table from a file */

			अगर (ap_insert_action
			    (acpi_gbl_optarg, AP_DUMP_TABLE_BY_खाता)) अणु
				वापस (-1);
			पूर्ण
			अवरोध;

		हाल 'n':	/* Get table by input name (signature) */

			अगर (ap_insert_action
			    (acpi_gbl_optarg, AP_DUMP_TABLE_BY_NAME)) अणु
				वापस (-1);
			पूर्ण
			अवरोध;

		शेष:

			ap_display_usage();
			वापस (-1);
		पूर्ण

	/* If there are no actions, this means "get/dump all tables" */

	अगर (current_action == 0) अणु
		अगर (ap_insert_action(शून्य, AP_DUMP_ALL_TABLES)) अणु
			वापस (-1);
		पूर्ण
	पूर्ण

	वापस (0);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    मुख्य
 *
 * PARAMETERS:  argc/argv           - Standard argc/argv
 *
 * RETURN:      Status
 *
 * DESCRIPTION: C मुख्य function क्रम acpidump utility
 *
 ******************************************************************************/

#अगर !defined(_GNU_EFI) && !defined(_EDK2_EFI)
पूर्णांक ACPI_SYSTEM_XFACE मुख्य(पूर्णांक argc, अक्षर *argv[])
#अन्यथा
पूर्णांक ACPI_SYSTEM_XFACE acpi_मुख्य(पूर्णांक argc, अक्षर *argv[])
#पूर्ण_अगर
अणु
	पूर्णांक status = 0;
	काष्ठा ap_dump_action *action;
	u32 file_size;
	u32 i;

	ACPI_DEBUG_INITIALIZE();	/* For debug version only */
	acpi_os_initialize();
	gbl_output_file = ACPI_खाता_OUT;
	acpi_gbl_पूर्णांकeger_byte_width = 8;

	/* Process command line options */

	status = ap_करो_options(argc, argv);
	अगर (status > 0) अणु
		वापस (0);
	पूर्ण
	अगर (status < 0) अणु
		वापस (status);
	पूर्ण

	/* Get/dump ACPI table(s) as requested */

	क्रम (i = 0; i < current_action; i++) अणु
		action = &action_table[i];
		चयन (action->to_be_करोne) अणु
		हाल AP_DUMP_ALL_TABLES:

			status = ap_dump_all_tables();
			अवरोध;

		हाल AP_DUMP_TABLE_BY_ADDRESS:

			status = ap_dump_table_by_address(action->argument);
			अवरोध;

		हाल AP_DUMP_TABLE_BY_NAME:

			status = ap_dump_table_by_name(action->argument);
			अवरोध;

		हाल AP_DUMP_TABLE_BY_खाता:

			status = ap_dump_table_from_file(action->argument);
			अवरोध;

		शेष:

			ख_लिखो(मानक_त्रुटि,
				"Internal error, invalid action: 0x%X\n",
				action->to_be_करोne);
			वापस (-1);
		पूर्ण

		अगर (status) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	अगर (gbl_output_filename) अणु
		अगर (gbl_verbose_mode) अणु

			/* Summary क्रम the output file */

			file_size = cm_get_file_size(gbl_output_file);
			ख_लिखो(मानक_त्रुटि,
				"Output file %s contains 0x%X (%u) bytes\n\n",
				gbl_output_filename, file_size, file_size);
		पूर्ण

		ख_बंद(gbl_output_file);
	पूर्ण

	वापस (status);
पूर्ण
