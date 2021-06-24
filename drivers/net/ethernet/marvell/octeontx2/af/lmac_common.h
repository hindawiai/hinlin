<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RPM driver
 *
 * Copyright (C) 2020 Marvell.
 */

#अगर_अघोषित LMAC_COMMON_H
#घोषणा LMAC_COMMON_H

#समावेश "rvu.h"
#समावेश "cgx.h"
/**
 * काष्ठा lmac
 * @wq_cmd_cmplt:	रुकोq to keep the process blocked until cmd completion
 * @cmd_lock:		Lock to serialize the command पूर्णांकerface
 * @resp:		command response
 * @link_info:		link related inक्रमmation
 * @event_cb:		callback क्रम linkchange events
 * @event_cb_lock:	lock क्रम serializing callback with unरेजिस्टर
 * @cmd_pend:		flag set beक्रमe new command is started
 *			flag cleared after command response is received
 * @cgx:		parent cgx port
 * @lmac_id:		lmac port id
 * @name:		lmac port name
 */
काष्ठा lmac अणु
	रुको_queue_head_t wq_cmd_cmplt;
	/* Lock to serialize the command पूर्णांकerface */
	काष्ठा mutex cmd_lock;
	u64 resp;
	काष्ठा cgx_link_user_info link_info;
	काष्ठा cgx_event_cb event_cb;
	/* lock क्रम serializing callback with unरेजिस्टर */
	spinlock_t event_cb_lock;
	bool cmd_pend;
	काष्ठा cgx *cgx;
	u8 lmac_id;
	अक्षर *name;
पूर्ण;

/* CGX & RPM has dअगरferent feature set
 * update the काष्ठाure fields with dअगरferent one
 */
काष्ठा mac_ops अणु
	अक्षर		       *name;
	/* Features like RXSTAT, TXSTAT, DMAC FILTER csrs dअगरfers by fixed
	 * bar offset क्रम example
	 * CGX DMAC_CTL0  0x1f8
	 * RPM DMAC_CTL0  0x4ff8
	 */
	u64			csr_offset;
	/* For ATF to send events to kernel, there is no dedicated पूर्णांकerrupt
	 * defined hence CGX uses OVERFLOW bit in CMR_INT. RPM block supports
	 * SW_INT so that ATF triggers this पूर्णांकerrupt after processing of
	 * requested command
	 */
	u64			पूर्णांक_रेजिस्टर;
	u64			पूर्णांक_set_reg;
	/* lmac offset is dअगरferent is RPM */
	u8			lmac_offset;
	u8			irq_offset;
	u8			पूर्णांक_ena_bit;
	u8			lmac_fwi;
	u32			fअगरo_len;
	bool			non_contiguous_serdes_lane;
	/* RPM & CGX dअगरfers in number of Receive/transmit stats */
	u8			rx_stats_cnt;
	u8			tx_stats_cnt;
	/* Inहाल of RPM get number of lmacs from RPMX_CMR_RX_LMACS[LMAC_EXIST]
	 * number of setbits in lmac_exist tells number of lmacs
	 */
	पूर्णांक			(*get_nr_lmacs)(व्योम *cgx);
	u8                      (*get_lmac_type)(व्योम *cgx, पूर्णांक lmac_id);
	पूर्णांक                     (*mac_lmac_पूर्णांकl_lbk)(व्योम *cgx, पूर्णांक lmac_id,
						     bool enable);
	/* Register Stats related functions */
	पूर्णांक			(*mac_get_rx_stats)(व्योम *cgx, पूर्णांक lmac_id,
						    पूर्णांक idx, u64 *rx_stat);
	पूर्णांक			(*mac_get_tx_stats)(व्योम *cgx, पूर्णांक lmac_id,
						    पूर्णांक idx, u64 *tx_stat);

	/* Enable LMAC Pause Frame Configuration */
	व्योम			(*mac_enadis_rx_छोड़ो_fwding)(व्योम *cgxd,
							      पूर्णांक lmac_id,
							      bool enable);

	पूर्णांक			(*mac_get_छोड़ो_frm_status)(व्योम *cgxd,
							    पूर्णांक lmac_id,
							    u8 *tx_छोड़ो,
							    u8 *rx_छोड़ो);

	पूर्णांक			(*mac_enadis_छोड़ो_frm)(व्योम *cgxd,
							पूर्णांक lmac_id,
							u8 tx_छोड़ो,
							u8 rx_छोड़ो);

	व्योम			(*mac_छोड़ो_frm_config)(व्योम  *cgxd,
							पूर्णांक lmac_id,
							bool enable);
पूर्ण;

काष्ठा cgx अणु
	व्योम __iomem		*reg_base;
	काष्ठा pci_dev		*pdev;
	u8			cgx_id;
	u8			lmac_count;
	काष्ठा lmac		*lmac_idmap[MAX_LMAC_PER_CGX];
	काष्ठा			work_काष्ठा cgx_cmd_work;
	काष्ठा			workqueue_काष्ठा *cgx_cmd_workq;
	काष्ठा list_head	cgx_list;
	u64			hw_features;
	काष्ठा mac_ops		*mac_ops;
	अचिन्हित दीर्घ		lmac_bmap; /* biपंचांगap of enabled lmacs */
	/* Lock to serialize पढ़ो/ग_लिखो of global csrs like
	 * RPMX_MTI_STAT_DATA_HI_CDC etc
	 */
	काष्ठा mutex		lock;
पूर्ण;

प्रकार काष्ठा cgx rpm_t;

/* Function Declarations */
व्योम cgx_ग_लिखो(काष्ठा cgx *cgx, u64 lmac, u64 offset, u64 val);
u64 cgx_पढ़ो(काष्ठा cgx *cgx, u64 lmac, u64 offset);
काष्ठा lmac *lmac_pdata(u8 lmac_id, काष्ठा cgx *cgx);
पूर्णांक cgx_fwi_cmd_send(u64 req, u64 *resp, काष्ठा lmac *lmac);
पूर्णांक cgx_fwi_cmd_generic(u64 req, u64 *resp, काष्ठा cgx *cgx, पूर्णांक lmac_id);
bool is_lmac_valid(काष्ठा cgx *cgx, पूर्णांक lmac_id);
काष्ठा mac_ops *rpm_get_mac_ops(व्योम);

#पूर्ण_अगर /* LMAC_COMMON_H */
