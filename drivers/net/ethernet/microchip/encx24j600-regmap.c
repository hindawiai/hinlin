<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Register map access API - ENCX24J600 support
 *
 * Copyright 2015 Gridpoपूर्णांक
 *
 * Author: Jon Ringle <jringle@gridpoपूर्णांक.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/regmap.h>
#समावेश <linux/spi/spi.h>

#समावेश "encx24j600_hw.h"

अटल पूर्णांक encx24j600_चयन_bank(काष्ठा encx24j600_context *ctx,
				  पूर्णांक bank)
अणु
	पूर्णांक ret = 0;
	पूर्णांक bank_opcode = BANK_SELECT(bank);

	ret = spi_ग_लिखो(ctx->spi, &bank_opcode, 1);
	अगर (ret == 0)
		ctx->bank = bank;

	वापस ret;
पूर्ण

अटल पूर्णांक encx24j600_cmdn(काष्ठा encx24j600_context *ctx, u8 opcode,
			   स्थिर व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[2] = अणु अणु .tx_buf = &opcode, .len = 1, पूर्ण,
				     अणु .tx_buf = buf, .len = len पूर्ण, पूर्ण;
	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);
	spi_message_add_tail(&t[1], &m);

	वापस spi_sync(ctx->spi, &m);
पूर्ण

अटल व्योम regmap_lock_mutex(व्योम *context)
अणु
	काष्ठा encx24j600_context *ctx = context;

	mutex_lock(&ctx->mutex);
पूर्ण

अटल व्योम regmap_unlock_mutex(व्योम *context)
अणु
	काष्ठा encx24j600_context *ctx = context;

	mutex_unlock(&ctx->mutex);
पूर्ण

अटल पूर्णांक regmap_encx24j600_sfr_पढ़ो(व्योम *context, u8 reg, u8 *val,
				      माप_प्रकार len)
अणु
	काष्ठा encx24j600_context *ctx = context;
	u8 banked_reg = reg & ADDR_MASK;
	u8 bank = ((reg & BANK_MASK) >> BANK_SHIFT);
	u8 cmd = RCRU;
	पूर्णांक ret = 0;
	पूर्णांक i = 0;
	u8 tx_buf[2];

	अगर (reg < 0x80) अणु
		cmd = RCRCODE | banked_reg;
		अगर ((banked_reg < 0x16) && (ctx->bank != bank))
			ret = encx24j600_चयन_bank(ctx, bank);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Translate रेजिस्टरs that are more effecient using
		 * 3-byte SPI commands
		 */
		चयन (reg) अणु
		हाल EGPRDPT:
			cmd = RGPRDPT; अवरोध;
		हाल EGPWRPT:
			cmd = RGPWRPT; अवरोध;
		हाल ERXRDPT:
			cmd = RRXRDPT; अवरोध;
		हाल ERXWRPT:
			cmd = RRXWRPT; अवरोध;
		हाल EUDARDPT:
			cmd = RUDARDPT; अवरोध;
		हाल EUDAWRPT:
			cmd = RUDAWRPT; अवरोध;
		हाल EGPDATA:
		हाल ERXDATA:
		हाल EUDADATA:
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	tx_buf[i++] = cmd;
	अगर (cmd == RCRU)
		tx_buf[i++] = reg;

	ret = spi_ग_लिखो_then_पढ़ो(ctx->spi, tx_buf, i, val, len);

	वापस ret;
पूर्ण

अटल पूर्णांक regmap_encx24j600_sfr_update(काष्ठा encx24j600_context *ctx,
					u8 reg, u8 *val, माप_प्रकार len,
					u8 unbanked_cmd, u8 banked_code)
