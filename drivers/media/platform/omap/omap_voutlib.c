<शैली गुरु>
/*
 * omap_voutlib.c
 *
 * Copyright (C) 2005-2010 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * Based on the OMAP2 camera driver
 * Video-क्रम-Linux (Version 2) camera capture driver क्रम
 * the OMAP24xx camera controller.
 *
 * Author: Andy Lowe (source@mvista.com)
 *
 * Copyright (C) 2004 MontaVista Software, Inc.
 * Copyright (C) 2010 Texas Instruments.
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>

#समावेश <linux/dma-mapping.h>

#समावेश <video/omapfb_dss.h>

#समावेश "omap_voutlib.h"

MODULE_AUTHOR("Texas Instruments");
MODULE_DESCRIPTION("OMAP Video library");
MODULE_LICENSE("GPL");

/* Return the शेष overlay cropping rectangle in crop given the image
 * size in pix and the video display size in fbuf.  The शेष
 * cropping rectangle is the largest rectangle no larger than the capture size
 * that will fit on the display.  The शेष cropping rectangle is centered in
 * the image.  All dimensions and offsets are rounded करोwn to even numbers.
 */
व्योम omap_vout_शेष_crop(काष्ठा v4l2_pix_क्रमmat *pix,
		  काष्ठा v4l2_framebuffer *fbuf, काष्ठा v4l2_rect *crop)
अणु
	crop->width = (pix->width < fbuf->fmt.width) ?
		pix->width : fbuf->fmt.width;
	crop->height = (pix->height < fbuf->fmt.height) ?
		pix->height : fbuf->fmt.height;
	crop->width &= ~1;
	crop->height &= ~1;
	crop->left = ((pix->width - crop->width) >> 1) & ~1;
	crop->top = ((pix->height - crop->height) >> 1) & ~1;
पूर्ण
EXPORT_SYMBOL_GPL(omap_vout_शेष_crop);

/* Given a new render winकरोw in new_win, adjust the winकरोw to the
 * nearest supported configuration.  The adjusted winकरोw parameters are
 * वापसed in new_win.
 * Returns zero अगर successful, or -EINVAL अगर the requested winकरोw is
 * impossible and cannot reasonably be adjusted.
 */
पूर्णांक omap_vout_try_winकरोw(काष्ठा v4l2_framebuffer *fbuf,
			काष्ठा v4l2_winकरोw *new_win)
अणु
	काष्ठा v4l2_rect try_win;

	/* make a working copy of the new_win rectangle */
	try_win = new_win->w;

	/* adjust the preview winकरोw so it fits on the display by clipping any
	 * offscreen areas
	 */
	अगर (try_win.left < 0) अणु
		try_win.width += try_win.left;
		try_win.left = 0;
	पूर्ण
	अगर (try_win.top < 0) अणु
		try_win.height += try_win.top;
		try_win.top = 0;
	पूर्ण
	try_win.width = (try_win.width < fbuf->fmt.width) ?
		try_win.width : fbuf->fmt.width;
	try_win.height = (try_win.height < fbuf->fmt.height) ?
		try_win.height : fbuf->fmt.height;
	अगर (try_win.left + try_win.width > fbuf->fmt.width)
		try_win.width = fbuf->fmt.width - try_win.left;
	अगर (try_win.top + try_win.height > fbuf->fmt.height)
		try_win.height = fbuf->fmt.height - try_win.top;
	try_win.width &= ~1;
	try_win.height &= ~1;

	अगर (try_win.width <= 0 || try_win.height <= 0)
		वापस -EINVAL;

	/* We now have a valid preview winकरोw, so go with it */
	new_win->w = try_win;
	new_win->field = V4L2_FIELD_NONE;
	new_win->clips = शून्य;
	new_win->clipcount = 0;
	new_win->biपंचांगap = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_vout_try_winकरोw);

/* Given a new render winकरोw in new_win, adjust the winकरोw to the
 * nearest supported configuration.  The image cropping winकरोw in crop
 * will also be adjusted अगर necessary.  Preference is given to keeping the
 * the winकरोw as बंद to the requested configuration as possible.  If
 * successful, new_win, vout->win, and crop are updated.
 * Returns zero अगर successful, or -EINVAL अगर the requested preview winकरोw is
 * impossible and cannot reasonably be adjusted.
 */
पूर्णांक omap_vout_new_winकरोw(काष्ठा v4l2_rect *crop,
		काष्ठा v4l2_winकरोw *win, काष्ठा v4l2_framebuffer *fbuf,
		काष्ठा v4l2_winकरोw *new_win)
