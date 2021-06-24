<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * SGI UV IRQ definitions
 *
 * Copyright (C) 2008 Silicon Graphics, Inc. All rights reserved.
 */

#अगर_अघोषित _ASM_X86_UV_UV_IRQ_H
#घोषणा _ASM_X86_UV_UV_IRQ_H

/* If a generic version of this काष्ठाure माला_लो defined, eliminate this one. */
काष्ठा uv_IO_APIC_route_entry अणु
	__u64	vector		:  8,
		delivery_mode	:  3,
		dest_mode	:  1,
		delivery_status	:  1,
		polarity	:  1,
		__reserved_1	:  1,
		trigger		:  1,
		mask		:  1,
		__reserved_2	: 15,
		dest		: 32;
पूर्ण;

क्रमागत अणु
	UV_AFFINITY_ALL,
	UV_AFFINITY_NODE,
	UV_AFFINITY_CPU
पूर्ण;

बाह्य पूर्णांक uv_irq_2_mmr_info(पूर्णांक, अचिन्हित दीर्घ *, पूर्णांक *);
बाह्य पूर्णांक uv_setup_irq(अक्षर *, पूर्णांक, पूर्णांक, अचिन्हित दीर्घ, पूर्णांक);
बाह्य व्योम uv_tearकरोwn_irq(अचिन्हित पूर्णांक);

#पूर्ण_अगर /* _ASM_X86_UV_UV_IRQ_H */
