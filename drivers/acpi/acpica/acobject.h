<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acobject.h - Definition of जोड़ acpi_opeअक्रम_object  (Internal object only)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित _ACOBJECT_H
#घोषणा _ACOBJECT_H

/* acpisrc:काष्ठा_defs -- क्रम acpisrc conversion */

/*
 * The जोड़ acpi_opeअक्रम_object is used to pass AML opeअक्रमs from the dispatcher
 * to the पूर्णांकerpreter, and to keep track of the various handlers such as
 * address space handlers and notअगरy handlers. The object is a स्थिरant
 * size in order to allow it to be cached and reused.
 *
 * Note: The object is optimized to be aligned and will not work अगर it is
 * byte-packed.
 */
#अगर ACPI_MACHINE_WIDTH == 64
#आशय pack(8)
#अन्यथा
#आशय pack(4)
#पूर्ण_अगर

/*******************************************************************************
 *
 * Common Descriptors
 *
 ******************************************************************************/

/*
 * Common area क्रम all objects.
 *
 * descriptor_type is used to dअगरferentiate between पूर्णांकernal descriptors, and
 * must be in the same place across all descriptors
 *
 * Note: The descriptor_type and Type fields must appear in the identical
 * position in both the काष्ठा acpi_namespace_node and जोड़ acpi_opeअक्रम_object
 * काष्ठाures.
 */
#घोषणा ACPI_OBJECT_COMMON_HEADER \
	जोड़ acpi_opeअक्रम_object       *next_object;       /* Objects linked to parent NS node */\
	u8                              descriptor_type;    /* To dअगरferentiate various पूर्णांकernal objs */\
	u8                              type;               /* acpi_object_type */\
	u16                             reference_count;    /* For object deletion management */\
	u8                              flags;
	/*
	 * Note: There are 3 bytes available here beक्रमe the
	 * next natural alignment boundary (क्रम both 32/64 हालs)
	 */

/* Values क्रम Flag byte above */

#घोषणा AOPOBJ_AML_CONSTANT         0x01	/* Integer is an AML स्थिरant */
#घोषणा AOPOBJ_STATIC_POINTER       0x02	/* Data is part of an ACPI table, करोn't delete */
#घोषणा AOPOBJ_DATA_VALID           0x04	/* Object is initialized and data is valid */
#घोषणा AOPOBJ_OBJECT_INITIALIZED   0x08	/* Region is initialized */
#घोषणा AOPOBJ_REG_CONNECTED        0x10	/* _REG was run */
#घोषणा AOPOBJ_SETUP_COMPLETE       0x20	/* Region setup is complete */
#घोषणा AOPOBJ_INVALID              0x40	/* Host OS won't allow a Region address */

/******************************************************************************
 *
 * Basic data types
 *
 *****************************************************************************/

काष्ठा acpi_object_common अणु
ACPI_OBJECT_COMMON_HEADERपूर्ण;

काष्ठा acpi_object_पूर्णांकeger अणु
	ACPI_OBJECT_COMMON_HEADER u8 fill[3];	/* Prevent warning on some compilers */
	u64 value;
पूर्ण;

/*
 * Note: The String and Buffer object must be identical through the
 * poपूर्णांकer and length elements. There is code that depends on this.
 *
 * Fields common to both Strings and Buffers
 */
#घोषणा ACPI_COMMON_BUFFER_INFO(_type) \
	_type                           *poपूर्णांकer; \
	u32                             length;

/* Null terminated, ASCII अक्षरacters only */

काष्ठा acpi_object_string अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_BUFFER_INFO(अक्षर)	/* String in AML stream or allocated string */
पूर्ण;

काष्ठा acpi_object_buffer अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_BUFFER_INFO(u8)	/* Buffer in AML stream or allocated buffer */
	u32 aml_length;
	u8 *aml_start;
	काष्ठा acpi_namespace_node *node;	/* Link back to parent node */
पूर्ण;

