<शैली गुरु>
/* SPDX-License-Identअगरier: ISC */
/*
 * Copyright (c) 2014,2017 Qualcomm Atheros, Inc.
 */

/* "API" level of the ath10k tesपंचांगode पूर्णांकerface. Bump it after every
 * incompatible पूर्णांकerface change.
 */
#घोषणा ATH10K_TESTMODE_VERSION_MAJOR 1

/* Bump this after every _compatible_ पूर्णांकerface change, क्रम example
 * addition of a new command or an attribute.
 */
#घोषणा ATH10K_TESTMODE_VERSION_MINOR 0

#घोषणा ATH10K_TM_DATA_MAX_LEN		5000

क्रमागत ath10k_पंचांग_attr अणु
	__ATH10K_TM_ATTR_INVALID	= 0,
	ATH10K_TM_ATTR_CMD		= 1,
	ATH10K_TM_ATTR_DATA		= 2,
	ATH10K_TM_ATTR_WMI_CMDID	= 3,
	ATH10K_TM_ATTR_VERSION_MAJOR	= 4,
	ATH10K_TM_ATTR_VERSION_MINOR	= 5,
	ATH10K_TM_ATTR_WMI_OP_VERSION	= 6,

	/* keep last */
	__ATH10K_TM_ATTR_AFTER_LAST,
	ATH10K_TM_ATTR_MAX		= __ATH10K_TM_ATTR_AFTER_LAST - 1,
पूर्ण;

/* All ath10k tesपंचांगode पूर्णांकerface commands specअगरied in
 * ATH10K_TM_ATTR_CMD
 */
क्रमागत ath10k_पंचांग_cmd अणु
	/* Returns the supported ath10k tesपंचांगode पूर्णांकerface version in
	 * ATH10K_TM_ATTR_VERSION. Always guaranteed to work. User space
	 * uses this to verअगरy it's using the correct version of the
	 * tesपंचांगode पूर्णांकerface
	 */
	ATH10K_TM_CMD_GET_VERSION = 0,

	/* Boots the UTF firmware, the netdev पूर्णांकerface must be करोwn at the
	 * समय.
	 */
	ATH10K_TM_CMD_UTF_START = 1,

	/* Shuts करोwn the UTF firmware and माला_दो the driver back पूर्णांकo OFF
	 * state.
	 */
	ATH10K_TM_CMD_UTF_STOP = 2,

	/* The command used to transmit a WMI command to the firmware and
	 * the event to receive WMI events from the firmware. Without
	 * काष्ठा wmi_cmd_hdr header, only the WMI payload. Command id is
	 * provided with ATH10K_TM_ATTR_WMI_CMDID and payload in
	 * ATH10K_TM_ATTR_DATA.
	 */
	ATH10K_TM_CMD_WMI = 3,
पूर्ण;
