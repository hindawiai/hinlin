<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/drivers/mmc/core/sdio_io.c
 *
 *  Copyright 2007-2008 Pierre Ossman
 */

#समावेश <linux/export.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_func.h>

#समावेश "sdio_ops.h"
#समावेश "core.h"
#समावेश "card.h"
#समावेश "host.h"

/**
 *	sdio_claim_host - exclusively claim a bus क्रम a certain SDIO function
 *	@func: SDIO function that will be accessed
 *
 *	Claim a bus क्रम a set of operations. The SDIO function given
 *	is used to figure out which bus is relevant.
 */
व्योम sdio_claim_host(काष्ठा sdio_func *func)
अणु
	अगर (WARN_ON(!func))
		वापस;

	mmc_claim_host(func->card->host);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_claim_host);

/**
 *	sdio_release_host - release a bus क्रम a certain SDIO function
 *	@func: SDIO function that was accessed
 *
 *	Release a bus, allowing others to claim the bus क्रम their
 *	operations.
 */
व्योम sdio_release_host(काष्ठा sdio_func *func)
अणु
	अगर (WARN_ON(!func))
		वापस;

	mmc_release_host(func->card->host);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_release_host);

/**
 *	sdio_enable_func - enables a SDIO function क्रम usage
 *	@func: SDIO function to enable
 *
 *	Powers up and activates a SDIO function so that रेजिस्टर
 *	access is possible.
 */
पूर्णांक sdio_enable_func(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर reg;
	अचिन्हित दीर्घ समयout;

	अगर (!func)
		वापस -EINVAL;

	pr_debug("SDIO: Enabling device %s...\n", sdio_func_id(func));

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IOEx, 0, &reg);
	अगर (ret)
		जाओ err;

	reg |= 1 << func->num;

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IOEx, reg, शून्य);
	अगर (ret)
		जाओ err;

	समयout = jअगरfies + msecs_to_jअगरfies(func->enable_समयout);

	जबतक (1) अणु
		ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IORx, 0, &reg);
		अगर (ret)
			जाओ err;
		अगर (reg & (1 << func->num))
			अवरोध;
		ret = -ETIME;
		अगर (समय_after(jअगरfies, समयout))
			जाओ err;
	पूर्ण

	pr_debug("SDIO: Enabled device %s\n", sdio_func_id(func));

	वापस 0;

err:
	pr_debug("SDIO: Failed to enable device %s\n", sdio_func_id(func));
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_enable_func);

/**
 *	sdio_disable_func - disable a SDIO function
 *	@func: SDIO function to disable
 *
 *	Powers करोwn and deactivates a SDIO function. Register access
 *	to this function will fail until the function is reenabled.
 */
पूर्णांक sdio_disable_func(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर reg;

	अगर (!func)
		वापस -EINVAL;

	pr_debug("SDIO: Disabling device %s...\n", sdio_func_id(func));

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IOEx, 0, &reg);
	अगर (ret)
		जाओ err;

	reg &= ~(1 << func->num);

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IOEx, reg, शून्य);
	अगर (ret)
		जाओ err;

	pr_debug("SDIO: Disabled device %s\n", sdio_func_id(func));

	वापस 0;

err:
	pr_debug("SDIO: Failed to disable device %s\n", sdio_func_id(func));
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_disable_func);

/**
 *	sdio_set_block_size - set the block size of an SDIO function
 *	@func: SDIO function to change
 *	@blksz: new block size or 0 to use the शेष.
 *
 *	The शेष block size is the largest supported by both the function
 *	and the host, with a maximum of 512 to ensure that arbitrarily sized
 *	data transfer use the optimal (least) number of commands.
 *
 *	A driver may call this to override the शेष block size set by the
 *	core. This can be used to set a block size greater than the maximum
 *	that reported by the card; it is the driver's responsibility to ensure
 *	it uses a value that the card supports.
 *
 *	Returns 0 on success, -EINVAL अगर the host करोes not support the
 *	requested block size, or -EIO (etc.) अगर one of the resultant FBR block
 *	size रेजिस्टर ग_लिखोs failed.
 *
 */
