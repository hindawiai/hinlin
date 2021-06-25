<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/include/video/mmp_disp.h
 * Header file क्रम Marvell MMP Display Controller
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors: Zhou Zhu <zzhu3@marvell.com>
 */

#अगर_अघोषित _MMP_DISP_H_
#घोषणा _MMP_DISP_H_
#समावेश <linux/kthपढ़ो.h>

क्रमागत अणु
	PIXFMT_UYVY = 0,
	PIXFMT_VYUY,
	PIXFMT_YUYV,
	PIXFMT_YUV422P,
	PIXFMT_YVU422P,
	PIXFMT_YUV420P,
	PIXFMT_YVU420P,
	PIXFMT_RGB565 = 0x100,
	PIXFMT_BGR565,
	PIXFMT_RGB1555,
	PIXFMT_BGR1555,
	PIXFMT_RGB888PACK,
	PIXFMT_BGR888PACK,
	PIXFMT_RGB888UNPACK,
	PIXFMT_BGR888UNPACK,
	PIXFMT_RGBA888,
	PIXFMT_BGRA888,
	PIXFMT_RGB666, /* क्रम output usage */
	PIXFMT_PSEUDOCOLOR = 0x200,
पूर्ण;

अटल अंतरभूत पूर्णांक pixfmt_to_stride(पूर्णांक pix_fmt)
अणु
	चयन (pix_fmt) अणु
	हाल PIXFMT_RGB565:
	हाल PIXFMT_BGR565:
	हाल PIXFMT_RGB1555:
	हाल PIXFMT_BGR1555:
	हाल PIXFMT_UYVY:
	हाल PIXFMT_VYUY:
	हाल PIXFMT_YUYV:
		वापस 2;
	हाल PIXFMT_RGB888UNPACK:
	हाल PIXFMT_BGR888UNPACK:
	हाल PIXFMT_RGBA888:
	हाल PIXFMT_BGRA888:
		वापस 4;
	हाल PIXFMT_RGB888PACK:
	हाल PIXFMT_BGR888PACK:
		वापस 3;
	हाल PIXFMT_YUV422P:
	हाल PIXFMT_YVU422P:
	हाल PIXFMT_YUV420P:
	हाल PIXFMT_YVU420P:
	हाल PIXFMT_PSEUDOCOLOR:
		वापस 1;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

/* parameters used by path/overlay */
/* overlay related para: win/addr */
काष्ठा mmp_win अणु
	/* position/size of winकरोw */
	u16	xsrc;
	u16	ysrc;
	u16	xdst;
	u16	ydst;
	u16	xpos;
	u16	ypos;
	u16	left_crop;
	u16	right_crop;
	u16	up_crop;
	u16	bottom_crop;
	पूर्णांक	pix_fmt;
	/*
	 * pitch[0]: graphics/video layer line length or y pitch
	 * pitch[1]/pitch[2]: video u/v pitch अगर non-zero
	 */
	u32	pitch[3];
पूर्ण;

काष्ठा mmp_addr अणु
	/* phys address */
	u32	phys[6];
पूर्ण;

/* path related para: mode */
काष्ठा mmp_mode अणु
	स्थिर अक्षर *name;
	u32 refresh;
	u32 xres;
	u32 yres;
	u32 left_margin;
	u32 right_margin;
	u32 upper_margin;
	u32 lower_margin;
	u32 hsync_len;
	u32 vsync_len;
	u32 hsync_invert;
	u32 vsync_invert;
	u32 invert_pixघड़ी;
	u32 pixघड़ी_freq;
	पूर्णांक pix_fmt_out;
पूर्ण;

/* मुख्य काष्ठाures */
काष्ठा mmp_path;
काष्ठा mmp_overlay;
काष्ठा mmp_panel;

/* status types */
क्रमागत अणु
	MMP_OFF = 0,
	MMP_ON,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *stat_name(पूर्णांक stat)
अणु
	चयन (stat) अणु
	हाल MMP_OFF:
		वापस "OFF";
	हाल MMP_ON:
		वापस "ON";
	शेष:
		वापस "UNKNOWNSTAT";
	पूर्ण
पूर्ण

