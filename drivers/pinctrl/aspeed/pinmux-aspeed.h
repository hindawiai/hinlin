<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* Copyright (C) 2019 IBM Corp.  */

#अगर_अघोषित ASPEED_PINMUX_H
#घोषणा ASPEED_PINMUX_H

#समावेश <linux/regmap.h>
#समावेश <stdbool.h>

/*
 * The ASPEED SoCs provide typically more than 200 pins क्रम GPIO and other
 * functions. The SoC function enabled on a pin is determined on a priority
 * basis where a given pin can provide a number of dअगरferent संकेत types.
 *
 * The संकेत active on a pin is described by both a priority level and
 * compound logical expressions involving multiple चालकs, रेजिस्टरs and
 * bits. Some dअगरficulty arises as the pin's function bit masks क्रम each
 * priority level are frequently not the same (i.e. cannot just flip a bit to
 * change from a high to low priority संकेत), or even in the same रेजिस्टर.
 * Further, not all संकेतs can be unmuxed, as some expressions depend on
 * values in the hardware strapping रेजिस्टर (which may be treated as
 * पढ़ो-only).
 *
 * SoC Multi-function Pin Expression Examples
 * ------------------------------------------
 *
 * Here are some sample mux configurations from the AST2400 and AST2500
 * datasheets to illustrate the corner हालs, roughly in order of least to most
 * corner. The संकेत priorities are in decending order from P0 (highest).
 *
 * D6 is a pin with a single function (beside GPIO); a high priority संकेत
 * that participates in one function:
 *
 * Ball | Default | P0 Signal | P0 Expression               | P1 Signal | P1 Expression | Other
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *  D6    GPIOA0    MAC1LINK    SCU80[0]=1                                                GPIOA0
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *
 * C5 is a multi-संकेत pin (high and low priority संकेतs). Here we touch
 * dअगरferent रेजिस्टरs क्रम the dअगरferent functions that enable each संकेत:
 *
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *  C5    GPIOA4    SCL9        SCU90[22]=1                   TIMER5      SCU80[4]=1      GPIOA4
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *
 * E19 is a single-संकेत pin with two functions that influence the active
 * संकेत. In this हाल both bits have the same meaning - enable a dedicated
 * LPC reset pin. However it's not always the हाल that the bits in the
 * OR-relationship have the same meaning.
 *
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *  E19   GPIOB4    LPCRST#     SCU80[12]=1 | Strap[14]=1                                 GPIOB4
 * -----+---------+-----------+-----------------------------+-----------+---------------+----------
 *
 * For example, pin B19 has a low-priority संकेत that's enabled by two
 * distinct SoC functions: A specअगरic SIOPBI bit in रेजिस्टर SCUA4, and an ACPI
 * bit in the STRAP रेजिस्टर. The ACPI bit configures संकेतs on pins in
 * addition to B19. Both of the low priority functions as well as the high
 * priority function must be disabled क्रम GPIOF1 to be used.
 *
 * Ball | Default | P0 Signal | P0 Expression                           | P1 Signal | P1 Expression                          | Other
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *  B19   GPIOF1    NDCD4       SCU80[25]=1                               SIOPBI#     SCUA4[12]=1 | Strap[19]=0                GPIOF1
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *
 * For pin E18, the SoC ANDs the expected state of three bits to determine the
 * pin's active संकेत:
 *
 * * SCU3C[3]: Enable बाह्यal SOC reset function
 * * SCU80[15]: Enable SPICS1# or EXTRST# function pin
 * * SCU90[31]: Select SPI पूर्णांकerface CS# output
 *
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *  E18   GPIOB7    EXTRST#     SCU3C[3]=1 & SCU80[15]=1 & SCU90[31]=0    SPICS1#     SCU3C[3]=1 & SCU80[15]=1 & SCU90[31]=1   GPIOB7
 * -----+---------+-----------+-----------------------------------------+-----------+----------------------------------------+----------
 *
 * (Bits SCU3C[3] and SCU80[15] appear to only be used in the expressions क्रम
 * selecting the संकेतs on pin E18)
 *
 * Pin T5 is a multi-संकेत pin with a more complex configuration:
 *
 * Ball | Default | P0 Signal | P0 Expression                | P1 Signal | P1 Expression | Other
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *  T5    GPIOL1    VPIDE       SCU90[5:4]!=0 & SCU84[17]=1    NDCD1       SCU84[17]=1     GPIOL1
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *
 * The high priority संकेत configuration is best thought of in terms of its
 * exploded क्रमm, with reference to the SCU90[5:4] bits:
 *
 * * SCU90[5:4]=00: disable
 * * SCU90[5:4]=01: 18 bits (R6/G6/B6) video mode.
 * * SCU90[5:4]=10: 24 bits (R8/G8/B8) video mode.
 * * SCU90[5:4]=11: 30 bits (R10/G10/B10) video mode.
 *
 * Re-writing:
 *
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *  T5    GPIOL1    VPIDE      (SCU90[5:4]=1 & SCU84[17]=1)    NDCD1       SCU84[17]=1     GPIOL1
 *                             | (SCU90[5:4]=2 & SCU84[17]=1)
 *                             | (SCU90[5:4]=3 & SCU84[17]=1)
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *
 * For reference the SCU84[17] bit configure the "UART1 NDCD1 or Video VPIDE
 * function pin", where the संकेत itself is determined by whether SCU94[5:4]
 * is disabled or in one of the 18, 24 or 30bit video modes.
 *
 * Other video-input-related pins require an explicit state in SCU90[5:4], e.g.
 * W1 and U5:
 *
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *  W1    GPIOL6    VPIB0       SCU90[5:4]=3 & SCU84[22]=1     TXD1        SCU84[22]=1     GPIOL6
 *  U5    GPIOL7    VPIB1       SCU90[5:4]=3 & SCU84[23]=1     RXD1        SCU84[23]=1     GPIOL7
 * -----+---------+-----------+------------------------------+-----------+---------------+----------
 *
 * The examples of T5 and W1 are particularly fertile, as they also demonstrate
 * that despite operating as part of the video input bus each संकेत needs to
 * be enabled inभागidually via it's own SCU84 (in the हालs of T5 and W1)
 * रेजिस्टर bit. This is a little crazy अगर the bus करोesn't have optional
 * संकेतs, but is used to decent effect with some of the UARTs where not all
 * संकेतs are required. However, this isn't करोne consistently - UART1 is
 * enabled on a per-pin basis, and by contrast, all संकेतs क्रम UART6 are
 * enabled by a single bit.
 *
 * Further, the high and low priority संकेतs listed in the table above share
 * a configuration bit. The VPI संकेतs should operate in concert in a single
 * function, but the UART संकेतs should retain the ability to be configured
 * independently. This pushes the implementation करोwn the path of tagging a
 * संकेत's expressions with the function they participate in, rather than
 * defining masks affecting multiple संकेतs per function. The latter approach
 * fails in this instance where applying the configuration क्रम the UART pin of
 * पूर्णांकerest will stomp on the state of other UART संकेतs when disabling the
 * VPI functions on the current pin.
 *
 * Ball |  Default   | P0 Signal | P0 Expression             | P1 Signal | P1 Expression | Other
 * -----+------------+-----------+---------------------------+-----------+---------------+------------
 *  A12   RGMII1TXCK   GPIOT0      SCUA0[0]=1                  RMII1TXEN   Strap[6]=0      RGMII1TXCK
 *  B12   RGMII1TXCTL  GPIOT1      SCUA0[1]=1                  ै            Strap[6]=0      RGMII1TXCTL
 * -----+------------+-----------+---------------------------+-----------+---------------+------------
 *
 * A12 demonstrates that the "Other" संकेत isn't always GPIO - in this हाल
 * GPIOT0 is a high-priority संकेत and RGMII1TXCK is Other. Thus, GPIO
 * should be treated like any other संकेत type with full function expression
 * requirements, and not assumed to be the शेष हाल. Separately, GPIOT0 and
 * GPIOT1's संकेत descriptor bits are distinct, thereक्रमe we must iterate all
 * pins in the function's group to disable the higher-priority संकेतs such
 * that the संकेत क्रम the function of पूर्णांकerest is correctly enabled.
 *
 * Finally, three priority levels aren't always enough; the AST2500 brings with
 * it 18 pins of five priority levels, however the 18 pins only use three of
 * the five priority levels.
 *
 * Ultimately the requirement to control pins in the examples above drive the
 * design:
 *
 * * Pins provide संकेतs according to functions activated in the mux
 *   configuration
 *
 * * Pins provide up to five संकेत types in a priority order
 *
 * * For priorities levels defined on a pin, each priority provides one संकेत
 *
 * * Enabling lower priority संकेतs requires higher priority संकेतs be
 *   disabled
 *
 * * A function represents a set of संकेतs; functions are distinct अगर they
 *   करो not share a subset of संकेतs (and may be distinct अगर they are a
 *   strict subset).
 *
 * * Signals participate in one or more functions or groups
 *
 * * A function is described by an expression of one or more संकेत
 *   descriptors, which compare bit values in a रेजिस्टर
 *
 * * A संकेत expression is the smallest set of संकेत descriptors whose
 *   comparisons must evaluate 'true' क्रम a संकेत to be enabled on a pin.
 *
 * * A संकेत participating in a function is active on a pin अगर evaluating all
 *   संकेत descriptors in the pin's संकेत expression क्रम the function yields
 *   a 'true' result
 *
 * * A संकेत at a given priority on a given pin is active अगर any of the
 *   functions in which the संकेत participates are active, and no higher
 *   priority संकेत on the pin is active
 *
 * * GPIO is configured per-pin
 *
 * And so:
 *
 * * To disable a संकेत, any function(s) activating the संकेत must be
 *   disabled
 *
 * * Each pin must know the संकेत expressions of functions in which it
 *   participates, क्रम the purpose of enabling the Other function. This is करोne
 *   by deactivating all functions that activate higher priority संकेतs on the
 *   pin.
 *
 * As a concrete example:
 *
 * * T5 provides three संकेतs types: VPIDE, NDCD1 and GPIO
 *
 * * The VPIDE संकेत participates in 3 functions: VPI18, VPI24 and VPI30
 *
 * * The NDCD1 संकेत participates in just its own NDCD1 function
 *
 * * VPIDE is high priority, NDCD1 is low priority, and GPIOL1 is the least
 *   prioritised
 *
 * * The prerequisit क्रम activating the NDCD1 संकेत is that the VPI18, VPI24
 *   and VPI30 functions all be disabled
 *
 * * Similarly, all of VPI18, VPI24, VPI30 and NDCD1 functions must be disabled
 *   to provide GPIOL6
 *
 * Considerations
 * --------------
 *
 * If pinctrl allows us to allocate a pin we can configure a function without
 * concern क्रम the function of alपढ़ोy allocated pins, अगर pin groups are
 * created with respect to the SoC functions in which they participate. This is
 * पूर्णांकuitive, but it did not feel obvious from the bit/pin relationships.
 *
 * Conversely, failing to allocate all pins in a group indicates some bits (as
 * well as pins) required क्रम the group's configuration will alपढ़ोy be in use,
 * likely in a way that's inconsistent with the requirements of the failed
 * group.
 *
 * Implementation
 * --------------
 *
 * Beyond the करोcumentation below the various काष्ठाures and helper macros that
 * allow the implementation to hang together are defined. The macros are fairly
 * dense, so below we walk through some raw examples of the configuration
 * tables in an efक्रमt to clarअगरy the concepts.
 *
 * The complनिकासy of configuring the mux combined with the scale of the pins
 * and functions was a concern, so the table design aदीर्घ with the macro jungle
 * is an attempt to address it. The rough principles of the approach are:
 *
 * 1. Use a data-driven solution rather than embedding state पूर्णांकo code
 * 2. Minimise editing to the specअगरics of the given mux configuration
 * 3. Detect as many errors as possible at compile समय
 *
 * Addressing poपूर्णांक 3 leads to naming of symbols in terms of the four
 * properties associated with a given mux configuration: The pin, the संकेत,
 * the group and the function. In this way copy/paste errors cause duplicate
 * symbols to be defined, which prevents successful compilation. Failing to
 * properly parent the tables leads to unused symbol warnings, and use of
 * designated initialisers and additional warnings ensures that there are
 * no override errors in the pin, group and function arrays.
 *
 * Addressing poपूर्णांक 2 drives the development of the macro jungle, as it
 * centralises the definition noise at the cost of taking some समय to
 * understand.
 *
 * Here's a complete, concrete "pre-processed" example of the table काष्ठाures
 * used to describe the D6 ball from the examples above:
 *
 * ```
 * अटल स्थिर काष्ठा aspeed_sig_desc sig_descs_MAC1LINK_MAC1LINK[] = अणु
 *     अणु
 *         .ip = ASPEED_IP_SCU,
 *         .reg = 0x80,
 *         .mask = BIT(0),
 *         .enable = 1,
 *         .disable = 0
 *     पूर्ण,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr sig_expr_MAC1LINK_MAC1LINK = अणु
 *     .संकेत = "MAC1LINK",
 *     .function = "MAC1LINK",
 *     .ndescs = ARRAY_SIZE(sig_descs_MAC1LINK_MAC1LINK),
 *     .descs = &(sig_descs_MAC1LINK_MAC1LINK)[0],
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr *sig_exprs_MAC1LINK_MAC1LINK[] = अणु
 *     &sig_expr_MAC1LINK_MAC1LINK,
 *     शून्य,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_desc sig_descs_GPIOA0_GPIOA0[] = अणु पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr sig_expr_GPIOA0_GPIOA0 = अणु
 *     .संकेत = "GPIOA0",
 *     .function = "GPIOA0",
 *     .ndescs = ARRAY_SIZE(sig_descs_GPIOA0_GPIOA0),
 *     .descs = &(sig_descs_GPIOA0_GPIOA0)[0],
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr *sig_exprs_GPIOA0_GPIOA0[] = अणु
 *     &sig_expr_GPIOA0_GPIOA0,
 *     शून्य
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr **pin_exprs_0[] = अणु
 *     sig_exprs_MAC1LINK_MAC1LINK,
 *     sig_exprs_GPIOA0_GPIOA0,
 *     शून्य
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_pin_desc pin_0 = अणु "0", (&pin_exprs_0[0]) पूर्ण;
 * अटल स्थिर पूर्णांक group_pins_MAC1LINK[] = अणु 0 पूर्ण;
 * अटल स्थिर अक्षर *func_groups_MAC1LINK[] = अणु "MAC1LINK" पूर्ण;
 *
 * अटल काष्ठा pinctrl_pin_desc aspeed_g4_pins[] = अणु
 *     [0] = अणु .number = 0, .name = "D6", .drv_data = &pin_0 पूर्ण,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_pin_group aspeed_g4_groups[] = अणु
 *     अणु
 *         .name = "MAC1LINK",
 *         .pins = &(group_pins_MAC1LINK)[0],
 *         .npins = ARRAY_SIZE(group_pins_MAC1LINK),
 *     पूर्ण,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_pin_function aspeed_g4_functions[] = अणु
 *     अणु
 *         .name = "MAC1LINK",
 *         .groups = &func_groups_MAC1LINK[0],
 *         .ngroups = ARRAY_SIZE(func_groups_MAC1LINK),
 *     पूर्ण,
 * पूर्ण;
 * ```
 *
 * At the end of the day much of the above code is compressed पूर्णांकo the
 * following two lines:
 *
 * ```
 * #घोषणा D6 0
 * SSSF_PIN_DECL(D6, GPIOA0, MAC1LINK, SIG_DESC_SET(SCU80, 0));
 * ```
 *
 * The two examples below show just the dअगरferences from the example above.
 *
 * Ball E18 demonstrates a function, EXTRST, that requires multiple descriptors
 * be set क्रम it to be muxed:
 *
 * ```
 * अटल स्थिर काष्ठा aspeed_sig_desc sig_descs_EXTRST_EXTRST[] = अणु
 *     अणु
 *         .ip = ASPEED_IP_SCU,
 *         .reg = 0x3C,
 *         .mask = BIT(3),
 *         .enable = 1,
 *         .disable = 0
 *     पूर्ण,
 *     अणु
 *         .ip = ASPEED_IP_SCU,
 *         .reg = 0x80,
 *         .mask = BIT(15),
 *         .enable = 1,
 *         .disable = 0
 *     पूर्ण,
 *     अणु
 *         .ip = ASPEED_IP_SCU,
 *         .reg = 0x90,
 *         .mask = BIT(31),
 *         .enable = 0,
 *         .disable = 1
 *     पूर्ण,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr sig_expr_EXTRST_EXTRST = अणु
 *     .संकेत = "EXTRST",
 *     .function = "EXTRST",
 *     .ndescs = ARRAY_SIZE(sig_descs_EXTRST_EXTRST),
 *     .descs = &(sig_descs_EXTRST_EXTRST)[0],
 * पूर्ण;
 * ...
 * ```
 *
 * For ball E19, we have multiple functions enabling a single संकेत, LPCRST#.
 * The data काष्ठाures look like:
 *
 * अटल स्थिर काष्ठा aspeed_sig_desc sig_descs_LPCRST_LPCRST[] = अणु
 *     अणु
 *         .ip = ASPEED_IP_SCU,
 *         .reg = 0x80,
 *         .mask = BIT(12),
 *         .enable = 1,
 *         .disable = 0
 *     पूर्ण,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr sig_expr_LPCRST_LPCRST = अणु
 *     .संकेत = "LPCRST",
 *     .function = "LPCRST",
 *     .ndescs = ARRAY_SIZE(sig_descs_LPCRST_LPCRST),
 *     .descs = &(sig_descs_LPCRST_LPCRST)[0],
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_desc sig_descs_LPCRST_LPCRSTS[] = अणु
 *     अणु
 *         .ip = ASPEED_IP_SCU,
 *         .reg = 0x70,
 *         .mask = BIT(14),
 *         .enable = 1,
 *         .disable = 0
 *     पूर्ण,
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr sig_expr_LPCRST_LPCRSTS = अणु
 *     .संकेत = "LPCRST",
 *     .function = "LPCRSTS",
 *     .ndescs = ARRAY_SIZE(sig_descs_LPCRST_LPCRSTS),
 *     .descs = &(sig_descs_LPCRST_LPCRSTS)[0],
 * पूर्ण;
 *
 * अटल स्थिर काष्ठा aspeed_sig_expr *sig_exprs_LPCRST_LPCRST[] = अणु
 *     &sig_expr_LPCRST_LPCRST,
 *     &sig_expr_LPCRST_LPCRSTS,
 *     शून्य,
 * पूर्ण;
 * ...
 * ```
 *
 * Both expressions listed in the sig_exprs_LPCRST_LPCRST array need to be set
 * to disabled क्रम the associated GPIO to be muxed.
 *
 */

