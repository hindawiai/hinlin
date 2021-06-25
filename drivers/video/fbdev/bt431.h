<शैली गुरु>
/*
 *	linux/drivers/video/bt431.h
 *
 *	Copyright 2003  Thiemo Seufer <seufer@csv.ica.uni-stuttgart.de>
 *	Copyright 2016  Maciej W. Rozycki <macro@linux-mips.org>
 *
 *	This file is subject to the terms and conditions of the GNU General
 *	Public License. See the file COPYING in the मुख्य directory of this
 *	archive क्रम more details.
 */
#समावेश <linux/types.h>

#घोषणा BT431_CURSOR_SIZE	64

/*
 * Bt431 cursor generator रेजिस्टरs, 32-bit aligned.
 * Two twin Bt431 are used on the DECstation's PMAG-AA.
 */
काष्ठा bt431_regs अणु
	अस्थिर u16 addr_lo;
	u16 pad0;
	अस्थिर u16 addr_hi;
	u16 pad1;
	अस्थिर u16 addr_cmap;
	u16 pad2;
	अस्थिर u16 addr_reg;
	u16 pad3;
पूर्ण;

अटल अंतरभूत u16 bt431_set_value(u8 val)
अणु
	वापस ((val << 8) | (val & 0xff)) & 0xffff;
पूर्ण

अटल अंतरभूत u8 bt431_get_value(u16 val)
अणु
	वापस val & 0xff;
पूर्ण

/*
 * Additional रेजिस्टरs addressed indirectly.
 */
#घोषणा BT431_REG_CMD		0x0000
#घोषणा BT431_REG_CXLO		0x0001
#घोषणा BT431_REG_CXHI		0x0002
#घोषणा BT431_REG_CYLO		0x0003
#घोषणा BT431_REG_CYHI		0x0004
#घोषणा BT431_REG_WXLO		0x0005
#घोषणा BT431_REG_WXHI		0x0006
#घोषणा BT431_REG_WYLO		0x0007
#घोषणा BT431_REG_WYHI		0x0008
#घोषणा BT431_REG_WWLO		0x0009
#घोषणा BT431_REG_WWHI		0x000a
#घोषणा BT431_REG_WHLO		0x000b
#घोषणा BT431_REG_WHHI		0x000c

#घोषणा BT431_REG_CRAM_BASE	0x0000
#घोषणा BT431_REG_CRAM_END	0x01ff

/*
 * Command रेजिस्टर.
 */
#घोषणा BT431_CMD_CURS_ENABLE	0x40
#घोषणा BT431_CMD_XHAIR_ENABLE	0x20
#घोषणा BT431_CMD_OR_CURSORS	0x10
#घोषणा BT431_CMD_XOR_CURSORS	0x00
#घोषणा BT431_CMD_1_1_MUX	0x00
#घोषणा BT431_CMD_4_1_MUX	0x04
#घोषणा BT431_CMD_5_1_MUX	0x08
#घोषणा BT431_CMD_xxx_MUX	0x0c
#घोषणा BT431_CMD_THICK_1	0x00
#घोषणा BT431_CMD_THICK_3	0x01
#घोषणा BT431_CMD_THICK_5	0x02
#घोषणा BT431_CMD_THICK_7	0x03

अटल अंतरभूत व्योम bt431_select_reg(काष्ठा bt431_regs *regs, पूर्णांक ir)
अणु
	/*
	 * The compiler splits the ग_लिखो in two bytes without these
	 * helper variables.
	 */
	अस्थिर u16 *lo = &(regs->addr_lo);
	अस्थिर u16 *hi = &(regs->addr_hi);

	mb();
	*lo = bt431_set_value(ir & 0xff);
	wmb();
	*hi = bt431_set_value((ir >> 8) & 0xff);
पूर्ण

/* Autoincrement पढ़ो/ग_लिखो. */
अटल अंतरभूत u8 bt431_पढ़ो_reg_inc(काष्ठा bt431_regs *regs)
अणु
	/*
	 * The compiler splits the ग_लिखो in two bytes without the
	 * helper variable.
	 */
	अस्थिर u16 *r = &(regs->addr_reg);

	mb();
	वापस bt431_get_value(*r);
पूर्ण

अटल अंतरभूत व्योम bt431_ग_लिखो_reg_inc(काष्ठा bt431_regs *regs, u8 value)
अणु
	/*
	 * The compiler splits the ग_लिखो in two bytes without the
	 * helper variable.
	 */
	अस्थिर u16 *r = &(regs->addr_reg);

	mb();
	*r = bt431_set_value(value);
पूर्ण

अटल अंतरभूत u8 bt431_पढ़ो_reg(काष्ठा bt431_regs *regs, पूर्णांक ir)
अणु
	bt431_select_reg(regs, ir);
	वापस bt431_पढ़ो_reg_inc(regs);
पूर्ण

