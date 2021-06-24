<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dbinput - user front-end to the AML debugger
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdebug.h"

#अगर_घोषित ACPI_APPLICATION
#समावेश "acapps.h"
#पूर्ण_अगर

#घोषणा _COMPONENT          ACPI_CA_DEBUGGER
ACPI_MODULE_NAME("dbinput")

/* Local prototypes */
अटल u32 acpi_db_get_line(अक्षर *input_buffer);

अटल u32 acpi_db_match_command(अक्षर *user_command);

अटल व्योम acpi_db_display_command_info(स्थिर अक्षर *command, u8 display_all);

अटल व्योम acpi_db_display_help(अक्षर *command);

अटल u8
acpi_db_match_command_help(स्थिर अक्षर *command,
			   स्थिर काष्ठा acpi_db_command_help *help);

/*
 * Top-level debugger commands.
 *
 * This list of commands must match the string table below it
 */
क्रमागत acpi_ex_debugger_commands अणु
	CMD_NOT_FOUND = 0,
	CMD_शून्य,
	CMD_ALL,
	CMD_ALLOCATIONS,
	CMD_ARGS,
	CMD_ARGUMENTS,
	CMD_BREAKPOINT,
	CMD_BUSINFO,
	CMD_CALL,
	CMD_DEBUG,
	CMD_DISASSEMBLE,
	CMD_DISASM,
	CMD_DUMP,
	CMD_EVALUATE,
	CMD_EXECUTE,
	CMD_EXIT,
	CMD_FIELDS,
	CMD_FIND,
	CMD_GO,
	CMD_HANDLERS,
	CMD_HELP,
	CMD_HELP2,
	CMD_HISTORY,
	CMD_HISTORY_EXE,
	CMD_HISTORY_LAST,
	CMD_INFORMATION,
	CMD_INTEGRITY,
	CMD_INTO,
	CMD_LEVEL,
	CMD_LIST,
	CMD_LOCALS,
	CMD_LOCKS,
	CMD_METHODS,
	CMD_NAMESPACE,
	CMD_NOTIFY,
	CMD_OBJECTS,
	CMD_OSI,
	CMD_OWNER,
	CMD_PATHS,
	CMD_PREDEFINED,
	CMD_PREFIX,
	CMD_QUIT,
	CMD_REFERENCES,
	CMD_RESOURCES,
	CMD_RESULTS,
	CMD_SET,
	CMD_STATS,
	CMD_STOP,
	CMD_TABLES,
	CMD_TEMPLATE,
	CMD_TRACE,
	CMD_TREE,
	CMD_TYPE,
#अगर_घोषित ACPI_APPLICATION
	CMD_ENABLEACPI,
	CMD_EVENT,
	CMD_GPE,
	CMD_GPES,
	CMD_SCI,
	CMD_SLEEP,

	CMD_CLOSE,
	CMD_LOAD,
	CMD_OPEN,
	CMD_UNLOAD,

	CMD_TERMINATE,
	CMD_BACKGROUND,
	CMD_THREADS,

	CMD_TEST,
#पूर्ण_अगर
पूर्ण;

#घोषणा CMD_FIRST_VALID     2

/* Second parameter is the required argument count */

अटल स्थिर काष्ठा acpi_db_command_info acpi_gbl_db_commands[] = अणु
	अणु"<NOT FOUND>", 0पूर्ण,
	अणु"<NULL>", 0पूर्ण,
	अणु"ALL", 1पूर्ण,
	अणु"ALLOCATIONS", 0पूर्ण,
	अणु"ARGS", 0पूर्ण,
	अणु"ARGUMENTS", 0पूर्ण,
	अणु"BREAKPOINT", 1पूर्ण,
	अणु"BUSINFO", 0पूर्ण,
	अणु"CALL", 0पूर्ण,
	अणु"DEBUG", 1पूर्ण,
	अणु"DISASSEMBLE", 1पूर्ण,
	अणु"DISASM", 1पूर्ण,
	अणु"DUMP", 1पूर्ण,
	अणु"EVALUATE", 1पूर्ण,
	अणु"EXECUTE", 1पूर्ण,
	अणु"EXIT", 0पूर्ण,
	अणु"FIELDS", 1पूर्ण,
	अणु"FIND", 1पूर्ण,
	अणु"GO", 0पूर्ण,
	अणु"HANDLERS", 0पूर्ण,
	अणु"HELP", 0पूर्ण,
	अणु"?", 0पूर्ण,
	अणु"HISTORY", 0पूर्ण,
	अणु"!", 1पूर्ण,
	अणु"!!", 0पूर्ण,
	अणु"INFORMATION", 0पूर्ण,
	अणु"INTEGRITY", 0पूर्ण,
	अणु"INTO", 0पूर्ण,
	अणु"LEVEL", 0पूर्ण,
	अणु"LIST", 0पूर्ण,
	अणु"LOCALS", 0पूर्ण,
	अणु"LOCKS", 0पूर्ण,
	अणु"METHODS", 0पूर्ण,
	अणु"NAMESPACE", 0पूर्ण,
	अणु"NOTIFY", 2पूर्ण,
	अणु"OBJECTS", 0पूर्ण,
	अणु"OSI", 0पूर्ण,
	अणु"OWNER", 1पूर्ण,
	अणु"PATHS", 0पूर्ण,
	अणु"PREDEFINED", 0पूर्ण,
	अणु"PREFIX", 0पूर्ण,
	अणु"QUIT", 0पूर्ण,
	अणु"REFERENCES", 1पूर्ण,
	अणु"RESOURCES", 0पूर्ण,
	अणु"RESULTS", 0पूर्ण,
	अणु"SET", 3पूर्ण,
	अणु"STATS", 1पूर्ण,
	अणु"STOP", 0पूर्ण,
	अणु"TABLES", 0पूर्ण,
	अणु"TEMPLATE", 1पूर्ण,
	अणु"TRACE", 1पूर्ण,
	अणु"TREE", 0पूर्ण,
	अणु"TYPE", 1पूर्ण,
