<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Definitions क्रम talking to the CUDA.  The CUDA is a microcontroller
 * which controls the ADB, प्रणाली घातer, RTC, and various other things.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */

#अगर_अघोषित _UAPI_LINUX_CUDA_H
#घोषणा _UAPI_LINUX_CUDA_H

/* CUDA commands (2nd byte) */
#घोषणा CUDA_WARM_START		0
#घोषणा CUDA_AUTOPOLL		1
#घोषणा CUDA_GET_6805_ADDR	2
#घोषणा CUDA_GET_TIME		3
#घोषणा CUDA_GET_PRAM		7
#घोषणा CUDA_SET_6805_ADDR	8
#घोषणा CUDA_SET_TIME		9
#घोषणा CUDA_POWERDOWN		0xa
#घोषणा CUDA_POWERUP_TIME	0xb
#घोषणा CUDA_SET_PRAM		0xc
#घोषणा CUDA_MS_RESET		0xd
#घोषणा CUDA_SEND_DFAC		0xe
#घोषणा CUDA_RESET_SYSTEM	0x11
#घोषणा CUDA_SET_IPL		0x12
#घोषणा CUDA_SET_AUTO_RATE	0x14
#घोषणा CUDA_GET_AUTO_RATE	0x16
#घोषणा CUDA_SET_DEVICE_LIST	0x19
#घोषणा CUDA_GET_DEVICE_LIST	0x1a
#घोषणा CUDA_GET_SET_IIC	0x22


#पूर्ण_अगर /* _UAPI_LINUX_CUDA_H */
