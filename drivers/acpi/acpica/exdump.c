<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exdump - Interpreter debug output routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exdump")

/*
 * The following routines are used क्रम debug output only
 */
#अगर defined(ACPI_DEBUG_OUTPUT) || defined(ACPI_DEBUGGER)
/* Local prototypes */
अटल व्योम acpi_ex_out_string(स्थिर अक्षर *title, स्थिर अक्षर *value);

अटल व्योम acpi_ex_out_poपूर्णांकer(स्थिर अक्षर *title, स्थिर व्योम *value);

अटल व्योम
acpi_ex_dump_object(जोड़ acpi_opeअक्रम_object *obj_desc,
		    काष्ठा acpi_exdump_info *info);

अटल व्योम acpi_ex_dump_reference_obj(जोड़ acpi_opeअक्रम_object *obj_desc);

अटल व्योम
acpi_ex_dump_package_obj(जोड़ acpi_opeअक्रम_object *obj_desc,
			 u32 level, u32 index);

/*******************************************************************************
 *
 * Object Descriptor info tables
 *
 * Note: The first table entry must be an INIT opcode and must contain
 * the table length (number of table entries)
 *
 ******************************************************************************/

अटल काष्ठा acpi_exdump_info acpi_ex_dump_पूर्णांकeger[2] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_पूर्णांकeger), शून्यपूर्ण,
	अणुACPI_EXD_UINT64, ACPI_EXD_OFFSET(पूर्णांकeger.value), "Value"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_string[4] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_string), शून्यपूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(string.length), "Length"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(string.poपूर्णांकer), "Pointer"पूर्ण,
	अणुACPI_EXD_STRING, 0, शून्यपूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_buffer[5] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_buffer), शून्यपूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(buffer.length), "Length"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(buffer.poपूर्णांकer), "Pointer"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(buffer.node), "Parent Node"पूर्ण,
	अणुACPI_EXD_BUFFER, 0, शून्यपूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_package[6] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_package), शून्यपूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(package.node), "Parent Node"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(package.flags), "Flags"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(package.count), "Element Count"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(package.elements), "Element List"पूर्ण,
	अणुACPI_EXD_PACKAGE, 0, शून्यपूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_device[4] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_device), शून्यपूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(device.notअगरy_list[0]),
	 "System Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(device.notअगरy_list[1]),
	 "Device Notify"पूर्ण,
	अणुACPI_EXD_HDLR_LIST, ACPI_EXD_OFFSET(device.handler), "Handler"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_event[2] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_event), शून्यपूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(event.os_semaphore), "OsSemaphore"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_method[9] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_method), शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.info_flags), "Info Flags"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.param_count),
	 "Parameter Count"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.sync_level), "Sync Level"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(method.mutex), "Mutex"पूर्ण,
	अणुACPI_EXD_UINT16, ACPI_EXD_OFFSET(method.owner_id), "Owner Id"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(method.thपढ़ो_count), "Thread Count"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(method.aml_length), "Aml Length"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(method.aml_start), "Aml Start"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_mutex[6] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_mutex), शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(mutex.sync_level), "Sync Level"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(mutex.original_sync_level),
	 "Original Sync Level"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(mutex.owner_thपढ़ो), "Owner Thread"पूर्ण,
	अणुACPI_EXD_UINT16, ACPI_EXD_OFFSET(mutex.acquisition_depth),
	 "Acquire Depth"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(mutex.os_mutex), "OsMutex"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_region[8] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_region), शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(region.space_id), "Space Id"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(region.flags), "Flags"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(region.node), "Parent Node"पूर्ण,
	अणुACPI_EXD_ADDRESS, ACPI_EXD_OFFSET(region.address), "Address"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(region.length), "Length"पूर्ण,
	अणुACPI_EXD_HDLR_LIST, ACPI_EXD_OFFSET(region.handler), "Handler"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(region.next), "Next"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_घातer[6] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_घातer), शून्यपूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(घातer_resource.प्रणाली_level),
	 "System Level"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(घातer_resource.resource_order),
	 "Resource Order"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(घातer_resource.notअगरy_list[0]),
	 "System Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(घातer_resource.notअगरy_list[1]),
	 "Device Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(घातer_resource.handler), "Handler"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_processor[7] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_processor), शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(processor.proc_id), "Processor ID"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(processor.length), "Length"पूर्ण,
	अणुACPI_EXD_ADDRESS, ACPI_EXD_OFFSET(processor.address), "Address"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(processor.notअगरy_list[0]),
	 "System Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(processor.notअगरy_list[1]),
	 "Device Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(processor.handler), "Handler"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_thermal[4] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_thermal), शून्यपूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(thermal_zone.notअगरy_list[0]),
	 "System Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(thermal_zone.notअगरy_list[1]),
	 "Device Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(thermal_zone.handler), "Handler"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_buffer_field[3] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_buffer_field), शून्यपूर्ण,
	अणुACPI_EXD_FIELD, 0, शून्यपूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(buffer_field.buffer_obj),
	 "Buffer Object"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_region_field[5] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_region_field), शून्यपूर्ण,
	अणुACPI_EXD_FIELD, 0, शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(field.access_length), "AccessLength"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(field.region_obj), "Region Object"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(field.resource_buffer),
	 "ResourceBuffer"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_bank_field[5] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_bank_field), शून्यपूर्ण,
	अणुACPI_EXD_FIELD, 0, शून्यपूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(bank_field.value), "Value"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(bank_field.region_obj),
	 "Region Object"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(bank_field.bank_obj), "Bank Object"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_index_field[5] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_bank_field), शून्यपूर्ण,
	अणुACPI_EXD_FIELD, 0, शून्यपूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(index_field.value), "Value"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(index_field.index_obj),
	 "Index Object"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(index_field.data_obj), "Data Object"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_reference[9] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_reference), शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(reference.class), "Class"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(reference.target_type), "Target Type"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(reference.value), "Value"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(reference.object), "Object Desc"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(reference.node), "Node"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(reference.where), "Where"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(reference.index_poपूर्णांकer),
	 "Index Pointer"पूर्ण,
	अणुACPI_EXD_REFERENCE, 0, शून्यपूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_address_handler[6] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_address_handler),
	 शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(address_space.space_id), "Space Id"पूर्ण,
	अणुACPI_EXD_HDLR_LIST, ACPI_EXD_OFFSET(address_space.next), "Next"पूर्ण,
	अणुACPI_EXD_RGN_LIST, ACPI_EXD_OFFSET(address_space.region_list),
	 "Region List"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(address_space.node), "Node"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(address_space.context), "Context"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_notअगरy[7] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_notअगरy), शून्यपूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(notअगरy.node), "Node"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(notअगरy.handler_type), "Handler Type"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(notअगरy.handler), "Handler"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(notअगरy.context), "Context"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(notअगरy.next[0]),
	 "Next System Notify"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(notअगरy.next[1]), "Next Device Notify"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_extra[6] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_extra), शून्यपूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(extra.method_REG), "_REG Method"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(extra.scope_node), "Scope Node"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(extra.region_context),
	 "Region Context"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(extra.aml_start), "Aml Start"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(extra.aml_length), "Aml Length"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_data[3] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_data), शून्यपूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(data.handler), "Handler"पूर्ण,
	अणुACPI_EXD_POINTER, ACPI_EXD_OFFSET(data.poपूर्णांकer), "Raw Data"पूर्ण
