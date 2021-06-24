<शैली गुरु>
/*
 * Copyright 2005-2009 Freescale Semiconductor, Inc.
 *
 * The code contained herein is licensed under the GNU Lesser General
 * Public License.  You may obtain a copy of the GNU Lesser General
 * Public License Version 2.1 or later at the following locations:
 *
 * http://www.खोलोsource.org/licenses/lgpl-license.hपंचांगl
 * http://www.gnu.org/copyleft/lgpl.hपंचांगl
 */

#अगर_अघोषित __DRM_IPU_H__
#घोषणा __DRM_IPU_H__

#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/biपंचांगap.h>
#समावेश <linux/fb.h>
#समावेश <linux/of.h>
#समावेश <media/v4l2-mediabus.h>
#समावेश <video/videomode.h>

काष्ठा ipu_soc;

क्रमागत ipuv3_type अणु
	IPUV3EX,
	IPUV3M,
	IPUV3H,
पूर्ण;

#घोषणा IPU_PIX_FMT_GBR24	v4l2_fourcc('G', 'B', 'R', '3')

/*
 * Bitfield of Display Interface संकेत polarities.
 */
काष्ठा ipu_di_संकेत_cfg अणु
	अचिन्हित data_pol:1;	/* true = inverted */
	अचिन्हित clk_pol:1;	/* true = rising edge */
	अचिन्हित enable_pol:1;

	काष्ठा videomode mode;

	u32 bus_क्रमmat;
	u32 v_to_h_sync;

#घोषणा IPU_DI_CLKMODE_SYNC	(1 << 0)
#घोषणा IPU_DI_CLKMODE_EXT	(1 << 1)
	अचिन्हित दीर्घ clkflags;

	u8 hsync_pin;
	u8 vsync_pin;
पूर्ण;

/*
 * Enumeration of CSI destinations
 */
क्रमागत ipu_csi_dest अणु
	IPU_CSI_DEST_IDMAC, /* to memory via SMFC */
	IPU_CSI_DEST_IC,	/* to Image Converter */
	IPU_CSI_DEST_VDIC,  /* to VDIC */
पूर्ण;

/*
 * Enumeration of IPU rotation modes
 */
#घोषणा IPU_ROT_BIT_VFLIP (1 << 0)
#घोषणा IPU_ROT_BIT_HFLIP (1 << 1)
#घोषणा IPU_ROT_BIT_90    (1 << 2)

क्रमागत ipu_rotate_mode अणु
	IPU_ROTATE_NONE = 0,
	IPU_ROTATE_VERT_FLIP = IPU_ROT_BIT_VFLIP,
	IPU_ROTATE_HORIZ_FLIP = IPU_ROT_BIT_HFLIP,
	IPU_ROTATE_180 = (IPU_ROT_BIT_VFLIP | IPU_ROT_BIT_HFLIP),
	IPU_ROTATE_90_RIGHT = IPU_ROT_BIT_90,
	IPU_ROTATE_90_RIGHT_VFLIP = (IPU_ROT_BIT_90 | IPU_ROT_BIT_VFLIP),
	IPU_ROTATE_90_RIGHT_HFLIP = (IPU_ROT_BIT_90 | IPU_ROT_BIT_HFLIP),
	IPU_ROTATE_90_LEFT = (IPU_ROT_BIT_90 |
			      IPU_ROT_BIT_VFLIP | IPU_ROT_BIT_HFLIP),
पूर्ण;

/* 90-degree rotations require the IRT unit */
#घोषणा ipu_rot_mode_is_irt(m) (((m) & IPU_ROT_BIT_90) != 0)

क्रमागत ipu_color_space अणु
	IPUV3_COLORSPACE_RGB,
	IPUV3_COLORSPACE_YUV,
	IPUV3_COLORSPACE_UNKNOWN,
पूर्ण;

/*
 * Enumeration of VDI MOTION select
 */
