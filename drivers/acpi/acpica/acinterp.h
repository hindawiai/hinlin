<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acपूर्णांकerp.h - Interpreter subcomponent prototypes and defines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACINTERP_H__
#घोषणा __ACINTERP_H__

#घोषणा ACPI_WALK_OPERANDS          (&(walk_state->opeअक्रमs [walk_state->num_opeअक्रमs -1]))

/* Macros क्रम tables used क्रम debug output */

#घोषणा ACPI_EXD_OFFSET(f)          (u8) ACPI_OFFSET (जोड़ acpi_opeअक्रम_object,f)
#घोषणा ACPI_EXD_NSOFFSET(f)        (u8) ACPI_OFFSET (काष्ठा acpi_namespace_node,f)
#घोषणा ACPI_EXD_TABLE_SIZE(name)   (माप(name) / माप (काष्ठा acpi_exdump_info))

/*
 * If possible, pack the following काष्ठाures to byte alignment, since we
 * करोn't care about perक्रमmance क्रम debug output. Two हालs where we cannot
 * pack the काष्ठाures:
 *
 * 1) Hardware करोes not support misaligned memory transfers
 * 2) Compiler करोes not support poपूर्णांकers within packed काष्ठाures
 */
#अगर (!defined(ACPI_MISALIGNMENT_NOT_SUPPORTED) && !defined(ACPI_PACKED_POINTERS_NOT_SUPPORTED))
#आशय pack(1)
#पूर्ण_अगर

प्रकार स्थिर काष्ठा acpi_exdump_info अणु
	u8 opcode;
	u8 offset;
	स्थिर अक्षर *name;

पूर्ण acpi_exdump_info;

/* Values क्रम the Opcode field above */

#घोषणा ACPI_EXD_INIT                   0
#घोषणा ACPI_EXD_TYPE                   1
#घोषणा ACPI_EXD_UINT8                  2
#घोषणा ACPI_EXD_UINT16                 3
#घोषणा ACPI_EXD_UINT32                 4
#घोषणा ACPI_EXD_UINT64                 5
#घोषणा ACPI_EXD_LITERAL                6
#घोषणा ACPI_EXD_POINTER                7
#घोषणा ACPI_EXD_ADDRESS                8
#घोषणा ACPI_EXD_STRING                 9
#घोषणा ACPI_EXD_BUFFER                 10
#घोषणा ACPI_EXD_PACKAGE                11
#घोषणा ACPI_EXD_FIELD                  12
#घोषणा ACPI_EXD_REFERENCE              13
#घोषणा ACPI_EXD_LIST                   14	/* Opeअक्रम object list */
#घोषणा ACPI_EXD_HDLR_LIST              15	/* Address Handler list */
#घोषणा ACPI_EXD_RGN_LIST               16	/* Region list */
#घोषणा ACPI_EXD_NODE                   17	/* Namespace Node */

/* restore शेष alignment */

#आशय pack()

/*
 * exconvrt - object conversion
 */
acpi_status
acpi_ex_convert_to_पूर्णांकeger(जोड़ acpi_opeअक्रम_object *obj_desc,
			   जोड़ acpi_opeअक्रम_object **result_desc,
			   u32 implicit_conversion);

acpi_status
acpi_ex_convert_to_buffer(जोड़ acpi_opeअक्रम_object *obj_desc,
			  जोड़ acpi_opeअक्रम_object **result_desc);

acpi_status
acpi_ex_convert_to_string(जोड़ acpi_opeअक्रम_object *obj_desc,
			  जोड़ acpi_opeअक्रम_object **result_desc, u32 type);

/* Types क्रम ->String conversion */

#घोषणा ACPI_EXPLICIT_BYTE_COPY         0x00000000
#घोषणा ACPI_EXPLICIT_CONVERT_HEX       0x00000001
#घोषणा ACPI_IMPLICIT_CONVERT_HEX       0x00000002
#घोषणा ACPI_EXPLICIT_CONVERT_DECIMAL   0x00000003

