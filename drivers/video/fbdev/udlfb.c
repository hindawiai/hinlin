<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * udlfb.c -- Framebuffer driver क्रम DisplayLink USB controller
 *
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>
 *
 * Layout is based on skeletonfb by James Simmons and Geert Uytterhoeven,
 * usb-skeleton by GregKH.
 *
 * Device-specअगरic portions based on inक्रमmation from Displaylink, with work
 * from Florian Echtler, Henrik Bjerregaard Pedersen, and others.
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/usb.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mm.h>
#समावेश <linux/fb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <video/udlfb.h>
#समावेश "edid.h"

अटल स्थिर काष्ठा fb_fix_screeninfo dlfb_fix = अणु
	.id =           "udlfb",
	.type =         FB_TYPE_PACKED_PIXELS,
	.visual =       FB_VISUAL_TRUECOLOR,
	.xpanstep =     0,
	.ypanstep =     0,
	.ywrapstep =    0,
	.accel =        FB_ACCEL_NONE,
पूर्ण;

अटल स्थिर u32 udlfb_info_flags = FBINFO_DEFAULT | FBINFO_READS_FAST |
		FBINFO_VIRTFB |
		FBINFO_HWACCEL_IMAGEBLIT | FBINFO_HWACCEL_FILLRECT |
		FBINFO_HWACCEL_COPYAREA | FBINFO_MISC_ALWAYS_SETPAR;

/*
 * There are many DisplayLink-based graphics products, all with unique PIDs.
 * So we match on DisplayLink's VID + Venकरोr-Defined Interface Class (0xff)
 * We also require a match on SubClass (0x00) and Protocol (0x00),
 * which is compatible with all known USB 2.0 era graphics chips and firmware,
 * but allows DisplayLink to increment those क्रम any future incompatible chips
 */
अटल स्थिर काष्ठा usb_device_id id_table[] = अणु
	अणु.idVenकरोr = 0x17e9,
	 .bInterfaceClass = 0xff,
	 .bInterfaceSubClass = 0x00,
	 .bInterfaceProtocol = 0x00,
	 .match_flags = USB_DEVICE_ID_MATCH_VENDOR |
		USB_DEVICE_ID_MATCH_INT_CLASS |
		USB_DEVICE_ID_MATCH_INT_SUBCLASS |
		USB_DEVICE_ID_MATCH_INT_PROTOCOL,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(usb, id_table);

/* module options */
अटल bool console = true; /* Allow fbcon to खोलो framebuffer */
अटल bool fb_defio = true;  /* Detect mmap ग_लिखोs using page faults */
अटल bool shaकरोw = true; /* Optionally disable shaकरोw framebuffer */
अटल पूर्णांक pixel_limit; /* Optionally क्रमce a pixel resolution limit */

काष्ठा dlfb_deferred_मुक्त अणु
	काष्ठा list_head list;
	व्योम *mem;
पूर्ण;

अटल पूर्णांक dlfb_पुनः_स्मृति_framebuffer(काष्ठा dlfb_data *dlfb, काष्ठा fb_info *info, u32 new_len);

/* dlfb keeps a list of urbs क्रम efficient bulk transfers */
अटल व्योम dlfb_urb_completion(काष्ठा urb *urb);
अटल काष्ठा urb *dlfb_get_urb(काष्ठा dlfb_data *dlfb);
अटल पूर्णांक dlfb_submit_urb(काष्ठा dlfb_data *dlfb, काष्ठा urb * urb, माप_प्रकार len);
अटल पूर्णांक dlfb_alloc_urb_list(काष्ठा dlfb_data *dlfb, पूर्णांक count, माप_प्रकार size);
अटल व्योम dlfb_मुक्त_urb_list(काष्ठा dlfb_data *dlfb);

/*
 * All DisplayLink bulk operations start with 0xAF, followed by specअगरic code
 * All operations are written to buffers which then later get sent to device
 */
अटल अक्षर *dlfb_set_रेजिस्टर(अक्षर *buf, u8 reg, u8 val)
अणु
	*buf++ = 0xAF;
	*buf++ = 0x20;
	*buf++ = reg;
	*buf++ = val;
	वापस buf;
पूर्ण

अटल अक्षर *dlfb_vidreg_lock(अक्षर *buf)
अणु
	वापस dlfb_set_रेजिस्टर(buf, 0xFF, 0x00);
पूर्ण

अटल अक्षर *dlfb_vidreg_unlock(अक्षर *buf)
अणु
	वापस dlfb_set_रेजिस्टर(buf, 0xFF, 0xFF);
पूर्ण

/*
 * Map FB_BLANK_* to DisplayLink रेजिस्टर
 * DLReg FB_BLANK_*
 * ----- -----------------------------
 *  0x00 FB_BLANK_UNBLANK (0)
 *  0x01 FB_BLANK (1)
 *  0x03 FB_BLANK_VSYNC_SUSPEND (2)
 *  0x05 FB_BLANK_HSYNC_SUSPEND (3)
 *  0x07 FB_BLANK_POWERDOWN (4) Note: requires modeset to come back
 */
अटल अक्षर *dlfb_blanking(अक्षर *buf, पूर्णांक fb_blank)
अणु
	u8 reg;

	चयन (fb_blank) अणु
	हाल FB_BLANK_POWERDOWN:
		reg = 0x07;
		अवरोध;
	हाल FB_BLANK_HSYNC_SUSPEND:
		reg = 0x05;
		अवरोध;
	हाल FB_BLANK_VSYNC_SUSPEND:
		reg = 0x03;
		अवरोध;
	हाल FB_BLANK_NORMAL:
		reg = 0x01;
		अवरोध;
	शेष:
		reg = 0x00;
	पूर्ण

	buf = dlfb_set_रेजिस्टर(buf, 0x1F, reg);

	वापस buf;
पूर्ण

अटल अक्षर *dlfb_set_color_depth(अक्षर *buf, u8 selection)
अणु
	वापस dlfb_set_रेजिस्टर(buf, 0x00, selection);
पूर्ण

अटल अक्षर *dlfb_set_base16bpp(अक्षर *wrptr, u32 base)
अणु
	/* the base poपूर्णांकer is 16 bits wide, 0x20 is hi byte. */
	wrptr = dlfb_set_रेजिस्टर(wrptr, 0x20, base >> 16);
	wrptr = dlfb_set_रेजिस्टर(wrptr, 0x21, base >> 8);
	वापस dlfb_set_रेजिस्टर(wrptr, 0x22, base);
पूर्ण

/*
 * DisplayLink HW has separate 16bpp and 8bpp framebuffers.
 * In 24bpp modes, the low 323 RGB bits go in the 8bpp framebuffer
 */
अटल अक्षर *dlfb_set_base8bpp(अक्षर *wrptr, u32 base)
अणु
	wrptr = dlfb_set_रेजिस्टर(wrptr, 0x26, base >> 16);
	wrptr = dlfb_set_रेजिस्टर(wrptr, 0x27, base >> 8);
	वापस dlfb_set_रेजिस्टर(wrptr, 0x28, base);
पूर्ण

अटल अक्षर *dlfb_set_रेजिस्टर_16(अक्षर *wrptr, u8 reg, u16 value)
अणु
	wrptr = dlfb_set_रेजिस्टर(wrptr, reg, value >> 8);
	वापस dlfb_set_रेजिस्टर(wrptr, reg+1, value);
पूर्ण

/*
 * This is kind of weird because the controller takes some
 * रेजिस्टर values in a dअगरferent byte order than other रेजिस्टरs.
 */
अटल अक्षर *dlfb_set_रेजिस्टर_16be(अक्षर *wrptr, u8 reg, u16 value)
अणु
	wrptr = dlfb_set_रेजिस्टर(wrptr, reg, value);
	वापस dlfb_set_रेजिस्टर(wrptr, reg+1, value >> 8);
पूर्ण

/*
 * LFSR is linear feedback shअगरt रेजिस्टर. The reason we have this is
 * because the display controller needs to minimize the घड़ी depth of
 * various counters used in the display path. So this code reverses the
 * provided value पूर्णांकo the lfsr16 value by counting backwards to get
 * the value that needs to be set in the hardware comparator to get the
 * same actual count. This makes sense once you पढ़ो above a couple of
 * बार and think about it from a hardware perspective.
 */
अटल u16 dlfb_lfsr16(u16 actual_count)
अणु
	u32 lv = 0xFFFF; /* This is the lfsr value that the hw starts with */

	जबतक (actual_count--) अणु
		lv =	 ((lv << 1) |
			(((lv >> 15) ^ (lv >> 4) ^ (lv >> 2) ^ (lv >> 1)) & 1))
			& 0xFFFF;
	पूर्ण

	वापस (u16) lv;
पूर्ण

/*
 * This करोes LFSR conversion on the value that is to be written.
 * See LFSR explanation above क्रम more detail.
 */
अटल अक्षर *dlfb_set_रेजिस्टर_lfsr16(अक्षर *wrptr, u8 reg, u16 value)
अणु
	वापस dlfb_set_रेजिस्टर_16(wrptr, reg, dlfb_lfsr16(value));
पूर्ण

/*
 * This takes a standard fbdev screeninfo काष्ठा and all of its monitor mode
 * details and converts them पूर्णांकo the DisplayLink equivalent रेजिस्टर commands.
 */
