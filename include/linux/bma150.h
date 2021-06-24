<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (c) 2011 Bosch Sensortec GmbH
 * Copyright (c) 2011 Unixphere
 */

#अगर_अघोषित _BMA150_H_
#घोषणा _BMA150_H_

#घोषणा BMA150_DRIVER		"bma150"

#घोषणा BMA150_RANGE_2G		0
#घोषणा BMA150_RANGE_4G		1
#घोषणा BMA150_RANGE_8G		2

#घोषणा BMA150_BW_25HZ		0
#घोषणा BMA150_BW_50HZ		1
#घोषणा BMA150_BW_100HZ		2
#घोषणा BMA150_BW_190HZ		3
#घोषणा BMA150_BW_375HZ		4
#घोषणा BMA150_BW_750HZ		5
#घोषणा BMA150_BW_1500HZ	6

काष्ठा bma150_cfg अणु
	bool any_motion_पूर्णांक;		/* Set to enable any-motion पूर्णांकerrupt */
	bool hg_पूर्णांक;			/* Set to enable high-G पूर्णांकerrupt */
	bool lg_पूर्णांक;			/* Set to enable low-G पूर्णांकerrupt */
	अचिन्हित अक्षर any_motion_dur;	/* Any-motion duration */
	अचिन्हित अक्षर any_motion_thres;	/* Any-motion threshold */
	अचिन्हित अक्षर hg_hyst;		/* High-G hysterisis */
	अचिन्हित अक्षर hg_dur;		/* High-G duration */
	अचिन्हित अक्षर hg_thres;		/* High-G threshold */
	अचिन्हित अक्षर lg_hyst;		/* Low-G hysterisis */
	अचिन्हित अक्षर lg_dur;		/* Low-G duration */
	अचिन्हित अक्षर lg_thres;		/* Low-G threshold */
	अचिन्हित अक्षर range;		/* one of BMA0150_RANGE_xxx */
	अचिन्हित अक्षर bandwidth;	/* one of BMA0150_BW_xxx */
पूर्ण;

काष्ठा bma150_platक्रमm_data अणु
	काष्ठा bma150_cfg cfg;
	पूर्णांक (*irq_gpio_cfg)(व्योम);
पूर्ण;

#पूर्ण_अगर /* _BMA150_H_ */
