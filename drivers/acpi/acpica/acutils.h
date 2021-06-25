<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acutils.h -- prototypes क्रम the common (subप्रणाली-wide) procedures
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित _ACUTILS_H
#घोषणा _ACUTILS_H

बाह्य स्थिर u8 acpi_gbl_resource_aml_sizes[];
बाह्य स्थिर u8 acpi_gbl_resource_aml_serial_bus_sizes[];

/* Strings used by the disassembler and debugger resource dump routines */

#अगर defined(ACPI_DEBUG_OUTPUT) || defined (ACPI_DISASSEMBLER) || defined (ACPI_DEBUGGER)

बाह्य स्थिर अक्षर *acpi_gbl_bm_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_config_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_consume_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_dec_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_he_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_io_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ll_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_max_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_mem_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_min_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_mtp_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_phy_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_rng_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_rw_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_shr_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_siz_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_trs_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ttp_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_typ_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ppc_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ior_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_dts_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ct_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_sbt_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_am_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_sm_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_wm_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_cph_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_cpo_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_dp_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ed_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_bpb_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_sb_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_fc_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_pt_decode[];
बाह्य स्थिर अक्षर *acpi_gbl_ptyp_decode[];
#पूर्ण_अगर

/*
 * For the iASL compiler हाल, the output is redirected to मानक_त्रुटि so that
 * any of the various ACPI errors and warnings करो not appear in the output
 * files, क्रम either the compiler or disassembler portions of the tool.
 */
#अगर_घोषित ACPI_ASL_COMPILER

#समावेश <मानकपन.स>

#घोषणा ACPI_MSG_REसूचीECT_BEGIN \
	खाता                            *output_file = acpi_gbl_output_file; \
	acpi_os_redirect_output (मानक_त्रुटि);

#घोषणा ACPI_MSG_REसूचीECT_END \
	acpi_os_redirect_output (output_file);

#अन्यथा
/*
 * non-iASL हाल - no redirection, nothing to करो
 */
#घोषणा ACPI_MSG_REसूचीECT_BEGIN
#घोषणा ACPI_MSG_REसूचीECT_END
#पूर्ण_अगर

/*
 * Common error message prefixes
 */
#अगर_अघोषित ACPI_MSG_ERROR
#घोषणा ACPI_MSG_ERROR          "ACPI Error: "
#पूर्ण_अगर
#अगर_अघोषित ACPI_MSG_WARNING
#घोषणा ACPI_MSG_WARNING        "ACPI Warning: "
#पूर्ण_अगर
#अगर_अघोषित ACPI_MSG_INFO
#घोषणा ACPI_MSG_INFO           "ACPI: "
#पूर्ण_अगर

#अगर_अघोषित ACPI_MSG_BIOS_ERROR
#घोषणा ACPI_MSG_BIOS_ERROR     "Firmware Error (ACPI): "
#पूर्ण_अगर
#अगर_अघोषित ACPI_MSG_BIOS_WARNING
#घोषणा ACPI_MSG_BIOS_WARNING   "Firmware Warning (ACPI): "
#पूर्ण_अगर

/*
 * Common message suffix
 */
#घोषणा ACPI_MSG_SUFFIX \
	acpi_os_म_लिखो (" (%8.8X/%s-%u)\n", ACPI_CA_VERSION, module_name, line_number)

/* Flags to indicate implicit or explicit string-to-पूर्णांकeger conversion */

#घोषणा ACPI_IMPLICIT_CONVERSION        TRUE
#घोषणा ACPI_NO_IMPLICIT_CONVERSION     FALSE

/* Types क्रम Resource descriptor entries */

#घोषणा ACPI_INVALID_RESOURCE           0
#घोषणा ACPI_FIXED_LENGTH               1
#घोषणा ACPI_VARIABLE_LENGTH            2
#घोषणा ACPI_SMALL_VARIABLE_LENGTH      3

प्रकार
acpi_status (*acpi_walk_aml_callback) (u8 *aml,
				       u32 length,
				       u32 offset,
				       u8 resource_index, व्योम **context);

