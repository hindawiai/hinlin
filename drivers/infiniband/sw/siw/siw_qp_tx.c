<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 or BSD-3-Clause

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>
#समावेश <linux/net.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/highस्मृति.स>
#समावेश <net/tcp.h>

#समावेश <rdma/iw_cm.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/ib_user_verbs.h>

#समावेश "siw.h"
#समावेश "siw_verbs.h"
#समावेश "siw_mem.h"

#घोषणा MAX_HDR_INLINE					\
	(((uपूर्णांक32_t)(माप(काष्ठा siw_rreq_pkt) -	\
		     माप(काष्ठा iwarp_send))) & 0xF8)

अटल काष्ठा page *siw_get_pblpage(काष्ठा siw_mem *mem, u64 addr, पूर्णांक *idx)
अणु
	काष्ठा siw_pbl *pbl = mem->pbl;
	u64 offset = addr - mem->va;
	dma_addr_t paddr = siw_pbl_get_buffer(pbl, offset, शून्य, idx);

	अगर (paddr)
		वापस virt_to_page(paddr);

	वापस शून्य;
पूर्ण

/*
 * Copy लघु payload at provided destination payload address
 */
अटल पूर्णांक siw_try_1seg(काष्ठा siw_iwarp_tx *c_tx, व्योम *paddr)
अणु
	काष्ठा siw_wqe *wqe = &c_tx->wqe_active;
	काष्ठा siw_sge *sge = &wqe->sqe.sge[0];
	u32 bytes = sge->length;

	अगर (bytes > MAX_HDR_INLINE || wqe->sqe.num_sge != 1)
		वापस MAX_HDR_INLINE + 1;

	अगर (!bytes)
		वापस 0;

	अगर (tx_flags(wqe) & SIW_WQE_INLINE) अणु
		स_नकल(paddr, &wqe->sqe.sge[1], bytes);
	पूर्ण अन्यथा अणु
		काष्ठा siw_mem *mem = wqe->mem[0];

		अगर (!mem->mem_obj) अणु
			/* Kernel client using kva */
			स_नकल(paddr,
			       (स्थिर व्योम *)(uपूर्णांकptr_t)sge->laddr, bytes);
		पूर्ण अन्यथा अगर (c_tx->in_syscall) अणु
			अगर (copy_from_user(paddr, u64_to_user_ptr(sge->laddr),
					   bytes))
				वापस -EFAULT;
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक off = sge->laddr & ~PAGE_MASK;
			काष्ठा page *p;
			अक्षर *buffer;
			पूर्णांक pbl_idx = 0;

			अगर (!mem->is_pbl)
				p = siw_get_upage(mem->umem, sge->laddr);
			अन्यथा
				p = siw_get_pblpage(mem, sge->laddr, &pbl_idx);

			अगर (unlikely(!p))
				वापस -EFAULT;

			buffer = kmap(p);

			अगर (likely(PAGE_SIZE - off >= bytes)) अणु
				स_नकल(paddr, buffer + off, bytes);
			पूर्ण अन्यथा अणु
				अचिन्हित दीर्घ part = bytes - (PAGE_SIZE - off);

				स_नकल(paddr, buffer + off, part);
				kunmap(p);

				अगर (!mem->is_pbl)
					p = siw_get_upage(mem->umem,
							  sge->laddr + part);
				अन्यथा
					p = siw_get_pblpage(mem,
							    sge->laddr + part,
							    &pbl_idx);
				अगर (unlikely(!p))
					वापस -EFAULT;

				buffer = kmap(p);
				स_नकल(paddr + part, buffer, bytes - part);
			पूर्ण
			kunmap(p);
		पूर्ण
	पूर्ण
	वापस (पूर्णांक)bytes;
पूर्ण

#घोषणा PKT_FRAGMENTED 1
#घोषणा PKT_COMPLETE 0

/*
 * siw_qp_prepare_tx()
 *
 * Prepare tx state क्रम sending out one fpdu. Builds complete pkt
 * अगर no user data or only immediate data are present.
 *
 * वापसs PKT_COMPLETE अगर complete pkt built, PKT_FRAGMENTED otherwise.
 */
