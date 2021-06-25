<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009-2016 Cavium, Inc.
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/phy.h>

#समावेश "mdio-cavium.h"

अटल व्योम cavium_mdiobus_set_mode(काष्ठा cavium_mdiobus *p,
				    क्रमागत cavium_mdiobus_mode m)
अणु
	जोड़ cvmx_smix_clk smi_clk;

	अगर (m == p->mode)
		वापस;

	smi_clk.u64 = oct_mdio_पढ़ोq(p->रेजिस्टर_base + SMI_CLK);
	smi_clk.s.mode = (m == C45) ? 1 : 0;
	smi_clk.s.preamble = 1;
	oct_mdio_ग_लिखोq(smi_clk.u64, p->रेजिस्टर_base + SMI_CLK);
	p->mode = m;
पूर्ण

अटल पूर्णांक cavium_mdiobus_c45_addr(काष्ठा cavium_mdiobus *p,
				   पूर्णांक phy_id, पूर्णांक regnum)
अणु
	जोड़ cvmx_smix_cmd smi_cmd;
	जोड़ cvmx_smix_wr_dat smi_wr;
	पूर्णांक समयout = 1000;

	cavium_mdiobus_set_mode(p, C45);

	smi_wr.u64 = 0;
	smi_wr.s.dat = regnum & 0xffff;
	oct_mdio_ग_लिखोq(smi_wr.u64, p->रेजिस्टर_base + SMI_WR_DAT);

	regnum = (regnum >> 16) & 0x1f;

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = 0; /* MDIO_CLAUSE_45_ADDRESS */
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = regnum;
	oct_mdio_ग_लिखोq(smi_cmd.u64, p->रेजिस्टर_base + SMI_CMD);

	करो अणु
		/* Wait 1000 घड़ीs so we करोn't saturate the RSL bus
		 * करोing पढ़ोs.
		 */
		__delay(1000);
		smi_wr.u64 = oct_mdio_पढ़ोq(p->रेजिस्टर_base + SMI_WR_DAT);
	पूर्ण जबतक (smi_wr.s.pending && --समयout);

	अगर (समयout <= 0)
		वापस -EIO;
	वापस 0;
पूर्ण

पूर्णांक cavium_mdiobus_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum)
अणु
	काष्ठा cavium_mdiobus *p = bus->priv;
	जोड़ cvmx_smix_cmd smi_cmd;
	जोड़ cvmx_smix_rd_dat smi_rd;
	अचिन्हित पूर्णांक op = 1; /* MDIO_CLAUSE_22_READ */
	पूर्णांक समयout = 1000;

	अगर (regnum & MII_ADDR_C45) अणु
		पूर्णांक r = cavium_mdiobus_c45_addr(p, phy_id, regnum);

		अगर (r < 0)
			वापस r;

		regnum = (regnum >> 16) & 0x1f;
		op = 3; /* MDIO_CLAUSE_45_READ */
	पूर्ण अन्यथा अणु
		cavium_mdiobus_set_mode(p, C22);
	पूर्ण

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = op;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = regnum;
	oct_mdio_ग_लिखोq(smi_cmd.u64, p->रेजिस्टर_base + SMI_CMD);

	करो अणु
		/* Wait 1000 घड़ीs so we करोn't saturate the RSL bus
		 * करोing पढ़ोs.
		 */
		__delay(1000);
		smi_rd.u64 = oct_mdio_पढ़ोq(p->रेजिस्टर_base + SMI_RD_DAT);
	पूर्ण जबतक (smi_rd.s.pending && --समयout);

	अगर (smi_rd.s.val)
		वापस smi_rd.s.dat;
	अन्यथा
		वापस -EIO;
पूर्ण
EXPORT_SYMBOL(cavium_mdiobus_पढ़ो);

पूर्णांक cavium_mdiobus_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_id, पूर्णांक regnum, u16 val)
अणु
	काष्ठा cavium_mdiobus *p = bus->priv;
	जोड़ cvmx_smix_cmd smi_cmd;
	जोड़ cvmx_smix_wr_dat smi_wr;
	अचिन्हित पूर्णांक op = 0; /* MDIO_CLAUSE_22_WRITE */
	पूर्णांक समयout = 1000;

	अगर (regnum & MII_ADDR_C45) अणु
		पूर्णांक r = cavium_mdiobus_c45_addr(p, phy_id, regnum);

		अगर (r < 0)
			वापस r;

		regnum = (regnum >> 16) & 0x1f;
		op = 1; /* MDIO_CLAUSE_45_WRITE */
	पूर्ण अन्यथा अणु
		cavium_mdiobus_set_mode(p, C22);
	पूर्ण

	smi_wr.u64 = 0;
	smi_wr.s.dat = val;
	oct_mdio_ग_लिखोq(smi_wr.u64, p->रेजिस्टर_base + SMI_WR_DAT);

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = op;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = regnum;
	oct_mdio_ग_लिखोq(smi_cmd.u64, p->रेजिस्टर_base + SMI_CMD);

	करो अणु
		/* Wait 1000 घड़ीs so we करोn't saturate the RSL bus
		 * करोing पढ़ोs.
		 */
		__delay(1000);
		smi_wr.u64 = oct_mdio_पढ़ोq(p->रेजिस्टर_base + SMI_WR_DAT);
	पूर्ण जबतक (smi_wr.s.pending && --समयout);

	अगर (समयout <= 0)
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cavium_mdiobus_ग_लिखो);

MODULE_DESCRIPTION("Common code for OCTEON and Thunder MDIO bus drivers");
MODULE_AUTHOR("David Daney");
MODULE_LICENSE("GPL v2");
