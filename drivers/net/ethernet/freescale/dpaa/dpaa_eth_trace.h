<शैली गुरु>
/* Copyright 2013-2015 Freescale Semiconductor Inc.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *	 notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *	 notice, this list of conditions and the following disclaimer in the
 *	 करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *	 names of its contributors may be used to enकरोrse or promote products
 *	 derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM	dpaa_eth

#अगर !defined(_DPAA_ETH_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _DPAA_ETH_TRACE_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश "dpaa_eth.h"
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा fd_क्रमmat_name(क्रमmat)	अणु qm_fd_##क्रमmat, #क्रमmat पूर्ण
#घोषणा fd_क्रमmat_list	\
	fd_क्रमmat_name(contig),	\
	fd_क्रमmat_name(sg)

/* This is used to declare a class of events.
 * inभागidual events of this type will be defined below.
 */

/* Store details about a frame descriptor and the FQ on which it was
 * transmitted/received.
 */
DECLARE_EVENT_CLASS(dpaa_eth_fd,
	/* Trace function prototype */
	TP_PROTO(काष्ठा net_device *netdev,
		 काष्ठा qman_fq *fq,
		 स्थिर काष्ठा qm_fd *fd),

	/* Repeat argument list here */
	TP_ARGS(netdev, fq, fd),

	/* A काष्ठाure containing the relevant inक्रमmation we want to record.
	 * Declare name and type क्रम each normal element, name, type and size
	 * क्रम arrays. Use __string क्रम variable length strings.
	 */
	TP_STRUCT__entry(
		__field(u32,	fqid)
		__field(u64,	fd_addr)
		__field(u8,	fd_क्रमmat)
		__field(u16,	fd_offset)
		__field(u32,	fd_length)
		__field(u32,	fd_status)
		__string(name,	netdev->name)
	),

	/* The function that assigns values to the above declared fields */
	TP_fast_assign(
		__entry->fqid = fq->fqid;
		__entry->fd_addr = qm_fd_addr_get64(fd);
		__entry->fd_क्रमmat = qm_fd_get_क्रमmat(fd);
		__entry->fd_offset = qm_fd_get_offset(fd);
		__entry->fd_length = qm_fd_get_length(fd);
		__entry->fd_status = fd->status;
		__assign_str(name, netdev->name);
	),

	/* This is what माला_लो prपूर्णांकed when the trace event is triggered */
	TP_prपूर्णांकk("[%s] fqid=%d, fd: addr=0x%llx, format=%s, off=%u, len=%u, status=0x%08x",
		  __get_str(name), __entry->fqid, __entry->fd_addr,
		  __prपूर्णांक_symbolic(__entry->fd_क्रमmat, fd_क्रमmat_list),
		  __entry->fd_offset, __entry->fd_length, __entry->fd_status)
);

/* Now declare events of the above type. Format is:
 * DEFINE_EVENT(class, name, proto, args), with proto and args same as क्रम class
 */

/* Tx (egress) fd */
DEFINE_EVENT(dpaa_eth_fd, dpaa_tx_fd,

	TP_PROTO(काष्ठा net_device *netdev,
		 काष्ठा qman_fq *fq,
		 स्थिर काष्ठा qm_fd *fd),

	TP_ARGS(netdev, fq, fd)
);

/* Rx fd */
DEFINE_EVENT(dpaa_eth_fd, dpaa_rx_fd,

	TP_PROTO(काष्ठा net_device *netdev,
		 काष्ठा qman_fq *fq,
		 स्थिर काष्ठा qm_fd *fd),

	TP_ARGS(netdev, fq, fd)
);

/* Tx confirmation fd */
DEFINE_EVENT(dpaa_eth_fd, dpaa_tx_conf_fd,

	TP_PROTO(काष्ठा net_device *netdev,
		 काष्ठा qman_fq *fq,
		 स्थिर काष्ठा qm_fd *fd),

	TP_ARGS(netdev, fq, fd)
);

/* If only one event of a certain type needs to be declared, use TRACE_EVENT().
 * The syntax is the same as क्रम DECLARE_EVENT_CLASS().
 */

#पूर्ण_अगर /* _DPAA_ETH_TRACE_H */

/* This must be outside अगरdef _DPAA_ETH_TRACE_H */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता	dpaa_eth_trace
#समावेश <trace/define_trace.h>