अटल अक्षर *dlfb_set_vid_cmds(अक्षर *wrptr, काष्ठा fb_var_screeninfo *var)
अणु
	u16 xds, yds;
	u16 xde, yde;
	u16 yec;

	/* x display start */
	xds = var->left_margin + var->hsync_len;
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x01, xds);
	/* x display end */
	xde = xds + var->xres;
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x03, xde);

	/* y display start */
	yds = var->upper_margin + var->vsync_len;
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x05, yds);
	/* y display end */
	yde = yds + var->yres;
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x07, yde);

	/* x end count is active + blanking - 1 */
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x09,
			xde + var->right_margin - 1);

	/* libdlo hardcodes hsync start to 1 */
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x0B, 1);

	/* hsync end is width of sync pulse + 1 */
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x0D, var->hsync_len + 1);

	/* hpixels is active pixels */
	wrptr = dlfb_set_रेजिस्टर_16(wrptr, 0x0F, var->xres);

	/* yendcount is vertical active + vertical blanking */
	yec = var->yres + var->upper_margin + var->lower_margin +
			var->vsync_len;
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x11, yec);

	/* libdlo hardcodes vsync start to 0 */
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x13, 0);

	/* vsync end is width of vsync pulse */
	wrptr = dlfb_set_रेजिस्टर_lfsr16(wrptr, 0x15, var->vsync_len);

	/* vpixels is active pixels */
	wrptr = dlfb_set_रेजिस्टर_16(wrptr, 0x17, var->yres);

	/* convert picoseconds to 5kHz multiple क्रम pclk5k = x * 1E12/5k */
	wrptr = dlfb_set_रेजिस्टर_16be(wrptr, 0x1B,
			200*1000*1000/var->pixघड़ी);

	वापस wrptr;
पूर्ण

/*
 * This takes a standard fbdev screeninfo काष्ठा that was fetched or prepared
 * and then generates the appropriate command sequence that then drives the
 * display controller.
 */
अटल पूर्णांक dlfb_set_video_mode(काष्ठा dlfb_data *dlfb,
				काष्ठा fb_var_screeninfo *var)
अणु
	अक्षर *buf;
	अक्षर *wrptr;
	पूर्णांक retval;
	पूर्णांक ग_लिखोsize;
	काष्ठा urb *urb;

	अगर (!atomic_पढ़ो(&dlfb->usb_active))
		वापस -EPERM;

	urb = dlfb_get_urb(dlfb);
	अगर (!urb)
		वापस -ENOMEM;

	buf = (अक्षर *) urb->transfer_buffer;

	/*
	* This first section has to करो with setting the base address on the
	* controller * associated with the display. There are 2 base
	* poपूर्णांकers, currently, we only * use the 16 bpp segment.
	*/
	wrptr = dlfb_vidreg_lock(buf);
	wrptr = dlfb_set_color_depth(wrptr, 0x00);
	/* set base क्रम 16bpp segment to 0 */
	wrptr = dlfb_set_base16bpp(wrptr, 0);
	/* set base क्रम 8bpp segment to end of fb */
	wrptr = dlfb_set_base8bpp(wrptr, dlfb->info->fix.smem_len);

	wrptr = dlfb_set_vid_cmds(wrptr, var);
	wrptr = dlfb_blanking(wrptr, FB_BLANK_UNBLANK);
	wrptr = dlfb_vidreg_unlock(wrptr);

	ग_लिखोsize = wrptr - buf;

	retval = dlfb_submit_urb(dlfb, urb, ग_लिखोsize);

	dlfb->blank_mode = FB_BLANK_UNBLANK;

	वापस retval;
पूर्ण

