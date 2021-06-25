<शैली गुरु>
/*
 *  linux/drivers/video/console/fbcon_rotate.c -- Software Rotation
 *
 *      Copyright (C) 2005 Antonino Daplas <adaplas @pol.net>
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License.  See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/console.h>
#समावेश <यंत्र/types.h>
#समावेश "fbcon.h"
#समावेश "fbcon_rotate.h"

अटल पूर्णांक fbcon_rotate_font(काष्ठा fb_info *info, काष्ठा vc_data *vc)
अणु
	काष्ठा fbcon_ops *ops = info->fbcon_par;
	पूर्णांक len, err = 0;
	पूर्णांक s_cellsize, d_cellsize, i;
	स्थिर u8 *src;
	u8 *dst;

	अगर (vc->vc_font.data == ops->fontdata &&
	    ops->p->con_rotate == ops->cur_rotate)
		जाओ finished;

	src = ops->fontdata = vc->vc_font.data;
	ops->cur_rotate = ops->p->con_rotate;
	len = vc->vc_font.अक्षरcount;
	s_cellsize = ((vc->vc_font.width + 7)/8) *
		vc->vc_font.height;
	d_cellsize = s_cellsize;

	अगर (ops->rotate == FB_ROTATE_CW ||
	    ops->rotate == FB_ROTATE_CCW)
		d_cellsize = ((vc->vc_font.height + 7)/8) *
			vc->vc_font.width;

	अगर (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	अगर (ops->fd_size < d_cellsize * len) अणु
		dst = kदो_स्मृति_array(len, d_cellsize, GFP_KERNEL);

		अगर (dst == शून्य) अणु
			err = -ENOMEM;
			जाओ finished;
		पूर्ण

		ops->fd_size = d_cellsize * len;
		kमुक्त(ops->fontbuffer);
		ops->fontbuffer = dst;
	पूर्ण

	dst = ops->fontbuffer;
	स_रखो(dst, 0, ops->fd_size);

	चयन (ops->rotate) अणु
	हाल FB_ROTATE_UD:
		क्रम (i = len; i--; ) अणु
			rotate_ud(src, dst, vc->vc_font.width,
				  vc->vc_font.height);

			src += s_cellsize;
			dst += d_cellsize;
		पूर्ण
		अवरोध;
	हाल FB_ROTATE_CW:
		क्रम (i = len; i--; ) अणु
			rotate_cw(src, dst, vc->vc_font.width,
				  vc->vc_font.height);
			src += s_cellsize;
			dst += d_cellsize;
		पूर्ण
		अवरोध;
	हाल FB_ROTATE_CCW:
		क्रम (i = len; i--; ) अणु
			rotate_ccw(src, dst, vc->vc_font.width,
				   vc->vc_font.height);
			src += s_cellsize;
			dst += d_cellsize;
		पूर्ण
		अवरोध;
	पूर्ण

finished:
	वापस err;
पूर्ण

व्योम fbcon_set_rotate(काष्ठा fbcon_ops *ops)
अणु
	ops->rotate_font = fbcon_rotate_font;

	चयन(ops->rotate) अणु
	हाल FB_ROTATE_CW:
		fbcon_rotate_cw(ops);
		अवरोध;
	हाल FB_ROTATE_UD:
		fbcon_rotate_ud(ops);
		अवरोध;
	हाल FB_ROTATE_CCW:
		fbcon_rotate_ccw(ops);
		अवरोध;
	पूर्ण
पूर्ण
