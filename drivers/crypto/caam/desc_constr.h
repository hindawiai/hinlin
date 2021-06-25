<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * caam descriptor स्थिरruction helper functions
 *
 * Copyright 2008-2012 Freescale Semiconductor, Inc.
 * Copyright 2019 NXP
 */

#अगर_अघोषित DESC_CONSTR_H
#घोषणा DESC_CONSTR_H

#समावेश "desc.h"
#समावेश "regs.h"

#घोषणा IMMEDIATE (1 << 23)
#घोषणा CAAM_CMD_SZ माप(u32)
#घोषणा CAAM_PTR_SZ caam_ptr_sz
#घोषणा CAAM_PTR_SZ_MAX माप(dma_addr_t)
#घोषणा CAAM_PTR_SZ_MIN माप(u32)
#घोषणा CAAM_DESC_BYTES_MAX (CAAM_CMD_SZ * MAX_CAAM_DESCSIZE)
#घोषणा __DESC_JOB_IO_LEN(n) (CAAM_CMD_SZ * 5 + (n) * 3)
#घोषणा DESC_JOB_IO_LEN __DESC_JOB_IO_LEN(CAAM_PTR_SZ)
#घोषणा DESC_JOB_IO_LEN_MAX __DESC_JOB_IO_LEN(CAAM_PTR_SZ_MAX)
#घोषणा DESC_JOB_IO_LEN_MIN __DESC_JOB_IO_LEN(CAAM_PTR_SZ_MIN)

/*
 * The CAAM QI hardware स्थिरructs a job descriptor which poपूर्णांकs
 * to shared descriptor (as poपूर्णांकed by context_a of FQ to CAAM).
 * When the job descriptor is executed by deco, the whole job
 * descriptor together with shared descriptor माला_लो loaded in
 * deco buffer which is 64 words दीर्घ (each 32-bit).
 *
 * The job descriptor स्थिरructed by QI hardware has layout:
 *
 *	HEADER		(1 word)
 *	Shdesc ptr	(1 or 2 words)
 *	SEQ_OUT_PTR	(1 word)
 *	Out ptr		(1 or 2 words)
 *	Out length	(1 word)
 *	SEQ_IN_PTR	(1 word)
 *	In ptr		(1 or 2 words)
 *	In length	(1 word)
 *
 * The shdesc ptr is used to fetch shared descriptor contents
 * पूर्णांकo deco buffer.
 *
 * Apart from shdesc contents, the total number of words that
 * get loaded in deco buffer are '8' or '11'. The reमुख्यing words
 * in deco buffer can be used क्रम storing shared descriptor.
 */
#घोषणा MAX_SDLEN	((CAAM_DESC_BYTES_MAX - DESC_JOB_IO_LEN_MIN) / CAAM_CMD_SZ)

#अगर_घोषित DEBUG
#घोषणा PRINT_POS करो अणु prपूर्णांकk(KERN_DEBUG "%02d: %s\n", desc_len(desc),\
			      &__func__[माप("append")]); पूर्ण जबतक (0)
#अन्यथा
#घोषणा PRINT_POS
#पूर्ण_अगर

#घोषणा SET_OK_NO_PROP_ERRORS (IMMEDIATE | LDST_CLASS_DECO | \
			       LDST_SRCDST_WORD_DECOCTRL | \
			       (LDOFF_CHG_SHARE_OK_NO_PROP << \
				LDST_OFFSET_SHIFT))
#घोषणा DISABLE_AUTO_INFO_FIFO (IMMEDIATE | LDST_CLASS_DECO | \
				LDST_SRCDST_WORD_DECOCTRL | \
				(LDOFF_DISABLE_AUTO_NFIFO << LDST_OFFSET_SHIFT))
#घोषणा ENABLE_AUTO_INFO_FIFO (IMMEDIATE | LDST_CLASS_DECO | \
			       LDST_SRCDST_WORD_DECOCTRL | \
			       (LDOFF_ENABLE_AUTO_NFIFO << LDST_OFFSET_SHIFT))

बाह्य bool caam_little_end;
बाह्य माप_प्रकार caam_ptr_sz;

