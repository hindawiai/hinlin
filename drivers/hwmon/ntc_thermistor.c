<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ntc_thermistor.c - NTC Thermistors
 *
 *  Copyright (C) 2010 Samsung Electronics
 *  MyungJoo Ham <myungjoo.ham@samsung.com>
 */

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/math64.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/platक्रमm_data/ntc_thermistor.h>

#समावेश <linux/iio/iपन.स>
#समावेश <linux/iio/machine.h>
#समावेश <linux/iio/driver.h>
#समावेश <linux/iio/consumer.h>

#समावेश <linux/hwmon.h>

काष्ठा ntc_compensation अणु
	पूर्णांक		temp_c;
	अचिन्हित पूर्णांक	ohm;
पूर्ण;

/*
 * Used as index in a zero-terminated array, holes not allowed so
 * that NTC_LAST is the first empty array entry.
 */
क्रमागत अणु
	NTC_B57330V2103,
	NTC_B57891S0103,
	NTC_NCP03WB473,
	NTC_NCP03WF104,
	NTC_NCP15WB473,
	NTC_NCP15WL333,
	NTC_NCP15XH103,
	NTC_NCP18WB473,
	NTC_NCP21WB473,
	NTC_LAST,
पूर्ण;

अटल स्थिर काष्ठा platक्रमm_device_id ntc_thermistor_id[] = अणु
	[NTC_B57330V2103]     = अणु "b57330v2103",     TYPE_B57330V2103 पूर्ण,
	[NTC_B57891S0103]     = अणु "b57891s0103",     TYPE_B57891S0103 पूर्ण,
	[NTC_NCP03WB473]      = अणु "ncp03wb473",      TYPE_NCPXXWB473 पूर्ण,
	[NTC_NCP03WF104]      = अणु "ncp03wf104",      TYPE_NCPXXWF104 पूर्ण,
	[NTC_NCP15WB473]      = अणु "ncp15wb473",      TYPE_NCPXXWB473 पूर्ण,
	[NTC_NCP15WL333]      = अणु "ncp15wl333",      TYPE_NCPXXWL333 पूर्ण,
	[NTC_NCP15XH103]      = अणु "ncp15xh103",      TYPE_NCPXXXH103 पूर्ण,
	[NTC_NCP18WB473]      = अणु "ncp18wb473",      TYPE_NCPXXWB473 पूर्ण,
	[NTC_NCP21WB473]      = अणु "ncp21wb473",      TYPE_NCPXXWB473 पूर्ण,
	[NTC_LAST]            = अणु पूर्ण,
पूर्ण;

/*
 * A compensation table should be sorted by the values of .ohm
 * in descending order.
 * The following compensation tables are from the specअगरication of Murata NTC
 * Thermistors Datasheet
 */
