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
 * Copyright (C) 2010-2011 Jonas Bonn <jonas@southpole.se>
 */

#अगर_अघोषित __ASM_OPENRISC_SPR_H
#घोषणा __ASM_OPENRISC_SPR_H

#घोषणा mtspr(_spr, _val) __यंत्र__ __अस्थिर__ (		\
	"l.mtspr r0,%1,%0"					\
	: : "K" (_spr), "r" (_val))
#घोषणा mtspr_off(_spr, _off, _val) __यंत्र__ __अस्थिर__ (	\
	"l.mtspr %0,%1,%2"					\
	: : "r" (_off), "r" (_val), "K" (_spr))

अटल अंतरभूत अचिन्हित दीर्घ mfspr(अचिन्हित दीर्घ add)
अणु
	अचिन्हित दीर्घ ret;
	__यंत्र__ __अस्थिर__ ("l.mfspr %0,r0,%1" : "=r" (ret) : "K" (add));
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ mfspr_off(अचिन्हित दीर्घ add, अचिन्हित दीर्घ offset)
अणु
	अचिन्हित दीर्घ ret;
	__यंत्र__ __अस्थिर__ ("l.mfspr %0,%1,%2" : "=r" (ret)
						 : "r" (offset), "K" (add));
	वापस ret;
पूर्ण

#पूर्ण_अगर
