<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/sdio.c
 *
 *  Copyright 2006-2007 Pierre Ossman
 */

#समावेश <linux/err.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_func.h>
#समावेश <linux/mmc/sdio_ids.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "bus.h"
#समावेश "quirks.h"
#समावेश "sd.h"
#समावेश "sdio_bus.h"
#समावेश "mmc_ops.h"
#समावेश "sd_ops.h"
#समावेश "sdio_ops.h"
#समावेश "sdio_cis.h"

MMC_DEV_ATTR(venकरोr, "0x%04x\n", card->cis.venकरोr);
MMC_DEV_ATTR(device, "0x%04x\n", card->cis.device);
MMC_DEV_ATTR(revision, "%u.%u\n", card->major_rev, card->minor_rev);
MMC_DEV_ATTR(ocr, "0x%08x\n", card->ocr);
MMC_DEV_ATTR(rca, "0x%04x\n", card->rca);

#घोषणा sdio_info_attr(num)									\
अटल sमाप_प्रकार info##num##_show(काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु												\
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);						\
												\
	अगर (num > card->num_info)								\
		वापस -ENODATA;								\
	अगर (!card->info[num-1][0])								\
		वापस 0;									\
	वापस प्र_लिखो(buf, "%s\n", card->info[num-1]);						\
पूर्ण												\
अटल DEVICE_ATTR_RO(info##num)

sdio_info_attr(1);
sdio_info_attr(2);
sdio_info_attr(3);
sdio_info_attr(4);

अटल काष्ठा attribute *sdio_std_attrs[] = अणु
	&dev_attr_venकरोr.attr,
	&dev_attr_device.attr,
	&dev_attr_revision.attr,
	&dev_attr_info1.attr,
	&dev_attr_info2.attr,
	&dev_attr_info3.attr,
	&dev_attr_info4.attr,
	&dev_attr_ocr.attr,
	&dev_attr_rca.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(sdio_std);

अटल काष्ठा device_type sdio_type = अणु
	.groups = sdio_std_groups,
पूर्ण;

अटल पूर्णांक sdio_पढ़ो_fbr(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर data;

	अगर (mmc_card_nonstd_func_पूर्णांकerface(func->card)) अणु
		func->class = SDIO_CLASS_NONE;
		वापस 0;
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 0, 0,
		SDIO_FBR_BASE(func->num) + SDIO_FBR_STD_IF, 0, &data);
	अगर (ret)
		जाओ out;

	data &= 0x0f;

	अगर (data == 0x0f) अणु
		ret = mmc_io_rw_direct(func->card, 0, 0,
			SDIO_FBR_BASE(func->num) + SDIO_FBR_STD_IF_EXT, 0, &data);
		अगर (ret)
			जाओ out;
	पूर्ण

	func->class = data;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक sdio_init_func(काष्ठा mmc_card *card, अचिन्हित पूर्णांक fn)
अणु
	पूर्णांक ret;
	काष्ठा sdio_func *func;

	अगर (WARN_ON(fn > SDIO_MAX_FUNCS))
		वापस -EINVAL;

	func = sdio_alloc_func(card);
	अगर (IS_ERR(func))
		वापस PTR_ERR(func);

	func->num = fn;

	अगर (!(card->quirks & MMC_QUIRK_NONSTD_SDIO)) अणु
		ret = sdio_पढ़ो_fbr(func);
		अगर (ret)
			जाओ fail;

		ret = sdio_पढ़ो_func_cis(func);
		अगर (ret)
			जाओ fail;
	पूर्ण अन्यथा अणु
		func->venकरोr = func->card->cis.venकरोr;
		func->device = func->card->cis.device;
		func->max_blksize = func->card->cis.blksize;
	पूर्ण

	card->sdio_func[fn - 1] = func;

	वापस 0;

fail:
	/*
	 * It is okay to हटाओ the function here even though we hold
	 * the host lock as we haven't रेजिस्टरed the device yet.
	 */
	sdio_हटाओ_func(func);
	वापस ret;
पूर्ण

अटल पूर्णांक sdio_पढ़ो_cccr(काष्ठा mmc_card *card, u32 ocr)
अणु
	पूर्णांक ret;
	पूर्णांक cccr_vsn;
	पूर्णांक uhs = ocr & R4_18V_PRESENT;
	अचिन्हित अक्षर data;
	अचिन्हित अक्षर speed;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_CCCR, 0, &data);
	अगर (ret)
		जाओ out;

	cccr_vsn = data & 0x0f;

	अगर (cccr_vsn > SDIO_CCCR_REV_3_00) अणु
		pr_err("%s: unrecognised CCCR structure version %d\n",
			mmc_hostname(card->host), cccr_vsn);
		वापस -EINVAL;
	पूर्ण

	card->cccr.sdio_vsn = (data & 0xf0) >> 4;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_CAPS, 0, &data);
	अगर (ret)
		जाओ out;

	अगर (data & SDIO_CCCR_CAP_SMB)
		card->cccr.multi_block = 1;
	अगर (data & SDIO_CCCR_CAP_LSC)
		card->cccr.low_speed = 1;
	अगर (data & SDIO_CCCR_CAP_4BLS)
		card->cccr.wide_bus = 1;

	अगर (cccr_vsn >= SDIO_CCCR_REV_1_10) अणु
		ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_POWER, 0, &data);
		अगर (ret)
			जाओ out;

		अगर (data & SDIO_POWER_SMPC)
			card->cccr.high_घातer = 1;
	पूर्ण

	अगर (cccr_vsn >= SDIO_CCCR_REV_1_20) अणु
		ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_SPEED, 0, &speed);
		अगर (ret)
			जाओ out;

		card->scr.sda_spec3 = 0;
		card->sw_caps.sd3_bus_mode = 0;
		card->sw_caps.sd3_drv_type = 0;
		अगर (cccr_vsn >= SDIO_CCCR_REV_3_00 && uhs) अणु
			card->scr.sda_spec3 = 1;
			ret = mmc_io_rw_direct(card, 0, 0,
				SDIO_CCCR_UHS, 0, &data);
			अगर (ret)
				जाओ out;

			अगर (mmc_host_uhs(card->host)) अणु
				अगर (data & SDIO_UHS_DDR50)
					card->sw_caps.sd3_bus_mode
						|= SD_MODE_UHS_DDR50 | SD_MODE_UHS_SDR50
							| SD_MODE_UHS_SDR25 | SD_MODE_UHS_SDR12;

				अगर (data & SDIO_UHS_SDR50)
					card->sw_caps.sd3_bus_mode
						|= SD_MODE_UHS_SDR50 | SD_MODE_UHS_SDR25
							| SD_MODE_UHS_SDR12;

				अगर (data & SDIO_UHS_SDR104)
					card->sw_caps.sd3_bus_mode
						|= SD_MODE_UHS_SDR104 | SD_MODE_UHS_SDR50
							| SD_MODE_UHS_SDR25 | SD_MODE_UHS_SDR12;
			पूर्ण

			ret = mmc_io_rw_direct(card, 0, 0,
				SDIO_CCCR_DRIVE_STRENGTH, 0, &data);
			अगर (ret)
				जाओ out;

			अगर (data & SDIO_DRIVE_SDTA)
				card->sw_caps.sd3_drv_type |= SD_DRIVER_TYPE_A;
			अगर (data & SDIO_DRIVE_SDTC)
				card->sw_caps.sd3_drv_type |= SD_DRIVER_TYPE_C;
			अगर (data & SDIO_DRIVE_SDTD)
				card->sw_caps.sd3_drv_type |= SD_DRIVER_TYPE_D;
		पूर्ण

		/* अगर no uhs mode ensure we check क्रम high speed */
		अगर (!card->sw_caps.sd3_bus_mode) अणु
			अगर (speed & SDIO_SPEED_SHS) अणु
				card->cccr.high_speed = 1;
				card->sw_caps.hs_max_dtr = 50000000;
			पूर्ण अन्यथा अणु
				card->cccr.high_speed = 0;
				card->sw_caps.hs_max_dtr = 25000000;
			पूर्ण
		पूर्ण
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक sdio_enable_wide(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;
	u8 ctrl;

	अगर (!(card->host->caps & MMC_CAP_4_BIT_DATA))
		वापस 0;

	अगर (card->cccr.low_speed && !card->cccr.wide_bus)
		वापस 0;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_IF, 0, &ctrl);
	अगर (ret)
		वापस ret;

	अगर ((ctrl & SDIO_BUS_WIDTH_MASK) == SDIO_BUS_WIDTH_RESERVED)
		pr_warn("%s: SDIO_CCCR_IF is invalid: 0x%02x\n",
			mmc_hostname(card->host), ctrl);

	/* set as 4-bit bus width */
	ctrl &= ~SDIO_BUS_WIDTH_MASK;
	ctrl |= SDIO_BUS_WIDTH_4BIT;

	ret = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_IF, ctrl, शून्य);
	अगर (ret)
		वापस ret;

	वापस 1;
