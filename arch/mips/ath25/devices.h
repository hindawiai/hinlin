<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ATH25_DEVICES_H
#घोषणा __ATH25_DEVICES_H

#समावेश <linux/cpu.h>

#घोषणा ATH25_REG_MS(_val, _field)	(((_val) & _field##_M) >> _field##_S)

#घोषणा ATH25_IRQ_CPU_CLOCK	(MIPS_CPU_IRQ_BASE + 7)	/* C0_CAUSE: 0x8000 */

क्रमागत ath25_soc_type अणु
	/* handled by ar5312.c */
	ATH25_SOC_AR2312,
	ATH25_SOC_AR2313,
	ATH25_SOC_AR5312,

	/* handled by ar2315.c */
	ATH25_SOC_AR2315,
	ATH25_SOC_AR2316,
	ATH25_SOC_AR2317,
	ATH25_SOC_AR2318,

	ATH25_SOC_UNKNOWN
पूर्ण;

बाह्य क्रमागत ath25_soc_type ath25_soc;
बाह्य काष्ठा ar231x_board_config ath25_board;
बाह्य व्योम (*ath25_irq_dispatch)(व्योम);

पूर्णांक ath25_find_config(phys_addr_t offset, अचिन्हित दीर्घ size);
व्योम ath25_serial_setup(u32 mapbase, पूर्णांक irq, अचिन्हित पूर्णांक uartclk);
पूर्णांक ath25_add_wmac(पूर्णांक nr, u32 base, पूर्णांक irq);

अटल अंतरभूत bool is_ar2315(व्योम)
अणु
	वापस (current_cpu_data.cputype == CPU_4KEC);
पूर्ण

अटल अंतरभूत bool is_ar5312(व्योम)
अणु
	वापस !is_ar2315();
पूर्ण

#पूर्ण_अगर
