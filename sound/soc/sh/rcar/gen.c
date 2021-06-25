<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car Gen1 SRU/SSI support
//
// Copyright (C) 2013 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

/*
 * #घोषणा DEBUG
 *
 * you can also add below in
 * $अणुLINUXपूर्ण/drivers/base/regmap/regmap.c
 * क्रम regmap debug
 *
 * #घोषणा LOG_DEVICE "xxxx.rcar_sound"
 */

#समावेश "rsnd.h"

काष्ठा rsnd_gen अणु
	काष्ठा rsnd_gen_ops *ops;

	/* RSND_BASE_MAX base */
	व्योम __iomem *base[RSND_BASE_MAX];
	phys_addr_t res[RSND_BASE_MAX];
	काष्ठा regmap *regmap[RSND_BASE_MAX];

	/* RSND_REG_MAX base */
	काष्ठा regmap_field *regs[REG_MAX];
	स्थिर अक्षर *reg_name[REG_MAX];
पूर्ण;

#घोषणा rsnd_priv_to_gen(p)	((काष्ठा rsnd_gen *)(p)->gen)
#घोषणा rsnd_reg_name(gen, id)	((gen)->reg_name[id])

काष्ठा rsnd_regmap_field_conf अणु
	पूर्णांक idx;
	अचिन्हित पूर्णांक reg_offset;
	अचिन्हित पूर्णांक id_offset;
	स्थिर अक्षर *reg_name;
पूर्ण;

#घोषणा RSND_REG_SET(id, offset, _id_offset, n)	\
अणु						\
	.idx = id,				\
	.reg_offset = offset,			\
	.id_offset = _id_offset,		\
	.reg_name = n,				\
