<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2017-2021 NXP
 */

#अगर_अघोषित __FSL_RPMSG_H
#घोषणा __FSL_RPMSG_H

/*
 * काष्ठा fsl_rpmsg - rpmsg निजी data
 *
 * @ipg: ipg घड़ी क्रम cpu dai (SAI)
 * @mclk: master घड़ी क्रम cpu dai (SAI)
 * @dma: घड़ी क्रम dma device
 * @pll8k: parent घड़ी क्रम multiple of 8kHz frequency
 * @pll11k: parent घड़ी क्रम multiple of 11kHz frequency
 * @card_pdev: Platक्रमm_device poपूर्णांकer to रेजिस्टर a sound card
 * @mclk_streams: Active streams that are using baudclk
 * @क्रमce_lpa: क्रमce enable low घातer audio routine अगर condition satisfy
 * @enable_lpa: enable low घातer audio routine according to dts setting
 * @buffer_size: pre allocated dma buffer size
 */
काष्ठा fsl_rpmsg अणु
	काष्ठा clk *ipg;
	काष्ठा clk *mclk;
	काष्ठा clk *dma;
	काष्ठा clk *pll8k;
	काष्ठा clk *pll11k;
	काष्ठा platक्रमm_device *card_pdev;
	अचिन्हित पूर्णांक mclk_streams;
	पूर्णांक क्रमce_lpa;
	पूर्णांक enable_lpa;
	पूर्णांक buffer_size;
पूर्ण;
#पूर्ण_अगर /* __FSL_RPMSG_H */