अटल अंतरभूत व्योम bt431_ग_लिखो_reg(काष्ठा bt431_regs *regs, पूर्णांक ir, u8 value)
अणु
	bt431_select_reg(regs, ir);
	bt431_ग_लिखो_reg_inc(regs, value);
पूर्ण

/* Autoincremented पढ़ो/ग_लिखो क्रम the cursor map. */
अटल अंतरभूत u16 bt431_पढ़ो_cmap_inc(काष्ठा bt431_regs *regs)
अणु
	/*
	 * The compiler splits the ग_लिखो in two bytes without the
	 * helper variable.
	 */
	अस्थिर u16 *r = &(regs->addr_cmap);

	mb();
	वापस *r;
पूर्ण

अटल अंतरभूत व्योम bt431_ग_लिखो_cmap_inc(काष्ठा bt431_regs *regs, u16 value)
अणु
	/*
	 * The compiler splits the ग_लिखो in two bytes without the
	 * helper variable.
	 */
	अस्थिर u16 *r = &(regs->addr_cmap);

	mb();
	*r = value;
पूर्ण

अटल अंतरभूत u16 bt431_पढ़ो_cmap(काष्ठा bt431_regs *regs, पूर्णांक cr)
अणु
	bt431_select_reg(regs, cr);
	वापस bt431_पढ़ो_cmap_inc(regs);
पूर्ण

अटल अंतरभूत व्योम bt431_ग_लिखो_cmap(काष्ठा bt431_regs *regs, पूर्णांक cr, u16 value)
अणु
	bt431_select_reg(regs, cr);
	bt431_ग_लिखो_cmap_inc(regs, value);
पूर्ण

अटल अंतरभूत व्योम bt431_enable_cursor(काष्ठा bt431_regs *regs)
अणु
	bt431_ग_लिखो_reg(regs, BT431_REG_CMD,
			BT431_CMD_CURS_ENABLE | BT431_CMD_OR_CURSORS
			| BT431_CMD_4_1_MUX | BT431_CMD_THICK_1);
पूर्ण

अटल अंतरभूत व्योम bt431_erase_cursor(काष्ठा bt431_regs *regs)
अणु
	bt431_ग_लिखो_reg(regs, BT431_REG_CMD, BT431_CMD_4_1_MUX);
पूर्ण

अटल अंतरभूत व्योम bt431_position_cursor(काष्ठा bt431_regs *regs, u16 x, u16 y)
अणु
	/*
	 * Magic from the MACH sources.
	 *
	 * Cx = x + D + H - P
	 *  P = 37 अगर 1:1, 52 अगर 4:1, 57 अगर 5:1
	 *  D = pixel skew between outdata and बाह्यal data
	 *  H = pixels between HSYNCH falling and active video
	 *
	 * Cy = y + V - 32
	 *  V = scanlines between HSYNCH falling, two or more
	 *      घड़ीs after VSYNCH falling, and active video
	 */
	x += 412 - 52;
	y += 68 - 32;

	/* Use स्वतःincrement. */
	bt431_select_reg(regs, BT431_REG_CXLO);
	bt431_ग_लिखो_reg_inc(regs, x & 0xff); /* BT431_REG_CXLO */
	bt431_ग_लिखो_reg_inc(regs, (x >> 8) & 0x0f); /* BT431_REG_CXHI */
	bt431_ग_लिखो_reg_inc(regs, y & 0xff); /* BT431_REG_CYLO */
	bt431_ग_लिखो_reg_inc(regs, (y >> 8) & 0x0f); /* BT431_REG_CYHI */
पूर्ण

अटल अंतरभूत व्योम bt431_set_cursor(काष्ठा bt431_regs *regs,
				    स्थिर अक्षर *data, स्थिर अक्षर *mask,
				    u16 rop, u16 width, u16 height)
अणु
	u16 x, y;
	पूर्णांक i;

	i = 0;
	width = DIV_ROUND_UP(width, 8);
	bt431_select_reg(regs, BT431_REG_CRAM_BASE);
	क्रम (y = 0; y < BT431_CURSOR_SIZE; y++)
		क्रम (x = 0; x < BT431_CURSOR_SIZE / 8; x++) अणु
			u16 val = 0;

			अगर (y < height && x < width) अणु
				val = mask[i];
				अगर (rop == ROP_XOR)
					val = (val << 8) | (val ^ data[i]);
				अन्यथा
					val = (val << 8) | (val & data[i]);
				i++;
			पूर्ण
			bt431_ग_लिखो_cmap_inc(regs, val);
		पूर्ण
पूर्ण

अटल अंतरभूत व्योम bt431_init_cursor(काष्ठा bt431_regs *regs)
अणु
	/* no crosshair winकरोw */
	bt431_select_reg(regs, BT431_REG_WXLO);
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WXLO */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WXHI */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WYLO */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WYHI */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WWLO */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WWHI */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WHLO */
	bt431_ग_लिखो_reg_inc(regs, 0x00); /* BT431_REG_WHHI */
पूर्ण
