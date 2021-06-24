<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file is based on code from OCTEON SDK by Cavium Networks.
 *
 * Copyright (c) 2003-2007 Cavium Networks
 */

/*
 * A few defines are used to control the operation of this driver:
 *  USE_ASYNC_IOBDMA
 *      Use asynchronous IO access to hardware. This uses Octeon's asynchronous
 *      IOBDMAs to issue IO accesses without stalling. Set this to zero
 *      to disable this. Note that IOBDMAs require CVMSEG.
 *  REUSE_SKBUFFS_WITHOUT_FREE
 *      Allows the TX path to मुक्त an skbuff पूर्णांकo the FPA hardware pool. This
 *      can signअगरicantly improve perक्रमmance क्रम क्रमwarding and bridging, but
 *      may be somewhat dangerous. Checks are made, but अगर any buffer is reused
 *      without the proper Linux cleanup, the networking stack may have very
 *      bizarre bugs.
 */
#अगर_अघोषित __ETHERNET_DEFINES_H__
#घोषणा __ETHERNET_DEFINES_H__

#अगर_घोषित CONFIG_NETFILTER
#घोषणा REUSE_SKBUFFS_WITHOUT_FREE	0
#अन्यथा
#घोषणा REUSE_SKBUFFS_WITHOUT_FREE	1
#पूर्ण_अगर

#घोषणा USE_ASYNC_IOBDMA		(CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE > 0)

/* Maximum number of SKBs to try to मुक्त per xmit packet. */
#घोषणा MAX_OUT_QUEUE_DEPTH		1000

#घोषणा FAU_TOTAL_TX_TO_CLEAN (CVMX_FAU_REG_END - माप(u32))
#घोषणा FAU_NUM_PACKET_BUFFERS_TO_FREE (FAU_TOTAL_TX_TO_CLEAN - माप(u32))

#घोषणा TOTAL_NUMBER_OF_PORTS		(CVMX_PIP_NUM_INPUT_PORTS + 1)

#पूर्ण_अगर /* __ETHERNET_DEFINES_H__ */
