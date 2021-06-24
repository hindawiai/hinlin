<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NV04_DISPLAY_H__
#घोषणा __NV04_DISPLAY_H__
#समावेश <subdev/मूलप्रण.स>
#समावेश <subdev/bios/pll.h>

#समावेश "nouveau_display.h"

काष्ठा nouveau_encoder;

क्रमागत nv04_fp_display_regs अणु
	FP_DISPLAY_END,
	FP_TOTAL,
	FP_CRTC,
	FP_SYNC_START,
	FP_SYNC_END,
	FP_VALID_START,
	FP_VALID_END
पूर्ण;

काष्ठा nv04_crtc_reg अणु
	अचिन्हित अक्षर MiscOutReg;
	uपूर्णांक8_t CRTC[0xa0];
	uपूर्णांक8_t CR58[0x10];
	uपूर्णांक8_t Sequencer[5];
	uपूर्णांक8_t Graphics[9];
	uपूर्णांक8_t Attribute[21];
	अचिन्हित अक्षर DAC[768];

	/* PCRTC regs */
	uपूर्णांक32_t fb_start;
	uपूर्णांक32_t crtc_cfg;
	uपूर्णांक32_t cursor_cfg;
	uपूर्णांक32_t gpio_ext;
	uपूर्णांक32_t crtc_830;
	uपूर्णांक32_t crtc_834;
	uपूर्णांक32_t crtc_850;
	uपूर्णांक32_t crtc_eng_ctrl;

	/* PRAMDAC regs */
	uपूर्णांक32_t nv10_cursync;
	काष्ठा nvkm_pll_vals pllvals;
	uपूर्णांक32_t ramdac_gen_ctrl;
	uपूर्णांक32_t ramdac_630;
	uपूर्णांक32_t ramdac_634;
	uपूर्णांक32_t tv_setup;
	uपूर्णांक32_t tv_vtotal;
	uपूर्णांक32_t tv_vskew;
	uपूर्णांक32_t tv_vsync_delay;
	uपूर्णांक32_t tv_htotal;
	uपूर्णांक32_t tv_hskew;
	uपूर्णांक32_t tv_hsync_delay;
	uपूर्णांक32_t tv_hsync_delay2;
	uपूर्णांक32_t fp_horiz_regs[7];
	uपूर्णांक32_t fp_vert_regs[7];
	uपूर्णांक32_t dither;
	uपूर्णांक32_t fp_control;
	uपूर्णांक32_t dither_regs[6];
	uपूर्णांक32_t fp_debug_0;
	uपूर्णांक32_t fp_debug_1;
	uपूर्णांक32_t fp_debug_2;
	uपूर्णांक32_t fp_margin_color;
	uपूर्णांक32_t ramdac_8c0;
	uपूर्णांक32_t ramdac_a20;
	uपूर्णांक32_t ramdac_a24;
	uपूर्णांक32_t ramdac_a34;
	uपूर्णांक32_t ctv_regs[38];
पूर्ण;

काष्ठा nv04_output_reg अणु
	uपूर्णांक32_t output;
	पूर्णांक head;
पूर्ण;

काष्ठा nv04_mode_state अणु
	काष्ठा nv04_crtc_reg crtc_reg[2];
	uपूर्णांक32_t pllsel;
	uपूर्णांक32_t sel_clk;
पूर्ण;

काष्ठा nv04_display अणु
	काष्ठा nv04_mode_state mode_reg;
	काष्ठा nv04_mode_state saved_reg;
	uपूर्णांक32_t saved_vga_font[4][16384];
	uपूर्णांक32_t dac_users[4];
	काष्ठा nouveau_bo *image[2];
	काष्ठा nvअगर_notअगरy flip;
पूर्ण;

अटल अंतरभूत काष्ठा nv04_display *
nv04_display(काष्ठा drm_device *dev)
अणु
	वापस nouveau_display(dev)->priv;
पूर्ण

