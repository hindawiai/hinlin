<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acglobal.h - Declarations क्रम global variables
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACGLOBAL_H__
#घोषणा __ACGLOBAL_H__

/*****************************************************************************
 *
 * Globals related to the incoming ACPI tables
 *
 ****************************************************************************/

/* Master list of all ACPI tables that were found in the RSDT/XSDT */

ACPI_GLOBAL(काष्ठा acpi_table_list, acpi_gbl_root_table_list);

/* DSDT inक्रमmation. Used to check क्रम DSDT corruption */

ACPI_GLOBAL(काष्ठा acpi_table_header *, acpi_gbl_DSDT);
ACPI_GLOBAL(काष्ठा acpi_table_header, acpi_gbl_original_dsdt_header);
ACPI_INIT_GLOBAL(u32, acpi_gbl_dsdt_index, ACPI_INVALID_TABLE_INDEX);
ACPI_INIT_GLOBAL(u32, acpi_gbl_facs_index, ACPI_INVALID_TABLE_INDEX);
ACPI_INIT_GLOBAL(u32, acpi_gbl_xfacs_index, ACPI_INVALID_TABLE_INDEX);
ACPI_INIT_GLOBAL(u32, acpi_gbl_fadt_index, ACPI_INVALID_TABLE_INDEX);

#अगर (!ACPI_REDUCED_HARDWARE)
ACPI_GLOBAL(काष्ठा acpi_table_facs *, acpi_gbl_FACS);

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/* These addresses are calculated from the FADT Event Block addresses */

ACPI_GLOBAL(काष्ठा acpi_generic_address, acpi_gbl_xpm1a_status);
ACPI_GLOBAL(काष्ठा acpi_generic_address, acpi_gbl_xpm1a_enable);

ACPI_GLOBAL(काष्ठा acpi_generic_address, acpi_gbl_xpm1b_status);
ACPI_GLOBAL(काष्ठा acpi_generic_address, acpi_gbl_xpm1b_enable);

#अगर_घोषित ACPI_GPE_USE_LOGICAL_ADDRESSES
ACPI_GLOBAL(अचिन्हित दीर्घ, acpi_gbl_xgpe0_block_logical_address);
ACPI_GLOBAL(अचिन्हित दीर्घ, acpi_gbl_xgpe1_block_logical_address);

#पूर्ण_अगर				/* ACPI_GPE_USE_LOGICAL_ADDRESSES */

/*
 * Handle both ACPI 1.0 and ACPI 2.0+ Integer widths. The पूर्णांकeger width is
 * determined by the revision of the DSDT: If the DSDT revision is less than
 * 2, use only the lower 32 bits of the पूर्णांकernal 64-bit Integer.
 */
ACPI_GLOBAL(u8, acpi_gbl_पूर्णांकeger_bit_width);
ACPI_GLOBAL(u8, acpi_gbl_पूर्णांकeger_byte_width);
ACPI_GLOBAL(u8, acpi_gbl_पूर्णांकeger_nybble_width);

/*****************************************************************************
 *
 * Mutual exclusion within the ACPICA subप्रणाली
 *
 ****************************************************************************/

/*
 * Predefined mutex objects. This array contains the
 * actual OS mutex handles, indexed by the local ACPI_MUTEX_HANDLEs.
 * (The table maps local handles to the real OS handles)
 */
ACPI_GLOBAL(काष्ठा acpi_mutex_info, acpi_gbl_mutex_info[ACPI_NUM_MUTEX]);

/*
 * Global lock mutex is an actual AML mutex object
 * Global lock semaphore works in conjunction with the actual global lock
 * Global lock spinlock is used क्रम "pending" handshake
 */
ACPI_GLOBAL(जोड़ acpi_opeअक्रम_object *, acpi_gbl_global_lock_mutex);
ACPI_GLOBAL(acpi_semaphore, acpi_gbl_global_lock_semaphore);
ACPI_GLOBAL(acpi_spinlock, acpi_gbl_global_lock_pending_lock);
ACPI_GLOBAL(u16, acpi_gbl_global_lock_handle);
ACPI_GLOBAL(u8, acpi_gbl_global_lock_acquired);
ACPI_GLOBAL(u8, acpi_gbl_global_lock_present);
ACPI_GLOBAL(u8, acpi_gbl_global_lock_pending);

