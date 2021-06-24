<शैली गुरु>
/*
 *	linux/drivers/video/bt455.h
 *
 *	Copyright 2003  Thiemo Seufer <seufer@csv.ica.uni-stuttgart.de>
 *	Copyright 2016  Maciej W. Rozycki <macro@linux-mips.org>
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License. See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 */
#समावेश <linux/types.h>

/*
 * Bt455 byte-wide रेजिस्टरs, 32-bit aligned.
 */
काष्ठा bt455_regs अणु
	अस्थिर u8 addr_cmap;
	u8 pad0[3];
	अस्थिर u8 addr_cmap_data;
	u8 pad1[3];
	अस्थिर u8 addr_clr;
	u8 pad2[3];
	अस्थिर u8 addr_ovly;
	u8 pad3[3];
पूर्ण;

अटल अंतरभूत व्योम bt455_select_reg(काष्ठा bt455_regs *regs, पूर्णांक ir)
अणु
	mb();
	regs->addr_cmap = ir & 0x0f;
पूर्ण

अटल अंतरभूत व्योम bt455_reset_reg(काष्ठा bt455_regs *regs)
अणु
	mb();
	regs->addr_clr = 0;
पूर्ण

/*
 * Read/ग_लिखो to a Bt455 color map रेजिस्टर.
 */
अटल अंतरभूत व्योम bt455_पढ़ो_cmap_next(काष्ठा bt455_regs *regs, u8 *grey)
अणु
	mb();
	regs->addr_cmap_data;
	rmb();
	*grey = regs->addr_cmap_data & 0xf;
	rmb();
	regs->addr_cmap_data;
पूर्ण

अटल अंतरभूत व्योम bt455_ग_लिखो_cmap_next(काष्ठा bt455_regs *regs, u8 grey)
अणु
	wmb();
	regs->addr_cmap_data = 0x0;
	wmb();
	regs->addr_cmap_data = grey & 0xf;
	wmb();
	regs->addr_cmap_data = 0x0;
पूर्ण

अटल अंतरभूत व्योम bt455_ग_लिखो_ovly_next(काष्ठा bt455_regs *regs, u8 grey)
अणु
	wmb();
	regs->addr_ovly = 0x0;
	wmb();
	regs->addr_ovly = grey & 0xf;
	wmb();
	regs->addr_ovly = 0x0;
पूर्ण

अटल अंतरभूत व्योम bt455_पढ़ो_cmap_entry(काष्ठा bt455_regs *regs,
					 पूर्णांक cr, u8 *grey)
अणु
	bt455_select_reg(regs, cr);
	bt455_पढ़ो_cmap_next(regs, grey);
पूर्ण

अटल अंतरभूत व्योम bt455_ग_लिखो_cmap_entry(काष्ठा bt455_regs *regs,
					  पूर्णांक cr, u8 grey)
अणु
	bt455_select_reg(regs, cr);
	bt455_ग_लिखो_cmap_next(regs, grey);
पूर्ण

अटल अंतरभूत व्योम bt455_ग_लिखो_ovly_entry(काष्ठा bt455_regs *regs, u8 grey)
अणु
	bt455_reset_reg(regs);
	bt455_ग_लिखो_ovly_next(regs, grey);
पूर्ण