पूर्ण;

/* Miscellaneous tables */

अटल काष्ठा acpi_exdump_info acpi_ex_dump_common[5] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_common), शून्यपूर्ण,
	अणुACPI_EXD_TYPE, 0, शून्यपूर्ण,
	अणुACPI_EXD_UINT16, ACPI_EXD_OFFSET(common.reference_count),
	 "Reference Count"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(common.flags), "Flags"पूर्ण,
	अणुACPI_EXD_LIST, ACPI_EXD_OFFSET(common.next_object), "Object List"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_field_common[7] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_field_common), शून्यपूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(common_field.field_flags),
	 "Field Flags"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(common_field.access_byte_width),
	 "Access Byte Width"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(common_field.bit_length),
	 "Bit Length"पूर्ण,
	अणुACPI_EXD_UINT8, ACPI_EXD_OFFSET(common_field.start_field_bit_offset),
	 "Field Bit Offset"पूर्ण,
	अणुACPI_EXD_UINT32, ACPI_EXD_OFFSET(common_field.base_byte_offset),
	 "Base Byte Offset"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_OFFSET(common_field.node), "Parent Node"पूर्ण
पूर्ण;

अटल काष्ठा acpi_exdump_info acpi_ex_dump_node[7] = अणु
	अणुACPI_EXD_INIT, ACPI_EXD_TABLE_SIZE(acpi_ex_dump_node), शून्यपूर्ण,
	अणुACPI_EXD_UINT16, ACPI_EXD_NSOFFSET(flags), "Flags"पूर्ण,
	अणुACPI_EXD_UINT16, ACPI_EXD_NSOFFSET(owner_id), "Owner Id"पूर्ण,
	अणुACPI_EXD_LIST, ACPI_EXD_NSOFFSET(object), "Object List"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_NSOFFSET(parent), "Parent"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_NSOFFSET(child), "Child"पूर्ण,
	अणुACPI_EXD_NODE, ACPI_EXD_NSOFFSET(peer), "Peer"पूर्ण