अटल पूर्णांक dlfb_ops_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ start = vma->vm_start;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ page, pos;

	अगर (vma->vm_pgoff > (~0UL >> PAGE_SHIFT))
		वापस -EINVAL;
	अगर (size > info->fix.smem_len)
		वापस -EINVAL;
	अगर (offset > info->fix.smem_len - size)
		वापस -EINVAL;

	pos = (अचिन्हित दीर्घ)info->fix.smem_start + offset;

	dev_dbg(info->dev, "mmap() framebuffer addr:%lu size:%lu\n",
		pos, size);

	जबतक (size > 0) अणु
		page = vदो_स्मृति_to_pfn((व्योम *)pos);
		अगर (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED))
			वापस -EAGAIN;

		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		अगर (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		अन्यथा
			size = 0;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Trims identical data from front and back of line
 * Sets new front buffer address and width
 * And वापसs byte count of identical pixels
 * Assumes CPU natural alignment (अचिन्हित दीर्घ)
 * क्रम back and front buffer ptrs and width
 */
अटल पूर्णांक dlfb_trim_hline(स्थिर u8 *bback, स्थिर u8 **bfront, पूर्णांक *width_bytes)
अणु
	पूर्णांक j, k;
	स्थिर अचिन्हित दीर्घ *back = (स्थिर अचिन्हित दीर्घ *) bback;
	स्थिर अचिन्हित दीर्घ *front = (स्थिर अचिन्हित दीर्घ *) *bfront;
	स्थिर पूर्णांक width = *width_bytes / माप(अचिन्हित दीर्घ);
	पूर्णांक identical = width;
	पूर्णांक start = width;
	पूर्णांक end = width;

	क्रम (j = 0; j < width; j++) अणु
		अगर (back[j] != front[j]) अणु
			start = j;
			अवरोध;
		पूर्ण
	पूर्ण

	क्रम (k = width - 1; k > j; k--) अणु
		अगर (back[k] != front[k]) अणु
			end = k+1;
			अवरोध;
		पूर्ण
	पूर्ण

	identical = start + (width - end);
	*bfront = (u8 *) &front[start];
	*width_bytes = (end - start) * माप(अचिन्हित दीर्घ);

	वापस identical * माप(अचिन्हित दीर्घ);
पूर्ण

/*
 * Render a command stream क्रम an encoded horizontal line segment of pixels.
 *
 * A command buffer holds several commands.
 * It always begins with a fresh command header
 * (the protocol करोesn't require this, but we enक्रमce it to allow
 * multiple buffers to be potentially encoded and sent in parallel).
 * A single command encodes one contiguous horizontal line of pixels
 *
 * The function relies on the client to करो all allocation, so that
 * rendering can be करोne directly to output buffers (e.g. USB URBs).
 * The function fills the supplied command buffer, providing inक्रमmation
 * on where it left off, so the client may call in again with additional
 * buffers अगर the line will take several buffers to complete.
 *
 * A single command can transmit a maximum of 256 pixels,
 * regardless of the compression ratio (protocol design limit).
 * To the hardware, 0 क्रम a size byte means 256
 *
 * Rather than 256 pixel commands which are either rl or raw encoded,
 * the rlx command simply assumes alternating raw and rl spans within one cmd.
 * This has a slightly larger header overhead, but produces more even results.
 * It also processes all data (पढ़ो and ग_लिखो) in a single pass.
 * Perक्रमmance benchmarks of common हालs show it having just slightly better
 * compression than 256 pixel raw or rle commands, with similar CPU consumpion.
 * But क्रम very rl मित्रly data, will compress not quite as well.
 */
अटल व्योम dlfb_compress_hline(
	स्थिर uपूर्णांक16_t **pixel_start_ptr,
	स्थिर uपूर्णांक16_t *स्थिर pixel_end,
	uपूर्णांक32_t *device_address_ptr,
	uपूर्णांक8_t **command_buffer_ptr,
	स्थिर uपूर्णांक8_t *स्थिर cmd_buffer_end,
	अचिन्हित दीर्घ back_buffer_offset,
	पूर्णांक *ident_ptr)
अणु
	स्थिर uपूर्णांक16_t *pixel = *pixel_start_ptr;
	uपूर्णांक32_t dev_addr  = *device_address_ptr;
	uपूर्णांक8_t *cmd = *command_buffer_ptr;

	जबतक ((pixel_end > pixel) &&
	       (cmd_buffer_end - MIN_RLX_CMD_BYTES > cmd)) अणु
		uपूर्णांक8_t *raw_pixels_count_byte = शून्य;
		uपूर्णांक8_t *cmd_pixels_count_byte = शून्य;
		स्थिर uपूर्णांक16_t *raw_pixel_start = शून्य;
		स्थिर uपूर्णांक16_t *cmd_pixel_start, *cmd_pixel_end = शून्य;

		अगर (back_buffer_offset &&
		    *pixel == *(u16 *)((u8 *)pixel + back_buffer_offset)) अणु
			pixel++;
			dev_addr += BPP;
			(*ident_ptr)++;
			जारी;
		पूर्ण

		*cmd++ = 0xAF;
		*cmd++ = 0x6B;
		*cmd++ = dev_addr >> 16;
		*cmd++ = dev_addr >> 8;
		*cmd++ = dev_addr;

		cmd_pixels_count_byte = cmd++; /*  we'll know this later */
		cmd_pixel_start = pixel;

		raw_pixels_count_byte = cmd++; /*  we'll know this later */
		raw_pixel_start = pixel;

		cmd_pixel_end = pixel + min3(MAX_CMD_PIXELS + 1UL,
					(अचिन्हित दीर्घ)(pixel_end - pixel),
					(अचिन्हित दीर्घ)(cmd_buffer_end - 1 - cmd) / BPP);

		अगर (back_buffer_offset) अणु
			/* note: the framebuffer may change under us, so we must test क्रम underflow */
			जबतक (cmd_pixel_end - 1 > pixel &&
			       *(cmd_pixel_end - 1) == *(u16 *)((u8 *)(cmd_pixel_end - 1) + back_buffer_offset))
				cmd_pixel_end--;
		पूर्ण

		जबतक (pixel < cmd_pixel_end) अणु
			स्थिर uपूर्णांक16_t * स्थिर repeating_pixel = pixel;
			u16 pixel_value = *pixel;

			put_unaligned_be16(pixel_value, cmd);
			अगर (back_buffer_offset)
				*(u16 *)((u8 *)pixel + back_buffer_offset) = pixel_value;
			cmd += 2;
			pixel++;

			अगर (unlikely((pixel < cmd_pixel_end) &&
				     (*pixel == pixel_value))) अणु
				/* go back and fill in raw pixel count */
				*raw_pixels_count_byte = ((repeating_pixel -
						raw_pixel_start) + 1) & 0xFF;

				करो अणु
					अगर (back_buffer_offset)
						*(u16 *)((u8 *)pixel + back_buffer_offset) = pixel_value;
					pixel++;
				पूर्ण जबतक ((pixel < cmd_pixel_end) &&
					 (*pixel == pixel_value));

				/* immediately after raw data is repeat byte */
				*cmd++ = ((pixel - repeating_pixel) - 1) & 0xFF;

				/* Then start another raw pixel span */
				raw_pixel_start = pixel;
				raw_pixels_count_byte = cmd++;
			पूर्ण
		पूर्ण

		अगर (pixel > raw_pixel_start) अणु
			/* finalize last RAW span */
			*raw_pixels_count_byte = (pixel-raw_pixel_start) & 0xFF;
		पूर्ण अन्यथा अणु
			/* unकरो unused byte */
			cmd--;
		पूर्ण

		*cmd_pixels_count_byte = (pixel - cmd_pixel_start) & 0xFF;
		dev_addr += (u8 *)pixel - (u8 *)cmd_pixel_start;
	पूर्ण

	अगर (cmd_buffer_end - MIN_RLX_CMD_BYTES <= cmd) अणु
		/* Fill leftover bytes with no-ops */
		अगर (cmd_buffer_end > cmd)
			स_रखो(cmd, 0xAF, cmd_buffer_end - cmd);
		cmd = (uपूर्णांक8_t *) cmd_buffer_end;
	पूर्ण

	*command_buffer_ptr = cmd;
	*pixel_start_ptr = pixel;
	*device_address_ptr = dev_addr;
पूर्ण

/*
 * There are 3 copies of every pixel: The front buffer that the fbdev
 * client renders to, the actual framebuffer across the USB bus in hardware
 * (that we can only ग_लिखो to, slowly, and can never पढ़ो), and (optionally)
 * our shaकरोw copy that tracks what's been sent to that hardware buffer.
 */
अटल पूर्णांक dlfb_render_hline(काष्ठा dlfb_data *dlfb, काष्ठा urb **urb_ptr,
			      स्थिर अक्षर *front, अक्षर **urb_buf_ptr,
			      u32 byte_offset, u32 byte_width,
			      पूर्णांक *ident_ptr, पूर्णांक *sent_ptr)
अणु
	स्थिर u8 *line_start, *line_end, *next_pixel;
	u32 dev_addr = dlfb->base16 + byte_offset;
	काष्ठा urb *urb = *urb_ptr;
	u8 *cmd = *urb_buf_ptr;
	u8 *cmd_end = (u8 *) urb->transfer_buffer + urb->transfer_buffer_length;
	अचिन्हित दीर्घ back_buffer_offset = 0;

	line_start = (u8 *) (front + byte_offset);
	next_pixel = line_start;
	line_end = next_pixel + byte_width;

	अगर (dlfb->backing_buffer) अणु
		पूर्णांक offset;
		स्थिर u8 *back_start = (u8 *) (dlfb->backing_buffer
						+ byte_offset);

		back_buffer_offset = (अचिन्हित दीर्घ)back_start - (अचिन्हित दीर्घ)line_start;

		*ident_ptr += dlfb_trim_hline(back_start, &next_pixel,
			&byte_width);

		offset = next_pixel - line_start;
		line_end = next_pixel + byte_width;
		dev_addr += offset;
		back_start += offset;
		line_start += offset;
	पूर्ण

	जबतक (next_pixel < line_end) अणु

		dlfb_compress_hline((स्थिर uपूर्णांक16_t **) &next_pixel,
			     (स्थिर uपूर्णांक16_t *) line_end, &dev_addr,
			(u8 **) &cmd, (u8 *) cmd_end, back_buffer_offset,
			ident_ptr);

		अगर (cmd >= cmd_end) अणु
			पूर्णांक len = cmd - (u8 *) urb->transfer_buffer;
			अगर (dlfb_submit_urb(dlfb, urb, len))
				वापस 1; /* lost pixels is set */
			*sent_ptr += len;
			urb = dlfb_get_urb(dlfb);
			अगर (!urb)
				वापस 1; /* lost_pixels is set */
			*urb_ptr = urb;
			cmd = urb->transfer_buffer;
			cmd_end = &cmd[urb->transfer_buffer_length];
		पूर्ण
	पूर्ण

	*urb_buf_ptr = cmd;

	वापस 0;
पूर्ण

अटल पूर्णांक dlfb_handle_damage(काष्ठा dlfb_data *dlfb, पूर्णांक x, पूर्णांक y, पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक i, ret;
	अक्षर *cmd;
	cycles_t start_cycles, end_cycles;
	पूर्णांक bytes_sent = 0;
	पूर्णांक bytes_identical = 0;
	काष्ठा urb *urb;
	पूर्णांक aligned_x;

	start_cycles = get_cycles();

	mutex_lock(&dlfb->render_mutex);

	aligned_x = DL_ALIGN_DOWN(x, माप(अचिन्हित दीर्घ));
	width = DL_ALIGN_UP(width + (x-aligned_x), माप(अचिन्हित दीर्घ));
	x = aligned_x;

	अगर ((width <= 0) ||
	    (x + width > dlfb->info->var.xres) ||
	    (y + height > dlfb->info->var.yres)) अणु
		ret = -EINVAL;
		जाओ unlock_ret;
	पूर्ण

	अगर (!atomic_पढ़ो(&dlfb->usb_active)) अणु
		ret = 0;
		जाओ unlock_ret;
	पूर्ण

	urb = dlfb_get_urb(dlfb);
	अगर (!urb) अणु
		ret = 0;
		जाओ unlock_ret;
	पूर्ण
	cmd = urb->transfer_buffer;

	क्रम (i = y; i < y + height ; i++) अणु
		स्थिर पूर्णांक line_offset = dlfb->info->fix.line_length * i;
		स्थिर पूर्णांक byte_offset = line_offset + (x * BPP);

		अगर (dlfb_render_hline(dlfb, &urb,
				      (अक्षर *) dlfb->info->fix.smem_start,
				      &cmd, byte_offset, width * BPP,
				      &bytes_identical, &bytes_sent))
			जाओ error;
	पूर्ण

	अगर (cmd > (अक्षर *) urb->transfer_buffer) अणु
		पूर्णांक len;
		अगर (cmd < (अक्षर *) urb->transfer_buffer + urb->transfer_buffer_length)
			*cmd++ = 0xAF;
		/* Send partial buffer reमुख्यing beक्रमe निकासing */
		len = cmd - (अक्षर *) urb->transfer_buffer;
		dlfb_submit_urb(dlfb, urb, len);
		bytes_sent += len;
	पूर्ण अन्यथा
		dlfb_urb_completion(urb);

error:
	atomic_add(bytes_sent, &dlfb->bytes_sent);
	atomic_add(bytes_identical, &dlfb->bytes_identical);
	atomic_add(width*height*2, &dlfb->bytes_rendered);
	end_cycles = get_cycles();
	atomic_add(((अचिन्हित पूर्णांक) ((end_cycles - start_cycles)
		    >> 10)), /* Kcycles */
		   &dlfb->cpu_kcycles_used);

	ret = 0;

unlock_ret:
	mutex_unlock(&dlfb->render_mutex);
	वापस ret;
पूर्ण

अटल व्योम dlfb_init_damage(काष्ठा dlfb_data *dlfb)
अणु
	dlfb->damage_x = पूर्णांक_उच्च;
	dlfb->damage_x2 = 0;
	dlfb->damage_y = पूर्णांक_उच्च;
	dlfb->damage_y2 = 0;
पूर्ण

अटल व्योम dlfb_damage_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा dlfb_data *dlfb = container_of(w, काष्ठा dlfb_data, damage_work);
	पूर्णांक x, x2, y, y2;

	spin_lock_irq(&dlfb->damage_lock);
	x = dlfb->damage_x;
	x2 = dlfb->damage_x2;
	y = dlfb->damage_y;
	y2 = dlfb->damage_y2;
	dlfb_init_damage(dlfb);
	spin_unlock_irq(&dlfb->damage_lock);

	अगर (x < x2 && y < y2)
		dlfb_handle_damage(dlfb, x, y, x2 - x, y2 - y);
पूर्ण

अटल व्योम dlfb_offload_damage(काष्ठा dlfb_data *dlfb, पूर्णांक x, पूर्णांक y, पूर्णांक width, पूर्णांक height)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक x2 = x + width;
	पूर्णांक y2 = y + height;

	अगर (x >= x2 || y >= y2)
		वापस;

	spin_lock_irqsave(&dlfb->damage_lock, flags);
	dlfb->damage_x = min(x, dlfb->damage_x);
	dlfb->damage_x2 = max(x2, dlfb->damage_x2);
	dlfb->damage_y = min(y, dlfb->damage_y);
	dlfb->damage_y2 = max(y2, dlfb->damage_y2);
	spin_unlock_irqrestore(&dlfb->damage_lock, flags);

	schedule_work(&dlfb->damage_work);
पूर्ण

/*
 * Path triggered by usermode clients who ग_लिखो to fileप्रणाली
 * e.g. cat filename > /dev/fb1
 * Not used by X Winकरोws or text-mode console. But useful क्रम testing.
 * Slow because of extra copy and we must assume all pixels dirty.
 */
अटल sमाप_प्रकार dlfb_ops_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
			  माप_प्रकार count, loff_t *ppos)
अणु
	sमाप_प्रकार result;
	काष्ठा dlfb_data *dlfb = info->par;
	u32 offset = (u32) *ppos;

	result = fb_sys_ग_लिखो(info, buf, count, ppos);

	अगर (result > 0) अणु
		पूर्णांक start = max((पूर्णांक)(offset / info->fix.line_length), 0);
		पूर्णांक lines = min((u32)((result / info->fix.line_length) + 1),
				(u32)info->var.yres);

		dlfb_handle_damage(dlfb, 0, start, info->var.xres,
			lines);
	पूर्ण

	वापस result;
पूर्ण

/* hardware has native COPY command (see libdlo), but not worth it क्रम fbcon */
अटल व्योम dlfb_ops_copyarea(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_copyarea *area)
अणु

	काष्ठा dlfb_data *dlfb = info->par;

	sys_copyarea(info, area);

	dlfb_offload_damage(dlfb, area->dx, area->dy,
			area->width, area->height);
पूर्ण

अटल व्योम dlfb_ops_imageblit(काष्ठा fb_info *info,
				स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा dlfb_data *dlfb = info->par;

	sys_imageblit(info, image);

	dlfb_offload_damage(dlfb, image->dx, image->dy,
			image->width, image->height);
पूर्ण

अटल व्योम dlfb_ops_fillrect(काष्ठा fb_info *info,
			  स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा dlfb_data *dlfb = info->par;

	sys_fillrect(info, rect);

	dlfb_offload_damage(dlfb, rect->dx, rect->dy, rect->width,
			      rect->height);
पूर्ण

/*
 * NOTE: fb_defio.c is holding info->fbdefio.mutex
 *   Touching ANY framebuffer memory that triggers a page fault
 *   in fb_defio will cause a deadlock, when it also tries to
 *   grab the same mutex.
 */
अटल व्योम dlfb_dpy_deferred_io(काष्ठा fb_info *info,
				काष्ठा list_head *pagelist)
अणु
	काष्ठा page *cur;
	काष्ठा fb_deferred_io *fbdefio = info->fbdefio;
	काष्ठा dlfb_data *dlfb = info->par;
	काष्ठा urb *urb;
	अक्षर *cmd;
	cycles_t start_cycles, end_cycles;
	पूर्णांक bytes_sent = 0;
	पूर्णांक bytes_identical = 0;
	पूर्णांक bytes_rendered = 0;

	mutex_lock(&dlfb->render_mutex);

	अगर (!fb_defio)
		जाओ unlock_ret;

	अगर (!atomic_पढ़ो(&dlfb->usb_active))
		जाओ unlock_ret;

	start_cycles = get_cycles();

	urb = dlfb_get_urb(dlfb);
	अगर (!urb)
		जाओ unlock_ret;

	cmd = urb->transfer_buffer;

	/* walk the written page list and render each to device */
	list_क्रम_each_entry(cur, &fbdefio->pagelist, lru) अणु

		अगर (dlfb_render_hline(dlfb, &urb, (अक्षर *) info->fix.smem_start,
				  &cmd, cur->index << PAGE_SHIFT,
				  PAGE_SIZE, &bytes_identical, &bytes_sent))
			जाओ error;
		bytes_rendered += PAGE_SIZE;
	पूर्ण

	अगर (cmd > (अक्षर *) urb->transfer_buffer) अणु
		पूर्णांक len;
		अगर (cmd < (अक्षर *) urb->transfer_buffer + urb->transfer_buffer_length)
			*cmd++ = 0xAF;
		/* Send partial buffer reमुख्यing beक्रमe निकासing */
		len = cmd - (अक्षर *) urb->transfer_buffer;
		dlfb_submit_urb(dlfb, urb, len);
		bytes_sent += len;
	पूर्ण अन्यथा
		dlfb_urb_completion(urb);

error:
	atomic_add(bytes_sent, &dlfb->bytes_sent);
	atomic_add(bytes_identical, &dlfb->bytes_identical);
	atomic_add(bytes_rendered, &dlfb->bytes_rendered);
	end_cycles = get_cycles();
	atomic_add(((अचिन्हित पूर्णांक) ((end_cycles - start_cycles)
		    >> 10)), /* Kcycles */
		   &dlfb->cpu_kcycles_used);
unlock_ret:
	mutex_unlock(&dlfb->render_mutex);
पूर्ण

अटल पूर्णांक dlfb_get_edid(काष्ठा dlfb_data *dlfb, अक्षर *edid, पूर्णांक len)
अणु
	पूर्णांक i, ret;
	अक्षर *rbuf;

	rbuf = kदो_स्मृति(2, GFP_KERNEL);
	अगर (!rbuf)
		वापस 0;

	क्रम (i = 0; i < len; i++) अणु
		ret = usb_control_msg(dlfb->udev,
				      usb_rcvctrlpipe(dlfb->udev, 0), 0x02,
				      (0x80 | (0x02 << 5)), i << 8, 0xA1,
				      rbuf, 2, USB_CTRL_GET_TIMEOUT);
		अगर (ret < 2) अणु
			dev_err(&dlfb->udev->dev,
				"Read EDID byte %d failed: %d\n", i, ret);
			i--;
			अवरोध;
		पूर्ण
		edid[i] = rbuf[1];
	पूर्ण

	kमुक्त(rbuf);

	वापस i;
पूर्ण

अटल पूर्णांक dlfb_ops_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
				अचिन्हित दीर्घ arg)
अणु

	काष्ठा dlfb_data *dlfb = info->par;

	अगर (!atomic_पढ़ो(&dlfb->usb_active))
		वापस 0;

	/* TODO: Update X server to get this from sysfs instead */
	अगर (cmd == DLFB_IOCTL_RETURN_EDID) अणु
		व्योम __user *edid = (व्योम __user *)arg;
		अगर (copy_to_user(edid, dlfb->edid, dlfb->edid_size))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	/* TODO: Help propose a standard fb.h ioctl to report mmap damage */
	अगर (cmd == DLFB_IOCTL_REPORT_DAMAGE) अणु
		काष्ठा dloarea area;

		अगर (copy_from_user(&area, (व्योम __user *)arg,
				  माप(काष्ठा dloarea)))
			वापस -EFAULT;

		/*
		 * If we have a damage-aware client, turn fb_defio "off"
		 * To aव्योम perf imact of unnecessary page fault handling.
		 * Done by resetting the delay क्रम this fb_info to a very
		 * दीर्घ period. Pages will become writable and stay that way.
		 * Reset to normal value when all clients have बंदd this fb.
		 */
		अगर (info->fbdefio)
			info->fbdefio->delay = DL_DEFIO_WRITE_DISABLE;

		अगर (area.x < 0)
			area.x = 0;

		अगर (area.x > info->var.xres)
			area.x = info->var.xres;

		अगर (area.y < 0)
			area.y = 0;

		अगर (area.y > info->var.yres)
			area.y = info->var.yres;

		dlfb_handle_damage(dlfb, area.x, area.y, area.w, area.h);
	पूर्ण

	वापस 0;
पूर्ण

/* taken from vesafb */
अटल पूर्णांक
dlfb_ops_setcolreg(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
	       अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info)
अणु
	पूर्णांक err = 0;

	अगर (regno >= info->cmap.len)
		वापस 1;

	अगर (regno < 16) अणु
		अगर (info->var.red.offset == 10) अणु
			/* 1:5:5:5 */
			((u32 *) (info->pseuकरो_palette))[regno] =
			    ((red & 0xf800) >> 1) |
			    ((green & 0xf800) >> 6) | ((blue & 0xf800) >> 11);
		पूर्ण अन्यथा अणु
			/* 0:5:6:5 */
			((u32 *) (info->pseuकरो_palette))[regno] =
			    ((red & 0xf800)) |
			    ((green & 0xfc00) >> 5) | ((blue & 0xf800) >> 11);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/*
 * It's common क्रम several clients to have framebuffer खोलो simultaneously.
 * e.g. both fbcon and X. Makes things पूर्णांकeresting.
 * Assumes caller is holding info->lock (क्रम खोलो and release at least)
 */
अटल पूर्णांक dlfb_ops_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा dlfb_data *dlfb = info->par;

	/*
	 * fbcon aggressively connects to first framebuffer it finds,
	 * preventing other clients (X) from working properly. Usually
	 * not what the user wants. Fail by शेष with option to enable.
	 */
	अगर ((user == 0) && (!console))
		वापस -EBUSY;

	/* If the USB device is gone, we करोn't accept new खोलोs */
	अगर (dlfb->भवized)
		वापस -ENODEV;

	dlfb->fb_count++;

	अगर (fb_defio && (info->fbdefio == शून्य)) अणु
		/* enable defio at last moment अगर not disabled by client */

		काष्ठा fb_deferred_io *fbdefio;

		fbdefio = kzalloc(माप(काष्ठा fb_deferred_io), GFP_KERNEL);

		अगर (fbdefio) अणु
			fbdefio->delay = DL_DEFIO_WRITE_DELAY;
			fbdefio->deferred_io = dlfb_dpy_deferred_io;
		पूर्ण

		info->fbdefio = fbdefio;
		fb_deferred_io_init(info);
	पूर्ण

	dev_dbg(info->dev, "open, user=%d fb_info=%p count=%d\n",
		user, info, dlfb->fb_count);

	वापस 0;
पूर्ण

अटल व्योम dlfb_ops_destroy(काष्ठा fb_info *info)
अणु
	काष्ठा dlfb_data *dlfb = info->par;

	cancel_work_sync(&dlfb->damage_work);

	mutex_destroy(&dlfb->render_mutex);

	अगर (info->cmap.len != 0)
		fb_dealloc_cmap(&info->cmap);
	अगर (info->monspecs.modedb)
		fb_destroy_modedb(info->monspecs.modedb);
	vमुक्त(info->screen_base);

	fb_destroy_modelist(&info->modelist);

	जबतक (!list_empty(&dlfb->deferred_मुक्त)) अणु
		काष्ठा dlfb_deferred_मुक्त *d = list_entry(dlfb->deferred_मुक्त.next, काष्ठा dlfb_deferred_मुक्त, list);
		list_del(&d->list);
		vमुक्त(d->mem);
		kमुक्त(d);
	पूर्ण
	vमुक्त(dlfb->backing_buffer);
	kमुक्त(dlfb->edid);
	dlfb_मुक्त_urb_list(dlfb);
	usb_put_dev(dlfb->udev);
	kमुक्त(dlfb);

	/* Assume info काष्ठाure is मुक्तd after this poपूर्णांक */
	framebuffer_release(info);
पूर्ण

/*
 * Assumes caller is holding info->lock mutex (क्रम खोलो and release at least)
 */
अटल पूर्णांक dlfb_ops_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा dlfb_data *dlfb = info->par;

	dlfb->fb_count--;

	अगर ((dlfb->fb_count == 0) && (info->fbdefio)) अणु
		fb_deferred_io_cleanup(info);
		kमुक्त(info->fbdefio);
		info->fbdefio = शून्य;
	पूर्ण

	dev_dbg(info->dev, "release, user=%d count=%d\n", user, dlfb->fb_count);

	वापस 0;
पूर्ण

/*
 * Check whether a video mode is supported by the DisplayLink chip
 * We start from monitor's modes, so don't need to filter that here
 */
अटल पूर्णांक dlfb_is_valid_mode(काष्ठा fb_videomode *mode, काष्ठा dlfb_data *dlfb)
अणु
	अगर (mode->xres * mode->yres > dlfb->sku_pixel_limit)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम dlfb_var_color_क्रमmat(काष्ठा fb_var_screeninfo *var)
अणु
	स्थिर काष्ठा fb_bitfield red = अणु 11, 5, 0 पूर्ण;
	स्थिर काष्ठा fb_bitfield green = अणु 5, 6, 0 पूर्ण;
	स्थिर काष्ठा fb_bitfield blue = अणु 0, 5, 0 पूर्ण;

	var->bits_per_pixel = 16;
	var->red = red;
	var->green = green;
	var->blue = blue;
पूर्ण

अटल पूर्णांक dlfb_ops_check_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	काष्ठा fb_videomode mode;
	काष्ठा dlfb_data *dlfb = info->par;

	/* set device-specअगरic elements of var unrelated to mode */
	dlfb_var_color_क्रमmat(var);

	fb_var_to_videomode(&mode, var);

	अगर (!dlfb_is_valid_mode(&mode, dlfb))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक dlfb_ops_set_par(काष्ठा fb_info *info)
अणु
	काष्ठा dlfb_data *dlfb = info->par;
	पूर्णांक result;
	u16 *pix_framebuffer;
	पूर्णांक i;
	काष्ठा fb_var_screeninfo fvs;
	u32 line_length = info->var.xres * (info->var.bits_per_pixel / 8);

	/* clear the activate field because it causes spurious miscompares */
	fvs = info->var;
	fvs.activate = 0;
	fvs.vmode &= ~FB_VMODE_SMOOTH_XPAN;

	अगर (!स_भेद(&dlfb->current_mode, &fvs, माप(काष्ठा fb_var_screeninfo)))
		वापस 0;

	result = dlfb_पुनः_स्मृति_framebuffer(dlfb, info, info->var.yres * line_length);
	अगर (result)
		वापस result;

	result = dlfb_set_video_mode(dlfb, &info->var);

	अगर (result)
		वापस result;

	dlfb->current_mode = fvs;
	info->fix.line_length = line_length;

	अगर (dlfb->fb_count == 0) अणु

		/* paपूर्णांक greenscreen */

		pix_framebuffer = (u16 *) info->screen_base;
		क्रम (i = 0; i < info->fix.smem_len / 2; i++)
			pix_framebuffer[i] = 0x37e6;
	पूर्ण

	dlfb_handle_damage(dlfb, 0, 0, info->var.xres, info->var.yres);

	वापस 0;
पूर्ण

/* To fonzi the jukebox (e.g. make blanking changes take effect) */
अटल अक्षर *dlfb_dummy_render(अक्षर *buf)
अणु
	*buf++ = 0xAF;
	*buf++ = 0x6A; /* copy */
	*buf++ = 0x00; /* from address*/
	*buf++ = 0x00;
	*buf++ = 0x00;
	*buf++ = 0x01; /* one pixel */
	*buf++ = 0x00; /* to address */
	*buf++ = 0x00;
	*buf++ = 0x00;
	वापस buf;
पूर्ण

/*
 * In order to come back from full DPMS off, we need to set the mode again
 */
अटल पूर्णांक dlfb_ops_blank(पूर्णांक blank_mode, काष्ठा fb_info *info)
अणु
	काष्ठा dlfb_data *dlfb = info->par;
	अक्षर *bufptr;
	काष्ठा urb *urb;

	dev_dbg(info->dev, "blank, mode %d --> %d\n",
		dlfb->blank_mode, blank_mode);

	अगर ((dlfb->blank_mode == FB_BLANK_POWERDOWN) &&
	    (blank_mode != FB_BLANK_POWERDOWN)) अणु

		/* वापसing from घातerकरोwn requires a fresh modeset */
		dlfb_set_video_mode(dlfb, &info->var);
	पूर्ण

	urb = dlfb_get_urb(dlfb);
	अगर (!urb)
		वापस 0;

	bufptr = (अक्षर *) urb->transfer_buffer;
	bufptr = dlfb_vidreg_lock(bufptr);
	bufptr = dlfb_blanking(bufptr, blank_mode);
	bufptr = dlfb_vidreg_unlock(bufptr);

	/* seems like a render op is needed to have blank change take effect */
	bufptr = dlfb_dummy_render(bufptr);

	dlfb_submit_urb(dlfb, urb, bufptr -
			(अक्षर *) urb->transfer_buffer);

	dlfb->blank_mode = blank_mode;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops dlfb_ops = अणु
	.owner = THIS_MODULE,
	.fb_पढ़ो = fb_sys_पढ़ो,
	.fb_ग_लिखो = dlfb_ops_ग_लिखो,
	.fb_setcolreg = dlfb_ops_setcolreg,
	.fb_fillrect = dlfb_ops_fillrect,
	.fb_copyarea = dlfb_ops_copyarea,
	.fb_imageblit = dlfb_ops_imageblit,
	.fb_mmap = dlfb_ops_mmap,
	.fb_ioctl = dlfb_ops_ioctl,
	.fb_खोलो = dlfb_ops_खोलो,
	.fb_release = dlfb_ops_release,
	.fb_blank = dlfb_ops_blank,
	.fb_check_var = dlfb_ops_check_var,
	.fb_set_par = dlfb_ops_set_par,
	.fb_destroy = dlfb_ops_destroy,
पूर्ण;


अटल व्योम dlfb_deferred_vमुक्त(काष्ठा dlfb_data *dlfb, व्योम *mem)
अणु
	काष्ठा dlfb_deferred_मुक्त *d = kदो_स्मृति(माप(काष्ठा dlfb_deferred_मुक्त), GFP_KERNEL);
	अगर (!d)
		वापस;
	d->mem = mem;
	list_add(&d->list, &dlfb->deferred_मुक्त);
पूर्ण

/*
 * Assumes &info->lock held by caller
 * Assumes no active clients have framebuffer खोलो
 */
अटल पूर्णांक dlfb_पुनः_स्मृति_framebuffer(काष्ठा dlfb_data *dlfb, काष्ठा fb_info *info, u32 new_len)
अणु
	u32 old_len = info->fix.smem_len;
	स्थिर व्योम *old_fb = (स्थिर व्योम __क्रमce *)info->screen_base;
	अचिन्हित अक्षर *new_fb;
	अचिन्हित अक्षर *new_back = शून्य;

	new_len = PAGE_ALIGN(new_len);

	अगर (new_len > old_len) अणु
		/*
		 * Alloc प्रणाली memory क्रम भव framebuffer
		 */
		new_fb = vदो_स्मृति(new_len);
		अगर (!new_fb) अणु
			dev_err(info->dev, "Virtual framebuffer alloc failed\n");
			वापस -ENOMEM;
		पूर्ण
		स_रखो(new_fb, 0xff, new_len);

		अगर (info->screen_base) अणु
			स_नकल(new_fb, old_fb, old_len);
			dlfb_deferred_vमुक्त(dlfb, (व्योम __क्रमce *)info->screen_base);
		पूर्ण

		info->screen_base = (अक्षर __iomem *)new_fb;
		info->fix.smem_len = new_len;
		info->fix.smem_start = (अचिन्हित दीर्घ) new_fb;
		info->flags = udlfb_info_flags;

		/*
		 * Second framebuffer copy to mirror the framebuffer state
		 * on the physical USB device. We can function without this.
		 * But with imperfect damage info we may send pixels over USB
		 * that were, in fact, unchanged - wasting limited USB bandwidth
		 */
		अगर (shaकरोw)
			new_back = vzalloc(new_len);
		अगर (!new_back)
			dev_info(info->dev,
				 "No shadow/backing buffer allocated\n");
		अन्यथा अणु
			dlfb_deferred_vमुक्त(dlfb, dlfb->backing_buffer);
			dlfb->backing_buffer = new_back;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * 1) Get EDID from hw, or use sw शेष
 * 2) Parse पूर्णांकo various fb_info काष्ठाs
 * 3) Allocate भव framebuffer memory to back highest res mode
 *
 * Parses EDID पूर्णांकo three places used by various parts of fbdev:
 * fb_var_screeninfo contains the timing of the monitor's preferred mode
 * fb_info.monspecs is full parsed EDID info, including monspecs.modedb
 * fb_info.modelist is a linked list of all monitor & VESA modes which work
 *
 * If EDID is not पढ़ोable/valid, then modelist is all VESA modes,
 * monspecs is शून्य, and fb_var_screeninfo is set to safe VESA mode
 * Returns 0 अगर successful
 */
