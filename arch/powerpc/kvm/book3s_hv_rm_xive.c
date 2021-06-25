<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/kvm_host.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/kvm_book3s.h>
#समावेश <यंत्र/kvm_ppc.h>
#समावेश <यंत्र/hvcall.h>
#समावेश <यंत्र/xics.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/synch.h>
#समावेश <यंत्र/cputhपढ़ोs.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/pnv-pci.h>
#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/xive.h>
#समावेश <यंत्र/xive-regs.h>

#समावेश "book3s_xive.h"

/* XXX */
#समावेश <यंत्र/udbg.h>
//#घोषणा DBG(fmt...) udbg_म_लिखो(fmt)
#घोषणा DBG(fmt...) करो अणु पूर्ण जबतक(0)

अटल अंतरभूत व्योम __iomem *get_tima_phys(व्योम)
अणु
	वापस local_paca->kvm_hstate.xive_tima_phys;
पूर्ण

#अघोषित XIVE_RUNTIME_CHECKS
#घोषणा X_PFX xive_rm_
#घोषणा X_STATIC
#घोषणा X_STAT_PFX stat_rm_
#घोषणा __x_tima		get_tima_phys()
#घोषणा __x_eoi_page(xd)	((व्योम __iomem *)((xd)->eoi_page))
#घोषणा __x_trig_page(xd)	((व्योम __iomem *)((xd)->trig_page))
#घोषणा __x_ग_लिखोb	__raw_rm_ग_लिखोb
#घोषणा __x_पढ़ोw	__raw_rm_पढ़ोw
#घोषणा __x_पढ़ोq	__raw_rm_पढ़ोq
#घोषणा __x_ग_लिखोq	__raw_rm_ग_लिखोq

#समावेश "book3s_xive_template.c"
