<शैली गुरु>
#अगर_अघोषित __NVIF_PUSHC37B_H__
#घोषणा __NVIF_PUSHC37B_H__
#समावेश <nvअगर/push.h>

#समावेश <nvhw/class/clc37b.h>

#घोषणा PUSH_HDR(p,m,c) करो अणु                                                    \
        PUSH_ASSERT(!((m) & ~DRF_SMASK(NVC37B_DMA_METHOD_OFFSET)), "mthd");     \
        PUSH_ASSERT(!((c) & ~DRF_MASK(NVC37B_DMA_METHOD_COUNT)), "size");       \
        PUSH_DATA__((p), NVDEF(NVC37B, DMA, OPCODE, METHOD) |                   \
			 NVVAL(NVC37B, DMA, METHOD_COUNT, (c)) |                \
			 NVVAL(NVC37B, DMA, METHOD_OFFSET, (m) >> 2),           \
		    " mthd 0x%04x size %d - %s", (u32)(m), (u32)(c), __func__); \
पूर्ण जबतक(0)

#घोषणा PUSH_MTHD_HDR(p,s,m,c) PUSH_HDR(p,m,c)
#घोषणा PUSH_MTHD_INC 4:4
#पूर्ण_अगर
