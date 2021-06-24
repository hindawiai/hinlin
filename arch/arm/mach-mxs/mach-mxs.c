<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2012 Freescale Semiconductor, Inc.
 * Copyright 2012 Linaro Ltd.
 */

#समावेश <linux/clk.h>
#समावेश <linux/clk/mxs.h>
#समावेश <linux/clkdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/init.h>
#समावेश <linux/irqchip/mxs.h>
#समावेश <linux/reboot.h>
#समावेश <linux/micrel_phy.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/phy.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <linux/sys_soc.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/समय.स>
#समावेश <यंत्र/प्रणाली_info.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "pm.h"

/* MXS DIGCTL SAIF CLKMUX */
#घोषणा MXS_DIGCTL_SAIF_CLKMUX_सूचीECT		0x0
#घोषणा MXS_DIGCTL_SAIF_CLKMUX_CROSSINPUT	0x1
#घोषणा MXS_DIGCTL_SAIF_CLKMUX_EXTMSTR0		0x2
#घोषणा MXS_DIGCTL_SAIF_CLKMUX_EXTMSTR1		0x3

#घोषणा HW_DIGCTL_CHIPID	0x310
#घोषणा HW_DIGCTL_CHIPID_MASK	(0xffff << 16)
#घोषणा HW_DIGCTL_REV_MASK	0xff
#घोषणा HW_DIGCTL_CHIPID_MX23	(0x3780 << 16)
#घोषणा HW_DIGCTL_CHIPID_MX28	(0x2800 << 16)

#घोषणा MXS_CHIP_REVISION_1_0	0x10
#घोषणा MXS_CHIP_REVISION_1_1	0x11
#घोषणा MXS_CHIP_REVISION_1_2	0x12
#घोषणा MXS_CHIP_REVISION_1_3	0x13
#घोषणा MXS_CHIP_REVISION_1_4	0x14
#घोषणा MXS_CHIP_REV_UNKNOWN	0xff

#घोषणा MXS_GPIO_NR(bank, nr)	((bank) * 32 + (nr))

#घोषणा MXS_SET_ADDR		0x4
#घोषणा MXS_CLR_ADDR		0x8
#घोषणा MXS_TOG_ADDR		0xc

#घोषणा HW_OCOTP_OPS2		19	/* offset 0x150 */
#घोषणा HW_OCOTP_OPS3		20	/* offset 0x160 */

अटल u32 chipid;
अटल u32 socid;

अटल व्योम __iomem *reset_addr;

अटल अंतरभूत व्योम __mxs_setl(u32 mask, व्योम __iomem *reg)
अणु
	__raw_ग_लिखोl(mask, reg + MXS_SET_ADDR);
पूर्ण

अटल अंतरभूत व्योम __mxs_clrl(u32 mask, व्योम __iomem *reg)
अणु
	__raw_ग_लिखोl(mask, reg + MXS_CLR_ADDR);
पूर्ण

अटल अंतरभूत व्योम __mxs_togl(u32 mask, व्योम __iomem *reg)
अणु
	__raw_ग_लिखोl(mask, reg + MXS_TOG_ADDR);
पूर्ण

#घोषणा OCOTP_WORD_OFFSET		0x20
#घोषणा OCOTP_WORD_COUNT		0x20

#घोषणा BM_OCOTP_CTRL_BUSY		(1 << 8)
#घोषणा BM_OCOTP_CTRL_ERROR		(1 << 9)
#घोषणा BM_OCOTP_CTRL_RD_BANK_OPEN	(1 << 12)

अटल DEFINE_MUTEX(ocotp_mutex);
अटल u32 ocotp_words[OCOTP_WORD_COUNT];