पूर्ण;

/* Dispatch table, indexed by object type */

अटल काष्ठा acpi_exdump_info *acpi_ex_dump_info[] = अणु
	शून्य,
	acpi_ex_dump_पूर्णांकeger,
	acpi_ex_dump_string,
	acpi_ex_dump_buffer,
	acpi_ex_dump_package,
	शून्य,
	acpi_ex_dump_device,
	acpi_ex_dump_event,
	acpi_ex_dump_method,
	acpi_ex_dump_mutex,
	acpi_ex_dump_region,
	acpi_ex_dump_घातer,
	acpi_ex_dump_processor,
	acpi_ex_dump_thermal,
	acpi_ex_dump_buffer_field,
	शून्य,
	शून्य,
	acpi_ex_dump_region_field,
	acpi_ex_dump_bank_field,
	acpi_ex_dump_index_field,
	acpi_ex_dump_reference,
	शून्य,
	शून्य,
	acpi_ex_dump_notअगरy,
	acpi_ex_dump_address_handler,
	शून्य,
	शून्य,
	शून्य,
	acpi_ex_dump_extra,
	acpi_ex_dump_data
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_object
 *
 * PARAMETERS:  obj_desc            - Descriptor to dump
 *              info                - Info table corresponding to this object
 *                                    type
 *
 * RETURN:      None
 *
 * DESCRIPTION: Walk the info table क्रम this object
 *
 ******************************************************************************/

अटल व्योम
acpi_ex_dump_object(जोड़ acpi_opeअक्रम_object *obj_desc,
		    काष्ठा acpi_exdump_info *info)
