<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित MPC85xx_H
#घोषणा MPC85xx_H
बाह्य पूर्णांक mpc85xx_common_publish_devices(व्योम);

#अगर_घोषित CONFIG_CPM2
बाह्य व्योम mpc85xx_cpm2_pic_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init mpc85xx_cpm2_pic_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_CPM2 */

#अगर_घोषित CONFIG_QUICC_ENGINE
बाह्य व्योम mpc85xx_qe_par_io_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम __init mpc85xx_qe_par_io_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