#घोषणा ASPEED_IP_SCU		0
#घोषणा ASPEED_IP_GFX		1
#घोषणा ASPEED_IP_LPC		2
#घोषणा ASPEED_NR_PINMUX_IPS	3

 /**
  * A संकेत descriptor, which describes the रेजिस्टर, bits and the
  * enable/disable values that should be compared or written.
  *
  * @ip: The IP block identअगरier, used as an index पूर्णांकo the regmap array in
  *      काष्ठा aspeed_pinctrl_data
  * @reg: The रेजिस्टर offset with respect to the base address of the IP block
  * @mask: The mask to apply to the रेजिस्टर. The lowest set bit of the mask is
  *        used to derive the shअगरt value.
  * @enable: The value that enables the function. Value should be in the LSBs,
  *          not at the position of the mask.
  * @disable: The value that disables the function. Value should be in the
  *           LSBs, not at the position of the mask.
  */
काष्ठा aspeed_sig_desc अणु
	अचिन्हित पूर्णांक ip;
	अचिन्हित पूर्णांक reg;
	u32 mask;
	u32 enable;
	u32 disable;
पूर्ण;

/**
 * Describes a संकेत expression. The expression is evaluated by ANDing the
 * evaluation of the descriptors.
 *
 * @संकेत: The संकेत name क्रम the priority level on the pin. If the संकेत
 *          type is GPIO, then the संकेत name must begin with the
 *          prefix "GPI", e.g. GPIOA0, GPIT0 etc.
 * @function: The name of the function the संकेत participates in क्रम the
 *            associated expression. For pin-specअगरic GPIO, the function
 *            name must match the संकेत name.
 * @ndescs: The number of संकेत descriptors in the expression
 * @descs: Poपूर्णांकer to an array of संकेत descriptors that comprise the
 *         function expression
 */
