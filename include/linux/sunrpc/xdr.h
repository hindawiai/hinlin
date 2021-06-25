<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * XDR standard data types and function declarations
 *
 * Copyright (C) 1995-1997 Olaf Kirch <okir@monad.swb.de>
 *
 * Based on:
 *   RFC 4506 "XDR: External Data Representation Standard", May 2006
 */

#अगर_अघोषित _SUNRPC_XDR_H_
#घोषणा _SUNRPC_XDR_H_

#समावेश <linux/uपन.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/scatterlist.h>

काष्ठा bio_vec;
काष्ठा rpc_rqst;

/*
 * Size of an XDR encoding unit in bytes, i.e. 32 bits,
 * as defined in Section 3 of RFC 4506. All encoded
 * XDR data items are aligned on a boundary of 32 bits.
 */
#घोषणा XDR_UNIT		माप(__be32)

/*
 * Buffer adjusपंचांगent
 */
#घोषणा XDR_QUADLEN(l)		(((l) + 3) >> 2)

/*
 * Generic opaque `network object.'
 */
#घोषणा XDR_MAX_NETOBJ		1024
काष्ठा xdr_netobj अणु
	अचिन्हित पूर्णांक		len;
	u8 *			data;
पूर्ण;

/*
 * Basic काष्ठाure क्रम transmission/reception of a client XDR message.
 * Features a header (क्रम a linear buffer containing RPC headers
 * and the data payload क्रम लघु messages), and then an array of
 * pages.
 * The tail iovec allows you to append data after the page array. Its
 * मुख्य पूर्णांकerest is क्रम appending padding to the pages in order to
 * satisfy the पूर्णांक_32-alignment requirements in RFC1832.
 *
 * For the future, we might want to string several of these together
 * in a list अगर anybody wants to make use of NFSv4 COMPOUND
 * operations and/or has a need क्रम scatter/gather involving pages.
 */
काष्ठा xdr_buf अणु
	काष्ठा kvec	head[1],	/* RPC header + non-page data */
			tail[1];	/* Appended after page data */

	काष्ठा bio_vec	*bvec;
	काष्ठा page **	pages;		/* Array of pages */
	अचिन्हित पूर्णांक	page_base,	/* Start of page data */
			page_len,	/* Length of page data */
			flags;		/* Flags क्रम data disposition */
#घोषणा XDRBUF_READ		0x01		/* target of file पढ़ो */
#घोषणा XDRBUF_WRITE		0x02		/* source of file ग_लिखो */
#घोषणा XDRBUF_SPARSE_PAGES	0x04		/* Page array is sparse */

	अचिन्हित पूर्णांक	buflen,		/* Total length of storage buffer */
			len;		/* Length of XDR encoded message */
पूर्ण;

अटल अंतरभूत व्योम
xdr_buf_init(काष्ठा xdr_buf *buf, व्योम *start, माप_प्रकार len)
अणु
	buf->head[0].iov_base = start;
	buf->head[0].iov_len = len;
	buf->tail[0].iov_len = 0;
	buf->pages = शून्य;
	buf->page_len = 0;
	buf->flags = 0;
	buf->len = 0;
	buf->buflen = len;
पूर्ण

/*
 * pre-xdr'ed macros.
 */

#घोषणा	xdr_zero	cpu_to_be32(0)
#घोषणा	xdr_one		cpu_to_be32(1)
#घोषणा	xdr_two		cpu_to_be32(2)

#घोषणा	rpc_auth_null	cpu_to_be32(RPC_AUTH_शून्य)
#घोषणा	rpc_auth_unix	cpu_to_be32(RPC_AUTH_UNIX)
#घोषणा	rpc_auth_लघु	cpu_to_be32(RPC_AUTH_SHORT)
#घोषणा	rpc_auth_gss	cpu_to_be32(RPC_AUTH_GSS)

#घोषणा	rpc_call	cpu_to_be32(RPC_CALL)
#घोषणा	rpc_reply	cpu_to_be32(RPC_REPLY)

#घोषणा	rpc_msg_accepted	cpu_to_be32(RPC_MSG_ACCEPTED)

