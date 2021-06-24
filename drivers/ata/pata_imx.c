<शैली गुरु>
/*
 * Freescale iMX PATA driver
 *
 * Copyright (C) 2011 Arnaud Patard <arnaud.patard@rtp-net.org>
 *
 * Based on pata_platक्रमm - Copyright (C) 2006 - 2007  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * TODO:
 * - dmaengine support
 */

#समावेश <linux/ata.h>
#समावेश <linux/clk.h>
#समावेश <linux/libata.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "pata_imx"

#घोषणा PATA_IMX_ATA_TIME_OFF		0x00
#घोषणा PATA_IMX_ATA_TIME_ON		0x01
#घोषणा PATA_IMX_ATA_TIME_1		0x02
#घोषणा PATA_IMX_ATA_TIME_2W		0x03
#घोषणा PATA_IMX_ATA_TIME_2R		0x04
#घोषणा PATA_IMX_ATA_TIME_AX		0x05
#घोषणा PATA_IMX_ATA_TIME_PIO_RDX	0x06
#घोषणा PATA_IMX_ATA_TIME_4		0x07
#घोषणा PATA_IMX_ATA_TIME_9		0x08

#घोषणा PATA_IMX_ATA_CONTROL		0x24
#घोषणा PATA_IMX_ATA_CTRL_FIFO_RST_B	(1<<7)
#घोषणा PATA_IMX_ATA_CTRL_ATA_RST_B	(1<<6)
#घोषणा PATA_IMX_ATA_CTRL_IORDY_EN	(1<<0)
#घोषणा PATA_IMX_ATA_INT_EN		0x2C
#घोषणा PATA_IMX_ATA_INTR_ATA_INTRQ2	(1<<3)
#घोषणा PATA_IMX_DRIVE_DATA		0xA0
#घोषणा PATA_IMX_DRIVE_CONTROL		0xD8

अटल u32 pio_t4[] = अणु 30,  20,  15,  10,  10 पूर्ण;
अटल u32 pio_t9[] = अणु 20,  15,  10,  10,  10 पूर्ण;
अटल u32 pio_tA[] = अणु 35,  35,  35,  35,  35 पूर्ण;

काष्ठा pata_imx_priv अणु
	काष्ठा clk *clk;
	/* timings/पूर्णांकerrupt/control regs */
	व्योम __iomem *host_regs;
	u32 ata_ctl;
पूर्ण;

अटल व्योम pata_imx_set_timing(काष्ठा ata_device *adev,
				काष्ठा pata_imx_priv *priv)
अणु
	काष्ठा ata_timing timing;
	अचिन्हित दीर्घ clkrate;
	u32 T, mode;

	clkrate = clk_get_rate(priv->clk);

	अगर (adev->pio_mode < XFER_PIO_0 || adev->pio_mode > XFER_PIO_4 ||
	    !clkrate)
		वापस;

	T = 1000000000 / clkrate;
	ata_timing_compute(adev, adev->pio_mode, &timing, T * 1000, 0);

	mode = adev->pio_mode - XFER_PIO_0;

	ग_लिखोb(3, priv->host_regs + PATA_IMX_ATA_TIME_OFF);
	ग_लिखोb(3, priv->host_regs + PATA_IMX_ATA_TIME_ON);
	ग_लिखोb(timing.setup, priv->host_regs + PATA_IMX_ATA_TIME_1);
	ग_लिखोb(timing.act8b, priv->host_regs + PATA_IMX_ATA_TIME_2W);
	ग_लिखोb(timing.act8b, priv->host_regs + PATA_IMX_ATA_TIME_2R);
	ग_लिखोb(1, priv->host_regs + PATA_IMX_ATA_TIME_PIO_RDX);

	ग_लिखोb(pio_t4[mode] / T + 1, priv->host_regs + PATA_IMX_ATA_TIME_4);
	ग_लिखोb(pio_t9[mode] / T + 1, priv->host_regs + PATA_IMX_ATA_TIME_9);
	ग_लिखोb(pio_tA[mode] / T + 1, priv->host_regs + PATA_IMX_ATA_TIME_AX);
पूर्ण

अटल व्योम pata_imx_set_piomode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pata_imx_priv *priv = ap->host->निजी_data;
	u32 val;

	pata_imx_set_timing(adev, priv);

	val = __raw_पढ़ोl(priv->host_regs + PATA_IMX_ATA_CONTROL);
	अगर (ata_pio_need_iordy(adev))
		val |= PATA_IMX_ATA_CTRL_IORDY_EN;
	अन्यथा
		val &= ~PATA_IMX_ATA_CTRL_IORDY_EN;
	__raw_ग_लिखोl(val, priv->host_regs + PATA_IMX_ATA_CONTROL);
पूर्ण

अटल काष्ठा scsi_host_ढाँचा pata_imx_sht = अणु
	ATA_PIO_SHT(DRV_NAME),
पूर्ण;

अटल काष्ठा ata_port_operations pata_imx_port_ops = अणु
	.inherits		= &ata_sff_port_ops,
	.sff_data_xfer		= ata_sff_data_xfer32,
	.cable_detect		= ata_cable_unknown,
	.set_piomode		= pata_imx_set_piomode,
पूर्ण;

