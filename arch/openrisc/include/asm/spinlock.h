<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * OpenRISC Linux
 *
 * Linux architectural port borrowing liberally from similar works of
 * others.  All original copyrights apply as per the original source
 * declaration.
 *
 * OpenRISC implementation:
 * Copyright (C) 2003 Matjaz Breskvar <phoenix@bsemi.com>
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 * et al.
 */

#अगर_अघोषित __ASM_OPENRISC_SPINLOCK_H
#घोषणा __ASM_OPENRISC_SPINLOCK_H

#समावेश <यंत्र/qspinlock.h>

#समावेश <यंत्र/qrwlock.h>

#घोषणा arch_पढ़ो_lock_flags(lock, flags) arch_पढ़ो_lock(lock)
#घोषणा arch_ग_लिखो_lock_flags(lock, flags) arch_ग_लिखो_lock(lock)

#घोषणा arch_spin_relax(lock)	cpu_relax()
#घोषणा arch_पढ़ो_relax(lock)	cpu_relax()
#घोषणा arch_ग_लिखो_relax(lock)	cpu_relax()


#पूर्ण_अगर
