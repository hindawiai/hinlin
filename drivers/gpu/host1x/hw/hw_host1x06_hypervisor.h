<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2017 NVIDIA Corporation.
 */

#घोषणा HOST1X_HV_SYNCPT_PROT_EN			0x1ac4
#घोषणा HOST1X_HV_SYNCPT_PROT_EN_CH_EN			BIT(1)
#घोषणा HOST1X_HV_CH_KERNEL_FILTER_GBUFFER(x)		(0x2020 + (x * 4))
#घोषणा HOST1X_HV_CMDFIFO_PEEK_CTRL			0x233c
#घोषणा HOST1X_HV_CMDFIFO_PEEK_CTRL_ADDR(x)		(x)
#घोषणा HOST1X_HV_CMDFIFO_PEEK_CTRL_CHANNEL(x)		((x) << 16)
#घोषणा HOST1X_HV_CMDFIFO_PEEK_CTRL_ENABLE		BIT(31)
#घोषणा HOST1X_HV_CMDFIFO_PEEK_READ			0x2340
#घोषणा HOST1X_HV_CMDFIFO_PEEK_PTRS			0x2344
#घोषणा HOST1X_HV_CMDFIFO_PEEK_PTRS_WR_PTR_V(x)		(((x) >> 16) & 0xfff)
#घोषणा HOST1X_HV_CMDFIFO_PEEK_PTRS_RD_PTR_V(x)		((x) & 0xfff)
#घोषणा HOST1X_HV_CMDFIFO_SETUP(x)			(0x2588 + (x * 4))
#घोषणा HOST1X_HV_CMDFIFO_SETUP_LIMIT_V(x)		(((x) >> 16) & 0xfff)
#घोषणा HOST1X_HV_CMDFIFO_SETUP_BASE_V(x)		((x) & 0xfff)
#घोषणा HOST1X_HV_ICG_EN_OVERRIDE			0x2aa8