पूर्णांक sdio_set_block_size(काष्ठा sdio_func *func, अचिन्हित blksz)
अणु
	पूर्णांक ret;

	अगर (blksz > func->card->host->max_blk_size)
		वापस -EINVAL;

	अगर (blksz == 0) अणु
		blksz = min(func->max_blksize, func->card->host->max_blk_size);
		blksz = min(blksz, 512u);
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 1, 0,
		SDIO_FBR_BASE(func->num) + SDIO_FBR_BLKSIZE,
		blksz & 0xff, शून्य);
	अगर (ret)
		वापस ret;
	ret = mmc_io_rw_direct(func->card, 1, 0,
		SDIO_FBR_BASE(func->num) + SDIO_FBR_BLKSIZE + 1,
		(blksz >> 8) & 0xff, शून्य);
	अगर (ret)
		वापस ret;
	func->cur_blksize = blksz;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_set_block_size);

/*
 * Calculate the maximum byte mode transfer size
 */
अटल अंतरभूत अचिन्हित पूर्णांक sdio_max_byte_size(काष्ठा sdio_func *func)
अणु
	अचिन्हित mval =	func->card->host->max_blk_size;

	अगर (mmc_blksz_क्रम_byte_mode(func->card))
		mval = min(mval, func->cur_blksize);
	अन्यथा
		mval = min(mval, func->max_blksize);

	अगर (mmc_card_broken_byte_mode_512(func->card))
		वापस min(mval, 511u);

	वापस min(mval, 512u); /* maximum size क्रम byte mode */
पूर्ण

/*
 * This is legacy code, which needs to be re-worked some day. Basically we need
 * to take पूर्णांकo account the properties of the host, as to enable the SDIO func
 * driver layer to allocate optimal buffers.
 */
अटल अंतरभूत अचिन्हित पूर्णांक _sdio_align_size(अचिन्हित पूर्णांक sz)
अणु
	/*
	 * FIXME: We करोn't have a प्रणाली क्रम the controller to tell
	 * the core about its problems yet, so क्रम now we just 32-bit
	 * align the size.
	 */
	वापस ALIGN(sz, 4);
पूर्ण

/**
 *	sdio_align_size - pads a transfer size to a more optimal value
 *	@func: SDIO function
 *	@sz: original transfer size
 *
 *	Pads the original data size with a number of extra bytes in
 *	order to aव्योम controller bugs and/or perक्रमmance hits
 *	(e.g. some controllers revert to PIO क्रम certain sizes).
 *
 *	If possible, it will also adjust the size so that it can be
 *	handled in just a single request.
 *
 *	Returns the improved size, which might be unmodअगरied.
 */
अचिन्हित पूर्णांक sdio_align_size(काष्ठा sdio_func *func, अचिन्हित पूर्णांक sz)
अणु
	अचिन्हित पूर्णांक orig_sz;
	अचिन्हित पूर्णांक blk_sz, byte_sz;
	अचिन्हित chunk_sz;

	orig_sz = sz;

	/*
	 * Do a first check with the controller, in हाल it
	 * wants to increase the size up to a poपूर्णांक where it
	 * might need more than one block.
	 */
	sz = _sdio_align_size(sz);

	/*
	 * If we can still करो this with just a byte transfer, then
	 * we're करोne.
	 */
	अगर (sz <= sdio_max_byte_size(func))
		वापस sz;

	अगर (func->card->cccr.multi_block) अणु
		/*
		 * Check अगर the transfer is alपढ़ोy block aligned
		 */
		अगर ((sz % func->cur_blksize) == 0)
			वापस sz;

		/*
		 * Realign it so that it can be करोne with one request,
		 * and recheck अगर the controller still likes it.
		 */
		blk_sz = ((sz + func->cur_blksize - 1) /
			func->cur_blksize) * func->cur_blksize;
		blk_sz = _sdio_align_size(blk_sz);

		/*
		 * This value is only good अगर it is still just
		 * one request.
		 */
		अगर ((blk_sz % func->cur_blksize) == 0)
			वापस blk_sz;

		/*
		 * We failed to करो one request, but at least try to
		 * pad the reमुख्यder properly.
		 */
		byte_sz = _sdio_align_size(sz % func->cur_blksize);
		अगर (byte_sz <= sdio_max_byte_size(func)) अणु
			blk_sz = sz / func->cur_blksize;
			वापस blk_sz * func->cur_blksize + byte_sz;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We need multiple requests, so first check that the
		 * controller can handle the chunk size;
		 */
		chunk_sz = _sdio_align_size(sdio_max_byte_size(func));
		अगर (chunk_sz == sdio_max_byte_size(func)) अणु
			/*
			 * Fix up the size of the reमुख्यder (अगर any)
			 */
			byte_sz = orig_sz % chunk_sz;
			अगर (byte_sz) अणु
				byte_sz = _sdio_align_size(byte_sz);
			पूर्ण

			वापस (orig_sz / chunk_sz) * chunk_sz + byte_sz;
		पूर्ण
	पूर्ण

	/*
	 * The controller is simply incapable of transferring the size
	 * we want in decent manner, so just वापस the original size.
	 */
	वापस orig_sz;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_align_size);

