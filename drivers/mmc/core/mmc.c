<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/drivers/mmc/core/mmc.c
 *
 *  Copyright (C) 2003-2004 Russell King, All Rights Reserved.
 *  Copyright (C) 2005-2007 Pierre Ossman, All Rights Reserved.
 *  MMCv4 support Copyright (C) 2006 Philip Langdale, All Rights Reserved.
 */

#समावेश <linux/err.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/pm_runसमय.स>

#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/mmc.h>

#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"
#समावेश "bus.h"
#समावेश "mmc_ops.h"
#समावेश "quirks.h"
#समावेश "sd_ops.h"
#समावेश "pwrseq.h"

#घोषणा DEFAULT_CMD6_TIMEOUT_MS	500
#घोषणा MIN_CACHE_EN_TIMEOUT_MS 1600

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
अटल पूर्णांक mmc_decode_cid(काष्ठा mmc_card *card)
अणु
	u32 *resp = card->raw_cid;

	/*
	 * The selection of the क्रमmat here is based upon published
	 * specs from sandisk and from what people have reported.
	 */
	चयन (card->csd.mmca_vsn) अणु
	हाल 0: /* MMC v1.0 - v1.2 */
	हाल 1: /* MMC v1.4 */
		card->cid.manfid	= UNSTUFF_BITS(resp, 104, 24);
		card->cid.prod_name[0]	= UNSTUFF_BITS(resp, 96, 8);
		card->cid.prod_name[1]	= UNSTUFF_BITS(resp, 88, 8);
		card->cid.prod_name[2]	= UNSTUFF_BITS(resp, 80, 8);
		card->cid.prod_name[3]	= UNSTUFF_BITS(resp, 72, 8);
		card->cid.prod_name[4]	= UNSTUFF_BITS(resp, 64, 8);
		card->cid.prod_name[5]	= UNSTUFF_BITS(resp, 56, 8);
		card->cid.prod_name[6]	= UNSTUFF_BITS(resp, 48, 8);
		card->cid.hwrev		= UNSTUFF_BITS(resp, 44, 4);
		card->cid.fwrev		= UNSTUFF_BITS(resp, 40, 4);
		card->cid.serial	= UNSTUFF_BITS(resp, 16, 24);
		card->cid.month		= UNSTUFF_BITS(resp, 12, 4);
		card->cid.year		= UNSTUFF_BITS(resp, 8, 4) + 1997;
		अवरोध;

	हाल 2: /* MMC v2.0 - v2.2 */
	हाल 3: /* MMC v3.1 - v3.3 */
	हाल 4: /* MMC v4 */
		card->cid.manfid	= UNSTUFF_BITS(resp, 120, 8);
		card->cid.oemid		= UNSTUFF_BITS(resp, 104, 16);
		card->cid.prod_name[0]	= UNSTUFF_BITS(resp, 96, 8);
		card->cid.prod_name[1]	= UNSTUFF_BITS(resp, 88, 8);
		card->cid.prod_name[2]	= UNSTUFF_BITS(resp, 80, 8);
		card->cid.prod_name[3]	= UNSTUFF_BITS(resp, 72, 8);
		card->cid.prod_name[4]	= UNSTUFF_BITS(resp, 64, 8);
		card->cid.prod_name[5]	= UNSTUFF_BITS(resp, 56, 8);
		card->cid.prv		= UNSTUFF_BITS(resp, 48, 8);
		card->cid.serial	= UNSTUFF_BITS(resp, 16, 32);
		card->cid.month		= UNSTUFF_BITS(resp, 12, 4);
		card->cid.year		= UNSTUFF_BITS(resp, 8, 4) + 1997;
		अवरोध;

	शेष:
		pr_err("%s: card has unknown MMCA version %d\n",
			mmc_hostname(card->host), card->csd.mmca_vsn);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mmc_set_erase_size(काष्ठा mmc_card *card)
अणु
	अगर (card->ext_csd.erase_group_def & 1)
		card->erase_size = card->ext_csd.hc_erase_size;
	अन्यथा
		card->erase_size = card->csd.erase_size;

	mmc_init_erase(card);
पूर्ण

/*
 * Given a 128-bit response, decode to our card CSD काष्ठाure.
 */
अटल पूर्णांक mmc_decode_csd(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_csd *csd = &card->csd;
	अचिन्हित पूर्णांक e, m, a, b;
	u32 *resp = card->raw_csd;

	/*
	 * We only understand CSD काष्ठाure v1.1 and v1.2.
	 * v1.2 has extra inक्रमmation in bits 15, 11 and 10.
	 * We also support eMMC v4.4 & v4.41.
	 */
	csd->काष्ठाure = UNSTUFF_BITS(resp, 126, 2);
	अगर (csd->काष्ठाure == 0) अणु
		pr_err("%s: unrecognised CSD structure version %d\n",
			mmc_hostname(card->host), csd->काष्ठाure);
		वापस -EINVAL;
	पूर्ण

	csd->mmca_vsn	 = UNSTUFF_BITS(resp, 122, 4);
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

	अगर (csd->ग_लिखो_blkbits >= 9) अणु
		a = UNSTUFF_BITS(resp, 42, 5);
		b = UNSTUFF_BITS(resp, 37, 5);
		csd->erase_size = (a + 1) * (b + 1);
		csd->erase_size <<= csd->ग_लिखो_blkbits - 9;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम mmc_select_card_type(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	u8 card_type = card->ext_csd.raw_card_type;
	u32 caps = host->caps, caps2 = host->caps2;
	अचिन्हित पूर्णांक hs_max_dtr = 0, hs200_max_dtr = 0;
	अचिन्हित पूर्णांक avail_type = 0;

	अगर (caps & MMC_CAP_MMC_HIGHSPEED &&
	    card_type & EXT_CSD_CARD_TYPE_HS_26) अणु
		hs_max_dtr = MMC_HIGH_26_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS_26;
	पूर्ण

	अगर (caps & MMC_CAP_MMC_HIGHSPEED &&
	    card_type & EXT_CSD_CARD_TYPE_HS_52) अणु
		hs_max_dtr = MMC_HIGH_52_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS_52;
	पूर्ण

	अगर (caps & (MMC_CAP_1_8V_DDR | MMC_CAP_3_3V_DDR) &&
	    card_type & EXT_CSD_CARD_TYPE_DDR_1_8V) अणु
		hs_max_dtr = MMC_HIGH_DDR_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_DDR_1_8V;
	पूर्ण

	अगर (caps & MMC_CAP_1_2V_DDR &&
	    card_type & EXT_CSD_CARD_TYPE_DDR_1_2V) अणु
		hs_max_dtr = MMC_HIGH_DDR_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_DDR_1_2V;
	पूर्ण

	अगर (caps2 & MMC_CAP2_HS200_1_8V_SDR &&
	    card_type & EXT_CSD_CARD_TYPE_HS200_1_8V) अणु
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS200_1_8V;
	पूर्ण

	अगर (caps2 & MMC_CAP2_HS200_1_2V_SDR &&
	    card_type & EXT_CSD_CARD_TYPE_HS200_1_2V) अणु
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS200_1_2V;
	पूर्ण

	अगर (caps2 & MMC_CAP2_HS400_1_8V &&
	    card_type & EXT_CSD_CARD_TYPE_HS400_1_8V) अणु
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS400_1_8V;
	पूर्ण

	अगर (caps2 & MMC_CAP2_HS400_1_2V &&
	    card_type & EXT_CSD_CARD_TYPE_HS400_1_2V) अणु
		hs200_max_dtr = MMC_HS200_MAX_DTR;
		avail_type |= EXT_CSD_CARD_TYPE_HS400_1_2V;
	पूर्ण

	अगर ((caps2 & MMC_CAP2_HS400_ES) &&
	    card->ext_csd.strobe_support &&
	    (avail_type & EXT_CSD_CARD_TYPE_HS400))
		avail_type |= EXT_CSD_CARD_TYPE_HS400ES;

	card->ext_csd.hs_max_dtr = hs_max_dtr;
	card->ext_csd.hs200_max_dtr = hs200_max_dtr;
	card->mmc_avail_type = avail_type;
पूर्ण

अटल व्योम mmc_manage_enhanced_area(काष्ठा mmc_card *card, u8 *ext_csd)
अणु
	u8 hc_erase_grp_sz, hc_wp_grp_sz;

	/*
	 * Disable these attributes by शेष
	 */
	card->ext_csd.enhanced_area_offset = -EINVAL;
	card->ext_csd.enhanced_area_size = -EINVAL;

	/*
	 * Enhanced area feature support -- check whether the eMMC
	 * card has the Enhanced area enabled.  If so, export enhanced
	 * area offset and size to user by adding sysfs पूर्णांकerface.
	 */
	अगर ((ext_csd[EXT_CSD_PARTITION_SUPPORT] & 0x2) &&
	    (ext_csd[EXT_CSD_PARTITION_ATTRIBUTE] & 0x1)) अणु
		अगर (card->ext_csd.partition_setting_completed) अणु
			hc_erase_grp_sz =
				ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE];
			hc_wp_grp_sz =
				ext_csd[EXT_CSD_HC_WP_GRP_SIZE];

			/*
			 * calculate the enhanced data area offset, in bytes
			 */
			card->ext_csd.enhanced_area_offset =
				(((अचिन्हित दीर्घ दीर्घ)ext_csd[139]) << 24) +
				(((अचिन्हित दीर्घ दीर्घ)ext_csd[138]) << 16) +
				(((अचिन्हित दीर्घ दीर्घ)ext_csd[137]) << 8) +
				(((अचिन्हित दीर्घ दीर्घ)ext_csd[136]));
			अगर (mmc_card_blockaddr(card))
				card->ext_csd.enhanced_area_offset <<= 9;
			/*
			 * calculate the enhanced data area size, in kilobytes
			 */
			card->ext_csd.enhanced_area_size =
				(ext_csd[142] << 16) + (ext_csd[141] << 8) +
				ext_csd[140];
			card->ext_csd.enhanced_area_size *=
				(माप_प्रकार)(hc_erase_grp_sz * hc_wp_grp_sz);
			card->ext_csd.enhanced_area_size <<= 9;
		पूर्ण अन्यथा अणु
			pr_warn("%s: defines enhanced area without partition setting complete\n",
				mmc_hostname(card->host));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम mmc_part_add(काष्ठा mmc_card *card, u64 size,
			 अचिन्हित पूर्णांक part_cfg, अक्षर *name, पूर्णांक idx, bool ro,
			 पूर्णांक area_type)
अणु
	card->part[card->nr_parts].size = size;
	card->part[card->nr_parts].part_cfg = part_cfg;
	प्र_लिखो(card->part[card->nr_parts].name, name, idx);
	card->part[card->nr_parts].क्रमce_ro = ro;
	card->part[card->nr_parts].area_type = area_type;
	card->nr_parts++;
पूर्ण

अटल व्योम mmc_manage_gp_partitions(काष्ठा mmc_card *card, u8 *ext_csd)
अणु
	पूर्णांक idx;
	u8 hc_erase_grp_sz, hc_wp_grp_sz;
	u64 part_size;

	/*
	 * General purpose partition feature support --
	 * If ext_csd has the size of general purpose partitions,
	 * set size, part_cfg, partition name in mmc_part.
	 */
	अगर (ext_csd[EXT_CSD_PARTITION_SUPPORT] &
	    EXT_CSD_PART_SUPPORT_PART_EN) अणु
		hc_erase_grp_sz =
			ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE];
		hc_wp_grp_sz =
			ext_csd[EXT_CSD_HC_WP_GRP_SIZE];

		क्रम (idx = 0; idx < MMC_NUM_GP_PARTITION; idx++) अणु
			अगर (!ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3] &&
			    !ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 1] &&
			    !ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 2])
				जारी;
			अगर (card->ext_csd.partition_setting_completed == 0) अणु
				pr_warn("%s: has partition size defined without partition complete\n",
					mmc_hostname(card->host));
				अवरोध;
			पूर्ण
			part_size =
				(ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 2]
				<< 16) +
				(ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3 + 1]
				<< 8) +
				ext_csd[EXT_CSD_GP_SIZE_MULT + idx * 3];
			part_size *= (hc_erase_grp_sz * hc_wp_grp_sz);
			mmc_part_add(card, part_size << 19,
				EXT_CSD_PART_CONFIG_ACC_GP0 + idx,
				"gp%d", idx, false,
				MMC_BLK_DATA_AREA_GP);
		पूर्ण
	पूर्ण
