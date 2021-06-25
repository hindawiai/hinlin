<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_TRANSPORT_ACCESS_MACROS_H
#घोषणा ADF_TRANSPORT_ACCESS_MACROS_H

#समावेश "adf_accel_devices.h"
#घोषणा ADF_RING_CONFIG_NEAR_FULL_WM 0x0A
#घोषणा ADF_RING_CONFIG_NEAR_EMPTY_WM 0x05
#घोषणा ADF_COALESCING_MIN_TIME 0x1FF
#घोषणा ADF_COALESCING_MAX_TIME 0xFFFFF
#घोषणा ADF_COALESCING_DEF_TIME 0x27FF
#घोषणा ADF_RING_NEAR_WATERMARK_512 0x08
#घोषणा ADF_RING_NEAR_WATERMARK_0 0x00
#घोषणा ADF_RING_EMPTY_SIG 0x7F7F7F7F

/* Valid पूर्णांकernal ring size values */
#घोषणा ADF_RING_SIZE_128 0x01
#घोषणा ADF_RING_SIZE_256 0x02
#घोषणा ADF_RING_SIZE_512 0x03
#घोषणा ADF_RING_SIZE_4K 0x06
#घोषणा ADF_RING_SIZE_16K 0x08
#घोषणा ADF_RING_SIZE_4M 0x10
#घोषणा ADF_MIN_RING_SIZE ADF_RING_SIZE_128
#घोषणा ADF_MAX_RING_SIZE ADF_RING_SIZE_4M
#घोषणा ADF_DEFAULT_RING_SIZE ADF_RING_SIZE_16K

/* Valid पूर्णांकernal msg size values */
#घोषणा ADF_MSG_SIZE_32 0x01
#घोषणा ADF_MSG_SIZE_64 0x02
#घोषणा ADF_MSG_SIZE_128 0x04
#घोषणा ADF_MIN_MSG_SIZE ADF_MSG_SIZE_32
#घोषणा ADF_MAX_MSG_SIZE ADF_MSG_SIZE_128

/* Size to bytes conversion macros क्रम ring and msg size values */
#घोषणा ADF_MSG_SIZE_TO_BYTES(SIZE) (SIZE << 5)
#घोषणा ADF_BYTES_TO_MSG_SIZE(SIZE) (SIZE >> 5)
#घोषणा ADF_SIZE_TO_RING_SIZE_IN_BYTES(SIZE) ((1 << (SIZE - 1)) << 7)
#घोषणा ADF_RING_SIZE_IN_BYTES_TO_SIZE(SIZE) ((1 << (SIZE - 1)) >> 7)

/* Minimum ring bufer size क्रम memory allocation */
#घोषणा ADF_RING_SIZE_BYTES_MIN(SIZE) \
	((SIZE < ADF_SIZE_TO_RING_SIZE_IN_BYTES(ADF_RING_SIZE_4K)) ? \
		ADF_SIZE_TO_RING_SIZE_IN_BYTES(ADF_RING_SIZE_4K) : SIZE)
#घोषणा ADF_RING_SIZE_MODULO(SIZE) (SIZE + 0x6)
#घोषणा ADF_SIZE_TO_POW(SIZE) ((((SIZE & 0x4) >> 1) | ((SIZE & 0x4) >> 2) | \
				SIZE) & ~0x4)
/* Max outstanding requests */
#घोषणा ADF_MAX_INFLIGHTS(RING_SIZE, MSG_SIZE) \
	((((1 << (RING_SIZE - 1)) << 3) >> ADF_SIZE_TO_POW(MSG_SIZE)) - 1)
#घोषणा BUILD_RING_CONFIG(size)	\
	((ADF_RING_NEAR_WATERMARK_0 << ADF_RING_CONFIG_NEAR_FULL_WM) \
	| (ADF_RING_NEAR_WATERMARK_0 << ADF_RING_CONFIG_NEAR_EMPTY_WM) \
	| size)
#घोषणा BUILD_RESP_RING_CONFIG(size, watermark_nf, watermark_ne) \
	((watermark_nf << ADF_RING_CONFIG_NEAR_FULL_WM)	\
	| (watermark_ne << ADF_RING_CONFIG_NEAR_EMPTY_WM) \
	| size)
#पूर्ण_अगर
