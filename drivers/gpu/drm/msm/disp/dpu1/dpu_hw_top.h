<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2015-2018, The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _DPU_HW_TOP_H
#घोषणा _DPU_HW_TOP_H

#समावेश "dpu_hw_catalog.h"
#समावेश "dpu_hw_mdss.h"
#समावेश "dpu_hw_util.h"
#समावेश "dpu_hw_blk.h"

काष्ठा dpu_hw_mdp;

/**
 * काष्ठा traffic_shaper_cfg: traffic shaper configuration
 * @en        : enable/disable traffic shaper
 * @rd_client : true अगर पढ़ो client; false अगर ग_लिखो client
 * @client_id : client identअगरier
 * @bpc_denom : denominator of byte per clk
 * @bpc_numer : numerator of byte per clk
 */
काष्ठा traffic_shaper_cfg अणु
	bool en;
	bool rd_client;
	u32 client_id;
	u32 bpc_denom;
	u64 bpc_numer;
पूर्ण;

/**
 * काष्ठा split_pipe_cfg - pipe configuration क्रम dual display panels
 * @en        : Enable/disable dual pipe configuration
 * @mode      : Panel पूर्णांकerface mode
 * @पूर्णांकf      : Interface id क्रम मुख्य control path
 * @split_flush_en: Allows both the paths to be flushed when master path is
 *              flushed
 */
काष्ठा split_pipe_cfg अणु
	bool en;
	क्रमागत dpu_पूर्णांकf_mode mode;
	क्रमागत dpu_पूर्णांकf पूर्णांकf;
	bool split_flush_en;
पूर्ण;

/**
 * काष्ठा dpu_danger_safe_status: danger and safe status संकेतs
 * @mdp: top level status
 * @sspp: source pipe status
 */
काष्ठा dpu_danger_safe_status अणु
	u8 mdp;
	u8 sspp[SSPP_MAX];
पूर्ण;

/**
 * काष्ठा dpu_vsync_source_cfg - configure vsync source and configure the
 *                                    watchकरोg समयrs अगर required.
 * @pp_count: number of ping pongs active
 * @frame_rate: Display frame rate
 * @ppnumber: ping pong index array
 * @vsync_source: vsync source selection
 */
काष्ठा dpu_vsync_source_cfg अणु
	u32 pp_count;
	u32 frame_rate;
	u32 ppnumber[PINGPONG_MAX];
	u32 vsync_source;
पूर्ण;

/**
 * काष्ठा dpu_hw_mdp_ops - पूर्णांकerface to the MDP TOP Hw driver functions
 * Assumption is these functions will be called after घड़ीs are enabled.
 * @setup_split_pipe : Programs the pipe control रेजिस्टरs
 * @setup_pp_split : Programs the pp split control रेजिस्टरs
 * @setup_traffic_shaper : programs traffic shaper control
 */
काष्ठा dpu_hw_mdp_ops अणु
	/** setup_split_pipe() : Registers are not द्विगुन buffered, thisk
	 * function should be called beक्रमe timing control enable
	 * @mdp  : mdp top context driver
	 * @cfg  : upper and lower part of pipe configuration
	 */
	व्योम (*setup_split_pipe)(काष्ठा dpu_hw_mdp *mdp,
			काष्ठा split_pipe_cfg *p);

	/**
	 * setup_traffic_shaper() : Setup traffic shaper control
	 * @mdp  : mdp top context driver
	 * @cfg  : traffic shaper configuration
	 */
	व्योम (*setup_traffic_shaper)(काष्ठा dpu_hw_mdp *mdp,
			काष्ठा traffic_shaper_cfg *cfg);

	/**
	 * setup_clk_क्रमce_ctrl - set घड़ी क्रमce control
	 * @mdp: mdp top context driver
	 * @clk_ctrl: घड़ी to be controlled
	 * @enable: क्रमce on enable
	 * @वापस: अगर the घड़ी is क्रमced-on by this function
	 */
	bool (*setup_clk_क्रमce_ctrl)(काष्ठा dpu_hw_mdp *mdp,
			क्रमागत dpu_clk_ctrl_type clk_ctrl, bool enable);

	/**
	 * get_danger_status - get danger status
	 * @mdp: mdp top context driver
	 * @status: Poपूर्णांकer to danger safe status
	 */
	व्योम (*get_danger_status)(काष्ठा dpu_hw_mdp *mdp,
			काष्ठा dpu_danger_safe_status *status);

	/**
	 * setup_vsync_source - setup vsync source configuration details
	 * @mdp: mdp top context driver
	 * @cfg: vsync source selection configuration
	 */
	व्योम (*setup_vsync_source)(काष्ठा dpu_hw_mdp *mdp,
				काष्ठा dpu_vsync_source_cfg *cfg);

	/**
	 * get_safe_status - get safe status
	 * @mdp: mdp top context driver
	 * @status: Poपूर्णांकer to danger safe status
	 */
	व्योम (*get_safe_status)(काष्ठा dpu_hw_mdp *mdp,
			काष्ठा dpu_danger_safe_status *status);

	/**
	 * पूर्णांकf_audio_select - select the बाह्यal पूर्णांकerface क्रम audio
	 * @mdp: mdp top context driver
	 */
	व्योम (*पूर्णांकf_audio_select)(काष्ठा dpu_hw_mdp *mdp);
पूर्ण;

काष्ठा dpu_hw_mdp अणु
	काष्ठा dpu_hw_blk base;
	काष्ठा dpu_hw_blk_reg_map hw;

	/* top */
	क्रमागत dpu_mdp idx;
	स्थिर काष्ठा dpu_mdp_cfg *caps;

	/* ops */
	काष्ठा dpu_hw_mdp_ops ops;
पूर्ण;

/**
 * dpu_hw_mdptop_init - initializes the top driver क्रम the passed idx
 * @idx:  Interface index क्रम which driver object is required
 * @addr: Mapped रेजिस्टर io address of MDP
 * @m:    Poपूर्णांकer to mdss catalog data
 */
काष्ठा dpu_hw_mdp *dpu_hw_mdptop_init(क्रमागत dpu_mdp idx,
		व्योम __iomem *addr,
		स्थिर काष्ठा dpu_mdss_cfg *m);

व्योम dpu_hw_mdp_destroy(काष्ठा dpu_hw_mdp *mdp);

#पूर्ण_अगर /*_DPU_HW_TOP_H */
