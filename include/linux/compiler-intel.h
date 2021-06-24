<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_COMPILER_TYPES_H
#त्रुटि "Please don't include <linux/compiler-intel.h> directly, include <linux/compiler.h> instead."
#पूर्ण_अगर

#अगर_घोषित __ECC

/* Compiler specअगरic definitions क्रम Intel ECC compiler */

#समावेश <यंत्र/पूर्णांकrinsics.h>

/* Intel ECC compiler करोesn't support gcc specअगरic यंत्र sपंचांगts.
 * It uses पूर्णांकrinsics to करो the equivalent things.
 */

#घोषणा barrier() __memory_barrier()
#घोषणा barrier_data(ptr) barrier()

#घोषणा RELOC_HIDE(ptr, off)					\
  (अणु अचिन्हित दीर्घ __ptr;					\
     __ptr = (अचिन्हित दीर्घ) (ptr);				\
    (typeof(ptr)) (__ptr + (off)); पूर्ण)

/* This should act as an optimization barrier on var.
 * Given that this compiler करोes not have अंतरभूत assembly, a compiler barrier
 * is the best we can करो.
 */
#घोषणा OPTIMIZER_HIDE_VAR(var) barrier()

#पूर्ण_अगर

/* icc has this, but it's called _bswap16 */
#घोषणा __HAVE_BUILTIN_BSWAP16__
#घोषणा __builtin_bswap16 _bswap16
