<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018 Cadence Design Systems Inc.
 */

#अगर_अघोषित __PHY_MIPI_DPHY_H_
#घोषणा __PHY_MIPI_DPHY_H_

/**
 * काष्ठा phy_configure_opts_mipi_dphy - MIPI D-PHY configuration set
 *
 * This काष्ठाure is used to represent the configuration state of a
 * MIPI D-PHY phy.
 */
काष्ठा phy_configure_opts_mipi_dphy अणु
	/**
	 * @clk_miss:
	 *
	 * Timeout, in picoseconds, क्रम receiver to detect असलence of
	 * Clock transitions and disable the Clock Lane HS-RX.
	 *
	 * Maximum value: 60000 ps
	 */
	अचिन्हित पूर्णांक		clk_miss;

	/**
	 * @clk_post:
	 *
	 * Time, in picoseconds, that the transmitter जारीs to
	 * send HS घड़ी after the last associated Data Lane has
	 * transitioned to LP Mode. Interval is defined as the period
	 * from the end of @hs_trail to the beginning of @clk_trail.
	 *
	 * Minimum value: 60000 ps + 52 * @hs_clk_rate period in ps
	 */
	अचिन्हित पूर्णांक		clk_post;

	/**
	 * @clk_pre:
	 *
	 * Time, in UI, that the HS घड़ी shall be driven by
	 * the transmitter prior to any associated Data Lane beginning
	 * the transition from LP to HS mode.
	 *
	 * Minimum value: 8 UI
	 */
	अचिन्हित पूर्णांक		clk_pre;

	/**
	 * @clk_prepare:
	 *
	 * Time, in picoseconds, that the transmitter drives the Clock
	 * Lane LP-00 Line state immediately beक्रमe the HS-0 Line
	 * state starting the HS transmission.
	 *
	 * Minimum value: 38000 ps
	 * Maximum value: 95000 ps
	 */
	अचिन्हित पूर्णांक		clk_prepare;

	/**
	 * @clk_settle:
	 *
	 * Time पूर्णांकerval, in picoseconds, during which the HS receiver
	 * should ignore any Clock Lane HS transitions, starting from
	 * the beginning of @clk_prepare.
	 *
	 * Minimum value: 95000 ps
	 * Maximum value: 300000 ps
	 */
	अचिन्हित पूर्णांक		clk_settle;

	/**
	 * @clk_term_en:
	 *
	 * Time, in picoseconds, क्रम the Clock Lane receiver to enable
	 * the HS line termination.
	 *
	 * Maximum value: 38000 ps
	 */
	अचिन्हित पूर्णांक		clk_term_en;

	/**
	 * @clk_trail:
	 *
	 * Time, in picoseconds, that the transmitter drives the HS-0
	 * state after the last payload घड़ी bit of a HS transmission
	 * burst.
	 *
	 * Minimum value: 60000 ps
	 */
	अचिन्हित पूर्णांक		clk_trail;

	/**
	 * @clk_zero:
	 *
	 * Time, in picoseconds, that the transmitter drives the HS-0
	 * state prior to starting the Clock.
	 */
	अचिन्हित पूर्णांक		clk_zero;

	/**
	 * @d_term_en:
	 *
	 * Time, in picoseconds, क्रम the Data Lane receiver to enable
	 * the HS line termination.
	 *
	 * Maximum value: 35000 ps + 4 * @hs_clk_rate period in ps
	 */
	अचिन्हित पूर्णांक		d_term_en;

	/**
	 * @eot:
	 *
	 * Transmitted समय पूर्णांकerval, in picoseconds, from the start
	 * of @hs_trail or @clk_trail, to the start of the LP- 11
	 * state following a HS burst.
	 *
	 * Maximum value: 105000 ps + 12 * @hs_clk_rate period in ps
	 */
	अचिन्हित पूर्णांक		eot;

	/**
	 * @hs_निकास:
	 *
	 * Time, in picoseconds, that the transmitter drives LP-11
	 * following a HS burst.
	 *
	 * Minimum value: 100000 ps
	 */
	अचिन्हित पूर्णांक		hs_निकास;

	/**
	 * @hs_prepare:
	 *
	 * Time, in picoseconds, that the transmitter drives the Data
	 * Lane LP-00 Line state immediately beक्रमe the HS-0 Line
	 * state starting the HS transmission.
	 *
	 * Minimum value: 40000 ps + 4 * @hs_clk_rate period in ps
	 * Maximum value: 85000 ps + 6 * @hs_clk_rate period in ps
	 */
	अचिन्हित पूर्णांक		hs_prepare;

	/**
	 * @hs_settle:
	 *
	 * Time पूर्णांकerval, in picoseconds, during which the HS receiver
	 * shall ignore any Data Lane HS transitions, starting from
	 * the beginning of @hs_prepare.
	 *
	 * Minimum value: 85000 ps + 6 * @hs_clk_rate period in ps
	 * Maximum value: 145000 ps + 10 * @hs_clk_rate period in ps
	 */
	अचिन्हित पूर्णांक		hs_settle;

	/**
	 * @hs_skip:
	 *
	 * Time पूर्णांकerval, in picoseconds, during which the HS-RX
	 * should ignore any transitions on the Data Lane, following a
	 * HS burst. The end poपूर्णांक of the पूर्णांकerval is defined as the
	 * beginning of the LP-11 state following the HS burst.
	 *
	 * Minimum value: 40000 ps
	 * Maximum value: 55000 ps + 4 * @hs_clk_rate period in ps
	 */
	अचिन्हित पूर्णांक		hs_skip;

	/**
	 * @hs_trail:
	 *
	 * Time, in picoseconds, that the transmitter drives the
	 * flipped dअगरferential state after last payload data bit of a
	 * HS transmission burst
	 *
	 * Minimum value: max(8 * @hs_clk_rate period in ps,
	 *		      60000 ps + 4 * @hs_clk_rate period in ps)
	 */
	अचिन्हित पूर्णांक		hs_trail;

	/**
	 * @hs_zero:
	 *
	 * Time, in picoseconds, that the transmitter drives the HS-0
	 * state prior to transmitting the Sync sequence.
	 */
	अचिन्हित पूर्णांक		hs_zero;

	/**
	 * @init:
	 *
	 * Time, in microseconds क्रम the initialization period to
	 * complete.
	 *
	 * Minimum value: 100 us
	 */
	अचिन्हित पूर्णांक		init;

	/**
	 * @lpx:
	 *
	 * Transmitted length, in picoseconds, of any Low-Power state
	 * period.
	 *
	 * Minimum value: 50000 ps
	 */
	अचिन्हित पूर्णांक		lpx;

	/**
	 * @ta_get:
	 *
	 * Time, in picoseconds, that the new transmitter drives the
	 * Bridge state (LP-00) after accepting control during a Link
	 * Turnaround.
	 *
	 * Value: 5 * @lpx
	 */
	अचिन्हित पूर्णांक		ta_get;

	/**
	 * @ta_go:
	 *
	 * Time, in picoseconds, that the transmitter drives the
	 * Bridge state (LP-00) beक्रमe releasing control during a Link
	 * Turnaround.
	 *
	 * Value: 4 * @lpx
	 */
	अचिन्हित पूर्णांक		ta_go;

	/**
	 * @ta_sure:
	 *
	 * Time, in picoseconds, that the new transmitter रुकोs after
	 * the LP-10 state beक्रमe transmitting the Bridge state
	 * (LP-00) during a Link Turnaround.
	 *
	 * Minimum value: @lpx
	 * Maximum value: 2 * @lpx
	 */
	अचिन्हित पूर्णांक		ta_sure;

	/**
	 * @wakeup:
	 *
	 * Time, in microseconds, that a transmitter drives a Mark-1
	 * state prior to a Stop state in order to initiate an निकास
	 * from ULPS.
	 *
	 * Minimum value: 1000 us
	 */
	अचिन्हित पूर्णांक		wakeup;

	/**
	 * @hs_clk_rate:
	 *
	 * Clock rate, in Hertz, of the high-speed घड़ी.
	 */
	अचिन्हित दीर्घ		hs_clk_rate;

	/**
	 * @lp_clk_rate:
	 *
	 * Clock rate, in Hertz, of the low-घातer घड़ी.
	 */
	अचिन्हित दीर्घ		lp_clk_rate;

	/**
	 * @lanes:
	 *
	 * Number of active, consecutive, data lanes, starting from
	 * lane 0, used क्रम the transmissions.
	 */
	अचिन्हित अक्षर		lanes;
पूर्ण;

पूर्णांक phy_mipi_dphy_get_शेष_config(अचिन्हित दीर्घ pixel_घड़ी,
				     अचिन्हित पूर्णांक bpp,
				     अचिन्हित पूर्णांक lanes,
				     काष्ठा phy_configure_opts_mipi_dphy *cfg);
पूर्णांक phy_mipi_dphy_config_validate(काष्ठा phy_configure_opts_mipi_dphy *cfg);

#पूर्ण_अगर /* __PHY_MIPI_DPHY_H_ */
