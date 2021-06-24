<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * acpi/पूर्णांकernal.h
 * For use by Linux/ACPI infraकाष्ठाure, not drivers
 *
 * Copyright (c) 2009, Intel Corporation.
 */

#अगर_अघोषित _ACPI_INTERNAL_H_
#घोषणा _ACPI_INTERNAL_H_

#समावेश <linux/idr.h>

#घोषणा PREFIX "ACPI: "

पूर्णांक early_acpi_osi_init(व्योम);
पूर्णांक acpi_osi_init(व्योम);
acpi_status acpi_os_initialize1(व्योम);
पूर्णांक acpi_scan_init(व्योम);
#अगर_घोषित CONFIG_PCI
व्योम acpi_pci_root_init(व्योम);
व्योम acpi_pci_link_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_pci_root_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम acpi_pci_link_init(व्योम) अणुपूर्ण
#पूर्ण_अगर
व्योम acpi_processor_init(व्योम);
व्योम acpi_platक्रमm_init(व्योम);
व्योम acpi_pnp_init(व्योम);
व्योम acpi_पूर्णांक340x_thermal_init(व्योम);
#अगर_घोषित CONFIG_ARM_AMBA
व्योम acpi_amba_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_amba_init(व्योम) अणुपूर्ण
#पूर्ण_अगर
पूर्णांक acpi_sysfs_init(व्योम);
व्योम acpi_gpe_apply_masked_gpes(व्योम);
व्योम acpi_container_init(व्योम);
व्योम acpi_memory_hotplug_init(व्योम);
#अगर_घोषित	CONFIG_ACPI_HOTPLUG_IOAPIC
व्योम pci_ioapic_हटाओ(काष्ठा acpi_pci_root *root);
पूर्णांक acpi_ioapic_हटाओ(काष्ठा acpi_pci_root *root);
#अन्यथा
अटल अंतरभूत व्योम pci_ioapic_हटाओ(काष्ठा acpi_pci_root *root) अणु वापस; पूर्ण
अटल अंतरभूत पूर्णांक acpi_ioapic_हटाओ(काष्ठा acpi_pci_root *root) अणु वापस 0; पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_ACPI_DOCK
व्योम रेजिस्टर_करोck_dependent_device(काष्ठा acpi_device *adev,
				    acpi_handle dshandle);
पूर्णांक करोck_notअगरy(काष्ठा acpi_device *adev, u32 event);
व्योम acpi_करोck_add(काष्ठा acpi_device *adev);
#अन्यथा
अटल अंतरभूत व्योम रेजिस्टर_करोck_dependent_device(काष्ठा acpi_device *adev,
						  acpi_handle dshandle) अणुपूर्ण
अटल अंतरभूत पूर्णांक करोck_notअगरy(काष्ठा acpi_device *adev, u32 event) अणु वापस -ENODEV; पूर्ण
अटल अंतरभूत व्योम acpi_करोck_add(काष्ठा acpi_device *adev) अणुपूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_X86
व्योम acpi_cmos_rtc_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_cmos_rtc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर
पूर्णांक acpi_rev_override_setup(अक्षर *str);

व्योम acpi_sysfs_add_hotplug_profile(काष्ठा acpi_hotplug_profile *hotplug,
				    स्थिर अक्षर *name);
पूर्णांक acpi_scan_add_handler_with_hotplug(काष्ठा acpi_scan_handler *handler,
				       स्थिर अक्षर *hotplug_profile_name);
व्योम acpi_scan_hotplug_enabled(काष्ठा acpi_hotplug_profile *hotplug, bool val);

#अगर_घोषित CONFIG_DEBUG_FS
बाह्य काष्ठा dentry *acpi_debugfs_dir;
व्योम acpi_debugfs_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_debugfs_init(व्योम) अणु वापस; पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_PCI
व्योम acpi_lpss_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_lpss_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम acpi_apd_init(व्योम);

acpi_status acpi_hotplug_schedule(काष्ठा acpi_device *adev, u32 src);
bool acpi_queue_hotplug_work(काष्ठा work_काष्ठा *work);
व्योम acpi_device_hotplug(काष्ठा acpi_device *adev, u32 src);
bool acpi_scan_is_offline(काष्ठा acpi_device *adev, bool uevent);

