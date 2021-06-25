<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver
  Common PHY routines

  Copyright (c) 2005 Martin Langer <martin-langer@gmx.de>,
  Copyright (c) 2005-2007 Stefano Brivio <stefano.brivio@polimi.it>
  Copyright (c) 2005-2008 Michael Buesch <m@bues.ch>
  Copyright (c) 2005, 2006 Danny van Dyk <kugelfang@gentoo.org>
  Copyright (c) 2005, 2006 Andreas Jaggi <andreas.jaggi@waterwave.ch>


*/

#समावेश "phy_common.h"
#समावेश "phy_g.h"
#समावेश "phy_a.h"
#समावेश "phy_n.h"
#समावेश "phy_lp.h"
#समावेश "phy_ht.h"
#समावेश "phy_lcn.h"
#समावेश "phy_ac.h"
#समावेश "b43.h"
#समावेश "main.h"


पूर्णांक b43_phy_allocate(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &(dev->phy);
	पूर्णांक err;

	phy->ops = शून्य;

	चयन (phy->type) अणु
	हाल B43_PHYTYPE_G:
#अगर_घोषित CONFIG_B43_PHY_G
		phy->ops = &b43_phyops_g;
#पूर्ण_अगर
		अवरोध;
	हाल B43_PHYTYPE_N:
#अगर_घोषित CONFIG_B43_PHY_N
		phy->ops = &b43_phyops_n;
#पूर्ण_अगर
		अवरोध;
	हाल B43_PHYTYPE_LP:
#अगर_घोषित CONFIG_B43_PHY_LP
		phy->ops = &b43_phyops_lp;
#पूर्ण_अगर
		अवरोध;
	हाल B43_PHYTYPE_HT:
#अगर_घोषित CONFIG_B43_PHY_HT
		phy->ops = &b43_phyops_ht;
#पूर्ण_अगर
		अवरोध;
	हाल B43_PHYTYPE_LCN:
#अगर_घोषित CONFIG_B43_PHY_LCN
		phy->ops = &b43_phyops_lcn;
#पूर्ण_अगर
		अवरोध;
	हाल B43_PHYTYPE_AC:
#अगर_घोषित CONFIG_B43_PHY_AC
		phy->ops = &b43_phyops_ac;
#पूर्ण_अगर
		अवरोध;
	पूर्ण
	अगर (B43_WARN_ON(!phy->ops))
		वापस -ENODEV;

	err = phy->ops->allocate(dev);
	अगर (err)
		phy->ops = शून्य;

	वापस err;
पूर्ण

व्योम b43_phy_मुक्त(काष्ठा b43_wldev *dev)
अणु
	dev->phy.ops->मुक्त(dev);
	dev->phy.ops = शून्य;
पूर्ण

पूर्णांक b43_phy_init(काष्ठा b43_wldev *dev)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	स्थिर काष्ठा b43_phy_operations *ops = phy->ops;
	पूर्णांक err;

	/* During PHY init we need to use some channel. On the first init this
	 * function is called *beक्रमe* b43_op_config, so our poपूर्णांकer is शून्य.
	 */
	अगर (!phy->chandef) अणु
		phy->chandef = &dev->wl->hw->conf.chandef;
		phy->channel = phy->chandef->chan->hw_value;
	पूर्ण

	phy->ops->चयन_analog(dev, true);
	b43_software_rfसमाप्त(dev, false);

	err = ops->init(dev);
	अगर (err) अणु
		b43err(dev->wl, "PHY init failed\n");
		जाओ err_block_rf;
	पूर्ण
	phy->करो_full_init = false;

	err = b43_चयन_channel(dev, phy->channel);
	अगर (err) अणु
		b43err(dev->wl, "PHY init: Channel switch to default failed\n");
		जाओ err_phy_निकास;
	पूर्ण

	वापस 0;

err_phy_निकास:
	phy->करो_full_init = true;
	अगर (ops->निकास)
		ops->निकास(dev);
err_block_rf:
	b43_software_rfसमाप्त(dev, true);

	वापस err;
पूर्ण

व्योम b43_phy_निकास(काष्ठा b43_wldev *dev)
अणु
	स्थिर काष्ठा b43_phy_operations *ops = dev->phy.ops;

	b43_software_rfसमाप्त(dev, true);
	dev->phy.करो_full_init = true;
	अगर (ops->निकास)
		ops->निकास(dev);
पूर्ण

bool b43_has_hardware_pctl(काष्ठा b43_wldev *dev)
अणु
	अगर (!dev->phy.hardware_घातer_control)
		वापस false;
	अगर (!dev->phy.ops->supports_hwpctl)
		वापस false;
	वापस dev->phy.ops->supports_hwpctl(dev);
पूर्ण

व्योम b43_radio_lock(काष्ठा b43_wldev *dev)
अणु
	u32 macctl;

#अगर B43_DEBUG
	B43_WARN_ON(dev->phy.radio_locked);
	dev->phy.radio_locked = true;
#पूर्ण_अगर

	macctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	macctl |= B43_MACCTL_RADIOLOCK;
	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, macctl);
	/* Commit the ग_लिखो and रुको क्रम the firmware
	 * to finish any radio रेजिस्टर access. */
	b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	udelay(10);
