<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * timb_dma.h timberdale FPGA DMA driver defines
 * Copyright (c) 2010 Intel Corporation
 */

/* Supports:
 * Timberdale FPGA DMA engine
 */

#अगर_अघोषित _LINUX_TIMB_DMA_H
#घोषणा _LINUX_TIMB_DMA_H

/**
 * काष्ठा timb_dma_platक्रमm_data_channel - Description of each inभागidual
 *	DMA channel क्रम the timberdale DMA driver
 * @rx:			true अगर this channel handles data in the direction to
 *	the CPU.
 * @bytes_per_line:	Number of bytes per line, this is specअगरic क्रम channels
 *	handling video data. For other channels this shall be left to 0.
 * @descriptors:	Number of descriptors to allocate क्रम this channel.
 * @descriptor_elements: Number of elements in each descriptor.
 *
 */
काष्ठा timb_dma_platक्रमm_data_channel अणु
	bool rx;
	अचिन्हित पूर्णांक bytes_per_line;
	अचिन्हित पूर्णांक descriptors;
	अचिन्हित पूर्णांक descriptor_elements;
पूर्ण;

/**
 * काष्ठा timb_dma_platक्रमm_data - Platक्रमm data of the timberdale DMA driver
 * @nr_channels:	Number of defined channels in the channels array.
 * @channels:		Definition of the each channel.
 *
 */
काष्ठा timb_dma_platक्रमm_data अणु
	अचिन्हित nr_channels;
	काष्ठा timb_dma_platक्रमm_data_channel channels[32];
पूर्ण;

#पूर्ण_अगर
