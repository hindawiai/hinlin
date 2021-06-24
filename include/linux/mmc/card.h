<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/include/linux/mmc/card.h
 *
 *  Card driver specअगरic definitions.
 */
#अगर_अघोषित LINUX_MMC_CARD_H
#घोषणा LINUX_MMC_CARD_H

#समावेश <linux/device.h>
#समावेश <linux/mod_devicetable.h>

काष्ठा mmc_cid अणु
	अचिन्हित पूर्णांक		manfid;
	अक्षर			prod_name[8];
	अचिन्हित अक्षर		prv;
	अचिन्हित पूर्णांक		serial;
	अचिन्हित लघु		oemid;
	अचिन्हित लघु		year;
	अचिन्हित अक्षर		hwrev;
	अचिन्हित अक्षर		fwrev;
	अचिन्हित अक्षर		month;
पूर्ण;

काष्ठा mmc_csd अणु
	अचिन्हित अक्षर		काष्ठाure;
	अचिन्हित अक्षर		mmca_vsn;
	अचिन्हित लघु		cmdclass;
	अचिन्हित लघु		taac_clks;
	अचिन्हित पूर्णांक		taac_ns;
	अचिन्हित पूर्णांक		c_size;
	अचिन्हित पूर्णांक		r2w_factor;
	अचिन्हित पूर्णांक		max_dtr;
	अचिन्हित पूर्णांक		erase_size;		/* In sectors */
	अचिन्हित पूर्णांक		पढ़ो_blkbits;
	अचिन्हित पूर्णांक		ग_लिखो_blkbits;
	अचिन्हित पूर्णांक		capacity;
	अचिन्हित पूर्णांक		पढ़ो_partial:1,
				पढ़ो_misalign:1,
				ग_लिखो_partial:1,
				ग_लिखो_misalign:1,
				dsr_imp:1;
पूर्ण;

काष्ठा mmc_ext_csd अणु
	u8			rev;
	u8			erase_group_def;
	u8			sec_feature_support;
	u8			rel_sectors;
	u8			rel_param;
	bool			enhanced_rpmb_supported;
	u8			part_config;
	u8			cache_ctrl;
	u8			rst_n_function;
	u8			max_packed_ग_लिखोs;
	u8			max_packed_पढ़ोs;
	u8			packed_event_en;
	अचिन्हित पूर्णांक		part_समय;		/* Units: ms */
	अचिन्हित पूर्णांक		sa_समयout;		/* Units: 100ns */
	अचिन्हित पूर्णांक		generic_cmd6_समय;	/* Units: 10ms */
	अचिन्हित पूर्णांक            घातer_off_दीर्घसमय;     /* Units: ms */
	u8			घातer_off_notअगरication;	/* state */
	अचिन्हित पूर्णांक		hs_max_dtr;
	अचिन्हित पूर्णांक		hs200_max_dtr;
#घोषणा MMC_HIGH_26_MAX_DTR	26000000
#घोषणा MMC_HIGH_52_MAX_DTR	52000000
#घोषणा MMC_HIGH_DDR_MAX_DTR	52000000
#घोषणा MMC_HS200_MAX_DTR	200000000
	अचिन्हित पूर्णांक		sectors;
	अचिन्हित पूर्णांक		hc_erase_size;		/* In sectors */
	अचिन्हित पूर्णांक		hc_erase_समयout;	/* In milliseconds */
	अचिन्हित पूर्णांक		sec_trim_mult;	/* Secure trim multiplier  */
	अचिन्हित पूर्णांक		sec_erase_mult;	/* Secure erase multiplier */
	अचिन्हित पूर्णांक		trim_समयout;		/* In milliseconds */
	bool			partition_setting_completed;	/* enable bit */
	अचिन्हित दीर्घ दीर्घ	enhanced_area_offset;	/* Units: Byte */
	अचिन्हित पूर्णांक		enhanced_area_size;	/* Units: KB */
	अचिन्हित पूर्णांक		cache_size;		/* Units: KB */
	bool			hpi_en;			/* HPI enablebit */
	bool			hpi;			/* HPI support bit */
	अचिन्हित पूर्णांक		hpi_cmd;		/* cmd used as HPI */
	bool			bkops;		/* background support bit */
	bool			man_bkops_en;	/* manual bkops enable bit */
	bool			स्वतः_bkops_en;	/* स्वतः bkops enable bit */
	अचिन्हित पूर्णांक            data_sector_size;       /* 512 bytes or 4KB */
	अचिन्हित पूर्णांक            data_tag_unit_size;     /* DATA TAG UNIT size */
	अचिन्हित पूर्णांक		boot_ro_lock;		/* ro lock support */
	bool			boot_ro_lockable;
	bool			ffu_capable;	/* Firmware upgrade support */
	bool			cmdq_en;	/* Command Queue enabled */
	bool			cmdq_support;	/* Command Queue supported */
	अचिन्हित पूर्णांक		cmdq_depth;	/* Command Queue depth */
