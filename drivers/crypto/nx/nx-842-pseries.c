<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम IBM Power 842 compression accelerator
 *
 * Copyright (C) IBM Corporation, 2012
 *
 * Authors: Robert Jennings <rcj@linux.vnet.ibm.com>
 *          Seth Jennings <sjenning@linux.vnet.ibm.com>
 */

#समावेश <यंत्र/vपन.स>

#समावेश "nx-842.h"
#समावेश "nx_csbcpb.h" /* काष्ठा nx_csbcpb */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Robert Jennings <rcj@linux.vnet.ibm.com>");
MODULE_DESCRIPTION("842 H/W Compression driver for IBM Power processors");
MODULE_ALIAS_CRYPTO("842");
MODULE_ALIAS_CRYPTO("842-nx");

अटल काष्ठा nx842_स्थिरraपूर्णांकs nx842_pseries_स्थिरraपूर्णांकs = अणु
	.alignment =	DDE_BUFFER_ALIGN,
	.multiple =	DDE_BUFFER_LAST_MULT,
	.minimum =	DDE_BUFFER_LAST_MULT,
	.maximum =	PAGE_SIZE, /* dynamic, max_sync_size */
पूर्ण;

अटल पूर्णांक check_स्थिरraपूर्णांकs(अचिन्हित दीर्घ buf, अचिन्हित पूर्णांक *len, bool in)
अणु
	अगर (!IS_ALIGNED(buf, nx842_pseries_स्थिरraपूर्णांकs.alignment)) अणु
		pr_debug("%s buffer 0x%lx not aligned to 0x%x\n",
			 in ? "input" : "output", buf,
			 nx842_pseries_स्थिरraपूर्णांकs.alignment);
		वापस -EINVAL;
	पूर्ण
	अगर (*len % nx842_pseries_स्थिरraपूर्णांकs.multiple) अणु
		pr_debug("%s buffer len 0x%x not multiple of 0x%x\n",
			 in ? "input" : "output", *len,
			 nx842_pseries_स्थिरraपूर्णांकs.multiple);
		अगर (in)
			वापस -EINVAL;
		*len = round_करोwn(*len, nx842_pseries_स्थिरraपूर्णांकs.multiple);
	पूर्ण
	अगर (*len < nx842_pseries_स्थिरraपूर्णांकs.minimum) अणु
		pr_debug("%s buffer len 0x%x under minimum 0x%x\n",
			 in ? "input" : "output", *len,
			 nx842_pseries_स्थिरraपूर्णांकs.minimum);
		वापस -EINVAL;
	पूर्ण
	अगर (*len > nx842_pseries_स्थिरraपूर्णांकs.maximum) अणु
		pr_debug("%s buffer len 0x%x over maximum 0x%x\n",
			 in ? "input" : "output", *len,
			 nx842_pseries_स्थिरraपूर्णांकs.maximum);
		अगर (in)
			वापस -EINVAL;
		*len = nx842_pseries_स्थिरraपूर्णांकs.maximum;
	पूर्ण
	वापस 0;
पूर्ण

/* I assume we need to align the CSB? */
#घोषणा WORKMEM_ALIGN	(256)

काष्ठा nx842_workmem अणु
	/* scatterlist */
	अक्षर slin[4096];
	अक्षर slout[4096];
	/* coprocessor status/parameter block */
	काष्ठा nx_csbcpb csbcpb;

	अक्षर padding[WORKMEM_ALIGN];
पूर्ण __aligned(WORKMEM_ALIGN);

/* Macros क्रम fields within nx_csbcpb */
/* Check the valid bit within the csbcpb valid field */
#घोषणा NX842_CSBCBP_VALID_CHK(x) (x & BIT_MASK(7))

/* CE macros operate on the completion_extension field bits in the csbcpb.
 * CE0 0=full completion, 1=partial completion
 * CE1 0=CE0 indicates completion, 1=termination (output may be modअगरied)
 * CE2 0=processed_bytes is source bytes, 1=processed_bytes is target bytes */
#घोषणा NX842_CSBCPB_CE0(x)	(x & BIT_MASK(7))
#घोषणा NX842_CSBCPB_CE1(x)	(x & BIT_MASK(6))
#घोषणा NX842_CSBCPB_CE2(x)	(x & BIT_MASK(5))

/* The NX unit accepts data only on 4K page boundaries */
#घोषणा NX842_HW_PAGE_SIZE	(4096)
#घोषणा NX842_HW_PAGE_MASK	(~(NX842_HW_PAGE_SIZE-1))

काष्ठा ibm_nx842_counters अणु
	atomic64_t comp_complete;
	atomic64_t comp_failed;
	atomic64_t decomp_complete;
	atomic64_t decomp_failed;
	atomic64_t swdecomp;
	atomic64_t comp_बार[32];
	atomic64_t decomp_बार[32];
पूर्ण;

अटल काष्ठा nx842_devdata अणु
	काष्ठा vio_dev *vdev;
	काष्ठा device *dev;
	काष्ठा ibm_nx842_counters *counters;
	अचिन्हित पूर्णांक max_sg_len;
	अचिन्हित पूर्णांक max_sync_size;
	अचिन्हित पूर्णांक max_sync_sg;
पूर्ण __rcu *devdata;
अटल DEFINE_SPINLOCK(devdata_mutex);

#घोषणा NX842_COUNTER_INC(_x) \
अटल अंतरभूत व्योम nx842_inc_##_x( \
	स्थिर काष्ठा nx842_devdata *dev) अणु \
	अगर (dev) \
		atomic64_inc(&dev->counters->_x); \
पूर्ण
NX842_COUNTER_INC(comp_complete);
NX842_COUNTER_INC(comp_failed);
NX842_COUNTER_INC(decomp_complete);
NX842_COUNTER_INC(decomp_failed);
NX842_COUNTER_INC(swdecomp);

