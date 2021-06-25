<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2016-2017 Micron Technology, Inc.
 *
 * Authors:
 *	Peter Pan <peterpanकरोng@micron.com>
 *	Boris Brezillon <boris.brezillon@bootlin.com>
 */

#घोषणा pr_fmt(fmt)	"spi-nand: " fmt

#समावेश <linux/device.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/spinand.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi-स्मृति.स>

अटल पूर्णांक spinand_पढ़ो_reg_op(काष्ठा spinand_device *spinand, u8 reg, u8 *val)
अणु
	काष्ठा spi_mem_op op = SPIन_अंकD_GET_FEATURE_OP(reg,
						      spinand->scratchbuf);
	पूर्णांक ret;

	ret = spi_mem_exec_op(spinand->spimem, &op);
	अगर (ret)
		वापस ret;

	*val = *spinand->scratchbuf;
	वापस 0;
पूर्ण

अटल पूर्णांक spinand_ग_लिखो_reg_op(काष्ठा spinand_device *spinand, u8 reg, u8 val)
अणु
	काष्ठा spi_mem_op op = SPIन_अंकD_SET_FEATURE_OP(reg,
						      spinand->scratchbuf);

	*spinand->scratchbuf = val;
	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल पूर्णांक spinand_पढ़ो_status(काष्ठा spinand_device *spinand, u8 *status)
अणु
	वापस spinand_पढ़ो_reg_op(spinand, REG_STATUS, status);
पूर्ण

अटल पूर्णांक spinand_get_cfg(काष्ठा spinand_device *spinand, u8 *cfg)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);

	अगर (WARN_ON(spinand->cur_target < 0 ||
		    spinand->cur_target >= nand->memorg.ntarमाला_लो))
		वापस -EINVAL;

	*cfg = spinand->cfg_cache[spinand->cur_target];
	वापस 0;
पूर्ण

अटल पूर्णांक spinand_set_cfg(काष्ठा spinand_device *spinand, u8 cfg)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	पूर्णांक ret;

	अगर (WARN_ON(spinand->cur_target < 0 ||
		    spinand->cur_target >= nand->memorg.ntarमाला_लो))
		वापस -EINVAL;

	अगर (spinand->cfg_cache[spinand->cur_target] == cfg)
		वापस 0;

	ret = spinand_ग_लिखो_reg_op(spinand, REG_CFG, cfg);
	अगर (ret)
		वापस ret;

	spinand->cfg_cache[spinand->cur_target] = cfg;
	वापस 0;
पूर्ण

/**
 * spinand_upd_cfg() - Update the configuration रेजिस्टर
 * @spinand: the spinand device
 * @mask: the mask encoding the bits to update in the config reg
 * @val: the new value to apply
 *
 * Update the configuration रेजिस्टर.
 *
 * Return: 0 on success, a negative error code otherwise.
 */
पूर्णांक spinand_upd_cfg(काष्ठा spinand_device *spinand, u8 mask, u8 val)
अणु
	पूर्णांक ret;
	u8 cfg;

	ret = spinand_get_cfg(spinand, &cfg);
	अगर (ret)
		वापस ret;

	cfg &= ~mask;
	cfg |= val;

	वापस spinand_set_cfg(spinand, cfg);
पूर्ण

/**
 * spinand_select_target() - Select a specअगरic न_अंकD target/die
 * @spinand: the spinand device
 * @target: the target/die to select
 *
 * Select a new target/die. If chip only has one die, this function is a NOOP.
 *
 * Return: 0 on success, a negative error code otherwise.
 */
पूर्णांक spinand_select_target(काष्ठा spinand_device *spinand, अचिन्हित पूर्णांक target)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	पूर्णांक ret;

	अगर (WARN_ON(target >= nand->memorg.ntarमाला_लो))
		वापस -EINVAL;

	अगर (spinand->cur_target == target)
		वापस 0;

	अगर (nand->memorg.ntarमाला_लो == 1) अणु
		spinand->cur_target = target;
		वापस 0;
	पूर्ण

	ret = spinand->select_target(spinand, target);
	अगर (ret)
		वापस ret;

	spinand->cur_target = target;
	वापस 0;
पूर्ण

