<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2009 Nokia Corporation
 *
 * Contact: Luciano Coelho <luciano.coelho@nokia.com>
 */

#अगर_अघोषित __BOOT_H__
#घोषणा __BOOT_H__

#समावेश "wlcore.h"

पूर्णांक wlcore_boot_upload_firmware(काष्ठा wl1271 *wl);
पूर्णांक wlcore_boot_upload_nvs(काष्ठा wl1271 *wl);
पूर्णांक wlcore_boot_run_firmware(काष्ठा wl1271 *wl);

#घोषणा WL1271_NO_SUBBANDS 8
#घोषणा WL1271_NO_POWER_LEVELS 4
#घोषणा WL1271_FW_VERSION_MAX_LEN 20

काष्ठा wl1271_अटल_data अणु
	u8 mac_address[ETH_ALEN];
	u8 padding[2];
	u8 fw_version[WL1271_FW_VERSION_MAX_LEN];
	u32 hw_version;
	u8 tx_घातer_table[WL1271_NO_SUBBANDS][WL1271_NO_POWER_LEVELS];
	u8 priv[];
पूर्ण;

/* number of बार we try to पढ़ो the INIT पूर्णांकerrupt */
#घोषणा INIT_LOOP 20000

/* delay between retries */
#घोषणा INIT_LOOP_DELAY 50

#घोषणा WU_COUNTER_PAUSE_VAL 0x3FF
#घोषणा WELP_ARM_COMMAND_VAL 0x4

#पूर्ण_अगर
