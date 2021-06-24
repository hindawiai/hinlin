<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* This handles the memory map.. */

#अगर defined(CONFIG_RAMBASE)
#घोषणा PAGE_OFFSET_RAW		CONFIG_RAMBASE
#या_अगर defined(CONFIG_SUN3)
#घोषणा PAGE_OFFSET_RAW		0x0E000000
#अन्यथा
#घोषणा PAGE_OFFSET_RAW		0x00000000
#पूर्ण_अगर
