<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Freescale eDMA platक्रमm data, ColdFire SoC's family.
 *
 * Copyright (c) 2017 Angelo Dureghello <angelo@sysam.it>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित __LINUX_PLATFORM_DATA_MCF_EDMA_H__
#घोषणा __LINUX_PLATFORM_DATA_MCF_EDMA_H__

काष्ठा dma_slave_map;

bool mcf_edma_filter_fn(काष्ठा dma_chan *chan, व्योम *param);

#घोषणा MCF_EDMA_FILTER_PARAM(ch)	((व्योम *)ch)

/**
 * काष्ठा mcf_edma_platक्रमm_data - platक्रमm specअगरic data क्रम eDMA engine
 *
 * @ver			The eDMA module version.
 * @dma_channels	The number of eDMA channels.
 */
काष्ठा mcf_edma_platक्रमm_data अणु
	पूर्णांक dma_channels;
	स्थिर काष्ठा dma_slave_map *slave_map;
	पूर्णांक slavecnt;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PLATFORM_DATA_MCF_EDMA_H__ */
