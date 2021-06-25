<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * User-mode machine state access
 *
 * Copyright (C) 2007 Red Hat, Inc.  All rights reserved.
 *
 * Red Hat Author: Roland McGrath.
 */

#अगर_अघोषित _LINUX_REGSET_H
#घोषणा _LINUX_REGSET_H	1

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/bug.h>
#समावेश <linux/uaccess.h>
काष्ठा task_काष्ठा;
काष्ठा user_regset;

काष्ठा membuf अणु
	व्योम *p;
	माप_प्रकार left;
पूर्ण;

अटल अंतरभूत पूर्णांक membuf_zero(काष्ठा membuf *s, माप_प्रकार size)
अणु
	अगर (s->left) अणु
		अगर (size > s->left)
			size = s->left;
		स_रखो(s->p, 0, size);
		s->p += size;
		s->left -= size;
	पूर्ण
	वापस s->left;
पूर्ण

अटल अंतरभूत पूर्णांक membuf_ग_लिखो(काष्ठा membuf *s, स्थिर व्योम *v, माप_प्रकार size)
अणु
	अगर (s->left) अणु
		अगर (size > s->left)
			size = s->left;
		स_नकल(s->p, v, size);
		s->p += size;
		s->left -= size;
	पूर्ण
	वापस s->left;
पूर्ण

अटल अंतरभूत काष्ठा membuf membuf_at(स्थिर काष्ठा membuf *s, माप_प्रकार offs)
अणु
	काष्ठा membuf n = *s;

	अगर (offs > n.left)
		offs = n.left;
	n.p += offs;
	n.left -= offs;

	वापस n;
पूर्ण

/* current s->p must be aligned क्रम v; v must be a scalar */
#घोषणा membuf_store(s, v)				\
(अणु							\
	काष्ठा membuf *__s = (s);			\
        अगर (__s->left) अणु				\
		typeof(v) __v = (v);			\
		माप_प्रकार __size = माप(__v);		\
		अगर (unlikely(__size > __s->left)) अणु	\
			__size = __s->left;		\
			स_नकल(__s->p, &__v, __size);	\
		पूर्ण अन्यथा अणु				\
			*(typeof(__v + 0) *)__s->p = __v;	\
		पूर्ण					\
		__s->p += __size;			\
		__s->left -= __size;			\
	पूर्ण						\
	__s->left;पूर्ण)

/**
 * user_regset_active_fn - type of @active function in &काष्ठा user_regset
 * @target:	thपढ़ो being examined
 * @regset:	regset being examined
 *
 * Return -%ENODEV अगर not available on the hardware found.
 * Return %0 अगर no पूर्णांकeresting state in this thपढ़ो.
 * Return >%0 number of @size units of पूर्णांकeresting state.
 * Any get call fetching state beyond that number will
 * see the शेष initialization state क्रम this data,
 * so a caller that knows what the शेष state is need
 * not copy it all out.
 * This call is optional; the poपूर्णांकer is %शून्य अगर there
 * is no inexpensive check to yield a value < @n.
 */
प्रकार पूर्णांक user_regset_active_fn(काष्ठा task_काष्ठा *target,
				  स्थिर काष्ठा user_regset *regset);

प्रकार पूर्णांक user_regset_get2_fn(काष्ठा task_काष्ठा *target,
			       स्थिर काष्ठा user_regset *regset,
			       काष्ठा membuf to);

/**
 * user_regset_set_fn - type of @set function in &काष्ठा user_regset
 * @target:	thपढ़ो being examined
 * @regset:	regset being examined
 * @pos:	offset पूर्णांकo the regset data to access, in bytes
 * @count:	amount of data to copy, in bytes
 * @kbuf:	अगर not %शून्य, a kernel-space poपूर्णांकer to copy from
 * @ubuf:	अगर @kbuf is %शून्य, a user-space poपूर्णांकer to copy from
 *
 * Store रेजिस्टर values.  Return %0 on success; -%EIO or -%ENODEV
 * are usual failure वापसs.  The @pos and @count values are in
 * bytes, but must be properly aligned.  If @kbuf is non-null, that
 * buffer is used and @ubuf is ignored.  If @kbuf is %शून्य, then
 * ubuf gives a userland poपूर्णांकer to access directly, and an -%EFAULT
 * वापस value is possible.
 */
प्रकार पूर्णांक user_regset_set_fn(काष्ठा task_काष्ठा *target,
			       स्थिर काष्ठा user_regset *regset,
			       अचिन्हित पूर्णांक pos, अचिन्हित पूर्णांक count,
			       स्थिर व्योम *kbuf, स्थिर व्योम __user *ubuf);

