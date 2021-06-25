<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019 Cadence Design Systems Inc.
 */

#अगर_अघोषित __PHY_DP_H_
#घोषणा __PHY_DP_H_

#समावेश <linux/types.h>

/**
 * काष्ठा phy_configure_opts_dp - DisplayPort PHY configuration set
 *
 * This काष्ठाure is used to represent the configuration state of a
 * DisplayPort phy.
 */
काष्ठा phy_configure_opts_dp अणु
	/**
	 * @link_rate:
	 *
	 * Link Rate, in Mb/s, of the मुख्य link.
	 *
	 * Allowed values: 1620, 2160, 2430, 2700, 3240, 4320, 5400, 8100 Mb/s
	 */
	अचिन्हित पूर्णांक link_rate;

	/**
	 * @lanes:
	 *
	 * Number of active, consecutive, data lanes, starting from
	 * lane 0, used क्रम the transmissions on मुख्य link.
	 *
	 * Allowed values: 1, 2, 4
	 */
	अचिन्हित पूर्णांक lanes;

	/**
	 * @voltage:
	 *
	 * Voltage swing levels, as specअगरied by DisplayPort specअगरication,
	 * to be used by particular lanes. One value per lane.
	 * voltage[0] is क्रम lane 0, voltage[1] is क्रम lane 1, etc.
	 *
	 * Maximum value: 3
	 */
	अचिन्हित पूर्णांक voltage[4];

	/**
	 * @pre:
	 *
	 * Pre-emphasis levels, as specअगरied by DisplayPort specअगरication, to be
	 * used by particular lanes. One value per lane.
	 *
	 * Maximum value: 3
	 */
	अचिन्हित पूर्णांक pre[4];

	/**
	 * @ssc:
	 *
	 * Flag indicating, whether or not to enable spपढ़ो-spectrum घड़ीing.
	 *
	 */
	u8 ssc : 1;

	/**
	 * @set_rate:
	 *
	 * Flag indicating, whether or not reconfigure link rate and SSC to
	 * requested values.
	 *
	 */
	u8 set_rate : 1;

	/**
	 * @set_lanes:
	 *
	 * Flag indicating, whether or not reconfigure lane count to
	 * requested value.
	 *
	 */
	u8 set_lanes : 1;

	/**
	 * @set_voltages:
	 *
	 * Flag indicating, whether or not reconfigure voltage swing
	 * and pre-emphasis to requested values. Only lanes specअगरied
	 * by "lanes" parameter will be affected.
	 *
	 */
	u8 set_voltages : 1;
पूर्ण;

#पूर्ण_अगर /* __PHY_DP_H_ */
