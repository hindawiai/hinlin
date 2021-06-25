<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
 * Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#अगर_अघोषित _GVE_REGISTER_H_
#घोषणा _GVE_REGISTER_H_

/* Fixed Configuration Registers */
काष्ठा gve_रेजिस्टरs अणु
	__be32	device_status;
	__be32	driver_status;
	__be32	max_tx_queues;
	__be32	max_rx_queues;
	__be32	adminq_pfn;
	__be32	adminq_करोorbell;
	__be32	adminq_event_counter;
	u8	reserved[3];
	u8	driver_version;
पूर्ण;

क्रमागत gve_device_status_flags अणु
	GVE_DEVICE_STATUS_RESET_MASK		= BIT(1),
	GVE_DEVICE_STATUS_LINK_STATUS_MASK	= BIT(2),
	GVE_DEVICE_STATUS_REPORT_STATS_MASK	= BIT(3),
पूर्ण;
#पूर्ण_अगर /* _GVE_REGISTER_H_ */
