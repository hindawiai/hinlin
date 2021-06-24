<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (C) Copyright 2004, 2005 Cavium Networks
 */

#अगर_अघोषित __OCTEON_BOOT_H__
#घोषणा __OCTEON_BOOT_H__

#समावेश <linux/types.h>

काष्ठा boot_init_vector अणु
	/* First stage address - in ram instead of flash */
	uपूर्णांक64_t code_addr;
	/* Setup code क्रम application, NOT application entry poपूर्णांक */
	uपूर्णांक32_t app_start_func_addr;
	/* k0 is used क्रम global data - needs to be passed to other cores */
	uपूर्णांक32_t k0_val;
	/* Address of boot info block काष्ठाure */
	uपूर्णांक64_t boot_info_addr;
	uपूर्णांक32_t flags;		/* flags */
	uपूर्णांक32_t pad;
पूर्ण;

/* similar to bootloader's linux_app_boot_info but without global data */
काष्ठा linux_app_boot_info अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	uपूर्णांक32_t labi_signature;
	uपूर्णांक32_t start_core0_addr;
	uपूर्णांक32_t avail_coremask;
	uपूर्णांक32_t pci_console_active;
	uपूर्णांक32_t icache_prefetch_disable;
	uपूर्णांक32_t padding;
	uपूर्णांक64_t InitTLBStart_addr;
	uपूर्णांक32_t start_app_addr;
	uपूर्णांक32_t cur_exception_base;
	uपूर्णांक32_t no_mark_निजी_data;
	uपूर्णांक32_t compact_flash_common_base_addr;
	uपूर्णांक32_t compact_flash_attribute_base_addr;
	uपूर्णांक32_t led_display_base_addr;
#अन्यथा
	uपूर्णांक32_t start_core0_addr;
	uपूर्णांक32_t labi_signature;

	uपूर्णांक32_t pci_console_active;
	uपूर्णांक32_t avail_coremask;

	uपूर्णांक32_t padding;
	uपूर्णांक32_t icache_prefetch_disable;

	uपूर्णांक64_t InitTLBStart_addr;

	uपूर्णांक32_t cur_exception_base;
	uपूर्णांक32_t start_app_addr;

	uपूर्णांक32_t compact_flash_common_base_addr;
	uपूर्णांक32_t no_mark_निजी_data;

	uपूर्णांक32_t led_display_base_addr;
	uपूर्णांक32_t compact_flash_attribute_base_addr;
#पूर्ण_अगर
पूर्ण;

/* If not to copy a lot of bootloader's काष्ठाures
   here is only offset of requested member */
#घोषणा AVAIL_COREMASK_OFFSET_IN_LINUX_APP_BOOT_BLOCK	 0x765c

/* hardcoded in bootloader */
#घोषणा	 LABI_ADDR_IN_BOOTLOADER			 0x700

#घोषणा LINUX_APP_BOOT_BLOCK_NAME "linux-app-boot"

#घोषणा LABI_SIGNATURE 0xAABBCC01

/*  from uboot-headers/octeon_mem_map.h */
#घोषणा EXCEPTION_BASE_INCR	(4 * 1024)
			       /* Increment size क्रम exception base addresses (4k minimum) */
#घोषणा EXCEPTION_BASE_BASE	0
#घोषणा BOOTLOADER_PRIV_DATA_BASE	(EXCEPTION_BASE_BASE + 0x800)
#घोषणा BOOTLOADER_BOOT_VECTOR		(BOOTLOADER_PRIV_DATA_BASE)

#पूर्ण_अगर /* __OCTEON_BOOT_H__ */
