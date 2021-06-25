<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: utdecode - Utility decoding routines (value-to-string)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utdecode")

/*
 * Properties of the ACPI Object Types, both पूर्णांकernal and बाह्यal.
 * The table is indexed by values of acpi_object_type
 */
स्थिर u8 acpi_gbl_ns_properties[ACPI_NUM_NS_TYPES] = अणु
	ACPI_NS_NORMAL,		/* 00 Any              */
	ACPI_NS_NORMAL,		/* 01 Number           */
	ACPI_NS_NORMAL,		/* 02 String           */
	ACPI_NS_NORMAL,		/* 03 Buffer           */
	ACPI_NS_NORMAL,		/* 04 Package          */
	ACPI_NS_NORMAL,		/* 05 field_unit       */
	ACPI_NS_NEWSCOPE,	/* 06 Device           */
	ACPI_NS_NORMAL,		/* 07 Event            */
	ACPI_NS_NEWSCOPE,	/* 08 Method           */
	ACPI_NS_NORMAL,		/* 09 Mutex            */
	ACPI_NS_NORMAL,		/* 10 Region           */
	ACPI_NS_NEWSCOPE,	/* 11 Power            */
	ACPI_NS_NEWSCOPE,	/* 12 Processor        */
	ACPI_NS_NEWSCOPE,	/* 13 Thermal          */
	ACPI_NS_NORMAL,		/* 14 buffer_field     */
	ACPI_NS_NORMAL,		/* 15 ddb_handle       */
	ACPI_NS_NORMAL,		/* 16 Debug Object     */
	ACPI_NS_NORMAL,		/* 17 def_field        */
	ACPI_NS_NORMAL,		/* 18 bank_field       */
	ACPI_NS_NORMAL,		/* 19 index_field      */
	ACPI_NS_NORMAL,		/* 20 Reference        */
	ACPI_NS_NORMAL,		/* 21 Alias            */
	ACPI_NS_NORMAL,		/* 22 method_alias     */
	ACPI_NS_NORMAL,		/* 23 Notअगरy           */
	ACPI_NS_NORMAL,		/* 24 Address Handler  */
	ACPI_NS_NEWSCOPE | ACPI_NS_LOCAL,	/* 25 Resource Desc    */
	ACPI_NS_NEWSCOPE | ACPI_NS_LOCAL,	/* 26 Resource Field   */
	ACPI_NS_NEWSCOPE,	/* 27 Scope            */
	ACPI_NS_NORMAL,		/* 28 Extra            */
	ACPI_NS_NORMAL,		/* 29 Data             */
	ACPI_NS_NORMAL		/* 30 Invalid          */
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_region_name
 *
 * PARAMETERS:  Space ID            - ID क्रम the region
 *
 * RETURN:      Decoded region space_id name
 *
 * DESCRIPTION: Translate a Space ID पूर्णांकo a name string (Debug only)
 *
 ******************************************************************************/

/* Region type decoding */

स्थिर अक्षर *acpi_gbl_region_types[ACPI_NUM_PREDEFINED_REGIONS] = अणु
	"SystemMemory",		/* 0x00 */
	"SystemIO",		/* 0x01 */
	"PCI_Config",		/* 0x02 */
	"EmbeddedControl",	/* 0x03 */
	"SMBus",		/* 0x04 */
	"SystemCMOS",		/* 0x05 */
	"PCIBARTarget",		/* 0x06 */
	"IPMI",			/* 0x07 */
	"GeneralPurposeIo",	/* 0x08 */
	"GenericSerialBus",	/* 0x09 */
	"PCC",			/* 0x0A */
	"PlatformRtMechanism"	/* 0x0B */
पूर्ण;

