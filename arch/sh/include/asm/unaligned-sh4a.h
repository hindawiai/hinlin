<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_UNALIGNED_SH4A_H
#घोषणा __ASM_SH_UNALIGNED_SH4A_H

/*
 * SH-4A has support क्रम unaligned 32-bit loads, and 32-bit loads only.
 * Support क्रम 64-bit accesses are करोne through shअगरting and masking
 * relative to the endianness. Unaligned stores are not supported by the
 * inकाष्ठाion encoding, so these जारी to use the packed
 * काष्ठा.
 *
 * The same note as with the movli.l/movco.l pair applies here, as दीर्घ
 * as the load is guaranteed to be अंतरभूतd, nothing अन्यथा will hook in to
 * r0 and we get the वापस value क्रम मुक्त.
 *
 * NOTE: Due to the fact we require r0 encoding, care should be taken to
 * aव्योम mixing these heavily with other r0 consumers, such as the atomic
 * ops. Failure to adhere to this can result in the compiler running out
 * of spill रेजिस्टरs and blowing up when building at low optimization
 * levels. See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34777.
 */
#समावेश <linux/unaligned/packed_काष्ठा.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/byteorder.h>

अटल अंतरभूत u16 sh4a_get_unaligned_cpu16(स्थिर u8 *p)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	वापस p[0] | p[1] << 8;
#अन्यथा
	वापस p[0] << 8 | p[1];
#पूर्ण_अगर
पूर्ण

अटल __always_अंतरभूत u32 sh4a_get_unaligned_cpu32(स्थिर u8 *p)
अणु
	अचिन्हित दीर्घ unaligned;

	__यंत्र__ __अस्थिर__ (
		"movua.l	@%1, %0\n\t"
		 : "=z" (unaligned)
		 : "r" (p)
	);

	वापस unaligned;
पूर्ण

/*
 * Even though movua.l supports स्वतः-increment on the पढ़ो side, it can
 * only store to r0 due to inकाष्ठाion encoding स्थिरraपूर्णांकs, so just let
 * the compiler sort it out on its own.
 */
अटल अंतरभूत u64 sh4a_get_unaligned_cpu64(स्थिर u8 *p)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	वापस (u64)sh4a_get_unaligned_cpu32(p + 4) << 32 |
		    sh4a_get_unaligned_cpu32(p);
#अन्यथा
	वापस (u64)sh4a_get_unaligned_cpu32(p) << 32 |
		    sh4a_get_unaligned_cpu32(p + 4);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u16 get_unaligned_le16(स्थिर व्योम *p)
अणु
	वापस le16_to_cpu(sh4a_get_unaligned_cpu16(p));
पूर्ण

अटल अंतरभूत u32 get_unaligned_le32(स्थिर व्योम *p)
अणु
	वापस le32_to_cpu(sh4a_get_unaligned_cpu32(p));
पूर्ण

अटल अंतरभूत u64 get_unaligned_le64(स्थिर व्योम *p)
अणु
	वापस le64_to_cpu(sh4a_get_unaligned_cpu64(p));
पूर्ण

अटल अंतरभूत u16 get_unaligned_be16(स्थिर व्योम *p)
अणु
	वापस be16_to_cpu(sh4a_get_unaligned_cpu16(p));
पूर्ण

अटल अंतरभूत u32 get_unaligned_be32(स्थिर व्योम *p)
अणु
	वापस be32_to_cpu(sh4a_get_unaligned_cpu32(p));
पूर्ण

अटल अंतरभूत u64 get_unaligned_be64(स्थिर व्योम *p)
अणु
	वापस be64_to_cpu(sh4a_get_unaligned_cpu64(p));
पूर्ण

अटल अंतरभूत व्योम nonnative_put_le16(u16 val, u8 *p)
अणु
	*p++ = val;
	*p++ = val >> 8;
पूर्ण

अटल अंतरभूत व्योम nonnative_put_le32(u32 val, u8 *p)
अणु
	nonnative_put_le16(val, p);
	nonnative_put_le16(val >> 16, p + 2);
पूर्ण

अटल अंतरभूत व्योम nonnative_put_le64(u64 val, u8 *p)
अणु
	nonnative_put_le32(val, p);
	nonnative_put_le32(val >> 32, p + 4);
पूर्ण

अटल अंतरभूत व्योम nonnative_put_be16(u16 val, u8 *p)
अणु
	*p++ = val >> 8;
	*p++ = val;
पूर्ण

अटल अंतरभूत व्योम nonnative_put_be32(u32 val, u8 *p)
अणु
	nonnative_put_be16(val >> 16, p);
	nonnative_put_be16(val, p + 2);
पूर्ण

अटल अंतरभूत व्योम nonnative_put_be64(u64 val, u8 *p)
अणु
	nonnative_put_be32(val >> 32, p);
	nonnative_put_be32(val, p + 4);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le16(u16 val, व्योम *p)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	__put_unaligned_cpu16(val, p);
#अन्यथा
	nonnative_put_le16(val, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le32(u32 val, व्योम *p)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	__put_unaligned_cpu32(val, p);
#अन्यथा
	nonnative_put_le32(val, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le64(u64 val, व्योम *p)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	__put_unaligned_cpu64(val, p);
#अन्यथा
	nonnative_put_le64(val, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be16(u16 val, व्योम *p)
अणु
#अगर_घोषित __BIG_ENDIAN
	__put_unaligned_cpu16(val, p);
#अन्यथा
	nonnative_put_be16(val, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be32(u32 val, व्योम *p)
अणु
#अगर_घोषित __BIG_ENDIAN
	__put_unaligned_cpu32(val, p);
#अन्यथा
	nonnative_put_be32(val, p);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be64(u64 val, व्योम *p)
अणु
#अगर_घोषित __BIG_ENDIAN
	__put_unaligned_cpu64(val, p);
#अन्यथा
	nonnative_put_be64(val, p);
#पूर्ण_अगर
पूर्ण

/*
 * While it's a bit non-obvious, even though the generic le/be wrappers
 * use the __get/put_xxx prefixing, they actually wrap in to the
 * non-prefixed get/put_xxx variants as provided above.
 */
#समावेश <linux/unaligned/generic.h>

#अगर_घोषित __LITTLE_ENDIAN
# define get_unaligned __get_unaligned_le
# define put_unaligned __put_unaligned_le
#अन्यथा
# define get_unaligned __get_unaligned_be
# define put_unaligned __put_unaligned_be
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_SH_UNALIGNED_SH4A_H */
