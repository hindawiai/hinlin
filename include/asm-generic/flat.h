<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_GENERIC_FLAT_H
#घोषणा _ASM_GENERIC_FLAT_H

#समावेश <linux/uaccess.h>

अटल अंतरभूत पूर्णांक flat_get_addr_from_rp(u32 __user *rp, u32 relval, u32 flags,
		u32 *addr)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	वापस copy_from_user(addr, rp, 4) ? -EFAULT : 0;
#अन्यथा
	वापस get_user(*addr, rp);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक flat_put_addr_at_rp(u32 __user *rp, u32 addr, u32 rel)
अणु
#अगर_अघोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	वापस copy_to_user(rp, &addr, 4) ? -EFAULT : 0;
#अन्यथा
	वापस put_user(addr, rp);
#पूर्ण_अगर
पूर्ण

#पूर्ण_अगर /* _ASM_GENERIC_FLAT_H */
