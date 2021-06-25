<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: aclocal.h - Internal data types used across the ACPI subप्रणाली
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACLOCAL_H__
#घोषणा __ACLOCAL_H__

/* acpisrc:काष्ठा_defs -- क्रम acpisrc conversion */

#घोषणा ACPI_SERIALIZED                 0xFF

प्रकार u32 acpi_mutex_handle;
#घोषणा ACPI_GLOBAL_LOCK                (acpi_semaphore) (-1)

/* Total number of aml opcodes defined */

#घोषणा AML_NUM_OPCODES                 0x83

/* Forward declarations */

काष्ठा acpi_walk_state;
काष्ठा acpi_obj_mutex;
जोड़ acpi_parse_object;

/*****************************************************************************
 *
 * Mutex प्रकारs and काष्ठाs
 *
 ****************************************************************************/

/*
 * Predefined handles क्रम the mutex objects used within the subप्रणाली
 * All mutex objects are स्वतःmatically created by acpi_ut_mutex_initialize.
 *
 * The acquire/release ordering protocol is implied via this list. Mutexes
 * with a lower value must be acquired beक्रमe mutexes with a higher value.
 *
 * NOTE: any changes here must be reflected in the acpi_gbl_mutex_names
 * table below also!
 */
#घोषणा ACPI_MTX_INTERPRETER            0	/* AML Interpreter, मुख्य lock */
#घोषणा ACPI_MTX_NAMESPACE              1	/* ACPI Namespace */
#घोषणा ACPI_MTX_TABLES                 2	/* Data क्रम ACPI tables */
#घोषणा ACPI_MTX_EVENTS                 3	/* Data क्रम ACPI events */
#घोषणा ACPI_MTX_CACHES                 4	/* Internal caches, general purposes */
#घोषणा ACPI_MTX_MEMORY                 5	/* Debug memory tracking lists */

#घोषणा ACPI_MAX_MUTEX                  5
#घोषणा ACPI_NUM_MUTEX                  (ACPI_MAX_MUTEX+1)

/* Lock काष्ठाure क्रम पढ़ोer/ग_लिखोr पूर्णांकerfaces */

काष्ठा acpi_rw_lock अणु
	acpi_mutex ग_लिखोr_mutex;
	acpi_mutex पढ़ोer_mutex;
	u32 num_पढ़ोers;
पूर्ण;

/*
 * Predefined handles क्रम spinlocks used within the subप्रणाली.
 * These spinlocks are created by acpi_ut_mutex_initialize
 */
#घोषणा ACPI_LOCK_GPES                  0
#घोषणा ACPI_LOCK_HARDWARE              1

#घोषणा ACPI_MAX_LOCK                   1
#घोषणा ACPI_NUM_LOCK                   (ACPI_MAX_LOCK+1)

/* This Thपढ़ो ID means that the mutex is not in use (unlocked) */

#घोषणा ACPI_MUTEX_NOT_ACQUIRED         ((acpi_thपढ़ो_id) 0)

/* This Thपढ़ो ID means an invalid thपढ़ो ID */

#अगर_घोषित ACPI_OS_INVALID_THREAD_ID
#घोषणा ACPI_INVALID_THREAD_ID          ACPI_OS_INVALID_THREAD_ID
#अन्यथा
#घोषणा ACPI_INVALID_THREAD_ID          ((acpi_thपढ़ो_id) 0xFFFFFFFF)
#पूर्ण_अगर

/* Table क्रम the global mutexes */

काष्ठा acpi_mutex_info अणु
	acpi_mutex mutex;
	u32 use_count;
	acpi_thपढ़ो_id thपढ़ो_id;
पूर्ण;

/* Lock flag parameter क्रम various पूर्णांकerfaces */

#घोषणा ACPI_MTX_DO_NOT_LOCK            0
#घोषणा ACPI_MTX_LOCK                   1

/* Field access granularities */

#घोषणा ACPI_FIELD_BYTE_GRANULARITY     1
#घोषणा ACPI_FIELD_WORD_GRANULARITY     2
#घोषणा ACPI_FIELD_DWORD_GRANULARITY    4
#घोषणा ACPI_FIELD_QWORD_GRANULARITY    8

#घोषणा ACPI_ENTRY_NOT_FOUND            शून्य

/*****************************************************************************
 *
 * Namespace प्रकारs and काष्ठाs
 *
 ****************************************************************************/

/* Operational modes of the AML पूर्णांकerpreter/scanner */

प्रकार क्रमागत अणु
	ACPI_IMODE_LOAD_PASS1 = 0x01,
	ACPI_IMODE_LOAD_PASS2 = 0x02,
	ACPI_IMODE_EXECUTE = 0x03
पूर्ण acpi_पूर्णांकerpreter_mode;

/*
 * The Namespace Node describes a named object that appears in the AML.
 * descriptor_type is used to dअगरferentiate between पूर्णांकernal descriptors.
 *
 * The node is optimized क्रम both 32-bit and 64-bit platक्रमms:
 * 20 bytes क्रम the 32-bit हाल, 32 bytes क्रम the 64-bit हाल.
 *
 * Note: The descriptor_type and Type fields must appear in the identical
 * position in both the काष्ठा acpi_namespace_node and जोड़ acpi_opeअक्रम_object
 * काष्ठाures.
 */
काष्ठा acpi_namespace_node अणु
	जोड़ acpi_opeअक्रम_object *object;	/* Interpreter object */
	u8 descriptor_type;	/* Dअगरferentiate object descriptor types */
	u8 type;		/* ACPI Type associated with this name */
	u16 flags;		/* Miscellaneous flags */
	जोड़ acpi_name_जोड़ name;	/* ACPI Name, always 4 अक्षरs per ACPI spec */
	काष्ठा acpi_namespace_node *parent;	/* Parent node */
	काष्ठा acpi_namespace_node *child;	/* First child */
	काष्ठा acpi_namespace_node *peer;	/* First peer */
	acpi_owner_id owner_id;	/* Node creator */

	/*
	 * The following fields are used by the ASL compiler and disassembler only
	 */
#अगर_घोषित ACPI_LARGE_NAMESPACE_NODE
	जोड़ acpi_parse_object *op;
	व्योम *method_locals;
	व्योम *method_args;
	u32 value;
	u32 length;
	u8 arg_count;

#पूर्ण_अगर
पूर्ण;

/* Namespace Node flags */

#घोषणा ANOBJ_RESERVED                  0x01	/* Available क्रम use */
#घोषणा ANOBJ_TEMPORARY                 0x02	/* Node is create by a method and is temporary */
#घोषणा ANOBJ_METHOD_ARG                0x04	/* Node is a method argument */
#घोषणा ANOBJ_METHOD_LOCAL              0x08	/* Node is a method local */
#घोषणा ANOBJ_SUBTREE_HAS_INI           0x10	/* Used to optimize device initialization */
#घोषणा ANOBJ_EVALUATED                 0x20	/* Set on first evaluation of node */
#घोषणा ANOBJ_ALLOCATED_BUFFER          0x40	/* Method AML buffer is dynamic (install_method) */
#घोषणा ANOBJ_NODE_EARLY_INIT           0x80	/* acpi_exec only: Node was create via init file (-fi) */

