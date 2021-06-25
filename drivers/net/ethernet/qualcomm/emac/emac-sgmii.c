<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2015-2016, The Linux Foundation. All rights reserved.
 */

/* Qualcomm Technologies, Inc. EMAC SGMII Controller driver.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/acpi.h>
#समावेश <linux/of_device.h>
#समावेश "emac.h"
#समावेश "emac-mac.h"
#समावेश "emac-sgmii.h"

/* EMAC_SGMII रेजिस्टर offsets */
#घोषणा EMAC_SGMII_PHY_AUTONEG_CFG2		0x0048
#घोषणा EMAC_SGMII_PHY_SPEED_CFG1		0x0074
#घोषणा EMAC_SGMII_PHY_IRQ_CMD			0x00ac
#घोषणा EMAC_SGMII_PHY_INTERRUPT_CLEAR		0x00b0
#घोषणा EMAC_SGMII_PHY_INTERRUPT_MASK		0x00b4
#घोषणा EMAC_SGMII_PHY_INTERRUPT_STATUS		0x00b8
#घोषणा EMAC_SGMII_PHY_RX_CHK_STATUS		0x00d4

#घोषणा FORCE_AN_TX_CFG				BIT(5)
#घोषणा FORCE_AN_RX_CFG				BIT(4)
#घोषणा AN_ENABLE				BIT(0)

#घोषणा DUPLEX_MODE				BIT(4)
#घोषणा SPDMODE_1000				BIT(1)
#घोषणा SPDMODE_100				BIT(0)
#घोषणा SPDMODE_10				0

#घोषणा CDR_ALIGN_DET				BIT(6)

#घोषणा IRQ_GLOBAL_CLEAR			BIT(0)

#घोषणा DECODE_CODE_ERR				BIT(7)
#घोषणा DECODE_DISP_ERR				BIT(6)

#घोषणा SGMII_PHY_IRQ_CLR_WAIT_TIME		10

#घोषणा SGMII_PHY_INTERRUPT_ERR		(DECODE_CODE_ERR | DECODE_DISP_ERR)
#घोषणा SGMII_ISR_MASK  		(SGMII_PHY_INTERRUPT_ERR)

#घोषणा SERDES_START_WAIT_TIMES			100

पूर्णांक emac_sgmii_init(काष्ठा emac_adapter *adpt)
अणु
	अगर (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->init))
		वापस 0;

	वापस adpt->phy.sgmii_ops->init(adpt);
पूर्ण

पूर्णांक emac_sgmii_खोलो(काष्ठा emac_adapter *adpt)
अणु
	अगर (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->खोलो))
		वापस 0;

	वापस adpt->phy.sgmii_ops->खोलो(adpt);
पूर्ण

व्योम emac_sgmii_बंद(काष्ठा emac_adapter *adpt)
अणु
	अगर (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->बंद))
		वापस;

	adpt->phy.sgmii_ops->बंद(adpt);
पूर्ण

पूर्णांक emac_sgmii_link_change(काष्ठा emac_adapter *adpt, bool link_state)
अणु
	अगर (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->link_change))
		वापस 0;

	वापस adpt->phy.sgmii_ops->link_change(adpt, link_state);
पूर्ण

व्योम emac_sgmii_reset(काष्ठा emac_adapter *adpt)
अणु
	अगर (!(adpt->phy.sgmii_ops && adpt->phy.sgmii_ops->reset))
		वापस;

	adpt->phy.sgmii_ops->reset(adpt);
पूर्ण

