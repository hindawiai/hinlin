<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 2004-2008 Simtec Electronics
 *	http://armlinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung S3C2410/S3C2440/S3C2412 न_अंकD driver
*/

#घोषणा pr_fmt(fmt) "nand-s3c2410: " fmt

#अगर_घोषित CONFIG_MTD_न_अंकD_S3C2410_DEBUG
#घोषणा DEBUG
#पूर्ण_अगर

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/clk.h>
#समावेश <linux/cpufreq.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>

#घोषणा S3C2410_NFREG(x) (x)

#घोषणा S3C2410_NFCONF		S3C2410_NFREG(0x00)
#घोषणा S3C2410_NFCMD		S3C2410_NFREG(0x04)
#घोषणा S3C2410_NFADDR		S3C2410_NFREG(0x08)
#घोषणा S3C2410_NFDATA		S3C2410_NFREG(0x0C)
#घोषणा S3C2410_NFSTAT		S3C2410_NFREG(0x10)
#घोषणा S3C2410_NFECC		S3C2410_NFREG(0x14)
#घोषणा S3C2440_NFCONT		S3C2410_NFREG(0x04)
#घोषणा S3C2440_NFCMD		S3C2410_NFREG(0x08)
#घोषणा S3C2440_NFADDR		S3C2410_NFREG(0x0C)
#घोषणा S3C2440_NFDATA		S3C2410_NFREG(0x10)
#घोषणा S3C2440_NFSTAT		S3C2410_NFREG(0x20)
#घोषणा S3C2440_NFMECC0		S3C2410_NFREG(0x2C)
#घोषणा S3C2412_NFSTAT		S3C2410_NFREG(0x28)
#घोषणा S3C2412_NFMECC0		S3C2410_NFREG(0x34)
#घोषणा S3C2410_NFCONF_EN		(1<<15)
#घोषणा S3C2410_NFCONF_INITECC		(1<<12)
#घोषणा S3C2410_NFCONF_nFCE		(1<<11)
#घोषणा S3C2410_NFCONF_TACLS(x)		((x)<<8)
#घोषणा S3C2410_NFCONF_TWRPH0(x)	((x)<<4)
#घोषणा S3C2410_NFCONF_TWRPH1(x)	((x)<<0)
#घोषणा S3C2410_NFSTAT_BUSY		(1<<0)
#घोषणा S3C2440_NFCONF_TACLS(x)		((x)<<12)
#घोषणा S3C2440_NFCONF_TWRPH0(x)	((x)<<8)
#घोषणा S3C2440_NFCONF_TWRPH1(x)	((x)<<4)
#घोषणा S3C2440_NFCONT_INITECC		(1<<4)
#घोषणा S3C2440_NFCONT_nFCE		(1<<1)
#घोषणा S3C2440_NFCONT_ENABLE		(1<<0)
#घोषणा S3C2440_NFSTAT_READY		(1<<0)
#घोषणा S3C2412_NFCONF_न_अंकDBOOT		(1<<31)
#घोषणा S3C2412_NFCONT_INIT_MAIN_ECC	(1<<5)
#घोषणा S3C2412_NFCONT_nFCE0		(1<<1)
#घोषणा S3C2412_NFSTAT_READY		(1<<0)

/* new oob placement block क्रम use with hardware ecc generation
 */
अटल पूर्णांक s3c2410_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 0;
	oobregion->length = 3;

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 8;
	oobregion->length = 8;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops s3c2410_ooblayout_ops = अणु
	.ecc = s3c2410_ooblayout_ecc,
	.मुक्त = s3c2410_ooblayout_मुक्त,
पूर्ण;

/* controller and mtd inक्रमmation */

काष्ठा s3c2410_nand_info;

/**
 * काष्ठा s3c2410_nand_mtd - driver MTD काष्ठाure
 * @mtd: The MTD instance to pass to the MTD layer.
 * @chip: The न_अंकD chip inक्रमmation.
 * @set: The platक्रमm inक्रमmation supplied क्रम this set of न_अंकD chips.
 * @info: Link back to the hardware inक्रमmation.
*/
काष्ठा s3c2410_nand_mtd अणु
	काष्ठा nand_chip		chip;
	काष्ठा s3c2410_nand_set		*set;
	काष्ठा s3c2410_nand_info	*info;
पूर्ण;

क्रमागत s3c_cpu_type अणु
	TYPE_S3C2410,
	TYPE_S3C2412,
	TYPE_S3C2440,
पूर्ण;

क्रमागत s3c_nand_clk_state अणु
	CLOCK_DISABLE	= 0,
	CLOCK_ENABLE,
	CLOCK_SUSPEND,
पूर्ण;

/* overview of the s3c2410 nand state */

/**
 * काष्ठा s3c2410_nand_info - न_अंकD controller state.
 * @controller: Base controller काष्ठाure.
 * @mtds: An array of MTD instances on this controller.
 * @platक्रमm: The platक्रमm data क्रम this board.
 * @device: The platक्रमm device we bound to.
 * @clk: The घड़ी resource क्रम this controller.
 * @regs: The area mapped क्रम the hardware रेजिस्टरs.
 * @sel_reg: Poपूर्णांकer to the रेजिस्टर controlling the न_अंकD selection.
 * @sel_bit: The bit in @sel_reg to select the न_अंकD chip.
 * @mtd_count: The number of MTDs created from this controller.
 * @save_sel: The contents of @sel_reg to be saved over suspend.
 * @clk_rate: The घड़ी rate from @clk.
 * @clk_state: The current घड़ी state.
 * @cpu_type: The exact type of this controller.
 * @freq_transition: CPUFreq notअगरier block
 */
