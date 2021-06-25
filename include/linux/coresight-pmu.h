<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright(C) 2015 Linaro Limited. All rights reserved.
 * Author: Mathieu Poirier <mathieu.poirier@linaro.org>
 */

#अगर_अघोषित _LINUX_CORESIGHT_PMU_H
#घोषणा _LINUX_CORESIGHT_PMU_H

#घोषणा CORESIGHT_ETM_PMU_NAME "cs_etm"
#घोषणा CORESIGHT_ETM_PMU_SEED  0x10

/*
 * Below are the definition of bit offsets क्रम perf option, and works as
 * arbitrary values क्रम all ETM versions.
 *
 * Most of them are orignally from ETMv3.5/PTM's ETMCR config, thereक्रमe,
 * ETMv3.5/PTM करोesn't define ETMCR config bits with prefix "ETM3_" and
 * directly use below macros as config bits.
 */
#घोषणा ETM_OPT_CYCACC		12
#घोषणा ETM_OPT_CTXTID		14
#घोषणा ETM_OPT_CTXTID2		15
#घोषणा ETM_OPT_TS		28
#घोषणा ETM_OPT_RETSTK		29

/* ETMv4 CONFIGR programming bits क्रम the ETM OPTs */
#घोषणा ETM4_CFG_BIT_CYCACC	4
#घोषणा ETM4_CFG_BIT_CTXTID	6
#घोषणा ETM4_CFG_BIT_VMID	7
#घोषणा ETM4_CFG_BIT_TS		11
#घोषणा ETM4_CFG_BIT_RETSTK	12
#घोषणा ETM4_CFG_BIT_VMID_OPT	15

अटल अंतरभूत पूर्णांक coresight_get_trace_id(पूर्णांक cpu)
अणु
	/*
	 * A trace ID of value 0 is invalid, so let's start at some
	 * अक्रमom value that fits in 7 bits and go from there.  Since
	 * the common convention is to have data trace IDs be I(N) + 1,
	 * set inकाष्ठाion trace IDs as a function of the CPU number.
	 */
	वापस (CORESIGHT_ETM_PMU_SEED + (cpu * 2));
पूर्ण

#पूर्ण_अगर
