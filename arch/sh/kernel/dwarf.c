<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2009 Matt Fleming <matt@console-pimps.org>
 *
 * This is an implementation of a DWARF unwinder. Its मुख्य purpose is
 * क्रम generating stacktrace inक्रमmation. Based on the DWARF 3
 * specअगरication from http://www.dwarfstd.org.
 *
 * TODO:
 *	- DWARF64 करोesn't work.
 *	- Registers with DWARF_VAL_OFFSET rules aren't handled properly.
 */

/* #घोषणा DEBUG */
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/mempool.h>
#समावेश <linux/mm.h>
#समावेश <linux/elf.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/dwarf.h>
#समावेश <यंत्र/unwinder.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/stacktrace.h>

/* Reserve enough memory क्रम two stack frames */
#घोषणा DWARF_FRAME_MIN_REQ	2
/* ... with 4 रेजिस्टरs per frame. */
#घोषणा DWARF_REG_MIN_REQ	(DWARF_FRAME_MIN_REQ * 4)

अटल काष्ठा kmem_cache *dwarf_frame_cachep;
अटल mempool_t *dwarf_frame_pool;

अटल काष्ठा kmem_cache *dwarf_reg_cachep;
अटल mempool_t *dwarf_reg_pool;

अटल काष्ठा rb_root cie_root;
अटल DEFINE_SPINLOCK(dwarf_cie_lock);

अटल काष्ठा rb_root fde_root;
अटल DEFINE_SPINLOCK(dwarf_fde_lock);

अटल काष्ठा dwarf_cie *cached_cie;

अटल अचिन्हित पूर्णांक dwarf_unwinder_पढ़ोy;

/**
 *	dwarf_frame_alloc_reg - allocate memory क्रम a DWARF रेजिस्टर
 *	@frame: the DWARF frame whose list of रेजिस्टरs we insert on
 *	@reg_num: the रेजिस्टर number
 *
 *	Allocate space क्रम, and initialise, a dwarf reg from
 *	dwarf_reg_pool and insert it onto the (unsorted) linked-list of
 *	dwarf रेजिस्टरs क्रम @frame.
 *
 *	Return the initialised DWARF reg.
 */
अटल काष्ठा dwarf_reg *dwarf_frame_alloc_reg(काष्ठा dwarf_frame *frame,
					       अचिन्हित पूर्णांक reg_num)
अणु
	काष्ठा dwarf_reg *reg;

	reg = mempool_alloc(dwarf_reg_pool, GFP_ATOMIC);
	अगर (!reg) अणु
		prपूर्णांकk(KERN_WARNING "Unable to allocate a DWARF register\n");
		/*
		 * Let's just bomb hard here, we have no way to
		 * gracefully recover.
		 */
		UNWINDER_BUG();
	पूर्ण

	reg->number = reg_num;
	reg->addr = 0;
	reg->flags = 0;

	list_add(&reg->link, &frame->reg_list);

	वापस reg;
पूर्ण

अटल व्योम dwarf_frame_मुक्त_regs(काष्ठा dwarf_frame *frame)
अणु
	काष्ठा dwarf_reg *reg, *n;

	list_क्रम_each_entry_safe(reg, n, &frame->reg_list, link) अणु
		list_del(&reg->link);
		mempool_मुक्त(reg, dwarf_reg_pool);
	पूर्ण
पूर्ण

/**
 *	dwarf_frame_reg - वापस a DWARF रेजिस्टर
 *	@frame: the DWARF frame to search in क्रम @reg_num
 *	@reg_num: the रेजिस्टर number to search क्रम
 *
 *	Lookup and वापस the dwarf reg @reg_num क्रम this frame. Return
 *	शून्य अगर @reg_num is an रेजिस्टर invalid number.
 */
अटल काष्ठा dwarf_reg *dwarf_frame_reg(काष्ठा dwarf_frame *frame,
					 अचिन्हित पूर्णांक reg_num)
अणु
	काष्ठा dwarf_reg *reg;

	list_क्रम_each_entry(reg, &frame->reg_list, link) अणु
		अगर (reg->number == reg_num)
			वापस reg;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 *	dwarf_पढ़ो_addr - पढ़ो dwarf data
 *	@src: source address of data
 *	@dst: destination address to store the data to
 *
 *	Read 'n' bytes from @src, where 'n' is the size of an address on
 *	the native machine. We वापस the number of bytes पढ़ो, which
 *	should always be 'n'. We also have to be careful when पढ़ोing
 *	from @src and writing to @dst, because they can be arbitrarily
 *	aligned. Return 'n' - the number of bytes पढ़ो.
 */
अटल अंतरभूत पूर्णांक dwarf_पढ़ो_addr(अचिन्हित दीर्घ *src, अचिन्हित दीर्घ *dst)
अणु
	u32 val = get_unaligned(src);
	put_unaligned(val, dst);
	वापस माप(अचिन्हित दीर्घ *);
पूर्ण

/**
 *	dwarf_पढ़ो_uleb128 - पढ़ो अचिन्हित LEB128 data
 *	@addr: the address where the ULEB128 data is stored
 *	@ret: address to store the result
 *
 *	Decode an अचिन्हित LEB128 encoded datum. The algorithm is taken
 *	from Appendix C of the DWARF 3 spec. For inक्रमmation on the
 *	encodings refer to section "7.6 - Variable Length Data". Return
 *	the number of bytes पढ़ो.
 */
