<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SOC_EP93XX_H
#घोषणा _SOC_EP93XX_H

काष्ठा platक्रमm_device;

#घोषणा EP93XX_CHIP_REV_D0	3
#घोषणा EP93XX_CHIP_REV_D1	4
#घोषणा EP93XX_CHIP_REV_E0	5
#घोषणा EP93XX_CHIP_REV_E1	6
#घोषणा EP93XX_CHIP_REV_E2	7

#अगर_घोषित CONFIG_ARCH_EP93XX
पूर्णांक ep93xx_pwm_acquire_gpio(काष्ठा platक्रमm_device *pdev);
व्योम ep93xx_pwm_release_gpio(काष्ठा platक्रमm_device *pdev);
पूर्णांक ep93xx_ide_acquire_gpio(काष्ठा platक्रमm_device *pdev);
व्योम ep93xx_ide_release_gpio(काष्ठा platक्रमm_device *pdev);
पूर्णांक ep93xx_keypad_acquire_gpio(काष्ठा platक्रमm_device *pdev);
व्योम ep93xx_keypad_release_gpio(काष्ठा platक्रमm_device *pdev);
पूर्णांक ep93xx_i2s_acquire(व्योम);
व्योम ep93xx_i2s_release(व्योम);
अचिन्हित पूर्णांक ep93xx_chip_revision(व्योम);

#अन्यथा
अटल अंतरभूत पूर्णांक ep93xx_pwm_acquire_gpio(काष्ठा platक्रमm_device *pdev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ep93xx_pwm_release_gpio(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक ep93xx_ide_acquire_gpio(काष्ठा platक्रमm_device *pdev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ep93xx_ide_release_gpio(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक ep93xx_keypad_acquire_gpio(काष्ठा platक्रमm_device *pdev) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ep93xx_keypad_release_gpio(काष्ठा platक्रमm_device *pdev) अणुपूर्ण
अटल अंतरभूत पूर्णांक ep93xx_i2s_acquire(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ep93xx_i2s_release(व्योम) अणुपूर्ण
अटल अंतरभूत अचिन्हित पूर्णांक ep93xx_chip_revision(व्योम) अणु वापस 0; पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
