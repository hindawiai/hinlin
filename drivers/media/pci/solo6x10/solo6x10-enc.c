<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2010-2013 Bluecherry, LLC <https://www.bluecherrydvr.com>
 *
 * Original author:
 * Ben Collins <bcollins@ubuntu.com>
 *
 * Additional work by:
 * John Brooks <john.brooks@bluecherry.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/font.h>
#समावेश <linux/bitrev.h>
#समावेश <linux/slab.h>

#समावेश "solo6x10.h"

#घोषणा VI_PROG_HSIZE			(1280 - 16)
#घोषणा VI_PROG_VSIZE			(1024 - 16)

#घोषणा IRQ_LEVEL			2

अटल व्योम solo_capture_config(काष्ठा solo_dev *solo_dev)
अणु
	अचिन्हित दीर्घ height;
	अचिन्हित दीर्घ width;
	व्योम *buf;
	पूर्णांक i;

	solo_reg_ग_लिखो(solo_dev, SOLO_CAP_BASE,
		       SOLO_CAP_MAX_PAGE((SOLO_CAP_EXT_SIZE(solo_dev)
					  - SOLO_CAP_PAGE_SIZE) >> 16)
		       | SOLO_CAP_BASE_ADDR(SOLO_CAP_EXT_ADDR(solo_dev) >> 16));

	/* XXX: Unकरोcumented bits at b17 and b24 */
	अगर (solo_dev->type == SOLO_DEV_6110) अणु
		/* NOTE: Ref driver has (62 << 24) here as well, but it causes
		 * wacked out frame timing on 4-port 6110. */
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_BTW,
			       (1 << 17) | SOLO_CAP_PROG_BANDWIDTH(2) |
			       SOLO_CAP_MAX_BANDWIDTH(36));
	पूर्ण अन्यथा अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_BTW,
			       (1 << 17) | SOLO_CAP_PROG_BANDWIDTH(2) |
			       SOLO_CAP_MAX_BANDWIDTH(32));
	पूर्ण

	/* Set scale 1, 9 dimension */
	width = solo_dev->video_hsize;
	height = solo_dev->video_vsize;
	solo_reg_ग_लिखो(solo_dev, SOLO_DIM_SCALE1,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 2, 10 dimension */
	width = solo_dev->video_hsize / 2;
	height = solo_dev->video_vsize;
	solo_reg_ग_लिखो(solo_dev, SOLO_DIM_SCALE2,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 3, 11 dimension */
	width = solo_dev->video_hsize / 2;
	height = solo_dev->video_vsize / 2;
	solo_reg_ग_लिखो(solo_dev, SOLO_DIM_SCALE3,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 4, 12 dimension */
	width = solo_dev->video_hsize / 3;
	height = solo_dev->video_vsize / 3;
	solo_reg_ग_लिखो(solo_dev, SOLO_DIM_SCALE4,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Set scale 5, 13 dimension */
	width = solo_dev->video_hsize / 4;
	height = solo_dev->video_vsize / 2;
	solo_reg_ग_लिखो(solo_dev, SOLO_DIM_SCALE5,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 8) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Progressive */
	width = VI_PROG_HSIZE;
	height = VI_PROG_VSIZE;
	solo_reg_ग_लिखो(solo_dev, SOLO_DIM_PROG,
		       SOLO_DIM_H_MB_NUM(width / 16) |
		       SOLO_DIM_V_MB_NUM_FRAME(height / 16) |
		       SOLO_DIM_V_MB_NUM_FIELD(height / 16));

	/* Clear OSD */
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_OSD_CH, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_OSD_BASE, SOLO_EOSD_EXT_ADDR >> 16);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_OSD_CLR,
		       0xF0 << 16 | 0x80 << 8 | 0x80);

	अगर (solo_dev->type == SOLO_DEV_6010)
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_OSD_OPT,
			       SOLO_VE_OSD_H_SHADOW | SOLO_VE_OSD_V_SHADOW);
	अन्यथा
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_OSD_OPT, SOLO_VE_OSD_V_DOUBLE
			       | SOLO_VE_OSD_H_SHADOW | SOLO_VE_OSD_V_SHADOW);

	/* Clear OSG buffer */
	buf = kzalloc(SOLO_EOSD_EXT_SIZE(solo_dev), GFP_KERNEL);
	अगर (!buf)
		वापस;

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_p2m_dma(solo_dev, 1, buf,
			     SOLO_EOSD_EXT_ADDR +
			     (SOLO_EOSD_EXT_SIZE(solo_dev) * i),
			     SOLO_EOSD_EXT_SIZE(solo_dev), 0, 0);
	पूर्ण
	kमुक्त(buf);
