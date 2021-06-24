<शैली गुरु>
#अगर_अघोषित _QLA_DSD_H_
#घोषणा _QLA_DSD_H_

#समावेश <यंत्र/unaligned.h>

/* 32-bit data segment descriptor (8 bytes) */
काष्ठा dsd32 अणु
	__le32 address;
	__le32 length;
पूर्ण;

अटल अंतरभूत व्योम append_dsd32(काष्ठा dsd32 **dsd, काष्ठा scatterlist *sg)
अणु
	put_unaligned_le32(sg_dma_address(sg), &(*dsd)->address);
	put_unaligned_le32(sg_dma_len(sg),     &(*dsd)->length);
	(*dsd)++;
पूर्ण

/* 64-bit data segment descriptor (12 bytes) */
काष्ठा dsd64 अणु
	__le64 address;
	__le32 length;
पूर्ण __packed;

अटल अंतरभूत व्योम append_dsd64(काष्ठा dsd64 **dsd, काष्ठा scatterlist *sg)
अणु
	put_unaligned_le64(sg_dma_address(sg), &(*dsd)->address);
	put_unaligned_le32(sg_dma_len(sg),     &(*dsd)->length);
	(*dsd)++;
पूर्ण

#पूर्ण_अगर