#घोषणा MMC_FIRMWARE_LEN 8
	u8			fwrev[MMC_FIRMWARE_LEN];  /* FW version */
	u8			raw_exception_status;	/* 54 */
	u8			raw_partition_support;	/* 160 */
	u8			raw_rpmb_size_mult;	/* 168 */
	u8			raw_erased_mem_count;	/* 181 */
	u8			strobe_support;		/* 184 */
	u8			raw_ext_csd_काष्ठाure;	/* 194 */
	u8			raw_card_type;		/* 196 */
	u8			raw_driver_strength;	/* 197 */
	u8			out_of_पूर्णांक_समय;	/* 198 */
	u8			raw_pwr_cl_52_195;	/* 200 */
	u8			raw_pwr_cl_26_195;	/* 201 */
	u8			raw_pwr_cl_52_360;	/* 202 */
	u8			raw_pwr_cl_26_360;	/* 203 */
	u8			raw_s_a_समयout;	/* 217 */
	u8			raw_hc_erase_gap_size;	/* 221 */
	u8			raw_erase_समयout_mult;	/* 223 */
	u8			raw_hc_erase_grp_size;	/* 224 */
	u8			raw_sec_trim_mult;	/* 229 */
	u8			raw_sec_erase_mult;	/* 230 */
	u8			raw_sec_feature_support;/* 231 */
	u8			raw_trim_mult;		/* 232 */
	u8			raw_pwr_cl_200_195;	/* 236 */
	u8			raw_pwr_cl_200_360;	/* 237 */
	u8			raw_pwr_cl_ddr_52_195;	/* 238 */
	u8			raw_pwr_cl_ddr_52_360;	/* 239 */
	u8			raw_pwr_cl_ddr_200_360;	/* 253 */
	u8			raw_bkops_status;	/* 246 */
	u8			raw_sectors[4];		/* 212 - 4 bytes */
	u8			pre_eol_info;		/* 267 */
	u8			device_lअगरe_समय_est_typ_a;	/* 268 */
	u8			device_lअगरe_समय_est_typ_b;	/* 269 */

	अचिन्हित पूर्णांक            feature_support;
#घोषणा MMC_DISCARD_FEATURE	BIT(0)                  /* CMD38 feature */
पूर्ण;

काष्ठा sd_scr अणु
	अचिन्हित अक्षर		sda_vsn;
	अचिन्हित अक्षर		sda_spec3;
	अचिन्हित अक्षर		sda_spec4;
	अचिन्हित अक्षर		sda_specx;
	अचिन्हित अक्षर		bus_widths;
#घोषणा SD_SCR_BUS_WIDTH_1	(1<<0)
#घोषणा SD_SCR_BUS_WIDTH_4	(1<<2)
	अचिन्हित अक्षर		cmds;
#घोषणा SD_SCR_CMD20_SUPPORT   (1<<0)
#घोषणा SD_SCR_CMD23_SUPPORT   (1<<1)
पूर्ण;