पूर्ण

व्योम b43_radio_unlock(काष्ठा b43_wldev *dev)
अणु
	u32 macctl;

#अगर B43_DEBUG
	B43_WARN_ON(!dev->phy.radio_locked);
	dev->phy.radio_locked = false;
#पूर्ण_अगर

	/* Commit any ग_लिखो */
	b43_पढ़ो16(dev, B43_MMIO_PHY_VER);
	/* unlock */
	macctl = b43_पढ़ो32(dev, B43_MMIO_MACCTL);
	macctl &= ~B43_MACCTL_RADIOLOCK;
	b43_ग_लिखो32(dev, B43_MMIO_MACCTL, macctl);
पूर्ण

व्योम b43_phy_lock(काष्ठा b43_wldev *dev)
अणु
#अगर B43_DEBUG
	B43_WARN_ON(dev->phy.phy_locked);
	dev->phy.phy_locked = true;
#पूर्ण_अगर
	B43_WARN_ON(dev->dev->core_rev < 3);

	अगर (!b43_is_mode(dev->wl, NL80211_IFTYPE_AP))
		b43_घातer_saving_ctl_bits(dev, B43_PS_AWAKE);
पूर्ण

व्योम b43_phy_unlock(काष्ठा b43_wldev *dev)
अणु
#अगर B43_DEBUG
	B43_WARN_ON(!dev->phy.phy_locked);
	dev->phy.phy_locked = false;
#पूर्ण_अगर
	B43_WARN_ON(dev->dev->core_rev < 3);

	अगर (!b43_is_mode(dev->wl, NL80211_IFTYPE_AP))
		b43_घातer_saving_ctl_bits(dev, 0);
पूर्ण

अटल अंतरभूत व्योम निश्चित_mac_suspended(काष्ठा b43_wldev *dev)
अणु
	अगर (!B43_DEBUG)
		वापस;
	अगर ((b43_status(dev) >= B43_STAT_INITIALIZED) &&
	    (dev->mac_suspended <= 0)) अणु
		b43dbg(dev->wl, "PHY/RADIO register access with "
		       "enabled MAC.\n");
		dump_stack();
	पूर्ण
पूर्ण

u16 b43_radio_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	निश्चित_mac_suspended(dev);
	dev->phy.ग_लिखोs_counter = 0;
	वापस dev->phy.ops->radio_पढ़ो(dev, reg);
पूर्ण

व्योम b43_radio_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value)
अणु
	निश्चित_mac_suspended(dev);
	अगर (b43_bus_host_is_pci(dev->dev) &&
	    ++dev->phy.ग_लिखोs_counter > B43_MAX_WRITES_IN_ROW) अणु
		b43_पढ़ो32(dev, B43_MMIO_MACCTL);
		dev->phy.ग_लिखोs_counter = 1;
	पूर्ण
	dev->phy.ops->radio_ग_लिखो(dev, reg, value);
पूर्ण

व्योम b43_radio_mask(काष्ठा b43_wldev *dev, u16 offset, u16 mask)
अणु
	b43_radio_ग_लिखो16(dev, offset,
			  b43_radio_पढ़ो16(dev, offset) & mask);
पूर्ण

व्योम b43_radio_set(काष्ठा b43_wldev *dev, u16 offset, u16 set)
अणु
	b43_radio_ग_लिखो16(dev, offset,
			  b43_radio_पढ़ो16(dev, offset) | set);
पूर्ण

व्योम b43_radio_maskset(काष्ठा b43_wldev *dev, u16 offset, u16 mask, u16 set)
अणु
	b43_radio_ग_लिखो16(dev, offset,
			  (b43_radio_पढ़ो16(dev, offset) & mask) | set);
