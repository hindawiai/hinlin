<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित ISCSI_TARGET_STAT_H
#घोषणा ISCSI_TARGET_STAT_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/socket.h>

/*
 * For काष्ठा iscsi_tiqn->tiqn_wwn शेष groups
 */
बाह्य स्थिर काष्ठा config_item_type iscsi_stat_instance_cit;
बाह्य स्थिर काष्ठा config_item_type iscsi_stat_sess_err_cit;
बाह्य स्थिर काष्ठा config_item_type iscsi_stat_tgt_attr_cit;
बाह्य स्थिर काष्ठा config_item_type iscsi_stat_login_cit;
बाह्य स्थिर काष्ठा config_item_type iscsi_stat_logout_cit;

/*
 * For काष्ठा iscsi_session->se_sess शेष groups
 */
बाह्य स्थिर काष्ठा config_item_type iscsi_stat_sess_cit;

/* iSCSI session error types */
#घोषणा ISCSI_SESS_ERR_UNKNOWN		0
#घोषणा ISCSI_SESS_ERR_DIGEST		1
#घोषणा ISCSI_SESS_ERR_CXN_TIMEOUT	2
#घोषणा ISCSI_SESS_ERR_PDU_FORMAT	3

/* iSCSI session error stats */
काष्ठा iscsi_sess_err_stats अणु
	spinlock_t	lock;
	u32		digest_errors;
	u32		cxn_समयout_errors;
	u32		pdu_क्रमmat_errors;
	u32		last_sess_failure_type;
	अक्षर		last_sess_fail_rem_name[ISCSI_IQN_LEN];
पूर्ण ____cacheline_aligned;

/* iSCSI login failure types (sub oids) */
#घोषणा ISCSI_LOGIN_FAIL_OTHER		2
#घोषणा ISCSI_LOGIN_FAIL_REसूचीECT	3
#घोषणा ISCSI_LOGIN_FAIL_AUTHORIZE	4
#घोषणा ISCSI_LOGIN_FAIL_AUTHENTICATE	5
#घोषणा ISCSI_LOGIN_FAIL_NEGOTIATE	6

/* iSCSI login stats */
काष्ठा iscsi_login_stats अणु
	spinlock_t	lock;
	u32		accepts;
	u32		other_fails;
	u32		redirects;
	u32		authorize_fails;
	u32		authenticate_fails;
	u32		negotiate_fails;	/* used क्रम notअगरications */
	u64		last_fail_समय;		/* समय stamp (jअगरfies) */
	u32		last_fail_type;
	पूर्णांक		last_पूर्णांकr_fail_ip_family;
	काष्ठा sockaddr_storage last_पूर्णांकr_fail_sockaddr;
	अक्षर		last_पूर्णांकr_fail_name[ISCSI_IQN_LEN];
पूर्ण ____cacheline_aligned;

/* iSCSI logout stats */
काष्ठा iscsi_logout_stats अणु
	spinlock_t	lock;
	u32		normal_logouts;
	u32		abnormal_logouts;
पूर्ण ____cacheline_aligned;

#पूर्ण_अगर   /*** ISCSI_TARGET_STAT_H ***/