काष्ठा sd_ssr अणु
	अचिन्हित पूर्णांक		au;			/* In sectors */
	अचिन्हित पूर्णांक		erase_समयout;		/* In milliseconds */
	अचिन्हित पूर्णांक		erase_offset;		/* In milliseconds */
पूर्ण;

काष्ठा sd_चयन_caps अणु
	अचिन्हित पूर्णांक		hs_max_dtr;
	अचिन्हित पूर्णांक		uhs_max_dtr;
#घोषणा HIGH_SPEED_MAX_DTR	50000000
#घोषणा UHS_SDR104_MAX_DTR	208000000
#घोषणा UHS_SDR50_MAX_DTR	100000000
#घोषणा UHS_DDR50_MAX_DTR	50000000
#घोषणा UHS_SDR25_MAX_DTR	UHS_DDR50_MAX_DTR
#घोषणा UHS_SDR12_MAX_DTR	25000000
#घोषणा DEFAULT_SPEED_MAX_DTR	UHS_SDR12_MAX_DTR
	अचिन्हित पूर्णांक		sd3_bus_mode;
#घोषणा UHS_SDR12_BUS_SPEED	0
#घोषणा HIGH_SPEED_BUS_SPEED	1
#घोषणा UHS_SDR25_BUS_SPEED	1
#घोषणा UHS_SDR50_BUS_SPEED	2
#घोषणा UHS_SDR104_BUS_SPEED	3
#घोषणा UHS_DDR50_BUS_SPEED	4

#घोषणा SD_MODE_HIGH_SPEED	(1 << HIGH_SPEED_BUS_SPEED)
#घोषणा SD_MODE_UHS_SDR12	(1 << UHS_SDR12_BUS_SPEED)
#घोषणा SD_MODE_UHS_SDR25	(1 << UHS_SDR25_BUS_SPEED)
#घोषणा SD_MODE_UHS_SDR50	(1 << UHS_SDR50_BUS_SPEED)
#घोषणा SD_MODE_UHS_SDR104	(1 << UHS_SDR104_BUS_SPEED)
#घोषणा SD_MODE_UHS_DDR50	(1 << UHS_DDR50_BUS_SPEED)
	अचिन्हित पूर्णांक		sd3_drv_type;
#घोषणा SD_DRIVER_TYPE_B	0x01
#घोषणा SD_DRIVER_TYPE_A	0x02
#घोषणा SD_DRIVER_TYPE_C	0x04
#घोषणा SD_DRIVER_TYPE_D	0x08
	अचिन्हित पूर्णांक		sd3_curr_limit;
#घोषणा SD_SET_CURRENT_LIMIT_200	0
#घोषणा SD_SET_CURRENT_LIMIT_400	1
#घोषणा SD_SET_CURRENT_LIMIT_600	2
#घोषणा SD_SET_CURRENT_LIMIT_800	3
#घोषणा SD_SET_CURRENT_NO_CHANGE	(-1)

#घोषणा SD_MAX_CURRENT_200	(1 << SD_SET_CURRENT_LIMIT_200)
#घोषणा SD_MAX_CURRENT_400	(1 << SD_SET_CURRENT_LIMIT_400)
#घोषणा SD_MAX_CURRENT_600	(1 << SD_SET_CURRENT_LIMIT_600)
#घोषणा SD_MAX_CURRENT_800	(1 << SD_SET_CURRENT_LIMIT_800)
पूर्ण;

काष्ठा sdio_cccr अणु
	अचिन्हित पूर्णांक		sdio_vsn;
	अचिन्हित पूर्णांक		sd_vsn;
	अचिन्हित पूर्णांक		multi_block:1,
				low_speed:1,
				wide_bus:1,
				high_घातer:1,
				high_speed:1,
				disable_cd:1;
पूर्ण;

काष्ठा sdio_cis अणु
	अचिन्हित लघु		venकरोr;
	अचिन्हित लघु		device;
	अचिन्हित लघु		blksize;
	अचिन्हित पूर्णांक		max_dtr;