अटल अंतरभूत अचिन्हित दीर्घ dwarf_पढ़ो_uleb128(अक्षर *addr, अचिन्हित पूर्णांक *ret)
अणु
	अचिन्हित पूर्णांक result;
	अचिन्हित अक्षर byte;
	पूर्णांक shअगरt, count;

	result = 0;
	shअगरt = 0;
	count = 0;

	जबतक (1) अणु
		byte = __raw_पढ़ोb(addr);
		addr++;
		count++;

		result |= (byte & 0x7f) << shअगरt;
		shअगरt += 7;

		अगर (!(byte & 0x80))
			अवरोध;
	पूर्ण

	*ret = result;

	वापस count;
पूर्ण

/**
 *	dwarf_पढ़ो_leb128 - पढ़ो चिन्हित LEB128 data
 *	@addr: the address of the LEB128 encoded data
 *	@ret: address to store the result
 *
 *	Decode चिन्हित LEB128 data. The algorithm is taken from Appendix
 *	C of the DWARF 3 spec. Return the number of bytes पढ़ो.
 */
अटल अंतरभूत अचिन्हित दीर्घ dwarf_पढ़ो_leb128(अक्षर *addr, पूर्णांक *ret)
अणु
	अचिन्हित अक्षर byte;
	पूर्णांक result, shअगरt;
	पूर्णांक num_bits;
	पूर्णांक count;

	result = 0;
	shअगरt = 0;
	count = 0;

	जबतक (1) अणु
		byte = __raw_पढ़ोb(addr);
		addr++;
		result |= (byte & 0x7f) << shअगरt;
		shअगरt += 7;
		count++;

		अगर (!(byte & 0x80))
			अवरोध;
	पूर्ण

	/* The number of bits in a चिन्हित पूर्णांकeger. */
	num_bits = 8 * माप(result);

	अगर ((shअगरt < num_bits) && (byte & 0x40))
		result |= (-1 << shअगरt);

	*ret = result;

	वापस count;
पूर्ण

/**
 *	dwarf_पढ़ो_encoded_value - वापस the decoded value at @addr
 *	@addr: the address of the encoded value
 *	@val: where to ग_लिखो the decoded value
 *	@encoding: the encoding with which we can decode @addr
 *
 *	GCC emits encoded address in the .eh_frame FDE entries. Decode
 *	the value at @addr using @encoding. The decoded value is written
 *	to @val and the number of bytes पढ़ो is वापसed.
 */
अटल पूर्णांक dwarf_पढ़ो_encoded_value(अक्षर *addr, अचिन्हित दीर्घ *val,
				    अक्षर encoding)
अणु
	अचिन्हित दीर्घ decoded_addr = 0;
	पूर्णांक count = 0;

	चयन (encoding & 0x70) अणु
	हाल DW_EH_PE_असलptr:
		अवरोध;
	हाल DW_EH_PE_pcrel:
		decoded_addr = (अचिन्हित दीर्घ)addr;
		अवरोध;
	शेष:
		pr_debug("encoding=0x%x\n", (encoding & 0x70));
		UNWINDER_BUG();
	पूर्ण

	अगर ((encoding & 0x07) == 0x00)
		encoding |= DW_EH_PE_udata4;

	चयन (encoding & 0x0f) अणु
	हाल DW_EH_PE_sdata4:
	हाल DW_EH_PE_udata4:
		count += 4;
		decoded_addr += get_unaligned((u32 *)addr);
		__raw_ग_लिखोl(decoded_addr, val);
		अवरोध;
	शेष:
		pr_debug("encoding=0x%x\n", encoding);
		UNWINDER_BUG();
	पूर्ण

	वापस count;
पूर्ण

/**
 *	dwarf_entry_len - वापस the length of an FDE or CIE
 *	@addr: the address of the entry
 *	@len: the length of the entry
 *
 *	Read the initial_length field of the entry and store the size of
 *	the entry in @len. We वापस the number of bytes पढ़ो. Return a
 *	count of 0 on error.
 */
अटल अंतरभूत पूर्णांक dwarf_entry_len(अक्षर *addr, अचिन्हित दीर्घ *len)
अणु
	u32 initial_len;
	पूर्णांक count;

	initial_len = get_unaligned((u32 *)addr);
	count = 4;

	/*
	 * An initial length field value in the range DW_LEN_EXT_LO -
	 * DW_LEN_EXT_HI indicates an extension, and should not be
	 * पूर्णांकerpreted as a length. The only extension that we currently
	 * understand is the use of DWARF64 addresses.
	 */
	अगर (initial_len >= DW_EXT_LO && initial_len <= DW_EXT_HI) अणु
		/*
		 * The 64-bit length field immediately follows the
		 * compulsory 32-bit length field.
		 */
		अगर (initial_len == DW_EXT_DWARF64) अणु
			*len = get_unaligned((u64 *)addr + 4);
			count = 12;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_WARNING "Unknown DWARF extension\n");
			count = 0;
		पूर्ण
	पूर्ण अन्यथा
		*len = initial_len;

	वापस count;
पूर्ण

/**
 *	dwarf_lookup_cie - locate the cie
 *	@cie_ptr: poपूर्णांकer to help with lookup
 */
