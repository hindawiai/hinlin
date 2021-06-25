<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Core pinctrl/GPIO driver क्रम Intel GPIO controllers
 *
 * Copyright (C) 2015, Intel Corporation
 * Authors: Mathias Nyman <mathias.nyman@linux.पूर्णांकel.com>
 *          Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#अगर_अघोषित PINCTRL_INTEL_H
#घोषणा PINCTRL_INTEL_H

#समावेश <linux/bits.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pm.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/spinlock_types.h>

काष्ठा platक्रमm_device;
काष्ठा device;

/**
 * काष्ठा पूर्णांकel_pingroup - Description about group of pins
 * @name: Name of the groups
 * @pins: All pins in this group
 * @npins: Number of pins in this groups
 * @mode: Native mode in which the group is muxed out @pins. Used अगर @modes
 *        is %शून्य.
 * @modes: If not %शून्य this will hold mode क्रम each pin in @pins
 */
काष्ठा पूर्णांकel_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	माप_प्रकार npins;
	अचिन्हित लघु mode;
	स्थिर अचिन्हित पूर्णांक *modes;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_function - Description about a function
 * @name: Name of the function
 * @groups: An array of groups क्रम this function
 * @ngroups: Number of groups in @groups
 */
काष्ठा पूर्णांकel_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	माप_प्रकार ngroups;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_padgroup - Hardware pad group inक्रमmation
 * @reg_num: GPI_IS रेजिस्टर number
 * @base: Starting pin of this group
 * @size: Size of this group (maximum is 32).
 * @gpio_base: Starting GPIO base of this group
 * @paकरोwn_num: PAD_OWN रेजिस्टर number (asचिन्हित by the core driver)
 *
 * If pad groups of a community are not the same size, use this काष्ठाure
 * to specअगरy them.
 */
काष्ठा पूर्णांकel_padgroup अणु
	अचिन्हित पूर्णांक reg_num;
	अचिन्हित पूर्णांक base;
	अचिन्हित पूर्णांक size;
	पूर्णांक gpio_base;
	अचिन्हित पूर्णांक paकरोwn_num;
पूर्ण;

/**
 * क्रमागत - Special treaपंचांगent क्रम GPIO base in pad group
 *
 * @INTEL_GPIO_BASE_ZERO:	क्रमce GPIO base to be 0
 * @INTEL_GPIO_BASE_NOMAP:	no GPIO mapping should be created
 * @INTEL_GPIO_BASE_MATCH:	matches with starting pin number
 */
क्रमागत अणु
	INTEL_GPIO_BASE_ZERO	= -2,
	INTEL_GPIO_BASE_NOMAP	= -1,
	INTEL_GPIO_BASE_MATCH	= 0,
पूर्ण;

/**
 * काष्ठा पूर्णांकel_community - Intel pin community description
 * @barno: MMIO BAR number where रेजिस्टरs क्रम this community reside
 * @paकरोwn_offset: Register offset of PAD_OWN रेजिस्टर from @regs. If %0
 *                 then there is no support क्रम owner.
 * @padcfglock_offset: Register offset of PADCFGLOCK from @regs. If %0 then
 *                     locking is not supported.
 * @hostown_offset: Register offset of HOSTSW_OWN from @regs. If %0 then it
 *                  is assumed that the host owns the pin (rather than
 *                  ACPI).
 * @is_offset: Register offset of GPI_IS from @regs.
 * @ie_offset: Register offset of GPI_IE from @regs.
 * @features: Additional features supported by the hardware
 * @pin_base: Starting pin of pins in this community
 * @npins: Number of pins in this community
 * @gpp_size: Maximum number of pads in each group, such as PADCFGLOCK,
 *            HOSTSW_OWN, GPI_IS, GPI_IE. Used when @gpps is %शून्य.
 * @gpp_num_paकरोwn_regs: Number of pad रेजिस्टरs each pad group consumes at
 *			 minimum. Use %0 अगर the number of रेजिस्टरs can be
 *			 determined by the size of the group.
 * @gpps: Pad groups अगर the controller has variable size pad groups
 * @ngpps: Number of pad groups in this community
 * @pad_map: Optional non-linear mapping of the pads
 * @nirqs: Optional total number of IRQs this community can generate
 * @acpi_space_id: Optional address space ID क्रम ACPI OpRegion handler
 * @regs: Community specअगरic common रेजिस्टरs (reserved क्रम core driver)
 * @pad_regs: Community specअगरic pad रेजिस्टरs (reserved क्रम core driver)
 *
 * In some of Intel GPIO host controllers this driver supports each pad group
 * is of equal size (except the last one). In that हाल the driver can just
 * fill in @gpp_size field and let the core driver to handle the rest. If
 * the controller has pad groups of variable size the client driver can
 * pass custom @gpps and @ngpps instead.
 */
काष्ठा पूर्णांकel_community अणु
	अचिन्हित पूर्णांक barno;
	अचिन्हित पूर्णांक paकरोwn_offset;
	अचिन्हित पूर्णांक padcfglock_offset;
	अचिन्हित पूर्णांक hostown_offset;
	अचिन्हित पूर्णांक is_offset;
	अचिन्हित पूर्णांक ie_offset;
	अचिन्हित पूर्णांक features;
	अचिन्हित पूर्णांक pin_base;
	माप_प्रकार npins;
	अचिन्हित पूर्णांक gpp_size;
	अचिन्हित पूर्णांक gpp_num_paकरोwn_regs;
	स्थिर काष्ठा पूर्णांकel_padgroup *gpps;
	माप_प्रकार ngpps;
	स्थिर अचिन्हित पूर्णांक *pad_map;
	अचिन्हित लघु nirqs;
	अचिन्हित लघु acpi_space_id;

	/* Reserved क्रम the core driver */
	व्योम __iomem *regs;
	व्योम __iomem *pad_regs;