क्रमागत ipu_motion_sel अणु
	MOTION_NONE = 0,
	LOW_MOTION,
	MED_MOTION,
	HIGH_MOTION,
पूर्ण;

काष्ठा ipuv3_channel;

क्रमागत ipu_channel_irq अणु
	IPU_IRQ_खातापूर्ण = 0,
	IPU_IRQ_NFACK = 64,
	IPU_IRQ_NFB4खातापूर्ण = 128,
	IPU_IRQ_EOS = 192,
पूर्ण;

/*
 * Enumeration of IDMAC channels
 */
#घोषणा IPUV3_CHANNEL_CSI0			 0
#घोषणा IPUV3_CHANNEL_CSI1			 1
#घोषणा IPUV3_CHANNEL_CSI2			 2
#घोषणा IPUV3_CHANNEL_CSI3			 3
#घोषणा IPUV3_CHANNEL_VDI_MEM_IC_VF		 5
/*
 * NOTE: channels 6,7 are unused in the IPU and are not IDMAC channels,
 * but the direct CSI->VDI linking is handled the same way as IDMAC
 * channel linking in the FSU via the IPU_FS_PROC_FLOW रेजिस्टरs, so
 * these channel names are used to support the direct CSI->VDI link.
 */
#घोषणा IPUV3_CHANNEL_CSI_सूचीECT		 6
#घोषणा IPUV3_CHANNEL_CSI_VDI_PREV		 7
#घोषणा IPUV3_CHANNEL_MEM_VDI_PREV		 8
#घोषणा IPUV3_CHANNEL_MEM_VDI_CUR		 9
#घोषणा IPUV3_CHANNEL_MEM_VDI_NEXT		10
#घोषणा IPUV3_CHANNEL_MEM_IC_PP			11
#घोषणा IPUV3_CHANNEL_MEM_IC_PRP_VF		12
#घोषणा IPUV3_CHANNEL_VDI_MEM_RECENT		13
#घोषणा IPUV3_CHANNEL_G_MEM_IC_PRP_VF		14
#घोषणा IPUV3_CHANNEL_G_MEM_IC_PP		15
#घोषणा IPUV3_CHANNEL_G_MEM_IC_PRP_VF_ALPHA	17
#घोषणा IPUV3_CHANNEL_G_MEM_IC_PP_ALPHA		18
#घोषणा IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB_ALPHA	19
#घोषणा IPUV3_CHANNEL_IC_PRP_ENC_MEM		20
#घोषणा IPUV3_CHANNEL_IC_PRP_VF_MEM		21
#घोषणा IPUV3_CHANNEL_IC_PP_MEM			22
#घोषणा IPUV3_CHANNEL_MEM_BG_SYNC		23
#घोषणा IPUV3_CHANNEL_MEM_BG_ASYNC		24
#घोषणा IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB	25
#घोषणा IPUV3_CHANNEL_MEM_VDI_PLANE3_COMB	26
#घोषणा IPUV3_CHANNEL_MEM_FG_SYNC		27
#घोषणा IPUV3_CHANNEL_MEM_DC_SYNC		28
#घोषणा IPUV3_CHANNEL_MEM_FG_ASYNC		29
#घोषणा IPUV3_CHANNEL_MEM_FG_SYNC_ALPHA		31
#घोषणा IPUV3_CHANNEL_MEM_FG_ASYNC_ALPHA	33
#घोषणा IPUV3_CHANNEL_DC_MEM_READ		40
#घोषणा IPUV3_CHANNEL_MEM_DC_ASYNC		41
#घोषणा IPUV3_CHANNEL_MEM_DC_COMMAND		42
#घोषणा IPUV3_CHANNEL_MEM_DC_COMMAND2		43
#घोषणा IPUV3_CHANNEL_MEM_DC_OUTPUT_MASK	44
#घोषणा IPUV3_CHANNEL_MEM_ROT_ENC		45
#घोषणा IPUV3_CHANNEL_MEM_ROT_VF		46
#घोषणा IPUV3_CHANNEL_MEM_ROT_PP		47
#घोषणा IPUV3_CHANNEL_ROT_ENC_MEM		48
#घोषणा IPUV3_CHANNEL_ROT_VF_MEM		49
#घोषणा IPUV3_CHANNEL_ROT_PP_MEM		50
#घोषणा IPUV3_CHANNEL_MEM_BG_SYNC_ALPHA		51
#घोषणा IPUV3_CHANNEL_MEM_BG_ASYNC_ALPHA	52
#घोषणा IPUV3_NUM_CHANNELS			64