अटल पूर्णांक siw_qp_prepare_tx(काष्ठा siw_iwarp_tx *c_tx)
अणु
	काष्ठा siw_wqe *wqe = &c_tx->wqe_active;
	अक्षर *crc = शून्य;
	पूर्णांक data = 0;

	चयन (tx_type(wqe)) अणु
	हाल SIW_OP_READ:
	हाल SIW_OP_READ_LOCAL_INV:
		स_नकल(&c_tx->pkt.ctrl,
		       &iwarp_pktinfo[RDMAP_RDMA_READ_REQ].ctrl,
		       माप(काष्ठा iwarp_ctrl));

		c_tx->pkt.rreq.rsvd = 0;
		c_tx->pkt.rreq.ddp_qn = htonl(RDMAP_UNTAGGED_QN_RDMA_READ);
		c_tx->pkt.rreq.ddp_msn =
			htonl(++c_tx->ddp_msn[RDMAP_UNTAGGED_QN_RDMA_READ]);
		c_tx->pkt.rreq.ddp_mo = 0;
		c_tx->pkt.rreq.sink_stag = htonl(wqe->sqe.sge[0].lkey);
		c_tx->pkt.rreq.sink_to =
			cpu_to_be64(wqe->sqe.sge[0].laddr);
		c_tx->pkt.rreq.source_stag = htonl(wqe->sqe.rkey);
		c_tx->pkt.rreq.source_to = cpu_to_be64(wqe->sqe.raddr);
		c_tx->pkt.rreq.पढ़ो_size = htonl(wqe->sqe.sge[0].length);

		c_tx->ctrl_len = माप(काष्ठा iwarp_rdma_rreq);
		crc = (अक्षर *)&c_tx->pkt.rreq_pkt.crc;
		अवरोध;

	हाल SIW_OP_SEND:
		अगर (tx_flags(wqe) & SIW_WQE_SOLICITED)
			स_नकल(&c_tx->pkt.ctrl,
			       &iwarp_pktinfo[RDMAP_SEND_SE].ctrl,
			       माप(काष्ठा iwarp_ctrl));
		अन्यथा
			स_नकल(&c_tx->pkt.ctrl, &iwarp_pktinfo[RDMAP_SEND].ctrl,
			       माप(काष्ठा iwarp_ctrl));

		c_tx->pkt.send.ddp_qn = RDMAP_UNTAGGED_QN_SEND;
		c_tx->pkt.send.ddp_msn =
			htonl(++c_tx->ddp_msn[RDMAP_UNTAGGED_QN_SEND]);
		c_tx->pkt.send.ddp_mo = 0;

		c_tx->pkt.send_inv.inval_stag = 0;

		c_tx->ctrl_len = माप(काष्ठा iwarp_send);

		crc = (अक्षर *)&c_tx->pkt.send_pkt.crc;
		data = siw_try_1seg(c_tx, crc);
		अवरोध;

	हाल SIW_OP_SEND_REMOTE_INV:
		अगर (tx_flags(wqe) & SIW_WQE_SOLICITED)
			स_नकल(&c_tx->pkt.ctrl,
			       &iwarp_pktinfo[RDMAP_SEND_SE_INVAL].ctrl,
			       माप(काष्ठा iwarp_ctrl));
		अन्यथा
			स_नकल(&c_tx->pkt.ctrl,
			       &iwarp_pktinfo[RDMAP_SEND_INVAL].ctrl,
			       माप(काष्ठा iwarp_ctrl));

		c_tx->pkt.send.ddp_qn = RDMAP_UNTAGGED_QN_SEND;
		c_tx->pkt.send.ddp_msn =
			htonl(++c_tx->ddp_msn[RDMAP_UNTAGGED_QN_SEND]);
		c_tx->pkt.send.ddp_mo = 0;

		c_tx->pkt.send_inv.inval_stag = cpu_to_be32(wqe->sqe.rkey);

		c_tx->ctrl_len = माप(काष्ठा iwarp_send_inv);

		crc = (अक्षर *)&c_tx->pkt.send_pkt.crc;
		data = siw_try_1seg(c_tx, crc);
		अवरोध;

	हाल SIW_OP_WRITE:
		स_नकल(&c_tx->pkt.ctrl, &iwarp_pktinfo[RDMAP_RDMA_WRITE].ctrl,
		       माप(काष्ठा iwarp_ctrl));

		c_tx->pkt.rग_लिखो.sink_stag = htonl(wqe->sqe.rkey);
		c_tx->pkt.rग_लिखो.sink_to = cpu_to_be64(wqe->sqe.raddr);
		c_tx->ctrl_len = माप(काष्ठा iwarp_rdma_ग_लिखो);

		crc = (अक्षर *)&c_tx->pkt.ग_लिखो_pkt.crc;
		data = siw_try_1seg(c_tx, crc);
		अवरोध;

	हाल SIW_OP_READ_RESPONSE:
		स_नकल(&c_tx->pkt.ctrl,
		       &iwarp_pktinfo[RDMAP_RDMA_READ_RESP].ctrl,
		       माप(काष्ठा iwarp_ctrl));

		/* NBO */
		c_tx->pkt.rresp.sink_stag = cpu_to_be32(wqe->sqe.rkey);
		c_tx->pkt.rresp.sink_to = cpu_to_be64(wqe->sqe.raddr);

		c_tx->ctrl_len = माप(काष्ठा iwarp_rdma_rresp);

		crc = (अक्षर *)&c_tx->pkt.ग_लिखो_pkt.crc;
		data = siw_try_1seg(c_tx, crc);
		अवरोध;

	शेष:
		siw_dbg_qp(tx_qp(c_tx), "stale wqe type %d\n", tx_type(wqe));
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (unlikely(data < 0))
		वापस data;

	c_tx->ctrl_sent = 0;

	अगर (data <= MAX_HDR_INLINE) अणु
		अगर (data) अणु
			wqe->processed = data;

			c_tx->pkt.ctrl.mpa_len =
				htons(c_tx->ctrl_len + data - MPA_HDR_SIZE);

			/* Add pad, अगर needed */
			data += -(पूर्णांक)data & 0x3;
			/* advance CRC location after payload */
			crc += data;
			c_tx->ctrl_len += data;

			अगर (!(c_tx->pkt.ctrl.ddp_rdmap_ctrl & DDP_FLAG_TAGGED))
				c_tx->pkt.c_untagged.ddp_mo = 0;
			अन्यथा
				c_tx->pkt.c_tagged.ddp_to =
					cpu_to_be64(wqe->sqe.raddr);
		पूर्ण

		*(u32 *)crc = 0;
		/*
		 * Do complete CRC अगर enabled and लघु packet
		 */
		अगर (c_tx->mpa_crc_hd) अणु
			crypto_shash_init(c_tx->mpa_crc_hd);
			अगर (crypto_shash_update(c_tx->mpa_crc_hd,
						(u8 *)&c_tx->pkt,
						c_tx->ctrl_len))
				वापस -EINVAL;
			crypto_shash_final(c_tx->mpa_crc_hd, (u8 *)crc);
		पूर्ण
		c_tx->ctrl_len += MPA_CRC_SIZE;

		वापस PKT_COMPLETE;
	पूर्ण
	c_tx->ctrl_len += MPA_CRC_SIZE;
	c_tx->sge_idx = 0;
	c_tx->sge_off = 0;
	c_tx->pbl_idx = 0;

	/*
	 * Allow direct sending out of user buffer अगर WR is non संकेतled
	 * and payload is over threshold.
	 * Per RDMA verbs, the application should not change the send buffer
	 * until the work completed. In iWarp, work completion is only
	 * local delivery to TCP. TCP may reuse the buffer क्रम
	 * retransmission. Changing unsent data also अवरोधs the CRC,
	 * अगर applied.
	 */
	अगर (c_tx->zcopy_tx && wqe->bytes >= SENDPAGE_THRESH &&
	    !(tx_flags(wqe) & SIW_WQE_SIGNALLED))
		c_tx->use_sendpage = 1;
	अन्यथा
		c_tx->use_sendpage = 0;

	वापस PKT_FRAGMENTED;
पूर्ण

/*
 * Send out one complete control type FPDU, or header of FPDU carrying
 * data. Used क्रम fixed sized packets like Read.Requests or zero length
 * SENDs, WRITEs, READ.Responses, or header only.
 */
अटल पूर्णांक siw_tx_ctrl(काष्ठा siw_iwarp_tx *c_tx, काष्ठा socket *s,
			      पूर्णांक flags)