काष्ठा aspeed_sig_expr अणु
	स्थिर अक्षर *संकेत;
	स्थिर अक्षर *function;
	पूर्णांक ndescs;
	स्थिर काष्ठा aspeed_sig_desc *descs;
पूर्ण;

/**
 * A काष्ठा capturing the list of expressions enabling संकेतs at each priority
 * क्रम a given pin. The संकेत configuration क्रम a priority level is evaluated
 * by ORing the evaluation of the संकेत expressions in the respective
 * priority's list.
 *
 * @name: A name क्रम the pin
 * @prios: A poपूर्णांकer to an array of expression list poपूर्णांकers
 *
 */
काष्ठा aspeed_pin_desc अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा aspeed_sig_expr ***prios;
पूर्ण;

/* Macro hell */

#घोषणा SIG_DESC_IP_BIT(ip, reg, idx, val) \
	अणु ip, reg, BIT_MASK(idx), val, (((val) + 1) & 1) पूर्ण

/**
 * Short-hand macro क्रम describing an SCU descriptor enabled by the state of
 * one bit. The disable value is derived.
 *
 * @reg: The संकेत's associated रेजिस्टर, offset from base
 * @idx: The संकेत's bit index in the रेजिस्टर
 * @val: The value (0 or 1) that enables the function
 */