अटल अंतरभूत पूर्णांक ipu_channel_alpha_channel(पूर्णांक ch_num)
अणु
	चयन (ch_num) अणु
	हाल IPUV3_CHANNEL_G_MEM_IC_PRP_VF:
		वापस IPUV3_CHANNEL_G_MEM_IC_PRP_VF_ALPHA;
	हाल IPUV3_CHANNEL_G_MEM_IC_PP:
		वापस IPUV3_CHANNEL_G_MEM_IC_PP_ALPHA;
	हाल IPUV3_CHANNEL_MEM_FG_SYNC:
		वापस IPUV3_CHANNEL_MEM_FG_SYNC_ALPHA;
	हाल IPUV3_CHANNEL_MEM_FG_ASYNC:
		वापस IPUV3_CHANNEL_MEM_FG_ASYNC_ALPHA;
	हाल IPUV3_CHANNEL_MEM_BG_SYNC:
		वापस IPUV3_CHANNEL_MEM_BG_SYNC_ALPHA;
	हाल IPUV3_CHANNEL_MEM_BG_ASYNC:
		वापस IPUV3_CHANNEL_MEM_BG_ASYNC_ALPHA;
	हाल IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB:
		वापस IPUV3_CHANNEL_MEM_VDI_PLANE1_COMB_ALPHA;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक ipu_map_irq(काष्ठा ipu_soc *ipu, पूर्णांक irq);
पूर्णांक ipu_idmac_channel_irq(काष्ठा ipu_soc *ipu, काष्ठा ipuv3_channel *channel,
		क्रमागत ipu_channel_irq irq);

#घोषणा IPU_IRQ_DP_SF_START		(448 + 2)
#घोषणा IPU_IRQ_DP_SF_END		(448 + 3)
#घोषणा IPU_IRQ_BG_SF_END		IPU_IRQ_DP_SF_END,
#घोषणा IPU_IRQ_DC_FC_0			(448 + 8)
#घोषणा IPU_IRQ_DC_FC_1			(448 + 9)
#घोषणा IPU_IRQ_DC_FC_2			(448 + 10)
#घोषणा IPU_IRQ_DC_FC_3			(448 + 11)
#घोषणा IPU_IRQ_DC_FC_4			(448 + 12)
#घोषणा IPU_IRQ_DC_FC_6			(448 + 13)
#घोषणा IPU_IRQ_VSYNC_PRE_0		(448 + 14)
#घोषणा IPU_IRQ_VSYNC_PRE_1		(448 + 15)

/*
 * IPU Common functions
 */
पूर्णांक ipu_get_num(काष्ठा ipu_soc *ipu);
व्योम ipu_set_csi_src_mux(काष्ठा ipu_soc *ipu, पूर्णांक csi_id, bool mipi_csi2);
व्योम ipu_set_ic_src_mux(काष्ठा ipu_soc *ipu, पूर्णांक csi_id, bool vdi);
व्योम ipu_dump(काष्ठा ipu_soc *ipu);

/*
 * IPU Image DMA Controller (idmac) functions
 */
काष्ठा ipuv3_channel *ipu_idmac_get(काष्ठा ipu_soc *ipu, अचिन्हित channel);
व्योम ipu_idmac_put(काष्ठा ipuv3_channel *);

