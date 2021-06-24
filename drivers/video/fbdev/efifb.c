<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Framebuffer driver क्रम EFI/UEFI based प्रणाली
 *
 * (c) 2006 Edgar Hucek <gimli@dark-green.com>
 * Original efi driver written by Gerd Knorr <kraxel@goldbach.in-berlin.de>
 *
 */

#समावेश <linux/kernel.h>
#समावेश <linux/efi.h>
#समावेश <linux/efi-bgrt.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/screen_info.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <video/vga.h>
#समावेश <यंत्र/efi.h>
#समावेश <drm/drm_utils.h> /* For drm_get_panel_orientation_quirk */
#समावेश <drm/drm_connector.h>  /* For DRM_MODE_PANEL_ORIENTATION_* */

काष्ठा bmp_file_header अणु
	u16 id;
	u32 file_size;
	u32 reserved;
	u32 biपंचांगap_offset;
पूर्ण __packed;

काष्ठा bmp_dib_header अणु
	u32 dib_header_size;
	s32 width;
	s32 height;
	u16 planes;
	u16 bpp;
	u32 compression;
	u32 biपंचांगap_size;
	u32 horz_resolution;
	u32 vert_resolution;
	u32 colors_used;
	u32 colors_important;
पूर्ण __packed;

अटल bool use_bgrt = true;
अटल bool request_mem_succeeded = false;
अटल u64 mem_flags = EFI_MEMORY_WC | EFI_MEMORY_UC;

अटल काष्ठा fb_var_screeninfo efअगरb_defined = अणु
	.activate		= FB_ACTIVATE_NOW,
	.height			= -1,
	.width			= -1,
	.right_margin		= 32,
	.upper_margin		= 16,
	.lower_margin		= 4,
	.vsync_len		= 4,
	.vmode			= FB_VMODE_NONINTERLACED,
पूर्ण;

अटल काष्ठा fb_fix_screeninfo efअगरb_fix = अणु
	.id			= "EFI VGA",
	.type			= FB_TYPE_PACKED_PIXELS,
	.accel			= FB_ACCEL_NONE,
	.visual			= FB_VISUAL_TRUECOLOR,
पूर्ण;

अटल पूर्णांक efअगरb_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			   अचिन्हित blue, अचिन्हित transp,
			   काष्ठा fb_info *info)
अणु
	/*
	 *  Set a single color रेजिस्टर. The values supplied are
	 *  alपढ़ोy rounded करोwn to the hardware's capabilities
	 *  (according to the entries in the `var' काष्ठाure). Return
	 *  != 0 क्रम invalid regno.
	 */

	अगर (regno >= info->cmap.len)
		वापस 1;

	अगर (regno < 16) अणु
		red   >>= 16 - info->var.red.length;
		green >>= 16 - info->var.green.length;
		blue  >>= 16 - info->var.blue.length;
		((u32 *)(info->pseuकरो_palette))[regno] =
			(red   << info->var.red.offset)   |
			(green << info->var.green.offset) |
			(blue  << info->var.blue.offset);
	पूर्ण
	वापस 0;
पूर्ण

/*
 * If fbcon deffered console takeover is configured, the पूर्णांकent is क्रम the
 * framebuffer to show the boot graphics (e.g. venकरोr logo) until there is some
 * (error) message to display. But the boot graphics may have been destroyed by
 * e.g. option ROM output, detect this and restore the boot graphics.
 */
#अगर defined CONFIG_FRAMEBUFFER_CONSOLE_DEFERRED_TAKEOVER && \
    defined CONFIG_ACPI_BGRT
अटल व्योम efअगरb_copy_bmp(u8 *src, u32 *dst, पूर्णांक width, काष्ठा screen_info *si)
अणु
	u8 r, g, b;

	जबतक (width--) अणु
		b = *src++;
		g = *src++;
		r = *src++;
		*dst++ = (r << si->red_pos)   |
			 (g << si->green_pos) |
			 (b << si->blue_pos);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_X86
/*
 * On x86 some firmwares use a low non native resolution क्रम the display when
 * they have shown some text messages. While keeping the bgrt filled with info
 * क्रम the native resolution. If the bgrt image पूर्णांकended क्रम the native
 * resolution still fits, it will be displayed very बंद to the right edge of
 * the display looking quite bad. This function checks क्रम this.
 */