/*
 * HW fetches 4 S/G table entries at a समय, irrespective of how many entries
 * are in the table. It's SW's responsibility to make sure these accesses
 * करो not have side effects.
 */
अटल अंतरभूत पूर्णांक pad_sg_nents(पूर्णांक sg_nents)
अणु
	वापस ALIGN(sg_nents, 4);
पूर्ण

अटल अंतरभूत पूर्णांक desc_len(u32 * स्थिर desc)
अणु
	वापस caam32_to_cpu(*desc) & HDR_DESCLEN_MASK;
पूर्ण

अटल अंतरभूत पूर्णांक desc_bytes(व्योम * स्थिर desc)
अणु
	वापस desc_len(desc) * CAAM_CMD_SZ;
पूर्ण

अटल अंतरभूत u32 *desc_end(u32 * स्थिर desc)
अणु
	वापस desc + desc_len(desc);
पूर्ण

अटल अंतरभूत व्योम *sh_desc_pdb(u32 * स्थिर desc)
अणु
	वापस desc + 1;
पूर्ण

अटल अंतरभूत व्योम init_desc(u32 * स्थिर desc, u32 options)
अणु
	*desc = cpu_to_caam32((options | HDR_ONE) + 1);
पूर्ण

अटल अंतरभूत व्योम init_sh_desc(u32 * स्थिर desc, u32 options)
अणु
	PRINT_POS;
	init_desc(desc, CMD_SHARED_DESC_HDR | options);
पूर्ण

अटल अंतरभूत व्योम init_sh_desc_pdb(u32 * स्थिर desc, u32 options,
				    माप_प्रकार pdb_bytes)
अणु
	u32 pdb_len = (pdb_bytes + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ;

	init_sh_desc(desc, (((pdb_len + 1) << HDR_START_IDX_SHIFT) + pdb_len) |
		     options);
पूर्ण

अटल अंतरभूत व्योम init_job_desc(u32 * स्थिर desc, u32 options)
अणु
	init_desc(desc, CMD_DESC_HDR | options);
पूर्ण

अटल अंतरभूत व्योम init_job_desc_pdb(u32 * स्थिर desc, u32 options,
				     माप_प्रकार pdb_bytes)
अणु
	u32 pdb_len = (pdb_bytes + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ;

	init_job_desc(desc, (((pdb_len + 1) << HDR_START_IDX_SHIFT)) | options);
पूर्ण

अटल अंतरभूत व्योम append_ptr(u32 * स्थिर desc, dma_addr_t ptr)
अणु
	अगर (caam_ptr_sz == माप(dma_addr_t)) अणु
		dma_addr_t *offset = (dma_addr_t *)desc_end(desc);

		*offset = cpu_to_caam_dma(ptr);
	पूर्ण अन्यथा अणु
		u32 *offset = (u32 *)desc_end(desc);

		*offset = cpu_to_caam_dma(ptr);
	पूर्ण

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) +
				CAAM_PTR_SZ / CAAM_CMD_SZ);
पूर्ण

अटल अंतरभूत व्योम init_job_desc_shared(u32 * स्थिर desc, dma_addr_t ptr,
					पूर्णांक len, u32 options)
अणु
	PRINT_POS;
	init_job_desc(desc, HDR_SHARED | options |
		      (len << HDR_START_IDX_SHIFT));
	append_ptr(desc, ptr);
पूर्ण

अटल अंतरभूत व्योम append_data(u32 * स्थिर desc, स्थिर व्योम *data, पूर्णांक len)
अणु
	u32 *offset = desc_end(desc);

	अगर (len) /* aव्योम sparse warning: स_नकल with byte count of 0 */
		स_नकल(offset, data, len);

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) +
				(len + CAAM_CMD_SZ - 1) / CAAM_CMD_SZ);
पूर्ण

अटल अंतरभूत व्योम append_cmd(u32 * स्थिर desc, u32 command)
अणु
	u32 *cmd = desc_end(desc);

	*cmd = cpu_to_caam32(command);

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + 1);
पूर्ण

#घोषणा append_u32 append_cmd