अणु
	काष्ठा msghdr msg = अणु .msg_flags = flags पूर्ण;
	काष्ठा kvec iov = अणु .iov_base =
				    (अक्षर *)&c_tx->pkt.ctrl + c_tx->ctrl_sent,
			    .iov_len = c_tx->ctrl_len - c_tx->ctrl_sent पूर्ण;

	पूर्णांक rv = kernel_sendmsg(s, &msg, &iov, 1,
				c_tx->ctrl_len - c_tx->ctrl_sent);

	अगर (rv >= 0) अणु
		c_tx->ctrl_sent += rv;

		अगर (c_tx->ctrl_sent == c_tx->ctrl_len)
			rv = 0;
		अन्यथा
			rv = -EAGAIN;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * 0copy TCP transmit पूर्णांकerface: Use करो_tcp_sendpages.
 *
 * Using sendpage to push page by page appears to be less efficient
 * than using sendmsg, even अगर data are copied.
 *
 * A general perक्रमmance limitation might be the extra four bytes
 * trailer checksum segment to be pushed after user data.
 */
अटल पूर्णांक siw_tcp_sendpages(काष्ठा socket *s, काष्ठा page **page, पूर्णांक offset,
			     माप_प्रकार size)
अणु
	काष्ठा sock *sk = s->sk;
	पूर्णांक i = 0, rv = 0, sent = 0,
	    flags = MSG_MORE | MSG_DONTWAIT | MSG_SENDPAGE_NOTLAST;

	जबतक (size) अणु
		माप_प्रकार bytes = min_t(माप_प्रकार, PAGE_SIZE - offset, size);

		अगर (size + offset <= PAGE_SIZE)
			flags = MSG_MORE | MSG_DONTWAIT;

		tcp_rate_check_app_limited(sk);
try_page_again:
		lock_sock(sk);
		rv = करो_tcp_sendpages(sk, page[i], offset, bytes, flags);
		release_sock(sk);

		अगर (rv > 0) अणु
			size -= rv;
			sent += rv;
			अगर (rv != bytes) अणु
				offset += rv;
				bytes -= rv;
				जाओ try_page_again;
			पूर्ण
			offset = 0;
		पूर्ण अन्यथा अणु
			अगर (rv == -EAGAIN || rv == 0)
				अवरोध;
			वापस rv;
		पूर्ण
		i++;
	पूर्ण
	वापस sent;
पूर्ण

/*
 * siw_0copy_tx()
 *
 * Pushes list of pages to TCP socket. If pages from multiple
 * SGE's, all referenced pages of each SGE are pushed in one
 * shot.
 */
अटल पूर्णांक siw_0copy_tx(काष्ठा socket *s, काष्ठा page **page,
			काष्ठा siw_sge *sge, अचिन्हित पूर्णांक offset,
			अचिन्हित पूर्णांक size)
अणु
	पूर्णांक i = 0, sent = 0, rv;
	पूर्णांक sge_bytes = min(sge->length - offset, size);

	offset = (sge->laddr + offset) & ~PAGE_MASK;

	जबतक (sent != size) अणु
		rv = siw_tcp_sendpages(s, &page[i], offset, sge_bytes);
		अगर (rv >= 0) अणु
			sent += rv;
			अगर (size == sent || sge_bytes > rv)
				अवरोध;

			i += PAGE_ALIGN(sge_bytes + offset) >> PAGE_SHIFT;
			sge++;
			sge_bytes = min(sge->length, size - sent);
			offset = sge->laddr & ~PAGE_MASK;
		पूर्ण अन्यथा अणु
			sent = rv;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस sent;
पूर्ण

#घोषणा MAX_TRAILER (MPA_CRC_SIZE + 4)

अटल व्योम siw_unmap_pages(काष्ठा page **pp, अचिन्हित दीर्घ kmap_mask)
अणु
	जबतक (kmap_mask) अणु
		अगर (kmap_mask & BIT(0))
			kunmap(*pp);
		pp++;
		kmap_mask >>= 1;
	पूर्ण
पूर्ण

/*
 * siw_tx_hdt() tries to push a complete packet to TCP where all
 * packet fragments are referenced by the elements of one iovec.
 * For the data portion, each involved page must be referenced by
 * one extra element. All sge's data can be non-aligned to page
 * boundaries. Two more elements are referencing iWARP header
 * and trailer:
 * MAX_ARRAY = 64KB/PAGE_SIZE + 1 + (2 * (SIW_MAX_SGE - 1) + HDR + TRL
 */
#घोषणा MAX_ARRAY ((0xffff / PAGE_SIZE) + 1 + (2 * (SIW_MAX_SGE - 1) + 2))

/*
 * Write out iov referencing hdr, data and trailer of current FPDU.
 * Update transmit state dependent on ग_लिखो वापस status
 */
