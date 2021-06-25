<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Private data and functions क्रम adjunct processor VFIO matrix driver.
 *
 * Author(s): Tony Krowiak <akrowiak@linux.ibm.com>
 *	      Halil Pasic <pasic@linux.ibm.com>
 *	      Pierre Morel <pmorel@linux.ibm.com>
 *
 * Copyright IBM Corp. 2018
 */

#अगर_अघोषित _VFIO_AP_PRIVATE_H_
#घोषणा _VFIO_AP_PRIVATE_H_

#समावेश <linux/types.h>
#समावेश <linux/device.h>
#समावेश <linux/mdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kvm_host.h>

#समावेश "ap_bus.h"

#घोषणा VFIO_AP_MODULE_NAME "vfio_ap"
#घोषणा VFIO_AP_DRV_NAME "vfio_ap"

/**
 * ap_matrix_dev - the AP matrix device काष्ठाure
 * @device:	generic device काष्ठाure associated with the AP matrix device
 * @available_instances: number of mediated matrix devices that can be created
 * @info:	the काष्ठा containing the output from the PQAP(QCI) inकाष्ठाion
 * mdev_list:	the list of mediated matrix devices created
 * lock:	mutex क्रम locking the AP matrix device. This lock will be
 *		taken every समय we fiddle with state managed by the vfio_ap
 *		driver, be it using @mdev_list or writing the state of a
 *		single ap_matrix_mdev device. It's quite coarse but we don't
 *		expect much contention.
 */
काष्ठा ap_matrix_dev अणु
	काष्ठा device device;
	atomic_t available_instances;
	काष्ठा ap_config_info info;
	काष्ठा list_head mdev_list;
	काष्ठा mutex lock;
	काष्ठा ap_driver  *vfio_ap_drv;
पूर्ण;

बाह्य काष्ठा ap_matrix_dev *matrix_dev;

/**
 * The AP matrix is comprised of three bit masks identअगरying the adapters,
 * queues (करोमुख्यs) and control करोमुख्यs that beदीर्घ to an AP matrix. The bits i
 * each mask, from least signअगरicant to most signअगरicant bit, correspond to IDs
 * 0 to 255. When a bit is set, the corresponding ID beदीर्घs to the matrix.
 *
 * @apm_max: max adapter number in @apm
 * @apm identअगरies the AP adapters in the matrix
 * @aqm_max: max करोमुख्य number in @aqm
 * @aqm identअगरies the AP queues (करोमुख्यs) in the matrix
 * @adm_max: max करोमुख्य number in @adm
 * @adm identअगरies the AP control करोमुख्यs in the matrix
 */
काष्ठा ap_matrix अणु
	अचिन्हित दीर्घ apm_max;
	DECLARE_BITMAP(apm, 256);
	अचिन्हित दीर्घ aqm_max;
	DECLARE_BITMAP(aqm, 256);
	अचिन्हित दीर्घ adm_max;
	DECLARE_BITMAP(adm, 256);
पूर्ण;

/**
 * काष्ठा ap_matrix_mdev - the mediated matrix device काष्ठाure
 * @list:	allows the ap_matrix_mdev काष्ठा to be added to a list
 * @matrix:	the adapters, usage करोमुख्यs and control करोमुख्यs asचिन्हित to the
 *		mediated matrix device.
 * @group_notअगरier: notअगरier block used क्रम specअगरying callback function क्रम
 *		    handling the VFIO_GROUP_NOTIFY_SET_KVM event
 * @kvm:	the काष्ठा holding guest's state
 */
काष्ठा ap_matrix_mdev अणु
	काष्ठा list_head node;
	काष्ठा ap_matrix matrix;
	काष्ठा notअगरier_block group_notअगरier;
	काष्ठा notअगरier_block iommu_notअगरier;
	bool kvm_busy;
	रुको_queue_head_t रुको_क्रम_kvm;
	काष्ठा kvm *kvm;
	काष्ठा kvm_s390_module_hook pqap_hook;
	काष्ठा mdev_device *mdev;
पूर्ण;

काष्ठा vfio_ap_queue अणु
	काष्ठा ap_matrix_mdev *matrix_mdev;
	अचिन्हित दीर्घ saved_pfn;
	पूर्णांक	apqn;
#घोषणा VFIO_AP_ISC_INVALID 0xff
	अचिन्हित अक्षर saved_isc;
पूर्ण;

पूर्णांक vfio_ap_mdev_रेजिस्टर(व्योम);
व्योम vfio_ap_mdev_unरेजिस्टर(व्योम);
पूर्णांक vfio_ap_mdev_reset_queue(काष्ठा vfio_ap_queue *q,
			     अचिन्हित पूर्णांक retry);

#पूर्ण_अगर /* _VFIO_AP_PRIVATE_H_ */
