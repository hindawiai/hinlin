<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 2019 Texas Instruments Incorporated - http://www.ti.com
 */

#अगर_अघोषित K3_UDMA_H_
#घोषणा K3_UDMA_H_

#समावेश <linux/soc/ti/ti_sci_protocol.h>

/* Global रेजिस्टरs */
#घोषणा UDMA_REV_REG			0x0
#घोषणा UDMA_PERF_CTL_REG		0x4
#घोषणा UDMA_EMU_CTL_REG		0x8
#घोषणा UDMA_PSIL_TO_REG		0x10
#घोषणा UDMA_UTC_CTL_REG		0x1c
#घोषणा UDMA_CAP_REG(i)			(0x20 + ((i) * 4))
#घोषणा UDMA_RX_FLOW_ID_FW_OES_REG	0x80
#घोषणा UDMA_RX_FLOW_ID_FW_STATUS_REG	0x88

/* BCHANRT/TCHANRT/RCHANRT रेजिस्टरs */
#घोषणा UDMA_CHAN_RT_CTL_REG		0x0
#घोषणा UDMA_CHAN_RT_SWTRIG_REG		0x8
#घोषणा UDMA_CHAN_RT_STDATA_REG		0x80

#घोषणा UDMA_CHAN_RT_PEER_REG(i)	(0x200 + ((i) * 0x4))
#घोषणा UDMA_CHAN_RT_PEER_STATIC_TR_XY_REG	\
	UDMA_CHAN_RT_PEER_REG(0)	/* PSI-L: 0x400 */
#घोषणा UDMA_CHAN_RT_PEER_STATIC_TR_Z_REG	\
	UDMA_CHAN_RT_PEER_REG(1)	/* PSI-L: 0x401 */
#घोषणा UDMA_CHAN_RT_PEER_BCNT_REG		\
	UDMA_CHAN_RT_PEER_REG(4)	/* PSI-L: 0x404 */
#घोषणा UDMA_CHAN_RT_PEER_RT_EN_REG		\
	UDMA_CHAN_RT_PEER_REG(8)	/* PSI-L: 0x408 */

#घोषणा UDMA_CHAN_RT_PCNT_REG		0x400
#घोषणा UDMA_CHAN_RT_BCNT_REG		0x408
#घोषणा UDMA_CHAN_RT_SBCNT_REG		0x410

/* UDMA_CAP Registers */
#घोषणा UDMA_CAP2_TCHAN_CNT(val)	((val) & 0x1ff)
#घोषणा UDMA_CAP2_ECHAN_CNT(val)	(((val) >> 9) & 0x1ff)
#घोषणा UDMA_CAP2_RCHAN_CNT(val)	(((val) >> 18) & 0x1ff)
#घोषणा UDMA_CAP3_RFLOW_CNT(val)	((val) & 0x3fff)
#घोषणा UDMA_CAP3_HCHAN_CNT(val)	(((val) >> 14) & 0x1ff)
#घोषणा UDMA_CAP3_UCHAN_CNT(val)	(((val) >> 23) & 0x1ff)

#घोषणा BCDMA_CAP2_BCHAN_CNT(val)	((val) & 0x1ff)
#घोषणा BCDMA_CAP2_TCHAN_CNT(val)	(((val) >> 9) & 0x1ff)
#घोषणा BCDMA_CAP2_RCHAN_CNT(val)	(((val) >> 18) & 0x1ff)
#घोषणा BCDMA_CAP3_HBCHAN_CNT(val)	(((val) >> 14) & 0x1ff)
#घोषणा BCDMA_CAP3_UBCHAN_CNT(val)	(((val) >> 23) & 0x1ff)
#घोषणा BCDMA_CAP4_HRCHAN_CNT(val)	((val) & 0xff)
#घोषणा BCDMA_CAP4_URCHAN_CNT(val)	(((val) >> 8) & 0xff)
#घोषणा BCDMA_CAP4_HTCHAN_CNT(val)	(((val) >> 16) & 0xff)
#घोषणा BCDMA_CAP4_UTCHAN_CNT(val)	(((val) >> 24) & 0xff)

#घोषणा PKTDMA_CAP4_TFLOW_CNT(val)	((val) & 0x3fff)

/* UDMA_CHAN_RT_CTL_REG */
#घोषणा UDMA_CHAN_RT_CTL_EN		BIT(31)
#घोषणा UDMA_CHAN_RT_CTL_TDOWN		BIT(30)
#घोषणा UDMA_CHAN_RT_CTL_PAUSE		BIT(29)
#घोषणा UDMA_CHAN_RT_CTL_FTDOWN		BIT(28)
#घोषणा UDMA_CHAN_RT_CTL_ERROR		BIT(0)

/* UDMA_CHAN_RT_PEER_RT_EN_REG */
#घोषणा UDMA_PEER_RT_EN_ENABLE		BIT(31)
#घोषणा UDMA_PEER_RT_EN_TEARDOWN	BIT(30)
#घोषणा UDMA_PEER_RT_EN_PAUSE		BIT(29)
#घोषणा UDMA_PEER_RT_EN_FLUSH		BIT(28)
#घोषणा UDMA_PEER_RT_EN_IDLE		BIT(1)

/*
 * UDMA_TCHAN_RT_PEER_STATIC_TR_XY_REG /
 * UDMA_RCHAN_RT_PEER_STATIC_TR_XY_REG
 */
