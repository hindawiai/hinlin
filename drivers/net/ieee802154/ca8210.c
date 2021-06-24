<शैली गुरु>
/*
 * http://www.cascoda.com/products/ca-821x/
 * Copyright (c) 2016, Cascoda, Ltd.
 * All rights reserved.
 *
 * This code is dual-licensed under both GPLv2 and 3-clause BSD. What follows is
 * the license notice क्रम both respectively.
 *
 *******************************************************************************
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *******************************************************************************
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary क्रमm must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the करोcumentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to enकरोrse or promote products derived from this software without
 * specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/ieee802154.h>
#समावेश <linux/पन.स>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/poll.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/माला.स>
#समावेश <linux/workqueue.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <net/ieee802154_netdev.h>
#समावेश <net/mac802154.h>

#घोषणा DRIVER_NAME "ca8210"

/* बाह्यal घड़ी frequencies */
#घोषणा ONE_MHZ      1000000
#घोषणा TWO_MHZ      (2 * ONE_MHZ)
#घोषणा FOUR_MHZ     (4 * ONE_MHZ)
#घोषणा EIGHT_MHZ    (8 * ONE_MHZ)
#घोषणा SIXTEEN_MHZ  (16 * ONE_MHZ)

/* spi स्थिरants */
#घोषणा CA8210_SPI_BUF_SIZE 256
#घोषणा CA8210_SYNC_TIMEOUT 1000     /* Timeout क्रम synchronous commands [ms] */

/* test पूर्णांकerface स्थिरants */
#घोषणा CA8210_TEST_INT_खाता_NAME "ca8210_test"
#घोषणा CA8210_TEST_INT_FIFO_SIZE 256

/* MAC status क्रमागतerations */
#घोषणा MAC_SUCCESS                     (0x00)
#घोषणा MAC_ERROR                       (0x01)
#घोषणा MAC_CANCELLED                   (0x02)
#घोषणा MAC_READY_FOR_POLL              (0x03)
#घोषणा MAC_COUNTER_ERROR               (0xDB)
#घोषणा MAC_IMPROPER_KEY_TYPE           (0xDC)
#घोषणा MAC_IMPROPER_SECURITY_LEVEL     (0xDD)
#घोषणा MAC_UNSUPPORTED_LEGACY          (0xDE)
#घोषणा MAC_UNSUPPORTED_SECURITY        (0xDF)
#घोषणा MAC_BEACON_LOST                 (0xE0)
#घोषणा MAC_CHANNEL_ACCESS_FAILURE      (0xE1)
#घोषणा MAC_DENIED                      (0xE2)
#घोषणा MAC_DISABLE_TRX_FAILURE         (0xE3)
#घोषणा MAC_SECURITY_ERROR              (0xE4)
#घोषणा MAC_FRAME_TOO_LONG              (0xE5)
#घोषणा MAC_INVALID_GTS                 (0xE6)
#घोषणा MAC_INVALID_HANDLE              (0xE7)
#घोषणा MAC_INVALID_PARAMETER           (0xE8)
#घोषणा MAC_NO_ACK                      (0xE9)
#घोषणा MAC_NO_BEACON                   (0xEA)
#घोषणा MAC_NO_DATA                     (0xEB)
#घोषणा MAC_NO_SHORT_ADDRESS            (0xEC)
#घोषणा MAC_OUT_OF_CAP                  (0xED)
#घोषणा MAC_PAN_ID_CONFLICT             (0xEE)
#घोषणा MAC_REALIGNMENT                 (0xEF)
#घोषणा MAC_TRANSACTION_EXPIRED         (0xF0)
#घोषणा MAC_TRANSACTION_OVERFLOW        (0xF1)
#घोषणा MAC_TX_ACTIVE                   (0xF2)
#घोषणा MAC_UNAVAILABLE_KEY             (0xF3)
#घोषणा MAC_UNSUPPORTED_ATTRIBUTE       (0xF4)
#घोषणा MAC_INVALID_ADDRESS             (0xF5)
#घोषणा MAC_ON_TIME_TOO_LONG            (0xF6)
#घोषणा MAC_PAST_TIME                   (0xF7)
#घोषणा MAC_TRACKING_OFF                (0xF8)
#घोषणा MAC_INVALID_INDEX               (0xF9)
#घोषणा MAC_LIMIT_REACHED               (0xFA)
#घोषणा MAC_READ_ONLY                   (0xFB)
#घोषणा MAC_SCAN_IN_PROGRESS            (0xFC)
#घोषणा MAC_SUPERFRAME_OVERLAP          (0xFD)
#घोषणा MAC_SYSTEM_ERROR                (0xFF)

/* HWME attribute IDs */
#घोषणा HWME_EDTHRESHOLD       (0x04)
#घोषणा HWME_EDVALUE           (0x06)
#घोषणा HWME_SYSCLKOUT         (0x0F)
#घोषणा HWME_LQILIMIT          (0x11)

/* TDME attribute IDs */
#घोषणा TDME_CHANNEL          (0x00)
#घोषणा TDME_ATM_CONFIG       (0x06)

#घोषणा MAX_HWME_ATTRIBUTE_SIZE  16
#घोषणा MAX_TDME_ATTRIBUTE_SIZE  2

/* PHY/MAC PIB Attribute Enumerations */
#घोषणा PHY_CURRENT_CHANNEL               (0x00)
#घोषणा PHY_TRANSMIT_POWER                (0x02)
#घोषणा PHY_CCA_MODE                      (0x03)
#घोषणा MAC_ASSOCIATION_PERMIT            (0x41)
#घोषणा MAC_AUTO_REQUEST                  (0x42)
#घोषणा MAC_BATT_LIFE_EXT                 (0x43)
#घोषणा MAC_BATT_LIFE_EXT_PERIODS         (0x44)
#घोषणा MAC_BEACON_PAYLOAD                (0x45)
#घोषणा MAC_BEACON_PAYLOAD_LENGTH         (0x46)
#घोषणा MAC_BEACON_ORDER                  (0x47)
#घोषणा MAC_GTS_PERMIT                    (0x4d)
#घोषणा MAC_MAX_CSMA_BACKOFFS             (0x4e)
#घोषणा MAC_MIN_BE                        (0x4f)
#घोषणा MAC_PAN_ID                        (0x50)
#घोषणा MAC_PROMISCUOUS_MODE              (0x51)
#घोषणा MAC_RX_ON_WHEN_IDLE               (0x52)
#घोषणा MAC_SHORT_ADDRESS                 (0x53)
#घोषणा MAC_SUPERFRAME_ORDER              (0x54)
#घोषणा MAC_ASSOCIATED_PAN_COORD          (0x56)
#घोषणा MAC_MAX_BE                        (0x57)
#घोषणा MAC_MAX_FRAME_RETRIES             (0x59)
#घोषणा MAC_RESPONSE_WAIT_TIME            (0x5A)
#घोषणा MAC_SECURITY_ENABLED              (0x5D)

#घोषणा MAC_AUTO_REQUEST_SECURITY_LEVEL   (0x78)
#घोषणा MAC_AUTO_REQUEST_KEY_ID_MODE      (0x79)

#घोषणा NS_IEEE_ADDRESS                   (0xFF) /* Non-standard IEEE address */

/* MAC Address Mode Definitions */
#घोषणा MAC_MODE_NO_ADDR                (0x00)
#घोषणा MAC_MODE_SHORT_ADDR             (0x02)
#घोषणा MAC_MODE_LONG_ADDR              (0x03)

/* MAC स्थिरants */
#घोषणा MAX_BEACON_OVERHEAD        (75)
#घोषणा MAX_BEACON_PAYLOAD_LENGTH  (IEEE802154_MTU - MAX_BEACON_OVERHEAD)

#घोषणा MAX_ATTRIBUTE_SIZE              (122)
#घोषणा MAX_DATA_SIZE                   (114)

#घोषणा CA8210_VALID_CHANNELS                 (0x07FFF800)

/* MAC workarounds क्रम V1.1 and MPW silicon (V0.x) */
#घोषणा CA8210_MAC_WORKAROUNDS (0)
#घोषणा CA8210_MAC_MPW         (0)

/* memory manipulation macros */
#घोषणा LS_BYTE(x)     ((u8)((x) & 0xFF))
#घोषणा MS_BYTE(x)     ((u8)(((x) >> 8) & 0xFF))

/* message ID codes in SPI commands */
/* करोwnstream */
#घोषणा MCPS_DATA_REQUEST                     (0x00)
#घोषणा MLME_ASSOCIATE_REQUEST                (0x02)
#घोषणा MLME_ASSOCIATE_RESPONSE               (0x03)
#घोषणा MLME_DISASSOCIATE_REQUEST             (0x04)
#घोषणा MLME_GET_REQUEST                      (0x05)
#घोषणा MLME_ORPHAN_RESPONSE                  (0x06)
#घोषणा MLME_RESET_REQUEST                    (0x07)
#घोषणा MLME_RX_ENABLE_REQUEST                (0x08)
#घोषणा MLME_SCAN_REQUEST                     (0x09)
#घोषणा MLME_SET_REQUEST                      (0x0A)
#घोषणा MLME_START_REQUEST                    (0x0B)
#घोषणा MLME_POLL_REQUEST                     (0x0D)
#घोषणा HWME_SET_REQUEST                      (0x0E)
#घोषणा HWME_GET_REQUEST                      (0x0F)
#घोषणा TDME_SETSFR_REQUEST                   (0x11)
#घोषणा TDME_GETSFR_REQUEST                   (0x12)
#घोषणा TDME_SET_REQUEST                      (0x14)
/* upstream */
#घोषणा MCPS_DATA_INDICATION                  (0x00)
#घोषणा MCPS_DATA_CONFIRM                     (0x01)
#घोषणा MLME_RESET_CONFIRM                    (0x0A)
#घोषणा MLME_SET_CONFIRM                      (0x0E)
#घोषणा MLME_START_CONFIRM                    (0x0F)
#घोषणा HWME_SET_CONFIRM                      (0x12)
#घोषणा HWME_GET_CONFIRM                      (0x13)
#घोषणा HWME_WAKEUP_INDICATION		      (0x15)
#घोषणा TDME_SETSFR_CONFIRM                   (0x17)

/* SPI command IDs */
/* bit indicating a confirm or indication from slave to master */
#घोषणा SPI_S2M                            (0x20)
/* bit indicating a synchronous message */
#घोषणा SPI_SYN                            (0x40)

/* SPI command definitions */
#घोषणा SPI_IDLE                           (0xFF)
#घोषणा SPI_NACK                           (0xF0)

#घोषणा SPI_MCPS_DATA_REQUEST          (MCPS_DATA_REQUEST)
#घोषणा SPI_MCPS_DATA_INDICATION       (MCPS_DATA_INDICATION + SPI_S2M)
#घोषणा SPI_MCPS_DATA_CONFIRM          (MCPS_DATA_CONFIRM + SPI_S2M)

#घोषणा SPI_MLME_ASSOCIATE_REQUEST     (MLME_ASSOCIATE_REQUEST)
#घोषणा SPI_MLME_RESET_REQUEST         (MLME_RESET_REQUEST + SPI_SYN)
#घोषणा SPI_MLME_SET_REQUEST           (MLME_SET_REQUEST + SPI_SYN)
#घोषणा SPI_MLME_START_REQUEST         (MLME_START_REQUEST + SPI_SYN)
#घोषणा SPI_MLME_RESET_CONFIRM         (MLME_RESET_CONFIRM + SPI_S2M + SPI_SYN)
#घोषणा SPI_MLME_SET_CONFIRM           (MLME_SET_CONFIRM + SPI_S2M + SPI_SYN)
#घोषणा SPI_MLME_START_CONFIRM         (MLME_START_CONFIRM + SPI_S2M + SPI_SYN)

#घोषणा SPI_HWME_SET_REQUEST           (HWME_SET_REQUEST + SPI_SYN)
#घोषणा SPI_HWME_GET_REQUEST           (HWME_GET_REQUEST + SPI_SYN)
#घोषणा SPI_HWME_SET_CONFIRM           (HWME_SET_CONFIRM + SPI_S2M + SPI_SYN)
#घोषणा SPI_HWME_GET_CONFIRM           (HWME_GET_CONFIRM + SPI_S2M + SPI_SYN)
#घोषणा SPI_HWME_WAKEUP_INDICATION     (HWME_WAKEUP_INDICATION + SPI_S2M)

#घोषणा SPI_TDME_SETSFR_REQUEST        (TDME_SETSFR_REQUEST + SPI_SYN)
#घोषणा SPI_TDME_SET_REQUEST           (TDME_SET_REQUEST + SPI_SYN)
#घोषणा SPI_TDME_SETSFR_CONFIRM        (TDME_SETSFR_CONFIRM + SPI_S2M + SPI_SYN)

/* TDME SFR addresses */
/* Page 0 */
#घोषणा CA8210_SFR_PACFG                   (0xB1)
#घोषणा CA8210_SFR_MACCON                  (0xD8)
#घोषणा CA8210_SFR_PACFGIB                 (0xFE)
/* Page 1 */
#घोषणा CA8210_SFR_LOTXCAL                 (0xBF)
#घोषणा CA8210_SFR_PTHRH                   (0xD1)
#घोषणा CA8210_SFR_PRECFG                  (0xD3)
#घोषणा CA8210_SFR_LNAGX40                 (0xE1)
#घोषणा CA8210_SFR_LNAGX41                 (0xE2)
#घोषणा CA8210_SFR_LNAGX42                 (0xE3)
#घोषणा CA8210_SFR_LNAGX43                 (0xE4)
#घोषणा CA8210_SFR_LNAGX44                 (0xE5)
#घोषणा CA8210_SFR_LNAGX45                 (0xE6)
#घोषणा CA8210_SFR_LNAGX46                 (0xE7)
#घोषणा CA8210_SFR_LNAGX47                 (0xE9)

