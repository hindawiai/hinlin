<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

/*
 *  Linux logo to be displayed on boot
 *
 *  Copyright (C) 1996 Larry Ewing (lewing@isc.tamu.edu)
 *  Copyright (C) 1996,1998 Jakub Jelinek (jj@sunsite.mff.cuni.cz)
 *  Copyright (C) 2001 Greg Banks <gnb@alphalink.com.au>
 *  Copyright (C) 2001 Jan-Benedict Glaw <jbglaw@lug-owl.de>
 *  Copyright (C) 2003 Geert Uytterhoeven <geert@linux-m68k.org>
 */

#समावेश <linux/linux_logo.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>

#अगर_घोषित CONFIG_M68K
#समावेश <यंत्र/setup.h>
#पूर्ण_अगर

अटल bool nologo;
module_param(nologo, bool, 0);
MODULE_PARM_DESC(nologo, "Disables startup logo");

/*
 * Logos are located in the initdata, and will be मुक्तd in kernel_init.
 * Use late_init to mark the logos as मुक्तd to prevent any further use.
 */

अटल bool logos_मुक्तd;

अटल पूर्णांक __init fb_logo_late_init(व्योम)
अणु
	logos_मुक्तd = true;
	वापस 0;
पूर्ण

late_initcall_sync(fb_logo_late_init);

/* logo's are marked __initdata. Use __ref to tell
 * modpost that it is पूर्णांकended that this function uses data
 * marked __initdata.
 */
स्थिर काष्ठा linux_logo * __ref fb_find_logo(पूर्णांक depth)
अणु
	स्थिर काष्ठा linux_logo *logo = शून्य;

	अगर (nologo || logos_मुक्तd)
		वापस शून्य;

	अगर (depth >= 1) अणु
#अगर_घोषित CONFIG_LOGO_LINUX_MONO
		/* Generic Linux logo */
		logo = &logo_linux_mono;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_SUPERH_MONO
		/* SuperH Linux logo */
		logo = &logo_superh_mono;
#पूर्ण_अगर
	पूर्ण
	
	अगर (depth >= 4) अणु
#अगर_घोषित CONFIG_LOGO_LINUX_VGA16
		/* Generic Linux logo */
		logo = &logo_linux_vga16;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_SUPERH_VGA16
		/* SuperH Linux logo */
		logo = &logo_superh_vga16;
#पूर्ण_अगर
	पूर्ण
	
	अगर (depth >= 8) अणु
#अगर_घोषित CONFIG_LOGO_LINUX_CLUT224
		/* Generic Linux logo */
		logo = &logo_linux_clut224;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_DEC_CLUT224
		/* DEC Linux logo on MIPS/MIPS64 or ALPHA */
		logo = &logo_dec_clut224;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_MAC_CLUT224
		/* Macपूर्णांकosh Linux logo on m68k */
		अगर (MACH_IS_MAC)
			logo = &logo_mac_clut224;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_PARISC_CLUT224
		/* PA-RISC Linux logo */
		logo = &logo_parisc_clut224;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_SGI_CLUT224
		/* SGI Linux logo on MIPS/MIPS64 */
		logo = &logo_sgi_clut224;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_SUN_CLUT224
		/* Sun Linux logo */
		logo = &logo_sun_clut224;
#पूर्ण_अगर
#अगर_घोषित CONFIG_LOGO_SUPERH_CLUT224
		/* SuperH Linux logo */
		logo = &logo_superh_clut224;
#पूर्ण_अगर
	पूर्ण
	वापस logo;
पूर्ण
EXPORT_SYMBOL_GPL(fb_find_logo);