प्रकार
acpi_status (*acpi_pkg_callback) (u8 object_type,
				  जोड़ acpi_opeअक्रम_object * source_object,
				  जोड़ acpi_generic_state * state,
				  व्योम *context);

काष्ठा acpi_pkg_info अणु
	u8 *मुक्त_space;
	acpi_size length;
	u32 object_space;
	u32 num_packages;
पूर्ण;

/* Object reference counts */

#घोषणा REF_INCREMENT       (u16) 0
#घोषणा REF_DECREMENT       (u16) 1

/* acpi_ut_dump_buffer */

#घोषणा DB_BYTE_DISPLAY      0x01
#घोषणा DB_WORD_DISPLAY      0x02
#घोषणा DB_DWORD_DISPLAY     0x04
#घोषणा DB_QWORD_DISPLAY     0x08
#घोषणा DB_DISPLAY_DATA_ONLY 0x10

/*
 * utascii - ASCII utilities
 */
u8 acpi_ut_valid_nameseg(अक्षर *signature);

u8 acpi_ut_valid_name_अक्षर(अक्षर अक्षरacter, u32 position);

व्योम acpi_ut_check_and_repair_ascii(u8 *name, अक्षर *repaired_name, u32 count);

/*
 * utnonansi - Non-ANSI C library functions
 */
व्योम acpi_ut_strupr(अक्षर *src_string);

व्योम acpi_ut_strlwr(अक्षर *src_string);

पूर्णांक acpi_ut_stricmp(अक्षर *string1, अक्षर *string2);

/*
 * utstrsuppt - string-to-पूर्णांकeger conversion support functions
 */
acpi_status acpi_ut_convert_octal_string(अक्षर *string, u64 *वापस_value);

acpi_status acpi_ut_convert_decimal_string(अक्षर *string, u64 *वापस_value_ptr);

acpi_status acpi_ut_convert_hex_string(अक्षर *string, u64 *वापस_value_ptr);

अक्षर acpi_ut_हटाओ_whitespace(अक्षर **string);

अक्षर acpi_ut_हटाओ_leading_zeros(अक्षर **string);

u8 acpi_ut_detect_hex_prefix(अक्षर **string);

व्योम acpi_ut_हटाओ_hex_prefix(अक्षर **string);

u8 acpi_ut_detect_octal_prefix(अक्षर **string);

/*
 * utम_से_अदीर्घ64 - string-to-पूर्णांकeger conversion functions
 */
acpi_status acpi_ut_म_से_अदीर्घ64(अक्षर *string, u64 *ret_पूर्णांकeger);

u64 acpi_ut_explicit_म_से_अदीर्घ64(अक्षर *string);

u64 acpi_ut_implicit_म_से_अदीर्घ64(अक्षर *string);

/*
 * utglobal - Global data काष्ठाures and procedures
 */
acpi_status acpi_ut_init_globals(व्योम);

स्थिर अक्षर *acpi_ut_get_mutex_name(u32 mutex_id);

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)

स्थिर अक्षर *acpi_ut_get_notअगरy_name(u32 notअगरy_value, acpi_object_type type);
#पूर्ण_अगर

स्थिर अक्षर *acpi_ut_get_type_name(acpi_object_type type);

स्थिर अक्षर *acpi_ut_get_node_name(व्योम *object);

स्थिर अक्षर *acpi_ut_get_descriptor_name(व्योम *object);

स्थिर अक्षर *acpi_ut_get_reference_name(जोड़ acpi_opeअक्रम_object *object);

स्थिर अक्षर *acpi_ut_get_object_type_name(जोड़ acpi_opeअक्रम_object *obj_desc);

स्थिर अक्षर *acpi_ut_get_region_name(u8 space_id);

स्थिर अक्षर *acpi_ut_get_event_name(u32 event_id);

स्थिर अक्षर *acpi_ut_get_argument_type_name(u32 arg_type);

अक्षर acpi_ut_hex_to_ascii_अक्षर(u64 पूर्णांकeger, u32 position);

acpi_status acpi_ut_ascii_to_hex_byte(अक्षर *two_ascii_अक्षरs, u8 *वापस_byte);

