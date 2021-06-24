<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 STMicroelectronics Limited
 *
 * Authors: Francesco Virlinzi <francesco.virlinzi@st.com>
 *	    Alexandre Torgue <alexandre.torgue@st.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/export.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/of.h>
#समावेश <linux/ahci_platक्रमm.h>
#समावेश <linux/libata.h>
#समावेश <linux/reset.h>
#समावेश <linux/पन.स>
#समावेश <linux/dma-mapping.h>

#समावेश "ahci.h"

#घोषणा DRV_NAME  "st_ahci"

#घोषणा ST_AHCI_OOBR			0xbc
#घोषणा ST_AHCI_OOBR_WE			BIT(31)
#घोषणा ST_AHCI_OOBR_CWMIN_SHIFT	24
#घोषणा ST_AHCI_OOBR_CWMAX_SHIFT	16
#घोषणा ST_AHCI_OOBR_CIMIN_SHIFT	8
#घोषणा ST_AHCI_OOBR_CIMAX_SHIFT	0

काष्ठा st_ahci_drv_data अणु
	काष्ठा platक्रमm_device *ahci;
	काष्ठा reset_control *pwr;
	काष्ठा reset_control *sw_rst;
	काष्ठा reset_control *pwr_rst;
पूर्ण;

अटल व्योम st_ahci_configure_oob(व्योम __iomem *mmio)
अणु
	अचिन्हित दीर्घ old_val, new_val;

	new_val = (0x02 << ST_AHCI_OOBR_CWMIN_SHIFT) |
		  (0x04 << ST_AHCI_OOBR_CWMAX_SHIFT) |
		  (0x08 << ST_AHCI_OOBR_CIMIN_SHIFT) |
		  (0x0C << ST_AHCI_OOBR_CIMAX_SHIFT);

	old_val = पढ़ोl(mmio + ST_AHCI_OOBR);
	ग_लिखोl(old_val | ST_AHCI_OOBR_WE, mmio + ST_AHCI_OOBR);
	ग_लिखोl(new_val | ST_AHCI_OOBR_WE, mmio + ST_AHCI_OOBR);
	ग_लिखोl(new_val, mmio + ST_AHCI_OOBR);
पूर्ण

अटल पूर्णांक st_ahci_deनिश्चित_resets(काष्ठा ahci_host_priv *hpriv,
				काष्ठा device *dev)