अटल व्योम pata_imx_setup_port(काष्ठा ata_ioports *ioaddr)
अणु
	/* Fixup the port shअगरt क्रम platक्रमms that need it */
	ioaddr->data_addr	= ioaddr->cmd_addr + (ATA_REG_DATA    << 2);
	ioaddr->error_addr	= ioaddr->cmd_addr + (ATA_REG_ERR     << 2);
	ioaddr->feature_addr	= ioaddr->cmd_addr + (ATA_REG_FEATURE << 2);
	ioaddr->nsect_addr	= ioaddr->cmd_addr + (ATA_REG_NSECT   << 2);
	ioaddr->lbal_addr	= ioaddr->cmd_addr + (ATA_REG_LBAL    << 2);
	ioaddr->lbam_addr	= ioaddr->cmd_addr + (ATA_REG_LBAM    << 2);
	ioaddr->lbah_addr	= ioaddr->cmd_addr + (ATA_REG_LBAH    << 2);
	ioaddr->device_addr	= ioaddr->cmd_addr + (ATA_REG_DEVICE  << 2);
	ioaddr->status_addr	= ioaddr->cmd_addr + (ATA_REG_STATUS  << 2);
	ioaddr->command_addr	= ioaddr->cmd_addr + (ATA_REG_CMD     << 2);
पूर्ण

अटल पूर्णांक pata_imx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host;
	काष्ठा ata_port *ap;
	काष्ठा pata_imx_priv *priv;
	पूर्णांक irq = 0;
	काष्ठा resource *io_res;
	पूर्णांक ret;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	priv = devm_kzalloc(&pdev->dev,
				माप(काष्ठा pata_imx_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(priv->clk)) अणु
		dev_err(&pdev->dev, "Failed to get clock\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण

	ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	host = ata_host_alloc(&pdev->dev, 1);
	अगर (!host) अणु
		ret = -ENOMEM;
		जाओ err;
	पूर्ण

	host->निजी_data = priv;
	ap = host->ports[0];

	ap->ops = &pata_imx_port_ops;
	ap->pio_mask = ATA_PIO4;
	ap->flags |= ATA_FLAG_SLAVE_POSS;

	io_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->host_regs = devm_ioremap_resource(&pdev->dev, io_res);
	अगर (IS_ERR(priv->host_regs)) अणु
		ret = PTR_ERR(priv->host_regs);
		जाओ err;
	पूर्ण

	ap->ioaddr.cmd_addr = priv->host_regs + PATA_IMX_DRIVE_DATA;
	ap->ioaddr.ctl_addr = priv->host_regs + PATA_IMX_DRIVE_CONTROL;

	ap->ioaddr.altstatus_addr = ap->ioaddr.ctl_addr;

	pata_imx_setup_port(&ap->ioaddr);

	ata_port_desc(ap, "cmd 0x%llx ctl 0x%llx",
		(अचिन्हित दीर्घ दीर्घ)io_res->start + PATA_IMX_DRIVE_DATA,
		(अचिन्हित दीर्घ दीर्घ)io_res->start + PATA_IMX_DRIVE_CONTROL);

	/* deनिश्चित resets */
	__raw_ग_लिखोl(PATA_IMX_ATA_CTRL_FIFO_RST_B |
			PATA_IMX_ATA_CTRL_ATA_RST_B,
			priv->host_regs + PATA_IMX_ATA_CONTROL);
	/* enable पूर्णांकerrupts */
	__raw_ग_लिखोl(PATA_IMX_ATA_INTR_ATA_INTRQ2,
			priv->host_regs + PATA_IMX_ATA_INT_EN);

	/* activate */
	ret = ata_host_activate(host, irq, ata_sff_पूर्णांकerrupt, 0,
				&pata_imx_sht);

	अगर (ret)
		जाओ err;

	वापस 0;
err:
	clk_disable_unprepare(priv->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक pata_imx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ata_host *host = platक्रमm_get_drvdata(pdev);
	काष्ठा pata_imx_priv *priv = host->निजी_data;

	ata_host_detach(host);

	__raw_ग_लिखोl(0, priv->host_regs + PATA_IMX_ATA_INT_EN);

	clk_disable_unprepare(priv->clk);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक pata_imx_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा pata_imx_priv *priv = host->निजी_data;
	पूर्णांक ret;

	ret = ata_host_suspend(host, PMSG_SUSPEND);
	अगर (!ret) अणु
		__raw_ग_लिखोl(0, priv->host_regs + PATA_IMX_ATA_INT_EN);
		priv->ata_ctl =
			__raw_पढ़ोl(priv->host_regs + PATA_IMX_ATA_CONTROL);
		clk_disable_unprepare(priv->clk);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक pata_imx_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा pata_imx_priv *priv = host->निजी_data;

	पूर्णांक ret = clk_prepare_enable(priv->clk);
	अगर (ret)
		वापस ret;

	__raw_ग_लिखोl(priv->ata_ctl, priv->host_regs + PATA_IMX_ATA_CONTROL);

	__raw_ग_लिखोl(PATA_IMX_ATA_INTR_ATA_INTRQ2,
			priv->host_regs + PATA_IMX_ATA_INT_EN);

	ata_host_resume(host);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(pata_imx_pm_ops, pata_imx_suspend, pata_imx_resume);

अटल स्थिर काष्ठा of_device_id imx_pata_dt_ids[] = अणु
	अणु
		.compatible = "fsl,imx27-pata",
	पूर्ण, अणु
		/* sentinel */
	पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, imx_pata_dt_ids);

अटल काष्ठा platक्रमm_driver pata_imx_driver = अणु
	.probe		= pata_imx_probe,
	.हटाओ		= pata_imx_हटाओ,
	.driver = अणु
		.name		= DRV_NAME,
		.of_match_table	= imx_pata_dt_ids,
		.pm		= &pata_imx_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pata_imx_driver);

MODULE_AUTHOR("Arnaud Patard <arnaud.patard@rtp-net.org>");
MODULE_DESCRIPTION("low-level driver for iMX PATA");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