पूर्ण
/* single address mapping */
#घोषणा RSND_GEN_S_REG(id, offset)	\
	RSND_REG_SET(id, offset, 0, #id)

/* multi address mapping */
#घोषणा RSND_GEN_M_REG(id, offset, _id_offset)	\
	RSND_REG_SET(id, offset, _id_offset, #id)

/*
 *		basic function
 */
अटल पूर्णांक rsnd_is_accessible_reg(काष्ठा rsnd_priv *priv,
				  काष्ठा rsnd_gen *gen, क्रमागत rsnd_reg reg)
अणु
	अगर (!gen->regs[reg]) अणु
		काष्ठा device *dev = rsnd_priv_to_dev(priv);

		dev_err(dev, "unsupported register access %x\n", reg);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक rsnd_mod_id_cmd(काष्ठा rsnd_mod *mod)
अणु
	अगर (mod->ops->id_cmd)
		वापस mod->ops->id_cmd(mod);

	वापस rsnd_mod_id(mod);
पूर्ण

u32 rsnd_mod_पढ़ो(काष्ठा rsnd_mod *mod, क्रमागत rsnd_reg reg)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_gen *gen = rsnd_priv_to_gen(priv);
	u32 val;

	अगर (!rsnd_is_accessible_reg(priv, gen, reg))
		वापस 0;

	regmap_fields_पढ़ो(gen->regs[reg], rsnd_mod_id_cmd(mod), &val);

	dev_dbg(dev, "r %s - %-18s (%4d) : %08x\n",
		rsnd_mod_name(mod),
		rsnd_reg_name(gen, reg), reg, val);

	वापस val;
पूर्ण

व्योम rsnd_mod_ग_लिखो(काष्ठा rsnd_mod *mod,
		    क्रमागत rsnd_reg reg, u32 data)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_gen *gen = rsnd_priv_to_gen(priv);

	अगर (!rsnd_is_accessible_reg(priv, gen, reg))
		वापस;

	regmap_fields_क्रमce_ग_लिखो(gen->regs[reg], rsnd_mod_id_cmd(mod), data);

	dev_dbg(dev, "w %s - %-18s (%4d) : %08x\n",
		rsnd_mod_name(mod),
		rsnd_reg_name(gen, reg), reg, data);
पूर्ण

व्योम rsnd_mod_bset(काष्ठा rsnd_mod *mod,
		   क्रमागत rsnd_reg reg, u32 mask, u32 data)
अणु
	काष्ठा rsnd_priv *priv = rsnd_mod_to_priv(mod);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_gen *gen = rsnd_priv_to_gen(priv);

	अगर (!rsnd_is_accessible_reg(priv, gen, reg))
		वापस;

	regmap_fields_क्रमce_update_bits(gen->regs[reg],
					rsnd_mod_id_cmd(mod), mask, data);

	dev_dbg(dev, "b %s - %-18s (%4d) : %08x/%08x\n",
		rsnd_mod_name(mod),
		rsnd_reg_name(gen, reg), reg, data, mask);

पूर्ण

phys_addr_t rsnd_gen_get_phy_addr(काष्ठा rsnd_priv *priv, पूर्णांक reg_id)
अणु
	काष्ठा rsnd_gen *gen = rsnd_priv_to_gen(priv);

	वापस	gen->res[reg_id];
पूर्ण

#घोषणा rsnd_gen_regmap_init(priv, id_size, reg_id, name, conf)		\
	_rsnd_gen_regmap_init(priv, id_size, reg_id, name, conf, ARRAY_SIZE(conf))
अटल पूर्णांक _rsnd_gen_regmap_init(काष्ठा rsnd_priv *priv,
				 पूर्णांक id_size,
				 पूर्णांक reg_id,
				 स्थिर अक्षर *name,
				 स्थिर काष्ठा rsnd_regmap_field_conf *conf,
				 पूर्णांक conf_size)
अणु
	काष्ठा platक्रमm_device *pdev = rsnd_priv_to_pdev(priv);
	काष्ठा rsnd_gen *gen = rsnd_priv_to_gen(priv);
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा resource *res;
	काष्ठा regmap_config regc;
	काष्ठा regmap_field *regs;
	काष्ठा regmap *regmap;
	काष्ठा reg_field regf;
	व्योम __iomem *base;
	पूर्णांक i;

	स_रखो(&regc, 0, माप(regc));
	regc.reg_bits = 32;
	regc.val_bits = 32;
	regc.reg_stride = 4;
	regc.name = name;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, name);
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, reg_id);
	अगर (!res)
		वापस -ENODEV;

	base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(base))
		वापस PTR_ERR(base);

	regmap = devm_regmap_init_mmio(dev, base, &regc);
	अगर (IS_ERR(regmap))
		वापस PTR_ERR(regmap);

	/* RSND_BASE_MAX base */
	gen->base[reg_id] = base;
	gen->regmap[reg_id] = regmap;
	gen->res[reg_id] = res->start;

	क्रम (i = 0; i < conf_size; i++) अणु

		regf.reg	= conf[i].reg_offset;
		regf.id_offset	= conf[i].id_offset;
		regf.lsb	= 0;
		regf.msb	= 31;
		regf.id_size	= id_size;

		regs = devm_regmap_field_alloc(dev, regmap, regf);
		अगर (IS_ERR(regs))
			वापस PTR_ERR(regs);

		/* RSND_REG_MAX base */
		gen->regs[conf[i].idx] = regs;
		gen->reg_name[conf[i].idx] = conf[i].reg_name;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *		Gen2
 */
