<शैली गुरु>
/*
 * linux/include/video/vga.h -- standard VGA chipset पूर्णांकeraction
 *
 * Copyright 1999 Jeff Garzik <jgarzik@pobox.com>
 * 
 * Copyright history from vga16fb.c:
 *	Copyright 1999 Ben Pfaff and Petr Vandrovec
 *	Based on VGA info at http://www.osdever.net/FreeVGA/home.hपंचांग 
 *	Based on VESA framebuffer (c) 1998 Gerd Knorr
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.  
 *
 */

#अगर_अघोषित __linux_video_vga_h__
#घोषणा __linux_video_vga_h__

#समावेश <linux/types.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/vga.h>
#समावेश <यंत्र/byteorder.h>


/* Some of the code below is taken from SVGAlib.  The original,
   unmodअगरied copyright notice क्रम that code is below. */
/* VGAlib version 1.2 - (c) 1993 Tommy Fअक्रमsen                    */
/*                                                                 */
/* This library is मुक्त software; you can redistribute it and/or   */
/* modअगरy it without any restrictions. This library is distributed */
/* in the hope that it will be useful, but without any warranty.   */

/* Multi-chipset support Copyright 1993 Harm Hanemaayer */
/* partially copyrighted (C) 1993 by Harपंचांगut Schirmer */

/* VGA data रेजिस्टर ports */
#घोषणा VGA_CRT_DC  	0x3D5	/* CRT Controller Data Register - color emulation */
#घोषणा VGA_CRT_DM  	0x3B5	/* CRT Controller Data Register - mono emulation */
#घोषणा VGA_ATT_R   	0x3C1	/* Attribute Controller Data Read Register */
#घोषणा VGA_ATT_W   	0x3C0	/* Attribute Controller Data Write Register */
#घोषणा VGA_GFX_D   	0x3CF	/* Graphics Controller Data Register */
#घोषणा VGA_SEQ_D   	0x3C5	/* Sequencer Data Register */
#घोषणा VGA_MIS_R   	0x3CC	/* Misc Output Read Register */
#घोषणा VGA_MIS_W   	0x3C2	/* Misc Output Write Register */
#घोषणा VGA_FTC_R	0x3CA	/* Feature Control Read Register */
#घोषणा VGA_IS1_RC  	0x3DA	/* Input Status Register 1 - color emulation */
#घोषणा VGA_IS1_RM  	0x3BA	/* Input Status Register 1 - mono emulation */
#घोषणा VGA_PEL_D   	0x3C9	/* PEL Data Register */
#घोषणा VGA_PEL_MSK 	0x3C6	/* PEL mask रेजिस्टर */

/* EGA-specअगरic रेजिस्टरs */
#घोषणा EGA_GFX_E0	0x3CC	/* Graphics enable processor 0 */
#घोषणा EGA_GFX_E1	0x3CA	/* Graphics enable processor 1 */

/* VGA index रेजिस्टर ports */
#घोषणा VGA_CRT_IC  	0x3D4	/* CRT Controller Index - color emulation */
#घोषणा VGA_CRT_IM  	0x3B4	/* CRT Controller Index - mono emulation */
#घोषणा VGA_ATT_IW  	0x3C0	/* Attribute Controller Index & Data Write Register */
#घोषणा VGA_GFX_I   	0x3CE	/* Graphics Controller Index */
#घोषणा VGA_SEQ_I   	0x3C4	/* Sequencer Index */
#घोषणा VGA_PEL_IW  	0x3C8	/* PEL Write Index */
#घोषणा VGA_PEL_IR  	0x3C7	/* PEL Read Index */

/* standard VGA indexes max counts */
#घोषणा VGA_CRT_C   	0x19	/* Number of CRT Controller Registers */
#घोषणा VGA_ATT_C   	0x15	/* Number of Attribute Controller Registers */
#घोषणा VGA_GFX_C   	0x09	/* Number of Graphics Controller Registers */
#घोषणा VGA_SEQ_C   	0x05	/* Number of Sequencer Registers */
#घोषणा VGA_MIS_C   	0x01	/* Number of Misc Output Register */

