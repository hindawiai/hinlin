<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PPS kernel consumer API header
 *
 * Copyright (C) 2009-2010   Alexander Gordeev <lasaine@lvk.cs.msu.su>
 */

#अगर_अघोषित LINUX_PPS_KC_H
#घोषणा LINUX_PPS_KC_H

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/pps_kernel.h>

#अगर_घोषित CONFIG_NTP_PPS

बाह्य पूर्णांक pps_kc_bind(काष्ठा pps_device *pps,
		काष्ठा pps_bind_args *bind_args);
बाह्य व्योम pps_kc_हटाओ(काष्ठा pps_device *pps);
बाह्य व्योम pps_kc_event(काष्ठा pps_device *pps,
		काष्ठा pps_event_समय *ts, पूर्णांक event);


#अन्यथा /* CONFIG_NTP_PPS */

अटल अंतरभूत पूर्णांक pps_kc_bind(काष्ठा pps_device *pps,
		काष्ठा pps_bind_args *bind_args) अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत व्योम pps_kc_हटाओ(काष्ठा pps_device *pps) अणुपूर्ण
अटल अंतरभूत व्योम pps_kc_event(काष्ठा pps_device *pps,
		काष्ठा pps_event_समय *ts, पूर्णांक event) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_NTP_PPS */

#पूर्ण_अगर /* LINUX_PPS_KC_H */
