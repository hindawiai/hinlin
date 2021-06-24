<शैली गुरु>
/*
 * SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright (c) 2008 Intel Corporation
 * Copyright (c) 2018 The Linux Foundation. All rights reserved.
 */

#अगर_अघोषित _ASCII85_H_
#घोषणा _ASCII85_H_

#समावेश <linux/kernel.h>

#घोषणा ASCII85_BUFSZ 6

अटल अंतरभूत दीर्घ
ascii85_encode_len(दीर्घ len)
अणु
	वापस DIV_ROUND_UP(len, 4);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *
ascii85_encode(u32 in, अक्षर *out)
अणु
	पूर्णांक i;

	अगर (in == 0)
		वापस "z";

	out[5] = '\0';
	क्रम (i = 5; i--; ) अणु
		out[i] = '!' + in % 85;
		in /= 85;
	पूर्ण

	वापस out;
पूर्ण

#पूर्ण_अगर
