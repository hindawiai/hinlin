<शैली गुरु>
#अगर_अघोषित __NVIF_PUSH906F_H__
#घोषणा __NVIF_PUSH906F_H__
#समावेश <nvअगर/push.h>

#समावेश <nvhw/class/cl906f.h>

#अगर_अघोषित PUSH906F_SUBC
// Host methods
#घोषणा PUSH906F_SUBC_NV906F	0

// Twod
#घोषणा PUSH906F_SUBC_NV902D	3

// MemoryToMemoryFormat
#घोषणा PUSH906F_SUBC_NV9039	4

// DmaCopy
#घोषणा PUSH906F_SUBC_NV90B5	4
#घोषणा PUSH906F_SUBC_NVA0B5	4
#पूर्ण_अगर

#घोषणा PUSH_HDR(p,o,n,f,s,m,c) करो अणु                                                \
        PUSH_ASSERT(!((s) & ~DRF_MASK(NV906F_DMA_METHOD_SUBCHANNEL)), "subc");      \
        PUSH_ASSERT(!((m) & ~(DRF_MASK(NV906F_DMA_METHOD_ADDRESS) << 2)), "mthd");   \
        PUSH_ASSERT(!((c) & ~DRF_MASK(NV906F_DMA_METHOD_COUNT)), "count/immd");     \
        PUSH_DATA__((p), NVVAL(NV906F, DMA, METHOD_ADDRESS, (m) >> 2) |             \
			 NVVAL(NV906F, DMA, METHOD_SUBCHANNEL, (s)) |               \
			 NVVAL(NV906F, DMA, METHOD_COUNT, (c)) |                    \
			 NVDEF(NV906F, DMA, SEC_OP, o),                             \
		    " "n" subc %d mthd 0x%04x "f" - %s",                            \
		    (u32)(s), (u32)(m), (u32)(c), __func__);                        \
पूर्ण जबतक(0)

#घोषणा PUSH_MTHD_INC 4:4
#घोषणा PUSH_MTHD_HDR(p,c,m,n) \
	PUSH_HDR(p, INC_METHOD, "incr", "size %d", PUSH906F_SUBC_##c, m, n)

#घोषणा PUSH_NINC_INC 0:0
#घोषणा PUSH_NINC_HDR(p,c,m,n) \
	PUSH_HDR(p, NON_INC_METHOD, "ninc", "size %d", PUSH906F_SUBC_##c, m, n)

#घोषणा PUSH_IMMD_HDR(p,c,m,n) \
	PUSH_HDR(p, IMMD_DATA_METHOD, "immd", "data 0x%04x", PUSH906F_SUBC_##c, m, n)

#घोषणा PUSH_1INC_INC 4:0
#घोषणा PUSH_1INC_HDR(p,c,m,n) \
	PUSH_HDR(p, ONE_INC, "oinc", "size %d", PUSH906F_SUBC_##c, m, n)
#पूर्ण_अगर