#घोषणा ANOBJ_IS_EXTERNAL               0x08	/* iASL only: This object created via External() */
#घोषणा ANOBJ_METHOD_NO_RETVAL          0x10	/* iASL only: Method has no वापस value */
#घोषणा ANOBJ_METHOD_SOME_NO_RETVAL     0x20	/* iASL only: Method has at least one वापस value */
#घोषणा ANOBJ_IS_REFERENCED             0x80	/* iASL only: Object was referenced */

/* Internal ACPI table management - master table list */

काष्ठा acpi_table_list अणु
	काष्ठा acpi_table_desc *tables;	/* Table descriptor array */
	u32 current_table_count;	/* Tables currently in the array */
	u32 max_table_count;	/* Max tables array will hold */
	u8 flags;
पूर्ण;

/* Flags क्रम above */

#घोषणा ACPI_ROOT_ORIGIN_UNKNOWN        (0)	/* ~ORIGIN_ALLOCATED */
#घोषणा ACPI_ROOT_ORIGIN_ALLOCATED      (1)
#घोषणा ACPI_ROOT_ALLOW_RESIZE          (2)

/* List to manage incoming ACPI tables */

काष्ठा acpi_new_table_desc अणु
	काष्ठा acpi_table_header *table;
	काष्ठा acpi_new_table_desc *next;
पूर्ण;

/* Predefined table indexes */

#घोषणा ACPI_INVALID_TABLE_INDEX        (0xFFFFFFFF)

काष्ठा acpi_find_context अणु
	अक्षर *search_क्रम;
	acpi_handle *list;
	u32 *count;
पूर्ण;

काष्ठा acpi_ns_search_data अणु
	काष्ठा acpi_namespace_node *node;
पूर्ण;

/* Object types used during package copies */

#घोषणा ACPI_COPY_TYPE_SIMPLE           0
#घोषणा ACPI_COPY_TYPE_PACKAGE          1

/* Info काष्ठाure used to convert बाह्यal<->पूर्णांकernal namestrings */

काष्ठा acpi_namestring_info अणु
	स्थिर अक्षर *बाह्यal_name;
	स्थिर अक्षर *next_बाह्यal_अक्षर;
	अक्षर *पूर्णांकernal_name;
	u32 length;
	u32 num_segments;
	u32 num_carats;
	u8 fully_qualअगरied;
पूर्ण;

/* Field creation info */

काष्ठा acpi_create_field_info अणु
	काष्ठा acpi_namespace_node *region_node;
	काष्ठा acpi_namespace_node *field_node;
	काष्ठा acpi_namespace_node *रेजिस्टर_node;
	काष्ठा acpi_namespace_node *data_रेजिस्टर_node;
	काष्ठा acpi_namespace_node *connection_node;
	u8 *resource_buffer;
	u32 bank_value;
	u32 field_bit_position;
	u32 field_bit_length;
	u16 resource_length;
	u16 pin_number_index;
	u8 field_flags;
	u8 attribute;
	u8 field_type;
	u8 access_length;
पूर्ण;

प्रकार
acpi_status (*acpi_पूर्णांकernal_method) (काष्ठा acpi_walk_state * walk_state);

/*
 * Biपंचांगapped ACPI types. Used पूर्णांकernally only
 */
#घोषणा ACPI_BTYPE_ANY                  0x00000000
#घोषणा ACPI_BTYPE_INTEGER              0x00000001
#घोषणा ACPI_BTYPE_STRING               0x00000002
#घोषणा ACPI_BTYPE_BUFFER               0x00000004
#घोषणा ACPI_BTYPE_PACKAGE              0x00000008
#घोषणा ACPI_BTYPE_FIELD_UNIT           0x00000010
#घोषणा ACPI_BTYPE_DEVICE               0x00000020
#घोषणा ACPI_BTYPE_EVENT                0x00000040
#घोषणा ACPI_BTYPE_METHOD               0x00000080
#घोषणा ACPI_BTYPE_MUTEX                0x00000100
#घोषणा ACPI_BTYPE_REGION               0x00000200
#घोषणा ACPI_BTYPE_POWER                0x00000400
#घोषणा ACPI_BTYPE_PROCESSOR            0x00000800
#घोषणा ACPI_BTYPE_THERMAL              0x00001000
#घोषणा ACPI_BTYPE_BUFFER_FIELD         0x00002000
#घोषणा ACPI_BTYPE_DDB_HANDLE           0x00004000
#घोषणा ACPI_BTYPE_DEBUG_OBJECT         0x00008000
#घोषणा ACPI_BTYPE_REFERENCE_OBJECT     0x00010000	/* From Index(), ref_of(), etc (type6_opcodes) */
#घोषणा ACPI_BTYPE_RESOURCE             0x00020000
#घोषणा ACPI_BTYPE_NAMED_REFERENCE      0x00040000	/* Generic unresolved Name or Namepath */

#घोषणा ACPI_BTYPE_COMPUTE_DATA         (ACPI_BTYPE_INTEGER | ACPI_BTYPE_STRING | ACPI_BTYPE_BUFFER)

#घोषणा ACPI_BTYPE_DATA                 (ACPI_BTYPE_COMPUTE_DATA  | ACPI_BTYPE_PACKAGE)

	/* Used by Copy, de_ref_of, Store, Prपूर्णांकf, Fम_लिखो */

#घोषणा ACPI_BTYPE_DATA_REFERENCE       (ACPI_BTYPE_DATA | ACPI_BTYPE_REFERENCE_OBJECT | ACPI_BTYPE_DDB_HANDLE)
#घोषणा ACPI_BTYPE_DEVICE_OBJECTS       (ACPI_BTYPE_DEVICE | ACPI_BTYPE_THERMAL | ACPI_BTYPE_PROCESSOR)
#घोषणा ACPI_BTYPE_OBJECTS_AND_REFS     0x0001FFFF	/* ARG or LOCAL */
#घोषणा ACPI_BTYPE_ALL_OBJECTS          0x0000FFFF

#आशय pack(1)

/*
 * Inक्रमmation काष्ठाure क्रम ACPI predefined names.
 * Each entry in the table contains the following items:
 *
 * name                 - The ACPI reserved name
 * param_count          - Number of arguments to the method
 * expected_वापस_btypes - Allowed type(s) क्रम the वापस value
 */
काष्ठा acpi_name_info अणु
	अक्षर name[ACPI_NAMESEG_SIZE];
	u16 argument_list;
	u8 expected_btypes;
पूर्ण;

/*
 * Secondary inक्रमmation काष्ठाures क्रम ACPI predefined objects that वापस
 * package objects. This काष्ठाure appears as the next entry in the table
 * after the NAME_INFO काष्ठाure above.
 *
 * The reason क्रम this is to minimize the size of the predefined name table.
 */

/*
 * Used क्रम ACPI_PTYPE1_FIXED, ACPI_PTYPE1_VAR, ACPI_PTYPE2,
 * ACPI_PTYPE2_MIN, ACPI_PTYPE2_PKG_COUNT, ACPI_PTYPE2_COUNT,
 * ACPI_PTYPE2_FIX_VAR
 */
काष्ठा acpi_package_info अणु
	u8 type;
	u8 object_type1;
	u8 count1;
	u8 object_type2;
	u8 count2;
	u16 reserved;
पूर्ण;

/* Used क्रम ACPI_PTYPE2_FIXED */

काष्ठा acpi_package_info2 अणु
	u8 type;
	u8 count;
	u8 object_type[4];
	u8 reserved;
पूर्ण;

/* Used क्रम ACPI_PTYPE1_OPTION */

काष्ठा acpi_package_info3 अणु
	u8 type;
	u8 count;
	u8 object_type[2];
	u8 tail_object_type;
	u16 reserved;
पूर्ण;

काष्ठा acpi_package_info4 अणु
	u8 type;
	u8 object_type1;
	u8 count1;
	u8 sub_object_types;
	u8 pkg_count;
	u16 reserved;
पूर्ण;

जोड़ acpi_predefined_info अणु
	काष्ठा acpi_name_info info;
	काष्ठा acpi_package_info ret_info;
	काष्ठा acpi_package_info2 ret_info2;
	काष्ठा acpi_package_info3 ret_info3;
	काष्ठा acpi_package_info4 ret_info4;
पूर्ण;

/* Reset to शेष packing */

#आशय pack()

/* Return object स्वतः-repair info */

प्रकार acpi_status (*acpi_object_converter) (काष्ठा acpi_namespace_node *
					      scope,
					      जोड़ acpi_opeअक्रम_object *
					      original_object,
					      जोड़ acpi_opeअक्रम_object **
					      converted_object);

काष्ठा acpi_simple_repair_info अणु
	अक्षर name[ACPI_NAMESEG_SIZE];
	u32 unexpected_btypes;
	u32 package_index;
	acpi_object_converter object_converter;
पूर्ण;

/*
 * Biपंचांगapped वापस value types
 * Note: the actual data types must be contiguous, a loop in nspredef.c
 * depends on this.
 */
#घोषणा ACPI_RTYPE_ANY                  0x00
#घोषणा ACPI_RTYPE_NONE                 0x01
#घोषणा ACPI_RTYPE_INTEGER              0x02
#घोषणा ACPI_RTYPE_STRING               0x04
#घोषणा ACPI_RTYPE_BUFFER               0x08
#घोषणा ACPI_RTYPE_PACKAGE              0x10
#घोषणा ACPI_RTYPE_REFERENCE            0x20
#घोषणा ACPI_RTYPE_ALL                  0x3F

#घोषणा ACPI_NUM_RTYPES                 5	/* Number of actual object types */

/* Info क्रम running the _REG methods */

काष्ठा acpi_reg_walk_info अणु
	u32 function;
	u32 reg_run_count;
	acpi_adr_space_type space_id;
पूर्ण;

/*****************************************************************************
 *
 * Event प्रकारs and काष्ठाs
 *
 ****************************************************************************/

/* Dispatch info क्रम each host-installed SCI handler */

काष्ठा acpi_sci_handler_info अणु
	काष्ठा acpi_sci_handler_info *next;
	acpi_sci_handler address;	/* Address of handler */
	व्योम *context;		/* Context to be passed to handler */
पूर्ण;

/* Dispatch info क्रम each GPE -- either a method or handler, cannot be both */

काष्ठा acpi_gpe_handler_info अणु
	acpi_gpe_handler address;	/* Address of handler, अगर any */
	व्योम *context;		/* Context to be passed to handler */
	काष्ठा acpi_namespace_node *method_node;	/* Method node क्रम this GPE level (saved) */
	u8 original_flags;	/* Original (pre-handler) GPE info */
	u8 originally_enabled;	/* True अगर GPE was originally enabled */
पूर्ण;

/* Notअगरy info क्रम implicit notअगरy, multiple device objects */

काष्ठा acpi_gpe_notअगरy_info अणु
	काष्ठा acpi_namespace_node *device_node;	/* Device to be notअगरied */
	काष्ठा acpi_gpe_notअगरy_info *next;
पूर्ण;

/*
 * GPE dispatch info. At any समय, the GPE can have at most one type
 * of dispatch - Method, Handler, or Implicit Notअगरy.
 */
जोड़ acpi_gpe_dispatch_info अणु
	काष्ठा acpi_namespace_node *method_node;	/* Method node क्रम this GPE level */
	काष्ठा acpi_gpe_handler_info *handler;  /* Installed GPE handler */
	काष्ठा acpi_gpe_notअगरy_info *notअगरy_list;	/* List of _PRW devices क्रम implicit notअगरies */
पूर्ण;

/*
 * Inक्रमmation about a GPE, one per each GPE in an array.
 * NOTE: Important to keep this काष्ठा as small as possible.
 */
काष्ठा acpi_gpe_event_info अणु
	जोड़ acpi_gpe_dispatch_info dispatch;	/* Either Method, Handler, or notअगरy_list */
	काष्ठा acpi_gpe_रेजिस्टर_info *रेजिस्टर_info;	/* Backpoपूर्णांकer to रेजिस्टर info */
	u8 flags;		/* Misc info about this GPE */
	u8 gpe_number;		/* This GPE */
	u8 runसमय_count;	/* References to a run GPE */
	u8 disable_क्रम_dispatch;	/* Masked during dispatching */
पूर्ण;

/* GPE रेजिस्टर address */

काष्ठा acpi_gpe_address अणु
	u8 space_id;	/* Address space where the रेजिस्टर exists */
	u64 address;	/* 64-bit address of the रेजिस्टर */
पूर्ण;

/* Inक्रमmation about a GPE रेजिस्टर pair, one per each status/enable pair in an array */

काष्ठा acpi_gpe_रेजिस्टर_info अणु
	काष्ठा acpi_gpe_address status_address;	/* Address of status reg */
	काष्ठा acpi_gpe_address enable_address;	/* Address of enable reg */
	u16 base_gpe_number;	/* Base GPE number क्रम this रेजिस्टर */
	u8 enable_क्रम_wake;	/* GPEs to keep enabled when sleeping */
	u8 enable_क्रम_run;	/* GPEs to keep enabled when running */
	u8 mask_क्रम_run;	/* GPEs to keep masked when running */
	u8 enable_mask;		/* Current mask of enabled GPEs */
पूर्ण;

/*
 * Inक्रमmation about a GPE रेजिस्टर block, one per each installed block --
 * GPE0, GPE1, and one per each installed GPE Block Device.
 */
काष्ठा acpi_gpe_block_info अणु
	काष्ठा acpi_namespace_node *node;
	काष्ठा acpi_gpe_block_info *previous;
	काष्ठा acpi_gpe_block_info *next;
	काष्ठा acpi_gpe_xrupt_info *xrupt_block;	/* Backpoपूर्णांकer to पूर्णांकerrupt block */
	काष्ठा acpi_gpe_रेजिस्टर_info *रेजिस्टर_info;	/* One per GPE रेजिस्टर pair */
	काष्ठा acpi_gpe_event_info *event_info;	/* One क्रम each GPE */
	u64 address;		/* Base address of the block */
	u32 रेजिस्टर_count;	/* Number of रेजिस्टर pairs in block */
	u16 gpe_count;		/* Number of inभागidual GPEs in block */
	u16 block_base_number;	/* Base GPE number क्रम this block */
	u8 space_id;
	u8 initialized;		/* TRUE अगर this block is initialized */
पूर्ण;

/* Inक्रमmation about GPE पूर्णांकerrupt handlers, one per each पूर्णांकerrupt level used क्रम GPEs */