/* Split an arbitrarily sized data transfer पूर्णांकo several
 * IO_RW_EXTENDED commands. */
अटल पूर्णांक sdio_io_rw_ext_helper(काष्ठा sdio_func *func, पूर्णांक ग_लिखो,
	अचिन्हित addr, पूर्णांक incr_addr, u8 *buf, अचिन्हित size)
अणु
	अचिन्हित reमुख्यder = size;
	अचिन्हित max_blocks;
	पूर्णांक ret;

	अगर (!func || (func->num > 7))
		वापस -EINVAL;

	/* Do the bulk of the transfer using block mode (अगर supported). */
	अगर (func->card->cccr.multi_block && (size > sdio_max_byte_size(func))) अणु
		/* Blocks per command is limited by host count, host transfer
		 * size and the maximum क्रम IO_RW_EXTENDED of 511 blocks. */
		max_blocks = min(func->card->host->max_blk_count, 511u);

		जबतक (reमुख्यder >= func->cur_blksize) अणु
			अचिन्हित blocks;

			blocks = reमुख्यder / func->cur_blksize;
			अगर (blocks > max_blocks)
				blocks = max_blocks;
			size = blocks * func->cur_blksize;

			ret = mmc_io_rw_extended(func->card, ग_लिखो,
				func->num, addr, incr_addr, buf,
				blocks, func->cur_blksize);
			अगर (ret)
				वापस ret;

			reमुख्यder -= size;
			buf += size;
			अगर (incr_addr)
				addr += size;
		पूर्ण
	पूर्ण

	/* Write the reमुख्यder using byte mode. */
	जबतक (reमुख्यder > 0) अणु
		size = min(reमुख्यder, sdio_max_byte_size(func));

		/* Indicate byte mode by setting "blocks" = 0 */
		ret = mmc_io_rw_extended(func->card, ग_लिखो, func->num, addr,
			 incr_addr, buf, 0, size);
		अगर (ret)
			वापस ret;

		reमुख्यder -= size;
		buf += size;
		अगर (incr_addr)
			addr += size;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	sdio_पढ़ोb - पढ़ो a single byte from a SDIO function
 *	@func: SDIO function to access
 *	@addr: address to पढ़ो
 *	@err_ret: optional status value from transfer
 *
 *	Reads a single byte from the address space of a given SDIO
 *	function. If there is a problem पढ़ोing the address, 0xff
 *	is वापसed and @err_ret will contain the error code.
 */
u8 sdio_पढ़ोb(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;
	u8 val;

	अगर (!func) अणु
		अगर (err_ret)
			*err_ret = -EINVAL;
		वापस 0xFF;
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 0, func->num, addr, 0, &val);
	अगर (err_ret)
		*err_ret = ret;
	अगर (ret)
		वापस 0xFF;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_पढ़ोb);

/**
 *	sdio_ग_लिखोb - ग_लिखो a single byte to a SDIO function
 *	@func: SDIO function to access
 *	@b: byte to ग_लिखो
 *	@addr: address to ग_लिखो to
 *	@err_ret: optional status value from transfer
 *
 *	Writes a single byte to the address space of a given SDIO
 *	function. @err_ret will contain the status of the actual
 *	transfer.
 */
व्योम sdio_ग_लिखोb(काष्ठा sdio_func *func, u8 b, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;

	अगर (!func) अणु
		अगर (err_ret)
			*err_ret = -EINVAL;
		वापस;
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 1, func->num, addr, b, शून्य);
	अगर (err_ret)
		*err_ret = ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_ग_लिखोb);

/**
 *	sdio_ग_लिखोb_पढ़ोb - ग_लिखो and पढ़ो a byte from SDIO function
 *	@func: SDIO function to access
 *	@ग_लिखो_byte: byte to ग_लिखो
 *	@addr: address to ग_लिखो to
 *	@err_ret: optional status value from transfer
 *
 *	Perक्रमms a RAW (Read after Write) operation as defined by SDIO spec -
 *	single byte is written to address space of a given SDIO function and
 *	response is पढ़ो back from the same address, both using single request.
 *	If there is a problem with the operation, 0xff is वापसed and
 *	@err_ret will contain the error code.
 */