#घोषणा NX842_HIST_SLOTS 16

अटल व्योम ibm_nx842_incr_hist(atomic64_t *बार, अचिन्हित पूर्णांक समय)
अणु
	पूर्णांक bucket = fls(समय);

	अगर (bucket)
		bucket = min((NX842_HIST_SLOTS - 1), bucket - 1);

	atomic64_inc(&बार[bucket]);
पूर्ण

/* NX unit operation flags */
#घोषणा NX842_OP_COMPRESS	0x0
#घोषणा NX842_OP_CRC		0x1
#घोषणा NX842_OP_DECOMPRESS	0x2
#घोषणा NX842_OP_COMPRESS_CRC   (NX842_OP_COMPRESS | NX842_OP_CRC)
#घोषणा NX842_OP_DECOMPRESS_CRC (NX842_OP_DECOMPRESS | NX842_OP_CRC)
#घोषणा NX842_OP_ASYNC		(1<<23)
#घोषणा NX842_OP_NOTIFY		(1<<22)
#घोषणा NX842_OP_NOTIFY_INT(x)	((x & 0xff)<<8)

अटल अचिन्हित दीर्घ nx842_get_desired_dma(काष्ठा vio_dev *viodev)
अणु
	/* No use of DMA mappings within the driver. */
	वापस 0;
पूर्ण

काष्ठा nx842_slentry अणु
	__be64 ptr; /* Real address (use __pa()) */
	__be64 len;
पूर्ण;

/* pHyp scatterlist entry */
काष्ठा nx842_scatterlist अणु
	पूर्णांक entry_nr; /* number of slentries */
	काष्ठा nx842_slentry *entries; /* ptr to array of slentries */
पूर्ण;

/* Does not include माप(entry_nr) in the size */
अटल अंतरभूत अचिन्हित दीर्घ nx842_get_scatterlist_size(
				काष्ठा nx842_scatterlist *sl)
अणु
	वापस sl->entry_nr * माप(काष्ठा nx842_slentry);
पूर्ण

अटल पूर्णांक nx842_build_scatterlist(अचिन्हित दीर्घ buf, पूर्णांक len,
			काष्ठा nx842_scatterlist *sl)
अणु
	अचिन्हित दीर्घ entrylen;
	काष्ठा nx842_slentry *entry;

	sl->entry_nr = 0;

	entry = sl->entries;
	जबतक (len) अणु
		entry->ptr = cpu_to_be64(nx842_get_pa((व्योम *)buf));
		entrylen = min_t(पूर्णांक, len,
				 LEN_ON_SIZE(buf, NX842_HW_PAGE_SIZE));
		entry->len = cpu_to_be64(entrylen);

		len -= entrylen;
		buf += entrylen;

		sl->entry_nr++;
		entry++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nx842_validate_result(काष्ठा device *dev,
	काष्ठा cop_status_block *csb)
अणु
	/* The csb must be valid after वापसing from vio_h_cop_sync */
	अगर (!NX842_CSBCBP_VALID_CHK(csb->valid)) अणु
		dev_err(dev, "%s: cspcbp not valid upon completion.\n",
				__func__);
		dev_dbg(dev, "valid:0x%02x cs:0x%02x cc:0x%02x ce:0x%02x\n",
				csb->valid,
				csb->crb_seq_number,
				csb->completion_code,
				csb->completion_extension);
		dev_dbg(dev, "processed_bytes:%d address:0x%016lx\n",
				be32_to_cpu(csb->processed_byte_count),
				(अचिन्हित दीर्घ)be64_to_cpu(csb->address));
		वापस -EIO;
	पूर्ण

	/* Check वापस values from the hardware in the CSB */
	चयन (csb->completion_code) अणु
	हाल 0:	/* Completed without error */
		अवरोध;
	हाल 64: /* Compression ok, but output larger than input */
		dev_dbg(dev, "%s: output size larger than input size\n",
					__func__);
		अवरोध;
	हाल 13: /* Output buffer too small */
		dev_dbg(dev, "%s: Out of space in output buffer\n",
					__func__);
		वापस -ENOSPC;
	हाल 65: /* Calculated CRC करोesn't match the passed value */
		dev_dbg(dev, "%s: CRC mismatch for decompression\n",
					__func__);
		वापस -EINVAL;
	हाल 66: /* Input data contains an illegal ढाँचा field */
	हाल 67: /* Template indicates data past the end of the input stream */
		dev_dbg(dev, "%s: Bad data for decompression (code:%d)\n",
					__func__, csb->completion_code);
		वापस -EINVAL;
	शेष:
		dev_dbg(dev, "%s: Unspecified error (code:%d)\n",
					__func__, csb->completion_code);
		वापस -EIO;
	पूर्ण

	/* Hardware sanity check */
	अगर (!NX842_CSBCPB_CE2(csb->completion_extension)) अणु
		dev_err(dev, "%s: No error returned by hardware, but "
				"data returned is unusable, contact support.\n"
				"(Additional info: csbcbp->processed bytes "
				"does not specify processed bytes for the "
				"target buffer.)\n", __func__);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * nx842_pseries_compress - Compress data using the 842 algorithm
 *
 * Compression provide by the NX842 coprocessor on IBM Power प्रणालीs.
 * The input buffer is compressed and the result is stored in the
 * provided output buffer.
 *
 * Upon वापस from this function @outlen contains the length of the
 * compressed data.  If there is an error then @outlen will be 0 and an
 * error will be specअगरied by the वापस code from this function.
 *
 * @in: Poपूर्णांकer to input buffer
 * @inlen: Length of input buffer
 * @out: Poपूर्णांकer to output buffer
 * @outlen: Length of output buffer
 * @wrkmem: ptr to buffer क्रम working memory, size determined by
 *          nx842_pseries_driver.workmem_size
 *
 * Returns:
 *   0		Success, output of length @outlen stored in the buffer at @out
 *   -ENOMEM	Unable to allocate पूर्णांकernal buffers
 *   -ENOSPC	Output buffer is to small
 *   -EIO	Internal error
 *   -ENODEV	Hardware unavailable
 */
