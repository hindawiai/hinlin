<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/core/sd.c
 *
 *  Copyright (C) 2003-2004 Russell King, All Rights Reserved.
 *  SD support Copyright (C) 2004 Ian Molton, All Rights Reserved.
 *  Copyright (C) 2005-2007 Pierre Ossman, All Rights Reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/sizes.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>
#समावेश <linux/mmc/sd.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "bus.h"
#समावेश "mmc_ops.h"
#समावेश "sd.h"
#समावेश "sd_ops.h"

अटल स्थिर अचिन्हित पूर्णांक tran_exp[] = अणु
	10000,		100000,		1000000,	10000000,
	0,		0,		0,		0
पूर्ण;

अटल स्थिर अचिन्हित अक्षर tran_mant[] = अणु
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक taac_exp[] = अणु
	1,	10,	100,	1000,	10000,	100000,	1000000, 10000000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक taac_mant[] = अणु
	0,	10,	12,	13,	15,	20,	25,	30,
	35,	40,	45,	50,	55,	60,	70,	80,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक sd_au_size[] = अणु
	0,		SZ_16K / 512,		SZ_32K / 512,	SZ_64K / 512,
	SZ_128K / 512,	SZ_256K / 512,		SZ_512K / 512,	SZ_1M / 512,
	SZ_2M / 512,	SZ_4M / 512,		SZ_8M / 512,	(SZ_8M + SZ_4M) / 512,
	SZ_16M / 512,	(SZ_16M + SZ_8M) / 512,	SZ_32M / 512,	SZ_64M / 512,
पूर्ण;

#घोषणा UNSTUFF_BITS(resp,start,size)					\
	(अणु								\
		स्थिर पूर्णांक __size = size;				\
		स्थिर u32 __mask = (__size < 32 ? 1 << __size : 0) - 1;	\
		स्थिर पूर्णांक __off = 3 - ((start) / 32);			\
		स्थिर पूर्णांक __shft = (start) & 31;			\
		u32 __res;						\
									\
		__res = resp[__off] >> __shft;				\
		अगर (__size + __shft > 32)				\
			__res |= resp[__off-1] << ((32 - __shft) % 32);	\
		__res & __mask;						\
	पूर्ण)

/*
 * Given the decoded CSD काष्ठाure, decode the raw CID to our CID काष्ठाure.
 */
व्योम mmc_decode_cid(काष्ठा mmc_card *card)
अणु
	u32 *resp = card->raw_cid;

	/*
	 * SD करोesn't currently have a version field so we will
	 * have to assume we can parse this.
	 */
	card->cid.manfid		= UNSTUFF_BITS(resp, 120, 8);
	card->cid.oemid			= UNSTUFF_BITS(resp, 104, 16);
	card->cid.prod_name[0]		= UNSTUFF_BITS(resp, 96, 8);
	card->cid.prod_name[1]		= UNSTUFF_BITS(resp, 88, 8);
	card->cid.prod_name[2]		= UNSTUFF_BITS(resp, 80, 8);
	card->cid.prod_name[3]		= UNSTUFF_BITS(resp, 72, 8);
	card->cid.prod_name[4]		= UNSTUFF_BITS(resp, 64, 8);
	card->cid.hwrev			= UNSTUFF_BITS(resp, 60, 4);
	card->cid.fwrev			= UNSTUFF_BITS(resp, 56, 4);
	card->cid.serial		= UNSTUFF_BITS(resp, 24, 32);
	card->cid.year			= UNSTUFF_BITS(resp, 12, 8);
	card->cid.month			= UNSTUFF_BITS(resp, 8, 4);

	card->cid.year += 2000; /* SD cards year offset */
पूर्ण

/*
 * Given a 128-bit response, decode to our card CSD काष्ठाure.
 */
