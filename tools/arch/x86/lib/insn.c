<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * x86 inकाष्ठाion analysis
 *
 * Copyright (C) IBM Corporation, 2002, 2004, 2009
 */

#समावेश <linux/kernel.h>
#अगर_घोषित __KERNEL__
#समावेश <linux/माला.स>
#अन्यथा
#समावेश <माला.स>
#पूर्ण_अगर
#समावेश "../include/asm/inat.h" /* __ignore_sync_check__ */
#समावेश "../include/asm/insn.h" /* __ignore_sync_check__ */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kconfig.h>

#समावेश "../include/asm/emulate_prefix.h" /* __ignore_sync_check__ */

#घोषणा leXX_to_cpu(t, r)						\
(अणु									\
	__typeof__(t) v;						\
	चयन (माप(t)) अणु						\
	हाल 4: v = le32_to_cpu(r); अवरोध;				\
	हाल 2: v = le16_to_cpu(r); अवरोध;				\
	हाल 1:	v = r; अवरोध;						\
	शेष:							\
		BUILD_BUG(); अवरोध;					\
	पूर्ण								\
	v;								\
पूर्ण)

/* Verअगरy next माप(t) bytes can be on the same inकाष्ठाion */
#घोषणा validate_next(t, insn, n)	\
	((insn)->next_byte + माप(t) + n <= (insn)->end_kaddr)

#घोषणा __get_next(t, insn)	\
	(अणु t r = *(t*)insn->next_byte; insn->next_byte += माप(t); leXX_to_cpu(t, r); पूर्ण)

#घोषणा __peek_nbyte_next(t, insn, n)	\
	(अणु t r = *(t*)((insn)->next_byte + n); leXX_to_cpu(t, r); पूर्ण)

#घोषणा get_next(t, insn)	\
	(अणु अगर (unlikely(!validate_next(t, insn, 0))) जाओ err_out; __get_next(t, insn); पूर्ण)

#घोषणा peek_nbyte_next(t, insn, n)	\
	(अणु अगर (unlikely(!validate_next(t, insn, n))) जाओ err_out; __peek_nbyte_next(t, insn, n); पूर्ण)

#घोषणा peek_next(t, insn)	peek_nbyte_next(t, insn, 0)

/**
 * insn_init() - initialize काष्ठा insn
 * @insn:	&काष्ठा insn to be initialized
 * @kaddr:	address (in kernel memory) of inकाष्ठाion (or copy thereof)
 * @buf_len:	length of the insn buffer at @kaddr
 * @x86_64:	!0 क्रम 64-bit kernel or 64-bit app
 */
व्योम insn_init(काष्ठा insn *insn, स्थिर व्योम *kaddr, पूर्णांक buf_len, पूर्णांक x86_64)
अणु
	/*
	 * Inकाष्ठाions दीर्घer than MAX_INSN_SIZE (15 bytes) are invalid
	 * even अगर the input buffer is दीर्घ enough to hold them.
	 */
	अगर (buf_len > MAX_INSN_SIZE)
		buf_len = MAX_INSN_SIZE;

	स_रखो(insn, 0, माप(*insn));
	insn->kaddr = kaddr;
	insn->end_kaddr = kaddr + buf_len;
	insn->next_byte = kaddr;
	insn->x86_64 = x86_64 ? 1 : 0;
	insn->opnd_bytes = 4;
	अगर (x86_64)
		insn->addr_bytes = 8;
	अन्यथा
		insn->addr_bytes = 4;
पूर्ण

अटल स्थिर insn_byte_t xen_prefix[] = अणु __XEN_EMULATE_PREFIX पूर्ण;
अटल स्थिर insn_byte_t kvm_prefix[] = अणु __KVM_EMULATE_PREFIX पूर्ण;

अटल पूर्णांक __insn_get_emulate_prefix(काष्ठा insn *insn,
				     स्थिर insn_byte_t *prefix, माप_प्रकार len)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < len; i++) अणु
		अगर (peek_nbyte_next(insn_byte_t, insn, i) != prefix[i])
			जाओ err_out;
	पूर्ण

	insn->emulate_prefix_size = len;
	insn->next_byte += len;

	वापस 1;

err_out:
	वापस 0;
पूर्ण

अटल व्योम insn_get_emulate_prefix(काष्ठा insn *insn)
अणु
	अगर (__insn_get_emulate_prefix(insn, xen_prefix, माप(xen_prefix)))
		वापस;

	__insn_get_emulate_prefix(insn, kvm_prefix, माप(kvm_prefix));
