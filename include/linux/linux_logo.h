<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_LINUX_LOGO_H
#घोषणा _LINUX_LINUX_LOGO_H

/*
 *  Linux logo to be displayed on boot
 *
 *  Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)
 *  Copyright (C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Copyright (C) 2001 Greg Banks <gnb@alphalink.com.au>
 *  Copyright (C) 2001 Jan-Benedict Glaw <jbglaw@lug-owl.de>
 *  Copyright (C) 2003 Geert Uytterhoeven <geert@linux-m68k.org>
 *
 *  Serial_console ascii image can be any size,
 *  but should contain %s to display the version
 */

#समावेश <linux/init.h>


#घोषणा LINUX_LOGO_MONO		1	/* monochrome black/white */
#घोषणा LINUX_LOGO_VGA16	2	/* 16 colors VGA text palette */
#घोषणा LINUX_LOGO_CLUT224	3	/* 224 colors */
#घोषणा LINUX_LOGO_GRAY256	4	/* 256 levels grayscale */


काष्ठा linux_logo अणु
	पूर्णांक type;			/* one of LINUX_LOGO_* */
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक clutsize;		/* LINUX_LOGO_CLUT224 only */
	स्थिर अचिन्हित अक्षर *clut;	/* LINUX_LOGO_CLUT224 only */
	स्थिर अचिन्हित अक्षर *data;
पूर्ण;

बाह्य स्थिर काष्ठा linux_logo logo_linux_mono;
बाह्य स्थिर काष्ठा linux_logo logo_linux_vga16;
बाह्य स्थिर काष्ठा linux_logo logo_linux_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_dec_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_mac_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_parisc_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_sgi_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_sun_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_superh_mono;
बाह्य स्थिर काष्ठा linux_logo logo_superh_vga16;
बाह्य स्थिर काष्ठा linux_logo logo_superh_clut224;
बाह्य स्थिर काष्ठा linux_logo logo_spe_clut224;

बाह्य स्थिर काष्ठा linux_logo *fb_find_logo(पूर्णांक depth);
#अगर_घोषित CONFIG_FB_LOGO_EXTRA
बाह्य व्योम fb_append_extra_logo(स्थिर काष्ठा linux_logo *logo,
				 अचिन्हित पूर्णांक n);
#अन्यथा
अटल अंतरभूत व्योम fb_append_extra_logo(स्थिर काष्ठा linux_logo *logo,
					अचिन्हित पूर्णांक n)
अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_LINUX_LOGO_H */
