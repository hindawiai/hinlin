<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <linux/पन.स>
#समावेश <linux/console.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_vram_helper.h>
#समावेश <drm/drm_simple_kms_helper.h>

/* ---------------------------------------------------------------------- */

#घोषणा VBE_DISPI_IOPORT_INDEX           0x01CE
#घोषणा VBE_DISPI_IOPORT_DATA            0x01CF

#घोषणा VBE_DISPI_INDEX_ID               0x0
#घोषणा VBE_DISPI_INDEX_XRES             0x1
#घोषणा VBE_DISPI_INDEX_YRES             0x2
#घोषणा VBE_DISPI_INDEX_BPP              0x3
#घोषणा VBE_DISPI_INDEX_ENABLE           0x4
#घोषणा VBE_DISPI_INDEX_BANK             0x5
#घोषणा VBE_DISPI_INDEX_VIRT_WIDTH       0x6
#घोषणा VBE_DISPI_INDEX_VIRT_HEIGHT      0x7
#घोषणा VBE_DISPI_INDEX_X_OFFSET         0x8
#घोषणा VBE_DISPI_INDEX_Y_OFFSET         0x9
#घोषणा VBE_DISPI_INDEX_VIDEO_MEMORY_64K 0xa

#घोषणा VBE_DISPI_ID0                    0xB0C0
#घोषणा VBE_DISPI_ID1                    0xB0C1
#घोषणा VBE_DISPI_ID2                    0xB0C2
#घोषणा VBE_DISPI_ID3                    0xB0C3
#घोषणा VBE_DISPI_ID4                    0xB0C4
#घोषणा VBE_DISPI_ID5                    0xB0C5

#घोषणा VBE_DISPI_DISABLED               0x00
#घोषणा VBE_DISPI_ENABLED                0x01
#घोषणा VBE_DISPI_GETCAPS                0x02
#घोषणा VBE_DISPI_8BIT_DAC               0x20
#घोषणा VBE_DISPI_LFB_ENABLED            0x40
#घोषणा VBE_DISPI_NOCLEARMEM             0x80

/* ---------------------------------------------------------------------- */

क्रमागत bochs_types अणु
	BOCHS_QEMU_STDVGA,
	BOCHS_UNKNOWN,
पूर्ण;

काष्ठा bochs_device अणु
	/* hw */
	व्योम __iomem   *mmio;
	पूर्णांक            ioports;
	व्योम __iomem   *fb_map;
	अचिन्हित दीर्घ  fb_base;
	अचिन्हित दीर्घ  fb_size;
	अचिन्हित दीर्घ  qext_size;

	/* mode */
	u16 xres;
	u16 yres;
	u16 yres_भव;
	u32 stride;
	u32 bpp;
	काष्ठा edid *edid;

	/* drm */
	काष्ठा drm_device *dev;
	काष्ठा drm_simple_display_pipe pipe;
	काष्ठा drm_connector connector;
पूर्ण;

/* ---------------------------------------------------------------------- */

/* bochs_hw.c */
पूर्णांक bochs_hw_init(काष्ठा drm_device *dev);
व्योम bochs_hw_fini(काष्ठा drm_device *dev);

व्योम bochs_hw_seपंचांगode(काष्ठा bochs_device *bochs,
		      काष्ठा drm_display_mode *mode);
व्योम bochs_hw_setक्रमmat(काष्ठा bochs_device *bochs,
			स्थिर काष्ठा drm_क्रमmat_info *क्रमmat);
व्योम bochs_hw_setbase(काष्ठा bochs_device *bochs,
		      पूर्णांक x, पूर्णांक y, पूर्णांक stride, u64 addr);
पूर्णांक bochs_hw_load_edid(काष्ठा bochs_device *bochs);

/* bochs_mm.c */
पूर्णांक bochs_mm_init(काष्ठा bochs_device *bochs);
व्योम bochs_mm_fini(काष्ठा bochs_device *bochs);

/* bochs_kms.c */
पूर्णांक bochs_kms_init(काष्ठा bochs_device *bochs);

/* bochs_fbdev.c */
बाह्य स्थिर काष्ठा drm_mode_config_funcs bochs_mode_funcs;
