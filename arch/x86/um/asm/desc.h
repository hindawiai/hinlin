<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_DESC_H
#घोषणा __UM_DESC_H

/* Taken from यंत्र-i386/desc.h, it's the only thing we need. The rest wouldn't
 * compile, and has never been used. */
#घोषणा LDT_empty(info) (\
	(info)->base_addr	== 0	&& \
	(info)->limit		== 0	&& \
	(info)->contents	== 0	&& \
	(info)->पढ़ो_exec_only	== 1	&& \
	(info)->seg_32bit	== 0	&& \
	(info)->limit_in_pages	== 0	&& \
	(info)->seg_not_present	== 1	&& \
	(info)->useable		== 0	)

#पूर्ण_अगर
