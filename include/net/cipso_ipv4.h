<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CIPSO - Commercial IP Security Option
 *
 * This is an implementation of the CIPSO 2.2 protocol as specअगरied in
 * draft-ietf-cipso-ipsecurity-01.txt with additional tag types as found in
 * FIPS-188, copies of both करोcuments can be found in the Documentation
 * directory.  While CIPSO never became a full IETF RFC standard many venकरोrs
 * have chosen to aकरोpt the protocol and over the years it has become a
 * de-facto standard क्रम labeled networking.
 *
 * Author: Paul Moore <paul@paul-moore.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 */

#अगर_अघोषित _CIPSO_IPV4_H
#घोषणा _CIPSO_IPV4_H

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netlabel.h>
#समावेश <net/request_sock.h>
#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <यंत्र/unaligned.h>

/* known करोi values */
#घोषणा CIPSO_V4_DOI_UNKNOWN          0x00000000

/* standard tag types */
#घोषणा CIPSO_V4_TAG_INVALID          0
#घोषणा CIPSO_V4_TAG_RBITMAP          1
#घोषणा CIPSO_V4_TAG_ENUM             2
#घोषणा CIPSO_V4_TAG_RANGE            5
#घोषणा CIPSO_V4_TAG_PBITMAP          6
#घोषणा CIPSO_V4_TAG_FREEFORM         7

/* non-standard tag types (tags > 127) */
#घोषणा CIPSO_V4_TAG_LOCAL            128

/* करोi mapping types */
#घोषणा CIPSO_V4_MAP_UNKNOWN          0
#घोषणा CIPSO_V4_MAP_TRANS            1
#घोषणा CIPSO_V4_MAP_PASS             2
#घोषणा CIPSO_V4_MAP_LOCAL            3

/* limits */
#घोषणा CIPSO_V4_MAX_REM_LVLS         255
#घोषणा CIPSO_V4_INV_LVL              0x80000000
#घोषणा CIPSO_V4_MAX_LOC_LVLS         (CIPSO_V4_INV_LVL - 1)
#घोषणा CIPSO_V4_MAX_REM_CATS         65534
#घोषणा CIPSO_V4_INV_CAT              0x80000000
#घोषणा CIPSO_V4_MAX_LOC_CATS         (CIPSO_V4_INV_CAT - 1)

/*
 * CIPSO DOI definitions
 */

/* DOI definition काष्ठा */
#घोषणा CIPSO_V4_TAG_MAXCNT           5
काष्ठा cipso_v4_करोi अणु
	u32 करोi;
	u32 type;
	जोड़ अणु
		काष्ठा cipso_v4_std_map_tbl *std;
	पूर्ण map;
	u8 tags[CIPSO_V4_TAG_MAXCNT];

	refcount_t refcount;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/* Standard CIPSO mapping table */
/* NOTE: the highest order bit (i.e. 0x80000000) is an 'invalid' flag, अगर the
 *       bit is set then consider that value as unspecअगरied, meaning the
 *       mapping क्रम that particular level/category is invalid */
काष्ठा cipso_v4_std_map_tbl अणु
	काष्ठा अणु
		u32 *cipso;
		u32 *local;
		u32 cipso_size;
		u32 local_size;
	पूर्ण lvl;
	काष्ठा अणु
		u32 *cipso;
		u32 *local;
		u32 cipso_size;
		u32 local_size;
	पूर्ण cat;
पूर्ण;

/*
 * Sysctl Variables
 */

#अगर_घोषित CONFIG_NETLABEL
बाह्य पूर्णांक cipso_v4_cache_enabled;
बाह्य पूर्णांक cipso_v4_cache_bucketsize;
बाह्य पूर्णांक cipso_v4_rbm_optfmt;
बाह्य पूर्णांक cipso_v4_rbm_strictvalid;
#पूर्ण_अगर

/*
 * DOI List Functions
 */

#अगर_घोषित CONFIG_NETLABEL
पूर्णांक cipso_v4_करोi_add(काष्ठा cipso_v4_करोi *करोi_def,
		     काष्ठा netlbl_audit *audit_info);
व्योम cipso_v4_करोi_मुक्त(काष्ठा cipso_v4_करोi *करोi_def);
पूर्णांक cipso_v4_करोi_हटाओ(u32 करोi, काष्ठा netlbl_audit *audit_info);
काष्ठा cipso_v4_करोi *cipso_v4_करोi_getdef(u32 करोi);
व्योम cipso_v4_करोi_putdef(काष्ठा cipso_v4_करोi *करोi_def);
पूर्णांक cipso_v4_करोi_walk(u32 *skip_cnt,
		     पूर्णांक (*callback) (काष्ठा cipso_v4_करोi *करोi_def, व्योम *arg),
	             व्योम *cb_arg);
