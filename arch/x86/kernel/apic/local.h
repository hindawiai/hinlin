<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Historical copyright notices:
 *
 * Copyright 2004 James Cleverकरोn, IBM.
 * (c) 1995 Alan Cox, Building #3 <alan@redhat.com>
 * (c) 1998-99, 2000 Ingo Molnar <mingo@redhat.com>
 * (c) 2002,2003 Andi Kleen, SuSE Lअसल.
 */

#समावेश <linux/jump_label.h>

#समावेश <यंत्र/irq_vectors.h>
#समावेश <यंत्र/apic.h>

/* APIC flat 64 */
व्योम flat_init_apic_ldr(व्योम);

/* X2APIC */
पूर्णांक x2apic_apic_id_valid(u32 apicid);
पूर्णांक x2apic_apic_id_रेजिस्टरed(व्योम);
व्योम __x2apic_send_IPI_dest(अचिन्हित पूर्णांक apicid, पूर्णांक vector, अचिन्हित पूर्णांक dest);
अचिन्हित पूर्णांक x2apic_get_apic_id(अचिन्हित दीर्घ id);
u32 x2apic_set_apic_id(अचिन्हित पूर्णांक id);
पूर्णांक x2apic_phys_pkg_id(पूर्णांक initial_apicid, पूर्णांक index_msb);
व्योम x2apic_send_IPI_self(पूर्णांक vector);
व्योम __x2apic_send_IPI_लघुhand(पूर्णांक vector, u32 which);

/* IPI */

DECLARE_STATIC_KEY_FALSE(apic_use_ipi_लघुhand);

अटल अंतरभूत अचिन्हित पूर्णांक __prepare_ICR(अचिन्हित पूर्णांक लघुcut, पूर्णांक vector,
					 अचिन्हित पूर्णांक dest)
अणु
	अचिन्हित पूर्णांक icr = लघुcut | dest;

	चयन (vector) अणु
	शेष:
		icr |= APIC_DM_FIXED | vector;
		अवरोध;
	हाल NMI_VECTOR:
		icr |= APIC_DM_NMI;
		अवरोध;
	पूर्ण
	वापस icr;
पूर्ण

व्योम __शेष_send_IPI_लघुcut(अचिन्हित पूर्णांक लघुcut, पूर्णांक vector);

/*
 * This is used to send an IPI with no लघुhand notation (the destination is
 * specअगरied in bits 56 to 63 of the ICR).
 */
व्योम __शेष_send_IPI_dest_field(अचिन्हित पूर्णांक mask, पूर्णांक vector, अचिन्हित पूर्णांक dest);

व्योम शेष_send_IPI_single(पूर्णांक cpu, पूर्णांक vector);
व्योम शेष_send_IPI_single_phys(पूर्णांक cpu, पूर्णांक vector);
व्योम शेष_send_IPI_mask_sequence_phys(स्थिर काष्ठा cpumask *mask, पूर्णांक vector);
व्योम शेष_send_IPI_mask_allbutself_phys(स्थिर काष्ठा cpumask *mask, पूर्णांक vector);
व्योम शेष_send_IPI_allbutself(पूर्णांक vector);
व्योम शेष_send_IPI_all(पूर्णांक vector);
व्योम शेष_send_IPI_self(पूर्णांक vector);

#अगर_घोषित CONFIG_X86_32
व्योम शेष_send_IPI_mask_sequence_logical(स्थिर काष्ठा cpumask *mask, पूर्णांक vector);
व्योम शेष_send_IPI_mask_allbutself_logical(स्थिर काष्ठा cpumask *mask, पूर्णांक vector);
व्योम शेष_send_IPI_mask_logical(स्थिर काष्ठा cpumask *mask, पूर्णांक vector);
#पूर्ण_अगर
