<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LE_BYTESHIFT_H
#घोषणा _TOOLS_LE_BYTESHIFT_H

#समावेश <मानक_निवेशt.h>

अटल अंतरभूत uपूर्णांक16_t __get_unaligned_le16(स्थिर uपूर्णांक8_t *p)
अणु
	वापस p[0] | p[1] << 8;
पूर्ण

अटल अंतरभूत uपूर्णांक32_t __get_unaligned_le32(स्थिर uपूर्णांक8_t *p)
अणु
	वापस p[0] | p[1] << 8 | p[2] << 16 | p[3] << 24;
पूर्ण

अटल अंतरभूत uपूर्णांक64_t __get_unaligned_le64(स्थिर uपूर्णांक8_t *p)
अणु
	वापस (uपूर्णांक64_t)__get_unaligned_le32(p + 4) << 32 |
	       __get_unaligned_le32(p);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le16(uपूर्णांक16_t val, uपूर्णांक8_t *p)
अणु
	*p++ = val;
	*p++ = val >> 8;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le32(uपूर्णांक32_t val, uपूर्णांक8_t *p)
अणु
	__put_unaligned_le16(val >> 16, p + 2);
	__put_unaligned_le16(val, p);
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_le64(uपूर्णांक64_t val, uपूर्णांक8_t *p)
अणु
	__put_unaligned_le32(val >> 32, p + 4);
	__put_unaligned_le32(val, p);
पूर्ण

अटल अंतरभूत uपूर्णांक16_t get_unaligned_le16(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le16((स्थिर uपूर्णांक8_t *)p);
पूर्ण

अटल अंतरभूत uपूर्णांक32_t get_unaligned_le32(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le32((स्थिर uपूर्णांक8_t *)p);
पूर्ण

अटल अंतरभूत uपूर्णांक64_t get_unaligned_le64(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_le64((स्थिर uपूर्णांक8_t *)p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le16(uपूर्णांक16_t val, व्योम *p)
अणु
	__put_unaligned_le16(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le32(uपूर्णांक32_t val, व्योम *p)
अणु
	__put_unaligned_le32(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le64(uपूर्णांक64_t val, व्योम *p)
अणु
	__put_unaligned_le64(val, p);
पूर्ण

#पूर्ण_अगर /* _TOOLS_LE_BYTESHIFT_H */
