<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम IBM PowerNV compression accelerator
 *
 * Copyright (C) 2015 Dan Streeपंचांगan, IBM Corp
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश "nx-842.h"

#समावेश <linux/समयr.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/icswx.h>
#समावेश <यंत्र/vas.h>
#समावेश <यंत्र/reg.h>
#समावेश <यंत्र/opal-api.h>
#समावेश <यंत्र/opal.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Dan Streetman <ddstreet@ieee.org>");
MODULE_DESCRIPTION("H/W Compression driver for IBM PowerNV processors");
MODULE_ALIAS_CRYPTO("842");
MODULE_ALIAS_CRYPTO("842-nx");

#घोषणा WORKMEM_ALIGN	(CRB_ALIGN)
#घोषणा CSB_WAIT_MAX	(5000) /* ms */
#घोषणा VAS_RETRIES	(10)

काष्ठा nx842_workmem अणु
	/* Below fields must be properly aligned */
	काष्ठा coprocessor_request_block crb; /* CRB_ALIGN align */
	काष्ठा data_descriptor_entry ddl_in[DDL_LEN_MAX]; /* DDE_ALIGN align */
	काष्ठा data_descriptor_entry ddl_out[DDL_LEN_MAX]; /* DDE_ALIGN align */
	/* Above fields must be properly aligned */

	kसमय_प्रकार start;

	अक्षर padding[WORKMEM_ALIGN]; /* unused, to allow alignment */
पूर्ण __packed __aligned(WORKMEM_ALIGN);

काष्ठा nx_coproc अणु
	अचिन्हित पूर्णांक chip_id;
	अचिन्हित पूर्णांक ct;	/* Can be 842 or GZIP high/normal*/
	अचिन्हित पूर्णांक ci;	/* Coprocessor instance, used with icswx */
	काष्ठा अणु
		काष्ठा vas_winकरोw *rxwin;
		पूर्णांक id;
	पूर्ण vas;
	काष्ठा list_head list;
पूर्ण;

/*
 * Send the request to NX engine on the chip क्रम the corresponding CPU
 * where the process is executing. Use with VAS function.
 */
अटल DEFINE_PER_CPU(काष्ठा vas_winकरोw *, cpu_txwin);

/* no cpu hotplug on घातernv, so this list never changes after init */
अटल LIST_HEAD(nx_coprocs);
अटल अचिन्हित पूर्णांक nx842_ct;	/* used in icswx function */

/*
 * Using same values as in skiboot or coprocessor type representing
 * in NX workbook.
 */
#घोषणा NX_CT_GZIP	(2)	/* on P9 and later */
#घोषणा NX_CT_842	(3)

अटल पूर्णांक (*nx842_घातernv_exec)(स्थिर अचिन्हित अक्षर *in,
				अचिन्हित पूर्णांक inlen, अचिन्हित अक्षर *out,
				अचिन्हित पूर्णांक *outlenp, व्योम *workmem, पूर्णांक fc);

/**
 * setup_indirect_dde - Setup an indirect DDE
 *
 * The DDE is setup with the the DDE count, byte count, and address of
 * first direct DDE in the list.
 */
अटल व्योम setup_indirect_dde(काष्ठा data_descriptor_entry *dde,
			       काष्ठा data_descriptor_entry *ddl,
			       अचिन्हित पूर्णांक dde_count, अचिन्हित पूर्णांक byte_count)
अणु
	dde->flags = 0;
	dde->count = dde_count;
	dde->index = 0;
	dde->length = cpu_to_be32(byte_count);
	dde->address = cpu_to_be64(nx842_get_pa(ddl));
पूर्ण

/**
 * setup_direct_dde - Setup single DDE from buffer
 *
 * The DDE is setup with the buffer and length.  The buffer must be properly
 * aligned.  The used length is वापसed.
 * Returns:
 *   N    Successfully set up DDE with N bytes
 */
