<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) STMicroelectronics 2020
 */

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/regmap.h>
#समावेश <linux/reset.h>

/* FMC2 Controller Registers */
#घोषणा FMC2_BCR1			0x0
#घोषणा FMC2_BTR1			0x4
#घोषणा FMC2_BCR(x)			((x) * 0x8 + FMC2_BCR1)
#घोषणा FMC2_BTR(x)			((x) * 0x8 + FMC2_BTR1)
#घोषणा FMC2_PCSCNTR			0x20
#घोषणा FMC2_BWTR1			0x104
#घोषणा FMC2_BWTR(x)			((x) * 0x8 + FMC2_BWTR1)

/* Register: FMC2_BCR1 */
#घोषणा FMC2_BCR1_CCLKEN		BIT(20)
#घोषणा FMC2_BCR1_FMC2EN		BIT(31)

/* Register: FMC2_BCRx */
#घोषणा FMC2_BCR_MBKEN			BIT(0)
#घोषणा FMC2_BCR_MUXEN			BIT(1)
#घोषणा FMC2_BCR_MTYP			GENMASK(3, 2)
#घोषणा FMC2_BCR_MWID			GENMASK(5, 4)
#घोषणा FMC2_BCR_FACCEN			BIT(6)
#घोषणा FMC2_BCR_BURSTEN		BIT(8)
#घोषणा FMC2_BCR_WAITPOL		BIT(9)
#घोषणा FMC2_BCR_WAITCFG		BIT(11)
#घोषणा FMC2_BCR_WREN			BIT(12)
#घोषणा FMC2_BCR_WAITEN			BIT(13)
#घोषणा FMC2_BCR_EXTMOD			BIT(14)
#घोषणा FMC2_BCR_ASYNCWAIT		BIT(15)
#घोषणा FMC2_BCR_CPSIZE			GENMASK(18, 16)
#घोषणा FMC2_BCR_CBURSTRW		BIT(19)
#घोषणा FMC2_BCR_NBLSET			GENMASK(23, 22)

/* Register: FMC2_BTRx/FMC2_BWTRx */
#घोषणा FMC2_BXTR_ADDSET		GENMASK(3, 0)
#घोषणा FMC2_BXTR_ADDHLD		GENMASK(7, 4)
#घोषणा FMC2_BXTR_DATAST		GENMASK(15, 8)
#घोषणा FMC2_BXTR_BUSTURN		GENMASK(19, 16)
#घोषणा FMC2_BTR_CLKDIV			GENMASK(23, 20)
#घोषणा FMC2_BTR_DATLAT			GENMASK(27, 24)
#घोषणा FMC2_BXTR_ACCMOD		GENMASK(29, 28)
#घोषणा FMC2_BXTR_DATAHLD		GENMASK(31, 30)

/* Register: FMC2_PCSCNTR */
#घोषणा FMC2_PCSCNTR_CSCOUNT		GENMASK(15, 0)
#घोषणा FMC2_PCSCNTR_CNTBEN(x)		BIT((x) + 16)

#घोषणा FMC2_MAX_EBI_CE			4
#घोषणा FMC2_MAX_BANKS			5

#घोषणा FMC2_BCR_CPSIZE_0		0x0
#घोषणा FMC2_BCR_CPSIZE_128		0x1
#घोषणा FMC2_BCR_CPSIZE_256		0x2
#घोषणा FMC2_BCR_CPSIZE_512		0x3
#घोषणा FMC2_BCR_CPSIZE_1024		0x4

#घोषणा FMC2_BCR_MWID_8			0x0
#घोषणा FMC2_BCR_MWID_16		0x1

#घोषणा FMC2_BCR_MTYP_SRAM		0x0
#घोषणा FMC2_BCR_MTYP_PSRAM		0x1
#घोषणा FMC2_BCR_MTYP_NOR		0x2

#घोषणा FMC2_BXTR_EXTMOD_A		0x0
#घोषणा FMC2_BXTR_EXTMOD_B		0x1
#घोषणा FMC2_BXTR_EXTMOD_C		0x2
#घोषणा FMC2_BXTR_EXTMOD_D		0x3

#घोषणा FMC2_BCR_NBLSET_MAX		0x3
#घोषणा FMC2_BXTR_ADDSET_MAX		0xf
#घोषणा FMC2_BXTR_ADDHLD_MAX		0xf
#घोषणा FMC2_BXTR_DATAST_MAX		0xff
#घोषणा FMC2_BXTR_BUSTURN_MAX		0xf
#घोषणा FMC2_BXTR_DATAHLD_MAX		0x3
#घोषणा FMC2_BTR_CLKDIV_MAX		0xf
#घोषणा FMC2_BTR_DATLAT_MAX		0xf
#घोषणा FMC2_PCSCNTR_CSCOUNT_MAX	0xff

क्रमागत sपंचांग32_fmc2_ebi_bank अणु
	FMC2_EBI1 = 0,
	FMC2_EBI2,
	FMC2_EBI3,
	FMC2_EBI4,
	FMC2_न_अंकD
पूर्ण;

क्रमागत sपंचांग32_fmc2_ebi_रेजिस्टर_type अणु
	FMC2_REG_BCR = 1,
	FMC2_REG_BTR,
	FMC2_REG_BWTR,
	FMC2_REG_PCSCNTR