अटल स्थिर काष्ठा ntc_compensation ncpXXwb473[] = अणु
	अणु .temp_c	= -40, .ohm	= 1747920 पूर्ण,
	अणु .temp_c	= -35, .ohm	= 1245428 पूर्ण,
	अणु .temp_c	= -30, .ohm	= 898485 पूर्ण,
	अणु .temp_c	= -25, .ohm	= 655802 पूर्ण,
	अणु .temp_c	= -20, .ohm	= 483954 पूर्ण,
	अणु .temp_c	= -15, .ohm	= 360850 पूर्ण,
	अणु .temp_c	= -10, .ohm	= 271697 पूर्ण,
	अणु .temp_c	= -5, .ohm	= 206463 पूर्ण,
	अणु .temp_c	= 0, .ohm	= 158214 पूर्ण,
	अणु .temp_c	= 5, .ohm	= 122259 पूर्ण,
	अणु .temp_c	= 10, .ohm	= 95227 पूर्ण,
	अणु .temp_c	= 15, .ohm	= 74730 पूर्ण,
	अणु .temp_c	= 20, .ohm	= 59065 पूर्ण,
	अणु .temp_c	= 25, .ohm	= 47000 पूर्ण,
	अणु .temp_c	= 30, .ohm	= 37643 पूर्ण,
	अणु .temp_c	= 35, .ohm	= 30334 पूर्ण,
	अणु .temp_c	= 40, .ohm	= 24591 पूर्ण,
	अणु .temp_c	= 45, .ohm	= 20048 पूर्ण,
	अणु .temp_c	= 50, .ohm	= 16433 पूर्ण,
	अणु .temp_c	= 55, .ohm	= 13539 पूर्ण,
	अणु .temp_c	= 60, .ohm	= 11209 पूर्ण,
	अणु .temp_c	= 65, .ohm	= 9328 पूर्ण,
	अणु .temp_c	= 70, .ohm	= 7798 पूर्ण,
	अणु .temp_c	= 75, .ohm	= 6544 पूर्ण,
	अणु .temp_c	= 80, .ohm	= 5518 पूर्ण,
	अणु .temp_c	= 85, .ohm	= 4674 पूर्ण,
	अणु .temp_c	= 90, .ohm	= 3972 पूर्ण,
	अणु .temp_c	= 95, .ohm	= 3388 पूर्ण,
	अणु .temp_c	= 100, .ohm	= 2902 पूर्ण,
	अणु .temp_c	= 105, .ohm	= 2494 पूर्ण,
	अणु .temp_c	= 110, .ohm	= 2150 पूर्ण,
	अणु .temp_c	= 115, .ohm	= 1860 पूर्ण,
	अणु .temp_c	= 120, .ohm	= 1615 पूर्ण,
	अणु .temp_c	= 125, .ohm	= 1406 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा ntc_compensation ncpXXwl333[] = अणु
	अणु .temp_c	= -40, .ohm	= 1610154 पूर्ण,
	अणु .temp_c	= -35, .ohm	= 1130850 पूर्ण,
	अणु .temp_c	= -30, .ohm	= 802609 पूर्ण,
	अणु .temp_c	= -25, .ohm	= 575385 पूर्ण,
	अणु .temp_c	= -20, .ohm	= 416464 पूर्ण,
	अणु .temp_c	= -15, .ohm	= 304219 पूर्ण,
	अणु .temp_c	= -10, .ohm	= 224193 पूर्ण,
	अणु .temp_c	= -5, .ohm	= 166623 पूर्ण,
	अणु .temp_c	= 0, .ohm	= 124850 पूर्ण,
	अणु .temp_c	= 5, .ohm	= 94287 पूर्ण,
	अणु .temp_c	= 10, .ohm	= 71747 पूर्ण,
	अणु .temp_c	= 15, .ohm	= 54996 पूर्ण,
	अणु .temp_c	= 20, .ohm	= 42455 पूर्ण,
	अणु .temp_c	= 25, .ohm	= 33000 पूर्ण,
	अणु .temp_c	= 30, .ohm	= 25822 पूर्ण,
	अणु .temp_c	= 35, .ohm	= 20335 पूर्ण,
	अणु .temp_c	= 40, .ohm	= 16115 पूर्ण,
	अणु .temp_c	= 45, .ohm	= 12849 पूर्ण,
	अणु .temp_c	= 50, .ohm	= 10306 पूर्ण,
	अणु .temp_c	= 55, .ohm	= 8314 पूर्ण,
	अणु .temp_c	= 60, .ohm	= 6746 पूर्ण,
	अणु .temp_c	= 65, .ohm	= 5503 पूर्ण,
	अणु .temp_c	= 70, .ohm	= 4513 पूर्ण,
	अणु .temp_c	= 75, .ohm	= 3721 पूर्ण,
	अणु .temp_c	= 80, .ohm	= 3084 पूर्ण,
	अणु .temp_c	= 85, .ohm	= 2569 पूर्ण,
	अणु .temp_c	= 90, .ohm	= 2151 पूर्ण,
	अणु .temp_c	= 95, .ohm	= 1809 पूर्ण,
	अणु .temp_c	= 100, .ohm	= 1529 पूर्ण,
	अणु .temp_c	= 105, .ohm	= 1299 पूर्ण,
	अणु .temp_c	= 110, .ohm	= 1108 पूर्ण,
	अणु .temp_c	= 115, .ohm	= 949 पूर्ण,
	अणु .temp_c	= 120, .ohm	= 817 पूर्ण,
	अणु .temp_c	= 125, .ohm	= 707 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ntc_compensation ncpXXwf104[] = अणु
	अणु .temp_c	= -40, .ohm	= 4397119 पूर्ण,
	अणु .temp_c	= -35, .ohm	= 3088599 पूर्ण,
	अणु .temp_c	= -30, .ohm	= 2197225 पूर्ण,
	अणु .temp_c	= -25, .ohm	= 1581881 पूर्ण,
	अणु .temp_c	= -20, .ohm	= 1151037 पूर्ण,
	अणु .temp_c	= -15, .ohm	= 846579 पूर्ण,
	अणु .temp_c	= -10, .ohm	= 628988 पूर्ण,
	अणु .temp_c	= -5, .ohm	= 471632 पूर्ण,
	अणु .temp_c	= 0, .ohm	= 357012 पूर्ण,
	अणु .temp_c	= 5, .ohm	= 272500 पूर्ण,
	अणु .temp_c	= 10, .ohm	= 209710 पूर्ण,
	अणु .temp_c	= 15, .ohm	= 162651 पूर्ण,
	अणु .temp_c	= 20, .ohm	= 127080 पूर्ण,
	अणु .temp_c	= 25, .ohm	= 100000 पूर्ण,
	अणु .temp_c	= 30, .ohm	= 79222 पूर्ण,
	अणु .temp_c	= 35, .ohm	= 63167 पूर्ण,
	अणु .temp_c	= 40, .ohm	= 50677 पूर्ण,
	अणु .temp_c	= 45, .ohm	= 40904 पूर्ण,
	अणु .temp_c	= 50, .ohm	= 33195 पूर्ण,
	अणु .temp_c	= 55, .ohm	= 27091 पूर्ण,
	अणु .temp_c	= 60, .ohm	= 22224 पूर्ण,
	अणु .temp_c	= 65, .ohm	= 18323 पूर्ण,
	अणु .temp_c	= 70, .ohm	= 15184 पूर्ण,
	अणु .temp_c	= 75, .ohm	= 12635 पूर्ण,
	अणु .temp_c	= 80, .ohm	= 10566 पूर्ण,
	अणु .temp_c	= 85, .ohm	= 8873 पूर्ण,
	अणु .temp_c	= 90, .ohm	= 7481 पूर्ण,
	अणु .temp_c	= 95, .ohm	= 6337 पूर्ण,
	अणु .temp_c	= 100, .ohm	= 5384 पूर्ण,
	अणु .temp_c	= 105, .ohm	= 4594 पूर्ण,
	अणु .temp_c	= 110, .ohm	= 3934 पूर्ण,
	अणु .temp_c	= 115, .ohm	= 3380 पूर्ण,
	अणु .temp_c	= 120, .ohm	= 2916 पूर्ण,
	अणु .temp_c	= 125, .ohm	= 2522 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ntc_compensation ncpXXxh103[] = अणु
	अणु .temp_c	= -40, .ohm	= 247565 पूर्ण,
	अणु .temp_c	= -35, .ohm	= 181742 पूर्ण,
	अणु .temp_c	= -30, .ohm	= 135128 पूर्ण,
	अणु .temp_c	= -25, .ohm	= 101678 पूर्ण,
	अणु .temp_c	= -20, .ohm	= 77373 पूर्ण,
	अणु .temp_c	= -15, .ohm	= 59504 पूर्ण,
	अणु .temp_c	= -10, .ohm	= 46222 पूर्ण,
	अणु .temp_c	= -5, .ohm	= 36244 पूर्ण,
	अणु .temp_c	= 0, .ohm	= 28674 पूर्ण,
	अणु .temp_c	= 5, .ohm	= 22878 पूर्ण,
	अणु .temp_c	= 10, .ohm	= 18399 पूर्ण,
	अणु .temp_c	= 15, .ohm	= 14910 पूर्ण,
	अणु .temp_c	= 20, .ohm	= 12169 पूर्ण,
	अणु .temp_c	= 25, .ohm	= 10000 पूर्ण,
	अणु .temp_c	= 30, .ohm	= 8271 पूर्ण,
	अणु .temp_c	= 35, .ohm	= 6883 पूर्ण,
	अणु .temp_c	= 40, .ohm	= 5762 पूर्ण,
	अणु .temp_c	= 45, .ohm	= 4851 पूर्ण,
	अणु .temp_c	= 50, .ohm	= 4105 पूर्ण,
	अणु .temp_c	= 55, .ohm	= 3492 पूर्ण,
	अणु .temp_c	= 60, .ohm	= 2985 पूर्ण,
	अणु .temp_c	= 65, .ohm	= 2563 पूर्ण,
	अणु .temp_c	= 70, .ohm	= 2211 पूर्ण,
	अणु .temp_c	= 75, .ohm	= 1915 पूर्ण,
	अणु .temp_c	= 80, .ohm	= 1666 पूर्ण,
	अणु .temp_c	= 85, .ohm	= 1454 पूर्ण,
	अणु .temp_c	= 90, .ohm	= 1275 पूर्ण,
	अणु .temp_c	= 95, .ohm	= 1121 पूर्ण,
	अणु .temp_c	= 100, .ohm	= 990 पूर्ण,
	अणु .temp_c	= 105, .ohm	= 876 पूर्ण,
	अणु .temp_c	= 110, .ohm	= 779 पूर्ण,
	अणु .temp_c	= 115, .ohm	= 694 पूर्ण,
	अणु .temp_c	= 120, .ohm	= 620 पूर्ण,
	अणु .temp_c	= 125, .ohm	= 556 पूर्ण,
