<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Support क्रम Medअगरield PNW Camera Imaging ISP subप्रणाली.
 *
 * Copyright (c) 2010 Intel Corporation. All Rights Reserved.
 *
 * Copyright (c) 2010 Silicon Hive www.siliconhive.com.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */

#अगर_अघोषित	__HMM_BO_COMMON_H__
#घोषणा	__HMM_BO_COMMON_H__

#घोषणा	HMM_BO_NAME	"HMM"

/*
 * some common use micros
 */
#घोषणा	var_equal_वापस(var1, var2, exp, fmt, arg ...)	\
	करो अणु \
		अगर ((var1) == (var2)) अणु \
			dev_err(atomisp_dev, \
			fmt, ## arg); \
			वापस exp;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा	var_equal_वापस_व्योम(var1, var2, fmt, arg ...)	\
	करो अणु \
		अगर ((var1) == (var2)) अणु \
			dev_err(atomisp_dev, \
			fmt, ## arg); \
			वापस;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा	var_equal_जाओ(var1, var2, label, fmt, arg ...)	\
	करो अणु \
		अगर ((var1) == (var2)) अणु \
			dev_err(atomisp_dev, \
			fmt, ## arg); \
			जाओ label;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा	var_not_equal_जाओ(var1, var2, label, fmt, arg ...)	\
	करो अणु \
		अगर ((var1) != (var2)) अणु \
			dev_err(atomisp_dev, \
			fmt, ## arg); \
			जाओ label;\
		पूर्ण \
	पूर्ण जबतक (0)

#घोषणा	check_null_वापस(ptr, exp, fmt, arg ...)	\
		var_equal_वापस(ptr, शून्य, exp, fmt, ## arg)

#घोषणा	check_null_वापस_व्योम(ptr, fmt, arg ...)	\
		var_equal_वापस_व्योम(ptr, शून्य, fmt, ## arg)

/* hmm_mem_stat is used to trace the hmm mem used by ISP pipe. The unit is page
 * number.
 *
 * res_size:  reserved mem pool size, being allocated from प्रणाली at प्रणाली boot समय.
 *		res_size >= res_cnt.
 * sys_size:  प्रणाली mem pool size, being allocated from प्रणाली at camera running समय.
 *		dyc_size:  dynamic mem pool size.
 *		dyc_thr:   dynamic mem pool high watermark.
 *		dyc_size <= dyc_thr.
 * usr_size:  user ptr mem size.
 *
 * res_cnt:   track the mem allocated from reserved pool at camera running समय.
 * tol_cnt:   track the total mem used by ISP pipe at camera running समय.
 */
काष्ठा _hmm_mem_stat अणु
	पूर्णांक res_size;
	पूर्णांक sys_size;
	पूर्णांक dyc_size;
	पूर्णांक dyc_thr;
	पूर्णांक usr_size;
	पूर्णांक res_cnt;
	पूर्णांक tol_cnt;
पूर्ण;

बाह्य काष्ठा _hmm_mem_stat hmm_mem_stat;

#पूर्ण_अगर
