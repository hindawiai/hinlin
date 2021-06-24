<शैली गुरु>
#अगर_अघोषित _LINUX_UNALIGNED_PACKED_STRUCT_H
#घोषणा _LINUX_UNALIGNED_PACKED_STRUCT_H

#समावेश <linux/kernel.h>

काष्ठा __una_u16 अणु u16 x; पूर्ण __packed;
काष्ठा __una_u32 अणु u32 x; पूर्ण __packed;
काष्ठा __una_u64 अणु u64 x; पूर्ण __packed;

अटल अंतरभूत u16 __get_unaligned_cpu16(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा __una_u16 *ptr = (स्थिर काष्ठा __una_u16 *)p;
	वापस ptr->x;
पूर्ण

अटल अंतरभूत u32 __get_unaligned_cpu32(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा __una_u32 *ptr = (स्थिर काष्ठा __una_u32 *)p;
	वापस ptr->x;
पूर्ण

अटल अंतरभूत u64 __get_unaligned_cpu64(स्थिर व्योम *p)
अणु
	स्थिर काष्ठा __una_u64 *ptr = (स्थिर काष्ठा __una_u64 *)p;
	वापस ptr->x;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_cpu16(u16 val, व्योम *p)
अणु
	काष्ठा __una_u16 *ptr = (काष्ठा __una_u16 *)p;
	ptr->x = val;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_cpu32(u32 val, व्योम *p)
अणु
	काष्ठा __una_u32 *ptr = (काष्ठा __una_u32 *)p;
	ptr->x = val;
पूर्ण

अटल अंतरभूत व्योम __put_unaligned_cpu64(u64 val, व्योम *p)
अणु
	काष्ठा __una_u64 *ptr = (काष्ठा __una_u64 *)p;
	ptr->x = val;
पूर्ण

#पूर्ण_अगर /* _LINUX_UNALIGNED_PACKED_STRUCT_H */