अटल स्थिर u32 *mxs_get_ocotp(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *ocotp_base;
	पूर्णांक समयout = 0x400;
	माप_प्रकार i;
	अटल पूर्णांक once;

	अगर (once)
		वापस ocotp_words;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,ocotp");
	ocotp_base = of_iomap(np, 0);
	WARN_ON(!ocotp_base);

	mutex_lock(&ocotp_mutex);

	/*
	 * clk_enable(hbus_clk) क्रम ocotp can be skipped
	 * as it must be on when प्रणाली is running.
	 */

	/* try to clear ERROR bit */
	__mxs_clrl(BM_OCOTP_CTRL_ERROR, ocotp_base);

	/* check both BUSY and ERROR cleared */
	जबतक ((__raw_पढ़ोl(ocotp_base) &
		(BM_OCOTP_CTRL_BUSY | BM_OCOTP_CTRL_ERROR)) && --समयout)
		cpu_relax();

	अगर (unlikely(!समयout))
		जाओ error_unlock;

	/* खोलो OCOTP banks क्रम पढ़ो */
	__mxs_setl(BM_OCOTP_CTRL_RD_BANK_OPEN, ocotp_base);

	/* approximately रुको 32 hclk cycles */
	udelay(1);

	/* poll BUSY bit becoming cleared */
	समयout = 0x400;
	जबतक ((__raw_पढ़ोl(ocotp_base) & BM_OCOTP_CTRL_BUSY) && --समयout)
		cpu_relax();

	अगर (unlikely(!समयout))
		जाओ error_unlock;

	क्रम (i = 0; i < OCOTP_WORD_COUNT; i++)
		ocotp_words[i] = __raw_पढ़ोl(ocotp_base + OCOTP_WORD_OFFSET +
						i * 0x10);

	/* बंद banks क्रम घातer saving */
	__mxs_clrl(BM_OCOTP_CTRL_RD_BANK_OPEN, ocotp_base);

	once = 1;

	mutex_unlock(&ocotp_mutex);

	वापस ocotp_words;

error_unlock:
	mutex_unlock(&ocotp_mutex);
	pr_err("%s: timeout in reading OCOTP\n", __func__);
	वापस शून्य;
पूर्ण

क्रमागत mac_oui अणु
	OUI_FSL,
	OUI_DENX,
	OUI_CRYSTALFONTZ,
	OUI_I2SE,
	OUI_ARMADEUS,
पूर्ण;

अटल व्योम __init update_fec_mac_prop(क्रमागत mac_oui oui)
अणु
	काष्ठा device_node *np, *from = शून्य;
	काष्ठा property *newmac;
	स्थिर u32 *ocotp = mxs_get_ocotp();
	u8 *macaddr;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++) अणु
		np = of_find_compatible_node(from, शून्य, "fsl,imx28-fec");
		अगर (!np)
			वापस;

		from = np;

		अगर (of_get_property(np, "local-mac-address", शून्य))
			जारी;

		newmac = kzalloc(माप(*newmac) + 6, GFP_KERNEL);
		अगर (!newmac)
			वापस;
		newmac->value = newmac + 1;
		newmac->length = 6;

		newmac->name = kstrdup("local-mac-address", GFP_KERNEL);
		अगर (!newmac->name) अणु
			kमुक्त(newmac);
			वापस;
		पूर्ण

		/*
		 * OCOTP only stores the last 4 octets क्रम each mac address,
		 * so hard-code OUI here.
		 */
		macaddr = newmac->value;
		चयन (oui) अणु
		हाल OUI_FSL:
			macaddr[0] = 0x00;
			macaddr[1] = 0x04;
			macaddr[2] = 0x9f;
			अवरोध;
		हाल OUI_DENX:
			macaddr[0] = 0xc0;
			macaddr[1] = 0xe5;
			macaddr[2] = 0x4e;
			अवरोध;
		हाल OUI_CRYSTALFONTZ:
			macaddr[0] = 0x58;
			macaddr[1] = 0xb9;
			macaddr[2] = 0xe1;
			अवरोध;
		हाल OUI_I2SE:
			macaddr[0] = 0x00;
			macaddr[1] = 0x01;
			macaddr[2] = 0x87;
			अवरोध;
		हाल OUI_ARMADEUS:
			macaddr[0] = 0x00;
			macaddr[1] = 0x1e;
			macaddr[2] = 0xac;
			अवरोध;
		पूर्ण
		val = ocotp[i];
		macaddr[3] = (val >> 16) & 0xff;
		macaddr[4] = (val >> 8) & 0xff;
		macaddr[5] = (val >> 0) & 0xff;

		of_update_property(np, newmac);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम enable_clk_enet_out(व्योम)
अणु
	काष्ठा clk *clk = clk_get_sys("enet_out", शून्य);

	अगर (!IS_ERR(clk))
		clk_prepare_enable(clk);
पूर्ण

अटल व्योम __init imx28_evk_init(व्योम)
अणु
	update_fec_mac_prop(OUI_FSL);

	mxs_saअगर_clkmux_select(MXS_DIGCTL_SAIF_CLKMUX_EXTMSTR0);
