<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * CAAM Error Reporting
 *
 * Copyright 2009-2011 Freescale Semiconductor, Inc.
 */

#समावेश "compat.h"
#समावेश "regs.h"
#समावेश "desc.h"
#समावेश "error.h"

#अगर_घोषित DEBUG
#समावेश <linux/highस्मृति.स>

व्योम caam_dump_sg(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		  पूर्णांक rowsize, पूर्णांक groupsize, काष्ठा scatterlist *sg,
		  माप_प्रकार tlen, bool ascii)
अणु
	काष्ठा scatterlist *it;
	व्योम *it_page;
	माप_प्रकार len;
	व्योम *buf;

	क्रम (it = sg; it && tlen > 0 ; it = sg_next(it)) अणु
		/*
		 * make sure the scatterlist's page
		 * has a valid भव memory mapping
		 */
		it_page = kmap_atomic(sg_page(it));
		अगर (unlikely(!it_page)) अणु
			pr_err("caam_dump_sg: kmap failed\n");
			वापस;
		पूर्ण

		buf = it_page + it->offset;
		len = min_t(माप_प्रकार, tlen, it->length);
		prपूर्णांक_hex_dump_debug(prefix_str, prefix_type, rowsize,
				     groupsize, buf, len, ascii);
		tlen -= len;

		kunmap_atomic(it_page);
	पूर्ण
पूर्ण
#अन्यथा
व्योम caam_dump_sg(स्थिर अक्षर *prefix_str, पूर्णांक prefix_type,
		  पूर्णांक rowsize, पूर्णांक groupsize, काष्ठा scatterlist *sg,
		  माप_प्रकार tlen, bool ascii)
अणुपूर्ण
#पूर्ण_अगर /* DEBUG */
EXPORT_SYMBOL(caam_dump_sg);

bool caam_little_end;
EXPORT_SYMBOL(caam_little_end);

bool caam_imx;
EXPORT_SYMBOL(caam_imx);

माप_प्रकार caam_ptr_sz;
EXPORT_SYMBOL(caam_ptr_sz);

अटल स्थिर काष्ठा अणु
	u8 value;
	स्थिर अक्षर *error_text;
