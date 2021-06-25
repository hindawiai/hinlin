<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: achware.h -- hardware specअगरic पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACHWARE_H__
#घोषणा __ACHWARE_H__

/* Values क्रम the _SST predefined method */

#घोषणा ACPI_SST_INDICATOR_OFF  0
#घोषणा ACPI_SST_WORKING        1
#घोषणा ACPI_SST_WAKING         2
#घोषणा ACPI_SST_SLEEPING       3
#घोषणा ACPI_SST_SLEEP_CONTEXT  4

/*
 * hwacpi - high level functions
 */
acpi_status acpi_hw_set_mode(u32 mode);

u32 acpi_hw_get_mode(व्योम);

/*
 * hwregs - ACPI Register I/O
 */
acpi_status
acpi_hw_validate_रेजिस्टर(काष्ठा acpi_generic_address *reg,
			  u8 max_bit_width, u64 *address);

acpi_status acpi_hw_पढ़ो(u64 *value, काष्ठा acpi_generic_address *reg);

acpi_status acpi_hw_ग_लिखो(u64 value, काष्ठा acpi_generic_address *reg);

काष्ठा acpi_bit_रेजिस्टर_info *acpi_hw_get_bit_रेजिस्टर_info(u32 रेजिस्टर_id);

acpi_status acpi_hw_ग_लिखो_pm1_control(u32 pm1a_control, u32 pm1b_control);

acpi_status acpi_hw_रेजिस्टर_पढ़ो(u32 रेजिस्टर_id, u32 *वापस_value);

acpi_status acpi_hw_रेजिस्टर_ग_लिखो(u32 रेजिस्टर_id, u32 value);

acpi_status acpi_hw_clear_acpi_status(व्योम);

/*
 * hwsleep - sleep/wake support (Legacy sleep रेजिस्टरs)
 */
acpi_status acpi_hw_legacy_sleep(u8 sleep_state);

acpi_status acpi_hw_legacy_wake_prep(u8 sleep_state);

acpi_status acpi_hw_legacy_wake(u8 sleep_state);

/*
 * hwesleep - sleep/wake support (Extended FADT-V5 sleep रेजिस्टरs)
 */
व्योम acpi_hw_execute_sleep_method(अक्षर *method_name, u32 पूर्णांकeger_argument);

acpi_status acpi_hw_extended_sleep(u8 sleep_state);

acpi_status acpi_hw_extended_wake_prep(u8 sleep_state);

acpi_status acpi_hw_extended_wake(u8 sleep_state);

/*
 * hwvalid - Port I/O with validation
 */
acpi_status acpi_hw_पढ़ो_port(acpi_io_address address, u32 *value, u32 width);

acpi_status acpi_hw_ग_लिखो_port(acpi_io_address address, u32 value, u32 width);

acpi_status acpi_hw_validate_io_block(u64 address, u32 bit_width, u32 count);

/*
 * hwgpe - GPE support
 */
acpi_status acpi_hw_gpe_पढ़ो(u64 *value, काष्ठा acpi_gpe_address *reg);

acpi_status acpi_hw_gpe_ग_लिखो(u64 value, काष्ठा acpi_gpe_address *reg);

u32 acpi_hw_get_gpe_रेजिस्टर_bit(काष्ठा acpi_gpe_event_info *gpe_event_info);

acpi_status
acpi_hw_low_set_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info, u32 action);

acpi_status
acpi_hw_disable_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			  काष्ठा acpi_gpe_block_info *gpe_block, व्योम *context);

acpi_status acpi_hw_clear_gpe(काष्ठा acpi_gpe_event_info *gpe_event_info);

acpi_status
acpi_hw_clear_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
			काष्ठा acpi_gpe_block_info *gpe_block, व्योम *context);

acpi_status
acpi_hw_get_gpe_status(काष्ठा acpi_gpe_event_info *gpe_event_info,
		       acpi_event_status *event_status);

acpi_status acpi_hw_disable_all_gpes(व्योम);

acpi_status acpi_hw_enable_all_runसमय_gpes(व्योम);

acpi_status acpi_hw_enable_all_wakeup_gpes(व्योम);

u8 acpi_hw_check_all_gpes(acpi_handle gpe_skip_device, u32 gpe_skip_number);

acpi_status
acpi_hw_enable_runसमय_gpe_block(काष्ठा acpi_gpe_xrupt_info *gpe_xrupt_info,
				 काष्ठा acpi_gpe_block_info *gpe_block,
				 व्योम *context);

#अगर_घोषित ACPI_PCI_CONFIGURED
/*
 * hwpci - PCI configuration support
 */
acpi_status
acpi_hw_derive_pci_id(काष्ठा acpi_pci_id *pci_id,
		      acpi_handle root_pci_device, acpi_handle pci_region);
#अन्यथा
अटल अंतरभूत acpi_status
acpi_hw_derive_pci_id(काष्ठा acpi_pci_id *pci_id, acpi_handle root_pci_device,
		      acpi_handle pci_region)
अणु
	वापस AE_SUPPORT;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर				/* __ACHWARE_H__ */
