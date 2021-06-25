<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * File: drivers/video/omap/omapfb.h
 *
 * Framebuffer driver क्रम TI OMAP boards
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 */

#अगर_अघोषित __OMAPFB_H
#घोषणा __OMAPFB_H

#समावेश <linux/fb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/omapfb.h>

#घोषणा OMAPFB_EVENT_READY	1
#घोषणा OMAPFB_EVENT_DISABLED	2

#घोषणा OMAP_LCDC_INV_VSYNC             0x0001
#घोषणा OMAP_LCDC_INV_HSYNC             0x0002
#घोषणा OMAP_LCDC_INV_PIX_CLOCK         0x0004
#घोषणा OMAP_LCDC_INV_OUTPUT_EN         0x0008
#घोषणा OMAP_LCDC_HSVS_RISING_EDGE      0x0010
#घोषणा OMAP_LCDC_HSVS_OPPOSITE         0x0020

#घोषणा OMAP_LCDC_SIGNAL_MASK		0x003f

#घोषणा OMAP_LCDC_PANEL_TFT		0x0100

#घोषणा OMAPFB_PLANE_XRES_MIN		8
#घोषणा OMAPFB_PLANE_YRES_MIN		8

काष्ठा omapfb_device;

#घोषणा OMAPFB_PLANE_NUM		1

काष्ठा omapfb_mem_region अणु
	u32		paddr;
	व्योम __iomem	*vaddr;
	अचिन्हित दीर्घ	size;
	u8		type;		/* OMAPFB_PLANE_MEM_* */
	क्रमागत omapfb_color_क्रमmat क्रमmat;/* OMAPFB_COLOR_* */
	अचिन्हित	क्रमmat_used:1;	/* Must be set when क्रमmat is set.
					 * Needed b/c of the badly chosen 0
					 * base क्रम OMAPFB_COLOR_* values
					 */
	अचिन्हित	alloc:1;	/* allocated by the driver */
	अचिन्हित	map:1;		/* kernel mapped by the driver */
पूर्ण;

काष्ठा omapfb_mem_desc अणु
	पूर्णांक				region_cnt;
	काष्ठा omapfb_mem_region	region[OMAPFB_PLANE_NUM];
पूर्ण;

काष्ठा lcd_panel अणु
	स्थिर अक्षर	*name;
	पूर्णांक		config;		/* TFT/STN, संकेत inversion */
	पूर्णांक		bpp;		/* Pixel क्रमmat in fb mem */
	पूर्णांक		data_lines;	/* Lines on LCD HW पूर्णांकerface */

	पूर्णांक		x_res, y_res;
	पूर्णांक		pixel_घड़ी;	/* In kHz */
	पूर्णांक		hsw;		/* Horizontal synchronization
					   pulse width */
	पूर्णांक		hfp;		/* Horizontal front porch */
	पूर्णांक		hbp;		/* Horizontal back porch */
	पूर्णांक		vsw;		/* Vertical synchronization
					   pulse width */
	पूर्णांक		vfp;		/* Vertical front porch */
	पूर्णांक		vbp;		/* Vertical back porch */
	पूर्णांक		acb;		/* ac-bias pin frequency */
	पूर्णांक		pcd;		/* pixel घड़ी भागider.
					   Obsolete use pixel_घड़ी instead */

	पूर्णांक		(*init)		(काष्ठा lcd_panel *panel,
					 काष्ठा omapfb_device *fbdev);
	व्योम		(*cleanup)	(काष्ठा lcd_panel *panel);
	पूर्णांक		(*enable)	(काष्ठा lcd_panel *panel);
	व्योम		(*disable)	(काष्ठा lcd_panel *panel);
	अचिन्हित दीर्घ	(*get_caps)	(काष्ठा lcd_panel *panel);
	पूर्णांक		(*set_bklight_level)(काष्ठा lcd_panel *panel,
					     अचिन्हित पूर्णांक level);
	अचिन्हित पूर्णांक	(*get_bklight_level)(काष्ठा lcd_panel *panel);
	अचिन्हित पूर्णांक	(*get_bklight_max)  (काष्ठा lcd_panel *panel);
	पूर्णांक		(*run_test)	(काष्ठा lcd_panel *panel, पूर्णांक test_num);
