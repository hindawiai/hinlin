<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_X86_UV_BIOS_H
#घोषणा _ASM_X86_UV_BIOS_H

/*
 * UV BIOS layer definitions.
 *
 * (C) Copyright 2020 Hewlett Packard Enterprise Development LP
 * Copyright (C) 2007-2017 Silicon Graphics, Inc. All rights reserved.
 * Copyright (c) Russ Anderson <rja@sgi.com>
 */

#समावेश <linux/rtc.h>

/*
 * Values क्रम the BIOS calls.  It is passed as the first * argument in the
 * BIOS call.  Passing any other value in the first argument will result
 * in a BIOS_STATUS_UNIMPLEMENTED वापस status.
 */
क्रमागत uv_bios_cmd अणु
	UV_BIOS_COMMON,
	UV_BIOS_GET_SN_INFO,
	UV_BIOS_FREQ_BASE,
	UV_BIOS_WATCHLIST_ALLOC,
	UV_BIOS_WATCHLIST_FREE,
	UV_BIOS_MEMPROTECT,
	UV_BIOS_GET_PARTITION_ADDR,
	UV_BIOS_SET_LEGACY_VGA_TARGET
पूर्ण;

#घोषणा UV_BIOS_EXTRA			    0x10000
#घोषणा UV_BIOS_GET_PCI_TOPOLOGY	    0x10001
#घोषणा UV_BIOS_GET_GEOINFO		    0x10003

#घोषणा UV_BIOS_EXTRA_OP_MEM_COPYIN	    0x1000
#घोषणा UV_BIOS_EXTRA_OP_MEM_COPYOUT	    0x2000
#घोषणा UV_BIOS_EXTRA_OP_MASK		    0x0fff
#घोषणा UV_BIOS_EXTRA_GET_HEAPSIZE	    1
#घोषणा UV_BIOS_EXTRA_INSTALL_HEAP	    2
#घोषणा UV_BIOS_EXTRA_MASTER_NASID	    3
#घोषणा UV_BIOS_EXTRA_OBJECT_COUNT	    (10|UV_BIOS_EXTRA_OP_MEM_COPYOUT)
#घोषणा UV_BIOS_EXTRA_ENUM_OBJECTS	    (12|UV_BIOS_EXTRA_OP_MEM_COPYOUT)
#घोषणा UV_BIOS_EXTRA_ENUM_PORTS	    (13|UV_BIOS_EXTRA_OP_MEM_COPYOUT)

/*
 * Status values वापसed from a BIOS call.
 */
क्रमागत अणु
	BIOS_STATUS_MORE_PASSES		=  1,
	BIOS_STATUS_SUCCESS		=  0,
	BIOS_STATUS_UNIMPLEMENTED	= -ENOSYS,
	BIOS_STATUS_EINVAL		= -EINVAL,
	BIOS_STATUS_UNAVAIL		= -EBUSY,
	BIOS_STATUS_ABORT		= -EINTR,
पूर्ण;

/* Address map parameters */
काष्ठा uv_gam_parameters अणु
	u64	mmr_base;
	u64	gru_base;
	u8	mmr_shअगरt;	/* Convert PNode to MMR space offset */
	u8	gru_shअगरt;	/* Convert PNode to GRU space offset */
	u8	gpa_shअगरt;	/* Size of offset field in GRU phys addr */
	u8	unused1;
पूर्ण;

/* UV_TABLE_GAM_RANGE_ENTRY values */
#घोषणा UV_GAM_RANGE_TYPE_UNUSED	0 /* End of table */
#घोषणा UV_GAM_RANGE_TYPE_RAM		1 /* Normal RAM */
#घोषणा UV_GAM_RANGE_TYPE_NVRAM		2 /* Non-अस्थिर memory */
#घोषणा UV_GAM_RANGE_TYPE_NV_WINDOW	3 /* NVMDIMM block winकरोw */
#घोषणा UV_GAM_RANGE_TYPE_NV_MAILBOX	4 /* NVMDIMM mailbox */
#घोषणा UV_GAM_RANGE_TYPE_HOLE		5 /* Unused address range */
#घोषणा UV_GAM_RANGE_TYPE_MAX		6

/* The काष्ठाure stores PA bits 56:26, क्रम 64MB granularity */
#घोषणा UV_GAM_RANGE_SHFT		26		/* 64MB */

काष्ठा uv_gam_range_entry अणु
	अक्षर	type;		/* Entry type: GAM_RANGE_TYPE_UNUSED, etc. */
	अक्षर	unused1;
	u16	nasid;		/* HNasid */
	u16	sockid;		/* Socket ID, high bits of APIC ID */
	u16	pnode;		/* Index to MMR and GRU spaces */
	u32	unused2;
	u32	limit;		/* PA bits 56:26 (UV_GAM_RANGE_SHFT) */
पूर्ण;

#घोषणा	UV_AT_SIZE	8	/* 7 अक्षरacter arch type + शून्य अक्षर */
काष्ठा uv_arch_type_entry अणु
	अक्षर	archtype[UV_AT_SIZE];
पूर्ण;

#घोषणा	UV_SYSTAB_SIG			"UVST"
#घोषणा	UV_SYSTAB_VERSION_1		1	/* UV2/3 BIOS version */
#घोषणा	UV_SYSTAB_VERSION_UV4		0x400	/* UV4 BIOS base version */
#घोषणा	UV_SYSTAB_VERSION_UV4_1		0x401	/* + gpa_shअगरt */
#घोषणा	UV_SYSTAB_VERSION_UV4_2		0x402	/* + TYPE_NVRAM/WINDOW/MBOX */
#घोषणा	UV_SYSTAB_VERSION_UV4_3		0x403	/* - GAM Range PXM Value */
#घोषणा	UV_SYSTAB_VERSION_UV4_LATEST	UV_SYSTAB_VERSION_UV4_3

#घोषणा	UV_SYSTAB_VERSION_UV5		0x500	/* UV5 GAM base version */
#घोषणा	UV_SYSTAB_VERSION_UV5_LATEST	UV_SYSTAB_VERSION_UV5

#घोषणा	UV_SYSTAB_TYPE_UNUSED		0	/* End of table (offset == 0) */
#घोषणा	UV_SYSTAB_TYPE_GAM_PARAMS	1	/* GAM PARAM conversions */
#घोषणा	UV_SYSTAB_TYPE_GAM_RNG_TBL	2	/* GAM entry table */
#घोषणा	UV_SYSTAB_TYPE_ARCH_TYPE	3	/* UV arch type */
#घोषणा	UV_SYSTAB_TYPE_MAX		4

/*
 * The UV प्रणाली table describes specअगरic firmware
 * capabilities available to the Linux kernel at runसमय.
 */
काष्ठा uv_systab अणु
	अक्षर signature[4];	/* must be UV_SYSTAB_SIG */
	u32 revision;		/* distinguish dअगरferent firmware revs */
	u64 function;		/* BIOS runसमय callback function ptr */
	u32 size;		/* systab size (starting with _VERSION_UV4) */
	काष्ठा अणु
		u32 type:8;	/* type of entry */
		u32 offset:24;	/* byte offset from काष्ठा start to entry */
	पूर्ण entry[1];		/* additional entries follow */
पूर्ण;
बाह्य काष्ठा uv_systab *uv_systab;

#घोषणा UV_BIOS_MAXSTRING	      128
काष्ठा uv_bios_hub_info अणु
	अचिन्हित पूर्णांक id;
	जोड़ अणु
		काष्ठा अणु
			अचिन्हित दीर्घ दीर्घ this_part:1;
			अचिन्हित दीर्घ दीर्घ is_shared:1;
			अचिन्हित दीर्घ दीर्घ is_disabled:1;
		पूर्ण fields;
		काष्ठा अणु
			अचिन्हित दीर्घ दीर्घ flags;
			अचिन्हित दीर्घ दीर्घ reserved;
		पूर्ण b;
	पूर्ण f;
	अक्षर name[UV_BIOS_MAXSTRING];
	अक्षर location[UV_BIOS_MAXSTRING];
	अचिन्हित पूर्णांक ports;
