<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * (c) 2001, 2006 IBM Corporation.
 */

#अगर_अघोषित _ASM_POWERPC_UDBG_H
#घोषणा _ASM_POWERPC_UDBG_H
#अगर_घोषित __KERNEL__

#समावेश <linux/compiler.h>
#समावेश <linux/init.h>

बाह्य व्योम (*udbg_अ_दो)(अक्षर c);
बाह्य व्योम (*udbg_flush)(व्योम);
बाह्य पूर्णांक (*udbg_अ_लो)(व्योम);
बाह्य पूर्णांक (*udbg_अ_लो_poll)(व्योम);

बाह्य व्योम udbg_माला_दो(स्थिर अक्षर *s);
बाह्य पूर्णांक udbg_ग_लिखो(स्थिर अक्षर *s, पूर्णांक n);

बाह्य व्योम रेजिस्टर_early_udbg_console(व्योम);
बाह्य व्योम udbg_म_लिखो(स्थिर अक्षर *fmt, ...)
	__attribute__ ((क्रमmat (म_लिखो, 1, 2)));
बाह्य व्योम udbg_progress(अक्षर *s, अचिन्हित लघु hex);

बाह्य व्योम udbg_uart_init_mmio(व्योम __iomem *addr, अचिन्हित पूर्णांक stride);
बाह्य व्योम udbg_uart_init_pio(अचिन्हित दीर्घ port, अचिन्हित पूर्णांक stride);

बाह्य व्योम udbg_uart_setup(अचिन्हित पूर्णांक speed, अचिन्हित पूर्णांक घड़ी);
बाह्य अचिन्हित पूर्णांक udbg_probe_uart_speed(अचिन्हित पूर्णांक घड़ी);

काष्ठा device_node;
बाह्य व्योम udbg_scc_init(पूर्णांक क्रमce_scc);
बाह्य पूर्णांक udbg_adb_init(पूर्णांक क्रमce_btext);
बाह्य व्योम udbg_adb_init_early(व्योम);

बाह्य व्योम __init udbg_early_init(व्योम);
बाह्य व्योम __init udbg_init_debug_lpar(व्योम);
बाह्य व्योम __init udbg_init_debug_lpar_hvsi(व्योम);
बाह्य व्योम __init udbg_init_pmac_realmode(व्योम);
बाह्य व्योम __init udbg_init_maple_realmode(व्योम);
बाह्य व्योम __init udbg_init_pas_realmode(व्योम);
बाह्य व्योम __init udbg_init_rtas_panel(व्योम);
बाह्य व्योम __init udbg_init_rtas_console(व्योम);
बाह्य व्योम __init udbg_init_debug_beat(व्योम);
बाह्य व्योम __init udbg_init_btext(व्योम);
बाह्य व्योम __init udbg_init_44x_as1(व्योम);
बाह्य व्योम __init udbg_init_40x_realmode(व्योम);
बाह्य व्योम __init udbg_init_cpm(व्योम);
बाह्य व्योम __init udbg_init_usbgecko(व्योम);
बाह्य व्योम __init udbg_init_memcons(व्योम);
बाह्य व्योम __init udbg_init_ehv_bc(व्योम);
बाह्य व्योम __init udbg_init_ps3gelic(व्योम);
बाह्य व्योम __init udbg_init_debug_opal_raw(व्योम);
बाह्य व्योम __init udbg_init_debug_opal_hvsi(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_UDBG_H */
