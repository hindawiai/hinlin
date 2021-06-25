<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2019-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GAUDI_FW_IF_H
#घोषणा GAUDI_FW_IF_H

#समावेश <linux/types.h>

#घोषणा GAUDI_EVENT_QUEUE_MSI_IDX	8
#घोषणा GAUDI_NIC_PORT1_MSI_IDX		10
#घोषणा GAUDI_NIC_PORT3_MSI_IDX		12
#घोषणा GAUDI_NIC_PORT5_MSI_IDX		14
#घोषणा GAUDI_NIC_PORT7_MSI_IDX		16
#घोषणा GAUDI_NIC_PORT9_MSI_IDX		18

#घोषणा UBOOT_FW_OFFSET			0x100000	/* 1MB in SRAM */
#घोषणा LINUX_FW_OFFSET			0x800000	/* 8MB in HBM */

क्रमागत gaudi_nic_axi_error अणु
	RXB,
	RXE,
	TXS,
	TXE,
	QPC_RESP,
	NON_AXI_ERR,
पूर्ण;

/*
 * काष्ठा eq_nic_sei_event - describes an AXI error cause.
 * @axi_error_cause: one of the events defined in क्रमागत gaudi_nic_axi_error.
 * @id: can be either 0 or 1, to further describe unit with पूर्णांकerrupt cause
 *      (i.e. TXE0 or TXE1).
 * @pad[6]: padding काष्ठाure to 64bit.
 */
काष्ठा eq_nic_sei_event अणु
	__u8 axi_error_cause;
	__u8 id;
	__u8 pad[6];
पूर्ण;

#घोषणा GAUDI_PLL_FREQ_LOW		200000000 /* 200 MHz */

#पूर्ण_अगर /* GAUDI_FW_IF_H */