acpi_status acpi_sysfs_table_handler(u32 event, व्योम *table, व्योम *context);
व्योम acpi_scan_table_handler(u32 event, व्योम *table, व्योम *context);

/* --------------------------------------------------------------------------
                     Device Node Initialization / Removal
   -------------------------------------------------------------------------- */
#घोषणा ACPI_STA_DEFAULT (ACPI_STA_DEVICE_PRESENT | ACPI_STA_DEVICE_ENABLED | \
			  ACPI_STA_DEVICE_UI | ACPI_STA_DEVICE_FUNCTIONING)

बाह्य काष्ठा list_head acpi_bus_id_list;

#घोषणा ACPI_MAX_DEVICE_INSTANCES	4096

काष्ठा acpi_device_bus_id अणु
	स्थिर अक्षर *bus_id;
	काष्ठा ida instance_ida;
	काष्ठा list_head node;
पूर्ण;

पूर्णांक acpi_device_add(काष्ठा acpi_device *device,
		    व्योम (*release)(काष्ठा device *));
व्योम acpi_init_device_object(काष्ठा acpi_device *device, acpi_handle handle,
			     पूर्णांक type);
पूर्णांक acpi_device_setup_files(काष्ठा acpi_device *dev);
व्योम acpi_device_हटाओ_files(काष्ठा acpi_device *dev);
व्योम acpi_device_add_finalize(काष्ठा acpi_device *device);
व्योम acpi_मुक्त_pnp_ids(काष्ठा acpi_device_pnp *pnp);
bool acpi_device_is_present(स्थिर काष्ठा acpi_device *adev);
bool acpi_device_is_battery(काष्ठा acpi_device *adev);
bool acpi_device_is_first_physical_node(काष्ठा acpi_device *adev,
					स्थिर काष्ठा device *dev);
पूर्णांक acpi_bus_रेजिस्टर_early_device(पूर्णांक type);

/* --------------------------------------------------------------------------
                     Device Matching and Notअगरication
   -------------------------------------------------------------------------- */
काष्ठा acpi_device *acpi_companion_match(स्थिर काष्ठा device *dev);
पूर्णांक __acpi_device_uevent_modalias(काष्ठा acpi_device *adev,
				  काष्ठा kobj_uevent_env *env);

/* --------------------------------------------------------------------------
                                  Power Resource
   -------------------------------------------------------------------------- */
पूर्णांक acpi_घातer_init(व्योम);
व्योम acpi_घातer_resources_list_मुक्त(काष्ठा list_head *list);
पूर्णांक acpi_extract_घातer_resources(जोड़ acpi_object *package, अचिन्हित पूर्णांक start,
				 काष्ठा list_head *list);
काष्ठा acpi_device *acpi_add_घातer_resource(acpi_handle handle);
व्योम acpi_घातer_add_हटाओ_device(काष्ठा acpi_device *adev, bool add);
पूर्णांक acpi_घातer_wakeup_list_init(काष्ठा list_head *list, पूर्णांक *प्रणाली_level);
पूर्णांक acpi_device_sleep_wake(काष्ठा acpi_device *dev,
			   पूर्णांक enable, पूर्णांक sleep_state, पूर्णांक dev_state);
पूर्णांक acpi_घातer_get_inferred_state(काष्ठा acpi_device *device, पूर्णांक *state);
पूर्णांक acpi_घातer_on_resources(काष्ठा acpi_device *device, पूर्णांक state);
पूर्णांक acpi_घातer_transition(काष्ठा acpi_device *device, पूर्णांक state);
व्योम acpi_turn_off_unused_घातer_resources(bool init);

/* --------------------------------------------------------------------------
                              Device Power Management
   -------------------------------------------------------------------------- */
पूर्णांक acpi_device_get_घातer(काष्ठा acpi_device *device, पूर्णांक *state);
पूर्णांक acpi_wakeup_device_init(व्योम);

/* --------------------------------------------------------------------------
                                  Processor
   -------------------------------------------------------------------------- */
