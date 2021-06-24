<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * board initialization should put one of these पूर्णांकo dev->platक्रमm_data
 * and place the isp1760 onto platक्रमm_bus named "isp1760-hcd".
 */

#अगर_अघोषित __LINUX_USB_ISP1760_H
#घोषणा __LINUX_USB_ISP1760_H

काष्ठा isp1760_platक्रमm_data अणु
	अचिन्हित is_isp1761:1;			/* Chip is ISP1761 */
	अचिन्हित bus_width_16:1;		/* 16/32-bit data bus width */
	अचिन्हित port1_otg:1;			/* Port 1 supports OTG */
	अचिन्हित analog_oc:1;			/* Analog overcurrent */
	अचिन्हित dack_polarity_high:1;		/* DACK active high */
	अचिन्हित dreq_polarity_high:1;		/* DREQ active high */
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_ISP1760_H */
