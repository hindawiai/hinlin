<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause */
/*
 * Copyright (c) 2020, MIPI Alliance, Inc.
 *
 * Author: Nicolas Pitre <npitre@baylibre.com>
 *
 * Common command/response related stuff
 */

#अगर_अघोषित CMD_H
#घोषणा CMD_H

/*
 * Those bits are common to all descriptor क्रमmats and
 * may be manipulated by the core code.
 */
#घोषणा CMD_0_TOC			W0_BIT_(31)
#घोषणा CMD_0_ROC			W0_BIT_(30)
#घोषणा CMD_0_ATTR			W0_MASK(2, 0)

/*
 * Response Descriptor Structure
 */
#घोषणा RESP_STATUS(resp)		FIELD_GET(GENMASK(31, 28), resp)
#घोषणा RESP_TID(resp)			FIELD_GET(GENMASK(27, 24), resp)
#घोषणा RESP_DATA_LENGTH(resp)		FIELD_GET(GENMASK(21,  0), resp)

#घोषणा RESP_ERR_FIELD			GENMASK(31, 28)

क्रमागत hci_resp_err अणु
	RESP_SUCCESS			= 0x0,
	RESP_ERR_CRC			= 0x1,
	RESP_ERR_PARITY			= 0x2,
	RESP_ERR_FRAME			= 0x3,
	RESP_ERR_ADDR_HEADER		= 0x4,
	RESP_ERR_BCAST_NACK_7E		= 0x4,
	RESP_ERR_NACK			= 0x5,
	RESP_ERR_OVL			= 0x6,
	RESP_ERR_I3C_SHORT_READ		= 0x7,
	RESP_ERR_HC_TERMINATED		= 0x8,
	RESP_ERR_I2C_WR_DATA_NACK	= 0x9,
	RESP_ERR_BUS_XFER_ABORTED	= 0x9,
	RESP_ERR_NOT_SUPPORTED		= 0xa,
	RESP_ERR_ABORTED_WITH_CRC	= 0xb,
	/* 0xc to 0xf are reserved क्रम transfer specअगरic errors */
पूर्ण;

/* TID generation (4 bits wide in all हालs) */
#घोषणा hci_get_tid(bits) \
	(atomic_inc_वापस_relaxed(&hci->next_cmd_tid) % (1U << 4))

/* This असलtracts operations with our command descriptor क्रमmats */
काष्ठा hci_cmd_ops अणु
	पूर्णांक (*prep_ccc)(काष्ठा i3c_hci *hci, काष्ठा hci_xfer *xfer,
			u8 ccc_addr, u8 ccc_cmd, bool raw);
	व्योम (*prep_i3c_xfer)(काष्ठा i3c_hci *hci, काष्ठा i3c_dev_desc *dev,
			      काष्ठा hci_xfer *xfer);
	व्योम (*prep_i2c_xfer)(काष्ठा i3c_hci *hci, काष्ठा i2c_dev_desc *dev,
			      काष्ठा hci_xfer *xfer);
	पूर्णांक (*perक्रमm_daa)(काष्ठा i3c_hci *hci);
पूर्ण;

/* Our various instances */
बाह्य स्थिर काष्ठा hci_cmd_ops mipi_i3c_hci_cmd_v1;
बाह्य स्थिर काष्ठा hci_cmd_ops mipi_i3c_hci_cmd_v2;

#पूर्ण_अगर
