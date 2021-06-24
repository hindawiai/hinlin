<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BPF_PRELOAD_H
#घोषणा _BPF_PRELOAD_H

#समावेश <linux/usermode_driver.h>
#समावेश "iterators/bpf_preload_common.h"

काष्ठा bpf_preload_ops अणु
        काष्ठा umd_info info;
	पूर्णांक (*preload)(काष्ठा bpf_preload_info *);
	पूर्णांक (*finish)(व्योम);
	काष्ठा module *owner;
पूर्ण;
बाह्य काष्ठा bpf_preload_ops *bpf_preload_ops;
#घोषणा BPF_PRELOAD_LINKS 2
#पूर्ण_अगर
