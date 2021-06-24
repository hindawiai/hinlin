<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dbhistry - debugger HISTORY command
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbhistry")

#घोषणा HI_NO_HISTORY       0
#घोषणा HI_RECORD_HISTORY   1
#घोषणा HISTORY_SIZE        40
प्रकार काष्ठा history_info अणु
	अक्षर *command;
	u32 cmd_num;

पूर्ण HISTORY_INFO;

अटल HISTORY_INFO acpi_gbl_history_buffer[HISTORY_SIZE];
अटल u16 acpi_gbl_lo_history = 0;
अटल u16 acpi_gbl_num_history = 0;
अटल u16 acpi_gbl_next_history_index = 0;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_add_to_history
 *
 * PARAMETERS:  command_line    - Command to add
 *
 * RETURN:      None
 *
 * DESCRIPTION: Add a command line to the history buffer.
 *
 ******************************************************************************/

व्योम acpi_db_add_to_history(अक्षर *command_line)
अणु
	u16 cmd_len;
	u16 buffer_len;

	/* Put command पूर्णांकo the next available slot */

	cmd_len = (u16)म_माप(command_line);
	अगर (!cmd_len) अणु
		वापस;
	पूर्ण

	अगर (acpi_gbl_history_buffer[acpi_gbl_next_history_index].command !=
	    शून्य) अणु
		buffer_len =
		    (u16)
		    म_माप(acpi_gbl_history_buffer[acpi_gbl_next_history_index].
			   command);

		अगर (cmd_len > buffer_len) अणु
			acpi_os_मुक्त(acpi_gbl_history_buffer
				     [acpi_gbl_next_history_index].command);
			acpi_gbl_history_buffer[acpi_gbl_next_history_index].
			    command = acpi_os_allocate(cmd_len + 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		acpi_gbl_history_buffer[acpi_gbl_next_history_index].command =
		    acpi_os_allocate(cmd_len + 1);
	पूर्ण

	म_नकल(acpi_gbl_history_buffer[acpi_gbl_next_history_index].command,
	       command_line);

	acpi_gbl_history_buffer[acpi_gbl_next_history_index].cmd_num =
	    acpi_gbl_next_cmd_num;

	/* Adjust indexes */

	अगर ((acpi_gbl_num_history == HISTORY_SIZE) &&
	    (acpi_gbl_next_history_index == acpi_gbl_lo_history)) अणु
		acpi_gbl_lo_history++;
		अगर (acpi_gbl_lo_history >= HISTORY_SIZE) अणु
			acpi_gbl_lo_history = 0;
		पूर्ण
	पूर्ण

	acpi_gbl_next_history_index++;
	अगर (acpi_gbl_next_history_index >= HISTORY_SIZE) अणु
		acpi_gbl_next_history_index = 0;
	पूर्ण

	acpi_gbl_next_cmd_num++;
	अगर (acpi_gbl_num_history < HISTORY_SIZE) अणु
		acpi_gbl_num_history++;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_history
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display the contents of the history buffer
 *
 ******************************************************************************/

व्योम acpi_db_display_history(व्योम)
अणु
	u32 i;
	u16 history_index;

	history_index = acpi_gbl_lo_history;

	/* Dump entire history buffer */

	क्रम (i = 0; i < acpi_gbl_num_history; i++) अणु
		अगर (acpi_gbl_history_buffer[history_index].command) अणु
			acpi_os_म_लिखो("%3u %s\n",
				       acpi_gbl_history_buffer[history_index].
				       cmd_num,
				       acpi_gbl_history_buffer[history_index].
				       command);
		पूर्ण

		history_index++;
		अगर (history_index >= HISTORY_SIZE) अणु
			history_index = 0;
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_from_history
 *
 * PARAMETERS:  command_num_arg         - String containing the number of the
 *                                        command to be retrieved
 *
 * RETURN:      Poपूर्णांकer to the retrieved command. Null on error.
 *
 * DESCRIPTION: Get a command from the history buffer
 *
 ******************************************************************************/

अक्षर *acpi_db_get_from_history(अक्षर *command_num_arg)
अणु
	u32 cmd_num;

	अगर (command_num_arg == शून्य) अणु
		cmd_num = acpi_gbl_next_cmd_num - 1;
	पूर्ण

	अन्यथा अणु
		cmd_num = म_से_अदीर्घ(command_num_arg, शून्य, 0);
	पूर्ण

	वापस (acpi_db_get_history_by_index(cmd_num));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_history_by_index
 *
 * PARAMETERS:  cmd_num             - Index of the desired history entry.
 *                                    Values are 0...(acpi_gbl_next_cmd_num - 1)
 *
 * RETURN:      Poपूर्णांकer to the retrieved command. Null on error.
 *
 * DESCRIPTION: Get a command from the history buffer
 *
 ******************************************************************************/

अक्षर *acpi_db_get_history_by_index(u32 cmd_num)
अणु
	u32 i;
	u16 history_index;

	/* Search history buffer */

	history_index = acpi_gbl_lo_history;
	क्रम (i = 0; i < acpi_gbl_num_history; i++) अणु
		अगर (acpi_gbl_history_buffer[history_index].cmd_num == cmd_num) अणु

			/* Found the command, वापस it */

			वापस (acpi_gbl_history_buffer[history_index].command);
		पूर्ण

		/* History buffer is circular */

		history_index++;
		अगर (history_index >= HISTORY_SIZE) अणु
			history_index = 0;
		पूर्ण
	पूर्ण

	acpi_os_म_लिखो("Invalid history number: %u\n", history_index);
	वापस (शून्य);
पूर्ण