पूर्ण

/* Minimum partition चयन समयout in milliseconds */
#घोषणा MMC_MIN_PART_SWITCH_TIME	300

/*
 * Decode extended CSD.
 */
अटल पूर्णांक mmc_decode_ext_csd(काष्ठा mmc_card *card, u8 *ext_csd)
अणु
	पूर्णांक err = 0, idx;
	u64 part_size;
	काष्ठा device_node *np;
	bool broken_hpi = false;

	/* Version is coded in the CSD_STRUCTURE byte in the EXT_CSD रेजिस्टर */
	card->ext_csd.raw_ext_csd_काष्ठाure = ext_csd[EXT_CSD_STRUCTURE];
	अगर (card->csd.काष्ठाure == 3) अणु
		अगर (card->ext_csd.raw_ext_csd_काष्ठाure > 2) अणु
			pr_err("%s: unrecognised EXT_CSD structure "
				"version %d\n", mmc_hostname(card->host),
					card->ext_csd.raw_ext_csd_काष्ठाure);
			err = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	np = mmc_of_find_child_device(card->host, 0);
	अगर (np && of_device_is_compatible(np, "mmc-card"))
		broken_hpi = of_property_पढ़ो_bool(np, "broken-hpi");
	of_node_put(np);

	/*
	 * The EXT_CSD क्रमmat is meant to be क्रमward compatible. As दीर्घ
	 * as CSD_STRUCTURE करोes not change, all values क्रम EXT_CSD_REV
	 * are authorized, see JEDEC JESD84-B50 section B.8.
	 */
	card->ext_csd.rev = ext_csd[EXT_CSD_REV];

	/* fixup device after ext_csd revision field is updated */
	mmc_fixup_device(card, mmc_ext_csd_fixups);

	card->ext_csd.raw_sectors[0] = ext_csd[EXT_CSD_SEC_CNT + 0];
	card->ext_csd.raw_sectors[1] = ext_csd[EXT_CSD_SEC_CNT + 1];
	card->ext_csd.raw_sectors[2] = ext_csd[EXT_CSD_SEC_CNT + 2];
	card->ext_csd.raw_sectors[3] = ext_csd[EXT_CSD_SEC_CNT + 3];
	अगर (card->ext_csd.rev >= 2) अणु
		card->ext_csd.sectors =
			ext_csd[EXT_CSD_SEC_CNT + 0] << 0 |
			ext_csd[EXT_CSD_SEC_CNT + 1] << 8 |
			ext_csd[EXT_CSD_SEC_CNT + 2] << 16 |
			ext_csd[EXT_CSD_SEC_CNT + 3] << 24;

		/* Cards with density > 2GiB are sector addressed */
		अगर (card->ext_csd.sectors > (2u * 1024 * 1024 * 1024) / 512)
			mmc_card_set_blockaddr(card);
	पूर्ण

	card->ext_csd.strobe_support = ext_csd[EXT_CSD_STROBE_SUPPORT];
	card->ext_csd.raw_card_type = ext_csd[EXT_CSD_CARD_TYPE];
	mmc_select_card_type(card);

	card->ext_csd.raw_s_a_समयout = ext_csd[EXT_CSD_S_A_TIMEOUT];
	card->ext_csd.raw_erase_समयout_mult =
		ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT];
	card->ext_csd.raw_hc_erase_grp_size =
		ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE];
	अगर (card->ext_csd.rev >= 3) अणु
		u8 sa_shअगरt = ext_csd[EXT_CSD_S_A_TIMEOUT];
		card->ext_csd.part_config = ext_csd[EXT_CSD_PART_CONFIG];

		/* EXT_CSD value is in units of 10ms, but we store in ms */
		card->ext_csd.part_समय = 10 * ext_csd[EXT_CSD_PART_SWITCH_TIME];

		/* Sleep / awake समयout in 100ns units */
		अगर (sa_shअगरt > 0 && sa_shअगरt <= 0x17)
			card->ext_csd.sa_समयout =
					1 << ext_csd[EXT_CSD_S_A_TIMEOUT];
		card->ext_csd.erase_group_def =
			ext_csd[EXT_CSD_ERASE_GROUP_DEF];
		card->ext_csd.hc_erase_समयout = 300 *
			ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT];
		card->ext_csd.hc_erase_size =
			ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE] << 10;

		card->ext_csd.rel_sectors = ext_csd[EXT_CSD_REL_WR_SEC_C];

		/*
		 * There are two boot regions of equal size, defined in
		 * multiples of 128K.
		 */
		अगर (ext_csd[EXT_CSD_BOOT_MULT] && mmc_boot_partition_access(card->host)) अणु
			क्रम (idx = 0; idx < MMC_NUM_BOOT_PARTITION; idx++) अणु
				part_size = ext_csd[EXT_CSD_BOOT_MULT] << 17;
				mmc_part_add(card, part_size,
					EXT_CSD_PART_CONFIG_ACC_BOOT0 + idx,
					"boot%d", idx, true,
					MMC_BLK_DATA_AREA_BOOT);
			पूर्ण
		पूर्ण
	पूर्ण

	card->ext_csd.raw_hc_erase_gap_size =
		ext_csd[EXT_CSD_HC_WP_GRP_SIZE];
	card->ext_csd.raw_sec_trim_mult =
		ext_csd[EXT_CSD_SEC_TRIM_MULT];
	card->ext_csd.raw_sec_erase_mult =
		ext_csd[EXT_CSD_SEC_ERASE_MULT];
	card->ext_csd.raw_sec_feature_support =
		ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT];
	card->ext_csd.raw_trim_mult =
		ext_csd[EXT_CSD_TRIM_MULT];
	card->ext_csd.raw_partition_support = ext_csd[EXT_CSD_PARTITION_SUPPORT];
	card->ext_csd.raw_driver_strength = ext_csd[EXT_CSD_DRIVER_STRENGTH];
	अगर (card->ext_csd.rev >= 4) अणु
		अगर (ext_csd[EXT_CSD_PARTITION_SETTING_COMPLETED] &
		    EXT_CSD_PART_SETTING_COMPLETED)
			card->ext_csd.partition_setting_completed = 1;
		अन्यथा
			card->ext_csd.partition_setting_completed = 0;

		mmc_manage_enhanced_area(card, ext_csd);

		mmc_manage_gp_partitions(card, ext_csd);

		card->ext_csd.sec_trim_mult =
			ext_csd[EXT_CSD_SEC_TRIM_MULT];
		card->ext_csd.sec_erase_mult =
			ext_csd[EXT_CSD_SEC_ERASE_MULT];
		card->ext_csd.sec_feature_support =
			ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT];
		card->ext_csd.trim_समयout = 300 *
			ext_csd[EXT_CSD_TRIM_MULT];

		/*
		 * Note that the call to mmc_part_add above शेषs to पढ़ो
		 * only. If this शेष assumption is changed, the call must
		 * take पूर्णांकo account the value of boot_locked below.
		 */
		card->ext_csd.boot_ro_lock = ext_csd[EXT_CSD_BOOT_WP];
		card->ext_csd.boot_ro_lockable = true;

		/* Save घातer class values */
		card->ext_csd.raw_pwr_cl_52_195 =
			ext_csd[EXT_CSD_PWR_CL_52_195];
		card->ext_csd.raw_pwr_cl_26_195 =
			ext_csd[EXT_CSD_PWR_CL_26_195];
		card->ext_csd.raw_pwr_cl_52_360 =
			ext_csd[EXT_CSD_PWR_CL_52_360];
		card->ext_csd.raw_pwr_cl_26_360 =
			ext_csd[EXT_CSD_PWR_CL_26_360];
		card->ext_csd.raw_pwr_cl_200_195 =
			ext_csd[EXT_CSD_PWR_CL_200_195];
		card->ext_csd.raw_pwr_cl_200_360 =
			ext_csd[EXT_CSD_PWR_CL_200_360];
		card->ext_csd.raw_pwr_cl_ddr_52_195 =
			ext_csd[EXT_CSD_PWR_CL_DDR_52_195];
		card->ext_csd.raw_pwr_cl_ddr_52_360 =
			ext_csd[EXT_CSD_PWR_CL_DDR_52_360];
		card->ext_csd.raw_pwr_cl_ddr_200_360 =
			ext_csd[EXT_CSD_PWR_CL_DDR_200_360];
	पूर्ण

	अगर (card->ext_csd.rev >= 5) अणु
		/* Adjust production date as per JEDEC JESD84-B451 */
		अगर (card->cid.year < 2010)
			card->cid.year += 16;

		/* check whether the eMMC card supports BKOPS */
		अगर (ext_csd[EXT_CSD_BKOPS_SUPPORT] & 0x1) अणु
			card->ext_csd.bkops = 1;
			card->ext_csd.man_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_MANUAL_BKOPS_MASK);
			card->ext_csd.raw_bkops_status =
				ext_csd[EXT_CSD_BKOPS_STATUS];
			अगर (card->ext_csd.man_bkops_en)
				pr_debug("%s: MAN_BKOPS_EN bit is set\n",
					mmc_hostname(card->host));
			card->ext_csd.स्वतः_bkops_en =
					(ext_csd[EXT_CSD_BKOPS_EN] &
						EXT_CSD_AUTO_BKOPS_MASK);
			अगर (card->ext_csd.स्वतः_bkops_en)
				pr_debug("%s: AUTO_BKOPS_EN bit is set\n",
					mmc_hostname(card->host));
		पूर्ण

		/* check whether the eMMC card supports HPI */
		अगर (!mmc_card_broken_hpi(card) &&
		    !broken_hpi && (ext_csd[EXT_CSD_HPI_FEATURES] & 0x1)) अणु
			card->ext_csd.hpi = 1;
			अगर (ext_csd[EXT_CSD_HPI_FEATURES] & 0x2)
				card->ext_csd.hpi_cmd =	MMC_STOP_TRANSMISSION;
			अन्यथा
				card->ext_csd.hpi_cmd = MMC_SEND_STATUS;
			/*
			 * Indicate the maximum समयout to बंद
			 * a command पूर्णांकerrupted by HPI
			 */
			card->ext_csd.out_of_पूर्णांक_समय =
				ext_csd[EXT_CSD_OUT_OF_INTERRUPT_TIME] * 10;
		पूर्ण

		card->ext_csd.rel_param = ext_csd[EXT_CSD_WR_REL_PARAM];
		card->ext_csd.rst_n_function = ext_csd[EXT_CSD_RST_N_FUNCTION];

		/*
		 * RPMB regions are defined in multiples of 128K.
		 */
		card->ext_csd.raw_rpmb_size_mult = ext_csd[EXT_CSD_RPMB_MULT];
		अगर (ext_csd[EXT_CSD_RPMB_MULT] && mmc_host_cmd23(card->host)) अणु
			mmc_part_add(card, ext_csd[EXT_CSD_RPMB_MULT] << 17,
				EXT_CSD_PART_CONFIG_ACC_RPMB,
				"rpmb", 0, false,
				MMC_BLK_DATA_AREA_RPMB);
		पूर्ण
	पूर्ण

	card->ext_csd.raw_erased_mem_count = ext_csd[EXT_CSD_ERASED_MEM_CONT];
	अगर (ext_csd[EXT_CSD_ERASED_MEM_CONT])
		card->erased_byte = 0xFF;
	अन्यथा
		card->erased_byte = 0x0;

	/* eMMC v4.5 or later */
	card->ext_csd.generic_cmd6_समय = DEFAULT_CMD6_TIMEOUT_MS;
	अगर (card->ext_csd.rev >= 6) अणु
		card->ext_csd.feature_support |= MMC_DISCARD_FEATURE;

		card->ext_csd.generic_cmd6_समय = 10 *
			ext_csd[EXT_CSD_GENERIC_CMD6_TIME];
		card->ext_csd.घातer_off_दीर्घसमय = 10 *
			ext_csd[EXT_CSD_POWER_OFF_LONG_TIME];

		card->ext_csd.cache_size =
			ext_csd[EXT_CSD_CACHE_SIZE + 0] << 0 |
			ext_csd[EXT_CSD_CACHE_SIZE + 1] << 8 |
			ext_csd[EXT_CSD_CACHE_SIZE + 2] << 16 |
			ext_csd[EXT_CSD_CACHE_SIZE + 3] << 24;

		अगर (ext_csd[EXT_CSD_DATA_SECTOR_SIZE] == 1)
			card->ext_csd.data_sector_size = 4096;
		अन्यथा
			card->ext_csd.data_sector_size = 512;

		अगर ((ext_csd[EXT_CSD_DATA_TAG_SUPPORT] & 1) &&
		    (ext_csd[EXT_CSD_TAG_UNIT_SIZE] <= 8)) अणु
			card->ext_csd.data_tag_unit_size =
			((अचिन्हित पूर्णांक) 1 << ext_csd[EXT_CSD_TAG_UNIT_SIZE]) *
			(card->ext_csd.data_sector_size);
		पूर्ण अन्यथा अणु
			card->ext_csd.data_tag_unit_size = 0;
		पूर्ण

		card->ext_csd.max_packed_ग_लिखोs =
			ext_csd[EXT_CSD_MAX_PACKED_WRITES];
		card->ext_csd.max_packed_पढ़ोs =
			ext_csd[EXT_CSD_MAX_PACKED_READS];
	पूर्ण अन्यथा अणु
		card->ext_csd.data_sector_size = 512;
	पूर्ण

	/*
	 * GENERIC_CMD6_TIME is to be used "unless a specअगरic समयout is defined
	 * when accessing a specअगरic field", so use it here अगर there is no
	 * PARTITION_SWITCH_TIME.
	 */
	अगर (!card->ext_csd.part_समय)
		card->ext_csd.part_समय = card->ext_csd.generic_cmd6_समय;
	/* Some eMMC set the value too low so set a minimum */
	अगर (card->ext_csd.part_समय < MMC_MIN_PART_SWITCH_TIME)
		card->ext_csd.part_समय = MMC_MIN_PART_SWITCH_TIME;

	/* eMMC v5 or later */
	अगर (card->ext_csd.rev >= 7) अणु
		स_नकल(card->ext_csd.fwrev, &ext_csd[EXT_CSD_FIRMWARE_VERSION],
		       MMC_FIRMWARE_LEN);
		card->ext_csd.ffu_capable =
			(ext_csd[EXT_CSD_SUPPORTED_MODE] & 0x1) &&
			!(ext_csd[EXT_CSD_FW_CONFIG] & 0x1);

		card->ext_csd.pre_eol_info = ext_csd[EXT_CSD_PRE_EOL_INFO];
		card->ext_csd.device_lअगरe_समय_est_typ_a =
			ext_csd[EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_A];
		card->ext_csd.device_lअगरe_समय_est_typ_b =
			ext_csd[EXT_CSD_DEVICE_LIFE_TIME_EST_TYP_B];
	पूर्ण

	/* eMMC v5.1 or later */
	अगर (card->ext_csd.rev >= 8) अणु
		card->ext_csd.cmdq_support = ext_csd[EXT_CSD_CMDQ_SUPPORT] &
					     EXT_CSD_CMDQ_SUPPORTED;
		card->ext_csd.cmdq_depth = (ext_csd[EXT_CSD_CMDQ_DEPTH] &
					    EXT_CSD_CMDQ_DEPTH_MASK) + 1;
		/* Exclude inefficiently small queue depths */
		अगर (card->ext_csd.cmdq_depth <= 2) अणु
			card->ext_csd.cmdq_support = false;
			card->ext_csd.cmdq_depth = 0;
		पूर्ण
		अगर (card->ext_csd.cmdq_support) अणु
			pr_debug("%s: Command Queue supported depth %u\n",
				 mmc_hostname(card->host),
				 card->ext_csd.cmdq_depth);
		पूर्ण
		card->ext_csd.enhanced_rpmb_supported =
					(card->ext_csd.rel_param &
					 EXT_CSD_WR_REL_PARAM_EN_RPMB_REL_WR);
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक mmc_पढ़ो_ext_csd(काष्ठा mmc_card *card)
अणु
	u8 *ext_csd;
	पूर्णांक err;

	अगर (!mmc_can_ext_csd(card))
		वापस 0;

	err = mmc_get_ext_csd(card, &ext_csd);
	अगर (err) अणु
		/* If the host or the card can't करो the चयन,
		 * fail more gracefully. */
		अगर ((err != -EINVAL)
		 && (err != -ENOSYS)
		 && (err != -EFAULT))
			वापस err;

		/*
		 * High capacity cards should have this "magic" size
		 * stored in their CSD.
		 */
		अगर (card->csd.capacity == (4096 * 512)) अणु
			pr_err("%s: unable to read EXT_CSD on a possible high capacity card. Card will be ignored.\n",
				mmc_hostname(card->host));
		पूर्ण अन्यथा अणु
			pr_warn("%s: unable to read EXT_CSD, performance might suffer\n",
				mmc_hostname(card->host));
			err = 0;
		पूर्ण

		वापस err;
	पूर्ण

	err = mmc_decode_ext_csd(card, ext_csd);
	kमुक्त(ext_csd);
	वापस err;
