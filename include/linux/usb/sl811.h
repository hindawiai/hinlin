<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * board initialization should put one of these पूर्णांकo dev->platक्रमm_data
 * and place the sl811hs onto platक्रमm_bus named "sl811-hcd".
 */

#अगर_अघोषित __LINUX_USB_SL811_H
#घोषणा __LINUX_USB_SL811_H

काष्ठा sl811_platक्रमm_data अणु
	अचिन्हित	can_wakeup:1;

	/* given port_घातer, msec/2 after घातer on till घातer good */
	u8		potpg;

	/* mA/2 घातer supplied on this port (max = शेष = 250) */
	u8		घातer;

	/* sl811 relies on an बाह्यal source of VBUS current */
	व्योम		(*port_घातer)(काष्ठा device *dev, पूर्णांक is_on);

	/* pulse sl811 nRST (probably with a GPIO) */
	व्योम		(*reset)(काष्ठा device *dev);

	/* some boards need something like these: */
	/* पूर्णांक		(*check_overcurrent)(काष्ठा device *dev); */
	/* व्योम		(*घड़ी_enable)(काष्ठा device *dev, पूर्णांक is_on); */
पूर्ण;

#पूर्ण_अगर /* __LINUX_USB_SL811_H */
