<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 * features.h
 *
 * Feature flags, reported by XENVER_get_features.
 *
 * Copyright (c) 2006, Keir Fraser <keir@xensource.com>
 */

#अगर_अघोषित __XEN_PUBLIC_FEATURES_H__
#घोषणा __XEN_PUBLIC_FEATURES_H__

/*
 * If set, the guest करोes not need to ग_लिखो-protect its pagetables, and can
 * update them via direct ग_लिखोs.
 */
#घोषणा XENFEAT_writable_page_tables       0

/*
 * If set, the guest करोes not need to ग_लिखो-protect its segment descriptor
 * tables, and can update them via direct ग_लिखोs.
 */
#घोषणा XENFEAT_writable_descriptor_tables 1

/*
 * If set, translation between the guest's 'pseudo-physical' address space
 * and the host's machine address space are handled by the hypervisor. In this
 * mode the guest करोes not need to perक्रमm phys-to/from-machine translations
 * when perक्रमming page table operations.
 */
#घोषणा XENFEAT_स्वतः_translated_physmap    2

/* If set, the guest is running in supervisor mode (e.g., x86 ring 0). */
#घोषणा XENFEAT_supervisor_mode_kernel     3

/*
 * If set, the guest करोes not need to allocate x86 PAE page directories
 * below 4GB. This flag is usually implied by स्वतः_translated_physmap.
 */
#घोषणा XENFEAT_pae_pgdir_above_4gb        4

/* x86: Does this Xen host support the MMU_PT_UPDATE_PRESERVE_AD hypercall? */
#घोषणा XENFEAT_mmu_pt_update_preserve_ad  5

/* x86: Does this Xen host support the MMU_अणुCLEAR,COPYपूर्ण_PAGE hypercall? */
#घोषणा XENFEAT_highmem_assist             6

/*
 * If set, GNTTABOP_map_grant_ref honors flags to be placed पूर्णांकo guest kernel
 * available pte bits.
 */
#घोषणा XENFEAT_gnttab_map_avail_bits      7

/* x86: Does this Xen host support the HVM callback vector type? */
#घोषणा XENFEAT_hvm_callback_vector        8

/* x86: pvघड़ी algorithm is safe to use on HVM */
#घोषणा XENFEAT_hvm_safe_pvघड़ी           9

/* x86: pirq can be used by HVM guests */
#घोषणा XENFEAT_hvm_pirqs           10

/* operation as Dom0 is supported */
#घोषणा XENFEAT_करोm0                      11

/* Xen also maps grant references at pfn = mfn.
 * This feature flag is deprecated and should not be used.
#घोषणा XENFEAT_grant_map_identity        12
 */

/* Guest can use XENMEMF_vnode to specअगरy भव node क्रम memory op. */
#घोषणा XENFEAT_memory_op_vnode_supported 13

/* arm: Hypervisor supports ARM SMC calling convention. */
#घोषणा XENFEAT_ARM_SMCCC_supported       14

/*
 * x86/PVH: If set, ACPI RSDP can be placed at any address. Otherwise RSDP
 * must be located in lower 1MB, as required by ACPI Specअगरication क्रम IA-PC
 * प्रणालीs.
 * This feature flag is only consulted अगर XEN_ELFNOTE_GUEST_OS contains
 * the "linux" string.
 */
#घोषणा XENFEAT_linux_rsdp_unrestricted   15

/*
 * A direct-mapped (or 1:1 mapped) करोमुख्य is a करोमुख्य क्रम which its
 * local pages have gfn == mfn. If a करोमुख्य is direct-mapped,
 * XENFEAT_direct_mapped is set; otherwise XENFEAT_not_direct_mapped
 * is set.
 *
 * If neither flag is set (e.g. older Xen releases) the assumptions are:
 * - not स्वतः_translated करोमुख्यs (x86 only) are always direct-mapped
 * - on x86, स्वतः_translated करोमुख्यs are not direct-mapped
 * - on ARM, Dom0 is direct-mapped, DomUs are not
 */
#घोषणा XENFEAT_not_direct_mapped         16
#घोषणा XENFEAT_direct_mapped             17

#घोषणा XENFEAT_NR_SUBMAPS 1

#पूर्ण_अगर /* __XEN_PUBLIC_FEATURES_H__ */
