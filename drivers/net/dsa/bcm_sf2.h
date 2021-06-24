<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Broadcom Starfighter2 निजी context
 *
 * Copyright (C) 2014, Broadcom Corporation
 */

#अगर_अघोषित __BCM_SF2_H
#घोषणा __BCM_SF2_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/mii.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/reset.h>

#समावेश <net/dsa.h>

#समावेश "bcm_sf2_regs.h"
#समावेश "b53/b53_priv.h"

काष्ठा bcm_sf2_hw_params अणु
	u16	top_rev;
	u16	core_rev;
	u16	gphy_rev;
	u32	num_gphy;
	u8	num_acb_queue;
	u8	num_rgmii;
	u8	num_ports;
	u8	fcb_छोड़ो_override:1;
	u8	acb_packets_inflight:1;
पूर्ण;

#घोषणा BCM_SF2_REGS_NAME अणु\
	"core", "reg", "intrl2_0", "intrl2_1", "fcb", "acb" \
पूर्ण

#घोषणा BCM_SF2_REGS_NUM	6

काष्ठा bcm_sf2_port_status अणु
	phy_पूर्णांकerface_t mode;
	अचिन्हित पूर्णांक link;
	bool enabled;
पूर्ण;

काष्ठा bcm_sf2_cfp_priv अणु
	/* Mutex protecting concurrent accesses to the CFP रेजिस्टरs */
	काष्ठा mutex lock;
	DECLARE_BITMAP(used, CFP_NUM_RULES);
	DECLARE_BITMAP(unique, CFP_NUM_RULES);
	अचिन्हित पूर्णांक rules_cnt;
	काष्ठा list_head rules_list;
पूर्ण;

काष्ठा bcm_sf2_priv अणु
	/* Base रेजिस्टरs, keep those in order with BCM_SF2_REGS_NAME */
	व्योम __iomem			*core;
	व्योम __iomem			*reg;
	व्योम __iomem			*पूर्णांकrl2_0;
	व्योम __iomem			*पूर्णांकrl2_1;
	व्योम __iomem			*fcb;
	व्योम __iomem			*acb;

	काष्ठा reset_control		*rcdev;

	/* Register offsets indirection tables */
	u32 				type;
	स्थिर u16			*reg_offsets;
	अचिन्हित पूर्णांक			core_reg_align;
	अचिन्हित पूर्णांक			num_cfp_rules;
	अचिन्हित पूर्णांक			num_crossbar_पूर्णांक_ports;

	/* spinlock protecting access to the indirect रेजिस्टरs */
	spinlock_t			indir_lock;

	पूर्णांक				irq0;
	पूर्णांक				irq1;
	u32				irq0_stat;
	u32				irq0_mask;
	u32				irq1_stat;
	u32				irq1_mask;

	/* Backing b53_device */
	काष्ठा b53_device		*dev;

	काष्ठा bcm_sf2_hw_params	hw_params;

	काष्ठा bcm_sf2_port_status	port_sts[DSA_MAX_PORTS];

	/* Mask of ports enabled क्रम Wake-on-LAN */
	u32				wol_ports_mask;

	काष्ठा clk			*clk;
	काष्ठा clk			*clk_mभाग;

	/* MoCA port location */
	पूर्णांक				moca_port;

	/* Biपंचांगask of ports having an पूर्णांकegrated PHY */
	अचिन्हित पूर्णांक			पूर्णांक_phy_mask;

	/* Master and slave MDIO bus controller */
	अचिन्हित पूर्णांक			indir_phy_mask;
	काष्ठा device_node		*master_mii_dn;
	काष्ठा mii_bus			*slave_mii_bus;
	काष्ठा mii_bus			*master_mii_bus;

	/* Biपंचांगask of ports needing BRCM tags */
	अचिन्हित पूर्णांक			brcm_tag_mask;

	/* CFP rules context */
	काष्ठा bcm_sf2_cfp_priv		cfp;
पूर्ण;

अटल अंतरभूत काष्ठा bcm_sf2_priv *bcm_sf2_to_priv(काष्ठा dsa_चयन *ds)
अणु
	काष्ठा b53_device *dev = ds->priv;

	वापस dev->priv;
पूर्ण

अटल अंतरभूत u32 bcm_sf2_mangle_addr(काष्ठा bcm_sf2_priv *priv, u32 off)
अणु
	वापस off << priv->core_reg_align;
पूर्ण

#घोषणा SF2_IO_MACRO(name) \
अटल अंतरभूत u32 name##_पढ़ोl(काष्ठा bcm_sf2_priv *priv, u32 off)	\
अणु									\
	वापस पढ़ोl_relaxed(priv->name + off);				\
पूर्ण									\
अटल अंतरभूत व्योम name##_ग_लिखोl(काष्ठा bcm_sf2_priv *priv,		\
				  u32 val, u32 off)			\
अणु									\
	ग_लिखोl_relaxed(val, priv->name + off);				\
पूर्ण									\