अटल पूर्णांक nx842_pseries_compress(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
				  अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *outlen,
				  व्योम *wmem)
अणु
	काष्ठा nx842_devdata *local_devdata;
	काष्ठा device *dev = शून्य;
	काष्ठा nx842_workmem *workmem;
	काष्ठा nx842_scatterlist slin, slout;
	काष्ठा nx_csbcpb *csbcpb;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ inbuf, outbuf;
	काष्ठा vio_pfo_op op = अणु
		.करोne = शून्य,
		.handle = 0,
		.समयout = 0,
	पूर्ण;
	अचिन्हित दीर्घ start = get_tb();

	inbuf = (अचिन्हित दीर्घ)in;
	अगर (check_स्थिरraपूर्णांकs(inbuf, &inlen, true))
		वापस -EINVAL;

	outbuf = (अचिन्हित दीर्घ)out;
	अगर (check_स्थिरraपूर्णांकs(outbuf, outlen, false))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	local_devdata = rcu_dereference(devdata);
	अगर (!local_devdata || !local_devdata->dev) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	dev = local_devdata->dev;

	/* Init scatterlist */
	workmem = PTR_ALIGN(wmem, WORKMEM_ALIGN);
	slin.entries = (काष्ठा nx842_slentry *)workmem->slin;
	slout.entries = (काष्ठा nx842_slentry *)workmem->slout;

	/* Init operation */
	op.flags = NX842_OP_COMPRESS_CRC;
	csbcpb = &workmem->csbcpb;
	स_रखो(csbcpb, 0, माप(*csbcpb));
	op.csbcpb = nx842_get_pa(csbcpb);

	अगर ((inbuf & NX842_HW_PAGE_MASK) ==
	    ((inbuf + inlen - 1) & NX842_HW_PAGE_MASK)) अणु
		/* Create direct DDE */
		op.in = nx842_get_pa((व्योम *)inbuf);
		op.inlen = inlen;
	पूर्ण अन्यथा अणु
		/* Create indirect DDE (scatterlist) */
		nx842_build_scatterlist(inbuf, inlen, &slin);
		op.in = nx842_get_pa(slin.entries);
		op.inlen = -nx842_get_scatterlist_size(&slin);
	पूर्ण

	अगर ((outbuf & NX842_HW_PAGE_MASK) ==
	    ((outbuf + *outlen - 1) & NX842_HW_PAGE_MASK)) अणु
		/* Create direct DDE */
		op.out = nx842_get_pa((व्योम *)outbuf);
		op.outlen = *outlen;
	पूर्ण अन्यथा अणु
		/* Create indirect DDE (scatterlist) */
		nx842_build_scatterlist(outbuf, *outlen, &slout);
		op.out = nx842_get_pa(slout.entries);
		op.outlen = -nx842_get_scatterlist_size(&slout);
	पूर्ण

	dev_dbg(dev, "%s: op.in %lx op.inlen %ld op.out %lx op.outlen %ld\n",
		__func__, (अचिन्हित दीर्घ)op.in, (दीर्घ)op.inlen,
		(अचिन्हित दीर्घ)op.out, (दीर्घ)op.outlen);

	/* Send request to pHyp */
	ret = vio_h_cop_sync(local_devdata->vdev, &op);

	/* Check क्रम pHyp error */
	अगर (ret) अणु
		dev_dbg(dev, "%s: vio_h_cop_sync error (ret=%d, hret=%ld)\n",
			__func__, ret, op.hcall_err);
		ret = -EIO;
		जाओ unlock;
	पूर्ण

	/* Check क्रम hardware error */
	ret = nx842_validate_result(dev, &csbcpb->csb);
	अगर (ret)
		जाओ unlock;

	*outlen = be32_to_cpu(csbcpb->csb.processed_byte_count);
	dev_dbg(dev, "%s: processed_bytes=%d\n", __func__, *outlen);

unlock:
	अगर (ret)
		nx842_inc_comp_failed(local_devdata);
	अन्यथा अणु
		nx842_inc_comp_complete(local_devdata);
		ibm_nx842_incr_hist(local_devdata->counters->comp_बार,
			(get_tb() - start) / tb_ticks_per_usec);
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * nx842_pseries_decompress - Decompress data using the 842 algorithm
 *
 * Decompression provide by the NX842 coprocessor on IBM Power प्रणालीs.
 * The input buffer is decompressed and the result is stored in the
 * provided output buffer.  The size allocated to the output buffer is
 * provided by the caller of this function in @outlen.  Upon वापस from
 * this function @outlen contains the length of the decompressed data.
 * If there is an error then @outlen will be 0 and an error will be
 * specअगरied by the वापस code from this function.
 *
 * @in: Poपूर्णांकer to input buffer
 * @inlen: Length of input buffer
 * @out: Poपूर्णांकer to output buffer
 * @outlen: Length of output buffer
 * @wrkmem: ptr to buffer क्रम working memory, size determined by
 *          nx842_pseries_driver.workmem_size
 *
 * Returns:
 *   0		Success, output of length @outlen stored in the buffer at @out
 *   -ENODEV	Hardware decompression device is unavailable
 *   -ENOMEM	Unable to allocate पूर्णांकernal buffers
 *   -ENOSPC	Output buffer is to small
 *   -EINVAL	Bad input data encountered when attempting decompress
 *   -EIO	Internal error
 */