काष्ठा s3c2410_nand_info अणु
	/* mtd info */
	काष्ठा nand_controller		controller;
	काष्ठा s3c2410_nand_mtd		*mtds;
	काष्ठा s3c2410_platक्रमm_nand	*platक्रमm;

	/* device info */
	काष्ठा device			*device;
	काष्ठा clk			*clk;
	व्योम __iomem			*regs;
	व्योम __iomem			*sel_reg;
	पूर्णांक				sel_bit;
	पूर्णांक				mtd_count;
	अचिन्हित दीर्घ			save_sel;
	अचिन्हित दीर्घ			clk_rate;
	क्रमागत s3c_nand_clk_state		clk_state;

	क्रमागत s3c_cpu_type		cpu_type;

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर
पूर्ण;

काष्ठा s3c24XX_nand_devtype_data अणु
	क्रमागत s3c_cpu_type type;
पूर्ण;

अटल स्थिर काष्ठा s3c24XX_nand_devtype_data s3c2410_nand_devtype_data = अणु
	.type = TYPE_S3C2410,
पूर्ण;

अटल स्थिर काष्ठा s3c24XX_nand_devtype_data s3c2412_nand_devtype_data = अणु
	.type = TYPE_S3C2412,
पूर्ण;

अटल स्थिर काष्ठा s3c24XX_nand_devtype_data s3c2440_nand_devtype_data = अणु
	.type = TYPE_S3C2440,
पूर्ण;

/* conversion functions */

अटल काष्ठा s3c2410_nand_mtd *s3c2410_nand_mtd_toours(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd_to_nand(mtd), काष्ठा s3c2410_nand_mtd,
			    chip);
पूर्ण

अटल काष्ठा s3c2410_nand_info *s3c2410_nand_mtd_toinfo(काष्ठा mtd_info *mtd)
अणु
	वापस s3c2410_nand_mtd_toours(mtd)->info;
पूर्ण

अटल काष्ठा s3c2410_nand_info *to_nand_info(काष्ठा platक्रमm_device *dev)
अणु
	वापस platक्रमm_get_drvdata(dev);
पूर्ण

अटल काष्ठा s3c2410_platक्रमm_nand *to_nand_plat(काष्ठा platक्रमm_device *dev)
अणु
	वापस dev_get_platdata(&dev->dev);
पूर्ण

अटल अंतरभूत पूर्णांक allow_clk_suspend(काष्ठा s3c2410_nand_info *info)
अणु
#अगर_घोषित CONFIG_MTD_न_अंकD_S3C2410_CLKSTOP
	वापस 1;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

/**
 * s3c2410_nand_clk_set_state - Enable, disable or suspend न_अंकD घड़ी.
 * @info: The controller instance.
 * @new_state: State to which घड़ी should be set.
 */
अटल व्योम s3c2410_nand_clk_set_state(काष्ठा s3c2410_nand_info *info,
		क्रमागत s3c_nand_clk_state new_state)
अणु
	अगर (!allow_clk_suspend(info) && new_state == CLOCK_SUSPEND)
		वापस;

	अगर (info->clk_state == CLOCK_ENABLE) अणु
		अगर (new_state != CLOCK_ENABLE)
			clk_disable_unprepare(info->clk);
	पूर्ण अन्यथा अणु
		अगर (new_state == CLOCK_ENABLE)
			clk_prepare_enable(info->clk);
	पूर्ण

	info->clk_state = new_state;
पूर्ण

/* timing calculations */

#घोषणा NS_IN_KHZ 1000000

/**
 * s3c_nand_calc_rate - calculate timing data.
 * @wanted: The cycle समय in nanoseconds.
 * @clk: The घड़ी rate in kHz.
 * @max: The maximum भागider value.
 *
 * Calculate the timing value from the given parameters.
 */
अटल पूर्णांक s3c_nand_calc_rate(पूर्णांक wanted, अचिन्हित दीर्घ clk, पूर्णांक max)
अणु
	पूर्णांक result;

	result = DIV_ROUND_UP((wanted * clk), NS_IN_KHZ);

	pr_debug("result %d from %ld, %d\n", result, clk, wanted);

	अगर (result > max) अणु
		pr_err("%d ns is too big for current clock rate %ld\n",
			wanted, clk);
		वापस -1;
	पूर्ण

	अगर (result < 1)
		result = 1;

	वापस result;
पूर्ण

#घोषणा to_ns(ticks, clk) (((ticks) * NS_IN_KHZ) / (अचिन्हित पूर्णांक)(clk))

/* controller setup */

/**
 * s3c2410_nand_setrate - setup controller timing inक्रमmation.
 * @info: The controller instance.
 *
 * Given the inक्रमmation supplied by the platक्रमm, calculate and set
 * the necessary timing रेजिस्टरs in the hardware to generate the
 * necessary timing cycles to the hardware.
 */
