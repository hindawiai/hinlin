<शैली गुरु>
#अगर_अघोषित __GPIO_ASPEED_H
#घोषणा __GPIO_ASPEED_H

काष्ठा aspeed_gpio_copro_ops अणु
	पूर्णांक (*request_access)(व्योम *data);
	पूर्णांक (*release_access)(व्योम *data);
पूर्ण;

पूर्णांक aspeed_gpio_copro_grab_gpio(काष्ठा gpio_desc *desc,
				u16 *vreg_offset, u16 *dreg_offset, u8 *bit);
पूर्णांक aspeed_gpio_copro_release_gpio(काष्ठा gpio_desc *desc);
पूर्णांक aspeed_gpio_copro_set_ops(स्थिर काष्ठा aspeed_gpio_copro_ops *ops, व्योम *data);


#पूर्ण_अगर /* __GPIO_ASPEED_H */
