<शैली गुरु>
/*
 * Copyright (c) 2004-2008 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#अगर_अघोषित _FIRMWARE_EXPORTS_H_
#घोषणा _FIRMWARE_EXPORTS_H_

/* WR OPCODES supported by the firmware.
 */
#घोषणा	FW_WROPCODE_FORWARD			0x01
#घोषणा FW_WROPCODE_BYPASS			0x05

#घोषणा FW_WROPCODE_TUNNEL_TX_PKT		0x03

#घोषणा FW_WROPOCDE_ULPTX_DATA_SGL		0x00
#घोषणा FW_WROPCODE_ULPTX_MEM_READ		0x02
#घोषणा FW_WROPCODE_ULPTX_PKT			0x04
#घोषणा FW_WROPCODE_ULPTX_INVALIDATE		0x06

#घोषणा FW_WROPCODE_TUNNEL_RX_PKT		0x07

#घोषणा FW_WROPCODE_OFLD_GETTCB_RPL		0x08
#घोषणा FW_WROPCODE_OFLD_CLOSE_CON		0x09
#घोषणा FW_WROPCODE_OFLD_TP_ABORT_CON_REQ	0x0A
#घोषणा FW_WROPCODE_OFLD_HOST_ABORT_CON_RPL	0x0F
#घोषणा FW_WROPCODE_OFLD_HOST_ABORT_CON_REQ	0x0B
#घोषणा FW_WROPCODE_OFLD_TP_ABORT_CON_RPL	0x0C
#घोषणा FW_WROPCODE_OFLD_TX_DATA		0x0D
#घोषणा FW_WROPCODE_OFLD_TX_DATA_ACK		0x0E

#घोषणा FW_WROPCODE_RI_RDMA_INIT		0x10
#घोषणा FW_WROPCODE_RI_RDMA_WRITE		0x11
#घोषणा FW_WROPCODE_RI_RDMA_READ_REQ		0x12
#घोषणा FW_WROPCODE_RI_RDMA_READ_RESP		0x13
#घोषणा FW_WROPCODE_RI_SEND			0x14
#घोषणा FW_WROPCODE_RI_TERMINATE		0x15
#घोषणा FW_WROPCODE_RI_RDMA_READ		0x16
#घोषणा FW_WROPCODE_RI_RECEIVE			0x17
#घोषणा FW_WROPCODE_RI_BIND_MW			0x18
#घोषणा FW_WROPCODE_RI_FASTREGISTER_MR		0x19
#घोषणा FW_WROPCODE_RI_LOCAL_INV		0x1A
#घोषणा FW_WROPCODE_RI_MODIFY_QP		0x1B
#घोषणा FW_WROPCODE_RI_BYPASS			0x1C

#घोषणा FW_WROPOCDE_RSVD			0x1E

#घोषणा FW_WROPCODE_SGE_EGRESSCONTEXT_RR	0x1F

#घोषणा FW_WROPCODE_MNGT			0x1D
#घोषणा FW_MNGTOPCODE_PKTSCHED_SET		0x00

/* Maximum size of a WR sent from the host, limited by the SGE.
 *
 * Note: WR coming from ULP or TP are only limited by CIM.
 */
#घोषणा FW_WR_SIZE			128

/* Maximum number of outstanding WRs sent from the host. Value must be
 * programmed in the CTRL/TUNNEL/QP SGE Egress Context and used by
 * offload modules to limit the number of WRs per connection.
 */
#घोषणा FW_T3_WR_NUM			16
#घोषणा FW_N3_WR_NUM			7

#अगर_अघोषित N3
# define FW_WR_NUM			FW_T3_WR_NUM
#अन्यथा
# define FW_WR_NUM			FW_N3_WR_NUM
#पूर्ण_अगर

