<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-ep93xx/include/mach/platक्रमm.h
 */

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/platक्रमm_data/eth-ep93xx.h>
#समावेश <linux/reboot.h>

काष्ठा device;
काष्ठा i2c_board_info;
काष्ठा spi_board_info;
काष्ठा platक्रमm_device;
काष्ठा ep93xxfb_mach_info;
काष्ठा ep93xx_keypad_platक्रमm_data;
काष्ठा ep93xx_spi_info;

व्योम ep93xx_map_io(व्योम);
व्योम ep93xx_init_irq(व्योम);

व्योम ep93xx_रेजिस्टर_flash(अचिन्हित पूर्णांक width,
			   resource_माप_प्रकार start, resource_माप_प्रकार size);

व्योम ep93xx_रेजिस्टर_eth(काष्ठा ep93xx_eth_data *data, पूर्णांक copy_addr);
व्योम ep93xx_रेजिस्टर_i2c(काष्ठा i2c_board_info *devices, पूर्णांक num);
व्योम ep93xx_रेजिस्टर_spi(काष्ठा ep93xx_spi_info *info,
			 काष्ठा spi_board_info *devices, पूर्णांक num);
व्योम ep93xx_रेजिस्टर_fb(काष्ठा ep93xxfb_mach_info *data);
व्योम ep93xx_रेजिस्टर_pwm(पूर्णांक pwm0, पूर्णांक pwm1);
व्योम ep93xx_रेजिस्टर_keypad(काष्ठा ep93xx_keypad_platक्रमm_data *data);
व्योम ep93xx_रेजिस्टर_i2s(व्योम);
व्योम ep93xx_रेजिस्टर_ac97(व्योम);
व्योम ep93xx_रेजिस्टर_ide(व्योम);
व्योम ep93xx_रेजिस्टर_adc(व्योम);

काष्ठा device *ep93xx_init_devices(व्योम);
बाह्य व्योम ep93xx_समयr_init(व्योम);

व्योम ep93xx_restart(क्रमागत reboot_mode, स्थिर अक्षर *);
व्योम ep93xx_init_late(व्योम);

#अगर_घोषित CONFIG_CRUNCH
पूर्णांक crunch_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक crunch_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