पूर्ण;

क्रमागत sपंचांग32_fmc2_ebi_transaction_type अणु
	FMC2_ASYNC_MODE_1_SRAM = 0,
	FMC2_ASYNC_MODE_1_PSRAM,
	FMC2_ASYNC_MODE_A_SRAM,
	FMC2_ASYNC_MODE_A_PSRAM,
	FMC2_ASYNC_MODE_2_NOR,
	FMC2_ASYNC_MODE_B_NOR,
	FMC2_ASYNC_MODE_C_NOR,
	FMC2_ASYNC_MODE_D_NOR,
	FMC2_SYNC_READ_SYNC_WRITE_PSRAM,
	FMC2_SYNC_READ_ASYNC_WRITE_PSRAM,
	FMC2_SYNC_READ_SYNC_WRITE_NOR,
	FMC2_SYNC_READ_ASYNC_WRITE_NOR
पूर्ण;

क्रमागत sपंचांग32_fmc2_ebi_buswidth अणु
	FMC2_BUSWIDTH_8 = 8,
	FMC2_BUSWIDTH_16 = 16
पूर्ण;

क्रमागत sपंचांग32_fmc2_ebi_cpsize अणु
	FMC2_CPSIZE_0 = 0,
	FMC2_CPSIZE_128 = 128,
	FMC2_CPSIZE_256 = 256,
	FMC2_CPSIZE_512 = 512,
	FMC2_CPSIZE_1024 = 1024
पूर्ण;

काष्ठा sपंचांग32_fmc2_ebi अणु
	काष्ठा device *dev;
	काष्ठा clk *clk;
	काष्ठा regmap *regmap;
	u8 bank_asचिन्हित;

	u32 bcr[FMC2_MAX_EBI_CE];
	u32 btr[FMC2_MAX_EBI_CE];
	u32 bwtr[FMC2_MAX_EBI_CE];
	u32 pcscntr;
पूर्ण;

/*
 * काष्ठा sपंचांग32_fmc2_prop - STM32 FMC2 EBI property
 * @name: the device tree binding name of the property
 * @bprop: indicate that it is a boolean property
 * @mprop: indicate that it is a mandatory property
 * @reg_type: the रेजिस्टर that have to be modअगरied
 * @reg_mask: the bit that have to be modअगरied in the selected रेजिस्टर
 *            in हाल of it is a boolean property
 * @reset_val: the शेष value that have to be set in हाल the property
 *             has not been defined in the device tree
 * @check: this callback ckecks that the property is compliant with the
 *         transaction type selected
 * @calculate: this callback is called to calculate क्रम exemple a timing
 *             set in nanoseconds in the device tree in घड़ी cycles or in
 *             घड़ी period
 * @set: this callback applies the values in the रेजिस्टरs
 */
काष्ठा sपंचांग32_fmc2_prop अणु
	स्थिर अक्षर *name;
	bool bprop;
	bool mprop;
	पूर्णांक reg_type;
	u32 reg_mask;
	u32 reset_val;
	पूर्णांक (*check)(काष्ठा sपंचांग32_fmc2_ebi *ebi,
		     स्थिर काष्ठा sपंचांग32_fmc2_prop *prop, पूर्णांक cs);
	u32 (*calculate)(काष्ठा sपंचांग32_fmc2_ebi *ebi, पूर्णांक cs, u32 setup);
	पूर्णांक (*set)(काष्ठा sपंचांग32_fmc2_ebi *ebi,
		   स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
		   पूर्णांक cs, u32 setup);
पूर्ण;

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_mux(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				    स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				    पूर्णांक cs)
अणु
	u32 bcr;

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);

	अगर (bcr & FMC2_BCR_MTYP)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_रुकोcfg(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					पूर्णांक cs)
अणु
	u32 bcr, val = FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);

	अगर ((bcr & FMC2_BCR_MTYP) == val && bcr & FMC2_BCR_BURSTEN)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_sync_trans(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					   स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					   पूर्णांक cs)
अणु
	u32 bcr;

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);

	अगर (bcr & FMC2_BCR_BURSTEN)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_async_trans(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					    स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					    पूर्णांक cs)
अणु
	u32 bcr;

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);

	अगर (!(bcr & FMC2_BCR_BURSTEN) || !(bcr & FMC2_BCR_CBURSTRW))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_cpsize(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				       स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				       पूर्णांक cs)
अणु
	u32 bcr, val = FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_PSRAM);

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);

	अगर ((bcr & FMC2_BCR_MTYP) == val && bcr & FMC2_BCR_BURSTEN)
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_address_hold(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					     स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					     पूर्णांक cs)
अणु
	u32 bcr, bxtr, val = FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_D);

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);
	अगर (prop->reg_type == FMC2_REG_BWTR)
		regmap_पढ़ो(ebi->regmap, FMC2_BWTR(cs), &bxtr);
	अन्यथा
		regmap_पढ़ो(ebi->regmap, FMC2_BTR(cs), &bxtr);

	अगर ((!(bcr & FMC2_BCR_BURSTEN) || !(bcr & FMC2_BCR_CBURSTRW)) &&
	    ((bxtr & FMC2_BXTR_ACCMOD) == val || bcr & FMC2_BCR_MUXEN))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_clk_period(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					   स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					   पूर्णांक cs)
