<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/ipl.h>

/* VM IPL PARM routines */
माप_प्रकार ipl_block_get_ascii_vmparm(अक्षर *dest, माप_प्रकार size,
				  स्थिर काष्ठा ipl_parameter_block *ipb)
अणु
	पूर्णांक i;
	माप_प्रकार len;
	अक्षर has_lowerहाल = 0;

	len = 0;
	अगर ((ipb->ccw.vm_flags & IPL_PB0_CCW_VM_FLAG_VP) &&
	    (ipb->ccw.vm_parm_len > 0)) अणु

		len = min_t(माप_प्रकार, size - 1, ipb->ccw.vm_parm_len);
		स_नकल(dest, ipb->ccw.vm_parm, len);
		/* If at least one अक्षरacter is lowerहाल, we assume mixed
		 * हाल; otherwise we convert everything to lowerहाल.
		 */
		क्रम (i = 0; i < len; i++)
			अगर ((dest[i] > 0x80 && dest[i] < 0x8a) || /* a-i */
			    (dest[i] > 0x90 && dest[i] < 0x9a) || /* j-r */
			    (dest[i] > 0xa1 && dest[i] < 0xaa)) अणु /* s-z */
				has_lowerहाल = 1;
				अवरोध;
			पूर्ण
		अगर (!has_lowerहाल)
			EBC_TOLOWER(dest, len);
		EBCASC(dest, len);
	पूर्ण
	dest[len] = 0;

	वापस len;
पूर्ण