#घोषणा SIG_DESC_BIT(reg, idx, val) \
	SIG_DESC_IP_BIT(ASPEED_IP_SCU, reg, idx, val)

#घोषणा SIG_DESC_IP_SET(ip, reg, idx) SIG_DESC_IP_BIT(ip, reg, idx, 1)

/**
 * A further लघु-hand macro expanding to an SCU descriptor enabled by a set
 * bit.
 *
 * @reg: The रेजिस्टर, offset from base
 * @idx: The bit index in the रेजिस्टर
 */
#घोषणा SIG_DESC_SET(reg, idx) SIG_DESC_IP_BIT(ASPEED_IP_SCU, reg, idx, 1)
#घोषणा SIG_DESC_CLEAR(reg, idx) अणु ASPEED_IP_SCU, reg, BIT_MASK(idx), 0, 0 पूर्ण

#घोषणा SIG_DESC_LIST_SYM(sig, group) sig_descs_ ## sig ## _ ## group
#घोषणा SIG_DESC_LIST_DECL(sig, group, ...) \
	अटल स्थिर काष्ठा aspeed_sig_desc SIG_DESC_LIST_SYM(sig, group)[] = \
		अणु __VA_ARGS__ पूर्ण

#घोषणा SIG_EXPR_SYM(sig, group) sig_expr_ ## sig ## _ ## group
#घोषणा SIG_EXPR_DECL_(sig, group, func) \
	अटल स्थिर काष्ठा aspeed_sig_expr SIG_EXPR_SYM(sig, group) = \
	अणु \
		.संकेत = #sig, \
		.function = #func, \
		.ndescs = ARRAY_SIZE(SIG_DESC_LIST_SYM(sig, group)), \
		.descs = &(SIG_DESC_LIST_SYM(sig, group))[0], \
	पूर्ण

