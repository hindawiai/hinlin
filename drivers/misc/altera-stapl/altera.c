<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * altera.c
 *
 * altera FPGA driver
 *
 * Copyright (C) Altera Corporation 1998-2001
 * Copyright (C) 2010,2011 NetUP Inc.
 * Copyright (C) 2010,2011 Igor M. Liplianin <liplianin@netup.ru>
 */

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <misc/altera.h>
#समावेश "altera-exprt.h"
#समावेश "altera-jtag.h"

अटल पूर्णांक debug = 1;
module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debugging information");

MODULE_DESCRIPTION("altera FPGA kernel module");
MODULE_AUTHOR("Igor M. Liplianin  <liplianin@netup.ru>");
MODULE_LICENSE("GPL");

#घोषणा dprपूर्णांकk(args...) \
	अगर (debug) अणु \
		prपूर्णांकk(KERN_DEBUG args); \
	पूर्ण

क्रमागत altera_fpga_opcode अणु
	OP_NOP = 0,
	OP_DUP,
	OP_SWP,
	OP_ADD,
	OP_SUB,
	OP_MULT,
	OP_DIV,
	OP_MOD,
	OP_SHL,
	OP_SHR,
	OP_NOT,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_INV,
	OP_GT,
	OP_LT,
	OP_RET,
	OP_CMPS,
	OP_PINT,
	OP_PRNT,
	OP_DSS,
	OP_DSSC,
	OP_ISS,
	OP_ISSC,
	OP_DPR = 0x1c,
	OP_DPRL,
	OP_DPO,
	OP_DPOL,
	OP_IPR,
	OP_IPRL,
	OP_IPO,
	OP_IPOL,
	OP_PCHR,
	OP_EXIT,
	OP_EQU,
	OP_POPT,
	OP_ABS = 0x2c,
	OP_BCH0,
	OP_PSH0 = 0x2f,
	OP_PSHL = 0x40,
	OP_PSHV,
	OP_JMP,
	OP_CALL,
	OP_NEXT,
	OP_PSTR,
	OP_SINT = 0x47,
	OP_ST,
	OP_ISTP,
	OP_DSTP,
	OP_SWPN,
	OP_DUPN,
	OP_POPV,
	OP_POPE,
	OP_POPA,
	OP_JMPZ,
	OP_DS,
	OP_IS,
	OP_DPRA,
	OP_DPOA,
	OP_IPRA,
	OP_IPOA,
	OP_EXPT,
	OP_PSHE,
	OP_PSHA,
	OP_DYNA,
	OP_EXPV = 0x5c,
	OP_COPY = 0x80,
	OP_REVA,
	OP_DSC,
	OP_ISC,
	OP_WAIT,
	OP_VS,
	OP_CMPA = 0xc0,
	OP_VSC,
पूर्ण;

काष्ठा altera_procinfo अणु
	अक्षर			*name;
	u8			attrs;
	काष्ठा altera_procinfo	*next;
पूर्ण;

/* This function checks अगर enough parameters are available on the stack. */
अटल पूर्णांक altera_check_stack(पूर्णांक stack_ptr, पूर्णांक count, पूर्णांक *status)
अणु
	अगर (stack_ptr < count) अणु
		*status = -EOVERFLOW;
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम altera_export_पूर्णांक(अक्षर *key, s32 value)
अणु
	dprपूर्णांकk("Export: key = \"%s\", value = %d\n", key, value);
पूर्ण

#घोषणा HEX_LINE_CHARS 72
#घोषणा HEX_LINE_BITS (HEX_LINE_CHARS * 4)

अटल व्योम altera_export_bool_array(अक्षर *key, u8 *data, s32 count)
अणु
	अक्षर string[HEX_LINE_CHARS + 1];
	s32 i, offset;
	u32 size, line, lines, linebits, value, j, k;

	अगर (count > HEX_LINE_BITS) अणु
		dprपूर्णांकk("Export: key = \"%s\", %d bits, value = HEX\n",
							key, count);
		lines = (count + (HEX_LINE_BITS - 1)) / HEX_LINE_BITS;

		क्रम (line = 0; line < lines; ++line) अणु
			अगर (line < (lines - 1)) अणु
				linebits = HEX_LINE_BITS;
				size = HEX_LINE_CHARS;
				offset = count - ((line + 1) * HEX_LINE_BITS);
			पूर्ण अन्यथा अणु
				linebits =
					count - ((lines - 1) * HEX_LINE_BITS);
				size = (linebits + 3) / 4;
				offset = 0L;
			पूर्ण

			string[size] = '\0';
			j = size - 1;
			value = 0;

			क्रम (k = 0; k < linebits; ++k) अणु
				i = k + offset;
				अगर (data[i >> 3] & (1 << (i & 7)))
					value |= (1 << (i & 3));
				अगर ((i & 3) == 3) अणु
					प्र_लिखो(&string[j], "%1x", value);
					value = 0;
					--j;
				पूर्ण
			पूर्ण
			अगर ((k & 3) > 0)
				प्र_लिखो(&string[j], "%1x", value);

			dprपूर्णांकk("%s\n", string);
		पूर्ण

	पूर्ण अन्यथा अणु
		size = (count + 3) / 4;
		string[size] = '\0';
		j = size - 1;
		value = 0;

		क्रम (i = 0; i < count; ++i) अणु
			अगर (data[i >> 3] & (1 << (i & 7)))
				value |= (1 << (i & 3));
			अगर ((i & 3) == 3) अणु
				प्र_लिखो(&string[j], "%1x", value);
				value = 0;
				--j;
			पूर्ण
		पूर्ण
		अगर ((i & 3) > 0)
			प्र_लिखो(&string[j], "%1x", value);

		dprपूर्णांकk("Export: key = \"%s\", %d bits, value = HEX %s\n",
			key, count, string);
	पूर्ण
पूर्ण

अटल पूर्णांक altera_execute(काष्ठा altera_state *astate,
				u8 *p,
				s32 program_size,
				s32 *error_address,
				पूर्णांक *निकास_code,
				पूर्णांक *क्रमmat_version)
अणु
	काष्ठा altera_config *aconf = astate->config;
	अक्षर *msg_buff = astate->msg_buff;
	दीर्घ *stack = astate->stack;
	पूर्णांक status = 0;
	u32 first_word = 0L;
	u32 action_table = 0L;
	u32 proc_table = 0L;
	u32 str_table = 0L;
	u32 sym_table = 0L;
	u32 data_sect = 0L;
	u32 code_sect = 0L;
	u32 debug_sect = 0L;
	u32 action_count = 0L;
	u32 proc_count = 0L;
	u32 sym_count = 0L;
	दीर्घ *vars = शून्य;
	s32 *var_size = शून्य;
	अक्षर *attrs = शून्य;
	u8 *proc_attributes = शून्य;
	u32 pc;
	u32 opcode_address;
	u32 args[3];
	u32 opcode;
	u32 name_id;
	u8 अक्षरbuf[4];
	दीर्घ दीर्घ_पंचांगp;
	u32 variable_id;
	u8 *अक्षरptr_पंचांगp;
	u8 *अक्षरptr_पंचांगp2;
	दीर्घ *दीर्घptr_पंचांगp;
	पूर्णांक version = 0;
	पूर्णांक delta = 0;
	पूर्णांक stack_ptr = 0;
	u32 arg_count;
	पूर्णांक करोne = 0;
	पूर्णांक bad_opcode = 0;
	u32 count;
	u32 index;
	u32 index2;
	s32 दीर्घ_count;
	s32 दीर्घ_idx;
	s32 दीर्घ_idx2;
	u32 i;
	u32 j;
	u32 uncomp_size;
	u32 offset;
	u32 value;
	पूर्णांक current_proc = 0;
	पूर्णांक reverse;

	अक्षर *name;

	dprपूर्णांकk("%s\n", __func__);

	/* Read header inक्रमmation */
	अगर (program_size > 52L) अणु
		first_word    = get_unaligned_be32(&p[0]);
		version = (first_word & 1L);
		*क्रमmat_version = version + 1;
		delta = version * 8;

		action_table  = get_unaligned_be32(&p[4]);
		proc_table    = get_unaligned_be32(&p[8]);
		str_table  = get_unaligned_be32(&p[4 + delta]);
		sym_table  = get_unaligned_be32(&p[16 + delta]);
		data_sect  = get_unaligned_be32(&p[20 + delta]);
		code_sect  = get_unaligned_be32(&p[24 + delta]);
		debug_sect = get_unaligned_be32(&p[28 + delta]);
		action_count  = get_unaligned_be32(&p[40 + delta]);
		proc_count    = get_unaligned_be32(&p[44 + delta]);
		sym_count  = get_unaligned_be32(&p[48 + (2 * delta)]);
	पूर्ण

	अगर ((first_word != 0x4A414D00L) && (first_word != 0x4A414D01L)) अणु
		करोne = 1;
		status = -EIO;
		जाओ निकास_करोne;
	पूर्ण

	अगर (sym_count <= 0)
		जाओ निकास_करोne;

	vars = kसुस्मृति(sym_count, माप(दीर्घ), GFP_KERNEL);

	अगर (vars == शून्य)
		status = -ENOMEM;

	अगर (status == 0) अणु
		var_size = kसुस्मृति(sym_count, माप(s32), GFP_KERNEL);

		अगर (var_size == शून्य)
			status = -ENOMEM;
	पूर्ण

	अगर (status == 0) अणु
		attrs = kzalloc(sym_count, GFP_KERNEL);

		अगर (attrs == शून्य)
			status = -ENOMEM;
	पूर्ण

	अगर ((status == 0) && (version > 0)) अणु
		proc_attributes = kzalloc(proc_count, GFP_KERNEL);

		अगर (proc_attributes == शून्य)
			status = -ENOMEM;
	पूर्ण

	अगर (status != 0)
		जाओ निकास_करोne;

	delta = version * 2;

	क्रम (i = 0; i < sym_count; ++i) अणु
		offset = (sym_table + ((11 + delta) * i));

		value = get_unaligned_be32(&p[offset + 3 + delta]);

		attrs[i] = p[offset];

		/*
		 * use bit 7 of attribute byte to indicate that
		 * this buffer was dynamically allocated
		 * and should be मुक्तd later
		 */
		attrs[i] &= 0x7f;

		var_size[i] = get_unaligned_be32(&p[offset + 7 + delta]);

		/*
		 * Attribute bits:
		 * bit 0: 0 = पढ़ो-only, 1 = पढ़ो-ग_लिखो
		 * bit 1: 0 = not compressed, 1 = compressed
		 * bit 2: 0 = not initialized, 1 = initialized
		 * bit 3: 0 = scalar, 1 = array
		 * bit 4: 0 = Boolean, 1 = पूर्णांकeger
		 * bit 5: 0 = declared variable,
		 *	1 = compiler created temporary variable
		 */

		अगर ((attrs[i] & 0x0c) == 0x04)
			/* initialized scalar variable */
			vars[i] = value;
		अन्यथा अगर ((attrs[i] & 0x1e) == 0x0e) अणु
			/* initialized compressed Boolean array */
			uncomp_size = get_unaligned_le32(&p[data_sect + value]);

			/* allocate a buffer क्रम the uncompressed data */
			vars[i] = (दीर्घ)kzalloc(uncomp_size, GFP_KERNEL);
			अगर (vars[i] == 0L)
				status = -ENOMEM;
			अन्यथा अणु
				/* set flag so buffer will be मुक्तd later */
				attrs[i] |= 0x80;

				/* uncompress the data */
				अगर (altera_shrink(&p[data_sect + value],
						var_size[i],
						(u8 *)vars[i],
						uncomp_size,
						version) != uncomp_size)
					/* decompression failed */
					status = -EIO;
				अन्यथा
					var_size[i] = uncomp_size * 8L;

			पूर्ण
		पूर्ण अन्यथा अगर ((attrs[i] & 0x1e) == 0x0c) अणु
			/* initialized Boolean array */
			vars[i] = value + data_sect + (दीर्घ)p;
		पूर्ण अन्यथा अगर ((attrs[i] & 0x1c) == 0x1c) अणु
			/* initialized पूर्णांकeger array */
			vars[i] = value + data_sect;
		पूर्ण अन्यथा अगर ((attrs[i] & 0x0c) == 0x08) अणु
			/* uninitialized array */

			/* flag attrs so that memory is मुक्तd */
			attrs[i] |= 0x80;

			अगर (var_size[i] > 0) अणु
				u32 size;

				अगर (attrs[i] & 0x10)
					/* पूर्णांकeger array */
					size = (var_size[i] * माप(s32));
				अन्यथा
					/* Boolean array */
					size = ((var_size[i] + 7L) / 8L);

				vars[i] = (दीर्घ)kzalloc(size, GFP_KERNEL);

				अगर (vars[i] == 0) अणु
					status = -ENOMEM;
				पूर्ण अन्यथा अणु
					/* zero out memory */
					क्रम (j = 0; j < size; ++j)
						((u8 *)(vars[i]))[j] = 0;

				पूर्ण
			पूर्ण अन्यथा
				vars[i] = 0;

		पूर्ण अन्यथा
			vars[i] = 0;

	पूर्ण

