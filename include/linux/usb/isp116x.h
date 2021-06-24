<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Board initialization code should put one of these पूर्णांकo dev->platक्रमm_data
 * and place the isp116x onto platक्रमm_bus.
 */

#अगर_अघोषित __LINUX_USB_ISP116X_H
#घोषणा __LINUX_USB_ISP116X_H

काष्ठा isp116x_platक्रमm_data अणु
	/* Enable पूर्णांकernal resistors on करोwnstream ports */
	अचिन्हित sel15Kres:1;
	/* On-chip overcurrent detection */
	अचिन्हित oc_enable:1;
	/* INT output polarity */
	अचिन्हित पूर्णांक_act_high:1;
	/* INT edge or level triggered */
	अचिन्हित पूर्णांक_edge_triggered:1;
	/* Enable wakeup by devices on usb bus (e.g. wakeup
	   by attachment/detachment or by device activity
	   such as moving a mouse). When chosen, this option
	   prevents stopping पूर्णांकernal घड़ी, increasing
	   thereby घातer consumption in suspended state. */
	अचिन्हित remote_wakeup_enable:1;
	/* Inter-io delay (ns). The chip is picky about access timings; it
	   expects at least:
	   150ns delay between consecutive accesses to DATA_REG,
	   300ns delay between access to ADDR_REG and DATA_REG
	   OE, WE MUST NOT be changed during these पूर्णांकervals
	 */
	व्योम (*delay) (काष्ठा device *dev, पूर्णांक delay);
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_ISP116X_H */