अटल पूर्णांक mmc_decode_csd(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_csd *csd = &card->csd;
	अचिन्हित पूर्णांक e, m, csd_काष्ठा;
	u32 *resp = card->raw_csd;

	csd_काष्ठा = UNSTUFF_BITS(resp, 126, 2);

	चयन (csd_काष्ठा) अणु
	हाल 0:
		m = UNSTUFF_BITS(resp, 115, 4);
		e = UNSTUFF_BITS(resp, 112, 3);
		csd->taac_ns	 = (taac_exp[e] * taac_mant[m] + 9) / 10;
		csd->taac_clks	 = UNSTUFF_BITS(resp, 104, 8) * 100;

		m = UNSTUFF_BITS(resp, 99, 4);
		e = UNSTUFF_BITS(resp, 96, 3);
		csd->max_dtr	  = tran_exp[e] * tran_mant[m];
		csd->cmdclass	  = UNSTUFF_BITS(resp, 84, 12);

		e = UNSTUFF_BITS(resp, 47, 3);
		m = UNSTUFF_BITS(resp, 62, 12);
		csd->capacity	  = (1 + m) << (e + 2);

		csd->पढ़ो_blkbits = UNSTUFF_BITS(resp, 80, 4);
		csd->पढ़ो_partial = UNSTUFF_BITS(resp, 79, 1);
		csd->ग_लिखो_misalign = UNSTUFF_BITS(resp, 78, 1);
		csd->पढ़ो_misalign = UNSTUFF_BITS(resp, 77, 1);
		csd->dsr_imp = UNSTUFF_BITS(resp, 76, 1);
		csd->r2w_factor = UNSTUFF_BITS(resp, 26, 3);
		csd->ग_लिखो_blkbits = UNSTUFF_BITS(resp, 22, 4);
		csd->ग_लिखो_partial = UNSTUFF_BITS(resp, 21, 1);

		अगर (UNSTUFF_BITS(resp, 46, 1)) अणु
			csd->erase_size = 1;
		पूर्ण अन्यथा अगर (csd->ग_लिखो_blkbits >= 9) अणु
			csd->erase_size = UNSTUFF_BITS(resp, 39, 7) + 1;
			csd->erase_size <<= csd->ग_लिखो_blkbits - 9;
		पूर्ण

		अगर (UNSTUFF_BITS(resp, 13, 1))
			mmc_card_set_पढ़ोonly(card);
		अवरोध;
	हाल 1:
		/*
		 * This is a block-addressed SDHC or SDXC card. Most
		 * पूर्णांकeresting fields are unused and have fixed
		 * values. To aव्योम getting tripped by buggy cards,
		 * we assume those fixed values ourselves.
		 */
		mmc_card_set_blockaddr(card);

		csd->taac_ns	 = 0; /* Unused */
		csd->taac_clks	 = 0; /* Unused */

		m = UNSTUFF_BITS(resp, 99, 4);
		e = UNSTUFF_BITS(resp, 96, 3);
		csd->max_dtr	  = tran_exp[e] * tran_mant[m];
		csd->cmdclass	  = UNSTUFF_BITS(resp, 84, 12);
		csd->c_size	  = UNSTUFF_BITS(resp, 48, 22);

		/* SDXC cards have a minimum C_SIZE of 0x00FFFF */
		अगर (csd->c_size >= 0xFFFF)
			mmc_card_set_ext_capacity(card);

		m = UNSTUFF_BITS(resp, 48, 22);
		csd->capacity     = (1 + m) << 10;

		csd->पढ़ो_blkbits = 9;
		csd->पढ़ो_partial = 0;
		csd->ग_लिखो_misalign = 0;
		csd->पढ़ो_misalign = 0;
		csd->r2w_factor = 4; /* Unused */
		csd->ग_लिखो_blkbits = 9;
		csd->ग_लिखो_partial = 0;
		csd->erase_size = 1;

		अगर (UNSTUFF_BITS(resp, 13, 1))
			mmc_card_set_पढ़ोonly(card);
		अवरोध;
	शेष:
		pr_err("%s: unrecognised CSD structure version %d\n",
			mmc_hostname(card->host), csd_काष्ठा);
		वापस -EINVAL;
	पूर्ण

	card->erase_size = csd->erase_size;

	वापस 0;
पूर्ण

/*
 * Given a 64-bit response, decode to our card SCR काष्ठाure.
 */
अटल पूर्णांक mmc_decode_scr(काष्ठा mmc_card *card)
अणु
	काष्ठा sd_scr *scr = &card->scr;
	अचिन्हित पूर्णांक scr_काष्ठा;
	u32 resp[4];

	resp[3] = card->raw_scr[1];
	resp[2] = card->raw_scr[0];

	scr_काष्ठा = UNSTUFF_BITS(resp, 60, 4);
	अगर (scr_काष्ठा != 0) अणु
		pr_err("%s: unrecognised SCR structure version %d\n",
			mmc_hostname(card->host), scr_काष्ठा);
		वापस -EINVAL;
	पूर्ण

	scr->sda_vsn = UNSTUFF_BITS(resp, 56, 4);
	scr->bus_widths = UNSTUFF_BITS(resp, 48, 4);
	अगर (scr->sda_vsn == SCR_SPEC_VER_2)
		/* Check अगर Physical Layer Spec v3.0 is supported */
		scr->sda_spec3 = UNSTUFF_BITS(resp, 47, 1);

	अगर (scr->sda_spec3) अणु
		scr->sda_spec4 = UNSTUFF_BITS(resp, 42, 1);
		scr->sda_specx = UNSTUFF_BITS(resp, 38, 4);
	पूर्ण

	अगर (UNSTUFF_BITS(resp, 55, 1))
		card->erased_byte = 0xFF;
	अन्यथा
		card->erased_byte = 0x0;

	अगर (scr->sda_spec3)
		scr->cmds = UNSTUFF_BITS(resp, 32, 2);

	/* SD Spec says: any SD Card shall set at least bits 0 and 2 */
	अगर (!(scr->bus_widths & SD_SCR_BUS_WIDTH_1) ||
	    !(scr->bus_widths & SD_SCR_BUS_WIDTH_4)) अणु
		pr_err("%s: invalid bus width\n", mmc_hostname(card->host));
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Fetch and process SD Status रेजिस्टर.
 */
अटल पूर्णांक mmc_पढ़ो_ssr(काष्ठा mmc_card *card)
अणु
	अचिन्हित पूर्णांक au, es, et, eo;
	__be32 *raw_ssr;
	u32 resp[4] = अणुपूर्ण;
	u8 discard_support;
	पूर्णांक i;

	अगर (!(card->csd.cmdclass & CCC_APP_SPEC)) अणु
		pr_warn("%s: card lacks mandatory SD Status function\n",
			mmc_hostname(card->host));
		वापस 0;
	पूर्ण

	raw_ssr = kदो_स्मृति(माप(card->raw_ssr), GFP_KERNEL);
	अगर (!raw_ssr)
		वापस -ENOMEM;

	अगर (mmc_app_sd_status(card, raw_ssr)) अणु
		pr_warn("%s: problem reading SD Status register\n",
			mmc_hostname(card->host));
		kमुक्त(raw_ssr);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < 16; i++)
		card->raw_ssr[i] = be32_to_cpu(raw_ssr[i]);

	kमुक्त(raw_ssr);

	/*
	 * UNSTUFF_BITS only works with four u32s so we have to offset the
	 * bitfield positions accordingly.
	 */
	au = UNSTUFF_BITS(card->raw_ssr, 428 - 384, 4);
	अगर (au) अणु
		अगर (au <= 9 || card->scr.sda_spec3) अणु
			card->ssr.au = sd_au_size[au];
			es = UNSTUFF_BITS(card->raw_ssr, 408 - 384, 16);
			et = UNSTUFF_BITS(card->raw_ssr, 402 - 384, 6);
			अगर (es && et) अणु
				eo = UNSTUFF_BITS(card->raw_ssr, 400 - 384, 2);
				card->ssr.erase_समयout = (et * 1000) / es;
				card->ssr.erase_offset = eo * 1000;
			पूर्ण
		पूर्ण अन्यथा अणु
			pr_warn("%s: SD Status: Invalid Allocation Unit size\n",
				mmc_hostname(card->host));
		पूर्ण
	पूर्ण

	/*
	 * starting SD5.1 discard is supported अगर DISCARD_SUPPORT (b313) is set
	 */
	resp[3] = card->raw_ssr[6];
	discard_support = UNSTUFF_BITS(resp, 313 - 288, 1);
	card->erase_arg = (card->scr.sda_specx && discard_support) ?
			    SD_DISCARD_ARG : SD_ERASE_ARG;

	वापस 0;
