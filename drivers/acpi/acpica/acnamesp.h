<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acnamesp.h - Namespace subcomponent prototypes and defines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACNAMESP_H__
#घोषणा __ACNAMESP_H__

/* To search the entire name space, pass this as search_base */

#घोषणा ACPI_NS_ALL                 ((acpi_handle)0)

/*
 * Elements of acpi_ns_properties are bit signअगरicant
 * and should be one-to-one with values of acpi_object_type
 */
#घोषणा ACPI_NS_NORMAL              0
#घोषणा ACPI_NS_NEWSCOPE            1	/* a definition of this type खोलोs a name scope */
#घोषणा ACPI_NS_LOCAL               2	/* suppress search of enclosing scopes */

/* Flags क्रम acpi_ns_lookup, acpi_ns_search_and_enter */

#घोषणा ACPI_NS_NO_UPSEARCH         0
#घोषणा ACPI_NS_SEARCH_PARENT       0x0001
#घोषणा ACPI_NS_DONT_OPEN_SCOPE     0x0002
#घोषणा ACPI_NS_NO_PEER_SEARCH      0x0004
#घोषणा ACPI_NS_ERROR_IF_FOUND      0x0008
#घोषणा ACPI_NS_PREFIX_IS_SCOPE     0x0010
#घोषणा ACPI_NS_EXTERNAL            0x0020
#घोषणा ACPI_NS_TEMPORARY           0x0040
#घोषणा ACPI_NS_OVERRIDE_IF_FOUND   0x0080
#घोषणा ACPI_NS_EARLY_INIT          0x0100
#घोषणा ACPI_NS_PREFIX_MUST_EXIST   0x0200

/* Flags क्रम acpi_ns_walk_namespace */

#घोषणा ACPI_NS_WALK_NO_UNLOCK      0
#घोषणा ACPI_NS_WALK_UNLOCK         0x01
#घोषणा ACPI_NS_WALK_TEMP_NODES     0x02

/* Object is not a package element */

#घोषणा ACPI_NOT_PACKAGE_ELEMENT    ACPI_UINT32_MAX
#घोषणा ACPI_ALL_PACKAGE_ELEMENTS   (ACPI_UINT32_MAX-1)

/* Always emit warning message, not dependent on node flags */

#घोषणा ACPI_WARN_ALWAYS            0

/*
 * nsinit - Namespace initialization
 */
acpi_status acpi_ns_initialize_objects(व्योम);

acpi_status acpi_ns_initialize_devices(u32 flags);

acpi_status
acpi_ns_init_one_package(acpi_handle obj_handle,
			 u32 level, व्योम *context, व्योम **वापस_value);

/*
 * nsload -  Namespace loading
 */
acpi_status acpi_ns_load_namespace(व्योम);

acpi_status
acpi_ns_load_table(u32 table_index, काष्ठा acpi_namespace_node *node);

/*
 * nswalk - walk the namespace
 */
acpi_status
acpi_ns_walk_namespace(acpi_object_type type,
		       acpi_handle start_object,
		       u32 max_depth,
		       u32 flags,
		       acpi_walk_callback descending_callback,
		       acpi_walk_callback ascending_callback,
		       व्योम *context, व्योम **वापस_value);

काष्ठा acpi_namespace_node *acpi_ns_get_next_node(काष्ठा acpi_namespace_node
						  *parent,
						  काष्ठा acpi_namespace_node
						  *child);

काष्ठा acpi_namespace_node *acpi_ns_get_next_node_typed(acpi_object_type type,
							काष्ठा
							acpi_namespace_node
							*parent,
							काष्ठा
							acpi_namespace_node
							*child);

/*
 * nsparse - table parsing
 */
acpi_status
acpi_ns_parse_table(u32 table_index, काष्ठा acpi_namespace_node *start_node);

acpi_status
acpi_ns_execute_table(u32 table_index, काष्ठा acpi_namespace_node *start_node);

acpi_status
acpi_ns_one_complete_parse(u32 pass_number,
			   u32 table_index,
			   काष्ठा acpi_namespace_node *start_node);

/*
 * nsaccess - Top-level namespace access
 */
acpi_status acpi_ns_root_initialize(व्योम);

acpi_status
acpi_ns_lookup(जोड़ acpi_generic_state *scope_info,
	       अक्षर *name,
	       acpi_object_type type,
	       acpi_पूर्णांकerpreter_mode पूर्णांकerpreter_mode,
	       u32 flags,
	       काष्ठा acpi_walk_state *walk_state,
	       काष्ठा acpi_namespace_node **ret_node);

/*
 * nsalloc - Named object allocation/deallocation
 */
काष्ठा acpi_namespace_node *acpi_ns_create_node(u32 name);

व्योम acpi_ns_delete_node(काष्ठा acpi_namespace_node *node);

व्योम acpi_ns_हटाओ_node(काष्ठा acpi_namespace_node *node);

व्योम
acpi_ns_delete_namespace_subtree(काष्ठा acpi_namespace_node *parent_handle);

व्योम acpi_ns_delete_namespace_by_owner(acpi_owner_id owner_id);

