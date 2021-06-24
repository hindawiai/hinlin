<शैली गुरु>
/*
 * पूर्णांकelfb
 *
 * Linux framebuffer driver क्रम Intel(R) 830M/845G/852GM/855GM/865G/915G/915GM/
 * 945G/945GM/945GME/965G/965GM पूर्णांकegrated graphics chips.
 *
 * Copyright तऊ 2002, 2003 David Dawes <dawes@xमुक्त86.org>
 *                   2004 Sylvain Meyer
 *                   2006 David Airlie
 *
 * This driver consists of two parts.  The first part (पूर्णांकelfbdrv.c) provides
 * the basic fbdev पूर्णांकerfaces, is derived in part from the radeonfb and
 * vesafb drivers, and is covered by the GPL.  The second part (पूर्णांकelfbhw.c)
 * provides the code to program the hardware.  Most of it is derived from
 * the i810/i830 XFree86 driver.  The HW-specअगरic code is covered here
 * under a dual license (GPL and MIT/XFree86 license).
 *
 * Author: David Dawes
 *
 */

/* $DHD: पूर्णांकelfb/पूर्णांकelfbdrv.c,v 1.20 2003/06/27 15:17:40 dawes Exp $ */

/*
 * Changes:
 *    01/2003 - Initial driver (0.1.0), no mode चयनing, no acceleration.
 *		This initial version is a basic core that works a lot like
 *		the vesafb driver.  It must be built-in to the kernel,
 *		and the initial video mode must be set with vga=XXX at
 *		boot समय.  (David Dawes)
 *
 *    01/2003 - Version 0.2.0: Mode चयनing added, colormap support
 *		implemented, Y panning, and soft screen blanking implemented.
 *		No acceleration yet.  (David Dawes)
 *
 *    01/2003 - Version 0.3.0: fbcon acceleration support added.  Module
 *		option handling added.  (David Dawes)
 *
 *    01/2003 - Version 0.4.0: fbcon HW cursor support added.  (David Dawes)
 *
 *    01/2003 - Version 0.4.1: Add स्वतः-generation of built-in modes.
 *		(David Dawes)
 *
 *    02/2003 - Version 0.4.2: Add check क्रम active non-CRT devices, and
 *		mode validation checks.  (David Dawes)
 *
 *    02/2003 - Version 0.4.3: Check when the VC is in graphics mode so that
 *		acceleration is disabled जबतक an XFree86 server is running.
 *		(David Dawes)
 *
 *    02/2003 - Version 0.4.4: Monitor DPMS support.  (David Dawes)
 *
 *    02/2003 - Version 0.4.5: Basic XFree86 + fbdev working.  (David Dawes)
 *
 *    02/2003 - Version 0.5.0: Modअगरy to work with the 2.5.32 kernel as well
 *		as 2.4.x kernels.  (David Dawes)
 *
 *    02/2003 - Version 0.6.0: Split out HW-specअगरics पूर्णांकo a separate file.
 *		(David Dawes)
 *
 *    02/2003 - Version 0.7.0: Test on 852GM/855GM.  Acceleration and HW
 *		cursor are disabled on this platक्रमm.  (David Dawes)
 *
 *    02/2003 - Version 0.7.1: Test on 845G.  Acceleration is disabled
 *		on this platक्रमm.  (David Dawes)
 *
 *    02/2003 - Version 0.7.2: Test on 830M.  Acceleration and HW
 *		cursor are disabled on this platक्रमm.  (David Dawes)
 *
 *    02/2003 - Version 0.7.3: Fix 8-bit modes क्रम mobile platक्रमms
 *		(David Dawes)
 *
 *    02/2003 - Version 0.7.4: Add checks क्रम FB and FBCON_HAS_CFB* configured
 *		in the kernel, and add mode bpp verअगरication and शेष
 *		bpp selection based on which FBCON_HAS_CFB* are configured.
 *		(David Dawes)
 *
 *    02/2003 - Version 0.7.5: Add basic package/install scripts based on the
 *		DRI packaging scripts.  (David Dawes)
 *
 *    04/2003 - Version 0.7.6: Fix typo that affects builds with SMP-enabled
 *		kernels.  (David Dawes, reported by Anupam).
 *
 *    06/2003 - Version 0.7.7:
 *              Fix Makefile.kernel build problem (Tsutomu Yasuda).
 *		Fix mis-placed #पूर्ण_अगर (2.4.21 kernel).
 *
 *    09/2004 - Version 0.9.0 - by Sylvain Meyer
 *              Port to linux 2.6 kernel fbdev
 *              Fix HW accel and HW cursor on i845G
 *              Use of agpgart क्रम fb memory reservation
 *              Add mtrr support
 *
 *    10/2004 - Version 0.9.1
 *              Use module_param instead of old MODULE_PARM
 *              Some cleanup
 *
 *    11/2004 - Version 0.9.2
 *              Add vram option to reserve more memory than stolen by BIOS
 *              Fix पूर्णांकelfbhw_pan_display typo
 *              Add __initdata annotations
 *
 *    04/2008 - Version 0.9.5
 *              Add support क्रम 965G/965GM. (Maik Broemme <mbroemme@plusserver.de>)
 *
 *    08/2008 - Version 0.9.6
 *              Add support क्रम 945GME. (Phil Endecott <spam_from_पूर्णांकelfb@chezphil.org>)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/screen_info.h>

#समावेश <यंत्र/पन.स>

#समावेश "intelfb.h"
#समावेश "intelfbhw.h"
#समावेश "../edid.h"

अटल व्योम get_initial_mode(काष्ठा पूर्णांकelfb_info *dinfo);
अटल व्योम update_dinfo(काष्ठा पूर्णांकelfb_info *dinfo,
			 काष्ठा fb_var_screeninfo *var);
अटल पूर्णांक पूर्णांकelfb_खोलो(काष्ठा fb_info *info, पूर्णांक user);
अटल पूर्णांक पूर्णांकelfb_release(काष्ठा fb_info *info, पूर्णांक user);
अटल पूर्णांक पूर्णांकelfb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info);
अटल पूर्णांक पूर्णांकelfb_set_par(काष्ठा fb_info *info);
अटल पूर्णांक पूर्णांकelfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			     अचिन्हित blue, अचिन्हित transp,
			     काष्ठा fb_info *info);

अटल पूर्णांक पूर्णांकelfb_blank(पूर्णांक blank, काष्ठा fb_info *info);
अटल पूर्णांक पूर्णांकelfb_pan_display(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info);

अटल व्योम पूर्णांकelfb_fillrect(काष्ठा fb_info *info,
			     स्थिर काष्ठा fb_fillrect *rect);
अटल व्योम पूर्णांकelfb_copyarea(काष्ठा fb_info *info,
			     स्थिर काष्ठा fb_copyarea *region);
अटल व्योम पूर्णांकelfb_imageblit(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_image *image);
अटल पूर्णांक पूर्णांकelfb_cursor(काष्ठा fb_info *info,
			   काष्ठा fb_cursor *cursor);

अटल पूर्णांक पूर्णांकelfb_sync(काष्ठा fb_info *info);

अटल पूर्णांक पूर्णांकelfb_ioctl(काष्ठा fb_info *info,
			 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

अटल पूर्णांक पूर्णांकelfb_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent);
अटल व्योम पूर्णांकelfb_pci_unरेजिस्टर(काष्ठा pci_dev *pdev);
अटल पूर्णांक पूर्णांकelfb_set_fbinfo(काष्ठा पूर्णांकelfb_info *dinfo);

/*
 * Limiting the class to PCI_CLASS_DISPLAY_VGA prevents function 1 of the
 * mobile chipsets from being रेजिस्टरed.
 */
