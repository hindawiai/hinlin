<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2016-17 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __SOC_ARC_TIMERS_H
#घोषणा __SOC_ARC_TIMERS_H

#समावेश <soc/arc/aux.h>

/* Timer related Aux रेजिस्टरs */
#घोषणा ARC_REG_TIMER0_LIMIT	0x23	/* समयr 0 limit */
#घोषणा ARC_REG_TIMER0_CTRL	0x22	/* समयr 0 control */
#घोषणा ARC_REG_TIMER0_CNT	0x21	/* समयr 0 count */
#घोषणा ARC_REG_TIMER1_LIMIT	0x102	/* समयr 1 limit */
#घोषणा ARC_REG_TIMER1_CTRL	0x101	/* समयr 1 control */
#घोषणा ARC_REG_TIMER1_CNT	0x100	/* समयr 1 count */

/* CTRL reg bits */
#घोषणा TIMER_CTRL_IE	        (1 << 0) /* Interrupt when Count reaches limit */
#घोषणा TIMER_CTRL_NH	        (1 << 1) /* Count only when CPU NOT halted */

#घोषणा ARC_TIMERN_MAX		0xFFFFFFFF

#घोषणा ARC_REG_TIMERS_BCR	0x75

काष्ठा bcr_समयr अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad2:15, rtsc:1, pad1:5, rtc:1, t1:1, t0:1, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, t0:1, t1:1, rtc:1, pad1:5, rtsc:1, pad2:15;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर
