<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * The Virtual DVB test driver serves as a reference DVB driver and helps
 * validate the existing APIs in the media subप्रणाली. It can also aid
 * developers working on userspace applications.
 *
 * Copyright (C) 2020 Daniel W. S. Almeida
 */

#अगर_अघोषित VIDTV_COMMON_H
#घोषणा VIDTV_COMMON_H

#समावेश <linux/types.h>

#घोषणा CLOCK_UNIT_90KHZ 90000
#घोषणा CLOCK_UNIT_27MHZ 27000000
#घोषणा VIDTV_SLEEP_USECS 10000
#घोषणा VIDTV_MAX_SLEEP_USECS (2 * VIDTV_SLEEP_USECS)

u32 vidtv_स_नकल(व्योम *to,
		 माप_प्रकार to_offset,
		 माप_प्रकार to_size,
		 स्थिर व्योम *from,
		 माप_प्रकार len);

u32 vidtv_स_रखो(व्योम *to,
		 माप_प्रकार to_offset,
		 माप_प्रकार to_size,
		 पूर्णांक c,
		 माप_प्रकार len);

#पूर्ण_अगर // VIDTV_COMMON_H
