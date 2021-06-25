<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
// Copyright (C) IBM Corporation 2018
// FSI master driver क्रम AST2600

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/fsi.h>
#समावेश <linux/पन.स>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "fsi-master.h"

काष्ठा fsi_master_aspeed अणु
	काष्ठा fsi_master	master;
	काष्ठा mutex		lock;	/* protect HW access */
	काष्ठा device		*dev;
	व्योम __iomem		*base;
	काष्ठा clk		*clk;
	काष्ठा gpio_desc	*cfam_reset_gpio;
पूर्ण;

#घोषणा to_fsi_master_aspeed(m) \
	container_of(m, काष्ठा fsi_master_aspeed, master)

/* Control रेजिस्टर (size 0x400) */
अटल स्थिर u32 ctrl_base = 0x80000000;

अटल स्थिर u32 fsi_base = 0xa0000000;

#घोषणा OPB_FSI_VER	0x00
#घोषणा OPB_TRIGGER	0x04
#घोषणा OPB_CTRL_BASE	0x08
#घोषणा OPB_FSI_BASE	0x0c
#घोषणा OPB_CLK_SYNC	0x3c
#घोषणा OPB_IRQ_CLEAR	0x40
#घोषणा OPB_IRQ_MASK	0x44
#घोषणा OPB_IRQ_STATUS	0x48

#घोषणा OPB0_SELECT	0x10
#घोषणा OPB0_RW		0x14
#घोषणा OPB0_XFER_SIZE	0x18
#घोषणा OPB0_FSI_ADDR	0x1c
#घोषणा OPB0_FSI_DATA_W	0x20
#घोषणा OPB0_STATUS	0x80
#घोषणा OPB0_FSI_DATA_R	0x84

#घोषणा OPB0_WRITE_ORDER1	0x4c
#घोषणा OPB0_WRITE_ORDER2	0x50
#घोषणा OPB1_WRITE_ORDER1	0x54
#घोषणा OPB1_WRITE_ORDER2	0x58
#घोषणा OPB0_READ_ORDER1	0x5c
#घोषणा OPB1_READ_ORDER2	0x60

#घोषणा OPB_RETRY_COUNTER	0x64

/* OPBn_STATUS */
#घोषणा STATUS_HALFWORD_ACK	BIT(0)
#घोषणा STATUS_FULLWORD_ACK	BIT(1)
#घोषणा STATUS_ERR_ACK		BIT(2)
#घोषणा STATUS_RETRY		BIT(3)
#घोषणा STATUS_TIMEOUT		BIT(4)

/* OPB_IRQ_MASK */
#घोषणा OPB1_XFER_ACK_EN BIT(17)
#घोषणा OPB0_XFER_ACK_EN BIT(16)

/* OPB_RW */
#घोषणा CMD_READ	BIT(0)
#घोषणा CMD_WRITE	0

/* OPBx_XFER_SIZE */
#घोषणा XFER_FULLWORD	(BIT(1) | BIT(0))
#घोषणा XFER_HALFWORD	(BIT(0))
#घोषणा XFER_BYTE	(0)

#घोषणा CREATE_TRACE_POINTS
#समावेश <trace/events/fsi_master_aspeed.h>

#घोषणा FSI_LINK_ENABLE_SETUP_TIME	10	/* in mS */

/* Run the bus at maximum speed by शेष */
#घोषणा FSI_DIVISOR_DEFAULT            1
#घोषणा FSI_DIVISOR_CABLED             2
अटल u16 aspeed_fsi_भागisor = FSI_DIVISOR_DEFAULT;
module_param_named(bus_भाग,aspeed_fsi_भागisor, uलघु, 0);

#घोषणा OPB_POLL_TIMEOUT		10000

अटल पूर्णांक __opb_ग_लिखो(काष्ठा fsi_master_aspeed *aspeed, u32 addr,
		       u32 val, u32 transfer_size)