पूर्ण

अटल पूर्णांक mmc_compare_ext_csds(काष्ठा mmc_card *card, अचिन्हित bus_width)
अणु
	u8 *bw_ext_csd;
	पूर्णांक err;

	अगर (bus_width == MMC_BUS_WIDTH_1)
		वापस 0;

	err = mmc_get_ext_csd(card, &bw_ext_csd);
	अगर (err)
		वापस err;

	/* only compare पढ़ो only fields */
	err = !((card->ext_csd.raw_partition_support ==
			bw_ext_csd[EXT_CSD_PARTITION_SUPPORT]) &&
		(card->ext_csd.raw_erased_mem_count ==
			bw_ext_csd[EXT_CSD_ERASED_MEM_CONT]) &&
		(card->ext_csd.rev ==
			bw_ext_csd[EXT_CSD_REV]) &&
		(card->ext_csd.raw_ext_csd_काष्ठाure ==
			bw_ext_csd[EXT_CSD_STRUCTURE]) &&
		(card->ext_csd.raw_card_type ==
			bw_ext_csd[EXT_CSD_CARD_TYPE]) &&
		(card->ext_csd.raw_s_a_समयout ==
			bw_ext_csd[EXT_CSD_S_A_TIMEOUT]) &&
		(card->ext_csd.raw_hc_erase_gap_size ==
			bw_ext_csd[EXT_CSD_HC_WP_GRP_SIZE]) &&
		(card->ext_csd.raw_erase_समयout_mult ==
			bw_ext_csd[EXT_CSD_ERASE_TIMEOUT_MULT]) &&
		(card->ext_csd.raw_hc_erase_grp_size ==
			bw_ext_csd[EXT_CSD_HC_ERASE_GRP_SIZE]) &&
		(card->ext_csd.raw_sec_trim_mult ==
			bw_ext_csd[EXT_CSD_SEC_TRIM_MULT]) &&
		(card->ext_csd.raw_sec_erase_mult ==
			bw_ext_csd[EXT_CSD_SEC_ERASE_MULT]) &&
		(card->ext_csd.raw_sec_feature_support ==
			bw_ext_csd[EXT_CSD_SEC_FEATURE_SUPPORT]) &&
		(card->ext_csd.raw_trim_mult ==
			bw_ext_csd[EXT_CSD_TRIM_MULT]) &&
		(card->ext_csd.raw_sectors[0] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 0]) &&
		(card->ext_csd.raw_sectors[1] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 1]) &&
		(card->ext_csd.raw_sectors[2] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 2]) &&
		(card->ext_csd.raw_sectors[3] ==
			bw_ext_csd[EXT_CSD_SEC_CNT + 3]) &&
		(card->ext_csd.raw_pwr_cl_52_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_52_195]) &&
		(card->ext_csd.raw_pwr_cl_26_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_26_195]) &&
		(card->ext_csd.raw_pwr_cl_52_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_52_360]) &&
		(card->ext_csd.raw_pwr_cl_26_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_26_360]) &&
		(card->ext_csd.raw_pwr_cl_200_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_200_195]) &&
		(card->ext_csd.raw_pwr_cl_200_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_200_360]) &&
		(card->ext_csd.raw_pwr_cl_ddr_52_195 ==
			bw_ext_csd[EXT_CSD_PWR_CL_DDR_52_195]) &&
		(card->ext_csd.raw_pwr_cl_ddr_52_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_DDR_52_360]) &&
		(card->ext_csd.raw_pwr_cl_ddr_200_360 ==
			bw_ext_csd[EXT_CSD_PWR_CL_DDR_200_360]));

	अगर (err)
		err = -EINVAL;

	kमुक्त(bw_ext_csd);
	वापस err;