स्थिर अक्षर *acpi_ut_get_region_name(u8 space_id)
अणु

	अगर (space_id >= ACPI_USER_REGION_BEGIN) अणु
		वापस ("UserDefinedRegion");
	पूर्ण अन्यथा अगर (space_id == ACPI_ADR_SPACE_DATA_TABLE) अणु
		वापस ("DataTable");
	पूर्ण अन्यथा अगर (space_id == ACPI_ADR_SPACE_FIXED_HARDWARE) अणु
		वापस ("FunctionalFixedHW");
	पूर्ण अन्यथा अगर (space_id >= ACPI_NUM_PREDEFINED_REGIONS) अणु
		वापस ("InvalidSpaceId");
	पूर्ण

	वापस (acpi_gbl_region_types[space_id]);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_event_name
 *
 * PARAMETERS:  event_id            - Fixed event ID
 *
 * RETURN:      Decoded event ID name
 *
 * DESCRIPTION: Translate a Event ID पूर्णांकo a name string (Debug only)
 *
 ******************************************************************************/

/* Event type decoding */

अटल स्थिर अक्षर *acpi_gbl_event_types[ACPI_NUM_FIXED_EVENTS] = अणु
	"PM_Timer",
	"GlobalLock",
	"PowerButton",
	"SleepButton",
	"RealTimeClock",
पूर्ण;

स्थिर अक्षर *acpi_ut_get_event_name(u32 event_id)
अणु

	अगर (event_id > ACPI_EVENT_MAX) अणु
		वापस ("InvalidEventID");
	पूर्ण

	वापस (acpi_gbl_event_types[event_id]);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_type_name
 *
 * PARAMETERS:  type                - An ACPI object type
 *
 * RETURN:      Decoded ACPI object type name
 *
 * DESCRIPTION: Translate a Type ID पूर्णांकo a name string (Debug only)
 *
 ******************************************************************************/

/*
 * Elements of acpi_gbl_ns_type_names below must match
 * one-to-one with values of acpi_object_type
 *
 * The type ACPI_TYPE_ANY (Untyped) is used as a "don't care" when searching;
 * when stored in a table it really means that we have thus far seen no
 * evidence to indicate what type is actually going to be stored क्रम this
 & entry.
 */
अटल स्थिर अक्षर acpi_gbl_bad_type[] = "UNDEFINED";

/* Prपूर्णांकable names of the ACPI object types */

अटल स्थिर अक्षर *acpi_gbl_ns_type_names[] = अणु
	/* 00 */ "Untyped",
	/* 01 */ "Integer",
	/* 02 */ "String",
	/* 03 */ "Buffer",
	/* 04 */ "Package",
	/* 05 */ "FieldUnit",
	/* 06 */ "Device",
	/* 07 */ "Event",
	/* 08 */ "Method",
	/* 09 */ "Mutex",
	/* 10 */ "Region",
	/* 11 */ "Power",
	/* 12 */ "Processor",
	/* 13 */ "Thermal",
	/* 14 */ "BufferField",
	/* 15 */ "DdbHandle",
	/* 16 */ "DebugObject",
	/* 17 */ "RegionField",
	/* 18 */ "BankField",
	/* 19 */ "IndexField",
	/* 20 */ "Reference",
	/* 21 */ "Alias",
	/* 22 */ "MethodAlias",
	/* 23 */ "Notify",
	/* 24 */ "AddrHandler",
	/* 25 */ "ResourceDesc",
	/* 26 */ "ResourceFld",
	/* 27 */ "Scope",
	/* 28 */ "Extra",
	/* 29 */ "Data",
	/* 30 */ "Invalid"
पूर्ण;

स्थिर अक्षर *acpi_ut_get_type_name(acpi_object_type type)
अणु

	अगर (type > ACPI_TYPE_INVALID) अणु
		वापस (acpi_gbl_bad_type);
	पूर्ण

	वापस (acpi_gbl_ns_type_names[type]);
पूर्ण