काष्ठा acpi_object_package अणु
	ACPI_OBJECT_COMMON_HEADER काष्ठा acpi_namespace_node *node;	/* Link back to parent node */
	जोड़ acpi_opeअक्रम_object **elements;	/* Array of poपूर्णांकers to acpi_objects */
	u8 *aml_start;
	u32 aml_length;
	u32 count;		/* # of elements in package */
पूर्ण;

/******************************************************************************
 *
 * Complex data types
 *
 *****************************************************************************/

काष्ठा acpi_object_event अणु
	ACPI_OBJECT_COMMON_HEADER acpi_semaphore os_semaphore;	/* Actual OS synchronization object */
पूर्ण;

काष्ठा acpi_object_mutex अणु
	ACPI_OBJECT_COMMON_HEADER u8 sync_level;	/* 0-15, specअगरied in Mutex() call */
	u16 acquisition_depth;	/* Allow multiple Acquires, same thपढ़ो */
	acpi_mutex os_mutex;	/* Actual OS synchronization object */
	acpi_thपढ़ो_id thपढ़ो_id;	/* Current owner of the mutex */
	काष्ठा acpi_thपढ़ो_state *owner_thपढ़ो;	/* Current owner of the mutex */
	जोड़ acpi_opeअक्रम_object *prev;	/* Link क्रम list of acquired mutexes */
	जोड़ acpi_opeअक्रम_object *next;	/* Link क्रम list of acquired mutexes */
	काष्ठा acpi_namespace_node *node;	/* Containing namespace node */
	u8 original_sync_level;	/* Owner's original sync level (0-15) */
पूर्ण;

काष्ठा acpi_object_region अणु
	ACPI_OBJECT_COMMON_HEADER u8 space_id;
	काष्ठा acpi_namespace_node *node;	/* Containing namespace node */
	जोड़ acpi_opeअक्रम_object *handler;	/* Handler क्रम region access */
	जोड़ acpi_opeअक्रम_object *next;
	acpi_physical_address address;
	u32 length;
पूर्ण;

काष्ठा acpi_object_method अणु
	ACPI_OBJECT_COMMON_HEADER u8 info_flags;
	u8 param_count;
	u8 sync_level;
	जोड़ acpi_opeअक्रम_object *mutex;
	जोड़ acpi_opeअक्रम_object *node;
	u8 *aml_start;
	जोड़ अणु
		acpi_पूर्णांकernal_method implementation;
		जोड़ acpi_opeअक्रम_object *handler;
	पूर्ण dispatch;

	u32 aml_length;
	acpi_owner_id owner_id;
	u8 thपढ़ो_count;
पूर्ण;

/* Flags क्रम info_flags field above */

#घोषणा ACPI_METHOD_MODULE_LEVEL        0x01	/* Method is actually module-level code */
#घोषणा ACPI_METHOD_INTERNAL_ONLY       0x02	/* Method is implemented पूर्णांकernally (_OSI) */
#घोषणा ACPI_METHOD_SERIALIZED          0x04	/* Method is serialized */
#घोषणा ACPI_METHOD_SERIALIZED_PENDING  0x08	/* Method is to be marked serialized */
#घोषणा ACPI_METHOD_IGNORE_SYNC_LEVEL   0x10	/* Method was स्वतः-serialized at table load समय */
#घोषणा ACPI_METHOD_MODIFIED_NAMESPACE  0x20	/* Method modअगरied the namespace */

/******************************************************************************
 *
 * Objects that can be notअगरied. All share a common notअगरy_info area.
 *
 *****************************************************************************/

/*
 * Common fields क्रम objects that support ASL notअगरications
 */
#घोषणा ACPI_COMMON_NOTIFY_INFO \
	जोड़ acpi_opeअक्रम_object       *notअगरy_list[2];    /* Handlers क्रम प्रणाली/device notअगरies */\
	जोड़ acpi_opeअक्रम_object       *handler;	/* Handler क्रम Address space */

/* COMMON NOTIFY क्रम POWER, PROCESSOR, DEVICE, and THERMAL */

काष्ठा acpi_object_notअगरy_common अणु
ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_NOTIFY_INFOपूर्ण;