पूर्ण

/*
 * Fetches and decodes चयन inक्रमmation
 */
अटल पूर्णांक mmc_पढ़ो_चयन(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	u8 *status;

	अगर (card->scr.sda_vsn < SCR_SPEC_VER_1)
		वापस 0;

	अगर (!(card->csd.cmdclass & CCC_SWITCH)) अणु
		pr_warn("%s: card lacks mandatory switch function, performance might suffer\n",
			mmc_hostname(card->host));
		वापस 0;
	पूर्ण

	status = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!status)
		वापस -ENOMEM;

	/*
	 * Find out the card's support bits with a mode 0 operation.
	 * The argument करोes not matter, as the support bits करो not
	 * change with the arguments.
	 */
	err = mmc_sd_चयन(card, 0, 0, 0, status);
	अगर (err) अणु
		/*
		 * If the host or the card can't करो the चयन,
		 * fail more gracefully.
		 */
		अगर (err != -EINVAL && err != -ENOSYS && err != -EFAULT)
			जाओ out;

		pr_warn("%s: problem reading Bus Speed modes\n",
			mmc_hostname(card->host));
		err = 0;

		जाओ out;
	पूर्ण

	अगर (status[13] & SD_MODE_HIGH_SPEED)
		card->sw_caps.hs_max_dtr = HIGH_SPEED_MAX_DTR;

	अगर (card->scr.sda_spec3) अणु
		card->sw_caps.sd3_bus_mode = status[13];
		/* Driver Strengths supported by the card */
		card->sw_caps.sd3_drv_type = status[9];
		card->sw_caps.sd3_curr_limit = status[7] | status[6] << 8;
	पूर्ण

out:
	kमुक्त(status);

	वापस err;
पूर्ण

/*
 * Test अगर the card supports high-speed mode and, अगर so, चयन to it.
 */
पूर्णांक mmc_sd_चयन_hs(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	u8 *status;

	अगर (card->scr.sda_vsn < SCR_SPEC_VER_1)
		वापस 0;

	अगर (!(card->csd.cmdclass & CCC_SWITCH))
		वापस 0;

	अगर (!(card->host->caps & MMC_CAP_SD_HIGHSPEED))
		वापस 0;

	अगर (card->sw_caps.hs_max_dtr == 0)
		वापस 0;

	status = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!status)
		वापस -ENOMEM;

	err = mmc_sd_चयन(card, 1, 0, HIGH_SPEED_BUS_SPEED, status);
	अगर (err)
		जाओ out;

	अगर ((status[16] & 0xF) != HIGH_SPEED_BUS_SPEED) अणु
		pr_warn("%s: Problem switching card into high-speed mode!\n",
			mmc_hostname(card->host));
		err = 0;
	पूर्ण अन्यथा अणु
		err = 1;
	पूर्ण

out:
	kमुक्त(status);

	वापस err;
पूर्ण

अटल पूर्णांक sd_select_driver_type(काष्ठा mmc_card *card, u8 *status)
अणु
	पूर्णांक card_drv_type, drive_strength, drv_type;
	पूर्णांक err;

	card->drive_strength = 0;

	card_drv_type = card->sw_caps.sd3_drv_type | SD_DRIVER_TYPE_B;

	drive_strength = mmc_select_drive_strength(card,
						   card->sw_caps.uhs_max_dtr,
						   card_drv_type, &drv_type);

	अगर (drive_strength) अणु
		err = mmc_sd_चयन(card, 1, 2, drive_strength, status);
		अगर (err)
			वापस err;
		अगर ((status[15] & 0xF) != drive_strength) अणु
			pr_warn("%s: Problem setting drive strength!\n",
				mmc_hostname(card->host));
			वापस 0;
		पूर्ण
		card->drive_strength = drive_strength;
	पूर्ण

	अगर (drv_type)
		mmc_set_driver_type(card->host, drv_type);

	वापस 0;
पूर्ण

अटल व्योम sd_update_bus_speed_mode(काष्ठा mmc_card *card)
अणु
	/*
	 * If the host करोesn't support any of the UHS-I modes, fallback on
	 * शेष speed.
	 */
	अगर (!mmc_host_uhs(card->host)) अणु
		card->sd_bus_speed = 0;
		वापस;
	पूर्ण

	अगर ((card->host->caps & MMC_CAP_UHS_SDR104) &&
	    (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR104)) अणु
			card->sd_bus_speed = UHS_SDR104_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & MMC_CAP_UHS_DDR50) &&
		   (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_DDR50)) अणु
			card->sd_bus_speed = UHS_DDR50_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50)) && (card->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDR50)) अणु
			card->sd_bus_speed = UHS_SDR50_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25)) &&
		   (card->sw_caps.sd3_bus_mode & SD_MODE_UHS_SDR25)) अणु
			card->sd_bus_speed = UHS_SDR25_BUS_SPEED;
	पूर्ण अन्यथा अगर ((card->host->caps & (MMC_CAP_UHS_SDR104 |
		    MMC_CAP_UHS_SDR50 | MMC_CAP_UHS_SDR25 |
		    MMC_CAP_UHS_SDR12)) && (card->sw_caps.sd3_bus_mode &
		    SD_MODE_UHS_SDR12)) अणु
			card->sd_bus_speed = UHS_SDR12_BUS_SPEED;
	पूर्ण
पूर्ण

