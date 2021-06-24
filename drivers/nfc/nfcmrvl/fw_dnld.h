<शैली गुरु>
/*
 * Marvell NFC driver: Firmware करोwnloader
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

#अगर_अघोषित __NFCMRVL_FW_DNLD_H__
#घोषणा __NFCMRVL_FW_DNLD_H__

#समावेश <linux/workqueue.h>

#घोषणा NFCMRVL_FW_MAGIC		0x88888888

#घोषणा NCI_OP_PROP_BOOT_CMD		0x3A

#घोषणा NCI_CORE_LC_PROP_FW_DL		0xFD
#घोषणा NCI_CORE_LC_CONNID_PROP_FW_DL	0x02

#घोषणा HELPER_CMD_ENTRY_POINT		0x04
#घोषणा HELPER_CMD_PACKET_FORMAT	0xA5
#घोषणा HELPER_ACK_PACKET_FORMAT	0x5A
#घोषणा HELPER_RETRY_REQUESTED		(1 << 15)

काष्ठा nfcmrvl_निजी;

काष्ठा nfcmrvl_fw_uart_config अणु
	uपूर्णांक8_t flow_control;
	uपूर्णांक32_t baudrate;
पूर्ण __packed;

काष्ठा nfcmrvl_fw_i2c_config अणु
	uपूर्णांक32_t clk;
पूर्ण __packed;

काष्ठा nfcmrvl_fw_spi_config अणु
	uपूर्णांक32_t clk;
पूर्ण __packed;

काष्ठा nfcmrvl_fw_binary_config अणु
	uपूर्णांक32_t offset;
	जोड़ अणु
		व्योम *config;
		काष्ठा nfcmrvl_fw_uart_config uart;
		काष्ठा nfcmrvl_fw_i2c_config i2c;
		काष्ठा nfcmrvl_fw_spi_config spi;
		uपूर्णांक8_t reserved[64];
	पूर्ण;
पूर्ण __packed;

काष्ठा nfcmrvl_fw अणु
	uपूर्णांक32_t magic;
	uपूर्णांक32_t ref_घड़ी;
	uपूर्णांक32_t phy;
	काष्ठा nfcmrvl_fw_binary_config bootrom;
	काष्ठा nfcmrvl_fw_binary_config helper;
	काष्ठा nfcmrvl_fw_binary_config firmware;
	uपूर्णांक8_t reserved[64];
पूर्ण __packed;

काष्ठा nfcmrvl_fw_dnld अणु
	अक्षर name[NFC_FIRMWARE_NAME_MAXSIZE + 1];
	स्थिर काष्ठा firmware *fw;

	स्थिर काष्ठा nfcmrvl_fw *header;
	स्थिर काष्ठा nfcmrvl_fw_binary_config *binary_config;

	पूर्णांक state;
	पूर्णांक substate;
	पूर्णांक offset;
	पूर्णांक chunk_len;

	काष्ठा workqueue_काष्ठा	*rx_wq;
	काष्ठा work_काष्ठा rx_work;
	काष्ठा sk_buff_head rx_q;

	काष्ठा समयr_list समयr;
पूर्ण;

पूर्णांक nfcmrvl_fw_dnld_init(काष्ठा nfcmrvl_निजी *priv);
व्योम nfcmrvl_fw_dnld_deinit(काष्ठा nfcmrvl_निजी *priv);
व्योम nfcmrvl_fw_dnld_पात(काष्ठा nfcmrvl_निजी *priv);
पूर्णांक nfcmrvl_fw_dnld_start(काष्ठा nci_dev *ndev, स्थिर अक्षर *firmware_name);
व्योम nfcmrvl_fw_dnld_recv_frame(काष्ठा nfcmrvl_निजी *priv,
				काष्ठा sk_buff *skb);

#पूर्ण_अगर
