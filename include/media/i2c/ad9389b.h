<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Analog Devices AD9389B/AD9889B video encoder driver header
 *
 * Copyright 2012 Cisco Systems, Inc. and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित AD9389B_H
#घोषणा AD9389B_H

क्रमागत ad9389b_पंचांगds_pll_gear अणु
	AD9389B_TMDS_PLL_GEAR_AUTOMATIC,
	AD9389B_TMDS_PLL_GEAR_SEMI_AUTOMATIC,
पूर्ण;

/* Platक्रमm dependent definitions */
काष्ठा ad9389b_platक्रमm_data अणु
	क्रमागत ad9389b_पंचांगds_pll_gear पंचांगds_pll_gear ;
	/* Dअगरferential Data/Clock Output Drive Strength (reg. 0xa2/0xa3) */
	u8 dअगरf_data_drive_strength;
	u8 dअगरf_clk_drive_strength;
पूर्ण;

/* notअगरy events */
#घोषणा AD9389B_MONITOR_DETECT 0
#घोषणा AD9389B_EDID_DETECT 1

काष्ठा ad9389b_monitor_detect अणु
	पूर्णांक present;
पूर्ण;

काष्ठा ad9389b_edid_detect अणु
	पूर्णांक present;
	पूर्णांक segment;
पूर्ण;

#पूर्ण_अगर