अटल पूर्णांक dlfb_setup_modes(काष्ठा dlfb_data *dlfb,
			   काष्ठा fb_info *info,
			   अक्षर *शेष_edid, माप_प्रकार शेष_edid_size)
अणु
	अक्षर *edid;
	पूर्णांक i, result = 0, tries = 3;
	काष्ठा device *dev = info->device;
	काष्ठा fb_videomode *mode;
	स्थिर काष्ठा fb_videomode *शेष_vmode = शून्य;

	अगर (info->dev) अणु
		/* only use mutex अगर info has been रेजिस्टरed */
		mutex_lock(&info->lock);
		/* parent device is used otherwise */
		dev = info->dev;
	पूर्ण

	edid = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL);
	अगर (!edid) अणु
		result = -ENOMEM;
		जाओ error;
	पूर्ण

	fb_destroy_modelist(&info->modelist);
	स_रखो(&info->monspecs, 0, माप(info->monspecs));

	/*
	 * Try to (re)पढ़ो EDID from hardware first
	 * EDID data may वापस, but not parse as valid
	 * Try again a few बार, in हाल of e.g. analog cable noise
	 */
	जबतक (tries--) अणु

		i = dlfb_get_edid(dlfb, edid, EDID_LENGTH);

		अगर (i >= EDID_LENGTH)
			fb_edid_to_monspecs(edid, &info->monspecs);

		अगर (info->monspecs.modedb_len > 0) अणु
			dlfb->edid = edid;
			dlfb->edid_size = i;
			अवरोध;
		पूर्ण
	पूर्ण

	/* If that fails, use a previously वापसed EDID अगर available */
	अगर (info->monspecs.modedb_len == 0) अणु
		dev_err(dev, "Unable to get valid EDID from device/display\n");

		अगर (dlfb->edid) अणु
			fb_edid_to_monspecs(dlfb->edid, &info->monspecs);
			अगर (info->monspecs.modedb_len > 0)
				dev_err(dev, "Using previously queried EDID\n");
		पूर्ण
	पूर्ण

	/* If that fails, use the शेष EDID we were handed */
	अगर (info->monspecs.modedb_len == 0) अणु
		अगर (शेष_edid_size >= EDID_LENGTH) अणु
			fb_edid_to_monspecs(शेष_edid, &info->monspecs);
			अगर (info->monspecs.modedb_len > 0) अणु
				स_नकल(edid, शेष_edid, शेष_edid_size);
				dlfb->edid = edid;
				dlfb->edid_size = शेष_edid_size;
				dev_err(dev, "Using default/backup EDID\n");
			पूर्ण
		पूर्ण
	पूर्ण

	/* If we've got modes, let's pick a best शेष mode */
	अगर (info->monspecs.modedb_len > 0) अणु

		क्रम (i = 0; i < info->monspecs.modedb_len; i++) अणु
			mode = &info->monspecs.modedb[i];
			अगर (dlfb_is_valid_mode(mode, dlfb)) अणु
				fb_add_videomode(mode, &info->modelist);
			पूर्ण अन्यथा अणु
				dev_dbg(dev, "Specified mode %dx%d too big\n",
					mode->xres, mode->yres);
				अगर (i == 0)
					/* अगर we've हटाओd top/best mode */
					info->monspecs.misc
						&= ~FB_MISC_1ST_DETAIL;
			पूर्ण
		पूर्ण

		शेष_vmode = fb_find_best_display(&info->monspecs,
						     &info->modelist);
	पूर्ण

	/* If everything अन्यथा has failed, fall back to safe शेष mode */
	अगर (शेष_vmode == शून्य) अणु

		काष्ठा fb_videomode fb_vmode = अणु0पूर्ण;

		/*
		 * Add the standard VESA modes to our modelist
		 * Since we करोn't have EDID, there may be modes that
		 * overspec monitor and/or are incorrect aspect ratio, etc.
		 * But at least the user has a chance to choose
		 */
		क्रम (i = 0; i < VESA_MODEDB_SIZE; i++) अणु
			mode = (काष्ठा fb_videomode *)&vesa_modes[i];
			अगर (dlfb_is_valid_mode(mode, dlfb))
				fb_add_videomode(mode, &info->modelist);
			अन्यथा
				dev_dbg(dev, "VESA mode %dx%d too big\n",
					mode->xres, mode->yres);
		पूर्ण

		/*
		 * शेष to resolution safe क्रम projectors
		 * (since they are most common हाल without EDID)
		 */
		fb_vmode.xres = 800;
		fb_vmode.yres = 600;
		fb_vmode.refresh = 60;
		शेष_vmode = fb_find_nearest_mode(&fb_vmode,
						     &info->modelist);
	पूर्ण

	/* If we have good mode and no active clients*/
	अगर ((शेष_vmode != शून्य) && (dlfb->fb_count == 0)) अणु

		fb_videomode_to_var(&info->var, शेष_vmode);
		dlfb_var_color_क्रमmat(&info->var);

		/*
		 * with mode size info, we can now alloc our framebuffer.
		 */
		स_नकल(&info->fix, &dlfb_fix, माप(dlfb_fix));
	पूर्ण अन्यथा
		result = -EINVAL;

