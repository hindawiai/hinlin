<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright (C) 2013-2019 NVIDIA Corporation.
 * Copyright (C) 2015 Rob Clark
 */

#अगर_अघोषित DRM_TEGRA_DP_H
#घोषणा DRM_TEGRA_DP_H 1

#समावेश <linux/types.h>

काष्ठा drm_display_info;
काष्ठा drm_display_mode;
काष्ठा drm_dp_aux;
काष्ठा drm_dp_link;

/**
 * काष्ठा drm_dp_link_caps - DP link capabilities
 */
काष्ठा drm_dp_link_caps अणु
	/**
	 * @enhanced_framing:
	 *
	 * enhanced framing capability (mandatory as of DP 1.2)
	 */
	bool enhanced_framing;

	/**
	 * tps3_supported:
	 *
	 * training pattern sequence 3 supported क्रम equalization
	 */
	bool tps3_supported;

	/**
	 * @fast_training:
	 *
	 * AUX CH handshake not required क्रम link training
	 */
	bool fast_training;

	/**
	 * @channel_coding:
	 *
	 * ANSI 8B/10B channel coding capability
	 */
	bool channel_coding;

	/**
	 * @alternate_scrambler_reset:
	 *
	 * eDP alternate scrambler reset capability
	 */
	bool alternate_scrambler_reset;
पूर्ण;

व्योम drm_dp_link_caps_copy(काष्ठा drm_dp_link_caps *dest,
			   स्थिर काष्ठा drm_dp_link_caps *src);

/**
 * काष्ठा drm_dp_link_ops - DP link operations
 */
काष्ठा drm_dp_link_ops अणु
	/**
	 * @apply_training:
	 */
	पूर्णांक (*apply_training)(काष्ठा drm_dp_link *link);

	/**
	 * @configure:
	 */
	पूर्णांक (*configure)(काष्ठा drm_dp_link *link);
पूर्ण;

#घोषणा DP_TRAIN_VOLTAGE_SWING_LEVEL(x) ((x) << 0)
#घोषणा DP_TRAIN_PRE_EMPHASIS_LEVEL(x) ((x) << 3)
#घोषणा DP_LANE_POST_CURSOR(i, x) (((x) & 0x3) << (((i) & 1) << 2))

/**
 * काष्ठा drm_dp_link_train_set - link training settings
 * @voltage_swing: per-lane voltage swing
 * @pre_emphasis: per-lane pre-emphasis
 * @post_cursor: per-lane post-cursor
 */
काष्ठा drm_dp_link_train_set अणु
	अचिन्हित पूर्णांक voltage_swing[4];
	अचिन्हित पूर्णांक pre_emphasis[4];
	अचिन्हित पूर्णांक post_cursor[4];
पूर्ण;

/**
 * काष्ठा drm_dp_link_train - link training state inक्रमmation
 * @request: currently requested settings
 * @adjust: adjusपंचांगents requested by sink
 * @pattern: currently requested training pattern
 * @घड़ी_recovered: flag to track अगर घड़ी recovery has completed
 * @channel_equalized: flag to track अगर channel equalization has completed
 */
काष्ठा drm_dp_link_train अणु
	काष्ठा drm_dp_link_train_set request;
	काष्ठा drm_dp_link_train_set adjust;

	अचिन्हित पूर्णांक pattern;

	bool घड़ी_recovered;
	bool channel_equalized;
पूर्ण;

/**
 * काष्ठा drm_dp_link - DP link capabilities and configuration
 * @revision: DP specअगरication revision supported on the link
 * @max_rate: maximum घड़ी rate supported on the link
 * @max_lanes: maximum number of lanes supported on the link
 * @caps: capabilities supported on the link (see &drm_dp_link_caps)
 * @aux_rd_पूर्णांकerval: AUX पढ़ो पूर्णांकerval to use क्रम training (in microseconds)
 * @edp: eDP revision (0x11: eDP 1.1, 0x12: eDP 1.2, ...)
 * @rate: currently configured link rate
 * @lanes: currently configured number of lanes
 * @rates: additional supported link rates in kHz (eDP 1.4)
 * @num_rates: number of additional supported link rates (eDP 1.4)
 */
काष्ठा drm_dp_link अणु
	अचिन्हित अक्षर revision;
	अचिन्हित पूर्णांक max_rate;
	अचिन्हित पूर्णांक max_lanes;

	काष्ठा drm_dp_link_caps caps;

	/**
	 * @cr: घड़ी recovery पढ़ो पूर्णांकerval
	 * @ce: channel equalization पढ़ो पूर्णांकerval
	 */
	काष्ठा अणु
		अचिन्हित पूर्णांक cr;
		अचिन्हित पूर्णांक ce;
	पूर्ण aux_rd_पूर्णांकerval;

	अचिन्हित अक्षर edp;

	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक lanes;

	अचिन्हित दीर्घ rates[DP_MAX_SUPPORTED_RATES];
	अचिन्हित पूर्णांक num_rates;

	/**
	 * @ops: DP link operations
	 */
	स्थिर काष्ठा drm_dp_link_ops *ops;

	/**
	 * @aux: DP AUX channel
	 */
	काष्ठा drm_dp_aux *aux;

	/**
	 * @train: DP link training state
	 */
	काष्ठा drm_dp_link_train train;
पूर्ण;

पूर्णांक drm_dp_link_add_rate(काष्ठा drm_dp_link *link, अचिन्हित दीर्घ rate);
पूर्णांक drm_dp_link_हटाओ_rate(काष्ठा drm_dp_link *link, अचिन्हित दीर्घ rate);
व्योम drm_dp_link_update_rates(काष्ठा drm_dp_link *link);

पूर्णांक drm_dp_link_probe(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link);
पूर्णांक drm_dp_link_घातer_up(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link);
पूर्णांक drm_dp_link_घातer_करोwn(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link);
पूर्णांक drm_dp_link_configure(काष्ठा drm_dp_aux *aux, काष्ठा drm_dp_link *link);
पूर्णांक drm_dp_link_choose(काष्ठा drm_dp_link *link,
		       स्थिर काष्ठा drm_display_mode *mode,
		       स्थिर काष्ठा drm_display_info *info);

व्योम drm_dp_link_train_init(काष्ठा drm_dp_link_train *train);
पूर्णांक drm_dp_link_train(काष्ठा drm_dp_link *link);

#पूर्ण_अगर
