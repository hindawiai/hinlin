<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Marvell MVEBU pinctrl driver
 *
 * Authors: Sebastian Hesselbarth <sebastian.hesselbarth@gmail.com>
 *          Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 */

#अगर_अघोषित __PINCTRL_MVEBU_H__
#घोषणा __PINCTRL_MVEBU_H__

/**
 * काष्ठा mvebu_mpp_ctrl_data - निजी data क्रम the mpp ctrl operations
 * @base: base address of pinctrl hardware
 * @regmap.map: regmap काष्ठाure
 * @regmap.offset: regmap offset
 */
काष्ठा mvebu_mpp_ctrl_data अणु
	जोड़ अणु
		व्योम __iomem *base;
		काष्ठा अणु
			काष्ठा regmap *map;
			u32 offset;
		पूर्ण regmap;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा mvebu_mpp_ctrl - describe a mpp control
 * @name: name of the control group
 * @pid: first pin id handled by this control
 * @npins: number of pins controlled by this control
 * @mpp_get: (optional) special function to get mpp setting
 * @mpp_set: (optional) special function to set mpp setting
 * @mpp_gpio_req: (optional) special function to request gpio
 * @mpp_gpio_dir: (optional) special function to set gpio direction
 *
 * A mpp_ctrl describes a muxable unit, e.g. pin, group of pins, or
 * पूर्णांकernal function, inside the SoC. Each muxable unit can be चयनed
 * between two or more dअगरferent settings, e.g. assign mpp pin 13 to
 * uart1 or sata.
 *
 * The mpp_get/_set functions are mandatory and are used to get/set a
 * specअगरic mode. The optional mpp_gpio_req/_dir functions can be used
 * to allow pin settings with varying gpio pins.
 */
काष्ठा mvebu_mpp_ctrl अणु
	स्थिर अक्षर *name;
	u8 pid;
	u8 npins;
	अचिन्हित *pins;
	पूर्णांक (*mpp_get)(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
		       अचिन्हित दीर्घ *config);
	पूर्णांक (*mpp_set)(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
		       अचिन्हित दीर्घ config);
	पूर्णांक (*mpp_gpio_req)(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid);
	पूर्णांक (*mpp_gpio_dir)(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			    bool input);
पूर्ण;

/**
 * काष्ठा mvebu_mpp_ctrl_setting - describe a mpp ctrl setting
 * @val: ctrl setting value
 * @name: ctrl setting name, e.g. uart2, spi0 - unique per mpp_mode
 * @subname: (optional) additional ctrl setting name, e.g. rts, cts
 * @variant: (optional) variant identअगरier mask
 * @flags: (निजी) flags to store gpi/gpo/gpio capabilities
 *
 * A ctrl_setting describes a specअगरic पूर्णांकernal mux function that a mpp pin
 * can be चयनed to. The value (val) will be written in the corresponding
 * रेजिस्टर क्रम common mpp pin configuration रेजिस्टरs on MVEBU. SoC specअगरic
 * mpp_get/_set function may use val to distinguish between dअगरferent settings.
 *
 * The name will be used to चयन to this setting in DT description, e.g.
 * marvell,function = "uart2". subname is only क्रम debugging purposes.
 *
 * If name is one of "gpi", "gpo", "gpio" gpio capabilities are
 * parsed during initialization and stored in flags.
 *
 * The variant can be used to combine dअगरferent revisions of one SoC to a
 * common pinctrl driver. It is matched (AND) with variant of soc_info to
 * determine अगर a setting is available on the current SoC revision.
 */
काष्ठा mvebu_mpp_ctrl_setting अणु
	u8 val;
	स्थिर अक्षर *name;
	स्थिर अक्षर *subname;
	u8 variant;
	u8 flags;
#घोषणा  MVEBU_SETTING_GPO	(1 << 0)
#घोषणा  MVEBU_SETTING_GPI	(1 << 1)
पूर्ण;

/**
 * काष्ठा mvebu_mpp_mode - link ctrl and settings
 * @pid: first pin id handled by this mode
 * @settings: list of settings available क्रम this mode
 *
 * A mode connects all available settings with the corresponding mpp_ctrl
 * given by pid.
 */
काष्ठा mvebu_mpp_mode अणु
	u8 pid;
	काष्ठा mvebu_mpp_ctrl_setting *settings;
पूर्ण;

