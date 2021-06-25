<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * acpi.h - ACPI Interface
 *
 * Copyright (C) 2001 Paul Diefenbaugh <paul.s.diefenbaugh@पूर्णांकel.com>
 */

#अगर_अघोषित _LINUX_ACPI_H
#घोषणा _LINUX_ACPI_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ioport.h>	/* क्रम काष्ठा resource */
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/resource_ext.h>
#समावेश <linux/device.h>
#समावेश <linux/property.h>
#समावेश <linux/uuid.h>

#अगर_अघोषित _LINUX
#घोषणा _LINUX
#पूर्ण_अगर
#समावेश <acpi/acpi.h>

#अगर_घोषित	CONFIG_ACPI

#समावेश <linux/list.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/dynamic_debug.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>

#समावेश <acpi/acpi_bus.h>
#समावेश <acpi/acpi_drivers.h>
#समावेश <acpi/acpi_numa.h>
#समावेश <acpi/acpi_पन.स>
#समावेश <यंत्र/acpi.h>

अटल अंतरभूत acpi_handle acpi_device_handle(काष्ठा acpi_device *adev)
अणु
	वापस adev ? adev->handle : शून्य;
पूर्ण

#घोषणा ACPI_COMPANION(dev)		to_acpi_device_node((dev)->fwnode)
#घोषणा ACPI_COMPANION_SET(dev, adev)	set_primary_fwnode(dev, (adev) ? \
	acpi_fwnode_handle(adev) : शून्य)
#घोषणा ACPI_HANDLE(dev)		acpi_device_handle(ACPI_COMPANION(dev))
#घोषणा ACPI_HANDLE_FWNODE(fwnode)	\
				acpi_device_handle(to_acpi_device_node(fwnode))

अटल अंतरभूत काष्ठा fwnode_handle *acpi_alloc_fwnode_अटल(व्योम)
अणु
	काष्ठा fwnode_handle *fwnode;

	fwnode = kzalloc(माप(काष्ठा fwnode_handle), GFP_KERNEL);
	अगर (!fwnode)
		वापस शून्य;

	fwnode_init(fwnode, &acpi_अटल_fwnode_ops);

	वापस fwnode;
पूर्ण

अटल अंतरभूत व्योम acpi_मुक्त_fwnode_अटल(काष्ठा fwnode_handle *fwnode)
अणु
	अगर (WARN_ON(!is_acpi_अटल_node(fwnode)))
		वापस;

	kमुक्त(fwnode);
पूर्ण

/**
 * ACPI_DEVICE_CLASS - macro used to describe an ACPI device with
 * the PCI-defined class-code inक्रमmation
 *
 * @_cls : the class, subclass, prog-अगर triple क्रम this device
 * @_msk : the class mask क्रम this device
 *
 * This macro is used to create a काष्ठा acpi_device_id that matches a
 * specअगरic PCI class. The .id and .driver_data fields will be left
 * initialized with the शेष value.
 */
#घोषणा ACPI_DEVICE_CLASS(_cls, _msk)	.cls = (_cls), .cls_msk = (_msk),

अटल अंतरभूत bool has_acpi_companion(काष्ठा device *dev)
अणु
	वापस is_acpi_device_node(dev->fwnode);
पूर्ण

अटल अंतरभूत व्योम acpi_preset_companion(काष्ठा device *dev,
					 काष्ठा acpi_device *parent, u64 addr)
अणु
	ACPI_COMPANION_SET(dev, acpi_find_child_device(parent, addr, false));
पूर्ण

अटल अंतरभूत स्थिर अक्षर *acpi_dev_name(काष्ठा acpi_device *adev)
अणु
	वापस dev_name(&adev->dev);
पूर्ण

काष्ठा device *acpi_get_first_physical_node(काष्ठा acpi_device *adev);

क्रमागत acpi_irq_model_id अणु
	ACPI_IRQ_MODEL_PIC = 0,
	ACPI_IRQ_MODEL_IOAPIC,
	ACPI_IRQ_MODEL_IOSAPIC,
	ACPI_IRQ_MODEL_PLATFORM,
	ACPI_IRQ_MODEL_GIC,
	ACPI_IRQ_MODEL_COUNT
पूर्ण;

बाह्य क्रमागत acpi_irq_model_id	acpi_irq_model;

क्रमागत acpi_पूर्णांकerrupt_id अणु
	ACPI_INTERRUPT_PMI	= 1,
	ACPI_INTERRUPT_INIT,
	ACPI_INTERRUPT_CPEI,
	ACPI_INTERRUPT_COUNT
पूर्ण;

#घोषणा	ACPI_SPACE_MEM		0

क्रमागत acpi_address_range_id अणु
	ACPI_ADDRESS_RANGE_MEMORY = 1,
	ACPI_ADDRESS_RANGE_RESERVED = 2,
	ACPI_ADDRESS_RANGE_ACPI = 3,
	ACPI_ADDRESS_RANGE_NVS	= 4,
	ACPI_ADDRESS_RANGE_COUNT
पूर्ण;


/* Table Handlers */
जोड़ acpi_subtable_headers अणु
	काष्ठा acpi_subtable_header common;
	काष्ठा acpi_hmat_काष्ठाure hmat;
पूर्ण;

प्रकार पूर्णांक (*acpi_tbl_table_handler)(काष्ठा acpi_table_header *table);

प्रकार पूर्णांक (*acpi_tbl_entry_handler)(जोड़ acpi_subtable_headers *header,
				      स्थिर अचिन्हित दीर्घ end);

/* Debugger support */

काष्ठा acpi_debugger_ops अणु
	पूर्णांक (*create_thपढ़ो)(acpi_osd_exec_callback function, व्योम *context);
	sमाप_प्रकार (*ग_लिखो_log)(स्थिर अक्षर *msg);
	sमाप_प्रकार (*पढ़ो_cmd)(अक्षर *buffer, माप_प्रकार length);
	पूर्णांक (*रुको_command_पढ़ोy)(bool single_step, अक्षर *buffer, माप_प्रकार length);
	पूर्णांक (*notअगरy_command_complete)(व्योम);
पूर्ण;

काष्ठा acpi_debugger अणु
	स्थिर काष्ठा acpi_debugger_ops *ops;
	काष्ठा module *owner;
	काष्ठा mutex lock;
पूर्ण;

#अगर_घोषित CONFIG_ACPI_DEBUGGER
पूर्णांक __init acpi_debugger_init(व्योम);
पूर्णांक acpi_रेजिस्टर_debugger(काष्ठा module *owner,
			   स्थिर काष्ठा acpi_debugger_ops *ops);
