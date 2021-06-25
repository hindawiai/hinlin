<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright SUSE Linux Products GmbH 2009
 *
 * Authors: Alexander Graf <agraf@suse.de>
 */

#समावेश <linux/export.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/kvm_book3s.h>

#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
EXPORT_SYMBOL_GPL(kvmppc_hv_entry_trampoline);
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_PR_POSSIBLE
EXPORT_SYMBOL_GPL(kvmppc_entry_trampoline);
#पूर्ण_अगर

