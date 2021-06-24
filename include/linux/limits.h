<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LIMITS_H
#घोषणा _LINUX_LIMITS_H

#समावेश <uapi/linux/सीमा.स>
#समावेश <linux/types.h>
#समावेश <vdso/सीमा.स>

#घोषणा SIZE_MAX	(~(माप_प्रकार)0)
#घोषणा PHYS_ADDR_MAX	(~(phys_addr_t)0)

#घोषणा U8_MAX		((u8)~0U)
#घोषणा S8_MAX		((s8)(U8_MAX >> 1))
#घोषणा S8_MIN		((s8)(-S8_MAX - 1))
#घोषणा U16_MAX		((u16)~0U)
#घोषणा S16_MAX		((s16)(U16_MAX >> 1))
#घोषणा S16_MIN		((s16)(-S16_MAX - 1))
#घोषणा U32_MAX		((u32)~0U)
#घोषणा U32_MIN		((u32)0)
#घोषणा S32_MAX		((s32)(U32_MAX >> 1))
#घोषणा S32_MIN		((s32)(-S32_MAX - 1))
#घोषणा U64_MAX		((u64)~0ULL)
#घोषणा S64_MAX		((s64)(U64_MAX >> 1))
#घोषणा S64_MIN		((s64)(-S64_MAX - 1))

#पूर्ण_अगर /* _LINUX_LIMITS_H */