पूर्णांक ipu_idmac_enable_channel(काष्ठा ipuv3_channel *channel);
पूर्णांक ipu_idmac_disable_channel(काष्ठा ipuv3_channel *channel);
व्योम ipu_idmac_enable_watermark(काष्ठा ipuv3_channel *channel, bool enable);
पूर्णांक ipu_idmac_lock_enable(काष्ठा ipuv3_channel *channel, पूर्णांक num_bursts);
पूर्णांक ipu_idmac_रुको_busy(काष्ठा ipuv3_channel *channel, पूर्णांक ms);

व्योम ipu_idmac_set_द्विगुन_buffer(काष्ठा ipuv3_channel *channel,
		bool द्विगुनbuffer);
पूर्णांक ipu_idmac_get_current_buffer(काष्ठा ipuv3_channel *channel);
bool ipu_idmac_buffer_is_पढ़ोy(काष्ठा ipuv3_channel *channel, u32 buf_num);
व्योम ipu_idmac_select_buffer(काष्ठा ipuv3_channel *channel, u32 buf_num);
व्योम ipu_idmac_clear_buffer(काष्ठा ipuv3_channel *channel, u32 buf_num);
पूर्णांक ipu_fsu_link(काष्ठा ipu_soc *ipu, पूर्णांक src_ch, पूर्णांक sink_ch);
पूर्णांक ipu_fsu_unlink(काष्ठा ipu_soc *ipu, पूर्णांक src_ch, पूर्णांक sink_ch);
पूर्णांक ipu_idmac_link(काष्ठा ipuv3_channel *src, काष्ठा ipuv3_channel *sink);
पूर्णांक ipu_idmac_unlink(काष्ठा ipuv3_channel *src, काष्ठा ipuv3_channel *sink);

/*
 * IPU Channel Parameter Memory (cpmem) functions
 */
काष्ठा ipu_rgb अणु
	काष्ठा fb_bitfield      red;
	काष्ठा fb_bitfield      green;
	काष्ठा fb_bitfield      blue;
	काष्ठा fb_bitfield      transp;
	पूर्णांक                     bits_per_pixel;
पूर्ण;

काष्ठा ipu_image अणु
	काष्ठा v4l2_pix_क्रमmat pix;
	काष्ठा v4l2_rect rect;
	dma_addr_t phys0;
	dma_addr_t phys1;
	/* chroma plane offset overrides */
	u32 u_offset;
	u32 v_offset;
पूर्ण;

व्योम ipu_cpmem_zero(काष्ठा ipuv3_channel *ch);
व्योम ipu_cpmem_set_resolution(काष्ठा ipuv3_channel *ch, पूर्णांक xres, पूर्णांक yres);
व्योम ipu_cpmem_skip_odd_chroma_rows(काष्ठा ipuv3_channel *ch);
व्योम ipu_cpmem_set_stride(काष्ठा ipuv3_channel *ch, पूर्णांक stride);
व्योम ipu_cpmem_set_high_priority(काष्ठा ipuv3_channel *ch);
व्योम ipu_cpmem_set_buffer(काष्ठा ipuv3_channel *ch, पूर्णांक bufnum, dma_addr_t buf);
व्योम ipu_cpmem_set_uv_offset(काष्ठा ipuv3_channel *ch, u32 u_off, u32 v_off);
व्योम ipu_cpmem_पूर्णांकerlaced_scan(काष्ठा ipuv3_channel *ch, पूर्णांक stride,
			       u32 pixelक्रमmat);
व्योम ipu_cpmem_set_axi_id(काष्ठा ipuv3_channel *ch, u32 id);
पूर्णांक ipu_cpmem_get_burstsize(काष्ठा ipuv3_channel *ch);
व्योम ipu_cpmem_set_burstsize(काष्ठा ipuv3_channel *ch, पूर्णांक burstsize);
व्योम ipu_cpmem_set_block_mode(काष्ठा ipuv3_channel *ch);
व्योम ipu_cpmem_set_rotation(काष्ठा ipuv3_channel *ch,
			    क्रमागत ipu_rotate_mode rot);