error:
	अगर (edid && (dlfb->edid != edid))
		kमुक्त(edid);

	अगर (info->dev)
		mutex_unlock(&info->lock);

	वापस result;
पूर्ण

अटल sमाप_प्रकार metrics_bytes_rendered_show(काष्ठा device *fbdev,
				   काष्ठा device_attribute *a, अक्षर *buf) अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
			atomic_पढ़ो(&dlfb->bytes_rendered));
पूर्ण

अटल sमाप_प्रकार metrics_bytes_identical_show(काष्ठा device *fbdev,
				   काष्ठा device_attribute *a, अक्षर *buf) अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
			atomic_पढ़ो(&dlfb->bytes_identical));
पूर्ण

अटल sमाप_प्रकार metrics_bytes_sent_show(काष्ठा device *fbdev,
				   काष्ठा device_attribute *a, अक्षर *buf) अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
			atomic_पढ़ो(&dlfb->bytes_sent));
पूर्ण

अटल sमाप_प्रकार metrics_cpu_kcycles_used_show(काष्ठा device *fbdev,
				   काष्ठा device_attribute *a, अक्षर *buf) अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;
	वापस snम_लिखो(buf, PAGE_SIZE, "%u\n",
			atomic_पढ़ो(&dlfb->cpu_kcycles_used));
