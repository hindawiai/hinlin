<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Contains routines needed to support swiotlb क्रम ppc.
 *
 * Copyright (C) 2009-2010 Freescale Semiconductor, Inc.
 * Author: Becky Bruce
 */
#समावेश <linux/memblock.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/swiotlb.h>

अचिन्हित पूर्णांक ppc_swiotlb_enable;

व्योम __init swiotlb_detect_4g(व्योम)
अणु
	अगर ((memblock_end_of_DRAM() - 1) > 0xffffffff)
		ppc_swiotlb_enable = 1;
पूर्ण

अटल पूर्णांक __init check_swiotlb_enabled(व्योम)
अणु
	अगर (ppc_swiotlb_enable)
		swiotlb_prपूर्णांक_info();
	अन्यथा
		swiotlb_निकास();

	वापस 0;
पूर्ण
subsys_initcall(check_swiotlb_enabled);
