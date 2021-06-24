<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Dumb driver क्रम LiIon batteries using TWL4030 madc.
 *
 * Copyright 2013 Golden Delicious Computers
 * Nikolaus Schaller <hns@goldelico.com>
 */

#अगर_अघोषित __TWL4030_MADC_BATTERY_H
#घोषणा __TWL4030_MADC_BATTERY_H

/*
 * Usually we can assume 100% @ 4.15V and 0% @ 3.3V but curves dअगरfer क्रम
 * अक्षरging and disअक्षरging!
 */

काष्ठा twl4030_madc_bat_calibration अणु
	लघु voltage;	/* in mV - specअगरy -1 क्रम end of list */
	लघु level;	/* in percent (0 .. 100%) */
पूर्ण;

काष्ठा twl4030_madc_bat_platक्रमm_data अणु
	अचिन्हित पूर्णांक capacity;	/* total capacity in uAh */
	काष्ठा twl4030_madc_bat_calibration *अक्षरging;
	पूर्णांक अक्षरging_size;
	काष्ठा twl4030_madc_bat_calibration *disअक्षरging;
	पूर्णांक disअक्षरging_size;
पूर्ण;

#पूर्ण_अगर
