<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PCR_H
#घोषणा __PCR_H

काष्ठा pcr_ops अणु
	u64 (*पढ़ो_pcr)(अचिन्हित दीर्घ);
	व्योम (*ग_लिखो_pcr)(अचिन्हित दीर्घ, u64);
	u64 (*पढ़ो_pic)(अचिन्हित दीर्घ);
	व्योम (*ग_लिखो_pic)(अचिन्हित दीर्घ, u64);
	u64 (*nmi_picl_value)(अचिन्हित पूर्णांक nmi_hz);
	u64 pcr_nmi_enable;
	u64 pcr_nmi_disable;
पूर्ण;
बाह्य स्थिर काष्ठा pcr_ops *pcr_ops;

व्योम deferred_pcr_work_irq(पूर्णांक irq, काष्ठा pt_regs *regs);
व्योम schedule_deferred_pcr_work(व्योम);

#घोषणा PCR_PIC_PRIV		0x00000001 /* PIC access is privileged */
#घोषणा PCR_STRACE		0x00000002 /* Trace supervisor events  */
#घोषणा PCR_UTRACE		0x00000004 /* Trace user events        */
#घोषणा PCR_N2_HTRACE		0x00000008 /* Trace hypervisor events  */
#घोषणा PCR_N2_TOE_OV0		0x00000010 /* Trap अगर PIC 0 overflows  */
#घोषणा PCR_N2_TOE_OV1		0x00000020 /* Trap अगर PIC 1 overflows  */
#घोषणा PCR_N2_MASK0		0x00003fc0
#घोषणा PCR_N2_MASK0_SHIFT	6
#घोषणा PCR_N2_SL0		0x0003c000
#घोषणा PCR_N2_SL0_SHIFT	14
#घोषणा PCR_N2_OV0		0x00040000
#घोषणा PCR_N2_MASK1		0x07f80000
#घोषणा PCR_N2_MASK1_SHIFT	19
#घोषणा PCR_N2_SL1		0x78000000
#घोषणा PCR_N2_SL1_SHIFT	27
#घोषणा PCR_N2_OV1		0x80000000

#घोषणा PCR_N4_OV		0x00000001 /* PIC overflow             */
#घोषणा PCR_N4_TOE		0x00000002 /* Trap On Event            */
#घोषणा PCR_N4_UTRACE		0x00000004 /* Trace user events        */
#घोषणा PCR_N4_STRACE		0x00000008 /* Trace supervisor events  */
#घोषणा PCR_N4_HTRACE		0x00000010 /* Trace hypervisor events  */
#घोषणा PCR_N4_MASK		0x000007e0 /* Event mask               */
#घोषणा PCR_N4_MASK_SHIFT	5
#घोषणा PCR_N4_SL		0x0000f800 /* Event Select             */
#घोषणा PCR_N4_SL_SHIFT		11
#घोषणा PCR_N4_PICNPT		0x00010000 /* PIC non-privileged trap  */
#घोषणा PCR_N4_PICNHT		0x00020000 /* PIC non-hypervisor trap  */
#घोषणा PCR_N4_NTC		0x00040000 /* Next-To-Commit wrap      */

पूर्णांक pcr_arch_init(व्योम);

#पूर्ण_अगर /* __PCR_H */
