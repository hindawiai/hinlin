<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Copyright (c) 2017 Dialog Semiconductor
 *
 * Author: Adam Thomson <Adam.Thomson.Opensource@diasemi.com>
 */

#अगर_अघोषित __LINUX_USB_PD_ADO_H
#घोषणा __LINUX_USB_PD_ADO_H

/* ADO : Alert Data Object */
#घोषणा USB_PD_ADO_TYPE_SHIFT			24
#घोषणा USB_PD_ADO_TYPE_MASK			0xff
#घोषणा USB_PD_ADO_FIXED_BATT_SHIFT		20
#घोषणा USB_PD_ADO_FIXED_BATT_MASK		0xf
#घोषणा USB_PD_ADO_HOT_SWAP_BATT_SHIFT		16
#घोषणा USB_PD_ADO_HOT_SWAP_BATT_MASK		0xf

#घोषणा USB_PD_ADO_TYPE_BATT_STATUS_CHANGE	BIT(1)
#घोषणा USB_PD_ADO_TYPE_OCP			BIT(2)
#घोषणा USB_PD_ADO_TYPE_OTP			BIT(3)
#घोषणा USB_PD_ADO_TYPE_OP_COND_CHANGE		BIT(4)
#घोषणा USB_PD_ADO_TYPE_SRC_INPUT_CHANGE	BIT(5)
#घोषणा USB_PD_ADO_TYPE_OVP			BIT(6)

अटल अंतरभूत अचिन्हित पूर्णांक usb_pd_aकरो_type(u32 aकरो)
अणु
	वापस (aकरो >> USB_PD_ADO_TYPE_SHIFT) & USB_PD_ADO_TYPE_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक usb_pd_aकरो_fixed_batt(u32 aकरो)
अणु
	वापस (aकरो >> USB_PD_ADO_FIXED_BATT_SHIFT) &
	       USB_PD_ADO_FIXED_BATT_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक usb_pd_aकरो_hot_swap_batt(u32 aकरो)
अणु
	वापस (aकरो >> USB_PD_ADO_HOT_SWAP_BATT_SHIFT) &
	       USB_PD_ADO_HOT_SWAP_BATT_MASK;
पूर्ण
#पूर्ण_अगर /* __LINUX_USB_PD_ADO_H */