पूर्ण

/**
 * insn_get_prefixes - scan x86 inकाष्ठाion prefix bytes
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * Populates the @insn->prefixes biपंचांगap, and updates @insn->next_byte
 * to poपूर्णांक to the (first) opcode.  No effect अगर @insn->prefixes.got
 * is alपढ़ोy set.
 *
 * * Returns:
 * 0:  on success
 * < 0: on error
 */
पूर्णांक insn_get_prefixes(काष्ठा insn *insn)
अणु
	काष्ठा insn_field *prefixes = &insn->prefixes;
	insn_attr_t attr;
	insn_byte_t b, lb;
	पूर्णांक i, nb;

	अगर (prefixes->got)
		वापस 0;

	insn_get_emulate_prefix(insn);

	nb = 0;
	lb = 0;
	b = peek_next(insn_byte_t, insn);
	attr = inat_get_opcode_attribute(b);
	जबतक (inat_is_legacy_prefix(attr)) अणु
		/* Skip अगर same prefix */
		क्रम (i = 0; i < nb; i++)
			अगर (prefixes->bytes[i] == b)
				जाओ found;
		अगर (nb == 4)
			/* Invalid inकाष्ठाion */
			अवरोध;
		prefixes->bytes[nb++] = b;
		अगर (inat_is_address_size_prefix(attr)) अणु
			/* address size चयनes 2/4 or 4/8 */
			अगर (insn->x86_64)
				insn->addr_bytes ^= 12;
			अन्यथा
				insn->addr_bytes ^= 6;
		पूर्ण अन्यथा अगर (inat_is_opeअक्रम_size_prefix(attr)) अणु
			/* opअक्रम size चयनes 2/4 */
			insn->opnd_bytes ^= 6;
		पूर्ण
found:
		prefixes->nbytes++;
		insn->next_byte++;
		lb = b;
		b = peek_next(insn_byte_t, insn);
		attr = inat_get_opcode_attribute(b);
	पूर्ण
	/* Set the last prefix */
	अगर (lb && lb != insn->prefixes.bytes[3]) अणु
		अगर (unlikely(insn->prefixes.bytes[3])) अणु
			/* Swap the last prefix */
			b = insn->prefixes.bytes[3];
			क्रम (i = 0; i < nb; i++)
				अगर (prefixes->bytes[i] == lb)
					insn_set_byte(prefixes, i, b);
		पूर्ण
		insn_set_byte(&insn->prefixes, 3, lb);
	पूर्ण

	/* Decode REX prefix */
	अगर (insn->x86_64) अणु
		b = peek_next(insn_byte_t, insn);
		attr = inat_get_opcode_attribute(b);
		अगर (inat_is_rex_prefix(attr)) अणु
			insn_field_set(&insn->rex_prefix, b, 1);
			insn->next_byte++;
			अगर (X86_REX_W(b))
				/* REX.W overrides opnd_size */
				insn->opnd_bytes = 8;
		पूर्ण
	पूर्ण
	insn->rex_prefix.got = 1;

	/* Decode VEX prefix */
	b = peek_next(insn_byte_t, insn);
	attr = inat_get_opcode_attribute(b);
	अगर (inat_is_vex_prefix(attr)) अणु
		insn_byte_t b2 = peek_nbyte_next(insn_byte_t, insn, 1);
		अगर (!insn->x86_64) अणु
			/*
			 * In 32-bits mode, अगर the [7:6] bits (mod bits of
			 * ModRM) on the second byte are not 11b, it is
			 * LDS or LES or BOUND.
			 */
			अगर (X86_MODRM_MOD(b2) != 3)
				जाओ vex_end;
		पूर्ण
		insn_set_byte(&insn->vex_prefix, 0, b);
		insn_set_byte(&insn->vex_prefix, 1, b2);
		अगर (inat_is_evex_prefix(attr)) अणु
			b2 = peek_nbyte_next(insn_byte_t, insn, 2);
			insn_set_byte(&insn->vex_prefix, 2, b2);
			b2 = peek_nbyte_next(insn_byte_t, insn, 3);
			insn_set_byte(&insn->vex_prefix, 3, b2);
			insn->vex_prefix.nbytes = 4;
			insn->next_byte += 4;
			अगर (insn->x86_64 && X86_VEX_W(b2))
				/* VEX.W overrides opnd_size */
				insn->opnd_bytes = 8;
		पूर्ण अन्यथा अगर (inat_is_vex3_prefix(attr)) अणु
			b2 = peek_nbyte_next(insn_byte_t, insn, 2);
			insn_set_byte(&insn->vex_prefix, 2, b2);
			insn->vex_prefix.nbytes = 3;
			insn->next_byte += 3;
			अगर (insn->x86_64 && X86_VEX_W(b2))
				/* VEX.W overrides opnd_size */
				insn->opnd_bytes = 8;
		पूर्ण अन्यथा अणु
			/*
			 * For VEX2, fake VEX3-like byte#2.
			 * Makes it easier to decode vex.W, vex.vvvv,
			 * vex.L and vex.pp. Masking with 0x7f sets vex.W == 0.
			 */
			insn_set_byte(&insn->vex_prefix, 2, b2 & 0x7f);
			insn->vex_prefix.nbytes = 2;
			insn->next_byte += 2;
		पूर्ण
	पूर्ण
