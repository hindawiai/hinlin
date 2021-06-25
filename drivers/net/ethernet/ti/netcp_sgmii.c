<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SGMI module initialisation
 *
 * Copyright (C) 2014 Texas Instruments Incorporated
 * Authors:	Sandeep Nair <sandeep_n@ti.com>
 *		Sandeep Paulraj <s-paulraj@ti.com>
 *		Wingman Kwok <w-kwok2@ti.com>
 *
 */

#समावेश "netcp.h"

#घोषणा SGMII_SRESET_RESET		BIT(0)
#घोषणा SGMII_SRESET_RTRESET		BIT(1)

#घोषणा SGMII_REG_STATUS_LOCK		BIT(4)
#घोषणा	SGMII_REG_STATUS_LINK		BIT(0)
#घोषणा SGMII_REG_STATUS_AUTONEG	BIT(2)
#घोषणा SGMII_REG_CONTROL_AUTONEG	BIT(0)

#घोषणा SGMII23_OFFSET(x)	((x - 2) * 0x100)
#घोषणा SGMII_OFFSET(x)		((x <= 1) ? (x * 0x100) : (SGMII23_OFFSET(x)))

/* SGMII रेजिस्टरs */
#घोषणा SGMII_SRESET_REG(x)   (SGMII_OFFSET(x) + 0x004)
#घोषणा SGMII_CTL_REG(x)      (SGMII_OFFSET(x) + 0x010)
#घोषणा SGMII_STATUS_REG(x)   (SGMII_OFFSET(x) + 0x014)
#घोषणा SGMII_MRADV_REG(x)    (SGMII_OFFSET(x) + 0x018)

अटल व्योम sgmii_ग_लिखो_reg(व्योम __iomem *base, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl(val, base + reg);
पूर्ण

अटल u32 sgmii_पढ़ो_reg(व्योम __iomem *base, पूर्णांक reg)
अणु
	वापस पढ़ोl(base + reg);
पूर्ण

अटल व्योम sgmii_ग_लिखो_reg_bit(व्योम __iomem *base, पूर्णांक reg, u32 val)
अणु
	ग_लिखोl((पढ़ोl(base + reg) | val), base + reg);
पूर्ण

/* port is 0 based */
पूर्णांक netcp_sgmii_reset(व्योम __iomem *sgmii_ofs, पूर्णांक port)
अणु
	/* Soft reset */
	sgmii_ग_लिखो_reg_bit(sgmii_ofs, SGMII_SRESET_REG(port),
			    SGMII_SRESET_RESET);

	जबतक ((sgmii_पढ़ो_reg(sgmii_ofs, SGMII_SRESET_REG(port)) &
		SGMII_SRESET_RESET) != 0x0)
		;

	वापस 0;
पूर्ण

/* port is 0 based */
bool netcp_sgmii_rtreset(व्योम __iomem *sgmii_ofs, पूर्णांक port, bool set)
अणु
	u32 reg;
	bool oldval;

	/* Initiate a soft reset */
	reg = sgmii_पढ़ो_reg(sgmii_ofs, SGMII_SRESET_REG(port));
	oldval = (reg & SGMII_SRESET_RTRESET) != 0x0;
	अगर (set)
		reg |= SGMII_SRESET_RTRESET;
	अन्यथा
		reg &= ~SGMII_SRESET_RTRESET;
	sgmii_ग_लिखो_reg(sgmii_ofs, SGMII_SRESET_REG(port), reg);
	wmb();

	वापस oldval;
पूर्ण

पूर्णांक netcp_sgmii_get_port_link(व्योम __iomem *sgmii_ofs, पूर्णांक port)
अणु
	u32 status = 0, link = 0;

	status = sgmii_पढ़ो_reg(sgmii_ofs, SGMII_STATUS_REG(port));
	अगर ((status & SGMII_REG_STATUS_LINK) != 0)
		link = 1;
	वापस link;
पूर्ण

पूर्णांक netcp_sgmii_config(व्योम __iomem *sgmii_ofs, पूर्णांक port, u32 पूर्णांकerface)
अणु
	अचिन्हित पूर्णांक i, status, mask;
	u32 mr_adv_ability;
	u32 control;

	चयन (पूर्णांकerface) अणु
	हाल SGMII_LINK_MAC_MAC_AUTONEG:
		mr_adv_ability	= 0x9801;
		control		= 0x21;
		अवरोध;

	हाल SGMII_LINK_MAC_PHY:
	हाल SGMII_LINK_MAC_PHY_NO_MDIO:
		mr_adv_ability	= 1;
		control		= 1;
		अवरोध;

	हाल SGMII_LINK_MAC_MAC_FORCED:
		mr_adv_ability	= 0x9801;
		control		= 0x20;
		अवरोध;

	हाल SGMII_LINK_MAC_FIBER:
		mr_adv_ability	= 0x20;
		control		= 0x1;
		अवरोध;

	शेष:
		WARN_ONCE(1, "Invalid sgmii interface: %d\n", पूर्णांकerface);
		वापस -EINVAL;
	पूर्ण

	sgmii_ग_लिखो_reg(sgmii_ofs, SGMII_CTL_REG(port), 0);

	/* Wait क्रम the SerDes pll to lock */
	क्रम (i = 0; i < 1000; i++)  अणु
		usleep_range(1000, 2000);
		status = sgmii_पढ़ो_reg(sgmii_ofs, SGMII_STATUS_REG(port));
		अगर ((status & SGMII_REG_STATUS_LOCK) != 0)
			अवरोध;
	पूर्ण

	अगर ((status & SGMII_REG_STATUS_LOCK) == 0)
		pr_err("serdes PLL not locked\n");

	sgmii_ग_लिखो_reg(sgmii_ofs, SGMII_MRADV_REG(port), mr_adv_ability);
	sgmii_ग_लिखो_reg(sgmii_ofs, SGMII_CTL_REG(port), control);

	mask = SGMII_REG_STATUS_LINK;
	अगर (control & SGMII_REG_CONTROL_AUTONEG)
		mask |= SGMII_REG_STATUS_AUTONEG;

	क्रम (i = 0; i < 1000; i++)  अणु
		usleep_range(200, 500);
		status = sgmii_पढ़ो_reg(sgmii_ofs, SGMII_STATUS_REG(port));
		अगर ((status & mask) == mask)
			अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
