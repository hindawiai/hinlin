<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *      Davicom DM9000 Fast Ethernet driver क्रम Linux.
 * 	Copyright (C) 1997  Sten Wang
 *
 * (C) Copyright 1997-1998 DAVICOM Semiconductor,Inc. All Rights Reserved.
 *
 * Additional updates, Copyright:
 *	Ben Dooks <ben@simtec.co.uk>
 *	Sascha Hauer <s.hauer@pengutronix.de>
 */

#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/crc32.h>
#समावेश <linux/mii.h>
#समावेश <linux/of.h>
#समावेश <linux/of_net.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/irq.h>
#समावेश <linux/slab.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <यंत्र/delay.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>

#समावेश "dm9000.h"

/* Board/System/Debug inक्रमmation/definition ---------------- */

#घोषणा DM9000_PHY		0x40	/* PHY address 0x01 */

#घोषणा CARDNAME	"dm9000"

/*
 * Transmit समयout, शेष 5 seconds.
 */
अटल पूर्णांक watchकरोg = 5000;
module_param(watchकरोg, पूर्णांक, 0400);
MODULE_PARM_DESC(watchकरोg, "transmit timeout in milliseconds");

/*
 * Debug messages level
 */
अटल पूर्णांक debug;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "dm9000 debug level (0-6)");

/* DM9000 रेजिस्टर address locking.
 *
 * The DM9000 uses an address रेजिस्टर to control where data written
 * to the data रेजिस्टर goes. This means that the address रेजिस्टर
 * must be preserved over पूर्णांकerrupts or similar calls.
 *
 * During पूर्णांकerrupt and other critical calls, a spinlock is used to
 * protect the प्रणाली, but the calls themselves save the address
 * in the address रेजिस्टर in हाल they are पूर्णांकerrupting another
 * access to the device.
 *
 * For general accesses a lock is provided so that calls which are
 * allowed to sleep are serialised so that the address रेजिस्टर करोes
 * not need to be saved. This lock also serves to serialise access
 * to the EEPROM and PHY access रेजिस्टरs which are shared between
 * these two devices.
 */

/* The driver supports the original DM9000E, and now the two newer
 * devices, DM9000A and DM9000B.
 */

क्रमागत dm9000_type अणु
	TYPE_DM9000E,	/* original DM9000 */
	TYPE_DM9000A,
	TYPE_DM9000B
पूर्ण;

/* Structure/क्रमागत declaration ------------------------------- */
काष्ठा board_info अणु

	व्योम __iomem	*io_addr;	/* Register I/O base address */
	व्योम __iomem	*io_data;	/* Data I/O address */
	u16		 irq;		/* IRQ */

	u16		tx_pkt_cnt;
	u16		queue_pkt_len;
	u16		queue_start_addr;
	u16		queue_ip_summed;
	u16		dbug_cnt;
	u8		io_mode;		/* 0:word, 2:byte */
	u8		phy_addr;
	u8		imr_all;

	अचिन्हित पूर्णांक	flags;
	अचिन्हित पूर्णांक	in_समयout:1;
	अचिन्हित पूर्णांक	in_suspend:1;
	अचिन्हित पूर्णांक	wake_supported:1;

	क्रमागत dm9000_type type;

	व्योम (*inblk)(व्योम __iomem *port, व्योम *data, पूर्णांक length);
	व्योम (*outblk)(व्योम __iomem *port, व्योम *data, पूर्णांक length);
	व्योम (*dumpblk)(व्योम __iomem *port, पूर्णांक length);

	काष्ठा device	*dev;	     /* parent device */

	काष्ठा resource	*addr_res;   /* resources found */
	काष्ठा resource *data_res;
	काष्ठा resource	*addr_req;   /* resources requested */
	काष्ठा resource *data_req;

	पूर्णांक		 irq_wake;

	काष्ठा mutex	 addr_lock;	/* phy and eeprom access lock */

	काष्ठा delayed_work phy_poll;
	काष्ठा net_device  *ndev;

	spinlock_t	lock;

	काष्ठा mii_अगर_info mii;
	u32		msg_enable;
	u32		wake_state;

	पूर्णांक		ip_summed;

	काष्ठा regulator *घातer_supply;
पूर्ण;

/* debug code */

#घोषणा dm9000_dbg(db, lev, msg...) करो अणु		\
	अगर ((lev) < debug) अणु				\
		dev_dbg(db->dev, msg);			\
	पूर्ण						\
पूर्ण जबतक (0)

अटल अंतरभूत काष्ठा board_info *to_dm9000_board(काष्ठा net_device *dev)
अणु
	वापस netdev_priv(dev);
पूर्ण

/* DM9000 network board routine ---------------------------- */

/*
 *   Read a byte from I/O port
 */
अटल u8
ior(काष्ठा board_info *db, पूर्णांक reg)
अणु
	ग_लिखोb(reg, db->io_addr);
	वापस पढ़ोb(db->io_data);
पूर्ण

/*
 *   Write a byte to I/O port
 */

अटल व्योम
iow(काष्ठा board_info *db, पूर्णांक reg, पूर्णांक value)
अणु
	ग_लिखोb(reg, db->io_addr);
	ग_लिखोb(value, db->io_data);
पूर्ण

अटल व्योम
dm9000_reset(काष्ठा board_info *db)
अणु
	dev_dbg(db->dev, "resetting device\n");

	/* Reset DM9000, see DM9000 Application Notes V1.22 Jun 11, 2004 page 29
	 * The essential poपूर्णांक is that we have to करो a द्विगुन reset, and the
	 * inकाष्ठाion is to set LBK पूर्णांकo MAC पूर्णांकernal loopback mode.
	 */
	iow(db, DM9000_NCR, NCR_RST | NCR_MAC_LBK);
	udelay(100); /* Application note says at least 20 us */
	अगर (ior(db, DM9000_NCR) & 1)
		dev_err(db->dev, "dm9000 did not respond to first reset\n");

	iow(db, DM9000_NCR, 0);
	iow(db, DM9000_NCR, NCR_RST | NCR_MAC_LBK);
	udelay(100);
	अगर (ior(db, DM9000_NCR) & 1)
		dev_err(db->dev, "dm9000 did not respond to second reset\n");
पूर्ण

/* routines क्रम sending block to chip */

अटल व्योम dm9000_outblk_8bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ioग_लिखो8_rep(reg, data, count);
पूर्ण

अटल व्योम dm9000_outblk_16bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ioग_लिखो16_rep(reg, data, (count+1) >> 1);
पूर्ण

अटल व्योम dm9000_outblk_32bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ioग_लिखो32_rep(reg, data, (count+3) >> 2);
पूर्ण

/* input block from chip to memory */

अटल व्योम dm9000_inblk_8bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ioपढ़ो8_rep(reg, data, count);
पूर्ण


अटल व्योम dm9000_inblk_16bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ioपढ़ो16_rep(reg, data, (count+1) >> 1);
पूर्ण

अटल व्योम dm9000_inblk_32bit(व्योम __iomem *reg, व्योम *data, पूर्णांक count)
अणु
	ioपढ़ो32_rep(reg, data, (count+3) >> 2);
पूर्ण

/* dump block from chip to null */

अटल व्योम dm9000_dumpblk_8bit(व्योम __iomem *reg, पूर्णांक count)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < count; i++)
		पढ़ोb(reg);
पूर्ण

अटल व्योम dm9000_dumpblk_16bit(व्योम __iomem *reg, पूर्णांक count)
अणु
	पूर्णांक i;

	count = (count + 1) >> 1;

	क्रम (i = 0; i < count; i++)
		पढ़ोw(reg);
पूर्ण

अटल व्योम dm9000_dumpblk_32bit(व्योम __iomem *reg, पूर्णांक count)
अणु
	पूर्णांक i;

	count = (count + 3) >> 2;

	क्रम (i = 0; i < count; i++)
		पढ़ोl(reg);
पूर्ण

/*
 * Sleep, either by using msleep() or अगर we are suspending, then
 * use mdelay() to sleep.
 */
अटल व्योम dm9000_msleep(काष्ठा board_info *db, अचिन्हित पूर्णांक ms)
अणु
	अगर (db->in_suspend || db->in_समयout)
		mdelay(ms);
	अन्यथा
		msleep(ms);
पूर्ण

/* Read a word from phyxcer */
अटल पूर्णांक
dm9000_phy_पढ़ो(काष्ठा net_device *dev, पूर्णांक phy_reg_unused, पूर्णांक reg)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक reg_save;
	पूर्णांक ret;

	mutex_lock(&db->addr_lock);

	spin_lock_irqsave(&db->lock, flags);

	/* Save previous रेजिस्टर address */
	reg_save = पढ़ोb(db->io_addr);

	/* Fill the phyxcer रेजिस्टर पूर्णांकo REG_0C */
	iow(db, DM9000_EPAR, DM9000_PHY | reg);

	/* Issue phyxcer पढ़ो command */
	iow(db, DM9000_EPCR, EPCR_ERPRR | EPCR_EPOS);

	ग_लिखोb(reg_save, db->io_addr);
	spin_unlock_irqrestore(&db->lock, flags);

	dm9000_msleep(db, 1);		/* Wait पढ़ो complete */

	spin_lock_irqsave(&db->lock, flags);
	reg_save = पढ़ोb(db->io_addr);

	iow(db, DM9000_EPCR, 0x0);	/* Clear phyxcer पढ़ो command */

	/* The पढ़ो data keeps on REG_0D & REG_0E */
	ret = (ior(db, DM9000_EPDRH) << 8) | ior(db, DM9000_EPDRL);

	/* restore the previous address */
	ग_लिखोb(reg_save, db->io_addr);
	spin_unlock_irqrestore(&db->lock, flags);

	mutex_unlock(&db->addr_lock);

	dm9000_dbg(db, 5, "phy_read[%02x] -> %04x\n", reg, ret);
	वापस ret;
पूर्ण

/* Write a word to phyxcer */
अटल व्योम
dm9000_phy_ग_लिखो(काष्ठा net_device *dev,
		 पूर्णांक phyaddr_unused, पूर्णांक reg, पूर्णांक value)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ reg_save;

	dm9000_dbg(db, 5, "phy_write[%02x] = %04x\n", reg, value);
	अगर (!db->in_समयout)
		mutex_lock(&db->addr_lock);

	spin_lock_irqsave(&db->lock, flags);

	/* Save previous रेजिस्टर address */
	reg_save = पढ़ोb(db->io_addr);

	/* Fill the phyxcer रेजिस्टर पूर्णांकo REG_0C */
	iow(db, DM9000_EPAR, DM9000_PHY | reg);

	/* Fill the written data पूर्णांकo REG_0D & REG_0E */
	iow(db, DM9000_EPDRL, value);
	iow(db, DM9000_EPDRH, value >> 8);

	/* Issue phyxcer ग_लिखो command */
	iow(db, DM9000_EPCR, EPCR_EPOS | EPCR_ERPRW);

	ग_लिखोb(reg_save, db->io_addr);
	spin_unlock_irqrestore(&db->lock, flags);

	dm9000_msleep(db, 1);		/* Wait ग_लिखो complete */

	spin_lock_irqsave(&db->lock, flags);
	reg_save = पढ़ोb(db->io_addr);

	iow(db, DM9000_EPCR, 0x0);	/* Clear phyxcer ग_लिखो command */

	/* restore the previous address */
	ग_लिखोb(reg_save, db->io_addr);

	spin_unlock_irqrestore(&db->lock, flags);
	अगर (!db->in_समयout)
		mutex_unlock(&db->addr_lock);
पूर्ण

/* dm9000_set_io
 *
 * select the specअगरied set of io routines to use with the
 * device
 */

अटल व्योम dm9000_set_io(काष्ठा board_info *db, पूर्णांक byte_width)
अणु
	/* use the size of the data resource to work out what IO
	 * routines we want to use
	 */

	चयन (byte_width) अणु
	हाल 1:
		db->dumpblk = dm9000_dumpblk_8bit;
		db->outblk  = dm9000_outblk_8bit;
		db->inblk   = dm9000_inblk_8bit;
		अवरोध;


	हाल 3:
		dev_dbg(db->dev, ": 3 byte IO, falling back to 16bit\n");
		fallthrough;
	हाल 2:
		db->dumpblk = dm9000_dumpblk_16bit;
		db->outblk  = dm9000_outblk_16bit;
		db->inblk   = dm9000_inblk_16bit;
		अवरोध;

	हाल 4:
	शेष:
		db->dumpblk = dm9000_dumpblk_32bit;
		db->outblk  = dm9000_outblk_32bit;
		db->inblk   = dm9000_inblk_32bit;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम dm9000_schedule_poll(काष्ठा board_info *db)
अणु
	अगर (db->type == TYPE_DM9000E)
		schedule_delayed_work(&db->phy_poll, HZ * 2);
पूर्ण

अटल पूर्णांक dm9000_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *req, पूर्णांक cmd)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	वापस generic_mii_ioctl(&dm->mii, अगर_mii(req), cmd, शून्य);
पूर्ण

अटल अचिन्हित पूर्णांक
dm9000_पढ़ो_locked(काष्ठा board_info *db, पूर्णांक reg)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक ret;

	spin_lock_irqsave(&db->lock, flags);
	ret = ior(db, reg);
	spin_unlock_irqrestore(&db->lock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक dm9000_रुको_eeprom(काष्ठा board_info *db)
अणु
	अचिन्हित पूर्णांक status;
	पूर्णांक समयout = 8;	/* रुको max 8msec */

	/* The DM9000 data sheets say we should be able to
	 * poll the ERRE bit in EPCR to रुको क्रम the EEPROM
	 * operation. From testing several chips, this bit
	 * करोes not seem to work.
	 *
	 * We attempt to use the bit, but fall back to the
	 * समयout (which is why we करो not वापस an error
	 * on expiry) to say that the EEPROM operation has
	 * completed.
	 */

	जबतक (1) अणु
		status = dm9000_पढ़ो_locked(db, DM9000_EPCR);

		अगर ((status & EPCR_ERRE) == 0)
			अवरोध;

		msleep(1);

		अगर (समयout-- < 0) अणु
			dev_dbg(db->dev, "timeout waiting EEPROM\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 *  Read a word data from EEPROM
 */
अटल व्योम
dm9000_पढ़ो_eeprom(काष्ठा board_info *db, पूर्णांक offset, u8 *to)
अणु
	अचिन्हित दीर्घ flags;

	अगर (db->flags & DM9000_PLATF_NO_EEPROM) अणु
		to[0] = 0xff;
		to[1] = 0xff;
		वापस;
	पूर्ण

	mutex_lock(&db->addr_lock);

	spin_lock_irqsave(&db->lock, flags);

	iow(db, DM9000_EPAR, offset);
	iow(db, DM9000_EPCR, EPCR_ERPRR);

	spin_unlock_irqrestore(&db->lock, flags);

	dm9000_रुको_eeprom(db);

	/* delay क्रम at-least 150uS */
	msleep(1);

	spin_lock_irqsave(&db->lock, flags);

	iow(db, DM9000_EPCR, 0x0);

	to[0] = ior(db, DM9000_EPDRL);
	to[1] = ior(db, DM9000_EPDRH);

	spin_unlock_irqrestore(&db->lock, flags);

	mutex_unlock(&db->addr_lock);
पूर्ण

/*
 * Write a word data to SROM
 */
अटल व्योम
dm9000_ग_लिखो_eeprom(काष्ठा board_info *db, पूर्णांक offset, u8 *data)
अणु
	अचिन्हित दीर्घ flags;

	अगर (db->flags & DM9000_PLATF_NO_EEPROM)
		वापस;

	mutex_lock(&db->addr_lock);

	spin_lock_irqsave(&db->lock, flags);
	iow(db, DM9000_EPAR, offset);
	iow(db, DM9000_EPDRH, data[1]);
	iow(db, DM9000_EPDRL, data[0]);
	iow(db, DM9000_EPCR, EPCR_WEP | EPCR_ERPRW);
	spin_unlock_irqrestore(&db->lock, flags);

	dm9000_रुको_eeprom(db);

	mdelay(1);	/* रुको at least 150uS to clear */

	spin_lock_irqsave(&db->lock, flags);
	iow(db, DM9000_EPCR, 0);
	spin_unlock_irqrestore(&db->lock, flags);

	mutex_unlock(&db->addr_lock);
पूर्ण

/* ethtool ops */

अटल व्योम dm9000_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	strlcpy(info->driver, CARDNAME, माप(info->driver));
	strlcpy(info->bus_info, to_platक्रमm_device(dm->dev)->name,
		माप(info->bus_info));
पूर्ण

अटल u32 dm9000_get_msglevel(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	वापस dm->msg_enable;
पूर्ण

अटल व्योम dm9000_set_msglevel(काष्ठा net_device *dev, u32 value)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	dm->msg_enable = value;
पूर्ण

अटल पूर्णांक dm9000_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	mii_ethtool_get_link_ksettings(&dm->mii, cmd);
	वापस 0;
पूर्ण

अटल पूर्णांक dm9000_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	वापस mii_ethtool_set_link_ksettings(&dm->mii, cmd);
पूर्ण

अटल पूर्णांक dm9000_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);
	वापस mii_nway_restart(&dm->mii);
पूर्ण

अटल पूर्णांक dm9000_set_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);
	netdev_features_t changed = dev->features ^ features;
	अचिन्हित दीर्घ flags;

	अगर (!(changed & NETIF_F_RXCSUM))
		वापस 0;

	spin_lock_irqsave(&dm->lock, flags);
	iow(dm, DM9000_RCSR, (features & NETIF_F_RXCSUM) ? RCSR_CSUM : 0);
	spin_unlock_irqrestore(&dm->lock, flags);

	वापस 0;
पूर्ण

अटल u32 dm9000_get_link(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);
	u32 ret;

	अगर (dm->flags & DM9000_PLATF_EXT_PHY)
		ret = mii_link_ok(&dm->mii);
	अन्यथा
		ret = dm9000_पढ़ो_locked(dm, DM9000_NSR) & NSR_LINKST ? 1 : 0;

	वापस ret;
पूर्ण

#घोषणा DM_EEPROM_MAGIC		(0x444D394B)

अटल पूर्णांक dm9000_get_eeprom_len(काष्ठा net_device *dev)
अणु
	वापस 128;
पूर्ण

अटल पूर्णांक dm9000_get_eeprom(काष्ठा net_device *dev,
			     काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);
	पूर्णांक offset = ee->offset;
	पूर्णांक len = ee->len;
	पूर्णांक i;

	/* EEPROM access is aligned to two bytes */

	अगर ((len & 1) != 0 || (offset & 1) != 0)
		वापस -EINVAL;

	अगर (dm->flags & DM9000_PLATF_NO_EEPROM)
		वापस -ENOENT;

	ee->magic = DM_EEPROM_MAGIC;

	क्रम (i = 0; i < len; i += 2)
		dm9000_पढ़ो_eeprom(dm, (offset + i) / 2, data + i);

	वापस 0;
पूर्ण

अटल पूर्णांक dm9000_set_eeprom(काष्ठा net_device *dev,
			     काष्ठा ethtool_eeprom *ee, u8 *data)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);
	पूर्णांक offset = ee->offset;
	पूर्णांक len = ee->len;
	पूर्णांक करोne;

	/* EEPROM access is aligned to two bytes */

	अगर (dm->flags & DM9000_PLATF_NO_EEPROM)
		वापस -ENOENT;

	अगर (ee->magic != DM_EEPROM_MAGIC)
		वापस -EINVAL;

	जबतक (len > 0) अणु
		अगर (len & 1 || offset & 1) अणु
			पूर्णांक which = offset & 1;
			u8 पंचांगp[2];

			dm9000_पढ़ो_eeprom(dm, offset / 2, पंचांगp);
			पंचांगp[which] = *data;
			dm9000_ग_लिखो_eeprom(dm, offset / 2, पंचांगp);

			करोne = 1;
		पूर्ण अन्यथा अणु
			dm9000_ग_लिखो_eeprom(dm, offset / 2, data);
			करोne = 2;
		पूर्ण

		data += करोne;
		offset += करोne;
		len -= करोne;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dm9000_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *w)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	स_रखो(w, 0, माप(काष्ठा ethtool_wolinfo));

	/* note, we could probably support wake-phy too */
	w->supported = dm->wake_supported ? WAKE_MAGIC : 0;
	w->wolopts = dm->wake_state;
पूर्ण

अटल पूर्णांक dm9000_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *w)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);
	अचिन्हित दीर्घ flags;
	u32 opts = w->wolopts;
	u32 wcr = 0;

	अगर (!dm->wake_supported)
		वापस -EOPNOTSUPP;

	अगर (opts & ~WAKE_MAGIC)
		वापस -EINVAL;

	अगर (opts & WAKE_MAGIC)
		wcr |= WCR_MAGICEN;

	mutex_lock(&dm->addr_lock);

	spin_lock_irqsave(&dm->lock, flags);
	iow(dm, DM9000_WCR, wcr);
	spin_unlock_irqrestore(&dm->lock, flags);

	mutex_unlock(&dm->addr_lock);

	अगर (dm->wake_state != opts) अणु
		/* change in wol state, update IRQ state */

		अगर (!dm->wake_state)
			irq_set_irq_wake(dm->irq_wake, 1);
		अन्यथा अगर (dm->wake_state && !opts)
			irq_set_irq_wake(dm->irq_wake, 0);
	पूर्ण

	dm->wake_state = opts;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops dm9000_ethtool_ops = अणु
	.get_drvinfo		= dm9000_get_drvinfo,
	.get_msglevel		= dm9000_get_msglevel,
	.set_msglevel		= dm9000_set_msglevel,
	.nway_reset		= dm9000_nway_reset,
	.get_link		= dm9000_get_link,
	.get_wol		= dm9000_get_wol,
	.set_wol		= dm9000_set_wol,
	.get_eeprom_len		= dm9000_get_eeprom_len,
	.get_eeprom		= dm9000_get_eeprom,
	.set_eeprom		= dm9000_set_eeprom,
	.get_link_ksettings	= dm9000_get_link_ksettings,
	.set_link_ksettings	= dm9000_set_link_ksettings,
पूर्ण;

अटल व्योम dm9000_show_carrier(काष्ठा board_info *db,
				अचिन्हित carrier, अचिन्हित nsr)
अणु
	पूर्णांक lpa;
	काष्ठा net_device *ndev = db->ndev;
	काष्ठा mii_अगर_info *mii = &db->mii;
	अचिन्हित ncr = dm9000_पढ़ो_locked(db, DM9000_NCR);

	अगर (carrier) अणु
		lpa = mii->mdio_पढ़ो(mii->dev, mii->phy_id, MII_LPA);
		dev_info(db->dev,
			 "%s: link up, %dMbps, %s-duplex, lpa 0x%04X\n",
			 ndev->name, (nsr & NSR_SPEED) ? 10 : 100,
			 (ncr & NCR_FDX) ? "full" : "half", lpa);
	पूर्ण अन्यथा अणु
		dev_info(db->dev, "%s: link down\n", ndev->name);
	पूर्ण
पूर्ण

अटल व्योम
dm9000_poll_work(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा delayed_work *dw = to_delayed_work(w);
	काष्ठा board_info *db = container_of(dw, काष्ठा board_info, phy_poll);
	काष्ठा net_device *ndev = db->ndev;

	अगर (db->flags & DM9000_PLATF_SIMPLE_PHY &&
	    !(db->flags & DM9000_PLATF_EXT_PHY)) अणु
		अचिन्हित nsr = dm9000_पढ़ो_locked(db, DM9000_NSR);
		अचिन्हित old_carrier = netअगर_carrier_ok(ndev) ? 1 : 0;
		अचिन्हित new_carrier;

		new_carrier = (nsr & NSR_LINKST) ? 1 : 0;

		अगर (old_carrier != new_carrier) अणु
			अगर (netअगर_msg_link(db))
				dm9000_show_carrier(db, new_carrier, nsr);

			अगर (!new_carrier)
				netअगर_carrier_off(ndev);
			अन्यथा
				netअगर_carrier_on(ndev);
		पूर्ण
	पूर्ण अन्यथा
		mii_check_media(&db->mii, netअगर_msg_link(db), 0);

	अगर (netअगर_running(ndev))
		dm9000_schedule_poll(db);
पूर्ण

/* dm9000_release_board
 *
 * release a board, and any mapped resources
 */

अटल व्योम
dm9000_release_board(काष्ठा platक्रमm_device *pdev, काष्ठा board_info *db)
अणु
	/* unmap our resources */

	iounmap(db->io_addr);
	iounmap(db->io_data);

	/* release the resources */

	अगर (db->data_req)
		release_resource(db->data_req);
	kमुक्त(db->data_req);

	अगर (db->addr_req)
		release_resource(db->addr_req);
	kमुक्त(db->addr_req);
पूर्ण

अटल अचिन्हित अक्षर dm9000_type_to_अक्षर(क्रमागत dm9000_type type)
अणु
	चयन (type) अणु
	हाल TYPE_DM9000E: वापस 'e';
	हाल TYPE_DM9000A: वापस 'a';
	हाल TYPE_DM9000B: वापस 'b';
	पूर्ण

	वापस '?';
पूर्ण

/*
 *  Set DM9000 multicast address
 */
अटल व्योम
dm9000_hash_table_unlocked(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i, oft;
	u32 hash_val;
	u16 hash_table[4] = अणु 0, 0, 0, 0x8000 पूर्ण; /* broadcast address */
	u8 rcr = RCR_DIS_LONG | RCR_DIS_CRC | RCR_RXEN;

	dm9000_dbg(db, 1, "entering %s\n", __func__);

	क्रम (i = 0, oft = DM9000_PAR; i < 6; i++, oft++)
		iow(db, oft, dev->dev_addr[i]);

	अगर (dev->flags & IFF_PROMISC)
		rcr |= RCR_PRMSC;

	अगर (dev->flags & IFF_ALLMULTI)
		rcr |= RCR_ALL;

	/* the multicast address in Hash Table : 64 bits */
	netdev_क्रम_each_mc_addr(ha, dev) अणु
		hash_val = ether_crc_le(6, ha->addr) & 0x3f;
		hash_table[hash_val / 16] |= (u16) 1 << (hash_val % 16);
	पूर्ण

	/* Write the hash table to MAC MD table */
	क्रम (i = 0, oft = DM9000_MAR; i < 4; i++) अणु
		iow(db, oft++, hash_table[i]);
		iow(db, oft++, hash_table[i] >> 8);
	पूर्ण

	iow(db, DM9000_RCR, rcr);
पूर्ण

अटल व्योम
dm9000_hash_table(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&db->lock, flags);
	dm9000_hash_table_unlocked(dev);
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण

अटल व्योम
dm9000_mask_पूर्णांकerrupts(काष्ठा board_info *db)
अणु
	iow(db, DM9000_IMR, IMR_PAR);
पूर्ण

अटल व्योम
dm9000_unmask_पूर्णांकerrupts(काष्ठा board_info *db)
अणु
	iow(db, DM9000_IMR, db->imr_all);
पूर्ण

/*
 * Initialize dm9000 board
 */
अटल व्योम
dm9000_init_dm9000(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	अचिन्हित पूर्णांक imr;
	अचिन्हित पूर्णांक ncr;

	dm9000_dbg(db, 1, "entering %s\n", __func__);

	dm9000_reset(db);
	dm9000_mask_पूर्णांकerrupts(db);

	/* I/O mode */
	db->io_mode = ior(db, DM9000_ISR) >> 6;	/* ISR bit7:6 keeps I/O mode */

	/* Checksum mode */
	अगर (dev->hw_features & NETIF_F_RXCSUM)
		iow(db, DM9000_RCSR,
			(dev->features & NETIF_F_RXCSUM) ? RCSR_CSUM : 0);

	iow(db, DM9000_GPCR, GPCR_GEP_CNTL);	/* Let GPIO0 output */
	iow(db, DM9000_GPR, 0);

	/* If we are dealing with DM9000B, some extra steps are required: a
	 * manual phy reset, and setting init params.
	 */
	अगर (db->type == TYPE_DM9000B) अणु
		dm9000_phy_ग_लिखो(dev, 0, MII_BMCR, BMCR_RESET);
		dm9000_phy_ग_लिखो(dev, 0, MII_DM_DSPCR, DSPCR_INIT_PARAM);
	पूर्ण

	ncr = (db->flags & DM9000_PLATF_EXT_PHY) ? NCR_EXT_PHY : 0;

	/* अगर wol is needed, then always set NCR_WAKEEN otherwise we end
	 * up dumping the wake events अगर we disable this. There is alपढ़ोy
	 * a wake-mask in DM9000_WCR */
	अगर (db->wake_supported)
		ncr |= NCR_WAKEEN;

	iow(db, DM9000_NCR, ncr);

	/* Program operating रेजिस्टर */
	iow(db, DM9000_TCR, 0);	        /* TX Polling clear */
	iow(db, DM9000_BPTR, 0x3f);	/* Less 3Kb, 200us */
	iow(db, DM9000_FCR, 0xff);	/* Flow Control */
	iow(db, DM9000_SMCR, 0);        /* Special Mode */
	/* clear TX status */
	iow(db, DM9000_NSR, NSR_WAKEST | NSR_TX2END | NSR_TX1END);
	iow(db, DM9000_ISR, ISR_CLR_STATUS); /* Clear पूर्णांकerrupt status */

	/* Set address filter table */
	dm9000_hash_table_unlocked(dev);

	imr = IMR_PAR | IMR_PTM | IMR_PRM;
	अगर (db->type != TYPE_DM9000E)
		imr |= IMR_LNKCHNG;

	db->imr_all = imr;

	/* Init Driver variable */
	db->tx_pkt_cnt = 0;
	db->queue_pkt_len = 0;
	netअगर_trans_update(dev);
पूर्ण

/* Our watchकरोg समयd out. Called by the networking layer */
अटल व्योम dm9000_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	u8 reg_save;
	अचिन्हित दीर्घ flags;

	/* Save previous रेजिस्टर address */
	spin_lock_irqsave(&db->lock, flags);
	db->in_समयout = 1;
	reg_save = पढ़ोb(db->io_addr);

	netअगर_stop_queue(dev);
	dm9000_init_dm9000(dev);
	dm9000_unmask_पूर्णांकerrupts(db);
	/* We can accept TX packets again */
	netअगर_trans_update(dev); /* prevent tx समयout */
	netअगर_wake_queue(dev);

	/* Restore previous रेजिस्टर address */
	ग_लिखोb(reg_save, db->io_addr);
	db->in_समयout = 0;
	spin_unlock_irqrestore(&db->lock, flags);
पूर्ण

अटल व्योम dm9000_send_packet(काष्ठा net_device *dev,
			       पूर्णांक ip_summed,
			       u16 pkt_len)
अणु
	काष्ठा board_info *dm = to_dm9000_board(dev);

	/* The DM9000 is not smart enough to leave fragmented packets alone. */
	अगर (dm->ip_summed != ip_summed) अणु
		अगर (ip_summed == CHECKSUM_NONE)
			iow(dm, DM9000_TCCR, 0);
		अन्यथा
			iow(dm, DM9000_TCCR, TCCR_IP | TCCR_UDP | TCCR_TCP);
		dm->ip_summed = ip_summed;
	पूर्ण

	/* Set TX length to DM9000 */
	iow(dm, DM9000_TXPLL, pkt_len);
	iow(dm, DM9000_TXPLH, pkt_len >> 8);

	/* Issue TX polling command */
	iow(dm, DM9000_TCR, TCR_TXREQ);	/* Cleared after TX complete */
पूर्ण

/*
 *  Hardware start transmission.
 *  Send a packet to media from the upper layer.
 */
अटल पूर्णांक
dm9000_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा board_info *db = netdev_priv(dev);

	dm9000_dbg(db, 3, "%s:\n", __func__);

	अगर (db->tx_pkt_cnt > 1)
		वापस NETDEV_TX_BUSY;

	spin_lock_irqsave(&db->lock, flags);

	/* Move data to DM9000 TX RAM */
	ग_लिखोb(DM9000_MWCMD, db->io_addr);

	(db->outblk)(db->io_data, skb->data, skb->len);
	dev->stats.tx_bytes += skb->len;

	db->tx_pkt_cnt++;
	/* TX control: First packet immediately send, second packet queue */
	अगर (db->tx_pkt_cnt == 1) अणु
		dm9000_send_packet(dev, skb->ip_summed, skb->len);
	पूर्ण अन्यथा अणु
		/* Second packet */
		db->queue_pkt_len = skb->len;
		db->queue_ip_summed = skb->ip_summed;
		netअगर_stop_queue(dev);
	पूर्ण

	spin_unlock_irqrestore(&db->lock, flags);

	/* मुक्त this SKB */
	dev_consume_skb_any(skb);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * DM9000 पूर्णांकerrupt handler
 * receive the packet to upper layer, मुक्त the transmitted packet
 */

अटल व्योम dm9000_tx_करोne(काष्ठा net_device *dev, काष्ठा board_info *db)
अणु
	पूर्णांक tx_status = ior(db, DM9000_NSR);	/* Got TX status */

	अगर (tx_status & (NSR_TX2END | NSR_TX1END)) अणु
		/* One packet sent complete */
		db->tx_pkt_cnt--;
		dev->stats.tx_packets++;

		अगर (netअगर_msg_tx_करोne(db))
			dev_dbg(db->dev, "tx done, NSR %02x\n", tx_status);

		/* Queue packet check & send */
		अगर (db->tx_pkt_cnt > 0)
			dm9000_send_packet(dev, db->queue_ip_summed,
					   db->queue_pkt_len);
		netअगर_wake_queue(dev);
	पूर्ण
पूर्ण

काष्ठा dm9000_rxhdr अणु
	u8	RxPktReady;
	u8	RxStatus;
	__le16	RxLen;
पूर्ण __packed;

/*
 *  Received a packet and pass to upper layer
 */
अटल व्योम
dm9000_rx(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	काष्ठा dm9000_rxhdr rxhdr;
	काष्ठा sk_buff *skb;
	u8 rxbyte, *rdptr;
	bool GoodPacket;
	पूर्णांक RxLen;

	/* Check packet पढ़ोy or not */
	करो अणु
		ior(db, DM9000_MRCMDX);	/* Dummy पढ़ो */

		/* Get most updated data */
		rxbyte = पढ़ोb(db->io_data);

		/* Status check: this byte must be 0 or 1 */
		अगर (rxbyte & DM9000_PKT_ERR) अणु
			dev_warn(db->dev, "status check fail: %d\n", rxbyte);
			iow(db, DM9000_RCR, 0x00);	/* Stop Device */
			वापस;
		पूर्ण

		अगर (!(rxbyte & DM9000_PKT_RDY))
			वापस;

		/* A packet पढ़ोy now  & Get status/length */
		GoodPacket = true;
		ग_लिखोb(DM9000_MRCMD, db->io_addr);

		(db->inblk)(db->io_data, &rxhdr, माप(rxhdr));

		RxLen = le16_to_cpu(rxhdr.RxLen);

		अगर (netअगर_msg_rx_status(db))
			dev_dbg(db->dev, "RX: status %02x, length %04x\n",
				rxhdr.RxStatus, RxLen);

		/* Packet Status check */
		अगर (RxLen < 0x40) अणु
			GoodPacket = false;
			अगर (netअगर_msg_rx_err(db))
				dev_dbg(db->dev, "RX: Bad Packet (runt)\n");
		पूर्ण

		अगर (RxLen > DM9000_PKT_MAX) अणु
			dev_dbg(db->dev, "RST: RX Len:%x\n", RxLen);
		पूर्ण

		/* rxhdr.RxStatus is identical to RSR रेजिस्टर. */
		अगर (rxhdr.RxStatus & (RSR_FOE | RSR_CE | RSR_AE |
				      RSR_PLE | RSR_RWTO |
				      RSR_LCS | RSR_RF)) अणु
			GoodPacket = false;
			अगर (rxhdr.RxStatus & RSR_FOE) अणु
				अगर (netअगर_msg_rx_err(db))
					dev_dbg(db->dev, "fifo error\n");
				dev->stats.rx_fअगरo_errors++;
			पूर्ण
			अगर (rxhdr.RxStatus & RSR_CE) अणु
				अगर (netअगर_msg_rx_err(db))
					dev_dbg(db->dev, "crc error\n");
				dev->stats.rx_crc_errors++;
			पूर्ण
			अगर (rxhdr.RxStatus & RSR_RF) अणु
				अगर (netअगर_msg_rx_err(db))
					dev_dbg(db->dev, "length error\n");
				dev->stats.rx_length_errors++;
			पूर्ण
		पूर्ण

		/* Move data from DM9000 */
		अगर (GoodPacket &&
		    ((skb = netdev_alloc_skb(dev, RxLen + 4)) != शून्य)) अणु
			skb_reserve(skb, 2);
			rdptr = skb_put(skb, RxLen - 4);

			/* Read received packet from RX SRAM */

			(db->inblk)(db->io_data, rdptr, RxLen);
			dev->stats.rx_bytes += RxLen;

			/* Pass to upper layer */
			skb->protocol = eth_type_trans(skb, dev);
			अगर (dev->features & NETIF_F_RXCSUM) अणु
				अगर ((((rxbyte & 0x1c) << 3) & rxbyte) == 0)
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				अन्यथा
					skb_checksum_none_निश्चित(skb);
			पूर्ण
			netअगर_rx(skb);
			dev->stats.rx_packets++;

		पूर्ण अन्यथा अणु
			/* need to dump the packet's data */

			(db->dumpblk)(db->io_data, RxLen);
		पूर्ण
	पूर्ण जबतक (rxbyte & DM9000_PKT_RDY);
पूर्ण

अटल irqवापस_t dm9000_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा board_info *db = netdev_priv(dev);
	पूर्णांक पूर्णांक_status;
	अचिन्हित दीर्घ flags;
	u8 reg_save;

	dm9000_dbg(db, 3, "entering %s\n", __func__);

	/* A real पूर्णांकerrupt coming */

	/* holders of db->lock must always block IRQs */
	spin_lock_irqsave(&db->lock, flags);

	/* Save previous रेजिस्टर address */
	reg_save = पढ़ोb(db->io_addr);

	dm9000_mask_पूर्णांकerrupts(db);
	/* Got DM9000 पूर्णांकerrupt status */
	पूर्णांक_status = ior(db, DM9000_ISR);	/* Got ISR */
	iow(db, DM9000_ISR, पूर्णांक_status);	/* Clear ISR status */

	अगर (netअगर_msg_पूर्णांकr(db))
		dev_dbg(db->dev, "interrupt status %02x\n", पूर्णांक_status);

	/* Received the coming packet */
	अगर (पूर्णांक_status & ISR_PRS)
		dm9000_rx(dev);

	/* Transmit Interrupt check */
	अगर (पूर्णांक_status & ISR_PTS)
		dm9000_tx_करोne(dev, db);

	अगर (db->type != TYPE_DM9000E) अणु
		अगर (पूर्णांक_status & ISR_LNKCHNG) अणु
			/* fire a link-change request */
			schedule_delayed_work(&db->phy_poll, 1);
		पूर्ण
	पूर्ण

	dm9000_unmask_पूर्णांकerrupts(db);
	/* Restore previous रेजिस्टर address */
	ग_लिखोb(reg_save, db->io_addr);

	spin_unlock_irqrestore(&db->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t dm9000_wol_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा board_info *db = netdev_priv(dev);
	अचिन्हित दीर्घ flags;
	अचिन्हित nsr, wcr;

	spin_lock_irqsave(&db->lock, flags);

	nsr = ior(db, DM9000_NSR);
	wcr = ior(db, DM9000_WCR);

	dev_dbg(db->dev, "%s: NSR=0x%02x, WCR=0x%02x\n", __func__, nsr, wcr);

	अगर (nsr & NSR_WAKEST) अणु
		/* clear, so we can aव्योम */
		iow(db, DM9000_NSR, NSR_WAKEST);

		अगर (wcr & WCR_LINKST)
			dev_info(db->dev, "wake by link status change\n");
		अगर (wcr & WCR_SAMPLEST)
			dev_info(db->dev, "wake by sample packet\n");
		अगर (wcr & WCR_MAGICST)
			dev_info(db->dev, "wake by magic packet\n");
		अगर (!(wcr & (WCR_LINKST | WCR_SAMPLEST | WCR_MAGICST)))
			dev_err(db->dev, "wake signalled with no reason? "
				"NSR=0x%02x, WSR=0x%02x\n", nsr, wcr);
	पूर्ण

	spin_unlock_irqrestore(&db->lock, flags);

	वापस (nsr & NSR_WAKEST) ? IRQ_HANDLED : IRQ_NONE;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 *Used by netconsole
 */
अटल व्योम dm9000_poll_controller(काष्ठा net_device *dev)
अणु
	disable_irq(dev->irq);
	dm9000_पूर्णांकerrupt(dev->irq, dev);
	enable_irq(dev->irq);
पूर्ण
#पूर्ण_अगर

/*
 *  Open the पूर्णांकerface.
 *  The पूर्णांकerface is खोलोed whenever "ifconfig" actives it.
 */
अटल पूर्णांक
dm9000_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *db = netdev_priv(dev);
	अचिन्हित पूर्णांक irq_flags = irq_get_trigger_type(dev->irq);

	अगर (netअगर_msg_अगरup(db))
		dev_dbg(db->dev, "enabling %s\n", dev->name);

	/* If there is no IRQ type specअगरied, tell the user that this is a
	 * problem
	 */
	अगर (irq_flags == IRQF_TRIGGER_NONE)
		dev_warn(db->dev, "WARNING: no IRQ resource flags set.\n");

	irq_flags |= IRQF_SHARED;

	/* GPIO0 on pre-activate PHY, Reg 1F is not set by reset */
	iow(db, DM9000_GPR, 0);	/* REG_1F bit0 activate phyxcer */
	mdelay(1); /* delay needs by DM9000B */

	/* Initialize DM9000 board */
	dm9000_init_dm9000(dev);

	अगर (request_irq(dev->irq, dm9000_पूर्णांकerrupt, irq_flags, dev->name, dev))
		वापस -EAGAIN;
	/* Now that we have an पूर्णांकerrupt handler hooked up we can unmask
	 * our पूर्णांकerrupts
	 */
	dm9000_unmask_पूर्णांकerrupts(db);

	/* Init driver variable */
	db->dbug_cnt = 0;

	mii_check_media(&db->mii, netअगर_msg_link(db), 1);
	netअगर_start_queue(dev);

	/* Poll initial link status */
	schedule_delayed_work(&db->phy_poll, 1);

	वापस 0;
पूर्ण

अटल व्योम
dm9000_shutकरोwn(काष्ठा net_device *dev)
अणु
	काष्ठा board_info *db = netdev_priv(dev);

	/* RESET device */
	dm9000_phy_ग_लिखो(dev, 0, MII_BMCR, BMCR_RESET);	/* PHY RESET */
	iow(db, DM9000_GPR, 0x01);	/* Power-Down PHY */
	dm9000_mask_पूर्णांकerrupts(db);
	iow(db, DM9000_RCR, 0x00);	/* Disable RX */
पूर्ण

/*
 * Stop the पूर्णांकerface.
 * The पूर्णांकerface is stopped when it is brought.
 */
अटल पूर्णांक
dm9000_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा board_info *db = netdev_priv(ndev);

	अगर (netअगर_msg_अगरकरोwn(db))
		dev_dbg(db->dev, "shutting down %s\n", ndev->name);

	cancel_delayed_work_sync(&db->phy_poll);

	netअगर_stop_queue(ndev);
	netअगर_carrier_off(ndev);

	/* मुक्त पूर्णांकerrupt */
	मुक्त_irq(ndev->irq, ndev);

	dm9000_shutकरोwn(ndev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops dm9000_netdev_ops = अणु
	.nकरो_खोलो		= dm9000_खोलो,
	.nकरो_stop		= dm9000_stop,
	.nकरो_start_xmit		= dm9000_start_xmit,
	.nकरो_tx_समयout		= dm9000_समयout,
	.nकरो_set_rx_mode	= dm9000_hash_table,
	.nकरो_करो_ioctl		= dm9000_ioctl,
	.nकरो_set_features	= dm9000_set_features,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= eth_mac_addr,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= dm9000_poll_controller,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा dm9000_plat_data *dm9000_parse_dt(काष्ठा device *dev)
अणु
	काष्ठा dm9000_plat_data *pdata;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_OF) || !np)
		वापस ERR_PTR(-ENXIO);

	pdata = devm_kzalloc(dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस ERR_PTR(-ENOMEM);

	अगर (of_find_property(np, "davicom,ext-phy", शून्य))
		pdata->flags |= DM9000_PLATF_EXT_PHY;
	अगर (of_find_property(np, "davicom,no-eeprom", शून्य))
		pdata->flags |= DM9000_PLATF_NO_EEPROM;

	ret = of_get_mac_address(np, pdata->dev_addr);
	अगर (ret == -EPROBE_DEFER)
		वापस ERR_PTR(ret);

	वापस pdata;
पूर्ण

/*
 * Search DM9000 board, allocate space and रेजिस्टर it
 */
अटल पूर्णांक
dm9000_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dm9000_plat_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा board_info *db;	/* Poपूर्णांक a board inक्रमmation काष्ठाure */
	काष्ठा net_device *ndev;
	काष्ठा device *dev = &pdev->dev;
	स्थिर अचिन्हित अक्षर *mac_src;
	पूर्णांक ret = 0;
	पूर्णांक iosize;
	पूर्णांक i;
	u32 id_val;
	पूर्णांक reset_gpios;
	क्रमागत of_gpio_flags flags;
	काष्ठा regulator *घातer;
	bool inv_mac_addr = false;

	घातer = devm_regulator_get(dev, "vcc");
	अगर (IS_ERR(घातer)) अणु
		अगर (PTR_ERR(घातer) == -EPROBE_DEFER)
			वापस -EPROBE_DEFER;
		dev_dbg(dev, "no regulator provided\n");
	पूर्ण अन्यथा अणु
		ret = regulator_enable(घातer);
		अगर (ret != 0) अणु
			dev_err(dev,
				"Failed to enable power regulator: %d\n", ret);
			वापस ret;
		पूर्ण
		dev_dbg(dev, "regulator enabled\n");
	पूर्ण

	reset_gpios = of_get_named_gpio_flags(dev->of_node, "reset-gpios", 0,
					      &flags);
	अगर (gpio_is_valid(reset_gpios)) अणु
		ret = devm_gpio_request_one(dev, reset_gpios, flags,
					    "dm9000_reset");
		अगर (ret) अणु
			dev_err(dev, "failed to request reset gpio %d: %d\n",
				reset_gpios, ret);
			जाओ out_regulator_disable;
		पूर्ण

		/* According to manual PWRST# Low Period Min 1ms */
		msleep(2);
		gpio_set_value(reset_gpios, 1);
		/* Needs 3ms to पढ़ो eeprom when PWRST is deनिश्चितed */
		msleep(4);
	पूर्ण

	अगर (!pdata) अणु
		pdata = dm9000_parse_dt(&pdev->dev);
		अगर (IS_ERR(pdata)) अणु
			ret = PTR_ERR(pdata);
			जाओ out_regulator_disable;
		पूर्ण
	पूर्ण

	/* Init network device */
	ndev = alloc_etherdev(माप(काष्ठा board_info));
	अगर (!ndev) अणु
		ret = -ENOMEM;
		जाओ out_regulator_disable;
	पूर्ण

	SET_NETDEV_DEV(ndev, &pdev->dev);

	dev_dbg(&pdev->dev, "dm9000_probe()\n");

	/* setup board info काष्ठाure */
	db = netdev_priv(ndev);

	db->dev = &pdev->dev;
	db->ndev = ndev;
	अगर (!IS_ERR(घातer))
		db->घातer_supply = घातer;

	spin_lock_init(&db->lock);
	mutex_init(&db->addr_lock);

	INIT_DELAYED_WORK(&db->phy_poll, dm9000_poll_work);

	db->addr_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	db->data_res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);

	अगर (!db->addr_res || !db->data_res) अणु
		dev_err(db->dev, "insufficient resources addr=%p data=%p\n",
			db->addr_res, db->data_res);
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	ndev->irq = platक्रमm_get_irq(pdev, 0);
	अगर (ndev->irq < 0) अणु
		ret = ndev->irq;
		जाओ out;
	पूर्ण

	db->irq_wake = platक्रमm_get_irq_optional(pdev, 1);
	अगर (db->irq_wake >= 0) अणु
		dev_dbg(db->dev, "wakeup irq %d\n", db->irq_wake);

		ret = request_irq(db->irq_wake, dm9000_wol_पूर्णांकerrupt,
				  IRQF_SHARED, dev_name(db->dev), ndev);
		अगर (ret) अणु
			dev_err(db->dev, "cannot get wakeup irq (%d)\n", ret);
		पूर्ण अन्यथा अणु

			/* test to see अगर irq is really wakeup capable */
			ret = irq_set_irq_wake(db->irq_wake, 1);
			अगर (ret) अणु
				dev_err(db->dev, "irq %d cannot set wakeup (%d)\n",
					db->irq_wake, ret);
			पूर्ण अन्यथा अणु
				irq_set_irq_wake(db->irq_wake, 0);
				db->wake_supported = 1;
			पूर्ण
		पूर्ण
	पूर्ण

	iosize = resource_size(db->addr_res);
	db->addr_req = request_mem_region(db->addr_res->start, iosize,
					  pdev->name);

	अगर (db->addr_req == शून्य) अणु
		dev_err(db->dev, "cannot claim address reg area\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	db->io_addr = ioremap(db->addr_res->start, iosize);

	अगर (db->io_addr == शून्य) अणु
		dev_err(db->dev, "failed to ioremap address reg\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	iosize = resource_size(db->data_res);
	db->data_req = request_mem_region(db->data_res->start, iosize,
					  pdev->name);

	अगर (db->data_req == शून्य) अणु
		dev_err(db->dev, "cannot claim data reg area\n");
		ret = -EIO;
		जाओ out;
	पूर्ण

	db->io_data = ioremap(db->data_res->start, iosize);

	अगर (db->io_data == शून्य) अणु
		dev_err(db->dev, "failed to ioremap data reg\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	/* fill in parameters क्रम net-dev काष्ठाure */
	ndev->base_addr = (अचिन्हित दीर्घ)db->io_addr;

	/* ensure at least we have a शेष set of IO routines */
	dm9000_set_io(db, iosize);

	/* check to see अगर anything is being over-ridden */
	अगर (pdata != शून्य) अणु
		/* check to see अगर the driver wants to over-ride the
		 * शेष IO width */

		अगर (pdata->flags & DM9000_PLATF_8BITONLY)
			dm9000_set_io(db, 1);

		अगर (pdata->flags & DM9000_PLATF_16BITONLY)
			dm9000_set_io(db, 2);

		अगर (pdata->flags & DM9000_PLATF_32BITONLY)
			dm9000_set_io(db, 4);

		/* check to see अगर there are any IO routine
		 * over-rides */

		अगर (pdata->inblk != शून्य)
			db->inblk = pdata->inblk;

		अगर (pdata->outblk != शून्य)
			db->outblk = pdata->outblk;

		अगर (pdata->dumpblk != शून्य)
			db->dumpblk = pdata->dumpblk;

		db->flags = pdata->flags;
	पूर्ण

#अगर_घोषित CONFIG_DM9000_FORCE_SIMPLE_PHY_POLL
	db->flags |= DM9000_PLATF_SIMPLE_PHY;
#पूर्ण_अगर

	dm9000_reset(db);

	/* try multiple बार, DM9000 someबार माला_लो the पढ़ो wrong */
	क्रम (i = 0; i < 8; i++) अणु
		id_val  = ior(db, DM9000_VIDL);
		id_val |= (u32)ior(db, DM9000_VIDH) << 8;
		id_val |= (u32)ior(db, DM9000_PIDL) << 16;
		id_val |= (u32)ior(db, DM9000_PIDH) << 24;

		अगर (id_val == DM9000_ID)
			अवरोध;
		dev_err(db->dev, "read wrong id 0x%08x\n", id_val);
	पूर्ण

	अगर (id_val != DM9000_ID) अणु
		dev_err(db->dev, "wrong id: 0x%08x\n", id_val);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Identअगरy what type of DM9000 we are working on */

	id_val = ior(db, DM9000_CHIPR);
	dev_dbg(db->dev, "dm9000 revision 0x%02x\n", id_val);

	चयन (id_val) अणु
	हाल CHIPR_DM9000A:
		db->type = TYPE_DM9000A;
		अवरोध;
	हाल CHIPR_DM9000B:
		db->type = TYPE_DM9000B;
		अवरोध;
	शेष:
		dev_dbg(db->dev, "ID %02x => defaulting to DM9000E\n", id_val);
		db->type = TYPE_DM9000E;
	पूर्ण

	/* dm9000a/b are capable of hardware checksum offload */
	अगर (db->type == TYPE_DM9000A || db->type == TYPE_DM9000B) अणु
		ndev->hw_features = NETIF_F_RXCSUM | NETIF_F_IP_CSUM;
		ndev->features |= ndev->hw_features;
	पूर्ण

	/* from this poपूर्णांक we assume that we have found a DM9000 */

	ndev->netdev_ops	= &dm9000_netdev_ops;
	ndev->watchकरोg_समयo	= msecs_to_jअगरfies(watchकरोg);
	ndev->ethtool_ops	= &dm9000_ethtool_ops;

	db->msg_enable       = NETIF_MSG_LINK;
	db->mii.phy_id_mask  = 0x1f;
	db->mii.reg_num_mask = 0x1f;
	db->mii.क्रमce_media  = 0;
	db->mii.full_duplex  = 0;
	db->mii.dev	     = ndev;
	db->mii.mdio_पढ़ो    = dm9000_phy_पढ़ो;
	db->mii.mdio_ग_लिखो   = dm9000_phy_ग_लिखो;

	mac_src = "eeprom";

	/* try पढ़ोing the node address from the attached EEPROM */
	क्रम (i = 0; i < 6; i += 2)
		dm9000_पढ़ो_eeprom(db, i / 2, ndev->dev_addr+i);

	अगर (!is_valid_ether_addr(ndev->dev_addr) && pdata != शून्य) अणु
		mac_src = "platform data";
		स_नकल(ndev->dev_addr, pdata->dev_addr, ETH_ALEN);
	पूर्ण

	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		/* try पढ़ोing from mac */

		mac_src = "chip";
		क्रम (i = 0; i < 6; i++)
			ndev->dev_addr[i] = ior(db, i+DM9000_PAR);
	पूर्ण

	अगर (!is_valid_ether_addr(ndev->dev_addr)) अणु
		inv_mac_addr = true;
		eth_hw_addr_अक्रमom(ndev);
		mac_src = "random";
	पूर्ण


	platक्रमm_set_drvdata(pdev, ndev);
	ret = रेजिस्टर_netdev(ndev);

	अगर (ret == 0) अणु
		अगर (inv_mac_addr)
			dev_warn(db->dev, "%s: Invalid ethernet MAC address. Please set using ip\n",
				 ndev->name);
		prपूर्णांकk(KERN_INFO "%s: dm9000%c at %p,%p IRQ %d MAC: %pM (%s)\n",
		       ndev->name, dm9000_type_to_अक्षर(db->type),
		       db->io_addr, db->io_data, ndev->irq,
		       ndev->dev_addr, mac_src);
	पूर्ण
	वापस 0;

out:
	dev_err(db->dev, "not found (%d).\n", ret);

	dm9000_release_board(pdev, db);
	मुक्त_netdev(ndev);

out_regulator_disable:
	अगर (!IS_ERR(घातer))
		regulator_disable(घातer);

	वापस ret;
पूर्ण

अटल पूर्णांक
dm9000_drv_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा board_info *db;

	अगर (ndev) अणु
		db = netdev_priv(ndev);
		db->in_suspend = 1;

		अगर (!netअगर_running(ndev))
			वापस 0;

		netअगर_device_detach(ndev);

		/* only shutकरोwn अगर not using WoL */
		अगर (!db->wake_state)
			dm9000_shutकरोwn(ndev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
dm9000_drv_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *ndev = dev_get_drvdata(dev);
	काष्ठा board_info *db = netdev_priv(ndev);

	अगर (ndev) अणु
		अगर (netअगर_running(ndev)) अणु
			/* reset अगर we were not in wake mode to ensure अगर
			 * the device was घातered off it is in a known state */
			अगर (!db->wake_state) अणु
				dm9000_init_dm9000(ndev);
				dm9000_unmask_पूर्णांकerrupts(db);
			पूर्ण

			netअगर_device_attach(ndev);
		पूर्ण

		db->in_suspend = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dm9000_drv_pm_ops = अणु
	.suspend	= dm9000_drv_suspend,
	.resume		= dm9000_drv_resume,
पूर्ण;

अटल पूर्णांक
dm9000_drv_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(pdev);
	काष्ठा board_info *dm = to_dm9000_board(ndev);

	unरेजिस्टर_netdev(ndev);
	dm9000_release_board(pdev, dm);
	मुक्त_netdev(ndev);		/* मुक्त device काष्ठाure */
	अगर (dm->घातer_supply)
		regulator_disable(dm->घातer_supply);

	dev_dbg(&pdev->dev, "released and freed device\n");
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id dm9000_of_matches[] = अणु
	अणु .compatible = "davicom,dm9000", पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, dm9000_of_matches);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver dm9000_driver = अणु
	.driver	= अणु
		.name    = "dm9000",
		.pm	 = &dm9000_drv_pm_ops,
		.of_match_table = of_match_ptr(dm9000_of_matches),
	पूर्ण,
	.probe   = dm9000_probe,
	.हटाओ  = dm9000_drv_हटाओ,
पूर्ण;

module_platक्रमm_driver(dm9000_driver);

MODULE_AUTHOR("Sascha Hauer, Ben Dooks");
MODULE_DESCRIPTION("Davicom DM9000 network driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:dm9000");