vex_end:
	insn->vex_prefix.got = 1;

	prefixes->got = 1;

	वापस 0;

err_out:
	वापस -ENODATA;
पूर्ण

/**
 * insn_get_opcode - collect opcode(s)
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * Populates @insn->opcode, updates @insn->next_byte to poपूर्णांक past the
 * opcode byte(s), and set @insn->attr (except क्रम groups).
 * If necessary, first collects any preceding (prefix) bytes.
 * Sets @insn->opcode.value = opcode1.  No effect अगर @insn->opcode.got
 * is alपढ़ोy 1.
 *
 * Returns:
 * 0:  on success
 * < 0: on error
 */
पूर्णांक insn_get_opcode(काष्ठा insn *insn)
अणु
	काष्ठा insn_field *opcode = &insn->opcode;
	पूर्णांक pfx_id, ret;
	insn_byte_t op;

	अगर (opcode->got)
		वापस 0;

	अगर (!insn->prefixes.got) अणु
		ret = insn_get_prefixes(insn);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Get first opcode */
	op = get_next(insn_byte_t, insn);
	insn_set_byte(opcode, 0, op);
	opcode->nbytes = 1;

	/* Check अगर there is VEX prefix or not */
	अगर (insn_is_avx(insn)) अणु
		insn_byte_t m, p;
		m = insn_vex_m_bits(insn);
		p = insn_vex_p_bits(insn);
		insn->attr = inat_get_avx_attribute(op, m, p);
		अगर ((inat_must_evex(insn->attr) && !insn_is_evex(insn)) ||
		    (!inat_accept_vex(insn->attr) &&
		     !inat_is_group(insn->attr))) अणु
			/* This inकाष्ठाion is bad */
			insn->attr = 0;
			वापस -EINVAL;
		पूर्ण
		/* VEX has only 1 byte क्रम opcode */
		जाओ end;
	पूर्ण

	insn->attr = inat_get_opcode_attribute(op);
	जबतक (inat_is_escape(insn->attr)) अणु
		/* Get escaped opcode */
		op = get_next(insn_byte_t, insn);
		opcode->bytes[opcode->nbytes++] = op;
		pfx_id = insn_last_prefix_id(insn);
		insn->attr = inat_get_escape_attribute(op, pfx_id, insn->attr);
	पूर्ण

	अगर (inat_must_vex(insn->attr)) अणु
		/* This inकाष्ठाion is bad */
		insn->attr = 0;
		वापस -EINVAL;
	पूर्ण
end:
	opcode->got = 1;
	वापस 0;

err_out:
	वापस -ENODATA;
पूर्ण

/**
 * insn_get_modrm - collect ModRM byte, अगर any
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * Populates @insn->modrm and updates @insn->next_byte to poपूर्णांक past the
 * ModRM byte, अगर any.  If necessary, first collects the preceding bytes
 * (prefixes and opcode(s)).  No effect अगर @insn->modrm.got is alपढ़ोy 1.
 *
 * Returns:
 * 0:  on success
 * < 0: on error
 */