व्योम acpi_ns_detach_object(काष्ठा acpi_namespace_node *node);

व्योम acpi_ns_delete_children(काष्ठा acpi_namespace_node *parent);

पूर्णांक acpi_ns_compare_names(अक्षर *name1, अक्षर *name2);

/*
 * nsconvert - Dynamic object conversion routines
 */
acpi_status
acpi_ns_convert_to_पूर्णांकeger(जोड़ acpi_opeअक्रम_object *original_object,
			   जोड़ acpi_opeअक्रम_object **वापस_object);

acpi_status
acpi_ns_convert_to_string(जोड़ acpi_opeअक्रम_object *original_object,
			  जोड़ acpi_opeअक्रम_object **वापस_object);

acpi_status
acpi_ns_convert_to_buffer(जोड़ acpi_opeअक्रम_object *original_object,
			  जोड़ acpi_opeअक्रम_object **वापस_object);

acpi_status
acpi_ns_convert_to_unicode(काष्ठा acpi_namespace_node *scope,
			   जोड़ acpi_opeअक्रम_object *original_object,
			   जोड़ acpi_opeअक्रम_object **वापस_object);

acpi_status
acpi_ns_convert_to_resource(काष्ठा acpi_namespace_node *scope,
			    जोड़ acpi_opeअक्रम_object *original_object,
			    जोड़ acpi_opeअक्रम_object **वापस_object);

acpi_status
acpi_ns_convert_to_reference(काष्ठा acpi_namespace_node *scope,
			     जोड़ acpi_opeअक्रम_object *original_object,
			     जोड़ acpi_opeअक्रम_object **वापस_object);

/*
 * nsdump - Namespace dump/prपूर्णांक utilities
 */
व्योम acpi_ns_dump_tables(acpi_handle search_base, u32 max_depth);

व्योम acpi_ns_dump_entry(acpi_handle handle, u32 debug_level);

व्योम
acpi_ns_dump_pathname(acpi_handle handle,
		      स्थिर अक्षर *msg, u32 level, u32 component);

व्योम acpi_ns_prपूर्णांक_pathname(u32 num_segments, स्थिर अक्षर *pathname);

acpi_status
acpi_ns_dump_one_object(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value);

व्योम
acpi_ns_dump_objects(acpi_object_type type,
		     u8 display_type,
		     u32 max_depth,
		     acpi_owner_id owner_id, acpi_handle start_handle);

व्योम
acpi_ns_dump_object_paths(acpi_object_type type,
			  u8 display_type,
			  u32 max_depth,
			  acpi_owner_id owner_id, acpi_handle start_handle);

/*
 * nseval - Namespace evaluation functions
 */
acpi_status acpi_ns_evaluate(काष्ठा acpi_evaluate_info *info);

/*
 * nsarguments - Argument count/type checking क्रम predefined/reserved names
 */
व्योम
acpi_ns_check_argument_count(अक्षर *pathname,
			     काष्ठा acpi_namespace_node *node,
			     u32 user_param_count,
			     स्थिर जोड़ acpi_predefined_info *info);

व्योम
acpi_ns_check_acpi_compliance(अक्षर *pathname,
			      काष्ठा acpi_namespace_node *node,
			      स्थिर जोड़ acpi_predefined_info *predefined);

व्योम acpi_ns_check_argument_types(काष्ठा acpi_evaluate_info *info);

/*
 * nspredef - Return value checking क्रम predefined/reserved names
 */
acpi_status
acpi_ns_check_वापस_value(काष्ठा acpi_namespace_node *node,
			   काष्ठा acpi_evaluate_info *info,
			   u32 user_param_count,
			   acpi_status वापस_status,
			   जोड़ acpi_opeअक्रम_object **वापस_object);

acpi_status
acpi_ns_check_object_type(काष्ठा acpi_evaluate_info *info,
			  जोड़ acpi_opeअक्रम_object **वापस_object_ptr,
			  u32 expected_btypes, u32 package_index);

/*
 * nsprepkg - Validation of predefined name packages
 */
