<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acpixf.h - External पूर्णांकerfaces to the ACPI subप्रणाली
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACXFACE_H__
#घोषणा __ACXFACE_H__

/* Current ACPICA subप्रणाली version in YYYYMMDD क्रमmat */

#घोषणा ACPI_CA_VERSION                 0x20210331

#समावेश <acpi/acconfig.h>
#समावेश <acpi/actypes.h>
#समावेश <acpi/actbl.h>
#समावेश <acpi/acbuffer.h>

/*****************************************************************************
 *
 * Macros used क्रम ACPICA globals and configuration
 *
 ****************************************************************************/

/*
 * Ensure that global variables are defined and initialized only once.
 *
 * The use of these macros allows क्रम a single list of globals (here)
 * in order to simplअगरy मुख्यtenance of the code.
 */
#अगर_घोषित DEFINE_ACPI_GLOBALS
#घोषणा ACPI_GLOBAL(type,name) \
	बाह्य type name; \
	type name

#घोषणा ACPI_INIT_GLOBAL(type,name,value) \
	type name=value

#अन्यथा
#अगर_अघोषित ACPI_GLOBAL
#घोषणा ACPI_GLOBAL(type,name) \
	बाह्य type name
#पूर्ण_अगर

#अगर_अघोषित ACPI_INIT_GLOBAL
#घोषणा ACPI_INIT_GLOBAL(type,name,value) \
	बाह्य type name
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * These macros configure the various ACPICA पूर्णांकerfaces. They are
 * useful क्रम generating stub अंतरभूत functions क्रम features that are
 * configured out of the current kernel or ACPICA application.
 */
#अगर_अघोषित ACPI_EXTERNAL_RETURN_STATUS
#घोषणा ACPI_EXTERNAL_RETURN_STATUS(prototype) \
	prototype;
#पूर्ण_अगर

#अगर_अघोषित ACPI_EXTERNAL_RETURN_OK
#घोषणा ACPI_EXTERNAL_RETURN_OK(prototype) \
	prototype;
#पूर्ण_अगर

#अगर_अघोषित ACPI_EXTERNAL_RETURN_VOID
#घोषणा ACPI_EXTERNAL_RETURN_VOID(prototype) \
	prototype;
#पूर्ण_अगर

#अगर_अघोषित ACPI_EXTERNAL_RETURN_UINT32
#घोषणा ACPI_EXTERNAL_RETURN_UINT32(prototype) \
	prototype;
#पूर्ण_अगर

#अगर_अघोषित ACPI_EXTERNAL_RETURN_PTR
#घोषणा ACPI_EXTERNAL_RETURN_PTR(prototype) \
	prototype;
#पूर्ण_अगर

/*****************************************************************************
 *
 * Public globals and runसमय configuration options
 *
 ****************************************************************************/

