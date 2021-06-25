<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: evgpeinit - System GPE initialization and update
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EVENTS
ACPI_MODULE_NAME("evgpeinit")
#अगर (!ACPI_REDUCED_HARDWARE)	/* Entire module */
/*
 * Note: History of _PRW support in ACPICA
 *
 * Originally (2000 - 2010), the GPE initialization code perक्रमmed a walk of
 * the entire namespace to execute the _PRW methods and detect all GPEs
 * capable of waking the प्रणाली.
 *
 * As of 10/2010, the _PRW method execution has been हटाओd since it is
 * actually unnecessary. The host OS must in fact execute all _PRW methods
 * in order to identअगरy the device/घातer-resource dependencies. We now put
 * the onus on the host OS to identअगरy the wake GPEs as part of this process
 * and to inक्रमm ACPICA of these GPEs via the acpi_setup_gpe_क्रम_wake पूर्णांकerface. This
 * not only reduces the complनिकासy of the ACPICA initialization code, but in
 * some हालs (on प्रणालीs with very large namespaces) it should reduce the
 * kernel boot समय as well.
 */

#अगर_घोषित ACPI_GPE_USE_LOGICAL_ADDRESSES
#घोषणा ACPI_FADT_GPE_BLOCK_ADDRESS(N)	\
	acpi_gbl_FADT.xgpe##N##_block.space_id == \
					ACPI_ADR_SPACE_SYSTEM_MEMORY ? \
		(u64)acpi_gbl_xgpe##N##_block_logical_address : \
		acpi_gbl_FADT.xgpe##N##_block.address
#अन्यथा
#घोषणा ACPI_FADT_GPE_BLOCK_ADDRESS(N)	acpi_gbl_FADT.xgpe##N##_block.address
#पूर्ण_अगर		/* ACPI_GPE_USE_LOGICAL_ADDRESSES */

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_gpe_initialize
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the GPE data काष्ठाures and the FADT GPE 0/1 blocks
 *
 ******************************************************************************/
acpi_status acpi_ev_gpe_initialize(व्योम)
अणु
	u32 रेजिस्टर_count0 = 0;
	u32 रेजिस्टर_count1 = 0;
	u32 gpe_number_max = 0;
	acpi_status status;
	u64 address;

	ACPI_FUNCTION_TRACE(ev_gpe_initialize);

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_INIT,
			      "Initializing General Purpose Events (GPEs):\n"));

	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Initialize the GPE Block(s) defined in the FADT
	 *
	 * Why the GPE रेजिस्टर block lengths are भागided by 2:  From the ACPI
	 * Spec, section "General-Purpose Event Registers", we have:
	 *
	 * "Each रेजिस्टर block contains two रेजिस्टरs of equal length
	 *  GPEx_STS and GPEx_EN (where x is 0 or 1). The length of the
	 *  GPE0_STS and GPE0_EN रेजिस्टरs is equal to half the GPE0_LEN
	 *  The length of the GPE1_STS and GPE1_EN रेजिस्टरs is equal to
	 *  half the GPE1_LEN. If a generic रेजिस्टर block is not supported
	 *  then its respective block poपूर्णांकer and block length values in the
	 *  FADT table contain zeros. The GPE0_LEN and GPE1_LEN करो not need
	 *  to be the same size."
	 */

	/*
	 * Determine the maximum GPE number क्रम this machine.
	 *
	 * Note: both GPE0 and GPE1 are optional, and either can exist without
	 * the other.
	 *
	 * If EITHER the रेजिस्टर length OR the block address are zero, then that
	 * particular block is not supported.
	 */
	address = ACPI_FADT_GPE_BLOCK_ADDRESS(0);

	अगर (acpi_gbl_FADT.gpe0_block_length && address) अणु

		/* GPE block 0 exists (has both length and address > 0) */

		रेजिस्टर_count0 = (u16)(acpi_gbl_FADT.gpe0_block_length / 2);
		gpe_number_max =
		    (रेजिस्टर_count0 * ACPI_GPE_REGISTER_WIDTH) - 1;

		/* Install GPE Block 0 */

		status = acpi_ev_create_gpe_block(acpi_gbl_fadt_gpe_device,
						  address,
						  acpi_gbl_FADT.xgpe0_block.
						  space_id, रेजिस्टर_count0, 0,
						  acpi_gbl_FADT.sci_पूर्णांकerrupt,
						  &acpi_gbl_gpe_fadt_blocks[0]);

		अगर (ACPI_FAILURE(status)) अणु
			ACPI_EXCEPTION((AE_INFO, status,
					"Could not create GPE Block 0"));
		पूर्ण
	पूर्ण

	address = ACPI_FADT_GPE_BLOCK_ADDRESS(1);

	अगर (acpi_gbl_FADT.gpe1_block_length && address) अणु

		/* GPE block 1 exists (has both length and address > 0) */

		रेजिस्टर_count1 = (u16)(acpi_gbl_FADT.gpe1_block_length / 2);

		/* Check क्रम GPE0/GPE1 overlap (अगर both banks exist) */

		अगर ((रेजिस्टर_count0) &&
		    (gpe_number_max >= acpi_gbl_FADT.gpe1_base)) अणु
			ACPI_ERROR((AE_INFO,
				    "GPE0 block (GPE 0 to %u) overlaps the GPE1 block "
				    "(GPE %u to %u) - Ignoring GPE1",
				    gpe_number_max, acpi_gbl_FADT.gpe1_base,
				    acpi_gbl_FADT.gpe1_base +
				    ((रेजिस्टर_count1 *
				      ACPI_GPE_REGISTER_WIDTH) - 1)));

			/* Ignore GPE1 block by setting the रेजिस्टर count to zero */

			रेजिस्टर_count1 = 0;
		पूर्ण अन्यथा अणु
			/* Install GPE Block 1 */

			status =
			    acpi_ev_create_gpe_block(acpi_gbl_fadt_gpe_device,
						     address,
						     acpi_gbl_FADT.xgpe1_block.
						     space_id, रेजिस्टर_count1,
						     acpi_gbl_FADT.gpe1_base,
						     acpi_gbl_FADT.
						     sci_पूर्णांकerrupt,
						     &acpi_gbl_gpe_fadt_blocks
						     [1]);

			अगर (ACPI_FAILURE(status)) अणु
				ACPI_EXCEPTION((AE_INFO, status,
						"Could not create GPE Block 1"));
			पूर्ण

			/*
			 * GPE0 and GPE1 करो not have to be contiguous in the GPE number
			 * space. However, GPE0 always starts at GPE number zero.
			 */
		पूर्ण
	पूर्ण

	/* Exit अगर there are no GPE रेजिस्टरs */

	अगर ((रेजिस्टर_count0 + रेजिस्टर_count1) == 0) अणु

		/* GPEs are not required by ACPI, this is OK */

		ACPI_DEBUG_PRINT((ACPI_DB_INIT,
				  "There are no GPE blocks defined in the FADT\n"));
		जाओ cleanup;
	पूर्ण

