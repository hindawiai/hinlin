<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2008 Freescale Semiconductor, Inc. All Rights Reserved.
 *
 *  Freescale DIU Frame Buffer device driver
 *
 *  Authors: Hongjun Chen <hong-jun.chen@मुक्तscale.com>
 *           Paul Widmer <paul.widmer@मुक्तscale.com>
 *           Srikanth Srinivasan <srikanth.srinivasan@मुक्तscale.com>
 *           York Sun <yorksun@मुक्तscale.com>
 *
 *   Based on imxfb.c Copyright (C) 2004 S.Hauer, Pengutronix
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/fb.h>
#समावेश <linux/init.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/clk.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <sysdev/fsl_soc.h>
#समावेश <linux/fsl-diu-fb.h>
#समावेश "edid.h"

#घोषणा NUM_AOIS	5	/* 1 क्रम plane 0, 2 क्रम planes 1 & 2 each */

/* HW cursor parameters */
#घोषणा MAX_CURS		32

/* INT_STATUS/INT_MASK field descriptions */
#घोषणा INT_VSYNC	0x01	/* Vsync पूर्णांकerrupt  */
#घोषणा INT_VSYNC_WB	0x02	/* Vsync पूर्णांकerrupt क्रम ग_लिखो back operation */
#घोषणा INT_UNDRUN	0x04	/* Under run exception पूर्णांकerrupt */
#घोषणा INT_PARERR	0x08	/* Display parameters error पूर्णांकerrupt */
#घोषणा INT_LS_BF_VS	0x10	/* Lines beक्रमe vsync. पूर्णांकerrupt */

/*
 * List of supported video modes
 *
 * The first entry is the शेष video mode.  The reमुख्य entries are in
 * order अगर increasing resolution and frequency.  The 320x240-60 mode is
 * the initial AOI क्रम the second and third planes.
 */
अटल काष्ठा fb_videomode fsl_diu_mode_db[] = अणु
	अणु
		.refresh	= 60,
		.xres		= 1024,
		.yres		= 768,
		.pixघड़ी	= 15385,
		.left_margin	= 160,
		.right_margin	= 24,
		.upper_margin	= 29,
		.lower_margin	= 3,
		.hsync_len	= 136,
		.vsync_len	= 6,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 320,
		.yres		= 240,
		.pixघड़ी	= 79440,
		.left_margin	= 16,
		.right_margin	= 16,
		.upper_margin	= 16,
		.lower_margin	= 5,
		.hsync_len	= 48,
		.vsync_len	= 1,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh        = 60,
		.xres           = 640,
		.yres           = 480,
		.pixघड़ी       = 39722,
		.left_margin    = 48,
		.right_margin   = 16,
		.upper_margin   = 33,
		.lower_margin   = 10,
		.hsync_len      = 96,
		.vsync_len      = 2,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh        = 72,
		.xres           = 640,
		.yres           = 480,
		.pixघड़ी       = 32052,
		.left_margin    = 128,
		.right_margin   = 24,
		.upper_margin   = 28,
		.lower_margin   = 9,
		.hsync_len      = 40,
		.vsync_len      = 3,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh        = 75,
		.xres           = 640,
		.yres           = 480,
		.pixघड़ी       = 31747,
		.left_margin    = 120,
		.right_margin   = 16,
		.upper_margin   = 16,
		.lower_margin   = 1,
		.hsync_len      = 64,
		.vsync_len      = 3,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh        = 90,
		.xres           = 640,
		.yres           = 480,
		.pixघड़ी       = 25057,
		.left_margin    = 120,
		.right_margin   = 32,
		.upper_margin   = 14,
		.lower_margin   = 25,
		.hsync_len      = 40,
		.vsync_len      = 14,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh        = 100,
		.xres           = 640,
		.yres           = 480,
		.pixघड़ी       = 22272,
		.left_margin    = 48,
		.right_margin   = 32,
		.upper_margin   = 17,
		.lower_margin   = 22,
		.hsync_len      = 128,
		.vsync_len      = 12,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 800,
		.yres		= 480,
		.pixघड़ी	= 33805,
		.left_margin	= 96,
		.right_margin	= 24,
		.upper_margin	= 10,
		.lower_margin	= 3,
		.hsync_len	= 72,
		.vsync_len	= 7,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh        = 60,
		.xres           = 800,
		.yres           = 600,
		.pixघड़ी       = 25000,
		.left_margin    = 88,
		.right_margin   = 40,
		.upper_margin   = 23,
		.lower_margin   = 1,
		.hsync_len      = 128,
		.vsync_len      = 4,
		.sync           = FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode          = FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 854,
		.yres		= 480,
		.pixघड़ी	= 31518,
		.left_margin	= 104,
		.right_margin	= 16,
		.upper_margin	= 13,
		.lower_margin	= 1,
		.hsync_len	= 88,
		.vsync_len	= 3,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 70,
		.xres		= 1024,
		.yres		= 768,
		.pixघड़ी	= 16886,
		.left_margin	= 3,
		.right_margin	= 3,
		.upper_margin	= 2,
		.lower_margin	= 2,
		.hsync_len	= 40,
		.vsync_len	= 18,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 75,
		.xres		= 1024,
		.yres		= 768,
		.pixघड़ी	= 15009,
		.left_margin	= 3,
		.right_margin	= 3,
		.upper_margin	= 2,
		.lower_margin	= 2,
		.hsync_len	= 80,
		.vsync_len	= 32,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 1280,
		.yres		= 480,
		.pixघड़ी	= 18939,
		.left_margin	= 353,
		.right_margin	= 47,
		.upper_margin	= 39,
		.lower_margin	= 4,
		.hsync_len	= 8,
		.vsync_len	= 2,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 1280,
		.yres		= 720,
		.pixघड़ी	= 13426,
		.left_margin	= 192,
		.right_margin	= 64,
		.upper_margin	= 22,
		.lower_margin	= 1,
		.hsync_len	= 136,
		.vsync_len	= 3,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 1280,
		.yres		= 1024,
		.pixघड़ी	= 9375,
		.left_margin	= 38,
		.right_margin	= 128,
		.upper_margin	= 2,
		.lower_margin	= 7,
		.hsync_len	= 216,
		.vsync_len	= 37,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 70,
		.xres		= 1280,
		.yres		= 1024,
		.pixघड़ी	= 9380,
		.left_margin	= 6,
		.right_margin	= 6,
		.upper_margin	= 4,
		.lower_margin	= 4,
		.hsync_len	= 60,
		.vsync_len	= 94,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 75,
		.xres		= 1280,
		.yres		= 1024,
		.pixघड़ी	= 9380,
		.left_margin	= 6,
		.right_margin	= 6,
		.upper_margin	= 4,
		.lower_margin	= 4,
		.hsync_len	= 60,
		.vsync_len	= 15,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
	अणु
		.refresh	= 60,
		.xres		= 1920,
		.yres		= 1080,
		.pixघड़ी	= 5787,
		.left_margin	= 328,
		.right_margin	= 120,
		.upper_margin	= 34,
		.lower_margin	= 1,
		.hsync_len	= 208,
		.vsync_len	= 3,
		.sync		= FB_SYNC_COMP_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode		= FB_VMODE_NONINTERLACED
	पूर्ण,
पूर्ण;

अटल अक्षर *fb_mode;
अटल अचिन्हित दीर्घ शेष_bpp = 32;
अटल क्रमागत fsl_diu_monitor_port monitor_port;
अटल अक्षर *monitor_string;

#अगर defined(CONFIG_NOT_COHERENT_CACHE)
अटल u8 *coherence_data;
अटल माप_प्रकार coherence_data_size;
अटल अचिन्हित पूर्णांक d_cache_line_size;
#पूर्ण_अगर

अटल DEFINE_SPINLOCK(diu_lock);

क्रमागत mfb_index अणु
	PLANE0 = 0,	/* Plane 0, only one AOI that fills the screen */
	PLANE1_AOI0,	/* Plane 1, first AOI */
	PLANE1_AOI1,	/* Plane 1, second AOI */
	PLANE2_AOI0,	/* Plane 2, first AOI */
	PLANE2_AOI1,	/* Plane 2, second AOI */
पूर्ण;

काष्ठा mfb_info अणु
	क्रमागत mfb_index index;
	अक्षर *id;
	पूर्णांक रेजिस्टरed;
	अचिन्हित दीर्घ pseuकरो_palette[16];
	काष्ठा diu_ad *ad;
	अचिन्हित अक्षर g_alpha;
	अचिन्हित पूर्णांक count;
	पूर्णांक x_aoi_d;		/* aoi display x offset to physical screen */
	पूर्णांक y_aoi_d;		/* aoi display y offset to physical screen */
	काष्ठा fsl_diu_data *parent;
पूर्ण;