/*
 * Enable "slack mode" of the AML पूर्णांकerpreter?  Default is FALSE, and the
 * पूर्णांकerpreter strictly follows the ACPI specअगरication. Setting to TRUE
 * allows the पूर्णांकerpreter to ignore certain errors and/or bad AML स्थिरructs.
 *
 * Currently, these features are enabled by this flag:
 *
 * 1) Allow "implicit return" of last value in a control method
 * 2) Allow access beyond the end of an operation region
 * 3) Allow access to uninitialized locals/args (स्वतः-init to पूर्णांकeger 0)
 * 4) Allow ANY object type to be a source opeअक्रम क्रम the Store() चालक
 * 5) Allow unresolved references (invalid target name) in package objects
 * 6) Enable warning messages क्रम behavior that is not ACPI spec compliant
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_enable_पूर्णांकerpreter_slack, FALSE);

/*
 * Automatically serialize all methods that create named objects? Default
 * is TRUE, meaning that all non_serialized methods are scanned once at
 * table load समय to determine those that create named objects. Methods
 * that create named objects are marked Serialized in order to prevent
 * possible run-समय problems अगर they are entered by more than one thपढ़ो.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_स्वतः_serialize_methods, TRUE);

/*
 * Create the predefined _OSI method in the namespace? Default is TRUE
 * because ACPICA is fully compatible with other ACPI implementations.
 * Changing this will revert ACPICA (and machine ASL) to pre-OSI behavior.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_create_osi_method, TRUE);

/*
 * Optionally use शेष values क्रम the ACPI रेजिस्टर widths. Set this to
 * TRUE to use the शेषs, अगर an FADT contains incorrect widths/lengths.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_use_शेष_रेजिस्टर_widths, TRUE);

/*
 * Whether or not to validate (map) an entire table to verअगरy
 * checksum/duplication in early stage beक्रमe install. Set this to TRUE to
 * allow early table validation beक्रमe install it to the table manager.
 * Note that enabling this option causes errors to happen in some OSPMs
 * during early initialization stages. Default behavior is to allow such
 * validation.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_enable_table_validation, TRUE);

/*
 * Optionally enable output from the AML Debug Object.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_enable_aml_debug_object, FALSE);

/*
 * Optionally copy the entire DSDT to local memory (instead of simply
 * mapping it.) There are some BIOSs that corrupt or replace the original
 * DSDT, creating the need क्रम this option. Default is FALSE, करो not copy
 * the DSDT.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_copy_dsdt_locally, FALSE);

/*
 * Optionally ignore an XSDT अगर present and use the RSDT instead.
 * Although the ACPI specअगरication requires that an XSDT be used instead
 * of the RSDT, the XSDT has been found to be corrupt or ill-क्रमmed on
 * some machines. Default behavior is to use the XSDT अगर present.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_करो_not_use_xsdt, FALSE);

/*
 * Optionally use 32-bit FADT addresses अगर and when there is a conflict
 * (address mismatch) between the 32-bit and 64-bit versions of the
 * address. Although ACPICA adheres to the ACPI specअगरication which
 * requires the use of the corresponding 64-bit address अगर it is non-zero,
 * some machines have been found to have a corrupted non-zero 64-bit
 * address. Default is FALSE, करो not favor the 32-bit addresses.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_use32_bit_fadt_addresses, FALSE);

/*
 * Optionally use 32-bit FACS table addresses.
 * It is reported that some platक्रमms fail to resume from प्रणाली suspending
 * अगर 64-bit FACS table address is selected:
 * https://bugzilla.kernel.org/show_bug.cgi?id=74021
 * Default is TRUE, favor the 32-bit addresses.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_use32_bit_facs_addresses, TRUE);

/*
 * Optionally truncate I/O addresses to 16 bits. Provides compatibility
 * with other ACPI implementations. NOTE: During ACPICA initialization,
 * this value is set to TRUE अगर any Winकरोws OSI strings have been
 * requested by the BIOS.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_truncate_io_addresses, FALSE);

/*
 * Disable runसमय checking and repair of values वापसed by control methods.
 * Use only अगर the repair is causing a problem on a particular machine.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_disable_स्वतः_repair, FALSE);

/*
 * Optionally करो not install any SSDTs from the RSDT/XSDT during initialization.
 * This can be useful क्रम debugging ACPI problems on some machines.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_disable_ssdt_table_install, FALSE);

/*
 * Optionally enable runसमय namespace override.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_runसमय_namespace_override, TRUE);

/*
 * We keep track of the latest version of Winकरोws that has been requested by
 * the BIOS. ACPI 5.0.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_osi_data, 0);

/*
 * ACPI 5.0 पूर्णांकroduces the concept of a "reduced hardware platform", meaning
 * that the ACPI hardware is no दीर्घer required. A flag in the FADT indicates
 * a reduced HW machine, and that flag is duplicated here क्रम convenience.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_reduced_hardware, FALSE);

/*
 * Maximum समयout क्रम While() loop iterations beक्रमe क्रमced method पात.
 * This mechanism is पूर्णांकended to prevent infinite loops during पूर्णांकerpreter
 * execution within a host kernel.
 */
