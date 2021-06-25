<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utosi - Support क्रम the _OSI predefined control method
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utosi")

/******************************************************************************
 *
 * ACPICA policy क्रम new _OSI strings:
 *
 * It is the stated policy of ACPICA that new _OSI strings will be पूर्णांकegrated
 * पूर्णांकo this module as soon as possible after they are defined. It is strongly
 * recommended that all ACPICA hosts mirror this policy and पूर्णांकegrate any
 * changes to this module as soon as possible. There are several historical
 * reasons behind this policy:
 *
 * 1) New BIOSs tend to test only the हाल where the host responds TRUE to
 *    the latest version of Winकरोws, which would respond to the latest/newest
 *    _OSI string. Not responding TRUE to the latest version of Winकरोws will
 *    risk executing untested code paths throughout the DSDT and SSDTs.
 *
 * 2) If a new _OSI string is recognized only after a signअगरicant delay, this
 *    has the potential to cause problems on existing working machines because
 *    of the possibility that a new and dअगरferent path through the ASL code
 *    will be executed.
 *
 * 3) New _OSI strings are tending to come out about once per year. A delay
 *    in recognizing a new string क्रम a signअगरicant amount of समय risks the
 *    release of another string which only compounds the initial problem.
 *
 *****************************************************************************/
/*
 * Strings supported by the _OSI predefined control method (which is
 * implemented पूर्णांकernally within this module.)
 *
 * March 2009: Removed "Linux" as this host no दीर्घer wants to respond true
 * क्रम this string. Basically, the only safe OS strings are winकरोws-related
 * and in many or most हालs represent the only test path within the
 * BIOS-provided ASL code.
 *
 * The last element of each entry is used to track the newest version of
 * Winकरोws that the BIOS has requested.
 */
