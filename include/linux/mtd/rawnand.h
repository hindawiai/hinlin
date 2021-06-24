<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Copyright तऊ 2000-2010 David Woodhouse <dwmw2@infradead.org>
 *                        Steven J. Hill <sjhill@realitydiluted.com>
 *		          Thomas Gleixner <tglx@linutronix.de>
 *
 * Info:
 *	Contains standard defines and IDs क्रम न_अंकD flash devices
 *
 * Changelog:
 *	See git changelog.
 */
#अगर_अघोषित __LINUX_MTD_RAWन_अंकD_H
#घोषणा __LINUX_MTD_RAWन_अंकD_H

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nand.h>
#समावेश <linux/mtd/flashchip.h>
#समावेश <linux/mtd/bbm.h>
#समावेश <linux/mtd/jedec.h>
#समावेश <linux/mtd/onfi.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/types.h>

काष्ठा nand_chip;

/* The maximum number of न_अंकD chips in an array */
#घोषणा न_अंकD_MAX_CHIPS		8

/*
 * Constants क्रम hardware specअगरic CLE/ALE/NCE function
 *
 * These are bits which can be or'ed to set/clear multiple
 * bits in one go.
 */
/* Select the chip by setting nCE to low */
#घोषणा न_अंकD_NCE		0x01
/* Select the command latch by setting CLE to high */
#घोषणा न_अंकD_CLE		0x02
/* Select the address latch by setting ALE to high */
#घोषणा न_अंकD_ALE		0x04

#घोषणा न_अंकD_CTRL_CLE		(न_अंकD_NCE | न_अंकD_CLE)
#घोषणा न_अंकD_CTRL_ALE		(न_अंकD_NCE | न_अंकD_ALE)
#घोषणा न_अंकD_CTRL_CHANGE	0x80

/*
 * Standard न_अंकD flash commands
 */
#घोषणा न_अंकD_CMD_READ0		0
#घोषणा न_अंकD_CMD_READ1		1
#घोषणा न_अंकD_CMD_RNDOUT		5
#घोषणा न_अंकD_CMD_PAGEPROG	0x10
#घोषणा न_अंकD_CMD_READOOB	0x50
#घोषणा न_अंकD_CMD_ERASE1		0x60
#घोषणा न_अंकD_CMD_STATUS		0x70
#घोषणा न_अंकD_CMD_SEQIN		0x80
#घोषणा न_अंकD_CMD_RNDIN		0x85
#घोषणा न_अंकD_CMD_READID		0x90
#घोषणा न_अंकD_CMD_ERASE2		0xd0
#घोषणा न_अंकD_CMD_PARAM		0xec
#घोषणा न_अंकD_CMD_GET_FEATURES	0xee
#घोषणा न_अंकD_CMD_SET_FEATURES	0xef
#घोषणा न_अंकD_CMD_RESET		0xff

/* Extended commands क्रम large page devices */
#घोषणा न_अंकD_CMD_READSTART	0x30
#घोषणा न_अंकD_CMD_RNDOUTSTART	0xE0
#घोषणा न_अंकD_CMD_CACHEDPROG	0x15

#घोषणा न_अंकD_CMD_NONE		-1

/* Status bits */
#घोषणा न_अंकD_STATUS_FAIL	0x01
#घोषणा न_अंकD_STATUS_FAIL_N1	0x02
#घोषणा न_अंकD_STATUS_TRUE_READY	0x20
#घोषणा न_अंकD_STATUS_READY	0x40
#घोषणा न_अंकD_STATUS_WP		0x80

#घोषणा न_अंकD_DATA_IFACE_CHECK_ONLY	-1

/*
 * Constants क्रम Hardware ECC
 */
/* Reset Hardware ECC क्रम पढ़ो */
#घोषणा न_अंकD_ECC_READ		0
/* Reset Hardware ECC क्रम ग_लिखो */
#घोषणा न_अंकD_ECC_WRITE		1
/* Enable Hardware ECC beक्रमe syndrome is पढ़ो back from flash */
#घोषणा न_अंकD_ECC_READSYN	2

/*
 * Enable generic न_अंकD 'page erased' check. This check is only करोne when
 * ecc.correct() वापसs -EBADMSG.
 * Set this flag अगर your implementation करोes not fix bitflips in erased
 * pages and you want to rely on the शेष implementation.
 */
#घोषणा न_अंकD_ECC_GENERIC_ERASED_CHECK	BIT(0)

/*
 * Option स्थिरants क्रम bizarre disfunctionality and real
 * features.
 */

/* Buswidth is 16 bit */
#घोषणा न_अंकD_BUSWIDTH_16	BIT(1)

/*
 * When using software implementation of Hamming, we can specअगरy which byte
 * ordering should be used.
 */
#घोषणा न_अंकD_ECC_SOFT_HAMMING_SM_ORDER	BIT(2)

/* Chip has cache program function */
#घोषणा न_अंकD_CACHEPRG		BIT(3)
/* Options valid क्रम Samsung large page devices */
#घोषणा न_अंकD_SAMSUNG_LP_OPTIONS न_अंकD_CACHEPRG

/*
 * Chip requires पढ़ोy check on पढ़ो (क्रम स्वतः-incremented sequential पढ़ो).
 * True only क्रम small page devices; large page devices करो not support
 * स्वतःincrement.
 */
#घोषणा न_अंकD_NEED_READRDY	BIT(8)

/* Chip करोes not allow subpage ग_लिखोs */
#घोषणा न_अंकD_NO_SUBPAGE_WRITE	BIT(9)

/* Device is one of 'new' xD cards that expose fake nand command set */
#घोषणा न_अंकD_BROKEN_XD		BIT(10)

/* Device behaves just like nand, but is पढ़ोonly */
#घोषणा न_अंकD_ROM		BIT(11)

/* Device supports subpage पढ़ोs */
#घोषणा न_अंकD_SUBPAGE_READ	BIT(12)
/* Macros to identअगरy the above */
#घोषणा न_अंकD_HAS_SUBPAGE_READ(chip) ((chip->options & न_अंकD_SUBPAGE_READ))

/*
 * Some MLC न_अंकDs need data scrambling to limit bitflips caused by repeated
 * patterns.
 */
#घोषणा न_अंकD_NEED_SCRAMBLING	BIT(13)

/* Device needs 3rd row address cycle */
#घोषणा न_अंकD_ROW_ADDR_3		BIT(14)

/* Non chip related options */
/* This option skips the bbt scan during initialization. */
#घोषणा न_अंकD_SKIP_BBTSCAN	BIT(16)
/* Chip may not exist, so silence any errors in scan */
#घोषणा न_अंकD_SCAN_SILENT_NODEV	BIT(18)

/*
 * Autodetect nand buswidth with पढ़ोid/onfi.
 * This suppose the driver will configure the hardware in 8 bits mode
 * when calling nand_scan_ident, and update its configuration
 * beक्रमe calling nand_scan_tail.
 */
#घोषणा न_अंकD_BUSWIDTH_AUTO      BIT(19)

/*
 * This option could be defined by controller drivers to protect against
 * kmap'ed, vmalloc'ed highmem buffers being passed from upper layers
 */
#घोषणा न_अंकD_USES_DMA		BIT(20)

/*
 * In हाल your controller is implementing ->legacy.cmd_ctrl() and is relying
 * on the शेष ->cmdfunc() implementation, you may want to let the core
 * handle the tCCS delay which is required when a column change (RNDIN or
 * RNDOUT) is requested.
 * If your controller alपढ़ोy takes care of this delay, you करोn't need to set
 * this flag.
 */
#घोषणा न_अंकD_WAIT_TCCS		BIT(21)

/*
 * Whether the न_अंकD chip is a boot medium. Drivers might use this inक्रमmation
 * to select ECC algorithms supported by the boot ROM or similar restrictions.
 */
#घोषणा न_अंकD_IS_BOOT_MEDIUM	BIT(22)

/*
 * Do not try to tweak the timings at runसमय. This is needed when the
 * controller initializes the timings on itself or when it relies on
 * configuration करोne by the bootloader.
 */
#घोषणा न_अंकD_KEEP_TIMINGS	BIT(23)

/*
 * There are dअगरferent places where the manufacturer stores the factory bad
 * block markers.
 *
 * Position within the block: Each of these pages needs to be checked क्रम a
 * bad block marking pattern.
 */
#घोषणा न_अंकD_BBM_FIRSTPAGE	BIT(24)
#घोषणा न_अंकD_BBM_SECONDPAGE	BIT(25)
#घोषणा न_अंकD_BBM_LASTPAGE	BIT(26)

