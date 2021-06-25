<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
//
// S3C series GPIO PM code

#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/gpपन.स>

#समावेश "gpio-samsung.h"

#समावेश "gpio-core.h"
#समावेश "pm.h"

/* PM GPIO helpers */

#घोषणा OFFS_CON	(0x00)
#घोषणा OFFS_DAT	(0x04)
#घोषणा OFFS_UP		(0x08)

अटल व्योम samsung_gpio_pm_1bit_save(काष्ठा samsung_gpio_chip *chip)
अणु
	chip->pm_save[0] = __raw_पढ़ोl(chip->base + OFFS_CON);
	chip->pm_save[1] = __raw_पढ़ोl(chip->base + OFFS_DAT);
पूर्ण

अटल व्योम samsung_gpio_pm_1bit_resume(काष्ठा samsung_gpio_chip *chip)
अणु
	व्योम __iomem *base = chip->base;
	u32 old_gpcon = __raw_पढ़ोl(base + OFFS_CON);
	u32 old_gpdat = __raw_पढ़ोl(base + OFFS_DAT);
	u32 gps_gpcon = chip->pm_save[0];
	u32 gps_gpdat = chip->pm_save[1];
	u32 gpcon;

	/* GPACON only has one bit per control / data and no PULLUPs.
	 * GPACON[x] = 0 => Output, 1 => SFN */

	/* first set all SFN bits to SFN */

	gpcon = old_gpcon | gps_gpcon;
	__raw_ग_लिखोl(gpcon, base + OFFS_CON);

	/* now set all the other bits */

	__raw_ग_लिखोl(gps_gpdat, base + OFFS_DAT);
	__raw_ग_लिखोl(gps_gpcon, base + OFFS_CON);

	S3C_PMDBG("%s: CON %08x => %08x, DAT %08x => %08x\n",
		  chip->chip.label, old_gpcon, gps_gpcon, old_gpdat, gps_gpdat);
पूर्ण

काष्ठा samsung_gpio_pm samsung_gpio_pm_1bit = अणु
	.save	= samsung_gpio_pm_1bit_save,
	.resume = samsung_gpio_pm_1bit_resume,
पूर्ण;

अटल व्योम samsung_gpio_pm_2bit_save(काष्ठा samsung_gpio_chip *chip)
अणु
	chip->pm_save[0] = __raw_पढ़ोl(chip->base + OFFS_CON);
	chip->pm_save[1] = __raw_पढ़ोl(chip->base + OFFS_DAT);
	chip->pm_save[2] = __raw_पढ़ोl(chip->base + OFFS_UP);
पूर्ण

/* Test whether the given masked+shअगरted bits of an GPIO configuration
 * are one of the SFN (special function) modes. */

अटल अंतरभूत पूर्णांक is_sfn(अचिन्हित दीर्घ con)
अणु
	वापस con >= 2;
पूर्ण

/* Test अगर the given masked+shअगरted GPIO configuration is an input */

अटल अंतरभूत पूर्णांक is_in(अचिन्हित दीर्घ con)
अणु
	वापस con == 0;
पूर्ण

/* Test अगर the given masked+shअगरted GPIO configuration is an output */

अटल अंतरभूत पूर्णांक is_out(अचिन्हित दीर्घ con)
अणु
	वापस con == 1;
पूर्ण

/**
 * samsung_gpio_pm_2bit_resume() - restore the given GPIO bank
 * @chip: The chip inक्रमmation to resume.
 *
 * Restore one of the GPIO banks that was saved during suspend. This is
 * not as simple as once thought, due to the possibility of glitches
 * from the order that the CON and DAT रेजिस्टरs are set in.
 *
 * The three states the pin can be are अणुIN,OUT,SFNपूर्ण which gives us 9
 * combinations of changes to check. Three of these, अगर the pin stays
 * in the same configuration can be discounted. This leaves us with
 * the following:
 *
 * अणु IN => OUT पूर्ण  Change DAT first
 * अणु IN => SFN पूर्ण  Change CON first
 * अणु OUT => SFN पूर्ण Change CON first, so new data will not glitch
 * अणु OUT => IN पूर्ण  Change CON first, so new data will not glitch
 * अणु SFN => IN पूर्ण  Change CON first
 * अणु SFN => OUT पूर्ण Change DAT first, so new data will not glitch [1]
 *
 * We करो not currently deal with the UP रेजिस्टरs as these control
 * weak resistors, so a small delay in change should not need to bring
 * these पूर्णांकo the calculations.
 *
 * [1] this assumes that writing to a pin DAT whilst in SFN will set the
 *     state क्रम when it is next output.
 */