काष्ठा acpi_gpe_xrupt_info अणु
	काष्ठा acpi_gpe_xrupt_info *previous;
	काष्ठा acpi_gpe_xrupt_info *next;
	काष्ठा acpi_gpe_block_info *gpe_block_list_head;	/* List of GPE blocks क्रम this xrupt */
	u32 पूर्णांकerrupt_number;	/* System पूर्णांकerrupt number */
पूर्ण;

काष्ठा acpi_gpe_walk_info अणु
	काष्ठा acpi_namespace_node *gpe_device;
	काष्ठा acpi_gpe_block_info *gpe_block;
	u16 count;
	acpi_owner_id owner_id;
	u8 execute_by_owner_id;
पूर्ण;

काष्ठा acpi_gpe_device_info अणु
	u32 index;
	u32 next_block_base_index;
	acpi_status status;
	काष्ठा acpi_namespace_node *gpe_device;
पूर्ण;

प्रकार acpi_status (*acpi_gpe_callback) (काष्ठा acpi_gpe_xrupt_info *
					  gpe_xrupt_info,
					  काष्ठा acpi_gpe_block_info *
					  gpe_block, व्योम *context);

/* Inक्रमmation about each particular fixed event */

काष्ठा acpi_fixed_event_handler अणु
	acpi_event_handler handler;	/* Address of handler. */
	व्योम *context;		/* Context to be passed to handler */
पूर्ण;

काष्ठा acpi_fixed_event_info अणु
	u8 status_रेजिस्टर_id;
	u8 enable_रेजिस्टर_id;
	u16 status_bit_mask;
	u16 enable_bit_mask;
पूर्ण;

/* Inक्रमmation used during field processing */

काष्ठा acpi_field_info अणु
	u8 skip_field;
	u8 field_flag;
	u32 pkg_length;
पूर्ण;

/*****************************************************************************
 *
 * Generic "state" object क्रम stacks
 *
 ****************************************************************************/

#घोषणा ACPI_CONTROL_NORMAL                  0xC0
#घोषणा ACPI_CONTROL_CONDITIONAL_EXECUTING   0xC1
#घोषणा ACPI_CONTROL_PREDICATE_EXECUTING     0xC2
#घोषणा ACPI_CONTROL_PREDICATE_FALSE         0xC3
#घोषणा ACPI_CONTROL_PREDICATE_TRUE          0xC4

#घोषणा ACPI_STATE_COMMON \
	व्योम                            *next; \
	u8                              descriptor_type; /* To dअगरferentiate various पूर्णांकernal objs */\
	u8                              flags; \
	u16                             value; \
	u16                             state;

	/* There are 2 bytes available here until the next natural alignment boundary */

काष्ठा acpi_common_state अणु
ACPI_STATE_COMMONपूर्ण;

/*
 * Update state - used to traverse complex objects such as packages
 */
काष्ठा acpi_update_state अणु
	ACPI_STATE_COMMON जोड़ acpi_opeअक्रम_object *object;
पूर्ण;

/*
 * Pkg state - used to traverse nested package काष्ठाures
 */
काष्ठा acpi_pkg_state अणु
	ACPI_STATE_COMMON u32 index;
	जोड़ acpi_opeअक्रम_object *source_object;
	जोड़ acpi_opeअक्रम_object *dest_object;
	काष्ठा acpi_walk_state *walk_state;
	व्योम *this_target_obj;
	u32 num_packages;
पूर्ण;

/*
 * Control state - one per अगर/अन्यथा and जबतक स्थिरructs.
 * Allows nesting of these स्थिरructs
 */
काष्ठा acpi_control_state अणु
	ACPI_STATE_COMMON u16 opcode;
	जोड़ acpi_parse_object *predicate_op;
	u8 *aml_predicate_start;	/* Start of अगर/जबतक predicate */
	u8 *package_end;	/* End of अगर/जबतक block */
	u64 loop_समयout;	/* While() loop समयout */
पूर्ण;

/*
 * Scope state - current scope during namespace lookups
 */
काष्ठा acpi_scope_state अणु
	ACPI_STATE_COMMON काष्ठा acpi_namespace_node *node;
पूर्ण;

काष्ठा acpi_pscope_state अणु
	ACPI_STATE_COMMON u32 arg_count;	/* Number of fixed arguments */
	जोड़ acpi_parse_object *op;	/* Current op being parsed */
	u8 *arg_end;		/* Current argument end */
	u8 *pkg_end;		/* Current package end */
	u32 arg_list;		/* Next argument to parse */
पूर्ण;

/*
 * Thपढ़ो state - one per thपढ़ो across multiple walk states. Multiple walk
 * states are created when there are nested control methods executing.
 */
काष्ठा acpi_thपढ़ो_state अणु
	ACPI_STATE_COMMON u8 current_sync_level;	/* Mutex Sync (nested acquire) level */
	काष्ठा acpi_walk_state *walk_state_list;	/* Head of list of walk_states क्रम this thपढ़ो */
	जोड़ acpi_opeअक्रम_object *acquired_mutex_list;	/* List of all currently acquired mutexes */
	acpi_thपढ़ो_id thपढ़ो_id;	/* Running thपढ़ो ID */
पूर्ण;

/*
 * Result values - used to accumulate the results of nested
 * AML arguments
 */
काष्ठा acpi_result_values अणु
	ACPI_STATE_COMMON
	    जोड़ acpi_opeअक्रम_object *obj_desc[ACPI_RESULTS_FRAME_OBJ_NUM];
पूर्ण;

प्रकार
acpi_status (*acpi_parse_करोwnwards) (काष्ठा acpi_walk_state * walk_state,
				     जोड़ acpi_parse_object ** out_op);

प्रकार
acpi_status (*acpi_parse_upwards) (काष्ठा acpi_walk_state * walk_state);

/* Global handlers क्रम AML Notअगरies */

काष्ठा acpi_global_notअगरy_handler अणु
	acpi_notअगरy_handler handler;
	व्योम *context;
पूर्ण;

/*
 * Notअगरy info - used to pass info to the deferred notअगरy
 * handler/dispatcher.
 */
काष्ठा acpi_notअगरy_info अणु
	ACPI_STATE_COMMON u8 handler_list_id;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *handler_list_head;
	काष्ठा acpi_global_notअगरy_handler *global;
पूर्ण;

/* Generic state is जोड़ of काष्ठाs above */

जोड़ acpi_generic_state अणु
	काष्ठा acpi_common_state common;
	काष्ठा acpi_control_state control;
	काष्ठा acpi_update_state update;
	काष्ठा acpi_scope_state scope;
	काष्ठा acpi_pscope_state parse_scope;
	काष्ठा acpi_pkg_state pkg;
	काष्ठा acpi_thपढ़ो_state thपढ़ो;
	काष्ठा acpi_result_values results;
	काष्ठा acpi_notअगरy_info notअगरy;
पूर्ण;

/*****************************************************************************
 *
 * Interpreter प्रकारs and काष्ठाs
 *
 ****************************************************************************/

प्रकार
acpi_status (*acpi_execute_op) (काष्ठा acpi_walk_state * walk_state);

/* Address Range info block */

काष्ठा acpi_address_range अणु
	काष्ठा acpi_address_range *next;
	काष्ठा acpi_namespace_node *region_node;
	acpi_physical_address start_address;
	acpi_physical_address end_address;