ACPI_INIT_GLOBAL(u32, acpi_gbl_max_loop_iterations, ACPI_MAX_LOOP_TIMEOUT);

/*
 * Optionally ignore AE_NOT_FOUND errors from named reference package elements
 * during DSDT/SSDT table loading. This reduces error "noise" in platक्रमms
 * whose firmware is carrying around a bunch of unused package objects that
 * refer to non-existent named objects. However, If the AML actually tries to
 * use such a package, the unresolved element(s) will be replaced with शून्य
 * elements.
 */
ACPI_INIT_GLOBAL(u8, acpi_gbl_ignore_package_resolution_errors, FALSE);

/*
 * This mechanism is used to trace a specअगरied AML method. The method is
 * traced each समय it is executed.
 */
ACPI_INIT_GLOBAL(u32, acpi_gbl_trace_flags, 0);
ACPI_INIT_GLOBAL(स्थिर अक्षर *, acpi_gbl_trace_method_name, शून्य);
ACPI_INIT_GLOBAL(u32, acpi_gbl_trace_dbg_level, ACPI_TRACE_LEVEL_DEFAULT);
ACPI_INIT_GLOBAL(u32, acpi_gbl_trace_dbg_layer, ACPI_TRACE_LAYER_DEFAULT);

/*
 * Runसमय configuration of debug output control masks. We want the debug
 * चयनes अटलally initialized so they are alपढ़ोy set when the debugger
 * is entered.
 */
ACPI_INIT_GLOBAL(u32, acpi_dbg_level, ACPI_DEBUG_DEFAULT);
ACPI_INIT_GLOBAL(u32, acpi_dbg_layer, 0);

/* Optionally enable समयr output with Debug Object output */

ACPI_INIT_GLOBAL(u8, acpi_gbl_display_debug_समयr, FALSE);

/*
 * Debugger command handshake globals. Host OSes need to access these
 * variables to implement their own command handshake mechanism.
 */
#अगर_घोषित ACPI_DEBUGGER
ACPI_INIT_GLOBAL(u8, acpi_gbl_method_executing, FALSE);
ACPI_GLOBAL(अक्षर, acpi_gbl_db_line_buf[ACPI_DB_LINE_BUFFER_SIZE]);
#पूर्ण_अगर

/*
 * Other miscellaneous globals
 */
ACPI_GLOBAL(काष्ठा acpi_table_fadt, acpi_gbl_FADT);
ACPI_GLOBAL(u32, acpi_current_gpe_count);
ACPI_GLOBAL(u8, acpi_gbl_प्रणाली_awake_and_running);

/*****************************************************************************
 *
 * ACPICA खुला पूर्णांकerface configuration.
 *
 * Interfaces that are configured out of the ACPICA build are replaced
 * by अंतरभूतd stubs by शेष.
 *
 ****************************************************************************/

/*
 * Hardware-reduced prototypes (शेष: Not hardware reduced).
 *
 * All ACPICA hardware-related पूर्णांकerfaces that use these macros will be
 * configured out of the ACPICA build अगर the ACPI_REDUCED_HARDWARE flag
 * is set to TRUE.
 *
 * Note: This अटल build option क्रम reduced hardware is पूर्णांकended to
 * reduce ACPICA code size अगर desired or necessary. However, even अगर this
 * option is not specअगरied, the runसमय behavior of ACPICA is dependent
 * on the actual FADT reduced hardware flag (HW_REDUCED_ACPI). If set,
 * the flag will enable similar behavior -- ACPICA will not attempt
 * to access any ACPI-relate hardware (SCI, GPEs, Fixed Events, etc.)
 */
#अगर (!ACPI_REDUCED_HARDWARE)
#घोषणा ACPI_HW_DEPENDENT_RETURN_STATUS(prototype) \
	ACPI_EXTERNAL_RETURN_STATUS(prototype)

