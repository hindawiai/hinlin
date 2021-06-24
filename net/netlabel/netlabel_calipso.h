<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NetLabel CALIPSO Support
 *
 * This file defines the CALIPSO functions क्रम the NetLabel प्रणाली.  The
 * NetLabel प्रणाली manages अटल and dynamic label mappings क्रम network
 * protocols such as CIPSO and RIPSO.
 *
 * Authors: Paul Moore <paul@paul-moore.com>
 *          Huw Davies <huw@codeweavers.com>
 */

/* (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 * (c) Copyright Huw Davies <huw@codeweavers.com>, 2015
 */

#अगर_अघोषित _NETLABEL_CALIPSO
#घोषणा _NETLABEL_CALIPSO

#समावेश <net/netlabel.h>
#समावेश <net/calipso.h>

/* The following NetLabel payloads are supported by the CALIPSO subप्रणाली.
 *
 * o ADD:
 *   Sent by an application to add a new DOI mapping table.
 *
 *   Required attributes:
 *
 *     NLBL_CALIPSO_A_DOI
 *     NLBL_CALIPSO_A_MTYPE
 *
 *   If using CALIPSO_MAP_PASS no additional attributes are required.
 *
 * o REMOVE:
 *   Sent by an application to हटाओ a specअगरic DOI mapping table from the
 *   CALIPSO प्रणाली.
 *
 *   Required attributes:
 *
 *     NLBL_CALIPSO_A_DOI
 *
 * o LIST:
 *   Sent by an application to list the details of a DOI definition.  On
 *   success the kernel should send a response using the following क्रमmat.
 *
 *   Required attributes:
 *
 *     NLBL_CALIPSO_A_DOI
 *
 *   The valid response message क्रमmat depends on the type of the DOI mapping,
 *   the defined क्रमmats are shown below.
 *
 *   Required attributes:
 *
 *     NLBL_CALIPSO_A_MTYPE
 *
 *   If using CALIPSO_MAP_PASS no additional attributes are required.
 *
 * o LISTALL:
 *   This message is sent by an application to list the valid DOIs on the
 *   प्रणाली.  When sent by an application there is no payload and the
 *   NLM_F_DUMP flag should be set.  The kernel should respond with a series of
 *   the following messages.
 *
 *   Required attributes:
 *
 *    NLBL_CALIPSO_A_DOI
 *    NLBL_CALIPSO_A_MTYPE
 *
 */

/* NetLabel CALIPSO commands */
क्रमागत अणु
	NLBL_CALIPSO_C_UNSPEC,
	NLBL_CALIPSO_C_ADD,
	NLBL_CALIPSO_C_REMOVE,
	NLBL_CALIPSO_C_LIST,
	NLBL_CALIPSO_C_LISTALL,
	__NLBL_CALIPSO_C_MAX,
पूर्ण;

/* NetLabel CALIPSO attributes */
क्रमागत अणु
	NLBL_CALIPSO_A_UNSPEC,
	NLBL_CALIPSO_A_DOI,
	/* (NLA_U32)
	 * the DOI value */
	NLBL_CALIPSO_A_MTYPE,
	/* (NLA_U32)
	 * the mapping table type (defined in the calipso.h header as
	 * CALIPSO_MAP_*) */
	__NLBL_CALIPSO_A_MAX,
पूर्ण;

#घोषणा NLBL_CALIPSO_A_MAX (__NLBL_CALIPSO_A_MAX - 1)

/* NetLabel protocol functions */
#अगर IS_ENABLED(CONFIG_IPV6)
पूर्णांक netlbl_calipso_genl_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक netlbl_calipso_genl_init(व्योम)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक calipso_करोi_add(काष्ठा calipso_करोi *करोi_def,
		    काष्ठा netlbl_audit *audit_info);
व्योम calipso_करोi_मुक्त(काष्ठा calipso_करोi *करोi_def);
पूर्णांक calipso_करोi_हटाओ(u32 करोi, काष्ठा netlbl_audit *audit_info);
काष्ठा calipso_करोi *calipso_करोi_getdef(u32 करोi);
व्योम calipso_करोi_putdef(काष्ठा calipso_करोi *करोi_def);
पूर्णांक calipso_करोi_walk(u32 *skip_cnt,
		     पूर्णांक (*callback)(काष्ठा calipso_करोi *करोi_def, व्योम *arg),
		     व्योम *cb_arg);
पूर्णांक calipso_sock_getattr(काष्ठा sock *sk, काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक calipso_sock_setattr(काष्ठा sock *sk,
			 स्थिर काष्ठा calipso_करोi *करोi_def,
			 स्थिर काष्ठा netlbl_lsm_secattr *secattr);
व्योम calipso_sock_delattr(काष्ठा sock *sk);
पूर्णांक calipso_req_setattr(काष्ठा request_sock *req,
			स्थिर काष्ठा calipso_करोi *करोi_def,
			स्थिर काष्ठा netlbl_lsm_secattr *secattr);
व्योम calipso_req_delattr(काष्ठा request_sock *req);
अचिन्हित अक्षर *calipso_optptr(स्थिर काष्ठा sk_buff *skb);
पूर्णांक calipso_getattr(स्थिर अचिन्हित अक्षर *calipso,
		    काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक calipso_skbuff_setattr(काष्ठा sk_buff *skb,
			   स्थिर काष्ठा calipso_करोi *करोi_def,
			   स्थिर काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक calipso_skbuff_delattr(काष्ठा sk_buff *skb);
व्योम calipso_cache_invalidate(व्योम);
पूर्णांक calipso_cache_add(स्थिर अचिन्हित अक्षर *calipso_ptr,
		      स्थिर काष्ठा netlbl_lsm_secattr *secattr);

#पूर्ण_अगर
