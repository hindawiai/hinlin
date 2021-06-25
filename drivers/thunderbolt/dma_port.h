<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Thunderbolt DMA configuration based mailbox support
 *
 * Copyright (C) 2017, Intel Corporation
 * Authors: Michael Jamet <michael.jamet@पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित DMA_PORT_H_
#घोषणा DMA_PORT_H_

#समावेश "tb.h"

काष्ठा tb_चयन;
काष्ठा tb_dma_port;

#घोषणा DMA_PORT_CSS_ADDRESS		0x3fffff
#घोषणा DMA_PORT_CSS_MAX_SIZE		SZ_128

काष्ठा tb_dma_port *dma_port_alloc(काष्ठा tb_चयन *sw);
व्योम dma_port_मुक्त(काष्ठा tb_dma_port *dma);
पूर्णांक dma_port_flash_पढ़ो(काष्ठा tb_dma_port *dma, अचिन्हित पूर्णांक address,
			व्योम *buf, माप_प्रकार size);
पूर्णांक dma_port_flash_update_auth(काष्ठा tb_dma_port *dma);
पूर्णांक dma_port_flash_update_auth_status(काष्ठा tb_dma_port *dma, u32 *status);
पूर्णांक dma_port_flash_ग_लिखो(काष्ठा tb_dma_port *dma, अचिन्हित पूर्णांक address,
			 स्थिर व्योम *buf, माप_प्रकार size);
पूर्णांक dma_port_घातer_cycle(काष्ठा tb_dma_port *dma);

#पूर्ण_अगर
