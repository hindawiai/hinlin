<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित GPIOLIB_OF_H
#घोषणा GPIOLIB_OF_H

काष्ठा gpio_chip;
क्रमागत of_gpio_flags;

#अगर_घोषित CONFIG_OF_GPIO
काष्ठा gpio_desc *of_find_gpio(काष्ठा device *dev,
			       स्थिर अक्षर *con_id,
			       अचिन्हित पूर्णांक idx,
			       अचिन्हित दीर्घ *lookupflags);
पूर्णांक of_gpiochip_add(काष्ठा gpio_chip *gc);
व्योम of_gpiochip_हटाओ(काष्ठा gpio_chip *gc);
पूर्णांक of_gpio_get_count(काष्ठा device *dev, स्थिर अक्षर *con_id);
bool of_gpio_need_valid_mask(स्थिर काष्ठा gpio_chip *gc);
व्योम of_gpio_dev_init(काष्ठा gpio_chip *gc, काष्ठा gpio_device *gdev);
#अन्यथा
अटल अंतरभूत काष्ठा gpio_desc *of_find_gpio(काष्ठा device *dev,
					     स्थिर अक्षर *con_id,
					     अचिन्हित पूर्णांक idx,
					     अचिन्हित दीर्घ *lookupflags)
अणु
	वापस ERR_PTR(-ENOENT);
पूर्ण
अटल अंतरभूत पूर्णांक of_gpiochip_add(काष्ठा gpio_chip *gc) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम of_gpiochip_हटाओ(काष्ठा gpio_chip *gc) अणु पूर्ण
अटल अंतरभूत पूर्णांक of_gpio_get_count(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत bool of_gpio_need_valid_mask(स्थिर काष्ठा gpio_chip *gc)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम of_gpio_dev_init(काष्ठा gpio_chip *gc,
				    काष्ठा gpio_device *gdev)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_OF_GPIO */

बाह्य काष्ठा notअगरier_block gpio_of_notअगरier;

#पूर्ण_अगर /* GPIOLIB_OF_H */