काष्ठा mmp_overlay_ops अणु
	/* should be provided by driver */
	व्योम (*set_fetch)(काष्ठा mmp_overlay *overlay, पूर्णांक fetch_id);
	व्योम (*set_onoff)(काष्ठा mmp_overlay *overlay, पूर्णांक status);
	व्योम (*set_win)(काष्ठा mmp_overlay *overlay, काष्ठा mmp_win *win);
	पूर्णांक (*set_addr)(काष्ठा mmp_overlay *overlay, काष्ठा mmp_addr *addr);
पूर्ण;

/* overlay describes a z-order indexed slot in each path. */
काष्ठा mmp_overlay अणु
	पूर्णांक id;
	स्थिर अक्षर *name;
	काष्ठा mmp_path *path;

	/* overlay info: निजी data */
	पूर्णांक dmafetch_id;
	काष्ठा mmp_addr addr;
	काष्ठा mmp_win win;

	/* state */
	पूर्णांक खोलो_count;
	पूर्णांक status;
	काष्ठा mutex access_ok;

	काष्ठा mmp_overlay_ops *ops;
पूर्ण;

/* panel type */
क्रमागत अणु
	PANELTYPE_ACTIVE = 0,
	PANELTYPE_SMART,
	PANELTYPE_TV,
	PANELTYPE_DSI_CMD,
	PANELTYPE_DSI_VIDEO,
पूर्ण;

काष्ठा mmp_panel अणु
	/* use node to रेजिस्टर to list */
	काष्ठा list_head node;
	स्थिर अक्षर *name;
	/* path name used to connect to proper path configed */
	स्थिर अक्षर *plat_path_name;
	काष्ठा device *dev;
	पूर्णांक panel_type;
	व्योम *plat_data;
	पूर्णांक (*get_modelist)(काष्ठा mmp_panel *panel,
			काष्ठा mmp_mode **modelist);
	व्योम (*set_mode)(काष्ठा mmp_panel *panel,
			काष्ठा mmp_mode *mode);
	व्योम (*set_onoff)(काष्ठा mmp_panel *panel,
			पूर्णांक status);
पूर्ण;

काष्ठा mmp_path_ops अणु
	पूर्णांक (*check_status)(काष्ठा mmp_path *path);
	काष्ठा mmp_overlay *(*get_overlay)(काष्ठा mmp_path *path,
			पूर्णांक overlay_id);
	पूर्णांक (*get_modelist)(काष्ठा mmp_path *path,
			काष्ठा mmp_mode **modelist);

	/* follow ops should be provided by driver */
	व्योम (*set_mode)(काष्ठा mmp_path *path, काष्ठा mmp_mode *mode);
	व्योम (*set_onoff)(काष्ठा mmp_path *path, पूर्णांक status);
	/* toकरो: add query */
पूर्ण;

/* path output types */
क्रमागत अणु
	PATH_OUT_PARALLEL,
	PATH_OUT_DSI,
	PATH_OUT_HDMI,
पूर्ण;

/* path is मुख्य part of mmp-disp */
काष्ठा mmp_path अणु
	/* use node to रेजिस्टर to list */
	काष्ठा list_head node;

	/* init data */
	काष्ठा device *dev;

	पूर्णांक id;
	स्थिर अक्षर *name;
	पूर्णांक output_type;
	काष्ठा mmp_panel *panel;
	व्योम *plat_data;

	/* dynamic use */
	काष्ठा mmp_mode mode;

	/* state */
	पूर्णांक खोलो_count;
	पूर्णांक status;
	काष्ठा mutex access_ok;

	काष्ठा mmp_path_ops ops;

	/* layers */
	पूर्णांक overlay_num;
	काष्ठा mmp_overlay overlays[];
पूर्ण;

बाह्य काष्ठा mmp_path *mmp_get_path(स्थिर अक्षर *name);
अटल अंतरभूत व्योम mmp_path_set_mode(काष्ठा mmp_path *path,
		काष्ठा mmp_mode *mode)
अणु
	अगर (path)
		path->ops.set_mode(path, mode);