#अगर_घोषित CONFIG_ARCH_MIGHT_HAVE_ACPI_PDC
व्योम acpi_early_processor_set_pdc(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_early_processor_set_pdc(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_X86
व्योम acpi_early_processor_osc(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_early_processor_osc(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* --------------------------------------------------------------------------
                                  Embedded Controller
   -------------------------------------------------------------------------- */
काष्ठा acpi_ec अणु
	acpi_handle handle;
	पूर्णांक gpe;
	पूर्णांक irq;
	अचिन्हित दीर्घ command_addr;
	अचिन्हित दीर्घ data_addr;
	bool global_lock;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ reference_count;
	काष्ठा mutex mutex;
	रुको_queue_head_t रुको;
	काष्ठा list_head list;
	काष्ठा transaction *curr;
	spinlock_t lock;
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ बारtamp;
	अचिन्हित दीर्घ nr_pending_queries;
	bool busy_polling;
	अचिन्हित पूर्णांक polling_guard;
पूर्ण;

बाह्य काष्ठा acpi_ec *first_ec;

/* If we find an EC via the ECDT, we need to keep a ptr to its context */
/* External पूर्णांकerfaces use first EC only, so remember */
प्रकार पूर्णांक (*acpi_ec_query_func) (व्योम *data);

व्योम acpi_ec_init(व्योम);
व्योम acpi_ec_ecdt_probe(व्योम);
व्योम acpi_ec_dsdt_probe(व्योम);
व्योम acpi_ec_block_transactions(व्योम);
व्योम acpi_ec_unblock_transactions(व्योम);
पूर्णांक acpi_ec_add_query_handler(काष्ठा acpi_ec *ec, u8 query_bit,
			      acpi_handle handle, acpi_ec_query_func func,
			      व्योम *data);
व्योम acpi_ec_हटाओ_query_handler(काष्ठा acpi_ec *ec, u8 query_bit);

#अगर_घोषित CONFIG_PM_SLEEP
व्योम acpi_ec_flush_work(व्योम);
bool acpi_ec_dispatch_gpe(व्योम);
#पूर्ण_अगर


/*--------------------------------------------------------------------------
                                  Suspend/Resume
  -------------------------------------------------------------------------- */
#अगर_घोषित CONFIG_ACPI_SYSTEM_POWER_STATES_SUPPORT
बाह्य bool acpi_s2idle_wakeup(व्योम);
बाह्य पूर्णांक acpi_sleep_init(व्योम);
#अन्यथा
अटल अंतरभूत bool acpi_s2idle_wakeup(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक acpi_sleep_init(व्योम) अणु वापस -ENXIO; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_SLEEP
व्योम acpi_sleep_proc_init(व्योम);
पूर्णांक suspend_nvs_alloc(व्योम);
व्योम suspend_nvs_मुक्त(व्योम);
पूर्णांक suspend_nvs_save(व्योम);
व्योम suspend_nvs_restore(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_sleep_proc_init(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक suspend_nvs_alloc(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम suspend_nvs_मुक्त(व्योम) अणुपूर्ण
अटल अंतरभूत पूर्णांक suspend_nvs_save(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम suspend_nvs_restore(व्योम) अणुपूर्ण
#पूर्ण_अगर

/*--------------------------------------------------------------------------
				Device properties
  -------------------------------------------------------------------------- */
#घोषणा ACPI_DT_NAMESPACE_HID	"PRP0001"

व्योम acpi_init_properties(काष्ठा acpi_device *adev);
व्योम acpi_मुक्त_properties(काष्ठा acpi_device *adev);

#अगर_घोषित CONFIG_X86
व्योम acpi_extract_apple_properties(काष्ठा acpi_device *adev);
#अन्यथा
अटल अंतरभूत व्योम acpi_extract_apple_properties(काष्ठा acpi_device *adev) अणुपूर्ण
#पूर्ण_अगर

/*--------------------------------------------------------------------------
				Watchकरोg
  -------------------------------------------------------------------------- */

#अगर_घोषित CONFIG_ACPI_WATCHDOG
व्योम acpi_watchकरोg_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_watchकरोg_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_LPIT
व्योम acpi_init_lpit(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_init_lpit(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _ACPI_INTERNAL_H_ */