पूर्ण;

काष्ठा mmc_host;
काष्ठा sdio_func;
काष्ठा sdio_func_tuple;
काष्ठा mmc_queue_req;

#घोषणा SDIO_MAX_FUNCS		7

/* The number of MMC physical partitions.  These consist of:
 * boot partitions (2), general purpose partitions (4) and
 * RPMB partition (1) in MMC v4.4.
 */
#घोषणा MMC_NUM_BOOT_PARTITION	2
#घोषणा MMC_NUM_GP_PARTITION	4
#घोषणा MMC_NUM_PHY_PARTITION	7
#घोषणा MAX_MMC_PART_NAME_LEN	20

/*
 * MMC Physical partitions
 */
काष्ठा mmc_part अणु
	u64		size;	/* partition size (in bytes) */
	अचिन्हित पूर्णांक	part_cfg;	/* partition type */
	अक्षर	name[MAX_MMC_PART_NAME_LEN];
	bool	क्रमce_ro;	/* to make boot parts RO by शेष */
	अचिन्हित पूर्णांक	area_type;
#घोषणा MMC_BLK_DATA_AREA_MAIN	(1<<0)
#घोषणा MMC_BLK_DATA_AREA_BOOT	(1<<1)
#घोषणा MMC_BLK_DATA_AREA_GP	(1<<2)
#घोषणा MMC_BLK_DATA_AREA_RPMB	(1<<3)
पूर्ण;

/*
 * MMC device
 */
काष्ठा mmc_card अणु
	काष्ठा mmc_host		*host;		/* the host this device beदीर्घs to */
	काष्ठा device		dev;		/* the device */
	u32			ocr;		/* the current OCR setting */
	अचिन्हित पूर्णांक		rca;		/* relative card address of device */
	अचिन्हित पूर्णांक		type;		/* card type */
#घोषणा MMC_TYPE_MMC		0		/* MMC card */
#घोषणा MMC_TYPE_SD		1		/* SD card */
#घोषणा MMC_TYPE_SDIO		2		/* SDIO card */
#घोषणा MMC_TYPE_SD_COMBO	3		/* SD combo (IO+mem) card */
	अचिन्हित पूर्णांक		state;		/* (our) card state */
	अचिन्हित पूर्णांक		quirks; 	/* card quirks */
	अचिन्हित पूर्णांक		quirk_max_rate;	/* max rate set by quirks */
#घोषणा MMC_QUIRK_LENIENT_FN0	(1<<0)		/* allow SDIO FN0 ग_लिखोs outside of the VS CCCR range */
#घोषणा MMC_QUIRK_BLKSZ_FOR_BYTE_MODE (1<<1)	/* use func->cur_blksize */
						/* क्रम byte mode */
#घोषणा MMC_QUIRK_NONSTD_SDIO	(1<<2)		/* non-standard SDIO card attached */
						/* (missing CIA रेजिस्टरs) */
#घोषणा MMC_QUIRK_NONSTD_FUNC_IF (1<<4)		/* SDIO card has nonstd function पूर्णांकerfaces */
#घोषणा MMC_QUIRK_DISABLE_CD	(1<<5)		/* disconnect CD/DAT[3] resistor */
#घोषणा MMC_QUIRK_Iन_अंकD_CMD38	(1<<6)		/* iन_अंकD devices have broken CMD38 */
#घोषणा MMC_QUIRK_BLK_NO_CMD23	(1<<7)		/* Aव्योम CMD23 क्रम regular multiblock */
#घोषणा MMC_QUIRK_BROKEN_BYTE_MODE_512 (1<<8)	/* Aव्योम sending 512 bytes in */
						/* byte mode */
