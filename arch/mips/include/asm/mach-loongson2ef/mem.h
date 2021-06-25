<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin <wuzhangjin@gmail.com>
 */

#अगर_अघोषित __ASM_MACH_LOONGSON2EF_MEM_H
#घोषणा __ASM_MACH_LOONGSON2EF_MEM_H

/*
 * high memory space
 *
 * in loongson2e, starts from 512M
 * in loongson2f, starts from 2G 256M
 */
#अगर_घोषित CONFIG_CPU_LOONGSON2E
#घोषणा LOONGSON_HIGHMEM_START	0x20000000
#अन्यथा
#घोषणा LOONGSON_HIGHMEM_START	0x90000000
#पूर्ण_अगर

/*
 * the peripheral रेजिस्टरs(MMIO):
 *
 * On the Lemote Loongson 2e प्रणाली, reside between 0x1000:0000 and 0x2000:0000.
 * On the Lemote Loongson 2f प्रणाली, reside between 0x1000:0000 and 0x8000:0000.
 */

#घोषणा LOONGSON_MMIO_MEM_START 0x10000000

#अगर_घोषित CONFIG_CPU_LOONGSON2E
#घोषणा LOONGSON_MMIO_MEM_END	0x20000000
#अन्यथा
#घोषणा LOONGSON_MMIO_MEM_END	0x80000000
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_MACH_LOONGSON2EF_MEM_H */
