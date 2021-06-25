<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_LSU_H
#घोषणा _SPARC64_LSU_H

#समावेश <linux/स्थिर.h>

/* LSU Control Register */
#घोषणा LSU_CONTROL_PM _AC(0x000001fe00000000,UL) /* Phys-watchpoपूर्णांक byte mask*/
#घोषणा LSU_CONTROL_VM _AC(0x00000001fe000000,UL) /* Virt-watchpoपूर्णांक byte mask*/
#घोषणा LSU_CONTROL_PR _AC(0x0000000001000000,UL) /* Phys-rd watchpoपूर्णांक enable*/
#घोषणा LSU_CONTROL_PW _AC(0x0000000000800000,UL) /* Phys-wr watchpoपूर्णांक enable*/
#घोषणा LSU_CONTROL_VR _AC(0x0000000000400000,UL) /* Virt-rd watchpoपूर्णांक enable*/
#घोषणा LSU_CONTROL_VW _AC(0x0000000000200000,UL) /* Virt-wr watchpoपूर्णांक enable*/
#घोषणा LSU_CONTROL_FM _AC(0x00000000000ffff0,UL) /* Parity mask enables.     */
#घोषणा LSU_CONTROL_DM _AC(0x0000000000000008,UL) /* Data MMU enable.         */
#घोषणा LSU_CONTROL_IM _AC(0x0000000000000004,UL) /* Inकाष्ठाion MMU enable.  */
#घोषणा LSU_CONTROL_DC _AC(0x0000000000000002,UL) /* Data cache enable.       */
#घोषणा LSU_CONTROL_IC _AC(0x0000000000000001,UL) /* Inकाष्ठाion cache enable.*/

#पूर्ण_अगर /* !(_SPARC64_LSU_H) */