#अगर_घोषित ACPI_APPLICATION
	अणु"ENABLEACPI", 0पूर्ण,
	अणु"EVENT", 1पूर्ण,
	अणु"GPE", 1पूर्ण,
	अणु"GPES", 0पूर्ण,
	अणु"SCI", 0पूर्ण,
	अणु"SLEEP", 0पूर्ण,

	अणु"CLOSE", 0पूर्ण,
	अणु"LOAD", 1पूर्ण,
	अणु"OPEN", 1पूर्ण,
	अणु"UNLOAD", 1पूर्ण,

	अणु"TERMINATE", 0पूर्ण,
	अणु"BACKGROUND", 1पूर्ण,
	अणु"THREADS", 3पूर्ण,

	अणु"TEST", 1पूर्ण,
#पूर्ण_अगर
	अणुशून्य, 0पूर्ण
पूर्ण;

/*
 * Help क्रम all debugger commands. First argument is the number of lines
 * of help to output क्रम the command.
 *
 * Note: Some commands are not supported by the kernel-level version of
 * the debugger.
 */
अटल स्थिर काष्ठा acpi_db_command_help acpi_gbl_db_command_help[] = अणु
	अणु0, "\nNamespace Access:", "\n"पूर्ण,
	अणु1, "  Businfo", "Display system bus info\n"पूर्ण,
	अणु1, "  Disassemble <Method>", "Disassemble a control method\n"पूर्ण,
	अणु1, "  Find <AcpiName> (? is wildcard)",
	 "Find ACPI name(s) with wildcards\n"पूर्ण,
	अणु1, "  Integrity", "Validate namespace integrity\n"पूर्ण,
	अणु1, "  Methods", "Display list of loaded control methods\n"पूर्ण,
	अणु1, "  Fields <AddressSpaceId>",
	 "Display list of loaded field units by space ID\n"पूर्ण,
	अणु1, "  Namespace [Object] [Depth]",
	 "Display loaded namespace tree/subtree\n"पूर्ण,
	अणु1, "  Notify <Object> <Value>", "Send a notification on Object\n"पूर्ण,
	अणु1, "  Objects [ObjectType]",
	 "Display summary of all objects or just given type\n"पूर्ण,
	अणु1, "  Owner <OwnerId> [Depth]",
	 "Display loaded namespace by object owner\n"पूर्ण,
	अणु1, "  Paths", "Display full pathnames of namespace objects\n"पूर्ण,
	अणु1, "  Predefined", "Check all predefined names\n"पूर्ण,
	अणु1, "  Prefix [<Namepath>]", "Set or Get current execution prefix\n"पूर्ण,
	अणु1, "  References <Addr>", "Find all references to object at addr\n"पूर्ण,
	अणु1, "  Resources [DeviceName]",
	 "Display Device resources (no arg = all devices)\n"पूर्ण,
	अणु1, "  Set N <NamedObject> <Value>", "Set value for named integer\n"पूर्ण,
	अणु1, "  Template <Object>", "Format/dump a Buffer/ResourceTemplate\n"पूर्ण,
	अणु1, "  Type <Object>", "Display object type\n"पूर्ण,

	अणु0, "\nControl Method Execution:", "\n"पूर्ण,
	अणु1, "  All <NameSeg>", "Evaluate all objects named NameSeg\n"पूर्ण,
	अणु1, "  Evaluate <Namepath> [Arguments]",
	 "Evaluate object or control method\n"पूर्ण,
	अणु1, "  Execute <Namepath> [Arguments]", "Synonym for Evaluate\n"पूर्ण,
#अगर_घोषित ACPI_APPLICATION
	अणु1, "  Background <Namepath> [Arguments]",
	 "Evaluate object/method in a separate thread\n"पूर्ण,
	अणु1, "  Thread <Threads><Loops><NamePath>",
	 "Spawn threads to execute method(s)\n"पूर्ण,
