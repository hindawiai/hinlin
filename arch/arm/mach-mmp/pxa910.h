<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_PXA910_H
#घोषणा __ASM_MACH_PXA910_H

बाह्य व्योम pxa910_समयr_init(व्योम);
बाह्य व्योम __init icu_init_irq(व्योम);
बाह्य व्योम __init pxa910_init_irq(व्योम);

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>
#समावेश <video/mmp_disp.h>

#समावेश "devices.h"

बाह्य काष्ठा pxa_device_desc pxa910_device_uart1;
बाह्य काष्ठा pxa_device_desc pxa910_device_uart2;
बाह्य काष्ठा pxa_device_desc pxa910_device_twsi0;
बाह्य काष्ठा pxa_device_desc pxa910_device_twsi1;
बाह्य काष्ठा pxa_device_desc pxa910_device_pwm1;
बाह्य काष्ठा pxa_device_desc pxa910_device_pwm2;
बाह्य काष्ठा pxa_device_desc pxa910_device_pwm3;
बाह्य काष्ठा pxa_device_desc pxa910_device_pwm4;
बाह्य काष्ठा pxa_device_desc pxa910_device_nand;
बाह्य काष्ठा platक्रमm_device pxa168_device_usb_phy;
बाह्य काष्ठा platक्रमm_device pxa168_device_u2o;
बाह्य काष्ठा platक्रमm_device pxa168_device_u2ootg;
बाह्य काष्ठा platक्रमm_device pxa168_device_u2oehci;
बाह्य काष्ठा pxa_device_desc pxa910_device_disp;
बाह्य काष्ठा pxa_device_desc pxa910_device_fb;
बाह्य काष्ठा pxa_device_desc pxa910_device_panel;
बाह्य काष्ठा platक्रमm_device pxa910_device_gpio;
बाह्य काष्ठा platक्रमm_device pxa910_device_rtc;

अटल अंतरभूत पूर्णांक pxa910_add_uart(पूर्णांक id)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 1: d = &pxa910_device_uart1; अवरोध;
	हाल 2: d = &pxa910_device_uart2; अवरोध;
	पूर्ण

	अगर (d == शून्य)
		वापस -EINVAL;

	वापस pxa_रेजिस्टर_device(d, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pxa910_add_twsi(पूर्णांक id, काष्ठा i2c_pxa_platक्रमm_data *data,
				  काष्ठा i2c_board_info *info, अचिन्हित size)
अणु
	काष्ठा pxa_device_desc *d = शून्य;
	पूर्णांक ret;

	चयन (id) अणु
	हाल 0: d = &pxa910_device_twsi0; अवरोध;
	हाल 1: d = &pxa910_device_twsi1; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = i2c_रेजिस्टर_board_info(id, info, size);
	अगर (ret)
		वापस ret;

	वापस pxa_रेजिस्टर_device(d, data, माप(*data));
पूर्ण

अटल अंतरभूत पूर्णांक pxa910_add_pwm(पूर्णांक id)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 1: d = &pxa910_device_pwm1; अवरोध;
	हाल 2: d = &pxa910_device_pwm2; अवरोध;
	हाल 3: d = &pxa910_device_pwm3; अवरोध;
	हाल 4: d = &pxa910_device_pwm4; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pxa_रेजिस्टर_device(d, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pxa910_add_nand(काष्ठा pxa3xx_nand_platक्रमm_data *info)
अणु
	वापस pxa_रेजिस्टर_device(&pxa910_device_nand, info, माप(*info));
पूर्ण
#पूर्ण_अगर /* __ASM_MACH_PXA910_H */