पूर्ण;

/*
 * The following compensation tables are from the specअगरications in EPCOS NTC
 * Thermistors Datasheets
 */
अटल स्थिर काष्ठा ntc_compensation b57330v2103[] = अणु
	अणु .temp_c	= -40, .ohm	= 190030 पूर्ण,
	अणु .temp_c	= -35, .ohm	= 145360 पूर्ण,
	अणु .temp_c	= -30, .ohm	= 112060 पूर्ण,
	अणु .temp_c	= -25, .ohm	= 87041 पूर्ण,
	अणु .temp_c	= -20, .ohm	= 68104 पूर्ण,
	अणु .temp_c	= -15, .ohm	= 53665 पूर्ण,
	अणु .temp_c	= -10, .ohm	= 42576 पूर्ण,
	अणु .temp_c	= -5, .ohm	= 34001 पूर्ण,
	अणु .temp_c	= 0, .ohm	= 27326 पूर्ण,
	अणु .temp_c	= 5, .ohm	= 22096 पूर्ण,
	अणु .temp_c	= 10, .ohm	= 17973 पूर्ण,
	अणु .temp_c	= 15, .ohm	= 14703 पूर्ण,
	अणु .temp_c	= 20, .ohm	= 12090 पूर्ण,
	अणु .temp_c	= 25, .ohm	= 10000 पूर्ण,
	अणु .temp_c	= 30, .ohm	= 8311 पूर्ण,
	अणु .temp_c	= 35, .ohm	= 6941 पूर्ण,
	अणु .temp_c	= 40, .ohm	= 5825 पूर्ण,
	अणु .temp_c	= 45, .ohm	= 4911 पूर्ण,
	अणु .temp_c	= 50, .ohm	= 4158 पूर्ण,
	अणु .temp_c	= 55, .ohm	= 3536 पूर्ण,
	अणु .temp_c	= 60, .ohm	= 3019 पूर्ण,
	अणु .temp_c	= 65, .ohm	= 2588 पूर्ण,
	अणु .temp_c	= 70, .ohm	= 2227 पूर्ण,
	अणु .temp_c	= 75, .ohm	= 1924 पूर्ण,
	अणु .temp_c	= 80, .ohm	= 1668 पूर्ण,
	अणु .temp_c	= 85, .ohm	= 1451 पूर्ण,
	अणु .temp_c	= 90, .ohm	= 1266 पूर्ण,
	अणु .temp_c	= 95, .ohm	= 1108 पूर्ण,
	अणु .temp_c	= 100, .ohm	= 973 पूर्ण,
	अणु .temp_c	= 105, .ohm	= 857 पूर्ण,
	अणु .temp_c	= 110, .ohm	= 757 पूर्ण,
	अणु .temp_c	= 115, .ohm	= 671 पूर्ण,
	अणु .temp_c	= 120, .ohm	= 596 पूर्ण,
	अणु .temp_c	= 125, .ohm	= 531 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ntc_compensation b57891s0103[] = अणु
	अणु .temp_c	= -55.0, .ohm	= 878900 पूर्ण,
	अणु .temp_c	= -50.0, .ohm	= 617590 पूर्ण,
	अणु .temp_c	= -45.0, .ohm	= 439340 पूर्ण,
	अणु .temp_c	= -40.0, .ohm	= 316180 पूर्ण,
	अणु .temp_c	= -35.0, .ohm	= 230060 पूर्ण,
	अणु .temp_c	= -30.0, .ohm	= 169150 पूर्ण,
	अणु .temp_c	= -25.0, .ohm	= 125550 पूर्ण,
	अणु .temp_c	= -20.0, .ohm	= 94143 पूर्ण,
	अणु .temp_c	= -15.0, .ohm	= 71172 पूर्ण,
	अणु .temp_c	= -10.0, .ohm	= 54308 पूर्ण,
	अणु .temp_c	= -5.0, .ohm	= 41505 पूर्ण,
	अणु .temp_c	= 0.0, .ohm	= 32014 पूर्ण,
	अणु .temp_c	= 5.0, .ohm	= 25011 पूर्ण,
	अणु .temp_c	= 10.0, .ohm	= 19691 पूर्ण,
	अणु .temp_c	= 15.0, .ohm	= 15618 पूर्ण,
	अणु .temp_c	= 20.0, .ohm	= 12474 पूर्ण,
	अणु .temp_c	= 25.0, .ohm	= 10000 पूर्ण,
	अणु .temp_c	= 30.0, .ohm	= 8080 पूर्ण,
	अणु .temp_c	= 35.0, .ohm	= 6569 पूर्ण,
	अणु .temp_c	= 40.0, .ohm	= 5372 पूर्ण,
	अणु .temp_c	= 45.0, .ohm	= 4424 पूर्ण,
	अणु .temp_c	= 50.0, .ohm	= 3661 पूर्ण,
	अणु .temp_c	= 55.0, .ohm	= 3039 पूर्ण,
	अणु .temp_c	= 60.0, .ohm	= 2536 पूर्ण,
	अणु .temp_c	= 65.0, .ohm	= 2128 पूर्ण,
	अणु .temp_c	= 70.0, .ohm	= 1794 पूर्ण,
	अणु .temp_c	= 75.0, .ohm	= 1518 पूर्ण,
	अणु .temp_c	= 80.0, .ohm	= 1290 पूर्ण,
	अणु .temp_c	= 85.0, .ohm	= 1100 पूर्ण,
	अणु .temp_c	= 90.0, .ohm	= 942 पूर्ण,
	अणु .temp_c	= 95.0, .ohm	= 809 पूर्ण,
	अणु .temp_c	= 100.0, .ohm	= 697 पूर्ण,
	अणु .temp_c	= 105.0, .ohm	= 604 पूर्ण,
	अणु .temp_c	= 110.0, .ohm	= 525 पूर्ण,
	अणु .temp_c	= 115.0, .ohm	= 457 पूर्ण,
	अणु .temp_c	= 120.0, .ohm	= 400 पूर्ण,
	अणु .temp_c	= 125.0, .ohm	= 351 पूर्ण,
	अणु .temp_c	= 130.0, .ohm	= 308 पूर्ण,
	अणु .temp_c	= 135.0, .ohm	= 272 पूर्ण,
	अणु .temp_c	= 140.0, .ohm	= 240 पूर्ण,
	अणु .temp_c	= 145.0, .ohm	= 213 पूर्ण,
	अणु .temp_c	= 150.0, .ohm	= 189 पूर्ण,
	अणु .temp_c	= 155.0, .ohm	= 168 पूर्ण,