#घोषणा PACFGIB_DEFAULT_CURRENT            (0x3F)
#घोषणा PTHRH_DEFAULT_THRESHOLD            (0x5A)
#घोषणा LNAGX40_DEFAULT_GAIN               (0x29) /* 10dB */
#घोषणा LNAGX41_DEFAULT_GAIN               (0x54) /* 21dB */
#घोषणा LNAGX42_DEFAULT_GAIN               (0x6C) /* 27dB */
#घोषणा LNAGX43_DEFAULT_GAIN               (0x7A) /* 30dB */
#घोषणा LNAGX44_DEFAULT_GAIN               (0x84) /* 33dB */
#घोषणा LNAGX45_DEFAULT_GAIN               (0x8B) /* 34dB */
#घोषणा LNAGX46_DEFAULT_GAIN               (0x92) /* 36dB */
#घोषणा LNAGX47_DEFAULT_GAIN               (0x96) /* 37dB */

#घोषणा CA8210_IOCTL_HARD_RESET            (0x00)

/* Structs/Enums */

/**
 * काष्ठा cas_control - spi transfer काष्ठाure
 * @msg:                  spi_message क्रम each exchange
 * @transfer:             spi_transfer क्रम each exchange
 * @tx_buf:               source array क्रम transmission
 * @tx_in_buf:            array storing bytes received during transmission
 * @priv:                 poपूर्णांकer to निजी data
 *
 * This काष्ठाure stores all the necessary data passed around during a single
 * spi exchange.
 */
काष्ठा cas_control अणु
	काष्ठा spi_message msg;
	काष्ठा spi_transfer transfer;

	u8 tx_buf[CA8210_SPI_BUF_SIZE];
	u8 tx_in_buf[CA8210_SPI_BUF_SIZE];

	काष्ठा ca8210_priv *priv;
पूर्ण;

/**
 * काष्ठा ca8210_test - ca8210 test पूर्णांकerface काष्ठाure
 * @ca8210_dfs_spi_पूर्णांक: poपूर्णांकer to the entry in the debug fs क्रम this device
 * @up_fअगरo:            fअगरo क्रम upstream messages
 * @पढ़ोq:              पढ़ो रुको queue
 *
 * This काष्ठाure stores all the data pertaining to the debug पूर्णांकerface
 */
काष्ठा ca8210_test अणु
	काष्ठा dentry *ca8210_dfs_spi_पूर्णांक;
	काष्ठा kfअगरo up_fअगरo;
	रुको_queue_head_t पढ़ोq;
पूर्ण;

/**
 * काष्ठा ca8210_priv - ca8210 निजी data काष्ठाure
 * @spi:                    poपूर्णांकer to the ca8210 spi device object
 * @hw:                     poपूर्णांकer to the ca8210 ieee802154_hw object
 * @hw_रेजिस्टरed:          true अगर hw has been रेजिस्टरed with ieee802154
 * @lock:                   spinlock protecting the निजी data area
 * @mlme_workqueue:           workqueue क्रम triggering MLME Reset
 * @irq_workqueue:          workqueue क्रम irq processing
 * @tx_skb:                 current socket buffer to transmit
 * @nexपंचांगsduhandle:         msdu handle to pass to the 15.4 MAC layer क्रम the
 *                           next transmission
 * @clk:                    बाह्यal घड़ी provided by the ca8210
 * @last_dsn:               sequence number of last data packet received, क्रम
 *                           resend detection
 * @test:                   test पूर्णांकerface data section क्रम this instance
 * @async_tx_pending:       true अगर an asynchronous transmission was started and
 *                           is not complete
 * @sync_command_response:  poपूर्णांकer to buffer to fill with sync response
 * @ca8210_is_awake:        nonzero अगर ca8210 is initialised, पढ़ोy क्रम comms
 * @sync_करोwn:              counts number of करोwnstream synchronous commands
 * @sync_up:                counts number of upstream synchronous commands
 * @spi_transfer_complete:  completion object क्रम a single spi_transfer
 * @sync_exchange_complete: completion object क्रम a complete synchronous API
 *                          exchange
 * @promiscuous:            whether the ca8210 is in promiscuous mode or not
 * @retries:                records how many बार the current pending spi
 *                          transfer has been retried
 */
काष्ठा ca8210_priv अणु
	काष्ठा spi_device *spi;
	काष्ठा ieee802154_hw *hw;
	bool hw_रेजिस्टरed;
	spinlock_t lock;
	काष्ठा workqueue_काष्ठा *mlme_workqueue;
	काष्ठा workqueue_काष्ठा *irq_workqueue;
	काष्ठा sk_buff *tx_skb;
	u8 nexपंचांगsduhandle;
	काष्ठा clk *clk;
	पूर्णांक last_dsn;
	काष्ठा ca8210_test test;
	bool async_tx_pending;
	u8 *sync_command_response;
	काष्ठा completion ca8210_is_awake;
	पूर्णांक sync_करोwn, sync_up;
	काष्ठा completion spi_transfer_complete, sync_exchange_complete;
	bool promiscuous;
	पूर्णांक retries;
पूर्ण;

/**
 * काष्ठा work_priv_container - link between a work object and the relevant
 *                              device's निजी data
 * @work: work object being executed
 * @priv: device's निजी data section
 *
 */
काष्ठा work_priv_container अणु
	काष्ठा work_काष्ठा work;
	काष्ठा ca8210_priv *priv;
पूर्ण;

/**
 * काष्ठा ca8210_platक्रमm_data - ca8210 platक्रमm data काष्ठाure
 * @extघड़ीenable: true अगर the बाह्यal घड़ी is to be enabled
 * @extघड़ीfreq:   frequency of the बाह्यal घड़ी
 * @extघड़ीgpio:   ca8210 output gpio of the बाह्यal घड़ी
 * @gpio_reset:     gpio number of ca8210 reset line
 * @gpio_irq:       gpio number of ca8210 पूर्णांकerrupt line
 * @irq_id:         identअगरier क्रम the ca8210 irq
 *
 */
काष्ठा ca8210_platक्रमm_data अणु
	bool extघड़ीenable;
	अचिन्हित पूर्णांक extघड़ीfreq;
	अचिन्हित पूर्णांक extघड़ीgpio;
	पूर्णांक gpio_reset;
	पूर्णांक gpio_irq;
	पूर्णांक irq_id;
पूर्ण;

/**
 * काष्ठा fulladdr - full MAC addressing inक्रमmation काष्ठाure
 * @mode:    address mode (none, लघु, extended)
 * @pan_id:  16-bit LE pan id
 * @address: LE address, variable length as specअगरied by mode
 *
 */
काष्ठा fulladdr अणु
	u8         mode;
	u8         pan_id[2];
	u8         address[8];
पूर्ण;

/**
 * जोड़ macaddr: generic MAC address container
 * @लघु_address: 16-bit लघु address
 * @ieee_address:  64-bit extended address as LE byte array
 *
 */
जोड़ macaddr अणु
	u16        लघु_address;
	u8         ieee_address[8];
पूर्ण;

/**
 * काष्ठा secspec: security specअगरication क्रम SAP commands
 * @security_level: 0-7, controls level of authentication & encryption
 * @key_id_mode:    0-3, specअगरies how to obtain key
 * @key_source:     extended key retrieval data
 * @key_index:      single-byte key identअगरier
 *
 */
काष्ठा secspec अणु
	u8         security_level;
	u8         key_id_mode;
	u8         key_source[8];
	u8         key_index;
पूर्ण;

/* करोwnlink functions parameter set definitions */
काष्ठा mcps_data_request_pset अणु
	u8              src_addr_mode;
	काष्ठा fulladdr dst;
	u8              msdu_length;
	u8              msdu_handle;
	u8              tx_options;
	u8              msdu[MAX_DATA_SIZE];
पूर्ण;

काष्ठा mlme_set_request_pset अणु
	u8         pib_attribute;
	u8         pib_attribute_index;
	u8         pib_attribute_length;
	u8         pib_attribute_value[MAX_ATTRIBUTE_SIZE];
पूर्ण;

काष्ठा hwme_set_request_pset अणु
	u8         hw_attribute;
	u8         hw_attribute_length;
	u8         hw_attribute_value[MAX_HWME_ATTRIBUTE_SIZE];
पूर्ण;

काष्ठा hwme_get_request_pset अणु
	u8         hw_attribute;
पूर्ण;

काष्ठा tdme_setsfr_request_pset अणु
	u8         sfr_page;
	u8         sfr_address;
	u8         sfr_value;
पूर्ण;

/* uplink functions parameter set definitions */
काष्ठा hwme_set_confirm_pset अणु
	u8         status;
	u8         hw_attribute;
पूर्ण;

काष्ठा hwme_get_confirm_pset अणु
	u8         status;
	u8         hw_attribute;
	u8         hw_attribute_length;
	u8         hw_attribute_value[MAX_HWME_ATTRIBUTE_SIZE];
पूर्ण;

काष्ठा tdme_setsfr_confirm_pset अणु
	u8         status;
	u8         sfr_page;
	u8         sfr_address;
पूर्ण;

काष्ठा mac_message अणु
	u8      command_id;
	u8      length;
	जोड़ अणु
		काष्ठा mcps_data_request_pset       data_req;
		काष्ठा mlme_set_request_pset        set_req;
		काष्ठा hwme_set_request_pset        hwme_set_req;
		काष्ठा hwme_get_request_pset        hwme_get_req;
		काष्ठा tdme_setsfr_request_pset     tdme_set_sfr_req;
		काष्ठा hwme_set_confirm_pset        hwme_set_cnf;
		काष्ठा hwme_get_confirm_pset        hwme_get_cnf;
		काष्ठा tdme_setsfr_confirm_pset     tdme_set_sfr_cnf;
		u8                                  u8param;
		u8                                  status;
		u8                                  payload[148];
	पूर्ण pdata;
पूर्ण;

जोड़ pa_cfg_sfr अणु
	काष्ठा अणु
		u8 bias_current_trim     : 3;
		u8 /* reserved */        : 1;
		u8 buffer_capacitor_trim : 3;
		u8 boost                 : 1;
	पूर्ण;
	u8 paib;
पूर्ण;

काष्ठा preamble_cfg_sfr अणु
	u8 समयout_symbols      : 3;
	u8 acquisition_symbols  : 3;
	u8 search_symbols       : 2;
पूर्ण;

अटल पूर्णांक (*cascoda_api_upstream)(
	स्थिर u8 *buf,
	माप_प्रकार len,
	व्योम *device_ref
);

/**
 * link_to_linux_err() - Translates an 802.15.4 वापस code पूर्णांकo the बंदst
 *                       linux error
 * @link_status:  802.15.4 status code
 *
 * Return: 0 or Linux error code
 */
अटल पूर्णांक link_to_linux_err(पूर्णांक link_status)
अणु
	अगर (link_status < 0) अणु
		/* status is alपढ़ोy a Linux code */
		वापस link_status;
	पूर्ण
	चयन (link_status) अणु
	हाल MAC_SUCCESS:
	हाल MAC_REALIGNMENT:
		वापस 0;
	हाल MAC_IMPROPER_KEY_TYPE:
		वापस -EKEYREJECTED;
	हाल MAC_IMPROPER_SECURITY_LEVEL:
	हाल MAC_UNSUPPORTED_LEGACY:
	हाल MAC_DENIED:
		वापस -EACCES;
	हाल MAC_BEACON_LOST:
	हाल MAC_NO_ACK:
	हाल MAC_NO_BEACON:
		वापस -ENETUNREACH;
	हाल MAC_CHANNEL_ACCESS_FAILURE:
	हाल MAC_TX_ACTIVE:
	हाल MAC_SCAN_IN_PROGRESS:
		वापस -EBUSY;
	हाल MAC_DISABLE_TRX_FAILURE:
	हाल MAC_OUT_OF_CAP:
		वापस -EAGAIN;
	हाल MAC_FRAME_TOO_LONG:
		वापस -EMSGSIZE;
	हाल MAC_INVALID_GTS:
	हाल MAC_PAST_TIME:
		वापस -EBADSLT;
	हाल MAC_INVALID_HANDLE:
		वापस -EBADMSG;
	हाल MAC_INVALID_PARAMETER:
	हाल MAC_UNSUPPORTED_ATTRIBUTE:
	हाल MAC_ON_TIME_TOO_LONG:
	हाल MAC_INVALID_INDEX:
		वापस -EINVAL;
	हाल MAC_NO_DATA:
		वापस -ENODATA;
	हाल MAC_NO_SHORT_ADDRESS:
		वापस -EFAULT;
	हाल MAC_PAN_ID_CONFLICT:
		वापस -EADDRINUSE;
	हाल MAC_TRANSACTION_EXPIRED:
		वापस -ETIME;
	हाल MAC_TRANSACTION_OVERFLOW:
		वापस -ENOBUFS;
	हाल MAC_UNAVAILABLE_KEY:
		वापस -ENOKEY;
	हाल MAC_INVALID_ADDRESS:
		वापस -ENXIO;
	हाल MAC_TRACKING_OFF:
	हाल MAC_SUPERFRAME_OVERLAP:
		वापस -EREMOTEIO;
	हाल MAC_LIMIT_REACHED:
		वापस -EDQUOT;
	हाल MAC_READ_ONLY:
		वापस -EROFS;
	शेष:
		वापस -EPROTO;
	पूर्ण
पूर्ण

/**
 * ca8210_test_पूर्णांक_driver_ग_लिखो() - Writes a message to the test पूर्णांकerface to be
 *                                  पढ़ो by the userspace
 * @buf:  Buffer containing upstream message
 * @len:  length of message to ग_लिखो
 * @spi:  SPI device of message originator
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_test_पूर्णांक_driver_ग_लिखो(
	स्थिर u8       *buf,
	माप_प्रकार          len,
	व्योम           *spi
)
अणु
	काष्ठा ca8210_priv *priv = spi_get_drvdata(spi);
	काष्ठा ca8210_test *test = &priv->test;
	अक्षर *fअगरo_buffer;
	पूर्णांक i;

	dev_dbg(
		&priv->spi->dev,
		"test_interface: Buffering upstream message:\n"
	);
	क्रम (i = 0; i < len; i++)
		dev_dbg(&priv->spi->dev, "%#03x\n", buf[i]);

	fअगरo_buffer = kmemdup(buf, len, GFP_KERNEL);
	अगर (!fअगरo_buffer)
		वापस -ENOMEM;
	kfअगरo_in(&test->up_fअगरo, &fअगरo_buffer, 4);
	wake_up_पूर्णांकerruptible(&priv->test.पढ़ोq);

	वापस 0;
पूर्ण

/* SPI Operation */