/**
 * काष्ठा mvebu_pinctrl_soc_info - SoC specअगरic info passed to pinctrl-mvebu
 * @variant: variant mask of soc_info
 * @controls: list of available mvebu_mpp_ctrls
 * @control_data: optional array, one entry क्रम each control
 * @ncontrols: number of available mvebu_mpp_ctrls
 * @modes: list of available mvebu_mpp_modes
 * @nmodes: number of available mvebu_mpp_modes
 * @gpioranges: list of pinctrl_gpio_ranges
 * @ngpioranges: number of available pinctrl_gpio_ranges
 *
 * This काष्ठा describes all pinctrl related inक्रमmation क्रम a specअगरic SoC.
 * If variant is unequal 0 it will be matched (AND) with variant of each
 * setting and allows to distinguish between dअगरferent revisions of one SoC.
 */
काष्ठा mvebu_pinctrl_soc_info अणु
	u8 variant;
	स्थिर काष्ठा mvebu_mpp_ctrl *controls;
	काष्ठा mvebu_mpp_ctrl_data *control_data;
	पूर्णांक ncontrols;
	काष्ठा mvebu_mpp_mode *modes;
	पूर्णांक nmodes;
	काष्ठा pinctrl_gpio_range *gpioranges;
	पूर्णांक ngpioranges;
पूर्ण;

#घोषणा MPP_FUNC_CTRL(_idl, _idh, _name, _func)			\
	अणु							\
		.name = _name,					\
		.pid = _idl,					\
		.npins = _idh - _idl + 1,			\
		.pins = (अचिन्हित[_idh - _idl + 1]) अणु पूर्ण,	\
		.mpp_get = _func ## _get,			\
		.mpp_set = _func ## _set,			\
		.mpp_gpio_req = शून्य,				\
		.mpp_gpio_dir = शून्य,				\
	पूर्ण

#घोषणा MPP_FUNC_GPIO_CTRL(_idl, _idh, _name, _func)		\
	अणु							\
		.name = _name,					\
		.pid = _idl,					\
		.npins = _idh - _idl + 1,			\
		.pins = (अचिन्हित[_idh - _idl + 1]) अणु पूर्ण,	\
		.mpp_get = _func ## _get,			\
		.mpp_set = _func ## _set,			\
		.mpp_gpio_req = _func ## _gpio_req,		\
		.mpp_gpio_dir = _func ## _gpio_dir,		\
	पूर्ण

#घोषणा _MPP_VAR_FUNCTION(_val, _name, _subname, _mask)		\
	अणु							\
		.val = _val,					\
		.name = _name,					\
		.subname = _subname,				\
		.variant = _mask,				\
		.flags = 0,					\
	पूर्ण

#अगर defined(CONFIG_DEBUG_FS)
#घोषणा MPP_VAR_FUNCTION(_val, _name, _subname, _mask)		\
	_MPP_VAR_FUNCTION(_val, _name, _subname, _mask)
#अन्यथा
#घोषणा MPP_VAR_FUNCTION(_val, _name, _subname, _mask)		\
	_MPP_VAR_FUNCTION(_val, _name, शून्य, _mask)
#पूर्ण_अगर

#घोषणा MPP_FUNCTION(_val, _name, _subname)			\
	MPP_VAR_FUNCTION(_val, _name, _subname, (u8)-1)

#घोषणा MPP_MODE(_id, ...)					\
	अणु							\
		.pid = _id,					\
		.settings = (काष्ठा mvebu_mpp_ctrl_setting[])अणु	\
			__VA_ARGS__, अणु पूर्ण पूर्ण,			\
	पूर्ण

#घोषणा MPP_GPIO_RANGE(_id, _pinbase, _gpiobase, _npins)	\
	अणु							\
		.name = "mvebu-gpio",				\
		.id = _id,					\
		.pin_base = _pinbase,				\
		.base = _gpiobase,				\
		.npins = _npins,				\
	पूर्ण

#घोषणा MVEBU_MPPS_PER_REG	8
#घोषणा MVEBU_MPP_BITS		4
#घोषणा MVEBU_MPP_MASK		0xf

पूर्णांक mvebu_mmio_mpp_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			       अचिन्हित दीर्घ *config);
पूर्णांक mvebu_mmio_mpp_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			       अचिन्हित दीर्घ config);
पूर्णांक mvebu_regmap_mpp_ctrl_get(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ *config);
पूर्णांक mvebu_regmap_mpp_ctrl_set(काष्ठा mvebu_mpp_ctrl_data *data, अचिन्हित pid,
			      अचिन्हित दीर्घ config);

पूर्णांक mvebu_pinctrl_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक mvebu_pinctrl_simple_mmio_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक mvebu_pinctrl_simple_regmap_probe(काष्ठा platक्रमm_device *pdev,
				      काष्ठा device *syscon_dev, u32 offset);

#पूर्ण_अगर
