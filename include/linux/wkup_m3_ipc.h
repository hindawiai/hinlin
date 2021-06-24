<शैली गुरु>
/*
 * TI Wakeup M3 क्रम AMx3 SoCs Power Management Routines
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - https://www.ti.com/
 * Dave Gerlach <d-gerlach@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _LINUX_WKUP_M3_IPC_H
#घोषणा _LINUX_WKUP_M3_IPC_H

#घोषणा WKUP_M3_DEEPSLEEP	1
#घोषणा WKUP_M3_STANDBY		2
#घोषणा WKUP_M3_IDLE		3

#समावेश <linux/mailbox_client.h>

काष्ठा wkup_m3_ipc_ops;

काष्ठा wkup_m3_ipc अणु
	काष्ठा rproc *rproc;

	व्योम __iomem *ipc_mem_base;
	काष्ठा device *dev;

	पूर्णांक mem_type;
	अचिन्हित दीर्घ resume_addr;
	पूर्णांक state;

	काष्ठा completion sync_complete;
	काष्ठा mbox_client mbox_client;
	काष्ठा mbox_chan *mbox;

	काष्ठा wkup_m3_ipc_ops *ops;
	पूर्णांक is_rtc_only;
पूर्ण;

काष्ठा wkup_m3_wakeup_src अणु
	पूर्णांक irq_nr;
	अक्षर src[10];
पूर्ण;

काष्ठा wkup_m3_ipc_ops अणु
	व्योम (*set_mem_type)(काष्ठा wkup_m3_ipc *m3_ipc, पूर्णांक mem_type);
	व्योम (*set_resume_address)(काष्ठा wkup_m3_ipc *m3_ipc, व्योम *addr);
	पूर्णांक (*prepare_low_घातer)(काष्ठा wkup_m3_ipc *m3_ipc, पूर्णांक state);
	पूर्णांक (*finish_low_घातer)(काष्ठा wkup_m3_ipc *m3_ipc);
	पूर्णांक (*request_pm_status)(काष्ठा wkup_m3_ipc *m3_ipc);
	स्थिर अक्षर *(*request_wake_src)(काष्ठा wkup_m3_ipc *m3_ipc);
	व्योम (*set_rtc_only)(काष्ठा wkup_m3_ipc *m3_ipc);
पूर्ण;

काष्ठा wkup_m3_ipc *wkup_m3_ipc_get(व्योम);
व्योम wkup_m3_ipc_put(काष्ठा wkup_m3_ipc *m3_ipc);
व्योम wkup_m3_set_rtc_only_mode(व्योम);
#पूर्ण_अगर /* _LINUX_WKUP_M3_IPC_H */
