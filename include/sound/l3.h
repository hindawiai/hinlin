<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _L3_H_
#घोषणा _L3_H_ 1

काष्ठा l3_pins अणु
	व्योम (*setdat)(काष्ठा l3_pins *, पूर्णांक);
	व्योम (*setclk)(काष्ठा l3_pins *, पूर्णांक);
	व्योम (*seपंचांगode)(काष्ठा l3_pins *, पूर्णांक);

	पूर्णांक gpio_data;
	पूर्णांक gpio_clk;
	पूर्णांक gpio_mode;
	पूर्णांक use_gpios;

	पूर्णांक data_hold;
	पूर्णांक data_setup;
	पूर्णांक घड़ी_high;
	पूर्णांक mode_hold;
	पूर्णांक mode;
	पूर्णांक mode_setup;
पूर्ण;

काष्ठा device;

पूर्णांक l3_ग_लिखो(काष्ठा l3_pins *adap, u8 addr, u8 *data, पूर्णांक len);
पूर्णांक l3_set_gpio_ops(काष्ठा device *dev, काष्ठा l3_pins *adap);

#पूर्ण_अगर
