<शैली गुरु>
/*
 * Marvell NFC-over-SPI driver: SPI पूर्णांकerface related functions
 *
 * Copyright (C) 2015, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available on the worldwide web at
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 **/

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/nfc.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_gpपन.स>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश <linux/spi/spi.h>
#समावेश "nfcmrvl.h"

#घोषणा SPI_WAIT_HANDSHAKE	1

काष्ठा nfcmrvl_spi_drv_data अणु
	अचिन्हित दीर्घ flags;
	काष्ठा spi_device *spi;
	काष्ठा nci_spi *nci_spi;
	काष्ठा completion handshake_completion;
	काष्ठा nfcmrvl_निजी *priv;
पूर्ण;

अटल irqवापस_t nfcmrvl_spi_पूर्णांक_irq_thपढ़ो_fn(पूर्णांक irq, व्योम *drv_data_ptr)
अणु
	काष्ठा nfcmrvl_spi_drv_data *drv_data = drv_data_ptr;
	काष्ठा sk_buff *skb;

	/*
	 * Special हाल where we are रुकोing क्रम SPI_INT deनिश्चितion to start a
	 * transfer.
	 */
	अगर (test_and_clear_bit(SPI_WAIT_HANDSHAKE, &drv_data->flags)) अणु
		complete(&drv_data->handshake_completion);
		वापस IRQ_HANDLED;
	पूर्ण

	/* Normal हाल, SPI_INT deनिश्चितed by slave to trigger a master पढ़ो */

	skb = nci_spi_पढ़ो(drv_data->nci_spi);
	अगर (!skb) अणु
		nfc_err(&drv_data->spi->dev, "failed to read spi packet");
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (nfcmrvl_nci_recv_frame(drv_data->priv, skb) < 0)
		nfc_err(&drv_data->spi->dev, "corrupted RX packet");

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक nfcmrvl_spi_nci_खोलो(काष्ठा nfcmrvl_निजी *priv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_spi_nci_बंद(काष्ठा nfcmrvl_निजी *priv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_spi_nci_send(काष्ठा nfcmrvl_निजी *priv,
				काष्ठा sk_buff *skb)
अणु
	काष्ठा nfcmrvl_spi_drv_data *drv_data = priv->drv_data;
	पूर्णांक err;

	/* Reinit completion क्रम slave handshake */
	reinit_completion(&drv_data->handshake_completion);
	set_bit(SPI_WAIT_HANDSHAKE, &drv_data->flags);

	/*
	 * Append a dummy byte at the end of SPI frame. This is due to a
	 * specअगरic DMA implementation in the controller
	 */
	skb_put(skb, 1);

	/* Send the SPI packet */
	err = nci_spi_send(drv_data->nci_spi, &drv_data->handshake_completion,
			   skb);
	अगर (err)
		nfc_err(priv->dev, "spi_send failed %d", err);

	वापस err;
पूर्ण

अटल व्योम nfcmrvl_spi_nci_update_config(काष्ठा nfcmrvl_निजी *priv,
					  स्थिर व्योम *param)
अणु
	काष्ठा nfcmrvl_spi_drv_data *drv_data = priv->drv_data;
	स्थिर काष्ठा nfcmrvl_fw_spi_config *config = param;

	drv_data->nci_spi->xfer_speed_hz = config->clk;
पूर्ण

अटल काष्ठा nfcmrvl_अगर_ops spi_ops = अणु
	.nci_खोलो = nfcmrvl_spi_nci_खोलो,
	.nci_बंद = nfcmrvl_spi_nci_बंद,
	.nci_send = nfcmrvl_spi_nci_send,
	.nci_update_config = nfcmrvl_spi_nci_update_config,
पूर्ण;

अटल पूर्णांक nfcmrvl_spi_parse_dt(काष्ठा device_node *node,
				काष्ठा nfcmrvl_platक्रमm_data *pdata)
अणु
	पूर्णांक ret;

	ret = nfcmrvl_parse_dt(node, pdata);
	अगर (ret < 0) अणु
		pr_err("Failed to get generic entries\n");
		वापस ret;
	पूर्ण

	ret = irq_of_parse_and_map(node, 0);
	अगर (ret < 0) अणु
		pr_err("Unable to get irq, error: %d\n", ret);
		वापस ret;
	पूर्ण
	pdata->irq = ret;

	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_spi_probe(काष्ठा spi_device *spi)
अणु
	काष्ठा nfcmrvl_platक्रमm_data *pdata;
	काष्ठा nfcmrvl_platक्रमm_data config;
	काष्ठा nfcmrvl_spi_drv_data *drv_data;
	पूर्णांक ret = 0;

	drv_data = devm_kzalloc(&spi->dev, माप(*drv_data), GFP_KERNEL);
	अगर (!drv_data)
		वापस -ENOMEM;

	drv_data->spi = spi;
	drv_data->priv = शून्य;
	spi_set_drvdata(spi, drv_data);

	pdata = spi->dev.platक्रमm_data;

	अगर (!pdata && spi->dev.of_node)
		अगर (nfcmrvl_spi_parse_dt(spi->dev.of_node, &config) == 0)
			pdata = &config;

	अगर (!pdata)
		वापस -EINVAL;

	ret = devm_request_thपढ़ोed_irq(&drv_data->spi->dev, pdata->irq,
					शून्य, nfcmrvl_spi_पूर्णांक_irq_thपढ़ो_fn,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					"nfcmrvl_spi_int", drv_data);
	अगर (ret < 0) अणु
		nfc_err(&drv_data->spi->dev, "Unable to register IRQ handler");
		वापस -ENODEV;
	पूर्ण

	drv_data->priv = nfcmrvl_nci_रेजिस्टर_dev(NFCMRVL_PHY_SPI,
						  drv_data, &spi_ops,
						  &drv_data->spi->dev,
						  pdata);
	अगर (IS_ERR(drv_data->priv))
		वापस PTR_ERR(drv_data->priv);

	drv_data->priv->support_fw_dnld = true;

	drv_data->nci_spi = nci_spi_allocate_spi(drv_data->spi, 0, 10,
						 drv_data->priv->ndev);

	/* Init completion क्रम slave handshake */
	init_completion(&drv_data->handshake_completion);
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_spi_हटाओ(काष्ठा spi_device *spi)
अणु
	काष्ठा nfcmrvl_spi_drv_data *drv_data = spi_get_drvdata(spi);

	nfcmrvl_nci_unरेजिस्टर_dev(drv_data->priv);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id of_nfcmrvl_spi_match[] = अणु
	अणु .compatible = "marvell,nfc-spi", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, of_nfcmrvl_spi_match);

अटल स्थिर काष्ठा spi_device_id nfcmrvl_spi_id_table[] = अणु
	अणु "nfcmrvl_spi", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(spi, nfcmrvl_spi_id_table);

अटल काष्ठा spi_driver nfcmrvl_spi_driver = अणु
	.probe		= nfcmrvl_spi_probe,
	.हटाओ		= nfcmrvl_spi_हटाओ,
	.id_table	= nfcmrvl_spi_id_table,
	.driver		= अणु
		.name		= "nfcmrvl_spi",
		.owner		= THIS_MODULE,
		.of_match_table	= of_match_ptr(of_nfcmrvl_spi_match),
	पूर्ण,
पूर्ण;

module_spi_driver(nfcmrvl_spi_driver);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell NFC-over-SPI driver");
MODULE_LICENSE("GPL v2");