/*
 * Spinlocks are used क्रम पूर्णांकerfaces that can be possibly called at
 * पूर्णांकerrupt level
 */
ACPI_GLOBAL(acpi_spinlock, acpi_gbl_gpe_lock);	/* For GPE data काष्ठाs and रेजिस्टरs */
ACPI_GLOBAL(acpi_raw_spinlock, acpi_gbl_hardware_lock);	/* For ACPI H/W except GPE रेजिस्टरs */
ACPI_GLOBAL(acpi_spinlock, acpi_gbl_reference_count_lock);

/* Mutex क्रम _OSI support */

ACPI_GLOBAL(acpi_mutex, acpi_gbl_osi_mutex);

/* Reader/Writer lock is used क्रम namespace walk and dynamic table unload */

ACPI_GLOBAL(काष्ठा acpi_rw_lock, acpi_gbl_namespace_rw_lock);

/*****************************************************************************
 *
 * Miscellaneous globals
 *
 ****************************************************************************/

/* Object caches */

ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_namespace_cache);
ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_state_cache);
ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_ps_node_cache);
ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_ps_node_ext_cache);
ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_opeअक्रम_cache);

/* System */

ACPI_INIT_GLOBAL(u32, acpi_gbl_startup_flags, 0);
ACPI_INIT_GLOBAL(u8, acpi_gbl_shutकरोwn, TRUE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_early_initialization, TRUE);

/* Global handlers */

ACPI_GLOBAL(काष्ठा acpi_global_notअगरy_handler, acpi_gbl_global_notअगरy[2]);
ACPI_GLOBAL(acpi_exception_handler, acpi_gbl_exception_handler);
ACPI_GLOBAL(acpi_init_handler, acpi_gbl_init_handler);
ACPI_GLOBAL(acpi_table_handler, acpi_gbl_table_handler);
ACPI_GLOBAL(व्योम *, acpi_gbl_table_handler_context);
ACPI_GLOBAL(acpi_पूर्णांकerface_handler, acpi_gbl_पूर्णांकerface_handler);
ACPI_GLOBAL(काष्ठा acpi_sci_handler_info *, acpi_gbl_sci_handler_list);

/* Owner ID support */

ACPI_GLOBAL(u32, acpi_gbl_owner_id_mask[ACPI_NUM_OWNERID_MASKS]);
ACPI_GLOBAL(u8, acpi_gbl_last_owner_id_index);
ACPI_GLOBAL(u8, acpi_gbl_next_owner_id_offset);

/* Initialization sequencing */

ACPI_INIT_GLOBAL(u8, acpi_gbl_namespace_initialized, FALSE);

/* Miscellaneous */

ACPI_GLOBAL(u32, acpi_gbl_original_mode);
ACPI_GLOBAL(u32, acpi_gbl_ns_lookup_count);
ACPI_GLOBAL(u32, acpi_gbl_ps_find_count);
ACPI_GLOBAL(u16, acpi_gbl_pm1_enable_रेजिस्टर_save);
ACPI_GLOBAL(u8, acpi_gbl_debugger_configuration);
ACPI_GLOBAL(u8, acpi_gbl_step_to_next_call);
ACPI_GLOBAL(u8, acpi_gbl_acpi_hardware_present);
ACPI_GLOBAL(u8, acpi_gbl_events_initialized);
ACPI_GLOBAL(काष्ठा acpi_पूर्णांकerface_info *, acpi_gbl_supported_पूर्णांकerfaces);
ACPI_GLOBAL(काष्ठा acpi_address_range *,
	    acpi_gbl_address_range_list[ACPI_ADDRESS_RANGE_MAX]);

/* Other miscellaneous, declared and initialized in utglobal */

बाह्य स्थिर अक्षर *acpi_gbl_sleep_state_names[ACPI_S_STATE_COUNT];
बाह्य स्थिर अक्षर *acpi_gbl_lowest_dstate_names[ACPI_NUM_sx_w_METHODS];
बाह्य स्थिर अक्षर *acpi_gbl_highest_dstate_names[ACPI_NUM_sx_d_METHODS];
बाह्य स्थिर अक्षर *acpi_gbl_region_types[ACPI_NUM_PREDEFINED_REGIONS];
बाह्य स्थिर अक्षर acpi_gbl_lower_hex_digits[];
बाह्य स्थिर अक्षर acpi_gbl_upper_hex_digits[];
बाह्य स्थिर काष्ठा acpi_opcode_info acpi_gbl_aml_op_info[AML_NUM_OPCODES];

