<शैली गुरु>
/*
 * cxgb3i.h: Chelsio S3xx iSCSI driver.
 *
 * Copyright (c) 2008-2015 Chelsio Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Karen Xie (kxie@chelsio.com)
 */

#अगर_अघोषित __CXGB3I_H__
#घोषणा __CXGB3I_H__

#घोषणा CXGB3I_SCSI_HOST_QDEPTH 1024
#घोषणा CXGB3I_MAX_LUN		512
#घोषणा ISCSI_PDU_NONPAYLOAD_MAX \
	(माप(काष्ठा iscsi_hdr) + ISCSI_MAX_AHS_SIZE + 2*ISCSI_DIGEST_SIZE)

/*क्रम TX: a skb must have a headroom of at least TX_HEADER_LEN bytes */
#घोषणा CXGB3I_TX_HEADER_LEN \
	(माप(काष्ठा tx_data_wr) + माप(काष्ठा sge_opaque_hdr))

बाह्य cxgb3_cpl_handler_func cxgb3i_cpl_handlers[NUM_CPL_CMDS];

अटल अंतरभूत अचिन्हित पूर्णांक cxgb3i_get_निजी_ipv4addr(काष्ठा net_device *ndev)
अणु
	वापस ((काष्ठा port_info *)(netdev_priv(ndev)))->iscsi_ipv4addr;
पूर्ण

अटल अंतरभूत व्योम cxgb3i_set_निजी_ipv4addr(काष्ठा net_device *ndev,
						अचिन्हित पूर्णांक addr)
अणु
	काष्ठा port_info *pi =  (काष्ठा port_info *)netdev_priv(ndev);

	pi->iscsic.flags = addr ? 1 : 0;
	pi->iscsi_ipv4addr = addr;
	अगर (addr)
		स_नकल(pi->iscsic.mac_addr, ndev->dev_addr, ETH_ALEN);
पूर्ण

काष्ठा cpl_iscsi_hdr_norss अणु
	जोड़ opcode_tid ot;
	u16 pdu_len_ddp;
	u16 len;
	u32 seq;
	u16 urg;
	u8 rsvd;
	u8 status;
पूर्ण;

काष्ठा cpl_rx_data_ddp_norss अणु
	जोड़ opcode_tid ot;
	u16 urg;
	u16 len;
	u32 seq;
	u32 nxt_seq;
	u32 ulp_crc;
	u32 ddp_status;
पूर्ण;
#पूर्ण_अगर