अटल अंतरभूत व्योम append_u64(u32 * स्थिर desc, u64 data)
अणु
	u32 *offset = desc_end(desc);

	/* Only 32-bit alignment is guaranteed in descriptor buffer */
	अगर (caam_little_end) अणु
		*offset = cpu_to_caam32(lower_32_bits(data));
		*(++offset) = cpu_to_caam32(upper_32_bits(data));
	पूर्ण अन्यथा अणु
		*offset = cpu_to_caam32(upper_32_bits(data));
		*(++offset) = cpu_to_caam32(lower_32_bits(data));
	पूर्ण

	(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + 2);
पूर्ण

/* Write command without affecting header, and वापस poपूर्णांकer to next word */
अटल अंतरभूत u32 *ग_लिखो_cmd(u32 * स्थिर desc, u32 command)
अणु
	*desc = cpu_to_caam32(command);

	वापस desc + 1;
पूर्ण

अटल अंतरभूत व्योम append_cmd_ptr(u32 * स्थिर desc, dma_addr_t ptr, पूर्णांक len,
				  u32 command)
अणु
	append_cmd(desc, command | len);
	append_ptr(desc, ptr);
पूर्ण

/* Write length after poपूर्णांकer, rather than inside command */
अटल अंतरभूत व्योम append_cmd_ptr_extlen(u32 * स्थिर desc, dma_addr_t ptr,
					 अचिन्हित पूर्णांक len, u32 command)
अणु
	append_cmd(desc, command);
	अगर (!(command & (SQIN_RTO | SQIN_PRE)))
		append_ptr(desc, ptr);
	append_cmd(desc, len);
पूर्ण

अटल अंतरभूत व्योम append_cmd_data(u32 * स्थिर desc, स्थिर व्योम *data, पूर्णांक len,
				   u32 command)
अणु
	append_cmd(desc, command | IMMEDIATE | len);
	append_data(desc, data, len);
पूर्ण