पूर्ण

/*
 * If desired, disconnect the pull-up resistor on CD/DAT[3] (pin 1)
 * of the card. This may be required on certain setups of boards,
 * controllers and embedded sdio device which करो not need the card's
 * pull-up. As a result, card detection is disabled and घातer is saved.
 */
अटल पूर्णांक sdio_disable_cd(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;
	u8 ctrl;

	अगर (!mmc_card_disable_cd(card))
		वापस 0;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_IF, 0, &ctrl);
	अगर (ret)
		वापस ret;

	ctrl |= SDIO_BUS_CD_DISABLE;

	वापस mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_IF, ctrl, शून्य);
पूर्ण

/*
 * Devices that reमुख्य active during a प्रणाली suspend are
 * put back पूर्णांकo 1-bit mode.
 */
अटल पूर्णांक sdio_disable_wide(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;
	u8 ctrl;

	अगर (!(card->host->caps & MMC_CAP_4_BIT_DATA))
		वापस 0;

	अगर (card->cccr.low_speed && !card->cccr.wide_bus)
		वापस 0;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_IF, 0, &ctrl);
	अगर (ret)
		वापस ret;

	अगर (!(ctrl & SDIO_BUS_WIDTH_4BIT))
		वापस 0;

	ctrl &= ~SDIO_BUS_WIDTH_4BIT;
	ctrl |= SDIO_BUS_ASYNC_INT;

	ret = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_IF, ctrl, शून्य);
	अगर (ret)
		वापस ret;

	mmc_set_bus_width(card->host, MMC_BUS_WIDTH_1);

	वापस 0;
पूर्ण