अटल काष्ठा dwarf_cie *dwarf_lookup_cie(अचिन्हित दीर्घ cie_ptr)
अणु
	काष्ठा rb_node **rb_node = &cie_root.rb_node;
	काष्ठा dwarf_cie *cie = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dwarf_cie_lock, flags);

	/*
	 * We've cached the last CIE we looked up because chances are
	 * that the FDE wants this CIE.
	 */
	अगर (cached_cie && cached_cie->cie_poपूर्णांकer == cie_ptr) अणु
		cie = cached_cie;
		जाओ out;
	पूर्ण

	जबतक (*rb_node) अणु
		काष्ठा dwarf_cie *cie_पंचांगp;

		cie_पंचांगp = rb_entry(*rb_node, काष्ठा dwarf_cie, node);
		BUG_ON(!cie_पंचांगp);

		अगर (cie_ptr == cie_पंचांगp->cie_poपूर्णांकer) अणु
			cie = cie_पंचांगp;
			cached_cie = cie_पंचांगp;
			जाओ out;
		पूर्ण अन्यथा अणु
			अगर (cie_ptr < cie_पंचांगp->cie_poपूर्णांकer)
				rb_node = &(*rb_node)->rb_left;
			अन्यथा
				rb_node = &(*rb_node)->rb_right;
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&dwarf_cie_lock, flags);
	वापस cie;
पूर्ण

/**
 *	dwarf_lookup_fde - locate the FDE that covers pc
 *	@pc: the program counter
 */
काष्ठा dwarf_fde *dwarf_lookup_fde(अचिन्हित दीर्घ pc)
अणु
	काष्ठा rb_node **rb_node = &fde_root.rb_node;
	काष्ठा dwarf_fde *fde = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dwarf_fde_lock, flags);

	जबतक (*rb_node) अणु
		काष्ठा dwarf_fde *fde_पंचांगp;
		अचिन्हित दीर्घ पंचांगp_start, पंचांगp_end;

		fde_पंचांगp = rb_entry(*rb_node, काष्ठा dwarf_fde, node);
		BUG_ON(!fde_पंचांगp);

		पंचांगp_start = fde_पंचांगp->initial_location;
		पंचांगp_end = fde_पंचांगp->initial_location + fde_पंचांगp->address_range;

		अगर (pc < पंचांगp_start) अणु
			rb_node = &(*rb_node)->rb_left;
		पूर्ण अन्यथा अणु
			अगर (pc < पंचांगp_end) अणु
				fde = fde_पंचांगp;
				जाओ out;
			पूर्ण अन्यथा
				rb_node = &(*rb_node)->rb_right;
		पूर्ण
	पूर्ण

out:
	spin_unlock_irqrestore(&dwarf_fde_lock, flags);

	वापस fde;
पूर्ण

/**
 *	dwarf_cfa_execute_insns - execute inकाष्ठाions to calculate a CFA
 *	@insn_start: address of the first inकाष्ठाion
 *	@insn_end: address of the last inकाष्ठाion
 *	@cie: the CIE क्रम this function
 *	@fde: the FDE क्रम this function
 *	@frame: the inकाष्ठाions calculate the CFA क्रम this frame
 *	@pc: the program counter of the address we're पूर्णांकerested in
 *
 *	Execute the Call Frame inकाष्ठाion sequence starting at
 *	@insn_start and ending at @insn_end. The inकाष्ठाions describe
 *	how to calculate the Canonical Frame Address of a stackframe.
 *	Store the results in @frame.
 */
अटल पूर्णांक dwarf_cfa_execute_insns(अचिन्हित अक्षर *insn_start,
				   अचिन्हित अक्षर *insn_end,
				   काष्ठा dwarf_cie *cie,
				   काष्ठा dwarf_fde *fde,
				   काष्ठा dwarf_frame *frame,
				   अचिन्हित दीर्घ pc)