अणु
	u8 *target;
	स्थिर अक्षर *name;
	u8 count;
	जोड़ acpi_opeअक्रम_object *start;
	जोड़ acpi_opeअक्रम_object *data = शून्य;
	जोड़ acpi_opeअक्रम_object *next;
	काष्ठा acpi_namespace_node *node;

	अगर (!info) अणु
		acpi_os_म_लिखो
		    ("ExDumpObject: Display not implemented for object type %s\n",
		     acpi_ut_get_object_type_name(obj_desc));
		वापस;
	पूर्ण

	/* First table entry must contain the table length (# of table entries) */

	count = info->offset;

	जबतक (count) अणु
		अगर (!obj_desc) अणु
			वापस;
		पूर्ण

		target = ACPI_ADD_PTR(u8, obj_desc, info->offset);
		name = info->name;

		चयन (info->opcode) अणु
		हाल ACPI_EXD_INIT:

			अवरोध;

		हाल ACPI_EXD_TYPE:

			acpi_os_म_लिखो("%20s : %2.2X [%s]\n", "Type",
				       obj_desc->common.type,
				       acpi_ut_get_object_type_name(obj_desc));
			अवरोध;

		हाल ACPI_EXD_UINT8:

			acpi_os_म_लिखो("%20s : %2.2X\n", name, *target);
			अवरोध;

		हाल ACPI_EXD_UINT16:

			acpi_os_म_लिखो("%20s : %4.4X\n", name,
				       ACPI_GET16(target));
			अवरोध;

		हाल ACPI_EXD_UINT32:

			acpi_os_म_लिखो("%20s : %8.8X\n", name,
				       ACPI_GET32(target));
			अवरोध;

		हाल ACPI_EXD_UINT64:

			acpi_os_म_लिखो("%20s : %8.8X%8.8X\n", "Value",
				       ACPI_FORMAT_UINT64(ACPI_GET64(target)));
			अवरोध;

		हाल ACPI_EXD_POINTER:
		हाल ACPI_EXD_ADDRESS:

			acpi_ex_out_poपूर्णांकer(name,
					    *ACPI_CAST_PTR(व्योम *, target));
			अवरोध;

		हाल ACPI_EXD_STRING:

			acpi_ut_prपूर्णांक_string(obj_desc->string.poपूर्णांकer,
					     ACPI_UINT8_MAX);
			acpi_os_म_लिखो("\n");
			अवरोध;

		हाल ACPI_EXD_BUFFER:

			ACPI_DUMP_BUFFER(obj_desc->buffer.poपूर्णांकer,
					 obj_desc->buffer.length);
			अवरोध;

		हाल ACPI_EXD_PACKAGE:

			/* Dump the package contents */

			acpi_os_म_लिखो("\nPackage Contents:\n");
			acpi_ex_dump_package_obj(obj_desc, 0, 0);
			अवरोध;

		हाल ACPI_EXD_FIELD:

			acpi_ex_dump_object(obj_desc,
					    acpi_ex_dump_field_common);
			अवरोध;

		हाल ACPI_EXD_REFERENCE:

			acpi_ex_out_string("Class Name",
					   acpi_ut_get_reference_name
					   (obj_desc));
			acpi_ex_dump_reference_obj(obj_desc);
			अवरोध;

		हाल ACPI_EXD_LIST:

			start = *ACPI_CAST_PTR(व्योम *, target);
			next = start;

			acpi_os_म_लिखो("%20s : %p ", name, next);
			अगर (next) अणु
				acpi_os_म_लिखो("%s (Type %2.2X)",
					       acpi_ut_get_object_type_name
					       (next), next->common.type);

				जबतक (next->common.next_object) अणु
					अगर ((next->common.type ==
					     ACPI_TYPE_LOCAL_DATA) && !data) अणु
						data = next;
					पूर्ण

					next = next->common.next_object;
					acpi_os_म_लिखो("->%p(%s %2.2X)", next,
						       acpi_ut_get_object_type_name
						       (next),
						       next->common.type);

					अगर ((next == start) || (next == data)) अणु
						acpi_os_म_लिखो
						    ("\n**** Error: Object list appears to be circular linked");
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो("- No attached objects");
			पूर्ण

			acpi_os_म_लिखो("\n");
			अवरोध;

		हाल ACPI_EXD_HDLR_LIST:

			start = *ACPI_CAST_PTR(व्योम *, target);
			next = start;

			acpi_os_म_लिखो("%20s : %p", name, next);
			अगर (next) अणु
				acpi_os_म_लिखो("(%s %2.2X)",
					       acpi_ut_get_object_type_name
					       (next),
					       next->address_space.space_id);

				जबतक (next->address_space.next) अणु
					अगर ((next->common.type ==
					     ACPI_TYPE_LOCAL_DATA) && !data) अणु
						data = next;
					पूर्ण

					next = next->address_space.next;
					acpi_os_म_लिखो("->%p(%s %2.2X)", next,
						       acpi_ut_get_object_type_name
						       (next),
						       next->address_space.
						       space_id);

					अगर ((next == start) || (next == data)) अणु
						acpi_os_म_लिखो
						    ("\n**** Error: Handler list appears to be circular linked");
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			acpi_os_म_लिखो("\n");
			अवरोध;

		हाल ACPI_EXD_RGN_LIST:

			start = *ACPI_CAST_PTR(व्योम *, target);
			next = start;

			acpi_os_म_लिखो("%20s : %p", name, next);
			अगर (next) अणु
				acpi_os_म_लिखो("(%s %2.2X)",
					       acpi_ut_get_object_type_name
					       (next), next->common.type);

				जबतक (next->region.next) अणु
					अगर ((next->common.type ==
					     ACPI_TYPE_LOCAL_DATA) && !data) अणु
						data = next;
					पूर्ण

					next = next->region.next;
					acpi_os_म_लिखो("->%p(%s %2.2X)", next,
						       acpi_ut_get_object_type_name
						       (next),
						       next->common.type);

					अगर ((next == start) || (next == data)) अणु
						acpi_os_म_लिखो
						    ("\n**** Error: Region list appears to be circular linked");
						अवरोध;
					पूर्ण
				पूर्ण
			पूर्ण

			acpi_os_म_लिखो("\n");
			अवरोध;

		हाल ACPI_EXD_NODE:

			node =
			    *ACPI_CAST_PTR(काष्ठा acpi_namespace_node *,
					   target);

			acpi_os_म_लिखो("%20s : %p", name, node);
			अगर (node) अणु
				acpi_os_म_लिखो(" [%4.4s]", node->name.ascii);
			पूर्ण
			acpi_os_म_लिखो("\n");
			अवरोध;

		शेष:

			acpi_os_म_लिखो("**** Invalid table opcode [%X] ****\n",
				       info->opcode);
			वापस;
		पूर्ण

		info++;
		count--;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_opeअक्रम
 *
 * PARAMETERS:  *obj_desc       - Poपूर्णांकer to entry to be dumped
 *              depth           - Current nesting depth
 *
 * RETURN:      None
 *
 * DESCRIPTION: Dump an opeअक्रम object
 *
 ******************************************************************************/

