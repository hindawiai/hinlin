<शैली गुरु>
/*
 * Copyright (C) 2010 Francisco Jerez.
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश <subdev/fb/regsnv04.h>

#घोषणा NV04_PFB_DEBUG_0					0x00100080
#	define NV04_PFB_DEBUG_0_PAGE_MODE			0x00000001
#	define NV04_PFB_DEBUG_0_REFRESH_OFF			0x00000010
#	define NV04_PFB_DEBUG_0_REFRESH_COUNTX64		0x00003f00
#	define NV04_PFB_DEBUG_0_REFRESH_SLOW_CLK		0x00004000
#	define NV04_PFB_DEBUG_0_SAFE_MODE			0x00008000
#	define NV04_PFB_DEBUG_0_ALOM_ENABLE			0x00010000
#	define NV04_PFB_DEBUG_0_CASOE				0x00100000
#	define NV04_PFB_DEBUG_0_CKE_INVERT			0x10000000
#	define NV04_PFB_DEBUG_0_REFINC				0x20000000
#	define NV04_PFB_DEBUG_0_SAVE_POWER_OFF			0x40000000
#घोषणा NV04_PFB_CFG0						0x00100200
#	define NV04_PFB_CFG0_SCRAMBLE				0x20000000
#घोषणा NV04_PFB_CFG1						0x00100204
#घोषणा NV04_PFB_SCRAMBLE(i)                         (0x00100400 + 4 * (i))

#घोषणा NV10_PFB_REFCTRL					0x00100210
#	define NV10_PFB_REFCTRL_VALID_1				(1 << 31)

अटल अंतरभूत काष्ठा io_mapping *
fbmem_init(काष्ठा nvkm_device *dev)
अणु
	वापस io_mapping_create_wc(dev->func->resource_addr(dev, 1),
				    dev->func->resource_size(dev, 1));
पूर्ण

अटल अंतरभूत व्योम
fbmem_fini(काष्ठा io_mapping *fb)
अणु
	io_mapping_मुक्त(fb);
पूर्ण

अटल अंतरभूत u32
fbmem_peek(काष्ठा io_mapping *fb, u32 off)
अणु
	u8 __iomem *p = io_mapping_map_atomic_wc(fb, off & PAGE_MASK);
	u32 val = ioपढ़ो32(p + (off & ~PAGE_MASK));
	io_mapping_unmap_atomic(p);
	वापस val;
पूर्ण

अटल अंतरभूत व्योम
fbmem_poke(काष्ठा io_mapping *fb, u32 off, u32 val)
अणु
	u8 __iomem *p = io_mapping_map_atomic_wc(fb, off & PAGE_MASK);
	ioग_लिखो32(val, p + (off & ~PAGE_MASK));
	wmb();
	io_mapping_unmap_atomic(p);
पूर्ण

अटल अंतरभूत bool
fbmem_पढ़ोback(काष्ठा io_mapping *fb, u32 off, u32 val)
अणु
	fbmem_poke(fb, off, val);
	वापस val == fbmem_peek(fb, off);
पूर्ण
