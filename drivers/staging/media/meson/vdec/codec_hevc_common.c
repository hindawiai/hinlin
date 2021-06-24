<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (C) 2018 Maxime Jourdan <mjourdan@baylibre.com>
 */

#समावेश <media/v4l2-mem2स्मृति.स>
#समावेश <media/videobuf2-dma-contig.h>

#समावेश "codec_hevc_common.h"
#समावेश "vdec_helpers.h"
#समावेश "hevc_regs.h"

#घोषणा MMU_COMPRESS_HEADER_SIZE 0x48000
#घोषणा MMU_MAP_SIZE 0x4800

स्थिर u16 vdec_hevc_parser_cmd[] = अणु
	0x0401,	0x8401,	0x0800,	0x0402,
	0x9002,	0x1423,	0x8CC3,	0x1423,
	0x8804,	0x9825,	0x0800,	0x04FE,
	0x8406,	0x8411,	0x1800,	0x8408,
	0x8409,	0x8C2A,	0x9C2B,	0x1C00,
	0x840F,	0x8407,	0x8000,	0x8408,
	0x2000,	0xA800,	0x8410,	0x04DE,
	0x840C,	0x840D,	0xAC00,	0xA000,
	0x08C0,	0x08E0,	0xA40E,	0xFC00,
	0x7C00
पूर्ण;

/* Configure decode head पढ़ो mode */
व्योम codec_hevc_setup_decode_head(काष्ठा amvdec_session *sess, पूर्णांक is_10bit)
अणु
	काष्ठा amvdec_core *core = sess->core;
	u32 body_size = amvdec_am21c_body_size(sess->width, sess->height);
	u32 head_size = amvdec_am21c_head_size(sess->width, sess->height);

	अगर (!codec_hevc_use_fbc(sess->pixfmt_cap, is_10bit)) अणु
		/* Enable 2-plane reference पढ़ो mode */
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_DECOMP_CTL1, BIT(31));
		वापस;
	पूर्ण

	अगर (codec_hevc_use_mmu(core->platक्रमm->revision,
			       sess->pixfmt_cap, is_10bit))
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_DECOMP_CTL1, BIT(4));
	अन्यथा
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_DECOMP_CTL1, 0);

	अगर (core->platक्रमm->revision < VDEC_REVISION_SM1)
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_DECOMP_CTL2, body_size / 32);
	amvdec_ग_लिखो_करोs(core, HEVC_CM_BODY_LENGTH, body_size);
	amvdec_ग_लिखो_करोs(core, HEVC_CM_HEADER_OFFSET, body_size);
	amvdec_ग_लिखो_करोs(core, HEVC_CM_HEADER_LENGTH, head_size);
पूर्ण
EXPORT_SYMBOL_GPL(codec_hevc_setup_decode_head);

अटल व्योम codec_hevc_setup_buffers_gxbb(काष्ठा amvdec_session *sess,
					  काष्ठा codec_hevc_common *comm,
					  पूर्णांक is_10bit)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा v4l2_m2m_buffer *buf;
	u32 buf_num = v4l2_m2m_num_dst_bufs_पढ़ोy(sess->m2m_ctx);
	dma_addr_t buf_y_paddr = 0;
	dma_addr_t buf_uv_paddr = 0;
	u32 idx = 0;
	u32 val;
	पूर्णांक i;

	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CONF_ADDR, 0);

	v4l2_m2m_क्रम_each_dst_buf(sess->m2m_ctx, buf) अणु
		काष्ठा vb2_buffer *vb = &buf->vb.vb2_buf;

		idx = vb->index;

		अगर (codec_hevc_use_करोwnsample(sess->pixfmt_cap, is_10bit))
			buf_y_paddr = comm->fbc_buffer_paddr[idx];
		अन्यथा
			buf_y_paddr = vb2_dma_contig_plane_dma_addr(vb, 0);

		अगर (codec_hevc_use_fbc(sess->pixfmt_cap, is_10bit)) अणु
			val = buf_y_paddr | (idx << 8) | 1;
			amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CMD_ADDR,
					 val);
		पूर्ण अन्यथा अणु
			buf_uv_paddr = vb2_dma_contig_plane_dma_addr(vb, 1);
			val = buf_y_paddr | ((idx * 2) << 8) | 1;
			amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CMD_ADDR,
					 val);
			val = buf_uv_paddr | ((idx * 2 + 1) << 8) | 1;
			amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CMD_ADDR,
					 val);
		पूर्ण
	पूर्ण

	अगर (codec_hevc_use_fbc(sess->pixfmt_cap, is_10bit))
		val = buf_y_paddr | (idx << 8) | 1;
	अन्यथा
		val = buf_y_paddr | ((idx * 2) << 8) | 1;

	/* Fill the reमुख्यing unused slots with the last buffer's Y addr */
	क्रम (i = buf_num; i < MAX_REF_PIC_NUM; ++i)
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CMD_ADDR, val);

	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CONF_ADDR, 1);
	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDR, 1);
	क्रम (i = 0; i < 32; ++i)
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_DATA_ADDR, 0);
पूर्ण