/* Lists क्रम tracking memory allocations (debug only) */

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
ACPI_GLOBAL(काष्ठा acpi_memory_list *, acpi_gbl_global_list);
ACPI_GLOBAL(काष्ठा acpi_memory_list *, acpi_gbl_ns_node_list);
ACPI_GLOBAL(u8, acpi_gbl_display_final_mem_stats);
ACPI_GLOBAL(u8, acpi_gbl_disable_mem_tracking);
ACPI_GLOBAL(u8, acpi_gbl_verbose_leak_dump);
#पूर्ण_अगर

/*****************************************************************************
 *
 * ACPI Namespace
 *
 ****************************************************************************/

#घोषणा NUM_PREDEFINED_NAMES            10

ACPI_GLOBAL(काष्ठा acpi_namespace_node, acpi_gbl_root_node_काष्ठा);
ACPI_GLOBAL(काष्ठा acpi_namespace_node *, acpi_gbl_root_node);
ACPI_GLOBAL(काष्ठा acpi_namespace_node *, acpi_gbl_fadt_gpe_device);

बाह्य स्थिर u8 acpi_gbl_ns_properties[ACPI_NUM_NS_TYPES];
बाह्य स्थिर काष्ठा acpi_predefined_names
    acpi_gbl_pre_defined_names[NUM_PREDEFINED_NAMES];

#अगर_घोषित ACPI_DEBUG_OUTPUT
ACPI_GLOBAL(u32, acpi_gbl_current_node_count);
ACPI_GLOBAL(u32, acpi_gbl_current_node_size);
ACPI_GLOBAL(u32, acpi_gbl_max_concurrent_node_count);
ACPI_GLOBAL(acpi_size *, acpi_gbl_entry_stack_poपूर्णांकer);
ACPI_GLOBAL(acpi_size *, acpi_gbl_lowest_stack_poपूर्णांकer);
ACPI_GLOBAL(u32, acpi_gbl_deepest_nesting);
ACPI_INIT_GLOBAL(u32, acpi_gbl_nesting_level, 0);
#पूर्ण_अगर

/*****************************************************************************
 *
 * Interpreter/Parser globals
 *
 ****************************************************************************/

/* Control method single step flag */

ACPI_GLOBAL(u8, acpi_gbl_cm_single_step);
ACPI_GLOBAL(काष्ठा acpi_thपढ़ो_state *, acpi_gbl_current_walk_list);
ACPI_INIT_GLOBAL(जोड़ acpi_parse_object, *acpi_gbl_current_scope, शून्य);

/* ASL/ASL+ converter */

ACPI_INIT_GLOBAL(u8, acpi_gbl_capture_comments, FALSE);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_last_list_head, शून्य);

/*****************************************************************************
 *
 * Hardware globals
 *
 ****************************************************************************/

बाह्य काष्ठा acpi_bit_रेजिस्टर_info
    acpi_gbl_bit_रेजिस्टर_info[ACPI_NUM_BITREG];
ACPI_GLOBAL(u8, acpi_gbl_sleep_type_a);
ACPI_GLOBAL(u8, acpi_gbl_sleep_type_b);

/*****************************************************************************
 *
 * Event and GPE globals
 *
 ****************************************************************************/

#अगर (!ACPI_REDUCED_HARDWARE)
ACPI_GLOBAL(u8, acpi_gbl_all_gpes_initialized);
ACPI_GLOBAL(काष्ठा acpi_gpe_xrupt_info *, acpi_gbl_gpe_xrupt_list_head);
ACPI_GLOBAL(काष्ठा acpi_gpe_block_info *,
	    acpi_gbl_gpe_fadt_blocks[ACPI_MAX_GPE_BLOCKS]);
ACPI_GLOBAL(acpi_gbl_event_handler, acpi_gbl_global_event_handler);
ACPI_GLOBAL(व्योम *, acpi_gbl_global_event_handler_context);
ACPI_GLOBAL(काष्ठा acpi_fixed_event_handler,
	    acpi_gbl_fixed_event_handlers[ACPI_NUM_FIXED_EVENTS]);
