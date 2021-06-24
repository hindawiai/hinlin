<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Bitbanged MDIO support.
 *
 * Author: Scott Wood <scottwood@मुक्तscale.com>
 * Copyright (c) 2007 Freescale Semiconductor
 *
 * Based on CPM2 MDIO code which is:
 *
 * Copyright (c) 2003 Intracom S.A.
 *  by Pantelis Antoniou <panto@पूर्णांकracom.gr>
 *
 * 2005 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/mdio-bitbang.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>

#घोषणा MDIO_READ 2
#घोषणा MDIO_WRITE 1

#घोषणा MDIO_C45 (1<<15)
#घोषणा MDIO_C45_ADDR (MDIO_C45 | 0)
#घोषणा MDIO_C45_READ (MDIO_C45 | 3)
#घोषणा MDIO_C45_WRITE (MDIO_C45 | 1)

#घोषणा MDIO_SETUP_TIME 10
#घोषणा MDIO_HOLD_TIME 10

/* Minimum MDC period is 400 ns, plus some margin क्रम error.  MDIO_DELAY
 * is करोne twice per period.
 */
#घोषणा MDIO_DELAY 250

/* The PHY may take up to 300 ns to produce data, plus some margin
 * क्रम error.
 */
#घोषणा MDIO_READ_DELAY 350

/* MDIO must alपढ़ोy be configured as output. */
अटल व्योम mdiobb_send_bit(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक val)
अणु
	स्थिर काष्ठा mdiobb_ops *ops = ctrl->ops;

	ops->set_mdio_data(ctrl, val);
	ndelay(MDIO_DELAY);
	ops->set_mdc(ctrl, 1);
	ndelay(MDIO_DELAY);
	ops->set_mdc(ctrl, 0);
पूर्ण

/* MDIO must alपढ़ोy be configured as input. */
अटल पूर्णांक mdiobb_get_bit(काष्ठा mdiobb_ctrl *ctrl)
अणु
	स्थिर काष्ठा mdiobb_ops *ops = ctrl->ops;

	ndelay(MDIO_DELAY);
	ops->set_mdc(ctrl, 1);
	ndelay(MDIO_READ_DELAY);
	ops->set_mdc(ctrl, 0);

	वापस ops->get_mdio_data(ctrl);
पूर्ण

/* MDIO must alपढ़ोy be configured as output. */
अटल व्योम mdiobb_send_num(काष्ठा mdiobb_ctrl *ctrl, u16 val, पूर्णांक bits)
अणु
	पूर्णांक i;

	क्रम (i = bits - 1; i >= 0; i--)
		mdiobb_send_bit(ctrl, (val >> i) & 1);
पूर्ण

/* MDIO must alपढ़ोy be configured as input. */
अटल u16 mdiobb_get_num(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक bits)
अणु
	पूर्णांक i;
	u16 ret = 0;

	क्रम (i = bits - 1; i >= 0; i--) अणु
		ret <<= 1;
		ret |= mdiobb_get_bit(ctrl);
	पूर्ण

	वापस ret;
पूर्ण

/* Utility to send the preamble, address, and
 * रेजिस्टर (common to पढ़ो and ग_लिखो).
 */
अटल व्योम mdiobb_cmd(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक op, u8 phy, u8 reg)
अणु
	स्थिर काष्ठा mdiobb_ops *ops = ctrl->ops;
	पूर्णांक i;

	ops->set_mdio_dir(ctrl, 1);

	/*
	 * Send a 32 bit preamble ('1's) with an extra '1' bit क्रम good
	 * measure.  The IEEE spec says this is a PHY optional
	 * requirement.  The AMD 79C874 requires one after घातer up and
	 * one after a MII communications error.  This means that we are
	 * करोing more preambles than we need, but it is safer and will be
	 * much more robust.
	 */

	क्रम (i = 0; i < 32; i++)
		mdiobb_send_bit(ctrl, 1);

	/* send the start bit (01) and the पढ़ो opcode (10) or ग_लिखो (01).
	   Clause 45 operation uses 00 क्रम the start and 11, 10 क्रम
	   पढ़ो/ग_लिखो */
	mdiobb_send_bit(ctrl, 0);
	अगर (op & MDIO_C45)
		mdiobb_send_bit(ctrl, 0);
	अन्यथा
		mdiobb_send_bit(ctrl, 1);
	mdiobb_send_bit(ctrl, (op >> 1) & 1);
	mdiobb_send_bit(ctrl, (op >> 0) & 1);

	mdiobb_send_num(ctrl, phy, 5);
	mdiobb_send_num(ctrl, reg, 5);