अणु
	व्योम __iomem *base = aspeed->base;
	u32 reg, status;
	पूर्णांक ret;

	ग_लिखोl(CMD_WRITE, base + OPB0_RW);
	ग_लिखोl(transfer_size, base + OPB0_XFER_SIZE);
	ग_लिखोl(addr, base + OPB0_FSI_ADDR);
	ग_लिखोl(val, base + OPB0_FSI_DATA_W);
	ग_लिखोl(0x1, base + OPB_IRQ_CLEAR);
	ग_लिखोl(0x1, base + OPB_TRIGGER);

	ret = पढ़ोl_poll_समयout(base + OPB_IRQ_STATUS, reg,
				(reg & OPB0_XFER_ACK_EN) != 0,
				0, OPB_POLL_TIMEOUT);

	status = पढ़ोl(base + OPB0_STATUS);

	trace_fsi_master_aspeed_opb_ग_लिखो(addr, val, transfer_size, status, reg);

	/* Return error when poll समयd out */
	अगर (ret)
		वापस ret;

	/* Command failed, master will reset */
	अगर (status & STATUS_ERR_ACK)
		वापस -EIO;

	वापस 0;
पूर्ण

अटल पूर्णांक opb_ग_लिखोb(काष्ठा fsi_master_aspeed *aspeed, u32 addr, u8 val)
अणु
	वापस __opb_ग_लिखो(aspeed, addr, val, XFER_BYTE);
पूर्ण

अटल पूर्णांक opb_ग_लिखोw(काष्ठा fsi_master_aspeed *aspeed, u32 addr, __be16 val)
अणु
	वापस __opb_ग_लिखो(aspeed, addr, (__क्रमce u16)val, XFER_HALFWORD);
पूर्ण

अटल पूर्णांक opb_ग_लिखोl(काष्ठा fsi_master_aspeed *aspeed, u32 addr, __be32 val)
अणु
	वापस __opb_ग_लिखो(aspeed, addr, (__क्रमce u32)val, XFER_FULLWORD);
पूर्ण

अटल पूर्णांक __opb_पढ़ो(काष्ठा fsi_master_aspeed *aspeed, uपूर्णांक32_t addr,
		      u32 transfer_size, व्योम *out)
अणु
	व्योम __iomem *base = aspeed->base;
	u32 result, reg;
	पूर्णांक status, ret;

	ग_लिखोl(CMD_READ, base + OPB0_RW);
	ग_लिखोl(transfer_size, base + OPB0_XFER_SIZE);
	ग_लिखोl(addr, base + OPB0_FSI_ADDR);
	ग_लिखोl(0x1, base + OPB_IRQ_CLEAR);
	ग_लिखोl(0x1, base + OPB_TRIGGER);

	ret = पढ़ोl_poll_समयout(base + OPB_IRQ_STATUS, reg,
			   (reg & OPB0_XFER_ACK_EN) != 0,
			   0, OPB_POLL_TIMEOUT);

	status = पढ़ोl(base + OPB0_STATUS);

	result = पढ़ोl(base + OPB0_FSI_DATA_R);

	trace_fsi_master_aspeed_opb_पढ़ो(addr, transfer_size, result,
			पढ़ोl(base + OPB0_STATUS),
			reg);

	/* Return error when poll समयd out */
	अगर (ret)
		वापस ret;

	/* Command failed, master will reset */
	अगर (status & STATUS_ERR_ACK)
		वापस -EIO;

	अगर (out) अणु
		चयन (transfer_size) अणु
		हाल XFER_BYTE:
			*(u8 *)out = result;
			अवरोध;
		हाल XFER_HALFWORD:
			*(u16 *)out = result;
			अवरोध;
		हाल XFER_FULLWORD:
			*(u32 *)out = result;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक opb_पढ़ोl(काष्ठा fsi_master_aspeed *aspeed, uपूर्णांक32_t addr, __be32 *out)
अणु
	वापस __opb_पढ़ो(aspeed, addr, XFER_FULLWORD, out);
पूर्ण

अटल पूर्णांक opb_पढ़ोw(काष्ठा fsi_master_aspeed *aspeed, uपूर्णांक32_t addr, __be16 *out)
अणु
	वापस __opb_पढ़ो(aspeed, addr, XFER_HALFWORD, (व्योम *)out);
पूर्ण

अटल पूर्णांक opb_पढ़ोb(काष्ठा fsi_master_aspeed *aspeed, uपूर्णांक32_t addr, u8 *out)
अणु
	वापस __opb_पढ़ो(aspeed, addr, XFER_BYTE, (व्योम *)out);