अटल पूर्णांक sdio_disable_4bit_bus(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;

	अगर (card->type == MMC_TYPE_SDIO)
		जाओ out;

	अगर (!(card->host->caps & MMC_CAP_4_BIT_DATA))
		वापस 0;

	अगर (!(card->scr.bus_widths & SD_SCR_BUS_WIDTH_4))
		वापस 0;

	err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_1);
	अगर (err)
		वापस err;

out:
	वापस sdio_disable_wide(card);
पूर्ण


अटल पूर्णांक sdio_enable_4bit_bus(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;

	err = sdio_enable_wide(card);
	अगर (err <= 0)
		वापस err;
	अगर (card->type == MMC_TYPE_SDIO)
		जाओ out;

	अगर (card->scr.bus_widths & SD_SCR_BUS_WIDTH_4) अणु
		err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
		अगर (err) अणु
			sdio_disable_wide(card);
			वापस err;
		पूर्ण
	पूर्ण
out:
	mmc_set_bus_width(card->host, MMC_BUS_WIDTH_4);

	वापस 0;
पूर्ण


/*
 * Test अगर the card supports high-speed mode and, अगर so, चयन to it.
 */
अटल पूर्णांक mmc_sdio_चयन_hs(काष्ठा mmc_card *card, पूर्णांक enable)
अणु
	पूर्णांक ret;
	u8 speed;

	अगर (!(card->host->caps & MMC_CAP_SD_HIGHSPEED))
		वापस 0;

	अगर (!card->cccr.high_speed)
		वापस 0;

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_SPEED, 0, &speed);
	अगर (ret)
		वापस ret;

	अगर (enable)
		speed |= SDIO_SPEED_EHS;
	अन्यथा
		speed &= ~SDIO_SPEED_EHS;

	ret = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_SPEED, speed, शून्य);
	अगर (ret)
		वापस ret;

	वापस 1;
पूर्ण

/*
 * Enable SDIO/combo card's high-speed mode. Return 0/1 अगर [not]supported.
 */
अटल पूर्णांक sdio_enable_hs(काष्ठा mmc_card *card)
अणु
	पूर्णांक ret;

	ret = mmc_sdio_चयन_hs(card, true);
	अगर (ret <= 0 || card->type == MMC_TYPE_SDIO)
		वापस ret;

	ret = mmc_sd_चयन_hs(card);
	अगर (ret <= 0)
		mmc_sdio_चयन_hs(card, false);

	वापस ret;
पूर्ण

अटल अचिन्हित mmc_sdio_get_max_घड़ी(काष्ठा mmc_card *card)
अणु
	अचिन्हित max_dtr;

	अगर (mmc_card_hs(card)) अणु
		/*
		 * The SDIO specअगरication करोesn't mention how
		 * the CIS transfer speed रेजिस्टर relates to
		 * high-speed, but it seems that 50 MHz is
		 * mandatory.
		 */
		max_dtr = 50000000;
	पूर्ण अन्यथा अणु
		max_dtr = card->cis.max_dtr;
	पूर्ण

	अगर (card->type == MMC_TYPE_SD_COMBO)
		max_dtr = min(max_dtr, mmc_sd_get_max_घड़ी(card));

	वापस max_dtr;
पूर्ण

अटल अचिन्हित अक्षर host_drive_to_sdio_drive(पूर्णांक host_strength)
अणु
	चयन (host_strength) अणु
	हाल MMC_SET_DRIVER_TYPE_A:
		वापस SDIO_DTSx_SET_TYPE_A;
	हाल MMC_SET_DRIVER_TYPE_B:
		वापस SDIO_DTSx_SET_TYPE_B;
	हाल MMC_SET_DRIVER_TYPE_C:
		वापस SDIO_DTSx_SET_TYPE_C;
	हाल MMC_SET_DRIVER_TYPE_D:
		वापस SDIO_DTSx_SET_TYPE_D;
	शेष:
		वापस SDIO_DTSx_SET_TYPE_B;
	पूर्ण
पूर्ण

अटल व्योम sdio_select_driver_type(काष्ठा mmc_card *card)
अणु
	पूर्णांक card_drv_type, drive_strength, drv_type;
	अचिन्हित अक्षर card_strength;
	पूर्णांक err;

	card->drive_strength = 0;

	card_drv_type = card->sw_caps.sd3_drv_type | SD_DRIVER_TYPE_B;

	drive_strength = mmc_select_drive_strength(card,
						   card->sw_caps.uhs_max_dtr,
						   card_drv_type, &drv_type);

	अगर (drive_strength) अणु
		/* अगर error just use शेष क्रम drive strength B */
		err = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_DRIVE_STRENGTH, 0,
				       &card_strength);
		अगर (err)
			वापस;

		card_strength &= ~(SDIO_DRIVE_DTSx_MASK<<SDIO_DRIVE_DTSx_SHIFT);
		card_strength |= host_drive_to_sdio_drive(drive_strength);

		/* अगर error शेष to drive strength B */
		err = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_DRIVE_STRENGTH,
				       card_strength, शून्य);
		अगर (err)
			वापस;
		card->drive_strength = drive_strength;
	पूर्ण

	अगर (drv_type)
		mmc_set_driver_type(card->host, drv_type);
पूर्ण


