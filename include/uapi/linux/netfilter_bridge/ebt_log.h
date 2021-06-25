<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __LINUX_BRIDGE_EBT_LOG_H
#घोषणा __LINUX_BRIDGE_EBT_LOG_H

#समावेश <linux/types.h>

#घोषणा EBT_LOG_IP 0x01 /* अगर the frame is made by ip, log the ip inक्रमmation */
#घोषणा EBT_LOG_ARP 0x02
#घोषणा EBT_LOG_NFLOG 0x04
#घोषणा EBT_LOG_IP6 0x08
#घोषणा EBT_LOG_MASK (EBT_LOG_IP | EBT_LOG_ARP | EBT_LOG_IP6)
#घोषणा EBT_LOG_PREFIX_SIZE 30
#घोषणा EBT_LOG_WATCHER "log"

काष्ठा ebt_log_info अणु
	__u8 loglevel;
	__u8 prefix[EBT_LOG_PREFIX_SIZE];
	__u32 biपंचांगask;
पूर्ण;

#पूर्ण_अगर