acpi_status
acpi_ns_check_package(काष्ठा acpi_evaluate_info *info,
		      जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

/*
 * nsnames - Name and Scope manipulation
 */
u32 acpi_ns_खोलोs_scope(acpi_object_type type);

अक्षर *acpi_ns_get_बाह्यal_pathname(काष्ठा acpi_namespace_node *node);

u32
acpi_ns_build_normalized_path(काष्ठा acpi_namespace_node *node,
			      अक्षर *full_path, u32 path_size, u8 no_trailing);

व्योम acpi_ns_normalize_pathname(अक्षर *original_path);

अक्षर *acpi_ns_get_normalized_pathname(काष्ठा acpi_namespace_node *node,
				      u8 no_trailing);

अक्षर *acpi_ns_build_prefixed_pathname(जोड़ acpi_generic_state *prefix_scope,
				      स्थिर अक्षर *पूर्णांकernal_path);

अक्षर *acpi_ns_name_of_current_scope(काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ns_handle_to_name(acpi_handle target_handle, काष्ठा acpi_buffer *buffer);

acpi_status
acpi_ns_handle_to_pathname(acpi_handle target_handle,
			   काष्ठा acpi_buffer *buffer, u8 no_trailing);

u8
acpi_ns_pattern_match(काष्ठा acpi_namespace_node *obj_node, अक्षर *search_क्रम);

acpi_status
acpi_ns_get_node_unlocked(काष्ठा acpi_namespace_node *prefix_node,
			  स्थिर अक्षर *बाह्यal_pathname,
			  u32 flags, काष्ठा acpi_namespace_node **out_node);

acpi_status
acpi_ns_get_node(काष्ठा acpi_namespace_node *prefix_node,
		 स्थिर अक्षर *बाह्यal_pathname,
		 u32 flags, काष्ठा acpi_namespace_node **out_node);

acpi_size acpi_ns_get_pathname_length(काष्ठा acpi_namespace_node *node);

/*
 * nsobject - Object management क्रम namespace nodes
 */
acpi_status
acpi_ns_attach_object(काष्ठा acpi_namespace_node *node,
		      जोड़ acpi_opeअक्रम_object *object, acpi_object_type type);

जोड़ acpi_opeअक्रम_object *acpi_ns_get_attached_object(काष्ठा
						       acpi_namespace_node
						       *node);

जोड़ acpi_opeअक्रम_object *acpi_ns_get_secondary_object(जोड़
							acpi_opeअक्रम_object
							*obj_desc);

acpi_status
acpi_ns_attach_data(काष्ठा acpi_namespace_node *node,
		    acpi_object_handler handler, व्योम *data);

acpi_status
acpi_ns_detach_data(काष्ठा acpi_namespace_node *node,
		    acpi_object_handler handler);

acpi_status
acpi_ns_get_attached_data(काष्ठा acpi_namespace_node *node,
			  acpi_object_handler handler, व्योम **data);

/*
 * nsrepair - General वापस object repair क्रम all
 * predefined methods/objects
 */
acpi_status
acpi_ns_simple_repair(काष्ठा acpi_evaluate_info *info,
		      u32 expected_btypes,
		      u32 package_index,
		      जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

acpi_status
acpi_ns_wrap_with_package(काष्ठा acpi_evaluate_info *info,
			  जोड़ acpi_opeअक्रम_object *original_object,
			  जोड़ acpi_opeअक्रम_object **obj_desc_ptr);

acpi_status
acpi_ns_repair_null_element(काष्ठा acpi_evaluate_info *info,
			    u32 expected_btypes,
			    u32 package_index,
			    जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

व्योम
acpi_ns_हटाओ_null_elements(काष्ठा acpi_evaluate_info *info,
			     u8 package_type,
			     जोड़ acpi_opeअक्रम_object *obj_desc);

/*
 * nsrepair2 - Return object repair क्रम specअगरic
 * predefined methods/objects
 */
acpi_status
acpi_ns_complex_repairs(काष्ठा acpi_evaluate_info *info,
			काष्ठा acpi_namespace_node *node,
			acpi_status validate_status,
			जोड़ acpi_opeअक्रम_object **वापस_object_ptr);

/*
 * nssearch - Namespace searching and entry
 */
acpi_status
acpi_ns_search_and_enter(u32 entry_name,
			 काष्ठा acpi_walk_state *walk_state,
			 काष्ठा acpi_namespace_node *node,
			 acpi_पूर्णांकerpreter_mode पूर्णांकerpreter_mode,
			 acpi_object_type type,
			 u32 flags, काष्ठा acpi_namespace_node **ret_node);

acpi_status
acpi_ns_search_one_scope(u32 entry_name,
			 काष्ठा acpi_namespace_node *node,
			 acpi_object_type type,
			 काष्ठा acpi_namespace_node **ret_node);

व्योम
acpi_ns_install_node(काष्ठा acpi_walk_state *walk_state,
		     काष्ठा acpi_namespace_node *parent_node,
		     काष्ठा acpi_namespace_node *node, acpi_object_type type);

/*
 * nsutils - Utility functions
 */
acpi_object_type acpi_ns_get_type(काष्ठा acpi_namespace_node *node);

u32 acpi_ns_local(acpi_object_type type);

व्योम
acpi_ns_prपूर्णांक_node_pathname(काष्ठा acpi_namespace_node *node, स्थिर अक्षर *msg);

acpi_status acpi_ns_build_पूर्णांकernal_name(काष्ठा acpi_namestring_info *info);

व्योम acpi_ns_get_पूर्णांकernal_name_length(काष्ठा acpi_namestring_info *info);

acpi_status
acpi_ns_पूर्णांकernalize_name(स्थिर अक्षर *करोtted_name, अक्षर **converted_name);

acpi_status
acpi_ns_बाह्यalize_name(u32 पूर्णांकernal_name_length,
			 स्थिर अक्षर *पूर्णांकernal_name,
			 u32 * converted_name_length, अक्षर **converted_name);

काष्ठा acpi_namespace_node *acpi_ns_validate_handle(acpi_handle handle);

व्योम acpi_ns_terminate(व्योम);

#पूर्ण_अगर				/* __ACNAMESP_H__ */
