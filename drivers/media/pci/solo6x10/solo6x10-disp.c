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
#समावेश <linux/module.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-ioctl.h>

#समावेश "solo6x10.h"

#घोषणा SOLO_VCLK_DELAY			3
#घोषणा SOLO_PROGRESSIVE_VSIZE		1024

#घोषणा SOLO_MOT_THRESH_W		64
#घोषणा SOLO_MOT_THRESH_H		64
#घोषणा SOLO_MOT_THRESH_SIZE		8192
#घोषणा SOLO_MOT_THRESH_REAL		(SOLO_MOT_THRESH_W * SOLO_MOT_THRESH_H)
#घोषणा SOLO_MOT_FLAG_SIZE		1024
#घोषणा SOLO_MOT_FLAG_AREA		(SOLO_MOT_FLAG_SIZE * 16)

अटल व्योम solo_vin_config(काष्ठा solo_dev *solo_dev)
अणु
	solo_dev->vin_hstart = 8;
	solo_dev->vin_vstart = 2;

	solo_reg_ग_लिखो(solo_dev, SOLO_SYS_VCLK,
		       SOLO_VCLK_SELECT(2) |
		       SOLO_VCLK_VIN1415_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN1213_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN1011_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0809_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0607_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0405_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0203_DELAY(SOLO_VCLK_DELAY) |
		       SOLO_VCLK_VIN0001_DELAY(SOLO_VCLK_DELAY));

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_ACT_I_P,
		       SOLO_VI_H_START(solo_dev->vin_hstart) |
		       SOLO_VI_V_START(solo_dev->vin_vstart) |
		       SOLO_VI_V_STOP(solo_dev->vin_vstart +
				      solo_dev->video_vsize));

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_ACT_I_S,
		       SOLO_VI_H_START(solo_dev->vout_hstart) |
		       SOLO_VI_V_START(solo_dev->vout_vstart) |
		       SOLO_VI_V_STOP(solo_dev->vout_vstart +
				      solo_dev->video_vsize));

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_ACT_P,
		       SOLO_VI_H_START(0) |
		       SOLO_VI_V_START(1) |
		       SOLO_VI_V_STOP(SOLO_PROGRESSIVE_VSIZE));

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_CH_FORMAT,
		       SOLO_VI_FD_SEL_MASK(0) | SOLO_VI_PROG_MASK(0));

	/* On 6110, initialize mozaic darkness strength */
	अगर (solo_dev->type == SOLO_DEV_6010)
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_FMT_CFG, 0);
	अन्यथा
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_FMT_CFG, 16 << 22);

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_PAGE_SW, 2);

	अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_CONFIG,
			       SOLO_VI_PB_USER_MODE);
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_RANGE_HV,
			       SOLO_VI_PB_HSIZE(858) | SOLO_VI_PB_VSIZE(246));
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_ACT_V,
			       SOLO_VI_PB_VSTART(4) |
			       SOLO_VI_PB_VSTOP(4 + 240));
	पूर्ण अन्यथा अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_CONFIG,
			       SOLO_VI_PB_USER_MODE | SOLO_VI_PB_PAL);
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_RANGE_HV,
			       SOLO_VI_PB_HSIZE(864) | SOLO_VI_PB_VSIZE(294));
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_ACT_V,
			       SOLO_VI_PB_VSTART(4) |
			       SOLO_VI_PB_VSTOP(4 + 288));
	पूर्ण
	solo_reg_ग_लिखो(solo_dev, SOLO_VI_PB_ACT_H, SOLO_VI_PB_HSTART(16) |
		       SOLO_VI_PB_HSTOP(16 + 720));
पूर्ण

अटल व्योम solo_vout_config_cursor(काष्ठा solo_dev *dev)
अणु
	पूर्णांक i;

	/* Load (blank) cursor biपंचांगap mask (2bpp) */
	क्रम (i = 0; i < 20; i++)
		solo_reg_ग_लिखो(dev, SOLO_VO_CURSOR_MASK(i), 0);

	solo_reg_ग_लिखो(dev, SOLO_VO_CURSOR_POS, 0);

	solo_reg_ग_लिखो(dev, SOLO_VO_CURSOR_CLR,
		       (0x80 << 24) | (0x80 << 16) | (0x10 << 8) | 0x80);
	solo_reg_ग_लिखो(dev, SOLO_VO_CURSOR_CLR2, (0xe0 << 8) | 0x80);