पूर्ण;

/*****************************************************************************
 *
 * Parser प्रकारs and काष्ठाs
 *
 ****************************************************************************/

/*
 * AML opcode, name, and argument layout
 */
काष्ठा acpi_opcode_info अणु
#अगर defined(ACPI_DISASSEMBLER) || defined(ACPI_DEBUG_OUTPUT)
	अक्षर *name;		/* Opcode name (disassembler/debug only) */
#पूर्ण_अगर
	u32 parse_args;		/* Grammar/Parse समय arguments */
	u32 runसमय_args;	/* Interpret समय arguments */
	u16 flags;		/* Misc flags */
	u8 object_type;		/* Corresponding पूर्णांकernal object type */
	u8 class;		/* Opcode class */
	u8 type;		/* Opcode type */
पूर्ण;

/* Value associated with the parse object */

जोड़ acpi_parse_value अणु
	u64 पूर्णांकeger;		/* Integer स्थिरant (Up to 64 bits) */
	u32 size;		/* bytelist or field size */
	अक्षर *string;		/* शून्य terminated string */
	u8 *buffer;		/* buffer or string */
	अक्षर *name;		/* शून्य terminated string */
	जोड़ acpi_parse_object *arg;	/* arguments and contained ops */
पूर्ण;

#अगर defined(ACPI_DISASSEMBLER) || defined(ACPI_DEBUG_OUTPUT)
#घोषणा ACPI_DISASM_ONLY_MEMBERS(a)     a;
#अन्यथा
#घोषणा ACPI_DISASM_ONLY_MEMBERS(a)
#पूर्ण_अगर

#अगर defined(ACPI_ASL_COMPILER)
#घोषणा ACPI_CONVERTER_ONLY_MEMBERS(a)  a;
#अन्यथा
#घोषणा ACPI_CONVERTER_ONLY_MEMBERS(a)
#पूर्ण_अगर

#घोषणा ACPI_PARSE_COMMON \
	जोड़ acpi_parse_object         *parent;            /* Parent op */\
	u8                              descriptor_type;    /* To dअगरferentiate various पूर्णांकernal objs */\
	u8                              flags;              /* Type of Op */\
	u16                             aml_opcode;         /* AML opcode */\
	u8                              *aml;               /* Address of declaration in AML */\
	जोड़ acpi_parse_object         *next;              /* Next op */\
	काष्ठा acpi_namespace_node      *node;              /* For use by पूर्णांकerpreter */\
	जोड़ acpi_parse_value          value;              /* Value or args associated with the opcode */\
	u8                              arg_list_length;    /* Number of elements in the arg list */\
	 ACPI_DISASM_ONLY_MEMBERS (\
	u16                             disयंत्र_flags;       /* Used during AML disassembly */\
	u8                              disयंत्र_opcode;      /* Subtype used क्रम disassembly */\
	अक्षर                            *चालक_symbol;   /* Used क्रम C-style चालक name strings */\
	अक्षर                            aml_op_name[16])    /* Op name (debug only) */\
	 ACPI_CONVERTER_ONLY_MEMBERS (\
	अक्षर                            *अंतरभूत_comment;    /* Inline comment */\
	अक्षर                            *end_node_comment;  /* End of node comment */\
	अक्षर                            *name_comment;      /* Comment associated with the first parameter of the name node */\
	अक्षर                            *बंद_brace_comment; /* Comments that come after पूर्ण on the same as पूर्ण */\
	काष्ठा acpi_comment_node        *comment_list;      /* comments that appears beक्रमe this node */\
	काष्ठा acpi_comment_node        *end_blk_comment;   /* comments that at the end of a block but beक्रमe ) or पूर्ण */\
	अक्षर                            *cv_filename;       /* Filename associated with this node. Used क्रम ASL/ASL+ converter */\
	अक्षर                            *cv_parent_filename)	/* Parent filename associated with this node. Used क्रम ASL/ASL+ converter */

/* categories of comments */

प्रकार क्रमागत अणु
	STANDARD_COMMENT = 1,
	INLINE_COMMENT,
	ENDNODE_COMMENT,
	OPENBRACE_COMMENT,
	CLOSE_BRACE_COMMENT,
	STD_DEFBLK_COMMENT,
	END_DEFBLK_COMMENT,
	खाताNAME_COMMENT,
	PARENTखाताNAME_COMMENT,
	ENDBLK_COMMENT,
	INCLUDE_COMMENT
पूर्ण asl_comment_types;

/* Internal opcodes क्रम disयंत्र_opcode field above */

#घोषणा ACPI_DASM_BUFFER                0x00	/* Buffer is a simple data buffer */
#घोषणा ACPI_DASM_RESOURCE              0x01	/* Buffer is a Resource Descriptor */
#घोषणा ACPI_DASM_STRING                0x02	/* Buffer is a ASCII string */
#घोषणा ACPI_DASM_UNICODE               0x03	/* Buffer is a Unicode string */
#घोषणा ACPI_DASM_PLD_METHOD            0x04	/* Buffer is a _PLD method bit-packed buffer */
#घोषणा ACPI_DASM_UUID                  0x05	/* Buffer is a UUID/GUID */
#घोषणा ACPI_DASM_EISAID                0x06	/* Integer is an EISAID */
#घोषणा ACPI_DASM_MATCHOP               0x07	/* Parent opcode is a Match() चालक */
#घोषणा ACPI_DASM_LNOT_PREFIX           0x08	/* Start of a Lnot_equal (etc.) pair of opcodes */
#घोषणा ACPI_DASM_LNOT_SUFFIX           0x09	/* End  of a Lnot_equal (etc.) pair of opcodes */
#घोषणा ACPI_DASM_HID_STRING            0x0A	/* String is a _HID or _CID */
#घोषणा ACPI_DASM_IGNORE_SINGLE         0x0B	/* Ignore the opcode but not it's children */
#घोषणा ACPI_DASM_SWITCH                0x0C	/* While is a Switch */
#घोषणा ACPI_DASM_SWITCH_PREDICATE      0x0D	/* Object is a predicate क्रम a Switch or Case block */
#घोषणा ACPI_DASM_CASE                  0x0E	/* If/Else is a Case in a Switch/Case block */
#घोषणा ACPI_DASM_DEFAULT               0x0F	/* Else is a Default in a Switch/Case block */

/*
 * List काष्ठा used in the -ca option
 */
काष्ठा acpi_comment_node अणु
	अक्षर *comment;
	काष्ठा acpi_comment_node *next;
पूर्ण;

काष्ठा acpi_comment_addr_node अणु
	u8 *addr;
	काष्ठा acpi_comment_addr_node *next;
पूर्ण;

/*
 * File node - used क्रम "Include" चालक file stack and
 * dependency tree क्रम the -ca option
 */
काष्ठा acpi_file_node अणु
	व्योम *file;
	अक्षर *filename;
	अक्षर *file_start;	/* Poपूर्णांकs to AML and indicates when the AML क्रम this particular file starts. */
	अक्षर *file_end;		/* Poपूर्णांकs to AML and indicates when the AML क्रम this particular file ends. */
	काष्ठा acpi_file_node *next;
	काष्ठा acpi_file_node *parent;
	u8 include_written;
	काष्ठा acpi_comment_node *include_comment;
पूर्ण;