पूर्ण

अटल पूर्णांक check_errors(काष्ठा fsi_master_aspeed *aspeed, पूर्णांक err)
अणु
	पूर्णांक ret;

	अगर (trace_fsi_master_aspeed_opb_error_enabled()) अणु
		__be32 mresp0, mstap0, mesrb0;

		opb_पढ़ोl(aspeed, ctrl_base + FSI_MRESP0, &mresp0);
		opb_पढ़ोl(aspeed, ctrl_base + FSI_MSTAP0, &mstap0);
		opb_पढ़ोl(aspeed, ctrl_base + FSI_MESRB0, &mesrb0);

		trace_fsi_master_aspeed_opb_error(
				be32_to_cpu(mresp0),
				be32_to_cpu(mstap0),
				be32_to_cpu(mesrb0));
	पूर्ण

	अगर (err == -EIO) अणु
		/* Check MAEB (0x70) ? */

		/* Then clear errors in master */
		ret = opb_ग_लिखोl(aspeed, ctrl_base + FSI_MRESP0,
				cpu_to_be32(FSI_MRESP_RST_ALL_MASTER));
		अगर (ret) अणु
			/* TODO: log? वापस dअगरferent code? */
			वापस ret;
		पूर्ण
		/* TODO: confirm that 0x70 was okay */
	पूर्ण

	/* This will pass through समयout errors */
	वापस err;
पूर्ण

अटल पूर्णांक aspeed_master_पढ़ो(काष्ठा fsi_master *master, पूर्णांक link,
			uपूर्णांक8_t id, uपूर्णांक32_t addr, व्योम *val, माप_प्रकार size)