निकास_करोne:
	अगर (status != 0)
		करोne = 1;

	altera_jinit(astate);

	pc = code_sect;
	msg_buff[0] = '\0';

	/*
	 * For JBC version 2, we will execute the procedures corresponding to
	 * the selected ACTION
	 */
	अगर (version > 0) अणु
		अगर (aconf->action == शून्य) अणु
			status = -EINVAL;
			करोne = 1;
		पूर्ण अन्यथा अणु
			पूर्णांक action_found = 0;
			क्रम (i = 0; (i < action_count) && !action_found; ++i) अणु
				name_id = get_unaligned_be32(&p[action_table +
								(12 * i)]);

				name = &p[str_table + name_id];

				अगर (strnहालcmp(aconf->action, name, म_माप(name)) == 0) अणु
					action_found = 1;
					current_proc =
						get_unaligned_be32(&p[action_table +
								(12 * i) + 8]);
				पूर्ण
			पूर्ण

			अगर (!action_found) अणु
				status = -EINVAL;
				करोne = 1;
			पूर्ण
		पूर्ण

		अगर (status == 0) अणु
			पूर्णांक first_समय = 1;
			i = current_proc;
			जबतक ((i != 0) || first_समय) अणु
				first_समय = 0;
				/* check procedure attribute byte */
				proc_attributes[i] =
						(p[proc_table +
								(13 * i) + 8] &
									0x03);

				/*
				 * BIT0 - OPTIONAL
				 * BIT1 - RECOMMENDED
				 * BIT6 - FORCED OFF
				 * BIT7 - FORCED ON
				 */

				i = get_unaligned_be32(&p[proc_table +
							(13 * i) + 4]);
			पूर्ण

			/*
			 * Set current_proc to the first procedure
			 * to be executed
			 */
			i = current_proc;
			जबतक ((i != 0) &&
				((proc_attributes[i] == 1) ||
				((proc_attributes[i] & 0xc0) == 0x40))) अणु
				i = get_unaligned_be32(&p[proc_table +
							(13 * i) + 4]);
			पूर्ण

			अगर ((i != 0) || ((i == 0) && (current_proc == 0) &&
				((proc_attributes[0] != 1) &&
				((proc_attributes[0] & 0xc0) != 0x40)))) अणु
				current_proc = i;
				pc = code_sect +
					get_unaligned_be32(&p[proc_table +
								(13 * i) + 9]);
				अगर ((pc < code_sect) || (pc >= debug_sect))
					status = -दुस्फल;
			पूर्ण अन्यथा
				/* there are no procedures to execute! */
				करोne = 1;

		पूर्ण
	पूर्ण

	msg_buff[0] = '\0';

	जबतक (!करोne) अणु
		opcode = (p[pc] & 0xff);
		opcode_address = pc;
		++pc;

		अगर (debug > 1)
			prपूर्णांकk("opcode: %02x\n", opcode);

		arg_count = (opcode >> 6) & 3;
		क्रम (i = 0; i < arg_count; ++i) अणु
			args[i] = get_unaligned_be32(&p[pc]);
			pc += 4;
		पूर्ण

		चयन (opcode) अणु
		हाल OP_NOP:
			अवरोध;
		हाल OP_DUP:
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				stack[stack_ptr] = stack[stack_ptr - 1];
				++stack_ptr;
			पूर्ण
			अवरोध;
		हाल OP_SWP:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - 2];
				stack[stack_ptr - 2] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण
			अवरोध;
		हाल OP_ADD:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] += stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_SUB:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] -= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_MULT:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] *= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_DIV:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] /= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_MOD:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] %= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_SHL:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] <<= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_SHR:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] >>= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_NOT:
			अगर (altera_check_stack(stack_ptr, 1, &status))
				stack[stack_ptr - 1] ^= (-1L);

			अवरोध;
		हाल OP_AND:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] &= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_OR:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] |= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_XOR:
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				--stack_ptr;
				stack[stack_ptr - 1] ^= stack[stack_ptr];
			पूर्ण
			अवरोध;
		हाल OP_INV:
			अगर (!altera_check_stack(stack_ptr, 1, &status))
				अवरोध;
			stack[stack_ptr - 1] = stack[stack_ptr - 1] ? 0L : 1L;
			अवरोध;
		हाल OP_GT:
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			--stack_ptr;
			stack[stack_ptr - 1] =
				(stack[stack_ptr - 1] > stack[stack_ptr]) ?
									1L : 0L;

			अवरोध;
		हाल OP_LT:
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			--stack_ptr;
			stack[stack_ptr - 1] =
				(stack[stack_ptr - 1] < stack[stack_ptr]) ?
									1L : 0L;

			अवरोध;
		हाल OP_RET:
			अगर ((version > 0) && (stack_ptr == 0)) अणु
				/*
				 * We completed one of the मुख्य procedures
				 * of an ACTION.
				 * Find the next procedure
				 * to be executed and jump to it.
				 * If there are no more procedures, then EXIT.
				 */
				i = get_unaligned_be32(&p[proc_table +
						(13 * current_proc) + 4]);
				जबतक ((i != 0) &&
					((proc_attributes[i] == 1) ||
					((proc_attributes[i] & 0xc0) == 0x40)))
					i = get_unaligned_be32(&p[proc_table +
								(13 * i) + 4]);

				अगर (i == 0) अणु
					/* no procedures to execute! */
					करोne = 1;
					*निकास_code = 0;	/* success */
				पूर्ण अन्यथा अणु
					current_proc = i;
					pc = code_sect + get_unaligned_be32(
								&p[proc_table +
								(13 * i) + 9]);
					अगर ((pc < code_sect) ||
					    (pc >= debug_sect))
						status = -दुस्फल;
				पूर्ण

			पूर्ण अन्यथा
				अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
					pc = stack[--stack_ptr] + code_sect;
					अगर ((pc <= code_sect) ||
					    (pc >= debug_sect))
						status = -दुस्फल;

				पूर्ण

			अवरोध;
		हाल OP_CMPS:
			/*
			 * Array लघु compare
			 * ...stack 0 is source 1 value
			 * ...stack 1 is source 2 value
			 * ...stack 2 is mask value
			 * ...stack 3 is count
			 */
			अगर (altera_check_stack(stack_ptr, 4, &status)) अणु
				s32 a = stack[--stack_ptr];
				s32 b = stack[--stack_ptr];
				दीर्घ_पंचांगp = stack[--stack_ptr];
				count = stack[stack_ptr - 1];

				अगर ((count < 1) || (count > 32))
					status = -दुस्फल;
				अन्यथा अणु
					दीर्घ_पंचांगp &= ((-1L) >> (32 - count));

					stack[stack_ptr - 1] =
					((a & दीर्घ_पंचांगp) == (b & दीर्घ_पंचांगp))
								? 1L : 0L;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल OP_PINT:
			/*
			 * PRINT add पूर्णांकeger
			 * ...stack 0 is पूर्णांकeger value
			 */
			अगर (!altera_check_stack(stack_ptr, 1, &status))
				अवरोध;
			प्र_लिखो(&msg_buff[म_माप(msg_buff)],
					"%ld", stack[--stack_ptr]);
			अवरोध;
		हाल OP_PRNT:
			/* PRINT finish */
			अगर (debug)
				prपूर्णांकk(msg_buff, "\n");

			msg_buff[0] = '\0';
			अवरोध;
		हाल OP_DSS:
			/*
			 * DRSCAN लघु
			 * ...stack 0 is scan data
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			दीर्घ_पंचांगp = stack[--stack_ptr];
			count = stack[--stack_ptr];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_drscan(astate, count, अक्षरbuf, 0);
			अवरोध;
		हाल OP_DSSC:
			/*
			 * DRSCAN लघु with capture
			 * ...stack 0 is scan data
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			दीर्घ_पंचांगp = stack[--stack_ptr];
			count = stack[stack_ptr - 1];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_swap_dr(astate, count, अक्षरbuf,
							0, अक्षरbuf, 0);
			stack[stack_ptr - 1] = get_unaligned_le32(&अक्षरbuf[0]);
			अवरोध;
		हाल OP_ISS:
			/*
			 * IRSCAN लघु
			 * ...stack 0 is scan data
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			दीर्घ_पंचांगp = stack[--stack_ptr];
			count = stack[--stack_ptr];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_irscan(astate, count, अक्षरbuf, 0);
			अवरोध;
		हाल OP_ISSC:
			/*
			 * IRSCAN लघु with capture
			 * ...stack 0 is scan data
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			दीर्घ_पंचांगp = stack[--stack_ptr];
			count = stack[stack_ptr - 1];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_swap_ir(astate, count, अक्षरbuf,
							0, अक्षरbuf, 0);
			stack[stack_ptr - 1] = get_unaligned_le32(&अक्षरbuf[0]);
			अवरोध;
		हाल OP_DPR:
			अगर (!altera_check_stack(stack_ptr, 1, &status))
				अवरोध;
			count = stack[--stack_ptr];
			status = altera_set_dr_pre(&astate->js, count, 0, शून्य);
			अवरोध;
		हाल OP_DPRL:
			/*
			 * DRPRE with literal data
			 * ...stack 0 is count
			 * ...stack 1 is literal data
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			count = stack[--stack_ptr];
			दीर्घ_पंचांगp = stack[--stack_ptr];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_set_dr_pre(&astate->js, count, 0,
						अक्षरbuf);
			अवरोध;
		हाल OP_DPO:
			/*
			 * DRPOST
			 * ...stack 0 is count
			 */
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				count = stack[--stack_ptr];
				status = altera_set_dr_post(&astate->js, count,
								0, शून्य);
			पूर्ण
			अवरोध;
		हाल OP_DPOL:
			/*
			 * DRPOST with literal data
			 * ...stack 0 is count
			 * ...stack 1 is literal data
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			count = stack[--stack_ptr];
			दीर्घ_पंचांगp = stack[--stack_ptr];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_set_dr_post(&astate->js, count, 0,
							अक्षरbuf);
			अवरोध;
		हाल OP_IPR:
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				count = stack[--stack_ptr];
				status = altera_set_ir_pre(&astate->js, count,
								0, शून्य);
			पूर्ण
			अवरोध;
		हाल OP_IPRL:
			/*
			 * IRPRE with literal data
			 * ...stack 0 is count
			 * ...stack 1 is literal data
			 */
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				count = stack[--stack_ptr];
				दीर्घ_पंचांगp = stack[--stack_ptr];
				put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
				status = altera_set_ir_pre(&astate->js, count,
							0, अक्षरbuf);
			पूर्ण
			अवरोध;
		हाल OP_IPO:
			/*
			 * IRPOST
			 * ...stack 0 is count
			 */
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				count = stack[--stack_ptr];
				status = altera_set_ir_post(&astate->js, count,
							0, शून्य);
			पूर्ण
			अवरोध;
		हाल OP_IPOL:
			/*
			 * IRPOST with literal data
			 * ...stack 0 is count
			 * ...stack 1 is literal data
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			count = stack[--stack_ptr];
			दीर्घ_पंचांगp = stack[--stack_ptr];
			put_unaligned_le32(दीर्घ_पंचांगp, &अक्षरbuf[0]);
			status = altera_set_ir_post(&astate->js, count, 0,
							अक्षरbuf);
			अवरोध;
		हाल OP_PCHR:
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				u8 ch;
				count = म_माप(msg_buff);
				ch = (अक्षर) stack[--stack_ptr];
				अगर ((ch < 1) || (ch > 127)) अणु
					/*
					 * अक्षरacter code out of range
					 * instead of flagging an error,
					 * क्रमce the value to 127
					 */
					ch = 127;
				पूर्ण
				msg_buff[count] = ch;
				msg_buff[count + 1] = '\0';
			पूर्ण
			अवरोध;
		हाल OP_EXIT:
			अगर (altera_check_stack(stack_ptr, 1, &status))
				*निकास_code = stack[--stack_ptr];

			करोne = 1;
			अवरोध;
		हाल OP_EQU:
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			--stack_ptr;
			stack[stack_ptr - 1] =
				(stack[stack_ptr - 1] == stack[stack_ptr]) ?
									1L : 0L;
			अवरोध;
		हाल OP_POPT:
			अगर (altera_check_stack(stack_ptr, 1, &status))
				--stack_ptr;

			अवरोध;
		हाल OP_ABS:
			अगर (!altera_check_stack(stack_ptr, 1, &status))
				अवरोध;
			अगर (stack[stack_ptr - 1] < 0)
				stack[stack_ptr - 1] = 0 - stack[stack_ptr - 1];

			अवरोध;
		हाल OP_BCH0:
			/*
			 * Batch operation 0
			 * SWP
			 * SWPN 7
			 * SWP
			 * SWPN 6
			 * DUPN 8
			 * SWPN 2
			 * SWP
			 * DUPN 6
			 * DUPN 6
			 */

			/* SWP  */
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - 2];
				stack[stack_ptr - 2] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण

			/* SWPN 7 */
			index = 7 + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - index];
				stack[stack_ptr - index] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण

			/* SWP  */
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - 2];
				stack[stack_ptr - 2] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण

			/* SWPN 6 */
			index = 6 + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - index];
				stack[stack_ptr - index] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण

			/* DUPN 8 */
			index = 8 + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				stack[stack_ptr] = stack[stack_ptr - index];
				++stack_ptr;
			पूर्ण

			/* SWPN 2 */
			index = 2 + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - index];
				stack[stack_ptr - index] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण

			/* SWP  */
			अगर (altera_check_stack(stack_ptr, 2, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - 2];
				stack[stack_ptr - 2] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण

			/* DUPN 6 */
			index = 6 + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				stack[stack_ptr] = stack[stack_ptr - index];
				++stack_ptr;
			पूर्ण

			/* DUPN 6 */
			index = 6 + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				stack[stack_ptr] = stack[stack_ptr - index];
				++stack_ptr;
			पूर्ण
			अवरोध;
		हाल OP_PSH0:
			stack[stack_ptr++] = 0;
			अवरोध;
		हाल OP_PSHL:
			stack[stack_ptr++] = (s32) args[0];
			अवरोध;
		हाल OP_PSHV:
			stack[stack_ptr++] = vars[args[0]];
			अवरोध;
		हाल OP_JMP:
			pc = args[0] + code_sect;
			अगर ((pc < code_sect) || (pc >= debug_sect))
				status = -दुस्फल;
			अवरोध;
		हाल OP_CALL:
			stack[stack_ptr++] = pc;
			pc = args[0] + code_sect;
			अगर ((pc < code_sect) || (pc >= debug_sect))
				status = -दुस्फल;
			अवरोध;
		हाल OP_NEXT:
			/*
			 * Process FOR / NEXT loop
			 * ...argument 0 is variable ID
			 * ...stack 0 is step value
			 * ...stack 1 is end value
			 * ...stack 2 is top address
			 */
			अगर (altera_check_stack(stack_ptr, 3, &status)) अणु
				s32 step = stack[stack_ptr - 1];
				s32 end = stack[stack_ptr - 2];
				s32 top = stack[stack_ptr - 3];
				s32 iterator = vars[args[0]];
				पूर्णांक अवरोध_out = 0;

				अगर (step < 0) अणु
					अगर (iterator <= end)
						अवरोध_out = 1;
				पूर्ण अन्यथा अगर (iterator >= end)
					अवरोध_out = 1;

				अगर (अवरोध_out) अणु
					stack_ptr -= 3;
				पूर्ण अन्यथा अणु
					vars[args[0]] = iterator + step;
					pc = top + code_sect;
					अगर ((pc < code_sect) ||
					    (pc >= debug_sect))
						status = -दुस्फल;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल OP_PSTR:
			/*
			 * PRINT add string
			 * ...argument 0 is string ID
			 */
			count = म_माप(msg_buff);
			strlcpy(&msg_buff[count],
				&p[str_table + args[0]],
				ALTERA_MESSAGE_LENGTH - count);
			अवरोध;
		हाल OP_SINT:
			/*
			 * STATE पूर्णांकermediate state
			 * ...argument 0 is state code
			 */
			status = altera_जाओ_jstate(astate, args[0]);
			अवरोध;
		हाल OP_ST:
			/*
			 * STATE final state
			 * ...argument 0 is state code
			 */
			status = altera_जाओ_jstate(astate, args[0]);
			अवरोध;
		हाल OP_ISTP:
			/*
			 * IRSTOP state
			 * ...argument 0 is state code
			 */
			status = altera_set_irstop(&astate->js, args[0]);
			अवरोध;
		हाल OP_DSTP:
			/*
			 * DRSTOP state
			 * ...argument 0 is state code
			 */
			status = altera_set_drstop(&astate->js, args[0]);
			अवरोध;

		हाल OP_SWPN:
			/*
			 * Exchange top with Nth stack value
			 * ...argument 0 is 0-based stack entry
			 * to swap with top element
			 */
			index = (args[0]) + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				दीर्घ_पंचांगp = stack[stack_ptr - index];
				stack[stack_ptr - index] = stack[stack_ptr - 1];
				stack[stack_ptr - 1] = दीर्घ_पंचांगp;
			पूर्ण
			अवरोध;
		हाल OP_DUPN:
			/*
			 * Duplicate Nth stack value
			 * ...argument 0 is 0-based stack entry to duplicate
			 */
			index = (args[0]) + 1;
			अगर (altera_check_stack(stack_ptr, index, &status)) अणु
				stack[stack_ptr] = stack[stack_ptr - index];
				++stack_ptr;
			पूर्ण
			अवरोध;
		हाल OP_POPV:
			/*
			 * Pop stack पूर्णांकo scalar variable
			 * ...argument 0 is variable ID
			 * ...stack 0 is value
			 */
			अगर (altera_check_stack(stack_ptr, 1, &status))
				vars[args[0]] = stack[--stack_ptr];

			अवरोध;
		हाल OP_POPE:
			/*
			 * Pop stack पूर्णांकo पूर्णांकeger array element
			 * ...argument 0 is variable ID
			 * ...stack 0 is array index
			 * ...stack 1 is value
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			variable_id = args[0];

			/*
			 * If variable is पढ़ो-only,
			 * convert to writable array
			 */
			अगर ((version > 0) &&
				((attrs[variable_id] & 0x9c) == 0x1c)) अणु
				/* Allocate a writable buffer क्रम this array */
				count = var_size[variable_id];
				दीर्घ_पंचांगp = vars[variable_id];
				दीर्घptr_पंचांगp = kसुस्मृति(count, माप(दीर्घ),
								GFP_KERNEL);
				vars[variable_id] = (दीर्घ)दीर्घptr_पंचांगp;

				अगर (vars[variable_id] == 0) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				/* copy previous contents पूर्णांकo buffer */
				क्रम (i = 0; i < count; ++i) अणु
					दीर्घptr_पंचांगp[i] =
						get_unaligned_be32(&p[दीर्घ_पंचांगp]);
					दीर्घ_पंचांगp += माप(दीर्घ);
				पूर्ण

				/*
				 * set bit 7 - buffer was
				 * dynamically allocated
				 */
				attrs[variable_id] |= 0x80;

				/* clear bit 2 - variable is writable */
				attrs[variable_id] &= ~0x04;
				attrs[variable_id] |= 0x01;

			पूर्ण

			/* check that variable is a writable पूर्णांकeger array */
			अगर ((attrs[variable_id] & 0x1c) != 0x18)
				status = -दुस्फल;
			अन्यथा अणु
				दीर्घptr_पंचांगp = (दीर्घ *)vars[variable_id];

				/* pop the array index */
				index = stack[--stack_ptr];

				/* pop the value and store it पूर्णांकo the array */
				दीर्घptr_पंचांगp[index] = stack[--stack_ptr];
			पूर्ण

			अवरोध;
		हाल OP_POPA:
			/*
			 * Pop stack पूर्णांकo Boolean array
			 * ...argument 0 is variable ID
			 * ...stack 0 is count
			 * ...stack 1 is array index
			 * ...stack 2 is value
			 */
			अगर (!altera_check_stack(stack_ptr, 3, &status))
				अवरोध;
			variable_id = args[0];

			/*
			 * If variable is पढ़ो-only,
			 * convert to writable array
			 */
			अगर ((version > 0) &&
				((attrs[variable_id] & 0x9c) == 0x0c)) अणु
				/* Allocate a writable buffer क्रम this array */
				दीर्घ_पंचांगp =
					(var_size[variable_id] + 7L) >> 3L;
				अक्षरptr_पंचांगp2 = (u8 *)vars[variable_id];
				अक्षरptr_पंचांगp =
					kzalloc(दीर्घ_पंचांगp, GFP_KERNEL);
				vars[variable_id] = (दीर्घ)अक्षरptr_पंचांगp;

				अगर (vars[variable_id] == 0) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				/* zero the buffer */
				क्रम (दीर्घ_idx = 0L;
					दीर्घ_idx < दीर्घ_पंचांगp;
					++दीर्घ_idx) अणु
					अक्षरptr_पंचांगp[दीर्घ_idx] = 0;
				पूर्ण

				/* copy previous contents पूर्णांकo buffer */
				क्रम (दीर्घ_idx = 0L;
					दीर्घ_idx < var_size[variable_id];
					++दीर्घ_idx) अणु
					दीर्घ_idx2 = दीर्घ_idx;

					अगर (अक्षरptr_पंचांगp2[दीर्घ_idx2 >> 3] &
						(1 << (दीर्घ_idx2 & 7))) अणु
						अक्षरptr_पंचांगp[दीर्घ_idx >> 3] |=
							(1 << (दीर्घ_idx & 7));
					पूर्ण
				पूर्ण

				/*
				 * set bit 7 - buffer was
				 * dynamically allocated
				 */
				attrs[variable_id] |= 0x80;

				/* clear bit 2 - variable is writable */
				attrs[variable_id] &= ~0x04;
				attrs[variable_id] |= 0x01;

			पूर्ण

			/*
			 * check that variable is
			 * a writable Boolean array
			 */
			अगर ((attrs[variable_id] & 0x1c) != 0x08) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			अक्षरptr_पंचांगp = (u8 *)vars[variable_id];

			/* pop the count (number of bits to copy) */
			दीर्घ_count = stack[--stack_ptr];

			/* pop the array index */
			दीर्घ_idx = stack[--stack_ptr];

			reverse = 0;

			अगर (version > 0) अणु
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 */

				अगर (दीर्घ_idx > दीर्घ_count) अणु
					reverse = 1;
					दीर्घ_पंचांगp = दीर्घ_count;
					दीर्घ_count = 1 + दीर्घ_idx -
								दीर्घ_count;
					दीर्घ_idx = दीर्घ_पंचांगp;

					/* reverse POPA is not supported */
					status = -दुस्फल;
					अवरोध;
				पूर्ण अन्यथा
					दीर्घ_count = 1 + दीर्घ_count -
								दीर्घ_idx;

			पूर्ण

			/* pop the data */
			दीर्घ_पंचांगp = stack[--stack_ptr];

			अगर (दीर्घ_count < 1) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			क्रम (i = 0; i < दीर्घ_count; ++i) अणु
				अगर (दीर्घ_पंचांगp & (1L << (s32) i))
					अक्षरptr_पंचांगp[दीर्घ_idx >> 3L] |=
						(1L << (दीर्घ_idx & 7L));
				अन्यथा
					अक्षरptr_पंचांगp[दीर्घ_idx >> 3L] &=
						~(1L << (दीर्घ_idx & 7L));

				++दीर्घ_idx;
			पूर्ण

			अवरोध;
		हाल OP_JMPZ:
			/*
			 * Pop stack and branch अगर zero
			 * ...argument 0 is address
			 * ...stack 0 is condition value
			 */
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				अगर (stack[--stack_ptr] == 0) अणु
					pc = args[0] + code_sect;
					अगर ((pc < code_sect) ||
					    (pc >= debug_sect))
						status = -दुस्फल;
				पूर्ण
			पूर्ण
			अवरोध;
		हाल OP_DS:
		हाल OP_IS:
			/*
			 * DRSCAN
			 * IRSCAN
			 * ...argument 0 is scan data variable ID
			 * ...stack 0 is array index
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			दीर्घ_idx = stack[--stack_ptr];
			दीर्घ_count = stack[--stack_ptr];
			reverse = 0;
			अगर (version > 0) अणु
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 * stack 2 = count
				 */
				दीर्घ_पंचांगp = दीर्घ_count;
				दीर्घ_count = stack[--stack_ptr];

				अगर (दीर्घ_idx > दीर्घ_पंचांगp) अणु
					reverse = 1;
					दीर्घ_idx = दीर्घ_पंचांगp;
				पूर्ण
			पूर्ण

			अक्षरptr_पंचांगp = (u8 *)vars[args[0]];

			अगर (reverse) अणु
				/*
				 * allocate a buffer
				 * and reverse the data order
				 */
				अक्षरptr_पंचांगp2 = अक्षरptr_पंचांगp;
				अक्षरptr_पंचांगp = kzalloc((दीर्घ_count >> 3) + 1,
								GFP_KERNEL);
				अगर (अक्षरptr_पंचांगp == शून्य) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				दीर्घ_पंचांगp = दीर्घ_idx + दीर्घ_count - 1;
				दीर्घ_idx2 = 0;
				जबतक (दीर्घ_idx2 < दीर्घ_count) अणु
					अगर (अक्षरptr_पंचांगp2[दीर्घ_पंचांगp >> 3] &
							(1 << (दीर्घ_पंचांगp & 7)))
						अक्षरptr_पंचांगp[दीर्घ_idx2 >> 3] |=
							(1 << (दीर्घ_idx2 & 7));
					अन्यथा
						अक्षरptr_पंचांगp[दीर्घ_idx2 >> 3] &=
							~(1 << (दीर्घ_idx2 & 7));

					--दीर्घ_पंचांगp;
					++दीर्घ_idx2;
				पूर्ण
			पूर्ण

			अगर (opcode == 0x51) /* DS */
				status = altera_drscan(astate, दीर्घ_count,
						अक्षरptr_पंचांगp, दीर्घ_idx);
			अन्यथा /* IS */
				status = altera_irscan(astate, दीर्घ_count,
						अक्षरptr_पंचांगp, दीर्घ_idx);

			अगर (reverse)
				kमुक्त(अक्षरptr_पंचांगp);

			अवरोध;
		हाल OP_DPRA:
			/*
			 * DRPRE with array data
			 * ...argument 0 is variable ID
			 * ...stack 0 is array index
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			index = stack[--stack_ptr];
			count = stack[--stack_ptr];

			अगर (version > 0)
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 */
				count = 1 + count - index;

			अक्षरptr_पंचांगp = (u8 *)vars[args[0]];
			status = altera_set_dr_pre(&astate->js, count, index,
							अक्षरptr_पंचांगp);
			अवरोध;
		हाल OP_DPOA:
			/*
			 * DRPOST with array data
			 * ...argument 0 is variable ID
			 * ...stack 0 is array index
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			index = stack[--stack_ptr];
			count = stack[--stack_ptr];

			अगर (version > 0)
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 */
				count = 1 + count - index;

			अक्षरptr_पंचांगp = (u8 *)vars[args[0]];
			status = altera_set_dr_post(&astate->js, count, index,
							अक्षरptr_पंचांगp);
			अवरोध;
		हाल OP_IPRA:
			/*
			 * IRPRE with array data
			 * ...argument 0 is variable ID
			 * ...stack 0 is array index
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			index = stack[--stack_ptr];
			count = stack[--stack_ptr];

			अगर (version > 0)
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 */
				count = 1 + count - index;

			अक्षरptr_पंचांगp = (u8 *)vars[args[0]];
			status = altera_set_ir_pre(&astate->js, count, index,
							अक्षरptr_पंचांगp);

			अवरोध;
		हाल OP_IPOA:
			/*
			 * IRPOST with array data
			 * ...argument 0 is variable ID
			 * ...stack 0 is array index
			 * ...stack 1 is count
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			index = stack[--stack_ptr];
			count = stack[--stack_ptr];

			अगर (version > 0)
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 */
				count = 1 + count - index;

			अक्षरptr_पंचांगp = (u8 *)vars[args[0]];
			status = altera_set_ir_post(&astate->js, count, index,
							अक्षरptr_पंचांगp);

			अवरोध;
		हाल OP_EXPT:
			/*
			 * EXPORT
			 * ...argument 0 is string ID
			 * ...stack 0 is पूर्णांकeger expression
			 */
			अगर (altera_check_stack(stack_ptr, 1, &status)) अणु
				name = &p[str_table + args[0]];
				दीर्घ_पंचांगp = stack[--stack_ptr];
				altera_export_पूर्णांक(name, दीर्घ_पंचांगp);
			पूर्ण
			अवरोध;
		हाल OP_PSHE:
			/*
			 * Push पूर्णांकeger array element
			 * ...argument 0 is variable ID
			 * ...stack 0 is array index
			 */
			अगर (!altera_check_stack(stack_ptr, 1, &status))
				अवरोध;
			variable_id = args[0];
			index = stack[stack_ptr - 1];

			/* check variable type */
			अगर ((attrs[variable_id] & 0x1f) == 0x19) अणु
				/* writable पूर्णांकeger array */
				दीर्घptr_पंचांगp = (दीर्घ *)vars[variable_id];
				stack[stack_ptr - 1] = दीर्घptr_पंचांगp[index];
			पूर्ण अन्यथा अगर ((attrs[variable_id] & 0x1f) == 0x1c) अणु
				/* पढ़ो-only पूर्णांकeger array */
				दीर्घ_पंचांगp = vars[variable_id] +
						(index * माप(दीर्घ));
				stack[stack_ptr - 1] =
					get_unaligned_be32(&p[दीर्घ_पंचांगp]);
			पूर्ण अन्यथा
				status = -दुस्फल;

			अवरोध;
		हाल OP_PSHA:
			/*
			 * Push Boolean array
			 * ...argument 0 is variable ID
			 * ...stack 0 is count
			 * ...stack 1 is array index
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			variable_id = args[0];

			/* check that variable is a Boolean array */
			अगर ((attrs[variable_id] & 0x18) != 0x08) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			अक्षरptr_पंचांगp = (u8 *)vars[variable_id];

			/* pop the count (number of bits to copy) */
			count = stack[--stack_ptr];

			/* pop the array index */
			index = stack[stack_ptr - 1];

			अगर (version > 0)
				/*
				 * stack 0 = array right index
				 * stack 1 = array left index
				 */
				count = 1 + count - index;

			अगर ((count < 1) || (count > 32)) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			दीर्घ_पंचांगp = 0L;

			क्रम (i = 0; i < count; ++i)
				अगर (अक्षरptr_पंचांगp[(i + index) >> 3] &
						(1 << ((i + index) & 7)))
					दीर्घ_पंचांगp |= (1L << i);

			stack[stack_ptr - 1] = दीर्घ_पंचांगp;

			अवरोध;
		हाल OP_DYNA:
			/*
			 * Dynamically change size of array
			 * ...argument 0 is variable ID
			 * ...stack 0 is new size
			 */
			अगर (!altera_check_stack(stack_ptr, 1, &status))
				अवरोध;
			variable_id = args[0];
			दीर्घ_पंचांगp = stack[--stack_ptr];

			अगर (दीर्घ_पंचांगp > var_size[variable_id]) अणु
				var_size[variable_id] = दीर्घ_पंचांगp;

				अगर (attrs[variable_id] & 0x10)
					/* allocate पूर्णांकeger array */
					दीर्घ_पंचांगp *= माप(दीर्घ);
				अन्यथा
					/* allocate Boolean array */
					दीर्घ_पंचांगp = (दीर्घ_पंचांगp + 7) >> 3;

				/*
				 * If the buffer was previously allocated,
				 * मुक्त it
				 */
				अगर (attrs[variable_id] & 0x80) अणु
					kमुक्त((व्योम *)vars[variable_id]);
					vars[variable_id] = 0;
				पूर्ण

				/*
				 * Allocate a new buffer
				 * of the requested size
				 */
				vars[variable_id] = (दीर्घ)
					kzalloc(दीर्घ_पंचांगp, GFP_KERNEL);

				अगर (vars[variable_id] == 0) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				/*
				 * Set the attribute bit to indicate that
				 * this buffer was dynamically allocated and
				 * should be मुक्तd later
				 */
				attrs[variable_id] |= 0x80;

				/* zero out memory */
				count = ((var_size[variable_id] + 7L) /
									8L);
				अक्षरptr_पंचांगp = (u8 *)(vars[variable_id]);
				क्रम (index = 0; index < count; ++index)
					अक्षरptr_पंचांगp[index] = 0;

			पूर्ण

			अवरोध;
		हाल OP_EXPV:
			/*
			 * Export Boolean array
			 * ...argument 0 is string ID
			 * ...stack 0 is variable ID
			 * ...stack 1 is array right index
			 * ...stack 2 is array left index
			 */
			अगर (!altera_check_stack(stack_ptr, 3, &status))
				अवरोध;
			अगर (version == 0) अणु
				/* EXPV is not supported in JBC 1.0 */
				bad_opcode = 1;
				अवरोध;
			पूर्ण
			name = &p[str_table + args[0]];
			variable_id = stack[--stack_ptr];
			दीर्घ_idx = stack[--stack_ptr];/* right indx */
			दीर्घ_idx2 = stack[--stack_ptr];/* left indx */

			अगर (दीर्घ_idx > दीर्घ_idx2) अणु
				/* reverse indices not supported */
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			दीर्घ_count = 1 + दीर्घ_idx2 - दीर्घ_idx;

			अक्षरptr_पंचांगp = (u8 *)vars[variable_id];
			अक्षरptr_पंचांगp2 = शून्य;

			अगर ((दीर्घ_idx & 7L) != 0) अणु
				s32 k = दीर्घ_idx;
				अक्षरptr_पंचांगp2 =
					kzalloc(((दीर्घ_count + 7L) / 8L),
							GFP_KERNEL);
				अगर (अक्षरptr_पंचांगp2 == शून्य) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				क्रम (i = 0; i < दीर्घ_count; ++i) अणु
					अगर (अक्षरptr_पंचांगp[k >> 3] &
							(1 << (k & 7)))
						अक्षरptr_पंचांगp2[i >> 3] |=
								(1 << (i & 7));
					अन्यथा
						अक्षरptr_पंचांगp2[i >> 3] &=
								~(1 << (i & 7));

					++k;
				पूर्ण
				अक्षरptr_पंचांगp = अक्षरptr_पंचांगp2;

			पूर्ण अन्यथा अगर (दीर्घ_idx != 0)
				अक्षरptr_पंचांगp = &अक्षरptr_पंचांगp[दीर्घ_idx >> 3];

			altera_export_bool_array(name, अक्षरptr_पंचांगp,
							दीर्घ_count);

			/* मुक्त allocated buffer */
			अगर ((दीर्घ_idx & 7L) != 0)
				kमुक्त(अक्षरptr_पंचांगp2);

			अवरोध;
		हाल OP_COPY: अणु
			/*
			 * Array copy
			 * ...argument 0 is dest ID
			 * ...argument 1 is source ID
			 * ...stack 0 is count
			 * ...stack 1 is dest index
			 * ...stack 2 is source index
			 */
			s32 copy_count;
			s32 copy_index;
			s32 copy_index2;
			s32 destleft;
			s32 src_count;
			s32 dest_count;
			पूर्णांक src_reverse = 0;
			पूर्णांक dest_reverse = 0;

			अगर (!altera_check_stack(stack_ptr, 3, &status))
				अवरोध;

			copy_count = stack[--stack_ptr];
			copy_index = stack[--stack_ptr];
			copy_index2 = stack[--stack_ptr];
			reverse = 0;

			अगर (version > 0) अणु
				/*
				 * stack 0 = source right index
				 * stack 1 = source left index
				 * stack 2 = destination right index
				 * stack 3 = destination left index
				 */
				destleft = stack[--stack_ptr];

				अगर (copy_count > copy_index) अणु
					src_reverse = 1;
					reverse = 1;
					src_count = 1 + copy_count - copy_index;
					/* copy_index = source start index */
				पूर्ण अन्यथा अणु
					src_count = 1 + copy_index - copy_count;
					/* source start index */
					copy_index = copy_count;
				पूर्ण

				अगर (copy_index2 > destleft) अणु
					dest_reverse = 1;
					reverse = !reverse;
					dest_count = 1 + copy_index2 - destleft;
					/* destination start index */
					copy_index2 = destleft;
				पूर्ण अन्यथा
					dest_count = 1 + destleft - copy_index2;

				copy_count = (src_count < dest_count) ?
							src_count : dest_count;

				अगर ((src_reverse || dest_reverse) &&
					(src_count != dest_count))
					/*
					 * If either the source or destination
					 * is reversed, we can't tolerate
					 * a length mismatch, because we
					 * "left justify" arrays when copying.
					 * This won't work correctly
					 * with reversed arrays.
					 */
					status = -दुस्फल;

			पूर्ण

			count = copy_count;
			index = copy_index;
			index2 = copy_index2;

			/*
			 * If destination is a पढ़ो-only array,
			 * allocate a buffer and convert it to a writable array
			 */
			variable_id = args[1];
			अगर ((version > 0) &&
				((attrs[variable_id] & 0x9c) == 0x0c)) अणु
				/* Allocate a writable buffer क्रम this array */
				दीर्घ_पंचांगp =
					(var_size[variable_id] + 7L) >> 3L;
				अक्षरptr_पंचांगp2 = (u8 *)vars[variable_id];
				अक्षरptr_पंचांगp =
					kzalloc(दीर्घ_पंचांगp, GFP_KERNEL);
				vars[variable_id] = (दीर्घ)अक्षरptr_पंचांगp;

				अगर (vars[variable_id] == 0) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				/* zero the buffer */
				क्रम (दीर्घ_idx = 0L; दीर्घ_idx < दीर्घ_पंचांगp;
								++दीर्घ_idx)
					अक्षरptr_पंचांगp[दीर्घ_idx] = 0;

				/* copy previous contents पूर्णांकo buffer */
				क्रम (दीर्घ_idx = 0L;
					दीर्घ_idx < var_size[variable_id];
								++दीर्घ_idx) अणु
					दीर्घ_idx2 = दीर्घ_idx;

					अगर (अक्षरptr_पंचांगp2[दीर्घ_idx2 >> 3] &
						(1 << (दीर्घ_idx2 & 7)))
						अक्षरptr_पंचांगp[दीर्घ_idx >> 3] |=
							(1 << (दीर्घ_idx & 7));

				पूर्ण

				/*
				set bit 7 - buffer was dynamically allocated */
				attrs[variable_id] |= 0x80;

				/* clear bit 2 - variable is writable */
				attrs[variable_id] &= ~0x04;
				attrs[variable_id] |= 0x01;
			पूर्ण

			अक्षरptr_पंचांगp = (u8 *)vars[args[1]];
			अक्षरptr_पंचांगp2 = (u8 *)vars[args[0]];

			/* check अगर destination is a writable Boolean array */
			अगर ((attrs[args[1]] & 0x1c) != 0x08) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			अगर (count < 1) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			अगर (reverse)
				index2 += (count - 1);

			क्रम (i = 0; i < count; ++i) अणु
				अगर (अक्षरptr_पंचांगp2[index >> 3] &
							(1 << (index & 7)))
					अक्षरptr_पंचांगp[index2 >> 3] |=
							(1 << (index2 & 7));
				अन्यथा
					अक्षरptr_पंचांगp[index2 >> 3] &=
						~(1 << (index2 & 7));

				++index;
				अगर (reverse)
					--index2;
				अन्यथा
					++index2;
			पूर्ण

			अवरोध;
		पूर्ण
		हाल OP_DSC:
		हाल OP_ISC: अणु
			/*
			 * DRSCAN with capture
			 * IRSCAN with capture
			 * ...argument 0 is scan data variable ID
			 * ...argument 1 is capture variable ID
			 * ...stack 0 is capture index
			 * ...stack 1 is scan data index
			 * ...stack 2 is count
			 */
			s32 scan_right, scan_left;
			s32 capture_count = 0;
			s32 scan_count = 0;
			s32 capture_index;
			s32 scan_index;

			अगर (!altera_check_stack(stack_ptr, 3, &status))
				अवरोध;

			capture_index = stack[--stack_ptr];
			scan_index = stack[--stack_ptr];

			अगर (version > 0) अणु
				/*
				 * stack 0 = capture right index
				 * stack 1 = capture left index
				 * stack 2 = scan right index
				 * stack 3 = scan left index
				 * stack 4 = count
				 */
				scan_right = stack[--stack_ptr];
				scan_left = stack[--stack_ptr];
				capture_count = 1 + scan_index - capture_index;
				scan_count = 1 + scan_left - scan_right;
				scan_index = scan_right;
			पूर्ण

			दीर्घ_count = stack[--stack_ptr];
			/*
			 * If capture array is पढ़ो-only, allocate a buffer
			 * and convert it to a writable array
			 */
			variable_id = args[1];
			अगर ((version > 0) &&
				((attrs[variable_id] & 0x9c) == 0x0c)) अणु
				/* Allocate a writable buffer क्रम this array */
				दीर्घ_पंचांगp =
					(var_size[variable_id] + 7L) >> 3L;
				अक्षरptr_पंचांगp2 = (u8 *)vars[variable_id];
				अक्षरptr_पंचांगp =
					kzalloc(दीर्घ_पंचांगp, GFP_KERNEL);
				vars[variable_id] = (दीर्घ)अक्षरptr_पंचांगp;

				अगर (vars[variable_id] == 0) अणु
					status = -ENOMEM;
					अवरोध;
				पूर्ण

				/* zero the buffer */
				क्रम (दीर्घ_idx = 0L; दीर्घ_idx < दीर्घ_पंचांगp;
								++दीर्घ_idx)
					अक्षरptr_पंचांगp[दीर्घ_idx] = 0;

				/* copy previous contents पूर्णांकo buffer */
				क्रम (दीर्घ_idx = 0L;
					दीर्घ_idx < var_size[variable_id];
								++दीर्घ_idx) अणु
					दीर्घ_idx2 = दीर्घ_idx;

					अगर (अक्षरptr_पंचांगp2[दीर्घ_idx2 >> 3] &
						(1 << (दीर्घ_idx2 & 7)))
						अक्षरptr_पंचांगp[दीर्घ_idx >> 3] |=
							(1 << (दीर्घ_idx & 7));

				पूर्ण

				/*
				 * set bit 7 - buffer was
				 * dynamically allocated
				 */
				attrs[variable_id] |= 0x80;

				/* clear bit 2 - variable is writable */
				attrs[variable_id] &= ~0x04;
				attrs[variable_id] |= 0x01;

			पूर्ण

			अक्षरptr_पंचांगp = (u8 *)vars[args[0]];
			अक्षरptr_पंचांगp2 = (u8 *)vars[args[1]];

			अगर ((version > 0) &&
					((दीर्घ_count > capture_count) ||
					(दीर्घ_count > scan_count))) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			/*
			 * check that capture array
			 * is a writable Boolean array
			 */
			अगर ((attrs[args[1]] & 0x1c) != 0x08) अणु
				status = -दुस्फल;
				अवरोध;
			पूर्ण

			अगर (status == 0) अणु
				अगर (opcode == 0x82) /* DSC */
					status = altera_swap_dr(astate,
							दीर्घ_count,
							अक्षरptr_पंचांगp,
							scan_index,
							अक्षरptr_पंचांगp2,
							capture_index);
				अन्यथा /* ISC */
					status = altera_swap_ir(astate,
							दीर्घ_count,
							अक्षरptr_पंचांगp,
							scan_index,
							अक्षरptr_पंचांगp2,
							capture_index);

			पूर्ण

			अवरोध;
		पूर्ण
		हाल OP_WAIT:
			/*
			 * WAIT
			 * ...argument 0 is रुको state
			 * ...argument 1 is end state
			 * ...stack 0 is cycles
			 * ...stack 1 is microseconds
			 */
			अगर (!altera_check_stack(stack_ptr, 2, &status))
				अवरोध;
			दीर्घ_पंचांगp = stack[--stack_ptr];

			अगर (दीर्घ_पंचांगp != 0L)
				status = altera_रुको_cycles(astate, दीर्घ_पंचांगp,
								args[0]);

			दीर्घ_पंचांगp = stack[--stack_ptr];

			अगर ((status == 0) && (दीर्घ_पंचांगp != 0L))
				status = altera_रुको_msecs(astate,
								दीर्घ_पंचांगp,
								args[0]);

			अगर ((status == 0) && (args[1] != args[0]))
				status = altera_जाओ_jstate(astate,
								args[1]);

			अगर (version > 0) अणु
				--stack_ptr; /* throw away MAX cycles */
				--stack_ptr; /* throw away MAX microseconds */
			पूर्ण
			अवरोध;
		हाल OP_CMPA: अणु
			/*
			 * Array compare
			 * ...argument 0 is source 1 ID
			 * ...argument 1 is source 2 ID
			 * ...argument 2 is mask ID
			 * ...stack 0 is source 1 index
			 * ...stack 1 is source 2 index
			 * ...stack 2 is mask index
			 * ...stack 3 is count
			 */
			s32 a, b;
			u8 *source1 = (u8 *)vars[args[0]];
			u8 *source2 = (u8 *)vars[args[1]];
			u8 *mask = (u8 *)vars[args[2]];
			u32 index1;
			u32 index2;
			u32 mask_index;

			अगर (!altera_check_stack(stack_ptr, 4, &status))
				अवरोध;

			index1 = stack[--stack_ptr];
			index2 = stack[--stack_ptr];
			mask_index = stack[--stack_ptr];
			दीर्घ_count = stack[--stack_ptr];

			अगर (version > 0) अणु
				/*
				 * stack 0 = source 1 right index
				 * stack 1 = source 1 left index
				 * stack 2 = source 2 right index
				 * stack 3 = source 2 left index
				 * stack 4 = mask right index
				 * stack 5 = mask left index
				 */
				s32 mask_right = stack[--stack_ptr];
				s32 mask_left = stack[--stack_ptr];
				/* source 1 count */
				a = 1 + index2 - index1;
				/* source 2 count */
				b = 1 + दीर्घ_count - mask_index;
				a = (a < b) ? a : b;
				/* mask count */
				b = 1 + mask_left - mask_right;
				a = (a < b) ? a : b;
				/* source 2 start index */
				index2 = mask_index;
				/* mask start index */
				mask_index = mask_right;
				दीर्घ_count = a;
			पूर्ण

			दीर्घ_पंचांगp = 1L;

			अगर (दीर्घ_count < 1)
				status = -दुस्फल;
			अन्यथा अणु
				count = दीर्घ_count;

				क्रम (i = 0; i < count; ++i) अणु
					अगर (mask[mask_index >> 3] &
						(1 << (mask_index & 7))) अणु
						a = source1[index1 >> 3] &
							(1 << (index1 & 7))
								? 1 : 0;
						b = source2[index2 >> 3] &
							(1 << (index2 & 7))
								? 1 : 0;

						अगर (a != b) /* failure */
							दीर्घ_पंचांगp = 0L;
					पूर्ण
					++index1;
					++index2;
					++mask_index;
				पूर्ण
			पूर्ण

			stack[stack_ptr++] = दीर्घ_पंचांगp;

			अवरोध;
		पूर्ण
		शेष:
			/* Unrecognized opcode -- ERROR! */
			bad_opcode = 1;
			अवरोध;
		पूर्ण

		अगर (bad_opcode)
			status = -ENOSYS;

		अगर ((stack_ptr < 0) || (stack_ptr >= ALTERA_STACK_SIZE))
			status = -EOVERFLOW;

		अगर (status != 0) अणु
			करोne = 1;
			*error_address = (s32)(opcode_address - code_sect);
		पूर्ण
	पूर्ण

	altera_मुक्त_buffers(astate);

	/* Free all dynamically allocated arrays */
	अगर ((attrs != शून्य) && (vars != शून्य))
		क्रम (i = 0; i < sym_count; ++i)
			अगर (attrs[i] & 0x80)
				kमुक्त((व्योम *)vars[i]);

	kमुक्त(vars);
	kमुक्त(var_size);
	kमुक्त(attrs);
	kमुक्त(proc_attributes);

	वापस status;
पूर्ण

अटल पूर्णांक altera_get_note(u8 *p, s32 program_size, s32 *offset,
			   अक्षर *key, अक्षर *value, पूर्णांक keylen, पूर्णांक vallen)
/*
 * Gets key and value of NOTE fields in the JBC file.
 * Can be called in two modes:  अगर offset poपूर्णांकer is शून्य,
 * then the function searches क्रम note fields which match
 * the key string provided.  If offset is not शून्य, then
 * the function finds the next note field of any key,
 * starting at the offset specअगरied by the offset poपूर्णांकer.
 * Returns 0 क्रम success, अन्यथा appropriate error code
 */
अणु
	पूर्णांक status = -ENODATA;
	u32 note_strings = 0L;
	u32 note_table = 0L;
	u32 note_count = 0L;
	u32 first_word = 0L;
	पूर्णांक version = 0;
	पूर्णांक delta = 0;
	अक्षर *key_ptr;
	अक्षर *value_ptr;
	पूर्णांक i;

	/* Read header inक्रमmation */
	अगर (program_size > 52L) अणु
		first_word    = get_unaligned_be32(&p[0]);
		version = (first_word & 1L);
		delta = version * 8;

		note_strings  = get_unaligned_be32(&p[8 + delta]);
		note_table    = get_unaligned_be32(&p[12 + delta]);
		note_count    = get_unaligned_be32(&p[44 + (2 * delta)]);
	पूर्ण

	अगर ((first_word != 0x4A414D00L) && (first_word != 0x4A414D01L))
		वापस -EIO;

	अगर (note_count <= 0L)
		वापस status;

	अगर (offset == शून्य) अणु
		/*
		 * We will search क्रम the first note with a specअगरic key,
		 * and वापस only the value
		 */
		क्रम (i = 0; (i < note_count) &&
						(status != 0); ++i) अणु
			key_ptr = &p[note_strings +
					get_unaligned_be32(
					&p[note_table + (8 * i)])];
			अगर (key && !strnहालcmp(key, key_ptr, म_माप(key_ptr))) अणु
				status = 0;

				value_ptr = &p[note_strings +
						get_unaligned_be32(
						&p[note_table + (8 * i) + 4])];

				अगर (value != शून्य)
					strlcpy(value, value_ptr, vallen);

			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * We will search क्रम the next note, regardless of the key,
		 * and वापस both the value and the key
		 */

		i = *offset;

		अगर ((i >= 0) && (i < note_count)) अणु
			status = 0;

			अगर (key != शून्य)
				strlcpy(key, &p[note_strings +
						get_unaligned_be32(
						&p[note_table + (8 * i)])],
					keylen);

			अगर (value != शून्य)
				strlcpy(value, &p[note_strings +
						get_unaligned_be32(
						&p[note_table + (8 * i) + 4])],
					vallen);

			*offset = i + 1;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक altera_check_crc(u8 *p, s32 program_size)
अणु
	पूर्णांक status = 0;
	u16 local_expected = 0,
	    local_actual = 0,
	    shअगरt_reg = 0xffff;
	पूर्णांक bit, feedback;
	u8 databyte;
	u32 i;
	u32 crc_section = 0L;
	u32 first_word = 0L;
	पूर्णांक version = 0;
	पूर्णांक delta = 0;

	अगर (program_size > 52L) अणु
		first_word  = get_unaligned_be32(&p[0]);
		version = (first_word & 1L);
		delta = version * 8;

		crc_section = get_unaligned_be32(&p[32 + delta]);
	पूर्ण

	अगर ((first_word != 0x4A414D00L) && (first_word != 0x4A414D01L))
		status = -EIO;

	अगर (crc_section >= program_size)
		status = -EIO;

	अगर (status == 0) अणु
		local_expected = (u16)get_unaligned_be16(&p[crc_section]);

		क्रम (i = 0; i < crc_section; ++i) अणु
			databyte = p[i];
			क्रम (bit = 0; bit < 8; bit++) अणु
				feedback = (databyte ^ shअगरt_reg) & 0x01;
				shअगरt_reg >>= 1;
				अगर (feedback)
					shअगरt_reg ^= 0x8408;

				databyte >>= 1;
			पूर्ण
		पूर्ण

		local_actual = (u16)~shअगरt_reg;

		अगर (local_expected != local_actual)
			status = -EILSEQ;

	पूर्ण

	अगर (debug || status) अणु
		चयन (status) अणु
		हाल 0:
			prपूर्णांकk(KERN_INFO "%s: CRC matched: %04x\n", __func__,
				local_actual);
			अवरोध;
		हाल -EILSEQ:
			prपूर्णांकk(KERN_ERR "%s: CRC mismatch: expected %04x, "
				"actual %04x\n", __func__, local_expected,
				local_actual);
			अवरोध;
		हाल -EIO:
			prपूर्णांकk(KERN_ERR "%s: error: format isn't "
				"recognized.\n", __func__);
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_ERR "%s: CRC function returned error "
				"code %d\n", __func__, status);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक altera_get_file_info(u8 *p,
					s32 program_size,
					पूर्णांक *क्रमmat_version,
					पूर्णांक *action_count,
					पूर्णांक *procedure_count)
