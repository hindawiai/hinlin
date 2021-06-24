<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * CALIPSO - Common Architecture Label IPv6 Security Option
 *
 * This is an implementation of the CALIPSO protocol as specअगरied in
 * RFC 5570.
 *
 * Authors: Paul Moore <paul@paul-moore.com>
 *          Huw Davies <huw@codeweavers.com>
 */

/*
 * (c) Copyright Hewlett-Packard Development Company, L.P., 2006
 * (c) Copyright Huw Davies <huw@codeweavers.com>, 2015
 */

#अगर_अघोषित _CALIPSO_H
#घोषणा _CALIPSO_H

#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/list.h>
#समावेश <linux/net.h>
#समावेश <linux/skbuff.h>
#समावेश <net/netlabel.h>
#समावेश <net/request_sock.h>
#समावेश <linux/refcount.h>
#समावेश <यंत्र/unaligned.h>

/* known करोi values */
#घोषणा CALIPSO_DOI_UNKNOWN          0x00000000

/* करोi mapping types */
#घोषणा CALIPSO_MAP_UNKNOWN          0
#घोषणा CALIPSO_MAP_PASS             2

/*
 * CALIPSO DOI definitions
 */

/* DOI definition काष्ठा */
काष्ठा calipso_करोi अणु
	u32 करोi;
	u32 type;

	refcount_t refcount;
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
पूर्ण;

/*
 * Sysctl Variables
 */
बाह्य पूर्णांक calipso_cache_enabled;
बाह्य पूर्णांक calipso_cache_bucketsize;

#अगर_घोषित CONFIG_NETLABEL
पूर्णांक __init calipso_init(व्योम);
व्योम calipso_निकास(व्योम);
bool calipso_validate(स्थिर काष्ठा sk_buff *skb, स्थिर अचिन्हित अक्षर *option);
#अन्यथा
अटल अंतरभूत पूर्णांक __init calipso_init(व्योम)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम calipso_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत bool calipso_validate(स्थिर काष्ठा sk_buff *skb,
				    स्थिर अचिन्हित अक्षर *option)
अणु
	वापस true;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

#पूर्ण_अगर /* _CALIPSO_H */