#अन्यथा
अटल अंतरभूत पूर्णांक cipso_v4_करोi_add(काष्ठा cipso_v4_करोi *करोi_def,
				   काष्ठा netlbl_audit *audit_info)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम cipso_v4_करोi_मुक्त(काष्ठा cipso_v4_करोi *करोi_def)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_करोi_हटाओ(u32 करोi,
				      काष्ठा netlbl_audit *audit_info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत काष्ठा cipso_v4_करोi *cipso_v4_करोi_getdef(u32 करोi)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_करोi_walk(u32 *skip_cnt,
		     पूर्णांक (*callback) (काष्ठा cipso_v4_करोi *करोi_def, व्योम *arg),
		     व्योम *cb_arg)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

/*
 * Label Mapping Cache Functions
 */

#अगर_घोषित CONFIG_NETLABEL
व्योम cipso_v4_cache_invalidate(व्योम);
पूर्णांक cipso_v4_cache_add(स्थिर अचिन्हित अक्षर *cipso_ptr,
		       स्थिर काष्ठा netlbl_lsm_secattr *secattr);
#अन्यथा
अटल अंतरभूत व्योम cipso_v4_cache_invalidate(व्योम)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_cache_add(स्थिर अचिन्हित अक्षर *cipso_ptr,
				     स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

/*
 * Protocol Handling Functions
 */

#अगर_घोषित CONFIG_NETLABEL
व्योम cipso_v4_error(काष्ठा sk_buff *skb, पूर्णांक error, u32 gateway);
पूर्णांक cipso_v4_getattr(स्थिर अचिन्हित अक्षर *cipso,
		     काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक cipso_v4_sock_setattr(काष्ठा sock *sk,
			  स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			  स्थिर काष्ठा netlbl_lsm_secattr *secattr);
व्योम cipso_v4_sock_delattr(काष्ठा sock *sk);
पूर्णांक cipso_v4_sock_getattr(काष्ठा sock *sk, काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक cipso_v4_req_setattr(काष्ठा request_sock *req,
			 स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			 स्थिर काष्ठा netlbl_lsm_secattr *secattr);
व्योम cipso_v4_req_delattr(काष्ठा request_sock *req);
पूर्णांक cipso_v4_skbuff_setattr(काष्ठा sk_buff *skb,
			    स्थिर काष्ठा cipso_v4_करोi *करोi_def,
			    स्थिर काष्ठा netlbl_lsm_secattr *secattr);
पूर्णांक cipso_v4_skbuff_delattr(काष्ठा sk_buff *skb);
पूर्णांक cipso_v4_skbuff_getattr(स्थिर काष्ठा sk_buff *skb,
			    काष्ठा netlbl_lsm_secattr *secattr);
अचिन्हित अक्षर *cipso_v4_optptr(स्थिर काष्ठा sk_buff *skb);
पूर्णांक cipso_v4_validate(स्थिर काष्ठा sk_buff *skb, अचिन्हित अक्षर **option);
#अन्यथा
अटल अंतरभूत व्योम cipso_v4_error(काष्ठा sk_buff *skb,
				  पूर्णांक error,
				  u32 gateway)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_getattr(स्थिर अचिन्हित अक्षर *cipso,
				   काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_sock_setattr(काष्ठा sock *sk,
				      स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				      स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम cipso_v4_sock_delattr(काष्ठा sock *sk)
अणु
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_sock_getattr(काष्ठा sock *sk,
					काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_req_setattr(काष्ठा request_sock *req,
				       स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				       स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत व्योम cipso_v4_req_delattr(काष्ठा request_sock *req)
अणु
	वापस;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_skbuff_setattr(काष्ठा sk_buff *skb,
				      स्थिर काष्ठा cipso_v4_करोi *करोi_def,
				      स्थिर काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_skbuff_delattr(काष्ठा sk_buff *skb)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_skbuff_getattr(स्थिर काष्ठा sk_buff *skb,
					  काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOSYS;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर *cipso_v4_optptr(स्थिर काष्ठा sk_buff *skb)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक cipso_v4_validate(स्थिर काष्ठा sk_buff *skb,
				    अचिन्हित अक्षर **option)
अणु
	अचिन्हित अक्षर *opt = *option;
	अचिन्हित अक्षर err_offset = 0;
	u8 opt_len = opt[1];
	u8 opt_iter;
	u8 tag_len;

	अगर (opt_len < 8) अणु
		err_offset = 1;
		जाओ out;
	पूर्ण

	अगर (get_unaligned_be32(&opt[2]) == 0) अणु
		err_offset = 2;
		जाओ out;
	पूर्ण

	क्रम (opt_iter = 6; opt_iter < opt_len;) अणु
		अगर (opt_iter + 1 == opt_len) अणु
			err_offset = opt_iter;
			जाओ out;
		पूर्ण
		tag_len = opt[opt_iter + 1];
		अगर ((tag_len == 0) || (tag_len > (opt_len - opt_iter))) अणु
			err_offset = opt_iter + 1;
			जाओ out;
		पूर्ण
		opt_iter += tag_len;
	पूर्ण

out:
	*option = opt + err_offset;
	वापस err_offset;

पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

#पूर्ण_अगर /* _CIPSO_IPV4_H */