/*
 * Some controllers with pipelined ECC engines override the BBM marker with
 * data or ECC bytes, thus making bad block detection through bad block marker
 * impossible. Let's flag those chips so the core knows it shouldn't check the
 * BBM and consider all blocks good.
 */
#घोषणा न_अंकD_NO_BBM_QUIRK	BIT(27)

/* Cell info स्थिरants */
#घोषणा न_अंकD_CI_CHIPNR_MSK	0x03
#घोषणा न_अंकD_CI_CELLTYPE_MSK	0x0C
#घोषणा न_अंकD_CI_CELLTYPE_SHIFT	2

/* Position within the OOB data of the page */
#घोषणा न_अंकD_BBM_POS_SMALL		5
#घोषणा न_अंकD_BBM_POS_LARGE		0

/**
 * काष्ठा nand_parameters - न_अंकD generic parameters from the parameter page
 * @model: Model name
 * @supports_set_get_features: The न_अंकD chip supports setting/getting features
 * @set_feature_list: Biपंचांगap of features that can be set
 * @get_feature_list: Biपंचांगap of features that can be get
 * @onfi: ONFI specअगरic parameters
 */
काष्ठा nand_parameters अणु
	/* Generic parameters */
	स्थिर अक्षर *model;
	bool supports_set_get_features;
	DECLARE_BITMAP(set_feature_list, ONFI_FEATURE_NUMBER);
	DECLARE_BITMAP(get_feature_list, ONFI_FEATURE_NUMBER);

	/* ONFI parameters */
	काष्ठा onfi_params *onfi;
पूर्ण;

/* The maximum expected count of bytes in the न_अंकD ID sequence */
#घोषणा न_अंकD_MAX_ID_LEN 8

/**
 * काष्ठा nand_id - न_अंकD id काष्ठाure
 * @data: buffer containing the id bytes.
 * @len: ID length.
 */
काष्ठा nand_id अणु
	u8 data[न_अंकD_MAX_ID_LEN];
	पूर्णांक len;
पूर्ण;

/**
 * काष्ठा nand_ecc_step_info - ECC step inक्रमmation of ECC engine
 * @stepsize: data bytes per ECC step
 * @strengths: array of supported strengths
 * @nstrengths: number of supported strengths
 */
काष्ठा nand_ecc_step_info अणु
	पूर्णांक stepsize;
	स्थिर पूर्णांक *strengths;
	पूर्णांक nstrengths;
पूर्ण;

/**
 * काष्ठा nand_ecc_caps - capability of ECC engine
 * @stepinfos: array of ECC step inक्रमmation
 * @nstepinfos: number of ECC step inक्रमmation
 * @calc_ecc_bytes: driver's hook to calculate ECC bytes per step
 */
काष्ठा nand_ecc_caps अणु
	स्थिर काष्ठा nand_ecc_step_info *stepinfos;
	पूर्णांक nstepinfos;
	पूर्णांक (*calc_ecc_bytes)(पूर्णांक step_size, पूर्णांक strength);
पूर्ण;