u8 acpi_ut_ascii_अक्षर_to_hex(पूर्णांक hex_अक्षर);

u8 acpi_ut_valid_object_type(acpi_object_type type);

/*
 * utinit - miscellaneous initialization and shutकरोwn
 */
acpi_status acpi_ut_hardware_initialize(व्योम);

व्योम acpi_ut_subप्रणाली_shutकरोwn(व्योम);

/*
 * utcopy - Object स्थिरruction and conversion पूर्णांकerfaces
 */
acpi_status
acpi_ut_build_simple_object(जोड़ acpi_opeअक्रम_object *obj,
			    जोड़ acpi_object *user_obj,
			    u8 *data_space, u32 *buffer_space_used);

acpi_status
acpi_ut_build_package_object(जोड़ acpi_opeअक्रम_object *obj,
			     u8 *buffer, u32 *space_used);

acpi_status
acpi_ut_copy_iobject_to_eobject(जोड़ acpi_opeअक्रम_object *obj,
				काष्ठा acpi_buffer *ret_buffer);

acpi_status
acpi_ut_copy_eobject_to_iobject(जोड़ acpi_object *obj,
				जोड़ acpi_opeअक्रम_object **पूर्णांकernal_obj);

acpi_status
acpi_ut_copy_isimple_to_isimple(जोड़ acpi_opeअक्रम_object *source_obj,
				जोड़ acpi_opeअक्रम_object *dest_obj);

acpi_status
acpi_ut_copy_iobject_to_iobject(जोड़ acpi_opeअक्रम_object *source_desc,
				जोड़ acpi_opeअक्रम_object **dest_desc,
				काष्ठा acpi_walk_state *walk_state);

/*
 * utcreate - Object creation
 */
acpi_status
acpi_ut_update_object_reference(जोड़ acpi_opeअक्रम_object *object, u16 action);

/*
 * utdebug - Debug पूर्णांकerfaces
 */
व्योम acpi_ut_init_stack_ptr_trace(व्योम);

व्योम acpi_ut_track_stack_ptr(व्योम);

व्योम
acpi_ut_trace(u32 line_number,
	      स्थिर अक्षर *function_name,
	      स्थिर अक्षर *module_name, u32 component_id);

व्योम
acpi_ut_trace_ptr(u32 line_number,
		  स्थिर अक्षर *function_name,
		  स्थिर अक्षर *module_name,
		  u32 component_id, स्थिर व्योम *poपूर्णांकer);

व्योम
acpi_ut_trace_u32(u32 line_number,
		  स्थिर अक्षर *function_name,
		  स्थिर अक्षर *module_name, u32 component_id, u32 पूर्णांकeger);

व्योम
acpi_ut_trace_str(u32 line_number,
		  स्थिर अक्षर *function_name,
		  स्थिर अक्षर *module_name,
		  u32 component_id, स्थिर अक्षर *string);

व्योम
acpi_ut_निकास(u32 line_number,
	     स्थिर अक्षर *function_name,
	     स्थिर अक्षर *module_name, u32 component_id);

व्योम
acpi_ut_status_निकास(u32 line_number,
		    स्थिर अक्षर *function_name,
		    स्थिर अक्षर *module_name,
		    u32 component_id, acpi_status status);

व्योम
acpi_ut_value_निकास(u32 line_number,
		   स्थिर अक्षर *function_name,
		   स्थिर अक्षर *module_name, u32 component_id, u64 value);

व्योम
acpi_ut_ptr_निकास(u32 line_number,
		 स्थिर अक्षर *function_name,
		 स्थिर अक्षर *module_name, u32 component_id, u8 *ptr);

व्योम
acpi_ut_str_निकास(u32 line_number,
		 स्थिर अक्षर *function_name,
		 स्थिर अक्षर *module_name, u32 component_id, स्थिर अक्षर *string);

व्योम
acpi_ut_debug_dump_buffer(u8 *buffer, u32 count, u32 display, u32 component_id);

व्योम acpi_ut_dump_buffer(u8 *buffer, u32 count, u32 display, u32 offset);

