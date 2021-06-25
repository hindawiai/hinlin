<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_BOOTPARAM_H
#घोषणा _ASM_X86_BOOTPARAM_H

/* setup_data/setup_indirect types */
#घोषणा SETUP_NONE			0
#घोषणा SETUP_E820_EXT			1
#घोषणा SETUP_DTB			2
#घोषणा SETUP_PCI			3
#घोषणा SETUP_EFI			4
#घोषणा SETUP_APPLE_PROPERTIES		5
#घोषणा SETUP_JAILHOUSE			6

#घोषणा SETUP_INसूचीECT			(1<<31)

/* SETUP_INसूचीECT | max(SETUP_*) */
#घोषणा SETUP_TYPE_MAX			(SETUP_INसूचीECT | SETUP_JAILHOUSE)

/* ram_size flags */
#घोषणा RAMDISK_IMAGE_START_MASK	0x07FF
#घोषणा RAMDISK_PROMPT_FLAG		0x8000
#घोषणा RAMDISK_LOAD_FLAG		0x4000

/* loadflags */
#घोषणा LOADED_HIGH	(1<<0)
#घोषणा KASLR_FLAG	(1<<1)
#घोषणा QUIET_FLAG	(1<<5)
#घोषणा KEEP_SEGMENTS	(1<<6)
#घोषणा CAN_USE_HEAP	(1<<7)

/* xloadflags */
#घोषणा XLF_KERNEL_64			(1<<0)
#घोषणा XLF_CAN_BE_LOADED_ABOVE_4G	(1<<1)
#घोषणा XLF_EFI_HANDOVER_32		(1<<2)
#घोषणा XLF_EFI_HANDOVER_64		(1<<3)
#घोषणा XLF_EFI_KEXEC			(1<<4)
#घोषणा XLF_5LEVEL			(1<<5)
#घोषणा XLF_5LEVEL_ENABLED		(1<<6)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/types.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/apm_मूलप्रण.स>
#समावेश <linux/edd.h>
#समावेश <यंत्र/ist.h>
#समावेश <video/edid.h>

/* extensible setup data list node */
काष्ठा setup_data अणु
	__u64 next;
	__u32 type;
	__u32 len;
	__u8 data[0];
पूर्ण;

/* extensible setup indirect data node */
काष्ठा setup_indirect अणु
	__u32 type;
	__u32 reserved;  /* Reserved, must be set to zero. */
	__u64 len;
	__u64 addr;
पूर्ण;

काष्ठा setup_header अणु
	__u8	setup_sects;
	__u16	root_flags;
	__u32	syssize;
	__u16	ram_size;
	__u16	vid_mode;
	__u16	root_dev;
	__u16	boot_flag;
	__u16	jump;
	__u32	header;
	__u16	version;
	__u32	realmode_swtch;
	__u16	start_sys_seg;
	__u16	kernel_version;
	__u8	type_of_loader;
	__u8	loadflags;
	__u16	setup_move_size;
	__u32	code32_start;
	__u32	ramdisk_image;
	__u32	ramdisk_size;
	__u32	bootsect_kludge;
	__u16	heap_end_ptr;
	__u8	ext_loader_ver;
	__u8	ext_loader_type;
	__u32	cmd_line_ptr;
	__u32	initrd_addr_max;
	__u32	kernel_alignment;
	__u8	relocatable_kernel;
	__u8	min_alignment;
	__u16	xloadflags;
	__u32	cmdline_size;
	__u32	hardware_subarch;
	__u64	hardware_subarch_data;
	__u32	payload_offset;
	__u32	payload_length;
	__u64	setup_data;
	__u64	pref_address;
	__u32	init_size;
	__u32	hanकरोver_offset;
	__u32	kernel_info_offset;
पूर्ण __attribute__((packed));

काष्ठा sys_desc_table अणु
	__u16 length;
	__u8  table[14];
पूर्ण;

