<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/* Copyright 2014-2015 Freescale Semiconductor Inc.
 */

#अघोषित TRACE_SYSTEM
#घोषणा TRACE_SYSTEM	dpaa2_eth

#अगर !defined(_DPAA2_ETH_TRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#घोषणा _DPAA2_ETH_TRACE_H

#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/tracepoपूर्णांक.h>

#घोषणा TR_FMT "[%s] fd: addr=0x%llx, len=%u, off=%u"
/* trace_prपूर्णांकk क्रमmat क्रम raw buffer event class */
#घोषणा TR_BUF_FMT "[%s] vaddr=%p size=%zu dma_addr=%pad map_size=%zu bpid=%d"

/* This is used to declare a class of events.
 * inभागidual events of this type will be defined below.
 */

/* Store details about a frame descriptor */
DECLARE_EVENT_CLASS(dpaa2_eth_fd,
		    /* Trace function prototype */
		    TP_PROTO(काष्ठा net_device *netdev,
			     स्थिर काष्ठा dpaa2_fd *fd),

		    /* Repeat argument list here */
		    TP_ARGS(netdev, fd),

		    /* A काष्ठाure containing the relevant inक्रमmation we want
		     * to record. Declare name and type क्रम each normal element,
		     * name, type and size क्रम arrays. Use __string क्रम variable
		     * length strings.
		     */
		    TP_STRUCT__entry(
				     __field(u64, fd_addr)
				     __field(u32, fd_len)
				     __field(u16, fd_offset)
				     __string(name, netdev->name)
		    ),

		    /* The function that assigns values to the above declared
		     * fields
		     */
		    TP_fast_assign(
				   __entry->fd_addr = dpaa2_fd_get_addr(fd);
				   __entry->fd_len = dpaa2_fd_get_len(fd);
				   __entry->fd_offset = dpaa2_fd_get_offset(fd);
				   __assign_str(name, netdev->name);
		    ),

		    /* This is what माला_लो prपूर्णांकed when the trace event is
		     * triggered.
		     */
		    TP_prपूर्णांकk(TR_FMT,
			      __get_str(name),
			      __entry->fd_addr,
			      __entry->fd_len,
			      __entry->fd_offset)
);

/* Now declare events of the above type. Format is:
 * DEFINE_EVENT(class, name, proto, args), with proto and args same as क्रम class
 */

/* Tx (egress) fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_tx_fd,
	     TP_PROTO(काष्ठा net_device *netdev,
		      स्थिर काष्ठा dpaa2_fd *fd),

	     TP_ARGS(netdev, fd)
);

/* Rx fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_rx_fd,
	     TP_PROTO(काष्ठा net_device *netdev,
		      स्थिर काष्ठा dpaa2_fd *fd),

	     TP_ARGS(netdev, fd)
);

/* Tx confirmation fd */
DEFINE_EVENT(dpaa2_eth_fd, dpaa2_tx_conf_fd,
	     TP_PROTO(काष्ठा net_device *netdev,
		      स्थिर काष्ठा dpaa2_fd *fd),

	     TP_ARGS(netdev, fd)
);

/* Log data about raw buffers. Useful क्रम tracing DPBP content. */
TRACE_EVENT(dpaa2_eth_buf_seed,
	    /* Trace function prototype */
	    TP_PROTO(काष्ठा net_device *netdev,
		     /* भव address and size */
		     व्योम *vaddr,
		     माप_प्रकार size,
		     /* dma map address and size */
		     dma_addr_t dma_addr,
		     माप_प्रकार map_size,
		     /* buffer pool id, अगर relevant */
		     u16 bpid),

	    /* Repeat argument list here */
	    TP_ARGS(netdev, vaddr, size, dma_addr, map_size, bpid),

	    /* A काष्ठाure containing the relevant inक्रमmation we want
	     * to record. Declare name and type क्रम each normal element,
	     * name, type and size क्रम arrays. Use __string क्रम variable
	     * length strings.
	     */
	    TP_STRUCT__entry(
			     __field(व्योम *, vaddr)
			     __field(माप_प्रकार, size)
			     __field(dma_addr_t, dma_addr)
			     __field(माप_प्रकार, map_size)
			     __field(u16, bpid)
			     __string(name, netdev->name)
	    ),

	    /* The function that assigns values to the above declared
	     * fields
	     */
	    TP_fast_assign(
			   __entry->vaddr = vaddr;
			   __entry->size = size;
			   __entry->dma_addr = dma_addr;
			   __entry->map_size = map_size;
			   __entry->bpid = bpid;
			   __assign_str(name, netdev->name);
	    ),

	    /* This is what माला_लो prपूर्णांकed when the trace event is
	     * triggered.
	     */
	    TP_prपूर्णांकk(TR_BUF_FMT,
		      __get_str(name),
		      __entry->vaddr,
		      __entry->size,
		      &__entry->dma_addr,
		      __entry->map_size,
		      __entry->bpid)
);

/* If only one event of a certain type needs to be declared, use TRACE_EVENT().
 * The syntax is the same as क्रम DECLARE_EVENT_CLASS().
 */

#पूर्ण_अगर /* _DPAA2_ETH_TRACE_H */

/* This must be outside अगरdef _DPAA2_ETH_TRACE_H */
#अघोषित TRACE_INCLUDE_PATH
#घोषणा TRACE_INCLUDE_PATH .
#अघोषित TRACE_INCLUDE_खाता
#घोषणा TRACE_INCLUDE_खाता	dpaa2-eth-trace
#समावेश <trace/define_trace.h>