पूर्ण

अटल sमाप_प्रकार edid_show(
			काष्ठा file *filp,
			काष्ठा kobject *kobj, काष्ठा bin_attribute *a,
			 अक्षर *buf, loff_t off, माप_प्रकार count) अणु
	काष्ठा device *fbdev = kobj_to_dev(kobj);
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;

	अगर (dlfb->edid == शून्य)
		वापस 0;

	अगर ((off >= dlfb->edid_size) || (count > dlfb->edid_size))
		वापस 0;

	अगर (off + count > dlfb->edid_size)
		count = dlfb->edid_size - off;

	स_नकल(buf, dlfb->edid, count);

	वापस count;
पूर्ण

अटल sमाप_प्रकार edid_store(
			काष्ठा file *filp,
			काष्ठा kobject *kobj, काष्ठा bin_attribute *a,
			अक्षर *src, loff_t src_off, माप_प्रकार src_size) अणु
	काष्ठा device *fbdev = kobj_to_dev(kobj);
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;
	पूर्णांक ret;

	/* We only support ग_लिखो of entire EDID at once, no offset*/
	अगर ((src_size != EDID_LENGTH) || (src_off != 0))
		वापस -EINVAL;

	ret = dlfb_setup_modes(dlfb, fb_info, src, src_size);
	अगर (ret)
		वापस ret;

	अगर (!dlfb->edid || स_भेद(src, dlfb->edid, src_size))
		वापस -EINVAL;

	ret = dlfb_ops_set_par(fb_info);
	अगर (ret)
		वापस ret;

	वापस src_size;