पूर्णांक ipu_cpmem_set_क्रमmat_rgb(काष्ठा ipuv3_channel *ch,
			     स्थिर काष्ठा ipu_rgb *rgb);
पूर्णांक ipu_cpmem_set_क्रमmat_passthrough(काष्ठा ipuv3_channel *ch, पूर्णांक width);
व्योम ipu_cpmem_set_yuv_पूर्णांकerleaved(काष्ठा ipuv3_channel *ch, u32 pixel_क्रमmat);
व्योम ipu_cpmem_set_yuv_planar_full(काष्ठा ipuv3_channel *ch,
				   अचिन्हित पूर्णांक uv_stride,
				   अचिन्हित पूर्णांक u_offset,
				   अचिन्हित पूर्णांक v_offset);
पूर्णांक ipu_cpmem_set_fmt(काष्ठा ipuv3_channel *ch, u32 drm_fourcc);
पूर्णांक ipu_cpmem_set_image(काष्ठा ipuv3_channel *ch, काष्ठा ipu_image *image);
व्योम ipu_cpmem_dump(काष्ठा ipuv3_channel *ch);

/*
 * IPU Display Controller (dc) functions
 */
काष्ठा ipu_dc;
काष्ठा ipu_di;
काष्ठा ipu_dc *ipu_dc_get(काष्ठा ipu_soc *ipu, पूर्णांक channel);
व्योम ipu_dc_put(काष्ठा ipu_dc *dc);
पूर्णांक ipu_dc_init_sync(काष्ठा ipu_dc *dc, काष्ठा ipu_di *di, bool पूर्णांकerlaced,
		u32 pixel_fmt, u32 width);
व्योम ipu_dc_enable(काष्ठा ipu_soc *ipu);
व्योम ipu_dc_enable_channel(काष्ठा ipu_dc *dc);
व्योम ipu_dc_disable_channel(काष्ठा ipu_dc *dc);
व्योम ipu_dc_disable(काष्ठा ipu_soc *ipu);

/*
 * IPU Display Interface (di) functions
 */
काष्ठा ipu_di *ipu_di_get(काष्ठा ipu_soc *ipu, पूर्णांक disp);
व्योम ipu_di_put(काष्ठा ipu_di *);
पूर्णांक ipu_di_disable(काष्ठा ipu_di *);
पूर्णांक ipu_di_enable(काष्ठा ipu_di *);
पूर्णांक ipu_di_get_num(काष्ठा ipu_di *);
पूर्णांक ipu_di_adjust_videomode(काष्ठा ipu_di *di, काष्ठा videomode *mode);
पूर्णांक ipu_di_init_sync_panel(काष्ठा ipu_di *, काष्ठा ipu_di_संकेत_cfg *sig);

/*
 * IPU Display Multi FIFO Controller (dmfc) functions
 */
काष्ठा dmfc_channel;
पूर्णांक ipu_dmfc_enable_channel(काष्ठा dmfc_channel *dmfc);
व्योम ipu_dmfc_disable_channel(काष्ठा dmfc_channel *dmfc);
व्योम ipu_dmfc_config_रुको4eot(काष्ठा dmfc_channel *dmfc, पूर्णांक width);
काष्ठा dmfc_channel *ipu_dmfc_get(काष्ठा ipu_soc *ipu, पूर्णांक ipuv3_channel);
व्योम ipu_dmfc_put(काष्ठा dmfc_channel *dmfc);

/*
 * IPU Display Processor (dp) functions
 */
