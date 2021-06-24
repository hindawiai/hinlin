<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Samsung S5P G2D - 2D Graphics Accelerator Driver
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Kamil Debski, <k.debski@samsung.com>
 */

#समावेश <linux/पन.स>

#समावेश "g2d.h"
#समावेश "g2d-regs.h"

#घोषणा w(x, a)	ग_लिखोl((x), d->regs + (a))
#घोषणा r(a)	पढ़ोl(d->regs + (a))

/* g2d_reset clears all g2d रेजिस्टरs */
व्योम g2d_reset(काष्ठा g2d_dev *d)
अणु
	w(1, SOFT_RESET_REG);
पूर्ण

व्योम g2d_set_src_size(काष्ठा g2d_dev *d, काष्ठा g2d_frame *f)
अणु
	u32 n;

	w(0, SRC_SELECT_REG);
	w(f->stride & 0xFFFF, SRC_STRIDE_REG);

	n = f->o_height & 0xFFF;
	n <<= 16;
	n |= f->o_width & 0xFFF;
	w(n, SRC_LEFT_TOP_REG);

	n = f->bottom & 0xFFF;
	n <<= 16;
	n |= f->right & 0xFFF;
	w(n, SRC_RIGHT_BOTTOM_REG);

	w(f->fmt->hw, SRC_COLOR_MODE_REG);
पूर्ण

व्योम g2d_set_src_addr(काष्ठा g2d_dev *d, dma_addr_t a)
अणु
	w(a, SRC_BASE_ADDR_REG);
पूर्ण

व्योम g2d_set_dst_size(काष्ठा g2d_dev *d, काष्ठा g2d_frame *f)
अणु
	u32 n;

	w(0, DST_SELECT_REG);
	w(f->stride & 0xFFFF, DST_STRIDE_REG);

	n = f->o_height & 0xFFF;
	n <<= 16;
	n |= f->o_width & 0xFFF;
	w(n, DST_LEFT_TOP_REG);

	n = f->bottom & 0xFFF;
	n <<= 16;
	n |= f->right & 0xFFF;
	w(n, DST_RIGHT_BOTTOM_REG);

	w(f->fmt->hw, DST_COLOR_MODE_REG);
पूर्ण

व्योम g2d_set_dst_addr(काष्ठा g2d_dev *d, dma_addr_t a)
अणु
	w(a, DST_BASE_ADDR_REG);
पूर्ण

व्योम g2d_set_rop4(काष्ठा g2d_dev *d, u32 r)
अणु
	w(r, ROP4_REG);
पूर्ण

व्योम g2d_set_flip(काष्ठा g2d_dev *d, u32 r)
अणु
	w(r, SRC_MSK_सूचीECT_REG);
पूर्ण

व्योम g2d_set_v41_stretch(काष्ठा g2d_dev *d, काष्ठा g2d_frame *src,
					काष्ठा g2d_frame *dst)
अणु
	w(DEFAULT_SCALE_MODE, SRC_SCALE_CTRL_REG);

	/* inversed scaling factor: src is numerator */
	w((src->c_width << 16) / dst->c_width, SRC_XSCALE_REG);
	w((src->c_height << 16) / dst->c_height, SRC_YSCALE_REG);
पूर्ण

व्योम g2d_set_cmd(काष्ठा g2d_dev *d, u32 c)
अणु
	w(c, BITBLT_COMMAND_REG);
पूर्ण

व्योम g2d_start(काष्ठा g2d_dev *d)
अणु
	/* Clear cache */
	अगर (d->variant->hw_rev == TYPE_G2D_3X)
		w(0x7, CACHECTL_REG);

	/* Enable पूर्णांकerrupt */
	w(1, INTEN_REG);
	/* Start G2D engine */
	w(1, BITBLT_START_REG);
पूर्ण

व्योम g2d_clear_पूर्णांक(काष्ठा g2d_dev *d)
अणु
	w(1, INTC_PEND_REG);
पूर्ण