बाह्य काष्ठा acpi_fixed_event_info
    acpi_gbl_fixed_event_info[ACPI_NUM_FIXED_EVENTS];
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/*****************************************************************************
 *
 * Debug support
 *
 ****************************************************************************/

/* Event counters */

ACPI_GLOBAL(u32, acpi_method_count);
ACPI_GLOBAL(u32, acpi_gpe_count);
ACPI_GLOBAL(u32, acpi_sci_count);
ACPI_GLOBAL(u32, acpi_fixed_event_count[ACPI_NUM_FIXED_EVENTS]);

/* Dynamic control method tracing mechanism */

ACPI_GLOBAL(u32, acpi_gbl_original_dbg_level);
ACPI_GLOBAL(u32, acpi_gbl_original_dbg_layer);

/*****************************************************************************
 *
 * Debugger and Disassembler
 *
 ****************************************************************************/

ACPI_INIT_GLOBAL(u8, acpi_gbl_db_output_flags, ACPI_DB_CONSOLE_OUTPUT);

#अगर_घोषित ACPI_DISASSEMBLER

/* Do not disassemble buffers to resource descriptors */

ACPI_INIT_GLOBAL(u8, acpi_gbl_no_resource_disassembly, FALSE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_ignore_noop_चालक, FALSE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_cstyle_disassembly, TRUE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_क्रमce_aml_disassembly, FALSE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_dm_opt_verbose, TRUE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_dm_emit_बाह्यal_opcodes, FALSE);
ACPI_INIT_GLOBAL(u8, acpi_gbl_करो_disassembler_optimizations, TRUE);
ACPI_INIT_GLOBAL(ACPI_PARSE_OBJECT_LIST, *acpi_gbl_temp_list_head, शून्य);

ACPI_GLOBAL(u8, acpi_gbl_dm_opt_disयंत्र);
ACPI_GLOBAL(u8, acpi_gbl_dm_opt_listing);
ACPI_GLOBAL(u8, acpi_gbl_num_बाह्यal_methods);
ACPI_GLOBAL(u32, acpi_gbl_resolved_बाह्यal_methods);
ACPI_GLOBAL(काष्ठा acpi_बाह्यal_list *, acpi_gbl_बाह्यal_list);
ACPI_GLOBAL(काष्ठा acpi_बाह्यal_file *, acpi_gbl_बाह्यal_file_list);
#पूर्ण_अगर

#अगर_घोषित ACPI_DEBUGGER
ACPI_INIT_GLOBAL(u8, acpi_gbl_पात_method, FALSE);
ACPI_INIT_GLOBAL(acpi_thपढ़ो_id, acpi_gbl_db_thपढ़ो_id, ACPI_INVALID_THREAD_ID);
ACPI_INIT_GLOBAL(u32, acpi_gbl_next_cmd_num, 1);

ACPI_GLOBAL(u8, acpi_gbl_db_opt_no_ini_methods);
ACPI_GLOBAL(u8, acpi_gbl_db_opt_no_region_support);
ACPI_GLOBAL(u8, acpi_gbl_db_output_to_file);
ACPI_GLOBAL(अक्षर *, acpi_gbl_db_buffer);
ACPI_GLOBAL(अक्षर *, acpi_gbl_db_filename);
ACPI_GLOBAL(u32, acpi_gbl_db_debug_level);
ACPI_GLOBAL(u32, acpi_gbl_db_console_debug_level);
ACPI_GLOBAL(काष्ठा acpi_namespace_node *, acpi_gbl_db_scope_node);
ACPI_GLOBAL(u8, acpi_gbl_db_terminate_loop);
ACPI_GLOBAL(u8, acpi_gbl_db_thपढ़ोs_terminated);
ACPI_GLOBAL(अक्षर *, acpi_gbl_db_args[ACPI_DEBUGGER_MAX_ARGS]);
ACPI_GLOBAL(acpi_object_type, acpi_gbl_db_arg_types[ACPI_DEBUGGER_MAX_ARGS]);

/* These buffers should all be the same size */

