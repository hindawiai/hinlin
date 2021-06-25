<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Raspberry Pi 4 firmware reset driver
 *
 * Copyright (C) 2020 Nicolas Saenz Julienne <nsaenzjulienne@suse.de>
 */
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/reset-controller.h>
#समावेश <soc/bcm2835/raspberrypi-firmware.h>
#समावेश <dt-bindings/reset/raspberrypi,firmware-reset.h>

काष्ठा rpi_reset अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा rpi_firmware *fw;
पूर्ण;

अटल अंतरभूत काष्ठा rpi_reset *to_rpi(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा rpi_reset, rcdev);
पूर्ण

अटल पूर्णांक rpi_reset_reset(काष्ठा reset_controller_dev *rcdev, अचिन्हित दीर्घ id)
अणु
	काष्ठा rpi_reset *priv = to_rpi(rcdev);
	u32 dev_addr;
	पूर्णांक ret;

	चयन (id) अणु
	हाल RASPBERRYPI_FIRMWARE_RESET_ID_USB:
		/*
		 * The Raspberry Pi 4 माला_लो its USB functionality from VL805, a
		 * PCIe chip that implements xHCI. After a PCI reset, VL805's
		 * firmware may either be loaded directly from an EEPROM or, अगर
		 * not present, by the SoC's co-processor, VideoCore. rpi's
		 * VideoCore OS contains both the non खुला firmware load
		 * logic and the VL805 firmware blob. This triggers the
		 * aक्रमementioned process.
		 *
		 * The pci device address is expected is expected by the
		 * firmware encoded like this:
		 *
		 *	PCI_BUS << 20 | PCI_SLOT << 15 | PCI_FUNC << 12
		 *
		 * But since rpi's PCIe is hardwired, we know the address in
		 * advance.
		 */
		dev_addr = 0x100000;
		ret = rpi_firmware_property(priv->fw, RPI_FIRMWARE_NOTIFY_XHCI_RESET,
					    &dev_addr, माप(dev_addr));
		अगर (ret)
			वापस ret;

		/* Wait क्रम vl805 to startup */
		usleep_range(200, 1000);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops rpi_reset_ops = अणु
	.reset	= rpi_reset_reset,
पूर्ण;

अटल पूर्णांक rpi_reset_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा rpi_firmware *fw;
	काष्ठा device_node *np;
	काष्ठा rpi_reset *priv;

	np = of_get_parent(dev->of_node);
	अगर (!np) अणु
		dev_err(dev, "Missing firmware node\n");
		वापस -ENOENT;
	पूर्ण

	fw = devm_rpi_firmware_get(&pdev->dev, np);
	of_node_put(np);
	अगर (!fw)
		वापस -EPROBE_DEFER;

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	dev_set_drvdata(dev, priv);

	priv->fw = fw;
	priv->rcdev.owner = THIS_MODULE;
	priv->rcdev.nr_resets = RASPBERRYPI_FIRMWARE_RESET_NUM_IDS;
	priv->rcdev.ops = &rpi_reset_ops;
	priv->rcdev.of_node = dev->of_node;

	वापस devm_reset_controller_रेजिस्टर(dev, &priv->rcdev);
पूर्ण

अटल स्थिर काष्ठा of_device_id rpi_reset_of_match[] = अणु
	अणु .compatible = "raspberrypi,firmware-reset" पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rpi_reset_of_match);

अटल काष्ठा platक्रमm_driver rpi_reset_driver = अणु
	.probe	= rpi_reset_probe,
	.driver	= अणु
		.name = "raspberrypi-reset",
		.of_match_table = rpi_reset_of_match,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(rpi_reset_driver);

MODULE_AUTHOR("Nicolas Saenz Julienne <nsaenzjulienne@suse.de>");
MODULE_DESCRIPTION("Raspberry Pi 4 firmware reset driver");
MODULE_LICENSE("GPL");
