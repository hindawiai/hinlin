<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) 2019 ARM Limited */
#समावेश "testcases.h"

काष्ठा _aarch64_ctx *get_header(काष्ठा _aarch64_ctx *head, uपूर्णांक32_t magic,
				माप_प्रकार resv_sz, माप_प्रकार *offset)
अणु
	माप_प्रकार offs = 0;
	काष्ठा _aarch64_ctx *found = शून्य;

	अगर (!head || resv_sz < HDR_SZ)
		वापस found;

	जबतक (offs <= resv_sz - HDR_SZ &&
	       head->magic != magic && head->magic) अणु
		offs += head->size;
		head = GET_RESV_NEXT_HEAD(head);
	पूर्ण
	अगर (head->magic == magic) अणु
		found = head;
		अगर (offset)
			*offset = offs;
	पूर्ण

	वापस found;
पूर्ण

bool validate_extra_context(काष्ठा extra_context *extra, अक्षर **err)
अणु
	काष्ठा _aarch64_ctx *term;

	अगर (!extra || !err)
		वापस false;

	ख_लिखो(मानक_त्रुटि, "Validating EXTRA...\n");
	term = GET_RESV_NEXT_HEAD(extra);
	अगर (!term || term->magic || term->size) अणु
		*err = "Missing terminator after EXTRA context";
		वापस false;
	पूर्ण
	अगर (extra->datap & 0x0fUL)
		*err = "Extra DATAP misaligned";
	अन्यथा अगर (extra->size & 0x0fUL)
		*err = "Extra SIZE misaligned";
	अन्यथा अगर (extra->datap != (uपूर्णांक64_t)term + माप(*term))
		*err = "Extra DATAP misplaced (not contiguous)";
	अगर (*err)
		वापस false;

	वापस true;
पूर्ण

bool validate_reserved(ucontext_t *uc, माप_प्रकार resv_sz, अक्षर **err)
अणु
	bool terminated = false;
	माप_प्रकार offs = 0;
	पूर्णांक flags = 0;
	काष्ठा extra_context *extra = शून्य;
	काष्ठा _aarch64_ctx *head =
		(काष्ठा _aarch64_ctx *)uc->uc_mcontext.__reserved;

	अगर (!err)
		वापस false;
	/* Walk till the end terminator verअगरying __reserved contents */
	जबतक (head && !terminated && offs < resv_sz) अणु
		अगर ((uपूर्णांक64_t)head & 0x0fUL) अणु
			*err = "Misaligned HEAD";
			वापस false;
		पूर्ण

		चयन (head->magic) अणु
		हाल 0:
			अगर (head->size)
				*err = "Bad size for terminator";
			अन्यथा
				terminated = true;
			अवरोध;
		हाल FPSIMD_MAGIC:
			अगर (flags & FPSIMD_CTX)
				*err = "Multiple FPSIMD_MAGIC";
			अन्यथा अगर (head->size !=
				 माप(काष्ठा fpsimd_context))
				*err = "Bad size for fpsimd_context";
			flags |= FPSIMD_CTX;
			अवरोध;
		हाल ESR_MAGIC:
			अगर (head->size != माप(काष्ठा esr_context))
				*err = "Bad size for esr_context";
			अवरोध;
		हाल SVE_MAGIC:
			अगर (flags & SVE_CTX)
				*err = "Multiple SVE_MAGIC";
			अन्यथा अगर (head->size !=
				 माप(काष्ठा sve_context))
				*err = "Bad size for sve_context";
			flags |= SVE_CTX;
			अवरोध;
		हाल EXTRA_MAGIC:
			अगर (flags & EXTRA_CTX)
				*err = "Multiple EXTRA_MAGIC";
			अन्यथा अगर (head->size !=
				 माप(काष्ठा extra_context))
				*err = "Bad size for extra_context";
			flags |= EXTRA_CTX;
			extra = (काष्ठा extra_context *)head;
			अवरोध;
		हाल KSFT_BAD_MAGIC:
			/*
			 * This is a BAD magic header defined
			 * artअगरicially by a testहाल and surely
			 * unknown to the Kernel parse_user_sigframe().
			 * It MUST cause a Kernel induced SEGV
			 */
			*err = "BAD MAGIC !";
			अवरोध;
		शेष:
			/*
			 * A still unknown Magic: potentially freshly added
			 * to the Kernel code and still unknown to the
			 * tests.
			 */
			ख_लिखो(मानक_निकास,
				"SKIP Unknown MAGIC: 0x%X - Is KSFT arm64/signal up to date ?\n",
				head->magic);
			अवरोध;
		पूर्ण

		अगर (*err)
			वापस false;

		offs += head->size;
		अगर (resv_sz < offs + माप(*head)) अणु
			*err = "HEAD Overrun";
			वापस false;
		पूर्ण

		अगर (flags & EXTRA_CTX)
			अगर (!validate_extra_context(extra, err))
				वापस false;

		head = GET_RESV_NEXT_HEAD(head);
	पूर्ण

	अगर (terminated && !(flags & FPSIMD_CTX)) अणु
		*err = "Missing FPSIMD";
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

/*
 * This function walks through the records inside the provided reserved area
 * trying to find enough space to fit @need_sz bytes: अगर not enough space is
 * available and an extra_context record is present, it throws away the
 * extra_context record.
 *
 * It वापसs a poपूर्णांकer to a new header where it is possible to start storing
 * our need_sz bytes.
 *
 * @shead: poपूर्णांकs to the start of reserved area
 * @need_sz: needed bytes
 * @resv_sz: reserved area size in bytes
 * @offset: अगर not null, this will be filled with the offset of the वापस
 *	    head poपूर्णांकer from @shead
 *
 * @वापस: poपूर्णांकer to a new head where to start storing need_sz bytes, or
 *	    शून्य अगर space could not be made available.
 */
काष्ठा _aarch64_ctx *get_starting_head(काष्ठा _aarch64_ctx *shead,
				       माप_प्रकार need_sz, माप_प्रकार resv_sz,
				       माप_प्रकार *offset)
अणु
	माप_प्रकार offs = 0;
	काष्ठा _aarch64_ctx *head;

	head = get_terminator(shead, resv_sz, &offs);
	/* not found a terminator...no need to update offset अगर any */
	अगर (!head)
		वापस head;
	अगर (resv_sz - offs < need_sz) अणु
		ख_लिखो(मानक_त्रुटि, "Low on space:%zd. Discarding extra_context.\n",
			resv_sz - offs);
		head = get_header(shead, EXTRA_MAGIC, resv_sz, &offs);
		अगर (!head || resv_sz - offs < need_sz) अणु
			ख_लिखो(मानक_त्रुटि,
				"Failed to reclaim space on sigframe.\n");
			वापस शून्य;
		पूर्ण
	पूर्ण

	ख_लिखो(मानक_त्रुटि, "Available space:%zd\n", resv_sz - offs);
	अगर (offset)
		*offset = offs;
	वापस head;
पूर्ण