#अगर DETECT_VGA_CLASS_ONLY
#घोषणा INTELFB_CLASS_MASK ~0 << 8
#अन्यथा
#घोषणा INTELFB_CLASS_MASK 0
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id पूर्णांकelfb_pci_table[] = अणु
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_830M, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_830M पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_845G, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_845G पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_85XGM, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_85XGM पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_865G, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_865G पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_854, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_854 पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_915G, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_915G पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_915GM, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_915GM पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_945G, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_945G पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_945GM, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_945GM पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_945GME, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_945GME पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_965G, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_965G पूर्ण,
	अणु PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_965GM, PCI_ANY_ID, PCI_ANY_ID, PCI_CLASS_DISPLAY_VGA << 8, INTELFB_CLASS_MASK, INTEL_965GM पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

/* Global data */
अटल पूर्णांक num_रेजिस्टरed = 0;

/* fb ops */
अटल स्थिर काष्ठा fb_ops पूर्णांकel_fb_ops = अणु
	.owner =		THIS_MODULE,
	.fb_खोलो =              पूर्णांकelfb_खोलो,
	.fb_release =           पूर्णांकelfb_release,
	.fb_check_var =         पूर्णांकelfb_check_var,
	.fb_set_par =           पूर्णांकelfb_set_par,
	.fb_setcolreg =		पूर्णांकelfb_setcolreg,
	.fb_blank =		पूर्णांकelfb_blank,
	.fb_pan_display =       पूर्णांकelfb_pan_display,
	.fb_fillrect  =         पूर्णांकelfb_fillrect,
	.fb_copyarea  =         पूर्णांकelfb_copyarea,
	.fb_imageblit =         पूर्णांकelfb_imageblit,
	.fb_cursor =            पूर्णांकelfb_cursor,
	.fb_sync =              पूर्णांकelfb_sync,
	.fb_ioctl =		पूर्णांकelfb_ioctl
पूर्ण;

/* PCI driver module table */
अटल काष्ठा pci_driver पूर्णांकelfb_driver = अणु
	.name =		"intelfb",
	.id_table =	पूर्णांकelfb_pci_table,
	.probe =	पूर्णांकelfb_pci_रेजिस्टर,
	.हटाओ =	पूर्णांकelfb_pci_unरेजिस्टर,
पूर्ण;

/* Module description/parameters */
MODULE_AUTHOR("David Dawes <dawes@tungstengraphics.com>, "
	      "Sylvain Meyer <sylvain.meyer@worldonline.fr>");
MODULE_DESCRIPTION("Framebuffer driver for Intel(R) " SUPPORTED_CHIPSETS
		   " chipsets");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DEVICE_TABLE(pci, पूर्णांकelfb_pci_table);

अटल bool accel       = 1;
अटल पूर्णांक vram         = 4;
अटल bool hwcursor    = 0;
अटल bool mtrr        = 1;
अटल bool fixed       = 0;
अटल bool noinit      = 0;
अटल bool noरेजिस्टर  = 0;
अटल bool probeonly   = 0;
अटल bool iकरोnly      = 0;
अटल पूर्णांक bailearly    = 0;
अटल पूर्णांक voffset	= 48;
अटल अक्षर *mode       = शून्य;