अटल पूर्णांक siw_tx_hdt(काष्ठा siw_iwarp_tx *c_tx, काष्ठा socket *s)
अणु
	काष्ठा siw_wqe *wqe = &c_tx->wqe_active;
	काष्ठा siw_sge *sge = &wqe->sqe.sge[c_tx->sge_idx];
	काष्ठा kvec iov[MAX_ARRAY];
	काष्ठा page *page_array[MAX_ARRAY];
	काष्ठा msghdr msg = अणु .msg_flags = MSG_DONTWAIT | MSG_EOR पूर्ण;

	पूर्णांक seg = 0, करो_crc = c_tx->करो_crc, is_kva = 0, rv;
	अचिन्हित पूर्णांक data_len = c_tx->bytes_unsent, hdr_len = 0, trl_len = 0,
		     sge_off = c_tx->sge_off, sge_idx = c_tx->sge_idx,
		     pbl_idx = c_tx->pbl_idx;
	अचिन्हित दीर्घ kmap_mask = 0L;

	अगर (c_tx->state == SIW_SEND_HDR) अणु
		अगर (c_tx->use_sendpage) अणु
			rv = siw_tx_ctrl(c_tx, s, MSG_DONTWAIT | MSG_MORE);
			अगर (rv)
				जाओ करोne;

			c_tx->state = SIW_SEND_DATA;
		पूर्ण अन्यथा अणु
			iov[0].iov_base =
				(अक्षर *)&c_tx->pkt.ctrl + c_tx->ctrl_sent;
			iov[0].iov_len = hdr_len =
				c_tx->ctrl_len - c_tx->ctrl_sent;
			seg = 1;
		पूर्ण
	पूर्ण

	wqe->processed += data_len;

	जबतक (data_len) अणु /* walk the list of SGE's */
		अचिन्हित पूर्णांक sge_len = min(sge->length - sge_off, data_len);
		अचिन्हित पूर्णांक fp_off = (sge->laddr + sge_off) & ~PAGE_MASK;
		काष्ठा siw_mem *mem;

		अगर (!(tx_flags(wqe) & SIW_WQE_INLINE)) अणु
			mem = wqe->mem[sge_idx];
			is_kva = mem->mem_obj == शून्य ? 1 : 0;
		पूर्ण अन्यथा अणु
			is_kva = 1;
		पूर्ण
		अगर (is_kva && !c_tx->use_sendpage) अणु
			/*
			 * tx from kernel भव address: either अंतरभूत data
			 * or memory region with asचिन्हित kernel buffer
			 */
			iov[seg].iov_base =
				(व्योम *)(uपूर्णांकptr_t)(sge->laddr + sge_off);
			iov[seg].iov_len = sge_len;

			अगर (करो_crc)
				crypto_shash_update(c_tx->mpa_crc_hd,
						    iov[seg].iov_base,
						    sge_len);
			sge_off += sge_len;
			data_len -= sge_len;
			seg++;
			जाओ sge_करोne;
		पूर्ण

		जबतक (sge_len) अणु
			माप_प्रकार plen = min((पूर्णांक)PAGE_SIZE - fp_off, sge_len);

			अगर (!is_kva) अणु
				काष्ठा page *p;

				अगर (mem->is_pbl)
					p = siw_get_pblpage(
						mem, sge->laddr + sge_off,
						&pbl_idx);
				अन्यथा
					p = siw_get_upage(mem->umem,
							  sge->laddr + sge_off);
				अगर (unlikely(!p)) अणु
					siw_unmap_pages(page_array, kmap_mask);
					wqe->processed -= c_tx->bytes_unsent;
					rv = -EFAULT;
					जाओ करोne_crc;
				पूर्ण
				page_array[seg] = p;

				अगर (!c_tx->use_sendpage) अणु
					iov[seg].iov_base = kmap(p) + fp_off;
					iov[seg].iov_len = plen;

					/* Remember क्रम later kunmap() */
					kmap_mask |= BIT(seg);

					अगर (करो_crc)
						crypto_shash_update(
							c_tx->mpa_crc_hd,
							iov[seg].iov_base,
							plen);
				पूर्ण अन्यथा अगर (करो_crc) अणु
					crypto_shash_update(c_tx->mpa_crc_hd,
							    kmap(p) + fp_off,
							    plen);
					kunmap(p);
				पूर्ण
			पूर्ण अन्यथा अणु
				u64 va = sge->laddr + sge_off;

				page_array[seg] = virt_to_page(va & PAGE_MASK);
				अगर (करो_crc)
					crypto_shash_update(
						c_tx->mpa_crc_hd,
						(व्योम *)(uपूर्णांकptr_t)va,
						plen);
			पूर्ण

			sge_len -= plen;
			sge_off += plen;
			data_len -= plen;
			fp_off = 0;

			अगर (++seg > (पूर्णांक)MAX_ARRAY) अणु
				siw_dbg_qp(tx_qp(c_tx), "to many fragments\n");
				siw_unmap_pages(page_array, kmap_mask);
				wqe->processed -= c_tx->bytes_unsent;
				rv = -EMSGSIZE;
				जाओ करोne_crc;
			पूर्ण
		पूर्ण
sge_करोne:
		/* Update SGE variables at end of SGE */
		अगर (sge_off == sge->length &&
		    (data_len != 0 || wqe->processed < wqe->bytes)) अणु
			sge_idx++;
			sge++;
			sge_off = 0;
		पूर्ण
	पूर्ण
	/* trailer */
	अगर (likely(c_tx->state != SIW_SEND_TRAILER)) अणु
		iov[seg].iov_base = &c_tx->trailer.pad[4 - c_tx->pad];
		iov[seg].iov_len = trl_len = MAX_TRAILER - (4 - c_tx->pad);
	पूर्ण अन्यथा अणु
		iov[seg].iov_base = &c_tx->trailer.pad[c_tx->ctrl_sent];
		iov[seg].iov_len = trl_len = MAX_TRAILER - c_tx->ctrl_sent;
	पूर्ण

	अगर (c_tx->pad) अणु
		*(u32 *)c_tx->trailer.pad = 0;
		अगर (करो_crc)
			crypto_shash_update(c_tx->mpa_crc_hd,
				(u8 *)&c_tx->trailer.crc - c_tx->pad,
				c_tx->pad);
	पूर्ण
	अगर (!c_tx->mpa_crc_hd)
		c_tx->trailer.crc = 0;
	अन्यथा अगर (करो_crc)
		crypto_shash_final(c_tx->mpa_crc_hd, (u8 *)&c_tx->trailer.crc);

	data_len = c_tx->bytes_unsent;

	अगर (c_tx->use_sendpage) अणु
		rv = siw_0copy_tx(s, page_array, &wqe->sqe.sge[c_tx->sge_idx],
				  c_tx->sge_off, data_len);
		अगर (rv == data_len) अणु
			rv = kernel_sendmsg(s, &msg, &iov[seg], 1, trl_len);
			अगर (rv > 0)
				rv += data_len;
			अन्यथा
				rv = data_len;
		पूर्ण
	पूर्ण अन्यथा अणु
		rv = kernel_sendmsg(s, &msg, iov, seg + 1,
				    hdr_len + data_len + trl_len);
		siw_unmap_pages(page_array, kmap_mask);
	पूर्ण
	अगर (rv < (पूर्णांक)hdr_len) अणु
		/* Not even complete hdr pushed or negative rv */
		wqe->processed -= data_len;
		अगर (rv >= 0) अणु
			c_tx->ctrl_sent += rv;
			rv = -EAGAIN;
		पूर्ण
		जाओ करोne_crc;
	पूर्ण
	rv -= hdr_len;

	अगर (rv >= (पूर्णांक)data_len) अणु
		/* all user data pushed to TCP or no data to push */
		अगर (data_len > 0 && wqe->processed < wqe->bytes) अणु
			/* Save the current state क्रम next tx */
			c_tx->sge_idx = sge_idx;
			c_tx->sge_off = sge_off;
			c_tx->pbl_idx = pbl_idx;
		पूर्ण
		rv -= data_len;

		अगर (rv == trl_len) /* all pushed */
			rv = 0;
		अन्यथा अणु
			c_tx->state = SIW_SEND_TRAILER;
			c_tx->ctrl_len = MAX_TRAILER;
			c_tx->ctrl_sent = rv + 4 - c_tx->pad;
			c_tx->bytes_unsent = 0;
			rv = -EAGAIN;
		पूर्ण

	पूर्ण अन्यथा अगर (data_len > 0) अणु
		/* Maybe some user data pushed to TCP */
		c_tx->state = SIW_SEND_DATA;
		wqe->processed -= data_len - rv;

		अगर (rv) अणु
			/*
			 * Some bytes out. Recompute tx state based
			 * on old state and bytes pushed
			 */
			अचिन्हित पूर्णांक sge_unsent;

			c_tx->bytes_unsent -= rv;
			sge = &wqe->sqe.sge[c_tx->sge_idx];
			sge_unsent = sge->length - c_tx->sge_off;

			जबतक (sge_unsent <= rv) अणु
				rv -= sge_unsent;
				c_tx->sge_idx++;
				c_tx->sge_off = 0;
				sge++;
				sge_unsent = sge->length;
			पूर्ण
			c_tx->sge_off += rv;
		पूर्ण
		rv = -EAGAIN;
	पूर्ण
