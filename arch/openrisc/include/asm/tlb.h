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

#अगर_अघोषित __ASM_OPENRISC_TLB_H__
#घोषणा __ASM_OPENRISC_TLB_H__

/*
 * OpenRISC करोesn't have an efficient flush_tlb_range() so use flush_tlb_mm()
 * क्रम everything.
 */

#समावेश <linux/pagemap.h>
#समावेश <यंत्र-generic/tlb.h>

#पूर्ण_अगर /* __ASM_OPENRISC_TLB_H__ */