/* a लघुhand to generate काष्ठा nand_ecc_caps with only one ECC stepsize */
#घोषणा न_अंकD_ECC_CAPS_SINGLE(__name, __calc, __step, ...)	\
अटल स्थिर पूर्णांक __name##_strengths[] = अणु __VA_ARGS__ पूर्ण;	\
अटल स्थिर काष्ठा nand_ecc_step_info __name##_stepinfo = अणु	\
	.stepsize = __step,					\
	.strengths = __name##_strengths,			\
	.nstrengths = ARRAY_SIZE(__name##_strengths),		\
पूर्ण;								\
अटल स्थिर काष्ठा nand_ecc_caps __name = अणु			\
	.stepinfos = &__name##_stepinfo,			\
	.nstepinfos = 1,					\
	.calc_ecc_bytes = __calc,				\
पूर्ण

/**
 * काष्ठा nand_ecc_ctrl - Control काष्ठाure क्रम ECC
 * @engine_type: ECC engine type
 * @placement:	OOB bytes placement
 * @algo:	ECC algorithm
 * @steps:	number of ECC steps per page
 * @size:	data bytes per ECC step
 * @bytes:	ECC bytes per step
 * @strength:	max number of correctible bits per ECC step
 * @total:	total number of ECC bytes per page
 * @prepad:	padding inक्रमmation क्रम syndrome based ECC generators
 * @postpad:	padding inक्रमmation क्रम syndrome based ECC generators
 * @options:	ECC specअगरic options (see न_अंकD_ECC_XXX flags defined above)
 * @calc_buf:	buffer क्रम calculated ECC, size is oobsize.
 * @code_buf:	buffer क्रम ECC पढ़ो from flash, size is oobsize.
 * @hwctl:	function to control hardware ECC generator. Must only
 *		be provided अगर an hardware ECC is available
 * @calculate:	function क्रम ECC calculation or पढ़ोback from ECC hardware
 * @correct:	function क्रम ECC correction, matching to ECC generator (sw/hw).
 *		Should वापस a positive number representing the number of
 *		corrected bitflips, -EBADMSG अगर the number of bitflips exceed
 *		ECC strength, or any other error code अगर the error is not
 *		directly related to correction.
 *		If -EBADMSG is वापसed the input buffers should be left
 *		untouched.
 * @पढ़ो_page_raw:	function to पढ़ो a raw page without ECC. This function
 *			should hide the specअगरic layout used by the ECC
 *			controller and always वापस contiguous in-band and
 *			out-of-band data even अगर they're not stored
 *			contiguously on the न_अंकD chip (e.g.
 *			न_अंकD_ECC_PLACEMENT_INTERLEAVED पूर्णांकerleaves in-band and
 *			out-of-band data).
 * @ग_लिखो_page_raw:	function to ग_लिखो a raw page without ECC. This function
 *			should hide the specअगरic layout used by the ECC
 *			controller and consider the passed data as contiguous
 *			in-band and out-of-band data. ECC controller is
 *			responsible क्रम करोing the appropriate transक्रमmations
 *			to adapt to its specअगरic layout (e.g.
 *			न_अंकD_ECC_PLACEMENT_INTERLEAVED पूर्णांकerleaves in-band and
 *			out-of-band data).
 * @पढ़ो_page:	function to पढ़ो a page according to the ECC generator
 *		requirements; वापसs maximum number of bitflips corrected in
 *		any single ECC step, -EIO hw error
 * @पढ़ो_subpage:	function to पढ़ो parts of the page covered by ECC;
 *			वापसs same as पढ़ो_page()
 * @ग_लिखो_subpage:	function to ग_लिखो parts of the page covered by ECC.
 * @ग_लिखो_page:	function to ग_लिखो a page according to the ECC generator
 *		requirements.
 * @ग_लिखो_oob_raw:	function to ग_लिखो chip OOB data without ECC
 * @पढ़ो_oob_raw:	function to पढ़ो chip OOB data without ECC
 * @पढ़ो_oob:	function to पढ़ो chip OOB data
 * @ग_लिखो_oob:	function to ग_लिखो chip OOB data
 */
काष्ठा nand_ecc_ctrl अणु
	क्रमागत nand_ecc_engine_type engine_type;
	क्रमागत nand_ecc_placement placement;
	क्रमागत nand_ecc_algo algo;
	पूर्णांक steps;
	पूर्णांक size;
	पूर्णांक bytes;
	पूर्णांक total;
	पूर्णांक strength;
	पूर्णांक prepad;
	पूर्णांक postpad;
	अचिन्हित पूर्णांक options;
	u8 *calc_buf;
	u8 *code_buf;
	व्योम (*hwctl)(काष्ठा nand_chip *chip, पूर्णांक mode);
	पूर्णांक (*calculate)(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *dat,
			 uपूर्णांक8_t *ecc_code);
	पूर्णांक (*correct)(काष्ठा nand_chip *chip, uपूर्णांक8_t *dat, uपूर्णांक8_t *पढ़ो_ecc,
		       uपूर्णांक8_t *calc_ecc);
	पूर्णांक (*पढ़ो_page_raw)(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			     पूर्णांक oob_required, पूर्णांक page);
	पूर्णांक (*ग_लिखो_page_raw)(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			      पूर्णांक oob_required, पूर्णांक page);
	पूर्णांक (*पढ़ो_page)(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
			 पूर्णांक oob_required, पूर्णांक page);
	पूर्णांक (*पढ़ो_subpage)(काष्ठा nand_chip *chip, uपूर्णांक32_t offs,
			    uपूर्णांक32_t len, uपूर्णांक8_t *buf, पूर्णांक page);
	पूर्णांक (*ग_लिखो_subpage)(काष्ठा nand_chip *chip, uपूर्णांक32_t offset,
			     uपूर्णांक32_t data_len, स्थिर uपूर्णांक8_t *data_buf,
			     पूर्णांक oob_required, पूर्णांक page);
	पूर्णांक (*ग_लिखो_page)(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			  पूर्णांक oob_required, पूर्णांक page);
	पूर्णांक (*ग_लिखो_oob_raw)(काष्ठा nand_chip *chip, पूर्णांक page);
	पूर्णांक (*पढ़ो_oob_raw)(काष्ठा nand_chip *chip, पूर्णांक page);
	पूर्णांक (*पढ़ो_oob)(काष्ठा nand_chip *chip, पूर्णांक page);
	पूर्णांक (*ग_लिखो_oob)(काष्ठा nand_chip *chip, पूर्णांक page);
पूर्ण;

/**
 * काष्ठा nand_sdr_timings - SDR न_अंकD chip timings
 *
 * This काष्ठा defines the timing requirements of a SDR न_अंकD chip.
 * These inक्रमmation can be found in every न_अंकD datasheets and the timings
 * meaning are described in the ONFI specअगरications:
 * www.onfi.org/~/media/ONFI/specs/onfi_3_1_spec.pdf (chapter 4.15 Timing
 * Parameters)
 *
 * All these timings are expressed in picoseconds.
 *
 * @tBERS_max: Block erase समय
 * @tCCS_min: Change column setup समय
 * @tPROG_max: Page program समय
 * @tR_max: Page पढ़ो समय
 * @tALH_min: ALE hold समय
 * @tADL_min: ALE to data loading समय
 * @tALS_min: ALE setup समय
 * @tAR_min: ALE to RE# delay
 * @tCEA_max: CE# access समय
 * @tCEH_min: CE# high hold समय
 * @tCH_min:  CE# hold समय
 * @tCHZ_max: CE# high to output hi-Z
 * @tCLH_min: CLE hold समय
 * @tCLR_min: CLE to RE# delay
 * @tCLS_min: CLE setup समय
 * @tCOH_min: CE# high to output hold
 * @tCS_min: CE# setup समय
 * @tDH_min: Data hold समय
 * @tDS_min: Data setup समय
 * @tFEAT_max: Busy समय क्रम Set Features and Get Features
 * @tIR_min: Output hi-Z to RE# low
 * @tITC_max: Interface and Timing Mode Change समय
 * @tRC_min: RE# cycle समय
 * @tREA_max: RE# access समय
 * @tREH_min: RE# high hold समय
 * @tRHOH_min: RE# high to output hold
 * @tRHW_min: RE# high to WE# low
 * @tRHZ_max: RE# high to output hi-Z
 * @tRLOH_min: RE# low to output hold
 * @tRP_min: RE# pulse width
 * @tRR_min: Ready to RE# low (data only)
 * @tRST_max: Device reset समय, measured from the falling edge of R/B# to the
 *	      rising edge of R/B#.
 * @tWB_max: WE# high to SR[6] low
 * @tWC_min: WE# cycle समय
 * @tWH_min: WE# high hold समय
 * @tWHR_min: WE# high to RE# low
 * @tWP_min: WE# pulse width
 * @tWW_min: WP# transition to WE# low
 */
काष्ठा nand_sdr_timings अणु
	u64 tBERS_max;
	u32 tCCS_min;
	u64 tPROG_max;
	u64 tR_max;
	u32 tALH_min;
	u32 tADL_min;
	u32 tALS_min;
	u32 tAR_min;
	u32 tCEA_max;
	u32 tCEH_min;
	u32 tCH_min;
	u32 tCHZ_max;
	u32 tCLH_min;
	u32 tCLR_min;
	u32 tCLS_min;
	u32 tCOH_min;
	u32 tCS_min;
	u32 tDH_min;
	u32 tDS_min;
	u32 tFEAT_max;
	u32 tIR_min;
	u32 tITC_max;
	u32 tRC_min;
	u32 tREA_max;
	u32 tREH_min;
	u32 tRHOH_min;
	u32 tRHW_min;
	u32 tRHZ_max;
	u32 tRLOH_min;
	u32 tRP_min;
	u32 tRR_min;
	u64 tRST_max;
	u32 tWB_max;
	u32 tWC_min;
	u32 tWH_min;
	u32 tWHR_min;
	u32 tWP_min;
	u32 tWW_min;
पूर्ण;

/**
 * क्रमागत nand_पूर्णांकerface_type - न_अंकD पूर्णांकerface type
 * @न_अंकD_SDR_IFACE:	Single Data Rate पूर्णांकerface
 */
क्रमागत nand_पूर्णांकerface_type अणु
	न_अंकD_SDR_IFACE,
पूर्ण;

/**
 * काष्ठा nand_पूर्णांकerface_config - न_अंकD पूर्णांकerface timing
 * @type:	 type of the timing
 * @timings:	 The timing inक्रमmation
 * @timings.mode: Timing mode as defined in the specअगरication
 * @timings.sdr: Use it when @type is %न_अंकD_SDR_IFACE.
 */
काष्ठा nand_पूर्णांकerface_config अणु
	क्रमागत nand_पूर्णांकerface_type type;
	काष्ठा nand_timings अणु
		अचिन्हित पूर्णांक mode;
		जोड़ अणु
			काष्ठा nand_sdr_timings sdr;
		पूर्ण;
	पूर्ण timings;
पूर्ण;

/**
 * nand_get_sdr_timings - get SDR timing from data पूर्णांकerface
 * @conf:	The data पूर्णांकerface
 */
अटल अंतरभूत स्थिर काष्ठा nand_sdr_timings *
nand_get_sdr_timings(स्थिर काष्ठा nand_पूर्णांकerface_config *conf)
अणु
	अगर (conf->type != न_अंकD_SDR_IFACE)
		वापस ERR_PTR(-EINVAL);

	वापस &conf->timings.sdr;
पूर्ण

/**
 * काष्ठा nand_op_cmd_instr - Definition of a command inकाष्ठाion
 * @opcode: the command to issue in one cycle
 */
काष्ठा nand_op_cmd_instr अणु
	u8 opcode;
पूर्ण;

/**
 * काष्ठा nand_op_addr_instr - Definition of an address inकाष्ठाion
 * @naddrs: length of the @addrs array
 * @addrs: array containing the address cycles to issue
 */
काष्ठा nand_op_addr_instr अणु
	अचिन्हित पूर्णांक naddrs;
	स्थिर u8 *addrs;
पूर्ण;

/**
 * काष्ठा nand_op_data_instr - Definition of a data inकाष्ठाion
 * @len: number of data bytes to move
 * @buf: buffer to fill
 * @buf.in: buffer to fill when पढ़ोing from the न_अंकD chip
 * @buf.out: buffer to पढ़ो from when writing to the न_अंकD chip
 * @क्रमce_8bit: क्रमce 8-bit access
 *
 * Please note that "in" and "out" are inverted from the ONFI specअगरication
 * and are from the controller perspective, so a "in" is a पढ़ो from the न_अंकD
 * chip जबतक a "out" is a ग_लिखो to the न_अंकD chip.
 */
काष्ठा nand_op_data_instr अणु
	अचिन्हित पूर्णांक len;
	जोड़ अणु
		व्योम *in;
		स्थिर व्योम *out;
	पूर्ण buf;
	bool क्रमce_8bit;
पूर्ण;

/**
 * काष्ठा nand_op_रुकोrdy_instr - Definition of a रुको पढ़ोy inकाष्ठाion
 * @समयout_ms: maximum delay जबतक रुकोing क्रम the पढ़ोy/busy pin in ms
 */
काष्ठा nand_op_रुकोrdy_instr अणु
	अचिन्हित पूर्णांक समयout_ms;
पूर्ण;

/**
 * क्रमागत nand_op_instr_type - Definition of all inकाष्ठाion types
 * @न_अंकD_OP_CMD_INSTR: command inकाष्ठाion
 * @न_अंकD_OP_ADDR_INSTR: address inकाष्ठाion
 * @न_अंकD_OP_DATA_IN_INSTR: data in inकाष्ठाion
 * @न_अंकD_OP_DATA_OUT_INSTR: data out inकाष्ठाion
 * @न_अंकD_OP_WAITRDY_INSTR: रुको पढ़ोy inकाष्ठाion
 */
क्रमागत nand_op_instr_type अणु
	न_अंकD_OP_CMD_INSTR,
	न_अंकD_OP_ADDR_INSTR,
	न_अंकD_OP_DATA_IN_INSTR,
	न_अंकD_OP_DATA_OUT_INSTR,
	न_अंकD_OP_WAITRDY_INSTR,
पूर्ण;

/**
 * काष्ठा nand_op_instr - Inकाष्ठाion object
 * @type: the inकाष्ठाion type
 * @ctx:  extra data associated to the inकाष्ठाion. You'll have to use the
 *        appropriate element depending on @type
 * @ctx.cmd: use it अगर @type is %न_अंकD_OP_CMD_INSTR
 * @ctx.addr: use it अगर @type is %न_अंकD_OP_ADDR_INSTR
 * @ctx.data: use it अगर @type is %न_अंकD_OP_DATA_IN_INSTR
 *	      or %न_अंकD_OP_DATA_OUT_INSTR
 * @ctx.रुकोrdy: use it अगर @type is %न_अंकD_OP_WAITRDY_INSTR
 * @delay_ns: delay the controller should apply after the inकाष्ठाion has been
 *	      issued on the bus. Most modern controllers have पूर्णांकernal timings
 *	      control logic, and in this हाल, the controller driver can ignore
 *	      this field.
 */
काष्ठा nand_op_instr अणु
	क्रमागत nand_op_instr_type type;
	जोड़ अणु
		काष्ठा nand_op_cmd_instr cmd;
		काष्ठा nand_op_addr_instr addr;
		काष्ठा nand_op_data_instr data;
		काष्ठा nand_op_रुकोrdy_instr रुकोrdy;
	पूर्ण ctx;
	अचिन्हित पूर्णांक delay_ns;
पूर्ण;

/*
 * Special handling must be करोne क्रम the WAITRDY समयout parameter as it usually
 * is either tPROG (after a prog), tR (beक्रमe a पढ़ो), tRST (during a reset) or
 * tBERS (during an erase) which all of them are u64 values that cannot be
 * भागided by usual kernel macros and must be handled with the special
 * DIV_ROUND_UP_ULL() macro.
 *
 * Cast to type of भागidend is needed here to guarantee that the result won't
 * be an अचिन्हित दीर्घ दीर्घ when the भागidend is an अचिन्हित दीर्घ (or smaller),
 * which is what the compiler करोes when it sees ternary चालक with 2
 * dअगरferent वापस types (picks the largest type to make sure there's no
 * loss).
 */
#घोषणा __DIVIDE(भागidend, भागisor) (अणु						\
	(__typeof__(भागidend))(माप(भागidend) <= माप(अचिन्हित दीर्घ) ?	\
			       DIV_ROUND_UP(भागidend, भागisor) :		\
			       DIV_ROUND_UP_ULL(भागidend, भागisor)); 		\
	पूर्ण)
