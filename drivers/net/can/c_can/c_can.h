<शैली गुरु>
/*
 * CAN bus driver क्रम Bosch C_CAN controller
 *
 * Copyright (C) 2010 ST Microelectronics
 * Bhupesh Sharma <bhupesh.sharma@st.com>
 *
 * Borrowed heavily from the C_CAN driver originally written by:
 * Copyright (C) 2007
 * - Sascha Hauer, Marc Kleine-Budde, Pengutronix <s.hauer@pengutronix.de>
 * - Simon Kallweit, पूर्णांकefo AG <simon.kallweit@पूर्णांकefo.ch>
 *
 * Bosch C_CAN controller is compliant to CAN protocol version 2.0 part A and B.
 * Bosch C_CAN user manual can be obtained from:
 * http://www.semiconductors.bosch.de/media/en/pdf/ipmodules_1/c_can/
 * users_manual_c_can.pdf
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित C_CAN_H
#घोषणा C_CAN_H

क्रमागत reg अणु
	C_CAN_CTRL_REG = 0,
	C_CAN_CTRL_EX_REG,
	C_CAN_STS_REG,
	C_CAN_ERR_CNT_REG,
	C_CAN_BTR_REG,
	C_CAN_INT_REG,
	C_CAN_TEST_REG,
	C_CAN_BRPEXT_REG,
	C_CAN_IF1_COMREQ_REG,
	C_CAN_IF1_COMMSK_REG,
	C_CAN_IF1_MASK1_REG,
	C_CAN_IF1_MASK2_REG,
	C_CAN_IF1_ARB1_REG,
	C_CAN_IF1_ARB2_REG,
	C_CAN_IF1_MSGCTRL_REG,
	C_CAN_IF1_DATA1_REG,
	C_CAN_IF1_DATA2_REG,
	C_CAN_IF1_DATA3_REG,
	C_CAN_IF1_DATA4_REG,
	C_CAN_IF2_COMREQ_REG,
	C_CAN_IF2_COMMSK_REG,
	C_CAN_IF2_MASK1_REG,
	C_CAN_IF2_MASK2_REG,
	C_CAN_IF2_ARB1_REG,
	C_CAN_IF2_ARB2_REG,
	C_CAN_IF2_MSGCTRL_REG,
	C_CAN_IF2_DATA1_REG,
	C_CAN_IF2_DATA2_REG,
	C_CAN_IF2_DATA3_REG,
	C_CAN_IF2_DATA4_REG,
	C_CAN_TXRQST1_REG,
	C_CAN_TXRQST2_REG,
	C_CAN_NEWDAT1_REG,
	C_CAN_NEWDAT2_REG,
	C_CAN_INTPND1_REG,
	C_CAN_INTPND2_REG,
	C_CAN_INTPND3_REG,
	C_CAN_MSGVAL1_REG,
	C_CAN_MSGVAL2_REG,
	C_CAN_FUNCTION_REG,
पूर्ण;

अटल स्थिर u16 __maybe_unused reg_map_c_can[] = अणु
	[C_CAN_CTRL_REG]	= 0x00,
	[C_CAN_STS_REG]		= 0x02,
	[C_CAN_ERR_CNT_REG]	= 0x04,
	[C_CAN_BTR_REG]		= 0x06,
	[C_CAN_INT_REG]		= 0x08,
	[C_CAN_TEST_REG]	= 0x0A,
	[C_CAN_BRPEXT_REG]	= 0x0C,
	[C_CAN_IF1_COMREQ_REG]	= 0x10,
	[C_CAN_IF1_COMMSK_REG]	= 0x12,
	[C_CAN_IF1_MASK1_REG]	= 0x14,
	[C_CAN_IF1_MASK2_REG]	= 0x16,
	[C_CAN_IF1_ARB1_REG]	= 0x18,
	[C_CAN_IF1_ARB2_REG]	= 0x1A,
	[C_CAN_IF1_MSGCTRL_REG]	= 0x1C,
	[C_CAN_IF1_DATA1_REG]	= 0x1E,
	[C_CAN_IF1_DATA2_REG]	= 0x20,
	[C_CAN_IF1_DATA3_REG]	= 0x22,
	[C_CAN_IF1_DATA4_REG]	= 0x24,
	[C_CAN_IF2_COMREQ_REG]	= 0x40,
	[C_CAN_IF2_COMMSK_REG]	= 0x42,
	[C_CAN_IF2_MASK1_REG]	= 0x44,
	[C_CAN_IF2_MASK2_REG]	= 0x46,
	[C_CAN_IF2_ARB1_REG]	= 0x48,
	[C_CAN_IF2_ARB2_REG]	= 0x4A,
	[C_CAN_IF2_MSGCTRL_REG]	= 0x4C,
	[C_CAN_IF2_DATA1_REG]	= 0x4E,
	[C_CAN_IF2_DATA2_REG]	= 0x50,
	[C_CAN_IF2_DATA3_REG]	= 0x52,
	[C_CAN_IF2_DATA4_REG]	= 0x54,
	[C_CAN_TXRQST1_REG]	= 0x80,
	[C_CAN_TXRQST2_REG]	= 0x82,
	[C_CAN_NEWDAT1_REG]	= 0x90,
	[C_CAN_NEWDAT2_REG]	= 0x92,
	[C_CAN_INTPND1_REG]	= 0xA0,
	[C_CAN_INTPND2_REG]	= 0xA2,
	[C_CAN_MSGVAL1_REG]	= 0xB0,
	[C_CAN_MSGVAL2_REG]	= 0xB2,
पूर्ण;

अटल स्थिर u16 __maybe_unused reg_map_d_can[] = अणु
	[C_CAN_CTRL_REG]	= 0x00,
	[C_CAN_CTRL_EX_REG]	= 0x02,
	[C_CAN_STS_REG]		= 0x04,
	[C_CAN_ERR_CNT_REG]	= 0x08,
	[C_CAN_BTR_REG]		= 0x0C,
	[C_CAN_BRPEXT_REG]	= 0x0E,
	[C_CAN_INT_REG]		= 0x10,
	[C_CAN_TEST_REG]	= 0x14,
	[C_CAN_FUNCTION_REG]	= 0x18,
	[C_CAN_TXRQST1_REG]	= 0x88,
	[C_CAN_TXRQST2_REG]	= 0x8A,
	[C_CAN_NEWDAT1_REG]	= 0x9C,
	[C_CAN_NEWDAT2_REG]	= 0x9E,
	[C_CAN_INTPND1_REG]	= 0xB0,
	[C_CAN_INTPND2_REG]	= 0xB2,
	[C_CAN_INTPND3_REG]	= 0xB4,
	[C_CAN_MSGVAL1_REG]	= 0xC4,
	[C_CAN_MSGVAL2_REG]	= 0xC6,
	[C_CAN_IF1_COMREQ_REG]	= 0x100,
	[C_CAN_IF1_COMMSK_REG]	= 0x102,
	[C_CAN_IF1_MASK1_REG]	= 0x104,
	[C_CAN_IF1_MASK2_REG]	= 0x106,
	[C_CAN_IF1_ARB1_REG]	= 0x108,
	[C_CAN_IF1_ARB2_REG]	= 0x10A,
	[C_CAN_IF1_MSGCTRL_REG]	= 0x10C,
	[C_CAN_IF1_DATA1_REG]	= 0x110,
	[C_CAN_IF1_DATA2_REG]	= 0x112,
	[C_CAN_IF1_DATA3_REG]	= 0x114,
	[C_CAN_IF1_DATA4_REG]	= 0x116,
	[C_CAN_IF2_COMREQ_REG]	= 0x120,
	[C_CAN_IF2_COMMSK_REG]	= 0x122,
	[C_CAN_IF2_MASK1_REG]	= 0x124,
	[C_CAN_IF2_MASK2_REG]	= 0x126,
	[C_CAN_IF2_ARB1_REG]	= 0x128,
	[C_CAN_IF2_ARB2_REG]	= 0x12A,
	[C_CAN_IF2_MSGCTRL_REG]	= 0x12C,
	[C_CAN_IF2_DATA1_REG]	= 0x130,
	[C_CAN_IF2_DATA2_REG]	= 0x132,
	[C_CAN_IF2_DATA3_REG]	= 0x134,
	[C_CAN_IF2_DATA4_REG]	= 0x136,
पूर्ण;

क्रमागत c_can_dev_id अणु
	BOSCH_C_CAN,
	BOSCH_D_CAN,
पूर्ण;

काष्ठा raminit_bits अणु
	u8 start;
	u8 करोne;
पूर्ण;

काष्ठा c_can_driver_data अणु
	क्रमागत c_can_dev_id id;
	अचिन्हित पूर्णांक msg_obj_num;

	/* RAMINIT रेजिस्टर description. Optional. */
	स्थिर काष्ठा raminit_bits *raminit_bits; /* Array of START/DONE bit positions */
	u8 raminit_num;		/* Number of CAN instances on the SoC */
	bool raminit_pulse;	/* If set, sets and clears START bit (pulse) */
पूर्ण;

/* Out of band RAMINIT रेजिस्टर access via syscon regmap */
काष्ठा c_can_raminit अणु
	काष्ठा regmap *syscon;	/* क्रम raminit ctrl. reg. access */
	अचिन्हित पूर्णांक reg;	/* रेजिस्टर index within syscon */
	काष्ठा raminit_bits bits;
	bool needs_pulse;
पूर्ण;

/* c_can निजी data काष्ठाure */
काष्ठा c_can_priv अणु
	काष्ठा can_priv can;	/* must be the first member */
	काष्ठा napi_काष्ठा napi;
	काष्ठा net_device *dev;
	काष्ठा device *device;
	अचिन्हित पूर्णांक msg_obj_num;
	अचिन्हित पूर्णांक msg_obj_rx_num;
	अचिन्हित पूर्णांक msg_obj_tx_num;
	अचिन्हित पूर्णांक msg_obj_rx_first;
	अचिन्हित पूर्णांक msg_obj_rx_last;
	अचिन्हित पूर्णांक msg_obj_tx_first;
	अचिन्हित पूर्णांक msg_obj_tx_last;
	u32 msg_obj_rx_mask;
	atomic_t tx_active;
	atomic_t sie_pending;
	अचिन्हित दीर्घ tx_dir;
	पूर्णांक last_status;
	u16 (*पढ़ो_reg)(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index);
	व्योम (*ग_लिखो_reg)(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index, u16 val);
	u32 (*पढ़ो_reg32)(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index);
	व्योम (*ग_लिखो_reg32)(स्थिर काष्ठा c_can_priv *priv, क्रमागत reg index, u32 val);
	व्योम __iomem *base;
	स्थिर u16 *regs;
	व्योम *priv;		/* क्रम board-specअगरic data */
	क्रमागत c_can_dev_id type;
	काष्ठा c_can_raminit raminit_sys;	/* RAMINIT via syscon regmap */
	व्योम (*raminit)(स्थिर काष्ठा c_can_priv *priv, bool enable);
	u32 comm_rcv_high;
	u32 rxmasked;
	u32 dlc[];
पूर्ण;

काष्ठा net_device *alloc_c_can_dev(पूर्णांक msg_obj_num);
व्योम मुक्त_c_can_dev(काष्ठा net_device *dev);
पूर्णांक रेजिस्टर_c_can_dev(काष्ठा net_device *dev);
व्योम unरेजिस्टर_c_can_dev(काष्ठा net_device *dev);

#अगर_घोषित CONFIG_PM
पूर्णांक c_can_घातer_up(काष्ठा net_device *dev);
पूर्णांक c_can_घातer_करोwn(काष्ठा net_device *dev);
#पूर्ण_अगर

#पूर्ण_अगर /* C_CAN_H */