अटल पूर्णांक nx842_pseries_decompress(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
				    अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *outlen,
				    व्योम *wmem)
अणु
	काष्ठा nx842_devdata *local_devdata;
	काष्ठा device *dev = शून्य;
	काष्ठा nx842_workmem *workmem;
	काष्ठा nx842_scatterlist slin, slout;
	काष्ठा nx_csbcpb *csbcpb;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ inbuf, outbuf;
	काष्ठा vio_pfo_op op = अणु
		.करोne = शून्य,
		.handle = 0,
		.समयout = 0,
	पूर्ण;
	अचिन्हित दीर्घ start = get_tb();

	/* Ensure page alignment and size */
	inbuf = (अचिन्हित दीर्घ)in;
	अगर (check_स्थिरraपूर्णांकs(inbuf, &inlen, true))
		वापस -EINVAL;

	outbuf = (अचिन्हित दीर्घ)out;
	अगर (check_स्थिरraपूर्णांकs(outbuf, outlen, false))
		वापस -EINVAL;

	rcu_पढ़ो_lock();
	local_devdata = rcu_dereference(devdata);
	अगर (!local_devdata || !local_devdata->dev) अणु
		rcu_पढ़ो_unlock();
		वापस -ENODEV;
	पूर्ण
	dev = local_devdata->dev;

	workmem = PTR_ALIGN(wmem, WORKMEM_ALIGN);

	/* Init scatterlist */
	slin.entries = (काष्ठा nx842_slentry *)workmem->slin;
	slout.entries = (काष्ठा nx842_slentry *)workmem->slout;

	/* Init operation */
	op.flags = NX842_OP_DECOMPRESS_CRC;
	csbcpb = &workmem->csbcpb;
	स_रखो(csbcpb, 0, माप(*csbcpb));
	op.csbcpb = nx842_get_pa(csbcpb);

	अगर ((inbuf & NX842_HW_PAGE_MASK) ==
	    ((inbuf + inlen - 1) & NX842_HW_PAGE_MASK)) अणु
		/* Create direct DDE */
		op.in = nx842_get_pa((व्योम *)inbuf);
		op.inlen = inlen;
	पूर्ण अन्यथा अणु
		/* Create indirect DDE (scatterlist) */
		nx842_build_scatterlist(inbuf, inlen, &slin);
		op.in = nx842_get_pa(slin.entries);
		op.inlen = -nx842_get_scatterlist_size(&slin);
	पूर्ण

	अगर ((outbuf & NX842_HW_PAGE_MASK) ==
	    ((outbuf + *outlen - 1) & NX842_HW_PAGE_MASK)) अणु
		/* Create direct DDE */
		op.out = nx842_get_pa((व्योम *)outbuf);
		op.outlen = *outlen;
	पूर्ण अन्यथा अणु
		/* Create indirect DDE (scatterlist) */
		nx842_build_scatterlist(outbuf, *outlen, &slout);
		op.out = nx842_get_pa(slout.entries);
		op.outlen = -nx842_get_scatterlist_size(&slout);
	पूर्ण

	dev_dbg(dev, "%s: op.in %lx op.inlen %ld op.out %lx op.outlen %ld\n",
		__func__, (अचिन्हित दीर्घ)op.in, (दीर्घ)op.inlen,
		(अचिन्हित दीर्घ)op.out, (दीर्घ)op.outlen);

	/* Send request to pHyp */
	ret = vio_h_cop_sync(local_devdata->vdev, &op);

	/* Check क्रम pHyp error */
	अगर (ret) अणु
		dev_dbg(dev, "%s: vio_h_cop_sync error (ret=%d, hret=%ld)\n",
			__func__, ret, op.hcall_err);
		जाओ unlock;
	पूर्ण

	/* Check क्रम hardware error */
	ret = nx842_validate_result(dev, &csbcpb->csb);
	अगर (ret)
		जाओ unlock;

	*outlen = be32_to_cpu(csbcpb->csb.processed_byte_count);

unlock:
	अगर (ret)
		/* decompress fail */
		nx842_inc_decomp_failed(local_devdata);
	अन्यथा अणु
		nx842_inc_decomp_complete(local_devdata);
		ibm_nx842_incr_hist(local_devdata->counters->decomp_बार,
			(get_tb() - start) / tb_ticks_per_usec);
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस ret;
पूर्ण

/**
 * nx842_OF_set_शेषs -- Set शेष (disabled) values क्रम devdata
 *
 * @devdata - काष्ठा nx842_devdata to update
 *
 * Returns:
 *  0 on success
 *  -ENOENT अगर @devdata ptr is शून्य
 */
अटल पूर्णांक nx842_OF_set_शेषs(काष्ठा nx842_devdata *devdata)
अणु
	अगर (devdata) अणु
		devdata->max_sync_size = 0;
		devdata->max_sync_sg = 0;
		devdata->max_sg_len = 0;
		वापस 0;
	पूर्ण अन्यथा
		वापस -ENOENT;
पूर्ण

/**
 * nx842_OF_upd_status -- Check the device info from OF status prop
 *
 * The status property indicates अगर the accelerator is enabled.  If the
 * device is in the OF tree it indicates that the hardware is present.
 * The status field indicates अगर the device is enabled when the status
 * is 'okay'.  Otherwise the device driver will be disabled.
 *
 * @prop - काष्ठा property poपूर्णांक containing the maxsyncop क्रम the update
 *
 * Returns:
 *  0 - Device is available
 *  -ENODEV - Device is not available
 */
