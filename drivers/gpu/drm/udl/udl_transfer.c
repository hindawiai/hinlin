<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Red Hat
 * based in parts on udlfb.c:
 * Copyright (C) 2009 Roberto De Ioris <roberto@unbit.it>
 * Copyright (C) 2009 Jaya Kumar <jayakumar.lkml@gmail.com>
 * Copyright (C) 2009 Bernie Thompson <bernie@plugable.com>
 */

#समावेश <यंत्र/unaligned.h>

#समावेश "udl_drv.h"

#घोषणा MAX_CMD_PIXELS		255

#घोषणा RLX_HEADER_BYTES	7
#घोषणा MIN_RLX_PIX_BYTES       4
#घोषणा MIN_RLX_CMD_BYTES	(RLX_HEADER_BYTES + MIN_RLX_PIX_BYTES)

#घोषणा RLE_HEADER_BYTES	6
#घोषणा MIN_RLE_PIX_BYTES	3
#घोषणा MIN_RLE_CMD_BYTES	(RLE_HEADER_BYTES + MIN_RLE_PIX_BYTES)

#घोषणा RAW_HEADER_BYTES	6
#घोषणा MIN_RAW_PIX_BYTES	2
#घोषणा MIN_RAW_CMD_BYTES	(RAW_HEADER_BYTES + MIN_RAW_PIX_BYTES)

/*
 * Trims identical data from front and back of line
 * Sets new front buffer address and width
 * And वापसs byte count of identical pixels
 * Assumes CPU natural alignment (अचिन्हित दीर्घ)
 * क्रम back and front buffer ptrs and width
 */
#अगर 0
अटल पूर्णांक udl_trim_hline(स्थिर u8 *bback, स्थिर u8 **bfront, पूर्णांक *width_bytes)
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
#पूर्ण_अगर

अटल अंतरभूत u16 pixel32_to_be16(स्थिर uपूर्णांक32_t pixel)
अणु
	वापस (((pixel >> 3) & 0x001f) |
		((pixel >> 5) & 0x07e0) |
		((pixel >> 8) & 0xf800));
पूर्ण

अटल अंतरभूत u16 get_pixel_val16(स्थिर uपूर्णांक8_t *pixel, पूर्णांक log_bpp)
अणु
	u16 pixel_val16;
	अगर (log_bpp == 1)
		pixel_val16 = *(स्थिर uपूर्णांक16_t *)pixel;
	अन्यथा
		pixel_val16 = pixel32_to_be16(*(स्थिर uपूर्णांक32_t *)pixel);
	वापस pixel_val16;
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
अटल व्योम udl_compress_hline16(
	स्थिर u8 **pixel_start_ptr,
	स्थिर u8 *स्थिर pixel_end,
	uपूर्णांक32_t *device_address_ptr,
	uपूर्णांक8_t **command_buffer_ptr,
	स्थिर uपूर्णांक8_t *स्थिर cmd_buffer_end, पूर्णांक log_bpp)
