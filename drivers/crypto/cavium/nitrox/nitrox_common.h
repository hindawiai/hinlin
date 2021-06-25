<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __NITROX_COMMON_H
#घोषणा __NITROX_COMMON_H

#समावेश "nitrox_dev.h"
#समावेश "nitrox_req.h"

पूर्णांक nitrox_crypto_रेजिस्टर(व्योम);
व्योम nitrox_crypto_unरेजिस्टर(व्योम);
पूर्णांक nitrox_रेजिस्टर_aeads(व्योम);
व्योम nitrox_unरेजिस्टर_aeads(व्योम);
पूर्णांक nitrox_रेजिस्टर_skciphers(व्योम);
व्योम nitrox_unरेजिस्टर_skciphers(व्योम);
व्योम *crypto_alloc_context(काष्ठा nitrox_device *ndev);
व्योम crypto_मुक्त_context(व्योम *ctx);
काष्ठा nitrox_device *nitrox_get_first_device(व्योम);
व्योम nitrox_put_device(काष्ठा nitrox_device *ndev);

पूर्णांक nitrox_common_sw_init(काष्ठा nitrox_device *ndev);
व्योम nitrox_common_sw_cleanup(काष्ठा nitrox_device *ndev);

व्योम pkt_slc_resp_tasklet(अचिन्हित दीर्घ data);
पूर्णांक nitrox_process_se_request(काष्ठा nitrox_device *ndev,
			      काष्ठा se_crypto_request *req,
			      completion_t cb,
			      व्योम *cb_arg);
व्योम backlog_qflush_work(काष्ठा work_काष्ठा *work);


#पूर्ण_अगर /* __NITROX_COMMON_H */