करोne_crc:
	c_tx->करो_crc = 0;
करोne:
	वापस rv;
पूर्ण

अटल व्योम siw_update_tcpseg(काष्ठा siw_iwarp_tx *c_tx,
				     काष्ठा socket *s)
अणु
	काष्ठा tcp_sock *tp = tcp_sk(s->sk);

	अगर (tp->gso_segs) अणु
		अगर (c_tx->gso_seg_limit == 0)
			c_tx->tcp_seglen = tp->mss_cache * tp->gso_segs;
		अन्यथा
			c_tx->tcp_seglen =
				tp->mss_cache *
				min_t(u16, c_tx->gso_seg_limit, tp->gso_segs);
	पूर्ण अन्यथा अणु
		c_tx->tcp_seglen = tp->mss_cache;
	पूर्ण
	/* Loopback may give odd numbers */
	c_tx->tcp_seglen &= 0xfffffff8;
पूर्ण

/*
 * siw_prepare_fpdu()
 *
 * Prepares transmit context to send out one FPDU अगर FPDU will contain
 * user data and user data are not immediate data.
 * Computes maximum FPDU length to fill up TCP MSS अगर possible.
 *
 * @qp:		QP from which to transmit
 * @wqe:	Current WQE causing transmission
 *
 * TODO: Take पूर्णांकo account real available sendspace on socket
 *       to aव्योम header misalignment due to send pausing within
 *       fpdu transmission
 */
अटल व्योम siw_prepare_fpdu(काष्ठा siw_qp *qp, काष्ठा siw_wqe *wqe)
अणु
	काष्ठा siw_iwarp_tx *c_tx = &qp->tx_ctx;
	पूर्णांक data_len;

	c_tx->ctrl_len =
		iwarp_pktinfo[__rdmap_get_opcode(&c_tx->pkt.ctrl)].hdr_len;
	c_tx->ctrl_sent = 0;

	/*
	 * Update target buffer offset अगर any
	 */
	अगर (!(c_tx->pkt.ctrl.ddp_rdmap_ctrl & DDP_FLAG_TAGGED))
		/* Untagged message */
		c_tx->pkt.c_untagged.ddp_mo = cpu_to_be32(wqe->processed);
	अन्यथा /* Tagged message */
		c_tx->pkt.c_tagged.ddp_to =
			cpu_to_be64(wqe->sqe.raddr + wqe->processed);

	data_len = wqe->bytes - wqe->processed;
	अगर (data_len + c_tx->ctrl_len + MPA_CRC_SIZE > c_tx->tcp_seglen) अणु
		/* Trim DDP payload to fit पूर्णांकo current TCP segment */
		data_len = c_tx->tcp_seglen - (c_tx->ctrl_len + MPA_CRC_SIZE);
		c_tx->pkt.ctrl.ddp_rdmap_ctrl &= ~DDP_FLAG_LAST;
		c_tx->pad = 0;
	पूर्ण अन्यथा अणु
		c_tx->pkt.ctrl.ddp_rdmap_ctrl |= DDP_FLAG_LAST;
		c_tx->pad = -data_len & 0x3;
	पूर्ण
	c_tx->bytes_unsent = data_len;

	c_tx->pkt.ctrl.mpa_len =
		htons(c_tx->ctrl_len + data_len - MPA_HDR_SIZE);

	/*
	 * Init MPA CRC computation
	 */
	अगर (c_tx->mpa_crc_hd) अणु
		crypto_shash_init(c_tx->mpa_crc_hd);
		crypto_shash_update(c_tx->mpa_crc_hd, (u8 *)&c_tx->pkt,
				    c_tx->ctrl_len);
		c_tx->करो_crc = 1;
	पूर्ण
पूर्ण

/*
 * siw_check_sgl_tx()
 *
 * Check permissions क्रम a list of SGE's (SGL).
 * A successful check will have all memory referenced
 * क्रम transmission resolved and asचिन्हित to the WQE.
 *
 * @pd:		Protection Doमुख्य SGL should beदीर्घ to
 * @wqe:	WQE to be checked
 * @perms:	requested access permissions
 *
 */

अटल पूर्णांक siw_check_sgl_tx(काष्ठा ib_pd *pd, काष्ठा siw_wqe *wqe,
			    क्रमागत ib_access_flags perms)
अणु
	काष्ठा siw_sge *sge = &wqe->sqe.sge[0];
	पूर्णांक i, len, num_sge = wqe->sqe.num_sge;

	अगर (unlikely(num_sge > SIW_MAX_SGE))
		वापस -EINVAL;

	क्रम (i = 0, len = 0; num_sge; num_sge--, i++, sge++) अणु
		/*
		 * rdma verbs: करो not check stag क्रम a zero length sge
		 */
		अगर (sge->length) अणु
			पूर्णांक rv = siw_check_sge(pd, sge, &wqe->mem[i], perms, 0,
					       sge->length);

			अगर (unlikely(rv != E_ACCESS_OK))
				वापस rv;
		पूर्ण
		len += sge->length;
	पूर्ण
	वापस len;
पूर्ण

/*
 * siw_qp_sq_proc_tx()
 *
 * Process one WQE which needs transmission on the wire.
 */
