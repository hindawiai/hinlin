<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC64_SCRATCHPAD_H
#घोषणा _SPARC64_SCRATCHPAD_H

/* Sun4v scratchpad रेजिस्टरs, accessed via ASI_SCRATCHPAD.  */

#घोषणा SCRATCHPAD_MMU_MISS	0x00 /* Shared with OBP - set by OBP	    */
#घोषणा SCRATCHPAD_CPUID	0x08 /* Shared with OBP - set by hypervisor */
#घोषणा SCRATCHPAD_UTSBREG1	0x10
#घोषणा SCRATCHPAD_UTSBREG2	0x18
	/* 0x20 and 0x28, hypervisor only... */
#घोषणा SCRATCHPAD_UNUSED1	0x30
#घोषणा SCRATCHPAD_UNUSED2	0x38 /* Reserved क्रम OBP		    */

#पूर्ण_अगर /* !(_SPARC64_SCRATCHPAD_H) */
