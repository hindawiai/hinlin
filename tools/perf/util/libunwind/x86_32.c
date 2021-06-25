<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file setups defines to compile arch specअगरic binary from the
 * generic one.
 *
 * The function 'LIBUNWIND__ARCH_REG_ID' name is set according to arch
 * name and the definition of this function is included directly from
 * 'arch/x86/util/unwind-libunwind.c', to make sure that this function
 * is defined no matter what arch the host is.
 *
 * Finally, the arch specअगरic unwind methods are exported which will
 * be asचिन्हित to each x86 thपढ़ो.
 */

#घोषणा REMOTE_UNWIND_LIBUNWIND

/* Define arch specअगरic functions & regs क्रम libunwind, should be
 * defined beक्रमe including "unwind.h"
 */
#घोषणा LIBUNWIND__ARCH_REG_ID(regnum) libunwind__x86_reg_id(regnum)
#घोषणा LIBUNWIND__ARCH_REG_IP PERF_REG_X86_IP
#घोषणा LIBUNWIND__ARCH_REG_SP PERF_REG_X86_SP

#समावेश "unwind.h"
#समावेश "libunwind-x86.h"
#समावेश <../../../../arch/x86/include/uapi/यंत्र/perf_regs.h>

/* HAVE_ARCH_X86_64_SUPPORT is used in'arch/x86/util/unwind-libunwind.c'
 * क्रम x86_32, we undef it to compile code क्रम x86_32 only.
 */
#अघोषित HAVE_ARCH_X86_64_SUPPORT
#समावेश "../../arch/x86/util/unwind-libunwind.c"

/* Explicitly define NO_LIBUNWIND_DEBUG_FRAME, because non-ARM has no
 * dwarf_find_debug_frame() function.
 */
#अगर_अघोषित NO_LIBUNWIND_DEBUG_FRAME
#घोषणा NO_LIBUNWIND_DEBUG_FRAME
#पूर्ण_अगर
#समावेश "util/unwind-libunwind-local.c"

काष्ठा unwind_libunwind_ops *
x86_32_unwind_libunwind_ops = &_unwind_libunwind_ops;
