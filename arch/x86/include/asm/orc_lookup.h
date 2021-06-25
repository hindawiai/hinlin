<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2017 Josh Poimboeuf <jpoimboe@redhat.com>
 */
#अगर_अघोषित _ORC_LOOKUP_H
#घोषणा _ORC_LOOKUP_H

/*
 * This is a lookup table क्रम speeding up access to the .orc_unwind table.
 * Given an input address offset, the corresponding lookup table entry
 * specअगरies a subset of the .orc_unwind table to search.
 *
 * Each block represents the end of the previous range and the start of the
 * next range.  An extra block is added to give the last range an end.
 *
 * The block size should be a घातer of 2 to aव्योम a costly 'div' inकाष्ठाion.
 *
 * A block size of 256 was chosen because it roughly द्विगुनs unwinder
 * perक्रमmance जबतक only adding ~5% to the ORC data footprपूर्णांक.
 */
#घोषणा LOOKUP_BLOCK_ORDER	8
#घोषणा LOOKUP_BLOCK_SIZE	(1 << LOOKUP_BLOCK_ORDER)

#अगर_अघोषित LINKER_SCRIPT

बाह्य अचिन्हित पूर्णांक orc_lookup[];
बाह्य अचिन्हित पूर्णांक orc_lookup_end[];

#घोषणा LOOKUP_START_IP		(अचिन्हित दीर्घ)_stext
#घोषणा LOOKUP_STOP_IP		(अचिन्हित दीर्घ)_etext

#पूर्ण_अगर /* LINKER_SCRIPT */

#पूर्ण_अगर /* _ORC_LOOKUP_H */
