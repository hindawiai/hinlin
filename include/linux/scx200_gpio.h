<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
u32 scx200_gpio_configure(अचिन्हित index, u32 set, u32 clear);

बाह्य अचिन्हित scx200_gpio_base;
बाह्य अचिन्हित दीर्घ scx200_gpio_shaकरोw[2];
बाह्य काष्ठा nsc_gpio_ops scx200_gpio_ops;

#घोषणा scx200_gpio_present() (scx200_gpio_base!=0)

/* Definitions to make sure I करो the same thing in all functions */
#घोषणा __SCx200_GPIO_BANK अचिन्हित bank = index>>5
#घोषणा __SCx200_GPIO_IOADDR अचिन्हित लघु ioaddr = scx200_gpio_base+0x10*bank
#घोषणा __SCx200_GPIO_SHADOW अचिन्हित दीर्घ *shaकरोw = scx200_gpio_shaकरोw+bank
#घोषणा __SCx200_GPIO_INDEX index &= 31

#घोषणा __SCx200_GPIO_OUT __यंत्र__ __अस्थिर__("outsl":"=mS" (shaकरोw):"d" (ioaddr), "0" (shaकरोw))

/* वापसs the value of the GPIO pin */

अटल अंतरभूत पूर्णांक scx200_gpio_get(अचिन्हित index) अणु
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDR + 0x04;
	__SCx200_GPIO_INDEX;
		
	वापस (inl(ioaddr) & (1<<index)) ? 1 : 0;
पूर्ण

/* वापस the value driven on the GPIO संकेत (the value that will be
   driven अगर the GPIO is configured as an output, it might not be the
   state of the GPIO right now अगर the GPIO is configured as an input) */

अटल अंतरभूत पूर्णांक scx200_gpio_current(अचिन्हित index) अणु
        __SCx200_GPIO_BANK;
	__SCx200_GPIO_INDEX;
		
	वापस (scx200_gpio_shaकरोw[bank] & (1<<index)) ? 1 : 0;
पूर्ण

/* drive the GPIO संकेत high */

अटल अंतरभूत व्योम scx200_gpio_set_high(अचिन्हित index) अणु
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDR;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	set_bit(index, shaकरोw);	/* __set_bit()? */
	__SCx200_GPIO_OUT;
पूर्ण

/* drive the GPIO संकेत low */

अटल अंतरभूत व्योम scx200_gpio_set_low(अचिन्हित index) अणु
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDR;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	clear_bit(index, shaकरोw); /* __clear_bit()? */
	__SCx200_GPIO_OUT;
पूर्ण

/* drive the GPIO संकेत to state */

अटल अंतरभूत व्योम scx200_gpio_set(अचिन्हित index, पूर्णांक state) अणु
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDR;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	अगर (state)
		set_bit(index, shaकरोw);
	अन्यथा
		clear_bit(index, shaकरोw);
	__SCx200_GPIO_OUT;
पूर्ण

/* toggle the GPIO संकेत */
अटल अंतरभूत व्योम scx200_gpio_change(अचिन्हित index) अणु
	__SCx200_GPIO_BANK;
	__SCx200_GPIO_IOADDR;
	__SCx200_GPIO_SHADOW;
	__SCx200_GPIO_INDEX;
	change_bit(index, shaकरोw);
	__SCx200_GPIO_OUT;
पूर्ण

#अघोषित __SCx200_GPIO_BANK
#अघोषित __SCx200_GPIO_IOADDR
#अघोषित __SCx200_GPIO_SHADOW
#अघोषित __SCx200_GPIO_INDEX
#अघोषित __SCx200_GPIO_OUT
