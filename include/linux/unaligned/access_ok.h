<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNALIGNED_ACCESS_OK_H
#घोषणा _LINUX_UNALIGNED_ACCESS_OK_H

#समावेश <linux/kernel.h>
#समावेश <यंत्र/byteorder.h>

अटल __always_अंतरभूत u16 get_unaligned_le16(स्थिर व्योम *p)
अणु
	वापस le16_to_cpup((__le16 *)p);
पूर्ण

अटल __always_अंतरभूत u32 get_unaligned_le32(स्थिर व्योम *p)
अणु
	वापस le32_to_cpup((__le32 *)p);
पूर्ण

अटल __always_अंतरभूत u64 get_unaligned_le64(स्थिर व्योम *p)
अणु
	वापस le64_to_cpup((__le64 *)p);
पूर्ण

अटल __always_अंतरभूत u16 get_unaligned_be16(स्थिर व्योम *p)
अणु
	वापस be16_to_cpup((__be16 *)p);
पूर्ण

अटल __always_अंतरभूत u32 get_unaligned_be32(स्थिर व्योम *p)
अणु
	वापस be32_to_cpup((__be32 *)p);
पूर्ण

अटल __always_अंतरभूत u64 get_unaligned_be64(स्थिर व्योम *p)
अणु
	वापस be64_to_cpup((__be64 *)p);
पूर्ण

अटल __always_अंतरभूत व्योम put_unaligned_le16(u16 val, व्योम *p)
अणु
	*((__le16 *)p) = cpu_to_le16(val);
पूर्ण

अटल __always_अंतरभूत व्योम put_unaligned_le32(u32 val, व्योम *p)
अणु
	*((__le32 *)p) = cpu_to_le32(val);
पूर्ण

अटल __always_अंतरभूत व्योम put_unaligned_le64(u64 val, व्योम *p)
अणु
	*((__le64 *)p) = cpu_to_le64(val);
पूर्ण

अटल __always_अंतरभूत व्योम put_unaligned_be16(u16 val, व्योम *p)
अणु
	*((__be16 *)p) = cpu_to_be16(val);
पूर्ण

अटल __always_अंतरभूत व्योम put_unaligned_be32(u32 val, व्योम *p)
अणु
	*((__be32 *)p) = cpu_to_be32(val);
पूर्ण

अटल __always_अंतरभूत व्योम put_unaligned_be64(u64 val, व्योम *p)
अणु
	*((__be64 *)p) = cpu_to_be64(val);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_ACCESS_OK_H */
