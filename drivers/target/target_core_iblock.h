<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित TARGET_CORE_IBLOCK_H
#घोषणा TARGET_CORE_IBLOCK_H

#समावेश <linux/atomic.h>
#समावेश <linux/refcount.h>
#समावेश <linux/blkdev.h>
#समावेश <target/target_core_base.h>

#घोषणा IBLOCK_VERSION		"4.0"

#घोषणा IBLOCK_MAX_CDBS		16

काष्ठा iblock_req अणु
	refcount_t pending;
	atomic_t ib_bio_err_cnt;
पूर्ण ____cacheline_aligned;

#घोषणा IBDF_HAS_UDEV_PATH		0x01

#घोषणा IBD_PLUGF_PLUGGED		0x01

काष्ठा iblock_dev_plug अणु
	काष्ठा se_dev_plug se_plug;
	काष्ठा blk_plug blk_plug;
	अचिन्हित दीर्घ flags;
पूर्ण;

काष्ठा iblock_dev अणु
	काष्ठा se_device dev;
	अचिन्हित अक्षर ibd_udev_path[SE_UDEV_PATH_LEN];
	u32	ibd_flags;
	काष्ठा bio_set	ibd_bio_set;
	काष्ठा block_device *ibd_bd;
	bool ibd_पढ़ोonly;
	काष्ठा iblock_dev_plug *ibd_plug;
पूर्ण ____cacheline_aligned;

#पूर्ण_अगर /* TARGET_CORE_IBLOCK_H */
