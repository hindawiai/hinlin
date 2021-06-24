<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics SA 2014
 * Author: Vincent Abriou <vincent.abriou@st.com> क्रम STMicroelectronics.
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "sti_hdmi_tx3g4c28phy.h"

#घोषणा HDMI_SRZ_CFG                             0x504
#घोषणा HDMI_SRZ_PLL_CFG                         0x510
#घोषणा HDMI_SRZ_ICNTL                           0x518
#घोषणा HDMI_SRZ_CALCODE_EXT                     0x520

#घोषणा HDMI_SRZ_CFG_EN                          BIT(0)
#घोषणा HDMI_SRZ_CFG_DISABLE_BYPASS_SINK_CURRENT BIT(1)
#घोषणा HDMI_SRZ_CFG_EXTERNAL_DATA               BIT(16)
#घोषणा HDMI_SRZ_CFG_RBIAS_EXT                   BIT(17)
#घोषणा HDMI_SRZ_CFG_EN_SINK_TERM_DETECTION      BIT(18)
#घोषणा HDMI_SRZ_CFG_EN_BIASRES_DETECTION        BIT(19)
#घोषणा HDMI_SRZ_CFG_EN_SRC_TERMINATION          BIT(24)

#घोषणा HDMI_SRZ_CFG_INTERNAL_MASK  (HDMI_SRZ_CFG_EN     | \
		HDMI_SRZ_CFG_DISABLE_BYPASS_SINK_CURRENT | \
		HDMI_SRZ_CFG_EXTERNAL_DATA               | \
		HDMI_SRZ_CFG_RBIAS_EXT                   | \
		HDMI_SRZ_CFG_EN_SINK_TERM_DETECTION      | \
		HDMI_SRZ_CFG_EN_BIASRES_DETECTION        | \
		HDMI_SRZ_CFG_EN_SRC_TERMINATION)

#घोषणा PLL_CFG_EN                               BIT(0)
#घोषणा PLL_CFG_NDIV_SHIFT                       (8)
#घोषणा PLL_CFG_IDF_SHIFT                        (16)
#घोषणा PLL_CFG_ODF_SHIFT                        (24)

#घोषणा ODF_DIV_1                                (0)
#घोषणा ODF_DIV_2                                (1)
#घोषणा ODF_DIV_4                                (2)
#घोषणा ODF_DIV_8                                (3)

#घोषणा HDMI_TIMEOUT_PLL_LOCK  50  /*milliseconds */

काष्ठा plद_भागiders_s अणु
	uपूर्णांक32_t min;
	uपूर्णांक32_t max;
	uपूर्णांक32_t idf;
	uपूर्णांक32_t odf;
पूर्ण;

/*
 * Functional specअगरication recommended values
 */
#घोषणा NB_PLL_MODE 5
अटल काष्ठा plद_भागiders_s plद_भागiders[NB_PLL_MODE] = अणु
	अणु0, 20000000, 1, ODF_DIV_8पूर्ण,
	अणु20000000, 42500000, 2, ODF_DIV_8पूर्ण,
	अणु42500000, 85000000, 4, ODF_DIV_4पूर्ण,
	अणु85000000, 170000000, 8, ODF_DIV_2पूर्ण,
	अणु170000000, 340000000, 16, ODF_DIV_1पूर्ण
पूर्ण;

#घोषणा NB_HDMI_PHY_CONFIG 2
अटल काष्ठा hdmi_phy_config hdmiphy_config[NB_HDMI_PHY_CONFIG] = अणु
	अणु0, 250000000, अणु0x0, 0x0, 0x0, 0x0पूर्ण पूर्ण,
	अणु250000000, 300000000, अणु0x1110, 0x0, 0x0, 0x0पूर्ण पूर्ण,
पूर्ण;

/**
 * Start hdmi phy macro cell tx3g4c28
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 *
 * Return false अगर an error occur
 */
