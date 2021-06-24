<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008-2013 Freescale Semiconductor, Inc. All rights reserved.
 */

#अगर_अघोषित KVM_E500_MMU_HOST_H
#घोषणा KVM_E500_MMU_HOST_H

व्योम inval_gtlbe_on_host(काष्ठा kvmppc_vcpu_e500 *vcpu_e500, पूर्णांक tlbsel,
			 पूर्णांक esel);

पूर्णांक e500_mmu_host_init(काष्ठा kvmppc_vcpu_e500 *vcpu_e500);
व्योम e500_mmu_host_uninit(काष्ठा kvmppc_vcpu_e500 *vcpu_e500);

#पूर्ण_अगर /* KVM_E500_MMU_HOST_H */
