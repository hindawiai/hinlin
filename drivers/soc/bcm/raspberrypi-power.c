<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* (C) 2015 Pengutronix, Alexander Aring <aar@pengutronix.de>
 *
 * Authors:
 * Alexander Aring <aar@pengutronix.de>
 * Eric Anholt <eric@anholt.net>
 */

#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <dt-bindings/घातer/raspberrypi-घातer.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>

/*
 * Firmware indices क्रम the old घातer करोमुख्यs पूर्णांकerface.  Only a few
 * of them were actually implemented.
 */
#घोषणा RPI_OLD_POWER_DOMAIN_USB		3
#घोषणा RPI_OLD_POWER_DOMAIN_V3D		10

काष्ठा rpi_घातer_करोमुख्य अणु
	u32 करोमुख्य;
	bool enabled;
	bool old_पूर्णांकerface;
	काष्ठा generic_pm_करोमुख्य base;
	काष्ठा rpi_firmware *fw;
पूर्ण;

काष्ठा rpi_घातer_करोमुख्यs अणु
	bool has_new_पूर्णांकerface;
	काष्ठा genpd_onecell_data xlate;
	काष्ठा rpi_firmware *fw;
	काष्ठा rpi_घातer_करोमुख्य करोमुख्यs[RPI_POWER_DOMAIN_COUNT];
पूर्ण;

/*
 * Packet definition used by RPI_FIRMWARE_SET_POWER_STATE and
 * RPI_FIRMWARE_SET_DOMAIN_STATE
 */
काष्ठा rpi_घातer_करोमुख्य_packet अणु
	u32 करोमुख्य;
	u32 on;
पूर्ण;

/*
 * Asks the firmware to enable or disable घातer on a specअगरic घातer
 * करोमुख्य.
 */
अटल पूर्णांक rpi_firmware_set_घातer(काष्ठा rpi_घातer_करोमुख्य *rpi_करोमुख्य, bool on)
अणु
	काष्ठा rpi_घातer_करोमुख्य_packet packet;

	packet.करोमुख्य = rpi_करोमुख्य->करोमुख्य;
	packet.on = on;
	वापस rpi_firmware_property(rpi_करोमुख्य->fw,
				     rpi_करोमुख्य->old_पूर्णांकerface ?
				     RPI_FIRMWARE_SET_POWER_STATE :
				     RPI_FIRMWARE_SET_DOMAIN_STATE,
				     &packet, माप(packet));
पूर्ण

