<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _M68K_MACHDEP_H
#घोषणा _M68K_MACHDEP_H

#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>

काष्ठा pt_regs;
काष्ठा स_गढ़ो;
काष्ठा rtc_समय;
काष्ठा rtc_pll_info;
काष्ठा buffer_head;

बाह्य व्योम (*mach_sched_init) (व्योम);
/* machine dependent irq functions */
बाह्य व्योम (*mach_init_IRQ) (व्योम);
बाह्य व्योम (*mach_get_model) (अक्षर *model);
बाह्य व्योम (*mach_get_hardware_list) (काष्ठा seq_file *m);
/* machine dependent समयr functions */
बाह्य पूर्णांक (*mach_hwclk)(पूर्णांक, काष्ठा rtc_समय*);
बाह्य अचिन्हित पूर्णांक (*mach_get_ss)(व्योम);
बाह्य पूर्णांक (*mach_get_rtc_pll)(काष्ठा rtc_pll_info *);
बाह्य पूर्णांक (*mach_set_rtc_pll)(काष्ठा rtc_pll_info *);
बाह्य व्योम (*mach_reset)( व्योम );
बाह्य व्योम (*mach_halt)( व्योम );
बाह्य व्योम (*mach_घातer_off)( व्योम );
बाह्य अचिन्हित दीर्घ (*mach_hd_init) (अचिन्हित दीर्घ, अचिन्हित दीर्घ);
बाह्य व्योम (*mach_hd_setup)(अक्षर *, पूर्णांक *);
बाह्य व्योम (*mach_heartbeat) (पूर्णांक);
बाह्य व्योम (*mach_l2_flush) (पूर्णांक);
बाह्य व्योम (*mach_beep) (अचिन्हित पूर्णांक, अचिन्हित पूर्णांक);

/* Hardware घड़ी functions */
बाह्य व्योम hw_समयr_init(व्योम);
#अगर_घोषित CONFIG_HEARTBEAT
बाह्य व्योम समयr_heartbeat(व्योम);
#अन्यथा
अटल अंतरभूत व्योम समयr_heartbeat(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

बाह्य व्योम config_BSP(अक्षर *command, पूर्णांक len);

#पूर्ण_अगर /* _M68K_MACHDEP_H */
