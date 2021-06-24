<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only
 *
 * Copyright तऊ 2018-2020 Intel Corporation
 */

#अगर_अघोषित __KMB_DRV_H__
#घोषणा __KMB_DRV_H__

#समावेश <drm/drm_device.h>

#समावेश "kmb_plane.h"
#समावेश "kmb_regs.h"

#घोषणा KMB_MAX_WIDTH			1920 /*Max width in pixels */
#घोषणा KMB_MAX_HEIGHT			1080 /*Max height in pixels */
#घोषणा KMB_MIN_WIDTH                   1920 /*Max width in pixels */
#घोषणा KMB_MIN_HEIGHT                  1080 /*Max height in pixels */
#घोषणा KMB_LCD_DEFAULT_CLK		200000000
#घोषणा KMB_SYS_CLK_MHZ			500

#घोषणा ICAM_MMIO		0x3b100000
#घोषणा ICAM_LCD_OFFSET		0x1080
#घोषणा ICAM_MMIO_SIZE		0x2000

काष्ठा kmb_dsi;

काष्ठा kmb_घड़ी अणु
	काष्ठा clk *clk_lcd;
	काष्ठा clk *clk_pll0;
पूर्ण;

काष्ठा kmb_drm_निजी अणु
	काष्ठा drm_device		drm;
	काष्ठा kmb_dsi			*kmb_dsi;
	व्योम __iomem			*lcd_mmio;
	काष्ठा kmb_घड़ी		kmb_clk;
	काष्ठा drm_crtc			crtc;
	काष्ठा kmb_plane		*plane;
	काष्ठा drm_atomic_state		*state;
	spinlock_t			irq_lock;
	पूर्णांक				irq_lcd;
	पूर्णांक				sys_clk_mhz;
	काष्ठा layer_status		plane_status[KMB_MAX_PLANES];
	पूर्णांक				kmb_under_flow;
	पूर्णांक				kmb_flush_करोne;
	पूर्णांक				layer_no;
पूर्ण;

अटल अंतरभूत काष्ठा kmb_drm_निजी *to_kmb(स्थिर काष्ठा drm_device *dev)
अणु
	वापस container_of(dev, काष्ठा kmb_drm_निजी, drm);
पूर्ण

अटल अंतरभूत काष्ठा kmb_drm_निजी *crtc_to_kmb_priv(स्थिर काष्ठा drm_crtc *x)
अणु
	वापस container_of(x, काष्ठा kmb_drm_निजी, crtc);
पूर्ण

अटल अंतरभूत व्योम kmb_ग_लिखो_lcd(काष्ठा kmb_drm_निजी *dev_p,
				 अचिन्हित पूर्णांक reg, u32 value)
अणु
	ग_लिखोl(value, (dev_p->lcd_mmio + reg));
पूर्ण

अटल अंतरभूत u32 kmb_पढ़ो_lcd(काष्ठा kmb_drm_निजी *dev_p, अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(dev_p->lcd_mmio + reg);
पूर्ण

अटल अंतरभूत व्योम kmb_set_biपंचांगask_lcd(काष्ठा kmb_drm_निजी *dev_p,
				       अचिन्हित पूर्णांक reg, u32 mask)
अणु
	u32 reg_val = kmb_पढ़ो_lcd(dev_p, reg);

	kmb_ग_लिखो_lcd(dev_p, reg, (reg_val | mask));
पूर्ण

अटल अंतरभूत व्योम kmb_clr_biपंचांगask_lcd(काष्ठा kmb_drm_निजी *dev_p,
				       अचिन्हित पूर्णांक reg, u32 mask)
अणु
	u32 reg_val = kmb_पढ़ो_lcd(dev_p, reg);

	kmb_ग_लिखो_lcd(dev_p, reg, (reg_val & (~mask)));
पूर्ण

पूर्णांक kmb_setup_crtc(काष्ठा drm_device *dev);
व्योम kmb_set_scanout(काष्ठा kmb_drm_निजी *lcd);
#पूर्ण_अगर /* __KMB_DRV_H__ */
