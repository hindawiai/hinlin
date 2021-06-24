<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbfileio - Debugger file I/O commands. These can't usually
 *              be used when running the debugger in Ring 0 (Kernel mode)
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbfileio")

#अगर_घोषित ACPI_APPLICATION
#समावेश "acapps.h"
#अगर_घोषित ACPI_DEBUGGER
/*******************************************************************************
 *
 * FUNCTION:    acpi_db_बंद_debug_file
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: If खोलो, बंद the current debug output file
 *
 ******************************************************************************/
व्योम acpi_db_बंद_debug_file(व्योम)
अणु

	अगर (acpi_gbl_debug_file) अणु
		ख_बंद(acpi_gbl_debug_file);
		acpi_gbl_debug_file = शून्य;
		acpi_gbl_db_output_to_file = FALSE;
		acpi_os_म_लिखो("Debug output file %s closed\n",
			       acpi_gbl_db_debug_filename);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_खोलो_debug_file
 *
 * PARAMETERS:  name                - Filename to खोलो
 *
 * RETURN:      None
 *
 * DESCRIPTION: Open a file where debug output will be directed.
 *
 ******************************************************************************/

व्योम acpi_db_खोलो_debug_file(अक्षर *name)
अणु

	acpi_db_बंद_debug_file();
	acpi_gbl_debug_file = ख_खोलो(name, "w+");
	अगर (!acpi_gbl_debug_file) अणु
		acpi_os_म_लिखो("Could not open debug file %s\n", name);
		वापस;
	पूर्ण

	acpi_os_म_लिखो("Debug output file %s opened\n", name);
	acpi_ut_safe_म_नकलन(acpi_gbl_db_debug_filename, name,
			     माप(acpi_gbl_db_debug_filename));
	acpi_gbl_db_output_to_file = TRUE;
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_load_tables
 *
 * PARAMETERS:  list_head       - List of ACPI tables to load
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Load ACPI tables from a previously स्थिरructed table list.
 *
 ******************************************************************************/

acpi_status acpi_db_load_tables(काष्ठा acpi_new_table_desc *list_head)
अणु
	acpi_status status;
	काष्ठा acpi_new_table_desc *table_list_head;
	काष्ठा acpi_table_header *table;

	/* Load all ACPI tables in the list */

	table_list_head = list_head;
	जबतक (table_list_head) अणु
		table = table_list_head->table;

		status = acpi_load_table(table, शून्य);
		अगर (ACPI_FAILURE(status)) अणु
			अगर (status == AE_ALREADY_EXISTS) अणु
				acpi_os_म_लिखो
				    ("Table %4.4s is already installed\n",
				     table->signature);
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो("Could not install table, %s\n",
					       acpi_क्रमmat_exception(status));
			पूर्ण

			वापस (status);
		पूर्ण

		acpi_os_म_लिखो
		    ("Acpi table [%4.4s] successfully installed and loaded\n",
		     table->signature);

		table_list_head = table_list_head->next;
	पूर्ण

	वापस (AE_OK);
पूर्ण
#पूर्ण_अगर
