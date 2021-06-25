<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 ARM Limited
 */
#अगर_अघोषित __COMPAT_BARRIER_H
#घोषणा __COMPAT_BARRIER_H

#अगर_अघोषित __ASSEMBLY__
/*
 * Warning: This code is meant to be used with
 * ENABLE_COMPAT_VDSO only.
 */
#अगर_अघोषित ENABLE_COMPAT_VDSO
#त्रुटि This header is meant to be used with ENABLE_COMPAT_VDSO only
#पूर्ण_अगर

#अगर_घोषित dmb
#अघोषित dmb
#पूर्ण_अगर

#घोषणा dmb(option) __यंत्र__ __अस्थिर__ ("dmb " #option : : : "memory")

#अगर __LINUX_ARM_ARCH__ >= 8 && defined(CONFIG_AS_DMB_ISHLD)
#घोषणा aarch32_smp_mb()	dmb(ish)
#घोषणा aarch32_smp_rmb()	dmb(ishld)
#घोषणा aarch32_smp_wmb()	dmb(ishst)
#अन्यथा
#घोषणा aarch32_smp_mb()	dmb(ish)
#घोषणा aarch32_smp_rmb()	aarch32_smp_mb()
#घोषणा aarch32_smp_wmb()	dmb(ishst)
#पूर्ण_अगर


#अघोषित smp_mb
#अघोषित smp_rmb
#अघोषित smp_wmb

#घोषणा smp_mb()	aarch32_smp_mb()
#घोषणा smp_rmb()	aarch32_smp_rmb()
#घोषणा smp_wmb()	aarch32_smp_wmb()

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __COMPAT_BARRIER_H */
