<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_LOONGSON64_BOOT_PARAM_H_
#घोषणा __ASM_MACH_LOONGSON64_BOOT_PARAM_H_

#समावेश <linux/types.h>

#घोषणा SYSTEM_RAM_LOW		1
#घोषणा SYSTEM_RAM_HIGH		2
#घोषणा SYSTEM_RAM_RESERVED	3
#घोषणा PCI_IO			4
#घोषणा PCI_MEM			5
#घोषणा LOONGSON_CFG_REG	6
#घोषणा VIDEO_ROM		7
#घोषणा ADAPTER_ROM		8
#घोषणा ACPI_TABLE		9
#घोषणा SMBIOS_TABLE		10
#घोषणा MAX_MEMORY_TYPE		11

#घोषणा LOONGSON3_BOOT_MEM_MAP_MAX 128
काष्ठा efi_memory_map_loongson अणु
	u16 vers;	/* version of efi_memory_map */
	u32 nr_map;	/* number of memory_maps */
	u32 mem_freq;	/* memory frequence */
	काष्ठा mem_map अणु
		u32 node_id;	/* node_id which memory attached to */
		u32 mem_type;	/* प्रणाली memory, pci memory, pci io, etc. */
		u64 mem_start;	/* memory map start address */
		u32 mem_size;	/* each memory_map size, not the total size */
	पूर्ण map[LOONGSON3_BOOT_MEM_MAP_MAX];
पूर्ण __packed;

क्रमागत loongson_cpu_type अणु
	Legacy_2E = 0x0,
	Legacy_2F = 0x1,
	Legacy_3A = 0x2,
	Legacy_3B = 0x3,
	Legacy_1A = 0x4,
	Legacy_1B = 0x5,
	Legacy_2G = 0x6,
	Legacy_2H = 0x7,
	Loongson_1A = 0x100,
	Loongson_1B = 0x101,
	Loongson_2E = 0x200,
	Loongson_2F = 0x201,
	Loongson_2G = 0x202,
	Loongson_2H = 0x203,
	Loongson_3A = 0x300,
	Loongson_3B = 0x301
पूर्ण;

/*
 * Capability and feature descriptor काष्ठाure क्रम MIPS CPU
 */
काष्ठा efi_cpuinfo_loongson अणु
	u16 vers;     /* version of efi_cpuinfo_loongson */
	u32 processor_id; /* PRID, e.g. 6305, 6306 */
	u32 cputype;  /* Loongson_3A/3B, etc. */
	u32 total_node;   /* num of total numa nodes */
	u16 cpu_startup_core_id; /* Boot core id */
	u16 reserved_cores_mask;
	u32 cpu_घड़ी_freq; /* cpu_घड़ी */
	u32 nr_cpus;
पूर्ण __packed;

#घोषणा MAX_UARTS 64
काष्ठा uart_device अणु
	u32 iotype; /* see include/linux/serial_core.h */
	u32 uartclk;
	u32 पूर्णांक_offset;
	u64 uart_base;
पूर्ण __packed;

#घोषणा MAX_SENSORS 64
#घोषणा SENSOR_TEMPER  0x00000001
#घोषणा SENSOR_VOLTAGE 0x00000002
#घोषणा SENSOR_FAN     0x00000004
काष्ठा sensor_device अणु
	अक्षर name[32];  /* a क्रमmal name */
	अक्षर label[64]; /* a flexible description */
	u32 type;       /* SENSOR_* */
	u32 id;         /* instance id of a sensor-class */
	u32 fan_policy; /* see loongson_hwmon.h */
	u32 fan_percent;/* only क्रम स्थिरant speed policy */
	u64 base_addr;  /* base address of device रेजिस्टरs */
पूर्ण __packed;

काष्ठा प्रणाली_loongson अणु
	u16 vers;     /* version of प्रणाली_loongson */
	u32 ccnuma_smp; /* 0: no numa; 1: has numa */
	u32 sing_द्विगुन_channel; /* 1:single; 2:द्विगुन */
	u32 nr_uarts;
	काष्ठा uart_device uarts[MAX_UARTS];
	u32 nr_sensors;
	काष्ठा sensor_device sensors[MAX_SENSORS];
	अक्षर has_ec;
	अक्षर ec_name[32];
	u64 ec_base_addr;
	अक्षर has_tcm;
	अक्षर tcm_name[32];
	u64 tcm_base_addr;
	u64 workarounds; /* see workarounds.h */
पूर्ण __packed;

