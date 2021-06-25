<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Simple पूर्णांकerface to link xor_vmx.c and xor_vmx_glue.c
 *
 * Separating these file ensures that no altivec inकाष्ठाions are run
 * outside of the enable/disable altivec block.
 */

व्योम __xor_altivec_2(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
			     अचिन्हित दीर्घ *v2_in);

व्योम __xor_altivec_3(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
			     अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in);

व्योम __xor_altivec_4(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
			     अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in,
			     अचिन्हित दीर्घ *v4_in);

व्योम __xor_altivec_5(अचिन्हित दीर्घ bytes, अचिन्हित दीर्घ *v1_in,
			     अचिन्हित दीर्घ *v2_in, अचिन्हित दीर्घ *v3_in,
			     अचिन्हित दीर्घ *v4_in, अचिन्हित दीर्घ *v5_in);
