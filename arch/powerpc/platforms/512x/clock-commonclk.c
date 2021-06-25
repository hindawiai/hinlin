<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2013 DENX Software Engineering
 *
 * Gerhard Sittig, <gsi@denx.de>
 *
 * common घड़ी driver support क्रम the MPC512x platक्रमm
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>

#समावेश <यंत्र/mpc5121.h>
#समावेश <dt-bindings/घड़ी/mpc512x-घड़ी.h>

#समावेश "mpc512x.h"		/* our खुला mpc5121_clk_init() API */

/* helpers to keep the MCLK पूर्णांकermediates "somewhere" in our table */
क्रमागत अणु
	MCLK_IDX_MUX0,
	MCLK_IDX_EN0,
	MCLK_IDX_DIV0,
	MCLK_MAX_IDX,
पूर्ण;

#घोषणा NR_PSCS			12
#घोषणा NR_MSCANS		4
#घोषणा NR_SPDIFS		1
#घोषणा NR_OUTCLK		4
#घोषणा NR_MCLKS		(NR_PSCS + NR_MSCANS + NR_SPDIFS + NR_OUTCLK)

/* extend the खुला set of घड़ीs by adding पूर्णांकernal slots क्रम management */
क्रमागत अणु
	/* arrange क्रम adjacent numbers after the खुला set */
	MPC512x_CLK_START_PRIVATE = MPC512x_CLK_LAST_PUBLIC,
	/* घड़ीs which aren't announced to the खुला */
	MPC512x_CLK_DDR,
	MPC512x_CLK_MEM,
	MPC512x_CLK_IIM,
	/* पूर्णांकermediates in भाग+gate combos or fractional भागiders */
	MPC512x_CLK_DDR_UG,
	MPC512x_CLK_SDHC_x4,
	MPC512x_CLK_SDHC_UG,
	MPC512x_CLK_SDHC2_UG,
	MPC512x_CLK_DIU_x4,
	MPC512x_CLK_DIU_UG,
	MPC512x_CLK_MBX_BUS_UG,
	MPC512x_CLK_MBX_UG,
	MPC512x_CLK_MBX_3D_UG,
	MPC512x_CLK_PCI_UG,
	MPC512x_CLK_NFC_UG,
	MPC512x_CLK_LPC_UG,
	MPC512x_CLK_SPDIF_TX_IN,
	/* पूर्णांकermediates क्रम the mux+gate+भाग+mux MCLK generation */
	MPC512x_CLK_MCLKS_FIRST,
	MPC512x_CLK_MCLKS_LAST = MPC512x_CLK_MCLKS_FIRST
				+ NR_MCLKS * MCLK_MAX_IDX,
	/* पूर्णांकernal, symbolic spec क्रम the number of slots */
	MPC512x_CLK_LAST_PRIVATE,
पूर्ण;

/* data required क्रम the OF घड़ी provider registration */
अटल काष्ठा clk *clks[MPC512x_CLK_LAST_PRIVATE];
अटल काष्ठा clk_onecell_data clk_data;

/* CCM रेजिस्टर access */
अटल काष्ठा mpc512x_ccm __iomem *clkregs;
अटल DEFINE_SPINLOCK(clklock);

/* SoC variants अणुअणुअणु */

/*
 * tell SoC variants apart as they are rather similar yet not identical,
 * cache the result in an क्रमागत to not repeatedly run the expensive OF test
 *
 * MPC5123 is an MPC5121 without the MBX graphics accelerator
 *
 * MPC5125 has many more dअगरferences: no MBX, no AXE, no VIU, no SPDIF,
 * no PATA, no SATA, no PCI, two FECs (of dअगरferent compatibility name),
 * only 10 PSCs (of dअगरferent compatibility name), two SDHCs, dअगरferent
 * NFC IP block, output घड़ीs, प्रणाली PLL status query, dअगरferent CPMF
 * पूर्णांकerpretation, no CFM, dअगरferent fourth PSC/CAN mux0 input -- yet
 * those dअगरferences can get folded पूर्णांकo this घड़ी provider support
 * code and करोn't warrant a separate highly redundant implementation
 */

अटल क्रमागत soc_type अणु
	MPC512x_SOC_MPC5121,
	MPC512x_SOC_MPC5123,
	MPC512x_SOC_MPC5125,
पूर्ण soc;

अटल व्योम mpc512x_clk_determine_soc(व्योम)
अणु
	अगर (of_machine_is_compatible("fsl,mpc5121")) अणु
		soc = MPC512x_SOC_MPC5121;
		वापस;
	पूर्ण
	अगर (of_machine_is_compatible("fsl,mpc5123")) अणु
		soc = MPC512x_SOC_MPC5123;
		वापस;
	पूर्ण
	अगर (of_machine_is_compatible("fsl,mpc5125")) अणु
		soc = MPC512x_SOC_MPC5125;
		वापस;
	पूर्ण
पूर्ण

अटल bool soc_has_mbx(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5121)
		वापस true;
	वापस false;
पूर्ण