#घोषणा IPU_DP_FLOW_SYNC_BG	0
#घोषणा IPU_DP_FLOW_SYNC_FG	1
#घोषणा IPU_DP_FLOW_ASYNC0_BG	2
#घोषणा IPU_DP_FLOW_ASYNC0_FG	3
#घोषणा IPU_DP_FLOW_ASYNC1_BG	4
#घोषणा IPU_DP_FLOW_ASYNC1_FG	5

काष्ठा ipu_dp *ipu_dp_get(काष्ठा ipu_soc *ipu, अचिन्हित पूर्णांक flow);
व्योम ipu_dp_put(काष्ठा ipu_dp *);
पूर्णांक ipu_dp_enable(काष्ठा ipu_soc *ipu);
पूर्णांक ipu_dp_enable_channel(काष्ठा ipu_dp *dp);
व्योम ipu_dp_disable_channel(काष्ठा ipu_dp *dp, bool sync);
व्योम ipu_dp_disable(काष्ठा ipu_soc *ipu);
पूर्णांक ipu_dp_setup_channel(काष्ठा ipu_dp *dp,
		क्रमागत ipu_color_space in, क्रमागत ipu_color_space out);
पूर्णांक ipu_dp_set_winकरोw_pos(काष्ठा ipu_dp *, u16 x_pos, u16 y_pos);
पूर्णांक ipu_dp_set_global_alpha(काष्ठा ipu_dp *dp, bool enable, u8 alpha,
		bool bg_chan);

/*
 * IPU Prefetch Resolve Gasket (prg) functions
 */
पूर्णांक ipu_prg_max_active_channels(व्योम);
bool ipu_prg_present(काष्ठा ipu_soc *ipu);
bool ipu_prg_क्रमmat_supported(काष्ठा ipu_soc *ipu, uपूर्णांक32_t क्रमmat,
			      uपूर्णांक64_t modअगरier);
पूर्णांक ipu_prg_enable(काष्ठा ipu_soc *ipu);
व्योम ipu_prg_disable(काष्ठा ipu_soc *ipu);
व्योम ipu_prg_channel_disable(काष्ठा ipuv3_channel *ipu_chan);
पूर्णांक ipu_prg_channel_configure(काष्ठा ipuv3_channel *ipu_chan,
			      अचिन्हित पूर्णांक axi_id,  अचिन्हित पूर्णांक width,
			      अचिन्हित पूर्णांक height, अचिन्हित पूर्णांक stride,
			      u32 क्रमmat, uपूर्णांक64_t modअगरier, अचिन्हित दीर्घ *eba);
bool ipu_prg_channel_configure_pending(काष्ठा ipuv3_channel *ipu_chan);

/*
 * IPU CMOS Sensor Interface (csi) functions
 */
काष्ठा ipu_csi;
पूर्णांक ipu_csi_init_पूर्णांकerface(काष्ठा ipu_csi *csi,
			   स्थिर काष्ठा v4l2_mbus_config *mbus_cfg,
			   स्थिर काष्ठा v4l2_mbus_framefmt *infmt,
			   स्थिर काष्ठा v4l2_mbus_framefmt *outfmt);
bool ipu_csi_is_पूर्णांकerlaced(काष्ठा ipu_csi *csi);
व्योम ipu_csi_get_winकरोw(काष्ठा ipu_csi *csi, काष्ठा v4l2_rect *w);
व्योम ipu_csi_set_winकरोw(काष्ठा ipu_csi *csi, काष्ठा v4l2_rect *w);
व्योम ipu_csi_set_करोwnsize(काष्ठा ipu_csi *csi, bool horiz, bool vert);
व्योम ipu_csi_set_test_generator(काष्ठा ipu_csi *csi, bool active,
				u32 r_value, u32 g_value, u32 b_value,
				u32 pix_clk);
पूर्णांक ipu_csi_set_mipi_datatype(काष्ठा ipu_csi *csi, u32 vc,
			      काष्ठा v4l2_mbus_framefmt *mbus_fmt);