/**
 * काष्ठा fsl_diu_data - per-DIU data काष्ठाure
 * @dma_addr: DMA address of this काष्ठाure
 * @fsl_diu_info: fb_info objects, one per AOI
 * @dev_attr: sysfs काष्ठाure
 * @irq: IRQ
 * @monitor_port: the monitor port this DIU is connected to
 * @diu_reg: poपूर्णांकer to the DIU hardware रेजिस्टरs
 * @reg_lock: spinlock क्रम रेजिस्टर access
 * @dummy_aoi: video buffer क्रम the 4x4 32-bit dummy AOI
 * dummy_ad: DIU Area Descriptor क्रम the dummy AOI
 * @ad[]: Area Descriptors क्रम each real AOI
 * @gamma: gamma color table
 * @cursor: hardware cursor data
 * @blank_cursor: blank cursor क्रम hiding cursor
 * @next_cursor: scratch space to build load cursor
 * @edid_data: EDID inक्रमmation buffer
 * @has_edid: whether or not the EDID buffer is valid
 *
 * This data काष्ठाure must be allocated with 32-byte alignment, so that the
 * पूर्णांकernal fields can be aligned properly.
 */
काष्ठा fsl_diu_data अणु
	dma_addr_t dma_addr;
	काष्ठा fb_info fsl_diu_info[NUM_AOIS];
	काष्ठा mfb_info mfb[NUM_AOIS];
	काष्ठा device_attribute dev_attr;
	अचिन्हित पूर्णांक irq;
	क्रमागत fsl_diu_monitor_port monitor_port;
	काष्ठा diu __iomem *diu_reg;
	spinlock_t reg_lock;
	u8 dummy_aoi[4 * 4 * 4];
	काष्ठा diu_ad dummy_ad __aligned(8);
	काष्ठा diu_ad ad[NUM_AOIS] __aligned(8);
	u8 gamma[256 * 3] __aligned(32);
	/* It's easier to parse the cursor data as little-endian */
	__le16 cursor[MAX_CURS * MAX_CURS] __aligned(32);
	/* Blank cursor data -- used to hide the cursor */
	__le16 blank_cursor[MAX_CURS * MAX_CURS] __aligned(32);
	/* Scratch cursor data -- used to build new cursor */
	__le16 next_cursor[MAX_CURS * MAX_CURS] __aligned(32);
	uपूर्णांक8_t edid_data[EDID_LENGTH];
	bool has_edid;
पूर्ण __aligned(32);

/* Determine the DMA address of a member of the fsl_diu_data काष्ठाure */
#घोषणा DMA_ADDR(p, f) ((p)->dma_addr + दुरत्व(काष्ठा fsl_diu_data, f))

अटल स्थिर काष्ठा mfb_info mfb_ढाँचा[] = अणु
	अणु
		.index = PLANE0,
		.id = "Panel0",
		.रेजिस्टरed = 0,
		.count = 0,
		.x_aoi_d = 0,
		.y_aoi_d = 0,
	पूर्ण,
	अणु
		.index = PLANE1_AOI0,
		.id = "Panel1 AOI0",
		.रेजिस्टरed = 0,
		.g_alpha = 0xff,
		.count = 0,
		.x_aoi_d = 0,
		.y_aoi_d = 0,
	पूर्ण,
	अणु
		.index = PLANE1_AOI1,
		.id = "Panel1 AOI1",
		.रेजिस्टरed = 0,
		.g_alpha = 0xff,
		.count = 0,
		.x_aoi_d = 0,
		.y_aoi_d = 480,
	पूर्ण,
	अणु
		.index = PLANE2_AOI0,
		.id = "Panel2 AOI0",
		.रेजिस्टरed = 0,
		.g_alpha = 0xff,
		.count = 0,
		.x_aoi_d = 640,
		.y_aoi_d = 0,
	पूर्ण,
	अणु
		.index = PLANE2_AOI1,
		.id = "Panel2 AOI1",
		.रेजिस्टरed = 0,
		.g_alpha = 0xff,
		.count = 0,
		.x_aoi_d = 640,
		.y_aoi_d = 480,
	पूर्ण,
पूर्ण;

#अगर_घोषित DEBUG
अटल व्योम __attribute__ ((unused)) fsl_diu_dump(काष्ठा diu __iomem *hw)
अणु
	mb();
	pr_debug("DIU: desc=%08x,%08x,%08x, gamma=%08x palette=%08x "
		 "cursor=%08x curs_pos=%08x diu_mode=%08x bgnd=%08x "
		 "disp_size=%08x hsyn_para=%08x vsyn_para=%08x syn_pol=%08x "
		 "thresholds=%08x int_mask=%08x plut=%08x\n",
		 hw->desc[0], hw->desc[1], hw->desc[2], hw->gamma,
		 hw->palette, hw->cursor, hw->curs_pos, hw->diu_mode,
		 hw->bgnd, hw->disp_size, hw->hsyn_para, hw->vsyn_para,
		 hw->syn_pol, hw->thresholds, hw->पूर्णांक_mask, hw->plut);
	rmb();
पूर्ण
#पूर्ण_अगर

/**
 * fsl_diu_name_to_port - convert a port name to a monitor port क्रमागत
 *
 * Takes the name of a monitor port ("dvi", "lvds", or "dlvds") and वापसs
 * the क्रमागत fsl_diu_monitor_port that corresponds to that string.
 *
 * For compatibility with older versions, a number ("0", "1", or "2") is also
 * supported.
 *
 * If the string is unknown, DVI is assumed.
 *
 * If the particular port is not supported by the platक्रमm, another port
 * (platक्रमm-specअगरic) is chosen instead.
 */
अटल क्रमागत fsl_diu_monitor_port fsl_diu_name_to_port(स्थिर अक्षर *s)
अणु
	क्रमागत fsl_diu_monitor_port port = FSL_DIU_PORT_DVI;
	अचिन्हित दीर्घ val;

	अगर (s) अणु
		अगर (!kम_से_अदीर्घ(s, 10, &val) && (val <= 2))
			port = (क्रमागत fsl_diu_monitor_port) val;
		अन्यथा अगर (म_भेदन(s, "lvds", 4) == 0)
			port = FSL_DIU_PORT_LVDS;
		अन्यथा अगर (म_भेदन(s, "dlvds", 5) == 0)
			port = FSL_DIU_PORT_DLVDS;
	पूर्ण

	अगर (diu_ops.valid_monitor_port)
		port = diu_ops.valid_monitor_port(port);

	वापस port;
पूर्ण

/*
 * Workaround क्रम failed writing desc रेजिस्टर of planes.
 * Needed with MPC5121 DIU rev 2.0 silicon.
 */
व्योम wr_reg_wa(u32 *reg, u32 val)
अणु
	करो अणु
		out_be32(reg, val);
	पूर्ण जबतक (in_be32(reg) != val);
पूर्ण

अटल व्योम fsl_diu_enable_panel(काष्ठा fb_info *info)
अणु
	काष्ठा mfb_info *pmfbi, *cmfbi, *mfbi = info->par;
	काष्ठा diu_ad *ad = mfbi->ad;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu __iomem *hw = data->diu_reg;

	चयन (mfbi->index) अणु
	हाल PLANE0:
		wr_reg_wa(&hw->desc[0], ad->paddr);
		अवरोध;
	हाल PLANE1_AOI0:
		cmfbi = &data->mfb[2];
		अगर (hw->desc[1] != ad->paddr) अणु	/* AOI0 बंदd */
			अगर (cmfbi->count > 0)	/* AOI1 खोलो */
				ad->next_ad =
					cpu_to_le32(cmfbi->ad->paddr);
			अन्यथा
				ad->next_ad = 0;
			wr_reg_wa(&hw->desc[1], ad->paddr);
		पूर्ण
		अवरोध;
	हाल PLANE2_AOI0:
		cmfbi = &data->mfb[4];
		अगर (hw->desc[2] != ad->paddr) अणु	/* AOI0 बंदd */
			अगर (cmfbi->count > 0)	/* AOI1 खोलो */
				ad->next_ad =
					cpu_to_le32(cmfbi->ad->paddr);
			अन्यथा
				ad->next_ad = 0;
			wr_reg_wa(&hw->desc[2], ad->paddr);
		पूर्ण
		अवरोध;
	हाल PLANE1_AOI1:
		pmfbi = &data->mfb[1];
		ad->next_ad = 0;
		अगर (hw->desc[1] == data->dummy_ad.paddr)
			wr_reg_wa(&hw->desc[1], ad->paddr);
		अन्यथा					/* AOI0 खोलो */
			pmfbi->ad->next_ad = cpu_to_le32(ad->paddr);
		अवरोध;
	हाल PLANE2_AOI1:
		pmfbi = &data->mfb[3];
		ad->next_ad = 0;
		अगर (hw->desc[2] == data->dummy_ad.paddr)
			wr_reg_wa(&hw->desc[2], ad->paddr);
		अन्यथा				/* AOI0 was खोलो */
			pmfbi->ad->next_ad = cpu_to_le32(ad->paddr);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम fsl_diu_disable_panel(काष्ठा fb_info *info)
