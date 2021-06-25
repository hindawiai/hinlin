<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * tegra20_das.h - Definitions क्रम Tegra20 DAS driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 */

#अगर_अघोषित __TEGRA20_DAS_H__
#घोषणा __TEGRA20_DAS_H__

/* Register TEGRA20_DAS_DAP_CTRL_SEL */
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL			0x00
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_COUNT			5
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_STRIDE			4
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_MS_SEL_P		31
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_MS_SEL_S		1
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_SDATA1_TX_RX_P	30
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_SDATA1_TX_RX_S	1
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_SDATA2_TX_RX_P	29
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_SDATA2_TX_RX_S	1
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL_P		0
#घोषणा TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL_S		5

/* Values क्रम field TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL */
#घोषणा TEGRA20_DAS_DAP_SEL_DAC1	0
#घोषणा TEGRA20_DAS_DAP_SEL_DAC2	1
#घोषणा TEGRA20_DAS_DAP_SEL_DAC3	2
#घोषणा TEGRA20_DAS_DAP_SEL_DAP1	16
#घोषणा TEGRA20_DAS_DAP_SEL_DAP2	17
#घोषणा TEGRA20_DAS_DAP_SEL_DAP3	18
#घोषणा TEGRA20_DAS_DAP_SEL_DAP4	19
#घोषणा TEGRA20_DAS_DAP_SEL_DAP5	20

/* Register TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL */
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL			0x40
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_COUNT		3
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_STRIDE		4
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA2_SEL_P	28
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA2_SEL_S	4
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA1_SEL_P	24
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA1_SEL_S	4
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_CLK_SEL_P	0
#घोषणा TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_CLK_SEL_S	4

/*
 * Values क्रम:
 * TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA2_SEL
 * TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_SDATA1_SEL
 * TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL_DAC_CLK_SEL
 */
#घोषणा TEGRA20_DAS_DAC_SEL_DAP1	0
#घोषणा TEGRA20_DAS_DAC_SEL_DAP2	1
#घोषणा TEGRA20_DAS_DAC_SEL_DAP3	2
#घोषणा TEGRA20_DAS_DAC_SEL_DAP4	3
#घोषणा TEGRA20_DAS_DAC_SEL_DAP5	4

/*
 * Names/IDs of the DACs/DAPs.
 */

#घोषणा TEGRA20_DAS_DAP_ID_1 0
#घोषणा TEGRA20_DAS_DAP_ID_2 1
#घोषणा TEGRA20_DAS_DAP_ID_3 2
#घोषणा TEGRA20_DAS_DAP_ID_4 3
#घोषणा TEGRA20_DAS_DAP_ID_5 4

#घोषणा TEGRA20_DAS_DAC_ID_1 0
#घोषणा TEGRA20_DAS_DAC_ID_2 1
#घोषणा TEGRA20_DAS_DAC_ID_3 2

काष्ठा tegra20_das अणु
	काष्ठा device *dev;
	काष्ठा regmap *regmap;
पूर्ण;

/*
 * Terminology:
 * DAS: Digital audio चयन (HW module controlled by this driver)
 * DAP: Digital audio port (port/pins on Tegra device)
 * DAC: Digital audio controller (e.g. I2S or AC97 controller अन्यथाwhere)
 *
 * The Tegra DAS is a mux/cross-bar which can connect each DAP to a specअगरic
 * DAC, or another DAP. When DAPs are connected, one must be the master and
 * one the slave. Each DAC allows selection of a specअगरic DAP क्रम input, to
 * cater क्रम the हाल where N DAPs are connected to 1 DAC क्रम broadcast
 * output.
 *
 * This driver is dumb; no attempt is made to ensure that a valid routing
 * configuration is programmed.
 */

/*
 * Connect a DAP to a DAC
 * dap_id: DAP to connect: TEGRA20_DAS_DAP_ID_*
 * dac_sel: DAC to connect to: TEGRA20_DAS_DAP_SEL_DAC*
 */
बाह्य पूर्णांक tegra20_das_connect_dap_to_dac(पूर्णांक dap, पूर्णांक dac);

/*
 * Connect a DAP to another DAP
 * dap_id: DAP to connect: TEGRA20_DAS_DAP_ID_*
 * other_dap_sel: DAP to connect to: TEGRA20_DAS_DAP_SEL_DAP*
 * master: Is this DAP the master (1) or slave (0)
 * sdata1rx: Is this DAP's SDATA1 pin RX (1) or TX (0)
 * sdata2rx: Is this DAP's SDATA2 pin RX (1) or TX (0)
 */
बाह्य पूर्णांक tegra20_das_connect_dap_to_dap(पूर्णांक dap, पूर्णांक otherdap,
					  पूर्णांक master, पूर्णांक sdata1rx,
					  पूर्णांक sdata2rx);

/*
 * Connect a DAC's input to a DAP
 * (DAC outमाला_दो are selected by the DAP)
 * dac_id: DAC ID to connect: TEGRA20_DAS_DAC_ID_*
 * dap_sel: DAP to receive input from: TEGRA20_DAS_DAC_SEL_DAP*
 */
बाह्य पूर्णांक tegra20_das_connect_dac_to_dap(पूर्णांक dac, पूर्णांक dap);

#पूर्ण_अगर
