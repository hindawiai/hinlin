<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright 2017 - Free Electrons
 *
 *  Authors:
 *	Boris Brezillon <boris.brezillon@मुक्त-electrons.com>
 *	Peter Pan <peterpanकरोng@micron.com>
 */

#अगर_अघोषित __LINUX_MTD_न_अंकD_H
#घोषणा __LINUX_MTD_न_अंकD_H

#समावेश <linux/mtd/mtd.h>

काष्ठा nand_device;

/**
 * काष्ठा nand_memory_organization - Memory organization काष्ठाure
 * @bits_per_cell: number of bits per न_अंकD cell
 * @pagesize: page size
 * @oobsize: OOB area size
 * @pages_per_eraseblock: number of pages per eraseblock
 * @eraseblocks_per_lun: number of eraseblocks per LUN (Logical Unit Number)
 * @max_bad_eraseblocks_per_lun: maximum number of eraseblocks per LUN
 * @planes_per_lun: number of planes per LUN
 * @luns_per_target: number of LUN per target (target is a synonym क्रम die)
 * @ntarमाला_लो: total number of tarमाला_लो exposed by the न_अंकD device
 */
काष्ठा nand_memory_organization अणु
	अचिन्हित पूर्णांक bits_per_cell;
	अचिन्हित पूर्णांक pagesize;
	अचिन्हित पूर्णांक oobsize;
	अचिन्हित पूर्णांक pages_per_eraseblock;
	अचिन्हित पूर्णांक eraseblocks_per_lun;
	अचिन्हित पूर्णांक max_bad_eraseblocks_per_lun;
	अचिन्हित पूर्णांक planes_per_lun;
	अचिन्हित पूर्णांक luns_per_target;
	अचिन्हित पूर्णांक ntarमाला_लो;
पूर्ण;

#घोषणा न_अंकD_MEMORG(bpc, ps, os, ppe, epl, mbb, ppl, lpt, nt)	\
	अणु							\
		.bits_per_cell = (bpc),				\
		.pagesize = (ps),				\
		.oobsize = (os),				\
		.pages_per_eraseblock = (ppe),			\
		.eraseblocks_per_lun = (epl),			\
		.max_bad_eraseblocks_per_lun = (mbb),		\
		.planes_per_lun = (ppl),			\
		.luns_per_target = (lpt),			\
		.ntarमाला_लो = (nt),				\
	पूर्ण

/**
 * काष्ठा nand_row_converter - Inक्रमmation needed to convert an असलolute offset
 *			       पूर्णांकo a row address
 * @lun_addr_shअगरt: position of the LUN identअगरier in the row address
 * @eraseblock_addr_shअगरt: position of the eraseblock identअगरier in the row
 *			   address
 */
काष्ठा nand_row_converter अणु
	अचिन्हित पूर्णांक lun_addr_shअगरt;
	अचिन्हित पूर्णांक eraseblock_addr_shअगरt;
पूर्ण;

/**
 * काष्ठा nand_pos - न_अंकD position object
 * @target: the न_अंकD target/die
 * @lun: the LUN identअगरier
 * @plane: the plane within the LUN
 * @eraseblock: the eraseblock within the LUN
 * @page: the page within the LUN
 *
 * These inक्रमmation are usually used by specअगरic sub-layers to select the
 * appropriate target/die and generate a row address to pass to the device.
 */
काष्ठा nand_pos अणु
	अचिन्हित पूर्णांक target;
	अचिन्हित पूर्णांक lun;
	अचिन्हित पूर्णांक plane;
	अचिन्हित पूर्णांक eraseblock;
	अचिन्हित पूर्णांक page;
पूर्ण;

/**
 * क्रमागत nand_page_io_req_type - Direction of an I/O request
 * @न_अंकD_PAGE_READ: from the chip, to the controller
 * @न_अंकD_PAGE_WRITE: from the controller, to the chip
 */
क्रमागत nand_page_io_req_type अणु
	न_अंकD_PAGE_READ = 0,
	न_अंकD_PAGE_WRITE,
पूर्ण;

/**
 * काष्ठा nand_page_io_req - न_अंकD I/O request object
 * @type: the type of page I/O: पढ़ो or ग_लिखो
 * @pos: the position this I/O request is targeting
 * @dataoffs: the offset within the page
 * @datalen: number of data bytes to पढ़ो from/ग_लिखो to this page
 * @databuf: buffer to store data in or get data from
 * @ooboffs: the OOB offset within the page
 * @ooblen: the number of OOB bytes to पढ़ो from/ग_लिखो to this page
 * @oobbuf: buffer to store OOB data in or get OOB data from
 * @mode: one of the %MTD_OPS_XXX mode
 *
 * This object is used to pass per-page I/O requests to न_अंकD sub-layers. This
 * way all useful inक्रमmation are alपढ़ोy क्रमmatted in a useful way and
 * specअगरic न_अंकD layers can focus on translating these inक्रमmation पूर्णांकo
 * specअगरic commands/operations.
 */