पूर्ण;

काष्ठा ntc_type अणु
	स्थिर काष्ठा ntc_compensation *comp;
	पूर्णांक n_comp;
पूर्ण;

#घोषणा NTC_TYPE(ntc, compensation) \
[(ntc)] = अणु .comp = (compensation), .n_comp = ARRAY_SIZE(compensation) पूर्ण

अटल स्थिर काष्ठा ntc_type ntc_type[] = अणु
	NTC_TYPE(TYPE_B57330V2103, b57330v2103),
	NTC_TYPE(TYPE_B57891S0103, b57891s0103),
	NTC_TYPE(TYPE_NCPXXWB473,  ncpXXwb473),
	NTC_TYPE(TYPE_NCPXXWF104,  ncpXXwf104),
	NTC_TYPE(TYPE_NCPXXWL333,  ncpXXwl333),
	NTC_TYPE(TYPE_NCPXXXH103,  ncpXXxh103),
पूर्ण;

काष्ठा ntc_data अणु
	काष्ठा ntc_thermistor_platक्रमm_data *pdata;
	स्थिर काष्ठा ntc_compensation *comp;
	पूर्णांक n_comp;
पूर्ण;

#अगर defined(CONFIG_OF) && IS_ENABLED(CONFIG_IIO)
अटल पूर्णांक ntc_adc_iio_पढ़ो(काष्ठा ntc_thermistor_platक्रमm_data *pdata)
अणु
	काष्ठा iio_channel *channel = pdata->chan;
	पूर्णांक uv, ret;

	ret = iio_पढ़ो_channel_processed_scale(channel, &uv, 1000);
	अगर (ret < 0) अणु
		पूर्णांक raw;

		/*
		 * This fallback uses a raw पढ़ो and then
		 * assumes the ADC is 12 bits, scaling with
		 * a factor 1000 to get to microvolts.
		 */
		ret = iio_पढ़ो_channel_raw(channel, &raw);
		अगर (ret < 0) अणु
			pr_err("read channel() error: %d\n", ret);
			वापस ret;
		पूर्ण
		ret = iio_convert_raw_to_processed(channel, raw, &uv, 1000);
		अगर (ret < 0) अणु
			/* Assume 12 bit ADC with vref at pullup_uv */
			uv = (pdata->pullup_uv * (s64)raw) >> 12;
		पूर्ण
	पूर्ण

	वापस uv;