/* Initialize the SGMII link between the पूर्णांकernal and बाह्यal PHYs. */
अटल व्योम emac_sgmii_link_init(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_sgmii *phy = &adpt->phy;
	u32 val;

	/* Always use स्वतःnegotiation. It works no matter how the बाह्यal
	 * PHY is configured.
	 */
	val = पढ़ोl(phy->base + EMAC_SGMII_PHY_AUTONEG_CFG2);
	val &= ~(FORCE_AN_RX_CFG | FORCE_AN_TX_CFG);
	val |= AN_ENABLE;
	ग_लिखोl(val, phy->base + EMAC_SGMII_PHY_AUTONEG_CFG2);
पूर्ण

अटल पूर्णांक emac_sgmii_irq_clear(काष्ठा emac_adapter *adpt, u8 irq_bits)
अणु
	काष्ठा emac_sgmii *phy = &adpt->phy;
	u8 status;

	ग_लिखोl_relaxed(irq_bits, phy->base + EMAC_SGMII_PHY_INTERRUPT_CLEAR);
	ग_लिखोl_relaxed(IRQ_GLOBAL_CLEAR, phy->base + EMAC_SGMII_PHY_IRQ_CMD);
	/* Ensure पूर्णांकerrupt clear command is written to HW */
	wmb();

	/* After set the IRQ_GLOBAL_CLEAR bit, the status clearing must
	 * be confirmed beक्रमe clearing the bits in other रेजिस्टरs.
	 * It takes a few cycles क्रम hw to clear the पूर्णांकerrupt status.
	 */
	अगर (पढ़ोl_poll_समयout_atomic(phy->base +
				      EMAC_SGMII_PHY_INTERRUPT_STATUS,
				      status, !(status & irq_bits), 1,
				      SGMII_PHY_IRQ_CLR_WAIT_TIME)) अणु
		net_err_ratelimited("%s: failed to clear SGMII irq: status:0x%x bits:0x%x\n",
				    adpt->netdev->name, status, irq_bits);
		वापस -EIO;
	पूर्ण

	/* Finalize clearing procedure */
	ग_लिखोl_relaxed(0, phy->base + EMAC_SGMII_PHY_IRQ_CMD);
	ग_लिखोl_relaxed(0, phy->base + EMAC_SGMII_PHY_INTERRUPT_CLEAR);

	/* Ensure that clearing procedure finalization is written to HW */
	wmb();

	वापस 0;
पूर्ण

/* The number of decode errors that triggers a reset */
#घोषणा DECODE_ERROR_LIMIT	2

अटल irqवापस_t emac_sgmii_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा emac_adapter *adpt = data;
	काष्ठा emac_sgmii *phy = &adpt->phy;
	u8 status;

	status = पढ़ोl(phy->base + EMAC_SGMII_PHY_INTERRUPT_STATUS);
	status &= SGMII_ISR_MASK;
	अगर (!status)
		वापस IRQ_HANDLED;

	/* If we get a decoding error and CDR is not locked, then try
	 * resetting the पूर्णांकernal PHY.  The पूर्णांकernal PHY uses an embedded
	 * घड़ी with Clock and Data Recovery (CDR) to recover the
	 * घड़ी and data.
	 */
	अगर (status & SGMII_PHY_INTERRUPT_ERR) अणु
		पूर्णांक count;

		/* The SGMII is capable of recovering from some decode
		 * errors स्वतःmatically.  However, अगर we get multiple
		 * decode errors in a row, then assume that something
		 * is wrong and reset the पूर्णांकerface.
		 */
		count = atomic_inc_वापस(&phy->decode_error_count);
		अगर (count == DECODE_ERROR_LIMIT) अणु
			schedule_work(&adpt->work_thपढ़ो);
			atomic_set(&phy->decode_error_count, 0);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We only care about consecutive decode errors. */
		atomic_set(&phy->decode_error_count, 0);
	पूर्ण

	अगर (emac_sgmii_irq_clear(adpt, status))
		schedule_work(&adpt->work_thपढ़ो);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम emac_sgmii_reset_prepare(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_sgmii *phy = &adpt->phy;
	u32 val;

	/* Reset PHY */
	val = पढ़ोl(phy->base + EMAC_EMAC_WRAPPER_CSR2);
	ग_लिखोl(((val & ~PHY_RESET) | PHY_RESET), phy->base +
	       EMAC_EMAC_WRAPPER_CSR2);
	/* Ensure phy-reset command is written to HW beक्रमe the release cmd */
	msleep(50);
	val = पढ़ोl(phy->base + EMAC_EMAC_WRAPPER_CSR2);
	ग_लिखोl((val & ~PHY_RESET), phy->base + EMAC_EMAC_WRAPPER_CSR2);
	/* Ensure phy-reset release command is written to HW beक्रमe initializing
	 * SGMII
	 */
	msleep(50);
पूर्ण

अटल व्योम emac_sgmii_common_reset(काष्ठा emac_adapter *adpt)
अणु
	पूर्णांक ret;

	emac_sgmii_reset_prepare(adpt);
	emac_sgmii_link_init(adpt);

	ret = emac_sgmii_init(adpt);
	अगर (ret)
		netdev_err(adpt->netdev,
			   "could not reinitialize internal PHY (error=%i)\n",
			   ret);
पूर्ण

अटल पूर्णांक emac_sgmii_common_खोलो(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_sgmii *sgmii = &adpt->phy;
	पूर्णांक ret;

	अगर (sgmii->irq) अणु
		/* Make sure पूर्णांकerrupts are cleared and disabled first */
		ret = emac_sgmii_irq_clear(adpt, 0xff);
		अगर (ret)
			वापस ret;
		ग_लिखोl(0, sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);

		ret = request_irq(sgmii->irq, emac_sgmii_पूर्णांकerrupt, 0,
				  "emac-sgmii", adpt);
		अगर (ret) अणु
			netdev_err(adpt->netdev,
				   "could not register handler for internal PHY\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम emac_sgmii_common_बंद(काष्ठा emac_adapter *adpt)
अणु
	काष्ठा emac_sgmii *sgmii = &adpt->phy;

	/* Make sure पूर्णांकerrupts are disabled */
	ग_लिखोl(0, sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);
	मुक्त_irq(sgmii->irq, adpt);
पूर्ण

/* The error पूर्णांकerrupts are only valid after the link is up */
अटल पूर्णांक emac_sgmii_common_link_change(काष्ठा emac_adapter *adpt, bool linkup)
अणु
	काष्ठा emac_sgmii *sgmii = &adpt->phy;
	पूर्णांक ret;

	अगर (linkup) अणु
		/* Clear and enable पूर्णांकerrupts */
		ret = emac_sgmii_irq_clear(adpt, 0xff);
		अगर (ret)
			वापस ret;

		ग_लिखोl(SGMII_ISR_MASK,
		       sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);
	पूर्ण अन्यथा अणु
		/* Disable पूर्णांकerrupts */
		ग_लिखोl(0, sgmii->base + EMAC_SGMII_PHY_INTERRUPT_MASK);
		synchronize_irq(sgmii->irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा sgmii_ops fsm9900_ops = अणु
	.init = emac_sgmii_init_fsm9900,
	.खोलो = emac_sgmii_common_खोलो,
	.बंद = emac_sgmii_common_बंद,
	.link_change = emac_sgmii_common_link_change,
	.reset = emac_sgmii_common_reset,
पूर्ण;

अटल काष्ठा sgmii_ops qdf2432_ops = अणु
	.init = emac_sgmii_init_qdf2432,
	.खोलो = emac_sgmii_common_खोलो,
	.बंद = emac_sgmii_common_बंद,
	.link_change = emac_sgmii_common_link_change,
	.reset = emac_sgmii_common_reset,
पूर्ण;

#अगर_घोषित CONFIG_ACPI
अटल काष्ठा sgmii_ops qdf2400_ops = अणु
	.init = emac_sgmii_init_qdf2400,
	.खोलो = emac_sgmii_common_खोलो,
	.बंद = emac_sgmii_common_बंद,
	.link_change = emac_sgmii_common_link_change,
	.reset = emac_sgmii_common_reset,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक emac_sgmii_acpi_match(काष्ठा device *dev, व्योम *data)
अणु
#अगर_घोषित CONFIG_ACPI
	अटल स्थिर काष्ठा acpi_device_id match_table[] = अणु
		अणु
			.id = "QCOM8071",
		पूर्ण,
		अणुपूर्ण
	पूर्ण;
	स्थिर काष्ठा acpi_device_id *id = acpi_match_device(match_table, dev);
	काष्ठा sgmii_ops **ops = data;

	अगर (id) अणु
		acpi_handle handle = ACPI_HANDLE(dev);
		अचिन्हित दीर्घ दीर्घ hrv;
		acpi_status status;

		status = acpi_evaluate_पूर्णांकeger(handle, "_HRV", शून्य, &hrv);
		अगर (status) अणु
			अगर (status == AE_NOT_FOUND)
				/* Older versions of the QDF2432 ACPI tables करो
				 * not have an _HRV property.
				 */
				hrv = 1;
			अन्यथा
				/* Something is wrong with the tables */
				वापस 0;
		पूर्ण

		चयन (hrv) अणु
		हाल 1:
			*ops = &qdf2432_ops;
			वापस 1;
		हाल 2:
			*ops = &qdf2400_ops;
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id emac_sgmii_dt_match[] = अणु
	अणु
		.compatible = "qcom,fsm9900-emac-sgmii",
		.data = &fsm9900_ops,
	पूर्ण,
	अणु
		.compatible = "qcom,qdf2432-emac-sgmii",
		.data = &qdf2432_ops,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक emac_sgmii_config(काष्ठा platक्रमm_device *pdev, काष्ठा emac_adapter *adpt)
अणु
	काष्ठा platक्रमm_device *sgmii_pdev = शून्य;
	काष्ठा emac_sgmii *phy = &adpt->phy;
	काष्ठा resource *res;
	पूर्णांक ret;

	अगर (has_acpi_companion(&pdev->dev)) अणु
		काष्ठा device *dev;

		dev = device_find_child(&pdev->dev, &phy->sgmii_ops,
					emac_sgmii_acpi_match);

		अगर (!dev) अणु
			dev_warn(&pdev->dev, "cannot find internal phy node\n");
			वापस 0;
		पूर्ण

		sgmii_pdev = to_platक्रमm_device(dev);
	पूर्ण अन्यथा अणु
		स्थिर काष्ठा of_device_id *match;
		काष्ठा device_node *np;

		np = of_parse_phandle(pdev->dev.of_node, "internal-phy", 0);
		अगर (!np) अणु
			dev_err(&pdev->dev, "missing internal-phy property\n");
			वापस -ENODEV;
		पूर्ण

		sgmii_pdev = of_find_device_by_node(np);
		of_node_put(np);
		अगर (!sgmii_pdev) अणु
			dev_err(&pdev->dev, "invalid internal-phy property\n");
			वापस -ENODEV;
		पूर्ण

		match = of_match_device(emac_sgmii_dt_match, &sgmii_pdev->dev);
		अगर (!match) अणु
			dev_err(&pdev->dev, "unrecognized internal phy node\n");
			ret = -ENODEV;
			जाओ error_put_device;
		पूर्ण

		phy->sgmii_ops = (काष्ठा sgmii_ops *)match->data;
	पूर्ण

	/* Base address is the first address */
	res = platक्रमm_get_resource(sgmii_pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -EINVAL;
		जाओ error_put_device;
	पूर्ण

	phy->base = ioremap(res->start, resource_size(res));
	अगर (!phy->base) अणु
		ret = -ENOMEM;
		जाओ error_put_device;
	पूर्ण

	/* v2 SGMII has a per-lane digital digital, so parse it अगर it exists */
	res = platक्रमm_get_resource(sgmii_pdev, IORESOURCE_MEM, 1);
	अगर (res) अणु
		phy->digital = ioremap(res->start, resource_size(res));
		अगर (!phy->digital) अणु
			ret = -ENOMEM;
			जाओ error_unmap_base;
		पूर्ण
	पूर्ण

	ret = emac_sgmii_init(adpt);
	अगर (ret)
		जाओ error;

	emac_sgmii_link_init(adpt);

	ret = platक्रमm_get_irq(sgmii_pdev, 0);
	अगर (ret > 0)
		phy->irq = ret;

	/* We've remapped the addresses, so we don't need the device any
	 * more.  of_find_device_by_node() says we should release it.
	 */
	put_device(&sgmii_pdev->dev);

	वापस 0;

error:
	अगर (phy->digital)
		iounmap(phy->digital);
error_unmap_base:
	iounmap(phy->base);
error_put_device:
	put_device(&sgmii_pdev->dev);

	वापस ret;
पूर्ण
