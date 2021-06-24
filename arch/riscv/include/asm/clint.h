<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 Google, Inc
 */

#अगर_अघोषित _ASM_RISCV_CLINT_H
#घोषणा _ASM_RISCV_CLINT_H

#समावेश <linux/types.h>
#समावेश <यंत्र/mmपन.स>

#अगर_घोषित CONFIG_RISCV_M_MODE
/*
 * This lives in the CLINT driver, but is accessed directly by समयx.h to aव्योम
 * any overhead when accessing the MMIO समयr.
 *
 * The ISA defines mसमय as a 64-bit memory-mapped रेजिस्टर that increments at
 * a स्थिरant frequency, but it करोesn't define some other स्थिरraपूर्णांकs we depend
 * on (most notably ordering स्थिरraपूर्णांकs, but also some simpler stuff like the
 * memory layout).  Thus, this is called "clint_time_val" instead of something
 * like "riscv_mtime", to signअगरy that these non-ISA assumptions must hold.
 */
बाह्य u64 __iomem *clपूर्णांक_समय_val;
#पूर्ण_अगर

#पूर्ण_अगर
