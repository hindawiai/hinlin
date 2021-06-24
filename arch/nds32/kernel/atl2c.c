<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/compiler.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/l2_cache.h>

व्योम __iomem *atl2c_base;
अटल स्थिर काष्ठा of_device_id atl2c_ids[] __initस्थिर = अणु
	अणु.compatible = "andestech,atl2c",पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक __init atl2c_of_init(व्योम)
अणु
	काष्ठा device_node *np;
	काष्ठा resource res;
	अचिन्हित दीर्घ पंचांगp = 0;
	अचिन्हित दीर्घ l2set, l2way, l2clsz;

	अगर (!(__nds32__mfsr(NDS32_SR_MSC_CFG) & MSC_CFG_mskL2C))
		वापस -ENODEV;

	np = of_find_matching_node(शून्य, atl2c_ids);
	अगर (!np)
		वापस -ENODEV;

	अगर (of_address_to_resource(np, 0, &res))
		वापस -ENODEV;

	atl2c_base = ioremap(res.start, resource_size(&res));
	अगर (!atl2c_base)
		वापस -ENOMEM;

	l2set =
	    64 << ((L2C_R_REG(L2_CA_CONF_OFF) & L2_CA_CONF_mskL2SET) >>
		   L2_CA_CONF_offL2SET);
	l2way =
	    1 +
	    ((L2C_R_REG(L2_CA_CONF_OFF) & L2_CA_CONF_mskL2WAY) >>
	     L2_CA_CONF_offL2WAY);
	l2clsz =
	    4 << ((L2C_R_REG(L2_CA_CONF_OFF) & L2_CA_CONF_mskL2CLSZ) >>
		  L2_CA_CONF_offL2CLSZ);
	pr_info("L2:%luKB/%luS/%luW/%luB\n",
		l2set * l2way * l2clsz / 1024, l2set, l2way, l2clsz);

	पंचांगp = L2C_R_REG(L2CC_PROT_OFF);
	पंचांगp &= ~L2CC_PROT_mskMRWEN;
	L2C_W_REG(L2CC_PROT_OFF, पंचांगp);

	पंचांगp = L2C_R_REG(L2CC_SETUP_OFF);
	पंचांगp &= ~L2CC_SETUP_mskPART;
	L2C_W_REG(L2CC_SETUP_OFF, पंचांगp);

	पंचांगp = L2C_R_REG(L2CC_CTRL_OFF);
	पंचांगp |= L2CC_CTRL_mskEN;
	L2C_W_REG(L2CC_CTRL_OFF, पंचांगp);

	वापस 0;
पूर्ण

subsys_initcall(atl2c_of_init);