/* nv04_display.c */
पूर्णांक nv04_display_create(काष्ठा drm_device *);
काष्ठा nouveau_connector *
nv04_encoder_get_connector(काष्ठा nouveau_encoder *nv_encoder);

/* nv04_crtc.c */
पूर्णांक nv04_crtc_create(काष्ठा drm_device *, पूर्णांक index);

/* nv04_dac.c */
पूर्णांक nv04_dac_create(काष्ठा drm_connector *, काष्ठा dcb_output *);
uपूर्णांक32_t nv17_dac_sample_load(काष्ठा drm_encoder *encoder);
पूर्णांक nv04_dac_output_offset(काष्ठा drm_encoder *encoder);
व्योम nv04_dac_update_dacclk(काष्ठा drm_encoder *encoder, bool enable);
bool nv04_dac_in_use(काष्ठा drm_encoder *encoder);

/* nv04_dfp.c */
पूर्णांक nv04_dfp_create(काष्ठा drm_connector *, काष्ठा dcb_output *);
पूर्णांक nv04_dfp_get_bound_head(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent);
व्योम nv04_dfp_bind_head(काष्ठा drm_device *dev, काष्ठा dcb_output *dcbent,
			       पूर्णांक head, bool dl);
व्योम nv04_dfp_disable(काष्ठा drm_device *dev, पूर्णांक head);
व्योम nv04_dfp_update_fp_control(काष्ठा drm_encoder *encoder, पूर्णांक mode);

/* nv04_tv.c */
पूर्णांक nv04_tv_identअगरy(काष्ठा drm_device *dev, पूर्णांक i2c_index);
पूर्णांक nv04_tv_create(काष्ठा drm_connector *, काष्ठा dcb_output *);

/* nv17_tv.c */
पूर्णांक nv17_tv_create(काष्ठा drm_connector *, काष्ठा dcb_output *);

/* overlay.c */
व्योम nouveau_overlay_init(काष्ठा drm_device *dev);

अटल अंतरभूत bool
nv_two_heads(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	स्थिर पूर्णांक impl = to_pci_dev(dev->dev)->device & 0x0ff0;

	अगर (drm->client.device.info.family >= NV_DEVICE_INFO_V0_CELSIUS && impl != 0x0100 &&
	    impl != 0x0150 && impl != 0x01a0 && impl != 0x0200)
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool
nv_gf4_disp_arch(काष्ठा drm_device *dev)
अणु
	वापस nv_two_heads(dev) && (to_pci_dev(dev->dev)->device & 0x0ff0) != 0x0110;
पूर्ण

अटल अंतरभूत bool
nv_two_reg_pll(काष्ठा drm_device *dev)
अणु
	काष्ठा nouveau_drm *drm = nouveau_drm(dev);
	स्थिर पूर्णांक impl = to_pci_dev(dev->dev)->device & 0x0ff0;

	अगर (impl == 0x0310 || impl == 0x0340 || drm->client.device.info.family >= NV_DEVICE_INFO_V0_CURIE)
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool
nv_match_device(काष्ठा drm_device *dev, अचिन्हित device,
		अचिन्हित sub_venकरोr, अचिन्हित sub_device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev->dev);

	वापस pdev->device == device &&
		pdev->subप्रणाली_venकरोr == sub_venकरोr &&
		pdev->subप्रणाली_device == sub_device;
पूर्ण

#समावेश <subdev/bios/init.h>

अटल अंतरभूत व्योम
nouveau_bios_run_init_table(काष्ठा drm_device *dev, u16 table,
			    काष्ठा dcb_output *outp, पूर्णांक crtc)
अणु
	nvbios_init(&nvxx_bios(&nouveau_drm(dev)->client.device)->subdev, table,
		init.outp = outp;
		init.head = crtc;
	);
पूर्ण

पूर्णांक nv04_flip_complete(काष्ठा nvअगर_notअगरy *);
#पूर्ण_अगर