#घोषणा PSEC_TO_NSEC(x) __DIVIDE(x, 1000)
#घोषणा PSEC_TO_MSEC(x) __DIVIDE(x, 1000000000)

#घोषणा न_अंकD_OP_CMD(id, ns)						\
	अणु								\
		.type = न_अंकD_OP_CMD_INSTR,				\
		.ctx.cmd.opcode = id,					\
		.delay_ns = ns,						\
	पूर्ण

#घोषणा न_अंकD_OP_ADDR(ncycles, cycles, ns)				\
	अणु								\
		.type = न_अंकD_OP_ADDR_INSTR,				\
		.ctx.addr = अणु						\
			.naddrs = ncycles,				\
			.addrs = cycles,				\
		पूर्ण,							\
		.delay_ns = ns,						\
	पूर्ण

#घोषणा न_अंकD_OP_DATA_IN(l, b, ns)					\
	अणु								\
		.type = न_अंकD_OP_DATA_IN_INSTR,				\
		.ctx.data = अणु						\
			.len = l,					\
			.buf.in = b,					\
			.क्रमce_8bit = false,				\
		पूर्ण,							\
		.delay_ns = ns,						\
	पूर्ण

#घोषणा न_अंकD_OP_DATA_OUT(l, b, ns)					\
	अणु								\
		.type = न_अंकD_OP_DATA_OUT_INSTR,				\
		.ctx.data = अणु						\
			.len = l,					\
			.buf.out = b,					\
			.क्रमce_8bit = false,				\
		पूर्ण,							\
		.delay_ns = ns,						\
	पूर्ण

#घोषणा न_अंकD_OP_8BIT_DATA_IN(l, b, ns)					\
	अणु								\
		.type = न_अंकD_OP_DATA_IN_INSTR,				\
		.ctx.data = अणु						\
			.len = l,					\
			.buf.in = b,					\
			.क्रमce_8bit = true,				\
		पूर्ण,							\
		.delay_ns = ns,						\
	पूर्ण

#घोषणा न_अंकD_OP_8BIT_DATA_OUT(l, b, ns)					\
	अणु								\
		.type = न_अंकD_OP_DATA_OUT_INSTR,				\
		.ctx.data = अणु						\
			.len = l,					\
			.buf.out = b,					\
			.क्रमce_8bit = true,				\
		पूर्ण,							\
		.delay_ns = ns,						\
	पूर्ण

#घोषणा न_अंकD_OP_WAIT_RDY(tout_ms, ns)					\
	अणु								\
		.type = न_अंकD_OP_WAITRDY_INSTR,				\
		.ctx.रुकोrdy.समयout_ms = tout_ms,			\
		.delay_ns = ns,						\
	पूर्ण

/**
 * काष्ठा nand_subop - a sub operation
 * @cs: the CS line to select क्रम this न_अंकD sub-operation
 * @instrs: array of inकाष्ठाions
 * @ninstrs: length of the @instrs array
 * @first_instr_start_off: offset to start from क्रम the first inकाष्ठाion
 *			   of the sub-operation
 * @last_instr_end_off: offset to end at (excluded) क्रम the last inकाष्ठाion
 *			of the sub-operation
 *
 * Both @first_instr_start_off and @last_instr_end_off only apply to data or
 * address inकाष्ठाions.
 *
 * When an operation cannot be handled as is by the न_अंकD controller, it will
 * be split by the parser पूर्णांकo sub-operations which will be passed to the
 * controller driver.
 */
काष्ठा nand_subop अणु
	अचिन्हित पूर्णांक cs;
	स्थिर काष्ठा nand_op_instr *instrs;
	अचिन्हित पूर्णांक ninstrs;
	अचिन्हित पूर्णांक first_instr_start_off;
	अचिन्हित पूर्णांक last_instr_end_off;
पूर्ण;

अचिन्हित पूर्णांक nand_subop_get_addr_start_off(स्थिर काष्ठा nand_subop *subop,
					   अचिन्हित पूर्णांक op_id);
अचिन्हित पूर्णांक nand_subop_get_num_addr_cyc(स्थिर काष्ठा nand_subop *subop,
					 अचिन्हित पूर्णांक op_id);
अचिन्हित पूर्णांक nand_subop_get_data_start_off(स्थिर काष्ठा nand_subop *subop,
					   अचिन्हित पूर्णांक op_id);
अचिन्हित पूर्णांक nand_subop_get_data_len(स्थिर काष्ठा nand_subop *subop,
				     अचिन्हित पूर्णांक op_id);

/**
 * काष्ठा nand_op_parser_addr_स्थिरraपूर्णांकs - Constraपूर्णांकs क्रम address inकाष्ठाions
 * @maxcycles: maximum number of address cycles the controller can issue in a
 *	       single step
 */
काष्ठा nand_op_parser_addr_स्थिरraपूर्णांकs अणु
	अचिन्हित पूर्णांक maxcycles;
पूर्ण;

/**
 * काष्ठा nand_op_parser_data_स्थिरraपूर्णांकs - Constraपूर्णांकs क्रम data inकाष्ठाions
 * @maxlen: maximum data length that the controller can handle in a single step
 */
काष्ठा nand_op_parser_data_स्थिरraपूर्णांकs अणु
	अचिन्हित पूर्णांक maxlen;
पूर्ण;

/**
 * काष्ठा nand_op_parser_pattern_elem - One element of a pattern
 * @type: the inकाष्ठाuction type
 * @optional: whether this element of the pattern is optional or mandatory
 * @ctx: address or data स्थिरraपूर्णांक
 * @ctx.addr: address स्थिरraपूर्णांक (number of cycles)
 * @ctx.data: data स्थिरraपूर्णांक (data length)
 */
काष्ठा nand_op_parser_pattern_elem अणु
	क्रमागत nand_op_instr_type type;
	bool optional;
	जोड़ अणु
		काष्ठा nand_op_parser_addr_स्थिरraपूर्णांकs addr;
		काष्ठा nand_op_parser_data_स्थिरraपूर्णांकs data;
	पूर्ण ctx;
पूर्ण;

#घोषणा न_अंकD_OP_PARSER_PAT_CMD_ELEM(_opt)			\
	अणु							\
		.type = न_अंकD_OP_CMD_INSTR,			\
		.optional = _opt,				\
	पूर्ण

