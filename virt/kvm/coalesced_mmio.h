<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __KVM_COALESCED_MMIO_H__
#घोषणा __KVM_COALESCED_MMIO_H__

/*
 * KVM coalesced MMIO
 *
 * Copyright (c) 2008 Bull S.A.S.
 *
 *  Author: Laurent Vivier <Laurent.Vivier@bull.net>
 *
 */

#अगर_घोषित CONFIG_KVM_MMIO

#समावेश <linux/list.h>

काष्ठा kvm_coalesced_mmio_dev अणु
	काष्ठा list_head list;
	काष्ठा kvm_io_device dev;
	काष्ठा kvm *kvm;
	काष्ठा kvm_coalesced_mmio_zone zone;
पूर्ण;

पूर्णांक kvm_coalesced_mmio_init(काष्ठा kvm *kvm);
व्योम kvm_coalesced_mmio_मुक्त(काष्ठा kvm *kvm);
पूर्णांक kvm_vm_ioctl_रेजिस्टर_coalesced_mmio(काष्ठा kvm *kvm,
					काष्ठा kvm_coalesced_mmio_zone *zone);
पूर्णांक kvm_vm_ioctl_unरेजिस्टर_coalesced_mmio(काष्ठा kvm *kvm,
					काष्ठा kvm_coalesced_mmio_zone *zone);

#अन्यथा

अटल अंतरभूत पूर्णांक kvm_coalesced_mmio_init(काष्ठा kvm *kvm) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम kvm_coalesced_mmio_मुक्त(काष्ठा kvm *kvm) अणु पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
