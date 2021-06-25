<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_NVRAM_H
#घोषणा _UAPI_LINUX_NVRAM_H

#समावेश <linux/ioctl.h>

/* /dev/nvram ioctls */
#घोषणा NVRAM_INIT	_IO('p', 0x40) /* initialize NVRAM and set checksum */
#घोषणा NVRAM_SETCKS	_IO('p', 0x41) /* recalculate checksum */

/* क्रम all current प्रणालीs, this is where NVRAM starts */
#घोषणा NVRAM_FIRST_BYTE    14
/* all these functions expect an NVRAM offset, not an असलolute */
#घोषणा NVRAM_OFFSET(x)   ((x)-NVRAM_FIRST_BYTE)


#पूर्ण_अगर /* _UAPI_LINUX_NVRAM_H */