अटल पूर्णांक sd_set_bus_speed_mode(काष्ठा mmc_card *card, u8 *status)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक timing = 0;

	चयन (card->sd_bus_speed) अणु
	हाल UHS_SDR104_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR104;
		card->sw_caps.uhs_max_dtr = UHS_SDR104_MAX_DTR;
		अवरोध;
	हाल UHS_DDR50_BUS_SPEED:
		timing = MMC_TIMING_UHS_DDR50;
		card->sw_caps.uhs_max_dtr = UHS_DDR50_MAX_DTR;
		अवरोध;
	हाल UHS_SDR50_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR50;
		card->sw_caps.uhs_max_dtr = UHS_SDR50_MAX_DTR;
		अवरोध;
	हाल UHS_SDR25_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR25;
		card->sw_caps.uhs_max_dtr = UHS_SDR25_MAX_DTR;
		अवरोध;
	हाल UHS_SDR12_BUS_SPEED:
		timing = MMC_TIMING_UHS_SDR12;
		card->sw_caps.uhs_max_dtr = UHS_SDR12_MAX_DTR;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	err = mmc_sd_चयन(card, 1, 0, card->sd_bus_speed, status);
	अगर (err)
		वापस err;

	अगर ((status[16] & 0xF) != card->sd_bus_speed)
		pr_warn("%s: Problem setting bus speed mode!\n",
			mmc_hostname(card->host));
	अन्यथा अणु
		mmc_set_timing(card->host, timing);
		mmc_set_घड़ी(card->host, card->sw_caps.uhs_max_dtr);
	पूर्ण

	वापस 0;
पूर्ण

/* Get host's max current setting at its current voltage */
अटल u32 sd_get_host_max_current(काष्ठा mmc_host *host)
अणु
	u32 voltage, max_current;

	voltage = 1 << host->ios.vdd;
	चयन (voltage) अणु
	हाल MMC_VDD_165_195:
		max_current = host->max_current_180;
		अवरोध;
	हाल MMC_VDD_29_30:
	हाल MMC_VDD_30_31:
		max_current = host->max_current_300;
		अवरोध;
	हाल MMC_VDD_32_33:
	हाल MMC_VDD_33_34:
		max_current = host->max_current_330;
		अवरोध;
	शेष:
		max_current = 0;
	पूर्ण

	वापस max_current;
पूर्ण

अटल पूर्णांक sd_set_current_limit(काष्ठा mmc_card *card, u8 *status)
अणु
	पूर्णांक current_limit = SD_SET_CURRENT_NO_CHANGE;
	पूर्णांक err;
	u32 max_current;

	/*
	 * Current limit चयन is only defined क्रम SDR50, SDR104, and DDR50
	 * bus speed modes. For other bus speed modes, we करो not change the
	 * current limit.
	 */
	अगर ((card->sd_bus_speed != UHS_SDR50_BUS_SPEED) &&
	    (card->sd_bus_speed != UHS_SDR104_BUS_SPEED) &&
	    (card->sd_bus_speed != UHS_DDR50_BUS_SPEED))
		वापस 0;

	/*
	 * Host has dअगरferent current capabilities when operating at
	 * dअगरferent voltages, so find out its max current first.
	 */
	max_current = sd_get_host_max_current(card->host);

	/*
	 * We only check host's capability here, अगर we set a limit that is
	 * higher than the card's maximum current, the card will be using its
	 * maximum current, e.g. अगर the card's maximum current is 300ma, and
	 * when we set current limit to 200ma, the card will draw 200ma, and
	 * when we set current limit to 400/600/800ma, the card will draw its
	 * maximum 300ma from the host.
	 *
	 * The above is incorrect: अगर we try to set a current limit that is
	 * not supported by the card, the card can rightfully error out the
	 * attempt, and reमुख्य at the शेष current limit.  This results
	 * in a 300mA card being limited to 200mA even though the host
	 * supports 800mA. Failures seen with SanDisk 8GB UHS cards with
	 * an iMX6 host. --rmk
	 */
	अगर (max_current >= 800 &&
	    card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_800)
		current_limit = SD_SET_CURRENT_LIMIT_800;
	अन्यथा अगर (max_current >= 600 &&
		 card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_600)
		current_limit = SD_SET_CURRENT_LIMIT_600;
	अन्यथा अगर (max_current >= 400 &&
		 card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_400)
		current_limit = SD_SET_CURRENT_LIMIT_400;
	अन्यथा अगर (max_current >= 200 &&
		 card->sw_caps.sd3_curr_limit & SD_MAX_CURRENT_200)
		current_limit = SD_SET_CURRENT_LIMIT_200;

	अगर (current_limit != SD_SET_CURRENT_NO_CHANGE) अणु
		err = mmc_sd_चयन(card, 1, 3, current_limit, status);
		अगर (err)
			वापस err;

		अगर (((status[15] >> 4) & 0x0F) != current_limit)
			pr_warn("%s: Problem setting current limit!\n",
				mmc_hostname(card->host));

	पूर्ण

	वापस 0;
पूर्ण

/*
 * UHS-I specअगरic initialization procedure
 */
