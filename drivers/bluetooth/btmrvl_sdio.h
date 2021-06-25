<शैली गुरु>
/**
 * Marvell BT-over-SDIO driver: SDIO पूर्णांकerface related definitions
 *
 * Copyright (C) 2009, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 *
 **/

#घोषणा SDIO_HEADER_LEN			4

/* SD block size can not bigger than 64 due to buf size limit in firmware */
/* define SD block size क्रम data Tx/Rx */
#घोषणा SDIO_BLOCK_SIZE			64

/* Number of blocks क्रम firmware transfer */
#घोषणा FIRMWARE_TRANSFER_NBLOCK	2

/* This is क्रम firmware specअगरic length */
#घोषणा FW_EXTRA_LEN			36

#घोषणा MRVDRV_SIZE_OF_CMD_BUFFER       (2 * 1024)

#घोषणा MRVDRV_BT_RX_PACKET_BUFFER_SIZE \
	(HCI_MAX_FRAME_SIZE + FW_EXTRA_LEN)

#घोषणा ALLOC_BUF_SIZE	(((max_t (पूर्णांक, MRVDRV_BT_RX_PACKET_BUFFER_SIZE, \
			MRVDRV_SIZE_OF_CMD_BUFFER) + SDIO_HEADER_LEN \
			+ SDIO_BLOCK_SIZE - 1) / SDIO_BLOCK_SIZE) \
			* SDIO_BLOCK_SIZE)

/* The number of बार to try when polling क्रम status */
#घोषणा MAX_POLL_TRIES			100

/* Max retry number of CMD53 ग_लिखो */
#घोषणा MAX_WRITE_IOMEM_RETRY		2

/* रेजिस्टर biपंचांगasks */
#घोषणा HOST_POWER_UP				BIT(1)
#घोषणा HOST_CMD53_FIN				BIT(2)

#घोषणा HIM_DISABLE				0xff
#घोषणा HIM_ENABLE				(BIT(0) | BIT(1))

#घोषणा UP_LD_HOST_INT_STATUS			BIT(0)
#घोषणा DN_LD_HOST_INT_STATUS			BIT(1)

#घोषणा DN_LD_CARD_RDY				BIT(0)
#घोषणा CARD_IO_READY				BIT(3)

#घोषणा FIRMWARE_READY				0xfedc

काष्ठा bपंचांगrvl_plt_wake_cfg अणु
	पूर्णांक irq_bt;
	bool wake_by_bt;
पूर्ण;

काष्ठा bपंचांगrvl_sdio_card_reg अणु
	u8 cfg;
	u8 host_पूर्णांक_mask;
	u8 host_पूर्णांकstatus;
	u8 card_status;
	u8 sq_पढ़ो_base_addr_a0;
	u8 sq_पढ़ो_base_addr_a1;
	u8 card_revision;
	u8 card_fw_status0;
	u8 card_fw_status1;
	u8 card_rx_len;
	u8 card_rx_unit;
	u8 io_port_0;
	u8 io_port_1;
	u8 io_port_2;
	bool पूर्णांक_पढ़ो_to_clear;
	u8 host_पूर्णांक_rsr;
	u8 card_misc_cfg;
	u8 fw_dump_ctrl;
	u8 fw_dump_start;
	u8 fw_dump_end;
पूर्ण;

काष्ठा bपंचांगrvl_sdio_card अणु
	काष्ठा sdio_func *func;
	u32 ioport;
	स्थिर अक्षर *helper;
	स्थिर अक्षर *firmware;
	स्थिर काष्ठा bपंचांगrvl_sdio_card_reg *reg;
	bool support_pscan_win_report;
	bool supports_fw_dump;
	u16 sd_blksz_fw_dl;
	u8 rx_unit;
	काष्ठा bपंचांगrvl_निजी *priv;
	काष्ठा device_node *plt_of_node;
	काष्ठा bपंचांगrvl_plt_wake_cfg *plt_wake_cfg;
पूर्ण;

काष्ठा bपंचांगrvl_sdio_device अणु
	स्थिर अक्षर *helper;
	स्थिर अक्षर *firmware;
	स्थिर काष्ठा bपंचांगrvl_sdio_card_reg *reg;
	स्थिर bool support_pscan_win_report;
	u16 sd_blksz_fw_dl;
	bool supports_fw_dump;
पूर्ण;


/* Platक्रमm specअगरic DMA alignment */
#घोषणा BTSDIO_DMA_ALIGN		8

/* Macros क्रम Data Alignment : size */
#घोषणा ALIGN_SZ(p, a)	\
	(((p) + ((a) - 1)) & ~((a) - 1))

/* Macros क्रम Data Alignment : address */
#घोषणा ALIGN_ADDR(p, a)	\
	((((अचिन्हित दीर्घ)(p)) + (((अचिन्हित दीर्घ)(a)) - 1)) & \
					~(((अचिन्हित दीर्घ)(a)) - 1))