अटल पूर्णांक nx842_OF_upd_status(काष्ठा property *prop)
अणु
	स्थिर अक्षर *status = (स्थिर अक्षर *)prop->value;

	अगर (!म_भेदन(status, "okay", (माप_प्रकार)prop->length))
		वापस 0;
	अगर (!म_भेदन(status, "disabled", (माप_प्रकार)prop->length))
		वापस -ENODEV;
	dev_info(devdata->dev, "%s: unknown status '%s'\n", __func__, status);

	वापस -EINVAL;
पूर्ण

/**
 * nx842_OF_upd_maxsglen -- Update the device info from OF maxsglen prop
 *
 * Definition of the 'ibm,max-sg-len' OF property:
 *  This field indicates the maximum byte length of a scatter list
 *  क्रम the platक्रमm facility. It is a single cell encoded as with encode-पूर्णांक.
 *
 * Example:
 *  # od -x ibm,max-sg-len
 *  0000000 0000 0ff0
 *
 *  In this example, the maximum byte length of a scatter list is
 *  0x0ff0 (4,080).
 *
 * @devdata - काष्ठा nx842_devdata to update
 * @prop - काष्ठा property poपूर्णांक containing the maxsyncop क्रम the update
 *
 * Returns:
 *  0 on success
 *  -EINVAL on failure
 */
अटल पूर्णांक nx842_OF_upd_maxsglen(काष्ठा nx842_devdata *devdata,
					काष्ठा property *prop) अणु
	पूर्णांक ret = 0;
	स्थिर अचिन्हित पूर्णांक maxsglen = of_पढ़ो_number(prop->value, 1);

	अगर (prop->length != माप(maxsglen)) अणु
		dev_err(devdata->dev, "%s: unexpected format for ibm,max-sg-len property\n", __func__);
		dev_dbg(devdata->dev, "%s: ibm,max-sg-len is %d bytes long, expected %lu bytes\n", __func__,
				prop->length, माप(maxsglen));
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		devdata->max_sg_len = min_t(अचिन्हित पूर्णांक,
					    maxsglen, NX842_HW_PAGE_SIZE);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * nx842_OF_upd_maxsyncop -- Update the device info from OF maxsyncop prop
 *
 * Definition of the 'ibm,max-sync-cop' OF property:
 *  Two series of cells.  The first series of cells represents the maximums
 *  that can be synchronously compressed. The second series of cells
 *  represents the maximums that can be synchronously decompressed.
 *  1. The first cell in each series contains the count of the number of
 *     data length, scatter list elements pairs that follow ै  each being
 *     of the क्रमm
 *    a. One cell data byte length
 *    b. One cell total number of scatter list elements
 *
 * Example:
 *  # od -x ibm,max-sync-cop
 *  0000000 0000 0001 0000 1000 0000 01fe 0000 0001
 *  0000020 0000 1000 0000 01fe
 *
 *  In this example, compression supports 0x1000 (4,096) data byte length
 *  and 0x1fe (510) total scatter list elements.  Decompression supports
 *  0x1000 (4,096) data byte length and 0x1f3 (510) total scatter list
 *  elements.
 *
 * @devdata - काष्ठा nx842_devdata to update
 * @prop - काष्ठा property poपूर्णांक containing the maxsyncop क्रम the update
 *
 * Returns:
 *  0 on success
 *  -EINVAL on failure
 */
अटल पूर्णांक nx842_OF_upd_maxsyncop(काष्ठा nx842_devdata *devdata,
					काष्ठा property *prop) अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक comp_data_limit, decomp_data_limit;
	अचिन्हित पूर्णांक comp_sg_limit, decomp_sg_limit;
	स्थिर काष्ठा maxsynccop_t अणु
		__be32 comp_elements;
		__be32 comp_data_limit;
		__be32 comp_sg_limit;
		__be32 decomp_elements;
		__be32 decomp_data_limit;
		__be32 decomp_sg_limit;
	पूर्ण *maxsynccop;

	अगर (prop->length != माप(*maxsynccop)) अणु
		dev_err(devdata->dev, "%s: unexpected format for ibm,max-sync-cop property\n", __func__);
		dev_dbg(devdata->dev, "%s: ibm,max-sync-cop is %d bytes long, expected %lu bytes\n", __func__, prop->length,
				माप(*maxsynccop));
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	maxsynccop = (स्थिर काष्ठा maxsynccop_t *)prop->value;
	comp_data_limit = be32_to_cpu(maxsynccop->comp_data_limit);
	comp_sg_limit = be32_to_cpu(maxsynccop->comp_sg_limit);
	decomp_data_limit = be32_to_cpu(maxsynccop->decomp_data_limit);
	decomp_sg_limit = be32_to_cpu(maxsynccop->decomp_sg_limit);

	/* Use one limit rather than separate limits क्रम compression and
	 * decompression. Set a maximum क्रम this so as not to exceed the
	 * size that the header can support and round the value करोwn to
	 * the hardware page size (4K) */
	devdata->max_sync_size = min(comp_data_limit, decomp_data_limit);

	devdata->max_sync_size = min_t(अचिन्हित पूर्णांक, devdata->max_sync_size,
					65536);

	अगर (devdata->max_sync_size < 4096) अणु
		dev_err(devdata->dev, "%s: hardware max data size (%u) is "
				"less than the driver minimum, unable to use "
				"the hardware device\n",
				__func__, devdata->max_sync_size);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	nx842_pseries_स्थिरraपूर्णांकs.maximum = devdata->max_sync_size;

	devdata->max_sync_sg = min(comp_sg_limit, decomp_sg_limit);
	अगर (devdata->max_sync_sg < 1) अणु
		dev_err(devdata->dev, "%s: hardware max sg size (%u) is "
				"less than the driver minimum, unable to use "
				"the hardware device\n",
				__func__, devdata->max_sync_sg);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

