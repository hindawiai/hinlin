<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Definitions क्रम talking to the CUDA.  The CUDA is a microcontroller
 * which controls the ADB, प्रणाली घातer, RTC, and various other things.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */
#अगर_अघोषित _LINUX_CUDA_H
#घोषणा _LINUX_CUDA_H

#समावेश <linux/rtc.h>
#समावेश <uapi/linux/cuda.h>


बाह्य पूर्णांक find_via_cuda(व्योम);
बाह्य पूर्णांक cuda_request(काष्ठा adb_request *req,
			व्योम (*करोne)(काष्ठा adb_request *), पूर्णांक nbytes, ...);
बाह्य व्योम cuda_poll(व्योम);

बाह्य समय64_t cuda_get_समय(व्योम);
बाह्य पूर्णांक cuda_set_rtc_समय(काष्ठा rtc_समय *पंचांग);

#पूर्ण_अगर /* _LINUX_CUDA_H */
