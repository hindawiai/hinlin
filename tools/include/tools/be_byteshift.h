<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_BE_BYTESHIFT_H
#घोषणा _TOOLS_BE_BYTESHIFT_H

#समावेश <मानक_निवेशt.h>

अटल अंतरभूत uपूर्णांक16_t __get_unaligned_be16(स्थिर uपूर्णांक8_t *p)
अणु
	वापस p[0] << 8 | p[1];
पूर्ण

अटल अंतरभूत uपूर्णांक32_t __get_unaligned_be32(स्थिर uपूर्णांक8_t *p)
अणु
	वापस p[0] << 24 | p[1] << 16 | p[2] << 8 | p[3];
पूर्ण

अटल अंतरभूत uपूर्णांक64_t __get_unaligned_be64(स्थिर uपूर्णांक8_t *p)
अणु
	वापस (uपूर्णांक64_t)__get_unaligned_be32(p) << 32 |
	       __get_unaligned_be32(p + 4);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be16(uपूर्णांक16_t val, uपूर्णांक8_t *p)
अणु
	*p++ = val >> 8;
	*p++ = val;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be32(uपूर्णांक32_t val, uपूर्णांक8_t *p)
अणु
	__put_unaligned_be16(val >> 16, p);
	__put_unaligned_be16(val, p + 2);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_be64(uपूर्णांक64_t val, uपूर्णांक8_t *p)
अणु
	__put_unaligned_be32(val >> 32, p);
	__put_unaligned_be32(val, p + 4);
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_unaligned_be16(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be16((स्थिर uपूर्णांक8_t *)p);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_unaligned_be32(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be32((स्थिर uपूर्णांक8_t *)p);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t get_unaligned_be64(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_be64((स्थिर uपूर्णांक8_t *)p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be16(uपूर्णांक16_t val, व्योम *p)
अणु
	__put_unaligned_be16(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be32(uपूर्णांक32_t val, व्योम *p)
अणु
	__put_unaligned_be32(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_be64(uपूर्णांक64_t val, व्योम *p)
अणु
	__put_unaligned_be64(val, p);
पूर्ण

#पूर्ण_अगर /* _TOOLS_BE_BYTESHIFT_H */
