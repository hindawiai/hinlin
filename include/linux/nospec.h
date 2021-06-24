<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright(c) 2018 Linus Torvalds. All rights reserved.
// Copyright(c) 2018 Alexei Starovoitov. All rights reserved.
// Copyright(c) 2018 Intel Corporation. All rights reserved.

#अगर_अघोषित _LINUX_NOSPEC_H
#घोषणा _LINUX_NOSPEC_H

#समावेश <linux/compiler.h>
#समावेश <यंत्र/barrier.h>

काष्ठा task_काष्ठा;

/**
 * array_index_mask_nospec() - generate a ~0 mask when index < size, 0 otherwise
 * @index: array element index
 * @size: number of elements in array
 *
 * When @index is out of bounds (@index >= @size), the sign bit will be
 * set.  Extend the sign bit to all bits and invert, giving a result of
 * zero क्रम an out of bounds index, or ~0 अगर within bounds [0, @size).
 */
#अगर_अघोषित array_index_mask_nospec
अटल अंतरभूत अचिन्हित दीर्घ array_index_mask_nospec(अचिन्हित दीर्घ index,
						    अचिन्हित दीर्घ size)
अणु
	/*
	 * Always calculate and emit the mask even अगर the compiler
	 * thinks the mask is not needed. The compiler करोes not take
	 * पूर्णांकo account the value of @index under speculation.
	 */
	OPTIMIZER_HIDE_VAR(index);
	वापस ~(दीर्घ)(index | (size - 1UL - index)) >> (BITS_PER_LONG - 1);
पूर्ण
#पूर्ण_अगर

/*
 * array_index_nospec - sanitize an array index after a bounds check
 *
 * For a code sequence like:
 *
 *     अगर (index < size) अणु
 *         index = array_index_nospec(index, size);
 *         val = array[index];
 *     पूर्ण
 *
 * ...अगर the CPU speculates past the bounds check then
 * array_index_nospec() will clamp the index within the range of [0,
 * size).
 */
#घोषणा array_index_nospec(index, size)					\
(अणु									\
	typeof(index) _i = (index);					\
	typeof(size) _s = (size);					\
	अचिन्हित दीर्घ _mask = array_index_mask_nospec(_i, _s);		\
									\
	BUILD_BUG_ON(माप(_i) > माप(दीर्घ));			\
	BUILD_BUG_ON(माप(_s) > माप(दीर्घ));			\
									\
	(typeof(_i)) (_i & _mask);					\
पूर्ण)

/* Speculation control prctl */
पूर्णांक arch_prctl_spec_ctrl_get(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which);
पूर्णांक arch_prctl_spec_ctrl_set(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ which,
			     अचिन्हित दीर्घ ctrl);
/* Speculation control क्रम seccomp enक्रमced mitigation */
व्योम arch_seccomp_spec_mitigate(काष्ठा task_काष्ठा *task);

#पूर्ण_अगर /* _LINUX_NOSPEC_H */