acpi_status
acpi_ex_convert_to_target_type(acpi_object_type destination_type,
			       जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object **result_desc,
			       काष्ठा acpi_walk_state *walk_state);

/*
 * exdebug - AML debug object
 */
व्योम
acpi_ex_करो_debug_object(जोड़ acpi_opeअक्रम_object *source_desc,
			u32 level, u32 index);

व्योम
acpi_ex_start_trace_method(काष्ठा acpi_namespace_node *method_node,
			   जोड़ acpi_opeअक्रम_object *obj_desc,
			   काष्ठा acpi_walk_state *walk_state);

व्योम
acpi_ex_stop_trace_method(काष्ठा acpi_namespace_node *method_node,
			  जोड़ acpi_opeअक्रम_object *obj_desc,
			  काष्ठा acpi_walk_state *walk_state);

व्योम
acpi_ex_start_trace_opcode(जोड़ acpi_parse_object *op,
			   काष्ठा acpi_walk_state *walk_state);

व्योम
acpi_ex_stop_trace_opcode(जोड़ acpi_parse_object *op,
			  काष्ठा acpi_walk_state *walk_state);

व्योम
acpi_ex_trace_poपूर्णांक(acpi_trace_event_type type,
		    u8 begin, u8 *aml, अक्षर *pathname);

/*
 * exfield - ACPI AML (p-code) execution - field manipulation
 */
acpi_status
acpi_ex_get_protocol_buffer_length(u32 protocol_id, u32 *वापस_length);

acpi_status
acpi_ex_common_buffer_setup(जोड़ acpi_opeअक्रम_object *obj_desc,
			    u32 buffer_length, u32 * datum_count);

acpi_status
acpi_ex_ग_लिखो_with_update_rule(जोड़ acpi_opeअक्रम_object *obj_desc,
			       u64 mask,
			       u64 field_value, u32 field_datum_byte_offset);

व्योम
acpi_ex_get_buffer_datum(u64 *datum,
			 व्योम *buffer,
			 u32 buffer_length,
			 u32 byte_granularity, u32 buffer_offset);

व्योम
acpi_ex_set_buffer_datum(u64 merged_datum,
			 व्योम *buffer,
			 u32 buffer_length,
			 u32 byte_granularity, u32 buffer_offset);

acpi_status
acpi_ex_पढ़ो_data_from_field(काष्ठा acpi_walk_state *walk_state,
			     जोड़ acpi_opeअक्रम_object *obj_desc,
			     जोड़ acpi_opeअक्रम_object **ret_buffer_desc);

acpi_status
acpi_ex_ग_लिखो_data_to_field(जोड़ acpi_opeअक्रम_object *source_desc,
			    जोड़ acpi_opeअक्रम_object *obj_desc,
			    जोड़ acpi_opeअक्रम_object **result_desc);

/*
 * exfldio - low level field I/O
 */
acpi_status
acpi_ex_extract_from_field(जोड़ acpi_opeअक्रम_object *obj_desc,
			   व्योम *buffer, u32 buffer_length);

acpi_status
acpi_ex_insert_पूर्णांकo_field(जोड़ acpi_opeअक्रम_object *obj_desc,
			  व्योम *buffer, u32 buffer_length);

acpi_status
acpi_ex_access_region(जोड़ acpi_opeअक्रम_object *obj_desc,
		      u32 field_datum_byte_offset, u64 *value, u32 पढ़ो_ग_लिखो);

/*
 * exmisc - misc support routines
 */
