<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * errors.h - Definitions of errors क्रम DIM2 HAL API
 * (MediaLB, Device Interface Macro IP, OS62420)
 *
 * Copyright (C) 2015, Microchip Technology Germany II GmbH & Co. KG
 */

#अगर_अघोषित _MOST_DIM_ERRORS_H
#घोषणा _MOST_DIM_ERRORS_H

/**
 * MOST DIM errors.
 */
क्रमागत dim_errors_t अणु
	/** Not an error */
	DIM_NO_ERROR = 0,

	/** Bad base address क्रम DIM2 IP */
	DIM_INIT_ERR_DIM_ADDR = 0x10,

	/**< Bad MediaLB घड़ी */
	DIM_INIT_ERR_MLB_CLOCK,

	/** Bad channel address */
	DIM_INIT_ERR_CHANNEL_ADDRESS,

	/** Out of DBR memory */
	DIM_INIT_ERR_OUT_OF_MEMORY,

	/** DIM API is called जबतक DIM is not initialized successfully */
	DIM_ERR_DRIVER_NOT_INITIALIZED = 0x20,

	/**
	 * Configuration करोes not respect hardware limitations
	 * क्रम isochronous or synchronous channels
	 */
	DIM_ERR_BAD_CONFIG,

	/**
	 * Buffer size करोes not respect hardware limitations
	 * क्रम isochronous or synchronous channels
	 */
	DIM_ERR_BAD_BUFFER_SIZE,

	DIM_ERR_UNDERFLOW,

	DIM_ERR_OVERFLOW,
पूर्ण;

#पूर्ण_अगर /* _MOST_DIM_ERRORS_H */
