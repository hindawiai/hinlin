<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_cmd.h
 *
 * Copyright (C) 2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अगर_अघोषित S5P_MFC_CMD_H_
#घोषणा S5P_MFC_CMD_H_

#समावेश "s5p_mfc_common.h"

#घोषणा MAX_H2R_ARG	4

काष्ठा s5p_mfc_cmd_args अणु
	अचिन्हित पूर्णांक	arg[MAX_H2R_ARG];
पूर्ण;

काष्ठा s5p_mfc_hw_cmds अणु
	पूर्णांक (*cmd_host2risc)(काष्ठा s5p_mfc_dev *dev, पूर्णांक cmd,
				काष्ठा s5p_mfc_cmd_args *args);
	पूर्णांक (*sys_init_cmd)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*sleep_cmd)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*wakeup_cmd)(काष्ठा s5p_mfc_dev *dev);
	पूर्णांक (*खोलो_inst_cmd)(काष्ठा s5p_mfc_ctx *ctx);
	पूर्णांक (*बंद_inst_cmd)(काष्ठा s5p_mfc_ctx *ctx);
पूर्ण;

व्योम s5p_mfc_init_hw_cmds(काष्ठा s5p_mfc_dev *dev);
#पूर्ण_अगर /* S5P_MFC_CMD_H_ */