अणु
	काष्ठा st_ahci_drv_data *drv_data = hpriv->plat_data;
	पूर्णांक err;

	अगर (drv_data->pwr) अणु
		err = reset_control_deनिश्चित(drv_data->pwr);
		अगर (err) अणु
			dev_err(dev, "unable to bring out of pwrdwn\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (drv_data->sw_rst) अणु
		err = reset_control_deनिश्चित(drv_data->sw_rst);
		अगर (err) अणु
			dev_err(dev, "unable to bring out of sw-rst\n");
			वापस err;
		पूर्ण
	पूर्ण

	अगर (drv_data->pwr_rst) अणु
		err = reset_control_deनिश्चित(drv_data->pwr_rst);
		अगर (err) अणु
			dev_err(dev, "unable to bring out of pwr-rst\n");
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम st_ahci_host_stop(काष्ठा ata_host *host)
अणु
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा st_ahci_drv_data *drv_data = hpriv->plat_data;
	काष्ठा device *dev = host->dev;
	पूर्णांक err;

	अगर (drv_data->pwr) अणु
		err = reset_control_निश्चित(drv_data->pwr);
		अगर (err)
			dev_err(dev, "unable to pwrdwn\n");
	पूर्ण

	ahci_platक्रमm_disable_resources(hpriv);
पूर्ण

अटल पूर्णांक st_ahci_probe_resets(काष्ठा ahci_host_priv *hpriv,
				काष्ठा device *dev)
अणु
	काष्ठा st_ahci_drv_data *drv_data = hpriv->plat_data;

	drv_data->pwr = devm_reset_control_get(dev, "pwr-dwn");
	अगर (IS_ERR(drv_data->pwr)) अणु
		dev_info(dev, "power reset control not defined\n");
		drv_data->pwr = शून्य;
	पूर्ण

	drv_data->sw_rst = devm_reset_control_get(dev, "sw-rst");
	अगर (IS_ERR(drv_data->sw_rst)) अणु
		dev_info(dev, "soft reset control not defined\n");
		drv_data->sw_rst = शून्य;
	पूर्ण

	drv_data->pwr_rst = devm_reset_control_get(dev, "pwr-rst");
	अगर (IS_ERR(drv_data->pwr_rst)) अणु
		dev_dbg(dev, "power soft reset control not defined\n");
		drv_data->pwr_rst = शून्य;
	पूर्ण

	वापस st_ahci_deनिश्चित_resets(hpriv, dev);
पूर्ण

अटल काष्ठा ata_port_operations st_ahci_port_ops = अणु
	.inherits	= &ahci_platक्रमm_ops,
	.host_stop	= st_ahci_host_stop,
पूर्ण;

अटल स्थिर काष्ठा ata_port_info st_ahci_port_info = अणु
	.flags          = AHCI_FLAG_COMMON,
	.pio_mask       = ATA_PIO4,
	.udma_mask      = ATA_UDMA6,
	.port_ops       = &st_ahci_port_ops,
पूर्ण;

अटल काष्ठा scsi_host_ढाँचा ahci_platक्रमm_sht = अणु
	AHCI_SHT(DRV_NAME),
पूर्ण;

अटल पूर्णांक st_ahci_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा st_ahci_drv_data *drv_data;
	काष्ठा ahci_host_priv *hpriv;
	पूर्णांक err;

	drv_data = devm_kzalloc(&pdev->dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	hpriv = ahci_platक्रमm_get_resources(pdev, 0);
	अगर (IS_ERR(hpriv))
		वापस PTR_ERR(hpriv);
	hpriv->plat_data = drv_data;

	err = st_ahci_probe_resets(hpriv, &pdev->dev);
	अगर (err)
		वापस err;

	err = ahci_platक्रमm_enable_resources(hpriv);
	अगर (err)
		वापस err;

	st_ahci_configure_oob(hpriv->mmio);

	of_property_पढ़ो_u32(dev->of_node,
			     "ports-implemented", &hpriv->क्रमce_port_map);

	err = ahci_platक्रमm_init_host(pdev, hpriv, &st_ahci_port_info,
				      &ahci_platक्रमm_sht);
	अगर (err) अणु
		ahci_platक्रमm_disable_resources(hpriv);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक st_ahci_suspend(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	काष्ठा st_ahci_drv_data *drv_data = hpriv->plat_data;
	पूर्णांक err;

	err = ahci_platक्रमm_suspend_host(dev);
	अगर (err)
		वापस err;

	अगर (drv_data->pwr) अणु
		err = reset_control_निश्चित(drv_data->pwr);
		अगर (err) अणु
			dev_err(dev, "unable to pwrdwn");
			वापस err;
		पूर्ण
	पूर्ण

	ahci_platक्रमm_disable_resources(hpriv);

	वापस 0;
पूर्ण

अटल पूर्णांक st_ahci_resume(काष्ठा device *dev)
अणु
	काष्ठा ata_host *host = dev_get_drvdata(dev);
	काष्ठा ahci_host_priv *hpriv = host->निजी_data;
	पूर्णांक err;

	err = ahci_platक्रमm_enable_resources(hpriv);
	अगर (err)
		वापस err;

	err = st_ahci_deनिश्चित_resets(hpriv, dev);
	अगर (err) अणु
		ahci_platक्रमm_disable_resources(hpriv);
		वापस err;
	पूर्ण

	st_ahci_configure_oob(hpriv->mmio);

	वापस ahci_platक्रमm_resume_host(dev);
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(st_ahci_pm_ops, st_ahci_suspend, st_ahci_resume);

अटल स्थिर काष्ठा of_device_id st_ahci_match[] = अणु
	अणु .compatible = "st,ahci", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, st_ahci_match);

अटल काष्ठा platक्रमm_driver st_ahci_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &st_ahci_pm_ops,
		.of_match_table = of_match_ptr(st_ahci_match),
	पूर्ण,
	.probe = st_ahci_probe,
	.हटाओ = ata_platक्रमm_हटाओ_one,
पूर्ण;
module_platक्रमm_driver(st_ahci_driver);

MODULE_AUTHOR("Alexandre Torgue <alexandre.torgue@st.com>");
MODULE_AUTHOR("Francesco Virlinzi <francesco.virlinzi@st.com>");
MODULE_DESCRIPTION("STMicroelectronics SATA AHCI Driver");
MODULE_LICENSE("GPL v2");