अटल व्योम codec_hevc_setup_buffers_gxl(काष्ठा amvdec_session *sess,
					 काष्ठा codec_hevc_common *comm,
					 पूर्णांक is_10bit)
अणु
	काष्ठा amvdec_core *core = sess->core;
	काष्ठा v4l2_m2m_buffer *buf;
	u32 revision = core->platक्रमm->revision;
	u32 pixfmt_cap = sess->pixfmt_cap;
	पूर्णांक i;

	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CONF_ADDR,
			 BIT(2) | BIT(1));

	v4l2_m2m_क्रम_each_dst_buf(sess->m2m_ctx, buf) अणु
		काष्ठा vb2_buffer *vb = &buf->vb.vb2_buf;
		dma_addr_t buf_y_paddr = 0;
		dma_addr_t buf_uv_paddr = 0;
		u32 idx = vb->index;

		अगर (codec_hevc_use_mmu(revision, pixfmt_cap, is_10bit))
			buf_y_paddr = comm->mmu_header_paddr[idx];
		अन्यथा अगर (codec_hevc_use_करोwnsample(pixfmt_cap, is_10bit))
			buf_y_paddr = comm->fbc_buffer_paddr[idx];
		अन्यथा
			buf_y_paddr = vb2_dma_contig_plane_dma_addr(vb, 0);

		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_DATA,
				 buf_y_paddr >> 5);

		अगर (!codec_hevc_use_fbc(pixfmt_cap, is_10bit)) अणु
			buf_uv_paddr = vb2_dma_contig_plane_dma_addr(vb, 1);
			amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_DATA,
					 buf_uv_paddr >> 5);
		पूर्ण
	पूर्ण

	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC2AXI_TBL_CONF_ADDR, 1);
	amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_ACCCONFIG_ADDR, 1);
	क्रम (i = 0; i < 32; ++i)
		amvdec_ग_लिखो_करोs(core, HEVCD_MPP_ANC_CANVAS_DATA_ADDR, 0);
पूर्ण

व्योम codec_hevc_मुक्त_fbc_buffers(काष्ठा amvdec_session *sess,
				 काष्ठा codec_hevc_common *comm)