अटल पूर्णांक ca8210_net_rx(
	काष्ठा ieee802154_hw  *hw,
	u8                    *command,
	माप_प्रकार                 len
);
अटल u8 mlme_reset_request_sync(
	u8       set_शेष_pib,
	व्योम    *device_ref
);
अटल पूर्णांक ca8210_spi_transfer(
	काष्ठा spi_device *spi,
	स्थिर u8          *buf,
	माप_प्रकार             len
);

/**
 * ca8210_reset_send() - Hard resets the ca8210 क्रम a given समय
 * @spi:  Poपूर्णांकer to target ca8210 spi device
 * @ms:   Milliseconds to hold the reset line low क्रम
 */
अटल व्योम ca8210_reset_send(काष्ठा spi_device *spi, अचिन्हित पूर्णांक ms)
अणु
	काष्ठा ca8210_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	काष्ठा ca8210_priv *priv = spi_get_drvdata(spi);
	दीर्घ status;

	gpio_set_value(pdata->gpio_reset, 0);
	reinit_completion(&priv->ca8210_is_awake);
	msleep(ms);
	gpio_set_value(pdata->gpio_reset, 1);
	priv->promiscuous = false;

	/* Wait until wakeup indication seen */
	status = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&priv->ca8210_is_awake,
		msecs_to_jअगरfies(CA8210_SYNC_TIMEOUT)
	);
	अगर (status == 0) अणु
		dev_crit(
			&spi->dev,
			"Fatal: No wakeup from ca8210 after reset!\n"
		);
	पूर्ण

	dev_dbg(&spi->dev, "Reset the device\n");
पूर्ण

/**
 * ca8210_mlme_reset_worker() - Resets the MLME, Called when the MAC OVERFLOW
 *                              condition happens.
 * @work:  Poपूर्णांकer to work being executed
 */
अटल व्योम ca8210_mlme_reset_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा work_priv_container *wpc = container_of(
		work,
		काष्ठा work_priv_container,
		work
	);
	काष्ठा ca8210_priv *priv = wpc->priv;

	mlme_reset_request_sync(0, priv->spi);
	kमुक्त(wpc);
पूर्ण

/**
 * ca8210_rx_करोne() - Calls various message dispatches responding to a received
 *                    command
 * @cas_ctl: Poपूर्णांकer to the cas_control object क्रम the relevant spi transfer
 *
 * Presents a received SAP command from the ca8210 to the Cascoda EVBME, test
 * पूर्णांकerface and network driver.
 */
अटल व्योम ca8210_rx_करोne(काष्ठा cas_control *cas_ctl)
अणु
	u8 *buf;
	अचिन्हित पूर्णांक len;
	काष्ठा work_priv_container *mlme_reset_wpc;
	काष्ठा ca8210_priv *priv = cas_ctl->priv;

	buf = cas_ctl->tx_in_buf;
	len = buf[1] + 2;
	अगर (len > CA8210_SPI_BUF_SIZE) अणु
		dev_crit(
			&priv->spi->dev,
			"Received packet len (%u) erroneously long\n",
			len
		);
		जाओ finish;
	पूर्ण

	अगर (buf[0] & SPI_SYN) अणु
		अगर (priv->sync_command_response) अणु
			स_नकल(priv->sync_command_response, buf, len);
			complete(&priv->sync_exchange_complete);
		पूर्ण अन्यथा अणु
			अगर (cascoda_api_upstream)
				cascoda_api_upstream(buf, len, priv->spi);
			priv->sync_up++;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cascoda_api_upstream)
			cascoda_api_upstream(buf, len, priv->spi);
	पूर्ण

	ca8210_net_rx(priv->hw, buf, len);
	अगर (buf[0] == SPI_MCPS_DATA_CONFIRM) अणु
		अगर (buf[3] == MAC_TRANSACTION_OVERFLOW) अणु
			dev_info(
				&priv->spi->dev,
				"Waiting for transaction overflow to stabilise...\n");
			msleep(2000);
			dev_info(
				&priv->spi->dev,
				"Resetting MAC...\n");

			mlme_reset_wpc = kदो_स्मृति(माप(*mlme_reset_wpc),
						 GFP_KERNEL);
			अगर (!mlme_reset_wpc)
				जाओ finish;
			INIT_WORK(
				&mlme_reset_wpc->work,
				ca8210_mlme_reset_worker
			);
			mlme_reset_wpc->priv = priv;
			queue_work(priv->mlme_workqueue, &mlme_reset_wpc->work);
		पूर्ण
	पूर्ण अन्यथा अगर (buf[0] == SPI_HWME_WAKEUP_INDICATION) अणु
		dev_notice(
			&priv->spi->dev,
			"Wakeup indication received, reason:\n"
		);
		चयन (buf[2]) अणु
		हाल 0:
			dev_notice(
				&priv->spi->dev,
				"Transceiver woken up from Power Up / System Reset\n"
			);
			अवरोध;
		हाल 1:
			dev_notice(
				&priv->spi->dev,
				"Watchdog Timer Time-Out\n"
			);
			अवरोध;
		हाल 2:
			dev_notice(
				&priv->spi->dev,
				"Transceiver woken up from Power-Off by Sleep Timer Time-Out\n");
			अवरोध;
		हाल 3:
			dev_notice(
				&priv->spi->dev,
				"Transceiver woken up from Power-Off by GPIO Activity\n"
			);
			अवरोध;
		हाल 4:
			dev_notice(
				&priv->spi->dev,
				"Transceiver woken up from Standby by Sleep Timer Time-Out\n"
			);
			अवरोध;
		हाल 5:
			dev_notice(
				&priv->spi->dev,
				"Transceiver woken up from Standby by GPIO Activity\n"
			);
			अवरोध;
		हाल 6:
			dev_notice(
				&priv->spi->dev,
				"Sleep-Timer Time-Out in Active Mode\n"
			);
			अवरोध;
		शेष:
			dev_warn(&priv->spi->dev, "Wakeup reason unknown\n");
			अवरोध;
		पूर्ण
		complete(&priv->ca8210_is_awake);
	पूर्ण

finish:;
पूर्ण

अटल पूर्णांक ca8210_हटाओ(काष्ठा spi_device *spi_device);

/**
 * ca8210_spi_transfer_complete() - Called when a single spi transfer has
 *                                  completed
 * @context:  Poपूर्णांकer to the cas_control object क्रम the finished transfer
 */
अटल व्योम ca8210_spi_transfer_complete(व्योम *context)
अणु
	काष्ठा cas_control *cas_ctl = context;
	काष्ठा ca8210_priv *priv = cas_ctl->priv;
	bool duplex_rx = false;
	पूर्णांक i;
	u8 retry_buffer[CA8210_SPI_BUF_SIZE];

	अगर (
		cas_ctl->tx_in_buf[0] == SPI_NACK ||
		(cas_ctl->tx_in_buf[0] == SPI_IDLE &&
		cas_ctl->tx_in_buf[1] == SPI_NACK)
	) अणु
		/* ca8210 is busy */
		dev_info(&priv->spi->dev, "ca8210 was busy during attempted write\n");
		अगर (cas_ctl->tx_buf[0] == SPI_IDLE) अणु
			dev_warn(
				&priv->spi->dev,
				"IRQ servicing NACKd, dropping transfer\n"
			);
			kमुक्त(cas_ctl);
			वापस;
		पूर्ण
		अगर (priv->retries > 3) अणु
			dev_err(&priv->spi->dev, "too many retries!\n");
			kमुक्त(cas_ctl);
			ca8210_हटाओ(priv->spi);
			वापस;
		पूर्ण
		स_नकल(retry_buffer, cas_ctl->tx_buf, CA8210_SPI_BUF_SIZE);
		kमुक्त(cas_ctl);
		ca8210_spi_transfer(
			priv->spi,
			retry_buffer,
			CA8210_SPI_BUF_SIZE
		);
		priv->retries++;
		dev_info(&priv->spi->dev, "retried spi write\n");
		वापस;
	पूर्ण अन्यथा अगर (
			cas_ctl->tx_in_buf[0] != SPI_IDLE &&
			cas_ctl->tx_in_buf[0] != SPI_NACK
		) अणु
		duplex_rx = true;
	पूर्ण

	अगर (duplex_rx) अणु
		dev_dbg(&priv->spi->dev, "READ CMD DURING TX\n");
		क्रम (i = 0; i < cas_ctl->tx_in_buf[1] + 2; i++)
			dev_dbg(
				&priv->spi->dev,
				"%#03x\n",
				cas_ctl->tx_in_buf[i]
			);
		ca8210_rx_करोne(cas_ctl);
	पूर्ण
	complete(&priv->spi_transfer_complete);
	kमुक्त(cas_ctl);
	priv->retries = 0;
पूर्ण

/**
 * ca8210_spi_transfer() - Initiate duplex spi transfer with ca8210
 * @spi: Poपूर्णांकer to spi device क्रम transfer
 * @buf: Octet array to send
 * @len: length of the buffer being sent
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_spi_transfer(
	काष्ठा spi_device  *spi,
	स्थिर u8           *buf,
	माप_प्रकार              len
)
अणु
	पूर्णांक i, status = 0;
	काष्ठा ca8210_priv *priv;
	काष्ठा cas_control *cas_ctl;

	अगर (!spi) अणु
		pr_crit("NULL spi device passed to %s\n", __func__);
		वापस -ENODEV;
	पूर्ण

	priv = spi_get_drvdata(spi);
	reinit_completion(&priv->spi_transfer_complete);

	dev_dbg(&spi->dev, "%s called\n", __func__);

	cas_ctl = kदो_स्मृति(माप(*cas_ctl), GFP_ATOMIC);
	अगर (!cas_ctl)
		वापस -ENOMEM;

	cas_ctl->priv = priv;
	स_रखो(cas_ctl->tx_buf, SPI_IDLE, CA8210_SPI_BUF_SIZE);
	स_रखो(cas_ctl->tx_in_buf, SPI_IDLE, CA8210_SPI_BUF_SIZE);
	स_नकल(cas_ctl->tx_buf, buf, len);

	क्रम (i = 0; i < len; i++)
		dev_dbg(&spi->dev, "%#03x\n", cas_ctl->tx_buf[i]);

	spi_message_init(&cas_ctl->msg);

	cas_ctl->transfer.tx_nbits = 1; /* 1 MOSI line */
	cas_ctl->transfer.rx_nbits = 1; /* 1 MISO line */
	cas_ctl->transfer.speed_hz = 0; /* Use device setting */
	cas_ctl->transfer.bits_per_word = 0; /* Use device setting */
	cas_ctl->transfer.tx_buf = cas_ctl->tx_buf;
	cas_ctl->transfer.rx_buf = cas_ctl->tx_in_buf;
	cas_ctl->transfer.delay.value = 0;
	cas_ctl->transfer.delay.unit = SPI_DELAY_UNIT_USECS;
	cas_ctl->transfer.cs_change = 0;
	cas_ctl->transfer.len = माप(काष्ठा mac_message);
	cas_ctl->msg.complete = ca8210_spi_transfer_complete;
	cas_ctl->msg.context = cas_ctl;

	spi_message_add_tail(
		&cas_ctl->transfer,
		&cas_ctl->msg
	);

	status = spi_async(spi, &cas_ctl->msg);
	अगर (status < 0) अणु
		dev_crit(
			&spi->dev,
			"status %d from spi_sync in write\n",
			status
		);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ca8210_spi_exchange() - Exchange API/SAP commands with the radio
 * @buf:         Octet array of command being sent करोwnstream
 * @len:         length of buf
 * @response:    buffer क्रम storing synchronous response
 * @device_ref:  spi_device poपूर्णांकer क्रम ca8210
 *
 * Effectively calls ca8210_spi_transfer to ग_लिखो buf[] to the spi, then क्रम
 * synchronous commands रुकोs क्रम the corresponding response to be पढ़ो from
 * the spi beक्रमe वापसing. The response is written to the response parameter.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_spi_exchange(
	स्थिर u8 *buf,
	माप_प्रकार len,
	u8 *response,
	व्योम *device_ref
)
अणु
	पूर्णांक status = 0;
	काष्ठा spi_device *spi = device_ref;
	काष्ठा ca8210_priv *priv = spi->dev.driver_data;
	दीर्घ रुको_reमुख्यing;

	अगर ((buf[0] & SPI_SYN) && response) अणु /* अगर sync रुको क्रम confirm */
		reinit_completion(&priv->sync_exchange_complete);
		priv->sync_command_response = response;
	पूर्ण

	करो अणु
		reinit_completion(&priv->spi_transfer_complete);
		status = ca8210_spi_transfer(priv->spi, buf, len);
		अगर (status) अणु
			dev_warn(
				&spi->dev,
				"spi write failed, returned %d\n",
				status
			);
			अगर (status == -EBUSY)
				जारी;
			अगर (((buf[0] & SPI_SYN) && response))
				complete(&priv->sync_exchange_complete);
			जाओ cleanup;
		पूर्ण

		रुको_reमुख्यing = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
			&priv->spi_transfer_complete,
			msecs_to_jअगरfies(1000)
		);
		अगर (रुको_reमुख्यing == -ERESTARTSYS) अणु
			status = -ERESTARTSYS;
		पूर्ण अन्यथा अगर (रुको_reमुख्यing == 0) अणु
			dev_err(
				&spi->dev,
				"SPI downstream transfer timed out!\n"
			);
			status = -ETIME;
			जाओ cleanup;
		पूर्ण
	पूर्ण जबतक (status < 0);

	अगर (!((buf[0] & SPI_SYN) && response))
		जाओ cleanup;

	रुको_reमुख्यing = रुको_क्रम_completion_पूर्णांकerruptible_समयout(
		&priv->sync_exchange_complete,
		msecs_to_jअगरfies(CA8210_SYNC_TIMEOUT)
	);
	अगर (रुको_reमुख्यing == -ERESTARTSYS) अणु
		status = -ERESTARTSYS;
	पूर्ण अन्यथा अगर (रुको_reमुख्यing == 0) अणु
		dev_err(
			&spi->dev,
			"Synchronous confirm timeout\n"
		);
		status = -ETIME;
	पूर्ण

