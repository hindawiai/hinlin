<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: actables.h - ACPI table management
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACTABLES_H__
#घोषणा __ACTABLES_H__

acpi_status acpi_allocate_root_table(u32 initial_table_count);

/*
 * tbxfroot - Root poपूर्णांकer utilities
 */
u32 acpi_tb_get_rsdp_length(काष्ठा acpi_table_rsdp *rsdp);

acpi_status acpi_tb_validate_rsdp(काष्ठा acpi_table_rsdp *rsdp);

u8 *acpi_tb_scan_memory_क्रम_rsdp(u8 *start_address, u32 length);

/*
 * tbdata - table data काष्ठाure management
 */
acpi_status
acpi_tb_get_next_table_descriptor(u32 *table_index,
				  काष्ठा acpi_table_desc **table_desc);

व्योम
acpi_tb_init_table_descriptor(काष्ठा acpi_table_desc *table_desc,
			      acpi_physical_address address,
			      u8 flags, काष्ठा acpi_table_header *table);

acpi_status
acpi_tb_acquire_temp_table(काष्ठा acpi_table_desc *table_desc,
			   acpi_physical_address address, u8 flags);

व्योम acpi_tb_release_temp_table(काष्ठा acpi_table_desc *table_desc);

acpi_status acpi_tb_validate_temp_table(काष्ठा acpi_table_desc *table_desc);

acpi_status
acpi_tb_verअगरy_temp_table(काष्ठा acpi_table_desc *table_desc,
			  अक्षर *signature, u32 *table_index);

u8 acpi_tb_is_table_loaded(u32 table_index);

व्योम acpi_tb_set_table_loaded_flag(u32 table_index, u8 is_loaded);

/*
 * tbfadt - FADT parse/convert/validate
 */
व्योम acpi_tb_parse_fadt(व्योम);

व्योम acpi_tb_create_local_fadt(काष्ठा acpi_table_header *table, u32 length);

/*
 * tbfind - find ACPI table
 */
acpi_status
acpi_tb_find_table(अक्षर *signature,
		   अक्षर *oem_id, अक्षर *oem_table_id, u32 *table_index);

/*
 * tbinstal - Table removal and deletion
 */
acpi_status acpi_tb_resize_root_table_list(व्योम);

acpi_status acpi_tb_validate_table(काष्ठा acpi_table_desc *table_desc);

व्योम acpi_tb_invalidate_table(काष्ठा acpi_table_desc *table_desc);

व्योम acpi_tb_override_table(काष्ठा acpi_table_desc *old_table_desc);

acpi_status
acpi_tb_acquire_table(काष्ठा acpi_table_desc *table_desc,
		      काष्ठा acpi_table_header **table_ptr,
		      u32 *table_length, u8 *table_flags);

व्योम
acpi_tb_release_table(काष्ठा acpi_table_header *table,
		      u32 table_length, u8 table_flags);

acpi_status
acpi_tb_install_standard_table(acpi_physical_address address,
			       u8 flags,
			       u8 reload, u8 override, u32 *table_index);

व्योम acpi_tb_uninstall_table(काष्ठा acpi_table_desc *table_desc);

acpi_status
acpi_tb_load_table(u32 table_index, काष्ठा acpi_namespace_node *parent_node);

acpi_status
acpi_tb_install_and_load_table(acpi_physical_address address,
			       u8 flags, u8 override, u32 *table_index);

acpi_status acpi_tb_unload_table(u32 table_index);

व्योम acpi_tb_notअगरy_table(u32 event, व्योम *table);

व्योम acpi_tb_terminate(व्योम);

acpi_status acpi_tb_delete_namespace_by_owner(u32 table_index);

acpi_status acpi_tb_allocate_owner_id(u32 table_index);

acpi_status acpi_tb_release_owner_id(u32 table_index);

acpi_status acpi_tb_get_owner_id(u32 table_index, acpi_owner_id *owner_id);

/*
 * tbutils - table manager utilities
 */
acpi_status acpi_tb_initialize_facs(व्योम);

व्योम
acpi_tb_prपूर्णांक_table_header(acpi_physical_address address,
			   काष्ठा acpi_table_header *header);

u8 acpi_tb_checksum(u8 *buffer, u32 length);

acpi_status
acpi_tb_verअगरy_checksum(काष्ठा acpi_table_header *table, u32 length);

व्योम acpi_tb_check_dsdt_header(व्योम);

काष्ठा acpi_table_header *acpi_tb_copy_dsdt(u32 table_index);

व्योम
acpi_tb_install_table_with_override(काष्ठा acpi_table_desc *new_table_desc,
				    u8 override, u32 *table_index);

acpi_status acpi_tb_parse_root_table(acpi_physical_address rsdp_address);

acpi_status
acpi_tb_get_table(काष्ठा acpi_table_desc *table_desc,
		  काष्ठा acpi_table_header **out_table);

व्योम acpi_tb_put_table(काष्ठा acpi_table_desc *table_desc);

/*
 * tbxfload
 */
acpi_status acpi_tb_load_namespace(व्योम);

#पूर्ण_अगर				/* __ACTABLES_H__ */
