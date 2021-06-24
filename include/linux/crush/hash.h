<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित CEPH_CRUSH_HASH_H
#घोषणा CEPH_CRUSH_HASH_H

#अगर_घोषित __KERNEL__
# include <linux/types.h>
#अन्यथा
# include "crush_compat.h"
#पूर्ण_अगर

#घोषणा CRUSH_HASH_RJENKINS1   0

#घोषणा CRUSH_HASH_DEFAULT CRUSH_HASH_RJENKINS1

बाह्य स्थिर अक्षर *crush_hash_name(पूर्णांक type);

बाह्य __u32 crush_hash32(पूर्णांक type, __u32 a);
बाह्य __u32 crush_hash32_2(पूर्णांक type, __u32 a, __u32 b);
बाह्य __u32 crush_hash32_3(पूर्णांक type, __u32 a, __u32 b, __u32 c);
बाह्य __u32 crush_hash32_4(पूर्णांक type, __u32 a, __u32 b, __u32 c, __u32 d);
बाह्य __u32 crush_hash32_5(पूर्णांक type, __u32 a, __u32 b, __u32 c, __u32 d,
			    __u32 e);

#पूर्ण_अगर
