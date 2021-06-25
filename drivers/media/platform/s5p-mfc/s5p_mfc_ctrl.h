<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/drivers/media/platक्रमm/s5p-mfc/s5p_mfc_ctrl.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 */

#अगर_अघोषित S5P_MFC_CTRL_H
#घोषणा S5P_MFC_CTRL_H

#समावेश "s5p_mfc_common.h"

पूर्णांक s5p_mfc_release_firmware(काष्ठा s5p_mfc_dev *dev);
पूर्णांक s5p_mfc_alloc_firmware(काष्ठा s5p_mfc_dev *dev);
पूर्णांक s5p_mfc_load_firmware(काष्ठा s5p_mfc_dev *dev);

पूर्णांक s5p_mfc_init_hw(काष्ठा s5p_mfc_dev *dev);
व्योम s5p_mfc_deinit_hw(काष्ठा s5p_mfc_dev *dev);

पूर्णांक s5p_mfc_sleep(काष्ठा s5p_mfc_dev *dev);
पूर्णांक s5p_mfc_wakeup(काष्ठा s5p_mfc_dev *dev);

पूर्णांक s5p_mfc_reset(काष्ठा s5p_mfc_dev *dev);

पूर्णांक s5p_mfc_खोलो_mfc_inst(काष्ठा s5p_mfc_dev *dev, काष्ठा s5p_mfc_ctx *ctx);
व्योम s5p_mfc_बंद_mfc_inst(काष्ठा s5p_mfc_dev *dev, काष्ठा s5p_mfc_ctx *ctx);

#पूर्ण_अगर /* S5P_MFC_CTRL_H */
