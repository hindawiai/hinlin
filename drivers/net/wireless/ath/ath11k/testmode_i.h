<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause-Clear */
/*
 * Copyright (c) 2018-2019 The Linux Foundation. All rights reserved.
 */

/* "API" level of the ath11k tesपंचांगode पूर्णांकerface. Bump it after every
 * incompatible पूर्णांकerface change.
 */
#घोषणा ATH11K_TESTMODE_VERSION_MAJOR 1

/* Bump this after every _compatible_ पूर्णांकerface change, क्रम example
 * addition of a new command or an attribute.
 */
#घोषणा ATH11K_TESTMODE_VERSION_MINOR 0

#घोषणा ATH11K_TM_DATA_MAX_LEN		5000

क्रमागत ath11k_पंचांग_attr अणु
	__ATH11K_TM_ATTR_INVALID		= 0,
	ATH11K_TM_ATTR_CMD			= 1,
	ATH11K_TM_ATTR_DATA			= 2,
	ATH11K_TM_ATTR_WMI_CMDID		= 3,
	ATH11K_TM_ATTR_VERSION_MAJOR		= 4,
	ATH11K_TM_ATTR_VERSION_MINOR		= 5,
	ATH11K_TM_ATTR_WMI_OP_VERSION		= 6,

	/* keep last */
	__ATH11K_TM_ATTR_AFTER_LAST,
	ATH11K_TM_ATTR_MAX		= __ATH11K_TM_ATTR_AFTER_LAST - 1,
पूर्ण;

/* All ath11k tesपंचांगode पूर्णांकerface commands specअगरied in
 * ATH11K_TM_ATTR_CMD
 */
क्रमागत ath11k_पंचांग_cmd अणु
	/* Returns the supported ath11k tesपंचांगode पूर्णांकerface version in
	 * ATH11K_TM_ATTR_VERSION. Always guaranteed to work. User space
	 * uses this to verअगरy it's using the correct version of the
	 * tesपंचांगode पूर्णांकerface
	 */
	ATH11K_TM_CMD_GET_VERSION = 0,

	/* The command used to transmit a WMI command to the firmware and
	 * the event to receive WMI events from the firmware. Without
	 * काष्ठा wmi_cmd_hdr header, only the WMI payload. Command id is
	 * provided with ATH11K_TM_ATTR_WMI_CMDID and payload in
	 * ATH11K_TM_ATTR_DATA.
	 */
	ATH11K_TM_CMD_WMI = 1,
पूर्ण;
