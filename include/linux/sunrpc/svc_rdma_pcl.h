<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2020, Oracle and/or its affiliates
 */

#अगर_अघोषित SVC_RDMA_PCL_H
#घोषणा SVC_RDMA_PCL_H

#समावेश <linux/list.h>

काष्ठा svc_rdma_segment अणु
	u32			rs_handle;
	u32			rs_length;
	u64			rs_offset;
पूर्ण;

काष्ठा svc_rdma_chunk अणु
	काष्ठा list_head	ch_list;

	u32			ch_position;
	u32			ch_length;
	u32			ch_payload_length;

	u32			ch_segcount;
	काष्ठा svc_rdma_segment	ch_segments[];
पूर्ण;

काष्ठा svc_rdma_pcl अणु
	अचिन्हित पूर्णांक		cl_count;
	काष्ठा list_head	cl_chunks;
पूर्ण;

/**
 * pcl_init - Initialize a parsed chunk list
 * @pcl: parsed chunk list to initialize
 *
 */
अटल अंतरभूत व्योम pcl_init(काष्ठा svc_rdma_pcl *pcl)
अणु
	INIT_LIST_HEAD(&pcl->cl_chunks);
पूर्ण

/**
 * pcl_is_empty - Return true अगर parsed chunk list is empty
 * @pcl: parsed chunk list
 *
 */
अटल अंतरभूत bool pcl_is_empty(स्थिर काष्ठा svc_rdma_pcl *pcl)
अणु
	वापस list_empty(&pcl->cl_chunks);
पूर्ण

/**
 * pcl_first_chunk - Return first chunk in a parsed chunk list
 * @pcl: parsed chunk list
 *
 * Returns the first chunk in the list, or शून्य अगर the list is empty.
 */
अटल अंतरभूत काष्ठा svc_rdma_chunk *
pcl_first_chunk(स्थिर काष्ठा svc_rdma_pcl *pcl)
अणु
	अगर (pcl_is_empty(pcl))
		वापस शून्य;
	वापस list_first_entry(&pcl->cl_chunks, काष्ठा svc_rdma_chunk,
				ch_list);
पूर्ण

/**
 * pcl_next_chunk - Return next chunk in a parsed chunk list
 * @pcl: a parsed chunk list
 * @chunk: chunk in @pcl
 *
 * Returns the next chunk in the list, or शून्य अगर @chunk is alपढ़ोy last.
 */
अटल अंतरभूत काष्ठा svc_rdma_chunk *
pcl_next_chunk(स्थिर काष्ठा svc_rdma_pcl *pcl, काष्ठा svc_rdma_chunk *chunk)
अणु
	अगर (list_is_last(&chunk->ch_list, &pcl->cl_chunks))
		वापस शून्य;
	वापस list_next_entry(chunk, ch_list);
पूर्ण

/**
 * pcl_क्रम_each_chunk - Iterate over chunks in a parsed chunk list
 * @pos: the loop cursor
 * @pcl: a parsed chunk list
 */
#घोषणा pcl_क्रम_each_chunk(pos, pcl) \
	क्रम (pos = list_first_entry(&(pcl)->cl_chunks, काष्ठा svc_rdma_chunk, ch_list); \
	     &pos->ch_list != &(pcl)->cl_chunks; \
	     pos = list_next_entry(pos, ch_list))

/**
 * pcl_क्रम_each_segment - Iterate over segments in a parsed chunk
 * @pos: the loop cursor
 * @chunk: a parsed chunk
 */
#घोषणा pcl_क्रम_each_segment(pos, chunk) \
	क्रम (pos = &(chunk)->ch_segments[0]; \
	     pos <= &(chunk)->ch_segments[(chunk)->ch_segcount - 1]; \
	     pos++)

/**
 * pcl_chunk_end_offset - Return offset of byte range following @chunk
 * @chunk: chunk in @pcl
 *
 * Returns starting offset of the region just after @chunk
 */
अटल अंतरभूत अचिन्हित पूर्णांक
pcl_chunk_end_offset(स्थिर काष्ठा svc_rdma_chunk *chunk)
अणु
	वापस xdr_align_size(chunk->ch_position + chunk->ch_payload_length);
पूर्ण

काष्ठा svc_rdma_recv_ctxt;

बाह्य व्योम pcl_मुक्त(काष्ठा svc_rdma_pcl *pcl);
बाह्य bool pcl_alloc_call(काष्ठा svc_rdma_recv_ctxt *rctxt, __be32 *p);
बाह्य bool pcl_alloc_पढ़ो(काष्ठा svc_rdma_recv_ctxt *rctxt, __be32 *p);
बाह्य bool pcl_alloc_ग_लिखो(काष्ठा svc_rdma_recv_ctxt *rctxt,
			    काष्ठा svc_rdma_pcl *pcl, __be32 *p);
बाह्य पूर्णांक pcl_process_nonpayloads(स्थिर काष्ठा svc_rdma_pcl *pcl,
				   स्थिर काष्ठा xdr_buf *xdr,
				   पूर्णांक (*actor)(स्थिर काष्ठा xdr_buf *,
						व्योम *),
				   व्योम *data);

#पूर्ण_अगर	/* SVC_RDMA_PCL_H */
