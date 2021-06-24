<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNALIGNED_BE_BYTESHIFT_H
#घोषणा _LINUX_UNALIGNED_BE_BYTESHIFT_H

#समावेश <linux/types.h>

अटल अंतरभूत u16 __get_unaligned_be16(स्थिर u8 *p)
अणु
	वापस p[0] << 8 | p[1];
पूर्ण

अटल अंतरभूत u32 __get_unaligned_be32(स्थिर u8 *p)
अणु
	वापस p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
पूर्ण

अटल अंतरभूत u64 __get_unaligned_be64(स्थिर u8 *p)
अणु
	वापस (u64)__get_unaligned_be32(p) << 32 |
	       __get_unaligned_be32(p + 4);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be16(u16 val, u8 *p)
अणु
	*p++ = val >> 8;
	*p++ = val;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be32(u32 val, u8 *p)
अणु
	__put_unaligned_be16(val >> 16, p);
	__put_unaligned_be16(val, p + 2);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be64(u64 val, u8 *p)
अणु
	__put_unaligned_be32(val >> 32, p);
	__put_unaligned_be32(val, p + 4);
पूर्ण

अटल अंतरभूत u16 get_unaligned_be16(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be16(p);
पूर्ण

अटल अंतरभूत u32 get_unaligned_be32(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be32(p);
पूर्ण

अटल अंतरभूत u64 get_unaligned_be64(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be64(p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be16(u16 val, व्योम *p)
अणु
	__put_unaligned_be16(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be32(u32 val, व्योम *p)
अणु
	__put_unaligned_be32(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be64(u64 val, व्योम *p)
अणु
	__put_unaligned_be64(val, p);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_BE_BYTESHIFT_H */