अणु
	पूर्णांक err;

	err = omap_vout_try_winकरोw(fbuf, new_win);
	अगर (err)
		वापस err;

	/* update our preview winकरोw */
	win->w = new_win->w;
	win->field = new_win->field;
	win->chromakey = new_win->chromakey;

	/* Adjust the cropping winकरोw to allow क्रम resizing limitation */
	अगर (omap_vout_dss_omap24xx()) अणु
		/* For 24xx limit is 8x to 1/2x scaling. */
		अगर ((crop->height/win->w.height) >= 2)
			crop->height = win->w.height * 2;

		अगर ((crop->width/win->w.width) >= 2)
			crop->width = win->w.width * 2;

		अगर (crop->width > 768) अणु
			/* The OMAP2420 vertical resizing line buffer is 768
			 * pixels wide. If the cropped image is wider than
			 * 768 pixels then it cannot be vertically resized.
			 */
			अगर (crop->height != win->w.height)
				crop->width = 768;
		पूर्ण
	पूर्ण अन्यथा अगर (omap_vout_dss_omap34xx()) अणु
		/* For 34xx limit is 8x to 1/4x scaling. */
		अगर ((crop->height/win->w.height) >= 4)
			crop->height = win->w.height * 4;

		अगर ((crop->width/win->w.width) >= 4)
			crop->width = win->w.width * 4;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_vout_new_winकरोw);

/* Given a new cropping rectangle in new_crop, adjust the cropping rectangle to
 * the nearest supported configuration.  The image render winकरोw in win will
 * also be adjusted अगर necessary.  The preview winकरोw is adjusted such that the
 * horizontal and vertical rescaling ratios stay स्थिरant.  If the render
 * winकरोw would fall outside the display boundaries, the cropping rectangle
 * will also be adjusted to मुख्यtain the rescaling ratios.  If successful, crop
 * and win are updated.
 * Returns zero अगर successful, or -EINVAL अगर the requested cropping rectangle is
 * impossible and cannot reasonably be adjusted.
 */
पूर्णांक omap_vout_new_crop(काष्ठा v4l2_pix_क्रमmat *pix,
	      काष्ठा v4l2_rect *crop, काष्ठा v4l2_winकरोw *win,
	      काष्ठा v4l2_framebuffer *fbuf, स्थिर काष्ठा v4l2_rect *new_crop)
अणु
	काष्ठा v4l2_rect try_crop;
	अचिन्हित दीर्घ vresize, hresize;

	/* make a working copy of the new_crop rectangle */
	try_crop = *new_crop;

	/* adjust the cropping rectangle so it fits in the image */
	अगर (try_crop.left < 0) अणु
		try_crop.width += try_crop.left;
		try_crop.left = 0;
	पूर्ण
	अगर (try_crop.top < 0) अणु
		try_crop.height += try_crop.top;
		try_crop.top = 0;
	पूर्ण
	try_crop.width = (try_crop.width < pix->width) ?
		try_crop.width : pix->width;
	try_crop.height = (try_crop.height < pix->height) ?
		try_crop.height : pix->height;
	अगर (try_crop.left + try_crop.width > pix->width)
		try_crop.width = pix->width - try_crop.left;
	अगर (try_crop.top + try_crop.height > pix->height)
		try_crop.height = pix->height - try_crop.top;

	try_crop.width &= ~1;
	try_crop.height &= ~1;

	अगर (try_crop.width <= 0 || try_crop.height <= 0)
		वापस -EINVAL;

	अगर (omap_vout_dss_omap24xx()) अणु
		अगर (try_crop.height != win->w.height) अणु
			/* If we're resizing vertically, we can't support a
			 * crop width wider than 768 pixels.
			 */
			अगर (try_crop.width > 768)
				try_crop.width = 768;
		पूर्ण
	पूर्ण
	/* vertical resizing */
	vresize = (1024 * try_crop.height) / win->w.height;
	अगर (omap_vout_dss_omap24xx() && (vresize > 2048))
		vresize = 2048;
	अन्यथा अगर (omap_vout_dss_omap34xx() && (vresize > 4096))
		vresize = 4096;

	win->w.height = ((1024 * try_crop.height) / vresize) & ~1;
	अगर (win->w.height == 0)
		win->w.height = 2;
	अगर (win->w.height + win->w.top > fbuf->fmt.height) अणु
		/* We made the preview winकरोw extend below the bottom of the
		 * display, so clip it to the display boundary and resize the
		 * cropping height to मुख्यtain the vertical resizing ratio.
		 */
		win->w.height = (fbuf->fmt.height - win->w.top) & ~1;
		अगर (try_crop.height == 0)
			try_crop.height = 2;
	पूर्ण
	/* horizontal resizing */
	hresize = (1024 * try_crop.width) / win->w.width;
	अगर (omap_vout_dss_omap24xx() && (hresize > 2048))
		hresize = 2048;
	अन्यथा अगर (omap_vout_dss_omap34xx() && (hresize > 4096))
		hresize = 4096;

	win->w.width = ((1024 * try_crop.width) / hresize) & ~1;
	अगर (win->w.width == 0)
		win->w.width = 2;
	अगर (win->w.width + win->w.left > fbuf->fmt.width) अणु
		/* We made the preview winकरोw extend past the right side of the
		 * display, so clip it to the display boundary and resize the
		 * cropping width to मुख्यtain the horizontal resizing ratio.
		 */
		win->w.width = (fbuf->fmt.width - win->w.left) & ~1;
		अगर (try_crop.width == 0)
			try_crop.width = 2;
	पूर्ण
	अगर (omap_vout_dss_omap24xx()) अणु
		अगर ((try_crop.height/win->w.height) >= 2)
			try_crop.height = win->w.height * 2;

		अगर ((try_crop.width/win->w.width) >= 2)
			try_crop.width = win->w.width * 2;

		अगर (try_crop.width > 768) अणु
			/* The OMAP2420 vertical resizing line buffer is
			 * 768 pixels wide.  If the cropped image is wider
			 * than 768 pixels then it cannot be vertically resized.
			 */
			अगर (try_crop.height != win->w.height)
				try_crop.width = 768;
		पूर्ण
	पूर्ण अन्यथा अगर (omap_vout_dss_omap34xx()) अणु
		अगर ((try_crop.height/win->w.height) >= 4)
			try_crop.height = win->w.height * 4;

		अगर ((try_crop.width/win->w.width) >= 4)
			try_crop.width = win->w.width * 4;
	पूर्ण
	/* update our cropping rectangle and we're करोne */
	*crop = try_crop;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(omap_vout_new_crop);

