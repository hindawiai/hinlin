<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PARISC_HARDWARE_H
#घोषणा _PARISC_HARDWARE_H

#समावेश <linux/mod_devicetable.h>

#घोषणा HWTYPE_ANY_ID		PA_HWTYPE_ANY_ID
#घोषणा HVERSION_ANY_ID		PA_HVERSION_ANY_ID
#घोषणा HVERSION_REV_ANY_ID	PA_HVERSION_REV_ANY_ID
#घोषणा SVERSION_ANY_ID		PA_SVERSION_ANY_ID

काष्ठा hp_hardware अणु
	अचिन्हित लघु	hw_type:5;	/* HPHW_xxx */
	अचिन्हित लघु	hversion;
	अचिन्हित दीर्घ	sversion:28;
	अचिन्हित लघु	opt;
	स्थिर अक्षर	name[80];	/* The hardware description */
पूर्ण;

काष्ठा parisc_device;

क्रमागत cpu_type अणु
	pcx	= 0, /* pa7000		pa 1.0  */
	pcxs	= 1, /* pa7000		pa 1.1a */
	pcxt	= 2, /* pa7100		pa 1.1b */
	pcxt_	= 3, /* pa7200	(t')	pa 1.1c */
	pcxl	= 4, /* pa7100lc	pa 1.1d */
	pcxl2	= 5, /* pa7300lc	pa 1.1e */
	pcxu	= 6, /* pa8000		pa 2.0  */
	pcxu_	= 7, /* pa8200	(u+)	pa 2.0  */
	pcxw	= 8, /* pa8500		pa 2.0  */
	pcxw_	= 9, /* pa8600	(w+)	pa 2.0  */
	pcxw2	= 10, /* pa8700		pa 2.0  */
	mako	= 11, /* pa8800		pa 2.0  */
	mako2	= 12  /* pa8900		pa 2.0  */
पूर्ण;

बाह्य स्थिर अक्षर * स्थिर cpu_name_version[][2]; /* mapping from क्रमागत cpu_type to strings */

काष्ठा parisc_driver;

काष्ठा io_module अणु
        अस्थिर uपूर्णांक32_t nothing;		/* reg 0 */
        अस्थिर uपूर्णांक32_t io_eim;
        अस्थिर uपूर्णांक32_t io_dc_adata;
        अस्थिर uपूर्णांक32_t io_ii_cdata;
        अस्थिर uपूर्णांक32_t io_dma_link;		/* reg 4 */
        अस्थिर uपूर्णांक32_t io_dma_command;
        अस्थिर uपूर्णांक32_t io_dma_address;
        अस्थिर uपूर्णांक32_t io_dma_count;
        अस्थिर uपूर्णांक32_t io_flex;		/* reg 8 */
        अस्थिर uपूर्णांक32_t io_spa_address;
        अस्थिर uपूर्णांक32_t reserved1[2];
        अस्थिर uपूर्णांक32_t io_command;		/* reg 12 */
        अस्थिर uपूर्णांक32_t io_status;
        अस्थिर uपूर्णांक32_t io_control;
        अस्थिर uपूर्णांक32_t io_data;
        अस्थिर uपूर्णांक32_t reserved2;		/* reg 16 */
        अस्थिर uपूर्णांक32_t chain_addr;
        अस्थिर uपूर्णांक32_t sub_mask_clr;
        अस्थिर uपूर्णांक32_t reserved3[13];
        अस्थिर uपूर्णांक32_t undefined[480];
        अस्थिर uपूर्णांक32_t unpriv[512];
पूर्ण;

काष्ठा bc_module अणु
        अस्थिर uपूर्णांक32_t unused1[12];
        अस्थिर uपूर्णांक32_t io_command;
        अस्थिर uपूर्णांक32_t io_status;
        अस्थिर uपूर्णांक32_t io_control;
        अस्थिर uपूर्णांक32_t unused2[1];
        अस्थिर uपूर्णांक32_t io_err_resp;
        अस्थिर uपूर्णांक32_t io_err_info;
        अस्थिर uपूर्णांक32_t io_err_req;
        अस्थिर uपूर्णांक32_t unused3[11];
        अस्थिर uपूर्णांक32_t io_io_low;
        अस्थिर uपूर्णांक32_t io_io_high;
पूर्ण;

#घोषणा HPHW_NPROC     0 
#घोषणा HPHW_MEMORY    1       
#घोषणा HPHW_B_DMA     2
#घोषणा HPHW_OBSOLETE  3
#घोषणा HPHW_A_DMA     4
#घोषणा HPHW_A_सूचीECT  5
#घोषणा HPHW_OTHER     6
#घोषणा HPHW_BCPORT    7
#घोषणा HPHW_CIO       8
#घोषणा HPHW_CONSOLE   9
#घोषणा HPHW_FIO       10
#घोषणा HPHW_BA        11
#घोषणा HPHW_IOA       12
#घोषणा HPHW_BRIDGE    13
#घोषणा HPHW_FABRIC    14
#घोषणा HPHW_MC	       15
#घोषणा HPHW_FAULTY    31

काष्ठा parisc_device_id;

/* hardware.c: */
बाह्य स्थिर अक्षर *parisc_hardware_description(काष्ठा parisc_device_id *id);
बाह्य क्रमागत cpu_type parisc_get_cpu_type(अचिन्हित दीर्घ hversion);

काष्ठा pci_dev;
काष्ठा hardware_path;

/* drivers.c: */
बाह्य काष्ठा parisc_device *alloc_pa_dev(अचिन्हित दीर्घ hpa,
		काष्ठा hardware_path *path);
बाह्य पूर्णांक रेजिस्टर_parisc_device(काष्ठा parisc_device *dev);
बाह्य पूर्णांक रेजिस्टर_parisc_driver(काष्ठा parisc_driver *driver);
बाह्य पूर्णांक count_parisc_driver(काष्ठा parisc_driver *driver);
बाह्य पूर्णांक unरेजिस्टर_parisc_driver(काष्ठा parisc_driver *driver);
बाह्य व्योम walk_central_bus(व्योम);
बाह्य स्थिर काष्ठा parisc_device *find_pa_parent_type(स्थिर काष्ठा parisc_device *, पूर्णांक);
बाह्य व्योम prपूर्णांक_parisc_devices(व्योम);
बाह्य अक्षर *prपूर्णांक_pa_hwpath(काष्ठा parisc_device *dev, अक्षर *path);
बाह्य अक्षर *prपूर्णांक_pci_hwpath(काष्ठा pci_dev *dev, अक्षर *path);
बाह्य व्योम get_pci_node_path(काष्ठा pci_dev *dev, काष्ठा hardware_path *path);
बाह्य व्योम init_parisc_bus(व्योम);
बाह्य काष्ठा device *hwpath_to_device(काष्ठा hardware_path *modpath);
बाह्य व्योम device_to_hwpath(काष्ठा device *dev, काष्ठा hardware_path *path);
बाह्य पूर्णांक machine_has_merced_bus(व्योम);

/* inventory.c: */
बाह्य व्योम करो_memory_inventory(व्योम);
बाह्य व्योम करो_device_inventory(व्योम);

#पूर्ण_अगर /* _PARISC_HARDWARE_H */