अटल काष्ठा acpi_पूर्णांकerface_info acpi_शेष_supported_पूर्णांकerfaces[] = अणु
	/* Operating System Venकरोr Strings */

	अणु"Windows 2000", शून्य, 0, ACPI_OSI_WIN_2000पूर्ण,	/* Winकरोws 2000 */
	अणु"Windows 2001", शून्य, 0, ACPI_OSI_WIN_XPपूर्ण,	/* Winकरोws XP */
	अणु"Windows 2001 SP1", शून्य, 0, ACPI_OSI_WIN_XP_SP1पूर्ण,	/* Winकरोws XP SP1 */
	अणु"Windows 2001.1", शून्य, 0, ACPI_OSI_WINSRV_2003पूर्ण,	/* Winकरोws Server 2003 */
	अणु"Windows 2001 SP2", शून्य, 0, ACPI_OSI_WIN_XP_SP2पूर्ण,	/* Winकरोws XP SP2 */
	अणु"Windows 2001.1 SP1", शून्य, 0, ACPI_OSI_WINSRV_2003_SP1पूर्ण,	/* Winकरोws Server 2003 SP1 - Added 03/2006 */
	अणु"Windows 2006", शून्य, 0, ACPI_OSI_WIN_VISTAपूर्ण,	/* Winकरोws vista - Added 03/2006 */
	अणु"Windows 2006.1", शून्य, 0, ACPI_OSI_WINSRV_2008पूर्ण,	/* Winकरोws Server 2008 - Added 09/2009 */
	अणु"Windows 2006 SP1", शून्य, 0, ACPI_OSI_WIN_VISTA_SP1पूर्ण,	/* Winकरोws Vista SP1 - Added 09/2009 */
	अणु"Windows 2006 SP2", शून्य, 0, ACPI_OSI_WIN_VISTA_SP2पूर्ण,	/* Winकरोws Vista SP2 - Added 09/2010 */
	अणु"Windows 2009", शून्य, 0, ACPI_OSI_WIN_7पूर्ण,	/* Winकरोws 7 and Server 2008 R2 - Added 09/2009 */
	अणु"Windows 2012", शून्य, 0, ACPI_OSI_WIN_8पूर्ण,	/* Winकरोws 8 and Server 2012 - Added 08/2012 */
	अणु"Windows 2013", शून्य, 0, ACPI_OSI_WIN_8_1पूर्ण,	/* Winकरोws 8.1 and Server 2012 R2 - Added 01/2014 */
	अणु"Windows 2015", शून्य, 0, ACPI_OSI_WIN_10पूर्ण,	/* Winकरोws 10 - Added 03/2015 */
	अणु"Windows 2016", शून्य, 0, ACPI_OSI_WIN_10_RS1पूर्ण,	/* Winकरोws 10 version 1607 - Added 12/2017 */
	अणु"Windows 2017", शून्य, 0, ACPI_OSI_WIN_10_RS2पूर्ण,	/* Winकरोws 10 version 1703 - Added 12/2017 */
	अणु"Windows 2017.2", शून्य, 0, ACPI_OSI_WIN_10_RS3पूर्ण,	/* Winकरोws 10 version 1709 - Added 02/2018 */
	अणु"Windows 2018", शून्य, 0, ACPI_OSI_WIN_10_RS4पूर्ण,	/* Winकरोws 10 version 1803 - Added 11/2018 */
	अणु"Windows 2018.2", शून्य, 0, ACPI_OSI_WIN_10_RS5पूर्ण,	/* Winकरोws 10 version 1809 - Added 11/2018 */
	अणु"Windows 2019", शून्य, 0, ACPI_OSI_WIN_10_19H1पूर्ण,	/* Winकरोws 10 version 1903 - Added 08/2019 */

	/* Feature Group Strings */

	अणु"Extended Address Space Descriptor", शून्य, ACPI_OSI_FEATURE, 0पूर्ण,

	/*
	 * All "optional" feature group strings (features that are implemented
	 * by the host) should be dynamically modअगरied to VALID by the host via
	 * acpi_install_पूर्णांकerface or acpi_update_पूर्णांकerfaces. Such optional feature
	 * group strings are set as INVALID by शेष here.
	 */

	अणु"Module Device", शून्य, ACPI_OSI_OPTIONAL_FEATURE, 0पूर्ण,
	अणु"Processor Device", शून्य, ACPI_OSI_OPTIONAL_FEATURE, 0पूर्ण,
	अणु"3.0 Thermal Model", शून्य, ACPI_OSI_OPTIONAL_FEATURE, 0पूर्ण,
	अणु"3.0 _SCP Extensions", शून्य, ACPI_OSI_OPTIONAL_FEATURE, 0पूर्ण,
	अणु"Processor Aggregator Device", शून्य, ACPI_OSI_OPTIONAL_FEATURE, 0पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_initialize_पूर्णांकerfaces
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the global _OSI supported पूर्णांकerfaces list
 *
 ******************************************************************************/

acpi_status acpi_ut_initialize_पूर्णांकerfaces(व्योम)
अणु
	acpi_status status;
	u32 i;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	acpi_gbl_supported_पूर्णांकerfaces = acpi_शेष_supported_पूर्णांकerfaces;

	/* Link the अटल list of supported पूर्णांकerfaces */

	क्रम (i = 0;
	     i < (ACPI_ARRAY_LENGTH(acpi_शेष_supported_पूर्णांकerfaces) - 1);
	     i++) अणु
		acpi_शेष_supported_पूर्णांकerfaces[i].next =
		    &acpi_शेष_supported_पूर्णांकerfaces[(acpi_size)i + 1];
	पूर्ण

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_पूर्णांकerface_terminate
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete all पूर्णांकerfaces in the global list. Sets
 *              acpi_gbl_supported_पूर्णांकerfaces to शून्य.
 *
 ******************************************************************************/

