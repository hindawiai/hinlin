<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DSI पूर्णांकerface to the Samsung S6E63M0 panel.
 * (C) 2019 Linus Walleij
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>

#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "panel-samsung-s6e63m0.h"

#घोषणा MCS_GLOBAL_PARAM	0xb0
#घोषणा S6E63M0_DSI_MAX_CHUNK	15 /* CMD + 15 bytes max */

अटल पूर्णांक s6e63m0_dsi_dcs_पढ़ो(काष्ठा device *dev, स्थिर u8 cmd, u8 *data)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	पूर्णांक ret;

	ret = mipi_dsi_dcs_पढ़ो(dsi, cmd, data, 1);
	अगर (ret < 0) अणु
		dev_err(dev, "could not read DCS CMD %02x\n", cmd);
		वापस ret;
	पूर्ण

	dev_info(dev, "DSI read CMD %02x = %02x\n", cmd, *data);

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_dsi_dcs_ग_लिखो(काष्ठा device *dev, स्थिर u8 *data, माप_प्रकार len)
अणु
	काष्ठा mipi_dsi_device *dsi = to_mipi_dsi_device(dev);
	स्थिर u8 *seqp = data;
	u8 cmd;
	u8 cmdwritten;
	पूर्णांक reमुख्य;
	पूर्णांक chunk;
	पूर्णांक ret;

	dev_info(dev, "DSI writing dcs seq: %*ph\n", (पूर्णांक)len, data);

	/* Pick out and skip past the DCS command */
	cmd = *seqp;
	seqp++;
	cmdwritten = 0;
	reमुख्य = len - 1;
	chunk = reमुख्य;

	/* Send max S6E63M0_DSI_MAX_CHUNK bytes at a समय */
	अगर (chunk > S6E63M0_DSI_MAX_CHUNK)
		chunk = S6E63M0_DSI_MAX_CHUNK;
	ret = mipi_dsi_dcs_ग_लिखो(dsi, cmd, seqp, chunk);
	अगर (ret < 0) अणु
		dev_err(dev, "error sending DCS command seq cmd %02x\n", cmd);
		वापस ret;
	पूर्ण
	cmdwritten += chunk;
	seqp += chunk;

	जबतक (cmdwritten < reमुख्य) अणु
		chunk = reमुख्य - cmdwritten;
		अगर (chunk > S6E63M0_DSI_MAX_CHUNK)
			chunk = S6E63M0_DSI_MAX_CHUNK;
		ret = mipi_dsi_dcs_ग_लिखो(dsi, MCS_GLOBAL_PARAM, &cmdwritten, 1);
		अगर (ret < 0) अणु
			dev_err(dev, "error sending CMD %02x global param %02x\n",
				cmd, cmdwritten);
			वापस ret;
		पूर्ण
		ret = mipi_dsi_dcs_ग_लिखो(dsi, cmd, seqp, chunk);
		अगर (ret < 0) अणु
			dev_err(dev, "error sending CMD %02x chunk\n", cmd);
			वापस ret;
		पूर्ण
		cmdwritten += chunk;
		seqp += chunk;
	पूर्ण
	dev_info(dev, "sent command %02x %02x bytes\n", cmd, cmdwritten);

	usleep_range(8000, 9000);

	वापस 0;
पूर्ण

अटल पूर्णांक s6e63m0_dsi_probe(काष्ठा mipi_dsi_device *dsi)
अणु
	काष्ठा device *dev = &dsi->dev;
	पूर्णांक ret;

	dsi->lanes = 2;
	dsi->क्रमmat = MIPI_DSI_FMT_RGB888;
	dsi->hs_rate = 349440000;
	dsi->lp_rate = 9600000;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO |
		MIPI_DSI_MODE_VIDEO_BURST;

	ret = s6e63m0_probe(dev, s6e63m0_dsi_dcs_पढ़ो, s6e63m0_dsi_dcs_ग_लिखो,
			    true);
	अगर (ret)
		वापस ret;

	ret = mipi_dsi_attach(dsi);
	अगर (ret < 0)
		s6e63m0_हटाओ(dev);

	वापस ret;
पूर्ण

अटल पूर्णांक s6e63m0_dsi_हटाओ(काष्ठा mipi_dsi_device *dsi)
अणु
	mipi_dsi_detach(dsi);
	वापस s6e63m0_हटाओ(&dsi->dev);
पूर्ण

अटल स्थिर काष्ठा of_device_id s6e63m0_dsi_of_match[] = अणु
	अणु .compatible = "samsung,s6e63m0" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s6e63m0_dsi_of_match);

अटल काष्ठा mipi_dsi_driver s6e63m0_dsi_driver = अणु
	.probe			= s6e63m0_dsi_probe,
	.हटाओ			= s6e63m0_dsi_हटाओ,
	.driver			= अणु
		.name		= "panel-samsung-s6e63m0",
		.of_match_table = s6e63m0_dsi_of_match,
	पूर्ण,
पूर्ण;
module_mipi_dsi_driver(s6e63m0_dsi_driver);

MODULE_AUTHOR("Linus Walleij <linusw@kernel.org>");
MODULE_DESCRIPTION("s6e63m0 LCD DSI Driver");
MODULE_LICENSE("GPL v2");