पूर्ण

अटल व्योम __init imx28_apf28_init(व्योम)
अणु
	update_fec_mac_prop(OUI_ARMADEUS);
पूर्ण

अटल पूर्णांक apx4devkit_phy_fixup(काष्ठा phy_device *phy)
अणु
	phy->dev_flags |= MICREL_PHY_50MHZ_CLK;
	वापस 0;
पूर्ण

अटल व्योम __init apx4devkit_init(व्योम)
अणु
	enable_clk_enet_out();

	अगर (IS_BUILTIN(CONFIG_PHYLIB))
		phy_रेजिस्टर_fixup_क्रम_uid(PHY_ID_KSZ8051, MICREL_PHY_ID_MASK,
					   apx4devkit_phy_fixup);
पूर्ण

अटल व्योम __init crystalfontz_init(व्योम)
अणु
	update_fec_mac_prop(OUI_CRYSTALFONTZ);
पूर्ण

अटल व्योम __init duckbill_init(व्योम)
अणु
	update_fec_mac_prop(OUI_I2SE);
पूर्ण

अटल व्योम __init m28cu3_init(व्योम)
अणु
	update_fec_mac_prop(OUI_DENX);
पूर्ण

अटल स्थिर अक्षर __init *mxs_get_soc_id(व्योम)
अणु
	काष्ठा device_node *np;
	व्योम __iomem *digctl_base;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,imx23-digctl");
	digctl_base = of_iomap(np, 0);
	WARN_ON(!digctl_base);

	chipid = पढ़ोl(digctl_base + HW_DIGCTL_CHIPID);
	socid = chipid & HW_DIGCTL_CHIPID_MASK;

	iounmap(digctl_base);
	of_node_put(np);

	चयन (socid) अणु
	हाल HW_DIGCTL_CHIPID_MX23:
		वापस "i.MX23";
	हाल HW_DIGCTL_CHIPID_MX28:
		वापस "i.MX28";
	शेष:
		वापस "Unknown";
	पूर्ण
पूर्ण

अटल u32 __init mxs_get_cpu_rev(व्योम)
अणु
	u32 rev = chipid & HW_DIGCTL_REV_MASK;

	चयन (socid) अणु
	हाल HW_DIGCTL_CHIPID_MX23:
		चयन (rev) अणु
		हाल 0x0:
			वापस MXS_CHIP_REVISION_1_0;
		हाल 0x1:
			वापस MXS_CHIP_REVISION_1_1;
		हाल 0x2:
			वापस MXS_CHIP_REVISION_1_2;
		हाल 0x3:
			वापस MXS_CHIP_REVISION_1_3;
		हाल 0x4:
			वापस MXS_CHIP_REVISION_1_4;
		शेष:
			वापस MXS_CHIP_REV_UNKNOWN;
		पूर्ण
	हाल HW_DIGCTL_CHIPID_MX28:
		चयन (rev) अणु
		हाल 0x0:
			वापस MXS_CHIP_REVISION_1_1;
		हाल 0x1:
			वापस MXS_CHIP_REVISION_1_2;
		शेष:
			वापस MXS_CHIP_REV_UNKNOWN;
		पूर्ण
	शेष:
		वापस MXS_CHIP_REV_UNKNOWN;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर __init *mxs_get_revision(व्योम)
अणु
	u32 rev = mxs_get_cpu_rev();

	अगर (rev != MXS_CHIP_REV_UNKNOWN)
		वापस kaप्र_लिखो(GFP_KERNEL, "%d.%d", (rev >> 4) & 0xf,
				rev & 0xf);
	अन्यथा
		वापस kaप्र_लिखो(GFP_KERNEL, "%s", "Unknown");
पूर्ण

#घोषणा MX23_CLKCTRL_RESET_OFFSET	0x120
#घोषणा MX28_CLKCTRL_RESET_OFFSET	0x1e0

अटल पूर्णांक __init mxs_restart_init(व्योम)
अणु
	काष्ठा device_node *np;

	np = of_find_compatible_node(शून्य, शून्य, "fsl,clkctrl");
	reset_addr = of_iomap(np, 0);
	अगर (!reset_addr)
		वापस -ENODEV;

	अगर (of_device_is_compatible(np, "fsl,imx23-clkctrl"))
		reset_addr += MX23_CLKCTRL_RESET_OFFSET;
	अन्यथा
		reset_addr += MX28_CLKCTRL_RESET_OFFSET;
	of_node_put(np);

	वापस 0;
