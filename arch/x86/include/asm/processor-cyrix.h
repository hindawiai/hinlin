<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NSC/Cyrix CPU indexed रेजिस्टर access. Must be अंतरभूतd instead of
 * macros to ensure correct access ordering
 * Access order is always 0x22 (=offset), 0x23 (=value)
 */

अटल अंतरभूत u8 getCx86(u8 reg)
अणु
	outb(reg, 0x22);
	वापस inb(0x23);
पूर्ण

अटल अंतरभूत व्योम setCx86(u8 reg, u8 data)
अणु
	outb(reg, 0x22);
	outb(data, 0x23);
पूर्ण
