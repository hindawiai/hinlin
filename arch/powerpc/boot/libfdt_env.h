<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ARCH_POWERPC_BOOT_LIBFDT_ENV_H
#घोषणा _ARCH_POWERPC_BOOT_LIBFDT_ENV_H

#समावेश <types.h>
#समावेश <माला.स>

#घोषणा पूर्णांक_उच्च			((पूर्णांक)(~0U>>1))
#घोषणा UINT32_MAX		((u32)~0U)
#घोषणा INT32_MAX		((s32)(UINT32_MAX >> 1))

#समावेश "of.h"

प्रकार अचिन्हित दीर्घ uपूर्णांकptr_t;

प्रकार __be16 fdt16_t;
प्रकार __be32 fdt32_t;
प्रकार __be64 fdt64_t;

#घोषणा fdt16_to_cpu(x)		be16_to_cpu(x)
#घोषणा cpu_to_fdt16(x)		cpu_to_be16(x)
#घोषणा fdt32_to_cpu(x)		be32_to_cpu(x)
#घोषणा cpu_to_fdt32(x)		cpu_to_be32(x)
#घोषणा fdt64_to_cpu(x)		be64_to_cpu(x)
#घोषणा cpu_to_fdt64(x)		cpu_to_be64(x)

#पूर्ण_अगर /* _ARCH_POWERPC_BOOT_LIBFDT_ENV_H */