अटल पूर्णांक s3c2410_nand_setrate(काष्ठा s3c2410_nand_info *info)
अणु
	काष्ठा s3c2410_platक्रमm_nand *plat = info->platक्रमm;
	पूर्णांक tacls_max = (info->cpu_type == TYPE_S3C2412) ? 8 : 4;
	पूर्णांक tacls, twrph0, twrph1;
	अचिन्हित दीर्घ clkrate = clk_get_rate(info->clk);
	अचिन्हित दीर्घ set, cfg, mask;
	अचिन्हित दीर्घ flags;

	/* calculate the timing inक्रमmation क्रम the controller */

	info->clk_rate = clkrate;
	clkrate /= 1000;	/* turn घड़ी पूर्णांकo kHz क्रम ease of use */

	अगर (plat != शून्य) अणु
		tacls = s3c_nand_calc_rate(plat->tacls, clkrate, tacls_max);
		twrph0 = s3c_nand_calc_rate(plat->twrph0, clkrate, 8);
		twrph1 = s3c_nand_calc_rate(plat->twrph1, clkrate, 8);
	पूर्ण अन्यथा अणु
		/* शेष timings */
		tacls = tacls_max;
		twrph0 = 8;
		twrph1 = 8;
	पूर्ण

	अगर (tacls < 0 || twrph0 < 0 || twrph1 < 0) अणु
		dev_err(info->device, "cannot get suitable timings\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(info->device, "Tacls=%d, %dns Twrph0=%d %dns, Twrph1=%d %dns\n",
		tacls, to_ns(tacls, clkrate), twrph0, to_ns(twrph0, clkrate),
						twrph1, to_ns(twrph1, clkrate));

	चयन (info->cpu_type) अणु
	हाल TYPE_S3C2410:
		mask = (S3C2410_NFCONF_TACLS(3) |
			S3C2410_NFCONF_TWRPH0(7) |
			S3C2410_NFCONF_TWRPH1(7));
		set = S3C2410_NFCONF_EN;
		set |= S3C2410_NFCONF_TACLS(tacls - 1);
		set |= S3C2410_NFCONF_TWRPH0(twrph0 - 1);
		set |= S3C2410_NFCONF_TWRPH1(twrph1 - 1);
		अवरोध;

	हाल TYPE_S3C2440:
	हाल TYPE_S3C2412:
		mask = (S3C2440_NFCONF_TACLS(tacls_max - 1) |
			S3C2440_NFCONF_TWRPH0(7) |
			S3C2440_NFCONF_TWRPH1(7));

		set = S3C2440_NFCONF_TACLS(tacls - 1);
		set |= S3C2440_NFCONF_TWRPH0(twrph0 - 1);
		set |= S3C2440_NFCONF_TWRPH1(twrph1 - 1);
		अवरोध;

	शेष:
		BUG();
	पूर्ण

	local_irq_save(flags);

	cfg = पढ़ोl(info->regs + S3C2410_NFCONF);
	cfg &= ~mask;
	cfg |= set;
	ग_लिखोl(cfg, info->regs + S3C2410_NFCONF);

	local_irq_restore(flags);

	dev_dbg(info->device, "NF_CONF is 0x%lx\n", cfg);

	वापस 0;
पूर्ण

/**
 * s3c2410_nand_inithw - basic hardware initialisation
 * @info: The hardware state.
 *
 * Do the basic initialisation of the hardware, using s3c2410_nand_setrate()
 * to setup the hardware access speeds and set the controller to be enabled.
*/
अटल पूर्णांक s3c2410_nand_inithw(काष्ठा s3c2410_nand_info *info)
अणु
	पूर्णांक ret;

	ret = s3c2410_nand_setrate(info);
	अगर (ret < 0)
		वापस ret;

	चयन (info->cpu_type) अणु
	हाल TYPE_S3C2410:
	शेष:
		अवरोध;

	हाल TYPE_S3C2440:
	हाल TYPE_S3C2412:
		/* enable the controller and de-निश्चित nFCE */

		ग_लिखोl(S3C2440_NFCONT_ENABLE, info->regs + S3C2440_NFCONT);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * s3c2410_nand_select_chip - select the given nand chip
 * @this: न_अंकD chip object.
 * @chip: The chip number.
 *
 * This is called by the MTD layer to either select a given chip क्रम the
 * @mtd instance, or to indicate that the access has finished and the
 * chip can be de-selected.
 *
 * The routine ensures that the nFCE line is correctly setup, and any
 * platक्रमm specअगरic selection code is called to route nFCE to the specअगरic
 * chip.
 */
अटल व्योम s3c2410_nand_select_chip(काष्ठा nand_chip *this, पूर्णांक chip)
अणु
	काष्ठा s3c2410_nand_info *info;
	काष्ठा s3c2410_nand_mtd *nmtd;
	अचिन्हित दीर्घ cur;

	nmtd = nand_get_controller_data(this);
	info = nmtd->info;

	अगर (chip != -1)
		s3c2410_nand_clk_set_state(info, CLOCK_ENABLE);

	cur = पढ़ोl(info->sel_reg);

	अगर (chip == -1) अणु
		cur |= info->sel_bit;
	पूर्ण अन्यथा अणु
		अगर (nmtd->set != शून्य && chip > nmtd->set->nr_chips) अणु
			dev_err(info->device, "invalid chip %d\n", chip);
			वापस;
		पूर्ण

		अगर (info->platक्रमm != शून्य) अणु
			अगर (info->platक्रमm->select_chip != शून्य)
				(info->platक्रमm->select_chip) (nmtd->set, chip);
		पूर्ण

		cur &= ~info->sel_bit;
	पूर्ण

	ग_लिखोl(cur, info->sel_reg);

	अगर (chip == -1)
		s3c2410_nand_clk_set_state(info, CLOCK_SUSPEND);
पूर्ण

/* s3c2410_nand_hwcontrol
 *
 * Issue command and address cycles to the chip
*/

अटल व्योम s3c2410_nand_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd,
				   अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		ग_लिखोb(cmd, info->regs + S3C2410_NFCMD);
	अन्यथा
		ग_लिखोb(cmd, info->regs + S3C2410_NFADDR);
पूर्ण

/* command and control functions */

अटल व्योम s3c2440_nand_hwcontrol(काष्ठा nand_chip *chip, पूर्णांक cmd,
				   अचिन्हित पूर्णांक ctrl)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	अगर (cmd == न_अंकD_CMD_NONE)
		वापस;

	अगर (ctrl & न_अंकD_CLE)
		ग_लिखोb(cmd, info->regs + S3C2440_NFCMD);
	अन्यथा
		ग_लिखोb(cmd, info->regs + S3C2440_NFADDR);
पूर्ण

/* s3c2410_nand_devपढ़ोy()
 *
 * वापसs 0 अगर the nand is busy, 1 अगर it is पढ़ोy
*/

अटल पूर्णांक s3c2410_nand_devपढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	वापस पढ़ोb(info->regs + S3C2410_NFSTAT) & S3C2410_NFSTAT_BUSY;
पूर्ण