#घोषणा MMC_QUIRK_LONG_READ_TIME (1<<9)		/* Data पढ़ो समय > CSD says */
#घोषणा MMC_QUIRK_SEC_ERASE_TRIM_BROKEN (1<<10)	/* Skip secure क्रम erase/trim */
#घोषणा MMC_QUIRK_BROKEN_IRQ_POLLING	(1<<11)	/* Polling SDIO_CCCR_INTx could create a fake पूर्णांकerrupt */
#घोषणा MMC_QUIRK_TRIM_BROKEN	(1<<12)		/* Skip trim */
#घोषणा MMC_QUIRK_BROKEN_HPI	(1<<13)		/* Disable broken HPI support */

	bool			reenable_cmdq;	/* Re-enable Command Queue */

	अचिन्हित पूर्णांक		erase_size;	/* erase size in sectors */
 	अचिन्हित पूर्णांक		erase_shअगरt;	/* अगर erase unit is घातer 2 */
 	अचिन्हित पूर्णांक		pref_erase;	/* in sectors */
	अचिन्हित पूर्णांक		eg_boundary;	/* करोn't cross erase-group boundaries */
	अचिन्हित पूर्णांक		erase_arg;	/* erase / trim / discard */
 	u8			erased_byte;	/* value of erased bytes */

	u32			raw_cid[4];	/* raw card CID */
	u32			raw_csd[4];	/* raw card CSD */
	u32			raw_scr[2];	/* raw card SCR */
	u32			raw_ssr[16];	/* raw card SSR */
	काष्ठा mmc_cid		cid;		/* card identअगरication */
	काष्ठा mmc_csd		csd;		/* card specअगरic */
	काष्ठा mmc_ext_csd	ext_csd;	/* mmc v4 extended card specअगरic */
	काष्ठा sd_scr		scr;		/* extra SD inक्रमmation */
	काष्ठा sd_ssr		ssr;		/* yet more SD inक्रमmation */
	काष्ठा sd_चयन_caps	sw_caps;	/* चयन (CMD6) caps */

	अचिन्हित पूर्णांक		sdio_funcs;	/* number of SDIO functions */
	atomic_t		sdio_funcs_probed; /* number of probed SDIO funcs */
	काष्ठा sdio_cccr	cccr;		/* common card info */
	काष्ठा sdio_cis		cis;		/* common tuple info */
	काष्ठा sdio_func	*sdio_func[SDIO_MAX_FUNCS]; /* SDIO functions (devices) */
	काष्ठा sdio_func	*sdio_single_irq; /* SDIO function when only one IRQ active */
	u8			major_rev;	/* major revision number */
	u8			minor_rev;	/* minor revision number */
	अचिन्हित		num_info;	/* number of info strings */
	स्थिर अक्षर		**info;		/* info strings */
	काष्ठा sdio_func_tuple	*tuples;	/* unknown common tuples */

	अचिन्हित पूर्णांक		sd_bus_speed;	/* Bus Speed Mode set क्रम the card */
	अचिन्हित पूर्णांक		mmc_avail_type;	/* supported device type by both host and card */
	अचिन्हित पूर्णांक		drive_strength;	/* क्रम UHS-I, HS200 or HS400 */

	काष्ठा dentry		*debugfs_root;
	काष्ठा mmc_part	part[MMC_NUM_PHY_PARTITION]; /* physical partitions */
	अचिन्हित पूर्णांक    nr_parts;

	काष्ठा workqueue_काष्ठा *complete_wq;	/* Private workqueue */
पूर्ण;

अटल अंतरभूत bool mmc_large_sector(काष्ठा mmc_card *card)
अणु
	वापस card->ext_csd.data_sector_size == 4096;
पूर्ण

bool mmc_card_is_blockaddr(काष्ठा mmc_card *card);

#घोषणा mmc_card_mmc(c)		((c)->type == MMC_TYPE_MMC)
#घोषणा mmc_card_sd(c)		((c)->type == MMC_TYPE_SD)
#घोषणा mmc_card_sdio(c)	((c)->type == MMC_TYPE_SDIO)

#पूर्ण_अगर /* LINUX_MMC_CARD_H */
