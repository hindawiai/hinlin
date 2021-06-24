<शैली गुरु>
/*
 *   Copyright (c) 2011, 2012, Qualcomm Atheros Communications Inc.
 *   Copyright (c) 2014, I2SE GmbH
 *
 *   Permission to use, copy, modअगरy, and/or distribute this software
 *   क्रम any purpose with or without fee is hereby granted, provided
 *   that the above copyright notice and this permission notice appear
 *   in all copies.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 *   WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 *   WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
 *   THE AUTHOR BE LIABLE FOR ANY SPECIAL, सूचीECT, INसूचीECT, OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 *   LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 *   NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 *   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*   Qualcomm Atheros SPI रेजिस्टर definition.
 *
 *   This module is deचिन्हित to define the Qualcomm Atheros SPI रेजिस्टर
 *   placeholders;
 */

#अगर_अघोषित _QCA_SPI_H
#घोषणा _QCA_SPI_H

#समावेश <linux/netdevice.h>
#समावेश <linux/sched.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/types.h>

#समावेश "qca_7k_common.h"

#घोषणा QCASPI_DRV_VERSION "0.2.7-i"
#घोषणा QCASPI_DRV_NAME    "qcaspi"

#घोषणा QCASPI_GOOD_SIGNATURE 0xAA55

#घोषणा TX_RING_MAX_LEN 10
#घोषणा TX_RING_MIN_LEN 2

/* sync related स्थिरants */
#घोषणा QCASPI_SYNC_UNKNOWN 0
#घोषणा QCASPI_SYNC_RESET   1
#घोषणा QCASPI_SYNC_READY   2

#घोषणा QCASPI_RESET_TIMEOUT 10

/* sync events */
#घोषणा QCASPI_EVENT_UPDATE 0
#घोषणा QCASPI_EVENT_CPUON  1

काष्ठा tx_ring अणु
	काष्ठा sk_buff *skb[TX_RING_MAX_LEN];
	u16 head;
	u16 tail;
	u16 size;
	u16 count;
पूर्ण;

काष्ठा qcaspi_stats अणु
	u64 trig_reset;
	u64 device_reset;
	u64 reset_समयout;
	u64 पढ़ो_err;
	u64 ग_लिखो_err;
	u64 पढ़ो_buf_err;
	u64 ग_लिखो_buf_err;
	u64 out_of_mem;
	u64 ग_लिखो_buf_miss;
	u64 ring_full;
	u64 spi_err;
	u64 ग_लिखो_verअगरy_failed;
	u64 buf_avail_err;
पूर्ण;

काष्ठा qcaspi अणु
	काष्ठा net_device *net_dev;
	काष्ठा spi_device *spi_dev;
	काष्ठा task_काष्ठा *spi_thपढ़ो;

	काष्ठा tx_ring txr;
	काष्ठा qcaspi_stats stats;

	u8 *rx_buffer;
	u32 buffer_size;
	u8 sync;

	काष्ठा qcafrm_handle frm_handle;
	काष्ठा sk_buff *rx_skb;

	अचिन्हित पूर्णांक पूर्णांकr_req;
	अचिन्हित पूर्णांक पूर्णांकr_svc;
	u16 reset_count;

#अगर_घोषित CONFIG_DEBUG_FS
	काष्ठा dentry *device_root;
#पूर्ण_अगर

	/* user configurable options */
	u32 clkspeed;
	u8 legacy_mode;
	u16 burst_len;
पूर्ण;

#पूर्ण_अगर /* _QCA_SPI_H */
