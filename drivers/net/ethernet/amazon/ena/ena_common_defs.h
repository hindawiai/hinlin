<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright 2015-2020 Amazon.com, Inc. or its affiliates. All rights reserved.
 */
#अगर_अघोषित _ENA_COMMON_H_
#घोषणा _ENA_COMMON_H_

#घोषणा ENA_COMMON_SPEC_VERSION_MAJOR        2
#घोषणा ENA_COMMON_SPEC_VERSION_MINOR        0

/* ENA operates with 48-bit memory addresses. ena_mem_addr_t */
काष्ठा ena_common_mem_addr अणु
	u32 mem_addr_low;

	u16 mem_addr_high;

	/* MBZ */
	u16 reserved16;
पूर्ण;

#पूर्ण_अगर /* _ENA_COMMON_H_ */