पूर्ण desc_error_list[] = अणु
	अणु 0x00, "No error." पूर्ण,
	अणु 0x01, "SGT Length Error. The descriptor is trying to read more data than is contained in the SGT table." पूर्ण,
	अणु 0x02, "SGT Null Entry Error." पूर्ण,
	अणु 0x03, "Job Ring Control Error. There is a bad value in the Job Ring Control register." पूर्ण,
	अणु 0x04, "Invalid Descriptor Command. The Descriptor Command field is invalid." पूर्ण,
	अणु 0x05, "Reserved." पूर्ण,
	अणु 0x06, "Invalid KEY Command" पूर्ण,
	अणु 0x07, "Invalid LOAD Command" पूर्ण,
	अणु 0x08, "Invalid STORE Command" पूर्ण,
	अणु 0x09, "Invalid OPERATION Command" पूर्ण,
	अणु 0x0A, "Invalid FIFO LOAD Command" पूर्ण,
	अणु 0x0B, "Invalid FIFO STORE Command" पूर्ण,
	अणु 0x0C, "Invalid MOVE/MOVE_LEN Command" पूर्ण,
	अणु 0x0D, "Invalid JUMP Command. A nonlocal JUMP Command is invalid because the target is not a Job Header Command, or the jump is from a Trusted Descriptor to a Job Descriptor, or because the target Descriptor contains a Shared Descriptor." पूर्ण,
	अणु 0x0E, "Invalid MATH Command" पूर्ण,
	अणु 0x0F, "Invalid SIGNATURE Command" पूर्ण,
	अणु 0x10, "Invalid Sequence Command. A SEQ IN PTR OR SEQ OUT PTR Command is invalid or a SEQ KEY, SEQ LOAD, SEQ FIFO LOAD, or SEQ FIFO STORE decremented the input or output sequence length below 0. This error may result if a built-in PROTOCOL Command has encountered a malformed PDU." पूर्ण,
	अणु 0x11, "Skip data type invalid. The type must be 0xE or 0xF."पूर्ण,
	अणु 0x12, "Shared Descriptor Header Error" पूर्ण,
	अणु 0x13, "Header Error. Invalid length or parity, or certain other problems." पूर्ण,
	अणु 0x14, "Burster Error. Burster has gotten to an illegal state" पूर्ण,
	अणु 0x15, "Context Register Length Error. The descriptor is trying to read or write past the end of the Context Register. A SEQ LOAD or SEQ STORE with the VLF bit set was executed with too large a length in the variable length register (VSOL for SEQ STORE or VSIL for SEQ LOAD)." पूर्ण,
	अणु 0x16, "DMA Error" पूर्ण,
	अणु 0x17, "Reserved." पूर्ण,
	अणु 0x1A, "Job failed due to JR reset" पूर्ण,
	अणु 0x1B, "Job failed due to Fail Mode" पूर्ण,
	अणु 0x1C, "DECO Watchdog timer timeout error" पूर्ण,
	अणु 0x1D, "DECO tried to copy a key from another DECO but the other DECO's Key Registers were locked" पूर्ण,
	अणु 0x1E, "DECO attempted to copy data from a DECO that had an unmasked Descriptor error" पूर्ण,
	अणु 0x1F, "LIODN error. DECO was trying to share from itself or from another DECO but the two Non-SEQ LIODN values didn't match or the 'shared from' DECO's Descriptor required that the SEQ LIODNs be the same and they aren't." पूर्ण,
	अणु 0x20, "DECO has completed a reset initiated via the DRR register" पूर्ण,
	अणु 0x21, "Nonce error. When using EKT (CCM) key encryption option in the FIFO STORE Command, the Nonce counter reached its maximum value and this encryption mode can no longer be used." पूर्ण,
	अणु 0x22, "Meta data is too large (> 511 bytes) for TLS decap (input frame; block ciphers) and IPsec decap (output frame, when doing the next header byte update) and DCRC (output frame)." पूर्ण,
	अणु 0x23, "Read Input Frame error" पूर्ण,
	अणु 0x24, "JDKEK, TDKEK or TDSK not loaded error" पूर्ण,
	अणु 0x80, "DNR (do not run) error" पूर्ण,
	अणु 0x81, "undefined protocol command" पूर्ण,
	अणु 0x82, "invalid setting in PDB" पूर्ण,
	अणु 0x83, "Anti-replay LATE error" पूर्ण,
	अणु 0x84, "Anti-replay REPLAY error" पूर्ण,
	अणु 0x85, "Sequence number overflow" पूर्ण,
	अणु 0x86, "Sigver invalid signature" पूर्ण,
	अणु 0x87, "DSA Sign Illegal test descriptor" पूर्ण,
	अणु 0x88, "Protocol Format Error - A protocol has seen an error in the format of data received. When running RSA, this means that formatting with random padding was used, and did not follow the form: 0x00, 0x02, 8-to-N bytes of non-zero pad, 0x00, F data." पूर्ण,
	अणु 0x89, "Protocol Size Error - A protocol has seen an error in size. When running RSA, pdb size N < (size of F) when no formatting is used; or pdb size N < (F + 11) when formatting is used." पूर्ण,
	अणु 0xC1, "Blob Command error: Undefined mode" पूर्ण,
	अणु 0xC2, "Blob Command error: Secure Memory Blob mode error" पूर्ण,
	अणु 0xC4, "Blob Command error: Black Blob key or input size error" पूर्ण,
	अणु 0xC5, "Blob Command error: Invalid key destination" पूर्ण,
	अणु 0xC8, "Blob Command error: Trusted/Secure mode error" पूर्ण,
	अणु 0xF0, "IPsec TTL or hop limit field either came in as 0, or was decremented to 0" पूर्ण,
	अणु 0xF1, "3GPP HFN matches or exceeds the Threshold" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा अणु
	u8 value;
	स्थिर अक्षर *error_text;