काष्ठा acpi_object_device अणु
	ACPI_OBJECT_COMMON_HEADER
	    ACPI_COMMON_NOTIFY_INFO काष्ठा acpi_gpe_block_info *gpe_block;
पूर्ण;

काष्ठा acpi_object_घातer_resource अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_NOTIFY_INFO u32 प्रणाली_level;
	u32 resource_order;
पूर्ण;

काष्ठा acpi_object_processor अणु
	ACPI_OBJECT_COMMON_HEADER
	    /* The next two fields take advantage of the 3-byte space beक्रमe NOTIFY_INFO */
	u8 proc_id;
	u8 length;
	ACPI_COMMON_NOTIFY_INFO acpi_io_address address;
पूर्ण;

काष्ठा acpi_object_thermal_zone अणु
ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_NOTIFY_INFOपूर्ण;

/******************************************************************************
 *
 * Fields. All share a common header/info field.
 *
 *****************************************************************************/

/*
 * Common bitfield क्रम the field objects
 * "Field Datum"  -- a datum from the actual field object
 * "Buffer Datum" -- a datum from a user buffer, पढ़ो from or to be written to the field
 */
#घोषणा ACPI_COMMON_FIELD_INFO \
	u8                              field_flags;        /* Access, update, and lock bits */\
	u8                              attribute;          /* From access_as keyword */\
	u8                              access_byte_width;  /* Read/Write size in bytes */\
	काष्ठा acpi_namespace_node      *node;              /* Link back to parent node */\
	u32                             bit_length;         /* Length of field in bits */\
	u32                             base_byte_offset;   /* Byte offset within containing object */\
	u32                             value;              /* Value to store पूर्णांकo the Bank or Index रेजिस्टर */\
	u8                              start_field_bit_offset;/* Bit offset within first field datum (0-63) */\
	u8                              access_length;	/* For serial regions/fields */


/* COMMON FIELD (क्रम BUFFER, REGION, BANK, and INDEX fields) */

काष्ठा acpi_object_field_common अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_FIELD_INFO जोड़ acpi_opeअक्रम_object *region_obj;	/* Parent Operation Region object (REGION/BANK fields only) */
पूर्ण;

काष्ठा acpi_object_region_field अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_FIELD_INFO u16 resource_length;
	जोड़ acpi_opeअक्रम_object *region_obj;	/* Containing op_region object */
	u8 *resource_buffer;	/* resource_ढाँचा क्रम serial regions/fields */
	u16 pin_number_index;	/* Index relative to previous Connection/Template */
	u8 *पूर्णांकernal_pcc_buffer;	/* Internal buffer क्रम fields associated with PCC */
पूर्ण;

काष्ठा acpi_object_bank_field अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_FIELD_INFO जोड़ acpi_opeअक्रम_object *region_obj;	/* Containing op_region object */
	जोड़ acpi_opeअक्रम_object *bank_obj;	/* bank_select Register object */
पूर्ण;

काष्ठा acpi_object_index_field अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_FIELD_INFO
	    /*
	     * No "RegionObj" poपूर्णांकer needed since the Index and Data रेजिस्टरs
	     * are each field definitions unto themselves.
	     */
	जोड़ acpi_opeअक्रम_object *index_obj;	/* Index रेजिस्टर */
	जोड़ acpi_opeअक्रम_object *data_obj;	/* Data रेजिस्टर */
पूर्ण;

/* The buffer_field is dअगरferent in that it is part of a Buffer, not an op_region */

काष्ठा acpi_object_buffer_field अणु
	ACPI_OBJECT_COMMON_HEADER ACPI_COMMON_FIELD_INFO u8 is_create_field;	/* Special हाल क्रम objects created by create_field() */
	जोड़ acpi_opeअक्रम_object *buffer_obj;	/* Containing Buffer object */
पूर्ण;

/******************************************************************************
 *
 * Objects क्रम handlers
 *
 *****************************************************************************/