अटल अचिन्हित पूर्णांक setup_direct_dde(काष्ठा data_descriptor_entry *dde,
				     अचिन्हित दीर्घ pa, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक l = min_t(अचिन्हित पूर्णांक, len, LEN_ON_PAGE(pa));

	dde->flags = 0;
	dde->count = 0;
	dde->index = 0;
	dde->length = cpu_to_be32(l);
	dde->address = cpu_to_be64(pa);

	वापस l;
पूर्ण

/**
 * setup_ddl - Setup DDL from buffer
 *
 * Returns:
 *   0		Successfully set up DDL
 */
अटल पूर्णांक setup_ddl(काष्ठा data_descriptor_entry *dde,
		     काष्ठा data_descriptor_entry *ddl,
		     अचिन्हित अक्षर *buf, अचिन्हित पूर्णांक len,
		     bool in)
अणु
	अचिन्हित दीर्घ pa = nx842_get_pa(buf);
	पूर्णांक i, ret, total_len = len;

	अगर (!IS_ALIGNED(pa, DDE_BUFFER_ALIGN)) अणु
		pr_debug("%s buffer pa 0x%lx not 0x%x-byte aligned\n",
			 in ? "input" : "output", pa, DDE_BUFFER_ALIGN);
		वापस -EINVAL;
	पूर्ण

	/* only need to check last mult; since buffer must be
	 * DDE_BUFFER_ALIGN aligned, and that is a multiple of
	 * DDE_BUFFER_SIZE_MULT, and pre-last page DDE buffers
	 * are guaranteed a multiple of DDE_BUFFER_SIZE_MULT.
	 */
	अगर (len % DDE_BUFFER_LAST_MULT) अणु
		pr_debug("%s buffer len 0x%x not a multiple of 0x%x\n",
			 in ? "input" : "output", len, DDE_BUFFER_LAST_MULT);
		अगर (in)
			वापस -EINVAL;
		len = round_करोwn(len, DDE_BUFFER_LAST_MULT);
	पूर्ण

	/* use a single direct DDE */
	अगर (len <= LEN_ON_PAGE(pa)) अणु
		ret = setup_direct_dde(dde, pa, len);
		WARN_ON(ret < len);
		वापस 0;
	पूर्ण

	/* use the DDL */
	क्रम (i = 0; i < DDL_LEN_MAX && len > 0; i++) अणु
		ret = setup_direct_dde(&ddl[i], pa, len);
		buf += ret;
		len -= ret;
		pa = nx842_get_pa(buf);
	पूर्ण

	अगर (len > 0) अणु
		pr_debug("0x%x total %s bytes 0x%x too many for DDL.\n",
			 total_len, in ? "input" : "output", len);
		अगर (in)
			वापस -EMSGSIZE;
		total_len -= len;
	पूर्ण
	setup_indirect_dde(dde, ddl, i, total_len);

	वापस 0;
पूर्ण

#घोषणा CSB_ERR(csb, msg, ...)					\
	pr_err("ERROR: " msg " : %02x %02x %02x %02x %08x\n",	\
	       ##__VA_ARGS__, (csb)->flags,			\
	       (csb)->cs, (csb)->cc, (csb)->ce,			\
	       be32_to_cpu((csb)->count))

#घोषणा CSB_ERR_ADDR(csb, msg, ...)				\
	CSB_ERR(csb, msg " at %lx", ##__VA_ARGS__,		\
		(अचिन्हित दीर्घ)be64_to_cpu((csb)->address))

/**
 * रुको_क्रम_csb
 */
अटल पूर्णांक रुको_क्रम_csb(काष्ठा nx842_workmem *wmem,
			काष्ठा coprocessor_status_block *csb)
अणु
	kसमय_प्रकार start = wmem->start, now = kसमय_get();
	kसमय_प्रकार समयout = kसमय_add_ms(start, CSB_WAIT_MAX);

	जबतक (!(READ_ONCE(csb->flags) & CSB_V)) अणु
		cpu_relax();
		now = kसमय_get();
		अगर (kसमय_after(now, समयout))
			अवरोध;
	पूर्ण

	/* hw has updated csb and output buffer */
	barrier();

	/* check CSB flags */
	अगर (!(csb->flags & CSB_V)) अणु
		CSB_ERR(csb, "CSB still not valid after %ld us, giving up",
			(दीर्घ)kसमय_us_delta(now, start));
		वापस -ETIMEDOUT;
	पूर्ण
	अगर (csb->flags & CSB_F) अणु
		CSB_ERR(csb, "Invalid CSB format");
		वापस -EPROTO;
	पूर्ण
	अगर (csb->flags & CSB_CH) अणु
		CSB_ERR(csb, "Invalid CSB chaining state");
		वापस -EPROTO;
	पूर्ण

	/* verअगरy CSB completion sequence is 0 */
	अगर (csb->cs) अणु
		CSB_ERR(csb, "Invalid CSB completion sequence");
		वापस -EPROTO;
	पूर्ण

	/* check CSB Completion Code */
	चयन (csb->cc) अणु
	/* no error */
	हाल CSB_CC_SUCCESS:
		अवरोध;
	हाल CSB_CC_TPBC_GT_SPBC:
		/* not an error, but the compressed data is
		 * larger than the uncompressed data :(
		 */
		अवरोध;

	/* input data errors */
	हाल CSB_CC_OPERAND_OVERLAP:
		/* input and output buffers overlap */
		CSB_ERR(csb, "Operand Overlap error");
		वापस -EINVAL;
	हाल CSB_CC_INVALID_OPERAND:
		CSB_ERR(csb, "Invalid operand");
		वापस -EINVAL;
	हाल CSB_CC_NOSPC:
		/* output buffer too small */
		वापस -ENOSPC;
	हाल CSB_CC_ABORT:
		CSB_ERR(csb, "Function aborted");
		वापस -EINTR;
	हाल CSB_CC_CRC_MISMATCH:
		CSB_ERR(csb, "CRC mismatch");
		वापस -EINVAL;
	हाल CSB_CC_TEMPL_INVALID:
		CSB_ERR(csb, "Compressed data template invalid");
		वापस -EINVAL;
	हाल CSB_CC_TEMPL_OVERFLOW:
		CSB_ERR(csb, "Compressed data template shows data past end");
		वापस -EINVAL;
	हाल CSB_CC_EXCEED_BYTE_COUNT:	/* P9 or later */
		/*
		 * DDE byte count exceeds the limit specअगरied in Maximum
		 * byte count रेजिस्टर.
		 */
		CSB_ERR(csb, "DDE byte count exceeds the limit");
		वापस -EINVAL;

	/* these should not happen */
	हाल CSB_CC_INVALID_ALIGN:
		/* setup_ddl should have detected this */
		CSB_ERR_ADDR(csb, "Invalid alignment");
		वापस -EINVAL;
	हाल CSB_CC_DATA_LENGTH:
		/* setup_ddl should have detected this */
		CSB_ERR(csb, "Invalid data length");
		वापस -EINVAL;
	हाल CSB_CC_WR_TRANSLATION:
	हाल CSB_CC_TRANSLATION:
	हाल CSB_CC_TRANSLATION_DUP1:
	हाल CSB_CC_TRANSLATION_DUP2:
	हाल CSB_CC_TRANSLATION_DUP3:
	हाल CSB_CC_TRANSLATION_DUP4:
	हाल CSB_CC_TRANSLATION_DUP5:
	हाल CSB_CC_TRANSLATION_DUP6:
		/* should not happen, we use physical addrs */
		CSB_ERR_ADDR(csb, "Translation error");
		वापस -EPROTO;
	हाल CSB_CC_WR_PROTECTION:
	हाल CSB_CC_PROTECTION:
	हाल CSB_CC_PROTECTION_DUP1:
	हाल CSB_CC_PROTECTION_DUP2:
	हाल CSB_CC_PROTECTION_DUP3:
	हाल CSB_CC_PROTECTION_DUP4:
	हाल CSB_CC_PROTECTION_DUP5:
	हाल CSB_CC_PROTECTION_DUP6:
		/* should not happen, we use physical addrs */
		CSB_ERR_ADDR(csb, "Protection error");
		वापस -EPROTO;
	हाल CSB_CC_PRIVILEGE:
		/* shouldn't happen, we're in HYP mode */
		CSB_ERR(csb, "Insufficient Privilege error");
		वापस -EPROTO;
	हाल CSB_CC_EXCESSIVE_DDE:
		/* shouldn't happen, setup_ddl doesn't use many dde's */
		CSB_ERR(csb, "Too many DDEs in DDL");
		वापस -EINVAL;
	हाल CSB_CC_TRANSPORT:
	हाल CSB_CC_INVALID_CRB:	/* P9 or later */
		/* shouldn't happen, we setup CRB correctly */
		CSB_ERR(csb, "Invalid CRB");
		वापस -EINVAL;
	हाल CSB_CC_INVALID_DDE:	/* P9 or later */
		/*
		 * shouldn't happen, setup_direct/indirect_dde creates
		 * DDE right
		 */
		CSB_ERR(csb, "Invalid DDE");
		वापस -EINVAL;
	हाल CSB_CC_SEGMENTED_DDL:
		/* shouldn't happen, setup_ddl creates DDL right */
		CSB_ERR(csb, "Segmented DDL error");
		वापस -EINVAL;
	हाल CSB_CC_DDE_OVERFLOW:
		/* shouldn't happen, setup_ddl creates DDL right */
		CSB_ERR(csb, "DDE overflow error");
		वापस -EINVAL;
	हाल CSB_CC_SESSION:
		/* should not happen with ICSWX */
		CSB_ERR(csb, "Session violation error");
		वापस -EPROTO;
	हाल CSB_CC_CHAIN:
		/* should not happen, we करोn't use chained CRBs */
		CSB_ERR(csb, "Chained CRB error");
		वापस -EPROTO;
	हाल CSB_CC_SEQUENCE:
		/* should not happen, we करोn't use chained CRBs */
		CSB_ERR(csb, "CRB sequence number error");
		वापस -EPROTO;
	हाल CSB_CC_UNKNOWN_CODE:
		CSB_ERR(csb, "Unknown subfunction code");
		वापस -EPROTO;

	/* hardware errors */
	हाल CSB_CC_RD_EXTERNAL:
	हाल CSB_CC_RD_EXTERNAL_DUP1:
	हाल CSB_CC_RD_EXTERNAL_DUP2:
	हाल CSB_CC_RD_EXTERNAL_DUP3:
		CSB_ERR_ADDR(csb, "Read error outside coprocessor");
		वापस -EPROTO;
	हाल CSB_CC_WR_EXTERNAL:
		CSB_ERR_ADDR(csb, "Write error outside coprocessor");
		वापस -EPROTO;
	हाल CSB_CC_INTERNAL:
		CSB_ERR(csb, "Internal error in coprocessor");
		वापस -EPROTO;
	हाल CSB_CC_PROVISION:
		CSB_ERR(csb, "Storage provision error");
		वापस -EPROTO;
	हाल CSB_CC_HW:
		CSB_ERR(csb, "Correctable hardware error");
		वापस -EPROTO;
	हाल CSB_CC_HW_EXPIRED_TIMER:	/* P9 or later */
		CSB_ERR(csb, "Job did not finish within allowed time");
		वापस -EPROTO;

	शेष:
		CSB_ERR(csb, "Invalid CC %d", csb->cc);
		वापस -EPROTO;
	पूर्ण

	/* check Completion Extension state */
	अगर (csb->ce & CSB_CE_TERMINATION) अणु
		CSB_ERR(csb, "CSB request was terminated");
		वापस -EPROTO;
	पूर्ण
	अगर (csb->ce & CSB_CE_INCOMPLETE) अणु
		CSB_ERR(csb, "CSB request not complete");
		वापस -EPROTO;
	पूर्ण
	अगर (!(csb->ce & CSB_CE_TPBC)) अणु
		CSB_ERR(csb, "TPBC not provided, unknown target length");
		वापस -EPROTO;
	पूर्ण

	/* successful completion */
	pr_debug_ratelimited("Processed %u bytes in %lu us\n",
			     be32_to_cpu(csb->count),
			     (अचिन्हित दीर्घ)kसमय_us_delta(now, start));

	वापस 0;
पूर्ण

अटल पूर्णांक nx842_config_crb(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
			अचिन्हित अक्षर *out, अचिन्हित पूर्णांक outlen,
			काष्ठा nx842_workmem *wmem)
अणु
	काष्ठा coprocessor_request_block *crb;
	काष्ठा coprocessor_status_block *csb;
	u64 csb_addr;
	पूर्णांक ret;

	crb = &wmem->crb;
	csb = &crb->csb;

	/* Clear any previous values */
	स_रखो(crb, 0, माप(*crb));

	/* set up DDLs */
	ret = setup_ddl(&crb->source, wmem->ddl_in,
			(अचिन्हित अक्षर *)in, inlen, true);
	अगर (ret)
		वापस ret;

	ret = setup_ddl(&crb->target, wmem->ddl_out,
			out, outlen, false);
	अगर (ret)
		वापस ret;

	/* set up CRB's CSB addr */
	csb_addr = nx842_get_pa(csb) & CRB_CSB_ADDRESS;
	csb_addr |= CRB_CSB_AT; /* Addrs are phys */
	crb->csb_addr = cpu_to_be64(csb_addr);

	वापस 0;
पूर्ण

/**
 * nx842_exec_icswx - compress/decompress data using the 842 algorithm
 *
 * (De)compression provided by the NX842 coprocessor on IBM PowerNV प्रणालीs.
 * This compresses or decompresses the provided input buffer पूर्णांकo the provided
 * output buffer.
 *
 * Upon वापस from this function @outlen contains the length of the
 * output data.  If there is an error then @outlen will be 0 and an
 * error will be specअगरied by the वापस code from this function.
 *
 * The @workmem buffer should only be used by one function call at a समय.
 *
 * @in: input buffer poपूर्णांकer
 * @inlen: input buffer size
 * @out: output buffer poपूर्णांकer
 * @outlenp: output buffer size poपूर्णांकer
 * @workmem: working memory buffer poपूर्णांकer, size determined by
 *           nx842_घातernv_driver.workmem_size
 * @fc: function code, see CCW Function Codes in nx-842.h
 *
 * Returns:
 *   0		Success, output of length @outlenp stored in the buffer at @out
 *   -ENODEV	Hardware unavailable
 *   -ENOSPC	Output buffer is to small
 *   -EMSGSIZE	Input buffer too large
 *   -EINVAL	buffer स्थिरraपूर्णांकs करो not fix nx842_स्थिरraपूर्णांकs
 *   -EPROTO	hardware error during operation
 *   -ETIMEDOUT	hardware did not complete operation in reasonable समय
 *   -EINTR	operation was पातed
 */
अटल पूर्णांक nx842_exec_icswx(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
				  अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *outlenp,
				  व्योम *workmem, पूर्णांक fc)
अणु
	काष्ठा coprocessor_request_block *crb;
	काष्ठा coprocessor_status_block *csb;
	काष्ठा nx842_workmem *wmem;
	पूर्णांक ret;
	u32 ccw;
	अचिन्हित पूर्णांक outlen = *outlenp;

	wmem = PTR_ALIGN(workmem, WORKMEM_ALIGN);

	*outlenp = 0;

	/* shoudn't happen, we don't load without a coproc */
	अगर (!nx842_ct) अणु
		pr_err_ratelimited("coprocessor CT is 0");
		वापस -ENODEV;
	पूर्ण

	ret = nx842_config_crb(in, inlen, out, outlen, wmem);
	अगर (ret)
		वापस ret;

	crb = &wmem->crb;
	csb = &crb->csb;

	/* set up CCW */
	ccw = 0;
	ccw = SET_FIELD(CCW_CT, ccw, nx842_ct);
	ccw = SET_FIELD(CCW_CI_842, ccw, 0); /* use 0 क्रम hw स्वतः-selection */
	ccw = SET_FIELD(CCW_FC_842, ccw, fc);

	wmem->start = kसमय_get();

	/* करो ICSWX */
	ret = icswx(cpu_to_be32(ccw), crb);

	pr_debug_ratelimited("icswx CR %x ccw %x crb->ccw %x\n", ret,
			     (अचिन्हित पूर्णांक)ccw,
			     (अचिन्हित पूर्णांक)be32_to_cpu(crb->ccw));

	/*
	 * NX842 coprocessor sets 3rd bit in CR रेजिस्टर with XER[S0].
	 * XER[S0] is the पूर्णांकeger summary overflow bit which is nothing
	 * to करो NX. Since this bit can be set with other वापस values,
	 * mask this bit.
	 */
	ret &= ~ICSWX_XERS0;

	चयन (ret) अणु
	हाल ICSWX_INITIATED:
		ret = रुको_क्रम_csb(wmem, csb);
		अवरोध;
	हाल ICSWX_BUSY:
		pr_debug_ratelimited("842 Coprocessor busy\n");
		ret = -EBUSY;
		अवरोध;
	हाल ICSWX_REJECTED:
		pr_err_ratelimited("ICSWX rejected\n");
		ret = -EPROTO;
		अवरोध;
	पूर्ण

	अगर (!ret)
		*outlenp = be32_to_cpu(csb->count);

	वापस ret;
पूर्ण

/**
 * nx842_exec_vas - compress/decompress data using the 842 algorithm
 *
 * (De)compression provided by the NX842 coprocessor on IBM PowerNV प्रणालीs.
 * This compresses or decompresses the provided input buffer पूर्णांकo the provided
 * output buffer.
 *
 * Upon वापस from this function @outlen contains the length of the
 * output data.  If there is an error then @outlen will be 0 and an
 * error will be specअगरied by the वापस code from this function.
 *
 * The @workmem buffer should only be used by one function call at a समय.
 *
 * @in: input buffer poपूर्णांकer
 * @inlen: input buffer size
 * @out: output buffer poपूर्णांकer
 * @outlenp: output buffer size poपूर्णांकer
 * @workmem: working memory buffer poपूर्णांकer, size determined by
 *           nx842_घातernv_driver.workmem_size
 * @fc: function code, see CCW Function Codes in nx-842.h
 *
 * Returns:
 *   0		Success, output of length @outlenp stored in the buffer
 *		at @out
 *   -ENODEV	Hardware unavailable
 *   -ENOSPC	Output buffer is to small
 *   -EMSGSIZE	Input buffer too large
 *   -EINVAL	buffer स्थिरraपूर्णांकs करो not fix nx842_स्थिरraपूर्णांकs
 *   -EPROTO	hardware error during operation
 *   -ETIMEDOUT	hardware did not complete operation in reasonable समय
 *   -EINTR	operation was पातed
 */
अटल पूर्णांक nx842_exec_vas(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
				  अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *outlenp,
				  व्योम *workmem, पूर्णांक fc)
अणु
	काष्ठा coprocessor_request_block *crb;
	काष्ठा coprocessor_status_block *csb;
	काष्ठा nx842_workmem *wmem;
	काष्ठा vas_winकरोw *txwin;
	पूर्णांक ret, i = 0;
	u32 ccw;
	अचिन्हित पूर्णांक outlen = *outlenp;

	wmem = PTR_ALIGN(workmem, WORKMEM_ALIGN);

	*outlenp = 0;

	crb = &wmem->crb;
	csb = &crb->csb;

	ret = nx842_config_crb(in, inlen, out, outlen, wmem);
	अगर (ret)
		वापस ret;

	ccw = 0;
	ccw = SET_FIELD(CCW_FC_842, ccw, fc);
	crb->ccw = cpu_to_be32(ccw);

	करो अणु
		wmem->start = kसमय_get();
		preempt_disable();
		txwin = this_cpu_पढ़ो(cpu_txwin);

		/*
		 * VAS copy CRB पूर्णांकo L2 cache. Refer <यंत्र/vas.h>.
		 * @crb and @offset.
		 */
		vas_copy_crb(crb, 0);

		/*
		 * VAS paste previously copied CRB to NX.
		 * @txwin, @offset and @last (must be true).
		 */
		ret = vas_paste_crb(txwin, 0, 1);
		preempt_enable();
		/*
		 * Retry copy/paste function क्रम VAS failures.
		 */
	पूर्ण जबतक (ret && (i++ < VAS_RETRIES));

	अगर (ret) अणु
		pr_err_ratelimited("VAS copy/paste failed\n");
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_csb(wmem, csb);
	अगर (!ret)
		*outlenp = be32_to_cpu(csb->count);

	वापस ret;
पूर्ण

/**
 * nx842_घातernv_compress - Compress data using the 842 algorithm
 *
 * Compression provided by the NX842 coprocessor on IBM PowerNV प्रणालीs.
 * The input buffer is compressed and the result is stored in the
 * provided output buffer.
 *
 * Upon वापस from this function @outlen contains the length of the
 * compressed data.  If there is an error then @outlen will be 0 and an
 * error will be specअगरied by the वापस code from this function.
 *
 * @in: input buffer poपूर्णांकer
 * @inlen: input buffer size
 * @out: output buffer poपूर्णांकer
 * @outlenp: output buffer size poपूर्णांकer
 * @workmem: working memory buffer poपूर्णांकer, size determined by
 *           nx842_घातernv_driver.workmem_size
 *
 * Returns: see @nx842_घातernv_exec()
 */
अटल पूर्णांक nx842_घातernv_compress(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
				  अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *outlenp,
				  व्योम *wmem)
अणु
	वापस nx842_घातernv_exec(in, inlen, out, outlenp,
				      wmem, CCW_FC_842_COMP_CRC);
पूर्ण

/**
 * nx842_घातernv_decompress - Decompress data using the 842 algorithm
 *
 * Decompression provided by the NX842 coprocessor on IBM PowerNV प्रणालीs.
 * The input buffer is decompressed and the result is stored in the
 * provided output buffer.
 *
 * Upon वापस from this function @outlen contains the length of the
 * decompressed data.  If there is an error then @outlen will be 0 and an
 * error will be specअगरied by the वापस code from this function.
 *
 * @in: input buffer poपूर्णांकer
 * @inlen: input buffer size
 * @out: output buffer poपूर्णांकer
 * @outlenp: output buffer size poपूर्णांकer
 * @workmem: working memory buffer poपूर्णांकer, size determined by
 *           nx842_घातernv_driver.workmem_size
 *
 * Returns: see @nx842_घातernv_exec()
 */
अटल पूर्णांक nx842_घातernv_decompress(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक inlen,
				    अचिन्हित अक्षर *out, अचिन्हित पूर्णांक *outlenp,
				    व्योम *wmem)
अणु
	वापस nx842_घातernv_exec(in, inlen, out, outlenp,
				      wmem, CCW_FC_842_DECOMP_CRC);
पूर्ण

अटल अंतरभूत व्योम nx_add_coprocs_list(काष्ठा nx_coproc *coproc,
					पूर्णांक chipid)
अणु
	coproc->chip_id = chipid;
	INIT_LIST_HEAD(&coproc->list);
	list_add(&coproc->list, &nx_coprocs);
पूर्ण

अटल काष्ठा vas_winकरोw *nx_alloc_txwin(काष्ठा nx_coproc *coproc)
अणु
	काष्ठा vas_winकरोw *txwin = शून्य;
	काष्ठा vas_tx_win_attr txattr;

	/*
	 * Kernel requests will be high priority. So खोलो send
	 * winकरोws only क्रम high priority RxFIFO entries.
	 */
	vas_init_tx_win_attr(&txattr, coproc->ct);
	txattr.lpid = 0;	/* lpid is 0 क्रम kernel requests */

	/*
	 * Open a VAS send winकरोw which is used to send request to NX.
	 */
	txwin = vas_tx_win_खोलो(coproc->vas.id, coproc->ct, &txattr);
	अगर (IS_ERR(txwin))
		pr_err("ibm,nx-842: Can not open TX window: %ld\n",
				PTR_ERR(txwin));

	वापस txwin;
पूर्ण

/*
 * Identअगरy chip ID क्रम each CPU, खोलो send wnकरोw क्रम the corresponding NX
 * engine and save txwin in percpu cpu_txwin.
 * cpu_txwin is used in copy/paste operation क्रम each compression /
 * decompression request.
 */
अटल पूर्णांक nx_खोलो_percpu_txwins(व्योम)
अणु
	काष्ठा nx_coproc *coproc, *n;
	अचिन्हित पूर्णांक i, chip_id;

	क्रम_each_possible_cpu(i) अणु
		काष्ठा vas_winकरोw *txwin = शून्य;

		chip_id = cpu_to_chip_id(i);

		list_क्रम_each_entry_safe(coproc, n, &nx_coprocs, list) अणु
			/*
			 * Kernel requests use only high priority FIFOs. So
			 * खोलो send winकरोws क्रम these FIFOs.
			 * GZIP is not supported in kernel right now.
			 */

			अगर (coproc->ct != VAS_COP_TYPE_842_HIPRI)
				जारी;

			अगर (coproc->chip_id == chip_id) अणु
				txwin = nx_alloc_txwin(coproc);
				अगर (IS_ERR(txwin))
					वापस PTR_ERR(txwin);

				per_cpu(cpu_txwin, i) = txwin;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!per_cpu(cpu_txwin, i)) अणु
			/* shouldn't happen, Each chip will have NX engine */
			pr_err("NX engine is not available for CPU %d\n", i);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init nx_set_ct(काष्ठा nx_coproc *coproc, स्थिर अक्षर *priority,
				पूर्णांक high, पूर्णांक normal)