अटल पूर्णांक sdio_set_bus_speed_mode(काष्ठा mmc_card *card)
अणु
	अचिन्हित पूर्णांक bus_speed, timing;
	पूर्णांक err;
	अचिन्हित अक्षर speed;
	अचिन्हित पूर्णांक max_rate;

	/*
	 * If the host करोesn't support any of the UHS-I modes, fallback on
	 * शेष speed.
	 */
	अगर (!mmc_host_uhs(card->host))
		वापस 0;

	bus_speed = SDIO_SPEED_SDR12;
	timing = MMC_TIMING_UHS_SDR12;
	अगर ((card->host->caps & MMC_CAP_UHS_SDR104) &&
	    (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR104)) अणु
			bus_speed = SDIO_SPEED_SDR104;
			timing = MMC_TIMING_UHS_SDR104;
			card->sw_caps.uhs_max_dtr = UHS_SDR104_MAX_DTR;
			card->sd_bus_speed = UHS_SDR104_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & MMC_CAP_UHS_DDR50) &&
		   (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_DDR50)) अणु
			bus_speed = SDIO_SPEED_DDR50;
			timing = MMC_TIMING_UHS_DDR50;
			card->sw_caps.uhs_max_dtr = UHS_DDR50_MAX_DTR;
			card->sd_bus_speed = UHS_DDR50_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50)) && (card->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDR50)) अणु
			bus_speed = SDIO_SPEED_SDR50;
			timing = MMC_TIMING_UHS_SDR50;
			card->sw_caps.uhs_max_dtr = UHS_SDR50_MAX_DTR;
			card->sd_bus_speed = UHS_SDR50_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25)) &&
		   (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR25)) अणु
			bus_speed = SDIO_SPEED_SDR25;
			timing = MMC_TIMING_UHS_SDR25;
			card->sw_caps.uhs_max_dtr = UHS_SDR25_MAX_DTR;
			card->sd_bus_speed = UHS_SDR25_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25 |
		    MMC_CAP_UHS_SDR12)) && (card->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDR12)) अणु
			bus_speed = SDIO_SPEED_SDR12;
			timing = MMC_TIMING_UHS_SDR12;
			card->sw_caps.uhs_max_dtr = UHS_SDR12_MAX_DTR;
			card->sd_bus_speed = UHS_SDR12_BUS_SPEED;
	पूर्ण

	err = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_SPEED, 0, &speed);
	अगर (err)
		वापस err;

	speed &= ~SDIO_SPEED_BSS_MASK;
	speed |= bus_speed;
	err = mmc_io_rw_direct(card, 1, 0, SDIO_CCCR_SPEED, speed, शून्य);
	अगर (err)
		वापस err;

	max_rate = min_not_zero(card->quirk_max_rate,
				card->sw_caps.uhs_max_dtr);

	mmc_set_timing(card->host, timing);
	mmc_set_घड़ी(card->host, max_rate);

	वापस 0;
पूर्ण

/*
 * UHS-I specअगरic initialization procedure
 */