cleanup:
	priv->sync_command_response = शून्य;
	वापस status;
पूर्ण

/**
 * ca8210_पूर्णांकerrupt_handler() - Called when an irq is received from the ca8210
 * @irq:     Id of the irq being handled
 * @dev_id:  Poपूर्णांकer passed by the प्रणाली, poपूर्णांकing to the ca8210's निजी data
 *
 * This function is called when the irq line from the ca8210 is निश्चितed,
 * signअगरying that the ca8210 has a message to send upstream to us. Starts the
 * asynchronous spi पढ़ो.
 *
 * Return: irq वापस code
 */
अटल irqवापस_t ca8210_पूर्णांकerrupt_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा ca8210_priv *priv = dev_id;
	पूर्णांक status;

	dev_dbg(&priv->spi->dev, "irq: Interrupt occurred\n");
	करो अणु
		status = ca8210_spi_transfer(priv->spi, शून्य, 0);
		अगर (status && (status != -EBUSY)) अणु
			dev_warn(
				&priv->spi->dev,
				"spi read failed, returned %d\n",
				status
			);
		पूर्ण
	पूर्ण जबतक (status == -EBUSY);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक (*cascoda_api_करोwnstream)(
	स्थिर u8 *buf,
	माप_प्रकार len,
	u8 *response,
	व्योम *device_ref
) = ca8210_spi_exchange;

/* Cascoda API / 15.4 SAP Primitives */

/**
 * tdme_setsfr_request_sync() - TDME_SETSFR_request/confirm according to API
 * @sfr_page:    SFR Page
 * @sfr_address: SFR Address
 * @sfr_value:   SFR Value
 * @device_ref:  Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of TDME-SETSFR.confirm
 */
अटल u8 tdme_setsfr_request_sync(
	u8            sfr_page,
	u8            sfr_address,
	u8            sfr_value,
	व्योम         *device_ref
)
अणु
	पूर्णांक ret;
	काष्ठा mac_message command, response;
	काष्ठा spi_device *spi = device_ref;

	command.command_id = SPI_TDME_SETSFR_REQUEST;
	command.length = 3;
	command.pdata.tdme_set_sfr_req.sfr_page    = sfr_page;
	command.pdata.tdme_set_sfr_req.sfr_address = sfr_address;
	command.pdata.tdme_set_sfr_req.sfr_value   = sfr_value;
	response.command_id = SPI_IDLE;
	ret = cascoda_api_करोwnstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref
	);
	अगर (ret) अणु
		dev_crit(&spi->dev, "cascoda_api_downstream returned %d", ret);
		वापस MAC_SYSTEM_ERROR;
	पूर्ण

	अगर (response.command_id != SPI_TDME_SETSFR_CONFIRM) अणु
		dev_crit(
			&spi->dev,
			"sync response to SPI_TDME_SETSFR_REQUEST was not SPI_TDME_SETSFR_CONFIRM, it was %d\n",
			response.command_id
		);
		वापस MAC_SYSTEM_ERROR;
	पूर्ण

	वापस response.pdata.tdme_set_sfr_cnf.status;
पूर्ण

/**
 * tdme_chipinit() - TDME Chip Register Default Initialisation Macro
 * @device_ref: Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of API calls
 */
अटल u8 tdme_chipinit(व्योम *device_ref)
अणु
	u8 status = MAC_SUCCESS;
	u8 sfr_address;
	काष्ठा spi_device *spi = device_ref;
	काष्ठा preamble_cfg_sfr pre_cfg_value = अणु
		.समयout_symbols     = 3,
		.acquisition_symbols = 3,
		.search_symbols      = 1,
	पूर्ण;
	/* LNA Gain Settings */
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX40),
		LNAGX40_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX41),
		LNAGX41_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX42),
		LNAGX42_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX43),
		LNAGX43_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX44),
		LNAGX44_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX45),
		LNAGX45_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX46),
		LNAGX46_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_LNAGX47),
		LNAGX47_DEFAULT_GAIN, device_ref);
	अगर (status)
		जाओ finish;
	/* Preamble Timing Config */
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_PRECFG),
		*((u8 *)&pre_cfg_value), device_ref);
	अगर (status)
		जाओ finish;
	/* Preamble Threshold High */
	status = tdme_setsfr_request_sync(
		1, (sfr_address = CA8210_SFR_PTHRH),
		PTHRH_DEFAULT_THRESHOLD, device_ref);
	अगर (status)
		जाओ finish;
	/* Tx Output Power 8 dBm */
	status = tdme_setsfr_request_sync(
		0, (sfr_address = CA8210_SFR_PACFGIB),
		PACFGIB_DEFAULT_CURRENT, device_ref);
	अगर (status)
		जाओ finish;

finish:
	अगर (status != MAC_SUCCESS) अणु
		dev_err(
			&spi->dev,
			"failed to set sfr at %#03x, status = %#03x\n",
			sfr_address,
			status
		);
	पूर्ण
	वापस status;
पूर्ण

/**
 * tdme_channelinit() - TDME Channel Register Default Initialisation Macro (Tx)
 * @channel:    802.15.4 channel to initialise chip क्रम
 * @device_ref: Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of API calls
 */
अटल u8 tdme_channelinit(u8 channel, व्योम *device_ref)
अणु
	/* Transceiver front-end local oscillator tx two-poपूर्णांक calibration
	 * value. Tuned क्रम the hardware.
	 */
	u8 txcalval;

	अगर (channel >= 25)
		txcalval = 0xA7;
	अन्यथा अगर (channel >= 23)
		txcalval = 0xA8;
	अन्यथा अगर (channel >= 22)
		txcalval = 0xA9;
	अन्यथा अगर (channel >= 20)
		txcalval = 0xAA;
	अन्यथा अगर (channel >= 17)
		txcalval = 0xAB;
	अन्यथा अगर (channel >= 16)
		txcalval = 0xAC;
	अन्यथा अगर (channel >= 14)
		txcalval = 0xAD;
	अन्यथा अगर (channel >= 12)
		txcalval = 0xAE;
	अन्यथा
		txcalval = 0xAF;

	वापस tdme_setsfr_request_sync(
		1,
		CA8210_SFR_LOTXCAL,
		txcalval,
		device_ref
	);  /* LO Tx Cal */
पूर्ण

/**
 * tdme_checkpibattribute() - Checks Attribute Values that are not checked in
 *                            MAC
 * @pib_attribute:        Attribute Number
 * @pib_attribute_length: Attribute length
 * @pib_attribute_value:  Poपूर्णांकer to Attribute Value
 *
 * Return: 802.15.4 status code of checks
 */
अटल u8 tdme_checkpibattribute(
	u8            pib_attribute,
	u8            pib_attribute_length,
	स्थिर व्योम   *pib_attribute_value
)
अणु
	u8 status = MAC_SUCCESS;
	u8 value;

	value  = *((u8 *)pib_attribute_value);

	चयन (pib_attribute) अणु
	/* PHY */
	हाल PHY_TRANSMIT_POWER:
		अगर (value > 0x3F)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल PHY_CCA_MODE:
		अगर (value > 0x03)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	/* MAC */
	हाल MAC_BATT_LIFE_EXT_PERIODS:
		अगर (value < 6 || value > 41)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_BEACON_PAYLOAD:
		अगर (pib_attribute_length > MAX_BEACON_PAYLOAD_LENGTH)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_BEACON_PAYLOAD_LENGTH:
		अगर (value > MAX_BEACON_PAYLOAD_LENGTH)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_BEACON_ORDER:
		अगर (value > 15)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_MAX_BE:
		अगर (value < 3 || value > 8)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_MAX_CSMA_BACKOFFS:
		अगर (value > 5)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_MAX_FRAME_RETRIES:
		अगर (value > 7)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_MIN_BE:
		अगर (value > 8)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_RESPONSE_WAIT_TIME:
		अगर (value < 2 || value > 64)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_SUPERFRAME_ORDER:
		अगर (value > 15)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	/* boolean */
	हाल MAC_ASSOCIATED_PAN_COORD:
	हाल MAC_ASSOCIATION_PERMIT:
	हाल MAC_AUTO_REQUEST:
	हाल MAC_BATT_LIFE_EXT:
	हाल MAC_GTS_PERMIT:
	हाल MAC_PROMISCUOUS_MODE:
	हाल MAC_RX_ON_WHEN_IDLE:
	हाल MAC_SECURITY_ENABLED:
		अगर (value > 1)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	/* MAC SEC */
	हाल MAC_AUTO_REQUEST_SECURITY_LEVEL:
		अगर (value > 7)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	हाल MAC_AUTO_REQUEST_KEY_ID_MODE:
		अगर (value > 3)
			status = MAC_INVALID_PARAMETER;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस status;
पूर्ण

/**
 * tdme_settxघातer() - Sets the tx घातer क्रम MLME_SET phyTransmitPower
 * @txp:        Transmit Power
 * @device_ref: Nondescript poपूर्णांकer to target device
 *
 * Normalised to 802.15.4 Definition (6-bit, चिन्हित):
 * Bit 7-6: not used
 * Bit 5-0: tx घातer (-32 - +31 dB)
 *
 * Return: 802.15.4 status code of api calls
 */
अटल u8 tdme_settxघातer(u8 txp, व्योम *device_ref)
अणु
	u8 status;
	s8 txp_val;
	u8 txp_ext;
	जोड़ pa_cfg_sfr pa_cfg_val;

	/* extend from 6 to 8 bit */
	txp_ext = 0x3F & txp;
	अगर (txp_ext & 0x20)
		txp_ext += 0xC0;
	txp_val = (s8)txp_ext;

	अगर (CA8210_MAC_MPW) अणु
		अगर (txp_val > 0) अणु
			/* 8 dBm: ptrim = 5, itrim = +3 => +4 dBm */
			pa_cfg_val.bias_current_trim     = 3;
			pa_cfg_val.buffer_capacitor_trim = 5;
			pa_cfg_val.boost                 = 1;
		पूर्ण अन्यथा अणु
			/* 0 dBm: ptrim = 7, itrim = +3 => -6 dBm */
			pa_cfg_val.bias_current_trim     = 3;
			pa_cfg_val.buffer_capacitor_trim = 7;
			pa_cfg_val.boost                 = 0;
		पूर्ण
		/* ग_लिखो PACFG */
		status = tdme_setsfr_request_sync(
			0,
			CA8210_SFR_PACFG,
			pa_cfg_val.paib,
			device_ref
		);
	पूर्ण अन्यथा अणु
		/* Look-Up Table क्रम Setting Current and Frequency Trim values
		 * क्रम desired Output Power
		 */
		अगर (txp_val > 8) अणु
			pa_cfg_val.paib = 0x3F;
		पूर्ण अन्यथा अगर (txp_val == 8) अणु
			pa_cfg_val.paib = 0x32;
		पूर्ण अन्यथा अगर (txp_val == 7) अणु
			pa_cfg_val.paib = 0x22;
		पूर्ण अन्यथा अगर (txp_val == 6) अणु
			pa_cfg_val.paib = 0x18;
		पूर्ण अन्यथा अगर (txp_val == 5) अणु
			pa_cfg_val.paib = 0x10;
		पूर्ण अन्यथा अगर (txp_val == 4) अणु
			pa_cfg_val.paib = 0x0C;
		पूर्ण अन्यथा अगर (txp_val == 3) अणु
			pa_cfg_val.paib = 0x08;
		पूर्ण अन्यथा अगर (txp_val == 2) अणु
			pa_cfg_val.paib = 0x05;
		पूर्ण अन्यथा अगर (txp_val == 1) अणु
			pa_cfg_val.paib = 0x03;
		पूर्ण अन्यथा अगर (txp_val == 0) अणु
			pa_cfg_val.paib = 0x01;
		पूर्ण अन्यथा अणु /* < 0 */
			pa_cfg_val.paib = 0x00;
		पूर्ण
		/* ग_लिखो PACFGIB */
		status = tdme_setsfr_request_sync(
			0,
			CA8210_SFR_PACFGIB,
			pa_cfg_val.paib,
			device_ref
		);
	पूर्ण

	वापस status;
पूर्ण

/**
 * mcps_data_request() - mcps_data_request (Send Data) according to API Spec
 * @src_addr_mode:    Source Addressing Mode
 * @dst_address_mode: Destination Addressing Mode
 * @dst_pan_id:       Destination PAN ID
 * @dst_addr:         Poपूर्णांकer to Destination Address
 * @msdu_length:      length of Data
 * @msdu:             Poपूर्णांकer to Data
 * @msdu_handle:      Handle of Data
 * @tx_options:       Tx Options Bit Field
 * @security:         Poपूर्णांकer to Security Structure or शून्य
 * @device_ref:       Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of action
 */
अटल u8 mcps_data_request(
	u8               src_addr_mode,
	u8               dst_address_mode,
	u16              dst_pan_id,
	जोड़ macaddr   *dst_addr,
	u8               msdu_length,
	u8              *msdu,
	u8               msdu_handle,
	u8               tx_options,
	काष्ठा secspec  *security,
	व्योम            *device_ref
)
अणु
	काष्ठा secspec *psec;
	काष्ठा mac_message command;

	command.command_id = SPI_MCPS_DATA_REQUEST;
	command.pdata.data_req.src_addr_mode = src_addr_mode;
	command.pdata.data_req.dst.mode = dst_address_mode;
	अगर (dst_address_mode != MAC_MODE_NO_ADDR) अणु
		command.pdata.data_req.dst.pan_id[0] = LS_BYTE(dst_pan_id);
		command.pdata.data_req.dst.pan_id[1] = MS_BYTE(dst_pan_id);
		अगर (dst_address_mode == MAC_MODE_SHORT_ADDR) अणु
			command.pdata.data_req.dst.address[0] = LS_BYTE(
				dst_addr->लघु_address
			);
			command.pdata.data_req.dst.address[1] = MS_BYTE(
				dst_addr->लघु_address
			);
		पूर्ण अन्यथा अणु   /* MAC_MODE_LONG_ADDR*/
			स_नकल(
				command.pdata.data_req.dst.address,
				dst_addr->ieee_address,
				8
			);
		पूर्ण
	पूर्ण
	command.pdata.data_req.msdu_length = msdu_length;
	command.pdata.data_req.msdu_handle = msdu_handle;
	command.pdata.data_req.tx_options = tx_options;
	स_नकल(command.pdata.data_req.msdu, msdu, msdu_length);
	psec = (काष्ठा secspec *)(command.pdata.data_req.msdu + msdu_length);
	command.length = माप(काष्ठा mcps_data_request_pset) -
		MAX_DATA_SIZE + msdu_length;
	अगर (!security || security->security_level == 0) अणु
		psec->security_level = 0;
		command.length += 1;
	पूर्ण अन्यथा अणु
		*psec = *security;
		command.length += माप(काष्ठा secspec);
	पूर्ण

	अगर (ca8210_spi_transfer(device_ref, &command.command_id,
				command.length + 2))
		वापस MAC_SYSTEM_ERROR;

	वापस MAC_SUCCESS;