अणु
	अचिन्हित अक्षर insn;
	अचिन्हित अक्षर *current_insn;
	अचिन्हित पूर्णांक count, delta, reg, expr_len, offset;
	काष्ठा dwarf_reg *regp;

	current_insn = insn_start;

	जबतक (current_insn < insn_end && frame->pc <= pc) अणु
		insn = __raw_पढ़ोb(current_insn++);

		/*
		 * Firstly, handle the opcodes that embed their opeअक्रमs
		 * in the inकाष्ठाions.
		 */
		चयन (DW_CFA_opcode(insn)) अणु
		हाल DW_CFA_advance_loc:
			delta = DW_CFA_opeअक्रम(insn);
			delta *= cie->code_alignment_factor;
			frame->pc += delta;
			जारी;
			/* NOTREACHED */
		हाल DW_CFA_offset:
			reg = DW_CFA_opeअक्रम(insn);
			count = dwarf_पढ़ो_uleb128(current_insn, &offset);
			current_insn += count;
			offset *= cie->data_alignment_factor;
			regp = dwarf_frame_alloc_reg(frame, reg);
			regp->addr = offset;
			regp->flags |= DWARF_REG_OFFSET;
			जारी;
			/* NOTREACHED */
		हाल DW_CFA_restore:
			reg = DW_CFA_opeअक्रम(insn);
			जारी;
			/* NOTREACHED */
		पूर्ण

		/*
		 * Secondly, handle the opcodes that करोn't embed their
		 * opeअक्रमs in the inकाष्ठाion.
		 */
		चयन (insn) अणु
		हाल DW_CFA_nop:
			जारी;
		हाल DW_CFA_advance_loc1:
			delta = *current_insn++;
			frame->pc += delta * cie->code_alignment_factor;
			अवरोध;
		हाल DW_CFA_advance_loc2:
			delta = get_unaligned((u16 *)current_insn);
			current_insn += 2;
			frame->pc += delta * cie->code_alignment_factor;
			अवरोध;
		हाल DW_CFA_advance_loc4:
			delta = get_unaligned((u32 *)current_insn);
			current_insn += 4;
			frame->pc += delta * cie->code_alignment_factor;
			अवरोध;
		हाल DW_CFA_offset_extended:
			count = dwarf_पढ़ो_uleb128(current_insn, &reg);
			current_insn += count;
			count = dwarf_पढ़ो_uleb128(current_insn, &offset);
			current_insn += count;
			offset *= cie->data_alignment_factor;
			अवरोध;
		हाल DW_CFA_restore_extended:
			count = dwarf_पढ़ो_uleb128(current_insn, &reg);
			current_insn += count;
			अवरोध;
		हाल DW_CFA_undefined:
			count = dwarf_पढ़ो_uleb128(current_insn, &reg);
			current_insn += count;
			regp = dwarf_frame_alloc_reg(frame, reg);
			regp->flags |= DWARF_UNDEFINED;
			अवरोध;
		हाल DW_CFA_def_cfa:
			count = dwarf_पढ़ो_uleb128(current_insn,
						   &frame->cfa_रेजिस्टर);
			current_insn += count;
			count = dwarf_पढ़ो_uleb128(current_insn,
						   &frame->cfa_offset);
			current_insn += count;

			frame->flags |= DWARF_FRAME_CFA_REG_OFFSET;
			अवरोध;
		हाल DW_CFA_def_cfa_रेजिस्टर:
			count = dwarf_पढ़ो_uleb128(current_insn,
						   &frame->cfa_रेजिस्टर);
			current_insn += count;
			frame->flags |= DWARF_FRAME_CFA_REG_OFFSET;
			अवरोध;
		हाल DW_CFA_def_cfa_offset:
			count = dwarf_पढ़ो_uleb128(current_insn, &offset);
			current_insn += count;
			frame->cfa_offset = offset;
			अवरोध;
		हाल DW_CFA_def_cfa_expression:
			count = dwarf_पढ़ो_uleb128(current_insn, &expr_len);
			current_insn += count;

			frame->cfa_expr = current_insn;
			frame->cfa_expr_len = expr_len;
			current_insn += expr_len;

			frame->flags |= DWARF_FRAME_CFA_REG_EXP;
			अवरोध;
		हाल DW_CFA_offset_extended_sf:
			count = dwarf_पढ़ो_uleb128(current_insn, &reg);
			current_insn += count;
			count = dwarf_पढ़ो_leb128(current_insn, &offset);
			current_insn += count;
			offset *= cie->data_alignment_factor;
			regp = dwarf_frame_alloc_reg(frame, reg);
			regp->flags |= DWARF_REG_OFFSET;
			regp->addr = offset;
			अवरोध;
		हाल DW_CFA_val_offset:
			count = dwarf_पढ़ो_uleb128(current_insn, &reg);
			current_insn += count;
			count = dwarf_पढ़ो_leb128(current_insn, &offset);
			offset *= cie->data_alignment_factor;
			regp = dwarf_frame_alloc_reg(frame, reg);
			regp->flags |= DWARF_VAL_OFFSET;
			regp->addr = offset;
			अवरोध;
		हाल DW_CFA_GNU_args_size:
			count = dwarf_पढ़ो_uleb128(current_insn, &offset);
			current_insn += count;
			अवरोध;
		हाल DW_CFA_GNU_negative_offset_extended:
			count = dwarf_पढ़ो_uleb128(current_insn, &reg);
			current_insn += count;
			count = dwarf_पढ़ो_uleb128(current_insn, &offset);
			offset *= cie->data_alignment_factor;

			regp = dwarf_frame_alloc_reg(frame, reg);
			regp->flags |= DWARF_REG_OFFSET;
			regp->addr = -offset;
			अवरोध;
		शेष:
			pr_debug("unhandled DWARF instruction 0x%x\n", insn);
			UNWINDER_BUG();
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	dwarf_मुक्त_frame - मुक्त the memory allocated क्रम @frame
 *	@frame: the frame to मुक्त
 */
व्योम dwarf_मुक्त_frame(काष्ठा dwarf_frame *frame)
अणु
	dwarf_frame_मुक्त_regs(frame);
	mempool_मुक्त(frame, dwarf_frame_pool);
पूर्ण

बाह्य व्योम ret_from_irq(व्योम);

/**
 *	dwarf_unwind_stack - unwind the stack
 *
 *	@pc: address of the function to unwind
 *	@prev: काष्ठा dwarf_frame of the previous stackframe on the callstack
 *
 *	Return a काष्ठा dwarf_frame representing the most recent frame
 *	on the callstack. Each of the lower (older) stack frames are
 *	linked via the "prev" member.
 */
काष्ठा dwarf_frame *dwarf_unwind_stack(अचिन्हित दीर्घ pc,
				       काष्ठा dwarf_frame *prev)