#घोषणा	rpc_success		cpu_to_be32(RPC_SUCCESS)
#घोषणा	rpc_prog_unavail	cpu_to_be32(RPC_PROG_UNAVAIL)
#घोषणा	rpc_prog_mismatch	cpu_to_be32(RPC_PROG_MISMATCH)
#घोषणा	rpc_proc_unavail	cpu_to_be32(RPC_PROC_UNAVAIL)
#घोषणा	rpc_garbage_args	cpu_to_be32(RPC_GARBAGE_ARGS)
#घोषणा	rpc_प्रणाली_err		cpu_to_be32(RPC_SYSTEM_ERR)
#घोषणा	rpc_drop_reply		cpu_to_be32(RPC_DROP_REPLY)

#घोषणा	rpc_mismatch		cpu_to_be32(RPC_MISMATCH)
#घोषणा	rpc_auth_error		cpu_to_be32(RPC_AUTH_ERROR)

#घोषणा	rpc_auth_ok		cpu_to_be32(RPC_AUTH_OK)
#घोषणा	rpc_autherr_badcred	cpu_to_be32(RPC_AUTH_BADCRED)
#घोषणा	rpc_autherr_rejectedcred cpu_to_be32(RPC_AUTH_REJECTEDCRED)
#घोषणा	rpc_autherr_badverf	cpu_to_be32(RPC_AUTH_BADVERF)
#घोषणा	rpc_autherr_rejectedverf cpu_to_be32(RPC_AUTH_REJECTEDVERF)
#घोषणा	rpc_autherr_tooweak	cpu_to_be32(RPC_AUTH_TOOWEAK)
#घोषणा	rpcsec_gsserr_credproblem	cpu_to_be32(RPCSEC_GSS_CREDPROBLEM)
#घोषणा	rpcsec_gsserr_ctxproblem	cpu_to_be32(RPCSEC_GSS_CTXPROBLEM)

/*
 * Miscellaneous XDR helper functions
 */
__be32 *xdr_encode_opaque_fixed(__be32 *p, स्थिर व्योम *ptr, अचिन्हित पूर्णांक len);
__be32 *xdr_encode_opaque(__be32 *p, स्थिर व्योम *ptr, अचिन्हित पूर्णांक len);
__be32 *xdr_encode_string(__be32 *p, स्थिर अक्षर *s);
__be32 *xdr_decode_string_inplace(__be32 *p, अक्षर **sp, अचिन्हित पूर्णांक *lenp,
			अचिन्हित पूर्णांक maxlen);
__be32 *xdr_encode_netobj(__be32 *p, स्थिर काष्ठा xdr_netobj *);
__be32 *xdr_decode_netobj(__be32 *p, काष्ठा xdr_netobj *);