काष्ठा acpi_object_notअगरy_handler अणु
	ACPI_OBJECT_COMMON_HEADER काष्ठा acpi_namespace_node *node;	/* Parent device */
	u32 handler_type;	/* Type: Device/System/Both */
	acpi_notअगरy_handler handler;	/* Handler address */
	व्योम *context;
	जोड़ acpi_opeअक्रम_object *next[2];	/* Device and System handler lists */
पूर्ण;

काष्ठा acpi_object_addr_handler अणु
	ACPI_OBJECT_COMMON_HEADER u8 space_id;
	u8 handler_flags;
	acpi_adr_space_handler handler;
	काष्ठा acpi_namespace_node *node;	/* Parent device */
	व्योम *context;
	acpi_mutex context_mutex;
	acpi_adr_space_setup setup;
	जोड़ acpi_opeअक्रम_object *region_list;	/* Regions using this handler */
	जोड़ acpi_opeअक्रम_object *next;
पूर्ण;

/* Flags क्रम address handler (handler_flags) */

#घोषणा ACPI_ADDR_HANDLER_DEFAULT_INSTALLED  0x01

/******************************************************************************
 *
 * Special पूर्णांकernal objects
 *
 *****************************************************************************/

/*
 * The Reference object is used क्रम these opcodes:
 * Arg[0-6], Local[0-7], index_op, name_op, ref_of_op, load_op, load_table_op, debug_op
 * The Reference.Class dअगरferentiates these types.
 */
काष्ठा acpi_object_reference अणु
	ACPI_OBJECT_COMMON_HEADER u8 class;	/* Reference Class */
	u8 target_type;		/* Used क्रम Index Op */
	u8 resolved;		/* Reference has been resolved to a value */
	व्योम *object;		/* name_op=>HANDLE to obj, index_op=>जोड़ acpi_opeअक्रम_object */
	काष्ठा acpi_namespace_node *node;	/* ref_of or Namepath */
	जोड़ acpi_opeअक्रम_object **where;	/* Target of Index */
	u8 *index_poपूर्णांकer;	/* Used क्रम Buffers and Strings */
	u8 *aml;		/* Used क्रम deferred resolution of the ref */
	u32 value;		/* Used क्रम Local/Arg/Index/ddb_handle */
पूर्ण;

/* Values क्रम Reference.Class above */

प्रकार क्रमागत अणु
	ACPI_REFCLASS_LOCAL = 0,	/* Method local */
	ACPI_REFCLASS_ARG = 1,	/* Method argument */
	ACPI_REFCLASS_REFOF = 2,	/* Result of ref_of() TBD: Split to Ref/Node and Ref/opeअक्रम_obj? */
	ACPI_REFCLASS_INDEX = 3,	/* Result of Index() */
	ACPI_REFCLASS_TABLE = 4,	/* ddb_handle - Load(), load_table() */
	ACPI_REFCLASS_NAME = 5,	/* Reference to a named object */
	ACPI_REFCLASS_DEBUG = 6,	/* Debug object */

	ACPI_REFCLASS_MAX = 6
पूर्ण ACPI_REFERENCE_CLASSES;

/*
 * Extra object is used as additional storage क्रम types that
 * have AML code in their declarations (term_args) that must be
 * evaluated at run समय.
 *
 * Currently: Region and field_unit types
 */
काष्ठा acpi_object_extra अणु
	ACPI_OBJECT_COMMON_HEADER काष्ठा acpi_namespace_node *method_REG;	/* _REG method क्रम this region (अगर any) */
	काष्ठा acpi_namespace_node *scope_node;
	व्योम *region_context;	/* Region-specअगरic data */
	u8 *aml_start;
	u32 aml_length;
पूर्ण;

/* Additional data that can be attached to namespace nodes */

काष्ठा acpi_object_data अणु
	ACPI_OBJECT_COMMON_HEADER acpi_object_handler handler;
	व्योम *poपूर्णांकer;
पूर्ण;

/* Structure used when objects are cached क्रम reuse */

काष्ठा acpi_object_cache_list अणु
	ACPI_OBJECT_COMMON_HEADER जोड़ acpi_opeअक्रम_object *next;	/* Link क्रम object cache and पूर्णांकernal lists */
