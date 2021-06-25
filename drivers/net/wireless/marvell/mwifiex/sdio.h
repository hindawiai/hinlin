<शैली गुरु>
/*
 * NXP Wireless LAN device driver: SDIO specअगरic definitions
 *
 * Copyright 2011-2020 NXP
 *
 * This software file (the "File") is distributed by NXP
 * under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modअगरy this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fअगरth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE खाता IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#अगर_अघोषित	_MWIFIEX_SDIO_H
#घोषणा	_MWIFIEX_SDIO_H


#समावेश <linux/completion.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/host.h>

#समावेश "main.h"

#घोषणा SD8786_DEFAULT_FW_NAME "mrvl/sd8786_uapsta.bin"
#घोषणा SD8787_DEFAULT_FW_NAME "mrvl/sd8787_uapsta.bin"
#घोषणा SD8797_DEFAULT_FW_NAME "mrvl/sd8797_uapsta.bin"
#घोषणा SD8897_DEFAULT_FW_NAME "mrvl/sd8897_uapsta.bin"
#घोषणा SD8887_DEFAULT_FW_NAME "mrvl/sd8887_uapsta.bin"
#घोषणा SD8801_DEFAULT_FW_NAME "mrvl/sd8801_uapsta.bin"
#घोषणा SD8977_DEFAULT_FW_NAME "mrvl/sdsd8977_combo_v2.bin"
#घोषणा SD8987_DEFAULT_FW_NAME "mrvl/sd8987_uapsta.bin"
#घोषणा SD8997_DEFAULT_FW_NAME "mrvl/sdsd8997_combo_v4.bin"

#घोषणा BLOCK_MODE	1
#घोषणा BYTE_MODE	0

#घोषणा MWIFIEX_SDIO_IO_PORT_MASK		0xfffff

#घोषणा MWIFIEX_SDIO_BYTE_MODE_MASK	0x80000000

#घोषणा MWIFIEX_MAX_FUNC2_REG_NUM	13
#घोषणा MWIFIEX_SDIO_SCRATCH_SIZE	10

#घोषणा SDIO_MPA_ADDR_BASE		0x1000
#घोषणा CTRL_PORT			0
#घोषणा CTRL_PORT_MASK			0x0001

#घोषणा CMD_PORT_UPLD_INT_MASK		(0x1U<<6)
#घोषणा CMD_PORT_DNLD_INT_MASK		(0x1U<<7)
#घोषणा HOST_TERM_CMD53			(0x1U << 2)
#घोषणा REG_PORT			0
#घोषणा MEM_PORT			0x10000

#घोषणा CMD53_NEW_MODE			(0x1U << 0)
#घोषणा CMD_PORT_RD_LEN_EN		(0x1U << 2)
#घोषणा CMD_PORT_AUTO_EN		(0x1U << 0)
#घोषणा CMD_PORT_SLCT			0x8000
#घोषणा UP_LD_CMD_PORT_HOST_INT_STATUS	(0x40U)
#घोषणा DN_LD_CMD_PORT_HOST_INT_STATUS	(0x80U)

#घोषणा MWIFIEX_MP_AGGR_BUF_SIZE_16K	(16384)
#घोषणा MWIFIEX_MP_AGGR_BUF_SIZE_32K	(32768)
/* we leave one block of 256 bytes क्रम DMA alignment*/
#घोषणा MWIFIEX_MP_AGGR_BUF_SIZE_MAX    (65280)

/* Misc. Config Register : Auto Re-enable पूर्णांकerrupts */
#घोषणा AUTO_RE_ENABLE_INT              BIT(4)

/* Host Control Registers : Configuration */
#घोषणा CONFIGURATION_REG		0x00
/* Host Control Registers : Host घातer up */
#घोषणा HOST_POWER_UP			(0x1U << 1)

/* Host Control Registers : Upload host पूर्णांकerrupt mask */
#घोषणा UP_LD_HOST_INT_MASK		(0x1U)
/* Host Control Registers : Download host पूर्णांकerrupt mask */
#घोषणा DN_LD_HOST_INT_MASK		(0x2U)