module_param(accel, bool, S_IRUGO);
MODULE_PARM_DESC(accel, "Enable hardware acceleration");
module_param(vram, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(vram, "System RAM to allocate to framebuffer in MiB");
module_param(voffset, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(voffset, "Offset of framebuffer in MiB");
module_param(hwcursor, bool, S_IRUGO);
MODULE_PARM_DESC(hwcursor, "Enable HW cursor");
module_param(mtrr, bool, S_IRUGO);
MODULE_PARM_DESC(mtrr, "Enable MTRR support");
module_param(fixed, bool, S_IRUGO);
MODULE_PARM_DESC(fixed, "Disable mode switching");
module_param(noinit, bool, 0);
MODULE_PARM_DESC(noinit, "Don't initialise graphics mode when loading");
module_param(noरेजिस्टर, bool, 0);
MODULE_PARM_DESC(noरेजिस्टर, "Don't register, just probe and exit (debug)");
module_param(probeonly, bool, 0);
MODULE_PARM_DESC(probeonly, "Do a minimal probe (debug)");
module_param(iकरोnly, bool, 0);
MODULE_PARM_DESC(iकरोnly, "Just identify without doing anything else (debug)");
module_param(bailearly, पूर्णांक, 0);
MODULE_PARM_DESC(bailearly, "Bail out early, depending on value (debug)");
module_param(mode, अक्षरp, S_IRUGO);
MODULE_PARM_DESC(mode,
		 "Initial video mode \"<xres>x<yres>[-<depth>][@<refresh>]\"");

#अगर_अघोषित MODULE
#घोषणा OPT_EQUAL(opt, name) (!म_भेदन(opt, name, म_माप(name)))
#घोषणा OPT_INTVAL(opt, name) simple_म_से_अदीर्घ(opt + म_माप(name) + 1, शून्य, 0)
#घोषणा OPT_STRVAL(opt, name) (opt + म_माप(name))

अटल __अंतरभूत__ अक्षर * get_opt_string(स्थिर अक्षर *this_opt, स्थिर अक्षर *name)
अणु
	स्थिर अक्षर *p;
	पूर्णांक i;
	अक्षर *ret;

	p = OPT_STRVAL(this_opt, name);
	i = 0;
	जबतक (p[i] && p[i] != ' ' && p[i] != ',')
		i++;
	ret = kदो_स्मृति(i + 1, GFP_KERNEL);
	अगर (ret) अणु
		म_नकलन(ret, p, i);
		ret[i] = '\0';
	पूर्ण
	वापस ret;
पूर्ण

अटल __अंतरभूत__ पूर्णांक get_opt_पूर्णांक(स्थिर अक्षर *this_opt, स्थिर अक्षर *name,
				  पूर्णांक *ret)
अणु
	अगर (!ret)
		वापस 0;

	अगर (!OPT_EQUAL(this_opt, name))
		वापस 0;

	*ret = OPT_INTVAL(this_opt, name);
	वापस 1;
पूर्ण

अटल __अंतरभूत__ पूर्णांक get_opt_bool(स्थिर अक्षर *this_opt, स्थिर अक्षर *name,
				   bool *ret)
अणु
	अगर (!ret)
		वापस 0;

	अगर (OPT_EQUAL(this_opt, name)) अणु
		अगर (this_opt[म_माप(name)] == '=')
			*ret = simple_म_से_अदीर्घ(this_opt + म_माप(name) + 1,
					      शून्य, 0);
		अन्यथा
			*ret = 1;
	पूर्ण अन्यथा अणु
		अगर (OPT_EQUAL(this_opt, "no") && OPT_EQUAL(this_opt + 2, name))
			*ret = 0;
		अन्यथा
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल पूर्णांक __init पूर्णांकelfb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	DBG_MSG("intelfb_setup\n");

	अगर (!options || !*options) अणु
		DBG_MSG("no options\n");
		वापस 0;
	पूर्ण अन्यथा
		DBG_MSG("options: %s\n", options);

	/*
	 * These are the built-in options analogous to the module parameters
	 * defined above.
	 *
	 * The syntax is:
	 *
	 *    video=पूर्णांकelfb:[mode][,<param>=<val>] ...
	 *
	 * e.g.,
	 *
	 *    video=पूर्णांकelfb:1024x768-16@75,accel=0
	 */

	जबतक ((this_opt = strsep(&options, ","))) अणु
		अगर (!*this_opt)
			जारी;
		अगर (get_opt_bool(this_opt, "accel", &accel))
			;
		अन्यथा अगर (get_opt_पूर्णांक(this_opt, "vram", &vram))
			;
		अन्यथा अगर (get_opt_bool(this_opt, "hwcursor", &hwcursor))
			;
		अन्यथा अगर (get_opt_bool(this_opt, "mtrr", &mtrr))
			;
		अन्यथा अगर (get_opt_bool(this_opt, "fixed", &fixed))
			;
		अन्यथा अगर (get_opt_bool(this_opt, "init", &noinit))
			noinit = !noinit;
		अन्यथा अगर (OPT_EQUAL(this_opt, "mode="))
			mode = get_opt_string(this_opt, "mode=");
		अन्यथा
			mode = this_opt;
	पूर्ण

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __init पूर्णांकelfb_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अक्षर *option = शून्य;
#पूर्ण_अगर

	DBG_MSG("intelfb_init\n");

	INF_MSG("Framebuffer driver for "
		"Intel(R) " SUPPORTED_CHIPSETS " chipsets\n");
	INF_MSG("Version " INTELFB_VERSION "\n");

	अगर (iकरोnly)
		वापस -ENODEV;

#अगर_अघोषित MODULE
	अगर (fb_get_options("intelfb", &option))
		वापस -ENODEV;
	पूर्णांकelfb_setup(option);
#पूर्ण_अगर

	वापस pci_रेजिस्टर_driver(&पूर्णांकelfb_driver);
पूर्ण

अटल व्योम __निकास पूर्णांकelfb_निकास(व्योम)
अणु
	DBG_MSG("intelfb_exit\n");
	pci_unरेजिस्टर_driver(&पूर्णांकelfb_driver);
पूर्ण

module_init(पूर्णांकelfb_init);
module_निकास(पूर्णांकelfb_निकास);

/***************************************************************
 *                        driver init / cleanup                *
 ***************************************************************/

अटल व्योम cleanup(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	DBG_MSG("cleanup\n");

	अगर (!dinfo)
		वापस;

	पूर्णांकelfbhw_disable_irq(dinfo);

	fb_dealloc_cmap(&dinfo->info->cmap);
	kमुक्त(dinfo->info->pixmap.addr);

	अगर (dinfo->रेजिस्टरed)
		unरेजिस्टर_framebuffer(dinfo->info);

	arch_phys_wc_del(dinfo->wc_cookie);

	अगर (dinfo->fbmem_gart && dinfo->gtt_fb_mem) अणु
		agp_unbind_memory(dinfo->gtt_fb_mem);
		agp_मुक्त_memory(dinfo->gtt_fb_mem);
	पूर्ण
	अगर (dinfo->gtt_cursor_mem) अणु
		agp_unbind_memory(dinfo->gtt_cursor_mem);
		agp_मुक्त_memory(dinfo->gtt_cursor_mem);
	पूर्ण
	अगर (dinfo->gtt_ring_mem) अणु
		agp_unbind_memory(dinfo->gtt_ring_mem);
		agp_मुक्त_memory(dinfo->gtt_ring_mem);
	पूर्ण

#अगर_घोषित CONFIG_FB_INTEL_I2C
	/* un-रेजिस्टर I2C bus */
	पूर्णांकelfb_delete_i2c_busses(dinfo);
#पूर्ण_अगर

	अगर (dinfo->mmio_base)
		iounmap((व्योम __iomem *)dinfo->mmio_base);
	अगर (dinfo->aperture.भव)
		iounmap((व्योम __iomem *)dinfo->aperture.भव);

	अगर (dinfo->flag & INTELFB_MMIO_ACQUIRED)
		release_mem_region(dinfo->mmio_base_phys, INTEL_REG_SIZE);
	अगर (dinfo->flag & INTELFB_FB_ACQUIRED)
		release_mem_region(dinfo->aperture.physical,
				   dinfo->aperture.size);
	framebuffer_release(dinfo->info);
पूर्ण

#घोषणा bailout(dinfo) करो अणु						\
	DBG_MSG("bailout\n");						\
	cleanup(dinfo);							\
	INF_MSG("Not going to register framebuffer, exiting...\n");	\
	वापस -ENODEV;							\
पूर्ण जबतक (0)


अटल पूर्णांक पूर्णांकelfb_pci_रेजिस्टर(काष्ठा pci_dev *pdev,
				स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा fb_info *info;
	काष्ठा पूर्णांकelfb_info *dinfo;
	पूर्णांक i, err, dvo;
	पूर्णांक aperture_size, stolen_size;
	काष्ठा agp_kern_info gtt_info;
	पूर्णांक agp_memtype;
	स्थिर अक्षर *s;
	काष्ठा agp_bridge_data *bridge;
	पूर्णांक aperture_bar = 0;
	पूर्णांक mmio_bar = 1;
	पूर्णांक offset;

	DBG_MSG("intelfb_pci_register\n");

	num_रेजिस्टरed++;
	अगर (num_रेजिस्टरed != 1) अणु
		ERR_MSG("Attempted to register %d devices "
			"(should be only 1).\n", num_रेजिस्टरed);
		वापस -ENODEV;
	पूर्ण

	info = framebuffer_alloc(माप(काष्ठा पूर्णांकelfb_info), &pdev->dev);
	अगर (!info)
		वापस -ENOMEM;

	अगर (fb_alloc_cmap(&info->cmap, 256, 1) < 0) अणु
		ERR_MSG("Could not allocate cmap for intelfb_info.\n");
		जाओ err_out_cmap;
	पूर्ण

	dinfo = info->par;
	dinfo->info  = info;
	dinfo->fbops = &पूर्णांकel_fb_ops;
	dinfo->pdev  = pdev;

	/* Reserve pixmap space. */
	info->pixmap.addr = kzalloc(64 * 1024, GFP_KERNEL);
	अगर (info->pixmap.addr == शून्य) अणु
		ERR_MSG("Cannot reserve pixmap memory.\n");
		जाओ err_out_pixmap;
	पूर्ण

	/* set early this option because it could be changed by tv encoder
	   driver */
	dinfo->fixed_mode = fixed;

	/* Enable device. */
	अगर ((err = pci_enable_device(pdev))) अणु
		ERR_MSG("Cannot enable device.\n");
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	/* Set base addresses. */
	अगर ((ent->device == PCI_DEVICE_ID_INTEL_915G) ||
	    (ent->device == PCI_DEVICE_ID_INTEL_915GM) ||
	    (ent->device == PCI_DEVICE_ID_INTEL_945G)  ||
	    (ent->device == PCI_DEVICE_ID_INTEL_945GM) ||
	    (ent->device == PCI_DEVICE_ID_INTEL_945GME) ||
	    (ent->device == PCI_DEVICE_ID_INTEL_965G) ||
	    (ent->device == PCI_DEVICE_ID_INTEL_965GM)) अणु

		aperture_bar = 2;
		mmio_bar = 0;
	पूर्ण
	dinfo->aperture.physical = pci_resource_start(pdev, aperture_bar);
	dinfo->aperture.size     = pci_resource_len(pdev, aperture_bar);
	dinfo->mmio_base_phys    = pci_resource_start(pdev, mmio_bar);
	DBG_MSG("fb aperture: 0x%llx/0x%llx, MMIO region: 0x%llx/0x%llx\n",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, aperture_bar),
		(अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, aperture_bar),
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(pdev, mmio_bar),
		(अचिन्हित दीर्घ दीर्घ)pci_resource_len(pdev, mmio_bar));

	/* Reserve the fb and MMIO regions */
	अगर (!request_mem_region(dinfo->aperture.physical, dinfo->aperture.size,
				INTELFB_MODULE_NAME)) अणु
		ERR_MSG("Cannot reserve FB region.\n");
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	dinfo->flag |= INTELFB_FB_ACQUIRED;

	अगर (!request_mem_region(dinfo->mmio_base_phys,
				INTEL_REG_SIZE,
				INTELFB_MODULE_NAME)) अणु
		ERR_MSG("Cannot reserve MMIO region.\n");
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	dinfo->flag |= INTELFB_MMIO_ACQUIRED;

	/* Get the chipset info. */
	dinfo->pci_chipset = pdev->device;

	अगर (पूर्णांकelfbhw_get_chipset(pdev, dinfo)) अणु
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	अगर (पूर्णांकelfbhw_get_memory(pdev, &aperture_size,&stolen_size)) अणु
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	INF_MSG("%02x:%02x.%d: %s, aperture size %dMB, "
		"stolen memory %dkB\n",
		pdev->bus->number, PCI_SLOT(pdev->devfn),
		PCI_FUNC(pdev->devfn), dinfo->name,
		BtoMB(aperture_size), BtoKB(stolen_size));

	/* Set these from the options. */
	dinfo->accel    = accel;
	dinfo->hwcursor = hwcursor;

	अगर (NOACCEL_CHIPSET(dinfo) && dinfo->accel == 1) अणु
		INF_MSG("Acceleration is not supported for the %s chipset.\n",
			dinfo->name);
		dinfo->accel = 0;
	पूर्ण

	/* Framebuffer parameters - Use all the stolen memory अगर >= vram */
	अगर (ROUND_UP_TO_PAGE(stolen_size) >= MB(vram)) अणु
		dinfo->fb.size = ROUND_UP_TO_PAGE(stolen_size);
		dinfo->fbmem_gart = 0;
	पूर्ण अन्यथा अणु
		dinfo->fb.size =  MB(vram);
		dinfo->fbmem_gart = 1;
	पूर्ण

	/* Allocate space क्रम the ring buffer and HW cursor अगर enabled. */
	अगर (dinfo->accel) अणु
		dinfo->ring.size = RINGBUFFER_SIZE;
		dinfo->ring_tail_mask = dinfo->ring.size - 1;
	पूर्ण
	अगर (dinfo->hwcursor)
		dinfo->cursor.size = HW_CURSOR_SIZE;

	/* Use agpgart to manage the GATT */
	अगर (!(bridge = agp_backend_acquire(pdev))) अणु
		ERR_MSG("cannot acquire agp\n");
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	/* get the current gatt info */
	अगर (agp_copy_info(bridge, &gtt_info)) अणु
		ERR_MSG("cannot get agp info\n");
		agp_backend_release(bridge);
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	अगर (MB(voffset) < stolen_size)
		offset = (stolen_size >> 12);
	अन्यथा
		offset = ROUND_UP_TO_PAGE(MB(voffset))/GTT_PAGE_SIZE;

	/* set the mem offsets - set them after the alपढ़ोy used pages */
	अगर (dinfo->accel)
		dinfo->ring.offset = offset + gtt_info.current_memory;
	अगर (dinfo->hwcursor)
		dinfo->cursor.offset = offset +
			+ gtt_info.current_memory + (dinfo->ring.size >> 12);
	अगर (dinfo->fbmem_gart)
		dinfo->fb.offset = offset +
			+ gtt_info.current_memory + (dinfo->ring.size >> 12)
			+ (dinfo->cursor.size >> 12);

	/* Allocate memories (which aren't stolen) */
	/* Map the fb and MMIO regions */
	/* ioremap only up to the end of used aperture */
	dinfo->aperture.भव = (u8 __iomem *)ioremap_wc
		(dinfo->aperture.physical, ((offset + dinfo->fb.offset) << 12)
		 + dinfo->fb.size);
	अगर (!dinfo->aperture.भव) अणु
		ERR_MSG("Cannot remap FB region.\n");
		agp_backend_release(bridge);
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	dinfo->mmio_base =
		(u8 __iomem *)ioremap(dinfo->mmio_base_phys,
					      INTEL_REG_SIZE);
	अगर (!dinfo->mmio_base) अणु
		ERR_MSG("Cannot remap MMIO region.\n");
		agp_backend_release(bridge);
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	अगर (dinfo->accel) अणु
		अगर (!(dinfo->gtt_ring_mem =
		      agp_allocate_memory(bridge, dinfo->ring.size >> 12,
					  AGP_NORMAL_MEMORY))) अणु
			ERR_MSG("cannot allocate ring buffer memory\n");
			agp_backend_release(bridge);
			cleanup(dinfo);
			वापस -ENOMEM;
		पूर्ण
		अगर (agp_bind_memory(dinfo->gtt_ring_mem,
				    dinfo->ring.offset)) अणु
			ERR_MSG("cannot bind ring buffer memory\n");
			agp_backend_release(bridge);
			cleanup(dinfo);
			वापस -EBUSY;
		पूर्ण
		dinfo->ring.physical = dinfo->aperture.physical
			+ (dinfo->ring.offset << 12);
		dinfo->ring.भव  = dinfo->aperture.भव
			+ (dinfo->ring.offset << 12);
		dinfo->ring_head = 0;
	पूर्ण
	अगर (dinfo->hwcursor) अणु
		agp_memtype = dinfo->mobile ? AGP_PHYSICAL_MEMORY
			: AGP_NORMAL_MEMORY;
		अगर (!(dinfo->gtt_cursor_mem =
		      agp_allocate_memory(bridge, dinfo->cursor.size >> 12,
					  agp_memtype))) अणु
			ERR_MSG("cannot allocate cursor memory\n");
			agp_backend_release(bridge);
			cleanup(dinfo);
			वापस -ENOMEM;
		पूर्ण
		अगर (agp_bind_memory(dinfo->gtt_cursor_mem,
				    dinfo->cursor.offset)) अणु
			ERR_MSG("cannot bind cursor memory\n");
			agp_backend_release(bridge);
			cleanup(dinfo);
			वापस -EBUSY;
		पूर्ण
		अगर (dinfo->mobile)
			dinfo->cursor.physical
				= dinfo->gtt_cursor_mem->physical;
		अन्यथा
			dinfo->cursor.physical = dinfo->aperture.physical
				+ (dinfo->cursor.offset << 12);
		dinfo->cursor.भव = dinfo->aperture.भव
			+ (dinfo->cursor.offset << 12);
	पूर्ण
	अगर (dinfo->fbmem_gart) अणु
		अगर (!(dinfo->gtt_fb_mem =
		      agp_allocate_memory(bridge, dinfo->fb.size >> 12,
					  AGP_NORMAL_MEMORY))) अणु
			WRN_MSG("cannot allocate framebuffer memory - use "
				"the stolen one\n");
			dinfo->fbmem_gart = 0;
		पूर्ण
		अगर (agp_bind_memory(dinfo->gtt_fb_mem,
				    dinfo->fb.offset)) अणु
			WRN_MSG("cannot bind framebuffer memory - use "
				"the stolen one\n");
			dinfo->fbmem_gart = 0;
		पूर्ण
	पूर्ण

	/* update framebuffer memory parameters */
	अगर (!dinfo->fbmem_gart)
		dinfo->fb.offset = 0;   /* starts at offset 0 */
	dinfo->fb.physical = dinfo->aperture.physical
		+ (dinfo->fb.offset << 12);
	dinfo->fb.भव = dinfo->aperture.भव + (dinfo->fb.offset << 12);
	dinfo->fb_start = dinfo->fb.offset << 12;

	/* release agpgart */
	agp_backend_release(bridge);

	अगर (mtrr)
		dinfo->wc_cookie = arch_phys_wc_add(dinfo->aperture.physical,
						    dinfo->aperture.size);

	DBG_MSG("fb: 0x%x(+ 0x%x)/0x%x (0x%p)\n",
		dinfo->fb.physical, dinfo->fb.offset, dinfo->fb.size,
		dinfo->fb.भव);
	DBG_MSG("MMIO: 0x%x/0x%x (0x%p)\n",
		dinfo->mmio_base_phys, INTEL_REG_SIZE,
		dinfo->mmio_base);
	DBG_MSG("ring buffer: 0x%x/0x%x (0x%p)\n",
		dinfo->ring.physical, dinfo->ring.size,
		dinfo->ring.भव);
	DBG_MSG("HW cursor: 0x%x/0x%x (0x%p) (offset 0x%x) (phys 0x%x)\n",
		dinfo->cursor.physical, dinfo->cursor.size,
		dinfo->cursor.भव, dinfo->cursor.offset,
		dinfo->cursor.physical);

	DBG_MSG("options: vram = %d, accel = %d, hwcursor = %d, fixed = %d, "
		"noinit = %d\n", vram, accel, hwcursor, fixed, noinit);
	DBG_MSG("options: mode = \"%s\"\n", mode ? mode : "");

	अगर (probeonly)
		bailout(dinfo);

	/*
	 * Check अगर the LVDS port or any DVO ports are enabled.  If so,
	 * करोn't allow mode चयनing
	 */
	dvo = पूर्णांकelfbhw_check_non_crt(dinfo);
	अगर (dvo) अणु
		dinfo->fixed_mode = 1;
		WRN_MSG("Non-CRT device is enabled ( ");
		i = 0;
		जबतक (dvo) अणु
			अगर (dvo & 1) अणु
				s = पूर्णांकelfbhw_dvo_to_string(1 << i);
				अगर (s)
					prपूर्णांकk("%s ", s);
			पूर्ण
			dvo >>= 1;
			++i;
		पूर्ण
		prपूर्णांकk(").  Disabling mode switching.\n");
	पूर्ण

	अगर (bailearly == 1)
		bailout(dinfo);

	अगर (FIXED_MODE(dinfo) &&
	    screen_info.orig_video_isVGA != VIDEO_TYPE_VLFB) अणु
		ERR_MSG("Video mode must be programmed at boot time.\n");
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	अगर (bailearly == 2)
		bailout(dinfo);

	/* Initialise dinfo and related data. */
	/* If an initial mode was programmed at boot समय, get its details. */
	अगर (screen_info.orig_video_isVGA == VIDEO_TYPE_VLFB)
		get_initial_mode(dinfo);

	अगर (bailearly == 3)
		bailout(dinfo);

	अगर (FIXED_MODE(dinfo))	/* remap fb address */
		update_dinfo(dinfo, &dinfo->initial_var);

	अगर (bailearly == 4)
		bailout(dinfo);


	अगर (पूर्णांकelfb_set_fbinfo(dinfo)) अणु
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	अगर (bailearly == 5)
		bailout(dinfo);

#अगर_घोषित CONFIG_FB_INTEL_I2C
	/* रेजिस्टर I2C bus */
	पूर्णांकelfb_create_i2c_busses(dinfo);
#पूर्ण_अगर

	अगर (bailearly == 6)
		bailout(dinfo);

	pci_set_drvdata(pdev, dinfo);

	/* Save the initial रेजिस्टर state. */
	i = पूर्णांकelfbhw_पढ़ो_hw_state(dinfo, &dinfo->save_state,
				    bailearly > 6 ? bailearly - 6 : 0);
	अगर (i != 0) अणु
		DBG_MSG("intelfbhw_read_hw_state returned %d\n", i);
		bailout(dinfo);
	पूर्ण

	पूर्णांकelfbhw_prपूर्णांक_hw_state(dinfo, &dinfo->save_state);

	अगर (bailearly == 18)
		bailout(dinfo);

	/* पढ़ो active pipe */
	dinfo->pipe = पूर्णांकelfbhw_active_pipe(&dinfo->save_state);

	/* Cursor initialisation */
	अगर (dinfo->hwcursor) अणु
		पूर्णांकelfbhw_cursor_init(dinfo);
		पूर्णांकelfbhw_cursor_reset(dinfo);
	पूर्ण

	अगर (bailearly == 19)
		bailout(dinfo);

	/* 2d acceleration init */
	अगर (dinfo->accel)
		पूर्णांकelfbhw_2d_start(dinfo);

	अगर (bailearly == 20)
		bailout(dinfo);

	अगर (noरेजिस्टर)
		bailout(dinfo);

	अगर (रेजिस्टर_framebuffer(dinfo->info) < 0) अणु
		ERR_MSG("Cannot register framebuffer.\n");
		cleanup(dinfo);
		वापस -ENODEV;
	पूर्ण

	dinfo->रेजिस्टरed = 1;
	dinfo->खोलो = 0;

	init_रुकोqueue_head(&dinfo->vsync.रुको);
	spin_lock_init(&dinfo->पूर्णांक_lock);
	dinfo->irq_flags = 0;
	dinfo->vsync.pan_display = 0;
	dinfo->vsync.pan_offset = 0;

	वापस 0;

err_out_pixmap:
	fb_dealloc_cmap(&info->cmap);
err_out_cmap:
	framebuffer_release(info);
	वापस -ENODEV;
पूर्ण

अटल व्योम पूर्णांकelfb_pci_unरेजिस्टर(काष्ठा pci_dev *pdev)
अणु
	काष्ठा पूर्णांकelfb_info *dinfo = pci_get_drvdata(pdev);

	DBG_MSG("intelfb_pci_unregister\n");

	अगर (!dinfo)
		वापस;

	cleanup(dinfo);
पूर्ण

/***************************************************************
 *                       helper functions                      *
 ***************************************************************/

__अंतरभूत__ पूर्णांक पूर्णांकelfb_var_to_depth(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	DBG_MSG("intelfb_var_to_depth: bpp: %d, green.length is %d\n",
		var->bits_per_pixel, var->green.length);

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		वापस (var->green.length == 6) ? 16 : 15;
	हाल 32:
		वापस 24;
	शेष:
		वापस var->bits_per_pixel;
	पूर्ण
पूर्ण


अटल __अंतरभूत__ पूर्णांक var_to_refresh(स्थिर काष्ठा fb_var_screeninfo *var)
अणु
	पूर्णांक xtot = var->xres + var->left_margin + var->right_margin +
		   var->hsync_len;
	पूर्णांक ytot = var->yres + var->upper_margin + var->lower_margin +
		   var->vsync_len;

	वापस (1000000000 / var->pixघड़ी * 1000 + 500) / xtot / ytot;
पूर्ण

/***************************************************************
 *                Various initialisation functions             *
 ***************************************************************/

अटल व्योम get_initial_mode(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	काष्ठा fb_var_screeninfo *var;
	पूर्णांक xtot, ytot;

	DBG_MSG("get_initial_mode\n");

	dinfo->initial_vga = 1;
	dinfo->initial_fb_base = screen_info.lfb_base;
	dinfo->initial_video_ram = screen_info.lfb_size * KB(64);
	dinfo->initial_pitch = screen_info.lfb_linelength;

	var = &dinfo->initial_var;
	स_रखो(var, 0, माप(*var));
	var->xres = screen_info.lfb_width;
	var->yres = screen_info.lfb_height;
	var->bits_per_pixel = screen_info.lfb_depth;
	चयन (screen_info.lfb_depth) अणु
	हाल 15:
		var->bits_per_pixel = 16;
		अवरोध;
	हाल 24:
		var->bits_per_pixel = 32;
		अवरोध;
	पूर्ण

	DBG_MSG("Initial info: FB is 0x%x/0x%x (%d kByte)\n",
		dinfo->initial_fb_base, dinfo->initial_video_ram,
		BtoKB(dinfo->initial_video_ram));

	DBG_MSG("Initial info: mode is %dx%d-%d (%d)\n",
		var->xres, var->yres, var->bits_per_pixel,
		dinfo->initial_pitch);

	/* Dummy timing values (assume 60Hz) */
	var->left_margin = (var->xres / 8) & 0xf8;
	var->right_margin = 32;
	var->upper_margin = 16;
	var->lower_margin = 4;
	var->hsync_len = (var->xres / 8) & 0xf8;
	var->vsync_len = 4;

	xtot = var->xres + var->left_margin +
		var->right_margin + var->hsync_len;
	ytot = var->yres + var->upper_margin +
		var->lower_margin + var->vsync_len;
	var->pixघड़ी = 10000000 / xtot * 1000 / ytot * 100 / 60;

	var->height = -1;
	var->width = -1;

	अगर (var->bits_per_pixel > 8) अणु
		var->red.offset = screen_info.red_pos;
		var->red.length = screen_info.red_size;
		var->green.offset = screen_info.green_pos;
		var->green.length = screen_info.green_size;
		var->blue.offset = screen_info.blue_pos;
		var->blue.length = screen_info.blue_size;
		var->transp.offset = screen_info.rsvd_pos;
		var->transp.length = screen_info.rsvd_size;
	पूर्ण अन्यथा अणु
		var->red.length = 8;
		var->green.length = 8;
		var->blue.length = 8;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकelfb_init_var(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	काष्ठा fb_var_screeninfo *var;
	पूर्णांक msrc = 0;

	DBG_MSG("intelfb_init_var\n");

	var = &dinfo->info->var;
	अगर (FIXED_MODE(dinfo)) अणु
	        स_नकल(var, &dinfo->initial_var,
		       माप(काष्ठा fb_var_screeninfo));
		msrc = 5;
	पूर्ण अन्यथा अणु
		स्थिर u8 *edid_s = fb_firmware_edid(&dinfo->pdev->dev);
		u8 *edid_d = शून्य;

		अगर (edid_s) अणु
			edid_d = kmemdup(edid_s, EDID_LENGTH, GFP_KERNEL);

			अगर (edid_d) अणु
				fb_edid_to_monspecs(edid_d,
						    &dinfo->info->monspecs);
				kमुक्त(edid_d);
			पूर्ण
		पूर्ण

		अगर (mode) अणु
			prपूर्णांकk("intelfb: Looking for mode in private "
			       "database\n");
			msrc = fb_find_mode(var, dinfo->info, mode,
					    dinfo->info->monspecs.modedb,
					    dinfo->info->monspecs.modedb_len,
					    शून्य, 0);

			अगर (msrc && msrc > 1) अणु
				prपूर्णांकk("intelfb: No mode in private database, "
				       "intelfb: looking for mode in global "
				       "database ");
				msrc = fb_find_mode(var, dinfo->info, mode,
						    शून्य, 0, शून्य, 0);

				अगर (msrc)
					msrc |= 8;
			पूर्ण

		पूर्ण

		अगर (!msrc)
			msrc = fb_find_mode(var, dinfo->info, PREFERRED_MODE,
					    शून्य, 0, शून्य, 0);
	पूर्ण

	अगर (!msrc) अणु
		ERR_MSG("Cannot find a suitable video mode.\n");
		वापस 1;
	पूर्ण

	INF_MSG("Initial video mode is %dx%d-%d@%d.\n", var->xres, var->yres,
		var->bits_per_pixel, var_to_refresh(var));

	DBG_MSG("Initial video mode is from %d.\n", msrc);

#अगर ALLOCATE_FOR_PANNING
	/* Allow use of half of the video ram क्रम panning */
	var->xres_भव = var->xres;
	var->yres_भव =
		dinfo->fb.size / 2 / (var->bits_per_pixel * var->xres);
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;
#अन्यथा
	var->yres_भव = var->yres;
#पूर्ण_अगर

	अगर (dinfo->accel)
		var->accel_flags |= FB_ACCELF_TEXT;
	अन्यथा
		var->accel_flags &= ~FB_ACCELF_TEXT;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_set_fbinfo(काष्ठा पूर्णांकelfb_info *dinfo)
अणु
	काष्ठा fb_info *info = dinfo->info;

	DBG_MSG("intelfb_set_fbinfo\n");

	info->flags = FBINFO_FLAG_DEFAULT;
	info->fbops = &पूर्णांकel_fb_ops;
	info->pseuकरो_palette = dinfo->pseuकरो_palette;

	info->pixmap.size = 64*1024;
	info->pixmap.buf_align = 8;
	info->pixmap.access_align = 32;
	info->pixmap.flags = FB_PIXMAP_SYSTEM;

	अगर (पूर्णांकelfb_init_var(dinfo))
		वापस 1;

	info->pixmap.scan_align = 1;
	म_नकल(info->fix.id, dinfo->name);
	info->fix.smem_start = dinfo->fb.physical;
	info->fix.smem_len = dinfo->fb.size;
	info->fix.type = FB_TYPE_PACKED_PIXELS;
	info->fix.type_aux = 0;
	info->fix.xpanstep = 8;
	info->fix.ypanstep = 1;
	info->fix.ywrapstep = 0;
	info->fix.mmio_start = dinfo->mmio_base_phys;
	info->fix.mmio_len = INTEL_REG_SIZE;
	info->fix.accel = FB_ACCEL_I830;
	update_dinfo(dinfo, &info->var);

	वापस 0;
पूर्ण

/* Update dinfo to match the active video mode. */
अटल व्योम update_dinfo(काष्ठा पूर्णांकelfb_info *dinfo,
			 काष्ठा fb_var_screeninfo *var)
अणु
	DBG_MSG("update_dinfo\n");

	dinfo->bpp = var->bits_per_pixel;
	dinfo->depth = पूर्णांकelfb_var_to_depth(var);
	dinfo->xres = var->xres;
	dinfo->yres = var->xres;
	dinfo->pixघड़ी = var->pixघड़ी;

	dinfo->info->fix.visual = dinfo->visual;
	dinfo->info->fix.line_length = dinfo->pitch;

	चयन (dinfo->bpp) अणु
	हाल 8:
		dinfo->visual = FB_VISUAL_PSEUDOCOLOR;
		dinfo->pitch = var->xres_भव;
		अवरोध;
	हाल 16:
		dinfo->visual = FB_VISUAL_TRUECOLOR;
		dinfo->pitch = var->xres_भव * 2;
		अवरोध;
	हाल 32:
		dinfo->visual = FB_VISUAL_TRUECOLOR;
		dinfo->pitch = var->xres_भव * 4;
		अवरोध;
	पूर्ण

	/* Make sure the line length is a aligned correctly. */
	अगर (IS_I9XX(dinfo))
		dinfo->pitch = ROUND_UP_TO(dinfo->pitch, STRIDE_ALIGNMENT_I9XX);
	अन्यथा
		dinfo->pitch = ROUND_UP_TO(dinfo->pitch, STRIDE_ALIGNMENT);

	अगर (FIXED_MODE(dinfo))
		dinfo->pitch = dinfo->initial_pitch;

	dinfo->info->screen_base = (अक्षर __iomem *)dinfo->fb.भव;
	dinfo->info->fix.line_length = dinfo->pitch;
	dinfo->info->fix.visual = dinfo->visual;
पूर्ण

/* fbops functions */

/***************************************************************
 *                       fbdev पूर्णांकerface                       *
 ***************************************************************/

अटल पूर्णांक पूर्णांकelfb_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);

	अगर (user)
		dinfo->खोलो++;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);

	अगर (user) अणु
		dinfo->खोलो--;
		msleep(1);
		अगर (!dinfo->खोलो)
			पूर्णांकelfbhw_disable_irq(dinfo);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_check_var(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	पूर्णांक change_var = 0;
	काष्ठा fb_var_screeninfo v;
	काष्ठा पूर्णांकelfb_info *dinfo;
	अटल पूर्णांक first = 1;
	पूर्णांक i;
	/* Good pitches to allow tiling.  Don't care about pitches < 1024. */
	अटल स्थिर पूर्णांक pitches[] = अणु
		128 * 8,
		128 * 16,
		128 * 32,
		128 * 64,
		0
	पूर्ण;

	DBG_MSG("intelfb_check_var: accel_flags is %d\n", var->accel_flags);

	dinfo = GET_DINFO(info);

	/* update the pitch */
	अगर (पूर्णांकelfbhw_validate_mode(dinfo, var) != 0)
		वापस -EINVAL;

	v = *var;

	क्रम (i = 0; pitches[i] != 0; i++) अणु
		अगर (pitches[i] >= v.xres_भव) अणु
			v.xres_भव = pitches[i];
			अवरोध;
		पूर्ण
	पूर्ण

	/* Check क्रम a supported bpp. */
	अगर (v.bits_per_pixel <= 8)
		v.bits_per_pixel = 8;
	अन्यथा अगर (v.bits_per_pixel <= 16) अणु
		अगर (v.bits_per_pixel == 16)
			v.green.length = 6;
		v.bits_per_pixel = 16;
	पूर्ण अन्यथा अगर (v.bits_per_pixel <= 32)
		v.bits_per_pixel = 32;
	अन्यथा
		वापस -EINVAL;

	change_var = ((info->var.xres != var->xres) ||
		      (info->var.yres != var->yres) ||
		      (info->var.xres_भव != var->xres_भव) ||
		      (info->var.yres_भव != var->yres_भव) ||
		      (info->var.bits_per_pixel != var->bits_per_pixel) ||
		      स_भेद(&info->var.red, &var->red, माप(var->red)) ||
		      स_भेद(&info->var.green, &var->green,
			     माप(var->green)) ||
		      स_भेद(&info->var.blue, &var->blue, माप(var->blue)));

	अगर (FIXED_MODE(dinfo) &&
	    (change_var ||
	     var->yres_भव > dinfo->initial_var.yres_भव ||
	     var->yres_भव < dinfo->initial_var.yres ||
	     var->xoffset || var->nonstd)) अणु
		अगर (first) अणु
			ERR_MSG("Changing the video mode is not supported.\n");
			first = 0;
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	चयन (पूर्णांकelfb_var_to_depth(&v)) अणु
	हाल 8:
		v.red.offset = v.green.offset = v.blue.offset = 0;
		v.red.length = v.green.length = v.blue.length = 8;
		v.transp.offset = v.transp.length = 0;
		अवरोध;
	हाल 15:
		v.red.offset = 10;
		v.green.offset = 5;
		v.blue.offset = 0;
		v.red.length = v.green.length = v.blue.length = 5;
		v.transp.offset = v.transp.length = 0;
		अवरोध;
	हाल 16:
		v.red.offset = 11;
		v.green.offset = 5;
		v.blue.offset = 0;
		v.red.length = 5;
		v.green.length = 6;
		v.blue.length = 5;
		v.transp.offset = v.transp.length = 0;
		अवरोध;
	हाल 24:
		v.red.offset = 16;
		v.green.offset = 8;
		v.blue.offset = 0;
		v.red.length = v.green.length = v.blue.length = 8;
		v.transp.offset = v.transp.length = 0;
		अवरोध;
	हाल 32:
		v.red.offset = 16;
		v.green.offset = 8;
		v.blue.offset = 0;
		v.red.length = v.green.length = v.blue.length = 8;
		v.transp.offset = 24;
		v.transp.length = 8;
		अवरोध;
	पूर्ण

	अगर (v.xoffset > v.xres_भव - v.xres)
		v.xoffset = v.xres_भव - v.xres;
	अगर (v.yoffset > v.yres_भव - v.yres)
		v.yoffset = v.yres_भव - v.yres;

	v.red.msb_right = v.green.msb_right = v.blue.msb_right =
			  v.transp.msb_right = 0;

        *var = v;

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा पूर्णांकelfb_hwstate *hw;
        काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);

	अगर (FIXED_MODE(dinfo)) अणु
		ERR_MSG("Changing the video mode is not supported.\n");
		वापस -EINVAL;
	पूर्ण

	hw = kदो_स्मृति(माप(*hw), GFP_ATOMIC);
	अगर (!hw)
		वापस -ENOMEM;

	DBG_MSG("intelfb_set_par (%dx%d-%d)\n", info->var.xres,
		info->var.yres, info->var.bits_per_pixel);

	/*
	 * Disable VCO prior to timing रेजिस्टर change.
	 */
	OUTREG(DPLL_A, INREG(DPLL_A) & ~DPLL_VCO_ENABLE);

	पूर्णांकelfb_blank(FB_BLANK_POWERDOWN, info);

	अगर (ACCEL(dinfo, info))
		पूर्णांकelfbhw_2d_stop(dinfo);

	स_नकल(hw, &dinfo->save_state, माप(*hw));
	अगर (पूर्णांकelfbhw_mode_to_hw(dinfo, hw, &info->var))
		जाओ invalid_mode;
	अगर (पूर्णांकelfbhw_program_mode(dinfo, hw, 0))
		जाओ invalid_mode;

#अगर REGDUMP > 0
	पूर्णांकelfbhw_पढ़ो_hw_state(dinfo, hw, 0);
	पूर्णांकelfbhw_prपूर्णांक_hw_state(dinfo, hw);
#पूर्ण_अगर

	update_dinfo(dinfo, &info->var);

	अगर (ACCEL(dinfo, info))
		पूर्णांकelfbhw_2d_start(dinfo);

	पूर्णांकelfb_pan_display(&info->var, info);

	पूर्णांकelfb_blank(FB_BLANK_UNBLANK, info);

	अगर (ACCEL(dinfo, info)) अणु
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN |
		FBINFO_HWACCEL_COPYAREA | FBINFO_HWACCEL_FILLRECT |
		FBINFO_HWACCEL_IMAGEBLIT;
	पूर्ण अन्यथा
		info->flags = FBINFO_DEFAULT | FBINFO_HWACCEL_YPAN;

	kमुक्त(hw);
	वापस 0;
invalid_mode:
	kमुक्त(hw);
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			     अचिन्हित blue, अचिन्हित transp,
			     काष्ठा fb_info *info)
अणु
	काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);

#अगर VERBOSE > 0
	DBG_MSG("intelfb_setcolreg: regno %d, depth %d\n", regno, dinfo->depth);
#पूर्ण_अगर

	अगर (regno > 255)
		वापस 1;

	अगर (dinfo->depth == 8) अणु
		red >>= 8;
		green >>= 8;
		blue >>= 8;

		पूर्णांकelfbhw_setcolreg(dinfo, regno, red, green, blue,
				    transp);
	पूर्ण

	अगर (regno < 16) अणु
		चयन (dinfo->depth) अणु
		हाल 15:
			dinfo->pseuकरो_palette[regno] = ((red & 0xf800) >>  1) |
				((green & 0xf800) >>  6) |
				((blue & 0xf800) >> 11);
			अवरोध;
		हाल 16:
			dinfo->pseuकरो_palette[regno] = (red & 0xf800) |
				((green & 0xfc00) >>  5) |
				((blue  & 0xf800) >> 11);
			अवरोध;
		हाल 24:
			dinfo->pseuकरो_palette[regno] = ((red & 0xff00) << 8) |
				(green & 0xff00) |
				((blue  & 0xff00) >> 8);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_blank(पूर्णांक blank, काष्ठा fb_info *info)
अणु
	पूर्णांकelfbhw_करो_blank(blank, info);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_pan_display(काष्ठा fb_var_screeninfo *var,
			       काष्ठा fb_info *info)
अणु
	पूर्णांकelfbhw_pan_display(var, info);
	वापस 0;
पूर्ण

/* When/अगर we have our own ioctls. */
अटल पूर्णांक पूर्णांकelfb_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			 अचिन्हित दीर्घ arg)
अणु
	पूर्णांक retval = 0;
	काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);
	u32 pipe = 0;

	चयन (cmd) अणु
		हाल FBIO_WAITFORVSYNC:
			अगर (get_user(pipe, (__u32 __user *)arg))
				वापस -EFAULT;

			retval = पूर्णांकelfbhw_रुको_क्रम_vsync(dinfo, pipe);
			अवरोध;
		शेष:
			अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम पूर्णांकelfb_fillrect (काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_fillrect *rect)