/* VGA misc रेजिस्टर bit masks */
#घोषणा VGA_MIS_COLOR		0x01
#घोषणा VGA_MIS_ENB_MEM_ACCESS	0x02
#घोषणा VGA_MIS_DCLK_28322_720	0x04
#घोषणा VGA_MIS_ENB_PLL_LOAD	(0x04 | 0x08)
#घोषणा VGA_MIS_SEL_HIGH_PAGE	0x20

/* VGA CRT controller रेजिस्टर indices */
#घोषणा VGA_CRTC_H_TOTAL	0
#घोषणा VGA_CRTC_H_DISP		1
#घोषणा VGA_CRTC_H_BLANK_START	2
#घोषणा VGA_CRTC_H_BLANK_END	3
#घोषणा VGA_CRTC_H_SYNC_START	4
#घोषणा VGA_CRTC_H_SYNC_END	5
#घोषणा VGA_CRTC_V_TOTAL	6
#घोषणा VGA_CRTC_OVERFLOW	7
#घोषणा VGA_CRTC_PRESET_ROW	8
#घोषणा VGA_CRTC_MAX_SCAN	9
#घोषणा VGA_CRTC_CURSOR_START	0x0A
#घोषणा VGA_CRTC_CURSOR_END	0x0B
#घोषणा VGA_CRTC_START_HI	0x0C
#घोषणा VGA_CRTC_START_LO	0x0D
#घोषणा VGA_CRTC_CURSOR_HI	0x0E
#घोषणा VGA_CRTC_CURSOR_LO	0x0F
#घोषणा VGA_CRTC_V_SYNC_START	0x10
#घोषणा VGA_CRTC_V_SYNC_END	0x11
#घोषणा VGA_CRTC_V_DISP_END	0x12
#घोषणा VGA_CRTC_OFFSET		0x13
#घोषणा VGA_CRTC_UNDERLINE	0x14
#घोषणा VGA_CRTC_V_BLANK_START	0x15
#घोषणा VGA_CRTC_V_BLANK_END	0x16
#घोषणा VGA_CRTC_MODE		0x17
#घोषणा VGA_CRTC_LINE_COMPARE	0x18
#घोषणा VGA_CRTC_REGS		VGA_CRT_C

/* VGA CRT controller bit masks */
#घोषणा VGA_CR11_LOCK_CR0_CR7	0x80 /* lock ग_लिखोs to CR0 - CR7 */
#घोषणा VGA_CR17_H_V_SIGNALS_ENABLED 0x80

/* VGA attribute controller रेजिस्टर indices */
#घोषणा VGA_ATC_PALETTE0	0x00
#घोषणा VGA_ATC_PALETTE1	0x01
#घोषणा VGA_ATC_PALETTE2	0x02
#घोषणा VGA_ATC_PALETTE3	0x03
#घोषणा VGA_ATC_PALETTE4	0x04
#घोषणा VGA_ATC_PALETTE5	0x05
#घोषणा VGA_ATC_PALETTE6	0x06
#घोषणा VGA_ATC_PALETTE7	0x07
#घोषणा VGA_ATC_PALETTE8	0x08
#घोषणा VGA_ATC_PALETTE9	0x09
#घोषणा VGA_ATC_PALETTEA	0x0A
#घोषणा VGA_ATC_PALETTEB	0x0B
#घोषणा VGA_ATC_PALETTEC	0x0C
#घोषणा VGA_ATC_PALETTED	0x0D
#घोषणा VGA_ATC_PALETTEE	0x0E
#घोषणा VGA_ATC_PALETTEF	0x0F
#घोषणा VGA_ATC_MODE		0x10
#घोषणा VGA_ATC_OVERSCAN	0x11
#घोषणा VGA_ATC_PLANE_ENABLE	0x12
#घोषणा VGA_ATC_PEL		0x13
#घोषणा VGA_ATC_COLOR_PAGE	0x14

#घोषणा VGA_AR_ENABLE_DISPLAY	0x20