cleanup:
	(व्योम)acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_update_gpes
 *
 * PARAMETERS:  table_owner_id      - ID of the newly-loaded ACPI table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Check क्रम new GPE methods (_Lxx/_Exx) made available as a
 *              result of a Load() or load_table() operation. If new GPE
 *              methods have been installed, रेजिस्टर the new methods.
 *
 ******************************************************************************/

व्योम acpi_ev_update_gpes(acpi_owner_id table_owner_id)
अणु
	काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info;
	काष्ठा acpi_gpe_block_info *gpe_block;
	काष्ठा acpi_gpe_walk_info walk_info;
	acpi_status status = AE_OK;

	/*
	 * Find any _Lxx/_Exx GPE methods that have just been loaded.
	 *
	 * Any GPEs that correspond to new _Lxx/_Exx methods are immediately
	 * enabled.
	 *
	 * Examine the namespace underneath each gpe_device within the
	 * gpe_block lists.
	 */
	status = acpi_ut_acquire_mutex(ACPI_MTX_EVENTS);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण

	walk_info.count = 0;
	walk_info.owner_id = table_owner_id;
	walk_info.execute_by_owner_id = TRUE;

	/* Walk the पूर्णांकerrupt level descriptor list */

	gpe_xrupt_info = acpi_gbl_gpe_xrupt_list_head;
	जबतक (gpe_xrupt_info) अणु

		/* Walk all Gpe Blocks attached to this पूर्णांकerrupt level */

		gpe_block = gpe_xrupt_info->gpe_block_list_head;
		जबतक (gpe_block) अणु
			walk_info.gpe_block = gpe_block;
			walk_info.gpe_device = gpe_block->node;

			status = acpi_ns_walk_namespace(ACPI_TYPE_METHOD,
							walk_info.gpe_device,
							ACPI_UINT32_MAX,
							ACPI_NS_WALK_NO_UNLOCK,
							acpi_ev_match_gpe_method,
							शून्य, &walk_info, शून्य);
			अगर (ACPI_FAILURE(status)) अणु
				ACPI_EXCEPTION((AE_INFO, status,
						"While decoding _Lxx/_Exx methods"));
			पूर्ण

			gpe_block = gpe_block->next;
		पूर्ण

		gpe_xrupt_info = gpe_xrupt_info->next;
	पूर्ण

	अगर (walk_info.count) अणु
		ACPI_INFO(("Enabled %u new GPEs", walk_info.count));
	पूर्ण

	(व्योम)acpi_ut_release_mutex(ACPI_MTX_EVENTS);
	वापस;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ev_match_gpe_method
 *
 * PARAMETERS:  Callback from walk_namespace
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Called from acpi_walk_namespace. Expects each object to be a
 *              control method under the _GPE portion of the namespace.
 *              Extract the name and GPE type from the object, saving this
 *              inक्रमmation क्रम quick lookup during GPE dispatch. Allows a
 *              per-owner_id evaluation अगर execute_by_owner_id is TRUE in the
 *              walk_info parameter block.
 *
 *              The name of each GPE control method is of the क्रमm:
 *              "_Lxx" or "_Exx", where:
 *                  L      - means that the GPE is level triggered
 *                  E      - means that the GPE is edge triggered
 *                  xx     - is the GPE number [in HEX]
 *
 * If walk_info->execute_by_owner_id is TRUE, we only execute examine GPE methods
 * with that owner.
 *
 ******************************************************************************/