अटल bool efअगरb_bgrt_sanity_check(काष्ठा screen_info *si, u32 bmp_width)
अणु
	/*
	 * All x86 firmwares horizontally center the image (the yoffset
	 * calculations dअगरfer between boards, but xoffset is predictable).
	 */
	u32 expected_xoffset = (si->lfb_width - bmp_width) / 2;

	वापस bgrt_tab.image_offset_x == expected_xoffset;
पूर्ण
#अन्यथा
अटल bool efअगरb_bgrt_sanity_check(काष्ठा screen_info *si, u32 bmp_width)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर

अटल व्योम efअगरb_show_boot_graphics(काष्ठा fb_info *info)
अणु
	u32 bmp_width, bmp_height, bmp_pitch, dst_x, y, src_y;
	काष्ठा screen_info *si = &screen_info;
	काष्ठा bmp_file_header *file_header;
	काष्ठा bmp_dib_header *dib_header;
	व्योम *bgrt_image = शून्य;
	u8 *dst = info->screen_base;

	अगर (!use_bgrt)
		वापस;

	अगर (!bgrt_tab.image_address) अणु
		pr_info("efifb: No BGRT, not showing boot graphics\n");
		वापस;
	पूर्ण

	अगर (bgrt_tab.status & 0x06) अणु
		pr_info("efifb: BGRT rotation bits set, not showing boot graphics\n");
		वापस;
	पूर्ण

	/* Aव्योम flashing the logo अगर we're going to prपूर्णांक std probe messages */
	अगर (console_loglevel > CONSOLE_LOGLEVEL_QUIET)
		वापस;

	/* bgrt_tab.status is unreliable, so we करोn't check it */

	अगर (si->lfb_depth != 32) अणु
		pr_info("efifb: not 32 bits, not showing boot graphics\n");
		वापस;
	पूर्ण

	bgrt_image = memremap(bgrt_tab.image_address, bgrt_image_size,
			      MEMREMAP_WB);
	अगर (!bgrt_image) अणु
		pr_warn("efifb: Ignoring BGRT: failed to map image memory\n");
		वापस;
	पूर्ण

	अगर (bgrt_image_size < (माप(*file_header) + माप(*dib_header)))
		जाओ error;

	file_header = bgrt_image;
	अगर (file_header->id != 0x4d42 || file_header->reserved != 0)
		जाओ error;

	dib_header = bgrt_image + माप(*file_header);
	अगर (dib_header->dib_header_size != 40 || dib_header->width < 0 ||
	    dib_header->planes != 1 || dib_header->bpp != 24 ||
	    dib_header->compression != 0)
		जाओ error;

	bmp_width = dib_header->width;
	bmp_height = असल(dib_header->height);
	bmp_pitch = round_up(3 * bmp_width, 4);

	अगर ((file_header->biपंचांगap_offset + bmp_pitch * bmp_height) >
				bgrt_image_size)
		जाओ error;

	अगर ((bgrt_tab.image_offset_x + bmp_width) > si->lfb_width ||
	    (bgrt_tab.image_offset_y + bmp_height) > si->lfb_height)
		जाओ error;

	अगर (!efअगरb_bgrt_sanity_check(si, bmp_width))
		जाओ error;

	pr_info("efifb: showing boot graphics\n");

	क्रम (y = 0; y < si->lfb_height; y++, dst += si->lfb_linelength) अणु
		/* Only background? */
		अगर (y < bgrt_tab.image_offset_y ||
		    y >= (bgrt_tab.image_offset_y + bmp_height)) अणु
			स_रखो(dst, 0, 4 * si->lfb_width);
			जारी;
		पूर्ण

		src_y = y - bgrt_tab.image_offset_y;
		/* Positive header height means upside करोwn row order */
		अगर (dib_header->height > 0)
			src_y = (bmp_height - 1) - src_y;

		स_रखो(dst, 0, bgrt_tab.image_offset_x * 4);
		dst_x = bgrt_tab.image_offset_x;
		efअगरb_copy_bmp(bgrt_image + file_header->biपंचांगap_offset +
					    src_y * bmp_pitch,
			       (u32 *)dst + dst_x, bmp_width, si);
		dst_x += bmp_width;
		स_रखो((u32 *)dst + dst_x, 0, (si->lfb_width - dst_x) * 4);
	पूर्ण

	memunmap(bgrt_image);
	वापस;

