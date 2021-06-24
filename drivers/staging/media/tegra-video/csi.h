<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2020 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित __TEGRA_CSI_H__
#घोषणा __TEGRA_CSI_H__

#समावेश <media/media-entity.h>
#समावेश <media/v4l2-async.h>
#समावेश <media/v4l2-subdev.h>

/*
 * Each CSI brick supports max of 4 lanes that can be used as either
 * one x4 port using both CILA and CILB partitions of a CSI brick or can
 * be used as two x2 ports with one x2 from CILA and the other x2 from
 * CILB.
 */
#घोषणा CSI_PORTS_PER_BRICK	2
#घोषणा CSI_LANES_PER_BRICK	4

/* Maximum 2 CSI x4 ports can be ganged up क्रम streaming */
#घोषणा GANG_PORTS_MAX	2

/* each CSI channel can have one sink and one source pads */
#घोषणा TEGRA_CSI_PADS_NUM	2

क्रमागत tegra_csi_cil_port अणु
	PORT_A = 0,
	PORT_B,
पूर्ण;

क्रमागत tegra_csi_block अणु
	CSI_CIL_AB = 0,
	CSI_CIL_CD,
	CSI_CIL_EF,
पूर्ण;

काष्ठा tegra_csi;

/**
 * काष्ठा tegra_csi_channel - Tegra CSI channel
 *
 * @list: list head क्रम this entry
 * @subdev: V4L2 subdevice associated with this channel
 * @pads: media pads क्रम the subdevice entity
 * @numpads: number of pads.
 * @csi: Tegra CSI device काष्ठाure
 * @of_node: csi device tree node
 * @numgangports: number of immediate ports ganged up to meet the
 *             channel bus-width
 * @numlanes: number of lanes used per port
 * @csi_port_nums: CSI channel port numbers
 * @pg_mode: test pattern generator mode क्रम channel
 * @क्रमmat: active क्रमmat of the channel
 * @framerate: active framerate क्रम TPG
 * @h_blank: horizontal blanking क्रम TPG active क्रमmat
 * @v_blank: vertical blanking क्रम TPG active क्रमmat
 * @mipi: mipi device क्रम corresponding csi channel pads
 * @pixel_rate: active pixel rate from the sensor on this channel
 */
काष्ठा tegra_csi_channel अणु
	काष्ठा list_head list;
	काष्ठा v4l2_subdev subdev;
	काष्ठा media_pad pads[TEGRA_CSI_PADS_NUM];
	अचिन्हित पूर्णांक numpads;
	काष्ठा tegra_csi *csi;
	काष्ठा device_node *of_node;
	u8 numgangports;
	अचिन्हित पूर्णांक numlanes;
	u8 csi_port_nums[GANG_PORTS_MAX];
	u8 pg_mode;
	काष्ठा v4l2_mbus_framefmt क्रमmat;
	अचिन्हित पूर्णांक framerate;
	अचिन्हित पूर्णांक h_blank;
	अचिन्हित पूर्णांक v_blank;
	काष्ठा tegra_mipi_device *mipi;
	अचिन्हित पूर्णांक pixel_rate;
पूर्ण;

/**
 * काष्ठा tpg_framerate - Tegra CSI TPG framerate configuration
 *
 * @frmsize: frame resolution
 * @code: media bus क्रमmat code
 * @h_blank: horizontal blanking used क्रम TPG
 * @v_blank: vertical blanking पूर्णांकerval used क्रम TPG
 * @framerate: framerate achieved with the corresponding blanking पूर्णांकervals,
 *		क्रमmat and resolution.
 */
काष्ठा tpg_framerate अणु
	काष्ठा v4l2_frmsize_discrete frmsize;
	u32 code;
	अचिन्हित पूर्णांक h_blank;
	अचिन्हित पूर्णांक v_blank;
	अचिन्हित पूर्णांक framerate;
पूर्ण;

/**
 * काष्ठा tegra_csi_ops - Tegra CSI operations
 *
 * @csi_start_streaming: programs csi hardware to enable streaming.
 * @csi_stop_streaming: programs csi hardware to disable streaming.
 * @csi_err_recover: csi hardware block recovery in हाल of any capture errors
 *		due to missing source stream or due to improper csi input from
 *		the बाह्यal source.
 */
काष्ठा tegra_csi_ops अणु
	पूर्णांक (*csi_start_streaming)(काष्ठा tegra_csi_channel *csi_chan);
	व्योम (*csi_stop_streaming)(काष्ठा tegra_csi_channel *csi_chan);
	व्योम (*csi_err_recover)(काष्ठा tegra_csi_channel *csi_chan);
पूर्ण;

/**
 * काष्ठा tegra_csi_soc - NVIDIA Tegra CSI SoC काष्ठाure
 *
 * @ops: csi hardware operations
 * @csi_max_channels: supported max streaming channels
 * @clk_names: csi and cil घड़ी names
 * @num_clks: total घड़ीs count
 * @tpg_frmrate_table: csi tpg frame rate table with blanking पूर्णांकervals
 * @tpg_frmrate_table_size: size of frame rate table
 */
काष्ठा tegra_csi_soc अणु
	स्थिर काष्ठा tegra_csi_ops *ops;
	अचिन्हित पूर्णांक csi_max_channels;
	स्थिर अक्षर * स्थिर *clk_names;
	अचिन्हित पूर्णांक num_clks;
	स्थिर काष्ठा tpg_framerate *tpg_frmrate_table;
	अचिन्हित पूर्णांक tpg_frmrate_table_size;
पूर्ण;

/**
 * काष्ठा tegra_csi - NVIDIA Tegra CSI device काष्ठाure
 *
 * @dev: device काष्ठा
 * @client: host1x_client काष्ठा
 * @iomem: रेजिस्टर base
 * @clks: घड़ी क्रम CSI and CIL
 * @soc: poपूर्णांकer to SoC data काष्ठाure
 * @ops: csi operations
 * @csi_chans: list head क्रम CSI channels
 */
काष्ठा tegra_csi अणु
	काष्ठा device *dev;
	काष्ठा host1x_client client;
	व्योम __iomem *iomem;
	काष्ठा clk_bulk_data *clks;
	स्थिर काष्ठा tegra_csi_soc *soc;
	स्थिर काष्ठा tegra_csi_ops *ops;
	काष्ठा list_head csi_chans;
पूर्ण;

#अगर defined(CONFIG_ARCH_TEGRA_210_SOC)
बाह्य स्थिर काष्ठा tegra_csi_soc tegra210_csi_soc;
#पूर्ण_अगर

व्योम tegra_csi_error_recover(काष्ठा v4l2_subdev *subdev);
व्योम tegra_csi_calc_settle_समय(काष्ठा tegra_csi_channel *csi_chan,
				u8 csi_port_num,
				u8 *clk_settle_समय,
				u8 *ths_settle_समय);
#पूर्ण_अगर
