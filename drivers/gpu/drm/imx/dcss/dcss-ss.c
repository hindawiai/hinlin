<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright 2019 NXP.
 */

#समावेश <linux/device.h>
#समावेश <linux/slab.h>

#समावेश "dcss-dev.h"

#घोषणा DCSS_SS_SYS_CTRL			0x00
#घोषणा   RUN_EN				BIT(0)
#घोषणा DCSS_SS_DISPLAY				0x10
#घोषणा   LRC_X_POS				0
#घोषणा   LRC_X_MASK				GENMASK(12, 0)
#घोषणा   LRC_Y_POS				16
#घोषणा   LRC_Y_MASK				GENMASK(28, 16)
#घोषणा DCSS_SS_HSYNC				0x20
#घोषणा DCSS_SS_VSYNC				0x30
#घोषणा   SYNC_START_POS			0
#घोषणा   SYNC_START_MASK			GENMASK(12, 0)
#घोषणा   SYNC_END_POS				16
#घोषणा   SYNC_END_MASK				GENMASK(28, 16)
#घोषणा   SYNC_POL				BIT(31)
#घोषणा DCSS_SS_DE_ULC				0x40
#घोषणा   ULC_X_POS				0
#घोषणा   ULC_X_MASK				GENMASK(12, 0)
#घोषणा   ULC_Y_POS				16
#घोषणा   ULC_Y_MASK				GENMASK(28, 16)
#घोषणा   ULC_POL				BIT(31)
#घोषणा DCSS_SS_DE_LRC				0x50
#घोषणा DCSS_SS_MODE				0x60
#घोषणा   PIPE_MODE_POS				0
#घोषणा   PIPE_MODE_MASK			GENMASK(1, 0)
#घोषणा DCSS_SS_COEFF				0x70
#घोषणा   HORIZ_A_POS				0
#घोषणा   HORIZ_A_MASK				GENMASK(3, 0)
#घोषणा   HORIZ_B_POS				4
#घोषणा   HORIZ_B_MASK				GENMASK(7, 4)
#घोषणा   HORIZ_C_POS				8
#घोषणा   HORIZ_C_MASK				GENMASK(11, 8)
#घोषणा   HORIZ_H_NORM_POS			12
#घोषणा   HORIZ_H_NORM_MASK			GENMASK(14, 12)
#घोषणा   VERT_A_POS				16
#घोषणा   VERT_A_MASK				GENMASK(19, 16)
#घोषणा   VERT_B_POS				20
#घोषणा   VERT_B_MASK				GENMASK(23, 20)
#घोषणा   VERT_C_POS				24
#घोषणा   VERT_C_MASK				GENMASK(27, 24)
#घोषणा   VERT_H_NORM_POS			28
#घोषणा   VERT_H_NORM_MASK			GENMASK(30, 28)
#घोषणा DCSS_SS_CLIP_CB				0x80
#घोषणा DCSS_SS_CLIP_CR				0x90
#घोषणा   CLIP_MIN_POS				0
#घोषणा   CLIP_MIN_MASK				GENMASK(9, 0)
#घोषणा   CLIP_MAX_POS				0
#घोषणा   CLIP_MAX_MASK				GENMASK(23, 16)
#घोषणा DCSS_SS_INTER_MODE			0xA0
#घोषणा   INT_EN				BIT(0)
#घोषणा   VSYNC_SHIFT				BIT(1)

काष्ठा dcss_ss अणु
	काष्ठा device *dev;
	व्योम __iomem *base_reg;
	u32 base_ofs;

	काष्ठा dcss_ctxld *ctxld;
	u32 ctx_id;

	bool in_use;
पूर्ण;

अटल व्योम dcss_ss_ग_लिखो(काष्ठा dcss_ss *ss, u32 val, u32 ofs)
अणु
	अगर (!ss->in_use)
		dcss_ग_लिखोl(val, ss->base_reg + ofs);

	dcss_ctxld_ग_लिखो(ss->ctxld, ss->ctx_id, val,
			 ss->base_ofs + ofs);
पूर्ण