#घोषणा ACPI_HW_DEPENDENT_RETURN_OK(prototype) \
	ACPI_EXTERNAL_RETURN_OK(prototype)

#घोषणा ACPI_HW_DEPENDENT_RETURN_UINT32(prototype) \
	ACPI_EXTERNAL_RETURN_UINT32(prototype)

#घोषणा ACPI_HW_DEPENDENT_RETURN_VOID(prototype) \
	ACPI_EXTERNAL_RETURN_VOID(prototype)

#अन्यथा
#घोषणा ACPI_HW_DEPENDENT_RETURN_STATUS(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(AE_NOT_CONFIGURED);पूर्ण

#घोषणा ACPI_HW_DEPENDENT_RETURN_OK(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(AE_OK);पूर्ण

#घोषणा ACPI_HW_DEPENDENT_RETURN_UINT32(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(0);पूर्ण

#घोषणा ACPI_HW_DEPENDENT_RETURN_VOID(prototype) \
	अटल ACPI_INLINE prototype अणुवापस;पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*
 * Error message prototypes (शेष: error messages enabled).
 *
 * All पूर्णांकerfaces related to error and warning messages
 * will be configured out of the ACPICA build अगर the
 * ACPI_NO_ERROR_MESSAGE flag is defined.
 */
#अगर_अघोषित ACPI_NO_ERROR_MESSAGES
#घोषणा ACPI_MSG_DEPENDENT_RETURN_VOID(prototype) \
	prototype;

#अन्यथा
#घोषणा ACPI_MSG_DEPENDENT_RETURN_VOID(prototype) \
	अटल ACPI_INLINE prototype अणुवापस;पूर्ण

#पूर्ण_अगर				/* ACPI_NO_ERROR_MESSAGES */

/*
 * Debugging output prototypes (शेष: no debug output).
 *
 * All पूर्णांकerfaces related to debug output messages
 * will be configured out of the ACPICA build unless the
 * ACPI_DEBUG_OUTPUT flag is defined.
 */
#अगर_घोषित ACPI_DEBUG_OUTPUT
#घोषणा ACPI_DBG_DEPENDENT_RETURN_VOID(prototype) \
	prototype;

#अन्यथा
#घोषणा ACPI_DBG_DEPENDENT_RETURN_VOID(prototype) \
	अटल ACPI_INLINE prototype अणुवापस;पूर्ण

#पूर्ण_अगर				/* ACPI_DEBUG_OUTPUT */

/*
 * Application prototypes
 *
 * All पूर्णांकerfaces used by application will be configured
 * out of the ACPICA build unless the ACPI_APPLICATION
 * flag is defined.
 */
#अगर_घोषित ACPI_APPLICATION
#घोषणा ACPI_APP_DEPENDENT_RETURN_VOID(prototype) \
	prototype;

#अन्यथा
#घोषणा ACPI_APP_DEPENDENT_RETURN_VOID(prototype) \
	अटल ACPI_INLINE prototype अणुवापस;पूर्ण

#पूर्ण_अगर				/* ACPI_APPLICATION */

/*
 * Debugger prototypes
 *
 * All पूर्णांकerfaces used by debugger will be configured
 * out of the ACPICA build unless the ACPI_DEBUGGER
 * flag is defined.
 */
#अगर_घोषित ACPI_DEBUGGER
#घोषणा ACPI_DBR_DEPENDENT_RETURN_OK(prototype) \
	ACPI_EXTERNAL_RETURN_OK(prototype)

#घोषणा ACPI_DBR_DEPENDENT_RETURN_VOID(prototype) \
	ACPI_EXTERNAL_RETURN_VOID(prototype)

#अन्यथा
#घोषणा ACPI_DBR_DEPENDENT_RETURN_OK(prototype) \
	अटल ACPI_INLINE prototype अणुवापस(AE_OK);पूर्ण

