<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/drivers/video/omap2/omapfb.h
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#अगर_अघोषित __DRIVERS_VIDEO_OMAP2_OMAPFB_H__
#घोषणा __DRIVERS_VIDEO_OMAP2_OMAPFB_H__

#अगर_घोषित CONFIG_FB_OMAP2_DEBUG_SUPPORT
#घोषणा DEBUG
#पूर्ण_अगर

#समावेश <linux/rwsem.h>
#समावेश <linux/dma-mapping.h>

#समावेश <video/omapfb_dss.h>

#अगर_घोषित DEBUG
बाह्य bool omapfb_debug;
#घोषणा DBG(क्रमmat, ...) \
	करो अणु \
		अगर (omapfb_debug) \
			prपूर्णांकk(KERN_DEBUG "OMAPFB: " क्रमmat, ## __VA_ARGS__); \
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा DBG(क्रमmat, ...) no_prपूर्णांकk(क्रमmat, ## __VA_ARGS__)
#पूर्ण_अगर

#घोषणा FB2OFB(fb_info) ((काष्ठा omapfb_info *)(fb_info->par))

/* max number of overlays to which a framebuffer data can be direct */
#घोषणा OMAPFB_MAX_OVL_PER_FB 3

काष्ठा omapfb2_mem_region अणु
	पूर्णांक             id;
	अचिन्हित दीर्घ	attrs;
	व्योम		*token;
	dma_addr_t	dma_handle;
	u32		paddr;
	व्योम __iomem	*vaddr;
	काष्ठा vrfb	vrfb;
	अचिन्हित दीर्घ	size;
	u8		type;		/* OMAPFB_PLANE_MEM_* */
	bool		alloc;		/* allocated by the driver */
	bool		map;		/* kernel mapped by the driver */
	atomic_t	map_count;
	काष्ठा rw_semaphore lock;
	atomic_t	lock_count;
पूर्ण;

/* appended to fb_info */
काष्ठा omapfb_info अणु
	पूर्णांक id;
	काष्ठा omapfb2_mem_region *region;
	पूर्णांक num_overlays;
	काष्ठा omap_overlay *overlays[OMAPFB_MAX_OVL_PER_FB];
	काष्ठा omapfb2_device *fbdev;
	क्रमागत omap_dss_rotation_type rotation_type;
	u8 rotation[OMAPFB_MAX_OVL_PER_FB];
	bool mirror;
पूर्ण;

काष्ठा omapfb_display_data अणु
	काष्ठा omapfb2_device *fbdev;
	काष्ठा omap_dss_device *dssdev;
	u8 bpp_override;
	क्रमागत omapfb_update_mode update_mode;
	bool स्वतः_update_work_enabled;
	काष्ठा delayed_work स्वतः_update_work;
पूर्ण;

काष्ठा omapfb2_device अणु
	काष्ठा device *dev;
	काष्ठा mutex  mtx;

	u32 pseuकरो_palette[17];

	पूर्णांक state;

	अचिन्हित num_fbs;
	काष्ठा fb_info *fbs[10];
	काष्ठा omapfb2_mem_region regions[10];

	अचिन्हित num_displays;
	काष्ठा omapfb_display_data displays[10];
	अचिन्हित num_overlays;
	काष्ठा omap_overlay *overlays[10];
	अचिन्हित num_managers;
	काष्ठा omap_overlay_manager *managers[10];

	काष्ठा workqueue_काष्ठा *स्वतः_update_wq;
पूर्ण;

काष्ठा omapfb_colormode अणु
	क्रमागत omap_color_mode dssmode;
	u32 bits_per_pixel;
	u32 nonstd;
	काष्ठा fb_bitfield red;
	काष्ठा fb_bitfield green;
	काष्ठा fb_bitfield blue;
	काष्ठा fb_bitfield transp;
पूर्ण;

व्योम set_fb_fix(काष्ठा fb_info *fbi);
पूर्णांक check_fb_var(काष्ठा fb_info *fbi, काष्ठा fb_var_screeninfo *var);
पूर्णांक omapfb_पुनः_स्मृति_fbmem(काष्ठा fb_info *fbi, अचिन्हित दीर्घ size, पूर्णांक type);
पूर्णांक omapfb_apply_changes(काष्ठा fb_info *fbi, पूर्णांक init);

पूर्णांक omapfb_create_sysfs(काष्ठा omapfb2_device *fbdev);
व्योम omapfb_हटाओ_sysfs(काष्ठा omapfb2_device *fbdev);

पूर्णांक omapfb_ioctl(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

पूर्णांक dss_mode_to_fb_mode(क्रमागत omap_color_mode dssmode,
			काष्ठा fb_var_screeninfo *var);

पूर्णांक omapfb_setup_overlay(काष्ठा fb_info *fbi, काष्ठा omap_overlay *ovl,
		u16 posx, u16 posy, u16 outw, u16 outh);

व्योम omapfb_start_स्वतः_update(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *display);
व्योम omapfb_stop_स्वतः_update(काष्ठा omapfb2_device *fbdev,
		काष्ठा omap_dss_device *display);
पूर्णांक omapfb_get_update_mode(काष्ठा fb_info *fbi, क्रमागत omapfb_update_mode *mode);
पूर्णांक omapfb_set_update_mode(काष्ठा fb_info *fbi, क्रमागत omapfb_update_mode mode);

/* find the display connected to this fb, अगर any */
अटल अंतरभूत काष्ठा omap_dss_device *fb2display(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omap_overlay *ovl;

	/* XXX: वापसs the display connected to first attached overlay */

	अगर (ofbi->num_overlays == 0)
		वापस शून्य;

	ovl = ofbi->overlays[0];

	वापस ovl->get_device(ovl);
पूर्ण

अटल अंतरभूत काष्ठा omapfb_display_data *get_display_data(
		काष्ठा omapfb2_device *fbdev, काष्ठा omap_dss_device *dssdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < fbdev->num_displays; ++i)
		अगर (fbdev->displays[i].dssdev == dssdev)
			वापस &fbdev->displays[i];

	/* This should never happen */
	BUG();
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम omapfb_lock(काष्ठा omapfb2_device *fbdev)
अणु
	mutex_lock(&fbdev->mtx);
पूर्ण

अटल अंतरभूत व्योम omapfb_unlock(काष्ठा omapfb2_device *fbdev)
अणु
	mutex_unlock(&fbdev->mtx);
पूर्ण

अटल अंतरभूत पूर्णांक omapfb_overlay_enable(काष्ठा omap_overlay *ovl,
		पूर्णांक enable)
अणु
	अगर (enable)
		वापस ovl->enable(ovl);
	अन्यथा
		वापस ovl->disable(ovl);
पूर्ण

अटल अंतरभूत काष्ठा omapfb2_mem_region *
omapfb_get_mem_region(काष्ठा omapfb2_mem_region *rg)
अणु
	करोwn_पढ़ो_nested(&rg->lock, rg->id);
	atomic_inc(&rg->lock_count);
	वापस rg;
पूर्ण

अटल अंतरभूत व्योम omapfb_put_mem_region(काष्ठा omapfb2_mem_region *rg)
अणु
	atomic_dec(&rg->lock_count);
	up_पढ़ो(&rg->lock);
पूर्ण

#पूर्ण_अगर