acpi_status
acpi_ev_match_gpe_method(acpi_handle obj_handle,
			 u32 level, व्योम *context, व्योम **वापस_value)
अणु
	काष्ठा acpi_namespace_node *method_node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, obj_handle);
	काष्ठा acpi_gpe_walk_info *walk_info =
	    ACPI_CAST_PTR(काष्ठा acpi_gpe_walk_info, context);
	काष्ठा acpi_gpe_event_info *gpe_event_info;
	acpi_status status;
	u32 gpe_number;
	u8 temp_gpe_number;
	अक्षर name[ACPI_NAMESEG_SIZE + 1];
	u8 type;

	ACPI_FUNCTION_TRACE(ev_match_gpe_method);

	/* Check अगर requested owner_id matches this owner_id */

	अगर ((walk_info->execute_by_owner_id) &&
	    (method_node->owner_id != walk_info->owner_id)) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/*
	 * Match and decode the _Lxx and _Exx GPE method names
	 *
	 * 1) Extract the method name and null terminate it
	 */
	ACPI_MOVE_32_TO_32(name, &method_node->name.पूर्णांकeger);
	name[ACPI_NAMESEG_SIZE] = 0;

	/* 2) Name must begin with an underscore */

	अगर (name[0] != '_') अणु
		वापस_ACPI_STATUS(AE_OK);	/* Ignore this method */
	पूर्ण

	/*
	 * 3) Edge/Level determination is based on the 2nd अक्षरacter
	 *    of the method name
	 */
	चयन (name[1]) अणु
	हाल 'L':

		type = ACPI_GPE_LEVEL_TRIGGERED;
		अवरोध;

	हाल 'E':

		type = ACPI_GPE_EDGE_TRIGGERED;
		अवरोध;

	शेष:

		/* Unknown method type, just ignore it */

		ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
				  "Ignoring unknown GPE method type: %s "
				  "(name not of form _Lxx or _Exx)", name));
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* 4) The last two अक्षरacters of the name are the hex GPE Number */

	status = acpi_ut_ascii_to_hex_byte(&name[2], &temp_gpe_number);
	अगर (ACPI_FAILURE(status)) अणु

		/* Conversion failed; invalid method, just ignore it */

		ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
				  "Could not extract GPE number from name: %s "
				  "(name is not of form _Lxx or _Exx)", name));
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Ensure that we have a valid GPE number क्रम this GPE block */

	gpe_number = (u32)temp_gpe_number;
	gpe_event_info =
	    acpi_ev_low_get_gpe_info(gpe_number, walk_info->gpe_block);
	अगर (!gpe_event_info) अणु
		/*
		 * This gpe_number is not valid क्रम this GPE block, just ignore it.
		 * However, it may be valid क्रम a dअगरferent GPE block, since GPE0
		 * and GPE1 methods both appear under \_GPE.
		 */
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर ((ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	     ACPI_GPE_DISPATCH_HANDLER) ||
	    (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	     ACPI_GPE_DISPATCH_RAW_HANDLER)) अणु

		/* If there is alपढ़ोy a handler, ignore this GPE method */

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (ACPI_GPE_DISPATCH_TYPE(gpe_event_info->flags) ==
	    ACPI_GPE_DISPATCH_METHOD) अणु
		/*
		 * If there is alपढ़ोy a method, ignore this method. But check
		 * क्रम a type mismatch (अगर both the _Lxx AND _Exx exist)
		 */
		अगर (type != (gpe_event_info->flags & ACPI_GPE_XRUPT_TYPE_MASK)) अणु
			ACPI_ERROR((AE_INFO,
				    "For GPE 0x%.2X, found both _L%2.2X and _E%2.2X methods",
				    gpe_number, gpe_number, gpe_number));
		पूर्ण
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Disable the GPE in हाल it's been enabled alपढ़ोy. */

	(व्योम)acpi_hw_low_set_gpe(gpe_event_info, ACPI_GPE_DISABLE);

	/*
	 * Add the GPE inक्रमmation from above to the gpe_event_info block क्रम
	 * use during dispatch of this GPE.
	 */
	gpe_event_info->flags &= ~(ACPI_GPE_DISPATCH_MASK);
	gpe_event_info->flags |= (u8)(type | ACPI_GPE_DISPATCH_METHOD);
	gpe_event_info->dispatch.method_node = method_node;

	ACPI_DEBUG_PRINT((ACPI_DB_LOAD,
			  "Registered GPE method %s as GPE number 0x%.2X\n",
			  name, gpe_number));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