स्थिर अक्षर *acpi_ut_get_object_type_name(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	ACPI_FUNCTION_TRACE(ut_get_object_type_name);

	अगर (!obj_desc) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Null Object Descriptor\n"));
		वापस_STR("[NULL Object Descriptor]");
	पूर्ण

	/* These descriptor types share a common area */

	अगर ((ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) &&
	    (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_NAMED)) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Invalid object descriptor type: 0x%2.2X [%s] (%p)\n",
				  ACPI_GET_DESCRIPTOR_TYPE(obj_desc),
				  acpi_ut_get_descriptor_name(obj_desc),
				  obj_desc));

		वापस_STR("Invalid object");
	पूर्ण

	वापस_STR(acpi_ut_get_type_name(obj_desc->common.type));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_node_name
 *
 * PARAMETERS:  object               - A namespace node
 *
 * RETURN:      ASCII name of the node
 *
 * DESCRIPTION: Validate the node and वापस the node's ACPI name.
 *
 ******************************************************************************/

स्थिर अक्षर *acpi_ut_get_node_name(व्योम *object)
अणु
	काष्ठा acpi_namespace_node *node = (काष्ठा acpi_namespace_node *)object;

	/* Must वापस a string of exactly 4 अक्षरacters == ACPI_NAMESEG_SIZE */

	अगर (!object) अणु
		वापस ("NULL");
	पूर्ण

	/* Check क्रम Root node */

	अगर ((object == ACPI_ROOT_OBJECT) || (object == acpi_gbl_root_node)) अणु
		वापस ("\"\\\" ");
	पूर्ण

	/* Descriptor must be a namespace node */

	अगर (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) अणु
		वापस ("####");
	पूर्ण

	/*
	 * Ensure name is valid. The name was validated/repaired when the node
	 * was created, but make sure it has not been corrupted.
	 */
	acpi_ut_repair_name(node->name.ascii);

	/* Return the name */

	वापस (node->name.ascii);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_descriptor_name
 *
 * PARAMETERS:  object               - An ACPI object
 *
 * RETURN:      Decoded name of the descriptor type
 *
 * DESCRIPTION: Validate object and वापस the descriptor type
 *
 ******************************************************************************/

/* Prपूर्णांकable names of object descriptor types */

अटल स्थिर अक्षर *acpi_gbl_desc_type_names[] = अणु
	/* 00 */ "Not a Descriptor",
	/* 01 */ "Cached Object",
	/* 02 */ "State-Generic",
	/* 03 */ "State-Update",
	/* 04 */ "State-Package",
	/* 05 */ "State-Control",
	/* 06 */ "State-RootParseScope",
	/* 07 */ "State-ParseScope",
	/* 08 */ "State-WalkScope",
	/* 09 */ "State-Result",
	/* 10 */ "State-Notify",
	/* 11 */ "State-Thread",
	/* 12 */ "Tree Walk State",
	/* 13 */ "Parse Tree Op",
	/* 14 */ "Operand Object",
	/* 15 */ "Namespace Node"
पूर्ण;

स्थिर अक्षर *acpi_ut_get_descriptor_name(व्योम *object)
अणु

	अगर (!object) अणु
		वापस ("NULL OBJECT");
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(object) > ACPI_DESC_TYPE_MAX) अणु
		वापस ("Not a Descriptor");
	पूर्ण

	वापस (acpi_gbl_desc_type_names[ACPI_GET_DESCRIPTOR_TYPE(object)]);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_reference_name
 *
 * PARAMETERS:  object               - An ACPI reference object
 *
 * RETURN:      Decoded name of the type of reference
 *
 * DESCRIPTION: Decode a reference object sub-type to a string.
 *
 ******************************************************************************/

/* Prपूर्णांकable names of reference object sub-types */

अटल स्थिर अक्षर *acpi_gbl_ref_class_names[] = अणु
	/* 00 */ "Local",
	/* 01 */ "Argument",
	/* 02 */ "RefOf",
	/* 03 */ "Index",
	/* 04 */ "DdbHandle",
	/* 05 */ "Named Object",
	/* 06 */ "Debug"
पूर्ण;

