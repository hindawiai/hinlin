<शैली गुरु>
/*
 * Driver header file क्रम the ST Microelectronics SPEAr pinmux
 *
 * Copyright (C) 2012 ST Microelectronics
 * Viresh Kumar <vireshk@kernel.org>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#अगर_अघोषित __PINMUX_SPEAR_H__
#घोषणा __PINMUX_SPEAR_H__

#समावेश <linux/gpio/driver.h>
#समावेश <linux/पन.स>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/types.h>

काष्ठा platक्रमm_device;
काष्ठा device;
काष्ठा spear_pmx;

/**
 * काष्ठा spear_pmx_mode - SPEAr pmx mode
 * @name: name of pmx mode
 * @mode: mode id
 * @reg: रेजिस्टर क्रम configuring this mode
 * @mask: mask of this mode in reg
 * @val: val to be configured at reg after करोing (val & mask)
 */
काष्ठा spear_pmx_mode अणु
	स्थिर अक्षर *स्थिर name;
	u16 mode;
	u16 reg;
	u16 mask;
	u32 val;
पूर्ण;

/**
 * काष्ठा spear_muxreg - SPEAr mux reg configuration
 * @reg: रेजिस्टर offset
 * @mask: mask bits
 * @val: val to be written on mask bits
 */
काष्ठा spear_muxreg अणु
	u16 reg;
	u32 mask;
	u32 val;
पूर्ण;

काष्ठा spear_gpio_pingroup अणु
	स्थिर अचिन्हित *pins;
	अचिन्हित npins;
	काष्ठा spear_muxreg *muxregs;
	u8 nmuxregs;
पूर्ण;

/* ste: set to enable */
#घोषणा DEFINE_MUXREG(__pins, __muxreg, __mask, __ste)		\
अटल काष्ठा spear_muxreg __pins##_muxregs[] = अणु		\
	अणु							\
		.reg = __muxreg,				\
		.mask = __mask,					\
		.val = __ste ? __mask : 0,			\
	पूर्ण,							\
पूर्ण

#घोषणा DEFINE_2_MUXREG(__pins, __muxreg1, __muxreg2, __mask, __ste1, __ste2) \
अटल काष्ठा spear_muxreg __pins##_muxregs[] = अणु		\
	अणु							\
		.reg = __muxreg1,				\
		.mask = __mask,					\
		.val = __ste1 ? __mask : 0,			\
	पूर्ण, अणु							\
		.reg = __muxreg2,				\
		.mask = __mask,					\
		.val = __ste2 ? __mask : 0,			\
	पूर्ण,							\
पूर्ण