अणु
	पूर्णांक status = -EIO;
	u32 first_word = 0;
	पूर्णांक version = 0;

	अगर (program_size <= 52L)
		वापस status;

	first_word = get_unaligned_be32(&p[0]);

	अगर ((first_word == 0x4A414D00L) || (first_word == 0x4A414D01L)) अणु
		status = 0;

		version = (first_word & 1L);
		*क्रमmat_version = version + 1;

		अगर (version > 0) अणु
			*action_count = get_unaligned_be32(&p[48]);
			*procedure_count = get_unaligned_be32(&p[52]);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक altera_get_act_info(u8 *p,
					s32 program_size,
					पूर्णांक index,
					अक्षर **name,
					अक्षर **description,
					काष्ठा altera_procinfo **proc_list)
अणु
	पूर्णांक status = -EIO;
	काष्ठा altera_procinfo *procptr = शून्य;
	काष्ठा altera_procinfo *पंचांगpptr = शून्य;
	u32 first_word = 0L;
	u32 action_table = 0L;
	u32 proc_table = 0L;
	u32 str_table = 0L;
	u32 note_strings = 0L;
	u32 action_count = 0L;
	u32 proc_count = 0L;
	u32 act_name_id = 0L;
	u32 act_desc_id = 0L;
	u32 act_proc_id = 0L;
	u32 act_proc_name = 0L;
	u8 act_proc_attribute = 0;

	अगर (program_size <= 52L)
		वापस status;
	/* Read header inक्रमmation */
	first_word = get_unaligned_be32(&p[0]);

	अगर (first_word != 0x4A414D01L)
		वापस status;

	action_table = get_unaligned_be32(&p[4]);
	proc_table   = get_unaligned_be32(&p[8]);
	str_table = get_unaligned_be32(&p[12]);
	note_strings = get_unaligned_be32(&p[16]);
	action_count = get_unaligned_be32(&p[48]);
	proc_count   = get_unaligned_be32(&p[52]);

	अगर (index >= action_count)
		वापस status;

	act_name_id = get_unaligned_be32(&p[action_table + (12 * index)]);
	act_desc_id = get_unaligned_be32(&p[action_table + (12 * index) + 4]);
	act_proc_id = get_unaligned_be32(&p[action_table + (12 * index) + 8]);

	*name = &p[str_table + act_name_id];

	अगर (act_desc_id < (note_strings - str_table))
		*description = &p[str_table + act_desc_id];

	करो अणु
		act_proc_name = get_unaligned_be32(
					&p[proc_table + (13 * act_proc_id)]);
		act_proc_attribute =
			(p[proc_table + (13 * act_proc_id) + 8] & 0x03);

		procptr =
				kzalloc(माप(काष्ठा altera_procinfo),
								GFP_KERNEL);

		अगर (procptr == शून्य)
			status = -ENOMEM;
		अन्यथा अणु
			procptr->name = &p[str_table + act_proc_name];
			procptr->attrs = act_proc_attribute;
			procptr->next = शून्य;

			/* add record to end of linked list */
			अगर (*proc_list == शून्य)
				*proc_list = procptr;
			अन्यथा अणु
				पंचांगpptr = *proc_list;
				जबतक (पंचांगpptr->next != शून्य)
					पंचांगpptr = पंचांगpptr->next;
				पंचांगpptr->next = procptr;
			पूर्ण
		पूर्ण

		act_proc_id = get_unaligned_be32(
				&p[proc_table + (13 * act_proc_id) + 4]);
	पूर्ण जबतक ((act_proc_id != 0) && (act_proc_id < proc_count));

	वापस status;
