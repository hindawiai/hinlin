<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * drivers/media/platक्रमm/s5p-mfc/s5p_mfc_debug.h
 *
 * Header file क्रम Samsung MFC (Multi Function Codec - FIMV) driver
 * This file contains debug macros
 *
 * Kamil Debski, Copyright (c) 2011 Samsung Electronics
 * http://www.samsung.com/
 */

#अगर_अघोषित S5P_MFC_DEBUG_H_
#घोषणा S5P_MFC_DEBUG_H_

#घोषणा DEBUG

#अगर_घोषित DEBUG
बाह्य पूर्णांक mfc_debug_level;

#घोषणा mfc_debug(level, fmt, args...)				\
	करो अणु							\
		अगर (mfc_debug_level >= level)			\
			prपूर्णांकk(KERN_DEBUG "%s:%d: " fmt,	\
				__func__, __LINE__, ##args);	\
	पूर्ण जबतक (0)
#अन्यथा
#घोषणा mfc_debug(level, fmt, args...)
#पूर्ण_अगर

#घोषणा mfc_debug_enter() mfc_debug(5, "enter\n")
#घोषणा mfc_debug_leave() mfc_debug(5, "leave\n")

#घोषणा mfc_err(fmt, args...)				\
	करो अणु						\
		prपूर्णांकk(KERN_ERR "%s:%d: " fmt,		\
		       __func__, __LINE__, ##args);	\
	पूर्ण जबतक (0)

#घोषणा mfc_err_limited(fmt, args...)			\
	करो अणु						\
		prपूर्णांकk_ratelimited(KERN_ERR "%s:%d: " fmt,	\
		       __func__, __LINE__, ##args);	\
	पूर्ण जबतक (0)

#घोषणा mfc_info(fmt, args...)				\
	करो अणु						\
		prपूर्णांकk(KERN_INFO "%s:%d: " fmt,		\
		       __func__, __LINE__, ##args);	\
	पूर्ण जबतक (0)

#पूर्ण_अगर /* S5P_MFC_DEBUG_H_ */
