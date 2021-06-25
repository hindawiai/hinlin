<शैली गुरु>
/*
 * Silicon Motion SM712 frame buffer device
 *
 * Copyright (C) 2006 Silicon Motion Technology Corp.
 * Authors:	Ge Wang, gewang@siliconmotion.com
 *		Boyod boyod.yang@siliconmotion.com.cn
 *
 * Copyright (C) 2009 Lemote, Inc.
 * Author: Wu Zhangjin, wuzhangjin@gmail.com
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#घोषणा FB_ACCEL_SMI_LYNX 88

#घोषणा SCREEN_X_RES          1024
#घोषणा SCREEN_Y_RES_PC       768
#घोषणा SCREEN_Y_RES_NETBOOK  600
#घोषणा SCREEN_BPP            16

#घोषणा dac_reg	(0x3c8)
#घोषणा dac_val	(0x3c9)

बाह्य व्योम __iomem *smtc_regbaseaddress;
#घोषणा smtc_mmiowb(dat, reg)	ग_लिखोb(dat, smtc_regbaseaddress + reg)

#घोषणा smtc_mmiorb(reg)	पढ़ोb(smtc_regbaseaddress + reg)

#घोषणा SIZE_SR00_SR04      (0x04 - 0x00 + 1)
#घोषणा SIZE_SR10_SR24      (0x24 - 0x10 + 1)
#घोषणा SIZE_SR30_SR75      (0x75 - 0x30 + 1)
#घोषणा SIZE_SR80_SR93      (0x93 - 0x80 + 1)
#घोषणा SIZE_SRA0_SRAF      (0xAF - 0xA0 + 1)
#घोषणा SIZE_GR00_GR08      (0x08 - 0x00 + 1)
#घोषणा SIZE_AR00_AR14      (0x14 - 0x00 + 1)
#घोषणा SIZE_CR00_CR18      (0x18 - 0x00 + 1)
#घोषणा SIZE_CR30_CR4D      (0x4D - 0x30 + 1)
#घोषणा SIZE_CR90_CRA7      (0xA7 - 0x90 + 1)

अटल अंतरभूत व्योम smtc_crtcw(पूर्णांक reg, पूर्णांक val)
अणु
	smtc_mmiowb(reg, 0x3d4);
	smtc_mmiowb(val, 0x3d5);
पूर्ण

अटल अंतरभूत व्योम smtc_grphw(पूर्णांक reg, पूर्णांक val)
अणु
	smtc_mmiowb(reg, 0x3ce);
	smtc_mmiowb(val, 0x3cf);
पूर्ण

अटल अंतरभूत व्योम smtc_attrw(पूर्णांक reg, पूर्णांक val)
अणु
	smtc_mmiorb(0x3da);
	smtc_mmiowb(reg, 0x3c0);
	smtc_mmiorb(0x3c1);
	smtc_mmiowb(val, 0x3c0);
पूर्ण

अटल अंतरभूत व्योम smtc_seqw(पूर्णांक reg, पूर्णांक val)
अणु
	smtc_mmiowb(reg, 0x3c4);
	smtc_mmiowb(val, 0x3c5);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक smtc_seqr(पूर्णांक reg)
अणु
	smtc_mmiowb(reg, 0x3c4);
	वापस smtc_mmiorb(0x3c5);
पूर्ण

/* The next काष्ठाure holds all inक्रमmation relevant क्रम a specअगरic video mode.
 */

काष्ठा modeinit अणु
	पूर्णांक mmsizex;
	पूर्णांक mmsizey;
	पूर्णांक bpp;
	पूर्णांक hz;
	अचिन्हित अक्षर init_misc;
	अचिन्हित अक्षर init_sr00_sr04[SIZE_SR00_SR04];
	अचिन्हित अक्षर init_sr10_sr24[SIZE_SR10_SR24];
	अचिन्हित अक्षर init_sr30_sr75[SIZE_SR30_SR75];
	अचिन्हित अक्षर init_sr80_sr93[SIZE_SR80_SR93];
	अचिन्हित अक्षर init_sra0_sraf[SIZE_SRA0_SRAF];
	अचिन्हित अक्षर init_gr00_gr08[SIZE_GR00_GR08];
	अचिन्हित अक्षर init_ar00_ar14[SIZE_AR00_AR14];
	अचिन्हित अक्षर init_cr00_cr18[SIZE_CR00_CR18];
	अचिन्हित अक्षर init_cr30_cr4d[SIZE_CR30_CR4D];
	अचिन्हित अक्षर init_cr90_cra7[SIZE_CR90_CRA7];
पूर्ण;

#अगर_घोषित __BIG_ENDIAN
#घोषणा pal_rgb(r, g, b, val)	(((r & 0xf800) >> 8) | \
				((g & 0xe000) >> 13) | \
				((g & 0x1c00) << 3) | \
				((b & 0xf800) >> 3))
#घोषणा big_addr		0x800000
#घोषणा mmio_addr		0x00800000
#घोषणा seqw17()		smtc_seqw(0x17, 0x30)
#घोषणा big_pixel_depth(p, d)	अणुअगर (p == 24) अणुp = 32; d = 32; पूर्ण पूर्ण
#घोषणा big_swap(p)		((p & 0xff00ff00 >> 8) | (p & 0x00ff00ff << 8))
#अन्यथा
#घोषणा pal_rgb(r, g, b, val)	val
#घोषणा big_addr		0
#घोषणा mmio_addr		0x00c00000
#घोषणा seqw17()		करो अणु पूर्ण जबतक (0)
#घोषणा big_pixel_depth(p, d)	करो अणु पूर्ण जबतक (0)
#घोषणा big_swap(p)		p
#पूर्ण_अगर