/* VGA sequencer रेजिस्टर indices */
#घोषणा VGA_SEQ_RESET		0x00
#घोषणा VGA_SEQ_CLOCK_MODE	0x01
#घोषणा VGA_SEQ_PLANE_WRITE	0x02
#घोषणा VGA_SEQ_CHARACTER_MAP	0x03
#घोषणा VGA_SEQ_MEMORY_MODE	0x04

/* VGA sequencer रेजिस्टर bit masks */
#घोषणा VGA_SR01_CHAR_CLK_8DOTS	0x01 /* bit 0: अक्षरacter घड़ीs 8 करोts wide are generated */
#घोषणा VGA_SR01_SCREEN_OFF	0x20 /* bit 5: Screen is off */
#घोषणा VGA_SR02_ALL_PLANES	0x0F /* bits 3-0: enable access to all planes */
#घोषणा VGA_SR04_EXT_MEM	0x02 /* bit 1: allows complete mem access to 256K */
#घोषणा VGA_SR04_SEQ_MODE	0x04 /* bit 2: directs प्रणाली to use a sequential addressing mode */
#घोषणा VGA_SR04_CHN_4M		0x08 /* bit 3: selects modulo 4 addressing क्रम CPU access to display memory */

/* VGA graphics controller रेजिस्टर indices */
#घोषणा VGA_GFX_SR_VALUE	0x00
#घोषणा VGA_GFX_SR_ENABLE	0x01
#घोषणा VGA_GFX_COMPARE_VALUE	0x02
#घोषणा VGA_GFX_DATA_ROTATE	0x03
#घोषणा VGA_GFX_PLANE_READ	0x04
#घोषणा VGA_GFX_MODE		0x05
#घोषणा VGA_GFX_MISC		0x06
#घोषणा VGA_GFX_COMPARE_MASK	0x07
#घोषणा VGA_GFX_BIT_MASK	0x08

/* VGA graphics controller bit masks */
#घोषणा VGA_GR06_GRAPHICS_MODE	0x01

/* macro क्रम composing an 8-bit VGA रेजिस्टर index and value
 * पूर्णांकo a single 16-bit quantity */
#घोषणा VGA_OUT16VAL(v, r)       (((v) << 8) | (r))

/* decide whether we should enable the faster 16-bit VGA रेजिस्टर ग_लिखोs */
#अगर_घोषित __LITTLE_ENDIAN
#घोषणा VGA_OUTW_WRITE
#पूर्ण_अगर

/* VGA State Save and Restore */
#घोषणा VGA_SAVE_FONT0 1  /* save/restore plane 2 fonts	  */
#घोषणा VGA_SAVE_FONT1 2  /* save/restore plane 3 fonts   */
#घोषणा VGA_SAVE_TEXT  4  /* save/restore plane 0/1 fonts */
#घोषणा VGA_SAVE_FONTS 7  /* save/restore all fonts	  */
#घोषणा VGA_SAVE_MODE  8  /* save/restore video mode 	  */
#घोषणा VGA_SAVE_CMAP  16 /* save/restore color map/DAC   */

काष्ठा vgastate अणु
	व्योम __iomem *vgabase;	/* mmio base, अगर supported 		   */
	अचिन्हित दीर्घ membase;	/* VGA winकरोw base, 0 क्रम शेष - 0xA000 */
	__u32 memsize;		/* VGA winकरोw size, 0 क्रम शेष 64K	   */
	__u32 flags;		/* what state[s] to save (see VGA_SAVE_*)  */
	__u32 depth;		/* current fb depth, not important	   */
	__u32 num_attr;		/* number of att रेजिस्टरs, 0 क्रम शेष  */
	__u32 num_crtc;		/* number of crt रेजिस्टरs, 0 क्रम शेष  */
	__u32 num_gfx;		/* number of gfx रेजिस्टरs, 0 क्रम शेष  */
	__u32 num_seq;		/* number of seq रेजिस्टरs, 0 क्रम शेष  */
	व्योम *vidstate;
पूर्ण;	

बाह्य पूर्णांक save_vga(काष्ठा vgastate *state);
बाह्य पूर्णांक restore_vga(काष्ठा vgastate *state);

/*
 * generic VGA port पढ़ो/ग_लिखो
 */
 
