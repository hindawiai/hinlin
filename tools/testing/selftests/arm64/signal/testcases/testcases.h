<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2019 ARM Limited */
#अगर_अघोषित __TESTCASES_H__
#घोषणा __TESTCASES_H__

#समावेश <मानकघोष.स>
#समावेश <मानकपन.स>
#समावेश <stdbool.h>
#समावेश <मानक_निवेशt.h>
#समावेश <मानककोष.स>
#समावेश <ucontext.h>
#समावेश <संकेत.स>

/* Architecture specअगरic sigframe definitions */
#समावेश <यंत्र/sigcontext.h>

#घोषणा FPSIMD_CTX	(1 << 0)
#घोषणा SVE_CTX		(1 << 1)
#घोषणा EXTRA_CTX	(1 << 2)

#घोषणा KSFT_BAD_MAGIC	0xdeadbeef

#घोषणा HDR_SZ \
	माप(काष्ठा _aarch64_ctx)

#घोषणा GET_SF_RESV_HEAD(sf) \
	(काष्ठा _aarch64_ctx *)(&(sf).uc.uc_mcontext.__reserved)

#घोषणा GET_SF_RESV_SIZE(sf) \
	माप((sf).uc.uc_mcontext.__reserved)

#घोषणा GET_UCP_RESV_SIZE(ucp) \
	माप((ucp)->uc_mcontext.__reserved)

#घोषणा ASSERT_BAD_CONTEXT(uc) करो अणु					\
	अक्षर *err = शून्य;						\
	अगर (!validate_reserved((uc), GET_UCP_RESV_SIZE((uc)), &err)) अणु	\
		अगर (err)						\
			ख_लिखो(मानक_त्रुटि,					\
				"Using badly built context - ERR: %s\n",\
				err);					\
	पूर्ण अन्यथा अणु							\
		पात();						\
	पूर्ण								\
पूर्ण जबतक (0)

#घोषणा ASSERT_GOOD_CONTEXT(uc) करो अणु					 \
	अक्षर *err = शून्य;						 \
	अगर (!validate_reserved((uc), GET_UCP_RESV_SIZE((uc)), &err)) अणु	 \
		अगर (err)						 \
			ख_लिखो(मानक_त्रुटि,					 \
				"Detected BAD context - ERR: %s\n", err);\
		पात();						 \
	पूर्ण अन्यथा अणु							 \
		ख_लिखो(मानक_त्रुटि, "uc context validated.\n");		 \
	पूर्ण								 \
पूर्ण जबतक (0)

/*
 * A simple record-walker क्रम __reserved area: it walks through assuming
 * only to find a proper काष्ठा __aarch64_ctx header descriptor.
 *
 * Instead it makes no assumptions on the content and ordering of the
 * records, any needed bounds checking must be enक्रमced by the caller
 * अगर wanted: this way can be used by caller on any maliciously built bad
 * contexts.
 *
 * head->size accounts both क्रम payload and header _aarch64_ctx size !
 */
#घोषणा GET_RESV_NEXT_HEAD(h) \
	(काष्ठा _aarch64_ctx *)((अक्षर *)(h) + (h)->size)

काष्ठा fake_sigframe अणु
	siginfo_t	info;
	ucontext_t	uc;
पूर्ण;


bool validate_reserved(ucontext_t *uc, माप_प्रकार resv_sz, अक्षर **err);

bool validate_extra_context(काष्ठा extra_context *extra, अक्षर **err);

काष्ठा _aarch64_ctx *get_header(काष्ठा _aarch64_ctx *head, uपूर्णांक32_t magic,
				माप_प्रकार resv_sz, माप_प्रकार *offset);

अटल अंतरभूत काष्ठा _aarch64_ctx *get_terminator(काष्ठा _aarch64_ctx *head,
						  माप_प्रकार resv_sz,
						  माप_प्रकार *offset)
अणु
	वापस get_header(head, 0, resv_sz, offset);
पूर्ण

अटल अंतरभूत व्योम ग_लिखो_terminator_record(काष्ठा _aarch64_ctx *tail)
अणु
	अगर (tail) अणु
		tail->magic = 0;
		tail->size = 0;
	पूर्ण
पूर्ण

काष्ठा _aarch64_ctx *get_starting_head(काष्ठा _aarch64_ctx *shead,
				       माप_प्रकार need_sz, माप_प्रकार resv_sz,
				       माप_प्रकार *offset);
#पूर्ण_अगर