पूर्ण

/**
 * mlme_reset_request_sync() - MLME_RESET_request/confirm according to API Spec
 * @set_शेष_pib: Set शेषs in PIB
 * @device_ref:      Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of MLME-RESET.confirm
 */
अटल u8 mlme_reset_request_sync(
	u8    set_शेष_pib,
	व्योम *device_ref
)
अणु
	u8 status;
	काष्ठा mac_message command, response;
	काष्ठा spi_device *spi = device_ref;

	command.command_id = SPI_MLME_RESET_REQUEST;
	command.length = 1;
	command.pdata.u8param = set_शेष_pib;

	अगर (cascoda_api_करोwnstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) अणु
		dev_err(&spi->dev, "cascoda_api_downstream failed\n");
		वापस MAC_SYSTEM_ERROR;
	पूर्ण

	अगर (response.command_id != SPI_MLME_RESET_CONFIRM)
		वापस MAC_SYSTEM_ERROR;

	status = response.pdata.status;

	/* reset COORD Bit क्रम Channel Filtering as Coordinator */
	अगर (CA8210_MAC_WORKAROUNDS && set_शेष_pib && !status) अणु
		status = tdme_setsfr_request_sync(
			0,
			CA8210_SFR_MACCON,
			0,
			device_ref
		);
	पूर्ण

	वापस status;
पूर्ण

/**
 * mlme_set_request_sync() - MLME_SET_request/confirm according to API Spec
 * @pib_attribute:        Attribute Number
 * @pib_attribute_index:  Index within Attribute अगर an Array
 * @pib_attribute_length: Attribute length
 * @pib_attribute_value:  Poपूर्णांकer to Attribute Value
 * @device_ref:           Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of MLME-SET.confirm
 */
अटल u8 mlme_set_request_sync(
	u8            pib_attribute,
	u8            pib_attribute_index,
	u8            pib_attribute_length,
	स्थिर व्योम   *pib_attribute_value,
	व्योम         *device_ref
)
अणु
	u8 status;
	काष्ठा mac_message command, response;

	/* pre-check the validity of pib_attribute values that are not checked
	 * in MAC
	 */
	अगर (tdme_checkpibattribute(
		pib_attribute, pib_attribute_length, pib_attribute_value)) अणु
		वापस MAC_INVALID_PARAMETER;
	पूर्ण

	अगर (pib_attribute == PHY_CURRENT_CHANNEL) अणु
		status = tdme_channelinit(
			*((u8 *)pib_attribute_value),
			device_ref
		);
		अगर (status)
			वापस status;
	पूर्ण

	अगर (pib_attribute == PHY_TRANSMIT_POWER) अणु
		वापस tdme_settxघातer(
			*((u8 *)pib_attribute_value),
			device_ref
		);
	पूर्ण

	command.command_id = SPI_MLME_SET_REQUEST;
	command.length = माप(काष्ठा mlme_set_request_pset) -
		MAX_ATTRIBUTE_SIZE + pib_attribute_length;
	command.pdata.set_req.pib_attribute = pib_attribute;
	command.pdata.set_req.pib_attribute_index = pib_attribute_index;
	command.pdata.set_req.pib_attribute_length = pib_attribute_length;
	स_नकल(
		command.pdata.set_req.pib_attribute_value,
		pib_attribute_value,
		pib_attribute_length
	);

	अगर (cascoda_api_करोwnstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) अणु
		वापस MAC_SYSTEM_ERROR;
	पूर्ण

	अगर (response.command_id != SPI_MLME_SET_CONFIRM)
		वापस MAC_SYSTEM_ERROR;

	वापस response.pdata.status;
पूर्ण

/**
 * hwme_set_request_sync() - HWME_SET_request/confirm according to API Spec
 * @hw_attribute:        Attribute Number
 * @hw_attribute_length: Attribute length
 * @hw_attribute_value:  Poपूर्णांकer to Attribute Value
 * @device_ref:          Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of HWME-SET.confirm
 */
अटल u8 hwme_set_request_sync(
	u8           hw_attribute,
	u8           hw_attribute_length,
	u8          *hw_attribute_value,
	व्योम        *device_ref
)
अणु
	काष्ठा mac_message command, response;

	command.command_id = SPI_HWME_SET_REQUEST;
	command.length = 2 + hw_attribute_length;
	command.pdata.hwme_set_req.hw_attribute = hw_attribute;
	command.pdata.hwme_set_req.hw_attribute_length = hw_attribute_length;
	स_नकल(
		command.pdata.hwme_set_req.hw_attribute_value,
		hw_attribute_value,
		hw_attribute_length
	);

	अगर (cascoda_api_करोwnstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) अणु
		वापस MAC_SYSTEM_ERROR;
	पूर्ण

	अगर (response.command_id != SPI_HWME_SET_CONFIRM)
		वापस MAC_SYSTEM_ERROR;

	वापस response.pdata.hwme_set_cnf.status;
पूर्ण

/**
 * hwme_get_request_sync() - HWME_GET_request/confirm according to API Spec
 * @hw_attribute:        Attribute Number
 * @hw_attribute_length: Attribute length
 * @hw_attribute_value:  Poपूर्णांकer to Attribute Value
 * @device_ref:          Nondescript poपूर्णांकer to target device
 *
 * Return: 802.15.4 status code of HWME-GET.confirm
 */
अटल u8 hwme_get_request_sync(
	u8           hw_attribute,
	u8          *hw_attribute_length,
	u8          *hw_attribute_value,
	व्योम        *device_ref
)
अणु
	काष्ठा mac_message command, response;

	command.command_id = SPI_HWME_GET_REQUEST;
	command.length = 1;
	command.pdata.hwme_get_req.hw_attribute = hw_attribute;

	अगर (cascoda_api_करोwnstream(
		&command.command_id,
		command.length + 2,
		&response.command_id,
		device_ref)) अणु
		वापस MAC_SYSTEM_ERROR;
	पूर्ण

	अगर (response.command_id != SPI_HWME_GET_CONFIRM)
		वापस MAC_SYSTEM_ERROR;

	अगर (response.pdata.hwme_get_cnf.status == MAC_SUCCESS) अणु
		*hw_attribute_length =
			response.pdata.hwme_get_cnf.hw_attribute_length;
		स_नकल(
			hw_attribute_value,
			response.pdata.hwme_get_cnf.hw_attribute_value,
			*hw_attribute_length
		);
	पूर्ण

	वापस response.pdata.hwme_get_cnf.status;
पूर्ण

/* Network driver operation */

/**
 * ca8210_async_xmit_complete() - Called to announce that an asynchronous
 *                                transmission has finished
 * @hw:          ieee802154_hw of ca8210 that has finished exchange
 * @msduhandle:  Identअगरier of transmission that has completed
 * @status:      Returned 802.15.4 status code of the transmission
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_async_xmit_complete(
	काष्ठा ieee802154_hw  *hw,
	u8                     msduhandle,
	u8                     status)
अणु
	काष्ठा ca8210_priv *priv = hw->priv;

	अगर (priv->nexपंचांगsduhandle != msduhandle) अणु
		dev_err(
			&priv->spi->dev,
			"Unexpected msdu_handle on data confirm, Expected %d, got %d\n",
			priv->nexपंचांगsduhandle,
			msduhandle
		);
		वापस -EIO;
	पूर्ण

	priv->async_tx_pending = false;
	priv->nexपंचांगsduhandle++;

	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"Link transmission unsuccessful, status = %d\n",
			status
		);
		अगर (status != MAC_TRANSACTION_OVERFLOW) अणु
			ieee802154_wake_queue(priv->hw);
			वापस 0;
		पूर्ण
	पूर्ण
	ieee802154_xmit_complete(priv->hw, priv->tx_skb, true);

	वापस 0;
पूर्ण

/**
 * ca8210_skb_rx() - Contructs a properly framed socket buffer from a received
 *                   MCPS_DATA_indication
 * @hw:        ieee802154_hw that MCPS_DATA_indication was received by
 * @len:       length of MCPS_DATA_indication
 * @data_ind:  Octet array of MCPS_DATA_indication
 *
 * Called by the spi driver whenever a SAP command is received, this function
 * will ascertain whether the command is of पूर्णांकerest to the network driver and
 * take necessary action.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_skb_rx(
	काष्ठा ieee802154_hw  *hw,
	माप_प्रकार                 len,
	u8                    *data_ind
)
अणु
	काष्ठा ieee802154_hdr hdr;
	पूर्णांक msdulen;
	पूर्णांक hlen;
	u8 mpdulinkquality = data_ind[23];
	काष्ठा sk_buff *skb;
	काष्ठा ca8210_priv *priv = hw->priv;

	/* Allocate mtu size buffer क्रम every rx packet */
	skb = dev_alloc_skb(IEEE802154_MTU + माप(hdr));
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, माप(hdr));

	msdulen = data_ind[22]; /* msdu_length */
	अगर (msdulen > IEEE802154_MTU) अणु
		dev_err(
			&priv->spi->dev,
			"received erroneously large msdu length!\n"
		);
		kमुक्त_skb(skb);
		वापस -EMSGSIZE;
	पूर्ण
	dev_dbg(&priv->spi->dev, "skb buffer length = %d\n", msdulen);

	अगर (priv->promiscuous)
		जाओ copy_payload;

	/* Populate hdr */
	hdr.sec.level = data_ind[29 + msdulen];
	dev_dbg(&priv->spi->dev, "security level: %#03x\n", hdr.sec.level);
	अगर (hdr.sec.level > 0) अणु
		hdr.sec.key_id_mode = data_ind[30 + msdulen];
		स_नकल(&hdr.sec.extended_src, &data_ind[31 + msdulen], 8);
		hdr.sec.key_id = data_ind[39 + msdulen];
	पूर्ण
	hdr.source.mode = data_ind[0];
	dev_dbg(&priv->spi->dev, "srcAddrMode: %#03x\n", hdr.source.mode);
	hdr.source.pan_id = *(u16 *)&data_ind[1];
	dev_dbg(&priv->spi->dev, "srcPanId: %#06x\n", hdr.source.pan_id);
	स_नकल(&hdr.source.extended_addr, &data_ind[3], 8);
	hdr.dest.mode = data_ind[11];
	dev_dbg(&priv->spi->dev, "dstAddrMode: %#03x\n", hdr.dest.mode);
	hdr.dest.pan_id = *(u16 *)&data_ind[12];
	dev_dbg(&priv->spi->dev, "dstPanId: %#06x\n", hdr.dest.pan_id);
	स_नकल(&hdr.dest.extended_addr, &data_ind[14], 8);

	/* Fill in FC implicitly */
	hdr.fc.type = 1; /* Data frame */
	अगर (hdr.sec.level)
		hdr.fc.security_enabled = 1;
	अन्यथा
		hdr.fc.security_enabled = 0;
	अगर (data_ind[1] != data_ind[12] || data_ind[2] != data_ind[13])
		hdr.fc.पूर्णांकra_pan = 1;
	अन्यथा
		hdr.fc.पूर्णांकra_pan = 0;
	hdr.fc.dest_addr_mode = hdr.dest.mode;
	hdr.fc.source_addr_mode = hdr.source.mode;

	/* Add hdr to front of buffer */
	hlen = ieee802154_hdr_push(skb, &hdr);

	अगर (hlen < 0) अणु
		dev_crit(&priv->spi->dev, "failed to push mac hdr onto skb!\n");
		kमुक्त_skb(skb);
		वापस hlen;
	पूर्ण

	skb_reset_mac_header(skb);
	skb->mac_len = hlen;

copy_payload:
	/* Add <msdulen> bytes of space to the back of the buffer */
	/* Copy msdu to skb */
	skb_put_data(skb, &data_ind[29], msdulen);

	ieee802154_rx_irqsafe(hw, skb, mpdulinkquality);
	वापस 0;
पूर्ण

