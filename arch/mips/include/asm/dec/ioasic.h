<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *	include/यंत्र-mips/dec/ioasic.h
 *
 *	DEC I/O ASIC access operations.
 *
 *	Copyright (C) 2000, 2002, 2003  Maciej W. Rozycki
 */

#अगर_अघोषित __ASM_DEC_IOASIC_H
#घोषणा __ASM_DEC_IOASIC_H

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>

बाह्य spinlock_t ioasic_ssr_lock;

बाह्य अस्थिर u32 *ioasic_base;

अटल अंतरभूत व्योम ioasic_ग_लिखो(अचिन्हित पूर्णांक reg, u32 v)
अणु
	ioasic_base[reg / 4] = v;
पूर्ण

अटल अंतरभूत u32 ioasic_पढ़ो(अचिन्हित पूर्णांक reg)
अणु
	वापस ioasic_base[reg / 4];
पूर्ण

बाह्य व्योम init_ioasic_irqs(पूर्णांक base);

बाह्य पूर्णांक dec_ioasic_घड़ीsource_init(व्योम);

#पूर्ण_अगर /* __ASM_DEC_IOASIC_H */
