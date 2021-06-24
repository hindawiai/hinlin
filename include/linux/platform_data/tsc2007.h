<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_I2C_TSC2007_H
#घोषणा __LINUX_I2C_TSC2007_H

/* linux/platक्रमm_data/tsc2007.h */

काष्ठा tsc2007_platक्रमm_data अणु
	u16	model;				/* 2007. */
	u16	x_plate_ohms;	/* must be non-zero value */
	u16	max_rt; /* max. resistance above which samples are ignored */
	अचिन्हित दीर्घ poll_period; /* समय (in ms) between samples */
	पूर्णांक	fuzzx; /* fuzz factor क्रम X, Y and pressure axes */
	पूर्णांक	fuzzy;
	पूर्णांक	fuzzz;

	पूर्णांक	(*get_penकरोwn_state)(काष्ठा device *);
	/* If needed, clear 2nd level पूर्णांकerrupt source */
	व्योम	(*clear_penirq)(व्योम);
	पूर्णांक	(*init_platक्रमm_hw)(व्योम);
	व्योम	(*निकास_platक्रमm_hw)(व्योम);
पूर्ण;

#पूर्ण_अगर