स्थिर अक्षर *acpi_ut_get_reference_name(जोड़ acpi_opeअक्रम_object *object)
अणु

	अगर (!object) अणु
		वापस ("NULL Object");
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(object) != ACPI_DESC_TYPE_OPERAND) अणु
		वापस ("Not an Operand object");
	पूर्ण

	अगर (object->common.type != ACPI_TYPE_LOCAL_REFERENCE) अणु
		वापस ("Not a Reference object");
	पूर्ण

	अगर (object->reference.class > ACPI_REFCLASS_MAX) अणु
		वापस ("Unknown Reference class");
	पूर्ण

	वापस (acpi_gbl_ref_class_names[object->reference.class]);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_mutex_name
 *
 * PARAMETERS:  mutex_id        - The predefined ID क्रम this mutex.
 *
 * RETURN:      Decoded name of the पूर्णांकernal mutex
 *
 * DESCRIPTION: Translate a mutex ID पूर्णांकo a name string (Debug only)
 *
 ******************************************************************************/

/* Names क्रम पूर्णांकernal mutex objects, used क्रम debug output */

अटल स्थिर अक्षर *acpi_gbl_mutex_names[ACPI_NUM_MUTEX] = अणु
	"ACPI_MTX_Interpreter",
	"ACPI_MTX_Namespace",
	"ACPI_MTX_Tables",
	"ACPI_MTX_Events",
	"ACPI_MTX_Caches",
	"ACPI_MTX_Memory",
पूर्ण;

स्थिर अक्षर *acpi_ut_get_mutex_name(u32 mutex_id)
अणु

	अगर (mutex_id > ACPI_MAX_MUTEX) अणु
		वापस ("Invalid Mutex ID");
	पूर्ण

	वापस (acpi_gbl_mutex_names[mutex_id]);
पूर्ण

#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)

/*
 * Strings and procedures used क्रम debug only
 */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_notअगरy_name
 *
 * PARAMETERS:  notअगरy_value    - Value from the Notअगरy() request
 *
 * RETURN:      Decoded name क्रम the notअगरy value
 *
 * DESCRIPTION: Translate a Notअगरy Value to a notअगरy namestring.
 *
 ******************************************************************************/

/* Names क्रम Notअगरy() values, used क्रम debug output */

अटल स्थिर अक्षर *acpi_gbl_generic_notअगरy[ACPI_GENERIC_NOTIFY_MAX + 1] = अणु
	/* 00 */ "Bus Check",
	/* 01 */ "Device Check",
	/* 02 */ "Device Wake",
	/* 03 */ "Eject Request",
	/* 04 */ "Device Check Light",
	/* 05 */ "Frequency Mismatch",
	/* 06 */ "Bus Mode Mismatch",
	/* 07 */ "Power Fault",
	/* 08 */ "Capabilities Check",
	/* 09 */ "Device PLD Check",
	/* 0A */ "Reserved",
	/* 0B */ "System Locality Update",
								/* 0C */ "Reserved (was previously Shutdown Request)",
								/* Reserved in ACPI 6.0 */
	/* 0D */ "System Resource Affinity Update",
								/* 0E */ "Heterogeneous Memory Attributes Update",
								/* ACPI 6.2 */
						/* 0F */ "Error Disconnect Recover"
						/* ACPI 6.3 */
पूर्ण;

अटल स्थिर अक्षर *acpi_gbl_device_notअगरy[5] = अणु
	/* 80 */ "Status Change",
	/* 81 */ "Information Change",
	/* 82 */ "Device-Specific Change",
	/* 83 */ "Device-Specific Change",
	/* 84 */ "Reserved"
पूर्ण;

अटल स्थिर अक्षर *acpi_gbl_processor_notअगरy[5] = अणु
	/* 80 */ "Performance Capability Change",
	/* 81 */ "C-State Change",
	/* 82 */ "Throttling Capability Change",
	/* 83 */ "Guaranteed Change",
	/* 84 */ "Minimum Excursion"
पूर्ण;

अटल स्थिर अक्षर *acpi_gbl_thermal_notअगरy[5] = अणु
	/* 80 */ "Thermal Status Change",
	/* 81 */ "Thermal Trip Point Change",
	/* 82 */ "Thermal Device List Change",
	/* 83 */ "Thermal Relationship Change",
	/* 84 */ "Reserved"