काष्ठा nand_page_io_req अणु
	क्रमागत nand_page_io_req_type type;
	काष्ठा nand_pos pos;
	अचिन्हित पूर्णांक dataoffs;
	अचिन्हित पूर्णांक datalen;
	जोड़ अणु
		स्थिर व्योम *out;
		व्योम *in;
	पूर्ण databuf;
	अचिन्हित पूर्णांक ooboffs;
	अचिन्हित पूर्णांक ooblen;
	जोड़ अणु
		स्थिर व्योम *out;
		व्योम *in;
	पूर्ण oobbuf;
	पूर्णांक mode;
पूर्ण;

स्थिर काष्ठा mtd_ooblayout_ops *nand_get_small_page_ooblayout(व्योम);
स्थिर काष्ठा mtd_ooblayout_ops *nand_get_large_page_ooblayout(व्योम);
स्थिर काष्ठा mtd_ooblayout_ops *nand_get_large_page_hamming_ooblayout(व्योम);

/**
 * क्रमागत nand_ecc_engine_type - न_अंकD ECC engine type
 * @न_अंकD_ECC_ENGINE_TYPE_INVALID: Invalid value
 * @न_अंकD_ECC_ENGINE_TYPE_NONE: No ECC correction
 * @न_अंकD_ECC_ENGINE_TYPE_SOFT: Software ECC correction
 * @न_अंकD_ECC_ENGINE_TYPE_ON_HOST: On host hardware ECC correction
 * @न_अंकD_ECC_ENGINE_TYPE_ON_DIE: On chip hardware ECC correction
 */
क्रमागत nand_ecc_engine_type अणु
	न_अंकD_ECC_ENGINE_TYPE_INVALID,
	न_अंकD_ECC_ENGINE_TYPE_NONE,
	न_अंकD_ECC_ENGINE_TYPE_SOFT,
	न_अंकD_ECC_ENGINE_TYPE_ON_HOST,
	न_अंकD_ECC_ENGINE_TYPE_ON_DIE,
पूर्ण;

/**
 * क्रमागत nand_ecc_placement - न_अंकD ECC bytes placement
 * @न_अंकD_ECC_PLACEMENT_UNKNOWN: The actual position of the ECC bytes is unknown
 * @न_अंकD_ECC_PLACEMENT_OOB: The ECC bytes are located in the OOB area
 * @न_अंकD_ECC_PLACEMENT_INTERLEAVED: Syndrome layout, there are ECC bytes
 *                                  पूर्णांकerleaved with regular data in the मुख्य
 *                                  area
 */
क्रमागत nand_ecc_placement अणु
	न_अंकD_ECC_PLACEMENT_UNKNOWN,
	न_अंकD_ECC_PLACEMENT_OOB,
	न_अंकD_ECC_PLACEMENT_INTERLEAVED,
पूर्ण;

/**
 * क्रमागत nand_ecc_algo - न_अंकD ECC algorithm
 * @न_अंकD_ECC_ALGO_UNKNOWN: Unknown algorithm
 * @न_अंकD_ECC_ALGO_HAMMING: Hamming algorithm
 * @न_अंकD_ECC_ALGO_BCH: Bose-Chaudhuri-Hocquenghem algorithm
 * @न_अंकD_ECC_ALGO_RS: Reed-Solomon algorithm
 */
क्रमागत nand_ecc_algo अणु
	न_अंकD_ECC_ALGO_UNKNOWN,
	न_अंकD_ECC_ALGO_HAMMING,
	न_अंकD_ECC_ALGO_BCH,
	न_अंकD_ECC_ALGO_RS,
पूर्ण;

/**
 * काष्ठा nand_ecc_props - न_अंकD ECC properties
 * @engine_type: ECC engine type
 * @placement: OOB placement (अगर relevant)
 * @algo: ECC algorithm (अगर relevant)
 * @strength: ECC strength
 * @step_size: Number of bytes per step
 * @flags: Misc properties
 */
काष्ठा nand_ecc_props अणु
	क्रमागत nand_ecc_engine_type engine_type;
	क्रमागत nand_ecc_placement placement;
	क्रमागत nand_ecc_algo algo;
	अचिन्हित पूर्णांक strength;
	अचिन्हित पूर्णांक step_size;
	अचिन्हित पूर्णांक flags;
पूर्ण;

#घोषणा न_अंकD_ECCREQ(str, stp) अणु .strength = (str), .step_size = (stp) पूर्ण

/* न_अंकD ECC misc flags */
#घोषणा न_अंकD_ECC_MAXIMIZE_STRENGTH BIT(0)

/**
 * काष्ठा nand_bbt - bad block table object
 * @cache: in memory BBT cache
 */
काष्ठा nand_bbt अणु
	अचिन्हित दीर्घ *cache;
पूर्ण;

/**
 * काष्ठा nand_ops - न_अंकD operations
 * @erase: erase a specअगरic block. No need to check अगर the block is bad beक्रमe
 *	   erasing, this has been taken care of by the generic न_अंकD layer
 * @markbad: mark a specअगरic block bad. No need to check अगर the block is
 *	     alपढ़ोy marked bad, this has been taken care of by the generic
 *	     न_अंकD layer. This method should just ग_लिखो the BBM (Bad Block
 *	     Marker) so that future call to काष्ठा_nand_ops->isbad() वापस
 *	     true
 * @isbad: check whether a block is bad or not. This method should just पढ़ो
 *	   the BBM and वापस whether the block is bad or not based on what it
 *	   पढ़ोs
 *
 * These are all low level operations that should be implemented by specialized
 * न_अंकD layers (SPI न_अंकD, raw न_अंकD, ...).
 */
