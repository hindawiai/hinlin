<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * This file is part of wl1251
 *
 * Copyright (C) 2008 Nokia Corporation
 */

#अगर_अघोषित __BOOT_H__
#घोषणा __BOOT_H__

#समावेश "wl1251.h"

पूर्णांक wl1251_boot_soft_reset(काष्ठा wl1251 *wl);
पूर्णांक wl1251_boot_init_seq(काष्ठा wl1251 *wl);
पूर्णांक wl1251_boot_run_firmware(काष्ठा wl1251 *wl);
व्योम wl1251_boot_target_enable_पूर्णांकerrupts(काष्ठा wl1251 *wl);
पूर्णांक wl1251_boot(काष्ठा wl1251 *wl);

/* number of बार we try to पढ़ो the INIT पूर्णांकerrupt */
#घोषणा INIT_LOOP 20000

/* delay between retries */
#घोषणा INIT_LOOP_DELAY 50

#पूर्ण_अगर
