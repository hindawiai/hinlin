<शैली गुरु>
/*
 * Marvell NFC-over-UART driver
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
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_gpपन.स>
#समावेश <net/nfc/nci.h>
#समावेश <net/nfc/nci_core.h>
#समावेश "nfcmrvl.h"

अटल अचिन्हित पूर्णांक hci_muxed;
अटल अचिन्हित पूर्णांक flow_control;
अटल अचिन्हित पूर्णांक अवरोध_control;
अटल पूर्णांक reset_n_io = -EINVAL;

/*
** NFCMRVL NCI OPS
*/

अटल पूर्णांक nfcmrvl_uart_nci_खोलो(काष्ठा nfcmrvl_निजी *priv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_uart_nci_बंद(काष्ठा nfcmrvl_निजी *priv)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक nfcmrvl_uart_nci_send(काष्ठा nfcmrvl_निजी *priv,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा nci_uart *nu = priv->drv_data;

	वापस nu->ops.send(nu, skb);
पूर्ण

अटल व्योम nfcmrvl_uart_nci_update_config(काष्ठा nfcmrvl_निजी *priv,
					   स्थिर व्योम *param)
अणु
	काष्ठा nci_uart *nu = priv->drv_data;
	स्थिर काष्ठा nfcmrvl_fw_uart_config *config = param;

	nci_uart_set_config(nu, le32_to_cpu(config->baudrate),
			    config->flow_control);
पूर्ण

अटल काष्ठा nfcmrvl_अगर_ops uart_ops = अणु
	.nci_खोलो = nfcmrvl_uart_nci_खोलो,
	.nci_बंद = nfcmrvl_uart_nci_बंद,
	.nci_send = nfcmrvl_uart_nci_send,
	.nci_update_config = nfcmrvl_uart_nci_update_config
पूर्ण;

अटल पूर्णांक nfcmrvl_uart_parse_dt(काष्ठा device_node *node,
				 काष्ठा nfcmrvl_platक्रमm_data *pdata)
अणु
	काष्ठा device_node *matched_node;
	पूर्णांक ret;

	matched_node = of_get_compatible_child(node, "marvell,nfc-uart");
	अगर (!matched_node) अणु
		matched_node = of_get_compatible_child(node, "mrvl,nfc-uart");
		अगर (!matched_node)
			वापस -ENODEV;
	पूर्ण

	ret = nfcmrvl_parse_dt(matched_node, pdata);
	अगर (ret < 0) अणु
		pr_err("Failed to get generic entries\n");
		of_node_put(matched_node);
		वापस ret;
	पूर्ण

	अगर (of_find_property(matched_node, "flow-control", शून्य))
		pdata->flow_control = 1;
	अन्यथा
		pdata->flow_control = 0;

	अगर (of_find_property(matched_node, "break-control", शून्य))
		pdata->अवरोध_control = 1;
	अन्यथा
		pdata->अवरोध_control = 0;

	of_node_put(matched_node);

	वापस 0;
पूर्ण

/*
** NCI UART OPS
*/

अटल पूर्णांक nfcmrvl_nci_uart_खोलो(काष्ठा nci_uart *nu)
अणु
	काष्ठा nfcmrvl_निजी *priv;
	काष्ठा nfcmrvl_platक्रमm_data *pdata = शून्य;
	काष्ठा nfcmrvl_platक्रमm_data config;
	काष्ठा device *dev = nu->tty->dev;

	/*
	 * Platक्रमm data cannot be used here since usually it is alपढ़ोy used
	 * by low level serial driver. We can try to retrieve serial device
	 * and check अगर DT entries were added.
	 */

	अगर (dev && dev->parent && dev->parent->of_node)
		अगर (nfcmrvl_uart_parse_dt(dev->parent->of_node, &config) == 0)
			pdata = &config;

	अगर (!pdata) अणु
		pr_info("No platform data / DT -> fallback to module params\n");
		config.hci_muxed = hci_muxed;
		config.reset_n_io = reset_n_io;
		config.flow_control = flow_control;
		config.अवरोध_control = अवरोध_control;
		pdata = &config;
	पूर्ण

	priv = nfcmrvl_nci_रेजिस्टर_dev(NFCMRVL_PHY_UART, nu, &uart_ops,
					dev, pdata);
	अगर (IS_ERR(priv))
		वापस PTR_ERR(priv);

	priv->support_fw_dnld = true;

	nu->drv_data = priv;
	nu->ndev = priv->ndev;

	वापस 0;
पूर्ण

अटल व्योम nfcmrvl_nci_uart_बंद(काष्ठा nci_uart *nu)
अणु
	nfcmrvl_nci_unरेजिस्टर_dev((काष्ठा nfcmrvl_निजी *)nu->drv_data);
पूर्ण

अटल पूर्णांक nfcmrvl_nci_uart_recv(काष्ठा nci_uart *nu, काष्ठा sk_buff *skb)
अणु
	वापस nfcmrvl_nci_recv_frame((काष्ठा nfcmrvl_निजी *)nu->drv_data,
				      skb);
पूर्ण

अटल व्योम nfcmrvl_nci_uart_tx_start(काष्ठा nci_uart *nu)
अणु
	काष्ठा nfcmrvl_निजी *priv = (काष्ठा nfcmrvl_निजी *)nu->drv_data;

	अगर (priv->ndev->nfc_dev->fw_करोwnload_in_progress)
		वापस;

	/* Remove BREAK to wake up the NFCC */
	अगर (priv->config.अवरोध_control && nu->tty->ops->अवरोध_ctl) अणु
		nu->tty->ops->अवरोध_ctl(nu->tty, 0);
		usleep_range(3000, 5000);
	पूर्ण
पूर्ण

अटल व्योम nfcmrvl_nci_uart_tx_करोne(काष्ठा nci_uart *nu)
अणु
	काष्ठा nfcmrvl_निजी *priv = (काष्ठा nfcmrvl_निजी *)nu->drv_data;

	अगर (priv->ndev->nfc_dev->fw_करोwnload_in_progress)
		वापस;

	/*
	** To ensure that अगर the NFCC goes in DEEP SLEEP sate we can wake him
	** up. we set BREAK. Once we will be पढ़ोy to send again we will हटाओ
	** it.
	*/
	अगर (priv->config.अवरोध_control && nu->tty->ops->अवरोध_ctl) अणु
		nu->tty->ops->अवरोध_ctl(nu->tty, -1);
		usleep_range(1000, 3000);
	पूर्ण
पूर्ण

अटल काष्ठा nci_uart nfcmrvl_nci_uart = अणु
	.owner  = THIS_MODULE,
	.name   = "nfcmrvl_uart",
	.driver = NCI_UART_DRIVER_MARVELL,
	.ops	= अणु
		.खोलो		= nfcmrvl_nci_uart_खोलो,
		.बंद		= nfcmrvl_nci_uart_बंद,
		.recv		= nfcmrvl_nci_uart_recv,
		.tx_start	= nfcmrvl_nci_uart_tx_start,
		.tx_करोne	= nfcmrvl_nci_uart_tx_करोne,
	पूर्ण
पूर्ण;

/*
** Module init
*/

अटल पूर्णांक nfcmrvl_uart_init_module(व्योम)
अणु
	वापस nci_uart_रेजिस्टर(&nfcmrvl_nci_uart);
पूर्ण

अटल व्योम nfcmrvl_uart_निकास_module(व्योम)
अणु
	nci_uart_unरेजिस्टर(&nfcmrvl_nci_uart);
पूर्ण

module_init(nfcmrvl_uart_init_module);
module_निकास(nfcmrvl_uart_निकास_module);

MODULE_AUTHOR("Marvell International Ltd.");
MODULE_DESCRIPTION("Marvell NFC-over-UART");
MODULE_LICENSE("GPL v2");

module_param(flow_control, uपूर्णांक, 0);
MODULE_PARM_DESC(flow_control, "Tell if UART needs flow control at init.");

module_param(अवरोध_control, uपूर्णांक, 0);
MODULE_PARM_DESC(अवरोध_control, "Tell if UART driver must drive break signal.");

module_param(hci_muxed, uपूर्णांक, 0);
MODULE_PARM_DESC(hci_muxed, "Tell if transport is muxed in HCI one.");

module_param(reset_n_io, पूर्णांक, 0);
MODULE_PARM_DESC(reset_n_io, "GPIO that is wired to RESET_N signal.");
