<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Atlantic Network Driver
 *
 * Copyright (C) 2014-2019 aQuantia Corporation
 * Copyright (C) 2019-2020 Marvell International Ltd.
 */

/* File aq_hw_utils.h: Declaration of helper functions used across hardware
 * layer.
 */

#अगर_अघोषित AQ_HW_UTILS_H
#घोषणा AQ_HW_UTILS_H

#समावेश <linux/iopoll.h>

#समावेश "aq_common.h"

#अगर_अघोषित HIDWORD
#घोषणा LODWORD(_qw)    ((u32)(_qw))
#घोषणा HIDWORD(_qw)    ((u32)(((_qw) >> 32) & 0xffffffff))
#पूर्ण_अगर

#घोषणा AQ_HW_SLEEP(_US_) mdelay(_US_)

#घोषणा aq_pr_err(...) pr_err(AQ_CFG_DRV_NAME ": " __VA_ARGS__)
#घोषणा aq_pr_trace(...) pr_info(AQ_CFG_DRV_NAME ": " __VA_ARGS__)

काष्ठा aq_hw_s;

व्योम aq_hw_ग_लिखो_reg_bit(काष्ठा aq_hw_s *aq_hw, u32 addr, u32 msk,
			 u32 shअगरt, u32 val);
u32 aq_hw_पढ़ो_reg_bit(काष्ठा aq_hw_s *aq_hw, u32 addr, u32 msk, u32 shअगरt);
u32 aq_hw_पढ़ो_reg(काष्ठा aq_hw_s *hw, u32 reg);
व्योम aq_hw_ग_लिखो_reg(काष्ठा aq_hw_s *hw, u32 reg, u32 value);
u64 aq_hw_पढ़ो_reg64(काष्ठा aq_hw_s *hw, u32 reg);
व्योम aq_hw_ग_लिखो_reg64(काष्ठा aq_hw_s *hw, u32 reg, u64 value);
पूर्णांक aq_hw_err_from_flags(काष्ठा aq_hw_s *hw);
पूर्णांक aq_hw_num_tcs(काष्ठा aq_hw_s *hw);
पूर्णांक aq_hw_q_per_tc(काष्ठा aq_hw_s *hw);

#पूर्ण_अगर /* AQ_HW_UTILS_H */
