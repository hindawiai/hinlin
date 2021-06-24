<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2020 Oracle. All rights reserved.
 */

#समावेश <linux/sunrpc/svc_rdma.h>
#समावेश <linux/sunrpc/rpc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

/**
 * pcl_मुक्त - Release all memory associated with a parsed chunk list
 * @pcl: parsed chunk list
 *
 */
व्योम pcl_मुक्त(काष्ठा svc_rdma_pcl *pcl)
अणु
	जबतक (!list_empty(&pcl->cl_chunks)) अणु
		काष्ठा svc_rdma_chunk *chunk;

		chunk = pcl_first_chunk(pcl);
		list_del(&chunk->ch_list);
		kमुक्त(chunk);
	पूर्ण
पूर्ण

अटल काष्ठा svc_rdma_chunk *pcl_alloc_chunk(u32 segcount, u32 position)
अणु
	काष्ठा svc_rdma_chunk *chunk;

	chunk = kदो_स्मृति(काष्ठा_size(chunk, ch_segments, segcount), GFP_KERNEL);
	अगर (!chunk)
		वापस शून्य;

	chunk->ch_position = position;
	chunk->ch_length = 0;
	chunk->ch_payload_length = 0;
	chunk->ch_segcount = 0;
	वापस chunk;
पूर्ण

अटल काष्ठा svc_rdma_chunk *
pcl_lookup_position(काष्ठा svc_rdma_pcl *pcl, u32 position)
अणु
	काष्ठा svc_rdma_chunk *pos;

	pcl_क्रम_each_chunk(pos, pcl) अणु
		अगर (pos->ch_position == position)
			वापस pos;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम pcl_insert_position(काष्ठा svc_rdma_pcl *pcl,
				काष्ठा svc_rdma_chunk *chunk)
अणु
	काष्ठा svc_rdma_chunk *pos;

	pcl_क्रम_each_chunk(pos, pcl) अणु
		अगर (pos->ch_position > chunk->ch_position)
			अवरोध;
	पूर्ण
	__list_add(&chunk->ch_list, pos->ch_list.prev, &pos->ch_list);
	pcl->cl_count++;
पूर्ण

अटल व्योम pcl_set_पढ़ो_segment(स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
				 काष्ठा svc_rdma_chunk *chunk,
				 u32 handle, u32 length, u64 offset)
अणु
	काष्ठा svc_rdma_segment *segment;

	segment = &chunk->ch_segments[chunk->ch_segcount];
	segment->rs_handle = handle;
	segment->rs_length = length;
	segment->rs_offset = offset;

	trace_svcrdma_decode_rseg(&rctxt->rc_cid, chunk, segment);

	chunk->ch_length += length;
	chunk->ch_segcount++;
पूर्ण

/**
 * pcl_alloc_call - Conकाष्ठा a parsed chunk list क्रम the Call body
 * @rctxt: Ingress receive context
 * @p: Start of an un-decoded Read list
 *
 * Assumptions:
 * - The incoming Read list has alपढ़ोy been sanity checked.
 * - cl_count is alपढ़ोy set to the number of segments in
 *   the un-decoded list.
 * - The list might not be in order by position.
 *
 * Return values:
 *       %true: Parsed chunk list was successfully स्थिरructed, and
 *              cl_count is updated to be the number of chunks (ie.
 *              unique positions) in the Read list.
 *      %false: Memory allocation failed.
 */
bool pcl_alloc_call(काष्ठा svc_rdma_recv_ctxt *rctxt, __be32 *p)
अणु
	काष्ठा svc_rdma_pcl *pcl = &rctxt->rc_call_pcl;
	अचिन्हित पूर्णांक i, segcount = pcl->cl_count;

	pcl->cl_count = 0;
	क्रम (i = 0; i < segcount; i++) अणु
		काष्ठा svc_rdma_chunk *chunk;
		u32 position, handle, length;
		u64 offset;

		p++;	/* skip the list discriminator */
		p = xdr_decode_पढ़ो_segment(p, &position, &handle,
					    &length, &offset);
		अगर (position != 0)
			जारी;

		अगर (pcl_is_empty(pcl)) अणु
			chunk = pcl_alloc_chunk(segcount, position);
			अगर (!chunk)
				वापस false;
			pcl_insert_position(pcl, chunk);
		पूर्ण अन्यथा अणु
			chunk = list_first_entry(&pcl->cl_chunks,
						 काष्ठा svc_rdma_chunk,
						 ch_list);
		पूर्ण

		pcl_set_पढ़ो_segment(rctxt, chunk, handle, length, offset);
	पूर्ण

	वापस true;
पूर्ण

/**
 * pcl_alloc_पढ़ो - Conकाष्ठा a parsed chunk list क्रम normal Read chunks
 * @rctxt: Ingress receive context
 * @p: Start of an un-decoded Read list
 *
 * Assumptions:
 * - The incoming Read list has alपढ़ोy been sanity checked.
 * - cl_count is alपढ़ोy set to the number of segments in
 *   the un-decoded list.
 * - The list might not be in order by position.
 *
 * Return values:
 *       %true: Parsed chunk list was successfully स्थिरructed, and
 *              cl_count is updated to be the number of chunks (ie.
 *              unique position values) in the Read list.
 *      %false: Memory allocation failed.
 *
 * TODO:
 * - Check क्रम chunk range overlaps
 */
