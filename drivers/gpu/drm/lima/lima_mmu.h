<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_MMU_H__
#घोषणा __LIMA_MMU_H__

काष्ठा lima_ip;
काष्ठा lima_vm;

पूर्णांक lima_mmu_resume(काष्ठा lima_ip *ip);
व्योम lima_mmu_suspend(काष्ठा lima_ip *ip);
पूर्णांक lima_mmu_init(काष्ठा lima_ip *ip);
व्योम lima_mmu_fini(काष्ठा lima_ip *ip);

व्योम lima_mmu_flush_tlb(काष्ठा lima_ip *ip);
व्योम lima_mmu_चयन_vm(काष्ठा lima_ip *ip, काष्ठा lima_vm *vm);
व्योम lima_mmu_page_fault_resume(काष्ठा lima_ip *ip);

#पूर्ण_अगर