/*
 * Generic operation (क्रम example:  If, While, Store)
 */
काष्ठा acpi_parse_obj_common अणु
ACPI_PARSE_COMMONपूर्ण;

/*
 * Extended Op क्रम named ops (Scope, Method, etc.), deferred ops (Methods and op_regions),
 * and bytelists.
 */
काष्ठा acpi_parse_obj_named अणु
	ACPI_PARSE_COMMON अक्षर *path;
	u8 *data;		/* AML body or bytelist data */
	u32 length;		/* AML length */
	u32 name;		/* 4-byte name or zero अगर no name */
पूर्ण;

/* This version is used by the iASL compiler only */

#घोषणा ACPI_MAX_PARSEOP_NAME       20

काष्ठा acpi_parse_obj_asl अणु
	ACPI_PARSE_COMMON जोड़ acpi_parse_object *child;
	जोड़ acpi_parse_object *parent_method;
	अक्षर *filename;
	u8 file_changed;
	अक्षर *parent_filename;
	अक्षर *बाह्यal_name;
	अक्षर *namepath;
	अक्षर name_seg[4];
	u32 extra_value;
	u32 column;
	u32 line_number;
	u32 logical_line_number;
	u32 logical_byte_offset;
	u32 end_line;
	u32 end_logical_line;
	u32 acpi_btype;
	u32 aml_length;
	u32 aml_subtree_length;
	u32 final_aml_length;
	u32 final_aml_offset;
	u32 compile_flags;
	u16 parse_opcode;
	u8 aml_opcode_length;
	u8 aml_pkg_len_bytes;
	u8 extra;
	अक्षर parse_op_name[ACPI_MAX_PARSEOP_NAME];
पूर्ण;

जोड़ acpi_parse_object अणु
	काष्ठा acpi_parse_obj_common common;
	काष्ठा acpi_parse_obj_named named;
	काष्ठा acpi_parse_obj_asl asl;
पूर्ण;

काष्ठा asl_comment_state अणु
	u8 comment_type;
	u32 spaces_beक्रमe;
	जोड़ acpi_parse_object *latest_parse_op;
	जोड़ acpi_parse_object *parsing_paren_brace_node;
	u8 capture_comments;
पूर्ण;

/*
 * Parse state - one state per parser invocation and each control
 * method.
 */
काष्ठा acpi_parse_state अणु
	u8 *aml_start;		/* First AML byte */
	u8 *aml;		/* Next AML byte */
	u8 *aml_end;		/* (last + 1) AML byte */
	u8 *pkg_start;		/* Current package begin */
	u8 *pkg_end;		/* Current package end */
	जोड़ acpi_parse_object *start_op;	/* Root of parse tree */
	काष्ठा acpi_namespace_node *start_node;
	जोड़ acpi_generic_state *scope;	/* Current scope */
	जोड़ acpi_parse_object *start_scope;
	u32 aml_size;
पूर्ण;

/* Parse object flags */

#घोषणा ACPI_PARSEOP_GENERIC                0x01
#घोषणा ACPI_PARSEOP_NAMED_OBJECT           0x02
#घोषणा ACPI_PARSEOP_DEFERRED               0x04
#घोषणा ACPI_PARSEOP_BYTELIST               0x08
#घोषणा ACPI_PARSEOP_IN_STACK               0x10
#घोषणा ACPI_PARSEOP_TARGET                 0x20
#घोषणा ACPI_PARSEOP_IN_CACHE               0x80

/* Parse object disयंत्र_flags */

#घोषणा ACPI_PARSEOP_IGNORE                 0x0001
#घोषणा ACPI_PARSEOP_PARAMETER_LIST         0x0002
#घोषणा ACPI_PARSEOP_EMPTY_TERMLIST         0x0004
#घोषणा ACPI_PARSEOP_PREDEFINED_CHECKED     0x0008
#घोषणा ACPI_PARSEOP_CLOSING_PAREN          0x0010
#घोषणा ACPI_PARSEOP_COMPOUND_ASSIGNMENT    0x0020
#घोषणा ACPI_PARSEOP_ASSIGNMENT             0x0040
#घोषणा ACPI_PARSEOP_ELSEIF                 0x0080
#घोषणा ACPI_PARSEOP_LEGACY_ASL_ONLY        0x0100

/*****************************************************************************
 *
 * Hardware (ACPI रेजिस्टरs) and PNP
 *
 ****************************************************************************/

काष्ठा acpi_bit_रेजिस्टर_info अणु
	u8 parent_रेजिस्टर;
	u8 bit_position;
	u16 access_bit_mask;
पूर्ण;

/*
 * Some ACPI रेजिस्टरs have bits that must be ignored -- meaning that they
 * must be preserved.
 */
#घोषणा ACPI_PM1_STATUS_PRESERVED_BITS          0x0800	/* Bit 11 */

/* Write-only bits must be zeroed by software */

#घोषणा ACPI_PM1_CONTROL_WRITEONLY_BITS         0x2004	/* Bits 13, 2 */

/* For control रेजिस्टरs, both ignored and reserved bits must be preserved */

/*
 * For PM1 control, the SCI enable bit (bit 0, SCI_EN) is defined by the
 * ACPI specअगरication to be a "preserved" bit - "OSPM always preserves this
 * bit position", section 4.7.3.2.1. However, on some machines the OS must
 * ग_लिखो a one to this bit after resume क्रम the machine to work properly.
 * To enable this, we no दीर्घer attempt to preserve this bit. No machines
 * are known to fail अगर the bit is not preserved. (May 2009)
 */
#घोषणा ACPI_PM1_CONTROL_IGNORED_BITS           0x0200	/* Bit 9 */
#घोषणा ACPI_PM1_CONTROL_RESERVED_BITS          0xC1F8	/* Bits 14-15, 3-8 */
#घोषणा ACPI_PM1_CONTROL_PRESERVED_BITS \
	       (ACPI_PM1_CONTROL_IGNORED_BITS | ACPI_PM1_CONTROL_RESERVED_BITS)

#घोषणा ACPI_PM2_CONTROL_PRESERVED_BITS         0xFFFFFFFE	/* All except bit 0 */

/*
 * Register IDs
 * These are the full ACPI रेजिस्टरs
 */
#घोषणा ACPI_REGISTER_PM1_STATUS                0x01
#घोषणा ACPI_REGISTER_PM1_ENABLE                0x02
#घोषणा ACPI_REGISTER_PM1_CONTROL               0x03
#घोषणा ACPI_REGISTER_PM2_CONTROL               0x04
#घोषणा ACPI_REGISTER_PM_TIMER                  0x05
#घोषणा ACPI_REGISTER_PROCESSOR_BLOCK           0x06
#घोषणा ACPI_REGISTER_SMI_COMMAND_BLOCK         0x07

/* Masks used to access the bit_रेजिस्टरs */

#घोषणा ACPI_BITMASK_TIMER_STATUS               0x0001
#घोषणा ACPI_BITMASK_BUS_MASTER_STATUS          0x0010
#घोषणा ACPI_BITMASK_GLOBAL_LOCK_STATUS         0x0020
#घोषणा ACPI_BITMASK_POWER_BUTTON_STATUS        0x0100
#घोषणा ACPI_BITMASK_SLEEP_BUTTON_STATUS        0x0200
#घोषणा ACPI_BITMASK_RT_CLOCK_STATUS            0x0400
#घोषणा ACPI_BITMASK_PCIEXP_WAKE_STATUS         0x4000	/* ACPI 3.0 */
#घोषणा ACPI_BITMASK_WAKE_STATUS                0x8000

