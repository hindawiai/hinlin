<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

बाह्य व्योम acpi_enable_wakeup_devices(u8 sleep_state);
बाह्य व्योम acpi_disable_wakeup_devices(u8 sleep_state);
बाह्य bool acpi_check_wakeup_handlers(व्योम);

बाह्य काष्ठा list_head acpi_wakeup_device_list;
बाह्य काष्ठा mutex acpi_device_lock;

बाह्य व्योम acpi_resume_घातer_resources(व्योम);

अटल अंतरभूत acpi_status acpi_set_waking_vector(u32 wakeup_address)
अणु
	वापस acpi_set_firmware_waking_vector(
				(acpi_physical_address)wakeup_address, 0);
पूर्ण

बाह्य पूर्णांक acpi_s2idle_begin(व्योम);
बाह्य पूर्णांक acpi_s2idle_prepare(व्योम);
बाह्य पूर्णांक acpi_s2idle_prepare_late(व्योम);
बाह्य bool acpi_s2idle_wake(व्योम);
बाह्य व्योम acpi_s2idle_restore_early(व्योम);
बाह्य व्योम acpi_s2idle_restore(व्योम);
बाह्य व्योम acpi_s2idle_end(व्योम);

बाह्य व्योम acpi_s2idle_setup(व्योम);

#अगर_घोषित CONFIG_ACPI_SLEEP
बाह्य bool acpi_sleep_शेष_s3;
#अन्यथा
#घोषणा acpi_sleep_शेष_s3	(1)
#पूर्ण_अगर
