<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <खोलोcsd/c_api/खोलोcsd_c_api.h>

/*
 * Check OpenCSD library version is sufficient to provide required features
 */
#घोषणा OCSD_MIN_VER ((1 << 16) | (0 << 8) | (0))
#अगर !defined(OCSD_VER_NUM) || (OCSD_VER_NUM < OCSD_MIN_VER)
#त्रुटि "OpenCSD >= 1.0.0 is required"
#पूर्ण_अगर

पूर्णांक मुख्य(व्योम)
अणु
	(व्योम)ocsd_get_version();
	वापस 0;
पूर्ण
