<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/***************************************************************************
 *
 * Copyright (C) 2004-2008 SMSC
 * Copyright (C) 2005-2008 ARM
 *
 ***************************************************************************
 * Rewritten, heavily based on smsc911x simple driver by SMSC.
 * Partly uses io macros from smc91x.c by Nicolas Pitre
 *
 * Supported devices:
 *   LAN9115, LAN9116, LAN9117, LAN9118
 *   LAN9215, LAN9216, LAN9217, LAN9218
 *   LAN9210, LAN9211
 *   LAN9220, LAN9221
 *   LAN89218,LAN9250
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/crc32.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/sched.h>
#समावेश <linux/समयr.h>
#समावेश <linux/bug.h>
#समावेश <linux/bitops.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>
#समावेश <linux/swab.h>
#समावेश <linux/phy.h>
#समावेश <linux/smsc911x.h>
#समावेश <linux/device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/acpi.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/property.h>
#समावेश <linux/gpio/consumer.h>

#समावेश "smsc911x.h"

#घोषणा SMSC_CHIPNAME		"smsc911x"
#घोषणा SMSC_MDIONAME		"smsc911x-mdio"
#घोषणा SMSC_DRV_VERSION	"2008-10-21"

MODULE_LICENSE("GPL");
MODULE_VERSION(SMSC_DRV_VERSION);
MODULE_ALIAS("platform:smsc911x");

#अगर USE_DEBUG > 0
अटल पूर्णांक debug = 16;
#अन्यथा
अटल पूर्णांक debug = 3;
#पूर्ण_अगर

module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

काष्ठा smsc911x_data;

काष्ठा smsc911x_ops अणु
	u32 (*reg_पढ़ो)(काष्ठा smsc911x_data *pdata, u32 reg);
	व्योम (*reg_ग_लिखो)(काष्ठा smsc911x_data *pdata, u32 reg, u32 val);
	व्योम (*rx_पढ़ोfअगरo)(काष्ठा smsc911x_data *pdata,
				अचिन्हित पूर्णांक *buf, अचिन्हित पूर्णांक wordcount);
	व्योम (*tx_ग_लिखोfअगरo)(काष्ठा smsc911x_data *pdata,
				अचिन्हित पूर्णांक *buf, अचिन्हित पूर्णांक wordcount);
पूर्ण;

#घोषणा SMSC911X_NUM_SUPPLIES 2

काष्ठा smsc911x_data अणु
	व्योम __iomem *ioaddr;

	अचिन्हित पूर्णांक idrev;

	/* used to decide which workarounds apply */
	अचिन्हित पूर्णांक generation;

	/* device configuration (copied from platक्रमm_data during probe) */
	काष्ठा smsc911x_platक्रमm_config config;

	/* This needs to be acquired beक्रमe calling any of below:
	 * smsc911x_mac_पढ़ो(), smsc911x_mac_ग_लिखो()
	 */
	spinlock_t mac_lock;

	/* spinlock to ensure रेजिस्टर accesses are serialised */
	spinlock_t dev_lock;

	काष्ठा mii_bus *mii_bus;
	अचिन्हित पूर्णांक using_extphy;
	पूर्णांक last_duplex;
	पूर्णांक last_carrier;

	u32 msg_enable;
	अचिन्हित पूर्णांक gpio_setting;
	अचिन्हित पूर्णांक gpio_orig_setting;
	काष्ठा net_device *dev;
	काष्ठा napi_काष्ठा napi;

	अचिन्हित पूर्णांक software_irq_संकेत;

#अगर_घोषित USE_PHY_WORK_AROUND
#घोषणा MIN_PACKET_SIZE (64)
	अक्षर loopback_tx_pkt[MIN_PACKET_SIZE];
	अक्षर loopback_rx_pkt[MIN_PACKET_SIZE];
	अचिन्हित पूर्णांक resetcount;
#पूर्ण_अगर

	/* Members क्रम Multicast filter workaround */
	अचिन्हित पूर्णांक multicast_update_pending;
	अचिन्हित पूर्णांक set_bits_mask;
	अचिन्हित पूर्णांक clear_bits_mask;
	अचिन्हित पूर्णांक hashhi;
	अचिन्हित पूर्णांक hashlo;

	/* रेजिस्टर access functions */
	स्थिर काष्ठा smsc911x_ops *ops;

	/* regulators */
	काष्ठा regulator_bulk_data supplies[SMSC911X_NUM_SUPPLIES];

	/* Reset GPIO */
	काष्ठा gpio_desc *reset_gpiod;

	/* घड़ी */
	काष्ठा clk *clk;
पूर्ण;

/* Easy access to inक्रमmation */
#घोषणा __smsc_shअगरt(pdata, reg) ((reg) << ((pdata)->config.shअगरt))

अटल अंतरभूत u32 __smsc911x_reg_पढ़ो(काष्ठा smsc911x_data *pdata, u32 reg)
अणु
	अगर (pdata->config.flags & SMSC911X_USE_32BIT)
		वापस पढ़ोl(pdata->ioaddr + reg);

	अगर (pdata->config.flags & SMSC911X_USE_16BIT)
		वापस ((पढ़ोw(pdata->ioaddr + reg) & 0xFFFF) |
			((पढ़ोw(pdata->ioaddr + reg + 2) & 0xFFFF) << 16));

	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत u32
__smsc911x_reg_पढ़ो_shअगरt(काष्ठा smsc911x_data *pdata, u32 reg)
अणु
	अगर (pdata->config.flags & SMSC911X_USE_32BIT)
		वापस पढ़ोl(pdata->ioaddr + __smsc_shअगरt(pdata, reg));

	अगर (pdata->config.flags & SMSC911X_USE_16BIT)
		वापस (पढ़ोw(pdata->ioaddr +
				__smsc_shअगरt(pdata, reg)) & 0xFFFF) |
			((पढ़ोw(pdata->ioaddr +
			__smsc_shअगरt(pdata, reg + 2)) & 0xFFFF) << 16);

	BUG();
	वापस 0;
पूर्ण

अटल अंतरभूत u32 smsc911x_reg_पढ़ो(काष्ठा smsc911x_data *pdata, u32 reg)
अणु
	u32 data;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);
	data = pdata->ops->reg_पढ़ो(pdata, reg);
	spin_unlock_irqrestore(&pdata->dev_lock, flags);

	वापस data;
पूर्ण

अटल अंतरभूत व्योम __smsc911x_reg_ग_लिखो(काष्ठा smsc911x_data *pdata, u32 reg,
					u32 val)
अणु
	अगर (pdata->config.flags & SMSC911X_USE_32BIT) अणु
		ग_लिखोl(val, pdata->ioaddr + reg);
		वापस;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_16BIT) अणु
		ग_लिखोw(val & 0xFFFF, pdata->ioaddr + reg);
		ग_लिखोw((val >> 16) & 0xFFFF, pdata->ioaddr + reg + 2);
		वापस;
	पूर्ण

	BUG();
पूर्ण

अटल अंतरभूत व्योम
__smsc911x_reg_ग_लिखो_shअगरt(काष्ठा smsc911x_data *pdata, u32 reg, u32 val)
अणु
	अगर (pdata->config.flags & SMSC911X_USE_32BIT) अणु
		ग_लिखोl(val, pdata->ioaddr + __smsc_shअगरt(pdata, reg));
		वापस;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_16BIT) अणु
		ग_लिखोw(val & 0xFFFF,
			pdata->ioaddr + __smsc_shअगरt(pdata, reg));
		ग_लिखोw((val >> 16) & 0xFFFF,
			pdata->ioaddr + __smsc_shअगरt(pdata, reg + 2));
		वापस;
	पूर्ण

	BUG();
पूर्ण

अटल अंतरभूत व्योम smsc911x_reg_ग_लिखो(काष्ठा smsc911x_data *pdata, u32 reg,
				      u32 val)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);
	pdata->ops->reg_ग_लिखो(pdata, reg, val);
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
पूर्ण

/* Writes a packet to the TX_DATA_FIFO */
अटल अंतरभूत व्योम
smsc911x_tx_ग_लिखोfअगरo(काष्ठा smsc911x_data *pdata, अचिन्हित पूर्णांक *buf,
		      अचिन्हित पूर्णांक wordcount)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);

	अगर (pdata->config.flags & SMSC911X_SWAP_FIFO) अणु
		जबतक (wordcount--)
			__smsc911x_reg_ग_लिखो(pdata, TX_DATA_FIFO,
					     swab32(*buf++));
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_32BIT) अणु
		ioग_लिखो32_rep(pdata->ioaddr + TX_DATA_FIFO, buf, wordcount);
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_16BIT) अणु
		जबतक (wordcount--)
			__smsc911x_reg_ग_लिखो(pdata, TX_DATA_FIFO, *buf++);
		जाओ out;
	पूर्ण

	BUG();
out:
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
पूर्ण

/* Writes a packet to the TX_DATA_FIFO - shअगरted version */
अटल अंतरभूत व्योम
smsc911x_tx_ग_लिखोfअगरo_shअगरt(काष्ठा smsc911x_data *pdata, अचिन्हित पूर्णांक *buf,
		      अचिन्हित पूर्णांक wordcount)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);

	अगर (pdata->config.flags & SMSC911X_SWAP_FIFO) अणु
		जबतक (wordcount--)
			__smsc911x_reg_ग_लिखो_shअगरt(pdata, TX_DATA_FIFO,
					     swab32(*buf++));
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_32BIT) अणु
		ioग_लिखो32_rep(pdata->ioaddr + __smsc_shअगरt(pdata,
						TX_DATA_FIFO), buf, wordcount);
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_16BIT) अणु
		जबतक (wordcount--)
			__smsc911x_reg_ग_लिखो_shअगरt(pdata,
						 TX_DATA_FIFO, *buf++);
		जाओ out;
	पूर्ण

	BUG();
out:
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
पूर्ण

/* Reads a packet out of the RX_DATA_FIFO */
अटल अंतरभूत व्योम
smsc911x_rx_पढ़ोfअगरo(काष्ठा smsc911x_data *pdata, अचिन्हित पूर्णांक *buf,
		     अचिन्हित पूर्णांक wordcount)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);

	अगर (pdata->config.flags & SMSC911X_SWAP_FIFO) अणु
		जबतक (wordcount--)
			*buf++ = swab32(__smsc911x_reg_पढ़ो(pdata,
							    RX_DATA_FIFO));
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_32BIT) अणु
		ioपढ़ो32_rep(pdata->ioaddr + RX_DATA_FIFO, buf, wordcount);
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_16BIT) अणु
		जबतक (wordcount--)
			*buf++ = __smsc911x_reg_पढ़ो(pdata, RX_DATA_FIFO);
		जाओ out;
	पूर्ण

	BUG();
out:
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
पूर्ण

/* Reads a packet out of the RX_DATA_FIFO - shअगरted version */
अटल अंतरभूत व्योम
smsc911x_rx_पढ़ोfअगरo_shअगरt(काष्ठा smsc911x_data *pdata, अचिन्हित पूर्णांक *buf,
		     अचिन्हित पूर्णांक wordcount)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&pdata->dev_lock, flags);

	अगर (pdata->config.flags & SMSC911X_SWAP_FIFO) अणु
		जबतक (wordcount--)
			*buf++ = swab32(__smsc911x_reg_पढ़ो_shअगरt(pdata,
							    RX_DATA_FIFO));
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_32BIT) अणु
		ioपढ़ो32_rep(pdata->ioaddr + __smsc_shअगरt(pdata,
						RX_DATA_FIFO), buf, wordcount);
		जाओ out;
	पूर्ण

	अगर (pdata->config.flags & SMSC911X_USE_16BIT) अणु
		जबतक (wordcount--)
			*buf++ = __smsc911x_reg_पढ़ो_shअगरt(pdata,
								RX_DATA_FIFO);
		जाओ out;
	पूर्ण

	BUG();
out:
	spin_unlock_irqrestore(&pdata->dev_lock, flags);
पूर्ण

/*
 * enable regulator and घड़ी resources.
 */
अटल पूर्णांक smsc911x_enable_resources(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smsc911x_data *pdata = netdev_priv(ndev);
	पूर्णांक ret = 0;

	ret = regulator_bulk_enable(ARRAY_SIZE(pdata->supplies),
			pdata->supplies);
	अगर (ret)
		netdev_err(ndev, "failed to enable regulators %d\n",
				ret);

	अगर (!IS_ERR(pdata->clk)) अणु
		ret = clk_prepare_enable(pdata->clk);
		अगर (ret < 0)
			netdev_err(ndev, "failed to enable clock %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

/*
 * disable resources, currently just regulators.
 */
अटल पूर्णांक smsc911x_disable_resources(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smsc911x_data *pdata = netdev_priv(ndev);
	पूर्णांक ret = 0;

	ret = regulator_bulk_disable(ARRAY_SIZE(pdata->supplies),
			pdata->supplies);

	अगर (!IS_ERR(pdata->clk))
		clk_disable_unprepare(pdata->clk);

	वापस ret;
पूर्ण

/*
 * Request resources, currently just regulators.
 *
 * The SMSC911x has two घातer pins: vddvario and vdd33a, in designs where
 * these are not always-on we need to request regulators to be turned on
 * beक्रमe we can try to access the device रेजिस्टरs.
 */
अटल पूर्णांक smsc911x_request_resources(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smsc911x_data *pdata = netdev_priv(ndev);
	पूर्णांक ret = 0;

	/* Request regulators */
	pdata->supplies[0].supply = "vdd33a";
	pdata->supplies[1].supply = "vddvario";
	ret = regulator_bulk_get(&pdev->dev,
			ARRAY_SIZE(pdata->supplies),
			pdata->supplies);
	अगर (ret) अणु
		/*
		 * Retry on deferrals, अन्यथा just report the error
		 * and try to जारी.
		 */
		अगर (ret == -EPROBE_DEFER)
			वापस ret;
		netdev_err(ndev, "couldn't get regulators %d\n",
				ret);
	पूर्ण

	/* Request optional RESET GPIO */
	pdata->reset_gpiod = devm_gpiod_get_optional(&pdev->dev,
						     "reset",
						     GPIOD_OUT_LOW);

	/* Request घड़ी */
	pdata->clk = clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(pdata->clk))
		dev_dbg(&pdev->dev, "couldn't get clock %li\n",
			PTR_ERR(pdata->clk));

	वापस ret;
पूर्ण

/*
 * Free resources, currently just regulators.
 *
 */
अटल व्योम smsc911x_मुक्त_resources(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा smsc911x_data *pdata = netdev_priv(ndev);

	/* Free regulators */
	regulator_bulk_मुक्त(ARRAY_SIZE(pdata->supplies),
			pdata->supplies);

	/* Free घड़ी */
	अगर (!IS_ERR(pdata->clk)) अणु
		clk_put(pdata->clk);
		pdata->clk = शून्य;
	पूर्ण
पूर्ण

/* रुकोs क्रम MAC not busy, with समयout.  Only called by smsc911x_mac_पढ़ो
 * and smsc911x_mac_ग_लिखो, so assumes mac_lock is held */
अटल पूर्णांक smsc911x_mac_complete(काष्ठा smsc911x_data *pdata)
अणु
	पूर्णांक i;
	u32 val;

	SMSC_ASSERT_MAC_LOCK(pdata);

	क्रम (i = 0; i < 40; i++) अणु
		val = smsc911x_reg_पढ़ो(pdata, MAC_CSR_CMD);
		अगर (!(val & MAC_CSR_CMD_CSR_BUSY_))
			वापस 0;
	पूर्ण
	SMSC_WARN(pdata, hw, "Timed out waiting for MAC not BUSY. "
		  "MAC_CSR_CMD: 0x%08X", val);
	वापस -EIO;
पूर्ण

/* Fetches a MAC रेजिस्टर value. Assumes mac_lock is acquired */
अटल u32 smsc911x_mac_पढ़ो(काष्ठा smsc911x_data *pdata, अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक temp;

	SMSC_ASSERT_MAC_LOCK(pdata);

	temp = smsc911x_reg_पढ़ो(pdata, MAC_CSR_CMD);
	अगर (unlikely(temp & MAC_CSR_CMD_CSR_BUSY_)) अणु
		SMSC_WARN(pdata, hw, "MAC busy at entry");
		वापस 0xFFFFFFFF;
	पूर्ण

	/* Send the MAC cmd */
	smsc911x_reg_ग_लिखो(pdata, MAC_CSR_CMD, ((offset & 0xFF) |
		MAC_CSR_CMD_CSR_BUSY_ | MAC_CSR_CMD_R_NOT_W_));

	/* Workaround क्रम hardware पढ़ो-after-ग_लिखो restriction */
	temp = smsc911x_reg_पढ़ो(pdata, BYTE_TEST);

	/* Wait क्रम the पढ़ो to complete */
	अगर (likely(smsc911x_mac_complete(pdata) == 0))
		वापस smsc911x_reg_पढ़ो(pdata, MAC_CSR_DATA);

	SMSC_WARN(pdata, hw, "MAC busy after read");
	वापस 0xFFFFFFFF;
पूर्ण

/* Set a mac रेजिस्टर, mac_lock must be acquired beक्रमe calling */
अटल व्योम smsc911x_mac_ग_लिखो(काष्ठा smsc911x_data *pdata,
			       अचिन्हित पूर्णांक offset, u32 val)
अणु
	अचिन्हित पूर्णांक temp;

	SMSC_ASSERT_MAC_LOCK(pdata);

	temp = smsc911x_reg_पढ़ो(pdata, MAC_CSR_CMD);
	अगर (unlikely(temp & MAC_CSR_CMD_CSR_BUSY_)) अणु
		SMSC_WARN(pdata, hw,
			  "smsc911x_mac_write failed, MAC busy at entry");
		वापस;
	पूर्ण

	/* Send data to ग_लिखो */
	smsc911x_reg_ग_लिखो(pdata, MAC_CSR_DATA, val);

	/* Write the actual data */
	smsc911x_reg_ग_लिखो(pdata, MAC_CSR_CMD, ((offset & 0xFF) |
		MAC_CSR_CMD_CSR_BUSY_));

	/* Workaround क्रम hardware पढ़ो-after-ग_लिखो restriction */
	temp = smsc911x_reg_पढ़ो(pdata, BYTE_TEST);

	/* Wait क्रम the ग_लिखो to complete */
	अगर (likely(smsc911x_mac_complete(pdata) == 0))
		वापस;

	SMSC_WARN(pdata, hw, "smsc911x_mac_write failed, MAC busy after write");
पूर्ण

/* Get a phy रेजिस्टर */
अटल पूर्णांक smsc911x_mii_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx)
अणु
	काष्ठा smsc911x_data *pdata = (काष्ठा smsc911x_data *)bus->priv;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक addr;
	पूर्णांक i, reg;

	pm_runसमय_get_sync(bus->parent);
	spin_lock_irqsave(&pdata->mac_lock, flags);

	/* Confirm MII not busy */
	अगर (unlikely(smsc911x_mac_पढ़ो(pdata, MII_ACC) & MII_ACC_MII_BUSY_)) अणु
		SMSC_WARN(pdata, hw, "MII is busy in smsc911x_mii_read???");
		reg = -EIO;
		जाओ out;
	पूर्ण

	/* Set the address, index & direction (पढ़ो from PHY) */
	addr = ((phyaddr & 0x1F) << 11) | ((regidx & 0x1F) << 6);
	smsc911x_mac_ग_लिखो(pdata, MII_ACC, addr);

	/* Wait क्रम पढ़ो to complete w/ समयout */
	क्रम (i = 0; i < 100; i++)
		अगर (!(smsc911x_mac_पढ़ो(pdata, MII_ACC) & MII_ACC_MII_BUSY_)) अणु
			reg = smsc911x_mac_पढ़ो(pdata, MII_DATA);
			जाओ out;
		पूर्ण

	SMSC_WARN(pdata, hw, "Timed out waiting for MII read to finish");
	reg = -EIO;

out:
	spin_unlock_irqrestore(&pdata->mac_lock, flags);
	pm_runसमय_put(bus->parent);
	वापस reg;
पूर्ण

/* Set a phy रेजिस्टर */
अटल पूर्णांक smsc911x_mii_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phyaddr, पूर्णांक regidx,
			   u16 val)
अणु
	काष्ठा smsc911x_data *pdata = (काष्ठा smsc911x_data *)bus->priv;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक addr;
	पूर्णांक i, reg;

	pm_runसमय_get_sync(bus->parent);
	spin_lock_irqsave(&pdata->mac_lock, flags);

	/* Confirm MII not busy */
	अगर (unlikely(smsc911x_mac_पढ़ो(pdata, MII_ACC) & MII_ACC_MII_BUSY_)) अणु
		SMSC_WARN(pdata, hw, "MII is busy in smsc911x_mii_write???");
		reg = -EIO;
		जाओ out;
	पूर्ण

	/* Put the data to ग_लिखो in the MAC */
	smsc911x_mac_ग_लिखो(pdata, MII_DATA, val);

	/* Set the address, index & direction (ग_लिखो to PHY) */
	addr = ((phyaddr & 0x1F) << 11) | ((regidx & 0x1F) << 6) |
		MII_ACC_MII_WRITE_;
	smsc911x_mac_ग_लिखो(pdata, MII_ACC, addr);

	/* Wait क्रम ग_लिखो to complete w/ समयout */
	क्रम (i = 0; i < 100; i++)
		अगर (!(smsc911x_mac_पढ़ो(pdata, MII_ACC) & MII_ACC_MII_BUSY_)) अणु
			reg = 0;
			जाओ out;
		पूर्ण

	SMSC_WARN(pdata, hw, "Timed out waiting for MII write to finish");
	reg = -EIO;

out:
	spin_unlock_irqrestore(&pdata->mac_lock, flags);
	pm_runसमय_put(bus->parent);
	वापस reg;
पूर्ण

/* Switch to बाह्यal phy. Assumes tx and rx are stopped. */
अटल व्योम smsc911x_phy_enable_बाह्यal(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक hwcfg = smsc911x_reg_पढ़ो(pdata, HW_CFG);

	/* Disable phy घड़ीs to the MAC */
	hwcfg &= (~HW_CFG_PHY_CLK_SEL_);
	hwcfg |= HW_CFG_PHY_CLK_SEL_CLK_DIS_;
	smsc911x_reg_ग_लिखो(pdata, HW_CFG, hwcfg);
	udelay(10);	/* Enough समय क्रम घड़ीs to stop */

	/* Switch to बाह्यal phy */
	hwcfg |= HW_CFG_EXT_PHY_EN_;
	smsc911x_reg_ग_लिखो(pdata, HW_CFG, hwcfg);

	/* Enable phy घड़ीs to the MAC */
	hwcfg &= (~HW_CFG_PHY_CLK_SEL_);
	hwcfg |= HW_CFG_PHY_CLK_SEL_EXT_PHY_;
	smsc911x_reg_ग_लिखो(pdata, HW_CFG, hwcfg);
	udelay(10);	/* Enough समय क्रम घड़ीs to restart */

	hwcfg |= HW_CFG_SMI_SEL_;
	smsc911x_reg_ग_लिखो(pdata, HW_CFG, hwcfg);
पूर्ण

/* Autodetects and enables बाह्यal phy अगर present on supported chips.
 * स्वतःdetection can be overridden by specअगरying SMSC911X_FORCE_INTERNAL_PHY
 * or SMSC911X_FORCE_EXTERNAL_PHY in the platक्रमm_data flags. */
अटल व्योम smsc911x_phy_initialise_बाह्यal(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक hwcfg = smsc911x_reg_पढ़ो(pdata, HW_CFG);

	अगर (pdata->config.flags & SMSC911X_FORCE_INTERNAL_PHY) अणु
		SMSC_TRACE(pdata, hw, "Forcing internal PHY");
		pdata->using_extphy = 0;
	पूर्ण अन्यथा अगर (pdata->config.flags & SMSC911X_FORCE_EXTERNAL_PHY) अणु
		SMSC_TRACE(pdata, hw, "Forcing external PHY");
		smsc911x_phy_enable_बाह्यal(pdata);
		pdata->using_extphy = 1;
	पूर्ण अन्यथा अगर (hwcfg & HW_CFG_EXT_PHY_DET_) अणु
		SMSC_TRACE(pdata, hw,
			   "HW_CFG EXT_PHY_DET set, using external PHY");
		smsc911x_phy_enable_बाह्यal(pdata);
		pdata->using_extphy = 1;
	पूर्ण अन्यथा अणु
		SMSC_TRACE(pdata, hw,
			   "HW_CFG EXT_PHY_DET clear, using internal PHY");
		pdata->using_extphy = 0;
	पूर्ण
पूर्ण

/* Fetches a tx status out of the status fअगरo */
अटल अचिन्हित पूर्णांक smsc911x_tx_get_txstatus(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक result =
	    smsc911x_reg_पढ़ो(pdata, TX_FIFO_INF) & TX_FIFO_INF_TSUSED_;

	अगर (result != 0)
		result = smsc911x_reg_पढ़ो(pdata, TX_STATUS_FIFO);

	वापस result;
पूर्ण

/* Fetches the next rx status */
अटल अचिन्हित पूर्णांक smsc911x_rx_get_rxstatus(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक result =
	    smsc911x_reg_पढ़ो(pdata, RX_FIFO_INF) & RX_FIFO_INF_RXSUSED_;

	अगर (result != 0)
		result = smsc911x_reg_पढ़ो(pdata, RX_STATUS_FIFO);

	वापस result;
पूर्ण

#अगर_घोषित USE_PHY_WORK_AROUND
अटल पूर्णांक smsc911x_phy_check_loopbackpkt(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक tries;
	u32 wrsz;
	u32 rdsz;
	uदीर्घ bufp;

	क्रम (tries = 0; tries < 10; tries++) अणु
		अचिन्हित पूर्णांक txcmd_a;
		अचिन्हित पूर्णांक txcmd_b;
		अचिन्हित पूर्णांक status;
		अचिन्हित पूर्णांक pktlength;
		अचिन्हित पूर्णांक i;

		/* Zero-out rx packet memory */
		स_रखो(pdata->loopback_rx_pkt, 0, MIN_PACKET_SIZE);

		/* Write tx packet to 118 */
		txcmd_a = (u32)((uदीर्घ)pdata->loopback_tx_pkt & 0x03) << 16;
		txcmd_a |= TX_CMD_A_FIRST_SEG_ | TX_CMD_A_LAST_SEG_;
		txcmd_a |= MIN_PACKET_SIZE;

		txcmd_b = MIN_PACKET_SIZE << 16 | MIN_PACKET_SIZE;

		smsc911x_reg_ग_लिखो(pdata, TX_DATA_FIFO, txcmd_a);
		smsc911x_reg_ग_लिखो(pdata, TX_DATA_FIFO, txcmd_b);

		bufp = (uदीर्घ)pdata->loopback_tx_pkt & (~0x3);
		wrsz = MIN_PACKET_SIZE + 3;
		wrsz += (u32)((uदीर्घ)pdata->loopback_tx_pkt & 0x3);
		wrsz >>= 2;

		pdata->ops->tx_ग_लिखोfअगरo(pdata, (अचिन्हित पूर्णांक *)bufp, wrsz);

		/* Wait till transmit is करोne */
		i = 60;
		करो अणु
			udelay(5);
			status = smsc911x_tx_get_txstatus(pdata);
		पूर्ण जबतक ((i--) && (!status));

		अगर (!status) अणु
			SMSC_WARN(pdata, hw,
				  "Failed to transmit during loopback test");
			जारी;
		पूर्ण
		अगर (status & TX_STS_ES_) अणु
			SMSC_WARN(pdata, hw,
				  "Transmit encountered errors during loopback test");
			जारी;
		पूर्ण

		/* Wait till receive is करोne */
		i = 60;
		करो अणु
			udelay(5);
			status = smsc911x_rx_get_rxstatus(pdata);
		पूर्ण जबतक ((i--) && (!status));

		अगर (!status) अणु
			SMSC_WARN(pdata, hw,
				  "Failed to receive during loopback test");
			जारी;
		पूर्ण
		अगर (status & RX_STS_ES_) अणु
			SMSC_WARN(pdata, hw,
				  "Receive encountered errors during loopback test");
			जारी;
		पूर्ण

		pktlength = ((status & 0x3FFF0000UL) >> 16);
		bufp = (uदीर्घ)pdata->loopback_rx_pkt;
		rdsz = pktlength + 3;
		rdsz += (u32)((uदीर्घ)pdata->loopback_rx_pkt & 0x3);
		rdsz >>= 2;

		pdata->ops->rx_पढ़ोfअगरo(pdata, (अचिन्हित पूर्णांक *)bufp, rdsz);

		अगर (pktlength != (MIN_PACKET_SIZE + 4)) अणु
			SMSC_WARN(pdata, hw, "Unexpected packet size "
				  "during loop back test, size=%d, will retry",
				  pktlength);
		पूर्ण अन्यथा अणु
			अचिन्हित पूर्णांक j;
			पूर्णांक mismatch = 0;
			क्रम (j = 0; j < MIN_PACKET_SIZE; j++) अणु
				अगर (pdata->loopback_tx_pkt[j]
				    != pdata->loopback_rx_pkt[j]) अणु
					mismatch = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (!mismatch) अणु
				SMSC_TRACE(pdata, hw, "Successfully verified "
					   "loopback packet");
				वापस 0;
			पूर्ण अन्यथा अणु
				SMSC_WARN(pdata, hw, "Data mismatch "
					  "during loop back test, will retry");
			पूर्ण
		पूर्ण
	पूर्ण

	वापस -EIO;
पूर्ण

अटल पूर्णांक smsc911x_phy_reset(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक temp;
	अचिन्हित पूर्णांक i = 100000;

	temp = smsc911x_reg_पढ़ो(pdata, PMT_CTRL);
	smsc911x_reg_ग_लिखो(pdata, PMT_CTRL, temp | PMT_CTRL_PHY_RST_);
	करो अणु
		msleep(1);
		temp = smsc911x_reg_पढ़ो(pdata, PMT_CTRL);
	पूर्ण जबतक ((i--) && (temp & PMT_CTRL_PHY_RST_));

	अगर (unlikely(temp & PMT_CTRL_PHY_RST_)) अणु
		SMSC_WARN(pdata, hw, "PHY reset failed to complete");
		वापस -EIO;
	पूर्ण
	/* Extra delay required because the phy may not be completed with
	* its reset when BMCR_RESET is cleared. Specs say 256 uS is
	* enough delay but using 1ms here to be safe */
	msleep(1);

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_phy_loopbacktest(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	काष्ठा phy_device *phy_dev = dev->phydev;
	पूर्णांक result = -EIO;
	अचिन्हित पूर्णांक i, val;
	अचिन्हित दीर्घ flags;

	/* Initialise tx packet using broadcast destination address */
	eth_broadcast_addr(pdata->loopback_tx_pkt);

	/* Use incrementing source address */
	क्रम (i = 6; i < 12; i++)
		pdata->loopback_tx_pkt[i] = (अक्षर)i;

	/* Set length type field */
	pdata->loopback_tx_pkt[12] = 0x00;
	pdata->loopback_tx_pkt[13] = 0x00;

	क्रम (i = 14; i < MIN_PACKET_SIZE; i++)
		pdata->loopback_tx_pkt[i] = (अक्षर)i;

	val = smsc911x_reg_पढ़ो(pdata, HW_CFG);
	val &= HW_CFG_TX_FIF_SZ_;
	val |= HW_CFG_SF_;
	smsc911x_reg_ग_लिखो(pdata, HW_CFG, val);

	smsc911x_reg_ग_लिखो(pdata, TX_CFG, TX_CFG_TX_ON_);
	smsc911x_reg_ग_लिखो(pdata, RX_CFG,
		(u32)((uदीर्घ)pdata->loopback_rx_pkt & 0x03) << 8);

	क्रम (i = 0; i < 10; i++) अणु
		/* Set PHY to 10/FD, no ANEG, and loopback mode */
		smsc911x_mii_ग_लिखो(phy_dev->mdio.bus, phy_dev->mdio.addr,
				   MII_BMCR, BMCR_LOOPBACK | BMCR_FULLDPLX);

		/* Enable MAC tx/rx, FD */
		spin_lock_irqsave(&pdata->mac_lock, flags);
		smsc911x_mac_ग_लिखो(pdata, MAC_CR, MAC_CR_FDPX_
				   | MAC_CR_TXEN_ | MAC_CR_RXEN_);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);

		अगर (smsc911x_phy_check_loopbackpkt(pdata) == 0) अणु
			result = 0;
			अवरोध;
		पूर्ण
		pdata->resetcount++;

		/* Disable MAC rx */
		spin_lock_irqsave(&pdata->mac_lock, flags);
		smsc911x_mac_ग_लिखो(pdata, MAC_CR, 0);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);

		smsc911x_phy_reset(pdata);
	पूर्ण

	/* Disable MAC */
	spin_lock_irqsave(&pdata->mac_lock, flags);
	smsc911x_mac_ग_लिखो(pdata, MAC_CR, 0);
	spin_unlock_irqrestore(&pdata->mac_lock, flags);

	/* Cancel PHY loopback mode */
	smsc911x_mii_ग_लिखो(phy_dev->mdio.bus, phy_dev->mdio.addr, MII_BMCR, 0);

	smsc911x_reg_ग_लिखो(pdata, TX_CFG, 0);
	smsc911x_reg_ग_लिखो(pdata, RX_CFG, 0);

	वापस result;
पूर्ण
#पूर्ण_अगर				/* USE_PHY_WORK_AROUND */

अटल व्योम smsc911x_phy_update_flowcontrol(काष्ठा smsc911x_data *pdata)
अणु
	काष्ठा net_device *ndev = pdata->dev;
	काष्ठा phy_device *phy_dev = ndev->phydev;
	u32 afc = smsc911x_reg_पढ़ो(pdata, AFC_CFG);
	u32 flow;
	अचिन्हित दीर्घ flags;

	अगर (phy_dev->duplex == DUPLEX_FULL) अणु
		u16 lcladv = phy_पढ़ो(phy_dev, MII_ADVERTISE);
		u16 rmtadv = phy_पढ़ो(phy_dev, MII_LPA);
		u8 cap = mii_resolve_flowctrl_fdx(lcladv, rmtadv);

		अगर (cap & FLOW_CTRL_RX)
			flow = 0xFFFF0002;
		अन्यथा
			flow = 0;

		अगर (cap & FLOW_CTRL_TX)
			afc |= 0xF;
		अन्यथा
			afc &= ~0xF;

		SMSC_TRACE(pdata, hw, "rx pause %s, tx pause %s",
			   (cap & FLOW_CTRL_RX ? "enabled" : "disabled"),
			   (cap & FLOW_CTRL_TX ? "enabled" : "disabled"));
	पूर्ण अन्यथा अणु
		SMSC_TRACE(pdata, hw, "half duplex");
		flow = 0;
		afc |= 0xF;
	पूर्ण

	spin_lock_irqsave(&pdata->mac_lock, flags);
	smsc911x_mac_ग_लिखो(pdata, FLOW, flow);
	spin_unlock_irqrestore(&pdata->mac_lock, flags);

	smsc911x_reg_ग_लिखो(pdata, AFC_CFG, afc);
पूर्ण

/* Update link mode अगर anything has changed.  Called periodically when the
 * PHY is in polling mode, even अगर nothing has changed. */
अटल व्योम smsc911x_phy_adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	काष्ठा phy_device *phy_dev = dev->phydev;
	अचिन्हित दीर्घ flags;
	पूर्णांक carrier;

	अगर (phy_dev->duplex != pdata->last_duplex) अणु
		अचिन्हित पूर्णांक mac_cr;
		SMSC_TRACE(pdata, hw, "duplex state has changed");

		spin_lock_irqsave(&pdata->mac_lock, flags);
		mac_cr = smsc911x_mac_पढ़ो(pdata, MAC_CR);
		अगर (phy_dev->duplex) अणु
			SMSC_TRACE(pdata, hw,
				   "configuring for full duplex mode");
			mac_cr |= MAC_CR_FDPX_;
		पूर्ण अन्यथा अणु
			SMSC_TRACE(pdata, hw,
				   "configuring for half duplex mode");
			mac_cr &= ~MAC_CR_FDPX_;
		पूर्ण
		smsc911x_mac_ग_लिखो(pdata, MAC_CR, mac_cr);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);

		smsc911x_phy_update_flowcontrol(pdata);
		pdata->last_duplex = phy_dev->duplex;
	पूर्ण

	carrier = netअगर_carrier_ok(dev);
	अगर (carrier != pdata->last_carrier) अणु
		SMSC_TRACE(pdata, hw, "carrier state has changed");
		अगर (carrier) अणु
			SMSC_TRACE(pdata, hw, "configuring for carrier OK");
			अगर ((pdata->gpio_orig_setting & GPIO_CFG_LED1_EN_) &&
			    (!pdata->using_extphy)) अणु
				/* Restore original GPIO configuration */
				pdata->gpio_setting = pdata->gpio_orig_setting;
				smsc911x_reg_ग_लिखो(pdata, GPIO_CFG,
					pdata->gpio_setting);
			पूर्ण
		पूर्ण अन्यथा अणु
			SMSC_TRACE(pdata, hw, "configuring for no carrier");
			/* Check global setting that LED1
			 * usage is 10/100 indicator */
			pdata->gpio_setting = smsc911x_reg_पढ़ो(pdata,
				GPIO_CFG);
			अगर ((pdata->gpio_setting & GPIO_CFG_LED1_EN_) &&
			    (!pdata->using_extphy)) अणु
				/* Force 10/100 LED off, after saving
				 * original GPIO configuration */
				pdata->gpio_orig_setting = pdata->gpio_setting;

				pdata->gpio_setting &= ~GPIO_CFG_LED1_EN_;
				pdata->gpio_setting |= (GPIO_CFG_GPIOBUF0_
							| GPIO_CFG_GPIOसूची0_
							| GPIO_CFG_GPIOD0_);
				smsc911x_reg_ग_लिखो(pdata, GPIO_CFG,
					pdata->gpio_setting);
			पूर्ण
		पूर्ण
		pdata->last_carrier = carrier;
	पूर्ण
पूर्ण

अटल पूर्णांक smsc911x_mii_probe(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	काष्ठा phy_device *phydev = शून्य;
	पूर्णांक ret;

	/* find the first phy */
	phydev = phy_find_first(pdata->mii_bus);
	अगर (!phydev) अणु
		netdev_err(dev, "no PHY found\n");
		वापस -ENODEV;
	पूर्ण

	SMSC_TRACE(pdata, probe, "PHY: addr %d, phy_id 0x%08X",
		   phydev->mdio.addr, phydev->phy_id);

	ret = phy_connect_direct(dev, phydev, &smsc911x_phy_adjust_link,
				 pdata->config.phy_पूर्णांकerface);

	अगर (ret) अणु
		netdev_err(dev, "Could not attach to PHY\n");
		वापस ret;
	पूर्ण

	phy_attached_info(phydev);

	phy_set_max_speed(phydev, SPEED_100);

	/* mask with MAC supported features */
	phy_support_asym_छोड़ो(phydev);

	pdata->last_duplex = -1;
	pdata->last_carrier = -1;

#अगर_घोषित USE_PHY_WORK_AROUND
	अगर (smsc911x_phy_loopbacktest(dev) < 0) अणु
		SMSC_WARN(pdata, hw, "Failed Loop Back Test");
		phy_disconnect(phydev);
		वापस -ENODEV;
	पूर्ण
	SMSC_TRACE(pdata, hw, "Passed Loop Back Test");
#पूर्ण_अगर				/* USE_PHY_WORK_AROUND */

	SMSC_TRACE(pdata, hw, "phy initialised successfully");
	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_mii_init(काष्ठा platक्रमm_device *pdev,
			     काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	पूर्णांक err = -ENXIO;

	pdata->mii_bus = mdiobus_alloc();
	अगर (!pdata->mii_bus) अणु
		err = -ENOMEM;
		जाओ err_out_1;
	पूर्ण

	pdata->mii_bus->name = SMSC_MDIONAME;
	snम_लिखो(pdata->mii_bus->id, MII_BUS_ID_SIZE, "%s-%x",
		pdev->name, pdev->id);
	pdata->mii_bus->priv = pdata;
	pdata->mii_bus->पढ़ो = smsc911x_mii_पढ़ो;
	pdata->mii_bus->ग_लिखो = smsc911x_mii_ग_लिखो;

	pdata->mii_bus->parent = &pdev->dev;

	चयन (pdata->idrev & 0xFFFF0000) अणु
	हाल 0x01170000:
	हाल 0x01150000:
	हाल 0x117A0000:
	हाल 0x115A0000:
		/* External PHY supported, try to स्वतःdetect */
		smsc911x_phy_initialise_बाह्यal(pdata);
		अवरोध;
	शेष:
		SMSC_TRACE(pdata, hw, "External PHY is not supported, "
			   "using internal PHY");
		pdata->using_extphy = 0;
		अवरोध;
	पूर्ण

	अगर (!pdata->using_extphy) अणु
		/* Mask all PHYs except ID 1 (पूर्णांकernal) */
		pdata->mii_bus->phy_mask = ~(1 << 1);
	पूर्ण

	अगर (mdiobus_रेजिस्टर(pdata->mii_bus)) अणु
		SMSC_WARN(pdata, probe, "Error registering mii bus");
		जाओ err_out_मुक्त_bus_2;
	पूर्ण

	वापस 0;

err_out_मुक्त_bus_2:
	mdiobus_मुक्त(pdata->mii_bus);
err_out_1:
	वापस err;
पूर्ण

/* Gets the number of tx statuses in the fअगरo */
अटल अचिन्हित पूर्णांक smsc911x_tx_get_txstatcount(काष्ठा smsc911x_data *pdata)
अणु
	वापस (smsc911x_reg_पढ़ो(pdata, TX_FIFO_INF)
		& TX_FIFO_INF_TSUSED_) >> 16;
पूर्ण

/* Reads tx statuses and increments counters where necessary */
अटल व्योम smsc911x_tx_update_txcounters(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	अचिन्हित पूर्णांक tx_stat;

	जबतक ((tx_stat = smsc911x_tx_get_txstatus(pdata)) != 0) अणु
		अगर (unlikely(tx_stat & 0x80000000)) अणु
			/* In this driver the packet tag is used as the packet
			 * length. Since a packet length can never reach the
			 * size of 0x8000, this bit is reserved. It is worth
			 * noting that the "reserved bit" in the warning above
			 * करोes not reference a hardware defined reserved bit
			 * but rather a driver defined one.
			 */
			SMSC_WARN(pdata, hw, "Packet tag reserved bit is high");
		पूर्ण अन्यथा अणु
			अगर (unlikely(tx_stat & TX_STS_ES_)) अणु
				dev->stats.tx_errors++;
			पूर्ण अन्यथा अणु
				dev->stats.tx_packets++;
				dev->stats.tx_bytes += (tx_stat >> 16);
			पूर्ण
			अगर (unlikely(tx_stat & TX_STS_EXCESS_COL_)) अणु
				dev->stats.collisions += 16;
				dev->stats.tx_पातed_errors += 1;
			पूर्ण अन्यथा अणु
				dev->stats.collisions +=
				    ((tx_stat >> 3) & 0xF);
			पूर्ण
			अगर (unlikely(tx_stat & TX_STS_LOST_CARRIER_))
				dev->stats.tx_carrier_errors += 1;
			अगर (unlikely(tx_stat & TX_STS_LATE_COL_)) अणु
				dev->stats.collisions++;
				dev->stats.tx_पातed_errors++;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/* Increments the Rx error counters */
अटल व्योम
smsc911x_rx_counterrors(काष्ठा net_device *dev, अचिन्हित पूर्णांक rxstat)
अणु
	पूर्णांक crc_err = 0;

	अगर (unlikely(rxstat & RX_STS_ES_)) अणु
		dev->stats.rx_errors++;
		अगर (unlikely(rxstat & RX_STS_CRC_ERR_)) अणु
			dev->stats.rx_crc_errors++;
			crc_err = 1;
		पूर्ण
	पूर्ण
	अगर (likely(!crc_err)) अणु
		अगर (unlikely((rxstat & RX_STS_FRAME_TYPE_) &&
			     (rxstat & RX_STS_LENGTH_ERR_)))
			dev->stats.rx_length_errors++;
		अगर (rxstat & RX_STS_MCAST_)
			dev->stats.multicast++;
	पूर्ण
पूर्ण

/* Quickly dumps bad packets */
अटल व्योम
smsc911x_rx_fastक्रमward(काष्ठा smsc911x_data *pdata, अचिन्हित पूर्णांक pktwords)
अणु
	अगर (likely(pktwords >= 4)) अणु
		अचिन्हित पूर्णांक समयout = 500;
		अचिन्हित पूर्णांक val;
		smsc911x_reg_ग_लिखो(pdata, RX_DP_CTRL, RX_DP_CTRL_RX_FFWD_);
		करो अणु
			udelay(1);
			val = smsc911x_reg_पढ़ो(pdata, RX_DP_CTRL);
		पूर्ण जबतक ((val & RX_DP_CTRL_RX_FFWD_) && --समयout);

		अगर (unlikely(समयout == 0))
			SMSC_WARN(pdata, hw, "Timed out waiting for "
				  "RX FFWD to finish, RX_DP_CTRL: 0x%08X", val);
	पूर्ण अन्यथा अणु
		जबतक (pktwords--)
			smsc911x_reg_पढ़ो(pdata, RX_DATA_FIFO);
	पूर्ण
पूर्ण

/* NAPI poll function */
अटल पूर्णांक smsc911x_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा smsc911x_data *pdata =
		container_of(napi, काष्ठा smsc911x_data, napi);
	काष्ठा net_device *dev = pdata->dev;
	पूर्णांक npackets = 0;

	जबतक (npackets < budget) अणु
		अचिन्हित पूर्णांक pktlength;
		अचिन्हित पूर्णांक pktwords;
		काष्ठा sk_buff *skb;
		अचिन्हित पूर्णांक rxstat = smsc911x_rx_get_rxstatus(pdata);

		अगर (!rxstat) अणु
			अचिन्हित पूर्णांक temp;
			/* We processed all packets available.  Tell NAPI it can
			 * stop polling then re-enable rx पूर्णांकerrupts */
			smsc911x_reg_ग_लिखो(pdata, INT_STS, INT_STS_RSFL_);
			napi_complete(napi);
			temp = smsc911x_reg_पढ़ो(pdata, INT_EN);
			temp |= INT_EN_RSFL_EN_;
			smsc911x_reg_ग_लिखो(pdata, INT_EN, temp);
			अवरोध;
		पूर्ण

		/* Count packet क्रम NAPI scheduling, even अगर it has an error.
		 * Error packets still require cycles to discard */
		npackets++;

		pktlength = ((rxstat & 0x3FFF0000) >> 16);
		pktwords = (pktlength + NET_IP_ALIGN + 3) >> 2;
		smsc911x_rx_counterrors(dev, rxstat);

		अगर (unlikely(rxstat & RX_STS_ES_)) अणु
			SMSC_WARN(pdata, rx_err,
				  "Discarding packet with error bit set");
			/* Packet has an error, discard it and जारी with
			 * the next */
			smsc911x_rx_fastक्रमward(pdata, pktwords);
			dev->stats.rx_dropped++;
			जारी;
		पूर्ण

		skb = netdev_alloc_skb(dev, pktwords << 2);
		अगर (unlikely(!skb)) अणु
			SMSC_WARN(pdata, rx_err,
				  "Unable to allocate skb for rx packet");
			/* Drop the packet and stop this polling iteration */
			smsc911x_rx_fastक्रमward(pdata, pktwords);
			dev->stats.rx_dropped++;
			अवरोध;
		पूर्ण

		pdata->ops->rx_पढ़ोfअगरo(pdata,
				 (अचिन्हित पूर्णांक *)skb->data, pktwords);

		/* Align IP on 16B boundary */
		skb_reserve(skb, NET_IP_ALIGN);
		skb_put(skb, pktlength - 4);
		skb->protocol = eth_type_trans(skb, dev);
		skb_checksum_none_निश्चित(skb);
		netअगर_receive_skb(skb);

		/* Update counters */
		dev->stats.rx_packets++;
		dev->stats.rx_bytes += (pktlength - 4);
	पूर्ण

	/* Return total received packets */
	वापस npackets;
पूर्ण

/* Returns hash bit number क्रम given MAC address
 * Example:
 * 01 00 5E 00 00 01 -> वापसs bit number 31 */
अटल अचिन्हित पूर्णांक smsc911x_hash(अक्षर addr[ETH_ALEN])
अणु
	वापस (ether_crc(ETH_ALEN, addr) >> 26) & 0x3f;
पूर्ण

अटल व्योम smsc911x_rx_multicast_update(काष्ठा smsc911x_data *pdata)
अणु
	/* Perक्रमms the multicast & mac_cr update.  This is called when
	 * safe on the current hardware, and with the mac_lock held */
	अचिन्हित पूर्णांक mac_cr;

	SMSC_ASSERT_MAC_LOCK(pdata);

	mac_cr = smsc911x_mac_पढ़ो(pdata, MAC_CR);
	mac_cr |= pdata->set_bits_mask;
	mac_cr &= ~(pdata->clear_bits_mask);
	smsc911x_mac_ग_लिखो(pdata, MAC_CR, mac_cr);
	smsc911x_mac_ग_लिखो(pdata, HASHH, pdata->hashhi);
	smsc911x_mac_ग_लिखो(pdata, HASHL, pdata->hashlo);
	SMSC_TRACE(pdata, hw, "maccr 0x%08X, HASHH 0x%08X, HASHL 0x%08X",
		   mac_cr, pdata->hashhi, pdata->hashlo);
पूर्ण

अटल व्योम smsc911x_rx_multicast_update_workaround(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक mac_cr;

	/* This function is only called क्रम older LAN911x devices
	 * (revA or revB), where MAC_CR, HASHH and HASHL should not
	 * be modअगरied during Rx - newer devices immediately update the
	 * रेजिस्टरs.
	 *
	 * This is called from पूर्णांकerrupt context */

	spin_lock(&pdata->mac_lock);

	/* Check Rx has stopped */
	अगर (smsc911x_mac_पढ़ो(pdata, MAC_CR) & MAC_CR_RXEN_)
		SMSC_WARN(pdata, drv, "Rx not stopped");

	/* Perक्रमm the update - safe to करो now Rx has stopped */
	smsc911x_rx_multicast_update(pdata);

	/* Re-enable Rx */
	mac_cr = smsc911x_mac_पढ़ो(pdata, MAC_CR);
	mac_cr |= MAC_CR_RXEN_;
	smsc911x_mac_ग_लिखो(pdata, MAC_CR, mac_cr);

	pdata->multicast_update_pending = 0;

	spin_unlock(&pdata->mac_lock);
पूर्ण

अटल पूर्णांक smsc911x_phy_general_घातer_up(काष्ठा smsc911x_data *pdata)
अणु
	काष्ठा net_device *ndev = pdata->dev;
	काष्ठा phy_device *phy_dev = ndev->phydev;
	पूर्णांक rc = 0;

	अगर (!phy_dev)
		वापस rc;

	/* If the पूर्णांकernal PHY is in General Power-Down mode, all, except the
	 * management पूर्णांकerface, is घातered-करोwn and stays in that condition as
	 * दीर्घ as Phy रेजिस्टर bit 0.11 is HIGH.
	 *
	 * In that हाल, clear the bit 0.11, so the PHY घातers up and we can
	 * access to the phy रेजिस्टरs.
	 */
	rc = phy_पढ़ो(phy_dev, MII_BMCR);
	अगर (rc < 0) अणु
		SMSC_WARN(pdata, drv, "Failed reading PHY control reg");
		वापस rc;
	पूर्ण

	/* If the PHY general घातer-करोwn bit is not set is not necessary to
	 * disable the general घातer करोwn-mode.
	 */
	अगर (rc & BMCR_PDOWN) अणु
		rc = phy_ग_लिखो(phy_dev, MII_BMCR, rc & ~BMCR_PDOWN);
		अगर (rc < 0) अणु
			SMSC_WARN(pdata, drv, "Failed writing PHY control reg");
			वापस rc;
		पूर्ण

		usleep_range(1000, 1500);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_phy_disable_energy_detect(काष्ठा smsc911x_data *pdata)
अणु
	काष्ठा net_device *ndev = pdata->dev;
	काष्ठा phy_device *phy_dev = ndev->phydev;
	पूर्णांक rc = 0;

	अगर (!phy_dev)
		वापस rc;

	rc = phy_पढ़ो(phy_dev, MII_LAN83C185_CTRL_STATUS);

	अगर (rc < 0) अणु
		SMSC_WARN(pdata, drv, "Failed reading PHY control reg");
		वापस rc;
	पूर्ण

	/* Only disable अगर energy detect mode is alपढ़ोy enabled */
	अगर (rc & MII_LAN83C185_EDPWRDOWN) अणु
		/* Disable energy detect mode क्रम this SMSC Transceivers */
		rc = phy_ग_लिखो(phy_dev, MII_LAN83C185_CTRL_STATUS,
			       rc & (~MII_LAN83C185_EDPWRDOWN));

		अगर (rc < 0) अणु
			SMSC_WARN(pdata, drv, "Failed writing PHY control reg");
			वापस rc;
		पूर्ण
		/* Allow PHY to wakeup */
		mdelay(2);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_phy_enable_energy_detect(काष्ठा smsc911x_data *pdata)
अणु
	काष्ठा net_device *ndev = pdata->dev;
	काष्ठा phy_device *phy_dev = ndev->phydev;
	पूर्णांक rc = 0;

	अगर (!phy_dev)
		वापस rc;

	rc = phy_पढ़ो(phy_dev, MII_LAN83C185_CTRL_STATUS);

	अगर (rc < 0) अणु
		SMSC_WARN(pdata, drv, "Failed reading PHY control reg");
		वापस rc;
	पूर्ण

	/* Only enable अगर energy detect mode is alपढ़ोy disabled */
	अगर (!(rc & MII_LAN83C185_EDPWRDOWN)) अणु
		/* Enable energy detect mode क्रम this SMSC Transceivers */
		rc = phy_ग_लिखो(phy_dev, MII_LAN83C185_CTRL_STATUS,
			       rc | MII_LAN83C185_EDPWRDOWN);

		अगर (rc < 0) अणु
			SMSC_WARN(pdata, drv, "Failed writing PHY control reg");
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_soft_reset(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक temp;
	पूर्णांक ret;
	अचिन्हित पूर्णांक reset_offset = HW_CFG;
	अचिन्हित पूर्णांक reset_mask = HW_CFG_SRST_;

	/*
	 * Make sure to घातer-up the PHY chip beक्रमe करोing a reset, otherwise
	 * the reset fails.
	 */
	ret = smsc911x_phy_general_घातer_up(pdata);
	अगर (ret) अणु
		SMSC_WARN(pdata, drv, "Failed to power-up the PHY chip");
		वापस ret;
	पूर्ण

	/*
	 * LAN9210/LAN9211/LAN9220/LAN9221 chips have an पूर्णांकernal PHY that
	 * are initialized in a Energy Detect Power-Down mode that prevents
	 * the MAC chip to be software reseted. So we have to wakeup the PHY
	 * beक्रमe.
	 */
	अगर (pdata->generation == 4) अणु
		ret = smsc911x_phy_disable_energy_detect(pdata);

		अगर (ret) अणु
			SMSC_WARN(pdata, drv, "Failed to wakeup the PHY chip");
			वापस ret;
		पूर्ण
	पूर्ण

	अगर ((pdata->idrev & 0xFFFF0000) == LAN9250) अणु
		/* special reset क्रम  LAN9250 */
		reset_offset = RESET_CTL;
		reset_mask = RESET_CTL_DIGITAL_RST_;
	पूर्ण

	/* Reset the LAN911x */
	smsc911x_reg_ग_लिखो(pdata, reset_offset, reset_mask);

	/* verअगरy reset bit is cleared */
	समयout = 10;
	करो अणु
		udelay(10);
		temp = smsc911x_reg_पढ़ो(pdata, reset_offset);
	पूर्ण जबतक ((--समयout) && (temp & reset_mask));

	अगर (unlikely(temp & reset_mask)) अणु
		SMSC_WARN(pdata, drv, "Failed to complete reset");
		वापस -EIO;
	पूर्ण

	अगर (pdata->generation == 4) अणु
		ret = smsc911x_phy_enable_energy_detect(pdata);

		अगर (ret) अणु
			SMSC_WARN(pdata, drv, "Failed to wakeup the PHY chip");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* Sets the device MAC address to dev_addr, called with mac_lock held */
अटल व्योम
smsc911x_set_hw_mac_address(काष्ठा smsc911x_data *pdata, u8 dev_addr[6])
अणु
	u32 mac_high16 = (dev_addr[5] << 8) | dev_addr[4];
	u32 mac_low32 = (dev_addr[3] << 24) | (dev_addr[2] << 16) |
	    (dev_addr[1] << 8) | dev_addr[0];

	SMSC_ASSERT_MAC_LOCK(pdata);

	smsc911x_mac_ग_लिखो(pdata, ADDRH, mac_high16);
	smsc911x_mac_ग_लिखो(pdata, ADDRL, mac_low32);
पूर्ण

अटल व्योम smsc911x_disable_irq_chip(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);

	smsc911x_reg_ग_लिखो(pdata, INT_EN, 0);
	smsc911x_reg_ग_लिखो(pdata, INT_STS, 0xFFFFFFFF);
पूर्ण

अटल irqवापस_t smsc911x_irqhandler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	u32 पूर्णांकsts = smsc911x_reg_पढ़ो(pdata, INT_STS);
	u32 पूर्णांकen = smsc911x_reg_पढ़ो(pdata, INT_EN);
	पूर्णांक serviced = IRQ_NONE;
	u32 temp;

	अगर (unlikely(पूर्णांकsts & पूर्णांकen & INT_STS_SW_INT_)) अणु
		temp = smsc911x_reg_पढ़ो(pdata, INT_EN);
		temp &= (~INT_EN_SW_INT_EN_);
		smsc911x_reg_ग_लिखो(pdata, INT_EN, temp);
		smsc911x_reg_ग_लिखो(pdata, INT_STS, INT_STS_SW_INT_);
		pdata->software_irq_संकेत = 1;
		smp_wmb();
		serviced = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(पूर्णांकsts & पूर्णांकen & INT_STS_RXSTOP_INT_)) अणु
		/* Called when there is a multicast update scheduled and
		 * it is now safe to complete the update */
		SMSC_TRACE(pdata, पूर्णांकr, "RX Stop interrupt");
		smsc911x_reg_ग_लिखो(pdata, INT_STS, INT_STS_RXSTOP_INT_);
		अगर (pdata->multicast_update_pending)
			smsc911x_rx_multicast_update_workaround(pdata);
		serviced = IRQ_HANDLED;
	पूर्ण

	अगर (पूर्णांकsts & पूर्णांकen & INT_STS_TDFA_) अणु
		temp = smsc911x_reg_पढ़ो(pdata, FIFO_INT);
		temp |= FIFO_INT_TX_AVAIL_LEVEL_;
		smsc911x_reg_ग_लिखो(pdata, FIFO_INT, temp);
		smsc911x_reg_ग_लिखो(pdata, INT_STS, INT_STS_TDFA_);
		netअगर_wake_queue(dev);
		serviced = IRQ_HANDLED;
	पूर्ण

	अगर (unlikely(पूर्णांकsts & पूर्णांकen & INT_STS_RXE_)) अणु
		SMSC_TRACE(pdata, पूर्णांकr, "RX Error interrupt");
		smsc911x_reg_ग_लिखो(pdata, INT_STS, INT_STS_RXE_);
		serviced = IRQ_HANDLED;
	पूर्ण

	अगर (likely(पूर्णांकsts & पूर्णांकen & INT_STS_RSFL_)) अणु
		अगर (likely(napi_schedule_prep(&pdata->napi))) अणु
			/* Disable Rx पूर्णांकerrupts */
			temp = smsc911x_reg_पढ़ो(pdata, INT_EN);
			temp &= (~INT_EN_RSFL_EN_);
			smsc911x_reg_ग_लिखो(pdata, INT_EN, temp);
			/* Schedule a NAPI poll */
			__napi_schedule(&pdata->napi);
		पूर्ण अन्यथा अणु
			SMSC_WARN(pdata, rx_err, "napi_schedule_prep failed");
		पूर्ण
		serviced = IRQ_HANDLED;
	पूर्ण

	वापस serviced;
पूर्ण

अटल पूर्णांक smsc911x_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	अचिन्हित पूर्णांक समयout;
	अचिन्हित पूर्णांक temp;
	अचिन्हित पूर्णांक पूर्णांकcfg;
	पूर्णांक retval;
	पूर्णांक irq_flags;

	pm_runसमय_get_sync(dev->dev.parent);

	/* find and start the given phy */
	अगर (!dev->phydev) अणु
		retval = smsc911x_mii_probe(dev);
		अगर (retval < 0) अणु
			SMSC_WARN(pdata, probe, "Error starting phy");
			जाओ out;
		पूर्ण
	पूर्ण

	/* Reset the LAN911x */
	retval = smsc911x_soft_reset(pdata);
	अगर (retval) अणु
		SMSC_WARN(pdata, hw, "soft reset failed");
		जाओ mii_मुक्त_out;
	पूर्ण

	smsc911x_reg_ग_लिखो(pdata, HW_CFG, 0x00050000);
	smsc911x_reg_ग_लिखो(pdata, AFC_CFG, 0x006E3740);

	/* Increase the legal frame size of VLAN tagged frames to 1522 bytes */
	spin_lock_irq(&pdata->mac_lock);
	smsc911x_mac_ग_लिखो(pdata, VLAN1, ETH_P_8021Q);
	spin_unlock_irq(&pdata->mac_lock);

	/* Make sure EEPROM has finished loading beक्रमe setting GPIO_CFG */
	समयout = 50;
	जबतक ((smsc911x_reg_पढ़ो(pdata, E2P_CMD) & E2P_CMD_EPC_BUSY_) &&
	       --समयout) अणु
		udelay(10);
	पूर्ण

	अगर (unlikely(समयout == 0))
		SMSC_WARN(pdata, अगरup,
			  "Timed out waiting for EEPROM busy bit to clear");

	smsc911x_reg_ग_लिखो(pdata, GPIO_CFG, 0x70070000);

	/* The soft reset above cleared the device's MAC address,
	 * restore it from local copy (set in probe) */
	spin_lock_irq(&pdata->mac_lock);
	smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
	spin_unlock_irq(&pdata->mac_lock);

	/* Initialise irqs, but leave all sources disabled */
	smsc911x_disable_irq_chip(dev);

	/* Set पूर्णांकerrupt deनिश्चितion to 100uS */
	पूर्णांकcfg = ((10 << 24) | INT_CFG_IRQ_EN_);

	अगर (pdata->config.irq_polarity) अणु
		SMSC_TRACE(pdata, अगरup, "irq polarity: active high");
		पूर्णांकcfg |= INT_CFG_IRQ_POL_;
	पूर्ण अन्यथा अणु
		SMSC_TRACE(pdata, अगरup, "irq polarity: active low");
	पूर्ण

	अगर (pdata->config.irq_type) अणु
		SMSC_TRACE(pdata, अगरup, "irq type: push-pull");
		पूर्णांकcfg |= INT_CFG_IRQ_TYPE_;
	पूर्ण अन्यथा अणु
		SMSC_TRACE(pdata, अगरup, "irq type: open drain");
	पूर्ण

	smsc911x_reg_ग_लिखो(pdata, INT_CFG, पूर्णांकcfg);

	SMSC_TRACE(pdata, अगरup, "Testing irq handler using IRQ %d", dev->irq);
	pdata->software_irq_संकेत = 0;
	smp_wmb();

	irq_flags = irq_get_trigger_type(dev->irq);
	retval = request_irq(dev->irq, smsc911x_irqhandler,
			     irq_flags | IRQF_SHARED, dev->name, dev);
	अगर (retval) अणु
		SMSC_WARN(pdata, probe,
			  "Unable to claim requested irq: %d", dev->irq);
		जाओ mii_मुक्त_out;
	पूर्ण

	temp = smsc911x_reg_पढ़ो(pdata, INT_EN);
	temp |= INT_EN_SW_INT_EN_;
	smsc911x_reg_ग_लिखो(pdata, INT_EN, temp);

	समयout = 1000;
	जबतक (समयout--) अणु
		अगर (pdata->software_irq_संकेत)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (!pdata->software_irq_संकेत) अणु
		netdev_warn(dev, "ISR failed signaling test (IRQ %d)\n",
			    dev->irq);
		retval = -ENODEV;
		जाओ irq_stop_out;
	पूर्ण
	SMSC_TRACE(pdata, अगरup, "IRQ handler passed test using IRQ %d",
		   dev->irq);

	netdev_info(dev, "SMSC911x/921x identified at %#08lx, IRQ: %d\n",
		    (अचिन्हित दीर्घ)pdata->ioaddr, dev->irq);

	/* Reset the last known duplex and carrier */
	pdata->last_duplex = -1;
	pdata->last_carrier = -1;

	/* Bring the PHY up */
	phy_start(dev->phydev);

	temp = smsc911x_reg_पढ़ो(pdata, HW_CFG);
	/* Preserve TX FIFO size and बाह्यal PHY configuration */
	temp &= (HW_CFG_TX_FIF_SZ_|0x00000FFF);
	temp |= HW_CFG_SF_;
	smsc911x_reg_ग_लिखो(pdata, HW_CFG, temp);

	temp = smsc911x_reg_पढ़ो(pdata, FIFO_INT);
	temp |= FIFO_INT_TX_AVAIL_LEVEL_;
	temp &= ~(FIFO_INT_RX_STS_LEVEL_);
	smsc911x_reg_ग_लिखो(pdata, FIFO_INT, temp);

	/* set RX Data offset to 2 bytes क्रम alignment */
	smsc911x_reg_ग_लिखो(pdata, RX_CFG, (NET_IP_ALIGN << 8));

	/* enable NAPI polling beक्रमe enabling RX पूर्णांकerrupts */
	napi_enable(&pdata->napi);

	temp = smsc911x_reg_पढ़ो(pdata, INT_EN);
	temp |= (INT_EN_TDFA_EN_ | INT_EN_RSFL_EN_ | INT_EN_RXSTOP_INT_EN_);
	smsc911x_reg_ग_लिखो(pdata, INT_EN, temp);

	spin_lock_irq(&pdata->mac_lock);
	temp = smsc911x_mac_पढ़ो(pdata, MAC_CR);
	temp |= (MAC_CR_TXEN_ | MAC_CR_RXEN_ | MAC_CR_HBDIS_);
	smsc911x_mac_ग_लिखो(pdata, MAC_CR, temp);
	spin_unlock_irq(&pdata->mac_lock);

	smsc911x_reg_ग_लिखो(pdata, TX_CFG, TX_CFG_TX_ON_);

	netअगर_start_queue(dev);
	वापस 0;

irq_stop_out:
	मुक्त_irq(dev->irq, dev);
mii_मुक्त_out:
	phy_disconnect(dev->phydev);
	dev->phydev = शून्य;
out:
	pm_runसमय_put(dev->dev.parent);
	वापस retval;
पूर्ण

/* Entry poपूर्णांक क्रम stopping the पूर्णांकerface */
अटल पूर्णांक smsc911x_stop(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	अचिन्हित पूर्णांक temp;

	/* Disable all device पूर्णांकerrupts */
	temp = smsc911x_reg_पढ़ो(pdata, INT_CFG);
	temp &= ~INT_CFG_IRQ_EN_;
	smsc911x_reg_ग_लिखो(pdata, INT_CFG, temp);

	/* Stop Tx and Rx polling */
	netअगर_stop_queue(dev);
	napi_disable(&pdata->napi);

	/* At this poपूर्णांक all Rx and Tx activity is stopped */
	dev->stats.rx_dropped += smsc911x_reg_पढ़ो(pdata, RX_DROP);
	smsc911x_tx_update_txcounters(dev);

	मुक्त_irq(dev->irq, dev);

	/* Bring the PHY करोwn */
	अगर (dev->phydev) अणु
		phy_stop(dev->phydev);
		phy_disconnect(dev->phydev);
		dev->phydev = शून्य;
	पूर्ण
	netअगर_carrier_off(dev);
	pm_runसमय_put(dev->dev.parent);

	SMSC_TRACE(pdata, अगरकरोwn, "Interface stopped");
	वापस 0;
पूर्ण

/* Entry poपूर्णांक क्रम transmitting a packet */
अटल netdev_tx_t
smsc911x_hard_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	अचिन्हित पूर्णांक मुक्तspace;
	अचिन्हित पूर्णांक tx_cmd_a;
	अचिन्हित पूर्णांक tx_cmd_b;
	अचिन्हित पूर्णांक temp;
	u32 wrsz;
	uदीर्घ bufp;

	मुक्तspace = smsc911x_reg_पढ़ो(pdata, TX_FIFO_INF) & TX_FIFO_INF_TDFREE_;

	अगर (unlikely(मुक्तspace < TX_FIFO_LOW_THRESHOLD))
		SMSC_WARN(pdata, tx_err,
			  "Tx data fifo low, space available: %d", मुक्तspace);

	/* Word alignment adjusपंचांगent */
	tx_cmd_a = (u32)((uदीर्घ)skb->data & 0x03) << 16;
	tx_cmd_a |= TX_CMD_A_FIRST_SEG_ | TX_CMD_A_LAST_SEG_;
	tx_cmd_a |= (अचिन्हित पूर्णांक)skb->len;

	tx_cmd_b = ((अचिन्हित पूर्णांक)skb->len) << 16;
	tx_cmd_b |= (अचिन्हित पूर्णांक)skb->len;

	smsc911x_reg_ग_लिखो(pdata, TX_DATA_FIFO, tx_cmd_a);
	smsc911x_reg_ग_लिखो(pdata, TX_DATA_FIFO, tx_cmd_b);

	bufp = (uदीर्घ)skb->data & (~0x3);
	wrsz = (u32)skb->len + 3;
	wrsz += (u32)((uदीर्घ)skb->data & 0x3);
	wrsz >>= 2;

	pdata->ops->tx_ग_लिखोfअगरo(pdata, (अचिन्हित पूर्णांक *)bufp, wrsz);
	मुक्तspace -= (skb->len + 32);
	skb_tx_बारtamp(skb);
	dev_consume_skb_any(skb);

	अगर (unlikely(smsc911x_tx_get_txstatcount(pdata) >= 30))
		smsc911x_tx_update_txcounters(dev);

	अगर (मुक्तspace < TX_FIFO_LOW_THRESHOLD) अणु
		netअगर_stop_queue(dev);
		temp = smsc911x_reg_पढ़ो(pdata, FIFO_INT);
		temp &= 0x00FFFFFF;
		temp |= 0x32000000;
		smsc911x_reg_ग_लिखो(pdata, FIFO_INT, temp);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/* Entry poपूर्णांक क्रम getting status counters */
अटल काष्ठा net_device_stats *smsc911x_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	smsc911x_tx_update_txcounters(dev);
	dev->stats.rx_dropped += smsc911x_reg_पढ़ो(pdata, RX_DROP);
	वापस &dev->stats;
पूर्ण

/* Entry poपूर्णांक क्रम setting addressing modes */
अटल व्योम smsc911x_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	अगर (dev->flags & IFF_PROMISC) अणु
		/* Enabling promiscuous mode */
		pdata->set_bits_mask = MAC_CR_PRMS_;
		pdata->clear_bits_mask = (MAC_CR_MCPAS_ | MAC_CR_HPFILT_);
		pdata->hashhi = 0;
		pdata->hashlo = 0;
	पूर्ण अन्यथा अगर (dev->flags & IFF_ALLMULTI) अणु
		/* Enabling all multicast mode */
		pdata->set_bits_mask = MAC_CR_MCPAS_;
		pdata->clear_bits_mask = (MAC_CR_PRMS_ | MAC_CR_HPFILT_);
		pdata->hashhi = 0;
		pdata->hashlo = 0;
	पूर्ण अन्यथा अगर (!netdev_mc_empty(dev)) अणु
		/* Enabling specअगरic multicast addresses */
		अचिन्हित पूर्णांक hash_high = 0;
		अचिन्हित पूर्णांक hash_low = 0;
		काष्ठा netdev_hw_addr *ha;

		pdata->set_bits_mask = MAC_CR_HPFILT_;
		pdata->clear_bits_mask = (MAC_CR_PRMS_ | MAC_CR_MCPAS_);

		netdev_क्रम_each_mc_addr(ha, dev) अणु
			अचिन्हित पूर्णांक bitnum = smsc911x_hash(ha->addr);
			अचिन्हित पूर्णांक mask = 0x01 << (bitnum & 0x1F);

			अगर (bitnum & 0x20)
				hash_high |= mask;
			अन्यथा
				hash_low |= mask;
		पूर्ण

		pdata->hashhi = hash_high;
		pdata->hashlo = hash_low;
	पूर्ण अन्यथा अणु
		/* Enabling local MAC address only */
		pdata->set_bits_mask = 0;
		pdata->clear_bits_mask =
		    (MAC_CR_PRMS_ | MAC_CR_MCPAS_ | MAC_CR_HPFILT_);
		pdata->hashhi = 0;
		pdata->hashlo = 0;
	पूर्ण

	spin_lock_irqsave(&pdata->mac_lock, flags);

	अगर (pdata->generation <= 1) अणु
		/* Older hardware revision - cannot change these flags जबतक
		 * receiving data */
		अगर (!pdata->multicast_update_pending) अणु
			अचिन्हित पूर्णांक temp;
			SMSC_TRACE(pdata, hw, "scheduling mcast update");
			pdata->multicast_update_pending = 1;

			/* Request the hardware to stop, then perक्रमm the
			 * update when we get an RX_STOP पूर्णांकerrupt */
			temp = smsc911x_mac_पढ़ो(pdata, MAC_CR);
			temp &= ~(MAC_CR_RXEN_);
			smsc911x_mac_ग_लिखो(pdata, MAC_CR, temp);
		पूर्ण अन्यथा अणु
			/* There is another update pending, this should now
			 * use the newer values */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Newer hardware revision - can ग_लिखो immediately */
		smsc911x_rx_multicast_update(pdata);
	पूर्ण

	spin_unlock_irqrestore(&pdata->mac_lock, flags);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम smsc911x_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	smsc911x_irqhandler(0, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर				/* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक smsc911x_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;

	/* On older hardware revisions we cannot change the mac address
	 * रेजिस्टरs जबतक receiving data.  Newer devices can safely change
	 * this at any समय. */
	अगर (pdata->generation <= 1 && netअगर_running(dev))
		वापस -EBUSY;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, ETH_ALEN);

	spin_lock_irq(&pdata->mac_lock);
	smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
	spin_unlock_irq(&pdata->mac_lock);

	netdev_info(dev, "MAC Address: %pM\n", dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम smsc911x_ethtool_getdrvinfo(काष्ठा net_device *dev,
					काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, SMSC_CHIPNAME, माप(info->driver));
	strlcpy(info->version, SMSC_DRV_VERSION, माप(info->version));
	strlcpy(info->bus_info, dev_name(dev->dev.parent),
		माप(info->bus_info));
पूर्ण

अटल u32 smsc911x_ethtool_geपंचांगsglevel(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	वापस pdata->msg_enable;
पूर्ण

अटल व्योम smsc911x_ethtool_seपंचांगsglevel(काष्ठा net_device *dev, u32 level)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	pdata->msg_enable = level;
पूर्ण

अटल पूर्णांक smsc911x_ethtool_getregslen(काष्ठा net_device *dev)
अणु
	वापस (((E2P_DATA - ID_REV) / 4 + 1) + (WUCSR - MAC_CR) + 1 + 32) *
	    माप(u32);
पूर्ण

अटल व्योम
smsc911x_ethtool_getregs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs,
			 व्योम *buf)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	काष्ठा phy_device *phy_dev = dev->phydev;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक j = 0;
	u32 *data = buf;

	regs->version = pdata->idrev;
	क्रम (i = ID_REV; i <= E2P_DATA; i += (माप(u32)))
		data[j++] = smsc911x_reg_पढ़ो(pdata, i);

	क्रम (i = MAC_CR; i <= WUCSR; i++) अणु
		spin_lock_irqsave(&pdata->mac_lock, flags);
		data[j++] = smsc911x_mac_पढ़ो(pdata, i);
		spin_unlock_irqrestore(&pdata->mac_lock, flags);
	पूर्ण

	क्रम (i = 0; i <= 31; i++)
		data[j++] = smsc911x_mii_पढ़ो(phy_dev->mdio.bus,
					      phy_dev->mdio.addr, i);
पूर्ण

अटल व्योम smsc911x_eeprom_enable_access(काष्ठा smsc911x_data *pdata)
अणु
	अचिन्हित पूर्णांक temp = smsc911x_reg_पढ़ो(pdata, GPIO_CFG);
	temp &= ~GPIO_CFG_EEPR_EN_;
	smsc911x_reg_ग_लिखो(pdata, GPIO_CFG, temp);
	msleep(1);
पूर्ण

अटल पूर्णांक smsc911x_eeprom_send_cmd(काष्ठा smsc911x_data *pdata, u32 op)
अणु
	पूर्णांक समयout = 100;
	u32 e2cmd;

	SMSC_TRACE(pdata, drv, "op 0x%08x", op);
	अगर (smsc911x_reg_पढ़ो(pdata, E2P_CMD) & E2P_CMD_EPC_BUSY_) अणु
		SMSC_WARN(pdata, drv, "Busy at start");
		वापस -EBUSY;
	पूर्ण

	e2cmd = op | E2P_CMD_EPC_BUSY_;
	smsc911x_reg_ग_लिखो(pdata, E2P_CMD, e2cmd);

	करो अणु
		msleep(1);
		e2cmd = smsc911x_reg_पढ़ो(pdata, E2P_CMD);
	पूर्ण जबतक ((e2cmd & E2P_CMD_EPC_BUSY_) && (--समयout));

	अगर (!समयout) अणु
		SMSC_TRACE(pdata, drv, "TIMED OUT");
		वापस -EAGAIN;
	पूर्ण

	अगर (e2cmd & E2P_CMD_EPC_TIMEOUT_) अणु
		SMSC_TRACE(pdata, drv, "Error occurred during eeprom operation");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_eeprom_पढ़ो_location(काष्ठा smsc911x_data *pdata,
					 u8 address, u8 *data)
अणु
	u32 op = E2P_CMD_EPC_CMD_READ_ | address;
	पूर्णांक ret;

	SMSC_TRACE(pdata, drv, "address 0x%x", address);
	ret = smsc911x_eeprom_send_cmd(pdata, op);

	अगर (!ret)
		data[address] = smsc911x_reg_पढ़ो(pdata, E2P_DATA);

	वापस ret;
पूर्ण

अटल पूर्णांक smsc911x_eeprom_ग_लिखो_location(काष्ठा smsc911x_data *pdata,
					  u8 address, u8 data)
अणु
	u32 op = E2P_CMD_EPC_CMD_ERASE_ | address;
	पूर्णांक ret;

	SMSC_TRACE(pdata, drv, "address 0x%x, data 0x%x", address, data);
	ret = smsc911x_eeprom_send_cmd(pdata, op);

	अगर (!ret) अणु
		op = E2P_CMD_EPC_CMD_WRITE_ | address;
		smsc911x_reg_ग_लिखो(pdata, E2P_DATA, (u32)data);

		/* Workaround क्रम hardware पढ़ो-after-ग_लिखो restriction */
		smsc911x_reg_पढ़ो(pdata, BYTE_TEST);

		ret = smsc911x_eeprom_send_cmd(pdata, op);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक smsc911x_ethtool_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस SMSC911X_EEPROM_SIZE;
पूर्ण

अटल पूर्णांक smsc911x_ethtool_get_eeprom(काष्ठा net_device *dev,
				       काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	u8 eeprom_data[SMSC911X_EEPROM_SIZE];
	पूर्णांक len;
	पूर्णांक i;

	smsc911x_eeprom_enable_access(pdata);

	len = min(eeprom->len, SMSC911X_EEPROM_SIZE);
	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक ret = smsc911x_eeprom_पढ़ो_location(pdata, i, eeprom_data);
		अगर (ret < 0) अणु
			eeprom->len = 0;
			वापस ret;
		पूर्ण
	पूर्ण

	स_नकल(data, &eeprom_data[eeprom->offset], len);
	eeprom->len = len;
	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_ethtool_set_eeprom(काष्ठा net_device *dev,
				       काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	पूर्णांक ret;
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);

	smsc911x_eeprom_enable_access(pdata);
	smsc911x_eeprom_send_cmd(pdata, E2P_CMD_EPC_CMD_EWEN_);
	ret = smsc911x_eeprom_ग_लिखो_location(pdata, eeprom->offset, *data);
	smsc911x_eeprom_send_cmd(pdata, E2P_CMD_EPC_CMD_EWDS_);

	/* Single byte ग_लिखो, according to man page */
	eeprom->len = 1;

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops smsc911x_ethtool_ops = अणु
	.get_link = ethtool_op_get_link,
	.get_drvinfo = smsc911x_ethtool_getdrvinfo,
	.nway_reset = phy_ethtool_nway_reset,
	.get_msglevel = smsc911x_ethtool_geपंचांगsglevel,
	.set_msglevel = smsc911x_ethtool_seपंचांगsglevel,
	.get_regs_len = smsc911x_ethtool_getregslen,
	.get_regs = smsc911x_ethtool_getregs,
	.get_eeprom_len = smsc911x_ethtool_get_eeprom_len,
	.get_eeprom = smsc911x_ethtool_get_eeprom,
	.set_eeprom = smsc911x_ethtool_set_eeprom,
	.get_ts_info = ethtool_op_get_ts_info,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops smsc911x_netdev_ops = अणु
	.nकरो_खोलो		= smsc911x_खोलो,
	.nकरो_stop		= smsc911x_stop,
	.nकरो_start_xmit		= smsc911x_hard_start_xmit,
	.nकरो_get_stats		= smsc911x_get_stats,
	.nकरो_set_rx_mode	= smsc911x_set_multicast_list,
	.nकरो_करो_ioctl		= phy_करो_ioctl_running,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address 	= smsc911x_set_mac_address,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= smsc911x_poll_controller,
#पूर्ण_अगर
पूर्ण;

/* copies the current mac address from hardware to dev->dev_addr */
अटल व्योम smsc911x_पढ़ो_mac_address(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	u32 mac_high16 = smsc911x_mac_पढ़ो(pdata, ADDRH);
	u32 mac_low32 = smsc911x_mac_पढ़ो(pdata, ADDRL);

	dev->dev_addr[0] = (u8)(mac_low32);
	dev->dev_addr[1] = (u8)(mac_low32 >> 8);
	dev->dev_addr[2] = (u8)(mac_low32 >> 16);
	dev->dev_addr[3] = (u8)(mac_low32 >> 24);
	dev->dev_addr[4] = (u8)(mac_high16);
	dev->dev_addr[5] = (u8)(mac_high16 >> 8);
पूर्ण

/* Initializing निजी device काष्ठाures, only called from probe */
अटल पूर्णांक smsc911x_init(काष्ठा net_device *dev)
अणु
	काष्ठा smsc911x_data *pdata = netdev_priv(dev);
	अचिन्हित पूर्णांक byte_test, mask;
	अचिन्हित पूर्णांक to = 100;

	SMSC_TRACE(pdata, probe, "Driver Parameters:");
	SMSC_TRACE(pdata, probe, "LAN base: 0x%08lX",
		   (अचिन्हित दीर्घ)pdata->ioaddr);
	SMSC_TRACE(pdata, probe, "IRQ: %d", dev->irq);
	SMSC_TRACE(pdata, probe, "PHY will be autodetected.");

	spin_lock_init(&pdata->dev_lock);
	spin_lock_init(&pdata->mac_lock);

	अगर (pdata->ioaddr == शून्य) अणु
		SMSC_WARN(pdata, probe, "pdata->ioaddr: 0x00000000");
		वापस -ENODEV;
	पूर्ण

	/*
	 * poll the READY bit in PMT_CTRL. Any other access to the device is
	 * क्रमbidden जबतक this bit isn't set. Try क्रम 100ms
	 *
	 * Note that this test is करोne beक्रमe the WORD_SWAP रेजिस्टर is
	 * programmed. So in some configurations the READY bit is at 16 beक्रमe
	 * WORD_SWAP is written to. This issue is worked around by रुकोing
	 * until either bit 0 or bit 16 माला_लो set in PMT_CTRL.
	 *
	 * SMSC has confirmed that checking bit 16 (marked as reserved in
	 * the datasheet) is fine since these bits "will either never be set
	 * or can only go high after READY करोes (so also indicate the device
	 * is पढ़ोy)".
	 */

	mask = PMT_CTRL_READY_ | swahw32(PMT_CTRL_READY_);
	जबतक (!(smsc911x_reg_पढ़ो(pdata, PMT_CTRL) & mask) && --to)
		udelay(1000);

	अगर (to == 0) अणु
		netdev_err(dev, "Device not READY in 100ms aborting\n");
		वापस -ENODEV;
	पूर्ण

	/* Check byte ordering */
	byte_test = smsc911x_reg_पढ़ो(pdata, BYTE_TEST);
	SMSC_TRACE(pdata, probe, "BYTE_TEST: 0x%08X", byte_test);
	अगर (byte_test == 0x43218765) अणु
		SMSC_TRACE(pdata, probe, "BYTE_TEST looks swapped, "
			   "applying WORD_SWAP");
		smsc911x_reg_ग_लिखो(pdata, WORD_SWAP, 0xffffffff);

		/* 1 dummy पढ़ो of BYTE_TEST is needed after a ग_लिखो to
		 * WORD_SWAP beक्रमe its contents are valid */
		byte_test = smsc911x_reg_पढ़ो(pdata, BYTE_TEST);

		byte_test = smsc911x_reg_पढ़ो(pdata, BYTE_TEST);
	पूर्ण

	अगर (byte_test != 0x87654321) अणु
		SMSC_WARN(pdata, drv, "BYTE_TEST: 0x%08X", byte_test);
		अगर (((byte_test >> 16) & 0xFFFF) == (byte_test & 0xFFFF)) अणु
			SMSC_WARN(pdata, probe,
				  "top 16 bits equal to bottom 16 bits");
			SMSC_TRACE(pdata, probe,
				   "This may mean the chip is set "
				   "for 32 bit while the bus is reading 16 bit");
		पूर्ण
		वापस -ENODEV;
	पूर्ण

	/* Default generation to zero (all workarounds apply) */
	pdata->generation = 0;

	pdata->idrev = smsc911x_reg_पढ़ो(pdata, ID_REV);
	चयन (pdata->idrev & 0xFFFF0000) अणु
	हाल LAN9118:
	हाल LAN9117:
	हाल LAN9116:
	हाल LAN9115:
	हाल LAN89218:
		/* LAN911[5678] family */
		pdata->generation = pdata->idrev & 0x0000FFFF;
		अवरोध;

	हाल LAN9218:
	हाल LAN9217:
	हाल LAN9216:
	हाल LAN9215:
		/* LAN921[5678] family */
		pdata->generation = 3;
		अवरोध;

	हाल LAN9210:
	हाल LAN9211:
	हाल LAN9220:
	हाल LAN9221:
	हाल LAN9250:
		/* LAN9210/LAN9211/LAN9220/LAN9221/LAN9250 */
		pdata->generation = 4;
		अवरोध;

	शेष:
		SMSC_WARN(pdata, probe, "LAN911x not identified, idrev: 0x%08X",
			  pdata->idrev);
		वापस -ENODEV;
	पूर्ण

	SMSC_TRACE(pdata, probe,
		   "LAN911x identified, idrev: 0x%08X, generation: %d",
		   pdata->idrev, pdata->generation);

	अगर (pdata->generation == 0)
		SMSC_WARN(pdata, probe,
			  "This driver is not intended for this chip revision");

	/* workaround क्रम platक्रमms without an eeprom, where the mac address
	 * is stored अन्यथाwhere and set by the bootloader.  This saves the
	 * mac address beक्रमe resetting the device */
	अगर (pdata->config.flags & SMSC911X_SAVE_MAC_ADDRESS) अणु
		spin_lock_irq(&pdata->mac_lock);
		smsc911x_पढ़ो_mac_address(dev);
		spin_unlock_irq(&pdata->mac_lock);
	पूर्ण

	/* Reset the LAN911x */
	अगर (smsc911x_phy_reset(pdata) || smsc911x_soft_reset(pdata))
		वापस -ENODEV;

	dev->flags |= IFF_MULTICAST;
	netअगर_napi_add(dev, &pdata->napi, smsc911x_poll, SMSC_NAPI_WEIGHT);
	dev->netdev_ops = &smsc911x_netdev_ops;
	dev->ethtool_ops = &smsc911x_ethtool_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा smsc911x_data *pdata;
	काष्ठा resource *res;

	dev = platक्रमm_get_drvdata(pdev);
	BUG_ON(!dev);
	pdata = netdev_priv(dev);
	BUG_ON(!pdata);
	BUG_ON(!pdata->ioaddr);

	SMSC_TRACE(pdata, अगरकरोwn, "Stopping driver");

	unरेजिस्टर_netdev(dev);

	mdiobus_unरेजिस्टर(pdata->mii_bus);
	mdiobus_मुक्त(pdata->mii_bus);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "smsc911x-memory");
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);

	release_mem_region(res->start, resource_size(res));

	iounmap(pdata->ioaddr);

	(व्योम)smsc911x_disable_resources(pdev);
	smsc911x_मुक्त_resources(pdev);

	मुक्त_netdev(dev);

	pm_runसमय_disable(&pdev->dev);

	वापस 0;
पूर्ण

/* standard रेजिस्टर acces */
अटल स्थिर काष्ठा smsc911x_ops standard_smsc911x_ops = अणु
	.reg_पढ़ो = __smsc911x_reg_पढ़ो,
	.reg_ग_लिखो = __smsc911x_reg_ग_लिखो,
	.rx_पढ़ोfअगरo = smsc911x_rx_पढ़ोfअगरo,
	.tx_ग_लिखोfअगरo = smsc911x_tx_ग_लिखोfअगरo,
पूर्ण;

/* shअगरted रेजिस्टर access */
अटल स्थिर काष्ठा smsc911x_ops shअगरted_smsc911x_ops = अणु
	.reg_पढ़ो = __smsc911x_reg_पढ़ो_shअगरt,
	.reg_ग_लिखो = __smsc911x_reg_ग_लिखो_shअगरt,
	.rx_पढ़ोfअगरo = smsc911x_rx_पढ़ोfअगरo_shअगरt,
	.tx_ग_लिखोfअगरo = smsc911x_tx_ग_लिखोfअगरo_shअगरt,
पूर्ण;

अटल पूर्णांक smsc911x_probe_config(काष्ठा smsc911x_platक्रमm_config *config,
				 काष्ठा device *dev)
अणु
	पूर्णांक phy_पूर्णांकerface;
	u32 width = 0;
	पूर्णांक err;

	phy_पूर्णांकerface = device_get_phy_mode(dev);
	अगर (phy_पूर्णांकerface < 0)
		phy_पूर्णांकerface = PHY_INTERFACE_MODE_NA;
	config->phy_पूर्णांकerface = phy_पूर्णांकerface;

	device_get_mac_address(dev, config->mac, ETH_ALEN);

	err = device_property_पढ़ो_u32(dev, "reg-io-width", &width);
	अगर (err == -ENXIO)
		वापस err;
	अगर (!err && width == 4)
		config->flags |= SMSC911X_USE_32BIT;
	अन्यथा
		config->flags |= SMSC911X_USE_16BIT;

	device_property_पढ़ो_u32(dev, "reg-shift", &config->shअगरt);

	अगर (device_property_present(dev, "smsc,irq-active-high"))
		config->irq_polarity = SMSC911X_IRQ_POLARITY_ACTIVE_HIGH;

	अगर (device_property_present(dev, "smsc,irq-push-pull"))
		config->irq_type = SMSC911X_IRQ_TYPE_PUSH_PULL;

	अगर (device_property_present(dev, "smsc,force-internal-phy"))
		config->flags |= SMSC911X_FORCE_INTERNAL_PHY;

	अगर (device_property_present(dev, "smsc,force-external-phy"))
		config->flags |= SMSC911X_FORCE_EXTERNAL_PHY;

	अगर (device_property_present(dev, "smsc,save-mac-address"))
		config->flags |= SMSC911X_SAVE_MAC_ADDRESS;

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *dev;
	काष्ठा smsc911x_data *pdata;
	काष्ठा smsc911x_platक्रमm_config *config = dev_get_platdata(&pdev->dev);
	काष्ठा resource *res;
	पूर्णांक res_size, irq;
	पूर्णांक retval;

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM,
					   "smsc911x-memory");
	अगर (!res)
		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		pr_warn("Could not allocate resource\n");
		retval = -ENODEV;
		जाओ out_0;
	पूर्ण
	res_size = resource_size(res);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq == -EPROBE_DEFER) अणु
		retval = -EPROBE_DEFER;
		जाओ out_0;
	पूर्ण अन्यथा अगर (irq <= 0) अणु
		pr_warn("Could not allocate irq resource\n");
		retval = -ENODEV;
		जाओ out_0;
	पूर्ण

	अगर (!request_mem_region(res->start, res_size, SMSC_CHIPNAME)) अणु
		retval = -EBUSY;
		जाओ out_0;
	पूर्ण

	dev = alloc_etherdev(माप(काष्ठा smsc911x_data));
	अगर (!dev) अणु
		retval = -ENOMEM;
		जाओ out_release_io_1;
	पूर्ण

	SET_NETDEV_DEV(dev, &pdev->dev);

	pdata = netdev_priv(dev);
	dev->irq = irq;
	pdata->ioaddr = ioremap(res->start, res_size);
	अगर (!pdata->ioaddr) अणु
		retval = -ENOMEM;
		जाओ out_ioremap_fail;
	पूर्ण

	pdata->dev = dev;
	pdata->msg_enable = ((1 << debug) - 1);

	platक्रमm_set_drvdata(pdev, dev);

	retval = smsc911x_request_resources(pdev);
	अगर (retval)
		जाओ out_request_resources_fail;

	retval = smsc911x_enable_resources(pdev);
	अगर (retval)
		जाओ out_enable_resources_fail;

	अगर (pdata->ioaddr == शून्य) अणु
		SMSC_WARN(pdata, probe, "Error smsc911x base address invalid");
		retval = -ENOMEM;
		जाओ out_disable_resources;
	पूर्ण

	retval = smsc911x_probe_config(&pdata->config, &pdev->dev);
	अगर (retval && config) अणु
		/* copy config parameters across to pdata */
		स_नकल(&pdata->config, config, माप(pdata->config));
		retval = 0;
	पूर्ण

	अगर (retval) अणु
		SMSC_WARN(pdata, probe, "Error smsc911x config not found");
		जाओ out_disable_resources;
	पूर्ण

	/* assume standard, non-shअगरted, access to HW रेजिस्टरs */
	pdata->ops = &standard_smsc911x_ops;
	/* apply the right access अगर shअगरting is needed */
	अगर (pdata->config.shअगरt)
		pdata->ops = &shअगरted_smsc911x_ops;

	pm_runसमय_enable(&pdev->dev);
	pm_runसमय_get_sync(&pdev->dev);

	retval = smsc911x_init(dev);
	अगर (retval < 0)
		जाओ out_init_fail;

	netअगर_carrier_off(dev);

	retval = smsc911x_mii_init(pdev, dev);
	अगर (retval) अणु
		SMSC_WARN(pdata, probe, "Error %i initialising mii", retval);
		जाओ out_init_fail;
	पूर्ण

	retval = रेजिस्टर_netdev(dev);
	अगर (retval) अणु
		SMSC_WARN(pdata, probe, "Error %i registering device", retval);
		जाओ out_init_fail;
	पूर्ण अन्यथा अणु
		SMSC_TRACE(pdata, probe,
			   "Network interface: \"%s\"", dev->name);
	पूर्ण

	spin_lock_irq(&pdata->mac_lock);

	/* Check अगर mac address has been specअगरied when bringing पूर्णांकerface up */
	अगर (is_valid_ether_addr(dev->dev_addr)) अणु
		smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
		SMSC_TRACE(pdata, probe,
			   "MAC Address is specified by configuration");
	पूर्ण अन्यथा अगर (is_valid_ether_addr(pdata->config.mac)) अणु
		स_नकल(dev->dev_addr, pdata->config.mac, ETH_ALEN);
		SMSC_TRACE(pdata, probe,
			   "MAC Address specified by platform data");
	पूर्ण अन्यथा अणु
		/* Try पढ़ोing mac address from device. अगर EEPROM is present
		 * it will alपढ़ोy have been set */
		smsc_get_mac(dev);

		अगर (is_valid_ether_addr(dev->dev_addr)) अणु
			/* eeprom values are valid  so use them */
			SMSC_TRACE(pdata, probe,
				   "Mac Address is read from LAN911x EEPROM");
		पूर्ण अन्यथा अणु
			/* eeprom values are invalid, generate अक्रमom MAC */
			eth_hw_addr_अक्रमom(dev);
			smsc911x_set_hw_mac_address(pdata, dev->dev_addr);
			SMSC_TRACE(pdata, probe,
				   "MAC Address is set to eth_random_addr");
		पूर्ण
	पूर्ण

	spin_unlock_irq(&pdata->mac_lock);
	pm_runसमय_put(&pdev->dev);

	netdev_info(dev, "MAC Address: %pM\n", dev->dev_addr);

	वापस 0;

out_init_fail:
	pm_runसमय_put(&pdev->dev);
	pm_runसमय_disable(&pdev->dev);
out_disable_resources:
	(व्योम)smsc911x_disable_resources(pdev);
out_enable_resources_fail:
	smsc911x_मुक्त_resources(pdev);
out_request_resources_fail:
	iounmap(pdata->ioaddr);
out_ioremap_fail:
	मुक्त_netdev(dev);
out_release_io_1:
	release_mem_region(res->start, resource_size(res));
out_0:
	वापस retval;
पूर्ण

#अगर_घोषित CONFIG_PM
/* This implementation assumes the devices reमुख्यs घातered on its VDDVARIO
 * pins during suspend. */

/* TODO: implement मुक्तze/thaw callbacks क्रम hibernation.*/

अटल पूर्णांक smsc911x_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा smsc911x_data *pdata = netdev_priv(ndev);

	अगर (netअगर_running(ndev)) अणु
		netअगर_stop_queue(ndev);
		netअगर_device_detach(ndev);
	पूर्ण

	/* enable wake on LAN, energy detection and the बाह्यal PME
	 * संकेत. */
	smsc911x_reg_ग_लिखो(pdata, PMT_CTRL,
		PMT_CTRL_PM_MODE_D1_ | PMT_CTRL_WOL_EN_ |
		PMT_CTRL_ED_EN_ | PMT_CTRL_PME_EN_);

	pm_runसमय_disable(dev);
	pm_runसमय_set_suspended(dev);

	वापस 0;
पूर्ण

अटल पूर्णांक smsc911x_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा smsc911x_data *pdata = netdev_priv(ndev);
	अचिन्हित पूर्णांक to = 100;

	pm_runसमय_enable(dev);
	pm_runसमय_resume(dev);

	/* Note 3.11 from the datasheet:
	 * 	"When the LAN9220 is in a घातer saving state, a ग_लिखो of any
	 * 	 data to the BYTE_TEST रेजिस्टर will wake-up the device."
	 */
	smsc911x_reg_ग_लिखो(pdata, BYTE_TEST, 0);

	/* poll the READY bit in PMT_CTRL. Any other access to the device is
	 * क्रमbidden जबतक this bit isn't set. Try क्रम 100ms and वापस -EIO
	 * अगर it failed. */
	जबतक (!(smsc911x_reg_पढ़ो(pdata, PMT_CTRL) & PMT_CTRL_READY_) && --to)
		udelay(1000);

	अगर (to == 0)
		वापस -EIO;

	अगर (netअगर_running(ndev)) अणु
		netअगर_device_attach(ndev);
		netअगर_start_queue(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops smsc911x_pm_ops = अणु
	.suspend	= smsc911x_suspend,
	.resume		= smsc911x_resume,
पूर्ण;

#घोषणा SMSC911X_PM_OPS (&smsc911x_pm_ops)

#अन्यथा
#घोषणा SMSC911X_PM_OPS शून्य
#पूर्ण_अगर

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id smsc911x_dt_ids[] = अणु
	अणु .compatible = "smsc,lan9115", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, smsc911x_dt_ids);
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id smsc911x_acpi_match[] = अणु
	अणु "ARMH9118", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(acpi, smsc911x_acpi_match);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver smsc911x_driver = अणु
	.probe = smsc911x_drv_probe,
	.हटाओ = smsc911x_drv_हटाओ,
	.driver = अणु
		.name	= SMSC_CHIPNAME,
		.pm	= SMSC911X_PM_OPS,
		.of_match_table = of_match_ptr(smsc911x_dt_ids),
		.acpi_match_table = ACPI_PTR(smsc911x_acpi_match),
	पूर्ण,
पूर्ण;

/* Entry poपूर्णांक क्रम loading the module */
अटल पूर्णांक __init smsc911x_init_module(व्योम)
अणु
	SMSC_INITIALIZE();
	वापस platक्रमm_driver_रेजिस्टर(&smsc911x_driver);
पूर्ण

/* entry poपूर्णांक क्रम unloading the module */
अटल व्योम __निकास smsc911x_cleanup_module(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&smsc911x_driver);
पूर्ण

module_init(smsc911x_init_module);
module_निकास(smsc911x_cleanup_module);
