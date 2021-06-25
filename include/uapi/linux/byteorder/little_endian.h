<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_BYTEORDER_LITTLE_ENDIAN_H
#घोषणा _UAPI_LINUX_BYTEORDER_LITTLE_ENDIAN_H

#अगर_अघोषित __LITTLE_ENDIAN
#घोषणा __LITTLE_ENDIAN 1234
#पूर्ण_अगर
#अगर_अघोषित __LITTLE_ENDIAN_BITFIELD
#घोषणा __LITTLE_ENDIAN_BITFIELD
#पूर्ण_अगर

#समावेश <linux/types.h>
#समावेश <linux/swab.h>

#घोषणा __स्थिरant_htonl(x) ((__क्रमce __be32)___स्थिरant_swab32((x)))
#घोषणा __स्थिरant_ntohl(x) ___स्थिरant_swab32((__क्रमce __be32)(x))
#घोषणा __स्थिरant_htons(x) ((__क्रमce __be16)___स्थिरant_swab16((x)))
#घोषणा __स्थिरant_ntohs(x) ___स्थिरant_swab16((__क्रमce __be16)(x))
#घोषणा __स्थिरant_cpu_to_le64(x) ((__क्रमce __le64)(__u64)(x))
#घोषणा __स्थिरant_le64_to_cpu(x) ((__क्रमce __u64)(__le64)(x))
#घोषणा __स्थिरant_cpu_to_le32(x) ((__क्रमce __le32)(__u32)(x))
#घोषणा __स्थिरant_le32_to_cpu(x) ((__क्रमce __u32)(__le32)(x))
#घोषणा __स्थिरant_cpu_to_le16(x) ((__क्रमce __le16)(__u16)(x))
#घोषणा __स्थिरant_le16_to_cpu(x) ((__क्रमce __u16)(__le16)(x))
#घोषणा __स्थिरant_cpu_to_be64(x) ((__क्रमce __be64)___स्थिरant_swab64((x)))
#घोषणा __स्थिरant_be64_to_cpu(x) ___स्थिरant_swab64((__क्रमce __u64)(__be64)(x))
#घोषणा __स्थिरant_cpu_to_be32(x) ((__क्रमce __be32)___स्थिरant_swab32((x)))
#घोषणा __स्थिरant_be32_to_cpu(x) ___स्थिरant_swab32((__क्रमce __u32)(__be32)(x))
#घोषणा __स्थिरant_cpu_to_be16(x) ((__क्रमce __be16)___स्थिरant_swab16((x)))
#घोषणा __स्थिरant_be16_to_cpu(x) ___स्थिरant_swab16((__क्रमce __u16)(__be16)(x))
#घोषणा __cpu_to_le64(x) ((__क्रमce __le64)(__u64)(x))
#घोषणा __le64_to_cpu(x) ((__क्रमce __u64)(__le64)(x))
#घोषणा __cpu_to_le32(x) ((__क्रमce __le32)(__u32)(x))
#घोषणा __le32_to_cpu(x) ((__क्रमce __u32)(__le32)(x))
#घोषणा __cpu_to_le16(x) ((__क्रमce __le16)(__u16)(x))
#घोषणा __le16_to_cpu(x) ((__क्रमce __u16)(__le16)(x))
#घोषणा __cpu_to_be64(x) ((__क्रमce __be64)__swab64((x)))
#घोषणा __be64_to_cpu(x) __swab64((__क्रमce __u64)(__be64)(x))
#घोषणा __cpu_to_be32(x) ((__क्रमce __be32)__swab32((x)))
#घोषणा __be32_to_cpu(x) __swab32((__क्रमce __u32)(__be32)(x))
#घोषणा __cpu_to_be16(x) ((__क्रमce __be16)__swab16((x)))
#घोषणा __be16_to_cpu(x) __swab16((__क्रमce __u16)(__be16)(x))

अटल __always_अंतरभूत __le64 __cpu_to_le64p(स्थिर __u64 *p)
अणु
	वापस (__क्रमce __le64)*p;
पूर्ण
अटल __always_अंतरभूत __u64 __le64_to_cpup(स्थिर __le64 *p)
अणु
	वापस (__क्रमce __u64)*p;
पूर्ण
अटल __always_अंतरभूत __le32 __cpu_to_le32p(स्थिर __u32 *p)
अणु
	वापस (__क्रमce __le32)*p;
पूर्ण
अटल __always_अंतरभूत __u32 __le32_to_cpup(स्थिर __le32 *p)
अणु
	वापस (__क्रमce __u32)*p;
पूर्ण
अटल __always_अंतरभूत __le16 __cpu_to_le16p(स्थिर __u16 *p)
अणु
	वापस (__क्रमce __le16)*p;
पूर्ण
अटल __always_अंतरभूत __u16 __le16_to_cpup(स्थिर __le16 *p)
अणु
	वापस (__क्रमce __u16)*p;
पूर्ण
अटल __always_अंतरभूत __be64 __cpu_to_be64p(स्थिर __u64 *p)
अणु
	वापस (__क्रमce __be64)__swab64p(p);
पूर्ण
अटल __always_अंतरभूत __u64 __be64_to_cpup(स्थिर __be64 *p)
अणु
	वापस __swab64p((__u64 *)p);
पूर्ण
अटल __always_अंतरभूत __be32 __cpu_to_be32p(स्थिर __u32 *p)
अणु
	वापस (__क्रमce __be32)__swab32p(p);
पूर्ण
अटल __always_अंतरभूत __u32 __be32_to_cpup(स्थिर __be32 *p)
अणु
	वापस __swab32p((__u32 *)p);
पूर्ण
अटल __always_अंतरभूत __be16 __cpu_to_be16p(स्थिर __u16 *p)
अणु
	वापस (__क्रमce __be16)__swab16p(p);
पूर्ण
अटल __always_अंतरभूत __u16 __be16_to_cpup(स्थिर __be16 *p)
अणु
	वापस __swab16p((__u16 *)p);
पूर्ण
#घोषणा __cpu_to_le64s(x) करो अणु (व्योम)(x); पूर्ण जबतक (0)
#घोषणा __le64_to_cpus(x) करो अणु (व्योम)(x); पूर्ण जबतक (0)
#घोषणा __cpu_to_le32s(x) करो अणु (व्योम)(x); पूर्ण जबतक (0)
#घोषणा __le32_to_cpus(x) करो अणु (व्योम)(x); पूर्ण जबतक (0)
#घोषणा __cpu_to_le16s(x) करो अणु (व्योम)(x); पूर्ण जबतक (0)
#घोषणा __le16_to_cpus(x) करो अणु (व्योम)(x); पूर्ण जबतक (0)
#घोषणा __cpu_to_be64s(x) __swab64s((x))
#घोषणा __be64_to_cpus(x) __swab64s((x))
#घोषणा __cpu_to_be32s(x) __swab32s((x))
#घोषणा __be32_to_cpus(x) __swab32s((x))
#घोषणा __cpu_to_be16s(x) __swab16s((x))
#घोषणा __be16_to_cpus(x) __swab16s((x))


#पूर्ण_अगर /* _UAPI_LINUX_BYTEORDER_LITTLE_ENDIAN_H */
