<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */

#अगर_अघोषित _LINUX_GPIO_REGMAP_H
#घोषणा _LINUX_GPIO_REGMAP_H

काष्ठा device;
काष्ठा fwnode_handle;
काष्ठा gpio_regmap;
काष्ठा irq_करोमुख्य;
काष्ठा regmap;

#घोषणा GPIO_REGMAP_ADDR_ZERO ((अचिन्हित पूर्णांक)(-1))
#घोषणा GPIO_REGMAP_ADDR(addr) ((addr) ? : GPIO_REGMAP_ADDR_ZERO)

/**
 * काष्ठा gpio_regmap_config - Description of a generic regmap gpio_chip.
 * @parent:		The parent device
 * @regmap:		The regmap used to access the रेजिस्टरs
 *			given, the name of the device is used
 * @fwnode:		(Optional) The firmware node.
 *			If not given, the fwnode of the parent is used.
 * @label:		(Optional) Descriptive name क्रम GPIO controller.
 *			If not given, the name of the device is used.
 * @ngpio:		Number of GPIOs
 * @names:		(Optional) Array of names क्रम gpios
 * @reg_dat_base:	(Optional) (in) रेजिस्टर base address
 * @reg_set_base:	(Optional) set रेजिस्टर base address
 * @reg_clr_base:	(Optional) clear रेजिस्टर base address
 * @reg_dir_in_base:	(Optional) in setting रेजिस्टर base address
 * @reg_dir_out_base:	(Optional) out setting रेजिस्टर base address
 * @reg_stride:		(Optional) May be set अगर the रेजिस्टरs (of the
 *			same type, dat, set, etc) are not consecutive.
 * @ngpio_per_reg:	Number of GPIOs per रेजिस्टर
 * @irq_करोमुख्य:		(Optional) IRQ करोमुख्य अगर the controller is
 *			पूर्णांकerrupt-capable
 * @reg_mask_xlate:     (Optional) Translates base address and GPIO
 *			offset to a रेजिस्टर/biपंचांगask pair. If not
 *			given the शेष gpio_regmap_simple_xlate()
 *			is used.
 *
 * The ->reg_mask_xlate translates a given base address and GPIO offset to
 * रेजिस्टर and mask pair. The base address is one of the given रेजिस्टर
 * base addresses in this काष्ठाure.
 *
 * Although all रेजिस्टर base addresses are marked as optional, there are
 * several rules:
 *     1. अगर you only have @reg_dat_base set, then it is input-only
 *     2. अगर you only have @reg_set_base set, then it is output-only
 *     3. अगर you have either @reg_dir_in_base or @reg_dir_out_base set, then
 *        you have to set both @reg_dat_base and @reg_set_base
 *     4. अगर you have @reg_set_base set, you may also set @reg_clr_base to have
 *        two dअगरferent रेजिस्टरs क्रम setting and clearing the output. This is
 *        also valid क्रम the output-only हाल.
 *     5. @reg_dir_in_base and @reg_dir_out_base are exclusive; is there really
 *        hardware which has redundant रेजिस्टरs?
 *
 * Note: All base addresses may have the special value %GPIO_REGMAP_ADDR_ZERO
 * which क्रमces the address to the value 0.
 */
काष्ठा gpio_regmap_config अणु
	काष्ठा device *parent;
	काष्ठा regmap *regmap;
	काष्ठा fwnode_handle *fwnode;

	स्थिर अक्षर *label;
	पूर्णांक ngpio;
	स्थिर अक्षर *स्थिर *names;

	अचिन्हित पूर्णांक reg_dat_base;
	अचिन्हित पूर्णांक reg_set_base;
	अचिन्हित पूर्णांक reg_clr_base;
	अचिन्हित पूर्णांक reg_dir_in_base;
	अचिन्हित पूर्णांक reg_dir_out_base;
	पूर्णांक reg_stride;
	पूर्णांक ngpio_per_reg;
	काष्ठा irq_करोमुख्य *irq_करोमुख्य;

	पूर्णांक (*reg_mask_xlate)(काष्ठा gpio_regmap *gpio, अचिन्हित पूर्णांक base,
			      अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक *reg,
			      अचिन्हित पूर्णांक *mask);
पूर्ण;

काष्ठा gpio_regmap *gpio_regmap_रेजिस्टर(स्थिर काष्ठा gpio_regmap_config *config);
व्योम gpio_regmap_unरेजिस्टर(काष्ठा gpio_regmap *gpio);
काष्ठा gpio_regmap *devm_gpio_regmap_रेजिस्टर(काष्ठा device *dev,
					      स्थिर काष्ठा gpio_regmap_config *config);
व्योम gpio_regmap_set_drvdata(काष्ठा gpio_regmap *gpio, व्योम *data);
व्योम *gpio_regmap_get_drvdata(काष्ठा gpio_regmap *gpio);

#पूर्ण_अगर /* _LINUX_GPIO_REGMAP_H */