अणु
	u32 bcr, bcr1;

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);
	अगर (cs)
		regmap_पढ़ो(ebi->regmap, FMC2_BCR1, &bcr1);
	अन्यथा
		bcr1 = bcr;

	अगर (bcr & FMC2_BCR_BURSTEN && (!cs || !(bcr1 & FMC2_BCR1_CCLKEN)))
		वापस 0;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_check_cclk(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				     स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				     पूर्णांक cs)
अणु
	अगर (cs)
		वापस -EINVAL;

	वापस sपंचांग32_fmc2_ebi_check_sync_trans(ebi, prop, cs);
पूर्ण

अटल u32 sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					     पूर्णांक cs, u32 setup)
अणु
	अचिन्हित दीर्घ hclk = clk_get_rate(ebi->clk);
	अचिन्हित दीर्घ hclkp = NSEC_PER_SEC / (hclk / 1000);

	वापस DIV_ROUND_UP(setup * 1000, hclkp);
पूर्ण

अटल u32 sपंचांग32_fmc2_ebi_ns_to_clk_period(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					   पूर्णांक cs, u32 setup)
अणु
	u32 nb_clk_cycles = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles(ebi, cs, setup);
	u32 bcr, btr, clk_period;

	regmap_पढ़ो(ebi->regmap, FMC2_BCR1, &bcr);
	अगर (bcr & FMC2_BCR1_CCLKEN || !cs)
		regmap_पढ़ो(ebi->regmap, FMC2_BTR1, &btr);
	अन्यथा
		regmap_पढ़ो(ebi->regmap, FMC2_BTR(cs), &btr);

	clk_period = FIELD_GET(FMC2_BTR_CLKDIV, btr) + 1;

	वापस DIV_ROUND_UP(nb_clk_cycles, clk_period);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_get_reg(पूर्णांक reg_type, पूर्णांक cs, u32 *reg)
अणु
	चयन (reg_type) अणु
	हाल FMC2_REG_BCR:
		*reg = FMC2_BCR(cs);
		अवरोध;
	हाल FMC2_REG_BTR:
		*reg = FMC2_BTR(cs);
		अवरोध;
	हाल FMC2_REG_BWTR:
		*reg = FMC2_BWTR(cs);
		अवरोध;
	हाल FMC2_REG_PCSCNTR:
		*reg = FMC2_PCSCNTR;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_bit_field(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					पूर्णांक cs, u32 setup)
अणु
	u32 reg;
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_ebi_get_reg(prop->reg_type, cs, &reg);
	अगर (ret)
		वापस ret;

	regmap_update_bits(ebi->regmap, reg, prop->reg_mask,
			   setup ? prop->reg_mask : 0);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_trans_type(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					 स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					 पूर्णांक cs, u32 setup)
अणु
	u32 bcr_mask, bcr = FMC2_BCR_WREN;
	u32 btr_mask, btr = 0;
	u32 bwtr_mask, bwtr = 0;

	bwtr_mask = FMC2_BXTR_ACCMOD;
	btr_mask = FMC2_BXTR_ACCMOD;
	bcr_mask = FMC2_BCR_MUXEN | FMC2_BCR_MTYP | FMC2_BCR_FACCEN |
		   FMC2_BCR_WREN | FMC2_BCR_WAITEN | FMC2_BCR_BURSTEN |
		   FMC2_BCR_EXTMOD | FMC2_BCR_CBURSTRW;

	चयन (setup) अणु
	हाल FMC2_ASYNC_MODE_1_SRAM:
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_SRAM);
		/*
		 * MUXEN = 0, MTYP = 0, FACCEN = 0, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 0, ACCMOD = 0
		 */
		अवरोध;
	हाल FMC2_ASYNC_MODE_1_PSRAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 0, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_PSRAM);
		अवरोध;
	हाल FMC2_ASYNC_MODE_A_SRAM:
		/*
		 * MUXEN = 0, MTYP = 0, FACCEN = 0, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 1, CBURSTRW = 0, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_SRAM);
		bcr |= FMC2_BCR_EXTMOD;
		btr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_A);
		bwtr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_A);
		अवरोध;
	हाल FMC2_ASYNC_MODE_A_PSRAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 1, CBURSTRW = 0, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_PSRAM);
		bcr |= FMC2_BCR_EXTMOD;
		btr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_A);
		bwtr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_A);
		अवरोध;
	हाल FMC2_ASYNC_MODE_2_NOR:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 0, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);
		bcr |= FMC2_BCR_FACCEN;
		अवरोध;
	हाल FMC2_ASYNC_MODE_B_NOR:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 1, CBURSTRW = 0, ACCMOD = 1
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);
		bcr |= FMC2_BCR_FACCEN | FMC2_BCR_EXTMOD;
		btr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_B);
		bwtr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_B);
		अवरोध;
	हाल FMC2_ASYNC_MODE_C_NOR:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 1, CBURSTRW = 0, ACCMOD = 2
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);
		bcr |= FMC2_BCR_FACCEN | FMC2_BCR_EXTMOD;
		btr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_C);
		bwtr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_C);
		अवरोध;
	हाल FMC2_ASYNC_MODE_D_NOR:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BURSTEN = 0, WAITEN = 0,
		 * WREN = 1, EXTMOD = 1, CBURSTRW = 0, ACCMOD = 3
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);
		bcr |= FMC2_BCR_FACCEN | FMC2_BCR_EXTMOD;
		btr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_D);
		bwtr |= FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_D);
		अवरोध;
	हाल FMC2_SYNC_READ_SYNC_WRITE_PSRAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BURSTEN = 1, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 1, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_PSRAM);
		bcr |= FMC2_BCR_BURSTEN | FMC2_BCR_CBURSTRW;
		अवरोध;
	हाल FMC2_SYNC_READ_ASYNC_WRITE_PSRAM:
		/*
		 * MUXEN = 0, MTYP = 1, FACCEN = 0, BURSTEN = 1, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 0, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_PSRAM);
		bcr |= FMC2_BCR_BURSTEN;
		अवरोध;
	हाल FMC2_SYNC_READ_SYNC_WRITE_NOR:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BURSTEN = 1, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 1, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);
		bcr |= FMC2_BCR_FACCEN | FMC2_BCR_BURSTEN | FMC2_BCR_CBURSTRW;
		अवरोध;
	हाल FMC2_SYNC_READ_ASYNC_WRITE_NOR:
		/*
		 * MUXEN = 0, MTYP = 2, FACCEN = 1, BURSTEN = 1, WAITEN = 0,
		 * WREN = 1, EXTMOD = 0, CBURSTRW = 0, ACCMOD = 0
		 */
		bcr |= FIELD_PREP(FMC2_BCR_MTYP, FMC2_BCR_MTYP_NOR);
		bcr |= FMC2_BCR_FACCEN | FMC2_BCR_BURSTEN;
		अवरोध;
	शेष:
		/* Type of transaction not supported */
		वापस -EINVAL;
	पूर्ण

	अगर (bcr & FMC2_BCR_EXTMOD)
		regmap_update_bits(ebi->regmap, FMC2_BWTR(cs),
				   bwtr_mask, bwtr);
	regmap_update_bits(ebi->regmap, FMC2_BTR(cs), btr_mask, btr);
	regmap_update_bits(ebi->regmap, FMC2_BCR(cs), bcr_mask, bcr);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_buswidth(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				       स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				       पूर्णांक cs, u32 setup)