अटल पूर्णांक rsnd_gen2_probe(काष्ठा rsnd_priv *priv)
अणु
	अटल स्थिर काष्ठा rsnd_regmap_field_conf conf_ssiu[] = अणु
		RSND_GEN_S_REG(SSI_MODE0,	0x800),
		RSND_GEN_S_REG(SSI_MODE1,	0x804),
		RSND_GEN_S_REG(SSI_MODE2,	0x808),
		RSND_GEN_S_REG(SSI_CONTROL,	0x810),
		RSND_GEN_S_REG(SSI_SYS_STATUS0,	0x840),
		RSND_GEN_S_REG(SSI_SYS_STATUS1,	0x844),
		RSND_GEN_S_REG(SSI_SYS_STATUS2,	0x848),
		RSND_GEN_S_REG(SSI_SYS_STATUS3,	0x84c),
		RSND_GEN_S_REG(SSI_SYS_STATUS4,	0x880),
		RSND_GEN_S_REG(SSI_SYS_STATUS5,	0x884),
		RSND_GEN_S_REG(SSI_SYS_STATUS6,	0x888),
		RSND_GEN_S_REG(SSI_SYS_STATUS7,	0x88c),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE0, 0x850),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE1, 0x854),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE2, 0x858),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE3, 0x85c),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE4, 0x890),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE5, 0x894),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE6, 0x898),
		RSND_GEN_S_REG(SSI_SYS_INT_ENABLE7, 0x89c),
		RSND_GEN_S_REG(HDMI0_SEL,	0x9e0),
		RSND_GEN_S_REG(HDMI1_SEL,	0x9e4),

		/* FIXME: it needs SSI_MODE2/3 in the future */
		RSND_GEN_M_REG(SSI_BUSIF0_MODE,		0x0,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF0_ADINR,	0x4,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF0_DALIGN,	0x8,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF1_MODE,		0x20,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF1_ADINR,	0x24,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF1_DALIGN,	0x28,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF2_MODE,		0x40,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF2_ADINR,	0x44,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF2_DALIGN,	0x48,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF3_MODE,		0x60,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF3_ADINR,	0x64,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF3_DALIGN,	0x68,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF4_MODE,		0x500,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF4_ADINR,	0x504,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF4_DALIGN,	0x508,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF5_MODE,		0x520,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF5_ADINR,	0x524,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF5_DALIGN,	0x528,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF6_MODE,		0x540,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF6_ADINR,	0x544,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF6_DALIGN,	0x548,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF7_MODE,		0x560,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF7_ADINR,	0x564,	0x80),
		RSND_GEN_M_REG(SSI_BUSIF7_DALIGN,	0x568,	0x80),
		RSND_GEN_M_REG(SSI_MODE,		0xc,	0x80),
		RSND_GEN_M_REG(SSI_CTRL,		0x10,	0x80),
		RSND_GEN_M_REG(SSI_INT_ENABLE,		0x18,	0x80),
		RSND_GEN_S_REG(SSI9_BUSIF0_MODE,	0x48c),
		RSND_GEN_S_REG(SSI9_BUSIF0_ADINR,	0x484),
		RSND_GEN_S_REG(SSI9_BUSIF0_DALIGN,	0x488),
		RSND_GEN_S_REG(SSI9_BUSIF1_MODE,	0x4a0),
		RSND_GEN_S_REG(SSI9_BUSIF1_ADINR,	0x4a4),
		RSND_GEN_S_REG(SSI9_BUSIF1_DALIGN,	0x4a8),
		RSND_GEN_S_REG(SSI9_BUSIF2_MODE,	0x4c0),
		RSND_GEN_S_REG(SSI9_BUSIF2_ADINR,	0x4c4),
		RSND_GEN_S_REG(SSI9_BUSIF2_DALIGN,	0x4c8),
		RSND_GEN_S_REG(SSI9_BUSIF3_MODE,	0x4e0),
		RSND_GEN_S_REG(SSI9_BUSIF3_ADINR,	0x4e4),
		RSND_GEN_S_REG(SSI9_BUSIF3_DALIGN,	0x4e8),
		RSND_GEN_S_REG(SSI9_BUSIF4_MODE,	0xd80),
		RSND_GEN_S_REG(SSI9_BUSIF4_ADINR,	0xd84),
		RSND_GEN_S_REG(SSI9_BUSIF4_DALIGN,	0xd88),
		RSND_GEN_S_REG(SSI9_BUSIF5_MODE,	0xda0),
		RSND_GEN_S_REG(SSI9_BUSIF5_ADINR,	0xda4),
		RSND_GEN_S_REG(SSI9_BUSIF5_DALIGN,	0xda8),
		RSND_GEN_S_REG(SSI9_BUSIF6_MODE,	0xdc0),
		RSND_GEN_S_REG(SSI9_BUSIF6_ADINR,	0xdc4),
		RSND_GEN_S_REG(SSI9_BUSIF6_DALIGN,	0xdc8),
		RSND_GEN_S_REG(SSI9_BUSIF7_MODE,	0xde0),
		RSND_GEN_S_REG(SSI9_BUSIF7_ADINR,	0xde4),
		RSND_GEN_S_REG(SSI9_BUSIF7_DALIGN,	0xde8),
	पूर्ण;

	अटल स्थिर काष्ठा rsnd_regmap_field_conf conf_scu[] = अणु
		RSND_GEN_M_REG(SRC_I_BUSIF_MODE,0x0,	0x20),
		RSND_GEN_M_REG(SRC_O_BUSIF_MODE,0x4,	0x20),
		RSND_GEN_M_REG(SRC_BUSIF_DALIGN,0x8,	0x20),
		RSND_GEN_M_REG(SRC_ROUTE_MODE0,	0xc,	0x20),
		RSND_GEN_M_REG(SRC_CTRL,	0x10,	0x20),
		RSND_GEN_M_REG(SRC_INT_ENABLE0,	0x18,	0x20),
		RSND_GEN_M_REG(CMD_BUSIF_MODE,	0x184,	0x20),
		RSND_GEN_M_REG(CMD_BUSIF_DALIGN,0x188,	0x20),
		RSND_GEN_M_REG(CMD_ROUTE_SLCT,	0x18c,	0x20),
		RSND_GEN_M_REG(CMD_CTRL,	0x190,	0x20),
		RSND_GEN_S_REG(SCU_SYS_STATUS0,	0x1c8),
		RSND_GEN_S_REG(SCU_SYS_INT_EN0,	0x1cc),
		RSND_GEN_S_REG(SCU_SYS_STATUS1,	0x1d0),
		RSND_GEN_S_REG(SCU_SYS_INT_EN1,	0x1d4),
		RSND_GEN_M_REG(SRC_SWRSR,	0x200,	0x40),
		RSND_GEN_M_REG(SRC_SRCIR,	0x204,	0x40),
		RSND_GEN_M_REG(SRC_ADINR,	0x214,	0x40),
		RSND_GEN_M_REG(SRC_IFSCR,	0x21c,	0x40),
		RSND_GEN_M_REG(SRC_IFSVR,	0x220,	0x40),
		RSND_GEN_M_REG(SRC_SRCCR,	0x224,	0x40),
		RSND_GEN_M_REG(SRC_BSDSR,	0x22c,	0x40),
		RSND_GEN_M_REG(SRC_BSISR,	0x238,	0x40),
		RSND_GEN_M_REG(CTU_SWRSR,	0x500,	0x100),
		RSND_GEN_M_REG(CTU_CTUIR,	0x504,	0x100),
		RSND_GEN_M_REG(CTU_ADINR,	0x508,	0x100),
		RSND_GEN_M_REG(CTU_CPMDR,	0x510,	0x100),
		RSND_GEN_M_REG(CTU_SCMDR,	0x514,	0x100),
		RSND_GEN_M_REG(CTU_SV00R,	0x518,	0x100),
		RSND_GEN_M_REG(CTU_SV01R,	0x51c,	0x100),
		RSND_GEN_M_REG(CTU_SV02R,	0x520,	0x100),
		RSND_GEN_M_REG(CTU_SV03R,	0x524,	0x100),
		RSND_GEN_M_REG(CTU_SV04R,	0x528,	0x100),
		RSND_GEN_M_REG(CTU_SV05R,	0x52c,	0x100),
		RSND_GEN_M_REG(CTU_SV06R,	0x530,	0x100),
		RSND_GEN_M_REG(CTU_SV07R,	0x534,	0x100),
		RSND_GEN_M_REG(CTU_SV10R,	0x538,	0x100),
		RSND_GEN_M_REG(CTU_SV11R,	0x53c,	0x100),
		RSND_GEN_M_REG(CTU_SV12R,	0x540,	0x100),
		RSND_GEN_M_REG(CTU_SV13R,	0x544,	0x100),
		RSND_GEN_M_REG(CTU_SV14R,	0x548,	0x100),
		RSND_GEN_M_REG(CTU_SV15R,	0x54c,	0x100),
		RSND_GEN_M_REG(CTU_SV16R,	0x550,	0x100),
		RSND_GEN_M_REG(CTU_SV17R,	0x554,	0x100),
		RSND_GEN_M_REG(CTU_SV20R,	0x558,	0x100),
		RSND_GEN_M_REG(CTU_SV21R,	0x55c,	0x100),
		RSND_GEN_M_REG(CTU_SV22R,	0x560,	0x100),
		RSND_GEN_M_REG(CTU_SV23R,	0x564,	0x100),
		RSND_GEN_M_REG(CTU_SV24R,	0x568,	0x100),
		RSND_GEN_M_REG(CTU_SV25R,	0x56c,	0x100),
		RSND_GEN_M_REG(CTU_SV26R,	0x570,	0x100),
		RSND_GEN_M_REG(CTU_SV27R,	0x574,	0x100),
		RSND_GEN_M_REG(CTU_SV30R,	0x578,	0x100),
		RSND_GEN_M_REG(CTU_SV31R,	0x57c,	0x100),
		RSND_GEN_M_REG(CTU_SV32R,	0x580,	0x100),
		RSND_GEN_M_REG(CTU_SV33R,	0x584,	0x100),
		RSND_GEN_M_REG(CTU_SV34R,	0x588,	0x100),
		RSND_GEN_M_REG(CTU_SV35R,	0x58c,	0x100),
		RSND_GEN_M_REG(CTU_SV36R,	0x590,	0x100),
		RSND_GEN_M_REG(CTU_SV37R,	0x594,	0x100),
		RSND_GEN_M_REG(MIX_SWRSR,	0xd00,	0x40),
		RSND_GEN_M_REG(MIX_MIXIR,	0xd04,	0x40),
		RSND_GEN_M_REG(MIX_ADINR,	0xd08,	0x40),
		RSND_GEN_M_REG(MIX_MIXMR,	0xd10,	0x40),
		RSND_GEN_M_REG(MIX_MVPDR,	0xd14,	0x40),
		RSND_GEN_M_REG(MIX_MDBAR,	0xd18,	0x40),
		RSND_GEN_M_REG(MIX_MDBBR,	0xd1c,	0x40),
		RSND_GEN_M_REG(MIX_MDBCR,	0xd20,	0x40),
		RSND_GEN_M_REG(MIX_MDBDR,	0xd24,	0x40),
		RSND_GEN_M_REG(MIX_MDBER,	0xd28,	0x40),
		RSND_GEN_M_REG(DVC_SWRSR,	0xe00,	0x100),
		RSND_GEN_M_REG(DVC_DVUIR,	0xe04,	0x100),
		RSND_GEN_M_REG(DVC_ADINR,	0xe08,	0x100),
		RSND_GEN_M_REG(DVC_DVUCR,	0xe10,	0x100),
		RSND_GEN_M_REG(DVC_ZCMCR,	0xe14,	0x100),
		RSND_GEN_M_REG(DVC_VRCTR,	0xe18,	0x100),
		RSND_GEN_M_REG(DVC_VRPDR,	0xe1c,	0x100),
		RSND_GEN_M_REG(DVC_VRDBR,	0xe20,	0x100),
		RSND_GEN_M_REG(DVC_VOL0R,	0xe28,	0x100),
		RSND_GEN_M_REG(DVC_VOL1R,	0xe2c,	0x100),
		RSND_GEN_M_REG(DVC_VOL2R,	0xe30,	0x100),
		RSND_GEN_M_REG(DVC_VOL3R,	0xe34,	0x100),
		RSND_GEN_M_REG(DVC_VOL4R,	0xe38,	0x100),
		RSND_GEN_M_REG(DVC_VOL5R,	0xe3c,	0x100),
		RSND_GEN_M_REG(DVC_VOL6R,	0xe40,	0x100),
		RSND_GEN_M_REG(DVC_VOL7R,	0xe44,	0x100),
		RSND_GEN_M_REG(DVC_DVUER,	0xe48,	0x100),
	पूर्ण;
	अटल स्थिर काष्ठा rsnd_regmap_field_conf conf_adg[] = अणु
		RSND_GEN_S_REG(BRRA,		0x00),
		RSND_GEN_S_REG(BRRB,		0x04),
		RSND_GEN_S_REG(BRGCKR,		0x08),
		RSND_GEN_S_REG(AUDIO_CLK_SEL0,	0x0c),
		RSND_GEN_S_REG(AUDIO_CLK_SEL1,	0x10),
		RSND_GEN_S_REG(AUDIO_CLK_SEL2,	0x14),
		RSND_GEN_S_REG(DIV_EN,		0x30),
		RSND_GEN_S_REG(SRCIN_TIMSEL0,	0x34),
		RSND_GEN_S_REG(SRCIN_TIMSEL1,	0x38),
		RSND_GEN_S_REG(SRCIN_TIMSEL2,	0x3c),
		RSND_GEN_S_REG(SRCIN_TIMSEL3,	0x40),
		RSND_GEN_S_REG(SRCIN_TIMSEL4,	0x44),
		RSND_GEN_S_REG(SRCOUT_TIMSEL0,	0x48),
		RSND_GEN_S_REG(SRCOUT_TIMSEL1,	0x4c),
		RSND_GEN_S_REG(SRCOUT_TIMSEL2,	0x50),
		RSND_GEN_S_REG(SRCOUT_TIMSEL3,	0x54),
		RSND_GEN_S_REG(SRCOUT_TIMSEL4,	0x58),
		RSND_GEN_S_REG(CMDOUT_TIMSEL,	0x5c),
	पूर्ण;
	अटल स्थिर काष्ठा rsnd_regmap_field_conf conf_ssi[] = अणु
		RSND_GEN_M_REG(SSICR,		0x00,	0x40),
		RSND_GEN_M_REG(SSISR,		0x04,	0x40),
		RSND_GEN_M_REG(SSITDR,		0x08,	0x40),
		RSND_GEN_M_REG(SSIRDR,		0x0c,	0x40),
		RSND_GEN_M_REG(SSIWSR,		0x20,	0x40),
	पूर्ण;
	पूर्णांक ret_ssiu;
	पूर्णांक ret_scu;
	पूर्णांक ret_adg;
	पूर्णांक ret_ssi;

	ret_ssiu = rsnd_gen_regmap_init(priv, 10, RSND_GEN2_SSIU, "ssiu", conf_ssiu);
	ret_scu  = rsnd_gen_regmap_init(priv, 10, RSND_GEN2_SCU,  "scu",  conf_scu);
	ret_adg  = rsnd_gen_regmap_init(priv, 10, RSND_GEN2_ADG,  "adg",  conf_adg);
	ret_ssi  = rsnd_gen_regmap_init(priv, 10, RSND_GEN2_SSI,  "ssi",  conf_ssi);
	अगर (ret_ssiu < 0 ||
	    ret_scu  < 0 ||
	    ret_adg  < 0 ||
	    ret_ssi  < 0)
		वापस ret_ssiu | ret_scu | ret_adg | ret_ssi;

	वापस 0;