पूर्ण

अटल sमाप_प्रकार metrics_reset_store(काष्ठा device *fbdev,
			   काष्ठा device_attribute *attr,
			   स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fb_info *fb_info = dev_get_drvdata(fbdev);
	काष्ठा dlfb_data *dlfb = fb_info->par;

	atomic_set(&dlfb->bytes_rendered, 0);
	atomic_set(&dlfb->bytes_identical, 0);
	atomic_set(&dlfb->bytes_sent, 0);
	atomic_set(&dlfb->cpu_kcycles_used, 0);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा bin_attribute edid_attr = अणु
	.attr.name = "edid",
	.attr.mode = 0666,
	.size = EDID_LENGTH,
	.पढ़ो = edid_show,
	.ग_लिखो = edid_store
पूर्ण;

अटल स्थिर काष्ठा device_attribute fb_device_attrs[] = अणु
	__ATTR_RO(metrics_bytes_rendered),
	__ATTR_RO(metrics_bytes_identical),
	__ATTR_RO(metrics_bytes_sent),
	__ATTR_RO(metrics_cpu_kcycles_used),
	__ATTR(metrics_reset, S_IWUSR, शून्य, metrics_reset_store),
पूर्ण;

/*
 * This is necessary beक्रमe we can communicate with the display controller.
 */
अटल पूर्णांक dlfb_select_std_channel(काष्ठा dlfb_data *dlfb)
अणु
	पूर्णांक ret;
	व्योम *buf;
	अटल स्थिर u8 set_def_chn[] = अणु
				0x57, 0xCD, 0xDC, 0xA7,
				0x1C, 0x88, 0x5E, 0x15,
				0x60, 0xFE, 0xC6, 0x97,
				0x16, 0x3D, 0x47, 0xF2  पूर्ण;

	buf = kmemdup(set_def_chn, माप(set_def_chn), GFP_KERNEL);

	अगर (!buf)
		वापस -ENOMEM;

	ret = usb_control_msg(dlfb->udev, usb_sndctrlpipe(dlfb->udev, 0),
			NR_USB_REQUEST_CHANNEL,
			(USB_सूची_OUT | USB_TYPE_VENDOR), 0, 0,
			buf, माप(set_def_chn), USB_CTRL_SET_TIMEOUT);

	kमुक्त(buf);

	वापस ret;
पूर्ण

अटल पूर्णांक dlfb_parse_venकरोr_descriptor(काष्ठा dlfb_data *dlfb,
					काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	अक्षर *desc;
	अक्षर *buf;
	अक्षर *desc_end;
	पूर्णांक total_len;

	buf = kzalloc(MAX_VENDOR_DESCRIPTOR_SIZE, GFP_KERNEL);
	अगर (!buf)
		वापस false;
	desc = buf;

	total_len = usb_get_descriptor(पूर्णांकerface_to_usbdev(पूर्णांकf),
					0x5f, /* venकरोr specअगरic */
					0, desc, MAX_VENDOR_DESCRIPTOR_SIZE);

	/* अगर not found, look in configuration descriptor */
	अगर (total_len < 0) अणु
		अगर (0 == usb_get_extra_descriptor(पूर्णांकf->cur_altsetting,
			0x5f, &desc))
			total_len = (पूर्णांक) desc[0];
	पूर्ण

	अगर (total_len > 5) अणु
		dev_info(&पूर्णांकf->dev,
			 "vendor descriptor length: %d data: %11ph\n",
			 total_len, desc);

		अगर ((desc[0] != total_len) || /* descriptor length */
		    (desc[1] != 0x5f) ||   /* venकरोr descriptor type */
		    (desc[2] != 0x01) ||   /* version (2 bytes) */
		    (desc[3] != 0x00) ||
		    (desc[4] != total_len - 2)) /* length after type */
			जाओ unrecognized;

		desc_end = desc + total_len;
		desc += 5; /* the fixed header we've alपढ़ोy parsed */

		जबतक (desc < desc_end) अणु
			u8 length;
			u16 key;

			key = *desc++;
			key |= (u16)*desc++ << 8;
			length = *desc++;

			चयन (key) अणु
			हाल 0x0200: अणु /* max_area */
				u32 max_area = *desc++;
				max_area |= (u32)*desc++ << 8;
				max_area |= (u32)*desc++ << 16;
				max_area |= (u32)*desc++ << 24;
				dev_warn(&पूर्णांकf->dev,
					 "DL chip limited to %d pixel modes\n",
					 max_area);
				dlfb->sku_pixel_limit = max_area;
				अवरोध;
			पूर्ण
			शेष:
				अवरोध;
			पूर्ण
			desc += length;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info(&पूर्णांकf->dev, "vendor descriptor not available (%d)\n",
			 total_len);
	पूर्ण

	जाओ success;

unrecognized:
	/* allow udlfb to load क्रम now even अगर firmware unrecognized */
	dev_err(&पूर्णांकf->dev, "Unrecognized vendor firmware descriptor\n");

success:
	kमुक्त(buf);
	वापस true;
पूर्ण

अटल पूर्णांक dlfb_usb_probe(काष्ठा usb_पूर्णांकerface *पूर्णांकf,
			  स्थिर काष्ठा usb_device_id *id)
अणु
	पूर्णांक i;
	स्थिर काष्ठा device_attribute *attr;
	काष्ठा dlfb_data *dlfb;
	काष्ठा fb_info *info;
	पूर्णांक retval = -ENOMEM;
	काष्ठा usb_device *usbdev = पूर्णांकerface_to_usbdev(पूर्णांकf);

	/* usb initialization */
	dlfb = kzalloc(माप(*dlfb), GFP_KERNEL);
	अगर (!dlfb) अणु
		dev_err(&पूर्णांकf->dev, "%s: failed to allocate dlfb\n", __func__);
		वापस -ENOMEM;
	पूर्ण

	INIT_LIST_HEAD(&dlfb->deferred_मुक्त);

	dlfb->udev = usb_get_dev(usbdev);
	usb_set_पूर्णांकfdata(पूर्णांकf, dlfb);

	dev_dbg(&पूर्णांकf->dev, "console enable=%d\n", console);
	dev_dbg(&पूर्णांकf->dev, "fb_defio enable=%d\n", fb_defio);
	dev_dbg(&पूर्णांकf->dev, "shadow enable=%d\n", shaकरोw);

	dlfb->sku_pixel_limit = 2048 * 1152; /* शेष to maximum */

	अगर (!dlfb_parse_venकरोr_descriptor(dlfb, पूर्णांकf)) अणु
		dev_err(&पूर्णांकf->dev,
			"firmware not recognized, incompatible device?\n");
		जाओ error;
	पूर्ण

	अगर (pixel_limit) अणु
		dev_warn(&पूर्णांकf->dev,
			 "DL chip limit of %d overridden to %d\n",
			 dlfb->sku_pixel_limit, pixel_limit);
		dlfb->sku_pixel_limit = pixel_limit;
	पूर्ण


	/* allocates framebuffer driver काष्ठाure, not framebuffer memory */
	info = framebuffer_alloc(0, &dlfb->udev->dev);
	अगर (!info)
		जाओ error;

	dlfb->info = info;
	info->par = dlfb;
	info->pseuकरो_palette = dlfb->pseuकरो_palette;
	dlfb->ops = dlfb_ops;
	info->fbops = &dlfb->ops;

	mutex_init(&dlfb->render_mutex);
	dlfb_init_damage(dlfb);
	spin_lock_init(&dlfb->damage_lock);
	INIT_WORK(&dlfb->damage_work, dlfb_damage_work);

	INIT_LIST_HEAD(&info->modelist);

	अगर (!dlfb_alloc_urb_list(dlfb, WRITES_IN_FLIGHT, MAX_TRANSFER)) अणु
		retval = -ENOMEM;
		dev_err(&पूर्णांकf->dev, "unable to allocate urb list\n");
		जाओ error;
	पूर्ण

	/* We करोn't रेजिस्टर a new USB class. Our client पूर्णांकerface is dlfbev */

	retval = fb_alloc_cmap(&info->cmap, 256, 0);
	अगर (retval < 0) अणु
		dev_err(info->device, "cmap allocation failed: %d\n", retval);
		जाओ error;
	पूर्ण

	retval = dlfb_setup_modes(dlfb, info, शून्य, 0);
	अगर (retval != 0) अणु
		dev_err(info->device,
			"unable to find common mode for display and adapter\n");
		जाओ error;
	पूर्ण

	/* पढ़ोy to begin using device */

	atomic_set(&dlfb->usb_active, 1);
	dlfb_select_std_channel(dlfb);

	dlfb_ops_check_var(&info->var, info);
	retval = dlfb_ops_set_par(info);
	अगर (retval)
		जाओ error;

	retval = रेजिस्टर_framebuffer(info);
	अगर (retval < 0) अणु
		dev_err(info->device, "unable to register framebuffer: %d\n",
			retval);
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(fb_device_attrs); i++) अणु
		attr = &fb_device_attrs[i];
		retval = device_create_file(info->dev, attr);
		अगर (retval)
			dev_warn(info->device,
				 "failed to create '%s' attribute: %d\n",
				 attr->attr.name, retval);
	पूर्ण

	retval = device_create_bin_file(info->dev, &edid_attr);
	अगर (retval)
		dev_warn(info->device, "failed to create '%s' attribute: %d\n",
			 edid_attr.attr.name, retval);

	dev_info(info->device,
		 "%s is DisplayLink USB device (%dx%d, %dK framebuffer memory)\n",
		 dev_name(info->dev), info->var.xres, info->var.yres,
		 ((dlfb->backing_buffer) ?
		 info->fix.smem_len * 2 : info->fix.smem_len) >> 10);
	वापस 0;

error:
	अगर (dlfb->info) अणु
		dlfb_ops_destroy(dlfb->info);
	पूर्ण अन्यथा अणु
		usb_put_dev(dlfb->udev);
		kमुक्त(dlfb);
	पूर्ण
	वापस retval;
पूर्ण

अटल व्योम dlfb_usb_disconnect(काष्ठा usb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा dlfb_data *dlfb;
	काष्ठा fb_info *info;
	पूर्णांक i;

	dlfb = usb_get_पूर्णांकfdata(पूर्णांकf);
	info = dlfb->info;

	dev_dbg(&पूर्णांकf->dev, "USB disconnect starting\n");

	/* we भवize until all fb clients release. Then we मुक्त */
	dlfb->भवized = true;

	/* When non-active we'll update भव framebuffer, but no new urbs */
	atomic_set(&dlfb->usb_active, 0);

	/* this function will रुको क्रम all in-flight urbs to complete */
	dlfb_मुक्त_urb_list(dlfb);

	/* हटाओ udlfb's sysfs पूर्णांकerfaces */
	क्रम (i = 0; i < ARRAY_SIZE(fb_device_attrs); i++)
		device_हटाओ_file(info->dev, &fb_device_attrs[i]);
	device_हटाओ_bin_file(info->dev, &edid_attr);

	unरेजिस्टर_framebuffer(info);
पूर्ण

अटल काष्ठा usb_driver dlfb_driver = अणु
	.name = "udlfb",
	.probe = dlfb_usb_probe,
	.disconnect = dlfb_usb_disconnect,
	.id_table = id_table,
पूर्ण;

module_usb_driver(dlfb_driver);

अटल व्योम dlfb_urb_completion(काष्ठा urb *urb)
अणु
	काष्ठा urb_node *unode = urb->context;
	काष्ठा dlfb_data *dlfb = unode->dlfb;
	अचिन्हित दीर्घ flags;

	चयन (urb->status) अणु
	हाल 0:
		/* success */
		अवरोध;
	हाल -ECONNRESET:
	हाल -ENOENT:
	हाल -ESHUTDOWN:
		/* sync/async unlink faults aren't errors */
		अवरोध;
	शेष:
		dev_err(&dlfb->udev->dev,
			"%s - nonzero write bulk status received: %d\n",
			__func__, urb->status);
		atomic_set(&dlfb->lost_pixels, 1);
		अवरोध;
	पूर्ण

	urb->transfer_buffer_length = dlfb->urbs.size; /* reset to actual */

	spin_lock_irqsave(&dlfb->urbs.lock, flags);
	list_add_tail(&unode->entry, &dlfb->urbs.list);
	dlfb->urbs.available++;
	spin_unlock_irqrestore(&dlfb->urbs.lock, flags);

	up(&dlfb->urbs.limit_sem);
पूर्ण

अटल व्योम dlfb_मुक्त_urb_list(काष्ठा dlfb_data *dlfb)
अणु
	पूर्णांक count = dlfb->urbs.count;
	काष्ठा list_head *node;
	काष्ठा urb_node *unode;
	काष्ठा urb *urb;

	/* keep रुकोing and मुक्तing, until we've got 'em all */
	जबतक (count--) अणु
		करोwn(&dlfb->urbs.limit_sem);

		spin_lock_irq(&dlfb->urbs.lock);

		node = dlfb->urbs.list.next; /* have reserved one with sem */
		list_del_init(node);

		spin_unlock_irq(&dlfb->urbs.lock);

		unode = list_entry(node, काष्ठा urb_node, entry);
		urb = unode->urb;

		/* Free each separately allocated piece */
		usb_मुक्त_coherent(urb->dev, dlfb->urbs.size,
				  urb->transfer_buffer, urb->transfer_dma);
		usb_मुक्त_urb(urb);
		kमुक्त(node);
	पूर्ण

	dlfb->urbs.count = 0;
पूर्ण

अटल पूर्णांक dlfb_alloc_urb_list(काष्ठा dlfb_data *dlfb, पूर्णांक count, माप_प्रकार size)
अणु
	काष्ठा urb *urb;
	काष्ठा urb_node *unode;
	अक्षर *buf;
	माप_प्रकार wanted_size = count * size;

	spin_lock_init(&dlfb->urbs.lock);

retry:
	dlfb->urbs.size = size;
	INIT_LIST_HEAD(&dlfb->urbs.list);

	sema_init(&dlfb->urbs.limit_sem, 0);
	dlfb->urbs.count = 0;
	dlfb->urbs.available = 0;

	जबतक (dlfb->urbs.count * size < wanted_size) अणु
		unode = kzalloc(माप(*unode), GFP_KERNEL);
		अगर (!unode)
			अवरोध;
		unode->dlfb = dlfb;

		urb = usb_alloc_urb(0, GFP_KERNEL);
		अगर (!urb) अणु
			kमुक्त(unode);
			अवरोध;
		पूर्ण
		unode->urb = urb;

		buf = usb_alloc_coherent(dlfb->udev, size, GFP_KERNEL,
					 &urb->transfer_dma);
		अगर (!buf) अणु
			kमुक्त(unode);
			usb_मुक्त_urb(urb);
			अगर (size > PAGE_SIZE) अणु
				size /= 2;
				dlfb_मुक्त_urb_list(dlfb);
				जाओ retry;
			पूर्ण
			अवरोध;
		पूर्ण

		/* urb->transfer_buffer_length set to actual beक्रमe submit */
		usb_fill_bulk_urb(urb, dlfb->udev, usb_sndbulkpipe(dlfb->udev, 1),
			buf, size, dlfb_urb_completion, unode);
		urb->transfer_flags |= URB_NO_TRANSFER_DMA_MAP;

		list_add_tail(&unode->entry, &dlfb->urbs.list);

		up(&dlfb->urbs.limit_sem);
		dlfb->urbs.count++;
		dlfb->urbs.available++;
	पूर्ण

	वापस dlfb->urbs.count;
पूर्ण

अटल काष्ठा urb *dlfb_get_urb(काष्ठा dlfb_data *dlfb)
अणु
	पूर्णांक ret;
	काष्ठा list_head *entry;
	काष्ठा urb_node *unode;

	/* Wait क्रम an in-flight buffer to complete and get re-queued */
	ret = करोwn_समयout(&dlfb->urbs.limit_sem, GET_URB_TIMEOUT);
	अगर (ret) अणु
		atomic_set(&dlfb->lost_pixels, 1);
		dev_warn(&dlfb->udev->dev,
			 "wait for urb interrupted: %d available: %d\n",
			 ret, dlfb->urbs.available);
		वापस शून्य;
	पूर्ण

	spin_lock_irq(&dlfb->urbs.lock);

	BUG_ON(list_empty(&dlfb->urbs.list)); /* reserved one with limit_sem */
	entry = dlfb->urbs.list.next;
	list_del_init(entry);
	dlfb->urbs.available--;

	spin_unlock_irq(&dlfb->urbs.lock);

	unode = list_entry(entry, काष्ठा urb_node, entry);
	वापस unode->urb;
पूर्ण

अटल पूर्णांक dlfb_submit_urb(काष्ठा dlfb_data *dlfb, काष्ठा urb *urb, माप_प्रकार len)
अणु
	पूर्णांक ret;

	BUG_ON(len > dlfb->urbs.size);

	urb->transfer_buffer_length = len; /* set to actual payload len */
	ret = usb_submit_urb(urb, GFP_KERNEL);
	अगर (ret) अणु
		dlfb_urb_completion(urb); /* because no one अन्यथा will */
		atomic_set(&dlfb->lost_pixels, 1);
		dev_err(&dlfb->udev->dev, "submit urb error: %d\n", ret);
	पूर्ण
	वापस ret;
पूर्ण

module_param(console, bool, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
MODULE_PARM_DESC(console, "Allow fbcon to open framebuffer");

module_param(fb_defio, bool, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
MODULE_PARM_DESC(fb_defio, "Page fault detection of mmap writes");

module_param(shaकरोw, bool, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
MODULE_PARM_DESC(shaकरोw, "Shadow vid mem. Disable to save mem but lose perf");

module_param(pixel_limit, पूर्णांक, S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP);
MODULE_PARM_DESC(pixel_limit, "Force limit on max mode (in x*y pixels)");

MODULE_AUTHOR("Roberto De Ioris <roberto@unbit.it>, "
	      "Jaya Kumar <jayakumar.lkml@gmail.com>, "
	      "Bernie Thompson <bernie@plugable.com>");
MODULE_DESCRIPTION("DisplayLink kernel framebuffer driver");
MODULE_LICENSE("GPL");