पूर्णांक dcss_ss_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ ss_base)
अणु
	काष्ठा dcss_ss *ss;

	ss = kzalloc(माप(*ss), GFP_KERNEL);
	अगर (!ss)
		वापस -ENOMEM;

	dcss->ss = ss;
	ss->dev = dcss->dev;
	ss->ctxld = dcss->ctxld;

	ss->base_reg = ioremap(ss_base, SZ_4K);
	अगर (!ss->base_reg) अणु
		dev_err(dcss->dev, "ss: unable to remap ss base\n");
		kमुक्त(ss);
		वापस -ENOMEM;
	पूर्ण

	ss->base_ofs = ss_base;
	ss->ctx_id = CTX_SB_HP;

	वापस 0;
पूर्ण

व्योम dcss_ss_निकास(काष्ठा dcss_ss *ss)
अणु
	/* stop SS */
	dcss_ग_लिखोl(0, ss->base_reg + DCSS_SS_SYS_CTRL);

	अगर (ss->base_reg)
		iounmap(ss->base_reg);

	kमुक्त(ss);
पूर्ण

व्योम dcss_ss_subsam_set(काष्ठा dcss_ss *ss)
अणु
	dcss_ss_ग_लिखो(ss, 0x41614161, DCSS_SS_COEFF);
	dcss_ss_ग_लिखो(ss, 0, DCSS_SS_MODE);
	dcss_ss_ग_लिखो(ss, 0x03ff0000, DCSS_SS_CLIP_CB);
	dcss_ss_ग_लिखो(ss, 0x03ff0000, DCSS_SS_CLIP_CR);
पूर्ण

व्योम dcss_ss_sync_set(काष्ठा dcss_ss *ss, काष्ठा videomode *vm,
		      bool phsync, bool pvsync)
अणु
	u16 lrc_x, lrc_y;
	u16 hsync_start, hsync_end;
	u16 vsync_start, vsync_end;
	u16 de_ulc_x, de_ulc_y;
	u16 de_lrc_x, de_lrc_y;

	lrc_x = vm->hfront_porch + vm->hback_porch + vm->hsync_len +
		vm->hactive - 1;
	lrc_y = vm->vfront_porch + vm->vback_porch + vm->vsync_len +
		vm->vactive - 1;

	dcss_ss_ग_लिखो(ss, (lrc_y << LRC_Y_POS) | lrc_x, DCSS_SS_DISPLAY);

	hsync_start = vm->hfront_porch + vm->hback_porch + vm->hsync_len +
		      vm->hactive - 1;
	hsync_end = vm->hsync_len - 1;

	dcss_ss_ग_लिखो(ss, (phsync ? SYNC_POL : 0) |
		      ((u32)hsync_end << SYNC_END_POS) | hsync_start,
		      DCSS_SS_HSYNC);

	vsync_start = vm->vfront_porch - 1;
	vsync_end = vm->vfront_porch + vm->vsync_len - 1;

	dcss_ss_ग_लिखो(ss, (pvsync ? SYNC_POL : 0) |
		      ((u32)vsync_end << SYNC_END_POS) | vsync_start,
		      DCSS_SS_VSYNC);

	de_ulc_x = vm->hsync_len + vm->hback_porch - 1;
	de_ulc_y = vm->vsync_len + vm->vfront_porch + vm->vback_porch;

	dcss_ss_ग_लिखो(ss, SYNC_POL | ((u32)de_ulc_y << ULC_Y_POS) | de_ulc_x,
		      DCSS_SS_DE_ULC);

	de_lrc_x = vm->hsync_len + vm->hback_porch + vm->hactive - 1;
	de_lrc_y = vm->vsync_len + vm->vfront_porch + vm->vback_porch +
		   vm->vactive - 1;

	dcss_ss_ग_लिखो(ss, (de_lrc_y << LRC_Y_POS) | de_lrc_x, DCSS_SS_DE_LRC);
पूर्ण

व्योम dcss_ss_enable(काष्ठा dcss_ss *ss)
अणु
	dcss_ss_ग_लिखो(ss, RUN_EN, DCSS_SS_SYS_CTRL);
	ss->in_use = true;
पूर्ण

व्योम dcss_ss_shutoff(काष्ठा dcss_ss *ss)
अणु
	dcss_ग_लिखोl(0, ss->base_reg + DCSS_SS_SYS_CTRL);
	ss->in_use = false;
पूर्ण