पूर्णांक insn_get_modrm(काष्ठा insn *insn)
अणु
	काष्ठा insn_field *modrm = &insn->modrm;
	insn_byte_t pfx_id, mod;
	पूर्णांक ret;

	अगर (modrm->got)
		वापस 0;

	अगर (!insn->opcode.got) अणु
		ret = insn_get_opcode(insn);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (inat_has_modrm(insn->attr)) अणु
		mod = get_next(insn_byte_t, insn);
		insn_field_set(modrm, mod, 1);
		अगर (inat_is_group(insn->attr)) अणु
			pfx_id = insn_last_prefix_id(insn);
			insn->attr = inat_get_group_attribute(mod, pfx_id,
							      insn->attr);
			अगर (insn_is_avx(insn) && !inat_accept_vex(insn->attr)) अणु
				/* Bad insn */
				insn->attr = 0;
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (insn->x86_64 && inat_is_क्रमce64(insn->attr))
		insn->opnd_bytes = 8;

	modrm->got = 1;
	वापस 0;

err_out:
	वापस -ENODATA;
पूर्ण


/**
 * insn_rip_relative() - Does inकाष्ठाion use RIP-relative addressing mode?
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * If necessary, first collects the inकाष्ठाion up to and including the
 * ModRM byte.  No effect अगर @insn->x86_64 is 0.
 */
पूर्णांक insn_rip_relative(काष्ठा insn *insn)
अणु
	काष्ठा insn_field *modrm = &insn->modrm;
	पूर्णांक ret;

	अगर (!insn->x86_64)
		वापस 0;

	अगर (!modrm->got) अणु
		ret = insn_get_modrm(insn);
		अगर (ret)
			वापस 0;
	पूर्ण
	/*
	 * For rip-relative inकाष्ठाions, the mod field (top 2 bits)
	 * is zero and the r/m field (bottom 3 bits) is 0x5.
	 */
	वापस (modrm->nbytes && (modrm->bytes[0] & 0xc7) == 0x5);
पूर्ण

/**
 * insn_get_sib() - Get the SIB byte of inकाष्ठाion
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * If necessary, first collects the inकाष्ठाion up to and including the
 * ModRM byte.
 *
 * Returns:
 * 0: अगर decoding succeeded
 * < 0: otherwise.
 */
पूर्णांक insn_get_sib(काष्ठा insn *insn)
अणु
	insn_byte_t modrm;
	पूर्णांक ret;

	अगर (insn->sib.got)
		वापस 0;

	अगर (!insn->modrm.got) अणु
		ret = insn_get_modrm(insn);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (insn->modrm.nbytes) अणु
		modrm = insn->modrm.bytes[0];
		अगर (insn->addr_bytes != 2 &&
		    X86_MODRM_MOD(modrm) != 3 && X86_MODRM_RM(modrm) == 4) अणु
			insn_field_set(&insn->sib,
				       get_next(insn_byte_t, insn), 1);
		पूर्ण
	पूर्ण
	insn->sib.got = 1;

	वापस 0;

err_out:
	वापस -ENODATA;
पूर्ण


/**
 * insn_get_displacement() - Get the displacement of inकाष्ठाion
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * If necessary, first collects the inकाष्ठाion up to and including the
 * SIB byte.
 * Displacement value is sign-expanded.
 *
 * * Returns:
 * 0: अगर decoding succeeded
 * < 0: otherwise.
 */
पूर्णांक insn_get_displacement(काष्ठा insn *insn)
अणु
	insn_byte_t mod, rm, base;
	पूर्णांक ret;

	अगर (insn->displacement.got)
		वापस 0;

	अगर (!insn->sib.got) अणु
		ret = insn_get_sib(insn);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (insn->modrm.nbytes) अणु
		/*
		 * Interpreting the modrm byte:
		 * mod = 00 - no displacement fields (exceptions below)
		 * mod = 01 - 1-byte displacement field
		 * mod = 10 - displacement field is 4 bytes, or 2 bytes अगर
		 * 	address size = 2 (0x67 prefix in 32-bit mode)
		 * mod = 11 - no memory opeअक्रम
		 *
		 * If address size = 2...
		 * mod = 00, r/m = 110 - displacement field is 2 bytes
		 *
		 * If address size != 2...
		 * mod != 11, r/m = 100 - SIB byte exists
		 * mod = 00, SIB base = 101 - displacement field is 4 bytes
		 * mod = 00, r/m = 101 - rip-relative addressing, displacement
		 * 	field is 4 bytes
		 */
		mod = X86_MODRM_MOD(insn->modrm.value);
		rm = X86_MODRM_RM(insn->modrm.value);
		base = X86_SIB_BASE(insn->sib.value);
		अगर (mod == 3)
			जाओ out;
		अगर (mod == 1) अणु
			insn_field_set(&insn->displacement,
				       get_next(चिन्हित अक्षर, insn), 1);
		पूर्ण अन्यथा अगर (insn->addr_bytes == 2) अणु
			अगर ((mod == 0 && rm == 6) || mod == 2) अणु
				insn_field_set(&insn->displacement,
					       get_next(लघु, insn), 2);
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((mod == 0 && rm == 5) || mod == 2 ||
			    (mod == 0 && base == 5)) अणु
				insn_field_set(&insn->displacement,
					       get_next(पूर्णांक, insn), 4);
			पूर्ण
		पूर्ण
	पूर्ण