अणु
	u32 val;

	चयन (setup) अणु
	हाल FMC2_BUSWIDTH_8:
		val = FIELD_PREP(FMC2_BCR_MWID, FMC2_BCR_MWID_8);
		अवरोध;
	हाल FMC2_BUSWIDTH_16:
		val = FIELD_PREP(FMC2_BCR_MWID, FMC2_BCR_MWID_16);
		अवरोध;
	शेष:
		/* Buswidth not supported */
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(ebi->regmap, FMC2_BCR(cs), FMC2_BCR_MWID, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_cpsize(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				     स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				     पूर्णांक cs, u32 setup)
अणु
	u32 val;

	चयन (setup) अणु
	हाल FMC2_CPSIZE_0:
		val = FIELD_PREP(FMC2_BCR_CPSIZE, FMC2_BCR_CPSIZE_0);
		अवरोध;
	हाल FMC2_CPSIZE_128:
		val = FIELD_PREP(FMC2_BCR_CPSIZE, FMC2_BCR_CPSIZE_128);
		अवरोध;
	हाल FMC2_CPSIZE_256:
		val = FIELD_PREP(FMC2_BCR_CPSIZE, FMC2_BCR_CPSIZE_256);
		अवरोध;
	हाल FMC2_CPSIZE_512:
		val = FIELD_PREP(FMC2_BCR_CPSIZE, FMC2_BCR_CPSIZE_512);
		अवरोध;
	हाल FMC2_CPSIZE_1024:
		val = FIELD_PREP(FMC2_BCR_CPSIZE, FMC2_BCR_CPSIZE_1024);
		अवरोध;
	शेष:
		/* Cpsize not supported */
		वापस -EINVAL;
	पूर्ण

	regmap_update_bits(ebi->regmap, FMC2_BCR(cs), FMC2_BCR_CPSIZE, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_bl_setup(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				       स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				       पूर्णांक cs, u32 setup)
अणु
	u32 val;

	val = min_t(u32, setup, FMC2_BCR_NBLSET_MAX);
	val = FIELD_PREP(FMC2_BCR_NBLSET, val);
	regmap_update_bits(ebi->regmap, FMC2_BCR(cs), FMC2_BCR_NBLSET, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_address_setup(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					    स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					    पूर्णांक cs, u32 setup)
अणु
	u32 bcr, bxtr, reg;
	u32 val = FIELD_PREP(FMC2_BXTR_ACCMOD, FMC2_BXTR_EXTMOD_D);
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_ebi_get_reg(prop->reg_type, cs, &reg);
	अगर (ret)
		वापस ret;

	regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);
	अगर (prop->reg_type == FMC2_REG_BWTR)
		regmap_पढ़ो(ebi->regmap, FMC2_BWTR(cs), &bxtr);
	अन्यथा
		regmap_पढ़ो(ebi->regmap, FMC2_BTR(cs), &bxtr);

	अगर ((bxtr & FMC2_BXTR_ACCMOD) == val || bcr & FMC2_BCR_MUXEN)
		val = clamp_val(setup, 1, FMC2_BXTR_ADDSET_MAX);
	अन्यथा
		val = min_t(u32, setup, FMC2_BXTR_ADDSET_MAX);
	val = FIELD_PREP(FMC2_BXTR_ADDSET, val);
	regmap_update_bits(ebi->regmap, reg, FMC2_BXTR_ADDSET, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_address_hold(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					   स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					   पूर्णांक cs, u32 setup)
अणु
	u32 val, reg;
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_ebi_get_reg(prop->reg_type, cs, &reg);
	अगर (ret)
		वापस ret;

	val = clamp_val(setup, 1, FMC2_BXTR_ADDHLD_MAX);
	val = FIELD_PREP(FMC2_BXTR_ADDHLD, val);
	regmap_update_bits(ebi->regmap, reg, FMC2_BXTR_ADDHLD, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_data_setup(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					 स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					 पूर्णांक cs, u32 setup)
अणु
	u32 val, reg;
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_ebi_get_reg(prop->reg_type, cs, &reg);
	अगर (ret)
		वापस ret;

	val = clamp_val(setup, 1, FMC2_BXTR_DATAST_MAX);
	val = FIELD_PREP(FMC2_BXTR_DATAST, val);
	regmap_update_bits(ebi->regmap, reg, FMC2_BXTR_DATAST, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_bus_turnaround(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					     स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					     पूर्णांक cs, u32 setup)
अणु
	u32 val, reg;
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_ebi_get_reg(prop->reg_type, cs, &reg);
	अगर (ret)
		वापस ret;

	val = setup ? min_t(u32, setup - 1, FMC2_BXTR_BUSTURN_MAX) : 0;
	val = FIELD_PREP(FMC2_BXTR_BUSTURN, val);
	regmap_update_bits(ebi->regmap, reg, FMC2_BXTR_BUSTURN, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_data_hold(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					पूर्णांक cs, u32 setup)
अणु
	u32 val, reg;
	पूर्णांक ret;

	ret = sपंचांग32_fmc2_ebi_get_reg(prop->reg_type, cs, &reg);
	अगर (ret)
		वापस ret;

	अगर (prop->reg_type == FMC2_REG_BWTR)
		val = setup ? min_t(u32, setup - 1, FMC2_BXTR_DATAHLD_MAX) : 0;
	अन्यथा
		val = min_t(u32, setup, FMC2_BXTR_DATAHLD_MAX);
	val = FIELD_PREP(FMC2_BXTR_DATAHLD, val);
	regmap_update_bits(ebi->regmap, reg, FMC2_BXTR_DATAHLD, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_clk_period(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					 स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					 पूर्णांक cs, u32 setup)
अणु
	u32 val;

	val = setup ? clamp_val(setup - 1, 1, FMC2_BTR_CLKDIV_MAX) : 1;
	val = FIELD_PREP(FMC2_BTR_CLKDIV, val);
	regmap_update_bits(ebi->regmap, FMC2_BTR(cs), FMC2_BTR_CLKDIV, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_data_latency(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					   स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					   पूर्णांक cs, u32 setup)
अणु
	u32 val;

	val = setup > 1 ? min_t(u32, setup - 2, FMC2_BTR_DATLAT_MAX) : 0;
	val = FIELD_PREP(FMC2_BTR_DATLAT, val);
	regmap_update_bits(ebi->regmap, FMC2_BTR(cs), FMC2_BTR_DATLAT, val);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_set_max_low_pulse(काष्ठा sपंचांग32_fmc2_ebi *ebi,
					    स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
					    पूर्णांक cs, u32 setup)
अणु
	u32 old_val, new_val, pcscntr;

	अगर (setup < 1)
		वापस 0;

	regmap_पढ़ो(ebi->regmap, FMC2_PCSCNTR, &pcscntr);

	/* Enable counter क्रम the bank */
	regmap_update_bits(ebi->regmap, FMC2_PCSCNTR,
			   FMC2_PCSCNTR_CNTBEN(cs),
			   FMC2_PCSCNTR_CNTBEN(cs));

	new_val = min_t(u32, setup - 1, FMC2_PCSCNTR_CSCOUNT_MAX);
	old_val = FIELD_GET(FMC2_PCSCNTR_CSCOUNT, pcscntr);
	अगर (old_val && new_val > old_val)
		/* Keep current counter value */
		वापस 0;

	new_val = FIELD_PREP(FMC2_PCSCNTR_CSCOUNT, new_val);
	regmap_update_bits(ebi->regmap, FMC2_PCSCNTR,
			   FMC2_PCSCNTR_CSCOUNT, new_val);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा sपंचांग32_fmc2_prop sपंचांग32_fmc2_child_props[] = अणु
	/* st,fmc2-ebi-cs-trans-type must be the first property */
	अणु
		.name = "st,fmc2-ebi-cs-transaction-type",
		.mprop = true,
		.set = sपंचांग32_fmc2_ebi_set_trans_type,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-cclk-enable",
		.bprop = true,
		.reg_type = FMC2_REG_BCR,
		.reg_mask = FMC2_BCR1_CCLKEN,
		.check = sपंचांग32_fmc2_ebi_check_cclk,
		.set = sपंचांग32_fmc2_ebi_set_bit_field,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-mux-enable",
		.bprop = true,
		.reg_type = FMC2_REG_BCR,
		.reg_mask = FMC2_BCR_MUXEN,
		.check = sपंचांग32_fmc2_ebi_check_mux,
		.set = sपंचांग32_fmc2_ebi_set_bit_field,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-buswidth",
		.reset_val = FMC2_BUSWIDTH_16,
		.set = sपंचांग32_fmc2_ebi_set_buswidth,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-waitpol-high",
		.bprop = true,
		.reg_type = FMC2_REG_BCR,
		.reg_mask = FMC2_BCR_WAITPOL,
		.set = sपंचांग32_fmc2_ebi_set_bit_field,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-waitcfg-enable",
		.bprop = true,
		.reg_type = FMC2_REG_BCR,
		.reg_mask = FMC2_BCR_WAITCFG,
		.check = sपंचांग32_fmc2_ebi_check_रुकोcfg,
		.set = sपंचांग32_fmc2_ebi_set_bit_field,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-wait-enable",
		.bprop = true,
		.reg_type = FMC2_REG_BCR,
		.reg_mask = FMC2_BCR_WAITEN,
		.check = sपंचांग32_fmc2_ebi_check_sync_trans,
		.set = sपंचांग32_fmc2_ebi_set_bit_field,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-asyncwait-enable",
		.bprop = true,
		.reg_type = FMC2_REG_BCR,
		.reg_mask = FMC2_BCR_ASYNCWAIT,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.set = sपंचांग32_fmc2_ebi_set_bit_field,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-cpsize",
		.check = sपंचांग32_fmc2_ebi_check_cpsize,
		.set = sपंचांग32_fmc2_ebi_set_cpsize,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-byte-lane-setup-ns",
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_bl_setup,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-address-setup-ns",
		.reg_type = FMC2_REG_BTR,
		.reset_val = FMC2_BXTR_ADDSET_MAX,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_address_setup,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-address-hold-ns",
		.reg_type = FMC2_REG_BTR,
		.reset_val = FMC2_BXTR_ADDHLD_MAX,
		.check = sपंचांग32_fmc2_ebi_check_address_hold,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_address_hold,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-data-setup-ns",
		.reg_type = FMC2_REG_BTR,
		.reset_val = FMC2_BXTR_DATAST_MAX,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_data_setup,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-bus-turnaround-ns",
		.reg_type = FMC2_REG_BTR,
		.reset_val = FMC2_BXTR_BUSTURN_MAX + 1,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_bus_turnaround,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-data-hold-ns",
		.reg_type = FMC2_REG_BTR,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_data_hold,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-clk-period-ns",
		.reset_val = FMC2_BTR_CLKDIV_MAX + 1,
		.check = sपंचांग32_fmc2_ebi_check_clk_period,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_clk_period,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-data-latency-ns",
		.check = sपंचांग32_fmc2_ebi_check_sync_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_clk_period,
		.set = sपंचांग32_fmc2_ebi_set_data_latency,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-write-address-setup-ns",
		.reg_type = FMC2_REG_BWTR,
		.reset_val = FMC2_BXTR_ADDSET_MAX,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_address_setup,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-write-address-hold-ns",
		.reg_type = FMC2_REG_BWTR,
		.reset_val = FMC2_BXTR_ADDHLD_MAX,
		.check = sपंचांग32_fmc2_ebi_check_address_hold,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_address_hold,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-write-data-setup-ns",
		.reg_type = FMC2_REG_BWTR,
		.reset_val = FMC2_BXTR_DATAST_MAX,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_data_setup,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-write-bus-turnaround-ns",
		.reg_type = FMC2_REG_BWTR,
		.reset_val = FMC2_BXTR_BUSTURN_MAX + 1,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_bus_turnaround,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-write-data-hold-ns",
		.reg_type = FMC2_REG_BWTR,
		.check = sपंचांग32_fmc2_ebi_check_async_trans,
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_data_hold,
	पूर्ण,
	अणु
		.name = "st,fmc2-ebi-cs-max-low-pulse-ns",
		.calculate = sपंचांग32_fmc2_ebi_ns_to_घड़ी_cycles,
		.set = sपंचांग32_fmc2_ebi_set_max_low_pulse,
	पूर्ण,
पूर्ण;

अटल पूर्णांक sपंचांग32_fmc2_ebi_parse_prop(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				     काष्ठा device_node *dev_node,
				     स्थिर काष्ठा sपंचांग32_fmc2_prop *prop,
				     पूर्णांक cs)
अणु
	काष्ठा device *dev = ebi->dev;
	u32 setup = 0;

	अगर (!prop->set) अणु
		dev_err(dev, "property %s is not well defined\n", prop->name);
		वापस -EINVAL;
	पूर्ण

	अगर (prop->check && prop->check(ebi, prop, cs))
		/* Skeep this property */
		वापस 0;

	अगर (prop->bprop) अणु
		bool bprop;

		bprop = of_property_पढ़ो_bool(dev_node, prop->name);
		अगर (prop->mprop && !bprop) अणु
			dev_err(dev, "mandatory property %s not defined in the device tree\n",
				prop->name);
			वापस -EINVAL;
		पूर्ण

		अगर (bprop)
			setup = 1;
	पूर्ण अन्यथा अणु
		u32 val;
		पूर्णांक ret;

		ret = of_property_पढ़ो_u32(dev_node, prop->name, &val);
		अगर (prop->mprop && ret) अणु
			dev_err(dev, "mandatory property %s not defined in the device tree\n",
				prop->name);
			वापस ret;
		पूर्ण

		अगर (ret)
			setup = prop->reset_val;
		अन्यथा अगर (prop->calculate)
			setup = prop->calculate(ebi, cs, val);
		अन्यथा
			setup = val;
	पूर्ण

	वापस prop->set(ebi, prop, cs, setup);
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_enable_bank(काष्ठा sपंचांग32_fmc2_ebi *ebi, पूर्णांक cs)
अणु
	regmap_update_bits(ebi->regmap, FMC2_BCR(cs),
			   FMC2_BCR_MBKEN, FMC2_BCR_MBKEN);
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_disable_bank(काष्ठा sपंचांग32_fmc2_ebi *ebi, पूर्णांक cs)
अणु
	regmap_update_bits(ebi->regmap, FMC2_BCR(cs), FMC2_BCR_MBKEN, 0);
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_save_setup(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	अचिन्हित पूर्णांक cs;

	क्रम (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) अणु
		regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &ebi->bcr[cs]);
		regmap_पढ़ो(ebi->regmap, FMC2_BTR(cs), &ebi->btr[cs]);
		regmap_पढ़ो(ebi->regmap, FMC2_BWTR(cs), &ebi->bwtr[cs]);
	पूर्ण

	regmap_पढ़ो(ebi->regmap, FMC2_PCSCNTR, &ebi->pcscntr);
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_set_setup(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	अचिन्हित पूर्णांक cs;

	क्रम (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) अणु
		regmap_ग_लिखो(ebi->regmap, FMC2_BCR(cs), ebi->bcr[cs]);
		regmap_ग_लिखो(ebi->regmap, FMC2_BTR(cs), ebi->btr[cs]);
		regmap_ग_लिखो(ebi->regmap, FMC2_BWTR(cs), ebi->bwtr[cs]);
	पूर्ण

	regmap_ग_लिखो(ebi->regmap, FMC2_PCSCNTR, ebi->pcscntr);
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_disable_banks(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	अचिन्हित पूर्णांक cs;

	क्रम (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) अणु
		अगर (!(ebi->bank_asचिन्हित & BIT(cs)))
			जारी;

		sपंचांग32_fmc2_ebi_disable_bank(ebi, cs);
	पूर्ण
पूर्ण

/* NWAIT संकेत can not be connected to EBI controller and न_अंकD controller */
अटल bool sपंचांग32_fmc2_ebi_nरुको_used_by_ctrls(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	अचिन्हित पूर्णांक cs;
	u32 bcr;

	क्रम (cs = 0; cs < FMC2_MAX_EBI_CE; cs++) अणु
		अगर (!(ebi->bank_asचिन्हित & BIT(cs)))
			जारी;

		regmap_पढ़ो(ebi->regmap, FMC2_BCR(cs), &bcr);
		अगर ((bcr & FMC2_BCR_WAITEN || bcr & FMC2_BCR_ASYNCWAIT) &&
		    ebi->bank_asचिन्हित & BIT(FMC2_न_अंकD))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_enable(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	regmap_update_bits(ebi->regmap, FMC2_BCR1,
			   FMC2_BCR1_FMC2EN, FMC2_BCR1_FMC2EN);
पूर्ण

अटल व्योम sपंचांग32_fmc2_ebi_disable(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	regmap_update_bits(ebi->regmap, FMC2_BCR1, FMC2_BCR1_FMC2EN, 0);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_setup_cs(काष्ठा sपंचांग32_fmc2_ebi *ebi,
				   काष्ठा device_node *dev_node,
				   u32 cs)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	sपंचांग32_fmc2_ebi_disable_bank(ebi, cs);

	क्रम (i = 0; i < ARRAY_SIZE(sपंचांग32_fmc2_child_props); i++) अणु
		स्थिर काष्ठा sपंचांग32_fmc2_prop *p = &sपंचांग32_fmc2_child_props[i];

		ret = sपंचांग32_fmc2_ebi_parse_prop(ebi, dev_node, p, cs);
		अगर (ret) अणु
			dev_err(ebi->dev, "property %s could not be set: %d\n",
				p->name, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	sपंचांग32_fmc2_ebi_enable_bank(ebi, cs);

	वापस 0;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_parse_dt(काष्ठा sपंचांग32_fmc2_ebi *ebi)
अणु
	काष्ठा device *dev = ebi->dev;
	काष्ठा device_node *child;
	bool child_found = false;
	u32 bank;
	पूर्णांक ret;

	क्रम_each_available_child_of_node(dev->of_node, child) अणु
		ret = of_property_पढ़ो_u32(child, "reg", &bank);
		अगर (ret) अणु
			dev_err(dev, "could not retrieve reg property: %d\n",
				ret);
			वापस ret;
		पूर्ण

		अगर (bank >= FMC2_MAX_BANKS) अणु
			dev_err(dev, "invalid reg value: %d\n", bank);
			वापस -EINVAL;
		पूर्ण

		अगर (ebi->bank_asचिन्हित & BIT(bank)) अणु
			dev_err(dev, "bank already assigned: %d\n", bank);
			वापस -EINVAL;
		पूर्ण

		अगर (bank < FMC2_MAX_EBI_CE) अणु
			ret = sपंचांग32_fmc2_ebi_setup_cs(ebi, child, bank);
			अगर (ret) अणु
				dev_err(dev, "setup chip select %d failed: %d\n",
					bank, ret);
				वापस ret;
			पूर्ण
		पूर्ण

		ebi->bank_asचिन्हित |= BIT(bank);
		child_found = true;
	पूर्ण

	अगर (!child_found) अणु
		dev_warn(dev, "no subnodes found, disable the driver.\n");
		वापस -ENODEV;
	पूर्ण

	अगर (sपंचांग32_fmc2_ebi_nरुको_used_by_ctrls(ebi)) अणु
		dev_err(dev, "NWAIT signal connected to EBI and NAND controllers\n");
		वापस -EINVAL;
	पूर्ण

	sपंचांग32_fmc2_ebi_enable(ebi);

	वापस of_platक्रमm_populate(dev->of_node, शून्य, शून्य, dev);
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा sपंचांग32_fmc2_ebi *ebi;
	काष्ठा reset_control *rstc;
	पूर्णांक ret;

	ebi = devm_kzalloc(&pdev->dev, माप(*ebi), GFP_KERNEL);
	अगर (!ebi)
		वापस -ENOMEM;

	ebi->dev = dev;

	ebi->regmap = device_node_to_regmap(dev->of_node);
	अगर (IS_ERR(ebi->regmap))
		वापस PTR_ERR(ebi->regmap);

	ebi->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(ebi->clk))
		वापस PTR_ERR(ebi->clk);

	rstc = devm_reset_control_get(dev, शून्य);
	अगर (PTR_ERR(rstc) == -EPROBE_DEFER)
		वापस -EPROBE_DEFER;

	ret = clk_prepare_enable(ebi->clk);
	अगर (ret)
		वापस ret;

	अगर (!IS_ERR(rstc)) अणु
		reset_control_निश्चित(rstc);
		reset_control_deनिश्चित(rstc);
	पूर्ण

	ret = sपंचांग32_fmc2_ebi_parse_dt(ebi);
	अगर (ret)
		जाओ err_release;

	sपंचांग32_fmc2_ebi_save_setup(ebi);
	platक्रमm_set_drvdata(pdev, ebi);

	वापस 0;

err_release:
	sपंचांग32_fmc2_ebi_disable_banks(ebi);
	sपंचांग32_fmc2_ebi_disable(ebi);
	clk_disable_unprepare(ebi->clk);

	वापस ret;
पूर्ण

अटल पूर्णांक sपंचांग32_fmc2_ebi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sपंचांग32_fmc2_ebi *ebi = platक्रमm_get_drvdata(pdev);

	of_platक्रमm_depopulate(&pdev->dev);
	sपंचांग32_fmc2_ebi_disable_banks(ebi);
	sपंचांग32_fmc2_ebi_disable(ebi);
	clk_disable_unprepare(ebi->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_fmc2_ebi_suspend(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_fmc2_ebi *ebi = dev_get_drvdata(dev);

	sपंचांग32_fmc2_ebi_disable(ebi);
	clk_disable_unprepare(ebi->clk);
	pinctrl_pm_select_sleep_state(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused sपंचांग32_fmc2_ebi_resume(काष्ठा device *dev)
अणु
	काष्ठा sपंचांग32_fmc2_ebi *ebi = dev_get_drvdata(dev);
	पूर्णांक ret;

	pinctrl_pm_select_शेष_state(dev);

	ret = clk_prepare_enable(ebi->clk);
	अगर (ret)
		वापस ret;

	sपंचांग32_fmc2_ebi_set_setup(ebi);
	sपंचांग32_fmc2_ebi_enable(ebi);

	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(sपंचांग32_fmc2_ebi_pm_ops, sपंचांग32_fmc2_ebi_suspend,
			 sपंचांग32_fmc2_ebi_resume);

अटल स्थिर काष्ठा of_device_id sपंचांग32_fmc2_ebi_match[] = अणु
	अणु.compatible = "st,stm32mp1-fmc2-ebi"पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, sपंचांग32_fmc2_ebi_match);

अटल काष्ठा platक्रमm_driver sपंचांग32_fmc2_ebi_driver = अणु
	.probe	= sपंचांग32_fmc2_ebi_probe,
	.हटाओ	= sपंचांग32_fmc2_ebi_हटाओ,
	.driver	= अणु
		.name = "stm32_fmc2_ebi",
		.of_match_table = sपंचांग32_fmc2_ebi_match,
		.pm = &sपंचांग32_fmc2_ebi_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sपंचांग32_fmc2_ebi_driver);

MODULE_ALIAS("platform:stm32_fmc2_ebi");
MODULE_AUTHOR("Christophe Kerello <christophe.kerello@st.com>");
MODULE_DESCRIPTION("STMicroelectronics STM32 FMC2 ebi driver");
MODULE_LICENSE("GPL v2");