व्योम acpi_ex_dump_opeअक्रम(जोड़ acpi_opeअक्रम_object *obj_desc, u32 depth)
अणु
	u32 length;
	u32 index;

	ACPI_FUNCTION_NAME(ex_dump_opeअक्रम);

	/* Check अगर debug output enabled */

	अगर (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_EXEC, _COMPONENT)) अणु
		वापस;
	पूर्ण

	अगर (!obj_desc) अणु

		/* This could be a null element of a package */

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Null Object Descriptor\n"));
		वापस;
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) == ACPI_DESC_TYPE_NAMED) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%p Namespace Node: ",
				  obj_desc));
		ACPI_DUMP_ENTRY(obj_desc, ACPI_LV_EXEC);
		वापस;
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "%p is not a node or operand object: [%s]\n",
				  obj_desc,
				  acpi_ut_get_descriptor_name(obj_desc)));
		ACPI_DUMP_BUFFER(obj_desc, माप(जोड़ acpi_opeअक्रम_object));
		वापस;
	पूर्ण

	/* obj_desc is a valid object */

	अगर (depth > 0) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%*s[%u] %p Refs=%u ",
				  depth, " ", depth, obj_desc,
				  obj_desc->common.reference_count));
	पूर्ण अन्यथा अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%p Refs=%u ",
				  obj_desc, obj_desc->common.reference_count));
	पूर्ण

	/* Decode object type */

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_LOCAL_REFERENCE:

		acpi_os_म_लिखो("Reference: [%s] ",
			       acpi_ut_get_reference_name(obj_desc));

		चयन (obj_desc->reference.class) अणु
		हाल ACPI_REFCLASS_DEBUG:

			acpi_os_म_लिखो("\n");
			अवरोध;

		हाल ACPI_REFCLASS_INDEX:

			acpi_os_म_लिखो("%p\n", obj_desc->reference.object);
			अवरोध;

		हाल ACPI_REFCLASS_TABLE:

			acpi_os_म_लिखो("Table Index %X\n",
				       obj_desc->reference.value);
			अवरोध;

		हाल ACPI_REFCLASS_REFOF:

			acpi_os_म_लिखो("%p [%s]\n", obj_desc->reference.object,
				       acpi_ut_get_type_name(((जोड़
							       acpi_opeअक्रम_object
							       *)
							      obj_desc->
							      reference.
							      object)->common.
							     type));
			अवरोध;

		हाल ACPI_REFCLASS_NAME:

			acpi_ut_repair_name(obj_desc->reference.node->name.
					    ascii);
			acpi_os_म_लिखो("- [%4.4s] (Node %p)\n",
				       obj_desc->reference.node->name.ascii,
				       obj_desc->reference.node);
			अवरोध;

		हाल ACPI_REFCLASS_ARG:
		हाल ACPI_REFCLASS_LOCAL:

			acpi_os_म_लिखो("%X\n", obj_desc->reference.value);
			अवरोध;

		शेष:	/* Unknown reference class */

			acpi_os_म_लिखो("%2.2X\n", obj_desc->reference.class);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		acpi_os_म_लिखो("Buffer length %.2X @ %p\n",
			       obj_desc->buffer.length,
			       obj_desc->buffer.poपूर्णांकer);

		/* Debug only -- dump the buffer contents */

		अगर (obj_desc->buffer.poपूर्णांकer) अणु
			length = obj_desc->buffer.length;
			अगर (length > 128) अणु
				length = 128;
			पूर्ण

			acpi_os_म_लिखो
			    ("Buffer Contents: (displaying length 0x%.2X)\n",
			     length);
			ACPI_DUMP_BUFFER(obj_desc->buffer.poपूर्णांकer, length);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		acpi_os_म_लिखो("Integer %8.8X%8.8X\n",
			       ACPI_FORMAT_UINT64(obj_desc->पूर्णांकeger.value));
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		acpi_os_म_लिखो("Package [Len %X] ElementArray %p\n",
			       obj_desc->package.count,
			       obj_desc->package.elements);

		/*
		 * If elements exist, package element poपूर्णांकer is valid,
		 * and debug_level exceeds 1, dump package's elements.
		 */
		अगर (obj_desc->package.count &&
		    obj_desc->package.elements && acpi_dbg_level > 1) अणु
			क्रम (index = 0; index < obj_desc->package.count;
			     index++) अणु
				acpi_ex_dump_opeअक्रम(obj_desc->package.
						     elements[index],
						     depth + 1);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_REGION:

		acpi_os_म_लिखो("Region %s (%X)",
			       acpi_ut_get_region_name(obj_desc->region.
						       space_id),
			       obj_desc->region.space_id);

		/*
		 * If the address and length have not been evaluated,
		 * करोn't prपूर्णांक them.
		 */
		अगर (!(obj_desc->region.flags & AOPOBJ_DATA_VALID)) अणु
			acpi_os_म_लिखो("\n");
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो(" base %8.8X%8.8X Length %X\n",
				       ACPI_FORMAT_UINT64(obj_desc->region.
							  address),
				       obj_desc->region.length);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_STRING:

		acpi_os_म_लिखो("String length %X @ %p ",
			       obj_desc->string.length,
			       obj_desc->string.poपूर्णांकer);

		acpi_ut_prपूर्णांक_string(obj_desc->string.poपूर्णांकer, ACPI_UINT8_MAX);
		acpi_os_म_लिखो("\n");
		अवरोध;

	हाल ACPI_TYPE_LOCAL_BANK_FIELD:

		acpi_os_म_लिखो("BankField\n");
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REGION_FIELD:

		acpi_os_म_लिखो
		    ("RegionField: Bits=%X AccWidth=%X Lock=%X Update=%X at "
		     "byte=%X bit=%X of below:\n", obj_desc->field.bit_length,
		     obj_desc->field.access_byte_width,
		     obj_desc->field.field_flags & AML_FIELD_LOCK_RULE_MASK,
		     obj_desc->field.field_flags & AML_FIELD_UPDATE_RULE_MASK,
		     obj_desc->field.base_byte_offset,
		     obj_desc->field.start_field_bit_offset);

		acpi_ex_dump_opeअक्रम(obj_desc->field.region_obj, depth + 1);
		अवरोध;

	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

		acpi_os_म_लिखो("IndexField\n");
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:

		acpi_os_म_लिखो("BufferField: %X bits at byte %X bit %X of\n",
			       obj_desc->buffer_field.bit_length,
			       obj_desc->buffer_field.base_byte_offset,
			       obj_desc->buffer_field.start_field_bit_offset);

		अगर (!obj_desc->buffer_field.buffer_obj) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "*NULL*\n"));
		पूर्ण अन्यथा अगर ((obj_desc->buffer_field.buffer_obj)->common.type !=
			   ACPI_TYPE_BUFFER) अणु
			acpi_os_म_लिखो("*not a Buffer*\n");
		पूर्ण अन्यथा अणु
			acpi_ex_dump_opeअक्रम(obj_desc->buffer_field.buffer_obj,
					     depth + 1);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_EVENT:

		acpi_os_म_लिखो("Event\n");
		अवरोध;

	हाल ACPI_TYPE_METHOD:

		acpi_os_म_लिखो("Method(%X) @ %p:%X\n",
			       obj_desc->method.param_count,
			       obj_desc->method.aml_start,
			       obj_desc->method.aml_length);
		अवरोध;

	हाल ACPI_TYPE_MUTEX:

		acpi_os_म_लिखो("Mutex\n");
		अवरोध;

	हाल ACPI_TYPE_DEVICE:

		acpi_os_म_लिखो("Device\n");
		अवरोध;

	हाल ACPI_TYPE_POWER:

		acpi_os_म_लिखो("Power\n");
		अवरोध;

	हाल ACPI_TYPE_PROCESSOR:

		acpi_os_म_लिखो("Processor\n");
		अवरोध;

	हाल ACPI_TYPE_THERMAL:

		acpi_os_म_लिखो("Thermal\n");
		अवरोध;

	शेष:

		/* Unknown Type */

		acpi_os_म_लिखो("Unknown Type %X\n", obj_desc->common.type);
		अवरोध;
	पूर्ण

	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_opeअक्रमs
 *
 * PARAMETERS:  opeअक्रमs            - A list of Opeअक्रम objects
 *		opcode_name	    - AML opcode name
 *		num_opeअक्रमs	    - Opeअक्रम count क्रम this opcode
 *
 * DESCRIPTION: Dump the opeअक्रमs associated with the opcode
 *
 ******************************************************************************/