अणु
	काष्ठा dwarf_frame *frame;
	काष्ठा dwarf_cie *cie;
	काष्ठा dwarf_fde *fde;
	काष्ठा dwarf_reg *reg;
	अचिन्हित दीर्घ addr;

	/*
	 * If we've been called in to beक्रमe initialization has
	 * completed, bail out immediately.
	 */
	अगर (!dwarf_unwinder_पढ़ोy)
		वापस शून्य;

	/*
	 * If we're starting at the top of the stack we need get the
	 * contents of a physical रेजिस्टर to get the CFA in order to
	 * begin the भव unwinding of the stack.
	 *
	 * NOTE: the वापस address is guaranteed to be setup by the
	 * समय this function makes its first function call.
	 */
	अगर (!pc || !prev)
		pc = _THIS_IP_;

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	/*
	 * If our stack has been patched by the function graph tracer
	 * then we might see the address of वापस_to_handler() where we
	 * expected to find the real वापस address.
	 */
	अगर (pc == (अचिन्हित दीर्घ)&वापस_to_handler) अणु
		काष्ठा ftrace_ret_stack *ret_stack;

		ret_stack = ftrace_graph_get_ret_stack(current, 0);
		अगर (ret_stack)
			pc = ret_stack->ret;
		/*
		 * We currently have no way of tracking how many
		 * वापस_to_handler()'s we've seen. If there is more
		 * than one patched वापस address on our stack,
		 * complain loudly.
		 */
		WARN_ON(ftrace_graph_get_ret_stack(current, 1));
	पूर्ण
#पूर्ण_अगर

	frame = mempool_alloc(dwarf_frame_pool, GFP_ATOMIC);
	अगर (!frame) अणु
		prपूर्णांकk(KERN_ERR "Unable to allocate a dwarf frame\n");
		UNWINDER_BUG();
	पूर्ण

	INIT_LIST_HEAD(&frame->reg_list);
	frame->flags = 0;
	frame->prev = prev;
	frame->वापस_addr = 0;

	fde = dwarf_lookup_fde(pc);
	अगर (!fde) अणु
		/*
		 * This is our normal निकास path. There are two reasons
		 * why we might निकास here,
		 *
		 *	a) pc has no asscociated DWARF frame info and so
		 *	we करोn't know how to unwind this frame. This is
		 *	usually the हाल when we're trying to unwind a
		 *	frame that was called from some assembly code
		 *	that has no DWARF info, e.g. syscalls.
		 *
		 *	b) the DEBUG info क्रम pc is bogus. There's
		 *	really no way to distinguish this हाल from the
		 *	हाल above, which sucks because we could prपूर्णांक a
		 *	warning here.
		 */
		जाओ bail;
	पूर्ण

	cie = dwarf_lookup_cie(fde->cie_poपूर्णांकer);

	frame->pc = fde->initial_location;

	/* CIE initial inकाष्ठाions */
	dwarf_cfa_execute_insns(cie->initial_inकाष्ठाions,
				cie->inकाष्ठाions_end, cie, fde,
				frame, pc);

	/* FDE inकाष्ठाions */
	dwarf_cfa_execute_insns(fde->inकाष्ठाions, fde->end, cie,
				fde, frame, pc);

	/* Calculate the CFA */
	चयन (frame->flags) अणु
	हाल DWARF_FRAME_CFA_REG_OFFSET:
		अगर (prev) अणु
			reg = dwarf_frame_reg(prev, frame->cfa_रेजिस्टर);
			UNWINDER_BUG_ON(!reg);
			UNWINDER_BUG_ON(reg->flags != DWARF_REG_OFFSET);

			addr = prev->cfa + reg->addr;
			frame->cfa = __raw_पढ़ोl(addr);

		पूर्ण अन्यथा अणु
			/*
			 * Again, we're starting from the top of the
			 * stack. We need to physically पढ़ो
			 * the contents of a रेजिस्टर in order to get
			 * the Canonical Frame Address क्रम this
			 * function.
			 */
			frame->cfa = dwarf_पढ़ो_arch_reg(frame->cfa_रेजिस्टर);
		पूर्ण

		frame->cfa += frame->cfa_offset;
		अवरोध;
	शेष:
		UNWINDER_BUG();
	पूर्ण

	reg = dwarf_frame_reg(frame, DWARF_ARCH_RA_REG);

	/*
	 * If we haven't seen the वापस address रेजिस्टर or the वापस
	 * address column is undefined then we must assume that this is
	 * the end of the callstack.
	 */
	अगर (!reg || reg->flags == DWARF_UNDEFINED)
		जाओ bail;

	UNWINDER_BUG_ON(reg->flags != DWARF_REG_OFFSET);

	addr = frame->cfa + reg->addr;
	frame->वापस_addr = __raw_पढ़ोl(addr);

	/*
	 * Ah, the joys of unwinding through पूर्णांकerrupts.
	 *
	 * Interrupts are tricky - the DWARF info needs to be _really_
	 * accurate and unक्रमtunately I'm seeing a lot of bogus DWARF
	 * info. For example, I've seen पूर्णांकerrupts occur in epilogues
	 * just after the frame poपूर्णांकer (r14) had been restored. The
	 * problem was that the DWARF info claimed that the CFA could be
	 * reached by using the value of the frame poपूर्णांकer beक्रमe it was
	 * restored.
	 *
	 * So until the compiler can be trusted to produce reliable
	 * DWARF info when it really matters, let's stop unwinding once
	 * we've calculated the function that was पूर्णांकerrupted.
	 */
	अगर (prev && prev->pc == (अचिन्हित दीर्घ)ret_from_irq)
		frame->वापस_addr = 0;

	वापस frame;

bail:
	dwarf_मुक्त_frame(frame);
	वापस शून्य;
पूर्ण

