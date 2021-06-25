<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*  Marvell OcteonTx2 RPM driver
 *
 * Copyright (C) 2020 Marvell.
 *
 */

#अगर_अघोषित RPM_H
#घोषणा RPM_H

#समावेश <linux/bits.h>

/* PCI device IDs */
#घोषणा PCI_DEVID_CN10K_RPM		0xA060

/* Registers */
#घोषणा RPMX_CMRX_SW_INT                0x180
#घोषणा RPMX_CMRX_SW_INT_W1S            0x188
#घोषणा RPMX_CMRX_SW_INT_ENA_W1S        0x198
#घोषणा RPMX_CMRX_LINK_CFG		0x1070
#घोषणा RPMX_MTI_PCS100X_CONTROL1       0x20000
#घोषणा RPMX_MTI_LPCSX_CONTROL1         0x30000
#घोषणा RPMX_MTI_PCS_LBK                BIT_ULL(14)
#घोषणा RPMX_MTI_LPCSX_CONTROL(id)     (0x30000 | ((id) * 0x100))

#घोषणा RPMX_CMRX_LINK_RANGE_MASK	GENMASK_ULL(19, 16)
#घोषणा RPMX_CMRX_LINK_BASE_MASK	GENMASK_ULL(11, 0)
#घोषणा RPMX_MTI_MAC100X_COMMAND_CONFIG	0x8010
#घोषणा RPMX_MTI_MAC100X_COMMAND_CONFIG_RX_P_DISABLE	BIT_ULL(29)
#घोषणा RPMX_MTI_MAC100X_COMMAND_CONFIG_TX_P_DISABLE	BIT_ULL(28)
#घोषणा RPMX_MTI_MAC100X_COMMAND_CONFIG_PAUSE_IGNORE	BIT_ULL(8)
#घोषणा RPMX_MTI_MAC100X_COMMAND_CONFIG_PFC_MODE	BIT_ULL(19)
#घोषणा RPMX_MTI_MAC100X_CL01_PAUSE_QUANTA		0x80A8
#घोषणा RPMX_MTI_MAC100X_CL01_QUANTA_THRESH		0x80C8
#घोषणा RPM_DEFAULT_PAUSE_TIME			0xFFFF
#घोषणा RPMX_CMR_RX_OVR_BP		0x4120
#घोषणा RPMX_CMR_RX_OVR_BP_EN(x)	BIT_ULL((x) + 8)
#घोषणा RPMX_CMR_RX_OVR_BP_BP(x)	BIT_ULL((x) + 4)
#घोषणा RPMX_MTI_STAT_RX_STAT_PAGES_COUNTERX 0x12000
#घोषणा RPMX_MTI_STAT_TX_STAT_PAGES_COUNTERX 0x13000
#घोषणा RPMX_MTI_STAT_DATA_HI_CDC            0x10038

#घोषणा RPM_LMAC_FWI			0xa

/* Function Declarations */
पूर्णांक rpm_get_nr_lmacs(व्योम *rpmd);
u8 rpm_get_lmac_type(व्योम *rpmd, पूर्णांक lmac_id);
पूर्णांक rpm_lmac_पूर्णांकernal_loopback(व्योम *rpmd, पूर्णांक lmac_id, bool enable);
व्योम rpm_lmac_enadis_rx_छोड़ो_fwding(व्योम *rpmd, पूर्णांक lmac_id, bool enable);
पूर्णांक rpm_lmac_get_छोड़ो_frm_status(व्योम *cgxd, पूर्णांक lmac_id, u8 *tx_छोड़ो,
				  u8 *rx_छोड़ो);
व्योम rpm_lmac_छोड़ो_frm_config(व्योम *rpmd, पूर्णांक lmac_id, bool enable);
पूर्णांक rpm_lmac_enadis_छोड़ो_frm(व्योम *rpmd, पूर्णांक lmac_id, u8 tx_छोड़ो,
			      u8 rx_छोड़ो);
पूर्णांक rpm_get_tx_stats(व्योम *rpmd, पूर्णांक lmac_id, पूर्णांक idx, u64 *tx_stat);
पूर्णांक rpm_get_rx_stats(व्योम *rpmd, पूर्णांक lmac_id, पूर्णांक idx, u64 *rx_stat);
#पूर्ण_अगर /* RPM_H */
