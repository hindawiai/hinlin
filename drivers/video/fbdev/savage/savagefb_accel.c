<शैली गुरु>
/*-*- linux-c -*-
 *  linux/drivers/video/savage/savage_accel.c -- Hardware Acceleration
 *
 *      Copyright (C) 2004 Antonino Daplas<adaplas@pol.net>
 *      All Rights Reserved
 *
 *  This file is subject to the terms and conditions of the GNU General Public
 *  License. See the file COPYING in the मुख्य directory of this archive क्रम
 *  more details.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/fb.h>
#समावेश <linux/module.h>

#समावेश "savagefb.h"

अटल u32 savagefb_rop[] = अणु
	0xCC, /* ROP_COPY */
	0x5A  /* ROP_XOR  */
पूर्ण;

पूर्णांक savagefb_sync(काष्ठा fb_info *info)
अणु
	काष्ठा savagefb_par *par = info->par;

	par->SavageWaitIdle(par);
	वापस 0;
पूर्ण

व्योम savagefb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक sx = region->sx, dx = region->dx;
	पूर्णांक sy = region->sy, dy = region->dy;
	पूर्णांक cmd;

	अगर (!region->width || !region->height)
		वापस;
	par->bci_ptr = 0;
	cmd = BCI_CMD_RECT | BCI_CMD_DEST_GBD | BCI_CMD_SRC_GBD;
	BCI_CMD_SET_ROP(cmd, savagefb_rop[0]);

	अगर (dx <= sx) अणु
		cmd |= BCI_CMD_RECT_XP;
	पूर्ण अन्यथा अणु
		sx += region->width - 1;
		dx += region->width - 1;
	पूर्ण

	अगर (dy <= sy) अणु
		cmd |= BCI_CMD_RECT_YP;
	पूर्ण अन्यथा अणु
		sy += region->height - 1;
		dy += region->height - 1;
	पूर्ण

	par->SavageWaitFअगरo(par,4);
	BCI_SEND(cmd);
	BCI_SEND(BCI_X_Y(sx, sy));
	BCI_SEND(BCI_X_Y(dx, dy));
	BCI_SEND(BCI_W_H(region->width, region->height));
पूर्ण

व्योम savagefb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक cmd, color;

	अगर (!rect->width || !rect->height)
		वापस;

	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR)
		color = rect->color;
	अन्यथा
		color = ((u32 *)info->pseuकरो_palette)[rect->color];

	cmd = BCI_CMD_RECT | BCI_CMD_RECT_XP | BCI_CMD_RECT_YP |
	      BCI_CMD_DEST_GBD | BCI_CMD_SRC_SOLID |
	      BCI_CMD_SEND_COLOR;

	par->bci_ptr = 0;
	BCI_CMD_SET_ROP(cmd, savagefb_rop[rect->rop]);

	par->SavageWaitFअगरo(par,4);
	BCI_SEND(cmd);
	BCI_SEND(color);
	BCI_SEND( BCI_X_Y(rect->dx, rect->dy) );
	BCI_SEND( BCI_W_H(rect->width, rect->height) );
पूर्ण

व्योम savagefb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image)
अणु
	काष्ठा savagefb_par *par = info->par;
	पूर्णांक fg, bg, size, i, width;
	पूर्णांक cmd;
	u32 *src = (u32 *) image->data;

	अगर (!image->width || !image->height)
		वापस;

	अगर (image->depth != 1) अणु
		cfb_imageblit(info, image);
		वापस;
	पूर्ण

	अगर (info->fix.visual == FB_VISUAL_PSEUDOCOLOR) अणु
		fg = image->fg_color;
		bg = image->bg_color;
	पूर्ण अन्यथा अणु
		fg = ((u32 *)info->pseuकरो_palette)[image->fg_color];
		bg = ((u32 *)info->pseuकरो_palette)[image->bg_color];
	पूर्ण

	cmd = BCI_CMD_RECT | BCI_CMD_RECT_XP | BCI_CMD_RECT_YP |
	      BCI_CMD_CLIP_LR | BCI_CMD_DEST_GBD | BCI_CMD_SRC_MONO |
	      BCI_CMD_SEND_COLOR;

	par->bci_ptr = 0;
	BCI_CMD_SET_ROP(cmd, savagefb_rop[0]);

	width = (image->width + 31) & ~31;
	size = (width * image->height)/8;
	size >>= 2;

	par->SavageWaitFअगरo(par, size + 5);
	BCI_SEND(cmd);
	BCI_SEND(BCI_CLIP_LR(image->dx, image->dx + image->width - 1));
	BCI_SEND(fg);
	BCI_SEND(bg);
	BCI_SEND(BCI_X_Y(image->dx, image->dy));
	BCI_SEND(BCI_W_H(width, image->height));
	क्रम (i = 0; i < size; i++)
		BCI_SEND(src[i]);
पूर्ण

MODULE_LICENSE("GPL");