पूर्णांक ipu_csi_set_skip_smfc(काष्ठा ipu_csi *csi, u32 skip,
			  u32 max_ratio, u32 id);
पूर्णांक ipu_csi_set_dest(काष्ठा ipu_csi *csi, क्रमागत ipu_csi_dest csi_dest);
पूर्णांक ipu_csi_enable(काष्ठा ipu_csi *csi);
पूर्णांक ipu_csi_disable(काष्ठा ipu_csi *csi);
काष्ठा ipu_csi *ipu_csi_get(काष्ठा ipu_soc *ipu, पूर्णांक id);
व्योम ipu_csi_put(काष्ठा ipu_csi *csi);
व्योम ipu_csi_dump(काष्ठा ipu_csi *csi);

/*
 * IPU Image Converter (ic) functions
 */
क्रमागत ipu_ic_task अणु
	IC_TASK_ENCODER,
	IC_TASK_VIEWFINDER,
	IC_TASK_POST_PROCESSOR,
	IC_NUM_TASKS,
पूर्ण;

/*
 * The parameters that describe a colorspace according to the
 * Image Converter:
 *    - Y'CbCr encoding
 *    - quantization
 *    - "colorspace" (RGB or YUV).
 */
काष्ठा ipu_ic_colorspace अणु
	क्रमागत v4l2_ycbcr_encoding enc;
	क्रमागत v4l2_quantization quant;
	क्रमागत ipu_color_space cs;
पूर्ण;

अटल अंतरभूत व्योम
ipu_ic_fill_colorspace(काष्ठा ipu_ic_colorspace *ic_cs,
		       क्रमागत v4l2_ycbcr_encoding enc,
		       क्रमागत v4l2_quantization quant,
		       क्रमागत ipu_color_space cs)
अणु
	ic_cs->enc = enc;
	ic_cs->quant = quant;
	ic_cs->cs = cs;
पूर्ण

काष्ठा ipu_ic_csc_params अणु
	s16 coeff[3][3];	/* चिन्हित 9-bit पूर्णांकeger coefficients */
	s16 offset[3];		/* चिन्हित 11+2-bit fixed poपूर्णांक offset */
	u8 scale:2;		/* scale coefficients * 2^(scale-1) */
	bool sat:1;		/* saturate to (16, 235(Y) / 240(U, V)) */
पूर्ण;

काष्ठा ipu_ic_csc अणु
	काष्ठा ipu_ic_colorspace in_cs;
	काष्ठा ipu_ic_colorspace out_cs;
	काष्ठा ipu_ic_csc_params params;
पूर्ण;

काष्ठा ipu_ic;

पूर्णांक __ipu_ic_calc_csc(काष्ठा ipu_ic_csc *csc);
पूर्णांक ipu_ic_calc_csc(काष्ठा ipu_ic_csc *csc,
		    क्रमागत v4l2_ycbcr_encoding in_enc,
		    क्रमागत v4l2_quantization in_quant,
		    क्रमागत ipu_color_space in_cs,
		    क्रमागत v4l2_ycbcr_encoding out_enc,
		    क्रमागत v4l2_quantization out_quant,
		    क्रमागत ipu_color_space out_cs);
पूर्णांक ipu_ic_task_init(काष्ठा ipu_ic *ic,
		     स्थिर काष्ठा ipu_ic_csc *csc,
		     पूर्णांक in_width, पूर्णांक in_height,
		     पूर्णांक out_width, पूर्णांक out_height);
पूर्णांक ipu_ic_task_init_rsc(काष्ठा ipu_ic *ic,
			 स्थिर काष्ठा ipu_ic_csc *csc,
			 पूर्णांक in_width, पूर्णांक in_height,
			 पूर्णांक out_width, पूर्णांक out_height,
			 u32 rsc);
पूर्णांक ipu_ic_task_graphics_init(काष्ठा ipu_ic *ic,
			      स्थिर काष्ठा ipu_ic_colorspace *g_in_cs,
			      bool galpha_en, u32 galpha,
			      bool colorkey_en, u32 colorkey);
