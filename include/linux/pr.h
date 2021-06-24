<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_PR_H
#घोषणा LINUX_PR_H

#समावेश <uapi/linux/pr.h>

काष्ठा pr_ops अणु
	पूर्णांक (*pr_रेजिस्टर)(काष्ठा block_device *bdev, u64 old_key, u64 new_key,
			u32 flags);
	पूर्णांक (*pr_reserve)(काष्ठा block_device *bdev, u64 key,
			क्रमागत pr_type type, u32 flags);
	पूर्णांक (*pr_release)(काष्ठा block_device *bdev, u64 key,
			क्रमागत pr_type type);
	पूर्णांक (*pr_preempt)(काष्ठा block_device *bdev, u64 old_key, u64 new_key,
			क्रमागत pr_type type, bool पात);
	पूर्णांक (*pr_clear)(काष्ठा block_device *bdev, u64 key);
पूर्ण;

#पूर्ण_अगर /* LINUX_PR_H */
