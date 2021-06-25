<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acevents.h - Event subcomponent prototypes and defines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACEVENTS_H__
#घोषणा __ACEVENTS_H__

/*
 * Conditions to trigger post enabling GPE polling:
 * It is not sufficient to trigger edge-triggered GPE with specअगरic GPE
 * chips, software need to poll once after enabling.
 */
#अगर_घोषित ACPI_USE_GPE_POLLING
#घोषणा ACPI_GPE_IS_POLLING_NEEDED(__gpe__)             \
	((__gpe__)->runसमय_count == 1 &&                   \
	 (__gpe__)->flags & ACPI_GPE_INITIALIZED &&         \
	 ((__gpe__)->flags & ACPI_GPE_XRUPT_TYPE_MASK) == ACPI_GPE_EDGE_TRIGGERED)
#अन्यथा
#घोषणा ACPI_GPE_IS_POLLING_NEEDED(__gpe__)             FALSE
#पूर्ण_अगर

/*
 * evevent
 */
acpi_status acpi_ev_initialize_events(व्योम);

acpi_status acpi_ev_install_xrupt_handlers(व्योम);

u32 acpi_ev_fixed_event_detect(व्योम);

/*
 * evmisc
 */
u8 acpi_ev_is_notअगरy_object(काष्ठा acpi_namespace_node *node);

u32 acpi_ev_get_gpe_number_index(u32 gpe_number);

acpi_status
acpi_ev_queue_notअगरy_request(काष्ठा acpi_namespace_node *node,
			     u32 notअगरy_value);

/*
 * evglock - Global Lock support
 */
acpi_status acpi_ev_init_global_lock_handler(व्योम);

ACPI_HW_DEPENDENT_RETURN_OK(acpi_status
			    acpi_ev_acquire_global_lock(u16 समयout))
ACPI_HW_DEPENDENT_RETURN_OK(acpi_status acpi_ev_release_global_lock(व्योम))

acpi_status acpi_ev_हटाओ_global_lock_handler(व्योम);

/*
 * evgpe - Low-level GPE support
 */
u32 acpi_ev_gpe_detect(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_list);

acpi_status
acpi_ev_update_gpe_enable_mask(काष्ठा acpi_gpe_event_info *gpe_event_info);

acpi_status acpi_ev_enable_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info);

acpi_status
acpi_ev_mask_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info, u8 is_masked);

acpi_status
acpi_ev_add_gpe_reference(काष्ठा acpi_gpe_event_info *gpe_event_info,
			  u8 clear_on_enable);

acpi_status
acpi_ev_हटाओ_gpe_reference(काष्ठा acpi_gpe_event_info *gpe_event_info);

काष्ठा acpi_gpe_event_info *acpi_ev_get_gpe_event_info(acpi_handle gpe_device,
						       u32 gpe_number);

काष्ठा acpi_gpe_event_info *acpi_ev_low_get_gpe_info(u32 gpe_number,
						     काष्ठा acpi_gpe_block_info
						     *gpe_block);

acpi_status acpi_ev_finish_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info);

u32
acpi_ev_detect_gpe(काष्ठा acpi_namespace_node *gpe_device,
		   काष्ठा acpi_gpe_event_info *gpe_event_info, u32 gpe_number);

/*
 * evgpeblk - Upper-level GPE block support
 */
acpi_status
acpi_ev_create_gpe_block(काष्ठा acpi_namespace_node *gpe_device,
			 u64 address,
			 u8 space_id,
			 u32 रेजिस्टर_count,
			 u16 gpe_block_base_number,
			 u32 पूर्णांकerrupt_number,
			 काष्ठा acpi_gpe_block_info **वापस_gpe_block);

acpi_status
acpi_ev_initialize_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			     काष्ठा acpi_gpe_block_info *gpe_block,
			     व्योम *context);

ACPI_HW_DEPENDENT_RETURN_OK(acpi_status
			    acpi_ev_delete_gpe_block(काष्ठा acpi_gpe_block_info
						     *gpe_block))

u32
acpi_ev_gpe_dispatch(काष्ठा acpi_namespace_node *gpe_device,
		     काष्ठा acpi_gpe_event_info *gpe_event_info,
		     u32 gpe_number);

/*
 * evgpeinit - GPE initialization and update
 */
acpi_status acpi_ev_gpe_initialize(व्योम);

ACPI_HW_DEPENDENT_RETURN_VOID(व्योम
			      acpi_ev_update_gpes(acpi_owner_id table_owner_id))