अटल पूर्णांक s3c2440_nand_devपढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	वापस पढ़ोb(info->regs + S3C2440_NFSTAT) & S3C2440_NFSTAT_READY;
पूर्ण

अटल पूर्णांक s3c2412_nand_devपढ़ोy(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	वापस पढ़ोb(info->regs + S3C2412_NFSTAT) & S3C2412_NFSTAT_READY;
पूर्ण

/* ECC handling functions */

अटल पूर्णांक s3c2410_nand_correct_data(काष्ठा nand_chip *chip, u_अक्षर *dat,
				     u_अक्षर *पढ़ो_ecc, u_अक्षर *calc_ecc)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	अचिन्हित पूर्णांक dअगरf0, dअगरf1, dअगरf2;
	अचिन्हित पूर्णांक bit, byte;

	pr_debug("%s(%p,%p,%p,%p)\n", __func__, mtd, dat, पढ़ो_ecc, calc_ecc);

	dअगरf0 = पढ़ो_ecc[0] ^ calc_ecc[0];
	dअगरf1 = पढ़ो_ecc[1] ^ calc_ecc[1];
	dअगरf2 = पढ़ो_ecc[2] ^ calc_ecc[2];

	pr_debug("%s: rd %*phN calc %*phN diff %02x%02x%02x\n",
		 __func__, 3, पढ़ो_ecc, 3, calc_ecc,
		 dअगरf0, dअगरf1, dअगरf2);

	अगर (dअगरf0 == 0 && dअगरf1 == 0 && dअगरf2 == 0)
		वापस 0;		/* ECC is ok */

	/* someबार people करो not think about using the ECC, so check
	 * to see अगर we have an 0xff,0xff,0xff पढ़ो ECC and then ignore
	 * the error, on the assumption that this is an un-eccd page.
	 */
	अगर (पढ़ो_ecc[0] == 0xff && पढ़ो_ecc[1] == 0xff && पढ़ो_ecc[2] == 0xff
	    && info->platक्रमm->ignore_unset_ecc)
		वापस 0;

	/* Can we correct this ECC (ie, one row and column change).
	 * Note, this is similar to the 256 error code on smarपंचांगedia */

	अगर (((dअगरf0 ^ (dअगरf0 >> 1)) & 0x55) == 0x55 &&
	    ((dअगरf1 ^ (dअगरf1 >> 1)) & 0x55) == 0x55 &&
	    ((dअगरf2 ^ (dअगरf2 >> 1)) & 0x55) == 0x55) अणु
		/* calculate the bit position of the error */

		bit  = ((dअगरf2 >> 3) & 1) |
		       ((dअगरf2 >> 4) & 2) |
		       ((dअगरf2 >> 5) & 4);

		/* calculate the byte position of the error */

		byte = ((dअगरf2 << 7) & 0x100) |
		       ((dअगरf1 << 0) & 0x80)  |
		       ((dअगरf1 << 1) & 0x40)  |
		       ((dअगरf1 << 2) & 0x20)  |
		       ((dअगरf1 << 3) & 0x10)  |
		       ((dअगरf0 >> 4) & 0x08)  |
		       ((dअगरf0 >> 3) & 0x04)  |
		       ((dअगरf0 >> 2) & 0x02)  |
		       ((dअगरf0 >> 1) & 0x01);

		dev_dbg(info->device, "correcting error bit %d, byte %d\n",
			bit, byte);

		dat[byte] ^= (1 << bit);
		वापस 1;
	पूर्ण

	/* अगर there is only one bit dअगरference in the ECC, then
	 * one of only a row or column parity has changed, which
	 * means the error is most probably in the ECC itself */

	dअगरf0 |= (dअगरf1 << 8);
	dअगरf0 |= (dअगरf2 << 16);

	/* equal to "(diff0 & ~(1 << __ffs(diff0)))" */
	अगर ((dअगरf0 & (dअगरf0 - 1)) == 0)
		वापस 1;

	वापस -1;
पूर्ण

/* ECC functions
 *
 * These allow the s3c2410 and s3c2440 to use the controller's ECC
 * generator block to ECC the data as it passes through]
*/

अटल व्योम s3c2410_nand_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा s3c2410_nand_info *info;
	अचिन्हित दीर्घ ctrl;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctrl = पढ़ोl(info->regs + S3C2410_NFCONF);
	ctrl |= S3C2410_NFCONF_INITECC;
	ग_लिखोl(ctrl, info->regs + S3C2410_NFCONF);
पूर्ण

अटल व्योम s3c2412_nand_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा s3c2410_nand_info *info;
	अचिन्हित दीर्घ ctrl;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctrl = पढ़ोl(info->regs + S3C2440_NFCONT);
	ग_लिखोl(ctrl | S3C2412_NFCONT_INIT_MAIN_ECC,
	       info->regs + S3C2440_NFCONT);
पूर्ण

अटल व्योम s3c2440_nand_enable_hwecc(काष्ठा nand_chip *chip, पूर्णांक mode)
अणु
	काष्ठा s3c2410_nand_info *info;
	अचिन्हित दीर्घ ctrl;

	info = s3c2410_nand_mtd_toinfo(nand_to_mtd(chip));
	ctrl = पढ़ोl(info->regs + S3C2440_NFCONT);
	ग_लिखोl(ctrl | S3C2440_NFCONT_INITECC, info->regs + S3C2440_NFCONT);
पूर्ण

अटल पूर्णांक s3c2410_nand_calculate_ecc(काष्ठा nand_chip *chip,
				      स्थिर u_अक्षर *dat, u_अक्षर *ecc_code)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	ecc_code[0] = पढ़ोb(info->regs + S3C2410_NFECC + 0);
	ecc_code[1] = पढ़ोb(info->regs + S3C2410_NFECC + 1);
	ecc_code[2] = पढ़ोb(info->regs + S3C2410_NFECC + 2);

	pr_debug("%s: returning ecc %*phN\n", __func__, 3, ecc_code);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2412_nand_calculate_ecc(काष्ठा nand_chip *chip,
				      स्थिर u_अक्षर *dat, u_अक्षर *ecc_code)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	अचिन्हित दीर्घ ecc = पढ़ोl(info->regs + S3C2412_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pr_debug("%s: returning ecc %*phN\n", __func__, 3, ecc_code);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2440_nand_calculate_ecc(काष्ठा nand_chip *chip,
				      स्थिर u_अक्षर *dat, u_अक्षर *ecc_code)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	अचिन्हित दीर्घ ecc = पढ़ोl(info->regs + S3C2440_NFMECC0);

	ecc_code[0] = ecc;
	ecc_code[1] = ecc >> 8;
	ecc_code[2] = ecc >> 16;

	pr_debug("%s: returning ecc %06lx\n", __func__, ecc & 0xffffff);

	वापस 0;
पूर्ण

/* over-ride the standard functions क्रम a little more speed. We can
 * use पढ़ो/ग_लिखो block to move the data buffers to/from the controller
*/

अटल व्योम s3c2410_nand_पढ़ो_buf(काष्ठा nand_chip *this, u_अक्षर *buf, पूर्णांक len)
अणु
	पढ़ोsb(this->legacy.IO_ADDR_R, buf, len);
पूर्ण

अटल व्योम s3c2440_nand_पढ़ो_buf(काष्ठा nand_chip *this, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	पढ़ोsl(info->regs + S3C2440_NFDATA, buf, len >> 2);

	/* cleanup अगर we've got less than a word to करो */
	अगर (len & 3) अणु
		buf += len & ~3;

		क्रम (; len & 3; len--)
			*buf++ = पढ़ोb(info->regs + S3C2440_NFDATA);
	पूर्ण
पूर्ण

अटल व्योम s3c2410_nand_ग_लिखो_buf(काष्ठा nand_chip *this, स्थिर u_अक्षर *buf,
				   पूर्णांक len)
अणु
	ग_लिखोsb(this->legacy.IO_ADDR_W, buf, len);
पूर्ण

अटल व्योम s3c2440_nand_ग_लिखो_buf(काष्ठा nand_chip *this, स्थिर u_अक्षर *buf,
				   पूर्णांक len)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(this);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	ग_लिखोsl(info->regs + S3C2440_NFDATA, buf, len >> 2);

	/* cleanup any fractional ग_लिखो */
	अगर (len & 3) अणु
		buf += len & ~3;

		क्रम (; len & 3; len--, buf++)
			ग_लिखोb(*buf, info->regs + S3C2440_NFDATA);
	पूर्ण
पूर्ण

/* cpufreq driver support */

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ

अटल पूर्णांक s3c2410_nand_cpufreq_transition(काष्ठा notअगरier_block *nb,
					  अचिन्हित दीर्घ val, व्योम *data)
अणु
	काष्ठा s3c2410_nand_info *info;
	अचिन्हित दीर्घ newclk;

	info = container_of(nb, काष्ठा s3c2410_nand_info, freq_transition);
	newclk = clk_get_rate(info->clk);

	अगर ((val == CPUFREQ_POSTCHANGE && newclk < info->clk_rate) ||
	    (val == CPUFREQ_PRECHANGE && newclk > info->clk_rate)) अणु
		s3c2410_nand_setrate(info);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक s3c2410_nand_cpufreq_रेजिस्टर(काष्ठा s3c2410_nand_info *info)
अणु
	info->freq_transition.notअगरier_call = s3c2410_nand_cpufreq_transition;

	वापस cpufreq_रेजिस्टर_notअगरier(&info->freq_transition,
					 CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

अटल अंतरभूत व्योम
s3c2410_nand_cpufreq_deरेजिस्टर(काष्ठा s3c2410_nand_info *info)
अणु
	cpufreq_unरेजिस्टर_notअगरier(&info->freq_transition,
				    CPUFREQ_TRANSITION_NOTIFIER);
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक s3c2410_nand_cpufreq_रेजिस्टर(काष्ठा s3c2410_nand_info *info)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
s3c2410_nand_cpufreq_deरेजिस्टर(काष्ठा s3c2410_nand_info *info)
अणु
पूर्ण
#पूर्ण_अगर

/* device management functions */

अटल पूर्णांक s3c24xx_nand_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_nand_info *info = to_nand_info(pdev);

	अगर (info == शून्य)
		वापस 0;

	s3c2410_nand_cpufreq_deरेजिस्टर(info);

	/* Release all our mtds  and their partitions, then go through
	 * मुक्तing the resources used
	 */

	अगर (info->mtds != शून्य) अणु
		काष्ठा s3c2410_nand_mtd *ptr = info->mtds;
		पूर्णांक mtdno;

		क्रम (mtdno = 0; mtdno < info->mtd_count; mtdno++, ptr++) अणु
			pr_debug("releasing mtd %d (%p)\n", mtdno, ptr);
			WARN_ON(mtd_device_unरेजिस्टर(nand_to_mtd(&ptr->chip)));
			nand_cleanup(&ptr->chip);
		पूर्ण
	पूर्ण

	/* मुक्त the common resources */

	अगर (!IS_ERR(info->clk))
		s3c2410_nand_clk_set_state(info, CLOCK_DISABLE);

	वापस 0;
पूर्ण

अटल पूर्णांक s3c2410_nand_add_partition(काष्ठा s3c2410_nand_info *info,
				      काष्ठा s3c2410_nand_mtd *mtd,
				      काष्ठा s3c2410_nand_set *set)
अणु
	अगर (set) अणु
		काष्ठा mtd_info *mtdinfo = nand_to_mtd(&mtd->chip);

		mtdinfo->name = set->name;

		वापस mtd_device_रेजिस्टर(mtdinfo, set->partitions,
					   set->nr_partitions);
	पूर्ण

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक s3c2410_nand_setup_पूर्णांकerface(काष्ठा nand_chip *chip, पूर्णांक csline,
					स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);
	काष्ठा s3c2410_platक्रमm_nand *pdata = info->platक्रमm;
	स्थिर काष्ठा nand_sdr_timings *timings;
	पूर्णांक tacls;

	timings = nand_get_sdr_timings(conf);
	अगर (IS_ERR(timings))
		वापस -ENOTSUPP;

	tacls = timings->tCLS_min - timings->tWP_min;
	अगर (tacls < 0)
		tacls = 0;

	pdata->tacls  = DIV_ROUND_UP(tacls, 1000);
	pdata->twrph0 = DIV_ROUND_UP(timings->tWP_min, 1000);
	pdata->twrph1 = DIV_ROUND_UP(timings->tCLH_min, 1000);

	वापस s3c2410_nand_setrate(info);
पूर्ण

/**
 * s3c2410_nand_init_chip - initialise a single instance of an chip
 * @info: The base न_अंकD controller the chip is on.
 * @nmtd: The new controller MTD instance to fill in.
 * @set: The inक्रमmation passed from the board specअगरic platक्रमm data.
 *
 * Initialise the given @nmtd from the inक्रमmation in @info and @set. This
 * पढ़ोies the काष्ठाure क्रम use with the MTD layer functions by ensuring
 * all poपूर्णांकers are setup and the necessary control routines selected.
 */
अटल व्योम s3c2410_nand_init_chip(काष्ठा s3c2410_nand_info *info,
				   काष्ठा s3c2410_nand_mtd *nmtd,
				   काष्ठा s3c2410_nand_set *set)
अणु
	काष्ठा device_node *np = info->device->of_node;
	काष्ठा nand_chip *chip = &nmtd->chip;
	व्योम __iomem *regs = info->regs;

	nand_set_flash_node(chip, set->of_node);

	chip->legacy.ग_लिखो_buf    = s3c2410_nand_ग_लिखो_buf;
	chip->legacy.पढ़ो_buf     = s3c2410_nand_पढ़ो_buf;
	chip->legacy.select_chip  = s3c2410_nand_select_chip;
	chip->legacy.chip_delay   = 50;
	nand_set_controller_data(chip, nmtd);
	chip->options	   = set->options;
	chip->controller   = &info->controller;

	/*
	 * let's keep behavior unchanged क्रम legacy boards booting via pdata and
	 * स्वतः-detect timings only when booting with a device tree.
	 */
	अगर (!np)
		chip->options |= न_अंकD_KEEP_TIMINGS;

	चयन (info->cpu_type) अणु
	हाल TYPE_S3C2410:
		chip->legacy.IO_ADDR_W = regs + S3C2410_NFDATA;
		info->sel_reg   = regs + S3C2410_NFCONF;
		info->sel_bit	= S3C2410_NFCONF_nFCE;
		chip->legacy.cmd_ctrl  = s3c2410_nand_hwcontrol;
		chip->legacy.dev_पढ़ोy = s3c2410_nand_devपढ़ोy;
		अवरोध;

	हाल TYPE_S3C2440:
		chip->legacy.IO_ADDR_W = regs + S3C2440_NFDATA;
		info->sel_reg   = regs + S3C2440_NFCONT;
		info->sel_bit	= S3C2440_NFCONT_nFCE;
		chip->legacy.cmd_ctrl  = s3c2440_nand_hwcontrol;
		chip->legacy.dev_पढ़ोy = s3c2440_nand_devपढ़ोy;
		chip->legacy.पढ़ो_buf  = s3c2440_nand_पढ़ो_buf;
		chip->legacy.ग_लिखो_buf	= s3c2440_nand_ग_लिखो_buf;
		अवरोध;

	हाल TYPE_S3C2412:
		chip->legacy.IO_ADDR_W = regs + S3C2440_NFDATA;
		info->sel_reg   = regs + S3C2440_NFCONT;
		info->sel_bit	= S3C2412_NFCONT_nFCE0;
		chip->legacy.cmd_ctrl  = s3c2440_nand_hwcontrol;
		chip->legacy.dev_पढ़ोy = s3c2412_nand_devपढ़ोy;

		अगर (पढ़ोl(regs + S3C2410_NFCONF) & S3C2412_NFCONF_न_अंकDBOOT)
			dev_info(info->device, "System booted from NAND\n");

		अवरोध;
	पूर्ण

	chip->legacy.IO_ADDR_R = chip->legacy.IO_ADDR_W;

	nmtd->info	   = info;
	nmtd->set	   = set;

	chip->ecc.engine_type = info->platक्रमm->engine_type;

	/*
	 * If you use u-boot BBT creation code, specअगरying this flag will
	 * let the kernel fish out the BBT from the न_अंकD.
	 */
	अगर (set->flash_bbt)
		chip->bbt_options |= न_अंकD_BBT_USE_FLASH;
पूर्ण

/**
 * s3c2410_nand_attach_chip - Init the ECC engine after न_अंकD scan
 * @chip: The न_अंकD chip
 *
 * This hook is called by the core after the identअगरication of the न_अंकD chip,
 * once the relevant per-chip inक्रमmation is up to date.. This call ensure that
 * we update the पूर्णांकernal state accordingly.
 *
 * The पूर्णांकernal state is currently limited to the ECC state inक्रमmation.
*/
अटल पूर्णांक s3c2410_nand_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा s3c2410_nand_info *info = s3c2410_nand_mtd_toinfo(mtd);

	चयन (chip->ecc.engine_type) अणु

	हाल न_अंकD_ECC_ENGINE_TYPE_NONE:
		dev_info(info->device, "ECC disabled\n");
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_SOFT:
		/*
		 * This driver expects Hamming based ECC when engine_type is set
		 * to न_अंकD_ECC_ENGINE_TYPE_SOFT. Force ecc.algo to
		 * न_अंकD_ECC_ALGO_HAMMING to aव्योम adding an extra ecc_algo field
		 * to s3c2410_platक्रमm_nand.
		 */
		chip->ecc.algo = न_अंकD_ECC_ALGO_HAMMING;
		dev_info(info->device, "soft ECC\n");
		अवरोध;

	हाल न_अंकD_ECC_ENGINE_TYPE_ON_HOST:
		chip->ecc.calculate = s3c2410_nand_calculate_ecc;
		chip->ecc.correct   = s3c2410_nand_correct_data;
		chip->ecc.strength  = 1;

		चयन (info->cpu_type) अणु
		हाल TYPE_S3C2410:
			chip->ecc.hwctl	    = s3c2410_nand_enable_hwecc;
			chip->ecc.calculate = s3c2410_nand_calculate_ecc;
			अवरोध;

		हाल TYPE_S3C2412:
			chip->ecc.hwctl     = s3c2412_nand_enable_hwecc;
			chip->ecc.calculate = s3c2412_nand_calculate_ecc;
			अवरोध;

		हाल TYPE_S3C2440:
			chip->ecc.hwctl     = s3c2440_nand_enable_hwecc;
			chip->ecc.calculate = s3c2440_nand_calculate_ecc;
			अवरोध;
		पूर्ण

		dev_dbg(info->device, "chip %p => page shift %d\n",
			chip, chip->page_shअगरt);

		/* change the behaviour depending on whether we are using
		 * the large or small page nand device */
		अगर (chip->page_shअगरt > 10) अणु
			chip->ecc.size	    = 256;
			chip->ecc.bytes	    = 3;
		पूर्ण अन्यथा अणु
			chip->ecc.size	    = 512;
			chip->ecc.bytes	    = 3;
			mtd_set_ooblayout(nand_to_mtd(chip),
					  &s3c2410_ooblayout_ops);
		पूर्ण

		dev_info(info->device, "hardware ECC\n");
		अवरोध;

	शेष:
		dev_err(info->device, "invalid ECC mode!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (chip->bbt_options & न_अंकD_BBT_USE_FLASH)
		chip->options |= न_अंकD_SKIP_BBTSCAN;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops s3c24xx_nand_controller_ops = अणु
	.attach_chip = s3c2410_nand_attach_chip,
	.setup_पूर्णांकerface = s3c2410_nand_setup_पूर्णांकerface,
पूर्ण;

अटल स्थिर काष्ठा of_device_id s3c24xx_nand_dt_ids[] = अणु
	अणु
		.compatible = "samsung,s3c2410-nand",
		.data = &s3c2410_nand_devtype_data,
	पूर्ण, अणु
		/* also compatible with s3c6400 */
		.compatible = "samsung,s3c2412-nand",
		.data = &s3c2412_nand_devtype_data,
	पूर्ण, अणु
		.compatible = "samsung,s3c2440-nand",
		.data = &s3c2440_nand_devtype_data,
	पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, s3c24xx_nand_dt_ids);

अटल पूर्णांक s3c24xx_nand_probe_dt(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा s3c24XX_nand_devtype_data *devtype_data;
	काष्ठा s3c2410_platक्रमm_nand *pdata;
	काष्ठा s3c2410_nand_info *info = platक्रमm_get_drvdata(pdev);
	काष्ठा device_node *np = pdev->dev.of_node, *child;
	काष्ठा s3c2410_nand_set *sets;

	devtype_data = of_device_get_match_data(&pdev->dev);
	अगर (!devtype_data)
		वापस -ENODEV;

	info->cpu_type = devtype_data->type;

	pdata = devm_kzalloc(&pdev->dev, माप(*pdata), GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	pdev->dev.platक्रमm_data = pdata;

	pdata->nr_sets = of_get_child_count(np);
	अगर (!pdata->nr_sets)
		वापस 0;

	sets = devm_kसुस्मृति(&pdev->dev, pdata->nr_sets, माप(*sets),
			    GFP_KERNEL);
	अगर (!sets)
		वापस -ENOMEM;

	pdata->sets = sets;

	क्रम_each_available_child_of_node(np, child) अणु
		sets->name = (अक्षर *)child->name;
		sets->of_node = child;
		sets->nr_chips = 1;

		of_node_get(child);

		sets++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_nand_probe_pdata(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_nand_info *info = platक्रमm_get_drvdata(pdev);

	info->cpu_type = platक्रमm_get_device_id(pdev)->driver_data;

	वापस 0;
पूर्ण

/* s3c24xx_nand_probe
 *
 * called by device layer when it finds a device matching
 * one our driver can handled. This code checks to see अगर
 * it can allocate all necessary resources then calls the
 * nand layer to look क्रम devices
*/
अटल पूर्णांक s3c24xx_nand_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा s3c2410_platक्रमm_nand *plat;
	काष्ठा s3c2410_nand_info *info;
	काष्ठा s3c2410_nand_mtd *nmtd;
	काष्ठा s3c2410_nand_set *sets;
	काष्ठा resource *res;
	पूर्णांक err = 0;
	पूर्णांक size;
	पूर्णांक nr_sets;
	पूर्णांक setno;

	info = devm_kzalloc(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (info == शून्य) अणु
		err = -ENOMEM;
		जाओ निकास_error;
	पूर्ण

	platक्रमm_set_drvdata(pdev, info);

	nand_controller_init(&info->controller);
	info->controller.ops = &s3c24xx_nand_controller_ops;

	/* get the घड़ी source and enable it */

	info->clk = devm_clk_get(&pdev->dev, "nand");
	अगर (IS_ERR(info->clk)) अणु
		dev_err(&pdev->dev, "failed to get clock\n");
		err = -ENOENT;
		जाओ निकास_error;
	पूर्ण

	s3c2410_nand_clk_set_state(info, CLOCK_ENABLE);

	अगर (pdev->dev.of_node)
		err = s3c24xx_nand_probe_dt(pdev);
	अन्यथा
		err = s3c24xx_nand_probe_pdata(pdev);

	अगर (err)
		जाओ निकास_error;

	plat = to_nand_plat(pdev);

	/* allocate and map the resource */

	/* currently we assume we have the one resource */
	res = pdev->resource;
	size = resource_size(res);

	info->device	= &pdev->dev;
	info->platक्रमm	= plat;

	info->regs = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(info->regs)) अणु
		err = PTR_ERR(info->regs);
		जाओ निकास_error;
	पूर्ण

	dev_dbg(&pdev->dev, "mapped registers at %p\n", info->regs);

	अगर (!plat->sets || plat->nr_sets < 1) अणु
		err = -EINVAL;
		जाओ निकास_error;
	पूर्ण

	sets = plat->sets;
	nr_sets = plat->nr_sets;

	info->mtd_count = nr_sets;

	/* allocate our inक्रमmation */

	size = nr_sets * माप(*info->mtds);
	info->mtds = devm_kzalloc(&pdev->dev, size, GFP_KERNEL);
	अगर (info->mtds == शून्य) अणु
		err = -ENOMEM;
		जाओ निकास_error;
	पूर्ण

	/* initialise all possible chips */

	nmtd = info->mtds;

	क्रम (setno = 0; setno < nr_sets; setno++, nmtd++, sets++) अणु
		काष्ठा mtd_info *mtd = nand_to_mtd(&nmtd->chip);

		pr_debug("initialising set %d (%p, info %p)\n",
			 setno, nmtd, info);

		mtd->dev.parent = &pdev->dev;
		s3c2410_nand_init_chip(info, nmtd, sets);

		err = nand_scan(&nmtd->chip, sets ? sets->nr_chips : 1);
		अगर (err)
			जाओ निकास_error;

		s3c2410_nand_add_partition(info, nmtd, sets);
	पूर्ण

	/* initialise the hardware */
	err = s3c2410_nand_inithw(info);
	अगर (err != 0)
		जाओ निकास_error;

	err = s3c2410_nand_cpufreq_रेजिस्टर(info);
	अगर (err < 0) अणु
		dev_err(&pdev->dev, "failed to init cpufreq support\n");
		जाओ निकास_error;
	पूर्ण

	अगर (allow_clk_suspend(info)) अणु
		dev_info(&pdev->dev, "clock idle support enabled\n");
		s3c2410_nand_clk_set_state(info, CLOCK_SUSPEND);
	पूर्ण

	वापस 0;

 निकास_error:
	s3c24xx_nand_हटाओ(pdev);

	अगर (err == 0)
		err = -EINVAL;
	वापस err;
पूर्ण

/* PM Support */
#अगर_घोषित CONFIG_PM

अटल पूर्णांक s3c24xx_nand_suspend(काष्ठा platक्रमm_device *dev, pm_message_t pm)
अणु
	काष्ठा s3c2410_nand_info *info = platक्रमm_get_drvdata(dev);

	अगर (info) अणु
		info->save_sel = पढ़ोl(info->sel_reg);

		/* For the moment, we must ensure nFCE is high during
		 * the समय we are suspended. This really should be
		 * handled by suspending the MTDs we are using, but
		 * that is currently not the हाल. */

		ग_लिखोl(info->save_sel | info->sel_bit, info->sel_reg);

		s3c2410_nand_clk_set_state(info, CLOCK_DISABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s3c24xx_nand_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा s3c2410_nand_info *info = platक्रमm_get_drvdata(dev);
	अचिन्हित दीर्घ sel;

	अगर (info) अणु
		s3c2410_nand_clk_set_state(info, CLOCK_ENABLE);
		s3c2410_nand_inithw(info);

		/* Restore the state of the nFCE line. */

		sel = पढ़ोl(info->sel_reg);
		sel &= ~info->sel_bit;
		sel |= info->save_sel & info->sel_bit;
		ग_लिखोl(sel, info->sel_reg);

		s3c2410_nand_clk_set_state(info, CLOCK_SUSPEND);
	पूर्ण

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा s3c24xx_nand_suspend शून्य
#घोषणा s3c24xx_nand_resume शून्य
#पूर्ण_अगर

/* driver device registration */

अटल स्थिर काष्ठा platक्रमm_device_id s3c24xx_driver_ids[] = अणु
	अणु
		.name		= "s3c2410-nand",
		.driver_data	= TYPE_S3C2410,
	पूर्ण, अणु
		.name		= "s3c2440-nand",
		.driver_data	= TYPE_S3C2440,
	पूर्ण, अणु
		.name		= "s3c2412-nand",
		.driver_data	= TYPE_S3C2412,
	पूर्ण, अणु
		.name		= "s3c6400-nand",
		.driver_data	= TYPE_S3C2412, /* compatible with 2412 */
	पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(platक्रमm, s3c24xx_driver_ids);

अटल काष्ठा platक्रमm_driver s3c24xx_nand_driver = अणु
	.probe		= s3c24xx_nand_probe,
	.हटाओ		= s3c24xx_nand_हटाओ,
	.suspend	= s3c24xx_nand_suspend,
	.resume		= s3c24xx_nand_resume,
	.id_table	= s3c24xx_driver_ids,
	.driver		= अणु
		.name	= "s3c24xx-nand",
		.of_match_table = s3c24xx_nand_dt_ids,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(s3c24xx_nand_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ben Dooks <ben@simtec.co.uk>");
MODULE_DESCRIPTION("S3C24XX MTD NAND driver");
