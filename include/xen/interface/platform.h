<शैली गुरु>
/******************************************************************************
 * platक्रमm.h
 *
 * Hardware platक्रमm operations. Intended क्रम use by करोमुख्य-0 kernel.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2002-2006, K Fraser
 */

#अगर_अघोषित __XEN_PUBLIC_PLATFORM_H__
#घोषणा __XEN_PUBLIC_PLATFORM_H__

#समावेश <xen/पूर्णांकerface/xen.h>

#घोषणा XENPF_INTERFACE_VERSION 0x03000001

/*
 * Set घड़ी such that it would पढ़ो <secs,nsecs> after 00:00:00 UTC,
 * 1 January, 1970 अगर the current प्रणाली समय was <प्रणाली_समय>.
 */
#घोषणा XENPF_समय_रखो32             17
काष्ठा xenpf_समय_रखो32 अणु
	/* IN variables. */
	uपूर्णांक32_t secs;
	uपूर्णांक32_t nsecs;
	uपूर्णांक64_t प्रणाली_समय;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_समय_रखो32_t);
#घोषणा XENPF_समय_रखो64           62
काष्ठा xenpf_समय_रखो64 अणु
    /* IN variables. */
    uपूर्णांक64_t secs;
    uपूर्णांक32_t nsecs;
    uपूर्णांक32_t mbz;
    uपूर्णांक64_t प्रणाली_समय;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_समय_रखो64_t);

/*
 * Request memory range (@mfn, @mfn+@nr_mfns-1) to have type @type.
 * On x86, @type is an architecture-defined MTRR memory type.
 * On success, वापसs the MTRR that was used (@reg) and a handle that can
 * be passed to XENPF_DEL_MEMTYPE to accurately tear करोwn the new setting.
 * (x86-specअगरic).
 */
#घोषणा XENPF_add_memtype         31
काष्ठा xenpf_add_memtype अणु
	/* IN variables. */
	xen_pfn_t mfn;
	uपूर्णांक64_t nr_mfns;
	uपूर्णांक32_t type;
	/* OUT variables. */
	uपूर्णांक32_t handle;
	uपूर्णांक32_t reg;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_add_memtype_t);

/*
 * Tear करोwn an existing memory-range type. If @handle is remembered then it
 * should be passed in to accurately tear करोwn the correct setting (in हाल
 * of overlapping memory regions with dअगरfering types). If it is not known
 * then @handle should be set to zero. In all हालs @reg must be set.
 * (x86-specअगरic).
 */
#घोषणा XENPF_del_memtype         32
काष्ठा xenpf_del_memtype अणु
	/* IN variables. */
	uपूर्णांक32_t handle;
	uपूर्णांक32_t reg;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_del_memtype_t);

/* Read current type of an MTRR (x86-specअगरic). */
#घोषणा XENPF_पढ़ो_memtype        33
काष्ठा xenpf_पढ़ो_memtype अणु
	/* IN variables. */
	uपूर्णांक32_t reg;
	/* OUT variables. */
	xen_pfn_t mfn;
	uपूर्णांक64_t nr_mfns;
	uपूर्णांक32_t type;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_पढ़ो_memtype_t);

#घोषणा XENPF_microcode_update    35
काष्ठा xenpf_microcode_update अणु
	/* IN variables. */
	GUEST_HANDLE(व्योम) data;          /* Poपूर्णांकer to microcode data */
	uपूर्णांक32_t length;                  /* Length of microcode data. */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_microcode_update_t);

#घोषणा XENPF_platक्रमm_quirk      39
#घोषणा QUIRK_NOIRQBALANCING      1 /* Do not restrict IO-APIC RTE tarमाला_लो */
#घोषणा QUIRK_IOAPIC_BAD_REGSEL   2 /* IO-APIC REGSEL क्रममाला_लो its value    */
#घोषणा QUIRK_IOAPIC_GOOD_REGSEL  3 /* IO-APIC REGSEL behaves properly     */
काष्ठा xenpf_platक्रमm_quirk अणु
	/* IN variables. */
	uपूर्णांक32_t quirk_id;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_platक्रमm_quirk_t);