/**
 * ca8210_net_rx() - Acts upon received SAP commands relevant to the network
 *                   driver
 * @hw:       ieee802154_hw that command was received by
 * @command:  Octet array of received command
 * @len:      length of the received command
 *
 * Called by the spi driver whenever a SAP command is received, this function
 * will ascertain whether the command is of पूर्णांकerest to the network driver and
 * take necessary action.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_net_rx(काष्ठा ieee802154_hw *hw, u8 *command, माप_प्रकार len)
अणु
	काष्ठा ca8210_priv *priv = hw->priv;
	अचिन्हित दीर्घ flags;
	u8 status;

	dev_dbg(&priv->spi->dev, "%s: CmdID = %d\n", __func__, command[0]);

	अगर (command[0] == SPI_MCPS_DATA_INDICATION) अणु
		/* Received data */
		spin_lock_irqsave(&priv->lock, flags);
		अगर (command[26] == priv->last_dsn) अणु
			dev_dbg(
				&priv->spi->dev,
				"DSN %d resend received, ignoring...\n",
				command[26]
			);
			spin_unlock_irqrestore(&priv->lock, flags);
			वापस 0;
		पूर्ण
		priv->last_dsn = command[26];
		spin_unlock_irqrestore(&priv->lock, flags);
		वापस ca8210_skb_rx(hw, len - 2, command + 2);
	पूर्ण अन्यथा अगर (command[0] == SPI_MCPS_DATA_CONFIRM) अणु
		status = command[3];
		अगर (priv->async_tx_pending) अणु
			वापस ca8210_async_xmit_complete(
				hw,
				command[2],
				status
			);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ca8210_skb_tx() - Transmits a given socket buffer using the ca8210
 * @skb:         Socket buffer to transmit
 * @msduhandle:  Data identअगरier to pass to the 802.15.4 MAC
 * @priv:        Poपूर्णांकer to निजी data section of target ca8210
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_skb_tx(
	काष्ठा sk_buff      *skb,
	u8                   msduhandle,
	काष्ठा ca8210_priv  *priv
)
अणु
	पूर्णांक status;
	काष्ठा ieee802154_hdr header = अणु पूर्ण;
	काष्ठा secspec secspec;
	अचिन्हित पूर्णांक mac_len;

	dev_dbg(&priv->spi->dev, "%s called\n", __func__);

	/* Get addressing info from skb - ieee802154 layer creates a full
	 * packet
	 */
	mac_len = ieee802154_hdr_peek_addrs(skb, &header);

	secspec.security_level = header.sec.level;
	secspec.key_id_mode = header.sec.key_id_mode;
	अगर (secspec.key_id_mode == 2)
		स_नकल(secspec.key_source, &header.sec.लघु_src, 4);
	अन्यथा अगर (secspec.key_id_mode == 3)
		स_नकल(secspec.key_source, &header.sec.extended_src, 8);
	secspec.key_index = header.sec.key_id;

	/* Pass to Cascoda API */
	status =  mcps_data_request(
		header.source.mode,
		header.dest.mode,
		header.dest.pan_id,
		(जोड़ macaddr *)&header.dest.extended_addr,
		skb->len - mac_len,
		&skb->data[mac_len],
		msduhandle,
		header.fc.ack_request,
		&secspec,
		priv->spi
	);
	वापस link_to_linux_err(status);
पूर्ण

/**
 * ca8210_start() - Starts the network driver
 * @hw:  ieee802154_hw of ca8210 being started
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_start(काष्ठा ieee802154_hw *hw)
अणु
	पूर्णांक status;
	u8 rx_on_when_idle;
	u8 lqi_threshold = 0;
	काष्ठा ca8210_priv *priv = hw->priv;

	priv->last_dsn = -1;
	/* Turn receiver on when idle क्रम now just to test rx */
	rx_on_when_idle = 1;
	status = mlme_set_request_sync(
		MAC_RX_ON_WHEN_IDLE,
		0,
		1,
		&rx_on_when_idle,
		priv->spi
	);
	अगर (status) अणु
		dev_crit(
			&priv->spi->dev,
			"Setting rx_on_when_idle failed, status = %d\n",
			status
		);
		वापस link_to_linux_err(status);
	पूर्ण
	status = hwme_set_request_sync(
		HWME_LQILIMIT,
		1,
		&lqi_threshold,
		priv->spi
	);
	अगर (status) अणु
		dev_crit(
			&priv->spi->dev,
			"Setting lqilimit failed, status = %d\n",
			status
		);
		वापस link_to_linux_err(status);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ca8210_stop() - Stops the network driver
 * @hw:  ieee802154_hw of ca8210 being stopped
 *
 * Return: 0 or linux error code
 */
अटल व्योम ca8210_stop(काष्ठा ieee802154_hw *hw)
अणु
पूर्ण

/**
 * ca8210_xmit_async() - Asynchronously transmits a given socket buffer using
 *                       the ca8210
 * @hw:   ieee802154_hw of ca8210 to transmit from
 * @skb:  Socket buffer to transmit
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_xmit_async(काष्ठा ieee802154_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा ca8210_priv *priv = hw->priv;
	पूर्णांक status;

	dev_dbg(&priv->spi->dev, "calling %s\n", __func__);

	priv->tx_skb = skb;
	priv->async_tx_pending = true;
	status = ca8210_skb_tx(skb, priv->nexपंचांगsduhandle, priv);
	वापस status;
पूर्ण

/**
 * ca8210_get_ed() - Returns the measured energy on the current channel at this
 *                   instant in समय
 * @hw:     ieee802154_hw of target ca8210
 * @level:  Measured Energy Detect level
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_get_ed(काष्ठा ieee802154_hw *hw, u8 *level)
अणु
	u8 lenvar;
	काष्ठा ca8210_priv *priv = hw->priv;

	वापस link_to_linux_err(
		hwme_get_request_sync(HWME_EDVALUE, &lenvar, level, priv->spi)
	);
पूर्ण

/**
 * ca8210_set_channel() - Sets the current operating 802.15.4 channel of the
 *                        ca8210
 * @hw:       ieee802154_hw of target ca8210
 * @page:     Channel page to set
 * @channel:  Channel number to set
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_channel(
	काष्ठा ieee802154_hw  *hw,
	u8                     page,
	u8                     channel
)
अणु
	u8 status;
	काष्ठा ca8210_priv *priv = hw->priv;

	status = mlme_set_request_sync(
		PHY_CURRENT_CHANNEL,
		0,
		1,
		&channel,
		priv->spi
	);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting channel, MLME-SET.confirm status = %d\n",
			status
		);
	पूर्ण
	वापस link_to_linux_err(status);
पूर्ण

/**
 * ca8210_set_hw_addr_filt() - Sets the address filtering parameters of the
 *                             ca8210
 * @hw:       ieee802154_hw of target ca8210
 * @filt:     Filtering parameters
 * @changed:  Biपंचांगap representing which parameters to change
 *
 * Effectively just sets the actual addressing inक्रमmation identअगरying this node
 * as all filtering is perक्रमmed by the ca8210 as detailed in the IEEE 802.15.4
 * 2006 specअगरication.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_hw_addr_filt(
	काष्ठा ieee802154_hw            *hw,
	काष्ठा ieee802154_hw_addr_filt  *filt,
	अचिन्हित दीर्घ                    changed
)
अणु
	u8 status = 0;
	काष्ठा ca8210_priv *priv = hw->priv;

	अगर (changed & IEEE802154_AFILT_PANID_CHANGED) अणु
		status = mlme_set_request_sync(
			MAC_PAN_ID,
			0,
			2,
			&filt->pan_id, priv->spi
		);
		अगर (status) अणु
			dev_err(
				&priv->spi->dev,
				"error setting pan id, MLME-SET.confirm status = %d",
				status
			);
			वापस link_to_linux_err(status);
		पूर्ण
	पूर्ण
	अगर (changed & IEEE802154_AFILT_SADDR_CHANGED) अणु
		status = mlme_set_request_sync(
			MAC_SHORT_ADDRESS,
			0,
			2,
			&filt->लघु_addr, priv->spi
		);
		अगर (status) अणु
			dev_err(
				&priv->spi->dev,
				"error setting short address, MLME-SET.confirm status = %d",
				status
			);
			वापस link_to_linux_err(status);
		पूर्ण
	पूर्ण
	अगर (changed & IEEE802154_AFILT_IEEEADDR_CHANGED) अणु
		status = mlme_set_request_sync(
			NS_IEEE_ADDRESS,
			0,
			8,
			&filt->ieee_addr,
			priv->spi
		);
		अगर (status) अणु
			dev_err(
				&priv->spi->dev,
				"error setting ieee address, MLME-SET.confirm status = %d",
				status
			);
			वापस link_to_linux_err(status);
		पूर्ण
	पूर्ण
	/* TODO: Should use MLME_START to set coord bit? */
	वापस 0;
पूर्ण

/**
 * ca8210_set_tx_घातer() - Sets the transmit घातer of the ca8210
 * @hw:   ieee802154_hw of target ca8210
 * @mbm:  Transmit घातer in mBm (dBm*100)
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_tx_घातer(काष्ठा ieee802154_hw *hw, s32 mbm)
अणु
	काष्ठा ca8210_priv *priv = hw->priv;

	mbm /= 100;
	वापस link_to_linux_err(
		mlme_set_request_sync(PHY_TRANSMIT_POWER, 0, 1, &mbm, priv->spi)
	);
पूर्ण

/**
 * ca8210_set_cca_mode() - Sets the clear channel assessment mode of the ca8210
 * @hw:   ieee802154_hw of target ca8210
 * @cca:  CCA mode to set
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_cca_mode(
	काष्ठा ieee802154_hw       *hw,
	स्थिर काष्ठा wpan_phy_cca  *cca
)
अणु
	u8 status;
	u8 cca_mode;
	काष्ठा ca8210_priv *priv = hw->priv;

	cca_mode = cca->mode & 3;
	अगर (cca_mode == 3 && cca->opt == NL802154_CCA_OPT_ENERGY_CARRIER_OR) अणु
		/* cca_mode 0 == CS OR ED, 3 == CS AND ED */
		cca_mode = 0;
	पूर्ण
	status = mlme_set_request_sync(
		PHY_CCA_MODE,
		0,
		1,
		&cca_mode,
		priv->spi
	);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting cca mode, MLME-SET.confirm status = %d",
			status
		);
	पूर्ण
	वापस link_to_linux_err(status);
पूर्ण

/**
 * ca8210_set_cca_ed_level() - Sets the CCA ED level of the ca8210
 * @hw:     ieee802154_hw of target ca8210
 * @level:  ED level to set (in mbm)
 *
 * Sets the minimum threshold of measured energy above which the ca8210 will
 * back off and retry a transmission.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_cca_ed_level(काष्ठा ieee802154_hw *hw, s32 level)
अणु
	u8 status;
	u8 ed_threshold = (level / 100) * 2 + 256;
	काष्ठा ca8210_priv *priv = hw->priv;

	status = hwme_set_request_sync(
		HWME_EDTHRESHOLD,
		1,
		&ed_threshold,
		priv->spi
	);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting ed threshold, HWME-SET.confirm status = %d",
			status
		);
	पूर्ण
	वापस link_to_linux_err(status);
पूर्ण

/**
 * ca8210_set_csma_params() - Sets the CSMA parameters of the ca8210
 * @hw:       ieee802154_hw of target ca8210
 * @min_be:   Minimum backoff exponent when backing off a transmission
 * @max_be:   Maximum backoff exponent when backing off a transmission
 * @retries:  Number of बार to retry after backing off
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_csma_params(
	काष्ठा ieee802154_hw  *hw,
	u8                     min_be,
	u8                     max_be,
	u8                     retries
)
अणु
	u8 status;
	काष्ठा ca8210_priv *priv = hw->priv;

	status = mlme_set_request_sync(MAC_MIN_BE, 0, 1, &min_be, priv->spi);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting min be, MLME-SET.confirm status = %d",
			status
		);
		वापस link_to_linux_err(status);
	पूर्ण
	status = mlme_set_request_sync(MAC_MAX_BE, 0, 1, &max_be, priv->spi);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting max be, MLME-SET.confirm status = %d",
			status
		);
		वापस link_to_linux_err(status);
	पूर्ण
	status = mlme_set_request_sync(
		MAC_MAX_CSMA_BACKOFFS,
		0,
		1,
		&retries,
		priv->spi
	);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting max csma backoffs, MLME-SET.confirm status = %d",
			status
		);
	पूर्ण
	वापस link_to_linux_err(status);
पूर्ण

/**
 * ca8210_set_frame_retries() - Sets the maximum frame retries of the ca8210
 * @hw:       ieee802154_hw of target ca8210
 * @retries:  Number of retries
 *
 * Sets the number of बार to retry a transmission अगर no acknowledgment was
 * was received from the other end when one was requested.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_set_frame_retries(काष्ठा ieee802154_hw *hw, s8 retries)
अणु
	u8 status;
	काष्ठा ca8210_priv *priv = hw->priv;

	status = mlme_set_request_sync(
		MAC_MAX_FRAME_RETRIES,
		0,
		1,
		&retries,
		priv->spi
	);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting frame retries, MLME-SET.confirm status = %d",
			status
		);
	पूर्ण
	वापस link_to_linux_err(status);
पूर्ण

अटल पूर्णांक ca8210_set_promiscuous_mode(काष्ठा ieee802154_hw *hw, स्थिर bool on)
अणु
	u8 status;
	काष्ठा ca8210_priv *priv = hw->priv;

	status = mlme_set_request_sync(
		MAC_PROMISCUOUS_MODE,
		0,
		1,
		(स्थिर व्योम *)&on,
		priv->spi
	);
	अगर (status) अणु
		dev_err(
			&priv->spi->dev,
			"error setting promiscuous mode, MLME-SET.confirm status = %d",
			status
		);
	पूर्ण अन्यथा अणु
		priv->promiscuous = on;
	पूर्ण
	वापस link_to_linux_err(status);
पूर्ण

अटल स्थिर काष्ठा ieee802154_ops ca8210_phy_ops = अणु
	.start = ca8210_start,
	.stop = ca8210_stop,
	.xmit_async = ca8210_xmit_async,
	.ed = ca8210_get_ed,
	.set_channel = ca8210_set_channel,
	.set_hw_addr_filt = ca8210_set_hw_addr_filt,
	.set_txघातer = ca8210_set_tx_घातer,
	.set_cca_mode = ca8210_set_cca_mode,
	.set_cca_ed_level = ca8210_set_cca_ed_level,
	.set_csma_params = ca8210_set_csma_params,
	.set_frame_retries = ca8210_set_frame_retries,
	.set_promiscuous_mode = ca8210_set_promiscuous_mode
पूर्ण;

/* Test/EVBME Interface */