#घोषणा न_अंकD_OP_PARSER_PAT_ADDR_ELEM(_opt, _maxcycles)		\
	अणु							\
		.type = न_अंकD_OP_ADDR_INSTR,			\
		.optional = _opt,				\
		.ctx.addr.maxcycles = _maxcycles,		\
	पूर्ण

#घोषणा न_अंकD_OP_PARSER_PAT_DATA_IN_ELEM(_opt, _maxlen)		\
	अणु							\
		.type = न_अंकD_OP_DATA_IN_INSTR,			\
		.optional = _opt,				\
		.ctx.data.maxlen = _maxlen,			\
	पूर्ण

#घोषणा न_अंकD_OP_PARSER_PAT_DATA_OUT_ELEM(_opt, _maxlen)		\
	अणु							\
		.type = न_अंकD_OP_DATA_OUT_INSTR,			\
		.optional = _opt,				\
		.ctx.data.maxlen = _maxlen,			\
	पूर्ण

#घोषणा न_अंकD_OP_PARSER_PAT_WAITRDY_ELEM(_opt)			\
	अणु							\
		.type = न_अंकD_OP_WAITRDY_INSTR,			\
		.optional = _opt,				\
	पूर्ण

/**
 * काष्ठा nand_op_parser_pattern - न_अंकD sub-operation pattern descriptor
 * @elems: array of pattern elements
 * @nelems: number of pattern elements in @elems array
 * @exec: the function that will issue a sub-operation
 *
 * A pattern is a list of elements, each element reprensenting one inकाष्ठाion
 * with its स्थिरraपूर्णांकs. The pattern itself is used by the core to match न_अंकD
 * chip operation with न_अंकD controller operations.
 * Once a match between a न_अंकD controller operation pattern and a न_अंकD chip
 * operation (or a sub-set of a न_अंकD operation) is found, the pattern ->exec()
 * hook is called so that the controller driver can issue the operation on the
 * bus.
 *
 * Controller drivers should declare as many patterns as they support and pass
 * this list of patterns (created with the help of the following macro) to
 * the nand_op_parser_exec_op() helper.
 */
काष्ठा nand_op_parser_pattern अणु
	स्थिर काष्ठा nand_op_parser_pattern_elem *elems;
	अचिन्हित पूर्णांक nelems;
	पूर्णांक (*exec)(काष्ठा nand_chip *chip, स्थिर काष्ठा nand_subop *subop);
पूर्ण;

#घोषणा न_अंकD_OP_PARSER_PATTERN(_exec, ...)							\
	अणु											\
		.exec = _exec,									\
		.elems = (स्थिर काष्ठा nand_op_parser_pattern_elem[]) अणु __VA_ARGS__ पूर्ण,		\
		.nelems = माप((काष्ठा nand_op_parser_pattern_elem[]) अणु __VA_ARGS__ पूर्ण) /	\
			  माप(काष्ठा nand_op_parser_pattern_elem),				\
	पूर्ण

/**
 * काष्ठा nand_op_parser - न_अंकD controller operation parser descriptor
 * @patterns: array of supported patterns
 * @npatterns: length of the @patterns array
 *
 * The parser descriptor is just an array of supported patterns which will be
 * iterated by nand_op_parser_exec_op() everyसमय it tries to execute an
 * न_अंकD operation (or tries to determine अगर a specअगरic operation is supported).
 *
 * It is worth mentioning that patterns will be tested in their declaration
 * order, and the first match will be taken, so it's important to order patterns
 * appropriately so that simple/inefficient patterns are placed at the end of
 * the list. Usually, this is where you put single inकाष्ठाion patterns.
 */
काष्ठा nand_op_parser अणु
	स्थिर काष्ठा nand_op_parser_pattern *patterns;
	अचिन्हित पूर्णांक npatterns;
पूर्ण;

#घोषणा न_अंकD_OP_PARSER(...)									\
	अणु											\
		.patterns = (स्थिर काष्ठा nand_op_parser_pattern[]) अणु __VA_ARGS__ पूर्ण,		\
		.npatterns = माप((काष्ठा nand_op_parser_pattern[]) अणु __VA_ARGS__ पूर्ण) /	\
			     माप(काष्ठा nand_op_parser_pattern),				\
	पूर्ण

/**
 * काष्ठा nand_operation - न_अंकD operation descriptor
 * @cs: the CS line to select क्रम this न_अंकD operation
 * @instrs: array of inकाष्ठाions to execute
 * @ninstrs: length of the @instrs array
 *
 * The actual operation काष्ठाure that will be passed to chip->exec_op().
 */
काष्ठा nand_operation अणु
	अचिन्हित पूर्णांक cs;
	स्थिर काष्ठा nand_op_instr *instrs;
	अचिन्हित पूर्णांक ninstrs;
पूर्ण;

#घोषणा न_अंकD_OPERATION(_cs, _instrs)				\
	अणु							\
		.cs = _cs,					\
		.instrs = _instrs,				\
		.ninstrs = ARRAY_SIZE(_instrs),			\
	पूर्ण

पूर्णांक nand_op_parser_exec_op(काष्ठा nand_chip *chip,
			   स्थिर काष्ठा nand_op_parser *parser,
			   स्थिर काष्ठा nand_operation *op, bool check_only);

अटल अंतरभूत व्योम nand_op_trace(स्थिर अक्षर *prefix,
				 स्थिर काष्ठा nand_op_instr *instr)
अणु
#अगर IS_ENABLED(CONFIG_DYNAMIC_DEBUG) || defined(DEBUG)
	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		pr_debug("%sCMD      [0x%02x]\n", prefix,
			 instr->ctx.cmd.opcode);
		अवरोध;
	हाल न_अंकD_OP_ADDR_INSTR:
		pr_debug("%sADDR     [%d cyc: %*ph]\n", prefix,
			 instr->ctx.addr.naddrs,
			 instr->ctx.addr.naddrs < 64 ?
			 instr->ctx.addr.naddrs : 64,
			 instr->ctx.addr.addrs);
		अवरोध;
	हाल न_अंकD_OP_DATA_IN_INSTR:
		pr_debug("%sDATA_IN  [%d B%s]\n", prefix,
			 instr->ctx.data.len,
			 instr->ctx.data.क्रमce_8bit ?
			 ", force 8-bit" : "");
		अवरोध;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		pr_debug("%sDATA_OUT [%d B%s]\n", prefix,
			 instr->ctx.data.len,
			 instr->ctx.data.क्रमce_8bit ?
			 ", force 8-bit" : "");
		अवरोध;
	हाल न_अंकD_OP_WAITRDY_INSTR:
		pr_debug("%sWAITRDY  [max %d ms]\n", prefix,
			 instr->ctx.रुकोrdy.समयout_ms);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
पूर्ण

/**
 * काष्ठा nand_controller_ops - Controller operations
 *
 * @attach_chip: this method is called after the न_अंकD detection phase after
 *		 flash ID and MTD fields such as erase size, page size and OOB
 *		 size have been set up. ECC requirements are available अगर
 *		 provided by the न_अंकD chip or device tree. Typically used to
 *		 choose the appropriate ECC configuration and allocate
 *		 associated resources.
 *		 This hook is optional.
 * @detach_chip: मुक्त all resources allocated/claimed in
 *		 nand_controller_ops->attach_chip().
 *		 This hook is optional.
 * @exec_op:	 controller specअगरic method to execute न_अंकD operations.
 *		 This method replaces chip->legacy.cmdfunc(),
 *		 chip->legacy.अणुपढ़ो,ग_लिखोपूर्ण_अणुbuf,byte,wordपूर्ण(),
 *		 chip->legacy.dev_पढ़ोy() and chip->legacy.waअगरunc().
 * @setup_पूर्णांकerface: setup the data पूर्णांकerface and timing. If chipnr is set to
 *		     %न_अंकD_DATA_IFACE_CHECK_ONLY this means the configuration
 *		     should not be applied but only checked.
 *		     This hook is optional.
 */
काष्ठा nand_controller_ops अणु
	पूर्णांक (*attach_chip)(काष्ठा nand_chip *chip);
	व्योम (*detach_chip)(काष्ठा nand_chip *chip);
	पूर्णांक (*exec_op)(काष्ठा nand_chip *chip,
		       स्थिर काष्ठा nand_operation *op,
		       bool check_only);
	पूर्णांक (*setup_पूर्णांकerface)(काष्ठा nand_chip *chip, पूर्णांक chipnr,
			       स्थिर काष्ठा nand_पूर्णांकerface_config *conf);
पूर्ण;