काष्ठा irq_source_routing_table अणु
	u16 vers;
	u16 size;
	u16 rtr_bus;
	u16 rtr_devfn;
	u32 venकरोr;
	u32 device;
	u32 PIC_type;   /* conक्रमm use HT or PCI to route to CPU-PIC */
	u64 ht_पूर्णांक_bit; /* 3A: 1<<24; 3B: 1<<16 */
	u64 ht_enable;  /* irqs used in this PIC */
	u32 node_id;    /* node id: 0x0-0; 0x1-1; 0x10-2; 0x11-3 */
	u64 pci_mem_start_addr;
	u64 pci_mem_end_addr;
	u64 pci_io_start_addr;
	u64 pci_io_end_addr;
	u64 pci_config_addr;
	u32 dma_mask_bits;
पूर्ण __packed;

काष्ठा पूर्णांकerface_info अणु
	u16 vers; /* version of the specअगरicition */
	u16 size;
	u8  flag;
	अक्षर description[64];
पूर्ण __packed;

#घोषणा MAX_RESOURCE_NUMBER 128
काष्ठा resource_loongson अणु
	u64 start; /* resource start address */
	u64 end;   /* resource end address */
	अक्षर name[64];
	u32 flags;
पूर्ण;

काष्ठा archdev_data अणुपूर्ण;  /* arch specअगरic additions */

काष्ठा board_devices अणु
	अक्षर name[64];    /* hold the device name */
	u32 num_resources; /* number of device_resource */
	/* क्रम each device's resource */
	काष्ठा resource_loongson resource[MAX_RESOURCE_NUMBER];
	/* arch specअगरic additions */
	काष्ठा archdev_data archdata;
पूर्ण;

काष्ठा loongson_special_attribute अणु
	u16 vers;     /* version of this special */
	अक्षर special_name[64]; /* special_atribute_name */
	u32 loongson_special_type; /* type of special device */
	/* क्रम each device's resource */
	काष्ठा resource_loongson resource[MAX_RESOURCE_NUMBER];
पूर्ण;

काष्ठा loongson_params अणु
	u64 memory_offset;	/* efi_memory_map_loongson काष्ठा offset */
	u64 cpu_offset;		/* efi_cpuinfo_loongson काष्ठा offset */
	u64 प्रणाली_offset;	/* प्रणाली_loongson काष्ठा offset */
	u64 irq_offset;		/* irq_source_routing_table काष्ठा offset */
	u64 पूर्णांकerface_offset;	/* पूर्णांकerface_info काष्ठा offset */
	u64 special_offset;	/* loongson_special_attribute काष्ठा offset */
	u64 boarddev_table_offset;  /* board_devices offset */
पूर्ण;

काष्ठा smbios_tables अणु
	u16 vers;     /* version of smbios */
	u64 vga_bios; /* vga_bios address */
	काष्ठा loongson_params lp;
पूर्ण;

काष्ठा efi_reset_प्रणाली_t अणु
	u64 ResetCold;
	u64 ResetWarm;
	u64 ResetType;
	u64 Shutकरोwn;
	u64 DoSuspend; /* शून्य अगर not support */
पूर्ण;

काष्ठा efi_loongson अणु
	u64 mps;	/* MPS table */
	u64 acpi;	/* ACPI table (IA64 ext 0.71) */
	u64 acpi20;	/* ACPI table (ACPI 2.0) */
	काष्ठा smbios_tables smbios;	/* SM BIOS table */
	u64 sal_systab;	/* SAL प्रणाली table */
	u64 boot_info;	/* boot info table */
पूर्ण;

काष्ठा boot_params अणु
	काष्ठा efi_loongson efi;
	काष्ठा efi_reset_प्रणाली_t reset_प्रणाली;
पूर्ण;

क्रमागत loongson_bridge_type अणु
	LS7A = 1,
	RS780E = 2,
	VIRTUAL = 3
पूर्ण;

बाह्य काष्ठा efi_memory_map_loongson *loongson_memmap;
बाह्य काष्ठा loongson_प्रणाली_configuration loongson_sysconf;

बाह्य काष्ठा board_devices *eboard;
बाह्य काष्ठा पूर्णांकerface_info *eपूर्णांकer;
बाह्य काष्ठा loongson_special_attribute *especial;

बाह्य u32 node_id_offset;
बाह्य व्योम ls7a_early_config(व्योम);
बाह्य व्योम rs780e_early_config(व्योम);
बाह्य व्योम भव_early_config(व्योम);

#पूर्ण_अगर