/**
 * user_regset_ग_लिखोback_fn - type of @ग_लिखोback function in &काष्ठा user_regset
 * @target:	thपढ़ो being examined
 * @regset:	regset being examined
 * @immediate:	zero अगर ग_लिखोback at completion of next context चयन is OK
 *
 * This call is optional; usually the poपूर्णांकer is %शून्य.  When
 * provided, there is some user memory associated with this regset's
 * hardware, such as memory backing cached रेजिस्टर data on रेजिस्टर
 * winकरोw machines; the regset's data controls what user memory is
 * used (e.g. via the stack poपूर्णांकer value).
 *
 * Write रेजिस्टर data back to user memory.  If the @immediate flag
 * is nonzero, it must be written to the user memory so uaccess or
 * access_process_vm() can see it when this call वापसs; अगर zero,
 * then it must be written back by the समय the task completes a
 * context चयन (as synchronized with रुको_task_inactive()).
 * Return %0 on success or अगर there was nothing to करो, -%EFAULT क्रम
 * a memory problem (bad stack poपूर्णांकer or whatever), or -%EIO क्रम a
 * hardware problem.
 */
प्रकार पूर्णांक user_regset_ग_लिखोback_fn(काष्ठा task_काष्ठा *target,
				     स्थिर काष्ठा user_regset *regset,
				     पूर्णांक immediate);

/**
 * काष्ठा user_regset - accessible thपढ़ो CPU state
 * @n:			Number of slots (रेजिस्टरs).
 * @size:		Size in bytes of a slot (रेजिस्टर).
 * @align:		Required alignment, in bytes.
 * @bias:		Bias from natural indexing.
 * @core_note_type:	ELF note @n_type value used in core dumps.
 * @get:		Function to fetch values.
 * @set:		Function to store values.
 * @active:		Function to report अगर regset is active, or %शून्य.
 * @ग_लिखोback:		Function to ग_लिखो data back to user memory, or %शून्य.
 *
 * This data काष्ठाure describes a machine resource we call a रेजिस्टर set.
 * This is part of the state of an inभागidual thपढ़ो, not necessarily
 * actual CPU रेजिस्टरs per se.  A रेजिस्टर set consists of a number of
 * similar slots, given by @n.  Each slot is @size bytes, and aligned to
 * @align bytes (which is at least @size).  For dynamically-sized
 * regsets, @n must contain the maximum possible number of slots क्रम the
 * regset.
 *
 * For backward compatibility, the @get and @set methods must pad to, or
 * accept, @n * @size bytes, even अगर the current regset size is smaller.
 * The precise semantics of these operations depend on the regset being
 * accessed.
 *
 * The functions to which &काष्ठा user_regset members poपूर्णांक must be
 * called only on the current thपढ़ो or on a thपढ़ो that is in
 * %TASK_STOPPED or %TASK_TRACED state, that we are guaranteed will not
 * be woken up and वापस to user mode, and that we have called
 * रुको_task_inactive() on.  (The target thपढ़ो always might wake up क्रम
 * SIGKILL जबतक these functions are working, in which हाल that
 * thपढ़ो's user_regset state might be scrambled.)
 *
 * The @pos argument must be aligned according to @align; the @count
 * argument must be a multiple of @size.  These functions are not
 * responsible क्रम checking क्रम invalid arguments.
 *
 * When there is a natural value to use as an index, @bias gives the
 * dअगरference between the natural index and the slot index क्रम the
 * रेजिस्टर set.  For example, x86 GDT segment descriptors क्रमm a regset;
 * the segment selector produces a natural index, but only a subset of
 * that index space is available as a regset (the TLS slots); subtracting
 * @bias from a segment selector index value computes the regset slot.
 *
 * If nonzero, @core_note_type gives the n_type field (NT_* value)
 * of the core file note in which this regset's data appears.
 * NT_PRSTATUS is a special हाल in that the regset data starts at
 * दुरत्व(काष्ठा elf_prstatus, pr_reg) पूर्णांकo the note data; that is
 * part of the per-machine ELF क्रमmats userland knows about.  In
 * other हालs, the core file note contains exactly the whole regset
 * (@n * @size) and nothing अन्यथा.  The core file note is normally
 * omitted when there is an @active function and it वापसs zero.
 */
काष्ठा user_regset अणु
	user_regset_get2_fn		*regset_get;
	user_regset_set_fn		*set;
	user_regset_active_fn		*active;
	user_regset_ग_लिखोback_fn	*ग_लिखोback;
	अचिन्हित पूर्णांक			n;
	अचिन्हित पूर्णांक 			size;
	अचिन्हित पूर्णांक 			align;
	अचिन्हित पूर्णांक 			bias;
	अचिन्हित पूर्णांक 			core_note_type;
पूर्ण;

/**
 * काष्ठा user_regset_view - available regsets
 * @name:	Identअगरier, e.g. UTS_MACHINE string.
 * @regsets:	Array of @n regsets available in this view.
 * @n:		Number of elements in @regsets.
 * @e_machine:	ELF header @e_machine %EM_* value written in core dumps.
 * @e_flags:	ELF header @e_flags value written in core dumps.
 * @ei_osabi:	ELF header @e_ident[%EI_OSABI] value written in core dumps.
 *
 * A regset view is a collection of regsets (&काष्ठा user_regset,
 * above).  This describes all the state of a thपढ़ो that can be seen
 * from a given architecture/ABI environment.  More than one view might
 * refer to the same &काष्ठा user_regset, or more than one regset
 * might refer to the same machine-specअगरic state in the thपढ़ो.  For
 * example, a 32-bit thपढ़ो's state could be examined from the 32-bit
 * view or from the 64-bit view.  Either method reaches the same thपढ़ो
 * रेजिस्टर state, करोing appropriate widening or truncation.
 */