काष्ठा nand_ops अणु
	पूर्णांक (*erase)(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);
	पूर्णांक (*markbad)(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);
	bool (*isbad)(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);
पूर्ण;

/**
 * काष्ठा nand_ecc_context - Context क्रम the ECC engine
 * @conf: basic ECC engine parameters
 * @nsteps: number of ECC steps
 * @total: total number of bytes used क्रम storing ECC codes, this is used by
 *         generic OOB layouts
 * @priv: ECC engine driver निजी data
 */
काष्ठा nand_ecc_context अणु
	काष्ठा nand_ecc_props conf;
	अचिन्हित पूर्णांक nsteps;
	अचिन्हित पूर्णांक total;
	व्योम *priv;
पूर्ण;

/**
 * काष्ठा nand_ecc_engine_ops - ECC engine operations
 * @init_ctx: given a desired user configuration क्रम the poपूर्णांकed न_अंकD device,
 *            requests the ECC engine driver to setup a configuration with
 *            values it supports.
 * @cleanup_ctx: clean the context initialized by @init_ctx.
 * @prepare_io_req: is called beक्रमe पढ़ोing/writing a page to prepare the I/O
 *                  request to be perक्रमmed with ECC correction.
 * @finish_io_req: is called after पढ़ोing/writing a page to terminate the I/O
 *                 request and ensure proper ECC correction.
 */
काष्ठा nand_ecc_engine_ops अणु
	पूर्णांक (*init_ctx)(काष्ठा nand_device *nand);
	व्योम (*cleanup_ctx)(काष्ठा nand_device *nand);
	पूर्णांक (*prepare_io_req)(काष्ठा nand_device *nand,
			      काष्ठा nand_page_io_req *req);
	पूर्णांक (*finish_io_req)(काष्ठा nand_device *nand,
			     काष्ठा nand_page_io_req *req);
पूर्ण;

/**
 * काष्ठा nand_ecc_engine - ECC engine असलtraction क्रम न_अंकD devices
 * @ops: ECC engine operations
 */
काष्ठा nand_ecc_engine अणु
	काष्ठा nand_ecc_engine_ops *ops;
पूर्ण;

व्योम of_get_nand_ecc_user_config(काष्ठा nand_device *nand);
पूर्णांक nand_ecc_init_ctx(काष्ठा nand_device *nand);
व्योम nand_ecc_cleanup_ctx(काष्ठा nand_device *nand);
पूर्णांक nand_ecc_prepare_io_req(काष्ठा nand_device *nand,
			    काष्ठा nand_page_io_req *req);
पूर्णांक nand_ecc_finish_io_req(काष्ठा nand_device *nand,
			   काष्ठा nand_page_io_req *req);
