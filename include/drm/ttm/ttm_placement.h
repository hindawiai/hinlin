<शैली गुरु>
/**************************************************************************
 *
 * Copyright (c) 2006-2009 VMware, Inc., Palo Alto, CA., USA
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/
/*
 * Authors: Thomas Hellstrom <thellstrom-at-vmware-करोt-com>
 */

#अगर_अघोषित _TTM_PLACEMENT_H_
#घोषणा _TTM_PLACEMENT_H_

#समावेश <linux/types.h>

/*
 * Memory regions क्रम data placement.
 */

#घोषणा TTM_PL_SYSTEM           0
#घोषणा TTM_PL_TT               1
#घोषणा TTM_PL_VRAM             2
#घोषणा TTM_PL_PRIV             3

/*
 * TTM_PL_FLAG_TOPDOWN requests to be placed from the
 * top of the memory area, instead of the bottom.
 */

#घोषणा TTM_PL_FLAG_CONTIGUOUS  (1 << 19)
#घोषणा TTM_PL_FLAG_TOPDOWN     (1 << 22)

/**
 * काष्ठा tपंचांग_place
 *
 * @fpfn:	first valid page frame number to put the object
 * @lpfn:	last valid page frame number to put the object
 * @flags:	memory करोमुख्य and caching flags क्रम the object
 *
 * Structure indicating a possible place to put an object.
 */
काष्ठा tपंचांग_place अणु
	अचिन्हित	fpfn;
	अचिन्हित	lpfn;
	uपूर्णांक32_t	mem_type;
	uपूर्णांक32_t	flags;
पूर्ण;

/**
 * काष्ठा tपंचांग_placement
 *
 * @num_placement:	number of preferred placements
 * @placement:		preferred placements
 * @num_busy_placement:	number of preferred placements when need to evict buffer
 * @busy_placement:	preferred placements when need to evict buffer
 *
 * Structure indicating the placement you request क्रम an object.
 */
काष्ठा tपंचांग_placement अणु
	अचिन्हित		num_placement;
	स्थिर काष्ठा tपंचांग_place	*placement;
	अचिन्हित		num_busy_placement;
	स्थिर काष्ठा tपंचांग_place	*busy_placement;
पूर्ण;

#पूर्ण_अगर
