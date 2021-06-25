<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright (C) 2003 Aurelien Alleaume <slts@मुक्त.fr>
 */

#अगर !defined(_OID_MGT_H)
#घोषणा _OID_MGT_H

#समावेश "isl_oid.h"
#समावेश "islpci_dev.h"

बाह्य काष्ठा oid_t isl_oid[];

पूर्णांक mgt_init(islpci_निजी *);

व्योम mgt_clean(islpci_निजी *);

/* I करोn't know where to put these 2 */
बाह्य स्थिर पूर्णांक frequency_list_a[];
पूर्णांक channel_of_freq(पूर्णांक);

व्योम mgt_le_to_cpu(पूर्णांक, व्योम *);

पूर्णांक mgt_set_request(islpci_निजी *, क्रमागत oid_num_t, पूर्णांक, व्योम *);
पूर्णांक mgt_set_varlen(islpci_निजी *, क्रमागत oid_num_t, व्योम *, पूर्णांक);


पूर्णांक mgt_get_request(islpci_निजी *, क्रमागत oid_num_t, पूर्णांक, व्योम *,
		    जोड़ oid_res_t *);

पूर्णांक mgt_commit_list(islpci_निजी *, क्रमागत oid_num_t *, पूर्णांक);

व्योम mgt_set(islpci_निजी *, क्रमागत oid_num_t, व्योम *);

व्योम mgt_get(islpci_निजी *, क्रमागत oid_num_t, व्योम *);

पूर्णांक mgt_commit(islpci_निजी *);

पूर्णांक mgt_mlme_answer(islpci_निजी *);

क्रमागत oid_num_t mgt_oidtonum(u32 oid);

पूर्णांक mgt_response_to_str(क्रमागत oid_num_t, जोड़ oid_res_t *, अक्षर *);

#पूर्ण_अगर				/* !defined(_OID_MGT_H) */
/* खातापूर्ण */
