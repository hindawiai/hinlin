<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_FBIO_H
#घोषणा __LINUX_FBIO_H

#समावेश <uapi/यंत्र/fbपन.स>

#घोषणा FBIOPUTCMAP_SPARC _IOW('F', 3, काष्ठा fbcmap)
#घोषणा FBIOGETCMAP_SPARC _IOW('F', 4, काष्ठा fbcmap)
/* Addresses on the fd of a cgsix that are mappable */
#घोषणा CG6_FBC    0x70000000
#घोषणा CG6_TEC    0x70001000
#घोषणा CG6_BTREGS 0x70002000
#घोषणा CG6_FHC    0x70004000
#घोषणा CG6_THC    0x70005000
#घोषणा CG6_ROM    0x70006000
#घोषणा CG6_RAM    0x70016000
#घोषणा CG6_DHC    0x80000000

#घोषणा CG3_MMAP_OFFSET 0x4000000

/* Addresses on the fd of a tcx that are mappable */
#घोषणा TCX_RAM8BIT   		0x00000000
#घोषणा TCX_RAM24BIT   		0x01000000
#घोषणा TCX_UNK3   		0x10000000
#घोषणा TCX_UNK4   		0x20000000
#घोषणा TCX_CONTROLPLANE   	0x28000000
#घोषणा TCX_UNK6   		0x30000000
#घोषणा TCX_UNK7   		0x38000000
#घोषणा TCX_TEC    		0x70000000
#घोषणा TCX_BTREGS 		0x70002000
#घोषणा TCX_THC    		0x70004000
#घोषणा TCX_DHC    		0x70008000
#घोषणा TCX_ALT	   		0x7000a000
#घोषणा TCX_SYNC   		0x7000e000
#घोषणा TCX_UNK2    		0x70010000

/* CG14 definitions */

/* Offsets पूर्णांकo the OBIO space: */
#घोषणा CG14_REGS        0       /* रेजिस्टरs */
#घोषणा CG14_CURSORREGS  0x1000  /* cursor रेजिस्टरs */
#घोषणा CG14_DACREGS     0x2000  /* DAC रेजिस्टरs */
#घोषणा CG14_XLUT        0x3000  /* X Look Up Table -- ??? */
#घोषणा CG14_CLUT1       0x4000  /* Color Look Up Table */
#घोषणा CG14_CLUT2       0x5000  /* Color Look Up Table */
#घोषणा CG14_CLUT3       0x6000  /* Color Look Up Table */
#घोषणा CG14_AUTO	 0xf000

काष्ठा  fbcmap32 अणु
	पूर्णांक             index;          /* first element (0 origin) */
	पूर्णांक             count;
	u32		red;
	u32		green;
	u32		blue;
पूर्ण;

#घोषणा FBIOPUTCMAP32	_IOW('F', 3, काष्ठा fbcmap32)
#घोषणा FBIOGETCMAP32	_IOW('F', 4, काष्ठा fbcmap32)

काष्ठा fbcursor32 अणु
	लघु set;		/* what to set, choose from the list above */
	लघु enable;		/* cursor on/off */
	काष्ठा fbcurpos pos;	/* cursor position */
	काष्ठा fbcurpos hot;	/* cursor hot spot */
	काष्ठा fbcmap32 cmap;	/* color map info */
	काष्ठा fbcurpos size;	/* cursor bit map size */
	u32	image;		/* cursor image bits */
	u32	mask;		/* cursor mask bits */
पूर्ण;

#घोषणा FBIOSCURSOR32	_IOW('F', 24, काष्ठा fbcursor32)
#घोषणा FBIOGCURSOR32	_IOW('F', 25, काष्ठा fbcursor32)
#पूर्ण_अगर /* __LINUX_FBIO_H */