अटल अंतरभूत अचिन्हित अक्षर vga_io_r (अचिन्हित लघु port)
अणु
	वापस inb_p(port);
पूर्ण

अटल अंतरभूत व्योम vga_io_w (अचिन्हित लघु port, अचिन्हित अक्षर val)
अणु
	outb_p(val, port);
पूर्ण

अटल अंतरभूत व्योम vga_io_w_fast (अचिन्हित लघु port, अचिन्हित अक्षर reg,
				  अचिन्हित अक्षर val)
अणु
	outw(VGA_OUT16VAL (val, reg), port);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_mm_r (व्योम __iomem *regbase, अचिन्हित लघु port)
अणु
	वापस पढ़ोb (regbase + port);
पूर्ण

अटल अंतरभूत व्योम vga_mm_w (व्योम __iomem *regbase, अचिन्हित लघु port, अचिन्हित अक्षर val)
अणु
	ग_लिखोb (val, regbase + port);
पूर्ण

अटल अंतरभूत व्योम vga_mm_w_fast (व्योम __iomem *regbase, अचिन्हित लघु port,
				  अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	ग_लिखोw (VGA_OUT16VAL (val, reg), regbase + port);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_r (व्योम __iomem *regbase, अचिन्हित लघु port)
अणु
	अगर (regbase)
		वापस vga_mm_r (regbase, port);
	अन्यथा
		वापस vga_io_r (port);
पूर्ण

अटल अंतरभूत व्योम vga_w (व्योम __iomem *regbase, अचिन्हित लघु port, अचिन्हित अक्षर val)
अणु
	अगर (regbase)
		vga_mm_w (regbase, port, val);
	अन्यथा
		vga_io_w (port, val);
पूर्ण


अटल अंतरभूत व्योम vga_w_fast (व्योम __iomem *regbase, अचिन्हित लघु port,
			       अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
	अगर (regbase)
		vga_mm_w_fast (regbase, port, reg, val);
	अन्यथा
		vga_io_w_fast (port, reg, val);
पूर्ण


/*
 * VGA CRTC रेजिस्टर पढ़ो/ग_लिखो
 */
 
अटल अंतरभूत अचिन्हित अक्षर vga_rcrt (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_w (regbase, VGA_CRT_IC, reg);
        वापस vga_r (regbase, VGA_CRT_DC);
पूर्ण

अटल अंतरभूत व्योम vga_wcrt (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_w_fast (regbase, VGA_CRT_IC, reg, val);
#अन्यथा
        vga_w (regbase, VGA_CRT_IC, reg);
        vga_w (regbase, VGA_CRT_DC, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_io_rcrt (अचिन्हित अक्षर reg)
अणु
        vga_io_w (VGA_CRT_IC, reg);
        वापस vga_io_r (VGA_CRT_DC);
पूर्ण

अटल अंतरभूत व्योम vga_io_wcrt (अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_io_w_fast (VGA_CRT_IC, reg, val);
#अन्यथा
        vga_io_w (VGA_CRT_IC, reg);
        vga_io_w (VGA_CRT_DC, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_mm_rcrt (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_mm_w (regbase, VGA_CRT_IC, reg);
        वापस vga_mm_r (regbase, VGA_CRT_DC);
पूर्ण

अटल अंतरभूत व्योम vga_mm_wcrt (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_mm_w_fast (regbase, VGA_CRT_IC, reg, val);
#अन्यथा
        vga_mm_w (regbase, VGA_CRT_IC, reg);
        vga_mm_w (regbase, VGA_CRT_DC, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण


/*
 * VGA sequencer रेजिस्टर पढ़ो/ग_लिखो
 */
 
अटल अंतरभूत अचिन्हित अक्षर vga_rseq (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_w (regbase, VGA_SEQ_I, reg);
        वापस vga_r (regbase, VGA_SEQ_D);
पूर्ण

अटल अंतरभूत व्योम vga_wseq (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_w_fast (regbase, VGA_SEQ_I, reg, val);
#अन्यथा
        vga_w (regbase, VGA_SEQ_I, reg);
        vga_w (regbase, VGA_SEQ_D, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_io_rseq (अचिन्हित अक्षर reg)
अणु
        vga_io_w (VGA_SEQ_I, reg);
        वापस vga_io_r (VGA_SEQ_D);
पूर्ण

अटल अंतरभूत व्योम vga_io_wseq (अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_io_w_fast (VGA_SEQ_I, reg, val);
#अन्यथा
        vga_io_w (VGA_SEQ_I, reg);
        vga_io_w (VGA_SEQ_D, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_mm_rseq (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_mm_w (regbase, VGA_SEQ_I, reg);
        वापस vga_mm_r (regbase, VGA_SEQ_D);
पूर्ण

अटल अंतरभूत व्योम vga_mm_wseq (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_mm_w_fast (regbase, VGA_SEQ_I, reg, val);
#अन्यथा
        vga_mm_w (regbase, VGA_SEQ_I, reg);
        vga_mm_w (regbase, VGA_SEQ_D, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

/*
 * VGA graphics controller रेजिस्टर पढ़ो/ग_लिखो
 */
 
अटल अंतरभूत अचिन्हित अक्षर vga_rgfx (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_w (regbase, VGA_GFX_I, reg);
        वापस vga_r (regbase, VGA_GFX_D);
पूर्ण

अटल अंतरभूत व्योम vga_wgfx (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_w_fast (regbase, VGA_GFX_I, reg, val);
#अन्यथा
        vga_w (regbase, VGA_GFX_I, reg);
        vga_w (regbase, VGA_GFX_D, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_io_rgfx (अचिन्हित अक्षर reg)
अणु
        vga_io_w (VGA_GFX_I, reg);
        वापस vga_io_r (VGA_GFX_D);
पूर्ण

अटल अंतरभूत व्योम vga_io_wgfx (अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_io_w_fast (VGA_GFX_I, reg, val);
#अन्यथा
        vga_io_w (VGA_GFX_I, reg);
        vga_io_w (VGA_GFX_D, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_mm_rgfx (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_mm_w (regbase, VGA_GFX_I, reg);
        वापस vga_mm_r (regbase, VGA_GFX_D);
पूर्ण

अटल अंतरभूत व्योम vga_mm_wgfx (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
#अगर_घोषित VGA_OUTW_WRITE
	vga_mm_w_fast (regbase, VGA_GFX_I, reg, val);
#अन्यथा
        vga_mm_w (regbase, VGA_GFX_I, reg);
        vga_mm_w (regbase, VGA_GFX_D, val);
#पूर्ण_अगर /* VGA_OUTW_WRITE */
पूर्ण


/*
 * VGA attribute controller रेजिस्टर पढ़ो/ग_लिखो
 */
 
अटल अंतरभूत अचिन्हित अक्षर vga_rattr (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_w (regbase, VGA_ATT_IW, reg);
        वापस vga_r (regbase, VGA_ATT_R);
पूर्ण

अटल अंतरभूत व्योम vga_wattr (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
        vga_w (regbase, VGA_ATT_IW, reg);
        vga_w (regbase, VGA_ATT_W, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_io_rattr (अचिन्हित अक्षर reg)
अणु
        vga_io_w (VGA_ATT_IW, reg);
        वापस vga_io_r (VGA_ATT_R);
पूर्ण

अटल अंतरभूत व्योम vga_io_wattr (अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
        vga_io_w (VGA_ATT_IW, reg);
        vga_io_w (VGA_ATT_W, val);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर vga_mm_rattr (व्योम __iomem *regbase, अचिन्हित अक्षर reg)
अणु
        vga_mm_w (regbase, VGA_ATT_IW, reg);
        वापस vga_mm_r (regbase, VGA_ATT_R);
पूर्ण

अटल अंतरभूत व्योम vga_mm_wattr (व्योम __iomem *regbase, अचिन्हित अक्षर reg, अचिन्हित अक्षर val)
अणु
        vga_mm_w (regbase, VGA_ATT_IW, reg);
        vga_mm_w (regbase, VGA_ATT_W, val);
पूर्ण

#पूर्ण_अगर /* __linux_video_vga_h__ */
