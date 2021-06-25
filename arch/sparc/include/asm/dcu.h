<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_DCU_H
#घोषणा _SPARC64_DCU_H

#समावेश <linux/स्थिर.h>

/* UltraSparc-III Data Cache Unit Control Register */
#घोषणा DCU_CP	_AC(0x0002000000000000,UL) /* Phys Cache Enable w/o mmu	*/
#घोषणा DCU_CV	_AC(0x0001000000000000,UL) /* Virt Cache Enable w/o mmu	*/
#घोषणा DCU_ME	_AC(0x0000800000000000,UL) /* NC-store Merging Enable	*/
#घोषणा DCU_RE	_AC(0x0000400000000000,UL) /* RAW bypass Enable		*/
#घोषणा DCU_PE	_AC(0x0000200000000000,UL) /* PCache Enable		*/
#घोषणा DCU_HPE	_AC(0x0000100000000000,UL) /* HW prefetch Enable	*/
#घोषणा DCU_SPE	_AC(0x0000080000000000,UL) /* SW prefetch Enable	*/
#घोषणा DCU_SL	_AC(0x0000040000000000,UL) /* Secondary ld-steering Enab*/
#घोषणा DCU_WE	_AC(0x0000020000000000,UL) /* WCache enable		*/
#घोषणा DCU_PM	_AC(0x000001fe00000000,UL) /* PA Watchpoपूर्णांक Byte Mask	*/
#घोषणा DCU_VM	_AC(0x00000001fe000000,UL) /* VA Watchpoपूर्णांक Byte Mask	*/
#घोषणा DCU_PR	_AC(0x0000000001000000,UL) /* PA Watchpoपूर्णांक Read Enable	*/
#घोषणा DCU_PW	_AC(0x0000000000800000,UL) /* PA Watchpoपूर्णांक Write Enable*/
#घोषणा DCU_VR	_AC(0x0000000000400000,UL) /* VA Watchpoपूर्णांक Read Enable	*/
#घोषणा DCU_VW	_AC(0x0000000000200000,UL) /* VA Watchpoपूर्णांक Write Enable*/
#घोषणा DCU_DM	_AC(0x0000000000000008,UL) /* DMMU Enable		*/
#घोषणा DCU_IM	_AC(0x0000000000000004,UL) /* IMMU Enable		*/
#घोषणा DCU_DC	_AC(0x0000000000000002,UL) /* Data Cache Enable		*/
#घोषणा DCU_IC	_AC(0x0000000000000001,UL) /* Inकाष्ठाion Cache Enable	*/

#पूर्ण_अगर /* _SPARC64_DCU_H */