#पूर्ण_अगर
	अणु1, "  Debug <Namepath> [Arguments]", "Single-Step a control method\n"पूर्ण,
	अणु7, "  [Arguments] formats:", "Control method argument formats\n"पूर्ण,
	अणु1, "     Hex Integer", "Integer\n"पूर्ण,
	अणु1, "     \"Ascii String\"", "String\n"पूर्ण,
	अणु1, "     (Hex Byte List)", "Buffer\n"पूर्ण,
	अणु1, "         (01 42 7A BF)", "Buffer example (4 bytes)\n"पूर्ण,
	अणु1, "     [Package Element List]", "Package\n"पूर्ण,
	अणु1, "         [0x01 0x1234 \"string\"]",
	 "Package example (3 elements)\n"पूर्ण,

	अणु0, "\nMiscellaneous:", "\n"पूर्ण,
	अणु1, "  Allocations", "Display list of current memory allocations\n"पूर्ण,
	अणु2, "  Dump <Address>|<Namepath>", "\n"पूर्ण,
	अणु0, "       [Byte|Word|Dword|Qword]",
	 "Display ACPI objects or memory\n"पूर्ण,
	अणु1, "  Handlers", "Info about global handlers\n"पूर्ण,
	अणु1, "  Help [Command]", "This help screen or individual command\n"पूर्ण,
	अणु1, "  History", "Display command history buffer\n"पूर्ण,
	अणु1, "  Level <DebugLevel>] [console]",
	 "Get/Set debug level for file or console\n"पूर्ण,
	अणु1, "  Locks", "Current status of internal mutexes\n"पूर्ण,
	अणु1, "  Osi [Install|Remove <name>]",
	 "Display or modify global _OSI list\n"पूर्ण,
	अणु1, "  Quit or Exit", "Exit this command\n"पूर्ण,
	अणु8, "  Stats <SubCommand>",
	 "Display namespace and memory statistics\n"पूर्ण,
	अणु1, "     Allocations", "Display list of current memory allocations\n"पूर्ण,
	अणु1, "     Memory", "Dump internal memory lists\n"पूर्ण,
	अणु1, "     Misc", "Namespace search and mutex stats\n"पूर्ण,
	अणु1, "     Objects", "Summary of namespace objects\n"पूर्ण,
	अणु1, "     Sizes", "Sizes for each of the internal objects\n"पूर्ण,
	अणु1, "     Stack", "Display CPU stack usage\n"पूर्ण,
	अणु1, "     Tables", "Info about current ACPI table(s)\n"पूर्ण,
	अणु1, "  Tables", "Display info about loaded ACPI tables\n"पूर्ण,
#अगर_घोषित ACPI_APPLICATION
	अणु1, "  Terminate", "Delete namespace and all internal objects\n"पूर्ण,
#पूर्ण_अगर
	अणु1, "  ! <CommandNumber>", "Execute command from history buffer\n"पूर्ण,
	अणु1, "  !!", "Execute last command again\n"पूर्ण,

	अणु0, "\nMethod and Namespace Debugging:", "\n"पूर्ण,
	अणु5, "  Trace <State> [<Namepath>] [Once]",
	 "Trace control method execution\n"पूर्ण,
	अणु1, "     Enable", "Enable all messages\n"पूर्ण,
	अणु1, "     Disable", "Disable tracing\n"पूर्ण,
	अणु1, "     Method", "Enable method execution messages\n"पूर्ण,
	अणु1, "     Opcode", "Enable opcode execution messages\n"पूर्ण,
	अणु3, "  Test <TestName>", "Invoke a debug test\n"पूर्ण,
	अणु1, "     Objects", "Read/write/compare all namespace data objects\n"पूर्ण,
	अणु1, "     Predefined",
	 "Validate all ACPI predefined names (_STA, etc.)\n"पूर्ण,
	अणु1, "  Execute predefined",
	 "Execute all predefined (public) methods\n"पूर्ण,

	अणु0, "\nControl Method Single-Step Execution:", "\n"पूर्ण,
	अणु1, "  Arguments (or Args)", "Display method arguments\n"पूर्ण,
	अणु1, "  Breakpoint <AmlOffset>", "Set an AML execution breakpoint\n"पूर्ण,
	अणु1, "  Call", "Run to next control method invocation\n"पूर्ण,
	अणु1, "  Go", "Allow method to run to completion\n"पूर्ण,
	अणु1, "  Information", "Display info about the current method\n"पूर्ण,
	अणु1, "  Into", "Step into (not over) a method call\n"पूर्ण,
	अणु1, "  List [# of Aml Opcodes]", "Display method ASL statements\n"पूर्ण,
	अणु1, "  Locals", "Display method local variables\n"पूर्ण,
	अणु1, "  Results", "Display method result stack\n"पूर्ण,
	अणु1, "  Set <A|L> <#> <Value>", "Set method data (Arguments/Locals)\n"पूर्ण,
	अणु1, "  Stop", "Terminate control method\n"पूर्ण,
	अणु1, "  Tree", "Display control method calling tree\n"पूर्ण,
	अणु1, "  <Enter>", "Single step next AML opcode (over calls)\n"पूर्ण,

