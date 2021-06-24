<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __PPC_FSL_SOC_H
#घोषणा __PPC_FSL_SOC_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/mmu.h>

काष्ठा spi_device;

बाह्य phys_addr_t get_immrbase(व्योम);
#अगर defined(CONFIG_CPM) || defined(CONFIG_QUICC_ENGINE)
बाह्य u32 get_brgfreq(व्योम);
बाह्य u32 get_baudrate(व्योम);
#अन्यथा
अटल अंतरभूत u32 get_brgfreq(व्योम) अणु वापस -1; पूर्ण
अटल अंतरभूत u32 get_baudrate(व्योम) अणु वापस -1; पूर्ण
#पूर्ण_अगर
बाह्य u32 fsl_get_sys_freq(व्योम);

काष्ठा spi_board_info;
काष्ठा device_node;

/* The dअगरferent ports that the DIU can be connected to */
क्रमागत fsl_diu_monitor_port अणु
	FSL_DIU_PORT_DVI,	/* DVI */
	FSL_DIU_PORT_LVDS,	/* Single-link LVDS */
	FSL_DIU_PORT_DLVDS	/* Dual-link LVDS */
पूर्ण;

काष्ठा platक्रमm_diu_data_ops अणु
	u32 (*get_pixel_क्रमmat)(क्रमागत fsl_diu_monitor_port port,
		अचिन्हित पूर्णांक bpp);
	व्योम (*set_gamma_table)(क्रमागत fsl_diu_monitor_port port,
		अक्षर *gamma_table_base);
	व्योम (*set_monitor_port)(क्रमागत fsl_diu_monitor_port port);
	व्योम (*set_pixel_घड़ी)(अचिन्हित पूर्णांक pixघड़ी);
	क्रमागत fsl_diu_monitor_port (*valid_monitor_port)
		(क्रमागत fsl_diu_monitor_port port);
	व्योम (*release_booपंचांगem)(व्योम);
पूर्ण;

बाह्य काष्ठा platक्रमm_diu_data_ops diu_ops;

व्योम __noवापस fsl_hv_restart(अक्षर *cmd);
व्योम __noवापस fsl_hv_halt(व्योम);

#पूर्ण_अगर
#पूर्ण_अगर
