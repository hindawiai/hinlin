<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/*
 * Microsemi Ocelot Switch driver
 *
 * Copyright (c) 2017 Microsemi Corporation
 */
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश "ocelot.h"

u32 __ocelot_पढ़ो_ix(काष्ठा ocelot *ocelot, u32 reg, u32 offset)
अणु
	u16 target = reg >> TARGET_OFFSET;
	u32 val;

	WARN_ON(!target);

	regmap_पढ़ो(ocelot->tarमाला_लो[target],
		    ocelot->map[target][reg & REG_MASK] + offset, &val);
	वापस val;
पूर्ण
EXPORT_SYMBOL(__ocelot_पढ़ो_ix);

व्योम __ocelot_ग_लिखो_ix(काष्ठा ocelot *ocelot, u32 val, u32 reg, u32 offset)
अणु
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_ग_लिखो(ocelot->tarमाला_लो[target],
		     ocelot->map[target][reg & REG_MASK] + offset, val);
पूर्ण
EXPORT_SYMBOL(__ocelot_ग_लिखो_ix);

व्योम __ocelot_rmw_ix(काष्ठा ocelot *ocelot, u32 val, u32 mask, u32 reg,
		     u32 offset)
अणु
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_update_bits(ocelot->tarमाला_लो[target],
			   ocelot->map[target][reg & REG_MASK] + offset,
			   mask, val);
पूर्ण
EXPORT_SYMBOL(__ocelot_rmw_ix);

u32 ocelot_port_पढ़ोl(काष्ठा ocelot_port *port, u32 reg)
अणु
	काष्ठा ocelot *ocelot = port->ocelot;
	u16 target = reg >> TARGET_OFFSET;
	u32 val;

	WARN_ON(!target);

	regmap_पढ़ो(port->target, ocelot->map[target][reg & REG_MASK], &val);
	वापस val;
पूर्ण
EXPORT_SYMBOL(ocelot_port_पढ़ोl);

व्योम ocelot_port_ग_लिखोl(काष्ठा ocelot_port *port, u32 val, u32 reg)
अणु
	काष्ठा ocelot *ocelot = port->ocelot;
	u16 target = reg >> TARGET_OFFSET;

	WARN_ON(!target);

	regmap_ग_लिखो(port->target, ocelot->map[target][reg & REG_MASK], val);
पूर्ण
EXPORT_SYMBOL(ocelot_port_ग_लिखोl);

व्योम ocelot_port_rmwl(काष्ठा ocelot_port *port, u32 val, u32 mask, u32 reg)
अणु
	u32 cur = ocelot_port_पढ़ोl(port, reg);

	ocelot_port_ग_लिखोl(port, (cur & (~mask)) | val, reg);
पूर्ण
EXPORT_SYMBOL(ocelot_port_rmwl);

u32 __ocelot_target_पढ़ो_ix(काष्ठा ocelot *ocelot, क्रमागत ocelot_target target,
			    u32 reg, u32 offset)
अणु
	u32 val;

	regmap_पढ़ो(ocelot->tarमाला_लो[target],
		    ocelot->map[target][reg] + offset, &val);
	वापस val;
पूर्ण

व्योम __ocelot_target_ग_लिखो_ix(काष्ठा ocelot *ocelot, क्रमागत ocelot_target target,
			      u32 val, u32 reg, u32 offset)
अणु
	regmap_ग_लिखो(ocelot->tarमाला_लो[target],
		     ocelot->map[target][reg] + offset, val);
पूर्ण

पूर्णांक ocelot_regfields_init(काष्ठा ocelot *ocelot,
			  स्थिर काष्ठा reg_field *स्थिर regfields)
अणु
	अचिन्हित पूर्णांक i;
	u16 target;

	क्रम (i = 0; i < REGFIELD_MAX; i++) अणु
		काष्ठा reg_field regfield = अणुपूर्ण;
		u32 reg = regfields[i].reg;

		अगर (!reg)
			जारी;

		target = regfields[i].reg >> TARGET_OFFSET;

		regfield.reg = ocelot->map[target][reg & REG_MASK];
		regfield.lsb = regfields[i].lsb;
		regfield.msb = regfields[i].msb;
		regfield.id_size = regfields[i].id_size;
		regfield.id_offset = regfields[i].id_offset;

		ocelot->regfields[i] =
		devm_regmap_field_alloc(ocelot->dev,
					ocelot->tarमाला_लो[target],
					regfield);

		अगर (IS_ERR(ocelot->regfields[i]))
			वापस PTR_ERR(ocelot->regfields[i]);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ocelot_regfields_init);

अटल काष्ठा regmap_config ocelot_regmap_config = अणु
	.reg_bits	= 32,
	.val_bits	= 32,
	.reg_stride	= 4,
पूर्ण;

काष्ठा regmap *ocelot_regmap_init(काष्ठा ocelot *ocelot, काष्ठा resource *res)
अणु
	व्योम __iomem *regs;

	regs = devm_ioremap_resource(ocelot->dev, res);
	अगर (IS_ERR(regs))
		वापस ERR_CAST(regs);

	ocelot_regmap_config.name = res->name;

	वापस devm_regmap_init_mmio(ocelot->dev, regs, &ocelot_regmap_config);
पूर्ण
EXPORT_SYMBOL(ocelot_regmap_init);