/* Gleaned from OFW's set-parameters in cpu/x86/pc/linux.fth */
काष्ठा olpc_ofw_header अणु
	__u32 ofw_magic;	/* OFW signature */
	__u32 ofw_version;
	__u32 cअगर_handler;	/* callback पूर्णांकo OFW */
	__u32 irq_desc_table;
पूर्ण __attribute__((packed));

काष्ठा efi_info अणु
	__u32 efi_loader_signature;
	__u32 efi_systab;
	__u32 efi_memdesc_size;
	__u32 efi_memdesc_version;
	__u32 efi_memmap;
	__u32 efi_memmap_size;
	__u32 efi_systab_hi;
	__u32 efi_memmap_hi;
पूर्ण;

/*
 * This is the maximum number of entries in काष्ठा boot_params::e820_table
 * (the zeropage), which is part of the x86 boot protocol ABI:
 */
#घोषणा E820_MAX_ENTRIES_ZEROPAGE 128

/*
 * The E820 memory region entry of the boot protocol ABI:
 */
काष्ठा boot_e820_entry अणु
	__u64 addr;
	__u64 size;
	__u32 type;
पूर्ण __attribute__((packed));

/*
 * Smallest compatible version of jailhouse_setup_data required by this kernel.
 */
#घोषणा JAILHOUSE_SETUP_REQUIRED_VERSION	1

/*
 * The boot loader is passing platक्रमm inक्रमmation via this Jailhouse-specअगरic
 * setup data काष्ठाure.
 */
काष्ठा jailhouse_setup_data अणु
	काष्ठा अणु
		__u16	version;
		__u16	compatible_version;
	पूर्ण __attribute__((packed)) hdr;
	काष्ठा अणु
		__u16	pm_समयr_address;
		__u16	num_cpus;
		__u64	pci_mmconfig_base;
		__u32	tsc_khz;
		__u32	apic_khz;
		__u8	standard_ioapic;
		__u8	cpu_ids[255];
	पूर्ण __attribute__((packed)) v1;
	काष्ठा अणु
		__u32	flags;
	पूर्ण __attribute__((packed)) v2;
पूर्ण __attribute__((packed));

/* The so-called "zeropage" */
काष्ठा boot_params अणु
	काष्ठा screen_info screen_info;			/* 0x000 */
	काष्ठा apm_bios_info apm_bios_info;		/* 0x040 */
	__u8  _pad2[4];					/* 0x054 */
	__u64  tboot_addr;				/* 0x058 */
	काष्ठा ist_info ist_info;			/* 0x060 */
	__u64 acpi_rsdp_addr;				/* 0x070 */
	__u8  _pad3[8];					/* 0x078 */
	__u8  hd0_info[16];	/* obsolete! */		/* 0x080 */
	__u8  hd1_info[16];	/* obsolete! */		/* 0x090 */
	काष्ठा sys_desc_table sys_desc_table; /* obsolete! */	/* 0x0a0 */
	काष्ठा olpc_ofw_header olpc_ofw_header;		/* 0x0b0 */
	__u32 ext_ramdisk_image;			/* 0x0c0 */
	__u32 ext_ramdisk_size;				/* 0x0c4 */
	__u32 ext_cmd_line_ptr;				/* 0x0c8 */
	__u8  _pad4[116];				/* 0x0cc */
	काष्ठा edid_info edid_info;			/* 0x140 */
	काष्ठा efi_info efi_info;			/* 0x1c0 */
	__u32 alt_mem_k;				/* 0x1e0 */
	__u32 scratch;		/* Scratch field! */	/* 0x1e4 */
	__u8  e820_entries;				/* 0x1e8 */
	__u8  eddbuf_entries;				/* 0x1e9 */
	__u8  edd_mbr_sig_buf_entries;			/* 0x1ea */
	__u8  kbd_status;				/* 0x1eb */
	__u8  secure_boot;				/* 0x1ec */
	__u8  _pad5[2];					/* 0x1ed */
	/*
	 * The sentinel is set to a nonzero value (0xff) in header.S.
	 *
	 * A bootloader is supposed to only take setup_header and put
	 * it पूर्णांकo a clean boot_params buffer. If it turns out that
	 * it is clumsy or too generous with the buffer, it most
	 * probably will pick up the sentinel variable too. The fact
	 * that this variable then is still 0xff will let kernel
	 * know that some variables in boot_params are invalid and
	 * kernel should zero out certain portions of boot_params.
	 */
	__u8  sentinel;					/* 0x1ef */
	__u8  _pad6[1];					/* 0x1f0 */
	काष्ठा setup_header hdr;    /* setup header */	/* 0x1f1 */
	__u8  _pad7[0x290-0x1f1-माप(काष्ठा setup_header)];
	__u32 edd_mbr_sig_buffer[EDD_MBR_SIG_MAX];	/* 0x290 */
	काष्ठा boot_e820_entry e820_table[E820_MAX_ENTRIES_ZEROPAGE]; /* 0x2d0 */
	__u8  _pad8[48];				/* 0xcd0 */
	काष्ठा edd_info eddbuf[EDDMAXNR];		/* 0xd00 */
	__u8  _pad9[276];				/* 0xeec */
