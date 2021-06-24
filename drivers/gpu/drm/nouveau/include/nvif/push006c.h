<शैली गुरु>
#अगर_अघोषित __NVIF_PUSH006C_H__
#घोषणा __NVIF_PUSH006C_H__
#समावेश <nvअगर/push.h>

#समावेश <nvhw/class/cl006c.h>

#अगर_अघोषित PUSH006C_SUBC
// Host methods
#घोषणा PUSH006C_SUBC_NV06E	0
#घोषणा PUSH006C_SUBC_NV176E	0
#घोषणा PUSH006C_SUBC_NV826F	0

// ContextSurfaces2d
#घोषणा PUSH006C_SUBC_NV042	0
#घोषणा PUSH006C_SUBC_NV062	0

// ContextClipRectangle
#घोषणा PUSH006C_SUBC_NV019	0

// ContextRop
#घोषणा PUSH006C_SUBC_NV043	0

// ContextPattern
#घोषणा PUSH006C_SUBC_NV044	0

// Misc करोdginess...
#घोषणा PUSH006C_SUBC_NV_SW	1

// ImageBlit
#घोषणा PUSH006C_SUBC_NV05F	2
#घोषणा PUSH006C_SUBC_NV09F	2

// GdiRectangleText
#घोषणा PUSH006C_SUBC_NV04A	3

// Twod
#घोषणा PUSH006C_SUBC_NV502D	3

// MemoryToMemoryFormat
#घोषणा PUSH006C_SUBC_NV039	4
#घोषणा PUSH006C_SUBC_NV5039	4

// DmaCopy
#घोषणा PUSH006C_SUBC_NV85B5	4

// Cipher
#घोषणा PUSH006C_SUBC_NV74C1	4
#पूर्ण_अगर

#घोषणा PUSH_HDR(p,o,n,s,m,c) करो अणु                                        \
        PUSH_ASSERT(!((s) & ~DRF_MASK(NV06C_METHOD_SUBCHANNEL)), "subc"); \
        PUSH_ASSERT(!((m) & ~DRF_SMASK(NV06C_METHOD_ADDRESS)), "mthd");   \
        PUSH_ASSERT(!((c) & ~DRF_MASK(NV06C_METHOD_COUNT)), "count");     \
        PUSH_DATA__((p), NVVAL_X(NV06C_METHOD_ADDRESS, (m) >> 2) |        \
			 NVVAL_X(NV06C_METHOD_SUBCHANNEL, (s)) |          \
			 NVVAL_X(NV06C_METHOD_COUNT, (c)) |               \
			 NVVAL_X(NV06C_OPCODE, NV06C_OPCODE_##o),         \
		    " "n" subc %d mthd 0x%04x size %d - %s",              \
		    (u32)(s), (u32)(m), (u32)(c), __func__);              \
पूर्ण जबतक(0)

#घोषणा PUSH_MTHD_HDR(p,c,m,n) PUSH_HDR(p, METHOD, "incr", PUSH006C_SUBC_##c, m, n)
#घोषणा PUSH_MTHD_INC 4:4
#घोषणा PUSH_NINC_HDR(p,c,m,n) PUSH_HDR(p, NONINC_METHOD, "ninc", PUSH006C_SUBC_##c, m, n)
#घोषणा PUSH_NINC_INC 0:0

#घोषणा PUSH_JUMP(p,o) करो अणु                                         \
        PUSH_ASSERT(!((o) & ~0x1fffffffcULL), "offset");            \
	PUSH_DATA__((p), NVVAL_X(NV06C_OPCODE, NV06C_OPCODE_JUMP) | \
			 NVVAL_X(NV06C_JUMP_OFFSET, (o) >> 2),      \
		    " jump 0x%08x - %s", (u32)(o), __func__);       \
पूर्ण जबतक(0)
#पूर्ण_अगर