अटल पूर्णांक dwarf_parse_cie(व्योम *entry, व्योम *p, अचिन्हित दीर्घ len,
			   अचिन्हित अक्षर *end, काष्ठा module *mod)
अणु
	काष्ठा rb_node **rb_node = &cie_root.rb_node;
	काष्ठा rb_node *parent = *rb_node;
	काष्ठा dwarf_cie *cie;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;

	cie = kzalloc(माप(*cie), GFP_KERNEL);
	अगर (!cie)
		वापस -ENOMEM;

	cie->length = len;

	/*
	 * Record the offset पूर्णांकo the .eh_frame section
	 * क्रम this CIE. It allows this CIE to be
	 * quickly and easily looked up from the
	 * corresponding FDE.
	 */
	cie->cie_poपूर्णांकer = (अचिन्हित दीर्घ)entry;

	cie->version = *(अक्षर *)p++;
	UNWINDER_BUG_ON(cie->version != 1);

	cie->augmentation = p;
	p += म_माप(cie->augmentation) + 1;

	count = dwarf_पढ़ो_uleb128(p, &cie->code_alignment_factor);
	p += count;

	count = dwarf_पढ़ो_leb128(p, &cie->data_alignment_factor);
	p += count;

	/*
	 * Which column in the rule table contains the
	 * वापस address?
	 */
	अगर (cie->version == 1) अणु
		cie->वापस_address_reg = __raw_पढ़ोb(p);
		p++;
	पूर्ण अन्यथा अणु
		count = dwarf_पढ़ो_uleb128(p, &cie->वापस_address_reg);
		p += count;
	पूर्ण

	अगर (cie->augmentation[0] == 'z') अणु
		अचिन्हित पूर्णांक length, count;
		cie->flags |= DWARF_CIE_Z_AUGMENTATION;

		count = dwarf_पढ़ो_uleb128(p, &length);
		p += count;

		UNWINDER_BUG_ON((अचिन्हित अक्षर *)p > end);

		cie->initial_inकाष्ठाions = p + length;
		cie->augmentation++;
	पूर्ण

	जबतक (*cie->augmentation) अणु
		/*
		 * "L" indicates a byte showing how the
		 * LSDA poपूर्णांकer is encoded. Skip it.
		 */
		अगर (*cie->augmentation == 'L') अणु
			p++;
			cie->augmentation++;
		पूर्ण अन्यथा अगर (*cie->augmentation == 'R') अणु
			/*
			 * "R" indicates a byte showing
			 * how FDE addresses are
			 * encoded.
			 */
			cie->encoding = *(अक्षर *)p++;
			cie->augmentation++;
		पूर्ण अन्यथा अगर (*cie->augmentation == 'P') अणु
			/*
			 * "R" indicates a personality
			 * routine in the CIE
			 * augmentation.
			 */
			UNWINDER_BUG();
		पूर्ण अन्यथा अगर (*cie->augmentation == 'S') अणु
			UNWINDER_BUG();
		पूर्ण अन्यथा अणु
			/*
			 * Unknown augmentation. Assume
			 * 'z' augmentation.
			 */
			p = cie->initial_inकाष्ठाions;
			UNWINDER_BUG_ON(!p);
			अवरोध;
		पूर्ण
	पूर्ण

	cie->initial_inकाष्ठाions = p;
	cie->inकाष्ठाions_end = end;

	/* Add to list */
	spin_lock_irqsave(&dwarf_cie_lock, flags);

	जबतक (*rb_node) अणु
		काष्ठा dwarf_cie *cie_पंचांगp;

		cie_पंचांगp = rb_entry(*rb_node, काष्ठा dwarf_cie, node);

		parent = *rb_node;

		अगर (cie->cie_poपूर्णांकer < cie_पंचांगp->cie_poपूर्णांकer)
			rb_node = &parent->rb_left;
		अन्यथा अगर (cie->cie_poपूर्णांकer >= cie_पंचांगp->cie_poपूर्णांकer)
			rb_node = &parent->rb_right;
		अन्यथा
			WARN_ON(1);
	पूर्ण

	rb_link_node(&cie->node, parent, rb_node);
	rb_insert_color(&cie->node, &cie_root);

#अगर_घोषित CONFIG_MODULES
	अगर (mod != शून्य)
		list_add_tail(&cie->link, &mod->arch.cie_list);
