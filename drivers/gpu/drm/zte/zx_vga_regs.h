<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2017 Sanechips Technology Co., Ltd.
 * Copyright 2017 Linaro Ltd.
 */

#अगर_अघोषित __ZX_VGA_REGS_H__
#घोषणा __ZX_VGA_REGS_H__

#घोषणा VGA_CMD_CFG			0x04
#घोषणा VGA_CMD_TRANS			BIT(6)
#घोषणा VGA_CMD_COMBO			BIT(5)
#घोषणा VGA_CMD_RW			BIT(4)
#घोषणा VGA_SUB_ADDR			0x0c
#घोषणा VGA_DEVICE_ADDR			0x10
#घोषणा VGA_CLK_DIV_FS			0x14
#घोषणा VGA_RXF_CTRL			0x20
#घोषणा VGA_RX_FIFO_CLEAR		BIT(7)
#घोषणा VGA_DATA			0x24
#घोषणा VGA_I2C_STATUS			0x28
#घोषणा VGA_DEVICE_DISCONNECTED		BIT(7)
#घोषणा VGA_DEVICE_CONNECTED		BIT(6)
#घोषणा VGA_CLEAR_IRQ			BIT(4)
#घोषणा VGA_TRANS_DONE			BIT(0)
#घोषणा VGA_RXF_STATUS			0x30
#घोषणा VGA_RXF_COUNT_SHIFT		2
#घोषणा VGA_RXF_COUNT_MASK		GENMASK(7, 2)
#घोषणा VGA_AUTO_DETECT_PARA		0x34
#घोषणा VGA_AUTO_DETECT_SEL		0x38
#घोषणा VGA_DETECT_SEL_HAS_DEVICE	BIT(1)
#घोषणा VGA_DETECT_SEL_NO_DEVICE	BIT(0)

#पूर्ण_अगर /* __ZX_VGA_REGS_H__ */