अटल bool sti_hdmi_tx3g4c28phy_start(काष्ठा sti_hdmi *hdmi)
अणु
	u32 ckpxpll = hdmi->mode.घड़ी * 1000;
	u32 val, पंचांगdsck, idf, odf, pllctrl = 0;
	bool foundplद_भागides = false;
	पूर्णांक i;

	DRM_DEBUG_DRIVER("ckpxpll = %dHz\n", ckpxpll);

	क्रम (i = 0; i < NB_PLL_MODE; i++) अणु
		अगर (ckpxpll >= plद_भागiders[i].min &&
		    ckpxpll < plद_भागiders[i].max) अणु
			idf = plद_भागiders[i].idf;
			odf = plद_भागiders[i].odf;
			foundplद_भागides = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!foundplद_भागides) अणु
		DRM_ERROR("input TMDS clock speed (%d) not supported\n",
			  ckpxpll);
		जाओ err;
	पूर्ण

	/* Assuming no pixel repetition and 24bits color */
	पंचांगdsck = ckpxpll;
	pllctrl |= 40 << PLL_CFG_NDIV_SHIFT;

	अगर (पंचांगdsck > 340000000) अणु
		DRM_ERROR("output TMDS clock (%d) out of range\n", पंचांगdsck);
		जाओ err;
	पूर्ण

	pllctrl |= idf << PLL_CFG_IDF_SHIFT;
	pllctrl |= odf << PLL_CFG_ODF_SHIFT;

	/*
	 * Configure and घातer up the PHY PLL
	 */
	hdmi->event_received = false;
	DRM_DEBUG_DRIVER("pllctrl = 0x%x\n", pllctrl);
	hdmi_ग_लिखो(hdmi, (pllctrl | PLL_CFG_EN), HDMI_SRZ_PLL_CFG);

	/* रुको PLL पूर्णांकerrupt */
	रुको_event_पूर्णांकerruptible_समयout(hdmi->रुको_event,
					 hdmi->event_received == true,
					 msecs_to_jअगरfies
					 (HDMI_TIMEOUT_PLL_LOCK));

	अगर ((hdmi_पढ़ो(hdmi, HDMI_STA) & HDMI_STA_DLL_LCK) == 0) अणु
		DRM_ERROR("hdmi phy pll not locked\n");
		जाओ err;
	पूर्ण

	DRM_DEBUG_DRIVER("got PHY PLL Lock\n");

	val = (HDMI_SRZ_CFG_EN |
	       HDMI_SRZ_CFG_EXTERNAL_DATA |
	       HDMI_SRZ_CFG_EN_BIASRES_DETECTION |
	       HDMI_SRZ_CFG_EN_SINK_TERM_DETECTION);

	अगर (पंचांगdsck > 165000000)
		val |= HDMI_SRZ_CFG_EN_SRC_TERMINATION;

	/*
	 * To configure the source termination and pre-emphasis appropriately
	 * क्रम dअगरferent high speed TMDS घड़ी frequencies a phy configuration
	 * table must be provided, tailored to the SoC and board combination.
	 */
	क्रम (i = 0; i < NB_HDMI_PHY_CONFIG; i++) अणु
		अगर ((hdmiphy_config[i].min_पंचांगds_freq <= पंचांगdsck) &&
		    (hdmiphy_config[i].max_पंचांगds_freq >= पंचांगdsck)) अणु
			val |= (hdmiphy_config[i].config[0]
				& ~HDMI_SRZ_CFG_INTERNAL_MASK);
			hdmi_ग_लिखो(hdmi, val, HDMI_SRZ_CFG);

			val = hdmiphy_config[i].config[1];
			hdmi_ग_लिखो(hdmi, val, HDMI_SRZ_ICNTL);

			val = hdmiphy_config[i].config[2];
			hdmi_ग_लिखो(hdmi, val, HDMI_SRZ_CALCODE_EXT);

			DRM_DEBUG_DRIVER("serializer cfg 0x%x 0x%x 0x%x\n",
					 hdmiphy_config[i].config[0],
					 hdmiphy_config[i].config[1],
					 hdmiphy_config[i].config[2]);
			वापस true;
		पूर्ण
	पूर्ण

	/*
	 * Default, घातer up the serializer with no pre-emphasis or
	 * output swing correction
	 */
	hdmi_ग_लिखो(hdmi, val,  HDMI_SRZ_CFG);
	hdmi_ग_लिखो(hdmi, 0x0, HDMI_SRZ_ICNTL);
	hdmi_ग_लिखो(hdmi, 0x0, HDMI_SRZ_CALCODE_EXT);

	वापस true;

err:
	वापस false;
पूर्ण

/**
 * Stop hdmi phy macro cell tx3g4c28
 *
 * @hdmi: poपूर्णांकer on the hdmi पूर्णांकernal काष्ठाure
 */
अटल व्योम sti_hdmi_tx3g4c28phy_stop(काष्ठा sti_hdmi *hdmi)
अणु
	पूर्णांक val = 0;

	DRM_DEBUG_DRIVER("\n");

	hdmi->event_received = false;

	val = HDMI_SRZ_CFG_EN_SINK_TERM_DETECTION;
	val |= HDMI_SRZ_CFG_EN_BIASRES_DETECTION;

	hdmi_ग_लिखो(hdmi, val, HDMI_SRZ_CFG);
	hdmi_ग_लिखो(hdmi, 0, HDMI_SRZ_PLL_CFG);

	/* रुको PLL पूर्णांकerrupt */
	रुको_event_पूर्णांकerruptible_समयout(hdmi->रुको_event,
					 hdmi->event_received == true,
					 msecs_to_jअगरfies
					 (HDMI_TIMEOUT_PLL_LOCK));

	अगर (hdmi_पढ़ो(hdmi, HDMI_STA) & HDMI_STA_DLL_LCK)
		DRM_ERROR("hdmi phy pll not well disabled\n");
पूर्ण

काष्ठा hdmi_phy_ops tx3g4c28phy_ops = अणु
	.start = sti_hdmi_tx3g4c28phy_start,
	.stop = sti_hdmi_tx3g4c28phy_stop,
पूर्ण;