पूर्ण

अटल व्योम __init eukrea_mbmx283lc_init(व्योम)
अणु
	mxs_saअगर_clkmux_select(MXS_DIGCTL_SAIF_CLKMUX_EXTMSTR0);
पूर्ण

अटल व्योम __init mxs_machine_init(व्योम)
अणु
	काष्ठा device_node *root;
	काष्ठा device *parent;
	काष्ठा soc_device *soc_dev;
	काष्ठा soc_device_attribute *soc_dev_attr;
	u64 soc_uid = 0;
	स्थिर u32 *ocotp = mxs_get_ocotp();
	पूर्णांक ret;

	soc_dev_attr = kzalloc(माप(*soc_dev_attr), GFP_KERNEL);
	अगर (!soc_dev_attr)
		वापस;

	root = of_find_node_by_path("/");
	ret = of_property_पढ़ो_string(root, "model", &soc_dev_attr->machine);
	अगर (ret)
		वापस;

	soc_dev_attr->family = "Freescale MXS Family";
	soc_dev_attr->soc_id = mxs_get_soc_id();
	soc_dev_attr->revision = mxs_get_revision();

	अगर (socid == HW_DIGCTL_CHIPID_MX23) अणु
		soc_uid = प्रणाली_serial_low = ocotp[HW_OCOTP_OPS3];
	पूर्ण अन्यथा अगर (socid == HW_DIGCTL_CHIPID_MX28) अणु
		soc_uid = प्रणाली_serial_high = ocotp[HW_OCOTP_OPS2];
		soc_uid <<= 32;
		प्रणाली_serial_low = ocotp[HW_OCOTP_OPS3];
		soc_uid |= प्रणाली_serial_low;
	पूर्ण

	अगर (soc_uid)
		soc_dev_attr->serial_number = kaप्र_लिखो(GFP_KERNEL, "%016llX", soc_uid);

	soc_dev = soc_device_रेजिस्टर(soc_dev_attr);
	अगर (IS_ERR(soc_dev)) अणु
		kमुक्त(soc_dev_attr->serial_number);
		kमुक्त(soc_dev_attr->revision);
		kमुक्त(soc_dev_attr);
		वापस;
	पूर्ण

	parent = soc_device_to_device(soc_dev);

	अगर (of_machine_is_compatible("fsl,imx28-evk"))
		imx28_evk_init();
	अगर (of_machine_is_compatible("armadeus,imx28-apf28"))
		imx28_apf28_init();
	अन्यथा अगर (of_machine_is_compatible("bluegiga,apx4devkit"))
		apx4devkit_init();
	अन्यथा अगर (of_machine_is_compatible("crystalfontz,cfa10036"))
		crystalfontz_init();
	अन्यथा अगर (of_machine_is_compatible("eukrea,mbmx283lc"))
		eukrea_mbmx283lc_init();
	अन्यथा अगर (of_machine_is_compatible("i2se,duckbill") ||
		 of_machine_is_compatible("i2se,duckbill-2"))
		duckbill_init();
	अन्यथा अगर (of_machine_is_compatible("msr,m28cu3"))
		m28cu3_init();

	of_platक्रमm_शेष_populate(शून्य, शून्य, parent);

	mxs_restart_init();
पूर्ण

#घोषणा MXS_CLKCTRL_RESET_CHIP		(1 << 1)

/*
 * Reset the प्रणाली. It is called by machine_restart().
 */
अटल व्योम mxs_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (reset_addr) अणु
		/* reset the chip */
		__mxs_setl(MXS_CLKCTRL_RESET_CHIP, reset_addr);

		pr_err("Failed to assert the chip reset\n");

		/* Delay to allow the serial port to show the message */
		mdelay(50);
	पूर्ण

	/* We'll take a jump through zero as a poor second */
	soft_restart(0);
पूर्ण

अटल स्थिर अक्षर *स्थिर mxs_dt_compat[] __initस्थिर = अणु
	"fsl,imx28",
	"fsl,imx23",
	शून्य,
पूर्ण;

DT_MACHINE_START(MXS, "Freescale MXS (Device Tree)")
	.handle_irq	= icoll_handle_irq,
	.init_machine	= mxs_machine_init,
	.init_late      = mxs_pm_init,
	.dt_compat	= mxs_dt_compat,
	.restart	= mxs_restart,
MACHINE_END