पूर्ण

अटल स्थिर काष्ठा of_device_id ntc_match[] = अणु
	अणु .compatible = "epcos,b57330v2103",
		.data = &ntc_thermistor_id[NTC_B57330V2103]पूर्ण,
	अणु .compatible = "epcos,b57891s0103",
		.data = &ntc_thermistor_id[NTC_B57891S0103] पूर्ण,
	अणु .compatible = "murata,ncp03wb473",
		.data = &ntc_thermistor_id[NTC_NCP03WB473] पूर्ण,
	अणु .compatible = "murata,ncp03wf104",
		.data = &ntc_thermistor_id[NTC_NCP03WF104] पूर्ण,
	अणु .compatible = "murata,ncp15wb473",
		.data = &ntc_thermistor_id[NTC_NCP15WB473] पूर्ण,
	अणु .compatible = "murata,ncp15wl333",
		.data = &ntc_thermistor_id[NTC_NCP15WL333] पूर्ण,
	अणु .compatible = "murata,ncp15xh103",
		.data = &ntc_thermistor_id[NTC_NCP15XH103] पूर्ण,
	अणु .compatible = "murata,ncp18wb473",
		.data = &ntc_thermistor_id[NTC_NCP18WB473] पूर्ण,
	अणु .compatible = "murata,ncp21wb473",
		.data = &ntc_thermistor_id[NTC_NCP21WB473] पूर्ण,

	/* Usage of venकरोr name "ntc" is deprecated */
	अणु .compatible = "ntc,ncp03wb473",
		.data = &ntc_thermistor_id[NTC_NCP03WB473] पूर्ण,
	अणु .compatible = "ntc,ncp15wb473",
		.data = &ntc_thermistor_id[NTC_NCP15WB473] पूर्ण,
	अणु .compatible = "ntc,ncp15wl333",
		.data = &ntc_thermistor_id[NTC_NCP15WL333] पूर्ण,
	अणु .compatible = "ntc,ncp18wb473",
		.data = &ntc_thermistor_id[NTC_NCP18WB473] पूर्ण,
	अणु .compatible = "ntc,ncp21wb473",
		.data = &ntc_thermistor_id[NTC_NCP21WB473] पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, ntc_match);