पूर्ण

अटल व्योम solo_vout_config(काष्ठा solo_dev *solo_dev)
अणु
	solo_dev->vout_hstart = 6;
	solo_dev->vout_vstart = 8;

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_FMT_ENC,
		       solo_dev->video_type |
		       SOLO_VO_USER_COLOR_SET_NAV |
		       SOLO_VO_USER_COLOR_SET_NAH |
		       SOLO_VO_NA_COLOR_Y(0) |
		       SOLO_VO_NA_COLOR_CB(0) |
		       SOLO_VO_NA_COLOR_CR(0));

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_ACT_H,
		       SOLO_VO_H_START(solo_dev->vout_hstart) |
		       SOLO_VO_H_STOP(solo_dev->vout_hstart +
				      solo_dev->video_hsize));

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_ACT_V,
		       SOLO_VO_V_START(solo_dev->vout_vstart) |
		       SOLO_VO_V_STOP(solo_dev->vout_vstart +
				      solo_dev->video_vsize));

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RANGE_HV,
		       SOLO_VO_H_LEN(solo_dev->video_hsize) |
		       SOLO_VO_V_LEN(solo_dev->video_vsize));

	/* Border & background colors */
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_BORDER_LINE_COLOR,
		       (0xa0 << 24) | (0x88 << 16) | (0xa0 << 8) | 0x88);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_BORDER_FILL_COLOR,
		       (0x10 << 24) | (0x8f << 16) | (0x10 << 8) | 0x8f);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_BKG_COLOR,
		       (16 << 24) | (128 << 16) | (16 << 8) | 128);

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_DISP_ERASE, SOLO_VO_DISP_ERASE_ON);

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_SW, 0);

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_ZOOM_CTRL, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_FREEZE_CTRL, 0);

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_DISP_CTRL, SOLO_VO_DISP_ON |
		       SOLO_VO_DISP_ERASE_COUNT(8) |
		       SOLO_VO_DISP_BASE(SOLO_DISP_EXT_ADDR));


	solo_vout_config_cursor(solo_dev);

	/* Enable channels we support */
	solo_reg_ग_लिखो(solo_dev, SOLO_VI_CH_ENA,
		       (1 << solo_dev->nr_chans) - 1);
पूर्ण

अटल पूर्णांक solo_dma_vin_region(काष्ठा solo_dev *solo_dev, u32 off,
			       u16 val, पूर्णांक reg_size)
अणु
	__le16 *buf;
	स्थिर पूर्णांक n = 64, size = n * माप(*buf);
	पूर्णांक i, ret = 0;

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	क्रम (i = 0; i < n; i++)
		buf[i] = cpu_to_le16(val);

	क्रम (i = 0; i < reg_size; i += size) अणु
		ret = solo_p2m_dma(solo_dev, 1, buf,
				   SOLO_MOTION_EXT_ADDR(solo_dev) + off + i,
				   size, 0, 0);

		अगर (ret)
			अवरोध;
	पूर्ण

	kमुक्त(buf);
	वापस ret;
पूर्ण

पूर्णांक solo_set_motion_threshold(काष्ठा solo_dev *solo_dev, u8 ch, u16 val)
अणु
	अगर (ch > solo_dev->nr_chans)
		वापस -EINVAL;

	वापस solo_dma_vin_region(solo_dev, SOLO_MOT_FLAG_AREA +
				   (ch * SOLO_MOT_THRESH_SIZE * 2),
				   val, SOLO_MOT_THRESH_SIZE);
पूर्ण

पूर्णांक solo_set_motion_block(काष्ठा solo_dev *solo_dev, u8 ch,
		स्थिर u16 *thresholds)