अणु
        काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);
	u32 rop, color;

#अगर VERBOSE > 0
	DBG_MSG("intelfb_fillrect\n");
#पूर्ण_अगर

	अगर (!ACCEL(dinfo, info) || dinfo->depth == 4) अणु
		cfb_fillrect(info, rect);
		वापस;
	पूर्ण

	अगर (rect->rop == ROP_COPY)
		rop = PAT_ROP_GXCOPY;
	अन्यथा /* ROP_XOR */
		rop = PAT_ROP_GXXOR;

	अगर (dinfo->depth != 8)
		color = dinfo->pseuकरो_palette[rect->color];
	अन्यथा
		color = rect->color;

	पूर्णांकelfbhw_करो_fillrect(dinfo, rect->dx, rect->dy,
			      rect->width, rect->height, color,
			      dinfo->pitch, info->var.bits_per_pixel,
			      rop);
पूर्ण

अटल व्योम पूर्णांकelfb_copyarea(काष्ठा fb_info *info,
			     स्थिर काष्ठा fb_copyarea *region)
अणु
        काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);

#अगर VERBOSE > 0
	DBG_MSG("intelfb_copyarea\n");
#पूर्ण_अगर

	अगर (!ACCEL(dinfo, info) || dinfo->depth == 4) अणु
		cfb_copyarea(info, region);
		वापस;
	पूर्ण

	पूर्णांकelfbhw_करो_bitblt(dinfo, region->sx, region->sy, region->dx,
			    region->dy, region->width, region->height,
			    dinfo->pitch, info->var.bits_per_pixel);