/**
 * ca8210_test_पूर्णांक_खोलो() - Opens the test पूर्णांकerface to the userspace
 * @inodp:  inode representation of file पूर्णांकerface
 * @filp:   file पूर्णांकerface
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_test_पूर्णांक_खोलो(काष्ठा inode *inodp, काष्ठा file *filp)
अणु
	काष्ठा ca8210_priv *priv = inodp->i_निजी;

	filp->निजी_data = priv;
	वापस 0;
पूर्ण

/**
 * ca8210_test_check_upstream() - Checks a command received from the upstream
 *                                testing पूर्णांकerface क्रम required action
 * @buf:        Buffer containing command to check
 * @device_ref: Nondescript poपूर्णांकer to target device
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_test_check_upstream(u8 *buf, व्योम *device_ref)
अणु
	पूर्णांक ret;
	u8 response[CA8210_SPI_BUF_SIZE];

	अगर (buf[0] == SPI_MLME_SET_REQUEST) अणु
		ret = tdme_checkpibattribute(buf[2], buf[4], buf + 5);
		अगर (ret) अणु
			response[0]  = SPI_MLME_SET_CONFIRM;
			response[1] = 3;
			response[2] = MAC_INVALID_PARAMETER;
			response[3] = buf[2];
			response[4] = buf[3];
			अगर (cascoda_api_upstream)
				cascoda_api_upstream(response, 5, device_ref);
			वापस ret;
		पूर्ण
	पूर्ण
	अगर (buf[0] == SPI_MLME_ASSOCIATE_REQUEST) अणु
		वापस tdme_channelinit(buf[2], device_ref);
	पूर्ण अन्यथा अगर (buf[0] == SPI_MLME_START_REQUEST) अणु
		वापस tdme_channelinit(buf[4], device_ref);
	पूर्ण अन्यथा अगर (
		(buf[0] == SPI_MLME_SET_REQUEST) &&
		(buf[2] == PHY_CURRENT_CHANNEL)
	) अणु
		वापस tdme_channelinit(buf[5], device_ref);
	पूर्ण अन्यथा अगर (
		(buf[0] == SPI_TDME_SET_REQUEST) &&
		(buf[2] == TDME_CHANNEL)
	) अणु
		वापस tdme_channelinit(buf[4], device_ref);
	पूर्ण अन्यथा अगर (
		(CA8210_MAC_WORKAROUNDS) &&
		(buf[0] == SPI_MLME_RESET_REQUEST) &&
		(buf[2] == 1)
	) अणु
		/* reset COORD Bit क्रम Channel Filtering as Coordinator */
		वापस tdme_setsfr_request_sync(
			0,
			CA8210_SFR_MACCON,
			0,
			device_ref
		);
	पूर्ण
	वापस 0;
पूर्ण /* End of EVBMECheckSerialCommand() */

/**
 * ca8210_test_पूर्णांक_user_ग_लिखो() - Called by a process in userspace to send a
 *                                message to the ca8210 drivers
 * @filp:    file पूर्णांकerface
 * @in_buf:  Buffer containing message to ग_लिखो
 * @len:     length of message
 * @off:     file offset
 *
 * Return: 0 or linux error code
 */
अटल sमाप_प्रकार ca8210_test_पूर्णांक_user_ग_लिखो(
	काष्ठा file        *filp,
	स्थिर अक्षर __user  *in_buf,
	माप_प्रकार              len,
	loff_t             *off
)
अणु
	पूर्णांक ret;
	काष्ठा ca8210_priv *priv = filp->निजी_data;
	u8 command[CA8210_SPI_BUF_SIZE];

	स_रखो(command, SPI_IDLE, 6);
	अगर (len > CA8210_SPI_BUF_SIZE || len < 2) अणु
		dev_warn(
			&priv->spi->dev,
			"userspace requested erroneous write length (%zu)\n",
			len
		);
		वापस -EBADE;
	पूर्ण

	ret = copy_from_user(command, in_buf, len);
	अगर (ret) अणु
		dev_err(
			&priv->spi->dev,
			"%d bytes could not be copied from userspace\n",
			ret
		);
		वापस -EIO;
	पूर्ण
	अगर (len != command[1] + 2) अणु
		dev_err(
			&priv->spi->dev,
			"write len does not match packet length field\n"
		);
		वापस -EBADE;
	पूर्ण

	ret = ca8210_test_check_upstream(command, priv->spi);
	अगर (ret == 0) अणु
		ret = ca8210_spi_exchange(
			command,
			command[1] + 2,
			शून्य,
			priv->spi
		);
		अगर (ret < 0) अणु
			/* effectively 0 bytes were written successfully */
			dev_err(
				&priv->spi->dev,
				"spi exchange failed\n"
			);
			वापस ret;
		पूर्ण
		अगर (command[0] & SPI_SYN)
			priv->sync_करोwn++;
	पूर्ण

	वापस len;
पूर्ण

/**
 * ca8210_test_पूर्णांक_user_पढ़ो() - Called by a process in userspace to पढ़ो a
 *                               message from the ca8210 drivers
 * @filp:  file पूर्णांकerface
 * @buf:   Buffer to ग_लिखो message to
 * @len:   length of message to पढ़ो (ignored)
 * @offp:  file offset
 *
 * If the O_NONBLOCK flag was set when खोलोing the file then this function will
 * not block, i.e. it will वापस अगर the fअगरo is empty. Otherwise the function
 * will block, i.e. रुको until new data arrives.
 *
 * Return: number of bytes पढ़ो
 */
अटल sमाप_प्रकार ca8210_test_पूर्णांक_user_पढ़ो(
	काष्ठा file  *filp,
	अक्षर __user  *buf,
	माप_प्रकार        len,
	loff_t       *offp
)
अणु
	पूर्णांक i, cmdlen;
	काष्ठा ca8210_priv *priv = filp->निजी_data;
	अचिन्हित अक्षर *fअगरo_buffer;
	अचिन्हित दीर्घ bytes_not_copied;

	अगर (filp->f_flags & O_NONBLOCK) अणु
		/* Non-blocking mode */
		अगर (kfअगरo_is_empty(&priv->test.up_fअगरo))
			वापस 0;
	पूर्ण अन्यथा अणु
		/* Blocking mode */
		रुको_event_पूर्णांकerruptible(
			priv->test.पढ़ोq,
			!kfअगरo_is_empty(&priv->test.up_fअगरo)
		);
	पूर्ण

	अगर (kfअगरo_out(&priv->test.up_fअगरo, &fअगरo_buffer, 4) != 4) अणु
		dev_err(
			&priv->spi->dev,
			"test_interface: Wrong number of elements popped from upstream fifo\n"
		);
		वापस 0;
	पूर्ण
	cmdlen = fअगरo_buffer[1];
	bytes_not_copied = cmdlen + 2;

	bytes_not_copied = copy_to_user(buf, fअगरo_buffer, bytes_not_copied);
	अगर (bytes_not_copied > 0) अणु
		dev_err(
			&priv->spi->dev,
			"%lu bytes could not be copied to user space!\n",
			bytes_not_copied
		);
	पूर्ण

	dev_dbg(&priv->spi->dev, "test_interface: Cmd len = %d\n", cmdlen);

	dev_dbg(&priv->spi->dev, "test_interface: Read\n");
	क्रम (i = 0; i < cmdlen + 2; i++)
		dev_dbg(&priv->spi->dev, "%#03x\n", fअगरo_buffer[i]);

	kमुक्त(fअगरo_buffer);

	वापस cmdlen + 2;
पूर्ण

/**
 * ca8210_test_पूर्णांक_ioctl() - Called by a process in userspace to enact an
 *                           arbitrary action
 * @filp:        file पूर्णांकerface
 * @ioctl_num:   which action to enact
 * @ioctl_param: arbitrary parameter क्रम the action
 *
 * Return: status
 */
अटल दीर्घ ca8210_test_पूर्णांक_ioctl(
	काष्ठा file *filp,
	अचिन्हित पूर्णांक ioctl_num,
	अचिन्हित दीर्घ ioctl_param
)
अणु
	काष्ठा ca8210_priv *priv = filp->निजी_data;

	चयन (ioctl_num) अणु
	हाल CA8210_IOCTL_HARD_RESET:
		ca8210_reset_send(priv->spi, ioctl_param);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ca8210_test_पूर्णांक_poll() - Called by a process in userspace to determine which
 *                          actions are currently possible क्रम the file
 * @filp:   file पूर्णांकerface
 * @ptable: poll table
 *
 * Return: set of poll वापस flags
 */
अटल __poll_t ca8210_test_पूर्णांक_poll(
	काष्ठा file *filp,
	काष्ठा poll_table_काष्ठा *ptable
)
अणु
	__poll_t वापस_flags = 0;
	काष्ठा ca8210_priv *priv = filp->निजी_data;

	poll_रुको(filp, &priv->test.पढ़ोq, ptable);
	अगर (!kfअगरo_is_empty(&priv->test.up_fअगरo))
		वापस_flags |= (EPOLLIN | EPOLLRDNORM);
	अगर (रुको_event_पूर्णांकerruptible(
		priv->test.पढ़ोq,
		!kfअगरo_is_empty(&priv->test.up_fअगरo))) अणु
		वापस EPOLLERR;
	पूर्ण
	वापस वापस_flags;
पूर्ण

अटल स्थिर काष्ठा file_operations test_पूर्णांक_fops = अणु
	.पढ़ो =           ca8210_test_पूर्णांक_user_पढ़ो,
	.ग_लिखो =          ca8210_test_पूर्णांक_user_ग_लिखो,
	.खोलो =           ca8210_test_पूर्णांक_खोलो,
	.release =        शून्य,
	.unlocked_ioctl = ca8210_test_पूर्णांक_ioctl,
	.poll =           ca8210_test_पूर्णांक_poll
पूर्ण;

/* Init/Deinit */

/**
 * ca8210_get_platक्रमm_data() - Populate a ca8210_platक्रमm_data object
 * @spi_device:  Poपूर्णांकer to ca8210 spi device object to get data क्रम
 * @pdata:       Poपूर्णांकer to ca8210_platक्रमm_data object to populate
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_get_platक्रमm_data(
	काष्ठा spi_device *spi_device,
	काष्ठा ca8210_platक्रमm_data *pdata
)
अणु
	पूर्णांक ret = 0;

	अगर (!spi_device->dev.of_node)
		वापस -EINVAL;

	pdata->extघड़ीenable = of_property_पढ़ो_bool(
		spi_device->dev.of_node,
		"extclock-enable"
	);
	अगर (pdata->extघड़ीenable) अणु
		ret = of_property_पढ़ो_u32(
			spi_device->dev.of_node,
			"extclock-freq",
			&pdata->extघड़ीfreq
		);
		अगर (ret < 0)
			वापस ret;

		ret = of_property_पढ़ो_u32(
			spi_device->dev.of_node,
			"extclock-gpio",
			&pdata->extघड़ीgpio
		);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ca8210_config_बाह्य_clk() - Configure the बाह्यal घड़ी provided by the
 *                              ca8210
 * @pdata:  Poपूर्णांकer to ca8210_platक्रमm_data containing घड़ी parameters
 * @spi:    Poपूर्णांकer to target ca8210 spi device
 * @on:	    True to turn the घड़ी on, false to turn off
 *
 * The बाह्यal घड़ी is configured with a frequency and output pin taken from
 * the platक्रमm data.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_config_बाह्य_clk(
	काष्ठा ca8210_platक्रमm_data *pdata,
	काष्ठा spi_device *spi,
	bool on
)
अणु
	u8 clkparam[2];

	अगर (on) अणु
		dev_info(&spi->dev, "Switching external clock on\n");
		चयन (pdata->extघड़ीfreq) अणु
		हाल SIXTEEN_MHZ:
			clkparam[0] = 1;
			अवरोध;
		हाल EIGHT_MHZ:
			clkparam[0] = 2;
			अवरोध;
		हाल FOUR_MHZ:
			clkparam[0] = 3;
			अवरोध;
		हाल TWO_MHZ:
			clkparam[0] = 4;
			अवरोध;
		हाल ONE_MHZ:
			clkparam[0] = 5;
			अवरोध;
		शेष:
			dev_crit(&spi->dev, "Invalid extclock-freq\n");
			वापस -EINVAL;
		पूर्ण
		clkparam[1] = pdata->extघड़ीgpio;
	पूर्ण अन्यथा अणु
		dev_info(&spi->dev, "Switching external clock off\n");
		clkparam[0] = 0; /* off */
		clkparam[1] = 0;
	पूर्ण
	वापस link_to_linux_err(
		hwme_set_request_sync(HWME_SYSCLKOUT, 2, clkparam, spi)
	);
पूर्ण

/**
 * ca8210_रेजिस्टर_ext_घड़ी() - Register ca8210's बाह्यal घड़ी with kernel
 * @spi:  Poपूर्णांकer to target ca8210 spi device
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_रेजिस्टर_ext_घड़ी(काष्ठा spi_device *spi)
अणु
	काष्ठा device_node *np = spi->dev.of_node;
	काष्ठा ca8210_priv *priv = spi_get_drvdata(spi);
	काष्ठा ca8210_platक्रमm_data *pdata = spi->dev.platक्रमm_data;
	पूर्णांक ret = 0;

	अगर (!np)
		वापस -EFAULT;

	priv->clk = clk_रेजिस्टर_fixed_rate(
		&spi->dev,
		np->name,
		शून्य,
		0,
		pdata->extघड़ीfreq
	);

	अगर (IS_ERR(priv->clk)) अणु
		dev_crit(&spi->dev, "Failed to register external clk\n");
		वापस PTR_ERR(priv->clk);
	पूर्ण
	ret = of_clk_add_provider(np, of_clk_src_simple_get, priv->clk);
	अगर (ret) अणु
		clk_unरेजिस्टर(priv->clk);
		dev_crit(
			&spi->dev,
			"Failed to register external clock as clock provider\n"
		);
	पूर्ण अन्यथा अणु
		dev_info(&spi->dev, "External clock set as clock provider\n");
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ca8210_unरेजिस्टर_ext_घड़ी() - Unरेजिस्टर ca8210's बाह्यal घड़ी with
 *                                 kernel
 * @spi:  Poपूर्णांकer to target ca8210 spi device
 */
अटल व्योम ca8210_unरेजिस्टर_ext_घड़ी(काष्ठा spi_device *spi)
अणु
	काष्ठा ca8210_priv *priv = spi_get_drvdata(spi);

	अगर (!priv->clk)
		वापस

	of_clk_del_provider(spi->dev.of_node);
	clk_unरेजिस्टर(priv->clk);
	dev_info(&spi->dev, "External clock unregistered\n");
पूर्ण

