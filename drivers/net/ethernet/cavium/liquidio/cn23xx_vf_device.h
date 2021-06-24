<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*! \पile  cn23xx_device.h
 * \मrief Host Driver: Routines that perक्रमm CN23XX specअगरic operations.
 */

#अगर_अघोषित __CN23XX_VF_DEVICE_H__
#घोषणा __CN23XX_VF_DEVICE_H__

#समावेश "cn23xx_vf_regs.h"

/* Register address and configuration क्रम a CN23XX devices.
 * If device specअगरic changes need to be made then add a काष्ठा to include
 * device specअगरic fields as shown in the commented section
 */
काष्ठा octeon_cn23xx_vf अणु
	काष्ठा octeon_config *conf;
पूर्ण;

#घोषणा BUSY_READING_REG_VF_LOOP_COUNT		10000

#घोषणा CN23XX_MAILBOX_MSGPARAM_SIZE		6

व्योम cn23xx_vf_ask_pf_to_करो_flr(काष्ठा octeon_device *oct);

पूर्णांक cn23xx_octeon_pfvf_handshake(काष्ठा octeon_device *oct);

पूर्णांक cn23xx_setup_octeon_vf_device(काष्ठा octeon_device *oct);

u32 cn23xx_vf_get_oq_ticks(काष्ठा octeon_device *oct, u32 समय_पूर्णांकr_in_us);

व्योम cn23xx_dump_vf_initialized_regs(काष्ठा octeon_device *oct);
#पूर्ण_अगर
