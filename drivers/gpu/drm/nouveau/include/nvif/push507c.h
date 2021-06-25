<शैली गुरु>
#अगर_अघोषित __NVIF_PUSH507C_H__
#घोषणा __NVIF_PUSH507C_H__
#समावेश <nvअगर/push.h>

#समावेश <nvhw/class/cl507c.h>

#घोषणा PUSH_HDR(p,m,c) करो अणु                                                    \
        PUSH_ASSERT(!((m) & ~DRF_SMASK(NV507C_DMA_METHOD_OFFSET)), "mthd");     \
        PUSH_ASSERT(!((c) & ~DRF_MASK(NV507C_DMA_METHOD_COUNT)), "size");       \
        PUSH_DATA__((p), NVDEF(NV507C, DMA, OPCODE, METHOD) |                   \
			 NVVAL(NV507C, DMA, METHOD_COUNT, (c)) |                \
			 NVVAL(NV507C, DMA, METHOD_OFFSET, (m) >> 2),           \
		    " mthd 0x%04x size %d - %s", (u32)(m), (u32)(c), __func__); \
पूर्ण जबतक(0)

#घोषणा PUSH_MTHD_HDR(p,s,m,c) PUSH_HDR(p,m,c)
#घोषणा PUSH_MTHD_INC 4:4

#घोषणा PUSH_JUMP(p,o) करो अणु                                                 \
        PUSH_ASSERT(!((o) & ~DRF_SMASK(NV507C_DMA_JUMP_OFFSET)), "offset"); \
	PUSH_DATA__((p), NVDEF(NV507C, DMA, OPCODE, JUMP) |                 \
			 NVVAL(NV507C, DMA, JUMP_OFFSET, (o) >> 2),         \
		    " jump 0x%08x - %s", (u32)(o), __func__);               \
पूर्ण जबतक(0)
#पूर्ण_अगर