पूर्ण

पूर्णांक altera_init(काष्ठा altera_config *config, स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा altera_state *astate = शून्य;
	काष्ठा altera_procinfo *proc_list = शून्य;
	काष्ठा altera_procinfo *procptr = शून्य;
	अक्षर *key = शून्य;
	अक्षर *value = शून्य;
	अक्षर *action_name = शून्य;
	अक्षर *description = शून्य;
	पूर्णांक exec_result = 0;
	पूर्णांक निकास_code = 0;
	पूर्णांक क्रमmat_version = 0;
	पूर्णांक action_count = 0;
	पूर्णांक procedure_count = 0;
	पूर्णांक index = 0;
	s32 offset = 0L;
	s32 error_address = 0L;
	पूर्णांक retval = 0;

	key = kzalloc(33, GFP_KERNEL);
	अगर (!key) अणु
		retval = -ENOMEM;
		जाओ out;
	पूर्ण
	value = kzalloc(257, GFP_KERNEL);
	अगर (!value) अणु
		retval = -ENOMEM;
		जाओ मुक्त_key;
	पूर्ण
	astate = kzalloc(माप(काष्ठा altera_state), GFP_KERNEL);
	अगर (!astate) अणु
		retval = -ENOMEM;
		जाओ मुक्त_value;
	पूर्ण

	astate->config = config;
	अगर (!astate->config->jtag_io) अणु
		dprपूर्णांकk("%s: using byteblaster!\n", __func__);
		astate->config->jtag_io = netup_jtag_io_lpt;
	पूर्ण

	altera_check_crc((u8 *)fw->data, fw->size);

	अगर (debug) अणु
		altera_get_file_info((u8 *)fw->data, fw->size, &क्रमmat_version,
					&action_count, &procedure_count);
		prपूर्णांकk(KERN_INFO "%s: File format is %s ByteCode format\n",
			__func__, (क्रमmat_version == 2) ? "Jam STAPL" :
						"pre-standardized Jam 1.1");
		जबतक (altera_get_note((u8 *)fw->data, fw->size,
					&offset, key, value, 32, 256) == 0)
			prपूर्णांकk(KERN_INFO "%s: NOTE \"%s\" = \"%s\"\n",
					__func__, key, value);
	पूर्ण

	अगर (debug && (क्रमmat_version == 2) && (action_count > 0)) अणु
		prपूर्णांकk(KERN_INFO "%s: Actions available:\n", __func__);
		क्रम (index = 0; index < action_count; ++index) अणु
			altera_get_act_info((u8 *)fw->data, fw->size,
						index, &action_name,
						&description,
						&proc_list);

			अगर (description == शून्य)
				prपूर्णांकk(KERN_INFO "%s: %s\n",
						__func__,
						action_name);
			अन्यथा
				prपूर्णांकk(KERN_INFO "%s: %s \"%s\"\n",
						__func__,
						action_name,
						description);

			procptr = proc_list;
			जबतक (procptr != शून्य) अणु
				अगर (procptr->attrs != 0)
					prपूर्णांकk(KERN_INFO "%s:    %s (%s)\n",
						__func__,
						procptr->name,
						(procptr->attrs == 1) ?
						"optional" : "recommended");

				proc_list = procptr->next;
				kमुक्त(procptr);
				procptr = proc_list;
			पूर्ण
		पूर्ण

		prपूर्णांकk(KERN_INFO "\n");
	पूर्ण

	exec_result = altera_execute(astate, (u8 *)fw->data, fw->size,
				&error_address, &निकास_code, &क्रमmat_version);

	अगर (निकास_code)
		exec_result = -EREMOTEIO;

	अगर ((क्रमmat_version == 2) && (exec_result == -EINVAL)) अणु
		अगर (astate->config->action == शून्य)
			prपूर्णांकk(KERN_ERR "%s: error: no action specified for "
				"Jam STAPL file.\nprogram terminated.\n",
				__func__);
		अन्यथा
			prपूर्णांकk(KERN_ERR "%s: error: action \"%s\""
				" is not supported "
				"for this Jam STAPL file.\n"
				"Program terminated.\n", __func__,
				astate->config->action);

	पूर्ण अन्यथा अगर (exec_result)
		prपूर्णांकk(KERN_ERR "%s: error %d\n", __func__, exec_result);

	kमुक्त(astate);
मुक्त_value:
	kमुक्त(value);
मुक्त_key:
	kमुक्त(key);
out:
	वापस retval;
पूर्ण
EXPORT_SYMBOL(altera_init);
