<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __ASM_SPINLOCK_TYPES_H
#घोषणा __ASM_SPINLOCK_TYPES_H

प्रकार काष्ठा अणु
	अस्थिर अचिन्हित पूर्णांक slock;
पूर्ण arch_spinlock_t;

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED__	0
#घोषणा __ARCH_SPIN_LOCK_LOCKED__	1

#घोषणा __ARCH_SPIN_LOCK_UNLOCKED	अणु __ARCH_SPIN_LOCK_UNLOCKED__ पूर्ण
#घोषणा __ARCH_SPIN_LOCK_LOCKED		अणु __ARCH_SPIN_LOCK_LOCKED__ पूर्ण

/*
 * Unlocked     : 0x0100_0000
 * Read lock(s) : 0x00FF_FFFF to 0x01  (Multiple Readers decrement it)
 * Write lock   : 0x0, but only अगर prior value is "unlocked" 0x0100_0000
 */
प्रकार काष्ठा अणु
	अस्थिर अचिन्हित पूर्णांक	counter;
#अगर_अघोषित CONFIG_ARC_HAS_LLSC
	arch_spinlock_t		lock_mutex;
#पूर्ण_अगर
पूर्ण arch_rwlock_t;

#घोषणा __ARCH_RW_LOCK_UNLOCKED__	0x01000000
#घोषणा __ARCH_RW_LOCK_UNLOCKED		अणु .counter = __ARCH_RW_LOCK_UNLOCKED__ पूर्ण

#पूर्ण_अगर