पूर्ण qi_error_list[] = अणु
	अणु 0x00, "No error" पूर्ण,
	अणु 0x1F, "Job terminated by FQ or ICID flush" पूर्ण,
	अणु 0x20, "FD format error"पूर्ण,
	अणु 0x21, "FD command format error"पूर्ण,
	अणु 0x23, "FL format error"पूर्ण,
	अणु 0x25, "CRJD specified in FD, but not enabled in FLC"पूर्ण,
	अणु 0x30, "Max. buffer size too small"पूर्ण,
	अणु 0x31, "DHR exceeds max. buffer size (allocate mode, S/G format)"पूर्ण,
	अणु 0x32, "SGT exceeds max. buffer size (allocate mode, S/G format"पूर्ण,
	अणु 0x33, "Size over/underflow (allocate mode)"पूर्ण,
	अणु 0x34, "Size over/underflow (reuse mode)"पूर्ण,
	अणु 0x35, "Length exceeds max. short length (allocate mode, S/G/ format)"पूर्ण,
	अणु 0x36, "Memory footprint exceeds max. value (allocate mode, S/G/ format)"पूर्ण,
	अणु 0x41, "SBC frame format not supported (allocate mode)"पूर्ण,
	अणु 0x42, "Pool 0 invalid / pool 1 size < pool 0 size (allocate mode)"पूर्ण,
	अणु 0x43, "Annotation output enabled but ASAR = 0 (allocate mode)"पूर्ण,
	अणु 0x44, "Unsupported or reserved frame format or SGHR = 1 (reuse mode)"पूर्ण,
	अणु 0x45, "DHR correction underflow (reuse mode, single buffer format)"पूर्ण,
	अणु 0x46, "Annotation length exceeds offset (reuse mode)"पूर्ण,
	अणु 0x48, "Annotation output enabled but ASA limited by ASAR (reuse mode)"पूर्ण,
	अणु 0x49, "Data offset correction exceeds input frame data length (reuse mode)"पूर्ण,
	अणु 0x4B, "Annotation output enabled but ASA cannot be expanded (frame list)"पूर्ण,
	अणु 0x51, "Unsupported IF reuse mode"पूर्ण,
	अणु 0x52, "Unsupported FL use mode"पूर्ण,
	अणु 0x53, "Unsupported RJD use mode"पूर्ण,
	अणु 0x54, "Unsupported inline descriptor use mode"पूर्ण,
	अणु 0xC0, "Table buffer pool 0 depletion"पूर्ण,
	अणु 0xC1, "Table buffer pool 1 depletion"पूर्ण,
	अणु 0xC2, "Data buffer pool 0 depletion, no OF allocated"पूर्ण,
	अणु 0xC3, "Data buffer pool 1 depletion, no OF allocated"पूर्ण,
	अणु 0xC4, "Data buffer pool 0 depletion, partial OF allocated"पूर्ण,
	अणु 0xC5, "Data buffer pool 1 depletion, partial OF allocated"पूर्ण,
	अणु 0xD0, "FLC read error"पूर्ण,
	अणु 0xD1, "FL read error"पूर्ण,
	अणु 0xD2, "FL write error"पूर्ण,
	अणु 0xD3, "OF SGT write error"पूर्ण,
	अणु 0xD4, "PTA read error"पूर्ण,
	अणु 0xD5, "PTA write error"पूर्ण,
	अणु 0xD6, "OF SGT F-bit write error"पूर्ण,
	अणु 0xD7, "ASA write error"पूर्ण,
	अणु 0xE1, "FLC[ICR]=0 ICID error"पूर्ण,
	अणु 0xE2, "FLC[ICR]=1 ICID error"पूर्ण,
	अणु 0xE4, "source of ICID flush not trusted (BDI = 0)"पूर्ण,
पूर्ण;

अटल स्थिर अक्षर * स्थिर cha_id_list[] = अणु
	"",
	"AES",
	"DES",
	"ARC4",
	"MDHA",
	"RNG",
	"SNOW f8",
	"Kasumi f8/9",
	"PKHA",
	"CRCA",
	"SNOW f9",
	"ZUCE",
	"ZUCA",
पूर्ण;

अटल स्थिर अक्षर * स्थिर err_id_list[] = अणु
	"No error.",
	"Mode error.",
	"Data size error.",
	"Key size error.",
	"PKHA A memory size error.",
	"PKHA B memory size error.",
	"Data arrived out of sequence error.",
	"PKHA divide-by-zero error.",
	"PKHA modulus even error.",
	"DES key parity error.",
	"ICV check failed.",
	"Hardware error.",
	"Unsupported CCM AAD size.",
	"Class 1 CHA is not reset",
	"Invalid CHA combination was selected",
	"Invalid CHA selected.",
पूर्ण;

अटल स्थिर अक्षर * स्थिर rng_err_id_list[] = अणु
	"",
	"",
	"",
	"Instantiate",
	"Not instantiated",
	"Test instantiate",
	"Prediction resistance",
	"Prediction resistance and test request",
	"Uninstantiate",
	"Secure key generation",
	"",
	"Hardware error",
	"Continuous check"
पूर्ण;

अटल पूर्णांक report_ccb_status(काष्ठा device *jrdev, स्थिर u32 status,
			     स्थिर अक्षर *error)
अणु
	u8 cha_id = (status & JRSTA_CCBERR_CHAID_MASK) >>
		    JRSTA_CCBERR_CHAID_SHIFT;
	u8 err_id = status & JRSTA_CCBERR_ERRID_MASK;
	u8 idx = (status & JRSTA_DECOERR_INDEX_MASK) >>
		  JRSTA_DECOERR_INDEX_SHIFT;
	अक्षर *idx_str;
	स्थिर अक्षर *cha_str = "unidentified cha_id value 0x";
	अक्षर cha_err_code[3] = अणु 0 पूर्ण;
	स्थिर अक्षर *err_str = "unidentified err_id value 0x";
	अक्षर err_err_code[3] = अणु 0 पूर्ण;

	अगर (status & JRSTA_DECOERR_JUMP)
		idx_str = "jump tgt desc idx";
	अन्यथा
		idx_str = "desc idx";

	अगर (cha_id < ARRAY_SIZE(cha_id_list))
		cha_str = cha_id_list[cha_id];
	अन्यथा
		snम_लिखो(cha_err_code, माप(cha_err_code), "%02x", cha_id);

	अगर ((cha_id << JRSTA_CCBERR_CHAID_SHIFT) == JRSTA_CCBERR_CHAID_RNG &&
	    err_id < ARRAY_SIZE(rng_err_id_list) &&
	    म_माप(rng_err_id_list[err_id])) अणु
		/* RNG-only error */
		err_str = rng_err_id_list[err_id];
	पूर्ण अन्यथा अणु
		err_str = err_id_list[err_id];
	पूर्ण

	/*
	 * CCB ICV check failures are part of normal operation lअगरe;
	 * we leave the upper layers to करो what they want with them.
	 */
	अगर (err_id == JRSTA_CCBERR_ERRID_ICVCHK)
		वापस -EBADMSG;

	dev_err_ratelimited(jrdev, "%08x: %s: %s %d: %s%s: %s%s\n", status,
			    error, idx_str, idx, cha_str, cha_err_code,
			    err_str, err_err_code);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक report_jump_status(काष्ठा device *jrdev, स्थिर u32 status,
			      स्थिर अक्षर *error)
अणु
	dev_err(jrdev, "%08x: %s: %s() not implemented\n",
		status, error, __func__);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक report_deco_status(काष्ठा device *jrdev, स्थिर u32 status,
			      स्थिर अक्षर *error)