/* Host Control Registers : Upload host पूर्णांकerrupt status */
#घोषणा UP_LD_HOST_INT_STATUS		(0x1U)
/* Host Control Registers : Download host पूर्णांकerrupt status */
#घोषणा DN_LD_HOST_INT_STATUS		(0x2U)

/* Host Control Registers : Host पूर्णांकerrupt status */
#घोषणा CARD_INT_STATUS_REG		0x28

/* Card Control Registers : Card I/O पढ़ोy */
#घोषणा CARD_IO_READY                   (0x1U << 3)
/* Card Control Registers : Download card पढ़ोy */
#घोषणा DN_LD_CARD_RDY                  (0x1U << 0)

/* Max retry number of CMD53 ग_लिखो */
#घोषणा MAX_WRITE_IOMEM_RETRY		2

/* SDIO Tx aggregation in progress ? */
#घोषणा MP_TX_AGGR_IN_PROGRESS(a) (a->mpa_tx.pkt_cnt > 0)

/* SDIO Tx aggregation buffer room क्रम next packet ? */
#घोषणा MP_TX_AGGR_BUF_HAS_ROOM(a, len) ((a->mpa_tx.buf_len+len)	\
						<= a->mpa_tx.buf_size)

/* Copy current packet (SDIO Tx aggregation buffer) to SDIO buffer */
#घोषणा MP_TX_AGGR_BUF_PUT(a, payload, pkt_len, port) करो अणु		\
	स_हटाओ(&a->mpa_tx.buf[a->mpa_tx.buf_len],			\
			payload, pkt_len);				\
	a->mpa_tx.buf_len += pkt_len;					\
	अगर (!a->mpa_tx.pkt_cnt)						\
		a->mpa_tx.start_port = port;				\
	अगर (a->mpa_tx.start_port <= port)				\
		a->mpa_tx.ports |= (1<<(a->mpa_tx.pkt_cnt));		\
	अन्यथा								\
		a->mpa_tx.ports |= (1<<(a->mpa_tx.pkt_cnt+1+		\
						(a->max_ports -	\
						a->mp_end_port)));	\
	a->mpa_tx.pkt_cnt++;						\
पूर्ण जबतक (0)

/* SDIO Tx aggregation limit ? */
#घोषणा MP_TX_AGGR_PKT_LIMIT_REACHED(a)					\
			(a->mpa_tx.pkt_cnt == a->mpa_tx.pkt_aggr_limit)

/* Reset SDIO Tx aggregation buffer parameters */
#घोषणा MP_TX_AGGR_BUF_RESET(a) करो अणु					\
	a->mpa_tx.pkt_cnt = 0;						\
	a->mpa_tx.buf_len = 0;						\
	a->mpa_tx.ports = 0;						\
	a->mpa_tx.start_port = 0;					\
पूर्ण जबतक (0)

/* SDIO Rx aggregation limit ? */
#घोषणा MP_RX_AGGR_PKT_LIMIT_REACHED(a)					\
			(a->mpa_rx.pkt_cnt == a->mpa_rx.pkt_aggr_limit)

/* SDIO Rx aggregation in progress ? */
#घोषणा MP_RX_AGGR_IN_PROGRESS(a) (a->mpa_rx.pkt_cnt > 0)

/* SDIO Rx aggregation buffer room क्रम next packet ? */
#घोषणा MP_RX_AGGR_BUF_HAS_ROOM(a, rx_len)				\
			((a->mpa_rx.buf_len+rx_len) <= a->mpa_rx.buf_size)

/* Reset SDIO Rx aggregation buffer parameters */
#घोषणा MP_RX_AGGR_BUF_RESET(a) करो अणु					\
	a->mpa_rx.pkt_cnt = 0;						\
	a->mpa_rx.buf_len = 0;						\
	a->mpa_rx.ports = 0;						\
	a->mpa_rx.start_port = 0;					\
पूर्ण जबतक (0)