bool nand_ecc_is_strong_enough(काष्ठा nand_device *nand);
काष्ठा nand_ecc_engine *nand_ecc_get_sw_engine(काष्ठा nand_device *nand);
काष्ठा nand_ecc_engine *nand_ecc_get_on_die_hw_engine(काष्ठा nand_device *nand);

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING)
काष्ठा nand_ecc_engine *nand_ecc_sw_hamming_get_engine(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा nand_ecc_engine *nand_ecc_sw_hamming_get_engine(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_MTD_न_अंकD_ECC_SW_HAMMING */

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_BCH)
काष्ठा nand_ecc_engine *nand_ecc_sw_bch_get_engine(व्योम);
#अन्यथा
अटल अंतरभूत काष्ठा nand_ecc_engine *nand_ecc_sw_bch_get_engine(व्योम)
अणु
	वापस शून्य;
पूर्ण
#पूर्ण_अगर /* CONFIG_MTD_न_अंकD_ECC_SW_BCH */

/**
 * काष्ठा nand_ecc_req_tweak_ctx - Help क्रम स्वतःmatically tweaking requests
 * @orig_req: Poपूर्णांकer to the original IO request
 * @nand: Related न_अंकD device, to have access to its memory organization
 * @page_buffer_size: Real size of the page buffer to use (can be set by the
 *                    user beक्रमe the tweaking mechanism initialization)
 * @oob_buffer_size: Real size of the OOB buffer to use (can be set by the
 *                   user beक्रमe the tweaking mechanism initialization)
 * @spare_databuf: Data bounce buffer
 * @spare_oobbuf: OOB bounce buffer
 * @bounce_data: Flag indicating a data bounce buffer is used
 * @bounce_oob: Flag indicating an OOB bounce buffer is used
 */
काष्ठा nand_ecc_req_tweak_ctx अणु
	काष्ठा nand_page_io_req orig_req;
	काष्ठा nand_device *nand;
	अचिन्हित पूर्णांक page_buffer_size;
	अचिन्हित पूर्णांक oob_buffer_size;
	व्योम *spare_databuf;
	व्योम *spare_oobbuf;
	bool bounce_data;
	bool bounce_oob;
पूर्ण;

पूर्णांक nand_ecc_init_req_tweaking(काष्ठा nand_ecc_req_tweak_ctx *ctx,
			       काष्ठा nand_device *nand);
व्योम nand_ecc_cleanup_req_tweaking(काष्ठा nand_ecc_req_tweak_ctx *ctx);
व्योम nand_ecc_tweak_req(काष्ठा nand_ecc_req_tweak_ctx *ctx,
			काष्ठा nand_page_io_req *req);
व्योम nand_ecc_restore_req(काष्ठा nand_ecc_req_tweak_ctx *ctx,
			  काष्ठा nand_page_io_req *req);

/**
 * काष्ठा nand_ecc - Inक्रमmation relative to the ECC
 * @शेषs: Default values, depend on the underlying subप्रणाली
 * @requirements: ECC requirements from the न_अंकD chip perspective
 * @user_conf: User desires in terms of ECC parameters
 * @ctx: ECC context क्रम the ECC engine, derived from the device @requirements
 *       the @user_conf and the @शेषs
 * @ondie_engine: On-die ECC engine reference, अगर any
 * @engine: ECC engine actually bound
 */
काष्ठा nand_ecc अणु
	काष्ठा nand_ecc_props शेषs;
	काष्ठा nand_ecc_props requirements;
	काष्ठा nand_ecc_props user_conf;
	काष्ठा nand_ecc_context ctx;
	काष्ठा nand_ecc_engine *ondie_engine;
	काष्ठा nand_ecc_engine *engine;
पूर्ण;

/**
 * काष्ठा nand_device - न_अंकD device
 * @mtd: MTD instance attached to the न_अंकD device
 * @memorg: memory layout
 * @ecc: न_अंकD ECC object attached to the न_अंकD device
 * @rowconv: position to row address converter
 * @bbt: bad block table info
 * @ops: न_अंकD operations attached to the न_अंकD device
 *
 * Generic न_अंकD object. Specialized न_अंकD layers (raw न_अंकD, SPI न_अंकD, Oneन_अंकD)
 * should declare their own न_अंकD object embedding a nand_device काष्ठा (that's
 * how inheritance is करोne).
 * काष्ठा_nand_device->memorg and काष्ठा_nand_device->ecc.requirements should
 * be filled at device detection समय to reflect the न_अंकD device
 * capabilities/requirements. Once this is करोne nanddev_init() can be called.
 * It will take care of converting न_अंकD inक्रमmation पूर्णांकo MTD ones, which means
 * the specialized न_अंकD layers should never manually tweak
 * काष्ठा_nand_device->mtd except क्रम the ->_पढ़ो/ग_लिखो() hooks.
 */
काष्ठा nand_device अणु
	काष्ठा mtd_info mtd;
	काष्ठा nand_memory_organization memorg;
	काष्ठा nand_ecc ecc;
	काष्ठा nand_row_converter rowconv;
	काष्ठा nand_bbt bbt;
	स्थिर काष्ठा nand_ops *ops;
पूर्ण;

/**
 * काष्ठा nand_io_iter - न_अंकD I/O iterator
 * @req: current I/O request
 * @oobbytes_per_page: maximum number of OOB bytes per page
 * @dataleft: reमुख्यing number of data bytes to पढ़ो/ग_लिखो
 * @oobleft: reमुख्यing number of OOB bytes to पढ़ो/ग_लिखो
 *
 * Can be used by specialized न_अंकD layers to iterate over all pages covered
 * by an MTD I/O request, which should greatly simplअगरies the boiler-plate
 * code needed to पढ़ो/ग_लिखो data from/to a न_अंकD device.
 */
काष्ठा nand_io_iter अणु
	काष्ठा nand_page_io_req req;
	अचिन्हित पूर्णांक oobbytes_per_page;
	अचिन्हित पूर्णांक dataleft;
	अचिन्हित पूर्णांक oobleft;
पूर्ण;

/**
 * mtd_to_nanddev() - Get the न_अंकD device attached to the MTD instance
 * @mtd: MTD instance
 *
 * Return: the न_अंकD device embedding @mtd.
 */
अटल अंतरभूत काष्ठा nand_device *mtd_to_nanddev(काष्ठा mtd_info *mtd)
अणु
	वापस container_of(mtd, काष्ठा nand_device, mtd);
पूर्ण

/**
 * nanddev_to_mtd() - Get the MTD device attached to a न_अंकD device
 * @nand: न_अंकD device
 *
 * Return: the MTD device embedded in @nand.
 */
अटल अंतरभूत काष्ठा mtd_info *nanddev_to_mtd(काष्ठा nand_device *nand)
अणु
	वापस &nand->mtd;
पूर्ण

/*
 * nanddev_bits_per_cell() - Get the number of bits per cell
 * @nand: न_अंकD device
 *
 * Return: the number of bits per cell.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nanddev_bits_per_cell(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.bits_per_cell;
पूर्ण

/**
 * nanddev_page_size() - Get न_अंकD page size
 * @nand: न_अंकD device
 *
 * Return: the page size.
 */
अटल अंतरभूत माप_प्रकार nanddev_page_size(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.pagesize;
पूर्ण

/**
 * nanddev_per_page_oobsize() - Get न_अंकD OOB size
 * @nand: न_अंकD device
 *
 * Return: the OOB size.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_per_page_oobsize(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.oobsize;
पूर्ण

/**
 * nanddev_pages_per_eraseblock() - Get the number of pages per eraseblock
 * @nand: न_अंकD device
 *
 * Return: the number of pages per eraseblock.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_pages_per_eraseblock(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.pages_per_eraseblock;
पूर्ण

/**
 * nanddev_pages_per_target() - Get the number of pages per target
 * @nand: न_अंकD device
 *
 * Return: the number of pages per target.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_pages_per_target(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.pages_per_eraseblock *
	       nand->memorg.eraseblocks_per_lun *
	       nand->memorg.luns_per_target;
पूर्ण

/**
 * nanddev_per_page_oobsize() - Get न_अंकD erase block size
 * @nand: न_अंकD device
 *
 * Return: the eraseblock size.
 */
अटल अंतरभूत माप_प्रकार nanddev_eraseblock_size(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.pagesize * nand->memorg.pages_per_eraseblock;
पूर्ण

/**
 * nanddev_eraseblocks_per_lun() - Get the number of eraseblocks per LUN
 * @nand: न_अंकD device
 *
 * Return: the number of eraseblocks per LUN.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_eraseblocks_per_lun(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.eraseblocks_per_lun;
पूर्ण

/**
 * nanddev_eraseblocks_per_target() - Get the number of eraseblocks per target
 * @nand: न_अंकD device
 *
 * Return: the number of eraseblocks per target.
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_eraseblocks_per_target(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.eraseblocks_per_lun * nand->memorg.luns_per_target;
पूर्ण

/**
 * nanddev_target_size() - Get the total size provided by a single target/die
 * @nand: न_अंकD device
 *
 * Return: the total size exposed by a single target/die in bytes.
 */
अटल अंतरभूत u64 nanddev_target_size(स्थिर काष्ठा nand_device *nand)
अणु
	वापस (u64)nand->memorg.luns_per_target *
	       nand->memorg.eraseblocks_per_lun *
	       nand->memorg.pages_per_eraseblock *
	       nand->memorg.pagesize;
पूर्ण

/**
 * nanddev_ntarget() - Get the total of tarमाला_लो
 * @nand: न_अंकD device
 *
 * Return: the number of tarमाला_लो/dies exposed by @nand.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nanddev_ntarमाला_लो(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.ntarमाला_लो;
पूर्ण

/**
 * nanddev_neraseblocks() - Get the total number of eraseblocks
 * @nand: न_अंकD device
 *
 * Return: the total number of eraseblocks exposed by @nand.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nanddev_neraseblocks(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nand->memorg.ntarमाला_लो * nand->memorg.luns_per_target *
	       nand->memorg.eraseblocks_per_lun;
पूर्ण

/**
 * nanddev_size() - Get न_अंकD size
 * @nand: न_अंकD device
 *
 * Return: the total size (in bytes) exposed by @nand.
 */
अटल अंतरभूत u64 nanddev_size(स्थिर काष्ठा nand_device *nand)
अणु
	वापस nanddev_target_size(nand) * nanddev_ntarमाला_लो(nand);
पूर्ण

/**
 * nanddev_get_memorg() - Extract memory organization info from a न_अंकD device
 * @nand: न_अंकD device
 *
 * This can be used by the upper layer to fill the memorg info beक्रमe calling
 * nanddev_init().
 *
 * Return: the memorg object embedded in the न_अंकD device.
 */
अटल अंतरभूत काष्ठा nand_memory_organization *
nanddev_get_memorg(काष्ठा nand_device *nand)
अणु
	वापस &nand->memorg;
पूर्ण

/**
 * nanddev_get_ecc_conf() - Extract the ECC configuration from a न_अंकD device
 * @nand: न_अंकD device
 */
अटल अंतरभूत स्थिर काष्ठा nand_ecc_props *
nanddev_get_ecc_conf(काष्ठा nand_device *nand)
अणु
	वापस &nand->ecc.ctx.conf;
पूर्ण

/**
 * nanddev_get_ecc_nsteps() - Extract the number of ECC steps
 * @nand: न_अंकD device
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_get_ecc_nsteps(काष्ठा nand_device *nand)
अणु
	वापस nand->ecc.ctx.nsteps;
पूर्ण

/**
 * nanddev_get_ecc_bytes_per_step() - Extract the number of ECC bytes per step
 * @nand: न_अंकD device
 */
अटल अंतरभूत अचिन्हित पूर्णांक
nanddev_get_ecc_bytes_per_step(काष्ठा nand_device *nand)
अणु
	वापस nand->ecc.ctx.total / nand->ecc.ctx.nsteps;
पूर्ण

/**
 * nanddev_get_ecc_requirements() - Extract the ECC requirements from a न_अंकD
 *                                  device
 * @nand: न_अंकD device
 */
अटल अंतरभूत स्थिर काष्ठा nand_ecc_props *
nanddev_get_ecc_requirements(काष्ठा nand_device *nand)
अणु
	वापस &nand->ecc.requirements;
पूर्ण

/**
 * nanddev_set_ecc_requirements() - Assign the ECC requirements of a न_अंकD
 *                                  device
 * @nand: न_अंकD device
 * @reqs: Requirements
 */
अटल अंतरभूत व्योम
nanddev_set_ecc_requirements(काष्ठा nand_device *nand,
			     स्थिर काष्ठा nand_ecc_props *reqs)
अणु
	nand->ecc.requirements = *reqs;
पूर्ण

पूर्णांक nanddev_init(काष्ठा nand_device *nand, स्थिर काष्ठा nand_ops *ops,
		 काष्ठा module *owner);
व्योम nanddev_cleanup(काष्ठा nand_device *nand);

/**
 * nanddev_रेजिस्टर() - Register a न_अंकD device
 * @nand: न_अंकD device
 *
 * Register a न_अंकD device.
 * This function is just a wrapper around mtd_device_रेजिस्टर()
 * रेजिस्टरing the MTD device embedded in @nand.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
अटल अंतरभूत पूर्णांक nanddev_रेजिस्टर(काष्ठा nand_device *nand)
अणु
	वापस mtd_device_रेजिस्टर(&nand->mtd, शून्य, 0);
पूर्ण

/**
 * nanddev_unरेजिस्टर() - Unरेजिस्टर a न_अंकD device
 * @nand: न_अंकD device
 *
 * Unरेजिस्टर a न_अंकD device.
 * This function is just a wrapper around mtd_device_unरेजिस्टर()
 * unरेजिस्टरing the MTD device embedded in @nand.
 *
 * Return: 0 in हाल of success, a negative error code otherwise.
 */
अटल अंतरभूत पूर्णांक nanddev_unरेजिस्टर(काष्ठा nand_device *nand)
अणु
	वापस mtd_device_unरेजिस्टर(&nand->mtd);
पूर्ण

/**
 * nanddev_set_of_node() - Attach a DT node to a न_अंकD device
 * @nand: न_अंकD device
 * @np: DT node
 *
 * Attach a DT node to a न_अंकD device.
 */
अटल अंतरभूत व्योम nanddev_set_of_node(काष्ठा nand_device *nand,
				       काष्ठा device_node *np)
अणु
	mtd_set_of_node(&nand->mtd, np);
पूर्ण

/**
 * nanddev_get_of_node() - Retrieve the DT node attached to a न_अंकD device
 * @nand: न_अंकD device
 *
 * Return: the DT node attached to @nand.
 */
अटल अंतरभूत काष्ठा device_node *nanddev_get_of_node(काष्ठा nand_device *nand)
अणु
	वापस mtd_get_of_node(&nand->mtd);
पूर्ण

/**
 * nanddev_offs_to_pos() - Convert an असलolute न_अंकD offset पूर्णांकo a न_अंकD position
 * @nand: न_अंकD device
 * @offs: असलolute न_अंकD offset (usually passed by the MTD layer)
 * @pos: a न_अंकD position object to fill in
 *
 * Converts @offs पूर्णांकo a nand_pos representation.
 *
 * Return: the offset within the न_अंकD page poपूर्णांकed by @pos.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nanddev_offs_to_pos(काष्ठा nand_device *nand,
					       loff_t offs,
					       काष्ठा nand_pos *pos)
अणु
	अचिन्हित पूर्णांक pageoffs;
	u64 पंचांगp = offs;

	pageoffs = करो_भाग(पंचांगp, nand->memorg.pagesize);
	pos->page = करो_भाग(पंचांगp, nand->memorg.pages_per_eraseblock);
	pos->eraseblock = करो_भाग(पंचांगp, nand->memorg.eraseblocks_per_lun);
	pos->plane = pos->eraseblock % nand->memorg.planes_per_lun;
	pos->lun = करो_भाग(पंचांगp, nand->memorg.luns_per_target);
	pos->target = पंचांगp;

	वापस pageoffs;
पूर्ण

/**
 * nanddev_pos_cmp() - Compare two न_अंकD positions
 * @a: First न_अंकD position
 * @b: Second न_अंकD position
 *
 * Compares two न_अंकD positions.
 *
 * Return: -1 अगर @a < @b, 0 अगर @a == @b and 1 अगर @a > @b.
 */
अटल अंतरभूत पूर्णांक nanddev_pos_cmp(स्थिर काष्ठा nand_pos *a,
				  स्थिर काष्ठा nand_pos *b)
अणु
	अगर (a->target != b->target)
		वापस a->target < b->target ? -1 : 1;

	अगर (a->lun != b->lun)
		वापस a->lun < b->lun ? -1 : 1;

	अगर (a->eraseblock != b->eraseblock)
		वापस a->eraseblock < b->eraseblock ? -1 : 1;

	अगर (a->page != b->page)
		वापस a->page < b->page ? -1 : 1;

	वापस 0;
पूर्ण

/**
 * nanddev_pos_to_offs() - Convert a न_अंकD position पूर्णांकo an असलolute offset
 * @nand: न_अंकD device
 * @pos: the न_अंकD position to convert
 *
 * Converts @pos न_अंकD position पूर्णांकo an असलolute offset.
 *
 * Return: the असलolute offset. Note that @pos poपूर्णांकs to the beginning of a
 *	   page, अगर one wants to poपूर्णांक to a specअगरic offset within this page
 *	   the वापसed offset has to be adjusted manually.
 */
अटल अंतरभूत loff_t nanddev_pos_to_offs(काष्ठा nand_device *nand,
					 स्थिर काष्ठा nand_pos *pos)
अणु
	अचिन्हित पूर्णांक npages;

	npages = pos->page +
		 ((pos->eraseblock +
		   (pos->lun +
		    (pos->target * nand->memorg.luns_per_target)) *
		   nand->memorg.eraseblocks_per_lun) *
		  nand->memorg.pages_per_eraseblock);

	वापस (loff_t)npages * nand->memorg.pagesize;
पूर्ण

/**
 * nanddev_pos_to_row() - Extract a row address from a न_अंकD position
 * @nand: न_अंकD device
 * @pos: the position to convert
 *
 * Converts a न_अंकD position पूर्णांकo a row address that can then be passed to the
 * device.
 *
 * Return: the row address extracted from @pos.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nanddev_pos_to_row(काष्ठा nand_device *nand,
					      स्थिर काष्ठा nand_pos *pos)
अणु
	वापस (pos->lun << nand->rowconv.lun_addr_shअगरt) |
	       (pos->eraseblock << nand->rowconv.eraseblock_addr_shअगरt) |
	       pos->page;
पूर्ण

/**
 * nanddev_pos_next_target() - Move a position to the next target/die
 * @nand: न_अंकD device
 * @pos: the position to update
 *
 * Updates @pos to poपूर्णांक to the start of the next target/die. Useful when you
 * want to iterate over all tarमाला_लो/dies of a न_अंकD device.
 */
अटल अंतरभूत व्योम nanddev_pos_next_target(काष्ठा nand_device *nand,
					   काष्ठा nand_pos *pos)
अणु
	pos->page = 0;
	pos->plane = 0;
	pos->eraseblock = 0;
	pos->lun = 0;
	pos->target++;
पूर्ण

/**
 * nanddev_pos_next_lun() - Move a position to the next LUN
 * @nand: न_अंकD device
 * @pos: the position to update
 *
 * Updates @pos to poपूर्णांक to the start of the next LUN. Useful when you want to
 * iterate over all LUNs of a न_अंकD device.
 */
अटल अंतरभूत व्योम nanddev_pos_next_lun(काष्ठा nand_device *nand,
					काष्ठा nand_pos *pos)
अणु
	अगर (pos->lun >= nand->memorg.luns_per_target - 1)
		वापस nanddev_pos_next_target(nand, pos);

	pos->lun++;
	pos->page = 0;
	pos->plane = 0;
	pos->eraseblock = 0;
पूर्ण

/**
 * nanddev_pos_next_eraseblock() - Move a position to the next eraseblock
 * @nand: न_अंकD device
 * @pos: the position to update
 *
 * Updates @pos to poपूर्णांक to the start of the next eraseblock. Useful when you
 * want to iterate over all eraseblocks of a न_अंकD device.
 */
अटल अंतरभूत व्योम nanddev_pos_next_eraseblock(काष्ठा nand_device *nand,
					       काष्ठा nand_pos *pos)
अणु
	अगर (pos->eraseblock >= nand->memorg.eraseblocks_per_lun - 1)
		वापस nanddev_pos_next_lun(nand, pos);

	pos->eraseblock++;
	pos->page = 0;
	pos->plane = pos->eraseblock % nand->memorg.planes_per_lun;
पूर्ण

/**
 * nanddev_pos_next_page() - Move a position to the next page
 * @nand: न_अंकD device
 * @pos: the position to update
 *
 * Updates @pos to poपूर्णांक to the start of the next page. Useful when you want to
 * iterate over all pages of a न_अंकD device.
 */
अटल अंतरभूत व्योम nanddev_pos_next_page(काष्ठा nand_device *nand,
					 काष्ठा nand_pos *pos)
अणु
	अगर (pos->page >= nand->memorg.pages_per_eraseblock - 1)
		वापस nanddev_pos_next_eraseblock(nand, pos);

	pos->page++;
पूर्ण

/**
 * nand_io_iter_init - Initialize a न_अंकD I/O iterator
 * @nand: न_अंकD device
 * @offs: असलolute offset
 * @req: MTD request
 * @iter: न_अंकD I/O iterator
 *
 * Initializes a न_अंकD iterator based on the inक्रमmation passed by the MTD
 * layer.
 */
अटल अंतरभूत व्योम nanddev_io_iter_init(काष्ठा nand_device *nand,
					क्रमागत nand_page_io_req_type reqtype,
					loff_t offs, काष्ठा mtd_oob_ops *req,
					काष्ठा nand_io_iter *iter)
अणु
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);

	iter->req.type = reqtype;
	iter->req.mode = req->mode;
	iter->req.dataoffs = nanddev_offs_to_pos(nand, offs, &iter->req.pos);
	iter->req.ooboffs = req->ooboffs;
	iter->oobbytes_per_page = mtd_oobavail(mtd, req);
	iter->dataleft = req->len;
	iter->oobleft = req->ooblen;
	iter->req.databuf.in = req->datbuf;
	iter->req.datalen = min_t(अचिन्हित पूर्णांक,
				  nand->memorg.pagesize - iter->req.dataoffs,
				  iter->dataleft);
	iter->req.oobbuf.in = req->oobbuf;
	iter->req.ooblen = min_t(अचिन्हित पूर्णांक,
				 iter->oobbytes_per_page - iter->req.ooboffs,
				 iter->oobleft);
पूर्ण

/**
 * nand_io_iter_next_page - Move to the next page
 * @nand: न_अंकD device
 * @iter: न_अंकD I/O iterator
 *
 * Updates the @iter to poपूर्णांक to the next page.
 */
अटल अंतरभूत व्योम nanddev_io_iter_next_page(काष्ठा nand_device *nand,
					     काष्ठा nand_io_iter *iter)
अणु
	nanddev_pos_next_page(nand, &iter->req.pos);
	iter->dataleft -= iter->req.datalen;
	iter->req.databuf.in += iter->req.datalen;
	iter->oobleft -= iter->req.ooblen;
	iter->req.oobbuf.in += iter->req.ooblen;
	iter->req.dataoffs = 0;
	iter->req.ooboffs = 0;
	iter->req.datalen = min_t(अचिन्हित पूर्णांक, nand->memorg.pagesize,
				  iter->dataleft);
	iter->req.ooblen = min_t(अचिन्हित पूर्णांक, iter->oobbytes_per_page,
				 iter->oobleft);
पूर्ण

/**
 * nand_io_iter_end - Should end iteration or not
 * @nand: न_अंकD device
 * @iter: न_अंकD I/O iterator
 *
 * Check whether @iter has reached the end of the न_अंकD portion it was asked to
 * iterate on or not.
 *
 * Return: true अगर @iter has reached the end of the iteration request, false
 *	   otherwise.
 */
अटल अंतरभूत bool nanddev_io_iter_end(काष्ठा nand_device *nand,
				       स्थिर काष्ठा nand_io_iter *iter)
अणु
	अगर (iter->dataleft || iter->oobleft)
		वापस false;

	वापस true;
पूर्ण

/**
 * nand_io_क्रम_each_page - Iterate over all न_अंकD pages contained in an MTD I/O
 *			   request
 * @nand: न_अंकD device
 * @start: start address to पढ़ो/ग_लिखो from
 * @req: MTD I/O request
 * @iter: न_अंकD I/O iterator
 *
 * Should be used क्रम iterate over pages that are contained in an MTD request.
 */
#घोषणा nanddev_io_क्रम_each_page(nand, type, start, req, iter)		\
	क्रम (nanddev_io_iter_init(nand, type, start, req, iter);	\
	     !nanddev_io_iter_end(nand, iter);				\
	     nanddev_io_iter_next_page(nand, iter))

bool nanddev_isbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);
bool nanddev_isreserved(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);
पूर्णांक nanddev_erase(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);
पूर्णांक nanddev_markbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos);

