<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2018-2019 SiFive, Inc.
 * Wesley Terpstra
 * Paul Walmsley
 */

#अगर_अघोषित __LINUX_CLK_ANALOGBITS_WRPLL_CLN28HPC_H
#घोषणा __LINUX_CLK_ANALOGBITS_WRPLL_CLN28HPC_H

#समावेश <linux/types.h>

/* DIVQ_VALUES: number of valid DIVQ values */
#घोषणा DIVQ_VALUES				6

/*
 * Bit definitions क्रम काष्ठा wrpll_cfg.flags
 *
 * WRPLL_FLAGS_BYPASS_FLAG: अगर set, the PLL is either in bypass, or should be
 *	programmed to enter bypass
 * WRPLL_FLAGS_RESET_FLAG: अगर set, the PLL is in reset
 * WRPLL_FLAGS_INT_FEEDBACK_FLAG: अगर set, the PLL is configured क्रम पूर्णांकernal
 *	feedback mode
 * WRPLL_FLAGS_EXT_FEEDBACK_FLAG: अगर set, the PLL is configured क्रम बाह्यal
 *	feedback mode (not yet supported by this driver)
 */
#घोषणा WRPLL_FLAGS_BYPASS_SHIFT		0
#घोषणा WRPLL_FLAGS_BYPASS_MASK		BIT(WRPLL_FLAGS_BYPASS_SHIFT)
#घोषणा WRPLL_FLAGS_RESET_SHIFT		1
#घोषणा WRPLL_FLAGS_RESET_MASK		BIT(WRPLL_FLAGS_RESET_SHIFT)
#घोषणा WRPLL_FLAGS_INT_FEEDBACK_SHIFT	2
#घोषणा WRPLL_FLAGS_INT_FEEDBACK_MASK	BIT(WRPLL_FLAGS_INT_FEEDBACK_SHIFT)
#घोषणा WRPLL_FLAGS_EXT_FEEDBACK_SHIFT	3
#घोषणा WRPLL_FLAGS_EXT_FEEDBACK_MASK	BIT(WRPLL_FLAGS_EXT_FEEDBACK_SHIFT)

/**
 * काष्ठा wrpll_cfg - WRPLL configuration values
 * @भागr: reference भागider value (6 bits), as presented to the PLL संकेतs
 * @भागf: feedback भागider value (9 bits), as presented to the PLL संकेतs
 * @भागq: output भागider value (3 bits), as presented to the PLL संकेतs
 * @flags: PLL configuration flags.  See above क्रम more inक्रमmation
 * @range: PLL loop filter range.  See below क्रम more inक्रमmation
 * @output_rate_cache: cached output rates, swept across DIVQ
 * @parent_rate: PLL refclk rate क्रम which values are valid
 * @max_r: maximum possible R भागider value, given @parent_rate
 * @init_r: initial R भागider value to start the search from
 *
 * @भागr, @भागq, @भागq, @range represent what the PLL expects to see
 * on its input संकेतs.  Thus @भागr and @भागf are the actual भागisors
 * minus one.  @भागq is a घातer-of-two भागider; क्रम example, 1 =
 * भागide-by-2 and 6 = भागide-by-64.  0 is an invalid @भागq value.
 *
 * When initially passing a काष्ठा wrpll_cfg record, the
 * record should be zero-initialized with the exception of the @flags
 * field.  The only flag bits that need to be set are either
 * WRPLL_FLAGS_INT_FEEDBACK or WRPLL_FLAGS_EXT_FEEDBACK.
 */
काष्ठा wrpll_cfg अणु
	u8 भागr;
	u8 भागq;
	u8 range;
	u8 flags;
	u16 भागf;
/* निजी: */
	u32 output_rate_cache[DIVQ_VALUES];
	अचिन्हित दीर्घ parent_rate;
	u8 max_r;
	u8 init_r;
पूर्ण;

पूर्णांक wrpll_configure_क्रम_rate(काष्ठा wrpll_cfg *c, u32 target_rate,
			     अचिन्हित दीर्घ parent_rate);

अचिन्हित पूर्णांक wrpll_calc_max_lock_us(स्थिर काष्ठा wrpll_cfg *c);

अचिन्हित दीर्घ wrpll_calc_output_rate(स्थिर काष्ठा wrpll_cfg *c,
				     अचिन्हित दीर्घ parent_rate);

#पूर्ण_अगर /* __LINUX_CLK_ANALOGBITS_WRPLL_CLN28HPC_H */
