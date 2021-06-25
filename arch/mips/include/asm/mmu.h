<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_MMU_H
#घोषणा __ASM_MMU_H

#समावेश <linux/atomic.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

प्रकार काष्ठा अणु
	जोड़ अणु
		u64 asid[NR_CPUS];
		atomic64_t mmid;
	पूर्ण;

	व्योम *vdso;

	/* lock to be held whilst modअगरying fp_bd_emupage_allocmap */
	spinlock_t bd_emupage_lock;
	/* biपंचांगap tracking allocation of fp_bd_emupage */
	अचिन्हित दीर्घ *bd_emupage_allocmap;
	/* रुको queue क्रम thपढ़ोs requiring an emuframe */
	रुको_queue_head_t bd_emupage_queue;
पूर्ण mm_context_t;

#पूर्ण_अगर /* __ASM_MMU_H */