error:
	memunmap(bgrt_image);
	pr_warn("efifb: Ignoring BGRT: unexpected or invalid BMP data\n");
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम efअगरb_show_boot_graphics(काष्ठा fb_info *info) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम efअगरb_destroy(काष्ठा fb_info *info)
अणु
	अगर (info->screen_base) अणु
		अगर (mem_flags & (EFI_MEMORY_UC | EFI_MEMORY_WC))
			iounmap(info->screen_base);
		अन्यथा
			memunmap(info->screen_base);
	पूर्ण
	अगर (request_mem_succeeded)
		release_mem_region(info->apertures->ranges[0].base,
				   info->apertures->ranges[0].size);
	fb_dealloc_cmap(&info->cmap);
पूर्ण

अटल स्थिर काष्ठा fb_ops efअगरb_ops = अणु
	.owner		= THIS_MODULE,
	.fb_destroy	= efअगरb_destroy,
	.fb_setcolreg	= efअगरb_setcolreg,
	.fb_fillrect	= cfb_fillrect,
	.fb_copyarea	= cfb_copyarea,
	.fb_imageblit	= cfb_imageblit,
पूर्ण;

अटल पूर्णांक efअगरb_setup(अक्षर *options)
अणु
	अक्षर *this_opt;

	अगर (options && *options) अणु
		जबतक ((this_opt = strsep(&options, ",")) != शून्य) अणु
			अगर (!*this_opt) जारी;

			efअगरb_setup_from_dmi(&screen_info, this_opt);

			अगर (!म_भेदन(this_opt, "base:", 5))
				screen_info.lfb_base = simple_म_से_अदीर्घ(this_opt+5, शून्य, 0);
			अन्यथा अगर (!म_भेदन(this_opt, "stride:", 7))
				screen_info.lfb_linelength = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0) * 4;
			अन्यथा अगर (!म_भेदन(this_opt, "height:", 7))
				screen_info.lfb_height = simple_म_से_अदीर्घ(this_opt+7, शून्य, 0);
			अन्यथा अगर (!म_भेदन(this_opt, "width:", 6))
				screen_info.lfb_width = simple_म_से_अदीर्घ(this_opt+6, शून्य, 0);
			अन्यथा अगर (!म_भेद(this_opt, "nowc"))
				mem_flags &= ~EFI_MEMORY_WC;
			अन्यथा अगर (!म_भेद(this_opt, "nobgrt"))
				use_bgrt = false;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत bool fb_base_is_valid(व्योम)
अणु
	अगर (screen_info.lfb_base)
		वापस true;

	अगर (!(screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE))
		वापस false;

	अगर (screen_info.ext_lfb_base)
		वापस true;

	वापस false;
पूर्ण

#घोषणा efअगरb_attr_decl(name, fmt)					\
अटल sमाप_प्रकार name##_show(काष्ठा device *dev,				\
			   काष्ठा device_attribute *attr,		\
			   अक्षर *buf)					\