#घोषणा XENPF_efi_runसमय_call    49
#घोषणा XEN_EFI_get_समय                      1
#घोषणा XEN_EFI_set_समय                      2
#घोषणा XEN_EFI_get_wakeup_समय               3
#घोषणा XEN_EFI_set_wakeup_समय               4
#घोषणा XEN_EFI_get_next_high_monotonic_count 5
#घोषणा XEN_EFI_get_variable                  6
#घोषणा XEN_EFI_set_variable                  7
#घोषणा XEN_EFI_get_next_variable_name        8
#घोषणा XEN_EFI_query_variable_info           9
#घोषणा XEN_EFI_query_capsule_capabilities   10
#घोषणा XEN_EFI_update_capsule               11

काष्ठा xenpf_efi_runसमय_call अणु
	uपूर्णांक32_t function;
	/*
	 * This field is generally used क्रम per sub-function flags (defined
	 * below), except क्रम the XEN_EFI_get_next_high_monotonic_count हाल,
	 * where it holds the single वापसed value.
	 */
	uपूर्णांक32_t misc;
	xen_uदीर्घ_t status;
	जोड़ अणु
#घोषणा XEN_EFI_GET_TIME_SET_CLEARS_NS 0x00000001
		काष्ठा अणु
			काष्ठा xenpf_efi_समय अणु
				uपूर्णांक16_t year;
				uपूर्णांक8_t month;
				uपूर्णांक8_t day;
				uपूर्णांक8_t hour;
				uपूर्णांक8_t min;
				uपूर्णांक8_t sec;
				uपूर्णांक32_t ns;
				पूर्णांक16_t tz;
				uपूर्णांक8_t daylight;
			पूर्ण समय;
			uपूर्णांक32_t resolution;
			uपूर्णांक32_t accuracy;
		पूर्ण get_समय;

		काष्ठा xenpf_efi_समय set_समय;

#घोषणा XEN_EFI_GET_WAKEUP_TIME_ENABLED 0x00000001
#घोषणा XEN_EFI_GET_WAKEUP_TIME_PENDING 0x00000002
		काष्ठा xenpf_efi_समय get_wakeup_समय;

#घोषणा XEN_EFI_SET_WAKEUP_TIME_ENABLE      0x00000001
#घोषणा XEN_EFI_SET_WAKEUP_TIME_ENABLE_ONLY 0x00000002
		काष्ठा xenpf_efi_समय set_wakeup_समय;

#घोषणा XEN_EFI_VARIABLE_NON_VOLATILE       0x00000001
#घोषणा XEN_EFI_VARIABLE_BOOTSERVICE_ACCESS 0x00000002
#घोषणा XEN_EFI_VARIABLE_RUNTIME_ACCESS     0x00000004
		काष्ठा अणु
			GUEST_HANDLE(व्योम) name;  /* UCS-2/UTF-16 string */
			xen_uदीर्घ_t size;
			GUEST_HANDLE(व्योम) data;
			काष्ठा xenpf_efi_guid अणु
				uपूर्णांक32_t data1;
				uपूर्णांक16_t data2;
				uपूर्णांक16_t data3;
				uपूर्णांक8_t data4[8];
			पूर्ण venकरोr_guid;
		पूर्ण get_variable, set_variable;

		काष्ठा अणु
			xen_uदीर्घ_t size;
			GUEST_HANDLE(व्योम) name;  /* UCS-2/UTF-16 string */
			काष्ठा xenpf_efi_guid venकरोr_guid;
		पूर्ण get_next_variable_name;

		काष्ठा अणु
			uपूर्णांक32_t attr;
			uपूर्णांक64_t max_store_size;
			uपूर्णांक64_t reमुख्य_store_size;
			uपूर्णांक64_t max_size;
		पूर्ण query_variable_info;

		काष्ठा अणु
			GUEST_HANDLE(व्योम) capsule_header_array;
			xen_uदीर्घ_t capsule_count;
			uपूर्णांक64_t max_capsule_size;
			uपूर्णांक32_t reset_type;
		पूर्ण query_capsule_capabilities;

		काष्ठा अणु
			GUEST_HANDLE(व्योम) capsule_header_array;
			xen_uदीर्घ_t capsule_count;
			uपूर्णांक64_t sg_list; /* machine address */
		पूर्ण update_capsule;
	पूर्ण u;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_efi_runसमय_call);