अटल पूर्णांक mmc_sd_init_uhs_card(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;
	u8 *status;

	अगर (!(card->csd.cmdclass & CCC_SWITCH))
		वापस 0;

	status = kदो_स्मृति(64, GFP_KERNEL);
	अगर (!status)
		वापस -ENOMEM;

	/* Set 4-bit bus width */
	err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
	अगर (err)
		जाओ out;

	mmc_set_bus_width(card->host, MMC_BUS_WIDTH_4);

	/*
	 * Select the bus speed mode depending on host
	 * and card capability.
	 */
	sd_update_bus_speed_mode(card);

	/* Set the driver strength क्रम the card */
	err = sd_select_driver_type(card, status);
	अगर (err)
		जाओ out;

	/* Set current limit क्रम the card */
	err = sd_set_current_limit(card, status);
	अगर (err)
		जाओ out;

	/* Set bus speed mode of the card */
	err = sd_set_bus_speed_mode(card, status);
	अगर (err)
		जाओ out;

	/*
	 * SPI mode करोesn't define CMD19 and tuning is only valid क्रम SDR50 and
	 * SDR104 mode SD-cards. Note that tuning is mandatory क्रम SDR104.
	 */
	अगर (!mmc_host_is_spi(card->host) &&
		(card->host->ios.timing == MMC_TIMING_UHS_SDR50 ||
		 card->host->ios.timing == MMC_TIMING_UHS_DDR50 ||
		 card->host->ios.timing == MMC_TIMING_UHS_SDR104)) अणु
		err = mmc_execute_tuning(card);

		/*
		 * As SD Specअगरications Part1 Physical Layer Specअगरication
		 * Version 3.01 says, CMD19 tuning is available क्रम unlocked
		 * cards in transfer state of 1.8V संकेतing mode. The small
		 * dअगरference between v3.00 and 3.01 spec means that CMD19
		 * tuning is also available क्रम DDR50 mode.
		 */
		अगर (err && card->host->ios.timing == MMC_TIMING_UHS_DDR50) अणु
			pr_warn("%s: ddr50 tuning failed\n",
				mmc_hostname(card->host));
			err = 0;
		पूर्ण
	पूर्ण

out:
	kमुक्त(status);

	वापस err;
पूर्ण

MMC_DEV_ATTR(cid, "%08x%08x%08x%08x\n", card->raw_cid[0], card->raw_cid[1],
	card->raw_cid[2], card->raw_cid[3]);
MMC_DEV_ATTR(csd, "%08x%08x%08x%08x\n", card->raw_csd[0], card->raw_csd[1],
	card->raw_csd[2], card->raw_csd[3]);
MMC_DEV_ATTR(scr, "%08x%08x\n", card->raw_scr[0], card->raw_scr[1]);
MMC_DEV_ATTR(ssr,
	"%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x\n",
		card->raw_ssr[0], card->raw_ssr[1], card->raw_ssr[2],
		card->raw_ssr[3], card->raw_ssr[4], card->raw_ssr[5],
		card->raw_ssr[6], card->raw_ssr[7], card->raw_ssr[8],
		card->raw_ssr[9], card->raw_ssr[10], card->raw_ssr[11],
		card->raw_ssr[12], card->raw_ssr[13], card->raw_ssr[14],
		card->raw_ssr[15]);
MMC_DEV_ATTR(date, "%02d/%04d\n", card->cid.month, card->cid.year);
MMC_DEV_ATTR(erase_size, "%u\n", card->erase_size << 9);
MMC_DEV_ATTR(preferred_erase_size, "%u\n", card->pref_erase << 9);
MMC_DEV_ATTR(fwrev, "0x%x\n", card->cid.fwrev);
MMC_DEV_ATTR(hwrev, "0x%x\n", card->cid.hwrev);
MMC_DEV_ATTR(manfid, "0x%06x\n", card->cid.manfid);
MMC_DEV_ATTR(name, "%s\n", card->cid.prod_name);
MMC_DEV_ATTR(oemid, "0x%04x\n", card->cid.oemid);
MMC_DEV_ATTR(serial, "0x%08x\n", card->cid.serial);
MMC_DEV_ATTR(ocr, "0x%08x\n", card->ocr);
MMC_DEV_ATTR(rca, "0x%04x\n", card->rca);


अटल sमाप_प्रकार mmc_dsr_show(काष्ठा device *dev,
                           काष्ठा device_attribute *attr,
                           अक्षर *buf)
अणु
       काष्ठा mmc_card *card = mmc_dev_to_card(dev);
       काष्ठा mmc_host *host = card->host;

       अगर (card->csd.dsr_imp && host->dsr_req)
               वापस प्र_लिखो(buf, "0x%x\n", host->dsr);
       अन्यथा
               /* वापस शेष DSR value */
               वापस प्र_लिखो(buf, "0x%x\n", 0x404);
पूर्ण

अटल DEVICE_ATTR(dsr, S_IRUGO, mmc_dsr_show, शून्य);

MMC_DEV_ATTR(venकरोr, "0x%04x\n", card->cis.venकरोr);
MMC_DEV_ATTR(device, "0x%04x\n", card->cis.device);
MMC_DEV_ATTR(revision, "%u.%u\n", card->major_rev, card->minor_rev);

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

अटल काष्ठा attribute *sd_std_attrs[] = अणु
	&dev_attr_venकरोr.attr,
	&dev_attr_device.attr,
	&dev_attr_revision.attr,
	&dev_attr_info1.attr,
	&dev_attr_info2.attr,
	&dev_attr_info3.attr,
	&dev_attr_info4.attr,
	&dev_attr_cid.attr,
	&dev_attr_csd.attr,
	&dev_attr_scr.attr,
	&dev_attr_ssr.attr,
	&dev_attr_date.attr,
	&dev_attr_erase_size.attr,
	&dev_attr_preferred_erase_size.attr,
	&dev_attr_fwrev.attr,
	&dev_attr_hwrev.attr,
	&dev_attr_manfid.attr,
	&dev_attr_name.attr,
	&dev_attr_oemid.attr,
	&dev_attr_serial.attr,
	&dev_attr_ocr.attr,
	&dev_attr_rca.attr,
	&dev_attr_dsr.attr,
	शून्य,
पूर्ण;

अटल umode_t sd_std_is_visible(काष्ठा kobject *kobj, काष्ठा attribute *attr,
				 पूर्णांक index)
अणु
	काष्ठा device *dev = kobj_to_dev(kobj);
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	/* CIS venकरोr and device ids, revision and info string are available only क्रम Combo cards */
	अगर ((attr == &dev_attr_venकरोr.attr ||
	     attr == &dev_attr_device.attr ||
	     attr == &dev_attr_revision.attr ||
	     attr == &dev_attr_info1.attr ||
	     attr == &dev_attr_info2.attr ||
	     attr == &dev_attr_info3.attr ||
	     attr == &dev_attr_info4.attr
	    ) && card->type != MMC_TYPE_SD_COMBO)
		वापस 0;

	वापस attr->mode;
पूर्ण

अटल स्थिर काष्ठा attribute_group sd_std_group = अणु
	.attrs = sd_std_attrs,
	.is_visible = sd_std_is_visible,
पूर्ण;
__ATTRIBUTE_GROUPS(sd_std);

काष्ठा device_type sd_type = अणु
	.groups = sd_std_groups,
पूर्ण;

/*
 * Fetch CID from card.
 */
पूर्णांक mmc_sd_get_cid(काष्ठा mmc_host *host, u32 ocr, u32 *cid, u32 *rocr)
अणु
	पूर्णांक err;
	u32 max_current;
	पूर्णांक retries = 10;
	u32 pocr = ocr;

try_again:
	अगर (!retries) अणु
		ocr &= ~SD_OCR_S18R;
		pr_warn("%s: Skipping voltage switch\n", mmc_hostname(host));
	पूर्ण

	/*
	 * Since we're changing the OCR value, we seem to
	 * need to tell some cards to go back to the idle
	 * state.  We रुको 1ms to give cards समय to
	 * respond.
	 */
	mmc_go_idle(host);

	/*
	 * If SD_SEND_IF_COND indicates an SD 2.0
	 * compliant card and we should set bit 30
	 * of the ocr to indicate that we can handle
	 * block-addressed SDHC cards.
	 */
	err = mmc_send_अगर_cond(host, ocr);
	अगर (!err)
		ocr |= SD_OCR_CCS;

	/*
	 * If the host supports one of UHS-I modes, request the card
	 * to चयन to 1.8V संकेतing level. If the card has failed
	 * repeatedly to चयन however, skip this.
	 */
	अगर (retries && mmc_host_uhs(host))
		ocr |= SD_OCR_S18R;

	/*
	 * If the host can supply more than 150mA at current voltage,
	 * XPC should be set to 1.
	 */
	max_current = sd_get_host_max_current(host);
	अगर (max_current > 150)
		ocr |= SD_OCR_XPC;

	err = mmc_send_app_op_cond(host, ocr, rocr);
	अगर (err)
		वापस err;

	/*
	 * In हाल CCS and S18A in the response is set, start Signal Voltage
	 * Switch procedure. SPI mode करोesn't support CMD11.
	 */
	अगर (!mmc_host_is_spi(host) && rocr &&
	   ((*rocr & 0x41000000) == 0x41000000)) अणु
		err = mmc_set_uhs_voltage(host, pocr);
		अगर (err == -EAGAIN) अणु
			retries--;
			जाओ try_again;
		पूर्ण अन्यथा अगर (err) अणु
			retries = 0;
			जाओ try_again;
		पूर्ण
	पूर्ण

	err = mmc_send_cid(host, cid);
	वापस err;
पूर्ण

पूर्णांक mmc_sd_get_csd(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;

	/*
	 * Fetch CSD from card.
	 */
	err = mmc_send_csd(card, card->raw_csd);
	अगर (err)
		वापस err;

	err = mmc_decode_csd(card);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_sd_get_ro(काष्ठा mmc_host *host)
अणु
	पूर्णांक ro;

	/*
	 * Some प्रणालीs करोn't feature a write-protect pin and don't need one.
	 * E.g. because they only have micro-SD card slot. For those प्रणालीs
	 * assume that the SD card is always पढ़ो-ग_लिखो.
	 */
	अगर (host->caps2 & MMC_CAP2_NO_WRITE_PROTECT)
		वापस 0;

	अगर (!host->ops->get_ro)
		वापस -1;

	ro = host->ops->get_ro(host);

	वापस ro;
पूर्ण

पूर्णांक mmc_sd_setup_card(काष्ठा mmc_host *host, काष्ठा mmc_card *card,
	bool reinit)
अणु
	पूर्णांक err;

	अगर (!reinit) अणु
		/*
		 * Fetch SCR from card.
		 */
		err = mmc_app_send_scr(card);
		अगर (err)
			वापस err;

		err = mmc_decode_scr(card);
		अगर (err)
			वापस err;

		/*
		 * Fetch and process SD Status रेजिस्टर.
		 */
		err = mmc_पढ़ो_ssr(card);
		अगर (err)
			वापस err;

		/* Erase init depends on CSD and SSR */
		mmc_init_erase(card);

		/*
		 * Fetch चयन inक्रमmation from card.
		 */
		err = mmc_पढ़ो_चयन(card);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * For SPI, enable CRC as appropriate.
	 * This CRC enable is located AFTER the पढ़ोing of the
	 * card रेजिस्टरs because some SDHC cards are not able
	 * to provide valid CRCs क्रम non-512-byte blocks.
	 */
	अगर (mmc_host_is_spi(host)) अणु
		err = mmc_spi_set_crc(host, use_spi_crc);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Check अगर पढ़ो-only चयन is active.
	 */
	अगर (!reinit) अणु
		पूर्णांक ro = mmc_sd_get_ro(host);

		अगर (ro < 0) अणु
			pr_warn("%s: host does not support reading read-only switch, assuming write-enable\n",
				mmc_hostname(host));
		पूर्ण अन्यथा अगर (ro > 0) अणु
			mmc_card_set_पढ़ोonly(card);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित mmc_sd_get_max_घड़ी(काष्ठा mmc_card *card)
अणु
	अचिन्हित max_dtr = (अचिन्हित पूर्णांक)-1;

	अगर (mmc_card_hs(card)) अणु
		अगर (max_dtr > card->sw_caps.hs_max_dtr)
			max_dtr = card->sw_caps.hs_max_dtr;
	पूर्ण अन्यथा अगर (max_dtr > card->csd.max_dtr) अणु
		max_dtr = card->csd.max_dtr;
	पूर्ण

	वापस max_dtr;
पूर्ण

अटल bool mmc_sd_card_using_v18(काष्ठा mmc_card *card)
अणु
	/*
	 * According to the SD spec., the Bus Speed Mode (function group 1) bits
	 * 2 to 4 are zero अगर the card is initialized at 3.3V संकेत level. Thus
	 * they can be used to determine अगर the card has alपढ़ोy चयनed to
	 * 1.8V संकेतing.
	 */
	वापस card->sw_caps.sd3_bus_mode &
	       (SD_MODE_UHS_SDR50 | SD_MODE_UHS_SDR104 | SD_MODE_UHS_DDR50);
पूर्ण

/*
 * Handle the detection and initialisation of a card.
 *
 * In the हाल of a resume, "oldcard" will contain the card
 * we're trying to reinitialise.
 */
अटल पूर्णांक mmc_sd_init_card(काष्ठा mmc_host *host, u32 ocr,
	काष्ठा mmc_card *oldcard)
अणु
	काष्ठा mmc_card *card;
	पूर्णांक err;
	u32 cid[4];
	u32 rocr = 0;
	bool v18_fixup_failed = false;

	WARN_ON(!host->claimed);
retry:
	err = mmc_sd_get_cid(host, ocr, cid, &rocr);
	अगर (err)
		वापस err;

	अगर (oldcard) अणु
		अगर (स_भेद(cid, oldcard->raw_cid, माप(cid)) != 0) अणु
			pr_debug("%s: Perhaps the card was replaced\n",
				mmc_hostname(host));
			वापस -ENOENT;
		पूर्ण

		card = oldcard;
	पूर्ण अन्यथा अणु
		/*
		 * Allocate card काष्ठाure.
		 */
		card = mmc_alloc_card(host, &sd_type);
		अगर (IS_ERR(card))
			वापस PTR_ERR(card);

		card->ocr = ocr;
		card->type = MMC_TYPE_SD;
		स_नकल(card->raw_cid, cid, माप(card->raw_cid));
	पूर्ण

	/*
	 * Call the optional HC's init_card function to handle quirks.
	 */
	अगर (host->ops->init_card)
		host->ops->init_card(host, card);

	/*
	 * For native busses:  get card RCA and quit खोलो drain mode.
	 */
	अगर (!mmc_host_is_spi(host)) अणु
		err = mmc_send_relative_addr(host, &card->rca);
		अगर (err)
			जाओ मुक्त_card;
	पूर्ण

	अगर (!oldcard) अणु
		err = mmc_sd_get_csd(card);
		अगर (err)
			जाओ मुक्त_card;

		mmc_decode_cid(card);
	पूर्ण

	/*
	 * handling only क्रम cards supporting DSR and hosts requesting
	 * DSR configuration
	 */
	अगर (card->csd.dsr_imp && host->dsr_req)
		mmc_set_dsr(host);

	/*
	 * Select card, as all following commands rely on that.
	 */
	अगर (!mmc_host_is_spi(host)) अणु
		err = mmc_select_card(card);
		अगर (err)
			जाओ मुक्त_card;
	पूर्ण

	err = mmc_sd_setup_card(host, card, oldcard != शून्य);
	अगर (err)
		जाओ मुक्त_card;

	/*
	 * If the card has not been घातer cycled, it may still be using 1.8V
	 * संकेतing. Detect that situation and try to initialize a UHS-I (1.8V)
	 * transfer mode.
	 */
	अगर (!v18_fixup_failed && !mmc_host_is_spi(host) && mmc_host_uhs(host) &&
	    mmc_sd_card_using_v18(card) &&
	    host->ios.संकेत_voltage != MMC_SIGNAL_VOLTAGE_180) अणु
		/*
		 * Re-पढ़ो चयन inक्रमmation in हाल it has changed since
		 * oldcard was initialized.
		 */
		अगर (oldcard) अणु
			err = mmc_पढ़ो_चयन(card);
			अगर (err)
				जाओ मुक्त_card;
		पूर्ण
		अगर (mmc_sd_card_using_v18(card)) अणु
			अगर (mmc_host_set_uhs_voltage(host) ||
			    mmc_sd_init_uhs_card(card)) अणु
				v18_fixup_failed = true;
				mmc_घातer_cycle(host, ocr);
				अगर (!oldcard)
					mmc_हटाओ_card(card);
				जाओ retry;
			पूर्ण
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* Initialization sequence क्रम UHS-I cards */
	अगर (rocr & SD_ROCR_S18A && mmc_host_uhs(host)) अणु
		err = mmc_sd_init_uhs_card(card);
		अगर (err)
			जाओ मुक्त_card;
	पूर्ण अन्यथा अणु
		/*
		 * Attempt to change to high-speed (अगर supported)
		 */
		err = mmc_sd_चयन_hs(card);
		अगर (err > 0)
			mmc_set_timing(card->host, MMC_TIMING_SD_HS);
		अन्यथा अगर (err)
			जाओ मुक्त_card;

		/*
		 * Set bus speed.
		 */
		mmc_set_घड़ी(host, mmc_sd_get_max_घड़ी(card));

		/*
		 * Switch to wider bus (अगर supported).
		 */
		अगर ((host->caps & MMC_CAP_4_BIT_DATA) &&
			(card->scr.bus_widths & SD_SCR_BUS_WIDTH_4)) अणु
			err = mmc_app_set_bus_width(card, MMC_BUS_WIDTH_4);
			अगर (err)
				जाओ मुक्त_card;

			mmc_set_bus_width(host, MMC_BUS_WIDTH_4);
		पूर्ण
	पूर्ण

	अगर (host->cqe_ops && !host->cqe_enabled) अणु
		err = host->cqe_ops->cqe_enable(host, card);
		अगर (!err) अणु
			host->cqe_enabled = true;
			host->hsq_enabled = true;
			pr_info("%s: Host Software Queue enabled\n",
				mmc_hostname(host));
		पूर्ण
	पूर्ण

	अगर (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		pr_err("%s: Host failed to negotiate down from 3.3V\n",
			mmc_hostname(host));
		err = -EINVAL;
		जाओ मुक्त_card;
	पूर्ण
करोne:
	host->card = card;
	वापस 0;

मुक्त_card:
	अगर (!oldcard)
		mmc_हटाओ_card(card);

	वापस err;
पूर्ण

/*
 * Host is being हटाओd. Free up the current card.
 */
अटल व्योम mmc_sd_हटाओ(काष्ठा mmc_host *host)
अणु
	mmc_हटाओ_card(host->card);
	host->card = शून्य;
पूर्ण

/*
 * Card detection - card is alive.
 */
अटल पूर्णांक mmc_sd_alive(काष्ठा mmc_host *host)
अणु
	वापस mmc_send_status(host->card, शून्य);
पूर्ण

/*
 * Card detection callback from host.
 */
अटल व्योम mmc_sd_detect(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	mmc_get_card(host->card, शून्य);

	/*
	 * Just check अगर our card has been हटाओd.
	 */
	err = _mmc_detect_card_हटाओd(host);

	mmc_put_card(host->card, शून्य);

	अगर (err) अणु
		mmc_sd_हटाओ(host);

		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_घातer_off(host);
		mmc_release_host(host);
	पूर्ण
पूर्ण

अटल पूर्णांक _mmc_sd_suspend(काष्ठा mmc_host *host)
अणु
	पूर्णांक err = 0;

	mmc_claim_host(host);

	अगर (mmc_card_suspended(host->card))
		जाओ out;

	अगर (!mmc_host_is_spi(host))
		err = mmc_deselect_cards(host);

	अगर (!err) अणु
		mmc_घातer_off(host);
		mmc_card_set_suspended(host->card);
	पूर्ण

out:
	mmc_release_host(host);
	वापस err;
पूर्ण

/*
 * Callback क्रम suspend
 */
अटल पूर्णांक mmc_sd_suspend(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	err = _mmc_sd_suspend(host);
	अगर (!err) अणु
		pm_runसमय_disable(&host->card->dev);
		pm_runसमय_set_suspended(&host->card->dev);
	पूर्ण

	वापस err;
पूर्ण

/*
 * This function tries to determine अगर the same card is still present
 * and, अगर so, restore all state to it.
 */
अटल पूर्णांक _mmc_sd_resume(काष्ठा mmc_host *host)
अणु
	पूर्णांक err = 0;

	mmc_claim_host(host);

	अगर (!mmc_card_suspended(host->card))
		जाओ out;

	mmc_घातer_up(host, host->card->ocr);
	err = mmc_sd_init_card(host, host->card->ocr, host->card);
	mmc_card_clr_suspended(host->card);

out:
	mmc_release_host(host);
	वापस err;
पूर्ण

/*
 * Callback क्रम resume
 */
अटल पूर्णांक mmc_sd_resume(काष्ठा mmc_host *host)
अणु
	pm_runसमय_enable(&host->card->dev);
	वापस 0;
पूर्ण

/*
 * Callback क्रम runसमय_suspend.
 */
अटल पूर्णांक mmc_sd_runसमय_suspend(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	अगर (!(host->caps & MMC_CAP_AGGRESSIVE_PM))
		वापस 0;

	err = _mmc_sd_suspend(host);
	अगर (err)
		pr_err("%s: error %d doing aggressive suspend\n",
			mmc_hostname(host), err);

	वापस err;
पूर्ण

/*
 * Callback क्रम runसमय_resume.
 */
अटल पूर्णांक mmc_sd_runसमय_resume(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	err = _mmc_sd_resume(host);
	अगर (err && err != -ENOMEDIUM)
		pr_err("%s: error %d doing runtime resume\n",
			mmc_hostname(host), err);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_sd_hw_reset(काष्ठा mmc_host *host)
अणु
	mmc_घातer_cycle(host, host->card->ocr);
	वापस mmc_sd_init_card(host, host->card->ocr, host->card);
पूर्ण

अटल स्थिर काष्ठा mmc_bus_ops mmc_sd_ops = अणु
	.हटाओ = mmc_sd_हटाओ,
	.detect = mmc_sd_detect,
	.runसमय_suspend = mmc_sd_runसमय_suspend,
	.runसमय_resume = mmc_sd_runसमय_resume,
	.suspend = mmc_sd_suspend,
	.resume = mmc_sd_resume,
	.alive = mmc_sd_alive,
	.shutकरोwn = mmc_sd_suspend,
	.hw_reset = mmc_sd_hw_reset,
पूर्ण;

/*
 * Starting poपूर्णांक क्रम SD card init.
 */
पूर्णांक mmc_attach_sd(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;
	u32 ocr, rocr;

	WARN_ON(!host->claimed);

	err = mmc_send_app_op_cond(host, 0, &ocr);
	अगर (err)
		वापस err;

	mmc_attach_bus(host, &mmc_sd_ops);
	अगर (host->ocr_avail_sd)
		host->ocr_avail = host->ocr_avail_sd;

	/*
	 * We need to get OCR a dअगरferent way क्रम SPI.
	 */
	अगर (mmc_host_is_spi(host)) अणु
		mmc_go_idle(host);

		err = mmc_spi_पढ़ो_ocr(host, 0, &ocr);
		अगर (err)
			जाओ err;
	पूर्ण

	/*
	 * Some SD cards claims an out of spec VDD voltage range. Let's treat
	 * these bits as being in-valid and especially also bit7.
	 */
	ocr &= ~0x7FFF;

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
	err = mmc_sd_init_card(host, rocr, शून्य);
	अगर (err)
		जाओ err;

	mmc_release_host(host);
	err = mmc_add_card(host->card);
	अगर (err)
		जाओ हटाओ_card;

	mmc_claim_host(host);
	वापस 0;

हटाओ_card:
	mmc_हटाओ_card(host->card);
	host->card = शून्य;
	mmc_claim_host(host);
err:
	mmc_detach_bus(host);

	pr_err("%s: error %d whilst initialising SD card\n",
		mmc_hostname(host), err);

	वापस err;
पूर्ण