काष्ठा user_regset_view अणु
	स्थिर अक्षर *name;
	स्थिर काष्ठा user_regset *regsets;
	अचिन्हित पूर्णांक n;
	u32 e_flags;
	u16 e_machine;
	u8 ei_osabi;
पूर्ण;

/*
 * This is करोcumented here rather than at the definition sites because its
 * implementation is machine-dependent but its पूर्णांकerface is universal.
 */
/**
 * task_user_regset_view - Return the process's native regset view.
 * @tsk: a thपढ़ो of the process in question
 *
 * Return the &काष्ठा user_regset_view that is native क्रम the given process.
 * For example, what it would access when it called ptrace().
 * Throughout the lअगरe of the process, this only changes at exec.
 */
स्थिर काष्ठा user_regset_view *task_user_regset_view(काष्ठा task_काष्ठा *tsk);

अटल अंतरभूत पूर्णांक user_regset_copyin(अचिन्हित पूर्णांक *pos, अचिन्हित पूर्णांक *count,
				     स्थिर व्योम **kbuf,
				     स्थिर व्योम __user **ubuf, व्योम *data,
				     स्थिर पूर्णांक start_pos, स्थिर पूर्णांक end_pos)
अणु
	अगर (*count == 0)
		वापस 0;
	BUG_ON(*pos < start_pos);
	अगर (end_pos < 0 || *pos < end_pos) अणु
		अचिन्हित पूर्णांक copy = (end_pos < 0 ? *count
				     : min(*count, end_pos - *pos));
		data += *pos - start_pos;
		अगर (*kbuf) अणु
			स_नकल(data, *kbuf, copy);
			*kbuf += copy;
		पूर्ण अन्यथा अगर (__copy_from_user(data, *ubuf, copy))
			वापस -EFAULT;
		अन्यथा
			*ubuf += copy;
		*pos += copy;
		*count -= copy;
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक user_regset_copyin_ignore(अचिन्हित पूर्णांक *pos,
					    अचिन्हित पूर्णांक *count,
					    स्थिर व्योम **kbuf,
					    स्थिर व्योम __user **ubuf,
					    स्थिर पूर्णांक start_pos,
					    स्थिर पूर्णांक end_pos)
अणु
	अगर (*count == 0)
		वापस 0;
	BUG_ON(*pos < start_pos);
	अगर (end_pos < 0 || *pos < end_pos) अणु
		अचिन्हित पूर्णांक copy = (end_pos < 0 ? *count
				     : min(*count, end_pos - *pos));
		अगर (*kbuf)
			*kbuf += copy;
		अन्यथा
			*ubuf += copy;
		*pos += copy;
		*count -= copy;
	पूर्ण
	वापस 0;
पूर्ण

बाह्य पूर्णांक regset_get(काष्ठा task_काष्ठा *target,
		      स्थिर काष्ठा user_regset *regset,
		      अचिन्हित पूर्णांक size, व्योम *data);

बाह्य पूर्णांक regset_get_alloc(काष्ठा task_काष्ठा *target,
			    स्थिर काष्ठा user_regset *regset,
			    अचिन्हित पूर्णांक size,
			    व्योम **data);

बाह्य पूर्णांक copy_regset_to_user(काष्ठा task_काष्ठा *target,
			       स्थिर काष्ठा user_regset_view *view,
			       अचिन्हित पूर्णांक setno, अचिन्हित पूर्णांक offset,
			       अचिन्हित पूर्णांक size, व्योम __user *data);

/**
 * copy_regset_from_user - store पूर्णांकo thपढ़ो's user_regset data from user memory
 * @target:	thपढ़ो to be examined
 * @view:	&काष्ठा user_regset_view describing user thपढ़ो machine state
 * @setno:	index in @view->regsets
 * @offset:	offset पूर्णांकo the regset data, in bytes
 * @size:	amount of data to copy, in bytes
 * @data:	user-mode poपूर्णांकer to copy from
 */
अटल अंतरभूत पूर्णांक copy_regset_from_user(काष्ठा task_काष्ठा *target,
					स्थिर काष्ठा user_regset_view *view,
					अचिन्हित पूर्णांक setno,
					अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size,
					स्थिर व्योम __user *data)
अणु
	स्थिर काष्ठा user_regset *regset = &view->regsets[setno];

	अगर (!regset->set)
		वापस -EOPNOTSUPP;

	अगर (!access_ok(data, size))
		वापस -EFAULT;

	वापस regset->set(target, regset, offset, size, शून्य, data);
पूर्ण

#पूर्ण_अगर	/* <linux/regset.h> */
