<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_cmd.c
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#समावेश "s5p_mfc_cmd.h"
#समावेश "s5p_mfc_common.h"
#समावेश "s5p_mfc_debug.h"
#समावेश "s5p_mfc_cmd_v5.h"
#समावेश "s5p_mfc_cmd_v6.h"

अटल काष्ठा s5p_mfc_hw_cmds *s5p_mfc_cmds;

व्योम s5p_mfc_init_hw_cmds(काष्ठा s5p_mfc_dev *dev)
अणु
	अगर (IS_MFCV6_PLUS(dev))
		s5p_mfc_cmds = s5p_mfc_init_hw_cmds_v6();
	अन्यथा
		s5p_mfc_cmds = s5p_mfc_init_hw_cmds_v5();

	dev->mfc_cmds = s5p_mfc_cmds;
पूर्ण