/* Accesses to 64-bits रेजिस्टर requires us to latch the hi/lo pairs
 * using the REG_सूची_DATA_अणुREAD,WRITEपूर्ण ancillary रेजिस्टरs. The 'indir_lock'
 * spinlock is स्वतःmatically grabbed and released to provide relative
 * atomiticy with latched पढ़ोs/ग_लिखोs.
 */
#घोषणा SF2_IO64_MACRO(name) \
अटल अंतरभूत u64 name##_पढ़ोq(काष्ठा bcm_sf2_priv *priv, u32 off)	\
अणु									\
	u32 indir, dir;							\
	spin_lock(&priv->indir_lock);					\
	dir = name##_पढ़ोl(priv, off);					\
	indir = reg_पढ़ोl(priv, REG_सूची_DATA_READ);			\
	spin_unlock(&priv->indir_lock);					\
	वापस (u64)indir << 32 | dir;					\
पूर्ण									\
अटल अंतरभूत व्योम name##_ग_लिखोq(काष्ठा bcm_sf2_priv *priv, u64 val,	\
							u32 off)	\
अणु									\
	spin_lock(&priv->indir_lock);					\
	reg_ग_लिखोl(priv, upper_32_bits(val), REG_सूची_DATA_WRITE);	\
	name##_ग_लिखोl(priv, lower_32_bits(val), off);			\
	spin_unlock(&priv->indir_lock);					\
पूर्ण

#घोषणा SWITCH_INTR_L2(which)						\
अटल अंतरभूत व्योम पूर्णांकrl2_##which##_mask_clear(काष्ठा bcm_sf2_priv *priv, \
						u32 mask)		\
अणु									\
	priv->irq##which##_mask &= ~(mask);				\
	पूर्णांकrl2_##which##_ग_लिखोl(priv, mask, INTRL2_CPU_MASK_CLEAR);	\
पूर्ण									\
अटल अंतरभूत व्योम पूर्णांकrl2_##which##_mask_set(काष्ठा bcm_sf2_priv *priv, \
						u32 mask)		\
अणु									\
	पूर्णांकrl2_## which##_ग_लिखोl(priv, mask, INTRL2_CPU_MASK_SET);	\
	priv->irq##which##_mask |= (mask);				\
पूर्ण									\

अटल अंतरभूत u32 core_पढ़ोl(काष्ठा bcm_sf2_priv *priv, u32 off)
अणु
	u32 पंचांगp = bcm_sf2_mangle_addr(priv, off);
	वापस पढ़ोl_relaxed(priv->core + पंचांगp);
पूर्ण

अटल अंतरभूत व्योम core_ग_लिखोl(काष्ठा bcm_sf2_priv *priv, u32 val, u32 off)
अणु
	u32 पंचांगp = bcm_sf2_mangle_addr(priv, off);
	ग_लिखोl_relaxed(val, priv->core + पंचांगp);
पूर्ण

अटल अंतरभूत u32 reg_पढ़ोl(काष्ठा bcm_sf2_priv *priv, u16 off)
अणु
	वापस पढ़ोl_relaxed(priv->reg + priv->reg_offsets[off]);
पूर्ण

अटल अंतरभूत व्योम reg_ग_लिखोl(काष्ठा bcm_sf2_priv *priv, u32 val, u16 off)
अणु
	ग_लिखोl_relaxed(val, priv->reg + priv->reg_offsets[off]);
पूर्ण

SF2_IO64_MACRO(core);
SF2_IO_MACRO(पूर्णांकrl2_0);
SF2_IO_MACRO(पूर्णांकrl2_1);
SF2_IO_MACRO(fcb);
SF2_IO_MACRO(acb);

SWITCH_INTR_L2(0);
SWITCH_INTR_L2(1);

/* RXNFC */
पूर्णांक bcm_sf2_get_rxnfc(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      काष्ठा ethtool_rxnfc *nfc, u32 *rule_locs);
पूर्णांक bcm_sf2_set_rxnfc(काष्ठा dsa_चयन *ds, पूर्णांक port,
		      काष्ठा ethtool_rxnfc *nfc);
पूर्णांक bcm_sf2_cfp_rst(काष्ठा bcm_sf2_priv *priv);
व्योम bcm_sf2_cfp_निकास(काष्ठा dsa_चयन *ds);
पूर्णांक bcm_sf2_cfp_resume(काष्ठा dsa_चयन *ds);
व्योम bcm_sf2_cfp_get_strings(काष्ठा dsa_चयन *ds, पूर्णांक port,
			     u32 stringset, uपूर्णांक8_t *data);
व्योम bcm_sf2_cfp_get_ethtool_stats(काष्ठा dsa_चयन *ds, पूर्णांक port,
				   uपूर्णांक64_t *data);
पूर्णांक bcm_sf2_cfp_get_sset_count(काष्ठा dsa_चयन *ds, पूर्णांक port, पूर्णांक sset);

#पूर्ण_अगर /* __BCM_SF2_H */
