<शैली गुरु>
/*
 * Copyright (c) 2003-2008 Chelsio, Inc. All rights reserved.
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
#अगर_अघोषित _CXGB3_OFFLOAD_CTL_DEFS_H
#घोषणा _CXGB3_OFFLOAD_CTL_DEFS_H

क्रमागत अणु
	GET_MAX_OUTSTANDING_WR 	= 0,
	GET_TX_MAX_CHUNK	= 1,
	GET_TID_RANGE		= 2,
	GET_STID_RANGE		= 3,
	GET_RTBL_RANGE		= 4,
	GET_L2T_CAPACITY	= 5,
	GET_MTUS		= 6,
	GET_WR_LEN		= 7,
	GET_IFF_FROM_MAC	= 8,
	GET_DDP_PARAMS		= 9,
	GET_PORTS		= 10,

	ULP_ISCSI_GET_PARAMS	= 11,
	ULP_ISCSI_SET_PARAMS	= 12,

	RDMA_GET_PARAMS		= 13,
	RDMA_CQ_OP		= 14,
	RDMA_CQ_SETUP		= 15,
	RDMA_CQ_DISABLE		= 16,
	RDMA_CTRL_QP_SETUP	= 17,
	RDMA_GET_MEM		= 18,
	RDMA_GET_MIB		= 19,

	GET_RX_PAGE_INFO	= 50,
	GET_ISCSI_IPV4ADDR	= 51,

	GET_EMBEDDED_INFO	= 70,
पूर्ण;

/*
 * Structure used to describe a TID range.  Valid TIDs are [base, base+num).
 */
काष्ठा tid_range अणु
	अचिन्हित पूर्णांक base;	/* first TID */
	अचिन्हित पूर्णांक num;	/* number of TIDs in range */
पूर्ण;

/*
 * Structure used to request the size and contents of the MTU table.
 */
काष्ठा mtutab अणु
	अचिन्हित पूर्णांक size;	/* # of entries in the MTU table */
	स्थिर अचिन्हित लघु *mtus;	/* the MTU table values */
पूर्ण;

काष्ठा net_device;

/*
 * Structure used to request the adapter net_device owning a given MAC address.
 */
काष्ठा अगरf_mac अणु
	काष्ठा net_device *dev;	/* the net_device */
	स्थिर अचिन्हित अक्षर *mac_addr;	/* MAC address to lookup */
	u16 vlan_tag;
पूर्ण;

/* Structure used to request a port's iSCSI IPv4 address */
काष्ठा iscsi_ipv4addr अणु
	काष्ठा net_device *dev;	/* the net_device */
	__be32 ipv4addr;	/* the वापस iSCSI IPv4 address */
पूर्ण;

काष्ठा pci_dev;

/*
 * Structure used to request the TCP DDP parameters.
 */
काष्ठा ddp_params अणु
	अचिन्हित पूर्णांक llimit;	/* TDDP region start address */
	अचिन्हित पूर्णांक ulimit;	/* TDDP region end address */
	अचिन्हित पूर्णांक tag_mask;	/* TDDP tag mask */
	काष्ठा pci_dev *pdev;
पूर्ण;

काष्ठा adap_ports अणु
	अचिन्हित पूर्णांक nports;	/* number of ports on this adapter */
	काष्ठा net_device *lldevs[2];
पूर्ण;

/*
 * Structure used to वापस inक्रमmation to the iscsi layer.
 */
काष्ठा ulp_iscsi_info अणु
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक llimit;
	अचिन्हित पूर्णांक ulimit;
	अचिन्हित पूर्णांक tagmask;
	u8 pgsz_factor[4];
	अचिन्हित पूर्णांक max_rxsz;
	अचिन्हित पूर्णांक max_txsz;
	काष्ठा pci_dev *pdev;
पूर्ण;

/*
 * Structure used to वापस inक्रमmation to the RDMA layer.
 */
काष्ठा rdma_info अणु
	अचिन्हित पूर्णांक tpt_base;	/* TPT base address */
	अचिन्हित पूर्णांक tpt_top;	/* TPT last entry address */
	अचिन्हित पूर्णांक pbl_base;	/* PBL base address */
	अचिन्हित पूर्णांक pbl_top;	/* PBL last entry address */
	अचिन्हित पूर्णांक rqt_base;	/* RQT base address */
	अचिन्हित पूर्णांक rqt_top;	/* RQT last entry address */
	अचिन्हित पूर्णांक udbell_len;	/* user करोorbell region length */
	अचिन्हित दीर्घ udbell_physbase;	/* user करोorbell physical start addr */
	व्योम __iomem *kdb_addr;	/* kernel करोorbell रेजिस्टर address */
	काष्ठा pci_dev *pdev;	/* associated PCI device */
पूर्ण;

/*
 * Structure used to request an operation on an RDMA completion queue.
 */
काष्ठा rdma_cq_op अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित पूर्णांक op;
	अचिन्हित पूर्णांक credits;
पूर्ण;

/*
 * Structure used to setup RDMA completion queues.
 */
काष्ठा rdma_cq_setup अणु
	अचिन्हित पूर्णांक id;
	अचिन्हित दीर्घ दीर्घ base_addr;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक credits;
	अचिन्हित पूर्णांक credit_thres;
	अचिन्हित पूर्णांक ovfl_mode;
पूर्ण;

/*
 * Structure used to setup the RDMA control egress context.
 */
काष्ठा rdma_ctrlqp_setup अणु
	अचिन्हित दीर्घ दीर्घ base_addr;
	अचिन्हित पूर्णांक size;
पूर्ण;

/*
 * Offload TX/RX page inक्रमmation.
 */
काष्ठा ofld_page_info अणु
	अचिन्हित पूर्णांक page_size;  /* Page size, should be a घातer of 2 */
	अचिन्हित पूर्णांक num;        /* Number of pages */
पूर्ण;

/*
 * Structure used to get firmware and protocol engine versions.
 */
काष्ठा ch_embedded_info अणु
	u32 fw_vers;
	u32 tp_vers;
पूर्ण;
#पूर्ण_अगर				/* _CXGB3_OFFLOAD_CTL_DEFS_H */
