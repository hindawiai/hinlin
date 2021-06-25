<शैली गुरु>
/*
 * Platक्रमm inक्रमmation definitions.
 *
 * 2006 (c) MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#अगर_अघोषित FS_PD_H
#घोषणा FS_PD_H
#समावेश <sysdev/fsl_soc.h>
#समावेश <यंत्र/समय.स>

#अगर_घोषित CONFIG_CPM2
#समावेश <यंत्र/cpm2.h>

#अगर defined(CONFIG_8260)
#समावेश <यंत्र/mpc8260.h>
#पूर्ण_अगर

#घोषणा cpm2_map(member) (&cpm2_immr->member)
#घोषणा cpm2_map_size(member, size) (&cpm2_immr->member)
#घोषणा cpm2_unmap(addr) करो अणुपूर्ण जबतक(0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_8xx
#समावेश <यंत्र/8xx_immap.h>

बाह्य immap_t __iomem *mpc8xx_immr;

#घोषणा immr_map(member) (&mpc8xx_immr->member)
#घोषणा immr_map_size(member, size) (&mpc8xx_immr->member)
#घोषणा immr_unmap(addr) करो अणुपूर्ण जबतक (0)
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक uart_baudrate(व्योम)
अणु
        वापस get_baudrate();
पूर्ण

अटल अंतरभूत पूर्णांक uart_घड़ी(व्योम)
अणु
        वापस ppc_proc_freq;
पूर्ण

#पूर्ण_अगर