अटल काष्ठा ntc_thermistor_platक्रमm_data *
ntc_thermistor_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा iio_channel *chan;
	क्रमागत iio_chan_type type;
	काष्ठा device_node *np = dev->of_node;
	काष्ठा ntc_thermistor_platक्रमm_data *pdata;
	पूर्णांक ret;

	अगर (!np)
		वापस शून्य;

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	chan = devm_iio_channel_get(dev, शून्य);
	अगर (IS_ERR(chan))
		वापस ERR_CAST(chan);

	ret = iio_get_channel_type(chan, &type);
	अगर (ret < 0)
		वापस ERR_PTR(ret);

	अगर (type != IIO_VOLTAGE)
		वापस ERR_PTR(-EINVAL);

	अगर (of_property_पढ़ो_u32(np, "pullup-uv", &pdata->pullup_uv))
		वापस ERR_PTR(-ENODEV);
	अगर (of_property_पढ़ो_u32(np, "pullup-ohm", &pdata->pullup_ohm))
		वापस ERR_PTR(-ENODEV);
	अगर (of_property_पढ़ो_u32(np, "pulldown-ohm", &pdata->pullकरोwn_ohm))
		वापस ERR_PTR(-ENODEV);

	अगर (of_find_property(np, "connected-positive", शून्य))
		pdata->connect = NTC_CONNECTED_POSITIVE;
	अन्यथा /* status change should be possible अगर not always on. */
		pdata->connect = NTC_CONNECTED_GROUND;

	pdata->chan = chan;
	pdata->पढ़ो_uv = ntc_adc_iio_पढ़ो;

	वापस pdata;
पूर्ण
#अन्यथा
अटल काष्ठा ntc_thermistor_platक्रमm_data *
ntc_thermistor_parse_dt(काष्ठा device *dev)
अणु
	वापस शून्य;
पूर्ण

#घोषणा ntc_match	शून्य

#पूर्ण_अगर

अटल अंतरभूत u64 भाग64_u64_safe(u64 भागidend, u64 भागisor)
अणु
	अगर (भागisor == 0 && भागidend == 0)
		वापस 0;
	अगर (भागisor == 0)
		वापस अच_पूर्णांक_उच्च;
	वापस भाग64_u64(भागidend, भागisor);
पूर्ण

अटल पूर्णांक get_ohm_of_thermistor(काष्ठा ntc_data *data, अचिन्हित पूर्णांक uv)
अणु
	काष्ठा ntc_thermistor_platक्रमm_data *pdata = data->pdata;
	u32 puv = pdata->pullup_uv;
	u64 n, puo, pकरो;
	puo = pdata->pullup_ohm;
	pकरो = pdata->pullकरोwn_ohm;

	अगर (uv == 0)
		वापस (pdata->connect == NTC_CONNECTED_POSITIVE) ?
			पूर्णांक_उच्च : 0;
	अगर (uv >= puv)
		वापस (pdata->connect == NTC_CONNECTED_POSITIVE) ?
			0 : पूर्णांक_उच्च;

	अगर (pdata->connect == NTC_CONNECTED_POSITIVE && puo == 0)
		n = भाग_u64(pकरो * (puv - uv), uv);
	अन्यथा अगर (pdata->connect == NTC_CONNECTED_GROUND && pकरो == 0)
		n = भाग_u64(puo * uv, puv - uv);
	अन्यथा अगर (pdata->connect == NTC_CONNECTED_POSITIVE)
		n = भाग64_u64_safe(pकरो * puo * (puv - uv),
				puo * uv - pकरो * (puv - uv));
	अन्यथा
		n = भाग64_u64_safe(pकरो * puo * uv, pकरो * (puv - uv) - puo * uv);

	अगर (n > पूर्णांक_उच्च)
		n = पूर्णांक_उच्च;
	वापस n;