/**
 * ca8210_reset_init() - Initialise the reset input to the ca8210
 * @spi:  Poपूर्णांकer to target ca8210 spi device
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_reset_init(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा ca8210_platक्रमm_data *pdata = spi->dev.platक्रमm_data;

	pdata->gpio_reset = of_get_named_gpio(
		spi->dev.of_node,
		"reset-gpio",
		0
	);

	ret = gpio_direction_output(pdata->gpio_reset, 1);
	अगर (ret < 0) अणु
		dev_crit(
			&spi->dev,
			"Reset GPIO %d did not set to output mode\n",
			pdata->gpio_reset
		);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ca8210_पूर्णांकerrupt_init() - Initialise the irq output from the ca8210
 * @spi:  Poपूर्णांकer to target ca8210 spi device
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_पूर्णांकerrupt_init(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret;
	काष्ठा ca8210_platक्रमm_data *pdata = spi->dev.platक्रमm_data;

	pdata->gpio_irq = of_get_named_gpio(
		spi->dev.of_node,
		"irq-gpio",
		0
	);

	pdata->irq_id = gpio_to_irq(pdata->gpio_irq);
	अगर (pdata->irq_id < 0) अणु
		dev_crit(
			&spi->dev,
			"Could not get irq for gpio pin %d\n",
			pdata->gpio_irq
		);
		gpio_मुक्त(pdata->gpio_irq);
		वापस pdata->irq_id;
	पूर्ण

	ret = request_irq(
		pdata->irq_id,
		ca8210_पूर्णांकerrupt_handler,
		IRQF_TRIGGER_FALLING,
		"ca8210-irq",
		spi_get_drvdata(spi)
	);
	अगर (ret) अणु
		dev_crit(&spi->dev, "request_irq %d failed\n", pdata->irq_id);
		gpio_unexport(pdata->gpio_irq);
		gpio_मुक्त(pdata->gpio_irq);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ca8210_dev_com_init() - Initialise the spi communication component
 * @priv:  Poपूर्णांकer to निजी data काष्ठाure
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_dev_com_init(काष्ठा ca8210_priv *priv)
अणु
	priv->mlme_workqueue = alloc_ordered_workqueue(
		"MLME work queue",
		WQ_UNBOUND
	);
	अगर (!priv->mlme_workqueue) अणु
		dev_crit(&priv->spi->dev, "alloc of mlme_workqueue failed!\n");
		वापस -ENOMEM;
	पूर्ण

	priv->irq_workqueue = alloc_ordered_workqueue(
		"ca8210 irq worker",
		WQ_UNBOUND
	);
	अगर (!priv->irq_workqueue) अणु
		dev_crit(&priv->spi->dev, "alloc of irq_workqueue failed!\n");
		destroy_workqueue(priv->mlme_workqueue);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ca8210_dev_com_clear() - Deinitialise the spi communication component
 * @priv:  Poपूर्णांकer to निजी data काष्ठाure
 */
अटल व्योम ca8210_dev_com_clear(काष्ठा ca8210_priv *priv)
अणु
	flush_workqueue(priv->mlme_workqueue);
	destroy_workqueue(priv->mlme_workqueue);
	flush_workqueue(priv->irq_workqueue);
	destroy_workqueue(priv->irq_workqueue);
पूर्ण

#घोषणा CA8210_MAX_TX_POWERS (9)
अटल स्थिर s32 ca8210_tx_घातers[CA8210_MAX_TX_POWERS] = अणु
	800, 700, 600, 500, 400, 300, 200, 100, 0
पूर्ण;

#घोषणा CA8210_MAX_ED_LEVELS (21)
अटल स्थिर s32 ca8210_ed_levels[CA8210_MAX_ED_LEVELS] = अणु
	-10300, -10250, -10200, -10150, -10100, -10050, -10000, -9950, -9900,
	-9850, -9800, -9750, -9700, -9650, -9600, -9550, -9500, -9450, -9400,
	-9350, -9300
पूर्ण;

/**
 * ca8210_hw_setup() - Populate the ieee802154_hw phy attributes with the
 *                     ca8210's शेषs
 * @ca8210_hw:  Poपूर्णांकer to ieee802154_hw to populate
 */
अटल व्योम ca8210_hw_setup(काष्ठा ieee802154_hw *ca8210_hw)
अणु
	/* Support channels 11-26 */
	ca8210_hw->phy->supported.channels[0] = CA8210_VALID_CHANNELS;
	ca8210_hw->phy->supported.tx_घातers_size = CA8210_MAX_TX_POWERS;
	ca8210_hw->phy->supported.tx_घातers = ca8210_tx_घातers;
	ca8210_hw->phy->supported.cca_ed_levels_size = CA8210_MAX_ED_LEVELS;
	ca8210_hw->phy->supported.cca_ed_levels = ca8210_ed_levels;
	ca8210_hw->phy->current_channel = 18;
	ca8210_hw->phy->current_page = 0;
	ca8210_hw->phy->transmit_घातer = 800;
	ca8210_hw->phy->cca.mode = NL802154_CCA_ENERGY_CARRIER;
	ca8210_hw->phy->cca.opt = NL802154_CCA_OPT_ENERGY_CARRIER_AND;
	ca8210_hw->phy->cca_ed_level = -9800;
	ca8210_hw->phy->symbol_duration = 16;
	ca8210_hw->phy->lअगरs_period = 40;
	ca8210_hw->phy->sअगरs_period = 12;
	ca8210_hw->flags =
		IEEE802154_HW_AFILT |
		IEEE802154_HW_OMIT_CKSUM |
		IEEE802154_HW_FRAME_RETRIES |
		IEEE802154_HW_PROMISCUOUS |
		IEEE802154_HW_CSMA_PARAMS;
	ca8210_hw->phy->flags =
		WPAN_PHY_FLAG_TXPOWER |
		WPAN_PHY_FLAG_CCA_ED_LEVEL |
		WPAN_PHY_FLAG_CCA_MODE;
पूर्ण

/**
 * ca8210_test_पूर्णांकerface_init() - Initialise the test file पूर्णांकerface
 * @priv:  Poपूर्णांकer to निजी data काष्ठाure
 *
 * Provided as an alternative to the standard linux network पूर्णांकerface, the test
 * पूर्णांकerface exposes a file in the fileप्रणाली (ca8210_test) that allows
 * 802.15.4 SAP Commands and Cascoda EVBME commands to be sent directly to
 * the stack.
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_test_पूर्णांकerface_init(काष्ठा ca8210_priv *priv)
अणु
	काष्ठा ca8210_test *test = &priv->test;
	अक्षर node_name[32];

	snम_लिखो(
		node_name,
		माप(node_name),
		"ca8210@%d_%d",
		priv->spi->master->bus_num,
		priv->spi->chip_select
	);

	test->ca8210_dfs_spi_पूर्णांक = debugfs_create_file(
		node_name,
		0600, /* S_IRUSR | S_IWUSR */
		शून्य,
		priv,
		&test_पूर्णांक_fops
	);

	debugfs_create_symlink("ca8210", शून्य, node_name);
	init_रुकोqueue_head(&test->पढ़ोq);
	वापस kfअगरo_alloc(
		&test->up_fअगरo,
		CA8210_TEST_INT_FIFO_SIZE,
		GFP_KERNEL
	);
पूर्ण

/**
 * ca8210_test_पूर्णांकerface_clear() - Deinitialise the test file पूर्णांकerface
 * @priv:  Poपूर्णांकer to निजी data काष्ठाure
 */
अटल व्योम ca8210_test_पूर्णांकerface_clear(काष्ठा ca8210_priv *priv)
अणु
	काष्ठा ca8210_test *test = &priv->test;

	debugfs_हटाओ(test->ca8210_dfs_spi_पूर्णांक);
	kfअगरo_मुक्त(&test->up_fअगरo);
	dev_info(&priv->spi->dev, "Test interface removed\n");
पूर्ण

/**
 * ca8210_हटाओ() - Shut करोwn a ca8210 upon being disconnected
 * @spi_device:  Poपूर्णांकer to spi device data काष्ठाure
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_हटाओ(काष्ठा spi_device *spi_device)
अणु
	काष्ठा ca8210_priv *priv;
	काष्ठा ca8210_platक्रमm_data *pdata;

	dev_info(&spi_device->dev, "Removing ca8210\n");

	pdata = spi_device->dev.platक्रमm_data;
	अगर (pdata) अणु
		अगर (pdata->extघड़ीenable) अणु
			ca8210_unरेजिस्टर_ext_घड़ी(spi_device);
			ca8210_config_बाह्य_clk(pdata, spi_device, 0);
		पूर्ण
		मुक्त_irq(pdata->irq_id, spi_device->dev.driver_data);
		kमुक्त(pdata);
		spi_device->dev.platक्रमm_data = शून्य;
	पूर्ण
	/* get spi_device निजी data */
	priv = spi_get_drvdata(spi_device);
	अगर (priv) अणु
		dev_info(
			&spi_device->dev,
			"sync_down = %d, sync_up = %d\n",
			priv->sync_करोwn,
			priv->sync_up
		);
		ca8210_dev_com_clear(spi_device->dev.driver_data);
		अगर (priv->hw) अणु
			अगर (priv->hw_रेजिस्टरed)
				ieee802154_unरेजिस्टर_hw(priv->hw);
			ieee802154_मुक्त_hw(priv->hw);
			priv->hw = शून्य;
			dev_info(
				&spi_device->dev,
				"Unregistered & freed ieee802154_hw.\n"
			);
		पूर्ण
		अगर (IS_ENABLED(CONFIG_IEEE802154_CA8210_DEBUGFS))
			ca8210_test_पूर्णांकerface_clear(priv);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ca8210_probe() - Set up a connected ca8210 upon being detected by the प्रणाली
 * @spi_device:  Poपूर्णांकer to spi device data काष्ठाure
 *
 * Return: 0 or linux error code
 */
अटल पूर्णांक ca8210_probe(काष्ठा spi_device *spi_device)
अणु
	काष्ठा ca8210_priv *priv;
	काष्ठा ieee802154_hw *hw;
	काष्ठा ca8210_platक्रमm_data *pdata;
	पूर्णांक ret;

	dev_info(&spi_device->dev, "Inserting ca8210\n");

	/* allocate ieee802154_hw and निजी data */
	hw = ieee802154_alloc_hw(माप(काष्ठा ca8210_priv), &ca8210_phy_ops);
	अगर (!hw) अणु
		dev_crit(&spi_device->dev, "ieee802154_alloc_hw failed\n");
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	priv = hw->priv;
	priv->hw = hw;
	priv->spi = spi_device;
	hw->parent = &spi_device->dev;
	spin_lock_init(&priv->lock);
	priv->async_tx_pending = false;
	priv->hw_रेजिस्टरed = false;
	priv->sync_up = 0;
	priv->sync_करोwn = 0;
	priv->promiscuous = false;
	priv->retries = 0;
	init_completion(&priv->ca8210_is_awake);
	init_completion(&priv->spi_transfer_complete);
	init_completion(&priv->sync_exchange_complete);
	spi_set_drvdata(priv->spi, priv);
	अगर (IS_ENABLED(CONFIG_IEEE802154_CA8210_DEBUGFS)) अणु
		cascoda_api_upstream = ca8210_test_पूर्णांक_driver_ग_लिखो;
		ca8210_test_पूर्णांकerface_init(priv);
	पूर्ण अन्यथा अणु
		cascoda_api_upstream = शून्य;
	पूर्ण
	ca8210_hw_setup(hw);
	ieee802154_अक्रमom_extended_addr(&hw->phy->perm_extended_addr);

	pdata = kदो_स्मृति(माप(*pdata), GFP_KERNEL);
	अगर (!pdata) अणु
		ret = -ENOMEM;
		जाओ error;
	पूर्ण

	priv->spi->dev.platक्रमm_data = pdata;
	ret = ca8210_get_platक्रमm_data(priv->spi, pdata);
	अगर (ret) अणु
		dev_crit(&spi_device->dev, "ca8210_get_platform_data failed\n");
		जाओ error;
	पूर्ण

	ret = ca8210_dev_com_init(priv);
	अगर (ret) अणु
		dev_crit(&spi_device->dev, "ca8210_dev_com_init failed\n");
		जाओ error;
	पूर्ण
	ret = ca8210_reset_init(priv->spi);
	अगर (ret) अणु
		dev_crit(&spi_device->dev, "ca8210_reset_init failed\n");
		जाओ error;
	पूर्ण

	ret = ca8210_पूर्णांकerrupt_init(priv->spi);
	अगर (ret) अणु
		dev_crit(&spi_device->dev, "ca8210_interrupt_init failed\n");
		जाओ error;
	पूर्ण

	msleep(100);

	ca8210_reset_send(priv->spi, 1);

	ret = tdme_chipinit(priv->spi);
	अगर (ret) अणु
		dev_crit(&spi_device->dev, "tdme_chipinit failed\n");
		जाओ error;
	पूर्ण

	अगर (pdata->extघड़ीenable) अणु
		ret = ca8210_config_बाह्य_clk(pdata, priv->spi, 1);
		अगर (ret) अणु
			dev_crit(
				&spi_device->dev,
				"ca8210_config_extern_clk failed\n"
			);
			जाओ error;
		पूर्ण
		ret = ca8210_रेजिस्टर_ext_घड़ी(priv->spi);
		अगर (ret) अणु
			dev_crit(
				&spi_device->dev,
				"ca8210_register_ext_clock failed\n"
			);
			जाओ error;
		पूर्ण
	पूर्ण

	ret = ieee802154_रेजिस्टर_hw(hw);
	अगर (ret) अणु
		dev_crit(&spi_device->dev, "ieee802154_register_hw failed\n");
		जाओ error;
	पूर्ण
	priv->hw_रेजिस्टरed = true;

	वापस 0;
error:
	msleep(100); /* रुको क्रम pending spi transfers to complete */
	ca8210_हटाओ(spi_device);
	वापस link_to_linux_err(ret);
पूर्ण

अटल स्थिर काष्ठा of_device_id ca8210_of_ids[] = अणु
	अणु.compatible = "cascoda,ca8210", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ca8210_of_ids);

अटल काष्ठा spi_driver ca8210_spi_driver = अणु
	.driver = अणु
		.name =                 DRIVER_NAME,
		.owner =                THIS_MODULE,
		.of_match_table =       of_match_ptr(ca8210_of_ids),
	पूर्ण,
	.probe  =                       ca8210_probe,
	.हटाओ =                       ca8210_हटाओ
पूर्ण;

module_spi_driver(ca8210_spi_driver);

MODULE_AUTHOR("Harry Morris <h.morris@cascoda.com>");
MODULE_DESCRIPTION("CA-8210 SoftMAC driver");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION("1.0");