u8 sdio_ग_लिखोb_पढ़ोb(काष्ठा sdio_func *func, u8 ग_लिखो_byte,
	अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;
	u8 val;

	ret = mmc_io_rw_direct(func->card, 1, func->num, addr,
			ग_लिखो_byte, &val);
	अगर (err_ret)
		*err_ret = ret;
	अगर (ret)
		वापस 0xff;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_ग_लिखोb_पढ़ोb);

/**
 *	sdio_स_नकल_fromio - पढ़ो a chunk of memory from a SDIO function
 *	@func: SDIO function to access
 *	@dst: buffer to store the data
 *	@addr: address to begin पढ़ोing from
 *	@count: number of bytes to पढ़ो
 *
 *	Reads from the address space of a given SDIO function. Return
 *	value indicates अगर the transfer succeeded or not.
 */
पूर्णांक sdio_स_नकल_fromio(काष्ठा sdio_func *func, व्योम *dst,
	अचिन्हित पूर्णांक addr, पूर्णांक count)
अणु
	वापस sdio_io_rw_ext_helper(func, 0, addr, 1, dst, count);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_स_नकल_fromio);

/**
 *	sdio_स_नकल_toio - ग_लिखो a chunk of memory to a SDIO function
 *	@func: SDIO function to access
 *	@addr: address to start writing to
 *	@src: buffer that contains the data to ग_लिखो
 *	@count: number of bytes to ग_लिखो
 *
 *	Writes to the address space of a given SDIO function. Return
 *	value indicates अगर the transfer succeeded or not.
 */
पूर्णांक sdio_स_नकल_toio(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr,
	व्योम *src, पूर्णांक count)
अणु
	वापस sdio_io_rw_ext_helper(func, 1, addr, 1, src, count);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_स_नकल_toio);

/**
 *	sdio_पढ़ोsb - पढ़ो from a FIFO on a SDIO function
 *	@func: SDIO function to access
 *	@dst: buffer to store the data
 *	@addr: address of (single byte) FIFO
 *	@count: number of bytes to पढ़ो
 *
 *	Reads from the specअगरied FIFO of a given SDIO function. Return
 *	value indicates अगर the transfer succeeded or not.
 */
पूर्णांक sdio_पढ़ोsb(काष्ठा sdio_func *func, व्योम *dst, अचिन्हित पूर्णांक addr,
	पूर्णांक count)
अणु
	वापस sdio_io_rw_ext_helper(func, 0, addr, 0, dst, count);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_पढ़ोsb);

/**
 *	sdio_ग_लिखोsb - ग_लिखो to a FIFO of a SDIO function
 *	@func: SDIO function to access
 *	@addr: address of (single byte) FIFO
 *	@src: buffer that contains the data to ग_लिखो
 *	@count: number of bytes to ग_लिखो
 *
 *	Writes to the specअगरied FIFO of a given SDIO function. Return
 *	value indicates अगर the transfer succeeded or not.
 */
पूर्णांक sdio_ग_लिखोsb(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, व्योम *src,
	पूर्णांक count)
अणु
	वापस sdio_io_rw_ext_helper(func, 1, addr, 0, src, count);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_ग_लिखोsb);

/**
 *	sdio_पढ़ोw - पढ़ो a 16 bit पूर्णांकeger from a SDIO function
 *	@func: SDIO function to access
 *	@addr: address to पढ़ो
 *	@err_ret: optional status value from transfer
 *
 *	Reads a 16 bit पूर्णांकeger from the address space of a given SDIO
 *	function. If there is a problem पढ़ोing the address, 0xffff
 *	is वापसed and @err_ret will contain the error code.
 */
u16 sdio_पढ़ोw(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;

	ret = sdio_स_नकल_fromio(func, func->पंचांगpbuf, addr, 2);
	अगर (err_ret)
		*err_ret = ret;
	अगर (ret)
		वापस 0xFFFF;

	वापस le16_to_cpup((__le16 *)func->पंचांगpbuf);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_पढ़ोw);

/**
 *	sdio_ग_लिखोw - ग_लिखो a 16 bit पूर्णांकeger to a SDIO function
 *	@func: SDIO function to access
 *	@b: पूर्णांकeger to ग_लिखो
 *	@addr: address to ग_लिखो to
 *	@err_ret: optional status value from transfer
 *
 *	Writes a 16 bit पूर्णांकeger to the address space of a given SDIO
 *	function. @err_ret will contain the status of the actual
 *	transfer.
 */
