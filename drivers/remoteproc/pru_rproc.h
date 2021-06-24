<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/*
 * PRUSS Remote Processor specअगरic types
 *
 * Copyright (C) 2014-2020 Texas Instruments Incorporated - https://www.ti.com/
 *	Suman Anna <s-anna@ti.com>
 */

#अगर_अघोषित _PRU_RPROC_H_
#घोषणा _PRU_RPROC_H_

/**
 * काष्ठा pruss_पूर्णांक_map - PRU प्रणाली events _to_ channel and host mapping
 * @event: number of the प्रणाली event
 * @chnl: channel number asचिन्हित to a given @event
 * @host: host number asचिन्हित to a given @chnl
 *
 * PRU प्रणाली events are mapped to channels, and these channels are mapped
 * to host पूर्णांकerrupts. Events can be mapped to channels in a one-to-one or
 * many-to-one ratio (multiple events per channel), and channels can be
 * mapped to host पूर्णांकerrupts in a one-to-one or many-to-one ratio (multiple
 * channels per पूर्णांकerrupt).
 */
काष्ठा pruss_पूर्णांक_map अणु
	u8 event;
	u8 chnl;
	u8 host;
पूर्ण;

/**
 * काष्ठा pru_irq_rsc - PRU firmware section header क्रम IRQ data
 * @type: resource type
 * @num_evts: number of described events
 * @pru_पूर्णांकc_map: PRU पूर्णांकerrupt routing description
 *
 * The PRU firmware blob can contain optional .pru_irq_map ELF section, which
 * provides the PRUSS पूर्णांकerrupt mapping description. The pru_irq_rsc काष्ठा
 * describes resource entry क्रमmat.
 */
काष्ठा pru_irq_rsc अणु
	u8 type;
	u8 num_evts;
	काष्ठा pruss_पूर्णांक_map pru_पूर्णांकc_map[];
पूर्ण __packed;

#पूर्ण_अगर	/* _PRU_RPROC_H_ */