अटल पूर्णांक mmc_sdio_init_uhs_card(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;

	अगर (!card->scr.sda_spec3)
		वापस 0;

	/* Switch to wider bus */
	err = sdio_enable_4bit_bus(card);
	अगर (err)
		जाओ out;

	/* Set the driver strength क्रम the card */
	sdio_select_driver_type(card);

	/* Set bus speed mode of the card */
	err = sdio_set_bus_speed_mode(card);
	अगर (err)
		जाओ out;

	/*
	 * SPI mode करोesn't define CMD19 and tuning is only valid क्रम SDR50 and
	 * SDR104 mode SD-cards. Note that tuning is mandatory क्रम SDR104.
	 */
	अगर (!mmc_host_is_spi(card->host) &&
	    ((card->host->ios.timing == MMC_TIMING_UHS_SDR50) ||
	      (card->host->ios.timing == MMC_TIMING_UHS_SDR104)))
		err = mmc_execute_tuning(card);
out:
	वापस err;
पूर्ण

अटल पूर्णांक mmc_sdio_pre_init(काष्ठा mmc_host *host, u32 ocr,
			     काष्ठा mmc_card *card)
अणु
	अगर (card)
		mmc_हटाओ_card(card);

	/*
	 * Reset the card by perक्रमming the same steps that are taken by
	 * mmc_rescan_try_freq() and mmc_attach_sdio() during a "normal" probe.
	 *
	 * sdio_reset() is technically not needed. Having just घातered up the
	 * hardware, it should alपढ़ोy be in reset state. However, some
	 * platक्रमms (such as SD8686 on OLPC) करो not instantly cut घातer,
	 * meaning that a reset is required when restoring घातer soon after
	 * घातering off. It is harmless in other हालs.
	 *
	 * The CMD5 reset (mmc_send_io_op_cond()), according to the SDIO spec,
	 * is not necessary क्रम non-removable cards. However, it is required
	 * क्रम OLPC SD8686 (which expects a [CMD5,5,3,7] init sequence), and
	 * harmless in other situations.
	 *
	 */

	sdio_reset(host);
	mmc_go_idle(host);
	mmc_send_अगर_cond(host, ocr);
	वापस mmc_send_io_op_cond(host, 0, शून्य);
पूर्ण

/*
 * Handle the detection and initialisation of a card.
 *
 * In the हाल of a resume, "oldcard" will contain the card
 * we're trying to reinitialise.
 */
अटल पूर्णांक mmc_sdio_init_card(काष्ठा mmc_host *host, u32 ocr,
			      काष्ठा mmc_card *oldcard)
अणु
	काष्ठा mmc_card *card;
	पूर्णांक err;
	पूर्णांक retries = 10;
	u32 rocr = 0;
	u32 ocr_card = ocr;

	WARN_ON(!host->claimed);

	/* to query card अगर 1.8V संकेतling is supported */
	अगर (mmc_host_uhs(host))
		ocr |= R4_18V_PRESENT;

try_again:
	अगर (!retries) अणु
		pr_warn("%s: Skipping voltage switch\n", mmc_hostname(host));
		ocr &= ~R4_18V_PRESENT;
	पूर्ण

	/*
	 * Inक्रमm the card of the voltage
	 */
	err = mmc_send_io_op_cond(host, ocr, &rocr);
	अगर (err)
		वापस err;

	/*
	 * For SPI, enable CRC as appropriate.
	 */
	अगर (mmc_host_is_spi(host)) अणु
		err = mmc_spi_set_crc(host, use_spi_crc);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Allocate card काष्ठाure.
	 */
	card = mmc_alloc_card(host, &sdio_type);
	अगर (IS_ERR(card))
		वापस PTR_ERR(card);

	अगर ((rocr & R4_MEMORY_PRESENT) &&
	    mmc_sd_get_cid(host, ocr & rocr, card->raw_cid, शून्य) == 0) अणु
		card->type = MMC_TYPE_SD_COMBO;

		अगर (oldcard && (oldcard->type != MMC_TYPE_SD_COMBO ||
		    स_भेद(card->raw_cid, oldcard->raw_cid, माप(card->raw_cid)) != 0)) अणु
			err = -ENOENT;
			जाओ mismatch;
		पूर्ण
	पूर्ण अन्यथा अणु
		card->type = MMC_TYPE_SDIO;

		अगर (oldcard && oldcard->type != MMC_TYPE_SDIO) अणु
			err = -ENOENT;
			जाओ mismatch;
		पूर्ण
	पूर्ण

	/*
	 * Call the optional HC's init_card function to handle quirks.
	 */
	अगर (host->ops->init_card)
		host->ops->init_card(host, card);

	/*
	 * If the host and card support UHS-I mode request the card
	 * to चयन to 1.8V संकेतing level.  No 1.8v संकेतling अगर
	 * UHS mode is not enabled to मुख्यtain compatibility and some
	 * प्रणालीs that claim 1.8v संकेतling in fact करो not support
	 * it. Per SDIO spec v3, section 3.1.2, अगर the voltage is alपढ़ोy
	 * 1.8v, the card sets S18A to 0 in the R4 response. So it will
	 * fails to check rocr & R4_18V_PRESENT,  but we still need to
	 * try to init uhs card. sdio_पढ़ो_cccr will take over this task
	 * to make sure which speed mode should work.
	 */
	अगर (rocr & ocr & R4_18V_PRESENT) अणु
		err = mmc_set_uhs_voltage(host, ocr_card);
		अगर (err == -EAGAIN) अणु
			mmc_sdio_pre_init(host, ocr_card, card);
			retries--;
			जाओ try_again;
		पूर्ण अन्यथा अगर (err) अणु
			ocr &= ~R4_18V_PRESENT;
		पूर्ण
	पूर्ण

	/*
	 * For native busses:  set card RCA and quit खोलो drain mode.
	 */
	अगर (!mmc_host_is_spi(host)) अणु
		err = mmc_send_relative_addr(host, &card->rca);
		अगर (err)
			जाओ हटाओ;

		/*
		 * Update oldcard with the new RCA received from the SDIO
		 * device -- we're doing this so that it's updated in the
		 * "card" काष्ठा when oldcard overग_लिखोs that later.
		 */
		अगर (oldcard)
			oldcard->rca = card->rca;
	पूर्ण

	/*
	 * Read CSD, beक्रमe selecting the card
	 */
	अगर (!oldcard && card->type == MMC_TYPE_SD_COMBO) अणु
		err = mmc_sd_get_csd(card);
		अगर (err)
			जाओ हटाओ;

		mmc_decode_cid(card);
	पूर्ण

	/*
	 * Select card, as all following commands rely on that.
	 */
	अगर (!mmc_host_is_spi(host)) अणु
		err = mmc_select_card(card);
		अगर (err)
			जाओ हटाओ;
	पूर्ण

	अगर (card->quirks & MMC_QUIRK_NONSTD_SDIO) अणु
		/*
		 * This is non-standard SDIO device, meaning it करोesn't
		 * have any CIA (Common I/O area) रेजिस्टरs present.
		 * It's host's responsibility to fill cccr and cis
		 * काष्ठाures in init_card().
		 */
		mmc_set_घड़ी(host, card->cis.max_dtr);

		अगर (card->cccr.high_speed) अणु
			mmc_set_timing(card->host, MMC_TIMING_SD_HS);
		पूर्ण

		अगर (oldcard)
			mmc_हटाओ_card(card);
		अन्यथा
			host->card = card;

		वापस 0;
	पूर्ण

	/*
	 * Read the common रेजिस्टरs. Note that we should try to
	 * validate whether UHS would work or not.
	 */
	err = sdio_पढ़ो_cccr(card, ocr);
	अगर (err) अणु
		mmc_sdio_pre_init(host, ocr_card, card);
		अगर (ocr & R4_18V_PRESENT) अणु
			/* Retry init sequence, but without R4_18V_PRESENT. */
			retries = 0;
			जाओ try_again;
		पूर्ण
		वापस err;
	पूर्ण

	/*
	 * Read the common CIS tuples.
	 */
	err = sdio_पढ़ो_common_cis(card);
	अगर (err)
		जाओ हटाओ;

	अगर (oldcard) अणु
		अगर (card->cis.venकरोr == oldcard->cis.venकरोr &&
		    card->cis.device == oldcard->cis.device) अणु
			mmc_हटाओ_card(card);
			card = oldcard;
		पूर्ण अन्यथा अणु
			err = -ENOENT;
			जाओ mismatch;
		पूर्ण
	पूर्ण
	card->ocr = ocr_card;
	mmc_fixup_device(card, sdio_fixup_methods);

	अगर (card->type == MMC_TYPE_SD_COMBO) अणु
		err = mmc_sd_setup_card(host, card, oldcard != शून्य);
		/* handle as SDIO-only card अगर memory init failed */
		अगर (err) अणु
			mmc_go_idle(host);
			अगर (mmc_host_is_spi(host))
				/* should not fail, as it worked previously */
				mmc_spi_set_crc(host, use_spi_crc);
			card->type = MMC_TYPE_SDIO;
		पूर्ण अन्यथा
			card->dev.type = &sd_type;
	पूर्ण

	/*
	 * If needed, disconnect card detection pull-up resistor.
	 */
	err = sdio_disable_cd(card);
	अगर (err)
		जाओ हटाओ;

	/* Initialization sequence क्रम UHS-I cards */
	/* Only अगर card supports 1.8v and UHS संकेतing */
	अगर ((ocr & R4_18V_PRESENT) && card->sw_caps.sd3_bus_mode) अणु
		err = mmc_sdio_init_uhs_card(card);
		अगर (err)
			जाओ हटाओ;
	पूर्ण अन्यथा अणु
		/*
		 * Switch to high-speed (अगर supported).
		 */
		err = sdio_enable_hs(card);
		अगर (err > 0)
			mmc_set_timing(card->host, MMC_TIMING_SD_HS);
		अन्यथा अगर (err)
			जाओ हटाओ;

		/*
		 * Change to the card's maximum speed.
		 */
		mmc_set_घड़ी(host, mmc_sdio_get_max_घड़ी(card));

		/*
		 * Switch to wider bus (अगर supported).
		 */
		err = sdio_enable_4bit_bus(card);
		अगर (err)
			जाओ हटाओ;
	पूर्ण

	अगर (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		pr_err("%s: Host failed to negotiate down from 3.3V\n",
			mmc_hostname(host));
		err = -EINVAL;
		जाओ हटाओ;
	पूर्ण

	host->card = card;
	वापस 0;

mismatch:
	pr_debug("%s: Perhaps the card was replaced\n", mmc_hostname(host));
हटाओ:
	अगर (oldcard != card)
		mmc_हटाओ_card(card);
	वापस err;
पूर्ण

अटल पूर्णांक mmc_sdio_reinit_card(काष्ठा mmc_host *host)
अणु
	पूर्णांक ret;

	ret = mmc_sdio_pre_init(host, host->card->ocr, शून्य);
	अगर (ret)
		वापस ret;

	वापस mmc_sdio_init_card(host, host->card->ocr, host->card);
पूर्ण

/*
 * Host is being हटाओd. Free up the current card.
 */
अटल व्योम mmc_sdio_हटाओ(काष्ठा mmc_host *host)
अणु
	पूर्णांक i;

	क्रम (i = 0;i < host->card->sdio_funcs;i++) अणु
		अगर (host->card->sdio_func[i]) अणु
			sdio_हटाओ_func(host->card->sdio_func[i]);
			host->card->sdio_func[i] = शून्य;
		पूर्ण
	पूर्ण

	mmc_हटाओ_card(host->card);
	host->card = शून्य;
पूर्ण

/*
 * Card detection - card is alive.
 */
अटल पूर्णांक mmc_sdio_alive(काष्ठा mmc_host *host)
अणु
	वापस mmc_select_card(host->card);
पूर्ण

/*
 * Card detection callback from host.
 */
अटल व्योम mmc_sdio_detect(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	/* Make sure card is घातered beक्रमe detecting it */
	अगर (host->caps & MMC_CAP_POWER_OFF_CARD) अणु
		err = pm_runसमय_get_sync(&host->card->dev);
		अगर (err < 0) अणु
			pm_runसमय_put_noidle(&host->card->dev);
			जाओ out;
		पूर्ण
	पूर्ण

	mmc_claim_host(host);

	/*
	 * Just check अगर our card has been हटाओd.
	 */
	err = _mmc_detect_card_हटाओd(host);

	mmc_release_host(host);

	/*
	 * Tell PM core it's OK to घातer off the card now.
	 *
	 * The _sync variant is used in order to ensure that the card
	 * is left घातered off in हाल an error occurred, and the card
	 * is going to be हटाओd.
	 *
	 * Since there is no specअगरic reason to believe a new user
	 * is about to show up at this poपूर्णांक, the _sync variant is
	 * desirable anyway.
	 */
	अगर (host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runसमय_put_sync(&host->card->dev);

out:
	अगर (err) अणु
		mmc_sdio_हटाओ(host);

		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_घातer_off(host);
		mmc_release_host(host);
	पूर्ण
पूर्ण

/*
 * SDIO pre_suspend.  We need to suspend all functions separately.
 * Thereक्रमe all रेजिस्टरed functions must have drivers with suspend
 * and resume methods.  Failing that we simply हटाओ the whole card.
 */
अटल पूर्णांक mmc_sdio_pre_suspend(काष्ठा mmc_host *host)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < host->card->sdio_funcs; i++) अणु
		काष्ठा sdio_func *func = host->card->sdio_func[i];
		अगर (func && sdio_func_present(func) && func->dev.driver) अणु
			स्थिर काष्ठा dev_pm_ops *pmops = func->dev.driver->pm;
			अगर (!pmops || !pmops->suspend || !pmops->resume)
				/* क्रमce removal of entire card in that हाल */
				जाओ हटाओ;
		पूर्ण
	पूर्ण

	वापस 0;

हटाओ:
	अगर (!mmc_card_is_removable(host)) अणु
		dev_warn(mmc_dev(host),
			 "missing suspend/resume ops for non-removable SDIO card\n");
		/* Don't remove a non-removable card - we can't re-detect it. */
		वापस 0;
	पूर्ण

	/* Remove the SDIO card and let it be re-detected later on. */
	mmc_sdio_हटाओ(host);
	mmc_claim_host(host);
	mmc_detach_bus(host);
	mmc_घातer_off(host);
	mmc_release_host(host);
	host->pm_flags = 0;

	वापस 0;
पूर्ण

/*
 * SDIO suspend.  Suspend all functions separately.
 */
अटल पूर्णांक mmc_sdio_suspend(काष्ठा mmc_host *host)
अणु
	WARN_ON(host->sdio_irqs && !mmc_card_keep_घातer(host));

	/* Prevent processing of SDIO IRQs in suspended state. */
	mmc_card_set_suspended(host->card);
	cancel_delayed_work_sync(&host->sdio_irq_work);

	mmc_claim_host(host);

	अगर (mmc_card_keep_घातer(host) && mmc_card_wake_sdio_irq(host))
		sdio_disable_4bit_bus(host->card);

	अगर (!mmc_card_keep_घातer(host)) अणु
		mmc_घातer_off(host);
	पूर्ण अन्यथा अगर (host->retune_period) अणु
		mmc_retune_समयr_stop(host);
		mmc_retune_needed(host);
	पूर्ण

	mmc_release_host(host);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_sdio_resume(काष्ठा mmc_host *host)
अणु
	पूर्णांक err = 0;

	/* Basic card reinitialization. */
	mmc_claim_host(host);

	/*
	 * Restore घातer and reinitialize the card when needed. Note that a
	 * removable card is checked from a detect work later on in the resume
	 * process.
	 */
	अगर (!mmc_card_keep_घातer(host)) अणु
		mmc_घातer_up(host, host->card->ocr);
		/*
		 * Tell runसमय PM core we just घातered up the card,
		 * since it still believes the card is घातered off.
		 * Note that currently runसमय PM is only enabled
		 * क्रम SDIO cards that are MMC_CAP_POWER_OFF_CARD
		 */
		अगर (host->caps & MMC_CAP_POWER_OFF_CARD) अणु
			pm_runसमय_disable(&host->card->dev);
			pm_runसमय_set_active(&host->card->dev);
			pm_runसमय_enable(&host->card->dev);
		पूर्ण
		err = mmc_sdio_reinit_card(host);
	पूर्ण अन्यथा अगर (mmc_card_wake_sdio_irq(host)) अणु
		/* We may have चयनed to 1-bit mode during suspend */
		err = sdio_enable_4bit_bus(host->card);
	पूर्ण

	अगर (err)
		जाओ out;

	/* Allow SDIO IRQs to be processed again. */
	mmc_card_clr_suspended(host->card);

	अगर (host->sdio_irqs) अणु
		अगर (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD))
			wake_up_process(host->sdio_irq_thपढ़ो);
		अन्यथा अगर (host->caps & MMC_CAP_SDIO_IRQ)
			queue_delayed_work(प्रणाली_wq, &host->sdio_irq_work, 0);
	पूर्ण

out:
	mmc_release_host(host);

	host->pm_flags &= ~MMC_PM_KEEP_POWER;
	वापस err;
पूर्ण

अटल पूर्णांक mmc_sdio_runसमय_suspend(काष्ठा mmc_host *host)
अणु
	/* No references to the card, cut the घातer to it. */
	mmc_claim_host(host);
	mmc_घातer_off(host);
	mmc_release_host(host);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_sdio_runसमय_resume(काष्ठा mmc_host *host)
अणु
	पूर्णांक ret;

	/* Restore घातer and re-initialize. */
	mmc_claim_host(host);
	mmc_घातer_up(host, host->card->ocr);
	ret = mmc_sdio_reinit_card(host);
	mmc_release_host(host);

	वापस ret;
पूर्ण

/*
 * SDIO HW reset
 *
 * Returns 0 अगर the HW reset was executed synchronously, वापसs 1 अगर the HW
 * reset was asynchronously scheduled, अन्यथा a negative error code.
 */
अटल पूर्णांक mmc_sdio_hw_reset(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_card *card = host->card;

	/*
	 * In हाल the card is shared among multiple func drivers, reset the
	 * card through a rescan work. In this way it will be हटाओd and
	 * re-detected, thus all func drivers becomes inक्रमmed about it.
	 */
	अगर (atomic_पढ़ो(&card->sdio_funcs_probed) > 1) अणु
		अगर (mmc_card_हटाओd(card))
			वापस 1;
		host->rescan_entered = 0;
		mmc_card_set_हटाओd(card);
		_mmc_detect_change(host, 0, false);
		वापस 1;
	पूर्ण

	/*
	 * A single func driver has been probed, then let's skip the heavy
	 * hotplug dance above and execute the reset immediately.
	 */
	mmc_घातer_cycle(host, card->ocr);
	वापस mmc_sdio_reinit_card(host);
पूर्ण

अटल पूर्णांक mmc_sdio_sw_reset(काष्ठा mmc_host *host)
अणु
	mmc_set_घड़ी(host, host->f_init);
	sdio_reset(host);
	mmc_go_idle(host);

	mmc_set_initial_state(host);
	mmc_set_initial_संकेत_voltage(host);

	वापस mmc_sdio_reinit_card(host);
पूर्ण

अटल स्थिर काष्ठा mmc_bus_ops mmc_sdio_ops = अणु
	.हटाओ = mmc_sdio_हटाओ,
	.detect = mmc_sdio_detect,
	.pre_suspend = mmc_sdio_pre_suspend,
	.suspend = mmc_sdio_suspend,
	.resume = mmc_sdio_resume,
	.runसमय_suspend = mmc_sdio_runसमय_suspend,
	.runसमय_resume = mmc_sdio_runसमय_resume,
	.alive = mmc_sdio_alive,
	.hw_reset = mmc_sdio_hw_reset,
	.sw_reset = mmc_sdio_sw_reset,
पूर्ण;


/*
 * Starting poपूर्णांक क्रम SDIO card init.
 */
पूर्णांक mmc_attach_sdio(काष्ठा mmc_host *host)
अणु
	पूर्णांक err, i, funcs;
	u32 ocr, rocr;
	काष्ठा mmc_card *card;

	WARN_ON(!host->claimed);

	err = mmc_send_io_op_cond(host, 0, &ocr);
	अगर (err)
		वापस err;

	mmc_attach_bus(host, &mmc_sdio_ops);
	अगर (host->ocr_avail_sdio)
		host->ocr_avail = host->ocr_avail_sdio;


	rocr = mmc_select_voltage(host, ocr);

	/*
	 * Can we support the voltage(s) of the card(s)?
	 */
	अगर (!rocr) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * Detect and init the card.
	 */
	err = mmc_sdio_init_card(host, rocr, शून्य);
	अगर (err)
		जाओ err;

	card = host->card;

	/*
	 * Enable runसमय PM only अगर supported by host+card+board
	 */
	अगर (host->caps & MMC_CAP_POWER_OFF_CARD) अणु
		/*
		 * Do not allow runसमय suspend until after SDIO function
		 * devices are added.
		 */
		pm_runसमय_get_noresume(&card->dev);

		/*
		 * Let runसमय PM core know our card is active
		 */
		err = pm_runसमय_set_active(&card->dev);
		अगर (err)
			जाओ हटाओ;

		/*
		 * Enable runसमय PM क्रम this card
		 */
		pm_runसमय_enable(&card->dev);
	पूर्ण

	/*
	 * The number of functions on the card is encoded inside
	 * the ocr.
	 */
	funcs = (ocr & 0x70000000) >> 28;
	card->sdio_funcs = 0;

	/*
	 * Initialize (but करोn't add) all present functions.
	 */
	क्रम (i = 0; i < funcs; i++, card->sdio_funcs++) अणु
		err = sdio_init_func(host->card, i + 1);
		अगर (err)
			जाओ हटाओ;

		/*
		 * Enable Runसमय PM क्रम this func (अगर supported)
		 */
		अगर (host->caps & MMC_CAP_POWER_OFF_CARD)
			pm_runसमय_enable(&card->sdio_func[i]->dev);
	पूर्ण

	/*
	 * First add the card to the driver model...
	 */
	mmc_release_host(host);
	err = mmc_add_card(host->card);
	अगर (err)
		जाओ हटाओ_added;

	/*
	 * ...then the SDIO functions.
	 */
	क्रम (i = 0;i < funcs;i++) अणु
		err = sdio_add_func(host->card->sdio_func[i]);
		अगर (err)
			जाओ हटाओ_added;
	पूर्ण

	अगर (host->caps & MMC_CAP_POWER_OFF_CARD)
		pm_runसमय_put(&card->dev);

	mmc_claim_host(host);
	वापस 0;


हटाओ:
	mmc_release_host(host);
हटाओ_added:
	/*
	 * The devices are being deleted so it is not necessary to disable
	 * runसमय PM. Similarly we also करोn't pm_runसमय_put() the SDIO card
	 * because it needs to be active to हटाओ any function devices that
	 * were probed, and after that it माला_लो deleted.
	 */
	mmc_sdio_हटाओ(host);
	mmc_claim_host(host);
err:
	mmc_detach_bus(host);

	pr_err("%s: error %d whilst initialising SDIO card\n",
		mmc_hostname(host), err);

	वापस err;
पूर्ण