पूर्ण

/*
 *		Gen1
 */

अटल पूर्णांक rsnd_gen1_probe(काष्ठा rsnd_priv *priv)
अणु
	अटल स्थिर काष्ठा rsnd_regmap_field_conf conf_adg[] = अणु
		RSND_GEN_S_REG(BRRA,		0x00),
		RSND_GEN_S_REG(BRRB,		0x04),
		RSND_GEN_S_REG(BRGCKR,		0x08),
		RSND_GEN_S_REG(AUDIO_CLK_SEL0,	0x0c),
		RSND_GEN_S_REG(AUDIO_CLK_SEL1,	0x10),
	पूर्ण;
	अटल स्थिर काष्ठा rsnd_regmap_field_conf conf_ssi[] = अणु
		RSND_GEN_M_REG(SSICR,		0x00,	0x40),
		RSND_GEN_M_REG(SSISR,		0x04,	0x40),
		RSND_GEN_M_REG(SSITDR,		0x08,	0x40),
		RSND_GEN_M_REG(SSIRDR,		0x0c,	0x40),
		RSND_GEN_M_REG(SSIWSR,		0x20,	0x40),
	पूर्ण;
	पूर्णांक ret_adg;
	पूर्णांक ret_ssi;

	ret_adg  = rsnd_gen_regmap_init(priv, 9, RSND_GEN1_ADG, "adg", conf_adg);
	ret_ssi  = rsnd_gen_regmap_init(priv, 9, RSND_GEN1_SSI, "ssi", conf_ssi);
	अगर (ret_adg  < 0 ||
	    ret_ssi  < 0)
		वापस ret_adg | ret_ssi;

	वापस 0;
पूर्ण

/*
 *		Gen
 */
पूर्णांक rsnd_gen_probe(काष्ठा rsnd_priv *priv)
अणु
	काष्ठा device *dev = rsnd_priv_to_dev(priv);
	काष्ठा rsnd_gen *gen;
	पूर्णांक ret;

	gen = devm_kzalloc(dev, माप(*gen), GFP_KERNEL);
	अगर (!gen)
		वापस -ENOMEM;

	priv->gen = gen;

	ret = -ENODEV;
	अगर (rsnd_is_gen1(priv))
		ret = rsnd_gen1_probe(priv);
	अन्यथा अगर (rsnd_is_gen2(priv) ||
		 rsnd_is_gen3(priv))
		ret = rsnd_gen2_probe(priv);

	अगर (ret < 0)
		dev_err(dev, "unknown generation R-Car sound device\n");

	वापस ret;
पूर्ण
