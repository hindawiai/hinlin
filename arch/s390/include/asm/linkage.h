<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_LINKAGE_H
#घोषणा __ASM_LINKAGE_H

#समावेश <यंत्र/यंत्र-स्थिर.h>
#समावेश <linux/stringअगरy.h>

#घोषणा __ALIGN .align 4, 0x07
#घोषणा __ALIGN_STR __stringअगरy(__ALIGN)

/*
 * Helper macro क्रम exception table entries
 */

#घोषणा __EX_TABLE(_section, _fault, _target)				\
	stringअगरy_in_c(.section	_section,"a";)				\
	stringअगरy_in_c(.align	8;)					\
	stringअगरy_in_c(.दीर्घ	(_fault) - .;)				\
	stringअगरy_in_c(.दीर्घ	(_target) - .;)				\
	stringअगरy_in_c(.quad	0;)					\
	stringअगरy_in_c(.previous)

#घोषणा EX_TABLE(_fault, _target)					\
	__EX_TABLE(__ex_table, _fault, _target)
#घोषणा EX_TABLE_DMA(_fault, _target)					\
	__EX_TABLE(.dma.ex_table, _fault, _target)

#पूर्ण_अगर