अणु
	काष्ठा device *dev = sess->core->dev;
	u32 am21_size = amvdec_am21c_size(sess->width, sess->height);
	पूर्णांक i;

	क्रम (i = 0; i < MAX_REF_PIC_NUM; ++i) अणु
		अगर (comm->fbc_buffer_vaddr[i]) अणु
			dma_मुक्त_coherent(dev, am21_size,
					  comm->fbc_buffer_vaddr[i],
					  comm->fbc_buffer_paddr[i]);
			comm->fbc_buffer_vaddr[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(codec_hevc_मुक्त_fbc_buffers);

अटल पूर्णांक codec_hevc_alloc_fbc_buffers(काष्ठा amvdec_session *sess,
					काष्ठा codec_hevc_common *comm)
अणु
	काष्ठा device *dev = sess->core->dev;
	काष्ठा v4l2_m2m_buffer *buf;
	u32 am21_size = amvdec_am21c_size(sess->width, sess->height);

	v4l2_m2m_क्रम_each_dst_buf(sess->m2m_ctx, buf) अणु
		u32 idx = buf->vb.vb2_buf.index;
		dma_addr_t paddr;
		व्योम *vaddr = dma_alloc_coherent(dev, am21_size, &paddr,
						 GFP_KERNEL);
		अगर (!vaddr) अणु
			codec_hevc_मुक्त_fbc_buffers(sess, comm);
			वापस -ENOMEM;
		पूर्ण

		comm->fbc_buffer_vaddr[idx] = vaddr;
		comm->fbc_buffer_paddr[idx] = paddr;
	पूर्ण

	वापस 0;
पूर्ण

व्योम codec_hevc_मुक्त_mmu_headers(काष्ठा amvdec_session *sess,
				 काष्ठा codec_hevc_common *comm)
अणु
	काष्ठा device *dev = sess->core->dev;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_REF_PIC_NUM; ++i) अणु
		अगर (comm->mmu_header_vaddr[i]) अणु
			dma_मुक्त_coherent(dev, MMU_COMPRESS_HEADER_SIZE,
					  comm->mmu_header_vaddr[i],
					  comm->mmu_header_paddr[i]);
			comm->mmu_header_vaddr[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (comm->mmu_map_vaddr) अणु
		dma_मुक्त_coherent(dev, MMU_MAP_SIZE,
				  comm->mmu_map_vaddr,
				  comm->mmu_map_paddr);
		comm->mmu_map_vaddr = शून्य;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(codec_hevc_मुक्त_mmu_headers);

अटल पूर्णांक codec_hevc_alloc_mmu_headers(काष्ठा amvdec_session *sess,
					काष्ठा codec_hevc_common *comm)
अणु
	काष्ठा device *dev = sess->core->dev;
	काष्ठा v4l2_m2m_buffer *buf;

	comm->mmu_map_vaddr = dma_alloc_coherent(dev, MMU_MAP_SIZE,
						 &comm->mmu_map_paddr,
						 GFP_KERNEL);
	अगर (!comm->mmu_map_vaddr)
		वापस -ENOMEM;

	v4l2_m2m_क्रम_each_dst_buf(sess->m2m_ctx, buf) अणु
		u32 idx = buf->vb.vb2_buf.index;
		dma_addr_t paddr;
		व्योम *vaddr = dma_alloc_coherent(dev, MMU_COMPRESS_HEADER_SIZE,
						 &paddr, GFP_KERNEL);
		अगर (!vaddr) अणु
			codec_hevc_मुक्त_mmu_headers(sess, comm);
			वापस -ENOMEM;
		पूर्ण

		comm->mmu_header_vaddr[idx] = vaddr;
		comm->mmu_header_paddr[idx] = paddr;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक codec_hevc_setup_buffers(काष्ठा amvdec_session *sess,
			     काष्ठा codec_hevc_common *comm,
			     पूर्णांक is_10bit)
अणु
	काष्ठा amvdec_core *core = sess->core;
	पूर्णांक ret;

	अगर (codec_hevc_use_करोwnsample(sess->pixfmt_cap, is_10bit)) अणु
		ret = codec_hevc_alloc_fbc_buffers(sess, comm);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (codec_hevc_use_mmu(core->platक्रमm->revision,
			       sess->pixfmt_cap, is_10bit)) अणु
		ret = codec_hevc_alloc_mmu_headers(sess, comm);
		अगर (ret) अणु
			codec_hevc_मुक्त_fbc_buffers(sess, comm);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (core->platक्रमm->revision == VDEC_REVISION_GXBB)
		codec_hevc_setup_buffers_gxbb(sess, comm, is_10bit);
	अन्यथा
		codec_hevc_setup_buffers_gxl(sess, comm, is_10bit);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(codec_hevc_setup_buffers);

व्योम codec_hevc_fill_mmu_map(काष्ठा amvdec_session *sess,
			     काष्ठा codec_hevc_common *comm,
			     काष्ठा vb2_buffer *vb)
अणु
	u32 size = amvdec_am21c_size(sess->width, sess->height);
	u32 nb_pages = size / PAGE_SIZE;
	u32 *mmu_map = comm->mmu_map_vaddr;
	u32 first_page;
	u32 i;

	अगर (sess->pixfmt_cap == V4L2_PIX_FMT_NV12M)
		first_page = comm->fbc_buffer_paddr[vb->index] >> PAGE_SHIFT;
	अन्यथा
		first_page = vb2_dma_contig_plane_dma_addr(vb, 0) >> PAGE_SHIFT;

	क्रम (i = 0; i < nb_pages; ++i)
		mmu_map[i] = first_page + i;
पूर्ण
EXPORT_SYMBOL_GPL(codec_hevc_fill_mmu_map);
