<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _NFSD4_CURRENT_STATE_H
#घोषणा _NFSD4_CURRENT_STATE_H

#समावेश "state.h"
#समावेश "xdr4.h"

बाह्य व्योम clear_current_stateid(काष्ठा nfsd4_compound_state *cstate);
/*
 * functions to set current state id
 */
बाह्य व्योम nfsd4_set_खोलोकरोwngradestateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_set_खोलोstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_set_lockstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_set_बंदstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);

/*
 * functions to consume current state id
 */
बाह्य व्योम nfsd4_get_खोलोकरोwngradestateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_delegवापसstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_मुक्तstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_setattrstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_बंदstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_lockustateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_पढ़ोstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);
बाह्य व्योम nfsd4_get_ग_लिखोstateid(काष्ठा nfsd4_compound_state *,
		जोड़ nfsd4_op_u *);

#पूर्ण_अगर   /* _NFSD4_CURRENT_STATE_H */