#अगर_घोषित ACPI_APPLICATION
व्योम
acpi_ut_dump_buffer_to_file(ACPI_खाता file,
			    u8 *buffer,
			    u32 count, u32 display, u32 base_offset);
#पूर्ण_अगर

व्योम acpi_ut_report_error(अक्षर *module_name, u32 line_number);

व्योम acpi_ut_report_info(अक्षर *module_name, u32 line_number);

व्योम acpi_ut_report_warning(अक्षर *module_name, u32 line_number);

/*
 * utdelete - Object deletion and reference counts
 */
व्योम acpi_ut_add_reference(जोड़ acpi_opeअक्रम_object *object);

व्योम acpi_ut_हटाओ_reference(जोड़ acpi_opeअक्रम_object *object);

व्योम acpi_ut_delete_पूर्णांकernal_package_object(जोड़ acpi_opeअक्रम_object *object);

व्योम acpi_ut_delete_पूर्णांकernal_simple_object(जोड़ acpi_opeअक्रम_object *object);

व्योम acpi_ut_delete_पूर्णांकernal_object_list(जोड़ acpi_opeअक्रम_object **obj_list);

/*
 * uteval - object evaluation
 */
acpi_status
acpi_ut_evaluate_object(काष्ठा acpi_namespace_node *prefix_node,
			स्थिर अक्षर *path,
			u32 expected_वापस_btypes,
			जोड़ acpi_opeअक्रम_object **वापस_desc);

acpi_status
acpi_ut_evaluate_numeric_object(स्थिर अक्षर *object_name,
				काष्ठा acpi_namespace_node *device_node,
				u64 *value);

acpi_status
acpi_ut_execute_STA(काष्ठा acpi_namespace_node *device_node, u32 *status_flags);

acpi_status
acpi_ut_execute_घातer_methods(काष्ठा acpi_namespace_node *device_node,
			      स्थिर अक्षर **method_names,
			      u8 method_count, u8 *out_values);

/*
 * utids - device ID support
 */
acpi_status
acpi_ut_execute_HID(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id ** वापस_id);

acpi_status
acpi_ut_execute_UID(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id ** वापस_id);

acpi_status
acpi_ut_execute_CID(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id_list ** वापस_cid_list);

acpi_status
acpi_ut_execute_CLS(काष्ठा acpi_namespace_node *device_node,
		    काष्ठा acpi_pnp_device_id **वापस_id);

/*
 * utlock - पढ़ोer/ग_लिखोr locks
 */
acpi_status acpi_ut_create_rw_lock(काष्ठा acpi_rw_lock *lock);

व्योम acpi_ut_delete_rw_lock(काष्ठा acpi_rw_lock *lock);

acpi_status acpi_ut_acquire_पढ़ो_lock(काष्ठा acpi_rw_lock *lock);

acpi_status acpi_ut_release_पढ़ो_lock(काष्ठा acpi_rw_lock *lock);

acpi_status acpi_ut_acquire_ग_लिखो_lock(काष्ठा acpi_rw_lock *lock);

व्योम acpi_ut_release_ग_लिखो_lock(काष्ठा acpi_rw_lock *lock);

/*
 * utobject - पूर्णांकernal object create/delete/cache routines
 */
जोड़ acpi_opeअक्रम_object *acpi_ut_create_पूर्णांकernal_object_dbg(स्थिर अक्षर
							      *module_name,
							      u32 line_number,
							      u32 component_id,
							      acpi_object_type
							      type);

व्योम *acpi_ut_allocate_object_desc_dbg(स्थिर अक्षर *module_name,
				       u32 line_number, u32 component_id);

#घोषणा acpi_ut_create_पूर्णांकernal_object(t) acpi_ut_create_पूर्णांकernal_object_dbg (_acpi_module_name,__LINE__,_COMPONENT,t)
#घोषणा acpi_ut_allocate_object_desc()  acpi_ut_allocate_object_desc_dbg (_acpi_module_name,__LINE__,_COMPONENT)