/**
 * Declare a संकेत expression.
 *
 * @sig: A macro symbol name क्रम the संकेत (is subjected to stringअगरication
 *        and token pasting)
 * @func: The function in which the संकेत is participating
 * @...: Signal descriptors that define the संकेत expression
 *
 * For example, the following declares the ROMD8 संकेत क्रम the ROM16 function:
 *
 *     SIG_EXPR_DECL(ROMD8, ROM16, ROM16, SIG_DESC_SET(SCU90, 6));
 *
 * And with multiple संकेत descriptors:
 *
 *     SIG_EXPR_DECL(ROMD8, ROM16S, ROM16S, SIG_DESC_SET(HW_STRAP1, 4),
 *              अणु HW_STRAP1, GENMASK(1, 0), 0, 0 पूर्ण);
 */
#घोषणा SIG_EXPR_DECL(sig, group, func, ...) \
	SIG_DESC_LIST_DECL(sig, group, __VA_ARGS__); \
	SIG_EXPR_DECL_(sig, group, func)

/**
 * Declare a poपूर्णांकer to a संकेत expression
 *
 * @sig: The macro symbol name क्रम the संकेत (subjected to token pasting)
 * @func: The macro symbol name क्रम the function (subjected to token pasting)
 */
#घोषणा SIG_EXPR_PTR(sig, group) (&SIG_EXPR_SYM(sig, group))