पूर्ण;

/* Additional features supported by the hardware */
#घोषणा PINCTRL_FEATURE_DEBOUNCE	BIT(0)
#घोषणा PINCTRL_FEATURE_1K_PD		BIT(1)
#घोषणा PINCTRL_FEATURE_GPIO_HW_INFO	BIT(2)
#घोषणा PINCTRL_FEATURE_PWM		BIT(3)
#घोषणा PINCTRL_FEATURE_BLINK		BIT(4)
#घोषणा PINCTRL_FEATURE_EXP		BIT(5)

/**
 * PIN_GROUP - Declare a pin group
 * @n: Name of the group
 * @p: An array of pins this group consists
 * @m: Mode which the pins are put when this group is active. Can be either
 *     a single पूर्णांकeger or an array of पूर्णांकegers in which हाल mode is per
 *     pin.
 */
#घोषणा PIN_GROUP(n, p, m)					\
	अणु							\
		.name = (n),					\
		.pins = (p),					\
		.npins = ARRAY_SIZE((p)),			\
		.mode = __builtin_choose_expr(			\
			__builtin_स्थिरant_p((m)), (m), 0),	\
		.modes = __builtin_choose_expr(			\
			__builtin_स्थिरant_p((m)), शून्य, (m)),	\
	पूर्ण

#घोषणा FUNCTION(n, g)				\
	अणु					\
		.name = (n),			\
		.groups = (g),			\
		.ngroups = ARRAY_SIZE((g)),	\
	पूर्ण

/**
 * काष्ठा पूर्णांकel_pinctrl_soc_data - Intel pin controller per-SoC configuration
 * @uid: ACPI _UID क्रम the probe driver use अगर needed
 * @pins: Array अगर pins this pinctrl controls
 * @npins: Number of pins in the array
 * @groups: Array of pin groups
 * @ngroups: Number of groups in the array
 * @functions: Array of functions
 * @nfunctions: Number of functions in the array
 * @communities: Array of communities this pinctrl handles
 * @ncommunities: Number of communities in the array
 *
 * The @communities is used as a ढाँचा by the core driver. It will make
 * copy of all communities and fill in rest of the inक्रमmation.
 */
काष्ठा पूर्णांकel_pinctrl_soc_data अणु
	स्थिर अक्षर *uid;
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	माप_प्रकार npins;
	स्थिर काष्ठा पूर्णांकel_pingroup *groups;
	माप_प्रकार ngroups;
	स्थिर काष्ठा पूर्णांकel_function *functions;
	माप_प्रकार nfunctions;
	स्थिर काष्ठा पूर्णांकel_community *communities;
	माप_प्रकार ncommunities;
पूर्ण;

स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *पूर्णांकel_pinctrl_get_soc_data(काष्ठा platक्रमm_device *pdev);

काष्ठा पूर्णांकel_pad_context;
काष्ठा पूर्णांकel_community_context;

/**
 * काष्ठा पूर्णांकel_pinctrl_context - context to be saved during suspend-resume
 * @pads: Opaque context per pad (driver dependent)
 * @communities: Opaque context per community (driver dependent)
 */
काष्ठा पूर्णांकel_pinctrl_context अणु
	काष्ठा पूर्णांकel_pad_context *pads;
	काष्ठा पूर्णांकel_community_context *communities;
पूर्ण;

/**
 * काष्ठा पूर्णांकel_pinctrl - Intel pinctrl निजी काष्ठाure
 * @dev: Poपूर्णांकer to the device काष्ठाure
 * @lock: Lock to serialize रेजिस्टर access
 * @pctldesc: Pin controller description
 * @pctldev: Poपूर्णांकer to the pin controller device
 * @chip: GPIO chip in this pin controller
 * @irqchip: IRQ chip in this pin controller
 * @soc: SoC/PCH specअगरic pin configuration data
 * @communities: All communities in this pin controller
 * @ncommunities: Number of communities in this pin controller
 * @context: Configuration saved over प्रणाली sleep
 * @irq: pinctrl/GPIO chip irq number
 */
काष्ठा पूर्णांकel_pinctrl अणु
	काष्ठा device *dev;
	raw_spinlock_t lock;
	काष्ठा pinctrl_desc pctldesc;
	काष्ठा pinctrl_dev *pctldev;
	काष्ठा gpio_chip chip;
	काष्ठा irq_chip irqchip;
	स्थिर काष्ठा पूर्णांकel_pinctrl_soc_data *soc;
	काष्ठा पूर्णांकel_community *communities;
	माप_प्रकार ncommunities;
	काष्ठा पूर्णांकel_pinctrl_context context;
	पूर्णांक irq;
पूर्ण;

पूर्णांक पूर्णांकel_pinctrl_probe_by_hid(काष्ठा platक्रमm_device *pdev);
पूर्णांक पूर्णांकel_pinctrl_probe_by_uid(काष्ठा platक्रमm_device *pdev);

#अगर_घोषित CONFIG_PM_SLEEP
पूर्णांक पूर्णांकel_pinctrl_suspend_noirq(काष्ठा device *dev);
पूर्णांक पूर्णांकel_pinctrl_resume_noirq(काष्ठा device *dev);
#पूर्ण_अगर

#घोषणा INTEL_PINCTRL_PM_OPS(_name)					\
स्थिर काष्ठा dev_pm_ops _name = अणु					\
	SET_NOIRQ_SYSTEM_SLEEP_PM_OPS(पूर्णांकel_pinctrl_suspend_noirq,	\
				      पूर्णांकel_pinctrl_resume_noirq)	\
पूर्ण

#पूर्ण_अगर /* PINCTRL_INTEL_H */
