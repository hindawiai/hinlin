<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	Apple Sound Chip
 */

#अगर_अघोषित __ASM_MAC_ASC_H
#घोषणा __ASM_MAC_ASC_H

/*
 *	ASC offsets and controls
 */

#घोषणा ASC_BUF_BASE	0x00	/* RAM buffer offset */
#घोषणा ASC_BUF_SIZE	0x800

#घोषणा ASC_CONTROL	0x800
#घोषणा ASC_CONTROL_OFF		0x00
#घोषणा ASC_FREQ(chan,byte)	((0x810)+((chan)<<3)+(byte))
#घोषणा ASC_ENABLE	0x801
#घोषणा ASC_ENABLE_SAMPLE	0x02
#घोषणा ASC_MODE	0x802
#घोषणा ASC_MODE_SAMPLE		0x02

#घोषणा ASC_VOLUME	0x806
#घोषणा ASC_CHAN	0x807	/* ??? */


#पूर्ण_अगर