अणु									\
	वापस प्र_लिखो(buf, fmt "\n", (screen_info.lfb_##name));	\
पूर्ण									\
अटल DEVICE_ATTR_RO(name)

efअगरb_attr_decl(base, "0x%x");
efअगरb_attr_decl(linelength, "%u");
efअगरb_attr_decl(height, "%u");
efअगरb_attr_decl(width, "%u");
efअगरb_attr_decl(depth, "%u");

अटल काष्ठा attribute *efअगरb_attrs[] = अणु
	&dev_attr_base.attr,
	&dev_attr_linelength.attr,
	&dev_attr_width.attr,
	&dev_attr_height.attr,
	&dev_attr_depth.attr,
	शून्य
पूर्ण;
ATTRIBUTE_GROUPS(efअगरb);

अटल bool pci_dev_disabled;	/* FB base matches BAR of a disabled device */

अटल काष्ठा pci_dev *efअगरb_pci_dev;	/* dev with BAR covering the efअगरb */
अटल काष्ठा resource *bar_resource;
अटल u64 bar_offset;

अटल पूर्णांक efअगरb_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा fb_info *info;
	पूर्णांक err, orientation;
	अचिन्हित पूर्णांक size_vmode;
	अचिन्हित पूर्णांक size_remap;
	अचिन्हित पूर्णांक माप_प्रकारotal;
	अक्षर *option = शून्य;
	efi_memory_desc_t md;

	अगर (screen_info.orig_video_isVGA != VIDEO_TYPE_EFI || pci_dev_disabled)
		वापस -ENODEV;

	अगर (fb_get_options("efifb", &option))
		वापस -ENODEV;
	efअगरb_setup(option);

	/* We करोn't get linelength from UGA Draw Protocol, only from
	 * EFI Graphics Protocol.  So अगर it's not in DMI, and it's not
	 * passed in from the user, we really can't use the framebuffer.
	 */
	अगर (!screen_info.lfb_linelength)
		वापस -ENODEV;

	अगर (!screen_info.lfb_depth)
		screen_info.lfb_depth = 32;
	अगर (!screen_info.pages)
		screen_info.pages = 1;
	अगर (!fb_base_is_valid()) अणु
		prपूर्णांकk(KERN_DEBUG "efifb: invalid framebuffer address\n");
		वापस -ENODEV;
	पूर्ण
	prपूर्णांकk(KERN_INFO "efifb: probing for efifb\n");

	/* just assume they're all unset अगर any are */
	अगर (!screen_info.blue_size) अणु
		screen_info.blue_size = 8;
		screen_info.blue_pos = 0;
		screen_info.green_size = 8;
		screen_info.green_pos = 8;
		screen_info.red_size = 8;
		screen_info.red_pos = 16;
		screen_info.rsvd_size = 8;
		screen_info.rsvd_pos = 24;
	पूर्ण

	efअगरb_fix.smem_start = screen_info.lfb_base;

	अगर (screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE) अणु
		u64 ext_lfb_base;

		ext_lfb_base = (u64)(अचिन्हित दीर्घ)screen_info.ext_lfb_base << 32;
		efअगरb_fix.smem_start |= ext_lfb_base;
	पूर्ण

	अगर (bar_resource &&
	    bar_resource->start + bar_offset != efअगरb_fix.smem_start) अणु
		dev_info(&efअगरb_pci_dev->dev,
			 "BAR has moved, updating efifb address\n");
		efअगरb_fix.smem_start = bar_resource->start + bar_offset;
	पूर्ण

	efअगरb_defined.bits_per_pixel = screen_info.lfb_depth;
	efअगरb_defined.xres = screen_info.lfb_width;
	efअगरb_defined.yres = screen_info.lfb_height;
	efअगरb_fix.line_length = screen_info.lfb_linelength;

	/*   size_vmode -- that is the amount of memory needed क्रम the
	 *                 used video mode, i.e. the minimum amount of
	 *                 memory we need. */
	size_vmode = efअगरb_defined.yres * efअगरb_fix.line_length;

	/*   माप_प्रकारotal -- all video memory we have. Used क्रम
	 *                 entries, ressource allocation and bounds
	 *                 checking. */
	माप_प्रकारotal = screen_info.lfb_size;
	अगर (माप_प्रकारotal < size_vmode)
		माप_प्रकारotal = size_vmode;

	/*   size_remap -- the amount of video memory we are going to
	 *                 use क्रम efअगरb.  With modern cards it is no
	 *                 option to simply use माप_प्रकारotal as that
	 *                 wastes plenty of kernel address space. */
	size_remap  = size_vmode * 2;
	अगर (size_remap > माप_प्रकारotal)
		size_remap = माप_प्रकारotal;
	अगर (size_remap % PAGE_SIZE)
		size_remap += PAGE_SIZE - (size_remap % PAGE_SIZE);
	efअगरb_fix.smem_len = size_remap;

	अगर (request_mem_region(efअगरb_fix.smem_start, size_remap, "efifb")) अणु
		request_mem_succeeded = true;
	पूर्ण अन्यथा अणु
		/* We cannot make this fatal. Someबार this comes from magic
		   spaces our resource handlers simply करोn't know about */
		pr_warn("efifb: cannot reserve video memory at 0x%lx\n",
			efअगरb_fix.smem_start);
	पूर्ण

	info = framebuffer_alloc(माप(u32) * 16, &dev->dev);
	अगर (!info) अणु
		err = -ENOMEM;
		जाओ err_release_mem;
	पूर्ण
	platक्रमm_set_drvdata(dev, info);
	info->pseuकरो_palette = info->par;
	info->par = शून्य;

	info->apertures = alloc_apertures(1);
	अगर (!info->apertures) अणु
		err = -ENOMEM;
		जाओ err_release_fb;
	पूर्ण
	info->apertures->ranges[0].base = efअगरb_fix.smem_start;
	info->apertures->ranges[0].size = size_remap;

	अगर (efi_enabled(EFI_MEMMAP) &&
	    !efi_mem_desc_lookup(efअगरb_fix.smem_start, &md)) अणु
		अगर ((efअगरb_fix.smem_start + efअगरb_fix.smem_len) >
		    (md.phys_addr + (md.num_pages << EFI_PAGE_SHIFT))) अणु
			pr_err("efifb: video memory @ 0x%lx spans multiple EFI memory regions\n",
			       efअगरb_fix.smem_start);
			err = -EIO;
			जाओ err_release_fb;
		पूर्ण
		/*
		 * If the UEFI memory map covers the efअगरb region, we may only
		 * remap it using the attributes the memory map prescribes.
		 */
		md.attribute &= EFI_MEMORY_UC | EFI_MEMORY_WC |
				EFI_MEMORY_WT | EFI_MEMORY_WB;
		अगर (md.attribute) अणु
			mem_flags |= EFI_MEMORY_WT | EFI_MEMORY_WB;
			mem_flags &= md.attribute;
		पूर्ण
	पूर्ण
	अगर (mem_flags & EFI_MEMORY_WC)
		info->screen_base = ioremap_wc(efअगरb_fix.smem_start,
					       efअगरb_fix.smem_len);
	अन्यथा अगर (mem_flags & EFI_MEMORY_UC)
		info->screen_base = ioremap(efअगरb_fix.smem_start,
					    efअगरb_fix.smem_len);
	अन्यथा अगर (mem_flags & EFI_MEMORY_WT)
		info->screen_base = memremap(efअगरb_fix.smem_start,
					     efअगरb_fix.smem_len, MEMREMAP_WT);
	अन्यथा अगर (mem_flags & EFI_MEMORY_WB)
		info->screen_base = memremap(efअगरb_fix.smem_start,
					     efअगरb_fix.smem_len, MEMREMAP_WB);
	अगर (!info->screen_base) अणु
		pr_err("efifb: abort, cannot remap video memory 0x%x @ 0x%lx\n",
			efअगरb_fix.smem_len, efअगरb_fix.smem_start);
		err = -EIO;
		जाओ err_release_fb;
	पूर्ण

	efअगरb_show_boot_graphics(info);

	pr_info("efifb: framebuffer at 0x%lx, using %dk, total %dk\n",
	       efअगरb_fix.smem_start, size_remap/1024, माप_प्रकारotal/1024);
	pr_info("efifb: mode is %dx%dx%d, linelength=%d, pages=%d\n",
	       efअगरb_defined.xres, efअगरb_defined.yres,
	       efअगरb_defined.bits_per_pixel, efअगरb_fix.line_length,
	       screen_info.pages);

	efअगरb_defined.xres_भव = efअगरb_defined.xres;
	efअगरb_defined.yres_भव = efअगरb_fix.smem_len /
					efअगरb_fix.line_length;
	pr_info("efifb: scrolling: redraw\n");
	efअगरb_defined.yres_भव = efअगरb_defined.yres;

	/* some dummy values क्रम timing to make fbset happy */
	efअगरb_defined.pixघड़ी     = 10000000 / efअगरb_defined.xres *
					1000 / efअगरb_defined.yres;
	efअगरb_defined.left_margin  = (efअगरb_defined.xres / 8) & 0xf8;
	efअगरb_defined.hsync_len    = (efअगरb_defined.xres / 8) & 0xf8;

	efअगरb_defined.red.offset    = screen_info.red_pos;
	efअगरb_defined.red.length    = screen_info.red_size;
	efअगरb_defined.green.offset  = screen_info.green_pos;
	efअगरb_defined.green.length  = screen_info.green_size;
	efअगरb_defined.blue.offset   = screen_info.blue_pos;
	efअगरb_defined.blue.length   = screen_info.blue_size;
	efअगरb_defined.transp.offset = screen_info.rsvd_pos;
	efअगरb_defined.transp.length = screen_info.rsvd_size;

	pr_info("efifb: %s: "
	       "size=%d:%d:%d:%d, shift=%d:%d:%d:%d\n",
	       "Truecolor",
	       screen_info.rsvd_size,
	       screen_info.red_size,
	       screen_info.green_size,
	       screen_info.blue_size,
	       screen_info.rsvd_pos,
	       screen_info.red_pos,
	       screen_info.green_pos,
	       screen_info.blue_pos);

	efअगरb_fix.ypanstep  = 0;
	efअगरb_fix.ywrapstep = 0;

	info->fbops = &efअगरb_ops;
	info->var = efअगरb_defined;
	info->fix = efअगरb_fix;
	info->flags = FBINFO_FLAG_DEFAULT | FBINFO_MISC_FIRMWARE;

	orientation = drm_get_panel_orientation_quirk(efअगरb_defined.xres,
						      efअगरb_defined.yres);
	चयन (orientation) अणु
	शेष:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_UR;
		अवरोध;
	हाल DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_UD;
		अवरोध;
	हाल DRM_MODE_PANEL_ORIENTATION_LEFT_UP:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_CCW;
		अवरोध;
	हाल DRM_MODE_PANEL_ORIENTATION_RIGHT_UP:
		info->fbcon_rotate_hपूर्णांक = FB_ROTATE_CW;
		अवरोध;
	पूर्ण

	err = sysfs_create_groups(&dev->dev.kobj, efअगरb_groups);
	अगर (err) अणु
		pr_err("efifb: cannot add sysfs attrs\n");
		जाओ err_unmap;
	पूर्ण
	err = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (err < 0) अणु
		pr_err("efifb: cannot allocate colormap\n");
		जाओ err_groups;
	पूर्ण
	err = रेजिस्टर_framebuffer(info);
	अगर (err < 0) अणु
		pr_err("efifb: cannot register framebuffer\n");
		जाओ err_fb_dealoc;
	पूर्ण
	fb_info(info, "%s frame buffer device\n", info->fix.id);
	अगर (efअगरb_pci_dev)
		pm_runसमय_get_sync(&efअगरb_pci_dev->dev);
	वापस 0;

err_fb_dealoc:
	fb_dealloc_cmap(&info->cmap);
err_groups:
	sysfs_हटाओ_groups(&dev->dev.kobj, efअगरb_groups);
err_unmap:
	अगर (mem_flags & (EFI_MEMORY_UC | EFI_MEMORY_WC))
		iounmap(info->screen_base);
	अन्यथा
		memunmap(info->screen_base);
err_release_fb:
	framebuffer_release(info);
err_release_mem:
	अगर (request_mem_succeeded)
		release_mem_region(efअगरb_fix.smem_start, माप_प्रकारotal);
	वापस err;
पूर्ण

अटल पूर्णांक efअगरb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fb_info *info = platक्रमm_get_drvdata(pdev);

	unरेजिस्टर_framebuffer(info);
	sysfs_हटाओ_groups(&pdev->dev.kobj, efअगरb_groups);
	framebuffer_release(info);
	अगर (efअगरb_pci_dev)
		pm_runसमय_put(&efअगरb_pci_dev->dev);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver efअगरb_driver = अणु
	.driver = अणु
		.name = "efi-framebuffer",
	पूर्ण,
	.probe = efअगरb_probe,
	.हटाओ = efअगरb_हटाओ,
पूर्ण;

builtin_platक्रमm_driver(efअगरb_driver);

#अगर defined(CONFIG_PCI)

अटल व्योम record_efअगरb_bar_resource(काष्ठा pci_dev *dev, पूर्णांक idx, u64 offset)
अणु
	u16 word;

	efअगरb_pci_dev = dev;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &word);
	अगर (!(word & PCI_COMMAND_MEMORY)) अणु
		pci_dev_disabled = true;
		dev_err(&dev->dev,
			"BAR %d: assigned to efifb but device is disabled!\n",
			idx);
		वापस;
	पूर्ण

	bar_resource = &dev->resource[idx];
	bar_offset = offset;

	dev_info(&dev->dev, "BAR %d: assigned to efifb\n", idx);
पूर्ण

अटल व्योम efअगरb_fixup_resources(काष्ठा pci_dev *dev)
अणु
	u64 base = screen_info.lfb_base;
	u64 size = screen_info.lfb_size;
	पूर्णांक i;

	अगर (efअगरb_pci_dev || screen_info.orig_video_isVGA != VIDEO_TYPE_EFI)
		वापस;

	अगर (screen_info.capabilities & VIDEO_CAPABILITY_64BIT_BASE)
		base |= (u64)screen_info.ext_lfb_base << 32;

	अगर (!base)
		वापस;

	क्रम (i = 0; i < PCI_STD_NUM_BARS; i++) अणु
		काष्ठा resource *res = &dev->resource[i];

		अगर (!(res->flags & IORESOURCE_MEM))
			जारी;

		अगर (res->start <= base && res->end >= base + size - 1) अणु
			record_efअगरb_bar_resource(dev, i, base - res->start);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
DECLARE_PCI_FIXUP_CLASS_HEADER(PCI_ANY_ID, PCI_ANY_ID, PCI_BASE_CLASS_DISPLAY,
			       16, efअगरb_fixup_resources);

#पूर्ण_अगर