out:
	insn->displacement.got = 1;
	वापस 0;

err_out:
	वापस -ENODATA;
पूर्ण

/* Decode moffset16/32/64. Return 0 अगर failed */
अटल पूर्णांक __get_moffset(काष्ठा insn *insn)
अणु
	चयन (insn->addr_bytes) अणु
	हाल 2:
		insn_field_set(&insn->moffset1, get_next(लघु, insn), 2);
		अवरोध;
	हाल 4:
		insn_field_set(&insn->moffset1, get_next(पूर्णांक, insn), 4);
		अवरोध;
	हाल 8:
		insn_field_set(&insn->moffset1, get_next(पूर्णांक, insn), 4);
		insn_field_set(&insn->moffset2, get_next(पूर्णांक, insn), 4);
		अवरोध;
	शेष:	/* opnd_bytes must be modअगरied manually */
		जाओ err_out;
	पूर्ण
	insn->moffset1.got = insn->moffset2.got = 1;

	वापस 1;

err_out:
	वापस 0;
पूर्ण

/* Decode imm v32(Iz). Return 0 अगर failed */
अटल पूर्णांक __get_immv32(काष्ठा insn *insn)
अणु
	चयन (insn->opnd_bytes) अणु
	हाल 2:
		insn_field_set(&insn->immediate, get_next(लघु, insn), 2);
		अवरोध;
	हाल 4:
	हाल 8:
		insn_field_set(&insn->immediate, get_next(पूर्णांक, insn), 4);
		अवरोध;
	शेष:	/* opnd_bytes must be modअगरied manually */
		जाओ err_out;
	पूर्ण

	वापस 1;

err_out:
	वापस 0;
पूर्ण

/* Decode imm v64(Iv/Ov), Return 0 अगर failed */
अटल पूर्णांक __get_immv(काष्ठा insn *insn)
अणु
	चयन (insn->opnd_bytes) अणु
	हाल 2:
		insn_field_set(&insn->immediate1, get_next(लघु, insn), 2);
		अवरोध;
	हाल 4:
		insn_field_set(&insn->immediate1, get_next(पूर्णांक, insn), 4);
		insn->immediate1.nbytes = 4;
		अवरोध;
	हाल 8:
		insn_field_set(&insn->immediate1, get_next(पूर्णांक, insn), 4);
		insn_field_set(&insn->immediate2, get_next(पूर्णांक, insn), 4);
		अवरोध;
	शेष:	/* opnd_bytes must be modअगरied manually */
		जाओ err_out;
	पूर्ण
	insn->immediate1.got = insn->immediate2.got = 1;

	वापस 1;
err_out:
	वापस 0;
पूर्ण

/* Decode ptr16:16/32(Ap) */
अटल पूर्णांक __get_immptr(काष्ठा insn *insn)
अणु
	चयन (insn->opnd_bytes) अणु
	हाल 2:
		insn_field_set(&insn->immediate1, get_next(लघु, insn), 2);
		अवरोध;
	हाल 4:
		insn_field_set(&insn->immediate1, get_next(पूर्णांक, insn), 4);
		अवरोध;
	हाल 8:
		/* ptr16:64 is not exist (no segment) */
		वापस 0;
	शेष:	/* opnd_bytes must be modअगरied manually */
		जाओ err_out;
	पूर्ण
	insn_field_set(&insn->immediate2, get_next(अचिन्हित लघु, insn), 2);
	insn->immediate1.got = insn->immediate2.got = 1;

	वापस 1;
err_out:
	वापस 0;
पूर्ण

/**
 * insn_get_immediate() - Get the immediate in an inकाष्ठाion
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * If necessary, first collects the inकाष्ठाion up to and including the
 * displacement bytes.
 * Basically, most of immediates are sign-expanded. Unचिन्हित-value can be
 * computed by bit masking with ((1 << (nbytes * 8)) - 1)
 *
 * Returns:
 * 0:  on success
 * < 0: on error
 */
