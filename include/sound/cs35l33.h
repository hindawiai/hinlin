<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/cs35l33.h -- Platक्रमm data क्रम CS35l33
 *
 * Copyright (c) 2016 Cirrus Logic Inc.
 */

#अगर_अघोषित __CS35L33_H
#घोषणा __CS35L33_H

काष्ठा cs35l33_hg अणु
	bool enable_hg_algo;
	अचिन्हित पूर्णांक mem_depth;
	अचिन्हित पूर्णांक release_rate;
	अचिन्हित पूर्णांक hd_rm;
	अचिन्हित पूर्णांक lकरो_thld;
	अचिन्हित पूर्णांक lकरो_path_disable;
	अचिन्हित पूर्णांक lकरो_entry_delay;
	bool vp_hg_स्वतः;
	अचिन्हित पूर्णांक vp_hg;
	अचिन्हित पूर्णांक vp_hg_rate;
	अचिन्हित पूर्णांक vp_hg_va;
पूर्ण;

काष्ठा cs35l33_pdata अणु
	/* Boost Controller Voltage Setting */
	अचिन्हित पूर्णांक boost_ctl;

	/* Boost Controller Peak Current */
	अचिन्हित पूर्णांक boost_ipk;

	/* Amplअगरier Drive Select */
	अचिन्हित पूर्णांक amp_drv_sel;

	/* soft volume ramp */
	अचिन्हित पूर्णांक ramp_rate;

	/* IMON adc scale */
	अचिन्हित पूर्णांक imon_adc_scale;

	/* H/G algo configuration */
	काष्ठा cs35l33_hg hg_config;
पूर्ण;

#पूर्ण_अगर /* __CS35L33_H */