अणु
	काष्ठा mfb_info *pmfbi, *cmfbi, *mfbi = info->par;
	काष्ठा diu_ad *ad = mfbi->ad;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu __iomem *hw = data->diu_reg;

	चयन (mfbi->index) अणु
	हाल PLANE0:
		wr_reg_wa(&hw->desc[0], 0);
		अवरोध;
	हाल PLANE1_AOI0:
		cmfbi = &data->mfb[2];
		अगर (cmfbi->count > 0)	/* AOI1 is खोलो */
			wr_reg_wa(&hw->desc[1], cmfbi->ad->paddr);
					/* move AOI1 to the first */
		अन्यथा			/* AOI1 was बंदd */
			wr_reg_wa(&hw->desc[1], data->dummy_ad.paddr);
					/* बंद AOI 0 */
		अवरोध;
	हाल PLANE2_AOI0:
		cmfbi = &data->mfb[4];
		अगर (cmfbi->count > 0)	/* AOI1 is खोलो */
			wr_reg_wa(&hw->desc[2], cmfbi->ad->paddr);
					/* move AOI1 to the first */
		अन्यथा			/* AOI1 was बंदd */
			wr_reg_wa(&hw->desc[2], data->dummy_ad.paddr);
					/* बंद AOI 0 */
		अवरोध;
	हाल PLANE1_AOI1:
		pmfbi = &data->mfb[1];
		अगर (hw->desc[1] != ad->paddr) अणु
				/* AOI1 is not the first in the chain */
			अगर (pmfbi->count > 0)
					/* AOI0 is खोलो, must be the first */
				pmfbi->ad->next_ad = 0;
		पूर्ण अन्यथा			/* AOI1 is the first in the chain */
			wr_reg_wa(&hw->desc[1], data->dummy_ad.paddr);
					/* बंद AOI 1 */
		अवरोध;
	हाल PLANE2_AOI1:
		pmfbi = &data->mfb[3];
		अगर (hw->desc[2] != ad->paddr) अणु
				/* AOI1 is not the first in the chain */
			अगर (pmfbi->count > 0)
				/* AOI0 is खोलो, must be the first */
				pmfbi->ad->next_ad = 0;
		पूर्ण अन्यथा		/* AOI1 is the first in the chain */
			wr_reg_wa(&hw->desc[2], data->dummy_ad.paddr);
				/* बंद AOI 1 */
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम enable_lcdc(काष्ठा fb_info *info)
अणु
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu __iomem *hw = data->diu_reg;

	out_be32(&hw->diu_mode, MFB_MODE1);
पूर्ण

अटल व्योम disable_lcdc(काष्ठा fb_info *info)
अणु
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu __iomem *hw = data->diu_reg;

	out_be32(&hw->diu_mode, 0);
पूर्ण