पूर्ण
अटल अंतरभूत व्योम mmp_path_set_onoff(काष्ठा mmp_path *path, पूर्णांक status)
अणु
	अगर (path)
		path->ops.set_onoff(path, status);
पूर्ण
अटल अंतरभूत पूर्णांक mmp_path_get_modelist(काष्ठा mmp_path *path,
		काष्ठा mmp_mode **modelist)
अणु
	अगर (path)
		वापस path->ops.get_modelist(path, modelist);
	वापस 0;
पूर्ण
अटल अंतरभूत काष्ठा mmp_overlay *mmp_path_get_overlay(
		काष्ठा mmp_path *path, पूर्णांक overlay_id)
अणु
	अगर (path)
		वापस path->ops.get_overlay(path, overlay_id);
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम mmp_overlay_set_fetch(काष्ठा mmp_overlay *overlay,
		पूर्णांक fetch_id)
अणु
	अगर (overlay)
		overlay->ops->set_fetch(overlay, fetch_id);
पूर्ण
अटल अंतरभूत व्योम mmp_overlay_set_onoff(काष्ठा mmp_overlay *overlay,
		पूर्णांक status)
अणु
	अगर (overlay)
		overlay->ops->set_onoff(overlay, status);
पूर्ण
अटल अंतरभूत व्योम mmp_overlay_set_win(काष्ठा mmp_overlay *overlay,
		काष्ठा mmp_win *win)
अणु
	अगर (overlay)
		overlay->ops->set_win(overlay, win);
पूर्ण
अटल अंतरभूत पूर्णांक mmp_overlay_set_addr(काष्ठा mmp_overlay *overlay,
		काष्ठा mmp_addr *addr)
अणु
	अगर (overlay)
		वापस overlay->ops->set_addr(overlay, addr);
	वापस 0;
पूर्ण

/*
 * driver data is set from each detailed ctrl driver क्रम path usage
 * it defined a common पूर्णांकerface that plat driver need to implement
 */
काष्ठा mmp_path_info अणु
	/* driver data, set when registed*/
	स्थिर अक्षर *name;
	काष्ठा device *dev;
	पूर्णांक id;
	पूर्णांक output_type;
	पूर्णांक overlay_num;
	व्योम (*set_mode)(काष्ठा mmp_path *path, काष्ठा mmp_mode *mode);
	व्योम (*set_onoff)(काष्ठा mmp_path *path, पूर्णांक status);
	काष्ठा mmp_overlay_ops *overlay_ops;
	व्योम *plat_data;
पूर्ण;

बाह्य काष्ठा mmp_path *mmp_रेजिस्टर_path(
		काष्ठा mmp_path_info *info);
बाह्य व्योम mmp_unरेजिस्टर_path(काष्ठा mmp_path *path);
बाह्य व्योम mmp_रेजिस्टर_panel(काष्ठा mmp_panel *panel);
बाह्य व्योम mmp_unरेजिस्टर_panel(काष्ठा mmp_panel *panel);

/* defपूर्णांकions क्रम platक्रमm data */
/* पूर्णांकerface क्रम buffer driver */
काष्ठा mmp_buffer_driver_mach_info अणु
	स्थिर अक्षर	*name;
	स्थिर अक्षर	*path_name;
	पूर्णांक	overlay_id;
	पूर्णांक	dmafetch_id;
	पूर्णांक	शेष_pixfmt;
पूर्ण;

/* पूर्णांकerface क्रम controllers driver */
काष्ठा mmp_mach_path_config अणु
	स्थिर अक्षर *name;
	पूर्णांक overlay_num;
	पूर्णांक output_type;
	u32 path_config;
	u32 link_config;
	u32 dsi_rbswap;
पूर्ण;

काष्ठा mmp_mach_plat_info अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *clk_name;
	पूर्णांक path_num;
	काष्ठा mmp_mach_path_config *paths;
पूर्ण;

/* पूर्णांकerface क्रम panel drivers */
काष्ठा mmp_mach_panel_info अणु
	स्थिर अक्षर *name;
	व्योम (*plat_set_onoff)(पूर्णांक status);
	स्थिर अक्षर *plat_path_name;
पूर्ण;
#पूर्ण_अगर	/* _MMP_DISP_H_ */