पूर्ण

अटल व्योम पूर्णांकelfb_imageblit(काष्ठा fb_info *info,
			      स्थिर काष्ठा fb_image *image)
अणु
        काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);
	u32 fgcolor, bgcolor;

#अगर VERBOSE > 0
	DBG_MSG("intelfb_imageblit\n");
#पूर्ण_अगर

	अगर (!ACCEL(dinfo, info) || dinfo->depth == 4
	    || image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	अगर (dinfo->depth != 8) अणु
		fgcolor = dinfo->pseuकरो_palette[image->fg_color];
		bgcolor = dinfo->pseuकरो_palette[image->bg_color];
	पूर्ण अन्यथा अणु
		fgcolor = image->fg_color;
		bgcolor = image->bg_color;
	पूर्ण

	अगर (!पूर्णांकelfbhw_करो_drawglyph(dinfo, fgcolor, bgcolor, image->width,
				    image->height, image->data,
				    image->dx, image->dy,
				    dinfo->pitch, info->var.bits_per_pixel)) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण
पूर्ण

अटल पूर्णांक पूर्णांकelfb_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
        काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);
	u32 physical;
#अगर VERBOSE > 0
	DBG_MSG("intelfb_cursor\n");
#पूर्ण_अगर

	अगर (!dinfo->hwcursor)
		वापस -ENODEV;

	पूर्णांकelfbhw_cursor_hide(dinfo);

	/* If XFree समाप्तed the cursor - restore it */
	physical = (dinfo->mobile || IS_I9XX(dinfo)) ? dinfo->cursor.physical :
		   (dinfo->cursor.offset << 12);

	अगर (INREG(CURSOR_A_BASEADDR) != physical) अणु
		u32 fg, bg;

		DBG_MSG("the cursor was killed - restore it !!\n");
		DBG_MSG("size %d, %d   pos %d, %d\n",
			cursor->image.width, cursor->image.height,
			cursor->image.dx, cursor->image.dy);

		पूर्णांकelfbhw_cursor_init(dinfo);
		पूर्णांकelfbhw_cursor_reset(dinfo);
		पूर्णांकelfbhw_cursor_setpos(dinfo, cursor->image.dx,
					cursor->image.dy);

		अगर (dinfo->depth != 8) अणु
			fg =dinfo->pseuकरो_palette[cursor->image.fg_color];
			bg =dinfo->pseuकरो_palette[cursor->image.bg_color];
		पूर्ण अन्यथा अणु
			fg = cursor->image.fg_color;
			bg = cursor->image.bg_color;
		पूर्ण
		पूर्णांकelfbhw_cursor_setcolor(dinfo, bg, fg);
		पूर्णांकelfbhw_cursor_load(dinfo, cursor->image.width,
				      cursor->image.height,
				      dinfo->cursor_src);

		अगर (cursor->enable)
			पूर्णांकelfbhw_cursor_show(dinfo);
		वापस 0;
	पूर्ण

	अगर (cursor->set & FB_CUR_SETPOS) अणु
		u32 dx, dy;

		dx = cursor->image.dx - info->var.xoffset;
		dy = cursor->image.dy - info->var.yoffset;

		पूर्णांकelfbhw_cursor_setpos(dinfo, dx, dy);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETSIZE) अणु
		अगर (cursor->image.width > 64 || cursor->image.height > 64)
			वापस -ENXIO;

		पूर्णांकelfbhw_cursor_reset(dinfo);
	पूर्ण

	अगर (cursor->set & FB_CUR_SETCMAP) अणु
		u32 fg, bg;

		अगर (dinfo->depth != 8) अणु
			fg = dinfo->pseuकरो_palette[cursor->image.fg_color];
			bg = dinfo->pseuकरो_palette[cursor->image.bg_color];
		पूर्ण अन्यथा अणु
			fg = cursor->image.fg_color;
			bg = cursor->image.bg_color;
		पूर्ण

		पूर्णांकelfbhw_cursor_setcolor(dinfo, bg, fg);
	पूर्ण

	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETIMAGE)) अणु
		u32 s_pitch = (ROUND_UP_TO(cursor->image.width, 8) / 8);
		u32 size = s_pitch * cursor->image.height;
		u8 *dat = (u8 *) cursor->image.data;
		u8 *msk = (u8 *) cursor->mask;
		u8 src[64];
		u32 i;

		अगर (cursor->image.depth != 1)
			वापस -ENXIO;

		चयन (cursor->rop) अणु
		हाल ROP_XOR:
			क्रम (i = 0; i < size; i++)
				src[i] = dat[i] ^ msk[i];
			अवरोध;
		हाल ROP_COPY:
		शेष:
			क्रम (i = 0; i < size; i++)
				src[i] = dat[i] & msk[i];
			अवरोध;
		पूर्ण

		/* save the biपंचांगap to restore it when XFree will
		   make the cursor dirty */
		स_नकल(dinfo->cursor_src, src, size);

		पूर्णांकelfbhw_cursor_load(dinfo, cursor->image.width,
				      cursor->image.height, src);
	पूर्ण

	अगर (cursor->enable)
		पूर्णांकelfbhw_cursor_show(dinfo);

	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकelfb_sync(काष्ठा fb_info *info)
अणु
        काष्ठा पूर्णांकelfb_info *dinfo = GET_DINFO(info);

#अगर VERBOSE > 0
	DBG_MSG("intelfb_sync\n");
#पूर्ण_अगर

	अगर (dinfo->ring_lockup)
		वापस 0;

	पूर्णांकelfbhw_करो_sync(dinfo);
	वापस 0;
पूर्ण

