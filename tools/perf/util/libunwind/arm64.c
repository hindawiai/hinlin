<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file setups defines to compile arch specअगरic binary from the
 * generic one.
 *
 * The function 'LIBUNWIND__ARCH_REG_ID' name is set according to arch
 * name and the definition of this function is included directly from
 * 'arch/arm64/util/unwind-libunwind.c', to make sure that this function
 * is defined no matter what arch the host is.
 *
 * Finally, the arch specअगरic unwind methods are exported which will
 * be asचिन्हित to each arm64 thपढ़ो.
 */

#घोषणा REMOTE_UNWIND_LIBUNWIND

/* Define arch specअगरic functions & regs क्रम libunwind, should be
 * defined beक्रमe including "unwind.h"
 */
#घोषणा LIBUNWIND__ARCH_REG_ID(regnum) libunwind__arm64_reg_id(regnum)
#घोषणा LIBUNWIND__ARCH_REG_IP PERF_REG_ARM64_PC
#घोषणा LIBUNWIND__ARCH_REG_SP PERF_REG_ARM64_SP

#समावेश "unwind.h"
#समावेश "libunwind-aarch64.h"
#समावेश <../../../../arch/arm64/include/uapi/यंत्र/perf_regs.h>
#समावेश "../../arch/arm64/util/unwind-libunwind.c"

/* NO_LIBUNWIND_DEBUG_FRAME is a feature flag क्रम local libunwind,
 * assign NO_LIBUNWIND_DEBUG_FRAME_AARCH64 to it क्रम compiling arm64
 * unwind methods.
 */
#अघोषित NO_LIBUNWIND_DEBUG_FRAME
#अगर_घोषित NO_LIBUNWIND_DEBUG_FRAME_AARCH64
#घोषणा NO_LIBUNWIND_DEBUG_FRAME
#पूर्ण_अगर
#समावेश "util/unwind-libunwind-local.c"

काष्ठा unwind_libunwind_ops *
arm64_unwind_libunwind_ops = &_unwind_libunwind_ops;