अटल व्योम samsung_gpio_pm_2bit_resume(काष्ठा samsung_gpio_chip *chip)
अणु
	व्योम __iomem *base = chip->base;
	u32 old_gpcon = __raw_पढ़ोl(base + OFFS_CON);
	u32 old_gpdat = __raw_पढ़ोl(base + OFFS_DAT);
	u32 gps_gpcon = chip->pm_save[0];
	u32 gps_gpdat = chip->pm_save[1];
	u32 gpcon, old, new, mask;
	u32 change_mask = 0x0;
	पूर्णांक nr;

	/* restore GPIO pull-up settings */
	__raw_ग_लिखोl(chip->pm_save[2], base + OFFS_UP);

	/* Create a change_mask of all the items that need to have
	 * their CON value changed beक्रमe their DAT value, so that
	 * we minimise the work between the two settings.
	 */

	क्रम (nr = 0, mask = 0x03; nr < 32; nr += 2, mask <<= 2) अणु
		old = (old_gpcon & mask) >> nr;
		new = (gps_gpcon & mask) >> nr;

		/* If there is no change, then skip */

		अगर (old == new)
			जारी;

		/* If both are special function, then skip */

		अगर (is_sfn(old) && is_sfn(new))
			जारी;

		/* Change is IN => OUT, करो not change now */

		अगर (is_in(old) && is_out(new))
			जारी;

		/* Change is SFN => OUT, करो not change now */

		अगर (is_sfn(old) && is_out(new))
			जारी;

		/* We should now be at the हाल of IN=>SFN,
		 * OUT=>SFN, OUT=>IN, SFN=>IN. */

		change_mask |= mask;
	पूर्ण


	/* Write the new CON settings */

	gpcon = old_gpcon & ~change_mask;
	gpcon |= gps_gpcon & change_mask;

	__raw_ग_लिखोl(gpcon, base + OFFS_CON);

	/* Now change any items that require DAT,CON */

	__raw_ग_लिखोl(gps_gpdat, base + OFFS_DAT);
	__raw_ग_लिखोl(gps_gpcon, base + OFFS_CON);

	S3C_PMDBG("%s: CON %08x => %08x, DAT %08x => %08x\n",
		  chip->chip.label, old_gpcon, gps_gpcon, old_gpdat, gps_gpdat);
पूर्ण

काष्ठा samsung_gpio_pm samsung_gpio_pm_2bit = अणु
	.save	= samsung_gpio_pm_2bit_save,
	.resume = samsung_gpio_pm_2bit_resume,
पूर्ण;

#अगर defined(CONFIG_ARCH_S3C64XX)
अटल व्योम samsung_gpio_pm_4bit_save(काष्ठा samsung_gpio_chip *chip)
अणु
	chip->pm_save[1] = __raw_पढ़ोl(chip->base + OFFS_CON);
	chip->pm_save[2] = __raw_पढ़ोl(chip->base + OFFS_DAT);
	chip->pm_save[3] = __raw_पढ़ोl(chip->base + OFFS_UP);

	अगर (chip->chip.ngpio > 8)
		chip->pm_save[0] = __raw_पढ़ोl(chip->base - 4);
पूर्ण

अटल u32 samsung_gpio_pm_4bit_mask(u32 old_gpcon, u32 gps_gpcon)
अणु
	u32 old, new, mask;
	u32 change_mask = 0x0;
	पूर्णांक nr;

	क्रम (nr = 0, mask = 0x0f; nr < 16; nr += 4, mask <<= 4) अणु
		old = (old_gpcon & mask) >> nr;
		new = (gps_gpcon & mask) >> nr;

		/* If there is no change, then skip */

		अगर (old == new)
			जारी;

		/* If both are special function, then skip */

		अगर (is_sfn(old) && is_sfn(new))
			जारी;

		/* Change is IN => OUT, करो not change now */

		अगर (is_in(old) && is_out(new))
			जारी;

		/* Change is SFN => OUT, करो not change now */

		अगर (is_sfn(old) && is_out(new))
			जारी;

		/* We should now be at the हाल of IN=>SFN,
		 * OUT=>SFN, OUT=>IN, SFN=>IN. */

		change_mask |= mask;
	पूर्ण

	वापस change_mask;
पूर्ण

अटल व्योम samsung_gpio_pm_4bit_con(काष्ठा samsung_gpio_chip *chip, पूर्णांक index)
अणु
	व्योम __iomem *con = chip->base + (index * 4);
	u32 old_gpcon = __raw_पढ़ोl(con);
	u32 gps_gpcon = chip->pm_save[index + 1];
	u32 gpcon, mask;

	mask = samsung_gpio_pm_4bit_mask(old_gpcon, gps_gpcon);

	gpcon = old_gpcon & ~mask;
	gpcon |= gps_gpcon & mask;

	__raw_ग_लिखोl(gpcon, con);
पूर्ण