व्योम sdio_ग_लिखोw(काष्ठा sdio_func *func, u16 b, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;

	*(__le16 *)func->पंचांगpbuf = cpu_to_le16(b);

	ret = sdio_स_नकल_toio(func, addr, func->पंचांगpbuf, 2);
	अगर (err_ret)
		*err_ret = ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_ग_लिखोw);

/**
 *	sdio_पढ़ोl - पढ़ो a 32 bit पूर्णांकeger from a SDIO function
 *	@func: SDIO function to access
 *	@addr: address to पढ़ो
 *	@err_ret: optional status value from transfer
 *
 *	Reads a 32 bit पूर्णांकeger from the address space of a given SDIO
 *	function. If there is a problem पढ़ोing the address,
 *	0xffffffff is वापसed and @err_ret will contain the error
 *	code.
 */
u32 sdio_पढ़ोl(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;

	ret = sdio_स_नकल_fromio(func, func->पंचांगpbuf, addr, 4);
	अगर (err_ret)
		*err_ret = ret;
	अगर (ret)
		वापस 0xFFFFFFFF;

	वापस le32_to_cpup((__le32 *)func->पंचांगpbuf);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_पढ़ोl);

/**
 *	sdio_ग_लिखोl - ग_लिखो a 32 bit पूर्णांकeger to a SDIO function
 *	@func: SDIO function to access
 *	@b: पूर्णांकeger to ग_लिखो
 *	@addr: address to ग_लिखो to
 *	@err_ret: optional status value from transfer
 *
 *	Writes a 32 bit पूर्णांकeger to the address space of a given SDIO
 *	function. @err_ret will contain the status of the actual
 *	transfer.
 */
व्योम sdio_ग_लिखोl(काष्ठा sdio_func *func, u32 b, अचिन्हित पूर्णांक addr, पूर्णांक *err_ret)
अणु
	पूर्णांक ret;

	*(__le32 *)func->पंचांगpbuf = cpu_to_le32(b);

	ret = sdio_स_नकल_toio(func, addr, func->पंचांगpbuf, 4);
	अगर (err_ret)
		*err_ret = ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_ग_लिखोl);

/**
 *	sdio_f0_पढ़ोb - पढ़ो a single byte from SDIO function 0
 *	@func: an SDIO function of the card
 *	@addr: address to पढ़ो
 *	@err_ret: optional status value from transfer
 *
 *	Reads a single byte from the address space of SDIO function 0.
 *	If there is a problem पढ़ोing the address, 0xff is वापसed
 *	and @err_ret will contain the error code.
 */
अचिन्हित अक्षर sdio_f0_पढ़ोb(काष्ठा sdio_func *func, अचिन्हित पूर्णांक addr,
	पूर्णांक *err_ret)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर val;

	अगर (!func) अणु
		अगर (err_ret)
			*err_ret = -EINVAL;
		वापस 0xFF;
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 0, 0, addr, 0, &val);
	अगर (err_ret)
		*err_ret = ret;
	अगर (ret)
		वापस 0xFF;

	वापस val;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_f0_पढ़ोb);

/**
 *	sdio_f0_ग_लिखोb - ग_लिखो a single byte to SDIO function 0
 *	@func: an SDIO function of the card
 *	@b: byte to ग_लिखो
 *	@addr: address to ग_लिखो to
 *	@err_ret: optional status value from transfer
 *
 *	Writes a single byte to the address space of SDIO function 0.
 *	@err_ret will contain the status of the actual transfer.
 *
 *	Only ग_लिखोs to the venकरोr specअगरic CCCR रेजिस्टरs (0xF0 -
 *	0xFF) are permiited; @err_ret will be set to -EINVAL क्रम *
 *	ग_लिखोs outside this range.
 */
व्योम sdio_f0_ग_लिखोb(काष्ठा sdio_func *func, अचिन्हित अक्षर b, अचिन्हित पूर्णांक addr,
	पूर्णांक *err_ret)
अणु
	पूर्णांक ret;

	अगर (!func) अणु
		अगर (err_ret)
			*err_ret = -EINVAL;
		वापस;
	पूर्ण

	अगर ((addr < 0xF0 || addr > 0xFF) && (!mmc_card_lenient_fn0(func->card))) अणु
		अगर (err_ret)
			*err_ret = -EINVAL;
		वापस;
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 1, 0, addr, b, शून्य);
	अगर (err_ret)
		*err_ret = ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_f0_ग_लिखोb);

