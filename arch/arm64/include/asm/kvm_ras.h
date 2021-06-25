<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright (C) 2018 - Arm Ltd */

#अगर_अघोषित __ARM64_KVM_RAS_H__
#घोषणा __ARM64_KVM_RAS_H__

#समावेश <linux/acpi.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/types.h>

#समावेश <यंत्र/acpi.h>

/*
 * Was this synchronous बाह्यal पात a RAS notअगरication?
 * Returns '0' क्रम errors handled by some RAS subप्रणाली, or -ENOENT.
 */
अटल अंतरभूत पूर्णांक kvm_handle_guest_sea(phys_addr_t addr, अचिन्हित पूर्णांक esr)
अणु
	/* apei_claim_sea(शून्य) expects to mask पूर्णांकerrupts itself */
	lockdep_निश्चित_irqs_enabled();

	वापस apei_claim_sea(शून्य);
पूर्ण

#पूर्ण_अगर /* __ARM64_KVM_RAS_H__ */