/* FW_TUNNEL_NUM corresponds to the number of supported TUNNEL Queues. These
 * queues must start at SGE Egress Context FW_TUNNEL_SGEEC_START and must
 * start at 'TID' (or 'uP Token') FW_TUNNEL_TID_START.
 *
 * Ingress Traffic (e.g. DMA completion credit)  क्रम TUNNEL Queue[i] is sent
 * to RESP Queue[i].
 */
#घोषणा FW_TUNNEL_NUM			8
#घोषणा FW_TUNNEL_SGEEC_START		8
#घोषणा FW_TUNNEL_TID_START		65544

/* FW_CTRL_NUM corresponds to the number of supported CTRL Queues. These queues
 * must start at SGE Egress Context FW_CTRL_SGEEC_START and must start at 'TID'
 * (or 'uP Token') FW_CTRL_TID_START.
 *
 * Ingress Traffic क्रम CTRL Queue[i] is sent to RESP Queue[i].
 */
#घोषणा FW_CTRL_NUM			8
#घोषणा FW_CTRL_SGEEC_START		65528
#घोषणा FW_CTRL_TID_START		65536

/* FW_OFLD_NUM corresponds to the number of supported OFFLOAD Queues. These
 * queues must start at SGE Egress Context FW_OFLD_SGEEC_START.
 *
 * Note: the 'uP Token' in the SGE Egress Context fields is irrelevant क्रम
 * OFFLOAD Queues, as the host is responsible क्रम providing the correct TID in
 * every WR.
 *
 * Ingress Trafffic क्रम OFFLOAD Queue[i] is sent to RESP Queue[i].
 */
#घोषणा FW_OFLD_NUM			8
#घोषणा FW_OFLD_SGEEC_START		0

/*
 *
 */
#घोषणा FW_RI_NUM			1
#घोषणा FW_RI_SGEEC_START		65527
#घोषणा FW_RI_TID_START			65552

/*
 * The RX_PKT_TID
 */
#घोषणा FW_RX_PKT_NUM			1
#घोषणा FW_RX_PKT_TID_START		65553

/* FW_WRC_NUM corresponds to the number of Work Request Context that supported
 * by the firmware.
 */
#घोषणा FW_WRC_NUM			\
    (65536 + FW_TUNNEL_NUM + FW_CTRL_NUM + FW_RI_NUM + FW_RX_PKT_NUM)

/*
 * FW type and version.
 */
#घोषणा S_FW_VERSION_TYPE		28
#घोषणा M_FW_VERSION_TYPE		0xF
#घोषणा V_FW_VERSION_TYPE(x)		((x) << S_FW_VERSION_TYPE)
#घोषणा G_FW_VERSION_TYPE(x)		\
    (((x) >> S_FW_VERSION_TYPE) & M_FW_VERSION_TYPE)

#घोषणा S_FW_VERSION_MAJOR		16
#घोषणा M_FW_VERSION_MAJOR		0xFFF
#घोषणा V_FW_VERSION_MAJOR(x)		((x) << S_FW_VERSION_MAJOR)
#घोषणा G_FW_VERSION_MAJOR(x)		\
    (((x) >> S_FW_VERSION_MAJOR) & M_FW_VERSION_MAJOR)

#घोषणा S_FW_VERSION_MINOR		8
#घोषणा M_FW_VERSION_MINOR		0xFF
#घोषणा V_FW_VERSION_MINOR(x)		((x) << S_FW_VERSION_MINOR)
#घोषणा G_FW_VERSION_MINOR(x)		\
    (((x) >> S_FW_VERSION_MINOR) & M_FW_VERSION_MINOR)

#घोषणा S_FW_VERSION_MICRO		0
#घोषणा M_FW_VERSION_MICRO		0xFF
#घोषणा V_FW_VERSION_MICRO(x)		((x) << S_FW_VERSION_MICRO)
#घोषणा G_FW_VERSION_MICRO(x)		\
    (((x) >> S_FW_VERSION_MICRO) & M_FW_VERSION_MICRO)

#पूर्ण_अगर				/* _FIRMWARE_EXPORTS_H_ */