#घोषणा ACPI_BITMASK_ALL_FIXED_STATUS           (\
	ACPI_BITMASK_TIMER_STATUS          | \
	ACPI_BITMASK_BUS_MASTER_STATUS     | \
	ACPI_BITMASK_GLOBAL_LOCK_STATUS    | \
	ACPI_BITMASK_POWER_BUTTON_STATUS   | \
	ACPI_BITMASK_SLEEP_BUTTON_STATUS   | \
	ACPI_BITMASK_RT_CLOCK_STATUS       | \
	ACPI_BITMASK_PCIEXP_WAKE_STATUS    | \
	ACPI_BITMASK_WAKE_STATUS)

#घोषणा ACPI_BITMASK_TIMER_ENABLE               0x0001
#घोषणा ACPI_BITMASK_GLOBAL_LOCK_ENABLE         0x0020
#घोषणा ACPI_BITMASK_POWER_BUTTON_ENABLE        0x0100
#घोषणा ACPI_BITMASK_SLEEP_BUTTON_ENABLE        0x0200
#घोषणा ACPI_BITMASK_RT_CLOCK_ENABLE            0x0400
#घोषणा ACPI_BITMASK_PCIEXP_WAKE_DISABLE        0x4000	/* ACPI 3.0 */

#घोषणा ACPI_BITMASK_SCI_ENABLE                 0x0001
#घोषणा ACPI_BITMASK_BUS_MASTER_RLD             0x0002
#घोषणा ACPI_BITMASK_GLOBAL_LOCK_RELEASE        0x0004
#घोषणा ACPI_BITMASK_SLEEP_TYPE                 0x1C00
#घोषणा ACPI_BITMASK_SLEEP_ENABLE               0x2000

#घोषणा ACPI_BITMASK_ARB_DISABLE                0x0001

/* Raw bit position of each bit_रेजिस्टर */

#घोषणा ACPI_BITPOSITION_TIMER_STATUS           0x00
#घोषणा ACPI_BITPOSITION_BUS_MASTER_STATUS      0x04
#घोषणा ACPI_BITPOSITION_GLOBAL_LOCK_STATUS     0x05
#घोषणा ACPI_BITPOSITION_POWER_BUTTON_STATUS    0x08
#घोषणा ACPI_BITPOSITION_SLEEP_BUTTON_STATUS    0x09
#घोषणा ACPI_BITPOSITION_RT_CLOCK_STATUS        0x0A
#घोषणा ACPI_BITPOSITION_PCIEXP_WAKE_STATUS     0x0E	/* ACPI 3.0 */
#घोषणा ACPI_BITPOSITION_WAKE_STATUS            0x0F

#घोषणा ACPI_BITPOSITION_TIMER_ENABLE           0x00
#घोषणा ACPI_BITPOSITION_GLOBAL_LOCK_ENABLE     0x05
#घोषणा ACPI_BITPOSITION_POWER_BUTTON_ENABLE    0x08
#घोषणा ACPI_BITPOSITION_SLEEP_BUTTON_ENABLE    0x09
#घोषणा ACPI_BITPOSITION_RT_CLOCK_ENABLE        0x0A
#घोषणा ACPI_BITPOSITION_PCIEXP_WAKE_DISABLE    0x0E	/* ACPI 3.0 */

#घोषणा ACPI_BITPOSITION_SCI_ENABLE             0x00
#घोषणा ACPI_BITPOSITION_BUS_MASTER_RLD         0x01
#घोषणा ACPI_BITPOSITION_GLOBAL_LOCK_RELEASE    0x02
#घोषणा ACPI_BITPOSITION_SLEEP_TYPE             0x0A
#घोषणा ACPI_BITPOSITION_SLEEP_ENABLE           0x0D

#घोषणा ACPI_BITPOSITION_ARB_DISABLE            0x00

/* Structs and definitions क्रम _OSI support and I/O port validation */

#घोषणा ACPI_ALWAYS_ILLEGAL             0x00

काष्ठा acpi_पूर्णांकerface_info अणु
	अक्षर *name;
	काष्ठा acpi_पूर्णांकerface_info *next;
	u8 flags;
	u8 value;
पूर्ण;

#घोषणा ACPI_OSI_INVALID                0x01
#घोषणा ACPI_OSI_DYNAMIC                0x02
#घोषणा ACPI_OSI_FEATURE                0x04
#घोषणा ACPI_OSI_DEFAULT_INVALID        0x08
#घोषणा ACPI_OSI_OPTIONAL_FEATURE       (ACPI_OSI_FEATURE | ACPI_OSI_DEFAULT_INVALID | ACPI_OSI_INVALID)

काष्ठा acpi_port_info अणु
	अक्षर *name;
	u16 start;
	u16 end;
	u8 osi_dependency;
पूर्ण;

/*****************************************************************************
 *
 * Resource descriptors
 *
 ****************************************************************************/

/* resource_type values */

#घोषणा ACPI_ADDRESS_TYPE_MEMORY_RANGE          0
#घोषणा ACPI_ADDRESS_TYPE_IO_RANGE              1
#घोषणा ACPI_ADDRESS_TYPE_BUS_NUMBER_RANGE      2

/* Resource descriptor types and masks */

#घोषणा ACPI_RESOURCE_NAME_LARGE                0x80
#घोषणा ACPI_RESOURCE_NAME_SMALL                0x00

#घोषणा ACPI_RESOURCE_NAME_SMALL_MASK           0x78	/* Bits 6:3 contain the type */
#घोषणा ACPI_RESOURCE_NAME_SMALL_LENGTH_MASK    0x07	/* Bits 2:0 contain the length */
#घोषणा ACPI_RESOURCE_NAME_LARGE_MASK           0x7F	/* Bits 6:0 contain the type */

/*
 * Small resource descriptor "names" as defined by the ACPI specअगरication.
 * Note: Bits 2:0 are used क्रम the descriptor length
 */
#घोषणा ACPI_RESOURCE_NAME_IRQ                  0x20
#घोषणा ACPI_RESOURCE_NAME_DMA                  0x28
#घोषणा ACPI_RESOURCE_NAME_START_DEPENDENT      0x30
#घोषणा ACPI_RESOURCE_NAME_END_DEPENDENT        0x38
#घोषणा ACPI_RESOURCE_NAME_IO                   0x40
#घोषणा ACPI_RESOURCE_NAME_FIXED_IO             0x48
#घोषणा ACPI_RESOURCE_NAME_FIXED_DMA            0x50
#घोषणा ACPI_RESOURCE_NAME_RESERVED_S2          0x58
#घोषणा ACPI_RESOURCE_NAME_RESERVED_S3          0x60
#घोषणा ACPI_RESOURCE_NAME_RESERVED_S4          0x68
#घोषणा ACPI_RESOURCE_NAME_VENDOR_SMALL         0x70
#घोषणा ACPI_RESOURCE_NAME_END_TAG              0x78

/*
 * Large resource descriptor "names" as defined by the ACPI specअगरication.
 * Note: includes the Large Descriptor bit in bit[7]
 */