#घोषणा ACPI_DBR_DEPENDENT_RETURN_VOID(prototype) \
	अटल ACPI_INLINE prototype अणुवापस;पूर्ण

#पूर्ण_अगर				/* ACPI_DEBUGGER */

/*****************************************************************************
 *
 * ACPICA खुला पूर्णांकerface prototypes
 *
 ****************************************************************************/

/*
 * Initialization
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_initialize_tables(काष्ठा acpi_table_desc
						   *initial_storage,
						   u32 initial_table_count,
						   u8 allow_resize))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_initialize_subप्रणाली(व्योम))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_enable_subप्रणाली(u32 flags))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_initialize_objects(u32 flags))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			     acpi_terminate(व्योम))

/*
 * Miscellaneous global पूर्णांकerfaces
 */
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_enable(व्योम))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_disable(व्योम))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_subप्रणाली_status(व्योम))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_प्रणाली_info(काष्ठा acpi_buffer
						 *ret_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_statistics(काष्ठा acpi_statistics *stats))
ACPI_EXTERNAL_RETURN_PTR(स्थिर अक्षर
			  *acpi_क्रमmat_exception(acpi_status exception))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_purge_cached_objects(व्योम))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_install_पूर्णांकerface(acpi_string पूर्णांकerface_name))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_हटाओ_पूर्णांकerface(acpi_string पूर्णांकerface_name))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_update_पूर्णांकerfaces(u8 action))

ACPI_EXTERNAL_RETURN_UINT32(u32
			    acpi_check_address_range(acpi_adr_space_type
						     space_id,
						     acpi_physical_address
						     address, acpi_size length,
						     u8 warn))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_decode_pld_buffer(u8 *in_buffer,
						    acpi_size length,
						    काष्ठा acpi_pld_info
						    **वापस_buffer))

/*
 * ACPI table load/unload पूर्णांकerfaces
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_install_table(acpi_physical_address address,
					       u8 physical))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_load_table(काष्ठा acpi_table_header *table,
					    u32 *table_idx))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_unload_table(u32 table_index))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_unload_parent_table(acpi_handle object))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_load_tables(व्योम))

/*
 * ACPI table manipulation पूर्णांकerfaces
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_पुनः_स्मृतिate_root_table(व्योम))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status ACPI_INIT_FUNCTION
			    acpi_find_root_poपूर्णांकer(acpi_physical_address
						   *rsdp_address))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_table_header(acpi_string signature,
						   u32 instance,
						   काष्ठा acpi_table_header
						   *out_table_header))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_table(acpi_string signature, u32 instance,
					    काष्ठा acpi_table_header
					    **out_table))
ACPI_EXTERNAL_RETURN_VOID(व्योम acpi_put_table(काष्ठा acpi_table_header *table))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_table_by_index(u32 table_index,
						    काष्ठा acpi_table_header
						    **out_table))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_install_table_handler(acpi_table_handler
							handler, व्योम *context))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_हटाओ_table_handler(acpi_table_handler
						       handler))

/*
 * Namespace and name पूर्णांकerfaces
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_walk_namespace(acpi_object_type type,
						acpi_handle start_object,
						u32 max_depth,
						acpi_walk_callback
						descending_callback,
						acpi_walk_callback
						ascending_callback,
						व्योम *context,
						व्योम **वापस_value))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_devices(स्थिर अक्षर *HID,
					      acpi_walk_callback user_function,
					      व्योम *context,
					      व्योम **वापस_value))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_name(acpi_handle object, u32 name_type,
					   काष्ठा acpi_buffer *ret_path_ptr))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_handle(acpi_handle parent,
					     acpi_string pathname,
					     acpi_handle *ret_handle))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_attach_data(acpi_handle object,
					      acpi_object_handler handler,
					      व्योम *data))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_detach_data(acpi_handle object,
					      acpi_object_handler handler))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_data(acpi_handle object,
					   acpi_object_handler handler,
					   व्योम **data))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_debug_trace(स्थिर अक्षर *name, u32 debug_level,
					      u32 debug_layer, u32 flags))

/*
 * Object manipulation and क्रमागतeration
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_evaluate_object(acpi_handle object,
						 acpi_string pathname,
						 काष्ठा acpi_object_list
						 *parameter_objects,
						 काष्ठा acpi_buffer
						 *वापस_object_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_evaluate_object_typed(acpi_handle object,
							acpi_string pathname,
							काष्ठा acpi_object_list
							*बाह्यal_params,
							काष्ठा acpi_buffer
							*वापस_buffer,
							acpi_object_type
							वापस_type))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_object_info(acpi_handle object,
						  काष्ठा acpi_device_info
						  **वापस_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_install_method(u8 *buffer))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_next_object(acpi_object_type type,
						 acpi_handle parent,
						 acpi_handle child,
						 acpi_handle *out_handle))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_type(acpi_handle object,
					  acpi_object_type *out_type))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_parent(acpi_handle object,
					    acpi_handle *out_handle))

/*
 * Handler पूर्णांकerfaces
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_install_initialization_handler
			    (acpi_init_handler handler, u32 function))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_install_sci_handler(acpi_sci_handler
							  address,
							  व्योम *context))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_हटाओ_sci_handler(acpi_sci_handler
							 address))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_install_global_event_handler
				 (acpi_gbl_event_handler handler,
				  व्योम *context))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_install_fixed_event_handler(u32
								  acpi_event,
								  acpi_event_handler
								  handler,
								  व्योम
								  *context))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_हटाओ_fixed_event_handler(u32 acpi_event,
								 acpi_event_handler
								 handler))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_install_gpe_handler(acpi_handle
							  gpe_device,
							  u32 gpe_number,
							  u32 type,
							  acpi_gpe_handler
							  address,
							  व्योम *context))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_install_gpe_raw_handler(acpi_handle
							      gpe_device,
							      u32 gpe_number,
							      u32 type,
							      acpi_gpe_handler
							      address,
							      व्योम *context))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_हटाओ_gpe_handler(acpi_handle gpe_device,
							 u32 gpe_number,
							 acpi_gpe_handler
							 address))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_install_notअगरy_handler(acpi_handle device,
							 u32 handler_type,
							 acpi_notअगरy_handler
							 handler,
							 व्योम *context))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_हटाओ_notअगरy_handler(acpi_handle device,
							u32 handler_type,
							acpi_notअगरy_handler
							handler))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_install_address_space_handler(acpi_handle
								device,
								acpi_adr_space_type
								space_id,
								acpi_adr_space_handler
								handler,
								acpi_adr_space_setup
								setup,
								व्योम *context))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_हटाओ_address_space_handler(acpi_handle
							       device,
							       acpi_adr_space_type
							       space_id,
							       acpi_adr_space_handler
							       handler))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_install_exception_handler
			     (acpi_exception_handler handler))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_install_पूर्णांकerface_handler
			     (acpi_पूर्णांकerface_handler handler))

/*
 * Global Lock पूर्णांकerfaces
 */
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_acquire_global_lock(u16 समयout,
							 u32 *handle))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_release_global_lock(u32 handle))

/*
 * Interfaces to AML mutex objects
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_acquire_mutex(acpi_handle handle,
					       acpi_string pathname,
					       u16 समयout))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_release_mutex(acpi_handle handle,
					       acpi_string pathname))

/*
 * Fixed Event पूर्णांकerfaces
 */
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_enable_event(u32 event, u32 flags))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_disable_event(u32 event, u32 flags))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_clear_event(u32 event))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_get_event_status(u32 event,
						      acpi_event_status
						      *event_status))