#घोषणा  XEN_FW_EFI_VERSION        0
#घोषणा  XEN_FW_EFI_CONFIG_TABLE   1
#घोषणा  XEN_FW_EFI_VENDOR         2
#घोषणा  XEN_FW_EFI_MEM_INFO       3
#घोषणा  XEN_FW_EFI_RT_VERSION     4

#घोषणा XENPF_firmware_info       50
#घोषणा XEN_FW_DISK_INFO          1 /* from पूर्णांक 13 AH=08/41/48 */
#घोषणा XEN_FW_DISK_MBR_SIGNATURE 2 /* from MBR offset 0x1b8 */
#घोषणा XEN_FW_VBEDDC_INFO        3 /* from पूर्णांक 10 AX=4f15 */
#घोषणा XEN_FW_EFI_INFO           4 /* from EFI */
#घोषणा XEN_FW_KBD_SHIFT_FLAGS    5 /* Int16, Fn02: Get keyboard shअगरt flags. */

काष्ठा xenpf_firmware_info अणु
	/* IN variables. */
	uपूर्णांक32_t type;
	uपूर्णांक32_t index;
	/* OUT variables. */
	जोड़ अणु
		काष्ठा अणु
			/* Int13, Fn48: Check Extensions Present. */
			uपूर्णांक8_t device;                   /* %dl: bios device number */
			uपूर्णांक8_t version;                  /* %ah: major version      */
			uपूर्णांक16_t पूर्णांकerface_support;       /* %cx: support biपंचांगap     */
			/* Int13, Fn08: Legacy Get Device Parameters. */
			uपूर्णांक16_t legacy_max_cylinder;     /* %cl[7:6]:%ch: max cyl # */
			uपूर्णांक8_t legacy_max_head;          /* %dh: max head #         */
			uपूर्णांक8_t legacy_sectors_per_track; /* %cl[5:0]: max sector #  */
			/* Int13, Fn41: Get Device Parameters (as filled पूर्णांकo %ds:%esi). */
			/* NB. First uपूर्णांक16_t of buffer must be set to buffer size.      */
			GUEST_HANDLE(व्योम) edd_params;
		पूर्ण disk_info; /* XEN_FW_DISK_INFO */
		काष्ठा अणु
			uपूर्णांक8_t device;                   /* bios device number  */
			uपूर्णांक32_t mbr_signature;           /* offset 0x1b8 in mbr */
		पूर्ण disk_mbr_signature; /* XEN_FW_DISK_MBR_SIGNATURE */
		काष्ठा अणु
			/* Int10, AX=4F15: Get EDID info. */
			uपूर्णांक8_t capabilities;
			uपूर्णांक8_t edid_transfer_समय;
			/* must refer to 128-byte buffer */
			GUEST_HANDLE(uअक्षर) edid;
		पूर्ण vbeddc_info; /* XEN_FW_VBEDDC_INFO */

		जोड़ xenpf_efi_info अणु
			uपूर्णांक32_t version;
			काष्ठा अणु
				uपूर्णांक64_t addr;   /* EFI_CONFIGURATION_TABLE */
				uपूर्णांक32_t nent;
			पूर्ण cfg;
			काष्ठा अणु
				uपूर्णांक32_t revision;
				uपूर्णांक32_t bufsz;  /* input, in bytes */
				GUEST_HANDLE(व्योम) name;
				/* UCS-2/UTF-16 string */
			पूर्ण venकरोr;
			काष्ठा अणु
				uपूर्णांक64_t addr;
				uपूर्णांक64_t size;
				uपूर्णांक64_t attr;
				uपूर्णांक32_t type;
			पूर्ण mem;
		पूर्ण efi_info; /* XEN_FW_EFI_INFO */

		uपूर्णांक8_t kbd_shअगरt_flags; /* XEN_FW_KBD_SHIFT_FLAGS */
	पूर्ण u;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_firmware_info_t);