/* ECC related functions */
पूर्णांक nanddev_ecc_engine_init(काष्ठा nand_device *nand);
व्योम nanddev_ecc_engine_cleanup(काष्ठा nand_device *nand);

/* BBT related functions */
क्रमागत nand_bbt_block_status अणु
	न_अंकD_BBT_BLOCK_STATUS_UNKNOWN,
	न_अंकD_BBT_BLOCK_GOOD,
	न_अंकD_BBT_BLOCK_WORN,
	न_अंकD_BBT_BLOCK_RESERVED,
	न_अंकD_BBT_BLOCK_FACTORY_BAD,
	न_अंकD_BBT_BLOCK_NUM_STATUS,
पूर्ण;

पूर्णांक nanddev_bbt_init(काष्ठा nand_device *nand);
व्योम nanddev_bbt_cleanup(काष्ठा nand_device *nand);
पूर्णांक nanddev_bbt_update(काष्ठा nand_device *nand);
पूर्णांक nanddev_bbt_get_block_status(स्थिर काष्ठा nand_device *nand,
				 अचिन्हित पूर्णांक entry);
पूर्णांक nanddev_bbt_set_block_status(काष्ठा nand_device *nand, अचिन्हित पूर्णांक entry,
				 क्रमागत nand_bbt_block_status status);