ACPI_GLOBAL(अक्षर, acpi_gbl_db_parsed_buf[ACPI_DB_LINE_BUFFER_SIZE]);
ACPI_GLOBAL(अक्षर, acpi_gbl_db_scope_buf[ACPI_DB_LINE_BUFFER_SIZE]);
ACPI_GLOBAL(अक्षर, acpi_gbl_db_debug_filename[ACPI_DB_LINE_BUFFER_SIZE]);

/* Statistics globals */

ACPI_GLOBAL(u16, acpi_gbl_obj_type_count[ACPI_TOTAL_TYPES]);
ACPI_GLOBAL(u16, acpi_gbl_node_type_count[ACPI_TOTAL_TYPES]);
ACPI_GLOBAL(u16, acpi_gbl_obj_type_count_misc);
ACPI_GLOBAL(u16, acpi_gbl_node_type_count_misc);
ACPI_GLOBAL(u32, acpi_gbl_num_nodes);
ACPI_GLOBAL(u32, acpi_gbl_num_objects);
#पूर्ण_अगर				/* ACPI_DEBUGGER */

#अगर defined (ACPI_DISASSEMBLER) || defined (ACPI_ASL_COMPILER)
ACPI_GLOBAL(स्थिर अक्षर, *acpi_gbl_pld_panel_list[]);
ACPI_GLOBAL(स्थिर अक्षर, *acpi_gbl_pld_vertical_position_list[]);
ACPI_GLOBAL(स्थिर अक्षर, *acpi_gbl_pld_horizontal_position_list[]);
ACPI_GLOBAL(स्थिर अक्षर, *acpi_gbl_pld_shape_list[]);
ACPI_INIT_GLOBAL(u8, acpi_gbl_disयंत्र_flag, FALSE);
#पूर्ण_अगर

/*****************************************************************************
 *
 * ACPICA application-specअगरic globals
 *
 ****************************************************************************/

/* ASL-to-ASL+ conversion utility (implemented within the iASL compiler) */

#अगर_घोषित ACPI_ASL_COMPILER
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_अंतरभूत_comment, शून्य);
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_end_node_comment, शून्य);
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_खोलो_brace_comment, शून्य);
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_बंद_brace_comment, शून्य);

ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_root_filename, शून्य);
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_filename, शून्य);
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_parent_filename, शून्य);
ACPI_INIT_GLOBAL(अक्षर *, acpi_gbl_current_include_filename, शून्य);

ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_def_blk_comment_list_head,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_def_blk_comment_list_tail,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_reg_comment_list_head,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_reg_comment_list_tail,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_inc_comment_list_head,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_inc_comment_list_tail,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_end_blk_comment_list_head,
		 शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_comment_node, *acpi_gbl_end_blk_comment_list_tail,
		 शून्य);

ACPI_INIT_GLOBAL(काष्ठा acpi_comment_addr_node,
		 *acpi_gbl_comment_addr_list_head, शून्य);
ACPI_INIT_GLOBAL(काष्ठा acpi_file_node, *acpi_gbl_file_tree_root, शून्य);

ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_reg_comment_cache);
ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_comment_addr_cache);
ACPI_GLOBAL(acpi_cache_t *, acpi_gbl_file_cache);

ACPI_INIT_GLOBAL(u8, acpi_gbl_debug_asl_conversion, FALSE);
ACPI_INIT_GLOBAL(ACPI_खाता, acpi_gbl_conv_debug_file, शून्य);
ACPI_GLOBAL(अक्षर, acpi_gbl_table_sig[4]);
#पूर्ण_अगर

#अगर_घोषित ACPI_APPLICATION
ACPI_INIT_GLOBAL(ACPI_खाता, acpi_gbl_debug_file, शून्य);
ACPI_INIT_GLOBAL(ACPI_खाता, acpi_gbl_output_file, शून्य);
ACPI_INIT_GLOBAL(u8, acpi_gbl_debug_समयout, FALSE);

/* Prपूर्णांक buffer */

ACPI_GLOBAL(acpi_spinlock, acpi_gbl_prपूर्णांक_lock);	/* For prपूर्णांक buffer */
ACPI_GLOBAL(अक्षर, acpi_gbl_prपूर्णांक_buffer[1024]);
#पूर्ण_अगर				/* ACPI_APPLICATION */

#पूर्ण_अगर				/* __ACGLOBAL_H__ */