व्योम	xdr_अंतरभूत_pages(काष्ठा xdr_buf *, अचिन्हित पूर्णांक,
			 काष्ठा page **, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
व्योम	xdr_terminate_string(स्थिर काष्ठा xdr_buf *, स्थिर u32);
माप_प्रकार	xdr_buf_pagecount(स्थिर काष्ठा xdr_buf *buf);
पूर्णांक	xdr_alloc_bvec(काष्ठा xdr_buf *buf, gfp_t gfp);
व्योम	xdr_मुक्त_bvec(काष्ठा xdr_buf *buf);

अटल अंतरभूत __be32 *xdr_encode_array(__be32 *p, स्थिर व्योम *s, अचिन्हित पूर्णांक len)
अणु
	वापस xdr_encode_opaque(p, s, len);
पूर्ण

/*
 * Decode 64bit quantities (NFSv3 support)
 */
अटल अंतरभूत __be32 *
xdr_encode_hyper(__be32 *p, __u64 val)
अणु
	put_unaligned_be64(val, p);
	वापस p + 2;
पूर्ण

अटल अंतरभूत __be32 *
xdr_decode_hyper(__be32 *p, __u64 *valp)
अणु
	*valp = get_unaligned_be64(p);
	वापस p + 2;
पूर्ण

अटल अंतरभूत __be32 *
xdr_decode_opaque_fixed(__be32 *p, व्योम *ptr, अचिन्हित पूर्णांक len)
अणु
	स_नकल(ptr, p, len);
	वापस p + XDR_QUADLEN(len);
पूर्ण

अटल अंतरभूत व्योम xdr_netobj_dup(काष्ठा xdr_netobj *dst,
				  काष्ठा xdr_netobj *src, gfp_t gfp_mask)
अणु
	dst->data = kmemdup(src->data, src->len, gfp_mask);
	dst->len = src->len;
पूर्ण

/*
 * Adjust kvec to reflect end of xdr'ed data (RPC client XDR)
 */
अटल अंतरभूत पूर्णांक
xdr_adjust_iovec(काष्ठा kvec *iov, __be32 *p)
अणु
	वापस iov->iov_len = ((u8 *) p - (u8 *) iov->iov_base);
पूर्ण

/*
 * XDR buffer helper functions
 */
बाह्य व्योम xdr_shअगरt_buf(काष्ठा xdr_buf *, माप_प्रकार);
बाह्य व्योम xdr_buf_from_iov(स्थिर काष्ठा kvec *, काष्ठा xdr_buf *);
बाह्य पूर्णांक xdr_buf_subsegment(स्थिर काष्ठा xdr_buf *, काष्ठा xdr_buf *, अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);
बाह्य व्योम xdr_buf_trim(काष्ठा xdr_buf *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक पढ़ो_bytes_from_xdr_buf(स्थिर काष्ठा xdr_buf *, अचिन्हित पूर्णांक, व्योम *, अचिन्हित पूर्णांक);
बाह्य पूर्णांक ग_लिखो_bytes_to_xdr_buf(स्थिर काष्ठा xdr_buf *, अचिन्हित पूर्णांक, व्योम *, अचिन्हित पूर्णांक);

बाह्य पूर्णांक xdr_encode_word(स्थिर काष्ठा xdr_buf *, अचिन्हित पूर्णांक, u32);
बाह्य पूर्णांक xdr_decode_word(स्थिर काष्ठा xdr_buf *, अचिन्हित पूर्णांक, u32 *);

काष्ठा xdr_array2_desc;
प्रकार पूर्णांक (*xdr_xcode_elem_t)(काष्ठा xdr_array2_desc *desc, व्योम *elem);
काष्ठा xdr_array2_desc अणु
	अचिन्हित पूर्णांक elem_size;
	अचिन्हित पूर्णांक array_len;
	अचिन्हित पूर्णांक array_maxlen;
	xdr_xcode_elem_t xcode;
पूर्ण;

बाह्य पूर्णांक xdr_decode_array2(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
			     काष्ठा xdr_array2_desc *desc);
बाह्य पूर्णांक xdr_encode_array2(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक base,
			     काष्ठा xdr_array2_desc *desc);
बाह्य व्योम _copy_from_pages(अक्षर *p, काष्ठा page **pages, माप_प्रकार pgbase,
			     माप_प्रकार len);

/*
 * Provide some simple tools क्रम XDR buffer overflow-checking etc.
 */
काष्ठा xdr_stream अणु
	__be32 *p;		/* start of available buffer */
	काष्ठा xdr_buf *buf;	/* XDR buffer to पढ़ो/ग_लिखो */

	__be32 *end;		/* end of available buffer space */
	काष्ठा kvec *iov;	/* poपूर्णांकer to the current kvec */
	काष्ठा kvec scratch;	/* Scratch buffer */
	काष्ठा page **page_ptr;	/* poपूर्णांकer to the current page */
	अचिन्हित पूर्णांक nwords;	/* Reमुख्यing decode buffer length */

	काष्ठा rpc_rqst *rqst;	/* For debugging */
पूर्ण;

/*
 * These are the xdr_stream style generic XDR encode and decode functions.
 */
प्रकार व्योम	(*kxdreproc_t)(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		स्थिर व्योम *obj);
प्रकार पूर्णांक	(*kxdrdproc_t)(काष्ठा rpc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		व्योम *obj);

बाह्य व्योम xdr_init_encode(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *buf,
			    __be32 *p, काष्ठा rpc_rqst *rqst);
बाह्य __be32 *xdr_reserve_space(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes);
बाह्य पूर्णांक xdr_reserve_space_vec(काष्ठा xdr_stream *xdr, काष्ठा kvec *vec,
		माप_प्रकार nbytes);
बाह्य व्योम xdr_commit_encode(काष्ठा xdr_stream *xdr);
बाह्य व्योम xdr_truncate_encode(काष्ठा xdr_stream *xdr, माप_प्रकार len);
बाह्य पूर्णांक xdr_restrict_buflen(काष्ठा xdr_stream *xdr, पूर्णांक newbuflen);
बाह्य व्योम xdr_ग_लिखो_pages(काष्ठा xdr_stream *xdr, काष्ठा page **pages,
		अचिन्हित पूर्णांक base, अचिन्हित पूर्णांक len);
बाह्य अचिन्हित पूर्णांक xdr_stream_pos(स्थिर काष्ठा xdr_stream *xdr);
बाह्य अचिन्हित पूर्णांक xdr_page_pos(स्थिर काष्ठा xdr_stream *xdr);
बाह्य व्योम xdr_init_decode(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *buf,
			    __be32 *p, काष्ठा rpc_rqst *rqst);
बाह्य व्योम xdr_init_decode_pages(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *buf,
		काष्ठा page **pages, अचिन्हित पूर्णांक len);
बाह्य __be32 *xdr_अंतरभूत_decode(काष्ठा xdr_stream *xdr, माप_प्रकार nbytes);
बाह्य अचिन्हित पूर्णांक xdr_पढ़ो_pages(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len);
बाह्य व्योम xdr_enter_page(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len);
बाह्य पूर्णांक xdr_process_buf(स्थिर काष्ठा xdr_buf *buf, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक len, पूर्णांक (*actor)(काष्ठा scatterlist *, व्योम *), व्योम *data);
बाह्य अचिन्हित पूर्णांक xdr_align_data(काष्ठा xdr_stream *, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length);
बाह्य अचिन्हित पूर्णांक xdr_expand_hole(काष्ठा xdr_stream *, अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length);
बाह्य bool xdr_stream_subsegment(काष्ठा xdr_stream *xdr, काष्ठा xdr_buf *subbuf,
				  अचिन्हित पूर्णांक len);

/**
 * xdr_set_scratch_buffer - Attach a scratch buffer क्रम decoding data.
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @buf: poपूर्णांकer to an empty buffer
 * @buflen: size of 'buf'
 *
 * The scratch buffer is used when decoding from an array of pages.
 * If an xdr_अंतरभूत_decode() call spans across page boundaries, then
 * we copy the data पूर्णांकo the scratch buffer in order to allow linear
 * access.
 */
अटल अंतरभूत व्योम
xdr_set_scratch_buffer(काष्ठा xdr_stream *xdr, व्योम *buf, माप_प्रकार buflen)
अणु
	xdr->scratch.iov_base = buf;
	xdr->scratch.iov_len = buflen;
पूर्ण

/**
 * xdr_set_scratch_page - Attach a scratch buffer क्रम decoding data
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 * @page: an anonymous page
 *
 * See xdr_set_scratch_buffer().
 */
अटल अंतरभूत व्योम
xdr_set_scratch_page(काष्ठा xdr_stream *xdr, काष्ठा page *page)
अणु
	xdr_set_scratch_buffer(xdr, page_address(page), PAGE_SIZE);
पूर्ण

/**
 * xdr_reset_scratch_buffer - Clear scratch buffer inक्रमmation
 * @xdr: poपूर्णांकer to xdr_stream काष्ठा
 *
 * See xdr_set_scratch_buffer().
 */
अटल अंतरभूत व्योम
xdr_reset_scratch_buffer(काष्ठा xdr_stream *xdr)
अणु
	xdr_set_scratch_buffer(xdr, शून्य, 0);
पूर्ण

/**
 * xdr_stream_reमुख्यing - Return the number of bytes reमुख्यing in the stream
 * @xdr: poपूर्णांकer to काष्ठा xdr_stream
 *
 * Return value:
 *   Number of bytes reमुख्यing in @xdr beक्रमe xdr->end
 */
अटल अंतरभूत माप_प्रकार
xdr_stream_reमुख्यing(स्थिर काष्ठा xdr_stream *xdr)
अणु
	वापस xdr->nwords << 2;
पूर्ण

sमाप_प्रकार xdr_stream_decode_opaque(काष्ठा xdr_stream *xdr, व्योम *ptr,
		माप_प्रकार size);
sमाप_प्रकार xdr_stream_decode_opaque_dup(काष्ठा xdr_stream *xdr, व्योम **ptr,
		माप_प्रकार maxlen, gfp_t gfp_flags);
sमाप_प्रकार xdr_stream_decode_string(काष्ठा xdr_stream *xdr, अक्षर *str,
		माप_प्रकार size);
sमाप_प्रकार xdr_stream_decode_string_dup(काष्ठा xdr_stream *xdr, अक्षर **str,
		माप_प्रकार maxlen, gfp_t gfp_flags);
/**
 * xdr_align_size - Calculate padded size of an object
 * @n: Size of an object being XDR encoded (in bytes)
 *
 * Return value:
 *   Size (in bytes) of the object including xdr padding
 */
अटल अंतरभूत माप_प्रकार
xdr_align_size(माप_प्रकार n)
अणु
	स्थिर माप_प्रकार mask = XDR_UNIT - 1;

	वापस (n + mask) & ~mask;
पूर्ण

/**
 * xdr_pad_size - Calculate size of an object's pad
 * @n: Size of an object being XDR encoded (in bytes)
 *
 * This implementation aव्योमs the need क्रम conditional
 * branches or modulo भागision.
 *
 * Return value:
 *   Size (in bytes) of the needed XDR pad
 */
अटल अंतरभूत माप_प्रकार xdr_pad_size(माप_प्रकार n)
अणु
	वापस xdr_align_size(n) - n;
पूर्ण

/**
 * xdr_stream_encode_item_present - Encode a "present" list item
 * @xdr: poपूर्णांकer to xdr_stream
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार xdr_stream_encode_item_present(काष्ठा xdr_stream *xdr)
अणु
	स्थिर माप_प्रकार len = XDR_UNIT;
	__be32 *p = xdr_reserve_space(xdr, len);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	*p = xdr_one;
	वापस len;
पूर्ण

/**
 * xdr_stream_encode_item_असलent - Encode a "not present" list item
 * @xdr: poपूर्णांकer to xdr_stream
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत पूर्णांक xdr_stream_encode_item_असलent(काष्ठा xdr_stream *xdr)
अणु
	स्थिर माप_प्रकार len = XDR_UNIT;
	__be32 *p = xdr_reserve_space(xdr, len);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	*p = xdr_zero;
	वापस len;
पूर्ण

/**
 * xdr_encode_bool - Encode a boolean item
 * @p: address in a buffer पूर्णांकo which to encode
 * @n: boolean value to encode
 *
 * Return value:
 *   Address of item following the encoded boolean
 */
अटल अंतरभूत __be32 *xdr_encode_bool(__be32 *p, u32 n)
अणु
	*p = n ? xdr_one : xdr_zero;
	वापस p++;
पूर्ण

/**
 * xdr_stream_encode_bool - Encode a boolean item
 * @xdr: poपूर्णांकer to xdr_stream
 * @n: boolean value to encode
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत पूर्णांक xdr_stream_encode_bool(काष्ठा xdr_stream *xdr, __u32 n)
अणु
	स्थिर माप_प्रकार len = XDR_UNIT;
	__be32 *p = xdr_reserve_space(xdr, len);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	xdr_encode_bool(p, n);
	वापस len;
पूर्ण

/**
 * xdr_stream_encode_u32 - Encode a 32-bit पूर्णांकeger
 * @xdr: poपूर्णांकer to xdr_stream
 * @n: पूर्णांकeger to encode
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_encode_u32(काष्ठा xdr_stream *xdr, __u32 n)
अणु
	स्थिर माप_प्रकार len = माप(n);
	__be32 *p = xdr_reserve_space(xdr, len);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	*p = cpu_to_be32(n);
	वापस len;
पूर्ण

/**
 * xdr_stream_encode_u64 - Encode a 64-bit पूर्णांकeger
 * @xdr: poपूर्णांकer to xdr_stream
 * @n: 64-bit पूर्णांकeger to encode
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_encode_u64(काष्ठा xdr_stream *xdr, __u64 n)
अणु
	स्थिर माप_प्रकार len = माप(n);
	__be32 *p = xdr_reserve_space(xdr, len);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	xdr_encode_hyper(p, n);
	वापस len;
पूर्ण

/**
 * xdr_stream_encode_opaque_अंतरभूत - Encode opaque xdr data
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: poपूर्णांकer to व्योम poपूर्णांकer
 * @len: size of object
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_encode_opaque_अंतरभूत(काष्ठा xdr_stream *xdr, व्योम **ptr, माप_प्रकार len)
अणु
	माप_प्रकार count = माप(__u32) + xdr_align_size(len);
	__be32 *p = xdr_reserve_space(xdr, count);

	अगर (unlikely(!p)) अणु
		*ptr = शून्य;
		वापस -EMSGSIZE;
	पूर्ण
	xdr_encode_opaque(p, शून्य, len);
	*ptr = ++p;
	वापस count;
पूर्ण

/**
 * xdr_stream_encode_opaque_fixed - Encode fixed length opaque xdr data
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: poपूर्णांकer to opaque data object
 * @len: size of object poपूर्णांकed to by @ptr
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_encode_opaque_fixed(काष्ठा xdr_stream *xdr, स्थिर व्योम *ptr, माप_प्रकार len)
अणु
	__be32 *p = xdr_reserve_space(xdr, len);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	xdr_encode_opaque_fixed(p, ptr, len);
	वापस xdr_align_size(len);
पूर्ण

/**
 * xdr_stream_encode_opaque - Encode variable length opaque xdr data
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: poपूर्णांकer to opaque data object
 * @len: size of object poपूर्णांकed to by @ptr
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_encode_opaque(काष्ठा xdr_stream *xdr, स्थिर व्योम *ptr, माप_प्रकार len)
अणु
	माप_प्रकार count = माप(__u32) + xdr_align_size(len);
	__be32 *p = xdr_reserve_space(xdr, count);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	xdr_encode_opaque(p, ptr, len);
	वापस count;
पूर्ण

/**
 * xdr_stream_encode_uपूर्णांक32_array - Encode variable length array of पूर्णांकegers
 * @xdr: poपूर्णांकer to xdr_stream
 * @array: array of पूर्णांकegers
 * @array_size: number of elements in @array
 *
 * Return values:
 *   On success, वापसs length in bytes of XDR buffer consumed
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_encode_uपूर्णांक32_array(काष्ठा xdr_stream *xdr,
		स्थिर __u32 *array, माप_प्रकार array_size)
अणु
	sमाप_प्रकार ret = (array_size+1) * माप(__u32);
	__be32 *p = xdr_reserve_space(xdr, ret);

	अगर (unlikely(!p))
		वापस -EMSGSIZE;
	*p++ = cpu_to_be32(array_size);
	क्रम (; array_size > 0; p++, array++, array_size--)
		*p = cpu_to_be32p(array);
	वापस ret;
पूर्ण

/**
 * xdr_item_is_असलent - symbolically handle XDR discriminators
 * @p: poपूर्णांकer to undecoded discriminator
 *
 * Return values:
 *   %true अगर the following XDR item is असलent
 *   %false अगर the following XDR item is present
 */
अटल अंतरभूत bool xdr_item_is_असलent(स्थिर __be32 *p)
अणु
	वापस *p == xdr_zero;
पूर्ण

/**
 * xdr_item_is_present - symbolically handle XDR discriminators
 * @p: poपूर्णांकer to undecoded discriminator
 *
 * Return values:
 *   %true अगर the following XDR item is present
 *   %false अगर the following XDR item is असलent
 */
अटल अंतरभूत bool xdr_item_is_present(स्थिर __be32 *p)
अणु
	वापस *p != xdr_zero;
पूर्ण

/**
 * xdr_stream_decode_bool - Decode a boolean
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: poपूर्णांकer to a u32 in which to store the result
 *
 * Return values:
 *   %0 on success
 *   %-EBADMSG on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_decode_bool(काष्ठा xdr_stream *xdr, __u32 *ptr)
अणु
	स्थिर माप_प्रकार count = माप(*ptr);
	__be32 *p = xdr_अंतरभूत_decode(xdr, count);

	अगर (unlikely(!p))
		वापस -EBADMSG;
	*ptr = (*p != xdr_zero);
	वापस 0;
पूर्ण

/**
 * xdr_stream_decode_u32 - Decode a 32-bit पूर्णांकeger
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: location to store पूर्णांकeger
 *
 * Return values:
 *   %0 on success
 *   %-EBADMSG on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_decode_u32(काष्ठा xdr_stream *xdr, __u32 *ptr)
अणु
	स्थिर माप_प्रकार count = माप(*ptr);
	__be32 *p = xdr_अंतरभूत_decode(xdr, count);

	अगर (unlikely(!p))
		वापस -EBADMSG;
	*ptr = be32_to_cpup(p);
	वापस 0;
पूर्ण

/**
 * xdr_stream_decode_u64 - Decode a 64-bit पूर्णांकeger
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: location to store 64-bit पूर्णांकeger
 *
 * Return values:
 *   %0 on success
 *   %-EBADMSG on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_decode_u64(काष्ठा xdr_stream *xdr, __u64 *ptr)
अणु
	स्थिर माप_प्रकार count = माप(*ptr);
	__be32 *p = xdr_अंतरभूत_decode(xdr, count);

	अगर (unlikely(!p))
		वापस -EBADMSG;
	xdr_decode_hyper(p, ptr);
	वापस 0;
पूर्ण

/**
 * xdr_stream_decode_opaque_fixed - Decode fixed length opaque xdr data
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: location to store data
 * @len: size of buffer poपूर्णांकed to by @ptr
 *
 * Return values:
 *   On success, वापसs size of object stored in @ptr
 *   %-EBADMSG on XDR buffer overflow
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_decode_opaque_fixed(काष्ठा xdr_stream *xdr, व्योम *ptr, माप_प्रकार len)
अणु
	__be32 *p = xdr_अंतरभूत_decode(xdr, len);

	अगर (unlikely(!p))
		वापस -EBADMSG;
	xdr_decode_opaque_fixed(p, ptr, len);
	वापस len;
पूर्ण

/**
 * xdr_stream_decode_opaque_अंतरभूत - Decode variable length opaque xdr data
 * @xdr: poपूर्णांकer to xdr_stream
 * @ptr: location to store poपूर्णांकer to opaque data
 * @maxlen: maximum acceptable object size
 *
 * Note: the poपूर्णांकer stored in @ptr cannot be assumed valid after the XDR
 * buffer has been destroyed, or even after calling xdr_अंतरभूत_decode()
 * on @xdr. It is thereक्रमe expected that the object it poपूर्णांकs to should
 * be processed immediately.
 *
 * Return values:
 *   On success, वापसs size of object stored in *@ptr
 *   %-EBADMSG on XDR buffer overflow
 *   %-EMSGSIZE अगर the size of the object would exceed @maxlen
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_decode_opaque_अंतरभूत(काष्ठा xdr_stream *xdr, व्योम **ptr, माप_प्रकार maxlen)
अणु
	__be32 *p;
	__u32 len;

	*ptr = शून्य;
	अगर (unlikely(xdr_stream_decode_u32(xdr, &len) < 0))
		वापस -EBADMSG;
	अगर (len != 0) अणु
		p = xdr_अंतरभूत_decode(xdr, len);
		अगर (unlikely(!p))
			वापस -EBADMSG;
		अगर (unlikely(len > maxlen))
			वापस -EMSGSIZE;
		*ptr = p;
	पूर्ण
	वापस len;
पूर्ण

/**
 * xdr_stream_decode_uपूर्णांक32_array - Decode variable length array of पूर्णांकegers
 * @xdr: poपूर्णांकer to xdr_stream
 * @array: location to store the पूर्णांकeger array or शून्य
 * @array_size: number of elements to store
 *
 * Return values:
 *   On success, वापसs number of elements stored in @array
 *   %-EBADMSG on XDR buffer overflow
 *   %-EMSGSIZE अगर the size of the array exceeds @array_size
 */
अटल अंतरभूत sमाप_प्रकार
xdr_stream_decode_uपूर्णांक32_array(काष्ठा xdr_stream *xdr,
		__u32 *array, माप_प्रकार array_size)
अणु
	__be32 *p;
	__u32 len;
	sमाप_प्रकार retval;

	अगर (unlikely(xdr_stream_decode_u32(xdr, &len) < 0))
		वापस -EBADMSG;
	p = xdr_अंतरभूत_decode(xdr, len * माप(*p));
	अगर (unlikely(!p))
		वापस -EBADMSG;
	अगर (array == शून्य)
		वापस len;
	अगर (len <= array_size) अणु
		अगर (len < array_size)
			स_रखो(array+len, 0, (array_size-len)*माप(*array));
		array_size = len;
		retval = len;
	पूर्ण अन्यथा
		retval = -EMSGSIZE;
	क्रम (; array_size > 0; p++, array++, array_size--)
		*array = be32_to_cpup(p);
	वापस retval;
पूर्ण

#पूर्ण_अगर /* _SUNRPC_XDR_H_ */
