<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

/* Copyright (c) 2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2020 Linaro Ltd.
 */
#अगर_अघोषित _IPA_QMI_H_
#घोषणा _IPA_QMI_H_

#समावेश <linux/types.h>
#समावेश <linux/soc/qcom/qmi.h>

काष्ठा ipa;

/**
 * काष्ठा ipa_qmi - QMI state associated with an IPA
 * @client_handle:	Used to send an QMI requests to the modem
 * @server_handle:	Used to handle QMI requests from the modem
 * @modem_sq:		QMAP socket address क्रम the modem QMI server
 * @init_driver_work:	Work काष्ठाure used क्रम INIT_DRIVER message handling
 * @initial_boot:	True अगर first boot has not yet completed
 * @uc_पढ़ोy:		True once DRIVER_INIT_COMPLETE request received
 * @modem_पढ़ोy:	True when INIT_DRIVER response received
 * @indication_requested: True when INDICATION_REGISTER request received
 * @indication_sent:	True when INIT_COMPLETE indication sent
 */
काष्ठा ipa_qmi अणु
	काष्ठा qmi_handle client_handle;
	काष्ठा qmi_handle server_handle;

	/* Inक्रमmation used क्रम the client handle */
	काष्ठा sockaddr_qrtr modem_sq;
	काष्ठा work_काष्ठा init_driver_work;

	/* Flags used in negotiating पढ़ोiness */
	bool initial_boot;
	bool uc_पढ़ोy;
	bool modem_पढ़ोy;
	bool indication_requested;
	bool indication_sent;
पूर्ण;

पूर्णांक ipa_qmi_setup(काष्ठा ipa *ipa);
व्योम ipa_qmi_tearकरोwn(काष्ठा ipa *ipa);

#पूर्ण_अगर /* !_IPA_QMI_H_ */