/* data काष्ठाure क्रम SDIO MPA TX */
काष्ठा mwअगरiex_sdio_mpa_tx अणु
	/* multiport tx aggregation buffer poपूर्णांकer */
	u8 *buf;
	u32 buf_len;
	u32 pkt_cnt;
	u32 ports;
	u16 start_port;
	u8 enabled;
	u32 buf_size;
	u32 pkt_aggr_limit;
पूर्ण;

काष्ठा mwअगरiex_sdio_mpa_rx अणु
	u8 *buf;
	u32 buf_len;
	u32 pkt_cnt;
	u32 ports;
	u16 start_port;

	काष्ठा sk_buff **skb_arr;
	u32 *len_arr;

	u8 enabled;
	u32 buf_size;
	u32 pkt_aggr_limit;
पूर्ण;

पूर्णांक mwअगरiex_bus_रेजिस्टर(व्योम);
व्योम mwअगरiex_bus_unरेजिस्टर(व्योम);

काष्ठा mwअगरiex_sdio_card_reg अणु
	u8 start_rd_port;
	u8 start_wr_port;
	u8 base_0_reg;
	u8 base_1_reg;
	u8 poll_reg;
	u8 host_पूर्णांक_enable;
	u8 host_पूर्णांक_rsr_reg;
	u8 host_पूर्णांक_status_reg;
	u8 host_पूर्णांक_mask_reg;
	u8 status_reg_0;
	u8 status_reg_1;
	u8 sdio_पूर्णांक_mask;
	u32 data_port_mask;
	u8 io_port_0_reg;
	u8 io_port_1_reg;
	u8 io_port_2_reg;
	u8 max_mp_regs;
	u8 rd_biपंचांगap_l;
	u8 rd_biपंचांगap_u;
	u8 rd_biपंचांगap_1l;
	u8 rd_biपंचांगap_1u;
	u8 wr_biपंचांगap_l;
	u8 wr_biपंचांगap_u;
	u8 wr_biपंचांगap_1l;
	u8 wr_biपंचांगap_1u;
	u8 rd_len_p0_l;
	u8 rd_len_p0_u;
	u8 card_misc_cfg_reg;
	u8 card_cfg_2_1_reg;
	u8 cmd_rd_len_0;
	u8 cmd_rd_len_1;
	u8 cmd_rd_len_2;
	u8 cmd_rd_len_3;
	u8 cmd_cfg_0;
	u8 cmd_cfg_1;
	u8 cmd_cfg_2;
	u8 cmd_cfg_3;
	u8 fw_dump_host_पढ़ोy;
	u8 fw_dump_ctrl;
	u8 fw_dump_start;
	u8 fw_dump_end;
	u8 func1_dump_reg_start;
	u8 func1_dump_reg_end;
	u8 func1_scratch_reg;
	u8 func1_spec_reg_num;
	u8 func1_spec_reg_table[MWIFIEX_MAX_FUNC2_REG_NUM];
पूर्ण;

काष्ठा sdio_mmc_card अणु
	काष्ठा sdio_func *func;
	काष्ठा mwअगरiex_adapter *adapter;

	काष्ठा completion fw_करोne;
	स्थिर अक्षर *firmware;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg;
	u8 max_ports;
	u8 mp_agg_pkt_limit;
	u16 tx_buf_size;
	u32 mp_tx_agg_buf_size;
	u32 mp_rx_agg_buf_size;

	u32 mp_rd_biपंचांगap;
	u32 mp_wr_biपंचांगap;

	u16 mp_end_port;
	u32 mp_data_port_mask;

	u8 curr_rd_port;
	u8 curr_wr_port;

	u8 *mp_regs;
	bool supports_sdio_new_mode;
	bool has_control_mask;
	bool can_dump_fw;
	bool fw_dump_enh;
	bool can_स्वतः_tdls;
	bool can_ext_scan;

	काष्ठा mwअगरiex_sdio_mpa_tx mpa_tx;
	काष्ठा mwअगरiex_sdio_mpa_rx mpa_rx;

	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ work_flags;
पूर्ण;