/*
 * General Purpose Event (GPE) Interfaces
 */
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_update_all_gpes(व्योम))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_enable_gpe(acpi_handle gpe_device,
						u32 gpe_number))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_disable_gpe(acpi_handle gpe_device,
						 u32 gpe_number))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_clear_gpe(acpi_handle gpe_device,
					       u32 gpe_number))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_set_gpe(acpi_handle gpe_device,
					     u32 gpe_number, u8 action))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_finish_gpe(acpi_handle gpe_device,
						u32 gpe_number))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_mask_gpe(acpi_handle gpe_device,
					      u32 gpe_number, u8 is_masked))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_mark_gpe_क्रम_wake(acpi_handle gpe_device,
						       u32 gpe_number))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_setup_gpe_क्रम_wake(acpi_handle
							parent_device,
							acpi_handle gpe_device,
							u32 gpe_number))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_set_gpe_wake_mask(acpi_handle gpe_device,
							u32 gpe_number,
							u8 action))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_get_gpe_status(acpi_handle gpe_device,
						     u32 gpe_number,
						     acpi_event_status
						     *event_status))
ACPI_HW_DEPENDENT_RETURN_UINT32(u32 acpi_dispatch_gpe(acpi_handle gpe_device, u32 gpe_number))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_disable_all_gpes(व्योम))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_enable_all_runसमय_gpes(व्योम))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_enable_all_wakeup_gpes(व्योम))
ACPI_HW_DEPENDENT_RETURN_UINT32(u32 acpi_any_gpe_status_set(u32 gpe_skip_number))
ACPI_HW_DEPENDENT_RETURN_UINT32(u32 acpi_any_fixed_event_status_set(व्योम))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_get_gpe_device(u32 gpe_index,
						    acpi_handle *gpe_device))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_install_gpe_block(acpi_handle gpe_device,
						       काष्ठा
						       acpi_generic_address
						       *gpe_block_address,
						       u32 रेजिस्टर_count,
						       u32 पूर्णांकerrupt_number))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				 acpi_हटाओ_gpe_block(acpi_handle gpe_device))

/*
 * Resource पूर्णांकerfaces
 */
प्रकार
acpi_status (*acpi_walk_resource_callback) (काष्ठा acpi_resource * resource,
					    व्योम *context);

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_venकरोr_resource(acpi_handle device,
						     अक्षर *name,
						     काष्ठा acpi_venकरोr_uuid
						     *uuid,
						     काष्ठा acpi_buffer
						     *ret_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_current_resources(acpi_handle device,
							काष्ठा acpi_buffer
							*ret_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_possible_resources(acpi_handle device,
							 काष्ठा acpi_buffer
							 *ret_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_event_resources(acpi_handle device_handle,
						      काष्ठा acpi_buffer
						      *ret_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_walk_resource_buffer(काष्ठा acpi_buffer
						       *buffer,
						       acpi_walk_resource_callback
						       user_function,
						       व्योम *context))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_walk_resources(acpi_handle device, अक्षर *name,
						 acpi_walk_resource_callback
						 user_function, व्योम *context))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_set_current_resources(acpi_handle device,
							काष्ठा acpi_buffer
							*in_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_get_irq_routing_table(acpi_handle device,
							काष्ठा acpi_buffer
							*ret_buffer))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_resource_to_address64(काष्ठा acpi_resource
							*resource,
							काष्ठा
							acpi_resource_address64
							*out))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			     acpi_buffer_to_resource(u8 *aml_buffer,
						     u16 aml_buffer_length,
						     काष्ठा acpi_resource
						     **resource_ptr))

