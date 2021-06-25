<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* Copyright (C) 2018 Microchip Technology Inc. */

#अगर_अघोषित _LAN743X_PTP_H
#घोषणा _LAN743X_PTP_H

#समावेश "linux/ptp_clock_kernel.h"
#समावेश "linux/netdevice.h"

#घोषणा LAN7430_N_LED			4
#घोषणा LAN7430_N_GPIO			4	/* multiplexed with PHY LEDs */
#घोषणा LAN7431_N_GPIO			12

#घोषणा LAN743X_PTP_N_GPIO		LAN7431_N_GPIO

/* the number of periodic outमाला_दो is limited by number of
 * PTP घड़ी event channels
 */
#घोषणा LAN743X_PTP_N_EVENT_CHAN	2
#घोषणा LAN743X_PTP_N_PEROUT		LAN743X_PTP_N_EVENT_CHAN

काष्ठा lan743x_adapter;

/* GPIO */
काष्ठा lan743x_gpio अणु
	/* gpio_lock: used to prevent concurrent access to gpio settings */
	spinlock_t gpio_lock;

	पूर्णांक used_bits;
	पूर्णांक output_bits;
	पूर्णांक ptp_bits;
	u32 gpio_cfg0;
	u32 gpio_cfg1;
	u32 gpio_cfg2;
	u32 gpio_cfg3;
पूर्ण;

पूर्णांक lan743x_gpio_init(काष्ठा lan743x_adapter *adapter);

व्योम lan743x_ptp_isr(व्योम *context);
bool lan743x_ptp_request_tx_बारtamp(काष्ठा lan743x_adapter *adapter);
व्योम lan743x_ptp_unrequest_tx_बारtamp(काष्ठा lan743x_adapter *adapter);
व्योम lan743x_ptp_tx_बारtamp_skb(काष्ठा lan743x_adapter *adapter,
				  काष्ठा sk_buff *skb, bool ignore_sync);
पूर्णांक lan743x_ptp_init(काष्ठा lan743x_adapter *adapter);
पूर्णांक lan743x_ptp_खोलो(काष्ठा lan743x_adapter *adapter);
व्योम lan743x_ptp_बंद(काष्ठा lan743x_adapter *adapter);
व्योम lan743x_ptp_update_latency(काष्ठा lan743x_adapter *adapter,
				u32 link_speed);

पूर्णांक lan743x_ptp_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd);

#घोषणा LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS (4)

#घोषणा PTP_FLAG_PTP_CLOCK_REGISTERED		BIT(1)
#घोषणा PTP_FLAG_ISR_ENABLED			BIT(2)

काष्ठा lan743x_ptp_perout अणु
	पूर्णांक  event_ch;	/* PTP event channel (0=channel A, 1=channel B) */
	पूर्णांक  gpio_pin;	/* GPIO pin where output appears */
पूर्ण;

काष्ठा lan743x_ptp अणु
	पूर्णांक flags;

	/* command_lock: used to prevent concurrent ptp commands */
	काष्ठा mutex	command_lock;

	काष्ठा ptp_घड़ी *ptp_घड़ी;
	काष्ठा ptp_घड़ी_info ptp_घड़ी_info;
	काष्ठा ptp_pin_desc pin_config[LAN743X_PTP_N_GPIO];

	अचिन्हित दीर्घ used_event_ch;
	काष्ठा lan743x_ptp_perout perout[LAN743X_PTP_N_PEROUT];

	bool leds_multiplexed;
	bool led_enabled[LAN7430_N_LED];

	/* tx_ts_lock: used to prevent concurrent access to बारtamp arrays */
	spinlock_t	tx_ts_lock;
	पूर्णांक pending_tx_बारtamps;
	काष्ठा sk_buff *tx_ts_skb_queue[LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS];
	अचिन्हित पूर्णांक	tx_ts_ignore_sync_queue;
	पूर्णांक tx_ts_skb_queue_size;
	u32 tx_ts_seconds_queue[LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS];
	u32 tx_ts_nseconds_queue[LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS];
	u32 tx_ts_header_queue[LAN743X_PTP_NUMBER_OF_TX_TIMESTAMPS];
	पूर्णांक tx_ts_queue_size;
पूर्ण;

#पूर्ण_अगर /* _LAN743X_PTP_H */