/**
 *
 * nx842_OF_upd -- Handle OF properties updates क्रम the device.
 *
 * Set all properties from the OF tree.  Optionally, a new property
 * can be provided by the @new_prop poपूर्णांकer to overग_लिखो an existing value.
 * The device will reमुख्य disabled until all values are valid, this function
 * will वापस an error क्रम updates unless all values are valid.
 *
 * @new_prop: If not शून्य, this property is being updated.  If शून्य, update
 *  all properties from the current values in the OF tree.
 *
 * Returns:
 *  0 - Success
 *  -ENOMEM - Could not allocate memory क्रम new devdata काष्ठाure
 *  -EINVAL - property value not found, new_prop is not a recognized
 *	property क्रम the device or property value is not valid.
 *  -ENODEV - Device is not available
 */
अटल पूर्णांक nx842_OF_upd(काष्ठा property *new_prop)
अणु
	काष्ठा nx842_devdata *old_devdata = शून्य;
	काष्ठा nx842_devdata *new_devdata = शून्य;
	काष्ठा device_node *of_node = शून्य;
	काष्ठा property *status = शून्य;
	काष्ठा property *maxsglen = शून्य;
	काष्ठा property *maxsyncop = शून्य;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	new_devdata = kzalloc(माप(*new_devdata), GFP_NOFS);
	अगर (!new_devdata)
		वापस -ENOMEM;

	spin_lock_irqsave(&devdata_mutex, flags);
	old_devdata = rcu_dereference_check(devdata,
			lockdep_is_held(&devdata_mutex));
	अगर (old_devdata)
		of_node = old_devdata->dev->of_node;

	अगर (!old_devdata || !of_node) अणु
		pr_err("%s: device is not available\n", __func__);
		spin_unlock_irqrestore(&devdata_mutex, flags);
		kमुक्त(new_devdata);
		वापस -ENODEV;
	पूर्ण

	स_नकल(new_devdata, old_devdata, माप(*old_devdata));
	new_devdata->counters = old_devdata->counters;

	/* Set ptrs क्रम existing properties */
	status = of_find_property(of_node, "status", शून्य);
	maxsglen = of_find_property(of_node, "ibm,max-sg-len", शून्य);
	maxsyncop = of_find_property(of_node, "ibm,max-sync-cop", शून्य);
	अगर (!status || !maxsglen || !maxsyncop) अणु
		dev_err(old_devdata->dev, "%s: Could not locate device properties\n", __func__);
		ret = -EINVAL;
		जाओ error_out;
	पूर्ण

	/*
	 * If this is a property update, there are only certain properties that
	 * we care about. Bail अगर it isn't in the below list
	 */
	अगर (new_prop && (म_भेदन(new_prop->name, "status", new_prop->length) ||
		         म_भेदन(new_prop->name, "ibm,max-sg-len", new_prop->length) ||
		         म_भेदन(new_prop->name, "ibm,max-sync-cop", new_prop->length)))
		जाओ out;

	/* Perक्रमm property updates */
	ret = nx842_OF_upd_status(status);
	अगर (ret)
		जाओ error_out;

	ret = nx842_OF_upd_maxsglen(new_devdata, maxsglen);
	अगर (ret)
		जाओ error_out;

	ret = nx842_OF_upd_maxsyncop(new_devdata, maxsyncop);
	अगर (ret)
		जाओ error_out;

out:
	dev_info(old_devdata->dev, "%s: max_sync_size new:%u old:%u\n",
			__func__, new_devdata->max_sync_size,
			old_devdata->max_sync_size);
	dev_info(old_devdata->dev, "%s: max_sync_sg new:%u old:%u\n",
			__func__, new_devdata->max_sync_sg,
			old_devdata->max_sync_sg);
	dev_info(old_devdata->dev, "%s: max_sg_len new:%u old:%u\n",
			__func__, new_devdata->max_sg_len,
			old_devdata->max_sg_len);

	rcu_assign_poपूर्णांकer(devdata, new_devdata);
	spin_unlock_irqrestore(&devdata_mutex, flags);
	synchronize_rcu();
	dev_set_drvdata(new_devdata->dev, new_devdata);
	kमुक्त(old_devdata);
	वापस 0;

error_out:
	अगर (new_devdata) अणु
		dev_info(old_devdata->dev, "%s: device disabled\n", __func__);
		nx842_OF_set_शेषs(new_devdata);
		rcu_assign_poपूर्णांकer(devdata, new_devdata);
		spin_unlock_irqrestore(&devdata_mutex, flags);
		synchronize_rcu();
		dev_set_drvdata(new_devdata->dev, new_devdata);
		kमुक्त(old_devdata);
	पूर्ण अन्यथा अणु
		dev_err(old_devdata->dev, "%s: could not update driver from hardware\n", __func__);
		spin_unlock_irqrestore(&devdata_mutex, flags);
	पूर्ण

	अगर (!ret)
		ret = -EINVAL;
	वापस ret;
पूर्ण

/**
 * nx842_OF_notअगरier - Process updates to OF properties क्रम the device
 *
 * @np: notअगरier block
 * @action: notअगरier action
 * @update: काष्ठा pSeries_reconfig_prop_update poपूर्णांकer अगर action is
 *	PSERIES_UPDATE_PROPERTY
 *
 * Returns:
 *	NOTIFY_OK on success
 *	NOTIFY_BAD encoded with error number on failure, use
 *		notअगरier_to_त्रुटि_सं() to decode this value
 */
अटल पूर्णांक nx842_OF_notअगरier(काष्ठा notअगरier_block *np, अचिन्हित दीर्घ action,
			     व्योम *data)