अणु
	अगर (!म_भेद(priority, "High"))
		coproc->ct = high;
	अन्यथा अगर (!म_भेद(priority, "Normal"))
		coproc->ct = normal;
	अन्यथा अणु
		pr_err("Invalid RxFIFO priority value\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init vas_cfg_coproc_info(काष्ठा device_node *dn, पूर्णांक chip_id,
					पूर्णांक vasid, पूर्णांक type, पूर्णांक *ct)
अणु
	काष्ठा vas_winकरोw *rxwin = शून्य;
	काष्ठा vas_rx_win_attr rxattr;
	u32 lpid, pid, tid, fअगरo_size;
	काष्ठा nx_coproc *coproc;
	u64 rx_fअगरo;
	स्थिर अक्षर *priority;
	पूर्णांक ret;

	ret = of_property_पढ़ो_u64(dn, "rx-fifo-address", &rx_fअगरo);
	अगर (ret) अणु
		pr_err("Missing rx-fifo-address property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dn, "rx-fifo-size", &fअगरo_size);
	अगर (ret) अणु
		pr_err("Missing rx-fifo-size property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dn, "lpid", &lpid);
	अगर (ret) अणु
		pr_err("Missing lpid property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dn, "pid", &pid);
	अगर (ret) अणु
		pr_err("Missing pid property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_u32(dn, "tid", &tid);
	अगर (ret) अणु
		pr_err("Missing tid property\n");
		वापस ret;
	पूर्ण

	ret = of_property_पढ़ो_string(dn, "priority", &priority);
	अगर (ret) अणु
		pr_err("Missing priority property\n");
		वापस ret;
	पूर्ण

	coproc = kzalloc(माप(*coproc), GFP_KERNEL);
	अगर (!coproc)
		वापस -ENOMEM;

	अगर (type == NX_CT_842)
		ret = nx_set_ct(coproc, priority, VAS_COP_TYPE_842_HIPRI,
			VAS_COP_TYPE_842);
	अन्यथा अगर (type == NX_CT_GZIP)
		ret = nx_set_ct(coproc, priority, VAS_COP_TYPE_GZIP_HIPRI,
				VAS_COP_TYPE_GZIP);

	अगर (ret)
		जाओ err_out;

	vas_init_rx_win_attr(&rxattr, coproc->ct);
	rxattr.rx_fअगरo = (व्योम *)rx_fअगरo;
	rxattr.rx_fअगरo_size = fअगरo_size;
	rxattr.lnotअगरy_lpid = lpid;
	rxattr.lnotअगरy_pid = pid;
	rxattr.lnotअगरy_tid = tid;
	/*
	 * Maximum RX winकरोw credits can not be more than #CRBs in
	 * RxFIFO. Otherwise, can get checkstop अगर RxFIFO overruns.
	 */
	rxattr.wcreds_max = fअगरo_size / CRB_SIZE;

	/*
	 * Open a VAS receice winकरोw which is used to configure RxFIFO
	 * क्रम NX.
	 */
	rxwin = vas_rx_win_खोलो(vasid, coproc->ct, &rxattr);
	अगर (IS_ERR(rxwin)) अणु
		ret = PTR_ERR(rxwin);
		pr_err("setting RxFIFO with VAS failed: %d\n",
			ret);
		जाओ err_out;
	पूर्ण

	coproc->vas.rxwin = rxwin;
	coproc->vas.id = vasid;
	nx_add_coprocs_list(coproc, chip_id);

	/*
	 * (lpid, pid, tid) combination has to be unique क्रम each
	 * coprocessor instance in the प्रणाली. So to make it
	 * unique, skiboot uses coprocessor type such as 842 or
	 * GZIP क्रम pid and provides this value to kernel in pid
	 * device-tree property.
	 */
	*ct = pid;

	वापस 0;

err_out:
	kमुक्त(coproc);
	वापस ret;
पूर्ण

अटल पूर्णांक __init nx_coproc_init(पूर्णांक chip_id, पूर्णांक ct_842, पूर्णांक ct_gzip)
अणु
	पूर्णांक ret = 0;

	अगर (opal_check_token(OPAL_NX_COPROC_INIT)) अणु
		ret = opal_nx_coproc_init(chip_id, ct_842);

		अगर (!ret)
			ret = opal_nx_coproc_init(chip_id, ct_gzip);

		अगर (ret) अणु
			ret = opal_error_code(ret);
			pr_err("Failed to initialize NX for chip(%d): %d\n",
				chip_id, ret);
		पूर्ण
	पूर्ण अन्यथा
		pr_warn("Firmware doesn't support NX initialization\n");

	वापस ret;
पूर्ण

अटल पूर्णांक __init find_nx_device_tree(काष्ठा device_node *dn, पूर्णांक chip_id,
					पूर्णांक vasid, पूर्णांक type, अक्षर *devname,
					पूर्णांक *ct)
अणु
	पूर्णांक ret = 0;

	अगर (of_device_is_compatible(dn, devname)) अणु
		ret  = vas_cfg_coproc_info(dn, chip_id, vasid, type, ct);
		अगर (ret)
			of_node_put(dn);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक __init nx_घातernv_probe_vas(काष्ठा device_node *pn)
अणु
	पूर्णांक chip_id, vasid, ret = 0;
	पूर्णांक ct_842 = 0, ct_gzip = 0;
	काष्ठा device_node *dn;

	chip_id = of_get_ibm_chip_id(pn);
	अगर (chip_id < 0) अणु
		pr_err("ibm,chip-id missing\n");
		वापस -EINVAL;
	पूर्ण

	vasid = chip_to_vas_id(chip_id);
	अगर (vasid < 0) अणु
		pr_err("Unable to map chip_id %d to vasid\n", chip_id);
		वापस -EINVAL;
	पूर्ण

	क्रम_each_child_of_node(pn, dn) अणु
		ret = find_nx_device_tree(dn, chip_id, vasid, NX_CT_842,
					"ibm,p9-nx-842", &ct_842);

		अगर (!ret)
			ret = find_nx_device_tree(dn, chip_id, vasid,
				NX_CT_GZIP, "ibm,p9-nx-gzip", &ct_gzip);

		अगर (ret) अणु
			of_node_put(dn);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (!ct_842 || !ct_gzip) अणु
		pr_err("NX FIFO nodes are missing\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Initialize NX instance क्रम both high and normal priority FIFOs.
	 */
	ret = nx_coproc_init(chip_id, ct_842, ct_gzip);

	वापस ret;
पूर्ण

अटल पूर्णांक __init nx842_घातernv_probe(काष्ठा device_node *dn)
अणु
	काष्ठा nx_coproc *coproc;
	अचिन्हित पूर्णांक ct, ci;
	पूर्णांक chip_id;

	chip_id = of_get_ibm_chip_id(dn);
	अगर (chip_id < 0) अणु
		pr_err("ibm,chip-id missing\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dn, "ibm,842-coprocessor-type", &ct)) अणु
		pr_err("ibm,842-coprocessor-type missing\n");
		वापस -EINVAL;
	पूर्ण

	अगर (of_property_पढ़ो_u32(dn, "ibm,842-coprocessor-instance", &ci)) अणु
		pr_err("ibm,842-coprocessor-instance missing\n");
		वापस -EINVAL;
	पूर्ण

	coproc = kzalloc(माप(*coproc), GFP_KERNEL);
	अगर (!coproc)
		वापस -ENOMEM;

	coproc->ct = ct;
	coproc->ci = ci;
	nx_add_coprocs_list(coproc, chip_id);

	pr_info("coprocessor found on chip %d, CT %d CI %d\n", chip_id, ct, ci);

	अगर (!nx842_ct)
		nx842_ct = ct;
	अन्यथा अगर (nx842_ct != ct)
		pr_err("NX842 chip %d, CT %d != first found CT %d\n",
		       chip_id, ct, nx842_ct);

	वापस 0;
पूर्ण

अटल व्योम nx_delete_coprocs(व्योम)
अणु
	काष्ठा nx_coproc *coproc, *n;
	काष्ठा vas_winकरोw *txwin;
	पूर्णांक i;

	/*
	 * बंद percpu txwins that are खोलोed क्रम the corresponding coproc.
	 */
	क्रम_each_possible_cpu(i) अणु
		txwin = per_cpu(cpu_txwin, i);
		अगर (txwin)
			vas_win_बंद(txwin);

		per_cpu(cpu_txwin, i) = शून्य;
	पूर्ण

	list_क्रम_each_entry_safe(coproc, n, &nx_coprocs, list) अणु
		अगर (coproc->vas.rxwin)
			vas_win_बंद(coproc->vas.rxwin);

		list_del(&coproc->list);
		kमुक्त(coproc);
	पूर्ण
पूर्ण

अटल काष्ठा nx842_स्थिरraपूर्णांकs nx842_घातernv_स्थिरraपूर्णांकs = अणु
	.alignment =	DDE_BUFFER_ALIGN,
	.multiple =	DDE_BUFFER_LAST_MULT,
	.minimum =	DDE_BUFFER_LAST_MULT,
	.maximum =	(DDL_LEN_MAX - 1) * PAGE_SIZE,
पूर्ण;

अटल काष्ठा nx842_driver nx842_घातernv_driver = अणु
	.name =		KBUILD_MODNAME,
	.owner =	THIS_MODULE,
	.workmem_size =	माप(काष्ठा nx842_workmem),
	.स्थिरraपूर्णांकs =	&nx842_घातernv_स्थिरraपूर्णांकs,
	.compress =	nx842_घातernv_compress,
	.decompress =	nx842_घातernv_decompress,
पूर्ण;

अटल पूर्णांक nx842_घातernv_crypto_init(काष्ठा crypto_tfm *tfm)
अणु
	वापस nx842_crypto_init(tfm, &nx842_घातernv_driver);
पूर्ण

अटल काष्ठा crypto_alg nx842_घातernv_alg = अणु
	.cra_name		= "842",
	.cra_driver_name	= "842-nx",
	.cra_priority		= 300,
	.cra_flags		= CRYPTO_ALG_TYPE_COMPRESS,
	.cra_ctxsize		= माप(काष्ठा nx842_crypto_ctx),
	.cra_module		= THIS_MODULE,
	.cra_init		= nx842_घातernv_crypto_init,
	.cra_निकास		= nx842_crypto_निकास,
	.cra_u			= अणु .compress = अणु
	.coa_compress		= nx842_crypto_compress,
	.coa_decompress		= nx842_crypto_decompress पूर्ण पूर्ण
पूर्ण;

अटल __init पूर्णांक nx_compress_घातernv_init(व्योम)
अणु
	काष्ठा device_node *dn;
	पूर्णांक ret;

	/* verअगरy workmem size/align restrictions */
	BUILD_BUG_ON(WORKMEM_ALIGN % CRB_ALIGN);
	BUILD_BUG_ON(CRB_ALIGN % DDE_ALIGN);
	BUILD_BUG_ON(CRB_SIZE % DDE_ALIGN);
	/* verअगरy buffer size/align restrictions */
	BUILD_BUG_ON(PAGE_SIZE % DDE_BUFFER_ALIGN);
	BUILD_BUG_ON(DDE_BUFFER_ALIGN % DDE_BUFFER_SIZE_MULT);
	BUILD_BUG_ON(DDE_BUFFER_SIZE_MULT % DDE_BUFFER_LAST_MULT);

	क्रम_each_compatible_node(dn, शून्य, "ibm,power9-nx") अणु
		ret = nx_घातernv_probe_vas(dn);
		अगर (ret) अणु
			nx_delete_coprocs();
			of_node_put(dn);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (list_empty(&nx_coprocs)) अणु
		क्रम_each_compatible_node(dn, शून्य, "ibm,power-nx")
			nx842_घातernv_probe(dn);

		अगर (!nx842_ct)
			वापस -ENODEV;

		nx842_घातernv_exec = nx842_exec_icswx;
	पूर्ण अन्यथा अणु
		/*
		 * Register VAS user space API क्रम NX GZIP so
		 * that user space can use GZIP engine.
		 * Using high FIFO priority क्रम kernel requests and
		 * normal FIFO priority is asचिन्हित क्रम userspace.
		 * 842 compression is supported only in kernel.
		 */
		ret = vas_रेजिस्टर_coproc_api(THIS_MODULE, VAS_COP_TYPE_GZIP,
						"nx-gzip");

		/*
		 * GZIP is not supported in kernel right now.
		 * So खोलो tx winकरोws only क्रम 842.
		 */
		अगर (!ret)
			ret = nx_खोलो_percpu_txwins();

		अगर (ret) अणु
			nx_delete_coprocs();
			वापस ret;
		पूर्ण

		nx842_घातernv_exec = nx842_exec_vas;
	पूर्ण

	ret = crypto_रेजिस्टर_alg(&nx842_घातernv_alg);
	अगर (ret) अणु
		nx_delete_coprocs();
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
module_init(nx_compress_घातernv_init);

अटल व्योम __निकास nx_compress_घातernv_निकास(व्योम)
अणु
	/*
	 * GZIP engine is supported only in घातer9 or later and nx842_ct
	 * is used on घातer8 (icswx).
	 * VAS API क्रम NX GZIP is रेजिस्टरed during init क्रम user space
	 * use. So delete this API use क्रम GZIP engine.
	 */
	अगर (!nx842_ct)
		vas_unरेजिस्टर_coproc_api();

	crypto_unरेजिस्टर_alg(&nx842_घातernv_alg);

	nx_delete_coprocs();
पूर्ण
module_निकास(nx_compress_घातernv_निकास);