#घोषणा XENPF_enter_acpi_sleep    51
काष्ठा xenpf_enter_acpi_sleep अणु
	/* IN variables */
	uपूर्णांक16_t val_a;             /* PM1a control / sleep type A. */
	uपूर्णांक16_t val_b;             /* PM1b control / sleep type B. */
	uपूर्णांक32_t sleep_state;       /* Which state to enter (Sn). */
#घोषणा XENPF_ACPI_SLEEP_EXTENDED 0x00000001
	uपूर्णांक32_t flags;             /* XENPF_ACPI_SLEEP_*. */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_enter_acpi_sleep_t);

#घोषणा XENPF_change_freq         52
काष्ठा xenpf_change_freq अणु
	/* IN variables */
	uपूर्णांक32_t flags; /* Must be zero. */
	uपूर्णांक32_t cpu;   /* Physical cpu. */
	uपूर्णांक64_t freq;  /* New frequency (Hz). */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_change_freq_t);

/*
 * Get idle बार (nanoseconds since boot) क्रम physical CPUs specअगरied in the
 * @cpumap_biपंचांगap with range [0..@cpumap_nr_cpus-1]. The @idleसमय array is
 * indexed by CPU number; only entries with the corresponding @cpumap_biपंचांगap
 * bit set are written to. On वापस, @cpumap_biपंचांगap is modअगरied so that any
 * non-existent CPUs are cleared. Such CPUs have their @idleसमय array entry
 * cleared.
 */
#घोषणा XENPF_getidleसमय         53
काष्ठा xenpf_getidleसमय अणु
	/* IN/OUT variables */
	/* IN: CPUs to पूर्णांकerrogate; OUT: subset of IN which are present */
	GUEST_HANDLE(uअक्षर) cpumap_biपंचांगap;
	/* IN variables */
	/* Size of cpumap biपंचांगap. */
	uपूर्णांक32_t cpumap_nr_cpus;
	/* Must be indexable क्रम every cpu in cpumap_biपंचांगap. */
	GUEST_HANDLE(uपूर्णांक64_t) idleसमय;
	/* OUT variables */
	/* System समय when the idleसमय snapshots were taken. */
	uपूर्णांक64_t now;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_getidleसमय_प्रकार);

#घोषणा XENPF_set_processor_pminfo      54

/* ability bits */
#घोषणा XEN_PROCESSOR_PM_CX	1
#घोषणा XEN_PROCESSOR_PM_PX	2
#घोषणा XEN_PROCESSOR_PM_TX	4

/* cmd type */
#घोषणा XEN_PM_CX   0
#घोषणा XEN_PM_PX   1
#घोषणा XEN_PM_TX   2
#घोषणा XEN_PM_PDC  3
/* Px sub info type */
#घोषणा XEN_PX_PCT   1
#घोषणा XEN_PX_PSS   2
#घोषणा XEN_PX_PPC   4
#घोषणा XEN_PX_PSD   8

काष्ठा xen_घातer_रेजिस्टर अणु
	uपूर्णांक32_t     space_id;
	uपूर्णांक32_t     bit_width;
	uपूर्णांक32_t     bit_offset;
	uपूर्णांक32_t     access_size;
	uपूर्णांक64_t     address;
पूर्ण;

काष्ठा xen_processor_csd अणु
	uपूर्णांक32_t    करोमुख्य;      /* करोमुख्य number of one dependent group */
	uपूर्णांक32_t    coord_type;  /* coordination type */
	uपूर्णांक32_t    num;         /* number of processors in same करोमुख्य */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_processor_csd);

