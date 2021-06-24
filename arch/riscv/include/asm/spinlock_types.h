<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of Calअगरornia
 */

#अगर_अघोषित _ASM_RISCV_SPINLOCK_TYPES_H
#घोषणा _ASM_RISCV_SPINLOCK_TYPES_H

#अगर_अघोषित __LINUX_SPINLOCK_TYPES_H
# error "please don't include this file directly"
#पूर्ण_अगर

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित पूर्णांक lock;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED	अणु 0 पूर्ण

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित पूर्णांक lock;
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED		अणु 0 पूर्ण

#पूर्ण_अगर /* _ASM_RISCV_SPINLOCK_TYPES_H */