पूर्ण

MMC_DEV_ATTR(cid, "%08x%08x%08x%08x\n", card->raw_cid[0], card->raw_cid[1],
	card->raw_cid[2], card->raw_cid[3]);
MMC_DEV_ATTR(csd, "%08x%08x%08x%08x\n", card->raw_csd[0], card->raw_csd[1],
	card->raw_csd[2], card->raw_csd[3]);
MMC_DEV_ATTR(date, "%02d/%04d\n", card->cid.month, card->cid.year);
MMC_DEV_ATTR(erase_size, "%u\n", card->erase_size << 9);
MMC_DEV_ATTR(preferred_erase_size, "%u\n", card->pref_erase << 9);
MMC_DEV_ATTR(ffu_capable, "%d\n", card->ext_csd.ffu_capable);
MMC_DEV_ATTR(hwrev, "0x%x\n", card->cid.hwrev);
MMC_DEV_ATTR(manfid, "0x%06x\n", card->cid.manfid);
MMC_DEV_ATTR(name, "%s\n", card->cid.prod_name);
MMC_DEV_ATTR(oemid, "0x%04x\n", card->cid.oemid);
MMC_DEV_ATTR(prv, "0x%x\n", card->cid.prv);
MMC_DEV_ATTR(rev, "0x%x\n", card->ext_csd.rev);
MMC_DEV_ATTR(pre_eol_info, "0x%02x\n", card->ext_csd.pre_eol_info);
MMC_DEV_ATTR(lअगरe_समय, "0x%02x 0x%02x\n",
	card->ext_csd.device_lअगरe_समय_est_typ_a,
	card->ext_csd.device_lअगरe_समय_est_typ_b);
MMC_DEV_ATTR(serial, "0x%08x\n", card->cid.serial);
MMC_DEV_ATTR(enhanced_area_offset, "%llu\n",
		card->ext_csd.enhanced_area_offset);
MMC_DEV_ATTR(enhanced_area_size, "%u\n", card->ext_csd.enhanced_area_size);
MMC_DEV_ATTR(raw_rpmb_size_mult, "%#x\n", card->ext_csd.raw_rpmb_size_mult);
MMC_DEV_ATTR(enhanced_rpmb_supported, "%#x\n",
	card->ext_csd.enhanced_rpmb_supported);
MMC_DEV_ATTR(rel_sectors, "%#x\n", card->ext_csd.rel_sectors);
MMC_DEV_ATTR(ocr, "0x%08x\n", card->ocr);
MMC_DEV_ATTR(rca, "0x%04x\n", card->rca);
MMC_DEV_ATTR(cmdq_en, "%d\n", card->ext_csd.cmdq_en);

अटल sमाप_प्रकार mmc_fwrev_show(काष्ठा device *dev,
			      काष्ठा device_attribute *attr,
			      अक्षर *buf)
अणु
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);

	अगर (card->ext_csd.rev < 7) अणु
		वापस प्र_लिखो(buf, "0x%x\n", card->cid.fwrev);
	पूर्ण अन्यथा अणु
		वापस प्र_लिखो(buf, "0x%*phN\n", MMC_FIRMWARE_LEN,
			       card->ext_csd.fwrev);
	पूर्ण
पूर्ण

अटल DEVICE_ATTR(fwrev, S_IRUGO, mmc_fwrev_show, शून्य);

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

अटल काष्ठा attribute *mmc_std_attrs[] = अणु
	&dev_attr_cid.attr,
	&dev_attr_csd.attr,
	&dev_attr_date.attr,
	&dev_attr_erase_size.attr,
	&dev_attr_preferred_erase_size.attr,
	&dev_attr_fwrev.attr,
	&dev_attr_ffu_capable.attr,
	&dev_attr_hwrev.attr,
	&dev_attr_manfid.attr,
	&dev_attr_name.attr,
	&dev_attr_oemid.attr,
	&dev_attr_prv.attr,
	&dev_attr_rev.attr,
	&dev_attr_pre_eol_info.attr,
	&dev_attr_lअगरe_समय.attr,
	&dev_attr_serial.attr,
	&dev_attr_enhanced_area_offset.attr,
	&dev_attr_enhanced_area_size.attr,
	&dev_attr_raw_rpmb_size_mult.attr,
	&dev_attr_enhanced_rpmb_supported.attr,
	&dev_attr_rel_sectors.attr,
	&dev_attr_ocr.attr,
	&dev_attr_rca.attr,
	&dev_attr_dsr.attr,
	&dev_attr_cmdq_en.attr,
	शून्य,
पूर्ण;
ATTRIBUTE_GROUPS(mmc_std);

अटल काष्ठा device_type mmc_type = अणु
	.groups = mmc_std_groups,
पूर्ण;

/*
 * Select the PowerClass क्रम the current bus width
 * If घातer class is defined क्रम 4/8 bit bus in the
 * extended CSD रेजिस्टर, select it by executing the
 * mmc_चयन command.
 */
अटल पूर्णांक __mmc_select_घातerclass(काष्ठा mmc_card *card,
				   अचिन्हित पूर्णांक bus_width)
अणु
	काष्ठा mmc_host *host = card->host;
	काष्ठा mmc_ext_csd *ext_csd = &card->ext_csd;
	अचिन्हित पूर्णांक pwrclass_val = 0;
	पूर्णांक err = 0;

	चयन (1 << host->ios.vdd) अणु
	हाल MMC_VDD_165_195:
		अगर (host->ios.घड़ी <= MMC_HIGH_26_MAX_DTR)
			pwrclass_val = ext_csd->raw_pwr_cl_26_195;
		अन्यथा अगर (host->ios.घड़ी <= MMC_HIGH_52_MAX_DTR)
			pwrclass_val = (bus_width <= EXT_CSD_BUS_WIDTH_8) ?
				ext_csd->raw_pwr_cl_52_195 :
				ext_csd->raw_pwr_cl_ddr_52_195;
		अन्यथा अगर (host->ios.घड़ी <= MMC_HS200_MAX_DTR)
			pwrclass_val = ext_csd->raw_pwr_cl_200_195;
		अवरोध;
	हाल MMC_VDD_27_28:
	हाल MMC_VDD_28_29:
	हाल MMC_VDD_29_30:
	हाल MMC_VDD_30_31:
	हाल MMC_VDD_31_32:
	हाल MMC_VDD_32_33:
	हाल MMC_VDD_33_34:
	हाल MMC_VDD_34_35:
	हाल MMC_VDD_35_36:
		अगर (host->ios.घड़ी <= MMC_HIGH_26_MAX_DTR)
			pwrclass_val = ext_csd->raw_pwr_cl_26_360;
		अन्यथा अगर (host->ios.घड़ी <= MMC_HIGH_52_MAX_DTR)
			pwrclass_val = (bus_width <= EXT_CSD_BUS_WIDTH_8) ?
				ext_csd->raw_pwr_cl_52_360 :
				ext_csd->raw_pwr_cl_ddr_52_360;
		अन्यथा अगर (host->ios.घड़ी <= MMC_HS200_MAX_DTR)
			pwrclass_val = (bus_width == EXT_CSD_DDR_BUS_WIDTH_8) ?
				ext_csd->raw_pwr_cl_ddr_200_360 :
				ext_csd->raw_pwr_cl_200_360;
		अवरोध;
	शेष:
		pr_warn("%s: Voltage range not supported for power class\n",
			mmc_hostname(host));
		वापस -EINVAL;
	पूर्ण

	अगर (bus_width & (EXT_CSD_BUS_WIDTH_8 | EXT_CSD_DDR_BUS_WIDTH_8))
		pwrclass_val = (pwrclass_val & EXT_CSD_PWR_CL_8BIT_MASK) >>
				EXT_CSD_PWR_CL_8BIT_SHIFT;
	अन्यथा
		pwrclass_val = (pwrclass_val & EXT_CSD_PWR_CL_4BIT_MASK) >>
				EXT_CSD_PWR_CL_4BIT_SHIFT;

	/* If the घातer class is dअगरferent from the शेष value */
	अगर (pwrclass_val > 0) अणु
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_POWER_CLASS,
				 pwrclass_val,
				 card->ext_csd.generic_cmd6_समय);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mmc_select_घातerclass(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	u32 bus_width, ext_csd_bits;
	पूर्णांक err, ddr;

	/* Power class selection is supported क्रम versions >= 4.0 */
	अगर (!mmc_can_ext_csd(card))
		वापस 0;

	bus_width = host->ios.bus_width;
	/* Power class values are defined only क्रम 4/8 bit bus */
	अगर (bus_width == MMC_BUS_WIDTH_1)
		वापस 0;

	ddr = card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_52;
	अगर (ddr)
		ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
			EXT_CSD_DDR_BUS_WIDTH_8 : EXT_CSD_DDR_BUS_WIDTH_4;
	अन्यथा
		ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
			EXT_CSD_BUS_WIDTH_8 :  EXT_CSD_BUS_WIDTH_4;

	err = __mmc_select_घातerclass(card, ext_csd_bits);
	अगर (err)
		pr_warn("%s: power class selection to bus width %d ddr %d failed\n",
			mmc_hostname(host), 1 << bus_width, ddr);

	वापस err;
पूर्ण

/*
 * Set the bus speed क्रम the selected speed mode.
 */
अटल व्योम mmc_set_bus_speed(काष्ठा mmc_card *card)
अणु
	अचिन्हित पूर्णांक max_dtr = (अचिन्हित पूर्णांक)-1;

	अगर ((mmc_card_hs200(card) || mmc_card_hs400(card)) &&
	     max_dtr > card->ext_csd.hs200_max_dtr)
		max_dtr = card->ext_csd.hs200_max_dtr;
	अन्यथा अगर (mmc_card_hs(card) && max_dtr > card->ext_csd.hs_max_dtr)
		max_dtr = card->ext_csd.hs_max_dtr;
	अन्यथा अगर (max_dtr > card->csd.max_dtr)
		max_dtr = card->csd.max_dtr;

	mmc_set_घड़ी(card->host, max_dtr);
पूर्ण

/*
 * Select the bus width amoung 4-bit and 8-bit(SDR).
 * If the bus width is changed successfully, वापस the selected width value.
 * Zero is वापसed instead of error value अगर the wide width is not supported.
 */
अटल पूर्णांक mmc_select_bus_width(काष्ठा mmc_card *card)
अणु
	अटल अचिन्हित ext_csd_bits[] = अणु
		EXT_CSD_BUS_WIDTH_8,
		EXT_CSD_BUS_WIDTH_4,
	पूर्ण;
	अटल अचिन्हित bus_widths[] = अणु
		MMC_BUS_WIDTH_8,
		MMC_BUS_WIDTH_4,
	पूर्ण;
	काष्ठा mmc_host *host = card->host;
	अचिन्हित idx, bus_width = 0;
	पूर्णांक err = 0;

	अगर (!mmc_can_ext_csd(card) ||
	    !(host->caps & (MMC_CAP_4_BIT_DATA | MMC_CAP_8_BIT_DATA)))
		वापस 0;

	idx = (host->caps & MMC_CAP_8_BIT_DATA) ? 0 : 1;

	/*
	 * Unlike SD, MMC cards करोnt have a configuration रेजिस्टर to notअगरy
	 * supported bus width. So bus test command should be run to identअगरy
	 * the supported bus width or compare the ext csd values of current
	 * bus width and ext csd values of 1 bit mode पढ़ो earlier.
	 */
	क्रम (; idx < ARRAY_SIZE(bus_widths); idx++) अणु
		/*
		 * Host is capable of 8bit transfer, then चयन
		 * the device to work in 8bit transfer mode. If the
		 * mmc चयन command वापसs error then चयन to
		 * 4bit transfer mode. On success set the corresponding
		 * bus width on the host.
		 */
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_BUS_WIDTH,
				 ext_csd_bits[idx],
				 card->ext_csd.generic_cmd6_समय);
		अगर (err)
			जारी;

		bus_width = bus_widths[idx];
		mmc_set_bus_width(host, bus_width);

		/*
		 * If controller can't handle bus width test,
		 * compare ext_csd previously पढ़ो in 1 bit mode
		 * against ext_csd at new bus width
		 */
		अगर (!(host->caps & MMC_CAP_BUS_WIDTH_TEST))
			err = mmc_compare_ext_csds(card, bus_width);
		अन्यथा
			err = mmc_bus_test(card, bus_width);

		अगर (!err) अणु
			err = bus_width;
			अवरोध;
		पूर्ण अन्यथा अणु
			pr_warn("%s: switch to bus width %d failed\n",
				mmc_hostname(host), 1 << bus_width);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