अटल पूर्णांक rpi_करोमुख्य_off(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rpi_घातer_करोमुख्य *rpi_करोमुख्य =
		container_of(करोमुख्य, काष्ठा rpi_घातer_करोमुख्य, base);

	वापस rpi_firmware_set_घातer(rpi_करोमुख्य, false);
पूर्ण

अटल पूर्णांक rpi_करोमुख्य_on(काष्ठा generic_pm_करोमुख्य *करोमुख्य)
अणु
	काष्ठा rpi_घातer_करोमुख्य *rpi_करोमुख्य =
		container_of(करोमुख्य, काष्ठा rpi_घातer_करोमुख्य, base);

	वापस rpi_firmware_set_घातer(rpi_करोमुख्य, true);
पूर्ण

अटल व्योम rpi_common_init_घातer_करोमुख्य(काष्ठा rpi_घातer_करोमुख्यs *rpi_करोमुख्यs,
					 पूर्णांक xlate_index, स्थिर अक्षर *name)
अणु
	काष्ठा rpi_घातer_करोमुख्य *करोm = &rpi_करोमुख्यs->करोमुख्यs[xlate_index];

	करोm->fw = rpi_करोमुख्यs->fw;

	करोm->base.name = name;
	करोm->base.घातer_on = rpi_करोमुख्य_on;
	करोm->base.घातer_off = rpi_करोमुख्य_off;

	/*
	 * Treat all घातer करोमुख्यs as off at boot.
	 *
	 * The firmware itself may be keeping some करोमुख्यs on, but
	 * from Linux's perspective all we control is the refcounts
	 * that we give to the firmware, and we can't ask the firmware
	 * to turn off something that we haven't ourselves turned on.
	 */
	pm_genpd_init(&करोm->base, शून्य, true);

	rpi_करोमुख्यs->xlate.करोमुख्यs[xlate_index] = &करोm->base;
पूर्ण

अटल व्योम rpi_init_घातer_करोमुख्य(काष्ठा rpi_घातer_करोमुख्यs *rpi_करोमुख्यs,
				  पूर्णांक xlate_index, स्थिर अक्षर *name)
अणु
	काष्ठा rpi_घातer_करोमुख्य *करोm = &rpi_करोमुख्यs->करोमुख्यs[xlate_index];

	अगर (!rpi_करोमुख्यs->has_new_पूर्णांकerface)
		वापस;

	/* The DT binding index is the firmware's करोमुख्य index minus one. */
	करोm->करोमुख्य = xlate_index + 1;

	rpi_common_init_घातer_करोमुख्य(rpi_करोमुख्यs, xlate_index, name);
पूर्ण

अटल व्योम rpi_init_old_घातer_करोमुख्य(काष्ठा rpi_घातer_करोमुख्यs *rpi_करोमुख्यs,
				      पूर्णांक xlate_index, पूर्णांक करोमुख्य,
				      स्थिर अक्षर *name)
अणु
	काष्ठा rpi_घातer_करोमुख्य *करोm = &rpi_करोमुख्यs->करोमुख्यs[xlate_index];

	करोm->old_पूर्णांकerface = true;
	करोm->करोमुख्य = करोमुख्य;

	rpi_common_init_घातer_करोमुख्य(rpi_करोमुख्यs, xlate_index, name);
पूर्ण

/*
 * Detects whether the firmware supports the new घातer करोमुख्यs पूर्णांकerface.
 *
 * The firmware करोesn't actually वापस an error on an unknown tag,
 * and just skips over it, so we करो the detection by putting an
 * unexpected value in the वापस field and checking अगर it was
 * unchanged.
 */
अटल bool
rpi_has_new_करोमुख्य_support(काष्ठा rpi_घातer_करोमुख्यs *rpi_करोमुख्यs)
अणु
	काष्ठा rpi_घातer_करोमुख्य_packet packet;
	पूर्णांक ret;

	packet.करोमुख्य = RPI_POWER_DOMAIN_ARM;
	packet.on = ~0;

	ret = rpi_firmware_property(rpi_करोमुख्यs->fw,
				    RPI_FIRMWARE_GET_DOMAIN_STATE,
				    &packet, माप(packet));

	वापस ret == 0 && packet.on != ~0;
पूर्ण

अटल पूर्णांक rpi_घातer_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *fw_np;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpi_घातer_करोमुख्यs *rpi_करोमुख्यs;

	rpi_करोमुख्यs = devm_kzalloc(dev, माप(*rpi_करोमुख्यs), GFP_KERNEL);
	अगर (!rpi_करोमुख्यs)
		वापस -ENOMEM;

	rpi_करोमुख्यs->xlate.करोमुख्यs =
		devm_kसुस्मृति(dev,
			     RPI_POWER_DOMAIN_COUNT,
			     माप(*rpi_करोमुख्यs->xlate.करोमुख्यs),
			     GFP_KERNEL);
	अगर (!rpi_करोमुख्यs->xlate.करोमुख्यs)
		वापस -ENOMEM;

	rpi_करोमुख्यs->xlate.num_करोमुख्यs = RPI_POWER_DOMAIN_COUNT;

	fw_np = of_parse_phandle(pdev->dev.of_node, "firmware", 0);
	अगर (!fw_np) अणु
		dev_err(&pdev->dev, "no firmware node\n");
		वापस -ENODEV;
	पूर्ण

	rpi_करोमुख्यs->fw = devm_rpi_firmware_get(&pdev->dev, fw_np);
	of_node_put(fw_np);
	अगर (!rpi_करोमुख्यs->fw)
		वापस -EPROBE_DEFER;

	rpi_करोमुख्यs->has_new_पूर्णांकerface =
		rpi_has_new_करोमुख्य_support(rpi_करोमुख्यs);

	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_I2C0, "I2C0");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_I2C1, "I2C1");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_I2C2, "I2C2");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_VIDEO_SCALER,
			      "VIDEO_SCALER");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_VPU1, "VPU1");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_HDMI, "HDMI");

	/*
	 * Use the old firmware पूर्णांकerface क्रम USB घातer, so that we
	 * can turn it on even अगर the firmware hasn't been updated.
	 */
	rpi_init_old_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_USB,
				  RPI_OLD_POWER_DOMAIN_USB, "USB");

	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_VEC, "VEC");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_JPEG, "JPEG");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_H264, "H264");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_V3D, "V3D");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_ISP, "ISP");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_UNICAM0, "UNICAM0");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_UNICAM1, "UNICAM1");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_CCP2RX, "CCP2RX");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_CSI2, "CSI2");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_CPI, "CPI");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_DSI0, "DSI0");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_DSI1, "DSI1");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_TRANSPOSER,
			      "TRANSPOSER");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_CCP2TX, "CCP2TX");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_CDP, "CDP");
	rpi_init_घातer_करोमुख्य(rpi_करोमुख्यs, RPI_POWER_DOMAIN_ARM, "ARM");

	of_genpd_add_provider_onecell(dev->of_node, &rpi_करोमुख्यs->xlate);

	platक्रमm_set_drvdata(pdev, rpi_करोमुख्यs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rpi_घातer_of_match[] = अणु
	अणु .compatible = "raspberrypi,bcm2835-power", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, rpi_घातer_of_match);

अटल काष्ठा platक्रमm_driver rpi_घातer_driver = अणु
	.driver = अणु
		.name = "raspberrypi-power",
		.of_match_table = rpi_घातer_of_match,
	पूर्ण,
	.probe		= rpi_घातer_probe,
पूर्ण;
builtin_platक्रमm_driver(rpi_घातer_driver);

MODULE_AUTHOR("Alexander Aring <aar@pengutronix.de>");
MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("Raspberry Pi power domain driver");
MODULE_LICENSE("GPL v2");