अणु
	u8 err_id = status & JRSTA_DECOERR_ERROR_MASK;
	u8 idx = (status & JRSTA_DECOERR_INDEX_MASK) >>
		  JRSTA_DECOERR_INDEX_SHIFT;
	अक्षर *idx_str;
	स्थिर अक्षर *err_str = "unidentified error value 0x";
	अक्षर err_err_code[3] = अणु 0 पूर्ण;
	पूर्णांक i;

	अगर (status & JRSTA_DECOERR_JUMP)
		idx_str = "jump tgt desc idx";
	अन्यथा
		idx_str = "desc idx";

	क्रम (i = 0; i < ARRAY_SIZE(desc_error_list); i++)
		अगर (desc_error_list[i].value == err_id)
			अवरोध;

	अगर (i != ARRAY_SIZE(desc_error_list) && desc_error_list[i].error_text)
		err_str = desc_error_list[i].error_text;
	अन्यथा
		snम_लिखो(err_err_code, माप(err_err_code), "%02x", err_id);

	dev_err(jrdev, "%08x: %s: %s %d: %s%s\n",
		status, error, idx_str, idx, err_str, err_err_code);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक report_qi_status(काष्ठा device *qidev, स्थिर u32 status,
			    स्थिर अक्षर *error)
अणु
	u8 err_id = status & JRSTA_QIERR_ERROR_MASK;
	स्थिर अक्षर *err_str = "unidentified error value 0x";
	अक्षर err_err_code[3] = अणु 0 पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(qi_error_list); i++)
		अगर (qi_error_list[i].value == err_id)
			अवरोध;

	अगर (i != ARRAY_SIZE(qi_error_list) && qi_error_list[i].error_text)
		err_str = qi_error_list[i].error_text;
	अन्यथा
		snम_लिखो(err_err_code, माप(err_err_code), "%02x", err_id);

	dev_err(qidev, "%08x: %s: %s%s\n",
		status, error, err_str, err_err_code);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक report_jr_status(काष्ठा device *jrdev, स्थिर u32 status,
			    स्थिर अक्षर *error)
अणु
	dev_err(jrdev, "%08x: %s: %s() not implemented\n",
		status, error, __func__);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक report_cond_code_status(काष्ठा device *jrdev, स्थिर u32 status,
				   स्थिर अक्षर *error)
अणु
	dev_err(jrdev, "%08x: %s: %s() not implemented\n",
		status, error, __func__);

	वापस -EINVAL;
पूर्ण

पूर्णांक caam_strstatus(काष्ठा device *jrdev, u32 status, bool qi_v2)
अणु
	अटल स्थिर काष्ठा stat_src अणु
		पूर्णांक (*report_ssed)(काष्ठा device *jrdev, स्थिर u32 status,
				   स्थिर अक्षर *error);
		स्थिर अक्षर *error;
	पूर्ण status_src[16] = अणु
		अणु शून्य, "No error" पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु report_ccb_status, "CCB" पूर्ण,
		अणु report_jump_status, "Jump" पूर्ण,
		अणु report_deco_status, "DECO" पूर्ण,
		अणु report_qi_status, "Queue Manager Interface" पूर्ण,
		अणु report_jr_status, "Job Ring" पूर्ण,
		अणु report_cond_code_status, "Condition Code" पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
		अणु शून्य, शून्य पूर्ण,
	पूर्ण;
	u32 ssrc = status >> JRSTA_SSRC_SHIFT;
	स्थिर अक्षर *error = status_src[ssrc].error;

	/*
	 * If there is an error handling function, call it to report the error.
	 * Otherwise prपूर्णांक the error source name.
	 */
	अगर (status_src[ssrc].report_ssed)
		वापस status_src[ssrc].report_ssed(jrdev, status, error);

	अगर (error)
		dev_err(jrdev, "%d: %s\n", ssrc, error);
	अन्यथा
		dev_err(jrdev, "%d: unknown error source\n", ssrc);

	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL(caam_strstatus);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("FSL CAAM error reporting");
MODULE_AUTHOR("Freescale Semiconductor");
