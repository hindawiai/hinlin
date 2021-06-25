<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Freescale ALSA SoC Machine driver utility
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * Copyright 2010 Freescale Semiconductor, Inc.
 */

#अगर_अघोषित _FSL_UTILS_H
#घोषणा _FSL_UTILS_H

#घोषणा DAI_NAME_SIZE	32

काष्ठा snd_soc_dai_link;
काष्ठा device_node;

पूर्णांक fsl_asoc_get_dma_channel(काष्ठा device_node *ssi_np, स्थिर अक्षर *name,
			     काष्ठा snd_soc_dai_link *dai,
			     अचिन्हित पूर्णांक *dma_channel_id,
			     अचिन्हित पूर्णांक *dma_id);
#पूर्ण_अगर /* _FSL_UTILS_H */
