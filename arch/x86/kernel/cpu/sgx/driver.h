<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_SGX_DRIVER_H__
#घोषणा __ARCH_SGX_DRIVER_H__

#समावेश <crypto/hash.h>
#समावेश <linux/kref.h>
#समावेश <linux/mmu_notअगरier.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/sched.h>
#समावेश <linux/workqueue.h>
#समावेश <uapi/यंत्र/sgx.h>
#समावेश "sgx.h"

#घोषणा SGX_EINIT_SPIN_COUNT	20
#घोषणा SGX_EINIT_SLEEP_COUNT	50
#घोषणा SGX_EINIT_SLEEP_TIME	20

बाह्य u64 sgx_attributes_reserved_mask;
बाह्य u64 sgx_xfrm_reserved_mask;
बाह्य u32 sgx_misc_reserved_mask;

बाह्य स्थिर काष्ठा file_operations sgx_provision_fops;

दीर्घ sgx_ioctl(काष्ठा file *filep, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

पूर्णांक sgx_drv_init(व्योम);

#पूर्ण_अगर /* __ARCH_X86_SGX_DRIVER_H__ */