acpi_status acpi_ut_पूर्णांकerface_terminate(व्योम)
अणु
	acpi_status status;
	काष्ठा acpi_पूर्णांकerface_info *next_पूर्णांकerface;

	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	next_पूर्णांकerface = acpi_gbl_supported_पूर्णांकerfaces;
	जबतक (next_पूर्णांकerface) अणु
		acpi_gbl_supported_पूर्णांकerfaces = next_पूर्णांकerface->next;

		अगर (next_पूर्णांकerface->flags & ACPI_OSI_DYNAMIC) अणु

			/* Only पूर्णांकerfaces added at runसमय can be मुक्तd */

			ACPI_FREE(next_पूर्णांकerface->name);
			ACPI_FREE(next_पूर्णांकerface);
		पूर्ण अन्यथा अणु
			/* Interface is in अटल list. Reset it to invalid or valid. */

			अगर (next_पूर्णांकerface->flags & ACPI_OSI_DEFAULT_INVALID) अणु
				next_पूर्णांकerface->flags |= ACPI_OSI_INVALID;
			पूर्ण अन्यथा अणु
				next_पूर्णांकerface->flags &= ~ACPI_OSI_INVALID;
			पूर्ण
		पूर्ण

		next_पूर्णांकerface = acpi_gbl_supported_पूर्णांकerfaces;
	पूर्ण

	acpi_os_release_mutex(acpi_gbl_osi_mutex);
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_install_पूर्णांकerface
 *
 * PARAMETERS:  पूर्णांकerface_name      - The पूर्णांकerface to install
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Install the पूर्णांकerface पूर्णांकo the global पूर्णांकerface list.
 *              Caller MUST hold acpi_gbl_osi_mutex
 *
 ******************************************************************************/

acpi_status acpi_ut_install_पूर्णांकerface(acpi_string पूर्णांकerface_name)
अणु
	काष्ठा acpi_पूर्णांकerface_info *पूर्णांकerface_info;

	/* Allocate info block and space क्रम the name string */

	पूर्णांकerface_info =
	    ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_पूर्णांकerface_info));
	अगर (!पूर्णांकerface_info) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	पूर्णांकerface_info->name = ACPI_ALLOCATE_ZEROED(म_माप(पूर्णांकerface_name) + 1);
	अगर (!पूर्णांकerface_info->name) अणु
		ACPI_FREE(पूर्णांकerface_info);
		वापस (AE_NO_MEMORY);
	पूर्ण

	/* Initialize new info and insert at the head of the global list */

	म_नकल(पूर्णांकerface_info->name, पूर्णांकerface_name);
	पूर्णांकerface_info->flags = ACPI_OSI_DYNAMIC;
	पूर्णांकerface_info->next = acpi_gbl_supported_पूर्णांकerfaces;

	acpi_gbl_supported_पूर्णांकerfaces = पूर्णांकerface_info;
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_हटाओ_पूर्णांकerface
 *
 * PARAMETERS:  पूर्णांकerface_name      - The पूर्णांकerface to हटाओ
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Remove the पूर्णांकerface from the global पूर्णांकerface list.
 *              Caller MUST hold acpi_gbl_osi_mutex
 *
 ******************************************************************************/