#पूर्ण_अगर

	spin_unlock_irqrestore(&dwarf_cie_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक dwarf_parse_fde(व्योम *entry, u32 entry_type,
			   व्योम *start, अचिन्हित दीर्घ len,
			   अचिन्हित अक्षर *end, काष्ठा module *mod)
अणु
	काष्ठा rb_node **rb_node = &fde_root.rb_node;
	काष्ठा rb_node *parent = *rb_node;
	काष्ठा dwarf_fde *fde;
	काष्ठा dwarf_cie *cie;
	अचिन्हित दीर्घ flags;
	पूर्णांक count;
	व्योम *p = start;

	fde = kzalloc(माप(*fde), GFP_KERNEL);
	अगर (!fde)
		वापस -ENOMEM;

	fde->length = len;

	/*
	 * In a .eh_frame section the CIE poपूर्णांकer is the
	 * delta between the address within the FDE
	 */
	fde->cie_poपूर्णांकer = (अचिन्हित दीर्घ)(p - entry_type - 4);

	cie = dwarf_lookup_cie(fde->cie_poपूर्णांकer);
	fde->cie = cie;

	अगर (cie->encoding)
		count = dwarf_पढ़ो_encoded_value(p, &fde->initial_location,
						 cie->encoding);
	अन्यथा
		count = dwarf_पढ़ो_addr(p, &fde->initial_location);

	p += count;

	अगर (cie->encoding)
		count = dwarf_पढ़ो_encoded_value(p, &fde->address_range,
						 cie->encoding & 0x0f);
	अन्यथा
		count = dwarf_पढ़ो_addr(p, &fde->address_range);

	p += count;

	अगर (fde->cie->flags & DWARF_CIE_Z_AUGMENTATION) अणु
		अचिन्हित पूर्णांक length;
		count = dwarf_पढ़ो_uleb128(p, &length);
		p += count + length;
	पूर्ण

	/* Call frame inकाष्ठाions. */
	fde->inकाष्ठाions = p;
	fde->end = end;

	/* Add to list. */
	spin_lock_irqsave(&dwarf_fde_lock, flags);

	जबतक (*rb_node) अणु
		काष्ठा dwarf_fde *fde_पंचांगp;
		अचिन्हित दीर्घ पंचांगp_start, पंचांगp_end;
		अचिन्हित दीर्घ start, end;

		fde_पंचांगp = rb_entry(*rb_node, काष्ठा dwarf_fde, node);

		start = fde->initial_location;
		end = fde->initial_location + fde->address_range;

		पंचांगp_start = fde_पंचांगp->initial_location;
		पंचांगp_end = fde_पंचांगp->initial_location + fde_पंचांगp->address_range;

		parent = *rb_node;

		अगर (start < पंचांगp_start)
			rb_node = &parent->rb_left;
		अन्यथा अगर (start >= पंचांगp_end)
			rb_node = &parent->rb_right;
		अन्यथा
			WARN_ON(1);
	पूर्ण

	rb_link_node(&fde->node, parent, rb_node);
	rb_insert_color(&fde->node, &fde_root);

#अगर_घोषित CONFIG_MODULES
	अगर (mod != शून्य)
		list_add_tail(&fde->link, &mod->arch.fde_list);
#पूर्ण_अगर

	spin_unlock_irqrestore(&dwarf_fde_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम dwarf_unwinder_dump(काष्ठा task_काष्ठा *task,
				काष्ठा pt_regs *regs,
				अचिन्हित दीर्घ *sp,
				स्थिर काष्ठा stacktrace_ops *ops,
				व्योम *data)
अणु
	काष्ठा dwarf_frame *frame, *_frame;
	अचिन्हित दीर्घ वापस_addr;

	_frame = शून्य;
	वापस_addr = 0;

	जबतक (1) अणु
		frame = dwarf_unwind_stack(वापस_addr, _frame);

		अगर (_frame)
			dwarf_मुक्त_frame(_frame);

		_frame = frame;

		अगर (!frame || !frame->वापस_addr)
			अवरोध;

		वापस_addr = frame->वापस_addr;
		ops->address(data, वापस_addr, 1);
	पूर्ण

	अगर (frame)
		dwarf_मुक्त_frame(frame);
पूर्ण

अटल काष्ठा unwinder dwarf_unwinder = अणु
	.name = "dwarf-unwinder",
	.dump = dwarf_unwinder_dump,
	.rating = 150,
पूर्ण;

अटल व्योम __init dwarf_unwinder_cleanup(व्योम)
अणु
	काष्ठा dwarf_fde *fde, *next_fde;
	काष्ठा dwarf_cie *cie, *next_cie;

	/*
	 * Deallocate all the memory allocated क्रम the DWARF unwinder.
	 * Traverse all the FDE/CIE lists and हटाओ and मुक्त all the
	 * memory associated with those data काष्ठाures.
	 */
	rbtree_postorder_क्रम_each_entry_safe(fde, next_fde, &fde_root, node)
		kमुक्त(fde);

	rbtree_postorder_क्रम_each_entry_safe(cie, next_cie, &cie_root, node)
		kमुक्त(cie);

	mempool_destroy(dwarf_reg_pool);
	mempool_destroy(dwarf_frame_pool);
	kmem_cache_destroy(dwarf_reg_cachep);
	kmem_cache_destroy(dwarf_frame_cachep);
पूर्ण

/**
 *	dwarf_parse_section - parse DWARF section
 *	@eh_frame_start: start address of the .eh_frame section
 *	@eh_frame_end: end address of the .eh_frame section
 *	@mod: the kernel module containing the .eh_frame section
 *
 *	Parse the inक्रमmation in a .eh_frame section.
 */
अटल पूर्णांक dwarf_parse_section(अक्षर *eh_frame_start, अक्षर *eh_frame_end,
			       काष्ठा module *mod)
अणु
	u32 entry_type;
	व्योम *p, *entry;
	पूर्णांक count, err = 0;
	अचिन्हित दीर्घ len = 0;
	अचिन्हित पूर्णांक c_entries, f_entries;
	अचिन्हित अक्षर *end;

	c_entries = 0;
	f_entries = 0;
	entry = eh_frame_start;

	जबतक ((अक्षर *)entry < eh_frame_end) अणु
		p = entry;

		count = dwarf_entry_len(p, &len);
		अगर (count == 0) अणु
			/*
			 * We पढ़ो a bogus length field value. There is
			 * nothing we can करो here apart from disabling
			 * the DWARF unwinder. We can't even skip this
			 * entry and move to the next one because 'len'
			 * tells us where our next entry is.
			 */
			err = -EINVAL;
			जाओ out;
		पूर्ण अन्यथा
			p += count;

		/* initial length करोes not include itself */
		end = p + len;

		entry_type = get_unaligned((u32 *)p);
		p += 4;

		अगर (entry_type == DW_EH_FRAME_CIE) अणु
			err = dwarf_parse_cie(entry, p, len, end, mod);
			अगर (err < 0)
				जाओ out;
			अन्यथा
				c_entries++;
		पूर्ण अन्यथा अणु
			err = dwarf_parse_fde(entry, entry_type, p, len,
					      end, mod);
			अगर (err < 0)
				जाओ out;
			अन्यथा
				f_entries++;
		पूर्ण

		entry = (अक्षर *)entry + len + 4;
	पूर्ण

	prपूर्णांकk(KERN_INFO "DWARF unwinder initialised: read %u CIEs, %u FDEs\n",
	       c_entries, f_entries);

	वापस 0;

out:
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_MODULES
पूर्णांक module_dwarf_finalize(स्थिर Elf_Ehdr *hdr, स्थिर Elf_Shdr *sechdrs,
			  काष्ठा module *me)
अणु
	अचिन्हित पूर्णांक i, err;
	अचिन्हित दीर्घ start, end;
	अक्षर *secstrings = (व्योम *)hdr + sechdrs[hdr->e_shstrndx].sh_offset;

	start = end = 0;

	क्रम (i = 1; i < hdr->e_shnum; i++) अणु
		/* Alloc bit cleared means "ignore it." */
		अगर ((sechdrs[i].sh_flags & SHF_ALLOC)
		    && !म_भेद(secstrings+sechdrs[i].sh_name, ".eh_frame")) अणु
			start = sechdrs[i].sh_addr;
			end = start + sechdrs[i].sh_size;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Did we find the .eh_frame section? */
	अगर (i != hdr->e_shnum) अणु
		INIT_LIST_HEAD(&me->arch.cie_list);
		INIT_LIST_HEAD(&me->arch.fde_list);
		err = dwarf_parse_section((अक्षर *)start, (अक्षर *)end, me);
		अगर (err) अणु
			prपूर्णांकk(KERN_WARNING "%s: failed to parse DWARF info\n",
			       me->name);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 *	module_dwarf_cleanup - हटाओ FDE/CIEs associated with @mod
 *	@mod: the module that is being unloaded
 *
 *	Remove any FDEs and CIEs from the global lists that came from
 *	@mod's .eh_frame section because @mod is being unloaded.
 */
व्योम module_dwarf_cleanup(काष्ठा module *mod)
अणु
	काष्ठा dwarf_fde *fde, *fपंचांगp;
	काष्ठा dwarf_cie *cie, *cपंचांगp;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&dwarf_cie_lock, flags);

	list_क्रम_each_entry_safe(cie, cपंचांगp, &mod->arch.cie_list, link) अणु
		list_del(&cie->link);
		rb_erase(&cie->node, &cie_root);
		kमुक्त(cie);
	पूर्ण

	spin_unlock_irqrestore(&dwarf_cie_lock, flags);

	spin_lock_irqsave(&dwarf_fde_lock, flags);

	list_क्रम_each_entry_safe(fde, fपंचांगp, &mod->arch.fde_list, link) अणु
		list_del(&fde->link);
		rb_erase(&fde->node, &fde_root);
		kमुक्त(fde);
	पूर्ण

	spin_unlock_irqrestore(&dwarf_fde_lock, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_MODULES */

/**
 *	dwarf_unwinder_init - initialise the dwarf unwinder
 *
 *	Build the data काष्ठाures describing the .dwarf_frame section to
 *	make it easier to lookup CIE and FDE entries. Because the
 *	.eh_frame section is packed as tightly as possible it is not
 *	easy to lookup the FDE क्रम a given PC, so we build a list of FDE
 *	and CIE entries that make it easier.
 */
अटल पूर्णांक __init dwarf_unwinder_init(व्योम)
अणु
	पूर्णांक err = -ENOMEM;

	dwarf_frame_cachep = kmem_cache_create("dwarf_frames",
			माप(काष्ठा dwarf_frame), 0,
			SLAB_PANIC | SLAB_HWCACHE_ALIGN, शून्य);

	dwarf_reg_cachep = kmem_cache_create("dwarf_regs",
			माप(काष्ठा dwarf_reg), 0,
			SLAB_PANIC | SLAB_HWCACHE_ALIGN, शून्य);

	dwarf_frame_pool = mempool_create_slab_pool(DWARF_FRAME_MIN_REQ,
						    dwarf_frame_cachep);
	अगर (!dwarf_frame_pool)
		जाओ out;

	dwarf_reg_pool = mempool_create_slab_pool(DWARF_REG_MIN_REQ,
						  dwarf_reg_cachep);
	अगर (!dwarf_reg_pool)
		जाओ out;

	err = dwarf_parse_section(__start_eh_frame, __stop_eh_frame, शून्य);
	अगर (err)
		जाओ out;

	err = unwinder_रेजिस्टर(&dwarf_unwinder);
	अगर (err)
		जाओ out;

	dwarf_unwinder_पढ़ोy = 1;

	वापस 0;

out:
	prपूर्णांकk(KERN_ERR "Failed to initialise DWARF unwinder: %d\n", err);
	dwarf_unwinder_cleanup();
	वापस err;
पूर्ण
early_initcall(dwarf_unwinder_init);
