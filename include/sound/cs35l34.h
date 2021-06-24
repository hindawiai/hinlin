<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/sound/cs35l34.h -- Platक्रमm data क्रम CS35l34
 *
 * Copyright (c) 2016 Cirrus Logic Inc.
 */

#अगर_अघोषित __CS35L34_H
#घोषणा __CS35L34_H

काष्ठा cs35l34_platक्रमm_data अणु
	/* Set AIF to half drive strength */
	bool aअगर_half_drv;
	/* Digital Soft Ramp Disable */
	bool digsft_disable;
	/* Amplअगरier Invert */
	bool amp_inv;
	/* Peak current (mA) */
	अचिन्हित पूर्णांक boost_peak;
	/* Boost inductor value (nH) */
	अचिन्हित पूर्णांक boost_ind;
	/* Boost Controller Voltage Setting (mV) */
	अचिन्हित पूर्णांक boost_vtge;
	/* Gain Change Zero Cross */
	bool gain_zc_disable;
	/* SDIN Left/Right Selection */
	अचिन्हित पूर्णांक i2s_sdinloc;
	/* TDM Rising Edge */
	bool tdm_rising_edge;
पूर्ण;

#पूर्ण_अगर /* __CS35L34_H */
