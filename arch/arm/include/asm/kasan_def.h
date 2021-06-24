<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  arch/arm/include/यंत्र/kasan_def.h
 *
 *  Copyright (c) 2018 Huawei Technologies Co., Ltd.
 *
 *  Author: Abbott Liu <liuwenliang@huawei.com>
 */

#अगर_अघोषित __ASM_KASAN_DEF_H
#घोषणा __ASM_KASAN_DEF_H

#अगर_घोषित CONFIG_KASAN

/*
 * Define KASAN_SHADOW_OFFSET,KASAN_SHADOW_START and KASAN_SHADOW_END क्रम
 * the Arm kernel address sanitizer. We are "stealing" lowmem (the 4GB
 * addressable by a 32bit architecture) out of the भव address
 * space to use as shaकरोw memory क्रम KASan as follows:
 *
 * +----+ 0xffffffff
 * |    |							\
 * |    | |-> Static kernel image (vmlinux) BSS and page table
 * |    |/
 * +----+ PAGE_OFFSET
 * |    |							\
 * |    | |->  Loadable kernel modules भव address space area
 * |    |/
 * +----+ MODULES_VADDR = KASAN_SHADOW_END
 * |    |						\
 * |    | |-> The shaकरोw area of kernel भव address.
 * |    |/
 * +----+->  TASK_SIZE (start of kernel space) = KASAN_SHADOW_START the
 * |    |\   shaकरोw address of MODULES_VADDR
 * |    | |
 * |    | |
 * |    | |-> The user space area in lowmem. The kernel address
 * |    | |   sanitizer करो not use this space, nor करोes it map it.
 * |    | |
 * |    | |
 * |    | |
 * |    | |
 * |    |/
 * ------ 0
 *
 * 1) KASAN_SHADOW_START
 *   This value begins with the MODULE_VADDR's shaकरोw address. It is the
 *   start of kernel भव space. Since we have modules to load, we need
 *   to cover also that area with shaकरोw memory so we can find memory
 *   bugs in modules.
 *
 * 2) KASAN_SHADOW_END
 *   This value is the 0x100000000's shaकरोw address: the mapping that would
 *   be after the end of the kernel memory at 0xffffffff. It is the end of
 *   kernel address sanitizer shaकरोw area. It is also the start of the
 *   module area.
 *
 * 3) KASAN_SHADOW_OFFSET:
 *   This value is used to map an address to the corresponding shaकरोw
 *   address by the following क्रमmula:
 *
 *	shaकरोw_addr = (address >> 3) + KASAN_SHADOW_OFFSET;
 *
 *  As you would expect, >> 3 is equal to भागiding by 8, meaning each
 *  byte in the shaकरोw memory covers 8 bytes of kernel memory, so one
 *  bit shaकरोw memory per byte of kernel memory is used.
 *
 *  The KASAN_SHADOW_OFFSET is provided in a Kconfig option depending
 *  on the VMSPLIT layout of the प्रणाली: the kernel and userspace can
 *  split up lowmem in dअगरferent ways according to needs, so we calculate
 *  the shaकरोw offset depending on this.
 */

#घोषणा KASAN_SHADOW_SCALE_SHIFT	3
#घोषणा KASAN_SHADOW_OFFSET	_AC(CONFIG_KASAN_SHADOW_OFFSET, UL)
#घोषणा KASAN_SHADOW_END	((UL(1) << (32 - KASAN_SHADOW_SCALE_SHIFT)) \
				 + KASAN_SHADOW_OFFSET)
#घोषणा KASAN_SHADOW_START      ((KASAN_SHADOW_END >> 3) + KASAN_SHADOW_OFFSET)

#पूर्ण_अगर
#पूर्ण_अगर
