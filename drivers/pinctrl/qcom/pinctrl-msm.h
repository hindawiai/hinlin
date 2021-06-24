<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2013, Sony Mobile Communications AB.
 */
#अगर_अघोषित __PINCTRL_MSM_H__
#घोषणा __PINCTRL_MSM_H__

काष्ठा pinctrl_pin_desc;

/**
 * काष्ठा msm_function - a pinmux function
 * @name:    Name of the pinmux function.
 * @groups:  List of pingroups क्रम this function.
 * @ngroups: Number of entries in @groups.
 */
काष्ठा msm_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर * स्थिर *groups;
	अचिन्हित ngroups;
पूर्ण;

/**
 * काष्ठा msm_pingroup - Qualcomm pingroup definition
 * @name:                 Name of the pingroup.
 * @pins:	          A list of pins asचिन्हित to this pingroup.
 * @npins:	          Number of entries in @pins.
 * @funcs:                A list of pinmux functions that can be selected क्रम
 *                        this group. The index of the selected function is used
 *                        क्रम programming the function selector.
 *                        Entries should be indices पूर्णांकo the groups list of the
 *                        काष्ठा msm_pinctrl_soc_data.
 * @ctl_reg:              Offset of the रेजिस्टर holding control bits क्रम this group.
 * @io_reg:               Offset of the रेजिस्टर holding input/output bits क्रम this group.
 * @पूर्णांकr_cfg_reg:         Offset of the रेजिस्टर holding पूर्णांकerrupt configuration bits.
 * @पूर्णांकr_status_reg:      Offset of the रेजिस्टर holding the status bits क्रम this group.
 * @पूर्णांकr_target_reg:      Offset of the रेजिस्टर specअगरying routing of the पूर्णांकerrupts
 *                        from this group.
 * @mux_bit:              Offset in @ctl_reg क्रम the pinmux function selection.
 * @pull_bit:             Offset in @ctl_reg क्रम the bias configuration.
 * @drv_bit:              Offset in @ctl_reg क्रम the drive strength configuration.
 * @od_bit:               Offset in @ctl_reg क्रम controlling खोलो drain.
 * @oe_bit:               Offset in @ctl_reg क्रम controlling output enable.
 * @in_bit:               Offset in @io_reg क्रम the input bit value.
 * @out_bit:              Offset in @io_reg क्रम the output bit value.
 * @पूर्णांकr_enable_bit:      Offset in @पूर्णांकr_cfg_reg क्रम enabling the पूर्णांकerrupt क्रम this group.
 * @पूर्णांकr_status_bit:      Offset in @पूर्णांकr_status_reg क्रम पढ़ोing and acking the पूर्णांकerrupt
 *                        status.
 * @पूर्णांकr_target_bit:      Offset in @पूर्णांकr_target_reg क्रम configuring the पूर्णांकerrupt routing.
 * @पूर्णांकr_target_kpss_val: Value in @पूर्णांकr_target_bit क्रम specअगरying that the पूर्णांकerrupt from
 *                        this gpio should get routed to the KPSS processor.
 * @पूर्णांकr_raw_status_bit:  Offset in @पूर्णांकr_cfg_reg क्रम the raw status bit.
 * @पूर्णांकr_polarity_bit:    Offset in @पूर्णांकr_cfg_reg क्रम specअगरying polarity of the पूर्णांकerrupt.
 * @पूर्णांकr_detection_bit:   Offset in @पूर्णांकr_cfg_reg क्रम specअगरying पूर्णांकerrupt type.
 * @पूर्णांकr_detection_width: Number of bits used क्रम specअगरying पूर्णांकerrupt type,
 *                        Should be 2 क्रम SoCs that can detect both edges in hardware,
 *                        otherwise 1.
 */
काष्ठा msm_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित *pins;
	अचिन्हित npins;

	अचिन्हित *funcs;
	अचिन्हित nfuncs;

	u32 ctl_reg;
	u32 io_reg;
	u32 पूर्णांकr_cfg_reg;
	u32 पूर्णांकr_status_reg;
	u32 पूर्णांकr_target_reg;

	अचिन्हित पूर्णांक tile:2;

	अचिन्हित mux_bit:5;

	अचिन्हित pull_bit:5;
	अचिन्हित drv_bit:5;

	अचिन्हित od_bit:5;
	अचिन्हित oe_bit:5;
	अचिन्हित in_bit:5;
	अचिन्हित out_bit:5;

	अचिन्हित पूर्णांकr_enable_bit:5;
	अचिन्हित पूर्णांकr_status_bit:5;
	अचिन्हित पूर्णांकr_ack_high:1;

	अचिन्हित पूर्णांकr_target_bit:5;
	अचिन्हित पूर्णांकr_target_kpss_val:5;
	अचिन्हित पूर्णांकr_raw_status_bit:5;
	अचिन्हित पूर्णांकr_polarity_bit:5;
	अचिन्हित पूर्णांकr_detection_bit:5;
	अचिन्हित पूर्णांकr_detection_width:5;
पूर्ण;

/**
 * काष्ठा msm_gpio_wakeirq_map - Map of GPIOs and their wakeup pins
 * @gpio:          The GPIOs that are wakeup capable
 * @wakeirq:       The पूर्णांकerrupt at the always-on पूर्णांकerrupt controller
 */
काष्ठा msm_gpio_wakeirq_map अणु
	अचिन्हित पूर्णांक gpio;
	अचिन्हित पूर्णांक wakeirq;
पूर्ण;

/**
 * काष्ठा msm_pinctrl_soc_data - Qualcomm pin controller driver configuration
 * @pins:	    An array describing all pins the pin controller affects.
 * @npins:	    The number of entries in @pins.
 * @functions:	    An array describing all mux functions the SoC supports.
 * @nfunctions:	    The number of entries in @functions.
 * @groups:	    An array describing all pin groups the pin SoC supports.
 * @ngroups:	    The numbmer of entries in @groups.
 * @ngpio:	    The number of pingroups the driver should expose as GPIOs.
 * @pull_no_keeper: The SoC करोes not support keeper bias.
 * @wakeirq_map:    The map of wakeup capable GPIOs and the pin at PDC/MPM
 * @nwakeirq_map:   The number of entries in @wakeirq_map
 * @wakeirq_dual_edge_errata: If true then GPIOs using the wakeirq_map need
 *                            to be aware that their parent can't handle dual
 *                            edge पूर्णांकerrupts.
 * @gpio_func: Which function number is GPIO (usually 0).
 */
काष्ठा msm_pinctrl_soc_data अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;
	स्थिर काष्ठा msm_function *functions;
	अचिन्हित nfunctions;
	स्थिर काष्ठा msm_pingroup *groups;
	अचिन्हित ngroups;
	अचिन्हित ngpios;
	bool pull_no_keeper;
	स्थिर अक्षर *स्थिर *tiles;
	अचिन्हित पूर्णांक ntiles;
	स्थिर पूर्णांक *reserved_gpios;
	स्थिर काष्ठा msm_gpio_wakeirq_map *wakeirq_map;
	अचिन्हित पूर्णांक nwakeirq_map;
	bool wakeirq_dual_edge_errata;
	अचिन्हित पूर्णांक gpio_func;
पूर्ण;

बाह्य स्थिर काष्ठा dev_pm_ops msm_pinctrl_dev_pm_ops;

पूर्णांक msm_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
		      स्थिर काष्ठा msm_pinctrl_soc_data *soc_data);
पूर्णांक msm_pinctrl_हटाओ(काष्ठा platक्रमm_device *pdev);

#पूर्ण_अगर