व्योम acpi_unरेजिस्टर_debugger(स्थिर काष्ठा acpi_debugger_ops *ops);
पूर्णांक acpi_debugger_create_thपढ़ो(acpi_osd_exec_callback function, व्योम *context);
sमाप_प्रकार acpi_debugger_ग_लिखो_log(स्थिर अक्षर *msg);
sमाप_प्रकार acpi_debugger_पढ़ो_cmd(अक्षर *buffer, माप_प्रकार buffer_length);
पूर्णांक acpi_debugger_रुको_command_पढ़ोy(व्योम);
पूर्णांक acpi_debugger_notअगरy_command_complete(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_debugger_init(व्योम)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_रेजिस्टर_debugger(काष्ठा module *owner,
					 स्थिर काष्ठा acpi_debugger_ops *ops)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत व्योम acpi_unरेजिस्टर_debugger(स्थिर काष्ठा acpi_debugger_ops *ops)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक acpi_debugger_create_thपढ़ो(acpi_osd_exec_callback function,
					      व्योम *context)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_debugger_ग_लिखो_log(स्थिर अक्षर *msg)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_debugger_पढ़ो_cmd(अक्षर *buffer, u32 buffer_length)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_debugger_रुको_command_पढ़ोy(व्योम)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_debugger_notअगरy_command_complete(व्योम)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#घोषणा BAD_MADT_ENTRY(entry, end) (					    \
		(!entry) || (अचिन्हित दीर्घ)entry + माप(*entry) > end ||  \
		((काष्ठा acpi_subtable_header *)entry)->length < माप(*entry))

काष्ठा acpi_subtable_proc अणु
	पूर्णांक id;
	acpi_tbl_entry_handler handler;
	पूर्णांक count;
पूर्ण;

व्योम __iomem *__acpi_map_table(अचिन्हित दीर्घ phys, अचिन्हित दीर्घ size);
व्योम __acpi_unmap_table(व्योम __iomem *map, अचिन्हित दीर्घ size);
पूर्णांक early_acpi_boot_init(व्योम);
पूर्णांक acpi_boot_init (व्योम);
व्योम acpi_boot_table_prepare (व्योम);
व्योम acpi_boot_table_init (व्योम);
पूर्णांक acpi_mps_check (व्योम);
पूर्णांक acpi_numa_init (व्योम);

पूर्णांक acpi_locate_initial_tables (व्योम);
व्योम acpi_reserve_initial_tables (व्योम);
व्योम acpi_table_init_complete (व्योम);
पूर्णांक acpi_table_init (व्योम);
पूर्णांक acpi_table_parse(अक्षर *id, acpi_tbl_table_handler handler);
पूर्णांक __init acpi_table_parse_entries(अक्षर *id, अचिन्हित दीर्घ table_size,
			      पूर्णांक entry_id,
			      acpi_tbl_entry_handler handler,
			      अचिन्हित पूर्णांक max_entries);
पूर्णांक __init acpi_table_parse_entries_array(अक्षर *id, अचिन्हित दीर्घ table_size,
			      काष्ठा acpi_subtable_proc *proc, पूर्णांक proc_num,
			      अचिन्हित पूर्णांक max_entries);
पूर्णांक acpi_table_parse_madt(क्रमागत acpi_madt_type id,
			  acpi_tbl_entry_handler handler,
			  अचिन्हित पूर्णांक max_entries);
पूर्णांक acpi_parse_mcfg (काष्ठा acpi_table_header *header);
व्योम acpi_table_prपूर्णांक_madt_entry (काष्ठा acpi_subtable_header *madt);

/* the following numa functions are architecture-dependent */
व्योम acpi_numa_slit_init (काष्ठा acpi_table_slit *slit);

#अगर defined(CONFIG_X86) || defined(CONFIG_IA64)
व्योम acpi_numa_processor_affinity_init (काष्ठा acpi_srat_cpu_affinity *pa);
#अन्यथा
अटल अंतरभूत व्योम
acpi_numa_processor_affinity_init(काष्ठा acpi_srat_cpu_affinity *pa) अणु पूर्ण
#पूर्ण_अगर

व्योम acpi_numa_x2apic_affinity_init(काष्ठा acpi_srat_x2apic_cpu_affinity *pa);

#अगर_घोषित CONFIG_ARM64
व्योम acpi_numa_gicc_affinity_init(काष्ठा acpi_srat_gicc_affinity *pa);
#अन्यथा
अटल अंतरभूत व्योम
acpi_numa_gicc_affinity_init(काष्ठा acpi_srat_gicc_affinity *pa) अणु पूर्ण
#पूर्ण_अगर

पूर्णांक acpi_numa_memory_affinity_init (काष्ठा acpi_srat_mem_affinity *ma);

#अगर_अघोषित PHYS_CPUID_INVALID
प्रकार u32 phys_cpuid_t;
#घोषणा PHYS_CPUID_INVALID (phys_cpuid_t)(-1)
#पूर्ण_अगर

अटल अंतरभूत bool invalid_logical_cpuid(u32 cpuid)
अणु
	वापस (पूर्णांक)cpuid < 0;
पूर्ण

अटल अंतरभूत bool invalid_phys_cpuid(phys_cpuid_t phys_id)
अणु
	वापस phys_id == PHYS_CPUID_INVALID;
पूर्ण

/* Validate the processor object's proc_id */
bool acpi_duplicate_processor_id(पूर्णांक proc_id);
/* Processor _CTS control */
काष्ठा acpi_processor_घातer;

#अगर_घोषित CONFIG_ACPI_PROCESSOR_CSTATE
bool acpi_processor_claim_cst_control(व्योम);
पूर्णांक acpi_processor_evaluate_cst(acpi_handle handle, u32 cpu,
				काष्ठा acpi_processor_घातer *info);