अटल पूर्णांक siw_qp_sq_proc_tx(काष्ठा siw_qp *qp, काष्ठा siw_wqe *wqe)
अणु
	काष्ठा siw_iwarp_tx *c_tx = &qp->tx_ctx;
	काष्ठा socket *s = qp->attrs.sk;
	पूर्णांक rv = 0, burst_len = qp->tx_ctx.burst;
	क्रमागत rdmap_ecode ecode = RDMAP_ECODE_CATASTROPHIC_STREAM;

	अगर (unlikely(wqe->wr_status == SIW_WR_IDLE))
		वापस 0;

	अगर (!burst_len)
		burst_len = SQ_USER_MAXBURST;

	अगर (wqe->wr_status == SIW_WR_QUEUED) अणु
		अगर (!(wqe->sqe.flags & SIW_WQE_INLINE)) अणु
			अगर (tx_type(wqe) == SIW_OP_READ_RESPONSE)
				wqe->sqe.num_sge = 1;

			अगर (tx_type(wqe) != SIW_OP_READ &&
			    tx_type(wqe) != SIW_OP_READ_LOCAL_INV) अणु
				/*
				 * Reference memory to be tx'd w/o checking
				 * access क्रम LOCAL_READ permission, since
				 * not defined in RDMA core.
				 */
				rv = siw_check_sgl_tx(qp->pd, wqe, 0);
				अगर (rv < 0) अणु
					अगर (tx_type(wqe) ==
					    SIW_OP_READ_RESPONSE)
						ecode = siw_rdmap_error(-rv);
					rv = -EINVAL;
					जाओ tx_error;
				पूर्ण
				wqe->bytes = rv;
			पूर्ण अन्यथा अणु
				wqe->bytes = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			wqe->bytes = wqe->sqe.sge[0].length;
			अगर (!rdma_is_kernel_res(&qp->base_qp.res)) अणु
				अगर (wqe->bytes > SIW_MAX_INLINE) अणु
					rv = -EINVAL;
					जाओ tx_error;
				पूर्ण
				wqe->sqe.sge[0].laddr =
					(u64)(uपूर्णांकptr_t)&wqe->sqe.sge[1];
			पूर्ण
		पूर्ण
		wqe->wr_status = SIW_WR_INPROGRESS;
		wqe->processed = 0;

		siw_update_tcpseg(c_tx, s);

		rv = siw_qp_prepare_tx(c_tx);
		अगर (rv == PKT_FRAGMENTED) अणु
			c_tx->state = SIW_SEND_HDR;
			siw_prepare_fpdu(qp, wqe);
		पूर्ण अन्यथा अगर (rv == PKT_COMPLETE) अणु
			c_tx->state = SIW_SEND_SHORT_FPDU;
		पूर्ण अन्यथा अणु
			जाओ tx_error;
		पूर्ण
	पूर्ण

next_segment:
	siw_dbg_qp(qp, "wr type %d, state %d, data %u, sent %u, id %llx\n",
		   tx_type(wqe), wqe->wr_status, wqe->bytes, wqe->processed,
		   wqe->sqe.id);

	अगर (--burst_len == 0) अणु
		rv = -EINPROGRESS;
		जाओ tx_करोne;
	पूर्ण
	अगर (c_tx->state == SIW_SEND_SHORT_FPDU) अणु
		क्रमागत siw_opcode tx_type = tx_type(wqe);
		अचिन्हित पूर्णांक msg_flags;

		अगर (siw_sq_empty(qp) || !siw_tcp_nagle || burst_len == 1)
			/*
			 * End current TCP segment, अगर SQ runs empty,
			 * or siw_tcp_nagle is not set, or we bail out
			 * soon due to no burst credit left.
			 */
			msg_flags = MSG_DONTWAIT;
		अन्यथा
			msg_flags = MSG_DONTWAIT | MSG_MORE;

		rv = siw_tx_ctrl(c_tx, s, msg_flags);

		अगर (!rv && tx_type != SIW_OP_READ &&
		    tx_type != SIW_OP_READ_LOCAL_INV)
			wqe->processed = wqe->bytes;

		जाओ tx_करोne;

	पूर्ण अन्यथा अणु
		rv = siw_tx_hdt(c_tx, s);
	पूर्ण
	अगर (!rv) अणु
		/*
		 * One segment sent. Processing completed अगर last
		 * segment, Do next segment otherwise.
		 */
		अगर (unlikely(c_tx->tx_suspend)) अणु
			/*
			 * Verbs, 6.4.: Try stopping sending after a full
			 * DDP segment अगर the connection goes करोwn
			 * (== peer halख_बंद)
			 */
			rv = -ECONNABORTED;
			जाओ tx_करोne;
		पूर्ण
		अगर (c_tx->pkt.ctrl.ddp_rdmap_ctrl & DDP_FLAG_LAST) अणु
			siw_dbg_qp(qp, "WQE completed\n");
			जाओ tx_करोne;
		पूर्ण
		c_tx->state = SIW_SEND_HDR;

		siw_update_tcpseg(c_tx, s);

		siw_prepare_fpdu(qp, wqe);
		जाओ next_segment;
	पूर्ण
tx_करोne:
	qp->tx_ctx.burst = burst_len;
	वापस rv;

tx_error:
	अगर (ecode != RDMAP_ECODE_CATASTROPHIC_STREAM)
		siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
				   RDMAP_ETYPE_REMOTE_PROTECTION, ecode, 1);
	अन्यथा
		siw_init_terminate(qp, TERM_ERROR_LAYER_RDMAP,
				   RDMAP_ETYPE_CATASTROPHIC,
				   RDMAP_ECODE_UNSPECIFIED, 1);
	वापस rv;
पूर्ण