/*
 * Switch to the high-speed mode
 */
अटल पूर्णांक mmc_select_hs(काष्ठा mmc_card *card)
अणु
	पूर्णांक err;

	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_HS_TIMING, EXT_CSD_TIMING_HS,
			   card->ext_csd.generic_cmd6_समय, MMC_TIMING_MMC_HS,
			   true, true, MMC_CMD_RETRIES);
	अगर (err)
		pr_warn("%s: switch to high-speed failed, err:%d\n",
			mmc_hostname(card->host), err);

	वापस err;
पूर्ण

/*
 * Activate wide bus and DDR अगर supported.
 */
अटल पूर्णांक mmc_select_hs_ddr(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	u32 bus_width, ext_csd_bits;
	पूर्णांक err = 0;

	अगर (!(card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_52))
		वापस 0;

	bus_width = host->ios.bus_width;
	अगर (bus_width == MMC_BUS_WIDTH_1)
		वापस 0;

	ext_csd_bits = (bus_width == MMC_BUS_WIDTH_8) ?
		EXT_CSD_DDR_BUS_WIDTH_8 : EXT_CSD_DDR_BUS_WIDTH_4;

	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_BUS_WIDTH,
			   ext_csd_bits,
			   card->ext_csd.generic_cmd6_समय,
			   MMC_TIMING_MMC_DDR52,
			   true, true, MMC_CMD_RETRIES);
	अगर (err) अणु
		pr_err("%s: switch to bus width %d ddr failed\n",
			mmc_hostname(host), 1 << bus_width);
		वापस err;
	पूर्ण

	/*
	 * eMMC cards can support 3.3V to 1.2V i/o (vccq)
	 * संकेतing.
	 *
	 * EXT_CSD_CARD_TYPE_DDR_1_8V means 3.3V or 1.8V vccq.
	 *
	 * 1.8V vccq at 3.3V core voltage (vcc) is not required
	 * in the JEDEC spec क्रम DDR.
	 *
	 * Even (e)MMC card can support 3.3v to 1.2v vccq, but not all
	 * host controller can support this, like some of the SDHCI
	 * controller which connect to an eMMC device. Some of these
	 * host controller still needs to use 1.8v vccq क्रम supporting
	 * DDR mode.
	 *
	 * So the sequence will be:
	 * अगर (host and device can both support 1.2v IO)
	 *	use 1.2v IO;
	 * अन्यथा अगर (host and device can both support 1.8v IO)
	 *	use 1.8v IO;
	 * so अगर host and device can only support 3.3v IO, this is the
	 * last choice.
	 *
	 * WARNING: eMMC rules are NOT the same as SD DDR
	 */
	अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_1_2V) अणु
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_120);
		अगर (!err)
			वापस 0;
	पूर्ण

	अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_DDR_1_8V &&
	    host->caps & MMC_CAP_1_8V_DDR)
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_180);

	/* make sure vccq is 3.3v after चयनing disaster */
	अगर (err)
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_330);

	वापस err;
पूर्ण

अटल पूर्णांक mmc_select_hs400(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	अचिन्हित पूर्णांक max_dtr;
	पूर्णांक err = 0;
	u8 val;

	/*
	 * HS400 mode requires 8-bit bus width
	 */
	अगर (!(card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS400 &&
	      host->ios.bus_width == MMC_BUS_WIDTH_8))
		वापस 0;

	/* Switch card to HS mode */
	val = EXT_CSD_TIMING_HS;
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_HS_TIMING, val,
			   card->ext_csd.generic_cmd6_समय, 0,
			   false, true, MMC_CMD_RETRIES);
	अगर (err) अणु
		pr_err("%s: switch to high-speed from hs200 failed, err:%d\n",
			mmc_hostname(host), err);
		वापस err;
	पूर्ण

	/* Prepare host to करोwngrade to HS timing */
	अगर (host->ops->hs400_करोwngrade)
		host->ops->hs400_करोwngrade(host);

	/* Set host controller to HS timing */
	mmc_set_timing(host, MMC_TIMING_MMC_HS);

	/* Reduce frequency to HS frequency */
	max_dtr = card->ext_csd.hs_max_dtr;
	mmc_set_घड़ी(host, max_dtr);

	err = mmc_चयन_status(card, true);
	अगर (err)
		जाओ out_err;

	अगर (host->ops->hs400_prepare_ddr)
		host->ops->hs400_prepare_ddr(host);

	/* Switch card to DDR */
	err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			 EXT_CSD_BUS_WIDTH,
			 EXT_CSD_DDR_BUS_WIDTH_8,
			 card->ext_csd.generic_cmd6_समय);
	अगर (err) अणु
		pr_err("%s: switch to bus width for hs400 failed, err:%d\n",
			mmc_hostname(host), err);
		वापस err;
	पूर्ण

	/* Switch card to HS400 */
	val = EXT_CSD_TIMING_HS400 |
	      card->drive_strength << EXT_CSD_DRV_STR_SHIFT;
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_HS_TIMING, val,
			   card->ext_csd.generic_cmd6_समय, 0,
			   false, true, MMC_CMD_RETRIES);
	अगर (err) अणु
		pr_err("%s: switch to hs400 failed, err:%d\n",
			 mmc_hostname(host), err);
		वापस err;
	पूर्ण

	/* Set host controller to HS400 timing and frequency */
	mmc_set_timing(host, MMC_TIMING_MMC_HS400);
	mmc_set_bus_speed(card);

	अगर (host->ops->hs400_complete)
		host->ops->hs400_complete(host);

	err = mmc_चयन_status(card, true);
	अगर (err)
		जाओ out_err;

	वापस 0;

out_err:
	pr_err("%s: %s failed, error %d\n", mmc_hostname(card->host),
	       __func__, err);
	वापस err;
पूर्ण

पूर्णांक mmc_hs200_to_hs400(काष्ठा mmc_card *card)
अणु
	वापस mmc_select_hs400(card);
पूर्ण

