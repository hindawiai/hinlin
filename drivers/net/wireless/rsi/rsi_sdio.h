<शैली गुरु>
/*
 * @section LICENSE
 * Copyright (c) 2014 Redpine Signals Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#अगर_अघोषित __RSI_SDIO_INTF__
#घोषणा __RSI_SDIO_INTF__

#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sd.h>
#समावेश <linux/mmc/sdio_ids.h>
#समावेश "rsi_main.h"

क्रमागत sdio_पूर्णांकerrupt_type अणु
	BUFFER_FULL         = 0x0,
	BUFFER_AVAILABLE    = 0x2,
	FIRMWARE_ASSERT_IND = 0x3,
	MSDU_PACKET_PENDING = 0x4,
	UNKNOWN_INT         = 0XE
पूर्ण;

/* Buffer status रेजिस्टर related info */
#घोषणा PKT_BUFF_SEMI_FULL                      0
#घोषणा PKT_BUFF_FULL                           1
#घोषणा PKT_MGMT_BUFF_FULL                      2
#घोषणा MSDU_PKT_PENDING                        3
#घोषणा RECV_NUM_BLOCKS                         4
/* Interrupt Bit Related Macros */
#घोषणा PKT_BUFF_AVAILABLE                      1
#घोषणा FW_ASSERT_IND                           2

#घोषणा RSI_MASTER_REG_BUF_SIZE			12

#घोषणा RSI_DEVICE_BUFFER_STATUS_REGISTER       0xf3
#घोषणा RSI_FN1_INT_REGISTER                    0xf9
#घोषणा RSI_INT_ENABLE_REGISTER			0x04
#घोषणा RSI_INT_ENABLE_MASK			0xfc
#घोषणा RSI_SD_REQUEST_MASTER                   0x10000

/* FOR SD CARD ONLY */
#घोषणा SDIO_RX_NUM_BLOCKS_REG                  0x000F1
#घोषणा SDIO_FW_STATUS_REG                      0x000F2
#घोषणा SDIO_NXT_RD_DELAY2                      0x000F5
#घोषणा SDIO_MASTER_ACCESS_MSBYTE               0x000FA
#घोषणा SDIO_MASTER_ACCESS_LSBYTE               0x000FB
#घोषणा SDIO_READ_START_LVL                     0x000FC
#घोषणा SDIO_READ_FIFO_CTL                      0x000FD
#घोषणा SDIO_WRITE_FIFO_CTL                     0x000FE
#घोषणा SDIO_WAKEUP_REG				0x000FF
#घोषणा SDIO_FUN1_INTR_CLR_REG                  0x0008
#घोषणा SDIO_REG_HIGH_SPEED                     0x0013

#घोषणा RSI_GET_SDIO_INTERRUPT_TYPE(_I, TYPE)      \
	अणु					   \
		TYPE =                             \
		(_I & (1 << PKT_BUFF_AVAILABLE)) ? \
		BUFFER_AVAILABLE :		   \
		(_I & (1 << MSDU_PKT_PENDING)) ?   \
		MSDU_PACKET_PENDING :              \
		(_I & (1 << FW_ASSERT_IND)) ?      \
		FIRMWARE_ASSERT_IND : UNKNOWN_INT; \
	पूर्ण

/* common रेजिस्टरs in SDIO function1 */
#घोषणा TA_SOFT_RESET_REG            0x0004
#घोषणा TA_TH0_PC_REG                0x0400
#घोषणा TA_HOLD_THREAD_REG           0x0844
#घोषणा TA_RELEASE_THREAD_REG        0x0848

#घोषणा TA_SOFT_RST_CLR              0
#घोषणा TA_SOFT_RST_SET              BIT(0)
#घोषणा TA_PC_ZERO                   0
#घोषणा TA_HOLD_THREAD_VALUE         0xF
#घोषणा TA_RELEASE_THREAD_VALUE      0xF
#घोषणा TA_BASE_ADDR                 0x2200
#घोषणा MISC_CFG_BASE_ADDR           0x4105

काष्ठा receive_info अणु
	bool buffer_full;
	bool semi_buffer_full;
	bool mgmt_buffer_full;
	u32 mgmt_buf_full_counter;
	u32 buf_semi_full_counter;
	u8 watch_bufferfull_count;
	u32 sdio_पूर्णांकr_status_zero;
	u32 sdio_पूर्णांक_counter;
	u32 total_sdio_msdu_pending_पूर्णांकr;
	u32 total_sdio_unknown_पूर्णांकr;
	u32 buf_full_counter;
	u32 buf_available_counter;
पूर्ण;

काष्ठा rsi_91x_sdiodev अणु
	काष्ठा sdio_func *pfunction;
	काष्ठा task_काष्ठा *sdio_irq_task;
	काष्ठा receive_info rx_info;
	u32 next_पढ़ो_delay;
	u32 sdio_high_speed_enable;
	u8 sdio_घड़ी_speed;
	u32 cardcapability;
	u8 prev_desc[16];
	u16 tx_blk_size;
	u8 ग_लिखो_fail;
	bool buff_status_updated;
	काष्ठा rsi_thपढ़ो rx_thपढ़ो;
	u8 pktbuffer[8192] __aligned(4);
पूर्ण;

पूर्णांक rsi_init_sdio_slave_regs(काष्ठा rsi_hw *adapter);
पूर्णांक rsi_sdio_पढ़ो_रेजिस्टर(काष्ठा rsi_hw *adapter, u32 addr, u8 *data);
पूर्णांक rsi_sdio_host_पूर्णांकf_पढ़ो_pkt(काष्ठा rsi_hw *adapter, u8 *pkt, u32 length);
पूर्णांक rsi_sdio_ग_लिखो_रेजिस्टर(काष्ठा rsi_hw *adapter, u8 function,
			    u32 addr, u8 *data);
पूर्णांक rsi_sdio_ग_लिखो_रेजिस्टर_multiple(काष्ठा rsi_hw *adapter, u32 addr,
				     u8 *data, u16 count);
पूर्णांक rsi_sdio_master_access_msword(काष्ठा rsi_hw *adapter, u16 ms_word);
व्योम rsi_sdio_ack_पूर्णांकr(काष्ठा rsi_hw *adapter, u8 पूर्णांक_bit);
पूर्णांक rsi_sdio_determine_event_समयout(काष्ठा rsi_hw *adapter);
पूर्णांक rsi_sdio_check_buffer_status(काष्ठा rsi_hw *adapter, u8 q_num);
व्योम rsi_sdio_rx_thपढ़ो(काष्ठा rsi_common *common);
#पूर्ण_अगर