अणु
	u8 banked_reg = reg & ADDR_MASK;
	u8 bank = ((reg & BANK_MASK) >> BANK_SHIFT);
	u8 cmd = unbanked_cmd;
	काष्ठा spi_message m;
	काष्ठा spi_transfer t[3] = अणु अणु .tx_buf = &cmd, .len = माप(cmd), पूर्ण,
				     अणु .tx_buf = &reg, .len = माप(reg), पूर्ण,
				     अणु .tx_buf = val, .len = len पूर्ण, पूर्ण;

	अगर (reg < 0x80) अणु
		पूर्णांक ret = 0;

		cmd = banked_code | banked_reg;
		अगर ((banked_reg < 0x16) && (ctx->bank != bank))
			ret = encx24j600_चयन_bank(ctx, bank);
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Translate रेजिस्टरs that are more effecient using
		 * 3-byte SPI commands
		 */
		चयन (reg) अणु
		हाल EGPRDPT:
			cmd = WGPRDPT; अवरोध;
		हाल EGPWRPT:
			cmd = WGPWRPT; अवरोध;
		हाल ERXRDPT:
			cmd = WRXRDPT; अवरोध;
		हाल ERXWRPT:
			cmd = WRXWRPT; अवरोध;
		हाल EUDARDPT:
			cmd = WUDARDPT; अवरोध;
		हाल EUDAWRPT:
			cmd = WUDAWRPT; अवरोध;
		हाल EGPDATA:
		हाल ERXDATA:
		हाल EUDADATA:
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	spi_message_init(&m);
	spi_message_add_tail(&t[0], &m);

	अगर (cmd == unbanked_cmd) अणु
		t[1].tx_buf = &reg;
		spi_message_add_tail(&t[1], &m);
	पूर्ण

	spi_message_add_tail(&t[2], &m);
	वापस spi_sync(ctx->spi, &m);
पूर्ण

अटल पूर्णांक regmap_encx24j600_sfr_ग_लिखो(व्योम *context, u8 reg, u8 *val,
				       माप_प्रकार len)
अणु
	काष्ठा encx24j600_context *ctx = context;

	वापस regmap_encx24j600_sfr_update(ctx, reg, val, len, WCRU, WCRCODE);
पूर्ण

अटल पूर्णांक regmap_encx24j600_sfr_set_bits(काष्ठा encx24j600_context *ctx,
					  u8 reg, u8 val)
अणु
	वापस regmap_encx24j600_sfr_update(ctx, reg, &val, 1, BFSU, BFSCODE);
पूर्ण

अटल पूर्णांक regmap_encx24j600_sfr_clr_bits(काष्ठा encx24j600_context *ctx,
					  u8 reg, u8 val)
अणु
	वापस regmap_encx24j600_sfr_update(ctx, reg, &val, 1, BFCU, BFCCODE);
पूर्ण

अटल पूर्णांक regmap_encx24j600_reg_update_bits(व्योम *context, अचिन्हित पूर्णांक reg,
					     अचिन्हित पूर्णांक mask,
					     अचिन्हित पूर्णांक val)
अणु
	काष्ठा encx24j600_context *ctx = context;

	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक set_mask = mask & val;
	अचिन्हित पूर्णांक clr_mask = mask & ~val;

	अगर ((reg >= 0x40 && reg < 0x6c) || reg >= 0x80)
		वापस -EINVAL;

	अगर (set_mask & 0xff)
		ret = regmap_encx24j600_sfr_set_bits(ctx, reg, set_mask);

	set_mask = (set_mask & 0xff00) >> 8;

	अगर ((set_mask & 0xff) && (ret == 0))
		ret = regmap_encx24j600_sfr_set_bits(ctx, reg + 1, set_mask);

	अगर ((clr_mask & 0xff) && (ret == 0))
		ret = regmap_encx24j600_sfr_clr_bits(ctx, reg, clr_mask);

	clr_mask = (clr_mask & 0xff00) >> 8;

	अगर ((clr_mask & 0xff) && (ret == 0))
		ret = regmap_encx24j600_sfr_clr_bits(ctx, reg + 1, clr_mask);

	वापस ret;
पूर्ण

पूर्णांक regmap_encx24j600_spi_ग_लिखो(व्योम *context, u8 reg, स्थिर u8 *data,
				माप_प्रकार count)
अणु
	काष्ठा encx24j600_context *ctx = context;

	अगर (reg < 0xc0)
		वापस encx24j600_cmdn(ctx, reg, data, count);

	/* SPI 1-byte command. Ignore data */
	वापस spi_ग_लिखो(ctx->spi, &reg, 1);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_encx24j600_spi_ग_लिखो);

पूर्णांक regmap_encx24j600_spi_पढ़ो(व्योम *context, u8 reg, u8 *data, माप_प्रकार count)
अणु
	काष्ठा encx24j600_context *ctx = context;

	अगर (reg == RBSEL && count > 1)
		count = 1;

	वापस spi_ग_लिखो_then_पढ़ो(ctx->spi, &reg, माप(reg), data, count);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_encx24j600_spi_पढ़ो);

अटल पूर्णांक regmap_encx24j600_ग_लिखो(व्योम *context, स्थिर व्योम *data,
				   माप_प्रकार len)
अणु
	u8 *करोut = (u8 *)data;
	u8 reg = करोut[0];
	++करोut;
	--len;

	अगर (reg > 0xa0)
		वापस regmap_encx24j600_spi_ग_लिखो(context, reg, करोut, len);

	अगर (len > 2)
		वापस -EINVAL;

	वापस regmap_encx24j600_sfr_ग_लिखो(context, reg, करोut, len);
पूर्ण

अटल पूर्णांक regmap_encx24j600_पढ़ो(व्योम *context,
				  स्थिर व्योम *reg_buf, माप_प्रकार reg_size,
				  व्योम *val, माप_प्रकार val_size)
अणु
	u8 reg = *(स्थिर u8 *)reg_buf;

	अगर (reg_size != 1) अणु
		pr_err("%s: reg=%02x reg_size=%zu\n", __func__, reg, reg_size);
		वापस -EINVAL;
	पूर्ण

	अगर (reg > 0xa0)
		वापस regmap_encx24j600_spi_पढ़ो(context, reg, val, val_size);

	अगर (val_size > 2) अणु
		pr_err("%s: reg=%02x val_size=%zu\n", __func__, reg, val_size);
		वापस -EINVAL;
	पूर्ण

	वापस regmap_encx24j600_sfr_पढ़ो(context, reg, val, val_size);
पूर्ण

अटल bool encx24j600_regmap_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर ((reg < 0x36) ||
	    ((reg >= 0x40) && (reg < 0x4c)) ||
	    ((reg >= 0x52) && (reg < 0x56)) ||
	    ((reg >= 0x60) && (reg < 0x66)) ||
	    ((reg >= 0x68) && (reg < 0x80)) ||
	    ((reg >= 0x86) && (reg < 0x92)) ||
	    (reg == 0xc8))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool encx24j600_regmap_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	अगर ((reg < 0x12) ||
	    ((reg >= 0x14) && (reg < 0x1a)) ||
	    ((reg >= 0x1c) && (reg < 0x36)) ||
	    ((reg >= 0x40) && (reg < 0x4c)) ||
	    ((reg >= 0x52) && (reg < 0x56)) ||
	    ((reg >= 0x60) && (reg < 0x68)) ||
	    ((reg >= 0x6c) && (reg < 0x80)) ||
	    ((reg >= 0x86) && (reg < 0x92)) ||
	    ((reg >= 0xc0) && (reg < 0xc8)) ||
	    ((reg >= 0xca) && (reg < 0xf0)))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool encx24j600_regmap_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल ERXHEAD:
	हाल EDMACS:
	हाल ETXSTAT:
	हाल ETXWIRE:
	हाल ECON1:	/* Can be modअगरied via single byte cmds */
	हाल ECON2:	/* Can be modअगरied via single byte cmds */
	हाल ESTAT:
	हाल EIR:	/* Can be modअगरied via single byte cmds */
	हाल MIRD:
	हाल MISTAT:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

