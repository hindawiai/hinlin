<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* drivers/media/platक्रमm/s5p-cec/exynos_hdmi_cec.h
 *
 * Copyright (c) 2010, 2014 Samsung Electronics
 *		http://www.samsung.com/
 *
 * Header file क्रम पूर्णांकerface of Samsung Exynos hdmi cec hardware
 */

#अगर_अघोषित _EXYNOS_HDMI_CEC_H_
#घोषणा _EXYNOS_HDMI_CEC_H_ __खाता__

#समावेश <linux/regmap.h>
#समावेश "s5p_cec.h"

व्योम s5p_cec_set_भागider(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_enable_rx(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_mask_rx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_unmask_rx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_mask_tx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_unmask_tx_पूर्णांकerrupts(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_reset(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_tx_reset(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_rx_reset(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_threshold(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_copy_packet(काष्ठा s5p_cec_dev *cec, अक्षर *data,
			 माप_प्रकार count, u8 retries);
व्योम s5p_cec_set_addr(काष्ठा s5p_cec_dev *cec, u32 addr);
u32 s5p_cec_get_status(काष्ठा s5p_cec_dev *cec);
व्योम s5p_clr_pending_tx(काष्ठा s5p_cec_dev *cec);
व्योम s5p_clr_pending_rx(काष्ठा s5p_cec_dev *cec);
व्योम s5p_cec_get_rx_buf(काष्ठा s5p_cec_dev *cec, u32 size, u8 *buffer);

#पूर्ण_अगर /* _EXYNOS_HDMI_CEC_H_ */
