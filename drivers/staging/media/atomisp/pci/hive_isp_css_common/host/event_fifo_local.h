<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2010-2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित _EVENT_FIFO_LOCAL_H
#घोषणा _EVENT_FIFO_LOCAL_H

/*
 * All events come from connections mapped on the प्रणाली
 * bus but करो not use a global IRQ
 */
#समावेश "event_fifo_global.h"

प्रकार क्रमागत अणु
	SP0_EVENT_ID,
	ISP0_EVENT_ID,
	STR2MIPI_EVENT_ID,
	N_EVENT_ID
पूर्ण event_ID_t;

#घोषणा	EVENT_QUERY_BIT		0

/* Events are पढ़ो from FIFO */
अटल स्थिर hrt_address event_source_addr[N_EVENT_ID] = अणु
	0x0000000000380000ULL,
	0x0000000000380004ULL,
	0xffffffffffffffffULL
पूर्ण;

/* Read from FIFO are blocking, query data availability */
अटल स्थिर hrt_address event_source_query_addr[N_EVENT_ID] = अणु
	0x0000000000380010ULL,
	0x0000000000380014ULL,
	0xffffffffffffffffULL
पूर्ण;

/* Events are written to FIFO */
अटल स्थिर hrt_address event_sink_addr[N_EVENT_ID] = अणु
	0x0000000000380008ULL,
	0x000000000038000CULL,
	0x0000000000090104ULL
पूर्ण;

/* Writes to FIFO are blocking, query data space */
अटल स्थिर hrt_address event_sink_query_addr[N_EVENT_ID] = अणु
	0x0000000000380018ULL,
	0x000000000038001CULL,
	0x000000000009010CULL
पूर्ण;

#पूर्ण_अगर /* _EVENT_FIFO_LOCAL_H */