पूर्णांक mmc_hs400_to_hs200(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	अचिन्हित पूर्णांक max_dtr;
	पूर्णांक err;
	u8 val;

	/* Reduce frequency to HS */
	max_dtr = card->ext_csd.hs_max_dtr;
	mmc_set_घड़ी(host, max_dtr);

	/* Switch HS400 to HS DDR */
	val = EXT_CSD_TIMING_HS;
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_HS_TIMING,
			   val, card->ext_csd.generic_cmd6_समय, 0,
			   false, true, MMC_CMD_RETRIES);
	अगर (err)
		जाओ out_err;

	अगर (host->ops->hs400_करोwngrade)
		host->ops->hs400_करोwngrade(host);

	mmc_set_timing(host, MMC_TIMING_MMC_DDR52);

	err = mmc_चयन_status(card, true);
	अगर (err)
		जाओ out_err;

	/* Switch HS DDR to HS */
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_BUS_WIDTH,
			   EXT_CSD_BUS_WIDTH_8, card->ext_csd.generic_cmd6_समय,
			   0, false, true, MMC_CMD_RETRIES);
	अगर (err)
		जाओ out_err;

	mmc_set_timing(host, MMC_TIMING_MMC_HS);

	err = mmc_चयन_status(card, true);
	अगर (err)
		जाओ out_err;

	/* Switch HS to HS200 */
	val = EXT_CSD_TIMING_HS200 |
	      card->drive_strength << EXT_CSD_DRV_STR_SHIFT;
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_HS_TIMING,
			   val, card->ext_csd.generic_cmd6_समय, 0,
			   false, true, MMC_CMD_RETRIES);
	अगर (err)
		जाओ out_err;

	mmc_set_timing(host, MMC_TIMING_MMC_HS200);

	/*
	 * For HS200, CRC errors are not a reliable way to know the चयन
	 * failed. If there really is a problem, we would expect tuning will
	 * fail and the result ends up the same.
	 */
	err = mmc_चयन_status(card, false);
	अगर (err)
		जाओ out_err;

	mmc_set_bus_speed(card);

	/* Prepare tuning क्रम HS400 mode. */
	अगर (host->ops->prepare_hs400_tuning)
		host->ops->prepare_hs400_tuning(host, &host->ios);

	वापस 0;

out_err:
	pr_err("%s: %s failed, error %d\n", mmc_hostname(card->host),
	       __func__, err);
	वापस err;
पूर्ण

अटल व्योम mmc_select_driver_type(काष्ठा mmc_card *card)
अणु
	पूर्णांक card_drv_type, drive_strength, drv_type = 0;
	पूर्णांक fixed_drv_type = card->host->fixed_drv_type;

	card_drv_type = card->ext_csd.raw_driver_strength |
			mmc_driver_type_mask(0);

	अगर (fixed_drv_type >= 0)
		drive_strength = card_drv_type & mmc_driver_type_mask(fixed_drv_type)
				 ? fixed_drv_type : 0;
	अन्यथा
		drive_strength = mmc_select_drive_strength(card,
							   card->ext_csd.hs200_max_dtr,
							   card_drv_type, &drv_type);

	card->drive_strength = drive_strength;

	अगर (drv_type)
		mmc_set_driver_type(card->host, drv_type);
पूर्ण

अटल पूर्णांक mmc_select_hs400es(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	पूर्णांक err = -EINVAL;
	u8 val;

	अगर (!(host->caps & MMC_CAP_8_BIT_DATA)) अणु
		err = -ENOTSUPP;
		जाओ out_err;
	पूर्ण

	अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS400_1_2V)
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_120);

	अगर (err && card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS400_1_8V)
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_180);

	/* If fails try again during next card घातer cycle */
	अगर (err)
		जाओ out_err;

	err = mmc_select_bus_width(card);
	अगर (err != MMC_BUS_WIDTH_8) अणु
		pr_err("%s: switch to 8bit bus width failed, err:%d\n",
			mmc_hostname(host), err);
		err = err < 0 ? err : -ENOTSUPP;
		जाओ out_err;
	पूर्ण

	/* Switch card to HS mode */
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_HS_TIMING, EXT_CSD_TIMING_HS,
			   card->ext_csd.generic_cmd6_समय, 0,
			   false, true, MMC_CMD_RETRIES);
	अगर (err) अणु
		pr_err("%s: switch to hs for hs400es failed, err:%d\n",
			mmc_hostname(host), err);
		जाओ out_err;
	पूर्ण

	mmc_set_timing(host, MMC_TIMING_MMC_HS);
	err = mmc_चयन_status(card, true);
	अगर (err)
		जाओ out_err;

	mmc_set_घड़ी(host, card->ext_csd.hs_max_dtr);

	/* Switch card to DDR with strobe bit */
	val = EXT_CSD_DDR_BUS_WIDTH_8 | EXT_CSD_BUS_WIDTH_STROBE;
	err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			 EXT_CSD_BUS_WIDTH,
			 val,
			 card->ext_csd.generic_cmd6_समय);
	अगर (err) अणु
		pr_err("%s: switch to bus width for hs400es failed, err:%d\n",
			mmc_hostname(host), err);
		जाओ out_err;
	पूर्ण

	mmc_select_driver_type(card);

	/* Switch card to HS400 */
	val = EXT_CSD_TIMING_HS400 |
	      card->drive_strength << EXT_CSD_DRV_STR_SHIFT;
	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			   EXT_CSD_HS_TIMING, val,
			   card->ext_csd.generic_cmd6_समय, 0,
			   false, true, MMC_CMD_RETRIES);
	अगर (err) अणु
		pr_err("%s: switch to hs400es failed, err:%d\n",
			mmc_hostname(host), err);
		जाओ out_err;
	पूर्ण

	/* Set host controller to HS400 timing and frequency */
	mmc_set_timing(host, MMC_TIMING_MMC_HS400);

	/* Controller enable enhanced strobe function */
	host->ios.enhanced_strobe = true;
	अगर (host->ops->hs400_enhanced_strobe)
		host->ops->hs400_enhanced_strobe(host, &host->ios);

	err = mmc_चयन_status(card, true);
	अगर (err)
		जाओ out_err;

	वापस 0;

out_err:
	pr_err("%s: %s failed, error %d\n", mmc_hostname(card->host),
	       __func__, err);
	वापस err;
पूर्ण

/*
 * For device supporting HS200 mode, the following sequence
 * should be करोne beक्रमe executing the tuning process.
 * 1. set the desired bus width(4-bit or 8-bit, 1-bit is not supported)
 * 2. चयन to HS200 mode
 * 3. set the घड़ी to > 52Mhz and <=200MHz
 */
अटल पूर्णांक mmc_select_hs200(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;
	अचिन्हित पूर्णांक old_timing, old_संकेत_voltage;
	पूर्णांक err = -EINVAL;
	u8 val;

	old_संकेत_voltage = host->ios.संकेत_voltage;
	अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS200_1_2V)
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_120);

	अगर (err && card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS200_1_8V)
		err = mmc_set_संकेत_voltage(host, MMC_SIGNAL_VOLTAGE_180);

	/* If fails try again during next card घातer cycle */
	अगर (err)
		वापस err;

	mmc_select_driver_type(card);

	/*
	 * Set the bus width(4 or 8) with host's support and
	 * चयन to HS200 mode अगर bus width is set successfully.
	 */
	err = mmc_select_bus_width(card);
	अगर (err > 0) अणु
		val = EXT_CSD_TIMING_HS200 |
		      card->drive_strength << EXT_CSD_DRV_STR_SHIFT;
		err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				   EXT_CSD_HS_TIMING, val,
				   card->ext_csd.generic_cmd6_समय, 0,
				   false, true, MMC_CMD_RETRIES);
		अगर (err)
			जाओ err;
		old_timing = host->ios.timing;
		mmc_set_timing(host, MMC_TIMING_MMC_HS200);

		/*
		 * For HS200, CRC errors are not a reliable way to know the
		 * चयन failed. If there really is a problem, we would expect
		 * tuning will fail and the result ends up the same.
		 */
		err = mmc_चयन_status(card, false);

		/*
		 * mmc_select_timing() assumes timing has not changed अगर
		 * it is a चयन error.
		 */
		अगर (err == -EBADMSG)
			mmc_set_timing(host, old_timing);
	पूर्ण
err:
	अगर (err) अणु
		/* fall back to the old संकेत voltage, अगर fails report error */
		अगर (mmc_set_संकेत_voltage(host, old_संकेत_voltage))
			err = -EIO;

		pr_err("%s: %s failed, error %d\n", mmc_hostname(card->host),
		       __func__, err);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Activate High Speed, HS200 or HS400ES mode अगर supported.
 */
अटल पूर्णांक mmc_select_timing(काष्ठा mmc_card *card)
अणु
	पूर्णांक err = 0;

	अगर (!mmc_can_ext_csd(card))
		जाओ bus_speed;

	अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS400ES)
		err = mmc_select_hs400es(card);
	अन्यथा अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS200)
		err = mmc_select_hs200(card);
	अन्यथा अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS)
		err = mmc_select_hs(card);

	अगर (err && err != -EBADMSG)
		वापस err;

bus_speed:
	/*
	 * Set the bus speed to the selected bus timing.
	 * If timing is not selected, backward compatible is the शेष.
	 */
	mmc_set_bus_speed(card);
	वापस 0;
पूर्ण

/*
 * Execute tuning sequence to seek the proper bus operating
 * conditions क्रम HS200 and HS400, which sends CMD21 to the device.
 */