अटल bool encx24j600_regmap_precious(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	/* single byte cmds are precious */
	अगर (((reg >= 0xc0) && (reg < 0xc8)) ||
	    ((reg >= 0xca) && (reg < 0xf0)))
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल पूर्णांक regmap_encx24j600_phy_reg_पढ़ो(व्योम *context, अचिन्हित पूर्णांक reg,
					  अचिन्हित पूर्णांक *val)
अणु
	काष्ठा encx24j600_context *ctx = context;
	पूर्णांक ret;
	अचिन्हित पूर्णांक mistat;

	reg = MIREGADR_VAL | (reg & PHREG_MASK);
	ret = regmap_ग_लिखो(ctx->regmap, MIREGADR, reg);
	अगर (unlikely(ret))
		जाओ err_out;

	ret = regmap_ग_लिखो(ctx->regmap, MICMD, MIIRD);
	अगर (unlikely(ret))
		जाओ err_out;

	usleep_range(26, 100);
	जबतक ((ret = regmap_पढ़ो(ctx->regmap, MISTAT, &mistat) != 0) &&
	       (mistat & BUSY))
		cpu_relax();

	अगर (unlikely(ret))
		जाओ err_out;

	ret = regmap_ग_लिखो(ctx->regmap, MICMD, 0);
	अगर (unlikely(ret))
		जाओ err_out;

	ret = regmap_पढ़ो(ctx->regmap, MIRD, val);

err_out:
	अगर (ret)
		pr_err("%s: error %d reading reg %02x\n", __func__, ret,
		       reg & PHREG_MASK);

	वापस ret;
पूर्ण

अटल पूर्णांक regmap_encx24j600_phy_reg_ग_लिखो(व्योम *context, अचिन्हित पूर्णांक reg,
					   अचिन्हित पूर्णांक val)
अणु
	काष्ठा encx24j600_context *ctx = context;
	पूर्णांक ret;
	अचिन्हित पूर्णांक mistat;

	reg = MIREGADR_VAL | (reg & PHREG_MASK);
	ret = regmap_ग_लिखो(ctx->regmap, MIREGADR, reg);
	अगर (unlikely(ret))
		जाओ err_out;

	ret = regmap_ग_लिखो(ctx->regmap, MIWR, val);
	अगर (unlikely(ret))
		जाओ err_out;

	usleep_range(26, 100);
	जबतक ((ret = regmap_पढ़ो(ctx->regmap, MISTAT, &mistat) != 0) &&
	       (mistat & BUSY))
		cpu_relax();

err_out:
	अगर (ret)
		pr_err("%s: error %d writing reg %02x=%04x\n", __func__, ret,
		       reg & PHREG_MASK, val);

	वापस ret;
पूर्ण

अटल bool encx24j600_phymap_पढ़ोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PHCON1:
	हाल PHSTAT1:
	हाल PHANA:
	हाल PHANLPA:
	हाल PHANE:
	हाल PHCON2:
	हाल PHSTAT2:
	हाल PHSTAT3:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool encx24j600_phymap_ग_लिखोable(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PHCON1:
	हाल PHCON2:
	हाल PHANA:
		वापस true;
	हाल PHSTAT1:
	हाल PHSTAT2:
	हाल PHSTAT3:
	हाल PHANLPA:
	हाल PHANE:
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool encx24j600_phymap_अस्थिर(काष्ठा device *dev, अचिन्हित पूर्णांक reg)
अणु
	चयन (reg) अणु
	हाल PHSTAT1:
	हाल PHSTAT2:
	हाल PHSTAT3:
	हाल PHANLPA:
	हाल PHANE:
	हाल PHCON2:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल काष्ठा regmap_config regcfg = अणु
	.name = "reg",
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = 0xee,
	.reg_stride = 2,
	.cache_type = REGCACHE_RBTREE,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.पढ़ोable_reg = encx24j600_regmap_पढ़ोable,
	.ग_लिखोable_reg = encx24j600_regmap_ग_लिखोable,
	.अस्थिर_reg = encx24j600_regmap_अस्थिर,
	.precious_reg = encx24j600_regmap_precious,
	.lock = regmap_lock_mutex,
	.unlock = regmap_unlock_mutex,
पूर्ण;

अटल काष्ठा regmap_bus regmap_encx24j600 = अणु
	.ग_लिखो = regmap_encx24j600_ग_लिखो,
	.पढ़ो = regmap_encx24j600_पढ़ो,
	.reg_update_bits = regmap_encx24j600_reg_update_bits,
पूर्ण;

अटल काष्ठा regmap_config phycfg = अणु
	.name = "phy",
	.reg_bits = 8,
	.val_bits = 16,
	.max_रेजिस्टर = 0x1f,
	.cache_type = REGCACHE_RBTREE,
	.val_क्रमmat_endian = REGMAP_ENDIAN_LITTLE,
	.पढ़ोable_reg = encx24j600_phymap_पढ़ोable,
	.ग_लिखोable_reg = encx24j600_phymap_ग_लिखोable,
	.अस्थिर_reg = encx24j600_phymap_अस्थिर,
पूर्ण;

अटल काष्ठा regmap_bus phymap_encx24j600 = अणु
	.reg_ग_लिखो = regmap_encx24j600_phy_reg_ग_लिखो,
	.reg_पढ़ो = regmap_encx24j600_phy_reg_पढ़ो,
पूर्ण;

व्योम devm_regmap_init_encx24j600(काष्ठा device *dev,
				 काष्ठा encx24j600_context *ctx)
अणु
	mutex_init(&ctx->mutex);
	regcfg.lock_arg = ctx;
	ctx->regmap = devm_regmap_init(dev, &regmap_encx24j600, ctx, &regcfg);
	ctx->phymap = devm_regmap_init(dev, &phymap_encx24j600, ctx, &phycfg);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_init_encx24j600);

MODULE_LICENSE("GPL");