पूर्णांक nanddev_bbt_markbad(काष्ठा nand_device *nand, अचिन्हित पूर्णांक block);

/**
 * nanddev_bbt_pos_to_entry() - Convert a न_अंकD position पूर्णांकo a BBT entry
 * @nand: न_अंकD device
 * @pos: the न_अंकD position we want to get BBT entry क्रम
 *
 * Return the BBT entry used to store inक्रमmation about the eraseblock poपूर्णांकed
 * by @pos.
 *
 * Return: the BBT entry storing inक्रमmation about eraseblock poपूर्णांकed by @pos.
 */
अटल अंतरभूत अचिन्हित पूर्णांक nanddev_bbt_pos_to_entry(काष्ठा nand_device *nand,
						    स्थिर काष्ठा nand_pos *pos)
अणु
	वापस pos->eraseblock +
	       ((pos->lun + (pos->target * nand->memorg.luns_per_target)) *
		nand->memorg.eraseblocks_per_lun);
पूर्ण

/**
 * nanddev_bbt_is_initialized() - Check अगर the BBT has been initialized
 * @nand: न_अंकD device
 *
 * Return: true अगर the BBT has been initialized, false otherwise.
 */
अटल अंतरभूत bool nanddev_bbt_is_initialized(काष्ठा nand_device *nand)
अणु
	वापस !!nand->bbt.cache;
पूर्ण

/* MTD -> न_अंकD helper functions. */
पूर्णांक nanddev_mtd_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *einfo);
पूर्णांक nanddev_mtd_max_bad_blocks(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len);

#पूर्ण_अगर /* __LINUX_MTD_न_अंकD_H */