काष्ठा xen_processor_cx अणु
	काष्ठा xen_घातer_रेजिस्टर  reg; /* GAS क्रम Cx trigger रेजिस्टर */
	uपूर्णांक8_t     type;     /* cstate value, c0: 0, c1: 1, ... */
	uपूर्णांक32_t    latency;  /* worst latency (ms) to enter/निकास this cstate */
	uपूर्णांक32_t    घातer;    /* average घातer consumption(mW) */
	uपूर्णांक32_t    dpcnt;    /* number of dependency entries */
	GUEST_HANDLE(xen_processor_csd) dp; /* शून्य अगर no dependency */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_processor_cx);

काष्ठा xen_processor_flags अणु
	uपूर्णांक32_t bm_control:1;
	uपूर्णांक32_t bm_check:1;
	uपूर्णांक32_t has_cst:1;
	uपूर्णांक32_t घातer_setup_करोne:1;
	uपूर्णांक32_t bm_rld_set:1;
पूर्ण;

काष्ठा xen_processor_घातer अणु
	uपूर्णांक32_t count;  /* number of C state entries in array below */
	काष्ठा xen_processor_flags flags;  /* global flags of this processor */
	GUEST_HANDLE(xen_processor_cx) states; /* supported c states */
पूर्ण;

काष्ठा xen_pct_रेजिस्टर अणु
	uपूर्णांक8_t  descriptor;
	uपूर्णांक16_t length;
	uपूर्णांक8_t  space_id;
	uपूर्णांक8_t  bit_width;
	uपूर्णांक8_t  bit_offset;
	uपूर्णांक8_t  reserved;
	uपूर्णांक64_t address;
पूर्ण;

काष्ठा xen_processor_px अणु
	uपूर्णांक64_t core_frequency; /* megahertz */
	uपूर्णांक64_t घातer;      /* milliWatts */
	uपूर्णांक64_t transition_latency; /* microseconds */
	uपूर्णांक64_t bus_master_latency; /* microseconds */
	uपूर्णांक64_t control;        /* control value */
	uपूर्णांक64_t status;     /* success indicator */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_processor_px);

काष्ठा xen_psd_package अणु
	uपूर्णांक64_t num_entries;
	uपूर्णांक64_t revision;
	uपूर्णांक64_t करोमुख्य;
	uपूर्णांक64_t coord_type;
	uपूर्णांक64_t num_processors;
पूर्ण;

काष्ठा xen_processor_perक्रमmance अणु
	uपूर्णांक32_t flags;     /* flag क्रम Px sub info type */
	uपूर्णांक32_t platक्रमm_limit;  /* Platक्रमm limitation on freq usage */
	काष्ठा xen_pct_रेजिस्टर control_रेजिस्टर;
	काष्ठा xen_pct_रेजिस्टर status_रेजिस्टर;
	uपूर्णांक32_t state_count;     /* total available perक्रमmance states */
	GUEST_HANDLE(xen_processor_px) states;
	काष्ठा xen_psd_package करोमुख्य_info;
	uपूर्णांक32_t shared_type;     /* coordination type of this processor */
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_processor_perक्रमmance);

काष्ठा xenpf_set_processor_pminfo अणु
	/* IN variables */
	uपूर्णांक32_t id;    /* ACPI CPU ID */
	uपूर्णांक32_t type;  /* अणुXEN_PM_CX, XEN_PM_PXपूर्ण */
	जोड़ अणु
		काष्ठा xen_processor_घातer          घातer;/* Cx: _CST/_CSD */
		काष्ठा xen_processor_perक्रमmance    perf; /* Px: _PPC/_PCT/_PSS/_PSD */
		GUEST_HANDLE(uपूर्णांक32_t)              pdc;
	पूर्ण;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_set_processor_pminfo);

#घोषणा XENPF_get_cpuinfo 55
काष्ठा xenpf_pcpuinfo अणु
	/* IN */
	uपूर्णांक32_t xen_cpuid;
	/* OUT */
	/* The maxium cpu_id that is present */
	uपूर्णांक32_t max_present;