अटल पूर्णांक mmc_hs200_tuning(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;

	/*
	 * Timing should be adjusted to the HS400 target
	 * operation frequency क्रम tuning process
	 */
	अगर (card->mmc_avail_type & EXT_CSD_CARD_TYPE_HS400 &&
	    host->ios.bus_width == MMC_BUS_WIDTH_8)
		अगर (host->ops->prepare_hs400_tuning)
			host->ops->prepare_hs400_tuning(host, &host->ios);

	वापस mmc_execute_tuning(card);
पूर्ण

/*
 * Handle the detection and initialisation of a card.
 *
 * In the हाल of a resume, "oldcard" will contain the card
 * we're trying to reinitialise.
 */
अटल पूर्णांक mmc_init_card(काष्ठा mmc_host *host, u32 ocr,
	काष्ठा mmc_card *oldcard)
अणु
	काष्ठा mmc_card *card;
	पूर्णांक err;
	u32 cid[4];
	u32 rocr;

	WARN_ON(!host->claimed);

	/* Set correct bus mode क्रम MMC beक्रमe attempting init */
	अगर (!mmc_host_is_spi(host))
		mmc_set_bus_mode(host, MMC_BUSMODE_OPENDRAIN);

	/*
	 * Since we're changing the OCR value, we seem to
	 * need to tell some cards to go back to the idle
	 * state.  We रुको 1ms to give cards समय to
	 * respond.
	 * mmc_go_idle is needed क्रम eMMC that are asleep
	 */
	mmc_go_idle(host);

	/* The extra bit indicates that we support high capacity */
	err = mmc_send_op_cond(host, ocr | (1 << 30), &rocr);
	अगर (err)
		जाओ err;

	/*
	 * For SPI, enable CRC as appropriate.
	 */
	अगर (mmc_host_is_spi(host)) अणु
		err = mmc_spi_set_crc(host, use_spi_crc);
		अगर (err)
			जाओ err;
	पूर्ण

	/*
	 * Fetch CID from card.
	 */
	err = mmc_send_cid(host, cid);
	अगर (err)
		जाओ err;

	अगर (oldcard) अणु
		अगर (स_भेद(cid, oldcard->raw_cid, माप(cid)) != 0) अणु
			pr_debug("%s: Perhaps the card was replaced\n",
				mmc_hostname(host));
			err = -ENOENT;
			जाओ err;
		पूर्ण

		card = oldcard;
	पूर्ण अन्यथा अणु
		/*
		 * Allocate card काष्ठाure.
		 */
		card = mmc_alloc_card(host, &mmc_type);
		अगर (IS_ERR(card)) अणु
			err = PTR_ERR(card);
			जाओ err;
		पूर्ण

		card->ocr = ocr;
		card->type = MMC_TYPE_MMC;
		card->rca = 1;
		स_नकल(card->raw_cid, cid, माप(card->raw_cid));
	पूर्ण

	/*
	 * Call the optional HC's init_card function to handle quirks.
	 */
	अगर (host->ops->init_card)
		host->ops->init_card(host, card);

	/*
	 * For native busses:  set card RCA and quit खोलो drain mode.
	 */
	अगर (!mmc_host_is_spi(host)) अणु
		err = mmc_set_relative_addr(card);
		अगर (err)
			जाओ मुक्त_card;

		mmc_set_bus_mode(host, MMC_BUSMODE_PUSHPULL);
	पूर्ण

	अगर (!oldcard) अणु
		/*
		 * Fetch CSD from card.
		 */
		err = mmc_send_csd(card, card->raw_csd);
		अगर (err)
			जाओ मुक्त_card;

		err = mmc_decode_csd(card);
		अगर (err)
			जाओ मुक्त_card;
		err = mmc_decode_cid(card);
		अगर (err)
			जाओ मुक्त_card;
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

	अगर (!oldcard) अणु
		/* Read extended CSD. */
		err = mmc_पढ़ो_ext_csd(card);
		अगर (err)
			जाओ मुक्त_card;

		/*
		 * If करोing byte addressing, check अगर required to करो sector
		 * addressing.  Handle the हाल of <2GB cards needing sector
		 * addressing.  See section 8.1 JEDEC Standard JED84-A441;
		 * ocr रेजिस्टर has bit 30 set क्रम sector addressing.
		 */
		अगर (rocr & BIT(30))
			mmc_card_set_blockaddr(card);

		/* Erase size depends on CSD and Extended CSD */
		mmc_set_erase_size(card);
	पूर्ण

	/* Enable ERASE_GRP_DEF. This bit is lost after a reset or घातer off. */
	अगर (card->ext_csd.rev >= 3) अणु
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_ERASE_GROUP_DEF, 1,
				 card->ext_csd.generic_cmd6_समय);

		अगर (err && err != -EBADMSG)
			जाओ मुक्त_card;

		अगर (err) अणु
			/*
			 * Just disable enhanced area off & sz
			 * will try to enable ERASE_GROUP_DEF
			 * during next समय reinit
			 */
			card->ext_csd.enhanced_area_offset = -EINVAL;
			card->ext_csd.enhanced_area_size = -EINVAL;
		पूर्ण अन्यथा अणु
			card->ext_csd.erase_group_def = 1;
			/*
			 * enable ERASE_GRP_DEF successfully.
			 * This will affect the erase size, so
			 * here need to reset erase size
			 */
			mmc_set_erase_size(card);
		पूर्ण
	पूर्ण

	/*
	 * Ensure eMMC user शेष partition is enabled
	 */
	अगर (card->ext_csd.part_config & EXT_CSD_PART_CONFIG_ACC_MASK) अणु
		card->ext_csd.part_config &= ~EXT_CSD_PART_CONFIG_ACC_MASK;
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL, EXT_CSD_PART_CONFIG,
				 card->ext_csd.part_config,
				 card->ext_csd.part_समय);
		अगर (err && err != -EBADMSG)
			जाओ मुक्त_card;
	पूर्ण

	/*
	 * Enable घातer_off_notअगरication byte in the ext_csd रेजिस्टर
	 */
	अगर (card->ext_csd.rev >= 6) अणु
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				 EXT_CSD_POWER_OFF_NOTIFICATION,
				 EXT_CSD_POWER_ON,
				 card->ext_csd.generic_cmd6_समय);
		अगर (err && err != -EBADMSG)
			जाओ मुक्त_card;

		/*
		 * The err can be -EBADMSG or 0,
		 * so check क्रम success and update the flag
		 */
		अगर (!err)
			card->ext_csd.घातer_off_notअगरication = EXT_CSD_POWER_ON;
	पूर्ण

	/* set erase_arg */
	अगर (mmc_can_discard(card))
		card->erase_arg = MMC_DISCARD_ARG;
	अन्यथा अगर (mmc_can_trim(card))
		card->erase_arg = MMC_TRIM_ARG;
	अन्यथा
		card->erase_arg = MMC_ERASE_ARG;

	/*
	 * Select timing पूर्णांकerface
	 */
	err = mmc_select_timing(card);
	अगर (err)
		जाओ मुक्त_card;

	अगर (mmc_card_hs200(card)) अणु
		host->करोing_init_tune = 1;

		err = mmc_hs200_tuning(card);
		अगर (!err)
			err = mmc_select_hs400(card);

		host->करोing_init_tune = 0;

		अगर (err)
			जाओ मुक्त_card;

	पूर्ण अन्यथा अगर (!mmc_card_hs400es(card)) अणु
		/* Select the desired bus width optionally */
		err = mmc_select_bus_width(card);
		अगर (err > 0 && mmc_card_hs(card)) अणु
			err = mmc_select_hs_ddr(card);
			अगर (err)
				जाओ मुक्त_card;
		पूर्ण
	पूर्ण

	/*
	 * Choose the घातer class with selected bus पूर्णांकerface
	 */
	mmc_select_घातerclass(card);

	/*
	 * Enable HPI feature (अगर supported)
	 */
	अगर (card->ext_csd.hpi) अणु
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				EXT_CSD_HPI_MGMT, 1,
				card->ext_csd.generic_cmd6_समय);
		अगर (err && err != -EBADMSG)
			जाओ मुक्त_card;
		अगर (err) अणु
			pr_warn("%s: Enabling HPI failed\n",
				mmc_hostname(card->host));
			card->ext_csd.hpi_en = 0;
		पूर्ण अन्यथा अणु
			card->ext_csd.hpi_en = 1;
		पूर्ण
	पूर्ण

	/*
	 * If cache size is higher than 0, this indicates the existence of cache
	 * and it can be turned on. Note that some eMMCs from Micron has been
	 * reported to need ~800 ms समयout, जबतक enabling the cache after
	 * sudden घातer failure tests. Let's extend the समयout to a minimum of
	 * DEFAULT_CACHE_EN_TIMEOUT_MS and करो it क्रम all cards.
	 */
	अगर (card->ext_csd.cache_size > 0) अणु
		अचिन्हित पूर्णांक समयout_ms = MIN_CACHE_EN_TIMEOUT_MS;

		समयout_ms = max(card->ext_csd.generic_cmd6_समय, समयout_ms);
		err = mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
				EXT_CSD_CACHE_CTRL, 1, समयout_ms);
		अगर (err && err != -EBADMSG)
			जाओ मुक्त_card;

		/*
		 * Only अगर no error, cache is turned on successfully.
		 */
		अगर (err) अणु
			pr_warn("%s: Cache is supported, but failed to turn on (%d)\n",
				mmc_hostname(card->host), err);
			card->ext_csd.cache_ctrl = 0;
		पूर्ण अन्यथा अणु
			card->ext_csd.cache_ctrl = 1;
		पूर्ण
	पूर्ण

	/*
	 * Enable Command Queue अगर supported. Note that Packed Commands cannot
	 * be used with Command Queue.
	 */
	card->ext_csd.cmdq_en = false;
	अगर (card->ext_csd.cmdq_support && host->caps2 & MMC_CAP2_CQE) अणु
		err = mmc_cmdq_enable(card);
		अगर (err && err != -EBADMSG)
			जाओ मुक्त_card;
		अगर (err) अणु
			pr_warn("%s: Enabling CMDQ failed\n",
				mmc_hostname(card->host));
			card->ext_csd.cmdq_support = false;
			card->ext_csd.cmdq_depth = 0;
		पूर्ण
	पूर्ण
	/*
	 * In some हालs (e.g. RPMB or mmc_test), the Command Queue must be
	 * disabled क्रम a समय, so a flag is needed to indicate to re-enable the
	 * Command Queue.
	 */
	card->reenable_cmdq = card->ext_csd.cmdq_en;

	अगर (host->cqe_ops && !host->cqe_enabled) अणु
		err = host->cqe_ops->cqe_enable(host, card);
		अगर (!err) अणु
			host->cqe_enabled = true;

			अगर (card->ext_csd.cmdq_en) अणु
				pr_info("%s: Command Queue Engine enabled\n",
					mmc_hostname(host));
			पूर्ण अन्यथा अणु
				host->hsq_enabled = true;
				pr_info("%s: Host Software Queue enabled\n",
					mmc_hostname(host));
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (host->caps2 & MMC_CAP2_AVOID_3_3V &&
	    host->ios.संकेत_voltage == MMC_SIGNAL_VOLTAGE_330) अणु
		pr_err("%s: Host failed to negotiate down from 3.3V\n",
			mmc_hostname(host));
		err = -EINVAL;
		जाओ मुक्त_card;
	पूर्ण

	अगर (!oldcard)
		host->card = card;

	वापस 0;

मुक्त_card:
	अगर (!oldcard)
		mmc_हटाओ_card(card);
err:
	वापस err;
पूर्ण

अटल पूर्णांक mmc_can_sleep(काष्ठा mmc_card *card)
अणु
	वापस card->ext_csd.rev >= 3;
पूर्ण

