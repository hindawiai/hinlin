<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
#अगर_अघोषित __NVIF_CL0002_H__
#घोषणा __NVIF_CL0002_H__

काष्ठा nv_dma_v0 अणु
	__u8  version;
#घोषणा NV_DMA_V0_TARGET_VM                                                0x00
#घोषणा NV_DMA_V0_TARGET_VRAM                                              0x01
#घोषणा NV_DMA_V0_TARGET_PCI                                               0x02
#घोषणा NV_DMA_V0_TARGET_PCI_US                                            0x03
#घोषणा NV_DMA_V0_TARGET_AGP                                               0x04
	__u8  target;
#घोषणा NV_DMA_V0_ACCESS_VM                                                0x00
#घोषणा NV_DMA_V0_ACCESS_RD                                                0x01
#घोषणा NV_DMA_V0_ACCESS_WR                                                0x02
#घोषणा NV_DMA_V0_ACCESS_RDWR                 (NV_DMA_V0_ACCESS_RD | NV_DMA_V0_ACCESS_WR)
	__u8  access;
	__u8  pad03[5];
	__u64 start;
	__u64 limit;
	/* ... chipset-specअगरic class data */
पूर्ण;

काष्ठा nv50_dma_v0 अणु
	__u8  version;
#घोषणा NV50_DMA_V0_PRIV_VM                                                0x00
#घोषणा NV50_DMA_V0_PRIV_US                                                0x01
#घोषणा NV50_DMA_V0_PRIV__S                                                0x02
	__u8  priv;
#घोषणा NV50_DMA_V0_PART_VM                                                0x00
#घोषणा NV50_DMA_V0_PART_256                                               0x01
#घोषणा NV50_DMA_V0_PART_1KB                                               0x02
	__u8  part;
#घोषणा NV50_DMA_V0_COMP_NONE                                              0x00
#घोषणा NV50_DMA_V0_COMP_1                                                 0x01
#घोषणा NV50_DMA_V0_COMP_2                                                 0x02
#घोषणा NV50_DMA_V0_COMP_VM                                                0x03
	__u8  comp;
#घोषणा NV50_DMA_V0_KIND_PITCH                                             0x00
#घोषणा NV50_DMA_V0_KIND_VM                                                0x7f
	__u8  kind;
	__u8  pad05[3];
पूर्ण;

काष्ठा gf100_dma_v0 अणु
	__u8  version;
#घोषणा GF100_DMA_V0_PRIV_VM                                               0x00
#घोषणा GF100_DMA_V0_PRIV_US                                               0x01
#घोषणा GF100_DMA_V0_PRIV__S                                               0x02
	__u8  priv;
#घोषणा GF100_DMA_V0_KIND_PITCH                                            0x00
#घोषणा GF100_DMA_V0_KIND_VM                                               0xff
	__u8  kind;
	__u8  pad03[5];
पूर्ण;

काष्ठा gf119_dma_v0 अणु
	__u8  version;
#घोषणा GF119_DMA_V0_PAGE_LP                                               0x00
#घोषणा GF119_DMA_V0_PAGE_SP                                               0x01
	__u8  page;
#घोषणा GF119_DMA_V0_KIND_PITCH                                            0x00
#घोषणा GF119_DMA_V0_KIND_VM                                               0xff
	__u8  kind;
	__u8  pad03[5];
पूर्ण;
#पूर्ण_अगर