पूर्ण;

काष्ठा extअगर_timings अणु
	पूर्णांक cs_on_समय;
	पूर्णांक cs_off_समय;
	पूर्णांक we_on_समय;
	पूर्णांक we_off_समय;
	पूर्णांक re_on_समय;
	पूर्णांक re_off_समय;
	पूर्णांक we_cycle_समय;
	पूर्णांक re_cycle_समय;
	पूर्णांक cs_pulse_width;
	पूर्णांक access_समय;

	पूर्णांक clk_भाग;

	u32 tim[5];		/* set by extअगर->convert_timings */

	पूर्णांक converted;
पूर्ण;

काष्ठा lcd_ctrl_extअगर अणु
	पूर्णांक  (*init)		(काष्ठा omapfb_device *fbdev);
	व्योम (*cleanup)		(व्योम);
	व्योम (*get_clk_info)	(u32 *clk_period, u32 *max_clk_भाग);
	अचिन्हित दीर्घ (*get_max_tx_rate)(व्योम);
	पूर्णांक  (*convert_timings)	(काष्ठा extअगर_timings *timings);
	व्योम (*set_timings)	(स्थिर काष्ठा extअगर_timings *timings);
	व्योम (*set_bits_per_cycle)(पूर्णांक bpc);
	व्योम (*ग_लिखो_command)	(स्थिर व्योम *buf, अचिन्हित पूर्णांक len);
	व्योम (*पढ़ो_data)	(व्योम *buf, अचिन्हित पूर्णांक len);
	व्योम (*ग_लिखो_data)	(स्थिर व्योम *buf, अचिन्हित पूर्णांक len);
	व्योम (*transfer_area)	(पूर्णांक width, पूर्णांक height,
				 व्योम (callback)(व्योम *data), व्योम *data);
	पूर्णांक  (*setup_tearsync)	(अचिन्हित pin_cnt,
				 अचिन्हित hs_pulse_समय, अचिन्हित vs_pulse_समय,
				 पूर्णांक hs_pol_inv, पूर्णांक vs_pol_inv, पूर्णांक भाग);
	पूर्णांक  (*enable_tearsync) (पूर्णांक enable, अचिन्हित line);

	अचिन्हित दीर्घ		max_transmit_size;
पूर्ण;

काष्ठा omapfb_notअगरier_block अणु
	काष्ठा notअगरier_block	nb;
	व्योम			*data;
	पूर्णांक			plane_idx;
पूर्ण;

प्रकार पूर्णांक (*omapfb_notअगरier_callback_t)(काष्ठा notअगरier_block *,
					  अचिन्हित दीर्घ event,
					  व्योम *fbi);

काष्ठा lcd_ctrl अणु
	स्थिर अक्षर	*name;
	व्योम		*data;

	पूर्णांक		(*init)		  (काष्ठा omapfb_device *fbdev,
					   पूर्णांक ext_mode,
					   काष्ठा omapfb_mem_desc *req_md);
	व्योम		(*cleanup)	  (व्योम);
	व्योम		(*bind_client)	  (काष्ठा omapfb_notअगरier_block *nb);
	व्योम		(*get_caps)	  (पूर्णांक plane, काष्ठा omapfb_caps *caps);
	पूर्णांक		(*set_update_mode)(क्रमागत omapfb_update_mode mode);
	क्रमागत omapfb_update_mode (*get_update_mode)(व्योम);
	पूर्णांक		(*setup_plane)	  (पूर्णांक plane, पूर्णांक channel_out,
					   अचिन्हित दीर्घ offset,
					   पूर्णांक screen_width,
					   पूर्णांक pos_x, पूर्णांक pos_y, पूर्णांक width,
					   पूर्णांक height, पूर्णांक color_mode);
	पूर्णांक		(*set_rotate)	  (पूर्णांक angle);
	पूर्णांक		(*setup_mem)	  (पूर्णांक plane, माप_प्रकार size,
					   पूर्णांक mem_type, अचिन्हित दीर्घ *paddr);
	पूर्णांक		(*mmap)		  (काष्ठा fb_info *info,
					   काष्ठा vm_area_काष्ठा *vma);
	पूर्णांक		(*set_scale)	  (पूर्णांक plane,
					   पूर्णांक orig_width, पूर्णांक orig_height,
					   पूर्णांक out_width, पूर्णांक out_height);
	पूर्णांक		(*enable_plane)	  (पूर्णांक plane, पूर्णांक enable);
	पूर्णांक		(*update_winकरोw)  (काष्ठा fb_info *fbi,
					   काष्ठा omapfb_update_winकरोw *win,
					   व्योम (*callback)(व्योम *),
					   व्योम *callback_data);
	व्योम		(*sync)		  (व्योम);
	व्योम		(*suspend)	  (व्योम);
	व्योम		(*resume)	  (व्योम);
	पूर्णांक		(*run_test)	  (पूर्णांक test_num);
	पूर्णांक		(*setcolreg)	  (u_पूर्णांक regno, u16 red, u16 green,
					   u16 blue, u16 transp,
					   पूर्णांक update_hw_mem);
	पूर्णांक		(*set_color_key)  (काष्ठा omapfb_color_key *ck);
	पूर्णांक		(*get_color_key)  (काष्ठा omapfb_color_key *ck);