#अन्यथा
अटल अंतरभूत bool acpi_processor_claim_cst_control(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत पूर्णांक acpi_processor_evaluate_cst(acpi_handle handle, u32 cpu,
					      काष्ठा acpi_processor_घातer *info)
अणु
	वापस -ENODEV;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_HOTPLUG_CPU
/* Arch dependent functions क्रम cpu hotplug support */
पूर्णांक acpi_map_cpu(acpi_handle handle, phys_cpuid_t physid, u32 acpi_id,
		 पूर्णांक *pcpu);
पूर्णांक acpi_unmap_cpu(पूर्णांक cpu);
#पूर्ण_अगर /* CONFIG_ACPI_HOTPLUG_CPU */

#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
पूर्णांक acpi_get_ioapic_id(acpi_handle handle, u32 gsi_base, u64 *phys_addr);
#पूर्ण_अगर

पूर्णांक acpi_रेजिस्टर_ioapic(acpi_handle handle, u64 phys_addr, u32 gsi_base);
पूर्णांक acpi_unरेजिस्टर_ioapic(acpi_handle handle, u32 gsi_base);
पूर्णांक acpi_ioapic_रेजिस्टरed(acpi_handle handle, u32 gsi_base);
व्योम acpi_irq_stats_init(व्योम);
बाह्य u32 acpi_irq_handled;
बाह्य u32 acpi_irq_not_handled;
बाह्य अचिन्हित पूर्णांक acpi_sci_irq;
बाह्य bool acpi_no_s5;
#घोषणा INVALID_ACPI_IRQ	((अचिन्हित)-1)
अटल अंतरभूत bool acpi_sci_irq_valid(व्योम)
अणु
	वापस acpi_sci_irq != INVALID_ACPI_IRQ;
पूर्ण

बाह्य पूर्णांक sbf_port;
बाह्य अचिन्हित दीर्घ acpi_realmode_flags;

पूर्णांक acpi_रेजिस्टर_gsi (काष्ठा device *dev, u32 gsi, पूर्णांक triggering, पूर्णांक polarity);
पूर्णांक acpi_gsi_to_irq (u32 gsi, अचिन्हित पूर्णांक *irq);
पूर्णांक acpi_isa_irq_to_gsi (अचिन्हित isa_irq, u32 *gsi);

व्योम acpi_set_irq_model(क्रमागत acpi_irq_model_id model,
			काष्ठा fwnode_handle *fwnode);

काष्ठा irq_करोमुख्य *acpi_irq_create_hierarchy(अचिन्हित पूर्णांक flags,
					     अचिन्हित पूर्णांक size,
					     काष्ठा fwnode_handle *fwnode,
					     स्थिर काष्ठा irq_करोमुख्य_ops *ops,
					     व्योम *host_data);

#अगर_घोषित CONFIG_X86_IO_APIC
बाह्य पूर्णांक acpi_get_override_irq(u32 gsi, पूर्णांक *trigger, पूर्णांक *polarity);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_get_override_irq(u32 gsi, पूर्णांक *trigger, पूर्णांक *polarity)
अणु
	वापस -1;
पूर्ण
#पूर्ण_अगर
/*
 * This function unकरोes the effect of one call to acpi_रेजिस्टर_gsi().
 * If this matches the last registration, any IRQ resources क्रम gsi
 * are मुक्तd.
 */
व्योम acpi_unरेजिस्टर_gsi (u32 gsi);

काष्ठा pci_dev;

पूर्णांक acpi_pci_irq_enable (काष्ठा pci_dev *dev);
व्योम acpi_penalize_isa_irq(पूर्णांक irq, पूर्णांक active);
bool acpi_isa_irq_available(पूर्णांक irq);
#अगर_घोषित CONFIG_PCI
व्योम acpi_penalize_sci_irq(पूर्णांक irq, पूर्णांक trigger, पूर्णांक polarity);
#अन्यथा
अटल अंतरभूत व्योम acpi_penalize_sci_irq(पूर्णांक irq, पूर्णांक trigger,
					पूर्णांक polarity)
अणु
पूर्ण
#पूर्ण_अगर
व्योम acpi_pci_irq_disable (काष्ठा pci_dev *dev);

बाह्य पूर्णांक ec_पढ़ो(u8 addr, u8 *val);
बाह्य पूर्णांक ec_ग_लिखो(u8 addr, u8 val);
बाह्य पूर्णांक ec_transaction(u8 command,
                          स्थिर u8 *wdata, अचिन्हित wdata_len,
                          u8 *rdata, अचिन्हित rdata_len);
बाह्य acpi_handle ec_get_handle(व्योम);

बाह्य bool acpi_is_pnp_device(काष्ठा acpi_device *);

#अगर defined(CONFIG_ACPI_WMI) || defined(CONFIG_ACPI_WMI_MODULE)

प्रकार व्योम (*wmi_notअगरy_handler) (u32 value, व्योम *context);

बाह्य acpi_status wmi_evaluate_method(स्थिर अक्षर *guid, u8 instance,
					u32 method_id,
					स्थिर काष्ठा acpi_buffer *in,
					काष्ठा acpi_buffer *out);
बाह्य acpi_status wmi_query_block(स्थिर अक्षर *guid, u8 instance,
					काष्ठा acpi_buffer *out);
बाह्य acpi_status wmi_set_block(स्थिर अक्षर *guid, u8 instance,
					स्थिर काष्ठा acpi_buffer *in);
बाह्य acpi_status wmi_install_notअगरy_handler(स्थिर अक्षर *guid,
					wmi_notअगरy_handler handler, व्योम *data);
बाह्य acpi_status wmi_हटाओ_notअगरy_handler(स्थिर अक्षर *guid);
बाह्य acpi_status wmi_get_event_data(u32 event, काष्ठा acpi_buffer *out);
बाह्य bool wmi_has_guid(स्थिर अक्षर *guid);
बाह्य अक्षर *wmi_get_acpi_device_uid(स्थिर अक्षर *guid);

#पूर्ण_अगर	/* CONFIG_ACPI_WMI */

#घोषणा ACPI_VIDEO_OUTPUT_SWITCHING			0x0001
#घोषणा ACPI_VIDEO_DEVICE_POSTING			0x0002
#घोषणा ACPI_VIDEO_ROM_AVAILABLE			0x0004
#घोषणा ACPI_VIDEO_BACKLIGHT				0x0008
#घोषणा ACPI_VIDEO_BACKLIGHT_FORCE_VENDOR		0x0010
#घोषणा ACPI_VIDEO_BACKLIGHT_FORCE_VIDEO		0x0020
#घोषणा ACPI_VIDEO_OUTPUT_SWITCHING_FORCE_VENDOR	0x0040
#घोषणा ACPI_VIDEO_OUTPUT_SWITCHING_FORCE_VIDEO		0x0080
#घोषणा ACPI_VIDEO_BACKLIGHT_DMI_VENDOR			0x0100
#घोषणा ACPI_VIDEO_BACKLIGHT_DMI_VIDEO			0x0200
#घोषणा ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VENDOR		0x0400
#घोषणा ACPI_VIDEO_OUTPUT_SWITCHING_DMI_VIDEO		0x0800

बाह्य अक्षर acpi_video_backlight_string[];
बाह्य दीर्घ acpi_is_video_device(acpi_handle handle);
बाह्य पूर्णांक acpi_blacklisted(व्योम);
बाह्य व्योम acpi_osi_setup(अक्षर *str);
बाह्य bool acpi_osi_is_win8(व्योम);

#अगर_घोषित CONFIG_ACPI_NUMA
पूर्णांक acpi_map_pxm_to_node(पूर्णांक pxm);
पूर्णांक acpi_get_node(acpi_handle handle);

/**
 * pxm_to_online_node - Map proximity ID to online node
 * @pxm: ACPI proximity ID
 *
 * This is similar to pxm_to_node(), but always वापसs an online
 * node.  When the mapped node from a given proximity ID is offline, it
 * looks up the node distance table and वापसs the nearest online node.
 *
 * ACPI device drivers, which are called after the NUMA initialization has
 * completed in the kernel, can call this पूर्णांकerface to obtain their device
 * NUMA topology from ACPI tables.  Such drivers करो not have to deal with
 * offline nodes.  A node may be offline when SRAT memory entry करोes not exist,
 * or NUMA is disabled, ex. "numa=off" on x86.
 */
अटल अंतरभूत पूर्णांक pxm_to_online_node(पूर्णांक pxm)
अणु
	पूर्णांक node = pxm_to_node(pxm);

	वापस numa_map_to_online_node(node);
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक pxm_to_online_node(पूर्णांक pxm)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_map_pxm_to_node(पूर्णांक pxm)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_get_node(acpi_handle handle)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर
बाह्य पूर्णांक acpi_paddr_to_node(u64 start_addr, u64 size);

बाह्य पूर्णांक pnpacpi_disabled;

#घोषणा PXM_INVAL	(-1)

bool acpi_dev_resource_memory(काष्ठा acpi_resource *ares, काष्ठा resource *res);
bool acpi_dev_resource_io(काष्ठा acpi_resource *ares, काष्ठा resource *res);
bool acpi_dev_resource_address_space(काष्ठा acpi_resource *ares,
				     काष्ठा resource_win *win);
bool acpi_dev_resource_ext_address_space(काष्ठा acpi_resource *ares,
					 काष्ठा resource_win *win);
अचिन्हित दीर्घ acpi_dev_irq_flags(u8 triggering, u8 polarity, u8 shareable);
अचिन्हित पूर्णांक acpi_dev_get_irq_type(पूर्णांक triggering, पूर्णांक polarity);
bool acpi_dev_resource_पूर्णांकerrupt(काष्ठा acpi_resource *ares, पूर्णांक index,
				 काष्ठा resource *res);

व्योम acpi_dev_मुक्त_resource_list(काष्ठा list_head *list);
पूर्णांक acpi_dev_get_resources(काष्ठा acpi_device *adev, काष्ठा list_head *list,
			   पूर्णांक (*preproc)(काष्ठा acpi_resource *, व्योम *),
			   व्योम *preproc_data);
पूर्णांक acpi_dev_get_dma_resources(काष्ठा acpi_device *adev,
			       काष्ठा list_head *list);
पूर्णांक acpi_dev_filter_resource_type(काष्ठा acpi_resource *ares,
				  अचिन्हित दीर्घ types);

अटल अंतरभूत पूर्णांक acpi_dev_filter_resource_type_cb(काष्ठा acpi_resource *ares,
						   व्योम *arg)
अणु
	वापस acpi_dev_filter_resource_type(ares, (अचिन्हित दीर्घ)arg);
पूर्ण

काष्ठा acpi_device *acpi_resource_consumer(काष्ठा resource *res);

पूर्णांक acpi_check_resource_conflict(स्थिर काष्ठा resource *res);

पूर्णांक acpi_check_region(resource_माप_प्रकार start, resource_माप_प्रकार n,
		      स्थिर अक्षर *name);

acpi_status acpi_release_memory(acpi_handle handle, काष्ठा resource *res,
				u32 level);

पूर्णांक acpi_resources_are_enक्रमced(व्योम);

#अगर_घोषित CONFIG_HIBERNATION
व्योम __init acpi_no_s4_hw_signature(व्योम);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_SLEEP
व्योम __init acpi_old_suspend_ordering(व्योम);
व्योम __init acpi_nvs_nosave(व्योम);
व्योम __init acpi_nvs_nosave_s3(व्योम);
व्योम __init acpi_sleep_no_blacklist(व्योम);
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

पूर्णांक acpi_रेजिस्टर_wakeup_handler(
	पूर्णांक wake_irq, bool (*wakeup)(व्योम *context), व्योम *context);
व्योम acpi_unरेजिस्टर_wakeup_handler(
	bool (*wakeup)(व्योम *context), व्योम *context);

काष्ठा acpi_osc_context अणु
	अक्षर *uuid_str;			/* UUID string */
	पूर्णांक rev;
	काष्ठा acpi_buffer cap;		/* list of DWORD capabilities */
	काष्ठा acpi_buffer ret;		/* मुक्त by caller अगर success */
पूर्ण;

acpi_status acpi_run_osc(acpi_handle handle, काष्ठा acpi_osc_context *context);

/* Indexes पूर्णांकo _OSC Capabilities Buffer (DWORDs 2 & 3 are device-specअगरic) */
#घोषणा OSC_QUERY_DWORD				0	/* DWORD 1 */
#घोषणा OSC_SUPPORT_DWORD			1	/* DWORD 2 */
#घोषणा OSC_CONTROL_DWORD			2	/* DWORD 3 */

/* _OSC Capabilities DWORD 1: Query/Control and Error Returns (generic) */
#घोषणा OSC_QUERY_ENABLE			0x00000001  /* input */
#घोषणा OSC_REQUEST_ERROR			0x00000002  /* वापस */
#घोषणा OSC_INVALID_UUID_ERROR			0x00000004  /* वापस */
#घोषणा OSC_INVALID_REVISION_ERROR		0x00000008  /* वापस */
#घोषणा OSC_CAPABILITIES_MASK_ERROR		0x00000010  /* वापस */

/* Platक्रमm-Wide Capabilities _OSC: Capabilities DWORD 2: Support Field */
#घोषणा OSC_SB_PAD_SUPPORT			0x00000001
#घोषणा OSC_SB_PPC_OST_SUPPORT			0x00000002
#घोषणा OSC_SB_PR3_SUPPORT			0x00000004
#घोषणा OSC_SB_HOTPLUG_OST_SUPPORT		0x00000008
#घोषणा OSC_SB_APEI_SUPPORT			0x00000010
#घोषणा OSC_SB_CPC_SUPPORT			0x00000020
#घोषणा OSC_SB_CPCV2_SUPPORT			0x00000040
#घोषणा OSC_SB_PCLPI_SUPPORT			0x00000080
#घोषणा OSC_SB_OSLPI_SUPPORT			0x00000100
#घोषणा OSC_SB_CPC_DIVERSE_HIGH_SUPPORT		0x00001000
#घोषणा OSC_SB_GENERIC_INITIATOR_SUPPORT	0x00002000
#घोषणा OSC_SB_NATIVE_USB4_SUPPORT		0x00040000

बाह्य bool osc_sb_apei_support_acked;
बाह्य bool osc_pc_lpi_support_confirmed;
बाह्य bool osc_sb_native_usb4_support_confirmed;

/* USB4 Capabilities */
#घोषणा OSC_USB_USB3_TUNNELING			0x00000001
#घोषणा OSC_USB_DP_TUNNELING			0x00000002
#घोषणा OSC_USB_PCIE_TUNNELING			0x00000004
#घोषणा OSC_USB_XDOMAIN				0x00000008

बाह्य u32 osc_sb_native_usb4_control;

/* PCI Host Bridge _OSC: Capabilities DWORD 2: Support Field */
#घोषणा OSC_PCI_EXT_CONFIG_SUPPORT		0x00000001
#घोषणा OSC_PCI_ASPM_SUPPORT			0x00000002
#घोषणा OSC_PCI_CLOCK_PM_SUPPORT		0x00000004
#घोषणा OSC_PCI_SEGMENT_GROUPS_SUPPORT		0x00000008
#घोषणा OSC_PCI_MSI_SUPPORT			0x00000010
#घोषणा OSC_PCI_EDR_SUPPORT			0x00000080
#घोषणा OSC_PCI_HPX_TYPE_3_SUPPORT		0x00000100
#घोषणा OSC_PCI_SUPPORT_MASKS			0x0000019f

/* PCI Host Bridge _OSC: Capabilities DWORD 3: Control Field */
#घोषणा OSC_PCI_EXPRESS_NATIVE_HP_CONTROL	0x00000001
#घोषणा OSC_PCI_SHPC_NATIVE_HP_CONTROL		0x00000002
#घोषणा OSC_PCI_EXPRESS_PME_CONTROL		0x00000004
#घोषणा OSC_PCI_EXPRESS_AER_CONTROL		0x00000008
#घोषणा OSC_PCI_EXPRESS_CAPABILITY_CONTROL	0x00000010
#घोषणा OSC_PCI_EXPRESS_LTR_CONTROL		0x00000020
#घोषणा OSC_PCI_EXPRESS_DPC_CONTROL		0x00000080
#घोषणा OSC_PCI_CONTROL_MASKS			0x000000bf

#घोषणा ACPI_GSB_ACCESS_ATTRIB_QUICK		0x00000002
#घोषणा ACPI_GSB_ACCESS_ATTRIB_SEND_RCV         0x00000004
#घोषणा ACPI_GSB_ACCESS_ATTRIB_BYTE		0x00000006
#घोषणा ACPI_GSB_ACCESS_ATTRIB_WORD		0x00000008
#घोषणा ACPI_GSB_ACCESS_ATTRIB_BLOCK		0x0000000A
#घोषणा ACPI_GSB_ACCESS_ATTRIB_MULTIBYTE	0x0000000B
#घोषणा ACPI_GSB_ACCESS_ATTRIB_WORD_CALL	0x0000000C
#घोषणा ACPI_GSB_ACCESS_ATTRIB_BLOCK_CALL	0x0000000D
#घोषणा ACPI_GSB_ACCESS_ATTRIB_RAW_BYTES	0x0000000E
#घोषणा ACPI_GSB_ACCESS_ATTRIB_RAW_PROCESS	0x0000000F

/* Enable _OST when all relevant hotplug operations are enabled */
#अगर defined(CONFIG_ACPI_HOTPLUG_CPU) &&			\
	defined(CONFIG_ACPI_HOTPLUG_MEMORY) &&		\
	defined(CONFIG_ACPI_CONTAINER)
#घोषणा ACPI_HOTPLUG_OST
#पूर्ण_अगर

/* _OST Source Event Code (OSPM Action) */
#घोषणा ACPI_OST_EC_OSPM_SHUTDOWN		0x100
#घोषणा ACPI_OST_EC_OSPM_EJECT			0x103
#घोषणा ACPI_OST_EC_OSPM_INSERTION		0x200

/* _OST General Processing Status Code */
#घोषणा ACPI_OST_SC_SUCCESS			0x0
#घोषणा ACPI_OST_SC_NON_SPECIFIC_FAILURE	0x1
#घोषणा ACPI_OST_SC_UNRECOGNIZED_NOTIFY		0x2

/* _OST OS Shutकरोwn Processing (0x100) Status Code */
#घोषणा ACPI_OST_SC_OS_SHUTDOWN_DENIED		0x80
#घोषणा ACPI_OST_SC_OS_SHUTDOWN_IN_PROGRESS	0x81
#घोषणा ACPI_OST_SC_OS_SHUTDOWN_COMPLETED	0x82
#घोषणा ACPI_OST_SC_OS_SHUTDOWN_NOT_SUPPORTED	0x83

/* _OST Ejection Request (0x3, 0x103) Status Code */
#घोषणा ACPI_OST_SC_EJECT_NOT_SUPPORTED		0x80
#घोषणा ACPI_OST_SC_DEVICE_IN_USE		0x81
#घोषणा ACPI_OST_SC_DEVICE_BUSY			0x82
#घोषणा ACPI_OST_SC_EJECT_DEPENDENCY_BUSY	0x83
#घोषणा ACPI_OST_SC_EJECT_IN_PROGRESS		0x84

/* _OST Insertion Request (0x200) Status Code */
#घोषणा ACPI_OST_SC_INSERT_IN_PROGRESS		0x80
#घोषणा ACPI_OST_SC_DRIVER_LOAD_FAILURE		0x81
#घोषणा ACPI_OST_SC_INSERT_NOT_SUPPORTED	0x82

क्रमागत acpi_predicate अणु
	all_versions,
	less_than_or_equal,
	equal,
	greater_than_or_equal,
पूर्ण;

/* Table must be termपूर्णांकed by a शून्य entry */
काष्ठा acpi_platक्रमm_list अणु
	अक्षर	oem_id[ACPI_OEM_ID_SIZE+1];
	अक्षर	oem_table_id[ACPI_OEM_TABLE_ID_SIZE+1];
	u32	oem_revision;
	अक्षर	*table;
	क्रमागत acpi_predicate pred;
	अक्षर	*reason;
	u32	data;
पूर्ण;
पूर्णांक acpi_match_platक्रमm_list(स्थिर काष्ठा acpi_platक्रमm_list *plat);

बाह्य व्योम acpi_early_init(व्योम);
बाह्य व्योम acpi_subप्रणाली_init(व्योम);
बाह्य व्योम arch_post_acpi_subsys_init(व्योम);

बाह्य पूर्णांक acpi_nvs_रेजिस्टर(__u64 start, __u64 size);

बाह्य पूर्णांक acpi_nvs_क्रम_each_region(पूर्णांक (*func)(__u64, __u64, व्योम *),
				    व्योम *data);

स्थिर काष्ठा acpi_device_id *acpi_match_device(स्थिर काष्ठा acpi_device_id *ids,
					       स्थिर काष्ठा device *dev);

स्थिर व्योम *acpi_device_get_match_data(स्थिर काष्ठा device *dev);
बाह्य bool acpi_driver_match_device(काष्ठा device *dev,
				     स्थिर काष्ठा device_driver *drv);
पूर्णांक acpi_device_uevent_modalias(काष्ठा device *, काष्ठा kobj_uevent_env *);
पूर्णांक acpi_device_modalias(काष्ठा device *, अक्षर *, पूर्णांक);
व्योम acpi_walk_dep_device_list(acpi_handle handle);

काष्ठा platक्रमm_device *acpi_create_platक्रमm_device(काष्ठा acpi_device *,
						    काष्ठा property_entry *);
#घोषणा ACPI_PTR(_ptr)	(_ptr)

अटल अंतरभूत व्योम acpi_device_set_क्रमागतerated(काष्ठा acpi_device *adev)
अणु
	adev->flags.visited = true;
पूर्ण

अटल अंतरभूत व्योम acpi_device_clear_क्रमागतerated(काष्ठा acpi_device *adev)
अणु
	adev->flags.visited = false;
पूर्ण

क्रमागत acpi_reconfig_event  अणु
	ACPI_RECONFIG_DEVICE_ADD = 0,
	ACPI_RECONFIG_DEVICE_REMOVE,
पूर्ण;

पूर्णांक acpi_reconfig_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb);
पूर्णांक acpi_reconfig_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb);