पूर्ण;

/******************************************************************************
 *
 * जोड़ acpi_opeअक्रम_object descriptor - a giant जोड़ of all of the above
 *
 *****************************************************************************/

जोड़ acpi_opeअक्रम_object अणु
	काष्ठा acpi_object_common common;
	काष्ठा acpi_object_पूर्णांकeger पूर्णांकeger;
	काष्ठा acpi_object_string string;
	काष्ठा acpi_object_buffer buffer;
	काष्ठा acpi_object_package package;
	काष्ठा acpi_object_event event;
	काष्ठा acpi_object_method method;
	काष्ठा acpi_object_mutex mutex;
	काष्ठा acpi_object_region region;
	काष्ठा acpi_object_notअगरy_common common_notअगरy;
	काष्ठा acpi_object_device device;
	काष्ठा acpi_object_घातer_resource घातer_resource;
	काष्ठा acpi_object_processor processor;
	काष्ठा acpi_object_thermal_zone thermal_zone;
	काष्ठा acpi_object_field_common common_field;
	काष्ठा acpi_object_region_field field;
	काष्ठा acpi_object_buffer_field buffer_field;
	काष्ठा acpi_object_bank_field bank_field;
	काष्ठा acpi_object_index_field index_field;
	काष्ठा acpi_object_notअगरy_handler notअगरy;
	काष्ठा acpi_object_addr_handler address_space;
	काष्ठा acpi_object_reference reference;
	काष्ठा acpi_object_extra extra;
	काष्ठा acpi_object_data data;
	काष्ठा acpi_object_cache_list cache;

	/*
	 * Add namespace node to जोड़ in order to simplअगरy code that accepts both
	 * ACPI_OPERAND_OBJECTs and ACPI_NAMESPACE_NODEs. The काष्ठाures share
	 * a common descriptor_type field in order to dअगरferentiate them.
	 */
	काष्ठा acpi_namespace_node node;
पूर्ण;

/******************************************************************************
 *
 * जोड़ acpi_descriptor - objects that share a common descriptor identअगरier
 *
 *****************************************************************************/

/* Object descriptor types */

#घोषणा ACPI_DESC_TYPE_CACHED           0x01	/* Used only when object is cached */
#घोषणा ACPI_DESC_TYPE_STATE            0x02
#घोषणा ACPI_DESC_TYPE_STATE_UPDATE     0x03
#घोषणा ACPI_DESC_TYPE_STATE_PACKAGE    0x04
#घोषणा ACPI_DESC_TYPE_STATE_CONTROL    0x05
#घोषणा ACPI_DESC_TYPE_STATE_RPSCOPE    0x06
#घोषणा ACPI_DESC_TYPE_STATE_PSCOPE     0x07
#घोषणा ACPI_DESC_TYPE_STATE_WSCOPE     0x08
#घोषणा ACPI_DESC_TYPE_STATE_RESULT     0x09
#घोषणा ACPI_DESC_TYPE_STATE_NOTIFY     0x0A
#घोषणा ACPI_DESC_TYPE_STATE_THREAD     0x0B
#घोषणा ACPI_DESC_TYPE_WALK             0x0C
#घोषणा ACPI_DESC_TYPE_PARSER           0x0D
#घोषणा ACPI_DESC_TYPE_OPERAND          0x0E
#घोषणा ACPI_DESC_TYPE_NAMED            0x0F
#घोषणा ACPI_DESC_TYPE_MAX              0x0F

काष्ठा acpi_common_descriptor अणु
	व्योम *common_poपूर्णांकer;
	u8 descriptor_type;	/* To dअगरferentiate various पूर्णांकernal objs */
पूर्ण;

जोड़ acpi_descriptor अणु
	काष्ठा acpi_common_descriptor common;
	जोड़ acpi_opeअक्रम_object object;
	काष्ठा acpi_namespace_node node;
	जोड़ acpi_parse_object op;
पूर्ण;

#आशय pack()

#पूर्ण_अगर				/* _ACOBJECT_H */
