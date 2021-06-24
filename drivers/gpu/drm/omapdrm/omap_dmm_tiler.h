<शैली गुरु>
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob@ti.com>
 *         Andy Gross <andy.gross@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#अगर_अघोषित OMAP_DMM_TILER_H
#घोषणा OMAP_DMM_TILER_H

#समावेश "omap_drv.h"
#समावेश "tcm.h"

क्रमागत tiler_fmt अणु
	TILFMT_8BIT = 0,
	TILFMT_16BIT,
	TILFMT_32BIT,
	TILFMT_PAGE,
	TILFMT_NFORMATS
पूर्ण;

काष्ठा pat_area अणु
	u32 x0:8;
	u32 y0:8;
	u32 x1:8;
	u32 y1:8;
पूर्ण;

काष्ठा tiler_block अणु
	काष्ठा list_head alloc_node;	/* node क्रम global block list */
	काष्ठा tcm_area area;		/* area */
	क्रमागत tiler_fmt fmt;		/* क्रमmat */
पूर्ण;

/* bits representing the same slot in DMM-TILER hw-block */
#घोषणा SLOT_WIDTH_BITS         6
#घोषणा SLOT_HEIGHT_BITS        6

/* bits reserved to describe coordinates in DMM-TILER hw-block */
#घोषणा CONT_WIDTH_BITS         14
#घोषणा CONT_HEIGHT_BITS        13

/* calculated स्थिरants */
#घोषणा TILER_PAGE              (1 << (SLOT_WIDTH_BITS + SLOT_HEIGHT_BITS))
#घोषणा TILER_WIDTH             (1 << (CONT_WIDTH_BITS - SLOT_WIDTH_BITS))
#घोषणा TILER_HEIGHT            (1 << (CONT_HEIGHT_BITS - SLOT_HEIGHT_BITS))

/*
Table 15-11. Coding and Description of TILER Orientations
S Y X	Description				Alternate description
0 0 0	0-degree view				Natural view
0 0 1	0-degree view with vertical mirror 	180-degree view with horizontal mirror
0 1 0	0-degree view with horizontal mirror 	180-degree view with vertical mirror
0 1 1	180-degree view
1 0 0	90-degree view with vertical mirror	270-degree view with horizontal mirror
1 0 1	270-degree view
1 1 0	90-degree view
1 1 1	90-degree view with horizontal mirror	270-degree view with vertical mirror
 */
#घोषणा MASK_XY_FLIP		(1 << 31)
#घोषणा MASK_Y_INVERT		(1 << 30)
#घोषणा MASK_X_INVERT		(1 << 29)
#घोषणा SHIFT_ACC_MODE		27
#घोषणा MASK_ACC_MODE		3

#घोषणा MASK(bits) ((1 << (bits)) - 1)

#घोषणा TILVIEW_8BIT    0x60000000u
#घोषणा TILVIEW_16BIT   (TILVIEW_8BIT  + VIEW_SIZE)
#घोषणा TILVIEW_32BIT   (TILVIEW_16BIT + VIEW_SIZE)
#घोषणा TILVIEW_PAGE    (TILVIEW_32BIT + VIEW_SIZE)
#घोषणा TILVIEW_END     (TILVIEW_PAGE  + VIEW_SIZE)

/* create tsptr by adding view orientation and access mode */
#घोषणा TIL_ADDR(x, orient, a)\
	((u32) (x) | (orient) | ((a) << SHIFT_ACC_MODE))

#अगर_घोषित CONFIG_DEBUG_FS
पूर्णांक tiler_map_show(काष्ठा seq_file *s, व्योम *arg);
#पूर्ण_अगर

/* pin/unpin */
पूर्णांक tiler_pin(काष्ठा tiler_block *block, काष्ठा page **pages,
		u32 npages, u32 roll, bool रुको);
पूर्णांक tiler_unpin(काष्ठा tiler_block *block);

/* reserve/release */
काष्ठा tiler_block *tiler_reserve_2d(क्रमागत tiler_fmt fmt, u16 w, u16 h,
				u16 align);
काष्ठा tiler_block *tiler_reserve_1d(माप_प्रकार size);
पूर्णांक tiler_release(काष्ठा tiler_block *block);

/* utilities */
dma_addr_t tiler_ssptr(काष्ठा tiler_block *block);
dma_addr_t tiler_tsptr(काष्ठा tiler_block *block, u32 orient,
		u32 x, u32 y);
u32 tiler_stride(क्रमागत tiler_fmt fmt, u32 orient);
माप_प्रकार tiler_size(क्रमागत tiler_fmt fmt, u16 w, u16 h);
माप_प्रकार tiler_vsize(क्रमागत tiler_fmt fmt, u16 w, u16 h);
व्योम tiler_align(क्रमागत tiler_fmt fmt, u16 *w, u16 *h);
u32 tiler_get_cpu_cache_flags(व्योम);
bool dmm_is_available(व्योम);

बाह्य काष्ठा platक्रमm_driver omap_dmm_driver;

/* GEM bo flags -> tiler fmt */
अटल अंतरभूत क्रमागत tiler_fmt gem2fmt(u32 flags)
अणु
	चयन (flags & OMAP_BO_TILED_MASK) अणु
	हाल OMAP_BO_TILED_8:
		वापस TILFMT_8BIT;
	हाल OMAP_BO_TILED_16:
		वापस TILFMT_16BIT;
	हाल OMAP_BO_TILED_32:
		वापस TILFMT_32BIT;
	शेष:
		वापस TILFMT_PAGE;
	पूर्ण
पूर्ण

अटल अंतरभूत bool validfmt(क्रमागत tiler_fmt fmt)
अणु
	चयन (fmt) अणु
	हाल TILFMT_8BIT:
	हाल TILFMT_16BIT:
	हाल TILFMT_32BIT:
	हाल TILFMT_PAGE:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#पूर्ण_अगर