अणु
	काष्ठा of_reconfig_data *upd = data;
	काष्ठा nx842_devdata *local_devdata;
	काष्ठा device_node *node = शून्य;

	rcu_पढ़ो_lock();
	local_devdata = rcu_dereference(devdata);
	अगर (local_devdata)
		node = local_devdata->dev->of_node;

	अगर (local_devdata &&
			action == OF_RECONFIG_UPDATE_PROPERTY &&
			!म_भेद(upd->dn->name, node->name)) अणु
		rcu_पढ़ो_unlock();
		nx842_OF_upd(upd->prop);
	पूर्ण अन्यथा
		rcu_पढ़ो_unlock();

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block nx842_of_nb = अणु
	.notअगरier_call = nx842_OF_notअगरier,
पूर्ण;

#घोषणा nx842_counter_पढ़ो(_name)					\
अटल sमाप_प्रकार nx842_##_name##_show(काष्ठा device *dev,		\
		काष्ठा device_attribute *attr,				\
		अक्षर *buf) अणु						\
	काष्ठा nx842_devdata *local_devdata;			\
	पूर्णांक p = 0;							\
	rcu_पढ़ो_lock();						\
	local_devdata = rcu_dereference(devdata);			\
	अगर (local_devdata)						\
		p = snम_लिखो(buf, PAGE_SIZE, "%lld\n",			\
		       atomic64_पढ़ो(&local_devdata->counters->_name));	\
	rcu_पढ़ो_unlock();						\
	वापस p;							\
पूर्ण

#घोषणा NX842DEV_COUNTER_ATTR_RO(_name)					\
	nx842_counter_पढ़ो(_name);					\
	अटल काष्ठा device_attribute dev_attr_##_name = __ATTR(_name,	\
						0444,			\
						nx842_##_name##_show,\
						शून्य);

NX842DEV_COUNTER_ATTR_RO(comp_complete);
NX842DEV_COUNTER_ATTR_RO(comp_failed);
NX842DEV_COUNTER_ATTR_RO(decomp_complete);
NX842DEV_COUNTER_ATTR_RO(decomp_failed);
NX842DEV_COUNTER_ATTR_RO(swdecomp);

अटल sमाप_प्रकार nx842_समयhist_show(काष्ठा device *,
		काष्ठा device_attribute *, अक्षर *);

अटल काष्ठा device_attribute dev_attr_comp_बार = __ATTR(comp_बार, 0444,
		nx842_समयhist_show, शून्य);
अटल काष्ठा device_attribute dev_attr_decomp_बार = __ATTR(decomp_बार,
		0444, nx842_समयhist_show, शून्य);

अटल sमाप_प्रकार nx842_समयhist_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf) अणु
	अक्षर *p = buf;
	काष्ठा nx842_devdata *local_devdata;
	atomic64_t *बार;
	पूर्णांक bytes_reमुख्य = PAGE_SIZE;
	पूर्णांक bytes;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	local_devdata = rcu_dereference(devdata);
	अगर (!local_devdata) अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	अगर (attr == &dev_attr_comp_बार)
		बार = local_devdata->counters->comp_बार;
	अन्यथा अगर (attr == &dev_attr_decomp_बार)
		बार = local_devdata->counters->decomp_बार;
	अन्यथा अणु
		rcu_पढ़ो_unlock();
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < (NX842_HIST_SLOTS - 2); i++) अणु
		bytes = snम_लिखो(p, bytes_reमुख्य, "%u-%uus:\t%lld\n",
			       i ? (2<<(i-1)) : 0, (2<<i)-1,
			       atomic64_पढ़ो(&बार[i]));
		bytes_reमुख्य -= bytes;
		p += bytes;
	पूर्ण
	/* The last bucket holds everything over
	 * 2<<(NX842_HIST_SLOTS - 2) us */
	bytes = snम_लिखो(p, bytes_reमुख्य, "%uus - :\t%lld\n",
			2<<(NX842_HIST_SLOTS - 2),
			atomic64_पढ़ो(&बार[(NX842_HIST_SLOTS - 1)]));
	p += bytes;

	rcu_पढ़ो_unlock();
	वापस p - buf;
पूर्ण

अटल काष्ठा attribute *nx842_sysfs_entries[] = अणु
	&dev_attr_comp_complete.attr,
	&dev_attr_comp_failed.attr,
	&dev_attr_decomp_complete.attr,
	&dev_attr_decomp_failed.attr,
	&dev_attr_swdecomp.attr,
	&dev_attr_comp_बार.attr,
	&dev_attr_decomp_बार.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group nx842_attribute_group = अणु
	.name = शून्य,		/* put in device directory */
	.attrs = nx842_sysfs_entries,
पूर्ण;

अटल काष्ठा nx842_driver nx842_pseries_driver = अणु
	.name =		KBUILD_MODNAME,
	.owner =	THIS_MODULE,
	.workmem_size =	माप(काष्ठा nx842_workmem),
	.स्थिरraपूर्णांकs =	&nx842_pseries_स्थिरraपूर्णांकs,
	.compress =	nx842_pseries_compress,
	.decompress =	nx842_pseries_decompress,
पूर्ण;

अटल पूर्णांक nx842_pseries_crypto_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस nx842_crypto_init(tfm, &nx842_pseries_driver);
पूर्ण

अटल काष्ठा crypto_alg nx842_pseries_alg = अणु
	.cra_name		= "842",
	.cra_driver_name	= "842-nx",
	.cra_priority		= 300,
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा nx842_crypto_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= nx842_pseries_crypto_init,
	.cra_निकास		= nx842_crypto_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress		= nx842_crypto_compress,
	.coa_decompress		= nx842_crypto_decompress पूर्ण पूर्ण
पूर्ण;