#घोषणा PDMA_STATIC_TR_X_MASK		GENMASK(26, 24)
#घोषणा PDMA_STATIC_TR_X_SHIFT		(24)
#घोषणा PDMA_STATIC_TR_Y_MASK		GENMASK(11, 0)
#घोषणा PDMA_STATIC_TR_Y_SHIFT		(0)

#घोषणा PDMA_STATIC_TR_Y(x)	\
	(((x) << PDMA_STATIC_TR_Y_SHIFT) & PDMA_STATIC_TR_Y_MASK)
#घोषणा PDMA_STATIC_TR_X(x)	\
	(((x) << PDMA_STATIC_TR_X_SHIFT) & PDMA_STATIC_TR_X_MASK)

#घोषणा PDMA_STATIC_TR_XY_ACC32		BIT(30)
#घोषणा PDMA_STATIC_TR_XY_BURST		BIT(31)

/*
 * UDMA_TCHAN_RT_PEER_STATIC_TR_Z_REG /
 * UDMA_RCHAN_RT_PEER_STATIC_TR_Z_REG
 */
#घोषणा PDMA_STATIC_TR_Z(x, mask)	((x) & (mask))

/* Address Space Select */
#घोषणा K3_ADDRESS_ASEL_SHIFT		48

काष्ठा udma_dev;
काष्ठा udma_tchan;
काष्ठा udma_rchan;
काष्ठा udma_rflow;

क्रमागत udma_rm_range अणु
	RM_RANGE_BCHAN = 0,
	RM_RANGE_TCHAN,
	RM_RANGE_RCHAN,
	RM_RANGE_RFLOW,
	RM_RANGE_TFLOW,
	RM_RANGE_LAST,
पूर्ण;

काष्ठा udma_tisci_rm अणु
	स्थिर काष्ठा ti_sci_handle *tisci;
	स्थिर काष्ठा ti_sci_rm_udmap_ops *tisci_udmap_ops;
	u32  tisci_dev_id;

	/* tisci inक्रमmation क्रम PSI-L thपढ़ो pairing/unpairing */
	स्थिर काष्ठा ti_sci_rm_psil_ops *tisci_psil_ops;
	u32  tisci_navss_dev_id;

	काष्ठा ti_sci_resource *rm_ranges[RM_RANGE_LAST];
पूर्ण;

/* Direct access to UDMA low lever resources क्रम the glue layer */
पूर्णांक xudma_navss_psil_pair(काष्ठा udma_dev *ud, u32 src_thपढ़ो, u32 dst_thपढ़ो);
पूर्णांक xudma_navss_psil_unpair(काष्ठा udma_dev *ud, u32 src_thपढ़ो,
			    u32 dst_thपढ़ो);

काष्ठा udma_dev *of_xudma_dev_get(काष्ठा device_node *np, स्थिर अक्षर *property);
काष्ठा device *xudma_get_device(काष्ठा udma_dev *ud);
काष्ठा k3_ringacc *xudma_get_ringacc(काष्ठा udma_dev *ud);
व्योम xudma_dev_put(काष्ठा udma_dev *ud);
u32 xudma_dev_get_psil_base(काष्ठा udma_dev *ud);
काष्ठा udma_tisci_rm *xudma_dev_get_tisci_rm(काष्ठा udma_dev *ud);

पूर्णांक xudma_alloc_gp_rflow_range(काष्ठा udma_dev *ud, पूर्णांक from, पूर्णांक cnt);
पूर्णांक xudma_मुक्त_gp_rflow_range(काष्ठा udma_dev *ud, पूर्णांक from, पूर्णांक cnt);

काष्ठा udma_tchan *xudma_tchan_get(काष्ठा udma_dev *ud, पूर्णांक id);
काष्ठा udma_rchan *xudma_rchan_get(काष्ठा udma_dev *ud, पूर्णांक id);
काष्ठा udma_rflow *xudma_rflow_get(काष्ठा udma_dev *ud, पूर्णांक id);

व्योम xudma_tchan_put(काष्ठा udma_dev *ud, काष्ठा udma_tchan *p);
व्योम xudma_rchan_put(काष्ठा udma_dev *ud, काष्ठा udma_rchan *p);
व्योम xudma_rflow_put(काष्ठा udma_dev *ud, काष्ठा udma_rflow *p);

पूर्णांक xudma_tchan_get_id(काष्ठा udma_tchan *p);
पूर्णांक xudma_rchan_get_id(काष्ठा udma_rchan *p);
पूर्णांक xudma_rflow_get_id(काष्ठा udma_rflow *p);

u32 xudma_tchanrt_पढ़ो(काष्ठा udma_tchan *tchan, पूर्णांक reg);
व्योम xudma_tchanrt_ग_लिखो(काष्ठा udma_tchan *tchan, पूर्णांक reg, u32 val);
u32 xudma_rchanrt_पढ़ो(काष्ठा udma_rchan *rchan, पूर्णांक reg);
व्योम xudma_rchanrt_ग_लिखो(काष्ठा udma_rchan *rchan, पूर्णांक reg, u32 val);
bool xudma_rflow_is_gp(काष्ठा udma_dev *ud, पूर्णांक id);
पूर्णांक xudma_get_rflow_ring_offset(काष्ठा udma_dev *ud);

पूर्णांक xudma_is_pktdma(काष्ठा udma_dev *ud);

पूर्णांक xudma_pktdma_tflow_get_irq(काष्ठा udma_dev *ud, पूर्णांक udma_tflow_id);
पूर्णांक xudma_pktdma_rflow_get_irq(काष्ठा udma_dev *ud, पूर्णांक udma_rflow_id);
#पूर्ण_अगर /* K3_UDMA_H_ */