/**
 * काष्ठा nand_controller - Structure used to describe a न_अंकD controller
 *
 * @lock:		lock used to serialize accesses to the न_अंकD controller
 * @ops:		न_अंकD controller operations.
 */
काष्ठा nand_controller अणु
	काष्ठा mutex lock;
	स्थिर काष्ठा nand_controller_ops *ops;
पूर्ण;

अटल अंतरभूत व्योम nand_controller_init(काष्ठा nand_controller *nfc)
अणु
	mutex_init(&nfc->lock);
पूर्ण

/**
 * काष्ठा nand_legacy - न_अंकD chip legacy fields/hooks
 * @IO_ADDR_R: address to पढ़ो the 8 I/O lines of the flash device
 * @IO_ADDR_W: address to ग_लिखो the 8 I/O lines of the flash device
 * @select_chip: select/deselect a specअगरic target/die
 * @पढ़ो_byte: पढ़ो one byte from the chip
 * @ग_लिखो_byte: ग_लिखो a single byte to the chip on the low 8 I/O lines
 * @ग_लिखो_buf: ग_लिखो data from the buffer to the chip
 * @पढ़ो_buf: पढ़ो data from the chip पूर्णांकo the buffer
 * @cmd_ctrl: hardware specअगरic function क्रम controlling ALE/CLE/nCE. Also used
 *	      to ग_लिखो command and address
 * @cmdfunc: hardware specअगरic function क्रम writing commands to the chip.
 * @dev_पढ़ोy: hardware specअगरic function क्रम accessing device पढ़ोy/busy line.
 *	       If set to शून्य no access to पढ़ोy/busy is available and the
 *	       पढ़ोy/busy inक्रमmation is पढ़ो from the chip status रेजिस्टर.
 * @रुकोfunc: hardware specअगरic function क्रम रुको on पढ़ोy.
 * @block_bad: check अगर a block is bad, using OOB markers
 * @block_markbad: mark a block bad
 * @set_features: set the न_अंकD chip features
 * @get_features: get the न_अंकD chip features
 * @chip_delay: chip dependent delay क्रम transferring data from array to पढ़ो
 *		regs (tR).
 * @dummy_controller: dummy controller implementation क्रम drivers that can
 *		      only control a single chip
 *
 * If you look at this काष्ठाure you're alपढ़ोy wrong. These fields/hooks are
 * all deprecated.
 */
काष्ठा nand_legacy अणु
	व्योम __iomem *IO_ADDR_R;
	व्योम __iomem *IO_ADDR_W;
	व्योम (*select_chip)(काष्ठा nand_chip *chip, पूर्णांक cs);
	u8 (*पढ़ो_byte)(काष्ठा nand_chip *chip);
	व्योम (*ग_लिखो_byte)(काष्ठा nand_chip *chip, u8 byte);
	व्योम (*ग_लिखो_buf)(काष्ठा nand_chip *chip, स्थिर u8 *buf, पूर्णांक len);
	व्योम (*पढ़ो_buf)(काष्ठा nand_chip *chip, u8 *buf, पूर्णांक len);
	व्योम (*cmd_ctrl)(काष्ठा nand_chip *chip, पूर्णांक dat, अचिन्हित पूर्णांक ctrl);
	व्योम (*cmdfunc)(काष्ठा nand_chip *chip, अचिन्हित command, पूर्णांक column,
			पूर्णांक page_addr);
	पूर्णांक (*dev_पढ़ोy)(काष्ठा nand_chip *chip);
	पूर्णांक (*रुकोfunc)(काष्ठा nand_chip *chip);
	पूर्णांक (*block_bad)(काष्ठा nand_chip *chip, loff_t ofs);
	पूर्णांक (*block_markbad)(काष्ठा nand_chip *chip, loff_t ofs);
	पूर्णांक (*set_features)(काष्ठा nand_chip *chip, पूर्णांक feature_addr,
			    u8 *subfeature_para);
	पूर्णांक (*get_features)(काष्ठा nand_chip *chip, पूर्णांक feature_addr,
			    u8 *subfeature_para);
	पूर्णांक chip_delay;
	काष्ठा nand_controller dummy_controller;
पूर्ण;

/**
 * काष्ठा nand_chip_ops - न_अंकD chip operations
 * @suspend: Suspend operation
 * @resume: Resume operation
 * @lock_area: Lock operation
 * @unlock_area: Unlock operation
 * @setup_पढ़ो_retry: Set the पढ़ो-retry mode (mostly needed क्रम MLC न_अंकDs)
 * @choose_पूर्णांकerface_config: Choose the best पूर्णांकerface configuration
 */
काष्ठा nand_chip_ops अणु
	पूर्णांक (*suspend)(काष्ठा nand_chip *chip);
	व्योम (*resume)(काष्ठा nand_chip *chip);
	पूर्णांक (*lock_area)(काष्ठा nand_chip *chip, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*unlock_area)(काष्ठा nand_chip *chip, loff_t ofs, uपूर्णांक64_t len);
	पूर्णांक (*setup_पढ़ो_retry)(काष्ठा nand_chip *chip, पूर्णांक retry_mode);
	पूर्णांक (*choose_पूर्णांकerface_config)(काष्ठा nand_chip *chip,
				       काष्ठा nand_पूर्णांकerface_config *अगरace);
पूर्ण;

/**
 * काष्ठा nand_manufacturer - न_अंकD manufacturer काष्ठाure
 * @desc: The manufacturer description
 * @priv: Private inक्रमmation क्रम the manufacturer driver
 */
काष्ठा nand_manufacturer अणु
	स्थिर काष्ठा nand_manufacturer_desc *desc;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा nand_secure_region - न_अंकD secure region काष्ठाure
 * @offset: Offset of the start of the secure region
 * @size: Size of the secure region
 */
काष्ठा nand_secure_region अणु
	u64 offset;
	u64 size;
पूर्ण;

/**
 * काष्ठा nand_chip - न_अंकD Private Flash Chip Data
 * @base: Inherit from the generic न_अंकD device
 * @id: Holds न_अंकD ID
 * @parameters: Holds generic parameters under an easily पढ़ोable क्रमm
 * @manufacturer: Manufacturer inक्रमmation
 * @ops: न_अंकD chip operations
 * @legacy: All legacy fields/hooks. If you develop a new driver, करोn't even try
 *          to use any of these fields/hooks, and अगर you're modअगरying an
 *          existing driver that is using those fields/hooks, you should
 *          consider reworking the driver and aव्योम using them.
 * @options: Various chip options. They can partly be set to inक्रमm nand_scan
 *           about special functionality. See the defines क्रम further
 *           explanation.
 * @current_पूर्णांकerface_config: The currently used न_अंकD पूर्णांकerface configuration
 * @best_पूर्णांकerface_config: The best न_अंकD पूर्णांकerface configuration which fits both
 *                         the न_अंकD chip and न_अंकD controller स्थिरraपूर्णांकs. If
 *                         unset, the शेष reset पूर्णांकerface configuration must
 *                         be used.
 * @bbt_erase_shअगरt: Number of address bits in a bbt entry
 * @bbt_options: Bad block table specअगरic options. All options used here must
 *               come from bbm.h. By शेष, these options will be copied to
 *               the appropriate nand_bbt_descr's.
 * @badblockpos: Bad block marker position in the oob area
 * @badblockbits: Minimum number of set bits in a good block's bad block marker
 *                position; i.e., BBM = 11110111b is good when badblockbits = 7
 * @bbt_td: Bad block table descriptor क्रम flash lookup
 * @bbt_md: Bad block table mirror descriptor
 * @badblock_pattern: Bad block scan pattern used क्रम initial bad block scan
 * @bbt: Bad block table poपूर्णांकer
 * @page_shअगरt: Number of address bits in a page (column address bits)
 * @phys_erase_shअगरt: Number of address bits in a physical eraseblock
 * @chip_shअगरt: Number of address bits in one chip
 * @pagemask: Page number mask = number of (pages / chip) - 1
 * @subpagesize: Holds the subpagesize
 * @data_buf: Buffer क्रम data, size is (page size + oobsize)
 * @oob_poi: poपूर्णांकer on the OOB area covered by data_buf
 * @pagecache: Structure containing page cache related fields
 * @pagecache.bitflips: Number of bitflips of the cached page
 * @pagecache.page: Page number currently in the cache. -1 means no page is
 *                  currently cached
 * @buf_align: Minimum buffer alignment required by a platक्रमm
 * @lock: Lock protecting the suspended field. Also used to serialize accesses
 *        to the न_अंकD device
 * @suspended: Set to 1 when the device is suspended, 0 when it's not
 * @cur_cs: Currently selected target. -1 means no target selected, otherwise we
 *          should always have cur_cs >= 0 && cur_cs < nanddev_ntarमाला_लो().
 *          न_अंकD Controller drivers should not modअगरy this value, but they're
 *          allowed to पढ़ो it.
 * @पढ़ो_retries: The number of पढ़ो retry modes supported
 * @secure_regions: Structure containing the secure regions info
 * @nr_secure_regions: Number of secure regions
 * @controller: The hardware controller	काष्ठाure which is shared among multiple
 *              independent devices
 * @ecc: The ECC controller काष्ठाure
 * @priv: Chip निजी data
 */