अणु
	स्थिर पूर्णांक bpp = 1 << log_bpp;
	स्थिर u8 *pixel = *pixel_start_ptr;
	uपूर्णांक32_t dev_addr  = *device_address_ptr;
	uपूर्णांक8_t *cmd = *command_buffer_ptr;

	जबतक ((pixel_end > pixel) &&
	       (cmd_buffer_end - MIN_RLX_CMD_BYTES > cmd)) अणु
		uपूर्णांक8_t *raw_pixels_count_byte = शून्य;
		uपूर्णांक8_t *cmd_pixels_count_byte = शून्य;
		स्थिर u8 *raw_pixel_start = शून्य;
		स्थिर u8 *cmd_pixel_start, *cmd_pixel_end = शून्य;
		uपूर्णांक16_t pixel_val16;

		*cmd++ = 0xaf;
		*cmd++ = 0x6b;
		*cmd++ = (uपूर्णांक8_t) ((dev_addr >> 16) & 0xFF);
		*cmd++ = (uपूर्णांक8_t) ((dev_addr >> 8) & 0xFF);
		*cmd++ = (uपूर्णांक8_t) ((dev_addr) & 0xFF);

		cmd_pixels_count_byte = cmd++; /*  we'll know this later */
		cmd_pixel_start = pixel;

		raw_pixels_count_byte = cmd++; /*  we'll know this later */
		raw_pixel_start = pixel;

		cmd_pixel_end = pixel + (min3(MAX_CMD_PIXELS + 1UL,
					(अचिन्हित दीर्घ)(pixel_end - pixel) >> log_bpp,
					(अचिन्हित दीर्घ)(cmd_buffer_end - 1 - cmd) / 2) << log_bpp);

		pixel_val16 = get_pixel_val16(pixel, log_bpp);

		जबतक (pixel < cmd_pixel_end) अणु
			स्थिर u8 *स्थिर start = pixel;
			स्थिर uपूर्णांक16_t repeating_pixel_val16 = pixel_val16;

			put_unaligned_be16(pixel_val16, cmd);

			cmd += 2;
			pixel += bpp;

			जबतक (pixel < cmd_pixel_end) अणु
				pixel_val16 = get_pixel_val16(pixel, log_bpp);
				अगर (pixel_val16 != repeating_pixel_val16)
					अवरोध;
				pixel += bpp;
			पूर्ण

			अगर (unlikely(pixel > start + bpp)) अणु
				/* go back and fill in raw pixel count */
				*raw_pixels_count_byte = (((start -
						raw_pixel_start) >> log_bpp) + 1) & 0xFF;

				/* immediately after raw data is repeat byte */
				*cmd++ = (((pixel - start) >> log_bpp) - 1) & 0xFF;

				/* Then start another raw pixel span */
				raw_pixel_start = pixel;
				raw_pixels_count_byte = cmd++;
			पूर्ण
		पूर्ण

		अगर (pixel > raw_pixel_start) अणु
			/* finalize last RAW span */
			*raw_pixels_count_byte = ((pixel - raw_pixel_start) >> log_bpp) & 0xFF;
		पूर्ण अन्यथा अणु
			/* unकरो unused byte */
			cmd--;
		पूर्ण

		*cmd_pixels_count_byte = ((pixel - cmd_pixel_start) >> log_bpp) & 0xFF;
		dev_addr += ((pixel - cmd_pixel_start) >> log_bpp) * 2;
	पूर्ण

	अगर (cmd_buffer_end <= MIN_RLX_CMD_BYTES + cmd) अणु
		/* Fill leftover bytes with no-ops */
		अगर (cmd_buffer_end > cmd)
			स_रखो(cmd, 0xAF, cmd_buffer_end - cmd);
		cmd = (uपूर्णांक8_t *) cmd_buffer_end;
	पूर्ण

	*command_buffer_ptr = cmd;
	*pixel_start_ptr = pixel;
	*device_address_ptr = dev_addr;

	वापस;
पूर्ण

/*
 * There are 3 copies of every pixel: The front buffer that the fbdev
 * client renders to, the actual framebuffer across the USB bus in hardware
 * (that we can only ग_लिखो to, slowly, and can never पढ़ो), and (optionally)
 * our shaकरोw copy that tracks what's been sent to that hardware buffer.
 */
पूर्णांक udl_render_hline(काष्ठा drm_device *dev, पूर्णांक log_bpp, काष्ठा urb **urb_ptr,
		     स्थिर अक्षर *front, अक्षर **urb_buf_ptr,
		     u32 byte_offset, u32 device_byte_offset,
		     u32 byte_width)
अणु
	स्थिर u8 *line_start, *line_end, *next_pixel;
	u32 base16 = 0 + (device_byte_offset >> log_bpp) * 2;
	काष्ठा urb *urb = *urb_ptr;
	u8 *cmd = *urb_buf_ptr;
	u8 *cmd_end = (u8 *) urb->transfer_buffer + urb->transfer_buffer_length;

	BUG_ON(!(log_bpp == 1 || log_bpp == 2));

	line_start = (u8 *) (front + byte_offset);
	next_pixel = line_start;
	line_end = next_pixel + byte_width;

	जबतक (next_pixel < line_end) अणु

		udl_compress_hline16(&next_pixel,
			     line_end, &base16,
			     (u8 **) &cmd, (u8 *) cmd_end, log_bpp);

		अगर (cmd >= cmd_end) अणु
			पूर्णांक len = cmd - (u8 *) urb->transfer_buffer;
			पूर्णांक ret = udl_submit_urb(dev, urb, len);
			अगर (ret)
				वापस ret;
			urb = udl_get_urb(dev);
			अगर (!urb)
				वापस -EAGAIN;
			*urb_ptr = urb;
			cmd = urb->transfer_buffer;
			cmd_end = &cmd[urb->transfer_buffer_length];
		पूर्ण
	पूर्ण

	*urb_buf_ptr = cmd;

	वापस 0;
पूर्ण