व्योम acpi_ut_delete_object_desc(जोड़ acpi_opeअक्रम_object *object);

u8 acpi_ut_valid_पूर्णांकernal_object(व्योम *object);

जोड़ acpi_opeअक्रम_object *acpi_ut_create_package_object(u32 count);

जोड़ acpi_opeअक्रम_object *acpi_ut_create_पूर्णांकeger_object(u64 value);

जोड़ acpi_opeअक्रम_object *acpi_ut_create_buffer_object(acpi_size buffer_size);

जोड़ acpi_opeअक्रम_object *acpi_ut_create_string_object(acpi_size string_size);

acpi_status
acpi_ut_get_object_size(जोड़ acpi_opeअक्रम_object *obj, acpi_size *obj_length);

/*
 * utosi - Support क्रम the _OSI predefined control method
 */
acpi_status acpi_ut_initialize_पूर्णांकerfaces(व्योम);

acpi_status acpi_ut_पूर्णांकerface_terminate(व्योम);

acpi_status acpi_ut_install_पूर्णांकerface(acpi_string पूर्णांकerface_name);

acpi_status acpi_ut_हटाओ_पूर्णांकerface(acpi_string पूर्णांकerface_name);

acpi_status acpi_ut_update_पूर्णांकerfaces(u8 action);

काष्ठा acpi_पूर्णांकerface_info *acpi_ut_get_पूर्णांकerface(acpi_string पूर्णांकerface_name);

acpi_status acpi_ut_osi_implementation(काष्ठा acpi_walk_state *walk_state);

/*
 * utpredef - support क्रम predefined names
 */
स्थिर जोड़ acpi_predefined_info *acpi_ut_get_next_predefined_method(स्थिर जोड़
								     acpi_predefined_info
								     *this_name);

स्थिर जोड़ acpi_predefined_info *acpi_ut_match_predefined_method(अक्षर *name);

व्योम acpi_ut_get_expected_वापस_types(अक्षर *buffer, u32 expected_btypes);

#अगर (defined ACPI_ASL_COMPILER || defined ACPI_HELP_APP)
स्थिर जोड़ acpi_predefined_info *acpi_ut_match_resource_name(अक्षर *name);

व्योम
acpi_ut_display_predefined_method(अक्षर *buffer,
				  स्थिर जोड़ acpi_predefined_info *this_name,
				  u8 multi_line);

u32 acpi_ut_get_resource_bit_width(अक्षर *buffer, u16 types);
#पूर्ण_अगर

/*
 * utstate - Generic state creation/cache routines
 */
व्योम
acpi_ut_push_generic_state(जोड़ acpi_generic_state **list_head,
			   जोड़ acpi_generic_state *state);

जोड़ acpi_generic_state *acpi_ut_pop_generic_state(जोड़ acpi_generic_state
						    **list_head);

जोड़ acpi_generic_state *acpi_ut_create_generic_state(व्योम);

काष्ठा acpi_thपढ़ो_state *acpi_ut_create_thपढ़ो_state(व्योम);

जोड़ acpi_generic_state *acpi_ut_create_update_state(जोड़ acpi_opeअक्रम_object
						      *object, u16 action);

जोड़ acpi_generic_state *acpi_ut_create_pkg_state(व्योम *पूर्णांकernal_object,
						   व्योम *बाह्यal_object,
						   u32 index);

acpi_status
acpi_ut_create_update_state_and_push(जोड़ acpi_opeअक्रम_object *object,
				     u16 action,
				     जोड़ acpi_generic_state **state_list);

जोड़ acpi_generic_state *acpi_ut_create_control_state(व्योम);

व्योम acpi_ut_delete_generic_state(जोड़ acpi_generic_state *state);

/*
 * uपंचांगath
 */
acpi_status
acpi_ut_भागide(u64 in_भागidend,
	       u64 in_भागisor, u64 *out_quotient, u64 *out_reमुख्यder);

acpi_status
acpi_ut_लघु_भागide(u64 in_भागidend,
		     u32 भागisor, u64 *out_quotient, u32 *out_reमुख्यder);