#अगर_घोषित ACPI_APPLICATION
	अणु0, "\nFile Operations:", "\n"पूर्ण,
	अणु1, "  Close", "Close debug output file\n"पूर्ण,
	अणु1, "  Load <Input Filename>", "Load ACPI table from a file\n"पूर्ण,
	अणु1, "  Open <Output Filename>", "Open a file for debug output\n"पूर्ण,
	अणु1, "  Unload <Namepath>",
	 "Unload an ACPI table via namespace object\n"पूर्ण,

	अणु0, "\nHardware Simulation:", "\n"पूर्ण,
	अणु1, "  EnableAcpi", "Enable ACPI (hardware) mode\n"पूर्ण,
	अणु1, "  Event <F|G> <Value>", "Generate AcpiEvent (Fixed/GPE)\n"पूर्ण,
	अणु1, "  Gpe <GpeNum> [GpeBlockDevice]", "Simulate a GPE\n"पूर्ण,
	अणु1, "  Gpes", "Display info on all GPE devices\n"पूर्ण,
	अणु1, "  Sci", "Generate an SCI\n"पूर्ण,
	अणु1, "  Sleep [SleepState]", "Simulate sleep/wake sequence(s) (0-5)\n"पूर्ण,
#पूर्ण_अगर
	अणु0, शून्य, शून्यपूर्ण
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_match_command_help
 *
 * PARAMETERS:  command             - Command string to match
 *              help                - Help table entry to attempt match
 *
 * RETURN:      TRUE अगर command matched, FALSE otherwise
 *
 * DESCRIPTION: Attempt to match a command in the help table in order to
 *              prपूर्णांक help inक्रमmation क्रम a single command.
 *
 ******************************************************************************/

अटल u8
acpi_db_match_command_help(स्थिर अक्षर *command,
			   स्थिर काष्ठा acpi_db_command_help *help)
