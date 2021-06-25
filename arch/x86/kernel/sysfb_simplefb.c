<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Generic System Framebuffers on x86
 * Copyright (c) 2012-2013 David Herrmann <dh.herrmann@gmail.com>
 */

/*
 * simple-framebuffer probing
 * Try to convert "screen_info" पूर्णांकo a "simple-framebuffer" compatible mode.
 * If the mode is incompatible, we वापस "false" and let the caller create
 * legacy nodes instead.
 */

#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/platक्रमm_data/simplefb.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>
#समावेश <यंत्र/sysfb.h>

अटल स्थिर अक्षर simplefb_resname[] = "BOOTFB";
अटल स्थिर काष्ठा simplefb_क्रमmat क्रमmats[] = SIMPLEFB_FORMATS;

/* try parsing x86 screen_info पूर्णांकo a simple-framebuffer mode काष्ठा */
__init bool parse_mode(स्थिर काष्ठा screen_info *si,
		       काष्ठा simplefb_platक्रमm_data *mode)
अणु
	स्थिर काष्ठा simplefb_क्रमmat *f;
	__u8 type;
	अचिन्हित पूर्णांक i;

	type = si->orig_video_isVGA;
	अगर (type != VIDEO_TYPE_VLFB && type != VIDEO_TYPE_EFI)
		वापस false;

	क्रम (i = 0; i < ARRAY_SIZE(क्रमmats); ++i) अणु
		f = &क्रमmats[i];
		अगर (si->lfb_depth == f->bits_per_pixel &&
		    si->red_size == f->red.length &&
		    si->red_pos == f->red.offset &&
		    si->green_size == f->green.length &&
		    si->green_pos == f->green.offset &&
		    si->blue_size == f->blue.length &&
		    si->blue_pos == f->blue.offset &&
		    si->rsvd_size == f->transp.length &&
		    si->rsvd_pos == f->transp.offset) अणु
			mode->क्रमmat = f->name;
			mode->width = si->lfb_width;
			mode->height = si->lfb_height;
			mode->stride = si->lfb_linelength;
			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

__init पूर्णांक create_simplefb(स्थिर काष्ठा screen_info *si,
			   स्थिर काष्ठा simplefb_platक्रमm_data *mode)
अणु
	काष्ठा platक्रमm_device *pd;
	काष्ठा resource res;
	u64 base, size;
	u32 length;

	/*
	 * If the 64BIT_BASE capability is set, ext_lfb_base will contain the
	 * upper half of the base address. Assemble the address, then make sure
	 * it is valid and we can actually access it.
	 */
	base = si->lfb_base;
	अगर (si->capabilities & VIDEO_CAPABILITY_64BIT_BASE)
		base |= (u64)si->ext_lfb_base << 32;
	अगर (!base || (u64)(resource_माप_प्रकार)base != base) अणु
		prपूर्णांकk(KERN_DEBUG "sysfb: inaccessible VRAM base\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Don't use lfb_size as IORESOURCE size, since it may contain the
	 * entire VMEM, and thus require huge mappings. Use just the part we
	 * need, that is, the part where the framebuffer is located. But verअगरy
	 * that it करोes not exceed the advertised VMEM.
	 * Note that in हाल of VBE, the lfb_size is shअगरted by 16 bits क्रम
	 * historical reasons.
	 */
	size = si->lfb_size;
	अगर (si->orig_video_isVGA == VIDEO_TYPE_VLFB)
		size <<= 16;
	length = mode->height * mode->stride;
	अगर (length > size) अणु
		prपूर्णांकk(KERN_WARNING "sysfb: VRAM smaller than advertised\n");
		वापस -EINVAL;
	पूर्ण
	length = PAGE_ALIGN(length);

	/* setup IORESOURCE_MEM as framebuffer memory */
	स_रखो(&res, 0, माप(res));
	res.flags = IORESOURCE_MEM | IORESOURCE_BUSY;
	res.name = simplefb_resname;
	res.start = base;
	res.end = res.start + length - 1;
	अगर (res.end <= res.start)
		वापस -EINVAL;

	pd = platक्रमm_device_रेजिस्टर_resndata(शून्य, "simple-framebuffer", 0,
					       &res, 1, mode, माप(*mode));
	वापस PTR_ERR_OR_ZERO(pd);
पूर्ण
