<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2021 NXP Semiconductors
 *
 * The Integrated Endpoपूर्णांक Register Block (IERB) is configured by pre-boot
 * software and is supposed to be to ENETC what a NVRAM is to a 'real' PCIe
 * card. Upon FLR, values from the IERB are transferred to the ENETC PFs, and
 * are पढ़ो-only in the PF memory space.
 *
 * This driver fixes up the घातer-on reset values क्रम the ENETC shared FIFO,
 * such that the TX and RX allocations are sufficient क्रम jumbo frames, and
 * that पूर्णांकelligent FIFO dropping is enabled beक्रमe the पूर्णांकernal data
 * काष्ठाures are corrupted.
 *
 * Even though not all ports might be used on a given board, we are not
 * concerned with partitioning the FIFO, because the शेष values configure
 * no strict reservations, so the entire FIFO can be used by the RX of a single
 * port, or the TX of a single port.
 */

#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश "enetc.h"
#समावेश "enetc_ierb.h"

/* IERB रेजिस्टरs */
#घोषणा ENETC_IERB_TXMBAR(port)			(((port) * 0x100) + 0x8080)
#घोषणा ENETC_IERB_RXMBER(port)			(((port) * 0x100) + 0x8090)
#घोषणा ENETC_IERB_RXMBLR(port)			(((port) * 0x100) + 0x8094)
#घोषणा ENETC_IERB_RXBCR(port)			(((port) * 0x100) + 0x80a0)
#घोषणा ENETC_IERB_TXBCR(port)			(((port) * 0x100) + 0x80a8)
#घोषणा ENETC_IERB_FMBDTR			0xa000

#घोषणा ENETC_RESERVED_FOR_ICM			1024

काष्ठा enetc_ierb अणु
	व्योम __iomem *regs;
पूर्ण;

अटल व्योम enetc_ierb_ग_लिखो(काष्ठा enetc_ierb *ierb, u32 offset, u32 val)
अणु
	ioग_लिखो32(val, ierb->regs + offset);
पूर्ण

पूर्णांक enetc_ierb_रेजिस्टर_pf(काष्ठा platक्रमm_device *pdev,
			   काष्ठा pci_dev *pf_pdev)
अणु
	काष्ठा enetc_ierb *ierb = platक्रमm_get_drvdata(pdev);
	पूर्णांक port = enetc_pf_to_port(pf_pdev);
	u16 tx_credit, rx_credit, tx_alloc;

	अगर (port < 0)
		वापस -ENODEV;

	अगर (!ierb)
		वापस -EPROBE_DEFER;

	/* By शेष, it is recommended to set the Host Transfer Agent
	 * per port transmit byte credit to "1000 + max_frame_size/2".
	 * The घातer-on reset value (1800 bytes) is rounded up to the nearest
	 * 100 assuming a maximum frame size of 1536 bytes.
	 */
	tx_credit = roundup(1000 + ENETC_MAC_MAXFRM_SIZE / 2, 100);

	/* Internal memory allocated क्रम transmit buffering is guaranteed but
	 * not reserved; i.e. अगर the total transmit allocation is not used,
	 * then the unused portion is not left idle, it can be used क्रम receive
	 * buffering but it will be reclaimed, अगर required, from receive by
	 * पूर्णांकelligently dropping alपढ़ोy stored receive frames in the पूर्णांकernal
	 * memory to ensure that the transmit allocation is respected.
	 *
	 * PaTXMBAR must be set to a value larger than
	 *     PaTXBCR + 2 * max_frame_size + 32
	 * अगर frame preemption is not enabled, or to
	 *     2 * PaTXBCR + 2 * p_max_frame_size (pMAC maximum frame size) +
	 *     2 * np_max_frame_size (eMAC maximum frame size) + 64
	 * अगर frame preemption is enabled.
	 */
	tx_alloc = roundup(2 * tx_credit + 4 * ENETC_MAC_MAXFRM_SIZE + 64, 16);

	/* Initial credits, in units of 8 bytes, to the Ingress Congestion
	 * Manager क्रम the maximum amount of bytes the port is allocated क्रम
	 * pending traffic.
	 * It is recommended to set the initial credits to 2 बार the maximum
	 * frame size (2 frames of maximum size).
	 */
	rx_credit = DIV_ROUND_UP(ENETC_MAC_MAXFRM_SIZE * 2, 8);

	enetc_ierb_ग_लिखो(ierb, ENETC_IERB_TXBCR(port), tx_credit);
	enetc_ierb_ग_लिखो(ierb, ENETC_IERB_TXMBAR(port), tx_alloc);
	enetc_ierb_ग_लिखो(ierb, ENETC_IERB_RXBCR(port), rx_credit);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(enetc_ierb_रेजिस्टर_pf);

अटल पूर्णांक enetc_ierb_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा enetc_ierb *ierb;
	काष्ठा resource *res;
	व्योम __iomem *regs;

	ierb = devm_kzalloc(&pdev->dev, माप(*ierb), GFP_KERNEL);
	अगर (!ierb)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	ierb->regs = regs;

	/* Free buffer depletion threshold in bytes.
	 * This sets the minimum amount of मुक्त buffer memory that should be
	 * मुख्यtained in the datapath sub प्रणाली, and when the amount of मुक्त
	 * buffer memory falls below this threshold, a depletion indication is
	 * निश्चितed, which may trigger "intelligent drop" frame releases from
	 * the ingress queues in the ICM.
	 * It is recommended to set the मुक्त buffer depletion threshold to 1024
	 * bytes, since the ICM needs some FIFO memory क्रम its own use.
	 */
	enetc_ierb_ग_लिखो(ierb, ENETC_IERB_FMBDTR, ENETC_RESERVED_FOR_ICM);

	platक्रमm_set_drvdata(pdev, ierb);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_ierb_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id enetc_ierb_match[] = अणु
	अणु .compatible = "fsl,ls1028a-enetc-ierb", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, enetc_ierb_match);

अटल काष्ठा platक्रमm_driver enetc_ierb_driver = अणु
	.driver = अणु
		.name = "fsl-enetc-ierb",
		.of_match_table = enetc_ierb_match,
	पूर्ण,
	.probe = enetc_ierb_probe,
	.हटाओ = enetc_ierb_हटाओ,
पूर्ण;

module_platक्रमm_driver(enetc_ierb_driver);

MODULE_DESCRIPTION("NXP ENETC IERB");
MODULE_LICENSE("Dual BSD/GPL");