काष्ठा nand_chip अणु
	काष्ठा nand_device base;
	काष्ठा nand_id id;
	काष्ठा nand_parameters parameters;
	काष्ठा nand_manufacturer manufacturer;
	काष्ठा nand_chip_ops ops;
	काष्ठा nand_legacy legacy;
	अचिन्हित पूर्णांक options;

	/* Data पूर्णांकerface */
	स्थिर काष्ठा nand_पूर्णांकerface_config *current_पूर्णांकerface_config;
	काष्ठा nand_पूर्णांकerface_config *best_पूर्णांकerface_config;

	/* Bad block inक्रमmation */
	अचिन्हित पूर्णांक bbt_erase_shअगरt;
	अचिन्हित पूर्णांक bbt_options;
	अचिन्हित पूर्णांक badblockpos;
	अचिन्हित पूर्णांक badblockbits;
	काष्ठा nand_bbt_descr *bbt_td;
	काष्ठा nand_bbt_descr *bbt_md;
	काष्ठा nand_bbt_descr *badblock_pattern;
	u8 *bbt;

	/* Device पूर्णांकernal layout */
	अचिन्हित पूर्णांक page_shअगरt;
	अचिन्हित पूर्णांक phys_erase_shअगरt;
	अचिन्हित पूर्णांक chip_shअगरt;
	अचिन्हित पूर्णांक pagemask;
	अचिन्हित पूर्णांक subpagesize;

	/* Buffers */
	u8 *data_buf;
	u8 *oob_poi;
	काष्ठा अणु
		अचिन्हित पूर्णांक bitflips;
		पूर्णांक page;
	पूर्ण pagecache;
	अचिन्हित दीर्घ buf_align;

	/* Internals */
	काष्ठा mutex lock;
	अचिन्हित पूर्णांक suspended : 1;
	पूर्णांक cur_cs;
	पूर्णांक पढ़ो_retries;
	काष्ठा nand_secure_region *secure_regions;
	u8 nr_secure_regions;

	/* Externals */
	काष्ठा nand_controller *controller;
	काष्ठा nand_ecc_ctrl ecc;
	व्योम *priv;
पूर्ण;

अटल अंतरभूत काष्ठा nand_chip *mtd_to_nand(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd, काष्ठा nand_chip, base.mtd);
पूर्ण

अटल अंतरभूत काष्ठा mtd_info *nand_to_mtd(काष्ठा nand_chip *chip)
अणु
	वापस &chip->base.mtd;
पूर्ण

अटल अंतरभूत व्योम *nand_get_controller_data(काष्ठा nand_chip *chip)
अणु
	वापस chip->priv;
पूर्ण

अटल अंतरभूत व्योम nand_set_controller_data(काष्ठा nand_chip *chip, व्योम *priv)
अणु
	chip->priv = priv;
पूर्ण

अटल अंतरभूत व्योम nand_set_manufacturer_data(काष्ठा nand_chip *chip,
					      व्योम *priv)
अणु
	chip->manufacturer.priv = priv;
पूर्ण

अटल अंतरभूत व्योम *nand_get_manufacturer_data(काष्ठा nand_chip *chip)
अणु
	वापस chip->manufacturer.priv;
पूर्ण

अटल अंतरभूत व्योम nand_set_flash_node(काष्ठा nand_chip *chip,
				       काष्ठा device_node *np)
अणु
	mtd_set_of_node(nand_to_mtd(chip), np);
पूर्ण

अटल अंतरभूत काष्ठा device_node *nand_get_flash_node(काष्ठा nand_chip *chip)
अणु
	वापस mtd_get_of_node(nand_to_mtd(chip));
पूर्ण

/**
 * nand_get_पूर्णांकerface_config - Retrieve the current पूर्णांकerface configuration
 *                             of a न_अंकD chip
 * @chip: The न_अंकD chip
 */
अटल अंतरभूत स्थिर काष्ठा nand_पूर्णांकerface_config *
nand_get_पूर्णांकerface_config(काष्ठा nand_chip *chip)
अणु
	वापस chip->current_पूर्णांकerface_config;
पूर्ण

/*
 * A helper क्रम defining older न_अंकD chips where the second ID byte fully
 * defined the chip, including the geometry (chip size, eraseblock size, page
 * size). All these chips have 512 bytes न_अंकD page size.
 */
#घोषणा LEGACY_ID_न_अंकD(nm, devid, chipsz, erasesz, opts)          \
	अणु .name = (nm), अणुअणु .dev_id = (devid) पूर्णपूर्ण, .pagesize = 512, \
	  .chipsize = (chipsz), .erasesize = (erasesz), .options = (opts) पूर्ण

/*
 * A helper क्रम defining newer chips which report their page size and
 * eraseblock size via the extended ID bytes.
 *
 * The real dअगरference between LEGACY_ID_न_अंकD and EXTENDED_ID_न_अंकD is that with
 * EXTENDED_ID_न_अंकD, manufacturers overloaded the same device ID so that the
 * device ID now only represented a particular total chip size (and voltage,
 * buswidth), and the page size, eraseblock size, and OOB size could vary जबतक
 * using the same device ID.
 */
#घोषणा EXTENDED_ID_न_अंकD(nm, devid, chipsz, opts)                      \
	अणु .name = (nm), अणुअणु .dev_id = (devid) पूर्णपूर्ण, .chipsize = (chipsz), \
	  .options = (opts) पूर्ण

#घोषणा न_अंकD_ECC_INFO(_strength, _step)	\
			अणु .strength_ds = (_strength), .step_ds = (_step) पूर्ण
#घोषणा न_अंकD_ECC_STRENGTH(type)		((type)->ecc.strength_ds)
#घोषणा न_अंकD_ECC_STEP(type)		((type)->ecc.step_ds)

/**
 * काष्ठा nand_flash_dev - न_अंकD Flash Device ID Structure
 * @name: a human-पढ़ोable name of the न_अंकD chip
 * @dev_id: the device ID (the second byte of the full chip ID array)
 * @mfr_id: manufacturer ID part of the full chip ID array (refers the same
 *          memory address as ``id[0]``)
 * @dev_id: device ID part of the full chip ID array (refers the same memory
 *          address as ``id[1]``)
 * @id: full device ID array
 * @pagesize: size of the न_अंकD page in bytes; अगर 0, then the real page size (as
 *            well as the eraseblock size) is determined from the extended न_अंकD
 *            chip ID array)
 * @chipsize: total chip size in MiB
 * @erasesize: eraseblock size in bytes (determined from the extended ID अगर 0)
 * @options: stores various chip bit options
 * @id_len: The valid length of the @id.
 * @oobsize: OOB size
 * @ecc: ECC correctability and step inक्रमmation from the datasheet.
 * @ecc.strength_ds: The ECC correctability from the datasheet, same as the
 *                   @ecc_strength_ds in nand_chipअणुपूर्ण.
 * @ecc.step_ds: The ECC step required by the @ecc.strength_ds, same as the
 *               @ecc_step_ds in nand_chipअणुपूर्ण, also from the datasheet.
 *               For example, the "4bit ECC for each 512Byte" can be set with
 *               न_अंकD_ECC_INFO(4, 512).
 */
काष्ठा nand_flash_dev अणु
	अक्षर *name;
	जोड़ अणु
		काष्ठा अणु
			uपूर्णांक8_t mfr_id;
			uपूर्णांक8_t dev_id;
		पूर्ण;
		uपूर्णांक8_t id[न_अंकD_MAX_ID_LEN];
	पूर्ण;
	अचिन्हित पूर्णांक pagesize;
	अचिन्हित पूर्णांक chipsize;
	अचिन्हित पूर्णांक erasesize;
	अचिन्हित पूर्णांक options;
	uपूर्णांक16_t id_len;
	uपूर्णांक16_t oobsize;
	काष्ठा अणु
		uपूर्णांक16_t strength_ds;
		uपूर्णांक16_t step_ds;
	पूर्ण ecc;
पूर्ण;

पूर्णांक nand_create_bbt(काष्ठा nand_chip *chip);