अटल पूर्णांक spinand_init_cfg_cache(काष्ठा spinand_device *spinand)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	काष्ठा device *dev = &spinand->spimem->spi->dev;
	अचिन्हित पूर्णांक target;
	पूर्णांक ret;

	spinand->cfg_cache = devm_kसुस्मृति(dev,
					  nand->memorg.ntarमाला_लो,
					  माप(*spinand->cfg_cache),
					  GFP_KERNEL);
	अगर (!spinand->cfg_cache)
		वापस -ENOMEM;

	क्रम (target = 0; target < nand->memorg.ntarमाला_लो; target++) अणु
		ret = spinand_select_target(spinand, target);
		अगर (ret)
			वापस ret;

		/*
		 * We use spinand_पढ़ो_reg_op() instead of spinand_get_cfg()
		 * here to bypass the config cache.
		 */
		ret = spinand_पढ़ो_reg_op(spinand, REG_CFG,
					  &spinand->cfg_cache[target]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spinand_init_quad_enable(काष्ठा spinand_device *spinand)
अणु
	bool enable = false;

	अगर (!(spinand->flags & SPIन_अंकD_HAS_QE_BIT))
		वापस 0;

	अगर (spinand->op_ढाँचाs.पढ़ो_cache->data.buswidth == 4 ||
	    spinand->op_ढाँचाs.ग_लिखो_cache->data.buswidth == 4 ||
	    spinand->op_ढाँचाs.update_cache->data.buswidth == 4)
		enable = true;

	वापस spinand_upd_cfg(spinand, CFG_QUAD_ENABLE,
			       enable ? CFG_QUAD_ENABLE : 0);
पूर्ण

अटल पूर्णांक spinand_ecc_enable(काष्ठा spinand_device *spinand,
			      bool enable)
अणु
	वापस spinand_upd_cfg(spinand, CFG_ECC_ENABLE,
			       enable ? CFG_ECC_ENABLE : 0);
पूर्ण

अटल पूर्णांक spinand_check_ecc_status(काष्ठा spinand_device *spinand, u8 status)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);

	अगर (spinand->eccinfo.get_status)
		वापस spinand->eccinfo.get_status(spinand, status);

	चयन (status & STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल STATUS_ECC_HAS_BITFLIPS:
		/*
		 * We have no way to know exactly how many bitflips have been
		 * fixed, so let's वापस the maximum possible value so that
		 * wear-leveling layers move the data immediately.
		 */
		वापस nanddev_get_ecc_conf(nand)->strength;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक spinand_noecc_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *region)
अणु
	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक spinand_noecc_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *region)
अणु
	अगर (section)
		वापस -दुस्फल;

	/* Reserve 2 bytes क्रम the BBM. */
	region->offset = 2;
	region->length = 62;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops spinand_noecc_ooblayout = अणु
	.ecc = spinand_noecc_ooblayout_ecc,
	.मुक्त = spinand_noecc_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक spinand_ondie_ecc_init_ctx(काष्ठा nand_device *nand)
अणु
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	काष्ठा mtd_info *mtd = nanddev_to_mtd(nand);
	काष्ठा spinand_ondie_ecc_conf *engine_conf;

	nand->ecc.ctx.conf.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_DIE;
	nand->ecc.ctx.conf.step_size = nand->ecc.requirements.step_size;
	nand->ecc.ctx.conf.strength = nand->ecc.requirements.strength;

	engine_conf = kzalloc(माप(*engine_conf), GFP_KERNEL);
	अगर (!engine_conf)
		वापस -ENOMEM;

	nand->ecc.ctx.priv = engine_conf;

	अगर (spinand->eccinfo.ooblayout)
		mtd_set_ooblayout(mtd, spinand->eccinfo.ooblayout);
	अन्यथा
		mtd_set_ooblayout(mtd, &spinand_noecc_ooblayout);

	वापस 0;
पूर्ण

अटल व्योम spinand_ondie_ecc_cleanup_ctx(काष्ठा nand_device *nand)
अणु
	kमुक्त(nand->ecc.ctx.priv);
पूर्ण

अटल पूर्णांक spinand_ondie_ecc_prepare_io_req(काष्ठा nand_device *nand,
					    काष्ठा nand_page_io_req *req)
अणु
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	bool enable = (req->mode != MTD_OPS_RAW);

	/* Only enable or disable the engine */
	वापस spinand_ecc_enable(spinand, enable);
पूर्ण

अटल पूर्णांक spinand_ondie_ecc_finish_io_req(काष्ठा nand_device *nand,
					   काष्ठा nand_page_io_req *req)
अणु
	काष्ठा spinand_ondie_ecc_conf *engine_conf = nand->ecc.ctx.priv;
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);

	अगर (req->mode == MTD_OPS_RAW)
		वापस 0;

	/* Nothing to करो when finishing a page ग_लिखो */
	अगर (req->type == न_अंकD_PAGE_WRITE)
		वापस 0;

	/* Finish a page ग_लिखो: check the status, report errors/bitflips */
	वापस spinand_check_ecc_status(spinand, engine_conf->status);
पूर्ण

अटल काष्ठा nand_ecc_engine_ops spinand_ondie_ecc_engine_ops = अणु
	.init_ctx = spinand_ondie_ecc_init_ctx,
	.cleanup_ctx = spinand_ondie_ecc_cleanup_ctx,
	.prepare_io_req = spinand_ondie_ecc_prepare_io_req,
	.finish_io_req = spinand_ondie_ecc_finish_io_req,
पूर्ण;

अटल काष्ठा nand_ecc_engine spinand_ondie_ecc_engine = अणु
	.ops = &spinand_ondie_ecc_engine_ops,
पूर्ण;

अटल व्योम spinand_ondie_ecc_save_status(काष्ठा nand_device *nand, u8 status)
अणु
	काष्ठा spinand_ondie_ecc_conf *engine_conf = nand->ecc.ctx.priv;

	अगर (nand->ecc.ctx.conf.engine_type == न_अंकD_ECC_ENGINE_TYPE_ON_DIE &&
	    engine_conf)
		engine_conf->status = status;
पूर्ण

