<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * MacBook (Pro) SPI keyboard and touchpad driver
 *
 * Copyright (c) 2015-2019 Federico Lorenzi
 * Copyright (c) 2017-2019 Ronald Tschalथअr
 */

#अगर_अघोषित _APPLESPI_H_
#घोषणा _APPLESPI_H_

क्रमागत applespi_evt_type अणु
	ET_CMD_TP_INI = BIT(0),
	ET_CMD_BL = BIT(1),
	ET_CMD_CL = BIT(2),
	ET_RD_KEYB = BIT(8),
	ET_RD_TPAD = BIT(9),
	ET_RD_UNKN = BIT(10),
	ET_RD_IRQ = BIT(11),
	ET_RD_CRC = BIT(12),
पूर्ण;

क्रमागत applespi_pkt_type अणु
	PT_READ,
	PT_WRITE,
	PT_STATUS,
पूर्ण;

#पूर्ण_अगर /* _APPLESPI_H_ */
