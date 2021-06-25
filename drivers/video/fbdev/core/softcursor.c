<शैली गुरु>
/*
 * linux/drivers/video/console/softcursor.c
 *
 * Generic software cursor क्रम frame buffer devices
 *
 *  Created 14 Nov 2002 by James Simmons
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the मुख्य directory of this
 * archive क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

#समावेश "fbcon.h"

पूर्णांक soft_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	अचिन्हित पूर्णांक scan_align = info->pixmap.scan_align - 1;
	अचिन्हित पूर्णांक buf_align = info->pixmap.buf_align - 1;
	अचिन्हित पूर्णांक i, size, dsize, s_pitch, d_pitch;
	काष्ठा fb_image *image;
	u8 *src, *dst;

	अगर (info->state != FBINFO_STATE_RUNNING)
		वापस 0;

	s_pitch = (cursor->image.width + 7) >> 3;
	dsize = s_pitch * cursor->image.height;

	अगर (dsize + माप(काष्ठा fb_image) != ops->cursor_size) अणु
		kमुक्त(ops->cursor_src);
		ops->cursor_size = dsize + माप(काष्ठा fb_image);

		ops->cursor_src = kदो_स्मृति(ops->cursor_size, GFP_ATOMIC);
		अगर (!ops->cursor_src) अणु
			ops->cursor_size = 0;
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	src = ops->cursor_src + माप(काष्ठा fb_image);
	image = (काष्ठा fb_image *)ops->cursor_src;
	*image = cursor->image;
	d_pitch = (s_pitch + scan_align) & ~scan_align;

	size = d_pitch * image->height + buf_align;
	size &= ~buf_align;
	dst = fb_get_buffer_offset(info, &info->pixmap, size);

	अगर (cursor->enable) अणु
		चयन (cursor->rop) अणु
		हाल ROP_XOR:
			क्रम (i = 0; i < dsize; i++)
				src[i] = image->data[i] ^ cursor->mask[i];
			अवरोध;
		हाल ROP_COPY:
		शेष:
			क्रम (i = 0; i < dsize; i++)
				src[i] = image->data[i] & cursor->mask[i];
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा
		स_नकल(src, image->data, dsize);

	fb_pad_aligned_buffer(dst, d_pitch, src, s_pitch, image->height);
	image->data = dst;
	info->fbops->fb_imageblit(info, image);
	वापस 0;
पूर्ण
