<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: getopt
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * ACPICA getopt() implementation
 *
 * Option strings:
 *    "f"       - Option has no arguments
 *    "f:"      - Option requires an argument
 *    "f+"      - Option has an optional argument
 *    "f^"      - Option has optional single-अक्षर sub-options
 *    "f|"      - Option has required single-अक्षर sub-options
 */

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acapps.h"

#घोषणा ACPI_OPTION_ERROR(msg, badअक्षर) \
	अगर (acpi_gbl_opterr) अणुख_लिखो (मानक_त्रुटि, "%s%c\n", msg, badअक्षर);पूर्ण

पूर्णांक acpi_gbl_opterr = 1;
पूर्णांक acpi_gbl_optind = 1;
पूर्णांक acpi_gbl_sub_opt_अक्षर = 0;
अक्षर *acpi_gbl_optarg;

अटल पूर्णांक current_अक्षर_ptr = 1;

/*******************************************************************************
 *
 * FUNCTION:    acpi_getopt_argument
 *
 * PARAMETERS:  argc, argv          - from मुख्य
 *
 * RETURN:      0 अगर an argument was found, -1 otherwise. Sets acpi_gbl_Optarg
 *              to poपूर्णांक to the next argument.
 *
 * DESCRIPTION: Get the next argument. Used to obtain arguments क्रम the
 *              two-अक्षरacter options after the original call to acpi_getopt.
 *              Note: Either the argument starts at the next अक्षरacter after
 *              the option, or it is poपूर्णांकed to by the next argv entry.
 *              (After call to acpi_getopt, we need to backup to the previous
 *              argv entry).
 *
 ******************************************************************************/

पूर्णांक acpi_getopt_argument(पूर्णांक argc, अक्षर **argv)
अणु

	acpi_gbl_optind--;
	current_अक्षर_ptr++;

	अगर (argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)] != '\0') अणु
		acpi_gbl_optarg =
		    &argv[acpi_gbl_optind++][(पूर्णांक)(current_अक्षर_ptr + 1)];
	पूर्ण अन्यथा अगर (++acpi_gbl_optind >= argc) अणु
		ACPI_OPTION_ERROR("\nOption requires an argument", 0);

		current_अक्षर_ptr = 1;
		वापस (-1);
	पूर्ण अन्यथा अणु
		acpi_gbl_optarg = argv[acpi_gbl_optind++];
	पूर्ण

	current_अक्षर_ptr = 1;
	वापस (0);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_getopt
 *
 * PARAMETERS:  argc, argv          - from मुख्य
 *              opts                - options info list
 *
 * RETURN:      Option अक्षरacter or ACPI_OPT_END
 *
 * DESCRIPTION: Get the next option
 *
 ******************************************************************************/

पूर्णांक acpi_getopt(पूर्णांक argc, अक्षर **argv, अक्षर *opts)
अणु
	पूर्णांक current_अक्षर;
	अक्षर *opts_ptr;

	अगर (current_अक्षर_ptr == 1) अणु
		अगर (acpi_gbl_optind >= argc ||
		    argv[acpi_gbl_optind][0] != '-' ||
		    argv[acpi_gbl_optind][1] == '\0') अणु
			वापस (ACPI_OPT_END);
		पूर्ण अन्यथा अगर (म_भेद(argv[acpi_gbl_optind], "--") == 0) अणु
			acpi_gbl_optind++;
			वापस (ACPI_OPT_END);
		पूर्ण
	पूर्ण

	/* Get the option */

	current_अक्षर = argv[acpi_gbl_optind][current_अक्षर_ptr];

	/* Make sure that the option is legal */

	अगर (current_अक्षर == ':' ||
	    (opts_ptr = म_अक्षर(opts, current_अक्षर)) == शून्य) अणु
		ACPI_OPTION_ERROR("Illegal option: -", current_अक्षर);

		अगर (argv[acpi_gbl_optind][++current_अक्षर_ptr] == '\0') अणु
			acpi_gbl_optind++;
			current_अक्षर_ptr = 1;
		पूर्ण

		वापस ('?');
	पूर्ण

	/* Option requires an argument? */

	अगर (*++opts_ptr == ':') अणु
		अगर (argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)] != '\0') अणु
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind++][(पूर्णांक)
						     (current_अक्षर_ptr + 1)];
		पूर्ण अन्यथा अगर (++acpi_gbl_optind >= argc) अणु
			ACPI_OPTION_ERROR("Option requires an argument: -",
					  current_अक्षर);

			current_अक्षर_ptr = 1;
			वापस ('?');
		पूर्ण अन्यथा अणु
			acpi_gbl_optarg = argv[acpi_gbl_optind++];
		पूर्ण

		current_अक्षर_ptr = 1;
	पूर्ण

	/* Option has an optional argument? */

	अन्यथा अगर (*opts_ptr == '+') अणु
		अगर (argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)] != '\0') अणु
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind++][(पूर्णांक)
						     (current_अक्षर_ptr + 1)];
		पूर्ण अन्यथा अगर (++acpi_gbl_optind >= argc) अणु
			acpi_gbl_optarg = शून्य;
		पूर्ण अन्यथा अणु
			acpi_gbl_optarg = argv[acpi_gbl_optind++];
		पूर्ण

		current_अक्षर_ptr = 1;
	पूर्ण

	/* Option has optional single-अक्षर arguments? */

	अन्यथा अगर (*opts_ptr == '^') अणु
		अगर (argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)] != '\0') अणु
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)];
		पूर्ण अन्यथा अणु
			acpi_gbl_optarg = "^";
		पूर्ण

		acpi_gbl_sub_opt_अक्षर = acpi_gbl_optarg[0];
		acpi_gbl_optind++;
		current_अक्षर_ptr = 1;
	पूर्ण

	/* Option has a required single-अक्षर argument? */

	अन्यथा अगर (*opts_ptr == '|') अणु
		अगर (argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)] != '\0') अणु
			acpi_gbl_optarg =
			    &argv[acpi_gbl_optind][(पूर्णांक)(current_अक्षर_ptr + 1)];
		पूर्ण अन्यथा अणु
			ACPI_OPTION_ERROR
			    ("Option requires a single-character suboption: -",
			     current_अक्षर);

			current_अक्षर_ptr = 1;
			वापस ('?');
		पूर्ण

		acpi_gbl_sub_opt_अक्षर = acpi_gbl_optarg[0];
		acpi_gbl_optind++;
		current_अक्षर_ptr = 1;
	पूर्ण

	/* Option with no arguments */

	अन्यथा अणु
		अगर (argv[acpi_gbl_optind][++current_अक्षर_ptr] == '\0') अणु
			current_अक्षर_ptr = 1;
			acpi_gbl_optind++;
		पूर्ण

		acpi_gbl_optarg = शून्य;
	पूर्ण

	वापस (current_अक्षर);
पूर्ण