पूर्ण

#घोषणा SOLO_OSD_WRITE_SIZE (16 * OSD_TEXT_MAX)

/* Should be called with enable_lock held */
पूर्णांक solo_osd_prपूर्णांक(काष्ठा solo_enc_dev *solo_enc)
अणु
	काष्ठा solo_dev *solo_dev = solo_enc->solo_dev;
	u8 *str = solo_enc->osd_text;
	u8 *buf = solo_enc->osd_buf;
	u32 reg;
	स्थिर काष्ठा font_desc *vga = find_font("VGA8x16");
	स्थिर u8 *vga_data;
	पूर्णांक i, j;

	अगर (WARN_ON_ONCE(!vga))
		वापस -ENODEV;

	reg = solo_reg_पढ़ो(solo_dev, SOLO_VE_OSD_CH);
	अगर (!*str) अणु
		/* Disable OSD on this channel */
		reg &= ~(1 << solo_enc->ch);
		जाओ out;
	पूर्ण

	स_रखो(buf, 0, SOLO_OSD_WRITE_SIZE);
	vga_data = (स्थिर u8 *)vga->data;

	क्रम (i = 0; *str; i++, str++) अणु
		क्रम (j = 0; j < 16; j++) अणु
			buf[(j << 1) | (i & 1) | ((i & ~1) << 4)] =
			    bitrev8(vga_data[(*str << 4) | j]);
		पूर्ण
	पूर्ण

	solo_p2m_dma(solo_dev, 1, buf,
		     SOLO_EOSD_EXT_ADDR_CHAN(solo_dev, solo_enc->ch),
		     SOLO_OSD_WRITE_SIZE, 0, 0);

	/* Enable OSD on this channel */
	reg |= (1 << solo_enc->ch);

out:
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_OSD_CH, reg);
	वापस 0;
पूर्ण

/*
 * Set channel Quality Profile (0-3).
 */
व्योम solo_s_jpeg_qp(काष्ठा solo_dev *solo_dev, अचिन्हित पूर्णांक ch,
		    अचिन्हित पूर्णांक qp)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक idx, reg;

	अगर ((ch > 31) || (qp > 3))
		वापस;

	अगर (solo_dev->type == SOLO_DEV_6010)
		वापस;

	अगर (ch < 16) अणु
		idx = 0;
		reg = SOLO_VE_JPEG_QP_CH_L;
	पूर्ण अन्यथा अणु
		ch -= 16;
		idx = 1;
		reg = SOLO_VE_JPEG_QP_CH_H;
	पूर्ण
	ch *= 2;

	spin_lock_irqsave(&solo_dev->jpeg_qp_lock, flags);

	solo_dev->jpeg_qp[idx] &= ~(3 << ch);
	solo_dev->jpeg_qp[idx] |= (qp & 3) << ch;

	solo_reg_ग_लिखो(solo_dev, reg, solo_dev->jpeg_qp[idx]);

	spin_unlock_irqrestore(&solo_dev->jpeg_qp_lock, flags);
पूर्ण

पूर्णांक solo_g_jpeg_qp(काष्ठा solo_dev *solo_dev, अचिन्हित पूर्णांक ch)
अणु
	पूर्णांक idx;

	अगर (solo_dev->type == SOLO_DEV_6010)
		वापस 2;

	अगर (WARN_ON_ONCE(ch > 31))
		वापस 2;

	अगर (ch < 16) अणु
		idx = 0;
	पूर्ण अन्यथा अणु
		ch -= 16;
		idx = 1;
	पूर्ण
	ch *= 2;

	वापस (solo_dev->jpeg_qp[idx] >> ch) & 3;
पूर्ण

#घोषणा SOLO_QP_INIT 0xaaaaaaaa

