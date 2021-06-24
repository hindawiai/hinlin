<शैली गुरु>
/*
 * omap_voutlib.h
 *
 * Copyright (C) 2010 Texas Instruments.
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 */

#अगर_अघोषित OMAP_VOUTLIB_H
#घोषणा OMAP_VOUTLIB_H

व्योम omap_vout_शेष_crop(काष्ठा v4l2_pix_क्रमmat *pix,
		काष्ठा v4l2_framebuffer *fbuf, काष्ठा v4l2_rect *crop);

पूर्णांक omap_vout_new_crop(काष्ठा v4l2_pix_क्रमmat *pix,
		काष्ठा v4l2_rect *crop, काष्ठा v4l2_winकरोw *win,
		काष्ठा v4l2_framebuffer *fbuf,
		स्थिर काष्ठा v4l2_rect *new_crop);

पूर्णांक omap_vout_try_winकरोw(काष्ठा v4l2_framebuffer *fbuf,
		काष्ठा v4l2_winकरोw *new_win);

पूर्णांक omap_vout_new_winकरोw(काष्ठा v4l2_rect *crop,
		काष्ठा v4l2_winकरोw *win, काष्ठा v4l2_framebuffer *fbuf,
		काष्ठा v4l2_winकरोw *new_win);

व्योम omap_vout_new_क्रमmat(काष्ठा v4l2_pix_क्रमmat *pix,
		काष्ठा v4l2_framebuffer *fbuf, काष्ठा v4l2_rect *crop,
		काष्ठा v4l2_winकरोw *win);
अचिन्हित दीर्घ omap_vout_alloc_buffer(u32 buf_size, u32 *phys_addr);
व्योम omap_vout_मुक्त_buffer(अचिन्हित दीर्घ virtaddr, u32 buf_size);

bool omap_vout_dss_omap24xx(व्योम);
bool omap_vout_dss_omap34xx(व्योम);
#पूर्ण_अगर	/* #अगर_अघोषित OMAP_VOUTLIB_H */