पूर्ण

bool b43_radio_रुको_value(काष्ठा b43_wldev *dev, u16 offset, u16 mask,
			  u16 value, पूर्णांक delay, पूर्णांक समयout)
अणु
	u16 val;
	पूर्णांक i;

	क्रम (i = 0; i < समयout; i += delay) अणु
		val = b43_radio_पढ़ो(dev, offset);
		अगर ((val & mask) == value)
			वापस true;
		udelay(delay);
	पूर्ण
	वापस false;
पूर्ण

u16 b43_phy_पढ़ो(काष्ठा b43_wldev *dev, u16 reg)
अणु
	निश्चित_mac_suspended(dev);
	dev->phy.ग_लिखोs_counter = 0;

	अगर (dev->phy.ops->phy_पढ़ो)
		वापस dev->phy.ops->phy_पढ़ो(dev, reg);

	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	वापस b43_पढ़ो16(dev, B43_MMIO_PHY_DATA);
पूर्ण

व्योम b43_phy_ग_लिखो(काष्ठा b43_wldev *dev, u16 reg, u16 value)
अणु
	निश्चित_mac_suspended(dev);
	अगर (b43_bus_host_is_pci(dev->dev) &&
	    ++dev->phy.ग_लिखोs_counter > B43_MAX_WRITES_IN_ROW) अणु
		b43_पढ़ो16(dev, B43_MMIO_PHY_VER);
		dev->phy.ग_लिखोs_counter = 1;
	पूर्ण

	अगर (dev->phy.ops->phy_ग_लिखो)
		वापस dev->phy.ops->phy_ग_लिखो(dev, reg, value);

	b43_ग_लिखो16f(dev, B43_MMIO_PHY_CONTROL, reg);
	b43_ग_लिखो16(dev, B43_MMIO_PHY_DATA, value);
पूर्ण

व्योम b43_phy_copy(काष्ठा b43_wldev *dev, u16 destreg, u16 srcreg)
अणु
	b43_phy_ग_लिखो(dev, destreg, b43_phy_पढ़ो(dev, srcreg));
पूर्ण

व्योम b43_phy_mask(काष्ठा b43_wldev *dev, u16 offset, u16 mask)
अणु
	अगर (dev->phy.ops->phy_maskset) अणु
		निश्चित_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, mask, 0);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, offset,
			      b43_phy_पढ़ो(dev, offset) & mask);
	पूर्ण
पूर्ण

व्योम b43_phy_set(काष्ठा b43_wldev *dev, u16 offset, u16 set)
अणु
	अगर (dev->phy.ops->phy_maskset) अणु
		निश्चित_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, 0xFFFF, set);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, offset,
			      b43_phy_पढ़ो(dev, offset) | set);
	पूर्ण
पूर्ण

व्योम b43_phy_maskset(काष्ठा b43_wldev *dev, u16 offset, u16 mask, u16 set)
अणु
	अगर (dev->phy.ops->phy_maskset) अणु
		निश्चित_mac_suspended(dev);
		dev->phy.ops->phy_maskset(dev, offset, mask, set);
	पूर्ण अन्यथा अणु
		b43_phy_ग_लिखो(dev, offset,
			      (b43_phy_पढ़ो(dev, offset) & mask) | set);
	पूर्ण
पूर्ण

व्योम b43_phy_put_पूर्णांकo_reset(काष्ठा b43_wldev *dev)
अणु
	u32 पंचांगp;

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp &= ~B43_BCMA_IOCTL_GMODE;
		पंचांगp |= B43_BCMA_IOCTL_PHY_RESET;
		पंचांगp |= BCMA_IOCTL_FGC;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		udelay(1);

		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp &= ~BCMA_IOCTL_FGC;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		udelay(1);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		पंचांगp &= ~B43_TMSLOW_GMODE;
		पंचांगp |= B43_TMSLOW_PHYRESET;
		पंचांगp |= SSB_TMSLOW_FGC;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		usleep_range(1000, 2000);

		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		पंचांगp &= ~SSB_TMSLOW_FGC;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		usleep_range(1000, 2000);

		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम b43_phy_take_out_of_reset(काष्ठा b43_wldev *dev)