अटल पूर्णांक mmc_sleep(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_command cmd = अणुपूर्ण;
	काष्ठा mmc_card *card = host->card;
	अचिन्हित पूर्णांक समयout_ms = DIV_ROUND_UP(card->ext_csd.sa_समयout, 10000);
	पूर्णांक err;

	/* Re-tuning can't be करोne once the card is deselected */
	mmc_retune_hold(host);

	err = mmc_deselect_cards(host);
	अगर (err)
		जाओ out_release;

	cmd.opcode = MMC_SLEEP_AWAKE;
	cmd.arg = card->rca << 16;
	cmd.arg |= 1 << 15;

	/*
	 * If the max_busy_समयout of the host is specअगरied, validate it against
	 * the sleep cmd समयout. A failure means we need to prevent the host
	 * from करोing hw busy detection, which is करोne by converting to a R1
	 * response instead of a R1B. Note, some hosts requires R1B, which also
	 * means they are on their own when it comes to deal with the busy
	 * समयout.
	 */
	अगर (!(host->caps & MMC_CAP_NEED_RSP_BUSY) && host->max_busy_समयout &&
	    (समयout_ms > host->max_busy_समयout)) अणु
		cmd.flags = MMC_RSP_R1 | MMC_CMD_AC;
	पूर्ण अन्यथा अणु
		cmd.flags = MMC_RSP_R1B | MMC_CMD_AC;
		cmd.busy_समयout = समयout_ms;
	पूर्ण

	err = mmc_रुको_क्रम_cmd(host, &cmd, 0);
	अगर (err)
		जाओ out_release;

	/*
	 * If the host करोes not रुको जबतक the card संकेतs busy, then we will
	 * will have to रुको the sleep/awake समयout.  Note, we cannot use the
	 * SEND_STATUS command to poll the status because that command (and most
	 * others) is invalid जबतक the card sleeps.
	 */
	अगर (!cmd.busy_समयout || !(host->caps & MMC_CAP_WAIT_WHILE_BUSY))
		mmc_delay(समयout_ms);

out_release:
	mmc_retune_release(host);
	वापस err;
पूर्ण

अटल पूर्णांक mmc_can_घातeroff_notअगरy(स्थिर काष्ठा mmc_card *card)
अणु
	वापस card &&
		mmc_card_mmc(card) &&
		(card->ext_csd.घातer_off_notअगरication == EXT_CSD_POWER_ON);
पूर्ण

अटल पूर्णांक mmc_घातeroff_notअगरy(काष्ठा mmc_card *card, अचिन्हित पूर्णांक notअगरy_type)
अणु
	अचिन्हित पूर्णांक समयout = card->ext_csd.generic_cmd6_समय;
	पूर्णांक err;

	/* Use EXT_CSD_POWER_OFF_SHORT as शेष notअगरication type. */
	अगर (notअगरy_type == EXT_CSD_POWER_OFF_LONG)
		समयout = card->ext_csd.घातer_off_दीर्घसमय;

	err = __mmc_चयन(card, EXT_CSD_CMD_SET_NORMAL,
			EXT_CSD_POWER_OFF_NOTIFICATION,
			notअगरy_type, समयout, 0, false, false, MMC_CMD_RETRIES);
	अगर (err)
		pr_err("%s: Power Off Notification timed out, %u\n",
		       mmc_hostname(card->host), समयout);

	/* Disable the घातer off notअगरication after the चयन operation. */
	card->ext_csd.घातer_off_notअगरication = EXT_CSD_NO_POWER_NOTIFICATION;

	वापस err;
पूर्ण

/*
 * Host is being हटाओd. Free up the current card.
 */
अटल व्योम mmc_हटाओ(काष्ठा mmc_host *host)
अणु
	mmc_हटाओ_card(host->card);
	host->card = शून्य;
पूर्ण

/*
 * Card detection - card is alive.
 */
अटल पूर्णांक mmc_alive(काष्ठा mmc_host *host)
अणु
	वापस mmc_send_status(host->card, शून्य);
पूर्ण

/*
 * Card detection callback from host.
 */
अटल व्योम mmc_detect(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	mmc_get_card(host->card, शून्य);

	/*
	 * Just check अगर our card has been हटाओd.
	 */
	err = _mmc_detect_card_हटाओd(host);

	mmc_put_card(host->card, शून्य);

	अगर (err) अणु
		mmc_हटाओ(host);

		mmc_claim_host(host);
		mmc_detach_bus(host);
		mmc_घातer_off(host);
		mmc_release_host(host);
	पूर्ण
पूर्ण

अटल bool _mmc_cache_enabled(काष्ठा mmc_host *host)
अणु
	वापस host->card->ext_csd.cache_size > 0 &&
	       host->card->ext_csd.cache_ctrl & 1;
पूर्ण

अटल पूर्णांक _mmc_suspend(काष्ठा mmc_host *host, bool is_suspend)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक notअगरy_type = is_suspend ? EXT_CSD_POWER_OFF_SHORT :
					EXT_CSD_POWER_OFF_LONG;

	mmc_claim_host(host);

	अगर (mmc_card_suspended(host->card))
		जाओ out;

	err = mmc_flush_cache(host->card);
	अगर (err)
		जाओ out;

	अगर (mmc_can_घातeroff_notअगरy(host->card) &&
	    ((host->caps2 & MMC_CAP2_FULL_PWR_CYCLE) || !is_suspend ||
	     (host->caps2 & MMC_CAP2_FULL_PWR_CYCLE_IN_SUSPEND)))
		err = mmc_घातeroff_notअगरy(host->card, notअगरy_type);
	अन्यथा अगर (mmc_can_sleep(host->card))
		err = mmc_sleep(host);
	अन्यथा अगर (!mmc_host_is_spi(host))
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
 * Suspend callback
 */
अटल पूर्णांक mmc_suspend(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	err = _mmc_suspend(host, true);
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
अटल पूर्णांक _mmc_resume(काष्ठा mmc_host *host)
अणु
	पूर्णांक err = 0;

	mmc_claim_host(host);

	अगर (!mmc_card_suspended(host->card))
		जाओ out;

	mmc_घातer_up(host, host->card->ocr);
	err = mmc_init_card(host, host->card->ocr, host->card);
	mmc_card_clr_suspended(host->card);

out:
	mmc_release_host(host);
	वापस err;
पूर्ण

/*
 * Shutकरोwn callback
 */
अटल पूर्णांक mmc_shutकरोwn(काष्ठा mmc_host *host)
अणु
	पूर्णांक err = 0;

	/*
	 * In a specअगरic हाल क्रम घातeroff notअगरy, we need to resume the card
	 * beक्रमe we can shutकरोwn it properly.
	 */
	अगर (mmc_can_घातeroff_notअगरy(host->card) &&
		!(host->caps2 & MMC_CAP2_FULL_PWR_CYCLE))
		err = _mmc_resume(host);

	अगर (!err)
		err = _mmc_suspend(host, false);

	वापस err;
पूर्ण

/*
 * Callback क्रम resume.
 */
अटल पूर्णांक mmc_resume(काष्ठा mmc_host *host)
अणु
	pm_runसमय_enable(&host->card->dev);
	वापस 0;
पूर्ण

/*
 * Callback क्रम runसमय_suspend.
 */
अटल पूर्णांक mmc_runसमय_suspend(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	अगर (!(host->caps & MMC_CAP_AGGRESSIVE_PM))
		वापस 0;

	err = _mmc_suspend(host, true);
	अगर (err)
		pr_err("%s: error %d doing aggressive suspend\n",
			mmc_hostname(host), err);

	वापस err;
पूर्ण

/*
 * Callback क्रम runसमय_resume.
 */
अटल पूर्णांक mmc_runसमय_resume(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;

	err = _mmc_resume(host);
	अगर (err && err != -ENOMEDIUM)
		pr_err("%s: error %d doing runtime resume\n",
			mmc_hostname(host), err);

	वापस 0;
पूर्ण

अटल पूर्णांक mmc_can_reset(काष्ठा mmc_card *card)
अणु
	u8 rst_n_function;

	rst_n_function = card->ext_csd.rst_n_function;
	अगर ((rst_n_function & EXT_CSD_RST_N_EN_MASK) != EXT_CSD_RST_N_ENABLED)
		वापस 0;
	वापस 1;
पूर्ण

अटल पूर्णांक _mmc_hw_reset(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_card *card = host->card;

	/*
	 * In the हाल of recovery, we can't expect flushing the cache to work
	 * always, but we have a go and ignore errors.
	 */
	mmc_flush_cache(host->card);

	अगर ((host->caps & MMC_CAP_HW_RESET) && host->ops->hw_reset &&
	     mmc_can_reset(card)) अणु
		/* If the card accept RST_n संकेत, send it. */
		mmc_set_घड़ी(host, host->f_init);
		host->ops->hw_reset(host);
		/* Set initial state and call mmc_set_ios */
		mmc_set_initial_state(host);
	पूर्ण अन्यथा अणु
		/* Do a brute क्रमce घातer cycle */
		mmc_घातer_cycle(host, card->ocr);
		mmc_pwrseq_reset(host);
	पूर्ण
	वापस mmc_init_card(host, card->ocr, card);
पूर्ण

अटल स्थिर काष्ठा mmc_bus_ops mmc_ops = अणु
	.हटाओ = mmc_हटाओ,
	.detect = mmc_detect,
	.suspend = mmc_suspend,
	.resume = mmc_resume,
	.runसमय_suspend = mmc_runसमय_suspend,
	.runसमय_resume = mmc_runसमय_resume,
	.alive = mmc_alive,
	.shutकरोwn = mmc_shutकरोwn,
	.hw_reset = _mmc_hw_reset,
	.cache_enabled = _mmc_cache_enabled,
पूर्ण;

/*
 * Starting poपूर्णांक क्रम MMC card init.
 */
पूर्णांक mmc_attach_mmc(काष्ठा mmc_host *host)
अणु
	पूर्णांक err;
	u32 ocr, rocr;

	WARN_ON(!host->claimed);

	/* Set correct bus mode क्रम MMC beक्रमe attempting attach */
	अगर (!mmc_host_is_spi(host))
		mmc_set_bus_mode(host, MMC_BUSMODE_OPENDRAIN);

	err = mmc_send_op_cond(host, 0, &ocr);
	अगर (err)
		वापस err;

	mmc_attach_bus(host, &mmc_ops);
	अगर (host->ocr_avail_mmc)
		host->ocr_avail = host->ocr_avail_mmc;

	/*
	 * We need to get OCR a dअगरferent way क्रम SPI.
	 */
	अगर (mmc_host_is_spi(host)) अणु
		err = mmc_spi_पढ़ो_ocr(host, 1, &ocr);
		अगर (err)
			जाओ err;
	पूर्ण

	rocr = mmc_select_voltage(host, ocr);

	/*
	 * Can we support the voltage of the card?
	 */
	अगर (!rocr) अणु
		err = -EINVAL;
		जाओ err;
	पूर्ण

	/*
	 * Detect and init the card.
	 */
	err = mmc_init_card(host, rocr, शून्य);
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
	mmc_claim_host(host);
	host->card = शून्य;
err:
	mmc_detach_bus(host);

	pr_err("%s: error %d whilst initialising MMC card\n",
		mmc_hostname(host), err);

	वापस err;
पूर्ण
