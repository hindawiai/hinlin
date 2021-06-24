<शैली गुरु>
#अगर_अघोषित __NVIF_PUSH206E_H__
#घोषणा __NVIF_PUSH206E_H__
#समावेश <nvअगर/push006c.h>

#समावेश <nvhw/class/cl206e.h>

#घोषणा PUSH_CALL(p,o) करो अणु                                         \
        PUSH_ASSERT(!((o) & ~0xffffffffcULL), "offset");            \
	PUSH_DATA__((p), NVDEF(NV206E, DMA, OPCODE2, CALL) |        \
			 NVVAL(NV206E, DMA, CALL_OFFSET, (o) >> 2), \
		    " call 0x%08x - %s", (u32)(o), __func__);       \
पूर्ण जबतक(0)
#पूर्ण_अगर