acpi_status
acpi_ut_लघु_multiply(u64 in_multiplicand, u32 multiplier, u64 *outproduct);

acpi_status acpi_ut_लघु_shअगरt_left(u64 opeअक्रम, u32 count, u64 *out_result);

acpi_status acpi_ut_लघु_shअगरt_right(u64 opeअक्रम, u32 count, u64 *out_result);

/*
 * uपंचांगisc
 */
स्थिर काष्ठा acpi_exception_info *acpi_ut_validate_exception(acpi_status
							     status);

u8 acpi_ut_is_pci_root_bridge(अक्षर *id);

#अगर (defined ACPI_ASL_COMPILER || defined ACPI_EXEC_APP || defined ACPI_NAMES_APP)
u8 acpi_ut_is_aml_table(काष्ठा acpi_table_header *table);
#पूर्ण_अगर

acpi_status
acpi_ut_walk_package_tree(जोड़ acpi_opeअक्रम_object *source_object,
			  व्योम *target_object,
			  acpi_pkg_callback walk_callback, व्योम *context);

/* Values क्रम Base above (16=Hex, 10=Decimal) */

#घोषणा ACPI_ANY_BASE        0

u32 acpi_ut_dword_byte_swap(u32 value);

व्योम acpi_ut_set_पूर्णांकeger_width(u8 revision);

#अगर_घोषित ACPI_DEBUG_OUTPUT
व्योम
acpi_ut_display_init_pathname(u8 type,
			      काष्ठा acpi_namespace_node *obj_handle,
			      स्थिर अक्षर *path);
#पूर्ण_अगर

/*
 * utownerid - Support क्रम Table/Method Owner IDs
 */
acpi_status acpi_ut_allocate_owner_id(acpi_owner_id *owner_id);

व्योम acpi_ut_release_owner_id(acpi_owner_id *owner_id);

/*
 * utresrc
 */
acpi_status
acpi_ut_walk_aml_resources(काष्ठा acpi_walk_state *walk_state,
			   u8 *aml,
			   acpi_size aml_length,
			   acpi_walk_aml_callback user_function,
			   व्योम **context);

acpi_status
acpi_ut_validate_resource(काष्ठा acpi_walk_state *walk_state,
			  व्योम *aml, u8 *वापस_index);

u32 acpi_ut_get_descriptor_length(व्योम *aml);

u16 acpi_ut_get_resource_length(व्योम *aml);

u8 acpi_ut_get_resource_header_length(व्योम *aml);

u8 acpi_ut_get_resource_type(व्योम *aml);

acpi_status
acpi_ut_get_resource_end_tag(जोड़ acpi_opeअक्रम_object *obj_desc, u8 **end_tag);

/*
 * utstring - String and अक्षरacter utilities
 */
व्योम acpi_ut_prपूर्णांक_string(अक्षर *string, u16 max_length);

#अगर defined ACPI_ASL_COMPILER || defined ACPI_EXEC_APP
व्योम ut_convert_backslashes(अक्षर *pathname);
#पूर्ण_अगर

व्योम acpi_ut_repair_name(अक्षर *name);

#अगर defined (ACPI_DEBUGGER) || defined (ACPI_APPLICATION) || defined (ACPI_DEBUG_OUTPUT)
u8 acpi_ut_safe_म_नकल(अक्षर *dest, acpi_size dest_size, अक्षर *source);

व्योम acpi_ut_safe_म_नकलन(अक्षर *dest, अक्षर *source, acpi_size dest_size);

u8 acpi_ut_safe_म_जोड़ो(अक्षर *dest, acpi_size dest_size, अक्षर *source);

u8
acpi_ut_safe_म_जोड़न(अक्षर *dest,
		     acpi_size dest_size,
		     अक्षर *source, acpi_size max_transfer_length);
#पूर्ण_अगर

/*
 * uपंचांगutex - mutex support
 */
acpi_status acpi_ut_mutex_initialize(व्योम);

व्योम acpi_ut_mutex_terminate(व्योम);

acpi_status acpi_ut_acquire_mutex(acpi_mutex_handle mutex_id);

