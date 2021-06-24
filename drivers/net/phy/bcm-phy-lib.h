<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2015 Broadcom Corporation
 */

#अगर_अघोषित _LINUX_BCM_PHY_LIB_H
#घोषणा _LINUX_BCM_PHY_LIB_H

#समावेश <linux/brcmphy.h>
#समावेश <linux/phy.h>

/* 28nm only रेजिस्टर definitions */
#घोषणा MISC_ADDR(base, channel)	base, channel

#घोषणा DSP_TAP10			MISC_ADDR(0x0a, 0)
#घोषणा PLL_PLLCTRL_1			MISC_ADDR(0x32, 1)
#घोषणा PLL_PLLCTRL_2			MISC_ADDR(0x32, 2)
#घोषणा PLL_PLLCTRL_4			MISC_ADDR(0x33, 0)

#घोषणा AFE_RXCONFIG_0			MISC_ADDR(0x38, 0)
#घोषणा AFE_RXCONFIG_1			MISC_ADDR(0x38, 1)
#घोषणा AFE_RXCONFIG_2			MISC_ADDR(0x38, 2)
#घोषणा AFE_RX_LP_COUNTER		MISC_ADDR(0x38, 3)
#घोषणा AFE_TX_CONFIG			MISC_ADDR(0x39, 0)
#घोषणा AFE_VDCA_ICTRL_0		MISC_ADDR(0x39, 1)
#घोषणा AFE_VDAC_OTHERS_0		MISC_ADDR(0x39, 3)
#घोषणा AFE_HPF_TRIM_OTHERS		MISC_ADDR(0x3a, 0)


पूर्णांक __bcm_phy_ग_लिखो_exp(काष्ठा phy_device *phydev, u16 reg, u16 val);
पूर्णांक __bcm_phy_पढ़ो_exp(काष्ठा phy_device *phydev, u16 reg);
पूर्णांक __bcm_phy_modअगरy_exp(काष्ठा phy_device *phydev, u16 reg, u16 mask, u16 set);
पूर्णांक bcm_phy_ग_लिखो_exp(काष्ठा phy_device *phydev, u16 reg, u16 val);
पूर्णांक bcm_phy_पढ़ो_exp(काष्ठा phy_device *phydev, u16 reg);
पूर्णांक bcm_phy_modअगरy_exp(काष्ठा phy_device *phydev, u16 reg, u16 mask, u16 set);

अटल अंतरभूत पूर्णांक bcm_phy_ग_लिखो_exp_sel(काष्ठा phy_device *phydev,
					u16 reg, u16 val)
अणु
	वापस bcm_phy_ग_लिखो_exp(phydev, reg | MII_BCM54XX_EXP_SEL_ER, val);
पूर्ण

पूर्णांक bcm54xx_auxctl_ग_लिखो(काष्ठा phy_device *phydev, u16 regnum, u16 val);
पूर्णांक bcm54xx_auxctl_पढ़ो(काष्ठा phy_device *phydev, u16 regnum);

पूर्णांक bcm_phy_ग_लिखो_misc(काष्ठा phy_device *phydev,
		       u16 reg, u16 chl, u16 value);
पूर्णांक bcm_phy_पढ़ो_misc(काष्ठा phy_device *phydev,
		      u16 reg, u16 chl);

पूर्णांक bcm_phy_ग_लिखो_shaकरोw(काष्ठा phy_device *phydev, u16 shaकरोw,
			 u16 val);
पूर्णांक bcm_phy_पढ़ो_shaकरोw(काष्ठा phy_device *phydev, u16 shaकरोw);

पूर्णांक __bcm_phy_ग_लिखो_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 val);
पूर्णांक bcm_phy_ग_लिखो_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 val);
पूर्णांक __bcm_phy_पढ़ो_rdb(काष्ठा phy_device *phydev, u16 rdb);
पूर्णांक bcm_phy_पढ़ो_rdb(काष्ठा phy_device *phydev, u16 rdb);
पूर्णांक __bcm_phy_modअगरy_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 mask,
			 u16 set);
पूर्णांक bcm_phy_modअगरy_rdb(काष्ठा phy_device *phydev, u16 rdb, u16 mask,
		       u16 set);

पूर्णांक bcm_phy_ack_पूर्णांकr(काष्ठा phy_device *phydev);
पूर्णांक bcm_phy_config_पूर्णांकr(काष्ठा phy_device *phydev);
irqवापस_t bcm_phy_handle_पूर्णांकerrupt(काष्ठा phy_device *phydev);

पूर्णांक bcm_phy_enable_apd(काष्ठा phy_device *phydev, bool dll_pwr_करोwn);

पूर्णांक bcm_phy_set_eee(काष्ठा phy_device *phydev, bool enable);

पूर्णांक bcm_phy_करोwnshअगरt_get(काष्ठा phy_device *phydev, u8 *count);

पूर्णांक bcm_phy_करोwnshअगरt_set(काष्ठा phy_device *phydev, u8 count);

पूर्णांक bcm_phy_get_sset_count(काष्ठा phy_device *phydev);
व्योम bcm_phy_get_strings(काष्ठा phy_device *phydev, u8 *data);
व्योम bcm_phy_get_stats(काष्ठा phy_device *phydev, u64 *shaकरोw,
		       काष्ठा ethtool_stats *stats, u64 *data);
व्योम bcm_phy_r_rc_cal_reset(काष्ठा phy_device *phydev);
पूर्णांक bcm_phy_28nm_a0b0_afe_config_init(काष्ठा phy_device *phydev);
पूर्णांक bcm_phy_enable_jumbo(काष्ठा phy_device *phydev);

पूर्णांक bcm_phy_cable_test_get_status_rdb(काष्ठा phy_device *phydev,
				      bool *finished);
पूर्णांक bcm_phy_cable_test_start_rdb(काष्ठा phy_device *phydev);
पूर्णांक bcm_phy_cable_test_start(काष्ठा phy_device *phydev);
पूर्णांक bcm_phy_cable_test_get_status(काष्ठा phy_device *phydev, bool *finished);

#पूर्ण_अगर /* _LINUX_BCM_PHY_LIB_H */
