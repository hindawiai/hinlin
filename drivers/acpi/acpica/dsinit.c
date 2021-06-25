<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dsinit - Object initialization namespace walk
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"
#समावेश "actables.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsinit")

/* Local prototypes */
अटल acpi_status
acpi_ds_init_one_object(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_one_object
 *
 * PARAMETERS:  obj_handle      - Node क्रम the object
 *              level           - Current nesting level
 *              context         - Poपूर्णांकs to a init info काष्ठा
 *              वापस_value    - Not used
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Callback from acpi_walk_namespace. Invoked क्रम every object
 *              within the namespace.
 *
 *              Currently, the only objects that require initialization are:
 *              1) Methods
 *              2) Operation Regions
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_init_one_object(acpi_handle obj_handle,
			u32 level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_init_walk_info *info =
	    (काष्ठा acpi_init_walk_info *)context;
	काष्ठा acpi_namespace_node *node =
	    (काष्ठा acpi_namespace_node *)obj_handle;
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_ENTRY();

	/*
	 * We are only पूर्णांकerested in NS nodes owned by the table that
	 * was just loaded
	 */
	अगर (node->owner_id != info->owner_id) अणु
		वापस (AE_OK);
	पूर्ण

	info->object_count++;

	/* And even then, we are only पूर्णांकerested in a few object types */

	चयन (acpi_ns_get_type(obj_handle)) अणु
	हाल ACPI_TYPE_REGION:

		status = acpi_ds_initialize_region(obj_handle);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"During Region initialization %p [%4.4s]",
					obj_handle,
					acpi_ut_get_node_name(obj_handle)));
		पूर्ण

		info->op_region_count++;
		अवरोध;

	हाल ACPI_TYPE_METHOD:
		/*
		 * Auto-serialization support. We will examine each method that is
		 * not_serialized to determine अगर it creates any Named objects. If
		 * it करोes, it will be marked serialized to prevent problems अगर
		 * the method is entered by two or more thपढ़ोs and an attempt is
		 * made to create the same named object twice -- which results in
		 * an AE_ALREADY_EXISTS exception and method पात.
		 */
		info->method_count++;
		obj_desc = acpi_ns_get_attached_object(node);
		अगर (!obj_desc) अणु
			अवरोध;
		पूर्ण

		/* Ignore अगर alपढ़ोy serialized */

		अगर (obj_desc->method.info_flags & ACPI_METHOD_SERIALIZED) अणु
			info->serial_method_count++;
			अवरोध;
		पूर्ण

		अगर (acpi_gbl_स्वतः_serialize_methods) अणु

			/* Parse/scan method and serialize it अगर necessary */

			acpi_ds_स्वतः_serialize_method(node, obj_desc);
			अगर (obj_desc->method.
			    info_flags & ACPI_METHOD_SERIALIZED) अणु

				/* Method was just converted to Serialized */

				info->serial_method_count++;
				info->serialized_method_count++;
				अवरोध;
			पूर्ण
		पूर्ण

		info->non_serial_method_count++;
		अवरोध;

	हाल ACPI_TYPE_DEVICE:

		info->device_count++;
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	/*
	 * We ignore errors from above, and always वापस OK, since
	 * we करोn't want to पात the walk on a single error.
	 */
	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_initialize_objects
 *
 * PARAMETERS:  table_desc      - Descriptor क्रम parent ACPI table
 *              start_node      - Root of subtree to be initialized.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Walk the namespace starting at "StartNode" and perक्रमm any
 *              necessary initialization on the objects found therein
 *
 ******************************************************************************/

acpi_status
acpi_ds_initialize_objects(u32 table_index,
			   काष्ठा acpi_namespace_node *start_node)
अणु
	acpi_status status;
	काष्ठा acpi_init_walk_info info;
	काष्ठा acpi_table_header *table;
	acpi_owner_id owner_id;

	ACPI_FUNCTION_TRACE(ds_initialize_objects);

	status = acpi_tb_get_owner_id(table_index, &owner_id);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
			  "**** Starting initialization of namespace objects ****\n"));

	/* Set all init info to zero */

	स_रखो(&info, 0, माप(काष्ठा acpi_init_walk_info));

	info.owner_id = owner_id;
	info.table_index = table_index;

	/* Walk entire namespace from the supplied root */

	/*
	 * We करोn't use acpi_walk_namespace since we करो not want to acquire
	 * the namespace पढ़ोer lock.
	 */
	status =
	    acpi_ns_walk_namespace(ACPI_TYPE_ANY, start_node, ACPI_UINT32_MAX,
				   ACPI_NS_WALK_NO_UNLOCK,
				   acpi_ds_init_one_object, शून्य, &info, शून्य);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status, "During WalkNamespace"));
	पूर्ण

	status = acpi_get_table_by_index(table_index, &table);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* DSDT is always the first AML table */

	अगर (ACPI_COMPARE_NAMESEG(table->signature, ACPI_SIG_DSDT)) अणु
		ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
				      "\nACPI table initialization:\n"));
	पूर्ण

	/* Summary of objects initialized */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Table [%4.4s: %-8.8s] (id %.2X) - %4u Objects with %3u Devices, "
			      "%3u Regions, %4u Methods (%u/%u/%u Serial/Non/Cvt)\n",
			      table->signature, table->oem_table_id, owner_id,
			      info.object_count, info.device_count,
			      info.op_region_count, info.method_count,
			      info.serial_method_count,
			      info.non_serial_method_count,
			      info.serialized_method_count));

	ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH, "%u Methods, %u Regions\n",
			  info.method_count, info.op_region_count));

	वापस_ACPI_STATUS(AE_OK);
पूर्ण
