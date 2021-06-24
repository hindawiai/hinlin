<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
//
// Actions Semi Owl SoCs Reset Management Unit driver
//
// Copyright (c) 2018 Linaro Ltd.
// Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>

#अगर_अघोषित _OWL_RESET_H_
#घोषणा _OWL_RESET_H_

#समावेश <linux/reset-controller.h>

काष्ठा owl_reset_map अणु
	u32	reg;
	u32	bit;
पूर्ण;

काष्ठा owl_reset अणु
	काष्ठा reset_controller_dev	rcdev;
	स्थिर काष्ठा owl_reset_map	*reset_map;
	काष्ठा regmap			*regmap;
पूर्ण;

अटल अंतरभूत काष्ठा owl_reset *to_owl_reset(काष्ठा reset_controller_dev *rcdev)
अणु
	वापस container_of(rcdev, काष्ठा owl_reset, rcdev);
पूर्ण

बाह्य स्थिर काष्ठा reset_control_ops owl_reset_ops;

#पूर्ण_अगर /* _OWL_RESET_H_ */