#अगर_घोषित CONFIG_ACPI_GTDT
पूर्णांक acpi_gtdt_init(काष्ठा acpi_table_header *table, पूर्णांक *platक्रमm_समयr_count);
पूर्णांक acpi_gtdt_map_ppi(पूर्णांक type);
bool acpi_gtdt_c3stop(पूर्णांक type);
पूर्णांक acpi_arch_समयr_mem_init(काष्ठा arch_समयr_mem *समयr_mem, पूर्णांक *समयr_count);
#पूर्ण_अगर

#अगर_अघोषित ACPI_HAVE_ARCH_SET_ROOT_POINTER
अटल अंतरभूत व्योम acpi_arch_set_root_poपूर्णांकer(u64 addr)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_अघोषित ACPI_HAVE_ARCH_GET_ROOT_POINTER
अटल अंतरभूत u64 acpi_arch_get_root_poपूर्णांकer(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अन्यथा	/* !CONFIG_ACPI */

#घोषणा acpi_disabled 1

#घोषणा ACPI_COMPANION(dev)		(शून्य)
#घोषणा ACPI_COMPANION_SET(dev, adev)	करो अणु पूर्ण जबतक (0)
#घोषणा ACPI_HANDLE(dev)		(शून्य)
#घोषणा ACPI_HANDLE_FWNODE(fwnode)	(शून्य)
#घोषणा ACPI_DEVICE_CLASS(_cls, _msk)	.cls = (0), .cls_msk = (0),

#समावेश <acpi/acpi_numa.h>

काष्ठा fwnode_handle;

अटल अंतरभूत bool acpi_dev_found(स्थिर अक्षर *hid)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool acpi_dev_present(स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv)
अणु
	वापस false;
पूर्ण

काष्ठा acpi_device;

अटल अंतरभूत bool
acpi_dev_hid_uid_match(काष्ठा acpi_device *adev, स्थिर अक्षर *hid2, स्थिर अक्षर *uid2)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा acpi_device *
acpi_dev_get_first_match_dev(स्थिर अक्षर *hid, स्थिर अक्षर *uid, s64 hrv)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool acpi_reduced_hardware(व्योम)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम acpi_dev_put(काष्ठा acpi_device *adev) अणुपूर्ण

अटल अंतरभूत bool is_acpi_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool is_acpi_device_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा acpi_device *to_acpi_device_node(काष्ठा fwnode_handle *fwnode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool is_acpi_data_node(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा acpi_data_node *to_acpi_data_node(काष्ठा fwnode_handle *fwnode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool acpi_data_node_match(काष्ठा fwnode_handle *fwnode,
					स्थिर अक्षर *name)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा fwnode_handle *acpi_fwnode_handle(काष्ठा acpi_device *adev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool has_acpi_companion(काष्ठा device *dev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम acpi_preset_companion(काष्ठा device *dev,
					 काष्ठा acpi_device *parent, u64 addr)
अणु
पूर्ण

अटल अंतरभूत स्थिर अक्षर *acpi_dev_name(काष्ठा acpi_device *adev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा device *acpi_get_first_physical_node(काष्ठा acpi_device *adev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम acpi_early_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम acpi_subप्रणाली_init(व्योम) अणु पूर्ण

अटल अंतरभूत पूर्णांक early_acpi_boot_init(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_boot_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम acpi_boot_table_prepare(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम acpi_boot_table_init(व्योम)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक acpi_mps_check(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_check_resource_conflict(काष्ठा resource *res)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_check_region(resource_माप_प्रकार start, resource_माप_प्रकार n,
				    स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण

काष्ठा acpi_table_header;
अटल अंतरभूत पूर्णांक acpi_table_parse(अक्षर *id,
				पूर्णांक (*handler)(काष्ठा acpi_table_header *))
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_nvs_रेजिस्टर(__u64 start, __u64 size)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_nvs_क्रम_each_region(पूर्णांक (*func)(__u64, __u64, व्योम *),
					   व्योम *data)
अणु
	वापस 0;
पूर्ण

काष्ठा acpi_device_id;

अटल अंतरभूत स्थिर काष्ठा acpi_device_id *acpi_match_device(
	स्थिर काष्ठा acpi_device_id *ids, स्थिर काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत स्थिर व्योम *acpi_device_get_match_data(स्थिर काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool acpi_driver_match_device(काष्ठा device *dev,
					    स्थिर काष्ठा device_driver *drv)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत जोड़ acpi_object *acpi_evaluate_dsm(acpi_handle handle,
						   स्थिर guid_t *guid,
						   u64 rev, u64 func,
						   जोड़ acpi_object *argv4)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_device_uevent_modalias(काष्ठा device *dev,
				काष्ठा kobj_uevent_env *env)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_device_modalias(काष्ठा device *dev,
				अक्षर *buf, पूर्णांक size)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत काष्ठा platक्रमm_device *
acpi_create_platक्रमm_device(काष्ठा acpi_device *adev,
			    काष्ठा property_entry *properties)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत bool acpi_dma_supported(काष्ठा acpi_device *adev)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत क्रमागत dev_dma_attr acpi_get_dma_attr(काष्ठा acpi_device *adev)
अणु
	वापस DEV_DMA_NOT_SUPPORTED;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_dma_get_range(काष्ठा device *dev, u64 *dma_addr,
				     u64 *offset, u64 *size)
अणु
	वापस -ENODEV;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_dma_configure(काष्ठा device *dev,
				     क्रमागत dev_dma_attr attr)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_dma_configure_id(काष्ठा device *dev,
					क्रमागत dev_dma_attr attr,
					स्थिर u32 *input_id)
अणु
	वापस 0;
पूर्ण

#घोषणा ACPI_PTR(_ptr)	(शून्य)

अटल अंतरभूत व्योम acpi_device_set_क्रमागतerated(काष्ठा acpi_device *adev)
अणु
पूर्ण

अटल अंतरभूत व्योम acpi_device_clear_क्रमागतerated(काष्ठा acpi_device *adev)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक acpi_reconfig_notअगरier_रेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_reconfig_notअगरier_unरेजिस्टर(काष्ठा notअगरier_block *nb)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत काष्ठा acpi_device *acpi_resource_consumer(काष्ठा resource *res)
अणु
	वापस शून्य;
पूर्ण

#पूर्ण_अगर	/* !CONFIG_ACPI */

#अगर_घोषित CONFIG_ACPI_HOTPLUG_IOAPIC
पूर्णांक acpi_ioapic_add(acpi_handle root);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_ioapic_add(acpi_handle root) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
व्योम acpi_os_set_prepare_sleep(पूर्णांक (*func)(u8 sleep_state,
			       u32 pm1a_ctrl,  u32 pm1b_ctrl));

acpi_status acpi_os_prepare_sleep(u8 sleep_state,
				  u32 pm1a_control, u32 pm1b_control);

व्योम acpi_os_set_prepare_extended_sleep(पूर्णांक (*func)(u8 sleep_state,
				        u32 val_a,  u32 val_b));

acpi_status acpi_os_prepare_extended_sleep(u8 sleep_state,
					   u32 val_a, u32 val_b);

#अगर_अघोषित CONFIG_IA64
व्योम arch_reserve_mem_area(acpi_physical_address addr, माप_प्रकार size);
#अन्यथा
अटल अंतरभूत व्योम arch_reserve_mem_area(acpi_physical_address addr,
					  माप_प्रकार size)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_X86 */
#अन्यथा
#घोषणा acpi_os_set_prepare_sleep(func, pm1a_ctrl, pm1b_ctrl) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PM)
पूर्णांक acpi_dev_suspend(काष्ठा device *dev, bool wakeup);
पूर्णांक acpi_dev_resume(काष्ठा device *dev);
पूर्णांक acpi_subsys_runसमय_suspend(काष्ठा device *dev);
पूर्णांक acpi_subsys_runसमय_resume(काष्ठा device *dev);
पूर्णांक acpi_dev_pm_attach(काष्ठा device *dev, bool घातer_on);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_subsys_runसमय_suspend(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक acpi_subsys_runसमय_resume(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक acpi_dev_pm_attach(काष्ठा device *dev, bool घातer_on)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI) && defined(CONFIG_PM_SLEEP)
पूर्णांक acpi_subsys_prepare(काष्ठा device *dev);
व्योम acpi_subsys_complete(काष्ठा device *dev);
पूर्णांक acpi_subsys_suspend_late(काष्ठा device *dev);
पूर्णांक acpi_subsys_suspend_noirq(काष्ठा device *dev);
पूर्णांक acpi_subsys_suspend(काष्ठा device *dev);
पूर्णांक acpi_subsys_मुक्तze(काष्ठा device *dev);
पूर्णांक acpi_subsys_घातeroff(काष्ठा device *dev);
व्योम acpi_ec_mark_gpe_क्रम_wake(व्योम);
व्योम acpi_ec_set_gpe_wake_mask(u8 action);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_subsys_prepare(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम acpi_subsys_complete(काष्ठा device *dev) अणुपूर्ण
अटल अंतरभूत पूर्णांक acpi_subsys_suspend_late(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक acpi_subsys_suspend_noirq(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक acpi_subsys_suspend(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक acpi_subsys_मुक्तze(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक acpi_subsys_घातeroff(काष्ठा device *dev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम acpi_ec_mark_gpe_क्रम_wake(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम acpi_ec_set_gpe_wake_mask(u8 action) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
__म_लिखो(3, 4)
व्योम acpi_handle_prपूर्णांकk(स्थिर अक्षर *level, acpi_handle handle,
			स्थिर अक्षर *fmt, ...);
व्योम acpi_evaluation_failure_warn(acpi_handle handle, स्थिर अक्षर *name,
				  acpi_status status);
#अन्यथा	/* !CONFIG_ACPI */
अटल अंतरभूत __म_लिखो(3, 4) व्योम
acpi_handle_prपूर्णांकk(स्थिर अक्षर *level, व्योम *handle, स्थिर अक्षर *fmt, ...) अणुपूर्ण
अटल अंतरभूत व्योम acpi_evaluation_failure_warn(acpi_handle handle,
						स्थिर अक्षर *name,
						acpi_status status) अणुपूर्ण
#पूर्ण_अगर	/* !CONFIG_ACPI */

#अगर defined(CONFIG_ACPI) && defined(CONFIG_DYNAMIC_DEBUG)
__म_लिखो(3, 4)
व्योम __acpi_handle_debug(काष्ठा _ddebug *descriptor, acpi_handle handle, स्थिर अक्षर *fmt, ...);
#पूर्ण_अगर

/*
 * acpi_handle_<level>: Prपूर्णांक message with ACPI prefix and object path
 *
 * These पूर्णांकerfaces acquire the global namespace mutex to obtain an object
 * path.  In पूर्णांकerrupt context, it shows the object path as <n/a>.
 */
#घोषणा acpi_handle_emerg(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_EMERG, handle, fmt, ##__VA_ARGS__)
#घोषणा acpi_handle_alert(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_ALERT, handle, fmt, ##__VA_ARGS__)
#घोषणा acpi_handle_crit(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_CRIT, handle, fmt, ##__VA_ARGS__)
#घोषणा acpi_handle_err(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_ERR, handle, fmt, ##__VA_ARGS__)
#घोषणा acpi_handle_warn(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_WARNING, handle, fmt, ##__VA_ARGS__)
#घोषणा acpi_handle_notice(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_NOTICE, handle, fmt, ##__VA_ARGS__)
#घोषणा acpi_handle_info(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_INFO, handle, fmt, ##__VA_ARGS__)

#अगर defined(DEBUG)
#घोषणा acpi_handle_debug(handle, fmt, ...)				\
	acpi_handle_prपूर्णांकk(KERN_DEBUG, handle, fmt, ##__VA_ARGS__)
#अन्यथा
#अगर defined(CONFIG_DYNAMIC_DEBUG)
#घोषणा acpi_handle_debug(handle, fmt, ...)				\
	_dynamic_func_call(fmt, __acpi_handle_debug,			\
			   handle, pr_fmt(fmt), ##__VA_ARGS__)
#अन्यथा
#घोषणा acpi_handle_debug(handle, fmt, ...)				\
(अणु									\
	अगर (0)								\
		acpi_handle_prपूर्णांकk(KERN_DEBUG, handle, fmt, ##__VA_ARGS__); \
	0;								\
पूर्ण)
#पूर्ण_अगर
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI) && defined(CONFIG_GPIOLIB)
bool acpi_gpio_get_irq_resource(काष्ठा acpi_resource *ares,
				काष्ठा acpi_resource_gpio **agpio);
पूर्णांक acpi_dev_gpio_irq_get_by(काष्ठा acpi_device *adev, स्थिर अक्षर *name, पूर्णांक index);
#अन्यथा
अटल अंतरभूत bool acpi_gpio_get_irq_resource(काष्ठा acpi_resource *ares,
					      काष्ठा acpi_resource_gpio **agpio)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक acpi_dev_gpio_irq_get_by(काष्ठा acpi_device *adev,
					   स्थिर अक्षर *name, पूर्णांक index)
अणु
	वापस -ENXIO;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक acpi_dev_gpio_irq_get(काष्ठा acpi_device *adev, पूर्णांक index)
अणु
	वापस acpi_dev_gpio_irq_get_by(adev, शून्य, index);
पूर्ण

/* Device properties */

#अगर_घोषित CONFIG_ACPI
पूर्णांक acpi_dev_get_property(स्थिर काष्ठा acpi_device *adev, स्थिर अक्षर *name,
			  acpi_object_type type, स्थिर जोड़ acpi_object **obj);
पूर्णांक __acpi_node_get_property_reference(स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *name, माप_प्रकार index, माप_प्रकार num_args,
				काष्ठा fwnode_reference_args *args);

अटल अंतरभूत पूर्णांक acpi_node_get_property_reference(
				स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *name, माप_प्रकार index,
				काष्ठा fwnode_reference_args *args)
अणु
	वापस __acpi_node_get_property_reference(fwnode, name, index,
		NR_FWNODE_REFERENCE_ARGS, args);
पूर्ण

अटल अंतरभूत bool acpi_dev_has_props(स्थिर काष्ठा acpi_device *adev)
अणु
	वापस !list_empty(&adev->data.properties);
पूर्ण

काष्ठा acpi_device_properties *
acpi_data_add_props(काष्ठा acpi_device_data *data, स्थिर guid_t *guid,
		    स्थिर जोड़ acpi_object *properties);

पूर्णांक acpi_node_prop_get(स्थिर काष्ठा fwnode_handle *fwnode, स्थिर अक्षर *propname,
		       व्योम **valptr);

काष्ठा fwnode_handle *acpi_get_next_subnode(स्थिर काष्ठा fwnode_handle *fwnode,
					    काष्ठा fwnode_handle *child);
काष्ठा fwnode_handle *acpi_node_get_parent(स्थिर काष्ठा fwnode_handle *fwnode);

काष्ठा acpi_probe_entry;
प्रकार bool (*acpi_probe_entry_validate_subtbl)(काष्ठा acpi_subtable_header *,
						 काष्ठा acpi_probe_entry *);

#घोषणा ACPI_TABLE_ID_LEN	5

/**
 * काष्ठा acpi_probe_entry - boot-समय probing entry
 * @id:			ACPI table name
 * @type:		Optional subtable type to match
 *			(अगर @id contains subtables)
 * @subtable_valid:	Optional callback to check the validity of
 *			the subtable
 * @probe_table:	Callback to the driver being probed when table
 *			match is successful
 * @probe_subtbl:	Callback to the driver being probed when table and
 *			subtable match (and optional callback is successful)
 * @driver_data:	Sideband data provided back to the driver
 */
काष्ठा acpi_probe_entry अणु
	__u8 id[ACPI_TABLE_ID_LEN];
	__u8 type;
	acpi_probe_entry_validate_subtbl subtable_valid;
	जोड़ अणु
		acpi_tbl_table_handler probe_table;
		acpi_tbl_entry_handler probe_subtbl;
	पूर्ण;
	kernel_uदीर्घ_t driver_data;
पूर्ण;

#घोषणा ACPI_DECLARE_PROBE_ENTRY(table, name, table_id, subtable,	\
				 valid, data, fn)			\
	अटल स्थिर काष्ठा acpi_probe_entry __acpi_probe_##name	\
		__used __section("__" #table "_acpi_probe_table") = अणु	\
			.id = table_id,					\
			.type = subtable,				\
			.subtable_valid = valid,			\
			.probe_table = fn,				\
			.driver_data = data,				\
		पूर्ण

#घोषणा ACPI_DECLARE_SUBTABLE_PROBE_ENTRY(table, name, table_id,	\
					  subtable, valid, data, fn)	\
	अटल स्थिर काष्ठा acpi_probe_entry __acpi_probe_##name	\
		__used __section("__" #table "_acpi_probe_table") = अणु	\
			.id = table_id,					\
			.type = subtable,				\
			.subtable_valid = valid,			\
			.probe_subtbl = fn,				\
			.driver_data = data,				\
		पूर्ण

#घोषणा ACPI_PROBE_TABLE(name)		__##name##_acpi_probe_table
#घोषणा ACPI_PROBE_TABLE_END(name)	__##name##_acpi_probe_table_end

पूर्णांक __acpi_probe_device_table(काष्ठा acpi_probe_entry *start, पूर्णांक nr);

#घोषणा acpi_probe_device_table(t)					\
	(अणु 								\
		बाह्य काष्ठा acpi_probe_entry ACPI_PROBE_TABLE(t),	\
			                       ACPI_PROBE_TABLE_END(t);	\
		__acpi_probe_device_table(&ACPI_PROBE_TABLE(t),		\
					  (&ACPI_PROBE_TABLE_END(t) -	\
					   &ACPI_PROBE_TABLE(t)));	\
	पूर्ण)
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_dev_get_property(काष्ठा acpi_device *adev,
					स्थिर अक्षर *name, acpi_object_type type,
					स्थिर जोड़ acpi_object **obj)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक
__acpi_node_get_property_reference(स्थिर काष्ठा fwnode_handle *fwnode,
				स्थिर अक्षर *name, माप_प्रकार index, माप_प्रकार num_args,
				काष्ठा fwnode_reference_args *args)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक
acpi_node_get_property_reference(स्थिर काष्ठा fwnode_handle *fwnode,
				 स्थिर अक्षर *name, माप_प्रकार index,
				 काष्ठा fwnode_reference_args *args)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत पूर्णांक acpi_node_prop_get(स्थिर काष्ठा fwnode_handle *fwnode,
				     स्थिर अक्षर *propname,
				     व्योम **valptr)
अणु
	वापस -ENXIO;
पूर्ण

अटल अंतरभूत काष्ठा fwnode_handle *
acpi_get_next_subnode(स्थिर काष्ठा fwnode_handle *fwnode,
		      काष्ठा fwnode_handle *child)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा fwnode_handle *
acpi_node_get_parent(स्थिर काष्ठा fwnode_handle *fwnode)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा fwnode_handle *
acpi_graph_get_next_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
			     काष्ठा fwnode_handle *prev)
अणु
	वापस ERR_PTR(-ENXIO);
पूर्ण

अटल अंतरभूत पूर्णांक
acpi_graph_get_remote_endpoपूर्णांक(स्थिर काष्ठा fwnode_handle *fwnode,
			       काष्ठा fwnode_handle **remote,
			       काष्ठा fwnode_handle **port,
			       काष्ठा fwnode_handle **endpoपूर्णांक)
अणु
	वापस -ENXIO;
पूर्ण

#घोषणा ACPI_DECLARE_PROBE_ENTRY(table, name, table_id, subtable, valid, data, fn) \
	अटल स्थिर व्योम * __acpi_table_##name[]			\
		__attribute__((unused))					\
		 = अणु (व्योम *) table_id,					\
		     (व्योम *) subtable,					\
		     (व्योम *) valid,					\
		     (व्योम *) fn,					\
		     (व्योम *) data पूर्ण

#घोषणा acpi_probe_device_table(t)	(अणु पूर्णांक __r = 0; __r;पूर्ण)
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_TABLE_UPGRADE
व्योम acpi_table_upgrade(व्योम);
#अन्यथा
अटल अंतरभूत व्योम acpi_table_upgrade(व्योम) अणु पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_ACPI) && defined(CONFIG_ACPI_WATCHDOG)
बाह्य bool acpi_has_watchकरोg(व्योम);
#अन्यथा
अटल अंतरभूत bool acpi_has_watchकरोg(व्योम) अणु वापस false; पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_SPCR_TABLE
बाह्य bool qdf2400_e44_present;
पूर्णांक acpi_parse_spcr(bool enable_earlycon, bool enable_console);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_parse_spcr(bool enable_earlycon, bool enable_console)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_ACPI_GENERIC_GSI)
पूर्णांक acpi_irq_get(acpi_handle handle, अचिन्हित पूर्णांक index, काष्ठा resource *res);
#अन्यथा
अटल अंतरभूत
पूर्णांक acpi_irq_get(acpi_handle handle, अचिन्हित पूर्णांक index, काष्ठा resource *res)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_LPIT
पूर्णांक lpit_पढ़ो_residency_count_address(u64 *address);
#अन्यथा
अटल अंतरभूत पूर्णांक lpit_पढ़ो_residency_count_address(u64 *address)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI_PPTT
पूर्णांक acpi_pptt_cpu_is_thपढ़ो(अचिन्हित पूर्णांक cpu);
पूर्णांक find_acpi_cpu_topology(अचिन्हित पूर्णांक cpu, पूर्णांक level);
पूर्णांक find_acpi_cpu_topology_package(अचिन्हित पूर्णांक cpu);
पूर्णांक find_acpi_cpu_topology_hetero_id(अचिन्हित पूर्णांक cpu);
पूर्णांक find_acpi_cpu_cache_topology(अचिन्हित पूर्णांक cpu, पूर्णांक level);
#अन्यथा
अटल अंतरभूत पूर्णांक acpi_pptt_cpu_is_thपढ़ो(अचिन्हित पूर्णांक cpu)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक find_acpi_cpu_topology(अचिन्हित पूर्णांक cpu, पूर्णांक level)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक find_acpi_cpu_topology_package(अचिन्हित पूर्णांक cpu)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक find_acpi_cpu_topology_hetero_id(अचिन्हित पूर्णांक cpu)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक find_acpi_cpu_cache_topology(अचिन्हित पूर्णांक cpu, पूर्णांक level)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
बाह्य पूर्णांक acpi_platक्रमm_notअगरy(काष्ठा device *dev, क्रमागत kobject_action action);
#अन्यथा
अटल अंतरभूत पूर्णांक
acpi_platक्रमm_notअगरy(काष्ठा device *dev, क्रमागत kobject_action action)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर	/*_LINUX_ACPI_H*/
