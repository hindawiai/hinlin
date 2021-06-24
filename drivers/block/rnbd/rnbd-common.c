<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * RDMA Network Block Driver
 *
 * Copyright (c) 2014 - 2018 ProfitBricks GmbH. All rights reserved.
 * Copyright (c) 2018 - 2019 1&1 IONOS Cloud GmbH. All rights reserved.
 * Copyright (c) 2019 - 2020 1&1 IONOS SE. All rights reserved.
 */
#समावेश "rnbd-proto.h"

स्थिर अक्षर *rnbd_access_mode_str(क्रमागत rnbd_access_mode mode)
अणु
	चयन (mode) अणु
	हाल RNBD_ACCESS_RO:
		वापस "ro";
	हाल RNBD_ACCESS_RW:
		वापस "rw";
	हाल RNBD_ACCESS_MIGRATION:
		वापस "migration";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