पूर्ण;

स्थिर अक्षर *acpi_ut_get_notअगरy_name(u32 notअगरy_value, acpi_object_type type)
अणु

	/* 00 - 0F are "common to all object types" (from ACPI Spec) */

	अगर (notअगरy_value <= ACPI_GENERIC_NOTIFY_MAX) अणु
		वापस (acpi_gbl_generic_notअगरy[notअगरy_value]);
	पूर्ण

	/* 10 - 7F are reserved */

	अगर (notअगरy_value <= ACPI_MAX_SYS_NOTIFY) अणु
		वापस ("Reserved");
	पूर्ण

	/* 80 - 84 are per-object-type */

	अगर (notअगरy_value <= ACPI_SPECIFIC_NOTIFY_MAX) अणु
		चयन (type) अणु
		हाल ACPI_TYPE_ANY:
		हाल ACPI_TYPE_DEVICE:
			वापस (acpi_gbl_device_notअगरy[notअगरy_value - 0x80]);

		हाल ACPI_TYPE_PROCESSOR:
			वापस (acpi_gbl_processor_notअगरy[notअगरy_value - 0x80]);

		हाल ACPI_TYPE_THERMAL:
			वापस (acpi_gbl_thermal_notअगरy[notअगरy_value - 0x80]);

		शेष:
			वापस ("Target object type does not support notifies");
		पूर्ण
	पूर्ण

	/* 84 - BF are device-specअगरic */

	अगर (notअगरy_value <= ACPI_MAX_DEVICE_SPECIFIC_NOTIFY) अणु
		वापस ("Device-Specific");
	पूर्ण

	/* C0 and above are hardware-specअगरic */

	वापस ("Hardware-Specific");
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_get_argument_type_name
 *
 * PARAMETERS:  arg_type            - an ARGP_* parser argument type
 *
 * RETURN:      Decoded ARGP_* type
 *
 * DESCRIPTION: Decode an ARGP_* parser type, as defined in the amlcode.h file,
 *              and used in the acopcode.h file. For example, ARGP_TERMARG.
 *              Used क्रम debug only.
 *
 ******************************************************************************/

अटल स्थिर अक्षर *acpi_gbl_argument_type[20] = अणु
	/* 00 */ "Unknown ARGP",
	/* 01 */ "ByteData",
	/* 02 */ "ByteList",
	/* 03 */ "CharList",
	/* 04 */ "DataObject",
	/* 05 */ "DataObjectList",
	/* 06 */ "DWordData",
	/* 07 */ "FieldList",
	/* 08 */ "Name",
	/* 09 */ "NameString",
	/* 0A */ "ObjectList",
	/* 0B */ "PackageLength",
	/* 0C */ "SuperName",
	/* 0D */ "Target",
	/* 0E */ "TermArg",
	/* 0F */ "TermList",
	/* 10 */ "WordData",
	/* 11 */ "QWordData",
	/* 12 */ "SimpleName",
	/* 13 */ "NameOrRef"
पूर्ण;

स्थिर अक्षर *acpi_ut_get_argument_type_name(u32 arg_type)
अणु

	अगर (arg_type > ARGP_MAX) अणु
		वापस ("Unknown ARGP");
	पूर्ण

	वापस (acpi_gbl_argument_type[arg_type]);
पूर्ण

#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_valid_object_type
 *
 * PARAMETERS:  type            - Object type to be validated
 *
 * RETURN:      TRUE अगर valid object type, FALSE otherwise
 *
 * DESCRIPTION: Validate an object type
 *
 ******************************************************************************/

u8 acpi_ut_valid_object_type(acpi_object_type type)
अणु

	अगर (type > ACPI_TYPE_LOCAL_MAX) अणु

		/* Note: Assumes all TYPEs are contiguous (बाह्यal/local) */

		वापस (FALSE);
	पूर्ण

	वापस (TRUE);
पूर्ण