अटल bool soc_has_axe(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस false;
	वापस true;
पूर्ण

अटल bool soc_has_viu(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस false;
	वापस true;
पूर्ण

अटल bool soc_has_spdअगर(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस false;
	वापस true;
पूर्ण

अटल bool soc_has_pata(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस false;
	वापस true;
पूर्ण

अटल bool soc_has_sata(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस false;
	वापस true;
पूर्ण

अटल bool soc_has_pci(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस false;
	वापस true;
पूर्ण

अटल bool soc_has_fec2(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक soc_max_pscnum(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस 10;
	वापस 12;
पूर्ण

अटल bool soc_has_sdhc2(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस true;
	वापस false;
पूर्ण

अटल bool soc_has_nfc_5125(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस true;
	वापस false;
पूर्ण

अटल bool soc_has_outclk(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस true;
	वापस false;
पूर्ण

अटल bool soc_has_cpmf_0_bypass(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस true;
	वापस false;
पूर्ण

अटल bool soc_has_mclk_mux0_canin(व्योम)
अणु
	अगर (soc == MPC512x_SOC_MPC5125)
		वापस true;
	वापस false;
पूर्ण

/* पूर्णपूर्णपूर्ण SoC variants */
/* common clk API wrappers अणुअणुअणु */

/* convenience wrappers around the common clk API */
अटल अंतरभूत काष्ठा clk *mpc512x_clk_fixed(स्थिर अक्षर *name, पूर्णांक rate)
अणु
	वापस clk_रेजिस्टर_fixed_rate(शून्य, name, शून्य, 0, rate);
पूर्ण

अटल अंतरभूत काष्ठा clk *mpc512x_clk_factor(
	स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
	पूर्णांक mul, पूर्णांक भाग)
अणु
	पूर्णांक clkflags;

	clkflags = CLK_SET_RATE_PARENT;
	वापस clk_रेजिस्टर_fixed_factor(शून्य, name, parent_name, clkflags,
					 mul, भाग);
पूर्ण

अटल अंतरभूत काष्ठा clk *mpc512x_clk_भागider(
	स्थिर अक्षर *name, स्थिर अक्षर *parent_name, u8 clkflags,
	u32 __iomem *reg, u8 pos, u8 len, पूर्णांक भागflags)
अणु
	भागflags |= CLK_DIVIDER_BIG_ENDIAN;
	वापस clk_रेजिस्टर_भागider(शून्य, name, parent_name, clkflags,
				    reg, pos, len, भागflags, &clklock);
पूर्ण

अटल अंतरभूत काष्ठा clk *mpc512x_clk_भागtable(
	स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
	u32 __iomem *reg, u8 pos, u8 len,
	स्थिर काष्ठा clk_भाग_प्रकारable *भागtab)
अणु
	u8 भागflags;

	भागflags = CLK_DIVIDER_BIG_ENDIAN;
	वापस clk_रेजिस्टर_भागider_table(शून्य, name, parent_name, 0,
					  reg, pos, len, भागflags,
					  भागtab, &clklock);
पूर्ण

अटल अंतरभूत काष्ठा clk *mpc512x_clk_gated(
	स्थिर अक्षर *name, स्थिर अक्षर *parent_name,
	u32 __iomem *reg, u8 pos)
अणु
	पूर्णांक clkflags;
	u8 gateflags;

	clkflags = CLK_SET_RATE_PARENT;
	gateflags = CLK_GATE_BIG_ENDIAN;
	वापस clk_रेजिस्टर_gate(शून्य, name, parent_name, clkflags,
				 reg, pos, gateflags, &clklock);
पूर्ण

अटल अंतरभूत काष्ठा clk *mpc512x_clk_muxed(स्थिर अक्षर *name,
	स्थिर अक्षर **parent_names, पूर्णांक parent_count,
	u32 __iomem *reg, u8 pos, u8 len)
अणु
	पूर्णांक clkflags;
	u8 muxflags;

	clkflags = CLK_SET_RATE_PARENT;
	muxflags = CLK_MUX_BIG_ENDIAN;
	वापस clk_रेजिस्टर_mux(शून्य, name,
				parent_names, parent_count, clkflags,
				reg, pos, len, muxflags, &clklock);
पूर्ण

/* पूर्णपूर्णपूर्ण common clk API wrappers */

/* helper to isolate a bit field from a रेजिस्टर */
अटल अंतरभूत पूर्णांक get_bit_field(uपूर्णांक32_t __iomem *reg, uपूर्णांक8_t pos, uपूर्णांक8_t len)
अणु
	uपूर्णांक32_t val;

	val = in_be32(reg);
	val >>= pos;
	val &= (1 << len) - 1;
	वापस val;
पूर्ण

/* get the SPMF and translate it पूर्णांकo the "sys pll" multiplier */
अटल पूर्णांक get_spmf_mult(व्योम)
अणु
	अटल पूर्णांक spmf_to_mult[] = अणु
		68, 1, 12, 16, 20, 24, 28, 32,
		36, 40, 44, 48, 52, 56, 60, 64,
	पूर्ण;
	पूर्णांक spmf;

	spmf = get_bit_field(&clkregs->spmr, 24, 4);
	वापस spmf_to_mult[spmf];
पूर्ण

/*
 * get the SYS_DIV value and translate it पूर्णांकo a भागide factor
 *
 * values वापसed from here are a multiple of the real factor since the
 * भागide ratio is fractional
 */
अटल पूर्णांक get_sys_भाग_x2(व्योम)
अणु
	अटल पूर्णांक sysभाग_code_to_x2[] = अणु
		4, 5, 6, 7, 8, 9, 10, 14,
		12, 16, 18, 22, 20, 24, 26, 30,
		28, 32, 34, 38, 36, 40, 42, 46,
		44, 48, 50, 54, 52, 56, 58, 62,
		60, 64, 66,
	पूर्ण;
	पूर्णांक भागcode;

	भागcode = get_bit_field(&clkregs->scfr2, 26, 6);
	वापस sysभाग_code_to_x2[भागcode];
पूर्ण

/*
 * get the CPMF value and translate it पूर्णांकo a multiplier factor
 *
 * values वापसed from here are a multiple of the real factor since the
 * multiplier ratio is fractional
 */
अटल पूर्णांक get_cpmf_mult_x2(व्योम)
अणु
	अटल पूर्णांक cpmf_to_mult_x36[] = अणु
		/* 0b000 is "times 36" */
		72, 2, 2, 3, 4, 5, 6, 7,
	पूर्ण;
	अटल पूर्णांक cpmf_to_mult_0by[] = अणु
		/* 0b000 is "bypass" */
		2, 2, 2, 3, 4, 5, 6, 7,
	पूर्ण;

	पूर्णांक *cpmf_to_mult;
	पूर्णांक cpmf;

	cpmf = get_bit_field(&clkregs->spmr, 16, 4);
	अगर (soc_has_cpmf_0_bypass())
		cpmf_to_mult = cpmf_to_mult_0by;
	अन्यथा
		cpmf_to_mult = cpmf_to_mult_x36;
	वापस cpmf_to_mult[cpmf];
पूर्ण

/*
 * some of the घड़ी भागiders करो scale in a linear way, yet not all of
 * their bit combinations are legal; use a भागider table to get a
 * resulting set of applicable भागider values
 */

/* applies to the IPS_DIV, and PCI_DIV values */
अटल स्थिर काष्ठा clk_भाग_प्रकारable भागtab_2346[] = अणु
	अणु .val = 2, .भाग = 2, पूर्ण,
	अणु .val = 3, .भाग = 3, पूर्ण,
	अणु .val = 4, .भाग = 4, पूर्ण,
	अणु .val = 6, .भाग = 6, पूर्ण,
	अणु .भाग = 0, पूर्ण,
पूर्ण;

/* applies to the MBX_DIV, LPC_DIV, and NFC_DIV values */
अटल स्थिर काष्ठा clk_भाग_प्रकारable भागtab_1234[] = अणु
	अणु .val = 1, .भाग = 1, पूर्ण,
	अणु .val = 2, .भाग = 2, पूर्ण,
	अणु .val = 3, .भाग = 3, पूर्ण,
	अणु .val = 4, .भाग = 4, पूर्ण,
	अणु .भाग = 0, पूर्ण,
पूर्ण;

अटल पूर्णांक get_freq_from_dt(अक्षर *propname)
अणु
	काष्ठा device_node *np;
	स्थिर अचिन्हित पूर्णांक *prop;
	पूर्णांक val;

	val = 0;
	np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-immr");
	अगर (np) अणु
		prop = of_get_property(np, propname, शून्य);
		अगर (prop)
			val = *prop;
	    of_node_put(np);
	पूर्ण
	वापस val;
पूर्ण

अटल व्योम mpc512x_clk_preset_data(व्योम)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(clks); i++)
		clks[i] = ERR_PTR(-ENODEV);
पूर्ण

/*
 * - receives the "bus frequency" from the caller (that's the IPS घड़ी
 *   rate, the historical source of घड़ी inक्रमmation)
 * - fetches the प्रणाली PLL multiplier and भागider values as well as the
 *   IPS भागider value from hardware
 * - determines the REF घड़ी rate either from the XTAL/OSC spec (अगर
 *   there is a device tree node describing the oscillator) or from the
 *   IPS bus घड़ी (supported क्रम backwards compatibility, such that
 *   setups without XTAL/OSC specs keep working)
 * - creates the "ref" घड़ी item in the घड़ी tree, such that
 *   subsequent code can create the reमुख्यder of the hierarchy (REF ->
 *   SYS -> CSB -> IPS) from the REF घड़ी rate and the वापसed mul/भाग
 *   values
 */
अटल व्योम mpc512x_clk_setup_ref_घड़ी(काष्ठा device_node *np, पूर्णांक bus_freq,
					पूर्णांक *sys_mul, पूर्णांक *sys_भाग,
					पूर्णांक *ips_भाग)
अणु
	काष्ठा clk *osc_clk;
	पूर्णांक calc_freq;

	/* fetch mul/भाग factors from the hardware */
	*sys_mul = get_spmf_mult();
	*sys_mul *= 2;		/* compensate क्रम the fractional भागider */
	*sys_भाग = get_sys_भाग_x2();
	*ips_भाग = get_bit_field(&clkregs->scfr1, 23, 3);

	/* lookup the oscillator घड़ी क्रम its rate */
	osc_clk = of_clk_get_by_name(np, "osc");

	/*
	 * either descend from OSC to REF (and in bypassing verअगरy the
	 * IPS rate), or backtrack from IPS and multiplier values that
	 * were fetched from hardware to REF and thus to the OSC value
	 *
	 * in either हाल the REF घड़ी माला_लो created here and the
	 * reमुख्यder of the घड़ी tree can get spanned from there
	 */
	अगर (!IS_ERR(osc_clk)) अणु
		clks[MPC512x_CLK_REF] = mpc512x_clk_factor("ref", "osc", 1, 1);
		calc_freq = clk_get_rate(clks[MPC512x_CLK_REF]);
		calc_freq *= *sys_mul;
		calc_freq /= *sys_भाग;
		calc_freq /= 2;
		calc_freq /= *ips_भाग;
		अगर (bus_freq && calc_freq != bus_freq)
			pr_warn("calc rate %d != OF spec %d\n",
				calc_freq, bus_freq);
	पूर्ण अन्यथा अणु
		calc_freq = bus_freq;	/* start with IPS */
		calc_freq *= *ips_भाग;	/* IPS -> CSB */
		calc_freq *= 2;		/* CSB -> SYS */
		calc_freq *= *sys_भाग;	/* SYS -> PLL out */
		calc_freq /= *sys_mul;	/* PLL out -> REF == OSC */
		clks[MPC512x_CLK_REF] = mpc512x_clk_fixed("ref", calc_freq);
	पूर्ण
पूर्ण

/* MCLK helpers अणुअणुअणु */

/*
 * helper code क्रम the MCLK subtree setup
 *
 * the overview in section 5.2.4 of the MPC5121e Reference Manual rev4
 * suggests that all instances of the "PSC clock generation" are equal,
 * and that one might re-use the PSC setup क्रम MSCAN घड़ी generation
 * (section 5.2.5) as well, at least the logic अगर not the data क्रम
 * description
 *
 * the details (starting at page 5-20) show dअगरferences in the specअगरic
 * inमाला_दो of the first mux stage ("can clk in", "spdif tx"), and the
 * factual non-availability of the second mux stage (it's present yet
 * only one input is valid)
 *
 * the MSCAN घड़ी related रेजिस्टरs (starting at page 5-35) all
 * reference "spdif clk" at the first mux stage and करोn't mention any
 * "can clk" at all, which somehow is unexpected
 *
 * TODO re-check the करोcument, and clarअगरy whether the RM is correct in
 * the overview or in the details, and whether the dअगरference is a
 * clipboard induced error or results from chip revisions
 *
 * it turns out that the RM rev4 as of 2012-06 talks about "can" क्रम the
 * PSCs जबतक RM rev3 as of 2008-10 talks about "spdif", so I guess that
 * first a करोc update is required which better reflects reality in the
 * SoC beक्रमe the implementation should follow जबतक no questions reमुख्य
 */

/*
 * note that this declaration उठाओs a checkpatch warning, but
 * it's the very data type dictated by <linux/clk-provider.h>,
 * "fixing" this warning will अवरोध compilation
 */
अटल स्थिर अक्षर *parent_names_mux0_spdअगर[] = अणु
	"sys", "ref", "psc-mclk-in", "spdif-tx",
पूर्ण;

अटल स्थिर अक्षर *parent_names_mux0_canin[] = अणु
	"sys", "ref", "psc-mclk-in", "can-clk-in",
पूर्ण;

क्रमागत mclk_type अणु
	MCLK_TYPE_PSC,
	MCLK_TYPE_MSCAN,
	MCLK_TYPE_SPDIF,
	MCLK_TYPE_OUTCLK,
पूर्ण;

काष्ठा mclk_setup_data अणु
	क्रमागत mclk_type type;
	bool has_mclk1;
	स्थिर अक्षर *name_mux0;
	स्थिर अक्षर *name_en0;
	स्थिर अक्षर *name_भाग0;
	स्थिर अक्षर *parent_names_mux1[2];
	स्थिर अक्षर *name_mclk;
पूर्ण;

#घोषणा MCLK_SETUP_DATA_PSC(id) अणु \
	MCLK_TYPE_PSC, 0, \
	"psc" #id "-mux0", \
	"psc" #id "-en0", \
	"psc" #id "_mclk_div", \
	अणु "psc" #id "_mclk_div", "dummy", पूर्ण, \
	"psc" #id "_mclk", \
पूर्ण

#घोषणा MCLK_SETUP_DATA_MSCAN(id) अणु \
	MCLK_TYPE_MSCAN, 0, \
	"mscan" #id "-mux0", \
	"mscan" #id "-en0", \
	"mscan" #id "_mclk_div", \
	अणु "mscan" #id "_mclk_div", "dummy", पूर्ण, \
	"mscan" #id "_mclk", \
पूर्ण

#घोषणा MCLK_SETUP_DATA_SPDIF अणु \
	MCLK_TYPE_SPDIF, 1, \
	"spdif-mux0", \
	"spdif-en0", \
	"spdif_mclk_div", \
	अणु "spdif_mclk_div", "spdif-rx", पूर्ण, \
	"spdif_mclk", \
पूर्ण

#घोषणा MCLK_SETUP_DATA_OUTCLK(id) अणु \
	MCLK_TYPE_OUTCLK, 0, \
	"out" #id "-mux0", \
	"out" #id "-en0", \
	"out" #id "_mclk_div", \
	अणु "out" #id "_mclk_div", "dummy", पूर्ण, \
	"out" #id "_clk", \
पूर्ण

अटल काष्ठा mclk_setup_data mclk_psc_data[] = अणु
	MCLK_SETUP_DATA_PSC(0),
	MCLK_SETUP_DATA_PSC(1),
	MCLK_SETUP_DATA_PSC(2),
	MCLK_SETUP_DATA_PSC(3),
	MCLK_SETUP_DATA_PSC(4),
	MCLK_SETUP_DATA_PSC(5),
	MCLK_SETUP_DATA_PSC(6),
	MCLK_SETUP_DATA_PSC(7),
	MCLK_SETUP_DATA_PSC(8),
	MCLK_SETUP_DATA_PSC(9),
	MCLK_SETUP_DATA_PSC(10),
	MCLK_SETUP_DATA_PSC(11),
पूर्ण;

अटल काष्ठा mclk_setup_data mclk_mscan_data[] = अणु
	MCLK_SETUP_DATA_MSCAN(0),
	MCLK_SETUP_DATA_MSCAN(1),
	MCLK_SETUP_DATA_MSCAN(2),
	MCLK_SETUP_DATA_MSCAN(3),
पूर्ण;

अटल काष्ठा mclk_setup_data mclk_spdअगर_data[] = अणु
	MCLK_SETUP_DATA_SPDIF,
पूर्ण;

अटल काष्ठा mclk_setup_data mclk_outclk_data[] = अणु
	MCLK_SETUP_DATA_OUTCLK(0),
	MCLK_SETUP_DATA_OUTCLK(1),
	MCLK_SETUP_DATA_OUTCLK(2),
	MCLK_SETUP_DATA_OUTCLK(3),
पूर्ण;

/* setup the MCLK घड़ी subtree of an inभागidual PSC/MSCAN/SPDIF */
अटल व्योम mpc512x_clk_setup_mclk(काष्ठा mclk_setup_data *entry, माप_प्रकार idx)
अणु
	माप_प्रकार clks_idx_pub, clks_idx_पूर्णांक;
	u32 __iomem *mccr_reg;	/* MCLK control रेजिस्टर (mux, en, भाग) */
	पूर्णांक भाग;

	/* derive a few parameters from the component type and index */
	चयन (entry->type) अणु
	हाल MCLK_TYPE_PSC:
		clks_idx_pub = MPC512x_CLK_PSC0_MCLK + idx;
		clks_idx_पूर्णांक = MPC512x_CLK_MCLKS_FIRST
			     + (idx) * MCLK_MAX_IDX;
		mccr_reg = &clkregs->psc_ccr[idx];
		अवरोध;
	हाल MCLK_TYPE_MSCAN:
		clks_idx_pub = MPC512x_CLK_MSCAN0_MCLK + idx;
		clks_idx_पूर्णांक = MPC512x_CLK_MCLKS_FIRST
			     + (NR_PSCS + idx) * MCLK_MAX_IDX;
		mccr_reg = &clkregs->mscan_ccr[idx];
		अवरोध;
	हाल MCLK_TYPE_SPDIF:
		clks_idx_pub = MPC512x_CLK_SPDIF_MCLK;
		clks_idx_पूर्णांक = MPC512x_CLK_MCLKS_FIRST
			     + (NR_PSCS + NR_MSCANS) * MCLK_MAX_IDX;
		mccr_reg = &clkregs->spccr;
		अवरोध;
	हाल MCLK_TYPE_OUTCLK:
		clks_idx_pub = MPC512x_CLK_OUT0_CLK + idx;
		clks_idx_पूर्णांक = MPC512x_CLK_MCLKS_FIRST
			     + (NR_PSCS + NR_MSCANS + NR_SPDIFS + idx)
			     * MCLK_MAX_IDX;
		mccr_reg = &clkregs->out_ccr[idx];
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * this was grabbed from the PPC_CLOCK implementation, which
	 * enक्रमced a specअगरic MCLK भागider जबतक the घड़ी was gated
	 * during setup (that's a करोcumented hardware requirement)
	 *
	 * the PPC_CLOCK implementation might even have violated the
	 * "MCLK <= IPS" स्थिरraपूर्णांक, the fixed भागider value of 1
	 * results in a भागider of 2 and thus MCLK = SYS/2 which equals
	 * CSB which is greater than IPS; the serial port setup may have
	 * adjusted the भागider which the घड़ी setup might have left in
	 * an undesirable state
	 *
	 * initial setup is:
	 * - MCLK 0 from SYS
	 * - MCLK DIV such to not exceed the IPS घड़ी
	 * - MCLK 0 enabled
	 * - MCLK 1 from MCLK DIV
	 */
	भाग = clk_get_rate(clks[MPC512x_CLK_SYS]);
	भाग /= clk_get_rate(clks[MPC512x_CLK_IPS]);
	out_be32(mccr_reg, (0 << 16));
	out_be32(mccr_reg, (0 << 16) | ((भाग - 1) << 17));
	out_be32(mccr_reg, (1 << 16) | ((भाग - 1) << 17));

	/*
	 * create the 'struct clk' items of the MCLK's घड़ी subtree
	 *
	 * note that by design we always create all nodes and won't take
	 * लघुcuts here, because
	 * - the "internal" MCLK_DIV and MCLK_OUT संकेत in turn are
	 *   selectable inमाला_दो to the CFM जबतक those who "actually use"
	 *   the PSC/MSCAN/SPDIF (serial drivers et al) need the MCLK
	 *   क्रम their bitrate
	 * - in the असलence of "aliases" क्रम घड़ीs we need to create
	 *   inभागidial 'struct clk' items क्रम whatever might get
	 *   referenced or looked up, even अगर several of those items are
	 *   identical from the logical POV (their rate value)
	 * - क्रम easier future मुख्यtenance and क्रम better reflection of
	 *   the SoC's करोcumentation, it appears appropriate to generate
	 *   घड़ी items even क्रम those muxers which actually are NOPs
	 *   (those with two inमाला_दो of which one is reserved)
	 */
	clks[clks_idx_पूर्णांक + MCLK_IDX_MUX0] = mpc512x_clk_muxed(
			entry->name_mux0,
			soc_has_mclk_mux0_canin()
				? &parent_names_mux0_canin[0]
				: &parent_names_mux0_spdअगर[0],
			ARRAY_SIZE(parent_names_mux0_spdअगर),
			mccr_reg, 14, 2);
	clks[clks_idx_पूर्णांक + MCLK_IDX_EN0] = mpc512x_clk_gated(
			entry->name_en0, entry->name_mux0,
			mccr_reg, 16);
	clks[clks_idx_पूर्णांक + MCLK_IDX_DIV0] = mpc512x_clk_भागider(
			entry->name_भाग0,
			entry->name_en0, CLK_SET_RATE_GATE,
			mccr_reg, 17, 15, 0);
	अगर (entry->has_mclk1) अणु
		clks[clks_idx_pub] = mpc512x_clk_muxed(
				entry->name_mclk,
				&entry->parent_names_mux1[0],
				ARRAY_SIZE(entry->parent_names_mux1),
				mccr_reg, 7, 1);
	पूर्ण अन्यथा अणु
		clks[clks_idx_pub] = mpc512x_clk_factor(
				entry->name_mclk,
				entry->parent_names_mux1[0],
				1, 1);
	पूर्ण
पूर्ण

/* पूर्णपूर्णपूर्ण MCLK helpers */

अटल व्योम mpc512x_clk_setup_घड़ी_प्रकारree(काष्ठा device_node *np, पूर्णांक busfreq)
अणु
	पूर्णांक sys_mul, sys_भाग, ips_भाग;
	पूर्णांक mul, भाग;
	माप_प्रकार mclk_idx;
	पूर्णांक freq;

	/*
	 * developer's notes:
	 * - consider whether to handle घड़ीs which have both gates and
	 *   भागiders via पूर्णांकermediates or by means of composites
	 * - fractional भागiders appear to not map well to composites
	 *   since they can be seen as a fixed multiplier and an
	 *   adjustable भागider, जबतक composites can only combine at
	 *   most one of a mux, भाग, and gate each पूर्णांकo one 'struct clk'
	 *   item
	 * - PSC/MSCAN/SPDIF घड़ी generation OTOH alपढ़ोy is very
	 *   specअगरic and cannot get mapped to composites (at least not
	 *   a single one, maybe two of them, but then some of these
	 *   पूर्णांकermediate घड़ी संकेतs get referenced अन्यथाwhere (e.g.
	 *   in the घड़ी frequency measurement, CFM) and thus need
	 *   खुलाly available names
	 * - the current source layout appropriately reflects the
	 *   hardware setup, and it works, so it's questionable whether
	 *   further changes will result in big enough a benefit
	 */

	/* regardless of whether XTAL/OSC exists, have REF created */
	mpc512x_clk_setup_ref_घड़ी(np, busfreq, &sys_mul, &sys_भाग, &ips_भाग);

	/* now setup the REF -> SYS -> CSB -> IPS hierarchy */
	clks[MPC512x_CLK_SYS] = mpc512x_clk_factor("sys", "ref",
						   sys_mul, sys_भाग);
	clks[MPC512x_CLK_CSB] = mpc512x_clk_factor("csb", "sys", 1, 2);
	clks[MPC512x_CLK_IPS] = mpc512x_clk_भागtable("ips", "csb",
						     &clkregs->scfr1, 23, 3,
						     भागtab_2346);
	/* now setup anything below SYS and CSB and IPS */

	clks[MPC512x_CLK_DDR_UG] = mpc512x_clk_factor("ddr-ug", "sys", 1, 2);

	/*
	 * the Reference Manual discusses that क्रम SDHC only even भागide
	 * ratios are supported because घड़ी करोमुख्य synchronization
	 * between 'per' and 'ipg' is broken;
	 * keep the भागider's bit 0 cleared (per reset value), and only
	 * allow to setup the भागider's bits 7:1, which results in that
	 * only even भागide ratios can get configured upon rate changes;
	 * keep the "x4" name because this bit shअगरt hack is an पूर्णांकernal
	 * implementation detail, the "fractional divider with quarters"
	 * semantics reमुख्यs
	 */
	clks[MPC512x_CLK_SDHC_x4] = mpc512x_clk_factor("sdhc-x4", "csb", 2, 1);
	clks[MPC512x_CLK_SDHC_UG] = mpc512x_clk_भागider("sdhc-ug", "sdhc-x4", 0,
							&clkregs->scfr2, 1, 7,
							CLK_DIVIDER_ONE_BASED);
	अगर (soc_has_sdhc2()) अणु
		clks[MPC512x_CLK_SDHC2_UG] = mpc512x_clk_भागider(
				"sdhc2-ug", "sdhc-x4", 0, &clkregs->scfr2,
				9, 7, CLK_DIVIDER_ONE_BASED);
	पूर्ण

	clks[MPC512x_CLK_DIU_x4] = mpc512x_clk_factor("diu-x4", "csb", 4, 1);
	clks[MPC512x_CLK_DIU_UG] = mpc512x_clk_भागider("diu-ug", "diu-x4", 0,
						       &clkregs->scfr1, 0, 8,
						       CLK_DIVIDER_ONE_BASED);

	/*
	 * the "power architecture PLL" was setup from data which was
	 * sampled from the reset config word, at this poपूर्णांक in समय the
	 * configuration can be considered fixed and पढ़ो only (i.e. no
	 * दीर्घer adjustable, or no दीर्घer in need of adjusपंचांगent), which
	 * is why we करोn't रेजिस्टर a PLL here but assume fixed factors
	 */
	mul = get_cpmf_mult_x2();
	भाग = 2;	/* compensate क्रम the fractional factor */
	clks[MPC512x_CLK_E300] = mpc512x_clk_factor("e300", "csb", mul, भाग);

	अगर (soc_has_mbx()) अणु
		clks[MPC512x_CLK_MBX_BUS_UG] = mpc512x_clk_factor(
				"mbx-bus-ug", "csb", 1, 2);
		clks[MPC512x_CLK_MBX_UG] = mpc512x_clk_भागtable(
				"mbx-ug", "mbx-bus-ug", &clkregs->scfr1,
				14, 3, भागtab_1234);
		clks[MPC512x_CLK_MBX_3D_UG] = mpc512x_clk_factor(
				"mbx-3d-ug", "mbx-ug", 1, 1);
	पूर्ण
	अगर (soc_has_pci()) अणु
		clks[MPC512x_CLK_PCI_UG] = mpc512x_clk_भागtable(
				"pci-ug", "csb", &clkregs->scfr1,
				20, 3, भागtab_2346);
	पूर्ण
	अगर (soc_has_nfc_5125()) अणु
		/*
		 * XXX TODO implement 5125 NFC घड़ी setup logic,
		 * with high/low period counters in clkregs->scfr3,
		 * currently there are no users so it's ENOIMPL
		 */
		clks[MPC512x_CLK_NFC_UG] = ERR_PTR(-ENOTSUPP);
	पूर्ण अन्यथा अणु
		clks[MPC512x_CLK_NFC_UG] = mpc512x_clk_भागtable(
				"nfc-ug", "ips", &clkregs->scfr1,
				8, 3, भागtab_1234);
	पूर्ण
	clks[MPC512x_CLK_LPC_UG] = mpc512x_clk_भागtable("lpc-ug", "ips",
							&clkregs->scfr1, 11, 3,
							भागtab_1234);

	clks[MPC512x_CLK_LPC] = mpc512x_clk_gated("lpc", "lpc-ug",
						  &clkregs->sccr1, 30);
	clks[MPC512x_CLK_NFC] = mpc512x_clk_gated("nfc", "nfc-ug",
						  &clkregs->sccr1, 29);
	अगर (soc_has_pata()) अणु
		clks[MPC512x_CLK_PATA] = mpc512x_clk_gated(
				"pata", "ips", &clkregs->sccr1, 28);
	पूर्ण
	/* क्रम PSCs there is a "registers" gate and a bitrate MCLK subtree */
	क्रम (mclk_idx = 0; mclk_idx < soc_max_pscnum(); mclk_idx++) अणु
		अक्षर name[12];
		snम_लिखो(name, माप(name), "psc%d", mclk_idx);
		clks[MPC512x_CLK_PSC0 + mclk_idx] = mpc512x_clk_gated(
				name, "ips", &clkregs->sccr1, 27 - mclk_idx);
		mpc512x_clk_setup_mclk(&mclk_psc_data[mclk_idx], mclk_idx);
	पूर्ण
	clks[MPC512x_CLK_PSC_FIFO] = mpc512x_clk_gated("psc-fifo", "ips",
						       &clkregs->sccr1, 15);
	अगर (soc_has_sata()) अणु
		clks[MPC512x_CLK_SATA] = mpc512x_clk_gated(
				"sata", "ips", &clkregs->sccr1, 14);
	पूर्ण
	clks[MPC512x_CLK_FEC] = mpc512x_clk_gated("fec", "ips",
						  &clkregs->sccr1, 13);
	अगर (soc_has_pci()) अणु
		clks[MPC512x_CLK_PCI] = mpc512x_clk_gated(
				"pci", "pci-ug", &clkregs->sccr1, 11);
	पूर्ण
	clks[MPC512x_CLK_DDR] = mpc512x_clk_gated("ddr", "ddr-ug",
						  &clkregs->sccr1, 10);
	अगर (soc_has_fec2()) अणु
		clks[MPC512x_CLK_FEC2] = mpc512x_clk_gated(
				"fec2", "ips", &clkregs->sccr1, 9);
	पूर्ण

	clks[MPC512x_CLK_DIU] = mpc512x_clk_gated("diu", "diu-ug",
						  &clkregs->sccr2, 31);
	अगर (soc_has_axe()) अणु
		clks[MPC512x_CLK_AXE] = mpc512x_clk_gated(
				"axe", "csb", &clkregs->sccr2, 30);
	पूर्ण
	clks[MPC512x_CLK_MEM] = mpc512x_clk_gated("mem", "ips",
						  &clkregs->sccr2, 29);
	clks[MPC512x_CLK_USB1] = mpc512x_clk_gated("usb1", "csb",
						   &clkregs->sccr2, 28);
	clks[MPC512x_CLK_USB2] = mpc512x_clk_gated("usb2", "csb",
						   &clkregs->sccr2, 27);
	clks[MPC512x_CLK_I2C] = mpc512x_clk_gated("i2c", "ips",
						  &clkregs->sccr2, 26);
	/* MSCAN dअगरfers from PSC with just one gate क्रम multiple components */
	clks[MPC512x_CLK_BDLC] = mpc512x_clk_gated("bdlc", "ips",
						   &clkregs->sccr2, 25);
	क्रम (mclk_idx = 0; mclk_idx < ARRAY_SIZE(mclk_mscan_data); mclk_idx++)
		mpc512x_clk_setup_mclk(&mclk_mscan_data[mclk_idx], mclk_idx);
	clks[MPC512x_CLK_SDHC] = mpc512x_clk_gated("sdhc", "sdhc-ug",
						   &clkregs->sccr2, 24);
	/* there is only one SPDIF component, which shares MCLK support code */
	अगर (soc_has_spdअगर()) अणु
		clks[MPC512x_CLK_SPDIF] = mpc512x_clk_gated(
				"spdif", "ips", &clkregs->sccr2, 23);
		mpc512x_clk_setup_mclk(&mclk_spdअगर_data[0], 0);
	पूर्ण
	अगर (soc_has_mbx()) अणु
		clks[MPC512x_CLK_MBX_BUS] = mpc512x_clk_gated(
				"mbx-bus", "mbx-bus-ug", &clkregs->sccr2, 22);
		clks[MPC512x_CLK_MBX] = mpc512x_clk_gated(
				"mbx", "mbx-ug", &clkregs->sccr2, 21);
		clks[MPC512x_CLK_MBX_3D] = mpc512x_clk_gated(
				"mbx-3d", "mbx-3d-ug", &clkregs->sccr2, 20);
	पूर्ण
	clks[MPC512x_CLK_IIM] = mpc512x_clk_gated("iim", "csb",
						  &clkregs->sccr2, 19);
	अगर (soc_has_viu()) अणु
		clks[MPC512x_CLK_VIU] = mpc512x_clk_gated(
				"viu", "csb", &clkregs->sccr2, 18);
	पूर्ण
	अगर (soc_has_sdhc2()) अणु
		clks[MPC512x_CLK_SDHC2] = mpc512x_clk_gated(
				"sdhc-2", "sdhc2-ug", &clkregs->sccr2, 17);
	पूर्ण

	अगर (soc_has_outclk()) अणु
		माप_प्रकार idx;	/* used as mclk_idx, just to trim line length */
		क्रम (idx = 0; idx < ARRAY_SIZE(mclk_outclk_data); idx++)
			mpc512x_clk_setup_mclk(&mclk_outclk_data[idx], idx);
	पूर्ण

	/*
	 * बाह्यally provided घड़ीs (when implemented in hardware,
	 * device tree may specअगरy values which otherwise were unknown)
	 */
	freq = get_freq_from_dt("psc_mclk_in");
	अगर (!freq)
		freq = 25000000;
	clks[MPC512x_CLK_PSC_MCLK_IN] = mpc512x_clk_fixed("psc_mclk_in", freq);
	अगर (soc_has_mclk_mux0_canin()) अणु
		freq = get_freq_from_dt("can_clk_in");
		clks[MPC512x_CLK_CAN_CLK_IN] = mpc512x_clk_fixed(
				"can_clk_in", freq);
	पूर्ण अन्यथा अणु
		freq = get_freq_from_dt("spdif_tx_in");
		clks[MPC512x_CLK_SPDIF_TX_IN] = mpc512x_clk_fixed(
				"spdif_tx_in", freq);
		freq = get_freq_from_dt("spdif_rx_in");
		clks[MPC512x_CLK_SPDIF_TX_IN] = mpc512x_clk_fixed(
				"spdif_rx_in", freq);
	पूर्ण

	/* fixed frequency क्रम AC97, always 24.567MHz */
	clks[MPC512x_CLK_AC97] = mpc512x_clk_fixed("ac97", 24567000);

	/*
	 * pre-enable those "internal" घड़ी items which never get
	 * claimed by any peripheral driver, to not have the घड़ी
	 * subप्रणाली disable them late at startup
	 */
	clk_prepare_enable(clks[MPC512x_CLK_DUMMY]);
	clk_prepare_enable(clks[MPC512x_CLK_E300]);	/* PowerPC CPU */
	clk_prepare_enable(clks[MPC512x_CLK_DDR]);	/* DRAM */
	clk_prepare_enable(clks[MPC512x_CLK_MEM]);	/* SRAM */
	clk_prepare_enable(clks[MPC512x_CLK_IPS]);	/* SoC periph */
	clk_prepare_enable(clks[MPC512x_CLK_LPC]);	/* boot media */
पूर्ण

/*
 * रेजिस्टरs the set of खुला घड़ीs (those listed in the dt-bindings/
 * header file) क्रम OF lookups, keeps the पूर्णांकermediates निजी to us
 */
अटल व्योम mpc5121_clk_रेजिस्टर_of_provider(काष्ठा device_node *np)
अणु
	clk_data.clks = clks;
	clk_data.clk_num = MPC512x_CLK_LAST_PUBLIC + 1;	/* _not_ ARRAY_SIZE() */
	of_clk_add_provider(np, of_clk_src_onecell_get, &clk_data);
पूर्ण

/*
 * temporary support क्रम the period of समय between पूर्णांकroduction of CCF
 * support and the adjusपंचांगent of peripheral drivers to OF based lookups
 */
अटल व्योम mpc5121_clk_provide_migration_support(व्योम)
अणु

	/*
	 * pre-enable those घड़ी items which are not yet appropriately
	 * acquired by their peripheral driver
	 *
	 * the PCI घड़ी cannot get acquired by its peripheral driver,
	 * because क्रम this platक्रमm the driver won't probe(), instead
	 * initialization is करोne from within the .setup_arch() routine
	 * at a poपूर्णांक in समय where the घड़ी provider has not been
	 * setup yet and thus isn't available yet
	 *
	 * so we "pre-enable" the घड़ी here, to not have the घड़ी
	 * subप्रणाली स्वतःmatically disable this item in a late init call
	 *
	 * this PCI घड़ी pre-enable workaround only applies when there
	 * are device tree nodes क्रम PCI and thus the peripheral driver
	 * has attached to bridges, otherwise the PCI घड़ी reमुख्यs
	 * unused and so it माला_लो disabled
	 */
	clk_prepare_enable(clks[MPC512x_CLK_PSC3_MCLK]);/* serial console */
	अगर (of_find_compatible_node(शून्य, "pci", "fsl,mpc5121-pci"))
		clk_prepare_enable(clks[MPC512x_CLK_PCI]);
पूर्ण

/*
 * those macros are not exactly pretty, but they encapsulate a lot
 * of copy'n'paste heavy code which is even more ugly, and reduce
 * the potential क्रम inconsistencies in those many code copies
 */
#घोषणा FOR_NODES(compatname) \
	क्रम_each_compatible_node(np, शून्य, compatname)

#घोषणा NODE_PREP करो अणु \
	of_address_to_resource(np, 0, &res); \
	snम_लिखो(devname, माप(devname), "%08x.%s", res.start, np->name); \
पूर्ण जबतक (0)

#घोषणा NODE_CHK(clkname, clkitem, regnode, regflag) करो अणु \
	काष्ठा clk *clk; \
	clk = of_clk_get_by_name(np, clkname); \
	अगर (IS_ERR(clk)) अणु \
		clk = clkitem; \
		clk_रेजिस्टर_clkdev(clk, clkname, devname); \
		अगर (regnode) \
			clk_रेजिस्टर_clkdev(clk, clkname, np->name); \
		did_रेजिस्टर |= DID_REG_ ## regflag; \
		pr_debug("clock alias name '%s' for dev '%s' pointer %p\n", \
			 clkname, devname, clk); \
	पूर्ण अन्यथा अणु \
		clk_put(clk); \
	पूर्ण \
पूर्ण जबतक (0)

/*
 * रेजिस्टर source code provided fallback results क्रम घड़ी lookups,
 * these get consulted when OF based घड़ी lookup fails (that is in the
 * हाल of not yet adjusted device tree data, where घड़ी related specs
 * are missing)
 */
अटल व्योम mpc5121_clk_provide_backwards_compat(व्योम)
अणु
	क्रमागत did_reg_flags अणु
		DID_REG_PSC	= BIT(0),
		DID_REG_PSCFIFO	= BIT(1),
		DID_REG_NFC	= BIT(2),
		DID_REG_CAN	= BIT(3),
		DID_REG_I2C	= BIT(4),
		DID_REG_DIU	= BIT(5),
		DID_REG_VIU	= BIT(6),
		DID_REG_FEC	= BIT(7),
		DID_REG_USB	= BIT(8),
		DID_REG_PATA	= BIT(9),
	पूर्ण;

	पूर्णांक did_रेजिस्टर;
	काष्ठा device_node *np;
	काष्ठा resource res;
	पूर्णांक idx;
	अक्षर devname[32];

	did_रेजिस्टर = 0;

	FOR_NODES(mpc512x_select_psc_compat()) अणु
		NODE_PREP;
		idx = (res.start >> 8) & 0xf;
		NODE_CHK("ipg", clks[MPC512x_CLK_PSC0 + idx], 0, PSC);
		NODE_CHK("mclk", clks[MPC512x_CLK_PSC0_MCLK + idx], 0, PSC);
	पूर्ण

	FOR_NODES("fsl,mpc5121-psc-fifo") अणु
		NODE_PREP;
		NODE_CHK("ipg", clks[MPC512x_CLK_PSC_FIFO], 1, PSCFIFO);
	पूर्ण

	FOR_NODES("fsl,mpc5121-nfc") अणु
		NODE_PREP;
		NODE_CHK("ipg", clks[MPC512x_CLK_NFC], 0, NFC);
	पूर्ण

	FOR_NODES("fsl,mpc5121-mscan") अणु
		NODE_PREP;
		idx = 0;
		idx += (res.start & 0x2000) ? 2 : 0;
		idx += (res.start & 0x0080) ? 1 : 0;
		NODE_CHK("ipg", clks[MPC512x_CLK_BDLC], 0, CAN);
		NODE_CHK("mclk", clks[MPC512x_CLK_MSCAN0_MCLK + idx], 0, CAN);
	पूर्ण

	/*
	 * करो रेजिस्टर the 'ips', 'sys', and 'ref' names globally
	 * instead of inside each inभागidual CAN node, as there is no
	 * potential क्रम a name conflict (in contrast to 'ipg' and 'mclk')
	 */
	अगर (did_रेजिस्टर & DID_REG_CAN) अणु
		clk_रेजिस्टर_clkdev(clks[MPC512x_CLK_IPS], "ips", शून्य);
		clk_रेजिस्टर_clkdev(clks[MPC512x_CLK_SYS], "sys", शून्य);
		clk_रेजिस्टर_clkdev(clks[MPC512x_CLK_REF], "ref", शून्य);
	पूर्ण

	FOR_NODES("fsl,mpc5121-i2c") अणु
		NODE_PREP;
		NODE_CHK("ipg", clks[MPC512x_CLK_I2C], 0, I2C);
	पूर्ण

	/*
	 * workaround क्रम the fact that the I2C driver करोes an "anonymous"
	 * lookup (शून्य name spec, which yields the first घड़ी spec) क्रम
	 * which we cannot रेजिस्टर an alias -- a _global_ 'ipg' alias that
	 * is not bound to any device name and वापसs the I2C घड़ी item
	 * is not a good idea
	 *
	 * so we have the lookup in the peripheral driver fail, which is
	 * silent and non-fatal, and pre-enable the घड़ी item here such
	 * that रेजिस्टर access is possible
	 *
	 * see commit b3bfce2b "i2c: mpc: cleanup clock API use" क्रम
	 * details, adjusting s/शून्य/"ipg"/ in i2c-mpc.c would make this
	 * workaround obsolete
	 */
	अगर (did_रेजिस्टर & DID_REG_I2C)
		clk_prepare_enable(clks[MPC512x_CLK_I2C]);

	FOR_NODES("fsl,mpc5121-diu") अणु
		NODE_PREP;
		NODE_CHK("ipg", clks[MPC512x_CLK_DIU], 1, DIU);
	पूर्ण

	FOR_NODES("fsl,mpc5121-viu") अणु
		NODE_PREP;
		NODE_CHK("ipg", clks[MPC512x_CLK_VIU], 0, VIU);
	पूर्ण

	/*
	 * note that 2771399a "fs_enet: cleanup clock API use" did use the
	 * "per" string क्रम the घड़ी lookup in contrast to the "ipg" name
	 * which most other nodes are using -- this is not a fatal thing
	 * but just something to keep in mind when करोing compatibility
	 * registration, it's a non-issue with up-to-date device tree data
	 */
	FOR_NODES("fsl,mpc5121-fec") अणु
		NODE_PREP;
		NODE_CHK("per", clks[MPC512x_CLK_FEC], 0, FEC);
	पूर्ण
	FOR_NODES("fsl,mpc5121-fec-mdio") अणु
		NODE_PREP;
		NODE_CHK("per", clks[MPC512x_CLK_FEC], 0, FEC);
	पूर्ण
	/*
	 * MPC5125 has two FECs: FEC1 at 0x2800, FEC2 at 0x4800;
	 * the घड़ी items करोn't "form an array" since FEC2 was
	 * added only later and was not allowed to shअगरt all other
	 * घड़ी item indices, so the numbers aren't adjacent
	 */
	FOR_NODES("fsl,mpc5125-fec") अणु
		NODE_PREP;
		अगर (res.start & 0x4000)
			idx = MPC512x_CLK_FEC2;
		अन्यथा
			idx = MPC512x_CLK_FEC;
		NODE_CHK("per", clks[idx], 0, FEC);
	पूर्ण

	FOR_NODES("fsl,mpc5121-usb2-dr") अणु
		NODE_PREP;
		idx = (res.start & 0x4000) ? 1 : 0;
		NODE_CHK("ipg", clks[MPC512x_CLK_USB1 + idx], 0, USB);
	पूर्ण

	FOR_NODES("fsl,mpc5121-pata") अणु
		NODE_PREP;
		NODE_CHK("ipg", clks[MPC512x_CLK_PATA], 0, PATA);
	पूर्ण

	/*
	 * try to collapse diagnostics पूर्णांकo a single line of output yet
	 * provide a full list of what is missing, to aव्योम noise in the
	 * असलence of up-to-date device tree data -- backwards
	 * compatibility to old DTBs is a requirement, updates may be
	 * desirable or preferrable but are not at all mandatory
	 */
	अगर (did_रेजिस्टर) अणु
		pr_notice("device tree lacks clock specs, adding fallbacks (0x%x,%s%s%s%s%s%s%s%s%s%s)\n",
			  did_रेजिस्टर,
			  (did_रेजिस्टर & DID_REG_PSC) ? " PSC" : "",
			  (did_रेजिस्टर & DID_REG_PSCFIFO) ? " PSCFIFO" : "",
			  (did_रेजिस्टर & DID_REG_NFC) ? " NFC" : "",
			  (did_रेजिस्टर & DID_REG_CAN) ? " CAN" : "",
			  (did_रेजिस्टर & DID_REG_I2C) ? " I2C" : "",
			  (did_रेजिस्टर & DID_REG_DIU) ? " DIU" : "",
			  (did_रेजिस्टर & DID_REG_VIU) ? " VIU" : "",
			  (did_रेजिस्टर & DID_REG_FEC) ? " FEC" : "",
			  (did_रेजिस्टर & DID_REG_USB) ? " USB" : "",
			  (did_रेजिस्टर & DID_REG_PATA) ? " PATA" : "");
	पूर्ण अन्यथा अणु
		pr_debug("device tree has clock specs, no fallbacks added\n");
	पूर्ण
पूर्ण

/*
 * The "fixed-clock" nodes (which includes the oscillator node अगर the board's
 * DT provides one) has alपढ़ोy been scanned by the of_clk_init() in
 * समय_init().
 */
पूर्णांक __init mpc5121_clk_init(व्योम)
अणु
	काष्ठा device_node *clk_np;
	पूर्णांक busfreq;

	/* map the घड़ी control रेजिस्टरs */
	clk_np = of_find_compatible_node(शून्य, शून्य, "fsl,mpc5121-clock");
	अगर (!clk_np)
		वापस -ENODEV;
	clkregs = of_iomap(clk_np, 0);
	WARN_ON(!clkregs);

	/* determine the SoC variant we run on */
	mpc512x_clk_determine_soc();

	/* invalidate all not yet रेजिस्टरed घड़ी slots */
	mpc512x_clk_preset_data();

	/*
	 * add a dummy घड़ी क्रम those situations where a घड़ी spec is
	 * required yet no real घड़ी is involved
	 */
	clks[MPC512x_CLK_DUMMY] = mpc512x_clk_fixed("dummy", 0);

	/*
	 * have all the real nodes in the घड़ी tree populated from REF
	 * करोwn to all leaves, either starting from the OSC node or from
	 * a REF root that was created from the IPS bus घड़ी input
	 */
	busfreq = get_freq_from_dt("bus-frequency");
	mpc512x_clk_setup_घड़ी_प्रकारree(clk_np, busfreq);

	/* रेजिस्टर as an OF घड़ी provider */
	mpc5121_clk_रेजिस्टर_of_provider(clk_np);

	/*
	 * unअवरोध not yet adjusted peripheral drivers during migration
	 * towards fully operational common घड़ी support, and allow
	 * operation in the असलence of घड़ी related device tree specs
	 */
	mpc5121_clk_provide_migration_support();
	mpc5121_clk_provide_backwards_compat();

	वापस 0;
पूर्ण
