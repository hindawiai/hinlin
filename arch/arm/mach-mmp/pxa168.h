<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MACH_PXA168_H
#घोषणा __ASM_MACH_PXA168_H

#समावेश <linux/reboot.h>

बाह्य व्योम pxa168_समयr_init(व्योम);
बाह्य व्योम __init icu_init_irq(व्योम);
बाह्य व्योम __init pxa168_init_irq(व्योम);
बाह्य व्योम pxa168_restart(क्रमागत reboot_mode, स्थिर अक्षर *);
बाह्य व्योम pxa168_clear_keypad_wakeup(व्योम);

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>
#समावेश <video/pxa168fb.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश <linux/pxa168_eth.h>
#समावेश <linux/platक्रमm_data/mv_usb.h>
#समावेश <linux/soc/mmp/cputype.h>

#समावेश "devices.h"

बाह्य काष्ठा pxa_device_desc pxa168_device_uart1;
बाह्य काष्ठा pxa_device_desc pxa168_device_uart2;
बाह्य काष्ठा pxa_device_desc pxa168_device_uart3;
बाह्य काष्ठा pxa_device_desc pxa168_device_twsi0;
बाह्य काष्ठा pxa_device_desc pxa168_device_twsi1;
बाह्य काष्ठा pxa_device_desc pxa168_device_pwm1;
बाह्य काष्ठा pxa_device_desc pxa168_device_pwm2;
बाह्य काष्ठा pxa_device_desc pxa168_device_pwm3;
बाह्य काष्ठा pxa_device_desc pxa168_device_pwm4;
बाह्य काष्ठा pxa_device_desc pxa168_device_ssp1;
बाह्य काष्ठा pxa_device_desc pxa168_device_ssp2;
बाह्य काष्ठा pxa_device_desc pxa168_device_ssp3;
बाह्य काष्ठा pxa_device_desc pxa168_device_ssp4;
बाह्य काष्ठा pxa_device_desc pxa168_device_ssp5;
बाह्य काष्ठा pxa_device_desc pxa168_device_nand;
बाह्य काष्ठा pxa_device_desc pxa168_device_fb;
बाह्य काष्ठा pxa_device_desc pxa168_device_keypad;
बाह्य काष्ठा pxa_device_desc pxa168_device_eth;

/* pdata can be शून्य */
बाह्य पूर्णांक __init pxa168_add_usb_host(काष्ठा mv_usb_platक्रमm_data *pdata);


बाह्य काष्ठा platक्रमm_device pxa168_device_gpio;

अटल अंतरभूत पूर्णांक pxa168_add_uart(पूर्णांक id)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 1: d = &pxa168_device_uart1; अवरोध;
	हाल 2: d = &pxa168_device_uart2; अवरोध;
	हाल 3: d = &pxa168_device_uart3; अवरोध;
	पूर्ण

	अगर (d == शून्य)
		वापस -EINVAL;

	वापस pxa_रेजिस्टर_device(d, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_twsi(पूर्णांक id, काष्ठा i2c_pxa_platक्रमm_data *data,
				  काष्ठा i2c_board_info *info, अचिन्हित size)
अणु
	काष्ठा pxa_device_desc *d = शून्य;
	पूर्णांक ret;

	चयन (id) अणु
	हाल 0: d = &pxa168_device_twsi0; अवरोध;
	हाल 1: d = &pxa168_device_twsi1; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = i2c_रेजिस्टर_board_info(id, info, size);
	अगर (ret)
		वापस ret;

	वापस pxa_रेजिस्टर_device(d, data, माप(*data));
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_pwm(पूर्णांक id)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 1: d = &pxa168_device_pwm1; अवरोध;
	हाल 2: d = &pxa168_device_pwm2; अवरोध;
	हाल 3: d = &pxa168_device_pwm3; अवरोध;
	हाल 4: d = &pxa168_device_pwm4; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस pxa_रेजिस्टर_device(d, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_ssp(पूर्णांक id)
अणु
	काष्ठा pxa_device_desc *d = शून्य;

	चयन (id) अणु
	हाल 1: d = &pxa168_device_ssp1; अवरोध;
	हाल 2: d = &pxa168_device_ssp2; अवरोध;
	हाल 3: d = &pxa168_device_ssp3; अवरोध;
	हाल 4: d = &pxa168_device_ssp4; अवरोध;
	हाल 5: d = &pxa168_device_ssp5; अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस pxa_रेजिस्टर_device(d, शून्य, 0);
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_nand(काष्ठा pxa3xx_nand_platक्रमm_data *info)
अणु
	वापस pxa_रेजिस्टर_device(&pxa168_device_nand, info, माप(*info));
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_fb(काष्ठा pxa168fb_mach_info *mi)
अणु
	वापस pxa_रेजिस्टर_device(&pxa168_device_fb, mi, माप(*mi));
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_keypad(काष्ठा pxa27x_keypad_platक्रमm_data *data)
अणु
	अगर (cpu_is_pxa168())
		data->clear_wakeup_event = pxa168_clear_keypad_wakeup;

	वापस pxa_रेजिस्टर_device(&pxa168_device_keypad, data, माप(*data));
पूर्ण

अटल अंतरभूत पूर्णांक pxa168_add_eth(काष्ठा pxa168_eth_platक्रमm_data *data)
अणु
	वापस pxa_रेजिस्टर_device(&pxa168_device_eth, data, माप(*data));
पूर्ण
#पूर्ण_अगर /* __ASM_MACH_PXA168_H */