अणु
	u32 पंचांगp;

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		/* Unset reset bit (with क्रमcing घड़ी) */
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp &= ~B43_BCMA_IOCTL_PHY_RESET;
		पंचांगp &= ~B43_BCMA_IOCTL_PHY_CLKEN;
		पंचांगp |= BCMA_IOCTL_FGC;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		udelay(1);

		/* Do not क्रमce घड़ी anymore */
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		पंचांगp &= ~BCMA_IOCTL_FGC;
		पंचांगp |= B43_BCMA_IOCTL_PHY_CLKEN;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		udelay(1);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		/* Unset reset bit (with क्रमcing घड़ी) */
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		पंचांगp &= ~B43_TMSLOW_PHYRESET;
		पंचांगp &= ~B43_TMSLOW_PHYCLKEN;
		पंचांगp |= SSB_TMSLOW_FGC;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW); /* flush */
		usleep_range(1000, 2000);

		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		पंचांगp &= ~SSB_TMSLOW_FGC;
		पंचांगp |= B43_TMSLOW_PHYCLKEN;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW); /* flush */
		usleep_range(1000, 2000);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण

पूर्णांक b43_चयन_channel(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक new_channel)
अणु
	काष्ठा b43_phy *phy = &(dev->phy);
	u16 channelcookie, savedcookie;
	पूर्णांक err;

	/* First we set the channel radio code to prevent the
	 * firmware from sending ghost packets.
	 */
	channelcookie = new_channel;
	अगर (b43_current_band(dev->wl) == NL80211_BAND_5GHZ)
		channelcookie |= B43_SHM_SH_CHAN_5GHZ;
	/* FIXME: set 40Mhz flag अगर required */
	अगर (0)
		channelcookie |= B43_SHM_SH_CHAN_40MHZ;
	savedcookie = b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_CHAN);
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED, B43_SHM_SH_CHAN, channelcookie);

	/* Now try to चयन the PHY hardware channel. */
	err = phy->ops->चयन_channel(dev, new_channel);
	अगर (err)
		जाओ err_restore_cookie;

	/* Wait क्रम the radio to tune to the channel and stabilize. */
	msleep(8);

	वापस 0;

err_restore_cookie:
	b43_shm_ग_लिखो16(dev, B43_SHM_SHARED,
			B43_SHM_SH_CHAN, savedcookie);

	वापस err;
पूर्ण

व्योम b43_software_rfसमाप्त(काष्ठा b43_wldev *dev, bool blocked)
अणु
	काष्ठा b43_phy *phy = &dev->phy;

	b43_mac_suspend(dev);
	phy->ops->software_rfसमाप्त(dev, blocked);
	phy->radio_on = !blocked;
	b43_mac_enable(dev);
पूर्ण

/*
 * b43_phy_txघातer_adjust_work - TX घातer workqueue.
 *
 * Workqueue क्रम updating the TX घातer parameters in hardware.
 */
व्योम b43_phy_txघातer_adjust_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा b43_wl *wl = container_of(work, काष्ठा b43_wl,
					 txघातer_adjust_work);
	काष्ठा b43_wldev *dev;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;

	अगर (likely(dev && (b43_status(dev) >= B43_STAT_STARTED)))
		dev->phy.ops->adjust_txघातer(dev);

	mutex_unlock(&wl->mutex);
पूर्ण