व्योम
acpi_ex_dump_opeअक्रमs(जोड़ acpi_opeअक्रम_object **opeअक्रमs,
		      स्थिर अक्षर *opcode_name, u32 num_opeअक्रमs)
अणु
	ACPI_FUNCTION_TRACE(ex_dump_opeअक्रमs);

	अगर (!opcode_name) अणु
		opcode_name = "UNKNOWN";
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "**** Start operand dump for opcode [%s], %u operands\n",
			  opcode_name, num_opeअक्रमs));

	अगर (num_opeअक्रमs == 0) अणु
		num_opeअक्रमs = 1;
	पूर्ण

	/* Dump the inभागidual opeअक्रमs */

	जबतक (num_opeअक्रमs) अणु
		acpi_ex_dump_opeअक्रम(*opeअक्रमs, 0);
		opeअक्रमs++;
		num_opeअक्रमs--;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "**** End operand dump for [%s]\n", opcode_name));
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_out* functions
 *
 * PARAMETERS:  title               - Descriptive text
 *              value               - Value to be displayed
 *
 * DESCRIPTION: Object dump output क्रमmatting functions. These functions
 *              reduce the number of क्रमmat strings required and keeps them
 *              all in one place क्रम easy modअगरication.
 *
 ******************************************************************************/

