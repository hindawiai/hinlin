<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2016 Freescale Semiconductor, Inc.
 * Copyright 2017~2018 NXP
 *
 * Header file containing the खुला System Controller Interface (SCI)
 * definitions.
 */

#अगर_अघोषित _SC_SCI_H
#घोषणा _SC_SCI_H

#समावेश <linux/firmware/imx/ipc.h>

#समावेश <linux/firmware/imx/svc/misc.h>
#समावेश <linux/firmware/imx/svc/pm.h>
#समावेश <linux/firmware/imx/svc/rm.h>

#अगर IS_ENABLED(CONFIG_IMX_SCU)
पूर्णांक imx_scu_enable_general_irq_channel(काष्ठा device *dev);
पूर्णांक imx_scu_irq_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक imx_scu_irq_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb);
पूर्णांक imx_scu_irq_group_enable(u8 group, u32 mask, u8 enable);
पूर्णांक imx_scu_soc_init(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक imx_scu_soc_init(काष्ठा device *dev)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_scu_enable_general_irq_channel(काष्ठा device *dev)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_scu_irq_रेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_scu_irq_unरेजिस्टर_notअगरier(काष्ठा notअगरier_block *nb)
अणु
	वापस -ENOTSUPP;
पूर्ण

अटल अंतरभूत पूर्णांक imx_scu_irq_group_enable(u8 group, u32 mask, u8 enable)
अणु
	वापस -ENOTSUPP;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _SC_SCI_H */