#घोषणा ACPI_RESOURCE_NAME_MEMORY24             0x81
#घोषणा ACPI_RESOURCE_NAME_GENERIC_REGISTER     0x82
#घोषणा ACPI_RESOURCE_NAME_RESERVED_L1          0x83
#घोषणा ACPI_RESOURCE_NAME_VENDOR_LARGE         0x84
#घोषणा ACPI_RESOURCE_NAME_MEMORY32             0x85
#घोषणा ACPI_RESOURCE_NAME_FIXED_MEMORY32       0x86
#घोषणा ACPI_RESOURCE_NAME_ADDRESS32            0x87
#घोषणा ACPI_RESOURCE_NAME_ADDRESS16            0x88
#घोषणा ACPI_RESOURCE_NAME_EXTENDED_IRQ         0x89
#घोषणा ACPI_RESOURCE_NAME_ADDRESS64            0x8A
#घोषणा ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64   0x8B
#घोषणा ACPI_RESOURCE_NAME_GPIO                 0x8C
#घोषणा ACPI_RESOURCE_NAME_PIN_FUNCTION         0x8D
#घोषणा ACPI_RESOURCE_NAME_SERIAL_BUS           0x8E
#घोषणा ACPI_RESOURCE_NAME_PIN_CONFIG           0x8F
#घोषणा ACPI_RESOURCE_NAME_PIN_GROUP            0x90
#घोषणा ACPI_RESOURCE_NAME_PIN_GROUP_FUNCTION   0x91
#घोषणा ACPI_RESOURCE_NAME_PIN_GROUP_CONFIG     0x92
#घोषणा ACPI_RESOURCE_NAME_LARGE_MAX            0x92

/*****************************************************************************
 *
 * Miscellaneous
 *
 ****************************************************************************/

#घोषणा ACPI_ASCII_ZERO                 0x30

/*****************************************************************************
 *
 * Disassembler
 *
 ****************************************************************************/

काष्ठा acpi_बाह्यal_list अणु
	अक्षर *path;
	अक्षर *पूर्णांकernal_path;
	काष्ठा acpi_बाह्यal_list *next;
	u32 value;
	u16 length;
	u16 flags;
	u8 type;
पूर्ण;

/* Values क्रम Flags field above */

#घोषणा ACPI_EXT_RESOLVED_REFERENCE         0x01	/* Object was resolved during cross ref */
#घोषणा ACPI_EXT_ORIGIN_FROM_खाता           0x02	/* External came from a file */
#घोषणा ACPI_EXT_INTERNAL_PATH_ALLOCATED    0x04	/* Deallocate पूर्णांकernal path on completion */
#घोषणा ACPI_EXT_EXTERNAL_EMITTED           0x08	/* External() statement has been emitted */
#घोषणा ACPI_EXT_ORIGIN_FROM_OPCODE         0x10	/* External came from a External() opcode */
#घोषणा ACPI_EXT_CONFLICTING_DECLARATION    0x20	/* External has a conflicting declaration within AML */

काष्ठा acpi_बाह्यal_file अणु
	अक्षर *path;
	काष्ठा acpi_बाह्यal_file *next;
पूर्ण;

काष्ठा acpi_parse_object_list अणु
	जोड़ acpi_parse_object *op;
	काष्ठा acpi_parse_object_list *next;
पूर्ण;

/*****************************************************************************
 *
 * Debugger
 *
 ****************************************************************************/

काष्ठा acpi_db_method_info अणु
	acpi_handle method;
	acpi_handle मुख्य_thपढ़ो_gate;
	acpi_handle thपढ़ो_complete_gate;
	acpi_handle info_gate;
	acpi_thपढ़ो_id *thपढ़ोs;
	u32 num_thपढ़ोs;
	u32 num_created;
	u32 num_completed;

	अक्षर *name;
	u32 flags;
	u32 num_loops;
	अक्षर pathname[ACPI_DB_LINE_BUFFER_SIZE];
	अक्षर **args;
	acpi_object_type *types;

	/*
	 * Arguments to be passed to method क्रम the commands Thपढ़ोs and
	 * Background. Note, ACPI specअगरies a maximum of 7 arguments (0 - 6).
	 *
	 * For the Thपढ़ोs command, the Number of thपढ़ोs, ID of current
	 * thपढ़ो and Index of current thपढ़ो inside all them created.
	 */
	अक्षर init_args;
#अगर_घोषित ACPI_DEBUGGER
	acpi_object_type arg_types[ACPI_METHOD_NUM_ARGS];
#पूर्ण_अगर
	अक्षर *arguments[ACPI_METHOD_NUM_ARGS];
	अक्षर num_thपढ़ोs_str[11];
	अक्षर id_of_thपढ़ो_str[11];
	अक्षर index_of_thपढ़ो_str[11];
पूर्ण;

काष्ठा acpi_पूर्णांकegrity_info अणु
	u32 nodes;
	u32 objects;
पूर्ण;

#घोषणा ACPI_DB_DISABLE_OUTPUT          0x00
#घोषणा ACPI_DB_REसूचीECTABLE_OUTPUT     0x01
#घोषणा ACPI_DB_CONSOLE_OUTPUT          0x02
#घोषणा ACPI_DB_DUPLICATE_OUTPUT        0x03

काष्ठा acpi_object_info अणु
	u32 types[ACPI_TOTAL_TYPES];
पूर्ण;

/*****************************************************************************
 *
 * Debug
 *
 ****************************************************************************/

/* Entry क्रम a memory allocation (debug only) */

#घोषणा ACPI_MEM_MALLOC                 0
#घोषणा ACPI_MEM_CALLOC                 1
#घोषणा ACPI_MAX_MODULE_NAME            16

#घोषणा ACPI_COMMON_DEBUG_MEM_HEADER \
	काष्ठा acpi_debug_mem_block     *previous; \
	काष्ठा acpi_debug_mem_block     *next; \
	u32                             size; \
	u32                             component; \
	u32                             line; \
	अक्षर                            module[ACPI_MAX_MODULE_NAME]; \
	u8                              alloc_type;

काष्ठा acpi_debug_mem_header अणु
ACPI_COMMON_DEBUG_MEM_HEADERपूर्ण;

काष्ठा acpi_debug_mem_block अणु
	ACPI_COMMON_DEBUG_MEM_HEADER u64 user_space;
पूर्ण;

#घोषणा ACPI_MEM_LIST_GLOBAL            0
#घोषणा ACPI_MEM_LIST_NSNODE            1
#घोषणा ACPI_MEM_LIST_MAX               1
#घोषणा ACPI_NUM_MEM_LISTS              2

/*****************************************************************************
 *
 * Info/help support
 *
 ****************************************************************************/

काष्ठा ah_predefined_name अणु
	अक्षर *name;
	अक्षर *description;
#अगर_अघोषित ACPI_ASL_COMPILER
	अक्षर *action;
#पूर्ण_अगर
पूर्ण;

काष्ठा ah_device_id अणु
	अक्षर *name;
	अक्षर *description;
पूर्ण;

काष्ठा ah_uuid अणु
	अक्षर *description;
	अक्षर *string;
पूर्ण;

काष्ठा ah_table अणु
	अक्षर *signature;
	अक्षर *description;
पूर्ण;

#पूर्ण_अगर				/* __ACLOCAL_H__ */