#घोषणा APPEND_CMD_RET(cmd, op) \
अटल अंतरभूत u32 *append_##cmd(u32 * स्थिर desc, u32 options) \
अणु \
	u32 *cmd = desc_end(desc); \
	PRINT_POS; \
	append_cmd(desc, CMD_##op | options); \
	वापस cmd; \
पूर्ण
APPEND_CMD_RET(jump, JUMP)
APPEND_CMD_RET(move, MOVE)
APPEND_CMD_RET(move_len, MOVE_LEN)

अटल अंतरभूत व्योम set_jump_tgt_here(u32 * स्थिर desc, u32 *jump_cmd)
अणु
	*jump_cmd = cpu_to_caam32(caam32_to_cpu(*jump_cmd) |
				  (desc_len(desc) - (jump_cmd - desc)));
पूर्ण

अटल अंतरभूत व्योम set_move_tgt_here(u32 * स्थिर desc, u32 *move_cmd)
अणु
	u32 val = caam32_to_cpu(*move_cmd);

	val &= ~MOVE_OFFSET_MASK;
	val |= (desc_len(desc) << (MOVE_OFFSET_SHIFT + 2)) & MOVE_OFFSET_MASK;
	*move_cmd = cpu_to_caam32(val);
पूर्ण

#घोषणा APPEND_CMD(cmd, op) \
अटल अंतरभूत व्योम append_##cmd(u32 * स्थिर desc, u32 options) \
अणु \
	PRINT_POS; \
	append_cmd(desc, CMD_##op | options); \
पूर्ण
APPEND_CMD(operation, OPERATION)

#घोषणा APPEND_CMD_LEN(cmd, op) \
अटल अंतरभूत व्योम append_##cmd(u32 * स्थिर desc, अचिन्हित पूर्णांक len, \
				u32 options) \
अणु \
	PRINT_POS; \
	append_cmd(desc, CMD_##op | len | options); \
पूर्ण

APPEND_CMD_LEN(seq_load, SEQ_LOAD)
APPEND_CMD_LEN(seq_store, SEQ_STORE)
APPEND_CMD_LEN(seq_fअगरo_load, SEQ_FIFO_LOAD)
APPEND_CMD_LEN(seq_fअगरo_store, SEQ_FIFO_STORE)

#घोषणा APPEND_CMD_PTR(cmd, op) \
अटल अंतरभूत व्योम append_##cmd(u32 * स्थिर desc, dma_addr_t ptr, \
				अचिन्हित पूर्णांक len, u32 options) \
अणु \
	PRINT_POS; \
	append_cmd_ptr(desc, ptr, len, CMD_##op | options); \
पूर्ण
APPEND_CMD_PTR(key, KEY)
APPEND_CMD_PTR(load, LOAD)
APPEND_CMD_PTR(fअगरo_load, FIFO_LOAD)
APPEND_CMD_PTR(fअगरo_store, FIFO_STORE)

अटल अंतरभूत व्योम append_store(u32 * स्थिर desc, dma_addr_t ptr,
				अचिन्हित पूर्णांक len, u32 options)
अणु
	u32 cmd_src;

	cmd_src = options & LDST_SRCDST_MASK;

	append_cmd(desc, CMD_STORE | options | len);

	/* The following options करो not require poपूर्णांकer */
	अगर (!(cmd_src == LDST_SRCDST_WORD_DESCBUF_SHARED ||
	      cmd_src == LDST_SRCDST_WORD_DESCBUF_JOB    ||
	      cmd_src == LDST_SRCDST_WORD_DESCBUF_JOB_WE ||
	      cmd_src == LDST_SRCDST_WORD_DESCBUF_SHARED_WE))
		append_ptr(desc, ptr);
पूर्ण

#घोषणा APPEND_SEQ_PTR_INTLEN(cmd, op) \
अटल अंतरभूत व्योम append_seq_##cmd##_ptr_पूर्णांकlen(u32 * स्थिर desc, \
						 dma_addr_t ptr, \
						 अचिन्हित पूर्णांक len, \
						 u32 options) \
अणु \
	PRINT_POS; \
	अगर (options & (SQIN_RTO | SQIN_PRE)) \
		append_cmd(desc, CMD_SEQ_##op##_PTR | len | options); \
	अन्यथा \
		append_cmd_ptr(desc, ptr, len, CMD_SEQ_##op##_PTR | options); \
पूर्ण
APPEND_SEQ_PTR_INTLEN(in, IN)
APPEND_SEQ_PTR_INTLEN(out, OUT)

#घोषणा APPEND_CMD_PTR_TO_IMM(cmd, op) \
अटल अंतरभूत व्योम append_##cmd##_as_imm(u32 * स्थिर desc, स्थिर व्योम *data, \
					 अचिन्हित पूर्णांक len, u32 options) \
अणु \
	PRINT_POS; \
	append_cmd_data(desc, data, len, CMD_##op | options); \
पूर्ण
APPEND_CMD_PTR_TO_IMM(load, LOAD);
APPEND_CMD_PTR_TO_IMM(fअगरo_load, FIFO_LOAD);

#घोषणा APPEND_CMD_PTR_EXTLEN(cmd, op) \
अटल अंतरभूत व्योम append_##cmd##_extlen(u32 * स्थिर desc, dma_addr_t ptr, \
					 अचिन्हित पूर्णांक len, u32 options) \
अणु \
	PRINT_POS; \
	append_cmd_ptr_extlen(desc, ptr, len, CMD_##op | SQIN_EXT | options); \
पूर्ण
APPEND_CMD_PTR_EXTLEN(seq_in_ptr, SEQ_IN_PTR)
APPEND_CMD_PTR_EXTLEN(seq_out_ptr, SEQ_OUT_PTR)

/*
 * Determine whether to store length पूर्णांकernally or बाह्यally depending on
 * the size of its type
 */
#घोषणा APPEND_CMD_PTR_LEN(cmd, op, type) \
अटल अंतरभूत व्योम append_##cmd(u32 * स्थिर desc, dma_addr_t ptr, \
				type len, u32 options) \
अणु \
	PRINT_POS; \
	अगर (माप(type) > माप(u16)) \
		append_##cmd##_extlen(desc, ptr, len, options); \
	अन्यथा \
		append_##cmd##_पूर्णांकlen(desc, ptr, len, options); \
पूर्ण
APPEND_CMD_PTR_LEN(seq_in_ptr, SEQ_IN_PTR, u32)
APPEND_CMD_PTR_LEN(seq_out_ptr, SEQ_OUT_PTR, u32)

/*
 * 2nd variant क्रम commands whose specअगरied immediate length dअगरfers
 * from length of immediate data provided, e.g., split keys
 */
#घोषणा APPEND_CMD_PTR_TO_IMM2(cmd, op) \
अटल अंतरभूत व्योम append_##cmd##_as_imm(u32 * स्थिर desc, स्थिर व्योम *data, \
					 अचिन्हित पूर्णांक data_len, \
					 अचिन्हित पूर्णांक len, u32 options) \
अणु \
	PRINT_POS; \
	append_cmd(desc, CMD_##op | IMMEDIATE | len | options); \
	append_data(desc, data, data_len); \
पूर्ण
APPEND_CMD_PTR_TO_IMM2(key, KEY);

#घोषणा APPEND_CMD_RAW_IMM(cmd, op, type) \
अटल अंतरभूत व्योम append_##cmd##_imm_##type(u32 * स्थिर desc, type immediate, \
					     u32 options) \
अणु \
	PRINT_POS; \
	अगर (options & LDST_LEN_MASK) \
		append_cmd(desc, CMD_##op | IMMEDIATE | options); \
	अन्यथा \
		append_cmd(desc, CMD_##op | IMMEDIATE | options | \
			   माप(type)); \
	append_cmd(desc, immediate); \
पूर्ण
APPEND_CMD_RAW_IMM(load, LOAD, u32);

/*
 * ee - endianness
 * size - size of immediate type in bytes
 */
#घोषणा APPEND_CMD_RAW_IMM2(cmd, op, ee, size) \
अटल अंतरभूत व्योम append_##cmd##_imm_##ee##size(u32 *desc, \
						   u##size immediate, \
						   u32 options) \
अणु \
	__##ee##size data = cpu_to_##ee##size(immediate); \
	PRINT_POS; \
	append_cmd(desc, CMD_##op | IMMEDIATE | options | माप(data)); \
	append_data(desc, &data, माप(data)); \
पूर्ण

APPEND_CMD_RAW_IMM2(load, LOAD, be, 32);

/*
 * Append math command. Only the last part of destination and source need to
 * be specअगरied
 */
#घोषणा APPEND_MATH(op, desc, dest, src_0, src_1, len) \
append_cmd(desc, CMD_MATH | MATH_FUN_##op | MATH_DEST_##dest | \
	MATH_SRC0_##src_0 | MATH_SRC1_##src_1 | (u32)len);

#घोषणा append_math_add(desc, dest, src0, src1, len) \
	APPEND_MATH(ADD, desc, dest, src0, src1, len)
#घोषणा append_math_sub(desc, dest, src0, src1, len) \
	APPEND_MATH(SUB, desc, dest, src0, src1, len)
#घोषणा append_math_add_c(desc, dest, src0, src1, len) \
	APPEND_MATH(ADDC, desc, dest, src0, src1, len)
#घोषणा append_math_sub_b(desc, dest, src0, src1, len) \
	APPEND_MATH(SUBB, desc, dest, src0, src1, len)
#घोषणा append_math_and(desc, dest, src0, src1, len) \
	APPEND_MATH(AND, desc, dest, src0, src1, len)
#घोषणा append_math_or(desc, dest, src0, src1, len) \
	APPEND_MATH(OR, desc, dest, src0, src1, len)
#घोषणा append_math_xor(desc, dest, src0, src1, len) \
	APPEND_MATH(XOR, desc, dest, src0, src1, len)
#घोषणा append_math_lshअगरt(desc, dest, src0, src1, len) \
	APPEND_MATH(LSHIFT, desc, dest, src0, src1, len)
#घोषणा append_math_rshअगरt(desc, dest, src0, src1, len) \
	APPEND_MATH(RSHIFT, desc, dest, src0, src1, len)
#घोषणा append_math_ldshअगरt(desc, dest, src0, src1, len) \
	APPEND_MATH(SHLD, desc, dest, src0, src1, len)

/* Exactly one source is IMM. Data is passed in as u32 value */
#घोषणा APPEND_MATH_IMM_u32(op, desc, dest, src_0, src_1, data) \
करो अणु \
	APPEND_MATH(op, desc, dest, src_0, src_1, CAAM_CMD_SZ); \
	append_cmd(desc, data); \
पूर्ण जबतक (0)

#घोषणा append_math_add_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(ADD, desc, dest, src0, src1, data)
#घोषणा append_math_sub_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(SUB, desc, dest, src0, src1, data)
#घोषणा append_math_add_c_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(ADDC, desc, dest, src0, src1, data)
#घोषणा append_math_sub_b_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(SUBB, desc, dest, src0, src1, data)
#घोषणा append_math_and_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(AND, desc, dest, src0, src1, data)
#घोषणा append_math_or_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(OR, desc, dest, src0, src1, data)
#घोषणा append_math_xor_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(XOR, desc, dest, src0, src1, data)
#घोषणा append_math_lshअगरt_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(LSHIFT, desc, dest, src0, src1, data)
#घोषणा append_math_rshअगरt_imm_u32(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u32(RSHIFT, desc, dest, src0, src1, data)

/* Exactly one source is IMM. Data is passed in as u64 value */
#घोषणा APPEND_MATH_IMM_u64(op, desc, dest, src_0, src_1, data) \
करो अणु \
	u32 upper = (data >> 16) >> 16; \
	APPEND_MATH(op, desc, dest, src_0, src_1, CAAM_CMD_SZ * 2 | \
		    (upper ? 0 : MATH_IFB)); \
	अगर (upper) \
		append_u64(desc, data); \
	अन्यथा \
		append_u32(desc, lower_32_bits(data)); \
पूर्ण जबतक (0)

#घोषणा append_math_add_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(ADD, desc, dest, src0, src1, data)
#घोषणा append_math_sub_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(SUB, desc, dest, src0, src1, data)
#घोषणा append_math_add_c_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(ADDC, desc, dest, src0, src1, data)
#घोषणा append_math_sub_b_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(SUBB, desc, dest, src0, src1, data)
#घोषणा append_math_and_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(AND, desc, dest, src0, src1, data)
#घोषणा append_math_or_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(OR, desc, dest, src0, src1, data)
#घोषणा append_math_xor_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(XOR, desc, dest, src0, src1, data)
#घोषणा append_math_lshअगरt_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(LSHIFT, desc, dest, src0, src1, data)
#घोषणा append_math_rshअगरt_imm_u64(desc, dest, src0, src1, data) \
	APPEND_MATH_IMM_u64(RSHIFT, desc, dest, src0, src1, data)

/**
 * काष्ठा alginfo - Container क्रम algorithm details
 * @algtype: algorithm selector; क्रम valid values, see करोcumentation of the
 *           functions where it is used.
 * @keylen: length of the provided algorithm key, in bytes
 * @keylen_pad: padded length of the provided algorithm key, in bytes
 * @key_dma: dma (bus) address where algorithm key resides
 * @key_virt: भव address where algorithm key resides
 * @key_अंतरभूत: true - key can be अंतरभूतd in the descriptor; false - key is
 *              referenced by the descriptor
 */
काष्ठा alginfo अणु
	u32 algtype;
	अचिन्हित पूर्णांक keylen;
	अचिन्हित पूर्णांक keylen_pad;
	dma_addr_t key_dma;
	स्थिर व्योम *key_virt;
	bool key_अंतरभूत;
पूर्ण;

/**
 * desc_अंतरभूत_query() - Provide indications on which data items can be अंतरभूतd
 *                       and which shall be referenced in a shared descriptor.
 * @sd_base_len: Shared descriptor base length - bytes consumed by the commands,
 *               excluding the data items to be अंतरभूतd (or corresponding
 *               poपूर्णांकer अगर an item is not अंतरभूतd). Each cnstr_* function that
 *               generates descriptors should have a define mentioning
 *               corresponding length.
 * @jd_len: Maximum length of the job descriptor(s) that will be used
 *          together with the shared descriptor.
 * @data_len: Array of lengths of the data items trying to be अंतरभूतd
 * @inl_mask: 32bit mask with bit x = 1 अगर data item x can be अंतरभूतd, 0
 *            otherwise.
 * @count: Number of data items (size of @data_len array); must be <= 32
 *
 * Return: 0 अगर data can be अंतरभूतd / referenced, negative value अगर not. If 0,
 *         check @inl_mask क्रम details.
 */
अटल अंतरभूत पूर्णांक desc_अंतरभूत_query(अचिन्हित पूर्णांक sd_base_len,
				    अचिन्हित पूर्णांक jd_len, अचिन्हित पूर्णांक *data_len,
				    u32 *inl_mask, अचिन्हित पूर्णांक count)
अणु
	पूर्णांक rem_bytes = (पूर्णांक)(CAAM_DESC_BYTES_MAX - sd_base_len - jd_len);
	अचिन्हित पूर्णांक i;

	*inl_mask = 0;
	क्रम (i = 0; (i < count) && (rem_bytes > 0); i++) अणु
		अगर (rem_bytes - (पूर्णांक)(data_len[i] +
			(count - i - 1) * CAAM_PTR_SZ) >= 0) अणु
			rem_bytes -= data_len[i];
			*inl_mask |= (1 << i);
		पूर्ण अन्यथा अणु
			rem_bytes -= CAAM_PTR_SZ;
		पूर्ण
	पूर्ण

	वापस (rem_bytes >= 0) ? 0 : -1;
पूर्ण

/**
 * append_proto_dkp - Derived Key Protocol (DKP): key -> split key
 * @desc: poपूर्णांकer to buffer used क्रम descriptor स्थिरruction
 * @adata: poपूर्णांकer to authentication transक्रमm definitions.
 *         keylen should be the length of initial key, जबतक keylen_pad
 *         the length of the derived (split) key.
 *         Valid algorithm values - one of OP_ALG_ALGSEL_अणुMD5, SHA1, SHA224,
 *         SHA256, SHA384, SHA512पूर्ण.
 */
अटल अंतरभूत व्योम append_proto_dkp(u32 * स्थिर desc, काष्ठा alginfo *adata)
अणु
	u32 protid;

	/*
	 * Quick & dirty translation from OP_ALG_ALGSEL_अणुMD5, SHA*पूर्ण
	 * to OP_PCLID_DKP_अणुMD5, SHA*पूर्ण
	 */
	protid = (adata->algtype & OP_ALG_ALGSEL_SUBMASK) |
		 (0x20 << OP_ALG_ALGSEL_SHIFT);

	अगर (adata->key_अंतरभूत) अणु
		पूर्णांक words;

		अगर (adata->keylen > adata->keylen_pad) अणु
			append_operation(desc, OP_TYPE_UNI_PROTOCOL | protid |
					 OP_PCL_DKP_SRC_PTR |
					 OP_PCL_DKP_DST_IMM | adata->keylen);
			append_ptr(desc, adata->key_dma);

			words = (ALIGN(adata->keylen_pad, CAAM_CMD_SZ) -
				 CAAM_PTR_SZ) / CAAM_CMD_SZ;
		पूर्ण अन्यथा अणु
			append_operation(desc, OP_TYPE_UNI_PROTOCOL | protid |
					 OP_PCL_DKP_SRC_IMM |
					 OP_PCL_DKP_DST_IMM | adata->keylen);
			append_data(desc, adata->key_virt, adata->keylen);

			words = (ALIGN(adata->keylen_pad, CAAM_CMD_SZ) -
				 ALIGN(adata->keylen, CAAM_CMD_SZ)) /
				CAAM_CMD_SZ;
		पूर्ण

		/* Reserve space in descriptor buffer क्रम the derived key */
		अगर (words)
			(*desc) = cpu_to_caam32(caam32_to_cpu(*desc) + words);
	पूर्ण अन्यथा अणु
		append_operation(desc, OP_TYPE_UNI_PROTOCOL | protid |
				 OP_PCL_DKP_SRC_PTR | OP_PCL_DKP_DST_PTR |
				 adata->keylen);
		append_ptr(desc, adata->key_dma);
	पूर्ण
पूर्ण

#पूर्ण_अगर /* DESC_CONSTR_H */