acpi_status
acpi_ex_get_object_reference(जोड़ acpi_opeअक्रम_object *obj_desc,
			     जोड़ acpi_opeअक्रम_object **वापस_desc,
			     काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_concat_ढाँचा(जोड़ acpi_opeअक्रम_object *obj_desc,
			जोड़ acpi_opeअक्रम_object *obj_desc2,
			जोड़ acpi_opeअक्रम_object **actual_वापस_desc,
			काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_करो_concatenate(जोड़ acpi_opeअक्रम_object *obj_desc,
		       जोड़ acpi_opeअक्रम_object *obj_desc2,
		       जोड़ acpi_opeअक्रम_object **actual_वापस_desc,
		       काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_करो_logical_numeric_op(u16 opcode,
			      u64 पूर्णांकeger0, u64 पूर्णांकeger1, u8 *logical_result);

acpi_status
acpi_ex_करो_logical_op(u16 opcode,
		      जोड़ acpi_opeअक्रम_object *opeअक्रम0,
		      जोड़ acpi_opeअक्रम_object *opeअक्रम1, u8 *logical_result);

u64 acpi_ex_करो_math_op(u16 opcode, u64 opeअक्रम0, u64 opeअक्रम1);

acpi_status acpi_ex_create_mutex(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_create_processor(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_create_घातer_resource(काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_create_region(u8 * aml_start,
		      u32 aml_length,
		      u8 region_space, काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_create_event(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_create_alias(काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_create_method(u8 * aml_start,
		      u32 aml_length, काष्ठा acpi_walk_state *walk_state);

/*
 * exconfig - dynamic table load/unload
 */
acpi_status
acpi_ex_load_op(जोड़ acpi_opeअक्रम_object *obj_desc,
		जोड़ acpi_opeअक्रम_object *target,
		काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_load_table_op(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_opeअक्रम_object **वापस_desc);

acpi_status acpi_ex_unload_table(जोड़ acpi_opeअक्रम_object *ddb_handle);

/*
 * exmutex - mutex support
 */
acpi_status
acpi_ex_acquire_mutex(जोड़ acpi_opeअक्रम_object *समय_desc,
		      जोड़ acpi_opeअक्रम_object *obj_desc,
		      काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_acquire_mutex_object(u16 समयout,
			     जोड़ acpi_opeअक्रम_object *obj_desc,
			     acpi_thपढ़ो_id thपढ़ो_id);

acpi_status
acpi_ex_release_mutex(जोड़ acpi_opeअक्रम_object *obj_desc,
		      काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_release_mutex_object(जोड़ acpi_opeअक्रम_object *obj_desc);

व्योम acpi_ex_release_all_mutexes(काष्ठा acpi_thपढ़ो_state *thपढ़ो);

व्योम acpi_ex_unlink_mutex(जोड़ acpi_opeअक्रम_object *obj_desc);

/*
 * exprep - ACPI AML execution - prep utilities
 */
acpi_status
acpi_ex_prep_common_field_object(जोड़ acpi_opeअक्रम_object *obj_desc,
				 u8 field_flags,
				 u8 field_attribute,
				 u32 field_bit_position, u32 field_bit_length);

acpi_status acpi_ex_prep_field_value(काष्ठा acpi_create_field_info *info);

/*
 * exserial - field_unit support क्रम serial address spaces
 */
acpi_status
acpi_ex_पढ़ो_serial_bus(जोड़ acpi_opeअक्रम_object *obj_desc,
			जोड़ acpi_opeअक्रम_object **वापस_buffer);

acpi_status
acpi_ex_ग_लिखो_serial_bus(जोड़ acpi_opeअक्रम_object *source_desc,
			 जोड़ acpi_opeअक्रम_object *obj_desc,
			 जोड़ acpi_opeअक्रम_object **वापस_buffer);

acpi_status
acpi_ex_पढ़ो_gpio(जोड़ acpi_opeअक्रम_object *obj_desc, व्योम *buffer);

acpi_status
acpi_ex_ग_लिखो_gpio(जोड़ acpi_opeअक्रम_object *source_desc,
		   जोड़ acpi_opeअक्रम_object *obj_desc,
		   जोड़ acpi_opeअक्रम_object **वापस_buffer);

/*
 * exप्रणाली - Interface to OS services
 */
acpi_status
acpi_ex_प्रणाली_करो_notअगरy_op(जोड़ acpi_opeअक्रम_object *value,
			    जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status acpi_ex_प्रणाली_करो_sleep(u64 समय);

acpi_status acpi_ex_प्रणाली_करो_stall(u32 समय);

acpi_status acpi_ex_प्रणाली_संकेत_event(जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status
acpi_ex_प्रणाली_रुको_event(जोड़ acpi_opeअक्रम_object *समय,
			  जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status acpi_ex_प्रणाली_reset_event(जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status
acpi_ex_प्रणाली_रुको_semaphore(acpi_semaphore semaphore, u16 समयout);

acpi_status acpi_ex_प्रणाली_रुको_mutex(acpi_mutex mutex, u16 समयout);

/*
 * exoparg1 - ACPI AML execution, 1 opeअक्रम
 */
acpi_status acpi_ex_opcode_0A_0T_1R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_1A_0T_0R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_1A_0T_1R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_1A_1T_1R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_1A_1T_0R(काष्ठा acpi_walk_state *walk_state);

/*
 * exoparg2 - ACPI AML execution, 2 opeअक्रमs
 */
acpi_status acpi_ex_opcode_2A_0T_0R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_2A_0T_1R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_2A_1T_1R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_2A_2T_1R(काष्ठा acpi_walk_state *walk_state);

/*
 * exoparg3 - ACPI AML execution, 3 opeअक्रमs
 */
acpi_status acpi_ex_opcode_3A_0T_0R(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ex_opcode_3A_1T_1R(काष्ठा acpi_walk_state *walk_state);

/*
 * exoparg6 - ACPI AML execution, 6 opeअक्रमs
 */
acpi_status acpi_ex_opcode_6A_0T_1R(काष्ठा acpi_walk_state *walk_state);

/*
 * exresolv - Object resolution and get value functions
 */
acpi_status
acpi_ex_resolve_to_value(जोड़ acpi_opeअक्रम_object **stack_ptr,
			 काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_resolve_multiple(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_opeअक्रम_object *opeअक्रम,
			 acpi_object_type *वापस_type,
			 जोड़ acpi_opeअक्रम_object **वापस_desc);

/*
 * exresnte - resolve namespace node
 */
acpi_status
acpi_ex_resolve_node_to_value(काष्ठा acpi_namespace_node **stack_ptr,
			      काष्ठा acpi_walk_state *walk_state);

/*
 * exresop - resolve opeअक्रम to value
 */
acpi_status
acpi_ex_resolve_opeअक्रमs(u16 opcode,
			 जोड़ acpi_opeअक्रम_object **stack_ptr,
			 काष्ठा acpi_walk_state *walk_state);

/*
 * exdump - Interpreter debug output routines
 */
व्योम acpi_ex_dump_opeअक्रम(जोड़ acpi_opeअक्रम_object *obj_desc, u32 depth);

व्योम
acpi_ex_dump_opeअक्रमs(जोड़ acpi_opeअक्रम_object **opeअक्रमs,
		      स्थिर अक्षर *opcode_name, u32 num_opcodes);

व्योम
acpi_ex_dump_object_descriptor(जोड़ acpi_opeअक्रम_object *object, u32 flags);

व्योम acpi_ex_dump_namespace_node(काष्ठा acpi_namespace_node *node, u32 flags);

/*
 * exnames - AML namestring support
 */
acpi_status
acpi_ex_get_name_string(acpi_object_type data_type,
			u8 * in_aml_address,
			अक्षर **out_name_string, u32 * out_name_length);

/*
 * exstore - Object store support
 */
acpi_status
acpi_ex_store(जोड़ acpi_opeअक्रम_object *val_desc,
	      जोड़ acpi_opeअक्रम_object *dest_desc,
	      काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_store_object_to_node(जोड़ acpi_opeअक्रम_object *source_desc,
			     काष्ठा acpi_namespace_node *node,
			     काष्ठा acpi_walk_state *walk_state,
			     u8 implicit_conversion);

/*
 * exstoren - resolve/store object
 */
acpi_status
acpi_ex_resolve_object(जोड़ acpi_opeअक्रम_object **source_desc_ptr,
		       acpi_object_type target_type,
		       काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ex_store_object_to_object(जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object *dest_desc,
			       जोड़ acpi_opeअक्रम_object **new_desc,
			       काष्ठा acpi_walk_state *walk_state);

/*
 * exstorob - store object - buffer/string
 */
acpi_status
acpi_ex_store_buffer_to_buffer(जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object *target_desc);

acpi_status
acpi_ex_store_string_to_string(जोड़ acpi_opeअक्रम_object *source_desc,
			       जोड़ acpi_opeअक्रम_object *target_desc);

/*
 * excopy - object copy
 */
acpi_status
acpi_ex_copy_पूर्णांकeger_to_index_field(जोड़ acpi_opeअक्रम_object *source_desc,
				    जोड़ acpi_opeअक्रम_object *target_desc);

acpi_status
acpi_ex_copy_पूर्णांकeger_to_bank_field(जोड़ acpi_opeअक्रम_object *source_desc,
				   जोड़ acpi_opeअक्रम_object *target_desc);

acpi_status
acpi_ex_copy_data_to_named_field(जोड़ acpi_opeअक्रम_object *source_desc,
				 काष्ठा acpi_namespace_node *node);

acpi_status
acpi_ex_copy_पूर्णांकeger_to_buffer_field(जोड़ acpi_opeअक्रम_object *source_desc,
				     जोड़ acpi_opeअक्रम_object *target_desc);

/*
 * exutils - पूर्णांकerpreter/scanner utilities
 */
व्योम acpi_ex_enter_पूर्णांकerpreter(व्योम);

व्योम acpi_ex_निकास_पूर्णांकerpreter(व्योम);

u8 acpi_ex_truncate_क्रम32bit_table(जोड़ acpi_opeअक्रम_object *obj_desc);

व्योम acpi_ex_acquire_global_lock(u32 rule);

व्योम acpi_ex_release_global_lock(u32 rule);

व्योम acpi_ex_eisa_id_to_string(अक्षर *dest, u64 compressed_id);

व्योम acpi_ex_पूर्णांकeger_to_string(अक्षर *dest, u64 value);

व्योम acpi_ex_pci_cls_to_string(अक्षर *dest, u8 class_code[3]);

u8 acpi_is_valid_space_id(u8 space_id);

/*
 * exregion - शेष op_region handlers
 */
acpi_status
acpi_ex_प्रणाली_memory_space_handler(u32 function,
				    acpi_physical_address address,
				    u32 bit_width,
				    u64 *value,
				    व्योम *handler_context,
				    व्योम *region_context);

acpi_status
acpi_ex_प्रणाली_io_space_handler(u32 function,
				acpi_physical_address address,
				u32 bit_width,
				u64 *value,
				व्योम *handler_context, व्योम *region_context);

acpi_status
acpi_ex_pci_config_space_handler(u32 function,
				 acpi_physical_address address,
				 u32 bit_width,
				 u64 *value,
				 व्योम *handler_context, व्योम *region_context);

acpi_status
acpi_ex_cmos_space_handler(u32 function,
			   acpi_physical_address address,
			   u32 bit_width,
			   u64 *value,
			   व्योम *handler_context, व्योम *region_context);

acpi_status
acpi_ex_pci_bar_space_handler(u32 function,
			      acpi_physical_address address,
			      u32 bit_width,
			      u64 *value,
			      व्योम *handler_context, व्योम *region_context);

acpi_status
acpi_ex_embedded_controller_space_handler(u32 function,
					  acpi_physical_address address,
					  u32 bit_width,
					  u64 *value,
					  व्योम *handler_context,
					  व्योम *region_context);

acpi_status
acpi_ex_sm_bus_space_handler(u32 function,
			     acpi_physical_address address,
			     u32 bit_width,
			     u64 *value,
			     व्योम *handler_context, व्योम *region_context);

acpi_status
acpi_ex_data_table_space_handler(u32 function,
				 acpi_physical_address address,
				 u32 bit_width,
				 u64 *value,
				 व्योम *handler_context, व्योम *region_context);

#पूर्ण_अगर				/* __INTERP_H__ */