व्योम ipu_ic_task_enable(काष्ठा ipu_ic *ic);
व्योम ipu_ic_task_disable(काष्ठा ipu_ic *ic);
पूर्णांक ipu_ic_task_idma_init(काष्ठा ipu_ic *ic, काष्ठा ipuv3_channel *channel,
			  u32 width, u32 height, पूर्णांक burst_size,
			  क्रमागत ipu_rotate_mode rot);
पूर्णांक ipu_ic_enable(काष्ठा ipu_ic *ic);
पूर्णांक ipu_ic_disable(काष्ठा ipu_ic *ic);
काष्ठा ipu_ic *ipu_ic_get(काष्ठा ipu_soc *ipu, क्रमागत ipu_ic_task task);
व्योम ipu_ic_put(काष्ठा ipu_ic *ic);
व्योम ipu_ic_dump(काष्ठा ipu_ic *ic);

/*
 * IPU Video De-Interlacer (vdi) functions
 */
काष्ठा ipu_vdi;
व्योम ipu_vdi_set_field_order(काष्ठा ipu_vdi *vdi, v4l2_std_id std, u32 field);
व्योम ipu_vdi_set_motion(काष्ठा ipu_vdi *vdi, क्रमागत ipu_motion_sel motion_sel);
व्योम ipu_vdi_setup(काष्ठा ipu_vdi *vdi, u32 code, पूर्णांक xres, पूर्णांक yres);
व्योम ipu_vdi_unsetup(काष्ठा ipu_vdi *vdi);
पूर्णांक ipu_vdi_enable(काष्ठा ipu_vdi *vdi);
पूर्णांक ipu_vdi_disable(काष्ठा ipu_vdi *vdi);
काष्ठा ipu_vdi *ipu_vdi_get(काष्ठा ipu_soc *ipu);
व्योम ipu_vdi_put(काष्ठा ipu_vdi *vdi);

/*
 * IPU Sensor Multiple FIFO Controller (SMFC) functions
 */
काष्ठा ipu_smfc *ipu_smfc_get(काष्ठा ipu_soc *ipu, अचिन्हित पूर्णांक chno);
व्योम ipu_smfc_put(काष्ठा ipu_smfc *smfc);
पूर्णांक ipu_smfc_enable(काष्ठा ipu_smfc *smfc);
पूर्णांक ipu_smfc_disable(काष्ठा ipu_smfc *smfc);
पूर्णांक ipu_smfc_map_channel(काष्ठा ipu_smfc *smfc, पूर्णांक csi_id, पूर्णांक mipi_id);
पूर्णांक ipu_smfc_set_burstsize(काष्ठा ipu_smfc *smfc, पूर्णांक burstsize);
पूर्णांक ipu_smfc_set_watermark(काष्ठा ipu_smfc *smfc, u32 set_level, u32 clr_level);

क्रमागत ipu_color_space ipu_drm_fourcc_to_colorspace(u32 drm_fourcc);
क्रमागत ipu_color_space ipu_pixelक्रमmat_to_colorspace(u32 pixelक्रमmat);
पूर्णांक ipu_degrees_to_rot_mode(क्रमागत ipu_rotate_mode *mode, पूर्णांक degrees,
			    bool hflip, bool vflip);
पूर्णांक ipu_rot_mode_to_degrees(पूर्णांक *degrees, क्रमागत ipu_rotate_mode mode,
			    bool hflip, bool vflip);

काष्ठा ipu_client_platक्रमmdata अणु
	पूर्णांक csi;
	पूर्णांक di;
	पूर्णांक dc;
	पूर्णांक dp;
	पूर्णांक dma[2];
	काष्ठा device_node *of_node;
पूर्ण;

#पूर्ण_अगर /* __DRM_IPU_H__ */