/* Given a new क्रमmat in pix and fbuf,  crop and win
 * काष्ठाures are initialized to शेष values. crop
 * is initialized to the largest winकरोw size that will fit on the display.  The
 * crop winकरोw is centered in the image. win is initialized to
 * the same size as crop and is centered on the display.
 * All sizes and offsets are स्थिरrained to be even numbers.
 */
व्योम omap_vout_new_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix,
		काष्ठा v4l2_framebuffer *fbuf, काष्ठा v4l2_rect *crop,
		काष्ठा v4l2_winकरोw *win)
अणु
	/* crop defines the preview source winकरोw in the image capture
	 * buffer
	 */
	omap_vout_शेष_crop(pix, fbuf, crop);

	/* win defines the preview target winकरोw on the display */
	win->w.width = crop->width;
	win->w.height = crop->height;
	win->w.left = ((fbuf->fmt.width - win->w.width) >> 1) & ~1;
	win->w.top = ((fbuf->fmt.height - win->w.height) >> 1) & ~1;
पूर्ण
EXPORT_SYMBOL_GPL(omap_vout_new_क्रमmat);

/*
 * Allocate buffers
 */
अचिन्हित दीर्घ omap_vout_alloc_buffer(u32 buf_size, u32 *phys_addr)
अणु
	u32 order, size;
	अचिन्हित दीर्घ virt_addr, addr;

	size = PAGE_ALIGN(buf_size);
	order = get_order(size);
	virt_addr = __get_मुक्त_pages(GFP_KERNEL, order);
	addr = virt_addr;

	अगर (virt_addr) अणु
		जबतक (size > 0) अणु
			SetPageReserved(virt_to_page(addr));
			addr += PAGE_SIZE;
			size -= PAGE_SIZE;
		पूर्ण
	पूर्ण
	*phys_addr = (u32) virt_to_phys((व्योम *) virt_addr);
	वापस virt_addr;
पूर्ण

/*
 * Free buffers
 */
व्योम omap_vout_मुक्त_buffer(अचिन्हित दीर्घ virtaddr, u32 buf_size)
अणु
	u32 order, size;
	अचिन्हित दीर्घ addr = virtaddr;

	size = PAGE_ALIGN(buf_size);
	order = get_order(size);

	जबतक (size > 0) अणु
		ClearPageReserved(virt_to_page(addr));
		addr += PAGE_SIZE;
		size -= PAGE_SIZE;
	पूर्ण
	मुक्त_pages((अचिन्हित दीर्घ) virtaddr, order);
पूर्ण

bool omap_vout_dss_omap24xx(व्योम)
अणु
	वापस omapdss_get_version() == OMAPDSS_VER_OMAP24xx;
पूर्ण

bool omap_vout_dss_omap34xx(व्योम)
अणु
	चयन (omapdss_get_version()) अणु
	हाल OMAPDSS_VER_OMAP34xx_ES1:
	हाल OMAPDSS_VER_OMAP34xx_ES3:
	हाल OMAPDSS_VER_OMAP3630:
	हाल OMAPDSS_VER_AM35xx:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण
