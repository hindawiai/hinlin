<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_UNALIGNED_LE_STRUCT_H
#घोषणा _LINUX_UNALIGNED_LE_STRUCT_H

#समावेश <linux/unaligned/packed_काष्ठा.h>

अटल अंतरभूत u16 get_unaligned_le16(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_cpu16((स्थिर u8 *)p);
पूर्ण

अटल अंतरभूत u32 get_unaligned_le32(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_cpu32((स्थिर u8 *)p);
पूर्ण

अटल अंतरभूत u64 get_unaligned_le64(स्थिर व्योम *p)
अणु
	वापस __get_unaligned_cpu64((स्थिर u8 *)p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le16(u16 val, व्योम *p)
अणु
	__put_unaligned_cpu16(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le32(u32 val, व्योम *p)
अणु
	__put_unaligned_cpu32(val, p);
पूर्ण

अटल अंतरभूत व्योम put_unaligned_le64(u64 val, व्योम *p)
अणु
	__put_unaligned_cpu64(val, p);
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_LE_STRUCT_H */