व्योम b43_phy_txघातer_check(काष्ठा b43_wldev *dev, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा b43_phy *phy = &dev->phy;
	अचिन्हित दीर्घ now = jअगरfies;
	क्रमागत b43_txpwr_result result;

	अगर (!(flags & B43_TXPWR_IGNORE_TIME)) अणु
		/* Check अगर it's समय क्रम a TXघातer check. */
		अगर (समय_beक्रमe(now, phy->next_txpwr_check_समय))
			वापस; /* Not yet */
	पूर्ण
	/* The next check will be needed in two seconds, or later. */
	phy->next_txpwr_check_समय = round_jअगरfies(now + (HZ * 2));

	अगर ((dev->dev->board_venकरोr == SSB_BOARDVENDOR_BCM) &&
	    (dev->dev->board_type == SSB_BOARD_BU4306))
		वापस; /* No software txघातer adjusपंचांगent needed */

	result = phy->ops->recalc_txघातer(dev, !!(flags & B43_TXPWR_IGNORE_TSSI));
	अगर (result == B43_TXPWR_RES_DONE)
		वापस; /* We are करोne. */
	B43_WARN_ON(result != B43_TXPWR_RES_NEED_ADJUST);
	B43_WARN_ON(phy->ops->adjust_txघातer == शून्य);

	/* We must adjust the transmission घातer in hardware.
	 * Schedule b43_phy_txघातer_adjust_work(). */
	ieee80211_queue_work(dev->wl->hw, &dev->wl->txघातer_adjust_work);
पूर्ण

पूर्णांक b43_phy_shm_tssi_पढ़ो(काष्ठा b43_wldev *dev, u16 shm_offset)
अणु
	स्थिर bool is_ofdm = (shm_offset != B43_SHM_SH_TSSI_CCK);
	अचिन्हित पूर्णांक a, b, c, d;
	अचिन्हित पूर्णांक average;
	u32 पंचांगp;

	पंचांगp = b43_shm_पढ़ो32(dev, B43_SHM_SHARED, shm_offset);
	a = पंचांगp & 0xFF;
	b = (पंचांगp >> 8) & 0xFF;
	c = (पंचांगp >> 16) & 0xFF;
	d = (पंचांगp >> 24) & 0xFF;
	अगर (a == 0 || a == B43_TSSI_MAX ||
	    b == 0 || b == B43_TSSI_MAX ||
	    c == 0 || c == B43_TSSI_MAX ||
	    d == 0 || d == B43_TSSI_MAX)
		वापस -ENOENT;
	/* The values are OK. Clear them. */
	पंचांगp = B43_TSSI_MAX | (B43_TSSI_MAX << 8) |
	      (B43_TSSI_MAX << 16) | (B43_TSSI_MAX << 24);
	b43_shm_ग_लिखो32(dev, B43_SHM_SHARED, shm_offset, पंचांगp);

	अगर (is_ofdm) अणु
		a = (a + 32) & 0x3F;
		b = (b + 32) & 0x3F;
		c = (c + 32) & 0x3F;
		d = (d + 32) & 0x3F;
	पूर्ण

	/* Get the average of the values with 0.5 added to each value. */
	average = (a + b + c + d + 2) / 4;
	अगर (is_ofdm) अणु
		/* Adjust क्रम CCK-boost */
		अगर (b43_shm_पढ़ो16(dev, B43_SHM_SHARED, B43_SHM_SH_HOSTF1)
		    & B43_HF_CCKBOOST)
			average = (average >= 13) ? (average - 13) : 0;
	पूर्ण

	वापस average;
पूर्ण

व्योम b43_phyop_चयन_analog_generic(काष्ठा b43_wldev *dev, bool on)
अणु
	b43_ग_लिखो16(dev, B43_MMIO_PHY0, on ? 0 : 0xF4);
पूर्ण


bool b43_is_40mhz(काष्ठा b43_wldev *dev)
अणु
	वापस dev->phy.chandef->width == NL80211_CHAN_WIDTH_40;
पूर्ण

/* https://bcm-v4.sipsolutions.net/802.11/PHY/N/BmacPhyClkFgc */
व्योम b43_phy_क्रमce_घड़ी(काष्ठा b43_wldev *dev, bool क्रमce)
अणु
	u32 पंचांगp;

	WARN_ON(dev->phy.type != B43_PHYTYPE_N &&
		dev->phy.type != B43_PHYTYPE_HT &&
		dev->phy.type != B43_PHYTYPE_AC);

	चयन (dev->dev->bus_type) अणु
#अगर_घोषित CONFIG_B43_BCMA
	हाल B43_BUS_BCMA:
		पंचांगp = bcma_aपढ़ो32(dev->dev->bdev, BCMA_IOCTL);
		अगर (क्रमce)
			पंचांगp |= BCMA_IOCTL_FGC;
		अन्यथा
			पंचांगp &= ~BCMA_IOCTL_FGC;
		bcma_aग_लिखो32(dev->dev->bdev, BCMA_IOCTL, पंचांगp);
		अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_B43_SSB
	हाल B43_BUS_SSB:
		पंचांगp = ssb_पढ़ो32(dev->dev->sdev, SSB_TMSLOW);
		अगर (क्रमce)
			पंचांगp |= SSB_TMSLOW_FGC;
		अन्यथा
			पंचांगp &= ~SSB_TMSLOW_FGC;
		ssb_ग_लिखो32(dev->dev->sdev, SSB_TMSLOW, पंचांगp);
		अवरोध;
#पूर्ण_अगर
	पूर्ण
पूर्ण
