<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित __IA_CSS_TIMER_H
#घोषणा __IA_CSS_TIMER_H

/* @file
 * Timer पूर्णांकerface definitions
 */
#समावेश <type_support.h>		/* क्रम uपूर्णांक32_t */
#समावेश "ia_css_err.h"

/* @brief समयr पढ़ोing definition */
प्रकार u32 घड़ी_value_t;

/* @brief 32 bit घड़ी tick,(बारtamp based on समयr-value of CSS-पूर्णांकernal समयr)*/
काष्ठा ia_css_घड़ी_प्रकारick अणु
	घड़ी_value_t ticks; /** measured समय in ticks.*/
पूर्ण;

/* @brief TIMER event codes */
क्रमागत ia_css_पंचांग_event अणु
	IA_CSS_TM_EVENT_AFTER_INIT,
	/** Timer Event after Initialization */
	IA_CSS_TM_EVENT_MAIN_END,
	/** Timer Event after end of Main */
	IA_CSS_TM_EVENT_THREAD_START,
	/** Timer Event after thपढ़ो start */
	IA_CSS_TM_EVENT_FRAME_PROC_START,
	/** Timer Event after Frame Process Start */
	IA_CSS_TM_EVENT_FRAME_PROC_END
	/** Timer Event after Frame Process End */
पूर्ण;

/* @brief code measurement common काष्ठा */
काष्ठा ia_css_समय_meas अणु
	घड़ी_value_t	start_समयr_value;	/** measured समय in ticks */
	घड़ी_value_t	end_समयr_value;	/** measured समय in ticks */
पूर्ण;

/**@brief SIZE_OF_IA_CSS_CLOCK_TICK_STRUCT checks to ensure correct alignment क्रम काष्ठा ia_css_घड़ी_प्रकारick. */
#घोषणा SIZE_OF_IA_CSS_CLOCK_TICK_STRUCT माप(घड़ी_value_t)
/* @brief checks to ensure correct alignment क्रम ia_css_समय_meas. */
#घोषणा SIZE_OF_IA_CSS_TIME_MEAS_STRUCT (माप(घड़ी_value_t) \
					+ माप(घड़ी_value_t))

/* @brief API to fetch समयr count directly
*
* @param curr_ts [out] measured count value
* @वापस 0 अगर success
*
*/
पूर्णांक
ia_css_समयr_get_current_tick(
    काष्ठा ia_css_घड़ी_प्रकारick *curr_ts);

#पूर्ण_अगर  /* __IA_CSS_TIMER_H */
