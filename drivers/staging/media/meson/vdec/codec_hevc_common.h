<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2018 BayLibre, SAS
 * Author: Maxime Jourdan <mjourdan@baylibre.com>
 */

#अगर_अघोषित __MESON_VDEC_HEVC_COMMON_H_
#घोषणा __MESON_VDEC_HEVC_COMMON_H_

#समावेश "vdec.h"

#घोषणा PARSER_CMD_SKIP_CFG_0 0x0000090b
#घोषणा PARSER_CMD_SKIP_CFG_1 0x1b14140f
#घोषणा PARSER_CMD_SKIP_CFG_2 0x001b1910

#घोषणा VDEC_HEVC_PARSER_CMD_LEN 37
बाह्य स्थिर u16 vdec_hevc_parser_cmd[VDEC_HEVC_PARSER_CMD_LEN];

#घोषणा MAX_REF_PIC_NUM	24

काष्ठा codec_hevc_common अणु
	व्योम      *fbc_buffer_vaddr[MAX_REF_PIC_NUM];
	dma_addr_t fbc_buffer_paddr[MAX_REF_PIC_NUM];

	व्योम      *mmu_header_vaddr[MAX_REF_PIC_NUM];
	dma_addr_t mmu_header_paddr[MAX_REF_PIC_NUM];

	व्योम      *mmu_map_vaddr;
	dma_addr_t mmu_map_paddr;
पूर्ण;

/* Returns 1 अगर we must use framebuffer compression */
अटल अंतरभूत पूर्णांक codec_hevc_use_fbc(u32 pixfmt, पूर्णांक is_10bit)
अणु
	/* TOFIX: Handle Amlogic Compressed buffer क्रम 8bit also */
	वापस is_10bit;
पूर्ण

/* Returns 1 अगर we are decoding 10-bit but outputting 8-bit NV12 */
अटल अंतरभूत पूर्णांक codec_hevc_use_करोwnsample(u32 pixfmt, पूर्णांक is_10bit)
अणु
	वापस is_10bit;
पूर्ण

/* Returns 1 अगर we are decoding using the IOMMU */
अटल अंतरभूत पूर्णांक codec_hevc_use_mmu(u32 revision, u32 pixfmt, पूर्णांक is_10bit)
अणु
	वापस revision >= VDEC_REVISION_G12A &&
	       codec_hevc_use_fbc(pixfmt, is_10bit);
पूर्ण

/* Configure decode head पढ़ो mode */
व्योम codec_hevc_setup_decode_head(काष्ठा amvdec_session *sess, पूर्णांक is_10bit);

व्योम codec_hevc_मुक्त_fbc_buffers(काष्ठा amvdec_session *sess,
				 काष्ठा codec_hevc_common *comm);

व्योम codec_hevc_मुक्त_mmu_headers(काष्ठा amvdec_session *sess,
				 काष्ठा codec_hevc_common *comm);

पूर्णांक codec_hevc_setup_buffers(काष्ठा amvdec_session *sess,
			     काष्ठा codec_hevc_common *comm,
			     पूर्णांक is_10bit);

व्योम codec_hevc_fill_mmu_map(काष्ठा amvdec_session *sess,
			     काष्ठा codec_hevc_common *comm,
			     काष्ठा vb2_buffer *vb);

#पूर्ण_अगर