अणु
	अक्षर *invocation = help->invocation;
	u32 line_count;

	/* Valid commands in the help table begin with a couple of spaces */

	अगर (*invocation != ' ') अणु
		वापस (FALSE);
	पूर्ण

	जबतक (*invocation == ' ') अणु
		invocation++;
	पूर्ण

	/* Match command name (full command or substring) */

	जबतक ((*command) && (*invocation) && (*invocation != ' ')) अणु
		अगर (छोटे((पूर्णांक)*command) != छोटे((पूर्णांक)*invocation)) अणु
			वापस (FALSE);
		पूर्ण

		invocation++;
		command++;
	पूर्ण

	/* Prपूर्णांक the appropriate number of help lines */

	line_count = help->line_count;
	जबतक (line_count) अणु
		acpi_os_म_लिखो("%-38s : %s", help->invocation,
			       help->description);
		help++;
		line_count--;
	पूर्ण

	वापस (TRUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_command_info
 *
 * PARAMETERS:  command             - Command string to match
 *              display_all         - Display all matching commands, or just
 *                                    the first one (substring match)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display help inक्रमmation क्रम a Debugger command.
 *
 ******************************************************************************/

अटल व्योम acpi_db_display_command_info(स्थिर अक्षर *command, u8 display_all)
अणु
	स्थिर काष्ठा acpi_db_command_help *next;
	u8 matched;

	next = acpi_gbl_db_command_help;
	जबतक (next->invocation) अणु
		matched = acpi_db_match_command_help(command, next);
		अगर (!display_all && matched) अणु
			वापस;
		पूर्ण

		next++;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_display_help
 *
 * PARAMETERS:  command             - Optional command string to display help.
 *                                    अगर not specअगरied, all debugger command
 *                                    help strings are displayed
 *
 * RETURN:      None
 *
 * DESCRIPTION: Display help क्रम a single debugger command, or all of them.
 *
 ******************************************************************************/

अटल व्योम acpi_db_display_help(अक्षर *command)
अणु
	स्थिर काष्ठा acpi_db_command_help *next = acpi_gbl_db_command_help;

	अगर (!command) अणु

		/* No argument to help, display help क्रम all commands */

		acpi_os_म_लिखो("\nSummary of AML Debugger Commands\n\n");

		जबतक (next->invocation) अणु
			acpi_os_म_लिखो("%-38s%s", next->invocation,
				       next->description);
			next++;
		पूर्ण
		acpi_os_म_लिखो("\n");

	पूर्ण अन्यथा अणु
		/* Display help क्रम all commands that match the substring */

		acpi_db_display_command_info(command, TRUE);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_next_token
 *
 * PARAMETERS:  string          - Command buffer
 *              next            - Return value, end of next token
 *
 * RETURN:      Poपूर्णांकer to the start of the next token.
 *
 * DESCRIPTION: Command line parsing. Get the next token on the command line
 *
 ******************************************************************************/

अक्षर *acpi_db_get_next_token(अक्षर *string,
			     अक्षर **next, acpi_object_type *वापस_type)
अणु
	अक्षर *start;
	u32 depth;
	acpi_object_type type = ACPI_TYPE_INTEGER;

	/* At end of buffer? */

	अगर (!string || !(*string)) अणु
		वापस (शून्य);
	पूर्ण

	/* Remove any spaces at the beginning, ignore blank lines */

	जबतक (*string && है_खाली((पूर्णांक)*string)) अणु
		string++;
	पूर्ण

	अगर (!(*string)) अणु
		वापस (शून्य);
	पूर्ण

	चयन (*string) अणु
	हाल '"':

		/* This is a quoted string, scan until closing quote */

		string++;
		start = string;
		type = ACPI_TYPE_STRING;

		/* Find end of string */

		जबतक (*string && (*string != '"')) अणु
			string++;
		पूर्ण
		अवरोध;

	हाल '(':

		/* This is the start of a buffer, scan until closing paren */

		string++;
		start = string;
		type = ACPI_TYPE_BUFFER;

		/* Find end of buffer */

		जबतक (*string && (*string != ')')) अणु
			string++;
		पूर्ण
		अवरोध;

	हाल '{':

		/* This is the start of a field unit, scan until closing brace */

		string++;
		start = string;
		type = ACPI_TYPE_FIELD_UNIT;

		/* Find end of buffer */

		जबतक (*string && (*string != '}')) अणु
			string++;
		पूर्ण
		अवरोध;

	हाल '[':

		/* This is the start of a package, scan until closing bracket */

		string++;
		depth = 1;
		start = string;
		type = ACPI_TYPE_PACKAGE;

		/* Find end of package (closing bracket) */

		जबतक (*string) अणु

			/* Handle String package elements */

			अगर (*string == '"') अणु
				/* Find end of string */

				string++;
				जबतक (*string && (*string != '"')) अणु
					string++;
				पूर्ण
				अगर (!(*string)) अणु
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अगर (*string == '[') अणु
				depth++;	/* A nested package declaration */
			पूर्ण अन्यथा अगर (*string == ']') अणु
				depth--;
				अगर (depth == 0) अणु	/* Found final package closing bracket */
					अवरोध;
				पूर्ण
			पूर्ण

			string++;
		पूर्ण
		अवरोध;

	शेष:

		start = string;

		/* Find end of token */

		जबतक (*string && !है_खाली((पूर्णांक)*string)) अणु
			string++;
		पूर्ण
		अवरोध;
	पूर्ण

	अगर (!(*string)) अणु
		*next = शून्य;
	पूर्ण अन्यथा अणु
		*string = 0;
		*next = string + 1;
	पूर्ण

	*वापस_type = type;
	वापस (start);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_get_line
 *
 * PARAMETERS:  input_buffer        - Command line buffer
 *
 * RETURN:      Count of arguments to the command
 *
 * DESCRIPTION: Get the next command line from the user. Gets entire line
 *              up to the next newline
 *
 ******************************************************************************/

अटल u32 acpi_db_get_line(अक्षर *input_buffer)
अणु
	u32 i;
	u32 count;
	अक्षर *next;
	अक्षर *this;

	अगर (acpi_ut_safe_म_नकल
	    (acpi_gbl_db_parsed_buf, माप(acpi_gbl_db_parsed_buf),
	     input_buffer)) अणु
		acpi_os_म_लिखो
		    ("Buffer overflow while parsing input line (max %u characters)\n",
		     (u32)माप(acpi_gbl_db_parsed_buf));
		वापस (0);
	पूर्ण

	this = acpi_gbl_db_parsed_buf;
	क्रम (i = 0; i < ACPI_DEBUGGER_MAX_ARGS; i++) अणु
		acpi_gbl_db_args[i] = acpi_db_get_next_token(this, &next,
							     &acpi_gbl_db_arg_types
							     [i]);
		अगर (!acpi_gbl_db_args[i]) अणु
			अवरोध;
		पूर्ण

		this = next;
	पूर्ण

	/* Upperहाल the actual command */

	acpi_ut_strupr(acpi_gbl_db_args[0]);

	count = i;
	अगर (count) अणु
		count--;	/* Number of args only */
	पूर्ण

	वापस (count);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_match_command
 *
 * PARAMETERS:  user_command            - User command line
 *
 * RETURN:      Index पूर्णांकo command array, -1 अगर not found
 *
 * DESCRIPTION: Search command array क्रम a command match
 *
 ******************************************************************************/

अटल u32 acpi_db_match_command(अक्षर *user_command)
अणु
	u32 i;

	अगर (!user_command || user_command[0] == 0) अणु
		वापस (CMD_शून्य);
	पूर्ण

	क्रम (i = CMD_FIRST_VALID; acpi_gbl_db_commands[i].name; i++) अणु
		अगर (म_माला
		    (ACPI_CAST_PTR(अक्षर, acpi_gbl_db_commands[i].name),
		     user_command) == acpi_gbl_db_commands[i].name) अणु
			वापस (i);
		पूर्ण
	पूर्ण

	/* Command not recognized */

	वापस (CMD_NOT_FOUND);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_command_dispatch
 *
 * PARAMETERS:  input_buffer        - Command line buffer
 *              walk_state          - Current walk
 *              op                  - Current (executing) parse op
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Command dispatcher.
 *
 ******************************************************************************/

acpi_status
acpi_db_command_dispatch(अक्षर *input_buffer,
			 काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op)
अणु
	u32 temp;
	u64 temp64;
	u32 command_index;
	u32 param_count;
	अक्षर *command_line;
	acpi_status status = AE_CTRL_TRUE;

	/* If acpi_terminate has been called, terminate this thपढ़ो */

	अगर (acpi_gbl_db_terminate_loop) अणु
		वापस (AE_CTRL_TERMINATE);
	पूर्ण

	/* Find command and add to the history buffer */

	param_count = acpi_db_get_line(input_buffer);
	command_index = acpi_db_match_command(acpi_gbl_db_args[0]);

	/*
	 * We करोn't want to add the !! command to the history buffer. It
	 * would cause an infinite loop because it would always be the
	 * previous command.
	 */
	अगर (command_index != CMD_HISTORY_LAST) अणु
		acpi_db_add_to_history(input_buffer);
	पूर्ण

	/* Verअगरy that we have the minimum number of params */

	अगर (param_count < acpi_gbl_db_commands[command_index].min_args) अणु
		acpi_os_म_लिखो
		    ("%u parameters entered, [%s] requires %u parameters\n",
		     param_count, acpi_gbl_db_commands[command_index].name,
		     acpi_gbl_db_commands[command_index].min_args);

		acpi_db_display_command_info(acpi_gbl_db_commands
					     [command_index].name, FALSE);
		वापस (AE_CTRL_TRUE);
	पूर्ण

	/* Decode and dispatch the command */

	चयन (command_index) अणु
	हाल CMD_शून्य:

		अगर (op) अणु
			वापस (AE_OK);
		पूर्ण
		अवरोध;

	हाल CMD_ALL:

		acpi_os_म_लिखो("Executing all objects with NameSeg: %s\n",
			       acpi_gbl_db_args[1]);
		acpi_db_execute(acpi_gbl_db_args[1], &acpi_gbl_db_args[2],
				&acpi_gbl_db_arg_types[2],
				EX_NO_SINGLE_STEP | EX_ALL);
		अवरोध;

	हाल CMD_ALLOCATIONS:

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
		acpi_ut_dump_allocations((u32)-1, शून्य);
#पूर्ण_अगर
		अवरोध;

	हाल CMD_ARGS:
	हाल CMD_ARGUMENTS:

		acpi_db_display_arguments();
		अवरोध;

	हाल CMD_BREAKPOINT:

		acpi_db_set_method_अवरोधpoपूर्णांक(acpi_gbl_db_args[1], walk_state,
					      op);
		अवरोध;

	हाल CMD_BUSINFO:

		acpi_db_get_bus_info();
		अवरोध;

	हाल CMD_CALL:

		acpi_db_set_method_call_अवरोधpoपूर्णांक(op);
		status = AE_OK;
		अवरोध;

	हाल CMD_DEBUG:

		acpi_db_execute(acpi_gbl_db_args[1],
				&acpi_gbl_db_args[2], &acpi_gbl_db_arg_types[2],
				EX_SINGLE_STEP);
		अवरोध;

	हाल CMD_DISASSEMBLE:
	हाल CMD_DISASM:

#अगर_घोषित ACPI_DISASSEMBLER
		(व्योम)acpi_db_disassemble_method(acpi_gbl_db_args[1]);
#अन्यथा
		acpi_os_म_लिखो
		    ("The AML Disassembler is not configured/present\n");
#पूर्ण_अगर
		अवरोध;

	हाल CMD_DUMP:

		acpi_db_decode_and_display_object(acpi_gbl_db_args[1],
						  acpi_gbl_db_args[2]);
		अवरोध;

	हाल CMD_EVALUATE:
	हाल CMD_EXECUTE:

		acpi_db_execute(acpi_gbl_db_args[1],
				&acpi_gbl_db_args[2], &acpi_gbl_db_arg_types[2],
				EX_NO_SINGLE_STEP);
		अवरोध;

	हाल CMD_FIND:

		status = acpi_db_find_name_in_namespace(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_FIELDS:

		status = acpi_ut_म_से_अदीर्घ64(acpi_gbl_db_args[1], &temp64);

		अगर (ACPI_FAILURE(status)
		    || temp64 >= ACPI_NUM_PREDEFINED_REGIONS) अणु
			acpi_os_म_लिखो
			    ("Invalid address space ID: must be between 0 and %u inclusive\n",
			     ACPI_NUM_PREDEFINED_REGIONS - 1);
			वापस (AE_OK);
		पूर्ण

		status = acpi_db_display_fields((u32)temp64);
		अवरोध;

	हाल CMD_GO:

		acpi_gbl_cm_single_step = FALSE;
		वापस (AE_OK);

	हाल CMD_HANDLERS:

		acpi_db_display_handlers();
		अवरोध;

	हाल CMD_HELP:
	हाल CMD_HELP2:

		acpi_db_display_help(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_HISTORY:

		acpi_db_display_history();
		अवरोध;

	हाल CMD_HISTORY_EXE:	/* ! command */

		command_line = acpi_db_get_from_history(acpi_gbl_db_args[1]);
		अगर (!command_line) अणु
			वापस (AE_CTRL_TRUE);
		पूर्ण

		status = acpi_db_command_dispatch(command_line, walk_state, op);
		वापस (status);

	हाल CMD_HISTORY_LAST:	/* !! command */

		command_line = acpi_db_get_from_history(शून्य);
		अगर (!command_line) अणु
			वापस (AE_CTRL_TRUE);
		पूर्ण

		status = acpi_db_command_dispatch(command_line, walk_state, op);
		वापस (status);

	हाल CMD_INFORMATION:

		acpi_db_display_method_info(op);
		अवरोध;

	हाल CMD_INTEGRITY:

		acpi_db_check_पूर्णांकegrity();
		अवरोध;

	हाल CMD_INTO:

		अगर (op) अणु
			acpi_gbl_cm_single_step = TRUE;
			वापस (AE_OK);
		पूर्ण
		अवरोध;

	हाल CMD_LEVEL:

		अगर (param_count == 0) अणु
			acpi_os_म_लिखो
			    ("Current debug level for file output is:    %8.8X\n",
			     acpi_gbl_db_debug_level);
			acpi_os_म_लिखो
			    ("Current debug level for console output is: %8.8X\n",
			     acpi_gbl_db_console_debug_level);
		पूर्ण अन्यथा अगर (param_count == 2) अणु
			temp = acpi_gbl_db_console_debug_level;
			acpi_gbl_db_console_debug_level =
			    म_से_अदीर्घ(acpi_gbl_db_args[1], शून्य, 16);
			acpi_os_म_लिखो
			    ("Debug Level for console output was %8.8X, now %8.8X\n",
			     temp, acpi_gbl_db_console_debug_level);
		पूर्ण अन्यथा अणु
			temp = acpi_gbl_db_debug_level;
			acpi_gbl_db_debug_level =
			    म_से_अदीर्घ(acpi_gbl_db_args[1], शून्य, 16);
			acpi_os_म_लिखो
			    ("Debug Level for file output was %8.8X, now %8.8X\n",
			     temp, acpi_gbl_db_debug_level);
		पूर्ण
		अवरोध;

	हाल CMD_LIST:

#अगर_घोषित ACPI_DISASSEMBLER
		acpi_db_disassemble_aml(acpi_gbl_db_args[1], op);
#अन्यथा
		acpi_os_म_लिखो
		    ("The AML Disassembler is not configured/present\n");
#पूर्ण_अगर
		अवरोध;

	हाल CMD_LOCKS:

		acpi_db_display_locks();
		अवरोध;

	हाल CMD_LOCALS:

		acpi_db_display_locals();
		अवरोध;

	हाल CMD_METHODS:

		status = acpi_db_display_objects("METHOD", acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_NAMESPACE:

		acpi_db_dump_namespace(acpi_gbl_db_args[1],
				       acpi_gbl_db_args[2]);
		अवरोध;

	हाल CMD_NOTIFY:

		temp = म_से_अदीर्घ(acpi_gbl_db_args[2], शून्य, 0);
		acpi_db_send_notअगरy(acpi_gbl_db_args[1], temp);
		अवरोध;

	हाल CMD_OBJECTS:

		acpi_ut_strupr(acpi_gbl_db_args[1]);
		status =
		    acpi_db_display_objects(acpi_gbl_db_args[1],
					    acpi_gbl_db_args[2]);
		अवरोध;

	हाल CMD_OSI:

		acpi_db_display_पूर्णांकerfaces(acpi_gbl_db_args[1],
					   acpi_gbl_db_args[2]);
		अवरोध;

	हाल CMD_OWNER:

		acpi_db_dump_namespace_by_owner(acpi_gbl_db_args[1],
						acpi_gbl_db_args[2]);
		अवरोध;

	हाल CMD_PATHS:

		acpi_db_dump_namespace_paths();
		अवरोध;

	हाल CMD_PREFIX:

		acpi_db_set_scope(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_REFERENCES:

		acpi_db_find_references(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_RESOURCES:

		acpi_db_display_resources(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_RESULTS:

		acpi_db_display_results();
		अवरोध;

	हाल CMD_SET:

		acpi_db_set_method_data(acpi_gbl_db_args[1],
					acpi_gbl_db_args[2],
					acpi_gbl_db_args[3]);
		अवरोध;

	हाल CMD_STATS:

		status = acpi_db_display_statistics(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_STOP:

		वापस (AE_NOT_IMPLEMENTED);

	हाल CMD_TABLES:

		acpi_db_display_table_info(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_TEMPLATE:

		acpi_db_display_ढाँचा(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_TRACE:

		acpi_db_trace(acpi_gbl_db_args[1], acpi_gbl_db_args[2],
			      acpi_gbl_db_args[3]);
		अवरोध;

	हाल CMD_TREE:

		acpi_db_display_calling_tree();
		अवरोध;

	हाल CMD_TYPE:

		acpi_db_display_object_type(acpi_gbl_db_args[1]);
		अवरोध;

#अगर_घोषित ACPI_APPLICATION

		/* Hardware simulation commands. */

	हाल CMD_ENABLEACPI:
#अगर (!ACPI_REDUCED_HARDWARE)

		status = acpi_enable();
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("AcpiEnable failed (Status=%X)\n",
				       status);
			वापस (status);
		पूर्ण
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
		अवरोध;

	हाल CMD_EVENT:

		acpi_os_म_लिखो("Event command not implemented\n");
		अवरोध;

	हाल CMD_GPE:

		acpi_db_generate_gpe(acpi_gbl_db_args[1], acpi_gbl_db_args[2]);
		अवरोध;

	हाल CMD_GPES:

		acpi_db_display_gpes();
		अवरोध;

	हाल CMD_SCI:

		acpi_db_generate_sci();
		अवरोध;

	हाल CMD_SLEEP:

		status = acpi_db_sleep(acpi_gbl_db_args[1]);
		अवरोध;

		/* File I/O commands. */

	हाल CMD_CLOSE:

		acpi_db_बंद_debug_file();
		अवरोध;

	हाल CMD_LOAD:अणु
			काष्ठा acpi_new_table_desc *list_head = शून्य;

			status =
			    ac_get_all_tables_from_file(acpi_gbl_db_args[1],
							ACPI_GET_ALL_TABLES,
							&list_head);
			अगर (ACPI_SUCCESS(status)) अणु
				acpi_db_load_tables(list_head);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल CMD_OPEN:

		acpi_db_खोलो_debug_file(acpi_gbl_db_args[1]);
		अवरोध;

		/* User space commands. */

	हाल CMD_TERMINATE:

		acpi_db_set_output_destination(ACPI_DB_REसूचीECTABLE_OUTPUT);
		acpi_ut_subप्रणाली_shutकरोwn();

		/*
		 * TBD: [Reकाष्ठाure] Need some way to re-initialize without
		 * re-creating the semaphores!
		 */

		acpi_gbl_db_terminate_loop = TRUE;
		/*  acpi_initialize (शून्य); */
		अवरोध;

	हाल CMD_BACKGROUND:

		acpi_db_create_execution_thपढ़ो(acpi_gbl_db_args[1],
						&acpi_gbl_db_args[2],
						&acpi_gbl_db_arg_types[2]);
		अवरोध;

	हाल CMD_THREADS:

		acpi_db_create_execution_thपढ़ोs(acpi_gbl_db_args[1],
						 acpi_gbl_db_args[2],
						 acpi_gbl_db_args[3]);
		अवरोध;

		/* Debug test commands. */

	हाल CMD_PREDEFINED:

		acpi_db_check_predefined_names();
		अवरोध;

	हाल CMD_TEST:

		acpi_db_execute_test(acpi_gbl_db_args[1]);
		अवरोध;

	हाल CMD_UNLOAD:

		acpi_db_unload_acpi_table(acpi_gbl_db_args[1]);
		अवरोध;
#पूर्ण_अगर

	हाल CMD_EXIT:
	हाल CMD_QUIT:

		अगर (op) अणु
			acpi_os_म_लिखो("Method execution terminated\n");
			वापस (AE_CTRL_TERMINATE);
		पूर्ण

		अगर (!acpi_gbl_db_output_to_file) अणु
			acpi_dbg_level = ACPI_DEBUG_DEFAULT;
		पूर्ण
#अगर_घोषित ACPI_APPLICATION
		acpi_db_बंद_debug_file();
#पूर्ण_अगर
		acpi_gbl_db_terminate_loop = TRUE;
		वापस (AE_CTRL_TERMINATE);

	हाल CMD_NOT_FOUND:
	शेष:

		acpi_os_म_लिखो("%s: unknown command\n", acpi_gbl_db_args[0]);
		वापस (AE_CTRL_TRUE);
	पूर्ण

	अगर (ACPI_SUCCESS(status)) अणु
		status = AE_CTRL_TRUE;
	पूर्ण

	वापस (status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_execute_thपढ़ो
 *
 * PARAMETERS:  context         - Not used
 *
 * RETURN:      None
 *
 * DESCRIPTION: Debugger execute thपढ़ो. Waits क्रम a command line, then
 *              simply dispatches it.
 *
 ******************************************************************************/

व्योम ACPI_SYSTEM_XFACE acpi_db_execute_thपढ़ो(व्योम *context)
अणु

	(व्योम)acpi_db_user_commands();
	acpi_gbl_db_thपढ़ोs_terminated = TRUE;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_db_user_commands
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Command line execution क्रम the AML debugger. Commands are
 *              matched and dispatched here.
 *
 ******************************************************************************/

acpi_status acpi_db_user_commands(व्योम)
अणु
	acpi_status status = AE_OK;

	acpi_os_म_लिखो("\n");

	/* TBD: [Reकाष्ठाure] Need a separate command line buffer क्रम step mode */

	जबतक (!acpi_gbl_db_terminate_loop) अणु

		/* Wait the पढ़ोiness of the command */

		status = acpi_os_रुको_command_पढ़ोy();
		अगर (ACPI_FAILURE(status)) अणु
			अवरोध;
		पूर्ण

		/* Just call to the command line पूर्णांकerpreter */

		acpi_gbl_method_executing = FALSE;
		acpi_gbl_step_to_next_call = FALSE;

		(व्योम)acpi_db_command_dispatch(acpi_gbl_db_line_buf, शून्य,
					       शून्य);

		/* Notअगरy the completion of the command */

		status = acpi_os_notअगरy_command_complete();
		अगर (ACPI_FAILURE(status)) अणु
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ACPI_FAILURE(status) && status != AE_CTRL_TERMINATE) अणु
		ACPI_EXCEPTION((AE_INFO, status, "While parsing command line"));
	पूर्ण
	वापस (status);
पूर्ण