पूर्णांक insn_get_immediate(काष्ठा insn *insn)
अणु
	पूर्णांक ret;

	अगर (insn->immediate.got)
		वापस 0;

	अगर (!insn->displacement.got) अणु
		ret = insn_get_displacement(insn);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (inat_has_moffset(insn->attr)) अणु
		अगर (!__get_moffset(insn))
			जाओ err_out;
		जाओ करोne;
	पूर्ण

	अगर (!inat_has_immediate(insn->attr))
		/* no immediates */
		जाओ करोne;

	चयन (inat_immediate_size(insn->attr)) अणु
	हाल INAT_IMM_BYTE:
		insn_field_set(&insn->immediate, get_next(चिन्हित अक्षर, insn), 1);
		अवरोध;
	हाल INAT_IMM_WORD:
		insn_field_set(&insn->immediate, get_next(लघु, insn), 2);
		अवरोध;
	हाल INAT_IMM_DWORD:
		insn_field_set(&insn->immediate, get_next(पूर्णांक, insn), 4);
		अवरोध;
	हाल INAT_IMM_QWORD:
		insn_field_set(&insn->immediate1, get_next(पूर्णांक, insn), 4);
		insn_field_set(&insn->immediate2, get_next(पूर्णांक, insn), 4);
		अवरोध;
	हाल INAT_IMM_PTR:
		अगर (!__get_immptr(insn))
			जाओ err_out;
		अवरोध;
	हाल INAT_IMM_VWORD32:
		अगर (!__get_immv32(insn))
			जाओ err_out;
		अवरोध;
	हाल INAT_IMM_VWORD:
		अगर (!__get_immv(insn))
			जाओ err_out;
		अवरोध;
	शेष:
		/* Here, insn must have an immediate, but failed */
		जाओ err_out;
	पूर्ण
	अगर (inat_has_second_immediate(insn->attr)) अणु
		insn_field_set(&insn->immediate2, get_next(चिन्हित अक्षर, insn), 1);
	पूर्ण
करोne:
	insn->immediate.got = 1;
	वापस 0;

err_out:
	वापस -ENODATA;
पूर्ण

/**
 * insn_get_length() - Get the length of inकाष्ठाion
 * @insn:	&काष्ठा insn containing inकाष्ठाion
 *
 * If necessary, first collects the inकाष्ठाion up to and including the
 * immediates bytes.
 *
 * Returns:
 *  - 0 on success
 *  - < 0 on error
*/
पूर्णांक insn_get_length(काष्ठा insn *insn)
अणु
	पूर्णांक ret;

	अगर (insn->length)
		वापस 0;

	अगर (!insn->immediate.got) अणु
		ret = insn_get_immediate(insn);
		अगर (ret)
			वापस ret;
	पूर्ण

	insn->length = (अचिन्हित अक्षर)((अचिन्हित दीर्घ)insn->next_byte
				     - (अचिन्हित दीर्घ)insn->kaddr);

	वापस 0;
पूर्ण

/* Ensure this inकाष्ठाion is decoded completely */
अटल अंतरभूत पूर्णांक insn_complete(काष्ठा insn *insn)
अणु
	वापस insn->opcode.got && insn->modrm.got && insn->sib.got &&
		insn->displacement.got && insn->immediate.got;
पूर्ण

/**
 * insn_decode() - Decode an x86 inकाष्ठाion
 * @insn:	&काष्ठा insn to be initialized
 * @kaddr:	address (in kernel memory) of inकाष्ठाion (or copy thereof)
 * @buf_len:	length of the insn buffer at @kaddr
 * @m:		insn mode, see क्रमागत insn_mode
 *
 * Returns:
 * 0: अगर decoding succeeded
 * < 0: otherwise.
 */
पूर्णांक insn_decode(काष्ठा insn *insn, स्थिर व्योम *kaddr, पूर्णांक buf_len, क्रमागत insn_mode m)
अणु
	पूर्णांक ret;

#घोषणा INSN_MODE_KERN (क्रमागत insn_mode)-1 /* __ignore_sync_check__ mode is only valid in the kernel */

	अगर (m == INSN_MODE_KERN)
		insn_init(insn, kaddr, buf_len, IS_ENABLED(CONFIG_X86_64));
	अन्यथा
		insn_init(insn, kaddr, buf_len, m == INSN_MODE_64);

	ret = insn_get_length(insn);
	अगर (ret)
		वापस ret;

	अगर (insn_complete(insn))
		वापस 0;

	वापस -EINVAL;
पूर्ण
