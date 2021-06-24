<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * board initialization code should put one of these पूर्णांकo dev->platक्रमm_data
 * and place the isp1362 onto platक्रमm_bus.
 */

#अगर_अघोषित __LINUX_USB_ISP1362_H__
#घोषणा __LINUX_USB_ISP1362_H__

काष्ठा isp1362_platक्रमm_data अणु
	/* Enable पूर्णांकernal pullकरोwn resistors on करोwnstream ports */
	अचिन्हित sel15Kres:1;
	/* Clock cannot be stopped */
	अचिन्हित clknotstop:1;
	/* On-chip overcurrent protection */
	अचिन्हित oc_enable:1;
	/* INT output polarity */
	अचिन्हित पूर्णांक_act_high:1;
	/* INT edge or level triggered */
	अचिन्हित पूर्णांक_edge_triggered:1;
	/* DREQ output polarity */
	अचिन्हित dreq_act_high:1;
	/* DACK input polarity */
	अचिन्हित dack_act_high:1;
	/* chip can be resumed via H_WAKEUP pin */
	अचिन्हित remote_wakeup_connected:1;
	/* Switch or not to चयन (keep always घातered) */
	अचिन्हित no_घातer_चयनing:1;
	/* Ganged port घातer चयनing (0) or inभागidual port घातer चयनing (1) */
	अचिन्हित घातer_चयनing_mode:1;
	/* Given port_घातer, msec/2 after घातer on till घातer good */
	u8 potpg;
	/* Hardware reset set/clear */
	व्योम (*reset) (काष्ठा device *dev, पूर्णांक set);
	/* Clock start/stop */
	व्योम (*घड़ी) (काष्ठा device *dev, पूर्णांक start);
	/* Inter-io delay (ns). The chip is picky about access timings; it
	 * expects at least:
	 * 110ns delay between consecutive accesses to DATA_REG,
	 * 300ns delay between access to ADDR_REG and DATA_REG (रेजिस्टरs)
	 * 462ns delay between access to ADDR_REG and DATA_REG (buffer memory)
	 * WE MUST NOT be activated during these पूर्णांकervals (even without CS!)
	 */
	व्योम (*delay) (काष्ठा device *dev, अचिन्हित पूर्णांक delay);
पूर्ण;

#पूर्ण_अगर