/*
 * Hardware (ACPI device) पूर्णांकerfaces
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_reset(व्योम))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_पढ़ो(u64 *value,
				      काष्ठा acpi_generic_address *reg))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_ग_लिखो(u64 value,
				       काष्ठा acpi_generic_address *reg))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_पढ़ो_bit_रेजिस्टर(u32 रेजिस्टर_id,
						       u32 *वापस_value))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_ग_लिखो_bit_रेजिस्टर(u32 रेजिस्टर_id,
							u32 value))

/*
 * Sleep/Wake पूर्णांकerfaces
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_sleep_type_data(u8 sleep_state,
						     u8 *slp_typ_a,
						     u8 *slp_typ_b))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_enter_sleep_state_prep(u8 sleep_state))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_enter_sleep_state(u8 sleep_state))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_enter_sleep_state_s4bios(व्योम))

ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_leave_sleep_state_prep(u8 sleep_state))
ACPI_EXTERNAL_RETURN_STATUS(acpi_status acpi_leave_sleep_state(u8 sleep_state))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_set_firmware_waking_vector
				(acpi_physical_address physical_address,
				 acpi_physical_address physical_address64))
/*
 * ACPI Timer पूर्णांकerfaces
 */
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_get_समयr_resolution(u32 *resolution))
ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status acpi_get_समयr(u32 *ticks))

ACPI_HW_DEPENDENT_RETURN_STATUS(acpi_status
				acpi_get_समयr_duration(u32 start_ticks,
							u32 end_ticks,
							u32 *समय_elapsed))

/*
 * Error/Warning output
 */
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(3)
			       व्योम ACPI_INTERNAL_VAR_XFACE
			       acpi_error(स्थिर अक्षर *module_name,
					  u32 line_number,
					  स्थिर अक्षर *क्रमmat, ...))
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(4)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_exception(स्थिर अक्षर *module_name,
					       u32 line_number,
					       acpi_status status,
					       स्थिर अक्षर *क्रमmat, ...))
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(3)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_warning(स्थिर अक्षर *module_name,
					     u32 line_number,
					     स्थिर अक्षर *क्रमmat, ...))
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(1)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_info(स्थिर अक्षर *क्रमmat, ...))
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(3)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_bios_error(स्थिर अक्षर *module_name,
						u32 line_number,
						स्थिर अक्षर *क्रमmat, ...))
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(4)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_bios_exception(स्थिर अक्षर *module_name,
						    u32 line_number,
						    acpi_status status,
						    स्थिर अक्षर *क्रमmat, ...))
ACPI_MSG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(3)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_bios_warning(स्थिर अक्षर *module_name,
						  u32 line_number,
						  स्थिर अक्षर *क्रमmat, ...))

/*
 * Debug output
 */
ACPI_DBG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(6)
			       व्योम ACPI_INTERNAL_VAR_XFACE
			       acpi_debug_prपूर्णांक(u32 requested_debug_level,
						u32 line_number,
						स्थिर अक्षर *function_name,
						स्थिर अक्षर *module_name,
						u32 component_id,
						स्थिर अक्षर *क्रमmat, ...))
ACPI_DBG_DEPENDENT_RETURN_VOID(ACPI_PRINTF_LIKE(6)
				व्योम ACPI_INTERNAL_VAR_XFACE
				acpi_debug_prपूर्णांक_raw(u32 requested_debug_level,
						     u32 line_number,
						     स्थिर अक्षर *function_name,
						     स्थिर अक्षर *module_name,
						     u32 component_id,
						     स्थिर अक्षर *क्रमmat, ...))

ACPI_DBG_DEPENDENT_RETURN_VOID(व्योम
			       acpi_trace_poपूर्णांक(acpi_trace_event_type type,
						u8 begin,
						u8 *aml, अक्षर *pathname))

acpi_status acpi_initialize_debugger(व्योम);

व्योम acpi_terminate_debugger(व्योम);

/*
 * Divergences
 */
ACPI_EXTERNAL_RETURN_STATUS(acpi_status
			    acpi_get_data_full(acpi_handle object,
					       acpi_object_handler handler,
					       व्योम **data,
					       व्योम (*callback)(व्योम *)))

व्योम acpi_run_debugger(अक्षर *batch_buffer);

व्योम acpi_set_debugger_thपढ़ो_id(acpi_thपढ़ो_id thपढ़ो_id);

#पूर्ण_अगर				/* __ACXFACE_H__ */
