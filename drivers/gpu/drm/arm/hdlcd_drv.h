<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  ARM HDLCD Controller रेजिस्टर definition
 */

#अगर_अघोषित __HDLCD_DRV_H__
#घोषणा __HDLCD_DRV_H__

काष्ठा hdlcd_drm_निजी अणु
	व्योम __iomem			*mmio;
	काष्ठा clk			*clk;
	काष्ठा drm_crtc			crtc;
	काष्ठा drm_plane		*plane;
#अगर_घोषित CONFIG_DEBUG_FS
	atomic_t buffer_underrun_count;
	atomic_t bus_error_count;
	atomic_t vsync_count;
	atomic_t dma_end_count;
#पूर्ण_अगर
पूर्ण;

#घोषणा crtc_to_hdlcd_priv(x)	container_of(x, काष्ठा hdlcd_drm_निजी, crtc)

अटल अंतरभूत व्योम hdlcd_ग_लिखो(काष्ठा hdlcd_drm_निजी *hdlcd,
			       अचिन्हित पूर्णांक reg, u32 value)
अणु
	ग_लिखोl(value, hdlcd->mmio + reg);
पूर्ण

अटल अंतरभूत u32 hdlcd_पढ़ो(काष्ठा hdlcd_drm_निजी *hdlcd, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(hdlcd->mmio + reg);
पूर्ण

पूर्णांक hdlcd_setup_crtc(काष्ठा drm_device *dev);
व्योम hdlcd_set_scanout(काष्ठा hdlcd_drm_निजी *hdlcd);

#पूर्ण_अगर /* __HDLCD_DRV_H__ */
