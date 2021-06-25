<शैली गुरु>
/*
 * Marvell NFC driver
 *
 * Copyright (C) 2014-2015, Marvell International Ltd.
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

#अगर_अघोषित _NFCMRVL_H_
#घोषणा _NFCMRVL_H_

#समावेश <linux/platक्रमm_data/nfcmrvl.h>

#समावेश "fw_dnld.h"

/* Define निजी flags: */
#घोषणा NFCMRVL_NCI_RUNNING			1
#घोषणा NFCMRVL_PHY_ERROR			2

#घोषणा NFCMRVL_EXT_COEX_ID			0xE0
#घोषणा NFCMRVL_NOT_ALLOWED_ID			0xE1
#घोषणा NFCMRVL_ACTIVE_ID			0xE2
#घोषणा NFCMRVL_EXT_COEX_ENABLE			1
#घोषणा NFCMRVL_GPIO_PIN_NFC_NOT_ALLOWED	0xA
#घोषणा NFCMRVL_GPIO_PIN_NFC_ACTIVE		0xB
#घोषणा NFCMRVL_NCI_MAX_EVENT_SIZE		260

/*
** NCI FW Parmaters
*/

#घोषणा NFCMRVL_PB_BAIL_OUT			0x11
#घोषणा NFCMRVL_PROP_REF_CLOCK			0xF0
#घोषणा NFCMRVL_PROP_SET_HI_CONFIG		0xF1

/*
** HCI defines
*/

#घोषणा NFCMRVL_HCI_EVENT_HEADER_SIZE		0x04
#घोषणा NFCMRVL_HCI_EVENT_CODE			0x04
#घोषणा NFCMRVL_HCI_NFC_EVENT_CODE		0xFF
#घोषणा NFCMRVL_HCI_COMMAND_CODE		0x01
#घोषणा NFCMRVL_HCI_OGF				0x81
#घोषणा NFCMRVL_HCI_OCF				0xFE

क्रमागत nfcmrvl_phy अणु
	NFCMRVL_PHY_USB		= 0,
	NFCMRVL_PHY_UART	= 1,
	NFCMRVL_PHY_I2C		= 2,
	NFCMRVL_PHY_SPI		= 3,
पूर्ण;

काष्ठा nfcmrvl_निजी अणु

	अचिन्हित दीर्घ flags;

	/* Platक्रमm configuration */
	काष्ठा nfcmrvl_platक्रमm_data config;

	/* Parent dev */
	काष्ठा nci_dev *ndev;

	/* FW करोwnload context */
	काष्ठा nfcmrvl_fw_dnld fw_dnld;

	/* FW करोwnload support */
	bool support_fw_dnld;

	/*
	** PHY related inक्रमmation
	*/

	/* PHY driver context */
	व्योम *drv_data;
	/* PHY device */
	काष्ठा device *dev;
	/* PHY type */
	क्रमागत nfcmrvl_phy phy;
	/* Low level driver ops */
	काष्ठा nfcmrvl_अगर_ops *अगर_ops;
पूर्ण;

काष्ठा nfcmrvl_अगर_ops अणु
	पूर्णांक (*nci_खोलो) (काष्ठा nfcmrvl_निजी *priv);
	पूर्णांक (*nci_बंद) (काष्ठा nfcmrvl_निजी *priv);
	पूर्णांक (*nci_send) (काष्ठा nfcmrvl_निजी *priv, काष्ठा sk_buff *skb);
	व्योम (*nci_update_config)(काष्ठा nfcmrvl_निजी *priv,
				  स्थिर व्योम *param);
पूर्ण;

व्योम nfcmrvl_nci_unरेजिस्टर_dev(काष्ठा nfcmrvl_निजी *priv);
पूर्णांक nfcmrvl_nci_recv_frame(काष्ठा nfcmrvl_निजी *priv, काष्ठा sk_buff *skb);
काष्ठा nfcmrvl_निजी *nfcmrvl_nci_रेजिस्टर_dev(क्रमागत nfcmrvl_phy phy,
				व्योम *drv_data,
				काष्ठा nfcmrvl_अगर_ops *ops,
				काष्ठा device *dev,
				काष्ठा nfcmrvl_platक्रमm_data *pdata);


व्योम nfcmrvl_chip_reset(काष्ठा nfcmrvl_निजी *priv);
व्योम nfcmrvl_chip_halt(काष्ठा nfcmrvl_निजी *priv);

पूर्णांक nfcmrvl_parse_dt(काष्ठा device_node *node,
		     काष्ठा nfcmrvl_platक्रमm_data *pdata);

#पूर्ण_अगर
