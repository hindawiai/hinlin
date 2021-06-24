<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SPI_MAX7301_H
#घोषणा LINUX_SPI_MAX7301_H

#समावेश <linux/gpपन.स>

/*
 * Some रेजिस्टरs must be पढ़ो back to modअगरy.
 * To save समय we cache them here in memory
 */
काष्ठा max7301 अणु
	काष्ठा mutex	lock;
	u8		port_config[8];	/* field 0 is unused */
	u32		out_level;	/* cached output levels */
	u32		input_pullup_active;
	काष्ठा gpio_chip chip;
	काष्ठा device *dev;
	पूर्णांक (*ग_लिखो)(काष्ठा device *dev, अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val);
	पूर्णांक (*पढ़ो)(काष्ठा device *dev, अचिन्हित पूर्णांक reg);
पूर्ण;

काष्ठा max7301_platक्रमm_data अणु
	/* number asचिन्हित to the first GPIO */
	अचिन्हित	base;
	/*
	 * biपंचांगask controlling the pullup configuration,
	 *
	 * _note_ the 4 lowest bits are unused, because the first 4
	 * ports of the controller are not used, too.
	 */
	u32		input_pullup_active;
पूर्ण;

बाह्य पूर्णांक __max730x_हटाओ(काष्ठा device *dev);
बाह्य पूर्णांक __max730x_probe(काष्ठा max7301 *ts);
#पूर्ण_अगर
