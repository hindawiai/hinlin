<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PMAC_H__
#घोषणा __PMAC_H__

#समावेश <linux/pci.h>
#समावेश <linux/irq.h>

/*
 * Declaration क्रम the various functions exported by the
 * pmac_* files. Mostly क्रम use by pmac_setup
 */

काष्ठा rtc_समय;

बाह्य पूर्णांक pmac_newworld;

बाह्य दीर्घ pmac_समय_init(व्योम);
बाह्य समय64_t pmac_get_boot_समय(व्योम);
बाह्य व्योम pmac_get_rtc_समय(काष्ठा rtc_समय *);
बाह्य पूर्णांक pmac_set_rtc_समय(काष्ठा rtc_समय *);
बाह्य व्योम pmac_पढ़ो_rtc_समय(व्योम);
बाह्य व्योम pmac_calibrate_decr(व्योम);
बाह्य व्योम pmac_pci_irq_fixup(काष्ठा pci_dev *);
बाह्य व्योम pmac_pci_init(व्योम);

बाह्य व्योम pmac_nvram_update(व्योम);
बाह्य अचिन्हित अक्षर pmac_nvram_पढ़ो_byte(पूर्णांक addr);
बाह्य व्योम pmac_nvram_ग_लिखो_byte(पूर्णांक addr, अचिन्हित अक्षर val);
बाह्य व्योम pmac_pcibios_after_init(व्योम);
बाह्य पूर्णांक of_show_percpuinfo(काष्ठा seq_file *m, पूर्णांक i);

बाह्य व्योम pmac_setup_pci_dma(व्योम);
बाह्य व्योम pmac_check_ht_link(व्योम);

बाह्य व्योम pmac_setup_smp(व्योम);
बाह्य पूर्णांक psurge_secondary_virq;
बाह्य व्योम low_cpu_offline_self(व्योम) __attribute__((noवापस));

बाह्य पूर्णांक pmac_nvram_init(व्योम);
बाह्य व्योम pmac_pic_init(व्योम);

बाह्य काष्ठा pci_controller_ops pmac_pci_controller_ops;

#पूर्ण_अगर /* __PMAC_H__ */
