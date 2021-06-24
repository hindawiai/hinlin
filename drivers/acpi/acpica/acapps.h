<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Module Name: acapps - common include क्रम ACPI applications/tools
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित _ACAPPS
#घोषणा _ACAPPS

#अगर_घोषित ACPI_USE_STANDARD_HEADERS
#समावेश <sys/स्थिति.स>
#पूर्ण_अगर				/* ACPI_USE_STANDARD_HEADERS */

/* Common info क्रम tool signons */

#घोषणा ACPICA_NAME                 "Intel ACPI Component Architecture"
#घोषणा ACPICA_COPYRIGHT            "Copyright (c) 2000 - 2021 Intel Corporation"

#अगर ACPI_MACHINE_WIDTH == 64
#घोषणा ACPI_WIDTH          " (64-bit version)"

#या_अगर ACPI_MACHINE_WIDTH == 32
#घोषणा ACPI_WIDTH          " (32-bit version)"

#अन्यथा
#त्रुटि unknown ACPI_MACHINE_WIDTH
#घोषणा ACPI_WIDTH          " (unknown bit width, not 32 or 64)"

#पूर्ण_अगर

/* Macros क्रम signons and file headers */

#घोषणा ACPI_COMMON_SIGNON(utility_name) \
	"\n%s\n%s version %8.8X\n%s\n\n", \
	ACPICA_NAME, \
	utility_name, ((u32) ACPI_CA_VERSION), \
	ACPICA_COPYRIGHT

#घोषणा ACPI_COMMON_HEADER(utility_name, prefix) \
	"%s%s\n%s%s version %8.8X%s\n%s%s\n%s\n", \
	prefix, ACPICA_NAME, \
	prefix, utility_name, ((u32) ACPI_CA_VERSION), ACPI_WIDTH, \
	prefix, ACPICA_COPYRIGHT, \
	prefix

#घोषणा ACPI_COMMON_BUILD_TIME \
	"Build date/time: %s %s\n", __DATE__, __TIME__

/* Macros क्रम usage messages */

#घोषणा ACPI_USAGE_HEADER(usage) \
	म_लिखो ("Usage: %s\nOptions:\n", usage);

#घोषणा ACPI_USAGE_TEXT(description) \
	म_लिखो (description);

#घोषणा ACPI_OPTION(name, description) \
	म_लिखो ("  %-20s%s\n", name, description);

/* Check क्रम unexpected exceptions */

#घोषणा ACPI_CHECK_STATUS(name, status, expected) \
	अगर (status != expected) \
	अणु \
		acpi_os_म_लिखो ("Unexpected %s from %s (%s-%d)\n", \
			acpi_क्रमmat_exception (status), #name, _acpi_module_name, __LINE__); \
	पूर्ण

/* Check क्रम unexpected non-AE_OK errors */

#घोषणा ACPI_CHECK_OK(name, status)   ACPI_CHECK_STATUS (name, status, AE_OK);

#घोषणा खाता_SUFFIX_DISASSEMBLY     "dsl"
#घोषणा खाता_SUFFIX_BINARY_TABLE    ".dat"	/* Needs the करोt */

/* acfileio */

acpi_status
ac_get_all_tables_from_file(अक्षर *filename,
			    u8 get_only_aml_tables,
			    काष्ठा acpi_new_table_desc **वापस_list_head);

व्योम ac_delete_table_list(काष्ठा acpi_new_table_desc *list_head);

u8 ac_is_file_binary(खाता * file);

acpi_status ac_validate_table_header(खाता * file, दीर्घ table_offset);

/* Values क्रम get_only_aml_tables */

#घोषणा ACPI_GET_ONLY_AML_TABLES    TRUE
#घोषणा ACPI_GET_ALL_TABLES         FALSE

/*
 * getopt
 */
पूर्णांक acpi_getopt(पूर्णांक argc, अक्षर **argv, अक्षर *opts);

पूर्णांक acpi_getopt_argument(पूर्णांक argc, अक्षर **argv);

बाह्य पूर्णांक acpi_gbl_optind;
बाह्य पूर्णांक acpi_gbl_opterr;
बाह्य पूर्णांक acpi_gbl_sub_opt_अक्षर;
बाह्य अक्षर *acpi_gbl_optarg;

/*
 * cmfsize - Common get file size function
 */
u32 cm_get_file_size(ACPI_खाता file);

/*
 * adwalk
 */
व्योम
acpi_dm_cross_reference_namespace(जोड़ acpi_parse_object *parse_tree_root,
				  काष्ठा acpi_namespace_node *namespace_root,
				  acpi_owner_id owner_id);

व्योम acpi_dm_dump_tree(जोड़ acpi_parse_object *origin);

व्योम acpi_dm_find_orphan_methods(जोड़ acpi_parse_object *origin);

व्योम
acpi_dm_finish_namespace_load(जोड़ acpi_parse_object *parse_tree_root,
			      काष्ठा acpi_namespace_node *namespace_root,
			      acpi_owner_id owner_id);

व्योम
acpi_dm_convert_parse_objects(जोड़ acpi_parse_object *parse_tree_root,
			      काष्ठा acpi_namespace_node *namespace_root);

/*
 * adfile
 */
acpi_status ad_initialize(व्योम);

अक्षर *fl_generate_filename(अक्षर *input_filename, अक्षर *suffix);

acpi_status
fl_split_input_pathname(अक्षर *input_path,
			अक्षर **out_directory_path, अक्षर **out_filename);

अक्षर *fl_get_file_basename(अक्षर *file_pathname);

अक्षर *ad_generate_filename(अक्षर *prefix, अक्षर *table_id);

व्योम
ad_ग_लिखो_table(काष्ठा acpi_table_header *table,
	       u32 length, अक्षर *table_name, अक्षर *oem_table_id);

#पूर्ण_अगर				/* _ACAPPS */