/**
 *	sdio_get_host_pm_caps - get host घातer management capabilities
 *	@func: SDIO function attached to host
 *
 *	Returns a capability biपंचांगask corresponding to घातer management
 *	features supported by the host controller that the card function
 *	might rely upon during a प्रणाली suspend.  The host करोesn't need
 *	to be claimed, nor the function active, क्रम this inक्रमmation to be
 *	obtained.
 */
mmc_pm_flag_t sdio_get_host_pm_caps(काष्ठा sdio_func *func)
अणु
	अगर (!func)
		वापस 0;

	वापस func->card->host->pm_caps;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_get_host_pm_caps);

/**
 *	sdio_set_host_pm_flags - set wanted host घातer management capabilities
 *	@func: SDIO function attached to host
 *	@flags: Power Management flags to set
 *
 *	Set a capability biपंचांगask corresponding to wanted host controller
 *	घातer management features क्रम the upcoming suspend state.
 *	This must be called, अगर needed, each समय the suspend method of
 *	the function driver is called, and must contain only bits that
 *	were वापसed by sdio_get_host_pm_caps().
 *	The host करोesn't need to be claimed, nor the function active,
 *	क्रम this inक्रमmation to be set.
 */
पूर्णांक sdio_set_host_pm_flags(काष्ठा sdio_func *func, mmc_pm_flag_t flags)
अणु
	काष्ठा mmc_host *host;

	अगर (!func)
		वापस -EINVAL;

	host = func->card->host;

	अगर (flags & ~host->pm_caps)
		वापस -EINVAL;

	/* function suspend methods are serialized, hence no lock needed */
	host->pm_flags |= flags;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_set_host_pm_flags);

/**
 *	sdio_retune_crc_disable - temporarily disable retuning on CRC errors
 *	@func: SDIO function attached to host
 *
 *	If the SDIO card is known to be in a state where it might produce
 *	CRC errors on the bus in response to commands (like अगर we know it is
 *	transitioning between घातer states), an SDIO function driver can
 *	call this function to temporarily disable the SD/MMC core behavior of
 *	triggering an स्वतःmatic retuning.
 *
 *	This function should be called जबतक the host is claimed and the host
 *	should reमुख्य claimed until sdio_retune_crc_enable() is called.
 *	Specअगरically, the expected sequence of calls is:
 *	- sdio_claim_host()
 *	- sdio_retune_crc_disable()
 *	- some number of calls like sdio_ग_लिखोb() and sdio_पढ़ोb()
 *	- sdio_retune_crc_enable()
 *	- sdio_release_host()
 */
व्योम sdio_retune_crc_disable(काष्ठा sdio_func *func)
अणु
	func->card->host->retune_crc_disable = true;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_retune_crc_disable);

/**
 *	sdio_retune_crc_enable - re-enable retuning on CRC errors
 *	@func: SDIO function attached to host
 *
 *	This is the compement to sdio_retune_crc_disable().
 */
व्योम sdio_retune_crc_enable(काष्ठा sdio_func *func)
अणु
	func->card->host->retune_crc_disable = false;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_retune_crc_enable);

/**
 *	sdio_retune_hold_now - start deferring retuning requests till release
 *	@func: SDIO function attached to host
 *
 *	This function can be called अगर it's currently a bad समय to करो
 *	a retune of the SDIO card.  Retune requests made during this समय
 *	will be held and we'll actually करो the retune someसमय after the
 *	release.
 *
 *	This function could be useful अगर an SDIO card is in a घातer state
 *	where it can respond to a small subset of commands that करोesn't
 *	include the retuning command.  Care should be taken when using
 *	this function since (presumably) the retuning request we might be
 *	deferring was made क्रम a good reason.
 *
 *	This function should be called जबतक the host is claimed.
 */
व्योम sdio_retune_hold_now(काष्ठा sdio_func *func)
अणु
	mmc_retune_hold_now(func->card->host);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_retune_hold_now);

/**
 *	sdio_retune_release - संकेत that it's OK to retune now
 *	@func: SDIO function attached to host
 *
 *	This is the complement to sdio_retune_hold_now().  Calling this
 *	function won't make a retune happen right away but will allow
 *	them to be scheduled normally.
 *
 *	This function should be called जबतक the host is claimed.
 */
व्योम sdio_retune_release(काष्ठा sdio_func *func)
अणु
	mmc_retune_release(func->card->host);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_retune_release);
