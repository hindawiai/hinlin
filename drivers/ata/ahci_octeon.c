<शैली गुरु>
/*
 * SATA glue क्रम Cavium Octeon III SOCs.
 *
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2010-2015 Cavium Networks
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/octeon/octeon.h>
#समावेश <यंत्र/bitfield.h>

#घोषणा CVMX_SATA_UCTL_SHIM_CFG		0xE8

#घोषणा SATA_UCTL_ENDIAN_MODE_BIG	1
#घोषणा SATA_UCTL_ENDIAN_MODE_LITTLE	0
#घोषणा SATA_UCTL_ENDIAN_MODE_MASK	3

#घोषणा SATA_UCTL_DMA_ENDIAN_MODE_SHIFT	8
#घोषणा SATA_UCTL_CSR_ENDIAN_MODE_SHIFT	0
#घोषणा SATA_UCTL_DMA_READ_CMD_SHIFT	12

अटल पूर्णांक ahci_octeon_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *node = dev->of_node;
	काष्ठा resource *res;
	व्योम __iomem *base;
	u64 cfg;
	पूर्णांक ret;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	cfg = cvmx_पढ़ोq_csr(base + CVMX_SATA_UCTL_SHIM_CFG);

	cfg &= ~(SATA_UCTL_ENDIAN_MODE_MASK << SATA_UCTL_DMA_ENDIAN_MODE_SHIFT);
	cfg &= ~(SATA_UCTL_ENDIAN_MODE_MASK << SATA_UCTL_CSR_ENDIAN_MODE_SHIFT);

#अगर_घोषित __BIG_ENDIAN
	cfg |= SATA_UCTL_ENDIAN_MODE_BIG << SATA_UCTL_DMA_ENDIAN_MODE_SHIFT;
	cfg |= SATA_UCTL_ENDIAN_MODE_BIG << SATA_UCTL_CSR_ENDIAN_MODE_SHIFT;
#अन्यथा
	cfg |= SATA_UCTL_ENDIAN_MODE_LITTLE << SATA_UCTL_DMA_ENDIAN_MODE_SHIFT;
	cfg |= SATA_UCTL_ENDIAN_MODE_LITTLE << SATA_UCTL_CSR_ENDIAN_MODE_SHIFT;
#पूर्ण_अगर

	cfg |= 1 << SATA_UCTL_DMA_READ_CMD_SHIFT;

	cvmx_ग_लिखोq_csr(base + CVMX_SATA_UCTL_SHIM_CFG, cfg);

	अगर (!node) अणु
		dev_err(dev, "no device node, failed to add octeon sata\n");
		वापस -ENODEV;
	पूर्ण

	ret = of_platक्रमm_populate(node, शून्य, शून्य, dev);
	अगर (ret) अणु
		dev_err(dev, "failed to add ahci-platform core\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ahci_octeon_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id octeon_ahci_match[] = अणु
	अणु .compatible = "cavium,octeon-7130-sata-uctl", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, octeon_ahci_match);

अटल काष्ठा platक्रमm_driver ahci_octeon_driver = अणु
	.probe          = ahci_octeon_probe,
	.हटाओ         = ahci_octeon_हटाओ,
	.driver         = अणु
		.name   = "octeon-ahci",
		.of_match_table = octeon_ahci_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(ahci_octeon_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Cavium, Inc. <support@cavium.com>");
MODULE_DESCRIPTION("Cavium Inc. sata config.");