acpi_status
acpi_ev_match_gpe_method(acpi_handle obj_handle,
			 u32 level, व्योम *context, व्योम **वापस_value);

/*
 * evgpeutil - GPE utilities
 */
acpi_status
acpi_ev_walk_gpe_list(acpi_gpe_callback gpe_walk_callback, व्योम *context);

acpi_status
acpi_ev_get_gpe_device(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
		       काष्ठा acpi_gpe_block_info *gpe_block, व्योम *context);

acpi_status
acpi_ev_get_gpe_xrupt_block(u32 पूर्णांकerrupt_number,
			    काष्ठा acpi_gpe_xrupt_info **gpe_xrupt_block);

acpi_status acpi_ev_delete_gpe_xrupt(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt);

acpi_status
acpi_ev_delete_gpe_handlers(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			    काष्ठा acpi_gpe_block_info *gpe_block,
			    व्योम *context);

/*
 * evhandler - Address space handling
 */
जोड़ acpi_opeअक्रम_object *acpi_ev_find_region_handler(acpi_adr_space_type
						       space_id,
						       जोड़ acpi_opeअक्रम_object
						       *handler_obj);

u8
acpi_ev_has_शेष_handler(काष्ठा acpi_namespace_node *node,
			    acpi_adr_space_type space_id);

acpi_status acpi_ev_install_region_handlers(व्योम);

acpi_status
acpi_ev_install_space_handler(काष्ठा acpi_namespace_node *node,
			      acpi_adr_space_type space_id,
			      acpi_adr_space_handler handler,
			      acpi_adr_space_setup setup, व्योम *context);

/*
 * evregion - Operation region support
 */
acpi_status acpi_ev_initialize_op_regions(व्योम);

acpi_status
acpi_ev_address_space_dispatch(जोड़ acpi_opeअक्रम_object *region_obj,
			       जोड़ acpi_opeअक्रम_object *field_obj,
			       u32 function,
			       u32 region_offset, u32 bit_width, u64 *value);

acpi_status
acpi_ev_attach_region(जोड़ acpi_opeअक्रम_object *handler_obj,
		      जोड़ acpi_opeअक्रम_object *region_obj,
		      u8 acpi_ns_is_locked);

व्योम
acpi_ev_detach_region(जोड़ acpi_opeअक्रम_object *region_obj,
		      u8 acpi_ns_is_locked);

व्योम
acpi_ev_execute_reg_methods(काष्ठा acpi_namespace_node *node,
			    acpi_adr_space_type space_id, u32 function);

acpi_status
acpi_ev_execute_reg_method(जोड़ acpi_opeअक्रम_object *region_obj, u32 function);

/*
 * evregini - Region initialization and setup
 */
acpi_status
acpi_ev_प्रणाली_memory_region_setup(acpi_handle handle,
				   u32 function,
				   व्योम *handler_context,
				   व्योम **region_context);

acpi_status
acpi_ev_io_space_region_setup(acpi_handle handle,
			      u32 function,
			      व्योम *handler_context, व्योम **region_context);

acpi_status
acpi_ev_pci_config_region_setup(acpi_handle handle,
				u32 function,
				व्योम *handler_context, व्योम **region_context);

acpi_status
acpi_ev_cmos_region_setup(acpi_handle handle,
			  u32 function,
			  व्योम *handler_context, व्योम **region_context);

acpi_status
acpi_ev_pci_bar_region_setup(acpi_handle handle,
			     u32 function,
			     व्योम *handler_context, व्योम **region_context);

acpi_status
acpi_ev_शेष_region_setup(acpi_handle handle,
			     u32 function,
			     व्योम *handler_context, व्योम **region_context);

acpi_status acpi_ev_initialize_region(जोड़ acpi_opeअक्रम_object *region_obj);

u8 acpi_ev_is_pci_root_bridge(काष्ठा acpi_namespace_node *node);

/*
 * evsci - SCI (System Control Interrupt) handling/dispatch
 */
u32 ACPI_SYSTEM_XFACE acpi_ev_gpe_xrupt_handler(व्योम *context);

u32 acpi_ev_sci_dispatch(व्योम);

u32 acpi_ev_install_sci_handler(व्योम);

acpi_status acpi_ev_हटाओ_all_sci_handlers(व्योम);

ACPI_HW_DEPENDENT_RETURN_VOID(व्योम acpi_ev_terminate(व्योम))
#पूर्ण_अगर				/* __ACEVENTS_H__  */