पूर्ण;

क्रमागत omapfb_state अणु
	OMAPFB_DISABLED		= 0,
	OMAPFB_SUSPENDED	= 99,
	OMAPFB_ACTIVE		= 100
पूर्ण;

काष्ठा omapfb_plane_काष्ठा अणु
	पूर्णांक				idx;
	काष्ठा omapfb_plane_info	info;
	क्रमागत omapfb_color_क्रमmat	color_mode;
	काष्ठा omapfb_device		*fbdev;
पूर्ण;

काष्ठा omapfb_device अणु
	पूर्णांक			state;
	पूर्णांक                     ext_lcdc;		/* Using बाह्यal
							   LCD controller */
	काष्ठा mutex		rqueue_mutex;

	पूर्णांक			palette_size;
	u32			pseuकरो_palette[17];

	काष्ठा lcd_panel	*panel;			/* LCD panel */
	स्थिर काष्ठा lcd_ctrl	*ctrl;			/* LCD controller */
	स्थिर काष्ठा lcd_ctrl	*पूर्णांक_ctrl;		/* पूर्णांकernal LCD ctrl */
	काष्ठा lcd_ctrl_extअगर	*ext_अगर;		/* LCD ctrl बाह्यal
							   पूर्णांकerface */
	काष्ठा device		*dev;
	काष्ठा fb_var_screeninfo	new_var;	/* क्रम mode changes */

	काष्ठा omapfb_mem_desc		mem_desc;
	काष्ठा fb_info			*fb_info[OMAPFB_PLANE_NUM];

	काष्ठा platक्रमm_device	*dssdev;	/* dummy dev क्रम घड़ीs */
पूर्ण;

बाह्य काष्ठा lcd_ctrl omap1_lcd_ctrl;

बाह्य व्योम omapfb_रेजिस्टर_panel(काष्ठा lcd_panel *panel);
बाह्य व्योम omapfb_ग_लिखो_first_pixel(काष्ठा omapfb_device *fbdev, u16 pixval);
बाह्य व्योम omapfb_notअगरy_clients(काष्ठा omapfb_device *fbdev,
				  अचिन्हित दीर्घ event);
बाह्य पूर्णांक  omapfb_रेजिस्टर_client(काष्ठा omapfb_notअगरier_block *nb,
				   omapfb_notअगरier_callback_t callback,
				   व्योम *callback_data);
बाह्य पूर्णांक  omapfb_unरेजिस्टर_client(काष्ठा omapfb_notअगरier_block *nb);
बाह्य पूर्णांक  omapfb_update_winकरोw_async(काष्ठा fb_info *fbi,
				       काष्ठा omapfb_update_winकरोw *win,
				       व्योम (*callback)(व्योम *),
				       व्योम *callback_data);

#पूर्ण_अगर /* __OMAPFB_H */