/*
 * Check अगर it is a SLC nand.
 * The !nand_is_slc() can be used to check the MLC/TLC nand chips.
 * We करो not distinguish the MLC and TLC now.
 */
अटल अंतरभूत bool nand_is_slc(काष्ठा nand_chip *chip)
अणु
	WARN(nanddev_bits_per_cell(&chip->base) == 0,
	     "chip->bits_per_cell is used uninitialized\n");
	वापस nanddev_bits_per_cell(&chip->base) == 1;
पूर्ण

/**
 * nand_opcode_8bits - Check अगर the opcode's address should be sent only on the
 *	lower 8 bits
 * @command: opcode to check
 */
अटल अंतरभूत पूर्णांक nand_opcode_8bits(अचिन्हित पूर्णांक command)
अणु
	चयन (command) अणु
	हाल न_अंकD_CMD_READID:
	हाल न_अंकD_CMD_PARAM:
	हाल न_अंकD_CMD_GET_FEATURES:
	हाल न_अंकD_CMD_SET_FEATURES:
		वापस 1;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक rawnand_sw_hamming_init(काष्ठा nand_chip *chip);
पूर्णांक rawnand_sw_hamming_calculate(काष्ठा nand_chip *chip,
				 स्थिर अचिन्हित अक्षर *buf,
				 अचिन्हित अक्षर *code);
पूर्णांक rawnand_sw_hamming_correct(काष्ठा nand_chip *chip,
			       अचिन्हित अक्षर *buf,
			       अचिन्हित अक्षर *पढ़ो_ecc,
			       अचिन्हित अक्षर *calc_ecc);
व्योम rawnand_sw_hamming_cleanup(काष्ठा nand_chip *chip);
पूर्णांक rawnand_sw_bch_init(काष्ठा nand_chip *chip);
पूर्णांक rawnand_sw_bch_correct(काष्ठा nand_chip *chip, अचिन्हित अक्षर *buf,
			   अचिन्हित अक्षर *पढ़ो_ecc, अचिन्हित अक्षर *calc_ecc);
व्योम rawnand_sw_bch_cleanup(काष्ठा nand_chip *chip);

पूर्णांक nand_check_erased_ecc_chunk(व्योम *data, पूर्णांक datalen,
				व्योम *ecc, पूर्णांक ecclen,
				व्योम *extraoob, पूर्णांक extraooblen,
				पूर्णांक threshold);

पूर्णांक nand_ecc_choose_conf(काष्ठा nand_chip *chip,
			 स्थिर काष्ठा nand_ecc_caps *caps, पूर्णांक oobavail);

/* Default ग_लिखो_oob implementation */
पूर्णांक nand_ग_लिखो_oob_std(काष्ठा nand_chip *chip, पूर्णांक page);

/* Default पढ़ो_oob implementation */
पूर्णांक nand_पढ़ो_oob_std(काष्ठा nand_chip *chip, पूर्णांक page);

/* Stub used by drivers that करो not support GET/SET FEATURES operations */
पूर्णांक nand_get_set_features_notsupp(काष्ठा nand_chip *chip, पूर्णांक addr,
				  u8 *subfeature_param);

/* पढ़ो_page_raw implementations */
पूर्णांक nand_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf, पूर्णांक oob_required,
		       पूर्णांक page);
पूर्णांक nand_monolithic_पढ़ो_page_raw(काष्ठा nand_chip *chip, uपूर्णांक8_t *buf,
				  पूर्णांक oob_required, पूर्णांक page);

/* ग_लिखो_page_raw implementations */
पूर्णांक nand_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
			पूर्णांक oob_required, पूर्णांक page);
पूर्णांक nand_monolithic_ग_लिखो_page_raw(काष्ठा nand_chip *chip, स्थिर uपूर्णांक8_t *buf,
				   पूर्णांक oob_required, पूर्णांक page);

/* Reset and initialize a न_अंकD device */
पूर्णांक nand_reset(काष्ठा nand_chip *chip, पूर्णांक chipnr);

/* न_अंकD operation helpers */
पूर्णांक nand_reset_op(काष्ठा nand_chip *chip);
पूर्णांक nand_पढ़ोid_op(काष्ठा nand_chip *chip, u8 addr, व्योम *buf,
		   अचिन्हित पूर्णांक len);
पूर्णांक nand_status_op(काष्ठा nand_chip *chip, u8 *status);
पूर्णांक nand_erase_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक eraseblock);
पूर्णांक nand_पढ़ो_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
		      अचिन्हित पूर्णांक offset_in_page, व्योम *buf, अचिन्हित पूर्णांक len);
पूर्णांक nand_change_पढ़ो_column_op(काष्ठा nand_chip *chip,
			       अचिन्हित पूर्णांक offset_in_page, व्योम *buf,
			       अचिन्हित पूर्णांक len, bool क्रमce_8bit);
पूर्णांक nand_पढ़ो_oob_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
		     अचिन्हित पूर्णांक offset_in_page, व्योम *buf, अचिन्हित पूर्णांक len);
पूर्णांक nand_prog_page_begin_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
			    अचिन्हित पूर्णांक offset_in_page, स्थिर व्योम *buf,
			    अचिन्हित पूर्णांक len);
पूर्णांक nand_prog_page_end_op(काष्ठा nand_chip *chip);
पूर्णांक nand_prog_page_op(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक page,
		      अचिन्हित पूर्णांक offset_in_page, स्थिर व्योम *buf,
		      अचिन्हित पूर्णांक len);
पूर्णांक nand_change_ग_लिखो_column_op(काष्ठा nand_chip *chip,
				अचिन्हित पूर्णांक offset_in_page, स्थिर व्योम *buf,
				अचिन्हित पूर्णांक len, bool क्रमce_8bit);
पूर्णांक nand_पढ़ो_data_op(काष्ठा nand_chip *chip, व्योम *buf, अचिन्हित पूर्णांक len,
		      bool क्रमce_8bit, bool check_only);
पूर्णांक nand_ग_लिखो_data_op(काष्ठा nand_chip *chip, स्थिर व्योम *buf,
		       अचिन्हित पूर्णांक len, bool क्रमce_8bit);

/* Scan and identअगरy a न_अंकD device */
पूर्णांक nand_scan_with_ids(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक max_chips,
		       काष्ठा nand_flash_dev *ids);

अटल अंतरभूत पूर्णांक nand_scan(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक max_chips)
अणु
	वापस nand_scan_with_ids(chip, max_chips, शून्य);
पूर्ण

/* Internal helper क्रम board drivers which need to override command function */
व्योम nand_रुको_पढ़ोy(काष्ठा nand_chip *chip);

/*
 * Free resources held by the न_अंकD device, must be called on error after a
 * sucessful nand_scan().
 */
व्योम nand_cleanup(काष्ठा nand_chip *chip);

/*
 * External helper क्रम controller drivers that have to implement the WAITRDY
 * inकाष्ठाion and have no physical pin to check it.
 */
पूर्णांक nand_soft_रुकोrdy(काष्ठा nand_chip *chip, अचिन्हित दीर्घ समयout_ms);
काष्ठा gpio_desc;
पूर्णांक nand_gpio_रुकोrdy(काष्ठा nand_chip *chip, काष्ठा gpio_desc *gpiod,
		      अचिन्हित दीर्घ समयout_ms);

/* Select/deselect a न_अंकD target. */
व्योम nand_select_target(काष्ठा nand_chip *chip, अचिन्हित पूर्णांक cs);
व्योम nand_deselect_target(काष्ठा nand_chip *chip);

/* Bitops */
व्योम nand_extract_bits(u8 *dst, अचिन्हित पूर्णांक dst_off, स्थिर u8 *src,
		       अचिन्हित पूर्णांक src_off, अचिन्हित पूर्णांक nbits);

/**
 * nand_get_data_buf() - Get the पूर्णांकernal page buffer
 * @chip: न_अंकD chip object
 *
 * Returns the pre-allocated page buffer after invalidating the cache. This
 * function should be used by drivers that करो not want to allocate their own
 * bounce buffer and still need such a buffer क्रम specअगरic operations (most
 * commonly when पढ़ोing OOB data only).
 *
 * Be careful to never call this function in the ग_लिखो/ग_लिखो_oob path, because
 * the core may have placed the data to be written out in this buffer.
 *
 * Return: poपूर्णांकer to the page cache buffer
 */
अटल अंतरभूत व्योम *nand_get_data_buf(काष्ठा nand_chip *chip)
अणु
	chip->pagecache.page = -1;

	वापस chip->data_buf;
पूर्ण

#पूर्ण_अगर /* __LINUX_MTD_RAWन_अंकD_H */
