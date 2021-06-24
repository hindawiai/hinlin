<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * kvm asynchronous fault support
 *
 * Copyright 2010 Red Hat, Inc.
 *
 * Author:
 *      Gleb Natapov <gleb@redhat.com>
 */

#अगर_अघोषित __KVM_ASYNC_PF_H__
#घोषणा __KVM_ASYNC_PF_H__

#अगर_घोषित CONFIG_KVM_ASYNC_PF
पूर्णांक kvm_async_pf_init(व्योम);
व्योम kvm_async_pf_deinit(व्योम);
व्योम kvm_async_pf_vcpu_init(काष्ठा kvm_vcpu *vcpu);
#अन्यथा
#घोषणा kvm_async_pf_init() (0)
#घोषणा kvm_async_pf_deinit() करो अणुपूर्ण जबतक (0)
#घोषणा kvm_async_pf_vcpu_init(C) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

#पूर्ण_अगर