अटल व्योम adjust_aoi_size_position(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	काष्ठा mfb_info *lower_aoi_mfbi, *upper_aoi_mfbi, *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	पूर्णांक available_height, upper_aoi_bottom;
	क्रमागत mfb_index index = mfbi->index;
	पूर्णांक lower_aoi_is_खोलो, upper_aoi_is_खोलो;
	__u32 base_plane_width, base_plane_height, upper_aoi_height;

	base_plane_width = data->fsl_diu_info[0].var.xres;
	base_plane_height = data->fsl_diu_info[0].var.yres;

	अगर (mfbi->x_aoi_d < 0)
		mfbi->x_aoi_d = 0;
	अगर (mfbi->y_aoi_d < 0)
		mfbi->y_aoi_d = 0;
	चयन (index) अणु
	हाल PLANE0:
		अगर (mfbi->x_aoi_d != 0)
			mfbi->x_aoi_d = 0;
		अगर (mfbi->y_aoi_d != 0)
			mfbi->y_aoi_d = 0;
		अवरोध;
	हाल PLANE1_AOI0:
	हाल PLANE2_AOI0:
		lower_aoi_mfbi = data->fsl_diu_info[index+1].par;
		lower_aoi_is_खोलो = lower_aoi_mfbi->count > 0 ? 1 : 0;
		अगर (var->xres > base_plane_width)
			var->xres = base_plane_width;
		अगर ((mfbi->x_aoi_d + var->xres) > base_plane_width)
			mfbi->x_aoi_d = base_plane_width - var->xres;

		अगर (lower_aoi_is_खोलो)
			available_height = lower_aoi_mfbi->y_aoi_d;
		अन्यथा
			available_height = base_plane_height;
		अगर (var->yres > available_height)
			var->yres = available_height;
		अगर ((mfbi->y_aoi_d + var->yres) > available_height)
			mfbi->y_aoi_d = available_height - var->yres;
		अवरोध;
	हाल PLANE1_AOI1:
	हाल PLANE2_AOI1:
		upper_aoi_mfbi = data->fsl_diu_info[index-1].par;
		upper_aoi_height = data->fsl_diu_info[index-1].var.yres;
		upper_aoi_bottom = upper_aoi_mfbi->y_aoi_d + upper_aoi_height;
		upper_aoi_is_खोलो = upper_aoi_mfbi->count > 0 ? 1 : 0;
		अगर (var->xres > base_plane_width)
			var->xres = base_plane_width;
		अगर ((mfbi->x_aoi_d + var->xres) > base_plane_width)
			mfbi->x_aoi_d = base_plane_width - var->xres;
		अगर (mfbi->y_aoi_d < 0)
			mfbi->y_aoi_d = 0;
		अगर (upper_aoi_is_खोलो) अणु
			अगर (mfbi->y_aoi_d < upper_aoi_bottom)
				mfbi->y_aoi_d = upper_aoi_bottom;
			available_height = base_plane_height
						- upper_aoi_bottom;
		पूर्ण अन्यथा
			available_height = base_plane_height;
		अगर (var->yres > available_height)
			var->yres = available_height;
		अगर ((mfbi->y_aoi_d + var->yres) > base_plane_height)
			mfbi->y_aoi_d = base_plane_height - var->yres;
		अवरोध;
	पूर्ण
पूर्ण
/*
 * Checks to see अगर the hardware supports the state requested by var passed
 * in. This function करोes not alter the hardware state! If the var passed in
 * is slightly off by what the hardware can support then we alter the var
 * PASSED in to what we can करो. If the hardware करोesn't support mode change
 * a -EINVAL will be वापसed by the upper layers.
 */
अटल पूर्णांक fsl_diu_check_var(काष्ठा fb_var_screeninfo *var,
				काष्ठा fb_info *info)
अणु
	अगर (var->xres_भव < var->xres)
		var->xres_भव = var->xres;
	अगर (var->yres_भव < var->yres)
		var->yres_भव = var->yres;

	अगर (var->xoffset + info->var.xres > info->var.xres_भव)
		var->xoffset = info->var.xres_भव - info->var.xres;

	अगर (var->yoffset + info->var.yres > info->var.yres_भव)
		var->yoffset = info->var.yres_भव - info->var.yres;

	अगर ((var->bits_per_pixel != 32) && (var->bits_per_pixel != 24) &&
	    (var->bits_per_pixel != 16))
		var->bits_per_pixel = शेष_bpp;

	चयन (var->bits_per_pixel) अणु
	हाल 16:
		var->red.length = 5;
		var->red.offset = 11;
		var->red.msb_right = 0;

		var->green.length = 6;
		var->green.offset = 5;
		var->green.msb_right = 0;

		var->blue.length = 5;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 0;
		var->transp.offset = 0;
		var->transp.msb_right = 0;
		अवरोध;
	हाल 24:
		var->red.length = 8;
		var->red.offset = 0;
		var->red.msb_right = 0;

		var->green.length = 8;
		var->green.offset = 8;
		var->green.msb_right = 0;

		var->blue.length = 8;
		var->blue.offset = 16;
		var->blue.msb_right = 0;

		var->transp.length = 0;
		var->transp.offset = 0;
		var->transp.msb_right = 0;
		अवरोध;
	हाल 32:
		var->red.length = 8;
		var->red.offset = 16;
		var->red.msb_right = 0;

		var->green.length = 8;
		var->green.offset = 8;
		var->green.msb_right = 0;

		var->blue.length = 8;
		var->blue.offset = 0;
		var->blue.msb_right = 0;

		var->transp.length = 8;
		var->transp.offset = 24;
		var->transp.msb_right = 0;

		अवरोध;
	पूर्ण

	var->height = -1;
	var->width = -1;
	var->grayscale = 0;

	/* Copy nonstd field to/from sync क्रम fbset usage */
	var->sync |= var->nonstd;
	var->nonstd |= var->sync;

	adjust_aoi_size_position(var, info);
	वापस 0;
पूर्ण

अटल व्योम set_fix(काष्ठा fb_info *info)
अणु
	काष्ठा fb_fix_screeninfo *fix = &info->fix;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा mfb_info *mfbi = info->par;

	म_नकलन(fix->id, mfbi->id, माप(fix->id));
	fix->line_length = var->xres_भव * var->bits_per_pixel / 8;
	fix->type = FB_TYPE_PACKED_PIXELS;
	fix->accel = FB_ACCEL_NONE;
	fix->visual = FB_VISUAL_TRUECOLOR;
	fix->xpanstep = 1;
	fix->ypanstep = 1;
पूर्ण

अटल व्योम update_lcdc(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu __iomem *hw;
	पूर्णांक i, j;
	u8 *gamma_table_base;

	u32 temp;

	hw = data->diu_reg;

	अगर (diu_ops.set_monitor_port)
		diu_ops.set_monitor_port(data->monitor_port);
	gamma_table_base = data->gamma;

	/* Prep क्रम DIU init  - gamma table, cursor table */

	क्रम (i = 0; i <= 2; i++)
		क्रम (j = 0; j <= 255; j++)
			*gamma_table_base++ = j;

	अगर (diu_ops.set_gamma_table)
		diu_ops.set_gamma_table(data->monitor_port, data->gamma);

	disable_lcdc(info);

	/* Program DIU रेजिस्टरs */

	out_be32(&hw->gamma, DMA_ADDR(data, gamma));

	out_be32(&hw->bgnd, 0x007F7F7F); /* Set background to grey */
	out_be32(&hw->disp_size, (var->yres << 16) | var->xres);

	/* Horizontal and vertical configuration रेजिस्टर */
	temp = var->left_margin << 22 | /* BP_H */
	       var->hsync_len << 11 |   /* PW_H */
	       var->right_margin;       /* FP_H */

	out_be32(&hw->hsyn_para, temp);

	temp = var->upper_margin << 22 | /* BP_V */
	       var->vsync_len << 11 |    /* PW_V  */
	       var->lower_margin;        /* FP_V  */

	out_be32(&hw->vsyn_para, temp);

	diu_ops.set_pixel_घड़ी(var->pixघड़ी);

#अगर_अघोषित CONFIG_PPC_MPC512x
	/*
	 * The PLUT रेजिस्टर is defined dअगरferently on the MPC5121 than it
	 * is on other SOCs.  Unक्रमtunately, there's no करोcumentation that
	 * explains how it's supposed to be programmed, so क्रम now, we leave
	 * it at the शेष value on the MPC5121.
	 *
	 * For other SOCs, program it क्रम the highest priority, which will
	 * reduce the chance of underrun. Technically, we should scale the
	 * priority to match the screen resolution, but करोing that properly
	 * requires delicate fine-tuning क्रम each use-हाल.
	 */
	out_be32(&hw->plut, 0x01F5F666);
#पूर्ण_अगर

	/* Enable the DIU */
	enable_lcdc(info);
पूर्ण

अटल पूर्णांक map_video_memory(काष्ठा fb_info *info)
अणु
	u32 smem_len = info->fix.line_length * info->var.yres_भव;
	व्योम *p;

	p = alloc_pages_exact(smem_len, GFP_DMA | __GFP_ZERO);
	अगर (!p) अणु
		dev_err(info->dev, "unable to allocate fb memory\n");
		वापस -ENOMEM;
	पूर्ण
	mutex_lock(&info->mm_lock);
	info->screen_base = p;
	info->fix.smem_start = virt_to_phys(info->screen_base);
	info->fix.smem_len = smem_len;
	mutex_unlock(&info->mm_lock);
	info->screen_size = info->fix.smem_len;

	वापस 0;
पूर्ण

अटल व्योम unmap_video_memory(काष्ठा fb_info *info)
अणु
	व्योम *p = info->screen_base;
	माप_प्रकार l = info->fix.smem_len;

	mutex_lock(&info->mm_lock);
	info->screen_base = शून्य;
	info->fix.smem_start = 0;
	info->fix.smem_len = 0;
	mutex_unlock(&info->mm_lock);

	अगर (p)
		मुक्त_pages_exact(p, l);
पूर्ण

/*
 * Using the fb_var_screeninfo in fb_info we set the aoi of this
 * particular framebuffer. It is a light version of fsl_diu_set_par.
 */
अटल पूर्णांक fsl_diu_set_aoi(काष्ठा fb_info *info)
अणु
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा diu_ad *ad = mfbi->ad;

	/* AOI should not be greater than display size */
	ad->offset_xyi = cpu_to_le32((var->yoffset << 16) | var->xoffset);
	ad->offset_xyd = cpu_to_le32((mfbi->y_aoi_d << 16) | mfbi->x_aoi_d);
	वापस 0;
पूर्ण

/**
 * fsl_diu_get_pixel_क्रमmat: वापस the pixel क्रमmat क्रम a given color depth
 *
 * The pixel क्रमmat is a 32-bit value that determine which bits in each
 * pixel are to be used क्रम each color.  This is the शेष function used
 * अगर the platक्रमm करोes not define its own version.
 */
अटल u32 fsl_diu_get_pixel_क्रमmat(अचिन्हित पूर्णांक bits_per_pixel)
अणु
#घोषणा PF_BYTE_F		0x10000000
#घोषणा PF_ALPHA_C_MASK		0x0E000000
#घोषणा PF_ALPHA_C_SHIFT	25
#घोषणा PF_BLUE_C_MASK		0x01800000
#घोषणा PF_BLUE_C_SHIFT		23
#घोषणा PF_GREEN_C_MASK		0x00600000
#घोषणा PF_GREEN_C_SHIFT	21
#घोषणा PF_RED_C_MASK		0x00180000
#घोषणा PF_RED_C_SHIFT		19
#घोषणा PF_PALETTE		0x00040000
#घोषणा PF_PIXEL_S_MASK		0x00030000
#घोषणा PF_PIXEL_S_SHIFT	16
#घोषणा PF_COMP_3_MASK		0x0000F000
#घोषणा PF_COMP_3_SHIFT		12
#घोषणा PF_COMP_2_MASK		0x00000F00
#घोषणा PF_COMP_2_SHIFT		8
#घोषणा PF_COMP_1_MASK		0x000000F0
#घोषणा PF_COMP_1_SHIFT		4
#घोषणा PF_COMP_0_MASK		0x0000000F
#घोषणा PF_COMP_0_SHIFT		0

#घोषणा MAKE_PF(alpha, red, green, blue, size, c0, c1, c2, c3) \
	cpu_to_le32(PF_BYTE_F | (alpha << PF_ALPHA_C_SHIFT) | \
	(blue << PF_BLUE_C_SHIFT) | (green << PF_GREEN_C_SHIFT) | \
	(red << PF_RED_C_SHIFT) | (c3 << PF_COMP_3_SHIFT) | \
	(c2 << PF_COMP_2_SHIFT) | (c1 << PF_COMP_1_SHIFT) | \
	(c0 << PF_COMP_0_SHIFT) | (size << PF_PIXEL_S_SHIFT))

	चयन (bits_per_pixel) अणु
	हाल 32:
		/* 0x88883316 */
		वापस MAKE_PF(3, 2, 1, 0, 3, 8, 8, 8, 8);
	हाल 24:
		/* 0x88082219 */
		वापस MAKE_PF(4, 0, 1, 2, 2, 8, 8, 8, 0);
	हाल 16:
		/* 0x65053118 */
		वापस MAKE_PF(4, 2, 1, 0, 1, 5, 6, 5, 0);
	शेष:
		pr_err("fsl-diu: unsupported color depth %u\n", bits_per_pixel);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * Copies a cursor image from user space to the proper place in driver
 * memory so that the hardware can display the cursor image.
 *
 * Cursor data is represented as a sequence of 'width' bits packed पूर्णांकo bytes.
 * That is, the first 8 bits are in the first byte, the second 8 bits in the
 * second byte, and so on.  Thereक्रमe, the each row of the cursor is (width +
 * 7) / 8 bytes of 'data'
 *
 * The DIU only supports cursors up to 32x32 (MAX_CURS).  We reject cursors
 * larger than this, so we alपढ़ोy know that 'width' <= 32.  Thereक्रमe, we can
 * simplअगरy our code by using a 32-bit big-endian पूर्णांकeger ("line") to पढ़ो in
 * a single line of pixels, and only look at the top 'width' bits of that
 * पूर्णांकeger.
 *
 * This could result in an unaligned 32-bit पढ़ो.  For example, अगर the cursor
 * is 24x24, then the first three bytes of 'image' contain the pixel data क्रम
 * the top line of the cursor.  We करो a 32-bit पढ़ो of 'image', but we look
 * only at the top 24 bits.  Then we increment 'image' by 3 bytes.  The next
 * पढ़ो is unaligned.  The only problem is that we might पढ़ो past the end of
 * 'image' by 1-3 bytes, but that should not cause any problems.
 */
अटल व्योम fsl_diu_load_cursor_image(काष्ठा fb_info *info,
	स्थिर व्योम *image, uपूर्णांक16_t bg, uपूर्णांक16_t fg,
	अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	__le16 *cursor = data->cursor;
	__le16 _fg = cpu_to_le16(fg);
	__le16 _bg = cpu_to_le16(bg);
	अचिन्हित पूर्णांक h, w;

	क्रम (h = 0; h < height; h++) अणु
		uपूर्णांक32_t mask = 1 << 31;
		uपूर्णांक32_t line = be32_to_cpup(image);

		क्रम (w = 0; w < width; w++) अणु
			cursor[w] = (line & mask) ? _fg : _bg;
			mask >>= 1;
		पूर्ण

		cursor += MAX_CURS;
		image += DIV_ROUND_UP(width, 8);
	पूर्ण
पूर्ण

/*
 * Set a hardware cursor.  The image data क्रम the cursor is passed via the
 * fb_cursor object.
 */
अटल पूर्णांक fsl_diu_cursor(काष्ठा fb_info *info, काष्ठा fb_cursor *cursor)
अणु
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu __iomem *hw = data->diu_reg;

	अगर (cursor->image.width > MAX_CURS || cursor->image.height > MAX_CURS)
		वापस -EINVAL;

	/* The cursor size has changed */
	अगर (cursor->set & FB_CUR_SETSIZE) अणु
		/*
		 * The DIU cursor is a fixed size, so when we get this
		 * message, instead of resizing the cursor, we just clear
		 * all the image data, in expectation of new data.  However,
		 * in tests this control करोes not appear to be normally
		 * called.
		 */
		स_रखो(data->cursor, 0, माप(data->cursor));
	पूर्ण

	/* The cursor position has changed (cursor->image.dx|dy) */
	अगर (cursor->set & FB_CUR_SETPOS) अणु
		uपूर्णांक32_t xx, yy;

		yy = (cursor->image.dy - info->var.yoffset) & 0x7ff;
		xx = (cursor->image.dx - info->var.xoffset) & 0x7ff;

		out_be32(&hw->curs_pos, yy << 16 | xx);
	पूर्ण

	/*
	 * FB_CUR_SETIMAGE - the cursor image has changed
	 * FB_CUR_SETCMAP  - the cursor colors has changed
	 * FB_CUR_SETSHAPE - the cursor biपंचांगask has changed
	 */
	अगर (cursor->set & (FB_CUR_SETSHAPE | FB_CUR_SETCMAP | FB_CUR_SETIMAGE)) अणु
		/*
		 * Determine the size of the cursor image data.  Normally,
		 * it's 8x16.
		 */
		अचिन्हित पूर्णांक image_size =
			DIV_ROUND_UP(cursor->image.width, 8) *
			cursor->image.height;
		अचिन्हित पूर्णांक image_words =
			DIV_ROUND_UP(image_size, माप(uपूर्णांक32_t));
		अचिन्हित पूर्णांक bg_idx = cursor->image.bg_color;
		अचिन्हित पूर्णांक fg_idx = cursor->image.fg_color;
		uपूर्णांक32_t *image, *source, *mask;
		uपूर्णांक16_t fg, bg;
		अचिन्हित पूर्णांक i;

		अगर (info->state != FBINFO_STATE_RUNNING)
			वापस 0;

		bg = ((info->cmap.red[bg_idx] & 0xf8) << 7) |
		     ((info->cmap.green[bg_idx] & 0xf8) << 2) |
		     ((info->cmap.blue[bg_idx] & 0xf8) >> 3) |
		     1 << 15;

		fg = ((info->cmap.red[fg_idx] & 0xf8) << 7) |
		     ((info->cmap.green[fg_idx] & 0xf8) << 2) |
		     ((info->cmap.blue[fg_idx] & 0xf8) >> 3) |
		     1 << 15;

		/* Use 32-bit operations on the data to improve perक्रमmance */
		image = (uपूर्णांक32_t *)data->next_cursor;
		source = (uपूर्णांक32_t *)cursor->image.data;
		mask = (uपूर्णांक32_t *)cursor->mask;

		अगर (cursor->rop == ROP_XOR)
			क्रम (i = 0; i < image_words; i++)
				image[i] = source[i] ^ mask[i];
		अन्यथा
			क्रम (i = 0; i < image_words; i++)
				image[i] = source[i] & mask[i];

		fsl_diu_load_cursor_image(info, image, bg, fg,
			cursor->image.width, cursor->image.height);
	पूर्ण

	/*
	 * Show or hide the cursor.  The cursor data is always stored in the
	 * 'cursor' memory block, and the actual cursor position is always in
	 * the DIU's CURS_POS रेजिस्टर.  To hide the cursor, we redirect the
	 * CURSOR रेजिस्टर to a blank cursor.  The show the cursor, we
	 * redirect the CURSOR रेजिस्टर to the real cursor data.
	 */
	अगर (cursor->enable)
		out_be32(&hw->cursor, DMA_ADDR(data, cursor));
	अन्यथा
		out_be32(&hw->cursor, DMA_ADDR(data, blank_cursor));

	वापस 0;
पूर्ण

/*
 * Using the fb_var_screeninfo in fb_info we set the resolution of this
 * particular framebuffer. This function alters the fb_fix_screeninfo stored
 * in fb_info. It करोes not alter var in fb_info since we are using that
 * data. This means we depend on the data in var inside fb_info to be
 * supported by the hardware. fsl_diu_check_var is always called beक्रमe
 * fsl_diu_set_par to ensure this.
 */
अटल पूर्णांक fsl_diu_set_par(काष्ठा fb_info *info)
अणु
	अचिन्हित दीर्घ len;
	काष्ठा fb_var_screeninfo *var = &info->var;
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	काष्ठा diu_ad *ad = mfbi->ad;
	काष्ठा diu __iomem *hw;

	hw = data->diu_reg;

	set_fix(info);

	len = info->var.yres_भव * info->fix.line_length;
	/* Alloc & dealloc each समय resolution/bpp change */
	अगर (len != info->fix.smem_len) अणु
		अगर (info->fix.smem_start)
			unmap_video_memory(info);

		/* Memory allocation क्रम framebuffer */
		अगर (map_video_memory(info)) अणु
			dev_err(info->dev, "unable to allocate fb memory 1\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	अगर (diu_ops.get_pixel_क्रमmat)
		ad->pix_fmt = diu_ops.get_pixel_क्रमmat(data->monitor_port,
						       var->bits_per_pixel);
	अन्यथा
		ad->pix_fmt = fsl_diu_get_pixel_क्रमmat(var->bits_per_pixel);

	ad->addr    = cpu_to_le32(info->fix.smem_start);
	ad->src_size_g_alpha = cpu_to_le32((var->yres_भव << 12) |
				var->xres_भव) | mfbi->g_alpha;
	/* AOI should not be greater than display size */
	ad->aoi_size 	= cpu_to_le32((var->yres << 16) | var->xres);
	ad->offset_xyi = cpu_to_le32((var->yoffset << 16) | var->xoffset);
	ad->offset_xyd = cpu_to_le32((mfbi->y_aoi_d << 16) | mfbi->x_aoi_d);

	/* Disable chroma keying function */
	ad->ckmax_r = 0;
	ad->ckmax_g = 0;
	ad->ckmax_b = 0;

	ad->ckmin_r = 255;
	ad->ckmin_g = 255;
	ad->ckmin_b = 255;

	अगर (mfbi->index == PLANE0)
		update_lcdc(info);
	वापस 0;
पूर्ण

अटल अंतरभूत __u32 CNVT_TOHW(__u32 val, __u32 width)
अणु
	वापस ((val << width) + 0x7FFF - val) >> 16;
पूर्ण

/*
 * Set a single color रेजिस्टर. The values supplied have a 16 bit magnitude
 * which needs to be scaled in this function क्रम the hardware. Things to take
 * पूर्णांकo consideration are how many color रेजिस्टरs, अगर any, are supported with
 * the current color visual. With truecolor mode no color palettes are
 * supported. Here a pseuकरो palette is created which we store the value in
 * pseuकरो_palette in काष्ठा fb_info. For pseuकरोcolor mode we have a limited
 * color palette.
 */
अटल पूर्णांक fsl_diu_setcolreg(अचिन्हित पूर्णांक regno, अचिन्हित पूर्णांक red,
			     अचिन्हित पूर्णांक green, अचिन्हित पूर्णांक blue,
			     अचिन्हित पूर्णांक transp, काष्ठा fb_info *info)
अणु
	पूर्णांक ret = 1;

	/*
	 * If greyscale is true, then we convert the RGB value
	 * to greyscale no matter what visual we are using.
	 */
	अगर (info->var.grayscale)
		red = green = blue = (19595 * red + 38470 * green +
				      7471 * blue) >> 16;
	चयन (info->fix.visual) अणु
	हाल FB_VISUAL_TRUECOLOR:
		/*
		 * 16-bit True Colour.  We encode the RGB value
		 * according to the RGB bitfield inक्रमmation.
		 */
		अगर (regno < 16) अणु
			u32 *pal = info->pseuकरो_palette;
			u32 v;

			red = CNVT_TOHW(red, info->var.red.length);
			green = CNVT_TOHW(green, info->var.green.length);
			blue = CNVT_TOHW(blue, info->var.blue.length);
			transp = CNVT_TOHW(transp, info->var.transp.length);

			v = (red << info->var.red.offset) |
			    (green << info->var.green.offset) |
			    (blue << info->var.blue.offset) |
			    (transp << info->var.transp.offset);

			pal[regno] = v;
			ret = 0;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/*
 * Pan (or wrap, depending on the `vmode' field) the display using the
 * 'xoffset' and 'yoffset' fields of the 'var' काष्ठाure. If the values
 * करोn't fit, वापस -EINVAL.
 */
अटल पूर्णांक fsl_diu_pan_display(काष्ठा fb_var_screeninfo *var,
			     काष्ठा fb_info *info)
अणु
	अगर ((info->var.xoffset == var->xoffset) &&
	    (info->var.yoffset == var->yoffset))
		वापस 0;	/* No change, करो nothing */

	अगर (var->xoffset + info->var.xres > info->var.xres_भव
	    || var->yoffset + info->var.yres > info->var.yres_भव)
		वापस -EINVAL;

	info->var.xoffset = var->xoffset;
	info->var.yoffset = var->yoffset;

	अगर (var->vmode & FB_VMODE_YWRAP)
		info->var.vmode |= FB_VMODE_YWRAP;
	अन्यथा
		info->var.vmode &= ~FB_VMODE_YWRAP;

	fsl_diu_set_aoi(info);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_diu_ioctl(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
		       अचिन्हित दीर्घ arg)
अणु
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा diu_ad *ad = mfbi->ad;
	काष्ठा mfb_chroma_key ck;
	अचिन्हित अक्षर global_alpha;
	काष्ठा aoi_display_offset aoi_d;
	__u32 pix_fmt;
	व्योम __user *buf = (व्योम __user *)arg;

	अगर (!arg)
		वापस -EINVAL;

	dev_dbg(info->dev, "ioctl %08x (dir=%s%s type=%u nr=%u size=%u)\n", cmd,
		_IOC_सूची(cmd) & _IOC_READ ? "R" : "",
		_IOC_सूची(cmd) & _IOC_WRITE ? "W" : "",
		_IOC_TYPE(cmd), _IOC_NR(cmd), _IOC_SIZE(cmd));

	चयन (cmd) अणु
	हाल MFB_SET_PIXFMT_OLD:
		dev_warn(info->dev,
			 "MFB_SET_PIXFMT value of 0x%08x is deprecated.\n",
			 MFB_SET_PIXFMT_OLD);
		fallthrough;
	हाल MFB_SET_PIXFMT:
		अगर (copy_from_user(&pix_fmt, buf, माप(pix_fmt)))
			वापस -EFAULT;
		ad->pix_fmt = pix_fmt;
		अवरोध;
	हाल MFB_GET_PIXFMT_OLD:
		dev_warn(info->dev,
			 "MFB_GET_PIXFMT value of 0x%08x is deprecated.\n",
			 MFB_GET_PIXFMT_OLD);
		fallthrough;
	हाल MFB_GET_PIXFMT:
		pix_fmt = ad->pix_fmt;
		अगर (copy_to_user(buf, &pix_fmt, माप(pix_fmt)))
			वापस -EFAULT;
		अवरोध;
	हाल MFB_SET_AOID:
		अगर (copy_from_user(&aoi_d, buf, माप(aoi_d)))
			वापस -EFAULT;
		mfbi->x_aoi_d = aoi_d.x_aoi_d;
		mfbi->y_aoi_d = aoi_d.y_aoi_d;
		fsl_diu_check_var(&info->var, info);
		fsl_diu_set_aoi(info);
		अवरोध;
	हाल MFB_GET_AOID:
		aoi_d.x_aoi_d = mfbi->x_aoi_d;
		aoi_d.y_aoi_d = mfbi->y_aoi_d;
		अगर (copy_to_user(buf, &aoi_d, माप(aoi_d)))
			वापस -EFAULT;
		अवरोध;
	हाल MFB_GET_ALPHA:
		global_alpha = mfbi->g_alpha;
		अगर (copy_to_user(buf, &global_alpha, माप(global_alpha)))
			वापस -EFAULT;
		अवरोध;
	हाल MFB_SET_ALPHA:
		/* set panel inक्रमmation */
		अगर (copy_from_user(&global_alpha, buf, माप(global_alpha)))
			वापस -EFAULT;
		ad->src_size_g_alpha = (ad->src_size_g_alpha & (~0xff)) |
							(global_alpha & 0xff);
		mfbi->g_alpha = global_alpha;
		अवरोध;
	हाल MFB_SET_CHROMA_KEY:
		/* set panel winक्रमmation */
		अगर (copy_from_user(&ck, buf, माप(ck)))
			वापस -EFAULT;

		अगर (ck.enable &&
		   (ck.red_max < ck.red_min ||
		    ck.green_max < ck.green_min ||
		    ck.blue_max < ck.blue_min))
			वापस -EINVAL;

		अगर (!ck.enable) अणु
			ad->ckmax_r = 0;
			ad->ckmax_g = 0;
			ad->ckmax_b = 0;
			ad->ckmin_r = 255;
			ad->ckmin_g = 255;
			ad->ckmin_b = 255;
		पूर्ण अन्यथा अणु
			ad->ckmax_r = ck.red_max;
			ad->ckmax_g = ck.green_max;
			ad->ckmax_b = ck.blue_max;
			ad->ckmin_r = ck.red_min;
			ad->ckmin_g = ck.green_min;
			ad->ckmin_b = ck.blue_min;
		पूर्ण
		अवरोध;
#अगर_घोषित CONFIG_PPC_MPC512x
	हाल MFB_SET_GAMMA: अणु
		काष्ठा fsl_diu_data *data = mfbi->parent;

		अगर (copy_from_user(data->gamma, buf, माप(data->gamma)))
			वापस -EFAULT;
		setbits32(&data->diu_reg->gamma, 0); /* Force table reload */
		अवरोध;
	पूर्ण
	हाल MFB_GET_GAMMA: अणु
		काष्ठा fsl_diu_data *data = mfbi->parent;

		अगर (copy_to_user(buf, data->gamma, माप(data->gamma)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	शेष:
		dev_err(info->dev, "unknown ioctl command (0x%08X)\n", cmd);
		वापस -ENOIOCTLCMD;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम fsl_diu_enable_पूर्णांकerrupts(काष्ठा fsl_diu_data *data)
अणु
	u32 पूर्णांक_mask = INT_UNDRUN; /* enable underrun detection */

	अगर (IS_ENABLED(CONFIG_NOT_COHERENT_CACHE))
		पूर्णांक_mask |= INT_VSYNC; /* enable vertical sync */

	clrbits32(&data->diu_reg->पूर्णांक_mask, पूर्णांक_mask);
पूर्ण

/* turn on fb अगर count == 1
 */
अटल पूर्णांक fsl_diu_खोलो(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा mfb_info *mfbi = info->par;
	पूर्णांक res = 0;

	/* मुक्त boot splash memory on first /dev/fb0 खोलो */
	अगर ((mfbi->index == PLANE0) && diu_ops.release_booपंचांगem)
		diu_ops.release_booपंचांगem();

	spin_lock(&diu_lock);
	mfbi->count++;
	अगर (mfbi->count == 1) अणु
		fsl_diu_check_var(&info->var, info);
		res = fsl_diu_set_par(info);
		अगर (res < 0)
			mfbi->count--;
		अन्यथा अणु
			fsl_diu_enable_पूर्णांकerrupts(mfbi->parent);
			fsl_diu_enable_panel(info);
		पूर्ण
	पूर्ण

	spin_unlock(&diu_lock);
	वापस res;
पूर्ण

/* turn off fb अगर count == 0
 */
अटल पूर्णांक fsl_diu_release(काष्ठा fb_info *info, पूर्णांक user)
अणु
	काष्ठा mfb_info *mfbi = info->par;

	spin_lock(&diu_lock);
	mfbi->count--;
	अगर (mfbi->count == 0) अणु
		काष्ठा fsl_diu_data *data = mfbi->parent;
		bool disable = true;
		पूर्णांक i;

		/* Disable पूर्णांकerrupts only अगर all AOIs are बंदd */
		क्रम (i = 0; i < NUM_AOIS; i++) अणु
			काष्ठा mfb_info *mi = data->fsl_diu_info[i].par;

			अगर (mi->count)
				disable = false;
		पूर्ण
		अगर (disable)
			out_be32(&data->diu_reg->पूर्णांक_mask, 0xffffffff);
		fsl_diu_disable_panel(info);
	पूर्ण

	spin_unlock(&diu_lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fb_ops fsl_diu_ops = अणु
	.owner = THIS_MODULE,
	.fb_check_var = fsl_diu_check_var,
	.fb_set_par = fsl_diu_set_par,
	.fb_setcolreg = fsl_diu_setcolreg,
	.fb_pan_display = fsl_diu_pan_display,
	.fb_fillrect = cfb_fillrect,
	.fb_copyarea = cfb_copyarea,
	.fb_imageblit = cfb_imageblit,
	.fb_ioctl = fsl_diu_ioctl,
	.fb_खोलो = fsl_diu_खोलो,
	.fb_release = fsl_diu_release,
	.fb_cursor = fsl_diu_cursor,
पूर्ण;

अटल पूर्णांक install_fb(काष्ठा fb_info *info)
अणु
	पूर्णांक rc;
	काष्ठा mfb_info *mfbi = info->par;
	काष्ठा fsl_diu_data *data = mfbi->parent;
	स्थिर अक्षर *aoi_mode, *init_aoi_mode = "320x240";
	काष्ठा fb_videomode *db = fsl_diu_mode_db;
	अचिन्हित पूर्णांक dbsize = ARRAY_SIZE(fsl_diu_mode_db);
	पूर्णांक has_शेष_mode = 1;

	info->var.activate = FB_ACTIVATE_NOW;
	info->fbops = &fsl_diu_ops;
	info->flags = FBINFO_DEFAULT | FBINFO_VIRTFB | FBINFO_PARTIAL_PAN_OK |
		FBINFO_READS_FAST;
	info->pseuकरो_palette = mfbi->pseuकरो_palette;

	rc = fb_alloc_cmap(&info->cmap, 16, 0);
	अगर (rc)
		वापस rc;

	अगर (mfbi->index == PLANE0) अणु
		अगर (data->has_edid) अणु
			/* Now build modedb from EDID */
			fb_edid_to_monspecs(data->edid_data, &info->monspecs);
			fb_videomode_to_modelist(info->monspecs.modedb,
						 info->monspecs.modedb_len,
						 &info->modelist);
			db = info->monspecs.modedb;
			dbsize = info->monspecs.modedb_len;
		पूर्ण
		aoi_mode = fb_mode;
	पूर्ण अन्यथा अणु
		aoi_mode = init_aoi_mode;
	पूर्ण
	rc = fb_find_mode(&info->var, info, aoi_mode, db, dbsize, शून्य,
			  शेष_bpp);
	अगर (!rc) अणु
		/*
		 * For plane 0 we जारी and look पूर्णांकo
		 * driver's पूर्णांकernal modedb.
		 */
		अगर ((mfbi->index == PLANE0) && data->has_edid)
			has_शेष_mode = 0;
		अन्यथा
			वापस -EINVAL;
	पूर्ण

	अगर (!has_शेष_mode) अणु
		rc = fb_find_mode(&info->var, info, aoi_mode, fsl_diu_mode_db,
			ARRAY_SIZE(fsl_diu_mode_db), शून्य, शेष_bpp);
		अगर (rc)
			has_शेष_mode = 1;
	पूर्ण

	/* Still not found, use preferred mode from database अगर any */
	अगर (!has_शेष_mode && info->monspecs.modedb) अणु
		काष्ठा fb_monspecs *specs = &info->monspecs;
		काष्ठा fb_videomode *modedb = &specs->modedb[0];

		/*
		 * Get preferred timing. If not found,
		 * first mode in database will be used.
		 */
		अगर (specs->misc & FB_MISC_1ST_DETAIL) अणु
			पूर्णांक i;

			क्रम (i = 0; i < specs->modedb_len; i++) अणु
				अगर (specs->modedb[i].flag & FB_MODE_IS_FIRST) अणु
					modedb = &specs->modedb[i];
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		info->var.bits_per_pixel = शेष_bpp;
		fb_videomode_to_var(&info->var, modedb);
	पूर्ण

	अगर (fsl_diu_check_var(&info->var, info)) अणु
		dev_err(info->dev, "fsl_diu_check_var failed\n");
		unmap_video_memory(info);
		fb_dealloc_cmap(&info->cmap);
		वापस -EINVAL;
	पूर्ण

	अगर (रेजिस्टर_framebuffer(info) < 0) अणु
		dev_err(info->dev, "register_framebuffer failed\n");
		unmap_video_memory(info);
		fb_dealloc_cmap(&info->cmap);
		वापस -EINVAL;
	पूर्ण

	mfbi->रेजिस्टरed = 1;
	dev_info(info->dev, "%s registered successfully\n", mfbi->id);

	वापस 0;
पूर्ण

अटल व्योम uninstall_fb(काष्ठा fb_info *info)
अणु
	काष्ठा mfb_info *mfbi = info->par;

	अगर (!mfbi->रेजिस्टरed)
		वापस;

	unरेजिस्टर_framebuffer(info);
	unmap_video_memory(info);
	fb_dealloc_cmap(&info->cmap);

	mfbi->रेजिस्टरed = 0;
पूर्ण

अटल irqवापस_t fsl_diu_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा diu __iomem *hw = dev_id;
	uपूर्णांक32_t status = in_be32(&hw->पूर्णांक_status);

	अगर (status) अणु
		/* This is the workaround क्रम underrun */
		अगर (status & INT_UNDRUN) अणु
			out_be32(&hw->diu_mode, 0);
			udelay(1);
			out_be32(&hw->diu_mode, 1);
		पूर्ण
#अगर defined(CONFIG_NOT_COHERENT_CACHE)
		अन्यथा अगर (status & INT_VSYNC) अणु
			अचिन्हित पूर्णांक i;

			क्रम (i = 0; i < coherence_data_size;
				i += d_cache_line_size)
				__यंत्र__ __अस्थिर__ (
					"dcbz 0, %[input]"
				::[input]"r"(&coherence_data[i]));
		पूर्ण
#पूर्ण_अगर
		वापस IRQ_HANDLED;
	पूर्ण
	वापस IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_PM
/*
 * Power management hooks. Note that we won't be called from IRQ context,
 * unlike the blank functions above, so we may sleep.
 */
अटल पूर्णांक fsl_diu_suspend(काष्ठा platक्रमm_device *ofdev, pm_message_t state)
अणु
	काष्ठा fsl_diu_data *data;

	data = dev_get_drvdata(&ofdev->dev);
	disable_lcdc(data->fsl_diu_info);

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_diu_resume(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा fsl_diu_data *data;
	अचिन्हित पूर्णांक i;

	data = dev_get_drvdata(&ofdev->dev);

	fsl_diu_enable_पूर्णांकerrupts(data);
	update_lcdc(data->fsl_diu_info);
	क्रम (i = 0; i < NUM_AOIS; i++) अणु
		अगर (data->mfb[i].count)
			fsl_diu_enable_panel(&data->fsl_diu_info[i]);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा fsl_diu_suspend शून्य
#घोषणा fsl_diu_resume शून्य
#पूर्ण_अगर				/* CONFIG_PM */

अटल sमाप_प्रकार store_monitor(काष्ठा device *device,
	काष्ठा device_attribute *attr, स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	क्रमागत fsl_diu_monitor_port old_monitor_port;
	काष्ठा fsl_diu_data *data =
		container_of(attr, काष्ठा fsl_diu_data, dev_attr);

	old_monitor_port = data->monitor_port;
	data->monitor_port = fsl_diu_name_to_port(buf);

	अगर (old_monitor_port != data->monitor_port) अणु
		/* All AOIs need adjust pixel क्रमmat
		 * fsl_diu_set_par only change the pixsel क्रमmat here
		 * unlikely to fail. */
		अचिन्हित पूर्णांक i;

		क्रम (i=0; i < NUM_AOIS; i++)
			fsl_diu_set_par(&data->fsl_diu_info[i]);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार show_monitor(काष्ठा device *device,
	काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा fsl_diu_data *data =
		container_of(attr, काष्ठा fsl_diu_data, dev_attr);

	चयन (data->monitor_port) अणु
	हाल FSL_DIU_PORT_DVI:
		वापस प्र_लिखो(buf, "DVI\n");
	हाल FSL_DIU_PORT_LVDS:
		वापस प्र_लिखो(buf, "Single-link LVDS\n");
	हाल FSL_DIU_PORT_DLVDS:
		वापस प्र_लिखो(buf, "Dual-link LVDS\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fsl_diu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा mfb_info *mfbi;
	काष्ठा fsl_diu_data *data;
	dma_addr_t dma_addr; /* DMA addr of fsl_diu_data काष्ठा */
	स्थिर व्योम *prop;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	data = dmam_alloc_coherent(&pdev->dev, माप(काष्ठा fsl_diu_data),
				   &dma_addr, GFP_DMA | __GFP_ZERO);
	अगर (!data)
		वापस -ENOMEM;
	data->dma_addr = dma_addr;

	/*
	 * dma_alloc_coherent() uses a page allocator, so the address is
	 * always page-aligned.  We need the memory to be 32-byte aligned,
	 * so that's good.  However, अगर one day the allocator changes, we
	 * need to catch that.  It's not worth the efक्रमt to handle unaligned
	 * alloctions now because it's highly unlikely to ever be a problem.
	 */
	अगर ((अचिन्हित दीर्घ)data & 31) अणु
		dev_err(&pdev->dev, "misaligned allocation");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	spin_lock_init(&data->reg_lock);

	क्रम (i = 0; i < NUM_AOIS; i++) अणु
		काष्ठा fb_info *info = &data->fsl_diu_info[i];

		info->device = &pdev->dev;
		info->par = &data->mfb[i];

		/*
		 * We store the physical address of the AD in the reserved
		 * 'paddr' field of the AD itself.
		 */
		data->ad[i].paddr = DMA_ADDR(data, ad[i]);

		info->fix.smem_start = 0;

		/* Initialize the AOI data काष्ठाure */
		mfbi = info->par;
		स_नकल(mfbi, &mfb_ढाँचा[i], माप(काष्ठा mfb_info));
		mfbi->parent = data;
		mfbi->ad = &data->ad[i];
	पूर्ण

	/* Get the EDID data from the device tree, अगर present */
	prop = of_get_property(np, "edid", &ret);
	अगर (prop && ret == EDID_LENGTH) अणु
		स_नकल(data->edid_data, prop, EDID_LENGTH);
		data->has_edid = true;
	पूर्ण

	data->diu_reg = of_iomap(np, 0);
	अगर (!data->diu_reg) अणु
		dev_err(&pdev->dev, "cannot map DIU registers\n");
		ret = -EFAULT;
		जाओ error;
	पूर्ण

	/* Get the IRQ of the DIU */
	data->irq = irq_of_parse_and_map(np, 0);

	अगर (!data->irq) अणु
		dev_err(&pdev->dev, "could not get DIU IRQ\n");
		ret = -EINVAL;
		जाओ error;
	पूर्ण
	data->monitor_port = monitor_port;

	/* Initialize the dummy Area Descriptor */
	data->dummy_ad.addr = cpu_to_le32(DMA_ADDR(data, dummy_aoi));
	data->dummy_ad.pix_fmt = 0x88882317;
	data->dummy_ad.src_size_g_alpha = cpu_to_le32((4 << 12) | 4);
	data->dummy_ad.aoi_size = cpu_to_le32((4 << 16) |  2);
	data->dummy_ad.offset_xyi = 0;
	data->dummy_ad.offset_xyd = 0;
	data->dummy_ad.next_ad = 0;
	data->dummy_ad.paddr = DMA_ADDR(data, dummy_ad);

	/*
	 * Let DIU जारी to display splash screen अगर it was pre-initialized
	 * by the bootloader; otherwise, clear the display.
	 */
	अगर (in_be32(&data->diu_reg->diu_mode) == MFB_MODE0)
		out_be32(&data->diu_reg->desc[0], 0);

	out_be32(&data->diu_reg->desc[1], data->dummy_ad.paddr);
	out_be32(&data->diu_reg->desc[2], data->dummy_ad.paddr);

	/*
	 * Older versions of U-Boot leave पूर्णांकerrupts enabled, so disable
	 * all of them and clear the status रेजिस्टर.
	 */
	out_be32(&data->diu_reg->पूर्णांक_mask, 0xffffffff);
	in_be32(&data->diu_reg->पूर्णांक_status);

	ret = request_irq(data->irq, fsl_diu_isr, 0, "fsl-diu-fb",
			  data->diu_reg);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not claim irq\n");
		जाओ error;
	पूर्ण

	क्रम (i = 0; i < NUM_AOIS; i++) अणु
		ret = install_fb(&data->fsl_diu_info[i]);
		अगर (ret) अणु
			dev_err(&pdev->dev, "could not register fb %d\n", i);
			मुक्त_irq(data->irq, data->diu_reg);
			जाओ error;
		पूर्ण
	पूर्ण

	sysfs_attr_init(&data->dev_attr.attr);
	data->dev_attr.attr.name = "monitor";
	data->dev_attr.attr.mode = S_IRUGO|S_IWUSR;
	data->dev_attr.show = show_monitor;
	data->dev_attr.store = store_monitor;
	ret = device_create_file(&pdev->dev, &data->dev_attr);
	अगर (ret) अणु
		dev_err(&pdev->dev, "could not create sysfs file %s\n",
			data->dev_attr.attr.name);
	पूर्ण

	dev_set_drvdata(&pdev->dev, data);
	वापस 0;

error:
	क्रम (i = 0; i < NUM_AOIS; i++)
		uninstall_fb(&data->fsl_diu_info[i]);

	iounmap(data->diu_reg);

	वापस ret;
पूर्ण

अटल पूर्णांक fsl_diu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsl_diu_data *data;
	पूर्णांक i;

	data = dev_get_drvdata(&pdev->dev);
	disable_lcdc(&data->fsl_diu_info[0]);

	मुक्त_irq(data->irq, data->diu_reg);

	क्रम (i = 0; i < NUM_AOIS; i++)
		uninstall_fb(&data->fsl_diu_info[i]);

	iounmap(data->diu_reg);

	वापस 0;
पूर्ण

#अगर_अघोषित MODULE
अटल पूर्णांक __init fsl_diu_setup(अक्षर *options)
अणु
	अक्षर *opt;
	अचिन्हित दीर्घ val;

	अगर (!options || !*options)
		वापस 0;

	जबतक ((opt = strsep(&options, ",")) != शून्य) अणु
		अगर (!*opt)
			जारी;
		अगर (!म_भेदन(opt, "monitor=", 8)) अणु
			monitor_port = fsl_diu_name_to_port(opt + 8);
		पूर्ण अन्यथा अगर (!म_भेदन(opt, "bpp=", 4)) अणु
			अगर (!kम_से_अदीर्घ(opt + 4, 10, &val))
				शेष_bpp = val;
		पूर्ण अन्यथा
			fb_mode = opt;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा of_device_id fsl_diu_match[] = अणु
#अगर_घोषित CONFIG_PPC_MPC512x
	अणु
		.compatible = "fsl,mpc5121-diu",
	पूर्ण,
#पूर्ण_अगर
	अणु
		.compatible = "fsl,diu",
	पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, fsl_diu_match);

अटल काष्ठा platक्रमm_driver fsl_diu_driver = अणु
	.driver = अणु
		.name = "fsl-diu-fb",
		.of_match_table = fsl_diu_match,
	पूर्ण,
	.probe  	= fsl_diu_probe,
	.हटाओ 	= fsl_diu_हटाओ,
	.suspend	= fsl_diu_suspend,
	.resume		= fsl_diu_resume,
पूर्ण;

अटल पूर्णांक __init fsl_diu_init(व्योम)
अणु
#अगर_घोषित CONFIG_NOT_COHERENT_CACHE
	काष्ठा device_node *np;
	स्थिर u32 *prop;
#पूर्ण_अगर
	पूर्णांक ret;
#अगर_अघोषित MODULE
	अक्षर *option;

	/*
	 * For kernel boot options (in 'video=xxxfb:<options>' क्रमmat)
	 */
	अगर (fb_get_options("fslfb", &option))
		वापस -ENODEV;
	fsl_diu_setup(option);
#अन्यथा
	monitor_port = fsl_diu_name_to_port(monitor_string);
#पूर्ण_अगर

	/*
	 * Must to verअगरy set_pixel_घड़ी. If not implement on platक्रमm,
	 * then that means that there is no platक्रमm support क्रम the DIU.
	 */
	अगर (!diu_ops.set_pixel_घड़ी)
		वापस -ENODEV;

	pr_info("Freescale Display Interface Unit (DIU) framebuffer driver\n");

#अगर_घोषित CONFIG_NOT_COHERENT_CACHE
	np = of_get_cpu_node(0, शून्य);
	अगर (!np) अणु
		pr_err("fsl-diu-fb: can't find 'cpu' device node\n");
		वापस -ENODEV;
	पूर्ण

	prop = of_get_property(np, "d-cache-size", शून्य);
	अगर (prop == शून्य) अणु
		pr_err("fsl-diu-fb: missing 'd-cache-size' property' "
		       "in 'cpu' node\n");
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण

	/*
	 * Freescale PLRU requires 13/8 बार the cache size to करो a proper
	 * displacement flush
	 */
	coherence_data_size = be32_to_cpup(prop) * 13;
	coherence_data_size /= 8;

	pr_debug("fsl-diu-fb: coherence data size is %zu bytes\n",
		 coherence_data_size);

	prop = of_get_property(np, "d-cache-line-size", शून्य);
	अगर (prop == शून्य) अणु
		pr_err("fsl-diu-fb: missing 'd-cache-line-size' property' "
		       "in 'cpu' node\n");
		of_node_put(np);
		वापस -ENODEV;
	पूर्ण
	d_cache_line_size = be32_to_cpup(prop);

	pr_debug("fsl-diu-fb: cache lines size is %u bytes\n",
		 d_cache_line_size);

	of_node_put(np);
	coherence_data = vदो_स्मृति(coherence_data_size);
	अगर (!coherence_data)
		वापस -ENOMEM;
#पूर्ण_अगर

	ret = platक्रमm_driver_रेजिस्टर(&fsl_diu_driver);
	अगर (ret) अणु
		pr_err("fsl-diu-fb: failed to register platform driver\n");
#अगर defined(CONFIG_NOT_COHERENT_CACHE)
		vमुक्त(coherence_data);
#पूर्ण_अगर
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास fsl_diu_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&fsl_diu_driver);
#अगर defined(CONFIG_NOT_COHERENT_CACHE)
	vमुक्त(coherence_data);
#पूर्ण_अगर
पूर्ण

module_init(fsl_diu_init);
module_निकास(fsl_diu_निकास);

MODULE_AUTHOR("York Sun <yorksun@freescale.com>");
MODULE_DESCRIPTION("Freescale DIU framebuffer driver");
MODULE_LICENSE("GPL");

module_param_named(mode, fb_mode, अक्षरp, 0);
MODULE_PARM_DESC(mode,
	"Specify resolution as \"<xres>x<yres>[-<bpp>][@<refresh>]\" ");
module_param_named(bpp, शेष_bpp, uदीर्घ, 0);
MODULE_PARM_DESC(bpp, "Specify bit-per-pixel if not specified in 'mode'");
module_param_named(monitor, monitor_string, अक्षरp, 0);
MODULE_PARM_DESC(monitor, "Specify the monitor port "
	"(\"dvi\", \"lvds\", or \"dlvds\") if supported by the platform");