अटल पूर्णांक spinand_ग_लिखो_enable_op(काष्ठा spinand_device *spinand)
अणु
	काष्ठा spi_mem_op op = SPIन_अंकD_WR_EN_DIS_OP(true);

	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल पूर्णांक spinand_load_page_op(काष्ठा spinand_device *spinand,
				स्थिर काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	अचिन्हित पूर्णांक row = nanddev_pos_to_row(nand, &req->pos);
	काष्ठा spi_mem_op op = SPIन_अंकD_PAGE_READ_OP(row);

	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल पूर्णांक spinand_पढ़ो_from_cache_op(काष्ठा spinand_device *spinand,
				      स्थिर काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	काष्ठा mtd_info *mtd = spinand_to_mtd(spinand);
	काष्ठा spi_mem_dirmap_desc *rdesc;
	अचिन्हित पूर्णांक nbytes = 0;
	व्योम *buf = शून्य;
	u16 column = 0;
	sमाप_प्रकार ret;

	अगर (req->datalen) अणु
		buf = spinand->databuf;
		nbytes = nanddev_page_size(nand);
		column = 0;
	पूर्ण

	अगर (req->ooblen) अणु
		nbytes += nanddev_per_page_oobsize(nand);
		अगर (!buf) अणु
			buf = spinand->oobbuf;
			column = nanddev_page_size(nand);
		पूर्ण
	पूर्ण

	rdesc = spinand->dirmaps[req->pos.plane].rdesc;

	जबतक (nbytes) अणु
		ret = spi_mem_dirmap_पढ़ो(rdesc, column, nbytes, buf);
		अगर (ret < 0)
			वापस ret;

		अगर (!ret || ret > nbytes)
			वापस -EIO;

		nbytes -= ret;
		column += ret;
		buf += ret;
	पूर्ण

	अगर (req->datalen)
		स_नकल(req->databuf.in, spinand->databuf + req->dataoffs,
		       req->datalen);

	अगर (req->ooblen) अणु
		अगर (req->mode == MTD_OPS_AUTO_OOB)
			mtd_ooblayout_get_databytes(mtd, req->oobbuf.in,
						    spinand->oobbuf,
						    req->ooboffs,
						    req->ooblen);
		अन्यथा
			स_नकल(req->oobbuf.in, spinand->oobbuf + req->ooboffs,
			       req->ooblen);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spinand_ग_लिखो_to_cache_op(काष्ठा spinand_device *spinand,
				     स्थिर काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	काष्ठा mtd_info *mtd = spinand_to_mtd(spinand);
	काष्ठा spi_mem_dirmap_desc *wdesc;
	अचिन्हित पूर्णांक nbytes, column = 0;
	व्योम *buf = spinand->databuf;
	sमाप_प्रकार ret;

	/*
	 * Looks like PROGRAM LOAD (AKA ग_लिखो cache) करोes not necessarily reset
	 * the cache content to 0xFF (depends on venकरोr implementation), so we
	 * must fill the page cache entirely even अगर we only want to program
	 * the data portion of the page, otherwise we might corrupt the BBM or
	 * user data previously programmed in OOB area.
	 *
	 * Only reset the data buffer manually, the OOB buffer is prepared by
	 * ECC engines ->prepare_io_req() callback.
	 */
	nbytes = nanddev_page_size(nand) + nanddev_per_page_oobsize(nand);
	स_रखो(spinand->databuf, 0xff, nanddev_page_size(nand));

	अगर (req->datalen)
		स_नकल(spinand->databuf + req->dataoffs, req->databuf.out,
		       req->datalen);

	अगर (req->ooblen) अणु
		अगर (req->mode == MTD_OPS_AUTO_OOB)
			mtd_ooblayout_set_databytes(mtd, req->oobbuf.out,
						    spinand->oobbuf,
						    req->ooboffs,
						    req->ooblen);
		अन्यथा
			स_नकल(spinand->oobbuf + req->ooboffs, req->oobbuf.out,
			       req->ooblen);
	पूर्ण

	wdesc = spinand->dirmaps[req->pos.plane].wdesc;

	जबतक (nbytes) अणु
		ret = spi_mem_dirmap_ग_लिखो(wdesc, column, nbytes, buf);
		अगर (ret < 0)
			वापस ret;

		अगर (!ret || ret > nbytes)
			वापस -EIO;

		nbytes -= ret;
		column += ret;
		buf += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक spinand_program_op(काष्ठा spinand_device *spinand,
			      स्थिर काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	अचिन्हित पूर्णांक row = nanddev_pos_to_row(nand, &req->pos);
	काष्ठा spi_mem_op op = SPIन_अंकD_PROG_EXEC_OP(row);

	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल पूर्णांक spinand_erase_op(काष्ठा spinand_device *spinand,
			    स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	अचिन्हित पूर्णांक row = nanddev_pos_to_row(nand, pos);
	काष्ठा spi_mem_op op = SPIन_अंकD_BLK_ERASE_OP(row);

	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल पूर्णांक spinand_रुको(काष्ठा spinand_device *spinand, u8 *s)
अणु
	अचिन्हित दीर्घ समयo =  jअगरfies + msecs_to_jअगरfies(400);
	u8 status;
	पूर्णांक ret;

	करो अणु
		ret = spinand_पढ़ो_status(spinand, &status);
		अगर (ret)
			वापस ret;

		अगर (!(status & STATUS_BUSY))
			जाओ out;
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, समयo));

	/*
	 * Extra पढ़ो, just in हाल the STATUS_READY bit has changed
	 * since our last check
	 */
	ret = spinand_पढ़ो_status(spinand, &status);
	अगर (ret)
		वापस ret;

out:
	अगर (s)
		*s = status;

	वापस status & STATUS_BUSY ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक spinand_पढ़ो_id_op(काष्ठा spinand_device *spinand, u8 naddr,
			      u8 ndummy, u8 *buf)
अणु
	काष्ठा spi_mem_op op = SPIन_अंकD_READID_OP(
		naddr, ndummy, spinand->scratchbuf, SPIन_अंकD_MAX_ID_LEN);
	पूर्णांक ret;

	ret = spi_mem_exec_op(spinand->spimem, &op);
	अगर (!ret)
		स_नकल(buf, spinand->scratchbuf, SPIन_अंकD_MAX_ID_LEN);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_reset_op(काष्ठा spinand_device *spinand)
अणु
	काष्ठा spi_mem_op op = SPIन_अंकD_RESET_OP;
	पूर्णांक ret;

	ret = spi_mem_exec_op(spinand->spimem, &op);
	अगर (ret)
		वापस ret;

	वापस spinand_रुको(spinand, शून्य);
पूर्ण

अटल पूर्णांक spinand_lock_block(काष्ठा spinand_device *spinand, u8 lock)
अणु
	वापस spinand_ग_लिखो_reg_op(spinand, REG_BLOCK_LOCK, lock);
पूर्ण

अटल पूर्णांक spinand_पढ़ो_page(काष्ठा spinand_device *spinand,
			     स्थिर काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	u8 status;
	पूर्णांक ret;

	ret = nand_ecc_prepare_io_req(nand, (काष्ठा nand_page_io_req *)req);
	अगर (ret)
		वापस ret;

	ret = spinand_load_page_op(spinand, req);
	अगर (ret)
		वापस ret;

	ret = spinand_रुको(spinand, &status);
	अगर (ret < 0)
		वापस ret;

	spinand_ondie_ecc_save_status(nand, status);

	ret = spinand_पढ़ो_from_cache_op(spinand, req);
	अगर (ret)
		वापस ret;

	वापस nand_ecc_finish_io_req(nand, (काष्ठा nand_page_io_req *)req);
पूर्ण

अटल पूर्णांक spinand_ग_लिखो_page(काष्ठा spinand_device *spinand,
			      स्थिर काष्ठा nand_page_io_req *req)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	u8 status;
	पूर्णांक ret;

	ret = nand_ecc_prepare_io_req(nand, (काष्ठा nand_page_io_req *)req);
	अगर (ret)
		वापस ret;

	ret = spinand_ग_लिखो_enable_op(spinand);
	अगर (ret)
		वापस ret;

	ret = spinand_ग_लिखो_to_cache_op(spinand, req);
	अगर (ret)
		वापस ret;

	ret = spinand_program_op(spinand, req);
	अगर (ret)
		वापस ret;

	ret = spinand_रुको(spinand, &status);
	अगर (!ret && (status & STATUS_PROG_FAILED))
		वापस -EIO;

	वापस nand_ecc_finish_io_req(nand, (काष्ठा nand_page_io_req *)req);
पूर्ण

अटल पूर्णांक spinand_mtd_पढ़ो(काष्ठा mtd_info *mtd, loff_t from,
			    काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा spinand_device *spinand = mtd_to_spinand(mtd);
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	अचिन्हित पूर्णांक max_bitflips = 0;
	काष्ठा nand_io_iter iter;
	bool disable_ecc = false;
	bool ecc_failed = false;
	पूर्णांक ret = 0;

	अगर (ops->mode == MTD_OPS_RAW || !spinand->eccinfo.ooblayout)
		disable_ecc = true;

	mutex_lock(&spinand->lock);

	nanddev_io_क्रम_each_page(nand, न_अंकD_PAGE_READ, from, ops, &iter) अणु
		अगर (disable_ecc)
			iter.req.mode = MTD_OPS_RAW;

		ret = spinand_select_target(spinand, iter.req.pos.target);
		अगर (ret)
			अवरोध;

		ret = spinand_पढ़ो_page(spinand, &iter.req);
		अगर (ret < 0 && ret != -EBADMSG)
			अवरोध;

		अगर (ret == -EBADMSG) अणु
			ecc_failed = true;
			mtd->ecc_stats.failed++;
		पूर्ण अन्यथा अणु
			mtd->ecc_stats.corrected += ret;
			max_bitflips = max_t(अचिन्हित पूर्णांक, max_bitflips, ret);
		पूर्ण

		ret = 0;
		ops->retlen += iter.req.datalen;
		ops->oobretlen += iter.req.ooblen;
	पूर्ण

	mutex_unlock(&spinand->lock);

	अगर (ecc_failed && !ret)
		ret = -EBADMSG;

	वापस ret ? ret : max_bitflips;
पूर्ण

अटल पूर्णांक spinand_mtd_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to,
			     काष्ठा mtd_oob_ops *ops)
अणु
	काष्ठा spinand_device *spinand = mtd_to_spinand(mtd);
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	काष्ठा nand_io_iter iter;
	bool disable_ecc = false;
	पूर्णांक ret = 0;

	अगर (ops->mode == MTD_OPS_RAW || !mtd->ooblayout)
		disable_ecc = true;

	mutex_lock(&spinand->lock);

	nanddev_io_क्रम_each_page(nand, न_अंकD_PAGE_WRITE, to, ops, &iter) अणु
		अगर (disable_ecc)
			iter.req.mode = MTD_OPS_RAW;

		ret = spinand_select_target(spinand, iter.req.pos.target);
		अगर (ret)
			अवरोध;

		ret = spinand_ग_लिखो_page(spinand, &iter.req);
		अगर (ret)
			अवरोध;

		ops->retlen += iter.req.datalen;
		ops->oobretlen += iter.req.ooblen;
	पूर्ण

	mutex_unlock(&spinand->lock);

	वापस ret;
पूर्ण

अटल bool spinand_isbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	u8 marker[2] = अणु पूर्ण;
	काष्ठा nand_page_io_req req = अणु
		.pos = *pos,
		.ooblen = माप(marker),
		.ooboffs = 0,
		.oobbuf.in = marker,
		.mode = MTD_OPS_RAW,
	पूर्ण;

	spinand_select_target(spinand, pos->target);
	spinand_पढ़ो_page(spinand, &req);
	अगर (marker[0] != 0xff || marker[1] != 0xff)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक spinand_mtd_block_isbad(काष्ठा mtd_info *mtd, loff_t offs)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	काष्ठा nand_pos pos;
	पूर्णांक ret;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_lock(&spinand->lock);
	ret = nanddev_isbad(nand, &pos);
	mutex_unlock(&spinand->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_markbad(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	u8 marker[2] = अणु पूर्ण;
	काष्ठा nand_page_io_req req = अणु
		.pos = *pos,
		.ooboffs = 0,
		.ooblen = माप(marker),
		.oobbuf.out = marker,
		.mode = MTD_OPS_RAW,
	पूर्ण;
	पूर्णांक ret;

	ret = spinand_select_target(spinand, pos->target);
	अगर (ret)
		वापस ret;

	ret = spinand_ग_लिखो_enable_op(spinand);
	अगर (ret)
		वापस ret;

	वापस spinand_ग_लिखो_page(spinand, &req);
पूर्ण

अटल पूर्णांक spinand_mtd_block_markbad(काष्ठा mtd_info *mtd, loff_t offs)
अणु
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	काष्ठा nand_pos pos;
	पूर्णांक ret;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_lock(&spinand->lock);
	ret = nanddev_markbad(nand, &pos);
	mutex_unlock(&spinand->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_erase(काष्ठा nand_device *nand, स्थिर काष्ठा nand_pos *pos)
अणु
	काष्ठा spinand_device *spinand = nand_to_spinand(nand);
	u8 status;
	पूर्णांक ret;

	ret = spinand_select_target(spinand, pos->target);
	अगर (ret)
		वापस ret;

	ret = spinand_ग_लिखो_enable_op(spinand);
	अगर (ret)
		वापस ret;

	ret = spinand_erase_op(spinand, pos);
	अगर (ret)
		वापस ret;

	ret = spinand_रुको(spinand, &status);
	अगर (!ret && (status & STATUS_ERASE_FAILED))
		ret = -EIO;

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_mtd_erase(काष्ठा mtd_info *mtd,
			     काष्ठा erase_info *einfo)
अणु
	काष्ठा spinand_device *spinand = mtd_to_spinand(mtd);
	पूर्णांक ret;

	mutex_lock(&spinand->lock);
	ret = nanddev_mtd_erase(mtd, einfo);
	mutex_unlock(&spinand->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_mtd_block_isreserved(काष्ठा mtd_info *mtd, loff_t offs)
अणु
	काष्ठा spinand_device *spinand = mtd_to_spinand(mtd);
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	काष्ठा nand_pos pos;
	पूर्णांक ret;

	nanddev_offs_to_pos(nand, offs, &pos);
	mutex_lock(&spinand->lock);
	ret = nanddev_isreserved(nand, &pos);
	mutex_unlock(&spinand->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_create_dirmap(काष्ठा spinand_device *spinand,
				 अचिन्हित पूर्णांक plane)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	काष्ठा spi_mem_dirmap_info info = अणु
		.length = nanddev_page_size(nand) +
			  nanddev_per_page_oobsize(nand),
	पूर्ण;
	काष्ठा spi_mem_dirmap_desc *desc;

	/* The plane number is passed in MSB just above the column address */
	info.offset = plane << fls(nand->memorg.pagesize);

	info.op_पंचांगpl = *spinand->op_ढाँचाs.update_cache;
	desc = devm_spi_mem_dirmap_create(&spinand->spimem->spi->dev,
					  spinand->spimem, &info);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	spinand->dirmaps[plane].wdesc = desc;

	info.op_पंचांगpl = *spinand->op_ढाँचाs.पढ़ो_cache;
	desc = devm_spi_mem_dirmap_create(&spinand->spimem->spi->dev,
					  spinand->spimem, &info);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	spinand->dirmaps[plane].rdesc = desc;

	वापस 0;
पूर्ण

अटल पूर्णांक spinand_create_dirmaps(काष्ठा spinand_device *spinand)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	पूर्णांक i, ret;

	spinand->dirmaps = devm_kzalloc(&spinand->spimem->spi->dev,
					माप(*spinand->dirmaps) *
					nand->memorg.planes_per_lun,
					GFP_KERNEL);
	अगर (!spinand->dirmaps)
		वापस -ENOMEM;

	क्रम (i = 0; i < nand->memorg.planes_per_lun; i++) अणु
		ret = spinand_create_dirmap(spinand, i);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_ops spinand_ops = अणु
	.erase = spinand_erase,
	.markbad = spinand_markbad,
	.isbad = spinand_isbad,
पूर्ण;

अटल स्थिर काष्ठा spinand_manufacturer *spinand_manufacturers[] = अणु
	&gigadevice_spinand_manufacturer,
	&macronix_spinand_manufacturer,
	&micron_spinand_manufacturer,
	&paragon_spinand_manufacturer,
	&toshiba_spinand_manufacturer,
	&winbond_spinand_manufacturer,
पूर्ण;

अटल पूर्णांक spinand_manufacturer_match(काष्ठा spinand_device *spinand,
				      क्रमागत spinand_पढ़ोid_method rdid_method)
अणु
	u8 *id = spinand->id.data;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	क्रम (i = 0; i < ARRAY_SIZE(spinand_manufacturers); i++) अणु
		स्थिर काष्ठा spinand_manufacturer *manufacturer =
			spinand_manufacturers[i];

		अगर (id[0] != manufacturer->id)
			जारी;

		ret = spinand_match_and_init(spinand,
					     manufacturer->chips,
					     manufacturer->nchips,
					     rdid_method);
		अगर (ret < 0)
			जारी;

		spinand->manufacturer = manufacturer;
		वापस 0;
	पूर्ण
	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक spinand_id_detect(काष्ठा spinand_device *spinand)
अणु
	u8 *id = spinand->id.data;
	पूर्णांक ret;

	ret = spinand_पढ़ो_id_op(spinand, 0, 0, id);
	अगर (ret)
		वापस ret;
	ret = spinand_manufacturer_match(spinand, SPIन_अंकD_READID_METHOD_OPCODE);
	अगर (!ret)
		वापस 0;

	ret = spinand_पढ़ो_id_op(spinand, 1, 0, id);
	अगर (ret)
		वापस ret;
	ret = spinand_manufacturer_match(spinand,
					 SPIन_अंकD_READID_METHOD_OPCODE_ADDR);
	अगर (!ret)
		वापस 0;

	ret = spinand_पढ़ो_id_op(spinand, 0, 1, id);
	अगर (ret)
		वापस ret;
	ret = spinand_manufacturer_match(spinand,
					 SPIन_अंकD_READID_METHOD_OPCODE_DUMMY);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_manufacturer_init(काष्ठा spinand_device *spinand)
अणु
	अगर (spinand->manufacturer->ops->init)
		वापस spinand->manufacturer->ops->init(spinand);

	वापस 0;
पूर्ण

अटल व्योम spinand_manufacturer_cleanup(काष्ठा spinand_device *spinand)
अणु
	/* Release manufacturer निजी data */
	अगर (spinand->manufacturer->ops->cleanup)
		वापस spinand->manufacturer->ops->cleanup(spinand);
पूर्ण

अटल स्थिर काष्ठा spi_mem_op *
spinand_select_op_variant(काष्ठा spinand_device *spinand,
			  स्थिर काष्ठा spinand_op_variants *variants)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < variants->nops; i++) अणु
		काष्ठा spi_mem_op op = variants->ops[i];
		अचिन्हित पूर्णांक nbytes;
		पूर्णांक ret;

		nbytes = nanddev_per_page_oobsize(nand) +
			 nanddev_page_size(nand);

		जबतक (nbytes) अणु
			op.data.nbytes = nbytes;
			ret = spi_mem_adjust_op_size(spinand->spimem, &op);
			अगर (ret)
				अवरोध;

			अगर (!spi_mem_supports_op(spinand->spimem, &op))
				अवरोध;

			nbytes -= op.data.nbytes;
		पूर्ण

		अगर (!nbytes)
			वापस &variants->ops[i];
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * spinand_match_and_init() - Try to find a match between a device ID and an
 *			      entry in a spinand_info table
 * @spinand: SPI न_अंकD object
 * @table: SPI न_अंकD device description table
 * @table_size: size of the device description table
 * @rdid_method: पढ़ो id method to match
 *
 * Match between a device ID retrieved through the READ_ID command and an
 * entry in the SPI न_अंकD description table. If a match is found, the spinand
 * object will be initialized with inक्रमmation provided by the matching
 * spinand_info entry.
 *
 * Return: 0 on success, a negative error code otherwise.
 */
पूर्णांक spinand_match_and_init(काष्ठा spinand_device *spinand,
			   स्थिर काष्ठा spinand_info *table,
			   अचिन्हित पूर्णांक table_size,
			   क्रमागत spinand_पढ़ोid_method rdid_method)
अणु
	u8 *id = spinand->id.data;
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < table_size; i++) अणु
		स्थिर काष्ठा spinand_info *info = &table[i];
		स्थिर काष्ठा spi_mem_op *op;

		अगर (rdid_method != info->devid.method)
			जारी;

		अगर (स_भेद(id + 1, info->devid.id, info->devid.len))
			जारी;

		nand->memorg = table[i].memorg;
		nanddev_set_ecc_requirements(nand, &table[i].eccreq);
		spinand->eccinfo = table[i].eccinfo;
		spinand->flags = table[i].flags;
		spinand->id.len = 1 + table[i].devid.len;
		spinand->select_target = table[i].select_target;

		op = spinand_select_op_variant(spinand,
					       info->op_variants.पढ़ो_cache);
		अगर (!op)
			वापस -ENOTSUPP;

		spinand->op_ढाँचाs.पढ़ो_cache = op;

		op = spinand_select_op_variant(spinand,
					       info->op_variants.ग_लिखो_cache);
		अगर (!op)
			वापस -ENOTSUPP;

		spinand->op_ढाँचाs.ग_लिखो_cache = op;

		op = spinand_select_op_variant(spinand,
					       info->op_variants.update_cache);
		spinand->op_ढाँचाs.update_cache = op;

		वापस 0;
	पूर्ण

	वापस -ENOTSUPP;
पूर्ण

अटल पूर्णांक spinand_detect(काष्ठा spinand_device *spinand)
अणु
	काष्ठा device *dev = &spinand->spimem->spi->dev;
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	पूर्णांक ret;

	ret = spinand_reset_op(spinand);
	अगर (ret)
		वापस ret;

	ret = spinand_id_detect(spinand);
	अगर (ret) अणु
		dev_err(dev, "unknown raw ID %*phN\n", SPIन_अंकD_MAX_ID_LEN,
			spinand->id.data);
		वापस ret;
	पूर्ण

	अगर (nand->memorg.ntarमाला_लो > 1 && !spinand->select_target) अणु
		dev_err(dev,
			"SPI NANDs with more than one die must implement ->select_target()\n");
		वापस -EINVAL;
	पूर्ण

	dev_info(&spinand->spimem->spi->dev,
		 "%s SPI NAND was found.\n", spinand->manufacturer->name);
	dev_info(&spinand->spimem->spi->dev,
		 "%llu MiB, block size: %zu KiB, page size: %zu, OOB size: %u\n",
		 nanddev_size(nand) >> 20, nanddev_eraseblock_size(nand) >> 10,
		 nanddev_page_size(nand), nanddev_per_page_oobsize(nand));

	वापस 0;
पूर्ण

अटल पूर्णांक spinand_init(काष्ठा spinand_device *spinand)
अणु
	काष्ठा device *dev = &spinand->spimem->spi->dev;
	काष्ठा mtd_info *mtd = spinand_to_mtd(spinand);
	काष्ठा nand_device *nand = mtd_to_nanddev(mtd);
	पूर्णांक ret, i;

	/*
	 * We need a scratch buffer because the spi_mem पूर्णांकerface requires that
	 * buf passed in spi_mem_op->data.buf be DMA-able.
	 */
	spinand->scratchbuf = kzalloc(SPIन_अंकD_MAX_ID_LEN, GFP_KERNEL);
	अगर (!spinand->scratchbuf)
		वापस -ENOMEM;

	ret = spinand_detect(spinand);
	अगर (ret)
		जाओ err_मुक्त_bufs;

	/*
	 * Use kzalloc() instead of devm_kzalloc() here, because some drivers
	 * may use this buffer क्रम DMA access.
	 * Memory allocated by devm_ करोes not guarantee DMA-safe alignment.
	 */
	spinand->databuf = kzalloc(nanddev_page_size(nand) +
			       nanddev_per_page_oobsize(nand),
			       GFP_KERNEL);
	अगर (!spinand->databuf) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_bufs;
	पूर्ण

	spinand->oobbuf = spinand->databuf + nanddev_page_size(nand);

	ret = spinand_init_cfg_cache(spinand);
	अगर (ret)
		जाओ err_मुक्त_bufs;

	ret = spinand_init_quad_enable(spinand);
	अगर (ret)
		जाओ err_मुक्त_bufs;

	ret = spinand_upd_cfg(spinand, CFG_OTP_ENABLE, 0);
	अगर (ret)
		जाओ err_मुक्त_bufs;

	ret = spinand_manufacturer_init(spinand);
	अगर (ret) अणु
		dev_err(dev,
			"Failed to initialize the SPI NAND chip (err = %d)\n",
			ret);
		जाओ err_मुक्त_bufs;
	पूर्ण

	ret = spinand_create_dirmaps(spinand);
	अगर (ret) अणु
		dev_err(dev,
			"Failed to create direct mappings for read/write operations (err = %d)\n",
			ret);
		जाओ err_manuf_cleanup;
	पूर्ण

	/* After घातer up, all blocks are locked, so unlock them here. */
	क्रम (i = 0; i < nand->memorg.ntarमाला_लो; i++) अणु
		ret = spinand_select_target(spinand, i);
		अगर (ret)
			जाओ err_manuf_cleanup;

		ret = spinand_lock_block(spinand, BL_ALL_UNLOCKED);
		अगर (ret)
			जाओ err_manuf_cleanup;
	पूर्ण

	ret = nanddev_init(nand, &spinand_ops, THIS_MODULE);
	अगर (ret)
		जाओ err_manuf_cleanup;

	/* SPI-न_अंकD शेष ECC engine is on-die */
	nand->ecc.शेषs.engine_type = न_अंकD_ECC_ENGINE_TYPE_ON_DIE;
	nand->ecc.ondie_engine = &spinand_ondie_ecc_engine;

	spinand_ecc_enable(spinand, false);
	ret = nanddev_ecc_engine_init(nand);
	अगर (ret)
		जाओ err_cleanup_nanddev;

	mtd->_पढ़ो_oob = spinand_mtd_पढ़ो;
	mtd->_ग_लिखो_oob = spinand_mtd_ग_लिखो;
	mtd->_block_isbad = spinand_mtd_block_isbad;
	mtd->_block_markbad = spinand_mtd_block_markbad;
	mtd->_block_isreserved = spinand_mtd_block_isreserved;
	mtd->_erase = spinand_mtd_erase;
	mtd->_max_bad_blocks = nanddev_mtd_max_bad_blocks;

	अगर (nand->ecc.engine) अणु
		ret = mtd_ooblayout_count_मुक्तbytes(mtd);
		अगर (ret < 0)
			जाओ err_cleanup_ecc_engine;
	पूर्ण

	mtd->oobavail = ret;

	/* Propagate ECC inक्रमmation to mtd_info */
	mtd->ecc_strength = nanddev_get_ecc_conf(nand)->strength;
	mtd->ecc_step_size = nanddev_get_ecc_conf(nand)->step_size;

	वापस 0;

err_cleanup_ecc_engine:
	nanddev_ecc_engine_cleanup(nand);

err_cleanup_nanddev:
	nanddev_cleanup(nand);

err_manuf_cleanup:
	spinand_manufacturer_cleanup(spinand);

err_मुक्त_bufs:
	kमुक्त(spinand->databuf);
	kमुक्त(spinand->scratchbuf);
	वापस ret;
पूर्ण

अटल व्योम spinand_cleanup(काष्ठा spinand_device *spinand)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);

	nanddev_cleanup(nand);
	spinand_manufacturer_cleanup(spinand);
	kमुक्त(spinand->databuf);
	kमुक्त(spinand->scratchbuf);
पूर्ण

अटल पूर्णांक spinand_probe(काष्ठा spi_mem *mem)
अणु
	काष्ठा spinand_device *spinand;
	काष्ठा mtd_info *mtd;
	पूर्णांक ret;

	spinand = devm_kzalloc(&mem->spi->dev, माप(*spinand),
			       GFP_KERNEL);
	अगर (!spinand)
		वापस -ENOMEM;

	spinand->spimem = mem;
	spi_mem_set_drvdata(mem, spinand);
	spinand_set_of_node(spinand, mem->spi->dev.of_node);
	mutex_init(&spinand->lock);
	mtd = spinand_to_mtd(spinand);
	mtd->dev.parent = &mem->spi->dev;

	ret = spinand_init(spinand);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		जाओ err_spinand_cleanup;

	वापस 0;

err_spinand_cleanup:
	spinand_cleanup(spinand);

	वापस ret;
पूर्ण

अटल पूर्णांक spinand_हटाओ(काष्ठा spi_mem *mem)
अणु
	काष्ठा spinand_device *spinand;
	काष्ठा mtd_info *mtd;
	पूर्णांक ret;

	spinand = spi_mem_get_drvdata(mem);
	mtd = spinand_to_mtd(spinand);

	ret = mtd_device_unरेजिस्टर(mtd);
	अगर (ret)
		वापस ret;

	spinand_cleanup(spinand);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spi_device_id spinand_ids[] = अणु
	अणु .name = "spi-nand" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(spi, spinand_ids);

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id spinand_of_ids[] = अणु
	अणु .compatible = "spi-nand" पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, spinand_of_ids);
#पूर्ण_अगर

अटल काष्ठा spi_mem_driver spinand_drv = अणु
	.spidrv = अणु
		.id_table = spinand_ids,
		.driver = अणु
			.name = "spi-nand",
			.of_match_table = of_match_ptr(spinand_of_ids),
		पूर्ण,
	पूर्ण,
	.probe = spinand_probe,
	.हटाओ = spinand_हटाओ,
पूर्ण;
module_spi_mem_driver(spinand_drv);

MODULE_DESCRIPTION("SPI NAND framework");
MODULE_AUTHOR("Peter Pan<peterpandong@micron.com>");
MODULE_LICENSE("GPL v2");