अणु
	काष्ठा fsi_master_aspeed *aspeed = to_fsi_master_aspeed(master);
	पूर्णांक ret;

	अगर (id > 0x3)
		वापस -EINVAL;

	addr |= id << 21;
	addr += link * FSI_HUB_LINK_SIZE;

	mutex_lock(&aspeed->lock);

	चयन (size) अणु
	हाल 1:
		ret = opb_पढ़ोb(aspeed, fsi_base + addr, val);
		अवरोध;
	हाल 2:
		ret = opb_पढ़ोw(aspeed, fsi_base + addr, val);
		अवरोध;
	हाल 4:
		ret = opb_पढ़ोl(aspeed, fsi_base + addr, val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = check_errors(aspeed, ret);
करोne:
	mutex_unlock(&aspeed->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_master_ग_लिखो(काष्ठा fsi_master *master, पूर्णांक link,
			uपूर्णांक8_t id, uपूर्णांक32_t addr, स्थिर व्योम *val, माप_प्रकार size)
अणु
	काष्ठा fsi_master_aspeed *aspeed = to_fsi_master_aspeed(master);
	पूर्णांक ret;

	अगर (id > 0x3)
		वापस -EINVAL;

	addr |= id << 21;
	addr += link * FSI_HUB_LINK_SIZE;

	mutex_lock(&aspeed->lock);

	चयन (size) अणु
	हाल 1:
		ret = opb_ग_लिखोb(aspeed, fsi_base + addr, *(u8 *)val);
		अवरोध;
	हाल 2:
		ret = opb_ग_लिखोw(aspeed, fsi_base + addr, *(__be16 *)val);
		अवरोध;
	हाल 4:
		ret = opb_ग_लिखोl(aspeed, fsi_base + addr, *(__be32 *)val);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	ret = check_errors(aspeed, ret);
करोne:
	mutex_unlock(&aspeed->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_master_link_enable(काष्ठा fsi_master *master, पूर्णांक link,
				     bool enable)
अणु
	काष्ठा fsi_master_aspeed *aspeed = to_fsi_master_aspeed(master);
	पूर्णांक idx, bit, ret;
	__be32 reg;

	idx = link / 32;
	bit = link % 32;

	reg = cpu_to_be32(0x80000000 >> bit);

	mutex_lock(&aspeed->lock);

	अगर (!enable) अणु
		ret = opb_ग_लिखोl(aspeed, ctrl_base + FSI_MCENP0 + (4 * idx), reg);
		जाओ करोne;
	पूर्ण

	ret = opb_ग_लिखोl(aspeed, ctrl_base + FSI_MSENP0 + (4 * idx), reg);
	अगर (ret)
		जाओ करोne;

	mdelay(FSI_LINK_ENABLE_SETUP_TIME);
करोne:
	mutex_unlock(&aspeed->lock);
	वापस ret;
पूर्ण

अटल पूर्णांक aspeed_master_term(काष्ठा fsi_master *master, पूर्णांक link, uपूर्णांक8_t id)
अणु
	uपूर्णांक32_t addr;
	__be32 cmd;

	addr = 0x4;
	cmd = cpu_to_be32(0xecc00000);

	वापस aspeed_master_ग_लिखो(master, link, id, addr, &cmd, 4);
पूर्ण

अटल पूर्णांक aspeed_master_अवरोध(काष्ठा fsi_master *master, पूर्णांक link)
अणु
	uपूर्णांक32_t addr;
	__be32 cmd;

	addr = 0x0;
	cmd = cpu_to_be32(0xc0de0000);

	वापस aspeed_master_ग_लिखो(master, link, 0, addr, &cmd, 4);
पूर्ण

अटल व्योम aspeed_master_release(काष्ठा device *dev)
अणु
	काष्ठा fsi_master_aspeed *aspeed =
		to_fsi_master_aspeed(dev_to_fsi_master(dev));

	kमुक्त(aspeed);
पूर्ण

/* mmode encoders */
अटल अंतरभूत u32 fsi_mmode_crs0(u32 x)
अणु
	वापस (x & FSI_MMODE_CRS0MASK) << FSI_MMODE_CRS0SHFT;
पूर्ण

अटल अंतरभूत u32 fsi_mmode_crs1(u32 x)
अणु
	वापस (x & FSI_MMODE_CRS1MASK) << FSI_MMODE_CRS1SHFT;
पूर्ण

अटल पूर्णांक aspeed_master_init(काष्ठा fsi_master_aspeed *aspeed)
अणु
	__be32 reg;

	reg = cpu_to_be32(FSI_MRESP_RST_ALL_MASTER | FSI_MRESP_RST_ALL_LINK
			| FSI_MRESP_RST_MCR | FSI_MRESP_RST_PYE);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MRESP0, reg);

	/* Initialize the MFSI (hub master) engine */
	reg = cpu_to_be32(FSI_MRESP_RST_ALL_MASTER | FSI_MRESP_RST_ALL_LINK
			| FSI_MRESP_RST_MCR | FSI_MRESP_RST_PYE);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MRESP0, reg);

	reg = cpu_to_be32(FSI_MECTRL_EOAE | FSI_MECTRL_P8_AUTO_TERM);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MECTRL, reg);

	reg = cpu_to_be32(FSI_MMODE_ECRC | FSI_MMODE_EPC | FSI_MMODE_RELA
			| fsi_mmode_crs0(aspeed_fsi_भागisor)
			| fsi_mmode_crs1(aspeed_fsi_भागisor)
			| FSI_MMODE_P8_TO_LSB);
	dev_info(aspeed->dev, "mmode set to %08x (divisor %d)\n",
			be32_to_cpu(reg), aspeed_fsi_भागisor);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MMODE, reg);

	reg = cpu_to_be32(0xffff0000);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MDLYR, reg);

	reg = cpu_to_be32(~0);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MSENP0, reg);

	/* Leave enabled दीर्घ enough क्रम master logic to set up */
	mdelay(FSI_LINK_ENABLE_SETUP_TIME);

	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MCENP0, reg);

	opb_पढ़ोl(aspeed, ctrl_base + FSI_MAEB, शून्य);

	reg = cpu_to_be32(FSI_MRESP_RST_ALL_MASTER | FSI_MRESP_RST_ALL_LINK);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MRESP0, reg);

	opb_पढ़ोl(aspeed, ctrl_base + FSI_MLEVP0, शून्य);

	/* Reset the master bridge */
	reg = cpu_to_be32(FSI_MRESB_RST_GEN);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MRESB0, reg);

	reg = cpu_to_be32(FSI_MRESB_RST_ERR);
	opb_ग_लिखोl(aspeed, ctrl_base + FSI_MRESB0, reg);

	वापस 0;