पूर्ण

अटल व्योम lookup_comp(काष्ठा ntc_data *data, अचिन्हित पूर्णांक ohm,
			पूर्णांक *i_low, पूर्णांक *i_high)
अणु
	पूर्णांक start, end, mid;

	/*
	 * Handle special हालs: Resistance is higher than or equal to
	 * resistance in first table entry, or resistance is lower or equal
	 * to resistance in last table entry.
	 * In these हालs, वापस i_low == i_high, either poपूर्णांकing to the
	 * beginning or to the end of the table depending on the condition.
	 */
	अगर (ohm >= data->comp[0].ohm) अणु
		*i_low = 0;
		*i_high = 0;
		वापस;
	पूर्ण
	अगर (ohm <= data->comp[data->n_comp - 1].ohm) अणु
		*i_low = data->n_comp - 1;
		*i_high = data->n_comp - 1;
		वापस;
	पूर्ण

	/* Do a binary search on compensation table */
	start = 0;
	end = data->n_comp;
	जबतक (start < end) अणु
		mid = start + (end - start) / 2;
		/*
		 * start <= mid < end
		 * data->comp[start].ohm > ohm >= data->comp[end].ohm
		 *
		 * We could check क्रम "ohm == data->comp[mid].ohm" here, but
		 * that is a quite unlikely condition, and we would have to
		 * check again after updating start. Check it at the end instead
		 * क्रम simplicity.
		 */
		अगर (ohm >= data->comp[mid].ohm) अणु
			end = mid;
		पूर्ण अन्यथा अणु
			start = mid + 1;
			/*
			 * ohm >= data->comp[start].ohm might be true here,
			 * since we set start to mid + 1. In that हाल, we are
			 * करोne. We could keep going, but the condition is quite
			 * likely to occur, so it is worth checking क्रम it.
			 */
			अगर (ohm >= data->comp[start].ohm)
				end = start;
		पूर्ण
		/*
		 * start <= end
		 * data->comp[start].ohm >= ohm >= data->comp[end].ohm
		 */
	पूर्ण
	/*
	 * start == end
	 * ohm >= data->comp[end].ohm
	 */
	*i_low = end;
	अगर (ohm == data->comp[end].ohm)
		*i_high = end;
	अन्यथा
		*i_high = end - 1;
पूर्ण

अटल पूर्णांक get_temp_mc(काष्ठा ntc_data *data, अचिन्हित पूर्णांक ohm)
अणु
	पूर्णांक low, high;
	पूर्णांक temp;

	lookup_comp(data, ohm, &low, &high);
	अगर (low == high) अणु
		/* Unable to use linear approximation */
		temp = data->comp[low].temp_c * 1000;
	पूर्ण अन्यथा अणु
		temp = data->comp[low].temp_c * 1000 +
			((data->comp[high].temp_c - data->comp[low].temp_c) *
			 1000 * ((पूर्णांक)ohm - (पूर्णांक)data->comp[low].ohm)) /
			((पूर्णांक)data->comp[high].ohm - (पूर्णांक)data->comp[low].ohm);
	पूर्ण
	वापस temp;
पूर्ण

अटल पूर्णांक ntc_thermistor_get_ohm(काष्ठा ntc_data *data)
अणु
	पूर्णांक पढ़ो_uv;

	अगर (data->pdata->पढ़ो_ohm)
		वापस data->pdata->पढ़ो_ohm();

	अगर (data->pdata->पढ़ो_uv) अणु
		पढ़ो_uv = data->pdata->पढ़ो_uv(data->pdata);
		अगर (पढ़ो_uv < 0)
			वापस पढ़ो_uv;
		वापस get_ohm_of_thermistor(data, पढ़ो_uv);
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक ntc_पढ़ो(काष्ठा device *dev, क्रमागत hwmon_sensor_types type,
		    u32 attr, पूर्णांक channel, दीर्घ *val)