पूर्ण

/* In clause 45 mode all commands are prefixed by MDIO_ADDR to specअगरy the
   lower 16 bits of the 21 bit address. This transfer is करोne identically to a
   MDIO_WRITE except क्रम a dअगरferent code. To enable clause 45 mode or
   MII_ADDR_C45 पूर्णांकo the address. Theoretically clause 45 and normal devices
   can exist on the same bus. Normal devices should ignore the MDIO_ADDR
   phase. */
अटल पूर्णांक mdiobb_cmd_addr(काष्ठा mdiobb_ctrl *ctrl, पूर्णांक phy, u32 addr)
अणु
	अचिन्हित पूर्णांक dev_addr = (addr >> 16) & 0x1F;
	अचिन्हित पूर्णांक reg = addr & 0xFFFF;
	mdiobb_cmd(ctrl, MDIO_C45_ADDR, phy, dev_addr);

	/* send the turnaround (10) */
	mdiobb_send_bit(ctrl, 1);
	mdiobb_send_bit(ctrl, 0);

	mdiobb_send_num(ctrl, reg, 16);

	ctrl->ops->set_mdio_dir(ctrl, 0);
	mdiobb_get_bit(ctrl);

	वापस dev_addr;
पूर्ण

पूर्णांक mdiobb_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg)
अणु
	काष्ठा mdiobb_ctrl *ctrl = bus->priv;
	पूर्णांक ret, i;

	अगर (reg & MII_ADDR_C45) अणु
		reg = mdiobb_cmd_addr(ctrl, phy, reg);
		mdiobb_cmd(ctrl, MDIO_C45_READ, phy, reg);
	पूर्ण अन्यथा
		mdiobb_cmd(ctrl, ctrl->op_c22_पढ़ो, phy, reg);

	ctrl->ops->set_mdio_dir(ctrl, 0);

	/* check the turnaround bit: the PHY should be driving it to zero, अगर this
	 * PHY is listed in phy_ignore_ta_mask as having broken TA, skip that
	 */
	अगर (mdiobb_get_bit(ctrl) != 0 &&
	    !(bus->phy_ignore_ta_mask & (1 << phy))) अणु
		/* PHY didn't drive TA low -- flush any bits it
		 * may be trying to send.
		 */
		क्रम (i = 0; i < 32; i++)
			mdiobb_get_bit(ctrl);

		वापस 0xffff;
	पूर्ण

	ret = mdiobb_get_num(ctrl, 16);
	mdiobb_get_bit(ctrl);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(mdiobb_पढ़ो);

पूर्णांक mdiobb_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy, पूर्णांक reg, u16 val)
अणु
	काष्ठा mdiobb_ctrl *ctrl = bus->priv;

	अगर (reg & MII_ADDR_C45) अणु
		reg = mdiobb_cmd_addr(ctrl, phy, reg);
		mdiobb_cmd(ctrl, MDIO_C45_WRITE, phy, reg);
	पूर्ण अन्यथा
		mdiobb_cmd(ctrl, ctrl->op_c22_ग_लिखो, phy, reg);

	/* send the turnaround (10) */
	mdiobb_send_bit(ctrl, 1);
	mdiobb_send_bit(ctrl, 0);

	mdiobb_send_num(ctrl, val, 16);

	ctrl->ops->set_mdio_dir(ctrl, 0);
	mdiobb_get_bit(ctrl);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(mdiobb_ग_लिखो);

काष्ठा mii_bus *alloc_mdio_bitbang(काष्ठा mdiobb_ctrl *ctrl)
अणु
	काष्ठा mii_bus *bus;

	bus = mdiobus_alloc();
	अगर (!bus)
		वापस शून्य;

	__module_get(ctrl->ops->owner);

	bus->पढ़ो = mdiobb_पढ़ो;
	bus->ग_लिखो = mdiobb_ग_लिखो;
	bus->priv = ctrl;
	अगर (!ctrl->override_op_c22) अणु
		ctrl->op_c22_पढ़ो = MDIO_READ;
		ctrl->op_c22_ग_लिखो = MDIO_WRITE;
	पूर्ण

	वापस bus;
पूर्ण
EXPORT_SYMBOL(alloc_mdio_bitbang);

व्योम मुक्त_mdio_bitbang(काष्ठा mii_bus *bus)
अणु
	काष्ठा mdiobb_ctrl *ctrl = bus->priv;

	module_put(ctrl->ops->owner);
	mdiobus_मुक्त(bus);
पूर्ण
EXPORT_SYMBOL(मुक्त_mdio_bitbang);

MODULE_LICENSE("GPL v2");
