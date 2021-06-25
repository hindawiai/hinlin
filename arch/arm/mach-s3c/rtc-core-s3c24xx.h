<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2011 Heiko Stuebner <heiko@sntech.de>
 *
 * Samsung RTC Controller core functions
 */

#अगर_अघोषित __RTC_CORE_S3C24XX_H
#घोषणा __RTC_CORE_S3C24XX_H __खाता__

/* These functions are only क्रम use with the core support code, such as
 * the cpu specअगरic initialisation code
 */

बाह्य काष्ठा platक्रमm_device s3c_device_rtc;

/* re-define device name depending on support. */
अटल अंतरभूत व्योम s3c_rtc_setname(अक्षर *name)
अणु
	s3c_device_rtc.name = name;
पूर्ण

#पूर्ण_अगर /* __RTC_CORE_S3C24XX_H */