#घोषणा SIG_EXPR_LIST_SYM(sig, group) sig_exprs_ ## sig ## _ ## group

/**
 * Declare a संकेत expression list क्रम reference in a काष्ठा aspeed_pin_prio.
 *
 * @sig: A macro symbol name क्रम the संकेत (is subjected to token pasting)
 * @...: Signal expression काष्ठाure poपूर्णांकers (use SIG_EXPR_PTR())
 *
 * For example, the 16-bit ROM bus can be enabled by one of two possible संकेत
 * expressions:
 *
 *     SIG_EXPR_DECL(ROMD8, ROM16, ROM16, SIG_DESC_SET(SCU90, 6));
 *     SIG_EXPR_DECL(ROMD8, ROM16S, ROM16S, SIG_DESC_SET(HW_STRAP1, 4),
 *              अणु HW_STRAP1, GENMASK(1, 0), 0, 0 पूर्ण);
 *     SIG_EXPR_LIST_DECL(ROMD8, SIG_EXPR_PTR(ROMD8, ROM16),
 *              SIG_EXPR_PTR(ROMD8, ROM16S));
 */
#घोषणा SIG_EXPR_LIST_DECL(sig, group, ...) \
	अटल स्थिर काष्ठा aspeed_sig_expr *SIG_EXPR_LIST_SYM(sig, group)[] =\
		अणु __VA_ARGS__, शून्य पूर्ण

#घोषणा stringअगरy(x) #x
#घोषणा istringअगरy(x) stringअगरy(x)

/**
 * Create an expression symbol alias from (संकेत, group) to (pin, संकेत).
 *
 * @pin: The pin number
 * @sig: The संकेत name
 * @group: The name of the group of which the pin is a member that is
 *         associated with the function's संकेत
 *
 * Using an alias in this way enables detection of copy/paste errors (defining
 * the संकेत क्रम a group multiple बार) whilst enabling multiple pin groups
 * to exist क्रम a संकेत without पूर्णांकrusive side-effects on defining the list of
 * संकेतs available on a pin.
 */
#घोषणा SIG_EXPR_LIST_ALIAS(pin, sig, group) \
	अटल स्थिर काष्ठा aspeed_sig_expr *\
		SIG_EXPR_LIST_SYM(pin, sig)[ARRAY_SIZE(SIG_EXPR_LIST_SYM(sig, group))] \
		__attribute__((alias(istringअगरy(SIG_EXPR_LIST_SYM(sig, group)))))

/**
 * A लघु-hand macro क्रम declaring a function expression and an expression
 * list with a single expression (SE) and a single group (SG) of pins.
 *
 * @pin: The pin the संकेत will be routed to
 * @sig: The संकेत that will be routed to the pin क्रम the function
 * @func: A macro symbol name क्रम the function
 * @...: Function descriptors that define the function expression
 *
 * For example, संकेत NCTS6 participates in its own function with one group:
 *
 *     SIG_EXPR_LIST_DECL_SINGLE(A18, NCTS6, NCTS6, SIG_DESC_SET(SCU90, 7));
 */
#घोषणा SIG_EXPR_LIST_DECL_SESG(pin, sig, func, ...) \
	SIG_DESC_LIST_DECL(sig, func, __VA_ARGS__); \
	SIG_EXPR_DECL_(sig, func, func); \
	SIG_EXPR_LIST_DECL(sig, func, SIG_EXPR_PTR(sig, func)); \
	SIG_EXPR_LIST_ALIAS(pin, sig, func)

/**
 * Similar to the above, but क्रम pins with a single expression (SE) and
 * multiple groups (MG) of pins.
 *
 * @pin: The pin the संकेत will be routed to
 * @sig: The संकेत that will be routed to the pin क्रम the function
 * @group: The name of the function's pin group in which the pin participates
 * @func: A macro symbol name क्रम the function
 * @...: Function descriptors that define the function expression
 */