अटल व्योम samsung_gpio_pm_4bit_resume(काष्ठा samsung_gpio_chip *chip)
अणु
	व्योम __iomem *base = chip->base;
	u32 old_gpcon[2];
	u32 old_gpdat = __raw_पढ़ोl(base + OFFS_DAT);
	u32 gps_gpdat = chip->pm_save[2];

	/* First, modअगरy the CON settings */

	old_gpcon[0] = 0;
	old_gpcon[1] = __raw_पढ़ोl(base + OFFS_CON);

	samsung_gpio_pm_4bit_con(chip, 0);
	अगर (chip->chip.ngpio > 8) अणु
		old_gpcon[0] = __raw_पढ़ोl(base - 4);
		samsung_gpio_pm_4bit_con(chip, -1);
	पूर्ण

	/* Now change the configurations that require DAT,CON */

	__raw_ग_लिखोl(chip->pm_save[2], base + OFFS_DAT);
	__raw_ग_लिखोl(chip->pm_save[1], base + OFFS_CON);
	अगर (chip->chip.ngpio > 8)
		__raw_ग_लिखोl(chip->pm_save[0], base - 4);

	__raw_ग_लिखोl(chip->pm_save[2], base + OFFS_DAT);
	__raw_ग_लिखोl(chip->pm_save[3], base + OFFS_UP);

	अगर (chip->chip.ngpio > 8) अणु
		S3C_PMDBG("%s: CON4 %08x,%08x => %08x,%08x, DAT %08x => %08x\n",
			  chip->chip.label, old_gpcon[0], old_gpcon[1],
			  __raw_पढ़ोl(base - 4),
			  __raw_पढ़ोl(base + OFFS_CON),
			  old_gpdat, gps_gpdat);
	पूर्ण अन्यथा
		S3C_PMDBG("%s: CON4 %08x => %08x, DAT %08x => %08x\n",
			  chip->chip.label, old_gpcon[1],
			  __raw_पढ़ोl(base + OFFS_CON),
			  old_gpdat, gps_gpdat);
पूर्ण

काष्ठा samsung_gpio_pm samsung_gpio_pm_4bit = अणु
	.save	= samsung_gpio_pm_4bit_save,
	.resume = samsung_gpio_pm_4bit_resume,
पूर्ण;
#पूर्ण_अगर /* CONFIG_ARCH_S3C64XX */

/**
 * samsung_pm_save_gpio() - save gpio chip data क्रम suspend
 * @ourchip: The chip क्रम suspend.
 */
अटल व्योम samsung_pm_save_gpio(काष्ठा samsung_gpio_chip *ourchip)
अणु
	काष्ठा samsung_gpio_pm *pm = ourchip->pm;

	अगर (pm == शून्य || pm->save == शून्य)
		S3C_PMDBG("%s: no pm for %s\n", __func__, ourchip->chip.label);
	अन्यथा
		pm->save(ourchip);
पूर्ण

/**
 * samsung_pm_save_gpios() - Save the state of the GPIO banks.
 *
 * For all the GPIO banks, save the state of each one पढ़ोy क्रम going
 * पूर्णांकo a suspend mode.
 */
व्योम samsung_pm_save_gpios(व्योम)
अणु
	काष्ठा samsung_gpio_chip *ourchip;
	अचिन्हित पूर्णांक gpio_nr;

	क्रम (gpio_nr = 0; gpio_nr < S3C_GPIO_END;) अणु
		ourchip = samsung_gpiolib_अ_लोhip(gpio_nr);
		अगर (!ourchip) अणु
			gpio_nr++;
			जारी;
		पूर्ण

		samsung_pm_save_gpio(ourchip);

		S3C_PMDBG("%s: save %08x,%08x,%08x,%08x\n",
			  ourchip->chip.label,
			  ourchip->pm_save[0],
			  ourchip->pm_save[1],
			  ourchip->pm_save[2],
			  ourchip->pm_save[3]);

		gpio_nr += ourchip->chip.ngpio;
		gpio_nr += CONFIG_S3C_GPIO_SPACE;
	पूर्ण
पूर्ण

/**
 * samsung_pm_resume_gpio() - restore gpio chip data after suspend
 * @ourchip: The suspended chip.
 */
अटल व्योम samsung_pm_resume_gpio(काष्ठा samsung_gpio_chip *ourchip)
अणु
	काष्ठा samsung_gpio_pm *pm = ourchip->pm;

	अगर (pm == शून्य || pm->resume == शून्य)
		S3C_PMDBG("%s: no pm for %s\n", __func__, ourchip->chip.label);
	अन्यथा
		pm->resume(ourchip);
पूर्ण

व्योम samsung_pm_restore_gpios(व्योम)
अणु
	काष्ठा samsung_gpio_chip *ourchip;
	अचिन्हित पूर्णांक gpio_nr;

	क्रम (gpio_nr = 0; gpio_nr < S3C_GPIO_END;) अणु
		ourchip = samsung_gpiolib_अ_लोhip(gpio_nr);
		अगर (!ourchip) अणु
			gpio_nr++;
			जारी;
		पूर्ण

		samsung_pm_resume_gpio(ourchip);

		gpio_nr += ourchip->chip.ngpio;
		gpio_nr += CONFIG_S3C_GPIO_SPACE;
	पूर्ण
पूर्ण