पूर्ण;

काष्ठा uv_bios_port_info अणु
	अचिन्हित पूर्णांक port;
	अचिन्हित पूर्णांक conn_id;
	अचिन्हित पूर्णांक conn_port;
पूर्ण;

/* (... end of definitions from UV BIOS ...) */

क्रमागत अणु
	BIOS_FREQ_BASE_PLATFORM = 0,
	BIOS_FREQ_BASE_INTERVAL_TIMER = 1,
	BIOS_FREQ_BASE_REALTIME_CLOCK = 2
पूर्ण;

जोड़ partition_info_u अणु
	u64	val;
	काष्ठा अणु
		u64	hub_version	:  8,
			partition_id	: 16,
			coherence_id	: 16,
			region_size	: 24;
	पूर्ण;
पूर्ण;

क्रमागत uv_memprotect अणु
	UV_MEMPROT_RESTRICT_ACCESS,
	UV_MEMPROT_ALLOW_AMO,
	UV_MEMPROT_ALLOW_RW
पूर्ण;

बाह्य s64 uv_bios_get_sn_info(पूर्णांक, पूर्णांक *, दीर्घ *, दीर्घ *, दीर्घ *, दीर्घ *);
बाह्य s64 uv_bios_freq_base(u64, u64 *);
बाह्य पूर्णांक uv_bios_mq_watchlist_alloc(अचिन्हित दीर्घ, अचिन्हित पूर्णांक,
					अचिन्हित दीर्घ *);
बाह्य पूर्णांक uv_bios_mq_watchlist_मुक्त(पूर्णांक, पूर्णांक);
बाह्य s64 uv_bios_change_memprotect(u64, u64, क्रमागत uv_memprotect);
बाह्य s64 uv_bios_reserved_page_pa(u64, u64 *, u64 *, u64 *);
बाह्य पूर्णांक uv_bios_set_legacy_vga_target(bool decode, पूर्णांक करोमुख्य, पूर्णांक bus);

बाह्य s64 uv_bios_get_master_nasid(u64 sz, u64 *nasid);
बाह्य s64 uv_bios_get_heapsize(u64 nasid, u64 sz, u64 *heap_sz);
बाह्य s64 uv_bios_install_heap(u64 nasid, u64 sz, u64 *heap);
बाह्य s64 uv_bios_obj_count(u64 nasid, u64 sz, u64 *objcnt);
बाह्य s64 uv_bios_क्रमागत_objs(u64 nasid, u64 sz, u64 *objbuf);
बाह्य s64 uv_bios_क्रमागत_ports(u64 nasid, u64 obj_id, u64 sz, u64 *portbuf);
बाह्य s64 uv_bios_get_geoinfo(u64 nasid, u64 sz, u64 *geo);
बाह्य s64 uv_bios_get_pci_topology(u64 sz, u64 *buf);

बाह्य पूर्णांक uv_bios_init(व्योम);
बाह्य अचिन्हित दीर्घ get_uv_systab_phys(bool msg);

बाह्य अचिन्हित दीर्घ sn_rtc_cycles_per_second;
बाह्य पूर्णांक uv_type;
बाह्य दीर्घ sn_partition_id;
बाह्य दीर्घ sn_coherency_id;
बाह्य दीर्घ sn_region_size;
बाह्य दीर्घ प्रणाली_serial_number;
बाह्य sमाप_प्रकार uv_get_archtype(अक्षर *buf, पूर्णांक len);
बाह्य पूर्णांक uv_get_hubless_प्रणाली(व्योम);

बाह्य काष्ठा kobject *sgi_uv_kobj;	/* /sys/firmware/sgi_uv */

/*
 * EFI runसमय lock; cf. firmware/efi/runसमय-wrappers.c क्रम details
 */
बाह्य काष्ठा semaphore __efi_uv_runसमय_lock;

#पूर्ण_अगर /* _ASM_X86_UV_BIOS_H */
