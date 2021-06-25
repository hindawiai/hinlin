<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित __IA_CSS_COMMON_IO_TYPES
#घोषणा __IA_CSS_COMMON_IO_TYPES

#घोषणा MAX_IO_DMA_CHANNELS 3

काष्ठा ia_css_common_io_config अणु
	अचिन्हित पूर्णांक base_address;
	अचिन्हित पूर्णांक width;
	अचिन्हित पूर्णांक height;
	अचिन्हित पूर्णांक stride;
	अचिन्हित पूर्णांक ddr_elems_per_word;
	अचिन्हित पूर्णांक dma_channel[MAX_IO_DMA_CHANNELS];
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_COMMON_IO_TYPES */
