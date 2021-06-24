<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/glue.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *  Copyright (C) 2000-2002 Deep Blue Solutions Ltd.
 *
 *  This file provides the glue to stick the processor-specअगरic bits
 *  पूर्णांकo the kernel in an efficient manner.  The idea is to use branches
 *  when we're only targeting one class of TLB, or indirect calls
 *  when we're targeting multiple classes of TLBs.
 */
#अगर_घोषित __KERNEL__

#अगर_घोषित __STDC__
#घोषणा ____glue(name,fn)	name##fn
#अन्यथा
#घोषणा ____glue(name,fn)	name/**/fn
#पूर्ण_अगर
#घोषणा __glue(name,fn)		____glue(name,fn)

#पूर्ण_अगर