अणु
	स्थिर अचिन्हित size = माप(u16) * 64;
	u32 off = SOLO_MOT_FLAG_AREA + ch * SOLO_MOT_THRESH_SIZE * 2;
	__le16 *buf;
	पूर्णांक x, y;
	पूर्णांक ret = 0;

	buf = kzalloc(size, GFP_KERNEL);
	अगर (buf == शून्य)
		वापस -ENOMEM;
	क्रम (y = 0; y < SOLO_MOTION_SZ; y++) अणु
		क्रम (x = 0; x < SOLO_MOTION_SZ; x++)
			buf[x] = cpu_to_le16(thresholds[y * SOLO_MOTION_SZ + x]);
		ret |= solo_p2m_dma(solo_dev, 1, buf,
			SOLO_MOTION_EXT_ADDR(solo_dev) + off + y * size,
			size, 0, 0);
	पूर्ण
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* First 8k is motion flag (512 bytes * 16). Following that is an 8k+8k
 * threshold and working table क्रम each channel. At least that's what the
 * spec says. However, this code (taken from rdk) has some mystery 8k
 * block right after the flag area, beक्रमe the first thresh table. */
अटल व्योम solo_motion_config(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		/* Clear motion flag area */
		solo_dma_vin_region(solo_dev, i * SOLO_MOT_FLAG_SIZE, 0x0000,
				    SOLO_MOT_FLAG_SIZE);

		/* Clear working cache table */
		solo_dma_vin_region(solo_dev, SOLO_MOT_FLAG_AREA +
				    (i * SOLO_MOT_THRESH_SIZE * 2) +
				    SOLO_MOT_THRESH_SIZE, 0x0000,
				    SOLO_MOT_THRESH_SIZE);

		/* Set शेष threshold table */
		solo_set_motion_threshold(solo_dev, i, SOLO_DEF_MOT_THRESH);
	पूर्ण

	/* Default motion settings */
	solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOT_ADR, SOLO_VI_MOTION_EN(0) |
		       (SOLO_MOTION_EXT_ADDR(solo_dev) >> 16));
	solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOT_CTRL,
		       SOLO_VI_MOTION_FRAME_COUNT(3) |
		       SOLO_VI_MOTION_SAMPLE_LENGTH(solo_dev->video_hsize / 16)
		       /* | SOLO_VI_MOTION_INTR_START_STOP */
		       | SOLO_VI_MOTION_SAMPLE_COUNT(10));

	solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOTION_BORDER, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VI_MOTION_BAR, 0);
पूर्ण

पूर्णांक solo_disp_init(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	solo_dev->video_hsize = 704;
	अगर (solo_dev->video_type == SOLO_VO_FMT_TYPE_NTSC) अणु
		solo_dev->video_vsize = 240;
		solo_dev->fps = 30;
	पूर्ण अन्यथा अणु
		solo_dev->video_vsize = 288;
		solo_dev->fps = 25;
	पूर्ण

	solo_vin_config(solo_dev);
	solo_motion_config(solo_dev);
	solo_vout_config(solo_dev);

	क्रम (i = 0; i < solo_dev->nr_chans; i++)
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_ON(i), 1);

	वापस 0;
पूर्ण

व्योम solo_disp_निकास(काष्ठा solo_dev *solo_dev)
अणु
	पूर्णांक i;

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_DISP_CTRL, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_ZOOM_CTRL, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_FREEZE_CTRL, 0);

	क्रम (i = 0; i < solo_dev->nr_chans; i++) अणु
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_CTRL0(i), 0);
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_CTRL1(i), 0);
		solo_reg_ग_लिखो(solo_dev, SOLO_VI_WIN_ON(i), 0);
	पूर्ण

	/* Set शेष border */
	क्रम (i = 0; i < 5; i++)
		solo_reg_ग_लिखो(solo_dev, SOLO_VO_BORDER_X(i), 0);

	क्रम (i = 0; i < 5; i++)
		solo_reg_ग_लिखो(solo_dev, SOLO_VO_BORDER_Y(i), 0);

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_BORDER_LINE_MASK, 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_BORDER_FILL_MASK, 0);

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RECTANGLE_CTRL(0), 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RECTANGLE_START(0), 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RECTANGLE_STOP(0), 0);

	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RECTANGLE_CTRL(1), 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RECTANGLE_START(1), 0);
	solo_reg_ग_लिखो(solo_dev, SOLO_VO_RECTANGLE_STOP(1), 0);
पूर्ण