अटल पूर्णांक siw_fastreg_mr(काष्ठा ib_pd *pd, काष्ठा siw_sqe *sqe)
अणु
	काष्ठा ib_mr *base_mr = (काष्ठा ib_mr *)(uपूर्णांकptr_t)sqe->base_mr;
	काष्ठा siw_device *sdev = to_siw_dev(pd->device);
	काष्ठा siw_mem *mem;
	पूर्णांक rv = 0;

	siw_dbg_pd(pd, "STag 0x%08x\n", sqe->rkey);

	अगर (unlikely(!base_mr)) अणु
		pr_warn("siw: fastreg: STag 0x%08x unknown\n", sqe->rkey);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(base_mr->rkey >> 8 != sqe->rkey  >> 8)) अणु
		pr_warn("siw: fastreg: STag 0x%08x: bad MR\n", sqe->rkey);
		वापस -EINVAL;
	पूर्ण

	mem = siw_mem_id2obj(sdev, sqe->rkey  >> 8);
	अगर (unlikely(!mem)) अणु
		pr_warn("siw: fastreg: STag 0x%08x unknown\n", sqe->rkey);
		वापस -EINVAL;
	पूर्ण

	अगर (unlikely(mem->pd != pd)) अणु
		pr_warn("siw: fastreg: PD mismatch\n");
		rv = -EINVAL;
		जाओ out;
	पूर्ण
	अगर (unlikely(mem->stag_valid)) अणु
		pr_warn("siw: fastreg: STag 0x%08x already valid\n", sqe->rkey);
		rv = -EINVAL;
		जाओ out;
	पूर्ण
	/* Refresh STag since user may have changed key part */
	mem->stag = sqe->rkey;
	mem->perms = sqe->access;

	siw_dbg_mem(mem, "STag 0x%08x now valid\n", sqe->rkey);
	mem->va = base_mr->iova;
	mem->stag_valid = 1;
out:
	siw_mem_put(mem);
	वापस rv;
पूर्ण

अटल पूर्णांक siw_qp_sq_proc_local(काष्ठा siw_qp *qp, काष्ठा siw_wqe *wqe)
अणु
	पूर्णांक rv;

	चयन (tx_type(wqe)) अणु
	हाल SIW_OP_REG_MR:
		rv = siw_fastreg_mr(qp->pd, &wqe->sqe);
		अवरोध;

	हाल SIW_OP_INVAL_STAG:
		rv = siw_invalidate_stag(qp->pd, wqe->sqe.rkey);
		अवरोध;

	शेष:
		rv = -EINVAL;
	पूर्ण
	वापस rv;
पूर्ण

/*
 * siw_qp_sq_process()
 *
 * Core TX path routine क्रम RDMAP/DDP/MPA using a TCP kernel socket.
 * Sends RDMAP payload क्रम the current SQ WR @wqe of @qp in one or more
 * MPA FPDUs, each containing a DDP segment.
 *
 * SQ processing may occur in user context as a result of posting
 * new WQE's or from siw_sq_work_handler() context. Processing in
 * user context is limited to non-kernel verbs users.
 *
 * SQ processing may get छोड़ोd anyसमय, possibly in the middle of a WR
 * or FPDU, अगर insufficient send space is available. SQ processing
 * माला_लो resumed from siw_sq_work_handler(), अगर send space becomes
 * available again.
 *
 * Must be called with the QP state पढ़ो-locked.
 *
 * Note:
 * An outbound RREQ can be satisfied by the corresponding RRESP
 * _beक्रमe_ it माला_लो asचिन्हित to the ORQ. This happens regularly
 * in RDMA READ via loopback हाल. Since both outbound RREQ and
 * inbound RRESP can be handled by the same CPU, locking the ORQ
 * is dead-lock prone and thus not an option. With that, the
 * RREQ माला_लो asचिन्हित to the ORQ _beक्रमe_ being sent - see
 * siw_activate_tx() - and pulled back in हाल of send failure.
 */
पूर्णांक siw_qp_sq_process(काष्ठा siw_qp *qp)
अणु
	काष्ठा siw_wqe *wqe = tx_wqe(qp);
	क्रमागत siw_opcode tx_type;
	अचिन्हित दीर्घ flags;
	पूर्णांक rv = 0;

	siw_dbg_qp(qp, "enter for type %d\n", tx_type(wqe));

next_wqe:
	/*
	 * Stop QP processing अगर SQ state changed
	 */
	अगर (unlikely(qp->tx_ctx.tx_suspend)) अणु
		siw_dbg_qp(qp, "tx suspended\n");
		जाओ करोne;
	पूर्ण
	tx_type = tx_type(wqe);

	अगर (tx_type <= SIW_OP_READ_RESPONSE)
		rv = siw_qp_sq_proc_tx(qp, wqe);
	अन्यथा
		rv = siw_qp_sq_proc_local(qp, wqe);

	अगर (!rv) अणु
		/*
		 * WQE processing करोne
		 */
		चयन (tx_type) अणु
		हाल SIW_OP_SEND:
		हाल SIW_OP_SEND_REMOTE_INV:
		हाल SIW_OP_WRITE:
			siw_wqe_put_mem(wqe, tx_type);
			fallthrough;

		हाल SIW_OP_INVAL_STAG:
		हाल SIW_OP_REG_MR:
			अगर (tx_flags(wqe) & SIW_WQE_SIGNALLED)
				siw_sqe_complete(qp, &wqe->sqe, wqe->bytes,
						 SIW_WC_SUCCESS);
			अवरोध;

		हाल SIW_OP_READ:
		हाल SIW_OP_READ_LOCAL_INV:
			/*
			 * alपढ़ोy enqueued to ORQ queue
			 */
			अवरोध;

		हाल SIW_OP_READ_RESPONSE:
			siw_wqe_put_mem(wqe, tx_type);
			अवरोध;

		शेष:
			WARN(1, "undefined WQE type %d\n", tx_type);
			rv = -EINVAL;
			जाओ करोne;
		पूर्ण

		spin_lock_irqsave(&qp->sq_lock, flags);
		wqe->wr_status = SIW_WR_IDLE;
		rv = siw_activate_tx(qp);
		spin_unlock_irqrestore(&qp->sq_lock, flags);

		अगर (rv <= 0)
			जाओ करोne;

		जाओ next_wqe;

	पूर्ण अन्यथा अगर (rv == -EAGAIN) अणु
		siw_dbg_qp(qp, "sq paused: hd/tr %d of %d, data %d\n",
			   qp->tx_ctx.ctrl_sent, qp->tx_ctx.ctrl_len,
			   qp->tx_ctx.bytes_unsent);
		rv = 0;
		जाओ करोne;
	पूर्ण अन्यथा अगर (rv == -EINPROGRESS) अणु
		rv = siw_sq_start(qp);
		जाओ करोne;
	पूर्ण अन्यथा अणु
		/*
		 * WQE processing failed.
		 * Verbs 8.3.2:
		 * o It turns any WQE पूर्णांकo a संकेतled WQE.
		 * o Local catastrophic error must be surfaced
		 * o QP must be moved पूर्णांकo Terminate state: करोne by code
		 *   करोing socket state change processing
		 *
		 * o TODO: Termination message must be sent.
		 * o TODO: Implement more precise work completion errors,
		 *         see क्रमागत ib_wc_status in ib_verbs.h
		 */
		siw_dbg_qp(qp, "wqe type %d processing failed: %d\n",
			   tx_type(wqe), rv);

		spin_lock_irqsave(&qp->sq_lock, flags);
		/*
		 * RREQ may have alपढ़ोy been completed by inbound RRESP!
		 */
		अगर ((tx_type == SIW_OP_READ ||
		     tx_type == SIW_OP_READ_LOCAL_INV) && qp->attrs.orq_size) अणु
			/* Cleanup pending entry in ORQ */
			qp->orq_put--;
			qp->orq[qp->orq_put % qp->attrs.orq_size].flags = 0;
		पूर्ण
		spin_unlock_irqrestore(&qp->sq_lock, flags);
		/*
		 * immediately suspends further TX processing
		 */
		अगर (!qp->tx_ctx.tx_suspend)
			siw_qp_cm_drop(qp, 0);

		चयन (tx_type) अणु
		हाल SIW_OP_SEND:
		हाल SIW_OP_SEND_REMOTE_INV:
		हाल SIW_OP_SEND_WITH_IMM:
		हाल SIW_OP_WRITE:
		हाल SIW_OP_READ:
		हाल SIW_OP_READ_LOCAL_INV:
			siw_wqe_put_mem(wqe, tx_type);
			fallthrough;

		हाल SIW_OP_INVAL_STAG:
		हाल SIW_OP_REG_MR:
			siw_sqe_complete(qp, &wqe->sqe, wqe->bytes,
					 SIW_WC_LOC_QP_OP_ERR);

			siw_qp_event(qp, IB_EVENT_QP_FATAL);

			अवरोध;

		हाल SIW_OP_READ_RESPONSE:
			siw_dbg_qp(qp, "proc. read.response failed: %d\n", rv);

			siw_qp_event(qp, IB_EVENT_QP_REQ_ERR);

			siw_wqe_put_mem(wqe, SIW_OP_READ_RESPONSE);

			अवरोध;

		शेष:
			WARN(1, "undefined WQE type %d\n", tx_type);
			rv = -EINVAL;
		पूर्ण
		wqe->wr_status = SIW_WR_IDLE;
	पूर्ण