पूर्ण

अटल sमाप_प्रकार cfam_reset_store(काष्ठा device *dev, काष्ठा device_attribute *attr,
				स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा fsi_master_aspeed *aspeed = dev_get_drvdata(dev);

	mutex_lock(&aspeed->lock);
	gpiod_set_value(aspeed->cfam_reset_gpio, 1);
	usleep_range(900, 1000);
	gpiod_set_value(aspeed->cfam_reset_gpio, 0);
	mutex_unlock(&aspeed->lock);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(cfam_reset, 0200, शून्य, cfam_reset_store);

अटल पूर्णांक setup_cfam_reset(काष्ठा fsi_master_aspeed *aspeed)
अणु
	काष्ठा device *dev = aspeed->dev;
	काष्ठा gpio_desc *gpio;
	पूर्णांक rc;

	gpio = devm_gpiod_get_optional(dev, "cfam-reset", GPIOD_OUT_LOW);
	अगर (IS_ERR(gpio))
		वापस PTR_ERR(gpio);
	अगर (!gpio)
		वापस 0;

	aspeed->cfam_reset_gpio = gpio;

	rc = device_create_file(dev, &dev_attr_cfam_reset);
	अगर (rc) अणु
		devm_gpiod_put(dev, gpio);
		वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tacoma_cabled_fsi_fixup(काष्ठा device *dev)
अणु
	काष्ठा gpio_desc *routing_gpio, *mux_gpio;
	पूर्णांक gpio;

	/*
	 * The routing GPIO is a jumper indicating we should mux क्रम the
	 * बाह्यally connected FSI cable.
	 */
	routing_gpio = devm_gpiod_get_optional(dev, "fsi-routing",
			GPIOD_IN | GPIOD_FLAGS_BIT_NONEXCLUSIVE);
	अगर (IS_ERR(routing_gpio))
		वापस PTR_ERR(routing_gpio);
	अगर (!routing_gpio)
		वापस 0;

	mux_gpio = devm_gpiod_get_optional(dev, "fsi-mux", GPIOD_ASIS);
	अगर (IS_ERR(mux_gpio))
		वापस PTR_ERR(mux_gpio);
	अगर (!mux_gpio)
		वापस 0;

	gpio = gpiod_get_value(routing_gpio);
	अगर (gpio < 0)
		वापस gpio;

	/* If the routing GPIO is high we should set the mux to low. */
	अगर (gpio) अणु
		/*
		 * Cable संकेत पूर्णांकegrity means we should run the bus
		 * slightly slower. Do not override अगर a kernel param
		 * has alपढ़ोy overridden.
		 */
		अगर (aspeed_fsi_भागisor == FSI_DIVISOR_DEFAULT)
			aspeed_fsi_भागisor = FSI_DIVISOR_CABLED;

		gpiod_direction_output(mux_gpio, 0);
		dev_info(dev, "FSI configured for external cable\n");
	पूर्ण अन्यथा अणु
		gpiod_direction_output(mux_gpio, 1);
	पूर्ण

	devm_gpiod_put(dev, routing_gpio);

	वापस 0;
पूर्ण

अटल पूर्णांक fsi_master_aspeed_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master_aspeed *aspeed;
	काष्ठा resource *res;
	पूर्णांक rc, links, reg;
	__be32 raw;

	rc = tacoma_cabled_fsi_fixup(&pdev->dev);
	अगर (rc) अणु
		dev_err(&pdev->dev, "Tacoma FSI cable fixup failed\n");
		वापस rc;
	पूर्ण

	aspeed = devm_kzalloc(&pdev->dev, माप(*aspeed), GFP_KERNEL);
	अगर (!aspeed)
		वापस -ENOMEM;

	aspeed->dev = &pdev->dev;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	aspeed->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(aspeed->base))
		वापस PTR_ERR(aspeed->base);

	aspeed->clk = devm_clk_get(aspeed->dev, शून्य);
	अगर (IS_ERR(aspeed->clk)) अणु
		dev_err(aspeed->dev, "couldn't get clock\n");
		वापस PTR_ERR(aspeed->clk);
	पूर्ण
	rc = clk_prepare_enable(aspeed->clk);
	अगर (rc) अणु
		dev_err(aspeed->dev, "couldn't enable clock\n");
		वापस rc;
	पूर्ण

	rc = setup_cfam_reset(aspeed);
	अगर (rc) अणु
		dev_err(&pdev->dev, "CFAM reset GPIO setup failed\n");
	पूर्ण

	ग_लिखोl(0x1, aspeed->base + OPB_CLK_SYNC);
	ग_लिखोl(OPB1_XFER_ACK_EN | OPB0_XFER_ACK_EN,
			aspeed->base + OPB_IRQ_MASK);

	/* TODO: determine an appropriate value */
	ग_लिखोl(0x10, aspeed->base + OPB_RETRY_COUNTER);

	ग_लिखोl(ctrl_base, aspeed->base + OPB_CTRL_BASE);
	ग_लिखोl(fsi_base, aspeed->base + OPB_FSI_BASE);

	/* Set पढ़ो data order */
	ग_लिखोl(0x00030b1b, aspeed->base + OPB0_READ_ORDER1);

	/* Set ग_लिखो data order */
	ग_लिखोl(0x0011101b, aspeed->base + OPB0_WRITE_ORDER1);
	ग_लिखोl(0x0c330f3f, aspeed->base + OPB0_WRITE_ORDER2);

	/*
	 * Select OPB0 क्रम all operations.
	 * Will need to be reworked when enabling DMA or anything that uses
	 * OPB1.
	 */
	ग_लिखोl(0x1, aspeed->base + OPB0_SELECT);

	rc = opb_पढ़ोl(aspeed, ctrl_base + FSI_MVER, &raw);
	अगर (rc) अणु
		dev_err(&pdev->dev, "failed to read hub version\n");
		वापस rc;
	पूर्ण

	reg = be32_to_cpu(raw);
	links = (reg >> 8) & 0xff;
	dev_info(&pdev->dev, "hub version %08x (%d links)\n", reg, links);

	aspeed->master.dev.parent = &pdev->dev;
	aspeed->master.dev.release = aspeed_master_release;
	aspeed->master.dev.of_node = of_node_get(dev_of_node(&pdev->dev));

	aspeed->master.n_links = links;
	aspeed->master.पढ़ो = aspeed_master_पढ़ो;
	aspeed->master.ग_लिखो = aspeed_master_ग_लिखो;
	aspeed->master.send_अवरोध = aspeed_master_अवरोध;
	aspeed->master.term = aspeed_master_term;
	aspeed->master.link_enable = aspeed_master_link_enable;

	dev_set_drvdata(&pdev->dev, aspeed);

	mutex_init(&aspeed->lock);
	aspeed_master_init(aspeed);

	rc = fsi_master_रेजिस्टर(&aspeed->master);
	अगर (rc)
		जाओ err_release;

	/* At this poपूर्णांक, fsi_master_रेजिस्टर perक्रमms the device_initialize(),
	 * and holds the sole reference on master.dev. This means the device
	 * will be मुक्तd (via ->release) during any subsequent call to
	 * fsi_master_unरेजिस्टर.  We add our own reference to it here, so we
	 * can perक्रमm cleanup (in _हटाओ()) without it being मुक्तd beक्रमe
	 * we're पढ़ोy.
	 */
	get_device(&aspeed->master.dev);
	वापस 0;

err_release:
	clk_disable_unprepare(aspeed->clk);
	वापस rc;
पूर्ण

अटल पूर्णांक fsi_master_aspeed_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fsi_master_aspeed *aspeed = platक्रमm_get_drvdata(pdev);

	fsi_master_unरेजिस्टर(&aspeed->master);
	clk_disable_unprepare(aspeed->clk);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fsi_master_aspeed_match[] = अणु
	अणु .compatible = "aspeed,ast2600-fsi-master" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fsi_master_aspeed_driver = अणु
	.driver = अणु
		.name		= "fsi-master-aspeed",
		.of_match_table	= fsi_master_aspeed_match,
	पूर्ण,
	.probe	= fsi_master_aspeed_probe,
	.हटाओ = fsi_master_aspeed_हटाओ,
पूर्ण;

module_platक्रमm_driver(fsi_master_aspeed_driver);
MODULE_LICENSE("GPL");