#घोषणा XEN_PCPU_FLAGS_ONLINE   1
	/* Correponding xen_cpuid is not present*/
#घोषणा XEN_PCPU_FLAGS_INVALID  2
	uपूर्णांक32_t flags;
	uपूर्णांक32_t apic_id;
	uपूर्णांक32_t acpi_id;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_pcpuinfo);

#घोषणा XENPF_cpu_online	56
#घोषणा XENPF_cpu_offline	57
काष्ठा xenpf_cpu_ol अणु
	uपूर्णांक32_t cpuid;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_cpu_ol);

#घोषणा XENPF_cpu_hotadd	58
काष्ठा xenpf_cpu_hotadd अणु
	uपूर्णांक32_t apic_id;
	uपूर्णांक32_t acpi_id;
	uपूर्णांक32_t pxm;
पूर्ण;

#घोषणा XENPF_mem_hotadd	59
काष्ठा xenpf_mem_hotadd अणु
	uपूर्णांक64_t spfn;
	uपूर्णांक64_t epfn;
	uपूर्णांक32_t pxm;
	uपूर्णांक32_t flags;
पूर्ण;

#घोषणा XENPF_core_parking     60
काष्ठा xenpf_core_parking अणु
	/* IN variables */
#घोषणा XEN_CORE_PARKING_SET   1
#घोषणा XEN_CORE_PARKING_GET   2
	uपूर्णांक32_t type;
	/* IN variables:  set cpu nums expected to be idled */
	/* OUT variables: get cpu nums actually be idled */
	uपूर्णांक32_t idle_nums;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_core_parking);

#घोषणा XENPF_get_symbol      63
काष्ठा xenpf_symdata अणु
	/* IN/OUT variables */
	uपूर्णांक32_t	namelen; /* size of 'name' buffer */

	/* IN/OUT variables */
	uपूर्णांक32_t	symnum; /* IN:  Symbol to पढ़ो                       */
				/* OUT: Next available symbol. If same as IN */
				/* then  we reached the end                  */

	/* OUT variables */
	GUEST_HANDLE(अक्षर) name;
	uपूर्णांक64_t	address;
	अक्षर            type;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xenpf_symdata);

काष्ठा xen_platक्रमm_op अणु
	uपूर्णांक32_t cmd;
	uपूर्णांक32_t पूर्णांकerface_version; /* XENPF_INTERFACE_VERSION */
	जोड़ अणु
		काष्ठा xenpf_समय_रखो32         समय_रखो32;
		काष्ठा xenpf_समय_रखो64         समय_रखो64;
		काष्ठा xenpf_add_memtype       add_memtype;
		काष्ठा xenpf_del_memtype       del_memtype;
		काष्ठा xenpf_पढ़ो_memtype      पढ़ो_memtype;
		काष्ठा xenpf_microcode_update  microcode;
		काष्ठा xenpf_platक्रमm_quirk    platक्रमm_quirk;
		काष्ठा xenpf_efi_runसमय_call  efi_runसमय_call;
		काष्ठा xenpf_firmware_info     firmware_info;
		काष्ठा xenpf_enter_acpi_sleep  enter_acpi_sleep;
		काष्ठा xenpf_change_freq       change_freq;
		काष्ठा xenpf_getidleसमय       getidleसमय;
		काष्ठा xenpf_set_processor_pminfo set_pminfo;
		काष्ठा xenpf_pcpuinfo          pcpu_info;
		काष्ठा xenpf_cpu_ol            cpu_ol;
		काष्ठा xenpf_cpu_hotadd        cpu_add;
		काष्ठा xenpf_mem_hotadd        mem_add;
		काष्ठा xenpf_core_parking      core_parking;
		काष्ठा xenpf_symdata           symdata;
		uपूर्णांक8_t                        pad[128];
	पूर्ण u;
पूर्ण;
DEFINE_GUEST_HANDLE_STRUCT(xen_platक्रमm_op_t);

#पूर्ण_अगर /* __XEN_PUBLIC_PLATFORM_H__ */
