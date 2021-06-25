<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_घोषित  __LINUX_COMPILER_VERSION_H
#त्रुटि "Please do not include <linux/compiler-version.h>. This is done by the build system."
#पूर्ण_अगर
#घोषणा __LINUX_COMPILER_VERSION_H

/*
 * This header exists to क्रमce full rebuild when the compiler is upgraded.
 *
 * When fixdep scans this, it will find this string "CONFIG_CC_VERSION_TEXT"
 * and add dependency on include/config/CC_VERSION_TEXT, which is touched
 * by Kconfig when the version string from the compiler changes.
 */
