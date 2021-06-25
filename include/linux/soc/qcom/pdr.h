<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __QCOM_PDR_HELPER__
#घोषणा __QCOM_PDR_HELPER__

#समावेश <linux/soc/qcom/qmi.h>

#घोषणा SERVREG_NAME_LENGTH	64

काष्ठा pdr_service;
काष्ठा pdr_handle;

क्रमागत servreg_service_state अणु
	SERVREG_LOCATOR_ERR = 0x1,
	SERVREG_SERVICE_STATE_DOWN = 0x0FFFFFFF,
	SERVREG_SERVICE_STATE_UP = 0x1FFFFFFF,
	SERVREG_SERVICE_STATE_EARLY_DOWN = 0x2FFFFFFF,
	SERVREG_SERVICE_STATE_UNINIT = 0x7FFFFFFF,
पूर्ण;

काष्ठा pdr_handle *pdr_handle_alloc(व्योम (*status)(पूर्णांक state,
						   अक्षर *service_path,
						   व्योम *priv), व्योम *priv);
काष्ठा pdr_service *pdr_add_lookup(काष्ठा pdr_handle *pdr,
				   स्थिर अक्षर *service_name,
				   स्थिर अक्षर *service_path);
पूर्णांक pdr_restart_pd(काष्ठा pdr_handle *pdr, काष्ठा pdr_service *pds);
व्योम pdr_handle_release(काष्ठा pdr_handle *pdr);

#पूर्ण_अगर