#घोषणा SIG_EXPR_LIST_DECL_SEMG(pin, sig, group, func, ...) \
	SIG_DESC_LIST_DECL(sig, group, __VA_ARGS__); \
	SIG_EXPR_DECL_(sig, group, func); \
	SIG_EXPR_LIST_DECL(sig, group, SIG_EXPR_PTR(sig, group)); \
	SIG_EXPR_LIST_ALIAS(pin, sig, group)

/**
 * Similar to the above, but क्रम pins with a dual expressions (DE) and
 * and a single group (SG) of pins.
 *
 * @pin: The pin the संकेत will be routed to
 * @sig: The संकेत that will be routed to the pin क्रम the function
 * @group: The name of the function's pin group in which the pin participates
 * @func: A macro symbol name क्रम the function
 * @...: Function descriptors that define the function expression
 */
#घोषणा SIG_EXPR_LIST_DECL_DESG(pin, sig, f0, f1) \
	SIG_EXPR_LIST_DECL(sig, f0, \
			   SIG_EXPR_PTR(sig, f0), \
			   SIG_EXPR_PTR(sig, f1)); \
	SIG_EXPR_LIST_ALIAS(pin, sig, f0)

#घोषणा SIG_EXPR_LIST_PTR(sig, group) SIG_EXPR_LIST_SYM(sig, group)

#घोषणा PIN_EXPRS_SYM(pin) pin_exprs_ ## pin
#घोषणा PIN_EXPRS_PTR(pin) (&PIN_EXPRS_SYM(pin)[0])
#घोषणा PIN_SYM(pin) pin_ ## pin

#घोषणा PIN_DECL_(pin, ...) \
	अटल स्थिर काष्ठा aspeed_sig_expr **PIN_EXPRS_SYM(pin)[] = \
		अणु __VA_ARGS__, शून्य पूर्ण; \
	अटल स्थिर काष्ठा aspeed_pin_desc PIN_SYM(pin) = \
		अणु #pin, PIN_EXPRS_PTR(pin) पूर्ण

/**
 * Declare a single संकेत pin
 *
 * @pin: The pin number
 * @other: Macro name क्रम "other" functionality (subjected to stringअगरication)
 * @sig: Macro name क्रम the संकेत (subjected to stringअगरication)
 *
 * For example:
 *
 *     #घोषणा E3 80
 *     SIG_EXPR_LIST_DECL_SINGLE(SCL5, I2C5, I2C5_DESC);
 *     PIN_DECL_1(E3, GPIOK0, SCL5);
 */
#घोषणा PIN_DECL_1(pin, other, sig) \
	SIG_EXPR_LIST_DECL_SESG(pin, other, other); \
	PIN_DECL_(pin, SIG_EXPR_LIST_PTR(pin, sig), \
		  SIG_EXPR_LIST_PTR(pin, other))

/**
 * Single संकेत, single function pin declaration
 *
 * @pin: The pin number
 * @other: Macro name क्रम "other" functionality (subjected to stringअगरication)
 * @sig: Macro name क्रम the संकेत (subjected to stringअगरication)
 * @...: Signal descriptors that define the function expression
 *
 * For example:
 *
 *    SSSF_PIN_DECL(A4, GPIOA2, TIMER3, SIG_DESC_SET(SCU80, 2));
 */
#घोषणा SSSF_PIN_DECL(pin, other, sig, ...) \
	SIG_EXPR_LIST_DECL_SESG(pin, sig, sig, __VA_ARGS__); \
	SIG_EXPR_LIST_DECL_SESG(pin, other, other); \
	PIN_DECL_(pin, SIG_EXPR_LIST_PTR(pin, sig), \
		  SIG_EXPR_LIST_PTR(pin, other)); \
	FUNC_GROUP_DECL(sig, pin)
/**
 * Declare a two-संकेत pin
 *
 * @pin: The pin number
 * @other: Macro name क्रम "other" functionality (subjected to stringअगरication)
 * @high: Macro name क्रम the highest priority संकेत functions
 * @low: Macro name क्रम the low संकेत functions
 *
 * For example:
 *
 *     #घोषणा A8 56
 *     SIG_EXPR_DECL(ROMD8, ROM16, SIG_DESC_SET(SCU90, 6));
 *     SIG_EXPR_DECL(ROMD8, ROM16S, SIG_DESC_SET(HW_STRAP1, 4),
 *              अणु HW_STRAP1, GENMASK(1, 0), 0, 0 पूर्ण);
 *     SIG_EXPR_LIST_DECL(ROMD8, SIG_EXPR_PTR(ROMD8, ROM16),
 *              SIG_EXPR_PTR(ROMD8, ROM16S));
 *     SIG_EXPR_LIST_DECL_SINGLE(NCTS6, NCTS6, SIG_DESC_SET(SCU90, 7));
 *     PIN_DECL_2(A8, GPIOH0, ROMD8, NCTS6);
 */