अटल पूर्णांक nx842_probe(काष्ठा vio_dev *viodev,
		       स्थिर काष्ठा vio_device_id *id)
अणु
	काष्ठा nx842_devdata *old_devdata, *new_devdata = शून्य;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	new_devdata = kzalloc(माप(*new_devdata), GFP_NOFS);
	अगर (!new_devdata)
		वापस -ENOMEM;

	new_devdata->counters = kzalloc(माप(*new_devdata->counters),
			GFP_NOFS);
	अगर (!new_devdata->counters) अणु
		kमुक्त(new_devdata);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&devdata_mutex, flags);
	old_devdata = rcu_dereference_check(devdata,
			lockdep_is_held(&devdata_mutex));

	अगर (old_devdata && old_devdata->vdev != शून्य) अणु
		dev_err(&viodev->dev, "%s: Attempt to register more than one instance of the hardware\n", __func__);
		ret = -1;
		जाओ error_unlock;
	पूर्ण

	dev_set_drvdata(&viodev->dev, शून्य);

	new_devdata->vdev = viodev;
	new_devdata->dev = &viodev->dev;
	nx842_OF_set_शेषs(new_devdata);

	rcu_assign_poपूर्णांकer(devdata, new_devdata);
	spin_unlock_irqrestore(&devdata_mutex, flags);
	synchronize_rcu();
	kमुक्त(old_devdata);

	of_reconfig_notअगरier_रेजिस्टर(&nx842_of_nb);

	ret = nx842_OF_upd(शून्य);
	अगर (ret)
		जाओ error;

	ret = crypto_रेजिस्टर_alg(&nx842_pseries_alg);
	अगर (ret) अणु
		dev_err(&viodev->dev, "could not register comp alg: %d\n", ret);
		जाओ error;
	पूर्ण

	rcu_पढ़ो_lock();
	dev_set_drvdata(&viodev->dev, rcu_dereference(devdata));
	rcu_पढ़ो_unlock();

	अगर (sysfs_create_group(&viodev->dev.kobj, &nx842_attribute_group)) अणु
		dev_err(&viodev->dev, "could not create sysfs device attributes\n");
		ret = -1;
		जाओ error;
	पूर्ण

	वापस 0;

error_unlock:
	spin_unlock_irqrestore(&devdata_mutex, flags);
	अगर (new_devdata)
		kमुक्त(new_devdata->counters);
	kमुक्त(new_devdata);
error:
	वापस ret;
पूर्ण

अटल व्योम nx842_हटाओ(काष्ठा vio_dev *viodev)
अणु
	काष्ठा nx842_devdata *old_devdata;
	अचिन्हित दीर्घ flags;

	pr_info("Removing IBM Power 842 compression device\n");
	sysfs_हटाओ_group(&viodev->dev.kobj, &nx842_attribute_group);

	crypto_unरेजिस्टर_alg(&nx842_pseries_alg);

	spin_lock_irqsave(&devdata_mutex, flags);
	old_devdata = rcu_dereference_check(devdata,
			lockdep_is_held(&devdata_mutex));
	of_reconfig_notअगरier_unरेजिस्टर(&nx842_of_nb);
	RCU_INIT_POINTER(devdata, शून्य);
	spin_unlock_irqrestore(&devdata_mutex, flags);
	synchronize_rcu();
	dev_set_drvdata(&viodev->dev, शून्य);
	अगर (old_devdata)
		kमुक्त(old_devdata->counters);
	kमुक्त(old_devdata);
पूर्ण

अटल स्थिर काष्ठा vio_device_id nx842_vio_driver_ids[] = अणु
	अणु"ibm,compression-v1", "ibm,compression"पूर्ण,
	अणु"", ""पूर्ण,
पूर्ण;

अटल काष्ठा vio_driver nx842_vio_driver = अणु
	.name = KBUILD_MODNAME,
	.probe = nx842_probe,
	.हटाओ = nx842_हटाओ,
	.get_desired_dma = nx842_get_desired_dma,
	.id_table = nx842_vio_driver_ids,
पूर्ण;

अटल पूर्णांक __init nx842_pseries_init(व्योम)
अणु
	काष्ठा nx842_devdata *new_devdata;
	पूर्णांक ret;

	अगर (!of_find_compatible_node(शून्य, शून्य, "ibm,compression"))
		वापस -ENODEV;

	RCU_INIT_POINTER(devdata, शून्य);
	new_devdata = kzalloc(माप(*new_devdata), GFP_KERNEL);
	अगर (!new_devdata)
		वापस -ENOMEM;

	RCU_INIT_POINTER(devdata, new_devdata);

	ret = vio_रेजिस्टर_driver(&nx842_vio_driver);
	अगर (ret) अणु
		pr_err("Could not register VIO driver %d\n", ret);

		kमुक्त(new_devdata);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

module_init(nx842_pseries_init);

अटल व्योम __निकास nx842_pseries_निकास(व्योम)
अणु
	काष्ठा nx842_devdata *old_devdata;
	अचिन्हित दीर्घ flags;

	crypto_unरेजिस्टर_alg(&nx842_pseries_alg);

	spin_lock_irqsave(&devdata_mutex, flags);
	old_devdata = rcu_dereference_check(devdata,
			lockdep_is_held(&devdata_mutex));
	RCU_INIT_POINTER(devdata, शून्य);
	spin_unlock_irqrestore(&devdata_mutex, flags);
	synchronize_rcu();
	अगर (old_devdata && old_devdata->dev)
		dev_set_drvdata(old_devdata->dev, शून्य);
	kमुक्त(old_devdata);
	vio_unरेजिस्टर_driver(&nx842_vio_driver);
पूर्ण

module_निकास(nx842_pseries_निकास);

