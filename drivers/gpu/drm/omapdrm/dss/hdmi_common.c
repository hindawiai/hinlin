<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#घोषणा DSS_SUBSYS_NAME "HDMI"

#समावेश <linux/kernel.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>

#समावेश "omapdss.h"
#समावेश "hdmi.h"

पूर्णांक hdmi_parse_lanes_of(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *ep,
	काष्ठा hdmi_phy_data *phy)
अणु
	काष्ठा property *prop;
	पूर्णांक r, len;

	prop = of_find_property(ep, "lanes", &len);
	अगर (prop) अणु
		u32 lanes[8];

		अगर (len / माप(u32) != ARRAY_SIZE(lanes)) अणु
			dev_err(&pdev->dev, "bad number of lanes\n");
			वापस -EINVAL;
		पूर्ण

		r = of_property_पढ़ो_u32_array(ep, "lanes", lanes,
			ARRAY_SIZE(lanes));
		अगर (r) अणु
			dev_err(&pdev->dev, "failed to read lane data\n");
			वापस r;
		पूर्ण

		r = hdmi_phy_parse_lanes(phy, lanes);
		अगर (r) अणु
			dev_err(&pdev->dev, "failed to parse lane data\n");
			वापस r;
		पूर्ण
	पूर्ण अन्यथा अणु
		अटल स्थिर u32 शेष_lanes[] = अणु 0, 1, 2, 3, 4, 5, 6, 7 पूर्ण;

		r = hdmi_phy_parse_lanes(phy, शेष_lanes);
		अगर (WARN_ON(r)) अणु
			dev_err(&pdev->dev, "failed to parse lane data\n");
			वापस r;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hdmi_compute_acr(u32 pclk, u32 sample_freq, u32 *n, u32 *cts)
अणु
	u32 deep_color;
	bool deep_color_correct = false;

	अगर (n == शून्य || cts == शून्य)
		वापस -EINVAL;

	/* TODO: When implemented, query deep color mode here. */
	deep_color = 100;

	/*
	 * When using deep color, the शेष N value (as in the HDMI
	 * specअगरication) yields to an non-पूर्णांकeger CTS. Hence, we
	 * modअगरy it जबतक keeping the restrictions described in
	 * section 7.2.1 of the HDMI 1.4a specअगरication.
	 */
	चयन (sample_freq) अणु
	हाल 32000:
	हाल 48000:
	हाल 96000:
	हाल 192000:
		अगर (deep_color == 125)
			अगर (pclk == 27027000 || pclk == 74250000)
				deep_color_correct = true;
		अगर (deep_color == 150)
			अगर (pclk == 27027000)
				deep_color_correct = true;
		अवरोध;
	हाल 44100:
	हाल 88200:
	हाल 176400:
		अगर (deep_color == 125)
			अगर (pclk == 27027000)
				deep_color_correct = true;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (deep_color_correct) अणु
		चयन (sample_freq) अणु
		हाल 32000:
			*n = 8192;
			अवरोध;
		हाल 44100:
			*n = 12544;
			अवरोध;
		हाल 48000:
			*n = 8192;
			अवरोध;
		हाल 88200:
			*n = 25088;
			अवरोध;
		हाल 96000:
			*n = 16384;
			अवरोध;
		हाल 176400:
			*n = 50176;
			अवरोध;
		हाल 192000:
			*n = 32768;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (sample_freq) अणु
		हाल 32000:
			*n = 4096;
			अवरोध;
		हाल 44100:
			*n = 6272;
			अवरोध;
		हाल 48000:
			*n = 6144;
			अवरोध;
		हाल 88200:
			*n = 12544;
			अवरोध;
		हाल 96000:
			*n = 12288;
			अवरोध;
		हाल 176400:
			*n = 25088;
			अवरोध;
		हाल 192000:
			*n = 24576;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	/* Calculate CTS. See HDMI 1.3a or 1.4a specअगरications */
	*cts = (pclk/1000) * (*n / 128) * deep_color / (sample_freq / 10);

	वापस 0;
पूर्ण