अटल व्योम solo_jpeg_config(काष्ठा solo_dev *solo_dev)
अणु
	अगर (solo_dev->type == SOLO_DEV_6010) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_QP_TBL,
			       (2 << 24) | (2 << 16) | (2 << 8) | 2);
	पूर्ण अन्यथा अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_QP_TBL,
			       (4 << 24) | (3 << 16) | (2 << 8) | 1);
	पूर्ण

	spin_lock_init(&solo_dev->jpeg_qp_lock);

	/* Initialize Quality Profile क्रम all channels */
	solo_dev->jpeg_qp[0] = solo_dev->jpeg_qp[1] = SOLO_QP_INIT;
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_QP_CH_L, SOLO_QP_INIT);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_QP_CH_H, SOLO_QP_INIT);

	solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_CFG,
		(SOLO_JPEG_EXT_SIZE(solo_dev) & 0xffff0000) |
		((SOLO_JPEG_EXT_ADDR(solo_dev) >> 16) & 0x0000ffff));
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_CTRL, 0xffffffff);
	अगर (solo_dev->type == SOLO_DEV_6110) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_JPEG_CFG1,
			       (0 << 16) | (30 << 8) | 60);
	पूर्ण
पूर्ण

अटल व्योम solo_mp4e_config(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;
	u32 cfg;

	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CFG0,
		       SOLO_VE_INTR_CTRL(IRQ_LEVEL) |
		       SOLO_VE_BLOCK_SIZE(SOLO_MP4E_EXT_SIZE(solo_dev) >> 16) |
		       SOLO_VE_BLOCK_BASE(SOLO_MP4E_EXT_ADDR(solo_dev) >> 16));


	cfg = SOLO_VE_BYTE_ALIGN(2) | SOLO_VE_INSERT_INDEX
		| SOLO_VE_MOTION_MODE(0);
	अगर (solo_dev->type != SOLO_DEV_6010) अणु
		cfg |= SOLO_VE_MPEG_SIZE_H(
			(SOLO_MP4E_EXT_SIZE(solo_dev) >> 24) & 0x0f);
		cfg |= SOLO_VE_JPEG_SIZE_H(
			(SOLO_JPEG_EXT_SIZE(solo_dev) >> 24) & 0x0f);
	पूर्ण
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_CFG1, cfg);

	solo_reg_ग_लिखो(solo_dev, SOLO_VE_WMRK_POLY, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_VMRK_INIT_KEY, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_WMRK_STRL, 0);
	अगर (solo_dev->type == SOLO_DEV_6110)
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_WMRK_ENABLE, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_ENCRYP_POLY, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VE_ENCRYP_INIT, 0);

	solo_reg_ग_लिखो(solo_dev, SOLO_VE_ATTR,
		       SOLO_VE_LITTLE_ENDIAN |
		       SOLO_COMP_ATTR_FCODE(1) |
		       SOLO_COMP_TIME_INC(0) |
		       SOLO_COMP_TIME_WIDTH(15) |
		       SOLO_DCT_INTERVAL(solo_dev->type == SOLO_DEV_6010 ? 9 : 10));

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_REF_BASE(i),
			       (SOLO_EREF_EXT_ADDR(solo_dev) +
			       (i * SOLO_EREF_EXT_SIZE)) >> 16);
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_REF_BASE_E(i),
			       (SOLO_EREF_EXT_ADDR(solo_dev) +
			       ((i + 16) * SOLO_EREF_EXT_SIZE)) >> 16);
	पूर्ण

	अगर (solo_dev->type == SOLO_DEV_6110) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VE_COMPT_MOT, 0x00040008);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < solo_dev->nr_chans; i++)
			solo_reg_ग_लिखो(solo_dev, SOLO_VE_CH_MOT(i), 0x100);
	पूर्ण
पूर्ण

पूर्णांक solo_enc_init(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	solo_capture_config(solo_dev);
	solo_mp4e_config(solo_dev);
	solo_jpeg_config(solo_dev);

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_SCALE(i), 0);
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_COMP_ENA_E(i), 0);
	पूर्ण

	वापस 0;
पूर्ण

व्योम solo_enc_निकास(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_SCALE(i), 0);
		solo_reg_ग_लिखो(solo_dev, SOLO_CAP_CH_COMP_ENA_E(i), 0);
	पूर्ण
पूर्ण