पूर्ण __attribute__((packed));

/**
 * क्रमागत x86_hardware_subarch - x86 hardware subarchitecture
 *
 * The x86 hardware_subarch and hardware_subarch_data were added as of the x86
 * boot protocol 2.07 to help distinguish and support custom x86 boot
 * sequences. This क्रमागत represents accepted values क्रम the x86
 * hardware_subarch.  Custom x86 boot sequences (not X86_SUBARCH_PC) करो not
 * have or simply *cannot* make use of natural stubs like BIOS or EFI, the
 * hardware_subarch can be used on the Linux entry path to revector to a
 * subarchitecture stub when needed. This subarchitecture stub can be used to
 * set up Linux boot parameters or क्रम special care to account क्रम nonstandard
 * handling of page tables.
 *
 * These क्रमागतs should only ever be used by x86 code, and the code that uses
 * it should be well contained and comparपंचांगentalized.
 *
 * KVM and Xen HVM करो not have a subarch as these are expected to follow
 * standard x86 boot entries. If there is a genuine need क्रम "hypervisor" type
 * that should be considered separately in the future. Future guest types
 * should seriously consider working with standard x86 boot stubs such as
 * the BIOS or EFI boot stubs.
 *
 * WARNING: this क्रमागत is only used क्रम legacy hacks, क्रम platक्रमm features that
 *	    are not easily क्रमागतerated or discoverable. You should not ever use
 *	    this क्रम new features.
 *
 * @X86_SUBARCH_PC: Should be used अगर the hardware is क्रमागतerable using standard
 *	PC mechanisms (PCI, ACPI) and करोesn't need a special boot flow.
 * @X86_SUBARCH_LGUEST: Used क्रम x86 hypervisor demo, lguest, deprecated
 * @X86_SUBARCH_XEN: Used क्रम Xen guest types which follow the PV boot path,
 * 	which start at यंत्र startup_xen() entry poपूर्णांक and later jump to the C
 * 	xen_start_kernel() entry poपूर्णांक. Both करोmU and करोm0 type of guests are
 * 	currently supported through this PV boot path.
 * @X86_SUBARCH_INTEL_MID: Used क्रम Intel MID (Mobile Internet Device) platक्रमm
 *	प्रणालीs which करो not have the PCI legacy पूर्णांकerfaces.
 * @X86_SUBARCH_CE4100: Used क्रम Intel CE media processor (CE4100) SoC
 * 	क्रम settop boxes and media devices, the use of a subarch क्रम CE4100
 * 	is more of a hack...
 */
क्रमागत x86_hardware_subarch अणु
	X86_SUBARCH_PC = 0,
	X86_SUBARCH_LGUEST,
	X86_SUBARCH_XEN,
	X86_SUBARCH_INTEL_MID,
	X86_SUBARCH_CE4100,
	X86_NR_SUBARCHS,
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_X86_BOOTPARAM_H */
