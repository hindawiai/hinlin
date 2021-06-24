<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: osunixxf - UNIX OSL पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * These पूर्णांकerfaces are required in order to compile the ASL compiler and the
 * various ACPICA tools under Linux or other Unix-like प्रणाली.
 */
#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acparser.h"
#समावेश "acdebug.h"

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <मानकतर्क.स>
#समावेश <unistd.h>
#समावेश <sys/समय.स>
#समावेश <semaphore.h>
#समावेश <pthपढ़ो.h>
#समावेश <त्रुटिसं.स>

#घोषणा _COMPONENT          ACPI_OS_SERVICES
ACPI_MODULE_NAME("osunixxf")

/* Upcalls to acpi_exec */
व्योम
ae_table_override(काष्ठा acpi_table_header *existing_table,
		  काष्ठा acpi_table_header **new_table);

प्रकार व्योम *(*PTHREAD_CALLBACK) (व्योम *);

/* Buffer used by acpi_os_भ_लिखो */

#घोषणा ACPI_VPRINTF_BUFFER_SIZE    512
#घोषणा _ASCII_NEWLINE              '\n'

/* Terminal support क्रम acpi_exec only */

#अगर_घोषित ACPI_EXEC_APP
#समावेश <termios.h>

काष्ठा termios original_term_attributes;
पूर्णांक term_attributes_were_set = 0;

acpi_status acpi_ut_पढ़ो_line(अक्षर *buffer, u32 buffer_length, u32 *bytes_पढ़ो);

अटल व्योम os_enter_line_edit_mode(व्योम);

अटल व्योम os_निकास_line_edit_mode(व्योम);

/******************************************************************************
 *
 * FUNCTION:    os_enter_line_edit_mode, os_निकास_line_edit_mode
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Enter/Exit the raw अक्षरacter input mode क्रम the terminal.
 *
 * Interactive line-editing support क्रम the AML debugger. Used with the
 * common/acgetline module.
 *
 * पढ़ोline() is not used because of non-portability. It is not available
 * on all प्रणालीs, and अगर it is, often the package must be manually installed.
 *
 * Thereक्रमe, we use the POSIX tcgetattr/tcsetattr and करो the minimal line
 * editing that we need in acpi_os_get_line.
 *
 * If the POSIX tcgetattr/tcsetattr पूर्णांकerfaces are unavailable, these
 * calls will also work:
 *     For os_enter_line_edit_mode: प्रणाली ("stty cbreak -echo")
 *     For os_निकास_line_edit_mode: प्रणाली ("stty cooked echo")
 *
 *****************************************************************************/

अटल व्योम os_enter_line_edit_mode(व्योम)
अणु
	काष्ठा termios local_term_attributes;

	term_attributes_were_set = 0;

	/* STDIN must be a terminal */

	अगर (!isatty(STDIN_खाताNO)) अणु
		वापस;
	पूर्ण

	/* Get and keep the original attributes */

	अगर (tcgetattr(STDIN_खाताNO, &original_term_attributes)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not get terminal attributes!\n");
		वापस;
	पूर्ण

	/* Set the new attributes to enable raw अक्षरacter input */

	स_नकल(&local_term_attributes, &original_term_attributes,
	       माप(काष्ठा termios));

	local_term_attributes.c_lflag &= ~(ICANON | ECHO);
	local_term_attributes.c_cc[VMIN] = 1;
	local_term_attributes.c_cc[VTIME] = 0;

	अगर (tcsetattr(STDIN_खाताNO, TCSANOW, &local_term_attributes)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not set terminal attributes!\n");
		वापस;
	पूर्ण

	term_attributes_were_set = 1;
पूर्ण

अटल व्योम os_निकास_line_edit_mode(व्योम)
अणु

	अगर (!term_attributes_were_set) अणु
		वापस;
	पूर्ण

	/* Set terminal attributes back to the original values */

	अगर (tcsetattr(STDIN_खाताNO, TCSANOW, &original_term_attributes)) अणु
		ख_लिखो(मानक_त्रुटि, "Could not restore terminal attributes!\n");
	पूर्ण
पूर्ण

#अन्यथा

/* These functions are not needed क्रम other ACPICA utilities */

#घोषणा os_enter_line_edit_mode()
#घोषणा os_निकास_line_edit_mode()
#पूर्ण_अगर

/******************************************************************************
 *
 * FUNCTION:    acpi_os_initialize, acpi_os_terminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize and terminate this module.
 *
 *****************************************************************************/

acpi_status acpi_os_initialize(व्योम)
अणु
	acpi_status status;

	acpi_gbl_output_file = मानक_निकास;

	os_enter_line_edit_mode();

	status = acpi_os_create_lock(&acpi_gbl_prपूर्णांक_lock);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	वापस (AE_OK);
पूर्ण

acpi_status acpi_os_terminate(व्योम)
अणु

	os_निकास_line_edit_mode();
	वापस (AE_OK);
पूर्ण

#अगर_अघोषित ACPI_USE_NATIVE_RSDP_POINTER
/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_root_poपूर्णांकer
 *
 * PARAMETERS:  None
 *
 * RETURN:      RSDP physical address
 *
 * DESCRIPTION: Gets the ACPI root poपूर्णांकer (RSDP)
 *
 *****************************************************************************/

acpi_physical_address acpi_os_get_root_poपूर्णांकer(व्योम)
अणु

	वापस (0);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 *
 * FUNCTION:    acpi_os_predefined_override
 *
 * PARAMETERS:  init_val            - Initial value of the predefined object
 *              new_val             - The new value क्रम the object
 *
 * RETURN:      Status, poपूर्णांकer to value. Null poपूर्णांकer वापसed अगर not
 *              overriding.
 *
 * DESCRIPTION: Allow the OS to override predefined names
 *
 *****************************************************************************/

acpi_status
acpi_os_predefined_override(स्थिर काष्ठा acpi_predefined_names *init_val,
			    acpi_string *new_val)
अणु

	अगर (!init_val || !new_val) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	*new_val = शून्य;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_table_override
 *
 * PARAMETERS:  existing_table      - Header of current table (probably
 *                                    firmware)
 *              new_table           - Where an entire new table is वापसed.
 *
 * RETURN:      Status, poपूर्णांकer to new table. Null poपूर्णांकer वापसed अगर no
 *              table is available to override
 *
 * DESCRIPTION: Return a dअगरferent version of a table अगर one is available
 *
 *****************************************************************************/

acpi_status
acpi_os_table_override(काष्ठा acpi_table_header *existing_table,
		       काष्ठा acpi_table_header **new_table)
अणु

	अगर (!existing_table || !new_table) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	*new_table = शून्य;

#अगर_घोषित ACPI_EXEC_APP

	ae_table_override(existing_table, new_table);
	वापस (AE_OK);
#अन्यथा

	वापस (AE_NO_ACPI_TABLES);
#पूर्ण_अगर
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_physical_table_override
 *
 * PARAMETERS:  existing_table      - Header of current table (probably firmware)
 *              new_address         - Where new table address is वापसed
 *                                    (Physical address)
 *              new_table_length    - Where new table length is वापसed
 *
 * RETURN:      Status, address/length of new table. Null poपूर्णांकer वापसed
 *              अगर no table is available to override.
 *
 * DESCRIPTION: Returns AE_SUPPORT, function not used in user space.
 *
 *****************************************************************************/

acpi_status
acpi_os_physical_table_override(काष्ठा acpi_table_header *existing_table,
				acpi_physical_address *new_address,
				u32 *new_table_length)
अणु

	वापस (AE_SUPPORT);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_enter_sleep
 *
 * PARAMETERS:  sleep_state         - Which sleep state to enter
 *              rega_value          - Register A value
 *              regb_value          - Register B value
 *
 * RETURN:      Status
 *
 * DESCRIPTION: A hook beक्रमe writing sleep रेजिस्टरs to enter the sleep
 *              state. Return AE_CTRL_TERMINATE to skip further sleep रेजिस्टर
 *              ग_लिखोs.
 *
 *****************************************************************************/

acpi_status acpi_os_enter_sleep(u8 sleep_state, u32 rega_value, u32 regb_value)
अणु

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_redirect_output
 *
 * PARAMETERS:  destination         - An खोलो file handle/poपूर्णांकer
 *
 * RETURN:      None
 *
 * DESCRIPTION: Causes redirect of acpi_os_म_लिखो and acpi_os_भ_लिखो
 *
 *****************************************************************************/

व्योम acpi_os_redirect_output(व्योम *destination)
अणु

	acpi_gbl_output_file = destination;
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_म_लिखो
 *
 * PARAMETERS:  fmt, ...            - Standard म_लिखो क्रमmat
 *
 * RETURN:      None
 *
 * DESCRIPTION: Formatted output. Note: very similar to acpi_os_भ_लिखो
 *              (perक्रमmance), changes should be tracked in both functions.
 *
 *****************************************************************************/

व्योम ACPI_INTERNAL_VAR_XFACE acpi_os_म_लिखो(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;
	u8 flags;

	flags = acpi_gbl_db_output_flags;
	अगर (flags & ACPI_DB_REसूचीECTABLE_OUTPUT) अणु

		/* Output is directable to either a file (अगर खोलो) or the console */

		अगर (acpi_gbl_debug_file) अणु

			/* Output file is खोलो, send the output there */

			बहु_शुरू(args, fmt);
			भख_लिखो(acpi_gbl_debug_file, fmt, args);
			बहु_पूर्ण(args);
		पूर्ण अन्यथा अणु
			/* No redirection, send output to console (once only!) */

			flags |= ACPI_DB_CONSOLE_OUTPUT;
		पूर्ण
	पूर्ण

	अगर (flags & ACPI_DB_CONSOLE_OUTPUT) अणु
		बहु_शुरू(args, fmt);
		भख_लिखो(acpi_gbl_output_file, fmt, args);
		बहु_पूर्ण(args);
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_भ_लिखो
 *
 * PARAMETERS:  fmt                 - Standard म_लिखो क्रमmat
 *              args                - Argument list
 *
 * RETURN:      None
 *
 * DESCRIPTION: Formatted output with argument list poपूर्णांकer. Note: very
 *              similar to acpi_os_म_लिखो, changes should be tracked in both
 *              functions.
 *
 *****************************************************************************/

व्योम acpi_os_भ_लिखो(स्थिर अक्षर *fmt, बहु_सूची args)
अणु
	u8 flags;
	अक्षर buffer[ACPI_VPRINTF_BUFFER_SIZE];

	/*
	 * We build the output string in a local buffer because we may be
	 * outputting the buffer twice. Using भख_लिखो is problematic because
	 * some implementations modअगरy the args poपूर्णांकer/काष्ठाure during
	 * execution. Thus, we use the local buffer क्रम portability.
	 *
	 * Note: Since this module is पूर्णांकended क्रम use by the various ACPICA
	 * utilities/applications, we can safely declare the buffer on the stack.
	 * Also, This function is used क्रम relatively small error messages only.
	 */
	vsnम_लिखो(buffer, ACPI_VPRINTF_BUFFER_SIZE, fmt, args);

	flags = acpi_gbl_db_output_flags;
	अगर (flags & ACPI_DB_REसूचीECTABLE_OUTPUT) अणु

		/* Output is directable to either a file (अगर खोलो) or the console */

		अगर (acpi_gbl_debug_file) अणु

			/* Output file is खोलो, send the output there */

			ख_माला_दो(buffer, acpi_gbl_debug_file);
		पूर्ण अन्यथा अणु
			/* No redirection, send output to console (once only!) */

			flags |= ACPI_DB_CONSOLE_OUTPUT;
		पूर्ण
	पूर्ण

	अगर (flags & ACPI_DB_CONSOLE_OUTPUT) अणु
		ख_माला_दो(buffer, acpi_gbl_output_file);
	पूर्ण
पूर्ण

#अगर_अघोषित ACPI_EXEC_APP
/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_line
 *
 * PARAMETERS:  buffer              - Where to वापस the command line
 *              buffer_length       - Maximum length of Buffer
 *              bytes_पढ़ो          - Where the actual byte count is वापसed
 *
 * RETURN:      Status and actual bytes पढ़ो
 *
 * DESCRIPTION: Get the next input line from the terminal. NOTE: For the
 *              acpi_exec utility, we use the acgetline module instead to
 *              provide line-editing and history support.
 *
 *****************************************************************************/

acpi_status acpi_os_get_line(अक्षर *buffer, u32 buffer_length, u32 *bytes_पढ़ो)
अणु
	पूर्णांक input_अक्षर;
	u32 end_of_line;

	/* Standard acpi_os_get_line क्रम all utilities except acpi_exec */

	क्रम (end_of_line = 0;; end_of_line++) अणु
		अगर (end_of_line >= buffer_length) अणु
			वापस (AE_BUFFER_OVERFLOW);
		पूर्ण

		अगर ((input_अक्षर = अक्षर_लो()) == खातापूर्ण) अणु
			वापस (AE_ERROR);
		पूर्ण

		अगर (!input_अक्षर || input_अक्षर == _ASCII_NEWLINE) अणु
			अवरोध;
		पूर्ण

		buffer[end_of_line] = (अक्षर)input_अक्षर;
	पूर्ण

	/* Null terminate the buffer */

	buffer[end_of_line] = 0;

	/* Return the number of bytes in the string */

	अगर (bytes_पढ़ो) अणु
		*bytes_पढ़ो = end_of_line;
	पूर्ण

	वापस (AE_OK);
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ACPI_USE_NATIVE_MEMORY_MAPPING
/******************************************************************************
 *
 * FUNCTION:    acpi_os_map_memory
 *
 * PARAMETERS:  where               - Physical address of memory to be mapped
 *              length              - How much memory to map
 *
 * RETURN:      Poपूर्णांकer to mapped memory. Null on error.
 *
 * DESCRIPTION: Map physical memory पूर्णांकo caller's address space
 *
 *****************************************************************************/

व्योम *acpi_os_map_memory(acpi_physical_address where, acpi_size length)
अणु

	वापस (ACPI_TO_POINTER((acpi_size)where));
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_unmap_memory
 *
 * PARAMETERS:  where               - Logical address of memory to be unmapped
 *              length              - How much memory to unmap
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Delete a previously created mapping. Where and Length must
 *              correspond to a previous mapping exactly.
 *
 *****************************************************************************/

व्योम acpi_os_unmap_memory(व्योम *where, acpi_size length)
अणु

	वापस;
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 *
 * FUNCTION:    acpi_os_allocate
 *
 * PARAMETERS:  size                - Amount to allocate, in bytes
 *
 * RETURN:      Poपूर्णांकer to the new allocation. Null on error.
 *
 * DESCRIPTION: Allocate memory. Algorithm is dependent on the OS.
 *
 *****************************************************************************/

व्योम *acpi_os_allocate(acpi_size size)
अणु
	व्योम *mem;

	mem = (व्योम *)दो_स्मृति((माप_प्रकार) size);
	वापस (mem);
पूर्ण

#अगर_घोषित USE_NATIVE_ALLOCATE_ZEROED
/******************************************************************************
 *
 * FUNCTION:    acpi_os_allocate_zeroed
 *
 * PARAMETERS:  size                - Amount to allocate, in bytes
 *
 * RETURN:      Poपूर्णांकer to the new allocation. Null on error.
 *
 * DESCRIPTION: Allocate and zero memory. Algorithm is dependent on the OS.
 *
 *****************************************************************************/

व्योम *acpi_os_allocate_zeroed(acpi_size size)
अणु
	व्योम *mem;

	mem = (व्योम *)सुस्मृति(1, (माप_प्रकार) size);
	वापस (mem);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 *
 * FUNCTION:    acpi_os_मुक्त
 *
 * PARAMETERS:  mem                 - Poपूर्णांकer to previously allocated memory
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Free memory allocated via acpi_os_allocate
 *
 *****************************************************************************/

व्योम acpi_os_मुक्त(व्योम *mem)
अणु

	मुक्त(mem);
पूर्ण

#अगर_घोषित ACPI_SINGLE_THREADED
/******************************************************************************
 *
 * FUNCTION:    Semaphore stub functions
 *
 * DESCRIPTION: Stub functions used क्रम single-thपढ़ो applications that करो
 *              not require semaphore synchronization. Full implementations
 *              of these functions appear after the stubs.
 *
 *****************************************************************************/

acpi_status
acpi_os_create_semaphore(u32 max_units,
			 u32 initial_units, acpi_handle *out_handle)
अणु
	*out_handle = (acpi_handle)1;
	वापस (AE_OK);
पूर्ण

acpi_status acpi_os_delete_semaphore(acpi_handle handle)
अणु
	वापस (AE_OK);
पूर्ण

acpi_status acpi_os_रुको_semaphore(acpi_handle handle, u32 units, u16 समयout)
अणु
	वापस (AE_OK);
पूर्ण

acpi_status acpi_os_संकेत_semaphore(acpi_handle handle, u32 units)
अणु
	वापस (AE_OK);
पूर्ण

#अन्यथा
/******************************************************************************
 *
 * FUNCTION:    acpi_os_create_semaphore
 *
 * PARAMETERS:  initial_units       - Units to be asचिन्हित to the new semaphore
 *              out_handle          - Where a handle will be वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Create an OS semaphore
 *
 *****************************************************************************/

acpi_status
acpi_os_create_semaphore(u32 max_units,
			 u32 initial_units, acpi_handle *out_handle)
अणु
	sem_t *sem;

	अगर (!out_handle) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण
#अगर_घोषित __APPLE__
	अणु
		अटल पूर्णांक semaphore_count = 0;
		अक्षर semaphore_name[32];

		snम_लिखो(semaphore_name, माप(semaphore_name), "acpi_sem_%d",
			 semaphore_count++);
		म_लिखो("%s\n", semaphore_name);
		sem =
		    sem_खोलो(semaphore_name, O_EXCL | O_CREAT, 0755,
			     initial_units);
		अगर (!sem) अणु
			वापस (AE_NO_MEMORY);
		पूर्ण
		sem_unlink(semaphore_name);	/* This just deletes the name */
	पूर्ण

#अन्यथा
	sem = acpi_os_allocate(माप(sem_t));
	अगर (!sem) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	अगर (sem_init(sem, 0, initial_units) == -1) अणु
		acpi_os_मुक्त(sem);
		वापस (AE_BAD_PARAMETER);
	पूर्ण
#पूर्ण_अगर

	*out_handle = (acpi_handle)sem;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_delete_semaphore
 *
 * PARAMETERS:  handle              - Handle वापसed by acpi_os_create_semaphore
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete an OS semaphore
 *
 *****************************************************************************/

acpi_status acpi_os_delete_semaphore(acpi_handle handle)
अणु
	sem_t *sem = (sem_t *) handle;

	अगर (!sem) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण
#अगर_घोषित __APPLE__
	अगर (sem_बंद(sem) == -1) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण
#अन्यथा
	अगर (sem_destroy(sem) == -1) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण
#पूर्ण_अगर

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_रुको_semaphore
 *
 * PARAMETERS:  handle              - Handle वापसed by acpi_os_create_semaphore
 *              units               - How many units to रुको क्रम
 *              msec_समयout        - How दीर्घ to रुको (milliseconds)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Wait क्रम units
 *
 *****************************************************************************/

acpi_status
acpi_os_रुको_semaphore(acpi_handle handle, u32 units, u16 msec_समयout)
अणु
	acpi_status status = AE_OK;
	sem_t *sem = (sem_t *) handle;
	पूर्णांक ret_val;
#अगर_अघोषित ACPI_USE_ALTERNATE_TIMEOUT
	काष्ठा बारpec समय;
#पूर्ण_अगर

	अगर (!sem) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	चयन (msec_समयout) अणु
		/*
		 * No Wait:
		 * --------
		 * A zero समयout value indicates that we shouldn't रुको - just
		 * acquire the semaphore अगर available otherwise वापस AE_TIME
		 * (a.k.a. 'would block').
		 */
	हाल 0:

		अगर (sem_tryरुको(sem) == -1) अणु
			status = (AE_TIME);
		पूर्ण
		अवरोध;

		/* Wait Indefinitely */

	हाल ACPI_WAIT_FOREVER:

		जबतक (((ret_val = sem_रुको(sem)) == -1) && (त्रुटि_सं == EINTR)) अणु
			जारी;	/* Restart अगर पूर्णांकerrupted */
		पूर्ण
		अगर (ret_val != 0) अणु
			status = (AE_TIME);
		पूर्ण
		अवरोध;

		/* Wait with msec_समयout */

	शेष:

#अगर_घोषित ACPI_USE_ALTERNATE_TIMEOUT
		/*
		 * Alternate समयout mechanism क्रम environments where
		 * sem_समयdरुको is not available or करोes not work properly.
		 */
		जबतक (msec_समयout) अणु
			अगर (sem_tryरुको(sem) == 0) अणु

				/* Got the semaphore */
				वापस (AE_OK);
			पूर्ण

			अगर (msec_समयout >= 10) अणु
				msec_समयout -= 10;
				usleep(10 * ACPI_USEC_PER_MSEC);	/* ten milliseconds */
			पूर्ण अन्यथा अणु
				msec_समयout--;
				usleep(ACPI_USEC_PER_MSEC);	/* one millisecond */
			पूर्ण
		पूर्ण
		status = (AE_TIME);
#अन्यथा
		/*
		 * The पूर्णांकerface to sem_समयdरुको is an असलolute समय, so we need to
		 * get the current समय, then add in the millisecond Timeout value.
		 */
		अगर (घड़ी_समय_लो(CLOCK_REALTIME, &समय) == -1) अणु
			लिखो_त्रुटि("clock_gettime");
			वापस (AE_TIME);
		पूर्ण

		समय.tv_sec += (msec_समयout / ACPI_MSEC_PER_SEC);
		समय.tv_nsec +=
		    ((msec_समयout % ACPI_MSEC_PER_SEC) * ACPI_NSEC_PER_MSEC);

		/* Handle nanosecond overflow (field must be less than one second) */

		अगर (समय.tv_nsec >= ACPI_NSEC_PER_SEC) अणु
			समय.tv_sec += (समय.tv_nsec / ACPI_NSEC_PER_SEC);
			समय.tv_nsec = (समय.tv_nsec % ACPI_NSEC_PER_SEC);
		पूर्ण

		जबतक (((ret_val = sem_समयdरुको(sem, &समय)) == -1)
		       && (त्रुटि_सं == EINTR)) अणु
			जारी;	/* Restart अगर पूर्णांकerrupted */

		पूर्ण

		अगर (ret_val != 0) अणु
			अगर (त्रुटि_सं != ETIMEDOUT) अणु
				लिखो_त्रुटि("sem_timedwait");
			पूर्ण
			status = (AE_TIME);
		पूर्ण
#पूर्ण_अगर
		अवरोध;
	पूर्ण

	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_संकेत_semaphore
 *
 * PARAMETERS:  handle              - Handle वापसed by acpi_os_create_semaphore
 *              units               - Number of units to send
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Send units
 *
 *****************************************************************************/

acpi_status acpi_os_संकेत_semaphore(acpi_handle handle, u32 units)
अणु
	sem_t *sem = (sem_t *) handle;

	अगर (!sem) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	अगर (sem_post(sem) == -1) अणु
		वापस (AE_LIMIT);
	पूर्ण

	वापस (AE_OK);
पूर्ण

#पूर्ण_अगर				/* ACPI_SINGLE_THREADED */

/******************************************************************************
 *
 * FUNCTION:    Spinlock पूर्णांकerfaces
 *
 * DESCRIPTION: Map these पूर्णांकerfaces to semaphore पूर्णांकerfaces
 *
 *****************************************************************************/

acpi_status acpi_os_create_lock(acpi_spinlock * out_handle)
अणु

	वापस (acpi_os_create_semaphore(1, 1, out_handle));
पूर्ण

व्योम acpi_os_delete_lock(acpi_spinlock handle)
अणु
	acpi_os_delete_semaphore(handle);
पूर्ण

acpi_cpu_flags acpi_os_acquire_lock(acpi_handle handle)
अणु
	acpi_os_रुको_semaphore(handle, 1, 0xFFFF);
	वापस (0);
पूर्ण

व्योम acpi_os_release_lock(acpi_spinlock handle, acpi_cpu_flags flags)
अणु
	acpi_os_संकेत_semaphore(handle, 1);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_install_पूर्णांकerrupt_handler
 *
 * PARAMETERS:  पूर्णांकerrupt_number    - Level handler should respond to.
 *              isr                 - Address of the ACPI पूर्णांकerrupt handler
 *              except_ptr          - Where status is वापसed
 *
 * RETURN:      Handle to the newly installed handler.
 *
 * DESCRIPTION: Install an पूर्णांकerrupt handler. Used to install the ACPI
 *              OS-independent handler.
 *
 *****************************************************************************/

u32
acpi_os_install_पूर्णांकerrupt_handler(u32 पूर्णांकerrupt_number,
				  acpi_osd_handler service_routine,
				  व्योम *context)
अणु

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_हटाओ_पूर्णांकerrupt_handler
 *
 * PARAMETERS:  handle              - Returned when handler was installed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Uninstalls an पूर्णांकerrupt handler.
 *
 *****************************************************************************/

acpi_status
acpi_os_हटाओ_पूर्णांकerrupt_handler(u32 पूर्णांकerrupt_number,
				 acpi_osd_handler service_routine)
अणु

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_stall
 *
 * PARAMETERS:  microseconds        - Time to sleep
 *
 * RETURN:      Blocks until sleep is completed.
 *
 * DESCRIPTION: Sleep at microsecond granularity
 *
 *****************************************************************************/

व्योम acpi_os_stall(u32 microseconds)
अणु

	अगर (microseconds) अणु
		usleep(microseconds);
	पूर्ण
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_sleep
 *
 * PARAMETERS:  milliseconds        - Time to sleep
 *
 * RETURN:      Blocks until sleep is completed.
 *
 * DESCRIPTION: Sleep at millisecond granularity
 *
 *****************************************************************************/

व्योम acpi_os_sleep(u64 milliseconds)
अणु

	/* Sleep क्रम whole seconds */

	sleep(milliseconds / ACPI_MSEC_PER_SEC);

	/*
	 * Sleep क्रम reमुख्यing microseconds.
	 * Arg to usleep() is in usecs and must be less than 1,000,000 (1 second).
	 */
	usleep((milliseconds % ACPI_MSEC_PER_SEC) * ACPI_USEC_PER_MSEC);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_समयr
 *
 * PARAMETERS:  None
 *
 * RETURN:      Current समय in 100 nanosecond units
 *
 * DESCRIPTION: Get the current प्रणाली समय
 *
 *****************************************************************************/

u64 acpi_os_get_समयr(व्योम)
अणु
	काष्ठा समयval समय;

	/* This समयr has sufficient resolution क्रम user-space application code */

	समय_लोofday(&समय, शून्य);

	/* (Seconds * 10^7 = 100ns(10^-7)) + (Microseconds(10^-6) * 10^1 = 100ns) */

	वापस (((u64)समय.tv_sec * ACPI_100NSEC_PER_SEC) +
		((u64)समय.tv_usec * ACPI_100NSEC_PER_USEC));
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_पढ़ो_pci_configuration
 *
 * PARAMETERS:  pci_id              - Seg/Bus/Dev
 *              pci_रेजिस्टर        - Device Register
 *              value               - Buffer where value is placed
 *              width               - Number of bits
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read data from PCI configuration space
 *
 *****************************************************************************/

acpi_status
acpi_os_पढ़ो_pci_configuration(काष्ठा acpi_pci_id *pci_id,
			       u32 pci_रेजिस्टर, u64 *value, u32 width)
अणु

	*value = 0;
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_ग_लिखो_pci_configuration
 *
 * PARAMETERS:  pci_id              - Seg/Bus/Dev
 *              pci_रेजिस्टर        - Device Register
 *              value               - Value to be written
 *              width               - Number of bits
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Write data to PCI configuration space
 *
 *****************************************************************************/

acpi_status
acpi_os_ग_लिखो_pci_configuration(काष्ठा acpi_pci_id *pci_id,
				u32 pci_रेजिस्टर, u64 value, u32 width)
अणु

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_पढ़ो_port
 *
 * PARAMETERS:  address             - Address of I/O port/रेजिस्टर to पढ़ो
 *              value               - Where value is placed
 *              width               - Number of bits
 *
 * RETURN:      Value पढ़ो from port
 *
 * DESCRIPTION: Read data from an I/O port or रेजिस्टर
 *
 *****************************************************************************/

acpi_status acpi_os_पढ़ो_port(acpi_io_address address, u32 *value, u32 width)
अणु

	चयन (width) अणु
	हाल 8:

		*value = 0xFF;
		अवरोध;

	हाल 16:

		*value = 0xFFFF;
		अवरोध;

	हाल 32:

		*value = 0xFFFFFFFF;
		अवरोध;

	शेष:

		वापस (AE_BAD_PARAMETER);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_ग_लिखो_port
 *
 * PARAMETERS:  address             - Address of I/O port/रेजिस्टर to ग_लिखो
 *              value               - Value to ग_लिखो
 *              width               - Number of bits
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write data to an I/O port or रेजिस्टर
 *
 *****************************************************************************/

acpi_status acpi_os_ग_लिखो_port(acpi_io_address address, u32 value, u32 width)
अणु

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_पढ़ो_memory
 *
 * PARAMETERS:  address             - Physical Memory Address to पढ़ो
 *              value               - Where value is placed
 *              width               - Number of bits (8,16,32, or 64)
 *
 * RETURN:      Value पढ़ो from physical memory address. Always वापसed
 *              as a 64-bit पूर्णांकeger, regardless of the पढ़ो width.
 *
 * DESCRIPTION: Read data from a physical memory address
 *
 *****************************************************************************/

acpi_status
acpi_os_पढ़ो_memory(acpi_physical_address address, u64 *value, u32 width)
अणु

	चयन (width) अणु
	हाल 8:
	हाल 16:
	हाल 32:
	हाल 64:

		*value = 0;
		अवरोध;

	शेष:

		वापस (AE_BAD_PARAMETER);
	पूर्ण
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_ग_लिखो_memory
 *
 * PARAMETERS:  address             - Physical Memory Address to ग_लिखो
 *              value               - Value to ग_लिखो
 *              width               - Number of bits (8,16,32, or 64)
 *
 * RETURN:      None
 *
 * DESCRIPTION: Write data to a physical memory address
 *
 *****************************************************************************/

acpi_status
acpi_os_ग_लिखो_memory(acpi_physical_address address, u64 value, u32 width)
अणु

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_पढ़ोable
 *
 * PARAMETERS:  poपूर्णांकer             - Area to be verअगरied
 *              length              - Size of area
 *
 * RETURN:      TRUE अगर पढ़ोable क्रम entire length
 *
 * DESCRIPTION: Verअगरy that a poपूर्णांकer is valid क्रम पढ़ोing
 *
 *****************************************************************************/

u8 acpi_os_पढ़ोable(व्योम *poपूर्णांकer, acpi_size length)
अणु

	वापस (TRUE);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_writable
 *
 * PARAMETERS:  poपूर्णांकer             - Area to be verअगरied
 *              length              - Size of area
 *
 * RETURN:      TRUE अगर writable क्रम entire length
 *
 * DESCRIPTION: Verअगरy that a poपूर्णांकer is valid क्रम writing
 *
 *****************************************************************************/

u8 acpi_os_writable(व्योम *poपूर्णांकer, acpi_size length)
अणु

	वापस (TRUE);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_संकेत
 *
 * PARAMETERS:  function            - ACPI A संकेत function code
 *              info                - Poपूर्णांकer to function-dependent काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Miscellaneous functions. Example implementation only.
 *
 *****************************************************************************/

acpi_status acpi_os_संकेत(u32 function, व्योम *info)
अणु

	चयन (function) अणु
	हाल ACPI_SIGNAL_FATAL:

		अवरोध;

	हाल ACPI_SIGNAL_BREAKPOINT:

		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/* Optional multi-thपढ़ो support */

#अगर_अघोषित ACPI_SINGLE_THREADED
/******************************************************************************
 *
 * FUNCTION:    acpi_os_get_thपढ़ो_id
 *
 * PARAMETERS:  None
 *
 * RETURN:      Id of the running thपढ़ो
 *
 * DESCRIPTION: Get the ID of the current (running) thपढ़ो
 *
 *****************************************************************************/

acpi_thपढ़ो_id acpi_os_get_thपढ़ो_id(व्योम)
अणु
	pthपढ़ो_t thपढ़ो;

	thपढ़ो = pthपढ़ो_self();
	वापस (ACPI_CAST_PTHREAD_T(thपढ़ो));
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_os_execute
 *
 * PARAMETERS:  type                - Type of execution
 *              function            - Address of the function to execute
 *              context             - Passed as a parameter to the function
 *
 * RETURN:      Status.
 *
 * DESCRIPTION: Execute a new thपढ़ो
 *
 *****************************************************************************/

acpi_status
acpi_os_execute(acpi_execute_type type,
		acpi_osd_exec_callback function, व्योम *context)
अणु
	pthपढ़ो_t thपढ़ो;
	पूर्णांक ret;

	ret =
	    pthपढ़ो_create(&thपढ़ो, शून्य, (PTHREAD_CALLBACK) function, context);
	अगर (ret) अणु
		acpi_os_म_लिखो("Create thread failed");
	पूर्ण
	वापस (0);
पूर्ण

#अन्यथा				/* ACPI_SINGLE_THREADED */
acpi_thपढ़ो_id acpi_os_get_thपढ़ो_id(व्योम)
अणु
	वापस (1);
पूर्ण

acpi_status
acpi_os_execute(acpi_execute_type type,
		acpi_osd_exec_callback function, व्योम *context)
अणु

	function(context);

	वापस (AE_OK);
पूर्ण

#पूर्ण_अगर				/* ACPI_SINGLE_THREADED */

/******************************************************************************
 *
 * FUNCTION:    acpi_os_रुको_events_complete
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Wait क्रम all asynchronous events to complete. This
 *              implementation करोes nothing.
 *
 *****************************************************************************/

व्योम acpi_os_रुको_events_complete(व्योम)
अणु
	वापस;
पूर्ण
