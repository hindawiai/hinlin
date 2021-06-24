<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SH_MOBILE_LCDCFB_H
#घोषणा SH_MOBILE_LCDCFB_H

#समावेश <linux/completion.h>
#समावेश <linux/fb.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>

/* per-channel रेजिस्टरs */
क्रमागत अणु LDDCKPAT1R, LDDCKPAT2R, LDMT1R, LDMT2R, LDMT3R, LDDFR, LDSM1R,
       LDSM2R, LDSA1R, LDSA2R, LDMLSR, LDHCNR, LDHSYNR, LDVLNR, LDVSYNR, LDPMR,
       LDHAJR,
       NR_CH_REGS पूर्ण;

#घोषणा PALETTE_NR 16

काष्ठा backlight_device;
काष्ठा fb_info;
काष्ठा module;
काष्ठा sh_mobile_lcdc_chan;
काष्ठा sh_mobile_lcdc_entity;
काष्ठा sh_mobile_lcdc_क्रमmat_info;
काष्ठा sh_mobile_lcdc_priv;

#घोषणा SH_MOBILE_LCDC_DISPLAY_DISCONNECTED	0
#घोषणा SH_MOBILE_LCDC_DISPLAY_CONNECTED	1

काष्ठा sh_mobile_lcdc_entity_ops अणु
	/* Display */
	पूर्णांक (*display_on)(काष्ठा sh_mobile_lcdc_entity *entity);
	व्योम (*display_off)(काष्ठा sh_mobile_lcdc_entity *entity);
पूर्ण;

क्रमागत sh_mobile_lcdc_entity_event अणु
	SH_MOBILE_LCDC_EVENT_DISPLAY_CONNECT,
	SH_MOBILE_LCDC_EVENT_DISPLAY_DISCONNECT,
	SH_MOBILE_LCDC_EVENT_DISPLAY_MODE,
पूर्ण;

काष्ठा sh_mobile_lcdc_entity अणु
	काष्ठा module *owner;
	स्थिर काष्ठा sh_mobile_lcdc_entity_ops *ops;
	काष्ठा sh_mobile_lcdc_chan *lcdc;
	काष्ठा fb_videomode def_mode;
पूर्ण;

/*
 * काष्ठा sh_mobile_lcdc_chan - LCDC display channel
 *
 * @pan_y_offset: Panning linear offset in bytes (luma component)
 * @base_addr_y: Frame buffer viewport base address (luma component)
 * @base_addr_c: Frame buffer viewport base address (chroma component)
 * @pitch: Frame buffer line pitch
 */
काष्ठा sh_mobile_lcdc_chan अणु
	काष्ठा sh_mobile_lcdc_priv *lcdc;
	काष्ठा sh_mobile_lcdc_entity *tx_dev;
	स्थिर काष्ठा sh_mobile_lcdc_chan_cfg *cfg;

	अचिन्हित दीर्घ *reg_offs;
	अचिन्हित दीर्घ ldmt1r_value;
	अचिन्हित दीर्घ enabled; /* ME and SE in LDCNT2R */

	काष्ठा mutex खोलो_lock;		/* protects the use counter */
	पूर्णांक use_count;

	व्योम *fb_mem;
	अचिन्हित दीर्घ fb_size;

	dma_addr_t dma_handle;
	अचिन्हित दीर्घ pan_y_offset;

	अचिन्हित दीर्घ frame_end;
	रुको_queue_head_t frame_end_रुको;
	काष्ठा completion vsync_completion;

	स्थिर काष्ठा sh_mobile_lcdc_क्रमmat_info *क्रमmat;
	u32 colorspace;
	अचिन्हित पूर्णांक xres;
	अचिन्हित पूर्णांक xres_भव;
	अचिन्हित पूर्णांक yres;
	अचिन्हित पूर्णांक yres_भव;
	अचिन्हित पूर्णांक pitch;

	अचिन्हित दीर्घ base_addr_y;
	अचिन्हित दीर्घ base_addr_c;
	अचिन्हित पूर्णांक line_size;

	/* Backlight */
	काष्ठा backlight_device *bl;
	अचिन्हित पूर्णांक bl_brightness;

	/* FB */
	काष्ठा fb_info *info;
	u32 pseuकरो_palette[PALETTE_NR];
	काष्ठा अणु
		अचिन्हित पूर्णांक width;
		अचिन्हित पूर्णांक height;
		काष्ठा fb_videomode mode;
	पूर्ण display;
	काष्ठा fb_deferred_io defio;
	काष्ठा scatterlist *sglist;
	पूर्णांक blank_status;
पूर्ण;

#पूर्ण_अगर