#घोषणा GPIO_PINGROUP(__pins)					\
	अणु							\
		.pins = __pins,					\
		.npins = ARRAY_SIZE(__pins),			\
		.muxregs = __pins##_muxregs,			\
		.nmuxregs = ARRAY_SIZE(__pins##_muxregs),	\
	पूर्ण

/**
 * काष्ठा spear_modemux - SPEAr mode mux configuration
 * @modes: mode ids supported by this group of muxregs
 * @nmuxregs: number of muxreg configurations to be करोne क्रम modes
 * @muxregs: array of muxreg configurations to be करोne क्रम modes
 */
काष्ठा spear_modemux अणु
	u16 modes;
	u8 nmuxregs;
	काष्ठा spear_muxreg *muxregs;
पूर्ण;

/**
 * काष्ठा spear_pingroup - SPEAr pin group configurations
 * @name: name of pin group
 * @pins: array containing pin numbers
 * @npins: size of pins array
 * @modemuxs: array of modemux configurations क्रम this pin group
 * @nmodemuxs: size of array modemuxs
 *
 * A representation of a group of pins in the SPEAr pin controller. Each group
 * allows some parameter or parameters to be configured.
 */
काष्ठा spear_pingroup अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित *pins;
	अचिन्हित npins;
	काष्ठा spear_modemux *modemuxs;
	अचिन्हित nmodemuxs;
पूर्ण;

/**
 * काष्ठा spear_function - SPEAr pinctrl mux function
 * @name: The name of the function, exported to pinctrl core.
 * @groups: An array of pin groups that may select this function.
 * @ngroups: The number of entries in @groups.
 */
काष्ठा spear_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *स्थिर *groups;
	अचिन्हित ngroups;
पूर्ण;

/**
 * काष्ठा spear_pinctrl_machdata - SPEAr pin controller machine driver
 *	configuration
 * @pins: An array describing all pins the pin controller affects.
 *	All pins which are also GPIOs must be listed first within the *array,
 *	and be numbered identically to the GPIO controller's *numbering.
 * @npins: The numbmer of entries in @pins.
 * @functions: An array describing all mux functions the SoC supports.
 * @nfunctions: The numbmer of entries in @functions.
 * @groups: An array describing all pin groups the pin SoC supports.
 * @ngroups: The numbmer of entries in @groups.
 * @gpio_pingroups: gpio pingroups
 * @ngpio_pingroups: gpio pingroups count
 *
 * @modes_supported: Does SoC support modes
 * @mode: mode configured from probe
 * @pmx_modes: array of modes supported by SoC
 * @npmx_modes: number of entries in pmx_modes.
 */
काष्ठा spear_pinctrl_machdata अणु
	स्थिर काष्ठा pinctrl_pin_desc *pins;
	अचिन्हित npins;
	काष्ठा spear_function **functions;
	अचिन्हित nfunctions;
	काष्ठा spear_pingroup **groups;
	अचिन्हित ngroups;
	काष्ठा spear_gpio_pingroup *gpio_pingroups;
	व्योम (*gpio_request_endisable)(काष्ठा spear_pmx *pmx, पूर्णांक offset,
			bool enable);
	अचिन्हित ngpio_pingroups;

	bool modes_supported;
	u16 mode;
	काष्ठा spear_pmx_mode **pmx_modes;
	अचिन्हित npmx_modes;
पूर्ण;

/**
 * काष्ठा spear_pmx - SPEAr pinctrl mux
 * @dev: poपूर्णांकer to काष्ठा dev of platक्रमm_device रेजिस्टरed
 * @pctl: poपूर्णांकer to काष्ठा pinctrl_dev
 * @machdata: poपूर्णांकer to SoC or machine specअगरic काष्ठाure
 * @vbase: भव base address of pinmux controller
 */
काष्ठा spear_pmx अणु
	काष्ठा device *dev;
	काष्ठा pinctrl_dev *pctl;
	काष्ठा spear_pinctrl_machdata *machdata;
	व्योम __iomem *vbase;
पूर्ण;

/* exported routines */
अटल अंतरभूत u32 pmx_पढ़ोl(काष्ठा spear_pmx *pmx, u32 reg)
अणु
	वापस पढ़ोl_relaxed(pmx->vbase + reg);
पूर्ण

अटल अंतरभूत व्योम pmx_ग_लिखोl(काष्ठा spear_pmx *pmx, u32 val, u32 reg)
अणु
	ग_लिखोl_relaxed(val, pmx->vbase + reg);
पूर्ण

व्योम pmx_init_addr(काष्ठा spear_pinctrl_machdata *machdata, u16 reg);
व्योम pmx_init_gpio_pingroup_addr(काष्ठा spear_gpio_pingroup *gpio_pingroup,
				 अचिन्हित count, u16 reg);
पूर्णांक spear_pinctrl_probe(काष्ठा platक्रमm_device *pdev,
			काष्ठा spear_pinctrl_machdata *machdata);

#घोषणा SPEAR_PIN_0_TO_101		\
	PINCTRL_PIN(0, "PLGPIO0"),	\
	PINCTRL_PIN(1, "PLGPIO1"),	\
	PINCTRL_PIN(2, "PLGPIO2"),	\
	PINCTRL_PIN(3, "PLGPIO3"),	\
	PINCTRL_PIN(4, "PLGPIO4"),	\
	PINCTRL_PIN(5, "PLGPIO5"),	\
	PINCTRL_PIN(6, "PLGPIO6"),	\
	PINCTRL_PIN(7, "PLGPIO7"),	\
	PINCTRL_PIN(8, "PLGPIO8"),	\
	PINCTRL_PIN(9, "PLGPIO9"),	\
	PINCTRL_PIN(10, "PLGPIO10"),	\
	PINCTRL_PIN(11, "PLGPIO11"),	\
	PINCTRL_PIN(12, "PLGPIO12"),	\
	PINCTRL_PIN(13, "PLGPIO13"),	\
	PINCTRL_PIN(14, "PLGPIO14"),	\
	PINCTRL_PIN(15, "PLGPIO15"),	\
	PINCTRL_PIN(16, "PLGPIO16"),	\
	PINCTRL_PIN(17, "PLGPIO17"),	\
	PINCTRL_PIN(18, "PLGPIO18"),	\
	PINCTRL_PIN(19, "PLGPIO19"),	\
	PINCTRL_PIN(20, "PLGPIO20"),	\
	PINCTRL_PIN(21, "PLGPIO21"),	\
	PINCTRL_PIN(22, "PLGPIO22"),	\
	PINCTRL_PIN(23, "PLGPIO23"),	\
	PINCTRL_PIN(24, "PLGPIO24"),	\
	PINCTRL_PIN(25, "PLGPIO25"),	\
	PINCTRL_PIN(26, "PLGPIO26"),	\
	PINCTRL_PIN(27, "PLGPIO27"),	\
	PINCTRL_PIN(28, "PLGPIO28"),	\
	PINCTRL_PIN(29, "PLGPIO29"),	\
	PINCTRL_PIN(30, "PLGPIO30"),	\
	PINCTRL_PIN(31, "PLGPIO31"),	\
	PINCTRL_PIN(32, "PLGPIO32"),	\
	PINCTRL_PIN(33, "PLGPIO33"),	\
	PINCTRL_PIN(34, "PLGPIO34"),	\
	PINCTRL_PIN(35, "PLGPIO35"),	\
	PINCTRL_PIN(36, "PLGPIO36"),	\
	PINCTRL_PIN(37, "PLGPIO37"),	\
	PINCTRL_PIN(38, "PLGPIO38"),	\
	PINCTRL_PIN(39, "PLGPIO39"),	\
	PINCTRL_PIN(40, "PLGPIO40"),	\
	PINCTRL_PIN(41, "PLGPIO41"),	\
	PINCTRL_PIN(42, "PLGPIO42"),	\
	PINCTRL_PIN(43, "PLGPIO43"),	\
	PINCTRL_PIN(44, "PLGPIO44"),	\
	PINCTRL_PIN(45, "PLGPIO45"),	\
	PINCTRL_PIN(46, "PLGPIO46"),	\
	PINCTRL_PIN(47, "PLGPIO47"),	\
	PINCTRL_PIN(48, "PLGPIO48"),	\
	PINCTRL_PIN(49, "PLGPIO49"),	\
	PINCTRL_PIN(50, "PLGPIO50"),	\
	PINCTRL_PIN(51, "PLGPIO51"),	\
	PINCTRL_PIN(52, "PLGPIO52"),	\
	PINCTRL_PIN(53, "PLGPIO53"),	\
	PINCTRL_PIN(54, "PLGPIO54"),	\
	PINCTRL_PIN(55, "PLGPIO55"),	\
	PINCTRL_PIN(56, "PLGPIO56"),	\
	PINCTRL_PIN(57, "PLGPIO57"),	\
	PINCTRL_PIN(58, "PLGPIO58"),	\
	PINCTRL_PIN(59, "PLGPIO59"),	\
	PINCTRL_PIN(60, "PLGPIO60"),	\
	PINCTRL_PIN(61, "PLGPIO61"),	\
	PINCTRL_PIN(62, "PLGPIO62"),	\
	PINCTRL_PIN(63, "PLGPIO63"),	\
	PINCTRL_PIN(64, "PLGPIO64"),	\
	PINCTRL_PIN(65, "PLGPIO65"),	\
	PINCTRL_PIN(66, "PLGPIO66"),	\
	PINCTRL_PIN(67, "PLGPIO67"),	\
	PINCTRL_PIN(68, "PLGPIO68"),	\
	PINCTRL_PIN(69, "PLGPIO69"),	\
	PINCTRL_PIN(70, "PLGPIO70"),	\
	PINCTRL_PIN(71, "PLGPIO71"),	\
	PINCTRL_PIN(72, "PLGPIO72"),	\
	PINCTRL_PIN(73, "PLGPIO73"),	\
	PINCTRL_PIN(74, "PLGPIO74"),	\
	PINCTRL_PIN(75, "PLGPIO75"),	\
	PINCTRL_PIN(76, "PLGPIO76"),	\
	PINCTRL_PIN(77, "PLGPIO77"),	\
	PINCTRL_PIN(78, "PLGPIO78"),	\
	PINCTRL_PIN(79, "PLGPIO79"),	\
	PINCTRL_PIN(80, "PLGPIO80"),	\
	PINCTRL_PIN(81, "PLGPIO81"),	\
	PINCTRL_PIN(82, "PLGPIO82"),	\
	PINCTRL_PIN(83, "PLGPIO83"),	\
	PINCTRL_PIN(84, "PLGPIO84"),	\
	PINCTRL_PIN(85, "PLGPIO85"),	\
	PINCTRL_PIN(86, "PLGPIO86"),	\
	PINCTRL_PIN(87, "PLGPIO87"),	\
	PINCTRL_PIN(88, "PLGPIO88"),	\
	PINCTRL_PIN(89, "PLGPIO89"),	\
	PINCTRL_PIN(90, "PLGPIO90"),	\
	PINCTRL_PIN(91, "PLGPIO91"),	\
	PINCTRL_PIN(92, "PLGPIO92"),	\
	PINCTRL_PIN(93, "PLGPIO93"),	\
	PINCTRL_PIN(94, "PLGPIO94"),	\
	PINCTRL_PIN(95, "PLGPIO95"),	\
	PINCTRL_PIN(96, "PLGPIO96"),	\
	PINCTRL_PIN(97, "PLGPIO97"),	\
	PINCTRL_PIN(98, "PLGPIO98"),	\
	PINCTRL_PIN(99, "PLGPIO99"),	\
	PINCTRL_PIN(100, "PLGPIO100"),	\
	PINCTRL_PIN(101, "PLGPIO101")

#घोषणा SPEAR_PIN_102_TO_245		\
	PINCTRL_PIN(102, "PLGPIO102"),	\
	PINCTRL_PIN(103, "PLGPIO103"),	\
	PINCTRL_PIN(104, "PLGPIO104"),	\
	PINCTRL_PIN(105, "PLGPIO105"),	\
	PINCTRL_PIN(106, "PLGPIO106"),	\
	PINCTRL_PIN(107, "PLGPIO107"),	\
	PINCTRL_PIN(108, "PLGPIO108"),	\
	PINCTRL_PIN(109, "PLGPIO109"),	\
	PINCTRL_PIN(110, "PLGPIO110"),	\
	PINCTRL_PIN(111, "PLGPIO111"),	\
	PINCTRL_PIN(112, "PLGPIO112"),	\
	PINCTRL_PIN(113, "PLGPIO113"),	\
	PINCTRL_PIN(114, "PLGPIO114"),	\
	PINCTRL_PIN(115, "PLGPIO115"),	\
	PINCTRL_PIN(116, "PLGPIO116"),	\
	PINCTRL_PIN(117, "PLGPIO117"),	\
	PINCTRL_PIN(118, "PLGPIO118"),	\
	PINCTRL_PIN(119, "PLGPIO119"),	\
	PINCTRL_PIN(120, "PLGPIO120"),	\
	PINCTRL_PIN(121, "PLGPIO121"),	\
	PINCTRL_PIN(122, "PLGPIO122"),	\
	PINCTRL_PIN(123, "PLGPIO123"),	\
	PINCTRL_PIN(124, "PLGPIO124"),	\
	PINCTRL_PIN(125, "PLGPIO125"),	\
	PINCTRL_PIN(126, "PLGPIO126"),	\
	PINCTRL_PIN(127, "PLGPIO127"),	\
	PINCTRL_PIN(128, "PLGPIO128"),	\
	PINCTRL_PIN(129, "PLGPIO129"),	\
	PINCTRL_PIN(130, "PLGPIO130"),	\
	PINCTRL_PIN(131, "PLGPIO131"),	\
	PINCTRL_PIN(132, "PLGPIO132"),	\
	PINCTRL_PIN(133, "PLGPIO133"),	\
	PINCTRL_PIN(134, "PLGPIO134"),	\
	PINCTRL_PIN(135, "PLGPIO135"),	\
	PINCTRL_PIN(136, "PLGPIO136"),	\
	PINCTRL_PIN(137, "PLGPIO137"),	\
	PINCTRL_PIN(138, "PLGPIO138"),	\
	PINCTRL_PIN(139, "PLGPIO139"),	\
	PINCTRL_PIN(140, "PLGPIO140"),	\
	PINCTRL_PIN(141, "PLGPIO141"),	\
	PINCTRL_PIN(142, "PLGPIO142"),	\
	PINCTRL_PIN(143, "PLGPIO143"),	\
	PINCTRL_PIN(144, "PLGPIO144"),	\
	PINCTRL_PIN(145, "PLGPIO145"),	\
	PINCTRL_PIN(146, "PLGPIO146"),	\
	PINCTRL_PIN(147, "PLGPIO147"),	\
	PINCTRL_PIN(148, "PLGPIO148"),	\
	PINCTRL_PIN(149, "PLGPIO149"),	\
	PINCTRL_PIN(150, "PLGPIO150"),	\
	PINCTRL_PIN(151, "PLGPIO151"),	\
	PINCTRL_PIN(152, "PLGPIO152"),	\
	PINCTRL_PIN(153, "PLGPIO153"),	\
	PINCTRL_PIN(154, "PLGPIO154"),	\
	PINCTRL_PIN(155, "PLGPIO155"),	\
	PINCTRL_PIN(156, "PLGPIO156"),	\
	PINCTRL_PIN(157, "PLGPIO157"),	\
	PINCTRL_PIN(158, "PLGPIO158"),	\
	PINCTRL_PIN(159, "PLGPIO159"),	\
	PINCTRL_PIN(160, "PLGPIO160"),	\
	PINCTRL_PIN(161, "PLGPIO161"),	\
	PINCTRL_PIN(162, "PLGPIO162"),	\
	PINCTRL_PIN(163, "PLGPIO163"),	\
	PINCTRL_PIN(164, "PLGPIO164"),	\
	PINCTRL_PIN(165, "PLGPIO165"),	\
	PINCTRL_PIN(166, "PLGPIO166"),	\
	PINCTRL_PIN(167, "PLGPIO167"),	\
	PINCTRL_PIN(168, "PLGPIO168"),	\
	PINCTRL_PIN(169, "PLGPIO169"),	\
	PINCTRL_PIN(170, "PLGPIO170"),	\
	PINCTRL_PIN(171, "PLGPIO171"),	\
	PINCTRL_PIN(172, "PLGPIO172"),	\
	PINCTRL_PIN(173, "PLGPIO173"),	\
	PINCTRL_PIN(174, "PLGPIO174"),	\
	PINCTRL_PIN(175, "PLGPIO175"),	\
	PINCTRL_PIN(176, "PLGPIO176"),	\
	PINCTRL_PIN(177, "PLGPIO177"),	\
	PINCTRL_PIN(178, "PLGPIO178"),	\
	PINCTRL_PIN(179, "PLGPIO179"),	\
	PINCTRL_PIN(180, "PLGPIO180"),	\
	PINCTRL_PIN(181, "PLGPIO181"),	\
	PINCTRL_PIN(182, "PLGPIO182"),	\
	PINCTRL_PIN(183, "PLGPIO183"),	\
	PINCTRL_PIN(184, "PLGPIO184"),	\
	PINCTRL_PIN(185, "PLGPIO185"),	\
	PINCTRL_PIN(186, "PLGPIO186"),	\
	PINCTRL_PIN(187, "PLGPIO187"),	\
	PINCTRL_PIN(188, "PLGPIO188"),	\
	PINCTRL_PIN(189, "PLGPIO189"),	\
	PINCTRL_PIN(190, "PLGPIO190"),	\
	PINCTRL_PIN(191, "PLGPIO191"),	\
	PINCTRL_PIN(192, "PLGPIO192"),	\
	PINCTRL_PIN(193, "PLGPIO193"),	\
	PINCTRL_PIN(194, "PLGPIO194"),	\
	PINCTRL_PIN(195, "PLGPIO195"),	\
	PINCTRL_PIN(196, "PLGPIO196"),	\
	PINCTRL_PIN(197, "PLGPIO197"),	\
	PINCTRL_PIN(198, "PLGPIO198"),	\
	PINCTRL_PIN(199, "PLGPIO199"),	\
	PINCTRL_PIN(200, "PLGPIO200"),	\
	PINCTRL_PIN(201, "PLGPIO201"),	\
	PINCTRL_PIN(202, "PLGPIO202"),	\
	PINCTRL_PIN(203, "PLGPIO203"),	\
	PINCTRL_PIN(204, "PLGPIO204"),	\
	PINCTRL_PIN(205, "PLGPIO205"),	\
	PINCTRL_PIN(206, "PLGPIO206"),	\
	PINCTRL_PIN(207, "PLGPIO207"),	\
	PINCTRL_PIN(208, "PLGPIO208"),	\
	PINCTRL_PIN(209, "PLGPIO209"),	\
	PINCTRL_PIN(210, "PLGPIO210"),	\
	PINCTRL_PIN(211, "PLGPIO211"),	\
	PINCTRL_PIN(212, "PLGPIO212"),	\
	PINCTRL_PIN(213, "PLGPIO213"),	\
	PINCTRL_PIN(214, "PLGPIO214"),	\
	PINCTRL_PIN(215, "PLGPIO215"),	\
	PINCTRL_PIN(216, "PLGPIO216"),	\
	PINCTRL_PIN(217, "PLGPIO217"),	\
	PINCTRL_PIN(218, "PLGPIO218"),	\
	PINCTRL_PIN(219, "PLGPIO219"),	\
	PINCTRL_PIN(220, "PLGPIO220"),	\
	PINCTRL_PIN(221, "PLGPIO221"),	\
	PINCTRL_PIN(222, "PLGPIO222"),	\
	PINCTRL_PIN(223, "PLGPIO223"),	\
	PINCTRL_PIN(224, "PLGPIO224"),	\
	PINCTRL_PIN(225, "PLGPIO225"),	\
	PINCTRL_PIN(226, "PLGPIO226"),	\
	PINCTRL_PIN(227, "PLGPIO227"),	\
	PINCTRL_PIN(228, "PLGPIO228"),	\
	PINCTRL_PIN(229, "PLGPIO229"),	\
	PINCTRL_PIN(230, "PLGPIO230"),	\
	PINCTRL_PIN(231, "PLGPIO231"),	\
	PINCTRL_PIN(232, "PLGPIO232"),	\
	PINCTRL_PIN(233, "PLGPIO233"),	\
	PINCTRL_PIN(234, "PLGPIO234"),	\
	PINCTRL_PIN(235, "PLGPIO235"),	\
	PINCTRL_PIN(236, "PLGPIO236"),	\
	PINCTRL_PIN(237, "PLGPIO237"),	\
	PINCTRL_PIN(238, "PLGPIO238"),	\
	PINCTRL_PIN(239, "PLGPIO239"),	\
	PINCTRL_PIN(240, "PLGPIO240"),	\
	PINCTRL_PIN(241, "PLGPIO241"),	\
	PINCTRL_PIN(242, "PLGPIO242"),	\
	PINCTRL_PIN(243, "PLGPIO243"),	\
	PINCTRL_PIN(244, "PLGPIO244"),	\
	PINCTRL_PIN(245, "PLGPIO245")

#पूर्ण_अगर /* __PINMUX_SPEAR_H__ */