acpi_status acpi_ut_release_mutex(acpi_mutex_handle mutex_id);

/*
 * utalloc - memory allocation and object caching
 */
acpi_status acpi_ut_create_caches(व्योम);

acpi_status acpi_ut_delete_caches(व्योम);

acpi_status acpi_ut_validate_buffer(काष्ठा acpi_buffer *buffer);

acpi_status
acpi_ut_initialize_buffer(काष्ठा acpi_buffer *buffer,
			  acpi_size required_length);

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
व्योम *acpi_ut_allocate_and_track(acpi_size size,
				 u32 component, स्थिर अक्षर *module, u32 line);

व्योम *acpi_ut_allocate_zeroed_and_track(acpi_size size,
					u32 component,
					स्थिर अक्षर *module, u32 line);

व्योम
acpi_ut_मुक्त_and_track(व्योम *address,
		       u32 component, स्थिर अक्षर *module, u32 line);

व्योम acpi_ut_dump_allocation_info(व्योम);

व्योम acpi_ut_dump_allocations(u32 component, स्थिर अक्षर *module);

acpi_status
acpi_ut_create_list(स्थिर अक्षर *list_name,
		    u16 object_size, काष्ठा acpi_memory_list **वापस_cache);

#पूर्ण_अगर				/* ACPI_DBG_TRACK_ALLOCATIONS */

/*
 * utaddress - address range check
 */
acpi_status
acpi_ut_add_address_range(acpi_adr_space_type space_id,
			  acpi_physical_address address,
			  u32 length, काष्ठा acpi_namespace_node *region_node);

व्योम
acpi_ut_हटाओ_address_range(acpi_adr_space_type space_id,
			     काष्ठा acpi_namespace_node *region_node);

u32
acpi_ut_check_address_range(acpi_adr_space_type space_id,
			    acpi_physical_address address, u32 length, u8 warn);

व्योम acpi_ut_delete_address_lists(व्योम);

/*
 * utxख_त्रुटि - various error/warning output functions
 */
ACPI_PRINTF_LIKE(5)
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_ut_predefined_warning(स्थिर अक्षर *module_name,
			   u32 line_number,
			   अक्षर *pathname,
			   u16 node_flags, स्थिर अक्षर *क्रमmat, ...);

ACPI_PRINTF_LIKE(5)
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_ut_predefined_info(स्थिर अक्षर *module_name,
			u32 line_number,
			अक्षर *pathname,
			u16 node_flags, स्थिर अक्षर *क्रमmat, ...);

ACPI_PRINTF_LIKE(5)
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_ut_predefined_bios_error(स्थिर अक्षर *module_name,
			      u32 line_number,
			      अक्षर *pathname,
			      u16 node_flags, स्थिर अक्षर *क्रमmat, ...);

व्योम
acpi_ut_prefixed_namespace_error(स्थिर अक्षर *module_name,
				 u32 line_number,
				 जोड़ acpi_generic_state *prefix_scope,
				 स्थिर अक्षर *पूर्णांकernal_name,
				 acpi_status lookup_status);

व्योम
acpi_ut_method_error(स्थिर अक्षर *module_name,
		     u32 line_number,
		     स्थिर अक्षर *message,
		     काष्ठा acpi_namespace_node *node,
		     स्थिर अक्षर *path, acpi_status lookup_status);

/*
 * Utility functions क्रम ACPI names and IDs
 */
स्थिर काष्ठा ah_predefined_name *acpi_ah_match_predefined_name(अक्षर *nameseg);

स्थिर काष्ठा ah_device_id *acpi_ah_match_hardware_id(अक्षर *hid);

स्थिर अक्षर *acpi_ah_match_uuid(u8 *data);

/*
 * utuuid -- UUID support functions
 */
#अगर (defined ACPI_ASL_COMPILER || defined ACPI_EXEC_APP || defined ACPI_HELP_APP)
व्योम acpi_ut_convert_string_to_uuid(अक्षर *in_string, u8 *uuid_buffer);
#पूर्ण_अगर

#पूर्ण_अगर				/* _ACUTILS_H */