bool pcl_alloc_पढ़ो(काष्ठा svc_rdma_recv_ctxt *rctxt, __be32 *p)
अणु
	काष्ठा svc_rdma_pcl *pcl = &rctxt->rc_पढ़ो_pcl;
	अचिन्हित पूर्णांक i, segcount = pcl->cl_count;

	pcl->cl_count = 0;
	क्रम (i = 0; i < segcount; i++) अणु
		काष्ठा svc_rdma_chunk *chunk;
		u32 position, handle, length;
		u64 offset;

		p++;	/* skip the list discriminator */
		p = xdr_decode_पढ़ो_segment(p, &position, &handle,
					    &length, &offset);
		अगर (position == 0)
			जारी;

		chunk = pcl_lookup_position(pcl, position);
		अगर (!chunk) अणु
			chunk = pcl_alloc_chunk(segcount, position);
			अगर (!chunk)
				वापस false;
			pcl_insert_position(pcl, chunk);
		पूर्ण

		pcl_set_पढ़ो_segment(rctxt, chunk, handle, length, offset);
	पूर्ण

	वापस true;
पूर्ण

/**
 * pcl_alloc_ग_लिखो - Conकाष्ठा a parsed chunk list from a Write list
 * @rctxt: Ingress receive context
 * @pcl: Parsed chunk list to populate
 * @p: Start of an un-decoded Write list
 *
 * Assumptions:
 * - The incoming Write list has alपढ़ोy been sanity checked, and
 * - cl_count is set to the number of chunks in the un-decoded list.
 *
 * Return values:
 *       %true: Parsed chunk list was successfully स्थिरructed.
 *      %false: Memory allocation failed.
 */
bool pcl_alloc_ग_लिखो(काष्ठा svc_rdma_recv_ctxt *rctxt,
		     काष्ठा svc_rdma_pcl *pcl, __be32 *p)
अणु
	काष्ठा svc_rdma_segment *segment;
	काष्ठा svc_rdma_chunk *chunk;
	अचिन्हित पूर्णांक i, j;
	u32 segcount;

	क्रम (i = 0; i < pcl->cl_count; i++) अणु
		p++;	/* skip the list discriminator */
		segcount = be32_to_cpup(p++);

		chunk = pcl_alloc_chunk(segcount, 0);
		अगर (!chunk)
			वापस false;
		list_add_tail(&chunk->ch_list, &pcl->cl_chunks);

		क्रम (j = 0; j < segcount; j++) अणु
			segment = &chunk->ch_segments[j];
			p = xdr_decode_rdma_segment(p, &segment->rs_handle,
						    &segment->rs_length,
						    &segment->rs_offset);
			trace_svcrdma_decode_wseg(&rctxt->rc_cid, chunk, j);

			chunk->ch_length += segment->rs_length;
			chunk->ch_segcount++;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक pcl_process_region(स्थिर काष्ठा xdr_buf *xdr,
			      अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length,
			      पूर्णांक (*actor)(स्थिर काष्ठा xdr_buf *, व्योम *),
			      व्योम *data)
अणु
	काष्ठा xdr_buf subbuf;

	अगर (!length)
		वापस 0;
	अगर (xdr_buf_subsegment(xdr, &subbuf, offset, length))
		वापस -EMSGSIZE;
	वापस actor(&subbuf, data);
पूर्ण

/**
 * pcl_process_nonpayloads - Process non-payload regions inside @xdr
 * @pcl: Chunk list to process
 * @xdr: xdr_buf to process
 * @actor: Function to invoke on each non-payload region
 * @data: Arguments क्रम @actor
 *
 * This mechanism must ignore not only result payloads that were alपढ़ोy
 * sent via RDMA Write, but also XDR padding क्रम those payloads that
 * the upper layer has added.
 *
 * Assumptions:
 *  The xdr->len and ch_position fields are aligned to 4-byte multiples.
 *
 * Returns:
 *   On success, zero,
 *   %-EMSGSIZE on XDR buffer overflow, or
 *   The वापस value of @actor
 */
पूर्णांक pcl_process_nonpayloads(स्थिर काष्ठा svc_rdma_pcl *pcl,
			    स्थिर काष्ठा xdr_buf *xdr,
			    पूर्णांक (*actor)(स्थिर काष्ठा xdr_buf *, व्योम *),
			    व्योम *data)
अणु
	काष्ठा svc_rdma_chunk *chunk, *next;
	अचिन्हित पूर्णांक start;
	पूर्णांक ret;

	chunk = pcl_first_chunk(pcl);

	/* No result payloads were generated */
	अगर (!chunk || !chunk->ch_payload_length)
		वापस actor(xdr, data);

	/* Process the region beक्रमe the first result payload */
	ret = pcl_process_region(xdr, 0, chunk->ch_position, actor, data);
	अगर (ret < 0)
		वापस ret;

	/* Process the regions between each middle result payload */
	जबतक ((next = pcl_next_chunk(pcl, chunk))) अणु
		अगर (!next->ch_payload_length)
			अवरोध;

		start = pcl_chunk_end_offset(chunk);
		ret = pcl_process_region(xdr, start, next->ch_position - start,
					 actor, data);
		अगर (ret < 0)
			वापस ret;

		chunk = next;
	पूर्ण

	/* Process the region after the last result payload */
	start = pcl_chunk_end_offset(chunk);
	ret = pcl_process_region(xdr, start, xdr->len - start, actor, data);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण
