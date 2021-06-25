<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  FUJITSU Extended Socket Network Device driver
 *  Copyright (c) 2015 FUJITSU LIMITED
 */

#अगर_अघोषित FJES_REGS_H_
#घोषणा FJES_REGS_H_

#समावेश <linux/bitops.h>

#घोषणा XSCT_DEVICE_REGISTER_SIZE 0x1000

/* रेजिस्टर offset */
/* Inक्रमmation रेजिस्टरs */
#घोषणा XSCT_OWNER_EPID     0x0000  /* Owner EPID */
#घोषणा XSCT_MAX_EP         0x0004  /* Maximum EP */

/* Device Control रेजिस्टरs */
#घोषणा XSCT_DCTL           0x0010  /* Device Control */

/* Command Control रेजिस्टरs */
#घोषणा XSCT_CR             0x0020  /* Command request */
#घोषणा XSCT_CS             0x0024  /* Command status */
#घोषणा XSCT_SHSTSAL        0x0028  /* Share status address Low */
#घोषणा XSCT_SHSTSAH        0x002C  /* Share status address High */

#घोषणा XSCT_REQBL          0x0034  /* Request Buffer length */
#घोषणा XSCT_REQBAL         0x0038  /* Request Buffer Address Low */
#घोषणा XSCT_REQBAH         0x003C  /* Request Buffer Address High */

#घोषणा XSCT_RESPBL         0x0044  /* Response Buffer Length */
#घोषणा XSCT_RESPBAL        0x0048  /* Response Buffer Address Low */
#घोषणा XSCT_RESPBAH        0x004C  /* Response Buffer Address High */

/* Interrupt Control रेजिस्टरs */
#घोषणा XSCT_IS             0x0080  /* Interrupt status */
#घोषणा XSCT_IMS            0x0084  /* Interrupt mask set */
#घोषणा XSCT_IMC            0x0088  /* Interrupt mask clear */
#घोषणा XSCT_IG             0x008C  /* Interrupt generator */
#घोषणा XSCT_ICTL           0x0090  /* Interrupt control */

/* रेजिस्टर काष्ठाure */
/* Inक्रमmation रेजिस्टरs */
जोड़ REG_OWNER_EPID अणु
	काष्ठा अणु
		__le32 epid:16;
		__le32:16;
	पूर्ण bits;
	__le32 reg;
पूर्ण;

जोड़ REG_MAX_EP अणु
	काष्ठा अणु
		__le32 maxep:16;
		__le32:16;
	पूर्ण bits;
	__le32 reg;
पूर्ण;

/* Device Control रेजिस्टरs */
जोड़ REG_DCTL अणु
	काष्ठा अणु
		__le32 reset:1;
		__le32 rsv0:15;
		__le32 rsv1:16;
	पूर्ण bits;
	__le32 reg;
पूर्ण;

/* Command Control रेजिस्टरs */
जोड़ REG_CR अणु
	काष्ठा अणु
		__le32 req_code:16;
		__le32 err_info:14;
		__le32 error:1;
		__le32 req_start:1;
	पूर्ण bits;
	__le32 reg;
पूर्ण;

जोड़ REG_CS अणु
	काष्ठा अणु
		__le32 req_code:16;
		__le32 rsv0:14;
		__le32 busy:1;
		__le32 complete:1;
	पूर्ण bits;
	__le32 reg;
पूर्ण;

/* Interrupt Control रेजिस्टरs */
जोड़ REG_ICTL अणु
	काष्ठा अणु
		__le32 स्वतःmak:1;
		__le32 rsv0:31;
	पूर्ण bits;
	__le32 reg;
पूर्ण;

क्रमागत REG_ICTL_MASK अणु
	REG_ICTL_MASK_INFO_UPDATE     = 1 << 20,
	REG_ICTL_MASK_DEV_STOP_REQ    = 1 << 19,
	REG_ICTL_MASK_TXRX_STOP_REQ   = 1 << 18,
	REG_ICTL_MASK_TXRX_STOP_DONE  = 1 << 17,
	REG_ICTL_MASK_RX_DATA         = 1 << 16,
	REG_ICTL_MASK_ALL             = GENMASK(20, 16),
पूर्ण;

क्रमागत REG_IS_MASK अणु
	REG_IS_MASK_IS_ASSERT	= 1 << 31,
	REG_IS_MASK_EPID	= GENMASK(15, 0),
पूर्ण;

काष्ठा fjes_hw;

u32 fjes_hw_rd32(काष्ठा fjes_hw *hw, u32 reg);

#घोषणा wr32(reg, val) \
करो अणु \
	u8 *base = hw->base; \
	ग_लिखोl((val), &base[(reg)]); \
पूर्ण जबतक (0)

#घोषणा rd32(reg) (fjes_hw_rd32(hw, reg))

#पूर्ण_अगर /* FJES_REGS_H_ */
