<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNALIGNED_LE_BYTESHIFT_H
#घोषणा _LINUX_UNALIGNED_LE_BYTESHIFT_H

#समावेश <linux/types.h>

अटल अंतरभूत u16 __get_unaligned_le16(स्थिर u8 *p)
अणु
	वापस p[0] | p[1] << 8;
पूर्ण

अटल अंतरभूत u32 __get_unaligned_le32(स्थिर u8 *p)
अणु
	वापस p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
पूर्ण

अटल अंतरभूत u64 __get_unaligned_le64(स्थिर u8 *p)
अणु
	वापस (u64)__get_unaligned_le32(p + 4) << 32 |
	       __get_unaligned_le32(p);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le16(u16 val, u8 *p)
अणु
	*p++ = val;
	*p++ = val >> 8;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le32(u32 val, u8 *p)
अणु
	__put_unaligned_le16(val >> 16, p + 2);
	__put_unaligned_le16(val, p);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le64(u64 val, u8 *p)
अणु
	__put_unaligned_le32(val >> 32, p + 4);
	__put_unaligned_le32(val, p);
पूर्ण

अटल अंतरभूत u16 get_unaligned_le16(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le16(p);
पूर्ण

अटल अंतरभूत u32 get_unaligned_le32(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le32(p);
पूर्ण

अटल अंतरभूत u64 get_unaligned_le64(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le64(p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le16(u16 val, व्योम *p)
अणु
	__put_unaligned_le16(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le32(u32 val, व्योम *p)
अणु
	__put_unaligned_le32(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le64(u64 val, व्योम *p)
अणु
	__put_unaligned_le64(val, p);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_LE_BYTESHIFT_H */