करोne:
	वापस rv;
पूर्ण

अटल व्योम siw_sq_resume(काष्ठा siw_qp *qp)
अणु
	अगर (करोwn_पढ़ो_trylock(&qp->state_lock)) अणु
		अगर (likely(qp->attrs.state == SIW_QP_STATE_RTS &&
			   !qp->tx_ctx.tx_suspend)) अणु
			पूर्णांक rv = siw_qp_sq_process(qp);

			up_पढ़ो(&qp->state_lock);

			अगर (unlikely(rv < 0)) अणु
				siw_dbg_qp(qp, "SQ task failed: err %d\n", rv);

				अगर (!qp->tx_ctx.tx_suspend)
					siw_qp_cm_drop(qp, 0);
			पूर्ण
		पूर्ण अन्यथा अणु
			up_पढ़ो(&qp->state_lock);
		पूर्ण
	पूर्ण अन्यथा अणु
		siw_dbg_qp(qp, "Resume SQ while QP locked\n");
	पूर्ण
	siw_qp_put(qp);
पूर्ण

काष्ठा tx_task_t अणु
	काष्ठा llist_head active;
	रुको_queue_head_t रुकोing;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा tx_task_t, siw_tx_task_g);

व्योम siw_stop_tx_thपढ़ो(पूर्णांक nr_cpu)
अणु
	kthपढ़ो_stop(siw_tx_thपढ़ो[nr_cpu]);
	wake_up(&per_cpu(siw_tx_task_g, nr_cpu).रुकोing);
पूर्ण

पूर्णांक siw_run_sq(व्योम *data)
अणु
	स्थिर पूर्णांक nr_cpu = (अचिन्हित पूर्णांक)(दीर्घ)data;
	काष्ठा llist_node *active;
	काष्ठा siw_qp *qp;
	काष्ठा tx_task_t *tx_task = &per_cpu(siw_tx_task_g, nr_cpu);

	init_llist_head(&tx_task->active);
	init_रुकोqueue_head(&tx_task->रुकोing);

	जबतक (1) अणु
		काष्ठा llist_node *fअगरo_list = शून्य;

		रुको_event_पूर्णांकerruptible(tx_task->रुकोing,
					 !llist_empty(&tx_task->active) ||
						 kthपढ़ो_should_stop());

		अगर (kthपढ़ो_should_stop())
			अवरोध;

		active = llist_del_all(&tx_task->active);
		/*
		 * llist_del_all वापसs a list with newest entry first.
		 * Re-order list क्रम fairness among QP's.
		 */
		जबतक (active) अणु
			काष्ठा llist_node *पंचांगp = active;

			active = llist_next(active);
			पंचांगp->next = fअगरo_list;
			fअगरo_list = पंचांगp;
		पूर्ण
		जबतक (fअगरo_list) अणु
			qp = container_of(fअगरo_list, काष्ठा siw_qp, tx_list);
			fअगरo_list = llist_next(fअगरo_list);
			qp->tx_list.next = शून्य;

			siw_sq_resume(qp);
		पूर्ण
	पूर्ण
	active = llist_del_all(&tx_task->active);
	अगर (active) अणु
		llist_क्रम_each_entry(qp, active, tx_list) अणु
			qp->tx_list.next = शून्य;
			siw_sq_resume(qp);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक siw_sq_start(काष्ठा siw_qp *qp)
अणु
	अगर (tx_wqe(qp)->wr_status == SIW_WR_IDLE)
		वापस 0;

	अगर (unlikely(!cpu_online(qp->tx_cpu))) अणु
		siw_put_tx_cpu(qp->tx_cpu);
		qp->tx_cpu = siw_get_tx_cpu(qp->sdev);
		अगर (qp->tx_cpu < 0) अणु
			pr_warn("siw: no tx cpu available\n");

			वापस -EIO;
		पूर्ण
	पूर्ण
	siw_qp_get(qp);

	llist_add(&qp->tx_list, &per_cpu(siw_tx_task_g, qp->tx_cpu).active);

	wake_up(&per_cpu(siw_tx_task_g, qp->tx_cpu).रुकोing);

	वापस 0;
पूर्ण