acpi_status acpi_ut_हटाओ_पूर्णांकerface(acpi_string पूर्णांकerface_name)
अणु
	काष्ठा acpi_पूर्णांकerface_info *previous_पूर्णांकerface;
	काष्ठा acpi_पूर्णांकerface_info *next_पूर्णांकerface;

	previous_पूर्णांकerface = next_पूर्णांकerface = acpi_gbl_supported_पूर्णांकerfaces;
	जबतक (next_पूर्णांकerface) अणु
		अगर (!म_भेद(पूर्णांकerface_name, next_पूर्णांकerface->name)) अणु
			/*
			 * Found: name is in either the अटल list
			 * or was added at runसमय
			 */
			अगर (next_पूर्णांकerface->flags & ACPI_OSI_DYNAMIC) अणु

				/* Interface was added dynamically, हटाओ and मुक्त it */

				अगर (previous_पूर्णांकerface == next_पूर्णांकerface) अणु
					acpi_gbl_supported_पूर्णांकerfaces =
					    next_पूर्णांकerface->next;
				पूर्ण अन्यथा अणु
					previous_पूर्णांकerface->next =
					    next_पूर्णांकerface->next;
				पूर्ण

				ACPI_FREE(next_पूर्णांकerface->name);
				ACPI_FREE(next_पूर्णांकerface);
			पूर्ण अन्यथा अणु
				/*
				 * Interface is in अटल list. If marked invalid, then
				 * it करोes not actually exist. Else, mark it invalid.
				 */
				अगर (next_पूर्णांकerface->flags & ACPI_OSI_INVALID) अणु
					वापस (AE_NOT_EXIST);
				पूर्ण

				next_पूर्णांकerface->flags |= ACPI_OSI_INVALID;
			पूर्ण

			वापस (AE_OK);
		पूर्ण

		previous_पूर्णांकerface = next_पूर्णांकerface;
		next_पूर्णांकerface = next_पूर्णांकerface->next;
	पूर्ण

	/* Interface was not found */

	वापस (AE_NOT_EXIST);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_update_पूर्णांकerfaces
 *
 * PARAMETERS:  action              - Actions to be perक्रमmed during the
 *                                    update
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Update _OSI पूर्णांकerface strings, disabling or enabling OS venकरोr
 *              strings or/and feature group strings.
 *              Caller MUST hold acpi_gbl_osi_mutex
 *
 ******************************************************************************/

acpi_status acpi_ut_update_पूर्णांकerfaces(u8 action)
अणु
	काष्ठा acpi_पूर्णांकerface_info *next_पूर्णांकerface;

	next_पूर्णांकerface = acpi_gbl_supported_पूर्णांकerfaces;
	जबतक (next_पूर्णांकerface) अणु
		अगर (((next_पूर्णांकerface->flags & ACPI_OSI_FEATURE) &&
		     (action & ACPI_FEATURE_STRINGS)) ||
		    (!(next_पूर्णांकerface->flags & ACPI_OSI_FEATURE) &&
		     (action & ACPI_VENDOR_STRINGS))) अणु
			अगर (action & ACPI_DISABLE_INTERFACES) अणु

				/* Mark the पूर्णांकerfaces as invalid */

				next_पूर्णांकerface->flags |= ACPI_OSI_INVALID;
			पूर्ण अन्यथा अणु
				/* Mark the पूर्णांकerfaces as valid */

				next_पूर्णांकerface->flags &= ~ACPI_OSI_INVALID;
			पूर्ण
		पूर्ण

		next_पूर्णांकerface = next_पूर्णांकerface->next;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_पूर्णांकerface
 *
 * PARAMETERS:  पूर्णांकerface_name      - The पूर्णांकerface to find
 *
 * RETURN:      काष्ठा acpi_पूर्णांकerface_info अगर found. शून्य अगर not found.
 *
 * DESCRIPTION: Search क्रम the specअगरied पूर्णांकerface name in the global list.
 *              Caller MUST hold acpi_gbl_osi_mutex
 *
 ******************************************************************************/

काष्ठा acpi_पूर्णांकerface_info *acpi_ut_get_पूर्णांकerface(acpi_string पूर्णांकerface_name)
अणु
	काष्ठा acpi_पूर्णांकerface_info *next_पूर्णांकerface;

	next_पूर्णांकerface = acpi_gbl_supported_पूर्णांकerfaces;
	जबतक (next_पूर्णांकerface) अणु
		अगर (!म_भेद(पूर्णांकerface_name, next_पूर्णांकerface->name)) अणु
			वापस (next_पूर्णांकerface);
		पूर्ण

		next_पूर्णांकerface = next_पूर्णांकerface->next;
	पूर्ण

	वापस (शून्य);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_osi_implementation
 *
 * PARAMETERS:  walk_state          - Current walk state
 *
 * RETURN:      Status
 *              Integer: TRUE (0) अगर input string is matched
 *                       FALSE (-1) अगर string is not matched
 *
 * DESCRIPTION: Implementation of the _OSI predefined control method. When
 *              an invocation of _OSI is encountered in the प्रणाली AML,
 *              control is transferred to this function.
 *
 * (August 2016)
 * Note:  _OSI is now defined to वापस "Ones" to indicate a match, क्रम
 * compatibility with other ACPI implementations. On a 32-bit DSDT, Ones
 * is 0xFFFFFFFF. On a 64-bit DSDT, Ones is 0xFFFFFFFFFFFFFFFF
 * (ACPI_UINT64_MAX).
 *
 * This function always वापसs ACPI_UINT64_MAX क्रम TRUE, and later code
 * will truncate this to 32 bits अगर necessary.
 *
 ******************************************************************************/

acpi_status acpi_ut_osi_implementation(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_opeअक्रम_object *string_desc;
	जोड़ acpi_opeअक्रम_object *वापस_desc;
	काष्ठा acpi_पूर्णांकerface_info *पूर्णांकerface_info;
	acpi_पूर्णांकerface_handler पूर्णांकerface_handler;
	acpi_status status;
	u64 वापस_value;

	ACPI_FUNCTION_TRACE(ut_osi_implementation);

	/* Validate the string input argument (from the AML caller) */

	string_desc = walk_state->arguments[0].object;
	अगर (!string_desc || (string_desc->common.type != ACPI_TYPE_STRING)) अणु
		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	/* Create a वापस object */

	वापस_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_INTEGER);
	अगर (!वापस_desc) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Default वापस value is 0, NOT SUPPORTED */

	वापस_value = 0;
	status = acpi_os_acquire_mutex(acpi_gbl_osi_mutex, ACPI_WAIT_FOREVER);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_ut_हटाओ_reference(वापस_desc);
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Lookup the पूर्णांकerface in the global _OSI list */

	पूर्णांकerface_info = acpi_ut_get_पूर्णांकerface(string_desc->string.poपूर्णांकer);
	अगर (पूर्णांकerface_info && !(पूर्णांकerface_info->flags & ACPI_OSI_INVALID)) अणु
		/*
		 * The पूर्णांकerface is supported.
		 * Update the osi_data अगर necessary. We keep track of the latest
		 * version of Winकरोws that has been requested by the BIOS.
		 */
		अगर (पूर्णांकerface_info->value > acpi_gbl_osi_data) अणु
			acpi_gbl_osi_data = पूर्णांकerface_info->value;
		पूर्ण

		वापस_value = ACPI_UINT64_MAX;
	पूर्ण

	acpi_os_release_mutex(acpi_gbl_osi_mutex);

	/*
	 * Invoke an optional _OSI पूर्णांकerface handler. The host OS may wish
	 * to करो some पूर्णांकerface-specअगरic handling. For example, warn about
	 * certain पूर्णांकerfaces or override the true/false support value.
	 */
	पूर्णांकerface_handler = acpi_gbl_पूर्णांकerface_handler;
	अगर (पूर्णांकerface_handler) अणु
		अगर (पूर्णांकerface_handler
		    (string_desc->string.poपूर्णांकer, (u32)वापस_value)) अणु
			वापस_value = ACPI_UINT64_MAX;
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INFO,
			      "ACPI: BIOS _OSI(\"%s\") is %ssupported\n",
			      string_desc->string.poपूर्णांकer,
			      वापस_value == 0 ? "not " : ""));

	/* Complete the वापस object */

	वापस_desc->पूर्णांकeger.value = वापस_value;
	walk_state->वापस_desc = वापस_desc;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