काष्ठा mwअगरiex_sdio_device अणु
	स्थिर अक्षर *firmware;
	स्थिर काष्ठा mwअगरiex_sdio_card_reg *reg;
	u8 max_ports;
	u8 mp_agg_pkt_limit;
	u16 tx_buf_size;
	u32 mp_tx_agg_buf_size;
	u32 mp_rx_agg_buf_size;
	bool supports_sdio_new_mode;
	bool has_control_mask;
	bool can_dump_fw;
	bool fw_dump_enh;
	bool can_स्वतः_tdls;
	bool can_ext_scan;
पूर्ण;

/*
 * .cmdrsp_complete handler
 */
अटल अंतरभूत पूर्णांक mwअगरiex_sdio_cmdrsp_complete(काष्ठा mwअगरiex_adapter *adapter,
					       काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
	वापस 0;
पूर्ण

/*
 * .event_complete handler
 */
अटल अंतरभूत पूर्णांक mwअगरiex_sdio_event_complete(काष्ठा mwअगरiex_adapter *adapter,
					      काष्ठा sk_buff *skb)
अणु
	dev_kमुक्त_skb_any(skb);
	वापस 0;
पूर्ण

अटल अंतरभूत bool
mp_rx_aggr_port_limit_reached(काष्ठा sdio_mmc_card *card)
अणु
	u8 पंचांगp;

	अगर (card->curr_rd_port < card->mpa_rx.start_port) अणु
		अगर (card->supports_sdio_new_mode)
			पंचांगp = card->mp_end_port >> 1;
		अन्यथा
			पंचांगp = card->mp_agg_pkt_limit;

		अगर (((card->max_ports - card->mpa_rx.start_port) +
		    card->curr_rd_port) >= पंचांगp)
			वापस true;
	पूर्ण

	अगर (!card->supports_sdio_new_mode)
		वापस false;

	अगर ((card->curr_rd_port - card->mpa_rx.start_port) >=
	    (card->mp_end_port >> 1))
		वापस true;

	वापस false;
पूर्ण

अटल अंतरभूत bool
mp_tx_aggr_port_limit_reached(काष्ठा sdio_mmc_card *card)
अणु
	u16 पंचांगp;

	अगर (card->curr_wr_port < card->mpa_tx.start_port) अणु
		अगर (card->supports_sdio_new_mode)
			पंचांगp = card->mp_end_port >> 1;
		अन्यथा
			पंचांगp = card->mp_agg_pkt_limit;

		अगर (((card->max_ports - card->mpa_tx.start_port) +
		    card->curr_wr_port) >= पंचांगp)
			वापस true;
	पूर्ण

	अगर (!card->supports_sdio_new_mode)
		वापस false;

	अगर ((card->curr_wr_port - card->mpa_tx.start_port) >=
	    (card->mp_end_port >> 1))
		वापस true;

	वापस false;
पूर्ण

/* Prepare to copy current packet from card to SDIO Rx aggregation buffer */
अटल अंतरभूत व्योम mp_rx_aggr_setup(काष्ठा sdio_mmc_card *card,
				    u16 rx_len, u8 port)
अणु
	card->mpa_rx.buf_len += rx_len;

	अगर (!card->mpa_rx.pkt_cnt)
		card->mpa_rx.start_port = port;

	अगर (card->supports_sdio_new_mode) अणु
		card->mpa_rx.ports |= (1 << port);
	पूर्ण अन्यथा अणु
		अगर (card->mpa_rx.start_port <= port)
			card->mpa_rx.ports |= 1 << (card->mpa_rx.pkt_cnt);
		अन्यथा
			card->mpa_rx.ports |= 1 << (card->mpa_rx.pkt_cnt + 1);
	पूर्ण
	card->mpa_rx.skb_arr[card->mpa_rx.pkt_cnt] = शून्य;
	card->mpa_rx.len_arr[card->mpa_rx.pkt_cnt] = rx_len;
	card->mpa_rx.pkt_cnt++;
पूर्ण
#पूर्ण_अगर /* _MWIFIEX_SDIO_H */