#घोषणा PIN_DECL_2(pin, other, high, low) \
	SIG_EXPR_LIST_DECL_SESG(pin, other, other); \
	PIN_DECL_(pin, \
			SIG_EXPR_LIST_PTR(pin, high), \
			SIG_EXPR_LIST_PTR(pin, low), \
			SIG_EXPR_LIST_PTR(pin, other))

#घोषणा PIN_DECL_3(pin, other, high, medium, low) \
	SIG_EXPR_LIST_DECL_SESG(pin, other, other); \
	PIN_DECL_(pin, \
			SIG_EXPR_LIST_PTR(pin, high), \
			SIG_EXPR_LIST_PTR(pin, medium), \
			SIG_EXPR_LIST_PTR(pin, low), \
			SIG_EXPR_LIST_PTR(pin, other))

#घोषणा GROUP_SYM(group) group_pins_ ## group
#घोषणा GROUP_DECL(group, ...) \
	अटल स्थिर पूर्णांक GROUP_SYM(group)[] = अणु __VA_ARGS__ पूर्ण

#घोषणा FUNC_SYM(func) func_groups_ ## func
#घोषणा FUNC_DECL_(func, ...) \
	अटल स्थिर अक्षर *FUNC_SYM(func)[] = अणु __VA_ARGS__ पूर्ण

#घोषणा FUNC_DECL_1(func, group) FUNC_DECL_(func, #group)
#घोषणा FUNC_DECL_2(func, one, two) FUNC_DECL_(func, #one, #two)
#घोषणा FUNC_DECL_3(func, one, two, three) FUNC_DECL_(func, #one, #two, #three)

#घोषणा FUNC_GROUP_DECL(func, ...) \
	GROUP_DECL(func, __VA_ARGS__); \
	FUNC_DECL_(func, #func)


#घोषणा GPIO_PIN_DECL(pin, gpio) \
	SIG_EXPR_LIST_DECL_SESG(pin, gpio, gpio); \
	PIN_DECL_(pin, SIG_EXPR_LIST_PTR(pin, gpio))

काष्ठा aspeed_pin_group अणु
	स्थिर अक्षर *name;
	स्थिर अचिन्हित पूर्णांक *pins;
	स्थिर अचिन्हित पूर्णांक npins;
पूर्ण;

#घोषणा ASPEED_PINCTRL_GROUP(name_) अणु \
	.name = #name_, \
	.pins = &(GROUP_SYM(name_))[0], \
	.npins = ARRAY_SIZE(GROUP_SYM(name_)), \
पूर्ण

काष्ठा aspeed_pin_function अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *स्थिर *groups;
	अचिन्हित पूर्णांक ngroups;
पूर्ण;

#घोषणा ASPEED_PINCTRL_FUNC(name_, ...) अणु \
	.name = #name_, \
	.groups = &FUNC_SYM(name_)[0], \
	.ngroups = ARRAY_SIZE(FUNC_SYM(name_)), \
पूर्ण

काष्ठा aspeed_pinmux_data;

काष्ठा aspeed_pinmux_ops अणु
	पूर्णांक (*eval)(काष्ठा aspeed_pinmux_data *ctx,
		    स्थिर काष्ठा aspeed_sig_expr *expr, bool enabled);
	पूर्णांक (*set)(काष्ठा aspeed_pinmux_data *ctx,
		   स्थिर काष्ठा aspeed_sig_expr *expr, bool enabled);
पूर्ण;

काष्ठा aspeed_pinmux_data अणु
	काष्ठा device *dev;
	काष्ठा regmap *maps[ASPEED_NR_PINMUX_IPS];

	स्थिर काष्ठा aspeed_pinmux_ops *ops;

	स्थिर काष्ठा aspeed_pin_group *groups;
	स्थिर अचिन्हित पूर्णांक ngroups;

	स्थिर काष्ठा aspeed_pin_function *functions;
	स्थिर अचिन्हित पूर्णांक nfunctions;
पूर्ण;

पूर्णांक aspeed_sig_desc_eval(स्थिर काष्ठा aspeed_sig_desc *desc, bool enabled,
			 काष्ठा regmap *map);

पूर्णांक aspeed_sig_expr_eval(काष्ठा aspeed_pinmux_data *ctx,
			 स्थिर काष्ठा aspeed_sig_expr *expr, bool enabled);

अटल अंतरभूत पूर्णांक aspeed_sig_expr_set(काष्ठा aspeed_pinmux_data *ctx,
				      स्थिर काष्ठा aspeed_sig_expr *expr,
				      bool enabled)
अणु
	वापस ctx->ops->set(ctx, expr, enabled);
पूर्ण

#पूर्ण_अगर /* ASPEED_PINMUX_H */
