<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Authors: Fabien Dessenne <fabien.dessenne@st.com> क्रम STMicroelectronics.
 */

#समावेश <linux/component.h>
#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/reset.h>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_fb_cma_helper.h>
#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_gem_cma_helper.h>

#समावेश "sti_compositor.h"
#समावेश "sti_drv.h"
#समावेश "sti_hqvdp_lut.h"
#समावेश "sti_plane.h"
#समावेश "sti_vtg.h"

/* Firmware name */
#घोषणा HQVDP_FMW_NAME          "hqvdp-stih407.bin"

/* Regs address */
#घोषणा HQVDP_DMEM              0x00000000               /* 0x00000000 */
#घोषणा HQVDP_PMEM              0x00040000               /* 0x00040000 */
#घोषणा HQVDP_RD_PLUG           0x000E0000               /* 0x000E0000 */
#घोषणा HQVDP_RD_PLUG_CONTROL   (HQVDP_RD_PLUG + 0x1000) /* 0x000E1000 */
#घोषणा HQVDP_RD_PLUG_PAGE_SIZE (HQVDP_RD_PLUG + 0x1004) /* 0x000E1004 */
#घोषणा HQVDP_RD_PLUG_MIN_OPC   (HQVDP_RD_PLUG + 0x1008) /* 0x000E1008 */
#घोषणा HQVDP_RD_PLUG_MAX_OPC   (HQVDP_RD_PLUG + 0x100C) /* 0x000E100C */
#घोषणा HQVDP_RD_PLUG_MAX_CHK   (HQVDP_RD_PLUG + 0x1010) /* 0x000E1010 */
#घोषणा HQVDP_RD_PLUG_MAX_MSG   (HQVDP_RD_PLUG + 0x1014) /* 0x000E1014 */
#घोषणा HQVDP_RD_PLUG_MIN_SPACE (HQVDP_RD_PLUG + 0x1018) /* 0x000E1018 */
#घोषणा HQVDP_WR_PLUG           0x000E2000               /* 0x000E2000 */
#घोषणा HQVDP_WR_PLUG_CONTROL   (HQVDP_WR_PLUG + 0x1000) /* 0x000E3000 */
#घोषणा HQVDP_WR_PLUG_PAGE_SIZE (HQVDP_WR_PLUG + 0x1004) /* 0x000E3004 */
#घोषणा HQVDP_WR_PLUG_MIN_OPC   (HQVDP_WR_PLUG + 0x1008) /* 0x000E3008 */
#घोषणा HQVDP_WR_PLUG_MAX_OPC   (HQVDP_WR_PLUG + 0x100C) /* 0x000E300C */
#घोषणा HQVDP_WR_PLUG_MAX_CHK   (HQVDP_WR_PLUG + 0x1010) /* 0x000E3010 */
#घोषणा HQVDP_WR_PLUG_MAX_MSG   (HQVDP_WR_PLUG + 0x1014) /* 0x000E3014 */
#घोषणा HQVDP_WR_PLUG_MIN_SPACE (HQVDP_WR_PLUG + 0x1018) /* 0x000E3018 */
#घोषणा HQVDP_MBX               0x000E4000               /* 0x000E4000 */
#घोषणा HQVDP_MBX_IRQ_TO_XP70   (HQVDP_MBX + 0x0000)     /* 0x000E4000 */
#घोषणा HQVDP_MBX_INFO_HOST     (HQVDP_MBX + 0x0004)     /* 0x000E4004 */
#घोषणा HQVDP_MBX_IRQ_TO_HOST   (HQVDP_MBX + 0x0008)     /* 0x000E4008 */
#घोषणा HQVDP_MBX_INFO_XP70     (HQVDP_MBX + 0x000C)     /* 0x000E400C */
#घोषणा HQVDP_MBX_SW_RESET_CTRL (HQVDP_MBX + 0x0010)     /* 0x000E4010 */
#घोषणा HQVDP_MBX_STARTUP_CTRL1 (HQVDP_MBX + 0x0014)     /* 0x000E4014 */
#घोषणा HQVDP_MBX_STARTUP_CTRL2 (HQVDP_MBX + 0x0018)     /* 0x000E4018 */
#घोषणा HQVDP_MBX_GP_STATUS     (HQVDP_MBX + 0x001C)     /* 0x000E401C */
#घोषणा HQVDP_MBX_NEXT_CMD      (HQVDP_MBX + 0x0020)     /* 0x000E4020 */
#घोषणा HQVDP_MBX_CURRENT_CMD   (HQVDP_MBX + 0x0024)     /* 0x000E4024 */
#घोषणा HQVDP_MBX_SOFT_VSYNC    (HQVDP_MBX + 0x0028)     /* 0x000E4028 */

/* Plugs config */
#घोषणा PLUG_CONTROL_ENABLE     0x00000001
#घोषणा PLUG_PAGE_SIZE_256      0x00000002
#घोषणा PLUG_MIN_OPC_8          0x00000003
#घोषणा PLUG_MAX_OPC_64         0x00000006
#घोषणा PLUG_MAX_CHK_2X         0x00000001
#घोषणा PLUG_MAX_MSG_1X         0x00000000
#घोषणा PLUG_MIN_SPACE_1        0x00000000

/* SW reset CTRL */
#घोषणा SW_RESET_CTRL_FULL      BIT(0)
#घोषणा SW_RESET_CTRL_CORE      BIT(1)

/* Startup ctrl 1 */
#घोषणा STARTUP_CTRL1_RST_DONE  BIT(0)
#घोषणा STARTUP_CTRL1_AUTH_IDLE BIT(2)

/* Startup ctrl 2 */
#घोषणा STARTUP_CTRL2_FETCH_EN  BIT(1)

/* Info xP70 */
#घोषणा INFO_XP70_FW_READY      BIT(15)
#घोषणा INFO_XP70_FW_PROCESSING BIT(14)
#घोषणा INFO_XP70_FW_INITQUEUES BIT(13)

/* SOFT_VSYNC */
#घोषणा SOFT_VSYNC_HW           0x00000000
#घोषणा SOFT_VSYNC_SW_CMD       0x00000001
#घोषणा SOFT_VSYNC_SW_CTRL_IRQ  0x00000003

/* Reset & boot poll config */
#घोषणा POLL_MAX_ATTEMPT        50
#घोषणा POLL_DELAY_MS           20

#घोषणा SCALE_FACTOR            8192
#घोषणा SCALE_MAX_FOR_LEG_LUT_F 4096
#घोषणा SCALE_MAX_FOR_LEG_LUT_E 4915
#घोषणा SCALE_MAX_FOR_LEG_LUT_D 6654
#घोषणा SCALE_MAX_FOR_LEG_LUT_C 8192

क्रमागत sti_hvsrc_orient अणु
	HVSRC_HORI,
	HVSRC_VERT
पूर्ण;

/* Command काष्ठाures */
काष्ठा sti_hqvdp_top अणु
	u32 config;
	u32 mem_क्रमmat;
	u32 current_luma;
	u32 current_enh_luma;
	u32 current_right_luma;
	u32 current_enh_right_luma;
	u32 current_chroma;
	u32 current_enh_chroma;
	u32 current_right_chroma;
	u32 current_enh_right_chroma;
	u32 output_luma;
	u32 output_chroma;
	u32 luma_src_pitch;
	u32 luma_enh_src_pitch;
	u32 luma_right_src_pitch;
	u32 luma_enh_right_src_pitch;
	u32 chroma_src_pitch;
	u32 chroma_enh_src_pitch;
	u32 chroma_right_src_pitch;
	u32 chroma_enh_right_src_pitch;
	u32 luma_processed_pitch;
	u32 chroma_processed_pitch;
	u32 input_frame_size;
	u32 input_viewport_ori;
	u32 input_viewport_ori_right;
	u32 input_viewport_size;
	u32 left_view_border_width;
	u32 right_view_border_width;
	u32 left_view_3d_offset_width;
	u32 right_view_3d_offset_width;
	u32 side_stripe_color;
	u32 crc_reset_ctrl;
पूर्ण;

/* Configs क्रम पूर्णांकerlaced : no IT, no pass thru, 3 fields */
#घोषणा TOP_CONFIG_INTER_BTM            0x00000000
#घोषणा TOP_CONFIG_INTER_TOP            0x00000002