अणु
	काष्ठा ntc_data *data = dev_get_drvdata(dev);
	पूर्णांक ohm;

	चयन (type) अणु
	हाल hwmon_temp:
		चयन (attr) अणु
		हाल hwmon_temp_input:
			ohm = ntc_thermistor_get_ohm(data);
			अगर (ohm < 0)
				वापस ohm;
			*val = get_temp_mc(data, ohm);
			वापस 0;
		हाल hwmon_temp_type:
			*val = 4;
			वापस 0;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल umode_t ntc_is_visible(स्थिर व्योम *data, क्रमागत hwmon_sensor_types type,
			      u32 attr, पूर्णांक channel)
अणु
	अगर (type == hwmon_temp) अणु
		चयन (attr) अणु
		हाल hwmon_temp_input:
		हाल hwmon_temp_type:
			वापस 0444;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा hwmon_channel_info *ntc_info[] = अणु
	HWMON_CHANNEL_INFO(chip, HWMON_C_REGISTER_TZ),
	HWMON_CHANNEL_INFO(temp, HWMON_T_INPUT | HWMON_T_TYPE),
	शून्य
पूर्ण;

अटल स्थिर काष्ठा hwmon_ops ntc_hwmon_ops = अणु
	.is_visible = ntc_is_visible,
	.पढ़ो = ntc_पढ़ो,
पूर्ण;

अटल स्थिर काष्ठा hwmon_chip_info ntc_chip_info = अणु
	.ops = &ntc_hwmon_ops,
	.info = ntc_info,
पूर्ण;

अटल पूर्णांक ntc_thermistor_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	स्थिर काष्ठा of_device_id *of_id =
			of_match_device(of_match_ptr(ntc_match), dev);
	स्थिर काष्ठा platक्रमm_device_id *pdev_id;
	काष्ठा ntc_thermistor_platक्रमm_data *pdata;
	काष्ठा device *hwmon_dev;
	काष्ठा ntc_data *data;

	pdata = ntc_thermistor_parse_dt(dev);
	अगर (IS_ERR(pdata))
		वापस PTR_ERR(pdata);
	अन्यथा अगर (pdata == शून्य)
		pdata = dev_get_platdata(dev);

	अगर (!pdata) अणु
		dev_err(dev, "No platform init data supplied.\n");
		वापस -ENODEV;
	पूर्ण

	/* Either one of the two is required. */
	अगर (!pdata->पढ़ो_uv && !pdata->पढ़ो_ohm) अणु
		dev_err(dev,
			"Both read_uv and read_ohm missing. Need either one of the two.\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdata->पढ़ो_uv && pdata->पढ़ो_ohm) अणु
		dev_warn(dev,
			 "Only one of read_uv and read_ohm is needed; ignoring read_uv.\n");
		pdata->पढ़ो_uv = शून्य;
	पूर्ण

	अगर (pdata->पढ़ो_uv && (pdata->pullup_uv == 0 ||
				(pdata->pullup_ohm == 0 && pdata->connect ==
				 NTC_CONNECTED_GROUND) ||
				(pdata->pullकरोwn_ohm == 0 && pdata->connect ==
				 NTC_CONNECTED_POSITIVE) ||
				(pdata->connect != NTC_CONNECTED_POSITIVE &&
				 pdata->connect != NTC_CONNECTED_GROUND))) अणु
		dev_err(dev, "Required data to use read_uv not supplied.\n");
		वापस -EINVAL;
	पूर्ण

	data = devm_kzalloc(dev, माप(काष्ठा ntc_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	pdev_id = of_id ? of_id->data : platक्रमm_get_device_id(pdev);

	data->pdata = pdata;

	अगर (pdev_id->driver_data >= ARRAY_SIZE(ntc_type)) अणु
		dev_err(dev, "Unknown device type: %lu(%s)\n",
				pdev_id->driver_data, pdev_id->name);
		वापस -EINVAL;
	पूर्ण

	data->comp   = ntc_type[pdev_id->driver_data].comp;
	data->n_comp = ntc_type[pdev_id->driver_data].n_comp;

	hwmon_dev = devm_hwmon_device_रेजिस्टर_with_info(dev, pdev_id->name,
							 data, &ntc_chip_info,
							 शून्य);
	अगर (IS_ERR(hwmon_dev)) अणु
		dev_err(dev, "unable to register as hwmon device.\n");
		वापस PTR_ERR(hwmon_dev);
	पूर्ण

	dev_info(dev, "Thermistor type: %s successfully probed.\n",
		 pdev_id->name);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ntc_thermistor_driver = अणु
	.driver = अणु
		.name = "ntc-thermistor",
		.of_match_table = of_match_ptr(ntc_match),
	पूर्ण,
	.probe = ntc_thermistor_probe,
	.id_table = ntc_thermistor_id,
पूर्ण;

module_platक्रमm_driver(ntc_thermistor_driver);

MODULE_DESCRIPTION("NTC Thermistor Driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:ntc-thermistor");