अटल व्योम acpi_ex_out_string(स्थिर अक्षर *title, स्थिर अक्षर *value)
अणु
	acpi_os_म_लिखो("%20s : %s\n", title, value);
पूर्ण

अटल व्योम acpi_ex_out_poपूर्णांकer(स्थिर अक्षर *title, स्थिर व्योम *value)
अणु
	acpi_os_म_लिखो("%20s : %p\n", title, value);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_namespace_node
 *
 * PARAMETERS:  node                - Descriptor to dump
 *              flags               - Force display अगर TRUE
 *
 * DESCRIPTION: Dumps the members of the given.Node
 *
 ******************************************************************************/

व्योम acpi_ex_dump_namespace_node(काष्ठा acpi_namespace_node *node, u32 flags)
अणु

	ACPI_FUNCTION_ENTRY();

	अगर (!flags) अणु

		/* Check अगर debug output enabled */

		अगर (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_OBJECTS, _COMPONENT)) अणु
			वापस;
		पूर्ण
	पूर्ण

	acpi_os_म_लिखो("%20s : %4.4s\n", "Name", acpi_ut_get_node_name(node));
	acpi_os_म_लिखो("%20s : %2.2X [%s]\n", "Type",
		       node->type, acpi_ut_get_type_name(node->type));

	acpi_ex_dump_object(ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object, node),
			    acpi_ex_dump_node);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_reference_obj
 *
 * PARAMETERS:  object              - Descriptor to dump
 *
 * DESCRIPTION: Dumps a reference object
 *
 ******************************************************************************/

अटल व्योम acpi_ex_dump_reference_obj(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु
	काष्ठा acpi_buffer ret_buf;
	acpi_status status;

	ret_buf.length = ACPI_ALLOCATE_LOCAL_BUFFER;

	अगर (obj_desc->reference.class == ACPI_REFCLASS_NAME) अणु
		acpi_os_म_लिखो(" %p ", obj_desc->reference.node);

		status = acpi_ns_handle_to_pathname(obj_desc->reference.node,
						    &ret_buf, TRUE);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो
			    (" Could not convert name to pathname: %s\n",
			     acpi_क्रमmat_exception(status));
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("%s: %s\n",
				       acpi_ut_get_type_name(obj_desc->
							     reference.node->
							     type),
				       (अक्षर *)ret_buf.poपूर्णांकer);
			ACPI_FREE(ret_buf.poपूर्णांकer);
		पूर्ण
	पूर्ण अन्यथा अगर (obj_desc->reference.object) अणु
		अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) ==
		    ACPI_DESC_TYPE_OPERAND) अणु
			acpi_os_म_लिखो("%22s %p", "Target :",
				       obj_desc->reference.object);
			अगर (obj_desc->reference.class == ACPI_REFCLASS_TABLE) अणु
				acpi_os_म_लिखो(" Table Index: %X\n",
					       obj_desc->reference.value);
			पूर्ण अन्यथा अणु
				acpi_os_म_लिखो(" [%s]\n",
					       acpi_ut_get_type_name(((जोड़
								       acpi_opeअक्रम_object
								       *)
								      obj_desc->
								      reference.
								      object)->
								     common.
								     type));
			पूर्ण
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो(" Target: %p\n",
				       obj_desc->reference.object);
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_package_obj
 *
 * PARAMETERS:  obj_desc            - Descriptor to dump
 *              level               - Indentation Level
 *              index               - Package index क्रम this object
 *
 * DESCRIPTION: Dumps the elements of the package
 *
 ******************************************************************************/

अटल व्योम
acpi_ex_dump_package_obj(जोड़ acpi_opeअक्रम_object *obj_desc,
			 u32 level, u32 index)
अणु
	u32 i;

	/* Indentation and index output */

	अगर (level > 0) अणु
		क्रम (i = 0; i < level; i++) अणु
			acpi_os_म_लिखो(" ");
		पूर्ण

		acpi_os_म_लिखो("[%.2d] ", index);
	पूर्ण

	acpi_os_म_लिखो("%p ", obj_desc);

	/* Null package elements are allowed */

	अगर (!obj_desc) अणु
		acpi_os_म_लिखो("[Null Object]\n");
		वापस;
	पूर्ण

	/* Packages may only contain a few object types */

	चयन (obj_desc->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		acpi_os_म_लिखो("[Integer] = %8.8X%8.8X\n",
			       ACPI_FORMAT_UINT64(obj_desc->पूर्णांकeger.value));
		अवरोध;

	हाल ACPI_TYPE_STRING:

		acpi_os_म_लिखो("[String] Value: ");
		acpi_ut_prपूर्णांक_string(obj_desc->string.poपूर्णांकer, ACPI_UINT8_MAX);
		acpi_os_म_लिखो("\n");
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		acpi_os_म_लिखो("[Buffer] Length %.2X = ",
			       obj_desc->buffer.length);
		अगर (obj_desc->buffer.length) अणु
			acpi_ut_debug_dump_buffer(ACPI_CAST_PTR
						  (u8,
						   obj_desc->buffer.poपूर्णांकer),
						  obj_desc->buffer.length,
						  DB_DWORD_DISPLAY, _COMPONENT);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("\n");
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		acpi_os_म_लिखो("[Package] Contains %u Elements:\n",
			       obj_desc->package.count);

		क्रम (i = 0; i < obj_desc->package.count; i++) अणु
			acpi_ex_dump_package_obj(obj_desc->package.elements[i],
						 level + 1, i);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		acpi_os_म_लिखो("[Object Reference] Class [%s]",
			       acpi_ut_get_reference_name(obj_desc));
		acpi_ex_dump_reference_obj(obj_desc);
		अवरोध;

	शेष:

		acpi_os_म_लिखो("[%s] Type: %2.2X\n",
			       acpi_ut_get_type_name(obj_desc->common.type),
			       obj_desc->common.type);
		अवरोध;
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_dump_object_descriptor
 *
 * PARAMETERS:  obj_desc            - Descriptor to dump
 *              flags               - Force display अगर TRUE
 *
 * DESCRIPTION: Dumps the members of the object descriptor given.
 *
 ******************************************************************************/

व्योम
acpi_ex_dump_object_descriptor(जोड़ acpi_opeअक्रम_object *obj_desc, u32 flags)
अणु
	ACPI_FUNCTION_TRACE(ex_dump_object_descriptor);

	अगर (!obj_desc) अणु
		वापस_VOID;
	पूर्ण

	अगर (!flags) अणु

		/* Check अगर debug output enabled */

		अगर (!ACPI_IS_DEBUG_ENABLED(ACPI_LV_OBJECTS, _COMPONENT)) अणु
			वापस_VOID;
		पूर्ण
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) == ACPI_DESC_TYPE_NAMED) अणु
		acpi_ex_dump_namespace_node((काष्ठा acpi_namespace_node *)
					    obj_desc, flags);

		obj_desc = ((काष्ठा acpi_namespace_node *)obj_desc)->object;
		अगर (!obj_desc) अणु
			वापस_VOID;
		पूर्ण

		acpi_os_म_लिखो("\nAttached Object %p", obj_desc);
		अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) == ACPI_DESC_TYPE_NAMED) अणु
			acpi_os_म_लिखो(" - Namespace Node");
		पूर्ण

		acpi_os_म_लिखो(":\n");
		जाओ dump_object;
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) अणु
		acpi_os_म_लिखो("%p is not an ACPI operand object: [%s]\n",
			       obj_desc, acpi_ut_get_descriptor_name(obj_desc));
		वापस_VOID;
	पूर्ण

	/* Validate the object type */

	अगर (obj_desc->common.type > ACPI_TYPE_LOCAL_MAX) अणु
		acpi_os_म_लिखो("Not a known object type: %2.2X\n",
			       obj_desc->common.type);
		वापस_VOID;
	पूर्ण

dump_object:

	अगर (!obj_desc) अणु
		वापस_VOID;
	पूर्ण

	/* Common Fields */

	acpi_ex_dump_object(obj_desc, acpi_ex_dump_common);

	/* Object-specअगरic fields */

	acpi_ex_dump_object(obj_desc, acpi_ex_dump_info[obj_desc->common.type]);

	अगर (obj_desc->common.type == ACPI_TYPE_REGION) अणु
		obj_desc = obj_desc->common.next_object;
		अगर (obj_desc->common.type > ACPI_TYPE_LOCAL_MAX) अणु
			acpi_os_म_लिखो
			    ("Secondary object is not a known object type: %2.2X\n",
			     obj_desc->common.type);

			वापस_VOID;
		पूर्ण

		acpi_os_म_लिखो("\nExtra attached Object (%p):\n", obj_desc);
		acpi_ex_dump_object(obj_desc,
				    acpi_ex_dump_info[obj_desc->common.type]);
	पूर्ण

	वापस_VOID;
पूर्ण

#पूर्ण_अगर