/* Config क्रम progressive : no IT, no pass thru, 3 fields */
#घोषणा TOP_CONFIG_PROGRESSIVE          0x00000001

/* Default MemFormat: in=420_raster_dual out=444_raster;opaque Mem2Tv mode */
#घोषणा TOP_MEM_FORMAT_DFLT             0x00018060

/* Min/Max size */
#घोषणा MAX_WIDTH                       0x1FFF
#घोषणा MAX_HEIGHT                      0x0FFF
#घोषणा MIN_WIDTH                       0x0030
#घोषणा MIN_HEIGHT                      0x0010

काष्ठा sti_hqvdp_vc1re अणु
	u32 ctrl_prv_csdi;
	u32 ctrl_cur_csdi;
	u32 ctrl_nxt_csdi;
	u32 ctrl_cur_fmd;
	u32 ctrl_nxt_fmd;
पूर्ण;

काष्ठा sti_hqvdp_fmd अणु
	u32 config;
	u32 viewport_ori;
	u32 viewport_size;
	u32 next_next_luma;
	u32 next_next_right_luma;
	u32 next_next_next_luma;
	u32 next_next_next_right_luma;
	u32 threshold_scd;
	u32 threshold_rfd;
	u32 threshold_move;
	u32 threshold_cfd;
पूर्ण;

काष्ठा sti_hqvdp_csdi अणु
	u32 config;
	u32 config2;
	u32 dcdi_config;
	u32 prev_luma;
	u32 prev_enh_luma;
	u32 prev_right_luma;
	u32 prev_enh_right_luma;
	u32 next_luma;
	u32 next_enh_luma;
	u32 next_right_luma;
	u32 next_enh_right_luma;
	u32 prev_chroma;
	u32 prev_enh_chroma;
	u32 prev_right_chroma;
	u32 prev_enh_right_chroma;
	u32 next_chroma;
	u32 next_enh_chroma;
	u32 next_right_chroma;
	u32 next_enh_right_chroma;
	u32 prev_motion;
	u32 prev_right_motion;
	u32 cur_motion;
	u32 cur_right_motion;
	u32 next_motion;
	u32 next_right_motion;
पूर्ण;

/* Config क्रम progressive: by pass */
#घोषणा CSDI_CONFIG_PROG                0x00000000
/* Config क्रम directional deपूर्णांकerlacing without motion */
#घोषणा CSDI_CONFIG_INTER_सूची           0x00000016
/* Additional configs क्रम fader, blender, motion,... deपूर्णांकerlace algorithms */
#घोषणा CSDI_CONFIG2_DFLT               0x000001B3
#घोषणा CSDI_DCDI_CONFIG_DFLT           0x00203803

काष्ठा sti_hqvdp_hvsrc अणु
	u32 hor_panoramic_ctrl;
	u32 output_picture_size;
	u32 init_horizontal;
	u32 init_vertical;
	u32 param_ctrl;
	u32 yh_coef[NB_COEF];
	u32 ch_coef[NB_COEF];
	u32 yv_coef[NB_COEF];
	u32 cv_coef[NB_COEF];
	u32 hori_shअगरt;
	u32 vert_shअगरt;
पूर्ण;

/* Default ParamCtrl: all controls enabled */
#घोषणा HVSRC_PARAM_CTRL_DFLT           0xFFFFFFFF

काष्ठा sti_hqvdp_iqi अणु
	u32 config;
	u32 demo_wind_size;
	u32 pk_config;
	u32 coeff0_coeff1;
	u32 coeff2_coeff3;
	u32 coeff4;
	u32 pk_lut;
	u32 pk_gain;
	u32 pk_coring_level;
	u32 cti_config;
	u32 le_config;
	u32 le_lut[64];
	u32 con_bri;
	u32 sat_gain;
	u32 pxf_conf;
	u32 शेष_color;
पूर्ण;

/* Default Config : IQI bypassed */
#घोषणा IQI_CONFIG_DFLT                 0x00000001
/* Default Contrast & Brightness gain = 256 */
#घोषणा IQI_CON_BRI_DFLT                0x00000100
/* Default Saturation gain = 256 */
#घोषणा IQI_SAT_GAIN_DFLT               0x00000100
/* Default PxfConf : P2I bypassed */
#घोषणा IQI_PXF_CONF_DFLT               0x00000001

काष्ठा sti_hqvdp_top_status अणु
	u32 processing_समय;
	u32 input_y_crc;
	u32 input_uv_crc;
पूर्ण;

काष्ठा sti_hqvdp_fmd_status अणु
	u32 fmd_repeat_move_status;
	u32 fmd_scene_count_status;
	u32 cfd_sum;
	u32 field_sum;
	u32 next_y_fmd_crc;
	u32 next_next_y_fmd_crc;
	u32 next_next_next_y_fmd_crc;
पूर्ण;

काष्ठा sti_hqvdp_csdi_status अणु
	u32 prev_y_csdi_crc;
	u32 cur_y_csdi_crc;
	u32 next_y_csdi_crc;
	u32 prev_uv_csdi_crc;
	u32 cur_uv_csdi_crc;
	u32 next_uv_csdi_crc;
	u32 y_csdi_crc;
	u32 uv_csdi_crc;
	u32 uv_cup_crc;
	u32 mot_csdi_crc;
	u32 mot_cur_csdi_crc;
	u32 mot_prev_csdi_crc;
पूर्ण;

काष्ठा sti_hqvdp_hvsrc_status अणु
	u32 y_hvsrc_crc;
	u32 u_hvsrc_crc;
	u32 v_hvsrc_crc;
पूर्ण;

काष्ठा sti_hqvdp_iqi_status अणु
	u32 pxf_it_status;
	u32 y_iqi_crc;
	u32 u_iqi_crc;
	u32 v_iqi_crc;
पूर्ण;

/* Main commands. We use 2 commands one being processed by the firmware, one
 * पढ़ोy to be fetched upon next Vsync*/
#घोषणा NB_VDP_CMD	2

काष्ठा sti_hqvdp_cmd अणु
	काष्ठा sti_hqvdp_top top;
	काष्ठा sti_hqvdp_vc1re vc1re;
	काष्ठा sti_hqvdp_fmd fmd;
	काष्ठा sti_hqvdp_csdi csdi;
	काष्ठा sti_hqvdp_hvsrc hvsrc;
	काष्ठा sti_hqvdp_iqi iqi;
	काष्ठा sti_hqvdp_top_status top_status;
	काष्ठा sti_hqvdp_fmd_status fmd_status;
	काष्ठा sti_hqvdp_csdi_status csdi_status;
	काष्ठा sti_hqvdp_hvsrc_status hvsrc_status;
	काष्ठा sti_hqvdp_iqi_status iqi_status;
पूर्ण;

/*
 * STI HQVDP काष्ठाure
 *
 * @dev:               driver device
 * @drm_dev:           the drm device
 * @regs:              रेजिस्टरs
 * @plane:             plane काष्ठाure क्रम hqvdp it self
 * @clk:               IP घड़ी
 * @clk_pix_मुख्य:      pix मुख्य घड़ी
 * @reset:             reset control
 * @vtg_nb:            notअगरier to handle VTG Vsync
 * @bपंचांग_field_pending: is there any bottom field (पूर्णांकerlaced frame) to display
 * @hqvdp_cmd:         buffer of commands
 * @hqvdp_cmd_paddr:   physical address of hqvdp_cmd
 * @vtg:               vtg क्रम मुख्य data path
 * @xp70_initialized:  true अगर xp70 is alपढ़ोy initialized
 * @vtg_रेजिस्टरed:    true अगर रेजिस्टरed to VTG
 */
काष्ठा sti_hqvdp अणु
	काष्ठा device *dev;
	काष्ठा drm_device *drm_dev;
	व्योम __iomem *regs;
	काष्ठा sti_plane plane;
	काष्ठा clk *clk;
	काष्ठा clk *clk_pix_मुख्य;
	काष्ठा reset_control *reset;
	काष्ठा notअगरier_block vtg_nb;
	bool bपंचांग_field_pending;
	व्योम *hqvdp_cmd;
	u32 hqvdp_cmd_paddr;
	काष्ठा sti_vtg *vtg;
	bool xp70_initialized;
	bool vtg_रेजिस्टरed;
