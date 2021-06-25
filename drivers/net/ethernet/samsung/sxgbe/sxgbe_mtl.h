<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* 10G controller driver क्रम Samsung SoCs
 *
 * Copyright (C) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Siva Reddy Kallam <siva.kallam@samsung.com>
 */
#अगर_अघोषित __SXGBE_MTL_H__
#घोषणा __SXGBE_MTL_H__

#घोषणा SXGBE_MTL_OPMODE_ESTMASK	0x3
#घोषणा SXGBE_MTL_OPMODE_RAAMASK	0x1
#घोषणा SXGBE_MTL_FCMASK		0x7
#घोषणा SXGBE_MTL_TX_FIFO_DIV		256
#घोषणा SXGBE_MTL_RX_FIFO_DIV		256

#घोषणा SXGBE_MTL_RXQ_OP_FEP		BIT(4)
#घोषणा SXGBE_MTL_RXQ_OP_FUP		BIT(3)
#घोषणा SXGBE_MTL_ENABLE_FC		0x80

#घोषणा ETS_WRR				0xFFFFFF9F
#घोषणा ETS_RST				0xFFFFFF9F
#घोषणा ETS_WFQ				0x00000020
#घोषणा ETS_DWRR			0x00000040
#घोषणा RAA_SP				0xFFFFFFFB
#घोषणा RAA_WSP				0x00000004

#घोषणा RX_QUEUE_DYNAMIC		0x80808080
#घोषणा RX_FC_ACTIVE			8
#घोषणा RX_FC_DEACTIVE			13

क्रमागत ttc_control अणु
	MTL_CONTROL_TTC_64 = 0x00000000,
	MTL_CONTROL_TTC_96 = 0x00000020,
	MTL_CONTROL_TTC_128 = 0x00000030,
	MTL_CONTROL_TTC_192 = 0x00000040,
	MTL_CONTROL_TTC_256 = 0x00000050,
	MTL_CONTROL_TTC_384 = 0x00000060,
	MTL_CONTROL_TTC_512 = 0x00000070,
पूर्ण;

क्रमागत rtc_control अणु
	MTL_CONTROL_RTC_64 = 0x00000000,
	MTL_CONTROL_RTC_96 = 0x00000002,
	MTL_CONTROL_RTC_128 = 0x00000003,
पूर्ण;

क्रमागत flow_control_th अणु
	MTL_FC_FULL_1K = 0x00000000,
	MTL_FC_FULL_2K = 0x00000001,
	MTL_FC_FULL_4K = 0x00000002,
	MTL_FC_FULL_5K = 0x00000003,
	MTL_FC_FULL_6K = 0x00000004,
	MTL_FC_FULL_8K = 0x00000005,
	MTL_FC_FULL_16K = 0x00000006,
	MTL_FC_FULL_24K = 0x00000007,
पूर्ण;

काष्ठा sxgbe_mtl_ops अणु
	व्योम (*mtl_init)(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक etsalg,
			 अचिन्हित पूर्णांक raa);

	व्योम (*mtl_set_txfअगरosize)(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				   पूर्णांक mtl_fअगरo);

	व्योम (*mtl_set_rxfअगरosize)(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				   पूर्णांक queue_fअगरo);

	व्योम (*mtl_enable_txqueue)(व्योम __iomem *ioaddr, पूर्णांक queue_num);

	व्योम (*mtl_disable_txqueue)(व्योम __iomem *ioaddr, पूर्णांक queue_num);

	व्योम (*set_tx_mtl_mode)(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				पूर्णांक tx_mode);

	व्योम (*set_rx_mtl_mode)(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				पूर्णांक rx_mode);

	व्योम (*mtl_dynamic_dma_rxqueue)(व्योम __iomem *ioaddr);

	व्योम (*mtl_fc_active)(व्योम __iomem *ioaddr, पूर्णांक queue_num,
			      पूर्णांक threshold);

	व्योम (*mtl_fc_deactive)(व्योम __iomem *ioaddr, पूर्णांक queue_num,
				पूर्णांक threshold);

	व्योम (*mtl_fc_enable)(व्योम __iomem *ioaddr, पूर्णांक queue_num);

	व्योम (*mtl_fep_enable)(व्योम __iomem *ioaddr, पूर्णांक queue_num);

	व्योम (*mtl_fep_disable)(व्योम __iomem *ioaddr, पूर्णांक queue_num);

	व्योम (*mtl_fup_enable)(व्योम __iomem *ioaddr, पूर्णांक queue_num);

	व्योम (*mtl_fup_disable)(व्योम __iomem *ioaddr, पूर्णांक queue_num);
पूर्ण;

स्थिर काष्ठा sxgbe_mtl_ops *sxgbe_get_mtl_ops(व्योम);

#पूर्ण_अगर /* __SXGBE_MTL_H__ */
