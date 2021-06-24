<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Export of symbols defined in assembly files and/or libgcc.
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/dma-mapping.h>
#समावेश <यंत्र/hexagon_vm.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>

/* Additional functions */
EXPORT_SYMBOL(__clear_user_hexagon);
EXPORT_SYMBOL(raw_copy_from_user);
EXPORT_SYMBOL(raw_copy_to_user);
EXPORT_SYMBOL(iounmap);
EXPORT_SYMBOL(__strnlen_user);
EXPORT_SYMBOL(__vmgetie);
EXPORT_SYMBOL(__vmsetie);
EXPORT_SYMBOL(__vmyield);
EXPORT_SYMBOL(empty_zero_page);
EXPORT_SYMBOL(ioremap);
EXPORT_SYMBOL(स_नकल);
EXPORT_SYMBOL(स_रखो);

/* Additional variables */
EXPORT_SYMBOL(__phys_offset);
EXPORT_SYMBOL(_dflt_cache_att);

#घोषणा DECLARE_EXPORT(name)     \
	बाह्य व्योम name(व्योम); EXPORT_SYMBOL(name)

/* Symbols found in libgcc that assorted kernel modules need */
DECLARE_EXPORT(__hexagon_स_नकल_likely_aligned_min32bytes_mult8bytes);

/* Additional functions */
DECLARE_EXPORT(__hexagon_भागsi3);
DECLARE_EXPORT(__hexagon_modsi3);
DECLARE_EXPORT(__hexagon_uभागsi3);
DECLARE_EXPORT(__hexagon_umodsi3);
DECLARE_EXPORT(csum_tcpudp_magic);
