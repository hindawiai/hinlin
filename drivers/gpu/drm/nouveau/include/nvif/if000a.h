<शैली गुरु>
#अगर_अघोषित __NVIF_IF000A_H__
#घोषणा __NVIF_IF000A_H__
काष्ठा nvअगर_mem_v0 अणु
	__u8  version;
	__u8  type;
	__u8  page;
	__u8  pad03[5];
	__u64 size;
	__u64 addr;
	__u8  data[];
पूर्ण;

काष्ठा nvअगर_mem_ram_vn अणु
पूर्ण;

काष्ठा nvअगर_mem_ram_v0 अणु
	__u8  version;
	__u8  pad01[7];
	dma_addr_t *dma;
	काष्ठा scatterlist *sgl;
पूर्ण;
#पूर्ण_अगर