पूर्ण;

#घोषणा to_sti_hqvdp(x) container_of(x, काष्ठा sti_hqvdp, plane)

अटल स्थिर uपूर्णांक32_t hqvdp_supported_क्रमmats[] = अणु
	DRM_FORMAT_NV12,
पूर्ण;

/**
 * sti_hqvdp_get_मुक्त_cmd
 * @hqvdp: hqvdp काष्ठाure
 *
 * Look क्रम a hqvdp_cmd that is not being used (or about to be used) by the FW.
 *
 * RETURNS:
 * the offset of the command to be used.
 * -1 in error हालs
 */
अटल पूर्णांक sti_hqvdp_get_मुक्त_cmd(काष्ठा sti_hqvdp *hqvdp)
अणु
	u32 curr_cmd, next_cmd;
	u32 cmd = hqvdp->hqvdp_cmd_paddr;
	पूर्णांक i;

	curr_cmd = पढ़ोl(hqvdp->regs + HQVDP_MBX_CURRENT_CMD);
	next_cmd = पढ़ोl(hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	क्रम (i = 0; i < NB_VDP_CMD; i++) अणु
		अगर ((cmd != curr_cmd) && (cmd != next_cmd))
			वापस i * माप(काष्ठा sti_hqvdp_cmd);
		cmd += माप(काष्ठा sti_hqvdp_cmd);
	पूर्ण

	वापस -1;
पूर्ण

/**
 * sti_hqvdp_get_curr_cmd
 * @hqvdp: hqvdp काष्ठाure
 *
 * Look क्रम the hqvdp_cmd that is being used by the FW.
 *
 * RETURNS:
 *  the offset of the command to be used.
 * -1 in error हालs
 */
अटल पूर्णांक sti_hqvdp_get_curr_cmd(काष्ठा sti_hqvdp *hqvdp)
अणु
	u32 curr_cmd;
	u32 cmd = hqvdp->hqvdp_cmd_paddr;
	अचिन्हित पूर्णांक i;

	curr_cmd = पढ़ोl(hqvdp->regs + HQVDP_MBX_CURRENT_CMD);

	क्रम (i = 0; i < NB_VDP_CMD; i++) अणु
		अगर (cmd == curr_cmd)
			वापस i * माप(काष्ठा sti_hqvdp_cmd);

		cmd += माप(काष्ठा sti_hqvdp_cmd);
	पूर्ण

	वापस -1;
पूर्ण

/**
 * sti_hqvdp_get_next_cmd
 * @hqvdp: hqvdp काष्ठाure
 *
 * Look क्रम the next hqvdp_cmd that will be used by the FW.
 *
 * RETURNS:
 *  the offset of the next command that will be used.
 * -1 in error हालs
 */
अटल पूर्णांक sti_hqvdp_get_next_cmd(काष्ठा sti_hqvdp *hqvdp)
अणु
	पूर्णांक next_cmd;
	dma_addr_t cmd = hqvdp->hqvdp_cmd_paddr;
	अचिन्हित पूर्णांक i;

	next_cmd = पढ़ोl(hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	क्रम (i = 0; i < NB_VDP_CMD; i++) अणु
		अगर (cmd == next_cmd)
			वापस i * माप(काष्ठा sti_hqvdp_cmd);

		cmd += माप(काष्ठा sti_hqvdp_cmd);
	पूर्ण

	वापस -1;
पूर्ण

#घोषणा DBGFS_DUMP(reg) seq_म_लिखो(s, "\n  %-25s 0x%08X", #reg, \
				   पढ़ोl(hqvdp->regs + reg))

अटल स्थिर अक्षर *hqvdp_dbg_get_lut(u32 *coef)
अणु
	अगर (!स_भेद(coef, coef_lut_a_legacy, 16))
		वापस "LUT A";
	अगर (!स_भेद(coef, coef_lut_b, 16))
		वापस "LUT B";
	अगर (!स_भेद(coef, coef_lut_c_y_legacy, 16))
		वापस "LUT C Y";
	अगर (!स_भेद(coef, coef_lut_c_c_legacy, 16))
		वापस "LUT C C";
	अगर (!स_भेद(coef, coef_lut_d_y_legacy, 16))
		वापस "LUT D Y";
	अगर (!स_भेद(coef, coef_lut_d_c_legacy, 16))
		वापस "LUT D C";
	अगर (!स_भेद(coef, coef_lut_e_y_legacy, 16))
		वापस "LUT E Y";
	अगर (!स_भेद(coef, coef_lut_e_c_legacy, 16))
		वापस "LUT E C";
	अगर (!स_भेद(coef, coef_lut_f_y_legacy, 16))
		वापस "LUT F Y";
	अगर (!स_भेद(coef, coef_lut_f_c_legacy, 16))
		वापस "LUT F C";
	वापस "<UNKNOWN>";
पूर्ण

अटल व्योम hqvdp_dbg_dump_cmd(काष्ठा seq_file *s, काष्ठा sti_hqvdp_cmd *c)
अणु
	पूर्णांक src_w, src_h, dst_w, dst_h;

	seq_माला_दो(s, "\n\tTOP:");
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "Config", c->top.config);
	चयन (c->top.config) अणु
	हाल TOP_CONFIG_PROGRESSIVE:
		seq_माला_दो(s, "\tProgressive");
		अवरोध;
	हाल TOP_CONFIG_INTER_TOP:
		seq_माला_दो(s, "\tInterlaced, top field");
		अवरोध;
	हाल TOP_CONFIG_INTER_BTM:
		seq_माला_दो(s, "\tInterlaced, bottom field");
		अवरोध;
	शेष:
		seq_माला_दो(s, "\t<UNKNOWN>");
		अवरोध;
	पूर्ण

	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "MemFormat", c->top.mem_क्रमmat);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "CurrentY", c->top.current_luma);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "CurrentC", c->top.current_chroma);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "YSrcPitch", c->top.luma_src_pitch);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "CSrcPitch",
		   c->top.chroma_src_pitch);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "InputFrameSize",
		   c->top.input_frame_size);
	seq_म_लिखो(s, "\t%dx%d",
		   c->top.input_frame_size & 0x0000FFFF,
		   c->top.input_frame_size >> 16);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "InputViewportSize",
		   c->top.input_viewport_size);
	src_w = c->top.input_viewport_size & 0x0000FFFF;
	src_h = c->top.input_viewport_size >> 16;
	seq_म_लिखो(s, "\t%dx%d", src_w, src_h);

	seq_माला_दो(s, "\n\tHVSRC:");
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "OutputPictureSize",
		   c->hvsrc.output_picture_size);
	dst_w = c->hvsrc.output_picture_size & 0x0000FFFF;
	dst_h = c->hvsrc.output_picture_size >> 16;
	seq_म_लिखो(s, "\t%dx%d", dst_w, dst_h);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "ParamCtrl", c->hvsrc.param_ctrl);

	seq_म_लिखो(s, "\n\t %-20s %s", "yh_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.yh_coef));
	seq_म_लिखो(s, "\n\t %-20s %s", "ch_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.ch_coef));
	seq_म_लिखो(s, "\n\t %-20s %s", "yv_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.yv_coef));
	seq_म_लिखो(s, "\n\t %-20s %s", "cv_coef",
		   hqvdp_dbg_get_lut(c->hvsrc.cv_coef));

	seq_म_लिखो(s, "\n\t %-20s", "ScaleH");
	अगर (dst_w > src_w)
		seq_म_लिखो(s, " %d/1", dst_w / src_w);
	अन्यथा
		seq_म_लिखो(s, " 1/%d", src_w / dst_w);

	seq_म_लिखो(s, "\n\t %-20s", "tScaleV");
	अगर (dst_h > src_h)
		seq_म_लिखो(s, " %d/1", dst_h / src_h);
	अन्यथा
		seq_म_लिखो(s, " 1/%d", src_h / dst_h);

	seq_माला_दो(s, "\n\tCSDI:");
	seq_म_लिखो(s, "\n\t %-20s 0x%08X\t", "Config", c->csdi.config);
	चयन (c->csdi.config) अणु
	हाल CSDI_CONFIG_PROG:
		seq_माला_दो(s, "Bypass");
		अवरोध;
	हाल CSDI_CONFIG_INTER_सूची:
		seq_माला_दो(s, "Deinterlace, directional");
		अवरोध;
	शेष:
		seq_माला_दो(s, "<UNKNOWN>");
		अवरोध;
	पूर्ण

	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "Config2", c->csdi.config2);
	seq_म_लिखो(s, "\n\t %-20s 0x%08X", "DcdiConfig", c->csdi.dcdi_config);
पूर्ण

अटल पूर्णांक hqvdp_dbg_show(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा drm_info_node *node = s->निजी;
	काष्ठा sti_hqvdp *hqvdp = (काष्ठा sti_hqvdp *)node->info_ent->data;
	पूर्णांक cmd, cmd_offset, infoxp70;
	व्योम *virt;

	seq_म_लिखो(s, "%s: (vaddr = 0x%p)",
		   sti_plane_to_str(&hqvdp->plane), hqvdp->regs);

	DBGFS_DUMP(HQVDP_MBX_IRQ_TO_XP70);
	DBGFS_DUMP(HQVDP_MBX_INFO_HOST);
	DBGFS_DUMP(HQVDP_MBX_IRQ_TO_HOST);
	DBGFS_DUMP(HQVDP_MBX_INFO_XP70);
	infoxp70 = पढ़ोl(hqvdp->regs + HQVDP_MBX_INFO_XP70);
	seq_माला_दो(s, "\tFirmware state: ");
	अगर (infoxp70 & INFO_XP70_FW_READY)
		seq_माला_दो(s, "idle and ready");
	अन्यथा अगर (infoxp70 & INFO_XP70_FW_PROCESSING)
		seq_माला_दो(s, "processing a picture");
	अन्यथा अगर (infoxp70 & INFO_XP70_FW_INITQUEUES)
		seq_माला_दो(s, "programming queues");
	अन्यथा
		seq_माला_दो(s, "NOT READY");

	DBGFS_DUMP(HQVDP_MBX_SW_RESET_CTRL);
	DBGFS_DUMP(HQVDP_MBX_STARTUP_CTRL1);
	अगर (पढ़ोl(hqvdp->regs + HQVDP_MBX_STARTUP_CTRL1)
					& STARTUP_CTRL1_RST_DONE)
		seq_माला_दो(s, "\tReset is done");
	अन्यथा
		seq_माला_दो(s, "\tReset is NOT done");
	DBGFS_DUMP(HQVDP_MBX_STARTUP_CTRL2);
	अगर (पढ़ोl(hqvdp->regs + HQVDP_MBX_STARTUP_CTRL2)
					& STARTUP_CTRL2_FETCH_EN)
		seq_माला_दो(s, "\tFetch is enabled");
	अन्यथा
		seq_माला_दो(s, "\tFetch is NOT enabled");
	DBGFS_DUMP(HQVDP_MBX_GP_STATUS);
	DBGFS_DUMP(HQVDP_MBX_NEXT_CMD);
	DBGFS_DUMP(HQVDP_MBX_CURRENT_CMD);
	DBGFS_DUMP(HQVDP_MBX_SOFT_VSYNC);
	अगर (!(पढ़ोl(hqvdp->regs + HQVDP_MBX_SOFT_VSYNC) & 3))
		seq_माला_दो(s, "\tHW Vsync");
	अन्यथा
		seq_माला_दो(s, "\tSW Vsync ?!?!");

	/* Last command */
	cmd = पढ़ोl(hqvdp->regs + HQVDP_MBX_CURRENT_CMD);
	cmd_offset = sti_hqvdp_get_curr_cmd(hqvdp);
	अगर (cmd_offset == -1) अणु
		seq_माला_दो(s, "\n\n  Last command: unknown");
	पूर्ण अन्यथा अणु
		virt = hqvdp->hqvdp_cmd + cmd_offset;
		seq_म_लिखो(s, "\n\n  Last command: address @ 0x%x (0x%p)",
			   cmd, virt);
		hqvdp_dbg_dump_cmd(s, (काष्ठा sti_hqvdp_cmd *)virt);
	पूर्ण

	/* Next command */
	cmd = पढ़ोl(hqvdp->regs + HQVDP_MBX_NEXT_CMD);
	cmd_offset = sti_hqvdp_get_next_cmd(hqvdp);
	अगर (cmd_offset == -1) अणु
		seq_माला_दो(s, "\n\n  Next command: unknown");
	पूर्ण अन्यथा अणु
		virt = hqvdp->hqvdp_cmd + cmd_offset;
		seq_म_लिखो(s, "\n\n  Next command address: @ 0x%x (0x%p)",
			   cmd, virt);
		hqvdp_dbg_dump_cmd(s, (काष्ठा sti_hqvdp_cmd *)virt);
	पूर्ण

	seq_अ_दो(s, '\n');
	वापस 0;
पूर्ण

अटल काष्ठा drm_info_list hqvdp_debugfs_files[] = अणु
	अणु "hqvdp", hqvdp_dbg_show, 0, शून्य पूर्ण,
पूर्ण;

अटल व्योम hqvdp_debugfs_init(काष्ठा sti_hqvdp *hqvdp, काष्ठा drm_minor *minor)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(hqvdp_debugfs_files); i++)
		hqvdp_debugfs_files[i].data = hqvdp;

	drm_debugfs_create_files(hqvdp_debugfs_files,
				 ARRAY_SIZE(hqvdp_debugfs_files),
				 minor->debugfs_root, minor);
पूर्ण

/**
 * sti_hqvdp_update_hvsrc
 * @orient: horizontal or vertical
 * @scale:  scaling/zoom factor
 * @hvsrc:  the काष्ठाure containing the LUT coef
 *
 * Update the Y and C Lut coef, as well as the shअगरt param
 *
 * RETURNS:
 * None.
 */
अटल व्योम sti_hqvdp_update_hvsrc(क्रमागत sti_hvsrc_orient orient, पूर्णांक scale,
		काष्ठा sti_hqvdp_hvsrc *hvsrc)
अणु
	स्थिर पूर्णांक *coef_c, *coef_y;
	पूर्णांक shअगरt_c, shअगरt_y;

	/* Get the appropriate coef tables */
	अगर (scale < SCALE_MAX_FOR_LEG_LUT_F) अणु
		coef_y = coef_lut_f_y_legacy;
		coef_c = coef_lut_f_c_legacy;
		shअगरt_y = SHIFT_LUT_F_Y_LEGACY;
		shअगरt_c = SHIFT_LUT_F_C_LEGACY;
	पूर्ण अन्यथा अगर (scale < SCALE_MAX_FOR_LEG_LUT_E) अणु
		coef_y = coef_lut_e_y_legacy;
		coef_c = coef_lut_e_c_legacy;
		shअगरt_y = SHIFT_LUT_E_Y_LEGACY;
		shअगरt_c = SHIFT_LUT_E_C_LEGACY;
	पूर्ण अन्यथा अगर (scale < SCALE_MAX_FOR_LEG_LUT_D) अणु
		coef_y = coef_lut_d_y_legacy;
		coef_c = coef_lut_d_c_legacy;
		shअगरt_y = SHIFT_LUT_D_Y_LEGACY;
		shअगरt_c = SHIFT_LUT_D_C_LEGACY;
	पूर्ण अन्यथा अगर (scale < SCALE_MAX_FOR_LEG_LUT_C) अणु
		coef_y = coef_lut_c_y_legacy;
		coef_c = coef_lut_c_c_legacy;
		shअगरt_y = SHIFT_LUT_C_Y_LEGACY;
		shअगरt_c = SHIFT_LUT_C_C_LEGACY;
	पूर्ण अन्यथा अगर (scale == SCALE_MAX_FOR_LEG_LUT_C) अणु
		coef_y = coef_c = coef_lut_b;
		shअगरt_y = shअगरt_c = SHIFT_LUT_B;
	पूर्ण अन्यथा अणु
		coef_y = coef_c = coef_lut_a_legacy;
		shअगरt_y = shअगरt_c = SHIFT_LUT_A_LEGACY;
	पूर्ण

	अगर (orient == HVSRC_HORI) अणु
		hvsrc->hori_shअगरt = (shअगरt_c << 16) | shअगरt_y;
		स_नकल(hvsrc->yh_coef, coef_y, माप(hvsrc->yh_coef));
		स_नकल(hvsrc->ch_coef, coef_c, माप(hvsrc->ch_coef));
	पूर्ण अन्यथा अणु
		hvsrc->vert_shअगरt = (shअगरt_c << 16) | shअगरt_y;
		स_नकल(hvsrc->yv_coef, coef_y, माप(hvsrc->yv_coef));
		स_नकल(hvsrc->cv_coef, coef_c, माप(hvsrc->cv_coef));
	पूर्ण
पूर्ण

/**
 * sti_hqvdp_check_hw_scaling
 * @hqvdp: hqvdp poपूर्णांकer
 * @mode: display mode with timing स्थिरraपूर्णांकs
 * @src_w: source width
 * @src_h: source height
 * @dst_w: destination width
 * @dst_h: destination height
 *
 * Check अगर the HW is able to perक्रमm the scaling request
 * The firmware scaling limitation is "CEIL(1/Zy) <= FLOOR(LFW)" where:
 *   Zy = OutputHeight / InputHeight
 *   LFW = (Tx * IPClock) / (MaxNbCycles * Cp)
 *     Tx : Total video mode horizontal resolution
 *     IPClock : HQVDP IP घड़ी (Mhz)
 *     MaxNbCycles: max(InputWidth, OutputWidth)
 *     Cp: Video mode pixel घड़ी (Mhz)
 *
 * RETURNS:
 * True अगर the HW can scale.
 */
अटल bool sti_hqvdp_check_hw_scaling(काष्ठा sti_hqvdp *hqvdp,
				       काष्ठा drm_display_mode *mode,
				       पूर्णांक src_w, पूर्णांक src_h,
				       पूर्णांक dst_w, पूर्णांक dst_h)
अणु
	अचिन्हित दीर्घ lfw;
	अचिन्हित पूर्णांक inv_zy;

	lfw = mode->htotal * (clk_get_rate(hqvdp->clk) / 1000000);
	lfw /= max(src_w, dst_w) * mode->घड़ी / 1000;

	inv_zy = DIV_ROUND_UP(src_h, dst_h);

	वापस (inv_zy <= lfw) ? true : false;
पूर्ण

/**
 * sti_hqvdp_disable
 * @hqvdp: hqvdp poपूर्णांकer
 *
 * Disables the HQVDP plane
 */
अटल व्योम sti_hqvdp_disable(काष्ठा sti_hqvdp *hqvdp)
अणु
	पूर्णांक i;

	DRM_DEBUG_DRIVER("%s\n", sti_plane_to_str(&hqvdp->plane));

	/* Unरेजिस्टर VTG Vsync callback */
	अगर (sti_vtg_unरेजिस्टर_client(hqvdp->vtg, &hqvdp->vtg_nb))
		DRM_DEBUG_DRIVER("Warning: cannot unregister VTG notifier\n");

	/* Set next cmd to शून्य */
	ग_लिखोl(0, hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	क्रम (i = 0; i < POLL_MAX_ATTEMPT; i++) अणु
		अगर (पढ़ोl(hqvdp->regs + HQVDP_MBX_INFO_XP70)
				& INFO_XP70_FW_READY)
			अवरोध;
		msleep(POLL_DELAY_MS);
	पूर्ण

	/* VTG can stop now */
	clk_disable_unprepare(hqvdp->clk_pix_मुख्य);

	अगर (i == POLL_MAX_ATTEMPT)
		DRM_ERROR("XP70 could not revert to idle\n");

	hqvdp->plane.status = STI_PLANE_DISABLED;
	hqvdp->vtg_रेजिस्टरed = false;
पूर्ण

/**
 * sti_vdp_vtg_cb
 * @nb: notअगरier block
 * @evt: event message
 * @data: निजी data
 *
 * Handle VTG Vsync event, display pending bottom field
 *
 * RETURNS:
 * 0 on success.
 */
अटल पूर्णांक sti_hqvdp_vtg_cb(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ evt, व्योम *data)
अणु
	काष्ठा sti_hqvdp *hqvdp = container_of(nb, काष्ठा sti_hqvdp, vtg_nb);
	पूर्णांक bपंचांग_cmd_offset, top_cmd_offest;
	काष्ठा sti_hqvdp_cmd *bपंचांग_cmd, *top_cmd;

	अगर ((evt != VTG_TOP_FIELD_EVENT) && (evt != VTG_BOTTOM_FIELD_EVENT)) अणु
		DRM_DEBUG_DRIVER("Unknown event\n");
		वापस 0;
	पूर्ण

	अगर (hqvdp->plane.status == STI_PLANE_FLUSHING) अणु
		/* disable need to be synchronize on vsync event */
		DRM_DEBUG_DRIVER("Vsync event received => disable %s\n",
				 sti_plane_to_str(&hqvdp->plane));

		sti_hqvdp_disable(hqvdp);
	पूर्ण

	अगर (hqvdp->bपंचांग_field_pending) अणु
		/* Create the bपंचांग field command from the current one */
		bपंचांग_cmd_offset = sti_hqvdp_get_मुक्त_cmd(hqvdp);
		top_cmd_offest = sti_hqvdp_get_curr_cmd(hqvdp);
		अगर ((bपंचांग_cmd_offset == -1) || (top_cmd_offest == -1)) अणु
			DRM_DEBUG_DRIVER("Warning: no cmd, will skip field\n");
			वापस -EBUSY;
		पूर्ण

		bपंचांग_cmd = hqvdp->hqvdp_cmd + bपंचांग_cmd_offset;
		top_cmd = hqvdp->hqvdp_cmd + top_cmd_offest;

		स_नकल(bपंचांग_cmd, top_cmd, माप(*bपंचांग_cmd));

		bपंचांग_cmd->top.config = TOP_CONFIG_INTER_BTM;
		bपंचांग_cmd->top.current_luma +=
				bपंचांग_cmd->top.luma_src_pitch / 2;
		bपंचांग_cmd->top.current_chroma +=
				bपंचांग_cmd->top.chroma_src_pitch / 2;

		/* Post the command to mailbox */
		ग_लिखोl(hqvdp->hqvdp_cmd_paddr + bपंचांग_cmd_offset,
				hqvdp->regs + HQVDP_MBX_NEXT_CMD);

		hqvdp->bपंचांग_field_pending = false;

		dev_dbg(hqvdp->dev, "%s Posted command:0x%x\n",
				__func__, hqvdp->hqvdp_cmd_paddr);

		sti_plane_update_fps(&hqvdp->plane, false, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sti_hqvdp_init(काष्ठा sti_hqvdp *hqvdp)
अणु
	पूर्णांक size;
	dma_addr_t dma_addr;

	hqvdp->vtg_nb.notअगरier_call = sti_hqvdp_vtg_cb;

	/* Allocate memory क्रम the VDP commands */
	size = NB_VDP_CMD * माप(काष्ठा sti_hqvdp_cmd);
	hqvdp->hqvdp_cmd = dma_alloc_wc(hqvdp->dev, size,
					&dma_addr,
					GFP_KERNEL | GFP_DMA);
	अगर (!hqvdp->hqvdp_cmd) अणु
		DRM_ERROR("Failed to allocate memory for VDP cmd\n");
		वापस;
	पूर्ण

	hqvdp->hqvdp_cmd_paddr = (u32)dma_addr;
	स_रखो(hqvdp->hqvdp_cmd, 0, size);
पूर्ण

अटल व्योम sti_hqvdp_init_plugs(काष्ठा sti_hqvdp *hqvdp)
अणु
	/* Configure Plugs (same क्रम RD & WR) */
	ग_लिखोl(PLUG_PAGE_SIZE_256, hqvdp->regs + HQVDP_RD_PLUG_PAGE_SIZE);
	ग_लिखोl(PLUG_MIN_OPC_8, hqvdp->regs + HQVDP_RD_PLUG_MIN_OPC);
	ग_लिखोl(PLUG_MAX_OPC_64, hqvdp->regs + HQVDP_RD_PLUG_MAX_OPC);
	ग_लिखोl(PLUG_MAX_CHK_2X, hqvdp->regs + HQVDP_RD_PLUG_MAX_CHK);
	ग_लिखोl(PLUG_MAX_MSG_1X, hqvdp->regs + HQVDP_RD_PLUG_MAX_MSG);
	ग_लिखोl(PLUG_MIN_SPACE_1, hqvdp->regs + HQVDP_RD_PLUG_MIN_SPACE);
	ग_लिखोl(PLUG_CONTROL_ENABLE, hqvdp->regs + HQVDP_RD_PLUG_CONTROL);

	ग_लिखोl(PLUG_PAGE_SIZE_256, hqvdp->regs + HQVDP_WR_PLUG_PAGE_SIZE);
	ग_लिखोl(PLUG_MIN_OPC_8, hqvdp->regs + HQVDP_WR_PLUG_MIN_OPC);
	ग_लिखोl(PLUG_MAX_OPC_64, hqvdp->regs + HQVDP_WR_PLUG_MAX_OPC);
	ग_लिखोl(PLUG_MAX_CHK_2X, hqvdp->regs + HQVDP_WR_PLUG_MAX_CHK);
	ग_लिखोl(PLUG_MAX_MSG_1X, hqvdp->regs + HQVDP_WR_PLUG_MAX_MSG);
	ग_लिखोl(PLUG_MIN_SPACE_1, hqvdp->regs + HQVDP_WR_PLUG_MIN_SPACE);
	ग_लिखोl(PLUG_CONTROL_ENABLE, hqvdp->regs + HQVDP_WR_PLUG_CONTROL);
पूर्ण

/**
 * sti_hqvdp_start_xp70
 * @hqvdp: hqvdp poपूर्णांकer
 *
 * Run the xP70 initialization sequence
 */
अटल व्योम sti_hqvdp_start_xp70(काष्ठा sti_hqvdp *hqvdp)
अणु
	स्थिर काष्ठा firmware *firmware;
	u32 *fw_rd_plug, *fw_wr_plug, *fw_pmem, *fw_dmem;
	u8 *data;
	पूर्णांक i;
	काष्ठा fw_header अणु
		पूर्णांक rd_size;
		पूर्णांक wr_size;
		पूर्णांक pmem_size;
		पूर्णांक dmem_size;
	पूर्ण *header;

	DRM_DEBUG_DRIVER("\n");

	अगर (hqvdp->xp70_initialized) अणु
		DRM_DEBUG_DRIVER("HQVDP XP70 already initialized\n");
		वापस;
	पूर्ण

	/* Request firmware */
	अगर (request_firmware(&firmware, HQVDP_FMW_NAME, hqvdp->dev)) अणु
		DRM_ERROR("Can't get HQVDP firmware\n");
		वापस;
	पूर्ण

	/* Check firmware parts */
	अगर (!firmware) अणु
		DRM_ERROR("Firmware not available\n");
		वापस;
	पूर्ण

	header = (काष्ठा fw_header *)firmware->data;
	अगर (firmware->size < माप(*header)) अणु
		DRM_ERROR("Invalid firmware size (%d)\n", firmware->size);
		जाओ out;
	पूर्ण
	अगर ((माप(*header) + header->rd_size + header->wr_size +
		header->pmem_size + header->dmem_size) != firmware->size) अणु
		DRM_ERROR("Invalid fmw structure (%d+%d+%d+%d+%d != %d)\n",
			  माप(*header), header->rd_size, header->wr_size,
			  header->pmem_size, header->dmem_size,
			  firmware->size);
		जाओ out;
	पूर्ण

	data = (u8 *)firmware->data;
	data += माप(*header);
	fw_rd_plug = (व्योम *)data;
	data += header->rd_size;
	fw_wr_plug = (व्योम *)data;
	data += header->wr_size;
	fw_pmem = (व्योम *)data;
	data += header->pmem_size;
	fw_dmem = (व्योम *)data;

	/* Enable घड़ी */
	अगर (clk_prepare_enable(hqvdp->clk))
		DRM_ERROR("Failed to prepare/enable HQVDP clk\n");

	/* Reset */
	ग_लिखोl(SW_RESET_CTRL_FULL, hqvdp->regs + HQVDP_MBX_SW_RESET_CTRL);

	क्रम (i = 0; i < POLL_MAX_ATTEMPT; i++) अणु
		अगर (पढ़ोl(hqvdp->regs + HQVDP_MBX_STARTUP_CTRL1)
				& STARTUP_CTRL1_RST_DONE)
			अवरोध;
		msleep(POLL_DELAY_MS);
	पूर्ण
	अगर (i == POLL_MAX_ATTEMPT) अणु
		DRM_ERROR("Could not reset\n");
		clk_disable_unprepare(hqvdp->clk);
		जाओ out;
	पूर्ण

	/* Init Read & Write plugs */
	क्रम (i = 0; i < header->rd_size / 4; i++)
		ग_लिखोl(fw_rd_plug[i], hqvdp->regs + HQVDP_RD_PLUG + i * 4);
	क्रम (i = 0; i < header->wr_size / 4; i++)
		ग_लिखोl(fw_wr_plug[i], hqvdp->regs + HQVDP_WR_PLUG + i * 4);

	sti_hqvdp_init_plugs(hqvdp);

	/* Authorize Idle Mode */
	ग_लिखोl(STARTUP_CTRL1_AUTH_IDLE, hqvdp->regs + HQVDP_MBX_STARTUP_CTRL1);

	/* Prevent VTG पूर्णांकerruption during the boot */
	ग_लिखोl(SOFT_VSYNC_SW_CTRL_IRQ, hqvdp->regs + HQVDP_MBX_SOFT_VSYNC);
	ग_लिखोl(0, hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	/* Download PMEM & DMEM */
	क्रम (i = 0; i < header->pmem_size / 4; i++)
		ग_लिखोl(fw_pmem[i], hqvdp->regs + HQVDP_PMEM + i * 4);
	क्रम (i = 0; i < header->dmem_size / 4; i++)
		ग_लिखोl(fw_dmem[i], hqvdp->regs + HQVDP_DMEM + i * 4);

	/* Enable fetch */
	ग_लिखोl(STARTUP_CTRL2_FETCH_EN, hqvdp->regs + HQVDP_MBX_STARTUP_CTRL2);

	/* Wait end of boot */
	क्रम (i = 0; i < POLL_MAX_ATTEMPT; i++) अणु
		अगर (पढ़ोl(hqvdp->regs + HQVDP_MBX_INFO_XP70)
				& INFO_XP70_FW_READY)
			अवरोध;
		msleep(POLL_DELAY_MS);
	पूर्ण
	अगर (i == POLL_MAX_ATTEMPT) अणु
		DRM_ERROR("Could not boot\n");
		clk_disable_unprepare(hqvdp->clk);
		जाओ out;
	पूर्ण

	/* Launch Vsync */
	ग_लिखोl(SOFT_VSYNC_HW, hqvdp->regs + HQVDP_MBX_SOFT_VSYNC);

	DRM_INFO("HQVDP XP70 initialized\n");

	hqvdp->xp70_initialized = true;

out:
	release_firmware(firmware);
पूर्ण

अटल पूर्णांक sti_hqvdp_atomic_check(काष्ठा drm_plane *drm_plane,
				  काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *new_plane_state = drm_atomic_get_new_plane_state(state,
										 drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_hqvdp *hqvdp = to_sti_hqvdp(plane);
	काष्ठा drm_crtc *crtc = new_plane_state->crtc;
	काष्ठा drm_framebuffer *fb = new_plane_state->fb;
	काष्ठा drm_crtc_state *crtc_state;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_x, dst_y, dst_w, dst_h;
	पूर्णांक src_x, src_y, src_w, src_h;

	/* no need क्रम further checks अगर the plane is being disabled */
	अगर (!crtc || !fb)
		वापस 0;

	crtc_state = drm_atomic_get_crtc_state(state, crtc);
	mode = &crtc_state->mode;
	dst_x = new_plane_state->crtc_x;
	dst_y = new_plane_state->crtc_y;
	dst_w = clamp_val(new_plane_state->crtc_w, 0, mode->hdisplay - dst_x);
	dst_h = clamp_val(new_plane_state->crtc_h, 0, mode->vdisplay - dst_y);
	/* src_x are in 16.16 क्रमmat */
	src_x = new_plane_state->src_x >> 16;
	src_y = new_plane_state->src_y >> 16;
	src_w = new_plane_state->src_w >> 16;
	src_h = new_plane_state->src_h >> 16;

	अगर (mode->घड़ी && !sti_hqvdp_check_hw_scaling(hqvdp, mode,
						       src_w, src_h,
						       dst_w, dst_h)) अणु
		DRM_ERROR("Scaling beyond HW capabilities\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!drm_fb_cma_get_gem_obj(fb, 0)) अणु
		DRM_ERROR("Can't get CMA GEM object for fb\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Input / output size
	 * Align to upper even value
	 */
	dst_w = ALIGN(dst_w, 2);
	dst_h = ALIGN(dst_h, 2);

	अगर ((src_w > MAX_WIDTH) || (src_w < MIN_WIDTH) ||
	    (src_h > MAX_HEIGHT) || (src_h < MIN_HEIGHT) ||
	    (dst_w > MAX_WIDTH) || (dst_w < MIN_WIDTH) ||
	    (dst_h > MAX_HEIGHT) || (dst_h < MIN_HEIGHT)) अणु
		DRM_ERROR("Invalid in/out size %dx%d -> %dx%d\n",
			  src_w, src_h,
			  dst_w, dst_h);
		वापस -EINVAL;
	पूर्ण

	अगर (!hqvdp->xp70_initialized)
		/* Start HQVDP XP70 coprocessor */
		sti_hqvdp_start_xp70(hqvdp);

	अगर (!hqvdp->vtg_रेजिस्टरed) अणु
		/* Prevent VTG shutकरोwn */
		अगर (clk_prepare_enable(hqvdp->clk_pix_मुख्य)) अणु
			DRM_ERROR("Failed to prepare/enable pix main clk\n");
			वापस -EINVAL;
		पूर्ण

		/* Register VTG Vsync callback to handle bottom fields */
		अगर (sti_vtg_रेजिस्टर_client(hqvdp->vtg,
					    &hqvdp->vtg_nb,
					    crtc)) अणु
			DRM_ERROR("Cannot register VTG notifier\n");
			clk_disable_unprepare(hqvdp->clk_pix_मुख्य);
			वापस -EINVAL;
		पूर्ण
		hqvdp->vtg_रेजिस्टरed = true;
	पूर्ण

	DRM_DEBUG_KMS("CRTC:%d (%s) drm plane:%d (%s)\n",
		      crtc->base.id, sti_mixer_to_str(to_sti_mixer(crtc)),
		      drm_plane->base.id, sti_plane_to_str(plane));
	DRM_DEBUG_KMS("%s dst=(%dx%d)@(%d,%d) - src=(%dx%d)@(%d,%d)\n",
		      sti_plane_to_str(plane),
		      dst_w, dst_h, dst_x, dst_y,
		      src_w, src_h, src_x, src_y);

	वापस 0;
पूर्ण

अटल व्योम sti_hqvdp_atomic_update(काष्ठा drm_plane *drm_plane,
				    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *oldstate = drm_atomic_get_old_plane_state(state,
									  drm_plane);
	काष्ठा drm_plane_state *newstate = drm_atomic_get_new_plane_state(state,
									  drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_hqvdp *hqvdp = to_sti_hqvdp(plane);
	काष्ठा drm_crtc *crtc = newstate->crtc;
	काष्ठा drm_framebuffer *fb = newstate->fb;
	काष्ठा drm_display_mode *mode;
	पूर्णांक dst_x, dst_y, dst_w, dst_h;
	पूर्णांक src_x, src_y, src_w, src_h;
	काष्ठा drm_gem_cma_object *cma_obj;
	काष्ठा sti_hqvdp_cmd *cmd;
	पूर्णांक scale_h, scale_v;
	पूर्णांक cmd_offset;

	अगर (!crtc || !fb)
		वापस;

	अगर ((oldstate->fb == newstate->fb) &&
	    (oldstate->crtc_x == newstate->crtc_x) &&
	    (oldstate->crtc_y == newstate->crtc_y) &&
	    (oldstate->crtc_w == newstate->crtc_w) &&
	    (oldstate->crtc_h == newstate->crtc_h) &&
	    (oldstate->src_x == newstate->src_x) &&
	    (oldstate->src_y == newstate->src_y) &&
	    (oldstate->src_w == newstate->src_w) &&
	    (oldstate->src_h == newstate->src_h)) अणु
		/* No change since last update, करो not post cmd */
		DRM_DEBUG_DRIVER("No change, not posting cmd\n");
		plane->status = STI_PLANE_UPDATED;
		वापस;
	पूर्ण

	mode = &crtc->mode;
	dst_x = newstate->crtc_x;
	dst_y = newstate->crtc_y;
	dst_w = clamp_val(newstate->crtc_w, 0, mode->hdisplay - dst_x);
	dst_h = clamp_val(newstate->crtc_h, 0, mode->vdisplay - dst_y);
	/* src_x are in 16.16 क्रमmat */
	src_x = newstate->src_x >> 16;
	src_y = newstate->src_y >> 16;
	src_w = newstate->src_w >> 16;
	src_h = newstate->src_h >> 16;

	cmd_offset = sti_hqvdp_get_मुक्त_cmd(hqvdp);
	अगर (cmd_offset == -1) अणु
		DRM_DEBUG_DRIVER("Warning: no cmd, will skip frame\n");
		वापस;
	पूर्ण
	cmd = hqvdp->hqvdp_cmd + cmd_offset;

	/* Static parameters, शेषing to progressive mode */
	cmd->top.config = TOP_CONFIG_PROGRESSIVE;
	cmd->top.mem_क्रमmat = TOP_MEM_FORMAT_DFLT;
	cmd->hvsrc.param_ctrl = HVSRC_PARAM_CTRL_DFLT;
	cmd->csdi.config = CSDI_CONFIG_PROG;

	/* VC1RE, FMD bypassed : keep everything set to 0
	 * IQI/P2I bypassed */
	cmd->iqi.config = IQI_CONFIG_DFLT;
	cmd->iqi.con_bri = IQI_CON_BRI_DFLT;
	cmd->iqi.sat_gain = IQI_SAT_GAIN_DFLT;
	cmd->iqi.pxf_conf = IQI_PXF_CONF_DFLT;

	cma_obj = drm_fb_cma_get_gem_obj(fb, 0);

	DRM_DEBUG_DRIVER("drm FB:%d format:%.4s phys@:0x%lx\n", fb->base.id,
			 (अक्षर *)&fb->क्रमmat->क्रमmat,
			 (अचिन्हित दीर्घ)cma_obj->paddr);

	/* Buffer planes address */
	cmd->top.current_luma = (u32)cma_obj->paddr + fb->offsets[0];
	cmd->top.current_chroma = (u32)cma_obj->paddr + fb->offsets[1];

	/* Pitches */
	cmd->top.luma_processed_pitch = fb->pitches[0];
	cmd->top.luma_src_pitch = fb->pitches[0];
	cmd->top.chroma_processed_pitch = fb->pitches[1];
	cmd->top.chroma_src_pitch = fb->pitches[1];

	/* Input / output size
	 * Align to upper even value */
	dst_w = ALIGN(dst_w, 2);
	dst_h = ALIGN(dst_h, 2);

	cmd->top.input_viewport_size = src_h << 16 | src_w;
	cmd->top.input_frame_size = src_h << 16 | src_w;
	cmd->hvsrc.output_picture_size = dst_h << 16 | dst_w;
	cmd->top.input_viewport_ori = src_y << 16 | src_x;

	/* Handle पूर्णांकerlaced */
	अगर (fb->flags & DRM_MODE_FB_INTERLACED) अणु
		/* Top field to display */
		cmd->top.config = TOP_CONFIG_INTER_TOP;

		/* Update pitches and vert size */
		cmd->top.input_frame_size = (src_h / 2) << 16 | src_w;
		cmd->top.luma_processed_pitch *= 2;
		cmd->top.luma_src_pitch *= 2;
		cmd->top.chroma_processed_pitch *= 2;
		cmd->top.chroma_src_pitch *= 2;

		/* Enable directional deपूर्णांकerlacing processing */
		cmd->csdi.config = CSDI_CONFIG_INTER_सूची;
		cmd->csdi.config2 = CSDI_CONFIG2_DFLT;
		cmd->csdi.dcdi_config = CSDI_DCDI_CONFIG_DFLT;
	पूर्ण

	/* Update hvsrc lut coef */
	scale_h = SCALE_FACTOR * dst_w / src_w;
	sti_hqvdp_update_hvsrc(HVSRC_HORI, scale_h, &cmd->hvsrc);

	scale_v = SCALE_FACTOR * dst_h / src_h;
	sti_hqvdp_update_hvsrc(HVSRC_VERT, scale_v, &cmd->hvsrc);

	ग_लिखोl(hqvdp->hqvdp_cmd_paddr + cmd_offset,
	       hqvdp->regs + HQVDP_MBX_NEXT_CMD);

	/* Interlaced : get पढ़ोy to display the bottom field at next Vsync */
	अगर (fb->flags & DRM_MODE_FB_INTERLACED)
		hqvdp->bपंचांग_field_pending = true;

	dev_dbg(hqvdp->dev, "%s Posted command:0x%x\n",
		__func__, hqvdp->hqvdp_cmd_paddr + cmd_offset);

	sti_plane_update_fps(plane, true, true);

	plane->status = STI_PLANE_UPDATED;
पूर्ण

अटल व्योम sti_hqvdp_atomic_disable(काष्ठा drm_plane *drm_plane,
				     काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_plane_state *oldstate = drm_atomic_get_old_plane_state(state,
									  drm_plane);
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);

	अगर (!oldstate->crtc) अणु
		DRM_DEBUG_DRIVER("drm plane:%d not enabled\n",
				 drm_plane->base.id);
		वापस;
	पूर्ण

	DRM_DEBUG_DRIVER("CRTC:%d (%s) drm plane:%d (%s)\n",
			 oldstate->crtc->base.id,
			 sti_mixer_to_str(to_sti_mixer(oldstate->crtc)),
			 drm_plane->base.id, sti_plane_to_str(plane));

	plane->status = STI_PLANE_DISABLING;
पूर्ण

अटल स्थिर काष्ठा drm_plane_helper_funcs sti_hqvdp_helpers_funcs = अणु
	.atomic_check = sti_hqvdp_atomic_check,
	.atomic_update = sti_hqvdp_atomic_update,
	.atomic_disable = sti_hqvdp_atomic_disable,
पूर्ण;

अटल पूर्णांक sti_hqvdp_late_रेजिस्टर(काष्ठा drm_plane *drm_plane)
अणु
	काष्ठा sti_plane *plane = to_sti_plane(drm_plane);
	काष्ठा sti_hqvdp *hqvdp = to_sti_hqvdp(plane);

	hqvdp_debugfs_init(hqvdp, drm_plane->dev->primary);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_plane_funcs sti_hqvdp_plane_helpers_funcs = अणु
	.update_plane = drm_atomic_helper_update_plane,
	.disable_plane = drm_atomic_helper_disable_plane,
	.destroy = drm_plane_cleanup,
	.reset = sti_plane_reset,
	.atomic_duplicate_state = drm_atomic_helper_plane_duplicate_state,
	.atomic_destroy_state = drm_atomic_helper_plane_destroy_state,
	.late_रेजिस्टर = sti_hqvdp_late_रेजिस्टर,
पूर्ण;

अटल काष्ठा drm_plane *sti_hqvdp_create(काष्ठा drm_device *drm_dev,
					  काष्ठा device *dev, पूर्णांक desc)
अणु
	काष्ठा sti_hqvdp *hqvdp = dev_get_drvdata(dev);
	पूर्णांक res;

	hqvdp->plane.desc = desc;
	hqvdp->plane.status = STI_PLANE_DISABLED;

	sti_hqvdp_init(hqvdp);

	res = drm_universal_plane_init(drm_dev, &hqvdp->plane.drm_plane, 1,
				       &sti_hqvdp_plane_helpers_funcs,
				       hqvdp_supported_क्रमmats,
				       ARRAY_SIZE(hqvdp_supported_क्रमmats),
				       शून्य, DRM_PLANE_TYPE_OVERLAY, शून्य);
	अगर (res) अणु
		DRM_ERROR("Failed to initialize universal plane\n");
		वापस शून्य;
	पूर्ण

	drm_plane_helper_add(&hqvdp->plane.drm_plane, &sti_hqvdp_helpers_funcs);

	sti_plane_init_property(&hqvdp->plane, DRM_PLANE_TYPE_OVERLAY);

	वापस &hqvdp->plane.drm_plane;
पूर्ण

अटल पूर्णांक sti_hqvdp_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा sti_hqvdp *hqvdp = dev_get_drvdata(dev);
	काष्ठा drm_device *drm_dev = data;
	काष्ठा drm_plane *plane;

	DRM_DEBUG_DRIVER("\n");

	hqvdp->drm_dev = drm_dev;

	/* Create HQVDP plane once xp70 is initialized */
	plane = sti_hqvdp_create(drm_dev, hqvdp->dev, STI_HQVDP_0);
	अगर (!plane)
		DRM_ERROR("Can't create HQVDP plane\n");

	वापस 0;
पूर्ण

अटल व्योम sti_hqvdp_unbind(काष्ठा device *dev,
		काष्ठा device *master, व्योम *data)
अणु
	/* करो nothing */
पूर्ण

अटल स्थिर काष्ठा component_ops sti_hqvdp_ops = अणु
	.bind = sti_hqvdp_bind,
	.unbind = sti_hqvdp_unbind,
पूर्ण;

अटल पूर्णांक sti_hqvdp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *vtg_np;
	काष्ठा sti_hqvdp *hqvdp;
	काष्ठा resource *res;

	DRM_DEBUG_DRIVER("\n");

	hqvdp = devm_kzalloc(dev, माप(*hqvdp), GFP_KERNEL);
	अगर (!hqvdp) अणु
		DRM_ERROR("Failed to allocate HQVDP context\n");
		वापस -ENOMEM;
	पूर्ण

	hqvdp->dev = dev;

	/* Get Memory resources */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		DRM_ERROR("Get memory resource failed\n");
		वापस -ENXIO;
	पूर्ण
	hqvdp->regs = devm_ioremap(dev, res->start, resource_size(res));
	अगर (!hqvdp->regs) अणु
		DRM_ERROR("Register mapping failed\n");
		वापस -ENXIO;
	पूर्ण

	/* Get घड़ी resources */
	hqvdp->clk = devm_clk_get(dev, "hqvdp");
	hqvdp->clk_pix_मुख्य = devm_clk_get(dev, "pix_main");
	अगर (IS_ERR(hqvdp->clk) || IS_ERR(hqvdp->clk_pix_मुख्य)) अणु
		DRM_ERROR("Cannot get clocks\n");
		वापस -ENXIO;
	पूर्ण

	/* Get reset resources */
	hqvdp->reset = devm_reset_control_get(dev, "hqvdp");
	अगर (!IS_ERR(hqvdp->reset))
		reset_control_deनिश्चित(hqvdp->reset);

	vtg_np = of_parse_phandle(pdev->dev.of_node, "st,vtg", 0);
	अगर (vtg_np)
		hqvdp->vtg = of_vtg_find(vtg_np);
	of_node_put(vtg_np);

	platक्रमm_set_drvdata(pdev, hqvdp);

	वापस component_add(&pdev->dev, &sti_hqvdp_ops);
पूर्ण

अटल पूर्णांक sti_hqvdp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &sti_hqvdp_ops);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id hqvdp_of_match[] = अणु
	अणु .compatible = "st,stih407-hqvdp", पूर्ण,
	अणु /* end node */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, hqvdp_of_match);

काष्ठा platक्रमm_driver sti_hqvdp_driver = अणु
	.driver = अणु
		.name = "sti-hqvdp",
		.owner = THIS_MODULE,
		.of_match_table = hqvdp_of_match,
	पूर्ण,
	.probe = sti_hqvdp_probe,
	.हटाओ = sti_hqvdp_हटाओ,
पूर्ण;

MODULE_AUTHOR("Benjamin Gaignard <benjamin.gaignard@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SoC DRM driver");
MODULE_LICENSE("GPL");
