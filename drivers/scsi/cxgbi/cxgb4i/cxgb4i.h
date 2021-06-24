<शैली गुरु>
/*
 * cxgb4i.h: Chelsio T4 iSCSI driver.
 *
 * Copyright (c) 2010-2015 Chelsio Communications, Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Karen Xie (kxie@chelsio.com)
 * Written by: Rakesh Ranjan (rranjan@chelsio.com)
 */

#अगर_अघोषित	__CXGB4I_H__
#घोषणा	__CXGB4I_H__

#घोषणा	CXGB4I_SCSI_HOST_QDEPTH	1024
#घोषणा	CXGB4I_MAX_CONN		16384
#घोषणा	CXGB4I_MAX_TARGET	CXGB4I_MAX_CONN
#घोषणा	CXGB4I_MAX_LUN		0x1000

/* क्रम TX: a skb must have a headroom of at least TX_HEADER_LEN bytes */
#घोषणा CXGB4I_TX_HEADER_LEN \
	(माप(काष्ठा fw_ofld_tx_data_wr) + माप(काष्ठा sge_opaque_hdr))

#घोषणा T5_ISS_VALID		(1 << 18)

#पूर्ण_अगर	/* __CXGB4I_H__ */
